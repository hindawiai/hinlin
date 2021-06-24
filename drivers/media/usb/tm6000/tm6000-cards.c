<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// पंचांग6000-cards.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
//
// Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>
#समावेश <media/i2c/tvaudपन.स>
#समावेश <media/rc-map.h>

#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"
#समावेश "tuner-xc2028.h"
#समावेश "xc5000.h"

#घोषणा TM6000_BOARD_UNKNOWN			0
#घोषणा TM5600_BOARD_GENERIC			1
#घोषणा TM6000_BOARD_GENERIC			2
#घोषणा TM6010_BOARD_GENERIC			3
#घोषणा TM5600_BOARD_10MOONS_UT821		4
#घोषणा TM5600_BOARD_10MOONS_UT330		5
#घोषणा TM6000_BOARD_ADSTECH_DUAL_TV		6
#घोषणा TM6000_BOARD_FREECOM_AND_SIMILAR	7
#घोषणा TM6000_BOARD_ADSTECH_MINI_DUAL_TV	8
#घोषणा TM6010_BOARD_HAUPPAUGE_900H		9
#घोषणा TM6010_BOARD_BEHOLD_WANDER		10
#घोषणा TM6010_BOARD_BEHOLD_VOYAGER		11
#घोषणा TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE	12
#घोषणा TM6010_BOARD_TWINHAN_TU501		13
#घोषणा TM6010_BOARD_BEHOLD_WANDER_LITE		14
#घोषणा TM6010_BOARD_BEHOLD_VOYAGER_LITE	15
#घोषणा TM5600_BOARD_TERRATEC_GRABSTER		16

#घोषणा is_generic(model) ((model == TM6000_BOARD_UNKNOWN) || \
			   (model == TM5600_BOARD_GENERIC) || \
			   (model == TM6000_BOARD_GENERIC) || \
			   (model == TM6010_BOARD_GENERIC))

