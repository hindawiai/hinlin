<शैली गुरु>
/*
    ivtv driver initialization and card probing
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* Main Driver file क्रम the ivtv project:
 * Driver क्रम the Conexant CX23415/CX23416 chip.
 * Author: Kevin Thayer (nufan_wfk at yahoo.com)
 * License: GPL
 *
 * -----
 * MPG600/MPG160 support by  T.Adachi <tadachi@tadachi-net.com>
 *                      and Takeru KOMORIYA<komoriya@paken.org>
 *
 * AVerMedia M179 GPIO info by Chris Pinkham <cpinkham@bc2va.org>
 *                using inक्रमmation provided by Jiun-Kuei Jung @ AVerMedia.
 *
 * Kurouto Sikou CX23416GYC-STVLP tested by K.Ohta <alpha292@bremen.or.jp>
 *                using inक्रमmation from T.Adachi,Takeru KOMORIYA and others :-)
 *
 * Nagase TRANSGEAR 5000TV, Aखोलो VA2000MAX-STN6 and I/O data GV-MVP/RX
 *                version by T.Adachi. Special thanks  Mr.Suzuki
 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-version.h"
#समावेश "ivtv-fileops.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-firmware.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-udma.h"
#समावेश "ivtv-irq.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-streams.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-vbi.h"
#समावेश "ivtv-routing.h"
#समावेश "ivtv-controls.h"
#समावेश "ivtv-gpio.h"
#समावेश <linux/dma-mapping.h>
#समावेश <media/tveeprom.h>
#समावेश <media/i2c/saa7115.h>
#समावेश "tuner-xc2028.h"
#समावेश <uapi/linux/sched/types.h>

/* If you have alपढ़ोy X v4l cards, then set this to X. This way
   the device numbers stay matched. Example: you have a WinTV card
   without radio and a PVR-350 with. Normally this would give a
   video1 device together with a radio0 device क्रम the PVR. By
   setting this to 1 you ensure that radio0 is now also radio1. */
पूर्णांक ivtv_first_minor;

/* Callback क्रम रेजिस्टरing extensions */
पूर्णांक (*ivtv_ext_init)(काष्ठा ivtv *);
EXPORT_SYMBOL(ivtv_ext_init);

/* add your revision and whatnot here */
अटल स्थिर काष्ठा pci_device_id ivtv_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_ICOMP, PCI_DEVICE_ID_IVTV15,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ICOMP, PCI_DEVICE_ID_IVTV16,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci,ivtv_pci_tbl);

/* ivtv instance counter */
अटल atomic_t ivtv_instance = ATOMIC_INIT(0);

/* Parameter declarations */
अटल पूर्णांक cardtype[IVTV_MAX_CARDS];
अटल पूर्णांक tuner[IVTV_MAX_CARDS] = अणु -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक radio[IVTV_MAX_CARDS] = अणु -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक i2c_घड़ी_period[IVTV_MAX_CARDS] = अणु -1, -1, -1, -1, -1, -1, -1, -1,
					       -1, -1, -1, -1, -1, -1, -1, -1,
					       -1, -1, -1, -1, -1, -1, -1, -1,
					       -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;

अटल अचिन्हित पूर्णांक cardtype_c = 1;
अटल अचिन्हित पूर्णांक tuner_c = 1;
अटल पूर्णांक radio_c = 1;
अटल अचिन्हित पूर्णांक i2c_घड़ी_period_c = 1;
अटल अक्षर pal[] = "---";
अटल अक्षर secam[] = "--";
अटल अक्षर ntsc[] = "-";

/* Buffers */

/* DMA Buffers, Default size in MB allocated */
#घोषणा IVTV_DEFAULT_ENC_MPG_BUFFERS 4
#घोषणा IVTV_DEFAULT_ENC_YUV_BUFFERS 2
#घोषणा IVTV_DEFAULT_ENC_VBI_BUFFERS 1
/* Exception: size in kB क्रम this stream (MB is overसमाप्त) */
#घोषणा IVTV_DEFAULT_ENC_PCM_BUFFERS 320
#घोषणा IVTV_DEFAULT_DEC_MPG_BUFFERS 1
#घोषणा IVTV_DEFAULT_DEC_YUV_BUFFERS 1
/* Exception: size in kB क्रम this stream (MB is way overसमाप्त) */
#घोषणा IVTV_DEFAULT_DEC_VBI_BUFFERS 64

अटल पूर्णांक enc_mpg_buffers = IVTV_DEFAULT_ENC_MPG_BUFFERS;
अटल पूर्णांक enc_yuv_buffers = IVTV_DEFAULT_ENC_YUV_BUFFERS;
अटल पूर्णांक enc_vbi_buffers = IVTV_DEFAULT_ENC_VBI_BUFFERS;
अटल पूर्णांक enc_pcm_buffers = IVTV_DEFAULT_ENC_PCM_BUFFERS;
अटल पूर्णांक dec_mpg_buffers = IVTV_DEFAULT_DEC_MPG_BUFFERS;
अटल पूर्णांक dec_yuv_buffers = IVTV_DEFAULT_DEC_YUV_BUFFERS;
अटल पूर्णांक dec_vbi_buffers = IVTV_DEFAULT_DEC_VBI_BUFFERS;

अटल पूर्णांक ivtv_yuv_mode;
अटल पूर्णांक ivtv_yuv_threshold = -1;
अटल पूर्णांक ivtv_pci_latency = 1;

पूर्णांक ivtv_debug;
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
पूर्णांक ivtv_fw_debug;
#पूर्ण_अगर

अटल पूर्णांक tunertype = -1;
अटल पूर्णांक newi2c = -1;

module_param_array(tuner, पूर्णांक, &tuner_c, 0644);
module_param_array(radio, पूर्णांक, &radio_c, 0644);
module_param_array(cardtype, पूर्णांक, &cardtype_c, 0644);
module_param_string(pal, pal, माप(pal), 0644);
module_param_string(secam, secam, माप(secam), 0644);
module_param_string(ntsc, ntsc, माप(ntsc), 0644);
module_param_named(debug,ivtv_debug, पूर्णांक, 0644);
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
module_param_named(fw_debug, ivtv_fw_debug, पूर्णांक, 0644);
#पूर्ण_अगर
module_param(ivtv_pci_latency, पूर्णांक, 0644);
module_param(ivtv_yuv_mode, पूर्णांक, 0644);
module_param(ivtv_yuv_threshold, पूर्णांक, 0644);
module_param(ivtv_first_minor, पूर्णांक, 0644);

module_param(enc_mpg_buffers, पूर्णांक, 0644);
module_param(enc_yuv_buffers, पूर्णांक, 0644);
module_param(enc_vbi_buffers, पूर्णांक, 0644);
module_param(enc_pcm_buffers, पूर्णांक, 0644);
module_param(dec_mpg_buffers, पूर्णांक, 0644);
module_param(dec_yuv_buffers, पूर्णांक, 0644);
module_param(dec_vbi_buffers, पूर्णांक, 0644);

module_param(tunertype, पूर्णांक, 0644);
module_param(newi2c, पूर्णांक, 0644);
module_param_array(i2c_घड़ी_period, पूर्णांक, &i2c_घड़ी_period_c, 0644);

MODULE_PARM_DESC(tuner, "Tuner type selection,\n"
			"\t\t\tsee tuner.h for values");
MODULE_PARM_DESC(radio,
		 "Enable or disable the radio. Use only if autodetection\n"
		 "\t\t\tfails. 0 = disable, 1 = enable");
