<शैली गुरु>
/*
 * Copyright 2016 Karol Herbst
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
 * Authors: Karol Herbst
 */
#समावेश "priv.h"

#समावेश <subdev/fuse.h>

अटल पूर्णांक
gf100_volt_speeकरो_पढ़ो(काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_device *device = volt->subdev.device;
	काष्ठा nvkm_fuse *fuse = device->fuse;

	अगर (!fuse)
		वापस -EINVAL;

	वापस nvkm_fuse_पढ़ो(fuse, 0x1cc);
पूर्ण

पूर्णांक
gf100_volt_oneinit(काष्ठा nvkm_volt *volt)
अणु
	काष्ठा nvkm_subdev *subdev = &volt->subdev;
	अगर (volt->speeकरो <= 0)
		nvkm_error(subdev, "couldn't find speedo value, volting not "
			   "possible\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_volt_func
gf100_volt = अणु
	.oneinit = gf100_volt_oneinit,
	.vid_get = nvkm_voltgpio_get,
	.vid_set = nvkm_voltgpio_set,
	.speeकरो_पढ़ो = gf100_volt_speeकरो_पढ़ो,
पूर्ण;

पूर्णांक
gf100_volt_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_volt **pvolt)
अणु
	काष्ठा nvkm_volt *volt;
	पूर्णांक ret;

	ret = nvkm_volt_new_(&gf100_volt, device, type, inst, &volt);
	*pvolt = volt;
	अगर (ret)
		वापस ret;

	वापस nvkm_voltgpio_init(volt);
पूर्ण
