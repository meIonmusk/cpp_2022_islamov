#include <iostream>
#include <iomanip>
#include <cmath>

double float_sum(float const psi[], float const pdf[], float const dv, unsigned size){
    float sum = 0.f;
    for (unsigned idx = 0; idx < size; idx++)
        sum += psi[idx] * pdf[idx];
    return 2 * sum * dv;
}

float recurrent_sum(float const psi[], float const pdf[], float const dv, unsigned ldx, unsigned rdx){
    auto ldx_ = ldx + (rdx - ldx) / 2;
    return (rdx - ldx)?
           (recurrent_sum(psi, pdf, dv, ldx, ldx_) + recurrent_sum(psi, pdf, dv, ldx_ + 1, rdx)) :
           2 * dv * psi[ldx] * pdf[rdx];
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
    return 2 * dv * sum;
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
    return 2 * fma(dv, sum, 0.f);
}

double double_sum(float const psi[], float const pdf[], float const dv, unsigned size){
    double sum = 0.;
    for (unsigned idx = 0; idx < size; idx++)
        sum += static_cast<double>(psi[idx]) * static_cast<double>(pdf[idx]);
    return 2 * sum * static_cast<double>(dv);
}


int main() {
    unsigned const n = 10000;
    float const pif = 3.1415926535f;
    float const T = 0.1f;
    float const pdf_coeff = std::sqrt(1.f / (T * pif));
    float psi[n] = {0}, pdf[n] = {0};

    float const v0 = 0.f;
    float const dv = 1.f / 128.f;
    for (unsigned idx = 0; idx != n; ++idx) {
        float v = std::fma(dv, static_cast<float>(idx), 0.f);
        psi[idx] = v;
        pdf[idx] = pdf_coeff * std::exp(-psi[idx] * psi[idx] / T);
    }
    std::cout << std::setprecision(10) << std::fixed;
    std::cout << "float sum\n" << float_sum(psi, pdf, dv, n) << '\n';
    std::cout << "recurrent sum\n" << recurrent_sum(psi, pdf, dv, 0, n-1) << '\n';
    std::cout << "forward kahan sum\n" << forward_kahan_sum(psi, pdf, dv, n) << '\n';
    std::cout << "forward kahan sum with using fma\n" << forward_kahan_sum_fma(psi, pdf, dv, n) << '\n';
    std::cout << "standard sum in double type\n" << double_sum(psi, pdf, dv, n) << '\n';
    std::cout << "mean velocity value\n" << std::sqrt(T / pif);

    return 0;
}