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
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"
#समावेश "aux.h"
#समावेश "bus.h"
#समावेश "pad.h"

#समावेश <core/notअगरy.h>
#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/i2c.h>

अटल काष्ठा nvkm_i2c_pad *
nvkm_i2c_pad_find(काष्ठा nvkm_i2c *i2c, पूर्णांक id)
अणु
	काष्ठा nvkm_i2c_pad *pad;

	list_क्रम_each_entry(pad, &i2c->pad, head) अणु
		अगर (pad->id == id)
			वापस pad;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा nvkm_i2c_bus *
nvkm_i2c_bus_find(काष्ठा nvkm_i2c *i2c, पूर्णांक id)
अणु
	काष्ठा nvkm_bios *bios = i2c->subdev.device->bios;
	काष्ठा nvkm_i2c_bus *bus;

	अगर (id == NVKM_I2C_BUS_PRI || id == NVKM_I2C_BUS_SEC) अणु
		u8  ver, hdr, cnt, len;
		u16 i2c = dcb_i2c_table(bios, &ver, &hdr, &cnt, &len);
		अगर (i2c && ver >= 0x30) अणु
			u8 auxidx = nvbios_rd08(bios, i2c + 4);
			अगर (id == NVKM_I2C_BUS_PRI)
				id = NVKM_I2C_BUS_CCB((auxidx & 0x0f) >> 0);
			अन्यथा
				id = NVKM_I2C_BUS_CCB((auxidx & 0xf0) >> 4);
		पूर्ण अन्यथा अणु
			id = NVKM_I2C_BUS_CCB(2);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(bus, &i2c->bus, head) अणु
		अगर (bus->id == id)
			वापस bus;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा nvkm_i2c_aux *
nvkm_i2c_aux_find(काष्ठा nvkm_i2c *i2c, पूर्णांक id)
अणु
	काष्ठा nvkm_i2c_aux *aux;

	list_क्रम_each_entry(aux, &i2c->aux, head) अणु
		अगर (aux->id == id)
			वापस aux;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
nvkm_i2c_पूर्णांकr_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक id)
अणु
	काष्ठा nvkm_i2c *i2c = container_of(event, typeof(*i2c), event);
	काष्ठा nvkm_i2c_aux *aux = nvkm_i2c_aux_find(i2c, id);
	अगर (aux)
		i2c->func->aux_mask(i2c, type, aux->पूर्णांकr, 0);
पूर्ण

अटल व्योम
nvkm_i2c_पूर्णांकr_init(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक id)
अणु
	काष्ठा nvkm_i2c *i2c = container_of(event, typeof(*i2c), event);
	काष्ठा nvkm_i2c_aux *aux = nvkm_i2c_aux_find(i2c, id);
	अगर (aux)
		i2c->func->aux_mask(i2c, type, aux->पूर्णांकr, aux->पूर्णांकr);
पूर्ण

अटल पूर्णांक
nvkm_i2c_पूर्णांकr_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		   काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_i2c_ntfy_req *req = data;
	अगर (!WARN_ON(size != माप(*req))) अणु
		notअगरy->size  = माप(काष्ठा nvkm_i2c_ntfy_rep);
		notअगरy->types = req->mask;
		notअगरy->index = req->port;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_i2c_पूर्णांकr_func = अणु
	.ctor = nvkm_i2c_पूर्णांकr_ctor,
	.init = nvkm_i2c_पूर्णांकr_init,
	.fini = nvkm_i2c_पूर्णांकr_fini,
पूर्ण;

