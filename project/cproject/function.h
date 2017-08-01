#ifndef FUNCTION_H
#define FUNCTION_H

void save_t(tea *head);
void save_s(stu *head);
void addstudent();
void addteacher();
void print_s();
void print_c();
void print_m();

void print_t();
void update_s();
void update_m();
void update_c();
void update_t();
void chang_t(char *passwd);
void chang_s(char *passwd);
void sort_s();
void sort_c();

void sort_m();
void sort_id();
void delete_s();
void delete_t(int id);
void resign(int id);
void agree();
void person(int id);
int job(int id);
void left_w();
void left_l();

#endif
