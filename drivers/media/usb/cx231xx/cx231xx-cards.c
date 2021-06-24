<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx-cards.c - driver क्रम Conexant Cx23100/101/102
				USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
				Based on em28xx driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <media/tuner.h>
#समावेश <media/tveeprom.h>
#समावेश <media/v4l2-common.h>

#समावेश <media/drv-पूर्णांकf/cx25840.h>
#समावेश <media/dvb-usb-ids.h>
#समावेश "xc5000.h"
#समावेश "tda18271.h"


अटल पूर्णांक tuner = -1;
module_param(tuner, पूर्णांक, 0444);
MODULE_PARM_DESC(tuner, "tuner type");

अटल पूर्णांक transfer_mode = 1;
module_param(transfer_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(transfer_mode, "transfer mode (1-ISO or 0-BULK)");

अटल अचिन्हित पूर्णांक disable_ir;
module_param(disable_ir, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ir, "disable infrared remote support");

/* Biपंचांगask marking allocated devices from 0 to CX231XX_MAXBOARDS */
अटल अचिन्हित दीर्घ cx231xx_devused;

/*
 *  Reset sequences क्रम analog/digital modes
 */

अटल काष्ठा cx231xx_reg_seq RDE250_XCV_TUNER[] = अणु
	अणु0x03, 0x01, 10पूर्ण,
	अणु0x03, 0x00, 30पूर्ण,
	अणु0x03, 0x01, 10पूर्ण,
	अणु-1, -1, -1पूर्ण,
पूर्ण;

/*
 *  Board definitions
 */
काष्ठा cx231xx_board cx231xx_boards[] = अणु
	[CX231XX_BOARD_UNKNOWN] = अणु
		.name = "Unknown CX231xx video grabber",
		.tuner_type = TUNER_ABSENT,
		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_CARRAERA] = अणु
		.name = "Conexant Hybrid TV - CARRAERA",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x02,
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_SHELBY] = अणु
		.name = "Conexant Hybrid TV - SHELBY",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x32,
		.norm = V4L2_STD_NTSC,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_RDE_253S] = अणु
		.name = "Conexant Hybrid TV - RDE253S",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x02,
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,

	[CX231XX_BOARD_CNXT_RDU_253S] = अणु
		.name = "Conexant Hybrid TV - RDU253S",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x02,
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_3_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_VIDEO_GRABBER] = अणु
		.name = "Conexant VIDEO GRABBER",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x1c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_PAL,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		/* Actually, it has a 417, but it isn't working correctly.
		 * So set to 0 क्रम now until someone can manage to get this
		 * to work reliably. */
		.has_417 = 0,

		.input = अणुअणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_RDE_250] = अणु
		.name = "Conexant Hybrid TV - rde 250",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x02,
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_CNXT_RDU_250] = अणु
		.name = "Conexant Hybrid TV - RDU 250",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x32,
		.norm = V4L2_STD_NTSC,

		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_VIDEO,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_EXETER] = अणु
		.name = "Hauppauge EXETER",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_1,
		.demod_i2c_master = I2C_1_MUX_1,
		.has_dvb = 1,
		.demod_addr = 0x0e,
		.norm = V4L2_STD_NTSC,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_USBLIVE2] = अणु
		.name = "Hauppauge USB Live 2",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_NTSC,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		.input = अणुअणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_KWORLD_UB430_USB_HYBRID] = अणु
		.name = "Kworld UB430 USB Hybrid",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x11,	/* According with PV cxPolaris.inf file */
		.tuner_sअगर_gpio = -1,
		.tuner_scl_gpio = -1,
		.tuner_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_2,
		.demod_i2c_master = I2C_1_MUX_3,
		.ir_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x10,
		.norm = V4L2_STD_PAL_M,
		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_KWORLD_UB445_USB_HYBRID] = अणु
		.name = "Kworld UB445 USB Hybrid",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x11,	/* According with PV cxPolaris.inf file */
		.tuner_sअगर_gpio = -1,
		.tuner_scl_gpio = -1,
		.tuner_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_2,
		.demod_i2c_master = I2C_1_MUX_3,
		.ir_i2c_master = I2C_2,
		.has_dvb = 1,
		.demod_addr = 0x10,
		.norm = V4L2_STD_NTSC_M,
		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_PV_PLAYTV_USB_HYBRID] = अणु
		.name = "Pixelview PlayTV USB Hybrid",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x1c,
		.tuner_sअगर_gpio = -1,
		.tuner_scl_gpio = -1,
		.tuner_sda_gpio = -1,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_2,
		.demod_i2c_master = I2C_1_MUX_3,
		.ir_i2c_master = I2C_2,
		.rc_map_name = RC_MAP_PIXELVIEW_002T,
		.has_dvb = 1,
		.demod_addr = 0x10,
		.norm = V4L2_STD_PAL_M,
		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_PV_XCAPTURE_USB] = अणु
		.name = "Pixelview Xcapture USB",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_NTSC,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,

		.input = अणुअणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,

	[CX231XX_BOARD_ICONBIT_U100] = अणु
		.name = "Iconbit Analog Stick U100 FM",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x1C,
		.gpio_pin_status_mask = 0x4001000,

		.input = अणुअणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL] = अणु
		.name = "Hauppauge WinTV USB2 FM (PAL)",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC] = अणु
		.name = "Hauppauge WinTV USB2 FM (NTSC)",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.norm = V4L2_STD_NTSC,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_ELGATO_VIDEO_CAPTURE_V2] = अणु
		.name = "Elgato Video Capture V2",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_NTSC,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		.input = अणुअणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_OTG102] = अणु
		.name = "Geniatech OTG102",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
			/* According with PV CxPlrCAP.inf file */
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_NTSC,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		/*.has_417 = 1, */
		/* This board is believed to have a hardware encoding chip
		 * supporting mpeg1/2/4, but as the 417 is apparently not
		 * working क्रम the reference board it is not here either. */

		.input = अणुअणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण, अणु
				.type = CX231XX_VMUX_SVIDEO,
				.vmux = CX231XX_VIN_1_1 |
					(CX231XX_VIN_1_2 << 8) |
					CX25840_SVIDEO_ON,
				.amux = CX231XX_AMUX_LINE_IN,
				.gpio = शून्य,
			पूर्ण
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx] = अणु
		.name = "Hauppauge WinTV 930C-HD (1113xx) / HVR-900H (111xxx) / PCTV QuatroStick 521e",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addr = 0x64, /* 0xc8 >> 1 */
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx] = अणु
		.name = "Hauppauge WinTV 930C-HD (1114xx) / HVR-901H (1114xx) / PCTV QuatroStick 522e",
		.tuner_type = TUNER_ABSENT,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addr = 0x64, /* 0xc8 >> 1 */
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_955Q] = अणु
		.name = "Hauppauge WinTV-HVR-955Q (111401)",
		.tuner_type = TUNER_ABSENT,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addr = 0x59, /* 0xb2 >> 1 */
		.norm = V4L2_STD_NTSC,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_TERRATEC_GRABBY] = अणु
		.name = "Terratec Grabby",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_PAL,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		.input = अणुअणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD] = अणु
		.name = "Evromedia USB Full Hybrid Full HD",
		.tuner_type = TUNER_ABSENT,
		.demod_addr = 0x64, /* 0xc8 >> 1 */
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.decoder = CX231XX_AVDECODER,
		.norm = V4L2_STD_PAL,
		.output_mode = OUT_MODE_VIP11,
		.tuner_addr = 0x60, /* 0xc0 >> 1 */
		.tuner_i2c_master = I2C_2,
		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = 0,
			.amux = CX231XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_ASTROMETA_T2HYBRID] = अणु
		.name = "Astrometa T2hybrid",
		.tuner_type = TUNER_ABSENT,
		.has_dvb = 1,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.agc_analog_digital_select_gpio = 0x01,
		.ctl_pin_status_mask = 0xffffffc4,
		.demod_addr = 0x18, /* 0x30 >> 1 */
		.demod_i2c_master = I2C_1_MUX_1,
		.gpio_pin_status_mask = 0xa,
		.norm = V4L2_STD_NTSC,
		.tuner_addr = 0x3a, /* 0x74 >> 1 */
		.tuner_i2c_master = I2C_1_MUX_3,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.tuner_sअगर_gpio = 0x05,
		.input = अणुअणु
				.type = CX231XX_VMUX_TELEVISION,
				.vmux = CX231XX_VIN_1_1,
				.amux = CX231XX_AMUX_VIDEO,
			पूर्ण, अणु
				.type = CX231XX_VMUX_COMPOSITE1,
				.vmux = CX231XX_VIN_2_1,
				.amux = CX231XX_AMUX_LINE_IN,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_THE_IMAGING_SOURCE_DFG_USB2_PRO] = अणु
		.name = "The Imaging Source DFG/USB2pro",
		.tuner_type = TUNER_ABSENT,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.norm = V4L2_STD_PAL,
		.no_alt_vanc = 1,
		.बाह्यal_av = 1,
		.input = अणुअणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_1_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_2_1 |
				(CX231XX_VIN_2_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_935C] = अणु
		.name = "Hauppauge WinTV-HVR-935C",
		.tuner_type = TUNER_ABSENT,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addr = 0x64, /* 0xc8 >> 1 */
		.norm = V4L2_STD_PAL,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX231XX_BOARD_HAUPPAUGE_975] = अणु
		.name = "Hauppauge WinTV-HVR-975",
		.tuner_type = TUNER_ABSENT,
		.tuner_addr = 0x60,
		.tuner_gpio = RDE250_XCV_TUNER,
		.tuner_sअगर_gpio = 0x05,
		.tuner_scl_gpio = 0x1a,
		.tuner_sda_gpio = 0x1b,
		.decoder = CX231XX_AVDECODER,
		.output_mode = OUT_MODE_VIP11,
		.demod_xfer_mode = 0,
		.ctl_pin_status_mask = 0xFFFFFFC4,
		.agc_analog_digital_select_gpio = 0x0c,
		.gpio_pin_status_mask = 0x4001000,
		.tuner_i2c_master = I2C_1_MUX_3,
		.demod_i2c_master = I2C_1_MUX_3,
		.has_dvb = 1,
		.demod_addr = 0x59, /* 0xb2 >> 1 */
		.demod_addr2 = 0x64, /* 0xc8 >> 1 */
		.norm = V4L2_STD_ALL,

		.input = अणुअणु
			.type = CX231XX_VMUX_TELEVISION,
			.vmux = CX231XX_VIN_3_1,
			.amux = CX231XX_AMUX_VIDEO,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_COMPOSITE1,
			.vmux = CX231XX_VIN_2_1,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण, अणु
			.type = CX231XX_VMUX_SVIDEO,
			.vmux = CX231XX_VIN_1_1 |
				(CX231XX_VIN_1_2 << 8) |
				CX25840_SVIDEO_ON,
			.amux = CX231XX_AMUX_LINE_IN,
			.gpio = शून्य,
		पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;
