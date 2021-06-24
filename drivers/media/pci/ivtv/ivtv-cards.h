<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Functions to query card hardware
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_CARDS_H
#घोषणा IVTV_CARDS_H

/* Supported cards */
#घोषणा IVTV_CARD_PVR_250	      0	/* WinTV PVR 250 */
#घोषणा IVTV_CARD_PVR_350	      1	/* encoder, decoder, tv-out */
#घोषणा IVTV_CARD_PVR_150	      2	/* WinTV PVR 150 and PVR 500 (really just two
					   PVR150s on one PCI board) */
#घोषणा IVTV_CARD_M179		      3	/* AVerMedia M179 (encoder only) */
#घोषणा IVTV_CARD_MPG600	      4	/* Kuroutoshikou ITVC16-STVLP/YUAN MPG600, encoder only */
#घोषणा IVTV_CARD_MPG160	      5	/* Kuroutoshikou ITVC15-STVLP/YUAN MPG160
					   cx23415 based, but करोes not have tv-out */
#घोषणा IVTV_CARD_PG600		      6	/* YUAN PG600/DIAMONDMM PVR-550 based on the CX Falcon 2 */
#घोषणा IVTV_CARD_AVC2410	      7	/* Adaptec AVC-2410 */
#घोषणा IVTV_CARD_AVC2010	      8	/* Adaptec AVD-2010 (No Tuner) */
#घोषणा IVTV_CARD_TG5000TV	      9 /* NAGASE TRANSGEAR 5000TV, encoder only */
#घोषणा IVTV_CARD_VA2000MAX_SNT6     10 /* VA2000MAX-STN6 */
#घोषणा IVTV_CARD_CX23416GYC	     11 /* Kuroutoshikou CX23416GYC-STVLP (Yuan MPG600GR OEM) */
#घोषणा IVTV_CARD_GV_MVPRX	     12 /* I/O Data GV-MVP/RX, RX2, RX2W */
#घोषणा IVTV_CARD_GV_MVPRX2E	     13 /* I/O Data GV-MVP/RX2E */
#घोषणा IVTV_CARD_GOTVIEW_PCI_DVD    14	/* GotView PCI DVD */
#घोषणा IVTV_CARD_GOTVIEW_PCI_DVD2   15	/* GotView PCI DVD2 */
#घोषणा IVTV_CARD_YUAN_MPC622        16	/* Yuan MPC622 miniPCI */
#घोषणा IVTV_CARD_DCTMTVP1	     17 /* DIGITAL COWBOY DCT-MTVP1 */
#घोषणा IVTV_CARD_PG600V2	     18 /* Yuan PG600V2/GotView PCI DVD Lite */
#घोषणा IVTV_CARD_CLUB3D	     19 /* Club3D ZAP-TV1x01 */
#घोषणा IVTV_CARD_AVERTV_MCE116	     20 /* AVerTV MCE 116 Plus */
#घोषणा IVTV_CARD_ASUS_FALCON2	     21 /* ASUS Falcon2 */
#घोषणा IVTV_CARD_AVER_PVR150PLUS    22 /* AVerMedia PVR-150 Plus */
#घोषणा IVTV_CARD_AVER_EZMAKER       23 /* AVerMedia EZMaker PCI Deluxe */
#घोषणा IVTV_CARD_AVER_M104          24 /* AverMedia M104 miniPCI card */
#घोषणा IVTV_CARD_BUFFALO_MV5L       25 /* Buffalo PC-MV5L/PCI card */
#घोषणा IVTV_CARD_AVER_ULTRA1500MCE  26 /* AVerMedia UltraTV 1500 MCE */
#घोषणा IVTV_CARD_KIKYOU             27 /* Sony VAIO Giga Pocket (ENX Kikyou) */
#घोषणा IVTV_CARD_LAST		     27

/* Variants of existing cards but with the same PCI IDs. The driver
   detects these based on other device inक्रमmation.
   These cards must always come last.
   New cards must be inserted above, and the indices of the cards below
   must be adjusted accordingly. */

