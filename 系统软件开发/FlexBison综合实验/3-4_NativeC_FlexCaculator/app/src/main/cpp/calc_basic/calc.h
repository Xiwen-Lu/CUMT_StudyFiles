
#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#define CALC_MAX_LENGTH  (2000)

enum calc_error {
	NO_ERROR = 0,
	EXPR_ERROR = -1,
	EXPR_TOO_LONG = -2
};

extern int  calc(const char* expr, double* ans);


#ifdef __cplusplus
}
#endif
