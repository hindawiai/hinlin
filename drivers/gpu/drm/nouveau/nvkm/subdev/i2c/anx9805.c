<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#घोषणा anx9805_pad(p) container_of((p), काष्ठा anx9805_pad, base)
#घोषणा anx9805_bus(p) container_of((p), काष्ठा anx9805_bus, base)
#घोषणा anx9805_aux(p) container_of((p), काष्ठा anx9805_aux, base)
#समावेश "aux.h"
#समावेश "bus.h"

काष्ठा anx9805_pad अणु
	काष्ठा nvkm_i2c_pad base;
	काष्ठा nvkm_i2c_bus *bus;
	u8 addr;
पूर्ण;

काष्ठा anx9805_bus अणु
	काष्ठा nvkm_i2c_bus base;
	काष्ठा anx9805_pad *pad;
	u8 addr;
पूर्ण;

अटल पूर्णांक
anx9805_bus_xfer(काष्ठा nvkm_i2c_bus *base, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा anx9805_bus *bus = anx9805_bus(base);
	काष्ठा anx9805_pad *pad = bus->pad;
	काष्ठा i2c_adapter *adap = &pad->bus->i2c;
	काष्ठा i2c_msg *msg = msgs;
	पूर्णांक ret = -ETIMEDOUT;
	पूर्णांक i, j, cnt = num;
	u8 seg = 0x00, off = 0x00, पंचांगp;

	पंचांगp = nvkm_rdi2cr(adap, pad->addr, 0x07) & ~0x10;
	nvkm_wri2cr(adap, pad->addr, 0x07, पंचांगp | 0x10);
	nvkm_wri2cr(adap, pad->addr, 0x07, पंचांगp);
	nvkm_wri2cr(adap, bus->addr, 0x43, 0x05);
	mdelay(5);

	जबतक (cnt--) अणु
		अगर ( (msg->flags & I2C_M_RD) && msg->addr == 0x50) अणु
			nvkm_wri2cr(adap, bus->addr, 0x40, msg->addr << 1);
			nvkm_wri2cr(adap, bus->addr, 0x41, seg);
			nvkm_wri2cr(adap, bus->addr, 0x42, off);
			nvkm_wri2cr(adap, bus->addr, 0x44, msg->len);
			nvkm_wri2cr(adap, bus->addr, 0x45, 0x00);
			nvkm_wri2cr(adap, bus->addr, 0x43, 0x01);
			क्रम (i = 0; i < msg->len; i++) अणु
				j = 0;
				जबतक (nvkm_rdi2cr(adap, bus->addr, 0x46) & 0x10) अणु
					mdelay(5);
					अगर (j++ == 32)
						जाओ करोne;
				पूर्ण
				msg->buf[i] = nvkm_rdi2cr(adap, bus->addr, 0x47);
			पूर्ण
		पूर्ण अन्यथा
		अगर (!(msg->flags & I2C_M_RD)) अणु
			अगर (msg->addr == 0x50 && msg->len == 0x01) अणु
				off = msg->buf[0];
			पूर्ण अन्यथा
			अगर (msg->addr == 0x30 && msg->len == 0x01) अणु
				seg = msg->buf[0];
			पूर्ण अन्यथा
				जाओ करोne;
		पूर्ण अन्यथा अणु
			जाओ करोne;
		पूर्ण
		msg++;
	पूर्ण

	ret = num;
करोne:
	nvkm_wri2cr(adap, bus->addr, 0x43, 0x00);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_bus_func
anx9805_bus_func = अणु
	.xfer = anx9805_bus_xfer,
पूर्ण;

अटल पूर्णांक
anx9805_bus_new(काष्ठा nvkm_i2c_pad *base, पूर्णांक id, u8 drive,
		काष्ठा nvkm_i2c_bus **pbus)
अणु
	काष्ठा anx9805_pad *pad = anx9805_pad(base);
	काष्ठा anx9805_bus *bus;
	पूर्णांक ret;

	अगर (!(bus = kzalloc(माप(*bus), GFP_KERNEL)))
		वापस -ENOMEM;
	*pbus = &bus->base;
	bus->pad = pad;

	ret = nvkm_i2c_bus_ctor(&anx9805_bus_func, &pad->base, id, &bus->base);
	अगर (ret)
		वापस ret;

	चयन (pad->addr) अणु
	हाल 0x39: bus->addr = 0x3d; अवरोध;
	हाल 0x3b: bus->addr = 0x3f; अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा anx9805_aux अणु
	काष्ठा nvkm_i2c_aux base;
	काष्ठा anx9805_pad *pad;
	u8 addr;
पूर्ण;

अटल पूर्णांक
anx9805_aux_xfer(काष्ठा nvkm_i2c_aux *base, bool retry,
		 u8 type, u32 addr, u8 *data, u8 *size)
अणु
	काष्ठा anx9805_aux *aux = anx9805_aux(base);
	काष्ठा anx9805_pad *pad = aux->pad;
	काष्ठा i2c_adapter *adap = &pad->bus->i2c;
	पूर्णांक i, ret = -ETIMEDOUT;
	u8 buf[16] = अणुपूर्ण;
	u8 पंचांगp;

	AUX_DBG(&aux->base, "%02x %05x %d", type, addr, *size);

	पंचांगp = nvkm_rdi2cr(adap, pad->addr, 0x07) & ~0x04;
	nvkm_wri2cr(adap, pad->addr, 0x07, पंचांगp | 0x04);
	nvkm_wri2cr(adap, pad->addr, 0x07, पंचांगp);
	nvkm_wri2cr(adap, pad->addr, 0xf7, 0x01);

	nvkm_wri2cr(adap, aux->addr, 0xe4, 0x80);
	अगर (!(type & 1)) अणु
		स_नकल(buf, data, *size);
		AUX_DBG(&aux->base, "%16ph", buf);
		क्रम (i = 0; i < *size; i++)
			nvkm_wri2cr(adap, aux->addr, 0xf0 + i, buf[i]);
	पूर्ण
	nvkm_wri2cr(adap, aux->addr, 0xe5, ((*size - 1) << 4) | type);
	nvkm_wri2cr(adap, aux->addr, 0xe6, (addr & 0x000ff) >>  0);
	nvkm_wri2cr(adap, aux->addr, 0xe7, (addr & 0x0ff00) >>  8);
	nvkm_wri2cr(adap, aux->addr, 0xe8, (addr & 0xf0000) >> 16);
	nvkm_wri2cr(adap, aux->addr, 0xe9, 0x01);

	i = 0;
	जबतक ((पंचांगp = nvkm_rdi2cr(adap, aux->addr, 0xe9)) & 0x01) अणु
		mdelay(5);
		अगर (i++ == 32)
			जाओ करोne;
	पूर्ण

	अगर ((पंचांगp = nvkm_rdi2cr(adap, pad->addr, 0xf7)) & 0x01) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (type & 1) अणु
		क्रम (i = 0; i < *size; i++)
			buf[i] = nvkm_rdi2cr(adap, aux->addr, 0xf0 + i);
		AUX_DBG(&aux->base, "%16ph", buf);
		स_नकल(data, buf, *size);
	पूर्ण

	ret = 0;
करोne:
	nvkm_wri2cr(adap, pad->addr, 0xf7, 0x01);
	वापस ret;
पूर्ण

अटल पूर्णांक
anx9805_aux_lnk_ctl(काष्ठा nvkm_i2c_aux *base,
		    पूर्णांक link_nr, पूर्णांक link_bw, bool enh)
अणु
	काष्ठा anx9805_aux *aux = anx9805_aux(base);
	काष्ठा anx9805_pad *pad = aux->pad;
	काष्ठा i2c_adapter *adap = &pad->bus->i2c;
	u8 पंचांगp, i;

	AUX_DBG(&aux->base, "ANX9805 train %d %02x %d",
		link_nr, link_bw, enh);

	nvkm_wri2cr(adap, aux->addr, 0xa0, link_bw);
	nvkm_wri2cr(adap, aux->addr, 0xa1, link_nr | (enh ? 0x80 : 0x00));
	nvkm_wri2cr(adap, aux->addr, 0xa2, 0x01);
	nvkm_wri2cr(adap, aux->addr, 0xa8, 0x01);

	i = 0;
	जबतक ((पंचांगp = nvkm_rdi2cr(adap, aux->addr, 0xa8)) & 0x01) अणु
		mdelay(5);
		अगर (i++ == 100) अणु
			AUX_ERR(&aux->base, "link training timeout");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	अगर (पंचांगp & 0x70) अणु
		AUX_ERR(&aux->base, "link training failed");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_aux_func
anx9805_aux_func = अणु
	.xfer = anx9805_aux_xfer,
	.lnk_ctl = anx9805_aux_lnk_ctl,
पूर्ण;

अटल पूर्णांक
anx9805_aux_new(काष्ठा nvkm_i2c_pad *base, पूर्णांक id, u8 drive,
		काष्ठा nvkm_i2c_aux **pbus)
अणु
	काष्ठा anx9805_pad *pad = anx9805_pad(base);
	काष्ठा anx9805_aux *aux;
	पूर्णांक ret;

	अगर (!(aux = kzalloc(माप(*aux), GFP_KERNEL)))
		वापस -ENOMEM;
	*pbus = &aux->base;
	aux->pad = pad;

	ret = nvkm_i2c_aux_ctor(&anx9805_aux_func, &pad->base, id, &aux->base);
	अगर (ret)
		वापस ret;

	चयन (pad->addr) अणु
	हाल 0x39: aux->addr = 0x38; अवरोध;
	हाल 0x3b: aux->addr = 0x3c; अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_pad_func
anx9805_pad_func = अणु
	.bus_new_4 = anx9805_bus_new,
	.aux_new_6 = anx9805_aux_new,
पूर्ण;

पूर्णांक
anx9805_pad_new(काष्ठा nvkm_i2c_bus *bus, पूर्णांक id, u8 addr,
		काष्ठा nvkm_i2c_pad **ppad)
अणु
	काष्ठा anx9805_pad *pad;

	अगर (!(pad = kzalloc(माप(*pad), GFP_KERNEL)))
		वापस -ENOMEM;
	*ppad = &pad->base;

	nvkm_i2c_pad_ctor(&anx9805_pad_func, bus->pad->i2c, id, &pad->base);
	pad->bus = bus;
	pad->addr = addr;
	वापस 0;
पूर्ण