स्थिर अचिन्हित पूर्णांक cx231xx_bcount = ARRAY_SIZE(cx231xx_boards);

/* table of devices that work with this driver */
काष्ठा usb_device_id cx231xx_id_table[] = अणु
	अणुUSB_DEVICE(0x1D19, 0x6109),
	.driver_info = CX231XX_BOARD_PV_XCAPTURE_USBपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x5A3C),
	 .driver_info = CX231XX_BOARD_UNKNOWNपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A2),
	 .driver_info = CX231XX_BOARD_CNXT_CARRAERAपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A1),
	 .driver_info = CX231XX_BOARD_CNXT_SHELBYपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A4),
	 .driver_info = CX231XX_BOARD_CNXT_RDE_253Sपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A5),
	 .driver_info = CX231XX_BOARD_CNXT_RDU_253Sपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A6),
	 .driver_info = CX231XX_BOARD_CNXT_VIDEO_GRABBERपूर्ण,
	अणुUSB_DEVICE(0x0572, 0x589E),
	 .driver_info = CX231XX_BOARD_CNXT_RDE_250पूर्ण,
	अणुUSB_DEVICE(0x0572, 0x58A0),
	 .driver_info = CX231XX_BOARD_CNXT_RDU_250पूर्ण,
	/* AverMedia DVD EZMaker 7 */
	अणुUSB_DEVICE(0x07ca, 0xc039),
	 .driver_info = CX231XX_BOARD_CNXT_VIDEO_GRABBERपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb110),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_USB2_FM_PALपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb111),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSCपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb120),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_EXETERपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb123),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_955Qपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb124),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_955Qपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb151),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_935Cपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb150),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_975पूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb130),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xxपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb131),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xxपूर्ण,
	/* Hauppauge WinTV-HVR-900-H */
	अणुUSB_DEVICE(0x2040, 0xb138),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xxपूर्ण,
	/* Hauppauge WinTV-HVR-901-H */
	अणुUSB_DEVICE(0x2040, 0xb139),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xxपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xb140),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_EXETERपूर्ण,
	अणुUSB_DEVICE(0x2040, 0xc200),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_USBLIVE2पूर्ण,
	/* PCTV QuatroStick 521e */
	अणुUSB_DEVICE(0x2013, 0x0259),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xxपूर्ण,
	/* PCTV QuatroStick 522e */
	अणुUSB_DEVICE(0x2013, 0x025e),
	 .driver_info = CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xxपूर्ण,
	अणुUSB_DEVICE_VER(USB_VID_PIXELVIEW, USB_PID_PIXELVIEW_SBTVD, 0x4000, 0x4001),
	 .driver_info = CX231XX_BOARD_PV_PLAYTV_USB_HYBRIDपूर्ण,
	अणुUSB_DEVICE(USB_VID_PIXELVIEW, 0x5014),
	 .driver_info = CX231XX_BOARD_PV_XCAPTURE_USBपूर्ण,
	अणुUSB_DEVICE(0x1b80, 0xe424),
	 .driver_info = CX231XX_BOARD_KWORLD_UB430_USB_HYBRIDपूर्ण,
	अणुUSB_DEVICE(0x1b80, 0xe421),
	 .driver_info = CX231XX_BOARD_KWORLD_UB445_USB_HYBRIDपूर्ण,
	अणुUSB_DEVICE(0x1f4d, 0x0237),
	 .driver_info = CX231XX_BOARD_ICONBIT_U100पूर्ण,
	अणुUSB_DEVICE(0x0fd9, 0x0037),
	 .driver_info = CX231XX_BOARD_ELGATO_VIDEO_CAPTURE_V2पूर्ण,
	अणुUSB_DEVICE(0x1f4d, 0x0102),
	 .driver_info = CX231XX_BOARD_OTG102पूर्ण,
	अणुUSB_DEVICE(USB_VID_TERRATEC, 0x00a6),
	 .driver_info = CX231XX_BOARD_TERRATEC_GRABBYपूर्ण,
	अणुUSB_DEVICE(0x1b80, 0xd3b2),
	.driver_info = CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHDपूर्ण,
	अणुUSB_DEVICE(0x15f4, 0x0135),
	.driver_info = CX231XX_BOARD_ASTROMETA_T2HYBRIDपूर्ण,
	अणुUSB_DEVICE(0x199e, 0x8002),
	 .driver_info = CX231XX_BOARD_THE_IMAGING_SOURCE_DFG_USB2_PROपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, cx231xx_id_table);

