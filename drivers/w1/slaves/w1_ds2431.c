<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w1_ds2431.c - w1 family 2d (DS2431) driver
 *
 * Copyright (c) 2008 Bernhard Weirich <bernhard.weirich@riedel.net>
 *
 * Heavily inspired by w1_DS2433 driver from Ben Gardner <bgardner@wabtec.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>

#समावेश <linux/w1.h>

#घोषणा W1_EEPROM_DS2431	0x2D

#घोषणा W1_F2D_EEPROM_SIZE		128
#घोषणा W1_F2D_PAGE_COUNT		4
#घोषणा W1_F2D_PAGE_BITS		5
#घोषणा W1_F2D_PAGE_SIZE		(1<<W1_F2D_PAGE_BITS)
#घोषणा W1_F2D_PAGE_MASK		0x1F

#घोषणा W1_F2D_SCRATCH_BITS  3
#घोषणा W1_F2D_SCRATCH_SIZE  (1<<W1_F2D_SCRATCH_BITS)
#घोषणा W1_F2D_SCRATCH_MASK  (W1_F2D_SCRATCH_SIZE-1)

#घोषणा W1_F2D_READ_EEPROM	0xF0
#घोषणा W1_F2D_WRITE_SCRATCH	0x0F
#घोषणा W1_F2D_READ_SCRATCH	0xAA
#घोषणा W1_F2D_COPY_SCRATCH	0x55


#घोषणा W1_F2D_TPROG_MS		11

#घोषणा W1_F2D_READ_RETRIES		10
#घोषणा W1_F2D_READ_MAXLEN		8

/*
 * Check the file size bounds and adjusts count as needed.
 * This would not be needed अगर the file size didn't reset to 0 after a ग_लिखो.
 */
अटल अंतरभूत माप_प्रकार w1_f2d_fix_count(loff_t off, माप_प्रकार count, माप_प्रकार size)
अणु
	अगर (off > size)
		वापस 0;

	अगर ((off + count) > size)
		वापस size - off;

	वापस count;
पूर्ण

/*
 * Read a block from W1 ROM two बार and compares the results.
 * If they are equal they are वापसed, otherwise the पढ़ो
 * is repeated W1_F2D_READ_RETRIES बार.
 *
 * count must not exceed W1_F2D_READ_MAXLEN.
 */
अटल पूर्णांक w1_f2d_पढ़ोblock(काष्ठा w1_slave *sl, पूर्णांक off, पूर्णांक count, अक्षर *buf)
अणु
	u8 wrbuf[3];
	u8 cmp[W1_F2D_READ_MAXLEN];
	पूर्णांक tries = W1_F2D_READ_RETRIES;

	करो अणु
		wrbuf[0] = W1_F2D_READ_EEPROM;
		wrbuf[1] = off & 0xff;
		wrbuf[2] = off >> 8;

		अगर (w1_reset_select_slave(sl))
			वापस -1;

		w1_ग_लिखो_block(sl->master, wrbuf, 3);
		w1_पढ़ो_block(sl->master, buf, count);

		अगर (w1_reset_select_slave(sl))
			वापस -1;

		w1_ग_लिखो_block(sl->master, wrbuf, 3);
		w1_पढ़ो_block(sl->master, cmp, count);

		अगर (!स_भेद(cmp, buf, count))
			वापस 0;
	पूर्ण जबतक (--tries);

	dev_err(&sl->dev, "proof reading failed %d times\n",
			W1_F2D_READ_RETRIES);

	वापस -1;
पूर्ण

अटल sमाप_प्रकार eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			   loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक toकरो = count;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPROM_SIZE);
	अगर (count == 0)
		वापस 0;

	mutex_lock(&sl->master->bus_mutex);

	/* पढ़ो directly from the EEPROM in chunks of W1_F2D_READ_MAXLEN */
	जबतक (toकरो > 0) अणु
		पूर्णांक block_पढ़ो;

		अगर (toकरो >= W1_F2D_READ_MAXLEN)
			block_पढ़ो = W1_F2D_READ_MAXLEN;
		अन्यथा
			block_पढ़ो = toकरो;

		अगर (w1_f2d_पढ़ोblock(sl, off, block_पढ़ो, buf) < 0)
			count = -EIO;

		toकरो -= W1_F2D_READ_MAXLEN;
		buf += W1_F2D_READ_MAXLEN;
		off += W1_F2D_READ_MAXLEN;
	पूर्ण

	mutex_unlock(&sl->master->bus_mutex);

	वापस count;
पूर्ण

/*
 * Writes to the scratchpad and पढ़ोs it back क्रम verअगरication.
 * Then copies the scratchpad to EEPROM.
 * The data must be aligned at W1_F2D_SCRATCH_SIZE bytes and
 * must be W1_F2D_SCRATCH_SIZE bytes दीर्घ.
 * The master must be locked.
 *
 * @param sl	The slave काष्ठाure
 * @param addr	Address क्रम the ग_लिखो
 * @param len   length must be <= (W1_F2D_PAGE_SIZE - (addr & W1_F2D_PAGE_MASK))
 * @param data	The data to ग_लिखो
 * @वापस	0=Success -1=failure
 */