#घोषणा TM6000_MAXBOARDS        16
अटल अचिन्हित पूर्णांक card[]     = अणु[0 ... (TM6000_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(card,  पूर्णांक, शून्य, 0444);

अटल अचिन्हित दीर्घ पंचांग6000_devused;


काष्ठा पंचांग6000_board अणु
	अक्षर            *name;
	अक्षर		eename[16];		/* EEPROM name */
	अचिन्हित	eename_size;		/* size of EEPROM name */
	अचिन्हित	eename_pos;		/* Position where it appears at ROM */

	काष्ठा पंचांग6000_capabilities caps;

	क्रमागत		पंचांग6000_devtype type;	/* variant of the chipset */
	पूर्णांक             tuner_type;     /* type of the tuner */
	पूर्णांक             tuner_addr;     /* tuner address */
	पूर्णांक             demod_addr;     /* demodulator address */

	काष्ठा पंचांग6000_gpio gpio;

	काष्ठा पंचांग6000_input	vinput[3];
	काष्ठा पंचांग6000_input	rinput;

	अक्षर		*ir_codes;
पूर्ण;

अटल काष्ठा पंचांग6000_board पंचांग6000_boards[] = अणु
	[TM6000_BOARD_UNKNOWN] = अणु
		.name         = "Unknown tm6000 video grabber",
		.caps = अणु
			.has_tuner	= 1,
			.has_eeprom	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM5600_BOARD_GENERIC] = अणु
		.name         = "Generic tm5600 board",
		.type         = TM5600,
		.tuner_type   = TUNER_XC2028,
		.tuner_addr   = 0xc2 >> 1,
		.caps = अणु
			.has_tuner	= 1,
			.has_eeprom	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6000_BOARD_GENERIC] = अणु
		.name         = "Generic tm6000 board",
		.tuner_type   = TUNER_XC2028,
		.tuner_addr   = 0xc2 >> 1,
		.caps = अणु
			.has_tuner	= 1,
			.has_eeprom	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_GENERIC] = अणु
		.name         = "Generic tm6010 board",
		.type         = TM6010,
		.tuner_type   = TUNER_XC2028,
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.caps = अणु
			.has_tuner	= 1,
			.has_dvb	= 1,
			.has_zl10353	= 1,
			.has_eeprom	= 1,
			.has_remote	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_2,
			.tuner_on	= TM6010_GPIO_3,
			.demod_reset	= TM6010_GPIO_1,
			.demod_on	= TM6010_GPIO_4,
			.घातer_led	= TM6010_GPIO_7,
			.dvb_led	= TM6010_GPIO_5,
			.ir		= TM6010_GPIO_0,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM5600_BOARD_10MOONS_UT821] = अणु
		.name         = "10Moons UT 821",
		.tuner_type   = TUNER_XC2028,
		.eename       = अणु '1', '0', 'M', 'O', 'O', 'N', 'S', '5', '6', '0', '0', 0xff, 0x45, 0x5bपूर्ण,
		.eename_size  = 14,
		.eename_pos   = 0x14,
		.type         = TM5600,
		.tuner_addr   = 0xc2 >> 1,
		.caps = अणु
			.has_tuner    = 1,
			.has_eeprom   = 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM5600_BOARD_10MOONS_UT330] = अणु
		.name         = "10Moons UT 330",
		.tuner_type   = TUNER_PHILIPS_FQ1216AME_MK4,
		.tuner_addr   = 0xc8 >> 1,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 0,
			.has_zl10353  = 0,
			.has_eeprom   = 1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6000_BOARD_ADSTECH_DUAL_TV] = अणु
		.name         = "ADSTECH Dual TV USB",
		.tuner_type   = TUNER_XC2028,
		.tuner_addr   = 0xc8 >> 1,
		.caps = अणु
			.has_tuner    = 1,
			.has_tda9874  = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 1,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6000_BOARD_FREECOM_AND_SIMILAR] = अणु
		.name         = "Freecom Hybrid Stick / Moka DVB-T Receiver Dual",
		.tuner_type   = TUNER_XC2028, /* has a XC3028 */
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 0,
			.has_remote   = 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_4,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6000_BOARD_ADSTECH_MINI_DUAL_TV] = अणु
		.name         = "ADSTECH Mini Dual TV USB",
		.tuner_type   = TUNER_XC2028, /* has a XC3028 */
		.tuner_addr   = 0xc8 >> 1,
		.demod_addr   = 0x1e >> 1,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 0,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6000_GPIO_4,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_HAUPPAUGE_900H] = अणु
		.name         = "Hauppauge WinTV HVR-900H / WinTV USB2-Stick",
		.eename       = अणु 'H', 0, 'V', 0, 'R', 0, '9', 0, '0', 0, '0', 0, 'H', 0 पूर्ण,
		.eename_size  = 14,
		.eename_pos   = 0x42,
		.tuner_type   = TUNER_XC2028, /* has a XC3028 */
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.type         = TM6010,
		.ir_codes = RC_MAP_HAUPPAUGE,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 1,
			.has_remote   = 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_2,
			.tuner_on	= TM6010_GPIO_3,
			.demod_reset	= TM6010_GPIO_1,
			.demod_on	= TM6010_GPIO_4,
			.घातer_led	= TM6010_GPIO_7,
			.dvb_led	= TM6010_GPIO_5,
			.ir		= TM6010_GPIO_0,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_BEHOLD_WANDER] = अणु
		.name         = "Beholder Wander DVB-T/TV/FM USB2.0",
		.tuner_type   = TUNER_XC5000,
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner      = 1,
			.has_dvb        = 1,
			.has_zl10353    = 1,
			.has_eeprom     = 1,
			.has_remote     = 1,
			.has_radio	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_0,
			.demod_reset	= TM6010_GPIO_1,
			.घातer_led	= TM6010_GPIO_6,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
		.rinput = अणु
			.type	= TM6000_INPUT_RADIO,
			.amux	= TM6000_AMUX_ADC1,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_BEHOLD_VOYAGER] = अणु
		.name         = "Beholder Voyager TV/FM USB2.0",
		.tuner_type   = TUNER_XC5000,
		.tuner_addr   = 0xc2 >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner      = 1,
			.has_dvb        = 0,
			.has_zl10353    = 0,
			.has_eeprom     = 1,
			.has_remote     = 1,
			.has_radio	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_0,
			.घातer_led	= TM6010_GPIO_6,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
		.rinput = अणु
			.type	= TM6000_INPUT_RADIO,
			.amux	= TM6000_AMUX_ADC1,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE] = अणु
		.name         = "Terratec Cinergy Hybrid XE / Cinergy Hybrid-Stick",
		.tuner_type   = TUNER_XC2028, /* has a XC3028 */
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 1,
			.has_remote   = 1,
			.has_radio    = 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_2,
			.tuner_on	= TM6010_GPIO_3,
			.demod_reset	= TM6010_GPIO_1,
			.demod_on	= TM6010_GPIO_4,
			.घातer_led	= TM6010_GPIO_7,
			.dvb_led	= TM6010_GPIO_5,
			.ir		= TM6010_GPIO_0,
		पूर्ण,
		.ir_codes = RC_MAP_NEC_TERRATEC_CINERGY_XS,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
		.rinput = अणु
			.type = TM6000_INPUT_RADIO,
			.amux = TM6000_AMUX_SIF1,
		पूर्ण,
	पूर्ण,
	[TM5600_BOARD_TERRATEC_GRABSTER] = अणु
		.name         = "Terratec Grabster AV 150/250 MX",
		.type         = TM5600,
		.tuner_type   = TUNER_ABSENT,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_ADC1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_TWINHAN_TU501] = अणु
		.name         = "Twinhan TU501(704D1)",
		.tuner_type   = TUNER_XC2028, /* has a XC3028 */
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner    = 1,
			.has_dvb      = 1,
			.has_zl10353  = 1,
			.has_eeprom   = 1,
			.has_remote   = 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_2,
			.tuner_on	= TM6010_GPIO_3,
			.demod_reset	= TM6010_GPIO_1,
			.demod_on	= TM6010_GPIO_4,
			.घातer_led	= TM6010_GPIO_7,
			.dvb_led	= TM6010_GPIO_5,
			.ir		= TM6010_GPIO_0,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण, अणु
			.type	= TM6000_INPUT_COMPOSITE1,
			.vmux	= TM6000_VMUX_VIDEO_A,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण, अणु
			.type	= TM6000_INPUT_SVIDEO,
			.vmux	= TM6000_VMUX_VIDEO_AB,
			.amux	= TM6000_AMUX_ADC2,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_BEHOLD_WANDER_LITE] = अणु
		.name         = "Beholder Wander Lite DVB-T/TV/FM USB2.0",
		.tuner_type   = TUNER_XC5000,
		.tuner_addr   = 0xc2 >> 1,
		.demod_addr   = 0x1e >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner      = 1,
			.has_dvb        = 1,
			.has_zl10353    = 1,
			.has_eeprom     = 1,
			.has_remote     = 0,
			.has_radio	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_0,
			.demod_reset	= TM6010_GPIO_1,
			.घातer_led	= TM6010_GPIO_6,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण,
		पूर्ण,
		.rinput = अणु
			.type	= TM6000_INPUT_RADIO,
			.amux	= TM6000_AMUX_ADC1,
		पूर्ण,
	पूर्ण,
	[TM6010_BOARD_BEHOLD_VOYAGER_LITE] = अणु
		.name         = "Beholder Voyager Lite TV/FM USB2.0",
		.tuner_type   = TUNER_XC5000,
		.tuner_addr   = 0xc2 >> 1,
		.type         = TM6010,
		.caps = अणु
			.has_tuner      = 1,
			.has_dvb        = 0,
			.has_zl10353    = 0,
			.has_eeprom     = 1,
			.has_remote     = 0,
			.has_radio	= 1,
		पूर्ण,
		.gpio = अणु
			.tuner_reset	= TM6010_GPIO_0,
			.घातer_led	= TM6010_GPIO_6,
		पूर्ण,
		.vinput = अणु अणु
			.type	= TM6000_INPUT_TV,
			.vmux	= TM6000_VMUX_VIDEO_B,
			.amux	= TM6000_AMUX_SIF1,
			पूर्ण,
		पूर्ण,
		.rinput = अणु
			.type	= TM6000_INPUT_RADIO,
			.amux	= TM6000_AMUX_ADC1,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id पंचांग6000_id_table[] = अणु
	अणु USB_DEVICE(0x6000, 0x0001), .driver_info = TM5600_BOARD_GENERIC पूर्ण,
	अणु USB_DEVICE(0x6000, 0x0002), .driver_info = TM6010_BOARD_GENERIC पूर्ण,
	अणु USB_DEVICE(0x06e1, 0xf332), .driver_info = TM6000_BOARD_ADSTECH_DUAL_TV पूर्ण,
	अणु USB_DEVICE(0x14aa, 0x0620), .driver_info = TM6000_BOARD_FREECOM_AND_SIMILAR पूर्ण,
	अणु USB_DEVICE(0x06e1, 0xb339), .driver_info = TM6000_BOARD_ADSTECH_MINI_DUAL_TV पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6600), .driver_info = TM6010_BOARD_HAUPPAUGE_900H पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6601), .driver_info = TM6010_BOARD_HAUPPAUGE_900H पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6610), .driver_info = TM6010_BOARD_HAUPPAUGE_900H पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6611), .driver_info = TM6010_BOARD_HAUPPAUGE_900H पूर्ण,
	अणु USB_DEVICE(0x6000, 0xdec0), .driver_info = TM6010_BOARD_BEHOLD_WANDER पूर्ण,
	अणु USB_DEVICE(0x6000, 0xdec1), .driver_info = TM6010_BOARD_BEHOLD_VOYAGER पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0086), .driver_info = TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x00A5), .driver_info = TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0079), .driver_info = TM5600_BOARD_TERRATEC_GRABSTER पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3240), .driver_info = TM6010_BOARD_TWINHAN_TU501 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3241), .driver_info = TM6010_BOARD_TWINHAN_TU501 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3243), .driver_info = TM6010_BOARD_TWINHAN_TU501 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3264), .driver_info = TM6010_BOARD_TWINHAN_TU501 पूर्ण,
	अणु USB_DEVICE(0x6000, 0xdec2), .driver_info = TM6010_BOARD_BEHOLD_WANDER_LITE पूर्ण,
	अणु USB_DEVICE(0x6000, 0xdec3), .driver_info = TM6010_BOARD_BEHOLD_VOYAGER_LITE पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, पंचांग6000_id_table);

