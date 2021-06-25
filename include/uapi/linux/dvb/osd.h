<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * osd.h - DEPRECATED On Screen Display API
 *
 * NOTE: should not be used on future drivers
 *
 * Copyright (C) 2001 Ralph  Metzler <ralph@convergence.de>
 *                  & Marcus Metzler <marcus@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Lesser Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVBOSD_H_
#घोषणा _DVBOSD_H_

#समावेश <linux/compiler.h>

प्रकार क्रमागत अणु
	/* All functions वापस -2 on "not open" */
	OSD_Close = 1,	/* () */
	/*
	 * Disables OSD and releases the buffers
	 * वापसs 0 on success
	 */
	OSD_Open,	/* (x0,y0,x1,y1,BitPerPixel[2/4/8](color&0x0F),mix[0..15](color&0xF0)) */
	/*
	 * Opens OSD with this size and bit depth
	 * वापसs 0 on success, -1 on DRAM allocation error, -2 on "already open"
	 */
	OSD_Show,	/* () */
	/*
	 * enables OSD mode
	 * वापसs 0 on success
	 */
	OSD_Hide,	/* () */
	/*
	 * disables OSD mode
	 * वापसs 0 on success
	 */
	OSD_Clear,	/* () */
	/*
	 * Sets all pixel to color 0
	 * वापसs 0 on success
	 */
	OSD_Fill,	/* (color) */
	/*
	 * Sets all pixel to color <col>
	 * वापसs 0 on success
	 */
	OSD_SetColor,	/* (color,Rअणुx0पूर्ण,Gअणुy0पूर्ण,Bअणुx1पूर्ण,opacityअणुy1पूर्ण) */
	/*
	 * set palette entry <num> to <r,g,b>, <mix> and <trans> apply
	 * R,G,B: 0..255
	 * R=Red, G=Green, B=Blue
	 * opacity=0:      pixel opacity 0% (only video pixel shows)
	 * opacity=1..254: pixel opacity as specअगरied in header
	 * opacity=255:    pixel opacity 100% (only OSD pixel shows)
	 * वापसs 0 on success, -1 on error
	 */
	OSD_SetPalette,	/* (firstcolorअणुcolorपूर्ण,lastcolorअणुx0पूर्ण,data) */
	/*
	 * Set a number of entries in the palette
	 * sets the entries "firstcolor" through "lastcolor" from the array "data"
	 * data has 4 byte क्रम each color:
	 * R,G,B, and a opacity value: 0->transparent, 1..254->mix, 255->pixel
	 */
	OSD_SetTrans,	/* (transparencyअणुcolorपूर्ण) */
	/*
	 * Sets transparency of mixed pixel (0..15)
	 * वापसs 0 on success
	 */
	OSD_SetPixel,	/* (x0,y0,color) */
	/*
	 * sets pixel <x>,<y> to color number <col>
	 * वापसs 0 on success, -1 on error
	 */
	OSD_GetPixel,	/* (x0,y0) */
	/* वापसs color number of pixel <x>,<y>,  or -1 */
	OSD_SetRow,	/* (x0,y0,x1,data) */
	/*
	 * fills pixels x0,y through  x1,y with the content of data[]
	 * वापसs 0 on success, -1 on clipping all pixel (no pixel drawn)
	 */
	OSD_SetBlock,	/* (x0,y0,x1,y1,incrementअणुcolorपूर्ण,data) */
	/*
	 * fills pixels x0,y0 through  x1,y1 with the content of data[]
	 * inc contains the width of one line in the data block,
	 * inc<=0 uses blockwidth as linewidth
	 * वापसs 0 on success, -1 on clipping all pixel
	 */
	OSD_FillRow,	/* (x0,y0,x1,color) */
	/*
	 * fills pixels x0,y through  x1,y with the color <col>
	 * वापसs 0 on success, -1 on clipping all pixel
	 */
	OSD_FillBlock,	/* (x0,y0,x1,y1,color) */
	/*
	 * fills pixels x0,y0 through  x1,y1 with the color <col>
	 * वापसs 0 on success, -1 on clipping all pixel
	 */
	OSD_Line,	/* (x0,y0,x1,y1,color) */
	/*
	 * draw a line from x0,y0 to x1,y1 with the color <col>
	 * वापसs 0 on success
	 */
	OSD_Query,	/* (x0,y0,x1,y1,xaspअणुcolorपूर्णपूर्ण), yasp=11 */
	/*
	 * fills parameters with the picture dimensions and the pixel aspect ratio
	 * वापसs 0 on success
	 */
	OSD_Test,       /* () */
	/*
	 * draws a test picture. क्रम debugging purposes only
	 * वापसs 0 on success
	 * TODO: हटाओ "test" in final version
	 */
	OSD_Text,	/* (x0,y0,size,color,text) */
	OSD_SetWinकरोw,	/* (x0) set winकरोw with number 0<x0<8 as current */
	OSD_MoveWinकरोw,	/* move current winकरोw to (x0, y0) */
	OSD_OpenRaw,	/* Open other types of OSD winकरोws */
