<शैली गुरु>
/*
 * Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#घोषणा gk20a_pmu(p) container_of((p), काष्ठा gk20a_pmu, base)
#समावेश "priv.h"

#समावेश <subdev/clk.h>
#समावेश <subdev/समयr.h>
#समावेश <subdev/volt.h>

#घोषणा BUSY_SLOT	0
#घोषणा CLK_SLOT	7

काष्ठा gk20a_pmu_dvfs_data अणु
	पूर्णांक p_load_target;
	पूर्णांक p_load_max;
	पूर्णांक p_smooth;
	अचिन्हित पूर्णांक avg_load;
पूर्ण;

काष्ठा gk20a_pmu अणु
	काष्ठा nvkm_pmu base;
	काष्ठा nvkm_alarm alarm;
	काष्ठा gk20a_pmu_dvfs_data *data;
पूर्ण;

काष्ठा gk20a_pmu_dvfs_dev_status अणु
	u32 total;
	u32 busy;
पूर्ण;

अटल पूर्णांक
gk20a_pmu_dvfs_target(काष्ठा gk20a_pmu *pmu, पूर्णांक *state)
अणु
	काष्ठा nvkm_clk *clk = pmu->base.subdev.device->clk;

	वापस nvkm_clk_astate(clk, *state, 0, false);
पूर्ण

अटल व्योम
gk20a_pmu_dvfs_get_cur_state(काष्ठा gk20a_pmu *pmu, पूर्णांक *state)
अणु
	काष्ठा nvkm_clk *clk = pmu->base.subdev.device->clk;

	*state = clk->pstate;
पूर्ण

अटल पूर्णांक
gk20a_pmu_dvfs_get_target_state(काष्ठा gk20a_pmu *pmu,
				पूर्णांक *state, पूर्णांक load)
अणु
	काष्ठा gk20a_pmu_dvfs_data *data = pmu->data;
	काष्ठा nvkm_clk *clk = pmu->base.subdev.device->clk;
	पूर्णांक cur_level, level;

	/* For GK20A, the perक्रमmance level is directly mapped to pstate */
	level = cur_level = clk->pstate;

	अगर (load > data->p_load_max) अणु
		level = min(clk->state_nr - 1, level + (clk->state_nr / 3));
	पूर्ण अन्यथा अणु
		level += ((load - data->p_load_target) * 10 /
				data->p_load_target) / 2;
		level = max(0, level);
		level = min(clk->state_nr - 1, level);
	पूर्ण

	nvkm_trace(&pmu->base.subdev, "cur level = %d, new level = %d\n",
		   cur_level, level);

	*state = level;

	वापस (level != cur_level);
पूर्ण

अटल व्योम
gk20a_pmu_dvfs_get_dev_status(काष्ठा gk20a_pmu *pmu,
			      काष्ठा gk20a_pmu_dvfs_dev_status *status)
अणु
	काष्ठा nvkm_falcon *falcon = &pmu->base.falcon;

	status->busy = nvkm_falcon_rd32(falcon, 0x508 + (BUSY_SLOT * 0x10));
	status->total= nvkm_falcon_rd32(falcon, 0x508 + (CLK_SLOT * 0x10));
पूर्ण

अटल व्योम
gk20a_pmu_dvfs_reset_dev_status(काष्ठा gk20a_pmu *pmu)
अणु
	काष्ठा nvkm_falcon *falcon = &pmu->base.falcon;

	nvkm_falcon_wr32(falcon, 0x508 + (BUSY_SLOT * 0x10), 0x80000000);
	nvkm_falcon_wr32(falcon, 0x508 + (CLK_SLOT * 0x10), 0x80000000);
पूर्ण

