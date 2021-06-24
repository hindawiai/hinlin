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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "ctrl.h"

#समावेश <core/client.h>
#समावेश <subdev/clk.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0001.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nvkm_control_mthd_pstate_info(काष्ठा nvkm_control *ctrl, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_control_pstate_info_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_clk *clk = ctrl->device->clk;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(&ctrl->object, "control pstate info size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(&ctrl->object, "control pstate info vers %d\n",
			   args->v0.version);
	पूर्ण अन्यथा
		वापस ret;

	अगर (clk) अणु
		args->v0.count = clk->state_nr;
		args->v0.ustate_ac = clk->ustate_ac;
		args->v0.ustate_dc = clk->ustate_dc;
		args->v0.pwrsrc = clk->pwrsrc;
		args->v0.pstate = clk->pstate;
	पूर्ण अन्यथा अणु
		args->v0.count = 0;
		args->v0.ustate_ac = NVIF_CONTROL_PSTATE_INFO_V0_USTATE_DISABLE;
		args->v0.ustate_dc = NVIF_CONTROL_PSTATE_INFO_V0_USTATE_DISABLE;
		args->v0.pwrsrc = -ENOSYS;
		args->v0.pstate = NVIF_CONTROL_PSTATE_INFO_V0_PSTATE_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_control_mthd_pstate_attr(काष्ठा nvkm_control *ctrl, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_control_pstate_attr_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_clk *clk = ctrl->device->clk;
	स्थिर काष्ठा nvkm_करोमुख्य *करोमुख्य;
	काष्ठा nvkm_pstate *pstate;
	काष्ठा nvkm_cstate *cstate;
	पूर्णांक i = 0, j = -1;
	u32 lo, hi;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(&ctrl->object, "control pstate attr size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(&ctrl->object,
			   "control pstate attr vers %d state %d index %d\n",
			   args->v0.version, args->v0.state, args->v0.index);
		अगर (!clk)
			वापस -ENODEV;
		अगर (args->v0.state < NVIF_CONTROL_PSTATE_ATTR_V0_STATE_CURRENT)
			वापस -EINVAL;
		अगर (args->v0.state >= clk->state_nr)
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस ret;
	करोमुख्य = clk->करोमुख्यs;

	जबतक (करोमुख्य->name != nv_clk_src_max) अणु
		अगर (करोमुख्य->mname && ++j == args->v0.index)
			अवरोध;
		करोमुख्य++;
	पूर्ण

	अगर (करोमुख्य->name == nv_clk_src_max)
		वापस -EINVAL;

	अगर (args->v0.state != NVIF_CONTROL_PSTATE_ATTR_V0_STATE_CURRENT) अणु
		list_क्रम_each_entry(pstate, &clk->states, head) अणु
			अगर (i++ == args->v0.state)
				अवरोध;
		पूर्ण

		lo = pstate->base.करोमुख्य[करोमुख्य->name];
		hi = lo;
		list_क्रम_each_entry(cstate, &pstate->list, head) अणु
			lo = min(lo, cstate->करोमुख्य[करोमुख्य->name]);
			hi = max(hi, cstate->करोमुख्य[करोमुख्य->name]);
		पूर्ण

		args->v0.state = pstate->pstate;
	पूर्ण अन्यथा अणु
		lo = max(nvkm_clk_पढ़ो(clk, करोमुख्य->name), 0);
		hi = lo;
	पूर्ण

	snम_लिखो(args->v0.name, माप(args->v0.name), "%s", करोमुख्य->mname);
	snम_लिखो(args->v0.unit, माप(args->v0.unit), "MHz");
	args->v0.min = lo / करोमुख्य->mभाग;
	args->v0.max = hi / करोमुख्य->mभाग;

	args->v0.index = 0;
	जबतक ((++करोमुख्य)->name != nv_clk_src_max) अणु
		अगर (करोमुख्य->mname) अणु
			args->v0.index = ++j;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_control_mthd_pstate_user(काष्ठा nvkm_control *ctrl, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_control_pstate_user_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_clk *clk = ctrl->device->clk;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(&ctrl->object, "control pstate user size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(&ctrl->object,
			   "control pstate user vers %d ustate %d pwrsrc %d\n",
			   args->v0.version, args->v0.ustate, args->v0.pwrsrc);
		अगर (!clk)
			वापस -ENODEV;
	पूर्ण अन्यथा
		वापस ret;

	अगर (args->v0.pwrsrc >= 0) अणु
		ret |= nvkm_clk_ustate(clk, args->v0.ustate, args->v0.pwrsrc);
	पूर्ण अन्यथा अणु
		ret |= nvkm_clk_ustate(clk, args->v0.ustate, 0);
		ret |= nvkm_clk_ustate(clk, args->v0.ustate, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_control_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_control *ctrl = nvkm_control(object);
	चयन (mthd) अणु
	हाल NVIF_CONTROL_PSTATE_INFO:
		वापस nvkm_control_mthd_pstate_info(ctrl, data, size);
	हाल NVIF_CONTROL_PSTATE_ATTR:
		वापस nvkm_control_mthd_pstate_attr(ctrl, data, size);
	हाल NVIF_CONTROL_PSTATE_USER:
		वापस nvkm_control_mthd_pstate_user(ctrl, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_control = अणु
	.mthd = nvkm_control_mthd,
पूर्ण;

अटल पूर्णांक
nvkm_control_new(काष्ठा nvkm_device *device, स्थिर काष्ठा nvkm_oclass *oclass,
		 व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_control *ctrl;

	अगर (!(ctrl = kzalloc(माप(*ctrl), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &ctrl->object;
	ctrl->device = device;

	nvkm_object_ctor(&nvkm_control, oclass, &ctrl->object);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_device_oclass
nvkm_control_oclass = अणु
	.base.oclass = NVIF_CLASS_CONTROL,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = nvkm_control_new,
पूर्ण;
