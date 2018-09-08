#pragma once

#define DEBUG_EXPR(expression) logger::debug("DEBUG_EXPR") << #expression << " (" << __FILE__ << ":" << __LINE__ << ")"; expression

#define DEBUG_VAL(value) logger::debug("DEBUG_VAL") << #value << " = " << (value);
