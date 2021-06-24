<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran zr36057/zr36067 PCI controller driver, क्रम the
 * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux
 * Media Lअसल LML33/LML33R10.
 *
 * This part handles card-specअगरic data and detection
 *
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <media/v4l2-common.h>
#समावेश <media/i2c/bt819.h>

#समावेश "videocodec.h"
#समावेश "zoran.h"
#समावेश "zoran_card.h"
#समावेश "zoran_device.h"

बाह्य स्थिर काष्ठा zoran_क्रमmat zoran_क्रमmats[];

अटल पूर्णांक card[BUZ_MAX] = अणु [0 ... (BUZ_MAX - 1)] = -1 पूर्ण;
module_param_array(card, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "Card type");

/*
 * The video mem address of the video card. The driver has a little database क्रम some videocards
 * to determine it from there. If your video card is not in there you have either to give it to
 * the driver as a parameter or set in in a VIDIOCSFBUF ioctl
 */

अटल अचिन्हित दीर्घ vidmem;	/* शेष = 0 - Video memory base address */
module_param_hw(vidmem, uदीर्घ, iomem, 0444);
MODULE_PARM_DESC(vidmem, "Default video memory base address");

/* Default input and video norm at startup of the driver. */

अटल अचिन्हित पूर्णांक शेष_input;	/* शेष 0 = Composite, 1 = S-Video */
module_param(शेष_input, uपूर्णांक, 0444);
MODULE_PARM_DESC(शेष_input,
		 "Default input (0=Composite, 1=S-Video, 2=Internal)");

अटल पूर्णांक शेष_mux = 1;	/* 6 Eyes input selection */
module_param(शेष_mux, पूर्णांक, 0644);
MODULE_PARM_DESC(शेष_mux,
		 "Default 6 Eyes mux setting (Input selection)");

अटल पूर्णांक शेष_norm;	/* शेष 0 = PAL, 1 = NTSC 2 = SECAM */
module_param(शेष_norm, पूर्णांक, 0444);
MODULE_PARM_DESC(शेष_norm, "Default norm (0=PAL, 1=NTSC, 2=SECAM)");

/* /dev/videoN, -1 क्रम स्वतःdetect */
अटल पूर्णांक video_nr[BUZ_MAX] = अणु [0 ... (BUZ_MAX - 1)] = -1 पूर्ण;
module_param_array(video_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_nr, "Video device number (-1=Auto)");

पूर्णांक v4l_nbufs = 4;
पूर्णांक v4l_bufsize = 864;		/* Everybody should be able to work with this setting */
module_param(v4l_nbufs, पूर्णांक, 0644);
MODULE_PARM_DESC(v4l_nbufs, "Maximum number of V4L buffers to use");
module_param(v4l_bufsize, पूर्णांक, 0644);
MODULE_PARM_DESC(v4l_bufsize, "Maximum size per V4L buffer (in kB)");

पूर्णांक jpg_nbufs = 32;
पूर्णांक jpg_bufsize = 512;		/* max size क्रम 100% quality full-PAL frame */
module_param(jpg_nbufs, पूर्णांक, 0644);
MODULE_PARM_DESC(jpg_nbufs, "Maximum number of JPG buffers to use");
module_param(jpg_bufsize, पूर्णांक, 0644);
MODULE_PARM_DESC(jpg_bufsize, "Maximum size per JPG buffer (in kB)");

/* 1=Pass through TV संकेत when device is not used */
/* 0=Show color bar when device is not used (LML33: only अगर lml33dpath=1) */
पूर्णांक pass_through;
module_param(pass_through, पूर्णांक, 0644);
MODULE_PARM_DESC(pass_through,
		 "Pass TV signal through to TV-out when idling");

पूर्णांक zr36067_debug = 1;
module_param_named(debug, zr36067_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-5)");

#घोषणा ZORAN_VERSION "0.10.1"

MODULE_DESCRIPTION("Zoran-36057/36067 JPEG codec driver");
MODULE_AUTHOR("Serguei Miridonov");
MODULE_LICENSE("GPL");
MODULE_VERSION(ZORAN_VERSION);

#घोषणा ZR_DEVICE(subven, subdev, data)	अणु \
	.venकरोr = PCI_VENDOR_ID_ZORAN, .device = PCI_DEVICE_ID_ZORAN_36057, \
	.subvenकरोr = (subven), .subdevice = (subdev), .driver_data = (data) पूर्ण

अटल स्थिर काष्ठा pci_device_id zr36067_pci_tbl[] = अणु
	ZR_DEVICE(PCI_VENDOR_ID_MIRO, PCI_DEVICE_ID_MIRO_DC10PLUS, DC10_PLUS),
	ZR_DEVICE(PCI_VENDOR_ID_MIRO, PCI_DEVICE_ID_MIRO_DC30PLUS, DC30_PLUS),
	ZR_DEVICE(PCI_VENDOR_ID_ELECTRONICDESIGNGMBH, PCI_DEVICE_ID_LML_33R10, LML33R10),
	ZR_DEVICE(PCI_VENDOR_ID_IOMEGA, PCI_DEVICE_ID_IOMEGA_BUZ, BUZ),
	ZR_DEVICE(PCI_ANY_ID, PCI_ANY_ID, NUM_CARDS),
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, zr36067_pci_tbl);

अटल अचिन्हित पूर्णांक zoran_num;		/* number of cards found */

/* videocodec bus functions ZR36060 */
अटल u32 zr36060_पढ़ो(काष्ठा videocodec *codec, u16 reg)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;
	__u32 data;

	अगर (post_office_रुको(zr) || post_office_ग_लिखो(zr, 0, 1, reg >> 8) ||
	    post_office_ग_लिखो(zr, 0, 2, reg & 0xff))
		वापस -1;

	data = post_office_पढ़ो(zr, 0, 3) & 0xff;
	वापस data;
पूर्ण

अटल व्योम zr36060_ग_लिखो(काष्ठा videocodec *codec, u16 reg, u32 val)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;

	अगर (post_office_रुको(zr) || post_office_ग_लिखो(zr, 0, 1, reg >> 8) ||
	    post_office_ग_लिखो(zr, 0, 2, reg & 0xff))
		वापस;

	post_office_ग_लिखो(zr, 0, 3, val & 0xff);
पूर्ण

/* videocodec bus functions ZR36050 */
अटल u32 zr36050_पढ़ो(काष्ठा videocodec *codec, u16 reg)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;
	__u32 data;

	अगर (post_office_रुको(zr) || post_office_ग_लिखो(zr, 1, 0, reg >> 2))	// reg. HIGHBYTES
		वापस -1;

	data = post_office_पढ़ो(zr, 0, reg & 0x03) & 0xff;	// reg. LOWBYTES + पढ़ो
	वापस data;
पूर्ण

