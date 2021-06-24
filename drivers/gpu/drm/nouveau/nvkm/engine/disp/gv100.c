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
gv100_disp_wndw_cnt(काष्ठा nvkm_disp *disp, अचिन्हित दीर्घ *pmask)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	*pmask = nvkm_rd32(device, 0x610064);
	वापस (nvkm_rd32(device, 0x610074) & 0x03f00000) >> 20;
पूर्ण

व्योम
gv100_disp_super(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nv50_disp *disp =
		container_of(work, काष्ठा nv50_disp, supervisor);
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_head *head;
	u32 stat = nvkm_rd32(device, 0x6107a8);
	u32 mask[4];

	nvkm_debug(subdev, "supervisor %d: %08x\n", ffs(disp->super), stat);
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		mask[head->id] = nvkm_rd32(device, 0x6107ac + (head->id * 4));
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
		nvkm_wr32(device, 0x6107ac + (head->id * 4), 0x00000000);
	nvkm_wr32(device, 0x6107a8, 0x80000000);
पूर्ण

अटल व्योम
gv100_disp_exception(काष्ठा nv50_disp *disp, पूर्णांक chid)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611020 + (chid * 12));
	u32 type = (stat & 0x00007000) >> 12;
	u32 mthd = (stat & 0x00000fff) << 2;
	स्थिर काष्ठा nvkm_क्रमागत *reason =
		nvkm_क्रमागत_find(nv50_disp_पूर्णांकr_error_type, type);

	/*TODO: Suspect 33->41 are क्रम WRBK channel exceptions, but we
	 *      करोn't support those currently.
	 *
	 *      CORE+WIN CHIDs map directly to the FE_EXCEPT() slots.
	 */
	अगर (chid <= 32) अणु
		u32 data = nvkm_rd32(device, 0x611024 + (chid * 12));
		u32 code = nvkm_rd32(device, 0x611028 + (chid * 12));
		nvkm_error(subdev, "chid %d stat %08x reason %d [%s] "
				   "mthd %04x data %08x code %08x\n",
			   chid, stat, type, reason ? reason->name : "",
			   mthd, data, code);
	पूर्ण अन्यथा अणु
		nvkm_error(subdev, "chid %d stat %08x reason %d [%s] "
				   "mthd %04x\n",
			   chid, stat, type, reason ? reason->name : "", mthd);
	पूर्ण

	अगर (chid < ARRAY_SIZE(disp->chan) && disp->chan[chid]) अणु
		चयन (mthd) अणु
		हाल 0x0200:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_ERROR);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x611020 + (chid * 12), 0x90000000);
पूर्ण

अटल व्योम
gv100_disp_पूर्णांकr_ctrl_disp(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611c30);

	अगर (stat & 0x00000007) अणु
		disp->super = (stat & 0x00000007);
		queue_work(disp->wq, &disp->supervisor);
		nvkm_wr32(device, 0x611860, disp->super);
		stat &= ~0x00000007;
	पूर्ण

	/*TODO: I would guess this is VBIOS_RELEASE, however, NFI how to
	 *      ACK it, nor करोes RM appear to bother.
	 */
	अगर (stat & 0x00000008)
		stat &= ~0x00000008;

	अगर (stat & 0x00000080) अणु
		u32 error = nvkm_mask(device, 0x611848, 0x00000000, 0x00000000);
		nvkm_warn(subdev, "error %08x\n", error);
		stat &= ~0x00000080;
	पूर्ण

	अगर (stat & 0x00000100) अणु
		अचिन्हित दीर्घ wndws = nvkm_rd32(device, 0x611858);
		अचिन्हित दीर्घ other = nvkm_rd32(device, 0x61185c);
		पूर्णांक wndw;

		nvkm_wr32(device, 0x611858, wndws);
		nvkm_wr32(device, 0x61185c, other);

		/* AWAKEN_OTHER_CORE. */
		अगर (other & 0x00000001)
			nv50_disp_chan_uevent_send(disp, 0);

		/* AWAKEN_WIN_CH(n). */
		क्रम_each_set_bit(wndw, &wndws, disp->wndw.nr) अणु
			nv50_disp_chan_uevent_send(disp, 1 + wndw);
		पूर्ण
	पूर्ण

	अगर (stat)
		nvkm_warn(subdev, "ctrl %08x\n", stat);
पूर्ण

अटल व्योम
gv100_disp_पूर्णांकr_exc_other(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611854);
	अचिन्हित दीर्घ mask;
	पूर्णांक head;

	अगर (stat & 0x00000001) अणु
		nvkm_wr32(device, 0x611854, 0x00000001);
		gv100_disp_exception(disp, 0);
		stat &= ~0x00000001;
	पूर्ण

	अगर ((mask = (stat & 0x00ff0000) >> 16)) अणु
		क्रम_each_set_bit(head, &mask, disp->wndw.nr) अणु
			nvkm_wr32(device, 0x611854, 0x00010000 << head);
			gv100_disp_exception(disp, 73 + head);
			stat &= ~(0x00010000 << head);
		पूर्ण
	पूर्ण

	अगर (stat) अणु
		nvkm_warn(subdev, "exception %08x\n", stat);
		nvkm_wr32(device, 0x611854, stat);
	पूर्ण
पूर्ण

