<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * sisusb - usb kernel driver क्रम SiS315(E) based USB2VGA करोngles
 *
 * Display mode initializing code
 *
 * Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, this code is licensed under the
 * terms of the GPL v2.
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
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/poll.h>
#समावेश <linux/spinlock.h>

#समावेश "sisusb.h"
#समावेश "sisusb_init.h"
#समावेश "sisusb_tables.h"

/*********************************************/
/*         POINTER INITIALIZATION            */
/*********************************************/

अटल व्योम SiSUSB_InitPtr(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_Pr->SiS_ModeResInfo = SiSUSB_ModeResInfo;
	SiS_Pr->SiS_StandTable = SiSUSB_StandTable;

	SiS_Pr->SiS_SModeIDTable = SiSUSB_SModeIDTable;
	SiS_Pr->SiS_EModeIDTable = SiSUSB_EModeIDTable;
	SiS_Pr->SiS_RefIndex = SiSUSB_RefIndex;
	SiS_Pr->SiS_CRT1Table = SiSUSB_CRT1Table;

	SiS_Pr->SiS_VCLKData = SiSUSB_VCLKData;
पूर्ण

/*********************************************/
/*          HELPER: SetReg, GetReg           */
/*********************************************/

अटल व्योम
SiS_SetReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port,
	   अचिन्हित लघु index, अचिन्हित लघु data)
अणु
	sisusb_setidxreg(SiS_Pr->sisusb, port, index, data);
पूर्ण

अटल व्योम
SiS_SetRegByte(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port,
	       अचिन्हित लघु data)
अणु
	sisusb_setreg(SiS_Pr->sisusb, port, data);
पूर्ण

अटल अचिन्हित अक्षर
SiS_GetReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port, अचिन्हित लघु index)
अणु
	u8 data;

	sisusb_getidxreg(SiS_Pr->sisusb, port, index, &data);

	वापस data;
पूर्ण

अटल अचिन्हित अक्षर
SiS_GetRegByte(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port)
अणु
	u8 data;

	sisusb_getreg(SiS_Pr->sisusb, port, &data);

	वापस data;
पूर्ण

अटल व्योम
SiS_SetRegANDOR(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port,
		अचिन्हित लघु index, अचिन्हित लघु DataAND,
		अचिन्हित लघु DataOR)
अणु
	sisusb_setidxreganकरोr(SiS_Pr->sisusb, port, index, DataAND, DataOR);
पूर्ण

अटल व्योम
SiS_SetRegAND(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port,
	      अचिन्हित लघु index, अचिन्हित लघु DataAND)
अणु
	sisusb_setidxregand(SiS_Pr->sisusb, port, index, DataAND);
पूर्ण

अटल व्योम
SiS_SetRegOR(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ port,
	     अचिन्हित लघु index, अचिन्हित लघु DataOR)
अणु
	sisusb_setidxregor(SiS_Pr->sisusb, port, index, DataOR);
पूर्ण

/*********************************************/
/*      HELPER: DisplayOn, DisplayOff        */
/*********************************************/

अटल व्योम SiS_DisplayOn(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x01, 0xDF);
पूर्ण

/*********************************************/
/*        HELPER: Init Port Addresses        */
/*********************************************/

अटल व्योम SiSUSBRegInit(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ BaseAddr)
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
पूर्ण

/*********************************************/
/*             HELPER: GetSysFlags           */
/*********************************************/

अटल व्योम SiS_GetSysFlags(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_Pr->SiS_MyCR63 = 0x63;
पूर्ण

/*********************************************/
/*         HELPER: Init PCI & Engines        */
/*********************************************/

अटल व्योम SiSInitPCIetc(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x20, 0xa1);
	/*  - Enable 2D (0x40)
	 *  - Enable 3D (0x02)
	 *  - Enable 3D vertex command fetch (0x10)
	 *  - Enable 3D command parser (0x08)
	 *  - Enable 3D G/L transक्रमmation engine (0x80)
	 */
	SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1E, 0xDA);
पूर्ण

/*********************************************/
/*        HELPER: SET SEGMENT REGISTERS      */
/*********************************************/

