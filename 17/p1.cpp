#include <iostream>
#include <vector>
#include <cmath>
#include <ranges>

using namespace std;

struct Machine {

    int A, B, C;
    int programCounter = 0;
    vector<int> program;
    string output;

    void execute(int instruction, int literal) {
        int combo = comboOperand(literal);
        switch(instruction) {
            case 0: // adv
                A = A / pow(2, combo);
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
                B = A / pow(2, combo);
                break;
            case 7: // cdv
                C = A / pow(2, combo);
                break;
        }
    }

    void run() {
        while(programCounter != program.size()) {
            execute(
                program[programCounter],
                program[programCounter+1]
            );
            programCounter += 2;
        }
    }

    int comboOperand(int operand) {
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

    cin >> tmpStr >> tmpStr >> machine.A;
    cin >> tmpStr >> tmpStr >> machine.B;
    cin >> tmpStr >> tmpStr >> machine.C;
    cin >> tmpStr >> programStr;

    machine.program = 
        programStr |
        views::split(',') |
        views::transform([](auto s) -> int { 
            return stoi(string(s.begin(), s.end())); 
        }) |
        ranges::to<vector>();

    machine.run();
    cout << machine.output << endl;

    return 0;
}
