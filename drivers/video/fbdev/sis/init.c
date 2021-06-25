<शैली गुरु>
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * Mode initializing code (CRT1 section) क्रम
 * क्रम SiS 300/305/540/630/730,
 *     SiS 315/550/[M]650/651/[M]661[FGM]X/[M]74x[GX]/330/[M]76x[GX],
 *     XGI Volari V3XT/V5/V8, Z7
 * (Universal module क्रम Linux kernel framebuffer and X.org/XFree86 4.x)
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
 * Formerly based on non-functional code-fragements क्रम 300 series by SiS, Inc.
 * Used by permission.
 */

#समावेश "init.h"

#अगर_घोषित CONFIG_FB_SIS_300
#समावेश "300vtbl.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
#समावेश "310vtbl.h"
#पूर्ण_अगर

#अगर defined(ALLOC_PRAGMA)
#आशय alloc_text(PAGE,SiSSetMode)
#पूर्ण_अगर

/*********************************************/
/*         POINTER INITIALIZATION            */
/*********************************************/

#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
अटल व्योम
InitCommonPoपूर्णांकer(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_Pr->SiS_SModeIDTable  = SiS_SModeIDTable;
   SiS_Pr->SiS_StResInfo     = SiS_StResInfo;
   SiS_Pr->SiS_ModeResInfo   = SiS_ModeResInfo;
   SiS_Pr->SiS_StandTable    = SiS_StandTable;

   SiS_Pr->SiS_NTSCTiming     = SiS_NTSCTiming;
   SiS_Pr->SiS_PALTiming      = SiS_PALTiming;
   SiS_Pr->SiS_HiTVSt1Timing  = SiS_HiTVSt1Timing;
   SiS_Pr->SiS_HiTVSt2Timing  = SiS_HiTVSt2Timing;

   SiS_Pr->SiS_HiTVExtTiming  = SiS_HiTVExtTiming;
   SiS_Pr->SiS_HiTVGroup3Data = SiS_HiTVGroup3Data;
   SiS_Pr->SiS_HiTVGroup3Simu = SiS_HiTVGroup3Simu;
#अगर 0
   SiS_Pr->SiS_HiTVTextTiming = SiS_HiTVTextTiming;
   SiS_Pr->SiS_HiTVGroup3Text = SiS_HiTVGroup3Text;
#पूर्ण_अगर

   SiS_Pr->SiS_StPALData   = SiS_StPALData;
   SiS_Pr->SiS_ExtPALData  = SiS_ExtPALData;
   SiS_Pr->SiS_StNTSCData  = SiS_StNTSCData;
   SiS_Pr->SiS_ExtNTSCData = SiS_ExtNTSCData;
   SiS_Pr->SiS_St1HiTVData = SiS_StHiTVData;
   SiS_Pr->SiS_St2HiTVData = SiS_St2HiTVData;
   SiS_Pr->SiS_ExtHiTVData = SiS_ExtHiTVData;
   SiS_Pr->SiS_St525iData  = SiS_StNTSCData;
   SiS_Pr->SiS_St525pData  = SiS_St525pData;
   SiS_Pr->SiS_St750pData  = SiS_St750pData;
   SiS_Pr->SiS_Ext525iData = SiS_ExtNTSCData;
   SiS_Pr->SiS_Ext525pData = SiS_ExtNTSCData;
   SiS_Pr->SiS_Ext750pData = SiS_Ext750pData;

   SiS_Pr->pSiS_OutputSelect = &SiS_OutputSelect;
   SiS_Pr->pSiS_SoftSetting  = &SiS_SoftSetting;

   SiS_Pr->SiS_LCD1280x720Data      = SiS_LCD1280x720Data;
   SiS_Pr->SiS_StLCD1280x768_2Data  = SiS_StLCD1280x768_2Data;
   SiS_Pr->SiS_ExtLCD1280x768_2Data = SiS_ExtLCD1280x768_2Data;
   SiS_Pr->SiS_LCD1280x800Data      = SiS_LCD1280x800Data;
   SiS_Pr->SiS_LCD1280x800_2Data    = SiS_LCD1280x800_2Data;
   SiS_Pr->SiS_LCD1280x854Data      = SiS_LCD1280x854Data;
   SiS_Pr->SiS_LCD1280x960Data      = SiS_LCD1280x960Data;
   SiS_Pr->SiS_StLCD1400x1050Data   = SiS_StLCD1400x1050Data;
   SiS_Pr->SiS_ExtLCD1400x1050Data  = SiS_ExtLCD1400x1050Data;
   SiS_Pr->SiS_LCD1680x1050Data     = SiS_LCD1680x1050Data;
   SiS_Pr->SiS_StLCD1600x1200Data   = SiS_StLCD1600x1200Data;
   SiS_Pr->SiS_ExtLCD1600x1200Data  = SiS_ExtLCD1600x1200Data;
   SiS_Pr->SiS_NoScaleData          = SiS_NoScaleData;

   SiS_Pr->SiS_LVDS320x240Data_1   = SiS_LVDS320x240Data_1;
   SiS_Pr->SiS_LVDS320x240Data_2   = SiS_LVDS320x240Data_2;
   SiS_Pr->SiS_LVDS640x480Data_1   = SiS_LVDS640x480Data_1;
   SiS_Pr->SiS_LVDS800x600Data_1   = SiS_LVDS800x600Data_1;
   SiS_Pr->SiS_LVDS1024x600Data_1  = SiS_LVDS1024x600Data_1;
   SiS_Pr->SiS_LVDS1024x768Data_1  = SiS_LVDS1024x768Data_1;

   SiS_Pr->SiS_LVDSCRT1320x240_1     = SiS_LVDSCRT1320x240_1;
   SiS_Pr->SiS_LVDSCRT1320x240_2     = SiS_LVDSCRT1320x240_2;
   SiS_Pr->SiS_LVDSCRT1320x240_2_H   = SiS_LVDSCRT1320x240_2_H;
   SiS_Pr->SiS_LVDSCRT1320x240_3     = SiS_LVDSCRT1320x240_3;
   SiS_Pr->SiS_LVDSCRT1320x240_3_H   = SiS_LVDSCRT1320x240_3_H;
   SiS_Pr->SiS_LVDSCRT1640x480_1     = SiS_LVDSCRT1640x480_1;
   SiS_Pr->SiS_LVDSCRT1640x480_1_H   = SiS_LVDSCRT1640x480_1_H;
#अगर 0
   SiS_Pr->SiS_LVDSCRT11024x600_1    = SiS_LVDSCRT11024x600_1;
   SiS_Pr->SiS_LVDSCRT11024x600_1_H  = SiS_LVDSCRT11024x600_1_H;
   SiS_Pr->SiS_LVDSCRT11024x600_2    = SiS_LVDSCRT11024x600_2;
   SiS_Pr->SiS_LVDSCRT11024x600_2_H  = SiS_LVDSCRT11024x600_2_H;
#पूर्ण_अगर

   SiS_Pr->SiS_CHTVUNTSCData = SiS_CHTVUNTSCData;
   SiS_Pr->SiS_CHTVONTSCData = SiS_CHTVONTSCData;

   SiS_Pr->SiS_PanelMinLVDS   = Panel_800x600;    /* lowest value LVDS/LCDA */
   SiS_Pr->SiS_PanelMin301    = Panel_1024x768;   /* lowest value 301 */
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_300
अटल व्योम
InitTo300Poपूर्णांकer(काष्ठा SiS_Private *SiS_Pr)
अणु
   InitCommonPoपूर्णांकer(SiS_Pr);

   SiS_Pr->SiS_VBModeIDTable = SiS300_VBModeIDTable;
   SiS_Pr->SiS_EModeIDTable  = SiS300_EModeIDTable;
   SiS_Pr->SiS_RefIndex      = SiS300_RefIndex;
   SiS_Pr->SiS_CRT1Table     = SiS300_CRT1Table;
   अगर(SiS_Pr->ChipType == SIS_300) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS300_MCLKData_300; /* 300 */
   पूर्ण अन्यथा अणु
      SiS_Pr->SiS_MCLKData_0 = SiS300_MCLKData_630; /* 630, 730 */
   पूर्ण
   SiS_Pr->SiS_VCLKData      = SiS300_VCLKData;
   SiS_Pr->SiS_VBVCLKData    = (काष्ठा SiS_VBVCLKData *)SiS300_VCLKData;

   SiS_Pr->SiS_SR15  = SiS300_SR15;

   SiS_Pr->SiS_PanelDelayTbl     = SiS300_PanelDelayTbl;
   SiS_Pr->SiS_PanelDelayTblLVDS = SiS300_PanelDelayTbl;

   SiS_Pr->SiS_ExtLCD1024x768Data   = SiS300_ExtLCD1024x768Data;
   SiS_Pr->SiS_St2LCD1024x768Data   = SiS300_St2LCD1024x768Data;
   SiS_Pr->SiS_ExtLCD1280x1024Data  = SiS300_ExtLCD1280x1024Data;
   SiS_Pr->SiS_St2LCD1280x1024Data  = SiS300_St2LCD1280x1024Data;

   SiS_Pr->SiS_CRT2Part2_1024x768_1  = SiS300_CRT2Part2_1024x768_1;
   SiS_Pr->SiS_CRT2Part2_1024x768_2  = SiS300_CRT2Part2_1024x768_2;
   SiS_Pr->SiS_CRT2Part2_1024x768_3  = SiS300_CRT2Part2_1024x768_3;

   SiS_Pr->SiS_CHTVUPALData  = SiS300_CHTVUPALData;
   SiS_Pr->SiS_CHTVOPALData  = SiS300_CHTVOPALData;
   SiS_Pr->SiS_CHTVUPALMData = SiS_CHTVUNTSCData;    /* not supported on 300 series */
   SiS_Pr->SiS_CHTVOPALMData = SiS_CHTVONTSCData;    /* not supported on 300 series */
   SiS_Pr->SiS_CHTVUPALNData = SiS300_CHTVUPALData;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVOPALNData = SiS300_CHTVOPALData;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVSOPALData = SiS300_CHTVSOPALData;

   SiS_Pr->SiS_LVDS848x480Data_1   = SiS300_LVDS848x480Data_1;
   SiS_Pr->SiS_LVDS848x480Data_2   = SiS300_LVDS848x480Data_2;
   SiS_Pr->SiS_LVDSBARCO1024Data_1 = SiS300_LVDSBARCO1024Data_1;
   SiS_Pr->SiS_LVDSBARCO1366Data_1 = SiS300_LVDSBARCO1366Data_1;
   SiS_Pr->SiS_LVDSBARCO1366Data_2 = SiS300_LVDSBARCO1366Data_2;

   SiS_Pr->SiS_PanelType04_1a = SiS300_PanelType04_1a;
   SiS_Pr->SiS_PanelType04_2a = SiS300_PanelType04_2a;
   SiS_Pr->SiS_PanelType04_1b = SiS300_PanelType04_1b;
   SiS_Pr->SiS_PanelType04_2b = SiS300_PanelType04_2b;

   SiS_Pr->SiS_CHTVCRT1UNTSC = SiS300_CHTVCRT1UNTSC;
   SiS_Pr->SiS_CHTVCRT1ONTSC = SiS300_CHTVCRT1ONTSC;
   SiS_Pr->SiS_CHTVCRT1UPAL  = SiS300_CHTVCRT1UPAL;
   SiS_Pr->SiS_CHTVCRT1OPAL  = SiS300_CHTVCRT1OPAL;
   SiS_Pr->SiS_CHTVCRT1SOPAL = SiS300_CHTVCRT1SOPAL;
   SiS_Pr->SiS_CHTVReg_UNTSC = SiS300_CHTVReg_UNTSC;
   SiS_Pr->SiS_CHTVReg_ONTSC = SiS300_CHTVReg_ONTSC;
   SiS_Pr->SiS_CHTVReg_UPAL  = SiS300_CHTVReg_UPAL;
   SiS_Pr->SiS_CHTVReg_OPAL  = SiS300_CHTVReg_OPAL;
   SiS_Pr->SiS_CHTVReg_UPALM = SiS300_CHTVReg_UNTSC;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVReg_OPALM = SiS300_CHTVReg_ONTSC;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVReg_UPALN = SiS300_CHTVReg_UPAL;   /* not supported on 300 series */
   SiS_Pr->SiS_CHTVReg_OPALN = SiS300_CHTVReg_OPAL;   /* not supported on 300 series */
   SiS_Pr->SiS_CHTVReg_SOPAL = SiS300_CHTVReg_SOPAL;
   SiS_Pr->SiS_CHTVVCLKUNTSC = SiS300_CHTVVCLKUNTSC;
   SiS_Pr->SiS_CHTVVCLKONTSC = SiS300_CHTVVCLKONTSC;
   SiS_Pr->SiS_CHTVVCLKUPAL  = SiS300_CHTVVCLKUPAL;
   SiS_Pr->SiS_CHTVVCLKOPAL  = SiS300_CHTVVCLKOPAL;
   SiS_Pr->SiS_CHTVVCLKUPALM = SiS300_CHTVVCLKUNTSC;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVVCLKOPALM = SiS300_CHTVVCLKONTSC;  /* not supported on 300 series */
   SiS_Pr->SiS_CHTVVCLKUPALN = SiS300_CHTVVCLKUPAL;   /* not supported on 300 series */
   SiS_Pr->SiS_CHTVVCLKOPALN = SiS300_CHTVVCLKOPAL;   /* not supported on 300 series */
   SiS_Pr->SiS_CHTVVCLKSOPAL = SiS300_CHTVVCLKSOPAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
InitTo310Poपूर्णांकer(काष्ठा SiS_Private *SiS_Pr)
अणु
   InitCommonPoपूर्णांकer(SiS_Pr);

   SiS_Pr->SiS_EModeIDTable  = SiS310_EModeIDTable;
   SiS_Pr->SiS_RefIndex      = SiS310_RefIndex;
   SiS_Pr->SiS_CRT1Table     = SiS310_CRT1Table;
   अगर(SiS_Pr->ChipType >= SIS_340) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_340;  /* 340 + XGI */
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_761) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_761;  /* 761 - preliminary */
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_760) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_760;  /* 760 */
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_660;  /* 661/741 */
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType == SIS_330) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_330;  /* 330 */
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType > SIS_315PRO) अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_650;  /* 550, 650, 740 */
   पूर्ण अन्यथा अणु
      SiS_Pr->SiS_MCLKData_0 = SiS310_MCLKData_0_315;  /* 315 */
   पूर्ण
   अगर(SiS_Pr->ChipType >= SIS_340) अणु
      SiS_Pr->SiS_MCLKData_1 = SiS310_MCLKData_1_340;
   पूर्ण अन्यथा अणु
      SiS_Pr->SiS_MCLKData_1 = SiS310_MCLKData_1;
   पूर्ण
   SiS_Pr->SiS_VCLKData      = SiS310_VCLKData;
   SiS_Pr->SiS_VBVCLKData    = SiS310_VBVCLKData;

   SiS_Pr->SiS_SR15  = SiS310_SR15;

   SiS_Pr->SiS_PanelDelayTbl     = SiS310_PanelDelayTbl;
   SiS_Pr->SiS_PanelDelayTblLVDS = SiS310_PanelDelayTblLVDS;

   SiS_Pr->SiS_St2LCD1024x768Data   = SiS310_St2LCD1024x768Data;
   SiS_Pr->SiS_ExtLCD1024x768Data   = SiS310_ExtLCD1024x768Data;
   SiS_Pr->SiS_St2LCD1280x1024Data  = SiS310_St2LCD1280x1024Data;
   SiS_Pr->SiS_ExtLCD1280x1024Data  = SiS310_ExtLCD1280x1024Data;

   SiS_Pr->SiS_CRT2Part2_1024x768_1  = SiS310_CRT2Part2_1024x768_1;

   SiS_Pr->SiS_CHTVUPALData  = SiS310_CHTVUPALData;
   SiS_Pr->SiS_CHTVOPALData  = SiS310_CHTVOPALData;
   SiS_Pr->SiS_CHTVUPALMData = SiS310_CHTVUPALMData;
   SiS_Pr->SiS_CHTVOPALMData = SiS310_CHTVOPALMData;
   SiS_Pr->SiS_CHTVUPALNData = SiS310_CHTVUPALNData;
   SiS_Pr->SiS_CHTVOPALNData = SiS310_CHTVOPALNData;
   SiS_Pr->SiS_CHTVSOPALData = SiS310_CHTVSOPALData;

   SiS_Pr->SiS_CHTVCRT1UNTSC = SiS310_CHTVCRT1UNTSC;
   SiS_Pr->SiS_CHTVCRT1ONTSC = SiS310_CHTVCRT1ONTSC;
   SiS_Pr->SiS_CHTVCRT1UPAL  = SiS310_CHTVCRT1UPAL;
   SiS_Pr->SiS_CHTVCRT1OPAL  = SiS310_CHTVCRT1OPAL;
   SiS_Pr->SiS_CHTVCRT1SOPAL = SiS310_CHTVCRT1OPAL;

   SiS_Pr->SiS_CHTVReg_UNTSC = SiS310_CHTVReg_UNTSC;
   SiS_Pr->SiS_CHTVReg_ONTSC = SiS310_CHTVReg_ONTSC;
   SiS_Pr->SiS_CHTVReg_UPAL  = SiS310_CHTVReg_UPAL;
   SiS_Pr->SiS_CHTVReg_OPAL  = SiS310_CHTVReg_OPAL;
   SiS_Pr->SiS_CHTVReg_UPALM = SiS310_CHTVReg_UPALM;
   SiS_Pr->SiS_CHTVReg_OPALM = SiS310_CHTVReg_OPALM;
   SiS_Pr->SiS_CHTVReg_UPALN = SiS310_CHTVReg_UPALN;
   SiS_Pr->SiS_CHTVReg_OPALN = SiS310_CHTVReg_OPALN;
   SiS_Pr->SiS_CHTVReg_SOPAL = SiS310_CHTVReg_OPAL;

   SiS_Pr->SiS_CHTVVCLKUNTSC = SiS310_CHTVVCLKUNTSC;
   SiS_Pr->SiS_CHTVVCLKONTSC = SiS310_CHTVVCLKONTSC;
   SiS_Pr->SiS_CHTVVCLKUPAL  = SiS310_CHTVVCLKUPAL;
   SiS_Pr->SiS_CHTVVCLKOPAL  = SiS310_CHTVVCLKOPAL;
   SiS_Pr->SiS_CHTVVCLKUPALM = SiS310_CHTVVCLKUPALM;
   SiS_Pr->SiS_CHTVVCLKOPALM = SiS310_CHTVVCLKOPALM;
   SiS_Pr->SiS_CHTVVCLKUPALN = SiS310_CHTVVCLKUPALN;
   SiS_Pr->SiS_CHTVVCLKOPALN = SiS310_CHTVVCLKOPALN;
   SiS_Pr->SiS_CHTVVCLKSOPAL = SiS310_CHTVVCLKOPAL;
