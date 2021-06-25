<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <media/drv-पूर्णांकf/cx25840.h>
#समावेश <linux/firmware.h>
#समावेश <misc/altera.h>

#समावेश "tuner-xc2028.h"
#समावेश "netup-eeprom.h"
#समावेश "netup-init.h"
#समावेश "altera-ci.h"
#समावेश "xc4000.h"
#समावेश "xc5000.h"
#समावेश "cx23888-ir.h"

अटल अचिन्हित पूर्णांक netup_card_rev = 4;
module_param(netup_card_rev, पूर्णांक, 0644);
MODULE_PARM_DESC(netup_card_rev,
		"NetUP Dual DVB-T/C CI card revision");
अटल अचिन्हित पूर्णांक enable_885_ir;
module_param(enable_885_ir, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_885_ir,
		 "Enable integrated IR controller for supported\n"
		 "\t\t    CX2388[57] boards that are wired for it:\n"
		 "\t\t\tHVR-1250 (reported safe)\n"
		 "\t\t\tTerraTec Cinergy T PCIe Dual (not well tested, appears to be safe)\n"
		 "\t\t\tTeVii S470 (reported unsafe)\n"
		 "\t\t    This can cause an interrupt storm with some cards.\n"
		 "\t\t    Default: 0 [Disabled]");

/* ------------------------------------------------------------------ */
/* board config info                                                  */

काष्ठा cx23885_board cx23885_boards[] = अणु
	[CX23885_BOARD_UNKNOWN] = अणु
		.name		= "UNKNOWN/GENERIC",
		/* Ensure safe शेष क्रम unknown boards */
		.clk_freq       = 0,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE2,
			.vmux   = 1,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE3,
			.vmux   = 2,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE4,
			.vmux   = 3,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1800lp] = अणु
		.name		= "Hauppauge WinTV-HVR1800lp",
		.portc		= CX23885_MPEG_DVB,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xff00,
		पूर्ण, अणु
			.type   = CX23885_VMUX_DEBUG,
			.vmux   = 0,
			.gpio0  = 0xff01,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0xff02,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0xff02,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1800] = अणु
		.name		= "Hauppauge WinTV-HVR1800",
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_ENCODER,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_PHILIPS_TDA8290,
		.tuner_addr	= 0x42, /* 0x84 >> 1 */
		.tuner_bus	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1,
			.amux   = CX25840_AUDIO8,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1250] = अणु
		.name		= "Hauppauge WinTV-HVR1250",
		.porta		= CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
#अगर_घोषित MT2131_NO_ANALOG_SUPPORT_YET
		.tuner_type	= TUNER_PHILIPS_TDA8290,
		.tuner_addr	= 0x42, /* 0x84 >> 1 */
		.tuner_bus	= 1,
#पूर्ण_अगर
		.क्रमce_bff	= 1,
		.input          = अणुअणु
#अगर_घोषित MT2131_NO_ANALOG_SUPPORT_YET
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1,
			.amux   = CX25840_AUDIO8,
			.gpio0  = 0xff00,
		पूर्ण, अणु
