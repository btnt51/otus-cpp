#include "async.h"
#include "cmd.hpp"
#include "outputCMD.hpp"
#include "loggerManager.hpp"
#include <cstring>
#include <future>
#include <memory>


std::shared_ptr<outputCMD> output = std::make_shared<outputCMD>();
std::shared_ptr<LoggerManager> logInFiles = std::make_shared<LoggerManager>();

namespace async {
    handle_t connect(std::size_t bulk) {
        auto * cmd = new CMD(bulk);
        cmd->subscribe(output);
        cmd->subscribe(logInFiles);
        return static_cast<void *>(cmd);

        return nullptr;
    }

    void receive(handle_t handle, [[maybe_unused]] const char *data, [[maybe_unused]] std::size_t size) {
        auto cmdHandle = static_cast<CMD*>(handle);
        auto l = std::async(std::launch::async,
            &CMD::inputControlAsync, cmdHandle, data);
        l.get();
    }

    void disconnect(handle_t handle) {
        auto cmdHandle = static_cast<CMD*>(handle);
        cmdHandle->unsubscribe();
    }

}
