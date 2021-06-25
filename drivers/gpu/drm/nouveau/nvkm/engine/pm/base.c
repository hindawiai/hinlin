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

#समावेश <core/client.h>
#समावेश <core/option.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0002.h>
#समावेश <nvअगर/अगर0003.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/unpack.h>

अटल u8
nvkm_pm_count_perfकरोm(काष्ठा nvkm_pm *pm)
अणु
	काष्ठा nvkm_perfकरोm *करोm;
	u8 करोमुख्य_nr = 0;

	list_क्रम_each_entry(करोm, &pm->करोमुख्यs, head)
		करोमुख्य_nr++;
	वापस करोमुख्य_nr;
पूर्ण

अटल u16
nvkm_perfकरोm_count_perfsig(काष्ठा nvkm_perfकरोm *करोm)
अणु
	u16 संकेत_nr = 0;
	पूर्णांक i;

	अगर (करोm) अणु
		क्रम (i = 0; i < करोm->संकेत_nr; i++) अणु
			अगर (करोm->संकेत[i].name)
				संकेत_nr++;
		पूर्ण
	पूर्ण
	वापस संकेत_nr;
पूर्ण

अटल काष्ठा nvkm_perfकरोm *
nvkm_perfकरोm_find(काष्ठा nvkm_pm *pm, पूर्णांक di)
अणु
	काष्ठा nvkm_perfकरोm *करोm;
	पूर्णांक पंचांगp = 0;

	list_क्रम_each_entry(करोm, &pm->करोमुख्यs, head) अणु
		अगर (पंचांगp++ == di)
			वापस करोm;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nvkm_perfsig *
nvkm_perfsig_find(काष्ठा nvkm_pm *pm, u8 di, u8 si, काष्ठा nvkm_perfकरोm **pकरोm)
अणु
	काष्ठा nvkm_perfकरोm *करोm = *pकरोm;

	अगर (करोm == शून्य) अणु
		करोm = nvkm_perfकरोm_find(pm, di);
		अगर (करोm == शून्य)
			वापस शून्य;
		*pकरोm = करोm;
	पूर्ण

	अगर (!करोm->संकेत[si].name)
		वापस शून्य;
	वापस &करोm->संकेत[si];
पूर्ण

अटल u8
nvkm_perfsig_count_perfsrc(काष्ठा nvkm_perfsig *sig)
अणु
	u8 source_nr = 0, i;

	क्रम (i = 0; i < ARRAY_SIZE(sig->source); i++) अणु
		अगर (sig->source[i])
			source_nr++;
	पूर्ण
	वापस source_nr;
पूर्ण

अटल काष्ठा nvkm_perfsrc *
nvkm_perfsrc_find(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfsig *sig, पूर्णांक si)
अणु
	काष्ठा nvkm_perfsrc *src;
	bool found = false;
	पूर्णांक पंचांगp = 1; /* Sources ID start from 1 */
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(sig->source) && sig->source[i]; i++) अणु
		अगर (sig->source[i] == si) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		list_क्रम_each_entry(src, &pm->sources, head) अणु
			अगर (पंचांगp++ == si)
				वापस src;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
nvkm_perfsrc_enable(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_subdev *subdev = &pm->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_perfकरोm *करोm = शून्य;
	काष्ठा nvkm_perfsig *sig;
	काष्ठा nvkm_perfsrc *src;
	u32 mask, value;
	पूर्णांक i, j;

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < 8 && ctr->source[i][j]; j++) अणु
			sig = nvkm_perfsig_find(pm, ctr->करोमुख्य,
						ctr->संकेत[i], &करोm);
			अगर (!sig)
				वापस -EINVAL;

			src = nvkm_perfsrc_find(pm, sig, ctr->source[i][j]);
			अगर (!src)
				वापस -EINVAL;

			/* set enable bit अगर needed */
			mask = value = 0x00000000;
			अगर (src->enable)
				mask = value = 0x80000000;
			mask  |= (src->mask << src->shअगरt);
			value |= ((ctr->source[i][j] >> 32) << src->shअगरt);

			/* enable the source */
			nvkm_mask(device, src->addr, mask, value);
			nvkm_debug(subdev,
				   "enabled source %08x %08x %08x\n",
				   src->addr, mask, value);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfsrc_disable(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_subdev *subdev = &pm->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_perfकरोm *करोm = शून्य;
	काष्ठा nvkm_perfsig *sig;
	काष्ठा nvkm_perfsrc *src;
	u32 mask;
	पूर्णांक i, j;

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < 8 && ctr->source[i][j]; j++) अणु
			sig = nvkm_perfsig_find(pm, ctr->करोमुख्य,
						ctr->संकेत[i], &करोm);
			अगर (!sig)
				वापस -EINVAL;

			src = nvkm_perfsrc_find(pm, sig, ctr->source[i][j]);
			अगर (!src)
				वापस -EINVAL;

			/* unset enable bit अगर needed */
			mask = 0x00000000;
			अगर (src->enable)
				mask = 0x80000000;
			mask |= (src->mask << src->shअगरt);

			/* disable the source */
			nvkm_mask(device, src->addr, mask, 0);
			nvkm_debug(subdev, "disabled source %08x %08x\n",
				   src->addr, mask);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*******************************************************************************
 * Perfकरोm object classes
 ******************************************************************************/
