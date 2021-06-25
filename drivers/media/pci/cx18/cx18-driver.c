<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 driver initialization and card probing
 *
 *  Derived from ivtv-driver.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-version.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-i2c.h"
#समावेश "cx18-irq.h"
#समावेश "cx18-gpio.h"
#समावेश "cx18-firmware.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-av-core.h"
#समावेश "cx18-scb.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-controls.h"
#समावेश "tuner-xc2028.h"
#समावेश <linux/dma-mapping.h>
#समावेश <media/tveeprom.h>

/* If you have alपढ़ोy X v4l cards, then set this to X. This way
   the device numbers stay matched. Example: you have a WinTV card
   without radio and a Compro H900 with. Normally this would give a
   video1 device together with a radio0 device क्रम the Compro. By
   setting this to 1 you ensure that radio0 is now also radio1. */
पूर्णांक cx18_first_minor;

/* Callback क्रम रेजिस्टरing extensions */
पूर्णांक (*cx18_ext_init)(काष्ठा cx18 *);
EXPORT_SYMBOL(cx18_ext_init);

/* add your revision and whatnot here */
अटल स्थिर काष्ठा pci_device_id cx18_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_CX, PCI_DEVICE_ID_CX23418,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cx18_pci_tbl);

अटल atomic_t cx18_instance = ATOMIC_INIT(0);

/* Parameter declarations */
अटल पूर्णांक cardtype[CX18_MAX_CARDS];
अटल पूर्णांक tuner[CX18_MAX_CARDS] = अणु -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक radio[CX18_MAX_CARDS] = अणु -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल अचिन्हित cardtype_c = 1;
अटल अचिन्हित tuner_c = 1;
अटल अचिन्हित radio_c = 1;
अटल अक्षर pal[] = "--";
अटल अक्षर secam[] = "--";
अटल अक्षर ntsc[] = "-";

/* Buffers */
अटल पूर्णांक enc_ts_buffers = CX18_DEFAULT_ENC_TS_BUFFERS;
अटल पूर्णांक enc_mpg_buffers = CX18_DEFAULT_ENC_MPG_BUFFERS;
अटल पूर्णांक enc_idx_buffers = CX18_DEFAULT_ENC_IDX_BUFFERS;
अटल पूर्णांक enc_yuv_buffers = CX18_DEFAULT_ENC_YUV_BUFFERS;
अटल पूर्णांक enc_vbi_buffers = CX18_DEFAULT_ENC_VBI_BUFFERS;
अटल पूर्णांक enc_pcm_buffers = CX18_DEFAULT_ENC_PCM_BUFFERS;

अटल पूर्णांक enc_ts_bufsize = CX18_DEFAULT_ENC_TS_बफ_मानE;
अटल पूर्णांक enc_mpg_bufsize = CX18_DEFAULT_ENC_MPG_बफ_मानE;
अटल पूर्णांक enc_idx_bufsize = CX18_DEFAULT_ENC_IDX_बफ_मानE;
अटल पूर्णांक enc_yuv_bufsize = CX18_DEFAULT_ENC_YUV_बफ_मानE;
अटल पूर्णांक enc_pcm_bufsize = CX18_DEFAULT_ENC_PCM_बफ_मानE;

अटल पूर्णांक enc_ts_bufs = -1;
अटल पूर्णांक enc_mpg_bufs = -1;
अटल पूर्णांक enc_idx_bufs = CX18_MAX_FW_MDLS_PER_STREAM;
अटल पूर्णांक enc_yuv_bufs = -1;
अटल पूर्णांक enc_vbi_bufs = -1;
अटल पूर्णांक enc_pcm_bufs = -1;


अटल पूर्णांक cx18_pci_latency = 1;

अटल पूर्णांक mmio_ndelay;
अटल पूर्णांक retry_mmio = 1;

पूर्णांक cx18_debug;

module_param_array(tuner, पूर्णांक, &tuner_c, 0644);
module_param_array(radio, पूर्णांक, &radio_c, 0644);
module_param_array(cardtype, पूर्णांक, &cardtype_c, 0644);
module_param_string(pal, pal, माप(pal), 0644);
module_param_string(secam, secam, माप(secam), 0644);
module_param_string(ntsc, ntsc, माप(ntsc), 0644);
module_param_named(debug, cx18_debug, पूर्णांक, 0644);
module_param(mmio_ndelay, पूर्णांक, 0644);
module_param(retry_mmio, पूर्णांक, 0644);
module_param(cx18_pci_latency, पूर्णांक, 0644);
module_param(cx18_first_minor, पूर्णांक, 0644);

module_param(enc_ts_buffers, पूर्णांक, 0644);
module_param(enc_mpg_buffers, पूर्णांक, 0644);
module_param(enc_idx_buffers, पूर्णांक, 0644);
module_param(enc_yuv_buffers, पूर्णांक, 0644);
module_param(enc_vbi_buffers, पूर्णांक, 0644);
module_param(enc_pcm_buffers, पूर्णांक, 0644);

module_param(enc_ts_bufsize, पूर्णांक, 0644);
module_param(enc_mpg_bufsize, पूर्णांक, 0644);
module_param(enc_idx_bufsize, पूर्णांक, 0644);
module_param(enc_yuv_bufsize, पूर्णांक, 0644);
module_param(enc_pcm_bufsize, पूर्णांक, 0644);

module_param(enc_ts_bufs, पूर्णांक, 0644);
module_param(enc_mpg_bufs, पूर्णांक, 0644);
module_param(enc_idx_bufs, पूर्णांक, 0644);
module_param(enc_yuv_bufs, पूर्णांक, 0644);
module_param(enc_vbi_bufs, पूर्णांक, 0644);
module_param(enc_pcm_bufs, पूर्णांक, 0644);

MODULE_PARM_DESC(tuner, "Tuner type selection,\n"
			"\t\t\tsee tuner.h for values");
MODULE_PARM_DESC(radio,
		 "Enable or disable the radio. Use only if autodetection\n"
		 "\t\t\tfails. 0 = disable, 1 = enable");
MODULE_PARM_DESC(cardtype,
		 "Only use this option if your card is not detected properly.\n"
		 "\t\tSpecify card type:\n"
		 "\t\t\t 1 = Hauppauge HVR 1600 (ESMT memory)\n"
		 "\t\t\t 2 = Hauppauge HVR 1600 (Samsung memory)\n"
		 "\t\t\t 3 = Compro VideoMate H900\n"
		 "\t\t\t 4 = Yuan MPC718\n"
		 "\t\t\t 5 = Conexant Raptor PAL/SECAM\n"
		 "\t\t\t 6 = Toshiba Qosmio DVB-T/Analog\n"
		 "\t\t\t 7 = Leadtek WinFast PVR2100\n"
		 "\t\t\t 8 = Leadtek WinFast DVR3100 H\n"
		 "\t\t\t 9 = GoTView PCI DVD3 Hybrid\n"
		 "\t\t\t 10 = Hauppauge HVR 1600 (S5H1411)\n"
		 "\t\t\t 0 = Autodetect (default)\n"
		 "\t\t\t-1 = Ignore this card\n\t\t");
