<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	w1_ds2423.c
 *
 * Copyright (c) 2010 Mika Laitio <lamikr@pilppa.org>
 *
 * This driver will पढ़ो and ग_लिखो the value of 4 counters to w1_slave file in
 * sys fileप्रणाली.
 * Inspired by the w1_therm and w1_ds2431 drivers.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc16.h>

#समावेश <linux/w1.h>

#घोषणा W1_COUNTER_DS2423	0x1D

#घोषणा CRC16_VALID	0xb001
#घोषणा CRC16_INIT	0

#घोषणा COUNTER_COUNT 4
#घोषणा READ_BYTE_COUNT 42

अटल sमाप_प्रकार w1_slave_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *out_buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा w1_master *dev = sl->master;
	u8 rbuf[COUNTER_COUNT * READ_BYTE_COUNT];
	u8 wrbuf[3];
	पूर्णांक rom_addr;
	पूर्णांक पढ़ो_byte_count;
	पूर्णांक result;
	sमाप_प्रकार c;
	पूर्णांक ii;
	पूर्णांक p;
	पूर्णांक crc;

	c		= PAGE_SIZE;
	rom_addr	= (12 << 5) + 31;
	wrbuf[0]	= 0xA5;
	wrbuf[1]	= rom_addr & 0xFF;
	wrbuf[2]	= rom_addr >> 8;
	mutex_lock(&dev->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_block(dev, wrbuf, 3);
		पढ़ो_byte_count = 0;
		क्रम (p = 0; p < 4; p++) अणु
			/*
			 * 1 byte क्रम first bytes in ram page पढ़ो
			 * 4 bytes क्रम counter
			 * 4 bytes क्रम zero bits
			 * 2 bytes क्रम crc
			 * 31 reमुख्यing bytes from the ram page
			 */
			पढ़ो_byte_count += w1_पढ़ो_block(dev,
				rbuf + (p * READ_BYTE_COUNT), READ_BYTE_COUNT);
			क्रम (ii = 0; ii < READ_BYTE_COUNT; ++ii)
				c -= snम_लिखो(out_buf + PAGE_SIZE - c,
					c, "%02x ",
					rbuf[(p * READ_BYTE_COUNT) + ii]);
			अगर (पढ़ो_byte_count != (p + 1) * READ_BYTE_COUNT) अणु
				dev_warn(device,
					"w1_counter_read() returned %u bytes "
					"instead of %d bytes wanted.\n",
					पढ़ो_byte_count,
					READ_BYTE_COUNT);
				c -= snम_लिखो(out_buf + PAGE_SIZE - c,
					c, "crc=NO\n");
			पूर्ण अन्यथा अणु
				अगर (p == 0) अणु
					crc = crc16(CRC16_INIT, wrbuf, 3);
					crc = crc16(crc, rbuf, 11);
				पूर्ण अन्यथा अणु
					/*
					 * DS2423 calculates crc from all bytes
					 * पढ़ो after the previous crc bytes.
					 */
					crc = crc16(CRC16_INIT,
						(rbuf + 11) +
						((p - 1) * READ_BYTE_COUNT),
						READ_BYTE_COUNT);
				पूर्ण
				अगर (crc == CRC16_VALID) अणु
					result = 0;
					क्रम (ii = 4; ii > 0; ii--) अणु
						result <<= 8;
						result |= rbuf[(p *
							READ_BYTE_COUNT) + ii];
					पूर्ण
					c -= snम_लिखो(out_buf + PAGE_SIZE - c,
						c, "crc=YES c=%d\n", result);
				पूर्ण अन्यथा अणु
					c -= snम_लिखो(out_buf + PAGE_SIZE - c,
						c, "crc=NO\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		c -= snम_लिखो(out_buf + PAGE_SIZE - c, c, "Connection error");
	पूर्ण
	mutex_unlock(&dev->bus_mutex);
	वापस PAGE_SIZE - c;
पूर्ण

अटल DEVICE_ATTR_RO(w1_slave);

अटल काष्ठा attribute *w1_f1d_attrs[] = अणु
	&dev_attr_w1_slave.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(w1_f1d);

अटल स्थिर काष्ठा w1_family_ops w1_f1d_fops = अणु
	.groups		= w1_f1d_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_1d = अणु
	.fid = W1_COUNTER_DS2423,
	.fops = &w1_f1d_fops,
पूर्ण;
module_w1_family(w1_family_1d);

MODULE_AUTHOR("Mika Laitio <lamikr@pilppa.org>");
MODULE_DESCRIPTION("w1 family 1d driver for DS2423, 4 counters and 4kb ram");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_COUNTER_DS2423));
