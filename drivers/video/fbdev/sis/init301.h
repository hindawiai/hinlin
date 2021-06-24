<शैली गुरु>
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * Data and prototypes क्रम init301.c
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

#अगर_अघोषित  _INIT301_H_
#घोषणा  _INIT301_H_

#समावेश "initdef.h"

#समावेश "vgatypes.h"
#समावेश "vstruct.h"
#अगर_घोषित SIS_CP
#अघोषित SIS_CP
#पूर्ण_अगर
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/fb.h>
#समावेश "sis.h"
#समावेश <video/sisfb.h>

व्योम		SiS_UnLockCRT2(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiS_EnableCRT2(काष्ठा SiS_Private *SiS_Pr);
अचिन्हित लघु	SiS_GetRatePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex);
व्योम		SiS_WaitRetrace1(काष्ठा SiS_Private *SiS_Pr);
bool		SiS_IsDualEdge(काष्ठा SiS_Private *SiS_Pr);
bool		SiS_IsVAMode(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiS_GetVBInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
			अचिन्हित लघु ModeIdIndex, पूर्णांक checkcrt2mode);
व्योम		SiS_SetYPbPr(काष्ठा SiS_Private *SiS_Pr);
व्योम    	SiS_SetTVMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
			अचिन्हित लघु ModeIdIndex);
व्योम		SiS_GetLCDResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex);
अचिन्हित लघु	SiS_GetVCLK2Ptr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
			अचिन्हित लघु RefreshRateTableIndex);
अचिन्हित लघु	SiS_GetResInfo(काष्ठा SiS_Private *SiS_Pr,अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex);
व्योम		SiS_DisableBridge(काष्ठा SiS_Private *SiS_Pr);
bool		SiS_SetCRT2Group(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo);
व्योम		SiS_SiS30xBLOn(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiS_SiS30xBLOff(काष्ठा SiS_Private *SiS_Pr);

व्योम		SiS_SetCH700x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val);
अचिन्हित लघु	SiS_GetCH700x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempax);
व्योम		SiS_SetCH701x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val);
अचिन्हित लघु	SiS_GetCH701x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempax);
व्योम		SiS_SetCH70xxANDOR(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg,
			अचिन्हित अक्षर orval,अचिन्हित लघु andval);
#अगर_घोषित CONFIG_FB_SIS_315
व्योम		SiS_Chrontel701xBLOn(काष्ठा SiS_Private *SiS_Pr);
व्योम		SiS_Chrontel701xBLOff(काष्ठा SiS_Private *SiS_Pr);
#पूर्ण_अगर /* 315 */

#अगर_घोषित CONFIG_FB_SIS_300
व्योम		SiS_SetChrontelGPIO(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु myvbinfo);
#पूर्ण_अगर

व्योम		SiS_DDC2Delay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक delayसमय);
अचिन्हित लघु	SiS_ReadDDC1Bit(काष्ठा SiS_Private *SiS_Pr);
अचिन्हित लघु	SiS_HandleDDC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक VBFlags, पूर्णांक VGAEngine,
			अचिन्हित लघु adaptnum, अचिन्हित लघु DDCdatatype,
			अचिन्हित अक्षर *buffer, अचिन्हित पूर्णांक VBFlags2);

बाह्य व्योम		SiS_DisplayOff(काष्ठा SiS_Private *SiS_Pr);
बाह्य व्योम		SiS_DisplayOn(काष्ठा SiS_Private *SiS_Pr);
बाह्य bool		SiS_SearchModeID(काष्ठा SiS_Private *, अचिन्हित लघु *, अचिन्हित लघु *);
बाह्य अचिन्हित लघु	SiS_GetModeFlag(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य अचिन्हित लघु	SiS_GetModePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex);
बाह्य अचिन्हित लघु	SiS_GetColorDepth(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex);
बाह्य अचिन्हित लघु	SiS_GetOffset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
				अचिन्हित लघु RefreshRateTableIndex);
बाह्य व्योम		SiS_LoadDAC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य व्योम		SiS_CalcLCDACRT1Timing(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
				अचिन्हित लघु ModeIdIndex);
बाह्य व्योम		SiS_CalcCRRegisters(काष्ठा SiS_Private *SiS_Pr, पूर्णांक depth);
बाह्य अचिन्हित लघु	SiS_GetRefCRTVCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide);
बाह्य अचिन्हित लघु	SiS_GetRefCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु Index, पूर्णांक UseWide);
#अगर_घोषित CONFIG_FB_SIS_300
बाह्य व्योम		SiS_GetFIFOThresholdIndex300(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *tempbx,
				अचिन्हित लघु *tempcl);
बाह्य अचिन्हित लघु	SiS_GetFIFOThresholdB300(अचिन्हित लघु tempbx, अचिन्हित लघु tempcl);
बाह्य अचिन्हित लघु	SiS_GetLatencyFactor630(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु index);
बाह्य अचिन्हित पूर्णांक	sisfb_पढ़ो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
बाह्य अचिन्हित पूर्णांक	sisfb_पढ़ो_lpc_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg);
#पूर्ण_अगर

#पूर्ण_अगर