/* PVR-350 V1 (uses saa7114) */
#घोषणा IVTV_CARD_PVR_350_V1	     (IVTV_CARD_LAST+1)
/* 2 variants of Kuroutoshikou CX23416GYC-STVLP (Yuan MPG600GR OEM) */
#घोषणा IVTV_CARD_CX23416GYC_NOGR    (IVTV_CARD_LAST+2)
#घोषणा IVTV_CARD_CX23416GYC_NOGRYCS (IVTV_CARD_LAST+3)

/* प्रणाली venकरोr and device IDs */
#घोषणा PCI_VENDOR_ID_ICOMP  0x4444
#घोषणा PCI_DEVICE_ID_IVTV15 0x0803
#घोषणा PCI_DEVICE_ID_IVTV16 0x0016

/* subप्रणाली venकरोr ID */
#घोषणा IVTV_PCI_ID_HAUPPAUGE		0x0070
#घोषणा IVTV_PCI_ID_HAUPPAUGE_ALT1	0x0270
#घोषणा IVTV_PCI_ID_HAUPPAUGE_ALT2	0x4070
#घोषणा IVTV_PCI_ID_ADAPTEC		0x9005
#घोषणा IVTV_PCI_ID_ASUSTEK		0x1043
#घोषणा IVTV_PCI_ID_AVERMEDIA		0x1461
#घोषणा IVTV_PCI_ID_YUAN1		0x12ab
#घोषणा IVTV_PCI_ID_YUAN2		0xff01
#घोषणा IVTV_PCI_ID_YUAN3		0xffab
#घोषणा IVTV_PCI_ID_YUAN4		0xfbab
#घोषणा IVTV_PCI_ID_DIAMONDMM		0xff92
#घोषणा IVTV_PCI_ID_IODATA		0x10fc
#घोषणा IVTV_PCI_ID_MELCO		0x1154
#घोषणा IVTV_PCI_ID_GOTVIEW1		0xffac
#घोषणा IVTV_PCI_ID_GOTVIEW2		0xffad
#घोषणा IVTV_PCI_ID_SONY		0x104d

/* hardware flags, no gaps allowed */
#घोषणा IVTV_HW_CX25840			(1 << 0)
#घोषणा IVTV_HW_SAA7115			(1 << 1)
#घोषणा IVTV_HW_SAA7127			(1 << 2)
#घोषणा IVTV_HW_MSP34XX			(1 << 3)
#घोषणा IVTV_HW_TUNER			(1 << 4)
#घोषणा IVTV_HW_WM8775			(1 << 5)
#घोषणा IVTV_HW_CS53L32A		(1 << 6)
#घोषणा IVTV_HW_TVEEPROM		(1 << 7)
#घोषणा IVTV_HW_SAA7114			(1 << 8)
#घोषणा IVTV_HW_UPD64031A		(1 << 9)
#घोषणा IVTV_HW_UPD6408X		(1 << 10)
#घोषणा IVTV_HW_SAA717X			(1 << 11)
#घोषणा IVTV_HW_WM8739			(1 << 12)
#घोषणा IVTV_HW_VP27SMPX		(1 << 13)
#घोषणा IVTV_HW_M52790			(1 << 14)
#घोषणा IVTV_HW_GPIO			(1 << 15)
#घोषणा IVTV_HW_I2C_IR_RX_AVER		(1 << 16)
#घोषणा IVTV_HW_I2C_IR_RX_HAUP_EXT	(1 << 17) /* External beक्रमe पूर्णांकernal */
#घोषणा IVTV_HW_I2C_IR_RX_HAUP_INT	(1 << 18)
#घोषणा IVTV_HW_Z8F0811_IR_HAUP		(1 << 19)
#घोषणा IVTV_HW_I2C_IR_RX_ADAPTEC	(1 << 20)

#घोषणा IVTV_HW_SAA711X   (IVTV_HW_SAA7115 | IVTV_HW_SAA7114)

#घोषणा IVTV_HW_IR_ANY (IVTV_HW_I2C_IR_RX_AVER | \
			IVTV_HW_I2C_IR_RX_HAUP_EXT | \
			IVTV_HW_I2C_IR_RX_HAUP_INT | \
			IVTV_HW_Z8F0811_IR_HAUP | \
			IVTV_HW_I2C_IR_RX_ADAPTEC)

