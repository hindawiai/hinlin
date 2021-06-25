<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple Motion Sensor driver
 *
 * Copyright (C) 2005 Stelian Pop (stelian@popies.net)
 * Copyright (C) 2006 Michael Hanselmann (linux-kernel@hansmi.ch)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/pmac_pfunc.h>

#समावेश "ams.h"

/* There is only one motion sensor per machine */
काष्ठा ams ams_info;

अटल bool verbose;
module_param(verbose, bool, 0644);
MODULE_PARM_DESC(verbose, "Show free falls and shocks in kernel output");

/* Call with ams_info.lock held! */
व्योम ams_sensors(s8 *x, s8 *y, s8 *z)
अणु
	u32 orient = ams_info.vflag? ams_info.orient1 : ams_info.orient2;

	अगर (orient & 0x80)
		/* X and Y swapped */
		ams_info.get_xyz(y, x, z);
	अन्यथा
		ams_info.get_xyz(x, y, z);

	अगर (orient & 0x04)
		*z = ~(*z);
	अगर (orient & 0x02)
		*y = ~(*y);
	अगर (orient & 0x01)
		*x = ~(*x);
पूर्ण

अटल sमाप_प्रकार ams_show_current(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	s8 x, y, z;

	mutex_lock(&ams_info.lock);
	ams_sensors(&x, &y, &z);
	mutex_unlock(&ams_info.lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d %d %d\n", x, y, z);
पूर्ण

अटल DEVICE_ATTR(current, S_IRUGO, ams_show_current, शून्य);

अटल व्योम ams_handle_irq(व्योम *data)
अणु
	क्रमागत ams_irq irq = *((क्रमागत ams_irq *)data);

	spin_lock(&ams_info.irq_lock);

	ams_info.worker_irqs |= irq;
	schedule_work(&ams_info.worker);

	spin_unlock(&ams_info.irq_lock);
पूर्ण

अटल क्रमागत ams_irq ams_मुक्तfall_irq_data = AMS_IRQ_FREEFALL;
अटल काष्ठा pmf_irq_client ams_मुक्तfall_client = अणु
	.owner = THIS_MODULE,
	.handler = ams_handle_irq,
	.data = &ams_मुक्तfall_irq_data,
पूर्ण;

अटल क्रमागत ams_irq ams_shock_irq_data = AMS_IRQ_SHOCK;
अटल काष्ठा pmf_irq_client ams_shock_client = अणु
	.owner = THIS_MODULE,
	.handler = ams_handle_irq,
	.data = &ams_shock_irq_data,
पूर्ण;

/* Once hard disk parking is implemented in the kernel, this function can
 * trigger it.
 */
अटल व्योम ams_worker(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	u8 irqs_to_clear;

	mutex_lock(&ams_info.lock);

	spin_lock_irqsave(&ams_info.irq_lock, flags);
	irqs_to_clear = ams_info.worker_irqs;

	अगर (ams_info.worker_irqs & AMS_IRQ_FREEFALL) अणु
		अगर (verbose)
			prपूर्णांकk(KERN_INFO "ams: freefall detected!\n");

		ams_info.worker_irqs &= ~AMS_IRQ_FREEFALL;
	पूर्ण

	अगर (ams_info.worker_irqs & AMS_IRQ_SHOCK) अणु
		अगर (verbose)
			prपूर्णांकk(KERN_INFO "ams: shock detected!\n");

		ams_info.worker_irqs &= ~AMS_IRQ_SHOCK;
	पूर्ण

	spin_unlock_irqrestore(&ams_info.irq_lock, flags);

	ams_info.clear_irq(irqs_to_clear);

	mutex_unlock(&ams_info.lock);
पूर्ण

/* Call with ams_info.lock held! */
पूर्णांक ams_sensor_attach(व्योम)
अणु
	पूर्णांक result;
	स्थिर u32 *prop;

	/* Get orientation */
	prop = of_get_property(ams_info.of_node, "orientation", शून्य);
	अगर (!prop)
		वापस -ENODEV;
	ams_info.orient1 = *prop;
	ams_info.orient2 = *(prop + 1);

	/* Register मुक्तfall पूर्णांकerrupt handler */
	result = pmf_रेजिस्टर_irq_client(ams_info.of_node,
			"accel-int-1",
			&ams_मुक्तfall_client);
	अगर (result < 0)
		वापस -ENODEV;

	/* Reset saved irqs */
	ams_info.worker_irqs = 0;

	/* Register shock पूर्णांकerrupt handler */
	result = pmf_रेजिस्टर_irq_client(ams_info.of_node,
			"accel-int-2",
			&ams_shock_client);
	अगर (result < 0)
		जाओ release_मुक्तfall;

	/* Create device */
	ams_info.of_dev = of_platक्रमm_device_create(ams_info.of_node, "ams", शून्य);
	अगर (!ams_info.of_dev) अणु
		result = -ENODEV;
		जाओ release_shock;
	पूर्ण

	/* Create attributes */
	result = device_create_file(&ams_info.of_dev->dev, &dev_attr_current);
	अगर (result)
		जाओ release_of;

	ams_info.vflag = !!(ams_info.get_venकरोr() & 0x10);

	/* Init input device */
	result = ams_input_init();
	अगर (result)
		जाओ release_device_file;

	वापस result;
release_device_file:
	device_हटाओ_file(&ams_info.of_dev->dev, &dev_attr_current);
release_of:
	of_device_unरेजिस्टर(ams_info.of_dev);
release_shock:
	pmf_unरेजिस्टर_irq_client(&ams_shock_client);
release_मुक्तfall:
	pmf_unरेजिस्टर_irq_client(&ams_मुक्तfall_client);
	वापस result;
पूर्ण

पूर्णांक __init ams_init(व्योम)
अणु
	काष्ठा device_node *np;

	spin_lock_init(&ams_info.irq_lock);
	mutex_init(&ams_info.lock);
	INIT_WORK(&ams_info.worker, ams_worker);

#अगर_घोषित CONFIG_SENSORS_AMS_I2C
	np = of_find_node_by_name(शून्य, "accelerometer");
	अगर (np && of_device_is_compatible(np, "AAPL,accelerometer_1"))
		/* Found I2C motion sensor */
		वापस ams_i2c_init(np);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SENSORS_AMS_PMU
	np = of_find_node_by_name(शून्य, "sms");
	अगर (np && of_device_is_compatible(np, "sms"))
		/* Found PMU motion sensor */
		वापस ams_pmu_init(np);
#पूर्ण_अगर
	वापस -ENODEV;
पूर्ण

व्योम ams_sensor_detach(व्योम)
अणु
	/* Remove input device */
	ams_input_निकास();

	/* Remove attributes */
	device_हटाओ_file(&ams_info.of_dev->dev, &dev_attr_current);

	/* Flush पूर्णांकerrupt worker
	 *
	 * We करो this after ams_info.निकास(), because an पूर्णांकerrupt might
	 * have arrived beक्रमe disabling them.
	 */
	flush_work(&ams_info.worker);

	/* Remove device */
	of_device_unरेजिस्टर(ams_info.of_dev);

	/* Remove handler */
	pmf_unरेजिस्टर_irq_client(&ams_shock_client);
	pmf_unरेजिस्टर_irq_client(&ams_मुक्तfall_client);
पूर्ण

अटल व्योम __निकास ams_निकास(व्योम)
अणु
	/* Shut करोwn implementation */
	ams_info.निकास();
पूर्ण

MODULE_AUTHOR("Stelian Pop, Michael Hanselmann");
MODULE_DESCRIPTION("Apple Motion Sensor driver");
MODULE_LICENSE("GPL");

module_init(ams_init);
module_निकास(ams_निकास);
