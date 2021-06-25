<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PRO]/550/[M]65x/[M]661[F|M]X/740/[M]741[GX]/330/[M]76x[GX],
 * XGI V3XT/V5/V8, Z7
 * frame buffer driver क्रम Linux kernels >=2.4.14 and >=2.6.3
 *
 * Copyright (C) 2001-2005 Thomas Winischhofer, Vienna, Austria.
 */

#अगर_अघोषित _SIS_H_
#घोषणा _SIS_H_

#समावेश <video/sisfb.h>

#समावेश "vgatypes.h"
#समावेश "vstruct.h"

#घोषणा VER_MAJOR		1
#घोषणा VER_MINOR		8
#घोषणा VER_LEVEL		9

#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_COMPAT
#घोषणा SIS_NEW_CONFIG_COMPAT
#पूर्ण_अगर	/* CONFIG_COMPAT */

#अघोषित SISFBDEBUG

#अगर_घोषित SISFBDEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__ , ## args)
#घोषणा TWDEBUG(x) prपूर्णांकk(KERN_INFO x "\n");
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#घोषणा TWDEBUG(x)
#पूर्ण_अगर

#घोषणा SISFAIL(x) करो अणु prपूर्णांकk(x "\n"); वापस -EINVAL; पूर्ण जबतक(0)

/* To be included in pci_ids.h */
#अगर_अघोषित PCI_DEVICE_ID_SI_650_VGA
#घोषणा PCI_DEVICE_ID_SI_650_VGA	0x6325
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_650
#घोषणा PCI_DEVICE_ID_SI_650		0x0650
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_651
#घोषणा PCI_DEVICE_ID_SI_651		0x0651
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_740
#घोषणा PCI_DEVICE_ID_SI_740		0x0740
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_330
#घोषणा PCI_DEVICE_ID_SI_330		0x0330
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_660_VGA
#घोषणा PCI_DEVICE_ID_SI_660_VGA	0x6330
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_661
#घोषणा PCI_DEVICE_ID_SI_661		0x0661
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_741
#घोषणा PCI_DEVICE_ID_SI_741		0x0741
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_660
#घोषणा PCI_DEVICE_ID_SI_660		0x0660
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_760
#घोषणा PCI_DEVICE_ID_SI_760		0x0760
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SI_761
#घोषणा PCI_DEVICE_ID_SI_761		0x0761
#पूर्ण_अगर

#अगर_अघोषित PCI_VENDOR_ID_XGI
#घोषणा PCI_VENDOR_ID_XGI		0x18ca
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_XGI_20
#घोषणा PCI_DEVICE_ID_XGI_20		0x0020
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_XGI_40
#घोषणा PCI_DEVICE_ID_XGI_40		0x0040
#पूर्ण_अगर

/* To be included in fb.h */
#अगर_अघोषित FB_ACCEL_SIS_GLAMOUR_2
#घोषणा FB_ACCEL_SIS_GLAMOUR_2	40	/* SiS 315, 65x, 740, 661, 741  */
#पूर्ण_अगर
#अगर_अघोषित FB_ACCEL_SIS_XABRE
#घोषणा FB_ACCEL_SIS_XABRE	41	/* SiS 330 ("Xabre"), 76x 	*/
#पूर्ण_अगर
#अगर_अघोषित FB_ACCEL_XGI_VOLARI_V
#घोषणा FB_ACCEL_XGI_VOLARI_V	47	/* XGI Volari Vx (V3XT, V5, V8)	*/
#पूर्ण_अगर
#अगर_अघोषित FB_ACCEL_XGI_VOLARI_Z
#घोषणा FB_ACCEL_XGI_VOLARI_Z	48	/* XGI Volari Z7		*/
#पूर्ण_अगर

/* ivideo->caps */
#घोषणा HW_CURSOR_CAP		0x80
#घोषणा TURBO_QUEUE_CAP		0x40
#घोषणा AGP_CMD_QUEUE_CAP	0x20
#घोषणा VM_CMD_QUEUE_CAP	0x10
#घोषणा MMIO_CMD_QUEUE_CAP	0x08

/* For 300 series */
#घोषणा TURBO_QUEUE_AREA_SIZE	(512 * 1024)	/* 512K */
#घोषणा HW_CURSOR_AREA_SIZE_300	4096		/* 4K */

