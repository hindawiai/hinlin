<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i2c-algo-bit.c: i2c driver algorithms क्रम bit-shअगरt adapters
 *
 *   Copyright (C) 1995-2000 Simon G. Vogl
 *
 * With some changes from Froकरो Looijaard <froकरोl@dds.nl>, Kyथघsti Mथअlkki
 * <kmalkki@cc.hut.fi> and Jean Delvare <jdelvare@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>


/* ----- global defines ----------------------------------------------- */

#अगर_घोषित DEBUG
#घोषणा bit_dbg(level, dev, क्रमmat, args...) \
	करो अणु \
		अगर (i2c_debug >= level) \
			dev_dbg(dev, क्रमmat, ##args); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा bit_dbg(level, dev, क्रमmat, args...) \
	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

/* ----- global variables ---------------------------------------------	*/

अटल पूर्णांक bit_test;	/* see अगर the line-setting functions work	*/
module_param(bit_test, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(bit_test, "lines testing - 0 off; 1 report; 2 fail if stuck");

#अगर_घोषित DEBUG
अटल पूर्णांक i2c_debug = 1;
module_param(i2c_debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(i2c_debug,
		 "debug level - 0 off; 1 normal; 2 verbose; 3 very verbose");
#पूर्ण_अगर

/* --- setting states on the bus with the right timing: ---------------	*/

#घोषणा setsda(adap, val)	adap->setsda(adap->data, val)
#घोषणा setscl(adap, val)	adap->setscl(adap->data, val)
#घोषणा माला_लोda(adap)		adap->माला_लोda(adap->data)
#घोषणा माला_लोcl(adap)		adap->माला_लोcl(adap->data)

अटल अंतरभूत व्योम sdalo(काष्ठा i2c_algo_bit_data *adap)
अणु
	setsda(adap, 0);
	udelay((adap->udelay + 1) / 2);
पूर्ण

अटल अंतरभूत व्योम sdahi(काष्ठा i2c_algo_bit_data *adap)
अणु
	setsda(adap, 1);
	udelay((adap->udelay + 1) / 2);
पूर्ण

अटल अंतरभूत व्योम scllo(काष्ठा i2c_algo_bit_data *adap)
अणु
	setscl(adap, 0);
	udelay(adap->udelay / 2);
पूर्ण

/*
 * Raise scl line, and करो checking क्रम delays. This is necessary क्रम slower
 * devices.
 */
अटल पूर्णांक sclhi(काष्ठा i2c_algo_bit_data *adap)
अणु
	अचिन्हित दीर्घ start;

	setscl(adap, 1);

	/* Not all adapters have scl sense line... */
	अगर (!adap->माला_लोcl)
		जाओ करोne;

	start = jअगरfies;
	जबतक (!माला_लोcl(adap)) अणु
		/* This hw knows how to पढ़ो the घड़ी line, so we रुको
		 * until it actually माला_लो high.  This is safer as some
		 * chips may hold it low ("clock stretching") जबतक they
		 * are processing data पूर्णांकernally.
		 */
		अगर (समय_after(jअगरfies, start + adap->समयout)) अणु
			/* Test one last समय, as we may have been preempted
			 * between last check and समयout test.
			 */
			अगर (माला_लोcl(adap))
				अवरोध;
			वापस -ETIMEDOUT;
		पूर्ण
		cpu_relax();
	पूर्ण
#अगर_घोषित DEBUG
	अगर (jअगरfies != start && i2c_debug >= 3)
		pr_debug("i2c-algo-bit: needed %ld jiffies for SCL to go high\n",
			 jअगरfies - start);
#पूर्ण_अगर

करोne:
	udelay(adap->udelay);
	वापस 0;
पूर्ण


/* --- other auxiliary functions --------------------------------------	*/
अटल व्योम i2c_start(काष्ठा i2c_algo_bit_data *adap)
अणु
	/* निश्चित: scl, sda are high */
	setsda(adap, 0);
	udelay(adap->udelay);
	scllo(adap);
पूर्ण

अटल व्योम i2c_repstart(काष्ठा i2c_algo_bit_data *adap)
अणु
	/* निश्चित: scl is low */
	sdahi(adap);
	sclhi(adap);
	setsda(adap, 0);
	udelay(adap->udelay);
	scllo(adap);
पूर्ण


अटल व्योम i2c_stop(काष्ठा i2c_algo_bit_data *adap)
अणु
	/* निश्चित: scl is low */
	sdalo(adap);
	sclhi(adap);
	setsda(adap, 1);
	udelay(adap->udelay);
पूर्ण



/* send a byte without start cond., look क्रम arbitration,
   check ackn. from slave */
/* वापसs:
 * 1 अगर the device acknowledged
 * 0 अगर the device did not ack
 * -ETIMEDOUT अगर an error occurred (जबतक raising the scl line)
 */
अटल पूर्णांक i2c_outb(काष्ठा i2c_adapter *i2c_adap, अचिन्हित अक्षर c)
अणु
	पूर्णांक i;
	पूर्णांक sb;
	पूर्णांक ack;
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;

	/* निश्चित: scl is low */
	क्रम (i = 7; i >= 0; i--) अणु
		sb = (c >> i) & 1;
		setsda(adap, sb);
		udelay((adap->udelay + 1) / 2);
		अगर (sclhi(adap) < 0) अणु /* समयd out */
			bit_dbg(1, &i2c_adap->dev,
				"i2c_outb: 0x%02x, timeout at bit #%d\n",
				(पूर्णांक)c, i);
			वापस -ETIMEDOUT;
		पूर्ण
		/* FIXME करो arbitration here:
		 * अगर (sb && !माला_लोda(adap)) -> ouch! Get out of here.
		 *
		 * Report a unique code, so higher level code can retry
		 * the whole (combined) message and *NOT* issue STOP.
		 */
		scllo(adap);
	पूर्ण
	sdahi(adap);
	अगर (sclhi(adap) < 0) अणु /* समयout */
		bit_dbg(1, &i2c_adap->dev,
			"i2c_outb: 0x%02x, timeout at ack\n", (पूर्णांक)c);
		वापस -ETIMEDOUT;
	पूर्ण

	/* पढ़ो ack: SDA should be pulled करोwn by slave, or it may
	 * NAK (usually to report problems with the data we wrote).
	 */
	ack = !माला_लोda(adap);    /* ack: sda is pulled low -> success */
	bit_dbg(2, &i2c_adap->dev, "i2c_outb: 0x%02x %s\n", (पूर्णांक)c,
		ack ? "A" : "NA");

	scllo(adap);
	वापस ack;
	/* निश्चित: scl is low (sda undef) */
पूर्ण


अटल पूर्णांक i2c_inb(काष्ठा i2c_adapter *i2c_adap)
अणु
	/* पढ़ो byte via i2c port, without start/stop sequence	*/
	/* acknowledge is sent in i2c_पढ़ो.			*/
	पूर्णांक i;
	अचिन्हित अक्षर indata = 0;
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;

	/* निश्चित: scl is low */
	sdahi(adap);
	क्रम (i = 0; i < 8; i++) अणु
		अगर (sclhi(adap) < 0) अणु /* समयout */
			bit_dbg(1, &i2c_adap->dev,
				"i2c_inb: timeout at bit #%d\n",
				7 - i);
			वापस -ETIMEDOUT;
		पूर्ण
		indata *= 2;
		अगर (माला_लोda(adap))
			indata |= 0x01;
		setscl(adap, 0);
		udelay(i == 7 ? adap->udelay / 2 : adap->udelay);
	पूर्ण
	/* निश्चित: scl is low */
	वापस indata;
पूर्ण

/*
 * Sanity check क्रम the adapter hardware - check the reaction of
 * the bus lines only अगर it seems to be idle.
 */
अटल पूर्णांक test_bus(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;
	स्थिर अक्षर *name = i2c_adap->name;
	पूर्णांक scl, sda, ret;

	अगर (adap->pre_xfer) अणु
		ret = adap->pre_xfer(i2c_adap);
		अगर (ret < 0)
			वापस -ENODEV;
	पूर्ण

	अगर (adap->माला_लोcl == शून्य)
		pr_info("%s: Testing SDA only, SCL is not readable\n", name);

	sda = माला_लोda(adap);
	scl = (adap->माला_लोcl == शून्य) ? 1 : माला_लोcl(adap);
	अगर (!scl || !sda) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: bus seems to be busy (scl=%d, sda=%d)\n",
		       name, scl, sda);
		जाओ bailout;
	पूर्ण

	sdalo(adap);
	sda = माला_लोda(adap);
	scl = (adap->माला_लोcl == शून्य) ? 1 : माला_लोcl(adap);
	अगर (sda) अणु
		prपूर्णांकk(KERN_WARNING "%s: SDA stuck high!\n", name);
		जाओ bailout;
	पूर्ण
	अगर (!scl) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: SCL unexpected low while pulling SDA low!\n",
		       name);
		जाओ bailout;
	पूर्ण

	sdahi(adap);
	sda = माला_लोda(adap);
	scl = (adap->माला_लोcl == शून्य) ? 1 : माला_लोcl(adap);
	अगर (!sda) अणु
		prपूर्णांकk(KERN_WARNING "%s: SDA stuck low!\n", name);
		जाओ bailout;
	पूर्ण
	अगर (!scl) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: SCL unexpected low while pulling SDA high!\n",
		       name);
		जाओ bailout;
	पूर्ण

	scllo(adap);
	sda = माला_लोda(adap);
	scl = (adap->माला_लोcl == शून्य) ? 0 : माला_लोcl(adap);
	अगर (scl) अणु
		prपूर्णांकk(KERN_WARNING "%s: SCL stuck high!\n", name);
		जाओ bailout;
	पूर्ण
	अगर (!sda) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: SDA unexpected low while pulling SCL low!\n",
		       name);
		जाओ bailout;
	पूर्ण

	sclhi(adap);
	sda = माला_लोda(adap);
	scl = (adap->माला_लोcl == शून्य) ? 1 : माला_लोcl(adap);
	अगर (!scl) अणु
		prपूर्णांकk(KERN_WARNING "%s: SCL stuck low!\n", name);
		जाओ bailout;
	पूर्ण
	अगर (!sda) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: SDA unexpected low while pulling SCL high!\n",
		       name);
		जाओ bailout;
	पूर्ण

	अगर (adap->post_xfer)
		adap->post_xfer(i2c_adap);

	pr_info("%s: Test OK\n", name);
	वापस 0;
