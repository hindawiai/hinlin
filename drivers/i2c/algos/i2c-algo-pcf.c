<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c-algo-pcf.c i2c driver algorithms क्रम PCF8584 adapters
 *
 *   Copyright (C) 1995-1997 Simon G. Vogl
 *		   1998-2000 Hans Berglund
 *
 * With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and
 * Froकरो Looijaard <froकरोl@dds.nl>, and also from Martin Bailey
 * <mbailey@littlefeet-inc.com>
 *
 * Partially reग_लिखोn by Oleg I. Vकरोvikin <vकरोvikin@jscc.ru> to handle multiple
 * messages, proper stop/repstart संकेतing during receive, added detect code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-pcf.h>
#समावेश "i2c-algo-pcf.h"


#घोषणा DEB2(x) अगर (i2c_debug >= 2) x
#घोषणा DEB3(x) अगर (i2c_debug >= 3) x /* prपूर्णांक several statistical values */
#घोषणा DEBPROTO(x) अगर (i2c_debug >= 9) x;
	/* debug the protocol by showing transferred bits */
#घोषणा DEF_TIMEOUT 16

/*
 * module parameters:
 */
अटल पूर्णांक i2c_debug;

/* setting states on the bus with the right timing: */

#घोषणा set_pcf(adap, ctl, val) adap->setpcf(adap->data, ctl, val)
#घोषणा get_pcf(adap, ctl) adap->getpcf(adap->data, ctl)
#घोषणा get_own(adap) adap->getown(adap->data)
#घोषणा get_घड़ी(adap) adap->अ_लोlock(adap->data)
#घोषणा i2c_outb(adap, val) adap->setpcf(adap->data, 0, val)
#घोषणा i2c_inb(adap) adap->getpcf(adap->data, 0)

/* other auxiliary functions */

अटल व्योम i2c_start(काष्ठा i2c_algo_pcf_data *adap)
अणु
	DEBPROTO(prपूर्णांकk(KERN_DEBUG "S "));
	set_pcf(adap, 1, I2C_PCF_START);
पूर्ण

अटल व्योम i2c_repstart(काष्ठा i2c_algo_pcf_data *adap)
अणु
	DEBPROTO(prपूर्णांकk(" Sr "));
	set_pcf(adap, 1, I2C_PCF_REPSTART);
पूर्ण

अटल व्योम i2c_stop(काष्ठा i2c_algo_pcf_data *adap)
अणु
	DEBPROTO(prपूर्णांकk("P\n"));
	set_pcf(adap, 1, I2C_PCF_STOP);
पूर्ण

अटल व्योम handle_lab(काष्ठा i2c_algo_pcf_data *adap, स्थिर पूर्णांक *status)
अणु
	DEB2(prपूर्णांकk(KERN_INFO
		"i2c-algo-pcf.o: lost arbitration (CSR 0x%02x)\n",
		*status));
	/*
	 * Cleanup from LAB -- reset and enable ESO.
	 * This resets the PCF8584; since we've lost the bus, no
	 * further attempts should be made by callers to clean up
	 * (no i2c_stop() etc.)
	 */
	set_pcf(adap, 1, I2C_PCF_PIN);
	set_pcf(adap, 1, I2C_PCF_ESO);
	/*
	 * We छोड़ो क्रम a समय period sufficient क्रम any running
	 * I2C transaction to complete -- the arbitration logic won't
	 * work properly until the next START is seen.
	 * It is assumed the bus driver or client has set a proper value.
	 *
	 * REVISIT: should probably use msleep instead of mdelay अगर we
	 * know we can sleep.
	 */
	अगर (adap->lab_mdelay)
		mdelay(adap->lab_mdelay);

	DEB2(prपूर्णांकk(KERN_INFO
		"i2c-algo-pcf.o: reset LAB condition (CSR 0x%02x)\n",
		get_pcf(adap, 1)));
पूर्ण

