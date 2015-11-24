#include <stdio.h>
#include <stdlib.h>
#include <mex.h>
#include <matrix.h>

extern void ist(int len, int lo, int hi, double *data, double *result);

/* [st_matrix, times, frequencies] = st(data, lo, hi, srate) */

void mexFunction(int nlhs, mxArray **plhs, int nrhs, const mxArray **prhs)
{
	int i, j, n, len, lo, hi;
	double lof, hif, srate, t;
	double *data, *result, *times, *freqs, *dr, *di, *s;

	if (nlhs > 1 || nrhs != 4) {
		mexErrMsgTxt("Wrong number of arguments to function st");
	}

	if (!mxIsDouble(prhs[0])) {
		mexErrMsgTxt("st input 1 must be real");
	}
	len = mxGetN(prhs[0]);

	if (mxGetM(prhs[1]) != 1 || mxGetN(prhs[1]) != 1) {
		mexErrMsgTxt("st input 2 must be a scalar");
	}
	lof = mxGetScalar(prhs[1]);

	if (mxGetM(prhs[2]) != 1 || mxGetN(prhs[2]) != 1) {
		mexErrMsgTxt("st input 3 must be a scalar");
	}
	hif = mxGetScalar(prhs[2]);

	if (mxGetM(prhs[3]) != 1 || mxGetN(prhs[3]) != 1) {
		mexErrMsgTxt("st input 4 must be a scalar");
	}
	srate = mxGetScalar(prhs[3]);

	/* Convert frequencies in Hz into rows of the ST. */

	lo = (int)(lof * len / srate + .5);
	hi = (int)(hif * len / srate + .5);

	if (lo < 0 || hi > len / 2) {
		mexErrMsgTxt("st frequencies out of bounds");
	}
	n = hi - lo + 1;

	if (mxGetM(prhs[0]) != n) {
		mexErrMsgTxt("spectrum does not match hi/lo specification");
	}

	/* Allocate space for the result matrix. */

	plhs[0] = mxCreateDoubleMatrix(1, len, mxREAL);


	/* Create temporary storage for the IST */
	data = (double *)mxMalloc(n * len * sizeof(double) * 2);

	/* Copy the real and imaginary parts into the ist input matrix matrix. */
	dr = mxGetPr(prhs[0]);
	di = mxGetPi(prhs[0]);
	s = data;
	for (j = 0; j < n; j++) {
		for (i = 0; i < len; i++) {
			*s = dr[i * n + j];
			s++;
			*s = di[i * n + j];
			s++;
		}
	}

	result = mxGetPr(plhs[0]);
	ist(len, lo, hi, data, result);

	mxFree(data);
}
