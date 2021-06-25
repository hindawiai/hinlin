<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <media/i2c/saa7115.h>
#समावेश <media/tuner.h>
#समावेश <media/i2c/uda1342.h>

#समावेश "go7007-priv.h"

अटल अचिन्हित पूर्णांक assume_endura;
module_param(assume_endura, पूर्णांक, 0644);
MODULE_PARM_DESC(assume_endura,
			"when probing fails, hardware is a Pelco Endura");

/* #घोषणा GO7007_I2C_DEBUG */ /* क्रम debugging the EZ-USB I2C adapter */

#घोषणा	HPI_STATUS_ADDR	0xFFF4
#घोषणा	INT_PARAM_ADDR	0xFFF6
#घोषणा	INT_INDEX_ADDR	0xFFF8

/*
 * Pipes on EZ-USB पूर्णांकerface:
 *	0 snd - Control
 *	0 rcv - Control
 *	2 snd - Download firmware (control)
 *	4 rcv - Read Interrupt (पूर्णांकerrupt)
 *	6 rcv - Read Video (bulk)
 *	8 rcv - Read Audio (bulk)
 */

#घोषणा GO7007_USB_EZUSB		(1<<0)
#घोषणा GO7007_USB_EZUSB_I2C		(1<<1)

काष्ठा go7007_usb_board अणु
	अचिन्हित पूर्णांक flags;
	काष्ठा go7007_board_info मुख्य_info;
पूर्ण;

काष्ठा go7007_usb अणु
	स्थिर काष्ठा go7007_usb_board *board;
	काष्ठा mutex i2c_lock;
	काष्ठा usb_device *usbdev;
	काष्ठा urb *video_urbs[8];
	काष्ठा urb *audio_urbs[8];
	काष्ठा urb *पूर्णांकr_urb;
पूर्ण;

/*********************** Product specअगरication data ***********************/

अटल स्थिर काष्ठा go7007_usb_board board_matrix_ii = अणु
	.flags		= GO7007_USB_EZUSB,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_VALID_ENABLE |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_SAA7115 |
					GO7007_SENSOR_VBI |
					GO7007_SENSOR_SCALING,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "saa7115",
				.addr	= 0x20,
				.is_video = 1,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 0,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 9,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
		.video_config	= SAA7115_IDQ_IS_DEFAULT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_matrix_reload = अणु
	.flags		= GO7007_USB_EZUSB,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "saa7113",
				.addr	= 0x25,
				.is_video = 1,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 0,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 9,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
		.video_config	= SAA7115_IDQ_IS_DEFAULT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_star_trek = अणु
	.flags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO, /* |
					GO7007_BOARD_HAS_TUNER, */
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_VALID_ENABLE |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_SAA7115 |
					GO7007_SENSOR_VBI |
					GO7007_SENSOR_SCALING,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WORD_16,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "saa7115",
				.addr	= 0x20,
				.is_video = 1,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
		/*	अणु
		 *		.video_input	= 3,
		 *		.audio_index	= AUDIO_TUNER,
		 *		.name		= "Tuner",
		 *	पूर्ण,
		 */
			अणु
				.video_input	= 1,
			/*	.audio_index	= AUDIO_EXTERN, */
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 8,
			/*	.audio_index	= AUDIO_EXTERN, */
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
		.video_config	= SAA7115_IDQ_IS_DEFAULT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_px_tv402u = अणु
	.flags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_HAS_TUNER,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_VALID_ENABLE |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_SAA7115 |
					GO7007_SENSOR_VBI |
					GO7007_SENSOR_SCALING,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WORD_16,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.num_i2c_devs	 = 5,
		.i2c_devs	 = अणु
			अणु
				.type	= "saa7115",
				.addr	= 0x20,
				.is_video = 1,
			पूर्ण,
			अणु
				.type	= "uda1342",
				.addr	= 0x1a,
				.is_audio = 1,
			पूर्ण,
			अणु
				.type	= "tuner",
				.addr	= 0x60,
			पूर्ण,
			अणु
				.type	= "tuner",
				.addr	= 0x43,
			पूर्ण,
			अणु
				.type	= "sony-btf-mpx",
				.addr	= 0x44,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 3,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 3,
				.audio_index	= 0,
				.name		= "Tuner",
			पूर्ण,
			अणु
				.video_input	= 1,
				.audio_index	= 1,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 8,
				.audio_index	= 1,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
		.video_config	= SAA7115_IDQ_IS_DEFAULT,
		.num_aud_inमाला_दो	 = 2,
		.aud_inमाला_दो	 = अणु
			अणु
				.audio_input	= UDA1342_IN2,
				.name		= "Tuner",
			पूर्ण,
			अणु
				.audio_input	= UDA1342_IN1,
				.name		= "Line In",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_xmen = अणु
	.flags		= 0,
	.मुख्य_info	= अणु
		.flags		  = GO7007_BOARD_USE_ONBOARD_I2C,
		.hpi_buffer_cap   = 0,
		.sensor_flags	  = GO7007_SENSOR_VREF_POLAR,
		.sensor_width	  = 320,
		.sensor_height	  = 240,
		.sensor_framerate = 30030,
		.audio_flags	  = GO7007_AUDIO_ONE_CHANNEL |
					GO7007_AUDIO_I2S_MODE_3 |
					GO7007_AUDIO_WORD_14 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_BCLK_POLAR |
					GO7007_AUDIO_OKI_MODE,
		.audio_rate	  = 8000,
		.audio_bclk_भाग	  = 48,
		.audio_मुख्य_भाग	  = 1,
		.num_i2c_devs	  = 1,
		.i2c_devs	  = अणु
			अणु
				.type	= "ov7640",
				.addr	= 0x21,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	  = 1,
		.inमाला_दो		  = अणु
			अणु
				.name		= "Camera",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_matrix_revolution = अणु
	.flags		= GO7007_USB_EZUSB,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "tw9903",
				.is_video = 1,
				.addr	= 0x44,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 2,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 8,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

