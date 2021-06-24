<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * device driver क्रम Conexant 2388x based TV cards
 * card-specअगरic stuff.
 *
 * (c) 2003 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "cx88.h"
#समावेश "tea5767.h"
#समावेश "xc4000.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

अटल अचिन्हित पूर्णांक tuner[] = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक radio[] = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक card[]  = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(tuner, पूर्णांक, शून्य, 0444);
module_param_array(radio, पूर्णांक, शून्य, 0444);
module_param_array(card,  पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(tuner, "tuner type");
MODULE_PARM_DESC(radio, "radio tuner type");
MODULE_PARM_DESC(card, "card type");

अटल अचिन्हित पूर्णांक latency = UNSET;
module_param(latency, पूर्णांक, 0444);
MODULE_PARM_DESC(latency, "pci latency timer");

अटल पूर्णांक disable_ir;
module_param(disable_ir, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ir, "Disable IR support");

#घोषणा dprपूर्णांकk(level, fmt, arg...)	करो अणु				\
	अगर (cx88_core_debug >= level)					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: core:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */
/* board config info                                                  */

/* If radio_type !=UNSET, radio_addr should be specअगरied
 */

अटल स्थिर काष्ठा cx88_board cx88_boards[] = अणु
	[CX88_BOARD_UNKNOWN] = अणु
		.name		= "UNKNOWN/GENERIC",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE2,
			.vmux   = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE3,
			.vmux   = 2,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE4,
			.vmux   = 3,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE] = अणु
		.name		= "Hauppauge WinTV 34xxx models",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xff00,  // पूर्णांकernal decoder
		पूर्ण, अणु
			.type   = CX88_VMUX_DEBUG,
			.vmux   = 0,
			.gpio0  = 0xff01,  // mono from tuner chip
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0xff02,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0xff02,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0xff01,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_GDI] = अणु
		.name		= "GDI Black Gold",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_PIXELVIEW] = अणु
		.name           = "PixelView",
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xff00,  // पूर्णांकernal decoder
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0xff10,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_ATI_WONDER_PRO] = अणु
		.name           = "ATI TV Wonder Pro",
		.tuner_type     = TUNER_PHILIPS_4IN1,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_INTERCARRIER,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x03ff,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x03fe,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x03fe,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_WINFAST2000XP_EXPERT] = अणु
		.name           = "Leadtek Winfast 2000XP Expert",
		.tuner_type     = TUNER_PHILIPS_4IN1,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0	= 0x00F5e700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x00F5e700,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0	= 0x00F5c700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x00F5c700,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0	= 0x00F5c700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x00F5c700,
			.gpio3  = 0x02000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0	= 0x00F5d700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x00F5d700,
			.gpio3  = 0x02000000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_AVERTV_STUDIO_303] = अणु
		.name           = "AverTV Studio 303 (M126)",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio1  = 0xe09f,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio1  = 0xe05f,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio1  = 0xe05f,
		पूर्ण पूर्ण,
		.radio = अणु
			.gpio1  = 0xe0df,
			.type   = CX88_RADIO,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_MSI_TVANYWHERE_MASTER] = अणु
		// added gpio values thanks to Michal
		// values क्रम PAL from DScaler
		.name           = "MSI TV-@nywhere Master",
		.tuner_type     = TUNER_MT2032,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf	= TDA9887_PRESENT | TDA9887_INTERCARRIER_NTSC,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x000040bf,
			.gpio1  = 0x000080c0,
			.gpio2  = 0x0000ff40,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000040bf,
			.gpio1  = 0x000080c0,
			.gpio2  = 0x0000ff40,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000040bf,
			.gpio1  = 0x000080c0,
			.gpio2  = 0x0000ff40,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type   = CX88_RADIO,
			 .vmux   = 3,
			 .gpio0  = 0x000040bf,
			 .gpio1  = 0x000080c0,
			 .gpio2  = 0x0000ff20,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_WINFAST_DV2000] = अणु
		.name           = "Leadtek Winfast DV2000",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0035e700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x0035e700,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0035c700,
			.gpio1  = 0x00003004,
			.gpio2  = 0x0035c700,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0035c700,
			.gpio1  = 0x0035c700,
			.gpio2  = 0x02000000,
			.gpio3  = 0x02000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0035d700,
			.gpio1  = 0x00007004,
			.gpio2  = 0x0035d700,
			.gpio3  = 0x02000000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_LEADTEK_PVR2000] = अणु
		// gpio values क्रम PAL version from regspy by DScaler
		.name           = "Leadtek PVR 2000",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0000bde2,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0000bde6,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0000bde6,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0000bd62,
			.audioroute = 1,
		पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_IODATA_GVVCP3PCI] = अणु
		.name		= "IODATA GV-VCP3/PCI",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE2,
			.vmux   = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_PROLINK_PLAYTVPVR] = अणु
		.name           = "Prolink PlayTV PVR",
		.tuner_type     = TUNER_PHILIPS_FM1236_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf	= TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xbff0,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0xbff3,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0xbff3,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0xbff0,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_ASUS_PVR_416] = अणु
		.name		= "ASUS PVR-416",
		.tuner_type     = TUNER_PHILIPS_FM1236_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0000fde6,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0000fde6, // 0x0000fda6 L,R RCA audio in?
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0000fde2,
		पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_MSI_TVANYWHERE] = अणु
		.name           = "MSI TV-@nywhere",
		.tuner_type     = TUNER_MT2032,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00000fbf,
			.gpio2  = 0x0000fc08,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00000fbf,
			.gpio2  = 0x0000fc68,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00000fbf,
			.gpio2  = 0x0000fc68,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_KWORLD_DVB_T] = अणु
		.name           = "KWorld/VStream XPert DVB-T",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_DVB_T1] = अणु
		.name           = "DViCO FusionHDTV DVB-T1",
		.tuner_type     = UNSET, /* No analog tuner */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000027df,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000027df,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_KWORLD_LTV883] = अणु
		.name           = "KWorld LTV883RF",
		.tuner_type     = TUNER_TNF_8831BGFF,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x07f8,
		पूर्ण, अणु
			.type   = CX88_VMUX_DEBUG,
			.vmux   = 0,
			.gpio0  = 0x07f9,  // mono from tuner chip
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000007fa,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000007fa,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x000007f8,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q] = अणु
		.name		= "DViCO FusionHDTV 3 Gold-Q",
		.tuner_type     = TUNER_MICROTUNE_4042FI5,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		/*
		 * GPIO[0] resets DT3302 DTV receiver
		 *     0 - reset निश्चितed
		 *     1 - normal operation
		 * GPIO[1] mutes analog audio output connector
		 *     0 - enable selected source
		 *     1 - mute
		 * GPIO[2] selects source क्रम analog audio output connector
		 *     0 - analog audio input connector on tab
		 *     1 - analog DAC output from CX23881 chip
		 * GPIO[3] selects RF input connector on tuner module
		 *     0 - RF connector labeled CABLE
		 *     1 - RF connector labeled ANT
		 * GPIO[4] selects high RF क्रम QAM256 mode
		 *     0 - normal RF
		 *     1 - high RF
		 */
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0	= 0x0f0d,
		पूर्ण, अणु
			.type   = CX88_VMUX_CABLE,
			.vmux   = 0,
			.gpio0	= 0x0f05,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0	= 0x0f00,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0	= 0x0f00,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_DVB_T1] = अणु
		.name           = "Hauppauge Nova-T DVB-T",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_CONEXANT_DVB_T1] = अणु
		.name           = "Conexant DVB-T reference design",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PROVIDEO_PV259] = अणु
		.name		= "Provideo PV259",
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS] = अणु
		.name           = "DViCO FusionHDTV DVB-T Plus",
		.tuner_type     = UNSET, /* No analog tuner */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000027df,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000027df,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DNTV_LIVE_DVB_T] = अणु
		.name		= "digitalnow DNTV Live! DVB-T",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input		= अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00000700,
			.gpio2  = 0x00000101,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00000700,
			.gpio2  = 0x00000101,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PCHDTV_HD3000] = अणु
		.name           = "pcHDTV HD3000 HDTV",
		.tuner_type     = TUNER_THOMSON_DTT761X,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		/* GPIO[2] = audio source क्रम analog audio out connector
		 *  0 = analog audio input connector
		 *  1 = CX88 audio DACs
		 *
		 * GPIO[7] = input to CX88's audio/chroma ADC
		 *  0 = FM 10.7 MHz IF
		 *  1 = Sound 4.5 MHz IF
		 *
		 * GPIO[1,5,6] = Oren 51132 pins 27,35,28 respectively
		 *
		 * GPIO[16] = Remote control input
		 */
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00008484,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00008400,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00008400,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x00008404,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_ROSLYN] = अणु
		// entry added by Kaustubh D. Bhalerao <bhalerao.1@osu.edu>
		// GPIO values obtained from regspy, courtesy Sean Covel
		.name           = "Hauppauge WinTV 28xxx (Roslyn) models",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xed1a,
			.gpio2  = 0x00ff,
		पूर्ण, अणु
			.type   = CX88_VMUX_DEBUG,
			.vmux   = 0,
			.gpio0  = 0xff01,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0xff02,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0xed92,
			.gpio2  = 0x00ff,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type   = CX88_RADIO,
			 .gpio0  = 0xed96,
			 .gpio2  = 0x00ff,
		 पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_DIGITALLOGIC_MEC] = अणु
		.name           = "Digital-Logic MICROSPACE Entertainment Center (MEC)",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00009d80,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00009d76,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00009d76,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x00009d00,
			.audioroute = 1,
		पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_IODATA_GVBCTV7E] = अणु
		.name           = "IODATA GV/BCTV7E",
		.tuner_type     = TUNER_PHILIPS_FQ1286,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 1,
			.gpio1  = 0x0000e03f,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 2,
			.gpio1  = 0x0000e07f,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 3,
			.gpio1  = 0x0000e07f,
		पूर्ण पूर्ण
	पूर्ण,
	[CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO] = अणु
		.name           = "PixelView PlayTV Ultra Pro (Stereo)",
		/* May be also TUNER_YMEC_TVF_5533MF क्रम NTSC/M or PAL/M */
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		/*
		 * Some variants use a tda9874 and so need the
		 * tvaudio module.
		 */
		.audio_chip     = CX88_AUDIO_TVAUDIO,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xbf61,  /* पूर्णांकernal decoder */
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0	= 0xbf63,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0	= 0xbf63,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0xbf60,
		 पूर्ण,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_T] = अणु
		.name           = "DViCO FusionHDTV 3 Gold-T",
		.tuner_type     = TUNER_THOMSON_DTT761X,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x97ed,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x97e9,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x97e9,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_ADSTECH_DVB_T_PCI] = अणु
		.name           = "ADS Tech Instant TV DVB-T PCI",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1] = अणु
		.name           = "TerraTec Cinergy 1400 DVB-T",
		.tuner_type     = UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 2,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD] = अणु
		.name           = "DViCO FusionHDTV 5 Gold",
		.tuner_type     = TUNER_LG_TDVS_H06XF, /* TDVS-H062F */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x87fd,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x87f9,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x87f9,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_AVERMEDIA_ULTRATV_MC_550] = अणु
		.name           = "AverMedia UltraTV Media Center PCI 550",
		.tuner_type     = TUNER_PHILIPS_FM1236_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 0,
			.gpio0  = 0x0000cd73,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 1,
			.gpio0  = 0x0000cd73,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 3,
			.gpio0  = 0x0000cdb3,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.vmux   = 2,
			.gpio0  = 0x0000cdf3,
			.audioroute = 1,
		पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_KWORLD_VSTREAM_EXPERT_DVD] = अणु
		 /* Alexander Wold <awold@bigfoot.com> */
		 .name           = "Kworld V-Stream Xpert DVD",
		 .tuner_type     = UNSET,
		 .input          = अणु अणु
			 .type   = CX88_VMUX_COMPOSITE1,
			 .vmux   = 1,
			 .gpio0  = 0x03000000,
			 .gpio1  = 0x01000000,
			 .gpio2  = 0x02000000,
			 .gpio3  = 0x00100000,
		 पूर्ण, अणु
			 .type   = CX88_VMUX_SVIDEO,
			 .vmux   = 2,
			 .gpio0  = 0x03000000,
			 .gpio1  = 0x01000000,
			 .gpio2  = 0x02000000,
			 .gpio3  = 0x00100000,
		 पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_ATI_HDTVWONDER] = अणु
		.name           = "ATI HDTV Wonder",
		.tuner_type     = TUNER_PHILIPS_TUV1236D,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00000ff7,
			.gpio1  = 0x000000ff,
			.gpio2  = 0x00000001,
			.gpio3  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00000ffe,
			.gpio1  = 0x000000ff,
			.gpio2  = 0x00000001,
			.gpio3  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00000ffe,
			.gpio1  = 0x000000ff,
			.gpio2  = 0x00000001,
			.gpio3  = 0x00000000,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV1000] = अणु
		.name           = "WinFast DTV1000-T",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_AVERTV_303] = अणु
		.name           = "AVerTV 303 (M126)",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00ff,
			.gpio1  = 0xe09f,
			.gpio2  = 0x0010,
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00ff,
			.gpio1  = 0xe05f,
			.gpio2  = 0x0010,
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00ff,
			.gpio1  = 0xe05f,
			.gpio2  = 0x0010,
			.gpio3  = 0x0000,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1] = अणु
		.name		= "Hauppauge Nova-S-Plus DVB-S",
		.tuner_type	= UNSET,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.audio_chip	= CX88_AUDIO_WM8775,
		.i2sinअ_दोntl   = 2,
		.input		= अणु अणु
			.type	= CX88_VMUX_DVB,
			.vmux	= 0,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_NOVASE2_S1] = अणु
		.name		= "Hauppauge Nova-SE2 DVB-S",
		.tuner_type	= UNSET,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input		= अणु अणु
			.type	= CX88_VMUX_DVB,
			.vmux	= 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_KWORLD_DVBS_100] = अणु
		.name		= "KWorld DVB-S 100",
		.tuner_type	= UNSET,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.audio_chip = CX88_AUDIO_WM8775,
		.input		= अणु अणु
			.type	= CX88_VMUX_DVB,
			.vmux	= 0,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR1100] = अणु
		.name		= "Hauppauge WinTV-HVR1100 DVB-T/Hybrid",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input		= अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
		पूर्ण पूर्ण,
		/* fixme: Add radio support */
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR1100LP] = अणु
		.name		= "Hauppauge WinTV-HVR1100 DVB-T/Hybrid (Low Profile)",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input		= अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
		पूर्ण पूर्ण,
		/* fixme: Add radio support */
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DNTV_LIVE_DVB_T_PRO] = अणु
		.name           = "digitalnow DNTV Live! DVB-T Pro",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE |
				  TDA9887_PORT2_ACTIVE,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xf80808,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0	= 0xf80808,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0	= 0xf80808,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0xf80808,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_KWORLD_DVB_T_CX22702] = अणु
		/* Kworld V-stream Xpert DVB-T with Thomson tuner */
		/* DTT 7579 Conexant CX22702-19 Conexant CX2388x  */
		/* Manenti Marco <marco_manenti@colman.it> */
		.name           = "KWorld/VStream XPert DVB-T with cx22702",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0700,
			.gpio2  = 0x0101,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL] = अणु
		.name           = "DViCO FusionHDTV DVB-T Dual Digital",
		.tuner_type     = UNSET, /* No analog tuner */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000067df,
		 पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000067df,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_KWORLD_HARDWARE_MPEG_TV_XPERT] = अणु
		.name           = "KWorld HardwareMpegTV XPert",
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x3de2,
			.gpio2  = 0x00ff,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x3de6,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x3de6,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x3de6,
			.gpio2  = 0x00ff,
		पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID] = अणु
		.name           = "DViCO FusionHDTV DVB-T Hybrid",
		.tuner_type     = TUNER_THOMSON_FE6600,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0000a75f,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0000a75b,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0000a75b,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PCHDTV_HD5500] = अणु
		.name           = "pcHDTV HD5500 HDTV",
		.tuner_type     = TUNER_LG_TDVS_H06XF, /* TDVS-H064F */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x87fd,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x87f9,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x87f9,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_KWORLD_MCE200_DELUXE] = अणु
		/*
		 * FIXME: tested TV input only, disabled composite,
		 * svideo and radio until they can be tested also.
		 */
		.name           = "Kworld MCE 200 Deluxe",
		.tuner_type     = TUNER_TENA_9533_DI,
		.radio_type     = UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0000BDE6
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_PIXELVIEW_PLAYTV_P7000] = अणु
		/* FIXME: SVideo, Composite and FM inमाला_दो are untested */
		.name           = "PixelView PlayTV P7000",
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE |
				  TDA9887_PORT2_ACTIVE,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x5da6,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_BLACKBIRD,
	पूर्ण,
	[CX88_BOARD_NPGTECH_REALTV_TOP10FM] = अणु
		.name           = "NPG Tech Real TV FM Top 10",
		.tuner_type     = TUNER_TNF_5335MF, /* Actually a TNF9535 */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0	= 0x0788,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0	= 0x078b,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0	= 0x078b,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0x074a,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV2000H] = अणु
		.name           = "WinFast DTV2000 H",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00017304,
			.gpio1  = 0x00008203,
			.gpio2  = 0x00017304,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0001d701,
			.gpio1  = 0x0000b207,
			.gpio2  = 0x0001d701,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE2,
			.vmux   = 2,
			.gpio0  = 0x0001d503,
			.gpio1  = 0x0000b207,
			.gpio2  = 0x0001d503,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 3,
			.gpio0  = 0x0001d701,
			.gpio1  = 0x0000b207,
			.gpio2  = 0x0001d701,
			.gpio3  = 0x02000000,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0x00015702,
			 .gpio1 = 0x0000f207,
			 .gpio2 = 0x00015702,
			 .gpio3 = 0x02000000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV2000H_J] = अणु
		.name           = "WinFast DTV2000 H rev. J",
		.tuner_type     = TUNER_PHILIPS_FMD1216MEX_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00017300,
			.gpio1  = 0x00008207,
			.gpio2	= 0x00000000,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00018300,
			.gpio1  = 0x0000f207,
			.gpio2	= 0x00017304,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00018301,
			.gpio1  = 0x0000f207,
			.gpio2	= 0x00017304,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00018301,
			.gpio1  = 0x0000f207,
			.gpio2	= 0x00017304,
			.gpio3  = 0x02000000,
		पूर्ण पूर्ण,
		.radio = अणु
			 .type  = CX88_RADIO,
			 .gpio0 = 0x00015702,
			 .gpio1 = 0x0000f207,
			 .gpio2 = 0x00015702,
			 .gpio3 = 0x02000000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_GENIATECH_DVBS] = अणु
		.name          = "Geniatech DVB-S",
		.tuner_type    = UNSET,
		.radio_type    = UNSET,
		.tuner_addr    = ADDR_UNSET,
		.radio_addr    = ADDR_UNSET,
		.input  = अणु अणु
			.type  = CX88_VMUX_DVB,
			.vmux  = 0,
		पूर्ण, अणु
			.type  = CX88_VMUX_COMPOSITE1,
			.vmux  = 1,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR3000] = अणु
		.name           = "Hauppauge WinTV-HVR3000 TriMode Analog/DVB-S/DVB-T",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.audio_chip     = CX88_AUDIO_WM8775,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x84bf,
			/* 1: TV Audio / FM Mono */
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x84bf,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x84bf,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0	= 0x84bf,
			/* 4: FM Stereo (untested) */
			.audioroute = 8,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
		.num_frontends	= 2,
	पूर्ण,
	[CX88_BOARD_NORWOOD_MICRO] = अणु
		.name           = "Norwood Micro TV Tuner",
		.tuner_type     = TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0709,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x070b,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x070b,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_TE_DTV_250_OEM_SWANN] = अणु
		.name           = "Shenzhen Tungsten Ages Tech TE-DTV-250 / Swann OEM",
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x003fffff,
			.gpio1  = 0x00e00000,
			.gpio2  = 0x003fffff,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x003fffff,
			.gpio1  = 0x00e00000,
			.gpio2  = 0x003fffff,
			.gpio3  = 0x02000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x003fffff,
			.gpio1  = 0x00e00000,
			.gpio2  = 0x003fffff,
			.gpio3  = 0x02000000,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR1300] = अणु
		.name		= "Hauppauge WinTV-HVR1300 DVB-T/Hybrid MPEG Encoder",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.audio_chip     = CX88_AUDIO_WM8775,
		/*
		 * gpio0 as reported by Mike Crash <mike AT mikecrash.com>
		 */
		.input		= अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0	= 0xef88,
			/* 1: TV Audio / FM Mono */
			.audioroute = 1,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
			.gpio0	= 0xef88,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
			.gpio0	= 0xef88,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB | CX88_MPEG_BLACKBIRD,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0	= 0xef88,
			/* 4: FM Stereo (untested) */
			.audioroute = 8,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_SAMSUNG_SMT_7020] = अणु
		.name		= "Samsung SMT 7020 DVB-S",
		.tuner_type	= UNSET,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input		= अणु अणु
			.type	= CX88_VMUX_DVB,
			.vmux	= 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_ADSTECH_PTV_390] = अणु
		.name           = "ADS Tech Instant Video PCI",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DEBUG,
			.vmux   = 3,
			.gpio0  = 0x04ff,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x07fa,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x07fa,
		पूर्ण पूर्ण,
	पूर्ण,
	[CX88_BOARD_PINNACLE_PCTV_HD_800i] = अणु
		.name           = "Pinnacle PCTV HD 800i",
		.tuner_type     = TUNER_XC5000,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x04fb,
			.gpio1  = 0x10ff,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x04fb,
			.gpio1  = 0x10ef,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x04fb,
			.gpio1  = 0x10ef,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO] = अणु
		.name           = "DViCO FusionHDTV 5 PCI nano",
		/* xc3008 tuner, digital only क्रम now */
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x000027df, /* Unconfirmed */
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000027df, /* Unconfirmed */
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000027df, /* Unconfirmed */
			.audioroute = 1,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PINNACLE_HYBRID_PCTV] = अणु
		.name           = "Pinnacle Hybrid PCTV",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x004ff,
			.gpio1  = 0x010ff,
			.gpio2  = 0x00001,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x004fb,
			.gpio1  = 0x010ef,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x004fb,
			.gpio1  = 0x010ef,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x004ff,
			.gpio1  = 0x010ff,
			.gpio2  = 0x0ff,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	/* Terry Wu <terrywu2009@gmail.com> */
	/* TV Audio :      set GPIO 2, 18, 19 value to 0, 1, 0 */
	/* FM Audio :      set GPIO 2, 18, 19 value to 0, 0, 0 */
	/* Line-in Audio : set GPIO 2, 18, 19 value to 0, 1, 1 */
	/* Mute Audio :    set GPIO 2 value to 1               */
	[CX88_BOARD_WINFAST_TV2000_XP_GLOBAL] = अणु
		.name           = "Leadtek TV2000 XP Global",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C04,       /* pin 18 = 1, pin 19 = 0 */
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C0C,       /* pin 18 = 1, pin 19 = 1 */
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C0C,       /* pin 18 = 1, pin 19 = 1 */
			.gpio3  = 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0400,        /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C00,       /* pin 18 = 0, pin 19 = 0 */
			.gpio3  = 0x0000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36] = अणु
		.name           = "Leadtek TV2000 XP Global (SC4100)",
		.tuner_type     = TUNER_XC4000,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C04,       /* pin 18 = 1, pin 19 = 0 */
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C0C,       /* pin 18 = 1, pin 19 = 1 */
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C0C,       /* pin 18 = 1, pin 19 = 1 */
			.gpio3  = 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0400,        /* pin 2 = 0 */
			.gpio1  = 0x0000,
			.gpio2  = 0x0C00,       /* pin 18 = 0, pin 19 = 0 */
			.gpio3  = 0x0000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43] = अणु
		.name           = "Leadtek TV2000 XP Global (XC4100)",
		.tuner_type     = TUNER_XC4000,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6040,       /* pin 14 = 1, pin 13 = 0 */
			.gpio2  = 0x0000,
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6060,       /* pin 14 = 1, pin 13 = 1 */
			.gpio2  = 0x0000,
			.gpio3  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6060,       /* pin 14 = 1, pin 13 = 1 */
			.gpio2  = 0x0000,
			.gpio3  = 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0400,        /* pin 2 = 0 */
			.gpio1  = 0x6000,        /* pin 14 = 1, pin 13 = 0 */
			.gpio2  = 0x0000,
			.gpio3  = 0x0000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_POWERCOLOR_REAL_ANGEL] = अणु
		/* Long names may confuse LIRC. */
		.name           = "PowerColor RA330",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.input          = अणु अणु
			/*
			 * Due to the way the cx88 driver is written,
			 * there is no way to deactivate audio pass-
			 * through without this entry. Furthermore, अगर
			 * the TV mux entry is first, you get audio
			 * from the tuner on boot क्रम a little जबतक.
			 */
			.type   = CX88_VMUX_DEBUG,
			.vmux   = 3,
			.gpio0 = 0x00ff,
			.gpio1 = 0xf39d,
			.gpio3 = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0 = 0x00ff,
			.gpio1 = 0xf35d,
			.gpio3 = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0 = 0x00ff,
			.gpio1 = 0xf37d,
			.gpio3 = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000ff,
			.gpio1  = 0x0f37d,
			.gpio3  = 0x00000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x000ff,
			.gpio1  = 0x0f35d,
			.gpio3  = 0x00000,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_GENIATECH_X8000_MT] = अणु
		/* Also PowerColor Real Angel 330 and Geniatech X800 OEM */
		.name           = "Geniatech X8000-MT DVBT",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x00000000,
			.gpio1  = 0x00e3e341,
			.gpio2  = 0x00000000,
			.gpio3  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x00000000,
			.gpio1  = 0x00e3e361,
			.gpio2  = 0x00000000,
			.gpio3  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x00000000,
			.gpio1  = 0x00e3e361,
			.gpio2  = 0x00000000,
			.gpio3  = 0x00000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x00000000,
			.gpio1  = 0x00e3e341,
			.gpio2  = 0x00000000,
			.gpio3  = 0x00000000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_NOTONLYTV_LV3H] = अणु
		.name           = "NotOnlyTV LV3H",
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr     = 0x61,
		.radio_addr     = ADDR_UNSET,
		/* अगर gpio1:bit9 is enabled, DVB-T won't work */

		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0000,
			.gpio1  = 0xa141,
			.gpio2  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0000,
			.gpio1  = 0xa161,
			.gpio2  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0000,
			.gpio1  = 0xa161,
			.gpio2  = 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0000,
			.gpio1  = 0xa141,
			.gpio2  = 0x0000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO] = अणु
		.name           = "DViCO FusionHDTV DVB-T PRO",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000067df,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000067df,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD] = अणु
		.name           = "DViCO FusionHDTV 7 Gold",
		.tuner_type     = TUNER_XC5000,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x10df,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x16d9,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x16d9,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PROLINK_PV_8000GT] = अणु
		.name           = "Prolink Pixelview MPEG 8000GT",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0 = 0x0ff,
			.gpio2 = 0x0cfb,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio2 = 0x0cfb,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio2 = 0x0cfb,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio2 = 0x0cfb,
		पूर्ण,
	पूर्ण,
	[CX88_BOARD_PROLINK_PV_GLOBAL_XTREME] = अणु
		.name           = "Prolink Pixelview Global Extreme",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0 = 0x04fb,
			.gpio1 = 0x04080,
			.gpio2 = 0x0cf7,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0 = 0x04fb,
			.gpio1 = 0x04080,
			.gpio2 = 0x0cfb,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0 = 0x04fb,
			.gpio1 = 0x04080,
			.gpio2 = 0x0cfb,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0 = 0x04ff,
			.gpio1 = 0x04080,
			.gpio2 = 0x0cf7,
		पूर्ण,
	पूर्ण,
	/*
	 * Both radio, analog and ATSC work with this board.
	 * However, क्रम analog to work, s5h1409 gate should be खोलो,
	 * otherwise, tuner-xc3028 won't be detected.
	 * A proper fix require using the newer i2c methods to add
	 * tuner-xc3028 without करोing an i2c probe.
	 */
	[CX88_BOARD_KWORLD_ATSC_120] = अणु
		.name           = "Kworld PlusTV HD PCI 120 (ATSC 120)",
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x000000ff,
			.gpio1  = 0x0000f35d,
			.gpio2  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x000000ff,
			.gpio1  = 0x0000f37e,
			.gpio2  = 0x00000000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x000000ff,
			.gpio1  = 0x0000f37e,
			.gpio2  = 0x00000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x000000ff,
			.gpio1  = 0x0000f35d,
			.gpio2  = 0x00000000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR4000] = अणु
		.name           = "Hauppauge WinTV-HVR4000 DVB-S/S2/T/Hybrid",
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.audio_chip     = CX88_AUDIO_WM8775,
		/*
		 * GPIO0 (WINTV2000)
		 *
		 * Analogue     SAT     DVB-T
		 * Antenna      0xc4bf  0xc4bb
		 * Composite    0xc4bf  0xc4bb
		 * S-Video      0xc4bf  0xc4bb
		 * Composite1   0xc4ff  0xc4fb
		 * S-Video1     0xc4ff  0xc4fb
		 *
		 * BIT  VALUE   FUNCTION GPअणुxपूर्ण_IO
		 * 0    1       I:?
		 * 1    1       I:?
		 * 2    1       O:MPEG PORT 0=DVB-T 1=DVB-S
		 * 3    1       I:?
		 * 4    1       I:?
		 * 5    1       I:?
		 * 6    0       O:INPUT SELECTOR 0=INTERNAL 1=EXPANSION
		 * 7    1       O:DVB-T DEMOD RESET LOW
		 *
		 * BIT  VALUE   FUNCTION GPअणुxपूर्ण_OE
		 * 8    0       I
		 * 9    0       I
		 * a    1       O
		 * b    0       I
		 * c    0       I
		 * d    0       I
		 * e    1       O
		 * f    1       O
		 *
		 * WM8775 ADC
		 *
		 * 1: TV Audio / FM Mono
		 * 2: Line-In
		 * 3: Line-In Expansion
		 * 4: FM Stereo
		 */
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0xc4bf,
			/* 1: TV Audio / FM Mono */
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0xc4bf,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0xc4bf,
			/* 2: Line-In */
			.audioroute = 2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0	= 0xc4bf,
			/* 4: FM Stereo */
			.audioroute = 8,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
		.num_frontends	= 2,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_HVR4000LITE] = अणु
		.name           = "Hauppauge WinTV-HVR4000(Lite) DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TEVII_S420] = अणु
		.name           = "TeVii S420 DVB-S",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TEVII_S460] = अणु
		.name           = "TeVii S460 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TEVII_S464] = अणु
		.name           = "TeVii S464 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_OMICOM_SS4_PCI] = अणु
		.name           = "Omicom SS4 DVB-S/S2 PCI",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TBS_8910] = अणु
		.name           = "TBS 8910 DVB-S",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TBS_8920] = अणु
		.name           = "TBS 8920 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
			.gpio0  = 0x8080,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PROF_6200] = अणु
		.name           = "Prof 6200 DVB-S",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PROF_7300] = अणु
		.name           = "PROF 7300 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_SATTRADE_ST4200] = अणु
		.name           = "SATTRADE ST4200 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII] = अणु
		.name           = "Terratec Cinergy HT PCI MKII",
		.tuner_type     = TUNER_XC2028,
		.tuner_addr     = 0x61,
		.radio_type     = UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x004ff,
			.gpio1  = 0x010ff,
			.gpio2  = 0x00001,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x004fb,
			.gpio1  = 0x010ef,
			.audioroute = 1,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x004fb,
			.gpio1  = 0x010ef,
			.audioroute = 1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x004ff,
			.gpio1  = 0x010ff,
			.gpio2  = 0x0ff,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_HAUPPAUGE_IRONLY] = अणु
		.name           = "Hauppauge WinTV-IR Only",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV1800H] = अणु
		.name           = "Leadtek WinFast DTV1800 Hybrid",
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr     = 0x61,
		.radio_addr     = ADDR_UNSET,
		/*
		 * GPIO setting
		 *
		 *  2: mute (0=off,1=on)
		 * 12: tuner reset pin
		 * 13: audio source (0=tuner audio,1=line in)
		 * 14: FM (0=on,1=off ???)
		 */
		.input          = अणु अणु
			.type   = CX88_VMUX_TELEVISION,
			.vmux   = 0,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6040,       /* pin 13 = 0, pin 14 = 1 */
			.gpio2  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_COMPOSITE1,
			.vmux   = 1,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6060,       /* pin 13 = 1, pin 14 = 1 */
			.gpio2  = 0x0000,
		पूर्ण, अणु
			.type   = CX88_VMUX_SVIDEO,
			.vmux   = 2,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6060,       /* pin 13 = 1, pin 14 = 1 */
			.gpio2  = 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type   = CX88_RADIO,
			.gpio0  = 0x0400,       /* pin 2 = 0 */
			.gpio1  = 0x6000,       /* pin 13 = 0, pin 14 = 0 */
			.gpio2  = 0x0000,
		पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV1800H_XC4000] = अणु
		.name		= "Leadtek WinFast DTV1800 H (XC4000)",
		.tuner_type	= TUNER_XC4000,
		.radio_type	= UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		/*
		 * GPIO setting
		 *
		 *  2: mute (0=off,1=on)
		 * 12: tuner reset pin
		 * 13: audio source (0=tuner audio,1=line in)
		 * 14: FM (0=on,1=off ???)
		 */
		.input		= अणु अणु
			.type	= CX88_VMUX_TELEVISION,
			.vmux	= 0,
			.gpio0	= 0x0400,	/* pin 2 = 0 */
			.gpio1	= 0x6040,	/* pin 13 = 0, pin 14 = 1 */
			.gpio2	= 0x0000,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
			.gpio0	= 0x0400,	/* pin 2 = 0 */
			.gpio1	= 0x6060,	/* pin 13 = 1, pin 14 = 1 */
			.gpio2	= 0x0000,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
			.gpio0	= 0x0400,	/* pin 2 = 0 */
			.gpio1	= 0x6060,	/* pin 13 = 1, pin 14 = 1 */
			.gpio2	= 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type	= CX88_RADIO,
			.gpio0	= 0x0400,	/* pin 2 = 0 */
			.gpio1	= 0x6000,	/* pin 13 = 0, pin 14 = 0 */
			.gpio2	= 0x0000,
		पूर्ण,
		.mpeg		= CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_WINFAST_DTV2000H_PLUS] = अणु
		.name		= "Leadtek WinFast DTV2000 H PLUS",
		.tuner_type	= TUNER_XC4000,
		.radio_type	= UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		/*
		 * GPIO
		 *   2: 1: mute audio
		 *  12: 0: reset XC4000
		 *  13: 1: audio input is line in (0: tuner)
		 *  14: 0: FM radio
		 *  16: 0: RF input is cable
		 */
		.input		= अणु अणु
			.type	= CX88_VMUX_TELEVISION,
			.vmux	= 0,
			.gpio0	= 0x0403,
			.gpio1	= 0xF0D7,
			.gpio2	= 0x0101,
			.gpio3	= 0x0000,
		पूर्ण, अणु
			.type	= CX88_VMUX_CABLE,
			.vmux	= 0,
			.gpio0	= 0x0403,
			.gpio1	= 0xF0D7,
			.gpio2	= 0x0100,
			.gpio3	= 0x0000,
		पूर्ण, अणु
			.type	= CX88_VMUX_COMPOSITE1,
			.vmux	= 1,
			.gpio0	= 0x0403,	/* was 0x0407 */
			.gpio1	= 0xF0F7,
			.gpio2	= 0x0101,
			.gpio3	= 0x0000,
		पूर्ण, अणु
			.type	= CX88_VMUX_SVIDEO,
			.vmux	= 2,
			.gpio0	= 0x0403,	/* was 0x0407 */
			.gpio1	= 0xF0F7,
			.gpio2	= 0x0101,
			.gpio3	= 0x0000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type	= CX88_RADIO,
			.gpio0	= 0x0403,
			.gpio1	= 0xF097,
			.gpio2	= 0x0100,
			.gpio3	= 0x0000,
		पूर्ण,
		.mpeg		= CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_PROF_7301] = अणु
		.name           = "Prof 7301 DVB-S/S2",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
			.type   = CX88_VMUX_DVB,
			.vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
	[CX88_BOARD_TWINHAN_VP1027_DVBS] = अणु
		.name		= "Twinhan VP-1027 DVB-S",
		.tuner_type     = UNSET,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.input          = अणु अणु
		       .type   = CX88_VMUX_DVB,
		       .vmux   = 0,
		पूर्ण पूर्ण,
		.mpeg           = CX88_MPEG_DVB,
	पूर्ण,