/* Control घातer led क्रम show some activity */
व्योम पंचांग6000_flash_led(काष्ठा पंचांग6000_core *dev, u8 state)
अणु
	/* Power LED unconfigured */
	अगर (!dev->gpio.घातer_led)
		वापस;

	/* ON Power LED */
	अगर (state) अणु
		चयन (dev->model) अणु
		हाल TM6010_BOARD_HAUPPAUGE_900H:
		हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		हाल TM6010_BOARD_TWINHAN_TU501:
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x00);
			अवरोध;
		हाल TM6010_BOARD_BEHOLD_WANDER:
		हाल TM6010_BOARD_BEHOLD_VOYAGER:
		हाल TM6010_BOARD_BEHOLD_WANDER_LITE:
		हाल TM6010_BOARD_BEHOLD_VOYAGER_LITE:
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x01);
			अवरोध;
		पूर्ण
	पूर्ण
	/* OFF Power LED */
	अन्यथा अणु
		चयन (dev->model) अणु
		हाल TM6010_BOARD_HAUPPAUGE_900H:
		हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		हाल TM6010_BOARD_TWINHAN_TU501:
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x01);
			अवरोध;
		हाल TM6010_BOARD_BEHOLD_WANDER:
		हाल TM6010_BOARD_BEHOLD_VOYAGER:
		हाल TM6010_BOARD_BEHOLD_WANDER_LITE:
		हाल TM6010_BOARD_BEHOLD_VOYAGER_LITE:
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x00);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Tuner callback to provide the proper gpio changes needed क्रम xc5000 */
पूर्णांक पंचांग6000_xc5000_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा पंचांग6000_core *dev = ptr;

	अगर (dev->tuner_type != TUNER_XC5000)
		वापस 0;

	चयन (command) अणु
	हाल XC5000_TUNER_RESET:
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x01);
		msleep(15);
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x00);
		msleep(15);
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x01);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_xc5000_callback);

