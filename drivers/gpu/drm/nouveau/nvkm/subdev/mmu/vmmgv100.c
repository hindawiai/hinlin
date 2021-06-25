<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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

#समावेश <subdev/fb.h>
#समावेश <subdev/ltc.h>

#समावेश <nvअगर/अगरc00d.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
gv100_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	u64 data[2], mask;
	पूर्णांक ret = gp100_vmm_join(vmm, inst), i;
	अगर (ret)
		वापस ret;

	nvkm_kmap(inst);
	data[0] = nvkm_ro32(inst, 0x200);
	data[1] = nvkm_ro32(inst, 0x204);
	mask = BIT_ULL(0);

	nvkm_wo32(inst, 0x21c, 0x00000000);

	क्रम (i = 0; i < 64; i++) अणु
		अगर (mask & BIT_ULL(i)) अणु
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), data[1]);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), data[0]);
		पूर्ण अन्यथा अणु
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), 0x00000001);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), 0x00000001);
		पूर्ण
		nvkm_wo32(inst, 0x2a8 + (i * 0x10), 0x00000000);
	पूर्ण

	nvkm_wo32(inst, 0x298, lower_32_bits(mask));
	nvkm_wo32(inst, 0x29c, upper_32_bits(mask));
	nvkm_करोne(inst);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
gv100_vmm = अणु
	.join = gv100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gp100_vmm_valid,
	.flush = gp100_vmm_flush,
	.mthd = gp100_vmm_mthd,
	.invalidate_pdb = gp100_vmm_invalidate_pdb,
	.page = अणु
		अणु 47, &gp100_vmm_desc_16[4], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 38, &gp100_vmm_desc_16[3], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 29, &gp100_vmm_desc_16[2], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 21, &gp100_vmm_desc_16[1], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 16, &gp100_vmm_desc_16[0], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 12, &gp100_vmm_desc_12[0], NVKM_VMM_PAGE_SVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gv100_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gp100_vmm_new_(&gv100_vmm, mmu, managed, addr, size,
			      argv, argc, key, name, pvmm);
पूर्ण
