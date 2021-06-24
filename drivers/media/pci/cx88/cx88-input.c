<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Device driver क्रम GPIO attached remote control पूर्णांकerfaces
 * on Conexant 2388x based TV/DVB cards.
 *
 * Copyright (c) 2003 Pavel Machek
 * Copyright (c) 2004 Gerd Knorr
 * Copyright (c) 2004, 2005 Chris Pascoe
 */

#समावेश "cx88.h"

#समावेश <linux/init.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <media/rc-core.h>

#घोषणा MODULE_NAME "cx88xx"

/* ---------------------------------------------------------------------- */

काष्ठा cx88_IR अणु
	काष्ठा cx88_core *core;
	काष्ठा rc_dev *dev;

	पूर्णांक users;

	अक्षर name[32];
	अक्षर phys[32];

	/* sample from gpio pin 16 */
	u32 sampling;

	/* poll बाह्यal decoder */
	पूर्णांक polling;
	काष्ठा hrसमयr समयr;
	u32 gpio_addr;
	u32 last_gpio;
	u32 mask_keycode;
	u32 mask_keyकरोwn;
	u32 mask_keyup;
पूर्ण;

अटल अचिन्हित पूर्णांक ir_samplerate = 4;
module_param(ir_samplerate, uपूर्णांक, 0444);
MODULE_PARM_DESC(ir_samplerate, "IR samplerate in kHz, 1 - 20, default 4");

अटल पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);	/* debug level [IR] */
MODULE_PARM_DESC(ir_debug, "enable debug messages [IR]");

#घोषणा ir_dprपूर्णांकk(fmt, arg...)	करो अणु					\
	अगर (ir_debug)							\
		prपूर्णांकk(KERN_DEBUG "%s IR: " fmt, ir->core->name, ##arg);\
पूर्ण जबतक (0)

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (ir_debug)							\
		prपूर्णांकk(KERN_DEBUG "cx88 IR: " fmt, ##arg);		\
पूर्ण जबतक (0)

/* ---------------------------------------------------------------------- */

अटल व्योम cx88_ir_handle_key(काष्ठा cx88_IR *ir)
अणु
	काष्ठा cx88_core *core = ir->core;
	u32 gpio, data, auxgpio;

	/* पढ़ो gpio value */
	gpio = cx_पढ़ो(ir->gpio_addr);
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_NPGTECH_REALTV_TOP10FM:
		/*
		 * This board apparently uses a combination of 2 GPIO
		 * to represent the keys. Additionally, the second GPIO
		 * can be used क्रम parity.
		 *
		 * Example:
		 *
		 * क्रम key "5"
		 *	gpio = 0x758, auxgpio = 0xe5 or 0xf5
		 * क्रम key "Power"
		 *	gpio = 0x758, auxgpio = 0xed or 0xfd
		 */

		auxgpio = cx_पढ़ो(MO_GP1_IO);
		/* Take out the parity part */
		gpio = (gpio & 0x7fd) + (auxgpio & 0xef);
		अवरोध;
	हाल CX88_BOARD_WINFAST_DTV1000:
	हाल CX88_BOARD_WINFAST_DTV1800H:
	हाल CX88_BOARD_WINFAST_DTV1800H_XC4000:
	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43:
		gpio = (gpio & 0x6ff) | ((cx_पढ़ो(MO_GP1_IO) << 8) & 0x900);
		auxgpio = gpio;
		अवरोध;
	शेष:
		auxgpio = gpio;
	पूर्ण
	अगर (ir->polling) अणु
		अगर (ir->last_gpio == auxgpio)
			वापस;
		ir->last_gpio = auxgpio;
	पूर्ण

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);
	ir_dprपूर्णांकk("irq gpio=0x%x code=%d | %s%s%s\n",
		   gpio, data,
		   ir->polling ? "poll" : "irq",
		   (gpio & ir->mask_keyकरोwn) ? " down" : "",
		   (gpio & ir->mask_keyup) ? " up" : "");

	अगर (ir->core->boardnr == CX88_BOARD_NORWOOD_MICRO) अणु
		u32 gpio_key = cx_पढ़ो(MO_GP0_IO);

		data = (data << 4) | ((gpio_key & 0xf0) >> 4);

		rc_keyकरोwn(ir->dev, RC_PROTO_UNKNOWN, data, 0);

	पूर्ण अन्यथा अगर (ir->core->boardnr == CX88_BOARD_PROLINK_PLAYTVPVR ||
		   ir->core->boardnr == CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO) अणु
		/* bit cleared on keyकरोwn, NEC scancode, 0xAAAACC, A = 0x866b */
		u16 addr;
		u8 cmd;
		u32 scancode;

		addr = (data >> 8) & 0xffff;
		cmd  = (data >> 0) & 0x00ff;
		scancode = RC_SCANCODE_NECX(addr, cmd);

		अगर (0 == (gpio & ir->mask_keyup))
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_NECX, scancode,
					     0);
		अन्यथा
			rc_keyup(ir->dev);

	पूर्ण अन्यथा अगर (ir->mask_keyकरोwn) अणु
		/* bit set on keyकरोwn */
		अगर (gpio & ir->mask_keyकरोwn)
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
		अन्यथा
			rc_keyup(ir->dev);

	पूर्ण अन्यथा अगर (ir->mask_keyup) अणु
		/* bit cleared on keyकरोwn */
		अगर (0 == (gpio & ir->mask_keyup))
			rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data,
					     0);
		अन्यथा
			rc_keyup(ir->dev);

	पूर्ण अन्यथा अणु
		/* can't distinguish keyकरोwn/up :-/ */
		rc_keyकरोwn_noसमयout(ir->dev, RC_PROTO_UNKNOWN, data, 0);
		rc_keyup(ir->dev);
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart cx88_ir_work(काष्ठा hrसमयr *समयr)
अणु
	u64 missed;
	काष्ठा cx88_IR *ir = container_of(समयr, काष्ठा cx88_IR, समयr);

	cx88_ir_handle_key(ir);
	missed = hrसमयr_क्रमward_now(&ir->समयr,
				     kसमय_set(0, ir->polling * 1000000));
	अगर (missed > 1)
		ir_dprपूर्णांकk("Missed ticks %llu\n", missed - 1);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक __cx88_ir_start(व्योम *priv)
