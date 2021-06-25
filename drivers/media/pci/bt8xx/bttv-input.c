<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (c) 2003 Gerd Knorr
 * Copyright (c) 2003 Pavel Machek
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

#समावेश "bttv.h"
#समावेश "bttvp.h"


अटल पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);

अटल पूर्णांक ir_rc5_remote_gap = 885;
module_param(ir_rc5_remote_gap, पूर्णांक, 0644);

#अघोषित dprपूर्णांकk
#घोषणा dprपूर्णांकk(fmt, ...)			\
करो अणु						\
	अगर (ir_debug >= 1)			\
		pr_info(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा DEVNAME "bttv-input"

#घोषणा MODULE_NAME "bttv"

/* ---------------------------------------------------------------------- */

अटल व्योम ir_handle_key(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_ir *ir = btv->remote;
	u32 gpio,data;

	/* पढ़ो gpio value */
	gpio = bttv_gpio_पढ़ो(&btv->c);
	अगर (ir->polling) अणु
		अगर (ir->last_gpio == gpio)
			वापस;
		ir->last_gpio = gpio;
	पूर्ण

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);
	dprपूर्णांकk("irq gpio=0x%x code=%d | %s%s%s\n",
		gpio, data,
		ir->polling               ? "poll"  : "irq",
		(gpio & ir->mask_keyकरोwn) ? " down" : "",
		(gpio & ir->mask_keyup)   ? " up"   : "");

	अगर ((ir->mask_keyकरोwn && (gpio & ir->mask_keyकरोwn)) ||
	    (ir->mask_keyup   && !(gpio & ir->mask_keyup))) अणु
		rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data, 0);
	पूर्ण अन्यथा अणु
		/* HACK: Probably, ir->mask_keyकरोwn is missing
		   क्रम this board */
		अगर (btv->c.type == BTTV_BOARD_WINFAST2000)
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);

		rc_keyup(ir->dev);
	पूर्ण
पूर्ण

अटल व्योम ir_enltv_handle_key(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_ir *ir = btv->remote;
	u32 gpio, data, keyup;

	/* पढ़ो gpio value */
	gpio = bttv_gpio_पढ़ो(&btv->c);

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);

	/* Check अगर it is keyup */
	keyup = (gpio & ir->mask_keyup) ? 1UL << 31 : 0;

	अगर ((ir->last_gpio & 0x7f) != data) अणु
		dprपूर्णांकk("gpio=0x%x code=%d | %s\n",
			gpio, data,
			(gpio & ir->mask_keyup) ? " up" : "up/down");

		rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data, 0);
		अगर (keyup)
			rc_keyup(ir->dev);
	पूर्ण अन्यथा अणु
		अगर ((ir->last_gpio & 1UL << 31) == keyup)
			वापस;

		dprपूर्णांकk("(cnt) gpio=0x%x code=%d | %s\n",
			gpio, data,
			(gpio & ir->mask_keyup) ? " up" : "down");

		अगर (keyup)
			rc_keyup(ir->dev);
		अन्यथा
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
	पूर्ण

	ir->last_gpio = data | keyup;
पूर्ण

अटल पूर्णांक bttv_rc5_irq(काष्ठा bttv *btv);