/* Tuner callback to provide the proper gpio changes needed क्रम xc2028 */

पूर्णांक पंचांग6000_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा पंचांग6000_core *dev = ptr;

	अगर (dev->tuner_type != TUNER_XC2028)
		वापस 0;

	चयन (command) अणु
	हाल XC2028_RESET_CLK:
		पंचांग6000_ir_रुको(dev, 0);

		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT,
					0x02, arg);
		msleep(10);
		rc = पंचांग6000_i2c_reset(dev, 10);
		अवरोध;
	हाल XC2028_TUNER_RESET:
		/* Reset codes during load firmware */
		चयन (arg) अणु
		हाल 0:
			/* newer tuner can faster reset */
			चयन (dev->model) अणु
			हाल TM5600_BOARD_10MOONS_UT821:
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x01);
				msleep(10);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x00);
				msleep(10);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x01);
				अवरोध;
			हाल TM6010_BOARD_HAUPPAUGE_900H:
			हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
			हाल TM6010_BOARD_TWINHAN_TU501:
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(60);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				msleep(75);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(60);
				अवरोध;
			शेष:
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				msleep(130);
				पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(130);
				अवरोध;
			पूर्ण

			पंचांग6000_ir_रुको(dev, 1);
			अवरोध;
		हाल 1:
			पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT,
						0x02, 0x01);
			msleep(10);
			अवरोध;
		हाल 2:
			rc = पंचांग6000_i2c_reset(dev, 100);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल XC2028_I2C_FLUSH:
		पंचांग6000_set_reg(dev, REQ_50_SET_START, 0, 0);
		पंचांग6000_set_reg(dev, REQ_51_SET_STOP, 0, 0);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_tuner_callback);