अटल व्योम SiS_SetSegRegLower(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
	अचिन्हित लघु temp;

	value &= 0x00ff;
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb) & 0xf0;
	temp |= (value >> 4);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb, temp);
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd) & 0xf0;
	temp |= (value & 0x0f);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd, temp);
पूर्ण

अटल व्योम SiS_SetSegRegUpper(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
	अचिन्हित लघु temp;

	value &= 0x00ff;
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb) & 0x0f;
	temp |= (value & 0xf0);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb, temp);
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd) & 0x0f;
	temp |= (value << 4);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd, temp);
पूर्ण

अटल व्योम SiS_SetSegmentReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
	SiS_SetSegRegLower(SiS_Pr, value);
	SiS_SetSegRegUpper(SiS_Pr, value);
पूर्ण

अटल व्योम SiS_ResetSegmentReg(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_SetSegmentReg(SiS_Pr, 0);
पूर्ण

अटल व्योम
SiS_SetSegmentRegOver(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु value)
अणु
	अचिन्हित लघु temp = value >> 8;

	temp &= 0x07;
	temp |= (temp << 4);
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1d, temp);
	SiS_SetSegmentReg(SiS_Pr, value);
पूर्ण

अटल व्योम SiS_ResetSegmentRegOver(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_SetSegmentRegOver(SiS_Pr, 0);
पूर्ण

अटल व्योम SiS_ResetSegmentRegisters(काष्ठा SiS_Private *SiS_Pr)
अणु
	SiS_ResetSegmentReg(SiS_Pr);
	SiS_ResetSegmentRegOver(SiS_Pr);
पूर्ण

/*********************************************/
/*           HELPER: SearchModeID            */
/*********************************************/

अटल पूर्णांक
SiS_SearchModeID(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *ModeNo,
		 अचिन्हित लघु *ModeIdIndex)
अणु
	अगर ((*ModeNo) <= 0x13) अणु

		अगर ((*ModeNo) != 0x03)
			वापस 0;

		(*ModeIdIndex) = 0;

	पूर्ण अन्यथा अणु

		क्रम (*ModeIdIndex = 0;; (*ModeIdIndex)++) अणु

			अगर (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    (*ModeNo))
				अवरोध;

			अगर (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    0xFF)
				वापस 0;
		पूर्ण

	पूर्ण

	वापस 1;
पूर्ण

/*********************************************/
/*            HELPER: ENABLE CRT1            */
/*********************************************/

अटल व्योम SiS_HandleCRT1(काष्ठा SiS_Private *SiS_Pr)
अणु
	/* Enable CRT1 gating */
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, SiS_Pr->SiS_MyCR63, 0xbf);
पूर्ण

/*********************************************/
/*           HELPER: GetColorDepth           */
/*********************************************/

अटल अचिन्हित लघु
SiS_GetColorDepth(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		  अचिन्हित लघु ModeIdIndex)
अणु
	अटल स्थिर अचिन्हित लघु ColorDepth[6] = अणु 1, 2, 4, 4, 6, 8 पूर्ण;
	अचिन्हित लघु modeflag;
	लघु index;

	अगर (ModeNo <= 0x13) अणु
		modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
	पूर्ण अन्यथा अणु
		modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	पूर्ण

	index = (modeflag & ModeTypeMask) - ModeEGA;
	अगर (index < 0)
		index = 0;
	वापस ColorDepth[index];
पूर्ण

/*********************************************/
/*             HELPER: GetOffset             */
/*********************************************/

अटल अचिन्हित लघु
SiS_GetOffset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
	      अचिन्हित लघु ModeIdIndex, अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु xres, temp, colordepth, infoflag;

	infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	xres = SiS_Pr->SiS_RefIndex[rrti].XRes;

	colordepth = SiS_GetColorDepth(SiS_Pr, ModeNo, ModeIdIndex);

	temp = xres / 16;

	अगर (infoflag & InterlaceMode)
		temp <<= 1;

	temp *= colordepth;

	अगर (xres % 16)
		temp += (colordepth >> 1);

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

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x00, 0x03);

	SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[0] | 0x20;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x01, SRdata);

	क्रम (i = 2; i <= 4; i++) अणु
		SRdata = SiS_Pr->SiS_StandTable[StandTableIndex].SR[i - 1];
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, i, SRdata);
	पूर्ण