पूर्ण;

/* ------------------------------------------------------------------ */
/* PCI subप्रणाली IDs                                                  */

अटल स्थिर काष्ठा cx88_subid cx88_subids[] = अणु
	अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x3400,
		.card      = CX88_BOARD_HAUPPAUGE,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x3401,
		.card      = CX88_BOARD_HAUPPAUGE,
	पूर्ण, अणु
		.subvenकरोr = 0x14c7,
		.subdevice = 0x0106,
		.card      = CX88_BOARD_GDI,
	पूर्ण, अणु
		.subvenकरोr = 0x14c7,
		.subdevice = 0x0107, /* with mpeg encoder */
		.card      = CX88_BOARD_GDI,
	पूर्ण, अणु
		.subvenकरोr = PCI_VENDOR_ID_ATI,
		.subdevice = 0x00f8,
		.card      = CX88_BOARD_ATI_WONDER_PRO,
	पूर्ण, अणु
		.subvenकरोr = PCI_VENDOR_ID_ATI,
		.subdevice = 0x00f9,
		.card      = CX88_BOARD_ATI_WONDER_PRO,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6611,
		.card      = CX88_BOARD_WINFAST2000XP_EXPERT,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6613,	/* NTSC */
		.card      = CX88_BOARD_WINFAST2000XP_EXPERT,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6620,
		.card      = CX88_BOARD_WINFAST_DV2000,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x663b,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x663c,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0x000b,
		.card      = CX88_BOARD_AVERTV_STUDIO_303,
	पूर्ण, अणु
		.subvenकरोr = 0x1462,
		.subdevice = 0x8606,
		.card      = CX88_BOARD_MSI_TVANYWHERE_MASTER,
	पूर्ण, अणु
		.subvenकरोr = 0x10fc,
		.subdevice = 0xd003,
		.card      = CX88_BOARD_IODATA_GVVCP3PCI,
	पूर्ण, अणु
		.subvenकरोr = 0x1043,
		.subdevice = 0x4823,  /* with mpeg encoder */
		.card      = CX88_BOARD_ASUS_PVR_416,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x08a6,
		.card      = CX88_BOARD_KWORLD_DVB_T,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd810,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd820,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_T,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb00,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9002,
		.card      = CX88_BOARD_HAUPPAUGE_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x0187,
		.card      = CX88_BOARD_CONEXANT_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x1540,
		.subdevice = 0x2580,
		.card      = CX88_BOARD_PROVIDEO_PV259,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb10,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS,
	पूर्ण, अणु
		.subvenकरोr = 0x1554,
		.subdevice = 0x4811,
		.card      = CX88_BOARD_PIXELVIEW,
	पूर्ण, अणु
		.subvenकरोr = 0x7063,
		.subdevice = 0x3000, /* HD-3000 card */
		.card      = CX88_BOARD_PCHDTV_HD3000,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0xa8a6,
		.card      = CX88_BOARD_DNTV_LIVE_DVB_T,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x2801,
		.card      = CX88_BOARD_HAUPPAUGE_ROSLYN,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x0342,
		.card      = CX88_BOARD_DIGITALLOGIC_MEC,
	पूर्ण, अणु
		.subvenकरोr = 0x10fc,
		.subdevice = 0xd035,
		.card      = CX88_BOARD_IODATA_GVBCTV7E,
	पूर्ण, अणु
		.subvenकरोr = 0x1421,
		.subdevice = 0x0334,
		.card      = CX88_BOARD_ADSTECH_DVB_T_PCI,
	पूर्ण, अणु
		.subvenकरोr = 0x153b,
		.subdevice = 0x1166,
		.card      = CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd500,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD,
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0x8011,
		.card      = CX88_BOARD_AVERMEDIA_ULTRATV_MC_550,
	पूर्ण, अणु
		.subvenकरोr = PCI_VENDOR_ID_ATI,
		.subdevice = 0xa101,
		.card      = CX88_BOARD_ATI_HDTVWONDER,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x665f,
		.card      = CX88_BOARD_WINFAST_DTV1000,
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0x000a,
		.card      = CX88_BOARD_AVERTV_303,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9200,
		.card      = CX88_BOARD_HAUPPAUGE_NOVASE2_S1,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9201,
		.card      = CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9202,
		.card      = CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x08b2,
		.card      = CX88_BOARD_KWORLD_DVBS_100,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9400,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1100,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9402,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1100,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9800,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1100LP,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9802,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1100LP,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9001,
		.card      = CX88_BOARD_HAUPPAUGE_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x1822,
		.subdevice = 0x0025,
		.card      = CX88_BOARD_DNTV_LIVE_DVB_T_PRO,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x08a1,
		.card      = CX88_BOARD_KWORLD_DVB_T_CX22702,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb50,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb54,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL,
		/* Re-bअक्रमed DViCO: DigitalNow DVB-T Dual */
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb11,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS,
		/* Re-bअक्रमed DViCO: UltraView DVB-T Plus */
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb30,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x0840,
		.card      = CX88_BOARD_KWORLD_HARDWARE_MPEG_TV_XPERT,
	पूर्ण, अणु
		.subvenकरोr = 0x1421,
		.subdevice = 0x0305,
		.card      = CX88_BOARD_KWORLD_HARDWARE_MPEG_TV_XPERT,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb40,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdb44,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID,
	पूर्ण, अणु
		.subvenकरोr = 0x7063,
		.subdevice = 0x5500,
		.card      = CX88_BOARD_PCHDTV_HD5500,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x0841,
		.card      = CX88_BOARD_KWORLD_MCE200_DELUXE,
	पूर्ण, अणु
		.subvenकरोr = 0x1822,
		.subdevice = 0x0019,
		.card      = CX88_BOARD_DNTV_LIVE_DVB_T_PRO,
	पूर्ण, अणु
		.subvenकरोr = 0x1554,
		.subdevice = 0x4813,
		.card      = CX88_BOARD_PIXELVIEW_PLAYTV_P7000,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x0842,
		.card      = CX88_BOARD_NPGTECH_REALTV_TOP10FM,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x665e,
		.card      = CX88_BOARD_WINFAST_DTV2000H,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f2b,
		.card      = CX88_BOARD_WINFAST_DTV2000H_J,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd800, /* FusionHDTV 3 Gold (original revision) */
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0x0084,
		.card      = CX88_BOARD_GENIATECH_DVBS,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x1404,
		.card      = CX88_BOARD_HAUPPAUGE_HVR3000,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdc00,
		.card      = CX88_BOARD_SAMSUNG_SMT_7020,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xdccd,
		.card      = CX88_BOARD_SAMSUNG_SMT_7020,
	पूर्ण, अणु
		.subvenकरोr = 0x1461,
		.subdevice = 0xc111, /* AverMedia M150-D */
		/* This board is known to work with the ASUS PVR416 config */
		.card      = CX88_BOARD_ASUS_PVR_416,
	पूर्ण, अणु
		.subvenकरोr = 0xc180,
		.subdevice = 0xc980,
		.card      = CX88_BOARD_TE_DTV_250_OEM_SWANN,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9600,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1300,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9601,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1300,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9602,
		.card      = CX88_BOARD_HAUPPAUGE_HVR1300,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6632,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		.subvenकरोr = 0x12ab,
		.subdevice = 0x2300, /* Club3D Zap TV2100 */
		.card      = CX88_BOARD_KWORLD_DVB_T_CX22702,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9000,
		.card      = CX88_BOARD_HAUPPAUGE_DVB_T1,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x1400,
		.card      = CX88_BOARD_HAUPPAUGE_HVR3000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x1401,
		.card      = CX88_BOARD_HAUPPAUGE_HVR3000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x1402,
		.card      = CX88_BOARD_HAUPPAUGE_HVR3000,
	पूर्ण, अणु
		.subvenकरोr = 0x1421,
		.subdevice = 0x0341, /* ADS Tech InstantTV DVB-S */
		.card      = CX88_BOARD_KWORLD_DVBS_100,
	पूर्ण, अणु
		.subvenकरोr = 0x1421,
		.subdevice = 0x0390,
		.card      = CX88_BOARD_ADSTECH_PTV_390,
	पूर्ण, अणु
		.subvenकरोr = 0x11bd,
		.subdevice = 0x0051,
		.card      = CX88_BOARD_PINNACLE_PCTV_HD_800i,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd530,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO,
	पूर्ण, अणु
		.subvenकरोr = 0x12ab,
		.subdevice = 0x1788,
		.card      = CX88_BOARD_PINNACLE_HYBRID_PCTV,
	पूर्ण, अणु
		.subvenकरोr = 0x14f1,
		.subdevice = 0xea3d,
		.card      = CX88_BOARD_POWERCOLOR_REAL_ANGEL,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f18,
		.card      = CX88_BOARD_WINFAST_TV2000_XP_GLOBAL,
	पूर्ण, अणु
		/* Also NotOnlyTV LV3H (version 1.11 is silkscreened on the board) */
		.subvenकरोr = 0x14f1,
		.subdevice = 0x8852,
		.card      = CX88_BOARD_GENIATECH_X8000_MT,
	पूर्ण, अणु
		.subvenकरोr = 0x18ac,
		.subdevice = 0xd610,
		.card      = CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD,
	पूर्ण, अणु
		.subvenकरोr = 0x1554,
		.subdevice = 0x4935,
		.card      = CX88_BOARD_PROLINK_PV_8000GT,
	पूर्ण, अणु
		.subvenकरोr = 0x1554,
		.subdevice = 0x4976,
		.card      = CX88_BOARD_PROLINK_PV_GLOBAL_XTREME,
	पूर्ण, अणु
		.subvenकरोr = 0x17de,
		.subdevice = 0x08c1,
		.card      = CX88_BOARD_KWORLD_ATSC_120,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6900,
		.card      = CX88_BOARD_HAUPPAUGE_HVR4000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6904,
		.card      = CX88_BOARD_HAUPPAUGE_HVR4000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6902,
		.card      = CX88_BOARD_HAUPPAUGE_HVR4000,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6905,
		.card      = CX88_BOARD_HAUPPAUGE_HVR4000LITE,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x6906,
		.card      = CX88_BOARD_HAUPPAUGE_HVR4000LITE,
	पूर्ण, अणु
		.subvenकरोr = 0xd420,
		.subdevice = 0x9022,
		.card      = CX88_BOARD_TEVII_S420,
	पूर्ण, अणु
		.subvenकरोr = 0xd460,
		.subdevice = 0x9022,
		.card      = CX88_BOARD_TEVII_S460,
	पूर्ण, अणु
		.subvenकरोr = 0xd464,
		.subdevice = 0x9022,
		.card      = CX88_BOARD_TEVII_S464,
	पूर्ण, अणु
		.subvenकरोr = 0xA044,
		.subdevice = 0x2011,
		.card      = CX88_BOARD_OMICOM_SS4_PCI,
	पूर्ण, अणु
		.subvenकरोr = 0x8910,
		.subdevice = 0x8888,
		.card      = CX88_BOARD_TBS_8910,
	पूर्ण, अणु
		.subvenकरोr = 0x8920,
		.subdevice = 0x8888,
		.card      = CX88_BOARD_TBS_8920,
	पूर्ण, अणु
		.subvenकरोr = 0xb022,
		.subdevice = 0x3022,
		.card      = CX88_BOARD_PROF_6200,
	पूर्ण, अणु
		.subvenकरोr = 0xB033,
		.subdevice = 0x3033,
		.card      = CX88_BOARD_PROF_7300,
	पूर्ण, अणु
		.subvenकरोr = 0xb200,
		.subdevice = 0x4200,
		.card      = CX88_BOARD_SATTRADE_ST4200,
	पूर्ण, अणु
		.subvenकरोr = 0x153b,
		.subdevice = 0x1177,
		.card      = CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII,
	पूर्ण, अणु
		.subvenकरोr = 0x0070,
		.subdevice = 0x9290,
		.card      = CX88_BOARD_HAUPPAUGE_IRONLY,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6654,
		.card      = CX88_BOARD_WINFAST_DTV1800H,
	पूर्ण, अणु
		/* WinFast DTV1800 H with XC4000 tuner */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f38,
		.card      = CX88_BOARD_WINFAST_DTV1800H_XC4000,
	पूर्ण, अणु
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f42,
		.card      = CX88_BOARD_WINFAST_DTV2000H_PLUS,
	पूर्ण, अणु
		/* PVR2000 PAL Model [107d:6630] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6630,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		/* PVR2000 PAL Model [107d:6638] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6638,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		/* PVR2000 NTSC Model [107d:6631] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6631,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		/* PVR2000 NTSC Model [107d:6637] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6637,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		/* PVR2000 NTSC Model [107d:663d] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x663d,
		.card      = CX88_BOARD_LEADTEK_PVR2000,
	पूर्ण, अणु
		/* DV2000 NTSC Model [107d:6621] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6621,
		.card      = CX88_BOARD_WINFAST_DV2000,
	पूर्ण, अणु
		/* TV2000 XP Global [107d:6618]  */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6618,
		.card      = CX88_BOARD_WINFAST_TV2000_XP_GLOBAL,
	पूर्ण, अणु
		/* TV2000 XP Global [107d:6618] */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6619,
		.card      = CX88_BOARD_WINFAST_TV2000_XP_GLOBAL,
	पूर्ण, अणु
		/* WinFast TV2000 XP Global with XC4000 tuner */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f36,
		.card      = CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36,
	पूर्ण, अणु
		/* WinFast TV2000 XP Global with XC4000 tuner and dअगरferent GPIOs */
		.subvenकरोr = 0x107d,
		.subdevice = 0x6f43,
		.card      = CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43,
	पूर्ण, अणु
		.subvenकरोr = 0xb034,
		.subdevice = 0x3034,
		.card      = CX88_BOARD_PROF_7301,
	पूर्ण, अणु
		.subvenकरोr = 0x1822,
		.subdevice = 0x0023,
		.card      = CX88_BOARD_TWINHAN_VP1027_DVBS,
	पूर्ण,
