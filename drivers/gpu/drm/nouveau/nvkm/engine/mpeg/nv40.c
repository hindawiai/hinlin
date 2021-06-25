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
#समावेश "nv31.h"

#समावेश <subdev/insपंचांगem.h>

#समावेश <nvअगर/class.h>

bool
nv40_mpeg_mthd_dma(काष्ठा nvkm_device *device, u32 mthd, u32 data)
अणु
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	काष्ठा nv31_mpeg *mpeg = nv31_mpeg(device->mpeg);
	काष्ठा nvkm_subdev *subdev = &mpeg->engine.subdev;
	u32 inst = data << 4;
	u32 dma0 = nvkm_insपंचांगem_rd32(imem, inst + 0);
	u32 dma1 = nvkm_insपंचांगem_rd32(imem, inst + 4);
	u32 dma2 = nvkm_insपंचांगem_rd32(imem, inst + 8);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;

	/* only allow linear DMA objects */
	अगर (!(dma0 & 0x00002000)) अणु
		nvkm_error(subdev, "inst %08x dma0 %08x dma1 %08x dma2 %08x\n",
			   inst, dma0, dma1, dma2);
		वापस false;
	पूर्ण

	अगर (mthd == 0x0190) अणु
		/* DMA_CMD */
		nvkm_mask(device, 0x00b300, 0x00030000, (dma0 & 0x00030000));
		nvkm_wr32(device, 0x00b334, base);
		nvkm_wr32(device, 0x00b324, size);
	पूर्ण अन्यथा
	अगर (mthd == 0x01a0) अणु
		/* DMA_DATA */
		nvkm_mask(device, 0x00b300, 0x000c0000, (dma0 & 0x00030000) << 2);
		nvkm_wr32(device, 0x00b360, base);
		nvkm_wr32(device, 0x00b364, size);
	पूर्ण अन्यथा अणु
		/* DMA_IMAGE, VRAM only */
		अगर (dma0 & 0x00030000)
			वापस false;

		nvkm_wr32(device, 0x00b370, base);
		nvkm_wr32(device, 0x00b374, size);
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा nv31_mpeg_func
nv40_mpeg = अणु
	.mthd_dma = nv40_mpeg_mthd_dma,
पूर्ण;

पूर्णांक
nv40_mpeg_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_engine **pmpeg)
अणु
	वापस nv31_mpeg_new_(&nv40_mpeg, device, type, inst, pmpeg);
पूर्ण