/* cx231xx_tuner_callback
 * will be used to reset XC5000 tuner using GPIO pin
 */

पूर्णांक cx231xx_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा cx231xx *dev = ptr;

	अगर (dev->tuner_type == TUNER_XC5000) अणु
		अगर (command == XC5000_TUNER_RESET) अणु
			dev_dbg(dev->dev,
				"Tuner CB: RESET: cmd %d : tuner type %d\n",
				command, dev->tuner_type);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       0);
			msleep(330);
			cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit,
					       1);
			msleep(10);
		पूर्ण
	पूर्ण अन्यथा अगर (dev->tuner_type == TUNER_NXP_TDA18271) अणु
		चयन (command) अणु
		हाल TDA18271_CALLBACK_CMD_AGC_ENABLE:
			अगर (dev->model == CX231XX_BOARD_PV_PLAYTV_USB_HYBRID)
				rc = cx231xx_set_agc_analog_digital_mux_select(dev, arg);
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_tuner_callback);

अटल व्योम cx231xx_reset_out(काष्ठा cx231xx *dev)
अणु
	cx231xx_set_gpio_value(dev, CX23417_RESET, 1);
	msleep(200);
	cx231xx_set_gpio_value(dev, CX23417_RESET, 0);
	msleep(200);
	cx231xx_set_gpio_value(dev, CX23417_RESET, 1);
पूर्ण

अटल व्योम cx231xx_enable_OSC(काष्ठा cx231xx *dev)
अणु
	cx231xx_set_gpio_value(dev, CX23417_OSC_EN, 1);
पूर्ण

अटल व्योम cx231xx_sleep_s5h1432(काष्ठा cx231xx *dev)
अणु
	cx231xx_set_gpio_value(dev, SLEEP_S5H1432, 0);
पूर्ण

अटल अंतरभूत व्योम cx231xx_set_model(काष्ठा cx231xx *dev)
अणु
	dev->board = cx231xx_boards[dev->model];
पूर्ण

/* Since cx231xx_pre_card_setup() requires a proper dev->model,
 * this won't work क्रम boards with generic PCI IDs
 */