पूर्ण;

/*
 * some leadtek specअगरic stuff
 */
अटल व्योम leadtek_eeprom(काष्ठा cx88_core *core, u8 *eeprom_data)
अणु
	अगर (eeprom_data[4] != 0x7d ||
	    eeprom_data[5] != 0x10 ||
	    eeprom_data[7] != 0x66) अणु
		pr_warn("Leadtek eeprom invalid.\n");
		वापस;
	पूर्ण

	/* Terry Wu <terrywu2009@gmail.com> */
	चयन (eeprom_data[6]) अणु
	हाल 0x13: /* SSID 6613 क्रम TV2000 XP Expert NTSC Model */
	हाल 0x21: /* SSID 6621 क्रम DV2000 NTSC Model */
	हाल 0x31: /* SSID 6631 क्रम PVR2000 NTSC Model */
	हाल 0x37: /* SSID 6637 क्रम PVR2000 NTSC Model */
	हाल 0x3d: /* SSID 6637 क्रम PVR2000 NTSC Model */
		core->board.tuner_type = TUNER_PHILIPS_FM1236_MK3;
		अवरोध;
	शेष:
		core->board.tuner_type = TUNER_PHILIPS_FM1216ME_MK3;
		अवरोध;
	पूर्ण

	pr_info("Leadtek Winfast 2000XP Expert config: tuner=%d, eeprom[0]=0x%02x\n",
		core->board.tuner_type, eeprom_data[0]);