#पूर्ण_अगर
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0xff02,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0xff02,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP] = अणु
		.name		= "DViCO FusionHDTV5 Express",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1500Q] = अणु
		.name		= "Hauppauge WinTV-HVR1500Q",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1500] = अणु
		.name		= "Hauppauge WinTV-HVR1500",
		.porta		= CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_XC2028,
		.tuner_addr	= 0x61, /* 0xc2 >> 1 */
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.gpio0  = 0,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1200] = अणु
		.name		= "Hauppauge WinTV-HVR1200",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1700] = अणु
		.name		= "Hauppauge WinTV-HVR1700",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1400] = अणु
		.name		= "Hauppauge WinTV-HVR1400",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP] = अणु
		.name		= "DViCO FusionHDTV7 Dual Express",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP] = अणु
		.name		= "DViCO FusionHDTV DVB-T Dual Express",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H] = अणु
		.name		= "Leadtek Winfast PxDVR3200 H",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200] = अणु
		.name		= "Leadtek Winfast PxPVR2200",
		.porta		= CX23885_ANALOG_VIDEO,
		.tuner_type	= TUNER_XC2028,
		.tuner_addr	= 0x61,
		.tuner_bus	= 1,
		.input		= अणुअणु
			.type	= CX23885_VMUX_TELEVISION,
			.vmux	= CX25840_VIN2_CH1 |
				  CX25840_VIN5_CH2,
			.amux	= CX25840_AUDIO8,
			.gpio0	= 0x704040,
		पूर्ण, अणु
			.type	= CX23885_VMUX_COMPOSITE1,
			.vmux	= CX25840_COMPOSITE1,
			.amux	= CX25840_AUDIO7,
			.gpio0	= 0x704040,
		पूर्ण, अणु
			.type	= CX23885_VMUX_SVIDEO,
			.vmux	= CX25840_SVIDEO_LUMA3 |
				  CX25840_SVIDEO_CHROMA4,
			.amux	= CX25840_AUDIO7,
			.gpio0	= 0x704040,
		पूर्ण, अणु
			.type	= CX23885_VMUX_COMPONENT,
			.vmux	= CX25840_VIN7_CH1 |
				  CX25840_VIN6_CH2 |
				  CX25840_VIN8_CH3 |
				  CX25840_COMPONENT_ON,
			.amux	= CX25840_AUDIO7,
			.gpio0	= 0x704040,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000] = अणु
		.name		= "Leadtek Winfast PxDVR3200 H XC4000",
		.porta		= CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_XC4000,
		.tuner_addr	= 0x61,
		.radio_type	= UNSET,
		.radio_addr	= ADDR_UNSET,
		.input		= अणुअणु
			.type	= CX23885_VMUX_TELEVISION,
			.vmux	= CX25840_VIN2_CH1 |
				  CX25840_VIN5_CH2 |
				  CX25840_NONE0_CH3,
		पूर्ण, अणु
			.type	= CX23885_VMUX_COMPOSITE1,
			.vmux	= CX25840_COMPOSITE1,
		पूर्ण, अणु
			.type	= CX23885_VMUX_SVIDEO,
			.vmux	= CX25840_SVIDEO_LUMA3 |
				  CX25840_SVIDEO_CHROMA4,
		पूर्ण, अणु
			.type	= CX23885_VMUX_COMPONENT,
			.vmux	= CX25840_VIN7_CH1 |
				  CX25840_VIN6_CH2 |
				  CX25840_VIN8_CH3 |
				  CX25840_COMPONENT_ON,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_COMPRO_VIDEOMATE_E650F] = अणु
		.name		= "Compro VideoMate E650F",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TBS_6920] = अणु
		.name		= "TurboSight TBS 6920",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TBS_6980] = अणु
		.name		= "TurboSight TBS 6980",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TBS_6981] = अणु
		.name		= "TurboSight TBS 6981",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TEVII_S470] = अणु
		.name		= "TeVii S470",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBWORLD_2005] = अणु
		.name		= "DVBWorld DVB-S2 2005",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_NETUP_DUAL_DVBS2_CI] = अणु
		.ci_type	= 1,
		.name		= "NetUP Dual DVB-S2 CI",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1270] = अणु
		.name		= "Hauppauge WinTV-HVR1270",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1275] = अणु
		.name		= "Hauppauge WinTV-HVR1275",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1255] = अणु
		.name		= "Hauppauge WinTV-HVR1255",
		.porta		= CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= 0x42, /* 0x84 >> 1 */
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1255_22111] = अणु
		.name		= "Hauppauge WinTV-HVR1255",
		.porta		= CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= 0x42, /* 0x84 >> 1 */
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1210] = अणु
		.name		= "Hauppauge WinTV-HVR1210",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_MYGICA_X8506] = अणु
		.name		= "Mygica X8506 DMB-TH",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_bus	= 1,
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.input		= अणु
			अणु
				.type   = CX23885_VMUX_TELEVISION,
				.vmux   = CX25840_COMPOSITE2,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPOSITE1,
				.vmux   = CX25840_COMPOSITE8,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_SVIDEO,
				.vmux   = CX25840_SVIDEO_LUMA3 |
						CX25840_SVIDEO_CHROMA4,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPONENT,
				.vmux   = CX25840_COMPONENT_ON |
					CX25840_VIN1_CH1 |
					CX25840_VIN6_CH2 |
					CX25840_VIN7_CH3,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[CX23885_BOARD_MAGICPRO_PROHDTVE2] = अणु
		.name		= "Magic-Pro ProHDTV Extreme 2",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_bus	= 1,
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.input		= अणु
			अणु
				.type   = CX23885_VMUX_TELEVISION,
				.vmux   = CX25840_COMPOSITE2,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPOSITE1,
				.vmux   = CX25840_COMPOSITE8,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_SVIDEO,
				.vmux   = CX25840_SVIDEO_LUMA3 |
						CX25840_SVIDEO_CHROMA4,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPONENT,
				.vmux   = CX25840_COMPONENT_ON |
					CX25840_VIN1_CH1 |
					CX25840_VIN6_CH2 |
					CX25840_VIN7_CH3,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1850] = अणु
		.name		= "Hauppauge WinTV-HVR1850",
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_ENCODER,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= 0x42, /* 0x84 >> 1 */
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN4_CH2 |
					CX25840_VIN8_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_COMPRO_VIDEOMATE_E800] = अणु
		.name		= "Compro VideoMate E800",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1290] = अणु
		.name		= "Hauppauge WinTV-HVR1290",
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_MYGICA_X8558PRO] = अणु
		.name		= "Mygica X8558 PRO DMB-TH",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_LEADTEK_WINFAST_PXTV1200] = अणु
		.name           = "LEADTEK WinFast PxTV1200",
		.porta          = CX23885_ANALOG_VIDEO,
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.tuner_bus	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   = CX25840_VIN2_CH1 |
				  CX25840_VIN5_CH2 |
				  CX25840_NONE0_CH3,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_COMPOSITE1,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_SVIDEO_LUMA3 |
				  CX25840_SVIDEO_CHROMA4,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPONENT,
			.vmux   = CX25840_VIN7_CH1 |
				  CX25840_VIN6_CH2 |
				  CX25840_VIN8_CH3 |
				  CX25840_COMPONENT_ON,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_GOTVIEW_X5_3D_HYBRID] = अणु
		.name		= "GoTView X5 3D Hybrid",
		.tuner_type	= TUNER_XC5000,
		.tuner_addr	= 0x64,
		.tuner_bus	= 1,
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   = CX25840_VIN2_CH1 |
				  CX25840_VIN5_CH2,
			.gpio0	= 0x02,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX23885_VMUX_COMPOSITE1,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_SVIDEO_LUMA3 |
				  CX25840_SVIDEO_CHROMA4,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF] = अणु
		.ci_type	= 2,
		.name		= "NetUP Dual DVB-T/C-CI RF",
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
		.num_fds_portb	= 2,
		.num_fds_portc	= 2,
		.tuner_type	= TUNER_XC5000,
		.tuner_addr	= 0x64,
		.input          = अणु अणु
				.type   = CX23885_VMUX_TELEVISION,
				.vmux   = CX25840_COMPOSITE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_MPX885] = अणु
		.name		= "MPX-885",
		.porta		= CX23885_ANALOG_VIDEO,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_COMPOSITE1,
			.amux   = CX25840_AUDIO6,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE2,
			.vmux   = CX25840_COMPOSITE2,
			.amux   = CX25840_AUDIO6,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE3,
			.vmux   = CX25840_COMPOSITE3,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE4,
			.vmux   = CX25840_COMPOSITE4,
			.amux   = CX25840_AUDIO7,
			.gpio0  = 0,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_MYGICA_X8507] = अणु
		.name		= "Mygica X8502/X8507 ISDB-T",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.tuner_bus	= 1,
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.input		= अणु
			अणु
				.type   = CX23885_VMUX_TELEVISION,
				.vmux   = CX25840_COMPOSITE2,
				.amux   = CX25840_AUDIO8,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPOSITE1,
				.vmux   = CX25840_COMPOSITE8,
				.amux   = CX25840_AUDIO7,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_SVIDEO,
				.vmux   = CX25840_SVIDEO_LUMA3 |
						CX25840_SVIDEO_CHROMA4,
				.amux   = CX25840_AUDIO7,
			पूर्ण,
			अणु
				.type   = CX23885_VMUX_COMPONENT,
				.vmux   = CX25840_COMPONENT_ON |
					CX25840_VIN1_CH1 |
					CX25840_VIN6_CH2 |
					CX25840_VIN7_CH3,
				.amux   = CX25840_AUDIO7,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL] = अणु
		.name		= "TerraTec Cinergy T PCIe Dual",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TEVII_S471] = अणु
		.name		= "TeVii S471",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_PROF_8000] = अणु
		.name		= "Prof Revolution DVB-S2 8000",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR4400] = अणु
		.name		= "Hauppauge WinTV-HVR4400/HVR5500",
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_NXP_TDA18271,
		.tuner_addr	= 0x60, /* 0xc0 >> 1 */
		.tuner_bus	= 1,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_STARBURST] = अणु
		.name		= "Hauppauge WinTV Starburst",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_AVERMEDIA_HC81R] = अणु
		.name		= "AVerTV Hybrid Express Slim HC81R",
		.tuner_type	= TUNER_XC2028,
		.tuner_addr	= 0x61, /* 0xc2 >> 1 */
		.tuner_bus	= 1,
		.porta		= CX23885_ANALOG_VIDEO,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   = CX25840_VIN2_CH1 |
				  CX25840_VIN5_CH2 |
				  CX25840_NONE0_CH3 |
				  CX25840_NONE1_CH3,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN8_CH1 |
				  CX25840_NONE_CH2 |
				  CX25840_VIN7_CH3 |
				  CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO6,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPONENT,
			.vmux   = CX25840_VIN1_CH1 |
				  CX25840_NONE_CH2 |
				  CX25840_NONE0_CH3 |
				  CX25840_NONE1_CH3,
			.amux   = CX25840_AUDIO6,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2] = अणु
		.name		= "DViCO FusionHDTV DVB-T Dual Express2",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_IMPACTVCBE] = अणु
		.name		= "Hauppauge ImpactVCB-e",
		.tuner_type	= TUNER_ABSENT,
		.porta		= CX23885_ANALOG_VIDEO,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN4_CH2 |
				  CX25840_VIN8_CH1 |
				  CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_T9580] = अणु
		.name		= "DVBSky T9580",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_T980C] = अणु
		.name		= "DVBSky T980C",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_S950C] = अणु
		.name		= "DVBSky S950C",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_TT_CT2_4500_CI] = अणु
		.name		= "Technotrend TT-budget CT2-4500 CI",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_S950] = अणु
		.name		= "DVBSky S950",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_S952] = अणु
		.name		= "DVBSky S952",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_DVBSKY_T982] = अणु
		.name		= "DVBSky T982",
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR5525] = अणु
		.name		= "Hauppauge WinTV-HVR5525",
		.porta		= CX23885_ANALOG_VIDEO,
		.portb		= CX23885_MPEG_DVB,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.क्रमce_bff	= 1,
		.input		= अणुअणु
			.type	= CX23885_VMUX_TELEVISION,
			.vmux	=	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN7_CH3 |
				  CX25840_VIN8_CH1 |
				  CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_VIEWCAST_260E] = अणु
		.name		= "ViewCast 260e",
		.porta		= CX23885_ANALOG_VIDEO,
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN7_CH3 |
					CX25840_VIN5_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPONENT,
			.vmux   = CX25840_VIN7_CH3 |
					CX25840_VIN6_CH2 |
					CX25840_VIN5_CH1 |
					CX25840_COMPONENT_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_VIEWCAST_460E] = अणु
		.name		= "ViewCast 460e",
		.porta		= CX23885_ANALOG_VIDEO,
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_VIN4_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN7_CH3 |
					CX25840_VIN6_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPONENT,
			.vmux   = CX25840_VIN7_CH3 |
					CX25840_VIN6_CH1 |
					CX25840_VIN5_CH2 |
					CX25840_COMPONENT_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_COMPOSITE2,
			.vmux   = CX25840_VIN6_CH1,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_QUADHD_DVB] = अणु
		.name         = "Hauppauge WinTV-QuadHD-DVB",
		.porta        = CX23885_ANALOG_VIDEO,
		.portb        = CX23885_MPEG_DVB,
		.portc        = CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885] = अणु
		.name         = "Hauppauge WinTV-QuadHD-DVB(885)",
		.portb        = CX23885_MPEG_DVB,
		.portc        = CX23885_MPEG_DVB,
		.tuner_type   = TUNER_ABSENT,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC] = अणु
		.name         = "Hauppauge WinTV-QuadHD-ATSC",
		.porta        = CX23885_ANALOG_VIDEO,
		.portb        = CX23885_MPEG_DVB,
		.portc        = CX23885_MPEG_DVB,
		.tuner_type	= TUNER_ABSENT,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885] = अणु
		.name         = "Hauppauge WinTV-QuadHD-ATSC(885)",
		.portb        = CX23885_MPEG_DVB,
		.portc        = CX23885_MPEG_DVB,
		.tuner_type   = TUNER_ABSENT,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_HVR1265_K4] = अणु
		.name		= "Hauppauge WinTV-HVR-1265(161111)",
		.porta          = CX23885_ANALOG_VIDEO,
		.portc		= CX23885_MPEG_DVB,
		.tuner_type     = TUNER_ABSENT,
		.input          = अणुअणु
			.type   = CX23885_VMUX_TELEVISION,
			.vmux   =	CX25840_VIN7_CH3 |
					CX25840_VIN5_CH2 |
					CX25840_VIN2_CH1 |
					CX25840_DIF_ON,
			.amux   = CX25840_AUDIO8,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   =	CX25840_VIN4_CH2 |
					CX25840_VIN6_CH1 |
					CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX23885_BOARD_HAUPPAUGE_STARBURST2] = अणु
		.name		= "Hauppauge WinTV-Starburst2",
		.portb		= CX23885_MPEG_DVB,
	पूर्ण,
	[CX23885_BOARD_AVERMEDIA_CE310B] = अणु
		.name		= "AVerMedia CE310B",
		.porta		= CX23885_ANALOG_VIDEO,
		.क्रमce_bff	= 1,
		.input          = अणुअणु
			.type   = CX23885_VMUX_COMPOSITE1,
			.vmux   = CX25840_VIN1_CH1 |
				  CX25840_NONE_CH2 |
				  CX25840_NONE0_CH3,
			.amux   = CX25840_AUDIO7,
		पूर्ण, अणु
			.type   = CX23885_VMUX_SVIDEO,
			.vmux   = CX25840_VIN8_CH1 |
				  CX25840_NONE_CH2 |
				  CX25840_VIN7_CH3 |
				  CX25840_SVIDEO_ON,
			.amux   = CX25840_AUDIO7,
		पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;
