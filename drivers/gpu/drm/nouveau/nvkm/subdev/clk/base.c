<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/boost.h>
#समावेश <subdev/bios/cstep.h>
#समावेश <subdev/bios/perf.h>
#समावेश <subdev/bios/vpstate.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/therm.h>
#समावेश <subdev/volt.h>

#समावेश <core/option.h>

/******************************************************************************
 * misc
 *****************************************************************************/
अटल u32
nvkm_clk_adjust(काष्ठा nvkm_clk *clk, bool adjust,
		u8 pstate, u8 करोमुख्य, u32 input)
अणु
	काष्ठा nvkm_bios *bios = clk->subdev.device->bios;
	काष्ठा nvbios_boostE boostE;
	u8  ver, hdr, cnt, len;
	u32 data;

	data = nvbios_boostEm(bios, pstate, &ver, &hdr, &cnt, &len, &boostE);
	अगर (data) अणु
		काष्ठा nvbios_boostS boostS;
		u8  idx = 0, sver, shdr;
		u32 subd;

		input = max(boostE.min, input);
		input = min(boostE.max, input);
		करो अणु
			sver = ver;
			shdr = hdr;
			subd = nvbios_boostSp(bios, idx++, data, &sver, &shdr,
					      cnt, len, &boostS);
			अगर (subd && boostS.करोमुख्य == करोमुख्य) अणु
				अगर (adjust)
					input = input * boostS.percent / 100;
				input = max(boostS.min, input);
				input = min(boostS.max, input);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (subd);
	पूर्ण

	वापस input;
पूर्ण

/******************************************************************************
 * C-States
 *****************************************************************************/
अटल bool
nvkm_cstate_valid(काष्ठा nvkm_clk *clk, काष्ठा nvkm_cstate *cstate,
		  u32 max_volt, पूर्णांक temp)
अणु
	स्थिर काष्ठा nvkm_करोमुख्य *करोमुख्य = clk->करोमुख्यs;
	काष्ठा nvkm_volt *volt = clk->subdev.device->volt;
	पूर्णांक voltage;

	जबतक (करोमुख्य && करोमुख्य->name != nv_clk_src_max) अणु
		अगर (करोमुख्य->flags & NVKM_CLK_DOM_FLAG_VPSTATE) अणु
			u32 freq = cstate->करोमुख्य[करोमुख्य->name];
			चयन (clk->boost_mode) अणु
			हाल NVKM_CLK_BOOST_NONE:
				अगर (clk->base_khz && freq > clk->base_khz)
					वापस false;
				fallthrough;
			हाल NVKM_CLK_BOOST_BIOS:
				अगर (clk->boost_khz && freq > clk->boost_khz)
					वापस false;
			पूर्ण
		पूर्ण
		करोमुख्य++;
	पूर्ण

	अगर (!volt)
		वापस true;

	voltage = nvkm_volt_map(volt, cstate->voltage, temp);
	अगर (voltage < 0)
		वापस false;
	वापस voltage <= min(max_volt, volt->max_uv);
पूर्ण

