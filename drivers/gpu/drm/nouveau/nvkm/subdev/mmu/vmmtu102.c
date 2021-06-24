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

#समावेश <subdev/समयr.h>

अटल व्योम
tu102_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक depth)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	u32 type = (5 /* CACHE_LEVEL_UP_TO_PDE3 */ - depth) << 24;

	type |= 0x00000001; /* PAGE_ALL */
	अगर (atomic_पढ़ो(&vmm->engref[NVKM_SUBDEV_BAR]))
		type |= 0x00000004; /* HUB_ONLY */

	mutex_lock(&vmm->mmu->mutex);

	nvkm_wr32(device, 0xb830a0, vmm->pd->pt[0]->addr >> 8);
	nvkm_wr32(device, 0xb830a4, 0x00000000);
	nvkm_wr32(device, 0x100e68, 0x00000000);
	nvkm_wr32(device, 0xb830b0, 0x80000000 | type);

	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0xb830b0) & 0x80000000))
			अवरोध;
	);

	mutex_unlock(&vmm->mmu->mutex);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
tu102_vmm = अणु
	.join = gv100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gp100_vmm_valid,
	.flush = tu102_vmm_flush,
	.mthd = gp100_vmm_mthd,
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
tu102_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gp100_vmm_new_(&tu102_vmm, mmu, managed, addr, size,
			      argv, argc, key, name, pvmm);
पूर्ण
