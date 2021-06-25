<शैली गुरु>
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * Global definitions क्रम init.c and init301.c
 *
 * Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is मुक्त software; you can redistribute it and/or modअगरy
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation; either version 2 of the named License,
 * * or any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License क्रम more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary क्रमms, with or without
 * * modअगरication, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary क्रमm must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    करोcumentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to enकरोrse or promote products
 * *    derived from this software without specअगरic prior written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: 	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#अगर_अघोषित _INITDEF_
#घोषणा _INITDEF_

#घोषणा IS_SIS330		(SiS_Pr->ChipType == SIS_330)
#घोषणा IS_SIS550		(SiS_Pr->ChipType == SIS_550)
#घोषणा IS_SIS650		(SiS_Pr->ChipType == SIS_650)  /* All versions, incl 651, M65x */
#घोषणा IS_SIS740		(SiS_Pr->ChipType == SIS_740)
#घोषणा IS_SIS651	        (SiS_Pr->SiS_SysFlags & (SF_Is651 | SF_Is652))
#घोषणा IS_SISM650	        (SiS_Pr->SiS_SysFlags & (SF_IsM650 | SF_IsM652 | SF_IsM653))
#घोषणा IS_SIS65x               (IS_SIS651 || IS_SISM650)       /* Only special versions of 65x */
#घोषणा IS_SIS661		(SiS_Pr->ChipType == SIS_661)
#घोषणा IS_SIS741		(SiS_Pr->ChipType == SIS_741)
#घोषणा IS_SIS660		(SiS_Pr->ChipType == SIS_660)
#घोषणा IS_SIS760		(SiS_Pr->ChipType == SIS_760)
#घोषणा IS_SIS761		(SiS_Pr->ChipType == SIS_761)
#घोषणा IS_SIS661741660760	(IS_SIS661 || IS_SIS741 || IS_SIS660 || IS_SIS760 || IS_SIS761)
#घोषणा IS_SIS650740            ((SiS_Pr->ChipType >= SIS_650) && (SiS_Pr->ChipType < SIS_330))
#घोषणा IS_SIS550650740         (IS_SIS550 || IS_SIS650740)
#घोषणा IS_SIS650740660         (IS_SIS650 || IS_SIS740 || IS_SIS661741660760)
#घोषणा IS_SIS550650740660      (IS_SIS550 || IS_SIS650740660)

#घोषणा SISGETROMW(x)		(ROMAddr[(x)] | (ROMAddr[(x)+1] << 8))

/* SiS_VBType */
#घोषणा VB_SIS301		0x0001
#घोषणा VB_SIS301B		0x0002
#घोषणा VB_SIS302B		0x0004
#घोषणा VB_SIS301LV		0x0008
#घोषणा VB_SIS302LV		0x0010
#घोषणा VB_SIS302ELV		0x0020
#घोषणा VB_SIS301C		0x0040
#घोषणा VB_SIS307T		0x0080
#घोषणा VB_SIS307LV		0x0100
#घोषणा VB_UMC			0x4000
#घोषणा VB_NoLCD        	0x8000
#घोषणा VB_SIS30xB		(VB_SIS301B | VB_SIS301C | VB_SIS302B | VB_SIS307T)
#घोषणा VB_SIS30xC		(VB_SIS301C | VB_SIS307T)
#घोषणा VB_SISTMDS		(VB_SIS301 | VB_SIS301B | VB_SIS301C | VB_SIS302B | VB_SIS307T)
#घोषणा VB_SISLVDS		(VB_SIS301LV | VB_SIS302LV | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SIS30xBLV		(VB_SIS30xB | VB_SISLVDS)
#घोषणा VB_SIS30xCLV		(VB_SIS30xC | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISVB		(VB_SIS301 | VB_SIS30xBLV)
#घोषणा VB_SISLCDA		(VB_SIS302B | VB_SIS301C  | VB_SIS307T  | VB_SISLVDS)
#घोषणा VB_SISTMDSLCDA		(VB_SIS301C | VB_SIS307T)
#घोषणा VB_SISPART4SCALER	(VB_SIS301C | VB_SIS307T | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISHIVISION		(VB_SIS301 | VB_SIS301B | VB_SIS302B)
#घोषणा VB_SISYPBPR		(VB_SIS301C | VB_SIS307T  | VB_SIS301LV | VB_SIS302LV | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISTAP4SCALER	(VB_SIS301C | VB_SIS307T | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISPART4OVERFLOW	(VB_SIS301C | VB_SIS307T | VB_SIS302LV | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISPWD		(VB_SIS301C | VB_SIS307T | VB_SISLVDS)
#घोषणा VB_SISEMI		(VB_SIS302LV | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISPOWER		(VB_SIS301C | VB_SIS307T | VB_SIS302LV | VB_SIS302ELV | VB_SIS307LV)
#घोषणा VB_SISDUALLINK		(VB_SIS302LV | VB_SIS302ELV | VB_SIS307T | VB_SIS307LV)
#घोषणा VB_SISVGA2		VB_SISTMDS
#घोषणा VB_SISRAMDAC202		(VB_SIS301C | VB_SIS307T)

