<शैली गुरु>
/*
 * linux/include/video/neo_reg.h -- NeoMagic Framebuffer Driver
 *
 * Copyright (c) 2001  Denis Oliver Kropp <करोk@convergence.de>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#घोषणा NEO_BS0_BLT_BUSY        0x00000001
#घोषणा NEO_BS0_FIFO_AVAIL      0x00000002
#घोषणा NEO_BS0_FIFO_PEND       0x00000004

#घोषणा NEO_BC0_DST_Y_DEC       0x00000001
#घोषणा NEO_BC0_X_DEC           0x00000002
#घोषणा NEO_BC0_SRC_TRANS       0x00000004
#घोषणा NEO_BC0_SRC_IS_FG       0x00000008
#घोषणा NEO_BC0_SRC_Y_DEC       0x00000010
#घोषणा NEO_BC0_FILL_PAT        0x00000020
#घोषणा NEO_BC0_SRC_MONO        0x00000040
#घोषणा NEO_BC0_SYS_TO_VID      0x00000080

#घोषणा NEO_BC1_DEPTH8          0x00000100
#घोषणा NEO_BC1_DEPTH16         0x00000200
#घोषणा NEO_BC1_X_320           0x00000400
#घोषणा NEO_BC1_X_640           0x00000800
#घोषणा NEO_BC1_X_800           0x00000c00
#घोषणा NEO_BC1_X_1024          0x00001000
#घोषणा NEO_BC1_X_1152          0x00001400
#घोषणा NEO_BC1_X_1280          0x00001800
#घोषणा NEO_BC1_X_1600          0x00001c00
#घोषणा NEO_BC1_DST_TRANS       0x00002000
#घोषणा NEO_BC1_MSTR_BLT        0x00004000
#घोषणा NEO_BC1_FILTER_Z        0x00008000

#घोषणा NEO_BC2_WR_TR_DST       0x00800000

#घोषणा NEO_BC3_SRC_XY_ADDR     0x01000000
#घोषणा NEO_BC3_DST_XY_ADDR     0x02000000
#घोषणा NEO_BC3_CLIP_ON         0x04000000
#घोषणा NEO_BC3_FIFO_EN         0x08000000
#घोषणा NEO_BC3_BLT_ON_ADDR     0x10000000
#घोषणा NEO_BC3_SKIP_MAPPING    0x80000000

#घोषणा NEO_MODE1_DEPTH8        0x0100
#घोषणा NEO_MODE1_DEPTH16       0x0200
#घोषणा NEO_MODE1_DEPTH24       0x0300
#घोषणा NEO_MODE1_X_320         0x0400
#घोषणा NEO_MODE1_X_640         0x0800
#घोषणा NEO_MODE1_X_800         0x0c00
#घोषणा NEO_MODE1_X_1024        0x1000
#घोषणा NEO_MODE1_X_1152        0x1400
#घोषणा NEO_MODE1_X_1280        0x1800
#घोषणा NEO_MODE1_X_1600        0x1c00
#घोषणा NEO_MODE1_BLT_ON_ADDR   0x2000

/* These are offseted in MMIO space by par->CursorOff */
#घोषणा NEOREG_CURSCNTL		0x00
#घोषणा NEOREG_CURSX		0x04
#घोषणा NEOREG_CURSY		0x08
#घोषणा NEOREG_CURSBGCOLOR	0x0C
#घोषणा NEOREG_CURSFGCOLOR	0x10
#घोषणा NEOREG_CURSMEMPOS	0x14

#घोषणा NEO_CURS_DISABLE	0x00000000
#घोषणा NEO_CURS_ENABLE		0x00000001
#घोषणा NEO_ICON64_ENABLE	0x00000008
#घोषणा NEO_ICON128_ENABLE	0x0000000C
#घोषणा NEO_ICON_BLANK		0x00000010

#घोषणा NEO_GR01_SUPPRESS_VSYNC 0x10
#घोषणा NEO_GR01_SUPPRESS_HSYNC 0x20

#अगर_घोषित __KERNEL__

#अगर_घोषित Nखातापूर्णB_DEBUG
# define DBG(x)		prपूर्णांकk (KERN_DEBUG "neofb: %s\n", (x));
#अन्यथा
# define DBG(x)
#पूर्ण_अगर