अटल पूर्णांक रुको_क्रम_bb(काष्ठा i2c_algo_pcf_data *adap)
अणु

	पूर्णांक समयout = DEF_TIMEOUT;
	पूर्णांक status;

	status = get_pcf(adap, 1);

	जबतक (!(status & I2C_PCF_BB) && --समयout) अणु
		udelay(100); /* रुको क्रम 100 us */
		status = get_pcf(adap, 1);
	पूर्ण

	अगर (समयout == 0) अणु
		prपूर्णांकk(KERN_ERR "Timeout waiting for Bus Busy\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_क्रम_pin(काष्ठा i2c_algo_pcf_data *adap, पूर्णांक *status)
अणु

	पूर्णांक समयout = DEF_TIMEOUT;

	*status = get_pcf(adap, 1);

	जबतक ((*status & I2C_PCF_PIN) && --समयout) अणु
		adap->रुकोक्रमpin(adap->data);
		*status = get_pcf(adap, 1);
	पूर्ण
	अगर (*status & I2C_PCF_LAB) अणु
		handle_lab(adap, status);
		वापस -EINTR;
	पूर्ण

	अगर (समयout == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/*
 * This should perक्रमm the 'PCF8584 initialization sequence' as described
 * in the Philips IC12 data book (1995, Aug 29).
 * There should be a 30 घड़ी cycle रुको after reset, I assume this
 * has been fulfilled.
 * There should be a delay at the end equal to the दीर्घest I2C message
 * to synchronize the BB-bit (in multimaster प्रणालीs). How दीर्घ is
 * this? I assume 1 second is always दीर्घ enough.
 *
 * vकरोvikin: added detect code क्रम PCF8584
 */
अटल पूर्णांक pcf_init_8584 (काष्ठा i2c_algo_pcf_data *adap)
अणु
	अचिन्हित अक्षर temp;

	DEB3(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: PCF state 0x%02x\n",
				get_pcf(adap, 1)));

	/* S1=0x80: S0 selected, serial पूर्णांकerface off */
	set_pcf(adap, 1, I2C_PCF_PIN);
	/*
	 * check to see S1 now used as R/W ctrl -
	 * PCF8584 करोes that when ESO is zero
	 */
	अगर (((temp = get_pcf(adap, 1)) & 0x7f) != (0)) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: PCF detection failed -- can't select S0 (0x%02x).\n", temp));
		वापस -ENXIO; /* definitely not PCF8584 */
	पूर्ण

	/* load own address in S0, effective address is (own << 1) */
	i2c_outb(adap, get_own(adap));
	/* check it's really written */
	अगर ((temp = i2c_inb(adap)) != get_own(adap)) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: PCF detection failed -- can't set S0 (0x%02x).\n", temp));
		वापस -ENXIO;
	पूर्ण

	/* S1=0xA0, next byte in S2 */
	set_pcf(adap, 1, I2C_PCF_PIN | I2C_PCF_ES1);
	/* check to see S2 now selected */
	अगर (((temp = get_pcf(adap, 1)) & 0x7f) != I2C_PCF_ES1) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: PCF detection failed -- can't select S2 (0x%02x).\n", temp));
		वापस -ENXIO;
	पूर्ण

	/* load घड़ी रेजिस्टर S2 */
	i2c_outb(adap, get_घड़ी(adap));
	/* check it's really written, the only 5 lowest bits करोes matter */
	अगर (((temp = i2c_inb(adap)) & 0x1f) != get_घड़ी(adap)) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: PCF detection failed -- can't set S2 (0x%02x).\n", temp));
		वापस -ENXIO;
	पूर्ण

	/* Enable serial पूर्णांकerface, idle, S0 selected */
	set_pcf(adap, 1, I2C_PCF_IDLE);

	/* check to see PCF is really idled and we can access status रेजिस्टर */
	अगर ((temp = get_pcf(adap, 1)) != (I2C_PCF_PIN | I2C_PCF_BB)) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: PCF detection failed -- can't select S1` (0x%02x).\n", temp));
		वापस -ENXIO;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: detected and initialized PCF8584.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcf_sendbytes(काष्ठा i2c_adapter *i2c_adap, स्थिर अक्षर *buf,
			 पूर्णांक count, पूर्णांक last)
अणु
	काष्ठा i2c_algo_pcf_data *adap = i2c_adap->algo_data;
	पूर्णांक wrcount, status, समयout;

	क्रम (wrcount=0; wrcount<count; ++wrcount) अणु
		DEB2(dev_dbg(&i2c_adap->dev, "i2c_write: writing %2.2X\n",
				buf[wrcount] & 0xff));
		i2c_outb(adap, buf[wrcount]);
		समयout = रुको_क्रम_pin(adap, &status);
		अगर (समयout) अणु
			अगर (समयout == -EINTR)
				वापस -EINTR; /* arbitration lost */

			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_write: error - timeout.\n");
			वापस -EREMOTEIO; /* got a better one ?? */
		पूर्ण
		अगर (status & I2C_PCF_LRB) अणु
			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_write: error - no ack.\n");
			वापस -EREMOTEIO; /* got a better one ?? */
		पूर्ण
	पूर्ण
	अगर (last)
		i2c_stop(adap);
	अन्यथा
		i2c_repstart(adap);

	वापस wrcount;
पूर्ण

अटल पूर्णांक pcf_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap, अक्षर *buf,
			 पूर्णांक count, पूर्णांक last)
अणु
	पूर्णांक i, status;
	काष्ठा i2c_algo_pcf_data *adap = i2c_adap->algo_data;
	पूर्णांक wfp;

	/* increment number of bytes to पढ़ो by one -- पढ़ो dummy byte */
	क्रम (i = 0; i <= count; i++) अणु

		अगर ((wfp = रुको_क्रम_pin(adap, &status))) अणु
			अगर (wfp == -EINTR)
				वापस -EINTR; /* arbitration lost */

			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "pcf_readbytes timed out.\n");
			वापस -1;
		पूर्ण

		अगर ((status & I2C_PCF_LRB) && (i != count)) अणु
			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_read: i2c_inb, No ack.\n");
			वापस -1;
		पूर्ण

		अगर (i == count - 1) अणु
			set_pcf(adap, 1, I2C_PCF_ESO);
		पूर्ण अन्यथा अगर (i == count) अणु
			अगर (last)
				i2c_stop(adap);
			अन्यथा
				i2c_repstart(adap);
		पूर्ण

		अगर (i)
			buf[i - 1] = i2c_inb(adap);
		अन्यथा
			i2c_inb(adap); /* dummy पढ़ो */
	पूर्ण

	वापस i - 1;