/* VBInfo */
#घोषणा SetSimuScanMode         0x0001   /* CR 30 */
#घोषणा SwitchCRT2              0x0002
#घोषणा SetCRT2ToAVIDEO         0x0004
#घोषणा SetCRT2ToSVIDEO         0x0008
#घोषणा SetCRT2ToSCART          0x0010
#घोषणा SetCRT2ToLCD            0x0020
#घोषणा SetCRT2ToRAMDAC         0x0040
#घोषणा SetCRT2ToHiVision       0x0080   		/* क्रम SiS bridge */
#घोषणा SetCRT2ToCHYPbPr       	SetCRT2ToHiVision	/* क्रम Chrontel   */
#घोषणा SetNTSCTV               0x0000   /* CR 31 */
#घोषणा SetPALTV                0x0100   		/* Deprecated here, now in TVMode */
#घोषणा SetInSlaveMode          0x0200
#घोषणा SetNotSimuMode          0x0400
#घोषणा SetNotSimuTVMode        SetNotSimuMode
#घोषणा SetDispDevSwitch        0x0800
#घोषणा SetCRT2ToYPbPr525750    0x0800
#घोषणा LoadDACFlag             0x1000
#घोषणा DisableCRT2Display      0x2000
#घोषणा DriverMode              0x4000
#घोषणा HotKeySwitch            0x8000
#घोषणा SetCRT2ToLCDA           0x8000

/* v-- Needs change in sis_vga.c अगर changed (GPIO) --v */
#घोषणा SetCRT2ToTV             (SetCRT2ToYPbPr525750|SetCRT2ToHiVision|SetCRT2ToSCART|SetCRT2ToSVIDEO|SetCRT2ToAVIDEO)
#घोषणा SetCRT2ToTVNoYPbPrHiVision (SetCRT2ToSCART | SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)
#घोषणा SetCRT2ToTVNoHiVision  	(SetCRT2ToYPbPr525750 | SetCRT2ToSCART | SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)

/* SiS_ModeType */
#घोषणा ModeText                0x00
#घोषणा ModeCGA                 0x01
#घोषणा ModeEGA                 0x02
#घोषणा ModeVGA                 0x03
#घोषणा Mode15Bpp               0x04
#घोषणा Mode16Bpp               0x05
#घोषणा Mode24Bpp               0x06
#घोषणा Mode32Bpp               0x07

#घोषणा ModeTypeMask            0x07
#घोषणा IsTextMode              0x07

#घोषणा DACInfoFlag             0x0018
#घोषणा MemoryInfoFlag          0x01E0
#घोषणा MemorySizeShअगरt         5

/* modeflag */
#घोषणा Charx8Dot               0x0200
#घोषणा LineCompareOff          0x0400
#घोषणा CRT2Mode                0x0800
#घोषणा HalfDCLK                0x1000
#घोषणा NoSupportSimuTV         0x2000
#घोषणा NoSupportLCDScale	0x4000 /* SiS bridge: No scaling possible (no matter what panel) */
#घोषणा DoubleScanMode          0x8000

/* Infoflag */
#घोषणा SupportTV               0x0008
#घोषणा SupportTV1024           0x0800
#घोषणा SupportCHTV 		0x0800
#घोषणा Support64048060Hz       0x0800  /* Special क्रम 640x480 LCD */
#घोषणा SupportHiVision         0x0010
#घोषणा SupportYPbPr750p        0x1000
#घोषणा SupportLCD              0x0020
#घोषणा SupportRAMDAC2          0x0040	/* All           (<= 100Mhz) */
#घोषणा SupportRAMDAC2_135      0x0100  /* All except DH (<= 135Mhz) */
#घोषणा SupportRAMDAC2_162      0x0200  /* B, C          (<= 162Mhz) */
#घोषणा SupportRAMDAC2_202      0x0400  /* C             (<= 202Mhz) */
#घोषणा InterlaceMode           0x0080
#घोषणा SyncPP                  0x0000
#घोषणा HaveWideTiming		0x2000	/* Have specअगरic wide- and non-wide timing */
#घोषणा SyncPN                  0x4000
#घोषणा SyncNP                  0x8000
#घोषणा SyncNN                  0xc000

