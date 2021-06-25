<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/usb/input/yealink.c
 *
 * Copyright (c) 2005 Henk Vergonet <Henk.Vergonet@gmail.com>
 */
/*
 * Description:
 *   Driver क्रम the USB-P1K voip usb phone.
 *   This device is produced by Yealink Network Technology Co Ltd
 *   but may be bअक्रमed under several names:
 *	- Yealink usb-p1k
 *	- Tiptel 115
 *	- ...
 *
 * This driver is based on:
 *   - the usbb2k-api	http://savannah.nongnu.org/projects/usbb2k-api/
 *   - inक्रमmation from	http://memeteau.मुक्त.fr/usbb2k
 *   - the xpad-driver	drivers/input/joystick/xpad.c
 *
 * Thanks to:
 *   - Olivier Vanकरोrpe, क्रम providing the usbb2k-api.
 *   - Martin Diehl, क्रम spotting my memory allocation bug.
 *
 * History:
 *   20050527 henk	First version, functional keyboard. Keyboard events
 *			will pop-up on the ../input/eventX bus.
 *   20050531 henk	Added led, LCD, dialtone and sysfs पूर्णांकerface.
 *   20050610 henk	Cleanups, make it पढ़ोy क्रम खुला consumption.
 *   20050630 henk	Cleanups, fixes in response to comments.
 *   20050701 henk	sysfs ग_लिखो serialisation, fix potential unload races
 *   20050801 henk	Added ringtone, reकाष्ठाure USB
 *   20050816 henk	Merge 2.6.13-rc6
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/map_to_7segment.h>

#समावेश "yealink.h"

#घोषणा DRIVER_VERSION "yld-20051230"

#घोषणा YEALINK_POLLING_FREQUENCY	10	/* in [Hz] */

काष्ठा yld_status अणु
	u8	lcd[24];
	u8	led;
	u8	dialtone;
	u8	ringtone;
	u8	keynum;
पूर्ण __attribute__ ((packed));

/*
 * Register the LCD segment and icon map
 */
#घोषणा _LOC(k,l)	अणु .a = (k), .m = (l) पूर्ण
#घोषणा _SEG(t, a, am, b, bm, c, cm, d, dm, e, em, f, fm, g, gm)	\
	अणु .type	= (t),							\
	  .u = अणु .s = अणु	_LOC(a, am), _LOC(b, bm), _LOC(c, cm),		\
		        _LOC(d, dm), _LOC(e, em), _LOC(g, gm),		\
			_LOC(f, fm) पूर्ण पूर्ण पूर्ण
#घोषणा _PIC(t, h, hm, n)						\
	अणु .type	= (t),							\
 	  .u = अणु .p = अणु .name = (n), .a = (h), .m = (hm) पूर्ण पूर्ण पूर्ण

अटल स्थिर काष्ठा lcd_segment_map अणु
	अक्षर	type;
	जोड़ अणु
		काष्ठा pictogram_map अणु
			u8	a,m;
			अक्षर	name[10];
		पूर्ण	p;
		काष्ठा segment_map अणु
			u8	a,m;
		पूर्ण s[7];
	पूर्ण u;
पूर्ण lcdMap[] = अणु
#समावेश "yealink.h"
पूर्ण;

काष्ठा yealink_dev अणु
	काष्ठा input_dev *idev;		/* input device */
	काष्ठा usb_device *udev;	/* usb device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;	/* usb पूर्णांकerface */

	/* irq input channel */
	काष्ठा yld_ctl_packet	*irq_data;
	dma_addr_t		irq_dma;
	काष्ठा urb		*urb_irq;

	/* control output channel */
	काष्ठा yld_ctl_packet	*ctl_data;
	dma_addr_t		ctl_dma;
	काष्ठा usb_ctrlrequest	*ctl_req;
	काष्ठा urb		*urb_ctl;

	अक्षर phys[64];			/* physical device path */

	u8 lcdMap[ARRAY_SIZE(lcdMap)];	/* state of LCD, LED ... */
	पूर्णांक key_code;			/* last reported key	 */

	अचिन्हित पूर्णांक shutकरोwn:1;

	पूर्णांक	stat_ix;
	जोड़ अणु
		काष्ठा yld_status s;
		u8		  b[माप(काष्ठा yld_status)];
	पूर्ण master, copy;
