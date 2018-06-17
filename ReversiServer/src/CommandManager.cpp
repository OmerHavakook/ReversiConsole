
#include "../include/CommandManager.h"

CommandManager *CommandManager::instance = 0;
pthread_mutex_t CommandManager::lock;

CommandManager::CommandManager() {
    // for each key (start,list,join an close) sets (by creating) the
    // matches object as the value in the map
    commands_map["start"] = new StartCommand();
    commands_map["list"] = new ListCommand();
    commands_map["close"] = new CloseCommand();
    commands_map["join"] = new JoinCommand();
}

CommandManager::~CommandManager() {
    // delete all of the values in the map
    map<string, Command *>::iterator it;
    for (it = commands_map.begin(); it != commands_map.end(); it++) {
        delete it->second;
    }
}

void CommandManager::executeCommand(string command, vector<string> args,
                                    int clientSocket) {
    // save in commandObj the right object (by using the map)
    Command *command_obj = commands_map[command];
    // call execute
    command_obj->execute(args, clientSocket);
}

CommandManager *CommandManager::getInstance() {
    // check if it's the first time to get into this method
    if (instance == 0) {
        // lock
        pthread_mutex_lock(&lock);
        // check if this is the first time to get into this method
        if (instance == 0) {
            instance = new CommandManager();
        }
        pthread_mutex_unlock(&lock);
    }
    // return the instance
    return instance;
}