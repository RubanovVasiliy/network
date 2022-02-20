#include "../src/func.h"
#include "../thirdparty/ctest.h"
#include <math.h>

// create_cir

CTEST(geometry, create_cir_corrrect_input_1)
{
    // Given
    char* input = "circle(0 0,4)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NOT_NULL(circle);
}

CTEST(geometry, create_cir_corrrect_input_2)
{
    // Given
    char* input = "circle(0.1 0.7,0.01)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NOT_NULL(circle);
}

CTEST(geometry, create_cir_bad_value)
{
    // Given
    char* input = "circle(0 0,-0.01)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_bad_input)
{
    // Given
    char* input = "21hj3g21jh3";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_bad_circle)
{
    // Given
    char* input = "circla(0 0,1)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_bad_format_brackets)
{
    // Given
    char* input = "circlе0 0,1";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_bad_format_pointer)
{
    // Given
    char* input = "(0 0 1)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_too_many_args)
{
    // Given
    char* input = "(0 0, 1, 1)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

CTEST(geometry, create_cir_few_args)
{
    // Given
    char* input = "(0, 1)";
    // When
    Circle* circle = create_cir(input);
    // Then

    ASSERT_NULL(circle);
}

// print_cir

CTEST(geometry, print_cir_correct)
{
    // Given
    char* input = "circle(0 0,4)";
    // When
    Circle* c = create_cir(input);
    int real = print_cir(c);
    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(geometry, print_cir_incorrect)
{
    // Given
    char* input = "circle(0 0,-4)";
    // When
    Circle* c = create_cir(input);
    int real = print_cir(c);
    // Then
    const int expected = -1;

    ASSERT_EQUAL(expected, real);
}

// intersec_cir_cir

CTEST(geometry, intersec_cir_cir_correct_intersec_1)
{
    // Given
    char* input1 = "circle(-3 0,2)";
    char* input2 = "circle(1 0,2)";
    // When
    Circle* c1 = create_cir(input1);
    Circle* c2 = create_cir(input2);
    int real = intersec_cir_cir(c1, c2);
    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}

CTEST(geometry, intersec_cir_cir_correct_intersec_2)
{
    // Given
    char* input1 = "circle(0 0,4)";
    char* input2 = "circle(3 0,1)";
    // When
    Circle* c1 = create_cir(input1);
    Circle* c2 = create_cir(input2);
    int real = intersec_cir_cir(c1, c2);
    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}

CTEST(geometry, intersec_cir_cir_correct_no_intersec_1)
{
    // Given
    char* input1 = "circle(-3 0,1)";
    char* input2 = "circle(1 0,1)";
    // When
    Circle* c1 = create_cir(input1);
    Circle* c2 = create_cir(input2);
    int real = intersec_cir_cir(c1, c2);
    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(geometry, intersec_cir_cir_correct_no_intersec_2)
{
    // Given
    char* input1 = "circle(0 0,4.01)";
    char* input2 = "circle(3 0,1)";
    // When
    Circle* c1 = create_cir(input1);
    Circle* c2 = create_cir(input2);
    int real = intersec_cir_cir(c1, c2);
    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

//perimeter_cir

CTEST(geometry, perimeter_cir_correct)
{
    // Given
    double r = 0.1;
    // When
    double real = perimeter_cir(r);
    // Then
    const double expected = 2 * M_PI * r;

    ASSERT_DBL_NEAR(expected, real);
}

CTEST(geometry, perimeter_cir_incorrect)
{
    // Given
    double r = -0.1;
    // When
    double real = perimeter_cir(r);
    // Then
    const double expected = -1;

    ASSERT_DBL_NEAR(expected, real);
}

//square_cir

CTEST(geometry, square_cir_correct)
{
    // Given
    double r = 0.1;
    // When
    double real = square_cir(r);
    // Then
    const double expected = M_PI * r * r;

    ASSERT_DBL_NEAR(expected, real);
}

CTEST(geometry, square_cir_incorrect)
{
    // Given
    double r = -0.1;
    // When
    double real = square_cir(r);
    // Then
    const double expected = -1;

    ASSERT_DBL_NEAR(expected, real);
}