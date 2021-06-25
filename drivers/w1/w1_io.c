<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <यंत्र/पन.स>

#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>

#समावेश "w1_internal.h"

अटल पूर्णांक w1_delay_parm = 1;
module_param_named(delay_coef, w1_delay_parm, पूर्णांक, 0);

अटल पूर्णांक w1_disable_irqs = 0;
module_param_named(disable_irqs, w1_disable_irqs, पूर्णांक, 0);

अटल u8 w1_crc8_table[] = अणु
	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
	157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
	35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
	190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
	70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
	219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
	101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
	248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
	140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
	17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
	175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
	50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
	202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
	87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
	233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
	116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
पूर्ण;

अटल व्योम w1_delay(अचिन्हित दीर्घ पंचांग)
अणु
	udelay(पंचांग * w1_delay_parm);
पूर्ण

अटल व्योम w1_ग_लिखो_bit(काष्ठा w1_master *dev, पूर्णांक bit);
अटल u8 w1_पढ़ो_bit(काष्ठा w1_master *dev);

/**
 * w1_touch_bit() - Generates a ग_लिखो-0 or ग_लिखो-1 cycle and samples the level.
 * @dev:	the master device
 * @bit:	0 - ग_लिखो a 0, 1 - ग_लिखो a 0 पढ़ो the level
 */
u8 w1_touch_bit(काष्ठा w1_master *dev, पूर्णांक bit)
अणु
	अगर (dev->bus_master->touch_bit)
		वापस dev->bus_master->touch_bit(dev->bus_master->data, bit);
	अन्यथा अगर (bit)
		वापस w1_पढ़ो_bit(dev);
	अन्यथा अणु
		w1_ग_लिखो_bit(dev, 0);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(w1_touch_bit);

/**
 * w1_ग_लिखो_bit() - Generates a ग_लिखो-0 or ग_लिखो-1 cycle.
 * @dev:	the master device
 * @bit:	bit to ग_लिखो
 *
 * Only call अगर dev->bus_master->touch_bit is शून्य
 */
अटल व्योम w1_ग_लिखो_bit(काष्ठा w1_master *dev, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ flags = 0;

	अगर(w1_disable_irqs) local_irq_save(flags);

	अगर (bit) अणु
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 0);
		w1_delay(6);
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 1);
		w1_delay(64);
	पूर्ण अन्यथा अणु
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 0);
		w1_delay(60);
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 1);
		w1_delay(10);
	पूर्ण

	अगर(w1_disable_irqs) local_irq_restore(flags);
पूर्ण

/**
 * w1_pre_ग_लिखो() - pre-ग_लिखो operations
 * @dev:	the master device
 *
 * Pre-ग_लिखो operation, currently only supporting strong pullups.
 * Program the hardware क्रम a strong pullup, अगर one has been requested and
 * the hardware supports it.
 */
अटल व्योम w1_pre_ग_लिखो(काष्ठा w1_master *dev)
अणु
	अगर (dev->pullup_duration &&
		dev->enable_pullup && dev->bus_master->set_pullup) अणु
		dev->bus_master->set_pullup(dev->bus_master->data,
			dev->pullup_duration);
	पूर्ण
पूर्ण

/**
 * w1_post_ग_लिखो() - post-ग_लिखो options
 * @dev:	the master device
 *
 * Post-ग_लिखो operation, currently only supporting strong pullups.
 * If a strong pullup was requested, clear it अगर the hardware supports
 * them, or execute the delay otherwise, in either हाल clear the request.
 */
अटल व्योम w1_post_ग_लिखो(काष्ठा w1_master *dev)
अणु
	अगर (dev->pullup_duration) अणु
		अगर (dev->enable_pullup && dev->bus_master->set_pullup)
			dev->bus_master->set_pullup(dev->bus_master->data, 0);
		अन्यथा
			msleep(dev->pullup_duration);
		dev->pullup_duration = 0;
	पूर्ण
पूर्ण

/**
 * w1_ग_लिखो_8() - Writes 8 bits.
 * @dev:	the master device
 * @byte:	the byte to ग_लिखो
 */
व्योम w1_ग_लिखो_8(काष्ठा w1_master *dev, u8 byte)
अणु
	पूर्णांक i;

	अगर (dev->bus_master->ग_लिखो_byte) अणु
		w1_pre_ग_लिखो(dev);
		dev->bus_master->ग_लिखो_byte(dev->bus_master->data, byte);
	पूर्ण
	अन्यथा
		क्रम (i = 0; i < 8; ++i) अणु
			अगर (i == 7)
				w1_pre_ग_लिखो(dev);
			w1_touch_bit(dev, (byte >> i) & 0x1);
		पूर्ण
	w1_post_ग_लिखो(dev);
पूर्ण
EXPORT_SYMBOL_GPL(w1_ग_लिखो_8);


