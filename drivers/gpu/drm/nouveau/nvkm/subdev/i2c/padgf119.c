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
 * Authors: Ben Skeggs
 */
#समावेश "pad.h"
#समावेश "aux.h"
#समावेश "bus.h"

अटल स्थिर काष्ठा nvkm_i2c_pad_func
gf119_i2c_pad_s_func = अणु
	.bus_new_4 = gf119_i2c_bus_new,
	.aux_new_6 = gf119_i2c_aux_new,
	.mode = g94_i2c_pad_mode,
पूर्ण;

पूर्णांक
gf119_i2c_pad_s_new(काष्ठा nvkm_i2c *i2c, पूर्णांक id, काष्ठा nvkm_i2c_pad **ppad)
अणु
	वापस nvkm_i2c_pad_new_(&gf119_i2c_pad_s_func, i2c, id, ppad);
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_pad_func
gf119_i2c_pad_x_func = अणु
	.bus_new_4 = gf119_i2c_bus_new,
	.aux_new_6 = gf119_i2c_aux_new,
पूर्ण;

पूर्णांक
gf119_i2c_pad_x_new(काष्ठा nvkm_i2c *i2c, पूर्णांक id, काष्ठा nvkm_i2c_pad **ppad)
अणु
	वापस nvkm_i2c_pad_new_(&gf119_i2c_pad_x_func, i2c, id, ppad);
पूर्ण