MODULE_PARM_DESC(pal, "Set PAL standard: B, G, H, D, K, I, M, N, Nc, 60");
MODULE_PARM_DESC(secam, "Set SECAM standard: B, G, H, D, K, L, LC");
MODULE_PARM_DESC(ntsc, "Set NTSC standard: M, J, K");
MODULE_PARM_DESC(debug,
		 "Debug level (bitmask). Default: 0\n"
		 "\t\t\t  1/0x0001: warning\n"
		 "\t\t\t  2/0x0002: info\n"
		 "\t\t\t  4/0x0004: mailbox\n"
		 "\t\t\t  8/0x0008: dma\n"
		 "\t\t\t 16/0x0010: ioctl\n"
		 "\t\t\t 32/0x0020: file\n"
		 "\t\t\t 64/0x0040: i2c\n"
		 "\t\t\t128/0x0080: irq\n"
		 "\t\t\t256/0x0100: high volume\n");
MODULE_PARM_DESC(cx18_pci_latency,
		 "Change the PCI latency to 64 if lower: 0 = No, 1 = Yes,\n"
		 "\t\t\tDefault: Yes");
MODULE_PARM_DESC(retry_mmio,
		 "(Deprecated) MMIO writes are now always checked and retried\n"
		 "\t\t\tEffectively: 1 [Yes]");
MODULE_PARM_DESC(mmio_ndelay,
		 "(Deprecated) MMIO accesses are now never purposely delayed\n"
		 "\t\t\tEffectively: 0 ns");