/* For 315/Xabre series */
#घोषणा COMMAND_QUEUE_AREA_SIZE	(512 * 1024)	/* 512K */
#घोषणा COMMAND_QUEUE_AREA_SIZE_Z7 (128 * 1024)	/* 128k क्रम XGI Z7 */
#घोषणा HW_CURSOR_AREA_SIZE_315	16384		/* 16K */
#घोषणा COMMAND_QUEUE_THRESHOLD	0x1F

#घोषणा SIS_OH_ALLOC_SIZE	4000
#घोषणा SENTINEL		0x7fffffff

#घोषणा SEQ_ADR			0x14
#घोषणा SEQ_DATA		0x15
#घोषणा DAC_ADR			0x18
#घोषणा DAC_DATA		0x19
#घोषणा CRTC_ADR		0x24
#घोषणा CRTC_DATA		0x25
#घोषणा DAC2_ADR		(0x16-0x30)
#घोषणा DAC2_DATA		(0x17-0x30)
#घोषणा VB_PART1_ADR		(0x04-0x30)
#घोषणा VB_PART1_DATA		(0x05-0x30)
#घोषणा VB_PART2_ADR		(0x10-0x30)
#घोषणा VB_PART2_DATA		(0x11-0x30)
#घोषणा VB_PART3_ADR		(0x12-0x30)
#घोषणा VB_PART3_DATA		(0x13-0x30)
#घोषणा VB_PART4_ADR		(0x14-0x30)
#घोषणा VB_PART4_DATA		(0x15-0x30)

#घोषणा SISSR			ivideo->SiS_Pr.SiS_P3c4
#घोषणा SISCR			ivideo->SiS_Pr.SiS_P3d4
#घोषणा SISDACA			ivideo->SiS_Pr.SiS_P3c8
#घोषणा SISDACD			ivideo->SiS_Pr.SiS_P3c9
#घोषणा SISPART1		ivideo->SiS_Pr.SiS_Part1Port
#घोषणा SISPART2		ivideo->SiS_Pr.SiS_Part2Port
#घोषणा SISPART3		ivideo->SiS_Pr.SiS_Part3Port
#घोषणा SISPART4		ivideo->SiS_Pr.SiS_Part4Port
#घोषणा SISPART5		ivideo->SiS_Pr.SiS_Part5Port
#घोषणा SISDAC2A		SISPART5
#घोषणा SISDAC2D		(SISPART5 + 1)
#घोषणा SISMISCR		(ivideo->SiS_Pr.RelIO + 0x1c)
#घोषणा SISMISCW		ivideo->SiS_Pr.SiS_P3c2
#घोषणा SISINPSTAT		(ivideo->SiS_Pr.RelIO + 0x2a)
#घोषणा SISPEL			ivideo->SiS_Pr.SiS_P3c6
#घोषणा SISVGAENABLE		(ivideo->SiS_Pr.RelIO + 0x13)
#घोषणा SISVID			(ivideo->SiS_Pr.RelIO + 0x02 - 0x30)
#घोषणा SISCAP			(ivideo->SiS_Pr.RelIO + 0x00 - 0x30)

#घोषणा IND_SIS_PASSWORD		0x05  /* SRs */
#घोषणा IND_SIS_COLOR_MODE		0x06
#घोषणा IND_SIS_RAMDAC_CONTROL		0x07
#घोषणा IND_SIS_DRAM_SIZE		0x14
#घोषणा IND_SIS_MODULE_ENABLE		0x1E
#घोषणा IND_SIS_PCI_ADDRESS_SET		0x20
#घोषणा IND_SIS_TURBOQUEUE_ADR		0x26
#घोषणा IND_SIS_TURBOQUEUE_SET		0x27
#घोषणा IND_SIS_POWER_ON_TRAP		0x38
#घोषणा IND_SIS_POWER_ON_TRAP2		0x39
#घोषणा IND_SIS_CMDQUEUE_SET		0x26
#घोषणा IND_SIS_CMDQUEUE_THRESHOLD	0x27

#घोषणा IND_SIS_AGP_IO_PAD	0x48

#घोषणा SIS_CRT2_WENABLE_300	0x24  /* Part1 */
#घोषणा SIS_CRT2_WENABLE_315	0x2F

#घोषणा SIS_PASSWORD		0x86  /* SR05 */

#घोषणा SIS_INTERLACED_MODE	0x20  /* SR06 */
#घोषणा SIS_8BPP_COLOR_MODE	0x0
#घोषणा SIS_15BPP_COLOR_MODE	0x1
#घोषणा SIS_16BPP_COLOR_MODE	0x2
#घोषणा SIS_32BPP_COLOR_MODE	0x4

