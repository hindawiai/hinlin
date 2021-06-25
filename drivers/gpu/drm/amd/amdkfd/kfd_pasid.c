<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/types.h>
#समावेश "kfd_priv.h"
#समावेश "amdgpu_ids.h"

अटल अचिन्हित पूर्णांक pasid_bits = 16;
अटल bool pasids_allocated; /* = false */

bool kfd_set_pasid_limit(अचिन्हित पूर्णांक new_limit)
अणु
	अगर (new_limit < 2)
		वापस false;

	अगर (new_limit < (1U << pasid_bits)) अणु
		अगर (pasids_allocated)
			/* We've alपढ़ोy allocated user PASIDs, too late to
			 * change the limit
			 */
			वापस false;

		जबतक (new_limit < (1U << pasid_bits))
			pasid_bits--;
	पूर्ण

	वापस true;
पूर्ण

अचिन्हित पूर्णांक kfd_get_pasid_limit(व्योम)
अणु
	वापस 1U << pasid_bits;
पूर्ण

u32 kfd_pasid_alloc(व्योम)
अणु
	पूर्णांक r = amdgpu_pasid_alloc(pasid_bits);

	अगर (r > 0) अणु
		pasids_allocated = true;
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम kfd_pasid_मुक्त(u32 pasid)
अणु
	amdgpu_pasid_मुक्त(pasid);
पूर्ण
