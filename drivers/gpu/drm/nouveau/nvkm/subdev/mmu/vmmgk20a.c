<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
#समावेश "vmm.h"

#समावेश <core/memory.h>

पूर्णांक
gk20a_vmm_aper(क्रमागत nvkm_memory_target target)
अणु
	चयन (target) अणु
	हाल NVKM_MEM_TARGET_NCOH: वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
gk20a_vmm_17 = अणु
	.join = gf100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 17, &gk104_vmm_desc_17_17[0], NVKM_VMM_PAGE_xxHC पूर्ण,
		अणु 12, &gk104_vmm_desc_17_12[0], NVKM_VMM_PAGE_xxHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_func
gk20a_vmm_16 = अणु
	.join = gf100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 16, &gk104_vmm_desc_16_16[0], NVKM_VMM_PAGE_xxHC पूर्ण,
		अणु 12, &gk104_vmm_desc_16_12[0], NVKM_VMM_PAGE_xxHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gk20a_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gf100_vmm_new_(&gk20a_vmm_16, &gk20a_vmm_17, mmu, managed, addr,
			      size, argv, argc, key, name, pvmm);
पूर्ण