/* SetFlag */
#घोषणा ProgrammingCRT2         0x0001
#घोषणा LowModeTests		0x0002
/* #घोषणा TVSimuMode           0x0002 - deprecated */
/* #घोषणा RPLLDIV2XO           0x0004 - deprecated */
#घोषणा LCDVESATiming           0x0008
#घोषणा EnableLVDSDDA           0x0010
#घोषणा SetDispDevSwitchFlag    0x0020
#घोषणा CheckWinDos             0x0040
#घोषणा SetDOSMode              0x0080

/* TVMode flag */
#घोषणा TVSetPAL		0x0001
#घोषणा TVSetNTSCJ		0x0002
#घोषणा TVSetPALM		0x0004
#घोषणा TVSetPALN		0x0008
#घोषणा TVSetCHOverScan		0x0010
#घोषणा TVSetYPbPr525i		0x0020 /* new 0x10 */
#घोषणा TVSetYPbPr525p		0x0040 /* new 0x20 */
#घोषणा TVSetYPbPr750p		0x0080 /* new 0x40 */
#घोषणा TVSetHiVision		0x0100 /* new 0x80; = 1080i, software-wise identical */
#घोषणा TVSetTVSimuMode		0x0200 /* new 0x200, prev. 0x800 */
#घोषणा TVRPLLDIV2XO		0x0400 /* prev 0x1000 */
#घोषणा TVSetNTSC1024		0x0800 /* new 0x100, prev. 0x2000 */
#घोषणा TVSet525p1024		0x1000 /* TW */
#घोषणा TVAspect43		0x2000
#घोषणा TVAspect169		0x4000
#घोषणा TVAspect43LB		0x8000

/* YPbPr flag (>=315, <661; converted to TVMode) */
#घोषणा YPbPr525p               0x0001
#घोषणा YPbPr750p               0x0002
#घोषणा YPbPr525i               0x0004
#घोषणा YPbPrHiVision           0x0008
#घोषणा YPbPrModeMask           (YPbPr750p | YPbPr525p | YPbPr525i | YPbPrHiVision)

/* SysFlags (to identअगरy special versions) */
#घोषणा SF_Is651                0x0001
#घोषणा SF_IsM650               0x0002
#घोषणा SF_Is652		0x0004
#घोषणा SF_IsM652		0x0008
#घोषणा SF_IsM653		0x0010
#घोषणा SF_IsM661		0x0020
#घोषणा SF_IsM741		0x0040
#घोषणा SF_IsM760		0x0080
#घोषणा SF_760UMA		0x4000  /* 76x: We have UMA */
#घोषणा SF_760LFB		0x8000  /* 76x: We have LFB */

/* CR32 (Newer 630, and 315 series)

   [0]   VB connected with CVBS
   [1]   VB connected with SVHS
   [2]   VB connected with SCART
   [3]   VB connected with LCD
   [4]   VB connected with CRT2 (secondary VGA)
   [5]   CRT1 monitor is connected
   [6]   VB connected with Hi-Vision TV
   [7]   <= 330: VB connected with DVI combo connector
         >= 661: VB connected to YPbPr
*/

/* CR35 (300 series only) */
#घोषणा TVOverScan              0x10
#घोषणा TVOverScanShअगरt         4

/* CR35 (661 series only)
   [0]    1 = PAL, 0 = NTSC
   [1]    1 = NTSC-J (अगर D0 = 0)
   [2]    1 = PALM (अगर D0 = 1)
   [3]    1 = PALN (अगर D0 = 1)
   [4]    1 = Overscan (Chrontel only)
   [7:5]  (only अगर D2 in CR38 is set)
	  000  525i
	  001  525p
	  010  750p
	  011  1080i (or HiVision on 301, 301B)
*/

