<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006, 2007 Eugene Konev <ejka@खोलोwrt.org>
 *
 * Parts of the VLYNQ specअगरication can be found here:
 * http://www.ti.com/litv/pdf/sprue36a
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <linux/vlynq.h>

#घोषणा VLYNQ_CTRL_PM_ENABLE		0x80000000
#घोषणा VLYNQ_CTRL_CLOCK_INT		0x00008000
#घोषणा VLYNQ_CTRL_CLOCK_DIV(x)		(((x) & 7) << 16)
#घोषणा VLYNQ_CTRL_INT_LOCAL		0x00004000
#घोषणा VLYNQ_CTRL_INT_ENABLE		0x00002000
#घोषणा VLYNQ_CTRL_INT_VECTOR(x)	(((x) & 0x1f) << 8)
#घोषणा VLYNQ_CTRL_INT2CFG		0x00000080
#घोषणा VLYNQ_CTRL_RESET		0x00000001

#घोषणा VLYNQ_CTRL_CLOCK_MASK          (0x7 << 16)

#घोषणा VLYNQ_INT_OFFSET		0x00000014
#घोषणा VLYNQ_REMOTE_OFFSET		0x00000080

#घोषणा VLYNQ_STATUS_LINK		0x00000001
#घोषणा VLYNQ_STATUS_LERROR		0x00000080
#घोषणा VLYNQ_STATUS_RERROR		0x00000100

#घोषणा VINT_ENABLE			0x00000100
#घोषणा VINT_TYPE_EDGE			0x00000080
#घोषणा VINT_LEVEL_LOW			0x00000040
#घोषणा VINT_VECTOR(x)			((x) & 0x1f)
#घोषणा VINT_OFFSET(irq)		(8 * ((irq) % 4))

#घोषणा VLYNQ_AUTONEGO_V2		0x00010000

काष्ठा vlynq_regs अणु
	u32 revision;
	u32 control;
	u32 status;
	u32 पूर्णांक_prio;
	u32 पूर्णांक_status;
	u32 पूर्णांक_pending;
	u32 पूर्णांक_ptr;
	u32 tx_offset;
	काष्ठा vlynq_mapping rx_mapping[4];
	u32 chip;
	u32 स्वतःnego;
	u32 unused[6];
	u32 पूर्णांक_device[8];
पूर्ण;

#अगर_घोषित CONFIG_VLYNQ_DEBUG
अटल व्योम vlynq_dump_regs(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "VLYNQ local=%p remote=%p\n",
			dev->local, dev->remote);
	क्रम (i = 0; i < 32; i++) अणु
		prपूर्णांकk(KERN_DEBUG "VLYNQ: local %d: %08x\n",
			i + 1, ((u32 *)dev->local)[i]);
		prपूर्णांकk(KERN_DEBUG "VLYNQ: remote %d: %08x\n",
			i + 1, ((u32 *)dev->remote)[i]);
	पूर्ण
पूर्ण

अटल व्योम vlynq_dump_mem(u32 *base, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (count + 3) / 4; i++) अणु
		अगर (i % 4 == 0)
			prपूर्णांकk(KERN_DEBUG "\nMEM[0x%04x]:", i * 4);
		prपूर्णांकk(KERN_DEBUG " 0x%08x", *(base + i));
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "\n");
पूर्ण
#पूर्ण_अगर

/* Check the VLYNQ link status with a given device */
अटल पूर्णांक vlynq_linked(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 100; i++)
		अगर (पढ़ोl(&dev->local->status) & VLYNQ_STATUS_LINK)
			वापस 1;
		अन्यथा
			cpu_relax();

	वापस 0;
पूर्ण

अटल व्योम vlynq_reset(काष्ठा vlynq_device *dev)
अणु
	ग_लिखोl(पढ़ोl(&dev->local->control) | VLYNQ_CTRL_RESET,
			&dev->local->control);

	/* Wait क्रम the devices to finish resetting */
	msleep(5);

	/* Remove reset bit */
	ग_लिखोl(पढ़ोl(&dev->local->control) & ~VLYNQ_CTRL_RESET,
			&dev->local->control);

	/* Give some समय क्रम the devices to settle */
	msleep(5);
