<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv-gpio.c  --  gpio sub drivers

    sysfs-based sub driver पूर्णांकerface क्रम bttv
    मुख्यly पूर्णांकended क्रम gpio access


    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
			   & Marcus Metzler (mocm@thp.uni-koeln.de)
    (c) 1999-2003 Gerd Knorr <kraxel@bytesex.org>


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश "bttvp.h"

/* ----------------------------------------------------------------------- */
/* पूर्णांकernal: the bttv "bus"                                                */

अटल पूर्णांक bttv_sub_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा bttv_sub_driver *sub = to_bttv_sub_drv(drv);
	पूर्णांक len = म_माप(sub->wanted);

	अगर (0 == म_भेदन(dev_name(dev), sub->wanted, len))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_sub_probe(काष्ठा device *dev)
अणु
	काष्ठा bttv_sub_device *sdev = to_bttv_sub_dev(dev);
	काष्ठा bttv_sub_driver *sub = to_bttv_sub_drv(dev->driver);

	वापस sub->probe ? sub->probe(sdev) : -ENODEV;
पूर्ण

अटल पूर्णांक bttv_sub_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा bttv_sub_device *sdev = to_bttv_sub_dev(dev);
	काष्ठा bttv_sub_driver *sub = to_bttv_sub_drv(dev->driver);

	अगर (sub->हटाओ)
		sub->हटाओ(sdev);
	वापस 0;
पूर्ण

काष्ठा bus_type bttv_sub_bus_type = अणु
	.name   = "bttv-sub",
	.match  = &bttv_sub_bus_match,
	.probe  = bttv_sub_probe,
	.हटाओ = bttv_sub_हटाओ,
पूर्ण;

अटल व्योम release_sub_device(काष्ठा device *dev)
अणु
	काष्ठा bttv_sub_device *sub = to_bttv_sub_dev(dev);
	kमुक्त(sub);
पूर्ण

पूर्णांक bttv_sub_add_device(काष्ठा bttv_core *core, अक्षर *name)
अणु
	काष्ठा bttv_sub_device *sub;
	पूर्णांक err;

	sub = kzalloc(माप(*sub),GFP_KERNEL);
	अगर (शून्य == sub)
		वापस -ENOMEM;

	sub->core        = core;
	sub->dev.parent  = &core->pci->dev;
	sub->dev.bus     = &bttv_sub_bus_type;
	sub->dev.release = release_sub_device;
	dev_set_name(&sub->dev, "%s%d", name, core->nr);

	err = device_रेजिस्टर(&sub->dev);
	अगर (0 != err) अणु
		put_device(&sub->dev);
		वापस err;
	पूर्ण
	pr_info("%d: add subdevice \"%s\"\n", core->nr, dev_name(&sub->dev));
	list_add_tail(&sub->list,&core->subs);
	वापस 0;
पूर्ण

पूर्णांक bttv_sub_del_devices(काष्ठा bttv_core *core)
अणु
	काष्ठा bttv_sub_device *sub, *save;

	list_क्रम_each_entry_safe(sub, save, &core->subs, list) अणु
		list_del(&sub->list);
		device_unरेजिस्टर(&sub->dev);
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */
/* बाह्यal: sub-driver रेजिस्टर/unरेजिस्टर                                */

पूर्णांक bttv_sub_रेजिस्टर(काष्ठा bttv_sub_driver *sub, अक्षर *wanted)
अणु
	sub->drv.bus = &bttv_sub_bus_type;
	snम_लिखो(sub->wanted,माप(sub->wanted),"%s",wanted);
	वापस driver_रेजिस्टर(&sub->drv);
पूर्ण
EXPORT_SYMBOL(bttv_sub_रेजिस्टर);

पूर्णांक bttv_sub_unरेजिस्टर(काष्ठा bttv_sub_driver *sub)
अणु
	driver_unरेजिस्टर(&sub->drv);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bttv_sub_unरेजिस्टर);

/* ----------------------------------------------------------------------- */
/* बाह्यal: gpio access functions                                         */

व्योम bttv_gpio_inout(काष्ठा bttv_core *core, u32 mask, u32 outbits)
अणु
	काष्ठा bttv *btv = container_of(core, काष्ठा bttv, c);
	अचिन्हित दीर्घ flags;
	u32 data;

	spin_lock_irqsave(&btv->gpio_lock,flags);
	data = btपढ़ो(BT848_GPIO_OUT_EN);
	data = data & ~mask;
	data = data | (mask & outbits);
	btग_लिखो(data,BT848_GPIO_OUT_EN);
	spin_unlock_irqrestore(&btv->gpio_lock,flags);
पूर्ण

u32 bttv_gpio_पढ़ो(काष्ठा bttv_core *core)
अणु
	काष्ठा bttv *btv = container_of(core, काष्ठा bttv, c);
	u32 value;

	value = btपढ़ो(BT848_GPIO_DATA);
	वापस value;
पूर्ण

व्योम bttv_gpio_ग_लिखो(काष्ठा bttv_core *core, u32 value)
अणु
	काष्ठा bttv *btv = container_of(core, काष्ठा bttv, c);

	btग_लिखो(value,BT848_GPIO_DATA);
पूर्ण

व्योम bttv_gpio_bits(काष्ठा bttv_core *core, u32 mask, u32 bits)
अणु
	काष्ठा bttv *btv = container_of(core, काष्ठा bttv, c);
	अचिन्हित दीर्घ flags;
	u32 data;

	spin_lock_irqsave(&btv->gpio_lock,flags);
	data = btपढ़ो(BT848_GPIO_DATA);
	data = data & ~mask;
	data = data | (mask & bits);
	btग_लिखो(data,BT848_GPIO_DATA);
	spin_unlock_irqrestore(&btv->gpio_lock,flags);
पूर्ण
