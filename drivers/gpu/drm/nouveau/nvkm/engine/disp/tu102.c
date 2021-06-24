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
#समावेश "nv50.h"
#समावेश "head.h"
#समावेश "ior.h"
#समावेश "channv50.h"
#समावेश "rootnv50.h"

#समावेश <core/gpuobj.h>
#समावेश <subdev/समयr.h>

पूर्णांक
tu102_disp_init(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	काष्ठा nvkm_head *head;
	पूर्णांक i, j;
	u32 पंचांगp;

	/* Claim ownership of display. */
	अगर (nvkm_rd32(device, 0x6254e8) & 0x00000002) अणु
		nvkm_mask(device, 0x6254e8, 0x00000001, 0x00000000);
		अगर (nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, 0x6254e8) & 0x00000002))
				अवरोध;
		) < 0)
			वापस -EBUSY;
	पूर्ण

	/* Lock pin capabilities. */
	पंचांगp = 0x00000021; /*XXX*/
	nvkm_wr32(device, 0x640008, पंचांगp);

	/* SOR capabilities. */
	क्रम (i = 0; i < disp->sor.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61c000 + (i * 0x800));
		nvkm_mask(device, 0x640000, 0x00000100 << i, 0x00000100 << i);
		nvkm_wr32(device, 0x640144 + (i * 0x08), पंचांगp);
	पूर्ण

	/* Head capabilities. */
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		स्थिर पूर्णांक id = head->id;

		/* RG. */
		पंचांगp = nvkm_rd32(device, 0x616300 + (id * 0x800));
		nvkm_wr32(device, 0x640048 + (id * 0x020), पंचांगp);

		/* POSTCOMP. */
		क्रम (j = 0; j < 5 * 4; j += 4) अणु
			पंचांगp = nvkm_rd32(device, 0x616140 + (id * 0x800) + j);
			nvkm_wr32(device, 0x640680 + (id * 0x20) + j, पंचांगp);
		पूर्ण
	पूर्ण

	/* Winकरोw capabilities. */
	क्रम (i = 0; i < disp->wndw.nr; i++) अणु
		nvkm_mask(device, 0x640004, 1 << i, 1 << i);
		क्रम (j = 0; j < 6 * 4; j += 4) अणु
			पंचांगp = nvkm_rd32(device, 0x630100 + (i * 0x800) + j);
			nvkm_mask(device, 0x640780 + (i * 0x20) + j, 0xffffffff, पंचांगp);
		पूर्ण
		nvkm_mask(device, 0x64000c, 0x00000100, 0x00000100);
	पूर्ण

	/* IHUB capabilities. */
	क्रम (i = 0; i < 3; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x62e000 + (i * 0x04));
		nvkm_wr32(device, 0x640010 + (i * 0x04), पंचांगp);
	पूर्ण

	nvkm_mask(device, 0x610078, 0x00000001, 0x00000001);

	/* Setup instance memory. */
	चयन (nvkm_memory_target(disp->inst->memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM: पंचांगp = 0x00000001; अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: पंचांगp = 0x00000002; अवरोध;
	हाल NVKM_MEM_TARGET_HOST: पंचांगp = 0x00000003; अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	nvkm_wr32(device, 0x610010, 0x00000008 | पंचांगp);
	nvkm_wr32(device, 0x610014, disp->inst->addr >> 16);

	/* CTRL_DISP: AWAKEN, ERROR, SUPERVISOR[1-3]. */
	nvkm_wr32(device, 0x611cf0, 0x00000187); /* MSK. */
	nvkm_wr32(device, 0x611db0, 0x00000187); /* EN. */

	/* EXC_OTHER: CURSn, CORE. */
	nvkm_wr32(device, 0x611cec, disp->head.mask << 16 |
				    0x00000001); /* MSK. */
	nvkm_wr32(device, 0x611dac, 0x00000000); /* EN. */

	/* EXC_WINIM. */
	nvkm_wr32(device, 0x611ce8, disp->wndw.mask); /* MSK. */
	nvkm_wr32(device, 0x611da8, 0x00000000); /* EN. */

	/* EXC_WIN. */
	nvkm_wr32(device, 0x611ce4, disp->wndw.mask); /* MSK. */
	nvkm_wr32(device, 0x611da4, 0x00000000); /* EN. */

	/* HEAD_TIMING(n): VBLANK. */
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		स्थिर u32 hoff = head->id * 4;
		nvkm_wr32(device, 0x611cc0 + hoff, 0x00000004); /* MSK. */
		nvkm_wr32(device, 0x611d80 + hoff, 0x00000000); /* EN. */
	पूर्ण

	/* OR. */
	nvkm_wr32(device, 0x611cf4, 0x00000000); /* MSK. */
	nvkm_wr32(device, 0x611db4, 0x00000000); /* EN. */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_disp_func
tu102_disp = अणु
	.init = tu102_disp_init,
	.fini = gv100_disp_fini,
	.पूर्णांकr = gv100_disp_पूर्णांकr,
	.uevent = &gv100_disp_chan_uevent,
	.super = gv100_disp_super,
	.root = &tu102_disp_root_oclass,
	.wndw = अणु .cnt = gv100_disp_wndw_cnt पूर्ण,
	.head = अणु .cnt = gv100_head_cnt, .new = gv100_head_new पूर्ण,
	.sor = अणु .cnt = gv100_sor_cnt, .new = tu102_sor_new पूर्ण,
	.ramht_size = 0x2000,
पूर्ण;

पूर्णांक
tu102_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&tu102_disp, device, type, inst, pdisp);
पूर्ण
