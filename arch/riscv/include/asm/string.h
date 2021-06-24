<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_STRING_H
#घोषणा _ASM_RISCV_STRING_H

#समावेश <linux/types.h>
#समावेश <linux/linkage.h>

#घोषणा __HAVE_ARCH_MEMSET
बाह्य यंत्रlinkage व्योम *स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
बाह्य यंत्रlinkage व्योम *__स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
#घोषणा __HAVE_ARCH_MEMCPY
बाह्य यंत्रlinkage व्योम *स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);
बाह्य यंत्रlinkage व्योम *__स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);
#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य यंत्रlinkage व्योम *स_हटाओ(व्योम *, स्थिर व्योम *, माप_प्रकार);
बाह्य यंत्रlinkage व्योम *__स_हटाओ(व्योम *, स्थिर व्योम *, माप_प्रकार);
/* For those files which करोn't want to check by kasan. */
#अगर defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__)
#घोषणा स_नकल(dst, src, len) __स_नकल(dst, src, len)
#घोषणा स_रखो(s, c, n) __स_रखो(s, c, n)
#घोषणा स_हटाओ(dst, src, len) __स_हटाओ(dst, src, len)

#अगर_अघोषित __NO_FORTIFY
#घोषणा __NO_FORTIFY /* FORTIFY_SOURCE uses __builtin_स_नकल, etc. */
#पूर्ण_अगर

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_RISCV_STRING_H */