/* video inमाला_दो */
#घोषणा	IVTV_CARD_INPUT_VID_TUNER	1
#घोषणा	IVTV_CARD_INPUT_SVIDEO1		2
#घोषणा	IVTV_CARD_INPUT_SVIDEO2		3
#घोषणा	IVTV_CARD_INPUT_COMPOSITE1	4
#घोषणा	IVTV_CARD_INPUT_COMPOSITE2	5
#घोषणा	IVTV_CARD_INPUT_COMPOSITE3	6

/* audio inमाला_दो */
#घोषणा	IVTV_CARD_INPUT_AUD_TUNER	1
#घोषणा	IVTV_CARD_INPUT_LINE_IN1	2
#घोषणा	IVTV_CARD_INPUT_LINE_IN2	3

#घोषणा IVTV_CARD_MAX_VIDEO_INPUTS 6
#घोषणा IVTV_CARD_MAX_AUDIO_INPUTS 3
#घोषणा IVTV_CARD_MAX_TUNERS	   3

/* SAA71XX HW inमाला_दो */
#घोषणा IVTV_SAA71XX_COMPOSITE0 0
#घोषणा IVTV_SAA71XX_COMPOSITE1 1
#घोषणा IVTV_SAA71XX_COMPOSITE2 2
#घोषणा IVTV_SAA71XX_COMPOSITE3 3
#घोषणा IVTV_SAA71XX_COMPOSITE4 4
#घोषणा IVTV_SAA71XX_COMPOSITE5 5
#घोषणा IVTV_SAA71XX_SVIDEO0    6
#घोषणा IVTV_SAA71XX_SVIDEO1    7
#घोषणा IVTV_SAA71XX_SVIDEO2    8
#घोषणा IVTV_SAA71XX_SVIDEO3    9

/* SAA717X needs to mark the tuner input by ORing with this flag */
#घोषणा IVTV_SAA717X_TUNER_FLAG 0x80

/* Dummy HW input */
#घोषणा IVTV_DUMMY_AUDIO        0

/* GPIO HW inमाला_दो */
#घोषणा IVTV_GPIO_TUNER   0
#घोषणा IVTV_GPIO_LINE_IN 1

/* SAA717X HW inमाला_दो */
#घोषणा IVTV_SAA717X_IN0 0
#घोषणा IVTV_SAA717X_IN1 1
#घोषणा IVTV_SAA717X_IN2 2

/* V4L2 capability aliases */
#घोषणा IVTV_CAP_ENCODER (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER | \
			  V4L2_CAP_AUDIO | V4L2_CAP_READWRITE | V4L2_CAP_VBI_CAPTURE | \
			  V4L2_CAP_SLICED_VBI_CAPTURE)
#घोषणा IVTV_CAP_DECODER (V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_SLICED_VBI_OUTPUT)

काष्ठा ivtv_card_video_input अणु
	u8  video_type;		/* video input type */
	u8  audio_index;	/* index in ivtv_card_audio_input array */
	u16 video_input;	/* hardware video input */
पूर्ण;

काष्ठा ivtv_card_audio_input अणु
	u8  audio_type;		/* audio input type */
	u32 audio_input;	/* hardware audio input */
	u16 muxer_input;	/* hardware muxer input क्रम boards with a
				   multiplexer chip */
पूर्ण;

काष्ठा ivtv_card_output अणु
	u8  name[32];
	u16 video_output;  /* hardware video output */
पूर्ण;

काष्ठा ivtv_card_pci_info अणु
	u16 device;
	u16 subप्रणाली_venकरोr;
	u16 subप्रणाली_device;
पूर्ण;

/* GPIO definitions */

/* The mask is the set of bits used by the operation */

काष्ठा ivtv_gpio_init अणु		/* set initial GPIO सूची and OUT values */
	u16 direction;		/* सूची setting. Leave to 0 अगर no init is needed */
	u16 initial_value;
पूर्ण;

काष्ठा ivtv_gpio_video_input अणु	/* select tuner/line in input */
	u16 mask;		/* leave to 0 अगर not supported */
	u16 tuner;
	u16 composite;
	u16 svideo;
पूर्ण;