स्थिर अचिन्हित पूर्णांक cx23885_bcount = ARRAY_SIZE(cx23885_boards);

/* ------------------------------------------------------------------ */
/* PCI subप्रणाली IDs                                                  */

काष्ठा cx23885_subid cx23885_subids[] = अणु
	अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x3400,
		.card      = CX23885_BOARD_UNKNOWN,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7600,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1800lp,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7800,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1800,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7801,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1800,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7809,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1800,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7911,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1250,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd500,
		.card      = CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7790,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1500Q,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7797,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1500Q,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7710,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1500,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7717,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1500,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x71d1,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1200,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x71d3,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1200,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8101,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1700,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8010,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1400,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd618,
		.card      = CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb78,
		.card      = CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6681,
		.card      = CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f21,
		.card      = CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f39,
		.card	   = CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000,
	पूर्ण, अणु
		.subvenकरोr = 0x185b,
		.subdevice = 0xe800,
		.card      = CX23885_BOARD_COMPRO_VIDEOMATE_E650F,
	पूर्ण, अणु
		.subvenकरोr = 0x6920,
		.subdevice = 0x8888,
		.card      = CX23885_BOARD_TBS_6920,
	पूर्ण, अणु
		.subvenकरोr = 0x6980,
		.subdevice = 0x8888,
		.card      = CX23885_BOARD_TBS_6980,
	पूर्ण, अणु
		.subvenकरोr = 0x6981,
		.subdevice = 0x8888,
		.card      = CX23885_BOARD_TBS_6981,
	पूर्ण, अणु
		.subvenकरोr = 0xd470,
		.subdevice = 0x9022,
		.card      = CX23885_BOARD_TEVII_S470,
	पूर्ण, अणु
		.subvenकरोr = 0x0001,
		.subdevice = 0x2005,
		.card      = CX23885_BOARD_DVBWORLD_2005,
	पूर्ण, अणु
		.subvenकरोr = 0x1b55,
		.subdevice = 0x2a2c,
		.card      = CX23885_BOARD_NETUP_DUAL_DVBS2_CI,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2211,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1270,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2215,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1275,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x221d,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1275,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2251,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1255,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2259,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1255_22111,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2291,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2295,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2299,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x229d,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210, /* HVR1215 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f0,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f1,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1255,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f2,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1275,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f3,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210, /* HVR1215 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f4,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x22f5,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1210, /* HVR1215 */
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x8651,
		.card      = CX23885_BOARD_MYGICA_X8506,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x8657,
		.card      = CX23885_BOARD_MAGICPRO_PROHDTVE2,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8541,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1850,
	पूर्ण, अणु
		.subvenकरोr = 0x1858,
		.subdevice = 0xe800,
		.card      = CX23885_BOARD_COMPRO_VIDEOMATE_E800,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x8551,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1290,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x8578,
		.card      = CX23885_BOARD_MYGICA_X8558PRO,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f22,
		.card      = CX23885_BOARD_LEADTEK_WINFAST_PXTV1200,
	पूर्ण, अणु
		.subvenकरोr = 0x5654,
		.subdevice = 0x2390,
		.card      = CX23885_BOARD_GOTVIEW_X5_3D_HYBRID,
	पूर्ण, अणु
		.subvenकरोr = 0x1b55,
		.subdevice = 0xe2e4,
		.card      = CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x8502,
		.card      = CX23885_BOARD_MYGICA_X8507,
	पूर्ण, अणु
		.subvenकरोr = 0x153b,
		.subdevice = 0x117e,
		.card      = CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL,
	पूर्ण, अणु
		.subvenकरोr = 0xd471,
		.subdevice = 0x9022,
		.card      = CX23885_BOARD_TEVII_S471,
	पूर्ण, अणु
		.subvenकरोr = 0x8000,
		.subdevice = 0x3034,
		.card      = CX23885_BOARD_PROF_8000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xc108,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR4400, /* Hauppauge WinTV HVR-4400 (Model 121xxx, Hybrid DVB-T/S2, IR) */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xc138,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR4400, /* Hauppauge WinTV HVR-5500 (Model 121xxx, Hybrid DVB-T/C/S2, IR) */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xc12a,
		.card      = CX23885_BOARD_HAUPPAUGE_STARBURST, /* Hauppauge WinTV Starburst (Model 121x00, DVB-S2, IR) */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xc1f8,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR4400, /* Hauppauge WinTV HVR-5500 (Model 121xxx, Hybrid DVB-T/C/S2, IR) */
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0xd939,
		.card      = CX23885_BOARD_AVERMEDIA_HC81R,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7133,
		.card      = CX23885_BOARD_HAUPPAUGE_IMPACTVCBE,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x7137,
		.card      = CX23885_BOARD_HAUPPAUGE_IMPACTVCBE,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb98,
		.card      = CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x9580,
		.card      = CX23885_BOARD_DVBSKY_T9580,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x980c,
		.card      = CX23885_BOARD_DVBSKY_T980C,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x950c,
		.card      = CX23885_BOARD_DVBSKY_S950C,
	पूर्ण, अणु
		.subvenकरोr = 0x13c2,
		.subdevice = 0x3013,
		.card      = CX23885_BOARD_TT_CT2_4500_CI,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x0950,
		.card      = CX23885_BOARD_DVBSKY_S950,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x0952,
		.card      = CX23885_BOARD_DVBSKY_S952,
	पूर्ण, अणु
		.subvenकरोr = 0x4254,
		.subdevice = 0x0982,
		.card      = CX23885_BOARD_DVBSKY_T982,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xf038,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR5525,
	पूर्ण, अणु
		.subvenकरोr = 0x1576,
		.subdevice = 0x0260,
		.card      = CX23885_BOARD_VIEWCAST_260E,
	पूर्ण, अणु
		.subvenकरोr = 0x1576,
		.subdevice = 0x0460,
		.card      = CX23885_BOARD_VIEWCAST_460E,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6a28,
		.card      = CX23885_BOARD_HAUPPAUGE_QUADHD_DVB, /* Tuner Pair 1 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6b28,
		.card      = CX23885_BOARD_HAUPPAUGE_QUADHD_DVB, /* Tuner Pair 2 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6a18,
		.card      = CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC, /* Tuner Pair 1 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6b18,
		.card      = CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC, /* Tuner Pair 2 */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2a18,
		.card      = CX23885_BOARD_HAUPPAUGE_HVR1265_K4, /* Hauppauge WinTV HVR-1265 (Model 161xx1, Hybrid ATSC/QAM-B) */
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0xf02a,
		.card      = CX23885_BOARD_HAUPPAUGE_STARBURST2,
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0x3100,
		.card      = CX23885_BOARD_AVERMEDIA_CE310B,
	पूर्ण,
