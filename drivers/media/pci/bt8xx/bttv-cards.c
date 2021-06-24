<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv-cards.c

    this file has configuration inक्रमmation - card-specअगरic stuff
    like the big tvcards array क्रम the most part

    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
			   & Marcus Metzler (mocm@thp.uni-koeln.de)
    (c) 1999-2001 Gerd Knorr <kraxel@goldbach.in-berlin.de>


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <net/checksum.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/पन.स>

#समावेश "bttvp.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/i2c/tvaudपन.स>
#समावेश "bttv-audio-hook.h"

/* fwd decl */
अटल व्योम boot_msp34xx(काष्ठा bttv *btv, पूर्णांक pin);
अटल व्योम hauppauge_eeprom(काष्ठा bttv *btv);
अटल व्योम avermedia_eeprom(काष्ठा bttv *btv);
अटल व्योम osprey_eeprom(काष्ठा bttv *btv, स्थिर u8 ee[256]);
अटल व्योम modtec_eeprom(काष्ठा bttv *btv);
अटल व्योम init_PXC200(काष्ठा bttv *btv);
अटल व्योम init_RTV24(काष्ठा bttv *btv);
अटल व्योम init_PCI8604PW(काष्ठा bttv *btv);

अटल व्योम rv605_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम eagle_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम xguard_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम ivc120_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम gvc1100_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल व्योम PXC200_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल व्योम picolo_tetra_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम picolo_tetra_init(काष्ठा bttv *btv);

अटल व्योम tibetCS16_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम tibetCS16_init(काष्ठा bttv *btv);

अटल व्योम kodicom4400r_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम kodicom4400r_init(काष्ठा bttv *btv);

अटल व्योम sigmaSLC_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम sigmaSQ_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल व्योम geovision_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल व्योम phytec_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल व्योम gv800s_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);
अटल व्योम gv800s_init(काष्ठा bttv *btv);

अटल व्योम td3116_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input);

अटल पूर्णांक terratec_active_radio_upgrade(काष्ठा bttv *btv);
अटल पूर्णांक tea575x_init(काष्ठा bttv *btv);
अटल व्योम identअगरy_by_eeprom(काष्ठा bttv *btv,
			       अचिन्हित अक्षर eeprom_data[256]);
अटल पूर्णांक pvr_boot(काष्ठा bttv *btv);

/* config variables */
अटल अचिन्हित पूर्णांक triton1;
अटल अचिन्हित पूर्णांक vsfx;
अटल अचिन्हित पूर्णांक latency = UNSET;
पूर्णांक no_overlay=-1;

अटल अचिन्हित पूर्णांक card[BTTV_MAX]   = अणु [ 0 ... (BTTV_MAX-1) ] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक pll[BTTV_MAX]    = अणु [ 0 ... (BTTV_MAX-1) ] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक tuner[BTTV_MAX]  = अणु [ 0 ... (BTTV_MAX-1) ] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक svhs[BTTV_MAX]   = अणु [ 0 ... (BTTV_MAX-1) ] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक remote[BTTV_MAX] = अणु [ 0 ... (BTTV_MAX-1) ] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक audiodev[BTTV_MAX];
अटल अचिन्हित पूर्णांक saa6588[BTTV_MAX];
अटल काष्ठा bttv  *master[BTTV_MAX] = अणु [ 0 ... (BTTV_MAX-1) ] = शून्य पूर्ण;
अटल अचिन्हित पूर्णांक स्वतःload = UNSET;
अटल अचिन्हित पूर्णांक gpiomask = UNSET;
अटल अचिन्हित पूर्णांक audioall = UNSET;
अटल अचिन्हित पूर्णांक audiomux[5] = अणु [ 0 ... 4 ] = UNSET पूर्ण;

/* insmod options */
module_param(triton1,    पूर्णांक, 0444);
module_param(vsfx,       पूर्णांक, 0444);
module_param(no_overlay, पूर्णांक, 0444);
module_param(latency,    पूर्णांक, 0444);
module_param(gpiomask,   पूर्णांक, 0444);
module_param(audioall,   पूर्णांक, 0444);
module_param(स्वतःload,   पूर्णांक, 0444);

