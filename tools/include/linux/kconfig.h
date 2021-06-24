<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_KCONFIG_H
#घोषणा _TOOLS_LINUX_KCONFIG_H

/* CONFIG_CC_VERSION_TEXT (Do not delete this comment. See help in Kconfig) */

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा __BIG_ENDIAN 4321
#अन्यथा
#घोषणा __LITTLE_ENDIAN 1234
#पूर्ण_अगर

#घोषणा __ARG_PLACEHOLDER_1 0,
#घोषणा __take_second_arg(__ignored, val, ...) val

/*
 * The use of "&&" / "||" is limited in certain expressions.
 * The following enable to calculate "and" / "or" with macro expansion only.
 */
#घोषणा __and(x, y)			___and(x, y)
#घोषणा ___and(x, y)			____and(__ARG_PLACEHOLDER_##x, y)
#घोषणा ____and(arg1_or_junk, y)	__take_second_arg(arg1_or_junk y, 0)

#घोषणा __or(x, y)			___or(x, y)
#घोषणा ___or(x, y)			____or(__ARG_PLACEHOLDER_##x, y)
#घोषणा ____or(arg1_or_junk, y)		__take_second_arg(arg1_or_junk 1, y)

/*
 * Helper macros to use CONFIG_ options in C/CPP expressions. Note that
 * these only work with boolean and tristate options.
 */

/*
 * Getting something that works in C and CPP क्रम an arg that may or may
 * not be defined is tricky.  Here, अगर we have "#define CONFIG_BOOGER 1"
 * we match on the placeholder define, insert the "0," क्रम arg1 and generate
 * the triplet (0, 1, 0).  Then the last step cherry picks the 2nd arg (a one).
 * When CONFIG_BOOGER is not defined, we generate a (... 1, 0) pair, and when
 * the last step cherry picks the 2nd arg, we get a zero.
 */
#घोषणा __is_defined(x)			___is_defined(x)
#घोषणा ___is_defined(val)		____is_defined(__ARG_PLACEHOLDER_##val)
#घोषणा ____is_defined(arg1_or_junk)	__take_second_arg(arg1_or_junk 1, 0)

/*
 * IS_BUILTIN(CONFIG_FOO) evaluates to 1 अगर CONFIG_FOO is set to 'y', 0
 * otherwise. For boolean options, this is equivalent to
 * IS_ENABLED(CONFIG_FOO).
 */
#घोषणा IS_BUILTIN(option) __is_defined(option)

/*
 * IS_MODULE(CONFIG_FOO) evaluates to 1 अगर CONFIG_FOO is set to 'm', 0
 * otherwise.
 */
#घोषणा IS_MODULE(option) __is_defined(option##_MODULE)

/*
 * IS_REACHABLE(CONFIG_FOO) evaluates to 1 अगर the currently compiled
 * code can call a function defined in code compiled based on CONFIG_FOO.
 * This is similar to IS_ENABLED(), but वापसs false when invoked from
 * built-in code when CONFIG_FOO is set to 'm'.
 */
#घोषणा IS_REACHABLE(option) __or(IS_BUILTIN(option), \
				__and(IS_MODULE(option), __is_defined(MODULE)))

/*
 * IS_ENABLED(CONFIG_FOO) evaluates to 1 अगर CONFIG_FOO is set to 'y' or 'm',
 * 0 otherwise.
 */
#घोषणा IS_ENABLED(option) __or(IS_BUILTIN(option), IS_MODULE(option))

#पूर्ण_अगर /* _TOOLS_LINUX_KCONFIG_H */
