<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * em28xx.h - driver क्रम Empia EM2800/EM2820/2840 USB video capture devices
 *
 * Copyright (C) 2005 Markus Rechberger <mrechberger@gmail.com>
 *		      Luकरोvico Caveकरोn <caveकरोn@sssup.it>
 *		      Mauro Carvalho Chehab <mchehab@kernel.org>
 * Copyright (C) 2012 Frank Schथअfer <fschaefer.oss@googlemail.com>
 *
 * Based on the em2800 driver from Sascha Sommer <saschasommer@मुक्तnet.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _EM28XX_H
#घोषणा _EM28XX_H

#समावेश <linux/bitfield.h>

#घोषणा EM28XX_VERSION "0.2.2"
#घोषणा DRIVER_DESC    "Empia em28xx device driver"

#समावेश <linux/workqueue.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>
#समावेश <linux/videodev2.h>

#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश <media/rc-core.h>
#समावेश "tuner-xc2028.h"
#समावेश "xc5000.h"
#समावेश "em28xx-reg.h"

/* Boards supported by driver */
#घोषणा EM2800_BOARD_UNKNOWN			  0
#घोषणा EM2820_BOARD_UNKNOWN			  1
#घोषणा EM2820_BOARD_TERRATEC_CINERGY_250	  2
#घोषणा EM2820_BOARD_PINNACLE_USB_2		  3
#घोषणा EM2820_BOARD_HAUPPAUGE_WINTV_USB_2	  4
#घोषणा EM2820_BOARD_MSI_VOX_USB_2		  5
#घोषणा EM2800_BOARD_TERRATEC_CINERGY_200	  6
#घोषणा EM2800_BOARD_LEADTEK_WINFAST_USBII	  7
#घोषणा EM2800_BOARD_KWORLD_USB2800		  8
#घोषणा EM2820_BOARD_PINNACLE_DVC_90		  9
#घोषणा EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900	  10
#घोषणा EM2880_BOARD_TERRATEC_HYBRID_XS		  11
#घोषणा EM2820_BOARD_KWORLD_PVRTV2800RF		  12
#घोषणा EM2880_BOARD_TERRATEC_PRODIGY_XS	  13
#घोषणा EM2820_BOARD_PROLINK_PLAYTV_USB2	  14
#घोषणा EM2800_BOARD_VGEAR_POCKETTV		  15
#घोषणा EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950	  16
#घोषणा EM2880_BOARD_PINNACLE_PCTV_HD_PRO	  17
#घोषणा EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2	  18
#घोषणा EM2860_BOARD_SAA711X_REFERENCE_DESIGN	  19
#घोषणा EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600	  20
#घोषणा EM2800_BOARD_GRABBEEX_USB2800		  21
#घोषणा EM2750_BOARD_UNKNOWN			  22
#घोषणा EM2750_BOARD_DLCW_130			  23
#घोषणा EM2820_BOARD_DLINK_USB_TV		  24
#घोषणा EM2820_BOARD_GADMEI_UTV310		  25
#घोषणा EM2820_BOARD_HERCULES_SMART_TV_USB2	  26
#घोषणा EM2820_BOARD_PINNACLE_USB_2_FM1216ME	  27
#घोषणा EM2820_BOARD_LEADTEK_WINFAST_USBII_DELUXE 28
#घोषणा EM2860_BOARD_TVP5150_REFERENCE_DESIGN	  29
#घोषणा EM2820_BOARD_VIDEOLOGY_20K14XUSB	  30
#घोषणा EM2821_BOARD_USBGEAR_VD204		  31
#घोषणा EM2821_BOARD_SUPERCOMP_USB_2		  32
#घोषणा EM2860_BOARD_ELGATO_VIDEO_CAPTURE	  33
#घोषणा EM2860_BOARD_TERRATEC_HYBRID_XS		  34
#घोषणा EM2860_BOARD_TYPHOON_DVD_MAKER		  35
#घोषणा EM2860_BOARD_NETGMBH_CAM		  36
#घोषणा EM2860_BOARD_GADMEI_UTV330		  37
#घोषणा EM2861_BOARD_YAKUMO_MOVIE_MIXER		  38
#घोषणा EM2861_BOARD_KWORLD_PVRTV_300U		  39
#घोषणा EM2861_BOARD_PLEXTOR_PX_TV100U		  40
#घोषणा EM2870_BOARD_KWORLD_350U		  41
#घोषणा EM2870_BOARD_KWORLD_355U		  42
#घोषणा EM2870_BOARD_TERRATEC_XS		  43
#घोषणा EM2870_BOARD_TERRATEC_XS_MT2060		  44
#घोषणा EM2870_BOARD_PINNACLE_PCTV_DVB		  45
#घोषणा EM2870_BOARD_COMPRO_VIDEOMATE		  46
#घोषणा EM2880_BOARD_KWORLD_DVB_305U		  47
#घोषणा EM2880_BOARD_KWORLD_DVB_310U		  48
#घोषणा EM2880_BOARD_MSI_DIGIVOX_AD		  49
#घोषणा EM2880_BOARD_MSI_DIGIVOX_AD_II		  50
#घोषणा EM2880_BOARD_TERRATEC_HYBRID_XS_FR	  51
#घोषणा EM2881_BOARD_DNT_DA2_HYBRID		  52
#घोषणा EM2881_BOARD_PINNACLE_HYBRID_PRO	  53
#घोषणा EM2882_BOARD_KWORLD_VS_DVBT		  54
#घोषणा EM2882_BOARD_TERRATEC_HYBRID_XS		  55
#घोषणा EM2882_BOARD_PINNACLE_HYBRID_PRO_330E	  56
#घोषणा EM2883_BOARD_KWORLD_HYBRID_330U		  57
#घोषणा EM2820_BOARD_COMPRO_VIDEOMATE_FORYOU	  58
#घोषणा EM2874_BOARD_PCTV_HD_MINI_80E		  59
#घोषणा EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850	  60
#घोषणा EM2820_BOARD_PROLINK_PLAYTV_BOX4_USB2	  61
#घोषणा EM2820_BOARD_GADMEI_TVR200		  62
#घोषणा EM2860_BOARD_KAIOMY_TVNPC_U2		  63
#घोषणा EM2860_BOARD_EASYCAP			  64
#घोषणा EM2820_BOARD_IODATA_GVMVP_SZ		  65
#घोषणा EM2880_BOARD_EMPIRE_DUAL_TV		  66
#घोषणा EM2860_BOARD_TERRATEC_GRABBY		  67
#घोषणा EM2860_BOARD_TERRATEC_AV350		  68
#घोषणा EM2882_BOARD_KWORLD_ATSC_315U		  69
#घोषणा EM2882_BOARD_EVGA_INDTUBE		  70
#घोषणा EM2820_BOARD_SILVERCREST_WEBCAM		  71
#घोषणा EM2861_BOARD_GADMEI_UTV330PLUS		  72
#घोषणा EM2870_BOARD_REDDO_DVB_C_USB_BOX	  73
#घोषणा EM2800_BOARD_VC211A			  74
#घोषणा EM2882_BOARD_DIKOM_DK300		  75
#घोषणा EM2870_BOARD_KWORLD_A340		  76
#घोषणा EM2874_BOARD_LEADERSHIP_ISDBT		  77
#घोषणा EM28174_BOARD_PCTV_290E			  78
#घोषणा EM2884_BOARD_TERRATEC_H5		  79
#घोषणा EM28174_BOARD_PCTV_460E			  80
#घोषणा EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C	  81
#घोषणा EM2884_BOARD_CINERGY_HTC_STICK		  82
#घोषणा EM2860_BOARD_HT_VIDBOX_NW03		  83
#घोषणा EM2874_BOARD_MAXMEDIA_UB425_TC		  84
#घोषणा EM2884_BOARD_PCTV_510E			  85
#घोषणा EM2884_BOARD_PCTV_520E			  86
#घोषणा EM2884_BOARD_TERRATEC_HTC_USB_XS	  87
#घोषणा EM2884_BOARD_C3TECH_DIGITAL_DUO		  88
#घोषणा EM2874_BOARD_DELOCK_61959		  89
#घोषणा EM2874_BOARD_KWORLD_UB435Q_V2		  90
#घोषणा EM2765_BOARD_SPEEDLINK_VAD_LAPLACE	  91
#घोषणा EM28178_BOARD_PCTV_461E                   92
#घोषणा EM2874_BOARD_KWORLD_UB435Q_V3		  93
#घोषणा EM28178_BOARD_PCTV_292E                   94
#घोषणा EM2861_BOARD_LEADTEK_VC100                95
#घोषणा EM28178_BOARD_TERRATEC_T2_STICK_HD        96
#घोषणा EM2884_BOARD_ELGATO_EYETV_HYBRID_2008     97
#घोषणा EM28178_BOARD_PLEX_PX_BCUD                98
#घोषणा EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB  99
#घोषणा EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595 100
#घोषणा EM2884_BOARD_TERRATEC_H6		  101
#घोषणा EM2882_BOARD_ZOLID_HYBRID_TV_STICK		102
#घोषणा EM2861_BOARD_MAGIX_VIDEOWANDLER2          103
#घोषणा EM28178_BOARD_PCTV_461E_V2                104
#घोषणा EM2860_BOARD_MYGICA_IGRABBER              105
#घोषणा EM2874_BOARD_HAUPPAUGE_USB_QUADHD         106