अणु
	काष्ठा cx88_core *core = priv;
	काष्ठा cx88_IR *ir;

	अगर (!core || !core->ir)
		वापस -EINVAL;

	ir = core->ir;

	अगर (ir->polling) अणु
		hrसमयr_init(&ir->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ir->समयr.function = cx88_ir_work;
		hrसमयr_start(&ir->समयr,
			      kसमय_set(0, ir->polling * 1000000),
			      HRTIMER_MODE_REL);
	पूर्ण
	अगर (ir->sampling) अणु
		core->pci_irqmask |= PCI_INT_IR_SMPINT;
		cx_ग_लिखो(MO_DDS_IO, 0x33F286 * ir_samplerate); /* samplerate */
		cx_ग_लिखो(MO_DDSCFG_IO, 0x5); /* enable */
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __cx88_ir_stop(व्योम *priv)
अणु
	काष्ठा cx88_core *core = priv;
	काष्ठा cx88_IR *ir;

	अगर (!core || !core->ir)
		वापस;

	ir = core->ir;
	अगर (ir->sampling) अणु
		cx_ग_लिखो(MO_DDSCFG_IO, 0x0);
		core->pci_irqmask &= ~PCI_INT_IR_SMPINT;
	पूर्ण

	अगर (ir->polling)
		hrसमयr_cancel(&ir->समयr);
पूर्ण

पूर्णांक cx88_ir_start(काष्ठा cx88_core *core)
अणु
	अगर (core->ir->users)
		वापस __cx88_ir_start(core);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_ir_start);

