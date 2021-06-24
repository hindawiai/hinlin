<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "mem.h"
#समावेश "vmm.h"

#समावेश <core/option.h>

#समावेश <nvअगर/class.h>

अटल व्योम
nv41_mmu_init(काष्ठा nvkm_mmu *mmu)
अणु
	काष्ठा nvkm_device *device = mmu->subdev.device;
	nvkm_wr32(device, 0x100800, 0x00000002 | mmu->vmm->pd->pt[0]->addr);
	nvkm_mask(device, 0x10008c, 0x00000100, 0x00000100);
	nvkm_wr32(device, 0x100820, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_mmu_func
nv41_mmu = अणु
	.init = nv41_mmu_init,
	.dma_bits = 39,
	.mmu = अणुअणु -1, -1, NVIF_CLASS_MMU_NV04पूर्णपूर्ण,
	.mem = अणुअणु -1, -1, NVIF_CLASS_MEM_NV04पूर्ण, nv04_mem_new, nv04_mem_map पूर्ण,
	.vmm = अणुअणु -1, -1, NVIF_CLASS_VMM_NV04पूर्ण, nv41_vmm_new, true पूर्ण,
पूर्ण;

पूर्णांक
nv41_mmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_mmu **pmmu)
अणु
	अगर (device->type == NVKM_DEVICE_AGP ||
	    !nvkm_boolopt(device->cfgopt, "NvPCIE", true))
		वापस nv04_mmu_new(device, type, inst, pmmu);

	वापस nvkm_mmu_new_(&nv41_mmu, device, type, inst, pmmu);
पूर्ण