MODULE_PARM_DESC(enc_ts_buffers,
		 "Encoder TS buffer memory (MB). (enc_ts_bufs can override)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_TS_BUFFERS));
MODULE_PARM_DESC(enc_ts_bufsize,
		 "Size of an encoder TS buffer (kB)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_TS_बफ_मानE));
MODULE_PARM_DESC(enc_ts_bufs,
		 "Number of encoder TS buffers\n"
		 "\t\t\tDefault is computed from other enc_ts_* parameters");
MODULE_PARM_DESC(enc_mpg_buffers,
		 "Encoder MPG buffer memory (MB). (enc_mpg_bufs can override)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_MPG_BUFFERS));
MODULE_PARM_DESC(enc_mpg_bufsize,
		 "Size of an encoder MPG buffer (kB)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_MPG_बफ_मानE));
MODULE_PARM_DESC(enc_mpg_bufs,
		 "Number of encoder MPG buffers\n"
		 "\t\t\tDefault is computed from other enc_mpg_* parameters");
MODULE_PARM_DESC(enc_idx_buffers,
		 "(Deprecated) Encoder IDX buffer memory (MB)\n"
		 "\t\t\tIgnored, except 0 disables IDX buffer allocations\n"
		 "\t\t\tDefault: 1 [Enabled]");
MODULE_PARM_DESC(enc_idx_bufsize,
		 "Size of an encoder IDX buffer (kB)\n"
		 "\t\t\tAllowed values are multiples of 1.5 kB rounded up\n"
		 "\t\t\t(multiples of size required for 64 index entries)\n"
		 "\t\t\tDefault: 2");
MODULE_PARM_DESC(enc_idx_bufs,
		 "Number of encoder IDX buffers\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_MAX_FW_MDLS_PER_STREAM));
MODULE_PARM_DESC(enc_yuv_buffers,
		 "Encoder YUV buffer memory (MB). (enc_yuv_bufs can override)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_YUV_BUFFERS));
MODULE_PARM_DESC(enc_yuv_bufsize,
		 "Size of an encoder YUV buffer (kB)\n"
		 "\t\t\tAllowed values are multiples of 33.75 kB rounded up\n"
		 "\t\t\t(multiples of size required for 32 screen lines)\n"
		 "\t\t\tDefault: 102");
MODULE_PARM_DESC(enc_yuv_bufs,
		 "Number of encoder YUV buffers\n"
		 "\t\t\tDefault is computed from other enc_yuv_* parameters");
MODULE_PARM_DESC(enc_vbi_buffers,
		 "Encoder VBI buffer memory (MB). (enc_vbi_bufs can override)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_VBI_BUFFERS));
MODULE_PARM_DESC(enc_vbi_bufs,
		 "Number of encoder VBI buffers\n"
		 "\t\t\tDefault is computed from enc_vbi_buffers");
MODULE_PARM_DESC(enc_pcm_buffers,
		 "Encoder PCM buffer memory (MB). (enc_pcm_bufs can override)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_PCM_BUFFERS));
MODULE_PARM_DESC(enc_pcm_bufsize,
		 "Size of an encoder PCM buffer (kB)\n"
		 "\t\t\tDefault: " __stringअगरy(CX18_DEFAULT_ENC_PCM_बफ_मानE));
MODULE_PARM_DESC(enc_pcm_bufs,
		 "Number of encoder PCM buffers\n"
		 "\t\t\tDefault is computed from other enc_pcm_* parameters");

MODULE_PARM_DESC(cx18_first_minor,
		 "Set device node number assigned to first card");

MODULE_AUTHOR("Hans Verkuil");
MODULE_DESCRIPTION("CX23418 driver");
MODULE_LICENSE("GPL");

MODULE_VERSION(CX18_VERSION);

#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx18 *dev = container_of(work, काष्ठा cx18, request_module_wk);

	/* Make sure cx18-alsa module is loaded */
	request_module("cx18-alsa");

	/* Initialize cx18-alsa क्रम this instance of the cx18 device */
	अगर (cx18_ext_init)
		cx18_ext_init(dev);
पूर्ण

अटल व्योम request_modules(काष्ठा cx18 *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा cx18 *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

/* Generic utility functions */
पूर्णांक cx18_msleep_समयout(अचिन्हित पूर्णांक msecs, पूर्णांक पूर्णांकr)
अणु
	दीर्घ पूर्णांक समयout = msecs_to_jअगरfies(msecs);
	पूर्णांक sig;

	करो अणु
		set_current_state(पूर्णांकr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		समयout = schedule_समयout(समयout);
		sig = पूर्णांकr ? संकेत_pending(current) : 0;
	पूर्ण जबतक (!sig && समयout);
	वापस sig;
पूर्ण

/* Release ioremapped memory */
अटल व्योम cx18_iounmap(काष्ठा cx18 *cx)
अणु
	अगर (!cx)
		वापस;

	/* Release io memory */
	अगर (cx->enc_mem) अणु
		CX18_DEBUG_INFO("releasing enc_mem\n");
		iounmap(cx->enc_mem);
		cx->enc_mem = शून्य;
	पूर्ण
पूर्ण

अटल व्योम cx18_eeprom_dump(काष्ठा cx18 *cx, अचिन्हित अक्षर *eedata, पूर्णांक len)
अणु
	पूर्णांक i;

	CX18_INFO("eeprom dump:\n");
	क्रम (i = 0; i < len; i++) अणु
		अगर (0 == (i % 16))
			CX18_INFO("eeprom %02x:", i);
		prपूर्णांकk(KERN_CONT " %02x", eedata[i]);
		अगर (15 == (i % 16))
			prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
पूर्ण

/* Hauppauge card? get values from tveeprom */
व्योम cx18_पढ़ो_eeprom(काष्ठा cx18 *cx, काष्ठा tveeprom *tv)
अणु
	काष्ठा i2c_client *c;
	u8 eedata[256];

	स_रखो(tv, 0, माप(*tv));

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस;

	strscpy(c->name, "cx18 tveeprom tmp", माप(c->name));
	c->adapter = &cx->i2c_adap[0];
	c->addr = 0xa0 >> 1;

	अगर (tveeprom_पढ़ो(c, eedata, माप(eedata)))
		जाओ ret;

	चयन (cx->card->type) अणु
	हाल CX18_CARD_HVR_1600_ESMT:
	हाल CX18_CARD_HVR_1600_SAMSUNG:
	हाल CX18_CARD_HVR_1600_S5H1411:
		tveeprom_hauppauge_analog(tv, eedata);
		अवरोध;
	हाल CX18_CARD_YUAN_MPC718:
	हाल CX18_CARD_GOTVIEW_PCI_DVD3:
		tv->model = 0x718;
		cx18_eeprom_dump(cx, eedata, माप(eedata));
		CX18_INFO("eeprom PCI ID: %02x%02x:%02x%02x\n",
			  eedata[2], eedata[1], eedata[4], eedata[3]);
		अवरोध;
	शेष:
		tv->model = 0xffffffff;
		cx18_eeprom_dump(cx, eedata, माप(eedata));
		अवरोध;
	पूर्ण

ret:
	kमुक्त(c);
पूर्ण

अटल व्योम cx18_process_eeprom(काष्ठा cx18 *cx)
अणु
	काष्ठा tveeprom tv;

	cx18_पढ़ो_eeprom(cx, &tv);

	/* Many thanks to Steven Toth from Hauppauge क्रम providing the
	   model numbers */
	/* Note: the Samsung memory models cannot be reliably determined
	   from the model number. Use the cardtype module option अगर you
	   have one of these preproduction models. */
	चयन (tv.model) अणु
	हाल 74301: /* Retail models */
	हाल 74321:
	हाल 74351: /* OEM models */
	हाल 74361:
		/* Digital side is s5h1411/tda18271 */
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_S5H1411);
		अवरोध;
	हाल 74021: /* Retail models */
	हाल 74031:
	हाल 74041:
	हाल 74141:
	हाल 74541: /* OEM models */
	हाल 74551:
	हाल 74591:
	हाल 74651:
	हाल 74691:
	हाल 74751:
	हाल 74891:
		/* Digital side is s5h1409/mxl5005s */
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
		अवरोध;
	हाल 0x718:
		वापस;
	हाल 0xffffffff:
		CX18_INFO("Unknown EEPROM encoding\n");
		वापस;
	हाल 0:
		CX18_ERR("Invalid EEPROM\n");
		वापस;
	शेष:
		CX18_ERR("Unknown model %d, defaulting to original HVR-1600 (cardtype=1)\n",
			 tv.model);
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
		अवरोध;
	पूर्ण

	cx->v4l2_cap = cx->card->v4l2_capabilities;
	cx->card_name = cx->card->name;
	cx->card_i2c = cx->card->i2c;

	CX18_INFO("Autodetected %s\n", cx->card_name);

	अगर (tv.tuner_type == TUNER_ABSENT)
		CX18_ERR("tveeprom cannot autodetect tuner!\n");

	अगर (cx->options.tuner == -1)
		cx->options.tuner = tv.tuner_type;
	अगर (cx->options.radio == -1)
		cx->options.radio = (tv.has_radio != 0);

	अगर (cx->std != 0)
		/* user specअगरied tuner standard */
		वापस;

	/* स्वतःdetect tuner standard */
#घोषणा TVEEPROM_TUNER_FORMAT_ALL (V4L2_STD_B  | V4L2_STD_GH | \
				   V4L2_STD_MN | \
				   V4L2_STD_PAL_I | \
				   V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC | \
				   V4L2_STD_DK)
	अगर ((tv.tuner_क्रमmats & TVEEPROM_TUNER_FORMAT_ALL)
					== TVEEPROM_TUNER_FORMAT_ALL) अणु
		CX18_DEBUG_INFO("Worldwide tuner detected\n");
		cx->std = V4L2_STD_ALL;
	पूर्ण अन्यथा अगर (tv.tuner_क्रमmats & V4L2_STD_PAL) अणु
		CX18_DEBUG_INFO("PAL tuner detected\n");
		cx->std |= V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
	पूर्ण अन्यथा अगर (tv.tuner_क्रमmats & V4L2_STD_NTSC) अणु
		CX18_DEBUG_INFO("NTSC tuner detected\n");
		cx->std |= V4L2_STD_NTSC_M;
	पूर्ण अन्यथा अगर (tv.tuner_क्रमmats & V4L2_STD_SECAM) अणु
		CX18_DEBUG_INFO("SECAM tuner detected\n");
		cx->std |= V4L2_STD_SECAM_L;
	पूर्ण अन्यथा अणु
		CX18_INFO("No tuner detected, default to NTSC-M\n");
		cx->std |= V4L2_STD_NTSC_M;
	पूर्ण
पूर्ण

अटल v4l2_std_id cx18_parse_std(काष्ठा cx18 *cx)
अणु
	चयन (pal[0]) अणु
	हाल '6':
		वापस V4L2_STD_PAL_60;
	हाल 'b':
	हाल 'B':
	हाल 'g':
	हाल 'G':
		वापस V4L2_STD_PAL_BG;
	हाल 'h':
	हाल 'H':
		वापस V4L2_STD_PAL_H;
	हाल 'n':
	हाल 'N':
		अगर (pal[1] == 'c' || pal[1] == 'C')
			वापस V4L2_STD_PAL_Nc;
		वापस V4L2_STD_PAL_N;
	हाल 'i':
	हाल 'I':
		वापस V4L2_STD_PAL_I;
	हाल 'd':
	हाल 'D':
	हाल 'k':
	हाल 'K':
		वापस V4L2_STD_PAL_DK;
	हाल 'M':
	हाल 'm':
		वापस V4L2_STD_PAL_M;
	हाल '-':
		अवरोध;
	शेष:
		CX18_WARN("pal= argument not recognised\n");
		वापस 0;
	पूर्ण

	चयन (secam[0]) अणु
	हाल 'b':
	हाल 'B':
	हाल 'g':
	हाल 'G':
	हाल 'h':
	हाल 'H':
		वापस V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H;
	हाल 'd':
	हाल 'D':
	हाल 'k':
	हाल 'K':
		वापस V4L2_STD_SECAM_DK;
	हाल 'l':
	हाल 'L':
		अगर (secam[1] == 'C' || secam[1] == 'c')
			वापस V4L2_STD_SECAM_LC;
		वापस V4L2_STD_SECAM_L;
	हाल '-':
		अवरोध;
	शेष:
		CX18_WARN("secam= argument not recognised\n");
		वापस 0;
	पूर्ण

	चयन (ntsc[0]) अणु
	हाल 'm':
	हाल 'M':
		वापस V4L2_STD_NTSC_M;
	हाल 'j':
	हाल 'J':
		वापस V4L2_STD_NTSC_M_JP;
	हाल 'k':
	हाल 'K':
		वापस V4L2_STD_NTSC_M_KR;
	हाल '-':
		अवरोध;
	शेष:
		CX18_WARN("ntsc= argument not recognised\n");
		वापस 0;
	पूर्ण

	/* no match found */
	वापस 0;
पूर्ण

अटल व्योम cx18_process_options(काष्ठा cx18 *cx)
अणु
	पूर्णांक i, j;

	cx->options.megabytes[CX18_ENC_STREAM_TYPE_TS] = enc_ts_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_MPG] = enc_mpg_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_IDX] = enc_idx_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_YUV] = enc_yuv_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_VBI] = enc_vbi_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_PCM] = enc_pcm_buffers;
	cx->options.megabytes[CX18_ENC_STREAM_TYPE_RAD] = 0; /* control only */

	cx->stream_buffers[CX18_ENC_STREAM_TYPE_TS] = enc_ts_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_MPG] = enc_mpg_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_IDX] = enc_idx_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_YUV] = enc_yuv_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_VBI] = enc_vbi_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_PCM] = enc_pcm_bufs;
	cx->stream_buffers[CX18_ENC_STREAM_TYPE_RAD] = 0; /* control, no data */

	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_TS] = enc_ts_bufsize;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_MPG] = enc_mpg_bufsize;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_IDX] = enc_idx_bufsize;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_YUV] = enc_yuv_bufsize;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_VBI] = VBI_ACTIVE_SAMPLES * 36;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_PCM] = enc_pcm_bufsize;
	cx->stream_buf_size[CX18_ENC_STREAM_TYPE_RAD] = 0; /* control no data */

	/* Ensure stream_buffers & stream_buf_size are valid */
	क्रम (i = 0; i < CX18_MAX_STREAMS; i++) अणु
		अगर (cx->stream_buffers[i] == 0 ||     /* User said 0 buffers */
		    cx->options.megabytes[i] <= 0 ||  /* User said 0 MB total */
		    cx->stream_buf_size[i] <= 0) अणु    /* User said buf size 0 */
			cx->options.megabytes[i] = 0;
			cx->stream_buffers[i] = 0;
			cx->stream_buf_size[i] = 0;
			जारी;
		पूर्ण
		/*
		 * YUV is a special हाल where the stream_buf_size needs to be
		 * an पूर्णांकegral multiple of 33.75 kB (storage क्रम 32 screens
		 * lines to मुख्यtain alignment in हाल of lost buffers).
		 *
		 * IDX is a special हाल where the stream_buf_size should be
		 * an पूर्णांकegral multiple of 1.5 kB (storage क्रम 64 index entries
		 * to मुख्यtain alignment in हाल of lost buffers).
		 *
		 */
		अगर (i == CX18_ENC_STREAM_TYPE_YUV) अणु
			cx->stream_buf_size[i] *= 1024;
			cx->stream_buf_size[i] -=
			   (cx->stream_buf_size[i] % CX18_UNIT_ENC_YUV_बफ_मानE);

			अगर (cx->stream_buf_size[i] < CX18_UNIT_ENC_YUV_बफ_मानE)
				cx->stream_buf_size[i] =
						CX18_UNIT_ENC_YUV_बफ_मानE;
		पूर्ण अन्यथा अगर (i == CX18_ENC_STREAM_TYPE_IDX) अणु
			cx->stream_buf_size[i] *= 1024;
			cx->stream_buf_size[i] -=
			   (cx->stream_buf_size[i] % CX18_UNIT_ENC_IDX_बफ_मानE);

			अगर (cx->stream_buf_size[i] < CX18_UNIT_ENC_IDX_बफ_मानE)
				cx->stream_buf_size[i] =
						CX18_UNIT_ENC_IDX_बफ_मानE;
		पूर्ण
		/*
		 * YUV and IDX are special हालs where the stream_buf_size is
		 * now in bytes.
		 * VBI is a special हाल where the stream_buf_size is fixed
		 * and alपढ़ोy in bytes
		 */
		अगर (i == CX18_ENC_STREAM_TYPE_VBI ||
		    i == CX18_ENC_STREAM_TYPE_YUV ||
		    i == CX18_ENC_STREAM_TYPE_IDX) अणु
			अगर (cx->stream_buffers[i] < 0) अणु
				cx->stream_buffers[i] =
					cx->options.megabytes[i] * 1024 * 1024
					/ cx->stream_buf_size[i];
			पूर्ण अन्यथा अणु
				/* N.B. This might round करोwn to 0 */
				cx->options.megabytes[i] =
					cx->stream_buffers[i]
					* cx->stream_buf_size[i]/(1024 * 1024);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* All other streams have stream_buf_size in kB here */
			अगर (cx->stream_buffers[i] < 0) अणु
				cx->stream_buffers[i] =
						cx->options.megabytes[i] * 1024
						/ cx->stream_buf_size[i];
			पूर्ण अन्यथा अणु
				/* N.B. This might round करोwn to 0 */
				cx->options.megabytes[i] =
						cx->stream_buffers[i]
						* cx->stream_buf_size[i] / 1024;
			पूर्ण
			/* convert from kB to bytes */
			cx->stream_buf_size[i] *= 1024;
		पूर्ण
		CX18_DEBUG_INFO("Stream type %d options: %d MB, %d buffers, %d bytes\n",
				i, cx->options.megabytes[i],
				cx->stream_buffers[i], cx->stream_buf_size[i]);
	पूर्ण

	cx->options.cardtype = cardtype[cx->instance];
	cx->options.tuner = tuner[cx->instance];
	cx->options.radio = radio[cx->instance];

	cx->std = cx18_parse_std(cx);
	अगर (cx->options.cardtype == -1) अणु
		CX18_INFO("Ignore card\n");
		वापस;
	पूर्ण
	cx->card = cx18_get_card(cx->options.cardtype - 1);
	अगर (cx->card)
		CX18_INFO("User specified %s card\n", cx->card->name);
	अन्यथा अगर (cx->options.cardtype != 0)
		CX18_ERR("Unknown user specified type, trying to autodetect card\n");
	अगर (!cx->card) अणु
		अगर (cx->pci_dev->subप्रणाली_venकरोr == CX18_PCI_ID_HAUPPAUGE) अणु
			cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
			CX18_INFO("Autodetected Hauppauge card\n");
		पूर्ण
	पूर्ण
	अगर (!cx->card) अणु
		क्रम (i = 0; (cx->card = cx18_get_card(i)); i++) अणु
			अगर (!cx->card->pci_list)
				जारी;
			क्रम (j = 0; cx->card->pci_list[j].device; j++) अणु
				अगर (cx->pci_dev->device !=
				    cx->card->pci_list[j].device)
					जारी;
				अगर (cx->pci_dev->subप्रणाली_venकरोr !=
				    cx->card->pci_list[j].subप्रणाली_venकरोr)
					जारी;
				अगर (cx->pci_dev->subप्रणाली_device !=
				    cx->card->pci_list[j].subप्रणाली_device)
					जारी;
				CX18_INFO("Autodetected %s card\n", cx->card->name);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:

	अगर (!cx->card) अणु
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
		CX18_ERR("Unknown card: vendor/device: [%04x:%04x]\n",
			 cx->pci_dev->venकरोr, cx->pci_dev->device);
		CX18_ERR("              subsystem vendor/device: [%04x:%04x]\n",
			 cx->pci_dev->subप्रणाली_venकरोr,
			 cx->pci_dev->subप्रणाली_device);
		CX18_ERR("Defaulting to %s card\n", cx->card->name);
		CX18_ERR("Please mail the vendor/device and subsystem vendor/device IDs and what kind of\n");
		CX18_ERR("card you have to the linux-media mailinglist (www.linuxtv.org)\n");
		CX18_ERR("Prefix your subject line with [UNKNOWN CX18 CARD].\n");
	पूर्ण
	cx->v4l2_cap = cx->card->v4l2_capabilities;
	cx->card_name = cx->card->name;
	cx->card_i2c = cx->card->i2c;
