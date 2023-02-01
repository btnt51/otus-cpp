#include "cmd.hpp"


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

        if(k == 1)
            msg.m_firstMessageTime = std::chrono::system_clock::now();

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
