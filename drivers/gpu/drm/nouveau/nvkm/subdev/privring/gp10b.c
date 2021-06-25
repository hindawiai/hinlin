<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
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
#समावेश <subdev/privring.h>

#समावेश "priv.h"

अटल पूर्णांक
gp10b_privring_init(काष्ठा nvkm_subdev *privring)
अणु
	काष्ठा nvkm_device *device = privring->device;

	nvkm_wr32(device, 0x1200a8, 0x0);

	/* init ring */
	nvkm_wr32(device, 0x12004c, 0x4);
	nvkm_wr32(device, 0x122204, 0x2);
	nvkm_rd32(device, 0x122204);

	/* समयout configuration */
	nvkm_wr32(device, 0x009080, 0x800186a0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
gp10b_privring = अणु
	.init = gp10b_privring_init,
	.पूर्णांकr = gk104_privring_पूर्णांकr,
पूर्ण;

पूर्णांक
gp10b_privring_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		   काष्ठा nvkm_subdev **pprivring)
अणु
	वापस nvkm_subdev_new_(&gp10b_privring, device, type, inst, pprivring);
पूर्ण