अटल पूर्णांक
nvkm_perfकरोm_init(काष्ठा nvkm_perfकरोm *करोm, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfकरोm_init none;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &करोm->object;
	काष्ठा nvkm_pm *pm = करोm->perfmon->pm;
	पूर्णांक ret = -ENOSYS, i;

	nvअगर_ioctl(object, "perfdom init size %d\n", size);
	अगर (!(ret = nvअगर_unvers(ret, &data, &size, args->none))) अणु
		nvअगर_ioctl(object, "perfdom init\n");
	पूर्ण अन्यथा
		वापस ret;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (करोm->ctr[i]) अणु
			करोm->func->init(pm, करोm, करोm->ctr[i]);

			/* enable sources */
			nvkm_perfsrc_enable(pm, करोm->ctr[i]);
		पूर्ण
	पूर्ण

	/* start next batch of counters क्रम sampling */
	करोm->func->next(pm, करोm);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfकरोm_sample(काष्ठा nvkm_perfकरोm *करोm, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfकरोm_sample none;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &करोm->object;
	काष्ठा nvkm_pm *pm = करोm->perfmon->pm;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "perfdom sample size %d\n", size);
	अगर (!(ret = nvअगर_unvers(ret, &data, &size, args->none))) अणु
		nvअगर_ioctl(object, "perfdom sample\n");
	पूर्ण अन्यथा
		वापस ret;
	pm->sequence++;

	/* sample previous batch of counters */
	list_क्रम_each_entry(करोm, &pm->करोमुख्यs, head)
		करोm->func->next(pm, करोm);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfकरोm_पढ़ो(काष्ठा nvkm_perfकरोm *करोm, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfकरोm_पढ़ो_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &करोm->object;
	काष्ठा nvkm_pm *pm = करोm->perfmon->pm;
	पूर्णांक ret = -ENOSYS, i;

	nvअगर_ioctl(object, "perfdom read size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "perfdom read vers %d\n", args->v0.version);
	पूर्ण अन्यथा
		वापस ret;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (करोm->ctr[i])
			करोm->func->पढ़ो(pm, करोm, करोm->ctr[i]);
	पूर्ण

	अगर (!करोm->clk)
		वापस -EAGAIN;

	क्रम (i = 0; i < 4; i++)
		अगर (करोm->ctr[i])
			args->v0.ctr[i] = करोm->ctr[i]->ctr;
	args->v0.clk = करोm->clk;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfकरोm_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_perfकरोm *करोm = nvkm_perfकरोm(object);
	चयन (mthd) अणु
	हाल NVIF_PERFDOM_V0_INIT:
		वापस nvkm_perfकरोm_init(करोm, data, size);
	हाल NVIF_PERFDOM_V0_SAMPLE:
		वापस nvkm_perfकरोm_sample(करोm, data, size);
	हाल NVIF_PERFDOM_V0_READ:
		वापस nvkm_perfकरोm_पढ़ो(करोm, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम *
nvkm_perfकरोm_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_perfकरोm *करोm = nvkm_perfकरोm(object);
	काष्ठा nvkm_pm *pm = करोm->perfmon->pm;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा nvkm_perfctr *ctr = करोm->ctr[i];
		अगर (ctr) अणु
			nvkm_perfsrc_disable(pm, ctr);
			अगर (ctr->head.next)
				list_del(&ctr->head);
		पूर्ण
		kमुक्त(ctr);
	पूर्ण

	वापस करोm;
पूर्ण

अटल पूर्णांक
nvkm_perfctr_new(काष्ठा nvkm_perfकरोm *करोm, पूर्णांक slot, u8 करोमुख्य,
		 काष्ठा nvkm_perfsig *संकेत[4], u64 source[4][8],
		 u16 logic_op, काष्ठा nvkm_perfctr **pctr)
अणु
	काष्ठा nvkm_perfctr *ctr;
	पूर्णांक i, j;

	अगर (!करोm)
		वापस -EINVAL;

	ctr = *pctr = kzalloc(माप(*ctr), GFP_KERNEL);
	अगर (!ctr)
		वापस -ENOMEM;

	ctr->करोमुख्य   = करोमुख्य;
	ctr->logic_op = logic_op;
	ctr->slot     = slot;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (संकेत[i]) अणु
			ctr->संकेत[i] = संकेत[i] - करोm->संकेत;
			क्रम (j = 0; j < 8; j++)
				ctr->source[i][j] = source[i][j];
		पूर्ण
	पूर्ण
	list_add_tail(&ctr->head, &करोm->list);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_perfकरोm = अणु
	.dtor = nvkm_perfकरोm_dtor,
	.mthd = nvkm_perfकरोm_mthd,
पूर्ण;

अटल पूर्णांक
nvkm_perfकरोm_new_(काष्ठा nvkm_perfmon *perfmon,
		  स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		  काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfकरोm_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_pm *pm = perfmon->pm;
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा nvkm_perfकरोm *sकरोm = शून्य;
	काष्ठा nvkm_perfctr *ctr[4] = अणुपूर्ण;
	काष्ठा nvkm_perfकरोm *करोm;
	पूर्णांक c, s, m;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create perfdom size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create perfdom vers %d dom %d mode %02x\n",
			   args->v0.version, args->v0.करोमुख्य, args->v0.mode);
	पूर्ण अन्यथा
		वापस ret;

	क्रम (c = 0; c < ARRAY_SIZE(args->v0.ctr); c++) अणु
		काष्ठा nvkm_perfsig *sig[4] = अणुपूर्ण;
		u64 src[4][8] = अणुपूर्ण;

		क्रम (s = 0; s < ARRAY_SIZE(args->v0.ctr[c].संकेत); s++) अणु
			sig[s] = nvkm_perfsig_find(pm, args->v0.करोमुख्य,
						   args->v0.ctr[c].संकेत[s],
						   &sकरोm);
			अगर (args->v0.ctr[c].संकेत[s] && !sig[s])
				वापस -EINVAL;

			क्रम (m = 0; m < 8; m++) अणु
				src[s][m] = args->v0.ctr[c].source[s][m];
				अगर (src[s][m] && !nvkm_perfsrc_find(pm, sig[s],
							            src[s][m]))
					वापस -EINVAL;
			पूर्ण
		पूर्ण

		ret = nvkm_perfctr_new(sकरोm, c, args->v0.करोमुख्य, sig, src,
				       args->v0.ctr[c].logic_op, &ctr[c]);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!sकरोm)
		वापस -EINVAL;

	अगर (!(करोm = kzalloc(माप(*करोm), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nvkm_perfकरोm, oclass, &करोm->object);
	करोm->perfmon = perfmon;
	*pobject = &करोm->object;

	करोm->func = sकरोm->func;
	करोm->addr = sकरोm->addr;
	करोm->mode = args->v0.mode;
	क्रम (c = 0; c < ARRAY_SIZE(ctr); c++)
		करोm->ctr[c] = ctr[c];
	वापस 0;
पूर्ण

/*******************************************************************************
 * Perfmon object classes
 ******************************************************************************/
अटल पूर्णांक
nvkm_perfmon_mthd_query_करोमुख्य(काष्ठा nvkm_perfmon *perfmon,
			       व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfmon_query_करोमुख्य_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &perfmon->object;
	काष्ठा nvkm_pm *pm = perfmon->pm;
	काष्ठा nvkm_perfकरोm *करोm;
	u8 करोमुख्य_nr;
	पूर्णांक di, ret = -ENOSYS;

	nvअगर_ioctl(object, "perfmon query domain size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "perfmon domain vers %d iter %02x\n",
			   args->v0.version, args->v0.iter);
		di = (args->v0.iter & 0xff) - 1;
	पूर्ण अन्यथा
		वापस ret;

	करोमुख्य_nr = nvkm_pm_count_perfकरोm(pm);
	अगर (di >= (पूर्णांक)करोमुख्य_nr)
		वापस -EINVAL;

	अगर (di >= 0) अणु
		करोm = nvkm_perfकरोm_find(pm, di);
		अगर (करोm == शून्य)
			वापस -EINVAL;

		args->v0.id         = di;
		args->v0.संकेत_nr  = nvkm_perfकरोm_count_perfsig(करोm);
		म_नकलन(args->v0.name, करोm->name, माप(args->v0.name) - 1);

		/* Currently only global counters (PCOUNTER) are implemented
		 * but this will be dअगरferent क्रम local counters (MP). */
		args->v0.counter_nr = 4;
	पूर्ण

	अगर (++di < करोमुख्य_nr) अणु
		args->v0.iter = ++di;
		वापस 0;
	पूर्ण

	args->v0.iter = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfmon_mthd_query_संकेत(काष्ठा nvkm_perfmon *perfmon,
			       व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfmon_query_संकेत_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &perfmon->object;
	काष्ठा nvkm_pm *pm = perfmon->pm;
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	काष्ठा nvkm_perfकरोm *करोm;
	काष्ठा nvkm_perfsig *sig;
	स्थिर bool all = nvkm_boolopt(device->cfgopt, "NvPmShowAll", false);
	स्थिर bool raw = nvkm_boolopt(device->cfgopt, "NvPmUnnamed", all);
	पूर्णांक ret = -ENOSYS, si;

	nvअगर_ioctl(object, "perfmon query signal size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object,
			   "perfmon query signal vers %d dom %d iter %04x\n",
			   args->v0.version, args->v0.करोमुख्य, args->v0.iter);
		si = (args->v0.iter & 0xffff) - 1;
	पूर्ण अन्यथा
		वापस ret;

	करोm = nvkm_perfकरोm_find(pm, args->v0.करोमुख्य);
	अगर (करोm == शून्य || si >= (पूर्णांक)करोm->संकेत_nr)
		वापस -EINVAL;

	अगर (si >= 0) अणु
		sig = &करोm->संकेत[si];
		अगर (raw || !sig->name) अणु
			snम_लिखो(args->v0.name, माप(args->v0.name),
				 "/%s/%02x", करोm->name, si);
		पूर्ण अन्यथा अणु
			म_नकलन(args->v0.name, sig->name,
				माप(args->v0.name) - 1);
		पूर्ण

		args->v0.संकेत = si;
		args->v0.source_nr = nvkm_perfsig_count_perfsrc(sig);
	पूर्ण

	जबतक (++si < करोm->संकेत_nr) अणु
		अगर (all || करोm->संकेत[si].name) अणु
			args->v0.iter = ++si;
			वापस 0;
		पूर्ण
	पूर्ण

	args->v0.iter = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfmon_mthd_query_source(काष्ठा nvkm_perfmon *perfmon,
			       व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_perfmon_query_source_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = &perfmon->object;
	काष्ठा nvkm_pm *pm = perfmon->pm;
	काष्ठा nvkm_perfकरोm *करोm = शून्य;
	काष्ठा nvkm_perfsig *sig;
	काष्ठा nvkm_perfsrc *src;
	u8 source_nr = 0;
	पूर्णांक si, ret = -ENOSYS;

	nvअगर_ioctl(object, "perfmon query source size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object,
			   "perfmon source vers %d dom %d sig %02x iter %02x\n",
			   args->v0.version, args->v0.करोमुख्य, args->v0.संकेत,
			   args->v0.iter);
		si = (args->v0.iter & 0xff) - 1;
	पूर्ण अन्यथा
		वापस ret;

	sig = nvkm_perfsig_find(pm, args->v0.करोमुख्य, args->v0.संकेत, &करोm);
	अगर (!sig)
		वापस -EINVAL;

	source_nr = nvkm_perfsig_count_perfsrc(sig);
	अगर (si >= (पूर्णांक)source_nr)
		वापस -EINVAL;

	अगर (si >= 0) अणु
		src = nvkm_perfsrc_find(pm, sig, sig->source[si]);
		अगर (!src)
			वापस -EINVAL;

		args->v0.source = sig->source[si];
		args->v0.mask   = src->mask;
		म_नकलन(args->v0.name, src->name, माप(args->v0.name) - 1);
	पूर्ण

	अगर (++si < source_nr) अणु
		args->v0.iter = ++si;
		वापस 0;
	पूर्ण

	args->v0.iter = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_perfmon_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_perfmon *perfmon = nvkm_perfmon(object);
	चयन (mthd) अणु
	हाल NVIF_PERFMON_V0_QUERY_DOMAIN:
		वापस nvkm_perfmon_mthd_query_करोमुख्य(perfmon, data, size);
	हाल NVIF_PERFMON_V0_QUERY_SIGNAL:
		वापस nvkm_perfmon_mthd_query_संकेत(perfmon, data, size);
	हाल NVIF_PERFMON_V0_QUERY_SOURCE:
		वापस nvkm_perfmon_mthd_query_source(perfmon, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_perfmon_child_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		       काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_perfmon *perfmon = nvkm_perfmon(oclass->parent);
	वापस nvkm_perfकरोm_new_(perfmon, oclass, data, size, pobject);
पूर्ण

अटल पूर्णांक
nvkm_perfmon_child_get(काष्ठा nvkm_object *object, पूर्णांक index,
		       काष्ठा nvkm_oclass *oclass)
अणु
	अगर (index == 0) अणु
		oclass->base.oclass = NVIF_CLASS_PERFDOM;
		oclass->base.minver = 0;
		oclass->base.maxver = 0;
		oclass->ctor = nvkm_perfmon_child_new;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम *
nvkm_perfmon_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_perfmon *perfmon = nvkm_perfmon(object);
	काष्ठा nvkm_pm *pm = perfmon->pm;
	spin_lock(&pm->client.lock);
	अगर (pm->client.object == &perfmon->object)
		pm->client.object = शून्य;
	spin_unlock(&pm->client.lock);
	वापस perfmon;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_perfmon = अणु
	.dtor = nvkm_perfmon_dtor,
	.mthd = nvkm_perfmon_mthd,
	.sclass = nvkm_perfmon_child_get,
पूर्ण;

अटल पूर्णांक
nvkm_perfmon_new(काष्ठा nvkm_pm *pm, स्थिर काष्ठा nvkm_oclass *oclass,
		 व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_perfmon *perfmon;

	अगर (!(perfmon = kzalloc(माप(*perfmon), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nvkm_perfmon, oclass, &perfmon->object);
	perfmon->pm = pm;
	*pobject = &perfmon->object;
	वापस 0;
पूर्ण

/*******************************************************************************
 * PPM engine/subdev functions
 ******************************************************************************/

अटल पूर्णांक
nvkm_pm_oclass_new(काष्ठा nvkm_device *device, स्थिर काष्ठा nvkm_oclass *oclass,
		   व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_pm *pm = nvkm_pm(oclass->engine);
	पूर्णांक ret;

	ret = nvkm_perfmon_new(pm, oclass, data, size, pobject);
	अगर (ret)
		वापस ret;

	spin_lock(&pm->client.lock);
	अगर (pm->client.object == शून्य)
		pm->client.object = *pobject;
	ret = (pm->client.object == *pobject) ? 0 : -EBUSY;
	spin_unlock(&pm->client.lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_device_oclass
nvkm_pm_oclass = अणु
	.base.oclass = NVIF_CLASS_PERFMON,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = nvkm_pm_oclass_new,
पूर्ण;

अटल पूर्णांक
nvkm_pm_oclass_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index,
		   स्थिर काष्ठा nvkm_device_oclass **class)
अणु
	अगर (index == 0) अणु
		oclass->base = nvkm_pm_oclass.base;
		*class = &nvkm_pm_oclass;
		वापस index;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक
nvkm_perfsrc_new(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfsig *sig,
		 स्थिर काष्ठा nvkm_specsrc *spec)
अणु
	स्थिर काष्ठा nvkm_specsrc *ssrc;
	स्थिर काष्ठा nvkm_specmux *smux;
	काष्ठा nvkm_perfsrc *src;
	u8 source_nr = 0;

	अगर (!spec) अणु
		/* No sources are defined क्रम this संकेत. */
		वापस 0;
	पूर्ण

	ssrc = spec;
	जबतक (ssrc->name) अणु
		smux = ssrc->mux;
		जबतक (smux->name) अणु
			bool found = false;
			u8 source_id = 0;
			u32 len;

			list_क्रम_each_entry(src, &pm->sources, head) अणु
				अगर (src->addr == ssrc->addr &&
				    src->shअगरt == smux->shअगरt) अणु
					found = true;
					अवरोध;
				पूर्ण
				source_id++;
			पूर्ण

			अगर (!found) अणु
				src = kzalloc(माप(*src), GFP_KERNEL);
				अगर (!src)
					वापस -ENOMEM;

				src->addr   = ssrc->addr;
				src->mask   = smux->mask;
				src->shअगरt  = smux->shअगरt;
				src->enable = smux->enable;

				len = म_माप(ssrc->name) +
				      म_माप(smux->name) + 2;
				src->name = kzalloc(len, GFP_KERNEL);
				अगर (!src->name) अणु
					kमुक्त(src);
					वापस -ENOMEM;
				पूर्ण
				snम_लिखो(src->name, len, "%s_%s", ssrc->name,
					 smux->name);

				list_add_tail(&src->head, &pm->sources);
			पूर्ण

			sig->source[source_nr++] = source_id + 1;
			smux++;
		पूर्ण
		ssrc++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_perfकरोm_new(काष्ठा nvkm_pm *pm, स्थिर अक्षर *name, u32 mask,
		 u32 base, u32 size_unit, u32 size_करोमुख्य,
		 स्थिर काष्ठा nvkm_specकरोm *spec)
अणु
	स्थिर काष्ठा nvkm_specकरोm *sकरोm;
	स्थिर काष्ठा nvkm_specsig *ssig;
	काष्ठा nvkm_perfकरोm *करोm;
	पूर्णांक ret, i;

	क्रम (i = 0; i == 0 || mask; i++) अणु
		u32 addr = base + (i * size_unit);
		अगर (i && !(mask & (1 << i)))
			जारी;

		sकरोm = spec;
		जबतक (sकरोm->संकेत_nr) अणु
			करोm = kzalloc(काष्ठा_size(करोm, संकेत, sकरोm->संकेत_nr),
				      GFP_KERNEL);
			अगर (!करोm)
				वापस -ENOMEM;

			अगर (mask) अणु
				snम_लिखो(करोm->name, माप(करोm->name),
					 "%s/%02x/%02x", name, i,
					 (पूर्णांक)(sकरोm - spec));
			पूर्ण अन्यथा अणु
				snम_लिखो(करोm->name, माप(करोm->name),
					 "%s/%02x", name, (पूर्णांक)(sकरोm - spec));
			पूर्ण

			list_add_tail(&करोm->head, &pm->करोमुख्यs);
			INIT_LIST_HEAD(&करोm->list);
			करोm->func = sकरोm->func;
			करोm->addr = addr;
			करोm->संकेत_nr = sकरोm->संकेत_nr;

			ssig = (sकरोm++)->संकेत;
			जबतक (ssig->name) अणु
				काष्ठा nvkm_perfsig *sig =
					&करोm->संकेत[ssig->संकेत];
				sig->name = ssig->name;
				ret = nvkm_perfsrc_new(pm, sig, ssig->source);
				अगर (ret)
					वापस ret;
				ssig++;
			पूर्ण

			addr += size_करोमुख्य;
		पूर्ण

		mask &= ~(1 << i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pm_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_pm *pm = nvkm_pm(engine);
	अगर (pm->func->fini)
		pm->func->fini(pm);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_pm_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_pm *pm = nvkm_pm(engine);
	काष्ठा nvkm_perfकरोm *करोm, *next_करोm;
	काष्ठा nvkm_perfsrc *src, *next_src;

	list_क्रम_each_entry_safe(करोm, next_करोm, &pm->करोमुख्यs, head) अणु
		list_del(&करोm->head);
		kमुक्त(करोm);
	पूर्ण

	list_क्रम_each_entry_safe(src, next_src, &pm->sources, head) अणु
		list_del(&src->head);
		kमुक्त(src->name);
		kमुक्त(src);
	पूर्ण

	वापस pm;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_pm = अणु
	.dtor = nvkm_pm_dtor,
	.fini = nvkm_pm_fini,
	.base.sclass = nvkm_pm_oclass_get,
पूर्ण;

पूर्णांक
nvkm_pm_ctor(स्थिर काष्ठा nvkm_pm_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm *pm)
अणु
	pm->func = func;
	INIT_LIST_HEAD(&pm->करोमुख्यs);
	INIT_LIST_HEAD(&pm->sources);
	spin_lock_init(&pm->client.lock);
	वापस nvkm_engine_ctor(&nvkm_pm, device, type, inst, true, &pm->engine);
पूर्ण