पूर्ण;


/*******************************************************************************
 * Yealink lcd पूर्णांकerface
 ******************************************************************************/

/*
 * Register a शेष 7 segment अक्षरacter set
 */
अटल SEG7_DEFAULT_MAP(map_seg7);

 /* Display a अक्षर,
  * अक्षर '\9' and '\n' are placeholders and करो not overग_लिखो the original text.
  * A space will always hide an icon.
  */
अटल पूर्णांक setChar(काष्ठा yealink_dev *yld, पूर्णांक el, पूर्णांक chr)
अणु
	पूर्णांक i, a, m, val;

	अगर (el >= ARRAY_SIZE(lcdMap))
		वापस -EINVAL;

	अगर (chr == '\t' || chr == '\n')
	    वापस 0;

	yld->lcdMap[el] = chr;

	अगर (lcdMap[el].type == '.') अणु
		a = lcdMap[el].u.p.a;
		m = lcdMap[el].u.p.m;
		अगर (chr != ' ')
			yld->master.b[a] |= m;
		अन्यथा
			yld->master.b[a] &= ~m;
		वापस 0;
	पूर्ण

	val = map_to_seg7(&map_seg7, chr);
	क्रम (i = 0; i < ARRAY_SIZE(lcdMap[0].u.s); i++) अणु
		m = lcdMap[el].u.s[i].m;

		अगर (m == 0)
			जारी;

		a = lcdMap[el].u.s[i].a;
		अगर (val & 1)
			yld->master.b[a] |= m;
		अन्यथा
			yld->master.b[a] &= ~m;
		val = val >> 1;
	पूर्ण
	वापस 0;
पूर्ण;

/*******************************************************************************
 * Yealink key पूर्णांकerface
 ******************************************************************************/

/* Map device buttons to पूर्णांकernal key events.
 *
 * USB-P1K button layout:
 *
 *             up
 *       IN           OUT
 *            करोwn
 *
 *     pickup   C    hangup
 *       1      2      3
 *       4      5      6
 *       7      8      9
 *       *      0      #
 *
 * The "up" and "down" keys, are symbolised by arrows on the button.
 * The "pickup" and "hangup" keys are symbolised by a green and red phone
 * on the button.
 */
अटल पूर्णांक map_p1k_to_key(पूर्णांक scancode)
अणु
	चयन(scancode) अणु		/* phone key:	*/
	हाल 0x23: वापस KEY_LEFT;	/*   IN		*/
	हाल 0x33: वापस KEY_UP;	/*   up		*/
	हाल 0x04: वापस KEY_RIGHT;	/*   OUT	*/
	हाल 0x24: वापस KEY_DOWN;	/*   करोwn	*/
	हाल 0x03: वापस KEY_ENTER;	/*   pickup	*/
	हाल 0x14: वापस KEY_BACKSPACE; /*  C		*/
	हाल 0x13: वापस KEY_ESC;	/*   hangup	*/
	हाल 0x00: वापस KEY_1;	/*   1		*/
	हाल 0x01: वापस KEY_2;	/*   2 		*/
	हाल 0x02: वापस KEY_3;	/*   3		*/
	हाल 0x10: वापस KEY_4;	/*   4		*/
	हाल 0x11: वापस KEY_5;	/*   5		*/
	हाल 0x12: वापस KEY_6;	/*   6		*/
	हाल 0x20: वापस KEY_7;	/*   7		*/
	हाल 0x21: वापस KEY_8;	/*   8		*/
	हाल 0x22: वापस KEY_9;	/*   9		*/
	हाल 0x30: वापस KEY_KPASTERISK; /* *		*/
	हाल 0x31: वापस KEY_0;	/*   0		*/
	हाल 0x32: वापस KEY_LEFTSHIFT |
			  KEY_3 << 8;	/*   #		*/
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Completes a request by converting the data पूर्णांकo events क्रम the
 * input subप्रणाली.
 *
 * The key parameter can be cascaded: key2 << 8 | key1
 */
