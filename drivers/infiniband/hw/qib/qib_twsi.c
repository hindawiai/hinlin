<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qib.h"

/*
 * QLogic_IB "Two Wire Serial Interface" driver.
 * Originally written क्रम a not-quite-i2c serial eeprom, which is
 * still used on some supported boards. Later boards have added a
 * variety of other uses, most board-specअगरic, so the bit-boffing
 * part has been split off to this file, जबतक the other parts
 * have been moved to chip-specअगरic files.
 *
 * We have also dropped all pretense of fully generic (e.g. pretend
 * we करोn't know whether '1' is the higher voltage) पूर्णांकerface, as
 * the restrictions of the generic i2c पूर्णांकerface (e.g. no access from
 * driver itself) make it unsuitable क्रम this use.
 */

#घोषणा READ_CMD 1
#घोषणा WRITE_CMD 0

/**
 * i2c_रुको_क्रम_ग_लिखोs - रुको क्रम a ग_लिखो
 * @dd: the qlogic_ib device
 *
 * We use this instead of udelay directly, so we can make sure
 * that previous रेजिस्टर ग_लिखोs have been flushed all the way
 * to the chip.  Since we are delaying anyway, the cost करोesn't
 * hurt, and makes the bit twiddling more regular
 */
अटल व्योम i2c_रुको_क्रम_ग_लिखोs(काष्ठा qib_devdata *dd)
अणु
	/*
	 * implicit पढ़ो of EXTStatus is as good as explicit
	 * पढ़ो of scratch, अगर all we want to करो is flush
	 * ग_लिखोs.
	 */
	dd->f_gpio_mod(dd, 0, 0, 0);
	rmb(); /* अंतरभूतd, so prevent compiler reordering */
पूर्ण

/*
 * QSFP modules are allowed to hold SCL low क्रम 500uSec. Allow twice that
 * क्रम "almost compliant" modules
 */
#घोषणा SCL_WAIT_USEC 1000

/* BUF_WAIT is समय bus must be मुक्त between STOP or ACK and to next START.
 * Should be 20, but some chips need more.
 */
#घोषणा TWSI_BUF_WAIT_USEC 60

अटल व्योम scl_out(काष्ठा qib_devdata *dd, u8 bit)
अणु
	u32 mask;

	udelay(1);

	mask = 1UL << dd->gpio_scl_num;

	/* SCL is meant to be bare-drain, so never set "OUT", just सूची */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	/*
	 * Allow क्रम slow slaves by simple
	 * delay क्रम falling edge, sampling on rise.
	 */
	अगर (!bit)
		udelay(2);
	अन्यथा अणु
		पूर्णांक rise_usec;

		क्रम (rise_usec = SCL_WAIT_USEC; rise_usec > 0; rise_usec -= 2) अणु
			अगर (mask & dd->f_gpio_mod(dd, 0, 0, 0))
				अवरोध;
			udelay(2);
		पूर्ण
		अगर (rise_usec <= 0)
			qib_dev_err(dd, "SCL interface stuck low > %d uSec\n",
				    SCL_WAIT_USEC);
	पूर्ण
	i2c_रुको_क्रम_ग_लिखोs(dd);
पूर्ण

अटल व्योम sda_out(काष्ठा qib_devdata *dd, u8 bit)
अणु
	u32 mask;

	mask = 1UL << dd->gpio_sda_num;

	/* SDA is meant to be bare-drain, so never set "OUT", just सूची */
	dd->f_gpio_mod(dd, 0, bit ? 0 : mask, mask);

	i2c_रुको_क्रम_ग_लिखोs(dd);
	udelay(2);
पूर्ण

अटल u8 sda_in(काष्ठा qib_devdata *dd, पूर्णांक रुको)
अणु
	पूर्णांक bnum;
	u32 पढ़ो_val, mask;

	bnum = dd->gpio_sda_num;
	mask = (1UL << bnum);
	/* SDA is meant to be bare-drain, so never set "OUT", just सूची */
	dd->f_gpio_mod(dd, 0, 0, mask);
	पढ़ो_val = dd->f_gpio_mod(dd, 0, 0, 0);
	अगर (रुको)
		i2c_रुको_क्रम_ग_लिखोs(dd);
	वापस (पढ़ो_val & mask) >> bnum;
पूर्ण