module_param_array(card,     पूर्णांक, शून्य, 0444);
module_param_array(pll,      पूर्णांक, शून्य, 0444);
module_param_array(tuner,    पूर्णांक, शून्य, 0444);
module_param_array(svhs,     पूर्णांक, शून्य, 0444);
module_param_array(remote,   पूर्णांक, शून्य, 0444);
module_param_array(audiodev, पूर्णांक, शून्य, 0444);
module_param_array(audiomux, पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(triton1, "set ETBF pci config bit [enable bug compatibility for triton1 + others]");
MODULE_PARM_DESC(vsfx, "set VSFX pci config bit [yet another chipset flaw workaround]");
MODULE_PARM_DESC(latency,"pci latency timer");
MODULE_PARM_DESC(card,"specify TV/grabber card model, see CARDLIST file for a list");
MODULE_PARM_DESC(pll, "specify installed crystal (0=none, 28=28 MHz, 35=35 MHz, 14=14 MHz)");
MODULE_PARM_DESC(tuner,"specify installed tuner type");
MODULE_PARM_DESC(स्वतःload, "obsolete option, please do not use anymore");
MODULE_PARM_DESC(audiodev, "specify audio device:\n"
		"\t\t-1 = no audio\n"
		"\t\t 0 = autodetect (default)\n"
		"\t\t 1 = msp3400\n"
		"\t\t 2 = tda7432\n"
		"\t\t 3 = tvaudio");
MODULE_PARM_DESC(saa6588, "if 1, then load the saa6588 RDS module, default (0) is to use the card definition.");
MODULE_PARM_DESC(no_overlay, "allow override overlay default (0 disables, 1 enables) [some VIA/SIS chipsets are known to have problem with overlay]");


/* I2C addresses list */
#घोषणा I2C_ADDR_TDA7432	0x8a
#घोषणा I2C_ADDR_MSP3400	0x80
#घोषणा I2C_ADDR_MSP3400_ALT	0x88


/* ----------------------------------------------------------------------- */
/* list of card IDs क्रम bt878+ cards                                       */

अटल काष्ठा CARD अणु
	अचिन्हित id;
	पूर्णांक cardnr;
	अक्षर *name;
पूर्ण cards[] = अणु
	अणु 0x13eb0070, BTTV_BOARD_HAUPPAUGE878,  "Hauppauge WinTV" पूर्ण,
	अणु 0x39000070, BTTV_BOARD_HAUPPAUGE878,  "Hauppauge WinTV-D" पूर्ण,
	अणु 0x45000070, BTTV_BOARD_HAUPPAUGEPVR,  "Hauppauge WinTV/PVR" पूर्ण,
	अणु 0xff000070, BTTV_BOARD_OSPREY1x0,     "Osprey-100" पूर्ण,
	अणु 0xff010070, BTTV_BOARD_OSPREY2x0_SVID,"Osprey-200" पूर्ण,
	अणु 0xff020070, BTTV_BOARD_OSPREY500,     "Osprey-500" पूर्ण,
	अणु 0xff030070, BTTV_BOARD_OSPREY2000,    "Osprey-2000" पूर्ण,
	अणु 0xff040070, BTTV_BOARD_OSPREY540,     "Osprey-540" पूर्ण,
	अणु 0xff070070, BTTV_BOARD_OSPREY440,     "Osprey-440" पूर्ण,

	अणु 0x00011002, BTTV_BOARD_ATI_TVWONDER,  "ATI TV Wonder" पूर्ण,
	अणु 0x00031002, BTTV_BOARD_ATI_TVWONDERVE,"ATI TV Wonder/VE" पूर्ण,

	अणु 0x6606107d, BTTV_BOARD_WINFAST2000,   "Leadtek WinFast TV 2000" पूर्ण,
	अणु 0x6607107d, BTTV_BOARD_WINFASTVC100,  "Leadtek WinFast VC 100" पूर्ण,
	अणु 0x6609107d, BTTV_BOARD_WINFAST2000,   "Leadtek TV 2000 XP" पूर्ण,
	अणु 0x263610b4, BTTV_BOARD_STB2,          "STB TV PCI FM, Gateway P/N 6000704" पूर्ण,
	अणु 0x264510b4, BTTV_BOARD_STB2,          "STB TV PCI FM, Gateway P/N 6000704" पूर्ण,
	अणु 0x402010fc, BTTV_BOARD_GVBCTV3PCI,    "I-O Data Co. GV-BCTV3/PCI" पूर्ण,
	अणु 0x405010fc, BTTV_BOARD_GVBCTV4PCI,    "I-O Data Co. GV-BCTV4/PCI" पूर्ण,
	अणु 0x407010fc, BTTV_BOARD_GVBCTV5PCI,    "I-O Data Co. GV-BCTV5/PCI" पूर्ण,
	अणु 0xd01810fc, BTTV_BOARD_GVBCTV5PCI,    "I-O Data Co. GV-BCTV5/PCI" पूर्ण,

	अणु 0x001211bd, BTTV_BOARD_PINNACLE,      "Pinnacle PCTV" पूर्ण,
	/* some cards ship with byteswapped IDs ... */
	अणु 0x1200bd11, BTTV_BOARD_PINNACLE,      "Pinnacle PCTV [bswap]" पूर्ण,
	अणु 0xff00bd11, BTTV_BOARD_PINNACLE,      "Pinnacle PCTV [bswap]" पूर्ण,
	/* this seems to happen as well ... */
	अणु 0xff1211bd, BTTV_BOARD_PINNACLE,      "Pinnacle PCTV" पूर्ण,

	अणु 0x3000121a, BTTV_BOARD_VOODOOTV_200,  "3Dfx VoodooTV 200" पूर्ण,
	अणु 0x263710b4, BTTV_BOARD_VOODOOTV_FM,   "3Dfx VoodooTV FM" पूर्ण,
	अणु 0x3060121a, BTTV_BOARD_STB2,	  "3Dfx VoodooTV 100/ STB OEM" पूर्ण,

	अणु 0x3000144f, BTTV_BOARD_MAGICTVIEW063, "(Askey Magic/others) TView99 CPH06x" पूर्ण,
	अणु 0xa005144f, BTTV_BOARD_MAGICTVIEW063, "CPH06X TView99-Card" पूर्ण,
	अणु 0x3002144f, BTTV_BOARD_MAGICTVIEW061, "(Askey Magic/others) TView99 CPH05x" पूर्ण,
	अणु 0x3005144f, BTTV_BOARD_MAGICTVIEW061, "(Askey Magic/others) TView99 CPH061/06L (T1/LC)" पूर्ण,
	अणु 0x5000144f, BTTV_BOARD_MAGICTVIEW061, "Askey CPH050" पूर्ण,
	अणु 0x300014ff, BTTV_BOARD_MAGICTVIEW061, "TView 99 (CPH061)" पूर्ण,
	अणु 0x300214ff, BTTV_BOARD_PHOEBE_TVMAS,  "Phoebe TV Master (CPH060)" पूर्ण,

	अणु 0x00011461, BTTV_BOARD_AVPHONE98,     "AVerMedia TVPhone98" पूर्ण,
	अणु 0x00021461, BTTV_BOARD_AVERMEDIA98,   "AVermedia TVCapture 98" पूर्ण,
	अणु 0x00031461, BTTV_BOARD_AVPHONE98,     "AVerMedia TVPhone98" पूर्ण,
	अणु 0x00041461, BTTV_BOARD_AVERMEDIA98,   "AVerMedia TVCapture 98" पूर्ण,
	अणु 0x03001461, BTTV_BOARD_AVERMEDIA98,   "VDOMATE TV TUNER CARD" पूर्ण,

	अणु 0x1117153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue (Philips PAL B/G)" पूर्ण,
	अणु 0x1118153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue (Temic PAL B/G)" पूर्ण,
	अणु 0x1119153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue (Philips PAL I)" पूर्ण,
	अणु 0x111a153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue (Temic PAL I)" पूर्ण,

	अणु 0x1123153b, BTTV_BOARD_TERRATVRADIO,  "Terratec TV Radio+" पूर्ण,
	अणु 0x1127153b, BTTV_BOARD_TERRATV,       "Terratec TV+ (V1.05)"    पूर्ण,
	/* clashes with FlyVideo
	 *अणु 0x18521852, BTTV_BOARD_TERRATV,     "Terratec TV+ (V1.10)"    पूर्ण, */
	अणु 0x1134153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue (LR102)" पूर्ण,
	अणु 0x1135153b, BTTV_BOARD_TERRATVALUER,  "Terratec TValue Radio" पूर्ण, /* LR102 */
	अणु 0x5018153b, BTTV_BOARD_TERRATVALUE,   "Terratec TValue" पूर्ण,       /* ?? */
	अणु 0xff3b153b, BTTV_BOARD_TERRATVALUER,  "Terratec TValue Radio" पूर्ण, /* ?? */

	अणु 0x400015b0, BTTV_BOARD_ZOLTRIX_GENIE, "Zoltrix Genie TV" पूर्ण,
	अणु 0x400a15b0, BTTV_BOARD_ZOLTRIX_GENIE, "Zoltrix Genie TV" पूर्ण,
	अणु 0x400d15b0, BTTV_BOARD_ZOLTRIX_GENIE, "Zoltrix Genie TV / Radio" पूर्ण,
	अणु 0x401015b0, BTTV_BOARD_ZOLTRIX_GENIE, "Zoltrix Genie TV / Radio" पूर्ण,
	अणु 0x401615b0, BTTV_BOARD_ZOLTRIX_GENIE, "Zoltrix Genie TV / Radio" पूर्ण,

	अणु 0x1430aa00, BTTV_BOARD_PV143,         "Provideo PV143A" पूर्ण,
	अणु 0x1431aa00, BTTV_BOARD_PV143,         "Provideo PV143B" पूर्ण,
	अणु 0x1432aa00, BTTV_BOARD_PV143,         "Provideo PV143C" पूर्ण,
	अणु 0x1433aa00, BTTV_BOARD_PV143,         "Provideo PV143D" पूर्ण,
	अणु 0x1433aa03, BTTV_BOARD_PV143,         "Security Eyes" पूर्ण,

	अणु 0x1460aa00, BTTV_BOARD_PV150,         "Provideo PV150A-1" पूर्ण,
	अणु 0x1461aa01, BTTV_BOARD_PV150,         "Provideo PV150A-2" पूर्ण,
	अणु 0x1462aa02, BTTV_BOARD_PV150,         "Provideo PV150A-3" पूर्ण,
	अणु 0x1463aa03, BTTV_BOARD_PV150,         "Provideo PV150A-4" पूर्ण,

	अणु 0x1464aa04, BTTV_BOARD_PV150,         "Provideo PV150B-1" पूर्ण,
	अणु 0x1465aa05, BTTV_BOARD_PV150,         "Provideo PV150B-2" पूर्ण,
	अणु 0x1466aa06, BTTV_BOARD_PV150,         "Provideo PV150B-3" पूर्ण,
	अणु 0x1467aa07, BTTV_BOARD_PV150,         "Provideo PV150B-4" पूर्ण,

	अणु 0xa132ff00, BTTV_BOARD_IVC100,        "IVC-100"  पूर्ण,
	अणु 0xa1550000, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550001, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550002, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550003, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550100, BTTV_BOARD_IVC200,        "IVC-200G" पूर्ण,
	अणु 0xa1550101, BTTV_BOARD_IVC200,        "IVC-200G" पूर्ण,
	अणु 0xa1550102, BTTV_BOARD_IVC200,        "IVC-200G" पूर्ण,
	अणु 0xa1550103, BTTV_BOARD_IVC200,        "IVC-200G" पूर्ण,
	अणु 0xa1550800, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550801, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550802, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa1550803, BTTV_BOARD_IVC200,        "IVC-200"  पूर्ण,
	अणु 0xa182ff00, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff01, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff02, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff03, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff04, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff05, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff06, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff07, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff08, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff09, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0a, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0b, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0c, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0d, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0e, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xa182ff0f, BTTV_BOARD_IVC120,        "IVC-120G" पूर्ण,
	अणु 0xf0500000, BTTV_BOARD_IVCE8784,      "IVCE-8784" पूर्ण,
	अणु 0xf0500001, BTTV_BOARD_IVCE8784,      "IVCE-8784" पूर्ण,
	अणु 0xf0500002, BTTV_BOARD_IVCE8784,      "IVCE-8784" पूर्ण,
	अणु 0xf0500003, BTTV_BOARD_IVCE8784,      "IVCE-8784" पूर्ण,

	अणु 0x41424344, BTTV_BOARD_GRANDTEC,      "GrandTec Multi Capture" पूर्ण,
	अणु 0x01020304, BTTV_BOARD_XGUARD,        "Grandtec Grand X-Guard" पूर्ण,

	अणु 0x18501851, BTTV_BOARD_CHRONOS_VS2,   "FlyVideo 98 (LR50)/ Chronos Video Shuttle II" पूर्ण,
	अणु 0xa0501851, BTTV_BOARD_CHRONOS_VS2,   "FlyVideo 98 (LR50)/ Chronos Video Shuttle II" पूर्ण,
	अणु 0x18511851, BTTV_BOARD_FLYVIDEO98EZ,  "FlyVideo 98EZ (LR51)/ CyberMail AV" पूर्ण,
	अणु 0x18521852, BTTV_BOARD_TYPHOON_TVIEW, "FlyVideo 98FM (LR50)/ Typhoon TView TV/FM Tuner" पूर्ण,
	अणु 0x41a0a051, BTTV_BOARD_FLYVIDEO_98FM, "Lifeview FlyVideo 98 LR50 Rev Q" पूर्ण,
	अणु 0x18501f7f, BTTV_BOARD_FLYVIDEO_98,   "Lifeview Flyvideo 98" पूर्ण,

	अणु 0x010115cb, BTTV_BOARD_GMV1,          "AG GMV1" पूर्ण,
	अणु 0x010114c7, BTTV_BOARD_MODTEC_205,    "Modular Technology MM201/MM202/MM205/MM210/MM215 PCTV" पूर्ण,

	अणु 0x10b42636, BTTV_BOARD_HAUPPAUGE878,  "STB ???" पूर्ण,
	अणु 0x217d6606, BTTV_BOARD_WINFAST2000,   "Leadtek WinFast TV 2000" पूर्ण,
	अणु 0xfff6f6ff, BTTV_BOARD_WINFAST2000,   "Leadtek WinFast TV 2000" पूर्ण,
	अणु 0x03116000, BTTV_BOARD_SENSORAY311_611, "Sensoray 311" पूर्ण,
	अणु 0x06116000, BTTV_BOARD_SENSORAY311_611, "Sensoray 611" पूर्ण,
	अणु 0x00790e11, BTTV_BOARD_WINDVR,        "Canopus WinDVR PCI" पूर्ण,
	अणु 0xa0fca1a0, BTTV_BOARD_ZOLTRIX,       "Face to Face Tvmax" पूर्ण,
	अणु 0x82b2aa6a, BTTV_BOARD_SIMUS_GVC1100, "SIMUS GVC1100" पूर्ण,
	अणु 0x146caa0c, BTTV_BOARD_PV951,         "ituner spectra8" पूर्ण,
	अणु 0x200a1295, BTTV_BOARD_PXC200,        "ImageNation PXC200A" पूर्ण,

	अणु 0x40111554, BTTV_BOARD_PV_BT878P_9B,  "Prolink Pixelview PV-BT" पूर्ण,
	अणु 0x17de0a01, BTTV_BOARD_KWORLD,        "Mecer TV/FM/Video Tuner" पूर्ण,

	अणु 0x01051805, BTTV_BOARD_PICOLO_TETRA_CHIP, "Picolo Tetra Chip #1" पूर्ण,
	अणु 0x01061805, BTTV_BOARD_PICOLO_TETRA_CHIP, "Picolo Tetra Chip #2" पूर्ण,
	अणु 0x01071805, BTTV_BOARD_PICOLO_TETRA_CHIP, "Picolo Tetra Chip #3" पूर्ण,
	अणु 0x01081805, BTTV_BOARD_PICOLO_TETRA_CHIP, "Picolo Tetra Chip #4" पूर्ण,

	अणु 0x15409511, BTTV_BOARD_ACORP_Y878F, "Acorp Y878F" पूर्ण,

	अणु 0x53534149, BTTV_BOARD_SSAI_SECURITY, "SSAI Security Video Interface" पूर्ण,
	अणु 0x5353414a, BTTV_BOARD_SSAI_ULTRASOUND, "SSAI Ultrasound Video Interface" पूर्ण,

	/* likely broken, venकरोr id करोesn't match the other magic views ...
	 * अणु 0xa0fca04f, BTTV_BOARD_MAGICTVIEW063, "Guillemot Maxi TV Video 3" पूर्ण, */

	/* Duplicate PCI ID, reconfigure क्रम this board during the eeprom पढ़ो.
	* अणु 0x13eb0070, BTTV_BOARD_HAUPPAUGE_IMPACTVCB,  "Hauppauge ImpactVCB" पूर्ण, */

	अणु 0x109e036e, BTTV_BOARD_CONCEPTRONIC_CTVFMI2,	"Conceptronic CTVFMi v2"पूर्ण,

	/* DVB cards (using pci function .1 क्रम mpeg data xfer) */
	अणु 0x001c11bd, BTTV_BOARD_PINNACLESAT,   "Pinnacle PCTV Sat" पूर्ण,
	अणु 0x01010071, BTTV_BOARD_NEBULA_DIGITV, "Nebula Electronics DigiTV" पूर्ण,
	अणु 0x20007063, BTTV_BOARD_PC_HDTV,       "pcHDTV HD-2000 TV"पूर्ण,
	अणु 0x002611bd, BTTV_BOARD_TWINHAN_DST,   "Pinnacle PCTV SAT CI" पूर्ण,
	अणु 0x00011822, BTTV_BOARD_TWINHAN_DST,   "Twinhan VisionPlus DVB" पूर्ण,
	अणु 0xfc00270f, BTTV_BOARD_TWINHAN_DST,   "ChainTech digitop DST-1000 DVB-S" पूर्ण,
	अणु 0x07711461, BTTV_BOARD_AVDVBT_771,    "AVermedia AverTV DVB-T 771" पूर्ण,
	अणु 0x07611461, BTTV_BOARD_AVDVBT_761,    "AverMedia AverTV DVB-T 761" पूर्ण,
	अणु 0xdb1018ac, BTTV_BOARD_DVICO_DVBT_LITE,    "DViCO FusionHDTV DVB-T Lite" पूर्ण,
	अणु 0xdb1118ac, BTTV_BOARD_DVICO_DVBT_LITE,    "Ultraview DVB-T Lite" पूर्ण,
	अणु 0xd50018ac, BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE,    "DViCO FusionHDTV 5 Lite" पूर्ण,
	अणु 0x00261822, BTTV_BOARD_TWINHAN_DST,	"DNTV Live! Mini "पूर्ण,
	अणु 0xd200dbc0, BTTV_BOARD_DVICO_FUSIONHDTV_2,	"DViCO FusionHDTV 2" पूर्ण,
	अणु 0x763c008a, BTTV_BOARD_GEOVISION_GV600,	"GeoVision GV-600" पूर्ण,
	अणु 0x18011000, BTTV_BOARD_ENLTV_FM_2,	"Encore ENL TV-FM-2" पूर्ण,
	अणु 0x763d800a, BTTV_BOARD_GEOVISION_GV800S, "GeoVision GV-800(S) (master)" पूर्ण,
	अणु 0x763d800b, BTTV_BOARD_GEOVISION_GV800S_SL,	"GeoVision GV-800(S) (slave)" पूर्ण,
	अणु 0x763d800c, BTTV_BOARD_GEOVISION_GV800S_SL,	"GeoVision GV-800(S) (slave)" पूर्ण,
	अणु 0x763d800d, BTTV_BOARD_GEOVISION_GV800S_SL,	"GeoVision GV-800(S) (slave)" पूर्ण,

	अणु 0x15401830, BTTV_BOARD_PV183,         "Provideo PV183-1" पूर्ण,
	अणु 0x15401831, BTTV_BOARD_PV183,         "Provideo PV183-2" पूर्ण,
	अणु 0x15401832, BTTV_BOARD_PV183,         "Provideo PV183-3" पूर्ण,
	अणु 0x15401833, BTTV_BOARD_PV183,         "Provideo PV183-4" पूर्ण,
	अणु 0x15401834, BTTV_BOARD_PV183,         "Provideo PV183-5" पूर्ण,
	अणु 0x15401835, BTTV_BOARD_PV183,         "Provideo PV183-6" पूर्ण,
	अणु 0x15401836, BTTV_BOARD_PV183,         "Provideo PV183-7" पूर्ण,
	अणु 0x15401837, BTTV_BOARD_PV183,         "Provideo PV183-8" पूर्ण,
	अणु 0x3116f200, BTTV_BOARD_TVT_TD3116,	"Tongwei Video Technology TD-3116" पूर्ण,
	अणु 0x02280279, BTTV_BOARD_APOSONIC_WDVR, "Aposonic W-DVR" पूर्ण,
	अणु 0, -1, शून्य पूर्ण
पूर्ण;

/* ----------------------------------------------------------------------- */
/* array with description क्रम bt848 / bt878 tv/grabber cards               */

काष्ठा tvcard bttv_tvcards[] = अणु
	/* ---- card 0x00 ---------------------------------- */
	[BTTV_BOARD_UNKNOWN] = अणु
		.name		= " *** UNKNOWN/GENERIC *** ",
		.video_inमाला_दो	= 4,
		.svhs		= 2,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MIRO] = अणु
		.name		= "MIRO PCTV",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 2, 0, 0, 0 पूर्ण,
		.gpiomute	= 10,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_HAUPPAUGE] = अणु
		.name		= "Hauppauge (bt848)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_STB] = अणु
		.name		= "STB, Gateway P/N 6000699 (bt848)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 4, 0, 2, 3 पूर्ण,
		.gpiomute	= 1,
		.no_msp34xx	= 1,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
		.has_radio      = 1,
	पूर्ण,

	/* ---- card 0x04 ---------------------------------- */
	[BTTV_BOARD_INTEL] = अणु
		.name		= "Intel Create and Share PCI/ Smart Video Recorder III",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0 पूर्ण,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_DIAMOND] = अणु
		.name		= "Diamond DTV2000",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 3,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.gpiomux	= अणु 0, 1, 0, 1 पूर्ण,
		.gpiomute	= 3,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_AVERMEDIA] = अणु
		.name		= "AVerMedia TVPhone",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomask	= 0x0f,
		.gpiomux	= अणु 0x0c, 0x04, 0x08, 0x04 पूर्ण,
		/*                0x04 क्रम some cards ?? */
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= avermedia_tvphone_audio,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_MATRIX_VISION] = अणु
		.name		= "MATRIX-Vision MV-Delta",
		.video_inमाला_दो	= 5,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 0, 0),
		.gpiomux	= अणु 0 पूर्ण,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x08 ---------------------------------- */
	[BTTV_BOARD_FLYVIDEO] = अणु
		.name		= "Lifeview FlyVideo II (Bt848) LR26 / MAXI TV Video PCI2 LR26",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xc00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0xc00, 0x800, 0x400 पूर्ण,
		.gpiomute	= 0xc00,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TURBOTV] = अणु
		.name		= "IMS/IXmicro TurboTV",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 3,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 1, 1, 2, 3 पूर्ण,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TEMIC_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_HAUPPAUGE878] = अणु
		.name		= "Hauppauge (bt878)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x0f, /* old: 7 */
		.muxsel		= MUXSEL(2, 0, 1, 1),
		.gpiomux	= अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MIROPRO] = अणु
		.name		= "MIRO PCTV pro",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x3014f,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x20001,0x10001, 0, 0 पूर्ण,
		.gpiomute	= 10,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x0c ---------------------------------- */
	[BTTV_BOARD_ADSTECH_TV] = अणु
		.name		= "ADS Technologies Channel Surfer TV (bt848)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 13, 14, 11, 7 पूर्ण,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_AVERMEDIA98] = अणु
		.name		= "AVerMedia TVCapture 98",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 4, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 13, 14, 11, 7 पूर्ण,
		.msp34xx_alt    = 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= avermedia_tv_stereo_audio,
		.no_gpioirq     = 1,
	पूर्ण,
	[BTTV_BOARD_VHX] = अणु
		.name		= "Aimslab Video Highway Xtreme (VHX)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 2, 1, 3 पूर्ण, /* old: अणु0, 1, 2, 3, 4पूर्ण */
		.gpiomute	= 4,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ZOLTRIX] = अणु
		.name		= "Zoltrix TV-Max",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0, 1, 0 पूर्ण,
		.gpiomute	= 10,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x10 ---------------------------------- */
	[BTTV_BOARD_PIXVIEWPLAYTV] = अणु
		.name		= "Prolink Pixelview PlayTV (bt878)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x01fe00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		/* 2003-10-20 by "Anton A. Arapov" <arapov@mail.ru> */
		.gpiomux        = अणु 0x001e00, 0, 0x018000, 0x014000 पूर्ण,
		.gpiomute	= 0x002000,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr     = ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_WINVIEW_601] = अणु
		.name		= "Leadtek WinView 601",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x8300f8,
		.muxsel		= MUXSEL(2, 3, 1, 1, 0),
		.gpiomux	= अणु 0x4fa007,0xcfa007,0xcfa007,0xcfa007 पूर्ण,
		.gpiomute	= 0xcfa007,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.volume_gpio	= winview_volume,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_AVEC_INTERCAP] = अणु
		.name		= "AVEC Intercapture",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 2, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 1, 0, 0, 0 पूर्ण,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_LIFE_FLYKIT] = अणु
		.name		= "Lifeview FlyVideo II EZ /FlyKit LR38 Bt848 (capture only)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x8dff00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0 पूर्ण,
		.no_msp34xx	= 1,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x14 ---------------------------------- */
	[BTTV_BOARD_CEI_RAFFLES] = अणु
		.name		= "CEI Raffles Card",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 3, */
		.svhs		= 2,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_CONFERENCETV] = अणु
		.name		= "Lifeview FlyVideo 98/ Lucky Star Image World ConferenceTV LR50",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 2,  tuner, line in */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0x800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_PHOEBE_TVMAS] = अणु
		.name		= "Askey CPH050/ Phoebe Tv Master + FM",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xc00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 1, 0x800, 0x400 पूर्ण,
		.gpiomute	= 0xc00,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MODTEC_205] = अणु
		.name		= "Modular Technology MM201/MM202/MM205/MM210/MM215 PCTV, bt878",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= NO_SVHS,
		.has_dig_in	= 1,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 3, 0), /* input 2 is digital */
		/* .digital_mode= DIGITAL_MODE_CAMERA, */
		.gpiomux	= अणु 0, 0, 0, 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ALPS_TSBB5_PAL_I,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x18 ---------------------------------- */
	[BTTV_BOARD_MAGICTVIEW061] = अणु
		.name		= "Askey CPH05X/06X (bt878) [many vendors]",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xe00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु0x400, 0x400, 0x400, 0x400 पूर्ण,
		.gpiomute	= 0xc00,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
		.has_radio	= 1,  /* not every card has radio */
	पूर्ण,
	[BTTV_BOARD_VOBIS_BOOSTAR] = अणु
		.name           = "Terratec TerraTV+ Version 1.0 (Bt848)/ Terra TValue Version 1.0/ Vobis TV-Boostar",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask       = 0x1f0fff,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0x20000, 0x30000, 0x10000, 0 पूर्ण,
		.gpiomute	= 0x40000,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= terratv_audio,
	पूर्ण,
	[BTTV_BOARD_HAUPPAUG_WCAM] = अणु
		.name		= "Hauppauge WinCam newer (bt878)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 0, 1, 1),
		.gpiomux	= अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MAXI] = अणु
		.name		= "Lifeview FlyVideo 98/ MAXI TV Video PCI2 LR50",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 2, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0x800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll            = PLL_28,
		.tuner_type	= TUNER_PHILIPS_SECAM,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x1c ---------------------------------- */
	[BTTV_BOARD_TERRATV] = अणु
		.name           = "Terratec TerraTV+ Version 1.1 (bt878)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x1f0fff,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x20000, 0x30000, 0x10000, 0x00000 पूर्ण,
		.gpiomute	= 0x40000,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= terratv_audio,
		/* GPIO wiring:
		External 20 pin connector (क्रम Active Radio Upgrade board)
		gpio00: i2c-sda
		gpio01: i2c-scl
		gpio02: om5610-data
		gpio03: om5610-clk
		gpio04: om5610-wre
		gpio05: om5610-stereo
		gpio06: rds6588-davn
		gpio07: Pin 7 n.c.
		gpio08: nIOW
		gpio09+10: nIOR, nSEL ?? (bt878)
			gpio09: nIOR (bt848)
			gpio10: nSEL (bt848)
		Sound Routing:
		gpio16: u2-A0 (1st 4052bt)
		gpio17: u2-A1
		gpio18: u2-nEN
		gpio19: u4-A0 (2nd 4052)
		gpio20: u4-A1
			u4-nEN - GND
		Btspy:
			00000 : Cdrom (पूर्णांकernal audio input)
			10000 : ext. Video audio input
			20000 : TV Mono
			a0000 : TV Mono/2
		1a0000 : TV Stereo
			30000 : Radio
			40000 : Mute
	*/

	पूर्ण,
	[BTTV_BOARD_PXC200] = अणु
		/* Jannik Fritsch <jannik@techfak.uni-bielefeld.de> */
		.name		= "Imagenation PXC200",
		.video_inमाला_दो	= 5,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 1, /* was: 4 */
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 0, 0),
		.gpiomux	= अणु 0 पूर्ण,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.muxsel_hook    = PXC200_muxsel,

	पूर्ण,
	[BTTV_BOARD_FLYVIDEO_98] = अणु
		.name		= "Lifeview FlyVideo 98 LR50",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x1800,  /* 0x8dfe00 */
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0x0800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll            = PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_IPROTV] = अणु
		.name		= "Formac iProTV, Formac ProTV I (bt848)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.gpiomask	= 1,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 1, 0, 0, 0 पूर्ण,
		.pll            = PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x20 ---------------------------------- */
	[BTTV_BOARD_INTEL_C_S_PCI] = अणु
		.name		= "Intel Create and Share PCI/ Smart Video Recorder III",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0 पूर्ण,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TERRATVALUE] = अणु
		.name           = "Terratec TerraTValue Version Bt878",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xffff00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x500, 0, 0x300, 0x900 पूर्ण,
		.gpiomute	= 0x900,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_WINFAST2000] = अणु
		.name		= "Leadtek WinFast 2000/ WinFast 2000 XP",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		/* TV, CVid, SVid, CVid over SVid connector */
		.muxsel		= MUXSEL(2, 3, 1, 1, 0),
		/* Alexander Varakin <avarakin@hoपंचांगail.com> [stereo version] */
		.gpiomask	= 0xb33000,
		.gpiomux	= अणु 0x122000,0x1000,0x0000,0x620000 पूर्ण,
		.gpiomute	= 0x800000,
		/* Audio Routing क्रम "WinFast 2000 XP" (no tv stereo !)
			gpio23 -- hef4052:nEnable (0x800000)
			gpio12 -- hef4052:A1
			gpio13 -- hef4052:A0
		0x0000: बाह्यal audio
		0x1000: FM
		0x2000: TV
		0x3000: n.c.
		Note: There exists another variant "Winfast 2000" with tv stereo !?
		Note: eeprom only contains FF and pci subप्रणाली id 107d:6606
		*/
		.pll		= PLL_28,
		.has_radio	= 1,
		.tuner_type	= TUNER_PHILIPS_PAL, /* शेष क्रम now, gpio पढ़ोs BFFF06 क्रम Pal bg+dk */
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= winfast2000_audio,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_CHRONOS_VS2] = अणु
		.name		= "Lifeview FlyVideo 98 LR50 / Chronos Video Shuttle II",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0x800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x24 ---------------------------------- */
	[BTTV_BOARD_TYPHOON_TVIEW] = अणु
		.name		= "Lifeview FlyVideo 98FM LR50 / Typhoon TView TV/FM Tuner",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0x800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_PXELVWPLTVPRO] = अणु
		.name		= "Prolink PixelView PlayTV pro",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xff,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x21, 0x20, 0x24, 0x2c पूर्ण,
		.gpiomute	= 0x29,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MAGICTVIEW063] = अणु
		.name		= "Askey CPH06X TView99",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x551e00,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.gpiomux	= अणु 0x551400, 0x551200, 0, 0 पूर्ण,
		.gpiomute	= 0x551c00,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_PINNACLE] = अणु
		.name		= "Pinnacle PCTV Studio/Rave",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x03000F,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 2, 0xd0001, 0, 0 पूर्ण,
		.gpiomute	= 1,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x28 ---------------------------------- */
	[BTTV_BOARD_STB2] = अणु
		.name		= "STB TV PCI FM, Gateway P/N 6000704 (bt878), 3Dfx VoodooTV 100",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 4, 0, 2, 3 पूर्ण,
		.gpiomute	= 1,
		.no_msp34xx	= 1,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
		.has_radio      = 1,
	पूर्ण,
	[BTTV_BOARD_AVPHONE98] = अणु
		.name		= "AVerMedia TVPhone 98",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 4, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 13, 4, 11, 7 पूर्ण,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.has_radio	= 1,
		.audio_mode_gpio= avermedia_tvphone_audio,
	पूर्ण,
	[BTTV_BOARD_PV951] = अणु
		.name		= "ProVideo PV951", /* pic16c54 */
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0, 0, 0पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ONAIR_TV] = अणु
		.name		= "Little OnAir TV",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xe00b,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0xff9ff6, 0xff9ff6, 0xff1ff7, 0 पूर्ण,
		.gpiomute	= 0xff3ffc,
		.no_msp34xx	= 1,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x2c ---------------------------------- */
	[BTTV_BOARD_SIGMA_TVII_FM] = अणु
		.name		= "Sigma TVII-FM",
		.video_inमाला_दो	= 2,
		/* .audio_inमाला_दो= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 3,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 1, 1, 0, 2 पूर्ण,
		.gpiomute	= 3,
		.no_msp34xx	= 1,
		.pll		= PLL_NONE,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MATRIX_VISION2] = अणु
		.name		= "MATRIX-Vision MV-Delta 2",
		.video_inमाला_दो	= 5,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.gpiomask	= 0,
		.muxsel		= MUXSEL(2, 3, 1, 0, 0),
		.gpiomux	= अणु 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ZOLTRIX_GENIE] = अणु
		.name		= "Zoltrix Genie TV/FM",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xbcf03f,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0xbc803f, 0xbc903f, 0xbcb03f, 0 पूर्ण,
		.gpiomute	= 0xbcb03f,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TEMIC_4039FR5_NTSC,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TERRATVRADIO] = अणु
		.name		= "Terratec TV/Radio+",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x70000,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x20000, 0x30000, 0x10000, 0 पूर्ण,
		.gpiomute	= 0x40000,
		.no_msp34xx	= 1,
		.pll		= PLL_35,
		.tuner_type	= TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
		.has_radio	= 1,
	पूर्ण,

	/* ---- card 0x30 ---------------------------------- */
	[BTTV_BOARD_DYNALINK] = अणु
		.name		= "Askey CPH03x/ Dynalink Magic TView",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु2,0,0,0 पूर्ण,
		.gpiomute	= 1,
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_GVBCTV3PCI] = अणु
		.name		= "IODATA GV-BCTV3/PCI",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x010f00,
		.muxsel		= MUXSEL(2, 3, 0, 0),
		.gpiomux	= अणु0x10000, 0, 0x10000, 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_ALPS_TSHC6_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= gvbctv3pci_audio,
	पूर्ण,
	[BTTV_BOARD_PXELVWPLTVPAK] = अणु
		.name		= "Prolink PV-BT878P+4E / PixelView PlayTV PAK / Lenco MXTV-9578 CP",
		.video_inमाला_दो	= 5,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.has_dig_in	= 1,
		.gpiomask	= 0xAA0000,
		.muxsel		= MUXSEL(2, 3, 1, 1, 0), /* in 4 is digital */
		/* .digital_mode= DIGITAL_MODE_CAMERA, */
		.gpiomux	= अणु 0x20000, 0, 0x80000, 0x80000 पूर्ण,
		.gpiomute	= 0xa8000,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
		.has_remote	= 1,
		/* GPIO wiring: (dअगरferent from Rev.4C !)
			GPIO17: U4.A0 (first hef4052bt)
			GPIO19: U4.A1
			GPIO20: U5.A1 (second hef4052bt)
			GPIO21: U4.nEN
			GPIO22: BT832 Reset Line
			GPIO23: A5,A0, U5,nEN
		Note: At i2c=0x8a is a Bt832 chip, which changes to 0x88 after being reset via GPIO22
		*/
	पूर्ण,
	[BTTV_BOARD_EAGLE] = अणु
		.name           = "Eagle Wireless Capricorn2 (bt878A)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 7,
		.muxsel         = MUXSEL(2, 0, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.pll            = PLL_28,
		.tuner_type     = UNSET /* TUNER_ALPS_TMDH2_NTSC */,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x34 ---------------------------------- */
	[BTTV_BOARD_PINNACLEPRO] = अणु
		/* David Hथअrdeman <david@2gen.com> */
		.name           = "Pinnacle PCTV Studio Pro",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 3,
		.gpiomask       = 0x03000F,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 1, 0xd0001, 0, 0 पूर्ण,
		.gpiomute	= 10,
				/* sound path (5 sources):
				MUX1 (mask 0x03), Enable Pin 0x08 (0=enable, 1=disable)
					0= ext. Audio IN
					1= from MUX2
					2= Mono TV sound from Tuner
					3= not connected
				MUX2 (mask 0x30000):
					0,2,3= from MSP34xx
					1= FM stereo Radio from Tuner */
		.pll            = PLL_28,
		.tuner_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TVIEW_RDS_FM] = अणु
		/* Claas Langbehn <claas@bigfoot.com>,
		Sven Grothklags <sven@upb.de> */
		.name		= "Typhoon TView RDS + FM Stereo / KNC1 TV Station RDS",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1c,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0, 0, 0x10, 8 पूर्ण,
		.gpiomute	= 4,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_LIFETEC_9415] = अणु
		/* Tim Rथघstermundt <rosterm@uni-muenster.de>
		in de.comp.os.unix.linux.hardware:
			options bttv card=0 pll=1 radio=1 gpiomask=0x18e0
			gpiomux =0x44c71f,0x44d71f,0,0x44d71f,0x44dfff
			options tuner type=5 */
		.name		= "Lifeview FlyVideo 2000 /FlyVideo A2/ Lifetec LT 9415 TV [LR90]",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x18e0,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x0000,0x0800,0x1000,0x1000 पूर्ण,
		.gpiomute	= 0x18e0,
			/* For cards with tda9820/tda9821:
				0x0000: Tuner normal stereo
				0x0080: Tuner A2 SAP (second audio program = Zweikanalton)
				0x0880: Tuner A2 stereo */
		.pll		= PLL_28,
		.tuner_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_BESTBUY_EASYTV] = अणु
		/* Miguel Angel Alvarez <maacruz@navegalia.com>
		old Easy TV BT848 version (model CPH031) */
		.name           = "Askey CPH031/ BESTBUY Easy TV",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0xF,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 2, 0, 0, 0 पूर्ण,
		.gpiomute	= 10,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TEMIC_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x38 ---------------------------------- */
	[BTTV_BOARD_FLYVIDEO_98FM] = अणु
		/* Gorकरोn Heyकरोn <gjheyकरोn@bigfoot.com ('98) */
		.name           = "Lifeview FlyVideo 98FM LR50",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 3, */
		.svhs           = 2,
		.gpiomask       = 0x1800,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 0x800, 0x1000, 0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
		/* This is the ultimate cheapo capture card
		* just a BT848A on a small PCB!
		* Steve Hosgood <steve@equiinet.com> */
	[BTTV_BOARD_GRANDTEC] = अणु
		.name           = "GrandTec 'Grand Video Capture' (Bt848)",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 1,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(3, 1),
		.gpiomux        = अणु 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_35,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ASKEY_CPH060] = अणु
		/* Daniel Herrington <daniel.herrington@home.com> */
		.name           = "Askey CPH060/ Phoebe TV Master Only (No FM)",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0xe00,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0x400, 0x400, 0x400, 0x400 पूर्ण,
		.gpiomute	= 0x800,
		.pll            = PLL_28,
		.tuner_type     = TUNER_TEMIC_4036FY5_NTSC,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ASKEY_CPH03X] = अणु
		/* Matti Mottus <mottus@physic.ut.ee> */
		.name		= "Askey CPH03x TV Capturer",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask       = 0x03000F,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 2, 0, 0, 0 पूर्ण,
		.gpiomute	= 1,
		.pll            = PLL_28,
		.tuner_type	= TUNER_TEMIC_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_remote	= 1,
	पूर्ण,

	/* ---- card 0x3c ---------------------------------- */
	[BTTV_BOARD_MM100PCTV] = अणु
		/* Philip Blundell <philb@gnu.org> */
		.name           = "Modular Technology MM100PCTV",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 2, */
		.svhs		= NO_SVHS,
		.gpiomask       = 11,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 2, 0, 0, 1 पूर्ण,
		.gpiomute	= 8,
		.pll            = PLL_35,
		.tuner_type     = TUNER_TEMIC_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_GMV1] = अणु
		/* Adrian Cox <adrian@humboldt.co.uk */
		.name		= "AG Electronics GMV1",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs		= 1,
		.gpiomask       = 0xF,
		.muxsel		= MUXSEL(2, 2),
		.gpiomux        = अणु पूर्ण,
		.no_msp34xx     = 1,
		.pll		= PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_BESTBUY_EASYTV2] = अणु
		/* Miguel Angel Alvarez <maacruz@navegalia.com>
		new Easy TV BT878 version (model CPH061)
		special thanks to Inक्रमmatica Mieres क्रम providing the card */
		.name           = "Askey CPH061/ BESTBUY Easy TV (bt878)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 2, */
		.svhs           = 2,
		.gpiomask       = 0xFF,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 1, 0, 4, 4 पूर्ण,
		.gpiomute	= 9,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_ATI_TVWONDER] = अणु
		/* Lukas Gebauer <geby@volny.cz> */
		.name		= "ATI TV-Wonder",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xf03f,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.gpiomux	= अणु 0xbffe, 0, 0xbfff, 0 पूर्ण,
		.gpiomute	= 0xbffe,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TEMIC_4006FN5_MULTI_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x40 ---------------------------------- */
	[BTTV_BOARD_ATI_TVWONDERVE] = अणु
		/* Lukas Gebauer <geby@volny.cz> */
		.name		= "ATI TV-Wonder VE",
		.video_inमाला_दो	= 2,
		/* .audio_inमाला_दो= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 1,
		.muxsel		= MUXSEL(2, 3, 0, 1),
		.gpiomux	= अणु 0, 0, 1, 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TEMIC_4006FN5_MULTI_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_FLYVIDEO2000] = अणु
		/* DeeJay <deejay@westel900.net (2000S) */
		.name           = "Lifeview FlyVideo 2000S LR90",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 3, */
		.svhs           = 2,
		.gpiomask	= 0x18e0,
		.muxsel		= MUXSEL(2, 3, 0, 1),
				/* Radio changed from 1e80 to 0x800 to make
				FlyVideo2000S in .hu happy (gm)*/
				/* -dk-???: set mute=0x1800 क्रम tda9874h daughterboard */
		.gpiomux	= अणु 0x0000,0x0800,0x1000,0x1000 पूर्ण,
		.gpiomute	= 0x1800,
		.audio_mode_gpio= fv2000s_audio,
		.no_msp34xx	= 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TERRATVALUER] = अणु
		.name		= "Terratec TValueRadio",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0xffff00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x500, 0x500, 0x300, 0x900 पूर्ण,
		.gpiomute	= 0x900,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_GVBCTV4PCI] = अणु
		/* TANAKA Kei <peg00625@nअगरty.com> */
		.name           = "IODATA GV-BCTV4/PCI",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x010f00,
		.muxsel         = MUXSEL(2, 3, 0, 0),
		.gpiomux        = अणु0x10000, 0, 0x10000, 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_SHARP_2U5JF5540_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= gvbctv3pci_audio,
	पूर्ण,

	/* ---- card 0x44 ---------------------------------- */
	[BTTV_BOARD_VOODOOTV_FM] = अणु
		.name           = "3Dfx VoodooTV FM (Euro)",
		/* try "insmod msp3400 simple=0" अगर you have
		* sound problems with this card. */
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x4f8a00,
		/* 0x100000: 1=MSP enabled (0=disable again)
		* 0x010000: Connected to "S0" on tda9880 (0=Pal/BG, 1=NTSC) */
		.gpiomux        = अणु0x947fff, 0x987fff,0x947fff,0x947fff पूर्ण,
		.gpiomute	= 0x947fff,
		/* tvtuner, radio,   बाह्यal,पूर्णांकernal, mute,  stereo
		* tuner, Composite, SVid, Composite-on-Svid-adapter */
		.muxsel         = MUXSEL(2, 3, 0, 1),
		.tuner_type     = TUNER_MT2032,
		.tuner_addr	= ADDR_UNSET,
		.pll		= PLL_28,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_VOODOOTV_200] = अणु
		.name           = "VoodooTV 200 (USA)",
		/* try "insmod msp3400 simple=0" अगर you have
		* sound problems with this card. */
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x4f8a00,
		/* 0x100000: 1=MSP enabled (0=disable again)
		* 0x010000: Connected to "S0" on tda9880 (0=Pal/BG, 1=NTSC) */
		.gpiomux        = अणु0x947fff, 0x987fff,0x947fff,0x947fff पूर्ण,
		.gpiomute	= 0x947fff,
		/* tvtuner, radio,   बाह्यal,पूर्णांकernal, mute,  stereo
		* tuner, Composite, SVid, Composite-on-Svid-adapter */
		.muxsel         = MUXSEL(2, 3, 0, 1),
		.tuner_type     = TUNER_MT2032,
		.tuner_addr	= ADDR_UNSET,
		.pll		= PLL_28,
		.has_radio	= 1,
	पूर्ण,
	[BTTV_BOARD_AIMMS] = अणु
		/* Philip Blundell <pb@nexus.co.uk> */
		.name           = "Active Imaging AIMMS",
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
		.muxsel         = MUXSEL(2),
		.gpiomask       = 0
	पूर्ण,
	[BTTV_BOARD_PV_BT878P_PLUS] = अणु
		/* Tomasz Pyra <hellfire@sedez.iq.pl> */
		.name           = "Prolink Pixelview PV-BT878P+ (Rev.4C,8E)",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 4, */
		.svhs           = 2,
		.gpiomask       = 15,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 0, 11, 7 पूर्ण, /* TV and Radio with same GPIO ! */
		.gpiomute	= 13,
		.pll            = PLL_28,
		.tuner_type     = TUNER_LG_PAL_I_FM,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
		/* GPIO wiring:
			GPIO0: U4.A0 (hef4052bt)
			GPIO1: U4.A1
			GPIO2: U4.A1 (second hef4052bt)
			GPIO3: U4.nEN, U5.A0, A5.nEN
			GPIO8-15: vrd866b ?
		*/
	पूर्ण,
	[BTTV_BOARD_FLYVIDEO98EZ] = अणु
		.name		= "Lifeview FlyVideo 98EZ (capture only) LR51",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= 2,
		/* AV1, AV2, SVHS, CVid adapter on SVHS */
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.pll		= PLL_28,
		.no_msp34xx	= 1,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

	/* ---- card 0x48 ---------------------------------- */
	[BTTV_BOARD_PV_BT878P_9B] = अणु
		/* Dariusz Kowalewski <darekk@स्वतःmex.pl> */
		.name		= "Prolink Pixelview PV-BT878P+9B (PlayTV Pro rev.9B FM+NICAM)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x3f,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 0x01, 0x00, 0x03, 0x03 पूर्ण,
		.gpiomute	= 0x09,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= pvbt878p9b_audio, /* Note: not all cards have stereo */
		.has_radio	= 1,  /* Note: not all cards have radio */
		.has_remote     = 1,
		/* GPIO wiring:
			GPIO0: A0 hef4052
			GPIO1: A1 hef4052
			GPIO3: nEN hef4052
			GPIO8-15: vrd866b
			GPIO20,22,23: R30,R29,R28
		*/
	पूर्ण,
	[BTTV_BOARD_SENSORAY311_611] = अणु
		/* Clay Kunz <ckunz@mail.arc.nasa.gov> */
		/* you must jumper JP5 क्रम the 311 card (PC/104+) to work */
		.name           = "Sensoray 311/611",
		.video_inमाला_दो   = 5,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 4,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 3, 1, 0, 0),
		.gpiomux        = अणु 0 पूर्ण,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_RV605] = अणु
		/* Miguel Freitas <miguel@cetuc.puc-rio.br> */
		.name           = "RemoteVision MX (RV605)",
		.video_inमाला_दो   = 16,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x07ff,
		.muxsel         = MUXSEL(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.no_msp34xx     = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.muxsel_hook    = rv605_muxsel,
	पूर्ण,
	[BTTV_BOARD_POWERCLR_MTV878] = अणु
		.name           = "Powercolor MTV878/ MTV878R/ MTV878F",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 2, */
		.svhs           = 2,
		.gpiomask       = 0x1C800F,  /* Bit0-2: Audio select, 8-12:remote control 14:remote valid 15:remote reset */
		.muxsel         = MUXSEL(2, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 2 पूर्ण,
		.gpiomute	= 4,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.pll		= PLL_28,
		.has_radio	= 1,
	पूर्ण,

	/* ---- card 0x4c ---------------------------------- */
	[BTTV_BOARD_WINDVR] = अणु
		/* Masaki Suzuki <masaki@btree.org> */
		.name           = "Canopus WinDVR PCI (COMPAQ Presario 3524JP, 5112JP)",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x140007,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= windvr_audio,
	पूर्ण,
	[BTTV_BOARD_GRANDTEC_MULTI] = अणु
		.name           = "GrandTec Multi Capture Card (Bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_KWORLD] = अणु
		.name           = "Jetway TV/Capture JW-TV878-FBK, Kworld KW-TV878RF",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 3, */
		.svhs           = 2,
		.gpiomask       = 7,
		/* Tuner, SVid, SVHS, SVid to SVHS connector */
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 0, 4, 4 पूर्ण,/* Yes, this tuner uses the same audio output क्रम TV and FM radio!
						* This card lacks बाह्यal Audio In, so we mute it on Ext. & Int.
						* The PCB can take a sbx1637/sbx1673, wiring unknown.
						* This card lacks PCI subप्रणाली ID, sigh.
						* gpiomux =1: lower volume, 2+3: mute
						* btwincap uses 0x80000/0x80003
						*/
		.gpiomute	= 4,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		/* Samsung TCPA9095PC27A (BG+DK), philips compatible, w/FM, stereo and
		radio संकेत strength indicators work fine. */
		.has_radio	= 1,
		/* GPIO Info:
			GPIO0,1:   HEF4052 A0,A1
			GPIO2:     HEF4052 nENABLE
			GPIO3-7:   n.c.
			GPIO8-13:  IRDC357 data0-5 (data6 n.c. ?) [chip not present on my card]
			GPIO14,15: ??
			GPIO16-21: n.c.
			GPIO22,23: ??
			??       : mtu8b56ep microcontroller क्रम IR (GPIO wiring unknown)*/
	पूर्ण,
	[BTTV_BOARD_DSP_TCVIDEO] = अणु
		/* Arthur Tetzlaff-Deas, DSP Design Ltd <software@dspdesign.com> */
		.name           = "DSP Design TCVIDEO",
		.video_inमाला_दो   = 4,
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.pll            = PLL_28,
		.tuner_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

		/* ---- card 0x50 ---------------------------------- */
	[BTTV_BOARD_HAUPPAUGEPVR] = अणु
		.name           = "Hauppauge WinTV PVR",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel         = MUXSEL(2, 0, 1, 1),
		.pll            = PLL_28,
		.tuner_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,

		.gpiomask       = 7,
		.gpiomux        = अणु7पूर्ण,
	पूर्ण,
	[BTTV_BOARD_GVBCTV5PCI] = अणु
		.name           = "IODATA GV-BCTV5/PCI",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x0f0f80,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु0x030000, 0x010000, 0, 0 पूर्ण,
		.gpiomute	= 0x020000,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= gvbctv5pci_audio,
		.has_radio      = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY1x0] = अणु
		.name           = "Osprey 100/150 (878)", /* 0x1(2|3)-45C6-C1 */
		.video_inमाला_दो   = 4,                  /* id-inमाला_दो-घड़ी */
		/* .audio_inमाला_दो= 0, */
		.svhs           = 3,
		.muxsel         = MUXSEL(3, 2, 0, 1),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY1x0_848] = अणु
		.name           = "Osprey 100/150 (848)", /* 0x04-54C0-C1 & older boards */
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 2,
		.muxsel         = MUXSEL(2, 3, 1),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,

		/* ---- card 0x54 ---------------------------------- */
	[BTTV_BOARD_OSPREY101_848] = अणु
		.name           = "Osprey 101 (848)", /* 0x05-40C0-C1 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 1,
		.muxsel         = MUXSEL(3, 1),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY1x1] = अणु
		.name           = "Osprey 101/151",       /* 0x1(4|5)-0004-C4 */
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(0),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY1x1_SVID] = अणु
		.name           = "Osprey 101/151 w/ svid",  /* 0x(16|17|20)-00C4-C1 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 1,
		.muxsel         = MUXSEL(0, 1),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY2xx] = अणु
		.name           = "Osprey 200/201/250/251",  /* 0x1(8|9|E|F)-0004-C4 */
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(0),
		.pll            = PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,

		/* ---- card 0x58 ---------------------------------- */
	[BTTV_BOARD_OSPREY2x0_SVID] = अणु
		.name           = "Osprey 200/250",   /* 0x1(A|B)-00C4-C1 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 1,
		.muxsel         = MUXSEL(0, 1),
		.pll            = PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY2x0] = अणु
		.name           = "Osprey 210/220/230",   /* 0x1(A|B)-04C0-C1 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 1,
		.muxsel         = MUXSEL(2, 3),
		.pll            = PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY500] = अणु
		.name           = "Osprey 500",   /* 500 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 1,
		.muxsel         = MUXSEL(2, 3),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	[BTTV_BOARD_OSPREY540] = अणु
		.name           = "Osprey 540",   /* 540 */
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,

		/* ---- card 0x5C ---------------------------------- */
	[BTTV_BOARD_OSPREY2000] = अणु
		.name           = "Osprey 2000",  /* 2000 */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 1,
		.muxsel         = MUXSEL(2, 3),
		.pll            = PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,      /* must aव्योम, conflicts with the bt860 */
	पूर्ण,
	[BTTV_BOARD_IDS_EAGLE] = अणु
		/* M G Berberich <berberic@क्रमwiss.uni-passau.de> */
		.name           = "IDS Eagle",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 2, 2, 2),
		.muxsel_hook    = eagle_muxsel,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_PINNACLESAT] = अणु
		.name           = "Pinnacle PCTV Sat",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.muxsel         = MUXSEL(3, 1),
		.pll            = PLL_28,
		.no_gpioirq     = 1,
		.has_dvb        = 1,
	पूर्ण,
	[BTTV_BOARD_FORMAC_PROTV] = अणु
		.name           = "Formac ProTV II (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 3,
		.gpiomask       = 2,
		/* TV, Comp1, Composite over SVID con, SVID */
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 2, 2, 0, 0 पूर्ण,
		.pll            = PLL_28,
		.has_radio      = 1,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
	/* sound routing:
		GPIO=0x00,0x01,0x03: mute (?)
		0x02: both TV and radio (tuner: FM1216/I)
		The card has onboard audio connectors labeled "cdrom" and "board",
		not soldered here, though unknown wiring.
		Card lacks: बाह्यal audio in, pci subप्रणाली id.
	*/
	पूर्ण,

		/* ---- card 0x60 ---------------------------------- */
	[BTTV_BOARD_MACHTV] = अणु
		.name           = "MachTV",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 7,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 3पूर्ण,
		.gpiomute	= 4,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_EURESYS_PICOLO] = अणु
		.name           = "Euresys Picolo",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 2,
		.gpiomask       = 0,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.muxsel         = MUXSEL(2, 0, 1),
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_PV150] = अणु
		/* Luc Van Hoeylandt <luc@e-magic.be> */
		.name           = "ProVideo PV150", /* 0x4f */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 3),
		.gpiomux        = अणु 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_AD_TVK503] = अणु
		/* Hiroshi Takekawa <sian@big.or.jp> */
		/* This card lacks subप्रणाली ID */
		.name           = "AD-TVK503", /* 0x63 */
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001e8007,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		/*                  Tuner, Radio, बाह्यal, पूर्णांकernal, off,  on */
		.gpiomux        = अणु 0x08,  0x0f,  0x0a,     0x08 पूर्ण,
		.gpiomute	= 0x0f,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.audio_mode_gpio= adtvk503_audio,
	पूर्ण,

		/* ---- card 0x64 ---------------------------------- */
	[BTTV_BOARD_HERCULES_SM_TV] = अणु
		.name           = "Hercules Smart TV Stereo",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		/* Notes:
		- card lacks subप्रणाली ID
		- stereo variant w/ daughter board with tda9874a @0xb0
		- Audio Routing:
			always from tda9874 independent of GPIO (?)
			बाह्यal line in: unknown
		- Other chips: em78p156elp @ 0x96 (probably IR remote control)
			hef4053 (instead 4052) क्रम unknown function
		*/
	पूर्ण,
	[BTTV_BOARD_PACETV] = अणु
		.name           = "Pace TV & Radio Card",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		/* Tuner, CVid, SVid, CVid over SVid connector */
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomask       = 0,
		.no_tda7432     = 1,
		.tuner_type     = TUNER_PHILIPS_PAL_I,
		.tuner_addr	= ADDR_UNSET,
		.has_radio      = 1,
		.pll            = PLL_28,
		/* Bt878, Bt832, FI1246 tuner; no pci subप्रणाली id
		only पूर्णांकernal line out: (4pin header) RGGL
		Radio must be decoded by msp3410d (not routed through)*/
		/*
		.digital_mode   = DIGITAL_MODE_CAMERA,  toकरो!
		*/
	पूर्ण,
	[BTTV_BOARD_IVC200] = अणु
		/* Chris Willing <chris@vislab.usyd.edu.au> */
		.name           = "IVC-200",
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsel         = MUXSEL(2),
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_IVCE8784] = अणु
		.name           = "IVCE-8784",
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr     = ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsel         = MUXSEL(2),
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_XGUARD] = अणु
		.name           = "Grand X-Guard / Trust 814PCI",
		.video_inमाला_दो   = 16,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.gpiomask2      = 0xff,
		.muxsel         = MUXSEL(2,2,2,2, 3,3,3,3, 1,1,1,1, 0,0,0,0),
		.muxsel_hook    = xguard_muxsel,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pll            = PLL_28,
	पूर्ण,

		/* ---- card 0x68 ---------------------------------- */
	[BTTV_BOARD_NEBULA_DIGITV] = अणु
		.name           = "Nebula Electronics DigiTV",
		.video_inमाला_दो   = 1,
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.has_dvb        = 1,
		.has_remote	= 1,
		.gpiomask	= 0x1b,
		.no_gpioirq     = 1,
	पूर्ण,
	[BTTV_BOARD_PV143] = अणु
		/* Jorge Boncompte - DTI2 <jorge@dti2.net> */
		.name           = "ProVideo PV143",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VD009X1_VD011_MINIDIN] = अणु
		/* M.Klahr@phytec.de */
		.name           = "PHYTEC VD-009-X1 VD-011 MiniDIN (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VD009X1_VD011_COMBI] = अणु
		.name           = "PHYTEC VD-009-X1 VD-011 Combi (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,

		/* ---- card 0x6c ---------------------------------- */
	[BTTV_BOARD_VD009_MINIDIN] = अणु
		.name           = "PHYTEC VD-009 MiniDIN (bt878)",
		.video_inमाला_दो   = 10,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 9,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x03, /* used क्रम बाह्यal video mux */
		.muxsel         = MUXSEL(2, 2, 2, 2, 3, 3, 3, 3, 1, 0),
		.muxsel_hook	= phytec_muxsel,
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VD009_COMBI] = अणु
		.name           = "PHYTEC VD-009 Combi (bt878)",
		.video_inमाला_दो   = 10,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 9,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x03, /* used क्रम बाह्यal video mux */
		.muxsel         = MUXSEL(2, 2, 2, 2, 3, 3, 3, 3, 1, 1),
		.muxsel_hook	= phytec_muxsel,
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_IVC100] = अणु
		.name           = "IVC-100",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_IVC120] = अणु
		/* IVC-120G - Alan Garfield <alan@fromorbit.com> */
		.name           = "IVC-120G",
		.video_inमाला_दो   = 16,
		/* .audio_inमाला_दो= 0, */
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,   /* card has no svhs */
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
		.muxsel_hook    = ivc120_muxsel,
		.pll            = PLL_28,
	पूर्ण,

		/* ---- card 0x70 ---------------------------------- */
	[BTTV_BOARD_PC_HDTV] = अणु
		.name           = "pcHDTV HD-2000 TV",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.tuner_type     = TUNER_PHILIPS_FCV1236D,
		.tuner_addr	= ADDR_UNSET,
		.has_dvb        = 1,
	पूर्ण,
	[BTTV_BOARD_TWINHAN_DST] = अणु
		.name           = "Twinhan DST + clones",
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.no_video       = 1,
		.has_dvb        = 1,
	पूर्ण,
	[BTTV_BOARD_WINFASTVC100] = अणु
		.name           = "Winfast VC100",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 1,
		/* Vid In, SVid In, Vid over SVid in connector */
		.muxsel		= MUXSEL(3, 1, 1, 3),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_TEV560] = अणु
		.name           = "Teppro TEV-560/InterVision IV-560",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 3,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 1, 1, 1, 1 पूर्ण,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_35,
	पूर्ण,

		/* ---- card 0x74 ---------------------------------- */
	[BTTV_BOARD_SIMUS_GVC1100] = अणु
		.name           = "SIMUS GVC1100",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
		.muxsel         = MUXSEL(2, 2, 2, 2),
		.gpiomask       = 0x3F,
		.muxsel_hook    = gvc1100_muxsel,
	पूर्ण,
	[BTTV_BOARD_NGSTV_PLUS] = अणु
		/* Carlos Silva r3pek@r3pek.homelinux.org || card 0x75 */
		.name           = "NGS NGSTV+",
		.video_inमाला_दो   = 3,
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsel         = MUXSEL(2, 3, 0, 0),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण,
		.gpiomute	= 0x000003,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_LMLBT4] = अणु
		/* http://linuxmediaद_असल.com */
		.name           = "LMLBT4",
		.video_inमाला_दो   = 4, /* IN1,IN2,IN3,IN4 */
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_TEKRAM_M205] = अणु
		/* Helmroos Harri <harri.helmroos@pp.inet.fi> */
		.name           = "Tekram M205 PRO",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = 2,
		.gpiomask       = 0x68,
		.muxsel         = MUXSEL(2, 3, 1),
		.gpiomux        = अणु 0x68, 0x68, 0x61, 0x61 पूर्ण,
		.pll            = PLL_28,
	पूर्ण,

		/* ---- card 0x78 ---------------------------------- */
	[BTTV_BOARD_CONTVFMI] = अणु
		/* Javier Cendan Ares <jcendan@lycos.es> */
		/* bt878 TV + FM without subप्रणाली ID */
		.name           = "Conceptronic CONTVFMi",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 2 पूर्ण,
		.gpiomute	= 3,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
		.has_radio      = 1,
	पूर्ण,
	[BTTV_BOARD_PICOLO_TETRA_CHIP] = अणु
		/*Eric DEBIEF <debief@telemsa.com>*/
		/*EURESYS Picolo Tetra : 4 Conexant Fusion 878A, no audio, video input set with analog multiplexers GPIO controlled*/
		/*adds picolo_tetra_muxsel(), picolo_tetra_init(), the following declaration*/
		/*काष्ठाure and #घोषणा BTTV_BOARD_PICOLO_TETRA_CHIP 0x79 in bttv.h*/
		.name           = "Euresys Picolo Tetra",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.gpiomask2      = 0x3C<<16,/*Set the GPIO[18]->GPIO[21] as output pin.==> drive the video inमाला_दो through analog multiplexers*/
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		/*878A input is always MUX0, see above.*/
		.muxsel         = MUXSEL(2, 2, 2, 2),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.muxsel_hook    = picolo_tetra_muxsel,/*Required as it करोesn't follow the classic input selection policy*/
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_SPIRIT_TV] = अणु
		/* Spirit TV Tuner from http://spiriपंचांगodems.com.au */
		/* Stafक्रमd Goodsell <surge@goliath.homeunix.org> */
		.name           = "Spirit TV Tuner",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x0000000f,
		.muxsel         = MUXSEL(2, 1, 1),
		.gpiomux        = अणु 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.tuner_type     = TUNER_TEMIC_PAL,
		.tuner_addr	= ADDR_UNSET,
		.no_msp34xx     = 1,
	पूर्ण,
	[BTTV_BOARD_AVDVBT_771] = अणु
		/* Wolfram Joost <wojo@frokaschwei.de> */
		.name           = "AVerMedia AVerTV DVB-T 771",
		.video_inमाला_दो   = 2,
		.svhs           = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.muxsel         = MUXSEL(3, 3),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pll            = PLL_28,
		.has_dvb        = 1,
		.no_gpioirq     = 1,
		.has_remote     = 1,
	पूर्ण,
		/* ---- card 0x7c ---------------------------------- */
	[BTTV_BOARD_AVDVBT_761] = अणु
		/* Matt Jesson <dvb@jesson.eclipse.co.uk> */
		/* Based on the Nebula card data - added remote and new card number - BTTV_BOARD_AVDVBT_761, see also ir-kbd-gpio.c */
		.name           = "AverMedia AverTV DVB-T 761",
		.video_inमाला_दो   = 2,
		.svhs           = 1,
		.muxsel         = MUXSEL(3, 1, 2, 0), /* Comp0, S-Video, ?, ? */
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.has_dvb        = 1,
		.no_gpioirq     = 1,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_MATRIX_VISIONSQ] = अणु
		/* andre.schwarz@matrix-vision.de */
		.name		= "MATRIX Vision Sigma-SQ",
		.video_inमाला_दो	= 16,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsel		= MUXSEL(2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3),
		.muxsel_hook	= sigmaSQ_muxsel,
		.gpiomux	= अणु 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MATRIX_VISIONSLC] = अणु
		/* andre.schwarz@matrix-vision.de */
		.name		= "MATRIX Vision Sigma-SLC",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsel		= MUXSEL(2, 2, 2, 2),
		.muxsel_hook	= sigmaSLC_muxsel,
		.gpiomux	= अणु 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
		/* BTTV_BOARD_APAC_VIEWCOMP */
	[BTTV_BOARD_APAC_VIEWCOMP] = अणु
		/* Attila Konकरोros <attila.konकरोros@chello.hu> */
		/* bt878 TV + FM 0x00000000 subप्रणाली ID */
		.name           = "APAC Viewcomp 878(AMAX)",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0xFF,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 2, 0, 0, 0 पूर्ण,
		.gpiomute	= 10,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,   /* miniremote works, see ir-kbd-gpio.c */
		.has_radio      = 1,   /* not every card has radio */
	पूर्ण,

		/* ---- card 0x80 ---------------------------------- */
	[BTTV_BOARD_DVICO_DVBT_LITE] = अणु
		/* Chris Pascoe <c.pascoe@itee.uq.edu.au> */
		.name           = "DViCO FusionHDTV DVB-T Lite",
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pll            = PLL_28,
		.no_video       = 1,
		.has_dvb        = 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VGEAR_MYVCD] = अणु
		/* Steven <photon38@pchome.com.tw> */
		.name           = "V-Gear MyVCD",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3f,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.gpiomux        = अणु0x31, 0x31, 0x31, 0x31 पूर्ण,
		.gpiomute	= 0x31,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.tuner_addr	= ADDR_UNSET,
		.has_radio      = 0,
	पूर्ण,
	[BTTV_BOARD_SUPER_TV] = अणु
		/* Rick C <cryptdragoon@gmail.com> */
		.name           = "Super TV Tuner",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
		.gpiomask       = 0x008007,
		.gpiomux        = अणु 0, 0x000001,0,0 पूर्ण,
		.has_radio      = 1,
	पूर्ण,
	[BTTV_BOARD_TIBET_CS16] = अणु
		/* Chris Fanning <video4linux@hayकरोn.net> */
		.name           = "Tibet Systems 'Progress DVR' CS16",
		.video_inमाला_दो   = 16,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.pll		= PLL_28,
		.no_msp34xx     = 1,
		.no_tda7432	= 1,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.muxsel_hook    = tibetCS16_muxsel,
	पूर्ण,
	[BTTV_BOARD_KODICOM_4400R] = अणु
		/* Bill Brack <wbrack@mmm.com.hk> */
		/*
		* Note that, because of the card's wiring, the "master"
		* BT878A chip (i.e. the one which controls the analog चयन
		* and must use this card type) is the 2nd one detected.  The
		* other 3 chips should use card type 0x85, whose description
		* follows this one.  There is a EEPROM on the card (which is
		* connected to the I2C of one of those other chips), but is
		* not currently handled.  There is also a facility क्रम a
		* "monitor", which is also not currently implemented.
		*/
		.name           = "Kodicom 4400R (master)",
		.video_inमाला_दो	= 16,
		/* .audio_inमाला_दो= 0, */
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs		= NO_SVHS,
		/* GPIO bits 0-9 used क्रम analog चयन:
		*   00 - 03:	camera selector
		*   04 - 06:	channel (controller) selector
		*   07:	data (1->on, 0->off)
		*   08:	strobe
		*   09:	reset
		* bit 16 is input from sync separator क्रम the channel
		*/
		.gpiomask	= 0x0003ff,
		.no_gpioirq     = 1,
		.muxsel		= MUXSEL(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.pll		= PLL_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsel_hook	= kodicom4400r_muxsel,
	पूर्ण,
	[BTTV_BOARD_KODICOM_4400R_SL] = अणु
		/* Bill Brack <wbrack@mmm.com.hk> */
		/* Note that, क्रम reasons unknown, the "master" BT878A chip (i.e. the
		* one which controls the analog चयन, and must use the card type)
		* is the 2nd one detected.  The other 3 chips should use this card
		* type
		*/
		.name		= "Kodicom 4400R (slave)",
		.video_inमाला_दो	= 16,
		/* .audio_inमाला_दो= 0, */
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs		= NO_SVHS,
		.gpiomask	= 0x010000,
		.no_gpioirq     = 1,
		.muxsel		= MUXSEL(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.pll		= PLL_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsel_hook	= kodicom4400r_muxsel,
	पूर्ण,
		/* ---- card 0x86---------------------------------- */
	[BTTV_BOARD_ADLINK_RTV24] = अणु
		/* Michael Henson <mhenson@clarityvi.com> */
		/* Adlink RTV24 with special unlock codes */
		.name           = "Adlink RTV24",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.tuner_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
	पूर्ण,
		/* ---- card 0x87---------------------------------- */
	[BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE] = अणु
		/* Michael Krufky <mkrufky@linuxtv.org> */
		.name           = "DViCO FusionHDTV 5 Lite",
		.tuner_type     = TUNER_LG_TDVS_H06XF, /* TDVS-H064F */
		.tuner_addr	= ADDR_UNSET,
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel		= MUXSEL(2, 3, 1),
		.gpiomask       = 0x00e00007,
		.gpiomux        = अणु 0x00400005, 0, 0x00000001, 0 पूर्ण,
		.gpiomute	= 0x00c00007,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.has_dvb        = 1,
	पूर्ण,
		/* ---- card 0x88---------------------------------- */
	[BTTV_BOARD_ACORP_Y878F] = अणु
		/* Mauro Carvalho Chehab <mchehab@kernel.org> */
		.name		= "Acorp Y878F",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x01fe00,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0x001e00, 0, 0x018000, 0x014000 पूर्ण,
		.gpiomute	= 0x002000,
		.pll		= PLL_28,
		.tuner_type	= TUNER_YMEC_TVF66T5_B_DFF,
		.tuner_addr	= 0xc1 >>1,
		.has_radio	= 1,
	पूर्ण,
		/* ---- card 0x89 ---------------------------------- */
	[BTTV_BOARD_CONCEPTRONIC_CTVFMI2] = अणु
		.name           = "Conceptronic CTVFMi v2",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001c0007,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 2 पूर्ण,
		.gpiomute	= 3,
		.pll            = PLL_28,
		.tuner_type     = TUNER_TENA_9533_DI,
		.tuner_addr	= ADDR_UNSET,
		.has_remote     = 1,
		.has_radio      = 1,
	पूर्ण,
		/* ---- card 0x8a ---------------------------------- */
	[BTTV_BOARD_PV_BT878P_2E] = अणु
		.name		= "Prolink Pixelview PV-BT878P+ (Rev.2E)",
		.video_inमाला_दो	= 5,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 3,
		.has_dig_in	= 1,
		.gpiomask	= 0x01fe00,
		.muxsel		= MUXSEL(2, 3, 1, 1, 0), /* in 4 is digital */
		/* .digital_mode= DIGITAL_MODE_CAMERA, */
		.gpiomux	= अणु 0x00400, 0x10400, 0x04400, 0x80000 पूर्ण,
		.gpiomute	= 0x12400,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_LG_PAL_FM,
		.tuner_addr	= ADDR_UNSET,
		.has_remote	= 1,
	पूर्ण,
		/* ---- card 0x8b ---------------------------------- */
	[BTTV_BOARD_PV_M4900] = अणु
		/* Sथऊrgio Fortier <sergioक्रमtier@yahoo.com.br> */
		.name           = "Prolink PixelView PlayTV MPEG2 PV-M4900",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3f,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0x21, 0x20, 0x24, 0x2c पूर्ण,
		.gpiomute	= 0x29,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_YMEC_TVF_5533MF,
		.tuner_addr     = ADDR_UNSET,
		.has_radio      = 1,
		.has_remote     = 1,
	पूर्ण,
		/* ---- card 0x8c ---------------------------------- */
	/* Has four Bt878 chips behind a PCI bridge, each chip has:
	     one बाह्यal BNC composite input (mux 2)
	     three पूर्णांकernal composite inमाला_दो (unknown muxes)
	     an 18-bit stereo A/D (CS5331A), which has:
	       one बाह्यal stereo unbalanced (RCA) audio connection
	       one (or 3?) पूर्णांकernal stereo balanced (XLR) audio connection
	       input is selected via gpio to a 14052B mux
		 (mask=0x300, unbal=0x000, bal=0x100, ??=0x200,0x300)
	       gain is controlled via an X9221A chip on the I2C bus @0x28
	       sample rate is controlled via gpio to an MK1413S
		 (mask=0x3, 32kHz=0x0, 44.1kHz=0x1, 48kHz=0x2, ??=0x3)
	     There is neither a tuner nor an svideo input. */
	[BTTV_BOARD_OSPREY440]  = अणु
		.name           = "Osprey 440",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 2, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 3, 0, 1), /* 3,0,1 are guesses */
		.gpiomask	= 0x303,
		.gpiomute	= 0x000, /* पूर्णांक + 32kHz */
		.gpiomux	= अणु 0, 0, 0x000, 0x100पूर्ण,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr     = ADDR_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
		/* ---- card 0x8d ---------------------------------- */
	[BTTV_BOARD_ASOUND_SKYEYE] = अणु
		.name		= "Asound Skyeye PCTV",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 2, 0, 0, 0 पूर्ण,
		.gpiomute	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_PHILIPS_NTSC,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
		/* ---- card 0x8e ---------------------------------- */
	[BTTV_BOARD_SABRENT_TVFM] = अणु
		.name		= "Sabrent TV-FM (bttv version)",
		.video_inमाला_दो	= 3,
		/* .audio_inमाला_दो= 1, */
		.svhs		= 2,
		.gpiomask	= 0x108007,
		.muxsel		= MUXSEL(2, 3, 1, 1),
		.gpiomux	= अणु 100000, 100002, 100002, 100000 पूर्ण,
		.no_msp34xx	= 1,
		.no_tda7432     = 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_TNF_5335MF,
		.tuner_addr	= ADDR_UNSET,
		.has_radio      = 1,
	पूर्ण,
	/* ---- card 0x8f ---------------------------------- */
	[BTTV_BOARD_HAUPPAUGE_IMPACTVCB] = अणु
		.name		= "Hauppauge ImpactVCB (bt878)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0f, /* old: 7 */
		.muxsel		= MUXSEL(0, 1, 3, 2), /* Composite 0-3 */
		.no_msp34xx	= 1,
		.no_tda7432     = 1,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_MACHTV_MAGICTV] = अणु
		/* Julian Calaby <julian.calaby@gmail.com>
		 * Slightly dअगरferent from original MachTV definition (0x60)

		 * FIXME: RegSpy says gpiomask should be "0x001c800f", but it
		 * stuffs up remote chip. Bug is a pin on the jaecs is not set
		 * properly (methinks) causing no keyup bits being set */

		.name           = "MagicTV", /* rebअक्रमed MachTV */
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 7,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 3 पूर्ण,
		.gpiomute	= 4,
		.tuner_type     = TUNER_TEMIC_4009FR5_PAL,
		.tuner_addr     = ADDR_UNSET,
		.pll            = PLL_28,
		.has_radio      = 1,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_SSAI_SECURITY] = अणु
		.name		= "SSAI Security Video Interface",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.muxsel		= MUXSEL(0, 1, 2, 3),
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_SSAI_ULTRASOUND] = अणु
		.name		= "SSAI Ultrasound Video Interface",
		.video_inमाला_दो	= 2,
		/* .audio_inमाला_दो= 0, */
		.svhs		= 1,
		.muxsel		= MUXSEL(2, 0, 1, 3),
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	/* ---- card 0x94---------------------------------- */
	[BTTV_BOARD_DVICO_FUSIONHDTV_2] = अणु
		.name           = "DViCO FusionHDTV 2",
		.tuner_type     = TUNER_PHILIPS_FCV1236D,
		.tuner_addr	= ADDR_UNSET,
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.muxsel		= MUXSEL(2, 3, 1),
		.gpiomask       = 0x00e00007,
		.gpiomux        = अणु 0x00400005, 0, 0x00000001, 0 पूर्ण,
		.gpiomute	= 0x00c00007,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	पूर्ण,
	/* ---- card 0x95---------------------------------- */
	[BTTV_BOARD_TYPHOON_TVTUNERPCI] = अणु
		.name           = "Typhoon TV-Tuner PCI (50684)",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3014f,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0x20001,0x10001, 0, 0 पूर्ण,
		.gpiomute       = 10,
		.pll            = PLL_28,
		.tuner_type     = TUNER_PHILIPS_PAL_I,
		.tuner_addr     = ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_GEOVISION_GV600] = अणु
		/* emhn@usb.ve */
		.name		= "Geovision GV-600",
		.video_inमाला_दो	= 16,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsel		= MUXSEL(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.muxsel_hook	= geovision_muxsel,
		.gpiomux	= अणु 0 पूर्ण,
		.no_msp34xx	= 1,
		.pll		= PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_KOZUMI_KTV_01C] = अणु
		/* Mauro Lacy <mauro@lacy.com.ar>
		 * Based on MagicTV and Conceptronic CONTVFMi */

		.name           = "Kozumi KTV-01C",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 2 पूर्ण, /* CONTVFMi */
		.gpiomute	= 3, /* CONTVFMi */
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3, /* TCL MK3 */
		.tuner_addr     = ADDR_UNSET,
		.pll            = PLL_28,
		.has_radio      = 1,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_ENLTV_FM_2] = अणु
		/* Encore TV Tuner Pro ENL TV-FM-2
		   Mauro Carvalho Chehab <mchehab@kernel.org> */
		.name           = "Encore ENL TV-FM-2",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		/* bit 6          -> IR disabled
		   bit 18/17 = 00 -> mute
			       01 -> enable बाह्यal audio input
			       10 -> पूर्णांकernal audio input (mono?)
			       11 -> पूर्णांकernal audio input
		 */
		.gpiomask       = 0x060040,
		.muxsel         = MUXSEL(2, 3, 3),
		.gpiomux        = अणु 0x60000, 0x60000, 0x20000, 0x20000 पूर्ण,
		.gpiomute	= 0,
		.tuner_type	= TUNER_TCL_MF02GIP_5N,
		.tuner_addr     = ADDR_UNSET,
		.pll            = PLL_28,
		.has_radio      = 1,
		.has_remote     = 1,
	पूर्ण,
	[BTTV_BOARD_VD012] = अणु
		/* D.Heer@Phytec.de */
		.name           = "PHYTEC VD-012 (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(0, 2, 3, 1),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VD012_X1] = अणु
		/* D.Heer@Phytec.de */
		.name           = "PHYTEC VD-012-X1 (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(2, 3, 1),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_VD012_X2] = अणु
		/* D.Heer@Phytec.de */
		.name           = "PHYTEC VD-012-X2 (bt878)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsel         = MUXSEL(3, 2, 1),
		.gpiomux        = अणु 0, 0, 0, 0 पूर्ण, /* card has no audio */
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_GEOVISION_GV800S] = अणु
		/* Bruno Christo <bchristo@inf.ufsm.br>
		 *
		 * GeoVision GV-800(S) has 4 Conexant Fusion 878A:
		 *	1 audio input  per BT878A = 4 audio inमाला_दो
		 *	4 video inमाला_दो per BT878A = 16 video inमाला_दो
		 * This is the first BT878A chip of the GV-800(S). It's the
		 * "master" chip and it controls the video inमाला_दो through an
		 * analog multiplexer (a CD22M3494) via some GPIO pins. The
		 * slaves should use card type 0x9e (following this one).
		 * There is a EEPROM on the card which is currently not handled.
		 * The audio input is not working yet.
		 */
		.name           = "Geovision GV-800(S) (master)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask	= 0xf107f,
		.no_gpioirq     = 1,
		.muxsel		= MUXSEL(2, 2, 2, 2),
		.pll		= PLL_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsel_hook    = gv800s_muxsel,
	पूर्ण,
	[BTTV_BOARD_GEOVISION_GV800S_SL] = अणु
		/* Bruno Christo <bchristo@inf.ufsm.br>
		 *
		 * GeoVision GV-800(S) has 4 Conexant Fusion 878A:
		 *	1 audio input  per BT878A = 4 audio inमाला_दो
		 *	4 video inमाला_दो per BT878A = 16 video inमाला_दो
		 * The 3 other BT878A chips are "slave" chips of the GV-800(S)
		 * and should use this card type.
		 * The audio input is not working yet.
		 */
		.name           = "Geovision GV-800(S) (slave)",
		.video_inमाला_दो   = 4,
		/* .audio_inमाला_दो= 1, */
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask	= 0x00,
		.no_gpioirq     = 1,
		.muxsel		= MUXSEL(2, 2, 2, 2),
		.pll		= PLL_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsel_hook    = gv800s_muxsel,
	पूर्ण,
	[BTTV_BOARD_PV183] = अणु
		.name           = "ProVideo PV183", /* 0x9f */
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsel         = MUXSEL(2, 3),
		.gpiomux        = अणु 0 पूर्ण,
		.no_msp34xx     = 1,
		.pll            = PLL_28,
		.tuner_type     = TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	/* ---- card 0xa0---------------------------------- */
	[BTTV_BOARD_TVT_TD3116] = अणु
		.name           = "Tongwei Video Technology TD-3116",
		.video_inमाला_दो   = 16,
		.gpiomask       = 0xc00ff,
		.muxsel         = MUXSEL(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.muxsel_hook    = td3116_muxsel,
		.svhs           = NO_SVHS,
		.pll		= PLL_28,
		.tuner_type     = TUNER_ABSENT,
	पूर्ण,
	[BTTV_BOARD_APOSONIC_WDVR] = अणु
		.name           = "Aposonic W-DVR",
		.video_inमाला_दो   = 4,
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 3, 1, 0),
		.tuner_type     = TUNER_ABSENT,
	पूर्ण,
	[BTTV_BOARD_ADLINK_MPG24] = अणु
		/* Adlink MPG24 */
		.name           = "Adlink MPG24",
		.video_inमाला_दो   = 1,
		/* .audio_inमाला_दो= 1, */
		.svhs           = NO_SVHS,
		.muxsel         = MUXSEL(2, 2, 2, 2),
		.tuner_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.pll            = PLL_28,
	पूर्ण,
	[BTTV_BOARD_BT848_CAP_14] = अणु
		.name		= "Bt848 Capture 14MHz",
		.video_inमाला_दो	= 4,
		.svhs		= 2,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.pll		= PLL_14,
		.tuner_type	= TUNER_ABSENT,
	पूर्ण,
	[BTTV_BOARD_CYBERVISION_CV06] = अणु
		.name		= "CyberVision CV06 (SV)",
		.video_inमाला_दो	= 4,
		/* .audio_inमाला_दो= 0, */
		.svhs		= NO_SVHS,
		.muxsel		= MUXSEL(2, 3, 1, 0),
		.pll		= PLL_28,
		.tuner_type	= TUNER_ABSENT,
		.tuner_addr	= ADDR_UNSET,
	पूर्ण,
	[BTTV_BOARD_KWORLD_VSTREAM_XPERT] = अणु
		/* Pojar George <geoubuntu@gmail.com> */
		.name           = "Kworld V-Stream Xpert TV PVR878",
		.video_inमाला_दो   = 3,
		/* .audio_inमाला_दो= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001c0007,
		.muxsel         = MUXSEL(2, 3, 1, 1),
		.gpiomux        = अणु 0, 1, 2, 2 पूर्ण,
		.gpiomute       = 3,
		.pll            = PLL_28,
		.tuner_type     = TUNER_TENA_9533_DI,
		.tuner_addr    = ADDR_UNSET,
		.has_remote     = 1,
		.has_radio      = 1,
	पूर्ण,
	/* ---- card 0xa6---------------------------------- */
	[BTTV_BOARD_PCI_8604PW] = अणु
		/* PCI-8604PW with special unlock sequence */
		.name           = "PCI-8604PW",
		.video_inमाला_दो   = 2,
		/* .audio_inमाला_दो= 0, */
		.svhs           = NO_SVHS,
		/* The second input is available on CN4, अगर populated.
		 * The other 5x2 header (CN2?) connects to the same inमाला_दो
		 * as the on-board BNCs */
		.muxsel         = MUXSEL(2, 3),
		.tuner_type     = TUNER_ABSENT,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.pll            = PLL_35,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bttv_num_tvcards = ARRAY_SIZE(bttv_tvcards);

