stockwelltransform
==================

Stockwell transform for spectral analysis

This is a Matlab wrapper of the [Stockwell transform](http://en.wikipedia.org/wiki/S_transform).

The core `st_src.c` file is `st.c` from [this](https://bitbucket.org/cleemesser/stockwelltransform/src/a4b1627626c2?at=default) bitbucket repository.

The Matlab wrapper `st.c` is `st_wrapper.c` from the [NIMH MEG](http://kurage.nimh.nih.gov/meglab/Meg/Ctf2st).

I made a small change to avoid shifting the Hilbert transform in frequency when multiplying by the Gaussian window. 
Avoiding this shift means the normal Hilbert instaneous phase comes out in the spectrum.


## Installation

`make.m` has an editor cell for each platform with details of prerequisites to install and mex calls to compile the stockwell transform functions. 

## Usage

- `st_examples.m` has some examples of how to call the function.

`[st_data,st_times,st_frequencies] = st(data,min_F,max_F,Fs);`