पूर्ण;
स्थिर अचिन्हित पूर्णांक cx23885_idcount = ARRAY_SIZE(cx23885_subids);

व्योम cx23885_card_list(काष्ठा cx23885_dev *dev)
अणु
	पूर्णांक i;

	अगर (0 == dev->pci->subप्रणाली_venकरोr &&
	    0 == dev->pci->subप्रणाली_device) अणु
		pr_info("%s: Board has no valid PCIe Subsystem ID and can't\n"
			"%s: be autodetected. Pass card=<n> insmod option\n"
			"%s: to workaround that. Redirect complaints to the\n"
			"%s: vendor of the TV card.  Best regards,\n"
			"%s:         -- tux\n",
			dev->name, dev->name, dev->name, dev->name, dev->name);
	पूर्ण अन्यथा अणु
		pr_info("%s: Your board isn't known (yet) to the driver.\n"
			"%s: Try to pick one of the existing card configs via\n"
			"%s: card=<n> insmod option.  Updating to the latest\n"
			"%s: version might help as well.\n",
			dev->name, dev->name, dev->name, dev->name);
	पूर्ण
	pr_info("%s: Here is a list of valid choices for the card=<n> insmod option:\n",
	       dev->name);
	क्रम (i = 0; i < cx23885_bcount; i++)
		pr_info("%s:    card=%d -> %s\n",
			dev->name, i, cx23885_boards[i].name);
पूर्ण

अटल व्योम viewcast_eeprom(काष्ठा cx23885_dev *dev, u8 *eeprom_data)
अणु
	u32 sn;

	/* The serial number record begins with tag 0x59 */
	अगर (*(eeprom_data + 0x00) != 0x59) अणु
		pr_info("%s() eeprom records are undefined, no serial number\n",
			__func__);
		वापस;
	पूर्ण

	sn =	(*(eeprom_data + 0x06) << 24) |
		(*(eeprom_data + 0x05) << 16) |
		(*(eeprom_data + 0x04) << 8) |
		(*(eeprom_data + 0x03));

	pr_info("%s: card '%s' sn# MM%d\n",
		dev->name,
		cx23885_boards[dev->board].name,
		sn);
पूर्ण

अटल व्योम hauppauge_eeprom(काष्ठा cx23885_dev *dev, u8 *eeprom_data)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);

	/* Make sure we support the board model */
	चयन (tv.model) अणु
	हाल 22001:
		/* WinTV-HVR1270 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Blast */
	हाल 22009:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Blast */
	हाल 22011:
		/* WinTV-HVR1270 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Recv */
	हाल 22019:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Recv */
	हाल 22021:
		/* WinTV-HVR1275 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Recv */
	हाल 22029:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Recv */
	हाल 22101:
		/* WinTV-HVR1270 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Blast */
	हाल 22109:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Blast */
	हाल 22111:
		/* WinTV-HVR1270 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Recv */
	हाल 22119:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Recv */
	हाल 22121:
		/* WinTV-HVR1275 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Recv */
	हाल 22129:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Recv */
	हाल 71009:
		/* WinTV-HVR1200 (PCIe, Retail, full height)
		 * DVB-T and basic analog */
	हाल 71100:
		/* WinTV-ImpactVCB-e (PCIe, Retail, half height)
		 * Basic analog */
	हाल 71359:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	हाल 71439:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	हाल 71449:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	हाल 71939:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	हाल 71949:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	हाल 71959:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	हाल 71979:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	हाल 71999:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	हाल 76601:
		/* WinTV-HVR1800lp (PCIe, Retail, No IR, Dual
			channel ATSC and MPEG2 HW Encoder */
	हाल 77001:
		/* WinTV-HVR1500 (Express Card, OEM, No IR, ATSC
			and Basic analog */
	हाल 77011:
		/* WinTV-HVR1500 (Express Card, Retail, No IR, ATSC
			and Basic analog */
	हाल 77041:
		/* WinTV-HVR1500Q (Express Card, OEM, No IR, ATSC/QAM
			and Basic analog */
	हाल 77051:
		/* WinTV-HVR1500Q (Express Card, Retail, No IR, ATSC/QAM
			and Basic analog */
	हाल 78011:
		/* WinTV-HVR1800 (PCIe, Retail, 3.5mm in, IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	हाल 78501:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	हाल 78521:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	हाल 78531:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	हाल 78631:
		/* WinTV-HVR1800 (PCIe, OEM, No IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	हाल 79001:
		/* WinTV-HVR1250 (PCIe, Retail, IR, full height,
			ATSC and Basic analog */
	हाल 79101:
		/* WinTV-HVR1250 (PCIe, Retail, IR, half height,
			ATSC and Basic analog */
	हाल 79501:
		/* WinTV-HVR1250 (PCIe, No IR, half height,
			ATSC [at least] and Basic analog) */
	हाल 79561:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, half height,
			ATSC and Basic analog */
	हाल 79571:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, full height,
		 ATSC and Basic analog */
	हाल 79671:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, half height,
			ATSC and Basic analog */
	हाल 80019:
		/* WinTV-HVR1400 (Express Card, Retail, IR,
		 * DVB-T and Basic analog */
	हाल 81509:
		/* WinTV-HVR1700 (PCIe, OEM, No IR, half height)
		 * DVB-T and MPEG2 HW Encoder */
	हाल 81519:
		/* WinTV-HVR1700 (PCIe, OEM, No IR, full height)
		 * DVB-T and MPEG2 HW Encoder */
		अवरोध;
	हाल 85021:
		/* WinTV-HVR1850 (PCIe, Retail, 3.5mm in, IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
		अवरोध;
	हाल 85721:
		/* WinTV-HVR1290 (PCIe, OEM, RCA in, IR,
			Dual channel ATSC and Basic analog */
	हाल 121019:
		/* WinTV-HVR4400 (PCIe, DVB-S2, DVB-C/T) */
		अवरोध;
	हाल 121029:
		/* WinTV-HVR5500 (PCIe, DVB-S2, DVB-C/T) */
		अवरोध;
	हाल 150329:
		/* WinTV-HVR5525 (PCIe, DVB-S/S2, DVB-T/T2/C) */
		अवरोध;
	हाल 161111:
		/* WinTV-HVR-1265 K4 (PCIe, Analog/ATSC/QAM-B) */
		अवरोध;
	हाल 166100: /* 888 version, hybrid */
	हाल 166200: /* 885 version, DVB only */
		/* WinTV-QuadHD (DVB) Tuner Pair 1 (PCIe, IR, half height,
		   DVB-T/T2/C, DVB-T/T2/C */
		अवरोध;
	हाल 166101: /* 888 version, hybrid */
	हाल 166201: /* 885 version, DVB only */
		/* WinTV-QuadHD (DVB) Tuner Pair 2 (PCIe, IR, half height,
		   DVB-T/T2/C, DVB-T/T2/C */
		अवरोध;
	हाल 165100: /* 888 version, hybrid */
	हाल 165200: /* 885 version, digital only */
		/* WinTV-QuadHD (ATSC) Tuner Pair 1 (PCIe, IR, half height,
		 * ATSC/QAM-B, ATSC/QAM-B */
		अवरोध;
	हाल 165101: /* 888 version, hybrid */
	हाल 165201: /* 885 version, digital only */
		/* WinTV-QuadHD (ATSC) Tuner Pair 2 (PCIe, IR, half height,
		 * ATSC/QAM-B, ATSC/QAM-B */
		अवरोध;
	शेष:
		pr_warn("%s: warning: unknown hauppauge model #%d\n",
			dev->name, tv.model);
		अवरोध;
	पूर्ण

	pr_info("%s: hauppauge eeprom: model=%d\n",
		dev->name, tv.model);