#घोषणा PCI_CHIP_NM2070 0x0001
#घोषणा PCI_CHIP_NM2090 0x0002
#घोषणा PCI_CHIP_NM2093 0x0003
#घोषणा PCI_CHIP_NM2097 0x0083
#घोषणा PCI_CHIP_NM2160 0x0004
#घोषणा PCI_CHIP_NM2200 0x0005
#घोषणा PCI_CHIP_NM2230 0x0025
#घोषणा PCI_CHIP_NM2360 0x0006
#घोषणा PCI_CHIP_NM2380 0x0016

/* --------------------------------------------------------------------- */

प्रकार अस्थिर काष्ठा अणु
	__u32 bltStat;
	__u32 bltCntl;
	__u32 xpColor;
	__u32 fgColor;
	__u32 bgColor;
	__u32 pitch;
	__u32 clipLT;
	__u32 clipRB;
	__u32 srcBitOffset;
	__u32 srcStart;
	__u32 reserved0;
	__u32 dstStart;
	__u32 xyExt;

	__u32 reserved1[19];

	__u32 pageCntl;
	__u32 pageBase;
	__u32 postBase;
	__u32 postPtr;
	__u32 dataPtr;
पूर्ण Neo2200;

#घोषणा MMIO_SIZE 0x200000

#घोषणा NEO_EXT_CR_MAX 0x85
#घोषणा NEO_EXT_GR_MAX 0xC7

काष्ठा neofb_par अणु
	काष्ठा vgastate state;
	अचिन्हित पूर्णांक ref_count;

	अचिन्हित अक्षर MiscOutReg;	/* Misc */
	अचिन्हित अक्षर CRTC[25];		/* Crtc Controller */
	अचिन्हित अक्षर Sequencer[5];	/* Video Sequencer */
	अचिन्हित अक्षर Graphics[9];	/* Video Graphics */
	अचिन्हित अक्षर Attribute[21];	/* Video Attribute */

	अचिन्हित अक्षर GeneralLockReg;
	अचिन्हित अक्षर ExtCRTDispAddr;
	अचिन्हित अक्षर ExtCRTOffset;
	अचिन्हित अक्षर SysIfaceCntl1;
	अचिन्हित अक्षर SysIfaceCntl2;
	अचिन्हित अक्षर ExtColorModeSelect;
	अचिन्हित अक्षर biosMode;

	अचिन्हित अक्षर PanelDispCntlReg1;
	अचिन्हित अक्षर PanelDispCntlReg2;
	अचिन्हित अक्षर PanelDispCntlReg3;
	अचिन्हित अक्षर PanelDispCntlRegRead;
	अचिन्हित अक्षर PanelVertCenterReg1;
	अचिन्हित अक्षर PanelVertCenterReg2;
	अचिन्हित अक्षर PanelVertCenterReg3;
	अचिन्हित अक्षर PanelVertCenterReg4;
	अचिन्हित अक्षर PanelVertCenterReg5;
	अचिन्हित अक्षर PanelHorizCenterReg1;
	अचिन्हित अक्षर PanelHorizCenterReg2;
	अचिन्हित अक्षर PanelHorizCenterReg3;
	अचिन्हित अक्षर PanelHorizCenterReg4;
	अचिन्हित अक्षर PanelHorizCenterReg5;

	पूर्णांक ProgramVCLK;
	अचिन्हित अक्षर VCLK3NumeratorLow;
	अचिन्हित अक्षर VCLK3NumeratorHigh;
	अचिन्हित अक्षर VCLK3Denominator;
	अचिन्हित अक्षर VerticalExt;
	पूर्णांक wc_cookie;
	u8 __iomem *mmio_vbase;
	u8 cursorOff;
	u8 *cursorPad;		/* Must die !! */

	Neo2200 __iomem *neo2200;

	/* Panels size */
	पूर्णांक NeoPanelWidth;
	पूर्णांक NeoPanelHeight;

	पूर्णांक maxClock;

	पूर्णांक pci_burst;
	पूर्णांक lcd_stretch;
	पूर्णांक पूर्णांकernal_display;
	पूर्णांक बाह्यal_display;
	पूर्णांक libretto;
	u32 palette[16];
पूर्ण;

प्रकार काष्ठा अणु
	पूर्णांक x_res;
	पूर्णांक y_res;
	पूर्णांक mode;
पूर्ण biosMode;

#पूर्ण_अगर