/* ----------------------------------------------------------------------- */

अटल अचिन्हित अक्षर eeprom_data[256];

/*
 * identअगरy card
 */
व्योम bttv_idcard(काष्ठा bttv *btv)
अणु
	अचिन्हित पूर्णांक gpiobits;
	पूर्णांक i,type;

	/* पढ़ो PCI subप्रणाली ID */
	btv->cardid  = btv->c.pci->subप्रणाली_device << 16;
	btv->cardid |= btv->c.pci->subप्रणाली_venकरोr;

	अगर (0 != btv->cardid && 0xffffffff != btv->cardid) अणु
		/* look क्रम the card */
		क्रम (type = -1, i = 0; cards[i].id != 0; i++)
			अगर (cards[i].id  == btv->cardid)
				type = i;

		अगर (type != -1) अणु
			/* found it */
			pr_info("%d: detected: %s [card=%d], PCI subsystem ID is %04x:%04x\n",
				btv->c.nr, cards[type].name, cards[type].cardnr,
				btv->cardid & 0xffff,
				(btv->cardid >> 16) & 0xffff);
			btv->c.type = cards[type].cardnr;
		पूर्ण अन्यथा अणु
			/* 404 */
			pr_info("%d: subsystem: %04x:%04x (UNKNOWN)\n",
				btv->c.nr, btv->cardid & 0xffff,
				(btv->cardid >> 16) & 0xffff);
			pr_debug("please mail id, board name and the correct card= insmod option to linux-media@vger.kernel.org\n");
		पूर्ण
	पूर्ण

	/* let the user override the स्वतःdetected type */
	अगर (card[btv->c.nr] < bttv_num_tvcards)
		btv->c.type=card[btv->c.nr];

	/* prपूर्णांक which card config we are using */
	pr_info("%d: using: %s [card=%d,%s]\n",
		btv->c.nr, bttv_tvcards[btv->c.type].name, btv->c.type,
		card[btv->c.nr] < bttv_num_tvcards
		? "insmod option" : "autodetected");

	/* overग_लिखो gpio stuff ?? */
	अगर (UNSET == audioall && UNSET == audiomux[0])
		वापस;

	अगर (UNSET != audiomux[0]) अणु
		gpiobits = 0;
		क्रम (i = 0; i < ARRAY_SIZE(bttv_tvcards->gpiomux); i++) अणु
			bttv_tvcards[btv->c.type].gpiomux[i] = audiomux[i];
			gpiobits |= audiomux[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		gpiobits = audioall;
		क्रम (i = 0; i < ARRAY_SIZE(bttv_tvcards->gpiomux); i++) अणु
			bttv_tvcards[btv->c.type].gpiomux[i] = audioall;
		पूर्ण
	पूर्ण
	bttv_tvcards[btv->c.type].gpiomask = (UNSET != gpiomask) ? gpiomask : gpiobits;
	pr_info("%d: gpio config override: mask=0x%x, mux=",
		btv->c.nr, bttv_tvcards[btv->c.type].gpiomask);
	क्रम (i = 0; i < ARRAY_SIZE(bttv_tvcards->gpiomux); i++) अणु
		pr_cont("%s0x%x",
			i ? "," : "", bttv_tvcards[btv->c.type].gpiomux[i]);
	पूर्ण
	pr_cont("\n");
पूर्ण

/*
 * (most) board specअगरic initialisations goes here
 */

/* Some Modular Technology cards have an eeprom, but no subप्रणाली ID */
अटल व्योम identअगरy_by_eeprom(काष्ठा bttv *btv, अचिन्हित अक्षर eeprom_data[256])
अणु
	पूर्णांक type = -1;

	अगर (0 == म_भेदन(eeprom_data,"GET MM20xPCTV",13))
		type = BTTV_BOARD_MODTEC_205;
	अन्यथा अगर (0 == म_भेदन(eeprom_data+20,"Picolo",7))
		type = BTTV_BOARD_EURESYS_PICOLO;
	अन्यथा अगर (eeprom_data[0] == 0x84 && eeprom_data[2]== 0)
		type = BTTV_BOARD_HAUPPAUGE; /* old bt848 */

	अगर (-1 != type) अणु
		btv->c.type = type;
		pr_info("%d: detected by eeprom: %s [card=%d]\n",
			btv->c.nr, bttv_tvcards[btv->c.type].name, btv->c.type);
	पूर्ण
पूर्ण

अटल व्योम flyvideo_gpio(काष्ठा bttv *btv)
अणु
	पूर्णांक gpio, has_remote, has_radio, is_capture_only;
	पूर्णांक is_lr90, has_tda9820_tda9821;
	पूर्णांक tuner_type = UNSET, ttype;

	gpio_inout(0xffffff, 0);
	udelay(8);  /* without this we would see the 0x1800 mask */
	gpio = gpio_पढ़ो();
	/* FIXME: must restore OUR_EN ??? */

	/* all cards provide GPIO info, some have an additional eeprom
	 * LR50: GPIO coding can be found lower right CP1 .. CP9
	 *       CP9=GPIO23 .. CP1=GPIO15; when OPEN, the corresponding GPIO पढ़ोs 1.
	 *       GPIO14-12: n.c.
	 * LR90: GP9=GPIO23 .. GP1=GPIO15 (right above the bt878)

	 * lowest 3 bytes are remote control codes (no handshake needed)
	 * xxxFFF: No remote control chip soldered
	 * xxxF00(LR26/LR50), xxxFE0(LR90): Remote control chip (LVA001 or CF45) soldered
	 * Note: Some bits are Audio_Mask !
	 */
	ttype = (gpio & 0x0f0000) >> 16;
	चयन (ttype) अणु
	हाल 0x0:
		tuner_type = 2;  /* NTSC, e.g. TPI8NSR11P */
		अवरोध;
	हाल 0x2:
		tuner_type = 39; /* LG NTSC (newer TAPC series) TAPC-H701P */
		अवरोध;
	हाल 0x4:
		tuner_type = 5;  /* Philips PAL TPI8PSB02P, TPI8PSB12P, TPI8PSB12D or FI1216, FM1216 */
		अवरोध;
	हाल 0x6:
		tuner_type = 37; /* LG PAL (newer TAPC series) TAPC-G702P */
		अवरोध;
	हाल 0xC:
		tuner_type = 3;  /* Philips SECAM(+PAL) FQ1216ME or FI1216MF */
		अवरोध;
	शेष:
		pr_info("%d: FlyVideo_gpio: unknown tuner type\n", btv->c.nr);
		अवरोध;
	पूर्ण

	has_remote          =   gpio & 0x800000;
	has_radio	    =   gpio & 0x400000;
	/*   unknown                   0x200000;
	 *   unknown2                  0x100000; */
	is_capture_only     = !(gpio & 0x008000); /* GPIO15 */
	has_tda9820_tda9821 = !(gpio & 0x004000);
	is_lr90             = !(gpio & 0x002000); /* अन्यथा LR26/LR50 (LR38/LR51 f. capture only) */
	/*
	 * gpio & 0x001000    output bit क्रम audio routing */

	अगर (is_capture_only)
		tuner_type = TUNER_ABSENT; /* No tuner present */

	pr_info("%d: FlyVideo Radio=%s RemoteControl=%s Tuner=%d gpio=0x%06x\n",
		btv->c.nr, has_radio ? "yes" : "no",
		has_remote ? "yes" : "no", tuner_type, gpio);
	pr_info("%d: FlyVideo  LR90=%s tda9821/tda9820=%s capture_only=%s\n",
		btv->c.nr, is_lr90 ? "yes" : "no",
		has_tda9820_tda9821 ? "yes" : "no",
		is_capture_only ? "yes" : "no");

	अगर (tuner_type != UNSET) /* only set अगर known tuner स्वतःdetected, अन्यथा let insmod option through */
		btv->tuner_type = tuner_type;
	btv->has_radio = has_radio;

	/* LR90 Audio Routing is करोne by 2 hef4052, so Audio_Mask has 4 bits: 0x001c80
	 * LR26/LR50 only has 1 hef4052, Audio_Mask 0x000c00
	 * Audio options: from tuner, from tda9821/tda9821(mono,stereo,sap), from tda9874, ext., mute */
	अगर (has_tda9820_tda9821)
		btv->audio_mode_gpio = lt9415_audio;
	/* toकरो: अगर(has_tda9874) btv->audio_mode_gpio = fv2000s_audio; */
पूर्ण

अटल पूर्णांक miro_tunermap[] = अणु 0,6,2,3,   4,5,6,0,  3,0,4,5,  5,2,16,1,
			       14,2,17,1, 4,1,4,3,  1,2,16,1, 4,4,4,4 पूर्ण;
अटल पूर्णांक miro_fmtuner[]  = अणु 0,0,0,0,   0,0,0,0,  0,0,0,0,  0,0,0,1,
			       1,1,1,1,   1,1,1,0,  0,0,0,0,  0,1,0,0 पूर्ण;

अटल व्योम miro_pinnacle_gpio(काष्ठा bttv *btv)
अणु
	पूर्णांक id,msp,gpio;
	अक्षर *info;

	gpio_inout(0xffffff, 0);
	gpio = gpio_पढ़ो();
	id   = ((gpio>>10) & 63) -1;
	msp  = bttv_I2CRead(btv, I2C_ADDR_MSP3400, "MSP34xx");
	अगर (id < 32) अणु
		btv->tuner_type = miro_tunermap[id];
		अगर (0 == (gpio & 0x20)) अणु
			btv->has_radio = 1;
			अगर (!miro_fmtuner[id]) अणु
				btv->has_tea575x = 1;
				btv->tea_gpio.wren = 6;
				btv->tea_gpio.most = 7;
				btv->tea_gpio.clk  = 8;
				btv->tea_gpio.data = 9;
				tea575x_init(btv);
			पूर्ण
		पूर्ण अन्यथा अणु
			btv->has_radio = 0;
		पूर्ण
		अगर (-1 != msp) अणु
			अगर (btv->c.type == BTTV_BOARD_MIRO)
				btv->c.type = BTTV_BOARD_MIROPRO;
			अगर (btv->c.type == BTTV_BOARD_PINNACLE)
				btv->c.type = BTTV_BOARD_PINNACLEPRO;
		पूर्ण
		pr_info("%d: miro: id=%d tuner=%d radio=%s stereo=%s\n",
			btv->c.nr, id+1, btv->tuner_type,
			!btv->has_radio ? "no" :
			(btv->has_tea575x ? "tea575x" : "fmtuner"),
			(-1 == msp) ? "no" : "yes");
	पूर्ण अन्यथा अणु
		/* new cards with microtune tuner */
		id = 63 - id;
		btv->has_radio = 0;
		चयन (id) अणु
		हाल 1:
			info = "PAL / mono";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			अवरोध;
		हाल 2:
			info = "PAL+SECAM / stereo";
			btv->has_radio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			अवरोध;
		हाल 3:
			info = "NTSC / stereo";
			btv->has_radio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			अवरोध;
		हाल 4:
			info = "PAL+SECAM / mono";
			btv->tda9887_conf = TDA9887_QSS;
			अवरोध;
		हाल 5:
			info = "NTSC / mono";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			अवरोध;
		हाल 6:
			info = "NTSC / stereo";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			अवरोध;
		हाल 7:
			info = "PAL / stereo";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			अवरोध;
		शेष:
			info = "oops: unknown card";
			अवरोध;
		पूर्ण
		अगर (-1 != msp)
			btv->c.type = BTTV_BOARD_PINNACLEPRO;
		pr_info("%d: pinnacle/mt: id=%d info=\"%s\" radio=%s\n",
			btv->c.nr, id, info, btv->has_radio ? "yes" : "no");
		btv->tuner_type = TUNER_MT2032;
	पूर्ण
पूर्ण

/* GPIO21   L: Buffer aktiv, H: Buffer inaktiv */
#घोषणा LM1882_SYNC_DRIVE     0x200000L

अटल व्योम init_ids_eagle(काष्ठा bttv *btv)
अणु
	gpio_inout(0xffffff,0xFFFF37);
	gpio_ग_लिखो(0x200020);

	/* flash strobe inverter ?! */
	gpio_ग_लिखो(0x200024);

	/* चयन sync drive off */
	gpio_bits(LM1882_SYNC_DRIVE,LM1882_SYNC_DRIVE);

	/* set BT848 muxel to 2 */
	btaor((2)<<5, ~(2<<5), BT848_IFORM);
पूर्ण

/* Muxsel helper क्रम the IDS Eagle.
 * the eagles करोes not use the standard muxsel-bits but
 * has its own multiplexer */
अटल व्योम eagle_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	gpio_bits(3, input & 3);

	/* composite */
	/* set chroma ADC to sleep */
	btor(BT848_ADC_C_SLEEP, BT848_ADC);
	/* set to composite video */
	btand(~BT848_CONTROL_COMP, BT848_E_CONTROL);
	btand(~BT848_CONTROL_COMP, BT848_O_CONTROL);

	/* चयन sync drive off */
	gpio_bits(LM1882_SYNC_DRIVE,LM1882_SYNC_DRIVE);
पूर्ण

अटल व्योम gvc1100_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अटल स्थिर पूर्णांक masks[] = अणु0x30, 0x01, 0x12, 0x23पूर्ण;
	gpio_ग_लिखो(masks[input%4]);
पूर्ण

/* LMLBT4x initialization - to allow access to GPIO bits क्रम sensors input and
   alarms output

   GPIObit    | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   assignment | TI | O3|INx| O2| O1|IN4|IN3|IN2|IN1|   |   |

   IN - sensor inमाला_दो, INx - sensor inमाला_दो and TI XORed together
   O1,O2,O3 - alarm outमाला_दो (relays)

   OUT ENABLE   1    1   0  . 1  1   0   0 . 0   0   0    0   = 0x6C0

*/

अटल व्योम init_lmlbt4x(काष्ठा bttv *btv)
अणु
	pr_debug("LMLBT4x init\n");
	btग_लिखो(0x000000, BT848_GPIO_REG_INP);
	gpio_inout(0xffffff, 0x0006C0);
	gpio_ग_लिखो(0x000000);
पूर्ण

अटल व्योम sigmaSQ_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अचिन्हित पूर्णांक inmux = input % 8;
	gpio_inout( 0xf, 0xf );
	gpio_bits( 0xf, inmux );
पूर्ण

अटल व्योम sigmaSLC_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अचिन्हित पूर्णांक inmux = input % 4;
	gpio_inout( 3<<9, 3<<9 );
	gpio_bits( 3<<9, inmux<<9 );
पूर्ण

अटल व्योम geovision_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अचिन्हित पूर्णांक inmux = input % 16;
	gpio_inout(0xf, 0xf);
	gpio_bits(0xf, inmux);
पूर्ण

/*
 * The TD3116 has 2 74HC4051 muxes wired to the MUX0 input of a bt878.
 * The first 74HC4051 has the lower 8 inमाला_दो, the second one the higher 8.
 * The muxes are controlled via a 74HC373 latch which is connected to
 * GPIOs 0-7. GPIO 18 is connected to the LE संकेत of the latch.
 * Q0 of the latch is connected to the Enable (~E) input of the first
 * 74HC4051. Q1 - Q3 are connected to S0 - S2 of the same 74HC4051.
 * Q4 - Q7 are connected to the second 74HC4051 in the same way.
 */

अटल व्योम td3116_latch_value(काष्ठा bttv *btv, u32 value)
अणु
	gpio_bits((1<<18) | 0xff, value);
	gpio_bits((1<<18) | 0xff, (1<<18) | value);
	udelay(1);
	gpio_bits((1<<18) | 0xff, value);
पूर्ण

अटल व्योम td3116_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	u32 value;
	u32 highbit;

	highbit = (input & 0x8) >> 3 ;

	/* Disable outमाला_दो and set value in the mux */
	value = 0x11; /* Disable outमाला_दो */
	value |= ((input & 0x7) << 1)  << (4 * highbit);
	td3116_latch_value(btv, value);

	/* Enable the correct output */
	value &= ~0x11;
	value |= ((highbit ^ 0x1) << 4) | highbit;
	td3116_latch_value(btv, value);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम bttv_reset_audio(काष्ठा bttv *btv)
अणु
	/*
	 * BT878A has a audio-reset रेजिस्टर.
	 * 1. This रेजिस्टर is an audio reset function but it is in
	 *    function-0 (video capture) address space.
	 * 2. It is enough to करो this once per घातer-up of the card.
	 * 3. There is a typo in the Conexant करोc -- it is not at
	 *    0x5B, but at 0x058. (B is an odd-number, obviously a typo!).
	 * --//Shrikumar 030609
	 */
	अगर (btv->id != 878)
		वापस;

	अगर (bttv_debug)
		pr_debug("%d: BT878A ARESET\n", btv->c.nr);
	btग_लिखो((1<<7), 0x058);
	udelay(10);
	btग_लिखो(     0, 0x058);
पूर्ण

/* initialization part one -- beक्रमe रेजिस्टरing i2c bus */
व्योम bttv_init_card1(काष्ठा bttv *btv)
अणु
	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_HAUPPAUGE:
	हाल BTTV_BOARD_HAUPPAUGE878:
		boot_msp34xx(btv,5);
		अवरोध;
	हाल BTTV_BOARD_VOODOOTV_200:
	हाल BTTV_BOARD_VOODOOTV_FM:
		boot_msp34xx(btv,20);
		अवरोध;
	हाल BTTV_BOARD_AVERMEDIA98:
		boot_msp34xx(btv,11);
		अवरोध;
	हाल BTTV_BOARD_HAUPPAUGEPVR:
		pvr_boot(btv);
		अवरोध;
	हाल BTTV_BOARD_TWINHAN_DST:
	हाल BTTV_BOARD_AVDVBT_771:
	हाल BTTV_BOARD_PINNACLESAT:
		btv->use_i2c_hw = 1;
		अवरोध;
	हाल BTTV_BOARD_ADLINK_RTV24:
		init_RTV24( btv );
		अवरोध;
	हाल BTTV_BOARD_PCI_8604PW:
		init_PCI8604PW(btv);
		अवरोध;

	पूर्ण
	अगर (!bttv_tvcards[btv->c.type].has_dvb)
		bttv_reset_audio(btv);
पूर्ण

/* initialization part two -- after रेजिस्टरing i2c bus */
व्योम bttv_init_card2(काष्ठा bttv *btv)
अणु
	btv->tuner_type = UNSET;

	अगर (BTTV_BOARD_UNKNOWN == btv->c.type) अणु
		bttv_पढ़ोee(btv,eeprom_data,0xa0);
		identअगरy_by_eeprom(btv,eeprom_data);
	पूर्ण

	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_MIRO:
	हाल BTTV_BOARD_MIROPRO:
	हाल BTTV_BOARD_PINNACLE:
	हाल BTTV_BOARD_PINNACLEPRO:
		/* miro/pinnacle */
		miro_pinnacle_gpio(btv);
		अवरोध;
	हाल BTTV_BOARD_FLYVIDEO_98:
	हाल BTTV_BOARD_MAXI:
	हाल BTTV_BOARD_LIFE_FLYKIT:
	हाल BTTV_BOARD_FLYVIDEO:
	हाल BTTV_BOARD_TYPHOON_TVIEW:
	हाल BTTV_BOARD_CHRONOS_VS2:
	हाल BTTV_BOARD_FLYVIDEO_98FM:
	हाल BTTV_BOARD_FLYVIDEO2000:
	हाल BTTV_BOARD_FLYVIDEO98EZ:
	हाल BTTV_BOARD_CONFERENCETV:
	हाल BTTV_BOARD_LIFETEC_9415:
		flyvideo_gpio(btv);
		अवरोध;
	हाल BTTV_BOARD_HAUPPAUGE:
	हाल BTTV_BOARD_HAUPPAUGE878:
	हाल BTTV_BOARD_HAUPPAUGEPVR:
		/* pick up some config infos from the eeprom */
		bttv_पढ़ोee(btv,eeprom_data,0xa0);
		hauppauge_eeprom(btv);
		अवरोध;
	हाल BTTV_BOARD_AVERMEDIA98:
	हाल BTTV_BOARD_AVPHONE98:
		bttv_पढ़ोee(btv,eeprom_data,0xa0);
		avermedia_eeprom(btv);
		अवरोध;
	हाल BTTV_BOARD_PXC200:
		init_PXC200(btv);
		अवरोध;
	हाल BTTV_BOARD_PICOLO_TETRA_CHIP:
		picolo_tetra_init(btv);
		अवरोध;
	हाल BTTV_BOARD_VHX:
		btv->has_radio    = 1;
		btv->has_tea575x  = 1;
		btv->tea_gpio.wren = 5;
		btv->tea_gpio.most = 6;
		btv->tea_gpio.clk  = 3;
		btv->tea_gpio.data = 4;
		tea575x_init(btv);
		अवरोध;
	हाल BTTV_BOARD_VOBIS_BOOSTAR:
	हाल BTTV_BOARD_TERRATV:
		terratec_active_radio_upgrade(btv);
		अवरोध;
	हाल BTTV_BOARD_MAGICTVIEW061:
		अगर (btv->cardid == 0x3002144f) अणु
			btv->has_radio=1;
			pr_info("%d: radio detected by subsystem id (CPH05x)\n",
				btv->c.nr);
		पूर्ण
		अवरोध;
	हाल BTTV_BOARD_STB2:
		अगर (btv->cardid == 0x3060121a) अणु
			/* Fix up entry क्रम 3DFX VooकरोoTV 100,
			   which is an OEM STB card variant. */
			btv->has_radio=0;
			btv->tuner_type=TUNER_TEMIC_NTSC;
		पूर्ण
		अवरोध;
	हाल BTTV_BOARD_OSPREY1x0:
	हाल BTTV_BOARD_OSPREY1x0_848:
	हाल BTTV_BOARD_OSPREY101_848:
	हाल BTTV_BOARD_OSPREY1x1:
	हाल BTTV_BOARD_OSPREY1x1_SVID:
	हाल BTTV_BOARD_OSPREY2xx:
	हाल BTTV_BOARD_OSPREY2x0_SVID:
	हाल BTTV_BOARD_OSPREY2x0:
	हाल BTTV_BOARD_OSPREY440:
	हाल BTTV_BOARD_OSPREY500:
	हाल BTTV_BOARD_OSPREY540:
	हाल BTTV_BOARD_OSPREY2000:
		bttv_पढ़ोee(btv,eeprom_data,0xa0);
		osprey_eeprom(btv, eeprom_data);
		अवरोध;
	हाल BTTV_BOARD_IDS_EAGLE:
		init_ids_eagle(btv);
		अवरोध;
	हाल BTTV_BOARD_MODTEC_205:
		bttv_पढ़ोee(btv,eeprom_data,0xa0);
		modtec_eeprom(btv);
		अवरोध;
	हाल BTTV_BOARD_LMLBT4:
		init_lmlbt4x(btv);
		अवरोध;
	हाल BTTV_BOARD_TIBET_CS16:
		tibetCS16_init(btv);
		अवरोध;
	हाल BTTV_BOARD_KODICOM_4400R:
		kodicom4400r_init(btv);
		अवरोध;
	हाल BTTV_BOARD_GEOVISION_GV800S:
		gv800s_init(btv);
		अवरोध;
	पूर्ण

	/* pll configuration */
	अगर (!(btv->id==848 && btv->revision==0x11)) अणु
		/* शेषs from card list */
		अगर (PLL_28 == bttv_tvcards[btv->c.type].pll) अणु
			btv->pll.pll_अगरreq=28636363;
			btv->pll.pll_crystal=BT848_IFORM_XT0;
		पूर्ण
		अगर (PLL_35 == bttv_tvcards[btv->c.type].pll) अणु
			btv->pll.pll_अगरreq=35468950;
			btv->pll.pll_crystal=BT848_IFORM_XT1;
		पूर्ण
		अगर (PLL_14 == bttv_tvcards[btv->c.type].pll) अणु
			btv->pll.pll_अगरreq = 14318181;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
		पूर्ण
		/* insmod options can override */
		चयन (pll[btv->c.nr]) अणु
		हाल 0: /* none */
			btv->pll.pll_crystal = 0;
			btv->pll.pll_अगरreq   = 0;
			btv->pll.pll_ofreq   = 0;
			अवरोध;
		हाल 1: /* 28 MHz */
		हाल 28:
			btv->pll.pll_अगरreq   = 28636363;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
			अवरोध;
		हाल 2: /* 35 MHz */
		हाल 35:
			btv->pll.pll_अगरreq   = 35468950;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT1;
			अवरोध;
		हाल 3: /* 14 MHz */
		हाल 14:
			btv->pll.pll_अगरreq   = 14318181;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
			अवरोध;
		पूर्ण
	पूर्ण
	btv->pll.pll_current = -1;

	/* tuner configuration (from card list / स्वतःdetect / insmod option) */
	अगर (UNSET != bttv_tvcards[btv->c.type].tuner_type)
		अगर (UNSET == btv->tuner_type)
			btv->tuner_type = bttv_tvcards[btv->c.type].tuner_type;
	अगर (UNSET != tuner[btv->c.nr])
		btv->tuner_type = tuner[btv->c.nr];

	अगर (btv->tuner_type == TUNER_ABSENT)
		pr_info("%d: tuner absent\n", btv->c.nr);
	अन्यथा अगर (btv->tuner_type == UNSET)
		pr_warn("%d: tuner type unset\n", btv->c.nr);
	अन्यथा
		pr_info("%d: tuner type=%d\n", btv->c.nr, btv->tuner_type);

	अगर (स्वतःload != UNSET) अणु
		pr_warn("%d: the autoload option is obsolete\n", btv->c.nr);
		pr_warn("%d: use option msp3400, tda7432 or tvaudio to override which audio module should be used\n",
			btv->c.nr);
	पूर्ण

	अगर (UNSET == btv->tuner_type)
		btv->tuner_type = TUNER_ABSENT;

	btv->dig = bttv_tvcards[btv->c.type].has_dig_in ?
		   bttv_tvcards[btv->c.type].video_inमाला_दो - 1 : UNSET;
	btv->svhs = bttv_tvcards[btv->c.type].svhs == NO_SVHS ?
		    UNSET : bttv_tvcards[btv->c.type].svhs;
	अगर (svhs[btv->c.nr] != UNSET)
		btv->svhs = svhs[btv->c.nr];
	अगर (remote[btv->c.nr] != UNSET)
		btv->has_remote = remote[btv->c.nr];

	अगर (bttv_tvcards[btv->c.type].has_radio)
		btv->has_radio = 1;
	अगर (bttv_tvcards[btv->c.type].has_remote)
		btv->has_remote = 1;
	अगर (!bttv_tvcards[btv->c.type].no_gpioirq)
		btv->gpioirq = 1;
	अगर (bttv_tvcards[btv->c.type].volume_gpio)
		btv->volume_gpio = bttv_tvcards[btv->c.type].volume_gpio;
	अगर (bttv_tvcards[btv->c.type].audio_mode_gpio)
		btv->audio_mode_gpio = bttv_tvcards[btv->c.type].audio_mode_gpio;

	अगर (btv->tuner_type == TUNER_ABSENT)
		वापस;  /* no tuner or related drivers to load */

	अगर (btv->has_saa6588 || saa6588[btv->c.nr]) अणु
		/* Probe क्रम RDS receiver chip */
		अटल स्थिर अचिन्हित लघु addrs[] = अणु
			0x20 >> 1,
			0x22 >> 1,
			I2C_CLIENT_END
		पूर्ण;
		काष्ठा v4l2_subdev *sd;

		sd = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "saa6588", 0, addrs);
		btv->has_saa6588 = (sd != शून्य);
	पूर्ण

	/* try to detect audio/fader chips */

	/* First check अगर the user specअगरied the audio chip via a module
	   option. */

	चयन (audiodev[btv->c.nr]) अणु
	हाल -1:
		वापस;	/* करो not load any audio module */

	हाल 0: /* स्वतःdetect */
		अवरोध;

	हाल 1: अणु
		/* The user specअगरied that we should probe क्रम msp3400 */
		अटल स्थिर अचिन्हित लघु addrs[] = अणु
			I2C_ADDR_MSP3400 >> 1,
			I2C_ADDR_MSP3400_ALT >> 1,
			I2C_CLIENT_END
		पूर्ण;

		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400", 0, addrs);
		अगर (btv->sd_msp34xx)
			वापस;
		जाओ no_audio;
	पूर्ण

	हाल 2: अणु
		/* The user specअगरied that we should probe क्रम tda7432 */
		अटल स्थिर अचिन्हित लघु addrs[] = अणु
			I2C_ADDR_TDA7432 >> 1,
			I2C_CLIENT_END
		पूर्ण;

		अगर (v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addrs))
			वापस;
		जाओ no_audio;
	पूर्ण

	हाल 3: अणु
		/* The user specअगरied that we should probe क्रम tvaudio */
		btv->sd_tvaudio = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
		अगर (btv->sd_tvaudio)
			वापस;
		जाओ no_audio;
	पूर्ण

	शेष:
		pr_warn("%d: unknown audiodev value!\n", btv->c.nr);
		वापस;
	पूर्ण

	/* There were no overrides, so now we try to discover this through the
	   card definition */

	/* probe क्रम msp3400 first: this driver can detect whether or not
	   it really is a msp3400, so it will वापस शून्य when the device
	   found is really something अन्यथा (e.g. a tea6300). */
	अगर (!bttv_tvcards[btv->c.type].no_msp34xx) अणु
		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDRS(I2C_ADDR_MSP3400 >> 1));
	पूर्ण अन्यथा अगर (bttv_tvcards[btv->c.type].msp34xx_alt) अणु
		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDRS(I2C_ADDR_MSP3400_ALT >> 1));
	पूर्ण

	/* If we found a msp34xx, then we're करोne. */
	अगर (btv->sd_msp34xx)
		वापस;

	/* Now see अगर we can find one of the tvaudio devices. */
	btv->sd_tvaudio = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
		&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
	अगर (btv->sd_tvaudio) अणु
		/* There may be two tvaudio chips on the card, so try to
		   find another. */
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
	पूर्ण

	/* it might also be a tda7432. */
	अगर (!bttv_tvcards[btv->c.type].no_tda7432) अणु
		अटल स्थिर अचिन्हित लघु addrs[] = अणु
			I2C_ADDR_TDA7432 >> 1,
			I2C_CLIENT_END
		पूर्ण;

		btv->sd_tda7432 = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addrs);
		अगर (btv->sd_tda7432)
			वापस;
	पूर्ण
	अगर (btv->sd_tvaudio)
		वापस;