पूर्ण

अटल व्योम vlynq_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा vlynq_device *dev = irq_data_get_irq_chip_data(d);
	पूर्णांक virq;
	u32 val;

	BUG_ON(!dev);
	virq = d->irq - dev->irq_start;
	val = पढ़ोl(&dev->remote->पूर्णांक_device[virq >> 2]);
	val |= (VINT_ENABLE | virq) << VINT_OFFSET(virq);
	ग_लिखोl(val, &dev->remote->पूर्णांक_device[virq >> 2]);
पूर्ण

अटल व्योम vlynq_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा vlynq_device *dev = irq_data_get_irq_chip_data(d);
	पूर्णांक virq;
	u32 val;

	BUG_ON(!dev);
	virq = d->irq - dev->irq_start;
	val = पढ़ोl(&dev->remote->पूर्णांक_device[virq >> 2]);
	val &= ~(VINT_ENABLE << VINT_OFFSET(virq));
	ग_लिखोl(val, &dev->remote->पूर्णांक_device[virq >> 2]);
पूर्ण

अटल पूर्णांक vlynq_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा vlynq_device *dev = irq_data_get_irq_chip_data(d);
	पूर्णांक virq;
	u32 val;

	BUG_ON(!dev);
	virq = d->irq - dev->irq_start;
	val = पढ़ोl(&dev->remote->पूर्णांक_device[virq >> 2]);
	चयन (flow_type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		val |= VINT_TYPE_EDGE << VINT_OFFSET(virq);
		val &= ~(VINT_LEVEL_LOW << VINT_OFFSET(virq));
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		val &= ~(VINT_TYPE_EDGE << VINT_OFFSET(virq));
		val &= ~(VINT_LEVEL_LOW << VINT_OFFSET(virq));
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		val &= ~(VINT_TYPE_EDGE << VINT_OFFSET(virq));
		val |= VINT_LEVEL_LOW << VINT_OFFSET(virq);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(val, &dev->remote->पूर्णांक_device[virq >> 2]);
	वापस 0;
पूर्ण

अटल व्योम vlynq_local_ack(काष्ठा irq_data *d)
अणु
	काष्ठा vlynq_device *dev = irq_data_get_irq_chip_data(d);
	u32 status = पढ़ोl(&dev->local->status);

	pr_debug("%s: local status: 0x%08x\n",
		       dev_name(&dev->dev), status);
	ग_लिखोl(status, &dev->local->status);
पूर्ण

अटल व्योम vlynq_remote_ack(काष्ठा irq_data *d)
अणु
	काष्ठा vlynq_device *dev = irq_data_get_irq_chip_data(d);
	u32 status = पढ़ोl(&dev->remote->status);

	pr_debug("%s: remote status: 0x%08x\n",
		       dev_name(&dev->dev), status);
	ग_लिखोl(status, &dev->remote->status);
पूर्ण

अटल irqवापस_t vlynq_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vlynq_device *dev = dev_id;
	u32 status;
	पूर्णांक virq = 0;

	status = पढ़ोl(&dev->local->पूर्णांक_status);
	ग_लिखोl(status, &dev->local->पूर्णांक_status);

	अगर (unlikely(!status))
		spurious_पूर्णांकerrupt();

	जबतक (status) अणु
		अगर (status & 1)
			करो_IRQ(dev->irq_start + virq);
		status >>= 1;
		virq++;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा irq_chip vlynq_irq_chip = अणु
	.name = "vlynq",
	.irq_unmask = vlynq_irq_unmask,
	.irq_mask = vlynq_irq_mask,
	.irq_set_type = vlynq_irq_type,
पूर्ण;

अटल काष्ठा irq_chip vlynq_local_chip = अणु
	.name = "vlynq local error",
	.irq_unmask = vlynq_irq_unmask,
	.irq_mask = vlynq_irq_mask,
	.irq_ack = vlynq_local_ack,
पूर्ण;

अटल काष्ठा irq_chip vlynq_remote_chip = अणु
	.name = "vlynq local error",
	.irq_unmask = vlynq_irq_unmask,
	.irq_mask = vlynq_irq_mask,
	.irq_ack = vlynq_remote_ack,
पूर्ण;

अटल पूर्णांक vlynq_setup_irq(काष्ठा vlynq_device *dev)
अणु
	u32 val;
	पूर्णांक i, virq;

	अगर (dev->local_irq == dev->remote_irq) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: local vlynq irq should be different from remote\n",
		       dev_name(&dev->dev));
		वापस -EINVAL;
	पूर्ण

	/* Clear local and remote error bits */
	ग_लिखोl(पढ़ोl(&dev->local->status), &dev->local->status);
	ग_लिखोl(पढ़ोl(&dev->remote->status), &dev->remote->status);

	/* Now setup पूर्णांकerrupts */
	val = VLYNQ_CTRL_INT_VECTOR(dev->local_irq);
	val |= VLYNQ_CTRL_INT_ENABLE | VLYNQ_CTRL_INT_LOCAL |
		VLYNQ_CTRL_INT2CFG;
	val |= पढ़ोl(&dev->local->control);
	ग_लिखोl(VLYNQ_INT_OFFSET, &dev->local->पूर्णांक_ptr);
	ग_लिखोl(val, &dev->local->control);

	val = VLYNQ_CTRL_INT_VECTOR(dev->remote_irq);
	val |= VLYNQ_CTRL_INT_ENABLE;
	val |= पढ़ोl(&dev->remote->control);
	ग_लिखोl(VLYNQ_INT_OFFSET, &dev->remote->पूर्णांक_ptr);
	ग_लिखोl(val, &dev->remote->पूर्णांक_ptr);
	ग_लिखोl(val, &dev->remote->control);

	क्रम (i = dev->irq_start; i <= dev->irq_end; i++) अणु
		virq = i - dev->irq_start;
		अगर (virq == dev->local_irq) अणु
			irq_set_chip_and_handler(i, &vlynq_local_chip,
						 handle_level_irq);
			irq_set_chip_data(i, dev);
		पूर्ण अन्यथा अगर (virq == dev->remote_irq) अणु
			irq_set_chip_and_handler(i, &vlynq_remote_chip,
						 handle_level_irq);
			irq_set_chip_data(i, dev);
		पूर्ण अन्यथा अणु
			irq_set_chip_and_handler(i, &vlynq_irq_chip,
						 handle_simple_irq);
			irq_set_chip_data(i, dev);
			ग_लिखोl(0, &dev->remote->पूर्णांक_device[virq >> 2]);
		पूर्ण
	पूर्ण

	अगर (request_irq(dev->irq, vlynq_irq, IRQF_SHARED, "vlynq", dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: request_irq failed\n",
					dev_name(&dev->dev));
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vlynq_device_release(काष्ठा device *dev)
अणु
	काष्ठा vlynq_device *vdev = to_vlynq_device(dev);
	kमुक्त(vdev);
पूर्ण

अटल पूर्णांक vlynq_device_match(काष्ठा device *dev,
			      काष्ठा device_driver *drv)
अणु
	काष्ठा vlynq_device *vdev = to_vlynq_device(dev);
	काष्ठा vlynq_driver *vdrv = to_vlynq_driver(drv);
	काष्ठा vlynq_device_id *ids = vdrv->id_table;

	जबतक (ids->id) अणु
		अगर (ids->id == vdev->dev_id) अणु
			vdev->भागisor = ids->भागisor;
			vlynq_set_drvdata(vdev, ids);
			prपूर्णांकk(KERN_INFO "Driver found for VLYNQ "
				"device: %08x\n", vdev->dev_id);
			वापस 1;
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "Not using the %08x VLYNQ device's driver"
			" for VLYNQ device: %08x\n", ids->id, vdev->dev_id);
		ids++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vlynq_device_probe(काष्ठा device *dev)