पूर्णांक पंचांग6000_cards_setup(काष्ठा पंचांग6000_core *dev)
अणु
	/*
	 * Board-specअगरic initialization sequence. Handles all GPIO
	 * initialization sequences that are board-specअगरic.
	 * Up to now, all found devices use GPIO1 and GPIO4 at the same way.
	 * Probably, they're all based on some reference device. Due to that,
	 * there's a common routine at the end to handle those GPIO's. Devices
	 * that use dअगरferent pinups or init sequences can just वापस at
	 * the board-specअगरic session.
	 */
	चयन (dev->model) अणु
	हाल TM6010_BOARD_HAUPPAUGE_900H:
	हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
	हाल TM6010_BOARD_TWINHAN_TU501:
	हाल TM6010_BOARD_GENERIC:
		/* Turn xceive 3028 on */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.tuner_on, 0x01);
		msleep(15);
		/* Turn zarlink zl10353 on */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_on, 0x00);
		msleep(15);
		/* Reset zarlink zl10353 */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_reset, 0x00);
		msleep(50);
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_reset, 0x01);
		msleep(15);
		/* Turn zarlink zl10353 off */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_on, 0x01);
		msleep(15);
		/* ir ? */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.ir, 0x01);
		msleep(15);
		/* Power led on (blue) */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.घातer_led, 0x00);
		msleep(15);
		/* DVB led off (orange) */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.dvb_led, 0x01);
		msleep(15);
		/* Turn zarlink zl10353 on */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_on, 0x00);
		msleep(15);
		अवरोध;
	हाल TM6010_BOARD_BEHOLD_WANDER:
	हाल TM6010_BOARD_BEHOLD_WANDER_LITE:
		/* Power led on (blue) */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.घातer_led, 0x01);
		msleep(15);
		/* Reset zarlink zl10353 */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_reset, 0x00);
		msleep(50);
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.demod_reset, 0x01);
		msleep(15);
		अवरोध;
	हाल TM6010_BOARD_BEHOLD_VOYAGER:
	हाल TM6010_BOARD_BEHOLD_VOYAGER_LITE:
		/* Power led on (blue) */
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, dev->gpio.घातer_led, 0x01);
		msleep(15);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Default initialization. Most of the devices seem to use GPIO1
	 * and GPIO4.on the same way, so, this handles the common sequence
	 * used by most devices.
	 * If a device uses a dअगरferent sequence or dअगरferent GPIO pins क्रम
	 * reset, just add the code at the board-specअगरic part
	 */

	अगर (dev->gpio.tuner_reset) अणु
		पूर्णांक rc;
		पूर्णांक i;

		क्रम (i = 0; i < 2; i++) अणु
			rc = पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
						dev->gpio.tuner_reset, 0x00);
			अगर (rc < 0) अणु
				prपूर्णांकk(KERN_ERR "Error %i doing tuner reset\n", rc);
				वापस rc;
			पूर्ण

			msleep(10); /* Just to be conservative */
			rc = पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
						dev->gpio.tuner_reset, 0x01);
			अगर (rc < 0) अणु
				prपूर्णांकk(KERN_ERR "Error %i doing tuner reset\n", rc);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Tuner reset is not configured\n");
		वापस -1;
	पूर्ण

	msleep(50);

	वापस 0;
पूर्ण;

