#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>

using boost::iequals;
using std::cout, std::cin, std::endl, std::string, std::vector;

const int smlHP = 44;
const int smlSpe = 56;
const int avgHP = 49;
const int avgSpe = 51;
const int lrgHP = 54;
const int lrgSpe = 46;
const int supHP = 59;
const int supSpe = 41;

const vector<int> ivBest = {31};
const vector<int> ivFantastic = {30};
const vector<int> ivVeryGood = {29, 28, 27, 26};
const vector<int> ivPrettyGood = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16};
const vector<int> ivDecent = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
const vector<int> ivNoGood = {0};

void RunCalc() {

    auto isNumber = [](const string& str) {
        return std::ranges::all_of(str.begin(), str.end(), [](char c) { return isdigit(c) != 0; });
    };

    string input;
    do {
        int level;
        int hp_total;
        int spe_total;
        float nature;
        vector<int> hp_ivs;
        vector<int> spe_ivs;
        cout << "enter 'exit' to exit." << endl;
    LEVEL:
        cout << "Enter level." << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!isNumber(input)) {
            cout << "Invalid input." << endl;
            goto LEVEL;
        }
        level = std::stoi(input);
    HP:
        cout << "Enter HP stat." << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!isNumber(input)) {
            cout << "Invalid input." << endl;
            goto HP;
        }
        hp_total = std::stoi(input);
    SPE:
        cout << "Enter Spe stat." << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!isNumber(input)) {
            cout << "Invalid input." << endl;
            goto SPE;
        }
        spe_total = std::stoi(input);
    NATURE:
        cout << "Helping or Hinding Spe Nature? [+/-/No]" << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!(iequals(input, "+") || iequals(input, "-") || iequals(input, "No"))) {
            cout << "Invalid input." << endl;
            goto NATURE;
        }
        if(input.at(0) == '+')
            nature = 1.1;
        else if(input.at(0) == '-')
            nature = 0.9;
        else
            nature = 1.0;
    HPIV:
        cout << "Enter HP IV range/stat. (best, fantastic, verygood, prettygood, decent, nogood, [0-31])" << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!isNumber(input) &&
           !(iequals(input, "best") || iequals(input, "fantastic") || iequals(input, "verygood") ||
             iequals(input, "prettygood") || iequals(input, "decent") || iequals(input, "nogood"))) {
            cout << "Invalid input." << endl;
            goto HPIV;
        }
        if(isNumber(input))
            hp_ivs = {std::stoi(input)};
        else {
            if(iequals(input, "best"))
                hp_ivs = ivBest;
            else if(iequals(input, "fantastic"))
                hp_ivs = ivFantastic;
            else if(iequals(input, "verygood"))
                hp_ivs = ivVeryGood;
            else if(iequals(input, "prettygood"))
                hp_ivs = ivPrettyGood;
            else if(iequals(input, "decent"))
                hp_ivs = ivDecent;
            else if(iequals(input, "nogood"))
                hp_ivs = ivNoGood;
            else {
                cout << "Invalid input." << endl;
                goto HPIV;
            }
        }

    SPEIV:
        cout << "Enter Speed IV range/stat. (best, fantastic, verygood, prettygood, decent, nogood, [0-31])" << endl;
        cin >> input;
        if(iequals(input, "exit")) return;
        if(!isNumber(input) &&
           !(iequals(input, "best") || iequals(input, "fantastic") || iequals(input, "verygood") ||
             iequals(input, "prettygood") || iequals(input, "decent") || iequals(input, "nogood"))) {
            cout << "Invalid input." << endl;
            goto SPEIV;
        }
        if(isNumber(input))
            spe_ivs = {std::stoi(input)};
        else {
            if(iequals(input, "best"))
                spe_ivs = ivBest;
            else if(iequals(input, "fantastic"))
                spe_ivs = ivFantastic;
            else if(iequals(input, "verygood"))
                spe_ivs = ivVeryGood;
            else if(iequals(input, "prettygood"))
                spe_ivs = ivPrettyGood;
            else if(iequals(input, "decent"))
                spe_ivs = ivDecent;
            else if(iequals(input, "nogood"))
                spe_ivs = ivNoGood;
            else {
                cout << "Invalid input." << endl;
                goto SPEIV;
            }
        }

        // hp formula    HP = Math.floor((2 * basestat + ivstat + ev/4 ) * level / 100) + level + 10
        // stat formula  stat = Math.floor((2 * basestat + ivstat + ev/4 ) * level / 100) + level + 10

        // check small pumpkaboo
        // hp 44 spe 56
        int smlCount = 0, hpcount = 0, specount = 0;
        for(int hp_iv : hp_ivs) {
            if(std::floor(((2 * smlHP + hp_iv) * level) / 100) + level + 10 == hp_total) ++hpcount;
        }
        for(int spe_iv : spe_ivs) {
            if(std::floor((std::floor(((2 * smlSpe + spe_iv) * level) / 100) + 5) * nature) == spe_total) ++specount;
        }
        smlCount = hpcount * specount;

        int avgCount = 0;
        hpcount = 0;
        specount = 0;
        for(int hp_iv : hp_ivs) {
            if(std::floor(((2 * avgHP + hp_iv) * level) / 100) + level + 10 == hp_total) ++hpcount;
        }
        for(int spe_iv : spe_ivs) {
            if(std::floor((std::floor(((2 * avgSpe + spe_iv) * level) / 100) + 5) * nature) == spe_total) ++specount;
        }
        avgCount = hpcount * specount;

        int lrgCount = 0;
        hpcount = 0;
        specount = 0;
        for(int hp_iv : hp_ivs) {
            if(std::floor(((2 * lrgHP + hp_iv) * level) / 100) + level + 10 == hp_total) ++hpcount;
        }
        for(int spe_iv : spe_ivs) {
            if(std::floor((std::floor(((2 * lrgSpe + spe_iv) * level) / 100) + 5) * nature) == spe_total) ++specount;
        }
        lrgCount = hpcount * specount;

        int supCount = 0;
        hpcount = 0;
        specount = 0;
        for(int hp_iv : hp_ivs) {
            if(std::floor(((2 * supHP + hp_iv) * level) / 100) + level + 10 == hp_total) ++hpcount;
        }
        for(int spe_iv : spe_ivs) {
            if(std::floor((std::floor(((2 * supSpe + spe_iv) * level) / 100) + 5) * nature) == spe_total) ++specount;
        }
        supCount = hpcount * specount;

        float totalCount = smlCount + avgCount + lrgCount + supCount;
        cout << "found " << int(totalCount) << " possible" << endl;
        if(smlCount / totalCount != 0) cout << "Small: " << (smlCount / totalCount) * 100 << "% confidence" << endl;
        if(avgCount / totalCount != 0) cout << "Average: " << (avgCount / totalCount) * 100 << "% confidence" << endl;
        if(lrgCount / totalCount != 0) cout << "Large: " << (lrgCount / totalCount) * 100 << "% confidence" << endl;
        if(supCount / totalCount != 0) cout << "Super: " << (supCount / totalCount) * 100 << "% confidence" << endl;

        cout << "'continue' to continue or 'exit' to exit" << endl;
        cin >> input;

    } while(!iequals(input, "exit"));
}

int main() {
    RunCalc();
}