no_audio:
	pr_warn("%d: audio absent, no audio device found!\n", btv->c.nr);
पूर्ण


/* initialize the tuner */
व्योम bttv_init_tuner(काष्ठा bttv *btv)
अणु
	पूर्णांक addr = ADDR_UNSET;

	अगर (ADDR_UNSET != bttv_tvcards[btv->c.type].tuner_addr)
		addr = bttv_tvcards[btv->c.type].tuner_addr;

	अगर (btv->tuner_type != TUNER_ABSENT) अणु
		काष्ठा tuner_setup tun_setup;

		/* Load tuner module beक्रमe issuing tuner config call! */
		अगर (btv->has_radio)
			v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_RADIO));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_TV_WITH_DEMOD));

		tun_setup.mode_mask = T_ANALOG_TV;
		tun_setup.type = btv->tuner_type;
		tun_setup.addr = addr;

		अगर (btv->has_radio)
			tun_setup.mode_mask |= T_RADIO;

		bttv_call_all(btv, tuner, s_type_addr, &tun_setup);
	पूर्ण

	अगर (btv->tda9887_conf) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &btv->tda9887_conf;

		bttv_call_all(btv, tuner, s_config, &tda9887_cfg);
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम modtec_eeprom(काष्ठा bttv *btv)
अणु
	अगर( म_भेदन(&(eeprom_data[0x1e]),"Temic 4066 FY5",14) ==0) अणु
		btv->tuner_type=TUNER_TEMIC_4066FY5_PAL_I;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	पूर्ण अन्यथा अगर (म_भेदन(&(eeprom_data[0x1e]),"Alps TSBB5",10) ==0) अणु
		btv->tuner_type=TUNER_ALPS_TSBB5_PAL_I;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	पूर्ण अन्यथा अगर (म_भेदन(&(eeprom_data[0x1e]),"Philips FM1246",14) ==0) अणु
		btv->tuner_type=TUNER_PHILIPS_NTSC;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	पूर्ण अन्यथा अणु
		pr_info("%d: Modtec: Unknown TunerString: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	पूर्ण
पूर्ण

अटल व्योम hauppauge_eeprom(काष्ठा bttv *btv)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);
	btv->tuner_type = tv.tuner_type;
	btv->has_radio  = tv.has_radio;

	pr_info("%d: Hauppauge eeprom indicates model#%d\n",
		btv->c.nr, tv.model);

	/*
	 * Some of the 878 boards have duplicate PCI IDs. Switch the board
	 * type based on model #.
	 */
	अगर(tv.model == 64900) अणु
		pr_info("%d: Switching board type from %s to %s\n",
			btv->c.nr,
			bttv_tvcards[btv->c.type].name,
			bttv_tvcards[BTTV_BOARD_HAUPPAUGE_IMPACTVCB].name);
		btv->c.type = BTTV_BOARD_HAUPPAUGE_IMPACTVCB;
	पूर्ण

	/* The 61334 needs the msp3410 to करो the radio demod to get sound */
	अगर (tv.model == 61334)
		btv->radio_uses_msp_demodulator = 1;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम bttv_tea575x_set_pins(काष्ठा snd_tea575x *tea, u8 pins)