पूर्ण

अटल पूर्णांक cx18_create_in_workq(काष्ठा cx18 *cx)
अणु
	snम_लिखो(cx->in_workq_name, माप(cx->in_workq_name), "%s-in",
		 cx->v4l2_dev.name);
	cx->in_work_queue = alloc_ordered_workqueue("%s", 0, cx->in_workq_name);
	अगर (!cx->in_work_queue) अणु
		CX18_ERR("Unable to create incoming mailbox handler thread\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cx18_init_in_work_orders(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++) अणु
		cx->in_work_order[i].cx = cx;
		cx->in_work_order[i].str = cx->epu_debug_str;
		INIT_WORK(&cx->in_work_order[i].work, cx18_in_work_handler);
	पूर्ण
पूर्ण

/* Precondition: the cx18 काष्ठाure has been स_रखो to 0. Only
   the dev and instance fields have been filled in.
   No assumptions on the card type may be made here (see cx18_init_काष्ठा2
   क्रम that).
 */
अटल पूर्णांक cx18_init_काष्ठा1(काष्ठा cx18 *cx)
अणु
	पूर्णांक ret;

	cx->base_addr = pci_resource_start(cx->pci_dev, 0);

	mutex_init(&cx->serialize_lock);
	mutex_init(&cx->gpio_lock);
	mutex_init(&cx->epu2apu_mb_lock);
	mutex_init(&cx->epu2cpu_mb_lock);

	ret = cx18_create_in_workq(cx);
	अगर (ret)
		वापस ret;

	cx18_init_in_work_orders(cx);

	/* start counting खोलो_id at 1 */
	cx->खोलो_id = 1;

	/* Initial settings */
	cx->cxhdl.port = CX2341X_PORT_MEMORY;
	cx->cxhdl.capabilities = CX2341X_CAP_HAS_TS | CX2341X_CAP_HAS_SLICED_VBI;
	cx->cxhdl.ops = &cx18_cxhdl_ops;
	cx->cxhdl.func = cx18_api_func;
	cx->cxhdl.priv = &cx->streams[CX18_ENC_STREAM_TYPE_MPG];
	ret = cx2341x_handler_init(&cx->cxhdl, 50);
	अगर (ret)
		वापस ret;
	cx->v4l2_dev.ctrl_handler = &cx->cxhdl.hdl;

	cx->temporal_strength = cx->cxhdl.video_temporal_filter->cur.val;
	cx->spatial_strength = cx->cxhdl.video_spatial_filter->cur.val;
	cx->filter_mode = cx->cxhdl.video_spatial_filter_mode->cur.val |
		(cx->cxhdl.video_temporal_filter_mode->cur.val << 1) |
		(cx->cxhdl.video_median_filter_type->cur.val << 2);

	init_रुकोqueue_head(&cx->cap_w);
	init_रुकोqueue_head(&cx->mb_apu_रुकोq);
	init_रुकोqueue_head(&cx->mb_cpu_रुकोq);
	init_रुकोqueue_head(&cx->dma_रुकोq);

	/* VBI */
	cx->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;
	cx->vbi.sliced_in = &cx->vbi.in.fmt.sliced;

	/* IVTV style VBI insertion पूर्णांकo MPEG streams */
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_buf.list);
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_mdl.list);
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_mdl.buf_list);
	list_add(&cx->vbi.sliced_mpeg_buf.list,
		 &cx->vbi.sliced_mpeg_mdl.buf_list);
	वापस 0;