व्योम cx88_ir_stop(काष्ठा cx88_core *core)
अणु
	अगर (core->ir->users)
		__cx88_ir_stop(core);
पूर्ण
EXPORT_SYMBOL(cx88_ir_stop);

अटल पूर्णांक cx88_ir_खोलो(काष्ठा rc_dev *rc)
अणु
	काष्ठा cx88_core *core = rc->priv;

	core->ir->users++;
	वापस __cx88_ir_start(core);
पूर्ण

अटल व्योम cx88_ir_बंद(काष्ठा rc_dev *rc)
अणु
	काष्ठा cx88_core *core = rc->priv;

	core->ir->users--;
	अगर (!core->ir->users)
		__cx88_ir_stop(core);
पूर्ण

/* ---------------------------------------------------------------------- */

पूर्णांक cx88_ir_init(काष्ठा cx88_core *core, काष्ठा pci_dev *pci)
अणु
	काष्ठा cx88_IR *ir;
	काष्ठा rc_dev *dev;
	अक्षर *ir_codes = शून्य;
	u64 rc_proto = RC_PROTO_BIT_OTHER;
	पूर्णांक err = -ENOMEM;
	u32 hardware_mask = 0;	/* For devices with a hardware mask, when
				 * used with a full-code IR table
				 */

	ir = kzalloc(माप(*ir), GFP_KERNEL);
	dev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!ir || !dev)
		जाओ err_out_मुक्त;

	ir->dev = dev;

	/* detect & configure */
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_DNTV_LIVE_DVB_T:
	हाल CX88_BOARD_KWORLD_DVB_T:
	हाल CX88_BOARD_KWORLD_DVB_T_CX22702:
		ir_codes = RC_MAP_DNTV_LIVE_DVB_T;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x60;
		ir->polling = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1:
		ir_codes = RC_MAP_CINERGY_1400;
		ir->sampling = 0xeb04; /* address */
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE:
	हाल CX88_BOARD_HAUPPAUGE_DVB_T1:
	हाल CX88_BOARD_HAUPPAUGE_NOVASE2_S1:
	हाल CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1:
	हाल CX88_BOARD_HAUPPAUGE_HVR1100:
	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000LITE:
	हाल CX88_BOARD_PCHDTV_HD3000:
	हाल CX88_BOARD_PCHDTV_HD5500:
	हाल CX88_BOARD_HAUPPAUGE_IRONLY:
		ir_codes = RC_MAP_HAUPPAUGE;
		ir->sampling = 1;
		अवरोध;
	हाल CX88_BOARD_WINFAST_DTV2000H:
	हाल CX88_BOARD_WINFAST_DTV2000H_J:
	हाल CX88_BOARD_WINFAST_DTV1800H:
	हाल CX88_BOARD_WINFAST_DTV1800H_XC4000:
	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
		ir_codes = RC_MAP_WINFAST;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0x8f8;
		ir->mask_keyup = 0x100;
		ir->polling = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_WINFAST2000XP_EXPERT:
	हाल CX88_BOARD_WINFAST_DTV1000:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43:
		ir_codes = RC_MAP_WINFAST;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0x8f8;
		ir->mask_keyup = 0x100;
		ir->polling = 1; /* ms */
		अवरोध;
	हाल CX88_BOARD_IODATA_GVBCTV7E:
		ir_codes = RC_MAP_IODATA_BCTV7E;
		ir->gpio_addr = MO_GP0_IO;
		ir->mask_keycode = 0xfd;
		ir->mask_keyकरोwn = 0x02;
		ir->polling = 5; /* ms */
		अवरोध;
	हाल CX88_BOARD_PROLINK_PLAYTVPVR:
	हाल CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO:
		/*
		 * It seems that this hardware is paired with NEC extended
		 * address 0x866b. So, unक्रमtunately, its usage with other
		 * IR's with different address won't work. Still, there are
		 * other IR's from the same manufacturer that works, like the
		 * 002-T mini RC, provided with newer PV hardware
		 */
		ir_codes = RC_MAP_PIXELVIEW_MK12;
		rc_proto = RC_PROTO_BIT_NECX;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keyup = 0x80;
		ir->polling = 10; /* ms */
		hardware_mask = 0x3f;	/* Hardware वापसs only 6 bits from command part */
		अवरोध;
	हाल CX88_BOARD_PROLINK_PV_8000GT:
	हाल CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
		ir_codes = RC_MAP_PIXELVIEW_NEW;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x3f;
		ir->mask_keyup = 0x80;
		ir->polling = 1; /* ms */
		अवरोध;
	हाल CX88_BOARD_KWORLD_LTV883:
		ir_codes = RC_MAP_PIXELVIEW;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x60;
		ir->polling = 1; /* ms */
		अवरोध;
	हाल CX88_BOARD_ADSTECH_DVB_T_PCI:
		ir_codes = RC_MAP_ADSTECH_DVB_T_PCI;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0xbf;
		ir->mask_keyup = 0x40;
		ir->polling = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_MSI_TVANYWHERE_MASTER:
		ir_codes = RC_MAP_MSI_TVANYWHERE;
		ir->gpio_addr = MO_GP1_IO;
		ir->mask_keycode = 0x1f;
		ir->mask_keyup = 0x40;
		ir->polling = 1; /* ms */
		अवरोध;
	हाल CX88_BOARD_AVERTV_303:
	हाल CX88_BOARD_AVERTV_STUDIO_303:
		ir_codes         = RC_MAP_AVERTV_303;
		ir->gpio_addr    = MO_GP2_IO;
		ir->mask_keycode = 0xfb;
		ir->mask_keyकरोwn = 0x02;
		ir->polling      = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_OMICOM_SS4_PCI:
	हाल CX88_BOARD_SATTRADE_ST4200:
	हाल CX88_BOARD_TBS_8920:
	हाल CX88_BOARD_TBS_8910:
	हाल CX88_BOARD_PROF_7300:
	हाल CX88_BOARD_PROF_7301:
	हाल CX88_BOARD_PROF_6200:
		ir_codes = RC_MAP_TBS_NEC;
		ir->sampling = 0xff00; /* address */
		अवरोध;
	हाल CX88_BOARD_TEVII_S464:
	हाल CX88_BOARD_TEVII_S460:
	हाल CX88_BOARD_TEVII_S420:
		ir_codes = RC_MAP_TEVII_NEC;
		ir->sampling = 0xff00; /* address */
		अवरोध;
	हाल CX88_BOARD_DNTV_LIVE_DVB_T_PRO:
		ir_codes         = RC_MAP_DNTV_LIVE_DVBT_PRO;
		ir->sampling     = 0xff00; /* address */
		अवरोध;
	हाल CX88_BOARD_NORWOOD_MICRO:
		ir_codes         = RC_MAP_NORWOOD;
		ir->gpio_addr    = MO_GP1_IO;
		ir->mask_keycode = 0x0e;
		ir->mask_keyup   = 0x80;
		ir->polling      = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_NPGTECH_REALTV_TOP10FM:
		ir_codes         = RC_MAP_NPGTECH;
		ir->gpio_addr    = MO_GP0_IO;
		ir->mask_keycode = 0xfa;
		ir->polling      = 50; /* ms */
		अवरोध;
	हाल CX88_BOARD_PINNACLE_PCTV_HD_800i:
		ir_codes         = RC_MAP_PINNACLE_PCTV_HD;
		ir->sampling     = 1;
		अवरोध;
	हाल CX88_BOARD_POWERCOLOR_REAL_ANGEL:
		ir_codes         = RC_MAP_POWERCOLOR_REAL_ANGEL;
		ir->gpio_addr    = MO_GP2_IO;
		ir->mask_keycode = 0x7e;
		ir->polling      = 100; /* ms */
		अवरोध;
	हाल CX88_BOARD_TWINHAN_VP1027_DVBS:
		ir_codes         = RC_MAP_TWINHAN_VP1027_DVBS;
		ir->sampling     = 0xff00; /* address */
		अवरोध;
	पूर्ण

	अगर (!ir_codes) अणु
		err = -ENODEV;
		जाओ err_out_मुक्त;
	पूर्ण

	/*
	 * The usage of mask_keycode were very convenient, due to several
	 * reasons. Among others, the scancode tables were using the scancode
	 * as the index elements. So, the less bits it was used, the smaller
	 * the table were stored. After the input changes, the better is to use
	 * the full scancodes, since it allows replacing the IR remote by
	 * another one. Unक्रमtunately, there are still some hardware, like
	 * Pixelview Ultra Pro, where only part of the scancode is sent via
	 * GPIO. So, there's no way to get the full scancode. Due to that,
	 * hardware_mask were पूर्णांकroduced here: it represents those hardware
	 * that has such limits.
	 */
	अगर (hardware_mask && !ir->mask_keycode)
		ir->mask_keycode = hardware_mask;

	/* init input device */
	snम_लिखो(ir->name, माप(ir->name), "cx88 IR (%s)", core->board.name);
	snम_लिखो(ir->phys, माप(ir->phys), "pci-%s/ir0", pci_name(pci));

	dev->device_name = ir->name;
	dev->input_phys = ir->phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	अगर (pci->subप्रणाली_venकरोr) अणु
		dev->input_id.venकरोr = pci->subप्रणाली_venकरोr;
		dev->input_id.product = pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		dev->input_id.venकरोr = pci->venकरोr;
		dev->input_id.product = pci->device;
	पूर्ण
	dev->dev.parent = &pci->dev;
	dev->map_name = ir_codes;
	dev->driver_name = MODULE_NAME;
	dev->priv = core;
	dev->खोलो = cx88_ir_खोलो;
	dev->बंद = cx88_ir_बंद;
	dev->scancode_mask = hardware_mask;

	अगर (ir->sampling) अणु
		dev->समयout = MS_TO_US(10); /* 10 ms */
	पूर्ण अन्यथा अणु
		dev->driver_type = RC_DRIVER_SCANCODE;
		dev->allowed_protocols = rc_proto;
	पूर्ण

	ir->core = core;
	core->ir = ir;

	/* all करोne */
	err = rc_रेजिस्टर_device(dev);
	अगर (err)
		जाओ err_out_मुक्त;

	वापस 0;