व्योम cx231xx_pre_card_setup(काष्ठा cx231xx *dev)
अणु
	dev_info(dev->dev, "Identified as %s (card=%d)\n",
		dev->board.name, dev->model);

	अगर (CX231XX_BOARD_ASTROMETA_T2HYBRID == dev->model) अणु
		/* turn on demodulator chip */
		cx231xx_set_gpio_value(dev, 0x03, 0x01);
	पूर्ण

	/* set the direction क्रम GPIO pins */
	अगर (dev->board.tuner_gpio) अणु
		cx231xx_set_gpio_direction(dev, dev->board.tuner_gpio->bit, 1);
		cx231xx_set_gpio_value(dev, dev->board.tuner_gpio->bit, 1);
	पूर्ण
	अगर (dev->board.tuner_sअगर_gpio >= 0)
		cx231xx_set_gpio_direction(dev, dev->board.tuner_sअगर_gpio, 1);

	/* request some modules अगर any required */

	/* set the mode to Analog mode initially */
	cx231xx_set_mode(dev, CX231XX_ANALOG_MODE);

	/* Unlock device */
	/* cx231xx_set_mode(dev, CX231XX_SUSPEND); */

पूर्ण

अटल व्योम cx231xx_config_tuner(काष्ठा cx231xx *dev)
अणु
	काष्ठा tuner_setup tun_setup;
	काष्ठा v4l2_frequency f;

	अगर (dev->tuner_type == TUNER_ABSENT)
		वापस;

	tun_setup.mode_mask = T_ANALOG_TV | T_RADIO;
	tun_setup.type = dev->tuner_type;
	tun_setup.addr = dev->tuner_addr;
	tun_setup.tuner_callback = cx231xx_tuner_callback;

	tuner_call(dev, tuner, s_type_addr, &tun_setup);

#अगर 0
	अगर (tun_setup.type == TUNER_XC5000) अणु
		अटल काष्ठा xc2028_ctrl ctrl = अणु
			.fname = XC5000_DEFAULT_FIRMWARE,
			.max_len = 64,
			.demod = 0;
		पूर्ण;
		काष्ठा v4l2_priv_tun_config cfg = अणु
			.tuner = dev->tuner_type,
			.priv = &ctrl,
		पूर्ण;
		tuner_call(dev, tuner, s_config, &cfg);
	पूर्ण
#पूर्ण_अगर
	/* configure tuner */
	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 9076;	/* just a magic number */
	dev->ctl_freq = f.frequency;
	call_all(dev, tuner, s_frequency, &f);

पूर्ण

अटल पूर्णांक पढ़ो_eeprom(काष्ठा cx231xx *dev, काष्ठा i2c_client *client,
		       u8 *eedata, पूर्णांक len)
अणु
	पूर्णांक ret;
	u8 start_offset = 0;
	पूर्णांक len_toकरो = len;
	u8 *eedata_cur = eedata;
	पूर्णांक i;
	काष्ठा i2c_msg msg_ग_लिखो = अणु .addr = client->addr, .flags = 0,
		.buf = &start_offset, .len = 1 पूर्ण;
	काष्ठा i2c_msg msg_पढ़ो = अणु .addr = client->addr, .flags = I2C_M_RD पूर्ण;

	/* start पढ़ोing at offset 0 */
	ret = i2c_transfer(client->adapter, &msg_ग_लिखो, 1);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "Can't read eeprom\n");
		वापस ret;
	पूर्ण

	जबतक (len_toकरो > 0) अणु
		msg_पढ़ो.len = (len_toकरो > 64) ? 64 : len_toकरो;
		msg_पढ़ो.buf = eedata_cur;

		ret = i2c_transfer(client->adapter, &msg_पढ़ो, 1);
		अगर (ret < 0) अणु
			dev_err(dev->dev, "Can't read eeprom\n");
			वापस ret;
		पूर्ण
		eedata_cur += msg_पढ़ो.len;
		len_toकरो -= msg_पढ़ो.len;
	पूर्ण

	क्रम (i = 0; i + 15 < len; i += 16)
		dev_dbg(dev->dev, "i2c eeprom %02x: %*ph\n",
			i, 16, &eedata[i]);

	वापस 0;
पूर्ण

व्योम cx231xx_card_setup(काष्ठा cx231xx *dev)
अणु

	cx231xx_set_model(dev);

	dev->tuner_type = cx231xx_boards[dev->model].tuner_type;
	अगर (cx231xx_boards[dev->model].tuner_addr)
		dev->tuner_addr = cx231xx_boards[dev->model].tuner_addr;

	/* request some modules */
	अगर (dev->board.decoder == CX231XX_AVDECODER) अणु
		dev->sd_cx25840 = v4l2_i2c_new_subdev(&dev->v4l2_dev,
					cx231xx_get_i2c_adap(dev, I2C_0),
					"cx25840", 0x88 >> 1, शून्य);
		अगर (dev->sd_cx25840 == शून्य)
			dev_err(dev->dev,
				"cx25840 subdev registration failure\n");
		cx25840_call(dev, core, load_fw);

	पूर्ण

	/* Initialize the tuner */
	अगर (dev->board.tuner_type != TUNER_ABSENT) अणु
		काष्ठा i2c_adapter *tuner_i2c = cx231xx_get_i2c_adap(dev,
						dev->board.tuner_i2c_master);
		dev->sd_tuner = v4l2_i2c_new_subdev(&dev->v4l2_dev,
						    tuner_i2c,
						    "tuner",
						    dev->tuner_addr, शून्य);
		अगर (dev->sd_tuner == शून्य)
			dev_err(dev->dev,
				"tuner subdev registration failure\n");
		अन्यथा
			cx231xx_config_tuner(dev);
	पूर्ण

	चयन (dev->model) अणु
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	हाल CX231XX_BOARD_HAUPPAUGE_975:
		अणु
			काष्ठा eeprom अणु
				काष्ठा tveeprom tvee;
				u8 eeprom[256];
				काष्ठा i2c_client client;
			पूर्ण;
			काष्ठा eeprom *e = kzalloc(माप(*e), GFP_KERNEL);

			अगर (e == शून्य) अणु
				dev_err(dev->dev,
					"failed to allocate memory to read eeprom\n");
				अवरोध;
			पूर्ण
			e->client.adapter = cx231xx_get_i2c_adap(dev, I2C_1_MUX_1);
			e->client.addr = 0xa0 >> 1;

			पढ़ो_eeprom(dev, &e->client, e->eeprom, माप(e->eeprom));
			tveeprom_hauppauge_analog(&e->tvee, e->eeprom + 0xc0);
			kमुक्त(e);
			अवरोध;
		पूर्ण
	पूर्ण

