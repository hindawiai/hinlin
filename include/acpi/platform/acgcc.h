<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acgcc.h - GCC specअगरic defines, etc.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACGCC_H__
#घोषणा __ACGCC_H__

/*
 * Use compiler specअगरic <मानकतर्क.स> is a good practice क्रम even when
 * -noमानक_निवेशc is specअगरied (i.e., ACPI_USE_STANDARD_HEADERS undefined.
 */
#अगर_अघोषित बहु_तर्क
#अगर_घोषित ACPI_USE_BUILTIN_STDARG
प्रकार __builtin_बहु_सूची बहु_सूची;
#घोषणा बहु_शुरू(v, l)          __builtin_बहु_शुरू(v, l)
#घोषणा बहु_पूर्ण(v)               __builtin_बहु_पूर्ण(v)
#घोषणा बहु_तर्क(v, l)            __builtin_बहु_तर्क(v, l)
#घोषणा va_copy(d, s)           __builtin_va_copy(d, s)
#अन्यथा
#समावेश <मानकतर्क.स>
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा ACPI_INLINE             __अंतरभूत__

/* Function name is used क्रम debug output. Non-ANSI, compiler-dependent */

#घोषणा ACPI_GET_FUNCTION_NAME          __func__

/*
 * This macro is used to tag functions as "printf-like" because
 * some compilers (like GCC) can catch म_लिखो क्रमmat string problems.
 */
#घोषणा ACPI_PRINTF_LIKE(c) __attribute__ ((__क्रमmat__ (__म_लिखो__, c, c+1)))

/*
 * Some compilers complain about unused variables. Someबार we करोn't want to
 * use all the variables (क्रम example, _acpi_module_name). This allows us
 * to tell the compiler warning in a per-variable manner that a variable
 * is unused.
 */
#घोषणा ACPI_UNUSED_VAR __attribute__ ((unused))

/* GCC supports __VA_ARGS__ in macros */

#घोषणा COMPILER_VA_MACRO               1

/* GCC supports native multiply/shअगरt on 32-bit platक्रमms */

#घोषणा ACPI_USE_NATIVE_MATH64

/* GCC did not support __has_attribute until 5.1. */

#अगर_अघोषित __has_attribute
#घोषणा __has_attribute(x) 0
#पूर्ण_अगर

/*
 * Explicitly mark पूर्णांकentional explicit fallthrough to silence
 * -Wimplicit-fallthrough in GCC 7.1+.
 */

#अगर __has_attribute(__fallthrough__)
#घोषणा ACPI_FALLTHROUGH __attribute__((__fallthrough__))
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACGCC_H__ */