bailout:
	sdahi(adap);
	sclhi(adap);

	अगर (adap->post_xfer)
		adap->post_xfer(i2c_adap);

	वापस -ENODEV;
पूर्ण

/* ----- Utility functions
 */

/* try_address tries to contact a chip क्रम a number of
 * बार beक्रमe it gives up.
 * वापस values:
 * 1 chip answered
 * 0 chip did not answer
 * -x transmission error
 */
अटल पूर्णांक try_address(काष्ठा i2c_adapter *i2c_adap,
		       अचिन्हित अक्षर addr, पूर्णांक retries)
अणु
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i <= retries; i++) अणु
		ret = i2c_outb(i2c_adap, addr);
		अगर (ret == 1 || i == retries)
			अवरोध;
		bit_dbg(3, &i2c_adap->dev, "emitting stop condition\n");
		i2c_stop(adap);
		udelay(adap->udelay);
		yield();
		bit_dbg(3, &i2c_adap->dev, "emitting start condition\n");
		i2c_start(adap);
	पूर्ण
	अगर (i && ret)
		bit_dbg(1, &i2c_adap->dev,
			"Used %d tries to %s client at 0x%02x: %s\n", i + 1,
			addr & 1 ? "read from" : "write to", addr >> 1,
			ret == 1 ? "success" : "failed, timeout?");
	वापस ret;