अटल व्योम
gv100_disp_पूर्णांकr_exc_winim(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अचिन्हित दीर्घ stat = nvkm_rd32(device, 0x611850);
	पूर्णांक wndw;

	क्रम_each_set_bit(wndw, &stat, disp->wndw.nr) अणु
		nvkm_wr32(device, 0x611850, BIT(wndw));
		gv100_disp_exception(disp, 33 + wndw);
		stat &= ~BIT(wndw);
	पूर्ण

	अगर (stat) अणु
		nvkm_warn(subdev, "wimm %08x\n", (u32)stat);
		nvkm_wr32(device, 0x611850, stat);
	पूर्ण
पूर्ण

अटल व्योम
gv100_disp_पूर्णांकr_exc_win(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अचिन्हित दीर्घ stat = nvkm_rd32(device, 0x61184c);
	पूर्णांक wndw;

	क्रम_each_set_bit(wndw, &stat, disp->wndw.nr) अणु
		nvkm_wr32(device, 0x61184c, BIT(wndw));
		gv100_disp_exception(disp, 1 + wndw);
		stat &= ~BIT(wndw);
	पूर्ण

	अगर (stat) अणु
		nvkm_warn(subdev, "wndw %08x\n", (u32)stat);
		nvkm_wr32(device, 0x61184c, stat);
	पूर्ण
पूर्ण

अटल व्योम
gv100_disp_पूर्णांकr_head_timing(काष्ठा nv50_disp *disp, पूर्णांक head)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611800 + (head * 0x04));

	/* LAST_DATA, LOADV. */
	अगर (stat & 0x00000003) अणु
		nvkm_wr32(device, 0x611800 + (head * 0x04), stat & 0x00000003);
		stat &= ~0x00000003;
	पूर्ण

	अगर (stat & 0x00000004) अणु
		nvkm_disp_vblank(&disp->base, head);
		nvkm_wr32(device, 0x611800 + (head * 0x04), 0x00000004);
		stat &= ~0x00000004;
	पूर्ण

	अगर (stat) अणु
		nvkm_warn(subdev, "head %08x\n", stat);
		nvkm_wr32(device, 0x611800 + (head * 0x04), stat);
	पूर्ण
पूर्ण

व्योम
gv100_disp_पूर्णांकr(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611ec0);
	अचिन्हित दीर्घ mask;
	पूर्णांक head;

	अगर ((mask = (stat & 0x000000ff))) अणु
		क्रम_each_set_bit(head, &mask, 8) अणु
			gv100_disp_पूर्णांकr_head_timing(disp, head);
			stat &= ~BIT(head);
		पूर्ण
	पूर्ण

	अगर (stat & 0x00000200) अणु
		gv100_disp_पूर्णांकr_exc_win(disp);
		stat &= ~0x00000200;
	पूर्ण

	अगर (stat & 0x00000400) अणु
		gv100_disp_पूर्णांकr_exc_winim(disp);
		stat &= ~0x00000400;
	पूर्ण

	अगर (stat & 0x00000800) अणु
		gv100_disp_पूर्णांकr_exc_other(disp);
		stat &= ~0x00000800;
	पूर्ण

	अगर (stat & 0x00001000) अणु
		gv100_disp_पूर्णांकr_ctrl_disp(disp);
		stat &= ~0x00001000;
	पूर्ण

	अगर (stat)
		nvkm_warn(subdev, "intr %08x\n", stat);
पूर्ण

व्योम
gv100_disp_fini(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	nvkm_wr32(device, 0x611db0, 0x00000000);
पूर्ण

अटल पूर्णांक
gv100_disp_init(काष्ठा nv50_disp *disp)
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
	पंचांगp = nvkm_rd32(device, 0x610068);
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
		क्रम (j = 0; j < 6 * 4; j += 4) अणु
			पंचांगp = nvkm_rd32(device, 0x616100 + (id * 0x800) + j);
			nvkm_wr32(device, 0x640030 + (id * 0x20) + j, पंचांगp);
		पूर्ण
	पूर्ण

	/* Winकरोw capabilities. */
	क्रम (i = 0; i < disp->wndw.nr; i++) अणु
		nvkm_mask(device, 0x640004, 1 << i, 1 << i);
		क्रम (j = 0; j < 6 * 4; j += 4) अणु
			पंचांगp = nvkm_rd32(device, 0x630050 + (i * 0x800) + j);
			nvkm_wr32(device, 0x6401e4 + (i * 0x20) + j, पंचांगp);
		पूर्ण
	पूर्ण

	/* IHUB capabilities. */
	क्रम (i = 0; i < 4; i++) अणु
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
gv100_disp = अणु
	.init = gv100_disp_init,
	.fini = gv100_disp_fini,
	.पूर्णांकr = gv100_disp_पूर्णांकr,
	.uevent = &gv100_disp_chan_uevent,
	.super = gv100_disp_super,
	.root = &gv100_disp_root_oclass,
	.wndw = अणु .cnt = gv100_disp_wndw_cnt पूर्ण,
	.head = अणु .cnt = gv100_head_cnt, .new = gv100_head_new पूर्ण,
	.sor = अणु .cnt = gv100_sor_cnt, .new = gv100_sor_new पूर्ण,
	.ramht_size = 0x2000,
पूर्ण;

पूर्णांक
gv100_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&gv100_disp, device, type, inst, pdisp);
पूर्ण