/* CR37
   [0]   Set 24/18 bit (0/1) RGB to LVDS/TMDS transmitter (set by BIOS)
   [3:1] External chip
         300 series:
	    001   SiS301 (never seen)
	    010   LVDS
	    011   LVDS + Tumpion Zurac
	    100   LVDS + Chrontel 7005
	    110   Chrontel 7005
	  315/330 series
	    001   SiS30x (never seen)
	    010   LVDS
	    011   LVDS + Chrontel 7019
	  660 series [2:1] only:
	     reserved (chip type now in CR38)
	  All other combinations reserved
   [3]    661 only: Pass 1:1 data
   [4]    LVDS: 0: Panel Link expands / 1: Panel Link करोes not expand
          30x:  0: Bridge scales      / 1: Bridge करोes not scale = Panel scales (अगर possible)
   [5]    LCD polarity select
          0: VESA DMT Standard
	  1: EDID 2.x defined
   [6]    LCD horizontal polarity select
          0: High active
	  1: Low active
   [7]    LCD vertical polarity select
          0: High active
	  1: Low active
*/

/* CR37: LCDInfo */
#घोषणा LCDRGB18Bit           0x0001
#घोषणा LCDNonExpanding       0x0010
#घोषणा LCDSync               0x0020
#घोषणा LCDPass11             0x0100   /* 0: center screen, 1: Pass 1:1 data */
#घोषणा LCDDualLink	      0x0200

#घोषणा DontExpandLCD	      LCDNonExpanding
#घोषणा LCDNonExpandingShअगरt       4
#घोषणा DontExpandLCDShअगरt    LCDNonExpandingShअगरt
#घोषणा LCDSyncBit            0x00e0
#घोषणा LCDSyncShअगरt               6

/* CR38 (315 series) */
#घोषणा EnableDualEdge 		0x01
#घोषणा SetToLCDA		0x02   /* LCD channel A (301C/302B/30x(E)LV and 650+LVDS only) */
#घोषणा EnableCHScart           0x04   /* Scart on Ch7019 (unofficial definition - TW) */
#घोषणा EnableCHYPbPr           0x08   /* YPbPr on Ch7019 (480i HDTV); only on 650/Ch7019 प्रणालीs */
#घोषणा EnableSiSYPbPr          0x08   /* Enable YPbPr mode (30xLV/301C only) */
#घोषणा EnableYPbPr525i         0x00   /* Enable 525i YPbPr mode (30xLV/301C only) (mask 0x30) */
#घोषणा EnableYPbPr525p         0x10   /* Enable 525p YPbPr mode (30xLV/301C only) (mask 0x30) */
#घोषणा EnableYPbPr750p         0x20   /* Enable 750p YPbPr mode (30xLV/301C only) (mask 0x30) */
#घोषणा EnableYPbPr1080i        0x30   /* Enable 1080i YPbPr mode (30xLV/301C only) (mask 0x30) */
#घोषणा EnablePALM              0x40   /* 1 = Set PALM */
#घोषणा EnablePALN              0x80   /* 1 = Set PALN */
#घोषणा EnableNTSCJ             EnablePALM  /* Not BIOS */

/* CR38 (661 and later)
  D[7:5]  000 No VB
          001 301 series VB
	  010 LVDS
	  011 Chrontel 7019
	  100 Conexant
  D2      Enable YPbPr output (see CR35)
  D[1:0]  LCDA (like beक्रमe)
*/

#घोषणा EnablePALMN             0x40   /* Romflag: 1 = Allow PALM/PALN */

/* CR39 (650 only) */
#घोषणा LCDPass1_1		0x01   /* 0: center screen, 1: pass 1:1 data output  */
#घोषणा Enable302LV_DualLink    0x04   /* 302LV only; enable dual link */

/* CR39 (661 and later)
   D[7]   LVDS (SiS or third party)
   D[1:0] YPbPr Aspect Ratio
          00 4:3 letterbox
	  01 4:3
	  10 16:9
	  11 4:3
*/

/* CR3B (651+301C)
   D[1:0] YPbPr Aspect Ratio
          ?
*/

/* CR79 (315/330 series only; not 661 and later)
   [3-0] Notअगरy driver
         0001 Mode Switch event (set by BIOS)
	 0010 Epansion On/Off event
	 0011 TV UnderScan/OverScan event
	 0100 Set Brightness event
	 0101 Set Contrast event
	 0110 Set Mute event
	 0111 Set Volume Up/Down event
   [4]   Enable Backlight Control by BIOS/driver
         (set by driver; set means that the BIOS should
	 not touch the backlight रेजिस्टरs because eg.
	 the driver alपढ़ोy चयनed off the backlight)
   [5]   PAL/NTSC (set by BIOS)
   [6]   Expansion On/Off (set by BIOS; copied to CR32[4])
   [7]   TV UnderScan/OverScan (set by BIOS)
*/

