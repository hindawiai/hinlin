<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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

#समावेश <nvअगर/device.h>

u64
nvअगर_device_समय(काष्ठा nvअगर_device *device)
अणु
	अगर (!device->user.func) अणु
		काष्ठा nv_device_समय_v0 args = अणुपूर्ण;
		पूर्णांक ret = nvअगर_object_mthd(&device->object, NV_DEVICE_V0_TIME,
					   &args, माप(args));
		WARN_ON_ONCE(ret != 0);
		वापस args.समय;
	पूर्ण

	वापस device->user.func->समय(&device->user);
पूर्ण

व्योम
nvअगर_device_dtor(काष्ठा nvअगर_device *device)
अणु
	nvअगर_user_dtor(device);
	kमुक्त(device->runlist);
	device->runlist = शून्य;
	nvअगर_object_dtor(&device->object);
पूर्ण

पूर्णांक
nvअगर_device_ctor(काष्ठा nvअगर_object *parent, स्थिर अक्षर *name, u32 handle,
		 s32 oclass, व्योम *data, u32 size, काष्ठा nvअगर_device *device)
अणु
	पूर्णांक ret = nvअगर_object_ctor(parent, name ? name : "nvifDevice", handle,
				   oclass, data, size, &device->object);
	device->runlist = शून्य;
	device->user.func = शून्य;
	अगर (ret == 0) अणु
		device->info.version = 0;
		ret = nvअगर_object_mthd(&device->object, NV_DEVICE_V0_INFO,
				       &device->info, माप(device->info));
	पूर्ण
	वापस ret;
पूर्ण