पूर्ण

/* Some TBS cards require initing a chip using a bitbanged SPI attached
   to the cx23885 gpio's. If this chip doesn't get init'ed the demod
   करोesn't respond to any command. */
अटल व्योम tbs_card_init(काष्ठा cx23885_dev *dev)
अणु
	पूर्णांक i;
	अटल स्थिर u8 buf[] = अणु
		0xe0, 0x06, 0x66, 0x33, 0x65,
		0x01, 0x17, 0x06, 0xdeपूर्ण;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
		cx_set(GP0_IO, 0x00070007);
		usleep_range(1000, 10000);
		cx_clear(GP0_IO, 2);
		usleep_range(1000, 10000);
		क्रम (i = 0; i < 9 * 8; i++) अणु
			cx_clear(GP0_IO, 7);
			usleep_range(1000, 10000);
			cx_set(GP0_IO,
				((buf[i >> 3] >> (7 - (i & 7))) & 1) | 4);
			usleep_range(1000, 10000);
		पूर्ण
		cx_set(GP0_IO, 7);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक cx23885_tuner_callback(व्योम *priv, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा cx23885_tsport *port = priv;
	काष्ठा cx23885_dev *dev = port->dev;
	u32 biपंचांगask = 0;

	अगर ((command == XC2028_RESET_CLK) || (command == XC2028_I2C_FLUSH))
		वापस 0;

	अगर (command != 0) अणु
		pr_err("%s(): Unknown command 0x%x.\n",
		       __func__, command);
		वापस -EINVAL;
	पूर्ण

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXTV1200:
		/* Tuner Reset Command */
		biपंचांगask = 0x04;
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2:
		/* Two identical tuners on two dअगरferent i2c buses,
		 * we need to reset the correct gpio. */
		अगर (port->nr == 1)
			biपंचांगask = 0x01;
		अन्यथा अगर (port->nr == 2)
			biपंचांगask = 0x04;
		अवरोध;
	हाल CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
		/* Tuner Reset Command */
		biपंचांगask = 0x02;
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		altera_ci_tuner_reset(dev, port->nr);
		अवरोध;
	हाल CX23885_BOARD_AVERMEDIA_HC81R:
		/* XC3028L Reset Command */
		biपंचांगask = 1 << 2;
		अवरोध;
	पूर्ण

	अगर (biपंचांगask) अणु
		/* Drive the tuner पूर्णांकo reset and back out */
		cx_clear(GP0_IO, biपंचांगask);
		mdelay(200);
		cx_set(GP0_IO, biपंचांगask);
	पूर्ण

	वापस 0;
पूर्ण

व्योम cx23885_gpio_setup(काष्ठा cx23885_dev *dev)
अणु
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
		/* GPIO-0 cx24227 demodulator reset */
		cx_set(GP0_IO, 0x00010001); /* Bring the part out of reset */
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
		/* GPIO-0 cx24227 demodulator */
		/* GPIO-2 xc3028 tuner */

		/* Put the parts पूर्णांकo reset */
		cx_set(GP0_IO, 0x00050000);
		cx_clear(GP0_IO, 0x00000005);
		msleep(5);

		/* Bring the parts out of reset */
		cx_set(GP0_IO, 0x00050005);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
		/* GPIO-0 cx24227 demodulator reset */
		/* GPIO-2 xc5000 tuner reset */
		cx_set(GP0_IO, 0x00050005); /* Bring the part out of reset */
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
		/* GPIO-0 656_CLK */
		/* GPIO-1 656_D0 */
		/* GPIO-2 8295A Reset */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */
		/* GPIO-19 IR_RX */

		/* CX23417 GPIO's */
		/* EIO15 Zilog Reset */
		/* EIO14 S5H1409/CX24227 Reset */
		mc417_gpio_enable(dev, GPIO_15 | GPIO_14, 1);

		/* Put the demod पूर्णांकo reset and protect the eeprom */
		mc417_gpio_clear(dev, GPIO_15 | GPIO_14);
		msleep(100);

		/* Bring the demod and blaster out of reset */
		mc417_gpio_set(dev, GPIO_15 | GPIO_14);
		msleep(100);

		/* Force the TDA8295A पूर्णांकo reset and back */
		cx23885_gpio_enable(dev, GPIO_2, 1);
		cx23885_gpio_set(dev, GPIO_2);
		msleep(20);
		cx23885_gpio_clear(dev, GPIO_2);
		msleep(20);
		cx23885_gpio_set(dev, GPIO_2);
		msleep(20);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1200:
		/* GPIO-0 tda10048 demodulator reset */
		/* GPIO-2 tda18271 tuner reset */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x00050000);
		msleep(20);
		cx_clear(GP0_IO, 0x00000005);
		msleep(20);
		cx_set(GP0_IO, 0x00050005);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1700:
		/* GPIO-0 TDA10048 demodulator reset */
		/* GPIO-2 TDA8295A Reset */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */

		/* The following GPIO's are on the पूर्णांकerna AVCore (cx25840) */
		/* GPIO-19 IR_RX */
		/* GPIO-20 IR_TX 416/DVBT Select */
		/* GPIO-21 IIS DAT */
		/* GPIO-22 IIS WCLK */
		/* GPIO-23 IIS BCLK */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x00050000);
		msleep(20);
		cx_clear(GP0_IO, 0x00000005);
		msleep(20);
		cx_set(GP0_IO, 0x00050005);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
		/* GPIO-0  Dibcom7000p demodulator reset */
		/* GPIO-2  xc3028L tuner reset */
		/* GPIO-13 LED */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x00050000);
		msleep(20);
		cx_clear(GP0_IO, 0x00000005);
		msleep(20);
		cx_set(GP0_IO, 0x00050005);
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
		/* GPIO-0 xc5000 tuner reset i2c bus 0 */
		/* GPIO-1 s5h1409 demod reset i2c bus 0 */
		/* GPIO-2 xc5000 tuner reset i2c bus 1 */
		/* GPIO-3 s5h1409 demod reset i2c bus 0 */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x000f0000);
		msleep(20);
		cx_clear(GP0_IO, 0x0000000f);
		msleep(20);
		cx_set(GP0_IO, 0x000f000f);
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2:
		/* GPIO-0 portb xc3028 reset */
		/* GPIO-1 portb zl10353 reset */
		/* GPIO-2 portc xc3028 reset */
		/* GPIO-3 portc zl10353 reset */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x000f0000);
		msleep(20);
		cx_clear(GP0_IO, 0x0000000f);
		msleep(20);
		cx_set(GP0_IO, 0x000f000f);
		अवरोध;
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXTV1200:
		/* GPIO-2  xc3028 tuner reset */

		/* The following GPIO's are on the पूर्णांकernal AVCore (cx25840) */
		/* GPIO-?  zl10353 demod reset */

		/* Put the parts पूर्णांकo reset and back */
		cx_set(GP0_IO, 0x00040000);
		msleep(20);
		cx_clear(GP0_IO, 0x00000004);
		msleep(20);
		cx_set(GP0_IO, 0x00040004);
		अवरोध;
	हाल CX23885_BOARD_TBS_6920:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_PROF_8000:
		cx_ग_लिखो(MC417_CTL, 0x00000036);
		cx_ग_लिखो(MC417_OEN, 0x00001000);
		cx_set(MC417_RWD, 0x00000002);
		msleep(200);
		cx_clear(MC417_RWD, 0x00000800);
		msleep(200);
		cx_set(MC417_RWD, 0x00000800);
		msleep(200);
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		/* GPIO-0 INTA from CiMax1
		   GPIO-1 INTB from CiMax2
		   GPIO-2 reset chips
		   GPIO-3 to GPIO-10 data/addr क्रम CA
		   GPIO-11 ~CS0 to CiMax1
		   GPIO-12 ~CS1 to CiMax2
		   GPIO-13 ADL0 load LSB addr
		   GPIO-14 ADL1 load MSB addr
		   GPIO-15 ~RDY from CiMax
		   GPIO-17 ~RD to CiMax
		   GPIO-18 ~WR to CiMax
		 */
		cx_set(GP0_IO, 0x00040000); /* GPIO as out */
		/* GPIO1 and GPIO2 as INTA and INTB from CiMaxes, reset low */
		cx_clear(GP0_IO, 0x00030004);
		msleep(100);/* reset delay */
		cx_set(GP0_IO, 0x00040004); /* GPIO as out, reset high */
		cx_ग_लिखो(MC417_CTL, 0x00000037);/* enable GPIO3-18 pins */
		/* GPIO-15 IN as ~ACK, rest as OUT */
		cx_ग_लिखो(MC417_OEN, 0x00001000);
		/* ~RD, ~WR high; ADL0, ADL1 low; ~CS0, ~CS1 high */
		cx_ग_लिखो(MC417_RWD, 0x0000c300);
		/* enable irq */
		cx_ग_लिखो(GPIO_ISM, 0x00000000);/* INTERRUPTS active low*/
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1210:
		/* GPIO-5 RF Control: 0 = RF1 Terrestrial, 1 = RF2 Cable */
		/* GPIO-6 I2C Gate which can isolate the demod from the bus */
		/* GPIO-9 Demod reset */

		/* Put the parts पूर्णांकo reset and back */
		cx23885_gpio_enable(dev, GPIO_9 | GPIO_6 | GPIO_5, 1);
		cx23885_gpio_set(dev, GPIO_9 | GPIO_6 | GPIO_5);
		cx23885_gpio_clear(dev, GPIO_9);
		msleep(20);
		cx23885_gpio_set(dev, GPIO_9);
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8506:
	हाल CX23885_BOARD_MAGICPRO_PROHDTVE2:
	हाल CX23885_BOARD_MYGICA_X8507:
		/* GPIO-0 (0)Analog / (1)Digital TV */
		/* GPIO-1 reset XC5000 */
		/* GPIO-2 demod reset */
		cx23885_gpio_enable(dev, GPIO_0 | GPIO_1 | GPIO_2, 1);
		cx23885_gpio_clear(dev, GPIO_1 | GPIO_2);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_0 | GPIO_1 | GPIO_2);
		msleep(100);
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8558PRO:
		/* GPIO-0 reset first ATBM8830 */
		/* GPIO-1 reset second ATBM8830 */
		cx23885_gpio_enable(dev, GPIO_0 | GPIO_1, 1);
		cx23885_gpio_clear(dev, GPIO_0 | GPIO_1);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_0 | GPIO_1);
		msleep(100);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
		/* GPIO-0 656_CLK */
		/* GPIO-1 656_D0 */
		/* GPIO-2 Wake# */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */
		/* GPIO-19 IR_RX */
		/* GPIO-20 C_IR_TX */
		/* GPIO-21 I2S DAT */
		/* GPIO-22 I2S WCLK */
		/* GPIO-23 I2S BCLK */
		/* ALT GPIO: EXP GPIO LATCH */

		/* CX23417 GPIO's */
		/* GPIO-14 S5H1411/CX24228 Reset */
		/* GPIO-13 EEPROM ग_लिखो protect */
		mc417_gpio_enable(dev, GPIO_14 | GPIO_13, 1);

		/* Put the demod पूर्णांकo reset and protect the eeprom */
		mc417_gpio_clear(dev, GPIO_14 | GPIO_13);
		msleep(100);

		/* Bring the demod out of reset */
		mc417_gpio_set(dev, GPIO_14);
		msleep(100);

		/* CX24228 GPIO */
		/* Connected to IF / Mux */
		अवरोध;
	हाल CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
		cx_set(GP0_IO, 0x00010001); /* Bring the part out of reset */
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		/* GPIO-0 ~INT in
		   GPIO-1 TMS out
		   GPIO-2 ~reset chips out
		   GPIO-3 to GPIO-10 data/addr क्रम CA in/out
		   GPIO-11 ~CS out
		   GPIO-12 ADDR out
		   GPIO-13 ~WR out
		   GPIO-14 ~RD out
		   GPIO-15 ~RDY in
		   GPIO-16 TCK out
		   GPIO-17 TDO in
		   GPIO-18 TDI out
		 */
		cx_set(GP0_IO, 0x00060000); /* GPIO-1,2 as out */
		/* GPIO-0 as INT, reset & TMS low */
		cx_clear(GP0_IO, 0x00010006);
		msleep(100);/* reset delay */
		cx_set(GP0_IO, 0x00000004); /* reset high */
		cx_ग_लिखो(MC417_CTL, 0x00000037);/* enable GPIO-3..18 pins */
		/* GPIO-17 is TDO in, GPIO-15 is ~RDY in, rest is out */
		cx_ग_लिखो(MC417_OEN, 0x00005000);
		/* ~RD, ~WR high; ADDR low; ~CS high */
		cx_ग_लिखो(MC417_RWD, 0x00000d00);
		/* enable irq */
		cx_ग_लिखो(GPIO_ISM, 0x00000000);/* INTERRUPTS active low*/
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR4400:
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST:
		/* GPIO-8 tda10071 demod reset */
		/* GPIO-9 si2165 demod reset (only HVR4400/HVR5500)*/

		/* Put the parts पूर्णांकo reset and back */
		cx23885_gpio_enable(dev, GPIO_8 | GPIO_9, 1);

		cx23885_gpio_clear(dev, GPIO_8 | GPIO_9);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_8 | GPIO_9);
		msleep(100);

		अवरोध;
	हाल CX23885_BOARD_AVERMEDIA_HC81R:
		cx_clear(MC417_CTL, 1);
		/* GPIO-0,1,2 setup direction as output */
		cx_set(GP0_IO, 0x00070000);
		usleep_range(10000, 11000);
		/* AF9013 demod reset */
		cx_set(GP0_IO, 0x00010001);
		usleep_range(10000, 11000);
		cx_clear(GP0_IO, 0x00010001);
		usleep_range(10000, 11000);
		cx_set(GP0_IO, 0x00010001);
		usleep_range(10000, 11000);
		/* demod tune? */
		cx_clear(GP0_IO, 0x00030003);
		usleep_range(10000, 11000);
		cx_set(GP0_IO, 0x00020002);
		usleep_range(10000, 11000);
		cx_set(GP0_IO, 0x00010001);
		usleep_range(10000, 11000);
		cx_clear(GP0_IO, 0x00020002);
		/* XC3028L tuner reset */
		cx_set(GP0_IO, 0x00040004);
		cx_clear(GP0_IO, 0x00040004);
		cx_set(GP0_IO, 0x00040004);
		msleep(60);
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
		/* enable GPIO3-18 pins */
		cx_ग_लिखो(MC417_CTL, 0x00000037);
		cx23885_gpio_enable(dev, GPIO_2 | GPIO_11, 1);
		cx23885_gpio_clear(dev, GPIO_2 | GPIO_11);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_2 | GPIO_11);
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
		/*
		 * GPIO-0 INTA from CiMax, input
		 * GPIO-1 reset CiMax, output, high active
		 * GPIO-2 reset demod, output, low active
		 * GPIO-3 to GPIO-10 data/addr क्रम CAM
		 * GPIO-11 ~CS0 to CiMax1
		 * GPIO-12 ~CS1 to CiMax2
		 * GPIO-13 ADL0 load LSB addr
		 * GPIO-14 ADL1 load MSB addr
		 * GPIO-15 ~RDY from CiMax
		 * GPIO-17 ~RD to CiMax
		 * GPIO-18 ~WR to CiMax
		 */

		cx_set(GP0_IO, 0x00060002); /* GPIO 1/2 as output */
		cx_clear(GP0_IO, 0x00010004); /* GPIO 0 as input */
		msleep(100); /* reset delay */
		cx_set(GP0_IO, 0x00060004); /* GPIO as out, reset high */
		cx_clear(GP0_IO, 0x00010002);
		cx_ग_लिखो(MC417_CTL, 0x00000037); /* enable GPIO3-18 pins */

		/* GPIO-15 IN as ~ACK, rest as OUT */
		cx_ग_लिखो(MC417_OEN, 0x00001000);

		/* ~RD, ~WR high; ADL0, ADL1 low; ~CS0, ~CS1 high */
		cx_ग_लिखो(MC417_RWD, 0x0000c300);

		/* enable irq */
		cx_ग_लिखो(GPIO_ISM, 0x00000000); /* INTERRUPTS active low */
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_S950:
		cx23885_gpio_enable(dev, GPIO_2, 1);
		cx23885_gpio_clear(dev, GPIO_2);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_2);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST2:
		/*
		 * HVR5525 GPIO Details:
		 *  GPIO-00 IR_WIDE
		 *  GPIO-02 wake#
		 *  GPIO-03 VAUX Pres.
		 *  GPIO-07 PROG#
		 *  GPIO-08 SAT_RESN
		 *  GPIO-09 TER_RESN
		 *  GPIO-10 B2_SENSE
		 *  GPIO-11 B1_SENSE
		 *  GPIO-15 IR_LED_STATUS
		 *  GPIO-19 IR_NARROW
		 *  GPIO-20 Blauster1
		 *  ALTGPIO VAUX_SWITCH
		 *  AUX_PLL_CLK : Blaster2
		 */
		/* Put the parts पूर्णांकo reset and back */
		cx23885_gpio_enable(dev, GPIO_8 | GPIO_9, 1);
		cx23885_gpio_clear(dev, GPIO_8 | GPIO_9);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_8 | GPIO_9);
		msleep(100);
		अवरोध;
	हाल CX23885_BOARD_VIEWCAST_260E:
	हाल CX23885_BOARD_VIEWCAST_460E:
		/* For करोcumentation purposes, it's worth noting that this
		 * card करोes not have any GPIO's connected to subcomponents.
		 */
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885:
		/*
		 * GPIO-08 TER1_RESN
		 * GPIO-09 TER2_RESN
		 */
		/* Put the parts पूर्णांकo reset and back */
		cx23885_gpio_enable(dev, GPIO_8 | GPIO_9, 1);
		cx23885_gpio_clear(dev, GPIO_8 | GPIO_9);
		msleep(100);
		cx23885_gpio_set(dev, GPIO_8 | GPIO_9);
		msleep(100);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक cx23885_ir_init(काष्ठा cx23885_dev *dev)