/* CR7C - 661 and later
   [7]   DualEdge enabled (or: to be enabled)
   [6]   CRT2 = TV/LCD/VGA enabled (or: to be enabled)
   [5]   Init करोne (set at end of SiS_Init)
   अणु4]   LVDS LCD capabilities
   [3]   LVDS LCD capabilities
   [2]   LVDS LCD capabilities (PWD)
   [1]   LVDS LCD capabilities (PWD)
   [0]   LVDS=1, TMDS=0 (SiS or third party)
*/

/* CR7E - 661 and later
   VBType:
   [7] LVDS (third party)
   [3] 301C
   [2] 302LV
   [1] 301LV
   [0] 301B
*/

/* LCDResInfo */
#घोषणा Panel300_800x600        0x01	/* CR36 */
#घोषणा Panel300_1024x768       0x02
#घोषणा Panel300_1280x1024      0x03
#घोषणा Panel300_1280x960       0x04
#घोषणा Panel300_640x480        0x05
#घोषणा Panel300_1024x600       0x06
#घोषणा Panel300_1152x768       0x07
#घोषणा Panel300_1280x768       0x0a
#घोषणा Panel300_Custom		0x0f
#घोषणा Panel300_Barco1366      0x10

#घोषणा Panel310_800x600        0x01
#घोषणा Panel310_1024x768       0x02
#घोषणा Panel310_1280x1024      0x03
#घोषणा Panel310_640x480        0x04
#घोषणा Panel310_1024x600       0x05
#घोषणा Panel310_1152x864       0x06
#घोषणा Panel310_1280x960       0x07
#घोषणा Panel310_1152x768       0x08	/* LVDS only */
#घोषणा Panel310_1400x1050      0x09
#घोषणा Panel310_1280x768       0x0a
#घोषणा Panel310_1600x1200      0x0b
#घोषणा Panel310_320x240_2      0x0c    /* xSTN */
#घोषणा Panel310_320x240_3      0x0d    /* xSTN */
#घोषणा Panel310_320x240_1      0x0e    /* xSTN - This is fake, can be any */
#घोषणा Panel310_Custom		0x0f

#घोषणा Panel661_800x600        0x01
#घोषणा Panel661_1024x768       0x02
#घोषणा Panel661_1280x1024      0x03
#घोषणा Panel661_640x480        0x04
#घोषणा Panel661_1024x600       0x05
#घोषणा Panel661_1152x864       0x06
#घोषणा Panel661_1280x960       0x07
#घोषणा Panel661_1280x854       0x08
#घोषणा Panel661_1400x1050      0x09
#घोषणा Panel661_1280x768       0x0a
#घोषणा Panel661_1600x1200      0x0b
#घोषणा Panel661_1280x800       0x0c
#घोषणा Panel661_1680x1050      0x0d
#घोषणा Panel661_1280x720       0x0e
#घोषणा Panel661_Custom		0x0f

#घोषणा Panel_800x600           0x01	/* Unअगरied values */
#घोषणा Panel_1024x768          0x02    /* MUST match BIOS values from 0-e */
#घोषणा Panel_1280x1024         0x03
#घोषणा Panel_640x480           0x04
#घोषणा Panel_1024x600          0x05
#घोषणा Panel_1152x864          0x06
#घोषणा Panel_1280x960          0x07
#घोषणा Panel_1152x768          0x08	/* LVDS only */
#घोषणा Panel_1400x1050         0x09
#घोषणा Panel_1280x768          0x0a    /* 30xB/C and LVDS only (BIOS: all) */
#घोषणा Panel_1600x1200         0x0b
#घोषणा Panel_1280x800		0x0c    /* 661etc (TMDS) */
#घोषणा Panel_1680x1050         0x0d    /* 661etc  */
#घोषणा Panel_1280x720		0x0e    /* 661etc  */
#घोषणा Panel_Custom		0x0f	/* MUST BE 0x0f (क्रम DVI DDC detection) */
#घोषणा Panel_320x240_1         0x10    /* SiS 550 xSTN */
#घोषणा Panel_Barco1366         0x11
#घोषणा Panel_848x480		0x12
#घोषणा Panel_320x240_2		0x13    /* SiS 550 xSTN */
#घोषणा Panel_320x240_3		0x14    /* SiS 550 xSTN */
#घोषणा Panel_1280x768_2        0x15	/* 30xLV */
#घोषणा Panel_1280x768_3        0x16    /* (unused) */
#घोषणा Panel_1280x800_2	0x17    /* 30xLV */
#घोषणा Panel_856x480		0x18
#घोषणा Panel_1280x854		0x19	/* 661etc */