अटल व्योम
nvkm_i2c_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_i2c *i2c = nvkm_i2c(subdev);
	काष्ठा nvkm_i2c_aux *aux;
	u32 hi, lo, rq, tx;

	अगर (!i2c->func->aux_stat)
		वापस;

	i2c->func->aux_stat(i2c, &hi, &lo, &rq, &tx);
	अगर (!hi && !lo && !rq && !tx)
		वापस;

	list_क्रम_each_entry(aux, &i2c->aux, head) अणु
		u32 mask = 0;
		अगर (hi & aux->पूर्णांकr) mask |= NVKM_I2C_PLUG;
		अगर (lo & aux->पूर्णांकr) mask |= NVKM_I2C_UNPLUG;
		अगर (rq & aux->पूर्णांकr) mask |= NVKM_I2C_IRQ;
		अगर (tx & aux->पूर्णांकr) mask |= NVKM_I2C_DONE;
		अगर (mask) अणु
			काष्ठा nvkm_i2c_ntfy_rep rep = अणु
				.mask = mask,
			पूर्ण;
			nvkm_event_send(&i2c->event, rep.mask, aux->id,
					&rep, माप(rep));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_i2c_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_i2c *i2c = nvkm_i2c(subdev);
	काष्ठा nvkm_i2c_pad *pad;
	काष्ठा nvkm_i2c_bus *bus;
	काष्ठा nvkm_i2c_aux *aux;
	u32 mask;

	list_क्रम_each_entry(aux, &i2c->aux, head) अणु
		nvkm_i2c_aux_fini(aux);
	पूर्ण

	list_क्रम_each_entry(bus, &i2c->bus, head) अणु
		nvkm_i2c_bus_fini(bus);
	पूर्ण

	अगर ((mask = (1 << i2c->func->aux) - 1), i2c->func->aux_stat) अणु
		i2c->func->aux_mask(i2c, NVKM_I2C_ANY, mask, 0);
		i2c->func->aux_stat(i2c, &mask, &mask, &mask, &mask);
	पूर्ण

	list_क्रम_each_entry(pad, &i2c->pad, head) अणु
		nvkm_i2c_pad_fini(pad);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_i2c_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_i2c *i2c = nvkm_i2c(subdev);
	काष्ठा nvkm_i2c_bus *bus;
	काष्ठा nvkm_i2c_pad *pad;

	/*
	 * We init our i2c busses as early as possible, since they may be
	 * needed by the vbios init scripts on some cards
	 */
	list_क्रम_each_entry(pad, &i2c->pad, head)
		nvkm_i2c_pad_init(pad);
	list_क्रम_each_entry(bus, &i2c->bus, head)
		nvkm_i2c_bus_init(bus);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_i2c_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_i2c *i2c = nvkm_i2c(subdev);
	काष्ठा nvkm_i2c_bus *bus;
	काष्ठा nvkm_i2c_pad *pad;
	काष्ठा nvkm_i2c_aux *aux;

	list_क्रम_each_entry(pad, &i2c->pad, head) अणु
		nvkm_i2c_pad_init(pad);
	पूर्ण

	list_क्रम_each_entry(bus, &i2c->bus, head) अणु
		nvkm_i2c_bus_init(bus);
	पूर्ण

	list_क्रम_each_entry(aux, &i2c->aux, head) अणु
		nvkm_i2c_aux_init(aux);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_i2c_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_i2c *i2c = nvkm_i2c(subdev);

	nvkm_event_fini(&i2c->event);

	जबतक (!list_empty(&i2c->aux)) अणु
		काष्ठा nvkm_i2c_aux *aux =
			list_first_entry(&i2c->aux, typeof(*aux), head);
		nvkm_i2c_aux_del(&aux);
	पूर्ण

	जबतक (!list_empty(&i2c->bus)) अणु
		काष्ठा nvkm_i2c_bus *bus =
			list_first_entry(&i2c->bus, typeof(*bus), head);
		nvkm_i2c_bus_del(&bus);
	पूर्ण

	जबतक (!list_empty(&i2c->pad)) अणु
		काष्ठा nvkm_i2c_pad *pad =
			list_first_entry(&i2c->pad, typeof(*pad), head);
		nvkm_i2c_pad_del(&pad);
	पूर्ण

	वापस i2c;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_i2c = अणु
	.dtor = nvkm_i2c_dtor,
	.preinit = nvkm_i2c_preinit,
	.init = nvkm_i2c_init,
	.fini = nvkm_i2c_fini,
	.पूर्णांकr = nvkm_i2c_पूर्णांकr,
पूर्ण;

अटल स्थिर काष्ठा nvkm_i2c_drv अणु
	u8 bios;
	u8 addr;
	पूर्णांक (*pad_new)(काष्ठा nvkm_i2c_bus *, पूर्णांक id, u8 addr,
		       काष्ठा nvkm_i2c_pad **);
पूर्ण
nvkm_i2c_drv[] = अणु
	अणु 0x0d, 0x39, anx9805_pad_new पूर्ण,
	अणु 0x0e, 0x3b, anx9805_pad_new पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
nvkm_i2c_new_(स्थिर काष्ठा nvkm_i2c_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_i2c **pi2c)
अणु
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_i2c *i2c;
	काष्ठा dcb_i2c_entry ccbE;
	काष्ठा dcb_output dcbE;
	u8 ver, hdr;
	पूर्णांक ret, i;

	अगर (!(i2c = *pi2c = kzalloc(माप(*i2c), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_i2c, device, type, inst, &i2c->subdev);
	i2c->func = func;
	INIT_LIST_HEAD(&i2c->pad);
	INIT_LIST_HEAD(&i2c->bus);
	INIT_LIST_HEAD(&i2c->aux);

	i = -1;
	जबतक (!dcb_i2c_parse(bios, ++i, &ccbE)) अणु
		काष्ठा nvkm_i2c_pad *pad = शून्य;
		काष्ठा nvkm_i2c_bus *bus = शून्य;
		काष्ठा nvkm_i2c_aux *aux = शून्य;

		nvkm_debug(&i2c->subdev, "ccb %02x: type %02x drive %02x "
			   "sense %02x share %02x auxch %02x\n", i, ccbE.type,
			   ccbE.drive, ccbE.sense, ccbE.share, ccbE.auxch);

		अगर (ccbE.share != DCB_I2C_UNUSED) अणु
			स्थिर पूर्णांक id = NVKM_I2C_PAD_HYBRID(ccbE.share);
			अगर (!(pad = nvkm_i2c_pad_find(i2c, id)))
				ret = func->pad_s_new(i2c, id, &pad);
			अन्यथा
				ret = 0;
		पूर्ण अन्यथा अणु
			ret = func->pad_x_new(i2c, NVKM_I2C_PAD_CCB(i), &pad);
		पूर्ण

		अगर (ret) अणु
			nvkm_error(&i2c->subdev, "ccb %02x pad, %d\n", i, ret);
			nvkm_i2c_pad_del(&pad);
			जारी;
		पूर्ण

		अगर (pad->func->bus_new_0 && ccbE.type == DCB_I2C_NV04_BIT) अणु
			ret = pad->func->bus_new_0(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.drive,
						   ccbE.sense, &bus);
		पूर्ण अन्यथा
		अगर (pad->func->bus_new_4 &&
		    ( ccbE.type == DCB_I2C_NV4E_BIT ||
		      ccbE.type == DCB_I2C_NVIO_BIT ||
		     (ccbE.type == DCB_I2C_PMGR &&
		      ccbE.drive != DCB_I2C_UNUSED))) अणु
			ret = pad->func->bus_new_4(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.drive, &bus);
		पूर्ण

		अगर (ret) अणु
			nvkm_error(&i2c->subdev, "ccb %02x bus, %d\n", i, ret);
			nvkm_i2c_bus_del(&bus);
		पूर्ण

		अगर (pad->func->aux_new_6 &&
		    ( ccbE.type == DCB_I2C_NVIO_AUX ||
		     (ccbE.type == DCB_I2C_PMGR &&
		      ccbE.auxch != DCB_I2C_UNUSED))) अणु
			ret = pad->func->aux_new_6(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.auxch, &aux);
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण

		अगर (ret) अणु
			nvkm_error(&i2c->subdev, "ccb %02x aux, %d\n", i, ret);
			nvkm_i2c_aux_del(&aux);
		पूर्ण

		अगर (ccbE.type != DCB_I2C_UNUSED && !bus && !aux) अणु
			nvkm_warn(&i2c->subdev, "ccb %02x was ignored\n", i);
			जारी;
		पूर्ण
	पूर्ण

	i = -1;
	जबतक (dcb_outp_parse(bios, ++i, &ver, &hdr, &dcbE)) अणु
		स्थिर काष्ठा nvkm_i2c_drv *drv = nvkm_i2c_drv;
		काष्ठा nvkm_i2c_bus *bus;
		काष्ठा nvkm_i2c_pad *pad;

		/* पूर्णांकernal outमाला_दो handled by native i2c busses (above) */
		अगर (!dcbE.location)
			जारी;

		/* we need an i2c bus to talk to the बाह्यal encoder */
		bus = nvkm_i2c_bus_find(i2c, dcbE.i2c_index);
		अगर (!bus) अणु
			nvkm_debug(&i2c->subdev, "dcb %02x no bus\n", i);
			जारी;
		पूर्ण

		/* ... and a driver क्रम it */
		जबतक (drv->pad_new) अणु
			अगर (drv->bios == dcbE.extdev)
				अवरोध;
			drv++;
		पूर्ण

		अगर (!drv->pad_new) अणु
			nvkm_debug(&i2c->subdev, "dcb %02x drv %02x unknown\n",
				   i, dcbE.extdev);
			जारी;
		पूर्ण

		/* find/create an instance of the driver */
		pad = nvkm_i2c_pad_find(i2c, NVKM_I2C_PAD_EXT(dcbE.extdev));
		अगर (!pad) अणु
			स्थिर पूर्णांक id = NVKM_I2C_PAD_EXT(dcbE.extdev);
			ret = drv->pad_new(bus, id, drv->addr, &pad);
			अगर (ret) अणु
				nvkm_error(&i2c->subdev, "dcb %02x pad, %d\n",
					   i, ret);
				nvkm_i2c_pad_del(&pad);
				जारी;
			पूर्ण
		पूर्ण

		/* create any i2c bus / aux channel required by the output */
		अगर (pad->func->aux_new_6 && dcbE.type == DCB_OUTPUT_DP) अणु
			स्थिर पूर्णांक id = NVKM_I2C_AUX_EXT(dcbE.extdev);
			काष्ठा nvkm_i2c_aux *aux = शून्य;
			ret = pad->func->aux_new_6(pad, id, 0, &aux);
			अगर (ret) अणु
				nvkm_error(&i2c->subdev, "dcb %02x aux, %d\n",
					   i, ret);
				nvkm_i2c_aux_del(&aux);
			पूर्ण
		पूर्ण अन्यथा
		अगर (pad->func->bus_new_4) अणु
			स्थिर पूर्णांक id = NVKM_I2C_BUS_EXT(dcbE.extdev);
			काष्ठा nvkm_i2c_bus *bus = शून्य;
			ret = pad->func->bus_new_4(pad, id, 0, &bus);
			अगर (ret) अणु
				nvkm_error(&i2c->subdev, "dcb %02x bus, %d\n",
					   i, ret);
				nvkm_i2c_bus_del(&bus);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस nvkm_event_init(&nvkm_i2c_पूर्णांकr_func, 4, i, &i2c->event);
पूर्ण