अटल काष्ठा nvkm_cstate *
nvkm_cstate_find_best(काष्ठा nvkm_clk *clk, काष्ठा nvkm_pstate *pstate,
		      काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा nvkm_device *device = clk->subdev.device;
	काष्ठा nvkm_volt *volt = device->volt;
	पूर्णांक max_volt;

	अगर (!pstate || !cstate)
		वापस शून्य;

	अगर (!volt)
		वापस cstate;

	max_volt = volt->max_uv;
	अगर (volt->max0_id != 0xff)
		max_volt = min(max_volt,
			       nvkm_volt_map(volt, volt->max0_id, clk->temp));
	अगर (volt->max1_id != 0xff)
		max_volt = min(max_volt,
			       nvkm_volt_map(volt, volt->max1_id, clk->temp));
	अगर (volt->max2_id != 0xff)
		max_volt = min(max_volt,
			       nvkm_volt_map(volt, volt->max2_id, clk->temp));

	list_क्रम_each_entry_from_reverse(cstate, &pstate->list, head) अणु
		अगर (nvkm_cstate_valid(clk, cstate, max_volt, clk->temp))
			अवरोध;
	पूर्ण

	वापस cstate;
पूर्ण

अटल काष्ठा nvkm_cstate *
nvkm_cstate_get(काष्ठा nvkm_clk *clk, काष्ठा nvkm_pstate *pstate, पूर्णांक cstatei)
अणु
	काष्ठा nvkm_cstate *cstate;
	अगर (cstatei == NVKM_CLK_CSTATE_HIGHEST)
		वापस list_last_entry(&pstate->list, typeof(*cstate), head);
	अन्यथा अणु
		list_क्रम_each_entry(cstate, &pstate->list, head) अणु
			अगर (cstate->id == cstatei)
				वापस cstate;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nvkm_cstate_prog(काष्ठा nvkm_clk *clk, काष्ठा nvkm_pstate *pstate, पूर्णांक cstatei)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_therm *therm = device->therm;
	काष्ठा nvkm_volt *volt = device->volt;
	काष्ठा nvkm_cstate *cstate;
	पूर्णांक ret;

	अगर (!list_empty(&pstate->list)) अणु
		cstate = nvkm_cstate_get(clk, pstate, cstatei);
		cstate = nvkm_cstate_find_best(clk, pstate, cstate);
	पूर्ण अन्यथा अणु
		cstate = &pstate->base;
	पूर्ण

	अगर (therm) अणु
		ret = nvkm_therm_cstate(therm, pstate->fanspeed, +1);
		अगर (ret && ret != -ENODEV) अणु
			nvkm_error(subdev, "failed to raise fan speed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (volt) अणु
		ret = nvkm_volt_set_id(volt, cstate->voltage,
				       pstate->base.voltage, clk->temp, +1);
		अगर (ret && ret != -ENODEV) अणु
			nvkm_error(subdev, "failed to raise voltage: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk->func->calc(clk, cstate);
	अगर (ret == 0) अणु
		ret = clk->func->prog(clk);
		clk->func->tidy(clk);
	पूर्ण

	अगर (volt) अणु
		ret = nvkm_volt_set_id(volt, cstate->voltage,
				       pstate->base.voltage, clk->temp, -1);
		अगर (ret && ret != -ENODEV)
			nvkm_error(subdev, "failed to lower voltage: %d\n", ret);
	पूर्ण

	अगर (therm) अणु
		ret = nvkm_therm_cstate(therm, pstate->fanspeed, -1);
		अगर (ret && ret != -ENODEV)
			nvkm_error(subdev, "failed to lower fan speed: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
nvkm_cstate_del(काष्ठा nvkm_cstate *cstate)
अणु
	list_del(&cstate->head);
	kमुक्त(cstate);
पूर्ण

अटल पूर्णांक
nvkm_cstate_new(काष्ठा nvkm_clk *clk, पूर्णांक idx, काष्ठा nvkm_pstate *pstate)
अणु
	काष्ठा nvkm_bios *bios = clk->subdev.device->bios;
	काष्ठा nvkm_volt *volt = clk->subdev.device->volt;
	स्थिर काष्ठा nvkm_करोमुख्य *करोमुख्य = clk->करोमुख्यs;
	काष्ठा nvkm_cstate *cstate = शून्य;
	काष्ठा nvbios_cstepX cstepX;
	u8  ver, hdr;
	u32 data;

	data = nvbios_cstepXp(bios, idx, &ver, &hdr, &cstepX);
	अगर (!data)
		वापस -ENOENT;

	अगर (volt && nvkm_volt_map_min(volt, cstepX.voltage) > volt->max_uv)
		वापस -EINVAL;

	cstate = kzalloc(माप(*cstate), GFP_KERNEL);
	अगर (!cstate)
		वापस -ENOMEM;

	*cstate = pstate->base;
	cstate->voltage = cstepX.voltage;
	cstate->id = idx;

	जबतक (करोमुख्य && करोमुख्य->name != nv_clk_src_max) अणु
		अगर (करोमुख्य->flags & NVKM_CLK_DOM_FLAG_CORE) अणु
			u32 freq = nvkm_clk_adjust(clk, true, pstate->pstate,
						   करोमुख्य->bios, cstepX.freq);
			cstate->करोमुख्य[करोमुख्य->name] = freq;
		पूर्ण
		करोमुख्य++;
	पूर्ण

	list_add(&cstate->head, &pstate->list);
	वापस 0;
पूर्ण

/******************************************************************************
 * P-States
 *****************************************************************************/
अटल पूर्णांक
nvkm_pstate_prog(काष्ठा nvkm_clk *clk, पूर्णांक pstatei)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->subdev;
	काष्ठा nvkm_fb *fb = subdev->device->fb;
	काष्ठा nvkm_pci *pci = subdev->device->pci;
	काष्ठा nvkm_pstate *pstate;
	पूर्णांक ret, idx = 0;

	list_क्रम_each_entry(pstate, &clk->states, head) अणु
		अगर (idx++ == pstatei)
			अवरोध;
	पूर्ण

	nvkm_debug(subdev, "setting performance state %d\n", pstatei);
	clk->pstate = pstatei;

	nvkm_pcie_set_link(pci, pstate->pcie_speed, pstate->pcie_width);

	अगर (fb && fb->ram && fb->ram->func->calc) अणु
		काष्ठा nvkm_ram *ram = fb->ram;
		पूर्णांक khz = pstate->base.करोमुख्य[nv_clk_src_mem];
		करो अणु
			ret = ram->func->calc(ram, khz);
			अगर (ret == 0)
				ret = ram->func->prog(ram);
		पूर्ण जबतक (ret > 0);
		ram->func->tidy(ram);
	पूर्ण

	वापस nvkm_cstate_prog(clk, pstate, NVKM_CLK_CSTATE_HIGHEST);
पूर्ण

अटल व्योम
nvkm_pstate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvkm_clk *clk = container_of(work, typeof(*clk), work);
	काष्ठा nvkm_subdev *subdev = &clk->subdev;
	पूर्णांक pstate;

	अगर (!atomic_xchg(&clk->रुकोing, 0))
		वापस;
	clk->pwrsrc = घातer_supply_is_प्रणाली_supplied();

	nvkm_trace(subdev, "P %d PWR %d U(AC) %d U(DC) %d A %d T %dतओC D %d\n",
		   clk->pstate, clk->pwrsrc, clk->ustate_ac, clk->ustate_dc,
		   clk->astate, clk->temp, clk->dstate);

	pstate = clk->pwrsrc ? clk->ustate_ac : clk->ustate_dc;
	अगर (clk->state_nr && pstate != -1) अणु
		pstate = (pstate < 0) ? clk->astate : pstate;
		pstate = min(pstate, clk->state_nr - 1);
		pstate = max(pstate, clk->dstate);
	पूर्ण अन्यथा अणु
		pstate = clk->pstate = -1;
	पूर्ण

	nvkm_trace(subdev, "-> %d\n", pstate);
	अगर (pstate != clk->pstate) अणु
		पूर्णांक ret = nvkm_pstate_prog(clk, pstate);
		अगर (ret) अणु
			nvkm_error(subdev, "error setting pstate %d: %d\n",
				   pstate, ret);
		पूर्ण
	पूर्ण

	wake_up_all(&clk->रुको);
	nvkm_notअगरy_get(&clk->pwrsrc_ntfy);
पूर्ण

अटल पूर्णांक
nvkm_pstate_calc(काष्ठा nvkm_clk *clk, bool रुको)
अणु
	atomic_set(&clk->रुकोing, 1);
	schedule_work(&clk->work);
	अगर (रुको)
		रुको_event(clk->रुको, !atomic_पढ़ो(&clk->रुकोing));
	वापस 0;
पूर्ण

अटल व्योम
nvkm_pstate_info(काष्ठा nvkm_clk *clk, काष्ठा nvkm_pstate *pstate)
अणु
	स्थिर काष्ठा nvkm_करोमुख्य *घड़ी = clk->करोमुख्यs - 1;
	काष्ठा nvkm_cstate *cstate;
	काष्ठा nvkm_subdev *subdev = &clk->subdev;
	अक्षर info[3][32] = अणु "", "", "" पूर्ण;
	अक्षर name[4] = "--";
	पूर्णांक i = -1;

	अगर (pstate->pstate != 0xff)
		snम_लिखो(name, माप(name), "%02x", pstate->pstate);

	जबतक ((++घड़ी)->name != nv_clk_src_max) अणु
		u32 lo = pstate->base.करोमुख्य[घड़ी->name];
		u32 hi = lo;
		अगर (hi == 0)
			जारी;

		nvkm_debug(subdev, "%02x: %10d KHz\n", घड़ी->name, lo);
		list_क्रम_each_entry(cstate, &pstate->list, head) अणु
			u32 freq = cstate->करोमुख्य[घड़ी->name];
			lo = min(lo, freq);
			hi = max(hi, freq);
			nvkm_debug(subdev, "%10d KHz\n", freq);
		पूर्ण

		अगर (घड़ी->mname && ++i < ARRAY_SIZE(info)) अणु
			lo /= घड़ी->mभाग;
			hi /= घड़ी->mभाग;
			अगर (lo == hi) अणु
				snम_लिखो(info[i], माप(info[i]), "%s %d MHz",
					 घड़ी->mname, lo);
			पूर्ण अन्यथा अणु
				snम_लिखो(info[i], माप(info[i]),
					 "%s %d-%d MHz", घड़ी->mname, lo, hi);
			पूर्ण
		पूर्ण
	पूर्ण

	nvkm_debug(subdev, "%s: %s %s %s\n", name, info[0], info[1], info[2]);
पूर्ण

अटल व्योम
nvkm_pstate_del(काष्ठा nvkm_pstate *pstate)
अणु
	काष्ठा nvkm_cstate *cstate, *temp;

	list_क्रम_each_entry_safe(cstate, temp, &pstate->list, head) अणु
		nvkm_cstate_del(cstate);
	पूर्ण

	list_del(&pstate->head);
	kमुक्त(pstate);
पूर्ण

अटल पूर्णांक
nvkm_pstate_new(काष्ठा nvkm_clk *clk, पूर्णांक idx)
अणु
	काष्ठा nvkm_bios *bios = clk->subdev.device->bios;
	स्थिर काष्ठा nvkm_करोमुख्य *करोमुख्य = clk->करोमुख्यs - 1;
	काष्ठा nvkm_pstate *pstate;
	काष्ठा nvkm_cstate *cstate;
	काष्ठा nvbios_cstepE cstepE;
	काष्ठा nvbios_perfE perfE;
	u8  ver, hdr, cnt, len;
	u32 data;

	data = nvbios_perfEp(bios, idx, &ver, &hdr, &cnt, &len, &perfE);
	अगर (!data)
		वापस -EINVAL;
	अगर (perfE.pstate == 0xff)
		वापस 0;

	pstate = kzalloc(माप(*pstate), GFP_KERNEL);
	cstate = &pstate->base;
	अगर (!pstate)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&pstate->list);

	pstate->pstate = perfE.pstate;
	pstate->fanspeed = perfE.fanspeed;
	pstate->pcie_speed = perfE.pcie_speed;
	pstate->pcie_width = perfE.pcie_width;
	cstate->voltage = perfE.voltage;
	cstate->करोमुख्य[nv_clk_src_core] = perfE.core;
	cstate->करोमुख्य[nv_clk_src_shader] = perfE.shader;
	cstate->करोमुख्य[nv_clk_src_mem] = perfE.memory;
	cstate->करोमुख्य[nv_clk_src_vdec] = perfE.vdec;
	cstate->करोमुख्य[nv_clk_src_करोm6] = perfE.disp;

	जबतक (ver >= 0x40 && (++करोमुख्य)->name != nv_clk_src_max) अणु
		काष्ठा nvbios_perfS perfS;
		u8  sver = ver, shdr = hdr;
		u32 perfSe = nvbios_perfSp(bios, data, करोमुख्य->bios,
					  &sver, &shdr, cnt, len, &perfS);
		अगर (perfSe == 0 || sver != 0x40)
			जारी;

		अगर (करोमुख्य->flags & NVKM_CLK_DOM_FLAG_CORE) अणु
			perfS.v40.freq = nvkm_clk_adjust(clk, false,
							 pstate->pstate,
							 करोमुख्य->bios,
							 perfS.v40.freq);
		पूर्ण

		cstate->करोमुख्य[करोमुख्य->name] = perfS.v40.freq;
	पूर्ण

	data = nvbios_cstepEm(bios, pstate->pstate, &ver, &hdr, &cstepE);
	अगर (data) अणु
		पूर्णांक idx = cstepE.index;
		करो अणु
			nvkm_cstate_new(clk, idx, pstate);
		पूर्ण जबतक(idx--);
	पूर्ण

	nvkm_pstate_info(clk, pstate);
	list_add_tail(&pstate->head, &clk->states);
	clk->state_nr++;
	वापस 0;
पूर्ण

/******************************************************************************
 * Adjusपंचांगent triggers
 *****************************************************************************/
अटल पूर्णांक
nvkm_clk_ustate_update(काष्ठा nvkm_clk *clk, पूर्णांक req)
अणु
	काष्ठा nvkm_pstate *pstate;
	पूर्णांक i = 0;

	अगर (!clk->allow_reघड़ी)
		वापस -ENOSYS;

	अगर (req != -1 && req != -2) अणु
		list_क्रम_each_entry(pstate, &clk->states, head) अणु
			अगर (pstate->pstate == req)
				अवरोध;
			i++;
		पूर्ण

		अगर (pstate->pstate != req)
			वापस -EINVAL;
		req = i;
	पूर्ण

	वापस req + 2;
पूर्ण

अटल पूर्णांक
nvkm_clk_nstate(काष्ठा nvkm_clk *clk, स्थिर अक्षर *mode, पूर्णांक arglen)
अणु
	पूर्णांक ret = 1;

	अगर (clk->allow_reघड़ी && !strnहालcmpz(mode, "auto", arglen))
		वापस -2;

	अगर (strnहालcmpz(mode, "disabled", arglen)) अणु
		अक्षर save = mode[arglen];
		दीर्घ v;

		((अक्षर *)mode)[arglen] = '\0';
		अगर (!kम_से_दीर्घ(mode, 0, &v)) अणु
			ret = nvkm_clk_ustate_update(clk, v);
			अगर (ret < 0)
				ret = 1;
		पूर्ण
		((अक्षर *)mode)[arglen] = save;
	पूर्ण

	वापस ret - 2;
पूर्ण

पूर्णांक
nvkm_clk_ustate(काष्ठा nvkm_clk *clk, पूर्णांक req, पूर्णांक pwr)
अणु
	पूर्णांक ret = nvkm_clk_ustate_update(clk, req);
	अगर (ret >= 0) अणु
		अगर (ret -= 2, pwr) clk->ustate_ac = ret;
		अन्यथा		   clk->ustate_dc = ret;
		वापस nvkm_pstate_calc(clk, true);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nvkm_clk_astate(काष्ठा nvkm_clk *clk, पूर्णांक req, पूर्णांक rel, bool रुको)
अणु
	अगर (!rel) clk->astate  = req;
	अगर ( rel) clk->astate += rel;
	clk->astate = min(clk->astate, clk->state_nr - 1);
	clk->astate = max(clk->astate, 0);
	वापस nvkm_pstate_calc(clk, रुको);
पूर्ण

पूर्णांक
nvkm_clk_tstate(काष्ठा nvkm_clk *clk, u8 temp)
अणु
	अगर (clk->temp == temp)
		वापस 0;
	clk->temp = temp;
	वापस nvkm_pstate_calc(clk, false);
पूर्ण

पूर्णांक
nvkm_clk_dstate(काष्ठा nvkm_clk *clk, पूर्णांक req, पूर्णांक rel)
अणु
	अगर (!rel) clk->dstate  = req;
	अगर ( rel) clk->dstate += rel;
	clk->dstate = min(clk->dstate, clk->state_nr - 1);
	clk->dstate = max(clk->dstate, 0);
	वापस nvkm_pstate_calc(clk, true);
पूर्ण

अटल पूर्णांक
nvkm_clk_pwrsrc(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_clk *clk =
		container_of(notअगरy, typeof(*clk), pwrsrc_ntfy);
	nvkm_pstate_calc(clk, false);
	वापस NVKM_NOTIFY_DROP;
पूर्ण

/******************************************************************************
 * subdev base class implementation
 *****************************************************************************/

पूर्णांक
nvkm_clk_पढ़ो(काष्ठा nvkm_clk *clk, क्रमागत nv_clk_src src)
अणु
	वापस clk->func->पढ़ो(clk, src);
पूर्ण

अटल पूर्णांक
nvkm_clk_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_clk *clk = nvkm_clk(subdev);
	nvkm_notअगरy_put(&clk->pwrsrc_ntfy);
	flush_work(&clk->work);
	अगर (clk->func->fini)
		clk->func->fini(clk);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_clk_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_clk *clk = nvkm_clk(subdev);
	स्थिर काष्ठा nvkm_करोमुख्य *घड़ी = clk->करोमुख्यs;
	पूर्णांक ret;

	स_रखो(&clk->bstate, 0x00, माप(clk->bstate));
	INIT_LIST_HEAD(&clk->bstate.list);
	clk->bstate.pstate = 0xff;

	जबतक (घड़ी->name != nv_clk_src_max) अणु
		ret = nvkm_clk_पढ़ो(clk, घड़ी->name);
		अगर (ret < 0) अणु
			nvkm_error(subdev, "%02x freq unknown\n", घड़ी->name);
			वापस ret;
		पूर्ण
		clk->bstate.base.करोमुख्य[घड़ी->name] = ret;
		घड़ी++;
	पूर्ण

	nvkm_pstate_info(clk, &clk->bstate);

	अगर (clk->func->init)
		वापस clk->func->init(clk);

	clk->astate = clk->state_nr - 1;
	clk->dstate = 0;
	clk->pstate = -1;
	clk->temp = 90; /* reasonable शेष value */
	nvkm_pstate_calc(clk, true);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_clk_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_clk *clk = nvkm_clk(subdev);
	काष्ठा nvkm_pstate *pstate, *temp;

	nvkm_notअगरy_fini(&clk->pwrsrc_ntfy);

	/* Early वापस अगर the pstates have been provided अटलally */
	अगर (clk->func->pstates)
		वापस clk;

	list_क्रम_each_entry_safe(pstate, temp, &clk->states, head) अणु
		nvkm_pstate_del(pstate);
	पूर्ण

	वापस clk;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_clk = अणु
	.dtor = nvkm_clk_dtor,
	.init = nvkm_clk_init,
	.fini = nvkm_clk_fini,
पूर्ण;

पूर्णांक
nvkm_clk_ctor(स्थिर काष्ठा nvkm_clk_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool allow_reघड़ी, काष्ठा nvkm_clk *clk)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->subdev;
	काष्ठा nvkm_bios *bios = device->bios;
	पूर्णांक ret, idx, arglen;
	स्थिर अक्षर *mode;
	काष्ठा nvbios_vpstate_header h;

	nvkm_subdev_ctor(&nvkm_clk, device, type, inst, subdev);

	अगर (bios && !nvbios_vpstate_parse(bios, &h)) अणु
		काष्ठा nvbios_vpstate_entry base, boost;
		अगर (!nvbios_vpstate_entry(bios, &h, h.boost_id, &boost))
			clk->boost_khz = boost.घड़ी_mhz * 1000;
		अगर (!nvbios_vpstate_entry(bios, &h, h.base_id, &base))
			clk->base_khz = base.घड़ी_mhz * 1000;
	पूर्ण

	clk->func = func;
	INIT_LIST_HEAD(&clk->states);
	clk->करोमुख्यs = func->करोमुख्यs;
	clk->ustate_ac = -1;
	clk->ustate_dc = -1;
	clk->allow_reघड़ी = allow_reघड़ी;

	INIT_WORK(&clk->work, nvkm_pstate_work);
	init_रुकोqueue_head(&clk->रुको);
	atomic_set(&clk->रुकोing, 0);

	/* If no pstates are provided, try and fetch them from the BIOS */
	अगर (!func->pstates) अणु
		idx = 0;
		करो अणु
			ret = nvkm_pstate_new(clk, idx++);
		पूर्ण जबतक (ret == 0);
	पूर्ण अन्यथा अणु
		क्रम (idx = 0; idx < func->nr_pstates; idx++)
			list_add_tail(&func->pstates[idx].head, &clk->states);
		clk->state_nr = func->nr_pstates;
	पूर्ण

	ret = nvkm_notअगरy_init(शून्य, &device->event, nvkm_clk_pwrsrc, true,
			       शून्य, 0, 0, &clk->pwrsrc_ntfy);
	अगर (ret)
		वापस ret;

	mode = nvkm_stropt(device->cfgopt, "NvClkMode", &arglen);
	अगर (mode) अणु
		clk->ustate_ac = nvkm_clk_nstate(clk, mode, arglen);
		clk->ustate_dc = nvkm_clk_nstate(clk, mode, arglen);
	पूर्ण

	mode = nvkm_stropt(device->cfgopt, "NvClkModeAC", &arglen);
	अगर (mode)
		clk->ustate_ac = nvkm_clk_nstate(clk, mode, arglen);

	mode = nvkm_stropt(device->cfgopt, "NvClkModeDC", &arglen);
	अगर (mode)
		clk->ustate_dc = nvkm_clk_nstate(clk, mode, arglen);

	clk->boost_mode = nvkm_दीर्घopt(device->cfgopt, "NvBoost",
				       NVKM_CLK_BOOST_NONE);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_clk_new_(स्थिर काष्ठा nvkm_clk_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool allow_reघड़ी, काष्ठा nvkm_clk **pclk)
अणु
	अगर (!(*pclk = kzalloc(माप(**pclk), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_clk_ctor(func, device, type, inst, allow_reघड़ी, *pclk);
पूर्ण
