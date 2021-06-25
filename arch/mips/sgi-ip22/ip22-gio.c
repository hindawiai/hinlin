<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/paccess.h>
#समावेश <यंत्र/gio_device.h>
#समावेश <यंत्र/sgi/gपन.स>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/ip22.h>

अटल काष्ठा bus_type gio_bus_type;

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	__u8	   id;
पूर्ण gio_name_table[] = अणु
	अणु .name = "SGI Impact", .id = 0x10 पूर्ण,
	अणु .name = "Phobos G160", .id = 0x35 पूर्ण,
	अणु .name = "Phobos G130", .id = 0x36 पूर्ण,
	अणु .name = "Phobos G100", .id = 0x37 पूर्ण,
	अणु .name = "Set Engineering GFE", .id = 0x38 पूर्ण,
	/* fake IDs */
	अणु .name = "SGI Newport", .id = 0x7e पूर्ण,
	अणु .name = "SGI GR2/GR3", .id = 0x7f पूर्ण,
पूर्ण;

अटल व्योम gio_bus_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा device gio_bus = अणु
	.init_name = "gio",
	.release = &gio_bus_release,
पूर्ण;

/**
 * gio_match_device - Tell अगर an of_device काष्ठाure has a matching
 * gio_match काष्ठाure
 * @ids: array of of device match काष्ठाures to search in
 * @dev: the of device काष्ठाure to match against
 *
 * Used by a driver to check whether an of_device present in the
 * प्रणाली is in its list of supported devices.
 */
अटल स्थिर काष्ठा gio_device_id *
gio_match_device(स्थिर काष्ठा gio_device_id *match,
		 स्थिर काष्ठा gio_device *dev)
अणु
	स्थिर काष्ठा gio_device_id *ids;

	क्रम (ids = match; ids->id != 0xff; ids++)
		अगर (ids->id == dev->id.id)
			वापस ids;

	वापस शून्य;
पूर्ण

काष्ठा gio_device *gio_dev_get(काष्ठा gio_device *dev)
अणु
	काष्ठा device *पंचांगp;

	अगर (!dev)
		वापस शून्य;
	पंचांगp = get_device(&dev->dev);
	अगर (पंचांगp)
		वापस to_gio_device(पंचांगp);
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(gio_dev_get);

व्योम gio_dev_put(काष्ठा gio_device *dev)
अणु
	अगर (dev)
		put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gio_dev_put);

/**
 * gio_release_dev - मुक्त an gio device काष्ठाure when all users of it are finished.
 * @dev: device that's been disconnected
 *
 * Will be called only by the device core when all users of this gio device are
 * करोne.
 */
व्योम gio_release_dev(काष्ठा device *dev)
अणु
	काष्ठा gio_device *giodev;

	giodev = to_gio_device(dev);
	kमुक्त(giodev);
पूर्ण
EXPORT_SYMBOL_GPL(gio_release_dev);

पूर्णांक gio_device_रेजिस्टर(काष्ठा gio_device *giodev)
अणु
	giodev->dev.bus = &gio_bus_type;
	giodev->dev.parent = &gio_bus;
	वापस device_रेजिस्टर(&giodev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gio_device_रेजिस्टर);

व्योम gio_device_unरेजिस्टर(काष्ठा gio_device *giodev)
अणु
	device_unरेजिस्टर(&giodev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gio_device_unरेजिस्टर);

अटल पूर्णांक gio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा gio_device *gio_dev = to_gio_device(dev);
	काष्ठा gio_driver *gio_drv = to_gio_driver(drv);

	वापस gio_match_device(gio_drv->id_table, gio_dev) != शून्य;
पूर्ण

अटल पूर्णांक gio_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = -ENODEV;
	काष्ठा gio_driver *drv;
	काष्ठा gio_device *gio_dev;
	स्थिर काष्ठा gio_device_id *match;

	drv = to_gio_driver(dev->driver);
	gio_dev = to_gio_device(dev);

	अगर (!drv->probe)
		वापस error;

	gio_dev_get(gio_dev);

	match = gio_match_device(drv->id_table, gio_dev);
	अगर (match)
		error = drv->probe(gio_dev, match);
	अगर (error)
		gio_dev_put(gio_dev);

	वापस error;
पूर्ण

अटल पूर्णांक gio_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा gio_device *gio_dev = to_gio_device(dev);
	काष्ठा gio_driver *drv = to_gio_driver(dev->driver);

	अगर (dev->driver && drv->हटाओ)
		drv->हटाओ(gio_dev);
	वापस 0;
पूर्ण