#घोषणा SIS_ENABLE_2D		0x40  /* SR1E */

#घोषणा SIS_MEM_MAP_IO_ENABLE	0x01  /* SR20 */
#घोषणा SIS_PCI_ADDR_ENABLE	0x80

#घोषणा SIS_AGP_CMDQUEUE_ENABLE		0x80  /* 315/330/340 series SR26 */
#घोषणा SIS_VRAM_CMDQUEUE_ENABLE	0x40
#घोषणा SIS_MMIO_CMD_ENABLE		0x20
#घोषणा SIS_CMD_QUEUE_SIZE_512k		0x00
#घोषणा SIS_CMD_QUEUE_SIZE_1M		0x04
#घोषणा SIS_CMD_QUEUE_SIZE_2M		0x08
#घोषणा SIS_CMD_QUEUE_SIZE_4M		0x0C
#घोषणा SIS_CMD_QUEUE_RESET		0x01
#घोषणा SIS_CMD_AUTO_CORR		0x02

#घोषणा SIS_CMD_QUEUE_SIZE_Z7_64k	0x00 /* XGI Z7 */
#घोषणा SIS_CMD_QUEUE_SIZE_Z7_128k	0x04

#घोषणा SIS_SIMULTANEOUS_VIEW_ENABLE	0x01  /* CR30 */
#घोषणा SIS_MODE_SELECT_CRT2		0x02
#घोषणा SIS_VB_OUTPUT_COMPOSITE		0x04
#घोषणा SIS_VB_OUTPUT_SVIDEO		0x08
#घोषणा SIS_VB_OUTPUT_SCART		0x10
#घोषणा SIS_VB_OUTPUT_LCD		0x20
#घोषणा SIS_VB_OUTPUT_CRT2		0x40
#घोषणा SIS_VB_OUTPUT_HIVISION		0x80

#घोषणा SIS_VB_OUTPUT_DISABLE	0x20  /* CR31 */
#घोषणा SIS_DRIVER_MODE		0x40

#घोषणा SIS_VB_COMPOSITE	0x01  /* CR32 */
#घोषणा SIS_VB_SVIDEO		0x02
#घोषणा SIS_VB_SCART		0x04
#घोषणा SIS_VB_LCD		0x08
#घोषणा SIS_VB_CRT2		0x10
#घोषणा SIS_CRT1		0x20
#घोषणा SIS_VB_HIVISION		0x40
#घोषणा SIS_VB_YPBPR		0x80
#घोषणा SIS_VB_TV		(SIS_VB_COMPOSITE | SIS_VB_SVIDEO | \
				SIS_VB_SCART | SIS_VB_HIVISION | SIS_VB_YPBPR)

#घोषणा SIS_EXTERNAL_CHIP_MASK			0x0E  /* CR37 (< SiS 660) */
#घोषणा SIS_EXTERNAL_CHIP_SIS301		0x01  /* in CR37 << 1 ! */
#घोषणा SIS_EXTERNAL_CHIP_LVDS			0x02
#घोषणा SIS_EXTERNAL_CHIP_TRUMPION		0x03
#घोषणा SIS_EXTERNAL_CHIP_LVDS_CHRONTEL		0x04
#घोषणा SIS_EXTERNAL_CHIP_CHRONTEL		0x05
#घोषणा SIS310_EXTERNAL_CHIP_LVDS		0x02
#घोषणा SIS310_EXTERNAL_CHIP_LVDS_CHRONTEL	0x03

#घोषणा SIS_AGP_2X		0x20  /* CR48 */

/* vbflags, निजी entries (others in sisfb.h) */
#घोषणा VB_CONEXANT		0x00000800	/* 661 series only */
#घोषणा VB_TRUMPION		VB_CONEXANT	/* 300 series only */
#घोषणा VB_302ELV		0x00004000
#घोषणा VB_301			0x00100000	/* Video bridge type */
#घोषणा VB_301B			0x00200000
#घोषणा VB_302B			0x00400000
#घोषणा VB_30xBDH		0x00800000	/* 30xB DH version (w/o LCD support) */
#घोषणा VB_LVDS			0x01000000
#घोषणा VB_CHRONTEL		0x02000000
#घोषणा VB_301LV		0x04000000
#घोषणा VB_302LV		0x08000000
#घोषणा VB_301C			0x10000000