पूर्ण

अटल व्योम hauppauge_eeprom(काष्ठा cx88_core *core, u8 *eeprom_data)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);
	core->board.tuner_type = tv.tuner_type;
	core->tuner_क्रमmats = tv.tuner_क्रमmats;
	core->board.radio.type = tv.has_radio ? CX88_RADIO : 0;
	core->model = tv.model;

	/* Make sure we support the board model */
	चयन (tv.model) अणु
	हाल 14009: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in) */
	हाल 14019: /* WinTV-HVR3000 (Retail, IR Blaster, b/panel video, 3.5mm audio in) */
	हाल 14029: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - 880 bridge) */
	हाल 14109: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - low profile) */
	हाल 14129: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - 880 bridge - LP) */
	हाल 14559: /* WinTV-HVR3000 (OEM, no IR, b/panel video, 3.5mm audio in) */
	हाल 14569: /* WinTV-HVR3000 (OEM, no IR, no back panel video) */
	हाल 14659: /* WinTV-HVR3000 (OEM, no IR, b/panel video, RCA audio in - Low profile) */
	हाल 14669: /* WinTV-HVR3000 (OEM, no IR, no b/panel video - Low profile) */
	हाल 28552: /* WinTV-PVR 'Roslyn' (No IR) */
	हाल 34519: /* WinTV-PCI-FM */
	हाल 69009:
		/* WinTV-HVR4000 (DVBS/S2/T, Video and IR, back panel inमाला_दो) */
	हाल 69100: /* WinTV-HVR4000LITE (DVBS/S2, IR) */
	हाल 69500: /* WinTV-HVR4000LITE (DVBS/S2, No IR) */
	हाल 69559:
		/* WinTV-HVR4000 (DVBS/S2/T, Video no IR, back panel inमाला_दो) */
	हाल 69569: /* WinTV-HVR4000 (DVBS/S2/T, Video no IR) */
	हाल 90002: /* Nova-T-PCI (9002) */
	हाल 92001: /* Nova-S-Plus (Video and IR) */
	हाल 92002: /* Nova-S-Plus (Video and IR) */
	हाल 90003: /* Nova-T-PCI (9002 No RF out) */
	हाल 90500: /* Nova-T-PCI (oem) */
	हाल 90501: /* Nova-T-PCI (oem/IR) */
	हाल 92000: /* Nova-SE2 (OEM, No Video or IR) */
	हाल 92900: /* WinTV-IROnly (No analog or digital Video inमाला_दो) */
	हाल 94009: /* WinTV-HVR1100 (Video and IR Retail) */
	हाल 94501: /* WinTV-HVR1100 (Video and IR OEM) */
	हाल 96009: /* WinTV-HVR1300 (PAL Video, MPEG Video and IR RX) */
	हाल 96019: /* WinTV-HVR1300 (PAL Video, MPEG Video and IR RX/TX) */
	हाल 96559: /* WinTV-HVR1300 (PAL Video, MPEG Video no IR) */
	हाल 96569: /* WinTV-HVR1300 () */
	हाल 96659: /* WinTV-HVR1300 () */
	हाल 98559: /* WinTV-HVR1100LP (Video no IR, Retail - Low Profile) */
		/* known */
		अवरोध;
	हाल CX88_BOARD_SAMSUNG_SMT_7020:
		cx_set(MO_GP0_IO, 0x008989FF);
		अवरोध;
	शेष:
		pr_warn("warning: unknown hauppauge model #%d\n", tv.model);
		अवरोध;
	पूर्ण

	pr_info("hauppauge eeprom: model=%d\n", tv.model);