अटल व्योम zr36050_ग_लिखो(काष्ठा videocodec *codec, u16 reg, u32 val)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;

	अगर (post_office_रुको(zr) || post_office_ग_लिखो(zr, 1, 0, reg >> 2))	// reg. HIGHBYTES
		वापस;

	post_office_ग_लिखो(zr, 0, reg & 0x03, val & 0xff);	// reg. LOWBYTES + wr. data
पूर्ण

/* videocodec bus functions ZR36016 */
अटल u32 zr36016_पढ़ो(काष्ठा videocodec *codec, u16 reg)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;
	__u32 data;

	अगर (post_office_रुको(zr))
		वापस -1;

	data = post_office_पढ़ो(zr, 2, reg & 0x03) & 0xff;	// पढ़ो
	वापस data;
पूर्ण

/* hack क्रम in zoran_device.c */
व्योम zr36016_ग_लिखो(काष्ठा videocodec *codec, u16 reg, u32 val)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)codec->master_data->data;

	अगर (post_office_रुको(zr))
		वापस;

	post_office_ग_लिखो(zr, 2, reg & 0x03, val & 0x0ff);	// wr. data
पूर्ण

/*
 * Board specअगरic inक्रमmation
 */

अटल व्योम dc10_init(काष्ठा zoran *zr)
अणु
	pci_dbg(zr->pci_dev, "%s\n", __func__);

	/* Pixel घड़ी selection */
	GPIO(zr, 4, 0);
	GPIO(zr, 5, 1);
	/* Enable the video bus sync संकेतs */
	GPIO(zr, 7, 0);
पूर्ण

अटल व्योम dc10plus_init(काष्ठा zoran *zr)
अणु
	pci_dbg(zr->pci_dev, "%s\n", __func__);
पूर्ण

अटल व्योम buz_init(काष्ठा zoran *zr)
अणु
	pci_dbg(zr->pci_dev, "%s\n", __func__);

	/* some stuff from Iomega */
	pci_ग_लिखो_config_dword(zr->pci_dev, 0xfc, 0x90680f15);
	pci_ग_लिखो_config_dword(zr->pci_dev, 0x0c, 0x00012020);
	pci_ग_लिखो_config_dword(zr->pci_dev, 0xe8, 0xc0200000);
पूर्ण

अटल व्योम lml33_init(काष्ठा zoran *zr)
अणु
	pci_dbg(zr->pci_dev, "%s\n", __func__);

	GPIO(zr, 2, 1);		// Set Composite input/output
पूर्ण

अटल व्योम avs6eyes_init(काष्ठा zoran *zr)
अणु
	// AverMedia 6-Eyes original driver by Christer Weinigel

	// Lअगरted straight from Christer's old driver and
	// modअगरied slightly by Martin Samuelsson.

	पूर्णांक mux = शेष_mux; /* 1 = BT866, 7 = VID1 */

	GPIO(zr, 4, 1); /* Bt866 SLEEP on */
	udelay(2);

	GPIO(zr, 0, 1); /* ZR36060 /RESET on */
	GPIO(zr, 1, 0); /* ZR36060 /SLEEP on */
	GPIO(zr, 2, mux & 1);   /* MUX S0 */
	GPIO(zr, 3, 0); /* /FRAME on */
	GPIO(zr, 4, 0); /* Bt866 SLEEP off */
	GPIO(zr, 5, mux & 2);   /* MUX S1 */
	GPIO(zr, 6, 0); /* ? */
	GPIO(zr, 7, mux & 4);   /* MUX S2 */
पूर्ण

अटल स्थिर अक्षर *codecid_to_modulename(u16 codecid)
अणु
	स्थिर अक्षर *name = शून्य;

	चयन (codecid) अणु
	हाल CODEC_TYPE_ZR36060:
		name = "zr36060";
		अवरोध;
	हाल CODEC_TYPE_ZR36050:
		name = "zr36050";
		अवरोध;
	हाल CODEC_TYPE_ZR36016:
		name = "zr36016";
		अवरोध;
	पूर्ण

	वापस name;
पूर्ण

// काष्ठा tvnorm अणु
//      u16 wt, wa, h_start, h_sync_start, ht, ha, v_start;
// पूर्ण;

अटल स्थिर काष्ठा tvnorm f50sqpixel = अणु 944, 768, 83, 880, 625, 576, 16 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60sqpixel = अणु 780, 640, 51, 716, 525, 480, 12 पूर्ण;
अटल स्थिर काष्ठा tvnorm f50ccir601 = अणु 864, 720, 75, 804, 625, 576, 18 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60ccir601 = अणु 858, 720, 57, 788, 525, 480, 16 पूर्ण;

अटल स्थिर काष्ठा tvnorm f50ccir601_lml33 = अणु 864, 720, 75 + 34, 804, 625, 576, 18 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60ccir601_lml33 = अणु 858, 720, 57 + 34, 788, 525, 480, 16 पूर्ण;

/* The DC10 (57/16/50) uses VActive as HSync, so h_start must be 0 */
अटल स्थिर काष्ठा tvnorm f50sqpixel_dc10 = अणु 944, 768, 0, 880, 625, 576, 0 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60sqpixel_dc10 = अणु 780, 640, 0, 716, 525, 480, 12 पूर्ण;

/*
 * FIXME: I cannot swap U and V in saa7114, so i करो one pixel left shअगरt in zoran (75 -> 74)
 * (Maxim Yevtyushkin <max@linuxmediaद_असल.com>)
 */
अटल स्थिर काष्ठा tvnorm f50ccir601_lm33r10 = अणु 864, 720, 74 + 54, 804, 625, 576, 18 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60ccir601_lm33r10 = अणु 858, 720, 56 + 54, 788, 525, 480, 16 पूर्ण;

/*
 * FIXME: The ks0127 seem incapable of swapping U and V, too, which is why I copy Maxim's left
 * shअगरt hack क्रम the 6 Eyes.
 *
 * Christer's driver used the unshअगरted norms, though...
 * /Sam
 */
अटल स्थिर काष्ठा tvnorm f50ccir601_avs6eyes = अणु 864, 720, 74, 804, 625, 576, 18 पूर्ण;
अटल स्थिर काष्ठा tvnorm f60ccir601_avs6eyes = अणु 858, 720, 56, 788, 525, 480, 16 पूर्ण;

अटल स्थिर अचिन्हित लघु vpx3220_addrs[] = अणु 0x43, 0x47, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु saa7110_addrs[] = अणु 0x4e, 0x4f, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु saa7111_addrs[] = अणु 0x25, 0x24, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु saa7114_addrs[] = अणु 0x21, 0x20, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु adv717x_addrs[] = अणु 0x6a, 0x6b, 0x2a, 0x2b, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु ks0127_addrs[] = अणु 0x6c, 0x6d, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु saa7185_addrs[] = अणु 0x44, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु bt819_addrs[] = अणु 0x45, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु bt856_addrs[] = अणु 0x44, I2C_CLIENT_END पूर्ण;
अटल स्थिर अचिन्हित लघु bt866_addrs[] = अणु 0x44, I2C_CLIENT_END पूर्ण;