#अगर 0
अटल स्थिर काष्ठा go7007_usb_board board_lअगरeview_lr192 = अणु
	.flags		= GO7007_USB_EZUSB,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_VALID_ENABLE |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_VBI |
					GO7007_SENSOR_SCALING,
		.num_i2c_devs	 = 0,
		.num_inमाला_दो	 = 1,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 0,
				.name		= "Composite",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा go7007_usb_board board_endura = अणु
	.flags		= 0,
	.मुख्य_info	= अणु
		.flags		 = 0,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 8000,
		.audio_bclk_भाग	 = 48,
		.audio_मुख्य_भाग	 = 8,
		.hpi_buffer_cap  = 0,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV,
		.sensor_h_offset = 8,
		.num_i2c_devs	 = 0,
		.num_inमाला_दो	 = 1,
		.inमाला_दो		 = अणु
			अणु
				.name		= "Camera",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_adlink_mpg24 = अणु
	.flags		= 0,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 0,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "tw2804",
				.addr	= 0x00, /* yes, really */
				.flags  = I2C_CLIENT_TEN,
				.is_video = 1,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 1,
		.inमाला_दो		 = अणु
			अणु
				.name		= "Composite",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_sensoray_2250 = अणु
	.flags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.मुख्य_info	= अणु
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.flags		 = GO7007_BOARD_HAS_AUDIO,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "s2250",
				.addr	= 0x43,
				.is_video = 1,
				.is_audio = 1,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 0,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 1,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
		.num_aud_inमाला_दो	 = 3,
		.aud_inमाला_दो	 = अणु
			अणु
				.audio_input	= 0,
				.name		= "Line In",
			पूर्ण,
			अणु
				.audio_input	= 1,
				.name		= "Mic",
			पूर्ण,
			अणु
				.audio_input	= 2,
				.name		= "Mic Boost",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा go7007_usb_board board_ads_usbav_709 = अणु
	.flags		= GO7007_USB_EZUSB,
	.मुख्य_info	= अणु
		.flags		 = GO7007_BOARD_HAS_AUDIO |
					GO7007_BOARD_USE_ONBOARD_I2C,
		.audio_flags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTER |
					GO7007_AUDIO_WORD_16,
		.audio_rate	 = 48000,
		.audio_bclk_भाग	 = 8,
		.audio_मुख्य_भाग	 = 2,
		.hpi_buffer_cap  = 7,
		.sensor_flags	 = GO7007_SENSOR_656 |
					GO7007_SENSOR_TV |
					GO7007_SENSOR_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = अणु
			अणु
				.type	= "tw9906",
				.is_video = 1,
				.addr	= 0x44,
			पूर्ण,
		पूर्ण,
		.num_inमाला_दो	 = 2,
		.inमाला_दो		 = अणु
			अणु
				.video_input	= 0,
				.name		= "Composite",
			पूर्ण,
			अणु
				.video_input	= 10,
				.name		= "S-Video",
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id go7007_usb_id_table[] = अणु
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x200,   /* Revision number of XMen */
		.bcdDevice_hi	= 0x200,
		.bInterfaceClass	= 255,
		.bInterfaceSubClass	= 0,
		.bInterfaceProtocol	= 255,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_XMEN,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x202,   /* Revision number of Matrix II */
		.bcdDevice_hi	= 0x202,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_MATRIX_II,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x204,   /* Revision number of Matrix */
		.bcdDevice_hi	= 0x204,   /*     Reloaded */
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_MATRIX_RELOAD,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x205,   /* Revision number of XMen-II */
		.bcdDevice_hi	= 0x205,
		.bInterfaceClass	= 255,
		.bInterfaceSubClass	= 0,
		.bInterfaceProtocol	= 255,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_XMEN_II,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x208,   /* Revision number of Star Trek */
		.bcdDevice_hi	= 0x208,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_STAR_TREK,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x209,   /* Revision number of XMen-III */
		.bcdDevice_hi	= 0x209,
		.bInterfaceClass	= 255,
		.bInterfaceSubClass	= 0,
		.bInterfaceProtocol	= 255,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_XMEN_III,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x0eb1,  /* Venकरोr ID of WIS Technologies */
		.idProduct	= 0x7007,  /* Product ID of GO7007SB chip */
		.bcdDevice_lo	= 0x210,   /* Revision number of Matrix */
		.bcdDevice_hi	= 0x210,   /*     Revolution */
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_MATRIX_REV,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x093b,  /* Venकरोr ID of Plextor */
		.idProduct	= 0xa102,  /* Product ID of M402U */
		.bcdDevice_lo	= 0x1,	   /* revision number of Blueberry */
		.bcdDevice_hi	= 0x1,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_PX_M402U,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x093b,  /* Venकरोr ID of Plextor */
		.idProduct	= 0xa104,  /* Product ID of TV402U */
		.bcdDevice_lo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_PX_TV402U,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x10fd,  /* Venकरोr ID of Anubis Electronics */
		.idProduct	= 0xde00,  /* Product ID of Lअगरeview LR192 */
		.bcdDevice_lo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_LIFEVIEW_LR192,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x1943,  /* Venकरोr ID Sensoray */
		.idProduct	= 0x2250,  /* Product ID of 2250/2251 */
		.bcdDevice_lo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_SENSORAY_2250,
	पूर्ण,
	अणु
		.match_flags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,
		.idVenकरोr	= 0x06e1,  /* Venकरोr ID of ADS Technologies */
		.idProduct	= 0x0709,  /* Product ID of DVD Xpress DX2 */
		.bcdDevice_lo	= 0x204,
		.bcdDevice_hi	= 0x204,
		.driver_info	= (kernel_uदीर्घ_t)GO7007_BOARDID_ADS_USBAV_709,
	पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, go7007_usb_id_table);

