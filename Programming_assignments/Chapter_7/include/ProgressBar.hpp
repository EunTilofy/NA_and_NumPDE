/**
 * @file ProgressBar.hpp
 * @author EunTilofy (papercloud@zju.edu.cn)
 * @brief a mini Progress Bar for program, with tips below it.
 *        usage. ProgressBar a(name); a.updateProgress(num);
 * @version 1.0
 * @date 2024-01-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _PROGRESS_BAR_
#define _PROGRESS_BAR_

#include <bits/stdc++.h>

class ProgressBar{
    std::string Name;
    std::vector<std::string> tips;
    int pro;
    double timestart;
    int last;
    bool beg, showtips;
    bool show;
    void showProgress() {
        if(!show) return ;
        if(!beg) { beg = 1; begin(); }
        for(int i = 0; i < last; ++i) std::cerr << "\33[1A";
        std::cerr << "\033[J";
        std::cerr << std::unitbuf << Name << " : " << 
            "[" + std::string(pro/2, '=') + ">" + std::string(50 - pro/2, ' ') << "]" << pro << "%" << std::endl;
        last = 0;
        if(showtips) {
            for(auto tip : tips) std::cerr << std::unitbuf << tip << std::endl, ++last;
        }
        ++last;
        fflush(stdout);
    }
public:
    ProgressBar(std::string _name, bool _beg = 0, bool _sh = 1, bool _ = 1) : 
        Name(_name), pro(0), tips(0), last(0), beg(_beg), showtips(_sh), show(_){
        if(_beg) begin();
    }
    void begin() {
        timestart = clock();
    }
    void end() {
        if(!show) return ;
        double _ = (clock()-timestart)/(double)CLOCKS_PER_SEC;
        // for(int i = 0; i < last - 1; ++i) std::cerr << "\33[1A"; std::cerr << "\033[J";
        last = min(1, last);
        std::cerr << Name << " cost " << std::fixed << std::setprecision(3) << _ << " sec.\033[J";
        std::cerr << std::endl;
        ++last;
    }
    void updateProgress(int _pro) {
        pro = std::min(100, _pro);
        showProgress();
        if(pro == 100) end();
    }
    void addTip(std::string tip) {
        tips.push_back(tip);
        showProgress();
    }
    void clearTip() { tips.clear(); showProgress(); }
    std::string popTip(std::string tip) {
        if(tips.size() == 0) return "";
        std::string ret = tips.back();
        tips.pop_back();
        showProgress();
        return ret;
    }
    void updateTip(std::string tip) {
        if(tips.size()) tips.pop_back();
        tips.push_back(tip);
        showProgress();
    }
};

#endif