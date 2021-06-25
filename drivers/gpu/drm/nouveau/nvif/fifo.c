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
#समावेश <nvअगर/fअगरo.h>

अटल पूर्णांक
nvअगर_fअगरo_runlists(काष्ठा nvअगर_device *device)
अणु
	काष्ठा nvअगर_object *object = &device->object;
	काष्ठा अणु
		काष्ठा nv_device_info_v1 m;
		काष्ठा अणु
			काष्ठा nv_device_info_v1_data runlists;
			काष्ठा nv_device_info_v1_data runlist[64];
		पूर्ण v;
	पूर्ण *a;
	पूर्णांक ret, i;

	अगर (device->runlist)
		वापस 0;

	अगर (!(a = kदो_स्मृति(माप(*a), GFP_KERNEL)))
		वापस -ENOMEM;
	a->m.version = 1;
	a->m.count = माप(a->v) / माप(a->v.runlists);
	a->v.runlists.mthd = NV_DEVICE_HOST_RUNLISTS;
	क्रम (i = 0; i < ARRAY_SIZE(a->v.runlist); i++) अणु
		a->v.runlist[i].mthd = NV_DEVICE_HOST_RUNLIST_ENGINES;
		a->v.runlist[i].data = i;
	पूर्ण

	ret = nvअगर_object_mthd(object, NV_DEVICE_V0_INFO, a, माप(*a));
	अगर (ret)
		जाओ करोne;

	device->runlists = fls64(a->v.runlists.data);
	device->runlist = kसुस्मृति(device->runlists, माप(*device->runlist),
				  GFP_KERNEL);
	अगर (!device->runlist) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < device->runlists; i++) अणु
		अगर (a->v.runlist[i].mthd != NV_DEVICE_INFO_INVALID)
			device->runlist[i].engines = a->v.runlist[i].data;
	पूर्ण

करोne:
	kमुक्त(a);
	वापस ret;
पूर्ण

u64
nvअगर_fअगरo_runlist(काष्ठा nvअगर_device *device, u64 engine)
अणु
	u64 runm = 0;
	पूर्णांक ret, i;

	अगर ((ret = nvअगर_fअगरo_runlists(device)))
		वापस runm;

	क्रम (i = 0; i < device->runlists; i++) अणु
		अगर (device->runlist[i].engines & engine)
			runm |= BIT_ULL(i);
	पूर्ण

	वापस runm;
पूर्ण
