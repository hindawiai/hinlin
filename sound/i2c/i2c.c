<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Generic i2c पूर्णांकerface क्रम ALSA
 *
 *   (c) 1998 Gerd Knorr <kraxel@cs.tu-berlin.de>
 *   Modअगरied क्रम the ALSA driver by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/core.h>
#समावेश <sound/i2c.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Generic i2c interface for ALSA");
MODULE_LICENSE("GPL");

अटल पूर्णांक snd_i2c_bit_sendbytes(काष्ठा snd_i2c_device *device,
				 अचिन्हित अक्षर *bytes, पूर्णांक count);
अटल पूर्णांक snd_i2c_bit_पढ़ोbytes(काष्ठा snd_i2c_device *device,
				 अचिन्हित अक्षर *bytes, पूर्णांक count);
अटल पूर्णांक snd_i2c_bit_probeaddr(काष्ठा snd_i2c_bus *bus,
				 अचिन्हित लघु addr);

अटल स्थिर काष्ठा snd_i2c_ops snd_i2c_bit_ops = अणु
	.sendbytes = snd_i2c_bit_sendbytes,
	.पढ़ोbytes = snd_i2c_bit_पढ़ोbytes,
	.probeaddr = snd_i2c_bit_probeaddr,
पूर्ण;

अटल पूर्णांक snd_i2c_bus_मुक्त(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_i2c_bus *slave;
	काष्ठा snd_i2c_device *device;

	अगर (snd_BUG_ON(!bus))
		वापस -EINVAL;
	जबतक (!list_empty(&bus->devices)) अणु
		device = snd_i2c_device(bus->devices.next);
		snd_i2c_device_मुक्त(device);
	पूर्ण
	अगर (bus->master)
		list_del(&bus->buses);
	अन्यथा अणु
		जबतक (!list_empty(&bus->buses)) अणु
			slave = snd_i2c_slave_bus(bus->buses.next);
			snd_device_मुक्त(bus->card, slave);
		पूर्ण
	पूर्ण
	अगर (bus->निजी_मुक्त)
		bus->निजी_मुक्त(bus);
	kमुक्त(bus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_i2c_bus_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_i2c_bus *bus = device->device_data;
	वापस snd_i2c_bus_मुक्त(bus);
पूर्ण

पूर्णांक snd_i2c_bus_create(काष्ठा snd_card *card, स्थिर अक्षर *name,
		       काष्ठा snd_i2c_bus *master, काष्ठा snd_i2c_bus **ri2c)
अणु
	काष्ठा snd_i2c_bus *bus;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_i2c_bus_dev_मुक्त,
	पूर्ण;

	*ri2c = शून्य;
	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (bus == शून्य)
		वापस -ENOMEM;
	mutex_init(&bus->lock_mutex);
	INIT_LIST_HEAD(&bus->devices);
	INIT_LIST_HEAD(&bus->buses);
	bus->card = card;
	bus->ops = &snd_i2c_bit_ops;
	अगर (master) अणु
		list_add_tail(&bus->buses, &master->buses);
		bus->master = master;
	पूर्ण
	strscpy(bus->name, name, माप(bus->name));
	err = snd_device_new(card, SNDRV_DEV_BUS, bus, &ops);
	अगर (err < 0) अणु
		snd_i2c_bus_मुक्त(bus);
		वापस err;
	पूर्ण
	*ri2c = bus;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_i2c_bus_create);

पूर्णांक snd_i2c_device_create(काष्ठा snd_i2c_bus *bus, स्थिर अक्षर *name,
			  अचिन्हित अक्षर addr, काष्ठा snd_i2c_device **rdevice)
अणु
	काष्ठा snd_i2c_device *device;

	*rdevice = शून्य;
	अगर (snd_BUG_ON(!bus))
		वापस -EINVAL;
	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (device == शून्य)
		वापस -ENOMEM;
	device->addr = addr;
	strscpy(device->name, name, माप(device->name));
	list_add_tail(&device->list, &bus->devices);
	device->bus = bus;
	*rdevice = device;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_i2c_device_create);