पूर्ण

/*
 * some GDI (was: Modular Technology) specअगरic stuff
 */

अटल स्थिर काष्ठा अणु
	पूर्णांक  id;
	पूर्णांक  fm;
	स्थिर अक्षर *name;
पूर्ण gdi_tuner[] = अणु
	[0x01] = अणु .id   = UNSET,
		   .name = "NTSC_M" पूर्ण,
	[0x02] = अणु .id   = UNSET,
		   .name = "PAL_B" पूर्ण,
	[0x03] = अणु .id   = UNSET,
		   .name = "PAL_I" पूर्ण,
	[0x04] = अणु .id   = UNSET,
		   .name = "PAL_D" पूर्ण,
	[0x05] = अणु .id   = UNSET,
		   .name = "SECAM" पूर्ण,

	[0x10] = अणु .id   = UNSET,
		   .fm   = 1,
		   .name = "TEMIC_4049" पूर्ण,
	[0x11] = अणु .id   = TUNER_TEMIC_4136FY5,
		   .name = "TEMIC_4136" पूर्ण,
	[0x12] = अणु .id   = UNSET,
		   .name = "TEMIC_4146" पूर्ण,

	[0x20] = अणु .id   = TUNER_PHILIPS_FQ1216ME,
		   .fm   = 1,
		   .name = "PHILIPS_FQ1216_MK3" पूर्ण,
	[0x21] = अणु .id   = UNSET, .fm = 1,
		   .name = "PHILIPS_FQ1236_MK3" पूर्ण,
	[0x22] = अणु .id   = UNSET,
		   .name = "PHILIPS_FI1236_MK3" पूर्ण,
	[0x23] = अणु .id   = UNSET,
		   .name = "PHILIPS_FI1216_MK3" पूर्ण,
