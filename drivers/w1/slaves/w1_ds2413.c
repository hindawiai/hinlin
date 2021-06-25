<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w1_ds2413.c - w1 family 3a (DS2413) driver
 * based on w1_ds2408.c by Jean-Francois Dagenais <dagenaisj@sonatest.com>
 *
 * Copyright (c) 2013 Mariusz Bialonczyk <manio@skyboo.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS2413	0x3A

#घोषणा W1_F3A_RETRIES                     3
#घोषणा W1_F3A_FUNC_PIO_ACCESS_READ        0xF5
#घोषणा W1_F3A_FUNC_PIO_ACCESS_WRITE       0x5A
#घोषणा W1_F3A_SUCCESS_CONFIRM_BYTE        0xAA
#घोषणा W1_F3A_INVALID_PIO_STATE           0xFF

अटल sमाप_प्रकार state_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			  माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	अचिन्हित पूर्णांक retries = W1_F3A_RETRIES;
	sमाप_प्रकार bytes_पढ़ो = -EIO;
	u8 state;

	dev_dbg(&sl->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (अचिन्हित पूर्णांक)off, count, buf);

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

next:
	अगर (w1_reset_select_slave(sl))
		जाओ out;

	जबतक (retries--) अणु
		w1_ग_लिखो_8(sl->master, W1_F3A_FUNC_PIO_ACCESS_READ);

		state = w1_पढ़ो_8(sl->master);
		अगर ((state & 0x0F) == ((~state >> 4) & 0x0F)) अणु
			/* complement is correct */
			*buf = state;
			bytes_पढ़ो = 1;
			जाओ out;
		पूर्ण अन्यथा अगर (state == W1_F3A_INVALID_PIO_STATE) अणु
			/* slave didn't respond, try to select it again */
			dev_warn(&sl->dev, "slave device did not respond to PIO_ACCESS_READ, " \
					    "reselecting, retries left: %d\n", retries);
			जाओ next;
		पूर्ण

		अगर (w1_reset_resume_command(sl->master))
			जाओ out; /* unrecoverable error */

		dev_warn(&sl->dev, "PIO_ACCESS_READ error, retries left: %d\n", retries);
	पूर्ण

out:
	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "%s, mutex unlocked, retries: %d\n",
		(bytes_पढ़ो > 0) ? "succeeded" : "error", retries);
	वापस bytes_पढ़ो;
पूर्ण

अटल BIN_ATTR_RO(state, 1);

अटल sमाप_प्रकार output_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[3];
	अचिन्हित पूर्णांक retries = W1_F3A_RETRIES;
	sमाप_प्रकार bytes_written = -EIO;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	dev_dbg(&sl->dev, "locking mutex for write_output");
	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

	अगर (w1_reset_select_slave(sl))
		जाओ out;

	/* according to the DS2413 datasheet the most signअगरicant 6 bits
	   should be set to "1"s, so करो it now */
	*buf = *buf | 0xFC;

	जबतक (retries--) अणु
		w1_buf[0] = W1_F3A_FUNC_PIO_ACCESS_WRITE;
		w1_buf[1] = *buf;
		w1_buf[2] = ~(*buf);
		w1_ग_लिखो_block(sl->master, w1_buf, 3);

		अगर (w1_पढ़ो_8(sl->master) == W1_F3A_SUCCESS_CONFIRM_BYTE) अणु
			bytes_written = 1;
			जाओ out;
		पूर्ण
		अगर (w1_reset_resume_command(sl->master))
			जाओ out; /* unrecoverable error */

		dev_warn(&sl->dev, "PIO_ACCESS_WRITE error, retries left: %d\n", retries);
	पूर्ण

out:
	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "%s, mutex unlocked, retries: %d\n",
		(bytes_written > 0) ? "succeeded" : "error", retries);
	वापस bytes_written;
पूर्ण

अटल BIN_ATTR(output, S_IRUGO | S_IWUSR | S_IWGRP, शून्य, output_ग_लिखो, 1);

अटल काष्ठा bin_attribute *w1_f3a_bin_attrs[] = अणु
	&bin_attr_state,
	&bin_attr_output,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f3a_group = अणु
	.bin_attrs = w1_f3a_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f3a_groups[] = अणु
	&w1_f3a_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_f3a_fops = अणु
	.groups		= w1_f3a_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_3a = अणु
	.fid = W1_FAMILY_DS2413,
	.fops = &w1_f3a_fops,
पूर्ण;
module_w1_family(w1_family_3a);

MODULE_AUTHOR("Mariusz Bialonczyk <manio@skyboo.net>");
MODULE_DESCRIPTION("w1 family 3a driver for DS2413 2 Pin IO");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2413));
