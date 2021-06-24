<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * handle saa7134 IR remotes via linux kernel input layer.
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#घोषणा MODULE_NAME "saa7134"

अटल अचिन्हित पूर्णांक disable_ir;
module_param(disable_ir, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ir,"disable infrared remote support");

अटल अचिन्हित पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_debug,"enable debug messages [IR]");

अटल पूर्णांक pinnacle_remote;
module_param(pinnacle_remote, पूर्णांक, 0644);    /* Choose Pinnacle PCTV remote */
MODULE_PARM_DESC(pinnacle_remote, "Specify Pinnacle PCTV remote: 0=coloured, 1=grey (defaults to 0)");

#घोषणा input_dbg(fmt, arg...) करो अणु \
	अगर (ir_debug) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("input: " fmt), ## arg); \
	पूर्ण जबतक (0)
#घोषणा ir_dbg(ir, fmt, arg...) करो अणु \
	अगर (ir_debug) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("ir %s: " fmt), ir->rc->device_name, \
		       ## arg); \
	पूर्ण जबतक (0)

/* Helper function क्रम raw decoding at GPIO16 or GPIO18 */
अटल पूर्णांक saa7134_raw_decode_irq(काष्ठा saa7134_dev *dev);

/* -------------------- GPIO generic keycode builder -------------------- */

अटल पूर्णांक build_key(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_card_ir *ir = dev->remote;
	u32 gpio, data;

	/* here comes the additional handshake steps क्रम some cards */
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x80);
		saa_clearb(SAA7134_GPIO_GPSTATUS1, 0x80);
		अवरोध;
	पूर्ण
	/* rising SAA7134_GPIO_GPRESCAN पढ़ोs the status */
	saa_clearb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN);

	gpio = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);
	अगर (ir->polling) अणु
		अगर (ir->last_gpio == gpio)
			वापस 0;
		ir->last_gpio = gpio;
	पूर्ण

	data = ir_extract_bits(gpio, ir->mask_keycode);
	input_dbg("build_key gpio=0x%x mask=0x%x data=%d\n",
		gpio, ir->mask_keycode, data);

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG:
		अगर (data == ir->mask_keycode)
			rc_keyup(ir->dev);
		अन्यथा
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
		वापस 0;
	पूर्ण

	अगर (ir->polling) अणु
		अगर ((ir->mask_keyकरोwn  &&  (0 != (gpio & ir->mask_keyकरोwn))) ||
		    (ir->mask_keyup    &&  (0 == (gpio & ir->mask_keyup)))) अणु
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
		पूर्ण अन्यथा अणु
			rc_keyup(ir->dev);
		पूर्ण
	पूर्ण
	अन्यथा अणु	/* IRQ driven mode - handle key press and release in one go */
		अगर ((ir->mask_keyकरोwn  &&  (0 != (gpio & ir->mask_keyकरोwn))) ||
		    (ir->mask_keyup    &&  (0 == (gpio & ir->mask_keyup)))) अणु
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
			rc_keyup(ir->dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* --------------------- Chip specअगरic I2C key builders ----------------- */

अटल पूर्णांक get_key_flydvb_trio(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			       u32 *scancode, u8 *toggle)
अणु
	पूर्णांक gpio, rc;
	पूर्णांक attempt = 0;
	अचिन्हित अक्षर b;

	/* We need this to access GPI Used by the saa_पढ़ोl macro. */
	काष्ठा saa7134_dev *dev = ir->c->adapter->algo_data;

	अगर (dev == शून्य) अणु
		ir_dbg(ir, "get_key_flydvb_trio: ir->c->adapter->algo_data is NULL!\n");
		वापस -EIO;
	पूर्ण

	/* rising SAA7134_GPIGPRESCAN पढ़ोs the status */
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);

	अगर (0x40000 & ~gpio)
		वापस 0; /* No button press */

	/* poll IR chip */
	/* weak up the IR chip */
	b = 0;

	जबतक (1 != i2c_master_send(ir->c, &b, 1)) अणु
		अगर ((attempt++) < 10) अणु
			/*
			 * रुको a bit क्रम next attempt -
			 * I करोn't know how make it better
			 */
			msleep(10);
			जारी;
		पूर्ण
		ir_dbg(ir, "send wake up byte to pic16C505 (IR chip)failed %dx\n",
		       attempt);
		वापस -EIO;
	पूर्ण
	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_msi_tvanywhere_plus(काष्ठा IR_i2c *ir,
				       क्रमागत rc_proto *protocol,
				       u32 *scancode, u8 *toggle)