पूर्ण
#पूर्ण_अगर

bool
SiSInitPtr(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      InitTo300Poपूर्णांकer(SiS_Pr);
#अन्यथा
      वापस false;
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
      InitTo310Poपूर्णांकer(SiS_Pr);
#अन्यथा
      वापस false;
#पूर्ण_अगर
   पूर्ण
   वापस true;
पूर्ण

/*********************************************/
/*            HELPER: Get ModeID             */
/*********************************************/

अटल
अचिन्हित लघु
SiS_GetModeID(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay, पूर्णांक VDisplay,
		पूर्णांक Depth, bool FSTN, पूर्णांक LCDwidth, पूर्णांक LCDheight)
अणु
   अचिन्हित लघु ModeIndex = 0;

   चयन(HDisplay)
   अणु
	हाल 320:
		अगर(VDisplay == 200) ModeIndex = ModeIndex_320x200[Depth];
		अन्यथा अगर(VDisplay == 240) अणु
			अगर((VBFlags & CRT2_LCD) && (FSTN))
				ModeIndex = ModeIndex_320x240_FSTN[Depth];
			अन्यथा
				ModeIndex = ModeIndex_320x240[Depth];
		पूर्ण
		अवरोध;
	हाल 400:
		अगर((!(VBFlags & CRT1_LCDA)) || ((LCDwidth >= 800) && (LCDwidth >= 600))) अणु
			अगर(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
		पूर्ण
		अवरोध;
	हाल 512:
		अगर((!(VBFlags & CRT1_LCDA)) || ((LCDwidth >= 1024) && (LCDwidth >= 768))) अणु
			अगर(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
		पूर्ण
		अवरोध;
	हाल 640:
		अगर(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
		अन्यथा अगर(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
		अवरोध;
	हाल 720:
		अगर(VDisplay == 480)      ModeIndex = ModeIndex_720x480[Depth];
		अन्यथा अगर(VDisplay == 576) ModeIndex = ModeIndex_720x576[Depth];
		अवरोध;
	हाल 768:
		अगर(VDisplay == 576) ModeIndex = ModeIndex_768x576[Depth];
		अवरोध;
	हाल 800:
		अगर(VDisplay == 600)      ModeIndex = ModeIndex_800x600[Depth];
		अन्यथा अगर(VDisplay == 480) ModeIndex = ModeIndex_800x480[Depth];
		अवरोध;
	हाल 848:
		अगर(VDisplay == 480) ModeIndex = ModeIndex_848x480[Depth];
		अवरोध;
	हाल 856:
		अगर(VDisplay == 480) ModeIndex = ModeIndex_856x480[Depth];
		अवरोध;
	हाल 960:
		अगर(VGAEngine == SIS_315_VGA) अणु
			अगर(VDisplay == 540)      ModeIndex = ModeIndex_960x540[Depth];
			अन्यथा अगर(VDisplay == 600) ModeIndex = ModeIndex_960x600[Depth];
		पूर्ण
		अवरोध;
	हाल 1024:
		अगर(VDisplay == 576)      ModeIndex = ModeIndex_1024x576[Depth];
		अन्यथा अगर(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
		अन्यथा अगर(VGAEngine == SIS_300_VGA) अणु
			अगर(VDisplay == 600) ModeIndex = ModeIndex_1024x600[Depth];
		पूर्ण
		अवरोध;
	हाल 1152:
		अगर(VDisplay == 864) ModeIndex = ModeIndex_1152x864[Depth];
		अगर(VGAEngine == SIS_300_VGA) अणु
			अगर(VDisplay == 768) ModeIndex = ModeIndex_1152x768[Depth];
		पूर्ण
		अवरोध;
	हाल 1280:
		चयन(VDisplay) अणु
			हाल 720:
				ModeIndex = ModeIndex_1280x720[Depth];
				अवरोध;
			हाल 768:
				अगर(VGAEngine == SIS_300_VGA) अणु
					ModeIndex = ModeIndex_300_1280x768[Depth];
				पूर्ण अन्यथा अणु
					ModeIndex = ModeIndex_310_1280x768[Depth];
				पूर्ण
				अवरोध;
			हाल 800:
				अगर(VGAEngine == SIS_315_VGA) अणु
					ModeIndex = ModeIndex_1280x800[Depth];
				पूर्ण
				अवरोध;
			हाल 854:
				अगर(VGAEngine == SIS_315_VGA) अणु
					ModeIndex = ModeIndex_1280x854[Depth];
				पूर्ण
				अवरोध;
			हाल 960:
				ModeIndex = ModeIndex_1280x960[Depth];
				अवरोध;
			हाल 1024:
				ModeIndex = ModeIndex_1280x1024[Depth];
				अवरोध;
		पूर्ण
		अवरोध;
	हाल 1360:
		अगर(VDisplay == 768) ModeIndex = ModeIndex_1360x768[Depth];
		अगर(VGAEngine == SIS_300_VGA) अणु
			अगर(VDisplay == 1024) ModeIndex = ModeIndex_300_1360x1024[Depth];
		पूर्ण
		अवरोध;
	हाल 1400:
		अगर(VGAEngine == SIS_315_VGA) अणु
			अगर(VDisplay == 1050) अणु
				ModeIndex = ModeIndex_1400x1050[Depth];
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 1600:
		अगर(VDisplay == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
		अवरोध;
	हाल 1680:
		अगर(VGAEngine == SIS_315_VGA) अणु
			अगर(VDisplay == 1050) ModeIndex = ModeIndex_1680x1050[Depth];
		पूर्ण
		अवरोध;
	हाल 1920:
		अगर(VDisplay == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
		अन्यथा अगर(VGAEngine == SIS_315_VGA) अणु
			अगर(VDisplay == 1080) ModeIndex = ModeIndex_1920x1080[Depth];
		पूर्ण
		अवरोध;
	हाल 2048:
		अगर(VDisplay == 1536) अणु
			अगर(VGAEngine == SIS_300_VGA) अणु
				ModeIndex = ModeIndex_300_2048x1536[Depth];
			पूर्ण अन्यथा अणु
				ModeIndex = ModeIndex_310_2048x1536[Depth];
			पूर्ण
		पूर्ण
		अवरोध;
   पूर्ण

   वापस ModeIndex;
पूर्ण

अचिन्हित लघु
SiS_GetModeID_LCD(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay, पूर्णांक VDisplay,
		पूर्णांक Depth, bool FSTN, अचिन्हित लघु CustomT, पूर्णांक LCDwidth, पूर्णांक LCDheight,
		अचिन्हित पूर्णांक VBFlags2)
अणु
   अचिन्हित लघु ModeIndex = 0;

   अगर(VBFlags2 & (VB2_LVDS | VB2_30xBDH)) अणु

      चयन(HDisplay)
      अणु
	हाल 320:
	     अगर((CustomT != CUT_PANEL848) && (CustomT != CUT_PANEL856)) अणु
		अगर(VDisplay == 200) अणु
		   अगर(!FSTN) ModeIndex = ModeIndex_320x200[Depth];
		पूर्ण अन्यथा अगर(VDisplay == 240) अणु
		   अगर(!FSTN) ModeIndex = ModeIndex_320x240[Depth];
		   अन्यथा अगर(VGAEngine == SIS_315_VGA) अणु
		      ModeIndex = ModeIndex_320x240_FSTN[Depth];
		   पूर्ण
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 400:
	     अगर((CustomT != CUT_PANEL848) && (CustomT != CUT_PANEL856)) अणु
		अगर(!((VGAEngine == SIS_300_VGA) && (VBFlags2 & VB2_TRUMPION))) अणु
		   अगर(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 512:
	     अगर((CustomT != CUT_PANEL848) && (CustomT != CUT_PANEL856)) अणु
		अगर(!((VGAEngine == SIS_300_VGA) && (VBFlags2 & VB2_TRUMPION))) अणु
		   अगर(LCDwidth >= 1024 && LCDwidth != 1152 && LCDheight >= 768) अणु
		      अगर(VDisplay == 384) अणु
		         ModeIndex = ModeIndex_512x384[Depth];
		      पूर्ण
		   पूर्ण
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 640:
	     अगर(VDisplay == 480) ModeIndex = ModeIndex_640x480[Depth];
	     अन्यथा अगर(VDisplay == 400) अणु
		अगर((CustomT != CUT_PANEL848) && (CustomT != CUT_PANEL856))
		   ModeIndex = ModeIndex_640x400[Depth];
	     पूर्ण
	     अवरोध;
	हाल 800:
	     अगर(VDisplay == 600) ModeIndex = ModeIndex_800x600[Depth];
	     अवरोध;
	हाल 848:
	     अगर(CustomT == CUT_PANEL848) अणु
	        अगर(VDisplay == 480) ModeIndex = ModeIndex_848x480[Depth];
	     पूर्ण
	     अवरोध;
	हाल 856:
	     अगर(CustomT == CUT_PANEL856) अणु
	        अगर(VDisplay == 480) ModeIndex = ModeIndex_856x480[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1024:
	     अगर(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     अन्यथा अगर(VGAEngine == SIS_300_VGA) अणु
		अगर((VDisplay == 600) && (LCDheight == 600)) अणु
		   ModeIndex = ModeIndex_1024x600[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1152:
	     अगर(VGAEngine == SIS_300_VGA) अणु
		अगर((VDisplay == 768) && (LCDheight == 768)) अणु
		   ModeIndex = ModeIndex_1152x768[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
        हाल 1280:
	     अगर(VDisplay == 1024) ModeIndex = ModeIndex_1280x1024[Depth];
	     अन्यथा अगर(VGAEngine == SIS_315_VGA) अणु
		अगर((VDisplay == 768) && (LCDheight == 768)) अणु
		   ModeIndex = ModeIndex_310_1280x768[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1360:
	     अगर(VGAEngine == SIS_300_VGA) अणु
		अगर(CustomT == CUT_BARCO1366) अणु
		   अगर(VDisplay == 1024) ModeIndex = ModeIndex_300_1360x1024[Depth];
		पूर्ण
	     पूर्ण
	     अगर(CustomT == CUT_PANEL848) अणु
		अगर(VDisplay == 768) ModeIndex = ModeIndex_1360x768[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1400:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 1050) ModeIndex = ModeIndex_1400x1050[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1600:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
	     पूर्ण
	     अवरोध;
      पूर्ण

   पूर्ण अन्यथा अगर(VBFlags2 & VB2_SISBRIDGE) अणु

      चयन(HDisplay)
      अणु
	हाल 320:
	     अगर(VDisplay == 200)      ModeIndex = ModeIndex_320x200[Depth];
	     अन्यथा अगर(VDisplay == 240) ModeIndex = ModeIndex_320x240[Depth];
	     अवरोध;
	हाल 400:
	     अगर(LCDwidth >= 800 && LCDheight >= 600) अणु
		अगर(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
	     पूर्ण
	     अवरोध;
	हाल 512:
	     अगर(LCDwidth >= 1024 && LCDheight >= 768 && LCDwidth != 1152) अणु
		अगर(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
	     पूर्ण
	     अवरोध;
	हाल 640:
	     अगर(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     अन्यथा अगर(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
	     अवरोध;
	हाल 720:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 480)      ModeIndex = ModeIndex_720x480[Depth];
		अन्यथा अगर(VDisplay == 576) ModeIndex = ModeIndex_720x576[Depth];
	     पूर्ण
	     अवरोध;
	हाल 768:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 576) ModeIndex = ModeIndex_768x576[Depth];
	     पूर्ण
	     अवरोध;
	हाल 800:
	     अगर(VDisplay == 600) ModeIndex = ModeIndex_800x600[Depth];
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 480) ModeIndex = ModeIndex_800x480[Depth];
	     पूर्ण
	     अवरोध;
	हाल 848:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 480) ModeIndex = ModeIndex_848x480[Depth];
	     पूर्ण
	     अवरोध;
	हाल 856:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 480) ModeIndex = ModeIndex_856x480[Depth];
	     पूर्ण
	     अवरोध;
	हाल 960:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 540)      ModeIndex = ModeIndex_960x540[Depth];
		अन्यथा अगर(VDisplay == 600) ModeIndex = ModeIndex_960x600[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1024:
	     अगर(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 576) ModeIndex = ModeIndex_1024x576[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1152:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 864) ModeIndex = ModeIndex_1152x864[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1280:
	     चयन(VDisplay) अणु
	     हाल 720:
		ModeIndex = ModeIndex_1280x720[Depth];
		अवरोध;
	     हाल 768:
		अगर(VGAEngine == SIS_300_VGA) अणु
		   ModeIndex = ModeIndex_300_1280x768[Depth];
		पूर्ण अन्यथा अणु
		   ModeIndex = ModeIndex_310_1280x768[Depth];
		पूर्ण
		अवरोध;
	     हाल 800:
		अगर(VGAEngine == SIS_315_VGA) अणु
		   ModeIndex = ModeIndex_1280x800[Depth];
		पूर्ण
		अवरोध;
	     हाल 854:
		अगर(VGAEngine == SIS_315_VGA) अणु
		   ModeIndex = ModeIndex_1280x854[Depth];
		पूर्ण
		अवरोध;
	     हाल 960:
		ModeIndex = ModeIndex_1280x960[Depth];
		अवरोध;
	     हाल 1024:
		ModeIndex = ModeIndex_1280x1024[Depth];
		अवरोध;
	     पूर्ण
	     अवरोध;
	हाल 1360:
	     अगर(VGAEngine == SIS_315_VGA) अणु  /* OVER1280 only? */
		अगर(VDisplay == 768) ModeIndex = ModeIndex_1360x768[Depth];
	     पूर्ण
	     अवरोध;
	हाल 1400:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VBFlags2 & VB2_LCDOVER1280BRIDGE) अणु
		   अगर(VDisplay == 1050) ModeIndex = ModeIndex_1400x1050[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1600:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VBFlags2 & VB2_LCDOVER1280BRIDGE) अणु
		   अगर(VDisplay == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
#अगर_अघोषित VB_FORBID_CRT2LCD_OVER_1600
	हाल 1680:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VBFlags2 & VB2_LCDOVER1280BRIDGE) अणु
		   अगर(VDisplay == 1050) ModeIndex = ModeIndex_1680x1050[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1920:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VBFlags2 & VB2_LCDOVER1600BRIDGE) अणु
		   अगर(VDisplay == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 2048:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VBFlags2 & VB2_LCDOVER1600BRIDGE) अणु
		   अगर(VDisplay == 1536) ModeIndex = ModeIndex_310_2048x1536[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
#पूर्ण_अगर
      पूर्ण
   पूर्ण

   वापस ModeIndex;
पूर्ण

अचिन्हित लघु
SiS_GetModeID_TV(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay, पूर्णांक VDisplay, पूर्णांक Depth,
			अचिन्हित पूर्णांक VBFlags2)
अणु
   अचिन्हित लघु ModeIndex = 0;

   अगर(VBFlags2 & VB2_CHRONTEL) अणु

      चयन(HDisplay)
      अणु
	हाल 512:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
	     पूर्ण
	     अवरोध;
	हाल 640:
	     अगर(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     अन्यथा अगर(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
	     अवरोध;
	हाल 800:
	     अगर(VDisplay == 600) ModeIndex = ModeIndex_800x600[Depth];
	     अवरोध;
	हाल 1024:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     पूर्ण
	     अवरोध;
      पूर्ण

   पूर्ण अन्यथा अगर(VBFlags2 & VB2_SISTVBRIDGE) अणु

      चयन(HDisplay)
      अणु
	हाल 320:
	     अगर(VDisplay == 200)      ModeIndex = ModeIndex_320x200[Depth];
	     अन्यथा अगर(VDisplay == 240) ModeIndex = ModeIndex_320x240[Depth];
	     अवरोध;
	हाल 400:
	     अगर(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
	     अवरोध;
	हाल 512:
	     अगर( ((VBFlags & TV_YPBPR) && (VBFlags & (TV_YPBPR750P | TV_YPBPR1080I))) ||
		 (VBFlags & TV_HIVISION) 					      ||
		 ((!(VBFlags & (TV_YPBPR | TV_PALM))) && (VBFlags & TV_PAL)) ) अणु
		अगर(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
	     पूर्ण
	     अवरोध;
	हाल 640:
	     अगर(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     अन्यथा अगर(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
	     अवरोध;
	हाल 720:
	     अगर((!(VBFlags & TV_HIVISION)) && (!((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR1080I)))) अणु
		अगर(VDisplay == 480) अणु
		   ModeIndex = ModeIndex_720x480[Depth];
		पूर्ण अन्यथा अगर(VDisplay == 576) अणु
		   अगर( ((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR750P)) ||
		       ((!(VBFlags & (TV_YPBPR | TV_PALM))) && (VBFlags & TV_PAL)) )
		      ModeIndex = ModeIndex_720x576[Depth];
		पूर्ण
	     पूर्ण
             अवरोध;
	हाल 768:
	     अगर((!(VBFlags & TV_HIVISION)) && (!((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR1080I)))) अणु
		अगर( ((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR750P)) ||
		    ((!(VBFlags & (TV_YPBPR | TV_PALM))) && (VBFlags & TV_PAL)) ) अणु
		   अगर(VDisplay == 576) ModeIndex = ModeIndex_768x576[Depth];
		पूर्ण
             पूर्ण
	     अवरोध;
	हाल 800:
	     अगर(VDisplay == 600) ModeIndex = ModeIndex_800x600[Depth];
	     अन्यथा अगर(VDisplay == 480) अणु
		अगर(!((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR750P))) अणु
		   ModeIndex = ModeIndex_800x480[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 960:
	     अगर(VGAEngine == SIS_315_VGA) अणु
		अगर(VDisplay == 600) अणु
		   अगर((VBFlags & TV_HIVISION) || ((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR1080I))) अणु
		      ModeIndex = ModeIndex_960x600[Depth];
		   पूर्ण
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1024:
	     अगर(VDisplay == 768) अणु
		अगर(VBFlags2 & VB2_30xBLV) अणु
		   ModeIndex = ModeIndex_1024x768[Depth];
		पूर्ण
	     पूर्ण अन्यथा अगर(VDisplay == 576) अणु
		अगर( (VBFlags & TV_HIVISION) ||
		    ((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR1080I)) ||
		    ((VBFlags2 & VB2_30xBLV) &&
		     ((!(VBFlags & (TV_YPBPR | TV_PALM))) && (VBFlags & TV_PAL))) ) अणु
		   ModeIndex = ModeIndex_1024x576[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
	हाल 1280:
	     अगर(VDisplay == 720) अणु
		अगर((VBFlags & TV_HIVISION) ||
		   ((VBFlags & TV_YPBPR) && (VBFlags & (TV_YPBPR1080I | TV_YPBPR750P)))) अणु
		   ModeIndex = ModeIndex_1280x720[Depth];
		पूर्ण
	     पूर्ण अन्यथा अगर(VDisplay == 1024) अणु
		अगर((VBFlags & TV_HIVISION) ||
		   ((VBFlags & TV_YPBPR) && (VBFlags & TV_YPBPR1080I))) अणु
		   ModeIndex = ModeIndex_1280x1024[Depth];
		पूर्ण
	     पूर्ण
	     अवरोध;
      पूर्ण
   पूर्ण
   वापस ModeIndex;
पूर्ण

अचिन्हित लघु
SiS_GetModeID_VGA2(पूर्णांक VGAEngine, अचिन्हित पूर्णांक VBFlags, पूर्णांक HDisplay, पूर्णांक VDisplay, पूर्णांक Depth,
			अचिन्हित पूर्णांक VBFlags2)
अणु
   अगर(!(VBFlags2 & VB2_SISVGA2BRIDGE)) वापस 0;

   अगर(HDisplay >= 1920) वापस 0;

   चयन(HDisplay)
   अणु
	हाल 1600:
		अगर(VDisplay == 1200) अणु
			अगर(VGAEngine != SIS_315_VGA) वापस 0;
			अगर(!(VBFlags2 & VB2_30xB)) वापस 0;
		पूर्ण
		अवरोध;
	हाल 1680:
		अगर(VDisplay == 1050) अणु
			अगर(VGAEngine != SIS_315_VGA) वापस 0;
			अगर(!(VBFlags2 & VB2_30xB)) वापस 0;
		पूर्ण
		अवरोध;
   पूर्ण

   वापस SiS_GetModeID(VGAEngine, 0, HDisplay, VDisplay, Depth, false, 0, 0);
पूर्ण


/*********************************************/
/*          HELPER: SetReg, GetReg           */
/*********************************************/

व्योम
SiS_SetReg(SISIOADDRESS port, u8 index, u8 data)
अणु
	outb(index, port);
	outb(data, port + 1);
पूर्ण

व्योम
SiS_SetRegByte(SISIOADDRESS port, u8 data)
अणु
	outb(data, port);
पूर्ण

व्योम
SiS_SetRegShort(SISIOADDRESS port, u16 data)
अणु
	outw(data, port);
पूर्ण

व्योम
SiS_SetRegLong(SISIOADDRESS port, u32 data)
अणु
	outl(data, port);
पूर्ण

u8
SiS_GetReg(SISIOADDRESS port, u8 index)
अणु
	outb(index, port);
	वापस inb(port + 1);
पूर्ण

u8
SiS_GetRegByte(SISIOADDRESS port)
अणु
	वापस inb(port);
पूर्ण

u16
SiS_GetRegShort(SISIOADDRESS port)
अणु
	वापस inw(port);
पूर्ण

u32
SiS_GetRegLong(SISIOADDRESS port)
अणु
	वापस inl(port);
पूर्ण

व्योम
SiS_SetRegANDOR(SISIOADDRESS Port, u8 Index, u8 DataAND, u8 DataOR)
अणु
   u8 temp;

   temp = SiS_GetReg(Port, Index);
   temp = (temp & (DataAND)) | DataOR;
   SiS_SetReg(Port, Index, temp);
पूर्ण

व्योम
SiS_SetRegAND(SISIOADDRESS Port, u8 Index, u8 DataAND)
अणु
   u8 temp;

   temp = SiS_GetReg(Port, Index);
   temp &= DataAND;
   SiS_SetReg(Port, Index, temp);
पूर्ण

व्योम
SiS_SetRegOR(SISIOADDRESS Port, u8 Index, u8 DataOR)
अणु
   u8 temp;

   temp = SiS_GetReg(Port, Index);
   temp |= DataOR;
   SiS_SetReg(Port, Index, temp);
पूर्ण

/*********************************************/
/*      HELPER: DisplayOn, DisplayOff        */
/*********************************************/

व्योम
SiS_DisplayOn(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x01,0xDF);
पूर्ण

व्योम
SiS_DisplayOff(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x01,0x20);
पूर्ण


/*********************************************/
/*        HELPER: Init Port Addresses        */
/*********************************************/

व्योम
SiSRegInit(काष्ठा SiS_Private *SiS_Pr, SISIOADDRESS BaseAddr)
अणु
   SiS_Pr->SiS_P3c4 = BaseAddr + 0x14;
   SiS_Pr->SiS_P3d4 = BaseAddr + 0x24;
   SiS_Pr->SiS_P3c0 = BaseAddr + 0x10;
   SiS_Pr->SiS_P3ce = BaseAddr + 0x1e;
   SiS_Pr->SiS_P3c2 = BaseAddr + 0x12;
   SiS_Pr->SiS_P3ca = BaseAddr + 0x1a;
   SiS_Pr->SiS_P3c6 = BaseAddr + 0x16;
   SiS_Pr->SiS_P3c7 = BaseAddr + 0x17;
   SiS_Pr->SiS_P3c8 = BaseAddr + 0x18;
   SiS_Pr->SiS_P3c9 = BaseAddr + 0x19;
   SiS_Pr->SiS_P3cb = BaseAddr + 0x1b;
   SiS_Pr->SiS_P3cc = BaseAddr + 0x1c;
   SiS_Pr->SiS_P3cd = BaseAddr + 0x1d;
   SiS_Pr->SiS_P3da = BaseAddr + 0x2a;
   SiS_Pr->SiS_Part1Port = BaseAddr + SIS_CRT2_PORT_04;
   SiS_Pr->SiS_Part2Port = BaseAddr + SIS_CRT2_PORT_10;
   SiS_Pr->SiS_Part3Port = BaseAddr + SIS_CRT2_PORT_12;
   SiS_Pr->SiS_Part4Port = BaseAddr + SIS_CRT2_PORT_14;
   SiS_Pr->SiS_Part5Port = BaseAddr + SIS_CRT2_PORT_14 + 2;
   SiS_Pr->SiS_DDC_Port  = BaseAddr + 0x14;
   SiS_Pr->SiS_VidCapt   = BaseAddr + SIS_VIDEO_CAPTURE;
   SiS_Pr->SiS_VidPlay   = BaseAddr + SIS_VIDEO_PLAYBACK;
पूर्ण

/*********************************************/
/*             HELPER: GetSysFlags           */
/*********************************************/

अटल व्योम
SiS_GetSysFlags(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर cr5f, temp1, temp2;

   /* 661 and newer: NEVER ग_लिखो non-zero to SR11[7:4] */
   /* (SR11 is used क्रम DDC and in enable/disablebridge) */
   SiS_Pr->SiS_SensibleSR11 = false;
   SiS_Pr->SiS_MyCR63 = 0x63;
   अगर(SiS_Pr->ChipType >= SIS_330) अणु
      SiS_Pr->SiS_MyCR63 = 0x53;
      अगर(SiS_Pr->ChipType >= SIS_661) अणु
         SiS_Pr->SiS_SensibleSR11 = true;
      पूर्ण
   पूर्ण

   /* You should use the macros, not these flags directly */

   SiS_Pr->SiS_SysFlags = 0;
   अगर(SiS_Pr->ChipType == SIS_650) अणु
      cr5f = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xf0;
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x5c,0x07);
      temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
      SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x5c,0xf8);
      temp2 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
      अगर((!temp1) || (temp2)) अणु
	 चयन(cr5f) अणु
	    हाल 0x80:
	    हाल 0x90:
	    हाल 0xc0:
	       SiS_Pr->SiS_SysFlags |= SF_IsM650;
	       अवरोध;
	    हाल 0xa0:
	    हाल 0xb0:
	    हाल 0xe0:
	       SiS_Pr->SiS_SysFlags |= SF_Is651;
	       अवरोध;
	 पूर्ण
      पूर्ण अन्यथा अणु
	 चयन(cr5f) अणु
	    हाल 0x90:
	       temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5c) & 0xf8;
	       चयन(temp1) अणु
		  हाल 0x00: SiS_Pr->SiS_SysFlags |= SF_IsM652; अवरोध;
		  हाल 0x40: SiS_Pr->SiS_SysFlags |= SF_IsM653; अवरोध;
		  शेष:   SiS_Pr->SiS_SysFlags |= SF_IsM650; अवरोध;
	       पूर्ण
	       अवरोध;
	    हाल 0xb0:
	       SiS_Pr->SiS_SysFlags |= SF_Is652;
	       अवरोध;
	    शेष:
	       SiS_Pr->SiS_SysFlags |= SF_IsM650;
	       अवरोध;
	 पूर्ण
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->ChipType >= SIS_760 && SiS_Pr->ChipType <= SIS_761) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x78) & 0x30) अणु
         SiS_Pr->SiS_SysFlags |= SF_760LFB;
      पूर्ण
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x79) & 0xf0) अणु
         SiS_Pr->SiS_SysFlags |= SF_760UMA;
      पूर्ण
   पूर्ण
पूर्ण

/*********************************************/
/*         HELPER: Init PCI & Engines        */
/*********************************************/

अटल व्योम
SiSInitPCIetc(काष्ठा SiS_Private *SiS_Pr)
अणु
   चयन(SiS_Pr->ChipType) अणु
#अगर_घोषित CONFIG_FB_SIS_300
   हाल SIS_300:
   हाल SIS_540:
   हाल SIS_630:
   हाल SIS_730:
      /* Set - PCI LINEAR ADDRESSING ENABLE (0x80)
       *     - RELOCATED VGA IO ENABLED (0x20)
       *     - MMIO ENABLED (0x01)
       * Leave other bits untouched.
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /*  - Enable 2D (0x40)
       *  - Enable 3D (0x02)
       *  - Enable 3D Vertex command fetch (0x10) ?
       *  - Enable 3D command parser (0x08) ?
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x5A);
      अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
   हाल SIS_315H:
   हाल SIS_315:
   हाल SIS_315PRO:
   हाल SIS_650:
   हाल SIS_740:
   हाल SIS_330:
   हाल SIS_661:
   हाल SIS_741:
   हाल SIS_660:
   हाल SIS_760:
   हाल SIS_761:
   हाल SIS_340:
   हाल XGI_40:
      /* See above */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /*  - Enable 3D G/L transक्रमmation engine (0x80)
       *  - Enable 2D (0x40)
       *  - Enable 3D vertex command fetch (0x10)
       *  - Enable 3D command parser (0x08)
       *  - Enable 3D (0x02)
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0xDA);
      अवरोध;
   हाल XGI_20:
   हाल SIS_550:
      /* See above */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /* No 3D engine ! */
      /*  - Enable 2D (0x40)
       *  - disable 3D
       */
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x1E,0x60,0x40);
      अवरोध;
#पूर्ण_अगर
   शेष:
      अवरोध;
   पूर्ण
पूर्ण

/*********************************************/
/*             HELPER: SetLVDSetc            */
/*********************************************/

अटल
व्योम
SiSSetLVDSetc(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु temp;

   SiS_Pr->SiS_IF_DEF_LVDS = 0;
   SiS_Pr->SiS_IF_DEF_TRUMPION = 0;
   SiS_Pr->SiS_IF_DEF_CH70xx = 0;
   SiS_Pr->SiS_IF_DEF_CONEX = 0;

   SiS_Pr->SiS_ChrontelInit = 0;

   अगर(SiS_Pr->ChipType == XGI_20) वापस;

   /* Check क्रम SiS30x first */
   temp = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);
   अगर((temp == 1) || (temp == 2)) वापस;

   चयन(SiS_Pr->ChipType) अणु
#अगर_घोषित CONFIG_FB_SIS_300
   हाल SIS_540:
   हाल SIS_630:
   हाल SIS_730:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x37) & 0x0e) >> 1;
	अगर((temp >= 2) && (temp <= 5))	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	अगर(temp == 3)			SiS_Pr->SiS_IF_DEF_TRUMPION = 1;
	अगर((temp == 4) || (temp == 5)) अणु
		/* Save घातer status (and error check) - UNUSED */
		SiS_Pr->SiS_Backup70xx = SiS_GetCH700x(SiS_Pr, 0x0e);
		SiS_Pr->SiS_IF_DEF_CH70xx = 1;
	पूर्ण
	अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
   हाल SIS_550:
   हाल SIS_650:
   हाल SIS_740:
   हाल SIS_330:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x37) & 0x0e) >> 1;
	अगर((temp >= 2) && (temp <= 3))	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	अगर(temp == 3)			SiS_Pr->SiS_IF_DEF_CH70xx = 2;
	अवरोध;
   हाल SIS_661:
   हाल SIS_741:
   हाल SIS_660:
   हाल SIS_760:
   हाल SIS_761:
   हाल SIS_340:
   हाल XGI_20:
   हाल XGI_40:
	temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & 0xe0) >> 5;
	अगर((temp >= 2) && (temp <= 3)) 	SiS_Pr->SiS_IF_DEF_LVDS = 1;
	अगर(temp == 3)			SiS_Pr->SiS_IF_DEF_CH70xx = 2;
	अगर(temp == 4)			SiS_Pr->SiS_IF_DEF_CONEX = 1;  /* Not yet supported */
	अवरोध;
#पूर्ण_अगर
   शेष:
	अवरोध;
   पूर्ण
पूर्ण

/*********************************************/
/*          HELPER: Enable DSTN/FSTN         */
/*********************************************/

व्योम
SiS_SetEnableDstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable)
अणु
   SiS_Pr->SiS_IF_DEF_DSTN = enable ? 1 : 0;
पूर्ण

व्योम
SiS_SetEnableFstn(काष्ठा SiS_Private *SiS_Pr, पूर्णांक enable)
अणु
   SiS_Pr->SiS_IF_DEF_FSTN = enable ? 1 : 0;
पूर्ण

/*********************************************/
/*            HELPER: Get modeflag           */
/*********************************************/

अचिन्हित लघु
SiS_GetModeFlag(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex)
अणु
   अगर(SiS_Pr->UseCustomMode) अणु
      वापस SiS_Pr->CModeFlag;
   पूर्ण अन्यथा अगर(ModeNo <= 0x13) अणु
      वापस SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   पूर्ण अन्यथा अणु
      वापस SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   पूर्ण
पूर्ण

/*********************************************/
/*        HELPER: Determine ROM usage        */
/*********************************************/

bool
SiSDetermineROMLayout661(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr  = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु romversoffs, romvmaj = 1, romvmin = 0;

   अगर(SiS_Pr->ChipType >= XGI_20) अणु
      /* XGI ROMs करोn't qualअगरy */
      वापस false;
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_761) अणु
      /* I very much assume 761, 340 and newer will use new layout */
      वापस true;
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) अणु
      अगर((ROMAddr[0x1a] == 'N') &&
	 (ROMAddr[0x1b] == 'e') &&
	 (ROMAddr[0x1c] == 'w') &&
	 (ROMAddr[0x1d] == 'V')) अणु
	 वापस true;
      पूर्ण
      romversoffs = ROMAddr[0x16] | (ROMAddr[0x17] << 8);
      अगर(romversoffs) अणु
	 अगर((ROMAddr[romversoffs+1] == '.') || (ROMAddr[romversoffs+4] == '.')) अणु
	    romvmaj = ROMAddr[romversoffs] - '0';
	    romvmin = ((ROMAddr[romversoffs+2] -'0') * 10) + (ROMAddr[romversoffs+3] - '0');
	 पूर्ण
      पूर्ण
      अगर((romvmaj != 0) || (romvmin >= 92)) अणु
	 वापस true;
      पूर्ण
   पूर्ण अन्यथा अगर(IS_SIS650740) अणु
      अगर((ROMAddr[0x1a] == 'N') &&
	 (ROMAddr[0x1b] == 'e') &&
	 (ROMAddr[0x1c] == 'w') &&
	 (ROMAddr[0x1d] == 'V')) अणु
	 वापस true;
      पूर्ण
   पूर्ण
   वापस false;
पूर्ण

अटल व्योम
SiSDetermineROMUsage(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr  = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु romptr = 0;

   SiS_Pr->SiS_UseROM = false;
   SiS_Pr->SiS_ROMNew = false;
   SiS_Pr->SiS_PWDOffset = 0;

   अगर(SiS_Pr->ChipType >= XGI_20) वापस;

   अगर((ROMAddr) && (SiS_Pr->UseROM)) अणु
      अगर(SiS_Pr->ChipType == SIS_300) अणु
	 /* 300: We check अगर the code starts below 0x220 by
	  * checking the jmp inकाष्ठाion at the beginning
	  * of the BIOS image.
	  */
	 अगर((ROMAddr[3] == 0xe9) && ((ROMAddr[5] << 8) | ROMAddr[4]) > 0x21a)
	    SiS_Pr->SiS_UseROM = true;
      पूर्ण अन्यथा अगर(SiS_Pr->ChipType < SIS_315H) अणु
	 /* Sony's VAIO BIOS 1.09 follows the standard, so perhaps
	  * the others करो as well
	  */
	 SiS_Pr->SiS_UseROM = true;
      पूर्ण अन्यथा अणु
	 /* 315/330 series stick to the standard(s) */
	 SiS_Pr->SiS_UseROM = true;
	 अगर((SiS_Pr->SiS_ROMNew = SiSDetermineROMLayout661(SiS_Pr))) अणु
	    SiS_Pr->SiS_EMIOffset = 14;
	    SiS_Pr->SiS_PWDOffset = 17;
	    SiS_Pr->SiS661LCD2TableSize = 36;
	    /* Find out about LCD data table entry size */
	    अगर((romptr = SISGETROMW(0x0102))) अणु
	       अगर(ROMAddr[romptr + (32 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 32;
	       अन्यथा अगर(ROMAddr[romptr + (34 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 34;
	       अन्यथा अगर(ROMAddr[romptr + (36 * 16)] == 0xff)	   /* 0.94, 2.05.00+ */
		  SiS_Pr->SiS661LCD2TableSize = 36;
	       अन्यथा अगर( (ROMAddr[romptr + (38 * 16)] == 0xff) ||   /* 2.00.00 - 2.02.00 */
		 	(ROMAddr[0x6F] & 0x01) ) अणु		   /* 2.03.00 - <2.05.00 */
		  SiS_Pr->SiS661LCD2TableSize = 38;		   /* UMC data layout abanकरोned at 2.05.00 */
		  SiS_Pr->SiS_EMIOffset = 16;
		  SiS_Pr->SiS_PWDOffset = 19;
	       पूर्ण
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

/*********************************************/
/*        HELPER: SET SEGMENT REGISTERS      */
/*********************************************/

अटल व्योम
SiS_SetSegRegLower(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
   अचिन्हित लघु temp;

   value &= 0x00ff;
   temp = SiS_GetRegByte(SiS_Pr->SiS_P3cb) & 0xf0;
   temp |= (value >> 4);
   SiS_SetRegByte(SiS_Pr->SiS_P3cb, temp);
   temp = SiS_GetRegByte(SiS_Pr->SiS_P3cd) & 0xf0;
   temp |= (value & 0x0f);
   SiS_SetRegByte(SiS_Pr->SiS_P3cd, temp);
पूर्ण

अटल व्योम
SiS_SetSegRegUpper(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
   अचिन्हित लघु temp;

   value &= 0x00ff;
   temp = SiS_GetRegByte(SiS_Pr->SiS_P3cb) & 0x0f;
   temp |= (value & 0xf0);
   SiS_SetRegByte(SiS_Pr->SiS_P3cb, temp);
   temp = SiS_GetRegByte(SiS_Pr->SiS_P3cd) & 0x0f;
   temp |= (value << 4);
   SiS_SetRegByte(SiS_Pr->SiS_P3cd, temp);
पूर्ण

अटल व्योम
SiS_SetSegmentReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
   SiS_SetSegRegLower(SiS_Pr, value);
   SiS_SetSegRegUpper(SiS_Pr, value);
पूर्ण

अटल व्योम
SiS_ResetSegmentReg(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_SetSegmentReg(SiS_Pr, 0);
पूर्ण

अटल व्योम
SiS_SetSegmentRegOver(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
   अचिन्हित लघु temp = value >> 8;

   temp &= 0x07;
   temp |= (temp << 4);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x1d,temp);
   SiS_SetSegmentReg(SiS_Pr, value);
पूर्ण

अटल व्योम
SiS_ResetSegmentRegOver(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_SetSegmentRegOver(SiS_Pr, 0);
पूर्ण

अटल व्योम
SiS_ResetSegmentRegisters(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर((IS_SIS65x) || (SiS_Pr->ChipType >= SIS_661)) अणु
      SiS_ResetSegmentReg(SiS_Pr);
      SiS_ResetSegmentRegOver(SiS_Pr);
   पूर्ण
पूर्ण

/*********************************************/
/*             HELPER: GetVBType             */
/*********************************************/

अटल
व्योम
SiS_GetVBType(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag = 0, rev = 0, nolcd = 0;
   अचिन्हित लघु p4_0f, p4_25, p4_27;

   SiS_Pr->SiS_VBType = 0;

   अगर((SiS_Pr->SiS_IF_DEF_LVDS) || (SiS_Pr->SiS_IF_DEF_CONEX))
      वापस;

   अगर(SiS_Pr->ChipType == XGI_20)
      वापस;

   flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);

   अगर(flag > 3)
      वापस;

   rev = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x01);

   अगर(flag >= 2) अणु
      SiS_Pr->SiS_VBType = VB_SIS302B;
   पूर्ण अन्यथा अगर(flag == 1) अणु
      अगर(rev >= 0xC0) अणु
	 SiS_Pr->SiS_VBType = VB_SIS301C;
      पूर्ण अन्यथा अगर(rev >= 0xB0) अणु
	 SiS_Pr->SiS_VBType = VB_SIS301B;
	 /* Check अगर 30xB DH version (no LCD support, use Panel Link instead) */
	 nolcd = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x23);
	 अगर(!(nolcd & 0x02)) SiS_Pr->SiS_VBType |= VB_NoLCD;
      पूर्ण अन्यथा अणु
	 SiS_Pr->SiS_VBType = VB_SIS301;
      पूर्ण
   पूर्ण
   अगर(SiS_Pr->SiS_VBType & (VB_SIS301B | VB_SIS301C | VB_SIS302B)) अणु
      अगर(rev >= 0xE0) अणु
	 flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x39);
	 अगर(flag == 0xff) SiS_Pr->SiS_VBType = VB_SIS302LV;
	 अन्यथा 	 	  SiS_Pr->SiS_VBType = VB_SIS301C;  /* VB_SIS302ELV; */
      पूर्ण अन्यथा अगर(rev >= 0xD0) अणु
	 SiS_Pr->SiS_VBType = VB_SIS301LV;
      पूर्ण
   पूर्ण
   अगर(SiS_Pr->SiS_VBType & (VB_SIS301C | VB_SIS301LV | VB_SIS302LV | VB_SIS302ELV)) अणु
      p4_0f = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x0f);
      p4_25 = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x25);
      p4_27 = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x27);
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x0f,0x7f);
      SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x25,0x08);
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x27,0xfd);
      अगर(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x08) अणु
         SiS_Pr->SiS_VBType |= VB_UMC;
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x27,p4_27);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x25,p4_25);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0f,p4_0f);
   पूर्ण
पूर्ण

/*********************************************/
/*           HELPER: Check RAM size          */
/*********************************************/

अटल bool
SiS_CheckMemorySize(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु AdapterMemSize = SiS_Pr->VideoMemorySize / (1024*1024);
   अचिन्हित लघु modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);
   अचिन्हित लघु memorysize = ((modeflag & MemoryInfoFlag) >> MemorySizeShअगरt) + 1;

   अगर(!AdapterMemSize) वापस true;

   अगर(AdapterMemSize < memorysize) वापस false;
   वापस true;
पूर्ण

/*********************************************/
/*           HELPER: Get DRAM type           */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_315
अटल अचिन्हित अक्षर
SiS_Get310DRAMType(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर data;

   अगर((*SiS_Pr->pSiS_SoftSetting) & SoftDRAMType) अणु
      data = (*SiS_Pr->pSiS_SoftSetting) & 0x03;
   पूर्ण अन्यथा अणु
      अगर(SiS_Pr->ChipType >= XGI_20) अणु
         /* Do I need this? SR17 seems to be zero anyway... */
	 data = 0;
      पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_340) अणु
	 /* TODO */
	 data = 0;
      पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) अणु
	 अगर(SiS_Pr->SiS_ROMNew) अणु
	    data = ((SiS_GetReg(SiS_Pr->SiS_P3d4,0x78) & 0xc0) >> 6);
	 पूर्ण अन्यथा अणु
	    data = SiS_GetReg(SiS_Pr->SiS_P3d4,0x78) & 0x07;
	 पूर्ण
      पूर्ण अन्यथा अगर(IS_SIS550650740) अणु
	 data = SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x07;
      पूर्ण अन्यथा अणु	/* 315, 330 */
	 data = SiS_GetReg(SiS_Pr->SiS_P3c4,0x3a) & 0x03;
	 अगर(SiS_Pr->ChipType == SIS_330) अणु
	    अगर(data > 1) अणु
	       चयन(SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0x30) अणु
	       हाल 0x00: data = 1; अवरोध;
	       हाल 0x10: data = 3; अवरोध;
	       हाल 0x20: data = 3; अवरोध;
	       हाल 0x30: data = 2; अवरोध;
	       पूर्ण
	    पूर्ण अन्यथा अणु
	       data = 0;
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण

   वापस data;
पूर्ण

अटल अचिन्हित लघु
SiS_GetMCLK(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु index;

   index = SiS_Get310DRAMType(SiS_Pr);
   अगर(SiS_Pr->ChipType >= SIS_661) अणु
      अगर(SiS_Pr->SiS_ROMNew) अणु
	 वापस((अचिन्हित लघु)(SISGETROMW((0x90 + (index * 5) + 3))));
      पूर्ण
      वापस(SiS_Pr->SiS_MCLKData_0[index].CLOCK);
   पूर्ण अन्यथा अगर(index >= 4) अणु
      वापस(SiS_Pr->SiS_MCLKData_1[index - 4].CLOCK);
   पूर्ण अन्यथा अणु
      वापस(SiS_Pr->SiS_MCLKData_0[index].CLOCK);
   पूर्ण
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*           HELPER: ClearBuffer             */
/*********************************************/

अटल व्योम
SiS_ClearBuffer(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   अचिन्हित अक्षर  SISIOMEMTYPE *memaddr = SiS_Pr->VideoMemoryAddress;
   अचिन्हित पूर्णांक   memsize = SiS_Pr->VideoMemorySize;
   अचिन्हित लघु SISIOMEMTYPE *pBuffer;
   पूर्णांक i;

   अगर(!memaddr || !memsize) वापस;

   अगर(SiS_Pr->SiS_ModeType >= ModeEGA) अणु
      अगर(ModeNo > 0x13) अणु
	 स_रखो_io(memaddr, 0, memsize);
      पूर्ण अन्यथा अणु
	 pBuffer = (अचिन्हित लघु SISIOMEMTYPE *)memaddr;
	 क्रम(i = 0; i < 0x4000; i++) ग_लिखोw(0x0000, &pBuffer[i]);
      पूर्ण
   पूर्ण अन्यथा अगर(SiS_Pr->SiS_ModeType < ModeCGA) अणु
      pBuffer = (अचिन्हित लघु SISIOMEMTYPE *)memaddr;
      क्रम(i = 0; i < 0x4000; i++) ग_लिखोw(0x0720, &pBuffer[i]);
   पूर्ण अन्यथा अणु
      स_रखो_io(memaddr, 0, 0x8000);
   पूर्ण
पूर्ण

/*********************************************/
/*           HELPER: SearchModeID            */
/*********************************************/

bool
SiS_SearchModeID(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *ModeNo,
		अचिन्हित लघु *ModeIdIndex)
अणु
   अचिन्हित अक्षर VGAINFO = SiS_Pr->SiS_VGAINFO;

   अगर((*ModeNo) <= 0x13) अणु

      अगर((*ModeNo) <= 0x05) (*ModeNo) |= 0x01;

      क्रम((*ModeIdIndex) = 0; ;(*ModeIdIndex)++) अणु
	 अगर(SiS_Pr->SiS_SModeIDTable[(*ModeIdIndex)].St_ModeID == (*ModeNo)) अवरोध;
	 अगर(SiS_Pr->SiS_SModeIDTable[(*ModeIdIndex)].St_ModeID == 0xFF) वापस false;
      पूर्ण

      अगर((*ModeNo) == 0x07) अणु
	  अगर(VGAINFO & 0x10) (*ModeIdIndex)++;   /* 400 lines */
	  /* अन्यथा 350 lines */
      पूर्ण
      अगर((*ModeNo) <= 0x03) अणु
	 अगर(!(VGAINFO & 0x80)) (*ModeIdIndex)++;
	 अगर(VGAINFO & 0x10)    (*ModeIdIndex)++; /* 400 lines  */
	 /* अन्यथा 350 lines  */
      पूर्ण
      /* अन्यथा 200 lines  */

   पूर्ण अन्यथा अणु

      क्रम((*ModeIdIndex) = 0; ;(*ModeIdIndex)++) अणु
	 अगर(SiS_Pr->SiS_EModeIDTable[(*ModeIdIndex)].Ext_ModeID == (*ModeNo)) अवरोध;
	 अगर(SiS_Pr->SiS_EModeIDTable[(*ModeIdIndex)].Ext_ModeID == 0xFF) वापस false;
      पूर्ण

   पूर्ण
   वापस true;
पूर्ण

/*********************************************/
/*            HELPER: GetModePtr             */
/*********************************************/

अचिन्हित लघु
SiS_GetModePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु index;

   अगर(ModeNo <= 0x13) अणु
      index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_StTableIndex;
   पूर्ण अन्यथा अणु
      अगर(SiS_Pr->SiS_ModeType <= ModeEGA) index = 0x1B;
      अन्यथा index = 0x0F;
   पूर्ण
   वापस index;
पूर्ण

/*********************************************/
/*         HELPERS: Get some indices         */
/*********************************************/

अचिन्हित लघु
SiS_GetRefCRTVCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide)
अणु
   अगर(SiS_Pr->SiS_RefIndex[Index].Ext_InfoFlag & HaveWideTiming) अणु
      अगर(UseWide == 1) अणु
         वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRTVCLK_WIDE;
      पूर्ण अन्यथा अणु
         वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRTVCLK_NORM;
      पूर्ण
   पूर्ण अन्यथा अणु
      वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRTVCLK;
   पूर्ण
पूर्ण

अचिन्हित लघु
SiS_GetRefCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide)
अणु
   अगर(SiS_Pr->SiS_RefIndex[Index].Ext_InfoFlag & HaveWideTiming) अणु
      अगर(UseWide == 1) अणु
         वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC_WIDE;
      पूर्ण अन्यथा अणु
         वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC_NORM;
      पूर्ण
   पूर्ण अन्यथा अणु
      वापस SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC;
   पूर्ण
पूर्ण

/*********************************************/
/*           HELPER: LowModeTests            */
/*********************************************/

अटल bool
SiS_DoLowModeTest(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   अचिन्हित लघु temp, temp1, temp2;

   अगर((ModeNo != 0x03) && (ModeNo != 0x10) && (ModeNo != 0x12))
      वापस true;
   temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x11);
   SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x11,0x80);
   temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x00);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x00,0x55);
   temp2 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x00);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x00,temp1);
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x11,temp);
   अगर((SiS_Pr->ChipType >= SIS_315H) ||
      (SiS_Pr->ChipType == SIS_300)) अणु
      अगर(temp2 == 0x55) वापस false;
      अन्यथा वापस true;
   पूर्ण अन्यथा अणु
      अगर(temp2 != 0x55) वापस true;
      अन्यथा अणु
	 SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x35,0x01);
	 वापस false;
      पूर्ण
   पूर्ण