अटल व्योम report_key(काष्ठा yealink_dev *yld, पूर्णांक key)
अणु
	काष्ठा input_dev *idev = yld->idev;

	अगर (yld->key_code >= 0) अणु
		/* old key up */
		input_report_key(idev, yld->key_code & 0xff, 0);
		अगर (yld->key_code >> 8)
			input_report_key(idev, yld->key_code >> 8, 0);
	पूर्ण

	yld->key_code = key;
	अगर (key >= 0) अणु
		/* new valid key */
		input_report_key(idev, key & 0xff, 1);
		अगर (key >> 8)
			input_report_key(idev, key >> 8, 1);
	पूर्ण
	input_sync(idev);
पूर्ण

/*******************************************************************************
 * Yealink usb communication पूर्णांकerface
 ******************************************************************************/

अटल पूर्णांक yealink_cmd(काष्ठा yealink_dev *yld, काष्ठा yld_ctl_packet *p)
अणु
	u8	*buf = (u8 *)p;
	पूर्णांक	i;
	u8	sum = 0;

	क्रम(i=0; i<USB_PKT_LEN-1; i++)
		sum -= buf[i];
	p->sum = sum;
	वापस usb_control_msg(yld->udev,
			usb_sndctrlpipe(yld->udev, 0),
			USB_REQ_SET_CONFIGURATION,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			0x200, 3,
			p, माप(*p),
			USB_CTRL_SET_TIMEOUT);
पूर्ण

अटल u8 शेष_ringtone[] = अणु
	0xEF,			/* volume [0-255] */
	0xFB, 0x1E, 0x00, 0x0C,	/* 1250 [hz], 12/100 [s] */
	0xFC, 0x18, 0x00, 0x0C,	/* 1000 [hz], 12/100 [s] */
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFF, 0xFF, 0x01, 0x90,	/* silent, 400/100 [s] */
	0x00, 0x00		/* end of sequence */
पूर्ण;

अटल पूर्णांक yealink_set_ringtone(काष्ठा yealink_dev *yld, u8 *buf, माप_प्रकार size)
अणु
	काष्ठा yld_ctl_packet *p = yld->ctl_data;
	पूर्णांक	ix, len;

	अगर (size <= 0)
		वापस -EINVAL;

	/* Set the ringtone volume */
	स_रखो(yld->ctl_data, 0, माप(*(yld->ctl_data)));
	yld->ctl_data->cmd	= CMD_RING_VOLUME;
	yld->ctl_data->size	= 1;
	yld->ctl_data->data[0]	= buf[0];
	yealink_cmd(yld, p);

	buf++;
	size--;

	p->cmd = CMD_RING_NOTE;
	ix = 0;
	जबतक (size != ix) अणु
		len = size - ix;
		अगर (len > माप(p->data))
			len = माप(p->data);
		p->size	  = len;
		p->offset = cpu_to_be16(ix);
		स_नकल(p->data, &buf[ix], len);
		yealink_cmd(yld, p);
		ix += len;
	पूर्ण
	वापस 0;
पूर्ण

/* keep stat_master & stat_copy in sync.
 */
अटल पूर्णांक yealink_करो_idle_tasks(काष्ठा yealink_dev *yld)
अणु
	u8 val;
	पूर्णांक i, ix, len;

	ix = yld->stat_ix;

	स_रखो(yld->ctl_data, 0, माप(*(yld->ctl_data)));
	yld->ctl_data->cmd  = CMD_KEYPRESS;
	yld->ctl_data->size = 1;
	yld->ctl_data->sum  = 0xff - CMD_KEYPRESS;

	/* If state update poपूर्णांकer wraps करो a KEYPRESS first. */
	अगर (ix >= माप(yld->master)) अणु
		yld->stat_ix = 0;
		वापस 0;
	पूर्ण

	/* find update candidates: copy != master */
	करो अणु
		val = yld->master.b[ix];
		अगर (val != yld->copy.b[ix])
			जाओ send_update;
	पूर्ण जबतक (++ix < माप(yld->master));

	/* nothing toकरो, रुको a bit and poll क्रम a KEYPRESS */
	yld->stat_ix = 0;
	/* TODO how can we रुको abit. ??
	 * msleep_पूर्णांकerruptible(1000 / YEALINK_POLLING_FREQUENCY);
	 */
	वापस 0;

