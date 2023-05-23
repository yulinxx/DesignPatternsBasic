// 来源于ChatGPT 未修改
// 当纪录达到一定值,应删除添加的命令


#include <iostream>
#include <stack>

// 命令基类
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// 具体命令类
class ConcreteCommand : public Command {
private:
    std::string m_action;

public:
    ConcreteCommand(const std::string& action) : m_action(action) {}

    void execute() override {
        std::cout << "执行命令: " << m_action << std::endl;
    }

    void undo() override {
        std::cout << "撤销命令: " << m_action << std::endl;
    }
};

// 命令管理器类
class CommandManager {
private:
    std::stack<Command*> m_undoStack;
    std::stack<Command*> m_redoStack;

public:
    void executeCommand(Command* command) {
        command->execute();
        m_undoStack.push(command);
        // 每次执行新的命令时，清空重做栈
        while (!m_redoStack.empty()) {
            delete m_redoStack.top();
            m_redoStack.pop();
        }
    }

    void undo() {
        if (!m_undoStack.empty()) {
            Command* command = m_undoStack.top();
            command->undo();
            m_undoStack.pop();
            m_redoStack.push(command);
        }
    }

    void redo() {
        if (!m_redoStack.empty()) {
            Command* command = m_redoStack.top();
            command->execute();
            m_redoStack.pop();
            m_undoStack.push(command);
        }
    }
};

int main() {
    CommandManager manager;

    // 创建具体命令对象
    Command* cmd1 = new ConcreteCommand("操作1");
    Command* cmd2 = new ConcreteCommand("操作2");
    Command* cmd3 = new ConcreteCommand("操作3");

    // 执行命令
    manager.executeCommand(cmd1);
    manager.executeCommand(cmd2);
    manager.executeCommand(cmd3);

    // 撤销操作
    manager.undo();
    manager.undo();

    // 重做操作
    manager.redo();

    delete cmd1;
    delete cmd2;
    delete cmd3;

    return 0;
}





// #include <iostream>
// #include <vector>

// // 命令接口
// class Command {
// public:
//     virtual ~Command() {}
//     virtual void execute() = 0;
//     virtual void undo() = 0;
// };

// // 具体命令类
// class ConcreteCommand : public Command {
// public:
//     ConcreteCommand(int& value, int newValue)
//         : value_(value), oldValue_(value) {
//         value_ = newValue;
//     }

//     void execute() override {
//         std::cout << "执行操作，新值为: " << value_ << std::endl;
//     }

//     void undo() override {
//         value_ = oldValue_;
//         std::cout << "撤销操作，恢复到原值: " << value_ << std::endl;
//     }

// private:
//     int& value_;
//     int oldValue_;
// };

// // 命令历史记录类
// class CommandHistory {
// public:
//     void addCommand(Command* command) {
//         commands_.push_back(command);
//     }

//     void undo() {
//         if (!commands_.empty()) {
//             Command* command = commands_.back();
//             commands_.pop_back();
//             command->undo();
//             delete command;
//         }
//     }

//     void redo() {
//         // 未实现 redo 操作的示例
//         std::cout << "Redo 操作未实现" << std::endl;
//     }

// private:
//     std::vector<Command*> commands_;
// };

// int main() {
//     int value = 0;
//     CommandHistory history;

//     // 执行一系列命令
//     history.addCommand(new ConcreteCommand(value, 10));
//     history.addCommand(new ConcreteCommand(value, 20));
//     history.addCommand(new ConcreteCommand(value, 30));
//     history.addCommand(new ConcreteCommand(value, 40));

//     // 撤销操作
//     history.undo(); // 恢复到30
//     history.undo(); // 恢复到20

//     // 重做操作
//     history.redo(); // 输出"Redo 操作未实现"

//     return 0;
// }



////////////////////////////////////////////////

// #include <iostream>
// #include <vector>

// // 命令基类
// class Command {
// public:
//     virtual ~Command() {}
//     virtual void Execute() = 0;
//     virtual void Undo() = 0;
// };

// // 具体命令类
// class ConcreteCommand : public Command {
// public:
//     ConcreteCommand() : m_value(0) {}
    
//     void Execute() override {
//         // 执行操作
//         std::cout << "执行操作: " << m_value << std::endl;
//     }
    
//     void Undo() override {
//         // 撤销操作
//         std::cout << "撤销操作: " << m_value << std::endl;
//     }
    
//     void SetValue(int value) {
//         m_value = value;
//     }
    
// private:
//     int m_value;
// };

// // 命令管理器
// class CommandManager {
// public:
//     void ExecuteCommand(Command* command) {
//         // 执行命令
//         command->Execute();
//         // 将命令添加到历史记录
//         m_history.push_back(command);
//         // 清空重做记录
//         m_redoStack.clear();
//     }
    
//     void UndoCommand() {
//         if (!m_history.empty()) {
//             // 从历史记录中取出最后一个命令并撤销
//             Command* command = m_history.back();
//             command->Undo();
//             // 将命令添加到重做记录
//             m_redoStack.push_back(command);
//             // 从历史记录中移除
//             m_history.pop_back();
//         }
//     }
    
//     void RedoCommand() {
//         if (!m_redoStack.empty()) {
//             // 从重做记录中取出最后一个命令并执行
//             Command* command = m_redoStack.back();
//             command->Execute();
//             // 将命令添加回历史记录
//             m_history.push_back(command);
//             // 从重做记录中移除
//             m_redoStack.pop_back();
//         }
//     }
    
// private:
//     std::vector<Command*> m_history;   // 命令历史记录
//     std::vector<Command*> m_redoStack; // 重做记录
// };

// int main() {
//     CommandManager commandManager;
    
//     // 创建命令并设置值
//     ConcreteCommand* command1 = new ConcreteCommand();
//     command1->SetValue(10);
    
//     ConcreteCommand* command2 = new ConcreteCommand();
//     command2->SetValue(20);
    
//     ConcreteCommand* command3 = new ConcreteCommand();
//     command3->SetValue(30);
    
//     // 执行命令
//     commandManager.ExecuteCommand(command1);
//     commandManager.ExecuteCommand(command2);
//     commandManager.ExecuteCommand(command3);
    
//     // 撤销命令
//     commandManager.UndoCommand();
//     commandManager.UndoCommand();
    
//     // 重做命令
//     commandManager.RedoCommand();
    
//     // 释放命令对象的内存
//     delete command1;
//     delete command2;
//     delete command3;
    
//     return 0;
// }