पूर्ण

अटल पूर्णांक sendbytes(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msg)
अणु
	स्थिर अचिन्हित अक्षर *temp = msg->buf;
	पूर्णांक count = msg->len;
	अचिन्हित लघु nak_ok = msg->flags & I2C_M_IGNORE_NAK;
	पूर्णांक retval;
	पूर्णांक wrcount = 0;

	जबतक (count > 0) अणु
		retval = i2c_outb(i2c_adap, *temp);

		/* OK/ACK; or ignored NAK */
		अगर ((retval > 0) || (nak_ok && (retval == 0))) अणु
			count--;
			temp++;
			wrcount++;

		/* A slave NAKing the master means the slave didn't like
		 * something about the data it saw.  For example, maybe
		 * the SMBus PEC was wrong.
		 */
		पूर्ण अन्यथा अगर (retval == 0) अणु
			dev_err(&i2c_adap->dev, "sendbytes: NAK bailout.\n");
			वापस -EIO;

		/* Timeout; or (someday) lost arbitration
		 *
		 * FIXME Lost ARB implies retrying the transaction from
		 * the first message, after the "winning" master issues
		 * its STOP.  As a rule, upper layer code has no reason
		 * to know or care about this ... it is *NOT* an error.
		 */
		पूर्ण अन्यथा अणु
			dev_err(&i2c_adap->dev, "sendbytes: error %d\n",
					retval);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस wrcount;
