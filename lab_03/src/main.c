//
// Created by dionis on 14.12.22.
//
#include <io.h>
#include <data_types.h>
#include <menu.h>


int main(void)
{
	error_t exit_code;

	matrix_std_t mtr_std, vec_std, res_mtr_std;
	matrix_sparse_t mtr_sparse, vec_sparse, res_mtr_sparse;

	greetings();
	exit_code = menu(&mtr_std, &mtr_sparse, &vec_std, &vec_sparse, &res_mtr_std, &res_mtr_sparse);

	return exit_code;
}
