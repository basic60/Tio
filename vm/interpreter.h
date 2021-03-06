#ifndef __TIOVM_INTERPRETER
#define __TIOVM_INTERPRETER
#include"mmu.h"
#include<queue>
#include<unordered_map>
#include<functional>
#include<stack>
#include"reg.h"
namespace tiovm
{
    struct Command {
        std::string name;
        int vsize;

        static Command parse_cmd(const std::string& cmd);
    };

    struct Operand {
        enum class opd_type {
            reg,
            number
        };

        opd_type type;
        std::string raw_val;
        static Operand parse_operand(const std::string& val);
    };

    struct Instruction {
        Command cmd;
        Operand opl;
        Operand opr;
        int op_cnt;
        bool laddr;
        bool raddr;
        std::string raw_command;
    };

    class Interpreter {
    private:
        MMU mmu;
        std::unordered_map<std::string, Register> regs;
        std::vector<Instruction> instructions;
        std::unordered_map<std::string, std::function<bool(int)>> jmp_judge;
        int64 entry_point;

        void pre_process(std::string fname);
        int64 get_operand_val(const Operand& op, bool addr);
    public:
        Interpreter();
        void execute(std::string fname);
    };
}
#endif