MODULE_PARM_DESC(cardtype,
		 "Only use this option if your card is not detected properly.\n"
		 "\t\tSpecify card type:\n"
		 "\t\t\t 1 = WinTV PVR 250\n"
		 "\t\t\t 2 = WinTV PVR 350\n"
		 "\t\t\t 3 = WinTV PVR-150 or PVR-500\n"
		 "\t\t\t 4 = AVerMedia M179\n"
		 "\t\t\t 5 = YUAN MPG600/Kuroutoshikou iTVC16-STVLP\n"
		 "\t\t\t 6 = YUAN MPG160/Kuroutoshikou iTVC15-STVLP\n"
		 "\t\t\t 7 = YUAN PG600/DIAMONDMM PVR-550 (CX Falcon 2)\n"
		 "\t\t\t 8 = Adaptec AVC-2410\n"
		 "\t\t\t 9 = Adaptec AVC-2010\n"
		 "\t\t\t10 = NAGASE TRANSGEAR 5000TV\n"
		 "\t\t\t11 = AOpen VA2000MAX-STN6\n"
		 "\t\t\t12 = YUAN MPG600GR/Kuroutoshikou CX23416GYC-STVLP\n"
		 "\t\t\t13 = I/O Data GV-MVP/RX\n"
		 "\t\t\t14 = I/O Data GV-MVP/RX2E\n"
		 "\t\t\t15 = GOTVIEW PCI DVD\n"
		 "\t\t\t16 = GOTVIEW PCI DVD2 Deluxe\n"
		 "\t\t\t17 = Yuan MPC622\n"
		 "\t\t\t18 = Digital Cowboy DCT-MTVP1\n"
		 "\t\t\t19 = Yuan PG600V2/GotView PCI DVD Lite\n"
		 "\t\t\t20 = Club3D ZAP-TV1x01\n"
		 "\t\t\t21 = AverTV MCE 116 Plus\n"
		 "\t\t\t22 = ASUS Falcon2\n"
		 "\t\t\t23 = AverMedia PVR-150 Plus\n"
		 "\t\t\t24 = AverMedia EZMaker PCI Deluxe\n"
		 "\t\t\t25 = AverMedia M104 (not yet working)\n"
		 "\t\t\t26 = Buffalo PC-MV5L/PCI\n"
		 "\t\t\t27 = AVerMedia UltraTV 1500 MCE\n"
		 "\t\t\t28 = Sony VAIO Giga Pocket (ENX Kikyou)\n"
		 "\t\t\t 0 = Autodetect (default)\n"
		 "\t\t\t-1 = Ignore this card\n\t\t");
MODULE_PARM_DESC(pal, "Set PAL standard: BGH, DK, I, M, N, Nc, 60");
MODULE_PARM_DESC(secam, "Set SECAM standard: BGH, DK, L, LC");
MODULE_PARM_DESC(ntsc, "Set NTSC standard: M, J (Japan), K (South Korea)");
MODULE_PARM_DESC(tunertype,
		"Specify tuner type:\n"
		"\t\t\t 0 = tuner for PAL-B/G/H/D/K/I, SECAM-B/G/H/D/K/L/Lc\n"
		"\t\t\t 1 = tuner for NTSC-M/J/K, PAL-M/N/Nc\n"
		"\t\t\t-1 = Autodetect (default)\n");
MODULE_PARM_DESC(debug,
		 "Debug level (bitmask). Default: 0\n"
		 "\t\t\t   1/0x0001: warning\n"
		 "\t\t\t   2/0x0002: info\n"
		 "\t\t\t   4/0x0004: mailbox\n"
		 "\t\t\t   8/0x0008: ioctl\n"
		 "\t\t\t  16/0x0010: file\n"
		 "\t\t\t  32/0x0020: dma\n"
		 "\t\t\t  64/0x0040: irq\n"
		 "\t\t\t 128/0x0080: decoder\n"
		 "\t\t\t 256/0x0100: yuv\n"
		 "\t\t\t 512/0x0200: i2c\n"
		 "\t\t\t1024/0x0400: high volume\n");
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
MODULE_PARM_DESC(fw_debug,
		 "Enable code for debugging firmware problems.  Default: 0\n");
#पूर्ण_अगर
MODULE_PARM_DESC(ivtv_pci_latency,
		 "Change the PCI latency to 64 if lower: 0 = No, 1 = Yes,\n"
		 "\t\t\tDefault: Yes");
MODULE_PARM_DESC(ivtv_yuv_mode,
		 "Specify the yuv playback mode:\n"
		 "\t\t\t0 = interlaced\n\t\t\t1 = progressive\n\t\t\t2 = auto\n"
		 "\t\t\tDefault: 0 (interlaced)");
MODULE_PARM_DESC(ivtv_yuv_threshold,
		 "If ivtv_yuv_mode is 2 (auto) then playback content as\n\t\tprogressive if src height <= ivtv_yuvthreshold\n"
		 "\t\t\tDefault: 480");
