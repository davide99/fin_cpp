#include <fftw3.h>
#include "Spectrogram.h"
#include "Vector.h"
#include "Window.h"

Math::Spectrogram::Spectrogram(const std::vector<float>& data) {
    uint16_t stepSize = Consts::WinSize - Consts::Overlap;

    //Calculation of the winFFT size
    size_t winFFTsize = ((size_t) ((data.size() - Consts::WinSize) / stepSize)) * stepSize;
    this->fftWindows.resize(winFFTsize);

    FFTWindow fftWindow;
    float timeWindow[Consts::WinSize];

    fftwf_plan p = fftwf_plan_dft_r2c_1d(
            Consts::WinSize, timeWindow,
            reinterpret_cast<fftwf_complex *>(fftWindow.data.data()), FFTW_ESTIMATE);

    for (size_t i = 0; i + Consts::WinSize < data.size(); i += stepSize) {
        //Multiply the sliding window by the hamming window
        Vector::mul(Window::get(), data.data() + i, timeWindow, Consts::WinSize);
        fftwf_execute(p);

        fftWindow.time = (float) i / Consts::SampleRate;
        this->fftWindows.push_back(fftWindow);
    }

    fftwf_destroy_plan(p);
}

Math::Spectrogram::FFTWindow Math::Spectrogram::operator[](size_t pos) const {
    return this->fftWindows[pos];
}