अणु
	काष्ठा bttv *btv = tea->निजी_data;
	काष्ठा bttv_tea575x_gpio gpio = btv->tea_gpio;
	u16 val = 0;

	val |= (pins & TEA575X_DATA) ? (1 << gpio.data) : 0;
	val |= (pins & TEA575X_CLK)  ? (1 << gpio.clk)  : 0;
	val |= (pins & TEA575X_WREN) ? (1 << gpio.wren) : 0;

	gpio_bits((1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren), val);
	अगर (btv->mbox_ior) अणु
		/* IOW and CSEL active */
		gpio_bits(btv->mbox_iow | btv->mbox_csel, 0);
		udelay(5);
		/* all inactive */
		gpio_bits(btv->mbox_ior | btv->mbox_iow | btv->mbox_csel,
			  btv->mbox_ior | btv->mbox_iow | btv->mbox_csel);
	पूर्ण
पूर्ण

अटल u8 bttv_tea575x_get_pins(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा bttv *btv = tea->निजी_data;
	काष्ठा bttv_tea575x_gpio gpio = btv->tea_gpio;
	u8 ret = 0;
	u16 val;

	अगर (btv->mbox_ior) अणु
		/* IOR and CSEL active */
		gpio_bits(btv->mbox_ior | btv->mbox_csel, 0);
		udelay(5);
	पूर्ण
	val = gpio_पढ़ो();
	अगर (btv->mbox_ior) अणु
		/* all inactive */
		gpio_bits(btv->mbox_ior | btv->mbox_iow | btv->mbox_csel,
			  btv->mbox_ior | btv->mbox_iow | btv->mbox_csel);
	पूर्ण

	अगर (val & (1 << gpio.data))
		ret |= TEA575X_DATA;
	अगर (val & (1 << gpio.most))
		ret |= TEA575X_MOST;

	वापस ret;
पूर्ण

अटल व्योम bttv_tea575x_set_direction(काष्ठा snd_tea575x *tea, bool output)
अणु
	काष्ठा bttv *btv = tea->निजी_data;
	काष्ठा bttv_tea575x_gpio gpio = btv->tea_gpio;
	u32 mask = (1 << gpio.clk) | (1 << gpio.wren) | (1 << gpio.data) |
		   (1 << gpio.most);

	अगर (output)
		gpio_inout(mask, (1 << gpio.data) | (1 << gpio.clk) |
				 (1 << gpio.wren));
	अन्यथा
		gpio_inout(mask, (1 << gpio.clk) | (1 << gpio.wren));
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops bttv_tea_ops = अणु
	.set_pins = bttv_tea575x_set_pins,
	.get_pins = bttv_tea575x_get_pins,
	.set_direction = bttv_tea575x_set_direction,
पूर्ण;

अटल पूर्णांक tea575x_init(काष्ठा bttv *btv)
अणु
	btv->tea.निजी_data = btv;
	btv->tea.ops = &bttv_tea_ops;
	अगर (!snd_tea575x_hw_init(&btv->tea)) अणु
		pr_info("%d: detected TEA575x radio\n", btv->c.nr);
		btv->tea.mute = false;
		वापस 0;
	पूर्ण

	btv->has_tea575x = 0;
	btv->has_radio = 0;

	वापस -ENODEV;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक terratec_active_radio_upgrade(काष्ठा bttv *btv)
अणु
	btv->has_radio    = 1;
	btv->has_tea575x  = 1;
	btv->tea_gpio.wren = 4;
	btv->tea_gpio.most = 5;
	btv->tea_gpio.clk  = 3;
	btv->tea_gpio.data = 2;

	btv->mbox_iow     = 1 <<  8;
	btv->mbox_ior     = 1 <<  9;
	btv->mbox_csel    = 1 << 10;

	अगर (!tea575x_init(btv)) अणु
		pr_info("%d: Terratec Active Radio Upgrade found\n", btv->c.nr);
		btv->has_saa6588 = 1;
	पूर्ण

	वापस 0;
पूर्ण


/* ----------------------------------------------------------------------- */

/*
 * minimal bootstrap क्रम the WinTV/PVR -- upload altera firmware.
 *
 * The hcwamc.rbf firmware file is on the Hauppauge driver CD.  Have
 * a look at Pvr/pvr45xxx.EXE (self-extracting zip archive, can be
 * unpacked with unzip).
 */
#घोषणा PVR_GPIO_DELAY		10

#घोषणा BTTV_ALT_DATA		0x000001
#घोषणा BTTV_ALT_DCLK		0x100000
#घोषणा BTTV_ALT_NCONFIG	0x800000

अटल पूर्णांक pvr_altera_load(काष्ठा bttv *btv, स्थिर u8 *micro, u32 microlen)
अणु
	u32 n;
	u8 bits;
	पूर्णांक i;

	gpio_inout(0xffffff,BTTV_ALT_DATA|BTTV_ALT_DCLK|BTTV_ALT_NCONFIG);
	gpio_ग_लिखो(0);
	udelay(PVR_GPIO_DELAY);

	gpio_ग_लिखो(BTTV_ALT_NCONFIG);
	udelay(PVR_GPIO_DELAY);

	क्रम (n = 0; n < microlen; n++) अणु
		bits = micro[n];
		क्रम (i = 0 ; i < 8 ; i++) अणु
			gpio_bits(BTTV_ALT_DCLK,0);
			अगर (bits & 0x01)
				gpio_bits(BTTV_ALT_DATA,BTTV_ALT_DATA);
			अन्यथा
				gpio_bits(BTTV_ALT_DATA,0);
			gpio_bits(BTTV_ALT_DCLK,BTTV_ALT_DCLK);
			bits >>= 1;
		पूर्ण
	पूर्ण
	gpio_bits(BTTV_ALT_DCLK,0);
	udelay(PVR_GPIO_DELAY);

	/* begin Altera init loop (Not necessary,but करोesn't hurt) */
	क्रम (i = 0 ; i < 30 ; i++) अणु
		gpio_bits(BTTV_ALT_DCLK,0);
		gpio_bits(BTTV_ALT_DCLK,BTTV_ALT_DCLK);
	पूर्ण
	gpio_bits(BTTV_ALT_DCLK,0);
	वापस 0;
पूर्ण

अटल पूर्णांक pvr_boot(काष्ठा bttv *btv)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक rc;

	rc = request_firmware(&fw_entry, "hcwamc.rbf", &btv->c.pci->dev);
	अगर (rc != 0) अणु
		pr_warn("%d: no altera firmware [via hotplug]\n", btv->c.nr);
		वापस rc;
	पूर्ण
	rc = pvr_altera_load(btv, fw_entry->data, fw_entry->size);
	pr_info("%d: altera firmware upload %s\n",
		btv->c.nr, (rc < 0) ? "failed" : "ok");
	release_firmware(fw_entry);
	वापस rc;
पूर्ण

/* ----------------------------------------------------------------------- */
/* some osprey specअगरic stuff                                              */

अटल व्योम osprey_eeprom(काष्ठा bttv *btv, स्थिर u8 ee[256])
अणु
	पूर्णांक i;
	u32 serial = 0;
	पूर्णांक cardid = -1;

	/* This code will never actually get called in this हाल.... */
	अगर (btv->c.type == BTTV_BOARD_UNKNOWN) अणु
		/* this might be an antique... check क्रम MMAC label in eeprom */
		अगर (!म_भेदन(ee, "MMAC", 4)) अणु
			u8 checksum = 0;
			क्रम (i = 0; i < 21; i++)
				checksum += ee[i];
			अगर (checksum != ee[21])
				वापस;
			cardid = BTTV_BOARD_OSPREY1x0_848;
			क्रम (i = 12; i < 21; i++) अणु
				serial *= 10;
				serial += ee[i] - '0';
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित लघु type;

		क्रम (i = 4 * 16; i < 8 * 16; i += 16) अणु
			u16 checksum = (__क्रमce u16)ip_compute_csum(ee + i, 16);

			अगर ((checksum & 0xff) + (checksum >> 8) == 0xff)
				अवरोध;
		पूर्ण
		अगर (i >= 8*16)
			वापस;
		ee += i;

		/* found a valid descriptor */
		type = get_unaligned_be16((__be16 *)(ee+4));

		चयन(type) अणु
		/* 848 based */
		हाल 0x0004:
			cardid = BTTV_BOARD_OSPREY1x0_848;
			अवरोध;
		हाल 0x0005:
			cardid = BTTV_BOARD_OSPREY101_848;
			अवरोध;

		/* 878 based */
		हाल 0x0012:
		हाल 0x0013:
			cardid = BTTV_BOARD_OSPREY1x0;
			अवरोध;
		हाल 0x0014:
		हाल 0x0015:
			cardid = BTTV_BOARD_OSPREY1x1;
			अवरोध;
		हाल 0x0016:
		हाल 0x0017:
		हाल 0x0020:
			cardid = BTTV_BOARD_OSPREY1x1_SVID;
			अवरोध;
		हाल 0x0018:
		हाल 0x0019:
		हाल 0x001E:
		हाल 0x001F:
			cardid = BTTV_BOARD_OSPREY2xx;
			अवरोध;
		हाल 0x001A:
		हाल 0x001B:
			cardid = BTTV_BOARD_OSPREY2x0_SVID;
			अवरोध;
		हाल 0x0040:
			cardid = BTTV_BOARD_OSPREY500;
			अवरोध;
		हाल 0x0050:
		हाल 0x0056:
			cardid = BTTV_BOARD_OSPREY540;
			/* bttv_osprey_540_init(btv); */
			अवरोध;
		हाल 0x0060:
		हाल 0x0070:
		हाल 0x00A0:
			cardid = BTTV_BOARD_OSPREY2x0;
			/* enable output on select control lines */
			gpio_inout(0xffffff,0x000303);
			अवरोध;
		हाल 0x00D8:
			cardid = BTTV_BOARD_OSPREY440;
			अवरोध;
		शेष:
			/* unknown...leave generic, but get serial # */
			pr_info("%d: osprey eeprom: unknown card type 0x%04x\n",
				btv->c.nr, type);
			अवरोध;
		पूर्ण
		serial = get_unaligned_be32((__be32 *)(ee+6));
	पूर्ण

	pr_info("%d: osprey eeprom: card=%d '%s' serial=%u\n",
		btv->c.nr, cardid,
		cardid > 0 ? bttv_tvcards[cardid].name : "Unknown", serial);

	अगर (cardid<0 || btv->c.type == cardid)
		वापस;

	/* card type isn't set correctly */
	अगर (card[btv->c.nr] < bttv_num_tvcards) अणु
		pr_warn("%d: osprey eeprom: Not overriding user specified card type\n",
			btv->c.nr);
	पूर्ण अन्यथा अणु
		pr_info("%d: osprey eeprom: Changing card type from %d to %d\n",
			btv->c.nr, btv->c.type, cardid);
		btv->c.type = cardid;
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------- */
/* AVermedia specअगरic stuff, from  bktr_card.c                             */

अटल पूर्णांक tuner_0_table[] = अणु
	TUNER_PHILIPS_NTSC,  TUNER_PHILIPS_PAL /* PAL-BG*/,
	TUNER_PHILIPS_PAL,   TUNER_PHILIPS_PAL /* PAL-I*/,
	TUNER_PHILIPS_PAL,   TUNER_PHILIPS_PAL,
	TUNER_PHILIPS_SECAM, TUNER_PHILIPS_SECAM,
	TUNER_PHILIPS_SECAM, TUNER_PHILIPS_PAL,
	TUNER_PHILIPS_FM1216ME_MK3 पूर्ण;

अटल पूर्णांक tuner_1_table[] = अणु
	TUNER_TEMIC_NTSC,  TUNER_TEMIC_PAL,
	TUNER_TEMIC_PAL,   TUNER_TEMIC_PAL,
	TUNER_TEMIC_PAL,   TUNER_TEMIC_PAL,
	TUNER_TEMIC_4012FY5, TUNER_TEMIC_4012FY5, /* TUNER_TEMIC_SECAM */
	TUNER_TEMIC_4012FY5, TUNER_TEMIC_PALपूर्ण;

अटल व्योम avermedia_eeprom(काष्ठा bttv *btv)
अणु
	पूर्णांक tuner_make, tuner_tv_fm, tuner_क्रमmat, tuner_type = 0;

	tuner_make      = (eeprom_data[0x41] & 0x7);
	tuner_tv_fm     = (eeprom_data[0x41] & 0x18) >> 3;
	tuner_क्रमmat    = (eeprom_data[0x42] & 0xf0) >> 4;
	btv->has_remote = (eeprom_data[0x42] & 0x01);

	अगर (tuner_make == 0 || tuner_make == 2)
		अगर (tuner_क्रमmat <= 0x0a)
			tuner_type = tuner_0_table[tuner_क्रमmat];
	अगर (tuner_make == 1)
		अगर (tuner_क्रमmat <= 9)
			tuner_type = tuner_1_table[tuner_क्रमmat];

	अगर (tuner_make == 4)
		अगर (tuner_क्रमmat == 0x09)
			tuner_type = TUNER_LG_NTSC_NEW_TAPC; /* TAPC-G702P */

	pr_info("%d: Avermedia eeprom[0x%02x%02x]: tuner=",
		btv->c.nr, eeprom_data[0x41], eeprom_data[0x42]);
	अगर (tuner_type) अणु
		btv->tuner_type = tuner_type;
		pr_cont("%d", tuner_type);
	पूर्ण अन्यथा
		pr_cont("Unknown type");
	pr_cont(" radio:%s remote control:%s\n",
	       tuner_tv_fm     ? "yes" : "no",
	       btv->has_remote ? "yes" : "no");
पूर्ण

/*
 * For Vooकरोo TV/FM and Vooकरोo 200.  These cards' tuners use a TDA9880
 * analog demod, which is not I2C controlled like the newer and more common
 * TDA9887 series.  Instead it has two tri-state input pins, S0 and S1,
 * that control the IF क्रम the video and audio.  Apparently, bttv GPIO
 * 0x10000 is connected to S0.  S0 low selects a 38.9 MHz VIF क्रम B/G/D/K/I
 * (i.e., PAL) जबतक high selects 45.75 MHz क्रम M/N (i.e., NTSC).
 */
u32 bttv_tda9880_setnorm(काष्ठा bttv *btv, u32 gpiobits)
अणु

	अगर (btv->audio_input == TVAUDIO_INPUT_TUNER) अणु
		अगर (bttv_tvnorms[btv->tvnorm].v4l2_id & V4L2_STD_MN)
			gpiobits |= 0x10000;
		अन्यथा
			gpiobits &= ~0x10000;
	पूर्ण

	gpio_bits(bttv_tvcards[btv->c.type].gpiomask, gpiobits);
	वापस gpiobits;
पूर्ण


/*
 * reset/enable the MSP on some Hauppauge cards
 * Thanks to Kyथघsti Mथअlkki (kmalkki@cc.hut.fi)!
 *
 * Hauppauge:  pin  5
 * Vooकरोo:     pin 20
 */
अटल व्योम boot_msp34xx(काष्ठा bttv *btv, पूर्णांक pin)
अणु
	पूर्णांक mask = (1 << pin);

	gpio_inout(mask,mask);
	gpio_bits(mask,0);
	mdelay(2);
	udelay(500);
	gpio_bits(mask,mask);

	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"msp34xx");
	अगर (bttv_verbose)
		pr_info("%d: Hauppauge/Voodoo msp34xx: reset line init [%d]\n",
			btv->c.nr, pin);