अणु
	अटल काष्ठा v4l2_subdev_io_pin_config ir_rxtx_pin_cfg[] = अणु
		अणु
			.flags	  = BIT(V4L2_SUBDEV_IO_PIN_INPUT),
			.pin	  = CX23885_PIN_IR_RX_GPIO19,
			.function = CX23885_PAD_IR_RX,
			.value	  = 0,
			.strength = CX25840_PIN_DRIVE_MEDIUM,
		पूर्ण, अणु
			.flags	  = BIT(V4L2_SUBDEV_IO_PIN_OUTPUT),
			.pin	  = CX23885_PIN_IR_TX_GPIO20,
			.function = CX23885_PAD_IR_TX,
			.value	  = 0,
			.strength = CX25840_PIN_DRIVE_MEDIUM,
		पूर्ण
	पूर्ण;
	स्थिर माप_प्रकार ir_rxtx_pin_cfg_count = ARRAY_SIZE(ir_rxtx_pin_cfg);

	अटल काष्ठा v4l2_subdev_io_pin_config ir_rx_pin_cfg[] = अणु
		अणु
			.flags	  = BIT(V4L2_SUBDEV_IO_PIN_INPUT),
			.pin	  = CX23885_PIN_IR_RX_GPIO19,
			.function = CX23885_PAD_IR_RX,
			.value	  = 0,
			.strength = CX25840_PIN_DRIVE_MEDIUM,
		पूर्ण
	पूर्ण;
	स्थिर माप_प्रकार ir_rx_pin_cfg_count = ARRAY_SIZE(ir_rx_pin_cfg);

	काष्ठा v4l2_subdev_ir_parameters params;
	पूर्णांक ret = 0;
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1200:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1210:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		/* FIXME: Implement me */
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
		ret = cx23888_ir_probe(dev);
		अगर (ret)
			अवरोध;
		dev->sd_ir = cx23885_find_hw(dev, CX23885_HW_888_IR);
		v4l2_subdev_call(dev->sd_cx25840, core, s_io_pin_config,
				 ir_rx_pin_cfg_count, ir_rx_pin_cfg);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
		ret = cx23888_ir_probe(dev);
		अगर (ret)
			अवरोध;
		dev->sd_ir = cx23885_find_hw(dev, CX23885_HW_888_IR);
		v4l2_subdev_call(dev->sd_cx25840, core, s_io_pin_config,
				 ir_rxtx_pin_cfg_count, ir_rxtx_pin_cfg);
		/*
		 * For these boards we need to invert the Tx output via the
		 * IR controller to have the LED off जबतक idle
		 */
		v4l2_subdev_call(dev->sd_ir, ir, tx_g_parameters, &params);
		params.enable = false;
		params.shutकरोwn = false;
		params.invert_level = true;
		v4l2_subdev_call(dev->sd_ir, ir, tx_s_parameters, &params);
		params.shutकरोwn = true;
		v4l2_subdev_call(dev->sd_ir, ir, tx_s_parameters, &params);
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
		अगर (!enable_885_ir)
			अवरोध;
		dev->sd_ir = cx23885_find_hw(dev, CX23885_HW_AV_CORE);
		अगर (dev->sd_ir == शून्य) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		v4l2_subdev_call(dev->sd_cx25840, core, s_io_pin_config,
				 ir_rx_pin_cfg_count, ir_rx_pin_cfg);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
		अगर (!enable_885_ir)
			अवरोध;
		dev->sd_ir = cx23885_find_hw(dev, CX23885_HW_AV_CORE);
		अगर (dev->sd_ir == शून्य) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		v4l2_subdev_call(dev->sd_cx25840, core, s_io_pin_config,
				 ir_rxtx_pin_cfg_count, ir_rxtx_pin_cfg);
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2:
		request_module("ir-kbd-i2c");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम cx23885_ir_fini(काष्ठा cx23885_dev *dev)
