<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	w1_ds2405.c
 *
 * Copyright (c) 2017 Maciej S. Szmigiero <mail@maciej.szmigiero.name>
 * Based on w1_therm.c copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS2405	0x05

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maciej S. Szmigiero <mail@maciej.szmigiero.name>");
MODULE_DESCRIPTION("Driver for 1-wire Dallas DS2405 PIO.");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2405));

अटल पूर्णांक w1_ds2405_select(काष्ठा w1_slave *sl, bool only_active)
अणु
	काष्ठा w1_master *dev = sl->master;

	u64 dev_addr = le64_to_cpu(*(u64 *)&sl->reg_num);
	अचिन्हित पूर्णांक bit_ctr;

	अगर (w1_reset_bus(dev) != 0)
		वापस 0;

	/*
	 * We cannot use a normal Match ROM command
	 * since करोing so would toggle PIO state
	 */
	w1_ग_लिखो_8(dev, only_active ? W1_ALARM_SEARCH : W1_SEARCH);

	क्रम (bit_ctr = 0; bit_ctr < 64; bit_ctr++) अणु
		पूर्णांक bit2send = !!(dev_addr & BIT(bit_ctr));
		u8 ret;

		ret = w1_triplet(dev, bit2send);

		अगर ((ret & (BIT(0) | BIT(1))) ==
		    (BIT(0) | BIT(1))) /* no devices found */
			वापस 0;

		अगर (!!(ret & BIT(2)) != bit2send)
			/* wrong direction taken - no such device */
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक w1_ds2405_पढ़ो_pio(काष्ठा w1_slave *sl)
अणु
	अगर (w1_ds2405_select(sl, true))
		वापस 0; /* "active" means PIO is low */

	अगर (w1_ds2405_select(sl, false))
		वापस 1;

	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा w1_master *dev = sl->master;

	पूर्णांक ret;
	sमाप_प्रकार f_retval;
	u8 state;

	ret = mutex_lock_पूर्णांकerruptible(&dev->bus_mutex);
	अगर (ret)
		वापस ret;

	अगर (!w1_ds2405_select(sl, false)) अणु
		f_retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	state = w1_पढ़ो_8(dev);
	अगर (state != 0 &&
	    state != 0xff) अणु
		dev_err(device, "non-consistent state %x\n", state);
		f_retval = -EIO;
		जाओ out_unlock;
	पूर्ण

	*buf = state ? '1' : '0';
	f_retval = 1;

out_unlock:
	w1_reset_bus(dev);
	mutex_unlock(&dev->bus_mutex);

	वापस f_retval;
पूर्ण

अटल sमाप_प्रकार output_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा w1_master *dev = sl->master;

	पूर्णांक ret;
	sमाप_प्रकार f_retval;

	ret = mutex_lock_पूर्णांकerruptible(&dev->bus_mutex);
	अगर (ret)
		वापस ret;

	ret = w1_ds2405_पढ़ो_pio(sl);
	अगर (ret < 0) अणु
		f_retval = ret;
		जाओ out_unlock;
	पूर्ण

	*buf = ret ? '1' : '0';
	f_retval = 1;

out_unlock:
	w1_reset_bus(dev);
	mutex_unlock(&dev->bus_mutex);

	वापस f_retval;
पूर्ण

अटल sमाप_प्रकार output_store(काष्ठा device *device,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा w1_master *dev = sl->master;

	पूर्णांक ret, current_pio;
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार f_retval;

	अगर (count < 1)
		वापस -EINVAL;

	अगर (माला_पूछो(buf, " %u%n", &val, &ret) < 1)
		वापस -EINVAL;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	f_retval = ret;

	ret = mutex_lock_पूर्णांकerruptible(&dev->bus_mutex);
	अगर (ret)
		वापस ret;

	current_pio = w1_ds2405_पढ़ो_pio(sl);
	अगर (current_pio < 0) अणु
		f_retval = current_pio;
		जाओ out_unlock;
	पूर्ण

	अगर (current_pio == val)
		जाओ out_unlock;

	अगर (w1_reset_bus(dev) != 0) अणु
		f_retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	/*
	 * can't use w1_reset_select_slave() here since it uses Skip ROM अगर
	 * there is only one device on bus
	 */
	करो अणु
		u64 dev_addr = le64_to_cpu(*(u64 *)&sl->reg_num);
		u8 cmd[9];

		cmd[0] = W1_MATCH_ROM;
		स_नकल(&cmd[1], &dev_addr, माप(dev_addr));

		w1_ग_लिखो_block(dev, cmd, माप(cmd));
	पूर्ण जबतक (0);

out_unlock:
	w1_reset_bus(dev);
	mutex_unlock(&dev->bus_mutex);

	वापस f_retval;
पूर्ण

अटल DEVICE_ATTR_RO(state);
अटल DEVICE_ATTR_RW(output);

अटल काष्ठा attribute *w1_ds2405_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_output.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(w1_ds2405);

अटल स्थिर काष्ठा w1_family_ops w1_ds2405_fops = अणु
	.groups = w1_ds2405_groups
पूर्ण;

अटल काष्ठा w1_family w1_family_ds2405 = अणु
	.fid = W1_FAMILY_DS2405,
	.fops = &w1_ds2405_fops
पूर्ण;

module_w1_family(w1_family_ds2405);