/********************* Driver क्रम EZ-USB HPI पूर्णांकerface *********************/

अटल पूर्णांक go7007_usb_venकरोr_request(काष्ठा go7007 *go, पूर्णांक request,
		पूर्णांक value, पूर्णांक index, व्योम *transfer_buffer, पूर्णांक length, पूर्णांक in)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक समयout = 5000;

	अगर (in) अणु
		वापस usb_control_msg(usb->usbdev,
				usb_rcvctrlpipe(usb->usbdev, 0), request,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
				value, index, transfer_buffer, length, समयout);
	पूर्ण अन्यथा अणु
		वापस usb_control_msg(usb->usbdev,
				usb_sndctrlpipe(usb->usbdev, 0), request,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				value, index, transfer_buffer, length, समयout);
	पूर्ण
पूर्ण

अटल पूर्णांक go7007_usb_पूर्णांकerface_reset(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	u16 पूर्णांकr_val, पूर्णांकr_data;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -1;
	/* Reset encoder */
	अगर (go7007_ग_लिखो_पूर्णांकerrupt(go, 0x0001, 0x0001) < 0)
		वापस -1;
	msleep(100);

	अगर (usb->board->flags & GO7007_USB_EZUSB) अणु
		/* Reset buffer in EZ-USB */
		pr_debug("resetting EZ-USB buffers\n");
		अगर (go7007_usb_venकरोr_request(go, 0x10, 0, 0, शून्य, 0, 0) < 0 ||
		    go7007_usb_venकरोr_request(go, 0x10, 0, 0, शून्य, 0, 0) < 0)
			वापस -1;

		/* Reset encoder again */
		अगर (go7007_ग_लिखो_पूर्णांकerrupt(go, 0x0001, 0x0001) < 0)
			वापस -1;
		msleep(100);
	पूर्ण

	/* Wait क्रम an पूर्णांकerrupt to indicate successful hardware reset */
	अगर (go7007_पढ़ो_पूर्णांकerrupt(go, &पूर्णांकr_val, &पूर्णांकr_data) < 0 ||
			(पूर्णांकr_val & ~0x1) != 0x55aa) अणु
		dev_err(go->dev, "unable to reset the USB interface\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_usb_ezusb_ग_लिखो_पूर्णांकerrupt(काष्ठा go7007 *go,
						पूर्णांक addr, पूर्णांक data)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक i, r;
	u16 status_reg = 0;
	पूर्णांक समयout = 500;

	pr_debug("WriteInterrupt: %04x %04x\n", addr, data);

	क्रम (i = 0; i < 100; ++i) अणु
		r = usb_control_msg(usb->usbdev,
				usb_rcvctrlpipe(usb->usbdev, 0), 0x14,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
				0, HPI_STATUS_ADDR, go->usb_buf,
				माप(status_reg), समयout);
		अगर (r < 0)
			अवरोध;
		status_reg = le16_to_cpu(*((__le16 *)go->usb_buf));
		अगर (!(status_reg & 0x0010))
			अवरोध;
		msleep(10);
	पूर्ण
	अगर (r < 0)
		जाओ ग_लिखो_पूर्णांक_error;
	अगर (i == 100) अणु
		dev_err(go->dev, "device is hung, status reg = 0x%04x\n", status_reg);
		वापस -1;
	पूर्ण
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 0), 0x12,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE, data,
			INT_PARAM_ADDR, शून्य, 0, समयout);
	अगर (r < 0)
		जाओ ग_लिखो_पूर्णांक_error;
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 0),
			0x12, USB_TYPE_VENDOR | USB_RECIP_DEVICE, addr,
			INT_INDEX_ADDR, शून्य, 0, समयout);
	अगर (r < 0)
		जाओ ग_लिखो_पूर्णांक_error;
	वापस 0;

ग_लिखो_पूर्णांक_error:
	dev_err(go->dev, "error in WriteInterrupt: %d\n", r);
	वापस r;
पूर्ण