err_out_मुक्त:
	rc_मुक्त_device(dev);
	core->ir = शून्य;
	kमुक्त(ir);
	वापस err;
पूर्ण

पूर्णांक cx88_ir_fini(काष्ठा cx88_core *core)
अणु
	काष्ठा cx88_IR *ir = core->ir;

	/* skip detach on non attached boards */
	अगर (!ir)
		वापस 0;

	cx88_ir_stop(core);
	rc_unरेजिस्टर_device(ir->dev);
	kमुक्त(ir);

	/* करोne */
	core->ir = शून्य;
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

व्योम cx88_ir_irq(काष्ठा cx88_core *core)
अणु
	काष्ठा cx88_IR *ir = core->ir;
	u32 samples;
	अचिन्हित पूर्णांक toकरो, bits;
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	अगर (!ir || !ir->sampling)
		वापस;

	/*
	 * Samples are stored in a 32 bit रेजिस्टर, oldest sample in
	 * the msb. A set bit represents space and an unset bit
	 * represents a pulse.
	 */
	samples = cx_पढ़ो(MO_SAMPLE_IO);

	अगर (samples == 0xff && ir->dev->idle)
		वापस;

	क्रम (toकरो = 32; toकरो > 0; toकरो -= bits) अणु
		ev.pulse = samples & 0x80000000 ? false : true;
		bits = min(toकरो, 32U - fls(ev.pulse ? samples : ~samples));
		ev.duration = (bits * (USEC_PER_SEC / 1000)) / ir_samplerate;
		ir_raw_event_store_with_filter(ir->dev, &ev);
		samples <<= bits;
	पूर्ण
	ir_raw_event_handle(ir->dev);
