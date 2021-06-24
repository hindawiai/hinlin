<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_TYPES_H
#घोषणा __LINUX_COMPILER_TYPES_H

/* Builtins */

/*
 * __has_builtin is supported on gcc >= 10, clang >= 3 and icc >= 21.
 * In the meanसमय, to support gcc < 10, we implement __has_builtin
 * by hand.
 */
#अगर_अघोषित __has_builtin
#घोषणा __has_builtin(x) (0)
#पूर्ण_अगर

/* Compiler specअगरic macros. */
#अगर_घोषित __GNUC__
#समावेश <linux/compiler-gcc.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_COMPILER_TYPES_H */