पूर्ण

/* ----------------------------------------------------------------------- */
/*  Imagenation L-Model PXC200 Framegrabber */
/*  This is basically the same procedure as
 *  used by Alessandro Rubini in his pxc200
 *  driver, but using BTTV functions */

अटल व्योम init_PXC200(काष्ठा bttv *btv)
अणु
	अटल पूर्णांक vals[] = अणु 0x08, 0x09, 0x0a, 0x0b, 0x0d, 0x0d, 0x01, 0x02,
			      0x03, 0x04, 0x05, 0x06, 0x00 पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक पंचांगp;
	u32 val;

	/* Initialise GPIO-connected stuff */
	gpio_inout(0xffffff, (1<<13));
	gpio_ग_लिखो(0);
	udelay(3);
	gpio_ग_लिखो(1<<13);
	/* GPIO inमाला_दो are pulled up, so no need to drive
	 * reset pin any दीर्घer */
	gpio_bits(0xffffff, 0);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"pxc200");

	/*  we could/should try and reset/control the AD pots? but
	    right now  we simply  turned off the crushing.  Without
	    this the AGC drअगरts drअगरts
	    remember the EN is reverse logic -->
	    setting BT848_ADC_AGC_EN disable the AGC
	    tboult@eecs.lehigh.edu
	*/

	btग_लिखो(BT848_ADC_RESERVED|BT848_ADC_AGC_EN, BT848_ADC);

	/*	Initialise MAX517 DAC */
	pr_info("Setting DAC reference voltage level ...\n");
	bttv_I2CWrite(btv,0x5E,0,0x80,1);

	/*	Initialise 12C508 PIC */
	/*	The I2CWrite and I2CRead commands are actually to the
	 *	same chips - but the R/W bit is included in the address
	 *	argument so the numbers are dअगरferent */


	pr_info("Initialising 12C508 PIC chip ...\n");

	/* First of all, enable the घड़ी line. This is used in the PXC200-F */
	val = btपढ़ो(BT848_GPIO_DMA_CTL);
	val |= BT848_GPIO_DMA_CTL_GPCLKMODE;
	btग_लिखो(val, BT848_GPIO_DMA_CTL);

	/* Then, push to 0 the reset pin दीर्घ enough to reset the *
	 * device same as above क्रम the reset line, but not the same
	 * value sent to the GPIO-connected stuff
	 * which one is the good one? */
	gpio_inout(0xffffff,(1<<2));
	gpio_ग_लिखो(0);
	udelay(10);
	gpio_ग_लिखो(1<<2);

	क्रम (i = 0; i < ARRAY_SIZE(vals); i++) अणु
		पंचांगp=bttv_I2CWrite(btv,0x1E,0,vals[i],1);
		अगर (पंचांगp != -1) अणु
			pr_info("I2C Write(%2.2x) = %i\nI2C Read () = %2.2x\n\n",
			       vals[i],पंचांगp,bttv_I2CRead(btv,0x1F,शून्य));
		पूर्ण
	पूर्ण

	pr_info("PXC200 Initialised\n");
