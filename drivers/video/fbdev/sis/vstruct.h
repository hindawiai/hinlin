<शैली गुरु>
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * General काष्ठाure definitions क्रम universal mode चयनing modules
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

#अगर_अघोषित _VSTRUCT_H_
#घोषणा _VSTRUCT_H_

काष्ठा SiS_PanelDelayTbl अणु
 	अचिन्हित अक्षर समयr[2];
पूर्ण;

काष्ठा SiS_LCDData अणु
	अचिन्हित लघु RVBHCMAX;
	अचिन्हित लघु RVBHCFACT;
	अचिन्हित लघु VGAHT;
	अचिन्हित लघु VGAVT;
	अचिन्हित लघु LCDHT;
	अचिन्हित लघु LCDVT;
पूर्ण;

काष्ठा SiS_TVData अणु
	अचिन्हित लघु RVBHCMAX;
	अचिन्हित लघु RVBHCFACT;
	अचिन्हित लघु VGAHT;
	अचिन्हित लघु VGAVT;
	अचिन्हित लघु TVHDE;
	अचिन्हित लघु TVVDE;
	अचिन्हित लघु RVBHRS;
	अचिन्हित अक्षर  FlickerMode;
	अचिन्हित लघु HALFRVBHRS;
	अचिन्हित लघु RVBHRS2;
	अचिन्हित अक्षर  RY1COE;
	अचिन्हित अक्षर  RY2COE;
	अचिन्हित अक्षर  RY3COE;
	अचिन्हित अक्षर  RY4COE;
पूर्ण;

काष्ठा SiS_LVDSData अणु
	अचिन्हित लघु VGAHT;
	अचिन्हित लघु VGAVT;
	अचिन्हित लघु LCDHT;
	अचिन्हित लघु LCDVT;
पूर्ण;

काष्ठा SiS_LVDSDes अणु
	अचिन्हित लघु LCDHDES;
	अचिन्हित लघु LCDVDES;
पूर्ण;

काष्ठा SiS_LVDSCRT1Data अणु
	अचिन्हित अक्षर  CR[15];
पूर्ण;

काष्ठा SiS_CHTVRegData अणु
	अचिन्हित अक्षर  Reg[16];
पूर्ण;

काष्ठा SiS_St अणु
	अचिन्हित अक्षर  St_ModeID;
	अचिन्हित लघु St_ModeFlag;
	अचिन्हित अक्षर  St_StTableIndex;
	अचिन्हित अक्षर  St_CRT2CRTC;
	अचिन्हित अक्षर  St_ResInfo;
	अचिन्हित अक्षर  VB_StTVFlickerIndex;
	अचिन्हित अक्षर  VB_StTVEdgeIndex;
	अचिन्हित अक्षर  VB_StTVYFilterIndex;
	अचिन्हित अक्षर  St_PDC;
पूर्ण;

काष्ठा SiS_VBMode अणु
	अचिन्हित अक्षर  ModeID;
	अचिन्हित अक्षर  VB_TVDelayIndex;
	अचिन्हित अक्षर  VB_TVFlickerIndex;
	अचिन्हित अक्षर  VB_TVPhaseIndex;
	अचिन्हित अक्षर  VB_TVYFilterIndex;
	अचिन्हित अक्षर  VB_LCDDelayIndex;
	अचिन्हित अक्षर  _VB_LCDHIndex;
	अचिन्हित अक्षर  _VB_LCDVIndex;
पूर्ण;

काष्ठा SiS_StandTable_S अणु
	अचिन्हित अक्षर  CRT_COLS;
	अचिन्हित अक्षर  ROWS;
	अचिन्हित अक्षर  CHAR_HEIGHT;
	अचिन्हित लघु CRT_LEN;
	अचिन्हित अक्षर  SR[4];
	अचिन्हित अक्षर  MISC;
	अचिन्हित अक्षर  CRTC[0x19];
	अचिन्हित अक्षर  ATTR[0x14];
	अचिन्हित अक्षर  GRC[9];
पूर्ण;

