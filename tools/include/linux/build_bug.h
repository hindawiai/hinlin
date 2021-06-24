<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BUILD_BUG_H
#घोषणा _LINUX_BUILD_BUG_H

#समावेश <linux/compiler.h>

#अगर_घोषित __CHECKER__
#घोषणा BUILD_BUG_ON_ZERO(e) (0)
#अन्यथा /* __CHECKER__ */
/*
 * Force a compilation error अगर condition is true, but also produce a
 * result (of value 0 and type पूर्णांक), so the expression can be used
 * e.g. in a काष्ठाure initializer (or where-ever अन्यथा comma expressions
 * aren't permitted).
 */
#घोषणा BUILD_BUG_ON_ZERO(e) ((पूर्णांक)(माप(काष्ठा अणु पूर्णांक:(-!!(e)); पूर्ण)))
#पूर्ण_अगर /* __CHECKER__ */

/* Force a compilation error अगर a स्थिरant expression is not a घातer of 2 */
#घोषणा __BUILD_BUG_ON_NOT_POWER_OF_2(n)	\
	BUILD_BUG_ON(((n) & ((n) - 1)) != 0)
#घोषणा BUILD_BUG_ON_NOT_POWER_OF_2(n)			\
	BUILD_BUG_ON((n) == 0 || (((n) & ((n) - 1)) != 0))

/*
 * BUILD_BUG_ON_INVALID() permits the compiler to check the validity of the
 * expression but aव्योमs the generation of any code, even अगर that expression
 * has side-effects.
 */
#घोषणा BUILD_BUG_ON_INVALID(e) ((व्योम)(माप((__क्रमce दीर्घ)(e))))

/**
 * BUILD_BUG_ON_MSG - अवरोध compile अगर a condition is true & emit supplied
 *		      error message.
 * @condition: the condition which the compiler should know is false.
 *
 * See BUILD_BUG_ON क्रम description.
 */
#घोषणा BUILD_BUG_ON_MSG(cond, msg) compileसमय_निश्चित(!(cond), msg)

/**
 * BUILD_BUG_ON - अवरोध compile अगर a condition is true.
 * @condition: the condition which the compiler should know is false.
 *
 * If you have some code which relies on certain स्थिरants being equal, or
 * some other compile-समय-evaluated condition, you should use BUILD_BUG_ON to
 * detect अगर someone changes it.
 */
#घोषणा BUILD_BUG_ON(condition) \
	BUILD_BUG_ON_MSG(condition, "BUILD_BUG_ON failed: " #condition)

/**
 * BUILD_BUG - अवरोध compile अगर used.
 *
 * If you have some code that you expect the compiler to eliminate at
 * build समय, you should use BUILD_BUG to detect अगर it is
 * unexpectedly used.
 */
#घोषणा BUILD_BUG() BUILD_BUG_ON_MSG(1, "BUILD_BUG failed")

/**
 * अटल_निश्चित - check पूर्णांकeger स्थिरant expression at build समय
 *
 * अटल_निश्चित() is a wrapper क्रम the C11 _Static_निश्चित, with a
 * little macro magic to make the message optional (शेषing to the
 * stringअगरication of the tested expression).
 *
 * Contrary to BUILD_BUG_ON(), अटल_निश्चित() can be used at global
 * scope, but requires the expression to be an पूर्णांकeger स्थिरant
 * expression (i.e., it is not enough that __builtin_स्थिरant_p() is
 * true क्रम expr).
 *
 * Also note that BUILD_BUG_ON() fails the build अगर the condition is
 * true, जबतक अटल_निश्चित() fails the build अगर the expression is
 * false.
 */
#अगर_अघोषित अटल_निश्चित
#घोषणा अटल_निश्चित(expr, ...) __अटल_निश्चित(expr, ##__VA_ARGS__, #expr)
#घोषणा __अटल_निश्चित(expr, msg, ...) _Static_निश्चित(expr, msg)
#पूर्ण_अगर // अटल_निश्चित

#पूर्ण_अगर	/* _LINUX_BUILD_BUG_H */