अटल व्योम पंचांग6000_config_tuner(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा tuner_setup tun_setup;

	/* Load tuner module */
	v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
		"tuner", dev->tuner_addr, शून्य);

	स_रखो(&tun_setup, 0, माप(tun_setup));
	tun_setup.type = dev->tuner_type;
	tun_setup.addr = dev->tuner_addr;

	tun_setup.mode_mask = 0;
	अगर (dev->caps.has_tuner)
		tun_setup.mode_mask |= (T_ANALOG_TV | T_RADIO);

	चयन (dev->tuner_type) अणु
	हाल TUNER_XC2028:
		tun_setup.tuner_callback = पंचांग6000_tuner_callback;
		अवरोध;
	हाल TUNER_XC5000:
		tun_setup.tuner_callback = पंचांग6000_xc5000_callback;
		अवरोध;
	पूर्ण

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_type_addr, &tun_setup);

	चयन (dev->tuner_type) अणु
	हाल TUNER_XC2028: अणु
		काष्ठा v4l2_priv_tun_config xc2028_cfg;
		काष्ठा xc2028_ctrl ctl;

		स_रखो(&xc2028_cfg, 0, माप(xc2028_cfg));
		स_रखो(&ctl, 0, माप(ctl));

		ctl.demod = XC3028_FE_ZARLINK456;

		xc2028_cfg.tuner = TUNER_XC2028;
		xc2028_cfg.priv  = &ctl;

		चयन (dev->model) अणु
		हाल TM6010_BOARD_HAUPPAUGE_900H:
		हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		हाल TM6010_BOARD_TWINHAN_TU501:
			ctl.max_len = 80;
			ctl.fname = "xc3028L-v36.fw";
			अवरोध;
		शेष:
			अगर (dev->dev_type == TM6010)
				ctl.fname = "xc3028-v27.fw";
			अन्यथा
				ctl.fname = "xc3028-v24.fw";
		पूर्ण

		prपूर्णांकk(KERN_INFO "Setting firmware parameters for xc2028\n");
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_config,
				     &xc2028_cfg);

		पूर्ण
		अवरोध;
	हाल TUNER_XC5000:
		अणु
		काष्ठा v4l2_priv_tun_config  xc5000_cfg;
		काष्ठा xc5000_config ctl = अणु
			.i2c_address = dev->tuner_addr,
			.अगर_khz      = 4570,
			.radio_input = XC5000_RADIO_FM1_MONO,
			पूर्ण;

		xc5000_cfg.tuner = TUNER_XC5000;
		xc5000_cfg.priv  = &ctl;

		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_config,
				     &xc5000_cfg);
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unknown tuner type. Tuner is not configured.\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fill_board_specअगरic_data(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक rc;

	dev->dev_type   = पंचांग6000_boards[dev->model].type;
	dev->tuner_type = पंचांग6000_boards[dev->model].tuner_type;
	dev->tuner_addr = पंचांग6000_boards[dev->model].tuner_addr;

	dev->gpio = पंचांग6000_boards[dev->model].gpio;

	dev->ir_codes = पंचांग6000_boards[dev->model].ir_codes;

	dev->demod_addr = पंचांग6000_boards[dev->model].demod_addr;

	dev->caps = पंचांग6000_boards[dev->model].caps;

	dev->vinput[0] = पंचांग6000_boards[dev->model].vinput[0];
	dev->vinput[1] = पंचांग6000_boards[dev->model].vinput[1];
	dev->vinput[2] = पंचांग6000_boards[dev->model].vinput[2];
	dev->rinput = पंचांग6000_boards[dev->model].rinput;

	/* setup per-model quirks */
	चयन (dev->model) अणु
	हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
	हाल TM6010_BOARD_HAUPPAUGE_900H:
		dev->quirks |= TM6000_QUIRK_NO_USB_DELAY;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* initialize hardware */
	rc = पंचांग6000_init(dev);
	अगर (rc < 0)
		वापस rc;

	वापस v4l2_device_रेजिस्टर(&dev->udev->dev, &dev->v4l2_dev);
पूर्ण


अटल व्योम use_alternative_detection_method(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक i, model = -1;

	अगर (!dev->eedata_size)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांग6000_boards); i++) अणु
		अगर (!पंचांग6000_boards[i].eename_size)
			जारी;
		अगर (dev->eedata_size < पंचांग6000_boards[i].eename_pos +
				       पंचांग6000_boards[i].eename_size)
			जारी;

		अगर (!स_भेद(&dev->eedata[पंचांग6000_boards[i].eename_pos],
			    पंचांग6000_boards[i].eename,
			    पंचांग6000_boards[i].eename_size)) अणु
			model = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (model < 0) अणु
		prपूर्णांकk(KERN_INFO "Device has eeprom but is currently unknown\n");
		वापस;
	पूर्ण

	dev->model = model;

	prपूर्णांकk(KERN_INFO "Device identified via eeprom as %s (type = %d)\n",
	       पंचांग6000_boards[model].name, model);
पूर्ण

#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांग6000_core *dev = container_of(work, काष्ठा पंचांग6000_core,
					       request_module_wk);

	request_module("tm6000-alsa");

	अगर (dev->caps.has_dvb)
		request_module("tm6000-dvb");
पूर्ण

अटल व्योम request_modules(काष्ठा पंचांग6000_core *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा पंचांग6000_core *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev)
#पूर्ण_अगर /* CONFIG_MODULES */

अटल पूर्णांक पंचांग6000_init_dev(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा v4l2_frequency f;
	पूर्णांक rc = 0;

	mutex_init(&dev->lock);
	mutex_lock(&dev->lock);

	अगर (!is_generic(dev->model)) अणु
		rc = fill_board_specअगरic_data(dev);
		अगर (rc < 0)
			जाओ err;

		/* रेजिस्टर i2c bus */
		rc = पंचांग6000_i2c_रेजिस्टर(dev);
		अगर (rc < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		/* रेजिस्टर i2c bus */
		rc = पंचांग6000_i2c_रेजिस्टर(dev);
		अगर (rc < 0)
			जाओ err;

		use_alternative_detection_method(dev);

		rc = fill_board_specअगरic_data(dev);
		अगर (rc < 0)
			जाओ err;
	पूर्ण

	/* Default values क्रम STD and resolutions */
	dev->width = 720;
	dev->height = 480;
	dev->norm = V4L2_STD_NTSC_M;

	/* Configure tuner */
	पंचांग6000_config_tuner(dev);

	/* Set video standard */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, dev->norm);

	/* Set tuner frequency - also loads firmware on xc2028/xc3028 */
	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 3092;	/* 193.25 MHz */
	dev->freq = f.frequency;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, &f);

	अगर (dev->caps.has_tda9874)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"tvaudio", I2C_ADDR_TDA9874, शून्य);

	/* रेजिस्टर and initialize V4L2 */
	rc = पंचांग6000_v4l2_रेजिस्टर(dev);
	अगर (rc < 0)
		जाओ err;

	पंचांग6000_add_पूर्णांकo_devlist(dev);
	पंचांग6000_init_extension(dev);

	पंचांग6000_ir_init(dev);

	request_modules(dev);

	mutex_unlock(&dev->lock);
	वापस 0;

