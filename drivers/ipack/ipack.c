<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Industry-pack bus support functions.
 *
 * Copyright (C) 2011-2012 CERN (www.cern.ch)
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/ipack.h>

#घोषणा to_ipack_dev(device) container_of(device, काष्ठा ipack_device, dev)
#घोषणा to_ipack_driver(drv) container_of(drv, काष्ठा ipack_driver, driver)

अटल DEFINE_IDA(ipack_ida);

अटल व्योम ipack_device_release(काष्ठा device *dev)
अणु
	काष्ठा ipack_device *device = to_ipack_dev(dev);
	kमुक्त(device->id);
	device->release(device);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ipack_device_id *
ipack_match_one_device(स्थिर काष्ठा ipack_device_id *id,
		       स्थिर काष्ठा ipack_device *device)
अणु
	अगर ((id->क्रमmat == IPACK_ANY_FORMAT ||
				id->क्रमmat == device->id_क्रमmat) &&
	    (id->venकरोr == IPACK_ANY_ID || id->venकरोr == device->id_venकरोr) &&
	    (id->device == IPACK_ANY_ID || id->device == device->id_device))
		वापस id;
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा ipack_device_id *
ipack_match_id(स्थिर काष्ठा ipack_device_id *ids, काष्ठा ipack_device *idev)
अणु
	अगर (ids) अणु
		जबतक (ids->venकरोr || ids->device) अणु
			अगर (ipack_match_one_device(ids, idev))
				वापस ids;
			ids++;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ipack_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ipack_device *idev = to_ipack_dev(dev);
	काष्ठा ipack_driver *idrv = to_ipack_driver(drv);
	स्थिर काष्ठा ipack_device_id *found_id;

	found_id = ipack_match_id(idrv->id_table, idev);
	वापस found_id ? 1 : 0;
पूर्ण

अटल पूर्णांक ipack_bus_probe(काष्ठा device *device)
अणु
	काष्ठा ipack_device *dev = to_ipack_dev(device);
	काष्ठा ipack_driver *drv = to_ipack_driver(device->driver);

	वापस drv->ops->probe(dev);
पूर्ण

अटल पूर्णांक ipack_bus_हटाओ(काष्ठा device *device)
अणु
	काष्ठा ipack_device *dev = to_ipack_dev(device);
	काष्ठा ipack_driver *drv = to_ipack_driver(device->driver);

	अगर (drv->ops->हटाओ)
		drv->ops->हटाओ(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ipack_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ipack_device *idev;

	अगर (!dev)
		वापस -ENODEV;

	idev = to_ipack_dev(dev);

	अगर (add_uevent_var(env,
			   "MODALIAS=ipack:f%02Xv%08Xd%08X", idev->id_क्रमmat,
			   idev->id_venकरोr, idev->id_device))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#घोषणा ipack_device_attr(field, क्रमmat_string)				\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,		\
		अक्षर *buf)						\
अणु									\
	काष्ठा ipack_device *idev = to_ipack_dev(dev);			\
	वापस प्र_लिखो(buf, क्रमmat_string, idev->field);		\
पूर्ण

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक i, c, l, s;
	काष्ठा ipack_device *idev = to_ipack_dev(dev);


	चयन (idev->id_क्रमmat) अणु
	हाल IPACK_ID_VERSION_1:
		l = 0x7; s = 1; अवरोध;
	हाल IPACK_ID_VERSION_2:
		l = 0xf; s = 2; अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण
	c = 0;
	क्रम (i = 0; i < idev->id_avail; i++) अणु
		अगर (i > 0) अणु
			अगर ((i & l) == 0)
				buf[c++] = '\n';
			अन्यथा अगर ((i & s) == 0)
				buf[c++] = ' ';
		पूर्ण
		प्र_लिखो(&buf[c], "%02x", idev->id[i]);
		c += 2;
	पूर्ण
	buf[c++] = '\n';
	वापस c;
पूर्ण