अणु
	काष्ठा vlynq_device *vdev = to_vlynq_device(dev);
	काष्ठा vlynq_driver *drv = to_vlynq_driver(dev->driver);
	काष्ठा vlynq_device_id *id = vlynq_get_drvdata(vdev);
	पूर्णांक result = -ENODEV;

	अगर (drv->probe)
		result = drv->probe(vdev, id);
	अगर (result)
		put_device(dev);
	वापस result;
पूर्ण

अटल पूर्णांक vlynq_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा vlynq_driver *drv = to_vlynq_driver(dev->driver);

	अगर (drv->हटाओ)
		drv->हटाओ(to_vlynq_device(dev));

	वापस 0;
पूर्ण

पूर्णांक __vlynq_रेजिस्टर_driver(काष्ठा vlynq_driver *driver, काष्ठा module *owner)
अणु
	driver->driver.name = driver->name;
	driver->driver.bus = &vlynq_bus_type;
	वापस driver_रेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(__vlynq_रेजिस्टर_driver);

व्योम vlynq_unरेजिस्टर_driver(काष्ठा vlynq_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(vlynq_unरेजिस्टर_driver);

/*
 * A VLYNQ remote device can घड़ी the VLYNQ bus master
 * using a dedicated घड़ी line. In that हाल, both the
 * हटाओ device and the bus master should have the same
 * serial घड़ी भागiders configured. Iterate through the
 * 8 possible भागiders until we actually link with the
 * device.
 */
अटल पूर्णांक __vlynq_try_remote(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक i;

	vlynq_reset(dev);
	क्रम (i = dev->dev_id ? vlynq_rभाग2 : vlynq_rभाग8; dev->dev_id ?
			i <= vlynq_rभाग8 : i >= vlynq_rभाग2;
		dev->dev_id ? i++ : i--) अणु

		अगर (!vlynq_linked(dev))
			अवरोध;

		ग_लिखोl((पढ़ोl(&dev->remote->control) &
				~VLYNQ_CTRL_CLOCK_MASK) |
				VLYNQ_CTRL_CLOCK_INT |
				VLYNQ_CTRL_CLOCK_DIV(i - vlynq_rभाग1),
				&dev->remote->control);
		ग_लिखोl((पढ़ोl(&dev->local->control)
				& ~(VLYNQ_CTRL_CLOCK_INT |
				VLYNQ_CTRL_CLOCK_MASK)) |
				VLYNQ_CTRL_CLOCK_DIV(i - vlynq_rभाग1),
				&dev->local->control);

		अगर (vlynq_linked(dev)) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: using remote clock divisor %d\n",
				dev_name(&dev->dev), i - vlynq_rभाग1 + 1);
			dev->भागisor = i;
			वापस 0;
		पूर्ण अन्यथा अणु
			vlynq_reset(dev);
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * A VLYNQ remote device can be घड़ीed by the VLYNQ bus
 * master using a dedicated घड़ी line. In that हाल, only
 * the bus master configures the serial घड़ी भागider.
 * Iterate through the 8 possible भागiders until we
 * actually get a link with the device.
 */
अटल पूर्णांक __vlynq_try_local(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक i;

	vlynq_reset(dev);

	क्रम (i = dev->dev_id ? vlynq_द_भाग2 : vlynq_द_भाग8; dev->dev_id ?
			i <= vlynq_द_भाग8 : i >= vlynq_द_भाग2;
		dev->dev_id ? i++ : i--) अणु

		ग_लिखोl((पढ़ोl(&dev->local->control) &
				~VLYNQ_CTRL_CLOCK_MASK) |
				VLYNQ_CTRL_CLOCK_INT |
				VLYNQ_CTRL_CLOCK_DIV(i - vlynq_द_भाग1),
				&dev->local->control);

		अगर (vlynq_linked(dev)) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: using local clock divisor %d\n",
				dev_name(&dev->dev), i - vlynq_द_भाग1 + 1);
			dev->भागisor = i;
			वापस 0;
		पूर्ण अन्यथा अणु
			vlynq_reset(dev);
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * When using बाह्यal घड़ीing method, serial घड़ी
 * is supplied by an बाह्यal oscillator, thereक्रमe we
 * should mask the local घड़ी bit in the घड़ी control
 * रेजिस्टर क्रम both the bus master and the remote device.
 */
अटल पूर्णांक __vlynq_try_बाह्यal(काष्ठा vlynq_device *dev)
अणु
	vlynq_reset(dev);
	अगर (!vlynq_linked(dev))
		वापस -ENODEV;

	ग_लिखोl((पढ़ोl(&dev->remote->control) &
			~VLYNQ_CTRL_CLOCK_INT),
			&dev->remote->control);

	ग_लिखोl((पढ़ोl(&dev->local->control) &
			~VLYNQ_CTRL_CLOCK_INT),
			&dev->local->control);

	अगर (vlynq_linked(dev)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: using external clock\n",
			dev_name(&dev->dev));
			dev->भागisor = vlynq_भाग_बाह्यal;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __vlynq_enable_device(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक result;
	काष्ठा plat_vlynq_ops *ops = dev->dev.platक्रमm_data;

	result = ops->on(dev);
	अगर (result)
		वापस result;

	चयन (dev->भागisor) अणु
	हाल vlynq_भाग_बाह्यal:
	हाल vlynq_भाग_स्वतः:
		/* When the device is brought from reset it should have घड़ी
		 * generation negotiated by hardware.
		 * Check which device is generating घड़ीs and perक्रमm setup
		 * accordingly */
		अगर (vlynq_linked(dev) && पढ़ोl(&dev->remote->control) &
		   VLYNQ_CTRL_CLOCK_INT) अणु
			अगर (!__vlynq_try_remote(dev) ||
				!__vlynq_try_local(dev)  ||
				!__vlynq_try_बाह्यal(dev))
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!__vlynq_try_बाह्यal(dev) ||
				!__vlynq_try_local(dev)    ||
				!__vlynq_try_remote(dev))
				वापस 0;
		पूर्ण
		अवरोध;
	हाल vlynq_द_भाग1:
	हाल vlynq_द_भाग2:
	हाल vlynq_द_भाग3:
	हाल vlynq_द_भाग4:
	हाल vlynq_द_भाग5:
	हाल vlynq_द_भाग6:
	हाल vlynq_द_भाग7:
	हाल vlynq_द_भाग8:
		ग_लिखोl(VLYNQ_CTRL_CLOCK_INT |
			VLYNQ_CTRL_CLOCK_DIV(dev->भागisor -
			vlynq_द_भाग1), &dev->local->control);
		ग_लिखोl(0, &dev->remote->control);
		अगर (vlynq_linked(dev)) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: using local clock divisor %d\n",
				dev_name(&dev->dev),
				dev->भागisor - vlynq_द_भाग1 + 1);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल vlynq_rभाग1:
	हाल vlynq_rभाग2:
	हाल vlynq_rभाग3:
	हाल vlynq_rभाग4:
	हाल vlynq_rभाग5:
	हाल vlynq_rभाग6:
	हाल vlynq_rभाग7:
	हाल vlynq_rभाग8:
		ग_लिखोl(0, &dev->local->control);
		ग_लिखोl(VLYNQ_CTRL_CLOCK_INT |
			VLYNQ_CTRL_CLOCK_DIV(dev->भागisor -
			vlynq_rभाग1), &dev->remote->control);
		अगर (vlynq_linked(dev)) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: using remote clock divisor %d\n",
				dev_name(&dev->dev),
				dev->भागisor - vlynq_rभाग1 + 1);
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	ops->off(dev);
	वापस -ENODEV;