काष्ठा SiS_Ext अणु
	अचिन्हित अक्षर  Ext_ModeID;
	अचिन्हित लघु Ext_ModeFlag;
	अचिन्हित लघु Ext_VESAID;
	अचिन्हित अक्षर  Ext_RESINFO;
	अचिन्हित अक्षर  VB_ExtTVFlickerIndex;
	अचिन्हित अक्षर  VB_ExtTVEdgeIndex;
	अचिन्हित अक्षर  VB_ExtTVYFilterIndex;
	अचिन्हित अक्षर  VB_ExtTVYFilterIndexROM661;
	अचिन्हित अक्षर  REFindex;
	अक्षर           ROMMODEIDX661;
पूर्ण;

काष्ठा SiS_Ext2 अणु
	अचिन्हित लघु Ext_InfoFlag;
	अचिन्हित अक्षर  Ext_CRT1CRTC;
	अचिन्हित अक्षर  Ext_CRTVCLK;
	अचिन्हित अक्षर  Ext_CRT2CRTC;
	अचिन्हित अक्षर  Ext_CRT2CRTC_NS;
	अचिन्हित अक्षर  ModeID;
	अचिन्हित लघु XRes;
	अचिन्हित लघु YRes;
	अचिन्हित अक्षर  Ext_PDC;
	अचिन्हित अक्षर  Ext_FakeCRT2CRTC;
	अचिन्हित अक्षर  Ext_FakeCRT2Clk;
	अचिन्हित अक्षर  Ext_CRT1CRTC_NORM;
	अचिन्हित अक्षर  Ext_CRTVCLK_NORM;
	अचिन्हित अक्षर  Ext_CRT1CRTC_WIDE;
	अचिन्हित अक्षर  Ext_CRTVCLK_WIDE;
पूर्ण;

काष्ठा SiS_Part2PortTbl अणु
 	अचिन्हित अक्षर  CR[12];
पूर्ण;

काष्ठा SiS_CRT1Table अणु
	अचिन्हित अक्षर  CR[17];
पूर्ण;

काष्ठा SiS_MCLKData अणु
	अचिन्हित अक्षर  SR28,SR29,SR2A;
	अचिन्हित लघु CLOCK;
पूर्ण;

काष्ठा SiS_VCLKData अणु
	अचिन्हित अक्षर  SR2B,SR2C;
	अचिन्हित लघु CLOCK;
पूर्ण;

काष्ठा SiS_VBVCLKData अणु
	अचिन्हित अक्षर  Part4_A,Part4_B;
	अचिन्हित लघु CLOCK;
पूर्ण;

काष्ठा SiS_StResInfo_S अणु
	अचिन्हित लघु HTotal;
	अचिन्हित लघु VTotal;
पूर्ण;

काष्ठा SiS_ModeResInfo_S अणु
	अचिन्हित लघु HTotal;
	अचिन्हित लघु VTotal;
	अचिन्हित अक्षर  XChar;
	अचिन्हित अक्षर  YChar;
पूर्ण;

/* Defines क्रम SiS_CustomT */
/* Never change these क्रम sisfb compatibility */
#घोषणा CUT_NONE		 0
#घोषणा CUT_FORCENONE		 1
#घोषणा CUT_BARCO1366		 2
#घोषणा CUT_BARCO1024		 3
#घोषणा CUT_COMPAQ1280		 4
#घोषणा CUT_COMPAQ12802		 5
#घोषणा CUT_PANEL848		 6
#घोषणा CUT_CLEVO1024		 7
#घोषणा CUT_CLEVO10242		 8
#घोषणा CUT_CLEVO1400		 9
#घोषणा CUT_CLEVO14002		10
#घोषणा CUT_UNIWILL1024		11
#घोषणा CUT_ASUSL3000D		12
#घोषणा CUT_UNIWILL10242	13
#घोषणा CUT_ACER1280		14
#घोषणा CUT_COMPAL1400_1	15
#घोषणा CUT_COMPAL1400_2	16
#घोषणा CUT_ASUSA2H_1		17
#घोषणा CUT_ASUSA2H_2		18
#घोषणा CUT_UNKNOWNLCD		19
#घोषणा CUT_AOP8060		20
#घोषणा CUT_PANEL856		21