अटल sमाप_प्रकार
id_venकरोr_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipack_device *idev = to_ipack_dev(dev);
	चयन (idev->id_क्रमmat) अणु
	हाल IPACK_ID_VERSION_1:
		वापस प्र_लिखो(buf, "0x%02x\n", idev->id_venकरोr);
	हाल IPACK_ID_VERSION_2:
		वापस प्र_लिखो(buf, "0x%06x\n", idev->id_venकरोr);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
id_device_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipack_device *idev = to_ipack_dev(dev);
	चयन (idev->id_क्रमmat) अणु
	हाल IPACK_ID_VERSION_1:
		वापस प्र_लिखो(buf, "0x%02x\n", idev->id_device);
	हाल IPACK_ID_VERSION_2:
		वापस प्र_लिखो(buf, "0x%04x\n", idev->id_device);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipack_device *idev = to_ipack_dev(dev);

	वापस प्र_लिखो(buf, "ipac:f%02Xv%08Xd%08X", idev->id_क्रमmat,
		       idev->id_venकरोr, idev->id_device);
पूर्ण

ipack_device_attr(id_क्रमmat, "0x%hhx\n");

अटल DEVICE_ATTR_RO(id);
अटल DEVICE_ATTR_RO(id_device);
अटल DEVICE_ATTR_RO(id_क्रमmat);
अटल DEVICE_ATTR_RO(id_venकरोr);
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ipack_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_id_device.attr,
	&dev_attr_id_क्रमmat.attr,
	&dev_attr_id_venकरोr.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ipack);

अटल काष्ठा bus_type ipack_bus_type = अणु
	.name      = "ipack",
	.probe     = ipack_bus_probe,
	.match     = ipack_bus_match,
	.हटाओ    = ipack_bus_हटाओ,
	.dev_groups = ipack_groups,
	.uevent	   = ipack_uevent,
पूर्ण;

काष्ठा ipack_bus_device *ipack_bus_रेजिस्टर(काष्ठा device *parent, पूर्णांक slots,
					    स्थिर काष्ठा ipack_bus_ops *ops,
					    काष्ठा module *owner)
अणु
	पूर्णांक bus_nr;
	काष्ठा ipack_bus_device *bus;

	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	bus_nr = ida_simple_get(&ipack_ida, 0, 0, GFP_KERNEL);
	अगर (bus_nr < 0) अणु
		kमुक्त(bus);
		वापस शून्य;
	पूर्ण

	bus->bus_nr = bus_nr;
	bus->parent = parent;
	bus->slots = slots;
	bus->ops = ops;
	bus->owner = owner;
	वापस bus;
पूर्ण
EXPORT_SYMBOL_GPL(ipack_bus_रेजिस्टर);

अटल पूर्णांक ipack_unरेजिस्टर_bus_member(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा ipack_device *idev = to_ipack_dev(dev);
	काष्ठा ipack_bus_device *bus = data;

	अगर (idev->bus == bus)
		ipack_device_del(idev);

	वापस 1;
पूर्ण

पूर्णांक ipack_bus_unरेजिस्टर(काष्ठा ipack_bus_device *bus)
अणु
	bus_क्रम_each_dev(&ipack_bus_type, शून्य, bus,
		ipack_unरेजिस्टर_bus_member);
	ida_simple_हटाओ(&ipack_ida, bus->bus_nr);
	kमुक्त(bus);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipack_bus_unरेजिस्टर);

पूर्णांक ipack_driver_रेजिस्टर(काष्ठा ipack_driver *edrv, काष्ठा module *owner,
			  स्थिर अक्षर *name)
अणु
	अगर (!edrv->ops->probe)
		वापस -EINVAL;

	edrv->driver.owner = owner;
	edrv->driver.name = name;
	edrv->driver.bus = &ipack_bus_type;
	वापस driver_रेजिस्टर(&edrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_driver_रेजिस्टर);

व्योम ipack_driver_unरेजिस्टर(काष्ठा ipack_driver *edrv)
अणु
	driver_unरेजिस्टर(&edrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_driver_unरेजिस्टर);

अटल u16 ipack_crc_byte(u16 crc, u8 c)
अणु
	पूर्णांक i;

	crc ^= c << 8;
	क्रम (i = 0; i < 8; i++)
		crc = (crc << 1) ^ ((crc & 0x8000) ? 0x1021 : 0);
	वापस crc;