/* Limits minimum and शेष number of buffers */
#घोषणा EM28XX_MIN_BUF 4
#घोषणा EM28XX_DEF_BUF 8

/*Limits the max URB message size */
#घोषणा URB_MAX_CTRL_SIZE 80

/* Params क्रम validated field */
#घोषणा EM28XX_BOARD_NOT_VALIDATED 1
#घोषणा EM28XX_BOARD_VALIDATED	   0

/* Params क्रम em28xx_cmd() audio */
#घोषणा EM28XX_START_AUDIO      1
#घोषणा EM28XX_STOP_AUDIO       0

/* maximum number of em28xx boards */
#घोषणा EM28XX_MAXBOARDS DVB_MAX_ADAPTERS /* All adapters could be em28xx */

/* maximum number of frames that can be queued */
#घोषणा EM28XX_NUM_FRAMES 5
/* number of frames that get used क्रम v4l2_पढ़ो() */
#घोषणा EM28XX_NUM_READ_FRAMES 2

/* number of buffers क्रम isoc transfers */
#घोषणा EM28XX_NUM_BUFS 5
#घोषणा EM28XX_DVB_NUM_BUFS 5

/* max number of I2C buses on em28xx devices */
#घोषणा NUM_I2C_BUSES	2

/*
 * isoc transfers: number of packets क्रम each buffer
 * winकरोws requests only 64 packets .. so we better करो the same
 * this is what I found out क्रम all alternate numbers there!
 */