पूर्ण;

अटल व्योम gdi_eeprom(काष्ठा cx88_core *core, u8 *eeprom_data)
अणु
	स्थिर अक्षर *name = (eeprom_data[0x0d] < ARRAY_SIZE(gdi_tuner))
		? gdi_tuner[eeprom_data[0x0d]].name : शून्य;

	pr_info("GDI: tuner=%s\n", name ? name : "unknown");
	अगर (!name)
		वापस;
	core->board.tuner_type = gdi_tuner[eeprom_data[0x0d]].id;
	core->board.radio.type = gdi_tuner[eeprom_data[0x0d]].fm ?
		CX88_RADIO : 0;
पूर्ण

/*
 * some Divco specअगरic stuff
 */
अटल पूर्णांक cx88_dvico_xc2028_callback(काष्ठा cx88_core *core,
				      पूर्णांक command, पूर्णांक arg)
अणु
	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		चयन (core->boardnr) अणु
		हाल CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO:
			/* GPIO-4 xc3028 tuner */

			cx_set(MO_GP0_IO, 0x00001000);
			cx_clear(MO_GP0_IO, 0x00000010);
			msleep(100);
			cx_set(MO_GP0_IO, 0x00000010);
			msleep(100);
			अवरोध;
		शेष:
			cx_ग_लिखो(MO_GP0_IO, 0x101000);
			mdelay(5);
			cx_set(MO_GP0_IO, 0x101010);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * some Geniatech specअगरic stuff
 */

अटल पूर्णांक cx88_xc3028_geniatech_tuner_callback(काष्ठा cx88_core *core,
						पूर्णांक command, पूर्णांक mode)
अणु
	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		चयन (INPUT(core->input).type) अणु
		हाल CX88_RADIO:
			अवरोध;
		हाल CX88_VMUX_DVB:
			cx_ग_लिखो(MO_GP1_IO, 0x030302);
			mdelay(50);
			अवरोध;
		शेष:
			cx_ग_लिखो(MO_GP1_IO, 0x030301);
			mdelay(50);
		पूर्ण
		cx_ग_लिखो(MO_GP1_IO, 0x101010);
		mdelay(50);
		cx_ग_लिखो(MO_GP1_IO, 0x101000);
		mdelay(50);
		cx_ग_लिखो(MO_GP1_IO, 0x101010);
		mdelay(50);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cx88_xc3028_winfast1800h_callback(काष्ठा cx88_core *core,
					     पूर्णांक command, पूर्णांक arg)
अणु
	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		/* GPIO 12 (xc3028 tuner reset) */
		cx_set(MO_GP1_IO, 0x1010);
		mdelay(50);
		cx_clear(MO_GP1_IO, 0x10);
		mdelay(75);
		cx_set(MO_GP1_IO, 0x10);
		mdelay(75);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cx88_xc4000_winfast2000h_plus_callback(काष्ठा cx88_core *core,
						  पूर्णांक command, पूर्णांक arg)
अणु
	चयन (command) अणु
	हाल XC4000_TUNER_RESET:
		/* GPIO 12 (xc4000 tuner reset) */
		cx_set(MO_GP1_IO, 0x1010);
		mdelay(50);
		cx_clear(MO_GP1_IO, 0x10);
		mdelay(75);
		cx_set(MO_GP1_IO, 0x10);
		mdelay(75);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * some Divco specअगरic stuff
 */
अटल पूर्णांक cx88_pv_8000gt_callback(काष्ठा cx88_core *core,
				   पूर्णांक command, पूर्णांक arg)
अणु
	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		cx_ग_लिखो(MO_GP2_IO, 0xcf7);
		mdelay(50);
		cx_ग_लिखो(MO_GP2_IO, 0xef5);
		mdelay(50);
		cx_ग_लिखो(MO_GP2_IO, 0xcf7);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * some DViCO specअगरic stuff
 */

अटल व्योम dvico_fusionhdtv_hybrid_init(काष्ठा cx88_core *core)
अणु
	काष्ठा i2c_msg msg = अणु .addr = 0x45, .flags = 0 पूर्ण;
	पूर्णांक i, err;
	अटल u8 init_bufs[13][5] = अणु
		अणु 0x10, 0x00, 0x20, 0x01, 0x03 पूर्ण,
		अणु 0x10, 0x10, 0x01, 0x00, 0x21 पूर्ण,
		अणु 0x10, 0x10, 0x10, 0x00, 0xCA पूर्ण,
		अणु 0x10, 0x10, 0x12, 0x00, 0x08 पूर्ण,
		अणु 0x10, 0x10, 0x13, 0x00, 0x0A पूर्ण,
		अणु 0x10, 0x10, 0x16, 0x01, 0xC0 पूर्ण,
		अणु 0x10, 0x10, 0x22, 0x01, 0x3D पूर्ण,
		अणु 0x10, 0x10, 0x73, 0x01, 0x2E पूर्ण,
		अणु 0x10, 0x10, 0x72, 0x00, 0xC5 पूर्ण,
		अणु 0x10, 0x10, 0x71, 0x01, 0x97 पूर्ण,
		अणु 0x10, 0x10, 0x70, 0x00, 0x0F पूर्ण,
		अणु 0x10, 0x10, 0xB0, 0x00, 0x01 पूर्ण,
		अणु 0x03, 0x0C पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(init_bufs); i++) अणु
		msg.buf = init_bufs[i];
		msg.len = (i != 12 ? 5 : 2);
		err = i2c_transfer(&core->i2c_adap, &msg, 1);
		अगर (err != 1) अणु
			pr_warn("dvico_fusionhdtv_hybrid_init buf %d failed (err = %d)!\n",
				i, err);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cx88_xc2028_tuner_callback(काष्ठा cx88_core *core,
				      पूर्णांक command, पूर्णांक arg)
अणु
	/* Board-specअगरic callbacks */
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_POWERCOLOR_REAL_ANGEL:
	हाल CX88_BOARD_GENIATECH_X8000_MT:
	हाल CX88_BOARD_KWORLD_ATSC_120:
		वापस cx88_xc3028_geniatech_tuner_callback(core,
							command, arg);
	हाल CX88_BOARD_PROLINK_PV_8000GT:
	हाल CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
		वापस cx88_pv_8000gt_callback(core, command, arg);
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO:
		वापस cx88_dvico_xc2028_callback(core, command, arg);
	हाल CX88_BOARD_NOTONLYTV_LV3H:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	हाल CX88_BOARD_WINFAST_DTV1800H:
		वापस cx88_xc3028_winfast1800h_callback(core, command, arg);
	पूर्ण

	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		चयन (INPUT(core->input).type) अणु
		हाल CX88_RADIO:
			dprपूर्णांकk(1, "setting GPIO to radio!\n");
			cx_ग_लिखो(MO_GP0_IO, 0x4ff);
			mdelay(250);
			cx_ग_लिखो(MO_GP2_IO, 0xff);
			mdelay(250);
			अवरोध;
		हाल CX88_VMUX_DVB:	/* Digital TV*/
		शेष:		/* Analog TV */
			dprपूर्णांकk(1, "setting GPIO to TV!\n");
			अवरोध;
		पूर्ण
		cx_ग_लिखो(MO_GP1_IO, 0x101010);
		mdelay(250);
		cx_ग_लिखो(MO_GP1_IO, 0x101000);
		mdelay(250);
		cx_ग_लिखो(MO_GP1_IO, 0x101010);
		mdelay(250);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cx88_xc4000_tuner_callback(काष्ठा cx88_core *core,
				      पूर्णांक command, पूर्णांक arg)
