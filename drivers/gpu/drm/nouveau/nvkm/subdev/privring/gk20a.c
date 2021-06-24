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
#समावेश <subdev/privring.h>
#समावेश <subdev/समयr.h>

अटल व्योम
gk20a_privring_init_privring_ring(काष्ठा nvkm_subdev *privring)
अणु
	काष्ठा nvkm_device *device = privring->device;
	nvkm_mask(device, 0x137250, 0x3f, 0);

	nvkm_mask(device, 0x000200, 0x20, 0);
	udelay(20);
	nvkm_mask(device, 0x000200, 0x20, 0x20);

	nvkm_wr32(device, 0x12004c, 0x4);
	nvkm_wr32(device, 0x122204, 0x2);
	nvkm_rd32(device, 0x122204);

	/*
	 * Bug: increase घड़ी समयout to aव्योम operation failure at high
	 * gpcclk rate.
	 */
	nvkm_wr32(device, 0x122354, 0x800);
	nvkm_wr32(device, 0x128328, 0x800);
	nvkm_wr32(device, 0x124320, 0x800);
पूर्ण

अटल व्योम
gk20a_privring_पूर्णांकr(काष्ठा nvkm_subdev *privring)
अणु
	काष्ठा nvkm_device *device = privring->device;
	u32 status0 = nvkm_rd32(device, 0x120058);

	अगर (status0 & 0x7) अणु
		nvkm_debug(privring, "resetting privring ring\n");
		gk20a_privring_init_privring_ring(privring);
	पूर्ण

	/* Acknowledge पूर्णांकerrupt */
	nvkm_mask(device, 0x12004c, 0x2, 0x2);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x12004c) & 0x0000003f))
			अवरोध;
	);
पूर्ण

अटल पूर्णांक
gk20a_privring_init(काष्ठा nvkm_subdev *privring)
अणु
	gk20a_privring_init_privring_ring(privring);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
gk20a_privring = अणु
	.init = gk20a_privring_init,
	.पूर्णांकr = gk20a_privring_पूर्णांकr,
पूर्ण;

पूर्णांक
gk20a_privring_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		   काष्ठा nvkm_subdev **pprivring)
अणु
	वापस nvkm_subdev_new_(&gk20a_privring, device, type, inst, pprivring);
पूर्ण