अटल पूर्णांक w1_f2d_ग_लिखो(काष्ठा w1_slave *sl, पूर्णांक addr, पूर्णांक len, स्थिर u8 *data)
अणु
	पूर्णांक tries = W1_F2D_READ_RETRIES;
	u8 wrbuf[4];
	u8 rdbuf[W1_F2D_SCRATCH_SIZE + 3];
	u8 es = (addr + len - 1) % W1_F2D_SCRATCH_SIZE;

retry:

	/* Write the data to the scratchpad */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F2D_WRITE_SCRATCH;
	wrbuf[1] = addr & 0xff;
	wrbuf[2] = addr >> 8;

	w1_ग_लिखो_block(sl->master, wrbuf, 3);
	w1_ग_लिखो_block(sl->master, data, len);

	/* Read the scratchpad and verअगरy */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	w1_ग_लिखो_8(sl->master, W1_F2D_READ_SCRATCH);
	w1_पढ़ो_block(sl->master, rdbuf, len + 3);

	/* Compare what was पढ़ो against the data written */
	अगर ((rdbuf[0] != wrbuf[1]) || (rdbuf[1] != wrbuf[2]) ||
	    (rdbuf[2] != es) || (स_भेद(data, &rdbuf[3], len) != 0)) अणु

		अगर (--tries)
			जाओ retry;

		dev_err(&sl->dev,
			"could not write to eeprom, scratchpad compare failed %d times\n",
			W1_F2D_READ_RETRIES);

		वापस -1;
	पूर्ण

	/* Copy the scratchpad to EEPROM */
	अगर (w1_reset_select_slave(sl))
		वापस -1;

	wrbuf[0] = W1_F2D_COPY_SCRATCH;
	wrbuf[3] = es;
	w1_ग_लिखो_block(sl->master, wrbuf, 4);

	/* Sleep क्रम tprog ms to रुको क्रम the ग_लिखो to complete */
	msleep(W1_F2D_TPROG_MS);

	/* Reset the bus to wake up the EEPROM  */
	w1_reset_bus(sl->master);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार eeprom_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक addr, len;
	पूर्णांक copy;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPROM_SIZE);
	अगर (count == 0)
		वापस 0;

	mutex_lock(&sl->master->bus_mutex);

	/* Can only ग_लिखो data in blocks of the size of the scratchpad */
	addr = off;
	len = count;
	जबतक (len > 0) अणु

		/* अगर len too लघु or addr not aligned */
		अगर (len < W1_F2D_SCRATCH_SIZE || addr & W1_F2D_SCRATCH_MASK) अणु
			अक्षर पंचांगp[W1_F2D_SCRATCH_SIZE];

			/* पढ़ो the block and update the parts to be written */
			अगर (w1_f2d_पढ़ोblock(sl, addr & ~W1_F2D_SCRATCH_MASK,
					W1_F2D_SCRATCH_SIZE, पंचांगp)) अणु
				count = -EIO;
				जाओ out_up;
			पूर्ण

			/* copy at most to the boundary of the PAGE or len */
			copy = W1_F2D_SCRATCH_SIZE -
				(addr & W1_F2D_SCRATCH_MASK);

			अगर (copy > len)
				copy = len;

			स_नकल(&पंचांगp[addr & W1_F2D_SCRATCH_MASK], buf, copy);
			अगर (w1_f2d_ग_लिखो(sl, addr & ~W1_F2D_SCRATCH_MASK,
					W1_F2D_SCRATCH_SIZE, पंचांगp) < 0) अणु
				count = -EIO;
				जाओ out_up;
			पूर्ण
		पूर्ण अन्यथा अणु

			copy = W1_F2D_SCRATCH_SIZE;
			अगर (w1_f2d_ग_लिखो(sl, addr, copy, buf) < 0) अणु
				count = -EIO;
				जाओ out_up;
			पूर्ण
		पूर्ण
		buf += copy;
		addr += copy;
		len -= copy;
	पूर्ण

out_up:
	mutex_unlock(&sl->master->bus_mutex);

	वापस count;
पूर्ण

अटल BIN_ATTR_RW(eeprom, W1_F2D_EEPROM_SIZE);

अटल काष्ठा bin_attribute *w1_f2d_bin_attrs[] = अणु
	&bin_attr_eeprom,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f2d_group = अणु
	.bin_attrs = w1_f2d_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f2d_groups[] = अणु
	&w1_f2d_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_f2d_fops = अणु
	.groups		= w1_f2d_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_2d = अणु
	.fid = W1_EEPROM_DS2431,
	.fops = &w1_f2d_fops,
पूर्ण;
module_w1_family(w1_family_2d);

MODULE_AUTHOR("Bernhard Weirich <bernhard.weirich@riedel.net>");
MODULE_DESCRIPTION("w1 family 2d driver for DS2431, 1kb EEPROM");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_EEPROM_DS2431));