अटल काष्ठा card_info zoran_cards[NUM_CARDS] = अणु
	अणु
		.type = DC10_OLD,
		.name = "DC10(old)",
		.i2c_decoder = "vpx3220a",
		.addrs_decoder = vpx3220_addrs,
		.video_codec = CODEC_TYPE_ZR36050,
		.video_vfe = CODEC_TYPE_ZR36016,

		.inमाला_दो = 3,
		.input = अणु
			अणु 1, "Composite" पूर्ण,
			अणु 2, "S-Video" पूर्ण,
			अणु 0, "Internal/comp" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
			&f50sqpixel_dc10,
			&f60sqpixel_dc10,
			&f50sqpixel_dc10
		पूर्ण,
		.jpeg_पूर्णांक = 0,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ1,
		.gpio = अणु 2, 1, -1, 3, 7, 0, 4, 5 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 1, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु -1, 0 पूर्ण,
		.vfe_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	पूर्ण, अणु
		.type = DC10_NEW,
		.name = "DC10(new)",
		.i2c_decoder = "saa7110",
		.addrs_decoder = saa7110_addrs,
		.i2c_encoder = "adv7175",
		.addrs_encoder = adv717x_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 3,
		.input = अणु
				अणु 0, "Composite" पूर्ण,
				अणु 7, "S-Video" पूर्ण,
				अणु 5, "Internal/comp" पूर्ण
			पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
				&f50sqpixel,
				&f60sqpixel,
				&f50sqpixelपूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ0,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ1,
		.gpio = अणु 3, 0, 6, 1, 2, -1, 4, 5 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु -1, 1पूर्ण,
		.vfe_pol = अणु 1, 1, 1, 1, 0, 0, 0, 0 पूर्ण,
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10plus_init,
	पूर्ण, अणु
		.type = DC10_PLUS,
		.name = "DC10_PLUS",
		.i2c_decoder = "saa7110",
		.addrs_decoder = saa7110_addrs,
		.i2c_encoder = "adv7175",
		.addrs_encoder = adv717x_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 3,
		.input = अणु
			अणु 0, "Composite" पूर्ण,
			अणु 7, "S-Video" पूर्ण,
			अणु 5, "Internal/comp" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
			&f50sqpixel,
			&f60sqpixel,
			&f50sqpixel
		पूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ0,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ1,
		.gpio = अणु 3, 0, 6, 1, 2, -1, 4, 5 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु -1, 1 पूर्ण,
		.vfe_pol = अणु 1, 1, 1, 1, 0, 0, 0, 0 पूर्ण,
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10plus_init,
	पूर्ण, अणु
		.type = DC30,
		.name = "DC30",
		.i2c_decoder = "vpx3220a",
		.addrs_decoder = vpx3220_addrs,
		.i2c_encoder = "adv7175",
		.addrs_encoder = adv717x_addrs,
		.video_codec = CODEC_TYPE_ZR36050,
		.video_vfe = CODEC_TYPE_ZR36016,

		.inमाला_दो = 3,
		.input = अणु
			अणु 1, "Composite" पूर्ण,
			अणु 2, "S-Video" पूर्ण,
			अणु 0, "Internal/comp" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
			&f50sqpixel_dc10,
			&f60sqpixel_dc10,
			&f50sqpixel_dc10
		पूर्ण,
		.jpeg_पूर्णांक = 0,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ1,
		.gpio = अणु 2, 1, -1, 3, 7, 0, 4, 5 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 1, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु -1, 0 पूर्ण,
		.vfe_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	पूर्ण, अणु
		.type = DC30_PLUS,
		.name = "DC30_PLUS",
		.i2c_decoder = "vpx3220a",
		.addrs_decoder = vpx3220_addrs,
		.i2c_encoder = "adv7175",
		.addrs_encoder = adv717x_addrs,
		.video_codec = CODEC_TYPE_ZR36050,
		.video_vfe = CODEC_TYPE_ZR36016,

		.inमाला_दो = 3,
		.input = अणु
			अणु 1, "Composite" पूर्ण,
			अणु 2, "S-Video" पूर्ण,
			अणु 0, "Internal/comp" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
			&f50sqpixel_dc10,
			&f60sqpixel_dc10,
			&f50sqpixel_dc10
		पूर्ण,
		.jpeg_पूर्णांक = 0,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ1,
		.gpio = अणु 2, 1, -1, 3, 7, 0, 4, 5 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 1, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु -1, 0 पूर्ण,
		.vfe_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	पूर्ण, अणु
		.type = LML33,
		.name = "LML33",
		.i2c_decoder = "bt819a",
		.addrs_decoder = bt819_addrs,
		.i2c_encoder = "bt856",
		.addrs_encoder = bt856_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 2,
		.input = अणु
			अणु 0, "Composite" पूर्ण,
			अणु 7, "S-Video" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL,
		.tvn = अणु
			&f50ccir601_lml33,
			&f60ccir601_lml33,
			शून्य
		पूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ1,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ0,
		.gpio = अणु 1, -1, 3, 5, 7, -1, -1, -1 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 0, 1, 0, 0, 0 पूर्ण,
		.gpcs = अणु 3, 1 पूर्ण,
		.vfe_pol = अणु 1, 1, 0, 0, 0, 1, 0, 0 पूर्ण,
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &lml33_init,
	पूर्ण, अणु
		.type = LML33R10,
		.name = "LML33R10",
		.i2c_decoder = "saa7114",
		.addrs_decoder = saa7114_addrs,
		.i2c_encoder = "adv7170",
		.addrs_encoder = adv717x_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 2,
		.input = अणु
			अणु 0, "Composite" पूर्ण,
			अणु 7, "S-Video" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL,
		.tvn = अणु
			&f50ccir601_lm33r10,
			&f60ccir601_lm33r10,
			शून्य
		पूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ1,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ0,
		.gpio = अणु 1, -1, 3, 5, 7, -1, -1, -1 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 0, 1, 0, 0, 0 पूर्ण,
		.gpcs = अणु 3, 1 पूर्ण,
		.vfe_pol = अणु 1, 1, 0, 0, 0, 1, 0, 0 पूर्ण,
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &lml33_init,
	पूर्ण, अणु
		.type = BUZ,
		.name = "Buz",
		.i2c_decoder = "saa7111",
		.addrs_decoder = saa7111_addrs,
		.i2c_encoder = "saa7185",
		.addrs_encoder = saa7185_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 2,
		.input = अणु
			अणु 3, "Composite" पूर्ण,
			अणु 7, "S-Video" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
		.tvn = अणु
			&f50ccir601,
			&f60ccir601,
			&f50ccir601
		पूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ1,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ0,
		.gpio = अणु 1, -1, 3, -1, -1, -1, -1, -1 पूर्ण,
		.gpio_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.gpcs = अणु 3, 1 पूर्ण,
		.vfe_pol = अणु 1, 1, 0, 0, 0, 1, 0, 0 पूर्ण,
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &buz_init,
	पूर्ण, अणु
		.type = AVS6EYES,
		.name = "6-Eyes",
