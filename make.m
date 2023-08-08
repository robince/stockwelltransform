
%%
%
% LINUX
%

% - Install your systems fftw3 and associated development packages
%   (e.g. `fftw3` and `fftw3-devel` on Centos, `fftw3` and `fftw3-dev`
%   on Debian/Ubuntu).
% - If you get errors about fftw3.h you might need to add
%   -I/path/to/fftw3.h to the first mex call.
%
mex -c st_src.c
mex st.c st_src.o -lfftw3
mex ist.c st_src.o -lfftw3

%%
%
% WINDOWS
%

% - Install Visual Studio community edition with MSVC option
% - In matlab: `mex -setup`, copy and paste the command to select the
%   compiler
% - Download fftw3 win64 package
% - Run `'C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64\lib.exe' /machine:x64 /def:libfftw3-3.def`
%   in the fftw folder (might need to change path to lib.exe to match your
%   version)
% - Copy `libfftw3-3.dll`, `libfftw3-3.exp`, `libfftw3-3.lib`, `fftw3.h` to
%   stockwelltransform directory
%
mex -c st_src.c -I.\ -D_USE_MATH_DEFINES
mex st.c st_src.obj -lfftw-3.3 -L.\

%%
%
% MAC
%

% - Install XCode command line developer tools
% - `mex -setup` to use those.
% - Install fftw with homebrew: `brew install fftw`
%
mex -c st_src.c

MEXARGS = {'st_src.o' '-lfftw3' };
if strcmpi(mexext,'mexmaca64')
    % apple silicon, homebrew in /opt
    MEXARGS{end+1} = '-L/opt/homebrew/lib';
elseif strmpci(mexext,'mexmaci64')
    % intel, homebrew in /usr/local (or change to your homebrew localtion
    MEXARGS{end+1} = '-L/usr/local/lib';
end

mex('st.c', MEXARGS{:})
mex('ist.c', MEXARGS{:})