अटल पूर्णांक go7007_usb_onboard_ग_लिखो_पूर्णांकerrupt(काष्ठा go7007 *go,
						पूर्णांक addr, पूर्णांक data)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक r;
	पूर्णांक समयout = 500;

	pr_debug("WriteInterrupt: %04x %04x\n", addr, data);

	go->usb_buf[0] = data & 0xff;
	go->usb_buf[1] = data >> 8;
	go->usb_buf[2] = addr & 0xff;
	go->usb_buf[3] = addr >> 8;
	go->usb_buf[4] = go->usb_buf[5] = go->usb_buf[6] = go->usb_buf[7] = 0;
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 2), 0x00,
			USB_TYPE_VENDOR | USB_RECIP_ENDPOINT, 0x55aa,
			0xf0f0, go->usb_buf, 8, समयout);
	अगर (r < 0) अणु
		dev_err(go->dev, "error in WriteInterrupt: %d\n", r);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम go7007_usb_पढ़ोपूर्णांकerrupt_complete(काष्ठा urb *urb)
अणु
	काष्ठा go7007 *go = (काष्ठा go7007 *)urb->context;
	__le16 *regs = (__le16 *)urb->transfer_buffer;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		अगर (status != -ESHUTDOWN &&
				go->status != STATUS_SHUTDOWN) अणु
			dev_err(go->dev, "error in read interrupt: %d\n", urb->status);
		पूर्ण अन्यथा अणु
			wake_up(&go->पूर्णांकerrupt_रुकोq);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (urb->actual_length != urb->transfer_buffer_length) अणु
		dev_err(go->dev, "short read in interrupt pipe!\n");
	पूर्ण अन्यथा अणु
		go->पूर्णांकerrupt_available = 1;
		go->पूर्णांकerrupt_data = __le16_to_cpu(regs[0]);
		go->पूर्णांकerrupt_value = __le16_to_cpu(regs[1]);
		pr_debug("ReadInterrupt: %04x %04x\n",
				go->पूर्णांकerrupt_value, go->पूर्णांकerrupt_data);
	पूर्ण

	wake_up(&go->पूर्णांकerrupt_रुकोq);
पूर्ण

अटल पूर्णांक go7007_usb_पढ़ो_पूर्णांकerrupt(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक r;

	r = usb_submit_urb(usb->पूर्णांकr_urb, GFP_KERNEL);
	अगर (r < 0) अणु
		dev_err(go->dev, "unable to submit interrupt urb: %d\n", r);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम go7007_usb_पढ़ो_video_pipe_complete(काष्ठा urb *urb)
अणु
	काष्ठा go7007 *go = (काष्ठा go7007 *)urb->context;
	पूर्णांक r, status = urb->status;

	अगर (!vb2_is_streaming(&go->vidq)) अणु
		wake_up_पूर्णांकerruptible(&go->frame_रुकोq);
		वापस;
	पूर्ण
	अगर (status) अणु
		dev_err(go->dev, "error in video pipe: %d\n", status);
		वापस;
	पूर्ण
	अगर (urb->actual_length != urb->transfer_buffer_length) अणु
		dev_err(go->dev, "short read in video pipe!\n");
		वापस;
	पूर्ण
	go7007_parse_video_stream(go, urb->transfer_buffer, urb->actual_length);
	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r < 0)
		dev_err(go->dev, "error in video pipe: %d\n", r);
पूर्ण

अटल व्योम go7007_usb_पढ़ो_audio_pipe_complete(काष्ठा urb *urb)
अणु
	काष्ठा go7007 *go = (काष्ठा go7007 *)urb->context;
	पूर्णांक r, status = urb->status;

	अगर (!vb2_is_streaming(&go->vidq))
		वापस;
	अगर (status) अणु
		dev_err(go->dev, "error in audio pipe: %d\n",
			status);
		वापस;
	पूर्ण
	अगर (urb->actual_length != urb->transfer_buffer_length) अणु
		dev_err(go->dev, "short read in audio pipe!\n");
		वापस;
	पूर्ण
	अगर (go->audio_deliver != शून्य)
		go->audio_deliver(go, urb->transfer_buffer, urb->actual_length);
	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r < 0)
		dev_err(go->dev, "error in audio pipe: %d\n", r);
पूर्ण