#घोषणा EM28XX_NUM_ISOC_PACKETS 64
#घोषणा EM28XX_DVB_NUM_ISOC_PACKETS 64

/*
 * bulk transfers: transfer buffer size = packet size * packet multiplier
 * USB 2.0 spec says bulk packet size is always 512 bytes
 */
#घोषणा EM28XX_BULK_PACKET_MULTIPLIER 384
#घोषणा EM28XX_DVB_BULK_PACKET_MULTIPLIER 94

#घोषणा EM28XX_INTERLACED_DEFAULT 1

/* समय in msecs to रुको क्रम AC97 xfers to finish */
#घोषणा EM28XX_AC97_XFER_TIMEOUT	100

/* max. number of button state polling addresses */
#घोषणा EM28XX_NUM_BUTTON_ADDRESSES_MAX		5

#घोषणा PRIMARY_TS	0
#घोषणा SECONDARY_TS	1

क्रमागत em28xx_mode अणु
	EM28XX_SUSPEND,
	EM28XX_ANALOG_MODE,
	EM28XX_DIGITAL_MODE,
पूर्ण;

काष्ठा em28xx;

/**
 * काष्ठा em28xx_usb_bufs - Contains URB-related buffer data
 *
 * @max_pkt_size:	max packet size of isoc transaction
 * @num_packets:	number of packets in each buffer
 * @num_bufs:		number of allocated urb
 * @urb:		urb क्रम isoc/bulk transfers
 * @buf:		transfer buffers क्रम isoc/bulk transfer
 */
काष्ठा em28xx_usb_bufs अणु
	पूर्णांक				max_pkt_size;
	पूर्णांक				num_packets;
	पूर्णांक				num_bufs;
	काष्ठा urb			**urb;
	अक्षर				**buf;
पूर्ण;

/**
 * काष्ठा em28xx_usb_ctl - Contains URB-related buffer data
 *
 * @analog_bufs:	isoc/bulk transfer buffers क्रम analog mode
 * @digital_bufs:	isoc/bulk transfer buffers क्रम digital mode
 * @vid_buf:		Stores alपढ़ोy requested video buffers
 * @vbi_buf:		Stores alपढ़ोy requested VBI buffers
 * @urb_data_copy:	copy data from URB
 */
काष्ठा em28xx_usb_ctl अणु
	काष्ठा em28xx_usb_bufs		analog_bufs;
	काष्ठा em28xx_usb_bufs		digital_bufs;
	काष्ठा em28xx_buffer	*vid_buf;
	काष्ठा em28xx_buffer	*vbi_buf;
	पूर्णांक (*urb_data_copy)(काष्ठा em28xx *dev, काष्ठा urb *urb);
पूर्ण;

/**
 * काष्ठा em28xx_fmt - Struct to क्रमागतberate video क्रमmats
 *
 * @fourcc:	v4l2 क्रमmat id
 * @depth:	mean number of bits to represent a pixel
 * @reg:	em28xx रेजिस्टर value to set it
 */
काष्ठा em28xx_fmt अणु
	u32	fourcc;
	पूर्णांक	depth;
	पूर्णांक	reg;
पूर्ण;

/**
 * काष्ठा em28xx_buffer- buffer क्रम storing one video frame
 *
 * @vb:		common v4l buffer stuff
 * @list:	List to associate it with the other buffers
 * @mem:	poपूर्णांकer to the buffer, as वापसed by vb2_plane_vaddr()
 * @length:	length of the buffer, as वापसed by vb2_plane_size()
 * @top_field:	If non-zero, indicate that the buffer is the top field
 * @pos:	Indicate the next position of the buffer to be filled.
 * @vb_buf:	poपूर्णांकer to vदो_स्मृति memory address in vb
 *
 * .. note::
 *
 *    in पूर्णांकerlaced mode, @pos is reset to zero at the start of each new
 *    field (not frame !)
 */
काष्ठा em28xx_buffer अणु
	काष्ठा vb2_v4l2_buffer	vb;		/* must be first */

	काष्ठा list_head	list;

	व्योम			*mem;
	अचिन्हित पूर्णांक		length;
	पूर्णांक			top_field;

	अचिन्हित पूर्णांक		pos;

	अक्षर			*vb_buf;
पूर्ण;

काष्ठा em28xx_dmaqueue अणु
	काष्ठा list_head       active;

	रुको_queue_head_t          wq;
