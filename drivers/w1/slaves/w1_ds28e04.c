<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	w1_ds28e04.c - w1 family 1C (DS28E04) driver
 *
 * Copyright (c) 2012 Markus Franke <franke.m@sebakmt.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc16.h>
#समावेश <linux/uaccess.h>

#घोषणा CRC16_INIT		0
#घोषणा CRC16_VALID		0xb001

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS28E04	0x1C

/* Allow the strong pullup to be disabled, but शेष to enabled.
 * If it was disabled a parasite घातered device might not get the required
 * current to copy the data from the scratchpad to EEPROM.  If it is enabled
 * parasite घातered devices have a better chance of getting the current
 * required.
 */
अटल पूर्णांक w1_strong_pullup = 1;
module_param_named(strong_pullup, w1_strong_pullup, पूर्णांक, 0);

/* enable/disable CRC checking on DS28E04-100 memory accesses */
अटल अक्षर w1_enable_crccheck = 1;

#घोषणा W1_EEPROM_SIZE		512
#घोषणा W1_PAGE_COUNT		16
#घोषणा W1_PAGE_SIZE		32
#घोषणा W1_PAGE_BITS		5
#घोषणा W1_PAGE_MASK		0x1F

#घोषणा W1_F1C_READ_EEPROM	0xF0
#घोषणा W1_F1C_WRITE_SCRATCH	0x0F
#घोषणा W1_F1C_READ_SCRATCH	0xAA
#घोषणा W1_F1C_COPY_SCRATCH	0x55
#घोषणा W1_F1C_ACCESS_WRITE	0x5A

#घोषणा W1_1C_REG_LOGIC_STATE	0x220

काष्ठा w1_f1C_data अणु
	u8	memory[W1_EEPROM_SIZE];
	u32	validcrc;
पूर्ण;

/**
 * Check the file size bounds and adjusts count as needed.
 * This would not be needed अगर the file size didn't reset to 0 after a ग_लिखो.
 */
अटल अंतरभूत माप_प्रकार w1_f1C_fix_count(loff_t off, माप_प्रकार count, माप_प्रकार size)
अणु
	अगर (off > size)
		वापस 0;

	अगर ((off + count) > size)
		वापस size - off;

	वापस count;
पूर्ण

अटल पूर्णांक w1_f1C_refresh_block(काष्ठा w1_slave *sl, काष्ठा w1_f1C_data *data,
				पूर्णांक block)
अणु
	u8	wrbuf[3];
	पूर्णांक	off = block * W1_PAGE_SIZE;

	अगर (data->validcrc & (1 << block))
		वापस 0;

	अगर (w1_reset_select_slave(sl)) अणु
		data->validcrc = 0;
		वापस -EIO;
	पूर्ण

	wrbuf[0] = W1_F1C_READ_EEPROM;
	wrbuf[1] = off & 0xff;
	wrbuf[2] = off >> 8;
	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_पढ़ो_block(sl->master, &data->memory[off], W1_PAGE_SIZE);

	/* cache the block अगर the CRC is valid */
	अगर (crc16(CRC16_INIT, &data->memory[off], W1_PAGE_SIZE) == CRC16_VALID)
		data->validcrc |= (1 << block);

	वापस 0;
पूर्ण

अटल पूर्णांक w1_f1C_पढ़ो(काष्ठा w1_slave *sl, पूर्णांक addr, पूर्णांक len, अक्षर *data)
अणु
	u8 wrbuf[3];

	/* पढ़ो directly from the EEPROM */
	अगर (w1_reset_select_slave(sl))
		वापस -EIO;

	wrbuf[0] = W1_F1C_READ_EEPROM;
	wrbuf[1] = addr & 0xff;
	wrbuf[2] = addr >> 8;

	w1_ग_लिखो_block(sl->master, wrbuf, माप(wrbuf));
	वापस w1_पढ़ो_block(sl->master, data, len);
पूर्ण