अणु
	/* Board-specअगरic callbacks */
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_WINFAST_DTV1800H_XC4000:
	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43:
		वापस cx88_xc4000_winfast2000h_plus_callback(core,
							      command, arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Tuner callback function. Currently only needed क्रम the Pinnacle
 * PCTV HD 800i with an xc5000 silicon tuner. This is used क्रम both
 * analog tuner attach (tuner-core.c) and dvb tuner attach (cx88-dvb.c)
 */
अटल पूर्णांक cx88_xc5000_tuner_callback(काष्ठा cx88_core *core,
				      पूर्णांक command, पूर्णांक arg)
अणु
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_PINNACLE_PCTV_HD_800i:
		अगर (command == 0) अणु /* This is the reset command from xc5000 */

			/*
			 * djh - According to the engineer at PCTV Systems,
			 * the xc5000 reset pin is supposed to be on GPIO12.
			 * However, despite three nights of efक्रमt, pulling
			 * that GPIO low didn't reset the xc5000.  While
			 * pulling MO_SRST_IO low करोes reset the xc5000, this
			 * also resets in the s5h1409 being reset as well.
			 * This causes tuning to always fail since the पूर्णांकernal
			 * state of the s5h1409 करोes not match the driver's
			 * state.  Given that the only two conditions in which
			 * the driver perक्रमms a reset is during firmware load
			 * and घातering करोwn the chip, I am taking out the
			 * reset.  We know that the chip is being reset
			 * when the cx88 comes online, and not being able to
			 * करो घातer management क्रम this board is worse than
			 * not having any tuning at all.
			 */
			वापस 0;
		पूर्ण

		dprपूर्णांकk(1, "xc5000: unknown tuner callback command.\n");
		वापस -EINVAL;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD:
		अगर (command == 0) अणु /* This is the reset command from xc5000 */
			cx_clear(MO_GP0_IO, 0x00000010);
			usleep_range(10000, 20000);
			cx_set(MO_GP0_IO, 0x00000010);
			वापस 0;
		पूर्ण

		dprपूर्णांकk(1, "xc5000: unknown tuner callback command.\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0; /* Should never be here */
पूर्ण

पूर्णांक cx88_tuner_callback(व्योम *priv, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा i2c_algo_bit_data *i2c_algo = priv;
	काष्ठा cx88_core *core;

	अगर (!i2c_algo) अणु
		pr_err("Error - i2c private data undefined.\n");
		वापस -EINVAL;
	पूर्ण

	core = i2c_algo->data;

	अगर (!core) अणु
		pr_err("Error - device struct undefined.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (component != DVB_FRONTEND_COMPONENT_TUNER)
		वापस -EINVAL;

	चयन (core->board.tuner_type) अणु
	हाल TUNER_XC2028:
		dprपूर्णांकk(1, "Calling XC2028/3028 callback\n");
		वापस cx88_xc2028_tuner_callback(core, command, arg);
	हाल TUNER_XC4000:
		dprपूर्णांकk(1, "Calling XC4000 callback\n");
		वापस cx88_xc4000_tuner_callback(core, command, arg);
	हाल TUNER_XC5000:
		dprपूर्णांकk(1, "Calling XC5000 callback\n");
		वापस cx88_xc5000_tuner_callback(core, command, arg);
	पूर्ण
	pr_err("Error: Calling callback for tuner %d\n",
	       core->board.tuner_type);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(cx88_tuner_callback);

/* ----------------------------------------------------------------------- */

अटल व्योम cx88_card_list(काष्ठा cx88_core *core, काष्ठा pci_dev *pci)
अणु
	पूर्णांक i;

	अगर (!pci->subप्रणाली_venकरोr && !pci->subप्रणाली_device) अणु
		pr_err("Your board has no valid PCI Subsystem ID and thus can't\n");
		pr_err("be autodetected.  Please pass card=<n> insmod option to\n");
		pr_err("workaround that.  Redirect complaints to the vendor of\n");
		pr_err("the TV card\n");
	पूर्ण अन्यथा अणु
		pr_err("Your board isn't known (yet) to the driver.  You can\n");
		pr_err("try to pick one of the existing card configs via\n");
		pr_err("card=<n> insmod option.  Updating to the latest\n");
		pr_err("version might help as well.\n");
	पूर्ण
	pr_err("Here is a list of valid choices for the card=<n> insmod option:\n");
	क्रम (i = 0; i < ARRAY_SIZE(cx88_boards); i++)
		pr_err("    card=%d -> %s\n", i, cx88_boards[i].name);
पूर्ण

अटल व्योम cx88_card_setup_pre_i2c(काष्ठा cx88_core *core)
अणु
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		/*
		 * Bring the 702 demod up beक्रमe i2c scanning/attach or
		 * devices are hidden.
		 *
		 * We leave here with the 702 on the bus
		 *
		 * "reset the IR receiver on GPIO[3]"
		 * Reported by Mike Crash <mike AT mikecrash.com>
		 */
		cx_ग_लिखो(MO_GP0_IO, 0x0000ef88);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000088);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000088); /* 702 out of reset */
		udelay(1000);
		अवरोध;

	हाल CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
	हाल CX88_BOARD_PROLINK_PV_8000GT:
		cx_ग_लिखो(MO_GP2_IO, 0xcf7);
		msleep(50);
		cx_ग_लिखो(MO_GP2_IO, 0xef5);
		msleep(50);
		cx_ग_लिखो(MO_GP2_IO, 0xcf7);
		usleep_range(10000, 20000);
		अवरोध;

	हाल CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD:
		/* Enable the xc5000 tuner */
		cx_set(MO_GP0_IO, 0x00001010);
		अवरोध;

	हाल CX88_BOARD_WINFAST_DTV2000H_J:
	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
		/* Init GPIO */
		cx_ग_लिखो(MO_GP0_IO, core->board.input[0].gpio0);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000080);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000080); /* 702 out of reset */
		udelay(1000);
		अवरोध;

	हाल CX88_BOARD_NOTONLYTV_LV3H:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	हाल CX88_BOARD_WINFAST_DTV1800H:
		cx88_xc3028_winfast1800h_callback(core, XC2028_TUNER_RESET, 0);
		अवरोध;

	हाल CX88_BOARD_WINFAST_DTV1800H_XC4000:
	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36:
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43:
		cx88_xc4000_winfast2000h_plus_callback(core,
						       XC4000_TUNER_RESET, 0);
		अवरोध;

	हाल CX88_BOARD_TWINHAN_VP1027_DVBS:
		cx_ग_लिखो(MO_GP0_IO, 0x00003230);
		cx_ग_लिखो(MO_GP0_IO, 0x00003210);
		usleep_range(10000, 20000);
		cx_ग_लिखो(MO_GP0_IO, 0x00001230);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Sets board-dependent xc3028 configuration
 */
व्योम cx88_setup_xc3028(काष्ठा cx88_core *core, काष्ठा xc2028_ctrl *ctl)
अणु
	स_रखो(ctl, 0, माप(*ctl));

	ctl->fname   = XC2028_DEFAULT_FIRMWARE;
	ctl->max_len = 64;

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_POWERCOLOR_REAL_ANGEL:
		/* Now works with firmware version 2.7 */
		अगर (core->i2c_algo.udelay < 16)
			core->i2c_algo.udelay = 16;
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
	हाल CX88_BOARD_WINFAST_DTV1800H:
		ctl->demod = XC3028_FE_ZARLINK456;
		अवरोध;
	हाल CX88_BOARD_KWORLD_ATSC_120:
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO:
		ctl->demod = XC3028_FE_OREN538;
		अवरोध;
	हाल CX88_BOARD_GENIATECH_X8000_MT:
		/*
		 * FIXME: For this board, the xc3028 never recovers after being
		 * घातered करोwn (the reset GPIO probably is not set properly).
		 * We करोn't have access to the hardware so we cannot determine
		 * which GPIO is used क्रम xc3028, so just disable घातer xc3028
		 * घातer management क्रम now
		 */
		ctl->disable_घातer_mgmt = 1;
		अवरोध;
	हाल CX88_BOARD_NOTONLYTV_LV3H:
		ctl->demod			= XC3028_FE_ZARLINK456;
		ctl->fname			= XC3028L_DEFAULT_FIRMWARE;
		ctl->पढ़ो_not_reliable	= 1;
		अवरोध;
	हाल CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	हाल CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
	हाल CX88_BOARD_PROLINK_PV_8000GT:
		/*
		 * Those boards uses non-MTS firmware
		 */
		अवरोध;
	हाल CX88_BOARD_PINNACLE_HYBRID_PCTV:
	हाल CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII:
		ctl->demod = XC3028_FE_ZARLINK456;
		ctl->mts = 1;
		अवरोध;
	शेष:
		ctl->demod = XC3028_FE_OREN538;
		ctl->mts = 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cx88_setup_xc3028);