पूर्ण

पूर्णांक vlynq_enable_device(काष्ठा vlynq_device *dev)
अणु
	काष्ठा plat_vlynq_ops *ops = dev->dev.platक्रमm_data;
	पूर्णांक result = -ENODEV;

	result = __vlynq_enable_device(dev);
	अगर (result)
		वापस result;

	result = vlynq_setup_irq(dev);
	अगर (result)
		ops->off(dev);

	dev->enabled = !result;
	वापस result;
पूर्ण
EXPORT_SYMBOL(vlynq_enable_device);


व्योम vlynq_disable_device(काष्ठा vlynq_device *dev)
अणु
	काष्ठा plat_vlynq_ops *ops = dev->dev.platक्रमm_data;

	dev->enabled = 0;
	मुक्त_irq(dev->irq, dev);
	ops->off(dev);
पूर्ण
EXPORT_SYMBOL(vlynq_disable_device);

पूर्णांक vlynq_set_local_mapping(काष्ठा vlynq_device *dev, u32 tx_offset,
			    काष्ठा vlynq_mapping *mapping)
अणु
	पूर्णांक i;

	अगर (!dev->enabled)
		वापस -ENXIO;

	ग_लिखोl(tx_offset, &dev->local->tx_offset);
	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(mapping[i].offset, &dev->local->rx_mapping[i].offset);
		ग_लिखोl(mapping[i].size, &dev->local->rx_mapping[i].size);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vlynq_set_local_mapping);