पूर्ण

/*********************************************/
/*                  MISC                     */
/*********************************************/

अटल व्योम
SiS_SetMiscRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
	अचिन्हित अक्षर Miscdata = SiS_Pr->SiS_StandTable[StandTableIndex].MISC;

	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c2, Miscdata);
पूर्ण

/*********************************************/
/*                  CRTC                     */
/*********************************************/

अटल व्योम
SiS_SetCRTCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
	अचिन्हित अक्षर CRTCdata;
	अचिन्हित लघु i;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, 0x11, 0x7f);

	क्रम (i = 0; i <= 0x18; i++) अणु
		CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, i, CRTCdata);
	पूर्ण
पूर्ण

/*********************************************/
/*                   ATT                     */
/*********************************************/

अटल व्योम
SiS_SetATTRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
	अचिन्हित अक्षर ARdata;
	अचिन्हित लघु i;

	क्रम (i = 0; i <= 0x13; i++) अणु
		ARdata = SiS_Pr->SiS_StandTable[StandTableIndex].ATTR[i];
		SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
		SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, i);
		SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, ARdata);
	पूर्ण
	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x14);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x00);

	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x20);
	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
पूर्ण

/*********************************************/
/*                   GRC                     */
/*********************************************/

अटल व्योम
SiS_SetGRCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु StandTableIndex)
अणु
	अचिन्हित अक्षर GRdata;
	अचिन्हित लघु i;

	क्रम (i = 0; i <= 0x08; i++) अणु
		GRdata = SiS_Pr->SiS_StandTable[StandTableIndex].GRC[i];
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3ce, i, GRdata);
	पूर्ण

	अगर (SiS_Pr->SiS_ModeType > ModeVGA) अणु
		/* 256 color disable */
		SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3ce, 0x05, 0xBF);
	पूर्ण
पूर्ण

/*********************************************/
/*          CLEAR EXTENDED REGISTERS         */
/*********************************************/

अटल व्योम SiS_ClearExt1Regs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
	पूर्णांक i;

	क्रम (i = 0x0A; i <= 0x0E; i++) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, i, 0x00);
	पूर्ण

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x37, 0xFE);
पूर्ण

/*********************************************/
/*              Get rate index               */
/*********************************************/

अटल अचिन्हित लघु
SiS_GetRatePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
	       अचिन्हित लघु ModeIdIndex)
अणु
	अचिन्हित लघु rrti, i, index, temp;

	अगर (ModeNo <= 0x13)
		वापस 0xFFFF;

	index = SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x33) & 0x0F;
	अगर (index > 0)
		index--;

	rrti = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
	ModeNo = SiS_Pr->SiS_RefIndex[rrti].ModeID;

	i = 0;
	करो अणु
		अगर (SiS_Pr->SiS_RefIndex[rrti + i].ModeID != ModeNo)
			अवरोध;

		temp =
		    SiS_Pr->SiS_RefIndex[rrti + i].Ext_InfoFlag & ModeTypeMask;
		अगर (temp < SiS_Pr->SiS_ModeType)
			अवरोध;

		i++;
		index--;
	पूर्ण जबतक (index != 0xFFFF);

	i--;

	वापस (rrti + i);
पूर्ण

/*********************************************/
/*                  SYNC                     */
/*********************************************/

अटल व्योम SiS_SetCRT1Sync(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु sync = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag >> 8;
	sync &= 0xC0;
	sync |= 0x2f;
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c2, sync);
पूर्ण

/*********************************************/
/*                  CRTC/2                   */
/*********************************************/

अटल व्योम
SiS_SetCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु rrti)
अणु
	अचिन्हित अक्षर index;
	अचिन्हित लघु temp, i, j, modeflag;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, 0x11, 0x7f);

	modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRT1CRTC;

	क्रम (i = 0, j = 0; i <= 7; i++, j++) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	पूर्ण
	क्रम (j = 0x10; i <= 10; i++, j++) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	पूर्ण
	क्रम (j = 0x15; i <= 12; i++, j++) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	पूर्ण
	क्रम (j = 0x0A; i <= 15; i++, j++) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	पूर्ण

	temp = SiS_Pr->SiS_CRT1Table[index].CR[16] & 0xE0;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0E, temp);

	temp = ((SiS_Pr->SiS_CRT1Table[index].CR[16]) & 0x01) << 5;
	अगर (modeflag & DoubleScanMode)
		temp |= 0x80;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3d4, 0x09, 0x5F, temp);

	अगर (SiS_Pr->SiS_ModeType > ModeVGA)
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x14, 0x4F);
पूर्ण