अटल sमाप_प्रकार eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			   loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	काष्ठा w1_f1C_data *data = sl->family_data;
	पूर्णांक i, min_page, max_page;

	count = w1_f1C_fix_count(off, count, W1_EEPROM_SIZE);
	अगर (count == 0)
		वापस 0;

	mutex_lock(&sl->master->mutex);

	अगर (w1_enable_crccheck) अणु
		min_page = (off >> W1_PAGE_BITS);
		max_page = (off + count - 1) >> W1_PAGE_BITS;
		क्रम (i = min_page; i <= max_page; i++) अणु
			अगर (w1_f1C_refresh_block(sl, data, i)) अणु
				count = -EIO;
				जाओ out_up;
			पूर्ण
		पूर्ण
		स_नकल(buf, &data->memory[off], count);
	पूर्ण अन्यथा अणु
		count = w1_f1C_पढ़ो(sl, off, count, buf);
	पूर्ण

out_up:
	mutex_unlock(&sl->master->mutex);

	वापस count;
पूर्ण

/**
 * Writes to the scratchpad and पढ़ोs it back क्रम verअगरication.
 * Then copies the scratchpad to EEPROM.
 * The data must be on one page.
 * The master must be locked.
 *
 * @param sl	The slave काष्ठाure
 * @param addr	Address क्रम the ग_लिखो
 * @param len   length must be <= (W1_PAGE_SIZE - (addr & W1_PAGE_MASK))
 * @param data	The data to ग_लिखो
 * @वापस	0=Success -1=failure
 */
अटल पूर्णांक w1_f1C_ग_लिखो(काष्ठा w1_slave *sl, पूर्णांक addr, पूर्णांक len, स्थिर u8 *data)
अणु
	u8 wrbuf[4];
	u8 rdbuf[W1_PAGE_SIZE + 3];
	u8 es = (addr + len - 1) & 0x1f;
	अचिन्हित पूर्णांक पंचांग = 10;
	पूर्णांक i;
	काष्ठा w1_f1C_data *f1C = sl->family_data;

	/* Write the data to the scratchpad */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F1C_WRITE_SCRATCH;
	wrbuf[1] = addr & 0xff;
	wrbuf[2] = addr >> 8;

	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_ग_लिखो_block(sl->master, data, len);

	/* Read the scratchpad and verअगरy */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	w1_ग_लिखो_8(sl->master, W1_F1C_READ_SCRATCH);
	w1_पढ़ो_block(sl->master, rdbuf, len + 3);

	/* Compare what was पढ़ो against the data written */
	अगर ((rdbuf[0] != wrbuf[1]) || (rdbuf[1] != wrbuf[2]) ||
	    (rdbuf[2] != es) || (स_भेद(data, &rdbuf[3], len) != 0))
		वापस -1;

	/* Copy the scratchpad to EEPROM */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F1C_COPY_SCRATCH;
	wrbuf[3] = es;

	क्रम (i = 0; i < माप(wrbuf); ++i) अणु
		/* issue 10ms strong pullup (or delay) on the last byte
		   क्रम writing the data from the scratchpad to EEPROM */
		अगर (w1_strong_pullup && i == माप(wrbuf)-1)
			w1_next_pullup(sl->master, पंचांग);

		w1_ग_लिखो_8(sl->master, wrbuf[i]);
	पूर्ण

	अगर (!w1_strong_pullup)
		msleep(पंचांग);

	अगर (w1_enable_crccheck) अणु
		/* invalidate cached data */
		f1C->validcrc &= ~(1 << (addr >> W1_PAGE_BITS));
	पूर्ण

	/* Reset the bus to wake up the EEPROM (this may not be needed) */
	w1_reset_bus(sl->master);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार eeprom_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)

अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक addr, len, idx;

	count = w1_f1C_fix_count(off, count, W1_EEPROM_SIZE);
	अगर (count == 0)
		वापस 0;

	अगर (w1_enable_crccheck) अणु
		/* can only ग_लिखो full blocks in cached mode */
		अगर ((off & W1_PAGE_MASK) || (count & W1_PAGE_MASK)) अणु
			dev_err(&sl->dev, "invalid offset/count off=%d cnt=%zd\n",
				(पूर्णांक)off, count);
			वापस -EINVAL;
		पूर्ण

		/* make sure the block CRCs are valid */
		क्रम (idx = 0; idx < count; idx += W1_PAGE_SIZE) अणु
			अगर (crc16(CRC16_INIT, &buf[idx], W1_PAGE_SIZE)
				!= CRC16_VALID) अणु
				dev_err(&sl->dev, "bad CRC at offset %d\n",
					(पूर्णांक)off);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_lock(&sl->master->mutex);

	/* Can only ग_लिखो data to one page at a समय */
	idx = 0;
	जबतक (idx < count) अणु
		addr = off + idx;
		len = W1_PAGE_SIZE - (addr & W1_PAGE_MASK);
		अगर (len > (count - idx))
			len = count - idx;

		अगर (w1_f1C_ग_लिखो(sl, addr, len, &buf[idx]) < 0) अणु
			count = -EIO;
			जाओ out_up;
		पूर्ण
		idx += len;
	पूर्ण