पूर्ण

अटल पूर्णांक get_key_pvr2000(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			   u32 *scancode, u8 *toggle)
अणु
	पूर्णांक flags, code;

	/* poll IR chip */
	flags = i2c_smbus_पढ़ो_byte_data(ir->c, 0x10);
	अगर (flags < 0) अणु
		dprपूर्णांकk("read error\n");
		वापस 0;
	पूर्ण
	/* key pressed ? */
	अगर (0 == (flags & 0x80))
		वापस 0;

	/* पढ़ो actual key code */
	code = i2c_smbus_पढ़ो_byte_data(ir->c, 0x00);
	अगर (code < 0) अणु
		dprपूर्णांकk("read error\n");
		वापस 0;
	पूर्ण

	dprपूर्णांकk("IR Key/Flags: (0x%02x/0x%02x)\n",
		code & 0xff, flags & 0xff);

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = code & 0xff;
	*toggle = 0;
	वापस 1;
पूर्ण

व्योम cx88_i2c_init_ir(काष्ठा cx88_core *core)
अणु
	काष्ठा i2c_board_info info;
	अटल स्थिर अचिन्हित लघु शेष_addr_list[] = अणु
		0x18, 0x6b, 0x71,
		I2C_CLIENT_END
	पूर्ण;
	अटल स्थिर अचिन्हित लघु pvr2000_addr_list[] = अणु
		0x18, 0x1a,
		I2C_CLIENT_END
	पूर्ण;
	स्थिर अचिन्हित लघु *addr_list = शेष_addr_list;
	स्थिर अचिन्हित लघु *addrp;
	/* Instantiate the IR receiver device, अगर present */
	अगर (core->i2c_rc != 0)
		वापस;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "ir_video", I2C_NAME_SIZE);

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_LEADTEK_PVR2000:
		addr_list = pvr2000_addr_list;
		core->init_data.name = "cx88 Leadtek PVR 2000 remote";
		core->init_data.type = RC_PROTO_BIT_UNKNOWN;
		core->init_data.get_key = get_key_pvr2000;
		core->init_data.ir_codes = RC_MAP_EMPTY;
		अवरोध;
	पूर्ण

	/*
	 * We can't call i2c_new_scanned_device() because it uses
	 * quick ग_लिखोs क्रम probing and at least some RC receiver
	 * devices only reply to पढ़ोs.
	 * Also, Hauppauge XVR needs to be specअगरied, as address 0x71
	 * conflicts with another remote type used with saa7134
	 */
	क्रम (addrp = addr_list; *addrp != I2C_CLIENT_END; addrp++) अणु
		info.platक्रमm_data = शून्य;
		स_रखो(&core->init_data, 0, माप(core->init_data));

		अगर (*addrp == 0x71) अणु
			/* Hauppauge Z8F0811 */
			strscpy(info.type, "ir_z8f0811_haup", I2C_NAME_SIZE);
			core->init_data.name = core->board.name;
			core->init_data.ir_codes = RC_MAP_HAUPPAUGE;
			core->init_data.type = RC_PROTO_BIT_RC5 |
				RC_PROTO_BIT_RC6_MCE | RC_PROTO_BIT_RC6_6A_32;
			core->init_data.पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;

			info.platक्रमm_data = &core->init_data;
		पूर्ण
		अगर (i2c_smbus_xfer(&core->i2c_adap, *addrp, 0,
				   I2C_SMBUS_READ, 0,
				   I2C_SMBUS_QUICK, शून्य) >= 0) अणु
			info.addr = *addrp;
			i2c_new_client_device(&core->i2c_adap, &info);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* ---------------------------------------------------------------------- */

MODULE_AUTHOR("Gerd Knorr, Pavel Machek, Chris Pascoe");
MODULE_DESCRIPTION("input driver for cx88 GPIO-based IR remote controls");
MODULE_LICENSE("GPL");