पूर्ण

अटल व्योम
SiS_SetLowModeTest(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   अगर(SiS_DoLowModeTest(SiS_Pr, ModeNo)) अणु
      SiS_Pr->SiS_SetFlag |= LowModeTests;
   पूर्ण
पूर्ण

/*********************************************/
/*        HELPER: OPEN/CLOSE CRT1 CRTC       */
/*********************************************/

अटल व्योम
SiS_OpenCRTC(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(IS_SIS650) अणु
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x51,0x1f);
      अगर(IS_SIS651) SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x51,0x20);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x56,0xe7);
   पूर्ण अन्यथा अगर(IS_SIS661741660760) अणु
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x61,0xf7);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x51,0x1f);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x56,0xe7);
      अगर(!SiS_Pr->SiS_ROMNew) अणु
	 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x3a,0xef);
      पूर्ण
   पूर्ण
पूर्ण

अटल व्योम
SiS_CloseCRTC(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर 0 /* This locks some CRTC रेजिस्टरs. We करोn't want that. */
   अचिन्हित लघु temp1 = 0, temp2 = 0;

   अगर(IS_SIS661741660760) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
         temp1 = 0xa0; temp2 = 0x08;
      पूर्ण
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x51,0x1f,temp1);
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x56,0xe7,temp2);
   पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