/**
 * i2c_ackrcv - see अगर ack following ग_लिखो is true
 * @dd: the qlogic_ib device
 */
अटल पूर्णांक i2c_ackrcv(काष्ठा qib_devdata *dd)
अणु
	u8 ack_received;

	/* AT ENTRY SCL = LOW */
	/* change direction, ignore data */
	ack_received = sda_in(dd, 1);
	scl_out(dd, 1);
	ack_received = sda_in(dd, 1) == 0;
	scl_out(dd, 0);
	वापस ack_received;
पूर्ण

अटल व्योम stop_cmd(काष्ठा qib_devdata *dd);

/**
 * rd_byte - पढ़ो a byte, sending STOP on last, अन्यथा ACK
 * @dd: the qlogic_ib device
 * @last: identअगरies the last पढ़ो
 *
 * Returns byte shअगरted out of device
 */
अटल पूर्णांक rd_byte(काष्ठा qib_devdata *dd, पूर्णांक last)
अणु
	पूर्णांक bit_cntr, data;

	data = 0;

	क्रम (bit_cntr = 7; bit_cntr >= 0; --bit_cntr) अणु
		data <<= 1;
		scl_out(dd, 1);
		data |= sda_in(dd, 0);
		scl_out(dd, 0);
	पूर्ण
	अगर (last) अणु
		scl_out(dd, 1);
		stop_cmd(dd);
	पूर्ण अन्यथा अणु
		sda_out(dd, 0);
		scl_out(dd, 1);
		scl_out(dd, 0);
		sda_out(dd, 1);
	पूर्ण
	वापस data;
पूर्ण

/**
 * wr_byte - ग_लिखो a byte, one bit at a समय
 * @dd: the qlogic_ib device
 * @data: the byte to ग_लिखो
 *
 * Returns 0 अगर we got the following ack, otherwise 1
 */
अटल पूर्णांक wr_byte(काष्ठा qib_devdata *dd, u8 data)
अणु
	पूर्णांक bit_cntr;
	u8 bit;

	क्रम (bit_cntr = 7; bit_cntr >= 0; bit_cntr--) अणु
		bit = (data >> bit_cntr) & 1;
		sda_out(dd, bit);
		scl_out(dd, 1);
		scl_out(dd, 0);
	पूर्ण
	वापस (!i2c_ackrcv(dd)) ? 1 : 0;
पूर्ण

/*
 * issue TWSI start sequence:
 * (both घड़ी/data high, घड़ी high, data low जबतक घड़ी is high)
 */
अटल व्योम start_seq(काष्ठा qib_devdata *dd)
अणु
	sda_out(dd, 1);
	scl_out(dd, 1);
	sda_out(dd, 0);
	udelay(1);
	scl_out(dd, 0);
पूर्ण

/**
 * stop_seq - transmit the stop sequence
 * @dd: the qlogic_ib device
 *
 * (both घड़ी/data low, घड़ी high, data high जबतक घड़ी is high)
 */
अटल व्योम stop_seq(काष्ठा qib_devdata *dd)
अणु
	scl_out(dd, 0);
	sda_out(dd, 0);
	scl_out(dd, 1);
	sda_out(dd, 1);
पूर्ण

/**
 * stop_cmd - transmit the stop condition
 * @dd: the qlogic_ib device
 *
 * (both घड़ी/data low, घड़ी high, data high जबतक घड़ी is high)
 */
अटल व्योम stop_cmd(काष्ठा qib_devdata *dd)
अणु
	stop_seq(dd);
	udelay(TWSI_BUF_WAIT_USEC);
पूर्ण

/**
 * qib_twsi_reset - reset I2C communication
 * @dd: the qlogic_ib device
 */