/* AverMedia chose not to bअक्रम the 6-Eyes. Thus it can't be स्वतःdetected, and requires card=x. */
		.i2c_decoder = "ks0127",
		.addrs_decoder = ks0127_addrs,
		.i2c_encoder = "bt866",
		.addrs_encoder = bt866_addrs,
		.video_codec = CODEC_TYPE_ZR36060,

		.inमाला_दो = 10,
		.input = अणु
			अणु 0, "Composite 1" पूर्ण,
			अणु 1, "Composite 2" पूर्ण,
			अणु 2, "Composite 3" पूर्ण,
			अणु 4, "Composite 4" पूर्ण,
			अणु 5, "Composite 5" पूर्ण,
			अणु 6, "Composite 6" पूर्ण,
			अणु 8, "S-Video 1" पूर्ण,
			अणु 9, "S-Video 2" पूर्ण,
			अणु10, "S-Video 3" पूर्ण,
			अणु15, "YCbCr" पूर्ण
		पूर्ण,
		.norms = V4L2_STD_NTSC | V4L2_STD_PAL,
		.tvn = अणु
			&f50ccir601_avs6eyes,
			&f60ccir601_avs6eyes,
			शून्य
		पूर्ण,
		.jpeg_पूर्णांक = ZR36057_ISR_GIRQ1,
		.vsync_पूर्णांक = ZR36057_ISR_GIRQ0,
		.gpio = अणु 1, 0, 3, -1, -1, -1, -1, -1 पूर्ण,// Validity unknown /Sam
		.gpio_pol = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण, // Validity unknown /Sam
		.gpcs = अणु 3, 1 पूर्ण,			// Validity unknown /Sam
		.vfe_pol = अणु 1, 0, 0, 0, 0, 1, 0, 0 पूर्ण,  // Validity unknown /Sam
		.gws_not_connected = 1,
		.input_mux = 1,
		.init = &avs6eyes_init,
	पूर्ण

पूर्ण;

/*
 * I2C functions
 */
/* software I2C functions */
अटल पूर्णांक zoran_i2c_माला_लोda(व्योम *data)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)data;

	वापस (btपढ़ो(ZR36057_I2CBR) >> 1) & 1;
पूर्ण

अटल पूर्णांक zoran_i2c_माला_लोcl(व्योम *data)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)data;

	वापस btपढ़ो(ZR36057_I2CBR) & 1;
पूर्ण

अटल व्योम zoran_i2c_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)data;

	अगर (state)
		zr->i2cbr |= 2;
	अन्यथा
		zr->i2cbr &= ~2;
	btग_लिखो(zr->i2cbr, ZR36057_I2CBR);
पूर्ण

अटल व्योम zoran_i2c_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा zoran *zr = (काष्ठा zoran *)data;

	अगर (state)
		zr->i2cbr |= 1;
	अन्यथा
		zr->i2cbr &= ~1;
	btग_लिखो(zr->i2cbr, ZR36057_I2CBR);
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data zoran_i2c_bit_data_ढाँचा = अणु
	.setsda = zoran_i2c_setsda,
	.setscl = zoran_i2c_setscl,
	.माला_लोda = zoran_i2c_माला_लोda,
	.माला_लोcl = zoran_i2c_माला_लोcl,
	.udelay = 10,
	.समयout = 100,
पूर्ण;

अटल पूर्णांक zoran_रेजिस्टर_i2c(काष्ठा zoran *zr)
अणु
	zr->i2c_algo = zoran_i2c_bit_data_ढाँचा;
	zr->i2c_algo.data = zr;
	strscpy(zr->i2c_adapter.name, ZR_DEVNAME(zr),
		माप(zr->i2c_adapter.name));
	i2c_set_adapdata(&zr->i2c_adapter, &zr->v4l2_dev);
	zr->i2c_adapter.algo_data = &zr->i2c_algo;
	zr->i2c_adapter.dev.parent = &zr->pci_dev->dev;
	वापस i2c_bit_add_bus(&zr->i2c_adapter);
पूर्ण

अटल व्योम zoran_unरेजिस्टर_i2c(काष्ठा zoran *zr)
अणु
	i2c_del_adapter(&zr->i2c_adapter);
पूर्ण

/* Check a zoran_params काष्ठा क्रम correctness, insert शेष params */
पूर्णांक zoran_check_jpg_settings(काष्ठा zoran *zr,
			     काष्ठा zoran_jpg_settings *settings, पूर्णांक try)
