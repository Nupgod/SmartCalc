#include "Calc_V2/model/SmartCalc.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(Calc, Default1) {
    std::string expression = "sin(cos(ln(sqrt(log(45.868)))))";
    s21::Model nw1;
    nw1.clearStr();
    nw1.norminette(expression);
    nw1.infToPost();
    double my_result = nw1.calculate(0);
    double original_result = sin(cos(log(sqrt(log10(45.868)))));
    EXPECT_DOUBLE_EQ(my_result, original_result);
}
TEST(Calc, Default2) {
    std::string expression = "acos(-0.06e+1)+asin(0.9)-atan(0.3)";
    s21::Model nw1;
    nw1.clearStr();
    nw1.norminette(expression);
    nw1.infToPost();
    double my_result = nw1.calculate(0);
    double original_result = acos(-0.06e+1)+asin(0.9)-atan(0.3);
    EXPECT_DOUBLE_EQ(my_result, original_result);
}
TEST(Calc, Default3) {
    std::string expression = "((tan(0.333)*0.259/15)%2)^0.15";
    s21::Model nw1;
    nw1.clearStr();
    nw1.norminette(expression);
    nw1.infToPost();
    EXPECT_TRUE(nw1.counter());
    double my_result = nw1.calculate(0);
    double original_result = pow(fmod(tan(0.333)*0.259/15, 2),0.15);
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}