पूर्णांक vlynq_set_remote_mapping(काष्ठा vlynq_device *dev, u32 tx_offset,
			     काष्ठा vlynq_mapping *mapping)
अणु
	पूर्णांक i;

	अगर (!dev->enabled)
		वापस -ENXIO;

	ग_लिखोl(tx_offset, &dev->remote->tx_offset);
	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(mapping[i].offset, &dev->remote->rx_mapping[i].offset);
		ग_लिखोl(mapping[i].size, &dev->remote->rx_mapping[i].size);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vlynq_set_remote_mapping);

पूर्णांक vlynq_set_local_irq(काष्ठा vlynq_device *dev, पूर्णांक virq)
अणु
	पूर्णांक irq = dev->irq_start + virq;
	अगर (dev->enabled)
		वापस -EBUSY;

	अगर ((irq < dev->irq_start) || (irq > dev->irq_end))
		वापस -EINVAL;

	अगर (virq == dev->remote_irq)
		वापस -EINVAL;

	dev->local_irq = virq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vlynq_set_local_irq);

पूर्णांक vlynq_set_remote_irq(काष्ठा vlynq_device *dev, पूर्णांक virq)
अणु
	पूर्णांक irq = dev->irq_start + virq;
	अगर (dev->enabled)
		वापस -EBUSY;

	अगर ((irq < dev->irq_start) || (irq > dev->irq_end))
		वापस -EINVAL;

	अगर (virq == dev->local_irq)
		वापस -EINVAL;

	dev->remote_irq = virq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vlynq_set_remote_irq);

