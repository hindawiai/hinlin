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

#समावेश <core/client.h>
#समावेश <core/ramht.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/disp.h>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/devinit.h>
#समावेश <subdev/समयr.h>

अटल स्थिर काष्ठा nvkm_disp_oclass *
nv50_disp_root_(काष्ठा nvkm_disp *base)
अणु
	वापस nv50_disp(base)->func->root;
पूर्ण

अटल व्योम
nv50_disp_पूर्णांकr_(काष्ठा nvkm_disp *base)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);
	disp->func->पूर्णांकr(disp);
पूर्ण

अटल व्योम
nv50_disp_fini_(काष्ठा nvkm_disp *base)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);
	disp->func->fini(disp);
पूर्ण

अटल पूर्णांक
nv50_disp_init_(काष्ठा nvkm_disp *base)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);
	वापस disp->func->init(disp);
पूर्ण

अटल व्योम *
nv50_disp_dtor_(काष्ठा nvkm_disp *base)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);

	nvkm_ramht_del(&disp->ramht);
	nvkm_gpuobj_del(&disp->inst);

	nvkm_event_fini(&disp->uevent);
	अगर (disp->wq)
		destroy_workqueue(disp->wq);

	वापस disp;
पूर्ण

अटल पूर्णांक
nv50_disp_oneinit_(काष्ठा nvkm_disp *base)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);
	स्थिर काष्ठा nv50_disp_func *func = disp->func;
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ret, i;

	अगर (func->wndw.cnt) अणु
		disp->wndw.nr = func->wndw.cnt(&disp->base, &disp->wndw.mask);
		nvkm_debug(subdev, "Window(s): %d (%08lx)\n",
			   disp->wndw.nr, disp->wndw.mask);
	पूर्ण

	disp->head.nr = func->head.cnt(&disp->base, &disp->head.mask);
	nvkm_debug(subdev, "  Head(s): %d (%02lx)\n",
		   disp->head.nr, disp->head.mask);
	क्रम_each_set_bit(i, &disp->head.mask, disp->head.nr) अणु
		ret = func->head.new(&disp->base, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (func->dac.cnt) अणु
		disp->dac.nr = func->dac.cnt(&disp->base, &disp->dac.mask);
		nvkm_debug(subdev, "   DAC(s): %d (%02lx)\n",
			   disp->dac.nr, disp->dac.mask);
		क्रम_each_set_bit(i, &disp->dac.mask, disp->dac.nr) अणु
			ret = func->dac.new(&disp->base, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (func->pior.cnt) अणु
		disp->pior.nr = func->pior.cnt(&disp->base, &disp->pior.mask);
		nvkm_debug(subdev, "  PIOR(s): %d (%02lx)\n",
			   disp->pior.nr, disp->pior.mask);
		क्रम_each_set_bit(i, &disp->pior.mask, disp->pior.nr) अणु
			ret = func->pior.new(&disp->base, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	disp->sor.nr = func->sor.cnt(&disp->base, &disp->sor.mask);
	nvkm_debug(subdev, "   SOR(s): %d (%02lx)\n",
		   disp->sor.nr, disp->sor.mask);
	क्रम_each_set_bit(i, &disp->sor.mask, disp->sor.nr) अणु
		ret = func->sor.new(&disp->base, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = nvkm_gpuobj_new(device, 0x10000, 0x10000, false, शून्य,
			      &disp->inst);
	अगर (ret)
		वापस ret;

	वापस nvkm_ramht_new(device, func->ramht_size ? func->ramht_size :
			      0x1000, 0, disp->inst, &disp->ramht);
पूर्ण

अटल स्थिर काष्ठा nvkm_disp_func
nv50_disp_ = अणु
	.dtor = nv50_disp_dtor_,
	.oneinit = nv50_disp_oneinit_,
	.init = nv50_disp_init_,
	.fini = nv50_disp_fini_,
	.पूर्णांकr = nv50_disp_पूर्णांकr_,
	.root = nv50_disp_root_,
पूर्ण;

पूर्णांक
nv50_disp_new_(स्थिर काष्ठा nv50_disp_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_disp **pdisp)
अणु
	काष्ठा nv50_disp *disp;
	पूर्णांक ret;

	अगर (!(disp = kzalloc(माप(*disp), GFP_KERNEL)))
		वापस -ENOMEM;
	disp->func = func;
	*pdisp = &disp->base;

	ret = nvkm_disp_ctor(&nv50_disp_, device, type, inst, &disp->base);
	अगर (ret)
		वापस ret;

	disp->wq = create_singlethपढ़ो_workqueue("nvkm-disp");
	अगर (!disp->wq)
		वापस -ENOMEM;

	INIT_WORK(&disp->supervisor, func->super);

	वापस nvkm_event_init(func->uevent, 1, ARRAY_SIZE(disp->chan),
			       &disp->uevent);
पूर्ण

अटल u32
nv50_disp_super_iedt(काष्ठा nvkm_head *head, काष्ठा nvkm_outp *outp,
		     u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		     काष्ठा nvbios_outp *iedt)
अणु
	काष्ठा nvkm_bios *bios = head->disp->engine.subdev.device->bios;
	स्थिर u8  l = ffs(outp->info.link);
	स्थिर u16 t = outp->info.hasht;
	स्थिर u16 m = (0x0100 << head->id) | (l << 6) | outp->info.or;
	u32 data = nvbios_outp_match(bios, t, m, ver, hdr, cnt, len, iedt);
	अगर (!data)
		OUTP_DBG(outp, "missing IEDT for %04x:%04x", t, m);
	वापस data;
पूर्ण

अटल व्योम
nv50_disp_super_ied_on(काष्ठा nvkm_head *head,
		       काष्ठा nvkm_ior *ior, पूर्णांक id, u32 khz)
अणु
	काष्ठा nvkm_subdev *subdev = &head->disp->engine.subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvkm_outp *outp = ior->asy.outp;
	काष्ठा nvbios_ocfg iedtrs;
	काष्ठा nvbios_outp iedt;
	u8  ver, hdr, cnt, len, flags = 0x00;
	u32 data;

	अगर (!outp) अणु
		IOR_DBG(ior, "nothing to attach");
		वापस;
	पूर्ण

	/* Lookup IED table क्रम the device. */
	data = nv50_disp_super_iedt(head, outp, &ver, &hdr, &cnt, &len, &iedt);
	अगर (!data)
		वापस;

	/* Lookup IEDT runसमय settings क्रम the current configuration. */
	अगर (ior->type == SOR) अणु
		अगर (ior->asy.proto == LVDS) अणु
			अगर (head->asy.or.depth == 24)
				flags |= 0x02;
		पूर्ण
		अगर (ior->asy.link == 3)
			flags |= 0x01;
	पूर्ण

	data = nvbios_ocfg_match(bios, data, ior->asy.proto_evo, flags,
				 &ver, &hdr, &cnt, &len, &iedtrs);
	अगर (!data) अणु
		OUTP_DBG(outp, "missing IEDT RS for %02x:%02x",
			 ior->asy.proto_evo, flags);
		वापस;
	पूर्ण

	/* Execute the OnInt[23] script क्रम the current frequency. */
	data = nvbios_oclk_match(bios, iedtrs.clkcmp[id], khz);
	अगर (!data) अणु
		OUTP_DBG(outp, "missing IEDT RSS %d for %02x:%02x %d khz",
			 id, ior->asy.proto_evo, flags, khz);
		वापस;
	पूर्ण

	nvbios_init(subdev, data,
		init.outp = &outp->info;
		init.or   = ior->id;
		init.link = ior->asy.link;
		init.head = head->id;
	);
पूर्ण

अटल व्योम
nv50_disp_super_ied_off(काष्ठा nvkm_head *head, काष्ठा nvkm_ior *ior, पूर्णांक id)
अणु
	काष्ठा nvkm_outp *outp = ior->arm.outp;
	काष्ठा nvbios_outp iedt;
	u8  ver, hdr, cnt, len;
	u32 data;

	अगर (!outp) अणु
		IOR_DBG(ior, "nothing attached");
		वापस;
	पूर्ण

	data = nv50_disp_super_iedt(head, outp, &ver, &hdr, &cnt, &len, &iedt);
	अगर (!data)
		वापस;

	nvbios_init(&head->disp->engine.subdev, iedt.script[id],
		init.outp = &outp->info;
		init.or   = ior->id;
		init.link = ior->arm.link;
		init.head = head->id;
	);
पूर्ण

अटल काष्ठा nvkm_ior *
nv50_disp_super_ior_asy(काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_ior *ior;
	list_क्रम_each_entry(ior, &head->disp->ior, head) अणु
		अगर (ior->asy.head & (1 << head->id)) अणु
			HEAD_DBG(head, "to %s", ior->name);
			वापस ior;
		पूर्ण
	पूर्ण
	HEAD_DBG(head, "nothing to attach");
	वापस शून्य;
पूर्ण

अटल काष्ठा nvkm_ior *
nv50_disp_super_ior_arm(काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_ior *ior;
	list_क्रम_each_entry(ior, &head->disp->ior, head) अणु
		अगर (ior->arm.head & (1 << head->id)) अणु
			HEAD_DBG(head, "on %s", ior->name);
			वापस ior;
		पूर्ण
	पूर्ण
	HEAD_DBG(head, "nothing attached");
	वापस शून्य;
पूर्ण

व्योम
nv50_disp_super_3_0(काष्ठा nv50_disp *disp, काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_ior *ior;

	/* Determine which OR, अगर any, we're attaching to the head. */
	HEAD_DBG(head, "supervisor 3.0");
	ior = nv50_disp_super_ior_asy(head);
	अगर (!ior)
		वापस;

	/* Execute OnInt3 IED script. */
	nv50_disp_super_ied_on(head, ior, 1, head->asy.hz / 1000);

	/* OR-specअगरic handling. */
	अगर (ior->func->war_3)
		ior->func->war_3(ior);
पूर्ण

अटल व्योम
nv50_disp_super_2_2_dp(काष्ठा nvkm_head *head, काष्ठा nvkm_ior *ior)
अणु
	काष्ठा nvkm_subdev *subdev = &head->disp->engine.subdev;
	स्थिर u32      khz = head->asy.hz / 1000;
	स्थिर u32 linkKBps = ior->dp.bw * 27000;
	स्थिर u32   symbol = 100000;
	पूर्णांक bestTU = 0, bestVTUi = 0, bestVTUf = 0, bestVTUa = 0;
	पूर्णांक TU, VTUi, VTUf, VTUa;
	u64 link_data_rate, link_ratio, unk;
	u32 best_dअगरf = 64 * symbol;
	u64 h, v;

	/* symbols/hblank - algorithm taken from comments in tegra driver */
	h = head->asy.hblanke + head->asy.htotal - head->asy.hblanks - 7;
	h = h * linkKBps;
	करो_भाग(h, khz);
	h = h - (3 * ior->dp.ef) - (12 / ior->dp.nr);

	/* symbols/vblank - algorithm taken from comments in tegra driver */
	v = head->asy.vblanks - head->asy.vblanke - 25;
	v = v * linkKBps;
	करो_भाग(v, khz);
	v = v - ((36 / ior->dp.nr) + 3) - 1;

	ior->func->dp.audio_sym(ior, head->id, h, v);

	/* watermark / activesym */
	link_data_rate = (khz * head->asy.or.depth / 8) / ior->dp.nr;

	/* calculate ratio of packed data rate to link symbol rate */
	link_ratio = link_data_rate * symbol;
	करो_भाग(link_ratio, linkKBps);

	क्रम (TU = 64; ior->func->dp.activesym && TU >= 32; TU--) अणु
		/* calculate average number of valid symbols in each TU */
		u32 tu_valid = link_ratio * TU;
		u32 calc, dअगरf;

		/* find a hw representation क्रम the fraction.. */
		VTUi = tu_valid / symbol;
		calc = VTUi * symbol;
		dअगरf = tu_valid - calc;
		अगर (dअगरf) अणु
			अगर (dअगरf >= (symbol / 2)) अणु
				VTUf = symbol / (symbol - dअगरf);
				अगर (symbol - (VTUf * dअगरf))
					VTUf++;

				अगर (VTUf <= 15) अणु
					VTUa  = 1;
					calc += symbol - (symbol / VTUf);
				पूर्ण अन्यथा अणु
					VTUa  = 0;
					VTUf  = 1;
					calc += symbol;
				पूर्ण
			पूर्ण अन्यथा अणु
				VTUa  = 0;
				VTUf  = min((पूर्णांक)(symbol / dअगरf), 15);
				calc += symbol / VTUf;
			पूर्ण

			dअगरf = calc - tu_valid;
		पूर्ण अन्यथा अणु
			/* no reमुख्यder, but the hw करोesn't like the fractional
			 * part to be zero.  decrement the पूर्णांकeger part and
			 * have the fraction add a whole symbol back
			 */
			VTUa = 0;
			VTUf = 1;
			VTUi--;
		पूर्ण

		अगर (dअगरf < best_dअगरf) अणु
			best_dअगरf = dअगरf;
			bestTU = TU;
			bestVTUa = VTUa;
			bestVTUf = VTUf;
			bestVTUi = VTUi;
			अगर (dअगरf == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ior->func->dp.activesym) अणु
		अगर (!bestTU) अणु
			nvkm_error(subdev, "unable to determine dp config\n");
			वापस;
		पूर्ण
		ior->func->dp.activesym(ior, head->id, bestTU,
					bestVTUa, bestVTUf, bestVTUi);
	पूर्ण अन्यथा अणु
		bestTU = 64;
	पूर्ण

	/* XXX बंद to vbios numbers, but not right */
	unk  = (symbol - link_ratio) * bestTU;
	unk *= link_ratio;
	करो_भाग(unk, symbol);
	करो_भाग(unk, symbol);
	unk += 6;

	ior->func->dp.watermark(ior, head->id, unk);
पूर्ण

व्योम
nv50_disp_super_2_2(काष्ठा nv50_disp *disp, काष्ठा nvkm_head *head)
अणु
	स्थिर u32 khz = head->asy.hz / 1000;
	काष्ठा nvkm_outp *outp;
	काष्ठा nvkm_ior *ior;

	/* Determine which OR, अगर any, we're attaching from the head. */
	HEAD_DBG(head, "supervisor 2.2");
	ior = nv50_disp_super_ior_asy(head);
	अगर (!ior)
		वापस;

	/* For some reason, NVIDIA decided not to:
	 *
	 * A) Give dual-link LVDS a separate EVO protocol, like क्रम TMDS.
	 *  and
	 * B) Use SetControlOutputResource.PixelDepth on LVDS.
	 *
	 * Override the values we usually पढ़ो from HW with the same
	 * data we pass though an ioctl instead.
	 */
	अगर (ior->type == SOR && ior->asy.proto == LVDS) अणु
		head->asy.or.depth = (disp->sor.lvdsconf & 0x0200) ? 24 : 18;
		ior->asy.link      = (disp->sor.lvdsconf & 0x0100) ? 3  : 1;
	पूर्ण

	/* Handle any link training, etc. */
	अगर ((outp = ior->asy.outp) && outp->func->acquire)
		outp->func->acquire(outp);

	/* Execute OnInt2 IED script. */
	nv50_disp_super_ied_on(head, ior, 0, khz);

	/* Program RG घड़ी भागider. */
	head->func->rgclk(head, ior->asy.rgभाग);

	/* Mode-specअगरic पूर्णांकernal DP configuration. */
	अगर (ior->type == SOR && ior->asy.proto == DP)
		nv50_disp_super_2_2_dp(head, ior);

	/* OR-specअगरic handling. */
	ior->func->घड़ी(ior);
	अगर (ior->func->war_2)
		ior->func->war_2(ior);
पूर्ण

व्योम
nv50_disp_super_2_1(काष्ठा nv50_disp *disp, काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_devinit *devinit = disp->base.engine.subdev.device->devinit;
	स्थिर u32 khz = head->asy.hz / 1000;
	HEAD_DBG(head, "supervisor 2.1 - %d khz", khz);
	अगर (khz)
		nvkm_devinit_pll_set(devinit, PLL_VPLL0 + head->id, khz);
पूर्ण

व्योम
nv50_disp_super_2_0(काष्ठा nv50_disp *disp, काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_outp *outp;
	काष्ठा nvkm_ior *ior;

	/* Determine which OR, अगर any, we're detaching from the head. */
	HEAD_DBG(head, "supervisor 2.0");
	ior = nv50_disp_super_ior_arm(head);
	अगर (!ior)
		वापस;

	/* Execute OffInt2 IED script. */
	nv50_disp_super_ied_off(head, ior, 2);

	/* If we're shutting down the OR's only active head, execute
	 * the output path's disable function.
	 */
	अगर (ior->arm.head == (1 << head->id)) अणु
		अगर ((outp = ior->arm.outp) && outp->func->disable)
			outp->func->disable(outp, ior);
	पूर्ण
पूर्ण

व्योम
nv50_disp_super_1_0(काष्ठा nv50_disp *disp, काष्ठा nvkm_head *head)
अणु
	काष्ठा nvkm_ior *ior;

	/* Determine which OR, अगर any, we're detaching from the head. */
	HEAD_DBG(head, "supervisor 1.0");
	ior = nv50_disp_super_ior_arm(head);
	अगर (!ior)
		वापस;

	/* Execute OffInt1 IED script. */
	nv50_disp_super_ied_off(head, ior, 1);
पूर्ण

व्योम
nv50_disp_super_1(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_head *head;
	काष्ठा nvkm_ior *ior;

	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		head->func->state(head, &head->arm);
		head->func->state(head, &head->asy);
	पूर्ण

	list_क्रम_each_entry(ior, &disp->base.ior, head) अणु
		ior->func->state(ior, &ior->arm);
		ior->func->state(ior, &ior->asy);
	पूर्ण
पूर्ण

व्योम
nv50_disp_super(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nv50_disp *disp =
		container_of(work, काष्ठा nv50_disp, supervisor);
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_head *head;
	u32 super = nvkm_rd32(device, 0x610030);

	nvkm_debug(subdev, "supervisor %08x %08x\n", disp->super, super);

	अगर (disp->super & 0x00000010) अणु
		nv50_disp_chan_mthd(disp->chan[0], NV_DBG_DEBUG);
		nv50_disp_super_1(disp);
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(super & (0x00000020 << head->id)))
				जारी;
			अगर (!(super & (0x00000080 << head->id)))
				जारी;
			nv50_disp_super_1_0(disp, head);
		पूर्ण
	पूर्ण अन्यथा
	अगर (disp->super & 0x00000020) अणु
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(super & (0x00000080 << head->id)))
				जारी;
			nv50_disp_super_2_0(disp, head);
		पूर्ण
		nvkm_outp_route(&disp->base);
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(super & (0x00000200 << head->id)))
				जारी;
			nv50_disp_super_2_1(disp, head);
		पूर्ण
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(super & (0x00000080 << head->id)))
				जारी;
			nv50_disp_super_2_2(disp, head);
		पूर्ण
	पूर्ण अन्यथा
	अगर (disp->super & 0x00000040) अणु
		list_क्रम_each_entry(head, &disp->base.head, head) अणु
			अगर (!(super & (0x00000080 << head->id)))
				जारी;
			nv50_disp_super_3_0(disp, head);
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x610030, 0x80000000);
पूर्ण

स्थिर काष्ठा nvkm_क्रमागत
nv50_disp_पूर्णांकr_error_type[] = अणु
	अणु 0, "NONE" पूर्ण,
	अणु 1, "PUSHBUFFER_ERR" पूर्ण,
	अणु 2, "TRAP" पूर्ण,
	अणु 3, "RESERVED_METHOD" पूर्ण,
	अणु 4, "INVALID_ARG" पूर्ण,
	अणु 5, "INVALID_STATE" पूर्ण,
	अणु 7, "UNRESOLVABLE_HANDLE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
nv50_disp_पूर्णांकr_error_code[] = अणु
	अणु 0x00, "" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv50_disp_पूर्णांकr_error(काष्ठा nv50_disp *disp, पूर्णांक chid)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 data = nvkm_rd32(device, 0x610084 + (chid * 0x08));
	u32 addr = nvkm_rd32(device, 0x610080 + (chid * 0x08));
	u32 code = (addr & 0x00ff0000) >> 16;
	u32 type = (addr & 0x00007000) >> 12;
	u32 mthd = (addr & 0x00000ffc);
	स्थिर काष्ठा nvkm_क्रमागत *ec, *et;

	et = nvkm_क्रमागत_find(nv50_disp_पूर्णांकr_error_type, type);
	ec = nvkm_क्रमागत_find(nv50_disp_पूर्णांकr_error_code, code);

	nvkm_error(subdev,
		   "ERROR %d [%s] %02x [%s] chid %d mthd %04x data %08x\n",
		   type, et ? et->name : "", code, ec ? ec->name : "",
		   chid, mthd, data);

	अगर (chid < ARRAY_SIZE(disp->chan)) अणु
		चयन (mthd) अणु
		हाल 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_ERROR);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x610020, 0x00010000 << chid);
	nvkm_wr32(device, 0x610080 + (chid * 0x08), 0x90000000);
पूर्ण

व्योम
nv50_disp_पूर्णांकr(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	u32 पूर्णांकr0 = nvkm_rd32(device, 0x610020);
	u32 पूर्णांकr1 = nvkm_rd32(device, 0x610024);

	जबतक (पूर्णांकr0 & 0x001f0000) अणु
		u32 chid = __ffs(पूर्णांकr0 & 0x001f0000) - 16;
		nv50_disp_पूर्णांकr_error(disp, chid);
		पूर्णांकr0 &= ~(0x00010000 << chid);
	पूर्ण

	जबतक (पूर्णांकr0 & 0x0000001f) अणु
		u32 chid = __ffs(पूर्णांकr0 & 0x0000001f);
		nv50_disp_chan_uevent_send(disp, chid);
		पूर्णांकr0 &= ~(0x00000001 << chid);
	पूर्ण

	अगर (पूर्णांकr1 & 0x00000004) अणु
		nvkm_disp_vblank(&disp->base, 0);
		nvkm_wr32(device, 0x610024, 0x00000004);
	पूर्ण

	अगर (पूर्णांकr1 & 0x00000008) अणु
		nvkm_disp_vblank(&disp->base, 1);
		nvkm_wr32(device, 0x610024, 0x00000008);
	पूर्ण

	अगर (पूर्णांकr1 & 0x00000070) अणु
		disp->super = (पूर्णांकr1 & 0x00000070);
		queue_work(disp->wq, &disp->supervisor);
		nvkm_wr32(device, 0x610024, disp->super);
	पूर्ण
पूर्ण

व्योम
nv50_disp_fini(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	/* disable all पूर्णांकerrupts */
	nvkm_wr32(device, 0x610024, 0x00000000);
	nvkm_wr32(device, 0x610020, 0x00000000);
पूर्ण

पूर्णांक
nv50_disp_init(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	काष्ठा nvkm_head *head;
	u32 पंचांगp;
	पूर्णांक i;

	/* The below segments of code copying values from one रेजिस्टर to
	 * another appear to inक्रमm EVO of the display capabilities or
	 * something similar.  NFI what the 0x614004 caps are क्रम..
	 */
	पंचांगp = nvkm_rd32(device, 0x614004);
	nvkm_wr32(device, 0x610184, पंचांगp);

	/* ... CRTC caps */
	list_क्रम_each_entry(head, &disp->base.head, head) अणु
		पंचांगp = nvkm_rd32(device, 0x616100 + (head->id * 0x800));
		nvkm_wr32(device, 0x610190 + (head->id * 0x10), पंचांगp);
		पंचांगp = nvkm_rd32(device, 0x616104 + (head->id * 0x800));
		nvkm_wr32(device, 0x610194 + (head->id * 0x10), पंचांगp);
		पंचांगp = nvkm_rd32(device, 0x616108 + (head->id * 0x800));
		nvkm_wr32(device, 0x610198 + (head->id * 0x10), पंचांगp);
		पंचांगp = nvkm_rd32(device, 0x61610c + (head->id * 0x800));
		nvkm_wr32(device, 0x61019c + (head->id * 0x10), पंचांगp);
	पूर्ण

	/* ... DAC caps */
	क्रम (i = 0; i < disp->dac.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61a000 + (i * 0x800));
		nvkm_wr32(device, 0x6101d0 + (i * 0x04), पंचांगp);
	पूर्ण

	/* ... SOR caps */
	क्रम (i = 0; i < disp->sor.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61c000 + (i * 0x800));
		nvkm_wr32(device, 0x6101e0 + (i * 0x04), पंचांगp);
	पूर्ण

	/* ... PIOR caps */
	क्रम (i = 0; i < disp->pior.nr; i++) अणु
		पंचांगp = nvkm_rd32(device, 0x61e000 + (i * 0x800));
		nvkm_wr32(device, 0x6101f0 + (i * 0x04), पंचांगp);
	पूर्ण

	/* steal display away from vbios, or something like that */
	अगर (nvkm_rd32(device, 0x610024) & 0x00000100) अणु
		nvkm_wr32(device, 0x610024, 0x00000100);
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
	nvkm_wr32(device, 0x61002c, 0x00000370);
	nvkm_wr32(device, 0x610028, 0x00000000);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_disp_func
nv50_disp = अणु
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.पूर्णांकr = nv50_disp_पूर्णांकr,
	.uevent = &nv50_disp_chan_uevent,
	.super = nv50_disp_super,
	.root = &nv50_disp_root_oclass,
	.head = अणु .cnt = nv50_head_cnt, .new = nv50_head_new पूर्ण,
	.dac = अणु .cnt = nv50_dac_cnt, .new = nv50_dac_new पूर्ण,
	.sor = अणु .cnt = nv50_sor_cnt, .new = nv50_sor_new पूर्ण,
	.pior = अणु .cnt = nv50_pior_cnt, .new = nv50_pior_new पूर्ण,
पूर्ण;

पूर्णांक
nv50_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&nv50_disp, device, type, inst, pdisp);
पूर्ण
