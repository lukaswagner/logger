/**\file macros.hpp
 * \brief Debugging macros
 *
 * This header contains helper macros for easier debugging.
 */

#pragma once

/**
 * \def DEBUG_EXPR
 * \brief Logs an expression, alongside the source file and line, and executes it afterwards. Use this for tracing execution progress.
 * \param expression The expression to be logged.
 */
#define DEBUG_EXPR(expression) logger::debug("DEBUG_EXPR") << #expression << " (" << __FILE__ << ":" << __LINE__ << ")";expression;

 /**
 * \def DEBUG_VAL
 * \brief Logs the name and value of a given variable or expression. Use this debugging variable values.
 * \param value A variable or simple expression.
 */
#define DEBUG_VAL(value) logger::debug("DEBUG_VAL") << #value << " = " << (value);
