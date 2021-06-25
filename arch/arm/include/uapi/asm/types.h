<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_TYPES_H
#घोषणा _UAPI_ASM_TYPES_H

#समावेश <यंत्र-generic/पूर्णांक-ll64.h>

/*
 * The C99 types uपूर्णांकXX_t that are usually defined in 'stdint.h' are not as
 * unambiguous on ARM as you would expect. For the types below, there is a
 * dअगरference on ARM between GCC built क्रम bare metal ARM, GCC built क्रम glibc
 * and the kernel itself, which results in build errors अगर you try to build with
 * -fमुक्तstanding and include 'stdint.h' (such as when you include 'arm_neon.h'
 * in order to use NEON पूर्णांकrinsics)
 *
 * As the प्रकारs क्रम these types in 'stdint.h' are based on builtin defines
 * supplied by GCC, we can tweak these to align with the kernel's idea of those
 * types, so 'linux/types.h' and 'stdint.h' can be safely included from the same
 * source file (provided that -fमुक्तstanding is used).
 *
 *                    पूर्णांक32_t         uपूर्णांक32_t               uपूर्णांकptr_t
 * bare metal GCC     दीर्घ            अचिन्हित दीर्घ          अचिन्हित पूर्णांक
 * glibc GCC          पूर्णांक             अचिन्हित पूर्णांक           अचिन्हित पूर्णांक
 * kernel             पूर्णांक             अचिन्हित पूर्णांक           अचिन्हित दीर्घ
 */

#अगर_घोषित __INT32_TYPE__
#अघोषित __INT32_TYPE__
#घोषणा __INT32_TYPE__		पूर्णांक
#पूर्ण_अगर

#अगर_घोषित __UINT32_TYPE__
#अघोषित __UINT32_TYPE__
#घोषणा __UINT32_TYPE__	अचिन्हित पूर्णांक
#पूर्ण_अगर

#अगर_घोषित __UINTPTR_TYPE__
#अघोषित __UINTPTR_TYPE__
#घोषणा __UINTPTR_TYPE__	अचिन्हित दीर्घ
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ASM_TYPES_H */
