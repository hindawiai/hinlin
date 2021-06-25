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
#समावेश <nvअगर/user.h>
#समावेश <nvअगर/device.h>

#समावेश <nvअगर/class.h>

व्योम
nvअगर_user_dtor(काष्ठा nvअगर_device *device)
अणु
	अगर (device->user.func) अणु
		nvअगर_object_dtor(&device->user.object);
		device->user.func = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvअगर_user_ctor(काष्ठा nvअगर_device *device, स्थिर अक्षर *name)
अणु
	काष्ठा अणु
		s32 oclass;
		पूर्णांक version;
		स्थिर काष्ठा nvअगर_user_func *func;
	पूर्ण users[] = अणु
		अणु VOLTA_USERMODE_A, -1, &nvअगर_userc361 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	पूर्णांक cid, ret;

	अगर (device->user.func)
		वापस 0;

	cid = nvअगर_mclass(&device->object, users);
	अगर (cid < 0)
		वापस cid;

	ret = nvअगर_object_ctor(&device->object, name ? name : "nvifUsermode",
			       0, users[cid].oclass, शून्य, 0,
			       &device->user.object);
	अगर (ret)
		वापस ret;

	nvअगर_object_map(&device->user.object, शून्य, 0);
	device->user.func = users[cid].func;
	वापस 0;
पूर्ण