पूर्ण



/* ----------------------------------------------------------------------- */
/*
 *  The Adlink RTV-24 (aka Angelo) has some special initialisation to unlock
 *  it. This apparently involves the following procedure क्रम each 878 chip:
 *
 *  1) ग_लिखो 0x00C3FEFF to the GPIO_OUT_EN रेजिस्टर
 *
 *  2)  ग_लिखो to GPIO_DATA
 *      - 0x0E
 *      - sleep 1ms
 *      - 0x10 + 0x0E
 *      - sleep 10ms
 *      - 0x0E
 *     पढ़ो from GPIO_DATA पूर्णांकo buf (uपूर्णांक_32)
 *      - अगर ( data>>18 & 0x01 != 0) || ( buf>>19 & 0x01 != 1 )
 *                 error. ERROR_CPLD_Check_Failed stop.
 *
 *  3) ग_लिखो to GPIO_DATA
 *      - ग_लिखो 0x4400 + 0x0E
 *      - sleep 10ms
 *      - ग_लिखो 0x4410 + 0x0E
 *      - sleep 1ms
 *      - ग_लिखो 0x0E
 *     पढ़ो from GPIO_DATA पूर्णांकo buf (uपूर्णांक_32)
 *      - अगर ( buf>>18 & 0x01 ) || ( buf>>19 & 0x01 != 0 )
 *                error. ERROR_CPLD_Check_Failed.
 */
/* ----------------------------------------------------------------------- */
अटल व्योम
init_RTV24 (काष्ठा bttv *btv)
अणु
	uपूर्णांक32_t dataRead = 0;
	दीर्घ watchकरोg_value = 0x0E;

	pr_info("%d: Adlink RTV-24 initialisation in progress ...\n",
		btv->c.nr);

	btग_लिखो (0x00c3feff, BT848_GPIO_OUT_EN);

	btग_लिखो (0 + watchकरोg_value, BT848_GPIO_DATA);
	msleep (1);
	btग_लिखो (0x10 + watchकरोg_value, BT848_GPIO_DATA);
	msleep (10);
	btग_लिखो (0 + watchकरोg_value, BT848_GPIO_DATA);

	dataRead = btपढ़ो (BT848_GPIO_DATA);

	अगर ((((dataRead >> 18) & 0x01) != 0) || (((dataRead >> 19) & 0x01) != 1)) अणु
		pr_info("%d: Adlink RTV-24 initialisation(1) ERROR_CPLD_Check_Failed (read %d)\n",
			btv->c.nr, dataRead);
	पूर्ण

	btग_लिखो (0x4400 + watchकरोg_value, BT848_GPIO_DATA);
	msleep (10);
	btग_लिखो (0x4410 + watchकरोg_value, BT848_GPIO_DATA);
	msleep (1);
	btग_लिखो (watchकरोg_value, BT848_GPIO_DATA);
	msleep (1);
	dataRead = btपढ़ो (BT848_GPIO_DATA);

	अगर ((((dataRead >> 18) & 0x01) != 0) || (((dataRead >> 19) & 0x01) != 0)) अणु
		pr_info("%d: Adlink RTV-24 initialisation(2) ERROR_CPLD_Check_Failed (read %d)\n",
			btv->c.nr, dataRead);

		वापस;
	पूर्ण

	pr_info("%d: Adlink RTV-24 initialisation complete\n", btv->c.nr);
पूर्ण



/* ----------------------------------------------------------------------- */
/*
 *  The PCI-8604PW contains a CPLD, probably an ispMACH 4A, that filters
 *  the PCI REQ संकेतs coming from the four BT878 chips. After घातer
 *  up, the CPLD करोes not क्रमward requests to the bus, which prevents
 *  the BT878 from fetching RISC inकाष्ठाions from memory. While the
 *  CPLD is connected to most of the GPIOs of PCI device 0xD, only
 *  five appear to play a role in unlocking the REQ संकेत. The following
 *  sequence has been determined by trial and error without access to the
 *  original driver.
 *
 *  Eight GPIOs of device 0xC are provided on connector CN4 (4 in, 4 out).
 *  Devices 0xE and 0xF करो not appear to have anything connected to their
 *  GPIOs.
 *
 *  The correct GPIO_OUT_EN value might have some more bits set. It should
 *  be possible to derive it from a boundary scan of the CPLD. Its JTAG
 *  pins are routed to test poपूर्णांकs.
 *
 */
/* ----------------------------------------------------------------------- */
अटल व्योम
init_PCI8604PW(काष्ठा bttv *btv)
अणु
	पूर्णांक state;

	अगर ((PCI_SLOT(btv->c.pci->devfn) & ~3) != 0xC) अणु
		pr_warn("This is not a PCI-8604PW\n");
		वापस;
	पूर्ण

	अगर (PCI_SLOT(btv->c.pci->devfn) != 0xD)
		वापस;

	btग_लिखो(0x080002, BT848_GPIO_OUT_EN);

	state = (btपढ़ो(BT848_GPIO_DATA) >> 21) & 7;

	क्रम (;;) अणु
		चयन (state) अणु
		हाल 1:
		हाल 5:
		हाल 6:
		हाल 4:
			pr_debug("PCI-8604PW in state %i, toggling pin\n",
				 state);
			btग_लिखो(0x080000, BT848_GPIO_DATA);
			msleep(1);
			btग_लिखो(0x000000, BT848_GPIO_DATA);
			msleep(1);
			अवरोध;
		हाल 7:
			pr_info("PCI-8604PW unlocked\n");
			वापस;
		हाल 0:
			/* FIXME: If we are in state 7 and toggle GPIO[19] one
			   more समय, the CPLD goes पूर्णांकo state 0, where PCI bus
			   mastering is inhibited again. We have not managed to
			   get out of that state. */

			pr_err("PCI-8604PW locked until reset\n");
			वापस;
		शेष:
			pr_err("PCI-8604PW in unknown state %i\n", state);
			वापस;
		पूर्ण

		state = (state << 4) | ((btपढ़ो(BT848_GPIO_DATA) >> 21) & 7);

		चयन (state) अणु
		हाल 0x15:
		हाल 0x56:
		हाल 0x64:
		हाल 0x47:
		/* The transition from state 7 to state 0 is, as explained
		   above, valid but undesired and with this code impossible
		   as we निकास as soon as we are in state 7.
		हाल 0x70: */
			अवरोध;
		शेष:
			pr_err("PCI-8604PW invalid transition %i -> %i\n",
			       state >> 4, state & 7);
			वापस;
		पूर्ण
		state &= 7;
	पूर्ण
पूर्ण

/* RemoteVision MX (rv605) muxsel helper [Miguel Freitas]
 *
 * This is needed because rv605 करोn't use a normal multiplex, but a crosspoपूर्णांक
 * चयन instead (CD22M3494E). This IC can have multiple active connections
 * between Xn (input) and Yn (output) pins. We need to clear any existing
 * connection prior to establish a new one, pulsing the STROBE pin.
 *
 * The board hardwire Y0 (xpoपूर्णांक) to MUX1 and MUXOUT to Yin.
 * GPIO pins are wired as:
 *  GPIO[0:3] - AX[0:3] (xpoपूर्णांक) - P1[0:3] (microcontroller)
 *  GPIO[4:6] - AY[0:2] (xpoपूर्णांक) - P1[4:6] (microcontroller)
 *  GPIO[7]   - DATA (xpoपूर्णांक)    - P1[7] (microcontroller)
 *  GPIO[8]   -                  - P3[5] (microcontroller)
 *  GPIO[9]   - RESET (xpoपूर्णांक)   - P3[6] (microcontroller)
 *  GPIO[10]  - STROBE (xpoपूर्णांक)  - P3[7] (microcontroller)
 *  GPINTR    -                  - P3[4] (microcontroller)
 *
 * The microcontroller is a 80C32 like. It should be possible to change xpoपूर्णांक
 * configuration either directly (as we are करोing) or using the microcontroller
 * which is also wired to I2C पूर्णांकerface. I have no further info on the
 * microcontroller features, one would need to disassembly the firmware.
 * note: the venकरोr refused to give any inक्रमmation on this product, all
 *       that stuff was found using a mulसमयter! :)
 */
अटल व्योम rv605_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अटल स्थिर u8 muxgpio[] = अणु 0x3, 0x1, 0x2, 0x4, 0xf, 0x7, 0xe, 0x0,
				      0xd, 0xb, 0xc, 0x6, 0x9, 0x5, 0x8, 0xa पूर्ण;

	gpio_bits(0x07f, muxgpio[input]);

	/* reset all connections */
	gpio_bits(0x200,0x200);
	mdelay(1);
	gpio_bits(0x200,0x000);
	mdelay(1);

	/* create a new connection */
	gpio_bits(0x480,0x480);
	mdelay(1);
	gpio_bits(0x480,0x080);
	mdelay(1);
पूर्ण

/* Tibet Systems 'Progress DVR' CS16 muxsel helper [Chris Fanning]
 *
 * The CS16 (available on eBay cheap) is a PCI board with four Fusion
 * 878A chips, a PCI bridge, an Aपंचांगel microcontroller, four sync separator
 * chips, ten eight input analog multiplexors, a not chip and a few
 * other components.
 *
 * 16 inमाला_दो on a secondary bracket are provided and can be selected
 * from each of the four capture chips.  Two of the eight input
 * multiplexors are used to select from any of the 16 input संकेतs.
 *
 * Unsupported hardware capabilities:
 *  . A video output monitor on the secondary bracket can be selected from
 *    one of the 878A chips.
 *  . Another passthrough but I haven't spent any समय investigating it.
 *  . Digital I/O (logic level connected to GPIO) is available from an
 *    onboard header.
 *
 * The on chip input mux should always be set to 2.
 * GPIO[16:19] - Video input selection
 * GPIO[0:3]   - Video output monitor select (only available from one 878A)
 * GPIO[?:?]   - Digital I/O.
 *
 * There is an ATMEL microcontroller with an 8031 core on board.  I have not
 * determined what function (अगर any) it provides.  With the microcontroller
 * and sync separator chips a guess is that it might have to करो with video
 * चयनing and maybe some digital I/O.
 */
अटल व्योम tibetCS16_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	/* video mux */
	gpio_bits(0x0f0000, input << 16);
पूर्ण

अटल व्योम tibetCS16_init(काष्ठा bttv *btv)
अणु
	/* enable gpio bits, mask obtained via btSpy */
	gpio_inout(0xffffff, 0x0f7fff);
	gpio_ग_लिखो(0x0f7fff);
पूर्ण

