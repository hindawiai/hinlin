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
#समावेश "mem.h"
#समावेश "vmm.h"

#समावेश <core/option.h>

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_mmu_func
gv100_mmu = अणु
	.dma_bits = 47,
	.mmu = अणुअणु -1, -1, NVIF_CLASS_MMU_GF100पूर्णपूर्ण,
	.mem = अणुअणु -1,  0, NVIF_CLASS_MEM_GF100पूर्ण, gf100_mem_new, gf100_mem_map पूर्ण,
	.vmm = अणुअणु -1,  0, NVIF_CLASS_VMM_GP100पूर्ण, gv100_vmm_new पूर्ण,
	.kind = gm200_mmu_kind,
	.kind_sys = true,
पूर्ण;

पूर्णांक
gv100_mmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_mmu **pmmu)
अणु
	वापस nvkm_mmu_new_(&gv100_mmu, device, type, inst, pmmu);
पूर्ण