send_update:

	/* Setup an appropriate update request */
	yld->copy.b[ix] = val;
	yld->ctl_data->data[0] = val;

	चयन(ix) अणु
	हाल दुरत्व(काष्ठा yld_status, led):
		yld->ctl_data->cmd	= CMD_LED;
		yld->ctl_data->sum	= -1 - CMD_LED - val;
		अवरोध;
	हाल दुरत्व(काष्ठा yld_status, dialtone):
		yld->ctl_data->cmd	= CMD_DIALTONE;
		yld->ctl_data->sum	= -1 - CMD_DIALTONE - val;
		अवरोध;
	हाल दुरत्व(काष्ठा yld_status, ringtone):
		yld->ctl_data->cmd	= CMD_RINGTONE;
		yld->ctl_data->sum	= -1 - CMD_RINGTONE - val;
		अवरोध;
	हाल दुरत्व(काष्ठा yld_status, keynum):
		val--;
		val &= 0x1f;
		yld->ctl_data->cmd	= CMD_SCANCODE;
		yld->ctl_data->offset	= cpu_to_be16(val);
		yld->ctl_data->data[0]	= 0;
		yld->ctl_data->sum	= -1 - CMD_SCANCODE - val;
		अवरोध;
	शेष:
		len = माप(yld->master.s.lcd) - ix;
		अगर (len > माप(yld->ctl_data->data))
			len = माप(yld->ctl_data->data);

		/* Combine up to <len> consecutive LCD bytes in a singe request
		 */
		yld->ctl_data->cmd	= CMD_LCD;
		yld->ctl_data->offset	= cpu_to_be16(ix);
		yld->ctl_data->size	= len;
		yld->ctl_data->sum	= -CMD_LCD - ix - val - len;
		क्रम(i=1; i<len; i++) अणु
			ix++;
			val = yld->master.b[ix];
			yld->copy.b[ix]		= val;
			yld->ctl_data->data[i]	= val;
			yld->ctl_data->sum     -= val;
		पूर्ण
	पूर्ण
	yld->stat_ix = ix + 1;
	वापस 1;
पूर्ण

/* Decide on how to handle responses
 *
 * The state transition diagram is somethhing like:
 *
 *          syncState<--+
 *               |      |
 *               |    idle
 *              \|/     |
 * init --ok--> रुकोForKey --ok--> getKey
 *  ^               ^                |
 *  |               +-------ok-------+
 * error,start
 *
 */
अटल व्योम urb_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा yealink_dev *yld = urb->context;
	पूर्णांक ret, status = urb->status;

	अगर (status)
		dev_err(&yld->पूर्णांकf->dev, "%s - urb status %d\n",
			__func__, status);

	चयन (yld->irq_data->cmd) अणु
	हाल CMD_KEYPRESS:

		yld->master.s.keynum = yld->irq_data->data[0];
		अवरोध;

	हाल CMD_SCANCODE:
		dev_dbg(&yld->पूर्णांकf->dev, "get scancode %x\n",
			yld->irq_data->data[0]);

		report_key(yld, map_p1k_to_key(yld->irq_data->data[0]));
		अवरोध;

	शेष:
		dev_err(&yld->पूर्णांकf->dev, "unexpected response %x\n",
			yld->irq_data->cmd);
	पूर्ण

	yealink_करो_idle_tasks(yld);

	अगर (!yld->shutकरोwn) अणु
		ret = usb_submit_urb(yld->urb_ctl, GFP_ATOMIC);
		अगर (ret && ret != -EPERM)
			dev_err(&yld->पूर्णांकf->dev,
				"%s - usb_submit_urb failed %d\n",
				__func__, ret);
	पूर्ण
पूर्ण

अटल व्योम urb_ctl_callback(काष्ठा urb *urb)
अणु
	काष्ठा yealink_dev *yld = urb->context;
	पूर्णांक ret = 0, status = urb->status;

	अगर (status)
		dev_err(&yld->पूर्णांकf->dev, "%s - urb status %d\n",
			__func__, status);

	चयन (yld->ctl_data->cmd) अणु
	हाल CMD_KEYPRESS:
	हाल CMD_SCANCODE:
		/* ask क्रम a response */
		अगर (!yld->shutकरोwn)
			ret = usb_submit_urb(yld->urb_irq, GFP_ATOMIC);
		अवरोध;
	शेष:
		/* send new command */
		yealink_करो_idle_tasks(yld);
		अगर (!yld->shutकरोwn)
			ret = usb_submit_urb(yld->urb_ctl, GFP_ATOMIC);
		अवरोध;
	पूर्ण

	अगर (ret && ret != -EPERM)
		dev_err(&yld->पूर्णांकf->dev, "%s - usb_submit_urb failed %d\n",
			__func__, ret);