पूर्ण;

/* inमाला_दो */

#घोषणा MAX_EM28XX_INPUT 4
क्रमागत क्रमागत28xx_itype अणु
	EM28XX_VMUX_COMPOSITE = 1,
	EM28XX_VMUX_SVIDEO,
	EM28XX_VMUX_TELEVISION,
	EM28XX_RADIO,
पूर्ण;

क्रमागत em28xx_ac97_mode अणु
	EM28XX_NO_AC97 = 0,
	EM28XX_AC97_EM202,
	EM28XX_AC97_SIGMATEL,
	EM28XX_AC97_OTHER,
पूर्ण;

काष्ठा em28xx_audio_mode अणु
	क्रमागत em28xx_ac97_mode ac97;
पूर्ण;

क्रमागत em28xx_पूर्णांक_audio_type अणु
	EM28XX_INT_AUDIO_NONE = 0,
	EM28XX_INT_AUDIO_AC97,
	EM28XX_INT_AUDIO_I2S,
पूर्ण;

क्रमागत em28xx_usb_audio_type अणु
	EM28XX_USB_AUDIO_NONE = 0,
	EM28XX_USB_AUDIO_CLASS,
	EM28XX_USB_AUDIO_VENDOR,
पूर्ण;

/**
 * क्रमागत em28xx_amux - describes the type of audio input used by em28xx
 *
 * @EM28XX_AMUX_UNUSED:
 *	Used only on em28xx dev->map field, in order to mark an entry
 *	as unused.
 * @EM28XX_AMUX_VIDEO:
 *	On devices without AC97, this is the only value that it is currently
 *	allowed.
 *	On devices with AC97, it corresponds to the AC97 mixer "Video" control.
 * @EM28XX_AMUX_LINE_IN:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "Line In".
 * @EM28XX_AMUX_VIDEO2:
 *	Only क्रम devices with AC97. It means that em28xx should use "Line In"
 *	And AC97 should use the "Video" mixer control.
 * @EM28XX_AMUX_PHONE:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "Phone".
 * @EM28XX_AMUX_MIC:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "Mic".
 * @EM28XX_AMUX_CD:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "CD".
 * @EM28XX_AMUX_AUX:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "Aux".
 * @EM28XX_AMUX_PCM_OUT:
 *	Only क्रम devices with AC97. Corresponds to AC97 mixer "PCM out".
 *
 * The em28xx chip itself has only two audio inमाला_दो: tuner and line in.
 * On almost all devices, only the tuner input is used.
 *
 * However, on most devices, an auxiliary AC97 codec device is used,
 * usually connected to the em28xx tuner input (except क्रम
 * @EM28XX_AMUX_LINE_IN).
 *
 * The AC97 device typically have several dअगरferent inमाला_दो and outमाला_दो.
 * The exact number and description depends on their model.
 *
 * It is possible to AC97 to mixer more than one dअगरferent entries at the
 * same समय, via the alsa mux.
 */
क्रमागत em28xx_amux अणु
	EM28XX_AMUX_UNUSED = -1,
	EM28XX_AMUX_VIDEO = 0,
	EM28XX_AMUX_LINE_IN,

	/* Some less-common mixer setups */
	EM28XX_AMUX_VIDEO2,
	EM28XX_AMUX_PHONE,
	EM28XX_AMUX_MIC,
	EM28XX_AMUX_CD,
	EM28XX_AMUX_AUX,
	EM28XX_AMUX_PCM_OUT,
पूर्ण;

क्रमागत em28xx_aout अणु
	/* AC97 outमाला_दो */
	EM28XX_AOUT_MASTER = BIT(0),
	EM28XX_AOUT_LINE   = BIT(1),
	EM28XX_AOUT_MONO   = BIT(2),
	EM28XX_AOUT_LFE    = BIT(3),
	EM28XX_AOUT_SURR   = BIT(4),

	/* PCM IN Mixer - used by AC97_RECORD_SELECT रेजिस्टर */
	EM28XX_AOUT_PCM_IN = BIT(7),

	/* Bits 10-8 are used to indicate the PCM IN record select */
	EM28XX_AOUT_PCM_MIC_PCM = 0 << 8,
	EM28XX_AOUT_PCM_CD	= 1 << 8,
	EM28XX_AOUT_PCM_VIDEO	= 2 << 8,
	EM28XX_AOUT_PCM_AUX	= 3 << 8,
	EM28XX_AOUT_PCM_LINE	= 4 << 8,
	EM28XX_AOUT_PCM_STEREO	= 5 << 8,
	EM28XX_AOUT_PCM_MONO	= 6 << 8,
	EM28XX_AOUT_PCM_PHONE	= 7 << 8,
पूर्ण;

अटल अंतरभूत पूर्णांक ac97_वापस_record_select(पूर्णांक a_out)
अणु
	वापस (a_out & 0x700) >> 8;
पूर्ण

काष्ठा em28xx_reg_seq अणु
	पूर्णांक reg;
	अचिन्हित अक्षर val, mask;
	पूर्णांक sleep;
पूर्ण;