/*********************************************/
/*               OFFSET & PITCH              */
/*********************************************/
/*  (partly overruled by SetPitch() in XF86) */
/*********************************************/

अटल व्योम
SiS_SetCRT1Offset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		  अचिन्हित लघु ModeIdIndex, अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु du = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
	अचिन्हित लघु infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	अचिन्हित लघु temp;

	temp = (du >> 8) & 0x0f;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0E, 0xF0, temp);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x13, (du & 0xFF));

	अगर (infoflag & InterlaceMode)
		du >>= 1;

	du <<= 5;
	temp = (du >> 8) & 0xff;
	अगर (du & 0xff)
		temp++;
	temp++;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x10, temp);
पूर्ण

/*********************************************/
/*                  VCLK                     */
/*********************************************/

अटल व्योम
SiS_SetCRT1VCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRTVCLK;
	अचिन्हित लघु clka = SiS_Pr->SiS_VCLKData[index].SR2B;
	अचिन्हित लघु clkb = SiS_Pr->SiS_VCLKData[index].SR2C;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x31, 0xCF);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2B, clka);
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2C, clkb);
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2D, 0x01);
पूर्ण

/*********************************************/
/*                  FIFO                     */
/*********************************************/

अटल व्योम
SiS_SetCRT1FIFO_310(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		    अचिन्हित लघु mi)
अणु
	अचिन्हित लघु modeflag = SiS_Pr->SiS_EModeIDTable[mi].Ext_ModeFlag;

	/* disable स्वतः-threshold */
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x3D, 0xFE);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x08, 0xAE);
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x09, 0xF0);

	अगर (ModeNo <= 0x13)
		वापस;

	अगर ((!(modeflag & DoubleScanMode)) || (!(modeflag & HalfDCLK))) अणु
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x08, 0x34);
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x3D, 0x01);
	पूर्ण
पूर्ण

/*********************************************/
/*              MODE REGISTERS               */
/*********************************************/

अटल व्योम
SiS_SetVCLKState(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		 अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु data = 0, VCLK = 0, index = 0;

	अगर (ModeNo > 0x13) अणु
		index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRTVCLK;
		VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
	पूर्ण

	अगर (VCLK >= 166)
		data |= 0x0c;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x32, 0xf3, data);

	अगर (VCLK >= 166)
		SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1f, 0xe7);

	/* DAC speed */
	data = 0x03;
	अगर (VCLK >= 260)
		data = 0x00;
	अन्यथा अगर (VCLK >= 160)
		data = 0x01;
	अन्यथा अगर (VCLK >= 135)
		data = 0x02;

	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x07, 0xF8, data);
पूर्ण

