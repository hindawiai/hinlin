<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/fpu/api.h>

#समावेश "i915_memcpy.h"

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)
#घोषणा CI_BUG_ON(expr) BUG_ON(expr)
#अन्यथा
#घोषणा CI_BUG_ON(expr) BUILD_BUG_ON_INVALID(expr)
#पूर्ण_अगर

अटल DEFINE_STATIC_KEY_FALSE(has_movntdqa);

अटल व्योम __स_नकल_ntdqa(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	kernel_fpu_begin();

	जबतक (len >= 4) अणु
		यंत्र("movntdqa   (%0), %%xmm0\n"
		    "movntdqa 16(%0), %%xmm1\n"
		    "movntdqa 32(%0), %%xmm2\n"
		    "movntdqa 48(%0), %%xmm3\n"
		    "movaps %%xmm0,   (%1)\n"
		    "movaps %%xmm1, 16(%1)\n"
		    "movaps %%xmm2, 32(%1)\n"
		    "movaps %%xmm3, 48(%1)\n"
		    :: "r" (src), "r" (dst) : "memory");
		src += 64;
		dst += 64;
		len -= 4;
	पूर्ण
	जबतक (len--) अणु
		यंत्र("movntdqa (%0), %%xmm0\n"
		    "movaps %%xmm0, (%1)\n"
		    :: "r" (src), "r" (dst) : "memory");
		src += 16;
		dst += 16;
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम __स_नकल_ntdqu(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	kernel_fpu_begin();

	जबतक (len >= 4) अणु
		यंत्र("movntdqa   (%0), %%xmm0\n"
		    "movntdqa 16(%0), %%xmm1\n"
		    "movntdqa 32(%0), %%xmm2\n"
		    "movntdqa 48(%0), %%xmm3\n"
		    "movups %%xmm0,   (%1)\n"
		    "movups %%xmm1, 16(%1)\n"
		    "movups %%xmm2, 32(%1)\n"
		    "movups %%xmm3, 48(%1)\n"
		    :: "r" (src), "r" (dst) : "memory");
		src += 64;
		dst += 64;
		len -= 4;
	पूर्ण
	जबतक (len--) अणु
		यंत्र("movntdqa (%0), %%xmm0\n"
		    "movups %%xmm0, (%1)\n"
		    :: "r" (src), "r" (dst) : "memory");
		src += 16;
		dst += 16;
	पूर्ण

	kernel_fpu_end();
पूर्ण

/**
 * i915_स_नकल_from_wc: perक्रमm an accelerated *aligned* पढ़ो from WC
 * @dst: destination poपूर्णांकer
 * @src: source poपूर्णांकer
 * @len: how many bytes to copy
 *
 * i915_स_नकल_from_wc copies @len bytes from @src to @dst using
 * non-temporal inकाष्ठाions where available. Note that all arguments
 * (@src, @dst) must be aligned to 16 bytes and @len must be a multiple
 * of 16.
 *
 * To test whether accelerated पढ़ोs from WC are supported, use
 * i915_स_नकल_from_wc(शून्य, शून्य, 0);
 *
 * Returns true अगर the copy was successful, false अगर the preconditions
 * are not met.
 */
bool i915_स_नकल_from_wc(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	अगर (unlikely(((अचिन्हित दीर्घ)dst | (अचिन्हित दीर्घ)src | len) & 15))
		वापस false;

	अगर (अटल_branch_likely(&has_movntdqa)) अणु
		अगर (likely(len))
			__स_नकल_ntdqa(dst, src, len >> 4);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * i915_unaligned_स_नकल_from_wc: perक्रमm a mostly accelerated पढ़ो from WC
 * @dst: destination poपूर्णांकer
 * @src: source poपूर्णांकer
 * @len: how many bytes to copy
 *
 * Like i915_स_नकल_from_wc(), the unaligned variant copies @len bytes from
 * @src to @dst using * non-temporal inकाष्ठाions where available, but
 * accepts that its arguments may not be aligned, but are valid क्रम the
 * potential 16-byte पढ़ो past the end.
 */
व्योम i915_unaligned_स_नकल_from_wc(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ addr;

	CI_BUG_ON(!i915_has_स_नकल_from_wc());

	addr = (अचिन्हित दीर्घ)src;
	अगर (!IS_ALIGNED(addr, 16)) अणु
		अचिन्हित दीर्घ x = min(ALIGN(addr, 16) - addr, len);

		स_नकल(dst, src, x);

		len -= x;
		dst += x;
		src += x;
	पूर्ण

	अगर (likely(len))
		__स_नकल_ntdqu(dst, src, DIV_ROUND_UP(len, 16));
पूर्ण

व्योम i915_स_नकल_init_early(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * Some hypervisors (e.g. KVM) करोn't support VEX-prefix inकाष्ठाions
	 * emulation. So करोn't enable movntdqa in hypervisor guest.
	 */
	अगर (अटल_cpu_has(X86_FEATURE_XMM4_1) &&
	    !boot_cpu_has(X86_FEATURE_HYPERVISOR))
		अटल_branch_enable(&has_movntdqa);
पूर्ण