काष्ठा em28xx_input अणु
	क्रमागत क्रमागत28xx_itype type;
	अचिन्हित पूर्णांक vmux;
	क्रमागत em28xx_amux amux;
	क्रमागत em28xx_aout aout;
	स्थिर काष्ठा em28xx_reg_seq *gpio;
पूर्ण;

#घोषणा INPUT(nr) (&em28xx_boards[dev->model].input[nr])

क्रमागत em28xx_decoder अणु
	EM28XX_NODECODER = 0,
	EM28XX_TVP5150,
	EM28XX_SAA711X,
पूर्ण;

क्रमागत em28xx_sensor अणु
	EM28XX_NOSENSOR = 0,
	EM28XX_MT9V011,
	EM28XX_MT9M001,
	EM28XX_MT9M111,
	EM28XX_OV2640,
पूर्ण;

क्रमागत em28xx_adecoder अणु
	EM28XX_NOADECODER = 0,
	EM28XX_TVAUDIO,
पूर्ण;

क्रमागत em28xx_led_role अणु
	EM28XX_LED_ANALOG_CAPTURING = 0,
	EM28XX_LED_DIGITAL_CAPTURING,
	EM28XX_LED_DIGITAL_CAPTURING_TS2,
	EM28XX_LED_ILLUMINATION,
	EM28XX_NUM_LED_ROLES, /* must be the last */
पूर्ण;

काष्ठा em28xx_led अणु
	क्रमागत em28xx_led_role role;
	u8 gpio_reg;
	u8 gpio_mask;
	bool inverted;
पूर्ण;

क्रमागत em28xx_button_role अणु
	EM28XX_BUTTON_SNAPSHOT = 0,
	EM28XX_BUTTON_ILLUMINATION,
	EM28XX_NUM_BUTTON_ROLES, /* must be the last */
पूर्ण;

काष्ठा em28xx_button अणु
	क्रमागत em28xx_button_role role;
	u8 reg_r;
	u8 reg_clearing;
	u8 mask;
	bool inverted;
पूर्ण;

काष्ठा em28xx_board अणु
	अक्षर *name;
	पूर्णांक vchannels;
	पूर्णांक tuner_type;
	पूर्णांक tuner_addr;
	अचिन्हित पूर्णांक def_i2c_bus;	/* Default I2C bus */

	/* i2c flags */
	अचिन्हित पूर्णांक tda9887_conf;

	/* GPIO sequences */
	स्थिर काष्ठा em28xx_reg_seq *dvb_gpio;
	स्थिर काष्ठा em28xx_reg_seq *suspend_gpio;
	स्थिर काष्ठा em28xx_reg_seq *tuner_gpio;
	स्थिर काष्ठा em28xx_reg_seq *mute_gpio;

	अचिन्हित पूर्णांक is_em2800:1;
	अचिन्हित पूर्णांक has_msp34xx:1;
	अचिन्हित पूर्णांक mts_firmware:1;
	अचिन्हित पूर्णांक max_range_640_480:1;
	अचिन्हित पूर्णांक has_dvb:1;
	अचिन्हित पूर्णांक has_dual_ts:1;
	अचिन्हित पूर्णांक is_webcam:1;
	अचिन्हित पूर्णांक valid:1;
	अचिन्हित पूर्णांक has_ir_i2c:1;

	अचिन्हित अक्षर xclk, i2c_speed;
	अचिन्हित अक्षर radio_addr;
	अचिन्हित लघु tvaudio_addr;

	क्रमागत em28xx_decoder decoder;
	क्रमागत em28xx_adecoder adecoder;

	काष्ठा em28xx_input       input[MAX_EM28XX_INPUT];
	काष्ठा em28xx_input	  radio;
	अक्षर			  *ir_codes;

	/* LEDs that need to be controlled explicitly */
	काष्ठा em28xx_led	  *leds;

	/* Buttons */
	स्थिर काष्ठा em28xx_button *buttons;
पूर्ण;

काष्ठा em28xx_eeprom अणु
	u8 id[4];			/* 1a eb 67 95 */
	__le16 venकरोr_ID;
	__le16 product_ID;

	__le16 chip_conf;

	__le16 board_conf;

	__le16 string1, string2, string3;

	u8 string_idx_table;
पूर्ण;

#घोषणा EM28XX_CAPTURE_STREAM_EN 1

/* em28xx extensions */
#घोषणा EM28XX_AUDIO   0x10
#घोषणा EM28XX_DVB     0x20
#घोषणा EM28XX_RC      0x30
#घोषणा EM28XX_V4L2    0x40

/* em28xx resource types (used क्रम res_get/res_lock etc */
#घोषणा EM28XX_RESOURCE_VIDEO 0x01
#घोषणा EM28XX_RESOURCE_VBI   0x02

