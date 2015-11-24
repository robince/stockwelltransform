#include <stdio.h>
#include <stdlib.h>
#include <mex.h>
#include <matrix.h>

extern void st(int len, int lo, int hi, double *data, double *result);

/* [st_matrix, times, frequencies] = st(data, lo, hi, srate) */

void mexFunction(int nlhs, mxArray **plhs, int nrhs, const mxArray **prhs)
{
	int i, j, n, len, lo, hi;
	double lof, hif, srate, t;
	double *data, *result, *times, *freqs, *d, *s;

	if (nlhs > 3 || nrhs != 4) {
		mexErrMsgTxt("Wrong number of arguments to function st");
	}

	if (mxGetM(prhs[0]) != 1) {
		mexErrMsgTxt("st input 1 must be a row vector");
	}
	if (!mxIsDouble(prhs[0])) {
		mexErrMsgTxt("st input 1 must be real");
	}
	len = mxGetN(prhs[0]);
	data = mxGetPr(prhs[0]);

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

	/* Allocate space for the result matrix. */

	plhs[0] = mxCreateDoubleMatrix(n, len, mxCOMPLEX);

	/* Create row vectors that contain the times and frequencies
	corresponding to the columns and rows of the matrix. */

	plhs[1] = mxCreateDoubleMatrix(1, len, mxREAL);
	plhs[2] = mxCreateDoubleMatrix(1, n, mxREAL);

	d = mxGetPr(plhs[1]);
	t = 1. / srate;
	for (i = 0; i < len; i++) {
		*d++ = i * t;
	}

	d = mxGetPr(plhs[2]);
	t = (hif - lof) / (n - 1);
	for (i = 0; i < n; i++) {
		*d++ = lof + i * t;
	}

	/* Create temporary storage for the ST and calculate it. */

	result = (double *)mxMalloc(n * len * sizeof(double) * 2);

	st(len, lo, hi, data, result);

	/* Copy the real and imaginary parts into the output matrix. */

	d = mxGetPr(plhs[0]);
	s = result;
	for (j = 0; j < n; j++) {
		for (i = 0; i < len; i++) {
			d[i * n + j] = *s;
			s += 2;
		}
	}
	d = mxGetPi(plhs[0]);
	s = result + 1;
	for (j = 0; j < n; j++) {
		for (i = 0; i < len; i++) {
			d[i * n + j] = *s;
			s += 2;
		}
	}

	mxFree(result);
}
