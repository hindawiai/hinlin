<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	w1_ds2433.c - w1 family 23 (DS2433) driver
 *
 * Copyright (c) 2005 Ben Gardner <bgardner@wabtec.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
#समावेश <linux/crc16.h>

#घोषणा CRC16_INIT		0
#घोषणा CRC16_VALID		0xb001

#पूर्ण_अगर

#समावेश <linux/w1.h>

#घोषणा W1_EEPROM_DS2433	0x23

#घोषणा W1_EEPROM_SIZE		512
#घोषणा W1_PAGE_COUNT		16
#घोषणा W1_PAGE_SIZE		32
#घोषणा W1_PAGE_BITS		5
#घोषणा W1_PAGE_MASK		0x1F

#घोषणा W1_F23_TIME		300

#घोषणा W1_F23_READ_EEPROM	0xF0
#घोषणा W1_F23_WRITE_SCRATCH	0x0F
#घोषणा W1_F23_READ_SCRATCH	0xAA
#घोषणा W1_F23_COPY_SCRATCH	0x55

काष्ठा w1_f23_data अणु
	u8	memory[W1_EEPROM_SIZE];
	u32	validcrc;
पूर्ण;

/**
 * Check the file size bounds and adjusts count as needed.
 * This would not be needed अगर the file size didn't reset to 0 after a ग_लिखो.
 */
अटल अंतरभूत माप_प्रकार w1_f23_fix_count(loff_t off, माप_प्रकार count, माप_प्रकार size)
अणु
	अगर (off > size)
		वापस 0;

	अगर ((off + count) > size)
		वापस (size - off);

	वापस count;
पूर्ण