पूर्ण

/*
 * The algorithm in lib/crc-ccitt.c करोes not seem to apply since it uses the
 * opposite bit ordering.
 */
अटल u8 ipack_calc_crc1(काष्ठा ipack_device *dev)
अणु
	u8 c;
	u16 crc;
	अचिन्हित पूर्णांक i;

	crc = 0xffff;
	क्रम (i = 0; i < dev->id_avail; i++) अणु
		c = (i != 11) ? dev->id[i] : 0;
		crc = ipack_crc_byte(crc, c);
	पूर्ण
	crc = ~crc;
	वापस crc & 0xff;
पूर्ण

अटल u16 ipack_calc_crc2(काष्ठा ipack_device *dev)
अणु
	u8 c;
	u16 crc;
	अचिन्हित पूर्णांक i;

	crc = 0xffff;
	क्रम (i = 0; i < dev->id_avail; i++) अणु
		c = ((i != 0x18) && (i != 0x19)) ? dev->id[i] : 0;
		crc = ipack_crc_byte(crc, c);
	पूर्ण
	crc = ~crc;
	वापस crc;
पूर्ण

अटल व्योम ipack_parse_id1(काष्ठा ipack_device *dev)
अणु
	u8 *id = dev->id;
	u8 crc;

	dev->id_venकरोr = id[4];
	dev->id_device = id[5];
	dev->speed_8mhz = 1;
	dev->speed_32mhz = (id[7] == 'H');
	crc = ipack_calc_crc1(dev);
	dev->id_crc_correct = (crc == id[11]);
	अगर (!dev->id_crc_correct) अणु
		dev_warn(&dev->dev, "ID CRC invalid found 0x%x, expected 0x%x.\n",
				id[11], crc);
	पूर्ण
पूर्ण

अटल व्योम ipack_parse_id2(काष्ठा ipack_device *dev)
अणु
	__be16 *id = (__be16 *) dev->id;
	u16 flags, crc;

	dev->id_venकरोr = ((be16_to_cpu(id[3]) & 0xff) << 16)
			 + be16_to_cpu(id[4]);
	dev->id_device = be16_to_cpu(id[5]);
	flags = be16_to_cpu(id[10]);
	dev->speed_8mhz = !!(flags & 2);
	dev->speed_32mhz = !!(flags & 4);
	crc = ipack_calc_crc2(dev);
	dev->id_crc_correct = (crc == be16_to_cpu(id[12]));
	अगर (!dev->id_crc_correct) अणु
		dev_warn(&dev->dev, "ID CRC invalid found 0x%x, expected 0x%x.\n",
				id[11], crc);
	पूर्ण
पूर्ण