अटल व्योम
SiS_SetCRT1ModeRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		    अचिन्हित लघु ModeIdIndex, अचिन्हित लघु rrti)
अणु
	अचिन्हित लघु data, infoflag = 0, modeflag;

	अगर (ModeNo <= 0x13)
		modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
	अन्यथा अणु
		modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
		infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	पूर्ण

	/* Disable DPMS */
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1F, 0x3F);

	data = 0;
	अगर (ModeNo > 0x13) अणु
		अगर (SiS_Pr->SiS_ModeType > ModeEGA) अणु
			data |= 0x02;
			data |= ((SiS_Pr->SiS_ModeType - ModeVGA) << 2);
		पूर्ण
		अगर (infoflag & InterlaceMode)
			data |= 0x20;
	पूर्ण
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x06, 0xC0, data);

	data = 0;
	अगर (infoflag & InterlaceMode) अणु
		/* data = (Hsync / 8) - ((Htotal / 8) / 2) + 3 */
		अचिन्हित लघु hrs =
		    (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x04) |
		     ((SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0b) & 0xc0) << 2))
		    - 3;
		अचिन्हित लघु hto =
		    (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x00) |
		     ((SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0b) & 0x03) << 8))
		    + 5;
		data = hrs - (hto >> 1) + 3;
	पूर्ण
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x19, (data & 0xFF));
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3d4, 0x1a, 0xFC, (data >> 8));

	अगर (modeflag & HalfDCLK)
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x01, 0x08);

	data = 0;
	अगर (modeflag & LineCompareOff)
		data = 0x08;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0F, 0xB7, data);

	अगर ((SiS_Pr->SiS_ModeType == ModeEGA) && (ModeNo > 0x13))
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0F, 0x40);

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x31, 0xfb);

	data = 0x60;
	अगर (SiS_Pr->SiS_ModeType != ModeText) अणु
		data ^= 0x60;
		अगर (SiS_Pr->SiS_ModeType != ModeEGA)
			data ^= 0xA0;
	पूर्ण
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x21, 0x1F, data);

	SiS_SetVCLKState(SiS_Pr, ModeNo, rrti);

	अगर (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x31) & 0x40)
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x52, 0x2c);
	अन्यथा
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x52, 0x6c);
पूर्ण

/*********************************************/
/*                 LOAD DAC                  */
/*********************************************/

अटल व्योम
SiS_WriteDAC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित दीर्घ DACData,
	     अचिन्हित लघु shअगरtflag, अचिन्हित लघु dl, अचिन्हित लघु ah,
	     अचिन्हित लघु al, अचिन्हित लघु dh)
अणु
	अचिन्हित लघु d1, d2, d3;

	चयन (dl) अणु
	हाल 0:
		d1 = dh;
		d2 = ah;
		d3 = al;
		अवरोध;
	हाल 1:
		d1 = ah;
		d2 = al;
		d3 = dh;
		अवरोध;
	शेष:
		d1 = al;
		d2 = dh;
		d3 = ah;
	पूर्ण
	SiS_SetRegByte(SiS_Pr, DACData, (d1 << shअगरtflag));
	SiS_SetRegByte(SiS_Pr, DACData, (d2 << shअगरtflag));
	SiS_SetRegByte(SiS_Pr, DACData, (d3 << shअगरtflag));
पूर्ण

अटल व्योम
SiS_LoadDAC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
	    अचिन्हित लघु mi)
अणु
	अचिन्हित लघु data, data2, समय, i, j, k, m, n, o;
	अचिन्हित लघु si, di, bx, sf;
	अचिन्हित दीर्घ DACAddr, DACData;
	स्थिर अचिन्हित अक्षर *table = शून्य;

	अगर (ModeNo < 0x13)
		data = SiS_Pr->SiS_SModeIDTable[mi].St_ModeFlag;
	अन्यथा
		data = SiS_Pr->SiS_EModeIDTable[mi].Ext_ModeFlag;

	data &= DACInfoFlag;

	j = समय = 64;
	अगर (data == 0x00)
		table = SiS_MDA_DAC;
	अन्यथा अगर (data == 0x08)
		table = SiS_CGA_DAC;
	अन्यथा अगर (data == 0x10)
		table = SiS_EGA_DAC;
	अन्यथा अणु
		j = 16;
		समय = 256;
		table = SiS_VGA_DAC;
	पूर्ण

	DACAddr = SiS_Pr->SiS_P3c8;
	DACData = SiS_Pr->SiS_P3c9;
	sf = 0;
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c6, 0xFF);

	SiS_SetRegByte(SiS_Pr, DACAddr, 0x00);

	क्रम (i = 0; i < j; i++) अणु
		data = table[i];
		क्रम (k = 0; k < 3; k++) अणु
			data2 = 0;
			अगर (data & 0x01)
				data2 += 0x2A;
			अगर (data & 0x02)
				data2 += 0x15;
			SiS_SetRegByte(SiS_Pr, DACData, (data2 << sf));
			data >>= 2;
		पूर्ण
	पूर्ण

	अगर (समय == 256) अणु
		क्रम (i = 16; i < 32; i++) अणु
			data = table[i] << sf;
			क्रम (k = 0; k < 3; k++)
				SiS_SetRegByte(SiS_Pr, DACData, data);
		पूर्ण
		si = 32;
		क्रम (m = 0; m < 9; m++) अणु
			di = si;
			bx = si + 4;
			क्रम (n = 0; n < 3; n++) अणु
				क्रम (o = 0; o < 5; o++) अणु
					SiS_WriteDAC(SiS_Pr, DACData, sf, n,
						     table[di], table[bx],
						     table[si]);
					si++;
				पूर्ण
				si -= 2;
				क्रम (o = 0; o < 3; o++) अणु
					SiS_WriteDAC(SiS_Pr, DACData, sf, n,
						     table[di], table[si],
						     table[bx]);
					si--;
				पूर्ण
			पूर्ण
			si += 5;
		पूर्ण
	पूर्ण