काष्ठा ivtv_gpio_audio_input अणु	/* select tuner/line in input */
	u16 mask;		/* leave to 0 अगर not supported */
	u16 tuner;
	u16 linein;
	u16 radio;
पूर्ण;

काष्ठा ivtv_gpio_audio_mute अणु
	u16 mask;		/* leave to 0 अगर not supported */
	u16 mute;		/* set this value to mute, 0 to unmute */
पूर्ण;

काष्ठा ivtv_gpio_audio_mode अणु
	u16 mask;		/* leave to 0 अगर not supported */
	u16 mono;		/* set audio to mono */
	u16 stereo;		/* set audio to stereo */
	u16 lang1;		/* set audio to the first language */
	u16 lang2;		/* set audio to the second language */
	u16 both;		/* both languages are output */
पूर्ण;

काष्ठा ivtv_gpio_audio_freq अणु
	u16 mask;		/* leave to 0 अगर not supported */
	u16 f32000;
	u16 f44100;
	u16 f48000;
पूर्ण;

काष्ठा ivtv_gpio_audio_detect अणु
	u16 mask;		/* leave to 0 अगर not supported */
	u16 stereo;		/* अगर the input matches this value then
				   stereo is detected */
पूर्ण;

काष्ठा ivtv_card_tuner अणु
	v4l2_std_id std;	/* standard क्रम which the tuner is suitable */
	पूर्णांक	    tuner;	/* tuner ID (from tuner.h) */
पूर्ण;

काष्ठा ivtv_card_tuner_i2c अणु
	अचिन्हित लघु radio[2];/* radio tuner i2c address to probe */
	अचिन्हित लघु demod[2];/* demodulator i2c address to probe */
	अचिन्हित लघु tv[4];	/* tv tuner i2c addresses to probe */
पूर्ण;

/* क्रम card inक्रमmation/parameters */
काष्ठा ivtv_card अणु
	पूर्णांक type;
	अक्षर *name;
	अक्षर *comment;
	u32 v4l2_capabilities;
	u32 hw_video;		/* hardware used to process video */
	u32 hw_audio;		/* hardware used to process audio */
	u32 hw_audio_ctrl;	/* hardware used क्रम the V4L2 controls (only 1 dev allowed) */
	u32 hw_muxer;		/* hardware used to multiplex audio input */
	u32 hw_all;		/* all hardware used by the board */
	काष्ठा ivtv_card_video_input video_inमाला_दो[IVTV_CARD_MAX_VIDEO_INPUTS];
	काष्ठा ivtv_card_audio_input audio_inमाला_दो[IVTV_CARD_MAX_AUDIO_INPUTS];
	काष्ठा ivtv_card_audio_input radio_input;
	पूर्णांक nof_outमाला_दो;
	स्थिर काष्ठा ivtv_card_output *video_outमाला_दो;
	u8 gr_config;		/* config byte क्रम the ghost reduction device */
	u8 xceive_pin;		/* XCeive tuner GPIO reset pin */

	/* GPIO card-specअगरic settings */
	काष्ठा ivtv_gpio_init		gpio_init;
	काष्ठा ivtv_gpio_video_input	gpio_video_input;
	काष्ठा ivtv_gpio_audio_input	gpio_audio_input;
	काष्ठा ivtv_gpio_audio_mute	gpio_audio_mute;
	काष्ठा ivtv_gpio_audio_mode	gpio_audio_mode;
	काष्ठा ivtv_gpio_audio_freq	gpio_audio_freq;
	काष्ठा ivtv_gpio_audio_detect	gpio_audio_detect;

	काष्ठा ivtv_card_tuner tuners[IVTV_CARD_MAX_TUNERS];
	काष्ठा ivtv_card_tuner_i2c *i2c;

	/* list of device and subप्रणाली venकरोr/devices that
	   correspond to this card type. */
	स्थिर काष्ठा ivtv_card_pci_info *pci_list;
पूर्ण;

पूर्णांक ivtv_get_input(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_input *input);
पूर्णांक ivtv_get_output(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_output *output);
पूर्णांक ivtv_get_audio_input(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_audio *input);
पूर्णांक ivtv_get_audio_output(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_audioout *output);
स्थिर काष्ठा ivtv_card *ivtv_get_card(u16 index);

#पूर्ण_अगर