SiS_HandleCRT1(काष्ठा SiS_Private *SiS_Pr)
अणु
   /* Enable CRT1 gating */
   SiS_SetRegAND(SiS_Pr->SiS_P3d4,SiS_Pr->SiS_MyCR63,0xbf);
#अगर 0
   अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x15) & 0x01)) अणु
      अगर((SiS_GetReg(SiS_Pr->SiS_P3c4,0x15) & 0x0a) ||
         (SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x01)) अणु
         SiS_SetRegOR(SiS_Pr->SiS_P3d4,SiS_Pr->SiS_MyCR63,0x40);
      पूर्ण
   पूर्ण
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*           HELPER: GetColorDepth           */
/*********************************************/

अचिन्हित लघु
SiS_GetColorDepth(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex)
अणु
   अटल स्थिर अचिन्हित लघु ColorDepth[6] = अणु 1, 2, 4, 4, 6, 8 पूर्ण;
   अचिन्हित लघु modeflag;
   लघु index;

   /* Do NOT check UseCustomMode, will skrew up FIFO */
   अगर(ModeNo == 0xfe) अणु
      modeflag = SiS_Pr->CModeFlag;
   पूर्ण अन्यथा अगर(ModeNo <= 0x13) अणु
      modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   पूर्ण अन्यथा अणु
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   पूर्ण

   index = (modeflag & ModeTypeMask) - ModeEGA;
   अगर(index < 0) index = 0;
   वापस ColorDepth[index];