पूर्ण

अटल पूर्णांक acknak(काष्ठा i2c_adapter *i2c_adap, पूर्णांक is_ack)
अणु
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;

	/* निश्चित: sda is high */
	अगर (is_ack)		/* send ack */
		setsda(adap, 0);
	udelay((adap->udelay + 1) / 2);
	अगर (sclhi(adap) < 0) अणु	/* समयout */
		dev_err(&i2c_adap->dev, "readbytes: ack/nak timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण
	scllo(adap);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक inval;
	पूर्णांक rdcount = 0;	/* counts bytes पढ़ो */
	अचिन्हित अक्षर *temp = msg->buf;
	पूर्णांक count = msg->len;
	स्थिर अचिन्हित flags = msg->flags;

	जबतक (count > 0) अणु
		inval = i2c_inb(i2c_adap);
		अगर (inval >= 0) अणु
			*temp = inval;
			rdcount++;
		पूर्ण अन्यथा अणु   /* पढ़ो समयd out */
			अवरोध;
		पूर्ण

		temp++;
		count--;

		/* Some SMBus transactions require that we receive the
		   transaction length as the first पढ़ो byte. */
		अगर (rdcount == 1 && (flags & I2C_M_RECV_LEN)) अणु
			अगर (inval <= 0 || inval > I2C_SMBUS_BLOCK_MAX) अणु
				अगर (!(flags & I2C_M_NO_RD_ACK))
					acknak(i2c_adap, 0);
				dev_err(&i2c_adap->dev,
					"readbytes: invalid block length (%d)\n",
					inval);
				वापस -EPROTO;
			पूर्ण
			/* The original count value accounts क्रम the extra
			   bytes, that is, either 1 क्रम a regular transaction,
			   or 2 क्रम a PEC transaction. */
			count += inval;
			msg->len += inval;
		पूर्ण

		bit_dbg(2, &i2c_adap->dev, "readbytes: 0x%02x %s\n",
			inval,
			(flags & I2C_M_NO_RD_ACK)
				? "(no ack/nak)"
				: (count ? "A" : "NA"));

		अगर (!(flags & I2C_M_NO_RD_ACK)) अणु
			inval = acknak(i2c_adap, count);
			अगर (inval < 0)
				वापस inval;
		पूर्ण
	पूर्ण
	वापस rdcount;
पूर्ण

/* करोAddress initiates the transfer by generating the start condition (in
 * try_address) and transmits the address in the necessary क्रमmat to handle
 * पढ़ोs, ग_लिखोs as well as 10bit-addresses.
 * वापसs:
 *  0 everything went okay, the chip ack'ed, or IGNORE_NAK flag was set
 * -x an error occurred (like: -ENXIO अगर the device did not answer, or
 *	-ETIMEDOUT, क्रम example अगर the lines are stuck...)
 */
अटल पूर्णांक bit_करोAddress(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msg)
अणु
	अचिन्हित लघु flags = msg->flags;
	अचिन्हित लघु nak_ok = msg->flags & I2C_M_IGNORE_NAK;
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;

	अचिन्हित अक्षर addr;
	पूर्णांक ret, retries;

	retries = nak_ok ? 0 : i2c_adap->retries;

	अगर (flags & I2C_M_TEN) अणु
		/* a ten bit address */
		addr = 0xf0 | ((msg->addr >> 7) & 0x06);
		bit_dbg(2, &i2c_adap->dev, "addr0: %d\n", addr);
		/* try extended address code...*/
		ret = try_address(i2c_adap, addr, retries);
		अगर ((ret != 1) && !nak_ok)  अणु
			dev_err(&i2c_adap->dev,
				"died at extended address code\n");
			वापस -ENXIO;
		पूर्ण
		/* the reमुख्यing 8 bit address */
		ret = i2c_outb(i2c_adap, msg->addr & 0xff);
		अगर ((ret != 1) && !nak_ok) अणु
			/* the chip did not ack / xmission error occurred */
			dev_err(&i2c_adap->dev, "died at 2nd address code\n");
			वापस -ENXIO;
		पूर्ण
		अगर (flags & I2C_M_RD) अणु
			bit_dbg(3, &i2c_adap->dev,
				"emitting repeated start condition\n");
			i2c_repstart(adap);
			/* okay, now चयन पूर्णांकo पढ़ोing mode */
			addr |= 0x01;
			ret = try_address(i2c_adap, addr, retries);
			अगर ((ret != 1) && !nak_ok) अणु
				dev_err(&i2c_adap->dev,
					"died at repeated address code\n");
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु		/* normal 7bit address	*/
		addr = i2c_8bit_addr_from_msg(msg);
		अगर (flags & I2C_M_REV_सूची_ADDR)
			addr ^= 1;
		ret = try_address(i2c_adap, addr, retries);
		अगर ((ret != 1) && !nak_ok)
			वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bit_xfer(काष्ठा i2c_adapter *i2c_adap,
		    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा i2c_msg *pmsg;
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;
	पूर्णांक i, ret;
	अचिन्हित लघु nak_ok;

	अगर (adap->pre_xfer) अणु
		ret = adap->pre_xfer(i2c_adap);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	bit_dbg(3, &i2c_adap->dev, "emitting start condition\n");
	i2c_start(adap);
	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];
		nak_ok = pmsg->flags & I2C_M_IGNORE_NAK;
		अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
			अगर (i) अणु
				अगर (msgs[i - 1].flags & I2C_M_STOP) अणु
					bit_dbg(3, &i2c_adap->dev,
						"emitting enforced stop/start condition\n");
					i2c_stop(adap);
					i2c_start(adap);
				पूर्ण अन्यथा अणु
					bit_dbg(3, &i2c_adap->dev,
						"emitting repeated start condition\n");
					i2c_repstart(adap);
				पूर्ण
			पूर्ण
			ret = bit_करोAddress(i2c_adap, pmsg);
			अगर ((ret != 0) && !nak_ok) अणु
				bit_dbg(1, &i2c_adap->dev,
					"NAK from device addr 0x%02x msg #%d\n",
					msgs[i].addr, i);
				जाओ bailout;
			पूर्ण
		पूर्ण
		अगर (pmsg->flags & I2C_M_RD) अणु
			/* पढ़ो bytes पूर्णांकo buffer*/
			ret = पढ़ोbytes(i2c_adap, pmsg);
			अगर (ret >= 1)
				bit_dbg(2, &i2c_adap->dev, "read %d byte%s\n",
					ret, ret == 1 ? "" : "s");
			अगर (ret < pmsg->len) अणु
				अगर (ret >= 0)
					ret = -EIO;
				जाओ bailout;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes from buffer */
			ret = sendbytes(i2c_adap, pmsg);
			अगर (ret >= 1)
				bit_dbg(2, &i2c_adap->dev, "wrote %d byte%s\n",
					ret, ret == 1 ? "" : "s");
			अगर (ret < pmsg->len) अणु
				अगर (ret >= 0)
					ret = -EIO;
				जाओ bailout;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = i;

bailout:
	bit_dbg(3, &i2c_adap->dev, "emitting stop condition\n");
	i2c_stop(adap);

	अगर (adap->post_xfer)
		adap->post_xfer(i2c_adap);
	वापस ret;
पूर्ण

/*
 * We prपूर्णांक a warning when we are not flagged to support atomic transfers but
 * will try anyhow. That's what the I2C core would do as well. Sadly, we can't
 * modअगरy the algorithm काष्ठा at probe समय because this काष्ठा is exported
 * 'const'.
 */
अटल पूर्णांक bit_xfer_atomic(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msgs[],
			   पूर्णांक num)
अणु
	काष्ठा i2c_algo_bit_data *adap = i2c_adap->algo_data;

	अगर (!adap->can_करो_atomic)
		dev_warn(&i2c_adap->dev, "not flagged for atomic transfers\n");

	वापस bit_xfer(i2c_adap, msgs, num);
पूर्ण

अटल u32 bit_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_NOSTART | I2C_FUNC_SMBUS_EMUL_ALL |
	       I2C_FUNC_10BIT_ADDR | I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण


/* -----exported algorithm data: -------------------------------------	*/

स्थिर काष्ठा i2c_algorithm i2c_bit_algo = अणु
	.master_xfer = bit_xfer,
	.master_xfer_atomic = bit_xfer_atomic,
	.functionality = bit_func,
पूर्ण;
EXPORT_SYMBOL(i2c_bit_algo);

अटल स्थिर काष्ठा i2c_adapter_quirks i2c_bit_quirk_no_clk_stretch = अणु
	.flags = I2C_AQ_NO_CLK_STRETCH,
पूर्ण;

/*
 * रेजिस्टरing functions to load algorithms at runसमय
 */
अटल पूर्णांक __i2c_bit_add_bus(काष्ठा i2c_adapter *adap,
			     पूर्णांक (*add_adapter)(काष्ठा i2c_adapter *))
अणु
	काष्ठा i2c_algo_bit_data *bit_adap = adap->algo_data;
	पूर्णांक ret;

	अगर (bit_test) अणु
		ret = test_bus(adap);
		अगर (bit_test >= 2 && ret < 0)
			वापस -ENODEV;
	पूर्ण

	/* रेजिस्टर new adapter to i2c module... */
	adap->algo = &i2c_bit_algo;
	adap->retries = 3;
	अगर (bit_adap->माला_लोcl == शून्य)
		adap->quirks = &i2c_bit_quirk_no_clk_stretch;

	/*
	 * We tried क्रमcing SCL/SDA to an initial state here. But that caused a
	 * regression, sadly. Check Bugzilla #200045 क्रम details.
	 */

	ret = add_adapter(adap);
	अगर (ret < 0)
		वापस ret;

	/* Complain अगर SCL can't be पढ़ो */
	अगर (bit_adap->माला_लोcl == शून्य) अणु
		dev_warn(&adap->dev, "Not I2C compliant: can't read SCL\n");
		dev_warn(&adap->dev, "Bus may be unreliable\n");
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक i2c_bit_add_bus(काष्ठा i2c_adapter *adap)
अणु
	वापस __i2c_bit_add_bus(adap, i2c_add_adapter);
पूर्ण
EXPORT_SYMBOL(i2c_bit_add_bus);

पूर्णांक i2c_bit_add_numbered_bus(काष्ठा i2c_adapter *adap)
अणु
	वापस __i2c_bit_add_bus(adap, i2c_add_numbered_adapter);
पूर्ण
EXPORT_SYMBOL(i2c_bit_add_numbered_bus);

MODULE_AUTHOR("Simon G. Vogl <simon@tk.uni-linz.ac.at>");
MODULE_DESCRIPTION("I2C-Bus bit-banging algorithm");
MODULE_LICENSE("GPL");
