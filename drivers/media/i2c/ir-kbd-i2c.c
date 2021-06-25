<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * keyboard input driver क्रम i2c IR remote controls
 *
 * Copyright (c) 2000-2003 Gerd Knorr <kraxel@bytesex.org>
 * modअगरied क्रम PixelView (BT878P+W/FM) by
 *      Michal Kochanowicz <mkochano@pld.org.pl>
 *      Christoph Bartelmus <lirc@bartelmus.de>
 * modअगरied क्रम KNC ONE TV Station/Anubis Typhoon TView Tuner by
 *      Ulrich Mueller <ulrich.mueller42@web.de>
 * modअगरied क्रम em2820 based USB TV tuners by
 *      Markus Rechberger <mrechberger@gmail.com>
 * modअगरied क्रम DViCO Fusion HDTV 5 RT GOLD by
 *      Chaogui Zhang <czhang1974@gmail.com>
 * modअगरied क्रम MSI TV@nywhere Plus by
 *      Henry Wong <henry@stuffedcow.net>
 *      Mark Schultz <n9xmj@yahoo.com>
 *      Brian Rogers <brian_rogers@comcast.net>
 * modअगरied क्रम AVerMedia Cardbus by
 *      Oldrich Jedlicka <oldium.pro@seznam.cz>
 * Zilog Transmitter portions/ideas were derived from GPLv2+ sources:
 *  - drivers/अक्षर/pctv_zilogir.[ch] from Hauppauge Broadway product
 *	Copyright 2011 Hauppauge Computer works
 *  - drivers/staging/media/lirc/lirc_zilog.c
 *	Copyright (c) 2000 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *	Michal Kochanowicz <mkochano@pld.org.pl>
 *	Christoph Bartelmus <lirc@bartelmus.de>
 *	Ulrich Mueller <ulrich.mueller42@web.de>
 *	Stefan Jahn <stefan@lkcc.org>
 *	Jerome Brock <jbrock@users.sourceक्रमge.net>
 *	Thomas Reiपंचांगayr (treiपंचांगayr@yahoo.com)
 *	Mark Weaver <mark@npsl.co.uk>
 *	Jarod Wilson <jarod@redhat.com>
 *	Copyright (C) 2011 Andy Walls <awalls@md.metrocast.net>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>

#समावेश <media/rc-core.h>
#समावेश <media/i2c/ir-kbd-i2c.h>

#घोषणा FLAG_TX		1
#घोषणा FLAG_HDPVR	2

अटल bool enable_hdpvr;
module_param(enable_hdpvr, bool, 0644);