पूर्णांक snd_i2c_device_मुक्त(काष्ठा snd_i2c_device *device)
अणु
	अगर (device->bus)
		list_del(&device->list);
	अगर (device->निजी_मुक्त)
		device->निजी_मुक्त(device);
	kमुक्त(device);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_i2c_device_मुक्त);

पूर्णांक snd_i2c_sendbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	वापस device->bus->ops->sendbytes(device, bytes, count);
पूर्ण

EXPORT_SYMBOL(snd_i2c_sendbytes);

पूर्णांक snd_i2c_पढ़ोbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	वापस device->bus->ops->पढ़ोbytes(device, bytes, count);
पूर्ण

EXPORT_SYMBOL(snd_i2c_पढ़ोbytes);

पूर्णांक snd_i2c_probeaddr(काष्ठा snd_i2c_bus *bus, अचिन्हित लघु addr)
अणु
	वापस bus->ops->probeaddr(bus, addr);
पूर्ण

EXPORT_SYMBOL(snd_i2c_probeaddr);

/*
 *  bit-operations
 */

अटल अंतरभूत व्योम snd_i2c_bit_hw_start(काष्ठा snd_i2c_bus *bus)
अणु
	अगर (bus->hw_ops.bit->start)
		bus->hw_ops.bit->start(bus);
पूर्ण

अटल अंतरभूत व्योम snd_i2c_bit_hw_stop(काष्ठा snd_i2c_bus *bus)
अणु
	अगर (bus->hw_ops.bit->stop)
		bus->hw_ops.bit->stop(bus);
पूर्ण

अटल व्योम snd_i2c_bit_direction(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data)
अणु
	अगर (bus->hw_ops.bit->direction)
		bus->hw_ops.bit->direction(bus, घड़ी, data);
पूर्ण

अटल व्योम snd_i2c_bit_set(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data)
अणु
	bus->hw_ops.bit->setlines(bus, घड़ी, data);
पूर्ण

#अगर 0
अटल पूर्णांक snd_i2c_bit_घड़ी(काष्ठा snd_i2c_bus *bus)
अणु
	अगर (bus->hw_ops.bit->अ_लोlock)
		वापस bus->hw_ops.bit->अ_लोlock(bus);
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_i2c_bit_data(काष्ठा snd_i2c_bus *bus, पूर्णांक ack)
अणु
	वापस bus->hw_ops.bit->getdata(bus, ack);
पूर्ण

अटल व्योम snd_i2c_bit_start(काष्ठा snd_i2c_bus *bus)
अणु
	snd_i2c_bit_hw_start(bus);
	snd_i2c_bit_direction(bus, 1, 1);	/* SCL - wr, SDA - wr */
	snd_i2c_bit_set(bus, 1, 1);
	snd_i2c_bit_set(bus, 1, 0);
	snd_i2c_bit_set(bus, 0, 0);
पूर्ण

अटल व्योम snd_i2c_bit_stop(काष्ठा snd_i2c_bus *bus)
अणु
	snd_i2c_bit_set(bus, 0, 0);
	snd_i2c_bit_set(bus, 1, 0);
	snd_i2c_bit_set(bus, 1, 1);
	snd_i2c_bit_hw_stop(bus);
पूर्ण

अटल व्योम snd_i2c_bit_send(काष्ठा snd_i2c_bus *bus, पूर्णांक data)
अणु
	snd_i2c_bit_set(bus, 0, data);
	snd_i2c_bit_set(bus, 1, data);
	snd_i2c_bit_set(bus, 0, data);
पूर्ण

अटल पूर्णांक snd_i2c_bit_ack(काष्ठा snd_i2c_bus *bus)
अणु
	पूर्णांक ack;

	snd_i2c_bit_set(bus, 0, 1);
	snd_i2c_bit_set(bus, 1, 1);
	snd_i2c_bit_direction(bus, 1, 0);	/* SCL - wr, SDA - rd */
	ack = snd_i2c_bit_data(bus, 1);
	snd_i2c_bit_direction(bus, 1, 1);	/* SCL - wr, SDA - wr */
	snd_i2c_bit_set(bus, 0, 1);
	वापस ack ? -EIO : 0;
