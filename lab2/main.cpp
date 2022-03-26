#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

float float_sum(float const psi[], float const pdf[], float const dv, unsigned size){
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

float near_sum_one(float psi[], float dv, unsigned size, unsigned dx){
    for (unsigned idx = 0; idx < size; idx += 2 * dx)
        if (idx + dx < size)
            psi[idx] += psi[idx + dx];

    return (2 * dx + 2 < size) ?
           near_sum_one(psi, dv, size, dx * 2):
           dv * psi[0];
}

float near_sum(float const psi[], float const pdf[], float const dv, unsigned size){
    float psi_[size];
    for (unsigned idx = 0; idx < size; idx++)
        psi_[idx] = psi[idx] * pdf[idx];
    return 2 * near_sum_one(psi_, dv, size, 1);
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

void fout(std::string file_name, unsigned const n, float const T, float value, double mvc){
    std::ofstream file_out(file_name, ios_base::app);
    file_out << std::setprecision(2) << "segmentation = " << 2 * n << " temperature = " << T;
    file_out << std::setprecision(10) << " value = " << value << " differ = " << mvc - value << '\n';
    file_out.close();
}

void fout(std::string file_name, unsigned const n, float const T, double value, double mvc){
    std::ofstream file_out(file_name, ios_base::app);
    file_out << std::setprecision(2) << "segmentation = " << 2 * n << " temperature = " << T;
    file_out << std::setprecision(10) << " value = " << value << " differ = " << mvc - value << '\n';
    file_out.close();
}

void fclear(std::string file_name){
    std::ofstream file( file_name, std::ios::out);
    file.close();
}

void fclear_all(){
    fclear("float_sum");
    fclear("recurrent_sum");
    fclear("sum_with_near_numbers");
    fclear("forward_kahan_sum");
    fclear("forward_kahan_sum_with_using_fma");
    fclear("standard_sum_in_double_type");
}

int main() {
    unsigned const n = 4385;
    float const pif = 3.1415926535f;
    double const pi = 3.1415926535;
    float const T = 100.f;
    float const pdf_coeff = std::sqrt(1.f / (T * pif));
    float psi[n] = {0}, pdf[n] = {0};

    float const dv = 1.f / 128.f;
    for (unsigned idx = 0; idx != n; ++idx) {
        float v = std::fma(dv, static_cast<float>(idx), 0.f);
        psi[idx] = v;
        pdf[idx] = pdf_coeff * std::exp(-psi[idx] * psi[idx] / T);
    }

    double mvc = std::sqrt(T / pi);

    fout("float_sum", n, T, float_sum(psi, pdf, dv, n), mvc);
    fout("recurrent_sum", n, T, recurrent_sum(psi, pdf, dv, 0, n-1), mvc);
    fout("sum_with_near_numbers", n, T, near_sum(psi, pdf, dv, n), mvc);
    fout("forward_kahan_sum", n, T, forward_kahan_sum(psi, pdf, dv, n), mvc);
    fout("forward_kahan_sum_with_using_fma", n, T, forward_kahan_sum_fma(psi, pdf, dv, n), mvc);
    fout("standard_sum_in_double_type", n, T, double_sum(psi, pdf, dv, n), mvc);

//    fclear_all();

    return 0;
}