काष्ठा em28xx_v4l2 अणु
	काष्ठा kref ref;
	काष्ठा em28xx *dev;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा video_device vdev;
	काष्ठा video_device vbi_dev;
	काष्ठा video_device radio_dev;

	/* Videobuf2 */
	काष्ठा vb2_queue vb_vidq;
	काष्ठा vb2_queue vb_vbiq;
	काष्ठा mutex vb_queue_lock;	/* Protects vb_vidq */
	काष्ठा mutex vb_vbi_queue_lock;	/* Protects vb_vbiq */

	u8 vinmode;
	u8 vinctl;

	/* Camera specअगरic fields */
	पूर्णांक sensor_xres;
	पूर्णांक sensor_yres;
	पूर्णांक sensor_xtal;

	पूर्णांक users;		/* user count क्रम exclusive use */
	पूर्णांक streaming_users;    /* number of actively streaming users */

	u32 frequency;		/* selected tuner frequency */

	काष्ठा em28xx_fmt *क्रमmat;
	v4l2_std_id norm;	/* selected tv norm */

	/* Progressive/पूर्णांकerlaced mode */
	bool progressive;
	पूर्णांक पूर्णांकerlaced_fieldmode; /* 1=पूर्णांकerlaced fields, 0=just top fields */
	/* FIXME: everything अन्यथा than पूर्णांकerlaced_fieldmode=1 करोesn't work */

	/* Frame properties */
	पूर्णांक width;		/* current frame width */
	पूर्णांक height;		/* current frame height */
	अचिन्हित पूर्णांक hscale;	/* horizontal scale factor (see datasheet) */
	अचिन्हित पूर्णांक vscale;	/* vertical scale factor (see datasheet) */
	अचिन्हित पूर्णांक vbi_width;
	अचिन्हित पूर्णांक vbi_height; /* lines per field */

	/* Capture state tracking */
	पूर्णांक capture_type;
	bool top_field;
	पूर्णांक vbi_पढ़ो;
	अचिन्हित पूर्णांक field_count;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_pad video_pad, vbi_pad;
	काष्ठा media_entity *decoder;
#पूर्ण_अगर
पूर्ण;

काष्ठा em28xx_audio अणु
	अक्षर name[50];
	अचिन्हित पूर्णांक num_urb;
	अक्षर **transfer_buffer;
	काष्ठा urb **urb;
	काष्ठा usb_device *udev;
	अचिन्हित पूर्णांक capture_transfer_करोne;
	काष्ठा snd_pcm_substream   *capture_pcm_substream;

	अचिन्हित पूर्णांक hwptr_करोne_capture;
	काष्ठा snd_card            *sndcard;

	माप_प्रकार period;

	पूर्णांक users;
	spinlock_t slock;		/* Protects काष्ठा em28xx_audio */

	/* Controls streaming */
	काष्ठा work_काष्ठा wq_trigger;	/* trigger to start/stop audio */
	atomic_t       stream_started;	/* stream should be running अगर true */
पूर्ण;

क्रमागत em28xx_i2c_algo_type अणु
	EM28XX_I2C_ALGO_EM28XX = 0,
	EM28XX_I2C_ALGO_EM2800,
	EM28XX_I2C_ALGO_EM25XX_BUS_B,
पूर्ण;

काष्ठा em28xx_i2c_bus अणु
	काष्ठा em28xx *dev;

	अचिन्हित पूर्णांक bus;
	क्रमागत em28xx_i2c_algo_type algo_type;
पूर्ण;

