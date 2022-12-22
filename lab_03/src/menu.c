//
// Created by dionis on 11.12.22.
//

#include <menu.h>
#include <constants.h>
#include <data_types.h>
#include <load_mtr.h>
#include <matrix_sparse.h>
#include <matrix_standard.h>
#include <measurements.h>
#include <io.h>


error_t menu(matrix_std_t *std_mtr, matrix_sparse_t *sparse_mtr,
			 matrix_std_t *std_vector, matrix_sparse_t *sparse_vector,
			 matrix_std_t *res_std_mtr, matrix_sparse_t *res_sparse_mtr)
{

	print_menu();
	input_prompt();

	error_t exit_code = OK;
	int menu_item = 1;
	int read_status = scanf("%d", &menu_item);

	while (menu_item != 0)
	{
		if (read_status != 1)
			err_message(COMM_ERR_MESS);
		else
			switch (menu_item)
			{
				case 1:
					exit_code = load_mtr_from_file(sparse_mtr, std_mtr);
					break;

				case 2:
					exit_code = load_mtr_from_cons(sparse_mtr, std_mtr);
					break;

				case 3:
					exit_code = load_vector_from_file(sparse_vector, std_vector);
					break;

				case 4:
					exit_code = load_vector_from_cons(sparse_vector, std_vector);
					break;

				case 5:
					exit_code = multiply_std(std_mtr, std_vector, res_std_mtr);
					break;

				case 6:
					exit_code = multiply_sparse(sparse_mtr, sparse_vector, res_sparse_mtr);
					break;

				case 7:
					compare_multiplications();
					break;

				case 8:
					print_std_format(res_std_mtr);
					break;

				case 9:
					print_sparse_format(res_sparse_mtr);
					break;

				case 10:
					print_coord_format(res_std_mtr);
					break;

				case 11:
					print_std_format(std_vector);
					break;

				case 12:
					print_sparse_format(sparse_vector);
					break;

				case 13:
					print_coord_format(std_vector);
					break;

				case 14:
					print_std_format(std_mtr);
					break;

				case 15:
					print_sparse_format(sparse_mtr);
					break;

				case 16:
					print_coord_format(std_mtr);
					break;

				case 17:
					print_menu();
					break;

				default:
					err_message("Error: unknown command!\n");
					break;
			}

		input_prompt();
		fflush(stdin);
		setbuf(stdin, NULL);
		read_status = scanf("%d", &menu_item);
	}

	return exit_code;
}