अणु
	अचिन्हित अक्षर b;
	पूर्णांक gpio, rc;

	/* <dev> is needed to access GPIO. Used by the saa_पढ़ोl macro. */
	काष्ठा saa7134_dev *dev = ir->c->adapter->algo_data;
	अगर (dev == शून्य) अणु
		ir_dbg(ir, "get_key_msi_tvanywhere_plus: ir->c->adapter->algo_data is NULL!\n");
		वापस -EIO;
	पूर्ण

	/* rising SAA7134_GPIO_GPRESCAN पढ़ोs the status */

	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);

	/* GPIO&0x40 is pulsed low when a button is pressed. Don't करो
	   I2C receive अगर gpio&0x40 is not low. */

	अगर (gpio & 0x40)
		वापस 0;       /* No button press */

	/* GPIO says there is a button press. Get it. */

	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/* No button press */

	अगर (b == 0xff)
		वापस 0;

	/* Button pressed */

	input_dbg("get_key_msi_tvanywhere_plus: Key = 0x%02X\n", b);
	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

/* copied and modअगरied from get_key_msi_tvanywhere_plus() */
अटल पूर्णांक get_key_kworld_pc150u(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
				 u32 *scancode, u8 *toggle)
अणु
	अचिन्हित अक्षर b;
	अचिन्हित पूर्णांक gpio;
	पूर्णांक rc;

	/* <dev> is needed to access GPIO. Used by the saa_पढ़ोl macro. */
	काष्ठा saa7134_dev *dev = ir->c->adapter->algo_data;
	अगर (dev == शून्य) अणु
		ir_dbg(ir, "get_key_kworld_pc150u: ir->c->adapter->algo_data is NULL!\n");
		वापस -EIO;
	पूर्ण

	/* rising SAA7134_GPIO_GPRESCAN पढ़ोs the status */

	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);

	/* GPIO&0x100 is pulsed low when a button is pressed. Don't करो
	   I2C receive अगर gpio&0x100 is not low. */

	अगर (gpio & 0x100)
		वापस 0;       /* No button press */

	/* GPIO says there is a button press. Get it. */

	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/* No button press */

	अगर (b == 0xff)
		वापस 0;

	/* Button pressed */

	input_dbg("get_key_kworld_pc150u: Key = 0x%02X\n", b);
	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_purpletv(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			    u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/* no button press */
	अगर (b==0)
		वापस 0;

	/* repeating */
	अगर (b & 0x80)
		वापस 1;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक get_key_beholdm6xx(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			      u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर data[12];
	u32 gpio;

	काष्ठा saa7134_dev *dev = ir->c->adapter->algo_data;

	/* rising SAA7134_GPIO_GPRESCAN पढ़ोs the status */
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);

	अगर (0x400000 & ~gpio)
		वापस 0; /* No button press */

	ir->c->addr = 0x5a >> 1;

	rc = i2c_master_recv(ir->c, data, 12);
	अगर (rc != 12) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	अगर (data[9] != (अचिन्हित अक्षर)(~data[8]))
		वापस 0;

	*protocol = RC_PROTO_NECX;
	*scancode = RC_SCANCODE_NECX(data[11] << 8 | data[10], data[9]);
	*toggle = 0;
	वापस 1;
पूर्ण

/* Common (grey or coloured) pinnacle PCTV remote handling
 *
 */
अटल पूर्णांक get_key_pinnacle(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			    u32 *scancode, u8 *toggle, पूर्णांक parity_offset,
			    पूर्णांक marker, पूर्णांक code_modulo)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b[4];
	अचिन्हित पूर्णांक start = 0,parity = 0,code = 0;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, b, 4);
	अगर (rc != 4) अणु
		ir_dbg(ir, "read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	क्रम (start = 0; start < ARRAY_SIZE(b); start++) अणु
		अगर (b[start] == marker) अणु
			code=b[(start+parity_offset + 1) % 4];
			parity=b[(start+parity_offset) % 4];
		पूर्ण
	पूर्ण

	/* Empty Request */
	अगर (parity == 0)
		वापस 0;

	/* Repeating... */
	अगर (ir->old == parity)
		वापस 0;

	ir->old = parity;

	/* drop special codes when a key is held करोwn a दीर्घ समय क्रम the grey controller
	   In this हाल, the second bit of the code is निश्चितed */
	अगर (marker == 0xfe && (code & 0x40))
		वापस 0;

	code %= code_modulo;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = code;
	*toggle = 0;

	ir_dbg(ir, "Pinnacle PCTV key %02x\n", code);
	वापस 1;
पूर्ण

/* The grey pinnacle PCTV remote
 *
 *  There are one issue with this remote:
 *   - I2c packet करोes not change when the same key is pressed quickly. The workaround
 *     is to hold करोwn each key क्रम about half a second, so that another code is generated
 *     in the i2c packet, and the function can distinguish key presses.
 *
 * Sylvain Pasche <sylvain.pasche@gmail.com>
 */
अटल पूर्णांक get_key_pinnacle_grey(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
				 u32 *scancode, u8 *toggle)
अणु

	वापस get_key_pinnacle(ir, protocol, scancode, toggle, 1, 0xfe, 0xff);
पूर्ण


/* The new pinnacle PCTV remote (with the colored buttons)
 *
 * Ricarकरो Cerqueira <v4l@cerqueira.org>
 */
अटल पूर्णांक get_key_pinnacle_color(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
				  u32 *scancode, u8 *toggle)
अणु
	/* code_modulo parameter (0x88) is used to reduce code value to fit inside IR_KEYTAB_SIZE
	 *
	 * this is the only value that results in 42 unique
	 * codes < 128
	 */

	वापस get_key_pinnacle(ir, protocol, scancode, toggle, 2, 0x80, 0x88);
पूर्ण

व्योम saa7134_input_irq(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_card_ir *ir;

	अगर (!dev || !dev->remote)
		वापस;

	ir = dev->remote;
	अगर (!ir->running)
		वापस;

	अगर (!ir->polling && !ir->raw_decode) अणु
		build_key(dev);
	पूर्ण अन्यथा अगर (ir->raw_decode) अणु
		saa7134_raw_decode_irq(dev);
	पूर्ण
पूर्ण

अटल व्योम saa7134_input_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा saa7134_card_ir *ir = from_समयr(ir, t, समयr);
	काष्ठा saa7134_dev *dev = ir->dev->priv;

	build_key(dev);
	mod_समयr(&ir->समयr, jअगरfies + msecs_to_jअगरfies(ir->polling));
पूर्ण

पूर्णांक saa7134_ir_खोलो(काष्ठा rc_dev *rc)
अणु
	काष्ठा saa7134_dev *dev = rc->priv;
	काष्ठा saa7134_card_ir *ir = dev->remote;

	/* Moved here from saa7134_input_init1() because the latter
	 * is not called on device resume */
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_MD2819:
	हाल SAA7134_BOARD_KWORLD_VSTREAM_XPERT:
	हाल SAA7134_BOARD_AVERMEDIA_305:
	हाल SAA7134_BOARD_AVERMEDIA_307:
	हाल SAA7134_BOARD_AVERMEDIA_505:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_305:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_505:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_307:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_507:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_507UA:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM:
	हाल SAA7134_BOARD_AVERMEDIA_M102:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE0, 0x4);
		saa_setb(SAA7134_GPIO_GPSTATUS0, 0x4);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_777:
	हाल SAA7134_BOARD_AVERMEDIA_A16AR:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A16D:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		अवरोध;
	हाल SAA7134_BOARD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPMODE1, 0x80);
		अवरोध;
	पूर्ण

	ir->running = true;

	अगर (ir->polling) अणु
		समयr_setup(&ir->समयr, saa7134_input_समयr, 0);
		ir->समयr.expires = jअगरfies + HZ;
		add_समयr(&ir->समयr);
	पूर्ण

	वापस 0;
