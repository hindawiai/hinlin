<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * Data and prototypes क्रम init.c
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

#अगर_अघोषित _SISUSB_INIT_H_
#घोषणा _SISUSB_INIT_H_

/* SiS_ModeType */
#घोषणा ModeText		0x00
#घोषणा ModeCGA			0x01
#घोषणा ModeEGA			0x02
#घोषणा ModeVGA			0x03
#घोषणा Mode15Bpp		0x04
#घोषणा Mode16Bpp		0x05
#घोषणा Mode24Bpp		0x06
#घोषणा Mode32Bpp		0x07

#घोषणा ModeTypeMask		0x07
#घोषणा IsTextMode		0x07

#घोषणा DACInfoFlag		0x0018
#घोषणा MemoryInfoFlag		0x01E0
#घोषणा MemorySizeShअगरt		5

/* modeflag */
#घोषणा Charx8Dot		0x0200
#घोषणा LineCompareOff		0x0400
#घोषणा CRT2Mode		0x0800
#घोषणा HalfDCLK		0x1000
#घोषणा NoSupportSimuTV		0x2000
#घोषणा NoSupportLCDScale	0x4000	/* SiS bridge: No scaling possible (no matter what panel) */
#घोषणा DoubleScanMode		0x8000

/* Infoflag */
#घोषणा SupportTV		0x0008
#घोषणा SupportTV1024		0x0800
#घोषणा SupportCHTV		0x0800
#घोषणा Support64048060Hz	0x0800	/* Special क्रम 640x480 LCD */
#घोषणा SupportHiVision		0x0010
#घोषणा SupportYPbPr750p	0x1000
#घोषणा SupportLCD		0x0020
#घोषणा SupportRAMDAC2		0x0040	/* All           (<= 100Mhz) */
#घोषणा SupportRAMDAC2_135	0x0100	/* All except DH (<= 135Mhz) */
#घोषणा SupportRAMDAC2_162	0x0200	/* B, C          (<= 162Mhz) */
#घोषणा SupportRAMDAC2_202	0x0400	/* C             (<= 202Mhz) */
#घोषणा InterlaceMode		0x0080
#घोषणा SyncPP			0x0000
#घोषणा SyncPN			0x4000
#घोषणा SyncNP			0x8000
#घोषणा SyncNN			0xc000

/* SetFlag */
#घोषणा ProgrammingCRT2		0x0001
#घोषणा LowModeTests		0x0002
#घोषणा LCDVESATiming		0x0008
#घोषणा EnableLVDSDDA		0x0010
#घोषणा SetDispDevSwitchFlag	0x0020
#घोषणा CheckWinDos		0x0040
#घोषणा SetDOSMode		0x0080

/* Index in ModeResInfo table */
#घोषणा SIS_RI_320x200		0
#घोषणा SIS_RI_320x240		1
#घोषणा SIS_RI_320x400		2
#घोषणा SIS_RI_400x300		3
#घोषणा SIS_RI_512x384		4
#घोषणा SIS_RI_640x400		5
#घोषणा SIS_RI_640x480		6
#घोषणा SIS_RI_800x600		7
#घोषणा SIS_RI_1024x768		8
#घोषणा SIS_RI_1280x1024	9
#घोषणा SIS_RI_1600x1200	10
#घोषणा SIS_RI_1920x1440	11
#घोषणा SIS_RI_2048x1536	12
#घोषणा SIS_RI_720x480		13
#घोषणा SIS_RI_720x576		14
#घोषणा SIS_RI_1280x960		15
#घोषणा SIS_RI_800x480		16
#घोषणा SIS_RI_1024x576		17
#घोषणा SIS_RI_1280x720		18
#घोषणा SIS_RI_856x480		19
#घोषणा SIS_RI_1280x768		20
#घोषणा SIS_RI_1400x1050	21
#घोषणा SIS_RI_1152x864		22	/* Up to here SiS conक्रमming */
#घोषणा SIS_RI_848x480		23
#घोषणा SIS_RI_1360x768		24
#घोषणा SIS_RI_1024x600		25
#घोषणा SIS_RI_1152x768		26
#घोषणा SIS_RI_768x576		27
#घोषणा SIS_RI_1360x1024	28
#घोषणा SIS_RI_1680x1050	29
#घोषणा SIS_RI_1280x800		30
#घोषणा SIS_RI_1920x1080	31
#घोषणा SIS_RI_960x540		32
#घोषणा SIS_RI_960x600		33

#घोषणा SIS_VIDEO_CAPTURE	0x00 - 0x30
#घोषणा SIS_VIDEO_PLAYBACK	0x02 - 0x30
#घोषणा SIS_CRT2_PORT_04	0x04 - 0x30

पूर्णांक SiSUSBSetMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo);
पूर्णांक SiSUSBSetVESAMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु VModeNo);

बाह्य पूर्णांक sisusb_setreg(काष्ठा sisusb_usb_data *sisusb, u32 port, u8 data);
बाह्य पूर्णांक sisusb_getreg(काष्ठा sisusb_usb_data *sisusb, u32 port, u8 * data);
बाह्य पूर्णांक sisusb_setidxreg(काष्ठा sisusb_usb_data *sisusb, u32 port,
			    u8 index, u8 data);
बाह्य पूर्णांक sisusb_getidxreg(काष्ठा sisusb_usb_data *sisusb, u32 port,
			    u8 index, u8 * data);
बाह्य पूर्णांक sisusb_setidxreganकरोr(काष्ठा sisusb_usb_data *sisusb, u32 port,
				 u8 idx, u8 myand, u8 myor);
बाह्य पूर्णांक sisusb_setidxregor(काष्ठा sisusb_usb_data *sisusb, u32 port,
			      u8 index, u8 myor);
बाह्य पूर्णांक sisusb_setidxregand(काष्ठा sisusb_usb_data *sisusb, u32 port,
			       u8 idx, u8 myand);

व्योम sisusb_delete(काष्ठा kref *kref);
पूर्णांक sisusb_ग_लिखोb(काष्ठा sisusb_usb_data *sisusb, u32 adr, u8 data);
पूर्णांक sisusb_पढ़ोb(काष्ठा sisusb_usb_data *sisusb, u32 adr, u8 * data);
पूर्णांक sisusb_copy_memory(काष्ठा sisusb_usb_data *sisusb, u8 *src,
		       u32 dest, पूर्णांक length);
पूर्णांक sisusb_reset_text_mode(काष्ठा sisusb_usb_data *sisusb, पूर्णांक init);
पूर्णांक sisusbcon_करो_font_op(काष्ठा sisusb_usb_data *sisusb, पूर्णांक set, पूर्णांक slot,
			 u8 * arg, पूर्णांक cmapsz, पूर्णांक ch512, पूर्णांक करोrecalc,
			 काष्ठा vc_data *c, पूर्णांक fh, पूर्णांक uplock);
व्योम sisusb_set_cursor(काष्ठा sisusb_usb_data *sisusb, अचिन्हित पूर्णांक location);
पूर्णांक sisusb_console_init(काष्ठा sisusb_usb_data *sisusb, पूर्णांक first, पूर्णांक last);
व्योम sisusb_console_निकास(काष्ठा sisusb_usb_data *sisusb);
व्योम sisusb_init_concode(व्योम);

#पूर्ण_अगर