#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
अटल पूर्णांक w1_f23_refresh_block(काष्ठा w1_slave *sl, काष्ठा w1_f23_data *data,
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

	wrbuf[0] = W1_F23_READ_EEPROM;
	wrbuf[1] = off & 0xff;
	wrbuf[2] = off >> 8;
	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_पढ़ो_block(sl->master, &data->memory[off], W1_PAGE_SIZE);

	/* cache the block अगर the CRC is valid */
	अगर (crc16(CRC16_INIT, &data->memory[off], W1_PAGE_SIZE) == CRC16_VALID)
		data->validcrc |= (1 << block);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_W1_SLAVE_DS2433_CRC */

अटल sमाप_प्रकार eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			   loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	काष्ठा w1_f23_data *data = sl->family_data;
	पूर्णांक i, min_page, max_page;
#अन्यथा
	u8 wrbuf[3];
#पूर्ण_अगर

	अगर ((count = w1_f23_fix_count(off, count, W1_EEPROM_SIZE)) == 0)
		वापस 0;

	mutex_lock(&sl->master->bus_mutex);

#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC

	min_page = (off >> W1_PAGE_BITS);
	max_page = (off + count - 1) >> W1_PAGE_BITS;
	क्रम (i = min_page; i <= max_page; i++) अणु
		अगर (w1_f23_refresh_block(sl, data, i)) अणु
			count = -EIO;
			जाओ out_up;
		पूर्ण
	पूर्ण
	स_नकल(buf, &data->memory[off], count);

#अन्यथा 	/* CONFIG_W1_SLAVE_DS2433_CRC */

	/* पढ़ो directly from the EEPROM */
	अगर (w1_reset_select_slave(sl)) अणु
		count = -EIO;
		जाओ out_up;
	पूर्ण

	wrbuf[0] = W1_F23_READ_EEPROM;
	wrbuf[1] = off & 0xff;
	wrbuf[2] = off >> 8;
	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_पढ़ो_block(sl->master, buf, count);

#पूर्ण_अगर	/* CONFIG_W1_SLAVE_DS2433_CRC */

out_up:
	mutex_unlock(&sl->master->bus_mutex);

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
अटल पूर्णांक w1_f23_ग_लिखो(काष्ठा w1_slave *sl, पूर्णांक addr, पूर्णांक len, स्थिर u8 *data)
अणु
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	काष्ठा w1_f23_data *f23 = sl->family_data;
#पूर्ण_अगर
	u8 wrbuf[4];
	u8 rdbuf[W1_PAGE_SIZE + 3];
	u8 es = (addr + len - 1) & 0x1f;

	/* Write the data to the scratchpad */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F23_WRITE_SCRATCH;
	wrbuf[1] = addr & 0xff;
	wrbuf[2] = addr >> 8;

	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_ग_लिखो_block(sl->master, data, len);

	/* Read the scratchpad and verअगरy */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	w1_ग_लिखो_8(sl->master, W1_F23_READ_SCRATCH);
	w1_पढ़ो_block(sl->master, rdbuf, len + 3);

	/* Compare what was पढ़ो against the data written */
	अगर ((rdbuf[0] != wrbuf[1]) || (rdbuf[1] != wrbuf[2]) ||
	    (rdbuf[2] != es) || (स_भेद(data, &rdbuf[3], len) != 0))
		वापस -1;

	/* Copy the scratchpad to EEPROM */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F23_COPY_SCRATCH;
	wrbuf[3] = es;
	w1_ग_लिखो_block(sl->master, wrbuf, 4);

	/* Sleep क्रम 5 ms to रुको क्रम the ग_लिखो to complete */
	msleep(5);

	/* Reset the bus to wake up the EEPROM (this may not be needed) */
	w1_reset_bus(sl->master);
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	f23->validcrc &= ~(1 << (addr >> W1_PAGE_BITS));
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल sमाप_प्रकार eeprom_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक addr, len, idx;

	अगर ((count = w1_f23_fix_count(off, count, W1_EEPROM_SIZE)) == 0)
		वापस 0;

#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	/* can only ग_लिखो full blocks in cached mode */
	अगर ((off & W1_PAGE_MASK) || (count & W1_PAGE_MASK)) अणु
		dev_err(&sl->dev, "invalid offset/count off=%d cnt=%zd\n",
			(पूर्णांक)off, count);
		वापस -EINVAL;
	पूर्ण

	/* make sure the block CRCs are valid */
	क्रम (idx = 0; idx < count; idx += W1_PAGE_SIZE) अणु
		अगर (crc16(CRC16_INIT, &buf[idx], W1_PAGE_SIZE) != CRC16_VALID) अणु
			dev_err(&sl->dev, "bad CRC at offset %d\n", (पूर्णांक)off);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
#पूर्ण_अगर	/* CONFIG_W1_SLAVE_DS2433_CRC */

	mutex_lock(&sl->master->bus_mutex);

	/* Can only ग_लिखो data to one page at a समय */
	idx = 0;
	जबतक (idx < count) अणु
		addr = off + idx;
		len = W1_PAGE_SIZE - (addr & W1_PAGE_MASK);
		अगर (len > (count - idx))
			len = count - idx;

		अगर (w1_f23_ग_लिखो(sl, addr, len, &buf[idx]) < 0) अणु
			count = -EIO;
			जाओ out_up;
		पूर्ण
		idx += len;
	पूर्ण

out_up:
	mutex_unlock(&sl->master->bus_mutex);

	वापस count;
पूर्ण

अटल BIN_ATTR_RW(eeprom, W1_EEPROM_SIZE);

अटल काष्ठा bin_attribute *w1_f23_bin_attributes[] = अणु
	&bin_attr_eeprom,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f23_group = अणु
	.bin_attrs = w1_f23_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f23_groups[] = अणु
	&w1_f23_group,
	शून्य,
पूर्ण;

अटल पूर्णांक w1_f23_add_slave(काष्ठा w1_slave *sl)
अणु
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	काष्ठा w1_f23_data *data;

	data = kzalloc(माप(काष्ठा w1_f23_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	sl->family_data = data;

#पूर्ण_अगर	/* CONFIG_W1_SLAVE_DS2433_CRC */
	वापस 0;
पूर्ण

अटल व्योम w1_f23_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
#अगर_घोषित CONFIG_W1_SLAVE_DS2433_CRC
	kमुक्त(sl->family_data);
	sl->family_data = शून्य;
#पूर्ण_अगर	/* CONFIG_W1_SLAVE_DS2433_CRC */
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_f23_fops = अणु
	.add_slave      = w1_f23_add_slave,
	.हटाओ_slave   = w1_f23_हटाओ_slave,
	.groups		= w1_f23_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_23 = अणु
	.fid = W1_EEPROM_DS2433,
	.fops = &w1_f23_fops,
पूर्ण;
module_w1_family(w1_family_23);

MODULE_AUTHOR("Ben Gardner <bgardner@wabtec.com>");
MODULE_DESCRIPTION("w1 family 23 driver for DS2433, 4kb EEPROM");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_EEPROM_DS2433));