पूर्ण

व्योम saa7134_ir_बंद(काष्ठा rc_dev *rc)
अणु
	काष्ठा saa7134_dev *dev = rc->priv;
	काष्ठा saa7134_card_ir *ir = dev->remote;

	अगर (ir->polling)
		del_समयr_sync(&ir->समयr);

	ir->running = false;
पूर्ण

पूर्णांक saa7134_input_init1(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_card_ir *ir;
	काष्ठा rc_dev *rc;
	अक्षर *ir_codes = शून्य;
	u32 mask_keycode = 0;
	u32 mask_keyकरोwn = 0;
	u32 mask_keyup   = 0;
	अचिन्हित polling = 0;
	bool raw_decode  = false;
	पूर्णांक err;

	अगर (dev->has_remote != SAA7134_REMOTE_GPIO)
		वापस -ENODEV;
	अगर (disable_ir)
		वापस -ENODEV;

	/* detect & configure */
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_FLYVIDEO2000:
	हाल SAA7134_BOARD_FLYVIDEO3000:
	हाल SAA7134_BOARD_FLYTVPLATINUM_FM:
	हाल SAA7134_BOARD_FLYTVPLATINUM_MINI2:
	हाल SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM:
		ir_codes     = RC_MAP_FLYVIDEO;
		mask_keycode = 0xEC00000;
		mask_keyकरोwn = 0x0040000;
		अवरोध;
	हाल SAA7134_BOARD_CINERGY400:
	हाल SAA7134_BOARD_CINERGY600:
	हाल SAA7134_BOARD_CINERGY600_MK3:
		ir_codes     = RC_MAP_CINERGY;
		mask_keycode = 0x00003f;
		mask_keyup   = 0x040000;
		अवरोध;
	हाल SAA7134_BOARD_ECS_TVP3XP:
	हाल SAA7134_BOARD_ECS_TVP3XP_4CB5:
		ir_codes     = RC_MAP_EZTV;
		mask_keycode = 0x00017c;
		mask_keyup   = 0x000002;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_XPERT:
	हाल SAA7134_BOARD_AVACSSMARTTV:
		ir_codes     = RC_MAP_PIXELVIEW;
		mask_keycode = 0x00001F;
		mask_keyup   = 0x000020;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_MD2819:
	हाल SAA7134_BOARD_KWORLD_VSTREAM_XPERT:
	हाल SAA7134_BOARD_AVERMEDIA_305:
	हाल SAA7134_BOARD_AVERMEDIA_307:
	हाल SAA7134_BOARD_AVERMEDIA_505:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_305:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_505:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_307:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_507:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_507UA:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM:
	हाल SAA7134_BOARD_AVERMEDIA_M102:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS:
		ir_codes     = RC_MAP_AVERMEDIA;
		mask_keycode = 0x0007C8;
		mask_keyकरोwn = 0x000010;
		polling      = 50; // ms
		/* GPIO stuff moved to saa7134_ir_खोलो() */
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M135A:
		ir_codes     = RC_MAP_AVERMEDIA_M135A;
		mask_keyकरोwn = 0x0040000;	/* Enable GPIO18 line on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M733A:
		ir_codes     = RC_MAP_AVERMEDIA_M733A_RM_K6;
		mask_keyकरोwn = 0x0040000;
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_777:
	हाल SAA7134_BOARD_AVERMEDIA_A16AR:
		ir_codes     = RC_MAP_AVERMEDIA;
		mask_keycode = 0x02F200;
		mask_keyकरोwn = 0x000400;
		polling      = 50; // ms
		/* GPIO stuff moved to saa7134_ir_खोलो() */
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A16D:
		ir_codes     = RC_MAP_AVERMEDIA_A16D;
		mask_keycode = 0x02F200;
		mask_keyकरोwn = 0x000400;
		polling      = 50; /* ms */
		/* GPIO stuff moved to saa7134_ir_खोलो() */
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_TERMINATOR:
		ir_codes     = RC_MAP_PIXELVIEW;
		mask_keycode = 0x00001f;
		mask_keyup   = 0x000060;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_MANLI_MTV001:
	हाल SAA7134_BOARD_MANLI_MTV002:
		ir_codes     = RC_MAP_MANLI;
		mask_keycode = 0x001f00;
		mask_keyup   = 0x004000;
		polling      = 50; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_409FM:
	हाल SAA7134_BOARD_BEHOLD_401:
	हाल SAA7134_BOARD_BEHOLD_403:
	हाल SAA7134_BOARD_BEHOLD_403FM:
	हाल SAA7134_BOARD_BEHOLD_405:
	हाल SAA7134_BOARD_BEHOLD_405FM:
	हाल SAA7134_BOARD_BEHOLD_407:
	हाल SAA7134_BOARD_BEHOLD_407FM:
	हाल SAA7134_BOARD_BEHOLD_409:
	हाल SAA7134_BOARD_BEHOLD_505FM:
	हाल SAA7134_BOARD_BEHOLD_505RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_505RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_507_9FM:
	हाल SAA7134_BOARD_BEHOLD_507RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_507RDS_MK5:
		ir_codes     = RC_MAP_MANLI;
		mask_keycode = 0x003f00;
		mask_keyup   = 0x004000;
		polling      = 50; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM:
		ir_codes     = RC_MAP_BEHOLD_COLUMBUS;
		mask_keycode = 0x003f00;
		mask_keyup   = 0x004000;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_SEDNA_PC_TV_CARDBUS:
		ir_codes     = RC_MAP_PCTV_SEDNA;
		mask_keycode = 0x001f00;
		mask_keyup   = 0x004000;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_GOTVIEW_7135:
		ir_codes     = RC_MAP_GOTVIEW7135;
		mask_keycode = 0x0003CC;
		mask_keyकरोwn = 0x000010;
		polling	     = 5; /* ms */
		/* GPIO stuff moved to saa7134_ir_खोलो() */
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_TV_PVR:
	हाल SAA7134_BOARD_VIDEOMATE_GOLD_PLUS:
	हाल SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII:
		ir_codes     = RC_MAP_VIDEOMATE_TV_PVR;
		mask_keycode = 0x00003F;
		mask_keyup   = 0x400000;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_PROTEUS_2309:
		ir_codes     = RC_MAP_PROTEUS_2309;
		mask_keycode = 0x00007F;
		mask_keyup   = 0x000080;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_300:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200:
		ir_codes     = RC_MAP_VIDEOMATE_TV_PVR;
		mask_keycode = 0x003F00;
		mask_keyup   = 0x040000;
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBS_LR300:
	हाल SAA7134_BOARD_FLYDVBT_LR301:
	हाल SAA7134_BOARD_FLYDVBTDUO:
		ir_codes     = RC_MAP_FLYDVB;
		mask_keycode = 0x0001F00;
		mask_keyकरोwn = 0x0040000;
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_P7131_DUAL:
	हाल SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA:
	हाल SAA7134_BOARD_ASUSTeK_P7131_ANALOG:
		ir_codes     = RC_MAP_ASUS_PC39;
		mask_keyकरोwn = 0x0040000;	/* Enable GPIO18 line on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_PS3_100:
		ir_codes     = RC_MAP_ASUS_PS3_100;
		mask_keyकरोwn = 0x0040000;
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_ENCORE_ENLTV:
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM:
		ir_codes     = RC_MAP_ENCORE_ENLTV;
		mask_keycode = 0x00007f;
		mask_keyup   = 0x040000;
		polling      = 50; // ms
		अवरोध;
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM53:
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM3:
		ir_codes     = RC_MAP_ENCORE_ENLTV_FM53;
		mask_keyकरोwn = 0x0040000;	/* Enable GPIO18 line on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_10MOONSTVMASTER3:
		ir_codes     = RC_MAP_ENCORE_ENLTV;
		mask_keycode = 0x5f80000;
		mask_keyup   = 0x8000000;
		polling      = 50; //ms
		अवरोध;
	हाल SAA7134_BOARD_GENIUS_TVGO_A11MCE:
		ir_codes     = RC_MAP_GENIUS_TVGO_A11MCE;
		mask_keycode = 0xff;
		mask_keyकरोwn = 0xf00000;
		polling = 50; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_REAL_ANGEL_220:
		ir_codes     = RC_MAP_REAL_AUDIO_220_32_KEYS;
		mask_keycode = 0x3f00;
		mask_keyup   = 0x4000;
		polling = 50; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG:
		ir_codes     = RC_MAP_KWORLD_PLUS_TV_ANALOG;
		mask_keycode = 0x7f;
		polling = 40; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_S350:
		ir_codes     = RC_MAP_VIDEOMATE_S350;
		mask_keycode = 0x003f00;
		mask_keyकरोwn = 0x040000;
		अवरोध;
	हाल SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S:
		ir_codes     = RC_MAP_WINFAST;
		mask_keycode = 0x5f00;
		mask_keyup   = 0x020000;
		polling      = 50; /* ms */
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_M1F:
		ir_codes     = RC_MAP_VIDEOMATE_K100;
		mask_keycode = 0x0ff00;
		mask_keyup   = 0x040000;
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
		ir_codes     = RC_MAP_HAUPPAUGE;
		mask_keyकरोwn = 0x0040000;	/* Enable GPIO18 line on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	हाल SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM:
		ir_codes     = RC_MAP_LEADTEK_Y04G0051;
		mask_keyकरोwn = 0x0040000;	/* Enable GPIO18 line on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		raw_decode   = true;
		अवरोध;
	पूर्ण
	अगर (शून्य == ir_codes) अणु
		pr_err("Oops: IR config error [card=%d]\n", dev->board);
		वापस -ENODEV;
	पूर्ण

	ir = kzalloc(माप(*ir), GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!ir || !rc) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	ir->dev = rc;
	dev->remote = ir;

	/* init hardware-specअगरic stuff */
	ir->mask_keycode = mask_keycode;
	ir->mask_keyकरोwn = mask_keyकरोwn;
	ir->mask_keyup   = mask_keyup;
	ir->polling      = polling;
	ir->raw_decode	 = raw_decode;

	/* init input device */
	snम_लिखो(ir->phys, माप(ir->phys), "pci-%s/ir0",
		 pci_name(dev->pci));

	rc->priv = dev;
	rc->खोलो = saa7134_ir_खोलो;
	rc->बंद = saa7134_ir_बंद;
	अगर (raw_decode) अणु
		rc->driver_type = RC_DRIVER_IR_RAW;
		rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	पूर्ण

	rc->device_name = saa7134_boards[dev->board].name;
	rc->input_phys = ir->phys;
	rc->input_id.bustype = BUS_PCI;
	rc->input_id.version = 1;
	अगर (dev->pci->subप्रणाली_venकरोr) अणु
		rc->input_id.venकरोr  = dev->pci->subप्रणाली_venकरोr;
		rc->input_id.product = dev->pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		rc->input_id.venकरोr  = dev->pci->venकरोr;
		rc->input_id.product = dev->pci->device;
	पूर्ण
	rc->dev.parent = &dev->pci->dev;
	rc->map_name = ir_codes;
	rc->driver_name = MODULE_NAME;
	rc->min_समयout = 1;
	rc->समयout = IR_DEFAULT_TIMEOUT;
	rc->max_समयout = 10 * IR_DEFAULT_TIMEOUT;

	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ err_out_मुक्त;

	वापस 0;

err_out_मुक्त:
	rc_मुक्त_device(rc);
	dev->remote = शून्य;
	kमुक्त(ir);
	वापस err;
पूर्ण

व्योम saa7134_input_fini(काष्ठा saa7134_dev *dev)
अणु
	अगर (शून्य == dev->remote)
		वापस;

	rc_unरेजिस्टर_device(dev->remote->dev);
	kमुक्त(dev->remote);
	dev->remote = शून्य;
पूर्ण

व्योम saa7134_probe_i2c_ir(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा i2c_msg msg_msi = अणु
		.addr = 0x50,
		.flags = I2C_M_RD,
		.len = 0,
		.buf = शून्य,
	पूर्ण;
	पूर्णांक rc;

	अगर (disable_ir) अणु
		input_dbg("IR has been disabled, not probing for i2c remote\n");
		वापस;
	पूर्ण

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	स_रखो(&dev->init_data, 0, माप(dev->init_data));
	strscpy(info.type, "ir_video", I2C_NAME_SIZE);

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_PINNACLE_PCTV_110i:
	हाल SAA7134_BOARD_PINNACLE_PCTV_310i:
		dev->init_data.name = "Pinnacle PCTV";
		अगर (pinnacle_remote == 0) अणु
			dev->init_data.get_key = get_key_pinnacle_color;
			dev->init_data.ir_codes = RC_MAP_PINNACLE_COLOR;
			info.addr = 0x47;
		पूर्ण अन्यथा अणु
			dev->init_data.get_key = get_key_pinnacle_grey;
			dev->init_data.ir_codes = RC_MAP_PINNACLE_GREY;
			info.addr = 0x47;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_UPMOST_PURPLE_TV:
		dev->init_data.name = "Purple TV";
		dev->init_data.get_key = get_key_purpletv;
		dev->init_data.ir_codes = RC_MAP_PURPLETV;
		info.addr = 0x7a;
		अवरोध;
	हाल SAA7134_BOARD_MSI_TVATANYWHERE_PLUS:
		dev->init_data.name = "MSI TV@nywhere Plus";
		dev->init_data.get_key = get_key_msi_tvanywhere_plus;
		dev->init_data.ir_codes = RC_MAP_MSI_TVANYWHERE_PLUS;
		/*
		 * MSI TV@nyware Plus requires more frequent polling
		 * otherwise it will miss some keypresses
		 */
		dev->init_data.polling_पूर्णांकerval = 50;
		info.addr = 0x30;
		/* MSI TV@nywhere Plus controller करोesn't seem to
		   respond to probes unless we पढ़ो something from
		   an existing device. Weird...
		   REVISIT: might no दीर्घer be needed */
		rc = i2c_transfer(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("probe 0x%02x @ %s: %s\n",
			msg_msi.addr, dev->i2c_adap.name,
			(1 == rc) ? "yes" : "no");
		अवरोध;
	हाल SAA7134_BOARD_SNAZIO_TVPVR_PRO:
		dev->init_data.name = "SnaZio* TVPVR PRO";
		dev->init_data.get_key = get_key_msi_tvanywhere_plus;
		dev->init_data.ir_codes = RC_MAP_MSI_TVANYWHERE_PLUS;
		/*
		 * MSI TV@nyware Plus requires more frequent polling
		 * otherwise it will miss some keypresses
		 */
		dev->init_data.polling_पूर्णांकerval = 50;
		info.addr = 0x30;
		/*
		 * MSI TV@nywhere Plus controller करोesn't seem to
		 *  respond to probes unless we पढ़ो something from
		 *  an existing device. Weird...
		 * REVISIT: might no दीर्घer be needed
		 */
		rc = i2c_transfer(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("probe 0x%02x @ %s: %s\n",
			msg_msi.addr, dev->i2c_adap.name,
			(rc == 1) ? "yes" : "no");
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_PC150U:
		/* copied and modअगरied from MSI TV@nywhere Plus */
		dev->init_data.name = "Kworld PC150-U";
		dev->init_data.get_key = get_key_kworld_pc150u;
		dev->init_data.ir_codes = RC_MAP_KWORLD_PC150U;
		info.addr = 0x30;
		/* MSI TV@nywhere Plus controller करोesn't seem to
		   respond to probes unless we पढ़ो something from
		   an existing device. Weird...
		   REVISIT: might no दीर्घer be needed */
		rc = i2c_transfer(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("probe 0x%02x @ %s: %s\n",
			msg_msi.addr, dev->i2c_adap.name,
			(1 == rc) ? "yes" : "no");
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1110:
		dev->init_data.name = saa7134_boards[dev->board].name;
		dev->init_data.ir_codes = RC_MAP_HAUPPAUGE;
		dev->init_data.type = RC_PROTO_BIT_RC5 |
				RC_PROTO_BIT_RC6_MCE | RC_PROTO_BIT_RC6_6A_32;
		dev->init_data.पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		info.addr = 0x71;
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_607FM_MK3:
	हाल SAA7134_BOARD_BEHOLD_607FM_MK5:
	हाल SAA7134_BOARD_BEHOLD_609FM_MK3:
	हाल SAA7134_BOARD_BEHOLD_609FM_MK5:
	हाल SAA7134_BOARD_BEHOLD_607RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_607RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_609RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_609RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_M6:
	हाल SAA7134_BOARD_BEHOLD_M63:
	हाल SAA7134_BOARD_BEHOLD_M6_EXTRA:
	हाल SAA7134_BOARD_BEHOLD_H6:
	हाल SAA7134_BOARD_BEHOLD_X7:
	हाल SAA7134_BOARD_BEHOLD_H7:
	हाल SAA7134_BOARD_BEHOLD_A7:
		dev->init_data.name = "BeholdTV";
		dev->init_data.get_key = get_key_beholdm6xx;
		dev->init_data.ir_codes = RC_MAP_BEHOLD;
		dev->init_data.type = RC_PROTO_BIT_NECX;
		info.addr = 0x2d;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_501:
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		info.addr = 0x40;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A706:
		info.addr = 0x41;
		अवरोध;
	हाल SAA7134_BOARD_FLYDVB_TRIO:
		dev->init_data.name = "FlyDVB Trio";
		dev->init_data.get_key = get_key_flydvb_trio;
		dev->init_data.ir_codes = RC_MAP_FLYDVB;
		info.addr = 0x0b;
		अवरोध;
	शेष:
		input_dbg("No I2C IR support for board %x\n", dev->board);
		वापस;
	पूर्ण

	अगर (dev->init_data.name)
		info.platक्रमm_data = &dev->init_data;
	i2c_new_client_device(&dev->i2c_adap, &info);
पूर्ण

अटल पूर्णांक saa7134_raw_decode_irq(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा saa7134_card_ir *ir = dev->remote;
	पूर्णांक space;

	/* Generate initial event */
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	space = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2) & ir->mask_keyकरोwn;
	ir_raw_event_store_edge(dev->remote->dev, !space);

	वापस 1;
पूर्ण
