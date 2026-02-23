#include "../include/exprtk.hpp"
using namespace std; // 这又不是什么大型项目就默认用了

// 判断表达式是否合法, 由 deepseek 娘编写. 
std::pair<bool, std::string> validate_expression(const std::string& expr, const std::string& var_name = "x") {
    using T = double;

    T x = 0.0; // 虚拟变量，值不重要

    exprtk::symbol_table<T> symbol_table;
    symbol_table.add_variable(var_name, x);

    exprtk::expression<T> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<T> parser;

    if (!parser.compile(expr, expression)) {
        std::string error_msg;
        if (parser.error_count() > 0) {
            // 获取第一个错误信息
            error_msg = parser.get_error(0).diagnostic;
        } else {
            error_msg = "Unknown compilation error";
        }
        return {false, error_msg};
    }
    return {true, ""};
}

// 对表达式求值, 由 ds 编写, 错误返回 INT_MIN(-2147483648)
double eval(const std::string& expression_string, double x_value) {
    using T = double;

    // 声明变量 x
    T x = x_value;

    // 创建符号表并注册变量 x
    exprtk::symbol_table<T> symbol_table;
    symbol_table.add_variable("x", x);

    // 创建表达式对象并关联符号表
    exprtk::expression<T> expression;
    expression.register_symbol_table(symbol_table);

    // 创建解析器并编译表达式字符串
    exprtk::parser<T> parser;
    if (!parser.compile(expression_string, expression)) {
        // 编译失败时处理错误
        return -2147483648;
    }

    // 求值：此时 x 的值已通过 x_value 设置
    return expression.value();
}