काष्ठा SiS_Private
अणु
	अचिन्हित अक्षर			ChipType;
	अचिन्हित अक्षर			ChipRevision;
	व्योम				*ivideo;
	अचिन्हित अक्षर 			*VirtualRomBase;
	bool				UseROM;
	अचिन्हित अक्षर SISIOMEMTYPE	*VideoMemoryAddress;
	अचिन्हित पूर्णांक			VideoMemorySize;
	SISIOADDRESS			IOAddress;
	SISIOADDRESS			IOAddress2;  /* For dual chip XGI volari */

	SISIOADDRESS			RelIO;
	SISIOADDRESS			SiS_P3c4;
	SISIOADDRESS			SiS_P3d4;
	SISIOADDRESS			SiS_P3c0;
	SISIOADDRESS			SiS_P3ce;
	SISIOADDRESS			SiS_P3c2;
	SISIOADDRESS			SiS_P3ca;
	SISIOADDRESS			SiS_P3c6;
	SISIOADDRESS			SiS_P3c7;
	SISIOADDRESS			SiS_P3c8;
	SISIOADDRESS			SiS_P3c9;
	SISIOADDRESS			SiS_P3cb;
	SISIOADDRESS			SiS_P3cc;
	SISIOADDRESS			SiS_P3cd;
	SISIOADDRESS			SiS_P3da;
	SISIOADDRESS			SiS_Part1Port;
	SISIOADDRESS			SiS_Part2Port;
	SISIOADDRESS			SiS_Part3Port;
	SISIOADDRESS			SiS_Part4Port;
	SISIOADDRESS			SiS_Part5Port;
	SISIOADDRESS			SiS_VidCapt;
	SISIOADDRESS			SiS_VidPlay;
	अचिन्हित लघु			SiS_IF_DEF_LVDS;
	अचिन्हित लघु			SiS_IF_DEF_CH70xx;
	अचिन्हित लघु			SiS_IF_DEF_CONEX;
	अचिन्हित लघु			SiS_IF_DEF_TRUMPION;
	अचिन्हित लघु			SiS_IF_DEF_DSTN;
	अचिन्हित लघु			SiS_IF_DEF_FSTN;
	अचिन्हित लघु			SiS_SysFlags;
	अचिन्हित अक्षर			SiS_VGAINFO;
	bool				SiS_UseROM;
	bool				SiS_ROMNew;
	bool				SiS_XGIROM;
	bool				SiS_NeedRomModeData;
	bool				PanelSelfDetected;
	bool				DDCPortMixup;
	पूर्णांक				SiS_CHOverScan;
	bool				SiS_CHSOverScan;
	bool				SiS_ChSW;
	bool				SiS_UseLCDA;
	पूर्णांक				SiS_UseOEM;
	अचिन्हित पूर्णांक			SiS_CustomT;
	पूर्णांक				SiS_UseWide, SiS_UseWideCRT2;
	पूर्णांक				SiS_TVBlue;
	अचिन्हित लघु			SiS_Backup70xx;
	bool				HaveEMI;
	bool				HaveEMILCD;
	bool				OverruleEMI;
	अचिन्हित अक्षर			EMI_30,EMI_31,EMI_32,EMI_33;
	अचिन्हित लघु			SiS_EMIOffset;
	अचिन्हित लघु			SiS_PWDOffset;
	लघु				PDC, PDCA;
	अचिन्हित अक्षर			SiS_MyCR63;
	अचिन्हित लघु			SiS_CRT1Mode;
	अचिन्हित लघु			SiS_flag_clearbuffer;
	पूर्णांक				SiS_RAMType;
	अचिन्हित अक्षर			SiS_ChannelAB;
	अचिन्हित अक्षर			SiS_DataBusWidth;
	अचिन्हित लघु			SiS_ModeType;
	अचिन्हित लघु			SiS_VBInfo;
	अचिन्हित लघु			SiS_TVMode;
	अचिन्हित लघु			SiS_LCDResInfo;
	अचिन्हित लघु			SiS_LCDTypeInfo;
	अचिन्हित लघु			SiS_LCDInfo;
	अचिन्हित लघु			SiS_LCDInfo661;
	अचिन्हित लघु			SiS_VBType;
	अचिन्हित लघु			SiS_VBExtInfo;
	अचिन्हित लघु			SiS_YPbPr;
	अचिन्हित लघु			SiS_SelectCRT2Rate;
	अचिन्हित लघु			SiS_SetFlag;
	अचिन्हित लघु			SiS_RVBHCFACT;
	अचिन्हित लघु			SiS_RVBHCMAX;
	अचिन्हित लघु			SiS_RVBHRS;
	अचिन्हित लघु			SiS_RVBHRS2;
	अचिन्हित लघु			SiS_VGAVT;
	अचिन्हित लघु			SiS_VGAHT;
	अचिन्हित लघु			SiS_VT;
	अचिन्हित लघु			SiS_HT;
	अचिन्हित लघु			SiS_VGAVDE;
	अचिन्हित लघु			SiS_VGAHDE;
	अचिन्हित लघु			SiS_VDE;
	अचिन्हित लघु			SiS_HDE;
	अचिन्हित लघु			SiS_NewFlickerMode;
	अचिन्हित लघु			SiS_RY1COE;
	अचिन्हित लघु			SiS_RY2COE;
	अचिन्हित लघु			SiS_RY3COE;
	अचिन्हित लघु			SiS_RY4COE;
	अचिन्हित लघु			SiS_LCDHDES;
	अचिन्हित लघु			SiS_LCDVDES;
	SISIOADDRESS			SiS_DDC_Port;
	अचिन्हित लघु			SiS_DDC_Index;
	अचिन्हित लघु			SiS_DDC_Data;
	अचिन्हित लघु			SiS_DDC_NData;
	अचिन्हित लघु			SiS_DDC_Clk;
	अचिन्हित लघु			SiS_DDC_NClk;
	अचिन्हित लघु			SiS_DDC_DeviceAddr;
	अचिन्हित लघु			SiS_DDC_ReadAddr;
	अचिन्हित लघु			SiS_DDC_SecAddr;
	अचिन्हित लघु			SiS_ChrontelInit;
	bool				SiS_SensibleSR11;
	अचिन्हित लघु			SiS661LCD2TableSize;

	अचिन्हित लघु			SiS_PanelMinLVDS;
	अचिन्हित लघु			SiS_PanelMin301;

	स्थिर काष्ठा SiS_St		*SiS_SModeIDTable;
	स्थिर काष्ठा SiS_StandTable_S	*SiS_StandTable;
	स्थिर काष्ठा SiS_Ext		*SiS_EModeIDTable;
	स्थिर काष्ठा SiS_Ext2		*SiS_RefIndex;
	स्थिर काष्ठा SiS_VBMode		*SiS_VBModeIDTable;
	स्थिर काष्ठा SiS_CRT1Table	*SiS_CRT1Table;
	स्थिर काष्ठा SiS_MCLKData	*SiS_MCLKData_0;
	स्थिर काष्ठा SiS_MCLKData	*SiS_MCLKData_1;
	काष्ठा SiS_VCLKData		*SiS_VCLKData;
	काष्ठा SiS_VBVCLKData		*SiS_VBVCLKData;
	स्थिर काष्ठा SiS_StResInfo_S	*SiS_StResInfo;
	स्थिर काष्ठा SiS_ModeResInfo_S	*SiS_ModeResInfo;

	स्थिर अचिन्हित अक्षर		*pSiS_OutputSelect;
	स्थिर अचिन्हित अक्षर		*pSiS_SoftSetting;

	स्थिर अचिन्हित अक्षर		*SiS_SR15;

	स्थिर काष्ठा SiS_PanelDelayTbl	*SiS_PanelDelayTbl;
	स्थिर काष्ठा SiS_PanelDelayTbl	*SiS_PanelDelayTblLVDS;

	/* SiS bridge */

	स्थिर काष्ठा SiS_LCDData	*SiS_ExtLCD1024x768Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_St2LCD1024x768Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1280x720Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_StLCD1280x768_2Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_ExtLCD1280x768_2Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1280x800Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1280x800_2Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1280x854Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1280x960Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_ExtLCD1280x1024Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_St2LCD1280x1024Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_StLCD1400x1050Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_ExtLCD1400x1050Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_StLCD1600x1200Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_ExtLCD1600x1200Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_LCD1680x1050Data;
	स्थिर काष्ठा SiS_LCDData	*SiS_NoScaleData;
	स्थिर काष्ठा SiS_TVData		*SiS_StPALData;
	स्थिर काष्ठा SiS_TVData		*SiS_ExtPALData;
	स्थिर काष्ठा SiS_TVData		*SiS_StNTSCData;
	स्थिर काष्ठा SiS_TVData		*SiS_ExtNTSCData;
	स्थिर काष्ठा SiS_TVData		*SiS_St1HiTVData;
	स्थिर काष्ठा SiS_TVData		*SiS_St2HiTVData;
	स्थिर काष्ठा SiS_TVData		*SiS_ExtHiTVData;
	स्थिर काष्ठा SiS_TVData		*SiS_St525iData;
	स्थिर काष्ठा SiS_TVData		*SiS_St525pData;
	स्थिर काष्ठा SiS_TVData		*SiS_St750pData;
	स्थिर काष्ठा SiS_TVData		*SiS_Ext525iData;
	स्थिर काष्ठा SiS_TVData		*SiS_Ext525pData;
	स्थिर काष्ठा SiS_TVData		*SiS_Ext750pData;
	स्थिर अचिन्हित अक्षर		*SiS_NTSCTiming;
	स्थिर अचिन्हित अक्षर		*SiS_PALTiming;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVExtTiming;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVSt1Timing;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVSt2Timing;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVGroup3Data;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVGroup3Simu;
