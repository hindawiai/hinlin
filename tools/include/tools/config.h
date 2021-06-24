<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_CONFIG_H
#घोषणा _TOOLS_CONFIG_H

/* Subset of include/linux/kconfig.h */

#घोषणा __ARG_PLACEHOLDER_1 0,
#घोषणा __take_second_arg(__ignored, val, ...) val

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

#पूर्ण_अगर /* _TOOLS_CONFIG_H */
