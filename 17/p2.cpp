#include <iostream>
#include <vector>
#include <cmath>
#include <ranges>
#include <set>

using namespace std;

struct Machine {

    int64_t A, B, C;
    int programCounter = 0;
    vector<int> program;
    string output;

    void execute(int instruction, int literal) {
        int64_t combo = comboOperand(literal);
        switch(instruction) {
            case 0: // adv
                A = A >> combo;
                break;
            case 1: // bxl
                B = B ^ literal;
                break;
            case 2: // bst
                B = combo % 8;
                break;
            case 3: // jnz
                if(A) 
                    programCounter = literal - 2;
                break;
            case 4: // bxc
                B = B ^ C;
                break;
            case 5: // out
                if(!output.empty()) 
                    output += ',';
                output += to_string(combo % 8);
                break;
            case 6: // bdv
                B = A >> combo;
                break;
            case 7: // cdv
                C = A >> combo;
                break;
        }
    }

    void run() {
        programCounter = 0;
        output.clear();
        while(programCounter != program.size()) {
            execute(
                program[programCounter],
                program[programCounter+1]
            );
            programCounter += 2;
        }
    }

    int64_t comboOperand(int operand) {
        switch(operand) {
            case 4:  return A;
            case 5:  return B;
            case 6:  return C;
            default: return operand;
        }
    }
};

int main() {
    string tmpStr, programStr;
    Machine machine;

    int A, B, C;

    cin >> tmpStr >> tmpStr >> A;
    cin >> tmpStr >> tmpStr >> B;
    cin >> tmpStr >> tmpStr >> C;
    cin >> tmpStr >> programStr;

    machine.program = 
        programStr |
        views::split(',') |
        views::transform([](auto s) -> int { 
            return stoi(string(s.begin(), s.end())); 
        }) |
        ranges::to<vector>();

    set<int64_t> candidates = {0};

    for(int instr = machine.program.size()-1; instr >= 0; instr--) {
        string target = programStr.substr(instr*2);
        set<int64_t> newCandidates;
        for(int64_t candidate : candidates) {
            for(int i = 0; i < 8; i++) {
                int64_t n = (candidate << 3) + i;
                machine.A = n;
                machine.B = B;
                machine.C = C;
                machine.run();
                cout << "Output for A=" << n << " is " << machine.output << endl;
                if(machine.output == target) {
                    newCandidates.insert(n);
                }
            }
        }
        candidates.swap(newCandidates);
    }

    cout << *candidates.begin() << endl;

    return 0;
}