पूर्ण

/*********************************************/
/*             HELPER: GetOffset             */
/*********************************************/

अचिन्हित लघु
SiS_GetOffset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु xres, temp, colordepth, infoflag;

   अगर(SiS_Pr->UseCustomMode) अणु
      infoflag = SiS_Pr->CInfoFlag;
      xres = SiS_Pr->CHDisplay;
   पूर्ण अन्यथा अणु
      infoflag = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag;
      xres = SiS_Pr->SiS_RefIndex[RRTI].XRes;
   पूर्ण

   colordepth = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex);

   temp = xres / 16;
   अगर(infoflag & InterlaceMode) temp <<= 1;
   temp *= colordepth;
   अगर(xres % 16) temp += (colordepth >> 1);

   वापस temp;
पूर्ण

/*********************************************/
/*                   SEQ                     */
/*********************************************/

अटल व्योम
SiS_SetSeqRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
   अचिन्हित अक्षर SRdata;
   पूर्णांक i;

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x00,0x03);

   /* or "display off"  */
   SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[0] | 0x20;

   /* determine whether to क्रमce x8 करोtघड़ी */
   अगर((SiS_Pr->SiS_VBType & VB_SISVB) || (SiS_Pr->SiS_IF_DEF_LVDS)) अणु

      अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) अणु
         अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode)    SRdata |= 0x01;
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) SRdata |= 0x01;

   पूर्ण

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x01,SRdata);

   क्रम(i = 2; i <= 4; i++) अणु
      SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[i - 1];
      SiS_SetReg(SiS_Pr->SiS_P3c4,i,SRdata);
   पूर्ण
पूर्ण

/*********************************************/
/*                  MISC                     */
/*********************************************/

अटल व्योम
SiS_SetMiscRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
   अचिन्हित अक्षर Miscdata;

   Miscdata = SiS_Pr->SiS_StandTable[StandTableIndex].MISC;

   अगर(SiS_Pr->ChipType < SIS_661) अणु
      अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	   Miscdata |= 0x0C;
	 पूर्ण
      पूर्ण
   पूर्ण

   SiS_SetRegByte(SiS_Pr->SiS_P3c2,Miscdata);
पूर्ण

/*********************************************/
/*                  CRTC                     */
/*********************************************/

अटल व्योम
SiS_SetCRTCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
   अचिन्हित अक्षर  CRTCdata;
   अचिन्हित लघु i;

   /* Unlock CRTC */
   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   क्रम(i = 0; i <= 0x18; i++) अणु
      CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
      SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
   पूर्ण

   अगर(SiS_Pr->ChipType >= SIS_661) अणु
      SiS_OpenCRTC(SiS_Pr);
      क्रम(i = 0x13; i <= 0x14; i++) अणु
	 CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
	 SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
      पूर्ण
   पूर्ण अन्यथा अगर( ( (SiS_Pr->ChipType == SIS_630) ||
	        (SiS_Pr->ChipType == SIS_730) )  &&
	      (SiS_Pr->ChipRevision >= 0x30) ) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	 अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) अणु
	    SiS_SetReg(SiS_Pr->SiS_P3d4,0x18,0xFE);
	 पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

/*********************************************/
/*                   ATT                     */
/*********************************************/

अटल व्योम
SiS_SetATTRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
   अचिन्हित अक्षर  ARdata;
   अचिन्हित लघु i;

   क्रम(i = 0; i <= 0x13; i++) अणु
      ARdata = SiS_Pr->SiS_StandTable[StandTableIndex].ATTR[i];

      अगर(i == 0x13) अणु
	 /* Pixel shअगरt. If screen on LCD or TV is shअगरted left or right,
	  * this might be the cause.
	  */
	 अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) ARdata = 0;
	 पूर्ण
	 अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	    अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
		  अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) ARdata = 0;
	       पूर्ण
	    पूर्ण
	 पूर्ण
	 अगर(SiS_Pr->ChipType >= SIS_661) अणु
	    अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToTV | SetCRT2ToLCD)) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) ARdata = 0;
	    पूर्ण
	 पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	    अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	       अगर(IS_SIS550650740660) अणु
		  /* 315, 330 करोn't करो this */
		  अगर(SiS_Pr->SiS_VBType & VB_SIS30xB) अणु
		     अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) ARdata = 0;
		  पूर्ण अन्यथा अणु
		     ARdata = 0;
		  पूर्ण
	       पूर्ण
	    पूर्ण अन्यथा अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) ARdata = 0;
	    पूर्ण
	 पूर्ण
      पूर्ण
      SiS_GetRegByte(SiS_Pr->SiS_P3da);		/* reset 3da  */
      SiS_SetRegByte(SiS_Pr->SiS_P3c0,i);	/* set index  */
      SiS_SetRegByte(SiS_Pr->SiS_P3c0,ARdata);	/* set data   */
   पूर्ण

   SiS_GetRegByte(SiS_Pr->SiS_P3da);		/* reset 3da  */
   SiS_SetRegByte(SiS_Pr->SiS_P3c0,0x14);	/* set index  */
   SiS_SetRegByte(SiS_Pr->SiS_P3c0,0x00);	/* set data   */

   SiS_GetRegByte(SiS_Pr->SiS_P3da);
   SiS_SetRegByte(SiS_Pr->SiS_P3c0,0x20);	/* Enable Attribute  */
   SiS_GetRegByte(SiS_Pr->SiS_P3da);
पूर्ण

/*********************************************/
/*                   GRC                     */
/*********************************************/

अटल व्योम
SiS_SetGRCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
   अचिन्हित अक्षर  GRdata;
   अचिन्हित लघु i;

   क्रम(i = 0; i <= 0x08; i++) अणु
      GRdata = SiS_Pr->SiS_StandTable[StandTableIndex].GRC[i];
      SiS_SetReg(SiS_Pr->SiS_P3ce,i,GRdata);
   पूर्ण

   अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
      /* 256 color disable */
      SiS_SetRegAND(SiS_Pr->SiS_P3ce,0x05,0xBF);
   पूर्ण
पूर्ण

/*********************************************/
/*          CLEAR EXTENDED REGISTERS         */
/*********************************************/

अटल व्योम
SiS_ClearExt1Regs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   अचिन्हित लघु i;

   क्रम(i = 0x0A; i <= 0x0E; i++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3c4,i,0x00);
   पूर्ण

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x37,0xFE);
      अगर(ModeNo <= 0x13) अणु
	 अगर(ModeNo == 0x06 || ModeNo >= 0x0e) अणु
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x0e,0x20);
	 पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

/*********************************************/
/*                 RESET VCLK                */
/*********************************************/

अटल व्योम
SiS_ResetCRT1VCLK(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर(SiS_Pr->ChipType < SIS_661) अणु
	 अगर(SiS_Pr->SiS_IF_DEF_LVDS == 0) वापस;
      पूर्ण
   पूर्ण अन्यथा अणु
      अगर((SiS_Pr->SiS_IF_DEF_LVDS == 0) &&
	 (!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) ) अणु
	 वापस;
      पूर्ण
   पूर्ण

   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x31,0xcf,0x20);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2B,SiS_Pr->SiS_VCLKData[1].SR2B);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2C,SiS_Pr->SiS_VCLKData[1].SR2C);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x31,0xcf,0x10);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2B,SiS_Pr->SiS_VCLKData[0].SR2B);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2C,SiS_Pr->SiS_VCLKData[0].SR2C);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
पूर्ण

/*********************************************/
/*                  SYNC                     */
/*********************************************/

अटल व्योम
SiS_SetCRT1Sync(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु sync;

   अगर(SiS_Pr->UseCustomMode) अणु
      sync = SiS_Pr->CInfoFlag >> 8;
   पूर्ण अन्यथा अणु
      sync = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag >> 8;
   पूर्ण

   sync &= 0xC0;
   sync |= 0x2f;
   SiS_SetRegByte(SiS_Pr->SiS_P3c2,sync);
पूर्ण

/*********************************************/
/*                  CRTC/2                   */
/*********************************************/

अटल व्योम
SiS_SetCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु temp, i, j, modeflag;
   अचिन्हित अक्षर  *crt1data = शून्य;

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(SiS_Pr->UseCustomMode) अणु

      crt1data = &SiS_Pr->CCRT1CRTC[0];

   पूर्ण अन्यथा अणु

      temp = SiS_GetRefCRT1CRTC(SiS_Pr, RRTI, SiS_Pr->SiS_UseWide);

      /* Alternate क्रम 1600x1200 LCDA */
      अगर((temp == 0x20) && (SiS_Pr->Alternate1600x1200)) temp = 0x57;

      crt1data = (अचिन्हित अक्षर *)&SiS_Pr->SiS_CRT1Table[temp].CR[0];

   पूर्ण

   /* unlock cr0-7 */
   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   क्रम(i = 0, j = 0; i <= 7; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,crt1data[i]);
   पूर्ण
   क्रम(j = 0x10; i <= 10; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,crt1data[i]);
   पूर्ण
   क्रम(j = 0x15; i <= 12; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,crt1data[i]);
   पूर्ण
   क्रम(j = 0x0A; i <= 15; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3c4,j,crt1data[i]);
   पूर्ण

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x0E,crt1data[16] & 0xE0);

   temp = (crt1data[16] & 0x01) << 5;
   अगर(modeflag & DoubleScanMode) temp |= 0x80;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x09,0x5F,temp);

   अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x14,0x4F);
   पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType == XGI_20) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x04,crt1data[4] - 1);
      अगर(!(temp = crt1data[5] & 0x1f)) अणु
         SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x0c,0xfb);
      पूर्ण
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x05,0xe0,((temp - 1) & 0x1f));
      temp = (crt1data[16] >> 5) + 3;
      अगर(temp > 7) temp -= 7;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0e,0x1f,(temp << 5));
   पूर्ण
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*               OFFSET & PITCH              */
/*********************************************/
/*  (partly overruled by SetPitch() in XF86) */
/*********************************************/

अटल व्योम
SiS_SetCRT1Offset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु temp, DisplayUnit, infoflag;

   अगर(SiS_Pr->UseCustomMode) अणु
      infoflag = SiS_Pr->CInfoFlag;
   पूर्ण अन्यथा अणु
      infoflag = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag;
   पूर्ण

   DisplayUnit = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, RRTI);

   temp = (DisplayUnit >> 8) & 0x0f;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0xF0,temp);

   SiS_SetReg(SiS_Pr->SiS_P3d4,0x13,DisplayUnit & 0xFF);

   अगर(infoflag & InterlaceMode) DisplayUnit >>= 1;

   DisplayUnit <<= 5;
   temp = (DisplayUnit >> 8) + 1;
   अगर(DisplayUnit & 0xff) temp++;
   अगर(SiS_Pr->ChipType == XGI_20) अणु
      अगर(ModeNo == 0x4a || ModeNo == 0x49) temp--;
   पूर्ण
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x10,temp);
पूर्ण

/*********************************************/
/*                  VCLK                     */
/*********************************************/

अटल व्योम
SiS_SetCRT1VCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु index = 0, clka, clkb;

   अगर(SiS_Pr->UseCustomMode) अणु
      clka = SiS_Pr->CSR2B;
      clkb = SiS_Pr->CSR2C;
   पूर्ण अन्यथा अणु
      index = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
      अगर((SiS_Pr->SiS_VBType & VB_SIS30xBLV) &&
	 (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	 /* Alternate क्रम 1600x1200 LCDA */
	 अगर((index == 0x21) && (SiS_Pr->Alternate1600x1200)) index = 0x72;
	 clka = SiS_Pr->SiS_VBVCLKData[index].Part4_A;
	 clkb = SiS_Pr->SiS_VBVCLKData[index].Part4_B;
      पूर्ण अन्यथा अणु
	 clka = SiS_Pr->SiS_VCLKData[index].SR2B;
	 clkb = SiS_Pr->SiS_VCLKData[index].SR2C;
      पूर्ण
   पूर्ण

   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x31,0xCF);

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,clka);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,clkb);

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_315
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x01);
      अगर(SiS_Pr->ChipType == XGI_20) अणु
         अचिन्हित लघु mf = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);
	 अगर(mf & HalfDCLK) अणु
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,SiS_GetReg(SiS_Pr->SiS_P3c4,0x2b));
	    clkb = SiS_GetReg(SiS_Pr->SiS_P3c4,0x2c);
	    clkb = (((clkb & 0x1f) << 1) + 1) | (clkb & 0xe0);
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,clkb);
	 पूर्ण
      पूर्ण
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
   पूर्ण
पूर्ण

/*********************************************/
/*                  FIFO                     */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_300
व्योम
SiS_GetFIFOThresholdIndex300(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *idx1,
		अचिन्हित लघु *idx2)
अणु
   अचिन्हित लघु temp1, temp2;
   अटल स्थिर अचिन्हित अक्षर ThTiming[8] = अणु
		1, 2, 2, 3, 0, 1, 1, 2
   पूर्ण;

   temp1 = temp2 = (SiS_GetReg(SiS_Pr->SiS_P3c4,0x18) & 0x62) >> 1;
   (*idx2) = (अचिन्हित लघु)(ThTiming[((temp2 >> 3) | temp1) & 0x07]);
   (*idx1) = (अचिन्हित लघु)(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) >> 6) & 0x03;
   (*idx1) |= (अचिन्हित लघु)(((SiS_GetReg(SiS_Pr->SiS_P3c4,0x14) >> 4) & 0x0c));
   (*idx1) <<= 1;
पूर्ण

अटल अचिन्हित लघु
SiS_GetFIFOThresholdA300(अचिन्हित लघु idx1, अचिन्हित लघु idx2)
अणु
   अटल स्थिर अचिन्हित अक्षर ThLowA[8 * 3] = अणु
		61, 3,52, 5,68, 7,100,11,
		43, 3,42, 5,54, 7, 78,11,
		34, 3,37, 5,47, 7, 67,11
   पूर्ण;

   वापस (अचिन्हित लघु)((ThLowA[idx1 + 1] * idx2) + ThLowA[idx1]);
पूर्ण

अचिन्हित लघु
SiS_GetFIFOThresholdB300(अचिन्हित लघु idx1, अचिन्हित लघु idx2)
अणु
   अटल स्थिर अचिन्हित अक्षर ThLowB[8 * 3] = अणु
		81, 4,72, 6,88, 8,120,12,
		55, 4,54, 6,66, 8, 90,12,
		42, 4,45, 6,55, 8, 75,12
   पूर्ण;

   वापस (अचिन्हित लघु)((ThLowB[idx1 + 1] * idx2) + ThLowB[idx1]);
पूर्ण

अटल अचिन्हित लघु
SiS_DoCalcDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु MCLK, अचिन्हित लघु VCLK,
		अचिन्हित लघु colordepth, अचिन्हित लघु key)
अणु
   अचिन्हित लघु idx1, idx2;
   अचिन्हित पूर्णांक   दीर्घtemp = VCLK * colordepth;

   SiS_GetFIFOThresholdIndex300(SiS_Pr, &idx1, &idx2);

   अगर(key == 0) अणु
      दीर्घtemp *= SiS_GetFIFOThresholdA300(idx1, idx2);
   पूर्ण अन्यथा अणु
      दीर्घtemp *= SiS_GetFIFOThresholdB300(idx1, idx2);
   पूर्ण
   idx1 = दीर्घtemp % (MCLK * 16);
   दीर्घtemp /= (MCLK * 16);
   अगर(idx1) दीर्घtemp++;
   वापस (अचिन्हित लघु)दीर्घtemp;
पूर्ण

अटल अचिन्हित लघु
SiS_CalcDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु VCLK,
		अचिन्हित लघु colordepth, अचिन्हित लघु MCLK)
अणु
   अचिन्हित लघु temp1, temp2;

   temp2 = SiS_DoCalcDelay(SiS_Pr, MCLK, VCLK, colordepth, 0);
   temp1 = SiS_DoCalcDelay(SiS_Pr, MCLK, VCLK, colordepth, 1);
   अगर(temp1 < 4) temp1 = 4;
   temp1 -= 4;
   अगर(temp2 < temp1) temp2 = temp1;
   वापस temp2;
पूर्ण

