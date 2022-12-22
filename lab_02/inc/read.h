//
// Created by dionis on 03.12.22.
//

#ifndef LAB_02_READ_H
#define LAB_02_READ_H


#include <data_types.h>


error_t read_string(FILE *stream, char **str, size_t *len);
error_t get_new_value(FILE *stream, theater_t *theater);
error_t get_new_value_from_stdin(theater_t *theater, const char *field_type);

error_t put_value_to_string_field(const char *src_str, char *dest_field, size_t len, size_t max_len, const char *err_mess);
error_t put_value_to_price_field(const char *src_str, price_t *dest_field);
error_t put_value_to_age_field(const char *src_str, age_t *dest_field);
error_t put_value_to_dur_field(const char *src_str, dur_t *dest_field);
error_t put_value_to_type_field(const char *src_str, theater_t *theater);
error_t put_value_to_attr_field(const char *field_type, const char *field_value, theater_t *theater);
error_t put_value_to_genre_field(const char *genre, theater_t *theater);


#endif //LAB_02_READ_H