पूर्णांक qib_twsi_reset(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक घड़ी_cycles_left = 9;
	पूर्णांक was_high = 0;
	u32 pins, mask;

	/* Both SCL and SDA should be high. If not, there
	 * is something wrong.
	 */
	mask = (1UL << dd->gpio_scl_num) | (1UL << dd->gpio_sda_num);

	/*
	 * Force pins to desired innocuous state.
	 * This is the शेष घातer-on state with out=0 and dir=0,
	 * So tri-stated and should be भग्नing high (barring HW problems)
	 */
	dd->f_gpio_mod(dd, 0, 0, mask);

	/*
	 * Clock nine बार to get all listeners पूर्णांकo a sane state.
	 * If SDA करोes not go high at any poपूर्णांक, we are wedged.
	 * One venकरोr recommends then issuing START followed by STOP.
	 * we cannot use our "normal" functions to करो that, because
	 * अगर SCL drops between them, another venकरोr's part will
	 * wedge, dropping SDA and keeping it low क्रमever, at the end of
	 * the next transaction (even अगर it was not the device addressed).
	 * So our START and STOP take place with SCL held high.
	 */
	जबतक (घड़ी_cycles_left--) अणु
		scl_out(dd, 0);
		scl_out(dd, 1);
		/* Note अगर SDA is high, but keep घड़ीing to sync slave */
		was_high |= sda_in(dd, 0);
	पूर्ण

	अगर (was_high) अणु
		/*
		 * We saw a high, which we hope means the slave is sync'd.
		 * Issue START, STOP, छोड़ो क्रम T_BUF.
		 */

		pins = dd->f_gpio_mod(dd, 0, 0, 0);
		अगर ((pins & mask) != mask)
			qib_dev_err(dd, "GPIO pins not at rest: %d\n",
				    pins & mask);
		/* Drop SDA to issue START */
		udelay(1); /* Guarantee .6 uSec setup */
		sda_out(dd, 0);
		udelay(1); /* Guarantee .6 uSec hold */
		/* At this poपूर्णांक, SCL is high, SDA low. Raise SDA क्रम STOP */
		sda_out(dd, 1);
		udelay(TWSI_BUF_WAIT_USEC);
	पूर्ण

	वापस !was_high;
पूर्ण

#घोषणा QIB_TWSI_START 0x100
#घोषणा QIB_TWSI_STOP 0x200

/* Write byte to TWSI, optionally prefixed with START or suffixed with
 * STOP.
 * वापसs 0 अगर OK (ACK received), अन्यथा != 0
 */
अटल पूर्णांक qib_twsi_wr(काष्ठा qib_devdata *dd, पूर्णांक data, पूर्णांक flags)
अणु
	पूर्णांक ret = 1;

	अगर (flags & QIB_TWSI_START)
		start_seq(dd);

	ret = wr_byte(dd, data); /* Leaves SCL low (from i2c_ackrcv()) */

	अगर (flags & QIB_TWSI_STOP)
		stop_cmd(dd);
	वापस ret;
पूर्ण

/* Added functionality क्रम IBA7220-based cards */
#घोषणा QIB_TEMP_DEV 0x98

/*
 * qib_twsi_blk_rd
 * Formerly called qib_eeprom_पूर्णांकernal_पढ़ो, and only used क्रम eeprom,
 * but now the general पूर्णांकerface क्रम data transfer from twsi devices.
 * One vestige of its क्रमmer role is that it recognizes a device
 * QIB_TWSI_NO_DEV and करोes the correct operation क्रम the legacy part,
 * which responded to all TWSI device codes, पूर्णांकerpreting them as
 * address within device. On all other devices found on board handled by
 * this driver, the device is followed by a one-byte "address" which selects
 * the "register" or "offset" within the device from which data should
 * be पढ़ो.
 */
पूर्णांक qib_twsi_blk_rd(काष्ठा qib_devdata *dd, पूर्णांक dev, पूर्णांक addr,
		    व्योम *buffer, पूर्णांक len)
अणु
	पूर्णांक ret;
	u8 *bp = buffer;

	ret = 1;

	अगर (dev == QIB_TWSI_NO_DEV) अणु
		/* legacy not-really-I2C */
		addr = (addr << 1) | READ_CMD;
		ret = qib_twsi_wr(dd, addr, QIB_TWSI_START);
	पूर्ण अन्यथा अणु
		/* Actual I2C */
		ret = qib_twsi_wr(dd, dev | WRITE_CMD, QIB_TWSI_START);
		अगर (ret) अणु
			stop_cmd(dd);
			ret = 1;
			जाओ bail;
		पूर्ण
		/*
		 * SFF spec claims we करो _not_ stop after the addr
		 * but simply issue a start with the "read" dev-addr.
		 * Since we are implicitely रुकोing क्रम ACK here,
		 * we need t_buf (nominally 20uSec) beक्रमe that start,
		 * and cannot rely on the delay built in to the STOP
		 */
		ret = qib_twsi_wr(dd, addr, 0);
		udelay(TWSI_BUF_WAIT_USEC);

		अगर (ret) अणु
			qib_dev_err(dd,
				"Failed to write interface read addr %02X\n",
				addr);
			ret = 1;
			जाओ bail;
		पूर्ण
		ret = qib_twsi_wr(dd, dev | READ_CMD, QIB_TWSI_START);
	पूर्ण
	अगर (ret) अणु
		stop_cmd(dd);
		ret = 1;
		जाओ bail;
	पूर्ण

	/*
	 * block devices keeps घड़ीing data out as दीर्घ as we ack,
	 * स्वतःmatically incrementing the address. Some have "pages"
	 * whose boundaries will not be crossed, but the handling
	 * of these is left to the caller, who is in a better
	 * position to know.
	 */
	जबतक (len-- > 0) अणु
		/*
		 * Get and store data, sending ACK अगर length reमुख्यing,
		 * अन्यथा STOP
		 */
		*bp++ = rd_byte(dd, !len);
	पूर्ण

	ret = 0;

bail:
	वापस ret;
पूर्ण

/*
 * qib_twsi_blk_wr
 * Formerly called qib_eeprom_पूर्णांकernal_ग_लिखो, and only used क्रम eeprom,
 * but now the general पूर्णांकerface क्रम data transfer to twsi devices.
 * One vestige of its क्रमmer role is that it recognizes a device
 * QIB_TWSI_NO_DEV and करोes the correct operation क्रम the legacy part,
 * which responded to all TWSI device codes, पूर्णांकerpreting them as
 * address within device. On all other devices found on board handled by
 * this driver, the device is followed by a one-byte "address" which selects
 * the "register" or "offset" within the device to which data should
 * be written.
 */
पूर्णांक qib_twsi_blk_wr(काष्ठा qib_devdata *dd, पूर्णांक dev, पूर्णांक addr,
		    स्थिर व्योम *buffer, पूर्णांक len)
अणु
	पूर्णांक sub_len;
	स्थिर u8 *bp = buffer;
	पूर्णांक max_रुको_समय, i;
	पूर्णांक ret = 1;

	जबतक (len > 0) अणु
		अगर (dev == QIB_TWSI_NO_DEV) अणु
			अगर (qib_twsi_wr(dd, (addr << 1) | WRITE_CMD,
					QIB_TWSI_START)) अणु
				जाओ failed_ग_लिखो;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Real I2C */
			अगर (qib_twsi_wr(dd, dev | WRITE_CMD, QIB_TWSI_START))
				जाओ failed_ग_लिखो;
			ret = qib_twsi_wr(dd, addr, 0);
			अगर (ret) अणु
				qib_dev_err(dd,
					"Failed to write interface write addr %02X\n",
					addr);
				जाओ failed_ग_लिखो;
			पूर्ण
		पूर्ण

		sub_len = min(len, 4);
		addr += sub_len;
		len -= sub_len;

		क्रम (i = 0; i < sub_len; i++)
			अगर (qib_twsi_wr(dd, *bp++, 0))
				जाओ failed_ग_लिखो;

		stop_cmd(dd);

		/*
		 * Wait क्रम ग_लिखो complete by रुकोing क्रम a successful
		 * पढ़ो (the chip replies with a zero after the ग_लिखो
		 * cmd completes, and beक्रमe it ग_लिखोs to the eeprom.
		 * The startcmd क्रम the पढ़ो will fail the ack until
		 * the ग_लिखोs have completed.   We करो this अंतरभूत to aव्योम
		 * the debug prपूर्णांकs that are in the real पढ़ो routine
		 * अगर the startcmd fails.
		 * We also use the proper device address, so it करोesn't matter
		 * whether we have real eeprom_dev. Legacy likes any address.
		 */
		max_रुको_समय = 100;
		जबतक (qib_twsi_wr(dd, dev | READ_CMD, QIB_TWSI_START)) अणु
			stop_cmd(dd);
			अगर (!--max_रुको_समय)
				जाओ failed_ग_लिखो;
		पूर्ण
		/* now पढ़ो (and ignore) the resulting byte */
		rd_byte(dd, 1);
	पूर्ण

	ret = 0;
	जाओ bail;

failed_ग_लिखो:
	stop_cmd(dd);
	ret = 1;

bail:
	वापस ret;
पूर्ण