#अगर 0
	स्थिर अचिन्हित अक्षर		*SiS_HiTVTextTiming;
	स्थिर अचिन्हित अक्षर		*SiS_HiTVGroup3Text;
#पूर्ण_अगर

	स्थिर काष्ठा SiS_Part2PortTbl	*SiS_CRT2Part2_1024x768_1;
	स्थिर काष्ठा SiS_Part2PortTbl	*SiS_CRT2Part2_1024x768_2;
	स्थिर काष्ठा SiS_Part2PortTbl	*SiS_CRT2Part2_1024x768_3;

	/* LVDS, Chrontel */

	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS320x240Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS320x240Data_2;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS640x480Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS800x600Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS1024x600Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS1024x768Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDSBARCO1366Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDSBARCO1366Data_2;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDSBARCO1024Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS848x480Data_1;
	स्थिर काष्ठा SiS_LVDSData	*SiS_LVDS848x480Data_2;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVUNTSCData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVONTSCData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVUPALData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVOPALData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVUPALMData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVOPALMData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVUPALNData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVOPALNData;
	स्थिर काष्ठा SiS_LVDSData	*SiS_CHTVSOPALData;

	स्थिर काष्ठा SiS_LVDSDes	*SiS_PanelType04_1a;
	स्थिर काष्ठा SiS_LVDSDes	*SiS_PanelType04_2a;
	स्थिर काष्ठा SiS_LVDSDes	*SiS_PanelType04_1b;
	स्थिर काष्ठा SiS_LVDSDes	*SiS_PanelType04_2b;

	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1320x240_1;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1320x240_2;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1320x240_2_H;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1320x240_3;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1320x240_3_H;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1640x480_1;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_LVDSCRT1640x480_1_H;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_CHTVCRT1UNTSC;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_CHTVCRT1ONTSC;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_CHTVCRT1UPAL;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_CHTVCRT1OPAL;
	स्थिर काष्ठा SiS_LVDSCRT1Data	*SiS_CHTVCRT1SOPAL;

	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_UNTSC;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_ONTSC;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_UPAL;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_OPAL;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_UPALM;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_OPALM;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_UPALN;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_OPALN;
	स्थिर काष्ठा SiS_CHTVRegData	*SiS_CHTVReg_SOPAL;

	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKUNTSC;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKONTSC;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKUPAL;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKOPAL;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKUPALM;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKOPALM;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKUPALN;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKOPALN;
	स्थिर अचिन्हित अक्षर		*SiS_CHTVVCLKSOPAL;

	अचिन्हित लघु			PanelXRes, PanelHT;
	अचिन्हित लघु			PanelYRes, PanelVT;
	अचिन्हित लघु			PanelHRS,  PanelHRE;
	अचिन्हित लघु			PanelVRS,  PanelVRE;
	अचिन्हित लघु			PanelVCLKIdx300;
	अचिन्हित लघु			PanelVCLKIdx315;
	bool				Alternate1600x1200;

	bool				UseCustomMode;
	bool				CRT1UsesCustomMode;
	अचिन्हित लघु			CHDisplay;
	अचिन्हित लघु			CHSyncStart;
	अचिन्हित लघु			CHSyncEnd;
	अचिन्हित लघु			CHTotal;
	अचिन्हित लघु			CHBlankStart;
	अचिन्हित लघु			CHBlankEnd;
	अचिन्हित लघु			CVDisplay;
	अचिन्हित लघु			CVSyncStart;
	अचिन्हित लघु			CVSyncEnd;
	अचिन्हित लघु			CVTotal;
	अचिन्हित लघु			CVBlankStart;
	अचिन्हित लघु			CVBlankEnd;
	अचिन्हित पूर्णांक			CDClock;
	अचिन्हित पूर्णांक			CFlags;
	अचिन्हित अक्षर			CCRT1CRTC[17];
	अचिन्हित अक्षर			CSR2B;
	अचिन्हित अक्षर			CSR2C;
	अचिन्हित लघु			CSRClock;
	अचिन्हित लघु			CSRClock_CRT1;
	अचिन्हित लघु			CModeFlag;
	अचिन्हित लघु			CModeFlag_CRT1;
	अचिन्हित लघु			CInfoFlag;

	पूर्णांक				LVDSHL;

	bool				Backup;
	अचिन्हित अक्षर			Backup_Mode;
	अचिन्हित अक्षर			Backup_14;
	अचिन्हित अक्षर			Backup_15;
	अचिन्हित अक्षर			Backup_16;
	अचिन्हित अक्षर			Backup_17;
	अचिन्हित अक्षर			Backup_18;
	अचिन्हित अक्षर			Backup_19;
	अचिन्हित अक्षर			Backup_1a;
	अचिन्हित अक्षर			Backup_1b;
	अचिन्हित अक्षर			Backup_1c;
	अचिन्हित अक्षर			Backup_1d;

	अचिन्हित अक्षर			Init_P4_0E;

	पूर्णांक				UsePanelScaler;
	पूर्णांक				CenterScreen;

	अचिन्हित लघु			CP_Venकरोr, CP_Product;
	bool				CP_HaveCustomData;
	पूर्णांक				CP_PreferredX, CP_PreferredY, CP_PreferredIndex;
	पूर्णांक				CP_MaxX, CP_MaxY, CP_MaxClock;
	अचिन्हित अक्षर			CP_PrefSR2B, CP_PrefSR2C;
	अचिन्हित लघु			CP_PrefClock;
	bool				CP_Supports64048075;
	पूर्णांक				CP_HDisplay[7], CP_VDisplay[7];	/* For Custom LCD panel dimensions */
	पूर्णांक				CP_HTotal[7], CP_VTotal[7];
	पूर्णांक				CP_HSyncStart[7], CP_VSyncStart[7];
	पूर्णांक				CP_HSyncEnd[7], CP_VSyncEnd[7];
	पूर्णांक				CP_HBlankStart[7], CP_VBlankStart[7];
	पूर्णांक				CP_HBlankEnd[7], CP_VBlankEnd[7];
	पूर्णांक				CP_Clock[7];
	bool				CP_DataValid[7];
	bool				CP_HSync_P[7], CP_VSync_P[7], CP_SyncValid[7];
पूर्ण;

#पूर्ण_अगर