व्योम bttv_input_irq(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_ir *ir = btv->remote;

	अगर (ir->rc5_gpio)
		bttv_rc5_irq(btv);
	अन्यथा अगर (!ir->polling)
		ir_handle_key(btv);
पूर्ण

अटल व्योम bttv_input_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bttv_ir *ir = from_समयr(ir, t, समयr);
	काष्ठा bttv *btv = ir->btv;

	अगर (btv->c.type == BTTV_BOARD_ENLTV_FM_2)
		ir_enltv_handle_key(btv);
	अन्यथा
		ir_handle_key(btv);
	mod_समयr(&ir->समयr, jअगरfies + msecs_to_jअगरfies(ir->polling));
पूर्ण

/*
 * FIXME: Nebula digi uses the legacy way to decode RC5, instead of relying
 * on the rc-core way. As we need to be sure that both IRQ transitions are
 * properly triggered, Better to touch it only with this hardware क्रम
 * testing.
 */

#घोषणा RC5_START(x)	(((x) >> 12) & 0x03)
#घोषणा RC5_TOGGLE(x)	(((x) >> 11) & 0x01)
#घोषणा RC5_ADDR(x)	(((x) >> 6)  & 0x1f)
#घोषणा RC5_INSTR(x)	(((x) >> 0)  & 0x3f)

/* decode raw bit pattern to RC5 code */
अटल u32 bttv_rc5_decode(अचिन्हित पूर्णांक code)
अणु
	अचिन्हित पूर्णांक org_code = code;
	अचिन्हित पूर्णांक pair;
	अचिन्हित पूर्णांक rc5 = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 14; ++i) अणु
		pair = code & 0x3;
		code >>= 2;

		rc5 <<= 1;
		चयन (pair) अणु
		हाल 0:
		हाल 2:
			अवरोध;
		हाल 1:
			rc5 |= 1;
		अवरोध;
		हाल 3:
			dprपूर्णांकk("rc5_decode(%x) bad code\n",
				org_code);
			वापस 0;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("code=%x, rc5=%x, start=%x, toggle=%x, address=%x, instr=%x\n",
		rc5, org_code, RC5_START(rc5),
		RC5_TOGGLE(rc5), RC5_ADDR(rc5), RC5_INSTR(rc5));
	वापस rc5;
पूर्ण

अटल व्योम bttv_rc5_समयr_end(काष्ठा समयr_list *t)
अणु
	काष्ठा bttv_ir *ir = from_समयr(ir, t, समयr);
	kसमय_प्रकार tv;
	u32 gap, rc5, scancode;
	u8 toggle, command, प्रणाली;

	/* get समय */
	tv = kसमय_get();

	gap = kसमय_प्रकारo_us(kसमय_sub(tv, ir->base_समय));
	/* aव्योम overflow with gap >1s */
	अगर (gap > USEC_PER_SEC) अणु
		gap = 200000;
	पूर्ण
	/* संकेत we're पढ़ोy to start a new code */
	ir->active = false;

	/* Allow some समयr jitter (RC5 is ~24ms anyway so this is ok) */
	अगर (gap < 28000) अणु
		dprपूर्णांकk("spurious timer_end\n");
		वापस;
	पूर्ण

	अगर (ir->last_bit < 20) अणु
		/* ignore spurious codes (caused by light/other remotes) */
		dprपूर्णांकk("short code: %x\n", ir->code);
		वापस;
	पूर्ण

	ir->code = (ir->code << ir->shअगरt_by) | 1;
	rc5 = bttv_rc5_decode(ir->code);

	toggle = RC5_TOGGLE(rc5);
	प्रणाली = RC5_ADDR(rc5);
	command = RC5_INSTR(rc5);

	चयन (RC5_START(rc5)) अणु
	हाल 0x3:
		अवरोध;
	हाल 0x2:
		command += 0x40;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	scancode = RC_SCANCODE_RC5(प्रणाली, command);
	rc_keyकरोwn(ir->dev, RC_PROTO_RC5, scancode, toggle);
	dprपूर्णांकk("scancode %x, toggle %x\n", scancode, toggle);
पूर्ण

