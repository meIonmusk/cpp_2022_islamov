#include <iostream>

uint32_t get_results(uint32_t channel)
{
    static uint32_t calls = 0;
    calls++;
    if (calls > 25) return static_cast<uint32_t>(-1);

    static uint32_t min = 10, max = 255760;
    static uint32_t min_channel = 50, max_channel = 40;
    static uint32_t zero = 10000;

    if (channel == 0)
        return zero;
    if (channel <= max_channel)
        return static_cast<uint32_t>(zero + channel*(max - (double)zero)/max_channel);
    if (channel <= min_channel)
        return static_cast<uint32_t>(max - ((double)channel - max_channel)*((double)max - min)/((double)min_channel - max_channel));
    if (channel <= 360)
        return static_cast<uint32_t>(min + ((double)channel - min_channel)*((double)zero - min)/((double)360 - min_channel));

//    if (channel <= min_channel)
//        return static_cast<uint32_t>(zero - channel*((double)zero - min)/min_channel);
//    if (channel <= max_channel)
//        return static_cast<uint32_t>(min + ((double)channel - min_channel)*((double)max - min)/((double)max_channel - min_channel));
//    if (channel <= 360)
//        return static_cast<uint32_t>(max - ((double)channel - max_channel)*((double)max - zero)/((double)360 - max_channel));
    return static_cast<uint32_t>(-1);
}


void detect(){
    unsigned dx = 45;
    unsigned lch = 0;
    unsigned mch = dx;
    unsigned rch = 360;
    uint32_t lres;
    uint32_t mres;
    uint32_t rres;
    uint32_t lres_;
    uint32_t mres_;
    uint32_t rres_;
    lres = get_results(lch);

    mres = get_results(mch);

    rres = lres;
    lres_ = lres;
    mres_ = mres;

    unsigned idx = lch + 2 * dx;
    while (true){
        rres_ = (idx == rch) ? rres : (idx == lch) ? lres : (idx == mch) ? mres : get_results(idx % 360);
//        std::cout << idx << ' ' << rres_ << '\n';
        if (rres_ <= mres_ and lres_ < mres_) {
            lch = (idx - 2 * dx) % 360;
            mch = (idx - dx) % 360;
            rch = idx % 360;
            mres = mres_;
            rres = rres_;
            lres = lres_;
            break;
        }
        lres_ = mres_;
        mres_ = rres_;
        idx += dx;
    }

//    std::cout << '\n' << lch << ' ' << mch << ' ' << rch << "\n\n";

    dx = 10;
    lres_ = lres;
    mres_ = get_results(lch + dx);
    if (rch == 0)
        rch = 360;
    for (unsigned idx = lch + 2 * dx; idx <= rch; idx += dx){
        rres_ = (idx == rch) ? rres : get_results(idx % 360);
//        std::cout << idx << ' ' << rres_ << '\n';
        if (rres_ <= mres_ and lres_ < mres_) {
            lch = (idx - 2 * dx) % 360;
            mch = (idx - dx) % 360;
            rch = idx % 360;
            mres = mres_;
            rres = rres_;
            lres = lres_;
            break;
        }
        lres_ = mres_;
        mres_ = rres_;
    }
    if (rch == 0)
        rch = 360;
//    std::cout << '\n' << lch << ' ' << mch << ' ' << rch << "\n\n";

    dx = 4;
    lres_ = lres;
    mres_ = get_results(lch + dx);

    for (unsigned idx = lch + 2 * dx; idx <= rch; idx += dx){
        rres_ = (idx == rch) ? rres : get_results(idx % 360);
//        std::cout << idx << ' ' << rres_ << '\n';
        if (rres_ <= mres_ and lres_ < mres_) {
            lch = (idx - 2 * dx) % 360;
            mch = (idx - dx) % 360;
            rch = idx % 360;
            mres = mres_;
            rres = rres_;
            lres = lres_;
            break;
        }
        lres_ = mres_;
        mres_ = rres_;
    }
    if (rch == 0)
        rch = 360;
//    std::cout << '\n' << lch << ' ' << mch << ' ' << rch << "\n\n";


    dx = 2;
    lres_ = lres;
    mres_ = get_results(lch + dx);

    for (unsigned idx = lch + 2 * dx; idx <= rch; idx += dx){
        rres_ = (idx == rch) ? rres : get_results(idx % 360);
//        std::cout << idx << ' ' << rres_ << '\n';
        if (rres_ <= mres_ and lres_ < mres_) {
            lch = (idx - 2 * dx) % 360;
            mch = (idx - dx) % 360;
            rch = idx % 360;
            mres = mres_;
            rres = rres_;
            lres = lres_;
            break;
        }
        lres_ = mres_;
        mres_ = rres_;
    }
    if (rch == 0)
        rch = 360;

//    std::cout << '\n' << lch << ' ' << mch << ' ' << rch << "\n\n";

    dx = 1;
    lres_ = lres;
    mres_ = get_results(lch + dx);

    for (unsigned idx = lch + 2 * dx; idx <= rch; idx += dx){
        rres_ = (idx == rch) ? rres : (idx == mch) ? mres : get_results(idx % 360);
//        std::cout << idx << ' ' << rres_ << '\n';
        if (rres_ <= mres_ and lres_ < mres_) {
            lch = (idx - 2 * dx) % 360;
            mch = (idx - dx) % 360;
            rch = idx % 360;
            mres = mres_;
            rres = rres_;
            lres = lres_;
            break;
        }
        lres_ = mres_;
        mres_ = rres_;
    }

//    std::cout << '\n' << lch << ' ' << mch << ' ' << rch << "\n\n" << lres << ' ' << mres << ' ' << rres;
    std::cout << mres << ' ' << mch;
}

int main() {
//    for (uint32_t i = 0; i < 30; i++)
//        std::cout << get_results(i) << '\n';
    detect();
    return 0;
}