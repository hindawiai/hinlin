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
#समावेश "nv50.h"
#समावेश "head.h"
#समावेश "ior.h"
#समावेश "channv50.h"
#समावेश "rootnv50.h"

#समावेश <core/ramht.h>
#समावेश <subdev/समयr.h>

व्योम
gf119_disp_super(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nv50_disp *disp =
		container_of(work, काष्ठा nv50_disp, supervisor);
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_head *head;
	u32 mask[4];

	nvkm_debug(subdev, "supervisor %d\n", ffs(disp->super));
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		mask[head->id] = nvkm_rd32(device, 0x6101d4 + (head->id * 0x800));
		HEAD_DBG(head, "%08x", mask[head->id]);
	पूर्ण

	अगर (disp->super & 0x00000001) अणु
		nv50_disp_chan_mthd(disp->chan[0], NV_DBG_DEBUG);
		nv50_disp_super_1(disp);
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(mask[head->id] & 0x00001000))
				जारी;
			nv50_disp_super_1_0(disp, head);
		पूर्ण
	पूर्ण अन्यथा
	अगर (disp->super & 0x00000002) अणु
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(mask[head->id] & 0x00001000))
				जारी;
			nv50_disp_super_2_0(disp, head);
		पूर्ण
		nvkm_outp_route(&disp->base);
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(mask[head->id] & 0x00010000))
				जारी;
			nv50_disp_super_2_1(disp, head);
		पूर्ण
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(mask[head->id] & 0x00001000))
				जारी;
			nv50_disp_super_2_2(disp, head);
		पूर्ण
	पूर्ण अन्यथा
	अगर (disp->super & 0x00000004) अणु
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(mask[head->id] & 0x00001000))
				जारी;
			nv50_disp_super_3_0(disp, head);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(head, &disp->base.head, head)
		nvkm_wr32(device, 0x6101d4 + (head->id * 0x800), 0x00000000);
	nvkm_wr32(device, 0x6101d0, 0x80000000);
पूर्ण

व्योम
gf119_disp_पूर्णांकr_error(काष्ठा nv50_disp *disp, पूर्णांक chid)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x6101f0 + (chid * 12));
	u32 type = (stat & 0x00007000) >> 12;
	u32 mthd = (stat & 0x00000ffc);
	u32 data = nvkm_rd32(device, 0x6101f4 + (chid * 12));
	u32 code = nvkm_rd32(device, 0x6101f8 + (chid * 12));
	स्थिर काष्ठा nvkm_क्रमागत *reason =
		nvkm_क्रमागत_find(nv50_disp_पूर्णांकr_error_type, type);

	nvkm_error(subdev, "chid %d stat %08x reason %d [%s] mthd %04x "
			   "data %08x code %08x\n",
		   chid, stat, type, reason ? reason->name : "",
		   mthd, data, code);

	अगर (chid < ARRAY_SIZE(disp->chan)) अणु
		चयन (mthd) अणु
		हाल 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_ERROR);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x61009c, (1 << chid));
	nvkm_wr32(device, 0x6101f0 + (chid * 12), 0x90000000);
पूर्ण