/* Index in ModeResInfo table */
#घोषणा SIS_RI_320x200    0
#घोषणा SIS_RI_320x240    1
#घोषणा SIS_RI_320x400    2
#घोषणा SIS_RI_400x300    3
#घोषणा SIS_RI_512x384    4
#घोषणा SIS_RI_640x400    5
#घोषणा SIS_RI_640x480    6
#घोषणा SIS_RI_800x600    7
#घोषणा SIS_RI_1024x768   8
#घोषणा SIS_RI_1280x1024  9
#घोषणा SIS_RI_1600x1200 10
#घोषणा SIS_RI_1920x1440 11
#घोषणा SIS_RI_2048x1536 12
#घोषणा SIS_RI_720x480   13
#घोषणा SIS_RI_720x576   14
#घोषणा SIS_RI_1280x960  15
#घोषणा SIS_RI_800x480   16
#घोषणा SIS_RI_1024x576  17
#घोषणा SIS_RI_1280x720  18
#घोषणा SIS_RI_856x480   19
#घोषणा SIS_RI_1280x768  20
#घोषणा SIS_RI_1400x1050 21
#घोषणा SIS_RI_1152x864  22  /* Up to here SiS conक्रमming */
#घोषणा SIS_RI_848x480   23
#घोषणा SIS_RI_1360x768  24
#घोषणा SIS_RI_1024x600  25
#घोषणा SIS_RI_1152x768  26
#घोषणा SIS_RI_768x576   27
#घोषणा SIS_RI_1360x1024 28
#घोषणा SIS_RI_1680x1050 29
#घोषणा SIS_RI_1280x800  30
#घोषणा SIS_RI_1920x1080 31
#घोषणा SIS_RI_960x540   32
#घोषणा SIS_RI_960x600   33
#घोषणा SIS_RI_1280x854  34

/* CR5F */
#घोषणा IsM650                  0x80

/* Timing data */
#घोषणा NTSCHT                  1716
#घोषणा NTSC2HT                 1920
#घोषणा NTSCVT                  525
#घोषणा PALHT                   1728
#घोषणा PALVT                   625
#घोषणा StHiTVHT                892
#घोषणा StHiTVVT                1126
#घोषणा StHiTextTVHT            1000
#घोषणा StHiTextTVVT            1126
#घोषणा ExtHiTVHT               2100
#घोषणा ExtHiTVVT               1125

/* Indices in (VB)VCLKData tables */

#घोषणा VCLK28                  0x00   /* Index in VCLKData table (300 and 315) */
#घोषणा VCLK40                  0x04   /* Index in VCLKData table (300 and 315) */
#घोषणा VCLK65_300              0x09   /* Index in VCLKData table (300) */
#घोषणा VCLK108_2_300           0x14   /* Index in VCLKData table (300) */
#घोषणा VCLK81_300		0x3f   /* Index in VCLKData table (300) */
#घोषणा VCLK108_3_300           0x42   /* Index in VCLKData table (300) */
#घोषणा VCLK100_300             0x43   /* Index in VCLKData table (300) */
#घोषणा VCLK34_300              0x3d   /* Index in VCLKData table (300) */
#घोषणा VCLK_CUSTOM_300		0x47

#घोषणा VCLK65_315              0x0b   /* Indices in (VB)VCLKData table (315) */
#घोषणा VCLK108_2_315           0x19
#घोषणा VCLK81_315		0x5b
#घोषणा VCLK162_315             0x5e
#घोषणा VCLK108_3_315           0x45
#घोषणा VCLK100_315             0x46
#घोषणा VCLK34_315              0x55
#घोषणा VCLK68_315		0x0d
#घोषणा VCLK_1280x800_315_2	0x5c
#घोषणा VCLK121_315		0x5d
#घोषणा VCLK130_315		0x72
#घोषणा VCLK_1280x720		0x5f
#घोषणा VCLK_1280x768_2		0x60
#घोषणा VCLK_1280x768_3		0x61   /* (unused?) */
#घोषणा VCLK_CUSTOM_315		0x62
#घोषणा VCLK_1280x720_2		0x63
#घोषणा VCLK_720x480		0x67
#घोषणा VCLK_720x576		0x68
#घोषणा VCLK_768x576		0x68
#घोषणा VCLK_848x480		0x65
#घोषणा VCLK_856x480		0x66
#घोषणा VCLK_800x480		0x65
#घोषणा VCLK_1024x576		0x51
#घोषणा VCLK_1152x864		0x64
#घोषणा VCLK_1360x768		0x58
#घोषणा VCLK_1280x800_315	0x6c
#घोषणा VCLK_1280x854		0x76