पूर्ण

/* Second initialization part. Here the card type has been
   स्वतःdetected. */
अटल व्योम cx18_init_काष्ठा2(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CX18_CARD_MAX_VIDEO_INPUTS - 1; i++)
		अगर (cx->card->video_inमाला_दो[i].video_type == 0)
			अवरोध;
	cx->nof_inमाला_दो = i;
	क्रम (i = 0; i < CX18_CARD_MAX_AUDIO_INPUTS - 1; i++)
		अगर (cx->card->audio_inमाला_दो[i].audio_type == 0)
			अवरोध;
	cx->nof_audio_inमाला_दो = i;

	/* Find tuner input */
	क्रम (i = 0; i < cx->nof_inमाला_दो; i++) अणु
		अगर (cx->card->video_inमाला_दो[i].video_type ==
				CX18_CARD_INPUT_VID_TUNER)
			अवरोध;
	पूर्ण
	अगर (i == cx->nof_inमाला_दो)
		i = 0;
	cx->active_input = i;
	cx->audio_input = cx->card->video_inमाला_दो[i].audio_index;
पूर्ण

अटल पूर्णांक cx18_setup_pci(काष्ठा cx18 *cx, काष्ठा pci_dev *pci_dev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	u16 cmd;
	अचिन्हित अक्षर pci_latency;

	CX18_DEBUG_INFO("Enabling pci device\n");

	अगर (pci_enable_device(pci_dev)) अणु
		CX18_ERR("Can't enable device %d!\n", cx->instance);
		वापस -EIO;
	पूर्ण
	अगर (pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32))) अणु
		CX18_ERR("No suitable DMA available, card %d\n", cx->instance);
		वापस -EIO;
	पूर्ण
	अगर (!request_mem_region(cx->base_addr, CX18_MEM_SIZE, "cx18 encoder")) अणु
		CX18_ERR("Cannot request encoder memory region, card %d\n",
			 cx->instance);
		वापस -EIO;
	पूर्ण

	/* Enable bus mastering and memory mapped IO क्रम the CX23418 */
	pci_पढ़ो_config_word(pci_dev, PCI_COMMAND, &cmd);
	cmd |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	pci_ग_लिखो_config_word(pci_dev, PCI_COMMAND, cmd);

	cx->card_rev = pci_dev->revision;
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER, &pci_latency);

	अगर (pci_latency < 64 && cx18_pci_latency) अणु
		CX18_INFO("Unreasonably low latency timer, setting to 64 (was %d)\n",
			  pci_latency);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, 64);
		pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER, &pci_latency);
	पूर्ण

	CX18_DEBUG_INFO("cx%d (rev %d) at %02x:%02x.%x, irq: %d, latency: %d, memory: 0x%llx\n",
		   cx->pci_dev->device, cx->card_rev, pci_dev->bus->number,
		   PCI_SLOT(pci_dev->devfn), PCI_FUNC(pci_dev->devfn),
		   cx->pci_dev->irq, pci_latency, (u64)cx->base_addr);

	वापस 0;