#घोषणा VB_SISBRIDGE		(VB_301|VB_301B|VB_301C|VB_302B|VB_301LV|VB_302LV|VB_302ELV)
#घोषणा VB_VIDEOBRIDGE		(VB_SISBRIDGE | VB_LVDS | VB_CHRONTEL | VB_CONEXANT)

/* vbflags2 (अटल stuff only!) */
#घोषणा VB2_SISUMC		0x00000001
#घोषणा VB2_301			0x00000002	/* Video bridge type */
#घोषणा VB2_301B		0x00000004
#घोषणा VB2_301C		0x00000008
#घोषणा VB2_307T		0x00000010
#घोषणा VB2_302B		0x00000800
#घोषणा VB2_301LV		0x00001000
#घोषणा VB2_302LV		0x00002000
#घोषणा VB2_302ELV		0x00004000
#घोषणा VB2_307LV		0x00008000
#घोषणा VB2_30xBDH		0x08000000      /* 30xB DH version (w/o LCD support) */
#घोषणा VB2_CONEXANT		0x10000000
#घोषणा VB2_TRUMPION		0x20000000
#घोषणा VB2_LVDS		0x40000000
#घोषणा VB2_CHRONTEL		0x80000000

#घोषणा VB2_SISLVDSBRIDGE	(VB2_301LV | VB2_302LV | VB2_302ELV | VB2_307LV)
#घोषणा VB2_SISTMDSBRIDGE	(VB2_301   | VB2_301B  | VB2_301C   | VB2_302B | VB2_307T)
#घोषणा VB2_SISBRIDGE		(VB2_SISLVDSBRIDGE | VB2_SISTMDSBRIDGE)

#घोषणा VB2_SISTMDSLCDABRIDGE	(VB2_301C | VB2_307T)
#घोषणा VB2_SISLCDABRIDGE	(VB2_SISTMDSLCDABRIDGE | VB2_301LV | VB2_302LV | VB2_302ELV | VB2_307LV)

#घोषणा VB2_SISHIVISIONBRIDGE	(VB2_301  | VB2_301B | VB2_302B)
#घोषणा VB2_SISYPBPRBRIDGE	(VB2_301C | VB2_307T | VB2_SISLVDSBRIDGE)
#घोषणा VB2_SISYPBPRARBRIDGE	(VB2_301C | VB2_307T | VB2_307LV)
#घोषणा VB2_SISTAP4SCALER	(VB2_301C | VB2_307T | VB2_302ELV | VB2_307LV)
#घोषणा VB2_SISTVBRIDGE		(VB2_SISHIVISIONBRIDGE | VB2_SISYPBPRBRIDGE)

#घोषणा VB2_SISVGA2BRIDGE	(VB2_301 | VB2_301B | VB2_301C | VB2_302B | VB2_307T)

#घोषणा VB2_VIDEOBRIDGE		(VB2_SISBRIDGE | VB2_LVDS | VB2_CHRONTEL | VB2_CONEXANT)

#घोषणा VB2_30xB		(VB2_301B  | VB2_301C   | VB2_302B  | VB2_307T)
#घोषणा VB2_30xBLV		(VB2_30xB  | VB2_SISLVDSBRIDGE)
#घोषणा VB2_30xC		(VB2_301C  | VB2_307T)
#घोषणा VB2_30xCLV		(VB2_301C  | VB2_307T   | VB2_302ELV| VB2_307LV)
#घोषणा VB2_SISEMIBRIDGE	(VB2_302LV | VB2_302ELV | VB2_307LV)
#घोषणा VB2_LCD162MHZBRIDGE	(VB2_301C  | VB2_307T)
#घोषणा VB2_LCDOVER1280BRIDGE	(VB2_301C  | VB2_307T   | VB2_302LV | VB2_302ELV | VB2_307LV)
#घोषणा VB2_LCDOVER1600BRIDGE	(VB2_307T  | VB2_307LV)
#घोषणा VB2_RAMDAC202MHZBRIDGE	(VB2_301C  | VB2_307T)

/* I/O port access functions */

व्योम SiS_SetReg(SISIOADDRESS, u8, u8);
व्योम SiS_SetRegByte(SISIOADDRESS, u8);
व्योम SiS_SetRegShort(SISIOADDRESS, u16);
व्योम SiS_SetRegLong(SISIOADDRESS, u32);
व्योम SiS_SetRegANDOR(SISIOADDRESS, u8, u8, u8);
व्योम SiS_SetRegAND(SISIOADDRESS, u8, u8);
व्योम SiS_SetRegOR(SISIOADDRESS, u8, u8);
u8 SiS_GetReg(SISIOADDRESS, u8);
u8 SiS_GetRegByte(SISIOADDRESS);
u16 SiS_GetRegShort(SISIOADDRESS);
u32 SiS_GetRegLong(SISIOADDRESS);