अटल व्योम gio_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा gio_device *gio_dev = to_gio_device(dev);
	काष्ठा gio_driver *drv = to_gio_driver(dev->driver);

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(gio_dev);
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			     अक्षर *buf)
अणु
	काष्ठा gio_device *gio_dev = to_gio_device(dev);
	पूर्णांक len = snम_लिखो(buf, PAGE_SIZE, "gio:%x\n", gio_dev->id.id);

	वापस (len >= PAGE_SIZE) ? (PAGE_SIZE - 1) : len;
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gio_device *giodev;

	giodev = to_gio_device(dev);
	वापस प्र_लिखो(buf, "%s", giodev->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gio_device *giodev;

	giodev = to_gio_device(dev);
	वापस प्र_लिखो(buf, "%x", giodev->id.id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल काष्ठा attribute *gio_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_name.attr,
	&dev_attr_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gio_dev);

अटल पूर्णांक gio_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा gio_device *gio_dev = to_gio_device(dev);

	add_uevent_var(env, "MODALIAS=gio:%x", gio_dev->id.id);
	वापस 0;
पूर्ण

पूर्णांक gio_रेजिस्टर_driver(काष्ठा gio_driver *drv)
अणु
	/* initialize common driver fields */
	अगर (!drv->driver.name)
		drv->driver.name = drv->name;
	अगर (!drv->driver.owner)
		drv->driver.owner = drv->owner;
	drv->driver.bus = &gio_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(gio_रेजिस्टर_driver);

व्योम gio_unरेजिस्टर_driver(काष्ठा gio_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(gio_unरेजिस्टर_driver);

व्योम gio_set_master(काष्ठा gio_device *dev)
अणु
	u32 पंचांगp = sgimc->giopar;

	चयन (dev->slotno) अणु
	हाल 0:
		पंचांगp |= SGIMC_GIOPAR_MASTERGFX;
		अवरोध;
	हाल 1:
		पंचांगp |= SGIMC_GIOPAR_MASTEREXP0;
		अवरोध;
	हाल 2:
		पंचांगp |= SGIMC_GIOPAR_MASTEREXP1;
		अवरोध;
	पूर्ण
	sgimc->giopar = पंचांगp;
पूर्ण
EXPORT_SYMBOL_GPL(gio_set_master);

व्योम ip22_gio_set_64bit(पूर्णांक slotno)
अणु
	u32 पंचांगp = sgimc->giopar;

	चयन (slotno) अणु
	हाल 0:
		पंचांगp |= SGIMC_GIOPAR_GFX64;
		अवरोध;
	हाल 1:
		पंचांगp |= SGIMC_GIOPAR_EXP064;
		अवरोध;
	हाल 2:
		पंचांगp |= SGIMC_GIOPAR_EXP164;
		अवरोध;
	पूर्ण
	sgimc->giopar = पंचांगp;
पूर्ण

अटल पूर्णांक ip22_gio_id(अचिन्हित दीर्घ addr, u32 *res)
अणु
	u8 पंचांगp8;
	u8 पंचांगp16;
	u32 पंचांगp32;
	u8 *ptr8;
	u16 *ptr16;
	u32 *ptr32;

	ptr32 = (व्योम *)CKSEG1ADDR(addr);
	अगर (!get_dbe(पंचांगp32, ptr32)) अणु
		/*
		 * We got no DBE, but this करोesn't mean anything.
		 * If GIO is pipelined (which can't be disabled
		 * क्रम GFX slot) we करोn't get a DBE, but we see
		 * the transfer size as data. So we करो an 8bit
		 * and a 16bit access and check whether the common
		 * data matches
		 */
		ptr8 = (व्योम *)CKSEG1ADDR(addr + 3);
		अगर (get_dbe(पंचांगp8, ptr8)) अणु
			/*
			 * 32bit access worked, but 8bit करोesn't
			 * so we करोn't see phantom पढ़ोs on
			 * a pipelined bus, but a real card which
			 * करोesn't support 8 bit पढ़ोs
			 */
			*res = पंचांगp32;
			वापस 1;
		पूर्ण
		ptr16 = (व्योम *)CKSEG1ADDR(addr + 2);
		get_dbe(पंचांगp16, ptr16);
		अगर (पंचांगp8 == (पंचांगp16 & 0xff) &&
		    पंचांगp8 == (पंचांगp32 & 0xff) &&
		    पंचांगp16 == (पंचांगp32 & 0xffff)) अणु
			*res = पंचांगp32;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0; /* nothing here */
पूर्ण

#घोषणा HQ2_MYSTERY_OFFS       0x6A07C
#घोषणा NEWPORT_USTATUS_OFFS   0xF133C

अटल पूर्णांक ip22_is_gr2(अचिन्हित दीर्घ addr)
अणु
	u32 पंचांगp;
	u32 *ptr;

	/* HQ2 only allows 32bit accesses */
	ptr = (व्योम *)CKSEG1ADDR(addr + HQ2_MYSTERY_OFFS);
	अगर (!get_dbe(पंचांगp, ptr)) अणु
		अगर (पंचांगp == 0xdeadbeef)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम ip22_check_gio(पूर्णांक slotno, अचिन्हित दीर्घ addr, पूर्णांक irq)
अणु
	स्थिर अक्षर *name = "Unknown";
	काष्ठा gio_device *gio_dev;
	u32 पंचांगp;
	__u8 id;
	पूर्णांक i;

	/* first look क्रम GR2/GR3 by checking mystery रेजिस्टर */
	अगर (ip22_is_gr2(addr))
		पंचांगp = 0x7f;
	अन्यथा अणु
		अगर (!ip22_gio_id(addr, &पंचांगp)) अणु
			/*
			 * no GIO signature at start address of slot
			 * since Newport करोesn't have one, we check अगर
			 * user status रेजिस्टर is पढ़ोable
			 */
			अगर (ip22_gio_id(addr + NEWPORT_USTATUS_OFFS, &पंचांगp))
				पंचांगp = 0x7e;
			अन्यथा
				पंचांगp = 0;
		पूर्ण
	पूर्ण
	अगर (पंचांगp) अणु
		id = GIO_ID(पंचांगp);
		अगर (पंचांगp & GIO_32BIT_ID) अणु
			अगर (पंचांगp & GIO_64BIT_IFACE)
				ip22_gio_set_64bit(slotno);
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(gio_name_table); i++) अणु
			अगर (id == gio_name_table[i].id) अणु
				name = gio_name_table[i].name;
				अवरोध;
			पूर्ण
		पूर्ण
		prपूर्णांकk(KERN_INFO "GIO: slot %d : %s (id %x)\n",
		       slotno, name, id);
		gio_dev = kzalloc(माप *gio_dev, GFP_KERNEL);
		gio_dev->name = name;
		gio_dev->slotno = slotno;
		gio_dev->id.id = id;
		gio_dev->resource.start = addr;
		gio_dev->resource.end = addr + 0x3fffff;
		gio_dev->resource.flags = IORESOURCE_MEM;
		gio_dev->irq = irq;
		dev_set_name(&gio_dev->dev, "%d", slotno);
		gio_device_रेजिस्टर(gio_dev);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "GIO: slot %d : Empty\n", slotno);