अटल पूर्णांक vlynq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vlynq_device *dev;
	काष्ठा resource *regs_res, *mem_res, *irq_res;
	पूर्णांक len, result;

	regs_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	अगर (!regs_res)
		वापस -ENODEV;

	mem_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mem");
	अगर (!mem_res)
		वापस -ENODEV;

	irq_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "devirq");
	अगर (!irq_res)
		वापस -ENODEV;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR
		       "vlynq: failed to allocate device structure\n");
		वापस -ENOMEM;
	पूर्ण

	dev->id = pdev->id;
	dev->dev.bus = &vlynq_bus_type;
	dev->dev.parent = &pdev->dev;
	dev_set_name(&dev->dev, "vlynq%d", dev->id);
	dev->dev.platक्रमm_data = pdev->dev.platक्रमm_data;
	dev->dev.release = vlynq_device_release;

	dev->regs_start = regs_res->start;
	dev->regs_end = regs_res->end;
	dev->mem_start = mem_res->start;
	dev->mem_end = mem_res->end;

	len = resource_size(regs_res);
	अगर (!request_mem_region(regs_res->start, len, dev_name(&dev->dev))) अणु
		prपूर्णांकk(KERN_ERR "%s: Can't request vlynq registers\n",
		       dev_name(&dev->dev));
		result = -ENXIO;
		जाओ fail_request;
	पूर्ण

	dev->local = ioremap(regs_res->start, len);
	अगर (!dev->local) अणु
		prपूर्णांकk(KERN_ERR "%s: Can't remap vlynq registers\n",
		       dev_name(&dev->dev));
		result = -ENXIO;
		जाओ fail_remap;
	पूर्ण

	dev->remote = (काष्ठा vlynq_regs *)((व्योम *)dev->local +
					    VLYNQ_REMOTE_OFFSET);

	dev->irq = platक्रमm_get_irq_byname(pdev, "irq");
	dev->irq_start = irq_res->start;
	dev->irq_end = irq_res->end;
	dev->local_irq = dev->irq_end - dev->irq_start;
	dev->remote_irq = dev->local_irq - 1;

	अगर (device_रेजिस्टर(&dev->dev))
		जाओ fail_रेजिस्टर;
	platक्रमm_set_drvdata(pdev, dev);

	prपूर्णांकk(KERN_INFO "%s: regs 0x%p, irq %d, mem 0x%p\n",
	       dev_name(&dev->dev), (व्योम *)dev->regs_start, dev->irq,
	       (व्योम *)dev->mem_start);

	dev->dev_id = 0;
	dev->भागisor = vlynq_भाग_स्वतः;
	result = __vlynq_enable_device(dev);
	अगर (result == 0) अणु
		dev->dev_id = पढ़ोl(&dev->remote->chip);
		((काष्ठा plat_vlynq_ops *)(dev->dev.platक्रमm_data))->off(dev);
	पूर्ण
	अगर (dev->dev_id)
		prपूर्णांकk(KERN_INFO "Found a VLYNQ device: %08x\n", dev->dev_id);

	वापस 0;

