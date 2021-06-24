<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
 * Copyright 2019 Raptor Engineering, LLC
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित _OS_TYPES_H_
#घोषणा _OS_TYPES_H_

#समावेश <linux/kgdb.h>
#समावेश <linux/kref.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "cgs_common.h"

#अगर defined(__BIG_ENDIAN) && !defined(BIGENDIAN_CPU)
#घोषणा BIGENDIAN_CPU
#या_अगर defined(__LITTLE_ENDIAN) && !defined(LITTLEENDIAN_CPU)
#घोषणा LITTLEENDIAN_CPU
#पूर्ण_अगर

#अघोषित FRAME_SIZE

#घोषणा dm_output_to_console(fmt, ...) DRM_DEBUG_KMS(fmt, ##__VA_ARGS__)

#घोषणा dm_error(fmt, ...) DRM_ERROR(fmt, ##__VA_ARGS__)

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#अगर defined(CONFIG_X86)
#समावेश <यंत्र/fpu/api.h>
#घोषणा DC_FP_START() kernel_fpu_begin()
#घोषणा DC_FP_END() kernel_fpu_end()
#या_अगर defined(CONFIG_PPC64)
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/cputable.h>
#घोषणा DC_FP_START() अणु \
	अगर (cpu_has_feature(CPU_FTR_VSX_COMP)) अणु \
		preempt_disable(); \
		enable_kernel_vsx(); \
	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ALTIVEC_COMP)) अणु \
		preempt_disable(); \
		enable_kernel_altivec(); \
	पूर्ण अन्यथा अगर (!cpu_has_feature(CPU_FTR_FPU_UNAVAILABLE)) अणु \
		preempt_disable(); \
		enable_kernel_fp(); \
	पूर्ण \
पूर्ण
#घोषणा DC_FP_END() अणु \
	अगर (cpu_has_feature(CPU_FTR_VSX_COMP)) अणु \
		disable_kernel_vsx(); \
		preempt_enable(); \
	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ALTIVEC_COMP)) अणु \
		disable_kernel_altivec(); \
		preempt_enable(); \
	पूर्ण अन्यथा अगर (!cpu_has_feature(CPU_FTR_FPU_UNAVAILABLE)) अणु \
		disable_kernel_fp(); \
		preempt_enable(); \
	पूर्ण \
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/*
 *
 * general debug capabilities
 *
 */
#अगर_घोषित CONFIG_DEBUG_KERNEL_DC
#घोषणा dc_अवरोधpoपूर्णांक()		kgdb_अवरोधpoपूर्णांक()
#अन्यथा
#घोषणा dc_अवरोधpoपूर्णांक()		करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा ASSERT_CRITICAL(expr) करो अणु		\
		अगर (WARN_ON(!(expr)))		\
			dc_अवरोधpoपूर्णांक();	\
	पूर्ण जबतक (0)

#घोषणा ASSERT(expr) करो अणु			\
		अगर (WARN_ON_ONCE(!(expr)))	\
			dc_अवरोधpoपूर्णांक();	\
	पूर्ण जबतक (0)

#घोषणा BREAK_TO_DEBUGGER() \
	करो अणु \
		DRM_DEBUG_DRIVER("%s():%d\n", __func__, __LINE__); \
		dc_अवरोधpoपूर्णांक(); \
	पूर्ण जबतक (0)

#घोषणा DC_ERR(...)  करो अणु \
	dm_error(__VA_ARGS__); \
	BREAK_TO_DEBUGGER(); \
पूर्ण जबतक (0)

#पूर्ण_अगर /* _OS_TYPES_H_ */