पूर्ण OSD_Command;

प्रकार काष्ठा osd_cmd_s अणु
	OSD_Command cmd;
	पूर्णांक x0;
	पूर्णांक y0;
	पूर्णांक x1;
	पूर्णांक y1;
	पूर्णांक color;
	व्योम __user *data;
पूर्ण osd_cmd_t;

/* OSD_OpenRaw: set 'color' to desired winकरोw type */
प्रकार क्रमागत अणु
	OSD_BITMAP1,           /* 1 bit biपंचांगap */
	OSD_BITMAP2,           /* 2 bit biपंचांगap */
	OSD_BITMAP4,           /* 4 bit biपंचांगap */
	OSD_BITMAP8,           /* 8 bit biपंचांगap */
	OSD_BITMAP1HR,         /* 1 Bit biपंचांगap half resolution */
	OSD_BITMAP2HR,         /* 2 bit biपंचांगap half resolution */
	OSD_BITMAP4HR,         /* 4 bit biपंचांगap half resolution */
	OSD_BITMAP8HR,         /* 8 bit biपंचांगap half resolution */
	OSD_YCRCB422,          /* 4:2:2 YCRCB Graphic Display */
	OSD_YCRCB444,          /* 4:4:4 YCRCB Graphic Display */
	OSD_YCRCB444HR,        /* 4:4:4 YCRCB graphic half resolution */
	OSD_VIDEOTSIZE,        /* True Size Normal MPEG Video Display */
	OSD_VIDEOHSIZE,        /* MPEG Video Display Half Resolution */
	OSD_VIDEOQSIZE,        /* MPEG Video Display Quarter Resolution */
	OSD_VIDEODSIZE,        /* MPEG Video Display Double Resolution */
	OSD_VIDEOTHSIZE,       /* True Size MPEG Video Display Half Resolution */
	OSD_VIDEOTQSIZE,       /* True Size MPEG Video Display Quarter Resolution*/
	OSD_VIDEOTDSIZE,       /* True Size MPEG Video Display Double Resolution */
	OSD_VIDEONSIZE,        /* Full Size MPEG Video Display */
	OSD_CURSOR             /* Cursor */
पूर्ण osd_raw_winकरोw_t;

प्रकार काष्ठा osd_cap_s अणु
	पूर्णांक  cmd;
#घोषणा OSD_CAP_MEMSIZE         1  /* memory size */
	दीर्घ val;
पूर्ण osd_cap_t;


#घोषणा OSD_SEND_CMD            _IOW('o', 160, osd_cmd_t)
#घोषणा OSD_GET_CAPABILITY      _IOR('o', 161, osd_cap_t)

#पूर्ण_अगर