अटल व्योम
gk20a_pmu_dvfs_work(काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा gk20a_pmu *pmu =
		container_of(alarm, काष्ठा gk20a_pmu, alarm);
	काष्ठा gk20a_pmu_dvfs_data *data = pmu->data;
	काष्ठा gk20a_pmu_dvfs_dev_status status;
	काष्ठा nvkm_subdev *subdev = &pmu->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_clk *clk = device->clk;
	काष्ठा nvkm_समयr *पंचांगr = device->समयr;
	काष्ठा nvkm_volt *volt = device->volt;
	u32 utilization = 0;
	पूर्णांक state;

	/*
	 * The PMU is initialized beक्रमe CLK and VOLT, so we have to make sure the
	 * CLK and VOLT are पढ़ोy here.
	 */
	अगर (!clk || !volt)
		जाओ resched;

	gk20a_pmu_dvfs_get_dev_status(pmu, &status);

	अगर (status.total)
		utilization = भाग_u64((u64)status.busy * 100, status.total);

	data->avg_load = (data->p_smooth * data->avg_load) + utilization;
	data->avg_load /= data->p_smooth + 1;
	nvkm_trace(subdev, "utilization = %d %%, avg_load = %d %%\n",
		   utilization, data->avg_load);

	gk20a_pmu_dvfs_get_cur_state(pmu, &state);

	अगर (gk20a_pmu_dvfs_get_target_state(pmu, &state, data->avg_load)) अणु
		nvkm_trace(subdev, "set new state to %d\n", state);
		gk20a_pmu_dvfs_target(pmu, &state);
	पूर्ण

resched:
	gk20a_pmu_dvfs_reset_dev_status(pmu);
	nvkm_समयr_alarm(पंचांगr, 100000000, alarm);
पूर्ण

अटल व्योम
gk20a_pmu_fini(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा gk20a_pmu *gpmu = gk20a_pmu(pmu);
	nvkm_समयr_alarm(pmu->subdev.device->समयr, 0, &gpmu->alarm);

	nvkm_falcon_put(&pmu->falcon, &pmu->subdev);
पूर्ण

अटल पूर्णांक
gk20a_pmu_init(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा gk20a_pmu *gpmu = gk20a_pmu(pmu);
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;
	काष्ठा nvkm_device *device = pmu->subdev.device;
	काष्ठा nvkm_falcon *falcon = &pmu->falcon;
	पूर्णांक ret;

	ret = nvkm_falcon_get(falcon, subdev);
	अगर (ret) अणु
		nvkm_error(subdev, "cannot acquire %s falcon!\n", falcon->name);
		वापस ret;
	पूर्ण

	/* init pwr perf counter */
	nvkm_falcon_wr32(falcon, 0x504 + (BUSY_SLOT * 0x10), 0x00200001);
	nvkm_falcon_wr32(falcon, 0x50c + (BUSY_SLOT * 0x10), 0x00000002);
	nvkm_falcon_wr32(falcon, 0x50c + (CLK_SLOT * 0x10), 0x00000003);

	nvkm_समयr_alarm(device->समयr, 2000000000, &gpmu->alarm);
	वापस 0;
पूर्ण

अटल काष्ठा gk20a_pmu_dvfs_data
gk20a_dvfs_data= अणु
	.p_load_target = 70,
	.p_load_max = 90,
	.p_smooth = 1,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_func
gk20a_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.enabled = gf100_pmu_enabled,
	.init = gk20a_pmu_init,
	.fini = gk20a_pmu_fini,
	.reset = gf100_pmu_reset,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gk20a_pmu_fwअगर[] = अणु
	अणु -1, gf100_pmu_nofw, &gk20a_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gk20a_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	काष्ठा gk20a_pmu *pmu;
	पूर्णांक ret;

	अगर (!(pmu = kzalloc(माप(*pmu), GFP_KERNEL)))
		वापस -ENOMEM;
	*ppmu = &pmu->base;

	ret = nvkm_pmu_ctor(gk20a_pmu_fwअगर, device, type, inst, &pmu->base);
	अगर (ret)
		वापस ret;

	pmu->data = &gk20a_dvfs_data;
	nvkm_alarm_init(&pmu->alarm, gk20a_pmu_dvfs_work);
	वापस 0;
पूर्ण