अटल व्योम cx88_card_setup(काष्ठा cx88_core *core)
अणु
	अटल u8 eeprom[256];
	काष्ठा tuner_setup tun_setup;
	अचिन्हित पूर्णांक mode_mask = T_RADIO | T_ANALOG_TV;

	स_रखो(&tun_setup, 0, माप(tun_setup));

	अगर (!core->i2c_rc) अणु
		core->i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&core->i2c_client, eeprom, माप(eeprom));
	पूर्ण

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE:
	हाल CX88_BOARD_HAUPPAUGE_ROSLYN:
		अगर (!core->i2c_rc)
			hauppauge_eeprom(core, eeprom + 8);
		अवरोध;
	हाल CX88_BOARD_GDI:
		अगर (!core->i2c_rc)
			gdi_eeprom(core, eeprom);
		अवरोध;
	हाल CX88_BOARD_LEADTEK_PVR2000:
	हाल CX88_BOARD_WINFAST_DV2000:
	हाल CX88_BOARD_WINFAST2000XP_EXPERT:
		अगर (!core->i2c_rc)
			leadtek_eeprom(core, eeprom);
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1:
	हाल CX88_BOARD_HAUPPAUGE_NOVASE2_S1:
	हाल CX88_BOARD_HAUPPAUGE_DVB_T1:
	हाल CX88_BOARD_HAUPPAUGE_HVR1100:
	हाल CX88_BOARD_HAUPPAUGE_HVR1100LP:
	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000LITE:
	हाल CX88_BOARD_HAUPPAUGE_IRONLY:
		अगर (!core->i2c_rc)
			hauppauge_eeprom(core, eeprom);
		अवरोध;
	हाल CX88_BOARD_KWORLD_DVBS_100:
		cx_ग_लिखो(MO_GP0_IO, 0x000007f8);
		cx_ग_लिखो(MO_GP1_IO, 0x00000001);
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
		/* GPIO0:0 is hooked to demod reset */
		/* GPIO0:4 is hooked to xc3028 reset */
		cx_ग_लिखो(MO_GP0_IO, 0x00111100);
		usleep_range(10000, 20000);
		cx_ग_लिखो(MO_GP0_IO, 0x00111111);
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL:
		/* GPIO0:6 is hooked to FX2 reset pin */
		cx_set(MO_GP0_IO, 0x00004040);
		cx_clear(MO_GP0_IO, 0x00000040);
		msleep(1000);
		cx_set(MO_GP0_IO, 0x00004040);
		fallthrough;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T1:
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS:
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID:
		/* GPIO0:0 is hooked to mt352 reset pin */
		cx_set(MO_GP0_IO, 0x00000101);
		cx_clear(MO_GP0_IO, 0x00000001);
		usleep_range(10000, 20000);
		cx_set(MO_GP0_IO, 0x00000101);
		अगर (!core->i2c_rc &&
		    core->boardnr == CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID)
			dvico_fusionhdtv_hybrid_init(core);
		अवरोध;
	हाल CX88_BOARD_KWORLD_DVB_T:
	हाल CX88_BOARD_DNTV_LIVE_DVB_T:
		cx_set(MO_GP0_IO, 0x00000707);
		cx_set(MO_GP2_IO, 0x00000101);
		cx_clear(MO_GP2_IO, 0x00000001);
		usleep_range(10000, 20000);
		cx_clear(MO_GP0_IO, 0x00000007);
		cx_set(MO_GP2_IO, 0x00000101);
		अवरोध;
	हाल CX88_BOARD_DNTV_LIVE_DVB_T_PRO:
		cx_ग_लिखो(MO_GP0_IO, 0x00080808);
		अवरोध;
	हाल CX88_BOARD_ATI_HDTVWONDER:
		अगर (!core->i2c_rc) अणु
			/* enable tuner */
			पूर्णांक i;
			अटल स्थिर u8 buffer[][2] = अणु
				अणु0x10, 0x12पूर्ण,
				अणु0x13, 0x04पूर्ण,
				अणु0x16, 0x00पूर्ण,
				अणु0x14, 0x04पूर्ण,
				अणु0x17, 0x00पूर्ण
			पूर्ण;
			core->i2c_client.addr = 0x0a;

			क्रम (i = 0; i < ARRAY_SIZE(buffer); i++)
				अगर (i2c_master_send(&core->i2c_client,
						    buffer[i], 2) != 2)
					pr_warn("Unable to enable tuner(%i).\n",
						i);
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_MSI_TVANYWHERE_MASTER:
	अणु
		काष्ठा v4l2_priv_tun_config tea5767_cfg;
		काष्ठा tea5767_ctrl ctl;

		स_रखो(&ctl, 0, माप(ctl));

		ctl.high_cut  = 1;
		ctl.st_noise  = 1;
		ctl.deemph_75 = 1;
		ctl.xtal_freq = TEA5767_HIGH_LO_13MHz;

		tea5767_cfg.tuner = TUNER_TEA5767;
		tea5767_cfg.priv  = &ctl;

		call_all(core, tuner, s_config, &tea5767_cfg);
		अवरोध;
	पूर्ण
	हाल  CX88_BOARD_TEVII_S420:
	हाल  CX88_BOARD_TEVII_S460:
	हाल  CX88_BOARD_TEVII_S464:
	हाल  CX88_BOARD_OMICOM_SS4_PCI:
	हाल  CX88_BOARD_TBS_8910:
	हाल  CX88_BOARD_TBS_8920:
	हाल  CX88_BOARD_PROF_6200:
	हाल  CX88_BOARD_PROF_7300:
	हाल  CX88_BOARD_PROF_7301:
	हाल  CX88_BOARD_SATTRADE_ST4200:
		cx_ग_लिखो(MO_GP0_IO, 0x8000);
		msleep(100);
		cx_ग_लिखो(MO_SRST_IO, 0);
		usleep_range(10000, 20000);
		cx_ग_लिखो(MO_GP0_IO, 0x8080);
		msleep(100);
		cx_ग_लिखो(MO_SRST_IO, 1);
		msleep(100);
		अवरोध;
	पूर्ण /*end चयन() */

	/* Setup tuners */
	अगर (core->board.radio_type != UNSET) अणु
		tun_setup.mode_mask      = T_RADIO;
		tun_setup.type           = core->board.radio_type;
		tun_setup.addr           = core->board.radio_addr;
		tun_setup.tuner_callback = cx88_tuner_callback;
		call_all(core, tuner, s_type_addr, &tun_setup);
		mode_mask &= ~T_RADIO;
	पूर्ण

	अगर (core->board.tuner_type != UNSET) अणु
		tun_setup.mode_mask      = mode_mask;
		tun_setup.type           = core->board.tuner_type;
		tun_setup.addr           = core->board.tuner_addr;
		tun_setup.tuner_callback = cx88_tuner_callback;

		call_all(core, tuner, s_type_addr, &tun_setup);
	पूर्ण

	अगर (core->board.tda9887_conf) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv  = &core->board.tda9887_conf;

		call_all(core, tuner, s_config, &tda9887_cfg);
	पूर्ण

	अगर (core->board.tuner_type == TUNER_XC2028) अणु
		काष्ठा v4l2_priv_tun_config  xc2028_cfg;
		काष्ठा xc2028_ctrl           ctl;

		/* Fills device-dependent initialization parameters */
		cx88_setup_xc3028(core, &ctl);

		/* Sends parameters to xc2028/3028 tuner */
		स_रखो(&xc2028_cfg, 0, माप(xc2028_cfg));
		xc2028_cfg.tuner = TUNER_XC2028;
		xc2028_cfg.priv  = &ctl;
		dprपूर्णांकk(1, "Asking xc2028/3028 to load firmware %s\n",
			ctl.fname);
		call_all(core, tuner, s_config, &xc2028_cfg);
	पूर्ण
	call_all(core, tuner, standby);
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक cx88_pci_quirks(स्थिर अक्षर *name, काष्ठा pci_dev *pci)
अणु
	अचिन्हित पूर्णांक lat = UNSET;
	u8 ctrl = 0;
	u8 value;

	/* check pci quirks */
	अगर (pci_pci_problems & PCIPCI_TRITON) अणु
		pr_info("quirk: PCIPCI_TRITON -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	पूर्ण
	अगर (pci_pci_problems & PCIPCI_NATOMA) अणु
		pr_info("quirk: PCIPCI_NATOMA -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	पूर्ण
	अगर (pci_pci_problems & PCIPCI_VIAETBF) अणु
		pr_info("quirk: PCIPCI_VIAETBF -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	पूर्ण
	अगर (pci_pci_problems & PCIPCI_VSFX) अणु
		pr_info("quirk: PCIPCI_VSFX -- set VSFX\n");
		ctrl |= CX88X_EN_VSFX;
	पूर्ण
#अगर_घोषित PCIPCI_ALIMAGIK
	अगर (pci_pci_problems & PCIPCI_ALIMAGIK) अणु
		pr_info("quirk: PCIPCI_ALIMAGIK -- latency fixup\n");
		lat = 0x0A;
	पूर्ण
#पूर्ण_अगर

	/* check insmod options */
	अगर (latency != UNSET)
		lat = latency;

	/* apply stuff */
	अगर (ctrl) अणु
		pci_पढ़ो_config_byte(pci, CX88X_DEVCTRL, &value);
		value |= ctrl;
		pci_ग_लिखो_config_byte(pci, CX88X_DEVCTRL, value);
	पूर्ण
	अगर (lat != UNSET) अणु
		pr_info("setting pci latency timer to %d\n", latency);
		pci_ग_लिखो_config_byte(pci, PCI_LATENCY_TIMER, latency);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cx88_get_resources(स्थिर काष्ठा cx88_core *core, काष्ठा pci_dev *pci)
अणु
	अगर (request_mem_region(pci_resource_start(pci, 0),
			       pci_resource_len(pci, 0),
			       core->name))
		वापस 0;
	pr_err("func %d: Can't get MMIO memory @ 0x%llx, subsystem: %04x:%04x\n",
	       PCI_FUNC(pci->devfn),
	       (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci, 0),
	       pci->subप्रणाली_venकरोr, pci->subप्रणाली_device);
	वापस -EBUSY;
पूर्ण

/*
 * Allocate and initialize the cx88 core काष्ठा.  One should hold the
 * devlist mutex beक्रमe calling this.
 */
काष्ठा cx88_core *cx88_core_create(काष्ठा pci_dev *pci, पूर्णांक nr)
अणु
	काष्ठा cx88_core *core;
	पूर्णांक i;

	core = kzalloc(माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस शून्य;

	refcount_set(&core->refcount, 1);
	core->pci_bus  = pci->bus->number;
	core->pci_slot = PCI_SLOT(pci->devfn);
	core->pci_irqmask = PCI_INT_RISC_RD_BERRINT | PCI_INT_RISC_WR_BERRINT |
			    PCI_INT_BRDG_BERRINT | PCI_INT_SRC_DMA_BERRINT |
			    PCI_INT_DST_DMA_BERRINT | PCI_INT_IPB_DMA_BERRINT;
	mutex_init(&core->lock);

	core->nr = nr;
	प्र_लिखो(core->name, "cx88[%d]", core->nr);

	/*
	 * Note: Setting initial standard here would cause first call to
	 * cx88_set_tvnorm() to वापस without programming any रेजिस्टरs.  Leave
	 * it blank क्रम at this poपूर्णांक and it will get set later in
	 * cx8800_initdev()
	 */
	core->tvnorm  = 0;

	core->width   = 320;
	core->height  = 240;
	core->field   = V4L2_FIELD_INTERLACED;

	strscpy(core->v4l2_dev.name, core->name, माप(core->v4l2_dev.name));
	अगर (v4l2_device_रेजिस्टर(शून्य, &core->v4l2_dev)) अणु
		kमुक्त(core);
		वापस शून्य;
	पूर्ण

	अगर (v4l2_ctrl_handler_init(&core->video_hdl, 13)) अणु
		v4l2_device_unरेजिस्टर(&core->v4l2_dev);
		kमुक्त(core);
		वापस शून्य;
	पूर्ण

	अगर (v4l2_ctrl_handler_init(&core->audio_hdl, 13)) अणु
		v4l2_ctrl_handler_मुक्त(&core->video_hdl);
		v4l2_device_unरेजिस्टर(&core->v4l2_dev);
		kमुक्त(core);
		वापस शून्य;
	पूर्ण

	अगर (cx88_get_resources(core, pci) != 0) अणु
		v4l2_ctrl_handler_मुक्त(&core->video_hdl);
		v4l2_ctrl_handler_मुक्त(&core->audio_hdl);
		v4l2_device_unरेजिस्टर(&core->v4l2_dev);
		kमुक्त(core);
		वापस शून्य;
	पूर्ण

	/* PCI stuff */
	cx88_pci_quirks(core->name, pci);
	core->lmmio = ioremap(pci_resource_start(pci, 0),
			      pci_resource_len(pci, 0));
	core->bmmio = (u8 __iomem *)core->lmmio;

	अगर (!core->lmmio) अणु
		release_mem_region(pci_resource_start(pci, 0),
				   pci_resource_len(pci, 0));
		v4l2_ctrl_handler_मुक्त(&core->video_hdl);
		v4l2_ctrl_handler_मुक्त(&core->audio_hdl);
		v4l2_device_unरेजिस्टर(&core->v4l2_dev);
		kमुक्त(core);
		वापस शून्य;
	पूर्ण

	/* board config */
	core->boardnr = UNSET;
	अगर (card[core->nr] < ARRAY_SIZE(cx88_boards))
		core->boardnr = card[core->nr];
	क्रम (i = 0; core->boardnr == UNSET && i < ARRAY_SIZE(cx88_subids); i++)
		अगर (pci->subप्रणाली_venकरोr == cx88_subids[i].subvenकरोr &&
		    pci->subप्रणाली_device == cx88_subids[i].subdevice)
			core->boardnr = cx88_subids[i].card;
	अगर (core->boardnr == UNSET) अणु
		core->boardnr = CX88_BOARD_UNKNOWN;
		cx88_card_list(core, pci);
	पूर्ण

	core->board = cx88_boards[core->boardnr];

	अगर (!core->board.num_frontends && (core->board.mpeg & CX88_MPEG_DVB))
		core->board.num_frontends = 1;

	pr_info("subsystem: %04x:%04x, board: %s [card=%d,%s], frontend(s): %d\n",
		pci->subप्रणाली_venकरोr, pci->subप्रणाली_device, core->board.name,
		core->boardnr, card[core->nr] == core->boardnr ?
		"insmod option" : "autodetected",
		core->board.num_frontends);

	अगर (tuner[core->nr] != UNSET)
		core->board.tuner_type = tuner[core->nr];
	अगर (radio[core->nr] != UNSET)
		core->board.radio_type = radio[core->nr];

	dprपूर्णांकk(1, "TV tuner type %d, Radio tuner type %d\n",
		core->board.tuner_type, core->board.radio_type);

	/* init hardware */
	cx88_reset(core);
	cx88_card_setup_pre_i2c(core);
	cx88_i2c_init(core, pci);

	/* load tuner module, अगर needed */
	अगर (core->board.tuner_type != UNSET) अणु
		/*
		 * Ignore 0x6b and 0x6f on cx88 boards.
		 * FusionHDTV5 RT Gold has an ir receiver at 0x6b
		 * and an RTC at 0x6f which can get corrupted अगर probed.
		 */
		अटल स्थिर अचिन्हित लघु tv_addrs[] = अणु
			0x42, 0x43, 0x4a, 0x4b,		/* tda8290 */
			0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
			0x68, 0x69, 0x6a, 0x6c, 0x6d, 0x6e,
			I2C_CLIENT_END
		पूर्ण;
		पूर्णांक has_demod = (core->board.tda9887_conf & TDA9887_PRESENT);

		/*
		 * I करोn't trust the radio_type as is stored in the card
		 * definitions, so we just probe क्रम it.
		 * The radio_type is someबार missing, or set to UNSET but
		 * later code configures a tea5767.
		 */
		v4l2_i2c_new_subdev(&core->v4l2_dev, &core->i2c_adap,
				    "tuner", 0,
				    v4l2_i2c_tuner_addrs(ADDRS_RADIO));
		अगर (has_demod)
			v4l2_i2c_new_subdev(&core->v4l2_dev,
					    &core->i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		अगर (core->board.tuner_addr == ADDR_UNSET) अणु
			v4l2_i2c_new_subdev(&core->v4l2_dev,
					    &core->i2c_adap, "tuner",
				0, has_demod ? tv_addrs + 4 : tv_addrs);
		पूर्ण अन्यथा अणु
			v4l2_i2c_new_subdev(&core->v4l2_dev, &core->i2c_adap,
					    "tuner", core->board.tuner_addr,
					    शून्य);
		पूर्ण
	पूर्ण

	cx88_card_setup(core);
	अगर (!disable_ir) अणु
		cx88_i2c_init_ir(core);
		cx88_ir_init(core, pci);
	पूर्ण

	वापस core;
पूर्ण