#घोषणा TVCLKBASE_300		0x21   /* Indices on TV घड़ीs in VCLKData table (300) */
#घोषणा TVCLKBASE_315	        0x3a   /* Indices on TV घड़ीs in (VB)VCLKData table (315) */
#घोषणा TVVCLKDIV2              0x00   /* Index relative to TVCLKBASE */
#घोषणा TVVCLK                  0x01   /* Index relative to TVCLKBASE */
#घोषणा HiTVVCLKDIV2            0x02   /* Index relative to TVCLKBASE */
#घोषणा HiTVVCLK                0x03   /* Index relative to TVCLKBASE */
#घोषणा HiTVSimuVCLK            0x04   /* Index relative to TVCLKBASE */
#घोषणा HiTVTextVCLK            0x05   /* Index relative to TVCLKBASE */
#घोषणा YPbPr750pVCLK		0x25   /* Index relative to TVCLKBASE; was 0x0f NOT relative */

/* ------------------------------ */

#घोषणा SetSCARTOutput          0x01

#घोषणा HotPlugFunction         0x08

#घोषणा StStructSize            0x06

#घोषणा SIS_VIDEO_CAPTURE       0x00 - 0x30
#घोषणा SIS_VIDEO_PLAYBACK      0x02 - 0x30
#घोषणा SIS_CRT2_PORT_04        0x04 - 0x30
#घोषणा SIS_CRT2_PORT_10        0x10 - 0x30
#घोषणा SIS_CRT2_PORT_12        0x12 - 0x30
#घोषणा SIS_CRT2_PORT_14        0x14 - 0x30

#घोषणा ADR_CRT2PtrData         0x20E
#घोषणा offset_Zurac            0x210   /* TW: Trumpion Zurac data poपूर्णांकer */
#घोषणा ADR_LVDSDesPtrData      0x212
#घोषणा ADR_LVDSCRT1DataPtr     0x214
#घोषणा ADR_CHTVVCLKPtr         0x216
#घोषणा ADR_CHTVRegDataPtr      0x218

#घोषणा LCDDataLen              8
#घोषणा HiTVDataLen             12
#घोषणा TVDataLen               16

#घोषणा LVDSDataLen             6
#घोषणा LVDSDesDataLen          3
#घोषणा ActiveNonExpanding      0x40
#घोषणा ActiveNonExpandingShअगरt 6
#घोषणा ActivePAL               0x20
#घोषणा ActivePALShअगरt          5
#घोषणा ModeSwitchStatus        0x0F
#घोषणा SoftTVType              0x40
#घोषणा SoftSettingAddr         0x52
#घोषणा ModeSettingAddr         0x53

#घोषणा _PanelType00             0x00
#घोषणा _PanelType01             0x08
#घोषणा _PanelType02             0x10
#घोषणा _PanelType03             0x18
#घोषणा _PanelType04             0x20
#घोषणा _PanelType05             0x28
#घोषणा _PanelType06             0x30
#घोषणा _PanelType07             0x38
#घोषणा _PanelType08             0x40
#घोषणा _PanelType09             0x48
#घोषणा _PanelType0A             0x50
#घोषणा _PanelType0B             0x58
#घोषणा _PanelType0C             0x60
#घोषणा _PanelType0D             0x68
#घोषणा _PanelType0E             0x70
#घोषणा _PanelType0F             0x78

#घोषणा PRIMARY_VGA       	0     /* 1: SiS is primary vga 0:SiS is secondary vga */

#घोषणा BIOSIDCodeAddr          0x235  /* Offsets to ptrs in BIOS image */
#घोषणा OEMUtilIDCodeAddr       0x237
#घोषणा VBModeIDTableAddr       0x239
#घोषणा OEMTVPtrAddr            0x241
#घोषणा PhaseTableAddr          0x243
#घोषणा NTSCFilterTableAddr     0x245
#घोषणा PALFilterTableAddr      0x247
#घोषणा OEMLCDPtr_1Addr         0x249
#घोषणा OEMLCDPtr_2Addr         0x24B
#घोषणा LCDHPosTable_1Addr      0x24D
#घोषणा LCDHPosTable_2Addr      0x24F
#घोषणा LCDVPosTable_1Addr      0x251
#घोषणा LCDVPosTable_2Addr      0x253
#घोषणा OEMLCDPIDTableAddr      0x255