पूर्ण


अटल पूर्णांक pcf_करोAddress(काष्ठा i2c_algo_pcf_data *adap,
			 काष्ठा i2c_msg *msg)
अणु
	अचिन्हित अक्षर addr = i2c_8bit_addr_from_msg(msg);

	अगर (msg->flags & I2C_M_REV_सूची_ADDR)
		addr ^= 1;
	i2c_outb(adap, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf_xfer(काष्ठा i2c_adapter *i2c_adap,
		    काष्ठा i2c_msg *msgs,
		    पूर्णांक num)
अणु
	काष्ठा i2c_algo_pcf_data *adap = i2c_adap->algo_data;
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i;
	पूर्णांक ret=0, समयout, status;

	अगर (adap->xfer_begin)
		adap->xfer_begin(adap->data);

	/* Check क्रम bus busy */
	समयout = रुको_क्रम_bb(adap);
	अगर (समयout) अणु
		DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: "
			    "Timeout waiting for BB in pcf_xfer\n");)
		i = -EIO;
		जाओ out;
	पूर्ण

	क्रम (i = 0;ret >= 0 && i < num; i++) अणु
		pmsg = &msgs[i];

		DEB2(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: Doing %s %d bytes to 0x%02x - %d of %d messages\n",
		     pmsg->flags & I2C_M_RD ? "read" : "write",
		     pmsg->len, pmsg->addr, i + 1, num);)

		ret = pcf_करोAddress(adap, pmsg);

		/* Send START */
		अगर (i == 0)
			i2c_start(adap);

		/* Wait क्रम PIN (pending पूर्णांकerrupt NOT) */
		समयout = रुको_क्रम_pin(adap, &status);
		अगर (समयout) अणु
			अगर (समयout == -EINTR) अणु
				/* arbitration lost */
				i = -EINTR;
				जाओ out;
			पूर्ण
			i2c_stop(adap);
			DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: Timeout waiting "
				    "for PIN(1) in pcf_xfer\n");)
			i = -EREMOTEIO;
			जाओ out;
		पूर्ण

		/* Check LRB (last rcvd bit - slave ack) */
		अगर (status & I2C_PCF_LRB) अणु
			i2c_stop(adap);
			DEB2(prपूर्णांकk(KERN_ERR "i2c-algo-pcf.o: No LRB(1) in pcf_xfer\n");)
			i = -EREMOTEIO;
			जाओ out;
		पूर्ण

		DEB3(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: Msg %d, addr=0x%x, flags=0x%x, len=%d\n",
			    i, msgs[i].addr, msgs[i].flags, msgs[i].len);)

		अगर (pmsg->flags & I2C_M_RD) अणु
			ret = pcf_पढ़ोbytes(i2c_adap, pmsg->buf, pmsg->len,
					    (i + 1 == num));

			अगर (ret != pmsg->len) अणु
				DEB2(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: fail: "
					    "only read %d bytes.\n",ret));
			पूर्ण अन्यथा अणु
				DEB2(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: read %d bytes.\n",ret));
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = pcf_sendbytes(i2c_adap, pmsg->buf, pmsg->len,
					    (i + 1 == num));

			अगर (ret != pmsg->len) अणु
				DEB2(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: fail: "
					    "only wrote %d bytes.\n",ret));
			पूर्ण अन्यथा अणु
				DEB2(prपूर्णांकk(KERN_DEBUG "i2c-algo-pcf.o: wrote %d bytes.\n",ret));
			पूर्ण
		पूर्ण
	पूर्ण

out:
	अगर (adap->xfer_end)
		adap->xfer_end(adap->data);
	वापस i;
पूर्ण

अटल u32 pcf_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

/* exported algorithm data: */
अटल स्थिर काष्ठा i2c_algorithm pcf_algo = अणु
	.master_xfer	= pcf_xfer,
	.functionality	= pcf_func,
पूर्ण;

/*
 * रेजिस्टरing functions to load algorithms at runसमय
 */
पूर्णांक i2c_pcf_add_bus(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_algo_pcf_data *pcf_adap = adap->algo_data;
	पूर्णांक rval;

	DEB2(dev_dbg(&adap->dev, "hw routines registered.\n"));

	/* रेजिस्टर new adapter to i2c module... */
	adap->algo = &pcf_algo;

	अगर ((rval = pcf_init_8584(pcf_adap)))
		वापस rval;

	rval = i2c_add_adapter(adap);

	वापस rval;
पूर्ण
EXPORT_SYMBOL(i2c_pcf_add_bus);

MODULE_AUTHOR("Hans Berglund <hb@spacetec.no>");
MODULE_DESCRIPTION("I2C-Bus PCF8584 algorithm");
MODULE_LICENSE("GPL");

module_param(i2c_debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(i2c_debug,
	"debug level - 0 off; 1 normal; 2,3 more verbose; 9 pcf-protocol");