अटल पूर्णांक go7007_usb_stream_start(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक i, r;

	क्रम (i = 0; i < 8; ++i) अणु
		r = usb_submit_urb(usb->video_urbs[i], GFP_KERNEL);
		अगर (r < 0) अणु
			dev_err(go->dev, "error submitting video urb %d: %d\n", i, r);
			जाओ video_submit_failed;
		पूर्ण
	पूर्ण
	अगर (!go->audio_enabled)
		वापस 0;

	क्रम (i = 0; i < 8; ++i) अणु
		r = usb_submit_urb(usb->audio_urbs[i], GFP_KERNEL);
		अगर (r < 0) अणु
			dev_err(go->dev, "error submitting audio urb %d: %d\n", i, r);
			जाओ audio_submit_failed;
		पूर्ण
	पूर्ण
	वापस 0;

audio_submit_failed:
	क्रम (i = 0; i < 7; ++i)
		usb_समाप्त_urb(usb->audio_urbs[i]);
video_submit_failed:
	क्रम (i = 0; i < 8; ++i)
		usb_समाप्त_urb(usb->video_urbs[i]);
	वापस -1;
पूर्ण

अटल पूर्णांक go7007_usb_stream_stop(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक i;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस 0;
	क्रम (i = 0; i < 8; ++i)
		usb_समाप्त_urb(usb->video_urbs[i]);
	अगर (go->audio_enabled)
		क्रम (i = 0; i < 8; ++i)
			usb_समाप्त_urb(usb->audio_urbs[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_usb_send_firmware(काष्ठा go7007 *go, u8 *data, पूर्णांक len)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक transferred, pipe;
	पूर्णांक समयout = 500;

	pr_debug("DownloadBuffer sending %d bytes\n", len);

	अगर (usb->board->flags & GO7007_USB_EZUSB)
		pipe = usb_sndbulkpipe(usb->usbdev, 2);
	अन्यथा
		pipe = usb_sndbulkpipe(usb->usbdev, 3);

	वापस usb_bulk_msg(usb->usbdev, pipe, data, len,
					&transferred, समयout);
पूर्ण

अटल व्योम go7007_usb_release(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	काष्ठा urb *vurb, *aurb;
	पूर्णांक i;

	अगर (usb->पूर्णांकr_urb) अणु
		usb_समाप्त_urb(usb->पूर्णांकr_urb);
		kमुक्त(usb->पूर्णांकr_urb->transfer_buffer);
		usb_मुक्त_urb(usb->पूर्णांकr_urb);
	पूर्ण

	/* Free USB-related काष्ठाs */
	क्रम (i = 0; i < 8; ++i) अणु
		vurb = usb->video_urbs[i];
		अगर (vurb) अणु
			usb_समाप्त_urb(vurb);
			kमुक्त(vurb->transfer_buffer);
			usb_मुक्त_urb(vurb);
		पूर्ण
		aurb = usb->audio_urbs[i];
		अगर (aurb) अणु
			usb_समाप्त_urb(aurb);
			kमुक्त(aurb->transfer_buffer);
			usb_मुक्त_urb(aurb);
		पूर्ण
	पूर्ण

	kमुक्त(go->hpi_context);
पूर्ण

अटल स्थिर काष्ठा go7007_hpi_ops go7007_usb_ezusb_hpi_ops = अणु
	.पूर्णांकerface_reset	= go7007_usb_पूर्णांकerface_reset,
	.ग_लिखो_पूर्णांकerrupt	= go7007_usb_ezusb_ग_लिखो_पूर्णांकerrupt,
	.पढ़ो_पूर्णांकerrupt		= go7007_usb_पढ़ो_पूर्णांकerrupt,
	.stream_start		= go7007_usb_stream_start,
	.stream_stop		= go7007_usb_stream_stop,
	.send_firmware		= go7007_usb_send_firmware,
	.release		= go7007_usb_release,
पूर्ण;

अटल स्थिर काष्ठा go7007_hpi_ops go7007_usb_onboard_hpi_ops = अणु
	.पूर्णांकerface_reset	= go7007_usb_पूर्णांकerface_reset,
	.ग_लिखो_पूर्णांकerrupt	= go7007_usb_onboard_ग_लिखो_पूर्णांकerrupt,
	.पढ़ो_पूर्णांकerrupt		= go7007_usb_पढ़ो_पूर्णांकerrupt,
	.stream_start		= go7007_usb_stream_start,
	.stream_stop		= go7007_usb_stream_stop,
	.send_firmware		= go7007_usb_send_firmware,
	.release		= go7007_usb_release,
पूर्ण;

/********************* Driver क्रम EZ-USB I2C adapter *********************/

अटल पूर्णांक go7007_usb_i2c_master_xfer(काष्ठा i2c_adapter *adapter,
					काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(adapter);
	काष्ठा go7007_usb *usb = go->hpi_context;
	u8 *buf = go->usb_buf;
	पूर्णांक buf_len, i;
	पूर्णांक ret = -EIO;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -ENODEV;

	mutex_lock(&usb->i2c_lock);

	क्रम (i = 0; i < num; ++i) अणु
		/* The hardware command is "ग_लिखो some bytes then पढ़ो some
		 * bytes", so we try to coalesce a ग_लिखो followed by a पढ़ो
		 * पूर्णांकo a single USB transaction */
		अगर (i + 1 < num && msgs[i].addr == msgs[i + 1].addr &&
				!(msgs[i].flags & I2C_M_RD) &&
				(msgs[i + 1].flags & I2C_M_RD)) अणु
#अगर_घोषित GO7007_I2C_DEBUG
			pr_debug("i2c write/read %d/%d bytes on %02x\n",
				msgs[i].len, msgs[i + 1].len, msgs[i].addr);
#पूर्ण_अगर
			buf[0] = 0x01;
			buf[1] = msgs[i].len + 1;
			buf[2] = msgs[i].addr << 1;
			स_नकल(&buf[3], msgs[i].buf, msgs[i].len);
			buf_len = msgs[i].len + 3;
			buf[buf_len++] = msgs[++i].len;
		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
#अगर_घोषित GO7007_I2C_DEBUG
			pr_debug("i2c read %d bytes on %02x\n",
					msgs[i].len, msgs[i].addr);
#पूर्ण_अगर
			buf[0] = 0x01;
			buf[1] = 1;
			buf[2] = msgs[i].addr << 1;
			buf[3] = msgs[i].len;
			buf_len = 4;
		पूर्ण अन्यथा अणु
#अगर_घोषित GO7007_I2C_DEBUG
			pr_debug("i2c write %d bytes on %02x\n",
					msgs[i].len, msgs[i].addr);
#पूर्ण_अगर
			buf[0] = 0x00;
			buf[1] = msgs[i].len + 1;
			buf[2] = msgs[i].addr << 1;
			स_नकल(&buf[3], msgs[i].buf, msgs[i].len);
			buf_len = msgs[i].len + 3;
			buf[buf_len++] = 0;
		पूर्ण
		अगर (go7007_usb_venकरोr_request(go, 0x24, 0, 0,
						buf, buf_len, 0) < 0)
			जाओ i2c_करोne;
		अगर (msgs[i].flags & I2C_M_RD) अणु
			स_रखो(buf, 0, msgs[i].len + 1);
			अगर (go7007_usb_venकरोr_request(go, 0x25, 0, 0, buf,
						msgs[i].len + 1, 1) < 0)
				जाओ i2c_करोne;
			स_नकल(msgs[i].buf, buf + 1, msgs[i].len);
		पूर्ण
	पूर्ण
	ret = num;

i2c_करोne:
	mutex_unlock(&usb->i2c_lock);
	वापस ret;
पूर्ण

अटल u32 go7007_usb_functionality(काष्ठा i2c_adapter *adapter)
अणु
	/* No errors are reported by the hardware, so we करोn't bother
	 * supporting quick ग_लिखोs to aव्योम confusing probing */
	वापस (I2C_FUNC_SMBUS_EMUL) & ~I2C_FUNC_SMBUS_QUICK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm go7007_usb_algo = अणु
	.master_xfer	= go7007_usb_i2c_master_xfer,
	.functionality	= go7007_usb_functionality,
पूर्ण;

अटल काष्ठा i2c_adapter go7007_usb_adap_templ = अणु
	.owner			= THIS_MODULE,
	.name			= "WIS GO7007SB EZ-USB",
	.algo			= &go7007_usb_algo,
पूर्ण;

/********************* USB add/हटाओ functions *********************/

अटल पूर्णांक go7007_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा go7007 *go;
	काष्ठा go7007_usb *usb;
	स्थिर काष्ठा go7007_usb_board *board;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अचिन्हित num_i2c_devs;
	अक्षर *name;
	पूर्णांक video_pipe, i, v_urb_len;

	pr_debug("probing new GO7007 USB board\n");

	चयन (id->driver_info) अणु
	हाल GO7007_BOARDID_MATRIX_II:
		name = "WIS Matrix II or compatible";
		board = &board_matrix_ii;
		अवरोध;
	हाल GO7007_BOARDID_MATRIX_RELOAD:
		name = "WIS Matrix Reloaded or compatible";
		board = &board_matrix_reload;
		अवरोध;
	हाल GO7007_BOARDID_MATRIX_REV:
		name = "WIS Matrix Revolution or compatible";
		board = &board_matrix_revolution;
		अवरोध;
	हाल GO7007_BOARDID_STAR_TREK:
		name = "WIS Star Trek or compatible";
		board = &board_star_trek;
		अवरोध;
	हाल GO7007_BOARDID_XMEN:
		name = "WIS XMen or compatible";
		board = &board_xmen;
		अवरोध;
	हाल GO7007_BOARDID_XMEN_II:
		name = "WIS XMen II or compatible";
		board = &board_xmen;
		अवरोध;
	हाल GO7007_BOARDID_XMEN_III:
		name = "WIS XMen III or compatible";
		board = &board_xmen;
		अवरोध;
	हाल GO7007_BOARDID_PX_M402U:
		name = "Plextor PX-M402U";
		board = &board_matrix_ii;
		अवरोध;
	हाल GO7007_BOARDID_PX_TV402U:
		name = "Plextor PX-TV402U (unknown tuner)";
		board = &board_px_tv402u;
		अवरोध;
	हाल GO7007_BOARDID_LIFEVIEW_LR192:
		dev_err(&पूर्णांकf->dev, "The Lifeview TV Walker Ultra is not supported. Sorry!\n");
		वापस -ENODEV;
#अगर 0
		name = "Lifeview TV Walker Ultra";
		board = &board_lअगरeview_lr192;
#पूर्ण_अगर
		अवरोध;
	हाल GO7007_BOARDID_SENSORAY_2250:
		dev_info(&पूर्णांकf->dev, "Sensoray 2250 found\n");
		name = "Sensoray 2250/2251";
		board = &board_sensoray_2250;
		अवरोध;
	हाल GO7007_BOARDID_ADS_USBAV_709:
		name = "ADS Tech DVD Xpress DX2";
		board = &board_ads_usbav_709;
		अवरोध;
	शेष:
		dev_err(&पूर्णांकf->dev, "unknown board ID %d!\n",
				(अचिन्हित पूर्णांक)id->driver_info);
		वापस -ENODEV;
	पूर्ण

	go = go7007_alloc(&board->मुख्य_info, &पूर्णांकf->dev);
	अगर (go == शून्य)
		वापस -ENOMEM;

	usb = kzalloc(माप(काष्ठा go7007_usb), GFP_KERNEL);
	अगर (usb == शून्य) अणु
		kमुक्त(go);
		वापस -ENOMEM;
	पूर्ण

	usb->board = board;
	usb->usbdev = usbdev;
	usb_make_path(usbdev, go->bus_info, माप(go->bus_info));
	go->board_id = id->driver_info;
	strscpy(go->name, name, माप(go->name));
	अगर (board->flags & GO7007_USB_EZUSB)
		go->hpi_ops = &go7007_usb_ezusb_hpi_ops;
	अन्यथा
		go->hpi_ops = &go7007_usb_onboard_hpi_ops;
	go->hpi_context = usb;

	ep = usb->usbdev->ep_in[4];
	अगर (!ep)
		वापस -ENODEV;

	/* Allocate the URB and buffer क्रम receiving incoming पूर्णांकerrupts */
	usb->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (usb->पूर्णांकr_urb == शून्य)
		जाओ allocfail;
	usb->पूर्णांकr_urb->transfer_buffer = kदो_स्मृति_array(2, माप(u16),
						       GFP_KERNEL);
	अगर (usb->पूर्णांकr_urb->transfer_buffer == शून्य)
		जाओ allocfail;

	अगर (usb_endpoपूर्णांक_type(&ep->desc) == USB_ENDPOINT_XFER_BULK)
		usb_fill_bulk_urb(usb->पूर्णांकr_urb, usb->usbdev,
			usb_rcvbulkpipe(usb->usbdev, 4),
			usb->पूर्णांकr_urb->transfer_buffer, 2*माप(u16),
			go7007_usb_पढ़ोपूर्णांकerrupt_complete, go);
	अन्यथा
		usb_fill_पूर्णांक_urb(usb->पूर्णांकr_urb, usb->usbdev,
			usb_rcvपूर्णांकpipe(usb->usbdev, 4),
			usb->पूर्णांकr_urb->transfer_buffer, 2*माप(u16),
			go7007_usb_पढ़ोपूर्णांकerrupt_complete, go, 8);
	usb_set_पूर्णांकfdata(पूर्णांकf, &go->v4l2_dev);

	/* Boot the GO7007 */
	अगर (go7007_boot_encoder(go, go->board_info->flags &
					GO7007_BOARD_USE_ONBOARD_I2C) < 0)
		जाओ allocfail;

	/* Register the EZ-USB I2C adapter, अगर we're using it */
	अगर (board->flags & GO7007_USB_EZUSB_I2C) अणु
		स_नकल(&go->i2c_adapter, &go7007_usb_adap_templ,
				माप(go7007_usb_adap_templ));
		mutex_init(&usb->i2c_lock);
		go->i2c_adapter.dev.parent = go->dev;
		i2c_set_adapdata(&go->i2c_adapter, go);
		अगर (i2c_add_adapter(&go->i2c_adapter) < 0) अणु
			dev_err(go->dev, "error: i2c_add_adapter failed\n");
			जाओ allocfail;
		पूर्ण
		go->i2c_adapter_online = 1;
	पूर्ण

	/* Pelco and Adlink reused the XMen and XMen-III venकरोr and product
	 * IDs क्रम their own incompatible designs.  We can detect XMen boards
	 * by probing the sensor, but there is no way to probe the sensors on
	 * the Pelco and Adlink designs so we शेष to the Adlink.  If it
	 * is actually a Pelco, the user must set the assume_endura module
	 * parameter. */
	अगर ((go->board_id == GO7007_BOARDID_XMEN ||
				go->board_id == GO7007_BOARDID_XMEN_III) &&
			go->i2c_adapter_online) अणु
		जोड़ i2c_smbus_data data;

		/* Check to see अगर रेजिस्टर 0x0A is 0x76 */
		i2c_smbus_xfer(&go->i2c_adapter, 0x21, I2C_CLIENT_SCCB,
			I2C_SMBUS_READ, 0x0A, I2C_SMBUS_BYTE_DATA, &data);
		अगर (data.byte != 0x76) अणु
			अगर (assume_endura) अणु
				go->board_id = GO7007_BOARDID_ENDURA;
				usb->board = board = &board_endura;
				go->board_info = &board->मुख्य_info;
				strscpy(go->name, "Pelco Endura",
					माप(go->name));
			पूर्ण अन्यथा अणु
				u16 channel;

				/* पढ़ो channel number from GPIO[1:0] */
				go7007_पढ़ो_addr(go, 0x3c81, &channel);
				channel &= 0x3;
				go->board_id = GO7007_BOARDID_ADLINK_MPG24;
				usb->board = board = &board_adlink_mpg24;
				go->board_info = &board->मुख्य_info;
				go->channel_number = channel;
				snम_लिखो(go->name, माप(go->name),
					"Adlink PCI-MPG24, channel #%d",
					channel);
			पूर्ण
			go7007_update_board(go);
		पूर्ण
	पूर्ण

	num_i2c_devs = go->board_info->num_i2c_devs;

	/* Probe the tuner model on the TV402U */
	अगर (go->board_id == GO7007_BOARDID_PX_TV402U) अणु
		/* Board strapping indicates tuner model */
		अगर (go7007_usb_venकरोr_request(go, 0x41, 0, 0, go->usb_buf, 3,
					1) < 0) अणु
			dev_err(go->dev, "GPIO read failed!\n");
			जाओ allocfail;
		पूर्ण
		चयन (go->usb_buf[0] >> 6) अणु
		हाल 1:
			go->tuner_type = TUNER_SONY_BTF_PG472Z;
			go->std = V4L2_STD_PAL;
			strscpy(go->name, "Plextor PX-TV402U-EU",
				माप(go->name));
			अवरोध;
		हाल 2:
			go->tuner_type = TUNER_SONY_BTF_PK467Z;
			go->std = V4L2_STD_NTSC_M_JP;
			num_i2c_devs -= 2;
			strscpy(go->name, "Plextor PX-TV402U-JP",
				माप(go->name));
			अवरोध;
		हाल 3:
			go->tuner_type = TUNER_SONY_BTF_PB463Z;
			num_i2c_devs -= 2;
			strscpy(go->name, "Plextor PX-TV402U-NA",
				माप(go->name));
			अवरोध;
		शेष:
			pr_debug("unable to detect tuner type!\n");
			अवरोध;
		पूर्ण
		/* Configure tuner mode selection inमाला_दो connected
		 * to the EZ-USB GPIO output pins */
		अगर (go7007_usb_venकरोr_request(go, 0x40, 0x7f02, 0,
					शून्य, 0, 0) < 0) अणु
			dev_err(go->dev, "GPIO write failed!\n");
			जाओ allocfail;
		पूर्ण
	पूर्ण

	/* Prपूर्णांक a nasty message अगर the user attempts to use a USB2.0 device in
	 * a USB1.1 port.  There will be silent corruption of the stream. */
	अगर ((board->flags & GO7007_USB_EZUSB) &&
			usbdev->speed != USB_SPEED_HIGH)
		dev_err(go->dev, "*** WARNING ***  This device must be connected to a USB 2.0 port! Attempting to capture video through a USB 1.1 port will result in stream corruption, even at low bitrates!\n");

	/* Allocate the URBs and buffers क्रम receiving the video stream */
	अगर (board->flags & GO7007_USB_EZUSB) अणु
		अगर (!usb->usbdev->ep_in[6])
			जाओ allocfail;
		v_urb_len = 1024;
		video_pipe = usb_rcvbulkpipe(usb->usbdev, 6);
	पूर्ण अन्यथा अणु
		अगर (!usb->usbdev->ep_in[1])
			जाओ allocfail;
		v_urb_len = 512;
		video_pipe = usb_rcvbulkpipe(usb->usbdev, 1);
	पूर्ण
	क्रम (i = 0; i < 8; ++i) अणु
		usb->video_urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (usb->video_urbs[i] == शून्य)
			जाओ allocfail;
		usb->video_urbs[i]->transfer_buffer =
						kदो_स्मृति(v_urb_len, GFP_KERNEL);
		अगर (usb->video_urbs[i]->transfer_buffer == शून्य)
			जाओ allocfail;
		usb_fill_bulk_urb(usb->video_urbs[i], usb->usbdev, video_pipe,
				usb->video_urbs[i]->transfer_buffer, v_urb_len,
				go7007_usb_पढ़ो_video_pipe_complete, go);
	पूर्ण

	/* Allocate the URBs and buffers क्रम receiving the audio stream */
	अगर ((board->flags & GO7007_USB_EZUSB) &&
	    (board->मुख्य_info.flags & GO7007_BOARD_HAS_AUDIO)) अणु
		अगर (!usb->usbdev->ep_in[8])
			जाओ allocfail;
		क्रम (i = 0; i < 8; ++i) अणु
			usb->audio_urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
			अगर (usb->audio_urbs[i] == शून्य)
				जाओ allocfail;
			usb->audio_urbs[i]->transfer_buffer = kदो_स्मृति(4096,
								GFP_KERNEL);
			अगर (usb->audio_urbs[i]->transfer_buffer == शून्य)
				जाओ allocfail;
			usb_fill_bulk_urb(usb->audio_urbs[i], usb->usbdev,
				usb_rcvbulkpipe(usb->usbdev, 8),
				usb->audio_urbs[i]->transfer_buffer, 4096,
				go7007_usb_पढ़ो_audio_pipe_complete, go);
		पूर्ण
	पूर्ण

	/* Do any final GO7007 initialization, then रेजिस्टर the
	 * V4L2 and ALSA पूर्णांकerfaces */
	अगर (go7007_रेजिस्टर_encoder(go, num_i2c_devs) < 0)
		जाओ allocfail;

	go->status = STATUS_ONLINE;
	वापस 0;

allocfail:
	go7007_usb_release(go);
	kमुक्त(go);
	वापस -ENOMEM;
पूर्ण

अटल व्योम go7007_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा go7007 *go = to_go7007(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&go->queue_lock);
	mutex_lock(&go->serialize_lock);

	अगर (go->audio_enabled)
		go7007_snd_हटाओ(go);

	go->status = STATUS_SHUTDOWN;
	v4l2_device_disconnect(&go->v4l2_dev);
	video_unरेजिस्टर_device(&go->vdev);
	mutex_unlock(&go->serialize_lock);
	mutex_unlock(&go->queue_lock);

	v4l2_device_put(&go->v4l2_dev);
पूर्ण

अटल काष्ठा usb_driver go7007_usb_driver = अणु
	.name		= "go7007",
	.probe		= go7007_usb_probe,
	.disconnect	= go7007_usb_disconnect,
	.id_table	= go7007_usb_id_table,
पूर्ण;

module_usb_driver(go7007_usb_driver);
MODULE_LICENSE("GPL v2");
