<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv-i2c.c  --  all the i2c code is here

    bttv - Bt848 frame grabber driver

    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
			   & Marcus Metzler (mocm@thp.uni-koeln.de)
    (c) 1999-2003 Gerd Knorr <kraxel@bytesex.org>

    (c) 2005 Mauro Carvalho Chehab <mchehab@kernel.org>
	- Multituner support and i2c address binding


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश "bttvp.h"
#समावेश <media/v4l2-common.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक i2c_debug;
अटल पूर्णांक i2c_hw;
अटल पूर्णांक i2c_scan;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "configure i2c debug level");
module_param(i2c_hw,    पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_hw, "force use of hardware i2c support, instead of software bitbang");
module_param(i2c_scan,  पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan,"scan i2c bus at insmod time");

अटल अचिन्हित पूर्णांक i2c_udelay = 5;
module_param(i2c_udelay, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_udelay, "soft i2c delay at insmod time, in usecs (should be 5 or higher). Lower value means higher bus speed.");

/* ----------------------------------------------------------------------- */
/* I2C functions - bitbanging adapter (software i2c)                       */

अटल व्योम bttv_bit_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा bttv *btv = (काष्ठा bttv*)data;

	अगर (state)
		btv->i2c_state |= 0x02;
	अन्यथा
		btv->i2c_state &= ~0x02;
	btग_लिखो(btv->i2c_state, BT848_I2C);
	btपढ़ो(BT848_I2C);
पूर्ण

अटल व्योम bttv_bit_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा bttv *btv = (काष्ठा bttv*)data;

	अगर (state)
		btv->i2c_state |= 0x01;
	अन्यथा
		btv->i2c_state &= ~0x01;
	btग_लिखो(btv->i2c_state, BT848_I2C);
	btपढ़ो(BT848_I2C);
पूर्ण

अटल पूर्णांक bttv_bit_माला_लोcl(व्योम *data)
अणु
	काष्ठा bttv *btv = (काष्ठा bttv*)data;
	पूर्णांक state;

	state = btपढ़ो(BT848_I2C) & 0x02 ? 1 : 0;
	वापस state;
पूर्ण

अटल पूर्णांक bttv_bit_माला_लोda(व्योम *data)
अणु
	काष्ठा bttv *btv = (काष्ठा bttv*)data;
	पूर्णांक state;

	state = btपढ़ो(BT848_I2C) & 0x01;
	वापस state;
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data bttv_i2c_algo_bit_ढाँचा = अणु
	.setsda  = bttv_bit_setsda,
	.setscl  = bttv_bit_setscl,
	.माला_लोda  = bttv_bit_माला_लोda,
	.माला_लोcl  = bttv_bit_माला_लोcl,
	.udelay  = 16,
	.समयout = 200,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* I2C functions - hardware i2c                                            */

अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल पूर्णांक
bttv_i2c_रुको_करोne(काष्ठा bttv *btv)
अणु
	पूर्णांक rc = 0;

	/* समयout */
	अगर (रुको_event_पूर्णांकerruptible_समयout(btv->i2c_queue,
	    btv->i2c_करोne, msecs_to_jअगरfies(85)) == -ERESTARTSYS)
		rc = -EIO;

	अगर (btv->i2c_करोne & BT848_INT_RACK)
		rc = 1;
	btv->i2c_करोne = 0;
	वापस rc;
पूर्ण

#घोषणा I2C_HW (BT878_I2C_MODE  | BT848_I2C_SYNC |\
		BT848_I2C_SCL | BT848_I2C_SDA)