out_up:
	mutex_unlock(&sl->master->mutex);

	वापस count;
पूर्ण

अटल BIN_ATTR_RW(eeprom, W1_EEPROM_SIZE);

अटल sमाप_प्रकार pio_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			माप_प्रकार count)

अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;

	/* check arguments */
	अगर (off != 0 || count != 1 || buf == शून्य)
		वापस -EINVAL;

	mutex_lock(&sl->master->mutex);
	ret = w1_f1C_पढ़ो(sl, W1_1C_REG_LOGIC_STATE, count, buf);
	mutex_unlock(&sl->master->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार pio_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			 माप_प्रकार count)

अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	u8 wrbuf[3];
	u8 ack;

	/* check arguments */
	अगर (off != 0 || count != 1 || buf == शून्य)
		वापस -EINVAL;

	mutex_lock(&sl->master->mutex);

	/* Write the PIO data */
	अगर (w1_reset_select_slave(sl)) अणु
		mutex_unlock(&sl->master->mutex);
		वापस -1;
	पूर्ण

	/* set bit 7..2 to value '1' */
	*buf = *buf | 0xFC;

	wrbuf[0] = W1_F1C_ACCESS_WRITE;
	wrbuf[1] = *buf;
	wrbuf[2] = ~(*buf);
	w1_ग_लिखो_block(sl->master, wrbuf, 3);

	w1_पढ़ो_block(sl->master, &ack, माप(ack));

	mutex_unlock(&sl->master->mutex);

	/* check क्रम acknowledgement */
	अगर (ack != 0xAA)
		वापस -EIO;

	वापस count;
पूर्ण

अटल BIN_ATTR_RW(pio, 1);

अटल sमाप_प्रकार crccheck_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अगर (put_user(w1_enable_crccheck + 0x30, buf))
		वापस -EFAULT;

	वापस माप(w1_enable_crccheck);
पूर्ण

अटल sमाप_प्रकार crccheck_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर val;

	अगर (count != 1 || !buf)
		वापस -EINVAL;

	अगर (get_user(val, buf))
		वापस -EFAULT;

	/* convert to decimal */
	val = val - 0x30;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	/* set the new value */
	w1_enable_crccheck = val;

	वापस माप(w1_enable_crccheck);
पूर्ण

अटल DEVICE_ATTR_RW(crccheck);

अटल काष्ठा attribute *w1_f1C_attrs[] = अणु
	&dev_attr_crccheck.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *w1_f1C_bin_attrs[] = अणु
	&bin_attr_eeprom,
	&bin_attr_pio,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f1C_group = अणु
	.attrs		= w1_f1C_attrs,
	.bin_attrs	= w1_f1C_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f1C_groups[] = अणु
	&w1_f1C_group,
	शून्य,
पूर्ण;

अटल पूर्णांक w1_f1C_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_f1C_data *data = शून्य;

	अगर (w1_enable_crccheck) अणु
		data = kzalloc(माप(काष्ठा w1_f1C_data), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
		sl->family_data = data;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम w1_f1C_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	kमुक्त(sl->family_data);
	sl->family_data = शून्य;
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_f1C_fops = अणु
	.add_slave      = w1_f1C_add_slave,
	.हटाओ_slave   = w1_f1C_हटाओ_slave,
	.groups		= w1_f1C_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_1C = अणु
	.fid = W1_FAMILY_DS28E04,
	.fops = &w1_f1C_fops,
पूर्ण;
module_w1_family(w1_family_1C);

MODULE_AUTHOR("Markus Franke <franke.m@sebakmt.com>, <franm@hrz.tu-chemnitz.de>");
MODULE_DESCRIPTION("w1 family 1C driver for DS28E04, 4kb EEPROM and PIO");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS28E04));
