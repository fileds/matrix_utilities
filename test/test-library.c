/**
 * @file test-library.c
 * @brief Tests for the matrix utilities
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix_utilities.h"

int
scalar_test_fail (double a,
                  double b);

int
vector_test_fail (int    n,
                  double a[n],
                  double b[n]);

int
matrix_test_fail (int    n,
                  int    m,
                  double a[n*m],
                  double b[n*m]);

void
test_init (char test[20]);

int main (void) {
  // Vector tests
  double v1[3] =  {1, 2, 3};
  double v2[3] =  {4, 5, 6};

  printf ("\n\t--- Vector tests ---\n\n");

  test_init ("scalar product");
  double s_scalar;
  double s_scalar_ref = 32;

  vector_scalar_product ( 3,
                          v1,
                          v2,
                         &s_scalar);

  if (scalar_test_fail (s_scalar, s_scalar_ref))
    return 1;


  test_init ("cross product");
  double v_cross[3];
  double v_cross_ref[3] = {-3, 6, -3};

  vector_3d_cross_product ( v1,
                            v2,
                           &v_cross);

  if (vector_test_fail (3, v_cross, v_cross_ref))
    return 1;


  test_init ("outer product");
  double m_op[9];
  double m_op_ref[9] = { 4,  5,  6,
                         8, 10, 12,
                        12, 15, 18};

  vector_outer_product ( 3,
                         v1,
                         v2,
                        &m_op);

  if (matrix_test_fail (3, 3, m_op, m_op_ref))
    return 1;


  // Matrix tests
  printf ("\n\n\t--- Matrix tests ---\n");
  double m1[9] = {1, 2, 3,
                  4, 5, 6,
                  7, 8, 9};


  test_init ("row to col conversion 1");
  double m_row_to_col_1[12];
  double m_row_to_col_test_1[12] = { 1,  2,  3,
                                     4,  5,  6,
                                     7,  8,  9,
                                    10, 11, 12};
  double m_row_to_col_ref_1[12] = { 1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12};

  matrix_row_to_col_major ( 4,
                            3,
                            m_row_to_col_test_1,
                           &m_row_to_col_1);

  if (matrix_test_fail (4, 3, m_row_to_col_1, m_row_to_col_ref_1))
    return 1;


  test_init ("row to col conversion 2");
  double m_row_to_col_2[9];
  double m_row_to_col_test_2[6] = {1, 2,
                                   3, 4,
                                   5, 6};
  double m_row_to_col_ref_2[6] = {1, 3, 5, 2, 4, 6};

  matrix_row_to_col_major( 3,
                           2,
                           m_row_to_col_test_2,
                          &m_row_to_col_2);

  if (matrix_test_fail (3, 2, m_row_to_col_2, m_row_to_col_ref_2))
    return 1;


  test_init ("col to row conversion");
  double m_col_to_row[9];
  matrix_col_to_row_major( 3,
                           2,
                           m_row_to_col_2,
                          &m_col_to_row);

  if (matrix_test_fail (3, 2, m_col_to_row, m_row_to_col_test_2))
    return 1;


  test_init ("matrix scaling");
  double m_scaled[9];
  double f = 2;
  double m_scaled_ref[9] = { 2,  4,  6,
                            8, 10, 12,
                           14, 16, 18};

  matrix_scaling( 3,
                  3,
                  f,
                  m1,
                 &m_scaled);

  if (matrix_test_fail (3, 3, m_scaled, m_scaled_ref))
    return 1;


  test_init ("matrix addition");
  double m_add[9];
  double m_ones[9] = {1, 1, 1,
                      1, 1, 1,
                      1, 1, 1};
  double m_add_ref[9] = {2, 3,  4,
                         5, 6,  7,
                         8, 9, 10};

  matrix_addition ( 3,
                                3,
                                m1,
                                m_ones,
                               &m_add);

  if (matrix_test_fail (3, 3, m_add, m_add_ref))
    return 1;


  test_init ("matrix subtraction");
  double m_sub[9];
  double m_sub_ref[9] = {0, 1, 2,
                         3, 4, 5,
                         6, 7, 8};

  matrix_subtraction ( 3,
                                   3,
                                   m1,
                                   m_ones,
                                  &m_sub);

  if (matrix_test_fail (3, 3, m_sub, m_sub_ref))
    return 1;


  test_init ("matrix sum");
  double m_sum;
  double m_sum_ref = 45;

  matrix_elementwise_sum ( 3,
                           3,
                           m1,
                          &m_sum);

  if (scalar_test_fail (m_sum, m_sum_ref))
    return 1;


  test_init ("vector matrix multiplication");
  double v_vec_mult[3];
  double v_vec_mult_ref[3] = {30, 36, 42};

  matrix_multiplication ( 1,
                          3,
                          3,
                          v1,
                          m1,
                         &v_vec_mult);

  if (vector_test_fail (3, v_vec_mult, v_vec_mult_ref))
    {
      return 1;
    }


  test_init ("matrix multiplication 1");
  double m_mult[9];
  double m_mult_ref[9] = { 6,  6,  6,
                          15, 15, 15,
                          24, 24, 24};

  matrix_multiplication ( 3,
                          3,
                          3,
                          m1,
                          m_ones,
                         &m_mult);

  if (matrix_test_fail (3, 3, m_mult, m_mult_ref))
    return 1;


  test_init ("matrix multiplication 2");
  double m_mult2[4];
  double m_mult2_1[6] = {1, 2, 3,
                         4, 5, 6};
  double m_mult2_2[6] = {1, 2,
                         3, 4,
                         5, 6};
  double m_mult2_ref[4] = {22, 28,
                           49, 64};

  matrix_multiplication ( 2,
                          3,
                          2,
                          m_mult2_1,
                          m_mult2_2,
                         &m_mult2);

  if (matrix_test_fail (2, 2, m_mult2, m_mult2_ref))
    return 1;


  test_init ("matrix multiplication 3");
  double m_mult3[9];
  double m_mult3_ref[9] = { 9, 12, 15,
                           19, 26, 33,
                           29, 40, 51};

  matrix_multiplication ( 3,
                          2,
                          3,
                          m_mult2_2,
                          m_mult2_1,
                         &m_mult3);

  if (matrix_test_fail (2, 2, m_mult2, m_mult2_ref))
    return 1;


  test_init ("2d matrix inversion");
  double m_2d[4] = {4, 7,
                    2, 6};
  double m_2d_inv[4];
  double m_2d_inv_ref[4] = { 0.6, -0.7,
                            -0.2,  0.4};

  matrix_2d_inversion ( m_2d,
                       &m_2d_inv);

  if (matrix_test_fail (2, 2, m_2d_inv, m_2d_inv_ref))
    return 1;


  test_init ("3d matrix inversion");
  double m_3d[9] = {1, 2, 3,
                    0, 1, 4,
                    5, 6, 0};

  double m_3d_inv[9];
  double m_3d_inv_ref[9] = {-24,  18,   5,
                             20, -15,  -4,
                             -5,   4,   1};

  matrix_3d_inversion ( m_3d,
                       &m_3d_inv);

  if (matrix_test_fail (3, 3, m_3d_inv, m_3d_inv_ref))
    return 1;


  printf ("\nAll tests passed!\nQuitting...\n");
  return 0;
}

int
scalar_test_fail (double a,
                  double b)
{
  // Prints comparison
  printf ("\tResult\tExpected\n");
  printf ("\t%6.2f\t%6.2f\n", a, b);

  // Compares values
  if (a != b)
    {
      printf ("\nError, test failed. Value %8.4f != reference %8.4f. "
              "Qutting...\n\n", a, b);
      return 1;
    }

  printf ("\n\tTest passed!\n");
  return 0;
}

int
vector_test_fail (int    n,
                  double a[n],
                  double b[n])
{
  // Prints comparison
  printf ("\tResult\tExpected");
  for (int i=0; i<n; i++)
    printf ("\n\t%6.2f\t%6.2f", a[i], b[i]);
  printf ("\n");

  // Compares each element
  for (int i=0; i<n; i++)
    {
      if (fabs (a[i] - b[i]) > 1e-9)
        {
            printf ("\nError, test failed. Value %8.4f !=  reference %8.4f. "
                    "Quitting...\n\n", a[i], b[i]);
          return 1;
        }
    }

  printf ("\n\tTest passed!\n");
  return 0;
}

int
matrix_test_fail (int    n,
                  int    m,
                  double a[n*m],
                  double b[n*m])
{
  // Prints comparison
  printf ("\tResult%*cExpected", (m)*6, ' ');
  for (int i=0; i<n; i++)
    {
      printf ("\n\t");
      for (int j=0; j<m; j++)
        printf ("%5.1f ", a[i*m + j]);
      printf ("%*c", 6, ' ');
      for (int j=0; j<m; j++)
        printf ("%5.1f ", b[i*m + j]);
    }
  printf ("\n");

  // Compares each element, accepts small numerical error of order 1e-9
  for (int i=0; i<n*m; i++)
      {
        if (fabs (a[i] - b[i]) > 1e-9)
          {
            printf ("\nError, test failed. Value %8.4f !=  reference %8.4f. "
                    "Quitting...\n\n", a[i], b[i]);
            return 1;
          }
      }

  printf ("\n\tTest passed!\n");
  return 0;
}

void
test_init (char test[20])
{
  printf ("\nTesting %s\n\n", test);
}
