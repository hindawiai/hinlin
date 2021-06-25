<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
#समावेश "pad.h"

अटल व्योम
nvkm_i2c_pad_mode_locked(काष्ठा nvkm_i2c_pad *pad, क्रमागत nvkm_i2c_pad_mode mode)
अणु
	PAD_TRACE(pad, "-> %s", (mode == NVKM_I2C_PAD_AUX) ? "aux" :
			      (mode == NVKM_I2C_PAD_I2C) ? "i2c" : "off");
	अगर (pad->func->mode)
		pad->func->mode(pad, mode);
पूर्ण

व्योम
nvkm_i2c_pad_mode(काष्ठा nvkm_i2c_pad *pad, क्रमागत nvkm_i2c_pad_mode mode)
अणु
	PAD_TRACE(pad, "mode %d", mode);
	mutex_lock(&pad->mutex);
	nvkm_i2c_pad_mode_locked(pad, mode);
	pad->mode = mode;
	mutex_unlock(&pad->mutex);
पूर्ण

व्योम
nvkm_i2c_pad_release(काष्ठा nvkm_i2c_pad *pad)
अणु
	PAD_TRACE(pad, "release");
	अगर (pad->mode == NVKM_I2C_PAD_OFF)
		nvkm_i2c_pad_mode_locked(pad, pad->mode);
	mutex_unlock(&pad->mutex);
पूर्ण

पूर्णांक
nvkm_i2c_pad_acquire(काष्ठा nvkm_i2c_pad *pad, क्रमागत nvkm_i2c_pad_mode mode)
अणु
	PAD_TRACE(pad, "acquire");
	mutex_lock(&pad->mutex);
	अगर (pad->mode != mode) अणु
		अगर (pad->mode != NVKM_I2C_PAD_OFF) अणु
			mutex_unlock(&pad->mutex);
			वापस -EBUSY;
		पूर्ण
		nvkm_i2c_pad_mode_locked(pad, mode);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
nvkm_i2c_pad_fini(काष्ठा nvkm_i2c_pad *pad)
अणु
	PAD_TRACE(pad, "fini");
	nvkm_i2c_pad_mode_locked(pad, NVKM_I2C_PAD_OFF);
पूर्ण

व्योम
nvkm_i2c_pad_init(काष्ठा nvkm_i2c_pad *pad)
अणु
	PAD_TRACE(pad, "init");
	nvkm_i2c_pad_mode_locked(pad, pad->mode);
पूर्ण

व्योम
nvkm_i2c_pad_del(काष्ठा nvkm_i2c_pad **ppad)
अणु
	काष्ठा nvkm_i2c_pad *pad = *ppad;
	अगर (pad) अणु
		PAD_TRACE(pad, "dtor");
		list_del(&pad->head);
		kमुक्त(pad);
		pad = शून्य;
	पूर्ण
पूर्ण

व्योम
nvkm_i2c_pad_ctor(स्थिर काष्ठा nvkm_i2c_pad_func *func, काष्ठा nvkm_i2c *i2c,
		  पूर्णांक id, काष्ठा nvkm_i2c_pad *pad)
अणु
	pad->func = func;
	pad->i2c = i2c;
	pad->id = id;
	pad->mode = NVKM_I2C_PAD_OFF;
	mutex_init(&pad->mutex);
	list_add_tail(&pad->head, &i2c->pad);
	PAD_TRACE(pad, "ctor");
पूर्ण

पूर्णांक
nvkm_i2c_pad_new_(स्थिर काष्ठा nvkm_i2c_pad_func *func, काष्ठा nvkm_i2c *i2c,
		  पूर्णांक id, काष्ठा nvkm_i2c_pad **ppad)
अणु
	अगर (!(*ppad = kzalloc(माप(**ppad), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_i2c_pad_ctor(func, i2c, id, *ppad);
	वापस 0;
पूर्ण