पूर्ण

अटल पूर्णांक snd_i2c_bit_sendbyte(काष्ठा snd_i2c_bus *bus, अचिन्हित अक्षर data)
अणु
	पूर्णांक i, err;

	क्रम (i = 7; i >= 0; i--)
		snd_i2c_bit_send(bus, !!(data & (1 << i)));
	err = snd_i2c_bit_ack(bus);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_i2c_bit_पढ़ोbyte(काष्ठा snd_i2c_bus *bus, पूर्णांक last)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर data = 0;

	snd_i2c_bit_set(bus, 0, 1);
	snd_i2c_bit_direction(bus, 1, 0);	/* SCL - wr, SDA - rd */
	क्रम (i = 7; i >= 0; i--) अणु
		snd_i2c_bit_set(bus, 1, 1);
		अगर (snd_i2c_bit_data(bus, 0))
			data |= (1 << i);
		snd_i2c_bit_set(bus, 0, 1);
	पूर्ण
	snd_i2c_bit_direction(bus, 1, 1);	/* SCL - wr, SDA - wr */
	snd_i2c_bit_send(bus, !!last);
	वापस data;
पूर्ण

अटल पूर्णांक snd_i2c_bit_sendbytes(काष्ठा snd_i2c_device *device,
				 अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	काष्ठा snd_i2c_bus *bus = device->bus;
	पूर्णांक err, res = 0;

	अगर (device->flags & SND_I2C_DEVICE_ADDRTEN)
		वापस -EIO;		/* not yet implemented */
	snd_i2c_bit_start(bus);
	err = snd_i2c_bit_sendbyte(bus, device->addr << 1);
	अगर (err < 0) अणु
		snd_i2c_bit_hw_stop(bus);
		वापस err;
	पूर्ण
	जबतक (count-- > 0) अणु
		err = snd_i2c_bit_sendbyte(bus, *bytes++);
		अगर (err < 0) अणु
			snd_i2c_bit_hw_stop(bus);
			वापस err;
		पूर्ण
		res++;
	पूर्ण
	snd_i2c_bit_stop(bus);
	वापस res;
पूर्ण

अटल पूर्णांक snd_i2c_bit_पढ़ोbytes(काष्ठा snd_i2c_device *device,
				 अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	काष्ठा snd_i2c_bus *bus = device->bus;
	पूर्णांक err, res = 0;

	अगर (device->flags & SND_I2C_DEVICE_ADDRTEN)
		वापस -EIO;		/* not yet implemented */
	snd_i2c_bit_start(bus);
	err = snd_i2c_bit_sendbyte(bus, (device->addr << 1) | 1);
	अगर (err < 0) अणु
		snd_i2c_bit_hw_stop(bus);
		वापस err;
	पूर्ण
	जबतक (count-- > 0) अणु
		err = snd_i2c_bit_पढ़ोbyte(bus, count == 0);
		अगर (err < 0) अणु
			snd_i2c_bit_hw_stop(bus);
			वापस err;
		पूर्ण
		*bytes++ = (अचिन्हित अक्षर)err;
		res++;
	पूर्ण
	snd_i2c_bit_stop(bus);
	वापस res;
पूर्ण

अटल पूर्णांक snd_i2c_bit_probeaddr(काष्ठा snd_i2c_bus *bus, अचिन्हित लघु addr)
अणु
	पूर्णांक err;

	अगर (addr & 0x8000)	/* 10-bit address */
		वापस -EIO;	/* not yet implemented */
	अगर (addr & 0x7f80)	/* invalid address */
		वापस -EINVAL;
	snd_i2c_bit_start(bus);
	err = snd_i2c_bit_sendbyte(bus, addr << 1);
	snd_i2c_bit_stop(bus);
	वापस err;
पूर्ण