अटल व्योम
SiS_SetCRT1FIFO_300(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु ThresholdLow = 0;
   अचिन्हित लघु temp, index, VCLK, MCLK, colorth;
   अटल स्थिर अचिन्हित लघु colortharray[6] = अणु 1, 1, 2, 2, 3, 4 पूर्ण;

   अगर(ModeNo > 0x13) अणु

      /* Get VCLK  */
      अगर(SiS_Pr->UseCustomMode) अणु
	 VCLK = SiS_Pr->CSRClock;
      पूर्ण अन्यथा अणु
	 index = SiS_GetRefCRTVCLK(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWide);
	 VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
      पूर्ण

      /* Get half colordepth */
      colorth = colortharray[(SiS_Pr->SiS_ModeType - ModeEGA)];

      /* Get MCLK  */
      index = SiS_GetReg(SiS_Pr->SiS_P3c4,0x3A) & 0x07;
      MCLK = SiS_Pr->SiS_MCLKData_0[index].CLOCK;

      temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35) & 0xc3;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x16,0x3c,temp);

      करो अणु
	 ThresholdLow = SiS_CalcDelay(SiS_Pr, VCLK, colorth, MCLK) + 1;
	 अगर(ThresholdLow < 0x13) अवरोध;
	 SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x16,0xfc);
	 ThresholdLow = 0x13;
	 temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) >> 6;
	 अगर(!temp) अवरोध;
	 SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x16,0x3f,((temp - 1) << 6));
      पूर्ण जबतक(0);

   पूर्ण अन्यथा ThresholdLow = 2;

   /* Write CRT/CPU threshold low, CRT/Engine threshold high */
   temp = (ThresholdLow << 4) | 0x0f;
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,temp);

   temp = (ThresholdLow & 0x10) << 1;
   अगर(ModeNo > 0x13) temp |= 0x40;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0f,0x9f,temp);

   /* What is this? */
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x3B,0x09);

   /* Write CRT/CPU threshold high */
   temp = ThresholdLow + 3;
   अगर(temp > 0x0f) temp = 0x0f;
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x09,temp);
पूर्ण

अचिन्हित लघु
SiS_GetLatencyFactor630(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु index)
अणु
   अटल स्थिर अचिन्हित अक्षर LatencyFactor[] = अणु
		97, 88, 86, 79, 77,  0,       /* 64  bit    BQ=2   */
		 0, 87, 85, 78, 76, 54,       /* 64  bit    BQ=1   */
		97, 88, 86, 79, 77,  0,       /* 128 bit    BQ=2   */
		 0, 79, 77, 70, 68, 48,       /* 128 bit    BQ=1   */
		80, 72, 69, 63, 61,  0,       /* 64  bit    BQ=2   */
		 0, 70, 68, 61, 59, 37,       /* 64  bit    BQ=1   */
		86, 77, 75, 68, 66,  0,       /* 128 bit    BQ=2   */
		 0, 68, 66, 59, 57, 37        /* 128 bit    BQ=1   */
   पूर्ण;
   अटल स्थिर अचिन्हित अक्षर LatencyFactor730[] = अणु
		 69, 63, 61,
		 86, 79, 77,
		103, 96, 94,
		120,113,111,
		137,130,128
   पूर्ण;

   अगर(SiS_Pr->ChipType == SIS_730) अणु
      वापस (अचिन्हित लघु)LatencyFactor730[index];
   पूर्ण अन्यथा अणु
      वापस (अचिन्हित लघु)LatencyFactor[index];
   पूर्ण
पूर्ण

अटल अचिन्हित लघु
SiS_CalcDelay2(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर key)
अणु
   अचिन्हित लघु index;

   अगर(SiS_Pr->ChipType == SIS_730) अणु
      index = ((key & 0x0f) * 3) + ((key & 0xc0) >> 6);
   पूर्ण अन्यथा अणु
      index = (key & 0xe0) >> 5;
      अगर(key & 0x10)    index +=  6;
      अगर(!(key & 0x01)) index += 24;
      अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x14) & 0x80) index += 12;
   पूर्ण
   वापस SiS_GetLatencyFactor630(SiS_Pr, index);
पूर्ण

अटल व्योम
SiS_SetCRT1FIFO_630(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
                    अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु  ThresholdLow = 0;
   अचिन्हित लघु  i, data, VCLK, MCLK16, colorth = 0;
   अचिन्हित पूर्णांक    templ, datal;
   स्थिर अचिन्हित अक्षर *queuedata = शून्य;
   अटल स्थिर अचिन्हित अक्षर FQBQData[21] = अणु
		0x01,0x21,0x41,0x61,0x81,
		0x31,0x51,0x71,0x91,0xb1,
		0x00,0x20,0x40,0x60,0x80,
		0x30,0x50,0x70,0x90,0xb0,
		0xff
   पूर्ण;
   अटल स्थिर अचिन्हित अक्षर FQBQData730[16] = अणु
		0x34,0x74,0xb4,
		0x23,0x63,0xa3,
		0x12,0x52,0x92,
		0x01,0x41,0x81,
		0x00,0x40,0x80,
		0xff
   पूर्ण;
   अटल स्थिर अचिन्हित लघु colortharray[6] = अणु
		1, 1, 2, 2, 3, 4
   पूर्ण;

   i = 0;

	अगर (SiS_Pr->ChipType == SIS_730)
		queuedata = &FQBQData730[0];
	अन्यथा
		queuedata = &FQBQData[0];

   अगर(ModeNo > 0x13) अणु

      /* Get VCLK  */
      अगर(SiS_Pr->UseCustomMode) अणु
	 VCLK = SiS_Pr->CSRClock;
      पूर्ण अन्यथा अणु
	 data = SiS_GetRefCRTVCLK(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWide);
	 VCLK = SiS_Pr->SiS_VCLKData[data].CLOCK;
      पूर्ण

      /* Get MCLK * 16 */
      data = SiS_GetReg(SiS_Pr->SiS_P3c4,0x1A) & 0x07;
      MCLK16 = SiS_Pr->SiS_MCLKData_0[data].CLOCK * 16;

      /* Get half colordepth */
      colorth = colortharray[(SiS_Pr->SiS_ModeType - ModeEGA)];

      करो अणु
	 templ = SiS_CalcDelay2(SiS_Pr, queuedata[i]) * VCLK * colorth;

	 datal = templ % MCLK16;
	 templ = (templ / MCLK16) + 1;
	 अगर(datal) templ++;

	 अगर(templ > 0x13) अणु
	    अगर(queuedata[i + 1] == 0xFF) अणु
	       ThresholdLow = 0x13;
	       अवरोध;
	    पूर्ण
	    i++;
	 पूर्ण अन्यथा अणु
	    ThresholdLow = templ;
	    अवरोध;
	 पूर्ण
      पूर्ण जबतक(queuedata[i] != 0xFF);

   पूर्ण अन्यथा अणु

      अगर(SiS_Pr->ChipType != SIS_730) i = 9;
      ThresholdLow = 0x02;

   पूर्ण

   /* Write CRT/CPU threshold low, CRT/Engine threshold high */
   data = ((ThresholdLow & 0x0f) << 4) | 0x0f;
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,data);

   data = (ThresholdLow & 0x10) << 1;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0F,0xDF,data);

   /* What is this? */
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x3B,0x09);

   /* Write CRT/CPU threshold high (gap = 3) */
   data = ThresholdLow + 3;
   अगर(data > 0x0f) data = 0x0f;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x09,0x80,data);

  /* Write क्रमeground and background queue */
   templ = sisfb_पढ़ो_nbridge_pci_dword(SiS_Pr, 0x50);

   अगर(SiS_Pr->ChipType == SIS_730) अणु

      templ &= 0xfffff9ff;
      templ |= ((queuedata[i] & 0xc0) << 3);

   पूर्ण अन्यथा अणु

      templ &= 0xf0ffffff;
      अगर( (ModeNo <= 0x13) &&
          (SiS_Pr->ChipType == SIS_630) &&
	  (SiS_Pr->ChipRevision >= 0x30) ) अणु
	 templ |= 0x0b000000;
      पूर्ण अन्यथा अणु
         templ |= ((queuedata[i] & 0xf0) << 20);
      पूर्ण

   पूर्ण

   sisfb_ग_लिखो_nbridge_pci_dword(SiS_Pr, 0x50, templ);
   templ = sisfb_पढ़ो_nbridge_pci_dword(SiS_Pr, 0xA0);

   /* GUI grant समयr (PCI config 0xA3) */
   अगर(SiS_Pr->ChipType == SIS_730) अणु

      templ &= 0x00ffffff;
      datal = queuedata[i] << 8;
      templ |= (((datal & 0x0f00) | ((datal & 0x3000) >> 8)) << 20);

   पूर्ण अन्यथा अणु

      templ &= 0xf0ffffff;
      templ |= ((queuedata[i] & 0x0f) << 24);

   पूर्ण

   sisfb_ग_लिखो_nbridge_pci_dword(SiS_Pr, 0xA0, templ);
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_SIS_300 */

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS_SetCRT1FIFO_310(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु modeflag;

   /* disable स्वतः-threshold */
   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x3D,0xFE);

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,0xAE);
   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x09,0xF0);
   अगर(ModeNo > 0x13) अणु
      अगर(SiS_Pr->ChipType >= XGI_20) अणु
	 SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,0x34);
	 SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x3D,0x01);
      पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) अणु
	 अगर(!(modeflag & HalfDCLK)) अणु
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,0x34);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x3D,0x01);
	 पूर्ण
      पूर्ण अन्यथा अणु
	 अगर((!(modeflag & DoubleScanMode)) || (!(modeflag & HalfDCLK))) अणु
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x08,0x34);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x3D,0x01);
	 पूर्ण
      पूर्ण
   पूर्ण
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*              MODE REGISTERS               */
/*********************************************/

अटल व्योम
SiS_SetVCLKState(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु RefreshRateTableIndex, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु data = 0, VCLK = 0, index = 0;

   अगर(ModeNo > 0x13) अणु
      अगर(SiS_Pr->UseCustomMode) अणु
         VCLK = SiS_Pr->CSRClock;
      पूर्ण अन्यथा अणु
         index = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
         VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      अगर(VCLK > 150) data |= 0x80;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0x7B,data);

      data = 0x00;
      अगर(VCLK >= 150) data |= 0x08;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xF7,data);
#पूर्ण_अगर
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType < XGI_20) अणु
#अगर_घोषित CONFIG_FB_SIS_315
      अगर(VCLK >= 166) data |= 0x0c;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xf3,data);

      अगर(VCLK >= 166) अणु
         SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1f,0xe7);
      पूर्ण
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
      अगर(VCLK >= 200) data |= 0x0c;
      अगर(SiS_Pr->ChipType == XGI_20) data &= ~0x04;
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x32,0xf3,data);
      अगर(SiS_Pr->ChipType != XGI_20) अणु
         data = SiS_GetReg(SiS_Pr->SiS_P3c4,0x1f) & 0xe7;
	 अगर(VCLK < 200) data |= 0x10;
	 SiS_SetReg(SiS_Pr->SiS_P3c4,0x1f,data);
      पूर्ण
#पूर्ण_अगर
   पूर्ण

   /* DAC speed */
   अगर(SiS_Pr->ChipType >= SIS_661) अणु

      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xE8,0x10);

   पूर्ण अन्यथा अणु

      data = 0x03;
      अगर(VCLK >= 260)      data = 0x00;
      अन्यथा अगर(VCLK >= 160) data = 0x01;
      अन्यथा अगर(VCLK >= 135) data = 0x02;

      अगर(SiS_Pr->ChipType == SIS_540) अणु
         /* Was == 203 or < 234 which made no sense */
         अगर (VCLK < 234) data = 0x02;
      पूर्ण

      अगर(SiS_Pr->ChipType < SIS_315H) अणु
         SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xFC,data);
      पूर्ण अन्यथा अणु
         अगर(SiS_Pr->ChipType > SIS_315PRO) अणु
            अगर(ModeNo > 0x13) data &= 0xfc;
         पूर्ण
         SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x07,0xF8,data);
      पूर्ण

   पूर्ण
पूर्ण

अटल व्योम
SiS_SetCRT1ModeRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु data, infoflag = 0, modeflag;
#अगर_घोषित CONFIG_FB_SIS_315
   अचिन्हित अक्षर  *ROMAddr  = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु data2, data3;
#पूर्ण_अगर

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(SiS_Pr->UseCustomMode) अणु
      infoflag = SiS_Pr->CInfoFlag;
   पूर्ण अन्यथा अणु
      अगर(ModeNo > 0x13) अणु
	 infoflag = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag;
      पूर्ण
   पूर्ण

   /* Disable DPMS */
   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1F,0x3F);

   data = 0;
   अगर(ModeNo > 0x13) अणु
      अगर(SiS_Pr->SiS_ModeType > ModeEGA) अणु
         data |= 0x02;
         data |= ((SiS_Pr->SiS_ModeType - ModeVGA) << 2);
      पूर्ण
      अगर(infoflag & InterlaceMode) data |= 0x20;
   पूर्ण
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x06,0xC0,data);

   अगर(SiS_Pr->ChipType != SIS_300) अणु
      data = 0;
      अगर(infoflag & InterlaceMode) अणु
	 /* data = (Hsync / 8) - ((Htotal / 8) / 2) + 3 */
	 पूर्णांक hrs = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x04) |
		    ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x0b) & 0xc0) << 2)) - 3;
	 पूर्णांक hto = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x00) |
		    ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x0b) & 0x03) << 8)) + 5;
	 data = hrs - (hto >> 1) + 3;
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x19,data);
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x1a,0xFC,((data >> 8) & 0x03));
   पूर्ण

   अगर(modeflag & HalfDCLK) अणु
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x01,0x08);
   पूर्ण

   data = 0;
   अगर(modeflag & LineCompareOff) data = 0x08;
   अगर(SiS_Pr->ChipType == SIS_300) अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0F,0xF7,data);
   पूर्ण अन्यथा अणु
      अगर(SiS_Pr->ChipType >= XGI_20) data |= 0x20;
      अगर(SiS_Pr->SiS_ModeType == ModeEGA) अणु
	 अगर(ModeNo > 0x13) अणु
	    data |= 0x40;
	 पूर्ण
      पूर्ण
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0F,0xB7,data);
   पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x31,0xfb);
   पूर्ण

   अगर(SiS_Pr->ChipType == SIS_315PRO) अणु

      data = SiS_Pr->SiS_SR15[(2 * 4) + SiS_Get310DRAMType(SiS_Pr)];
      अगर(SiS_Pr->SiS_ModeType == ModeText) अणु
	 data &= 0xc7;
      पूर्ण अन्यथा अणु
	 data2 = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, RRTI) >> 1;
	 अगर(infoflag & InterlaceMode) data2 >>= 1;
	 data3 = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex) >> 1;
	 अगर(data3) data2 /= data3;
	 अगर(data2 >= 0x50) अणु
	    data &= 0x0f;
	    data |= 0x50;
	 पूर्ण
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x17,data);

   पूर्ण अन्यथा अगर((SiS_Pr->ChipType == SIS_330) || (SiS_Pr->SiS_SysFlags & SF_760LFB)) अणु

      data = SiS_Get310DRAMType(SiS_Pr);
      अगर(SiS_Pr->ChipType == SIS_330) अणु
	 data = SiS_Pr->SiS_SR15[(2 * 4) + data];
      पूर्ण अन्यथा अणु
	 अगर(SiS_Pr->SiS_ROMNew)	     data = ROMAddr[0xf6];
	 अन्यथा अगर(SiS_Pr->SiS_UseROM) data = ROMAddr[0x100 + data];
	 अन्यथा			     data = 0xba;
      पूर्ण
      अगर(SiS_Pr->SiS_ModeType <= ModeEGA) अणु
	 data &= 0xc7;
      पूर्ण अन्यथा अणु
	 अगर(SiS_Pr->UseCustomMode) अणु
	    data2 = SiS_Pr->CSRClock;
	 पूर्ण अन्यथा अणु
	    data2 = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
	    data2 = SiS_Pr->SiS_VCLKData[data2].CLOCK;
	 पूर्ण

	 data3 = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex) >> 1;
	 अगर(data3) data2 *= data3;

	 data2 = ((अचिन्हित पूर्णांक)(SiS_GetMCLK(SiS_Pr) * 1024)) / data2;

	 अगर(SiS_Pr->ChipType == SIS_330) अणु
	    अगर(SiS_Pr->SiS_ModeType != Mode16Bpp) अणु
	       अगर     (data2 >= 0x19c) data = 0xba;
	       अन्यथा अगर(data2 >= 0x140) data = 0x7a;
	       अन्यथा अगर(data2 >= 0x101) data = 0x3a;
	       अन्यथा अगर(data2 >= 0xf5)  data = 0x32;
	       अन्यथा अगर(data2 >= 0xe2)  data = 0x2a;
	       अन्यथा अगर(data2 >= 0xc4)  data = 0x22;
	       अन्यथा अगर(data2 >= 0xac)  data = 0x1a;
	       अन्यथा अगर(data2 >= 0x9e)  data = 0x12;
	       अन्यथा अगर(data2 >= 0x8e)  data = 0x0a;
	       अन्यथा                    data = 0x02;
	    पूर्ण अन्यथा अणु
	       अगर(data2 >= 0x127)      data = 0xba;
	       अन्यथा                    data = 0x7a;
	    पूर्ण
	 पूर्ण अन्यथा अणु  /* 76x+LFB */
	    अगर     (data2 >= 0x190) data = 0xba;
	    अन्यथा अगर(data2 >= 0xff)  data = 0x7a;
	    अन्यथा अगर(data2 >= 0xd3)  data = 0x3a;
	    अन्यथा अगर(data2 >= 0xa9)  data = 0x1a;
	    अन्यथा अगर(data2 >= 0x93)  data = 0x0a;
	    अन्यथा                    data = 0x02;
	 पूर्ण
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x17,data);

   पूर्ण
      /* XGI: Nothing. */
      /* TODO: Check SiS340 */