अटल पूर्णांक get_key_haup_common(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			       u32 *scancode, u8 *ptoggle, पूर्णांक size)
अणु
	अचिन्हित अक्षर buf[6];
	पूर्णांक start, range, toggle, dev, code, ircode, venकरोr;

	/* poll IR chip */
	अगर (size != i2c_master_recv(ir->c, buf, size))
		वापस -EIO;

	अगर (buf[0] & 0x80) अणु
		पूर्णांक offset = (size == 6) ? 3 : 0;

		/* split rc5 data block ... */
		start  = (buf[offset] >> 7) &    1;
		range  = (buf[offset] >> 6) &    1;
		toggle = (buf[offset] >> 5) &    1;
		dev    =  buf[offset]       & 0x1f;
		code   = (buf[offset+1] >> 2) & 0x3f;

		/* rc5 has two start bits
		 * the first bit must be one
		 * the second bit defines the command range:
		 * 1 = 0-63, 0 = 64 - 127
		 */
		अगर (!start)
			/* no key pressed */
			वापस 0;

		/* filter out invalid key presses */
		ircode = (start << 12) | (toggle << 11) | (dev << 6) | code;
		अगर ((ircode & 0x1fff) == 0x1fff)
			वापस 0;

		अगर (!range)
			code += 64;

		dev_dbg(&ir->rc->dev,
			"ir hauppauge (rc5): s%d r%d t%d dev=%d code=%d\n",
			start, range, toggle, dev, code);

		*protocol = RC_PROTO_RC5;
		*scancode = RC_SCANCODE_RC5(dev, code);
		*ptoggle = toggle;

		वापस 1;
	पूर्ण अन्यथा अगर (size == 6 && (buf[0] & 0x40)) अणु
		code = buf[4];
		dev = buf[3];
		venकरोr = get_unaligned_be16(buf + 1);

		अगर (venकरोr == 0x800f) अणु
			*ptoggle = (dev & 0x80) != 0;
			*protocol = RC_PROTO_RC6_MCE;
			dev &= 0x7f;
			dev_dbg(&ir->rc->dev,
				"ir hauppauge (rc6-mce): t%d vendor=%d dev=%d code=%d\n",
				*ptoggle, venकरोr, dev, code);
		पूर्ण अन्यथा अणु
			*ptoggle = 0;
			*protocol = RC_PROTO_RC6_6A_32;
			dev_dbg(&ir->rc->dev,
				"ir hauppauge (rc6-6a-32): vendor=%d dev=%d code=%d\n",
				venकरोr, dev, code);
		पूर्ण

		*scancode = RC_SCANCODE_RC6_6A(venकरोr, dev, code);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_key_haup(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			u32 *scancode, u8 *toggle)
अणु
	वापस get_key_haup_common(ir, protocol, scancode, toggle, 3);
पूर्ण

अटल पूर्णांक get_key_haup_xvr(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			    u32 *scancode, u8 *toggle)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर buf[1] = अणु 0 पूर्ण;

	/*
	 * This is the same apparent "are you ready?" poll command observed
	 * watching Winकरोws driver traffic and implemented in lirc_zilog. With
	 * this added, we get far saner remote behavior with z8 chips on usb
	 * connected devices, even with the शेष polling पूर्णांकerval of 100ms.
	 */
	ret = i2c_master_send(ir->c, buf, 1);
	अगर (ret != 1)
		वापस (ret < 0) ? ret : -EINVAL;

	वापस get_key_haup_common(ir, protocol, scancode, toggle, 6);
पूर्ण