अणु
	पूर्णांक err = 0, err0 = 0;

	pci_dbg(zr->pci_dev, "%s - dec: %d, Hdcm: %d, Vdcm: %d, Tdcm: %d\n",
		__func__, settings->decimation, settings->hor_dcm,
		settings->ver_dcm, settings->पंचांगp_dcm);
	pci_dbg(zr->pci_dev, "%s - x: %d, y: %d, w: %d, y: %d\n", __func__,
		settings->img_x, settings->img_y,
		settings->img_width, settings->img_height);
	/* Check decimation, set शेष values क्रम decimation = 1, 2, 4 */
	चयन (settings->decimation) अणु
	हाल 1:

		settings->hor_dcm = 1;
		settings->ver_dcm = 1;
		settings->पंचांगp_dcm = 1;
		settings->field_per_buff = 2;
		settings->img_x = 0;
		settings->img_y = 0;
		settings->img_width = BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		अवरोध;
	हाल 2:

		settings->hor_dcm = 2;
		settings->ver_dcm = 1;
		settings->पंचांगp_dcm = 2;
		settings->field_per_buff = 1;
		settings->img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings->img_y = 0;
		settings->img_width =
		    (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		अवरोध;
	हाल 4:

		अगर (zr->card.type == DC10_NEW) अणु
			pci_dbg(zr->pci_dev, "%s - HDec by 4 is not supported on the DC10\n", __func__);
			err0++;
			अवरोध;
		पूर्ण

		settings->hor_dcm = 4;
		settings->ver_dcm = 2;
		settings->पंचांगp_dcm = 2;
		settings->field_per_buff = 1;
		settings->img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings->img_y = 0;
		settings->img_width =
		    (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		अवरोध;
	हाल 0:

		/* We have to check the data the user has set */

		अगर (settings->hor_dcm != 1 && settings->hor_dcm != 2 &&
		    (zr->card.type == DC10_NEW || settings->hor_dcm != 4)) अणु
			settings->hor_dcm = clamp(settings->hor_dcm, 1, 2);
			err0++;
		पूर्ण
		अगर (settings->ver_dcm != 1 && settings->ver_dcm != 2) अणु
			settings->ver_dcm = clamp(settings->ver_dcm, 1, 2);
			err0++;
		पूर्ण
		अगर (settings->पंचांगp_dcm != 1 && settings->पंचांगp_dcm != 2) अणु
			settings->पंचांगp_dcm = clamp(settings->पंचांगp_dcm, 1, 2);
			err0++;
		पूर्ण
		अगर (settings->field_per_buff != 1 &&
		    settings->field_per_buff != 2) अणु
			settings->field_per_buff = clamp(settings->field_per_buff, 1, 2);
			err0++;
		पूर्ण
		अगर (settings->img_x < 0) अणु
			settings->img_x = 0;
			err0++;
		पूर्ण
		अगर (settings->img_y < 0) अणु
			settings->img_y = 0;
			err0++;
		पूर्ण
		अगर (settings->img_width < 0 || settings->img_width > BUZ_MAX_WIDTH) अणु
			settings->img_width = clamp(settings->img_width, 0, (पूर्णांक)BUZ_MAX_WIDTH);
			err0++;
		पूर्ण
		अगर (settings->img_height < 0 || settings->img_height > BUZ_MAX_HEIGHT / 2) अणु
			settings->img_height = clamp(settings->img_height, 0, BUZ_MAX_HEIGHT / 2);
			err0++;
		पूर्ण
		अगर (settings->img_x + settings->img_width > BUZ_MAX_WIDTH) अणु
			settings->img_x = BUZ_MAX_WIDTH - settings->img_width;
			err0++;
		पूर्ण
		अगर (settings->img_y + settings->img_height > BUZ_MAX_HEIGHT / 2) अणु
			settings->img_y = BUZ_MAX_HEIGHT / 2 - settings->img_height;
			err0++;
		पूर्ण
		अगर (settings->img_width % (16 * settings->hor_dcm) != 0) अणु
			settings->img_width -= settings->img_width % (16 * settings->hor_dcm);
			अगर (settings->img_width == 0)
				settings->img_width = 16 * settings->hor_dcm;
			err0++;
		पूर्ण
		अगर (settings->img_height % (8 * settings->ver_dcm) != 0) अणु
			settings->img_height -= settings->img_height % (8 * settings->ver_dcm);
			अगर (settings->img_height == 0)
				settings->img_height = 8 * settings->ver_dcm;
			err0++;
		पूर्ण

		अगर (!try && err0) अणु
			pci_err(zr->pci_dev, "%s - error in params for decimation = 0\n", __func__);
			err++;
		पूर्ण
		अवरोध;
	शेष:
		pci_err(zr->pci_dev, "%s - decimation = %d, must be 0, 1, 2 or 4\n",
			__func__, settings->decimation);
		err++;
		अवरोध;
	पूर्ण

	अगर (settings->jpg_comp.quality > 100)
		settings->jpg_comp.quality = 100;
	अगर (settings->jpg_comp.quality < 5)
		settings->jpg_comp.quality = 5;
	अगर (settings->jpg_comp.APPn < 0)
		settings->jpg_comp.APPn = 0;
	अगर (settings->jpg_comp.APPn > 15)
		settings->jpg_comp.APPn = 15;
	अगर (settings->jpg_comp.APP_len < 0)
		settings->jpg_comp.APP_len = 0;
	अगर (settings->jpg_comp.APP_len > 60)
		settings->jpg_comp.APP_len = 60;
	अगर (settings->jpg_comp.COM_len < 0)
		settings->jpg_comp.COM_len = 0;
	अगर (settings->jpg_comp.COM_len > 60)
		settings->jpg_comp.COM_len = 60;
	अगर (err)
		वापस -EINVAL;
	वापस 0;
पूर्ण

व्योम zoran_खोलो_init_params(काष्ठा zoran *zr)
अणु
	पूर्णांक i;

	zr->v4l_settings.width = 192;
	zr->v4l_settings.height = 144;
	zr->v4l_settings.क्रमmat = &zoran_क्रमmats[7];	/* YUY2 - YUV-4:2:2 packed */
	zr->v4l_settings.bytesperline = zr->v4l_settings.width *
		((zr->v4l_settings.क्रमmat->depth + 7) / 8);

	/* Set necessary params and call zoran_check_jpg_settings to set the शेषs */
	zr->jpg_settings.decimation = 1;
	zr->jpg_settings.jpg_comp.quality = 50;	/* शेष compression factor 8 */
	अगर (zr->card.type != BUZ)
		zr->jpg_settings.odd_even = 1;
	अन्यथा
		zr->jpg_settings.odd_even = 0;
	zr->jpg_settings.jpg_comp.APPn = 0;
	zr->jpg_settings.jpg_comp.APP_len = 0;	/* No APPn marker */
	स_रखो(zr->jpg_settings.jpg_comp.APP_data, 0,
	       माप(zr->jpg_settings.jpg_comp.APP_data));
	zr->jpg_settings.jpg_comp.COM_len = 0;	/* No COM marker */
	स_रखो(zr->jpg_settings.jpg_comp.COM_data, 0,
	       माप(zr->jpg_settings.jpg_comp.COM_data));
	zr->jpg_settings.jpg_comp.jpeg_markers =
	    V4L2_JPEG_MARKER_DHT | V4L2_JPEG_MARKER_DQT;
	i = zoran_check_jpg_settings(zr, &zr->jpg_settings, 0);
	अगर (i)
		pci_err(zr->pci_dev, "%s internal error\n", __func__);

	zr->buffer_size = zr->v4l_settings.bytesperline * zr->v4l_settings.height;

	clear_पूर्णांकerrupt_counters(zr);
पूर्ण

अटल पूर्णांक zr36057_init(काष्ठा zoran *zr)
अणु
	पूर्णांक j, err;

	pci_info(zr->pci_dev, "initializing card[%d]\n", zr->id);

	/* Aव्योम nonsense settings from user क्रम शेष input/norm */
	अगर (शेष_norm < 0 || शेष_norm > 2)
		शेष_norm = 0;
	अगर (शेष_norm == 0) अणु
		zr->norm = V4L2_STD_PAL;
		zr->timing = zr->card.tvn[ZR_NORM_PAL];
	पूर्ण अन्यथा अगर (शेष_norm == 1) अणु
		zr->norm = V4L2_STD_NTSC;
		zr->timing = zr->card.tvn[ZR_NORM_NTSC];
	पूर्ण अन्यथा अणु
		zr->norm = V4L2_STD_SECAM;
		zr->timing = zr->card.tvn[ZR_NORM_SECAM];
	पूर्ण
	अगर (!zr->timing) अणु
		pci_warn(zr->pci_dev, "%s - default TV standard not supported by hardware. PAL will be used.\n", __func__);
		zr->norm = V4L2_STD_PAL;
		zr->timing = zr->card.tvn[ZR_NORM_PAL];
	पूर्ण

	अगर (शेष_input > zr->card.inमाला_दो - 1) अणु
		pci_warn(zr->pci_dev, "default_input value %d out of range (0-%d)\n",
			 शेष_input, zr->card.inमाला_दो - 1);
		शेष_input = 0;
	पूर्ण
	zr->input = शेष_input;

	/* शेष setup (will be repeated at every खोलो) */
	zoran_खोलो_init_params(zr);

	/* allocate memory *beक्रमe* करोing anything to the hardware in हाल allocation fails */
	zr->video_dev = video_device_alloc();
	अगर (!zr->video_dev) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	zr->stat_com = dma_alloc_coherent(&zr->pci_dev->dev,
					  BUZ_NUM_STAT_COM * माप(u32),
					  &zr->p_sc, GFP_KERNEL);
	अगर (!zr->stat_com) अणु
		err = -ENOMEM;
		जाओ निकास_video;
	पूर्ण
	क्रम (j = 0; j < BUZ_NUM_STAT_COM; j++)
		zr->stat_com[j] = cpu_to_le32(1); /* mark as unavailable to zr36057 */

	zr->stat_comb = dma_alloc_coherent(&zr->pci_dev->dev,
					   BUZ_NUM_STAT_COM * माप(u32) * 2,
					   &zr->p_scb, GFP_KERNEL);
	अगर (!zr->stat_comb) अणु
		err = -ENOMEM;
		जाओ निकास_statcom;
	पूर्ण

	/* Now add the ढाँचा and रेजिस्टर the device unit. */
	*zr->video_dev = zoran_ढाँचा;
	zr->video_dev->v4l2_dev = &zr->v4l2_dev;
	zr->video_dev->lock = &zr->lock;
	zr->video_dev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;

	strscpy(zr->video_dev->name, ZR_DEVNAME(zr), माप(zr->video_dev->name));
	/*
	 * It's not a mem2mem device, but you can both capture and output from one and the same
	 * device. This should really be split up पूर्णांकo two device nodes, but that's a job क्रम
	 * another day.
	 */
	zr->video_dev->vfl_dir = VFL_सूची_M2M;

	zoran_queue_init(zr, &zr->vq);

	err = video_रेजिस्टर_device(zr->video_dev, VFL_TYPE_VIDEO, video_nr[zr->id]);
	अगर (err < 0)
		जाओ निकास_statcomb;
	video_set_drvdata(zr->video_dev, zr);

	zoran_init_hardware(zr);
	अगर (!pass_through) अणु
		decoder_call(zr, video, s_stream, 0);
		encoder_call(zr, video, s_routing, 2, 0, 0);
	पूर्ण

	zr->initialized = 1;
	वापस 0;

निकास_statcomb:
	dma_मुक्त_coherent(&zr->pci_dev->dev, BUZ_NUM_STAT_COM * माप(u32) * 2, zr->stat_comb, zr->p_scb);
निकास_statcom:
	dma_मुक्त_coherent(&zr->pci_dev->dev, BUZ_NUM_STAT_COM * माप(u32), zr->stat_com, zr->p_sc);
निकास_video:
	kमुक्त(zr->video_dev);
निकास:
	वापस err;
पूर्ण

अटल व्योम zoran_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(&pdev->dev);
	काष्ठा zoran *zr = to_zoran(v4l2_dev);

	अगर (!zr->initialized)
		जाओ निकास_मुक्त;

	zoran_queue_निकास(zr);

	/* unरेजिस्टर videocodec bus */
	अगर (zr->codec)
		videocodec_detach(zr->codec);
	अगर (zr->vfe)
		videocodec_detach(zr->vfe);

	/* unरेजिस्टर i2c bus */
	zoran_unरेजिस्टर_i2c(zr);
	/* disable PCI bus-mastering */
	zoran_set_pci_master(zr, 0);
	/* put chip पूर्णांकo reset */
	btग_लिखो(0, ZR36057_SPGPPCR);
	pci_मुक्त_irq(zr->pci_dev, 0, zr);
	/* unmap and मुक्त memory */
	dma_मुक्त_coherent(&zr->pci_dev->dev, BUZ_NUM_STAT_COM * माप(u32), zr->stat_com, zr->p_sc);
	dma_मुक्त_coherent(&zr->pci_dev->dev, BUZ_NUM_STAT_COM * माप(u32) * 2, zr->stat_comb, zr->p_scb);
	pci_release_regions(pdev);
	pci_disable_device(zr->pci_dev);
	video_unरेजिस्टर_device(zr->video_dev);
निकास_मुक्त:
	v4l2_ctrl_handler_मुक्त(&zr->hdl);
	v4l2_device_unरेजिस्टर(&zr->v4l2_dev);
पूर्ण

व्योम zoran_vdev_release(काष्ठा video_device *vdev)
अणु
	kमुक्त(vdev);
पूर्ण

अटल काष्ठा videocodec_master *zoran_setup_videocodec(काष्ठा zoran *zr,
							पूर्णांक type)
अणु
	काष्ठा videocodec_master *m = शून्य;

	m = devm_kदो_स्मृति(&zr->pci_dev->dev, माप(*m), GFP_KERNEL);
	अगर (!m)
		वापस m;

	/*
	 * magic and type are unused क्रम master काष्ठा. Makes sense only at codec काष्ठाs.
	 * In the past, .type were initialized to the old V4L1 .hardware value,
	 * as VID_HARDWARE_ZR36067
	 */
	m->magic = 0L;
	m->type = 0;

	m->flags = CODEC_FLAG_ENCODER | CODEC_FLAG_DECODER;
	strscpy(m->name, ZR_DEVNAME(zr), माप(m->name));
	m->data = zr;

	चयन (type) अणु
	हाल CODEC_TYPE_ZR36060:
		m->पढ़ोreg = zr36060_पढ़ो;
		m->ग_लिखोreg = zr36060_ग_लिखो;
		m->flags |= CODEC_FLAG_JPEG | CODEC_FLAG_VFE;
		अवरोध;
	हाल CODEC_TYPE_ZR36050:
		m->पढ़ोreg = zr36050_पढ़ो;
		m->ग_लिखोreg = zr36050_ग_लिखो;
		m->flags |= CODEC_FLAG_JPEG;
		अवरोध;
	हाल CODEC_TYPE_ZR36016:
		m->पढ़ोreg = zr36016_पढ़ो;
		m->ग_लिखोreg = zr36016_ग_लिखो;
		m->flags |= CODEC_FLAG_VFE;
		अवरोध;
	पूर्ण

	वापस m;
पूर्ण

अटल व्योम zoran_subdev_notअगरy(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा zoran *zr = to_zoran(sd->v4l2_dev);

	/*
	 * Bt819 needs to reset its FIFO buffer using #FRST pin and
	 * LML33 card uses GPIO(7) क्रम that.
	 */
	अगर (cmd == BT819_FIFO_RESET_LOW)
		GPIO(zr, 7, 0);
	अन्यथा अगर (cmd == BT819_FIFO_RESET_HIGH)
		GPIO(zr, 7, 1);
पूर्ण

अटल पूर्णांक zoran_video_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा zoran *zr = container_of(ctrl->handler, काष्ठा zoran, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		zr->jpg_settings.jpg_comp.quality = ctrl->val;
		वापस zoran_check_jpg_settings(zr, &zr->jpg_settings, 0);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops zoran_video_ctrl_ops = अणु
	.s_ctrl = zoran_video_set_ctrl,
पूर्ण;

/*
 *   Scan क्रम a Buz card (actually क्रम the PCI controller ZR36057),
 *   request the irq and map the io memory
 */
अटल पूर्णांक zoran_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित अक्षर latency, need_latency;
	काष्ठा zoran *zr;
	पूर्णांक result;
	काष्ठा videocodec_master *master_vfe = शून्य;
	काष्ठा videocodec_master *master_codec = शून्य;
	पूर्णांक card_num;
	स्थिर अक्षर *codec_name, *vfe_name;
	अचिन्हित पूर्णांक nr;
	पूर्णांक err;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस -ENODEV;
	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	nr = zoran_num++;
	अगर (nr >= BUZ_MAX) अणु
		pci_err(pdev, "driver limited to %d card(s) maximum\n", BUZ_MAX);
		वापस -ENOENT;
	पूर्ण

	zr = devm_kzalloc(&pdev->dev, माप(*zr), GFP_KERNEL);
	अगर (!zr)
		वापस -ENOMEM;

	zr->v4l2_dev.notअगरy = zoran_subdev_notअगरy;
	अगर (v4l2_device_रेजिस्टर(&pdev->dev, &zr->v4l2_dev))
		जाओ zr_मुक्त_mem;
	zr->pci_dev = pdev;
	zr->id = nr;
	snम_लिखो(ZR_DEVNAME(zr), माप(ZR_DEVNAME(zr)), "MJPEG[%u]", zr->id);
	अगर (v4l2_ctrl_handler_init(&zr->hdl, 10))
		जाओ zr_unreg;
	zr->v4l2_dev.ctrl_handler = &zr->hdl;
	v4l2_ctrl_new_std(&zr->hdl, &zoran_video_ctrl_ops,
			  V4L2_CID_JPEG_COMPRESSION_QUALITY, 0,
			  100, 1, 50);
	spin_lock_init(&zr->spinlock);
	mutex_init(&zr->lock);
	अगर (pci_enable_device(pdev))
		जाओ zr_unreg;
	zr->revision = zr->pci_dev->revision;

	pci_info(zr->pci_dev, "Zoran ZR360%c7 (rev %d), irq: %d, memory: 0x%08llx\n",
		 zr->revision < 2 ? '5' : '6', zr->revision,
		 zr->pci_dev->irq, (uपूर्णांक64_t)pci_resource_start(zr->pci_dev, 0));
	अगर (zr->revision >= 2)
		pci_info(zr->pci_dev, "Subsystem vendor=0x%04x id=0x%04x\n",
			 zr->pci_dev->subप्रणाली_venकरोr, zr->pci_dev->subप्रणाली_device);

	/* Use स्वतः-detected card type? */
	अगर (card[nr] == -1) अणु
		अगर (zr->revision < 2) अणु
			pci_err(pdev, "No card type specified, please use the card=X module parameter\n");
			pci_err(pdev, "It is not possible to auto-detect ZR36057 based cards\n");
			जाओ zr_unreg;
		पूर्ण

		card_num = ent->driver_data;
		अगर (card_num >= NUM_CARDS) अणु
			pci_err(pdev, "Unknown card, try specifying card=X module parameter\n");
			जाओ zr_unreg;
		पूर्ण
		pci_info(zr->pci_dev, "%s() - card %s detected\n", __func__, zoran_cards[card_num].name);
	पूर्ण अन्यथा अणु
		card_num = card[nr];
		अगर (card_num >= NUM_CARDS || card_num < 0) अणु
			pci_err(pdev, "User specified card type %d out of range (0 .. %d)\n",
				card_num, NUM_CARDS - 1);
			जाओ zr_unreg;
		पूर्ण
	पूर्ण

	/*
	 * even though we make this a non poपूर्णांकer and thus
	 * theoretically allow क्रम making changes to this काष्ठा
	 * on a per-inभागidual card basis at runसमय, this is
	 * strongly discouraged. This काष्ठाure is पूर्णांकended to
	 * keep general card inक्रमmation, no settings or anything
	 */
	zr->card = zoran_cards[card_num];
	snम_लिखो(ZR_DEVNAME(zr), माप(ZR_DEVNAME(zr)), "%s[%u]",
		 zr->card.name, zr->id);

	err = pci_request_regions(pdev, ZR_DEVNAME(zr));
	अगर (err)
		जाओ zr_unreg;

	zr->zr36057_mem = devm_ioremap(&pdev->dev, pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
	अगर (!zr->zr36057_mem) अणु
		pci_err(pdev, "%s() - ioremap failed\n", __func__);
		जाओ zr_pci_release;
	पूर्ण

	result = pci_request_irq(pdev, 0, zoran_irq, शून्य, zr, ZR_DEVNAME(zr));
	अगर (result < 0) अणु
		अगर (result == -EINVAL) अणु
			pci_err(pdev, "%s - bad IRQ number or handler\n", __func__);
		पूर्ण अन्यथा अगर (result == -EBUSY) अणु
			pci_err(pdev, "%s - IRQ %d busy, change your PnP config in BIOS\n",
				__func__, zr->pci_dev->irq);
		पूर्ण अन्यथा अणु
			pci_err(pdev, "%s - cannot assign IRQ, error code %d\n", __func__, result);
		पूर्ण
		जाओ zr_pci_release;
	पूर्ण

	/* set PCI latency समयr */
	pci_पढ़ो_config_byte(zr->pci_dev, PCI_LATENCY_TIMER,
			     &latency);
	need_latency = zr->revision > 1 ? 32 : 48;
	अगर (latency != need_latency) अणु
		pci_info(zr->pci_dev, "Changing PCI latency from %d to %d\n", latency, need_latency);
		pci_ग_लिखो_config_byte(zr->pci_dev, PCI_LATENCY_TIMER, need_latency);
	पूर्ण

	zr36057_restart(zr);
	/* i2c */
	pci_info(zr->pci_dev, "Initializing i2c bus...\n");

	अगर (zoran_रेजिस्टर_i2c(zr) < 0) अणु
		pci_err(pdev, "%s - can't initialize i2c bus\n", __func__);
		जाओ zr_मुक्त_irq;
	पूर्ण

	zr->decoder = v4l2_i2c_new_subdev(&zr->v4l2_dev, &zr->i2c_adapter,
					  zr->card.i2c_decoder, 0,
					  zr->card.addrs_decoder);

	अगर (zr->card.i2c_encoder)
		zr->encoder = v4l2_i2c_new_subdev(&zr->v4l2_dev, &zr->i2c_adapter,
						  zr->card.i2c_encoder, 0,
						  zr->card.addrs_encoder);

	pci_info(zr->pci_dev, "Initializing videocodec bus...\n");

	अगर (zr->card.video_codec) अणु
		codec_name = codecid_to_modulename(zr->card.video_codec);
		अगर (codec_name) अणु
			result = request_module(codec_name);
			अगर (result)
				pci_err(pdev, "failed to load modules %s: %d\n", codec_name, result);
		पूर्ण
	पूर्ण
	अगर (zr->card.video_vfe) अणु
		vfe_name = codecid_to_modulename(zr->card.video_vfe);
		अगर (vfe_name) अणु
			result = request_module(vfe_name);
			अगर (result < 0)
				pci_err(pdev, "failed to load modules %s: %d\n", vfe_name, result);
		पूर्ण
	पूर्ण

	/* reset JPEG codec */
	jpeg_codec_sleep(zr, 1);
	jpeg_codec_reset(zr);
	/* video bus enabled */
	/* display codec revision */
	अगर (zr->card.video_codec != 0) अणु
		master_codec = zoran_setup_videocodec(zr, zr->card.video_codec);
		अगर (!master_codec)
			जाओ zr_unreg_i2c;
		zr->codec = videocodec_attach(master_codec);
		अगर (!zr->codec) अणु
			pci_err(pdev, "%s - no codec found\n", __func__);
			जाओ zr_unreg_i2c;
		पूर्ण
		अगर (zr->codec->type != zr->card.video_codec) अणु
			pci_err(pdev, "%s - wrong codec\n", __func__);
			जाओ zr_detach_codec;
		पूर्ण
	पूर्ण
	अगर (zr->card.video_vfe != 0) अणु
		master_vfe = zoran_setup_videocodec(zr, zr->card.video_vfe);
		अगर (!master_vfe)
			जाओ zr_detach_codec;
		zr->vfe = videocodec_attach(master_vfe);
		अगर (!zr->vfe) अणु
			pci_err(pdev, "%s - no VFE found\n", __func__);
			जाओ zr_detach_codec;
		पूर्ण
		अगर (zr->vfe->type != zr->card.video_vfe) अणु
			pci_err(pdev, "%s = wrong VFE\n", __func__);
			जाओ zr_detach_vfe;
		पूर्ण
	पूर्ण

	/* take care of Natoma chipset and a revision 1 zr36057 */
	अगर ((pci_pci_problems & PCIPCI_NATOMA) && zr->revision <= 1)
		pci_info(zr->pci_dev, "ZR36057/Natoma bug, max. buffer size is 128K\n");

	अगर (zr36057_init(zr) < 0)
		जाओ zr_detach_vfe;

	zr->map_mode = ZORAN_MAP_MODE_RAW;

	वापस 0;

zr_detach_vfe:
	videocodec_detach(zr->vfe);
zr_detach_codec:
	videocodec_detach(zr->codec);
zr_unreg_i2c:
	zoran_unरेजिस्टर_i2c(zr);
zr_मुक्त_irq:
	btग_लिखो(0, ZR36057_SPGPPCR);
	pci_मुक्त_irq(zr->pci_dev, 0, zr);
zr_pci_release:
	pci_release_regions(pdev);
zr_unreg:
	v4l2_ctrl_handler_मुक्त(&zr->hdl);
	v4l2_device_unरेजिस्टर(&zr->v4l2_dev);
zr_मुक्त_mem:

	वापस -ENODEV;
पूर्ण

अटल काष्ठा pci_driver zoran_driver = अणु
	.name = "zr36067",
	.id_table = zr36067_pci_tbl,
	.probe = zoran_probe,
	.हटाओ = zoran_हटाओ,
पूर्ण;

अटल पूर्णांक __init zoran_init(व्योम)
अणु
	पूर्णांक res;

	pr_info("Zoran MJPEG board driver version %s\n", ZORAN_VERSION);

	/* check the parameters we have been given, adjust अगर necessary */
	अगर (v4l_nbufs < 2)
		v4l_nbufs = 2;
	अगर (v4l_nbufs > VIDEO_MAX_FRAME)
		v4l_nbufs = VIDEO_MAX_FRAME;
	/* The user specअगरies the in KB, we want them in byte (and page aligned) */
	v4l_bufsize = PAGE_ALIGN(v4l_bufsize * 1024);
	अगर (v4l_bufsize < 32768)
		v4l_bufsize = 32768;
	/* 2 MB is arbitrary but sufficient क्रम the maximum possible images */
	अगर (v4l_bufsize > 2048 * 1024)
		v4l_bufsize = 2048 * 1024;
	अगर (jpg_nbufs < 4)
		jpg_nbufs = 4;
	अगर (jpg_nbufs > BUZ_MAX_FRAME)
		jpg_nbufs = BUZ_MAX_FRAME;
	jpg_bufsize = PAGE_ALIGN(jpg_bufsize * 1024);
	अगर (jpg_bufsize < 8192)
		jpg_bufsize = 8192;
	अगर (jpg_bufsize > (512 * 1024))
		jpg_bufsize = 512 * 1024;
	/* Use parameter क्रम vidmem or try to find a video card */
	अगर (vidmem)
		pr_info("%s: Using supplied video memory base address @ 0x%lx\n", ZORAN_NAME, vidmem);

	/* some मुख्यboards might not करो PCI-PCI data transfer well */
	अगर (pci_pci_problems & (PCIPCI_FAIL | PCIAGP_FAIL | PCIPCI_ALIMAGIK))
		pr_warn("%s: chipset does not support reliable PCI-PCI DMA\n", ZORAN_NAME);

	res = pci_रेजिस्टर_driver(&zoran_driver);
	अगर (res) अणु
		pr_err("Unable to register ZR36057 driver\n");
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास zoran_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&zoran_driver);
पूर्ण

module_init(zoran_init);
module_निकास(zoran_निकास);