#पूर्ण_अगर

   data = 0x60;
   अगर(SiS_Pr->SiS_ModeType != ModeText) अणु
      data ^= 0x60;
      अगर(SiS_Pr->SiS_ModeType != ModeEGA) अणु
         data ^= 0xA0;
      पूर्ण
   पूर्ण
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x21,0x1F,data);

   SiS_SetVCLKState(SiS_Pr, ModeNo, RRTI, ModeIdIndex);

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->ChipType < SIS_661)) ||
       (SiS_Pr->ChipType == XGI_40)) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) अणु
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x2c);
      पूर्ण अन्यथा अणु
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x6c);
      पूर्ण
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType == XGI_20) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) अणु
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x33);
      पूर्ण अन्यथा अणु
         SiS_SetReg(SiS_Pr->SiS_P3d4,0x52,0x73);
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_P3d4,0x51,0x02);
   पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS_SetupDualChip(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर 0
   /* TODO: Find out about IOAddress2 */
   SISIOADDRESS P2_3c2 = SiS_Pr->IOAddress2 + 0x12;
   SISIOADDRESS P2_3c4 = SiS_Pr->IOAddress2 + 0x14;
   SISIOADDRESS P2_3ce = SiS_Pr->IOAddress2 + 0x1e;
   पूर्णांक i;

   अगर((SiS_Pr->ChipRevision != 0) ||
      (!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x3a) & 0x04)))
      वापस;

   क्रम(i = 0; i <= 4; i++) अणु					/* SR00 - SR04 */
      SiS_SetReg(P2_3c4,i,SiS_GetReg(SiS_Pr->SiS_P3c4,i));
   पूर्ण
   क्रम(i = 0; i <= 8; i++) अणु					/* GR00 - GR08 */
      SiS_SetReg(P2_3ce,i,SiS_GetReg(SiS_Pr->SiS_P3ce,i));
   पूर्ण
   SiS_SetReg(P2_3c4,0x05,0x86);
   SiS_SetReg(P2_3c4,0x06,SiS_GetReg(SiS_Pr->SiS_P3c4,0x06));	/* SR06 */
   SiS_SetReg(P2_3c4,0x21,SiS_GetReg(SiS_Pr->SiS_P3c4,0x21));	/* SR21 */
   SiS_SetRegByte(P2_3c2,SiS_GetRegByte(SiS_Pr->SiS_P3cc));	/* MISC */
   SiS_SetReg(P2_3c4,0x05,0x00);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*                 LOAD DAC                  */
/*********************************************/

अटल व्योम
SiS_WriteDAC(काष्ठा SiS_Private *SiS_Pr, SISIOADDRESS DACData, अचिन्हित लघु shअगरtflag,
             अचिन्हित लघु dl, अचिन्हित लघु ah, अचिन्हित लघु al, अचिन्हित लघु dh)
अणु
   अचिन्हित लघु d1, d2, d3;

   चयन(dl) अणु
   हाल  0: d1 = dh; d2 = ah; d3 = al; अवरोध;
   हाल  1: d1 = ah; d2 = al; d3 = dh; अवरोध;
   शेष: d1 = al; d2 = dh; d3 = ah;
   पूर्ण
   SiS_SetRegByte(DACData, (d1 << shअगरtflag));
   SiS_SetRegByte(DACData, (d2 << shअगरtflag));
   SiS_SetRegByte(DACData, (d3 << shअगरtflag));
पूर्ण

व्योम
SiS_LoadDAC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु data, data2, समय, i, j, k, m, n, o;
   अचिन्हित लघु si, di, bx, sf;
   SISIOADDRESS DACAddr, DACData;
   स्थिर अचिन्हित अक्षर *table = शून्य;

   data = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex) & DACInfoFlag;

   j = समय = 64;
   अगर(data == 0x00)      table = SiS_MDA_DAC;
   अन्यथा अगर(data == 0x08) table = SiS_CGA_DAC;
   अन्यथा अगर(data == 0x10) table = SiS_EGA_DAC;
   अन्यथा अगर(data == 0x18) अणु
      j = 16;
      समय = 256;
      table = SiS_VGA_DAC;
   पूर्ण

   अगर( ( (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) &&        /* 301B-DH LCD */
         (SiS_Pr->SiS_VBType & VB_NoLCD) )        ||
       (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)       ||   /* LCDA */
       (!(SiS_Pr->SiS_SetFlag & ProgrammingCRT2)) ) अणु  /* Programming CRT1 */
      SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xFF);
      DACAddr = SiS_Pr->SiS_P3c8;
      DACData = SiS_Pr->SiS_P3c9;
      sf = 0;
   पूर्ण अन्यथा अणु
      DACAddr = SiS_Pr->SiS_Part5Port;
      DACData = SiS_Pr->SiS_Part5Port + 1;
      sf = 2;
   पूर्ण

   SiS_SetRegByte(DACAddr,0x00);

   क्रम(i = 0; i < j; i++) अणु
      data = table[i];
      क्रम(k = 0; k < 3; k++) अणु
	data2 = 0;
	अगर(data & 0x01) data2 += 0x2A;
	अगर(data & 0x02) data2 += 0x15;
	SiS_SetRegByte(DACData, (data2 << sf));
	data >>= 2;
      पूर्ण
   पूर्ण

   अगर(समय == 256) अणु
      क्रम(i = 16; i < 32; i++) अणु
	 data = table[i] << sf;
	 क्रम(k = 0; k < 3; k++) SiS_SetRegByte(DACData, data);
      पूर्ण
      si = 32;
      क्रम(m = 0; m < 9; m++) अणु
	 di = si;
	 bx = si + 4;
	 क्रम(n = 0; n < 3; n++) अणु
	    क्रम(o = 0; o < 5; o++) अणु
	       SiS_WriteDAC(SiS_Pr, DACData, sf, n, table[di], table[bx], table[si]);
	       si++;
	    पूर्ण
	    si -= 2;
	    क्रम(o = 0; o < 3; o++) अणु
	       SiS_WriteDAC(SiS_Pr, DACData, sf, n, table[di], table[si], table[bx]);
	       si--;
	    पूर्ण
	 पूर्ण            /* क्रम n < 3 */
	 si += 5;
      पूर्ण               /* क्रम m < 9 */
   पूर्ण
पूर्ण

/*********************************************/
/*         SET CRT1 REGISTER GROUP           */
/*********************************************/

अटल व्योम
SiS_SetCRT1Group(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु StandTableIndex, RefreshRateTableIndex;

   SiS_Pr->SiS_CRT1Mode = ModeNo;

   StandTableIndex = SiS_GetModePtr(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
      अगर(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2)) अणु
         SiS_DisableBridge(SiS_Pr);
      पूर्ण
   पूर्ण

   SiS_ResetSegmentRegisters(SiS_Pr);

   SiS_SetSeqRegs(SiS_Pr, StandTableIndex);
   SiS_SetMiscRegs(SiS_Pr, StandTableIndex);
   SiS_SetCRTCRegs(SiS_Pr, StandTableIndex);
   SiS_SetATTRegs(SiS_Pr, StandTableIndex);
   SiS_SetGRCRegs(SiS_Pr, StandTableIndex);
   SiS_ClearExt1Regs(SiS_Pr, ModeNo);
   SiS_ResetCRT1VCLK(SiS_Pr);

   SiS_Pr->SiS_SelectCRT2Rate = 0;
   SiS_Pr->SiS_SetFlag &= (~ProgrammingCRT2);

   अगर(SiS_Pr->SiS_VBInfo & SetSimuScanMode) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
         SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
      SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
   पूर्ण

   RefreshRateTableIndex = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
      SiS_Pr->SiS_SetFlag &= ~ProgrammingCRT2;
   पूर्ण

   अगर(RefreshRateTableIndex != 0xFFFF) अणु
      SiS_SetCRT1Sync(SiS_Pr, RefreshRateTableIndex);
      SiS_SetCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_SetCRT1Offset(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_SetCRT1VCLK(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
   पूर्ण

   चयन(SiS_Pr->ChipType) अणु
#अगर_घोषित CONFIG_FB_SIS_300
   हाल SIS_300:
      SiS_SetCRT1FIFO_300(SiS_Pr, ModeNo, RefreshRateTableIndex);
      अवरोध;
   हाल SIS_540:
   हाल SIS_630:
   हाल SIS_730:
      SiS_SetCRT1FIFO_630(SiS_Pr, ModeNo, RefreshRateTableIndex);
      अवरोध;
#पूर्ण_अगर
   शेष:
#अगर_घोषित CONFIG_FB_SIS_315
      अगर(SiS_Pr->ChipType == XGI_20) अणु
         अचिन्हित अक्षर sr2b = 0, sr2c = 0;
         चयन(ModeNo) अणु
	 हाल 0x00:
	 हाल 0x01: sr2b = 0x4e; sr2c = 0xe9; अवरोध;
	 हाल 0x04:
	 हाल 0x05:
	 हाल 0x0d: sr2b = 0x1b; sr2c = 0xe3; अवरोध;
	 पूर्ण
	 अगर(sr2b) अणु
            SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,sr2b);
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,sr2c);
	    SiS_SetRegByte(SiS_Pr->SiS_P3c2,(SiS_GetRegByte(SiS_Pr->SiS_P3cc) | 0x0c));
	 पूर्ण
      पूर्ण
      SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);
#पूर्ण_अगर
      अवरोध;
   पूर्ण

   SiS_SetCRT1ModeRegs(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType == XGI_40) अणु
      SiS_SetupDualChip(SiS_Pr);
   पूर्ण
#पूर्ण_अगर

   SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(SiS_Pr->SiS_flag_clearbuffer) अणु
      SiS_ClearBuffer(SiS_Pr, ModeNo);
   पूर्ण

   अगर(!(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2 | SetCRT2ToLCDA))) अणु
      SiS_WaitRetrace1(SiS_Pr);
      SiS_DisplayOn(SiS_Pr);
   पूर्ण
पूर्ण

/*********************************************/
/*       HELPER: VIDEO BRIDGE PROG CLK       */
/*********************************************/

अटल व्योम
SiS_InitVB(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर *ROMAddr = SiS_Pr->VirtualRomBase;

   SiS_Pr->Init_P4_0E = 0;
   अगर(SiS_Pr->SiS_ROMNew) अणु
      SiS_Pr->Init_P4_0E = ROMAddr[0x82];
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= XGI_40) अणु
      अगर(SiS_Pr->SiS_XGIROM) अणु
         SiS_Pr->Init_P4_0E = ROMAddr[0x80];
      पूर्ण
   पूर्ण
पूर्ण

अटल व्योम
SiS_ResetVB(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु temp;

   /* VB programming घड़ी */
   अगर(SiS_Pr->SiS_UseROM) अणु
      अगर(SiS_Pr->ChipType < SIS_330) अणु
	 temp = ROMAddr[VB310Data_1_2_Offset] | 0x40;
	 अगर(SiS_Pr->SiS_ROMNew) temp = ROMAddr[0x80] | 0x40;
	 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x02,temp);
      पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661 && SiS_Pr->ChipType < XGI_20) अणु
	 temp = ROMAddr[0x7e] | 0x40;
	 अगर(SiS_Pr->SiS_ROMNew) temp = ROMAddr[0x80] | 0x40;
	 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x02,temp);
      पूर्ण
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= XGI_40) अणु
      temp = 0x40;
      अगर(SiS_Pr->SiS_XGIROM) temp |= ROMAddr[0x7e];
      /* Can we करो this on any chipset? */
      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x02,temp);
   पूर्ण
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*    HELPER: SET VIDEO/CAPTURE REGISTERS    */
/*********************************************/

अटल व्योम
SiS_StrangeStuff(काष्ठा SiS_Private *SiS_Pr)
अणु
   /* SiS65x and XGI set up some sort of "lock mode" क्रम text
    * which locks CRT2 in some way to CRT1 timing. Disable
    * this here.
    */
#अगर_घोषित CONFIG_FB_SIS_315
   अगर((IS_SIS651) || (IS_SISM650) ||
      SiS_Pr->ChipType == SIS_340 ||
      SiS_Pr->ChipType == XGI_40) अणु
      SiS_SetReg(SiS_Pr->SiS_VidCapt, 0x3f, 0x00);   /* Fiddle with capture regs */
      SiS_SetReg(SiS_Pr->SiS_VidCapt, 0x00, 0x00);
      SiS_SetReg(SiS_Pr->SiS_VidPlay, 0x00, 0x86);   /* (BIOS करोes NOT unlock) */
      SiS_SetRegAND(SiS_Pr->SiS_VidPlay, 0x30, 0xfe); /* Fiddle with video regs */
      SiS_SetRegAND(SiS_Pr->SiS_VidPlay, 0x3f, 0xef);
   पूर्ण
   /* !!! This करोes not support modes < 0x13 !!! */
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*     HELPER: SET AGP TIMING FOR SiS760     */
/*********************************************/

अटल व्योम
SiS_Handle760(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अचिन्हित पूर्णांक somebase;
   अचिन्हित अक्षर temp1, temp2, temp3;

   अगर( (SiS_Pr->ChipType != SIS_760)                         ||
       ((SiS_GetReg(SiS_Pr->SiS_P3d4, 0x5c) & 0xf8) != 0x80) ||
       (!(SiS_Pr->SiS_SysFlags & SF_760LFB))                 ||
       (!(SiS_Pr->SiS_SysFlags & SF_760UMA)) )
      वापस;

   somebase = sisfb_पढ़ो_mio_pci_word(SiS_Pr, 0x74);
   somebase &= 0xffff;

   अगर(somebase == 0) वापस;

   temp3 = SiS_GetRegByte((somebase + 0x85)) & 0xb7;

   अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) अणु
      temp1 = 0x21;
      temp2 = 0x03;
      temp3 |= 0x08;
   पूर्ण अन्यथा अणु
      temp1 = 0x25;
      temp2 = 0x0b;
   पूर्ण

   sisfb_ग_लिखो_nbridge_pci_byte(SiS_Pr, 0x7e, temp1);
   sisfb_ग_लिखो_nbridge_pci_byte(SiS_Pr, 0x8d, temp2);

   SiS_SetRegByte((somebase + 0x85), temp3);
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*                 SiSSetMode()              */
/*********************************************/

bool
SiSSetMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   SISIOADDRESS BaseAddr = SiS_Pr->IOAddress;
   अचिन्हित लघु RealModeNo, ModeIdIndex;
   अचिन्हित अक्षर  backupreg = 0;
   अचिन्हित लघु KeepLockReg;

   SiS_Pr->UseCustomMode = false;
   SiS_Pr->CRT1UsesCustomMode = false;

   SiS_Pr->SiS_flag_clearbuffer = 0;

   अगर(SiS_Pr->UseCustomMode) अणु
      ModeNo = 0xfe;
   पूर्ण अन्यथा अणु
      अगर(!(ModeNo & 0x80)) SiS_Pr->SiS_flag_clearbuffer = 1;
      ModeNo &= 0x7f;
   पूर्ण

   /* Don't use FSTN mode क्रम CRT1 */
   RealModeNo = ModeNo;
   अगर(ModeNo == 0x5b) ModeNo = 0x56;

   SiSInitPtr(SiS_Pr);
   SiSRegInit(SiS_Pr, BaseAddr);
   SiS_GetSysFlags(SiS_Pr);

   SiS_Pr->SiS_VGAINFO = 0x11;

   KeepLockReg = SiS_GetReg(SiS_Pr->SiS_P3c4,0x05);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x05,0x86);

   SiSInitPCIetc(SiS_Pr);
   SiSSetLVDSetc(SiS_Pr);
   SiSDetermineROMUsage(SiS_Pr);

   SiS_UnLockCRT2(SiS_Pr);

   अगर(!SiS_Pr->UseCustomMode) अणु
      अगर(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) वापस false;
   पूर्ण अन्यथा अणु
      ModeIdIndex = 0;
   पूर्ण

   SiS_GetVBType(SiS_Pr);

   /* Init/restore some VB रेजिस्टरs */
   SiS_InitVB(SiS_Pr);
   अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
      अगर(SiS_Pr->ChipType >= SIS_315H) अणु
         SiS_ResetVB(SiS_Pr);
	 SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x32,0x10);
	 SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x00,0x0c);
         backupreg = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      पूर्ण अन्यथा अणु
         backupreg = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
      पूर्ण
   पूर्ण

   /* Get VB inक्रमmation (connectors, connected devices) */
   SiS_GetVBInfo(SiS_Pr, ModeNo, ModeIdIndex, (SiS_Pr->UseCustomMode) ? 0 : 1);
   SiS_SetYPbPr(SiS_Pr);
   SiS_SetTVMode(SiS_Pr, ModeNo, ModeIdIndex);
   SiS_GetLCDResInfo(SiS_Pr, ModeNo, ModeIdIndex);
   SiS_SetLowModeTest(SiS_Pr, ModeNo);

   /* Check memory size (kernel framebuffer driver only) */
   अगर(!SiS_CheckMemorySize(SiS_Pr, ModeNo, ModeIdIndex)) अणु
      वापस false;
   पूर्ण

   SiS_OpenCRTC(SiS_Pr);

   अगर(SiS_Pr->UseCustomMode) अणु
      SiS_Pr->CRT1UsesCustomMode = true;
      SiS_Pr->CSRClock_CRT1 = SiS_Pr->CSRClock;
      SiS_Pr->CModeFlag_CRT1 = SiS_Pr->CModeFlag;
   पूर्ण अन्यथा अणु
      SiS_Pr->CRT1UsesCustomMode = false;
   पूर्ण

   /* Set mode on CRT1 */
   अगर( (SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SetCRT2ToLCDA)) ||
       (!(SiS_Pr->SiS_VBInfo & SwitchCRT2)) ) अणु
      SiS_SetCRT1Group(SiS_Pr, ModeNo, ModeIdIndex);
   पूर्ण

   /* Set mode on CRT2 */
   अगर(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2 | SetCRT2ToLCDA)) अणु
      अगर( (SiS_Pr->SiS_VBType & VB_SISVB)    ||
	  (SiS_Pr->SiS_IF_DEF_LVDS     == 1) ||
	  (SiS_Pr->SiS_IF_DEF_CH70xx   != 0) ||
	  (SiS_Pr->SiS_IF_DEF_TRUMPION != 0) ) अणु
	 SiS_SetCRT2Group(SiS_Pr, RealModeNo);
      पूर्ण
   पूर्ण

   SiS_HandleCRT1(SiS_Pr);

   SiS_StrangeStuff(SiS_Pr);

   SiS_DisplayOn(SiS_Pr);
   SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xFF);

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	 अगर(!(SiS_IsDualEdge(SiS_Pr))) अणु
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	 पूर्ण
      पूर्ण
   पूर्ण
