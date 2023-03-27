#include "cmd.hpp"
#include "subscriber.hpp"
#include <future>
#include <mutex>


std::vector<std::string> split(const std::string &str) {
    char d = '\n';
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

CMD::CMD(int amountOfBlocks) {
    this->m_amountOfBlocks = amountOfBlocks;
}

void CMD::takeConsoleControl() {
    std::string command;
    int k = 1;

    bool isDynamicBlock = false;
    bool isSecondDynmicBlock = false;
    commandsContext msg;
    while(std::getline(std::cin, command)) {
        if(command == "" || command == " ")
            break;

        if(command == "{" && !isDynamicBlock) {
            if(msg.m_commands.size() > 0 && k > 1) {
                this->sendMessage(msg);
                k = 1;
            }
            isDynamicBlock = true;
        } else if(command == "{" && isDynamicBlock) {
            isSecondDynmicBlock = true;
            continue;
        }

        if(command == "}" && isDynamicBlock  && isSecondDynmicBlock) {
            isSecondDynmicBlock = false;
            continue;
        } else if(command == "}" && isDynamicBlock && !isSecondDynmicBlock) {
            this->sendMessage(msg);
            isDynamicBlock = false;
        }

        if(command == "{")
            continue;

        if(command == "}")
            continue; 

        if(k == 1) {
            auto tp_sec = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
            auto tt = std::chrono::system_clock::to_time_t (tp_sec);
            msg.m_firstMessageTime = tt;
        }

        msg.m_commands.push_back(command);
        if(k == this->m_amountOfBlocks && !isDynamicBlock) {          
            this->sendMessage(msg);
            msg.m_commands.clear();
            k = 1;
        } else if(k < this->m_amountOfBlocks && !isDynamicBlock) {
            k++;
        }
    }
}

void CMD::inputControlAsync(const char *data) {
    int k = 1;
    std::string innerData = data;
    std::vector<std::string> commands = split(innerData);
    //commandsContext m_msg;
    for(auto &command: commands){
        if(command == "" || command == " ")
            break;

        if(command == "{" && !m_isDynamicBlock) {
            if(m_msg.m_commands.size() > 0 && k > 1) {
                this->sendMessage(m_msg);
                m_msg.m_commands.clear();
                k = 1;
            }
            m_isDynamicBlock = true;
        } else if(command == "{" && m_isDynamicBlock) {
            m_isSecondDynmicBlock = true;
            continue;
        }

        if(command == "}" && m_isDynamicBlock  && m_isSecondDynmicBlock) {
            m_isSecondDynmicBlock = false;
            continue;
        } else if(command == "}" && m_isDynamicBlock && !m_isSecondDynmicBlock) {
            this->sendMessage(m_msg);
            m_isDynamicBlock = false;
            m_msg.m_commands.clear();
        }

        if(command == "{")
            continue;

        if(command == "}")
            continue; 

        if(k == 1) {
            auto tp_sec = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
            auto tt = std::chrono::system_clock::to_time_t (tp_sec);
            m_msg.m_firstMessageTime = tt;
        }

        
        if(k == this->m_amountOfBlocks && !m_isDynamicBlock) {          
            this->sendMessage(m_msg);
            m_msg.m_commands.clear();
            m_msg.m_commands.push_back(command);
            k = 1;
        } else if(k < this->m_amountOfBlocks && !m_isDynamicBlock) {
            m_msg.m_commands.push_back(command);
            k++;
        }else if(m_isDynamicBlock) {
            m_msg.m_commands.push_back(command);
        }
    }
}

void CMD::sendMessage(commandsContext& msg) {
    subscribersListPtr psubscriberList;
    {
        std::lock_guard<std::mutex> lock(this->m_lock);
        if(!this->mp_subscriberList) {
            return;
        }
        psubscriberList = this->mp_subscriberList;
    }
    for(std::size_t i = 0; i < psubscriberList->size(); ++i) {
        (*psubscriberList)[i]->getISubscriber()->messageHandler(msg);
    }
}

SubscriberId CMD::subscribe(std::shared_ptr<ISubscriber> pNewSubscriber) {
    subscribersListPtr pNewSubscriberList(new subscribersList());
    std::lock_guard<std::mutex> lock(this->m_lock);

    if(this->mp_subscriberList) {
        pNewSubscriberList->assign(this->mp_subscriberList->begin(), this->mp_subscriberList->end());
    }
    for(std::size_t i = 0; i < pNewSubscriberList->size(); ++i) {
        pISubscriberItem pSubscriberItem = (*pNewSubscriberList)[i];
        if(pSubscriberItem->getISubscriber()->getSubscriberId() == pNewSubscriber->getSubscriberId()) {
            return 0;
        }
    }
    pNewSubscriberList->push_back(pISubscriberItem(new ISubscriberItem(pNewSubscriber)));
    this->mp_subscriberList = pNewSubscriberList;
    return pNewSubscriber->getSubscriberId();
}


void CMD::unsubscribe() {
    if(!this->mp_subscriberList) {
        return;
    }
    subscribersListPtr temp(mp_subscriberList);
    for(auto &el: *temp) {
        this->unsubscribe(el->getISubscriber()->getSubscriberId());
    }
    mp_subscriberList = temp;
}

bool CMD::unsubscribe(SubscriberId id) {
    pISubscriberItem pSubcriberItemToRelease;
    subscribersListPtr pNewSubcriberList;
    std::lock_guard<std::mutex> lock(this->m_lock);
    if(!this->mp_subscriberList) {
        return false;
    }
    pNewSubcriberList = subscribersListPtr(new subscribersList());
    for(std::size_t i = 0; i < this->mp_subscriberList->size(); ++i) {
        pISubscriberItem pSubscriberItem = (*this->mp_subscriberList)[i];
        if(pSubscriberItem->getISubscriber()->getSubscriberId() == id) {
            pSubcriberItemToRelease = pSubscriberItem;
        } else {
            pNewSubcriberList->push_back(pSubscriberItem);
        }
    }
    this->mp_subscriberList = pNewSubcriberList;
    if(!pSubcriberItemToRelease.get()) {
        return false;
    }

    return true;
}
