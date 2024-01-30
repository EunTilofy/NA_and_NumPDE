/******************************************************
 * Ver 3.0 updated on Jan. 27th, 2024, by EunTilofy
 * execute code from a string, only support one param as input.
 * make sure the input param has only one character, like, a, A, x, y.
 * ex. REGISTER_FUNTION_FROM_STRING2(f, "x + x", double, double)
 *                                 name function XType  YType
 * usage. f(1) -> 2, f(2) -> 4
 * 
 * 2d - function
 * ex. REGISTER_FUNTION_FROM_STRING2(f, "x + y", double, double)
 *                                 name function XType  YType
 * usage. f(1，2) -> 3, f(2，2) -> 4
*******************************************************/
#ifndef EXEC_CODE_2
#define EXEC_CODE_2

#include <bits/stdc++.h>
using namespace std;

const std::string _func[] = {
    "", "exp", "sin", "cos", "tan", "pow", "sqrt", "abs", "fabs", "floor", "ceil", "min", "max", "log", "log10",
    /*0    1      2      3      4      5      6       7      8       9        10      11     12     13     14*/
    "+", "-", "*", "/", "+(pos)", "-(neg)"
    /*15  16   17   18   19        20*/
};

template<class Xtype, class Ytype = Xtype>
class FromString {
    string str;
    int len;
    bool _is_built{};
    std::vector<pair<int, std::pair<int,int>>> nodes;
    std::vector<Ytype> num;
    int cnt;
    pair<int, std::pair<int,int>> newnode() const { return {-1, {-1, -1}}; }
    int check_cmath_func(int l, int r) {
        for(int res = 1; res <= 14; ++res) {
            if(r - l + 1 >= _func[res].size() && str.substr(l, _func[res].size()) == _func[res]) {
                for(int i = l + _func[res].size() + 1, layer = 1; i <= r; ++i) {
                    if(str[i] == '(') ++ layer;
                    else if(str[i] == ')') {
                        if(-- layer == 0) {
                            if(i == r) return res;
                            else break;
                        } 
                    }
                }
            }
        }
        return 0;
    }
    vector<string> par_set;
    map<string, int> par_map; int npar;
    void check(int k, int l, int r) {
        // cerr << k << " " << l << " " << r << " " << str.substr(l, r-l+1) << std::endl;
        while(str[l] == '(' && str[r] == ')') ++l, --r;
        int _ = 0;
        for(int i = l, layer = 0; i <= r; ++i) {
            if(str[i] == '(') ++layer;
            if(str[i] == ')') --layer;
            _ = min(_, layer);
        }
        l += _; r -= _;
        /* check leaf */
        bool fln = 1, fll = 1;
        for(int i = l; i <= r; ++i) fln &= isdigit(str[i]) | str[i] == '.', fll &= isalpha(str[i]) | isdigit(str[i]);
        if(fln) {
            try {
                num.push_back((Ytype)std::stold(str.substr(l, r - l + 1)));
                nodes[k].first = num.size() - 1;
            } catch (const std::exception& e) {
                std::cerr << "parse number " <<  str.substr(l, r - l + 1) << " failed." << std::endl;
                throw "parse failed";
            }
            return ;
        }
        if(fll) {
            string par = str.substr(l, r - l + 1);
            if(!par_map[par]) par_map[par] = ++npar, par_set.push_back(par);
            nodes[k].first = -par_map[par];
            return ;
        }
        /* check cmath function */
        int res = check_cmath_func(l, r);
        if(res) {
            nodes[k].first = res;
            int layer = 0;
            int ls = -1, rs = -1, sl = l + _func[res].size() + 1, sr = r - 1;
            ls = ++cnt; nodes.push_back(newnode());
            for(int i = l; i <= r; ++i) {
                if(str[i] == '(') ++layer;
                if(str[i] == ')') --layer;
                if(str[i] == ',' && layer == 1) {
                    rs = ++cnt; nodes.push_back(newnode());
                    check(ls, sl, i - 1);
                    check(rs, i + 1, sr);
                    break;
                }
            }
            if(rs == -1) check(ls, sl, sr);
            nodes[k].second = {ls, rs};
        }
        /* otherwise */
        if(str[l] == '-' || str[l] == '+') {
            bool fl = 1;
            for(int i = l + 1, layer = 0; i <= r; ++i) {
                if(str[i] == '(') ++ layer;
                if(str[i] == ')') -- layer;
                if(layer == 0 && (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/')) {
                    fl = 0; break;
                }
            }
            if(fl) {
                int ls = ++cnt;
                nodes[k] = {19 + (str[l] == '-'), {ls, -1}};
                nodes.push_back(newnode());
                check(ls, l + 1, r);
                return ;
            }
        }
        for(int i = r, layer = 0; i > l; --i) {
            if(str[i] == '(') ++ layer;
            if(str[i] == ')') -- layer;
            if(layer == 0 && (str[i] == '-' || str[i] == '+')) {
                int ls = ++cnt, rs = ++cnt;
                nodes.push_back(newnode());
                nodes.push_back(newnode());
                nodes[k] = {15 + (str[i] == '-'), {ls, rs}};
                check(ls, l, i - 1);
                check(rs, i + 1, r);
                return;
            }
        }
        for(int i = r, layer = 0; i > l; --i) {
            if(str[i] == '(') ++ layer;
            if(str[i] == ')') -- layer;
            if(layer == 0 && (str[i] == '*' || str[i] == '/')) {
                int ls = ++cnt, rs = ++cnt;
                nodes.push_back(newnode());
                nodes.push_back(newnode());
                nodes[k] = {17 + (str[i] == '/'), {ls, rs}};
                check(ls, l, i - 1);
                check(rs, i + 1, r);
                return;
            }
        }
    }
    void build() {
        if(_is_built) return;
        /*  remove blanks  */
        string tmp = "";
        for(int i = 0; i < str.size(); ++i) if(str[i] != ' ') tmp = tmp + str[i];
        str = tmp; len = str.size();
        nodes[1] = newnode();
        check(1, 0, len - 1);
        _is_built = 1;
    }
    Ytype cal_dfs(int k, const vector<Xtype>& par) const {
        // cerr << k << " " << nodes[k].first << " " << nodes[k].second.first << " " << nodes[k].second.second << std::endl;
        if(nodes[k].second.first == -1 && nodes[k].second.second == -1) {
            if(nodes[k].first < 0) { return par[-nodes[k].first-1]; }
            else {return num[nodes[k].first];}
        }
        switch (nodes[k].first)
        {
            case 1:  return exp(cal_dfs(nodes[k].second.first, par)); break;
            case 2:  return sin(cal_dfs(nodes[k].second.first, par)); break;
            case 3:  return cos(cal_dfs(nodes[k].second.first, par)); break;
            case 4:  return tan(cal_dfs(nodes[k].second.first, par)); break;
            case 6:  return sqrt(cal_dfs(nodes[k].second.first, par)); break;
            case 7:  return abs(cal_dfs(nodes[k].second.first, par)); break;
            case 8:  return fabs(cal_dfs(nodes[k].second.first, par)); break;
            case 9:  return floor(cal_dfs(nodes[k].second.first, par)); break;
            case 10: return ceil(cal_dfs(nodes[k].second.first, par)); break;
            case 13: return log(cal_dfs(nodes[k].second.first, par)); break;
            case 14: return log10(cal_dfs(nodes[k].second.first, par)); break;
            case 19: return (cal_dfs(nodes[k].second.first, par)); break;
            case 20: return -(cal_dfs(nodes[k].second.first, par)); break;
            case 5:  return pow(cal_dfs(nodes[k].second.first, par), cal_dfs(nodes[k].second.second, par)); break;
            case 11: return min(cal_dfs(nodes[k].second.first, par), cal_dfs(nodes[k].second.second, par)); break;
            case 12: return max(cal_dfs(nodes[k].second.first, par), cal_dfs(nodes[k].second.second, par)); break;
            case 15: return (cal_dfs(nodes[k].second.first, par) + cal_dfs(nodes[k].second.second, par)); break;
            case 16: return (cal_dfs(nodes[k].second.first, par) - cal_dfs(nodes[k].second.second, par)); break;
            case 17: return (cal_dfs(nodes[k].second.first, par) * cal_dfs(nodes[k].second.second, par)); break;
            case 18: return (cal_dfs(nodes[k].second.first, par) / cal_dfs(nodes[k].second.second, par)); break;
            default: return 0;
        }
        return 0;
    }
public:
    FromString() : _is_built(0) {}
    FromString(const string& _str) : str(_str), _is_built(0), cnt(1), nodes(2),
                                     num(0), par_set(0), par_map(), npar(0) { build(); }
    Ytype cal(const Xtype& x) const {
        return cal_dfs(/* root */1, {x});
    }
    Ytype cal2(const map<string, Xtype>& pars) const {
        vector<Xtype> par_val;
        for(int i = 0; i < npar; ++i) par_val.push_back(pars.at(par_set[i]));
        return cal_dfs(/* root */1, par_val);
    }
};

#define REGISTER_FUNCTION_FROM_STRING2(name, str, Xtype, Ytype) \
    class _fUnCtIoN_##name : public Function<Xtype, Ytype> { \
        FromString<Xtype, Ytype> getvalue; \
    public: \
        _fUnCtIoN_##name(const std::string _str) : getvalue(_str) {} \
        Ytype operator() (const Xtype &x) const { \
            Xtype xx = x; return getvalue.cal(x); \
        } \
    }; \
    _fUnCtIoN_##name name(str); \

#define REGISTER_FUNCTION_FROM_STRING_2d(name, str, Xtype, Ytype) \
    class _fUnCtIoN_##name : public Function2D<Xtype, Ytype> { \
        FromString<Xtype, Ytype> getvalue; \
    public: \
        _fUnCtIoN_##name(const std::string _str) : getvalue(_str) {} \
        Ytype operator() (const Xtype &x, const Ytype &y) const { \
            Xtype xx = x, yy = y; return getvalue.cal2({{"x", xx}, {"y", yy}}); \
        } \
    }; \
    _fUnCtIoN_##name name(str); \

#endif