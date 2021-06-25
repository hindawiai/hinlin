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
#समावेश <nvअगर/disp.h>
#समावेश <nvअगर/device.h>

#समावेश <nvअगर/class.h>

व्योम
nvअगर_disp_dtor(काष्ठा nvअगर_disp *disp)
अणु
	nvअगर_object_dtor(&disp->object);
पूर्ण

पूर्णांक
nvअगर_disp_ctor(काष्ठा nvअगर_device *device, स्थिर अक्षर *name, s32 oclass,
	       काष्ठा nvअगर_disp *disp)
अणु
	अटल स्थिर काष्ठा nvअगर_mclass disps[] = अणु
		अणु GA102_DISP, -1 पूर्ण,
		अणु TU102_DISP, -1 पूर्ण,
		अणु GV100_DISP, -1 पूर्ण,
		अणु GP102_DISP, -1 पूर्ण,
		अणु GP100_DISP, -1 पूर्ण,
		अणु GM200_DISP, -1 पूर्ण,
		अणु GM107_DISP, -1 पूर्ण,
		अणु GK110_DISP, -1 पूर्ण,
		अणु GK104_DISP, -1 पूर्ण,
		अणु GF110_DISP, -1 पूर्ण,
		अणु GT214_DISP, -1 पूर्ण,
		अणु GT206_DISP, -1 पूर्ण,
		अणु GT200_DISP, -1 पूर्ण,
		अणु   G82_DISP, -1 पूर्ण,
		अणु  NV50_DISP, -1 पूर्ण,
		अणु  NV04_DISP, -1 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	पूर्णांक cid = nvअगर_sclass(&device->object, disps, oclass);
	disp->object.client = शून्य;
	अगर (cid < 0)
		वापस cid;

	वापस nvअगर_object_ctor(&device->object, name ? name : "nvifDisp", 0,
				disps[cid].oclass, शून्य, 0, &disp->object);
पूर्ण