अटल पूर्णांक get_key_pixelview(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			     u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		dev_dbg(&ir->rc->dev, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	*protocol = RC_PROTO_OTHER;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_fusionhdtv(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			      u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर buf[4];

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, buf, 4);
	अगर (rc != 4) अणु
		dev_dbg(&ir->rc->dev, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	अगर (buf[0] != 0 || buf[1] != 0 || buf[2] != 0 || buf[3] != 0)
		dev_dbg(&ir->rc->dev, "%s: %*ph\n", __func__, 4, buf);

	/* no key pressed or संकेत from other ir remote */
	अगर(buf[0] != 0x1 ||  buf[1] != 0xfe)
		वापस 0;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = buf[2];
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_knc1(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		dev_dbg(&ir->rc->dev, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/* it seems that 0xFE indicates that a button is still hold
	   करोwn, जबतक 0xff indicates that no button is hold
	   करोwn. 0xfe sequences are someबार पूर्णांकerrupted by 0xFF */

	dev_dbg(&ir->rc->dev, "key %02x\n", b);

	अगर (b == 0xff)
		वापस 0;

	अगर (b == 0xfe)
		/* keep old data */
		वापस 1;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_avermedia_cardbus(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
				     u32 *scancode, u8 *toggle)
अणु
	अचिन्हित अक्षर subaddr, key, keygroup;
	काष्ठा i2c_msg msg[] = अणु अणु .addr = ir->c->addr, .flags = 0,
				   .buf = &subaddr, .len = 1पूर्ण,
				 अणु .addr = ir->c->addr, .flags = I2C_M_RD,
				  .buf = &key, .len = 1पूर्ण पूर्ण;
	subaddr = 0x0d;
	अगर (2 != i2c_transfer(ir->c->adapter, msg, 2)) अणु
		dev_dbg(&ir->rc->dev, "read error\n");
		वापस -EIO;
	पूर्ण

	अगर (key == 0xff)
		वापस 0;

	subaddr = 0x0b;
	msg[1].buf = &keygroup;
	अगर (2 != i2c_transfer(ir->c->adapter, msg, 2)) अणु
		dev_dbg(&ir->rc->dev, "read error\n");
		वापस -EIO;
	पूर्ण

	अगर (keygroup == 0xff)
		वापस 0;

	dev_dbg(&ir->rc->dev, "read key 0x%02x/0x%02x\n", key, keygroup);
	अगर (keygroup < 2 || keygroup > 4) अणु
		dev_warn(&ir->rc->dev, "warning: invalid key group 0x%02x for key 0x%02x\n",
			 keygroup, key);
	पूर्ण
	key |= (keygroup & 1) << 6;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = key;
	अगर (ir->c->addr == 0x41) /* AVerMedia EM78P153 */
		*scancode |= keygroup << 8;
	*toggle = 0;
	वापस 1;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक ir_key_poll(काष्ठा IR_i2c *ir)
अणु
	क्रमागत rc_proto protocol;
	u32 scancode;
	u8 toggle;
	पूर्णांक rc;

	dev_dbg(&ir->rc->dev, "%s\n", __func__);
	rc = ir->get_key(ir, &protocol, &scancode, &toggle);
	अगर (rc < 0) अणु
		dev_warn(&ir->rc->dev, "error %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (rc) अणु
		dev_dbg(&ir->rc->dev, "%s: proto = 0x%04x, scancode = 0x%08x\n",
			__func__, protocol, scancode);
		rc_keyकरोwn(ir->rc, protocol, scancode, toggle);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ir_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा IR_i2c *ir = container_of(work, काष्ठा IR_i2c, work.work);

	/*
	 * If the transmit code is holding the lock, skip polling क्रम
	 * IR, we'll get it to it next समय round
	 */
	अगर (mutex_trylock(&ir->lock)) अणु
		rc = ir_key_poll(ir);
		mutex_unlock(&ir->lock);
		अगर (rc == -ENODEV) अणु
			rc_unरेजिस्टर_device(ir->rc);
			ir->rc = शून्य;
			वापस;
		पूर्ण
	पूर्ण

	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling_पूर्णांकerval));
पूर्ण

अटल पूर्णांक ir_खोलो(काष्ठा rc_dev *dev)
अणु
	काष्ठा IR_i2c *ir = dev->priv;

	schedule_delayed_work(&ir->work, 0);

	वापस 0;
पूर्ण

अटल व्योम ir_बंद(काष्ठा rc_dev *dev)
अणु
	काष्ठा IR_i2c *ir = dev->priv;

	cancel_delayed_work_sync(&ir->work);
पूर्ण

/* Zilog Transmit Interface */
#घोषणा XTAL_FREQ		18432000

#घोषणा ZILOG_SEND		0x80
#घोषणा ZILOG_UIR_END		0x40
#घोषणा ZILOG_INIT_END		0x20
#घोषणा ZILOG_LIR_END		0x10

#घोषणा ZILOG_STATUS_OK		0x80
#घोषणा ZILOG_STATUS_TX		0x40
#घोषणा ZILOG_STATUS_SET	0x20

/*
 * As you can see here, very few dअगरferent lengths of pulse and space
 * can be encoded. This means that the hardware करोes not work well with
 * recorded IR. It's best to work with generated IR, like from ir-ctl or
 * the in-kernel encoders.
 */
काष्ठा code_block अणु
	u8	length;
	u16	pulse[7];	/* not aligned */
	u8	carrier_pulse;
	u8	carrier_space;
	u16	space[8];	/* not aligned */
	u8	codes[61];
	u8	csum[2];
पूर्ण __packed;

अटल पूर्णांक send_data_block(काष्ठा IR_i2c *ir, पूर्णांक cmd,
			   काष्ठा code_block *code_block)
अणु
	पूर्णांक i, j, ret;
	u8 buf[5], *p;

	p = &code_block->length;
	क्रम (i = 0; p < code_block->csum; i++)
		code_block->csum[i & 1] ^= *p++;

	p = &code_block->length;

	क्रम (i = 0; i < माप(*code_block);) अणु
		पूर्णांक tosend = माप(*code_block) - i;

		अगर (tosend > 4)
			tosend = 4;
		buf[0] = i + 1;
		क्रम (j = 0; j < tosend; ++j)
			buf[1 + j] = p[i + j];
		dev_dbg(&ir->rc->dev, "%*ph", tosend + 1, buf);
		ret = i2c_master_send(ir->tx_c, buf, tosend + 1);
		अगर (ret != tosend + 1) अणु
			dev_dbg(&ir->rc->dev,
				"i2c_master_send failed with %d\n", ret);
			वापस ret < 0 ? ret : -EIO;
		पूर्ण
		i += tosend;
	पूर्ण

	buf[0] = 0;
	buf[1] = cmd;
	ret = i2c_master_send(ir->tx_c, buf, 2);
	अगर (ret != 2) अणु
		dev_err(&ir->rc->dev, "i2c_master_send failed with %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	usleep_range(2000, 5000);

	ret = i2c_master_send(ir->tx_c, buf, 1);
	अगर (ret != 1) अणु
		dev_err(&ir->rc->dev, "i2c_master_send failed with %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zilog_init(काष्ठा IR_i2c *ir)
अणु
	काष्ठा code_block code_block = अणु .length = माप(code_block) पूर्ण;
	u8 buf[4];
	पूर्णांक ret;

	put_unaligned_be16(0x1000, &code_block.pulse[3]);

	ret = send_data_block(ir, ZILOG_INIT_END, &code_block);
	अगर (ret)
		वापस ret;

	ret = i2c_master_recv(ir->tx_c, buf, 4);
	अगर (ret != 4) अणु
		dev_err(&ir->c->dev, "failed to retrieve firmware version: %d\n",
			ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	dev_info(&ir->c->dev, "Zilog/Hauppauge IR blaster firmware version %d.%d.%d\n",
		 buf[1], buf[2], buf[3]);

	वापस 0;
पूर्ण

/*
 * If the last slot क्रम pulse is the same as the current slot क्रम pulse,
 * then use slot no 7.
 */
अटल व्योम copy_codes(u8 *dst, u8 *src, अचिन्हित पूर्णांक count)
अणु
	u8 c, last = 0xff;

	जबतक (count--) अणु
		c = *src++;
		अगर ((c & 0xf0) == last) अणु
			*dst++ = 0x70 | (c & 0xf);
		पूर्ण अन्यथा अणु
			*dst++ = c;
			last = c & 0xf0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * When looking क्रम repeats, we करोn't care about the trailing space. This
 * is set to the लघुest possible anyway.
 */
अटल पूर्णांक cmp_no_trail(u8 *a, u8 *b, अचिन्हित पूर्णांक count)
अणु
	जबतक (--count) अणु
		अगर (*a++ != *b++)
			वापस 1;
	पूर्ण

	वापस (*a & 0xf0) - (*b & 0xf0);
पूर्ण

अटल पूर्णांक find_slot(u16 *array, अचिन्हित पूर्णांक size, u16 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (get_unaligned_be16(&array[i]) == val) अणु
			वापस i;
		पूर्ण अन्यथा अगर (!array[i]) अणु
			put_unaligned_be16(val, &array[i]);
			वापस i;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक zilog_ir_क्रमmat(काष्ठा rc_dev *rcdev, अचिन्हित पूर्णांक *txbuf,
			   अचिन्हित पूर्णांक count, काष्ठा code_block *code_block)
अणु
	काष्ठा IR_i2c *ir = rcdev->priv;
	पूर्णांक rep, i, l, p = 0, s, c = 0;
	bool repeating;
	u8 codes[174];

	code_block->carrier_pulse = DIV_ROUND_CLOSEST(
			ir->duty_cycle * XTAL_FREQ / 1000, ir->carrier);
	code_block->carrier_space = DIV_ROUND_CLOSEST(
			(100 - ir->duty_cycle) * XTAL_FREQ / 1000, ir->carrier);

	क्रम (i = 0; i < count; i++) अणु
		अगर (c >= ARRAY_SIZE(codes) - 1) अणु
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Lengths more than 142220us cannot be encoded; also
		 * this checks क्रम multiply overflow
		 */
		अगर (txbuf[i] > 142220)
			वापस -EINVAL;

		l = DIV_ROUND_CLOSEST((XTAL_FREQ / 1000) * txbuf[i], 40000);

		अगर (i & 1) अणु
			s = find_slot(code_block->space,
				      ARRAY_SIZE(code_block->space), l);
			अगर (s == -1) अणु
				dev_warn(&rcdev->dev, "Too many different lengths spaces, cannot transmit");
				वापस -EINVAL;
			पूर्ण

			/* We have a pulse and space */
			codes[c++] = (p << 4) | s;
		पूर्ण अन्यथा अणु
			p = find_slot(code_block->pulse,
				      ARRAY_SIZE(code_block->pulse), l);
			अगर (p == -1) अणु
				dev_warn(&rcdev->dev, "Too many different lengths pulses, cannot transmit");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* We have to encode the trailing pulse. Find the लघुest space */
	s = 0;
	क्रम (i = 1; i < ARRAY_SIZE(code_block->space); i++) अणु
		u16 d = get_unaligned_be16(&code_block->space[i]);

		अगर (get_unaligned_be16(&code_block->space[s]) > d)
			s = i;
	पूर्ण

	codes[c++] = (p << 4) | s;

	dev_dbg(&rcdev->dev, "generated %d codes\n", c);

	/*
	 * Are the last N codes (so pulse + space) repeating 3 बार?
	 * अगर so we can लघुen the codes list and use code 0xc0 to repeat
	 * them.
	 */
	repeating = false;

	क्रम (rep = c / 3; rep >= 1; rep--) अणु
		अगर (!स_भेद(&codes[c - rep * 3], &codes[c - rep * 2], rep) &&
		    !cmp_no_trail(&codes[c - rep], &codes[c - rep * 2], rep)) अणु
			repeating = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (repeating) अणु
		/* first copy any leading non-repeating */
		पूर्णांक leading = c - rep * 3;

		अगर (leading >= ARRAY_SIZE(code_block->codes) - 3 - rep) अणु
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(&rcdev->dev, "found trailing %d repeat\n", rep);
		copy_codes(code_block->codes, codes, leading);
		code_block->codes[leading] = 0x82;
		copy_codes(code_block->codes + leading + 1, codes + leading,
			   rep);
		c = leading + 1 + rep;
		code_block->codes[c++] = 0xc0;
	पूर्ण अन्यथा अणु
		अगर (c >= ARRAY_SIZE(code_block->codes) - 3) अणु
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(&rcdev->dev, "found no trailing repeat\n");
		code_block->codes[0] = 0x82;
		copy_codes(code_block->codes + 1, codes, c);
		c++;
		code_block->codes[c++] = 0xc4;
	पूर्ण

	जबतक (c < ARRAY_SIZE(code_block->codes))
		code_block->codes[c++] = 0x83;

	वापस 0;
पूर्ण

अटल पूर्णांक zilog_tx(काष्ठा rc_dev *rcdev, अचिन्हित पूर्णांक *txbuf,
		    अचिन्हित पूर्णांक count)
अणु
	काष्ठा IR_i2c *ir = rcdev->priv;
	काष्ठा code_block code_block = अणु .length = माप(code_block) पूर्ण;
	u8 buf[2];
	पूर्णांक ret, i;

	ret = zilog_ir_क्रमmat(rcdev, txbuf, count, &code_block);
	अगर (ret)
		वापस ret;

	ret = mutex_lock_पूर्णांकerruptible(&ir->lock);
	अगर (ret)
		वापस ret;

	ret = send_data_block(ir, ZILOG_UIR_END, &code_block);
	अगर (ret)
		जाओ out_unlock;

	ret = i2c_master_recv(ir->tx_c, buf, 1);
	अगर (ret != 1) अणु
		dev_err(&ir->rc->dev, "i2c_master_recv failed with %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	dev_dbg(&ir->rc->dev, "code set status: %02x\n", buf[0]);

	अगर (buf[0] != (ZILOG_STATUS_OK | ZILOG_STATUS_SET)) अणु
		dev_err(&ir->rc->dev, "unexpected IR TX response %02x\n",
			buf[0]);
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	buf[0] = 0x00;
	buf[1] = ZILOG_SEND;

	ret = i2c_master_send(ir->tx_c, buf, 2);
	अगर (ret != 2) अणु
		dev_err(&ir->rc->dev, "i2c_master_send failed with %d\n", ret);
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	dev_dbg(&ir->rc->dev, "send command sent\n");

	/*
	 * This bit NAKs until the device is पढ़ोy, so we retry it
	 * sleeping a bit each समय.  This seems to be what the winकरोws
	 * driver करोes, approximately.
	 * Try क्रम up to 1s.
	 */
	क्रम (i = 0; i < 20; ++i) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(50));
		ret = i2c_master_send(ir->tx_c, buf, 1);
		अगर (ret == 1)
			अवरोध;
		dev_dbg(&ir->rc->dev,
			"NAK expected: i2c_master_send failed with %d (try %d)\n",
			ret, i + 1);
	पूर्ण

	अगर (ret != 1) अणु
		dev_err(&ir->rc->dev,
			"IR TX chip never got ready: last i2c_master_send failed with %d\n",
			ret);
		अगर (ret >= 0)
			ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	i = i2c_master_recv(ir->tx_c, buf, 1);
	अगर (i != 1) अणु
		dev_err(&ir->rc->dev, "i2c_master_recv failed with %d\n", ret);
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (buf[0] != ZILOG_STATUS_OK) अणु
		dev_err(&ir->rc->dev, "unexpected IR TX response #2: %02x\n",
			buf[0]);
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण
	dev_dbg(&ir->rc->dev, "transmit complete\n");

	/* Oh good, it worked */
	ret = count;
out_unlock:
	mutex_unlock(&ir->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक zilog_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा IR_i2c *ir = dev->priv;

	अगर (carrier > 500000 || carrier < 20000)
		वापस -EINVAL;

	ir->carrier = carrier;

	वापस 0;
पूर्ण

अटल पूर्णांक zilog_tx_duty_cycle(काष्ठा rc_dev *dev, u32 duty_cycle)
अणु
	काष्ठा IR_i2c *ir = dev->priv;

	ir->duty_cycle = duty_cycle;

	वापस 0;
पूर्ण

अटल पूर्णांक ir_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	अक्षर *ir_codes = शून्य;
	स्थिर अक्षर *name = शून्य;
	u64 rc_proto = RC_PROTO_BIT_UNKNOWN;
	काष्ठा IR_i2c *ir;
	काष्ठा rc_dev *rc = शून्य;
	काष्ठा i2c_adapter *adap = client->adapter;
	अचिन्हित लघु addr = client->addr;
	bool probe_tx = (id->driver_data & FLAG_TX) != 0;
	पूर्णांक err;

	अगर ((id->driver_data & FLAG_HDPVR) && !enable_hdpvr) अणु
		dev_err(&client->dev, "IR for HDPVR is known to cause problems during recording, use enable_hdpvr modparam to enable\n");
		वापस -ENODEV;
	पूर्ण

	ir = devm_kzalloc(&client->dev, माप(*ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	ir->c = client;
	ir->polling_पूर्णांकerval = DEFAULT_POLLING_INTERVAL;
	i2c_set_clientdata(client, ir);

	चयन(addr) अणु
	हाल 0x64:
		name        = "Pixelview";
		ir->get_key = get_key_pixelview;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_EMPTY;
		अवरोध;
	हाल 0x18:
	हाल 0x1f:
	हाल 0x1a:
		name        = "Hauppauge";
		ir->get_key = get_key_haup;
		rc_proto    = RC_PROTO_BIT_RC5;
		ir_codes    = RC_MAP_HAUPPAUGE;
		अवरोध;
	हाल 0x30:
		name        = "KNC One";
		ir->get_key = get_key_knc1;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_EMPTY;
		अवरोध;
	हाल 0x6b:
		name        = "FusionHDTV";
		ir->get_key = get_key_fusionhdtv;
		rc_proto    = RC_PROTO_BIT_UNKNOWN;
		ir_codes    = RC_MAP_FUSIONHDTV_MCE;
		अवरोध;
	हाल 0x40:
		name        = "AVerMedia Cardbus remote";
		ir->get_key = get_key_avermedia_cardbus;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_AVERMEDIA_CARDBUS;
		अवरोध;
	हाल 0x41:
		name        = "AVerMedia EM78P153";
		ir->get_key = get_key_avermedia_cardbus;
		rc_proto    = RC_PROTO_BIT_OTHER;
		/* RM-KV remote, seems to be same as RM-K6 */
		ir_codes    = RC_MAP_AVERMEDIA_M733A_RM_K6;
		अवरोध;
	हाल 0x71:
		name        = "Hauppauge/Zilog Z8";
		ir->get_key = get_key_haup_xvr;
		rc_proto    = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
							RC_PROTO_BIT_RC6_6A_32;
		ir_codes    = RC_MAP_HAUPPAUGE;
		probe_tx = true;
		अवरोध;
	पूर्ण

	/* Let the caller override settings */
	अगर (client->dev.platक्रमm_data) अणु
		स्थिर काष्ठा IR_i2c_init_data *init_data =
						client->dev.platक्रमm_data;

		ir_codes = init_data->ir_codes;
		rc = init_data->rc_dev;

		name = init_data->name;
		अगर (init_data->type)
			rc_proto = init_data->type;

		अगर (init_data->polling_पूर्णांकerval)
			ir->polling_पूर्णांकerval = init_data->polling_पूर्णांकerval;

		चयन (init_data->पूर्णांकernal_get_key_func) अणु
		हाल IR_KBD_GET_KEY_CUSTOM:
			/* The bridge driver provided us its own function */
			ir->get_key = init_data->get_key;
			अवरोध;
		हाल IR_KBD_GET_KEY_PIXELVIEW:
			ir->get_key = get_key_pixelview;
			अवरोध;
		हाल IR_KBD_GET_KEY_HAUP:
			ir->get_key = get_key_haup;
			अवरोध;
		हाल IR_KBD_GET_KEY_KNC1:
			ir->get_key = get_key_knc1;
			अवरोध;
		हाल IR_KBD_GET_KEY_FUSIONHDTV:
			ir->get_key = get_key_fusionhdtv;
			अवरोध;
		हाल IR_KBD_GET_KEY_HAUP_XVR:
			ir->get_key = get_key_haup_xvr;
			अवरोध;
		हाल IR_KBD_GET_KEY_AVERMEDIA_CARDBUS:
			ir->get_key = get_key_avermedia_cardbus;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rc) अणु
		/*
		 * If platक्रमm_data करोesn't specअगरy rc_dev, initialize it
		 * पूर्णांकernally
		 */
		rc = rc_allocate_device(RC_DRIVER_SCANCODE);
		अगर (!rc)
			वापस -ENOMEM;
	पूर्ण
	ir->rc = rc;

	/* Make sure we are all setup beक्रमe going on */
	अगर (!name || !ir->get_key || !rc_proto || !ir_codes) अणु
		dev_warn(&client->dev, "Unsupported device at address 0x%02x\n",
			 addr);
		err = -ENODEV;
		जाओ err_out_मुक्त;
	पूर्ण

	ir->ir_codes = ir_codes;

	snम_लिखो(ir->phys, माप(ir->phys), "%s/%s", dev_name(&adap->dev),
		 dev_name(&client->dev));

	/*
	 * Initialize input_dev fields
	 * It करोesn't make sense to allow overriding them via platक्रमm_data
	 */
	rc->input_id.bustype = BUS_I2C;
	rc->input_phys       = ir->phys;
	rc->device_name	     = name;
	rc->dev.parent       = &client->dev;
	rc->priv             = ir;
	rc->खोलो             = ir_खोलो;
	rc->बंद            = ir_बंद;

	/*
	 * Initialize the other fields of rc_dev
	 */
	rc->map_name       = ir->ir_codes;
	rc->allowed_protocols = rc_proto;
	अगर (!rc->driver_name)
		rc->driver_name = KBUILD_MODNAME;

	mutex_init(&ir->lock);

	INIT_DELAYED_WORK(&ir->work, ir_work);

	अगर (probe_tx) अणु
		ir->tx_c = i2c_new_dummy_device(client->adapter, 0x70);
		अगर (IS_ERR(ir->tx_c)) अणु
			dev_err(&client->dev, "failed to setup tx i2c address");
			err = PTR_ERR(ir->tx_c);
			जाओ err_out_मुक्त;
		पूर्ण अन्यथा अगर (!zilog_init(ir)) अणु
			ir->carrier = 38000;
			ir->duty_cycle = 40;
			rc->tx_ir = zilog_tx;
			rc->s_tx_carrier = zilog_tx_carrier;
			rc->s_tx_duty_cycle = zilog_tx_duty_cycle;
		पूर्ण
	पूर्ण

	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ err_out_मुक्त;

	वापस 0;

 err_out_मुक्त:
	अगर (!IS_ERR(ir->tx_c))
		i2c_unरेजिस्टर_device(ir->tx_c);

	/* Only मुक्तs rc अगर it were allocated पूर्णांकernally */
	rc_मुक्त_device(rc);
	वापस err;
पूर्ण

अटल पूर्णांक ir_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा IR_i2c *ir = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&ir->work);

	i2c_unरेजिस्टर_device(ir->tx_c);

	rc_unरेजिस्टर_device(ir->rc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ir_kbd_id[] = अणु
	/* Generic entry क्रम any IR receiver */
	अणु "ir_video", 0 पूर्ण,
	/* IR device specअगरic entries should be added here */
	अणु "ir_z8f0811_haup", FLAG_TX पूर्ण,
	अणु "ir_z8f0811_hdpvr", FLAG_TX | FLAG_HDPVR पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ir_kbd_id);

अटल काष्ठा i2c_driver ir_kbd_driver = अणु
	.driver = अणु
		.name   = "ir-kbd-i2c",
	पूर्ण,
	.probe          = ir_probe,
	.हटाओ         = ir_हटाओ,
	.id_table       = ir_kbd_id,
पूर्ण;

module_i2c_driver(ir_kbd_driver);

/* ----------------------------------------------------------------------- */

MODULE_AUTHOR("Gerd Knorr, Michal Kochanowicz, Christoph Bartelmus, Ulrich Mueller");
MODULE_DESCRIPTION("input driver for i2c IR remote controls");
MODULE_LICENSE("GPL");