अटल पूर्णांक ipack_device_पढ़ो_id(काष्ठा ipack_device *dev)
अणु
	u8 __iomem *idmem;
	पूर्णांक i;
	पूर्णांक ret = 0;

	idmem = ioremap(dev->region[IPACK_ID_SPACE].start,
			dev->region[IPACK_ID_SPACE].size);
	अगर (!idmem) अणु
		dev_err(&dev->dev, "error mapping memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* Determine ID PROM Data Format.  If we find the ids "IPAC" or "IPAH"
	 * we are dealing with a IndustryPack  क्रमmat 1 device.  If we detect
	 * "VITA4 " (16 bit big endian क्रमmatted) we are dealing with a
	 * IndustryPack क्रमmat 2 device */
	अगर ((ioपढ़ो8(idmem + 1) == 'I') &&
			(ioपढ़ो8(idmem + 3) == 'P') &&
			(ioपढ़ो8(idmem + 5) == 'A') &&
			((ioपढ़ो8(idmem + 7) == 'C') ||
			 (ioपढ़ो8(idmem + 7) == 'H'))) अणु
		dev->id_क्रमmat = IPACK_ID_VERSION_1;
		dev->id_avail = ioपढ़ो8(idmem + 0x15);
		अगर ((dev->id_avail < 0x0c) || (dev->id_avail > 0x40)) अणु
			dev_warn(&dev->dev, "invalid id size");
			dev->id_avail = 0x0c;
		पूर्ण
	पूर्ण अन्यथा अगर ((ioपढ़ो8(idmem + 0) == 'I') &&
			(ioपढ़ो8(idmem + 1) == 'V') &&
			(ioपढ़ो8(idmem + 2) == 'A') &&
			(ioपढ़ो8(idmem + 3) == 'T') &&
			(ioपढ़ो8(idmem + 4) == ' ') &&
			(ioपढ़ो8(idmem + 5) == '4')) अणु
		dev->id_क्रमmat = IPACK_ID_VERSION_2;
		dev->id_avail = ioपढ़ो16be(idmem + 0x16);
		अगर ((dev->id_avail < 0x1a) || (dev->id_avail > 0x40)) अणु
			dev_warn(&dev->dev, "invalid id size");
			dev->id_avail = 0x1a;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->id_क्रमmat = IPACK_ID_VERSION_INVALID;
		dev->id_avail = 0;
	पूर्ण

	अगर (!dev->id_avail) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Obtain the amount of memory required to store a copy of the complete
	 * ID ROM contents */
	dev->id = kदो_स्मृति(dev->id_avail, GFP_KERNEL);
	अगर (!dev->id) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < dev->id_avail; i++) अणु
		अगर (dev->id_क्रमmat == IPACK_ID_VERSION_1)
			dev->id[i] = ioपढ़ो8(idmem + (i << 1) + 1);
		अन्यथा
			dev->id[i] = ioपढ़ो8(idmem + i);
	पूर्ण

	/* now we can finally work with the copy */
	चयन (dev->id_क्रमmat) अणु
	हाल IPACK_ID_VERSION_1:
		ipack_parse_id1(dev);
		अवरोध;
	हाल IPACK_ID_VERSION_2:
		ipack_parse_id2(dev);
		अवरोध;
	पूर्ण

out:
	iounmap(idmem);

	वापस ret;
पूर्ण

पूर्णांक ipack_device_init(काष्ठा ipack_device *dev)
अणु
	पूर्णांक ret;

	dev->dev.bus = &ipack_bus_type;
	dev->dev.release = ipack_device_release;
	dev->dev.parent = dev->bus->parent;
	dev_set_name(&dev->dev,
		     "ipack-dev.%u.%u", dev->bus->bus_nr, dev->slot);
	device_initialize(&dev->dev);

	अगर (dev->bus->ops->set_घड़ीrate(dev, 8))
		dev_warn(&dev->dev, "failed to switch to 8 MHz operation for reading of device ID.\n");
	अगर (dev->bus->ops->reset_समयout(dev))
		dev_warn(&dev->dev, "failed to reset potential timeout.");

	ret = ipack_device_पढ़ो_id(dev);
	अगर (ret < 0) अणु
		dev_err(&dev->dev, "error reading device id section.\n");
		वापस ret;
	पूर्ण

	/* अगर the device supports 32 MHz operation, use it. */
	अगर (dev->speed_32mhz) अणु
		ret = dev->bus->ops->set_घड़ीrate(dev, 32);
		अगर (ret < 0)
			dev_err(&dev->dev, "failed to switch to 32 MHz operation.\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipack_device_init);

पूर्णांक ipack_device_add(काष्ठा ipack_device *dev)
अणु
	वापस device_add(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_device_add);

व्योम ipack_device_del(काष्ठा ipack_device *dev)
अणु
	device_del(&dev->dev);
	ipack_put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_device_del);

व्योम ipack_get_device(काष्ठा ipack_device *dev)
अणु
	get_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_get_device);

व्योम ipack_put_device(काष्ठा ipack_device *dev)
अणु
	put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipack_put_device);

अटल पूर्णांक __init ipack_init(व्योम)
अणु
	ida_init(&ipack_ida);
	वापस bus_रेजिस्टर(&ipack_bus_type);
पूर्ण

अटल व्योम __निकास ipack_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&ipack_bus_type);
	ida_destroy(&ipack_ida);
पूर्ण

module_init(ipack_init);
module_निकास(ipack_निकास);

MODULE_AUTHOR("Samuel Iglesias Gonsalvez <siglesias@igalia.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Industry-pack bus core");