पूर्ण

अटल व्योम cx18_init_subdevs(काष्ठा cx18 *cx)
अणु
	u32 hw = cx->card->hw_all;
	u32 device;
	पूर्णांक i;

	क्रम (i = 0, device = 1; i < 32; i++, device <<= 1) अणु

		अगर (!(device & hw))
			जारी;

		चयन (device) अणु
		हाल CX18_HW_DVB:
		हाल CX18_HW_TVEEPROM:
			/* These subordinate devices करो not use probing */
			cx->hw_flags |= device;
			अवरोध;
		हाल CX18_HW_418_AV:
			/* The A/V decoder माला_लो probed earlier to set PLLs */
			/* Just note that the card uses it (i.e. has analog) */
			cx->hw_flags |= device;
			अवरोध;
		हाल CX18_HW_GPIO_RESET_CTRL:
			/*
			 * The Reset Controller माला_लो probed and added to
			 * hw_flags earlier क्रम i2c adapter/bus initialization
			 */
			अवरोध;
		हाल CX18_HW_GPIO_MUX:
			अगर (cx18_gpio_रेजिस्टर(cx, device) == 0)
				cx->hw_flags |= device;
			अवरोध;
		शेष:
			अगर (cx18_i2c_रेजिस्टर(cx, i) == 0)
				cx->hw_flags |= device;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cx->hw_flags & CX18_HW_418_AV)
		cx->sd_av = cx18_find_hw(cx, CX18_HW_418_AV);

	अगर (cx->card->hw_muxer != 0)
		cx->sd_exपंचांगux = cx18_find_hw(cx, cx->card->hw_muxer);
पूर्ण