/**
 * w1_पढ़ो_bit() - Generates a ग_लिखो-1 cycle and samples the level.
 * @dev:	the master device
 *
 * Only call अगर dev->bus_master->touch_bit is शून्य
 */
अटल u8 w1_पढ़ो_bit(काष्ठा w1_master *dev)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags = 0;

	/* sample timing is critical here */
	local_irq_save(flags);
	dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 0);
	w1_delay(6);
	dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 1);
	w1_delay(9);

	result = dev->bus_master->पढ़ो_bit(dev->bus_master->data);
	local_irq_restore(flags);

	w1_delay(55);

	वापस result & 0x1;
पूर्ण

/**
 * w1_triplet() - * Does a triplet - used क्रम searching ROM addresses.
 * @dev:	the master device
 * @bdir:	the bit to ग_लिखो अगर both id_bit and comp_bit are 0
 *
 * Return bits:
 *  bit 0 = id_bit
 *  bit 1 = comp_bit
 *  bit 2 = dir_taken
 *
 * If both bits 0 & 1 are set, the search should be restarted.
 *
 * Return:        bit fields - see above
 */
u8 w1_triplet(काष्ठा w1_master *dev, पूर्णांक bdir)
अणु
	अगर (dev->bus_master->triplet)
		वापस dev->bus_master->triplet(dev->bus_master->data, bdir);
	अन्यथा अणु
		u8 id_bit   = w1_touch_bit(dev, 1);
		u8 comp_bit = w1_touch_bit(dev, 1);
		u8 retval;

		अगर (id_bit && comp_bit)
			वापस 0x03;  /* error */

		अगर (!id_bit && !comp_bit) अणु
			/* Both bits are valid, take the direction given */
			retval = bdir ? 0x04 : 0;
		पूर्ण अन्यथा अणु
			/* Only one bit is valid, take that direction */
			bdir = id_bit;
			retval = id_bit ? 0x05 : 0x02;
		पूर्ण

		अगर (dev->bus_master->touch_bit)
			w1_touch_bit(dev, bdir);
		अन्यथा
			w1_ग_लिखो_bit(dev, bdir);
		वापस retval;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(w1_triplet);

/**
 * w1_पढ़ो_8() - Reads 8 bits.
 * @dev:	the master device
 *
 * Return:        the byte पढ़ो
 */
u8 w1_पढ़ो_8(काष्ठा w1_master *dev)
अणु
	पूर्णांक i;
	u8 res = 0;

	अगर (dev->bus_master->पढ़ो_byte)
		res = dev->bus_master->पढ़ो_byte(dev->bus_master->data);
	अन्यथा
		क्रम (i = 0; i < 8; ++i)
			res |= (w1_touch_bit(dev,1) << i);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(w1_पढ़ो_8);

/**
 * w1_ग_लिखो_block() - Writes a series of bytes.
 * @dev:	the master device
 * @buf:	poपूर्णांकer to the data to ग_लिखो
 * @len:	the number of bytes to ग_लिखो
 */
