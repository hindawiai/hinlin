<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2018 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __ASM_NEON_INTRINSICS_H
#घोषणा __ASM_NEON_INTRINSICS_H

#समावेश <यंत्र-generic/पूर्णांक-ll64.h>

/*
 * In the kernel, u64/s64 are [un]चिन्हित दीर्घ दीर्घ, not [un]चिन्हित दीर्घ.
 * So by redefining these macros to the क्रमmer, we can क्रमce gcc-मानक_निवेशt.h
 * to define uपूर्णांक64_t / in64_t in a compatible manner.
 */

#अगर_घोषित __INT64_TYPE__
#अघोषित __INT64_TYPE__
#घोषणा __INT64_TYPE__		दीर्घ दीर्घ
#पूर्ण_अगर

#अगर_घोषित __UINT64_TYPE__
#अघोषित __UINT64_TYPE__
#घोषणा __UINT64_TYPE__		अचिन्हित दीर्घ दीर्घ
#पूर्ण_अगर

/*
 * genksyms chokes on the ARM NEON instrinsics प्रणाली header, but we
 * करोn't export anything it defines anyway, so just disregard when
 * genksyms execute.
 */
#अगर_अघोषित __GENKSYMS__
#समावेश <arm_neon.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_CC_IS_CLANG
#आशय clang diagnostic ignored "-Wincompatible-pointer-types"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_NEON_INTRINSICS_H */
