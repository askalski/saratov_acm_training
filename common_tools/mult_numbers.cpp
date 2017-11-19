//this is useful if you only need to calculate Newton's symols and multiply
//large numbers, but expect constrained results.

class mult_number : public map<int, int> {
private:
#define max_factor_plus_one 1000001
    static int divisor[max_factor_plus_one];
    static bool built = false;
    void build_divisors() {
        if(built) return;
        int root = sqrt(max_factor_plus_one);
        for(int i = 1; i <= 100; ++i) {
            bool done = false;
            for(int d = 2; d <= root; ++d) {
                if(i % d == 0) {
                    divisor[i] = d;
                    done = true;
                }
            }
            if(!done) {
                divisor[i] = i;
            }
        }
        built = true;
    }

public:
    void operator*=(const map<int, int> &b) {
        for(const auto i : b) {
            (*this)[i.first] += i.second;
        }
    }

    void operator*=(int number) {
        if(number == 1) return;
        while(number != 1) {
            (*this)[divisor[number]]++;
            number /= divisor[number];
        }
    }

    void operator=(const int &number) {
        assert(number < max_factor_plus_one);
        assert(number > 0); //zero is not supported by this representation.
        if(!this->empty()) this->clear();
        (*this)*=number;
    }
};