#घोषणा VBModeStructSize        5
#घोषणा PhaseTableSize          4
#घोषणा FilterTableSize         4
#घोषणा LCDHPosTableSize        7
#घोषणा LCDVPosTableSize        5
#घोषणा OEMLVDSPIDTableSize     4
#घोषणा LVDSHPosTableSize       4
#घोषणा LVDSVPosTableSize       6

#घोषणा VB_ModeID               0
#घोषणा VB_TVTableIndex         1
#घोषणा VB_LCDTableIndex        2
#घोषणा VB_LCDHIndex            3
#घोषणा VB_LCDVIndex            4

#घोषणा OEMLCDEnable            0x0001
#घोषणा OEMLCDDelayEnable       0x0002
#घोषणा OEMLCDPOSEnable         0x0004
#घोषणा OEMTVEnable             0x0100
#घोषणा OEMTVDelayEnable        0x0200
#घोषणा OEMTVFlickerEnable      0x0400
#घोषणा OEMTVPhaseEnable        0x0800
#घोषणा OEMTVFilterEnable       0x1000

#घोषणा OEMLCDPanelIDSupport    0x0080

/*
  =============================================================
   		  क्रम 315 series (old data layout)
  =============================================================
*/
#घोषणा SoftDRAMType        0x80
#घोषणा SoftSetting_OFFSET  0x52
#घोषणा SR07_OFFSET  0x7C
#घोषणा SR15_OFFSET  0x7D
#घोषणा SR16_OFFSET  0x81
#घोषणा SR17_OFFSET  0x85
#घोषणा SR19_OFFSET  0x8D
#घोषणा SR1F_OFFSET  0x99
#घोषणा SR21_OFFSET  0x9A
#घोषणा SR22_OFFSET  0x9B
#घोषणा SR23_OFFSET  0x9C
#घोषणा SR24_OFFSET  0x9D
#घोषणा SR25_OFFSET  0x9E
#घोषणा SR31_OFFSET  0x9F
#घोषणा SR32_OFFSET  0xA0
#घोषणा SR33_OFFSET  0xA1

#घोषणा CR40_OFFSET  0xA2
#घोषणा SR25_1_OFFSET  0xF6
#घोषणा CR49_OFFSET  0xF7

#घोषणा VB310Data_1_2_Offset  0xB6
#घोषणा VB310Data_4_D_Offset  0xB7
#घोषणा VB310Data_4_E_Offset  0xB8
#घोषणा VB310Data_4_10_Offset 0xBB

#घोषणा RGBSenseDataOffset    0xBD
#घोषणा YCSenseDataOffset     0xBF
#घोषणा VideoSenseDataOffset  0xC1
#घोषणा OutputSelectOffset    0xF3

#घोषणा ECLK_MCLK_DISTANCE  0x14
#घोषणा VBIOSTablePoपूर्णांकerStart    0x100
#घोषणा StandTablePtrOffset       VBIOSTablePoपूर्णांकerStart+0x02
#घोषणा EModeIDTablePtrOffset     VBIOSTablePoपूर्णांकerStart+0x04
#घोषणा CRT1TablePtrOffset        VBIOSTablePoपूर्णांकerStart+0x06
#घोषणा ScreenOffsetPtrOffset     VBIOSTablePoपूर्णांकerStart+0x08
#घोषणा VCLKDataPtrOffset         VBIOSTablePoपूर्णांकerStart+0x0A
#घोषणा MCLKDataPtrOffset         VBIOSTablePoपूर्णांकerStart+0x0E
#घोषणा CRT2PtrDataPtrOffset      VBIOSTablePoपूर्णांकerStart+0x10
#घोषणा TVAntiFlickPtrOffset      VBIOSTablePoपूर्णांकerStart+0x12
#घोषणा TVDelayPtr1Offset         VBIOSTablePoपूर्णांकerStart+0x14
#घोषणा TVPhaseIncrPtr1Offset     VBIOSTablePoपूर्णांकerStart+0x16
#घोषणा TVYFilterPtr1Offset       VBIOSTablePoपूर्णांकerStart+0x18
#घोषणा LCDDelayPtr1Offset        VBIOSTablePoपूर्णांकerStart+0x20
#घोषणा TVEdgePtr1Offset          VBIOSTablePoपूर्णांकerStart+0x24
#घोषणा CRT2Delay1Offset          VBIOSTablePoपूर्णांकerStart+0x28

#पूर्ण_अगर