पूर्ण

/*
 * cx231xx_config()
 * inits रेजिस्टरs with sane शेषs
 */
पूर्णांक cx231xx_config(काष्ठा cx231xx *dev)
अणु
	/* TBD need to add cx231xx specअगरic code */

	वापस 0;
पूर्ण

/*
 * cx231xx_config_i2c()
 * configure i2c attached devices
 */
व्योम cx231xx_config_i2c(काष्ठा cx231xx *dev)
अणु
	/* u32 input = INPUT(dev->video_input)->vmux; */

	call_all(dev, video, s_stream, 1);
पूर्ण

अटल व्योम cx231xx_unरेजिस्टर_media_device(काष्ठा cx231xx *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	अगर (dev->media_dev) अणु
		media_device_unरेजिस्टर(dev->media_dev);
		media_device_cleanup(dev->media_dev);
		kमुक्त(dev->media_dev);
		dev->media_dev = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * cx231xx_realease_resources()
 * unरेजिस्टरs the v4l2,i2c and usb devices
 * called when the device माला_लो disconnected or at module unload
*/
व्योम cx231xx_release_resources(काष्ठा cx231xx *dev)
अणु
	cx231xx_ir_निकास(dev);

	cx231xx_release_analog_resources(dev);

	cx231xx_हटाओ_from_devlist(dev);

	/* Release I2C buses */
	cx231xx_dev_uninit(dev);

	/* delete v4l2 device */
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	cx231xx_unरेजिस्टर_media_device(dev);

	usb_put_dev(dev->udev);

	/* Mark device as unused */
	clear_bit(dev->devno, &cx231xx_devused);
पूर्ण

अटल पूर्णांक cx231xx_media_device_init(काष्ठा cx231xx *dev,
				      काष्ठा usb_device *udev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	media_device_usb_init(mdev, udev, dev->board.name);

	dev->media_dev = mdev;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * cx231xx_init_dev()
 * allocates and inits the device काष्ठाs, रेजिस्टरs i2c bus and v4l device
 */
अटल पूर्णांक cx231xx_init_dev(काष्ठा cx231xx *dev, काष्ठा usb_device *udev,
			    पूर्णांक minor)
अणु
	पूर्णांक retval = -ENOMEM;
	अचिन्हित पूर्णांक maxh, maxw;

	dev->udev = udev;
	mutex_init(&dev->lock);
	mutex_init(&dev->ctrl_urb_lock);
	mutex_init(&dev->gpio_i2c_lock);
	mutex_init(&dev->i2c_lock);

	spin_lock_init(&dev->video_mode.slock);
	spin_lock_init(&dev->vbi_mode.slock);
	spin_lock_init(&dev->sliced_cc_mode.slock);

	init_रुकोqueue_head(&dev->खोलो);
	init_रुकोqueue_head(&dev->रुको_frame);
	init_रुकोqueue_head(&dev->रुको_stream);

	dev->cx231xx_पढ़ो_ctrl_reg = cx231xx_पढ़ो_ctrl_reg;
	dev->cx231xx_ग_लिखो_ctrl_reg = cx231xx_ग_लिखो_ctrl_reg;
	dev->cx231xx_send_usb_command = cx231xx_send_usb_command;
	dev->cx231xx_gpio_i2c_पढ़ो = cx231xx_gpio_i2c_पढ़ो;
	dev->cx231xx_gpio_i2c_ग_लिखो = cx231xx_gpio_i2c_ग_लिखो;

	/* Query cx231xx to find what pcb config it is related to */
	retval = initialize_cx231xx(dev);
	अगर (retval < 0) अणु
		dev_err(dev->dev, "Failed to read PCB config\n");
		वापस retval;
	पूर्ण

	/*To workaround error number=-71 on EP0 क्रम VideoGrabber,
		 need set alt here.*/
	अगर (dev->model == CX231XX_BOARD_CNXT_VIDEO_GRABBER ||
	    dev->model == CX231XX_BOARD_HAUPPAUGE_USBLIVE2) अणु
		cx231xx_set_alt_setting(dev, INDEX_VIDEO, 3);
		cx231xx_set_alt_setting(dev, INDEX_VANC, 1);
	पूर्ण
	/* Cx231xx pre card setup */
	cx231xx_pre_card_setup(dev);

	retval = cx231xx_config(dev);
	अगर (retval) अणु
		dev_err(dev->dev, "error configuring device\n");
		वापस -ENOMEM;
	पूर्ण

	/* set शेष norm */
	dev->norm = dev->board.norm;

	/* रेजिस्टर i2c bus */
	retval = cx231xx_dev_init(dev);
	अगर (retval) अणु
		dev_err(dev->dev,
			"%s: cx231xx_i2c_register - errCode [%d]!\n",
			__func__, retval);
		जाओ err_dev_init;
	पूर्ण

	/* Do board specअगरic init */
	cx231xx_card_setup(dev);

	/* configure the device */
	cx231xx_config_i2c(dev);

	maxw = norm_maxw(dev);
	maxh = norm_maxh(dev);

	/* set शेष image size */
	dev->width = maxw;
	dev->height = maxh;
	dev->पूर्णांकerlaced = 0;
	dev->video_input = 0;

	retval = cx231xx_config(dev);
	अगर (retval) अणु
		dev_err(dev->dev, "%s: cx231xx_config - errCode [%d]!\n",
			__func__, retval);
		जाओ err_dev_init;
	पूर्ण

	/* init video dma queue */
	INIT_LIST_HEAD(&dev->video_mode.vidq.active);

	/* init vbi dma queue */
	INIT_LIST_HEAD(&dev->vbi_mode.vidq.active);

	/* Reset other chips required अगर they are tied up with GPIO pins */
	cx231xx_add_पूर्णांकo_devlist(dev);

	अगर (dev->board.has_417) अणु
		dev_info(dev->dev, "attach 417 %d\n", dev->model);
		अगर (cx231xx_417_रेजिस्टर(dev) < 0) अणु
			dev_err(dev->dev,
				"%s() Failed to register 417 on VID_B\n",
				__func__);
		पूर्ण
	पूर्ण

	retval = cx231xx_रेजिस्टर_analog_devices(dev);
	अगर (retval)
		जाओ err_analog;

	cx231xx_ir_init(dev);

	cx231xx_init_extension(dev);

	वापस 0;
err_analog:
	cx231xx_unरेजिस्टर_media_device(dev);
	cx231xx_release_analog_resources(dev);
	cx231xx_हटाओ_from_devlist(dev);
err_dev_init:
	cx231xx_dev_uninit(dev);
	वापस retval;
पूर्ण

#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx231xx *dev = container_of(work,
					   काष्ठा cx231xx, request_module_wk);

	अगर (dev->has_alsa_audio)
		request_module("cx231xx-alsa");

	अगर (dev->board.has_dvb)
		request_module("cx231xx-dvb");

पूर्ण

अटल व्योम request_modules(काष्ठा cx231xx *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा cx231xx *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

अटल पूर्णांक cx231xx_init_v4l2(काष्ठा cx231xx *dev,
			     काष्ठा usb_device *udev,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			     पूर्णांक isoc_pipe)
अणु
	काष्ठा usb_पूर्णांकerface *uअगर;
	पूर्णांक i, idx;

	/* Video Init */

	/* compute alternate max packet sizes क्रम video */
	idx = dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.video_index + 1;
	अगर (idx >= dev->max_iad_पूर्णांकerface_count) अणु
		dev_err(dev->dev,
			"Video PCB interface #%d doesn't exist\n", idx);
		वापस -ENODEV;
	पूर्ण

	uअगर = udev->actconfig->पूर्णांकerface[idx];

	अगर (uअगर->altsetting[0].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
		वापस -ENODEV;

	dev->video_mode.end_poपूर्णांक_addr = uअगर->altsetting[0].endpoपूर्णांक[isoc_pipe].desc.bEndpoपूर्णांकAddress;
	dev->video_mode.num_alt = uअगर->num_altsetting;

	dev_info(dev->dev,
		 "video EndPoint Addr 0x%x, Alternate settings: %i\n",
		 dev->video_mode.end_poपूर्णांक_addr,
		 dev->video_mode.num_alt);

	dev->video_mode.alt_max_pkt_size = devm_kदो_स्मृति_array(&udev->dev, 32, dev->video_mode.num_alt, GFP_KERNEL);
	अगर (dev->video_mode.alt_max_pkt_size == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->video_mode.num_alt; i++) अणु
		u16 पंचांगp;

		अगर (uअगर->altsetting[i].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
			वापस -ENODEV;

		पंचांगp = le16_to_cpu(uअगर->altsetting[i].endpoपूर्णांक[isoc_pipe].desc.wMaxPacketSize);
		dev->video_mode.alt_max_pkt_size[i] = (पंचांगp & 0x07ff) * (((पंचांगp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Alternate setting %i, max size= %i\n", i,
			dev->video_mode.alt_max_pkt_size[i]);
	पूर्ण

	/* VBI Init */

	idx = dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.vanc_index + 1;
	अगर (idx >= dev->max_iad_पूर्णांकerface_count) अणु
		dev_err(dev->dev,
			"VBI PCB interface #%d doesn't exist\n", idx);
		वापस -ENODEV;
	पूर्ण
	uअगर = udev->actconfig->पूर्णांकerface[idx];

	अगर (uअगर->altsetting[0].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
		वापस -ENODEV;

	dev->vbi_mode.end_poपूर्णांक_addr =
	    uअगर->altsetting[0].endpoपूर्णांक[isoc_pipe].desc.
			bEndpoपूर्णांकAddress;

	dev->vbi_mode.num_alt = uअगर->num_altsetting;
	dev_info(dev->dev,
		 "VBI EndPoint Addr 0x%x, Alternate settings: %i\n",
		 dev->vbi_mode.end_poपूर्णांक_addr,
		 dev->vbi_mode.num_alt);

	/* compute alternate max packet sizes क्रम vbi */
	dev->vbi_mode.alt_max_pkt_size = devm_kदो_स्मृति_array(&udev->dev, 32, dev->vbi_mode.num_alt, GFP_KERNEL);
	अगर (dev->vbi_mode.alt_max_pkt_size == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->vbi_mode.num_alt; i++) अणु
		u16 पंचांगp;

		अगर (uअगर->altsetting[i].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
			वापस -ENODEV;

		पंचांगp = le16_to_cpu(uअगर->altsetting[i].endpoपूर्णांक[isoc_pipe].
				desc.wMaxPacketSize);
		dev->vbi_mode.alt_max_pkt_size[i] =
		    (पंचांगp & 0x07ff) * (((पंचांगp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Alternate setting %i, max size= %i\n", i,
			dev->vbi_mode.alt_max_pkt_size[i]);
	पूर्ण

	/* Sliced CC VBI init */

	/* compute alternate max packet sizes क्रम sliced CC */
	idx = dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.hanc_index + 1;
	अगर (idx >= dev->max_iad_पूर्णांकerface_count) अणु
		dev_err(dev->dev,
			"Sliced CC PCB interface #%d doesn't exist\n", idx);
		वापस -ENODEV;
	पूर्ण
	uअगर = udev->actconfig->पूर्णांकerface[idx];

	अगर (uअगर->altsetting[0].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
		वापस -ENODEV;

	dev->sliced_cc_mode.end_poपूर्णांक_addr =
	    uअगर->altsetting[0].endpoपूर्णांक[isoc_pipe].desc.
			bEndpoपूर्णांकAddress;

	dev->sliced_cc_mode.num_alt = uअगर->num_altsetting;
	dev_info(dev->dev,
		 "sliced CC EndPoint Addr 0x%x, Alternate settings: %i\n",
		 dev->sliced_cc_mode.end_poपूर्णांक_addr,
		 dev->sliced_cc_mode.num_alt);
	dev->sliced_cc_mode.alt_max_pkt_size = devm_kदो_स्मृति_array(&udev->dev, 32, dev->sliced_cc_mode.num_alt, GFP_KERNEL);
	अगर (dev->sliced_cc_mode.alt_max_pkt_size == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->sliced_cc_mode.num_alt; i++) अणु
		u16 पंचांगp;

		अगर (uअगर->altsetting[i].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1)
			वापस -ENODEV;

		पंचांगp = le16_to_cpu(uअगर->altsetting[i].endpoपूर्णांक[isoc_pipe].
				desc.wMaxPacketSize);
		dev->sliced_cc_mode.alt_max_pkt_size[i] =
		    (पंचांगp & 0x07ff) * (((पंचांगp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"Alternate setting %i, max size= %i\n", i,
			dev->sliced_cc_mode.alt_max_pkt_size[i]);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * cx231xx_usb_probe()
 * checks क्रम supported devices
 */
अटल पूर्णांक cx231xx_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा device *d = &पूर्णांकerface->dev;
	काष्ठा usb_पूर्णांकerface *uअगर;
	काष्ठा cx231xx *dev = शून्य;
	पूर्णांक retval = -ENODEV;
	पूर्णांक nr = 0, अगरnum;
	पूर्णांक i, isoc_pipe = 0;
	अक्षर *speed;
	u8 idx;
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *assoc_desc;

	अगरnum = पूर्णांकerface->altsetting[0].desc.bInterfaceNumber;

	/*
	 * Interface number 0 - IR पूर्णांकerface (handled by mceusb driver)
	 * Interface number 1 - AV पूर्णांकerface (handled by this driver)
	 */
	अगर (अगरnum != 1)
		वापस -ENODEV;

	/* Check to see next मुक्त device and mark as used */
	करो अणु
		nr = find_first_zero_bit(&cx231xx_devused, CX231XX_MAXBOARDS);
		अगर (nr >= CX231XX_MAXBOARDS) अणु
			/* No मुक्त device slots */
			dev_err(d,
				"Supports only %i devices.\n",
				CX231XX_MAXBOARDS);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण जबतक (test_and_set_bit(nr, &cx231xx_devused));

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* allocate memory क्रम our device state and initialize it */
	dev = devm_kzalloc(&udev->dev, माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		retval = -ENOMEM;
		जाओ err_अगर;
	पूर्ण

	snम_लिखो(dev->name, 29, "cx231xx #%d", nr);
	dev->devno = nr;
	dev->model = id->driver_info;
	dev->video_mode.alt = -1;
	dev->dev = d;

	cx231xx_set_model(dev);

	dev->पूर्णांकerface_count++;
	/* reset gpio dir and value */
	dev->gpio_dir = 0;
	dev->gpio_val = 0;
	dev->xc_fw_load_करोne = 0;
	dev->has_alsa_audio = 1;
	dev->घातer_mode = -1;
	atomic_set(&dev->devlist_count, 0);

	/* 0 - vbi ; 1 -sliced cc mode */
	dev->vbi_or_sliced_cc_mode = 0;

	/* get maximum no.of IAD पूर्णांकerfaces */
	dev->max_iad_पूर्णांकerface_count = udev->config->desc.bNumInterfaces;

	/* init CIR module TBD */

	/*mode_tv: digital=1 or analog=0*/
	dev->mode_tv = 0;

	dev->USE_ISO = transfer_mode;

	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		speed = "1.5";
		अवरोध;
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_FULL:
		speed = "12";
		अवरोध;
	हाल USB_SPEED_HIGH:
		speed = "480";
		अवरोध;
	शेष:
		speed = "unknown";
	पूर्ण

	dev_info(d,
		 "New device %s %s @ %s Mbps (%04x:%04x) with %d interfaces\n",
		 udev->manufacturer ? udev->manufacturer : "",
		 udev->product ? udev->product : "",
		 speed,
		 le16_to_cpu(udev->descriptor.idVenकरोr),
		 le16_to_cpu(udev->descriptor.idProduct),
		 dev->max_iad_पूर्णांकerface_count);

	/* increment पूर्णांकerface count */
	dev->पूर्णांकerface_count++;

	/* get device number */
	nr = dev->devno;

	assoc_desc = udev->actconfig->पूर्णांकf_assoc[0];
	अगर (!assoc_desc || assoc_desc->bFirstInterface != अगरnum) अणु
		dev_err(d, "Not found matching IAD interface\n");
		retval = -ENODEV;
		जाओ err_अगर;
	पूर्ण

	dev_dbg(d, "registering interface %d\n", अगरnum);

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* Initialize the media controller */
	retval = cx231xx_media_device_init(dev, udev);
	अगर (retval) अणु
		dev_err(d, "cx231xx_media_device_init failed\n");
		जाओ err_media_init;
	पूर्ण

	/* Create v4l2 device */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	dev->v4l2_dev.mdev = dev->media_dev;
#पूर्ण_अगर
	retval = v4l2_device_रेजिस्टर(&पूर्णांकerface->dev, &dev->v4l2_dev);
	अगर (retval) अणु
		dev_err(d, "v4l2_device_register failed\n");
		जाओ err_v4l2;
	पूर्ण

	/* allocate device काष्ठा */
	retval = cx231xx_init_dev(dev, udev, nr);
	अगर (retval)
		जाओ err_init;

	retval = cx231xx_init_v4l2(dev, udev, पूर्णांकerface, isoc_pipe);
	अगर (retval)
		जाओ err_init;

	अगर (dev->current_pcb_config.ts1_source != 0xff) अणु
		/* compute alternate max packet sizes क्रम TS1 */
		idx = dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.ts1_index + 1;
		अगर (idx >= dev->max_iad_पूर्णांकerface_count) अणु
			dev_err(d, "TS1 PCB interface #%d doesn't exist\n",
				idx);
			retval = -ENODEV;
			जाओ err_video_alt;
		पूर्ण
		uअगर = udev->actconfig->पूर्णांकerface[idx];

		अगर (uअगर->altsetting[0].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1) अणु
			retval = -ENODEV;
			जाओ err_video_alt;
		पूर्ण

		dev->ts1_mode.end_poपूर्णांक_addr =
		    uअगर->altsetting[0].endpoपूर्णांक[isoc_pipe].
				desc.bEndpoपूर्णांकAddress;

		dev->ts1_mode.num_alt = uअगर->num_altsetting;
		dev_info(d,
			 "TS EndPoint Addr 0x%x, Alternate settings: %i\n",
			 dev->ts1_mode.end_poपूर्णांक_addr,
			 dev->ts1_mode.num_alt);

		dev->ts1_mode.alt_max_pkt_size = devm_kदो_स्मृति_array(&udev->dev, 32, dev->ts1_mode.num_alt, GFP_KERNEL);
		अगर (dev->ts1_mode.alt_max_pkt_size == शून्य) अणु
			retval = -ENOMEM;
			जाओ err_video_alt;
		पूर्ण

		क्रम (i = 0; i < dev->ts1_mode.num_alt; i++) अणु
			u16 पंचांगp;

			अगर (uअगर->altsetting[i].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1) अणु
				retval = -ENODEV;
				जाओ err_video_alt;
			पूर्ण

			पंचांगp = le16_to_cpu(uअगर->altsetting[i].
						endpoपूर्णांक[isoc_pipe].desc.
						wMaxPacketSize);
			dev->ts1_mode.alt_max_pkt_size[i] =
			    (पंचांगp & 0x07ff) * (((पंचांगp & 0x1800) >> 11) + 1);
			dev_dbg(d, "Alternate setting %i, max size= %i\n",
				i, dev->ts1_mode.alt_max_pkt_size[i]);
		पूर्ण
	पूर्ण

	अगर (dev->model == CX231XX_BOARD_CNXT_VIDEO_GRABBER) अणु
		cx231xx_enable_OSC(dev);
		cx231xx_reset_out(dev);
		cx231xx_set_alt_setting(dev, INDEX_VIDEO, 3);
	पूर्ण

	अगर (dev->model == CX231XX_BOARD_CNXT_RDE_253S)
		cx231xx_sleep_s5h1432(dev);

	/* load other modules required */
	request_modules(dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	/* Init entities at the Media Controller */
	cx231xx_v4l2_create_entities(dev);

	retval = v4l2_mc_create_media_graph(dev->media_dev);
	अगर (!retval)
		retval = media_device_रेजिस्टर(dev->media_dev);
#पूर्ण_अगर
	अगर (retval < 0)
		cx231xx_release_resources(dev);
	वापस retval;

err_video_alt:
	/* cx231xx_uninit_dev: */
	cx231xx_बंद_extension(dev);
	cx231xx_ir_निकास(dev);
	cx231xx_release_analog_resources(dev);
	cx231xx_417_unरेजिस्टर(dev);
	cx231xx_हटाओ_from_devlist(dev);
	cx231xx_dev_uninit(dev);
err_init:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_v4l2:
	cx231xx_unरेजिस्टर_media_device(dev);
err_media_init:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
err_अगर:
	usb_put_dev(udev);
	clear_bit(nr, &cx231xx_devused);
	वापस retval;
पूर्ण

/*
 * cx231xx_usb_disconnect()
 * called when the device माला_लो disconnected
 * video device will be unरेजिस्टरed on v4l2_बंद in हाल it is still खोलो
 */
अटल व्योम cx231xx_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा cx231xx *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	अगर (!dev)
		वापस;

	अगर (!dev->udev)
		वापस;

	dev->state |= DEV_DISCONNECTED;

	flush_request_modules(dev);

	/* रुको until all current v4l2 io is finished then deallocate
	   resources */
	mutex_lock(&dev->lock);

	wake_up_पूर्णांकerruptible_all(&dev->खोलो);

	अगर (dev->users) अणु
		dev_warn(dev->dev,
			 "device %s is open! Deregistration and memory deallocation are deferred on close.\n",
			 video_device_node_name(&dev->vdev));

		/* Even having users, it is safe to हटाओ the RC i2c driver */
		cx231xx_ir_निकास(dev);

		अगर (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		अन्यथा
			cx231xx_uninit_bulk(dev);
		wake_up_पूर्णांकerruptible(&dev->रुको_frame);
		wake_up_पूर्णांकerruptible(&dev->रुको_stream);
	पूर्ण अन्यथा अणु
	पूर्ण

	cx231xx_बंद_extension(dev);

	mutex_unlock(&dev->lock);

	अगर (!dev->users)
		cx231xx_release_resources(dev);
पूर्ण

अटल काष्ठा usb_driver cx231xx_usb_driver = अणु
	.name = "cx231xx",
	.probe = cx231xx_usb_probe,
	.disconnect = cx231xx_usb_disconnect,
	.id_table = cx231xx_id_table,
पूर्ण;

module_usb_driver(cx231xx_usb_driver);