अटल पूर्णांक bttv_rc5_irq(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_ir *ir = btv->remote;
	kसमय_प्रकार tv;
	u32 gpio;
	u32 gap;
	अचिन्हित दीर्घ current_jअगरfies;

	/* पढ़ो gpio port */
	gpio = bttv_gpio_पढ़ो(&btv->c);

	/* get समय of bit */
	current_jअगरfies = jअगरfies;
	tv = kसमय_get();

	gap = kसमय_प्रकारo_us(kसमय_sub(tv, ir->base_समय));
	/* aव्योम overflow with gap >1s */
	अगर (gap > USEC_PER_SEC) अणु
		gap = 200000;
	पूर्ण

	dprपूर्णांकk("RC5 IRQ: gap %d us for %s\n",
		gap, (gpio & 0x20) ? "mark" : "space");

	/* remote IRQ? */
	अगर (!(gpio & 0x20))
		वापस 0;

	/* active code => add bit */
	अगर (ir->active) अणु
		/* only अगर in the code (otherwise spurious IRQ or समयr
		   late) */
		अगर (ir->last_bit < 28) अणु
			ir->last_bit = (gap - ir_rc5_remote_gap / 2) /
			    ir_rc5_remote_gap;
			ir->code |= 1 << ir->last_bit;
		पूर्ण
		/* starting new code */
	पूर्ण अन्यथा अणु
		ir->active = true;
		ir->code = 0;
		ir->base_समय = tv;
		ir->last_bit = 0;

		mod_समयr(&ir->समयr, current_jअगरfies + msecs_to_jअगरfies(30));
	पूर्ण

	/* toggle GPIO pin 4 to reset the irq */
	bttv_gpio_ग_लिखो(&btv->c, gpio & ~(1 << 4));
	bttv_gpio_ग_लिखो(&btv->c, gpio | (1 << 4));
	वापस 1;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम bttv_ir_start(काष्ठा bttv_ir *ir)
अणु
	अगर (ir->polling) अणु
		समयr_setup(&ir->समयr, bttv_input_समयr, 0);
		ir->समयr.expires  = jअगरfies + msecs_to_jअगरfies(1000);
		add_समयr(&ir->समयr);
	पूर्ण अन्यथा अगर (ir->rc5_gpio) अणु
		/* set समयr_end क्रम code completion */
		समयr_setup(&ir->समयr, bttv_rc5_समयr_end, 0);
		ir->shअगरt_by = 1;
		ir->rc5_remote_gap = ir_rc5_remote_gap;
	पूर्ण
पूर्ण

अटल व्योम bttv_ir_stop(काष्ठा bttv *btv)
अणु
	अगर (btv->remote->polling)
		del_समयr_sync(&btv->remote->समयr);

	अगर (btv->remote->rc5_gpio) अणु
		u32 gpio;

		del_समयr_sync(&btv->remote->समयr);

		gpio = bttv_gpio_पढ़ो(&btv->c);
		bttv_gpio_ग_लिखो(&btv->c, gpio & ~(1 << 4));
	पूर्ण
पूर्ण

/*
 * Get_key functions used by I2C remotes
 */

अटल पूर्णांक get_key_pv951(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			 u32 *scancode, u8 *toggle)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	अगर (rc != 1) अणु
		dprपूर्णांकk("read error\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/* ignore 0xaa */
	अगर (b==0xaa)
		वापस 0;
	dprपूर्णांकk("key %02x\n", b);

	/*
	 * NOTE:
	 * lirc_i2c maps the pv951 code as:
	 *	addr = 0x61D6
	 *	cmd = bit_reverse (b)
	 * So, it seems that this device uses NEC extended
	 * I decided to not fix the table, due to two reasons:
	 *	1) Without the actual device, this is only a guess;
	 *	2) As the addr is not reported via I2C, nor can be changed,
	 *	   the device is bound to the venकरोr-provided RC.
	 */

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	वापस 1;
पूर्ण

/* Instantiate the I2C IR receiver device, अगर present */
व्योम init_bttv_i2c_ir(काष्ठा bttv *btv)
अणु
	अटल स्थिर अचिन्हित लघु addr_list[] = अणु
		0x1a, 0x18, 0x64, 0x30, 0x71,
		I2C_CLIENT_END
	पूर्ण;
	काष्ठा i2c_board_info info;
	काष्ठा i2c_client *i2c_dev;

	अगर (0 != btv->i2c_rc)
		वापस;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	स_रखो(&btv->init_data, 0, माप(btv->init_data));
	strscpy(info.type, "ir_video", I2C_NAME_SIZE);

	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_PV951:
		btv->init_data.name = "PV951";
		btv->init_data.get_key = get_key_pv951;
		btv->init_data.ir_codes = RC_MAP_PV951;
		info.addr = 0x4b;
		अवरोध;
	पूर्ण

	अगर (btv->init_data.name) अणु
		info.platक्रमm_data = &btv->init_data;
		i2c_dev = i2c_new_client_device(&btv->c.i2c_adap, &info);
	पूर्ण अन्यथा अणु
		/*
		 * The बाह्यal IR receiver is at i2c address 0x34 (0x35 क्रम
		 * पढ़ोs).  Future Hauppauge cards will have an पूर्णांकernal
		 * receiver at 0x30 (0x31 क्रम पढ़ोs).  In theory, both can be
		 * fitted, and Hauppauge suggest an बाह्यal overrides an
		 * पूर्णांकernal.
		 * That's why we probe 0x1a (~0x34) first. CB
		 */
		i2c_dev = i2c_new_scanned_device(&btv->c.i2c_adap, &info, addr_list, शून्य);
	पूर्ण
	अगर (IS_ERR(i2c_dev))
		वापस;

#अगर defined(CONFIG_MODULES) && defined(MODULE)
	request_module("ir-kbd-i2c");
#पूर्ण_अगर
पूर्ण

पूर्णांक bttv_input_init(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_ir *ir;
	अक्षर *ir_codes = शून्य;
	काष्ठा rc_dev *rc;
	पूर्णांक err = -ENOMEM;

	अगर (!btv->has_remote)
		वापस -ENODEV;

	ir = kzalloc(माप(*ir),GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!ir || !rc)
		जाओ err_out_मुक्त;

	/* detect & configure */
	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_AVERMEDIA:
	हाल BTTV_BOARD_AVPHONE98:
	हाल BTTV_BOARD_AVERMEDIA98:
		ir_codes         = RC_MAP_AVERMEDIA;
		ir->mask_keycode = 0xf88000;
		ir->mask_keyकरोwn = 0x010000;
		ir->polling      = 50; // ms
		अवरोध;

	हाल BTTV_BOARD_AVDVBT_761:
	हाल BTTV_BOARD_AVDVBT_771:
		ir_codes         = RC_MAP_AVERMEDIA_DVBT;
		ir->mask_keycode = 0x0f00c0;
		ir->mask_keyकरोwn = 0x000020;
		ir->polling      = 50; // ms
		अवरोध;

	हाल BTTV_BOARD_PXELVWPLTVPAK:
		ir_codes         = RC_MAP_PIXELVIEW;
		ir->mask_keycode = 0x003e00;
		ir->mask_keyup   = 0x010000;
		ir->polling      = 50; // ms
		अवरोध;
	हाल BTTV_BOARD_PV_M4900:
	हाल BTTV_BOARD_PV_BT878P_9B:
	हाल BTTV_BOARD_PV_BT878P_PLUS:
		ir_codes         = RC_MAP_PIXELVIEW;
		ir->mask_keycode = 0x001f00;
		ir->mask_keyup   = 0x008000;
		ir->polling      = 50; // ms
		अवरोध;

	हाल BTTV_BOARD_WINFAST2000:
		ir_codes         = RC_MAP_WINFAST;
		ir->mask_keycode = 0x1f8;
		अवरोध;
	हाल BTTV_BOARD_MAGICTVIEW061:
	हाल BTTV_BOARD_MAGICTVIEW063:
		ir_codes         = RC_MAP_WINFAST;
		ir->mask_keycode = 0x0008e000;
		ir->mask_keyकरोwn = 0x00200000;
		अवरोध;
	हाल BTTV_BOARD_APAC_VIEWCOMP:
		ir_codes         = RC_MAP_APAC_VIEWCOMP;
		ir->mask_keycode = 0x001f00;
		ir->mask_keyup   = 0x008000;
		ir->polling      = 50; // ms
		अवरोध;
	हाल BTTV_BOARD_ASKEY_CPH03X:
	हाल BTTV_BOARD_CONCEPTRONIC_CTVFMI2:
	हाल BTTV_BOARD_CONTVFMI:
	हाल BTTV_BOARD_KWORLD_VSTREAM_XPERT:
		ir_codes         = RC_MAP_PIXELVIEW;
		ir->mask_keycode = 0x001F00;
		ir->mask_keyup   = 0x006000;
		ir->polling      = 50; // ms
		अवरोध;
	हाल BTTV_BOARD_NEBULA_DIGITV:
		ir_codes         = RC_MAP_NEBULA;
		ir->rc5_gpio     = true;
		अवरोध;
	हाल BTTV_BOARD_MACHTV_MAGICTV:
		ir_codes         = RC_MAP_APAC_VIEWCOMP;
		ir->mask_keycode = 0x001F00;
		ir->mask_keyup   = 0x004000;
		ir->polling      = 50; /* ms */
		अवरोध;
	हाल BTTV_BOARD_KOZUMI_KTV_01C:
		ir_codes         = RC_MAP_PCTV_SEDNA;
		ir->mask_keycode = 0x001f00;
		ir->mask_keyup   = 0x006000;
		ir->polling      = 50; /* ms */
		अवरोध;
	हाल BTTV_BOARD_ENLTV_FM_2:
		ir_codes         = RC_MAP_ENCORE_ENLTV2;
		ir->mask_keycode = 0x00fd00;
		ir->mask_keyup   = 0x000080;
		ir->polling      = 1; /* ms */
		ir->last_gpio    = ir_extract_bits(bttv_gpio_पढ़ो(&btv->c),
						   ir->mask_keycode);
		अवरोध;
	पूर्ण

	अगर (!ir_codes) अणु
		dprपूर्णांकk("Ooops: IR config error [card=%d]\n", btv->c.type);
		err = -ENODEV;
		जाओ err_out_मुक्त;
	पूर्ण

	अगर (ir->rc5_gpio) अणु
		u32 gpio;
		/* enable remote irq */
		bttv_gpio_inout(&btv->c, (1 << 4), 1 << 4);
		gpio = bttv_gpio_पढ़ो(&btv->c);
		bttv_gpio_ग_लिखो(&btv->c, gpio & ~(1 << 4));
		bttv_gpio_ग_लिखो(&btv->c, gpio | (1 << 4));
	पूर्ण अन्यथा अणु
		/* init hardware-specअगरic stuff */
		bttv_gpio_inout(&btv->c, ir->mask_keycode | ir->mask_keyकरोwn, 0);
	पूर्ण

	/* init input device */
	ir->dev = rc;
	ir->btv = btv;

	snम_लिखो(ir->name, माप(ir->name), "bttv IR (card=%d)",
		 btv->c.type);
	snम_लिखो(ir->phys, माप(ir->phys), "pci-%s/ir0",
		 pci_name(btv->c.pci));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	rc->input_id.bustype = BUS_PCI;
	rc->input_id.version = 1;
	अगर (btv->c.pci->subप्रणाली_venकरोr) अणु
		rc->input_id.venकरोr  = btv->c.pci->subप्रणाली_venकरोr;
		rc->input_id.product = btv->c.pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		rc->input_id.venकरोr  = btv->c.pci->venकरोr;
		rc->input_id.product = btv->c.pci->device;
	पूर्ण
	rc->dev.parent = &btv->c.pci->dev;
	rc->map_name = ir_codes;
	rc->driver_name = MODULE_NAME;

	btv->remote = ir;
	bttv_ir_start(ir);

	/* all करोne */
	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ err_out_stop;

	वापस 0;

 err_out_stop:
	bttv_ir_stop(btv);
	btv->remote = शून्य;
 err_out_मुक्त:
	rc_मुक्त_device(rc);
	kमुक्त(ir);
	वापस err;
पूर्ण

व्योम bttv_input_fini(काष्ठा bttv *btv)
अणु
	अगर (btv->remote == शून्य)
		वापस;

	bttv_ir_stop(btv);
	rc_unरेजिस्टर_device(btv->remote->dev);
	kमुक्त(btv->remote);
	btv->remote = शून्य;
पूर्ण