पूर्ण

/*******************************************************************************
 * input event पूर्णांकerface
 ******************************************************************************/

/* TODO should we issue a ringtone on a SND_BELL event?
अटल पूर्णांक input_ev(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक code, पूर्णांक value)
अणु

	अगर (type != EV_SND)
		वापस -EINVAL;

	चयन (code) अणु
	हाल SND_BELL:
	हाल SND_TONE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
*/

अटल पूर्णांक input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा yealink_dev *yld = input_get_drvdata(dev);
	पूर्णांक i, ret;

	dev_dbg(&yld->पूर्णांकf->dev, "%s\n", __func__);

	/* क्रमce updates to device */
	क्रम (i = 0; i<माप(yld->master); i++)
		yld->copy.b[i] = ~yld->master.b[i];
	yld->key_code = -1;	/* no keys pressed */

        yealink_set_ringtone(yld, शेष_ringtone, माप(शेष_ringtone));

	/* issue INIT */
	स_रखो(yld->ctl_data, 0, माप(*(yld->ctl_data)));
	yld->ctl_data->cmd	= CMD_INIT;
	yld->ctl_data->size	= 10;
	yld->ctl_data->sum	= 0x100-CMD_INIT-10;
	अगर ((ret = usb_submit_urb(yld->urb_ctl, GFP_KERNEL)) != 0) अणु
		dev_dbg(&yld->पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा yealink_dev *yld = input_get_drvdata(dev);

	yld->shutकरोwn = 1;
	/*
	 * Make sure the flag is seen by other CPUs beक्रमe we start
	 * समाप्तing URBs so new URBs won't be submitted
	 */
	smp_wmb();

	usb_समाप्त_urb(yld->urb_ctl);
	usb_समाप्त_urb(yld->urb_irq);

	yld->shutकरोwn = 0;
	smp_wmb();
पूर्ण

/*******************************************************************************
 * sysfs पूर्णांकerface
 ******************************************************************************/

अटल DECLARE_RWSEM(sysfs_rwsema);

/* Interface to the 7-segments translation table aka. अक्षर set.
 */
अटल sमाप_प्रकार show_map(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	स_नकल(buf, &map_seg7, माप(map_seg7));
	वापस माप(map_seg7);
पूर्ण

अटल sमाप_प्रकार store_map(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार cnt)
अणु
	अगर (cnt != माप(map_seg7))
		वापस -EINVAL;
	स_नकल(&map_seg7, buf, माप(map_seg7));
	वापस माप(map_seg7);
पूर्ण

/* Interface to the LCD.
 */

/* Reading /sys/../lineX will वापस the क्रमmat string with its settings:
 *
 * Example:
 * cat ./line3
 * 888888888888
 * Linux Rocks!
 */
अटल sमाप_प्रकार show_line(काष्ठा device *dev, अक्षर *buf, पूर्णांक a, पूर्णांक b)
अणु
	काष्ठा yealink_dev *yld;
	पूर्णांक i;

	करोwn_पढ़ो(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	अगर (yld == शून्य) अणु
		up_पढ़ो(&sysfs_rwsema);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = a; i < b; i++)
		*buf++ = lcdMap[i].type;
	*buf++ = '\n';
	क्रम (i = a; i < b; i++)
		*buf++ = yld->lcdMap[i];
	*buf++ = '\n';
	*buf = 0;

	up_पढ़ो(&sysfs_rwsema);
	वापस 3 + ((b - a) << 1);
पूर्ण

अटल sमाप_प्रकार show_line1(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस show_line(dev, buf, LCD_LINE1_OFFSET, LCD_LINE2_OFFSET);
पूर्ण

अटल sमाप_प्रकार show_line2(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस show_line(dev, buf, LCD_LINE2_OFFSET, LCD_LINE3_OFFSET);
पूर्ण

अटल sमाप_प्रकार show_line3(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस show_line(dev, buf, LCD_LINE3_OFFSET, LCD_LINE4_OFFSET);
पूर्ण

/* Writing to /sys/../lineX will set the coresponding LCD line.
 * - Excess अक्षरacters are ignored.
 * - If less अक्षरacters are written than allowed, the reमुख्यing digits are
 *   unchanged.
 * - The '\n' or '\t' अक्षर is a placeholder, it करोes not overग_लिखो the
 *   original content.
 */
अटल sमाप_प्रकार store_line(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
		पूर्णांक el, माप_प्रकार len)
अणु
	काष्ठा yealink_dev *yld;
	पूर्णांक i;

	करोwn_ग_लिखो(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	अगर (yld == शून्य) अणु
		up_ग_लिखो(&sysfs_rwsema);
		वापस -ENODEV;
	पूर्ण

	अगर (len > count)
		len = count;
	क्रम (i = 0; i < len; i++)
		setChar(yld, el++, buf[i]);

	up_ग_लिखो(&sysfs_rwsema);
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_line1(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस store_line(dev, buf, count, LCD_LINE1_OFFSET, LCD_LINE1_SIZE);
पूर्ण

अटल sमाप_प्रकार store_line2(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस store_line(dev, buf, count, LCD_LINE2_OFFSET, LCD_LINE2_SIZE);
पूर्ण

अटल sमाप_प्रकार store_line3(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस store_line(dev, buf, count, LCD_LINE3_OFFSET, LCD_LINE3_SIZE);
पूर्ण

/* Interface to visible and audible "icons", these include:
 * pictures on the LCD, the LED, and the dialtone संकेत.
 */

/* Get a list of "switchable elements" with their current state. */
अटल sमाप_प्रकार get_icons(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा yealink_dev *yld;
	पूर्णांक i, ret = 1;

	करोwn_पढ़ो(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	अगर (yld == शून्य) अणु
		up_पढ़ो(&sysfs_rwsema);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(lcdMap); i++) अणु
		अगर (lcdMap[i].type != '.')
			जारी;
		ret += प्र_लिखो(&buf[ret], "%s %s\n",
				yld->lcdMap[i] == ' ' ? "  " : "on",
				lcdMap[i].u.p.name);
	पूर्ण
	up_पढ़ो(&sysfs_rwsema);
	वापस ret;
पूर्ण

/* Change the visibility of a particular element. */
अटल sमाप_प्रकार set_icon(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
			पूर्णांक chr)
अणु
	काष्ठा yealink_dev *yld;
	पूर्णांक i;

	करोwn_ग_लिखो(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	अगर (yld == शून्य) अणु
		up_ग_लिखो(&sysfs_rwsema);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(lcdMap); i++) अणु
		अगर (lcdMap[i].type != '.')
			जारी;
		अगर (म_भेदन(buf, lcdMap[i].u.p.name, count) == 0) अणु
			setChar(yld, i, chr);
			अवरोध;
		पूर्ण
	पूर्ण

	up_ग_लिखो(&sysfs_rwsema);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_icon(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस set_icon(dev, buf, count, buf[0]);
पूर्ण

अटल sमाप_प्रकार hide_icon(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस set_icon(dev, buf, count, ' ');
पूर्ण

/* Upload a ringtone to the device.
 */

/* Stores raw ringtone data in the phone */
अटल sमाप_प्रकार store_ringtone(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा yealink_dev *yld;

	करोwn_ग_लिखो(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	अगर (yld == शून्य) अणु
		up_ग_लिखो(&sysfs_rwsema);
		वापस -ENODEV;
	पूर्ण

	/* TODO locking with async usb control पूर्णांकerface??? */
	yealink_set_ringtone(yld, (अक्षर *)buf, count);
	up_ग_लिखो(&sysfs_rwsema);
	वापस count;
पूर्ण

#घोषणा _M444	S_IRUGO
#घोषणा _M664	S_IRUGO|S_IWUSR|S_IWGRP
#घोषणा _M220	S_IWUSR|S_IWGRP

अटल DEVICE_ATTR(map_seg7	, _M664, show_map	, store_map	);
अटल DEVICE_ATTR(line1	, _M664, show_line1	, store_line1	);
अटल DEVICE_ATTR(line2	, _M664, show_line2	, store_line2	);
अटल DEVICE_ATTR(line3	, _M664, show_line3	, store_line3	);
अटल DEVICE_ATTR(get_icons	, _M444, get_icons	, शून्य		);
अटल DEVICE_ATTR(show_icon	, _M220, शून्य		, show_icon	);
अटल DEVICE_ATTR(hide_icon	, _M220, शून्य		, hide_icon	);
अटल DEVICE_ATTR(ringtone	, _M220, शून्य		, store_ringtone);

अटल काष्ठा attribute *yld_attributes[] = अणु
	&dev_attr_line1.attr,
	&dev_attr_line2.attr,
	&dev_attr_line3.attr,
	&dev_attr_get_icons.attr,
	&dev_attr_show_icon.attr,
	&dev_attr_hide_icon.attr,
	&dev_attr_map_seg7.attr,
	&dev_attr_ringtone.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group yld_attr_group = अणु
	.attrs = yld_attributes
पूर्ण;

/*******************************************************************************
 * Linux पूर्णांकerface and usb initialisation
 ******************************************************************************/

काष्ठा driver_info अणु
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा driver_info info_P1K = अणु
	.name	= "Yealink usb-p1k",
पूर्ण;

अटल स्थिर काष्ठा usb_device_id usb_table [] = अणु
	अणु
		.match_flags		= USB_DEVICE_ID_MATCH_DEVICE |
						USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr		= 0x6993,
		.idProduct		= 0xb001,
		.bInterfaceClass	= USB_CLASS_HID,
		.bInterfaceSubClass	= 0,
		.bInterfaceProtocol	= 0,
		.driver_info		= (kernel_uदीर्घ_t)&info_P1K
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक usb_cleanup(काष्ठा yealink_dev *yld, पूर्णांक err)
अणु
	अगर (yld == शून्य)
		वापस err;

        अगर (yld->idev) अणु
		अगर (err)
			input_मुक्त_device(yld->idev);
		अन्यथा
			input_unरेजिस्टर_device(yld->idev);
	पूर्ण

	usb_मुक्त_urb(yld->urb_irq);
	usb_मुक्त_urb(yld->urb_ctl);

	kमुक्त(yld->ctl_req);
	usb_मुक्त_coherent(yld->udev, USB_PKT_LEN, yld->ctl_data, yld->ctl_dma);
	usb_मुक्त_coherent(yld->udev, USB_PKT_LEN, yld->irq_data, yld->irq_dma);

	kमुक्त(yld);
	वापस err;
पूर्ण

अटल व्योम usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा yealink_dev *yld;

	करोwn_ग_लिखो(&sysfs_rwsema);
	yld = usb_get_पूर्णांकfdata(पूर्णांकf);
	sysfs_हटाओ_group(&पूर्णांकf->dev.kobj, &yld_attr_group);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	up_ग_लिखो(&sysfs_rwsema);

	usb_cleanup(yld, 0);
पूर्ण

अटल पूर्णांक usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev (पूर्णांकf);
	काष्ठा driver_info *nfo = (काष्ठा driver_info *)id->driver_info;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा yealink_dev *yld;
	काष्ठा input_dev *input_dev;
	पूर्णांक ret, pipe, i;

	पूर्णांकerface = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	yld = kzalloc(माप(काष्ठा yealink_dev), GFP_KERNEL);
	अगर (!yld)
		वापस -ENOMEM;

	yld->udev = udev;
	yld->पूर्णांकf = पूर्णांकf;

	yld->idev = input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस usb_cleanup(yld, -ENOMEM);

	/* allocate usb buffers */
	yld->irq_data = usb_alloc_coherent(udev, USB_PKT_LEN,
					   GFP_KERNEL, &yld->irq_dma);
	अगर (yld->irq_data == शून्य)
		वापस usb_cleanup(yld, -ENOMEM);

	yld->ctl_data = usb_alloc_coherent(udev, USB_PKT_LEN,
					   GFP_KERNEL, &yld->ctl_dma);
	अगर (!yld->ctl_data)
		वापस usb_cleanup(yld, -ENOMEM);

	yld->ctl_req = kदो_स्मृति(माप(*(yld->ctl_req)), GFP_KERNEL);
	अगर (yld->ctl_req == शून्य)
		वापस usb_cleanup(yld, -ENOMEM);

	/* allocate urb काष्ठाures */
	yld->urb_irq = usb_alloc_urb(0, GFP_KERNEL);
        अगर (yld->urb_irq == शून्य)
		वापस usb_cleanup(yld, -ENOMEM);

	yld->urb_ctl = usb_alloc_urb(0, GFP_KERNEL);
        अगर (yld->urb_ctl == शून्य)
		वापस usb_cleanup(yld, -ENOMEM);

	/* get a handle to the पूर्णांकerrupt data pipe */
	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	ret = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	अगर (ret != USB_PKT_LEN)
		dev_err(&पूर्णांकf->dev, "invalid payload size %d, expected %zd\n",
			ret, USB_PKT_LEN);

	/* initialise irq urb */
	usb_fill_पूर्णांक_urb(yld->urb_irq, udev, pipe, yld->irq_data,
			USB_PKT_LEN,
			urb_irq_callback,
			yld, endpoपूर्णांक->bInterval);
	yld->urb_irq->transfer_dma = yld->irq_dma;
	yld->urb_irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	yld->urb_irq->dev = udev;

	/* initialise ctl urb */
	yld->ctl_req->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE |
				      USB_सूची_OUT;
	yld->ctl_req->bRequest	= USB_REQ_SET_CONFIGURATION;
	yld->ctl_req->wValue	= cpu_to_le16(0x200);
	yld->ctl_req->wIndex	= cpu_to_le16(पूर्णांकerface->desc.bInterfaceNumber);
	yld->ctl_req->wLength	= cpu_to_le16(USB_PKT_LEN);

	usb_fill_control_urb(yld->urb_ctl, udev, usb_sndctrlpipe(udev, 0),
			(व्योम *)yld->ctl_req, yld->ctl_data, USB_PKT_LEN,
			urb_ctl_callback, yld);
	yld->urb_ctl->transfer_dma	= yld->ctl_dma;
	yld->urb_ctl->transfer_flags	|= URB_NO_TRANSFER_DMA_MAP;
	yld->urb_ctl->dev = udev;

	/* find out the physical bus location */
	usb_make_path(udev, yld->phys, माप(yld->phys));
	strlcat(yld->phys,  "/input0", माप(yld->phys));

	/* रेजिस्टर settings क्रम the input device */
	input_dev->name = nfo->name;
	input_dev->phys = yld->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, yld);

	input_dev->खोलो = input_खोलो;
	input_dev->बंद = input_बंद;
	/* input_dev->event = input_ev;	TODO */

	/* रेजिस्टर available key events */
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	क्रम (i = 0; i < 256; i++) अणु
		पूर्णांक k = map_p1k_to_key(i);
		अगर (k >= 0) अणु
			set_bit(k & 0xff, input_dev->keybit);
			अगर (k >> 8)
				set_bit(k >> 8, input_dev->keybit);
		पूर्ण
	पूर्ण

	ret = input_रेजिस्टर_device(yld->idev);
	अगर (ret)
		वापस usb_cleanup(yld, ret);

	usb_set_पूर्णांकfdata(पूर्णांकf, yld);

	/* clear visible elements */
	क्रम (i = 0; i < ARRAY_SIZE(lcdMap); i++)
		setChar(yld, i, ' ');

	/* display driver version on LCD line 3 */
	store_line3(&पूर्णांकf->dev, शून्य,
			DRIVER_VERSION, माप(DRIVER_VERSION));

	/* Register sysfs hooks (करोn't care about failure) */
	ret = sysfs_create_group(&पूर्णांकf->dev.kobj, &yld_attr_group);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver yealink_driver = अणु
	.name		= "yealink",
	.probe		= usb_probe,
	.disconnect	= usb_disconnect,
	.id_table	= usb_table,
पूर्ण;

module_usb_driver(yealink_driver);

MODULE_DEVICE_TABLE (usb, usb_table);

MODULE_AUTHOR("Henk Vergonet");
MODULE_DESCRIPTION("Yealink phone driver");
MODULE_LICENSE("GPL");