fail_रेजिस्टर:
	iounmap(dev->local);
fail_remap:
fail_request:
	release_mem_region(regs_res->start, len);
	kमुक्त(dev);
	वापस result;
पूर्ण

अटल पूर्णांक vlynq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vlynq_device *dev = platक्रमm_get_drvdata(pdev);

	device_unरेजिस्टर(&dev->dev);
	iounmap(dev->local);
	release_mem_region(dev->regs_start,
			   dev->regs_end - dev->regs_start + 1);

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vlynq_platक्रमm_driver = अणु
	.driver.name = "vlynq",
	.probe = vlynq_probe,
	.हटाओ = vlynq_हटाओ,
पूर्ण;

काष्ठा bus_type vlynq_bus_type = अणु
	.name = "vlynq",
	.match = vlynq_device_match,
	.probe = vlynq_device_probe,
	.हटाओ = vlynq_device_हटाओ,
पूर्ण;
EXPORT_SYMBOL(vlynq_bus_type);

अटल पूर्णांक vlynq_init(व्योम)
अणु
	पूर्णांक res = 0;

	res = bus_रेजिस्टर(&vlynq_bus_type);
	अगर (res)
		जाओ fail_bus;

	res = platक्रमm_driver_रेजिस्टर(&vlynq_platक्रमm_driver);
	अगर (res)
		जाओ fail_platक्रमm;

	वापस 0;

fail_platक्रमm:
	bus_unरेजिस्टर(&vlynq_bus_type);
fail_bus:
	वापस res;
पूर्ण

अटल व्योम vlynq_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vlynq_platक्रमm_driver);
	bus_unरेजिस्टर(&vlynq_bus_type);
पूर्ण

module_init(vlynq_init);
module_निकास(vlynq_निकास);
