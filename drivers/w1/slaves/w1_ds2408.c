<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	w1_ds2408.c - w1 family 29 (DS2408) driver
 *
 * Copyright (c) 2010 Jean-Francois Dagenais <dagenaisj@sonatest.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS2408	0x29

#घोषणा W1_F29_RETRIES		3

#घोषणा W1_F29_REG_LOGIG_STATE             0x88 /* R */
#घोषणा W1_F29_REG_OUTPUT_LATCH_STATE      0x89 /* R */
#घोषणा W1_F29_REG_ACTIVITY_LATCH_STATE    0x8A /* R */
#घोषणा W1_F29_REG_COND_SEARCH_SELECT_MASK 0x8B /* RW */
#घोषणा W1_F29_REG_COND_SEARCH_POL_SELECT  0x8C /* RW */
#घोषणा W1_F29_REG_CONTROL_AND_STATUS      0x8D /* RW */

#घोषणा W1_F29_FUNC_READ_PIO_REGS          0xF0
#घोषणा W1_F29_FUNC_CHANN_ACCESS_READ      0xF5
#घोषणा W1_F29_FUNC_CHANN_ACCESS_WRITE     0x5A
/* also used to ग_लिखो the control/status reg (0x8D): */
#घोषणा W1_F29_FUNC_WRITE_COND_SEARCH_REG  0xCC
#घोषणा W1_F29_FUNC_RESET_ACTIVITY_LATCHES 0xC3

#घोषणा W1_F29_SUCCESS_CONFIRM_BYTE        0xAA

अटल पूर्णांक _पढ़ो_reg(काष्ठा w1_slave *sl, u8 address, अचिन्हित अक्षर* buf)
अणु
	u8 wrbuf[3];
	dev_dbg(&sl->dev,
			"Reading with slave: %p, reg addr: %0#4x, buff addr: %p",
			sl, (अचिन्हित पूर्णांक)address, buf);

	अगर (!buf)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

	अगर (w1_reset_select_slave(sl)) अणु
		mutex_unlock(&sl->master->bus_mutex);
		वापस -EIO;
	पूर्ण

	wrbuf[0] = W1_F29_FUNC_READ_PIO_REGS;
	wrbuf[1] = address;
	wrbuf[2] = 0;
	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	*buf = w1_पढ़ो_8(sl->master);

	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex unlocked");
	वापस 1;
पूर्ण

अटल sमाप_प्रकार state_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			  माप_प्रकार count)
अणु
	dev_dbg(&kobj_to_w1_slave(kobj)->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (अचिन्हित पूर्णांक)off, count, buf);
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj), W1_F29_REG_LOGIG_STATE, buf);
पूर्ण

अटल sमाप_प्रकार output_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			   loff_t off, माप_प्रकार count)
अणु
	dev_dbg(&kobj_to_w1_slave(kobj)->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (अचिन्हित पूर्णांक)off, count, buf);
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj),
					 W1_F29_REG_OUTPUT_LATCH_STATE, buf);
पूर्ण

अटल sमाप_प्रकार activity_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			     loff_t off, माप_प्रकार count)
अणु
	dev_dbg(&kobj_to_w1_slave(kobj)->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (अचिन्हित पूर्णांक)off, count, buf);
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj),
					 W1_F29_REG_ACTIVITY_LATCH_STATE, buf);
पूर्ण

अटल sमाप_प्रकार cond_search_mask_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				     loff_t off, माप_प्रकार count)
अणु
	dev_dbg(&kobj_to_w1_slave(kobj)->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (अचिन्हित पूर्णांक)off, count, buf);
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj),
		W1_F29_REG_COND_SEARCH_SELECT_MASK, buf);
पूर्ण

अटल sमाप_प्रकार cond_search_polarity_पढ़ो(काष्ठा file *filp,
					 काष्ठा kobject *kobj,
					 काष्ठा bin_attribute *bin_attr,
					 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj),
		W1_F29_REG_COND_SEARCH_POL_SELECT, buf);
पूर्ण

अटल sमाप_प्रकार status_control_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				   loff_t off, माप_प्रकार count)
अणु
	अगर (count != 1 || off != 0)
		वापस -EFAULT;
	वापस _पढ़ो_reg(kobj_to_w1_slave(kobj),
		W1_F29_REG_CONTROL_AND_STATUS, buf);
पूर्ण

#अगर_घोषित CONFIG_W1_SLAVE_DS2408_READBACK
अटल bool optional_पढ़ो_back_valid(काष्ठा w1_slave *sl, u8 expected)
अणु
	u8 w1_buf[3];

	अगर (w1_reset_resume_command(sl->master))
		वापस false;

	w1_buf[0] = W1_F29_FUNC_READ_PIO_REGS;
	w1_buf[1] = W1_F29_REG_OUTPUT_LATCH_STATE;
	w1_buf[2] = 0;

	w1_ग_लिखो_block(sl->master, w1_buf, 3);

	वापस (w1_पढ़ो_8(sl->master) == expected);
