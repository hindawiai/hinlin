<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
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
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#अगर_अघोषित _SISUSB_STRUCT_H_
#घोषणा _SISUSB_STRUCT_H_

काष्ठा SiS_St अणु
	अचिन्हित अक्षर St_ModeID;
	अचिन्हित लघु St_ModeFlag;
	अचिन्हित अक्षर St_StTableIndex;
	अचिन्हित अक्षर St_CRT2CRTC;
	अचिन्हित अक्षर St_ResInfo;
	अचिन्हित अक्षर VB_StTVFlickerIndex;
	अचिन्हित अक्षर VB_StTVEdgeIndex;
	अचिन्हित अक्षर VB_StTVYFilterIndex;
	अचिन्हित अक्षर St_PDC;
पूर्ण;

काष्ठा SiS_StandTable अणु
	अचिन्हित अक्षर CRT_COLS;
	अचिन्हित अक्षर ROWS;
	अचिन्हित अक्षर CHAR_HEIGHT;
	अचिन्हित लघु CRT_LEN;
	अचिन्हित अक्षर SR[4];
	अचिन्हित अक्षर MISC;
	अचिन्हित अक्षर CRTC[0x19];
	अचिन्हित अक्षर ATTR[0x14];
	अचिन्हित अक्षर GRC[9];
पूर्ण;

काष्ठा SiS_StResInfo_S अणु
	अचिन्हित लघु HTotal;
	अचिन्हित लघु VTotal;
पूर्ण;

काष्ठा SiS_Ext अणु
	अचिन्हित अक्षर Ext_ModeID;
	अचिन्हित लघु Ext_ModeFlag;
	अचिन्हित लघु Ext_VESAID;
	अचिन्हित अक्षर Ext_RESINFO;
	अचिन्हित अक्षर VB_ExtTVFlickerIndex;
	अचिन्हित अक्षर VB_ExtTVEdgeIndex;
	अचिन्हित अक्षर VB_ExtTVYFilterIndex;
	अचिन्हित अक्षर VB_ExtTVYFilterIndexROM661;
	अचिन्हित अक्षर REFindex;
	अक्षर ROMMODEIDX661;
पूर्ण;

काष्ठा SiS_Ext2 अणु
	अचिन्हित लघु Ext_InfoFlag;
	अचिन्हित अक्षर Ext_CRT1CRTC;
	अचिन्हित अक्षर Ext_CRTVCLK;
	अचिन्हित अक्षर Ext_CRT2CRTC;
	अचिन्हित अक्षर Ext_CRT2CRTC_NS;
	अचिन्हित अक्षर ModeID;
	अचिन्हित लघु XRes;
	अचिन्हित लघु YRes;
	अचिन्हित अक्षर Ext_PDC;
	अचिन्हित अक्षर Ext_FakeCRT2CRTC;
	अचिन्हित अक्षर Ext_FakeCRT2Clk;
पूर्ण;

काष्ठा SiS_CRT1Table अणु
	अचिन्हित अक्षर CR[17];
पूर्ण;

काष्ठा SiS_VCLKData अणु
	अचिन्हित अक्षर SR2B, SR2C;
	अचिन्हित लघु CLOCK;
पूर्ण;

काष्ठा SiS_ModeResInfo अणु
	अचिन्हित लघु HTotal;
	अचिन्हित लघु VTotal;
	अचिन्हित अक्षर XChar;
	अचिन्हित अक्षर YChar;
पूर्ण;

काष्ठा SiS_Private अणु
	व्योम *sisusb;

	अचिन्हित दीर्घ IOAddress;

	अचिन्हित दीर्घ SiS_P3c4;
	अचिन्हित दीर्घ SiS_P3d4;
	अचिन्हित दीर्घ SiS_P3c0;
	अचिन्हित दीर्घ SiS_P3ce;
	अचिन्हित दीर्घ SiS_P3c2;
	अचिन्हित दीर्घ SiS_P3ca;
	अचिन्हित दीर्घ SiS_P3c6;
	अचिन्हित दीर्घ SiS_P3c7;
	अचिन्हित दीर्घ SiS_P3c8;
	अचिन्हित दीर्घ SiS_P3c9;
	अचिन्हित दीर्घ SiS_P3cb;
	अचिन्हित दीर्घ SiS_P3cc;
	अचिन्हित दीर्घ SiS_P3cd;
	अचिन्हित दीर्घ SiS_P3da;
	अचिन्हित दीर्घ SiS_Part1Port;

	अचिन्हित अक्षर SiS_MyCR63;
	अचिन्हित लघु SiS_CRT1Mode;
	अचिन्हित लघु SiS_ModeType;
	अचिन्हित लघु SiS_SetFlag;

	स्थिर काष्ठा SiS_StandTable *SiS_StandTable;
	स्थिर काष्ठा SiS_St *SiS_SModeIDTable;
	स्थिर काष्ठा SiS_Ext *SiS_EModeIDTable;
	स्थिर काष्ठा SiS_Ext2 *SiS_RefIndex;
	स्थिर काष्ठा SiS_CRT1Table *SiS_CRT1Table;
	स्थिर काष्ठा SiS_VCLKData *SiS_VCLKData;
	स्थिर काष्ठा SiS_ModeResInfo *SiS_ModeResInfo;
पूर्ण;

#पूर्ण_अगर