पूर्ण

अटल काष्ठा bus_type gio_bus_type = अणु
	.name	   = "gio",
	.dev_groups = gio_dev_groups,
	.match	   = gio_bus_match,
	.probe	   = gio_device_probe,
	.हटाओ	   = gio_device_हटाओ,
	.shutकरोwn  = gio_device_shutकरोwn,
	.uevent	   = gio_device_uevent,
पूर्ण;

अटल काष्ठा resource gio_bus_resource = अणु
	.start = GIO_SLOT_GFX_BASE,
	.end   = GIO_SLOT_GFX_BASE + 0x9fffff,
	.name  = "GIO Bus",
	.flags = IORESOURCE_MEM,
पूर्ण;

पूर्णांक __init ip22_gio_init(व्योम)
अणु
	अचिन्हित पूर्णांक pbdma __maybe_unused;
	पूर्णांक ret;

	ret = device_रेजिस्टर(&gio_bus);
	अगर (ret) अणु
		put_device(&gio_bus);
		वापस ret;
	पूर्ण

	ret = bus_रेजिस्टर(&gio_bus_type);
	अगर (!ret) अणु
		request_resource(&iomem_resource, &gio_bus_resource);
		prपूर्णांकk(KERN_INFO "GIO: Probing bus...\n");

		अगर (ip22_is_fullhouse()) अणु
			/* Indigo2 */
			ip22_check_gio(0, GIO_SLOT_GFX_BASE, SGI_GIO_1_IRQ);
			ip22_check_gio(1, GIO_SLOT_EXP0_BASE, SGI_GIO_1_IRQ);
		पूर्ण अन्यथा अणु
			/* Indy/Challenge S */
			अगर (get_dbe(pbdma, (अचिन्हित पूर्णांक *)&hpc3c1->pbdma[1]))
				ip22_check_gio(0, GIO_SLOT_GFX_BASE,
					       SGI_GIO_0_IRQ);
			ip22_check_gio(1, GIO_SLOT_EXP0_BASE, SGI_GIOEXP0_IRQ);
			ip22_check_gio(2, GIO_SLOT_EXP1_BASE, SGI_GIOEXP1_IRQ);
		पूर्ण
	पूर्ण अन्यथा
		device_unरेजिस्टर(&gio_bus);

	वापस ret;
पूर्ण

subsys_initcall(ip22_gio_init);