#पूर्ण_अगर

   अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
      अगर(SiS_Pr->ChipType >= SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_315
	 अगर(!SiS_Pr->SiS_ROMNew) अणु
	    अगर(SiS_IsVAMode(SiS_Pr)) अणु
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x35,0x01);
	    पूर्ण अन्यथा अणु
	       SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x35,0xFE);
	    पूर्ण
	 पूर्ण

	 SiS_SetReg(SiS_Pr->SiS_P3d4,0x38,backupreg);

	 अगर((IS_SIS650) && (SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & 0xfc)) अणु
	    अगर((ModeNo == 0x03) || (ModeNo == 0x10)) अणु
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x51,0x80);
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x56,0x08);
	    पूर्ण
	 पूर्ण

	 अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & SetCRT2ToLCD) अणु
	    SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x38,0xfc);
	 पूर्ण
#पूर्ण_अगर
      पूर्ण अन्यथा अगर((SiS_Pr->ChipType == SIS_630) ||
	        (SiS_Pr->ChipType == SIS_730)) अणु
	 SiS_SetReg(SiS_Pr->SiS_P3d4,0x35,backupreg);
      पूर्ण
   पूर्ण

   SiS_CloseCRTC(SiS_Pr);

   SiS_Handle760(SiS_Pr);

   /* We never lock रेजिस्टरs in XF86 */
   अगर(KeepLockReg != 0xA1) SiS_SetReg(SiS_Pr->SiS_P3c4,0x05,0x00);

   वापस true;
पूर्ण

#अगर_अघोषित GETBITSTR
#घोषणा GENBITSMASK(mask)   	GENMASK(1?mask,0?mask)
#घोषणा GETBITS(var,mask)   	(((var) & GENBITSMASK(mask)) >> (0?mask))
#घोषणा GETBITSTR(val,from,to)  ((GETBITS(val,from)) << (0?to))
#पूर्ण_अगर

व्योम
SiS_CalcCRRegisters(काष्ठा SiS_Private *SiS_Pr, पूर्णांक depth)
अणु
   पूर्णांक x = 1; /* Fix sync */

   SiS_Pr->CCRT1CRTC[0]  =  ((SiS_Pr->CHTotal >> 3) - 5) & 0xff;		/* CR0 */
   SiS_Pr->CCRT1CRTC[1]  =  (SiS_Pr->CHDisplay >> 3) - 1;			/* CR1 */
   SiS_Pr->CCRT1CRTC[2]  =  (SiS_Pr->CHBlankStart >> 3) - 1;			/* CR2 */
   SiS_Pr->CCRT1CRTC[3]  =  (((SiS_Pr->CHBlankEnd >> 3) - 1) & 0x1F) | 0x80;	/* CR3 */
   SiS_Pr->CCRT1CRTC[4]  =  (SiS_Pr->CHSyncStart >> 3) + 3;			/* CR4 */
   SiS_Pr->CCRT1CRTC[5]  =  ((((SiS_Pr->CHBlankEnd >> 3) - 1) & 0x20) << 2) |	/* CR5 */
			    (((SiS_Pr->CHSyncEnd >> 3) + 3) & 0x1F);

   SiS_Pr->CCRT1CRTC[6]  =  (SiS_Pr->CVTotal       - 2) & 0xFF;			/* CR6 */
   SiS_Pr->CCRT1CRTC[7]  =  (((SiS_Pr->CVTotal     - 2) & 0x100) >> 8)		/* CR7 */
			  | (((SiS_Pr->CVDisplay   - 1) & 0x100) >> 7)
			  | (((SiS_Pr->CVSyncStart - x) & 0x100) >> 6)
			  | (((SiS_Pr->CVBlankStart- 1) & 0x100) >> 5)
			  | 0x10
			  | (((SiS_Pr->CVTotal     - 2) & 0x200) >> 4)
			  | (((SiS_Pr->CVDisplay   - 1) & 0x200) >> 3)
			  | (((SiS_Pr->CVSyncStart - x) & 0x200) >> 2);

   SiS_Pr->CCRT1CRTC[16] = ((((SiS_Pr->CVBlankStart - 1) & 0x200) >> 4) >> 5); 	/* CR9 */

   अगर(depth != 8) अणु
      अगर(SiS_Pr->CHDisplay >= 1600)      SiS_Pr->CCRT1CRTC[16] |= 0x60;		/* SRE */
      अन्यथा अगर(SiS_Pr->CHDisplay >= 640)  SiS_Pr->CCRT1CRTC[16] |= 0x40;
   पूर्ण

   SiS_Pr->CCRT1CRTC[8] =  (SiS_Pr->CVSyncStart  - x) & 0xFF;			/* CR10 */
   SiS_Pr->CCRT1CRTC[9] =  ((SiS_Pr->CVSyncEnd   - x) & 0x0F) | 0x80;		/* CR11 */
   SiS_Pr->CCRT1CRTC[10] = (SiS_Pr->CVDisplay    - 1) & 0xFF;			/* CR12 */
   SiS_Pr->CCRT1CRTC[11] = (SiS_Pr->CVBlankStart - 1) & 0xFF;			/* CR15 */
   SiS_Pr->CCRT1CRTC[12] = (SiS_Pr->CVBlankEnd   - 1) & 0xFF;			/* CR16 */

   SiS_Pr->CCRT1CRTC[13] =							/* SRA */
			GETBITSTR((SiS_Pr->CVTotal     -2), 10:10, 0:0) |
			GETBITSTR((SiS_Pr->CVDisplay   -1), 10:10, 1:1) |
			GETBITSTR((SiS_Pr->CVBlankStart-1), 10:10, 2:2) |
			GETBITSTR((SiS_Pr->CVSyncStart -x), 10:10, 3:3) |
			GETBITSTR((SiS_Pr->CVBlankEnd  -1),   8:8, 4:4) |
			GETBITSTR((SiS_Pr->CVSyncEnd     ),   4:4, 5:5) ;

   SiS_Pr->CCRT1CRTC[14] =							/* SRB */
			GETBITSTR((SiS_Pr->CHTotal      >> 3) - 5, 9:8, 1:0) |
			GETBITSTR((SiS_Pr->CHDisplay    >> 3) - 1, 9:8, 3:2) |
			GETBITSTR((SiS_Pr->CHBlankStart >> 3) - 1, 9:8, 5:4) |
			GETBITSTR((SiS_Pr->CHSyncStart  >> 3) + 3, 9:8, 7:6) ;


   SiS_Pr->CCRT1CRTC[15] =							/* SRC */
			GETBITSTR((SiS_Pr->CHBlankEnd >> 3) - 1, 7:6, 1:0) |
			GETBITSTR((SiS_Pr->CHSyncEnd  >> 3) + 3, 5:5, 2:2) ;
पूर्ण

व्योम
SiS_CalcLCDACRT1Timing(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु modeflag, tempax, tempbx = 0, reमुख्यing = 0;
   अचिन्हित लघु VGAHDE = SiS_Pr->SiS_VGAHDE;
   पूर्णांक i, j;

   /* 1:1 data: use data set by setcrt1crtc() */
   अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) वापस;

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(modeflag & HalfDCLK) VGAHDE >>= 1;

   SiS_Pr->CHDisplay = VGAHDE;
   SiS_Pr->CHBlankStart = VGAHDE;

   SiS_Pr->CVDisplay = SiS_Pr->SiS_VGAVDE;
   SiS_Pr->CVBlankStart = SiS_Pr->SiS_VGAVDE;

   अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      tempbx = SiS_Pr->SiS_VGAHT;
      अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
         tempbx = SiS_Pr->PanelHT;
      पूर्ण
      अगर(modeflag & HalfDCLK) tempbx >>= 1;
      reमुख्यing = tempbx % 8;
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
      /* OK क्रम LCDA, LVDS */
      tempbx = SiS_Pr->PanelHT - SiS_Pr->PanelXRes;
      tempax = SiS_Pr->SiS_VGAHDE;  /* not /2 ! */
      अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
         tempax = SiS_Pr->PanelXRes;
      पूर्ण
      tempbx += tempax;
      अगर(modeflag & HalfDCLK) tempbx -= VGAHDE;
#पूर्ण_अगर
   पूर्ण
   SiS_Pr->CHTotal = SiS_Pr->CHBlankEnd = tempbx;

   अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      अगर(SiS_Pr->SiS_VGAHDE == SiS_Pr->PanelXRes) अणु
	 SiS_Pr->CHSyncStart = SiS_Pr->SiS_VGAHDE + ((SiS_Pr->PanelHRS + 1) & ~1);
	 SiS_Pr->CHSyncEnd = SiS_Pr->CHSyncStart + SiS_Pr->PanelHRE;
	 अगर(modeflag & HalfDCLK) अणु
	    SiS_Pr->CHSyncStart >>= 1;
	    SiS_Pr->CHSyncEnd >>= 1;
	 पूर्ण
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	 tempax = (SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE) >> 1;
	 tempbx = (SiS_Pr->PanelHRS + 1) & ~1;
	 अगर(modeflag & HalfDCLK) अणु
	    tempax >>= 1;
	    tempbx >>= 1;
	 पूर्ण
	 SiS_Pr->CHSyncStart = (VGAHDE + tempax + tempbx + 7) & ~7;
	 tempax = SiS_Pr->PanelHRE + 7;
	 अगर(modeflag & HalfDCLK) tempax >>= 1;
	 SiS_Pr->CHSyncEnd = (SiS_Pr->CHSyncStart + tempax) & ~7;
      पूर्ण अन्यथा अणु
	 SiS_Pr->CHSyncStart = SiS_Pr->SiS_VGAHDE;
	 अगर(modeflag & HalfDCLK) अणु
	    SiS_Pr->CHSyncStart >>= 1;
	    tempax = ((SiS_Pr->CHTotal - SiS_Pr->CHSyncStart) / 3) << 1;
	    SiS_Pr->CHSyncEnd = SiS_Pr->CHSyncStart + tempax;
	 पूर्ण अन्यथा अणु
	    SiS_Pr->CHSyncEnd = (SiS_Pr->CHSyncStart + (SiS_Pr->CHTotal / 10) + 7) & ~7;
	    SiS_Pr->CHSyncStart += 8;
	 पूर्ण
      पूर्ण
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
      tempax = VGAHDE;
      अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	 tempbx = SiS_Pr->PanelXRes;
	 अगर(modeflag & HalfDCLK) tempbx >>= 1;
	 tempax += ((tempbx - tempax) >> 1);
      पूर्ण
      tempax += SiS_Pr->PanelHRS;
      SiS_Pr->CHSyncStart = tempax;
      tempax += SiS_Pr->PanelHRE;
      SiS_Pr->CHSyncEnd = tempax;
#पूर्ण_अगर
   पूर्ण

   tempbx = SiS_Pr->PanelVT - SiS_Pr->PanelYRes;
   tempax = SiS_Pr->SiS_VGAVDE;
   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
      tempax = SiS_Pr->PanelYRes;
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      /* Stupid hack क्रम 640x400/320x200 */
      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	 अगर((tempax + tempbx) == 438) tempbx += 16;
      पूर्ण अन्यथा अगर((SiS_Pr->SiS_LCDResInfo == Panel_800x600) ||
		(SiS_Pr->SiS_LCDResInfo == Panel_1024x600)) अणु
	 tempax = 0;
	 tempbx = SiS_Pr->SiS_VGAVT;
      पूर्ण
#पूर्ण_अगर
   पूर्ण
   SiS_Pr->CVTotal = SiS_Pr->CVBlankEnd = tempbx + tempax;

   tempax = SiS_Pr->SiS_VGAVDE;
   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
      tempax += (SiS_Pr->PanelYRes - tempax) >> 1;
   पूर्ण
   tempax += SiS_Pr->PanelVRS;
   SiS_Pr->CVSyncStart = tempax;
   tempax += SiS_Pr->PanelVRE;
   SiS_Pr->CVSyncEnd = tempax;
   अगर(SiS_Pr->ChipType < SIS_315H) अणु
      SiS_Pr->CVSyncStart--;
      SiS_Pr->CVSyncEnd--;
   पूर्ण

   SiS_CalcCRRegisters(SiS_Pr, 8);
   SiS_Pr->CCRT1CRTC[15] &= ~0xF8;
   SiS_Pr->CCRT1CRTC[15] |= (reमुख्यing << 4);
   SiS_Pr->CCRT1CRTC[16] &= ~0xE0;

   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   क्रम(i = 0, j = 0; i <= 7; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   पूर्ण
   क्रम(j = 0x10; i <= 10; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   पूर्ण
   क्रम(j = 0x15; i <= 12; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3d4,j,SiS_Pr->CCRT1CRTC[i]);
   पूर्ण
   क्रम(j = 0x0A; i <= 15; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_P3c4,j,SiS_Pr->CCRT1CRTC[i]);
   पूर्ण

   tempax = SiS_Pr->CCRT1CRTC[16] & 0xE0;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0x1F,tempax);

   tempax = (SiS_Pr->CCRT1CRTC[16] & 0x01) << 5;
   अगर(modeflag & DoubleScanMode) tempax |= 0x80;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x09,0x5F,tempax);

पूर्ण

व्योम
SiS_Generic_ConvertCRData(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *crdata,
			पूर्णांक xres, पूर्णांक yres,
			काष्ठा fb_var_screeninfo *var, bool ग_लिखोres
)
अणु
   अचिन्हित लघु HRE, HBE, HRS, HDE;
   अचिन्हित लघु VRE, VBE, VRS, VDE;
   अचिन्हित अक्षर  sr_data, cr_data;
   पूर्णांक            B, C, D, E, F, temp;

   sr_data = crdata[14];

   /* Horizontal display enable end */
   HDE = crdata[1] | ((अचिन्हित लघु)(sr_data & 0x0C) << 6);
   E = HDE + 1;

   /* Horizontal retrace (=sync) start */
   HRS = crdata[4] | ((अचिन्हित लघु)(sr_data & 0xC0) << 2);
   F = HRS - E - 3;

   sr_data = crdata[15];
   cr_data = crdata[5];

   /* Horizontal blank end */
   HBE = (crdata[3] & 0x1f) |
         ((अचिन्हित लघु)(cr_data & 0x80) >> 2) |
         ((अचिन्हित लघु)(sr_data & 0x03) << 6);

   /* Horizontal retrace (=sync) end */
   HRE = (cr_data & 0x1f) | ((sr_data & 0x04) << 3);

   temp = HBE - ((E - 1) & 255);
   B = (temp > 0) ? temp : (temp + 256);

   temp = HRE - ((E + F + 3) & 63);
   C = (temp > 0) ? temp : (temp + 64);

   D = B - F - C;

   अगर(ग_लिखोres) var->xres = xres = E * 8;
   var->left_margin = D * 8;
   var->right_margin = F * 8;
   var->hsync_len = C * 8;

   /* Vertical */
   sr_data = crdata[13];
   cr_data = crdata[7];

   /* Vertical display enable end */
   VDE = crdata[10] |
	 ((अचिन्हित लघु)(cr_data & 0x02) << 7) |
	 ((अचिन्हित लघु)(cr_data & 0x40) << 3) |
	 ((अचिन्हित लघु)(sr_data & 0x02) << 9);
   E = VDE + 1;

   /* Vertical retrace (=sync) start */
   VRS = crdata[8] |
	 ((अचिन्हित लघु)(cr_data & 0x04) << 6) |
	 ((अचिन्हित लघु)(cr_data & 0x80) << 2) |
	 ((अचिन्हित लघु)(sr_data & 0x08) << 7);
   F = VRS + 1 - E;

   /* Vertical blank end */
   VBE = crdata[12] | ((अचिन्हित लघु)(sr_data & 0x10) << 4);
   temp = VBE - ((E - 1) & 511);
   B = (temp > 0) ? temp : (temp + 512);

   /* Vertical retrace (=sync) end */
   VRE = (crdata[9] & 0x0f) | ((sr_data & 0x20) >> 1);
   temp = VRE - ((E + F - 1) & 31);
   C = (temp > 0) ? temp : (temp + 32);

   D = B - F - C;

   अगर(ग_लिखोres) var->yres = yres = E;
   var->upper_margin = D;
   var->lower_margin = F;
   var->vsync_len = C;

   अगर((xres == 320) && ((yres == 200) || (yres == 240))) अणु
	/* Terrible hack, but correct CRTC data क्रम
	 * these modes only produces a black screen...
	 * (HRE is 0, leading पूर्णांकo a too large C and
	 * a negative D. The CRT controller करोes not
	 * seem to like correcting HRE to 50)
	 */
      var->left_margin = (400 - 376);
      var->right_margin = (328 - 320);
      var->hsync_len = (376 - 328);

   पूर्ण

पूर्ण




