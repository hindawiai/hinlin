<शैली गुरु>
/*
 * Copyright 2010 Red Hat Inc.
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

#समावेश <nvअगर/class.h>

स्थिर u8 *
nv50_mmu_kind(काष्ठा nvkm_mmu *base, पूर्णांक *count, u8 *invalid)
अणु
	/* 0x01: no bank swizzle
	 * 0x02: bank swizzled
	 * 0x7f: invalid
	 *
	 * 0x01/0x02 are values understood by the VRAM allocator,
	 * and are required to aव्योम mixing the two types within
	 * a certain range.
	 */
	अटल स्थिर u8
	kind[128] = अणु
		0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x00 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x10 */
		0x02, 0x02, 0x02, 0x02, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, /* 0x20 */
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x7f,
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, /* 0x30 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, /* 0x40 */
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x7f, 0x7f,
		0x7f, 0x7f, 0x7f, 0x7f, 0x01, 0x01, 0x01, 0x7f, /* 0x50 */
		0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7f, /* 0x60 */
		0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
		0x01, 0x7f, 0x02, 0x7f, 0x01, 0x7f, 0x02, 0x7f, /* 0x70 */
		0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x7f, 0x7f
	पूर्ण;
	*count = ARRAY_SIZE(kind);
	*invalid = 0x7f;
	वापस kind;
पूर्ण

अटल स्थिर काष्ठा nvkm_mmu_func
nv50_mmu = अणु
	.dma_bits = 40,
	.mmu = अणुअणु -1, -1, NVIF_CLASS_MMU_NV50पूर्णपूर्ण,
	.mem = अणुअणु -1,  0, NVIF_CLASS_MEM_NV50पूर्ण, nv50_mem_new, nv50_mem_map पूर्ण,
	.vmm = अणुअणु -1, -1, NVIF_CLASS_VMM_NV50पूर्ण, nv50_vmm_new, false, 0x1400 पूर्ण,
	.kind = nv50_mmu_kind,
पूर्ण;

पूर्णांक
nv50_mmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_mmu **pmmu)
अणु
	वापस nvkm_mmu_new_(&nv50_mmu, device, type, inst, pmmu);
पूर्ण
