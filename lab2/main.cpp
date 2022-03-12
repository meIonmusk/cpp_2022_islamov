#include <iostream>
#include <iomanip>
#include <cmath>

float recurrent_sum(float const psi[], float const pdf[], float const dv, unsigned ldx, unsigned rdx){
    auto ldx_ = ldx + (rdx - ldx) / 2;
    return (rdx - ldx)?
    recurrent_sum(psi, pdf, dv, ldx, ldx_) + recurrent_sum(psi, pdf, dv, ldx_ + 1, rdx) :
    dv * psi[ldx] * pdf[rdx];
}

float forward_kahan_sum(float const psi[], float const pdf[], float const dv, unsigned size){
    float sum = 0.f;
    float s = 0.f;
    for (unsigned idx = 0; idx < size; idx++){
        float x = pdf[idx] * psi[idx] - s;
        float pre_sum = sum + x;
        s = (pre_sum - sum) - x;
        sum = pre_sum;
    }
    return dv * sum;
}

float forward_kahan_sum_fma(float const psi[], float const pdf[], float const dv, unsigned size){
    float sum = 0.f;
    float s = 0.f;
    for (unsigned idx = 0; idx < size; idx++){
        float x = fma(pdf[idx], psi[idx], -s);
        float pre_sum = sum + x;
        s = (pre_sum - sum) - x;
        sum = pre_sum;
    }
    return fma(dv, sum, 0.f);
}

double double_sum(float const psi[], float const pdf[], float const dv, unsigned size){
    double sum = 0.;
    auto ddv = (double)dv;
    for (unsigned idx = 0; idx < size; idx++)
        sum += (double)psi[idx] * (double)pdf[idx];
    return sum * ddv;
}


int main() {
    unsigned const n = 20480;
    float const pif = 3.1415926535f;
    float const T = 0.1f;
    float const pdf_coeff = std::sqrt(1.f / (T * pif));
    float psi[n] = {0}, pdf[n] = {0};

    float const v0 = 0.f;
    float const dv = 1.f / 128.f;
    for (unsigned idx = 0; idx != n; ++idx) {
        float v = std::fma(dv, static_cast<float>(idx), 0.f);
        psi[idx] = std::fma(dv, static_cast<float>(idx), 0.f);
        pdf[idx] = pdf_coeff * std::exp(-psi[idx] * psi[idx]);
    }
    std::cout << std::setprecision(10) << std::fixed;
    std::cout << "recurrent sum\n" << recurrent_sum(psi, pdf, dv, 0, n-1) << '\n';
    std::cout << "forward kahan sum\n" << forward_kahan_sum(psi, pdf, dv, n) << '\n';
    std::cout << "forward kahan sum with fma using\n" << forward_kahan_sum_fma(psi, pdf, dv, n) << '\n';
    std::cout << "standard sum in double type\n" << double_sum(psi, pdf, dv, n) << '\n';

    return 0;
}