व्योम
gf119_disp_पूर्णांकr(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_head *head;
	u32 पूर्णांकr = nvkm_rd32(device, 0x610088);

	अगर (पूर्णांकr & 0x00000001) अणु
		u32 stat = nvkm_rd32(device, 0x61008c);
		जबतक (stat) अणु
			पूर्णांक chid = __ffs(stat); stat &= ~(1 << chid);
			nv50_disp_chan_uevent_send(disp, chid);
			nvkm_wr32(device, 0x61008c, 1 << chid);
		पूर्ण
		पूर्णांकr &= ~0x00000001;
	पूर्ण

	अगर (पूर्णांकr & 0x00000002) अणु
		u32 stat = nvkm_rd32(device, 0x61009c);
		पूर्णांक chid = ffs(stat) - 1;
		अगर (chid >= 0)
			disp->func->पूर्णांकr_error(disp, chid);
		पूर्णांकr &= ~0x00000002;
	पूर्ण

	अगर (पूर्णांकr & 0x00100000) अणु
		u32 stat = nvkm_rd32(device, 0x6100ac);
		अगर (stat & 0x00000007) अणु
			disp->super = (stat & 0x00000007);
			queue_work(disp->wq, &disp->supervisor);
			nvkm_wr32(device, 0x6100ac, disp->super);
			stat &= ~0x00000007;
		पूर्ण

		अगर (stat) अणु
			nvkm_warn(subdev, "intr24 %08x\n", stat);
			nvkm_wr32(device, 0x6100ac, stat);
		पूर्ण

		पूर्णांकr &= ~0x00100000;
	पूर्ण

	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		स्थिर u32 hoff = head->id * 0x800;
		u32 mask = 0x01000000 << head->id;
		अगर (mask & पूर्णांकr) अणु
			u32 stat = nvkm_rd32(device, 0x6100bc + hoff);
			अगर (stat & 0x00000001)
				nvkm_disp_vblank(&disp->base, head->id);
			nvkm_mask(device, 0x6100bc + hoff, 0, 0);
			nvkm_rd32(device, 0x6100c0 + hoff);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gf119_disp_fini(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	/* disable all पूर्णांकerrupts */
	nvkm_wr32(device, 0x6100b0, 0x00000000);
पूर्ण

पूर्णांक
gf119_disp_init(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	काष्ठा nvkm_head *head;
	u32 पंचांगp;
	पूर्णांक i;

	/* The below segments of code copying values from one रेजिस्टर to
	 * another appear to inक्रमm EVO of the display capabilities or
	 * something similar.
	 */

	/* ... CRTC caps */
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		स्थिर u32 hoff = head->id * 0x800;
		पंचांगp = nvkm_rd32(device, 0x616104 + hoff);
		nvkm_wr32(device, 0x6101b4 + hoff, पंचांगp);
		पंचांगp = nvkm_rd32(device, 0x616108 + hoff);
		nvkm_wr32(device, 0x6101b8 + hoff, पंचांगp);
		पंचांगp = nvkm_rd32(device, 0x61610c + hoff);
		nvkm_wr32(device, 0x6101bc + hoff, पंचांगp);
	पूर्ण

	/* ... DAC caps */
	क्रम (i = 0; i < disp->dac.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61a000 + (i * 0x800));
		nvkm_wr32(device, 0x6101c0 + (i * 0x800), पंचांगp);
	पूर्ण

	/* ... SOR caps */
	क्रम (i = 0; i < disp->sor.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61c000 + (i * 0x800));
		nvkm_wr32(device, 0x6301c4 + (i * 0x800), पंचांगp);
	पूर्ण

	/* steal display away from vbios, or something like that */
	अगर (nvkm_rd32(device, 0x6100ac) & 0x00000100) अणु
		nvkm_wr32(device, 0x6100ac, 0x00000100);
		nvkm_mask(device, 0x6194e8, 0x00000001, 0x00000000);
		अगर (nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, 0x6194e8) & 0x00000002))
				अवरोध;
		) < 0)
			वापस -EBUSY;
	पूर्ण

	/* poपूर्णांक at display engine memory area (hash table, objects) */
	nvkm_wr32(device, 0x610010, (disp->inst->addr >> 8) | 9);

	/* enable supervisor पूर्णांकerrupts, disable everything अन्यथा */
	nvkm_wr32(device, 0x610090, 0x00000000);
	nvkm_wr32(device, 0x6100a0, 0x00000000);
	nvkm_wr32(device, 0x6100b0, 0x00000307);

	/* disable underflow reporting, preventing an पूर्णांकermittent issue
	 * on some gk104 boards where the production vbios left this
	 * setting enabled by शेष.
	 *
	 * ftp://करोwnload.nvidia.com/खोलो-gpu-करोc/gk104-disable-underflow-reporting/1/gk104-disable-underflow-reporting.txt
	 */
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		स्थिर u32 hoff = head->id * 0x800;
		nvkm_mask(device, 0x616308 + hoff, 0x00000111, 0x00000010);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_disp_func
gf119_disp = अणु
	.init = gf119_disp_init,
	.fini = gf119_disp_fini,
	.पूर्णांकr = gf119_disp_पूर्णांकr,
	.पूर्णांकr_error = gf119_disp_पूर्णांकr_error,
	.uevent = &gf119_disp_chan_uevent,
	.super = gf119_disp_super,
	.root = &gf119_disp_root_oclass,
	.head = अणु .cnt = gf119_head_cnt, .new = gf119_head_new पूर्ण,
	.dac = अणु .cnt = gf119_dac_cnt, .new = gf119_dac_new पूर्ण,
	.sor = अणु .cnt = gf119_sor_cnt, .new = gf119_sor_new पूर्ण,
पूर्ण;

पूर्णांक
gf119_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&gf119_disp, device, type, inst, pdisp);
पूर्ण
