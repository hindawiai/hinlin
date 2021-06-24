<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w1_ds2406.c - w1 family 12 (DS2406) driver
 * based on w1_ds2413.c by Mariusz Bialonczyk <manio@skyboo.net>
 *
 * Copyright (c) 2014 Scott Alfter <scott@alfter.us>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc16.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS2406	0x12

#घोषणा W1_F12_FUNC_READ_STATUS		   0xAA
#घोषणा W1_F12_FUNC_WRITE_STATUS	   0x55

अटल sमाप_प्रकार w1_f12_पढ़ो_state(
	काष्ठा file *filp, काष्ठा kobject *kobj,
	काष्ठा bin_attribute *bin_attr,
	अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	u8 w1_buf[6]=अणुW1_F12_FUNC_READ_STATUS, 7, 0, 0, 0, 0पूर्ण;
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u16 crc=0;
	पूर्णांक i;
	sमाप_प्रकार rtnval=1;

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl)) अणु
		mutex_unlock(&sl->master->bus_mutex);
		वापस -EIO;
	पूर्ण

	w1_ग_लिखो_block(sl->master, w1_buf, 3);
	w1_पढ़ो_block(sl->master, w1_buf+3, 3);
	क्रम (i=0; i<6; i++)
		crc=crc16_byte(crc, w1_buf[i]);
	अगर (crc==0xb001) /* good पढ़ो? */
		*buf=((w1_buf[3]>>5)&3)|0x30;
	अन्यथा
		rtnval=-EIO;

	mutex_unlock(&sl->master->bus_mutex);

	वापस rtnval;
पूर्ण

अटल sमाप_प्रकार w1_f12_ग_लिखो_output(
	काष्ठा file *filp, काष्ठा kobject *kobj,
	काष्ठा bin_attribute *bin_attr,
	अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[6]=अणुW1_F12_FUNC_WRITE_STATUS, 7, 0, 0, 0, 0पूर्ण;
	u16 crc=0;
	पूर्णांक i;
	sमाप_प्रकार rtnval=1;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl)) अणु
		mutex_unlock(&sl->master->bus_mutex);
		वापस -EIO;
	पूर्ण

	w1_buf[3] = (((*buf)&3)<<5)|0x1F;
	w1_ग_लिखो_block(sl->master, w1_buf, 4);
	w1_पढ़ो_block(sl->master, w1_buf+4, 2);
	क्रम (i=0; i<6; i++)
		crc=crc16_byte(crc, w1_buf[i]);
	अगर (crc==0xb001) /* good पढ़ो? */
		w1_ग_लिखो_8(sl->master, 0xFF);
	अन्यथा
		rtnval=-EIO;

	mutex_unlock(&sl->master->bus_mutex);
	वापस rtnval;
पूर्ण

#घोषणा NB_SYSFS_BIN_खाताS 2
अटल काष्ठा bin_attribute w1_f12_sysfs_bin_files[NB_SYSFS_BIN_खाताS] = अणु
	अणु
		.attr = अणु
			.name = "state",
			.mode = S_IRUGO,
		पूर्ण,
		.size = 1,
		.पढ़ो = w1_f12_पढ़ो_state,
	पूर्ण,
	अणु
		.attr = अणु
			.name = "output",
			.mode = S_IRUGO | S_IWUSR | S_IWGRP,
		पूर्ण,
		.size = 1,
		.ग_लिखो = w1_f12_ग_लिखो_output,
	पूर्ण
पूर्ण;

अटल पूर्णांक w1_f12_add_slave(काष्ठा w1_slave *sl)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NB_SYSFS_BIN_खाताS && !err; ++i)
		err = sysfs_create_bin_file(
			&sl->dev.kobj,
			&(w1_f12_sysfs_bin_files[i]));
	अगर (err)
		जबतक (--i >= 0)
			sysfs_हटाओ_bin_file(&sl->dev.kobj,
				&(w1_f12_sysfs_bin_files[i]));
	वापस err;
पूर्ण

अटल व्योम w1_f12_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	पूर्णांक i;
	क्रम (i = NB_SYSFS_BIN_खाताS - 1; i >= 0; --i)
		sysfs_हटाओ_bin_file(&sl->dev.kobj,
			&(w1_f12_sysfs_bin_files[i]));
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_f12_fops = अणु
	.add_slave      = w1_f12_add_slave,
	.हटाओ_slave   = w1_f12_हटाओ_slave,
पूर्ण;

अटल काष्ठा w1_family w1_family_12 = अणु
	.fid = W1_FAMILY_DS2406,
	.fops = &w1_f12_fops,
पूर्ण;
module_w1_family(w1_family_12);

MODULE_AUTHOR("Scott Alfter <scott@alfter.us>");
MODULE_DESCRIPTION("w1 family 12 driver for DS2406 2 Pin IO");
MODULE_LICENSE("GPL");