अणु
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
		cx23885_irq_हटाओ(dev, PCI_MSK_IR);
		cx23888_ir_हटाओ(dev);
		dev->sd_ir = शून्य;
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
		cx23885_irq_हटाओ(dev, PCI_MSK_AV_CORE);
		/* sd_ir is a duplicate poपूर्णांकer to the AV Core, just clear it */
		dev->sd_ir = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक netup_jtag_io(व्योम *device, पूर्णांक पंचांगs, पूर्णांक tdi, पूर्णांक पढ़ो_tकरो)
अणु
	पूर्णांक data;
	पूर्णांक tकरो = 0;
	काष्ठा cx23885_dev *dev = (काष्ठा cx23885_dev *)device;
	/*TMS*/
	data = ((cx_पढ़ो(GP0_IO)) & (~0x00000002));
	data |= (पंचांगs ? 0x00020002 : 0x00020000);
	cx_ग_लिखो(GP0_IO, data);

	/*TDI*/
	data = ((cx_पढ़ो(MC417_RWD)) & (~0x0000a000));
	data |= (tdi ? 0x00008000 : 0);
	cx_ग_लिखो(MC417_RWD, data);
	अगर (पढ़ो_tकरो)
		tकरो = (data & 0x00004000) ? 1 : 0; /*TDO*/

	cx_ग_लिखो(MC417_RWD, data | 0x00002000);
	udelay(1);
	/*TCK*/
	cx_ग_लिखो(MC417_RWD, data);

	वापस tकरो;