MODULE_PARM_DESC(enc_mpg_buffers,
		 "Encoder MPG Buffers (in MB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_ENC_MPG_BUFFERS));
MODULE_PARM_DESC(enc_yuv_buffers,
		 "Encoder YUV Buffers (in MB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_ENC_YUV_BUFFERS));
MODULE_PARM_DESC(enc_vbi_buffers,
		 "Encoder VBI Buffers (in MB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_ENC_VBI_BUFFERS));
MODULE_PARM_DESC(enc_pcm_buffers,
		 "Encoder PCM buffers (in kB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_ENC_PCM_BUFFERS));
MODULE_PARM_DESC(dec_mpg_buffers,
		 "Decoder MPG buffers (in MB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_DEC_MPG_BUFFERS));
MODULE_PARM_DESC(dec_yuv_buffers,
		 "Decoder YUV buffers (in MB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_DEC_YUV_BUFFERS));
MODULE_PARM_DESC(dec_vbi_buffers,
		 "Decoder VBI buffers (in kB)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_DEC_VBI_BUFFERS));
MODULE_PARM_DESC(newi2c,
		 "Use new I2C implementation\n"
		 "\t\t\t-1 is autodetect, 0 is off, 1 is on\n"
		 "\t\t\tDefault is autodetect");
MODULE_PARM_DESC(i2c_घड़ी_period,
		 "Period of SCL for the I2C bus controlled by the CX23415/6\n"
		 "\t\t\tMin: 10 usec (100 kHz), Max: 4500 usec (222 Hz)\n"
		 "\t\t\tDefault: " __stringअगरy(IVTV_DEFAULT_I2C_CLOCK_PERIOD));

MODULE_PARM_DESC(ivtv_first_minor, "Set device node number assigned to first card");

MODULE_AUTHOR("Kevin Thayer, Chris Kennedy, Hans Verkuil");
MODULE_DESCRIPTION("CX23415/CX23416 driver");
MODULE_LICENSE("GPL");

MODULE_VERSION(IVTV_VERSION);

#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ivtv *dev = container_of(work, काष्ठा ivtv, request_module_wk);

	/* Make sure ivtv-alsa module is loaded */
	request_module("ivtv-alsa");

	/* Initialize ivtv-alsa क्रम this instance of the cx18 device */
	अगर (ivtv_ext_init != शून्य)
		ivtv_ext_init(dev);
पूर्ण

अटल व्योम request_modules(काष्ठा ivtv *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा ivtv *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

व्योम ivtv_clear_irq_mask(काष्ठा ivtv *itv, u32 mask)
अणु
	itv->irqmask &= ~mask;
	ग_लिखो_reg_sync(itv->irqmask, IVTV_REG_IRQMASK);
पूर्ण

व्योम ivtv_set_irq_mask(काष्ठा ivtv *itv, u32 mask)
अणु
	itv->irqmask |= mask;
	ग_लिखो_reg_sync(itv->irqmask, IVTV_REG_IRQMASK);
पूर्ण

पूर्णांक ivtv_set_output_mode(काष्ठा ivtv *itv, पूर्णांक mode)
अणु
    पूर्णांक old_mode;

    spin_lock(&itv->lock);
    old_mode = itv->output_mode;
    अगर (old_mode == 0)
	itv->output_mode = old_mode = mode;
    spin_unlock(&itv->lock);
    वापस old_mode;
पूर्ण

काष्ठा ivtv_stream *ivtv_get_output_stream(काष्ठा ivtv *itv)
अणु
	चयन (itv->output_mode) अणु
	हाल OUT_MPG:
		वापस &itv->streams[IVTV_DEC_STREAM_TYPE_MPG];
	हाल OUT_YUV:
		वापस &itv->streams[IVTV_DEC_STREAM_TYPE_YUV];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

पूर्णांक ivtv_रुकोq(रुको_queue_head_t *रुकोq)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(रुकोq, &रुको, TASK_INTERRUPTIBLE);
	schedule();
	finish_रुको(रुकोq, &रुको);
	वापस संकेत_pending(current) ? -EINTR : 0;
पूर्ण

/* Generic utility functions */
पूर्णांक ivtv_msleep_समयout(अचिन्हित पूर्णांक msecs, पूर्णांक पूर्णांकr)
अणु
	पूर्णांक समयout = msecs_to_jअगरfies(msecs);

	करो अणु
		set_current_state(पूर्णांकr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		समयout = schedule_समयout(समयout);
		अगर (पूर्णांकr) अणु
			पूर्णांक ret = संकेत_pending(current);

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण जबतक (समयout);
	वापस 0;
पूर्ण

/* Release ioremapped memory */
अटल व्योम ivtv_iounmap(काष्ठा ivtv *itv)
अणु
	अगर (itv == शून्य)
		वापस;

	/* Release रेजिस्टरs memory */
	अगर (itv->reg_mem != शून्य) अणु
		IVTV_DEBUG_INFO("releasing reg_mem\n");
		iounmap(itv->reg_mem);
		itv->reg_mem = शून्य;
	पूर्ण
	/* Release io memory */
	अगर (itv->has_cx23415 && itv->dec_mem != शून्य) अणु
		IVTV_DEBUG_INFO("releasing dec_mem\n");
		iounmap(itv->dec_mem);
	पूर्ण
	itv->dec_mem = शून्य;

	/* Release io memory */
	अगर (itv->enc_mem != शून्य) अणु
		IVTV_DEBUG_INFO("releasing enc_mem\n");
		iounmap(itv->enc_mem);
		itv->enc_mem = शून्य;
	पूर्ण
पूर्ण

/* Hauppauge card? get values from tveeprom */
व्योम ivtv_पढ़ो_eeprom(काष्ठा ivtv *itv, काष्ठा tveeprom *tv)
अणु
	u8 eedata[256];

	itv->i2c_client.addr = 0xA0 >> 1;
	tveeprom_पढ़ो(&itv->i2c_client, eedata, माप(eedata));
	tveeprom_hauppauge_analog(tv, eedata);
पूर्ण

अटल व्योम ivtv_process_eeprom(काष्ठा ivtv *itv)
अणु
	काष्ठा tveeprom tv;
	पूर्णांक pci_slot = PCI_SLOT(itv->pdev->devfn);

	ivtv_पढ़ो_eeprom(itv, &tv);

	/* Many thanks to Steven Toth from Hauppauge क्रम providing the
	   model numbers */
	चयन (tv.model) अणु
		/* In a few हालs the PCI subप्रणाली IDs करो not correctly
		   identअगरy the card. A better method is to check the
		   model number from the eeprom instead. */
		हाल 30012 ... 30039:  /* Low profile PVR250 */
		हाल 32000 ... 32999:
		हाल 48000 ... 48099:  /* 48??? range are PVR250s with a cx23415 */
		हाल 48400 ... 48599:
			itv->card = ivtv_get_card(IVTV_CARD_PVR_250);
			अवरोध;
		हाल 48100 ... 48399:
		हाल 48600 ... 48999:
			itv->card = ivtv_get_card(IVTV_CARD_PVR_350);
			अवरोध;
		हाल 23000 ... 23999:  /* PVR500 */
		हाल 25000 ... 25999:  /* Low profile PVR150 */
		हाल 26000 ... 26999:  /* Regular PVR150 */
			itv->card = ivtv_get_card(IVTV_CARD_PVR_150);
			अवरोध;
		हाल 0:
			IVTV_ERR("Invalid EEPROM\n");
			वापस;
		शेष:
			IVTV_ERR("Unknown model %d, defaulting to PVR-150\n", tv.model);
			itv->card = ivtv_get_card(IVTV_CARD_PVR_150);
			अवरोध;
	पूर्ण

	चयन (tv.model) अणु
		/* Old style PVR350 (with an saa7114) uses this input क्रम
		   the tuner. */
		हाल 48254:
			itv->card = ivtv_get_card(IVTV_CARD_PVR_350_V1);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	itv->v4l2_cap = itv->card->v4l2_capabilities;
	itv->card_name = itv->card->name;
	itv->card_i2c = itv->card->i2c;

	/* If this is a PVR500 then it should be possible to detect whether it is the
	   first or second unit by looking at the subप्रणाली device ID: is bit 4 is
	   set, then it is the second unit (according to info from Hauppauge).

	   However, जबतक this works क्रम most cards, I have seen a few PVR500 cards
	   where both units have the same subप्रणाली ID.

	   So instead I look at the reported 'PCI slot' (which is the slot on the PVR500
	   PCI bridge) and अगर it is 8, then it is assumed to be the first unit, otherwise
	   it is the second unit. It is possible that it is a dअगरferent slot when ivtv is
	   used in Xen, in that हाल I ignore this card here. The worst that can happen
	   is that the card presents itself with a non-working radio device.

	   This detection is needed since the eeprom reports incorrectly that a radio is
	   present on the second unit. */
	अगर (tv.model / 1000 == 23) अणु
		अटल स्थिर काष्ठा ivtv_card_tuner_i2c ivtv_i2c_radio = अणु
			.radio = अणु 0x60, I2C_CLIENT_END पूर्ण,
			.demod = अणु 0x43, I2C_CLIENT_END पूर्ण,
			.tv = अणु 0x61, I2C_CLIENT_END पूर्ण,
		पूर्ण;

		itv->card_name = "WinTV PVR 500";
		itv->card_i2c = &ivtv_i2c_radio;
		अगर (pci_slot == 8 || pci_slot == 9) अणु
			पूर्णांक is_first = (pci_slot & 1) == 0;

			itv->card_name = is_first ? "WinTV PVR 500 (unit #1)" :
						    "WinTV PVR 500 (unit #2)";
			अगर (!is_first) अणु
				IVTV_INFO("Correcting tveeprom data: no radio present on second unit\n");
				tv.has_radio = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	IVTV_INFO("Autodetected %s\n", itv->card_name);

	चयन (tv.tuner_hauppauge_model) अणु
		हाल 85:
		हाल 99:
		हाल 112:
			itv->pvr150_workaround = 1;
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण
	अगर (tv.tuner_type == TUNER_ABSENT)
		IVTV_ERR("tveeprom cannot autodetect tuner!\n");

	अगर (itv->options.tuner == -1)
		itv->options.tuner = tv.tuner_type;
	अगर (itv->options.radio == -1)
		itv->options.radio = (tv.has_radio != 0);
	/* only enable newi2c अगर an IR blaster is present */
	अगर (itv->options.newi2c == -1 && tv.has_ir) अणु
		itv->options.newi2c = (tv.has_ir & 4) ? 1 : 0;
		अगर (itv->options.newi2c) अणु
		    IVTV_INFO("Reopen i2c bus for IR-blaster support\n");
		    निकास_ivtv_i2c(itv);
		    init_ivtv_i2c(itv);
		पूर्ण
	पूर्ण

	अगर (itv->std != 0)
		/* user specअगरied tuner standard */
		वापस;

	/* स्वतःdetect tuner standard */
	अगर (tv.tuner_क्रमmats & V4L2_STD_PAL) अणु
		IVTV_DEBUG_INFO("PAL tuner detected\n");
		itv->std |= V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
	पूर्ण अन्यथा अगर (tv.tuner_क्रमmats & V4L2_STD_NTSC) अणु
		IVTV_DEBUG_INFO("NTSC tuner detected\n");
		itv->std |= V4L2_STD_NTSC_M;
	पूर्ण अन्यथा अगर (tv.tuner_क्रमmats & V4L2_STD_SECAM) अणु
		IVTV_DEBUG_INFO("SECAM tuner detected\n");
		itv->std |= V4L2_STD_SECAM_L;
	पूर्ण अन्यथा अणु
		IVTV_INFO("No tuner detected, default to NTSC-M\n");
		itv->std |= V4L2_STD_NTSC_M;
	पूर्ण
पूर्ण

अटल v4l2_std_id ivtv_parse_std(काष्ठा ivtv *itv)
अणु
	चयन (pal[0]) अणु
		हाल '6':
			tunertype = 0;
			वापस V4L2_STD_PAL_60;
		हाल 'b':
		हाल 'B':
		हाल 'g':
		हाल 'G':
		हाल 'h':
		हाल 'H':
			tunertype = 0;
			वापस V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
		हाल 'n':
		हाल 'N':
			tunertype = 1;
			अगर (pal[1] == 'c' || pal[1] == 'C')
				वापस V4L2_STD_PAL_Nc;
			वापस V4L2_STD_PAL_N;
		हाल 'i':
		हाल 'I':
			tunertype = 0;
			वापस V4L2_STD_PAL_I;
		हाल 'd':
		हाल 'D':
		हाल 'k':
		हाल 'K':
			tunertype = 0;
			वापस V4L2_STD_PAL_DK;
		हाल 'M':
		हाल 'm':
			tunertype = 1;
			वापस V4L2_STD_PAL_M;
		हाल '-':
			अवरोध;
		शेष:
			IVTV_WARN("pal= argument not recognised\n");
			वापस 0;
	पूर्ण

	चयन (secam[0]) अणु
		हाल 'b':
		हाल 'B':
		हाल 'g':
		हाल 'G':
		हाल 'h':
		हाल 'H':
			tunertype = 0;
			वापस V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H;
		हाल 'd':
		हाल 'D':
		हाल 'k':
		हाल 'K':
			tunertype = 0;
			वापस V4L2_STD_SECAM_DK;
		हाल 'l':
		हाल 'L':
			tunertype = 0;
			अगर (secam[1] == 'C' || secam[1] == 'c')
				वापस V4L2_STD_SECAM_LC;
			वापस V4L2_STD_SECAM_L;
		हाल '-':
			अवरोध;
		शेष:
			IVTV_WARN("secam= argument not recognised\n");
			वापस 0;
	पूर्ण

	चयन (ntsc[0]) अणु
		हाल 'm':
		हाल 'M':
			tunertype = 1;
			वापस V4L2_STD_NTSC_M;
		हाल 'j':
		हाल 'J':
			tunertype = 1;
			वापस V4L2_STD_NTSC_M_JP;
		हाल 'k':
		हाल 'K':
			tunertype = 1;
			वापस V4L2_STD_NTSC_M_KR;
		हाल '-':
			अवरोध;
		शेष:
			IVTV_WARN("ntsc= argument not recognised\n");
			वापस 0;
	पूर्ण

	/* no match found */
	वापस 0;
पूर्ण

अटल व्योम ivtv_process_options(काष्ठा ivtv *itv)
अणु
	स्थिर अक्षर *chipname;
	पूर्णांक i, j;

	itv->options.kilobytes[IVTV_ENC_STREAM_TYPE_MPG] = enc_mpg_buffers * 1024;
	itv->options.kilobytes[IVTV_ENC_STREAM_TYPE_YUV] = enc_yuv_buffers * 1024;
	itv->options.kilobytes[IVTV_ENC_STREAM_TYPE_VBI] = enc_vbi_buffers * 1024;
	itv->options.kilobytes[IVTV_ENC_STREAM_TYPE_PCM] = enc_pcm_buffers;
	itv->options.kilobytes[IVTV_DEC_STREAM_TYPE_MPG] = dec_mpg_buffers * 1024;
	itv->options.kilobytes[IVTV_DEC_STREAM_TYPE_YUV] = dec_yuv_buffers * 1024;
	itv->options.kilobytes[IVTV_DEC_STREAM_TYPE_VBI] = dec_vbi_buffers;
	itv->options.cardtype = cardtype[itv->instance];
	itv->options.tuner = tuner[itv->instance];
	itv->options.radio = radio[itv->instance];

	itv->options.i2c_घड़ी_period = i2c_घड़ी_period[itv->instance];
	अगर (itv->options.i2c_घड़ी_period == -1)
		itv->options.i2c_घड़ी_period = IVTV_DEFAULT_I2C_CLOCK_PERIOD;
	अन्यथा अगर (itv->options.i2c_घड़ी_period < 10)
		itv->options.i2c_घड़ी_period = 10;
	अन्यथा अगर (itv->options.i2c_घड़ी_period > 4500)
		itv->options.i2c_घड़ी_period = 4500;

	itv->options.newi2c = newi2c;
	अगर (tunertype < -1 || tunertype > 1) अणु
		IVTV_WARN("Invalid tunertype argument, will autodetect instead\n");
		tunertype = -1;
	पूर्ण
	itv->std = ivtv_parse_std(itv);
	अगर (itv->std == 0 && tunertype >= 0)
		itv->std = tunertype ? V4L2_STD_MN : (V4L2_STD_ALL & ~V4L2_STD_MN);
	itv->has_cx23415 = (itv->pdev->device == PCI_DEVICE_ID_IVTV15);
	chipname = itv->has_cx23415 ? "cx23415" : "cx23416";
	अगर (itv->options.cardtype == -1) अणु
		IVTV_INFO("Ignore card (detected %s based chip)\n", chipname);
		वापस;
	पूर्ण
	अगर ((itv->card = ivtv_get_card(itv->options.cardtype - 1))) अणु
		IVTV_INFO("User specified %s card (detected %s based chip)\n",
				itv->card->name, chipname);
	पूर्ण अन्यथा अगर (itv->options.cardtype != 0) अणु
		IVTV_ERR("Unknown user specified type, trying to autodetect card\n");
	पूर्ण
	अगर (itv->card == शून्य) अणु
		अगर (itv->pdev->subप्रणाली_venकरोr == IVTV_PCI_ID_HAUPPAUGE ||
		    itv->pdev->subप्रणाली_venकरोr == IVTV_PCI_ID_HAUPPAUGE_ALT1 ||
		    itv->pdev->subप्रणाली_venकरोr == IVTV_PCI_ID_HAUPPAUGE_ALT2) अणु
			itv->card = ivtv_get_card(itv->has_cx23415 ? IVTV_CARD_PVR_350 : IVTV_CARD_PVR_150);
			IVTV_INFO("Autodetected Hauppauge card (%s based)\n",
					chipname);
		पूर्ण
	पूर्ण
	अगर (itv->card == शून्य) अणु
		क्रम (i = 0; (itv->card = ivtv_get_card(i)); i++) अणु
			अगर (itv->card->pci_list == शून्य)
				जारी;
			क्रम (j = 0; itv->card->pci_list[j].device; j++) अणु
				अगर (itv->pdev->device !=
				    itv->card->pci_list[j].device)
					जारी;
				अगर (itv->pdev->subप्रणाली_venकरोr !=
				    itv->card->pci_list[j].subप्रणाली_venकरोr)
					जारी;
				अगर (itv->pdev->subप्रणाली_device !=
				    itv->card->pci_list[j].subप्रणाली_device)
					जारी;
				IVTV_INFO("Autodetected %s card (%s based)\n",
						itv->card->name, chipname);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:

	अगर (itv->card == शून्य) अणु
		itv->card = ivtv_get_card(IVTV_CARD_PVR_150);
		IVTV_ERR("Unknown card: vendor/device: [%04x:%04x]\n",
		     itv->pdev->venकरोr, itv->pdev->device);
		IVTV_ERR("              subsystem vendor/device: [%04x:%04x]\n",
		     itv->pdev->subप्रणाली_venकरोr, itv->pdev->subप्रणाली_device);
		IVTV_ERR("              %s based\n", chipname);
		IVTV_ERR("Defaulting to %s card\n", itv->card->name);
		IVTV_ERR("Please mail the vendor/device and subsystem vendor/device IDs and what kind of\n");
		IVTV_ERR("card you have to the linux-media mailinglist (www.linuxtv.org)\n");
		IVTV_ERR("Prefix your subject line with [UNKNOWN IVTV CARD].\n");
	पूर्ण
	itv->v4l2_cap = itv->card->v4l2_capabilities;
	itv->card_name = itv->card->name;
	itv->card_i2c = itv->card->i2c;
पूर्ण

/* Precondition: the ivtv काष्ठाure has been स_रखो to 0. Only
   the dev and num fields have been filled in.
   No assumptions on the card type may be made here (see ivtv_init_काष्ठा2
   क्रम that).
 */
अटल पूर्णांक ivtv_init_काष्ठा1(काष्ठा ivtv *itv)
अणु
	itv->base_addr = pci_resource_start(itv->pdev, 0);
	itv->enc_mbox.max_mbox = 2; /* the encoder has 3 mailboxes (0-2) */
	itv->dec_mbox.max_mbox = 1; /* the decoder has 2 mailboxes (0-1) */

	mutex_init(&itv->serialize_lock);
	mutex_init(&itv->i2c_bus_lock);
	mutex_init(&itv->udma.lock);

	spin_lock_init(&itv->lock);
	spin_lock_init(&itv->dma_reg_lock);

	kthपढ़ो_init_worker(&itv->irq_worker);
	itv->irq_worker_task = kthपढ़ो_run(kthपढ़ो_worker_fn, &itv->irq_worker,
					   "%s", itv->v4l2_dev.name);
	अगर (IS_ERR(itv->irq_worker_task)) अणु
		IVTV_ERR("Could not create ivtv task\n");
		वापस -1;
	पूर्ण
	/* must use the FIFO scheduler as it is realसमय sensitive */
	sched_set_fअगरo(itv->irq_worker_task);

	kthपढ़ो_init_work(&itv->irq_work, ivtv_irq_work_handler);

	/* Initial settings */
	itv->cxhdl.port = CX2341X_PORT_MEMORY;
	itv->cxhdl.capabilities = CX2341X_CAP_HAS_SLICED_VBI;
	init_रुकोqueue_head(&itv->eos_रुकोq);
	init_रुकोqueue_head(&itv->event_रुकोq);
	init_रुकोqueue_head(&itv->vsync_रुकोq);
	init_रुकोqueue_head(&itv->dma_रुकोq);
	समयr_setup(&itv->dma_समयr, ivtv_unfinished_dma, 0);

	itv->cur_dma_stream = -1;
	itv->cur_pio_stream = -1;

	/* Ctrls */
	itv->speed = 1000;

	/* VBI */
	itv->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;
	itv->vbi.sliced_in = &itv->vbi.in.fmt.sliced;

	/* Init the sg table क्रम osd/yuv output */
	sg_init_table(itv->udma.SGlist, IVTV_DMA_SG_OSD_ENT);

	/* OSD */
	itv->osd_global_alpha_state = 1;
	itv->osd_global_alpha = 255;

	/* YUV */
	atomic_set(&itv->yuv_info.next_dma_frame, -1);
	itv->yuv_info.lace_mode = ivtv_yuv_mode;
	itv->yuv_info.lace_threshold = ivtv_yuv_threshold;
	itv->yuv_info.max_frames_buffered = 3;
	itv->yuv_info.track_osd = 1;
	वापस 0;
पूर्ण

/* Second initialization part. Here the card type has been
   स्वतःdetected. */
अटल व्योम ivtv_init_काष्ठा2(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IVTV_CARD_MAX_VIDEO_INPUTS; i++)
		अगर (itv->card->video_inमाला_दो[i].video_type == 0)
			अवरोध;
	itv->nof_inमाला_दो = i;
	क्रम (i = 0; i < IVTV_CARD_MAX_AUDIO_INPUTS; i++)
		अगर (itv->card->audio_inमाला_दो[i].audio_type == 0)
			अवरोध;
	itv->nof_audio_inमाला_दो = i;

	अगर (itv->card->hw_all & IVTV_HW_CX25840) अणु
		itv->vbi.sliced_size = 288;  /* multiple of 16, real size = 284 */
	पूर्ण अन्यथा अणु
		itv->vbi.sliced_size = 64;   /* multiple of 16, real size = 52 */
	पूर्ण

	/* Find tuner input */
	क्रम (i = 0; i < itv->nof_inमाला_दो; i++) अणु
		अगर (itv->card->video_inमाला_दो[i].video_type ==
				IVTV_CARD_INPUT_VID_TUNER)
			अवरोध;
	पूर्ण
	अगर (i >= itv->nof_inमाला_दो)
		i = 0;
	itv->active_input = i;
	itv->audio_input = itv->card->video_inमाला_दो[i].audio_index;
पूर्ण

अटल पूर्णांक ivtv_setup_pci(काष्ठा ivtv *itv, काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	u16 cmd;
	अचिन्हित अक्षर pci_latency;

	IVTV_DEBUG_INFO("Enabling pci device\n");

	अगर (pci_enable_device(pdev)) अणु
		IVTV_ERR("Can't enable device!\n");
		वापस -EIO;
	पूर्ण
	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) अणु
		IVTV_ERR("No suitable DMA available.\n");
		वापस -EIO;
	पूर्ण
	अगर (!request_mem_region(itv->base_addr, IVTV_ENCODER_SIZE, "ivtv encoder")) अणु
		IVTV_ERR("Cannot request encoder memory region.\n");
		वापस -EIO;
	पूर्ण

	अगर (!request_mem_region(itv->base_addr + IVTV_REG_OFFSET,
				IVTV_REG_SIZE, "ivtv registers")) अणु
		IVTV_ERR("Cannot request register memory region.\n");
		release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
		वापस -EIO;
	पूर्ण

	अगर (itv->has_cx23415 &&
	    !request_mem_region(itv->base_addr + IVTV_DECODER_OFFSET,
				IVTV_DECODER_SIZE, "ivtv decoder")) अणु
		IVTV_ERR("Cannot request decoder memory region.\n");
		release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
		release_mem_region(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
		वापस -EIO;
	पूर्ण

	/* Check क्रम bus mastering */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर (!(cmd & PCI_COMMAND_MASTER)) अणु
		IVTV_DEBUG_INFO("Attempting to enable Bus Mastering\n");
		pci_set_master(pdev);
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
		अगर (!(cmd & PCI_COMMAND_MASTER)) अणु
			IVTV_ERR("Bus Mastering is not enabled\n");
			अगर (itv->has_cx23415)
				release_mem_region(itv->base_addr + IVTV_DECODER_OFFSET,
						   IVTV_DECODER_SIZE);
			release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
			release_mem_region(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	IVTV_DEBUG_INFO("Bus Mastering Enabled.\n");

	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &pci_latency);

	अगर (pci_latency < 64 && ivtv_pci_latency) अणु
		IVTV_INFO("Unreasonably low latency timer, setting to 64 (was %d)\n",
			  pci_latency);
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 64);
		pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &pci_latency);
	पूर्ण
	/* This config space value relates to DMA latencies. The
	   शेष value 0x8080 is too low however and will lead
	   to DMA errors. 0xffff is the max value which solves
	   these problems. */
	pci_ग_लिखो_config_dword(pdev, 0x40, 0xffff);

	IVTV_DEBUG_INFO("%d (rev %d) at %02x:%02x.%x, irq: %d, latency: %d, memory: 0x%llx\n",
		   pdev->device, pdev->revision, pdev->bus->number,
		   PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
		   pdev->irq, pci_latency, (u64)itv->base_addr);

	वापस 0;
पूर्ण

अटल व्योम ivtv_load_and_init_modules(काष्ठा ivtv *itv)
अणु
	u32 hw = itv->card->hw_all;
	अचिन्हित i;

	/* check which i2c devices are actually found */
	क्रम (i = 0; i < 32; i++) अणु
		u32 device = BIT(i);

		अगर (!(device & hw))
			जारी;
		अगर (device == IVTV_HW_GPIO || device == IVTV_HW_TVEEPROM) अणु
			/* GPIO and TVEEPROM करो not use i2c probing */
			itv->hw_flags |= device;
			जारी;
		पूर्ण
		अगर (ivtv_i2c_रेजिस्टर(itv, i) == 0)
			itv->hw_flags |= device;
	पूर्ण

	/* probe क्रम legacy IR controllers that aren't in card definitions */
	अगर ((itv->hw_flags & IVTV_HW_IR_ANY) == 0)
		ivtv_i2c_new_ir_legacy(itv);

	अगर (itv->card->hw_all & IVTV_HW_CX25840)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_CX25840);
	अन्यथा अगर (itv->card->hw_all & IVTV_HW_SAA717X)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA717X);
	अन्यथा अगर (itv->card->hw_all & IVTV_HW_SAA7114)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA7114);
	अन्यथा
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA7115);
	itv->sd_audio = ivtv_find_hw(itv, itv->card->hw_audio_ctrl);
	itv->sd_muxer = ivtv_find_hw(itv, itv->card->hw_muxer);

	hw = itv->hw_flags;

	अगर (itv->card->type == IVTV_CARD_CX23416GYC) अणु
		/* Several variations of this card exist, detect which card
		   type should be used. */
		अगर ((hw & (IVTV_HW_UPD64031A | IVTV_HW_UPD6408X)) == 0)
			itv->card = ivtv_get_card(IVTV_CARD_CX23416GYC_NOGRYCS);
		अन्यथा अगर ((hw & IVTV_HW_UPD64031A) == 0)
			itv->card = ivtv_get_card(IVTV_CARD_CX23416GYC_NOGR);
	पूर्ण
	अन्यथा अगर (itv->card->type == IVTV_CARD_GV_MVPRX ||
		 itv->card->type == IVTV_CARD_GV_MVPRX2E) अणु
		/* The crystal frequency of GVMVPRX is 24.576MHz */
		v4l2_subdev_call(itv->sd_video, video, s_crystal_freq,
			SAA7115_FREQ_24_576_MHZ, SAA7115_FREQ_FL_UCGC);
	पूर्ण

	अगर (hw & IVTV_HW_CX25840) अणु
		itv->vbi.raw_decoder_line_size = 1444;
		itv->vbi.raw_decoder_sav_odd_field = 0x20;
		itv->vbi.raw_decoder_sav_even_field = 0x60;
		itv->vbi.sliced_decoder_line_size = 272;
		itv->vbi.sliced_decoder_sav_odd_field = 0xB0;
		itv->vbi.sliced_decoder_sav_even_field = 0xF0;
	पूर्ण

	अगर (hw & IVTV_HW_SAA711X) अणु
		/* determine the exact saa711x model */
		itv->hw_flags &= ~IVTV_HW_SAA711X;

		अगर (म_माला(itv->sd_video->name, "saa7114")) अणु
			itv->hw_flags |= IVTV_HW_SAA7114;
			/* VBI is not yet supported by the saa7114 driver. */
			itv->v4l2_cap &= ~(V4L2_CAP_SLICED_VBI_CAPTURE|V4L2_CAP_VBI_CAPTURE);
		पूर्ण अन्यथा अणु
			itv->hw_flags |= IVTV_HW_SAA7115;
		पूर्ण
		itv->vbi.raw_decoder_line_size = 1443;
		itv->vbi.raw_decoder_sav_odd_field = 0x25;
		itv->vbi.raw_decoder_sav_even_field = 0x62;
		itv->vbi.sliced_decoder_line_size = 51;
		itv->vbi.sliced_decoder_sav_odd_field = 0xAB;
		itv->vbi.sliced_decoder_sav_even_field = 0xEC;
	पूर्ण

	अगर (hw & IVTV_HW_SAA717X) अणु
		itv->vbi.raw_decoder_line_size = 1443;
		itv->vbi.raw_decoder_sav_odd_field = 0x25;
		itv->vbi.raw_decoder_sav_even_field = 0x62;
		itv->vbi.sliced_decoder_line_size = 51;
		itv->vbi.sliced_decoder_sav_odd_field = 0xAB;
		itv->vbi.sliced_decoder_sav_even_field = 0xEC;
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक retval = 0;
	पूर्णांक vbi_buf_size;
	काष्ठा ivtv *itv;

	itv = kzalloc(माप(काष्ठा ivtv), GFP_KERNEL);
	अगर (itv == शून्य)
		वापस -ENOMEM;
	itv->pdev = pdev;
	itv->instance = v4l2_device_set_name(&itv->v4l2_dev, "ivtv",
						&ivtv_instance);

	retval = v4l2_device_रेजिस्टर(&pdev->dev, &itv->v4l2_dev);
	अगर (retval) अणु
		kमुक्त(itv);
		वापस retval;
	पूर्ण
	IVTV_INFO("Initializing card %d\n", itv->instance);

	ivtv_process_options(itv);
	अगर (itv->options.cardtype == -1) अणु
		retval = -ENODEV;
		जाओ err;
	पूर्ण
	अगर (ivtv_init_काष्ठा1(itv)) अणु
		retval = -ENOMEM;
		जाओ err;
	पूर्ण
	retval = cx2341x_handler_init(&itv->cxhdl, 50);
	अगर (retval)
		जाओ err;
	itv->v4l2_dev.ctrl_handler = &itv->cxhdl.hdl;
	itv->cxhdl.ops = &ivtv_cxhdl_ops;
	itv->cxhdl.priv = itv;
	itv->cxhdl.func = ivtv_api_func;

	IVTV_DEBUG_INFO("base addr: 0x%llx\n", (u64)itv->base_addr);

	/* PCI Device Setup */
	retval = ivtv_setup_pci(itv, pdev, pci_id);
	अगर (retval == -EIO)
		जाओ मुक्त_worker;
	अगर (retval == -ENXIO)
		जाओ मुक्त_mem;

	/* map io memory */
	IVTV_DEBUG_INFO("attempting ioremap at 0x%llx len 0x%08x\n",
		   (u64)itv->base_addr + IVTV_ENCODER_OFFSET, IVTV_ENCODER_SIZE);
	itv->enc_mem = ioremap(itv->base_addr + IVTV_ENCODER_OFFSET,
				       IVTV_ENCODER_SIZE);
	अगर (!itv->enc_mem) अणु
		IVTV_ERR("ioremap failed. Can't get a window into CX23415/6 encoder memory\n");
		IVTV_ERR("Each capture card with a CX23415/6 needs 8 MB of vmalloc address space for this window\n");
		IVTV_ERR("Check the output of 'grep Vmalloc /proc/meminfo'\n");
		IVTV_ERR("Use the vmalloc= kernel command line option to set VmallocTotal to a larger value\n");
		retval = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	अगर (itv->has_cx23415) अणु
		IVTV_DEBUG_INFO("attempting ioremap at 0x%llx len 0x%08x\n",
				(u64)itv->base_addr + IVTV_DECODER_OFFSET, IVTV_DECODER_SIZE);
		itv->dec_mem = ioremap(itv->base_addr + IVTV_DECODER_OFFSET,
				IVTV_DECODER_SIZE);
		अगर (!itv->dec_mem) अणु
			IVTV_ERR("ioremap failed. Can't get a window into CX23415 decoder memory\n");
			IVTV_ERR("Each capture card with a CX23415 needs 8 MB of vmalloc address space for this window\n");
			IVTV_ERR("Check the output of 'grep Vmalloc /proc/meminfo'\n");
			IVTV_ERR("Use the vmalloc= kernel command line option to set VmallocTotal to a larger value\n");
			retval = -ENOMEM;
			जाओ मुक्त_mem;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		itv->dec_mem = itv->enc_mem;
	पूर्ण

	/* map रेजिस्टरs memory */
	IVTV_DEBUG_INFO("attempting ioremap at 0x%llx len 0x%08x\n",
		   (u64)itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
	itv->reg_mem =
	    ioremap(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
	अगर (!itv->reg_mem) अणु
		IVTV_ERR("ioremap failed. Can't get a window into CX23415/6 register space\n");
		IVTV_ERR("Each capture card with a CX23415/6 needs 64 kB of vmalloc address space for this window\n");
		IVTV_ERR("Check the output of 'grep Vmalloc /proc/meminfo'\n");
		IVTV_ERR("Use the vmalloc= kernel command line option to set VmallocTotal to a larger value\n");
		retval = -ENOMEM;
		जाओ मुक्त_io;
	पूर्ण

	retval = ivtv_gpio_init(itv);
	अगर (retval)
		जाओ मुक्त_io;

	/* active i2c  */
	IVTV_DEBUG_INFO("activating i2c...\n");
	अगर (init_ivtv_i2c(itv)) अणु
		IVTV_ERR("Could not initialize i2c\n");
		जाओ मुक्त_io;
	पूर्ण

	अगर (itv->card->hw_all & IVTV_HW_TVEEPROM) अणु
		/* Based on the model number the cardtype may be changed.
		   The PCI IDs are not always reliable. */
		ivtv_process_eeprom(itv);
	पूर्ण
	अगर (itv->card->comment)
		IVTV_INFO("%s", itv->card->comment);
	अगर (itv->card->v4l2_capabilities == 0) अणु
		/* card was detected but is not supported */
		retval = -ENODEV;
		जाओ मुक्त_i2c;
	पूर्ण

	अगर (itv->std == 0) अणु
		itv->std = V4L2_STD_NTSC_M;
	पूर्ण

	अगर (itv->options.tuner == -1) अणु
		पूर्णांक i;

		क्रम (i = 0; i < IVTV_CARD_MAX_TUNERS; i++) अणु
			अगर ((itv->std & itv->card->tuners[i].std) == 0)
				जारी;
			itv->options.tuner = itv->card->tuners[i].tuner;
			अवरोध;
		पूर्ण
	पूर्ण
	/* अगर no tuner was found, then pick the first tuner in the card list */
	अगर (itv->options.tuner == -1 && itv->card->tuners[0].std) अणु
		itv->std = itv->card->tuners[0].std;
		अगर (itv->std & V4L2_STD_PAL)
			itv->std = V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
		अन्यथा अगर (itv->std & V4L2_STD_NTSC)
			itv->std = V4L2_STD_NTSC_M;
		अन्यथा अगर (itv->std & V4L2_STD_SECAM)
			itv->std = V4L2_STD_SECAM_L;
		itv->options.tuner = itv->card->tuners[0].tuner;
	पूर्ण
	अगर (itv->options.radio == -1)
		itv->options.radio = (itv->card->radio_input.audio_type != 0);

	/* The card is now fully identअगरied, जारी with card-specअगरic
	   initialization. */
	ivtv_init_काष्ठा2(itv);

	ivtv_load_and_init_modules(itv);

	अगर (itv->std & V4L2_STD_525_60) अणु
		itv->is_60hz = 1;
		itv->is_out_60hz = 1;
	पूर्ण अन्यथा अणु
		itv->is_50hz = 1;
		itv->is_out_50hz = 1;
	पूर्ण

	itv->yuv_info.osd_full_w = 720;
	itv->yuv_info.osd_full_h = itv->is_out_50hz ? 576 : 480;
	itv->yuv_info.v4l2_src_w = itv->yuv_info.osd_full_w;
	itv->yuv_info.v4l2_src_h = itv->yuv_info.osd_full_h;

	cx2341x_handler_set_50hz(&itv->cxhdl, itv->is_50hz);

	itv->stream_buf_size[IVTV_ENC_STREAM_TYPE_MPG] = 0x08000;
	itv->stream_buf_size[IVTV_ENC_STREAM_TYPE_PCM] = 0x01200;
	itv->stream_buf_size[IVTV_DEC_STREAM_TYPE_MPG] = 0x10000;
	itv->stream_buf_size[IVTV_DEC_STREAM_TYPE_YUV] = 0x10000;
	itv->stream_buf_size[IVTV_ENC_STREAM_TYPE_YUV] = 0x08000;

	/* Setup VBI Raw Size. Should be big enough to hold PAL.
	   It is possible to चयन between PAL and NTSC, so we need to
	   take the largest size here. */
	/* 1456 is multiple of 16, real size = 1444 */
	itv->vbi.raw_size = 1456;
	/* We use a buffer size of 1/2 of the total size needed क्रम a
	   frame. This is actually very useful, since we now receive
	   a field at a समय and that makes 'compressing' the raw data
	   करोwn to size by stripping off the SAV codes a lot easier.
	   Note: having two dअगरferent buffer sizes prevents standard
	   चयनing on the fly. We need to find a better solution... */
	vbi_buf_size = itv->vbi.raw_size * (itv->is_60hz ? 24 : 36) / 2;
	itv->stream_buf_size[IVTV_ENC_STREAM_TYPE_VBI] = vbi_buf_size;
	itv->stream_buf_size[IVTV_DEC_STREAM_TYPE_VBI] = माप(काष्ठा v4l2_sliced_vbi_data) * 36;

	अगर (itv->options.radio > 0)
		itv->v4l2_cap |= V4L2_CAP_RADIO;

	अगर (itv->options.tuner > -1) अणु
		काष्ठा tuner_setup setup;

		setup.addr = ADDR_UNSET;
		setup.type = itv->options.tuner;
		setup.mode_mask = T_ANALOG_TV;  /* matches TV tuners */
		अगर (itv->options.radio > 0)
			setup.mode_mask |= T_RADIO;
		setup.tuner_callback = (setup.type == TUNER_XC2028) ?
			ivtv_reset_tuner_gpio : शून्य;
		ivtv_call_all(itv, tuner, s_type_addr, &setup);
		अगर (setup.type == TUNER_XC2028) अणु
			अटल काष्ठा xc2028_ctrl ctrl = अणु
				.fname = XC2028_DEFAULT_FIRMWARE,
				.max_len = 64,
			पूर्ण;
			काष्ठा v4l2_priv_tun_config cfg = अणु
				.tuner = itv->options.tuner,
				.priv = &ctrl,
			पूर्ण;
			ivtv_call_all(itv, tuner, s_config, &cfg);
		पूर्ण
	पूर्ण

	/* The tuner is fixed to the standard. The other inमाला_दो (e.g. S-Video)
	   are not. */
	itv->tuner_std = itv->std;

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		काष्ठा v4l2_ctrl_handler *hdl = itv->v4l2_dev.ctrl_handler;

		itv->ctrl_pts = v4l2_ctrl_new_std(hdl, &ivtv_hdl_out_ops,
				V4L2_CID_MPEG_VIDEO_DEC_PTS, 0, 0, 0, 0);
		itv->ctrl_frame = v4l2_ctrl_new_std(hdl, &ivtv_hdl_out_ops,
				V4L2_CID_MPEG_VIDEO_DEC_FRAME, 0, 0, 0, 0);
		/* Note: V4L2_MPEG_AUDIO_DEC_PLAYBACK_AUTO is not supported,
		   mask that menu item. */
		itv->ctrl_audio_playback =
			v4l2_ctrl_new_std_menu(hdl, &ivtv_hdl_out_ops,
				V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK,
				V4L2_MPEG_AUDIO_DEC_PLAYBACK_SWAPPED_STEREO,
				1 << V4L2_MPEG_AUDIO_DEC_PLAYBACK_AUTO,
				V4L2_MPEG_AUDIO_DEC_PLAYBACK_STEREO);
		itv->ctrl_audio_multilingual_playback =
			v4l2_ctrl_new_std_menu(hdl, &ivtv_hdl_out_ops,
				V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK,
				V4L2_MPEG_AUDIO_DEC_PLAYBACK_SWAPPED_STEREO,
				1 << V4L2_MPEG_AUDIO_DEC_PLAYBACK_AUTO,
				V4L2_MPEG_AUDIO_DEC_PLAYBACK_LEFT);
		अगर (hdl->error) अणु
			retval = hdl->error;
			जाओ मुक्त_i2c;
		पूर्ण
		v4l2_ctrl_cluster(2, &itv->ctrl_pts);
		v4l2_ctrl_cluster(2, &itv->ctrl_audio_playback);
		ivtv_call_all(itv, video, s_std_output, itv->std);
		/* Turn off the output संकेत. The mpeg decoder is not yet
		   active so without this you would get a green image until the
		   mpeg decoder becomes active. */
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 0);
	पूर्ण

	/* clear पूर्णांकerrupt mask, effectively disabling पूर्णांकerrupts */
	ivtv_set_irq_mask(itv, 0xffffffff);

	/* Register IRQ */
	retval = request_irq(itv->pdev->irq, ivtv_irq_handler,
	     IRQF_SHARED, itv->v4l2_dev.name, (व्योम *)itv);
	अगर (retval) अणु
		IVTV_ERR("Failed to register irq %d\n", retval);
		जाओ मुक्त_i2c;
	पूर्ण

	retval = ivtv_streams_setup(itv);
	अगर (retval) अणु
		IVTV_ERR("Error %d setting up streams\n", retval);
		जाओ मुक्त_irq;
	पूर्ण
	retval = ivtv_streams_रेजिस्टर(itv);
	अगर (retval) अणु
		IVTV_ERR("Error %d registering devices\n", retval);
		जाओ मुक्त_streams;
	पूर्ण
	IVTV_INFO("Initialized card: %s\n", itv->card_name);

	/* Load ivtv submodules (ivtv-alsa) */
	request_modules(itv);
	वापस 0;

मुक्त_streams:
	ivtv_streams_cleanup(itv);
मुक्त_irq:
	मुक्त_irq(itv->pdev->irq, (व्योम *)itv);
मुक्त_i2c:
	v4l2_ctrl_handler_मुक्त(&itv->cxhdl.hdl);
	निकास_ivtv_i2c(itv);
मुक्त_io:
	ivtv_iounmap(itv);
मुक्त_mem:
	release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
	release_mem_region(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
	अगर (itv->has_cx23415)
		release_mem_region(itv->base_addr + IVTV_DECODER_OFFSET, IVTV_DECODER_SIZE);
मुक्त_worker:
	kthपढ़ो_stop(itv->irq_worker_task);
err:
	अगर (retval == 0)
		retval = -ENODEV;
	IVTV_ERR("Error %d on initialization\n", retval);

	v4l2_device_unरेजिस्टर(&itv->v4l2_dev);
	kमुक्त(itv);
	वापस retval;
पूर्ण

पूर्णांक ivtv_init_on_first_खोलो(काष्ठा ivtv *itv)
अणु
	काष्ठा v4l2_frequency vf;
	/* Needed to call ioctls later */
	काष्ठा ivtv_खोलो_id fh;
	पूर्णांक fw_retry_count = 3;
	पूर्णांक video_input;

	fh.itv = itv;
	fh.type = IVTV_ENC_STREAM_TYPE_MPG;

	अगर (test_bit(IVTV_F_I_FAILED, &itv->i_flags))
		वापस -ENXIO;

	अगर (test_and_set_bit(IVTV_F_I_INITED, &itv->i_flags))
		वापस 0;

	जबतक (--fw_retry_count > 0) अणु
		/* load firmware */
		अगर (ivtv_firmware_init(itv) == 0)
			अवरोध;
		अगर (fw_retry_count > 1)
			IVTV_WARN("Retry loading firmware\n");
	पूर्ण

	अगर (fw_retry_count == 0) अणु
		set_bit(IVTV_F_I_FAILED, &itv->i_flags);
		वापस -ENXIO;
	पूर्ण

	/* Try and get firmware versions */
	IVTV_DEBUG_INFO("Getting firmware version..\n");
	ivtv_firmware_versions(itv);

	अगर (itv->card->hw_all & IVTV_HW_CX25840)
		v4l2_subdev_call(itv->sd_video, core, load_fw);

	vf.tuner = 0;
	vf.type = V4L2_TUNER_ANALOG_TV;
	vf.frequency = 6400; /* the tuner 'baseline' frequency */

	/* Set initial frequency. For PAL/SECAM broadcasts no
	   'default' channel exists AFAIK. */
	अगर (itv->std == V4L2_STD_NTSC_M_JP) अणु
		vf.frequency = 1460;	/* ch. 1 91250*16/1000 */
	पूर्ण
	अन्यथा अगर (itv->std & V4L2_STD_NTSC_M) अणु
		vf.frequency = 1076;	/* ch. 4 67250*16/1000 */
	पूर्ण

	video_input = itv->active_input;
	itv->active_input++;	/* Force update of input */
	ivtv_s_input(शून्य, &fh, video_input);

	/* Let the VIDIOC_S_STD ioctl करो all the work, keeps the code
	   in one place. */
	itv->std++;		/* Force full standard initialization */
	itv->std_out = itv->std;
	ivtv_s_frequency(शून्य, &fh, &vf);

	अगर (itv->card->v4l2_capabilities & V4L2_CAP_VIDEO_OUTPUT) अणु
		/* Turn on the TV-out: ivtv_init_mpeg_decoder() initializes
		   the mpeg decoder so now the saa7127 receives a proper
		   संकेत. */
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		ivtv_init_mpeg_decoder(itv);
	पूर्ण

	/* On a cx23416 this seems to be able to enable DMA to the chip? */
	अगर (!itv->has_cx23415)
		ग_लिखो_reg_sync(0x03, IVTV_REG_DMACONTROL);

	ivtv_s_std_enc(itv, itv->tuner_std);

	/* Default पूर्णांकerrupts enabled. For the PVR350 this includes the
	   decoder VSYNC पूर्णांकerrupt, which is always on. It is not only used
	   during decoding but also by the OSD.
	   Some old PVR250 cards had a cx23415, so testing क्रम that is too
	   general. Instead test अगर the card has video output capability. */
	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_INIT | IVTV_IRQ_DEC_VSYNC);
		ivtv_set_osd_alpha(itv);
		ivtv_s_std_dec(itv, itv->tuner_std);
	पूर्ण अन्यथा अणु
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_INIT);
	पूर्ण

	/* Setup initial controls */
	cx2341x_handler_setup(&itv->cxhdl);
	वापस 0;
पूर्ण

अटल व्योम ivtv_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	पूर्णांक i;

	IVTV_DEBUG_INFO("Removing card\n");

	flush_request_modules(itv);

	अगर (test_bit(IVTV_F_I_INITED, &itv->i_flags)) अणु
		/* Stop all captures */
		IVTV_DEBUG_INFO("Stopping all streams\n");
		अगर (atomic_पढ़ो(&itv->capturing) > 0)
			ivtv_stop_all_captures(itv);

		/* Stop all decoding */
		IVTV_DEBUG_INFO("Stopping decoding\n");

		/* Turn off the TV-out */
		अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)
			ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 0);
		अगर (atomic_पढ़ो(&itv->decoding) > 0) अणु
			पूर्णांक type;

			अगर (test_bit(IVTV_F_I_DEC_YUV, &itv->i_flags))
				type = IVTV_DEC_STREAM_TYPE_YUV;
			अन्यथा
				type = IVTV_DEC_STREAM_TYPE_MPG;
			ivtv_stop_v4l2_decode_stream(&itv->streams[type],
				V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY, 0);
		पूर्ण
		ivtv_halt_firmware(itv);
	पूर्ण

	/* Interrupts */
	ivtv_set_irq_mask(itv, 0xffffffff);
	del_समयr_sync(&itv->dma_समयr);

	/* Kill irq worker */
	kthपढ़ो_flush_worker(&itv->irq_worker);
	kthपढ़ो_stop(itv->irq_worker_task);

	ivtv_streams_cleanup(itv);
	ivtv_udma_मुक्त(itv);

	v4l2_ctrl_handler_मुक्त(&itv->cxhdl.hdl);

	निकास_ivtv_i2c(itv);

	मुक्त_irq(itv->pdev->irq, (व्योम *)itv);
	ivtv_iounmap(itv);

	release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
	release_mem_region(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
	अगर (itv->has_cx23415)
		release_mem_region(itv->base_addr + IVTV_DECODER_OFFSET, IVTV_DECODER_SIZE);

	pci_disable_device(itv->pdev);
	क्रम (i = 0; i < IVTV_VBI_FRAMES; i++)
		kमुक्त(itv->vbi.sliced_mpeg_data[i]);

	pr_info("Removed %s\n", itv->card_name);

	v4l2_device_unरेजिस्टर(&itv->v4l2_dev);
	kमुक्त(itv);
पूर्ण

/* define a pci_driver क्रम card detection */
अटल काष्ठा pci_driver ivtv_pci_driver = अणु
      .name =     "ivtv",
      .id_table = ivtv_pci_tbl,
      .probe =    ivtv_probe,
      .हटाओ =   ivtv_हटाओ,
पूर्ण;

अटल पूर्णांक __init module_start(व्योम)
अणु
	pr_info("Start initialization, version %s\n", IVTV_VERSION);

	/* Validate parameters */
	अगर (ivtv_first_minor < 0 || ivtv_first_minor >= IVTV_MAX_CARDS) अणु
		pr_err("Exiting, ivtv_first_minor must be between 0 and %d\n",
		     IVTV_MAX_CARDS - 1);
		वापस -1;
	पूर्ण

	अगर (ivtv_debug < 0 || ivtv_debug > 2047) अणु
		ivtv_debug = 0;
		pr_info("Debug value must be >= 0 and <= 2047\n");
	पूर्ण

	अगर (pci_रेजिस्टर_driver(&ivtv_pci_driver)) अणु
		pr_err("Error detecting PCI card\n");
		वापस -ENODEV;
	पूर्ण
	pr_info("End initialization\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास module_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ivtv_pci_driver);
पूर्ण

/* Note: These symbols are exported because they are used by the ivtvfb
   framebuffer module and an infrared module क्रम the IR-blaster. */
EXPORT_SYMBOL(ivtv_set_irq_mask);
EXPORT_SYMBOL(ivtv_api);
EXPORT_SYMBOL(ivtv_vapi);
EXPORT_SYMBOL(ivtv_vapi_result);
EXPORT_SYMBOL(ivtv_clear_irq_mask);
EXPORT_SYMBOL(ivtv_debug);
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
EXPORT_SYMBOL(ivtv_fw_debug);
#पूर्ण_अगर
EXPORT_SYMBOL(ivtv_reset_ir_gpio);
EXPORT_SYMBOL(ivtv_udma_setup);
EXPORT_SYMBOL(ivtv_udma_unmap);
EXPORT_SYMBOL(ivtv_udma_alloc);
EXPORT_SYMBOL(ivtv_udma_prepare);
EXPORT_SYMBOL(ivtv_init_on_first_खोलो);
EXPORT_SYMBOL(ivtv_firmware_check);

module_init(module_start);
module_निकास(module_cleanup);