अटल पूर्णांक
bttv_i2c_sendbytes(काष्ठा bttv *btv, स्थिर काष्ठा i2c_msg *msg, पूर्णांक last)
अणु
	u32 xmit;
	पूर्णांक retval,cnt;

	/* sanity checks */
	अगर (0 == msg->len)
		वापस -EINVAL;

	/* start, address + first byte */
	xmit = (msg->addr << 25) | (msg->buf[0] << 16) | I2C_HW;
	अगर (msg->len > 1 || !last)
		xmit |= BT878_I2C_NOSTOP;
	btग_लिखो(xmit, BT848_I2C);
	retval = bttv_i2c_रुको_करोne(btv);
	अगर (retval < 0)
		जाओ err;
	अगर (retval == 0)
		जाओ eio;
	अगर (i2c_debug) अणु
		pr_cont(" <W %02x %02x", msg->addr << 1, msg->buf[0]);
	पूर्ण

	क्रम (cnt = 1; cnt < msg->len; cnt++ ) अणु
		/* following bytes */
		xmit = (msg->buf[cnt] << 24) | I2C_HW | BT878_I2C_NOSTART;
		अगर (cnt < msg->len-1 || !last)
			xmit |= BT878_I2C_NOSTOP;
		btग_लिखो(xmit, BT848_I2C);
		retval = bttv_i2c_रुको_करोne(btv);
		अगर (retval < 0)
			जाओ err;
		अगर (retval == 0)
			जाओ eio;
		अगर (i2c_debug)
			pr_cont(" %02x", msg->buf[cnt]);
	पूर्ण
	अगर (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
		pr_cont(">\n");
	वापस msg->len;

 eio:
	retval = -EIO;
 err:
	अगर (i2c_debug)
		pr_cont(" ERR: %d\n",retval);
	वापस retval;
पूर्ण

अटल पूर्णांक
bttv_i2c_पढ़ोbytes(काष्ठा bttv *btv, स्थिर काष्ठा i2c_msg *msg, पूर्णांक last)
अणु
	u32 xmit;
	u32 cnt;
	पूर्णांक retval;

	क्रम (cnt = 0; cnt < msg->len; cnt++) अणु
		xmit = (msg->addr << 25) | (1 << 24) | I2C_HW;
		अगर (cnt < msg->len-1)
			xmit |= BT848_I2C_W3B;
		अगर (cnt < msg->len-1 || !last)
			xmit |= BT878_I2C_NOSTOP;
		अगर (cnt)
			xmit |= BT878_I2C_NOSTART;

		अगर (i2c_debug) अणु
			अगर (!(xmit & BT878_I2C_NOSTART))
				pr_cont(" <R %02x", (msg->addr << 1) +1);
		पूर्ण

		btग_लिखो(xmit, BT848_I2C);
		retval = bttv_i2c_रुको_करोne(btv);
		अगर (retval < 0)
			जाओ err;
		अगर (retval == 0)
			जाओ eio;
		msg->buf[cnt] = ((u32)btपढ़ो(BT848_I2C) >> 8) & 0xff;
		अगर (i2c_debug) अणु
			pr_cont(" =%02x", msg->buf[cnt]);
		पूर्ण
		अगर (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
			pr_cont(" >\n");
	पूर्ण


	वापस msg->len;

 eio:
	retval = -EIO;
 err:
	अगर (i2c_debug)
		pr_cont(" ERR: %d\n",retval);
	वापस retval;
पूर्ण

अटल पूर्णांक bttv_i2c_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा v4l2_device *v4l2_dev = i2c_get_adapdata(i2c_adap);
	काष्ठा bttv *btv = to_bttv(v4l2_dev);
	पूर्णांक retval = 0;
	पूर्णांक i;

	अगर (i2c_debug)
		pr_debug("bt-i2c:");

	btग_लिखो(BT848_INT_I2CDONE|BT848_INT_RACK, BT848_INT_STAT);
	क्रम (i = 0 ; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो */
			retval = bttv_i2c_पढ़ोbytes(btv, &msgs[i], i+1 == num);
			अगर (retval < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* ग_लिखो */
			retval = bttv_i2c_sendbytes(btv, &msgs[i], i+1 == num);
			अगर (retval < 0)
				जाओ err;
		पूर्ण
	पूर्ण
	वापस num;

 err:
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm bttv_algo = अणु
	.master_xfer   = bttv_i2c_xfer,
	.functionality = functionality,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* I2C functions - common stuff                                            */

/* पढ़ो I2C */
पूर्णांक bttv_I2CRead(काष्ठा bttv *btv, अचिन्हित अक्षर addr, अक्षर *probe_क्रम)
अणु
	अचिन्हित अक्षर buffer = 0;

	अगर (0 != btv->i2c_rc)
		वापस -1;
	अगर (bttv_verbose && शून्य != probe_क्रम)
		pr_info("%d: i2c: checking for %s @ 0x%02x... ",
			btv->c.nr, probe_क्रम, addr);
	btv->i2c_client.addr = addr >> 1;
	अगर (1 != i2c_master_recv(&btv->i2c_client, &buffer, 1)) अणु
		अगर (शून्य != probe_क्रम) अणु
			अगर (bttv_verbose)
				pr_cont("not found\n");
		पूर्ण अन्यथा
			pr_warn("%d: i2c read 0x%x: error\n",
				btv->c.nr, addr);
		वापस -1;
	पूर्ण
	अगर (bttv_verbose && शून्य != probe_क्रम)
		pr_cont("found\n");
	वापस buffer;
पूर्ण

/* ग_लिखो I2C */
पूर्णांक bttv_I2CWrite(काष्ठा bttv *btv, अचिन्हित अक्षर addr, अचिन्हित अक्षर b1,
		    अचिन्हित अक्षर b2, पूर्णांक both)
अणु
	अचिन्हित अक्षर buffer[2];
	पूर्णांक bytes = both ? 2 : 1;

	अगर (0 != btv->i2c_rc)
		वापस -1;
	btv->i2c_client.addr = addr >> 1;
	buffer[0] = b1;
	buffer[1] = b2;
	अगर (bytes != i2c_master_send(&btv->i2c_client, buffer, bytes))
		वापस -1;
	वापस 0;
पूर्ण

/* पढ़ो EEPROM content */
व्योम bttv_पढ़ोee(काष्ठा bttv *btv, अचिन्हित अक्षर *eedata, पूर्णांक addr)
अणु
	स_रखो(eedata, 0, 256);
	अगर (0 != btv->i2c_rc)
		वापस;
	btv->i2c_client.addr = addr >> 1;
	tveeprom_पढ़ो(&btv->i2c_client, eedata, 256);
पूर्ण

अटल अक्षर *i2c_devs[128] = अणु
	[ 0x1c >> 1 ] = "lgdt330x",
	[ 0x30 >> 1 ] = "IR (hauppauge)",
	[ 0x80 >> 1 ] = "msp34xx",
	[ 0x86 >> 1 ] = "tda9887",
	[ 0xa0 >> 1 ] = "eeprom",
	[ 0xc0 >> 1 ] = "tuner (analog)",
	[ 0xc2 >> 1 ] = "tuner (analog)",
पूर्ण;

अटल व्योम करो_i2c_scan(अक्षर *name, काष्ठा i2c_client *c)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i,rc;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_devs); i++) अणु
		c->addr = i;
		rc = i2c_master_recv(c,&buf,0);
		अगर (rc < 0)
			जारी;
		pr_info("%s: i2c scan: found device @ 0x%x  [%s]\n",
			name, i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण
पूर्ण

/* init + रेजिस्टर i2c adapter */
पूर्णांक init_bttv_i2c(काष्ठा bttv *btv)
अणु
	strscpy(btv->i2c_client.name, "bttv internal", I2C_NAME_SIZE);

	अगर (i2c_hw)
		btv->use_i2c_hw = 1;
	अगर (btv->use_i2c_hw) अणु
		/* bt878 */
		strscpy(btv->c.i2c_adap.name, "bt878",
			माप(btv->c.i2c_adap.name));
		btv->c.i2c_adap.algo = &bttv_algo;
	पूर्ण अन्यथा अणु
		/* bt848 */
	/* Prevents usage of invalid delay values */
		अगर (i2c_udelay<5)
			i2c_udelay=5;

		strscpy(btv->c.i2c_adap.name, "bttv",
			माप(btv->c.i2c_adap.name));
		btv->i2c_algo = bttv_i2c_algo_bit_ढाँचा;
		btv->i2c_algo.udelay = i2c_udelay;
		btv->i2c_algo.data = btv;
		btv->c.i2c_adap.algo_data = &btv->i2c_algo;
	पूर्ण
	btv->c.i2c_adap.owner = THIS_MODULE;

	btv->c.i2c_adap.dev.parent = &btv->c.pci->dev;
	snम_लिखो(btv->c.i2c_adap.name, माप(btv->c.i2c_adap.name),
		 "bt%d #%d [%s]", btv->id, btv->c.nr,
		 btv->use_i2c_hw ? "hw" : "sw");

	i2c_set_adapdata(&btv->c.i2c_adap, &btv->c.v4l2_dev);
	btv->i2c_client.adapter = &btv->c.i2c_adap;


	अगर (btv->use_i2c_hw) अणु
		btv->i2c_rc = i2c_add_adapter(&btv->c.i2c_adap);
	पूर्ण अन्यथा अणु
		bttv_bit_setscl(btv,1);
		bttv_bit_setsda(btv,1);
		btv->i2c_rc = i2c_bit_add_bus(&btv->c.i2c_adap);
	पूर्ण
	अगर (0 == btv->i2c_rc && i2c_scan)
		करो_i2c_scan(btv->c.v4l2_dev.name, &btv->i2c_client);

	वापस btv->i2c_rc;
पूर्ण

पूर्णांक fini_bttv_i2c(काष्ठा bttv *btv)
अणु
	अगर (btv->i2c_rc == 0)
		i2c_del_adapter(&btv->c.i2c_adap);

	वापस 0;
पूर्ण