पूर्ण

व्योम cx23885_ir_pci_पूर्णांक_enable(काष्ठा cx23885_dev *dev)
अणु
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
		अगर (dev->sd_ir)
			cx23885_irq_add_enable(dev, PCI_MSK_IR);
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
		अगर (dev->sd_ir)
			cx23885_irq_add_enable(dev, PCI_MSK_AV_CORE);
		अवरोध;
	पूर्ण
पूर्ण

व्योम cx23885_card_setup(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा cx23885_tsport *ts1 = &dev->ts1;
	काष्ठा cx23885_tsport *ts2 = &dev->ts2;

	अटल u8 eeprom[256];

	अगर (dev->i2c_bus[0].i2c_rc == 0) अणु
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_bus[0].i2c_client,
			      eeprom, माप(eeprom));
	पूर्ण

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
		अगर (dev->i2c_bus[0].i2c_rc == 0) अणु
			अगर (eeprom[0x80] != 0x84)
				hauppauge_eeprom(dev, eeprom+0xc0);
			अन्यथा
				hauppauge_eeprom(dev, eeprom+0x80);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
		अगर (dev->i2c_bus[0].i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0x80);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1200:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1700:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1210:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_HAUPPAUGE_HVR4400:
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST:
	हाल CX23885_BOARD_HAUPPAUGE_IMPACTVCBE:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST2:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885:
		अगर (dev->i2c_bus[0].i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0xc0);
		अवरोध;
	हाल CX23885_BOARD_VIEWCAST_260E:
	हाल CX23885_BOARD_VIEWCAST_460E:
		dev->i2c_bus[1].i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_bus[1].i2c_client,
			      eeprom, माप(eeprom));
		अगर (dev->i2c_bus[0].i2c_rc == 0)
			viewcast_eeprom(dev, eeprom);
		अवरोध;
	पूर्ण

	चयन (dev->board) अणु
	हाल CX23885_BOARD_AVERMEDIA_HC81R:
		/* Defaults क्रम VID B */
		ts1->gen_ctrl_val  = 0x4; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		/* Defaults क्रम VID C */
		/* DREQ_POL, SMODE, PUNC_CLK, MCLK_POL Serial bus + punc clk */
		ts2->gen_ctrl_val  = 0x10e;
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val     = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2:
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		fallthrough;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
		/* Defaults क्रम VID B - Analog encoder */
		/* DREQ_POL, SMODE, PUNC_CLK, MCLK_POL Serial bus + punc clk */
		ts1->gen_ctrl_val    = 0x10e;
		ts1->ts_clk_en_val   = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val     = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;

		/* APB_TSVALERR_POL (active low)*/
		ts1->vld_misc_val    = 0x2000;
		ts1->hw_sop_ctrl_val = (0x47 << 16 | 188 << 4 | 0xc);
		cx_ग_लिखो(0x130184, 0xc);

		/* Defaults क्रम VID C */
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_TBS_6920:
		ts1->gen_ctrl_val  = 0x4; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_TEVII_S471:
	हाल CX23885_BOARD_DVBWORLD_2005:
	हाल CX23885_BOARD_PROF_8000:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		tbs_card_init(dev);
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8506:
	हाल CX23885_BOARD_MAGICPRO_PROHDTVE2:
	हाल CX23885_BOARD_MYGICA_X8507:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8558PRO:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR4400:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T982:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0x8; /* Serial bus */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_S952:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xe; /* Serial bus */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST2:
		ts1->gen_ctrl_val  = 0x5; /* Parallel */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885:
		ts1->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts1->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts1->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1200:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1700:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
	हाल CX23885_BOARD_HAUPPAUGE_IMPACTVCBE:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1210:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
	शेष:
		ts2->gen_ctrl_val  = 0xc; /* Serial bus + punctured घड़ी */
		ts2->ts_clk_en_val = 0x1; /* Enable TS_CLK */
		ts2->src_sel_val   = CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO;
	पूर्ण

	/* Certain boards support analog, or require the avcore to be
	 * loaded, ensure this happens.
	 */
	चयन (dev->board) अणु
	हाल CX23885_BOARD_TEVII_S470:
		/* Currently only enabled क्रम the पूर्णांकegrated IR controller */
		अगर (!enable_885_ir)
			अवरोध;
		fallthrough;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
	हाल CX23885_BOARD_HAUPPAUGE_IMPACTVCBE:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800lp:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1700:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_MYGICA_X8506:
	हाल CX23885_BOARD_MAGICPRO_PROHDTVE2:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXTV1200:
	हाल CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
	हाल CX23885_BOARD_MPX885:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_AVERMEDIA_HC81R:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
	हाल CX23885_BOARD_VIEWCAST_260E:
	हाल CX23885_BOARD_VIEWCAST_460E:
	हाल CX23885_BOARD_AVERMEDIA_CE310B:
		dev->sd_cx25840 = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[2].i2c_adap,
				"cx25840", 0x88 >> 1, शून्य);
		अगर (dev->sd_cx25840) अणु
			/* set host data क्रम clk_freq configuration */
			v4l2_set_subdev_hostdata(dev->sd_cx25840,
						&dev->clk_freq);

			dev->sd_cx25840->grp_id = CX23885_HW_AV_CORE;
			v4l2_subdev_call(dev->sd_cx25840, core, load_fw);
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (dev->board) अणु
	हाल CX23885_BOARD_VIEWCAST_260E:
		v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[0].i2c_adap,
				"cs3308", 0x82 >> 1, शून्य);
		अवरोध;
	हाल CX23885_BOARD_VIEWCAST_460E:
		/* This cs3308 controls the audio from the अवरोधout cable */
		v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[0].i2c_adap,
				"cs3308", 0x80 >> 1, शून्य);
		/* This cs3308 controls the audio from the onboard header */
		v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[0].i2c_adap,
				"cs3308", 0x82 >> 1, शून्य);
		अवरोध;
	पूर्ण

	/* AUX-PLL 27MHz CLK */
	चयन (dev->board) अणु
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		netup_initialize(dev);
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF: अणु
		पूर्णांक ret;
		स्थिर काष्ठा firmware *fw;
		स्थिर अक्षर *filename = "dvb-netup-altera-01.fw";
		अक्षर *action = "configure";
		अटल काष्ठा netup_card_info cinfo;
		काष्ठा altera_config netup_config = अणु
			.dev = dev,
			.action = action,
			.jtag_io = netup_jtag_io,
		पूर्ण;

		netup_initialize(dev);

		netup_get_card_info(&dev->i2c_bus[0].i2c_adap, &cinfo);
		अगर (netup_card_rev)
			cinfo.rev = netup_card_rev;

		चयन (cinfo.rev) अणु
		हाल 0x4:
			filename = "dvb-netup-altera-04.fw";
			अवरोध;
		शेष:
			filename = "dvb-netup-altera-01.fw";
			अवरोध;
		पूर्ण
		pr_info("NetUP card rev=0x%x fw_filename=%s\n",
			cinfo.rev, filename);

		ret = request_firmware(&fw, filename, &dev->pci->dev);
		अगर (ret != 0)
			pr_err("did not find the firmware file '%s'. You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware.",
			       filename);
		अन्यथा
			altera_init(&netup_config, fw);

		release_firmware(fw);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण
