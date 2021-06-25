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
#समावेश "bus.h"
#समावेश "pad.h"

#समावेश <core/option.h>

/*******************************************************************************
 * i2c-algo-bit
 ******************************************************************************/
अटल पूर्णांक
nvkm_i2c_bus_pre_xfer(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा nvkm_i2c_bus *bus = container_of(adap, typeof(*bus), i2c);
	वापस nvkm_i2c_bus_acquire(bus);
पूर्ण

अटल व्योम
nvkm_i2c_bus_post_xfer(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा nvkm_i2c_bus *bus = container_of(adap, typeof(*bus), i2c);
	वापस nvkm_i2c_bus_release(bus);
पूर्ण

अटल व्योम
nvkm_i2c_bus_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा nvkm_i2c_bus *bus = data;
	bus->func->drive_scl(bus, state);
पूर्ण

अटल व्योम
nvkm_i2c_bus_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा nvkm_i2c_bus *bus = data;
	bus->func->drive_sda(bus, state);
पूर्ण

अटल पूर्णांक
nvkm_i2c_bus_माला_लोcl(व्योम *data)
अणु
	काष्ठा nvkm_i2c_bus *bus = data;
	वापस bus->func->sense_scl(bus);
पूर्ण

अटल पूर्णांक
nvkm_i2c_bus_माला_लोda(व्योम *data)
अणु
	काष्ठा nvkm_i2c_bus *bus = data;
	वापस bus->func->sense_sda(bus);
पूर्ण

/*******************************************************************************
 * !i2c-algo-bit (off-chip i2c bus / hw i2c / पूर्णांकernal bit-banging algo)
 ******************************************************************************/
अटल पूर्णांक
nvkm_i2c_bus_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा nvkm_i2c_bus *bus = container_of(adap, typeof(*bus), i2c);
	पूर्णांक ret;

	ret = nvkm_i2c_bus_acquire(bus);
	अगर (ret)
		वापस ret;

	ret = bus->func->xfer(bus, msgs, num);
	nvkm_i2c_bus_release(bus);
	वापस ret;
पूर्ण

अटल u32
nvkm_i2c_bus_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm
nvkm_i2c_bus_algo = अणु
	.master_xfer = nvkm_i2c_bus_xfer,
	.functionality = nvkm_i2c_bus_func,
पूर्ण;

/*******************************************************************************
 * nvkm_i2c_bus base
 ******************************************************************************/
व्योम
nvkm_i2c_bus_init(काष्ठा nvkm_i2c_bus *bus)
अणु
	BUS_TRACE(bus, "init");
	अगर (bus->func->init)
		bus->func->init(bus);

	mutex_lock(&bus->mutex);
	bus->enabled = true;
	mutex_unlock(&bus->mutex);
पूर्ण

व्योम
nvkm_i2c_bus_fini(काष्ठा nvkm_i2c_bus *bus)
अणु
	BUS_TRACE(bus, "fini");
	mutex_lock(&bus->mutex);
	bus->enabled = false;
	mutex_unlock(&bus->mutex);
पूर्ण

व्योम
nvkm_i2c_bus_release(काष्ठा nvkm_i2c_bus *bus)
अणु
	काष्ठा nvkm_i2c_pad *pad = bus->pad;
	BUS_TRACE(bus, "release");
	nvkm_i2c_pad_release(pad);
	mutex_unlock(&bus->mutex);
पूर्ण

पूर्णांक
nvkm_i2c_bus_acquire(काष्ठा nvkm_i2c_bus *bus)
अणु
	काष्ठा nvkm_i2c_pad *pad = bus->pad;
	पूर्णांक ret;

	BUS_TRACE(bus, "acquire");
	mutex_lock(&bus->mutex);

	अगर (bus->enabled)
		ret = nvkm_i2c_pad_acquire(pad, NVKM_I2C_PAD_I2C);
	अन्यथा
		ret = -EIO;

	अगर (ret)
		mutex_unlock(&bus->mutex);
	वापस ret;
पूर्ण

पूर्णांक
nvkm_i2c_bus_probe(काष्ठा nvkm_i2c_bus *bus, स्थिर अक्षर *what,
		   काष्ठा nvkm_i2c_bus_probe *info,
		   bool (*match)(काष्ठा nvkm_i2c_bus *,
				 काष्ठा i2c_board_info *, व्योम *), व्योम *data)
अणु
	पूर्णांक i;

	BUS_DBG(bus, "probing %ss", what);
	क्रम (i = 0; info[i].dev.addr; i++) अणु
		u8 orig_udelay = 0;

		अगर ((bus->i2c.algo == &i2c_bit_algo) && (info[i].udelay != 0)) अणु
			काष्ठा i2c_algo_bit_data *algo = bus->i2c.algo_data;
			BUS_DBG(bus, "%dms delay instead of %dms",
				     info[i].udelay, algo->udelay);
			orig_udelay = algo->udelay;
			algo->udelay = info[i].udelay;
		पूर्ण

		अगर (nvkm_probe_i2c(&bus->i2c, info[i].dev.addr) &&
		    (!match || match(bus, &info[i].dev, data))) अणु
			BUS_DBG(bus, "detected %s: %s",
				what, info[i].dev.type);
			वापस i;
		पूर्ण

		अगर (orig_udelay) अणु
			काष्ठा i2c_algo_bit_data *algo = bus->i2c.algo_data;
			algo->udelay = orig_udelay;
		पूर्ण
	पूर्ण

	BUS_DBG(bus, "no devices found.");
	वापस -ENODEV;
पूर्ण

व्योम
nvkm_i2c_bus_del(काष्ठा nvkm_i2c_bus **pbus)
अणु
	काष्ठा nvkm_i2c_bus *bus = *pbus;
	अगर (bus && !WARN_ON(!bus->func)) अणु
		BUS_TRACE(bus, "dtor");
		list_del(&bus->head);
		i2c_del_adapter(&bus->i2c);
		kमुक्त(bus->i2c.algo_data);
		kमुक्त(*pbus);
		*pbus = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_i2c_bus_ctor(स्थिर काष्ठा nvkm_i2c_bus_func *func,
		  काष्ठा nvkm_i2c_pad *pad, पूर्णांक id,
		  काष्ठा nvkm_i2c_bus *bus)
अणु
	काष्ठा nvkm_device *device = pad->i2c->subdev.device;
	काष्ठा i2c_algo_bit_data *bit;
#अगर_अघोषित CONFIG_NOUVEAU_I2C_INTERNAL_DEFAULT
	स्थिर bool पूर्णांकernal = false;
#अन्यथा
	स्थिर bool पूर्णांकernal = true;
#पूर्ण_अगर
	पूर्णांक ret;

	bus->func = func;
	bus->pad = pad;
	bus->id = id;
	mutex_init(&bus->mutex);
	list_add_tail(&bus->head, &pad->i2c->bus);
	BUS_TRACE(bus, "ctor");

	snम_लिखो(bus->i2c.name, माप(bus->i2c.name), "nvkm-%s-bus-%04x",
		 dev_name(device->dev), id);
	bus->i2c.owner = THIS_MODULE;
	bus->i2c.dev.parent = device->dev;

	अगर ( bus->func->drive_scl &&
	    !nvkm_boolopt(device->cfgopt, "NvI2C", पूर्णांकernal)) अणु
		अगर (!(bit = kzalloc(माप(*bit), GFP_KERNEL)))
			वापस -ENOMEM;
		bit->udelay = 10;
		bit->समयout = usecs_to_jअगरfies(2200);
		bit->data = bus;
		bit->pre_xfer = nvkm_i2c_bus_pre_xfer;
		bit->post_xfer = nvkm_i2c_bus_post_xfer;
		bit->setscl = nvkm_i2c_bus_setscl;
		bit->setsda = nvkm_i2c_bus_setsda;
		bit->माला_लोcl = nvkm_i2c_bus_माला_लोcl;
		bit->माला_लोda = nvkm_i2c_bus_माला_लोda;
		bus->i2c.algo_data = bit;
		ret = i2c_bit_add_bus(&bus->i2c);
	पूर्ण अन्यथा अणु
		bus->i2c.algo = &nvkm_i2c_bus_algo;
		ret = i2c_add_adapter(&bus->i2c);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
nvkm_i2c_bus_new_(स्थिर काष्ठा nvkm_i2c_bus_func *func,
		  काष्ठा nvkm_i2c_pad *pad, पूर्णांक id,
		  काष्ठा nvkm_i2c_bus **pbus)
अणु
	अगर (!(*pbus = kzalloc(माप(**pbus), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_i2c_bus_ctor(func, pad, id, *pbus);
पूर्ण