err:
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

/* high bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
#घोषणा hb_mult(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))

अटल व्योम get_max_endpoपूर्णांक(काष्ठा usb_device *udev,
			     काष्ठा usb_host_पूर्णांकerface *alt,
			     अक्षर *msgtype,
			     काष्ठा usb_host_endpoपूर्णांक *curr_e,
			     काष्ठा पंचांग6000_endpoपूर्णांक *पंचांग_ep)
अणु
	u16 पंचांगp = le16_to_cpu(curr_e->desc.wMaxPacketSize);
	अचिन्हित पूर्णांक size = पंचांगp & 0x7ff;

	अगर (udev->speed == USB_SPEED_HIGH)
		size = size * hb_mult(पंचांगp);

	अगर (size > पंचांग_ep->maxsize) अणु
		पंचांग_ep->endp = curr_e;
		पंचांग_ep->maxsize = size;
		पंचांग_ep->bInterfaceNumber = alt->desc.bInterfaceNumber;
		पंचांग_ep->bAlternateSetting = alt->desc.bAlternateSetting;

		prपूर्णांकk(KERN_INFO "tm6000: %s endpoint: 0x%02x (max size=%u bytes)\n",
					msgtype, curr_e->desc.bEndpoपूर्णांकAddress,
					size);
	पूर्ण
पूर्ण

/*
 * पंचांग6000_usb_probe()
 * checks क्रम supported devices
 */