पूर्ण

/*********************************************/
/*         SET CRT1 REGISTER GROUP           */
/*********************************************/

अटल व्योम
SiS_SetCRT1Group(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		 अचिन्हित लघु ModeIdIndex)
अणु
	अचिन्हित लघु StandTableIndex, rrti;

	SiS_Pr->SiS_CRT1Mode = ModeNo;

	अगर (ModeNo <= 0x13)
		StandTableIndex = 0;
	अन्यथा
		StandTableIndex = 1;

	SiS_ResetSegmentRegisters(SiS_Pr);
	SiS_SetSeqRegs(SiS_Pr, StandTableIndex);
	SiS_SetMiscRegs(SiS_Pr, StandTableIndex);
	SiS_SetCRTCRegs(SiS_Pr, StandTableIndex);
	SiS_SetATTRegs(SiS_Pr, StandTableIndex);
	SiS_SetGRCRegs(SiS_Pr, StandTableIndex);
	SiS_ClearExt1Regs(SiS_Pr, ModeNo);

	rrti = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

	अगर (rrti != 0xFFFF) अणु
		SiS_SetCRT1Sync(SiS_Pr, rrti);
		SiS_SetCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1Offset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1VCLK(SiS_Pr, ModeNo, rrti);
	पूर्ण

	SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_SetCRT1ModeRegs(SiS_Pr, ModeNo, ModeIdIndex, rrti);

	SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_DisplayOn(SiS_Pr);
पूर्ण

/*********************************************/
/*                 SiSSetMode()              */
/*********************************************/

पूर्णांक SiSUSBSetMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
	अचिन्हित लघु ModeIdIndex;
	अचिन्हित दीर्घ BaseAddr = SiS_Pr->IOAddress;

	SiSUSB_InitPtr(SiS_Pr);
	SiSUSBRegInit(SiS_Pr, BaseAddr);
	SiS_GetSysFlags(SiS_Pr);

	अगर (!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex)))
		वापस 0;

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x05, 0x86);

	SiSInitPCIetc(SiS_Pr);

	ModeNo &= 0x7f;

	SiS_Pr->SiS_ModeType =
	    SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag & ModeTypeMask;

	SiS_Pr->SiS_SetFlag = LowModeTests;

	/* Set mode on CRT1 */
	SiS_SetCRT1Group(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_HandleCRT1(SiS_Pr);

	SiS_DisplayOn(SiS_Pr);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c6, 0xFF);

	/* Store mode number */
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x34, ModeNo);

	वापस 1;
पूर्ण

पूर्णांक SiSUSBSetVESAMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु VModeNo)
अणु
	अचिन्हित लघु ModeNo = 0;
	पूर्णांक i;

	SiSUSB_InitPtr(SiS_Pr);

	अगर (VModeNo == 0x03) अणु

		ModeNo = 0x03;

	पूर्ण अन्यथा अणु

		i = 0;
		करो अणु

			अगर (SiS_Pr->SiS_EModeIDTable[i].Ext_VESAID == VModeNo) अणु
				ModeNo = SiS_Pr->SiS_EModeIDTable[i].Ext_ModeID;
				अवरोध;
			पूर्ण

		पूर्ण जबतक (SiS_Pr->SiS_EModeIDTable[i++].Ext_ModeID != 0xff);

	पूर्ण

	अगर (!ModeNo)
		वापस 0;

	वापस SiSUSBSetMode(SiS_Pr, ModeNo);
पूर्ण