/*
 * The following routines क्रम the Kodicom-4400r get a little mind-twisting.
 * There is a "master" controller and three "slave" controllers, together
 * an analog चयन which connects any of 16 cameras to any of the BT87A's.
 * The analog चयन is controlled by the "master", but the detection order
 * of the four BT878A chips is in an order which I just करोn't understand.
 * The "master" is actually the second controller to be detected.  The
 * logic on the board uses logical numbers क्रम the 4 controllers, but
 * those numbers are dअगरferent from the detection sequence.  When working
 * with the analog चयन, we need to "map" from the detection sequence
 * over to the board's logical controller number.  This mapping sequence
 * is अणु3, 0, 2, 1पूर्ण, i.e. the first controller to be detected is logical
 * unit 3, the second (which is the master) is logical unit 0, etc.
 * We need to मुख्यtain the status of the analog चयन (which of the 16
 * cameras is connected to which of the 4 controllers) in sw_status array.
 */

/*
 * First a routine to set the analog चयन, which controls which camera
 * is routed to which controller.  The चयन comprises an X-address
 * (gpio bits 0-3, representing the camera, ranging from 0-15), and a
 * Y-address (gpio bits 4-6, representing the controller, ranging from 0-3).
 * A data value (gpio bit 7) of '1' enables the switch, and '0' disables
 * the चयन.  A STROBE bit (gpio bit 8) latches the data value पूर्णांकo the
 * specअगरied address.  The idea is to set the address and data, then bring
 * STROBE high, and finally bring STROBE back to low.
 */
अटल व्योम kodicom4400r_ग_लिखो(काष्ठा bttv *btv,
			       अचिन्हित अक्षर xaddr,
			       अचिन्हित अक्षर yaddr,
			       अचिन्हित अक्षर data) अणु
	अचिन्हित पूर्णांक udata;

	udata = (data << 7) | ((yaddr&3) << 4) | (xaddr&0xf);
	gpio_bits(0x1ff, udata);		/* ग_लिखो ADDR and DAT */
	gpio_bits(0x1ff, udata | (1 << 8));	/* strobe high */
	gpio_bits(0x1ff, udata);		/* strobe low */
पूर्ण

/*
 * Next the mux select.  Both the "master" and "slave" 'cards' (controllers)
 * use this routine.  The routine finds the "master" क्रम the card, maps
 * the controller number from the detected position over to the logical
 * number, ग_लिखोs the appropriate data to the analog चयन, and housekeeps
 * the local copy of the चयन inक्रमmation.  The parameter 'input' is the
 * requested camera number (0 - 15).
 */
अटल व्योम kodicom4400r_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	पूर्णांक xaddr, yaddr;
	काष्ठा bttv *mctlr;
	अटल अचिन्हित अक्षर map[4] = अणु3, 0, 2, 1पूर्ण;

	mctlr = master[btv->c.nr];
	अगर (mctlr == शून्य) अणु	/* ignore अगर master not yet detected */
		वापस;
	पूर्ण
	yaddr = (btv->c.nr - mctlr->c.nr + 1) & 3; /* the '&' is क्रम safety */
	yaddr = map[yaddr];
	xaddr = input & 0xf;
	/* Check अगर the controller/camera pair has changed, अन्यथा ignore */
	अगर (mctlr->sw_status[yaddr] != xaddr)
	अणु
		/* "open" the old चयन, "close" the new one, save the new */
		kodicom4400r_ग_लिखो(mctlr, mctlr->sw_status[yaddr], yaddr, 0);
		mctlr->sw_status[yaddr] = xaddr;
		kodicom4400r_ग_लिखो(mctlr, xaddr, yaddr, 1);
	पूर्ण
पूर्ण

/*
 * During initialisation, we need to reset the analog चयन.  We
 * also preset the चयन to map the 4 connectors on the card to the
 * *user's* (see above description of kodicom4400r_muxsel) channels
 * 0 through 3
 */
अटल व्योम kodicom4400r_init(काष्ठा bttv *btv)
अणु
	पूर्णांक ix;

	gpio_inout(0x0003ff, 0x0003ff);
	gpio_ग_लिखो(1 << 9);	/* reset MUX */
	gpio_ग_लिखो(0);
	/* Preset camera 0 to the 4 controllers */
	क्रम (ix = 0; ix < 4; ix++) अणु
		btv->sw_status[ix] = ix;
		kodicom4400r_ग_लिखो(btv, ix, ix, 1);
	पूर्ण
	/*
	 * Since this is the "master", we need to set up the
	 * other three controller chips' poपूर्णांकers to this काष्ठाure
	 * क्रम later use in the muxsel routine.
	 */
	अगर ((btv->c.nr<1) || (btv->c.nr>BTTV_MAX-3))
	    वापस;
	master[btv->c.nr-1] = btv;
	master[btv->c.nr]   = btv;
	master[btv->c.nr+1] = btv;
	master[btv->c.nr+2] = btv;
पूर्ण

/* The Gअक्रमtec X-Guard framegrabber card uses two Dual 4-channel
 * video multiplexers to provide up to 16 video inमाला_दो. These
 * multiplexers are controlled by the lower 8 GPIO pins of the
 * bt878. The multiplexers probably Pericom PI5V331Q or similar.

 * xxx0 is pin xxx of multiplexer U5,
 * yyy1 is pin yyy of multiplexer U2
 */
#घोषणा ENA0    0x01
#घोषणा ENB0    0x02
#घोषणा ENA1    0x04
#घोषणा ENB1    0x08

#घोषणा IN10    0x10
#घोषणा IN00    0x20
#घोषणा IN11    0x40
#घोषणा IN01    0x80

अटल व्योम xguard_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अटल स्थिर पूर्णांक masks[] = अणु
		ENB0, ENB0|IN00, ENB0|IN10, ENB0|IN00|IN10,
		ENA0, ENA0|IN00, ENA0|IN10, ENA0|IN00|IN10,
		ENB1, ENB1|IN01, ENB1|IN11, ENB1|IN01|IN11,
		ENA1, ENA1|IN01, ENA1|IN11, ENA1|IN01|IN11,
	पूर्ण;
	gpio_ग_लिखो(masks[input%16]);
पूर्ण
अटल व्योम picolo_tetra_init(काष्ठा bttv *btv)
अणु
	/*This is the video input redirection functionality : I DID NOT USE IT. */
	btग_लिखो (0x08<<16,BT848_GPIO_DATA);/*GPIO[19] [==> 4053 B+C] set to 1 */
	btग_लिखो (0x04<<16,BT848_GPIO_DATA);/*GPIO[18] [==> 4053 A]  set to 1*/
पूर्ण
अटल व्योम picolo_tetra_muxsel (काष्ठा bttv* btv, अचिन्हित पूर्णांक input)
अणु

	dprपूर्णांकk("%d : picolo_tetra_muxsel =>  input = %d\n", btv->c.nr, input);
	/*Just set the right path in the analog multiplexers : channel 1 -> 4 ==> Analog Mux ==> MUX0*/
	/*GPIO[20]&GPIO[21] used to choose the right input*/
	btग_लिखो (input<<20,BT848_GPIO_DATA);

पूर्ण

/*
 * ivc120_muxsel [Added by Alan Garfield <alan@fromorbit.com>]
 *
 * The IVC120G security card has 4 i2c controlled TDA8540 matrix
 * चयनers to provide 16 channels to MUX0. The TDA8540's have
 * 4 independent outमाला_दो and as such the IVC120G also has the
 * optional "Monitor Out" bus. This allows the card to be looking
 * at one input जबतक the monitor is looking at another.
 *
 * Since I've couldn't be bothered figuring out how to add an
 * independent muxsel क्रम the monitor bus, I've just set it to
 * whatever the card is looking at.
 *
 *  OUT0 of the TDA8540's is connected to MUX0         (0x03)
 *  OUT1 of the TDA8540's is connected to "Monitor Out"        (0x0C)
 *
 *  TDA8540_ALT3 IN0-3 = Channel 13 - 16       (0x03)
 *  TDA8540_ALT4 IN0-3 = Channel 1 - 4         (0x03)
 *  TDA8540_ALT5 IN0-3 = Channel 5 - 8         (0x03)
 *  TDA8540_ALT6 IN0-3 = Channel 9 - 12                (0x03)
 *
 */

/* All 7 possible sub-ids क्रम the TDA8540 Matrix Switcher */
#घोषणा I2C_TDA8540        0x90
#घोषणा I2C_TDA8540_ALT1   0x92
#घोषणा I2C_TDA8540_ALT2   0x94
#घोषणा I2C_TDA8540_ALT3   0x96
#घोषणा I2C_TDA8540_ALT4   0x98
#घोषणा I2C_TDA8540_ALT5   0x9a
#घोषणा I2C_TDA8540_ALT6   0x9c

अटल व्योम ivc120_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	/* Simple maths */
	पूर्णांक key = input % 4;
	पूर्णांक matrix = input / 4;

	dprपूर्णांकk("%d: ivc120_muxsel: Input - %02d | TDA - %02d | In - %02d\n",
		btv->c.nr, input, matrix, key);

	/* Handles the input selection on the TDA8540's */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT3, 0x00,
		      ((matrix == 3) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT4, 0x00,
		      ((matrix == 0) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT5, 0x00,
		      ((matrix == 1) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWrite(btv, I2C_TDA8540_ALT6, 0x00,
		      ((matrix == 2) ? (key | key << 2) : 0x00), 1);

	/* Handles the output enables on the TDA8540's */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT3, 0x02,
		      ((matrix == 3) ? 0x03 : 0x00), 1);  /* 13 - 16 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT4, 0x02,
		      ((matrix == 0) ? 0x03 : 0x00), 1);  /* 1-4 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT5, 0x02,
		      ((matrix == 1) ? 0x03 : 0x00), 1);  /* 5-8 */
	bttv_I2CWrite(btv, I2C_TDA8540_ALT6, 0x02,
		      ((matrix == 2) ? 0x03 : 0x00), 1);  /* 9-12 */

	/* 878's MUX0 is alपढ़ोy selected क्रम input via muxsel values */
पूर्ण


/* PXC200 muxsel helper
 * luke@syseng.anu.edu.au
 * another transplant
 * from Alessandro Rubini (rubini@linux.it)
 *
 * There are 4 kinds of cards:
 * PXC200L which is bt848
 * PXC200F which is bt848 with PIC controlling mux
 * PXC200AL which is bt878
 * PXC200AF which is bt878 with PIC controlling mux
 */
#घोषणा PX_CFG_PXC200F 0x01
#घोषणा PX_FLAG_PXC200A  0x00001000 /* a pxc200A is bt-878 based */
#घोषणा PX_I2C_PIC       0x0f
#घोषणा PX_PXC200A_CARDID 0x200a1295
#घोषणा PX_I2C_CMD_CFG   0x00

अटल व्योम PXC200_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	पूर्णांक rc;
	दीर्घ mux;
	पूर्णांक biपंचांगask;
	अचिन्हित अक्षर buf[2];

	/* Read PIC config to determine अगर this is a PXC200F */
	/* PX_I2C_CMD_CFG*/
	buf[0]=0;
	buf[1]=0;
	rc=bttv_I2CWrite(btv,(PX_I2C_PIC<<1),buf[0],buf[1],1);
	अगर (rc) अणु
		pr_debug("%d: PXC200_muxsel: pic cfg write failed:%d\n",
			 btv->c.nr, rc);
	  /* not PXC ? करो nothing */
		वापस;
	पूर्ण

	rc=bttv_I2CRead(btv,(PX_I2C_PIC<<1),शून्य);
	अगर (!(rc & PX_CFG_PXC200F)) अणु
		pr_debug("%d: PXC200_muxsel: not PXC200F rc:%d\n",
			 btv->c.nr, rc);
		वापस;
	पूर्ण


	/* The multiplexer in the 200F is handled by the GPIO port */
	/* get correct mapping between inमाला_दो  */
	/*  mux = bttv_tvcards[btv->type].muxsel[input] & 3; */
	/* ** not needed!?   */
	mux = input;

	/* make sure output pins are enabled */
	/* biपंचांगask=0x30f; */
	biपंचांगask=0x302;
	/* check whether we have a PXC200A */
	अगर (btv->cardid == PX_PXC200A_CARDID)  अणु
	   biपंचांगask ^= 0x180; /* use 7 and 9, not 8 and 9 */
	   biपंचांगask |= 7<<4; /* the DAC */
	पूर्ण
	btग_लिखो(biपंचांगask, BT848_GPIO_OUT_EN);

	biपंचांगask = btपढ़ो(BT848_GPIO_DATA);
	अगर (btv->cardid == PX_PXC200A_CARDID)
	  biपंचांगask = (biपंचांगask & ~0x280) | ((mux & 2) << 8) | ((mux & 1) << 7);
	अन्यथा /* older device */
	  biपंचांगask = (biपंचांगask & ~0x300) | ((mux & 3) << 8);
	btग_लिखो(biपंचांगask,BT848_GPIO_DATA);

	/*
	 * Was "to be safe, set the bt848 to input 0"
	 * Actually, since it's ok at load समय, better not messing
	 * with these bits (on PXC200AF you need to set mux 2 here)
	 *
	 * needed because bttv-driver sets mux beक्रमe calling this function
	 */
	अगर (btv->cardid == PX_PXC200A_CARDID)
	  btaor(2<<5, ~BT848_IFORM_MUXSEL, BT848_IFORM);
	अन्यथा /* older device */
	  btand(~BT848_IFORM_MUXSEL,BT848_IFORM);

	pr_debug("%d: setting input channel to:%d\n", btv->c.nr, (पूर्णांक)mux);
पूर्ण

अटल व्योम phytec_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	अचिन्हित पूर्णांक mux = input % 4;

	अगर (input == btv->svhs)
		mux = 0;

	gpio_bits(0x3, mux);
पूर्ण

/*
 * GeoVision GV-800(S) functions
 * Bruno Christo <bchristo@inf.ufsm.br>
*/

/* This is a function to control the analog चयन, which determines which
 * camera is routed to which controller.  The चयन comprises an X-address
 * (gpio bits 0-3, representing the camera, ranging from 0-15), and a
 * Y-address (gpio bits 4-6, representing the controller, ranging from 0-3).
 * A data value (gpio bit 18) of '1' enables the switch, and '0' disables
 * the चयन.  A STROBE bit (gpio bit 17) latches the data value पूर्णांकo the
 * specअगरied address. There is also a chip select (gpio bit 16).
 * The idea is to set the address and chip select together, bring
 * STROBE high, ग_लिखो the data, and finally bring STROBE back to low.
 */
अटल व्योम gv800s_ग_लिखो(काष्ठा bttv *btv,
			 अचिन्हित अक्षर xaddr,
			 अचिन्हित अक्षर yaddr,
			 अचिन्हित अक्षर data) अणु
	/* On the "master" 878A:
	* GPIO bits 0-9 are used क्रम the analog चयन:
	*   00 - 03:	camera selector
	*   04 - 06:	878A (controller) selector
	*   16:		cselect
	*   17:		strobe
	*   18:		data (1->on, 0->off)
	*   19:		reset
	*/
	स्थिर u32 ADDRESS = ((xaddr&0xf) | (yaddr&3)<<4);
	स्थिर u32 CSELECT = 1<<16;
	स्थिर u32 STROBE = 1<<17;
	स्थिर u32 DATA = data<<18;

	gpio_bits(0x1007f, ADDRESS | CSELECT);	/* ग_लिखो ADDRESS and CSELECT */
	gpio_bits(0x20000, STROBE);		/* STROBE high */
	gpio_bits(0x40000, DATA);		/* ग_लिखो DATA */
	gpio_bits(0x20000, ~STROBE);		/* STROBE low */
पूर्ण

/*
 * GeoVision GV-800(S) muxsel
 *
 * Each of the 4 cards (controllers) use this function.
 * The controller using this function selects the input through the GPIO pins
 * of the "master" card. A poपूर्णांकer to this card is stored in master[btv->c.nr].
 *
 * The parameter 'input' is the requested camera number (0-4) on the controller.
 * The map array has the address of each input. Note that the addresses in the
 * array are in the sequence the original GeoVision driver uses, that is, set
 * every controller to input 0, then to input 1, 2, 3, repeat. This means that
 * the physical "camera 1" connector corresponds to controller 0 input 0,
 * "camera 2" corresponds to controller 1 input 0, and so on.
 *
 * After getting the input address, the function then ग_लिखोs the appropriate
 * data to the analog चयन, and housekeeps the local copy of the चयन
 * inक्रमmation.
 */
अटल व्योम gv800s_muxsel(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	काष्ठा bttv *mctlr;
	पूर्णांक xaddr, yaddr;
	अटल अचिन्हित पूर्णांक map[4][4] = अणु अणु 0x0, 0x4, 0xa, 0x6 पूर्ण,
					  अणु 0x1, 0x5, 0xb, 0x7 पूर्ण,
					  अणु 0x2, 0x8, 0xc, 0xe पूर्ण,
					  अणु 0x3, 0x9, 0xd, 0xf पूर्ण पूर्ण;
	input = input%4;
	mctlr = master[btv->c.nr];
	अगर (mctlr == शून्य) अणु
		/* करो nothing until the "master" is detected */
		वापस;
	पूर्ण
	yaddr = (btv->c.nr - mctlr->c.nr) & 3;
	xaddr = map[yaddr][input] & 0xf;

	/* Check अगर the controller/camera pair has changed, ignore otherwise */
	अगर (mctlr->sw_status[yaddr] != xaddr) अणु
		/* disable the old चयन, enable the new one and save status */
		gv800s_ग_लिखो(mctlr, mctlr->sw_status[yaddr], yaddr, 0);
		mctlr->sw_status[yaddr] = xaddr;
		gv800s_ग_लिखो(mctlr, xaddr, yaddr, 1);
	पूर्ण
पूर्ण

/* GeoVision GV-800(S) "master" chip init */
अटल व्योम gv800s_init(काष्ठा bttv *btv)
अणु
	पूर्णांक ix;

	gpio_inout(0xf107f, 0xf107f);
	gpio_ग_लिखो(1<<19); /* reset the analog MUX */
	gpio_ग_लिखो(0);

	/* Preset camera 0 to the 4 controllers */
	क्रम (ix = 0; ix < 4; ix++) अणु
		btv->sw_status[ix] = ix;
		gv800s_ग_लिखो(btv, ix, ix, 1);
	पूर्ण

	/* Inमाला_दो on the "master" controller need this brightness fix */
	bttv_I2CWrite(btv, 0x18, 0x5, 0x90, 1);

	अगर (btv->c.nr > BTTV_MAX-4)
		वापस;
	/*
	 * Store the "master" controller poपूर्णांकer in the master
	 * array क्रम later use in the muxsel function.
	 */
	master[btv->c.nr]   = btv;
	master[btv->c.nr+1] = btv;
	master[btv->c.nr+2] = btv;
	master[btv->c.nr+3] = btv;
पूर्ण

/* ----------------------------------------------------------------------- */
/* motherboard chipset specअगरic stuff                                      */

व्योम __init bttv_check_chipset(व्योम)
अणु
	पूर्णांक pcipci_fail = 0;
	काष्ठा pci_dev *dev = शून्य;

	अगर (pci_pci_problems & (PCIPCI_FAIL|PCIAGP_FAIL))	/* should check अगर target is AGP */
		pcipci_fail = 1;
	अगर (pci_pci_problems & (PCIPCI_TRITON|PCIPCI_NATOMA|PCIPCI_VIAETBF))
		triton1 = 1;
	अगर (pci_pci_problems & PCIPCI_VSFX)
		vsfx = 1;
#अगर_घोषित PCIPCI_ALIMAGIK
	अगर (pci_pci_problems & PCIPCI_ALIMAGIK)
		latency = 0x0A;
#पूर्ण_अगर


	/* prपूर्णांक warnings about any quirks found */
	अगर (triton1)
		pr_info("Host bridge needs ETBF enabled\n");
	अगर (vsfx)
		pr_info("Host bridge needs VSFX enabled\n");
	अगर (pcipci_fail) अणु
		pr_info("bttv and your chipset may not work together\n");
		अगर (!no_overlay) अणु
			pr_info("overlay will be disabled\n");
			no_overlay = 1;
		पूर्ण अन्यथा अणु
			pr_info("overlay forced. Use this option at your own risk.\n");
		पूर्ण
	पूर्ण
	अगर (UNSET != latency)
		pr_info("pci latency fixup [%d]\n", latency);
	जबतक ((dev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_82441, dev))) अणु
		अचिन्हित अक्षर b;
		pci_पढ़ो_config_byte(dev, 0x53, &b);
		अगर (bttv_debug)
			pr_info("Host bridge: 82441FX Natoma, bufcon=0x%02x\n",
				b);
	पूर्ण
पूर्ण

पूर्णांक bttv_handle_chipset(काष्ठा bttv *btv)
अणु
	अचिन्हित अक्षर command;

	अगर (!triton1 && !vsfx && UNSET == latency)
		वापस 0;

	अगर (bttv_verbose) अणु
		अगर (triton1)
			pr_info("%d: enabling ETBF (430FX/VP3 compatibility)\n",
				btv->c.nr);
		अगर (vsfx && btv->id >= 878)
			pr_info("%d: enabling VSFX\n", btv->c.nr);
		अगर (UNSET != latency)
			pr_info("%d: setting pci timer to %d\n",
				btv->c.nr, latency);
	पूर्ण

	अगर (btv->id < 878) अणु
		/* bt848 (mis)uses a bit in the irq mask क्रम etbf */
		अगर (triton1)
			btv->triton1 = BT848_INT_ETBF;
	पूर्ण अन्यथा अणु
		/* bt878 has a bit in the pci config space क्रम it */
		pci_पढ़ो_config_byte(btv->c.pci, BT878_DEVCTRL, &command);
		अगर (triton1)
			command |= BT878_EN_TBFX;
		अगर (vsfx)
			command |= BT878_EN_VSFX;
		pci_ग_लिखो_config_byte(btv->c.pci, BT878_DEVCTRL, command);
	पूर्ण
	अगर (UNSET != latency)
		pci_ग_लिखो_config_byte(btv->c.pci, PCI_LATENCY_TIMER, latency);
	वापस 0;
पूर्ण
