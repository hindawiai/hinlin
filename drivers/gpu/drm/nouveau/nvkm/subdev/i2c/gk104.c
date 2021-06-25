<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
#समावेश "pad.h"

व्योम
gk104_aux_stat(काष्ठा nvkm_i2c *i2c, u32 *hi, u32 *lo, u32 *rq, u32 *tx)
अणु
	काष्ठा nvkm_device *device = i2c->subdev.device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00dc60);
	u32 stat = nvkm_rd32(device, 0x00dc68) & पूर्णांकr, i;
	क्रम (i = 0, *hi = *lo = *rq = *tx = 0; i < 8; i++) अणु
		अगर ((stat & (1 << (i * 4)))) *hi |= 1 << i;
		अगर ((stat & (2 << (i * 4)))) *lo |= 1 << i;
		अगर ((stat & (4 << (i * 4)))) *rq |= 1 << i;
		अगर ((stat & (8 << (i * 4)))) *tx |= 1 << i;
	पूर्ण
	nvkm_wr32(device, 0x00dc60, पूर्णांकr);
पूर्ण

व्योम
gk104_aux_mask(काष्ठा nvkm_i2c *i2c, u32 type, u32 mask, u32 data)
अणु
	काष्ठा nvkm_device *device = i2c->subdev.device;
	u32 temp = nvkm_rd32(device, 0x00dc68), i;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (mask & (1 << i)) अणु
			अगर (!(data & (1 << i))) अणु
				temp &= ~(type << (i * 4));
				जारी;
			पूर्ण
			temp |= type << (i * 4);
		पूर्ण
	पूर्ण
	nvkm_wr32(device, 0x00dc68, temp);
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_func
gk104_i2c = अणु
	.pad_x_new = gf119_i2c_pad_x_new,
	.pad_s_new = gf119_i2c_pad_s_new,
	.aux = 4,
	.aux_stat = gk104_aux_stat,
	.aux_mask = gk104_aux_mask,
पूर्ण;

पूर्णांक
gk104_i2c_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_i2c **pi2c)
अणु
	वापस nvkm_i2c_new_(&gk104_i2c, device, type, inst, pi2c);
पूर्ण