/* Chrontel TV, DDC and DPMS functions */
/* from init.c */
bool		SiSInitPtr(काष्ठा SiS_Private *SiS_Pr);
अचिन्हित लघु	SiS_GetModeID_LCD(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, bool FSTN,
				अचिन्हित लघु CustomT, पूर्णांक LCDwith, पूर्णांक LCDheight,
				अचिन्हित पूर्णांक VBFlags2);
अचिन्हित लघु	SiS_GetModeID_TV(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, अचिन्हित पूर्णांक VBFlags2);
अचिन्हित लघु	SiS_GetModeID_VGA2(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, अचिन्हित पूर्णांक VBFlags2);

व्योम		SiS_DisplayOn(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiS_DisplayOff(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiSRegInit(काष्ठा SiS_Private *SiS_Pr, SISIOADDRESS BaseAddr);
व्योम		SiS_SetEnableDstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable);
व्योम		SiS_SetEnableFstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable);
अचिन्हित लघु	SiS_GetModeFlag(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
bool		SiSDetermineROMLayout661(काष्ठा SiS_Private *SiS_Pr);

bool		SiS_SearchModeID(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *ModeNo,
				अचिन्हित लघु *ModeIdIndex);
अचिन्हित लघु	SiS_GetModePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
अचिन्हित लघु  SiS_GetRefCRTVCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide);
अचिन्हित लघु  SiS_GetRefCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide);
अचिन्हित लघु	SiS_GetColorDepth(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
अचिन्हित लघु	SiS_GetOffset(काष्ठा SiS_Private *SiS_Pr,अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI);
#अगर_घोषित CONFIG_FB_SIS_300
व्योम		SiS_GetFIFOThresholdIndex300(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *idx1,
				अचिन्हित लघु *idx2);
अचिन्हित लघु	SiS_GetFIFOThresholdB300(अचिन्हित लघु idx1, अचिन्हित लघु idx2);
अचिन्हित लघु	SiS_GetLatencyFactor630(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु index);
#पूर्ण_अगर
व्योम		SiS_LoadDAC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex);
bool		SiSSetMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo);
व्योम		SiS_CalcCRRegisters(काष्ठा SiS_Private *SiS_Pr, पूर्णांक depth);
व्योम		SiS_CalcLCDACRT1Timing(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
व्योम		SiS_Generic_ConvertCRData(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *crdata, पूर्णांक xres,
				पूर्णांक yres, काष्ठा fb_var_screeninfo *var, bool ग_लिखोres);

/* From init301.c: */
बाह्य व्योम		SiS_GetVBInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex, पूर्णांक chkcrt2mode);
बाह्य व्योम		SiS_GetLCDResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य व्योम		SiS_SetYPbPr(काष्ठा SiS_Private *SiS_Pr);
बाह्य व्योम		SiS_SetTVMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य व्योम		SiS_UnLockCRT2(काष्ठा SiS_Private *SiS_Pr);
बाह्य व्योम		SiS_DisableBridge(काष्ठा SiS_Private *);
बाह्य bool		SiS_SetCRT2Group(काष्ठा SiS_Private *, अचिन्हित लघु);
बाह्य अचिन्हित लघु	SiS_GetRatePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य व्योम		SiS_WaitRetrace1(काष्ठा SiS_Private *SiS_Pr);
बाह्य अचिन्हित लघु	SiS_GetResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य अचिन्हित लघु	SiS_GetCH700x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempax);
बाह्य अचिन्हित लघु	SiS_GetVCLK2Ptr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI);
बाह्य bool		SiS_IsVAMode(काष्ठा SiS_Private *);
बाह्य bool		SiS_IsDualEdge(काष्ठा SiS_Private *);

#अगर_घोषित CONFIG_FB_SIS_300
बाह्य अचिन्हित पूर्णांक	sisfb_पढ़ो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
बाह्य व्योम		sisfb_ग_लिखो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg,
				अचिन्हित पूर्णांक val);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
बाह्य व्योम		sisfb_ग_लिखो_nbridge_pci_byte(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg,
				अचिन्हित अक्षर val);