/* मुख्य device काष्ठा */
काष्ठा em28xx अणु
	काष्ठा kref ref;

	// Sub-module data
	काष्ठा em28xx_v4l2 *v4l2;
	काष्ठा em28xx_dvb *dvb;
	काष्ठा em28xx_audio adev;
	काष्ठा em28xx_IR *ir;

	// generic device properties
	पूर्णांक model;		// index in the device_data काष्ठा
	पूर्णांक devno;		// marks the number of this device
	क्रमागत em28xx_chip_id chip_id;

	अचिन्हित पूर्णांक is_em25xx:1;	// em25xx/em276x/7x/8x family bridge
	अचिन्हित पूर्णांक disconnected:1;	// device has been disconnected
	अचिन्हित पूर्णांक has_video:1;
	अचिन्हित पूर्णांक is_audio_only:1;
	अचिन्हित पूर्णांक is_webcam:1;
	अचिन्हित पूर्णांक has_msp34xx:1;
	अचिन्हित पूर्णांक i2c_speed:2;
	क्रमागत em28xx_पूर्णांक_audio_type पूर्णांक_audio_type;
	क्रमागत em28xx_usb_audio_type usb_audio_type;
	अचिन्हित अक्षर name[32];

	काष्ठा em28xx_board board;

	क्रमागत em28xx_sensor em28xx_sensor;	// camera specअगरic

	// Some older em28xx chips needs a रुकोing समय after writing
	अचिन्हित पूर्णांक रुको_after_ग_लिखो;

	काष्ठा list_head	devlist;

	u32 i2s_speed;		// I2S speed क्रम audio digital stream

	काष्ठा em28xx_audio_mode audio_mode;

	पूर्णांक tuner_type;		// type of the tuner

	// i2c i/o
	काष्ठा i2c_adapter i2c_adap[NUM_I2C_BUSES];
	काष्ठा i2c_client i2c_client[NUM_I2C_BUSES];
	काष्ठा em28xx_i2c_bus i2c_bus[NUM_I2C_BUSES];

	अचिन्हित अक्षर eeprom_addrwidth_16bit:1;
	अचिन्हित पूर्णांक def_i2c_bus;	// Default I2C bus
	अचिन्हित पूर्णांक cur_i2c_bus;	// Current I2C bus
	काष्ठा rt_mutex i2c_bus_lock;

	// video क्रम linux
	अचिन्हित पूर्णांक ctl_input;	// selected input
	अचिन्हित पूर्णांक ctl_ainput;// selected audio input
	अचिन्हित पूर्णांक ctl_aoutput;// selected audio output
	क्रमागत em28xx_amux amux_map[MAX_EM28XX_INPUT];

	पूर्णांक mute;
	पूर्णांक volume;

	अचिन्हित दीर्घ hash;	// eeprom hash - क्रम boards with generic ID
	अचिन्हित दीर्घ i2c_hash;	// i2c devicelist hash -
				// क्रम boards with generic ID

	काष्ठा work_काष्ठा         request_module_wk;

	// locks
	काष्ठा mutex lock;		/* protects em28xx काष्ठा */
	काष्ठा mutex ctrl_urb_lock;	/* protects urb_buf */

	// resources in use
	अचिन्हित पूर्णांक resources;

	// eeprom content
	u8 *eedata;
	u16 eedata_len;

	// Isoc control काष्ठा
	काष्ठा em28xx_dmaqueue vidq;
	काष्ठा em28xx_dmaqueue vbiq;
	काष्ठा em28xx_usb_ctl usb_ctl;

	spinlock_t slock; /* Protects em28xx video/vbi/dvb IRQ stream data */

	// usb transfer
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;	// the usb पूर्णांकerface
	u8 अगरnum;		// number of the asचिन्हित usb पूर्णांकerface
	u8 analog_ep_isoc;	// address of isoc endpoपूर्णांक क्रम analog
	u8 analog_ep_bulk;	// address of bulk endpoपूर्णांक क्रम analog
	u8 dvb_ep_isoc_ts2;	// address of isoc endpoपूर्णांक क्रम DVB TS2
	u8 dvb_ep_bulk_ts2;	// address of bulk endpoपूर्णांक क्रम DVB TS2
	u8 dvb_ep_isoc;		// address of isoc endpoपूर्णांक क्रम DVB
	u8 dvb_ep_bulk;		// address of bulk endpoपूर्णांक क्रम DVB
	पूर्णांक alt;		// alternate setting
	पूर्णांक max_pkt_size;	// max packet size of the selected ep at alt
	पूर्णांक packet_multiplier;	// multiplier क्रम wMaxPacketSize, used क्रम
				// URB buffer size definition
	पूर्णांक num_alt;		// number of alternative settings
	अचिन्हित पूर्णांक *alt_max_pkt_size_isoc; // array of isoc wMaxPacketSize
	अचिन्हित पूर्णांक analog_xfer_bulk:1;	// use bulk instead of isoc
						// transfers क्रम analog
	पूर्णांक dvb_alt_isoc;	// alternate setting क्रम DVB isoc transfers
	अचिन्हित पूर्णांक dvb_max_pkt_size_isoc;	// isoc max packet size of the
						// selected DVB ep at dvb_alt
	अचिन्हित पूर्णांक dvb_max_pkt_size_isoc_ts2;	// isoc max packet size of the
						// selected DVB ep at dvb_alt
	अचिन्हित पूर्णांक dvb_xfer_bulk:1;		// use bulk instead of isoc
						// transfers क्रम DVB
	अक्षर urb_buf[URB_MAX_CTRL_SIZE];	// urb control msg buffer

	// helper funcs that call usb_control_msg
	पूर्णांक (*em28xx_ग_लिखो_regs)(काष्ठा em28xx *dev, u16 reg,
				 अक्षर *buf, पूर्णांक len);
	पूर्णांक (*em28xx_पढ़ो_reg)(काष्ठा em28xx *dev, u16 reg);
	पूर्णांक (*em28xx_पढ़ो_reg_req_len)(काष्ठा em28xx *dev, u8 req, u16 reg,
				       अक्षर *buf, पूर्णांक len);
	पूर्णांक (*em28xx_ग_लिखो_regs_req)(काष्ठा em28xx *dev, u8 req, u16 reg,
				     अक्षर *buf, पूर्णांक len);
	पूर्णांक (*em28xx_पढ़ो_reg_req)(काष्ठा em28xx *dev, u8 req, u16 reg);

	क्रमागत em28xx_mode mode;

	// Button state polling
	काष्ठा delayed_work buttons_query_work;
	u8 button_polling_addresses[EM28XX_NUM_BUTTON_ADDRESSES_MAX];
	u8 button_polling_last_values[EM28XX_NUM_BUTTON_ADDRESSES_MAX];
	u8 num_button_polling_addresses;
	u16 button_polling_पूर्णांकerval; // [ms]
	// Snapshot button input device
	अक्षर snapshot_button_path[30];	// path of the input dev
	काष्ठा input_dev *sbutton_input_dev;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *media_dev;
	काष्ठा media_entity input_ent[MAX_EM28XX_INPUT];
	काष्ठा media_pad input_pad[MAX_EM28XX_INPUT];