व्योम w1_ग_लिखो_block(काष्ठा w1_master *dev, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (dev->bus_master->ग_लिखो_block) अणु
		w1_pre_ग_लिखो(dev);
		dev->bus_master->ग_लिखो_block(dev->bus_master->data, buf, len);
	पूर्ण
	अन्यथा
		क्रम (i = 0; i < len; ++i)
			w1_ग_लिखो_8(dev, buf[i]); /* calls w1_pre_ग_लिखो */
	w1_post_ग_लिखो(dev);
पूर्ण
EXPORT_SYMBOL_GPL(w1_ग_लिखो_block);

/**
 * w1_touch_block() - Touches a series of bytes.
 * @dev:	the master device
 * @buf:	poपूर्णांकer to the data to ग_लिखो
 * @len:	the number of bytes to ग_लिखो
 */
व्योम w1_touch_block(काष्ठा w1_master *dev, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i, j;
	u8 पंचांगp;

	क्रम (i = 0; i < len; ++i) अणु
		पंचांगp = 0;
		क्रम (j = 0; j < 8; ++j) अणु
			अगर (j == 7)
				w1_pre_ग_लिखो(dev);
			पंचांगp |= w1_touch_bit(dev, (buf[i] >> j) & 0x1) << j;
		पूर्ण

		buf[i] = पंचांगp;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(w1_touch_block);

/**
 * w1_पढ़ो_block() - Reads a series of bytes.
 * @dev:	the master device
 * @buf:	poपूर्णांकer to the buffer to fill
 * @len:	the number of bytes to पढ़ो
 * Return:	the number of bytes पढ़ो
 */
u8 w1_पढ़ो_block(काष्ठा w1_master *dev, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	u8 ret;

	अगर (dev->bus_master->पढ़ो_block)
		ret = dev->bus_master->पढ़ो_block(dev->bus_master->data, buf, len);
	अन्यथा अणु
		क्रम (i = 0; i < len; ++i)
			buf[i] = w1_पढ़ो_8(dev);
		ret = len;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(w1_पढ़ो_block);

/**
 * w1_reset_bus() - Issues a reset bus sequence.
 * @dev:	the master device
 * Return:	0=Device present, 1=No device present or error
 */
पूर्णांक w1_reset_bus(काष्ठा w1_master *dev)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags = 0;

	अगर(w1_disable_irqs) local_irq_save(flags);

	अगर (dev->bus_master->reset_bus)
		result = dev->bus_master->reset_bus(dev->bus_master->data) & 0x1;
	अन्यथा अणु
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 0);
		/* minimum 480, max ? us
		 * be nice and sleep, except 18b20 spec lists 960us maximum,
		 * so until we can sleep with microsecond accuracy, spin.
		 * Feel मुक्त to come up with some other way to give up the
		 * cpu क्रम such a लघु amount of समय AND get it back in
		 * the maximum amount of समय.
		 */
		w1_delay(500);
		dev->bus_master->ग_लिखो_bit(dev->bus_master->data, 1);
		w1_delay(70);

		result = dev->bus_master->पढ़ो_bit(dev->bus_master->data) & 0x1;
		/* minimum 70 (above) + 430 = 500 us
		 * There aren't any timing requirements between a reset and
		 * the following transactions.  Sleeping is safe here.
		 */
		/* w1_delay(430); min required समय */
		msleep(1);
	पूर्ण

	अगर(w1_disable_irqs) local_irq_restore(flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(w1_reset_bus);

u8 w1_calc_crc8(u8 * data, पूर्णांक len)
अणु
	u8 crc = 0;

	जबतक (len--)
		crc = w1_crc8_table[crc ^ *data++];

	वापस crc;
पूर्ण
EXPORT_SYMBOL_GPL(w1_calc_crc8);

व्योम w1_search_devices(काष्ठा w1_master *dev, u8 search_type, w1_slave_found_callback cb)
अणु
	dev->attempts++;
	अगर (dev->bus_master->search)
		dev->bus_master->search(dev->bus_master->data, dev,
			search_type, cb);
	अन्यथा
		w1_search(dev, search_type, cb);
पूर्ण

/**
 * w1_reset_select_slave() - reset and select a slave
 * @sl:		the slave to select
 *
 * Resets the bus and then selects the slave by sending either a skip rom
 * or a rom match.  A skip rom is issued अगर there is only one device
 * रेजिस्टरed on the bus.
 * The w1 master lock must be held.
 *
 * Return:	0=success, anything अन्यथा=error
 */
पूर्णांक w1_reset_select_slave(काष्ठा w1_slave *sl)
अणु
	अगर (w1_reset_bus(sl->master))
		वापस -1;

	अगर (sl->master->slave_count == 1)
		w1_ग_लिखो_8(sl->master, W1_SKIP_ROM);
	अन्यथा अणु
		u8 match[9] = अणुW1_MATCH_ROM, पूर्ण;
		u64 rn = le64_to_cpu(*((u64*)&sl->reg_num));

		स_नकल(&match[1], &rn, 8);
		w1_ग_लिखो_block(sl->master, match, 9);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(w1_reset_select_slave);

/**
 * w1_reset_resume_command() - resume instead of another match ROM
 * @dev:	the master device
 *
 * When the workflow with a slave amongst many requires several
 * successive commands a reset between each, this function is similar
 * to करोing a reset then a match ROM क्रम the last matched ROM. The
 * advantage being that the matched ROM step is skipped in favor of the
 * resume command. The slave must support the command of course.
 *
 * If the bus has only one slave, traditionnaly the match ROM is skipped
 * and a "SKIP ROM" is करोne क्रम efficiency. On multi-slave busses, this
 * करोesn't work of course, but the resume command is the next best thing.
 *
 * The w1 master lock must be held.
 */
पूर्णांक w1_reset_resume_command(काष्ठा w1_master *dev)
अणु
	अगर (w1_reset_bus(dev))
		वापस -1;

	w1_ग_लिखो_8(dev, dev->slave_count > 1 ? W1_RESUME_CMD : W1_SKIP_ROM);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(w1_reset_resume_command);

/**
 * w1_next_pullup() - रेजिस्टर क्रम a strong pullup
 * @dev:	the master device
 * @delay:	समय in milliseconds
 *
 * Put out a strong pull-up of the specअगरied duration after the next ग_लिखो
 * operation.  Not all hardware supports strong pullups.  Hardware that
 * करोesn't support strong pullups will sleep क्रम the given समय after the
 * ग_लिखो operation without a strong pullup.  This is a one shot request क्रम
 * the next ग_लिखो, specअगरying zero will clear a previous request.
 * The w1 master lock must be held.
 *
 * Return:	0=success, anything अन्यथा=error
 */
व्योम w1_next_pullup(काष्ठा w1_master *dev, पूर्णांक delay)
अणु
	dev->pullup_duration = delay;
पूर्ण
EXPORT_SYMBOL_GPL(w1_next_pullup);