बाह्य अचिन्हित पूर्णांक	sisfb_पढ़ो_mio_pci_word(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
#पूर्ण_अगर


/* MMIO access macros */
#घोषणा MMIO_IN8(base, offset)  पढ़ोb((base+offset))
#घोषणा MMIO_IN16(base, offset) पढ़ोw((base+offset))
#घोषणा MMIO_IN32(base, offset) पढ़ोl((base+offset))

#घोषणा MMIO_OUT8(base, offset, val)  ग_लिखोb(((u8)(val)), (base+offset))
#घोषणा MMIO_OUT16(base, offset, val) ग_लिखोw(((u16)(val)), (base+offset))
#घोषणा MMIO_OUT32(base, offset, val) ग_लिखोl(((u32)(val)), (base+offset))

/* Queue control MMIO रेजिस्टरs */
#घोषणा Q_BASE_ADDR		0x85C0  /* Base address of software queue */
#घोषणा Q_WRITE_PTR		0x85C4  /* Current ग_लिखो poपूर्णांकer */
#घोषणा Q_READ_PTR		0x85C8  /* Current पढ़ो poपूर्णांकer */
#घोषणा Q_STATUS		0x85CC  /* queue status */

#घोषणा MMIO_QUEUE_PHYBASE      Q_BASE_ADDR
#घोषणा MMIO_QUEUE_WRITEPORT    Q_WRITE_PTR
#घोषणा MMIO_QUEUE_READPORT     Q_READ_PTR

#अगर_अघोषित FB_BLANK_UNBLANK
#घोषणा FB_BLANK_UNBLANK	0
#पूर्ण_अगर
#अगर_अघोषित FB_BLANK_NORMAL
#घोषणा FB_BLANK_NORMAL		1
#पूर्ण_अगर
#अगर_अघोषित FB_BLANK_VSYNC_SUSPEND
#घोषणा FB_BLANK_VSYNC_SUSPEND	2
#पूर्ण_अगर
#अगर_अघोषित FB_BLANK_HSYNC_SUSPEND
#घोषणा FB_BLANK_HSYNC_SUSPEND	3
#पूर्ण_अगर
#अगर_अघोषित FB_BLANK_POWERDOWN
#घोषणा FB_BLANK_POWERDOWN	4
#पूर्ण_अगर

क्रमागत _SIS_LCD_TYPE अणु
    LCD_INVALID = 0,
    LCD_800x600,
    LCD_1024x768,
    LCD_1280x1024,
    LCD_1280x960,
    LCD_640x480,
    LCD_1600x1200,
    LCD_1920x1440,
    LCD_2048x1536,
    LCD_320x240,	/* FSTN */
    LCD_1400x1050,
    LCD_1152x864,
    LCD_1152x768,
    LCD_1280x768,
    LCD_1024x600,
    LCD_320x240_2,	/* DSTN */
    LCD_320x240_3,	/* DSTN */
    LCD_848x480,
    LCD_1280x800,
    LCD_1680x1050,
    LCD_1280x720,
    LCD_1280x854,
    LCD_CUSTOM,
    LCD_UNKNOWN
पूर्ण;

क्रमागत _SIS_CMDTYPE अणु
    MMIO_CMD = 0,
    AGP_CMD_QUEUE,
    VM_CMD_QUEUE,
पूर्ण;

काष्ठा SIS_OH अणु
	काष्ठा SIS_OH *poh_next;
	काष्ठा SIS_OH *poh_prev;
	u32            offset;
	u32            size;
पूर्ण;

काष्ठा SIS_OHALLOC अणु
	काष्ठा SIS_OHALLOC *poha_next;
	काष्ठा SIS_OH aoh[1];
पूर्ण;

काष्ठा SIS_HEAP अणु
	काष्ठा SIS_OH	oh_मुक्त;
	काष्ठा SIS_OH	oh_used;
	काष्ठा SIS_OH	*poh_मुक्तlist;
	काष्ठा SIS_OHALLOC *poha_chain;
	u32		max_मुक्तsize;
	काष्ठा sis_video_info *vinfo;
पूर्ण;

/* Our "par" */
काष्ठा sis_video_info अणु
	पूर्णांक		cardnumber;
	काष्ठा fb_info  *memyselfandi;

	काष्ठा SiS_Private SiS_Pr;

	काष्ठा sisfb_info sisfbinfo;	/* For ioctl SISFB_GET_INFO */

	काष्ठा fb_var_screeninfo शेष_var;

	काष्ठा fb_fix_screeninfo sisfb_fix;
	u32		pseuकरो_palette[16];

	काष्ठा sisfb_monitor अणु
		u16 hmin;
		u16 hmax;
		u16 vmin;
		u16 vmax;
		u32 dघड़ीmax;
		u8  feature;
		bool datavalid;
	पूर्ण		sisfb_thismonitor;

	अचिन्हित लघु	chip_id;	/* PCI ID of chip */
	अचिन्हित लघु	chip_venकरोr;	/* PCI ID of venकरोr */
	अक्षर		myid[40];

	काष्ठा pci_dev  *nbridge;
	काष्ठा pci_dev  *lpcdev;

	पूर्णांक		mni;	/* Mode number index */

	अचिन्हित दीर्घ	video_size;
	अचिन्हित दीर्घ	video_base;
	अचिन्हित दीर्घ	mmio_size;
	अचिन्हित दीर्घ	mmio_base;
	अचिन्हित दीर्घ	vga_base;

	अचिन्हित दीर्घ	video_offset;

	अचिन्हित दीर्घ	UMAsize, LFBsize;

	व्योम __iomem	*video_vbase;
	व्योम __iomem	*mmio_vbase;

	अचिन्हित अक्षर	*bios_abase;

	पूर्णांक		wc_cookie;

	u32		sisfb_mem;

	u32		sisfb_parm_mem;
	पूर्णांक		sisfb_accel;
	पूर्णांक		sisfb_ypan;
	पूर्णांक		sisfb_max;
	पूर्णांक		sisfb_userom;
	पूर्णांक		sisfb_useoem;
	पूर्णांक		sisfb_mode_idx;
	पूर्णांक		sisfb_parm_rate;
	पूर्णांक		sisfb_crt1off;
	पूर्णांक		sisfb_क्रमcecrt1;
	पूर्णांक		sisfb_crt2type;
	पूर्णांक		sisfb_crt2flags;
	पूर्णांक		sisfb_dstn;
	पूर्णांक		sisfb_fstn;
	पूर्णांक		sisfb_tvplug;
	पूर्णांक		sisfb_tvstd;
	पूर्णांक		sisfb_nocrt2rate;

	u32		heapstart;		/* offset  */
	व्योम __iomem	*sisfb_heap_start;	/* address */
	व्योम __iomem	*sisfb_heap_end;	/* address */
	u32		sisfb_heap_size;
	पूर्णांक		havenoheap;

	काष्ठा SIS_HEAP	sisfb_heap;		/* This card's vram heap */

	पूर्णांक		video_bpp;
	पूर्णांक		video_cmap_len;
	पूर्णांक		video_width;
	पूर्णांक		video_height;
	अचिन्हित पूर्णांक	refresh_rate;

	अचिन्हित पूर्णांक	chip;
	अचिन्हित पूर्णांक	chip_real_id;
	u8		revision_id;
	पूर्णांक		sisvga_enabled;		/* PCI device was enabled */

	पूर्णांक		video_linelength;	/* real pitch */
	पूर्णांक		scrnpitchCRT1;		/* pitch regarding पूर्णांकerlace */

	u16		DstColor;		/* For 2d acceleration */
	u32		SiS310_AccelDepth;
	u32		CommandReg;
	पूर्णांक		cmdqueuelength;		/* Current (क्रम accel) */
	u32		cmdQueueSize;		/* Total size in KB */

	spinlock_t	lockaccel;		/* Do not use outside of kernel! */

	अचिन्हित पूर्णांक	pcibus;
	अचिन्हित पूर्णांक	pcislot;
	अचिन्हित पूर्णांक	pcअगरunc;

	पूर्णांक		accel;
	पूर्णांक		engineok;

	u16		subsysvenकरोr;
	u16		subsysdevice;

	u32		vbflags;		/* Replacing deprecated stuff from above */
	u32		currentvbflags;
	u32		vbflags2;

	पूर्णांक		lcdxres, lcdyres;
	पूर्णांक		lcddeभ_शेषeidx, tvdeभ_शेषeidx, deभ_शेषeidx;
	u32		CRT2LCDType;		/* defined in "SIS_LCD_TYPE" */
	u32		curFSTN, curDSTN;

	पूर्णांक		current_bpp;
	पूर्णांक		current_width;
	पूर्णांक		current_height;
	पूर्णांक		current_htotal;
	पूर्णांक		current_vtotal;
	पूर्णांक		current_linelength;
	__u32		current_pixघड़ी;
	पूर्णांक		current_refresh_rate;

	अचिन्हित पूर्णांक	current_base;

	u8		mode_no;
	u8		rate_idx;
	पूर्णांक		modechanged;
	अचिन्हित अक्षर	modeprechange;

	u8		sisfb_lastrates[128];

	पूर्णांक		newrom;
	पूर्णांक		haveXGIROM;
	पूर्णांक		रेजिस्टरed;
	पूर्णांक		warncount;

	पूर्णांक		sisvga_engine;
	पूर्णांक		hwcursor_size;
	पूर्णांक		CRT2_ग_लिखो_enable;
	u8		caps;

	u8		detectedpdc;
	u8		detectedpdca;
	u8		detectedlcda;

	व्योम __iomem	*hwcursor_vbase;

	पूर्णांक		chronteltype;
	पूर्णांक		tvxpos, tvypos;
	u8		p2_1f,p2_20,p2_2b,p2_42,p2_43,p2_01,p2_02;
	पूर्णांक		tvx, tvy;

	u8		sisfblocked;

	काष्ठा sisfb_info sisfb_infoblock;

	काष्ठा sisfb_cmd sisfb_command;

	u32		sisfb_id;

	u8		sisfb_can_post;
	u8		sisfb_card_posted;
	u8		sisfb_was_boot_device;

	काष्ठा sis_video_info *next;
पूर्ण;

/* from sis_accel.c */
बाह्य व्योम	fbcon_sis_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम	fbcon_sis_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area);
बाह्य पूर्णांक	fbcon_sis_sync(काष्ठा fb_info *info);