#पूर्ण_अगर

	काष्ठा em28xx	*dev_next;
	पूर्णांक ts;
पूर्ण;

#घोषणा kref_to_dev(d) container_of(d, काष्ठा em28xx, ref)

काष्ठा em28xx_ops अणु
	काष्ठा list_head next;
	अक्षर *name;
	पूर्णांक id;
	पूर्णांक (*init)(काष्ठा em28xx *dev);
	पूर्णांक (*fini)(काष्ठा em28xx *dev);
	पूर्णांक (*suspend)(काष्ठा em28xx *dev);
	पूर्णांक (*resume)(काष्ठा em28xx *dev);
पूर्ण;

/* Provided by em28xx-i2c.c */
व्योम em28xx_करो_i2c_scan(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus);
पूर्णांक  em28xx_i2c_रेजिस्टर(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus,
			 क्रमागत em28xx_i2c_algo_type algo_type);
पूर्णांक  em28xx_i2c_unरेजिस्टर(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus);

/* Provided by em28xx-core.c */
पूर्णांक em28xx_पढ़ो_reg_req_len(काष्ठा em28xx *dev, u8 req, u16 reg,
			    अक्षर *buf, पूर्णांक len);
पूर्णांक em28xx_पढ़ो_reg_req(काष्ठा em28xx *dev, u8 req, u16 reg);
पूर्णांक em28xx_पढ़ो_reg(काष्ठा em28xx *dev, u16 reg);
पूर्णांक em28xx_ग_लिखो_regs_req(काष्ठा em28xx *dev, u8 req, u16 reg, अक्षर *buf,
			  पूर्णांक len);
पूर्णांक em28xx_ग_लिखो_regs(काष्ठा em28xx *dev, u16 reg, अक्षर *buf, पूर्णांक len);
पूर्णांक em28xx_ग_लिखो_reg(काष्ठा em28xx *dev, u16 reg, u8 val);
पूर्णांक em28xx_ग_लिखो_reg_bits(काष्ठा em28xx *dev, u16 reg, u8 val,
			  u8 biपंचांगask);
पूर्णांक em28xx_toggle_reg_bits(काष्ठा em28xx *dev, u16 reg, u8 biपंचांगask);

पूर्णांक em28xx_पढ़ो_ac97(काष्ठा em28xx *dev, u8 reg);
पूर्णांक em28xx_ग_लिखो_ac97(काष्ठा em28xx *dev, u8 reg, u16 val);

पूर्णांक em28xx_audio_analog_set(काष्ठा em28xx *dev);
पूर्णांक em28xx_audio_setup(काष्ठा em28xx *dev);

स्थिर काष्ठा em28xx_led *em28xx_find_led(काष्ठा em28xx *dev,
					 क्रमागत em28xx_led_role role);
पूर्णांक em28xx_capture_start(काष्ठा em28xx *dev, पूर्णांक start);
पूर्णांक em28xx_alloc_urbs(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode, पूर्णांक xfer_bulk,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size, पूर्णांक packet_multiplier);
पूर्णांक em28xx_init_usb_xfer(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode,
			 पूर्णांक xfer_bulk,
			 पूर्णांक num_bufs, पूर्णांक max_pkt_size, पूर्णांक packet_multiplier,
			 पूर्णांक (*urb_data_copy)
					(काष्ठा em28xx *dev, काष्ठा urb *urb));
व्योम em28xx_uninit_usb_xfer(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode);
व्योम em28xx_stop_urbs(काष्ठा em28xx *dev);
पूर्णांक em28xx_set_mode(काष्ठा em28xx *dev, क्रमागत em28xx_mode set_mode);
पूर्णांक em28xx_gpio_set(काष्ठा em28xx *dev, स्थिर काष्ठा em28xx_reg_seq *gpio);
पूर्णांक em28xx_रेजिस्टर_extension(काष्ठा em28xx_ops *dev);
व्योम em28xx_unरेजिस्टर_extension(काष्ठा em28xx_ops *dev);
व्योम em28xx_init_extension(काष्ठा em28xx *dev);
व्योम em28xx_बंद_extension(काष्ठा em28xx *dev);
पूर्णांक em28xx_suspend_extension(काष्ठा em28xx *dev);
पूर्णांक em28xx_resume_extension(काष्ठा em28xx *dev);

/* Provided by em28xx-cards.c */
बाह्य स्थिर काष्ठा em28xx_board em28xx_boards[];
बाह्य काष्ठा usb_device_id em28xx_id_table[];
पूर्णांक em28xx_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg);
व्योम em28xx_setup_xc3028(काष्ठा em28xx *dev, काष्ठा xc2028_ctrl *ctl);
व्योम em28xx_मुक्त_device(काष्ठा kref *ref);

/* Provided by em28xx-camera.c */
पूर्णांक em28xx_detect_sensor(काष्ठा em28xx *dev);
पूर्णांक em28xx_init_camera(काष्ठा em28xx *dev);

#पूर्ण_अगर
