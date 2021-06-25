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
 * all copies or substantial busions of the Software.
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
#घोषणा gm200_i2c_aux(p) container_of((p), काष्ठा gm200_i2c_aux, base)
#समावेश "aux.h"

काष्ठा gm200_i2c_aux अणु
	काष्ठा nvkm_i2c_aux base;
	पूर्णांक ch;
पूर्ण;

अटल व्योम
gm200_i2c_aux_fini(काष्ठा gm200_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = aux->base.pad->i2c->subdev.device;
	nvkm_mask(device, 0x00d954 + (aux->ch * 0x50), 0x00710000, 0x00000000);
पूर्ण

अटल पूर्णांक
gm200_i2c_aux_init(काष्ठा gm200_i2c_aux *aux)
अणु
	काष्ठा nvkm_device *device = aux->base.pad->i2c->subdev.device;
	स्थिर u32 unksel = 1; /* nfi which to use, or अगर it matters.. */
	स्थिर u32 ureq = unksel ? 0x00100000 : 0x00200000;
	स्थिर u32 urep = unksel ? 0x01000000 : 0x02000000;
	u32 ctrl, समयout;

	/* रुको up to 1ms क्रम any previous transaction to be करोne... */
	समयout = 1000;
	करो अणु
		ctrl = nvkm_rd32(device, 0x00d954 + (aux->ch * 0x50));
		udelay(1);
		अगर (!समयout--) अणु
			AUX_ERR(&aux->base, "begin idle timeout %08x", ctrl);
			वापस -EBUSY;
		पूर्ण
	पूर्ण जबतक (ctrl & 0x07010000);

	/* set some magic, and रुको up to 1ms क्रम it to appear */
	nvkm_mask(device, 0x00d954 + (aux->ch * 0x50), 0x00700000, ureq);
	समयout = 1000;
	करो अणु
		ctrl = nvkm_rd32(device, 0x00d954 + (aux->ch * 0x50));
		udelay(1);
		अगर (!समयout--) अणु
			AUX_ERR(&aux->base, "magic wait %08x", ctrl);
			gm200_i2c_aux_fini(aux);
			वापस -EBUSY;
		पूर्ण
	पूर्ण जबतक ((ctrl & 0x07000000) != urep);

	वापस 0;
पूर्ण

अटल पूर्णांक
gm200_i2c_aux_xfer(काष्ठा nvkm_i2c_aux *obj, bool retry,
		   u8 type, u32 addr, u8 *data, u8 *size)
अणु
	काष्ठा gm200_i2c_aux *aux = gm200_i2c_aux(obj);
	काष्ठा nvkm_i2c *i2c = aux->base.pad->i2c;
	काष्ठा nvkm_device *device = i2c->subdev.device;
	स्थिर u32 base = aux->ch * 0x50;
	u32 ctrl, stat, समयout, retries = 0;
	u32 xbuf[4] = अणुपूर्ण;
	पूर्णांक ret, i;

	AUX_TRACE(&aux->base, "%d: %08x %d", type, addr, *size);

	ret = gm200_i2c_aux_init(aux);
	अगर (ret < 0)
		जाओ out;

	stat = nvkm_rd32(device, 0x00d958 + base);
	अगर (!(stat & 0x10000000)) अणु
		AUX_TRACE(&aux->base, "sink not detected");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	nvkm_i2c_aux_स्वतःdpcd(i2c, aux->ch, false);

	अगर (!(type & 1)) अणु
		स_नकल(xbuf, data, *size);
		क्रम (i = 0; i < 16; i += 4) अणु
			AUX_TRACE(&aux->base, "wr %08x", xbuf[i / 4]);
			nvkm_wr32(device, 0x00d930 + base + i, xbuf[i / 4]);
		पूर्ण
	पूर्ण

	ctrl  = nvkm_rd32(device, 0x00d954 + base);
	ctrl &= ~0x0001f1ff;
	ctrl |= type << 12;
	ctrl |= (*size ? (*size - 1) : 0x00000100);
	nvkm_wr32(device, 0x00d950 + base, addr);

	/* (maybe) retry transaction a number of बार on failure... */
	करो अणु
		/* reset, and delay a जबतक अगर this is a retry */
		nvkm_wr32(device, 0x00d954 + base, 0x80000000 | ctrl);
		nvkm_wr32(device, 0x00d954 + base, 0x00000000 | ctrl);
		अगर (retries)
			udelay(400);

		/* transaction request, रुको up to 2ms क्रम it to complete */
		nvkm_wr32(device, 0x00d954 + base, 0x00010000 | ctrl);

		समयout = 2000;
		करो अणु
			ctrl = nvkm_rd32(device, 0x00d954 + base);
			udelay(1);
			अगर (!समयout--) अणु
				AUX_ERR(&aux->base, "timeout %08x", ctrl);
				ret = -EIO;
				जाओ out_err;
			पूर्ण
		पूर्ण जबतक (ctrl & 0x00010000);
		ret = 0;

		/* पढ़ो status, and check अगर transaction completed ok */
		stat = nvkm_mask(device, 0x00d958 + base, 0, 0);
		अगर ((stat & 0x000f0000) == 0x00080000 ||
		    (stat & 0x000f0000) == 0x00020000)
			ret = 1;
		अगर ((stat & 0x00000100))
			ret = -ETIMEDOUT;
		अगर ((stat & 0x00000e00))
			ret = -EIO;

		AUX_TRACE(&aux->base, "%02d %08x %08x", retries, ctrl, stat);
	पूर्ण जबतक (ret && retry && retries++ < 32);

	अगर (type & 1) अणु
		क्रम (i = 0; i < 16; i += 4) अणु
			xbuf[i / 4] = nvkm_rd32(device, 0x00d940 + base + i);
			AUX_TRACE(&aux->base, "rd %08x", xbuf[i / 4]);
		पूर्ण
		स_नकल(data, xbuf, *size);
		*size = stat & 0x0000001f;
	पूर्ण

out_err:
	nvkm_i2c_aux_स्वतःdpcd(i2c, aux->ch, true);
out:
	gm200_i2c_aux_fini(aux);
	वापस ret < 0 ? ret : (stat & 0x000f0000) >> 16;
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_aux_func
gm200_i2c_aux_func = अणु
	.address_only = true,
	.xfer = gm200_i2c_aux_xfer,
पूर्ण;

पूर्णांक
gm200_i2c_aux_new(काष्ठा nvkm_i2c_pad *pad, पूर्णांक index, u8 drive,
		काष्ठा nvkm_i2c_aux **paux)
अणु
	काष्ठा gm200_i2c_aux *aux;

	अगर (!(aux = kzalloc(माप(*aux), GFP_KERNEL)))
		वापस -ENOMEM;
	*paux = &aux->base;

	nvkm_i2c_aux_ctor(&gm200_i2c_aux_func, pad, index, &aux->base);
	aux->ch = drive;
	aux->base.पूर्णांकr = 1 << aux->ch;
	वापस 0;
पूर्ण