अटल पूर्णांक cx18_probe(काष्ठा pci_dev *pci_dev,
		      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक retval = 0;
	पूर्णांक i;
	u32 devtype;
	काष्ठा cx18 *cx;

	/* FIXME - module parameter arrays स्थिरrain max instances */
	i = atomic_inc_वापस(&cx18_instance) - 1;
	अगर (i >= CX18_MAX_CARDS) अणु
		prपूर्णांकk(KERN_ERR "cx18: cannot manage card %d, driver has a limit of 0 - %d\n",
		       i, CX18_MAX_CARDS - 1);
		वापस -ENOMEM;
	पूर्ण

	cx = kzalloc(माप(*cx), GFP_ATOMIC);
	अगर (!cx)
		वापस -ENOMEM;

	cx->pci_dev = pci_dev;
	cx->instance = i;

	retval = v4l2_device_रेजिस्टर(&pci_dev->dev, &cx->v4l2_dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "cx18: v4l2_device_register of card %d failed\n",
		       cx->instance);
		kमुक्त(cx);
		वापस retval;
	पूर्ण
	snम_लिखो(cx->v4l2_dev.name, माप(cx->v4l2_dev.name), "cx18-%d",
		 cx->instance);
	CX18_INFO("Initializing card %d\n", cx->instance);

	cx18_process_options(cx);
	अगर (cx->options.cardtype == -1) अणु
		retval = -ENODEV;
		जाओ err;
	पूर्ण

	retval = cx18_init_काष्ठा1(cx);
	अगर (retval)
		जाओ err;

	CX18_DEBUG_INFO("base addr: 0x%llx\n", (u64)cx->base_addr);

	/* PCI Device Setup */
	retval = cx18_setup_pci(cx, pci_dev, pci_id);
	अगर (retval != 0)
		जाओ मुक्त_workqueues;

	/* map io memory */
	CX18_DEBUG_INFO("attempting ioremap at 0x%llx len 0x%08x\n",
		   (u64)cx->base_addr + CX18_MEM_OFFSET, CX18_MEM_SIZE);
	cx->enc_mem = ioremap(cx->base_addr + CX18_MEM_OFFSET,
				       CX18_MEM_SIZE);
	अगर (!cx->enc_mem) अणु
		CX18_ERR("ioremap failed. Can't get a window into CX23418 memory and register space\n");
		CX18_ERR("Each capture card with a CX23418 needs 64 MB of vmalloc address space for the window\n");
		CX18_ERR("Check the output of 'grep Vmalloc /proc/meminfo'\n");
		CX18_ERR("Use the vmalloc= kernel command line option to set VmallocTotal to a larger value\n");
		retval = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण
	cx->reg_mem = cx->enc_mem + CX18_REG_OFFSET;
	devtype = cx18_पढ़ो_reg(cx, 0xC72028);
	चयन (devtype & 0xff000000) अणु
	हाल 0xff000000:
		CX18_INFO("cx23418 revision %08x (A)\n", devtype);
		अवरोध;
	हाल 0x01000000:
		CX18_INFO("cx23418 revision %08x (B)\n", devtype);
		अवरोध;
	शेष:
		CX18_INFO("cx23418 revision %08x (Unknown)\n", devtype);
		अवरोध;
	पूर्ण

	cx18_init_घातer(cx, 1);
	cx18_init_memory(cx);

	cx->scb = (काष्ठा cx18_scb __iomem *)(cx->enc_mem + SCB_OFFSET);
	cx18_init_scb(cx);

	cx18_gpio_init(cx);

	/* Initialize पूर्णांकegrated A/V decoder early to set PLLs, just in हाल */
	retval = cx18_av_probe(cx);
	अगर (retval) अणु
		CX18_ERR("Could not register A/V decoder subdevice\n");
		जाओ मुक्त_map;
	पूर्ण

	/* Initialize GPIO Reset Controller to करो chip resets during i2c init */
	अगर (cx->card->hw_all & CX18_HW_GPIO_RESET_CTRL) अणु
		अगर (cx18_gpio_रेजिस्टर(cx, CX18_HW_GPIO_RESET_CTRL) != 0)
			CX18_WARN("Could not register GPIO reset controllersubdevice; proceeding anyway.\n");
		अन्यथा
			cx->hw_flags |= CX18_HW_GPIO_RESET_CTRL;
	पूर्ण

	/* active i2c  */
	CX18_DEBUG_INFO("activating i2c...\n");
	retval = init_cx18_i2c(cx);
	अगर (retval) अणु
		CX18_ERR("Could not initialize i2c\n");
		जाओ मुक्त_map;
	पूर्ण

	अगर (cx->card->hw_all & CX18_HW_TVEEPROM) अणु
		/* Based on the model number the cardtype may be changed.
		   The PCI IDs are not always reliable. */
		स्थिर काष्ठा cx18_card *orig_card = cx->card;
		cx18_process_eeprom(cx);

		अगर (cx->card != orig_card) अणु
			/* Changed the cardtype; re-reset the I2C chips */
			cx18_gpio_init(cx);
			cx18_call_hw(cx, CX18_HW_GPIO_RESET_CTRL,
					core, reset, (u32) CX18_GPIO_RESET_I2C);
		पूर्ण
	पूर्ण
	अगर (cx->card->comment)
		CX18_INFO("%s", cx->card->comment);
	अगर (cx->card->v4l2_capabilities == 0) अणु
		retval = -ENODEV;
		जाओ मुक्त_i2c;
	पूर्ण
	cx18_init_memory(cx);
	cx18_init_scb(cx);

	/* Register IRQ */
	retval = request_irq(cx->pci_dev->irq, cx18_irq_handler,
			     IRQF_SHARED, cx->v4l2_dev.name, (व्योम *)cx);
	अगर (retval) अणु
		CX18_ERR("Failed to register irq %d\n", retval);
		जाओ मुक्त_i2c;
	पूर्ण

	अगर (cx->std == 0)
		cx->std = V4L2_STD_NTSC_M;

	अगर (cx->options.tuner == -1) अणु
		क्रम (i = 0; i < CX18_CARD_MAX_TUNERS; i++) अणु
			अगर ((cx->std & cx->card->tuners[i].std) == 0)
				जारी;
			cx->options.tuner = cx->card->tuners[i].tuner;
			अवरोध;
		पूर्ण
	पूर्ण
	/* अगर no tuner was found, then pick the first tuner in the card list */
	अगर (cx->options.tuner == -1 && cx->card->tuners[0].std) अणु
		cx->std = cx->card->tuners[0].std;
		अगर (cx->std & V4L2_STD_PAL)
			cx->std = V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
		अन्यथा अगर (cx->std & V4L2_STD_NTSC)
			cx->std = V4L2_STD_NTSC_M;
		अन्यथा अगर (cx->std & V4L2_STD_SECAM)
			cx->std = V4L2_STD_SECAM_L;
		cx->options.tuner = cx->card->tuners[0].tuner;
	पूर्ण
	अगर (cx->options.radio == -1)
		cx->options.radio = (cx->card->radio_input.audio_type != 0);

	/* The card is now fully identअगरied, जारी with card-specअगरic
	   initialization. */
	cx18_init_काष्ठा2(cx);

	cx18_init_subdevs(cx);

	अगर (cx->std & V4L2_STD_525_60)
		cx->is_60hz = 1;
	अन्यथा
		cx->is_50hz = 1;

	cx2341x_handler_set_50hz(&cx->cxhdl, !cx->is_60hz);

	अगर (cx->options.radio > 0)
		cx->v4l2_cap |= V4L2_CAP_RADIO;

	अगर (cx->options.tuner > -1) अणु
		काष्ठा tuner_setup setup;

		setup.addr = ADDR_UNSET;
		setup.type = cx->options.tuner;
		setup.mode_mask = T_ANALOG_TV;  /* matches TV tuners */
		setup.config = शून्य;
		अगर (cx->options.radio > 0)
			setup.mode_mask |= T_RADIO;
		setup.tuner_callback = (setup.type == TUNER_XC2028) ?
			cx18_reset_tuner_gpio : शून्य;
		cx18_call_all(cx, tuner, s_type_addr, &setup);
		अगर (setup.type == TUNER_XC2028) अणु
			अटल काष्ठा xc2028_ctrl ctrl = अणु
				.fname = XC2028_DEFAULT_FIRMWARE,
				.max_len = 64,
			पूर्ण;
			काष्ठा v4l2_priv_tun_config cfg = अणु
				.tuner = cx->options.tuner,
				.priv = &ctrl,
			पूर्ण;
			cx18_call_all(cx, tuner, s_config, &cfg);
		पूर्ण
	पूर्ण

	/* The tuner is fixed to the standard. The other inमाला_दो (e.g. S-Video)
	   are not. */
	cx->tuner_std = cx->std;
	अगर (cx->std == V4L2_STD_ALL)
		cx->std = V4L2_STD_NTSC_M;

	retval = cx18_streams_setup(cx);
	अगर (retval) अणु
		CX18_ERR("Error %d setting up streams\n", retval);
		जाओ मुक्त_irq;
	पूर्ण
	retval = cx18_streams_रेजिस्टर(cx);
	अगर (retval) अणु
		CX18_ERR("Error %d registering devices\n", retval);
		जाओ मुक्त_streams;
	पूर्ण

	CX18_INFO("Initialized card: %s\n", cx->card_name);

	/* Load cx18 submodules (cx18-alsa) */
	request_modules(cx);
	वापस 0;

मुक्त_streams:
	cx18_streams_cleanup(cx, 1);
मुक्त_irq:
	मुक्त_irq(cx->pci_dev->irq, (व्योम *)cx);
मुक्त_i2c:
	निकास_cx18_i2c(cx);
मुक्त_map:
	cx18_iounmap(cx);
मुक्त_mem:
	release_mem_region(cx->base_addr, CX18_MEM_SIZE);
मुक्त_workqueues:
	destroy_workqueue(cx->in_work_queue);
err:
	CX18_ERR("Error %d on initialization\n", retval);

	v4l2_device_unरेजिस्टर(&cx->v4l2_dev);
	kमुक्त(cx);
	वापस retval;
पूर्ण

पूर्णांक cx18_init_on_first_खोलो(काष्ठा cx18 *cx)
अणु
	पूर्णांक video_input;
	पूर्णांक fw_retry_count = 3;
	काष्ठा v4l2_frequency vf;
	काष्ठा cx18_खोलो_id fh;
	v4l2_std_id std;

	fh.cx = cx;

	अगर (test_bit(CX18_F_I_FAILED, &cx->i_flags))
		वापस -ENXIO;

	अगर (test_and_set_bit(CX18_F_I_INITED, &cx->i_flags))
		वापस 0;

	जबतक (--fw_retry_count > 0) अणु
		/* load firmware */
		अगर (cx18_firmware_init(cx) == 0)
			अवरोध;
		अगर (fw_retry_count > 1)
			CX18_WARN("Retry loading firmware\n");
	पूर्ण

	अगर (fw_retry_count == 0) अणु
		set_bit(CX18_F_I_FAILED, &cx->i_flags);
		वापस -ENXIO;
	पूर्ण
	set_bit(CX18_F_I_LOADED_FW, &cx->i_flags);

	/*
	 * Init the firmware twice to work around a silicon bug
	 * with the digital TS.
	 *
	 * The second firmware load requires us to normalize the APU state,
	 * or the audio क्रम the first analog capture will be badly incorrect.
	 *
	 * I can't seem to call APU_RESETAI and have it succeed without the
	 * APU capturing audio, so we start and stop it here to करो the reset
	 */

	/* MPEG Encoding, 224 kbps, MPEG Layer II, 48 ksps */
	cx18_vapi(cx, CX18_APU_START, 2, CX18_APU_ENCODING_METHOD_MPEG|0xb9, 0);
	cx18_vapi(cx, CX18_APU_RESETAI, 0);
	cx18_vapi(cx, CX18_APU_STOP, 1, CX18_APU_ENCODING_METHOD_MPEG);

	fw_retry_count = 3;
	जबतक (--fw_retry_count > 0) अणु
		/* load firmware */
		अगर (cx18_firmware_init(cx) == 0)
			अवरोध;
		अगर (fw_retry_count > 1)
			CX18_WARN("Retry loading firmware\n");
	पूर्ण

	अगर (fw_retry_count == 0) अणु
		set_bit(CX18_F_I_FAILED, &cx->i_flags);
		वापस -ENXIO;
	पूर्ण

	/*
	 * The second firmware load requires us to normalize the APU state,
	 * or the audio क्रम the first analog capture will be badly incorrect.
	 *
	 * I can't seem to call APU_RESETAI and have it succeed without the
	 * APU capturing audio, so we start and stop it here to करो the reset
	 */

	/* MPEG Encoding, 224 kbps, MPEG Layer II, 48 ksps */
	cx18_vapi(cx, CX18_APU_START, 2, CX18_APU_ENCODING_METHOD_MPEG|0xb9, 0);
	cx18_vapi(cx, CX18_APU_RESETAI, 0);
	cx18_vapi(cx, CX18_APU_STOP, 1, CX18_APU_ENCODING_METHOD_MPEG);

	/* Init the A/V decoder, अगर it hasn't been alपढ़ोy */
	v4l2_subdev_call(cx->sd_av, core, load_fw);

	vf.tuner = 0;
	vf.type = V4L2_TUNER_ANALOG_TV;
	vf.frequency = 6400; /* the tuner 'baseline' frequency */

	/* Set initial frequency. For PAL/SECAM broadcasts no
	   'default' channel exists AFAIK. */
	अगर (cx->std == V4L2_STD_NTSC_M_JP)
		vf.frequency = 1460;	/* ch. 1 91250*16/1000 */
	अन्यथा अगर (cx->std & V4L2_STD_NTSC_M)
		vf.frequency = 1076;	/* ch. 4 67250*16/1000 */

	video_input = cx->active_input;
	cx->active_input++;	/* Force update of input */
	cx18_s_input(शून्य, &fh, video_input);

	/* Let the VIDIOC_S_STD ioctl करो all the work, keeps the code
	   in one place. */
	cx->std++;		/* Force full standard initialization */
	std = (cx->tuner_std == V4L2_STD_ALL) ? V4L2_STD_NTSC_M : cx->tuner_std;
	cx18_s_std(शून्य, &fh, std);
	cx18_s_frequency(शून्य, &fh, &vf);
	वापस 0;
पूर्ण

अटल व्योम cx18_cancel_in_work_orders(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++)
		cancel_work_sync(&cx->in_work_order[i].work);
पूर्ण

अटल व्योम cx18_cancel_out_work_orders(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_STREAMS; i++)
		अगर (cx->streams[i].video_dev.v4l2_dev)
			cancel_work_sync(&cx->streams[i].out_work_order);
पूर्ण

अटल व्योम cx18_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा cx18 *cx = to_cx18(v4l2_dev);
	पूर्णांक i;

	CX18_DEBUG_INFO("Removing Card\n");

	flush_request_modules(cx);

	/* Stop all captures */
	CX18_DEBUG_INFO("Stopping all streams\n");
	अगर (atomic_पढ़ो(&cx->tot_capturing) > 0)
		cx18_stop_all_captures(cx);

	/* Stop पूर्णांकerrupts that cause incoming work to be queued */
	cx18_sw1_irq_disable(cx, IRQ_CPU_TO_EPU | IRQ_APU_TO_EPU);

	/* Incoming work can cause outgoing work, so clean up incoming first */
	cx18_cancel_in_work_orders(cx);
	cx18_cancel_out_work_orders(cx);

	/* Stop ack पूर्णांकerrupts that may have been needed क्रम work to finish */
	cx18_sw2_irq_disable(cx, IRQ_CPU_TO_EPU_ACK | IRQ_APU_TO_EPU_ACK);

	cx18_halt_firmware(cx);

	destroy_workqueue(cx->in_work_queue);

	cx18_streams_cleanup(cx, 1);

	निकास_cx18_i2c(cx);

	मुक्त_irq(cx->pci_dev->irq, (व्योम *)cx);

	cx18_iounmap(cx);

	release_mem_region(cx->base_addr, CX18_MEM_SIZE);

	pci_disable_device(cx->pci_dev);

	अगर (cx->vbi.sliced_mpeg_data[0])
		क्रम (i = 0; i < CX18_VBI_FRAMES; i++)
			kमुक्त(cx->vbi.sliced_mpeg_data[i]);

	v4l2_ctrl_handler_मुक्त(&cx->av_state.hdl);

	CX18_INFO("Removed %s\n", cx->card_name);

	v4l2_device_unरेजिस्टर(v4l2_dev);
	kमुक्त(cx);
पूर्ण


/* define a pci_driver क्रम card detection */
अटल काष्ठा pci_driver cx18_pci_driver = अणु
      .name =     "cx18",
      .id_table = cx18_pci_tbl,
      .probe =    cx18_probe,
      .हटाओ =   cx18_हटाओ,
पूर्ण;

अटल पूर्णांक __init module_start(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "cx18:  Start initialization, version %s\n",
	       CX18_VERSION);

	/* Validate parameters */
	अगर (cx18_first_minor < 0 || cx18_first_minor >= CX18_MAX_CARDS) अणु
		prपूर्णांकk(KERN_ERR "cx18:  Exiting, cx18_first_minor must be between 0 and %d\n",
		     CX18_MAX_CARDS - 1);
		वापस -1;
	पूर्ण

	अगर (cx18_debug < 0 || cx18_debug > 511) अणु
		cx18_debug = 0;
		prपूर्णांकk(KERN_INFO "cx18:   Debug value must be >= 0 and <= 511!\n");
	पूर्ण

	अगर (pci_रेजिस्टर_driver(&cx18_pci_driver)) अणु
		prपूर्णांकk(KERN_ERR "cx18:   Error detecting PCI card\n");
		वापस -ENODEV;
	पूर्ण
	prपूर्णांकk(KERN_INFO "cx18:  End initialization\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास module_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cx18_pci_driver);
पूर्ण

module_init(module_start);
module_निकास(module_cleanup);
MODULE_FIRMWARE(XC2028_DEFAULT_FIRMWARE);