अटल पूर्णांक पंचांग6000_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev;
	काष्ठा पंचांग6000_core *dev;
	पूर्णांक i, rc;
	पूर्णांक nr = 0;
	अक्षर *speed;

	usbdev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* Selects the proper पूर्णांकerface */
	rc = usb_set_पूर्णांकerface(usbdev, 0, 1);
	अगर (rc < 0)
		जाओ report_failure;

	/* Check to see next मुक्त device and mark as used */
	nr = find_first_zero_bit(&पंचांग6000_devused, TM6000_MAXBOARDS);
	अगर (nr >= TM6000_MAXBOARDS) अणु
		prपूर्णांकk(KERN_ERR "tm6000: Supports only %i tm60xx boards.\n", TM6000_MAXBOARDS);
		rc = -ENOMEM;
		जाओ put_device;
	पूर्ण

	/* Create and initialize dev काष्ठा */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		rc = -ENOMEM;
		जाओ put_device;
	पूर्ण
	spin_lock_init(&dev->slock);
	mutex_init(&dev->usb_lock);

	/* Increment usage count */
	set_bit(nr, &पंचांग6000_devused);
	snम_लिखो(dev->name, 29, "tm6000 #%d", nr);

	dev->model = id->driver_info;
	अगर (card[nr] < ARRAY_SIZE(पंचांग6000_boards))
		dev->model = card[nr];

	dev->udev = usbdev;
	dev->devno = nr;

	चयन (usbdev->speed) अणु
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

	/* Get endpoपूर्णांकs */
	क्रम (i = 0; i < पूर्णांकerface->num_altsetting; i++) अणु
		पूर्णांक ep;

		क्रम (ep = 0; ep < पूर्णांकerface->altsetting[i].desc.bNumEndpoपूर्णांकs; ep++) अणु
			काष्ठा usb_host_endpoपूर्णांक	*e;
			पूर्णांक dir_out;

			e = &पूर्णांकerface->altsetting[i].endpoपूर्णांक[ep];

			dir_out = ((e->desc.bEndpoपूर्णांकAddress &
					USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT);

			prपूर्णांकk(KERN_INFO "tm6000: alt %d, interface %i, class %i\n",
			       i,
			       पूर्णांकerface->altsetting[i].desc.bInterfaceNumber,
			       पूर्णांकerface->altsetting[i].desc.bInterfaceClass);

			चयन (e->desc.bmAttributes) अणु
			हाल USB_ENDPOINT_XFER_BULK:
				अगर (!dir_out) अणु
					get_max_endpoपूर्णांक(usbdev,
							 &पूर्णांकerface->altsetting[i],
							 "Bulk IN", e,
							 &dev->bulk_in);
				पूर्ण अन्यथा अणु
					get_max_endpoपूर्णांक(usbdev,
							 &पूर्णांकerface->altsetting[i],
							 "Bulk OUT", e,
							 &dev->bulk_out);
				पूर्ण
				अवरोध;
			हाल USB_ENDPOINT_XFER_ISOC:
				अगर (!dir_out) अणु
					get_max_endpoपूर्णांक(usbdev,
							 &पूर्णांकerface->altsetting[i],
							 "ISOC IN", e,
							 &dev->isoc_in);
				पूर्ण अन्यथा अणु
					get_max_endpoपूर्णांक(usbdev,
							 &पूर्णांकerface->altsetting[i],
							 "ISOC OUT", e,
							 &dev->isoc_out);
				पूर्ण
				अवरोध;
			हाल USB_ENDPOINT_XFER_INT:
				अगर (!dir_out) अणु
					get_max_endpoपूर्णांक(usbdev,
							&पूर्णांकerface->altsetting[i],
							"INT IN", e,
							&dev->पूर्णांक_in);
				पूर्ण अन्यथा अणु
					get_max_endpoपूर्णांक(usbdev,
							&पूर्णांकerface->altsetting[i],
							"INT OUT", e,
							&dev->पूर्णांक_out);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण


	prपूर्णांकk(KERN_INFO "tm6000: New video device @ %s Mbps (%04x:%04x, ifnum %d)\n",
		speed,
		le16_to_cpu(dev->udev->descriptor.idVenकरोr),
		le16_to_cpu(dev->udev->descriptor.idProduct),
		पूर्णांकerface->altsetting->desc.bInterfaceNumber);

/* check अगर the the device has the iso in endpoपूर्णांक at the correct place */
	अगर (!dev->isoc_in.endp) अणु
		prपूर्णांकk(KERN_ERR "tm6000: probing error: no IN ISOC endpoint!\n");
		rc = -ENODEV;
		जाओ मुक्त_device;
	पूर्ण

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	prपूर्णांकk(KERN_INFO "tm6000: Found %s\n", पंचांग6000_boards[dev->model].name);

	rc = पंचांग6000_init_dev(dev);
	अगर (rc < 0)
		जाओ मुक्त_device;

	वापस 0;

मुक्त_device:
	kमुक्त(dev);
report_failure:
	prपूर्णांकk(KERN_ERR "tm6000: Error %d while registering\n", rc);

	clear_bit(nr, &पंचांग6000_devused);
put_device:
	usb_put_dev(usbdev);
	वापस rc;
पूर्ण

/*
 * पंचांग6000_usb_disconnect()
 * called when the device माला_लो disconnected
 * video device will be unरेजिस्टरed on v4l2_बंद in हाल it is still खोलो
 */
अटल व्योम पंचांग6000_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा पंचांग6000_core *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	अगर (!dev)
		वापस;

	prपूर्णांकk(KERN_INFO "tm6000: disconnecting %s\n", dev->name);

	flush_request_modules(dev);

	पंचांग6000_ir_fini(dev);

	अगर (dev->gpio.घातer_led) अणु
		चयन (dev->model) अणु
		हाल TM6010_BOARD_HAUPPAUGE_900H:
		हाल TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		हाल TM6010_BOARD_TWINHAN_TU501:
			/* Power led off */
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x01);
			msleep(15);
			अवरोध;
		हाल TM6010_BOARD_BEHOLD_WANDER:
		हाल TM6010_BOARD_BEHOLD_VOYAGER:
		हाल TM6010_BOARD_BEHOLD_WANDER_LITE:
		हाल TM6010_BOARD_BEHOLD_VOYAGER_LITE:
			/* Power led off */
			पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.घातer_led, 0x00);
			msleep(15);
			अवरोध;
		पूर्ण
	पूर्ण
	पंचांग6000_v4l2_unरेजिस्टर(dev);

	पंचांग6000_i2c_unरेजिस्टर(dev);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	dev->state |= DEV_DISCONNECTED;

	usb_put_dev(dev->udev);

	पंचांग6000_बंद_extension(dev);
	पंचांग6000_हटाओ_from_devlist(dev);

	clear_bit(dev->devno, &पंचांग6000_devused);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा usb_driver पंचांग6000_usb_driver = अणु
		.name = "tm6000",
		.probe = पंचांग6000_usb_probe,
		.disconnect = पंचांग6000_usb_disconnect,
		.id_table = पंचांग6000_id_table,
पूर्ण;

module_usb_driver(पंचांग6000_usb_driver);

MODULE_DESCRIPTION("Trident TVMaster TM5600/TM6000/TM6010 USB2 adapter");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");
