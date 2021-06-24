<शैली गुरु>
/*
 * Copyright 2009 Red Hat Inc.
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
#समावेश "aux.h"
#समावेश "pad.h"

अटल पूर्णांक
nvkm_i2c_aux_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा nvkm_i2c_aux *aux = container_of(adap, typeof(*aux), i2c);
	काष्ठा i2c_msg *msg = msgs;
	पूर्णांक ret, mcnt = num;

	ret = nvkm_i2c_aux_acquire(aux);
	अगर (ret)
		वापस ret;

	जबतक (mcnt--) अणु
		u8 reमुख्यing = msg->len;
		u8 *ptr = msg->buf;

		जबतक (reमुख्यing) अणु
			u8 cnt, retries, cmd;

			अगर (msg->flags & I2C_M_RD)
				cmd = 1;
			अन्यथा
				cmd = 0;

			अगर (mcnt || reमुख्यing > 16)
				cmd |= 4; /* MOT */

			क्रम (retries = 0, cnt = 0;
			     retries < 32 && !cnt;
			     retries++) अणु
				cnt = min_t(u8, reमुख्यing, 16);
				ret = aux->func->xfer(aux, true, cmd,
						      msg->addr, ptr, &cnt);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
			अगर (!cnt) अणु
				AUX_TRACE(aux, "no data after 32 retries");
				ret = -EIO;
				जाओ out;
			पूर्ण

			ptr += cnt;
			reमुख्यing -= cnt;
		पूर्ण

		msg++;
	पूर्ण

	ret = num;
out:
	nvkm_i2c_aux_release(aux);
	वापस ret;
पूर्ण

अटल u32
nvkm_i2c_aux_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm
nvkm_i2c_aux_i2c_algo = अणु
	.master_xfer = nvkm_i2c_aux_i2c_xfer,
	.functionality = nvkm_i2c_aux_i2c_func
पूर्ण;

व्योम
nvkm_i2c_aux_monitor(काष्ठा nvkm_i2c_aux *aux, bool monitor)
अणु
	काष्ठा nvkm_i2c_pad *pad = aux->pad;
	AUX_TRACE(aux, "monitor: %s", monitor ? "yes" : "no");
	अगर (monitor)
		nvkm_i2c_pad_mode(pad, NVKM_I2C_PAD_AUX);
	अन्यथा
		nvkm_i2c_pad_mode(pad, NVKM_I2C_PAD_OFF);
पूर्ण

व्योम
nvkm_i2c_aux_release(काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_i2c_pad *pad = aux->pad;
	AUX_TRACE(aux, "release");
	nvkm_i2c_pad_release(pad);
	mutex_unlock(&aux->mutex);
पूर्ण

पूर्णांक
nvkm_i2c_aux_acquire(काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_i2c_pad *pad = aux->pad;
	पूर्णांक ret;

	AUX_TRACE(aux, "acquire");
	mutex_lock(&aux->mutex);

	अगर (aux->enabled)
		ret = nvkm_i2c_pad_acquire(pad, NVKM_I2C_PAD_AUX);
	अन्यथा
		ret = -EIO;

	अगर (ret)
		mutex_unlock(&aux->mutex);
	वापस ret;
पूर्ण

पूर्णांक
nvkm_i2c_aux_xfer(काष्ठा nvkm_i2c_aux *aux, bool retry, u8 type,
		  u32 addr, u8 *data, u8 *size)
अणु
	अगर (!*size && !aux->func->address_only) अणु
		AUX_ERR(aux, "address-only transaction dropped");
		वापस -ENOSYS;
	पूर्ण
	वापस aux->func->xfer(aux, retry, type, addr, data, size);
पूर्ण

पूर्णांक
nvkm_i2c_aux_lnk_ctl(काष्ठा nvkm_i2c_aux *aux, पूर्णांक nr, पूर्णांक bw, bool ef)
अणु
	अगर (aux->func->lnk_ctl)
		वापस aux->func->lnk_ctl(aux, nr, bw, ef);
	वापस -ENODEV;
पूर्ण

व्योम
nvkm_i2c_aux_del(काष्ठा nvkm_i2c_aux **paux)
अणु
	काष्ठा nvkm_i2c_aux *aux = *paux;
	अगर (aux && !WARN_ON(!aux->func)) अणु
		AUX_TRACE(aux, "dtor");
		list_del(&aux->head);
		i2c_del_adapter(&aux->i2c);
		kमुक्त(*paux);
		*paux = शून्य;
	पूर्ण
पूर्ण

व्योम
nvkm_i2c_aux_init(काष्ठा nvkm_i2c_aux *aux)
अणु
	AUX_TRACE(aux, "init");
	mutex_lock(&aux->mutex);
	aux->enabled = true;
	mutex_unlock(&aux->mutex);
पूर्ण

व्योम
nvkm_i2c_aux_fini(काष्ठा nvkm_i2c_aux *aux)
अणु
	AUX_TRACE(aux, "fini");
	mutex_lock(&aux->mutex);
	aux->enabled = false;
	mutex_unlock(&aux->mutex);
पूर्ण

पूर्णांक
nvkm_i2c_aux_ctor(स्थिर काष्ठा nvkm_i2c_aux_func *func,
		  काष्ठा nvkm_i2c_pad *pad, पूर्णांक id,
		  काष्ठा nvkm_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = pad->i2c->subdev.device;

	aux->func = func;
	aux->pad = pad;
	aux->id = id;
	mutex_init(&aux->mutex);
	list_add_tail(&aux->head, &pad->i2c->aux);
	AUX_TRACE(aux, "ctor");

	snम_लिखो(aux->i2c.name, माप(aux->i2c.name), "nvkm-%s-aux-%04x",
		 dev_name(device->dev), id);
	aux->i2c.owner = THIS_MODULE;
	aux->i2c.dev.parent = device->dev;
	aux->i2c.algo = &nvkm_i2c_aux_i2c_algo;
	वापस i2c_add_adapter(&aux->i2c);
पूर्ण

पूर्णांक
nvkm_i2c_aux_new_(स्थिर काष्ठा nvkm_i2c_aux_func *func,
		  काष्ठा nvkm_i2c_pad *pad, पूर्णांक id,
		  काष्ठा nvkm_i2c_aux **paux)
अणु
	अगर (!(*paux = kzalloc(माप(**paux), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_i2c_aux_ctor(func, pad, id, *paux);
पूर्ण