पूर्ण
#अन्यथा
अटल bool optional_पढ़ो_back_valid(काष्ठा w1_slave *sl, u8 expected)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार output_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[3];
	अचिन्हित पूर्णांक retries = W1_F29_RETRIES;
	sमाप_प्रकार bytes_written = -EIO;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	dev_dbg(&sl->dev, "locking mutex for write_output");
	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

	अगर (w1_reset_select_slave(sl))
		जाओ out;

	करो अणु
		w1_buf[0] = W1_F29_FUNC_CHANN_ACCESS_WRITE;
		w1_buf[1] = *buf;
		w1_buf[2] = ~(*buf);

		w1_ग_लिखो_block(sl->master, w1_buf, 3);

		अगर (w1_पढ़ो_8(sl->master) == W1_F29_SUCCESS_CONFIRM_BYTE &&
		    optional_पढ़ो_back_valid(sl, *buf)) अणु
			bytes_written = 1;
			जाओ out;
		पूर्ण

		अगर (w1_reset_resume_command(sl->master))
			जाओ out; /* unrecoverable error */
		/* try again, the slave is पढ़ोy क्रम a command */
	पूर्ण जबतक (--retries);

out:
	mutex_unlock(&sl->master->bus_mutex);

	dev_dbg(&sl->dev, "%s, mutex unlocked retries:%d\n",
		(bytes_written > 0) ? "succeeded" : "error", retries);

	वापस bytes_written;
पूर्ण


/**
 * Writing to the activity file resets the activity latches.
 */
अटल sमाप_प्रकार activity_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			      loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	अचिन्हित पूर्णांक retries = W1_F29_RETRIES;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl))
		जाओ error;

	जबतक (retries--) अणु
		w1_ग_लिखो_8(sl->master, W1_F29_FUNC_RESET_ACTIVITY_LATCHES);
		अगर (w1_पढ़ो_8(sl->master) == W1_F29_SUCCESS_CONFIRM_BYTE) अणु
			mutex_unlock(&sl->master->bus_mutex);
			वापस 1;
		पूर्ण
		अगर (w1_reset_resume_command(sl->master))
			जाओ error;
	पूर्ण

error:
	mutex_unlock(&sl->master->bus_mutex);
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार status_control_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				    loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 w1_buf[4];
	अचिन्हित पूर्णांक retries = W1_F29_RETRIES;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl))
		जाओ error;

	जबतक (retries--) अणु
		w1_buf[0] = W1_F29_FUNC_WRITE_COND_SEARCH_REG;
		w1_buf[1] = W1_F29_REG_CONTROL_AND_STATUS;
		w1_buf[2] = 0;
		w1_buf[3] = *buf;

		w1_ग_लिखो_block(sl->master, w1_buf, 4);
		अगर (w1_reset_resume_command(sl->master))
			जाओ error;

		w1_buf[0] = W1_F29_FUNC_READ_PIO_REGS;
		w1_buf[1] = W1_F29_REG_CONTROL_AND_STATUS;
		w1_buf[2] = 0;

		w1_ग_लिखो_block(sl->master, w1_buf, 3);
		अगर (w1_पढ़ो_8(sl->master) == *buf) अणु
			/* success! */
			mutex_unlock(&sl->master->bus_mutex);
			वापस 1;
		पूर्ण
	पूर्ण
error:
	mutex_unlock(&sl->master->bus_mutex);

	वापस -EIO;
पूर्ण

/*
 * This is a special sequence we must करो to ensure the P0 output is not stuck
 * in test mode. This is described in rev 2 of the ds2408's datasheet
 * (http://datasheets.maximपूर्णांकegrated.com/en/ds/DS2408.pdf) under
 * "APPLICATION INFORMATION/Power-up timing".
 */
अटल पूर्णांक w1_f29_disable_test_mode(काष्ठा w1_slave *sl)
अणु
	पूर्णांक res;
	u8 magic[10] = अणु0x96, पूर्ण;
	u64 rn = le64_to_cpu(*((u64*)&sl->reg_num));

	स_नकल(&magic[1], &rn, 8);
	magic[9] = 0x3C;

	mutex_lock(&sl->master->bus_mutex);

	res = w1_reset_bus(sl->master);
	अगर (res)
		जाओ out;
	w1_ग_लिखो_block(sl->master, magic, ARRAY_SIZE(magic));

	res = w1_reset_bus(sl->master);
out:
	mutex_unlock(&sl->master->bus_mutex);
	वापस res;
पूर्ण

अटल BIN_ATTR_RO(state, 1);
अटल BIN_ATTR_RW(output, 1);
अटल BIN_ATTR_RW(activity, 1);
अटल BIN_ATTR_RO(cond_search_mask, 1);
अटल BIN_ATTR_RO(cond_search_polarity, 1);
अटल BIN_ATTR_RW(status_control, 1);

अटल काष्ठा bin_attribute *w1_f29_bin_attrs[] = अणु
	&bin_attr_state,
	&bin_attr_output,
	&bin_attr_activity,
	&bin_attr_cond_search_mask,
	&bin_attr_cond_search_polarity,
	&bin_attr_status_control,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f29_group = अणु
	.bin_attrs = w1_f29_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f29_groups[] = अणु
	&w1_f29_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_f29_fops = अणु
	.add_slave      = w1_f29_disable_test_mode,
	.groups		= w1_f29_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_29 = अणु
	.fid = W1_FAMILY_DS2408,
	.fops = &w1_f29_fops,
पूर्ण;
module_w1_family(w1_family_29);

MODULE_AUTHOR("Jean-Francois Dagenais <dagenaisj@sonatest.com>");
MODULE_DESCRIPTION("w1 family 29 driver for DS2408 8 Pin IO");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2408));