/* Internal 2D accelerator functions */
बाह्य पूर्णांक	sisfb_initaccel(काष्ठा sis_video_info *ivideo);
बाह्य व्योम	sisfb_syncaccel(काष्ठा sis_video_info *ivideo);

/* Internal general routines */
#अगर_घोषित CONFIG_FB_SIS_300
अचिन्हित पूर्णांक	sisfb_पढ़ो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
व्योम		sisfb_ग_लिखो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg, अचिन्हित पूर्णांक val);
अचिन्हित पूर्णांक	sisfb_पढ़ो_lpc_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
व्योम		sisfb_ग_लिखो_nbridge_pci_byte(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg, अचिन्हित अक्षर val);
अचिन्हित पूर्णांक	sisfb_पढ़ो_mio_pci_word(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
#पूर्ण_अगर

/* SiS-specअगरic exported functions */
व्योम			sis_दो_स्मृति(काष्ठा sis_memreq *req);
व्योम			sis_दो_स्मृति_new(काष्ठा pci_dev *pdev, काष्ठा sis_memreq *req);
व्योम			sis_मुक्त(u32 base);
व्योम			sis_मुक्त_new(काष्ठा pci_dev *pdev, u32 base);

/* Routines from init.c/init301.c */
बाह्य अचिन्हित लघु	SiS_GetModeID_LCD(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, bool FSTN, अचिन्हित लघु CustomT,
				पूर्णांक LCDwith, पूर्णांक LCDheight, अचिन्हित पूर्णांक VBFlags2);
बाह्य अचिन्हित लघु	SiS_GetModeID_TV(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, अचिन्हित पूर्णांक VBFlags2);
बाह्य अचिन्हित लघु	SiS_GetModeID_VGA2(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay,
				पूर्णांक VDisplay, पूर्णांक Depth, अचिन्हित पूर्णांक VBFlags2);
बाह्य व्योम		SiSRegInit(काष्ठा SiS_Private *SiS_Pr, SISIOADDRESS BaseAddr);
बाह्य bool		SiSSetMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo);
बाह्य व्योम		SiS_SetEnableDstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable);
बाह्य व्योम		SiS_SetEnableFstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable);

बाह्य bool		SiSDetermineROMLayout661(काष्ठा SiS_Private *SiS_Pr);

बाह्य bool		sisfb_gettotalfrommode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
				पूर्णांक *htotal, पूर्णांक *vtotal, अचिन्हित अक्षर rateindex);
बाह्य पूर्णांक		sisfb_mode_rate_to_dघड़ी(काष्ठा SiS_Private *SiS_Pr,
				अचिन्हित अक्षर modeno, अचिन्हित अक्षर rateindex);
बाह्य पूर्णांक		sisfb_mode_rate_to_ddata(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
				अचिन्हित अक्षर rateindex, काष्ठा fb_var_screeninfo *var);


#पूर्ण_अगर
