<शैली गुरु>
/*
 * linux/drivers/video/savagefb.h -- S3 Savage Framebuffer Driver
 *
 * Copyright (c) 2001  Denis Oliver Kropp <करोk@convergence.de>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */


#अगर_अघोषित __SAVAGEFB_H__
#घोषणा __SAVAGEFB_H__

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/mutex.h>
#समावेश <video/vga.h>
#समावेश "../edid.h"

#अगर_घोषित SAVAGEFB_DEBUG
# define DBG(x)		prपूर्णांकk (KERN_DEBUG "savagefb: %s\n", (x));
#अन्यथा
# define DBG(x)		no_prपूर्णांकk(x)
# define SavagePrपूर्णांकRegs(...)
#पूर्ण_अगर


#घोषणा PCI_CHIP_SAVAGE4      0x8a22
#घोषणा PCI_CHIP_SAVAGE3D     0x8a20
#घोषणा PCI_CHIP_SAVAGE3D_MV  0x8a21
#घोषणा PCI_CHIP_SAVAGE2000   0x9102
#घोषणा PCI_CHIP_SAVAGE_MX_MV 0x8c10
#घोषणा PCI_CHIP_SAVAGE_MX    0x8c11
#घोषणा PCI_CHIP_SAVAGE_IX_MV 0x8c12
#घोषणा PCI_CHIP_SAVAGE_IX    0x8c13
#घोषणा PCI_CHIP_PROSAVAGE_PM 0x8a25
#घोषणा PCI_CHIP_PROSAVAGE_KM 0x8a26
#घोषणा PCI_CHIP_S3TWISTER_P  0x8d01
#घोषणा PCI_CHIP_S3TWISTER_K  0x8d02
#घोषणा PCI_CHIP_PROSAVAGE_DDR          0x8d03
#घोषणा PCI_CHIP_PROSAVAGE_DDRK         0x8d04
#घोषणा PCI_CHIP_SUPSAV_MX128		0x8c22
#घोषणा PCI_CHIP_SUPSAV_MX64		0x8c24
#घोषणा PCI_CHIP_SUPSAV_MX64C		0x8c26
#घोषणा PCI_CHIP_SUPSAV_IX128SDR	0x8c2a
#घोषणा PCI_CHIP_SUPSAV_IX128DDR	0x8c2b
#घोषणा PCI_CHIP_SUPSAV_IX64SDR		0x8c2c
#घोषणा PCI_CHIP_SUPSAV_IX64DDR		0x8c2d
#घोषणा PCI_CHIP_SUPSAV_IXCSDR		0x8c2e
#घोषणा PCI_CHIP_SUPSAV_IXCDDR		0x8c2f


#घोषणा S3_SAVAGE_SERIES(chip)    ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE2000))

#घोषणा S3_SAVAGE3D_SERIES(chip)  ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE_MX))

#घोषणा S3_SAVAGE4_SERIES(chip)   ((chip>=S3_SAVAGE4) && (chip<=S3_PROSAVAGEDDR))

#घोषणा S3_SAVAGE_MOBILE_SERIES(chip)  ((chip==S3_SAVAGE_MX) || (chip==S3_SUPERSAVAGE))

#घोषणा S3_MOBILE_TWISTER_SERIES(chip) ((chip==S3_TWISTER) || (chip==S3_PROSAVAGEDDR))

/* Chip tags.  These are used to group the adapters पूर्णांकo
 * related families.
 */

प्रकार क्रमागत अणु
  S3_UNKNOWN = 0,
  S3_SAVAGE3D,
  S3_SAVAGE_MX,
  S3_SAVAGE4,
  S3_PROSAVAGE,
  S3_TWISTER,
  S3_PROSAVAGEDDR,
  S3_SUPERSAVAGE,
  S3_SAVAGE2000,
  S3_LAST
पूर्ण savage_chipset;

#घोषणा BIOS_BSIZE		     1024
#घोषणा BIOS_BASE		     0xc0000

#घोषणा SAVAGE_NEWMMIO_REGBASE_S3    0x1000000  /* 16MB */
#घोषणा SAVAGE_NEWMMIO_REGBASE_S4    0x0000000
#घोषणा SAVAGE_NEWMMIO_REGSIZE	     0x0080000  /* 512kb */
#घोषणा SAVAGE_NEWMMIO_VGABASE	     0x8000

#घोषणा BASE_FREQ		     14318
#घोषणा HALF_BASE_FREQ               7159

#घोषणा FIFO_CONTROL_REG	     0x8200
#घोषणा MIU_CONTROL_REG		     0x8204
#घोषणा STREAMS_TIMEOUT_REG	     0x8208
#घोषणा MISC_TIMEOUT_REG	     0x820c

#घोषणा MONO_PAT_0                   0xa4e8
#घोषणा MONO_PAT_1                   0xa4ec

#घोषणा MAXFIFO                      0x7f00

#घोषणा BCI_CMD_NOP                  0x40000000
#घोषणा BCI_CMD_SETREG               0x96000000
#घोषणा BCI_CMD_RECT                 0x48000000
#घोषणा BCI_CMD_RECT_XP              0x01000000
#घोषणा BCI_CMD_RECT_YP              0x02000000
#घोषणा BCI_CMD_SEND_COLOR           0x00008000
#घोषणा BCI_CMD_DEST_GBD             0x00000000
#घोषणा BCI_CMD_SRC_GBD              0x00000020
#घोषणा BCI_CMD_SRC_SOLID            0x00000000
#घोषणा BCI_CMD_SRC_MONO             0x00000060
#घोषणा BCI_CMD_CLIP_NEW             0x00006000
#घोषणा BCI_CMD_CLIP_LR              0x00004000

#घोषणा BCI_CLIP_LR(l, r)            ((((r) << 16) | (l)) & 0x0FFF0FFF)
#घोषणा BCI_CLIP_TL(t, l)            ((((t) << 16) | (l)) & 0x0FFF0FFF)
#घोषणा BCI_CLIP_BR(b, r)            ((((b) << 16) | (r)) & 0x0FFF0FFF)
#घोषणा BCI_W_H(w, h)                (((h) << 16) | ((w) & 0xFFF))
#घोषणा BCI_X_Y(x, y)                (((y) << 16) | ((x) & 0xFFF))

#घोषणा BCI_GBD1                     0xE0
#घोषणा BCI_GBD2                     0xE1

#घोषणा BCI_BUFFER_OFFSET            0x10000
#घोषणा BCI_SIZE                     0x4000

#घोषणा BCI_SEND(dw)                 ग_लिखोl(dw, par->bci_base + par->bci_ptr++)

#घोषणा BCI_CMD_GET_ROP(cmd)         (((cmd) >> 16) & 0xFF)
#घोषणा BCI_CMD_SET_ROP(cmd, rop)    ((cmd) |= ((rop & 0xFF) << 16))
#घोषणा BCI_CMD_SEND_COLOR           0x00008000

#घोषणा DISP_CRT     1
#घोषणा DISP_LCD     2
#घोषणा DISP_DFP     3

काष्ठा xtimings अणु
	अचिन्हित पूर्णांक Clock;
	अचिन्हित पूर्णांक HDisplay;
	अचिन्हित पूर्णांक HSyncStart;
	अचिन्हित पूर्णांक HSyncEnd;
	अचिन्हित पूर्णांक HTotal;
	अचिन्हित पूर्णांक HAdjusted;
	अचिन्हित पूर्णांक VDisplay;
	अचिन्हित पूर्णांक VSyncStart;
	अचिन्हित पूर्णांक VSyncEnd;
	अचिन्हित पूर्णांक VTotal;
	अचिन्हित पूर्णांक sync;
	पूर्णांक	       dblscan;
	पूर्णांक	       पूर्णांकerlaced;
पूर्ण;

काष्ठा savage_reg अणु
	अचिन्हित अक्षर MiscOutReg;     /* Misc */
	अचिन्हित अक्षर CRTC[25];       /* Crtc Controller */
	अचिन्हित अक्षर Sequencer[5];   /* Video Sequencer */
	अचिन्हित अक्षर Graphics[9];    /* Video Graphics */
	अचिन्हित अक्षर Attribute[21];  /* Video Attribute */

	अचिन्हित पूर्णांक mode, refresh;
	अचिन्हित अक्षर SR08, SR0E, SR0F;
	अचिन्हित अक्षर SR10, SR11, SR12, SR13, SR15, SR18, SR29, SR30;
	अचिन्हित अक्षर SR54[8];
	अचिन्हित अक्षर Clock;
	अचिन्हित अक्षर CR31, CR32, CR33, CR34, CR36, CR3A, CR3B, CR3C;
	अचिन्हित अक्षर CR40, CR41, CR42, CR43, CR45;
	अचिन्हित अक्षर CR50, CR51, CR53, CR55, CR58, CR5B, CR5D, CR5E;
	अचिन्हित अक्षर CR60, CR63, CR65, CR66, CR67, CR68, CR69, CR6D, CR6F;
	अचिन्हित अक्षर CR86, CR88;
	अचिन्हित अक्षर CR90, CR91, CRB0;
	अचिन्हित पूर्णांक  STREAMS[22];	/* yuck, streams regs */
	अचिन्हित पूर्णांक  MMPR0, MMPR1, MMPR2, MMPR3;
पूर्ण;
/* --------------------------------------------------------------------- */

#घोषणा NR_PALETTE	256


काष्ठा savagefb_par;

काष्ठा savagefb_i2c_chan अणु
	काष्ठा savagefb_par *par;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
	अस्थिर u8 __iomem *ioaddr;
	u32   reg;
पूर्ण;

काष्ठा savagefb_par अणु
	काष्ठा pci_dev *pcidev;
	savage_chipset  chip;
	काष्ठा savagefb_i2c_chan chan;
	काष्ठा savage_reg state;
	काष्ठा savage_reg save;
	काष्ठा savage_reg initial;
	काष्ठा vgastate vgastate;
	काष्ठा mutex खोलो_lock;
	अचिन्हित अक्षर   *edid;
	u32 pseuकरो_palette[16];
	u32 खोलो_count;
	पूर्णांक paletteEnabled;
	पूर्णांक pm_state;
	पूर्णांक display_type;
	पूर्णांक dvi;
	पूर्णांक crtonly;
	पूर्णांक dacSpeedBpp;
	पूर्णांक maxClock;
	पूर्णांक minClock;
	पूर्णांक numClocks;
	पूर्णांक घड़ी[4];
	पूर्णांक MCLK, REFCLK, LCDclk;
	काष्ठा अणु
		व्योम   __iomem *vbase;
		u32    pbase;
		u32    len;
		पूर्णांक    wc_cookie;
	पूर्ण video;

	काष्ठा अणु
		व्योम  __iomem *vbase;
		u32           pbase;
		u32           len;
	पूर्ण mmio;

	अस्थिर u32  __iomem *bci_base;
	अचिन्हित पूर्णांक  bci_ptr;
	u32           cob_offset;
	u32           cob_size;
	पूर्णांक           cob_index;

	व्योम (*SavageWaitIdle) (काष्ठा savagefb_par *par);
	व्योम (*SavageWaitFअगरo) (काष्ठा savagefb_par *par, पूर्णांक space);

	पूर्णांक HorizScaleFactor;

	/* Panels size */
	पूर्णांक SavagePanelWidth;
	पूर्णांक SavagePanelHeight;

	काष्ठा अणु
		u16 red, green, blue, transp;
	पूर्ण palette[NR_PALETTE];

	पूर्णांक depth;
	पूर्णांक vwidth;
पूर्ण;

#घोषणा BCI_BD_BW_DISABLE            0x10000000
#घोषणा BCI_BD_SET_BPP(bd, bpp)      ((bd) |= (((bpp) & 0xFF) << 16))
#घोषणा BCI_BD_SET_STRIDE(bd, st)    ((bd) |= ((st) & 0xFFFF))


/* IO functions */
अटल अंतरभूत u8 savage_in8(u32 addr, काष्ठा savagefb_par *par)
अणु
	वापस पढ़ोb(par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत u16 savage_in16(u32 addr, काष्ठा savagefb_par *par)
अणु
	वापस पढ़ोw(par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत u32 savage_in32(u32 addr, काष्ठा savagefb_par *par)
अणु
	वापस पढ़ोl(par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत व्योम savage_out8(u32 addr, u8 val, काष्ठा savagefb_par *par)
अणु
	ग_लिखोb(val, par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत व्योम savage_out16(u32 addr, u16 val, काष्ठा savagefb_par *par)
अणु
	ग_लिखोw(val, par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत व्योम savage_out32(u32 addr, u32 val, काष्ठा savagefb_par *par)
अणु
	ग_लिखोl(val, par->mmio.vbase + addr);
पूर्ण

अटल अंतरभूत u8 vga_in8(पूर्णांक addr, काष्ठा savagefb_par *par)
अणु
	वापस savage_in8(0x8000 + addr, par);
पूर्ण

अटल अंतरभूत u16 vga_in16(पूर्णांक addr, काष्ठा savagefb_par *par)
अणु
	वापस savage_in16(0x8000 + addr, par);
पूर्ण

अटल अंतरभूत u8 vga_in32(पूर्णांक addr, काष्ठा savagefb_par *par)
अणु
	वापस savage_in32(0x8000 + addr, par);
पूर्ण

अटल अंतरभूत व्योम vga_out8(पूर्णांक addr, u8 val, काष्ठा savagefb_par *par)
अणु
	savage_out8(0x8000 + addr, val, par);
पूर्ण

अटल अंतरभूत व्योम vga_out16(पूर्णांक addr, u16 val, काष्ठा savagefb_par *par)
अणु
	savage_out16(0x8000 + addr, val, par);
पूर्ण

अटल अंतरभूत व्योम vga_out32(पूर्णांक addr, u32 val, काष्ठा savagefb_par *par)
अणु
	savage_out32(0x8000 + addr, val, par);
पूर्ण

अटल अंतरभूत u8 VGArCR (u8 index, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3d4, index,  par);
	वापस vga_in8(0x3d5, par);
पूर्ण

अटल अंतरभूत u8 VGArGR (u8 index, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3ce, index, par);
	वापस vga_in8(0x3cf, par);
पूर्ण

अटल अंतरभूत u8 VGArSEQ (u8 index, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3c4, index, par);
	वापस vga_in8(0x3c5, par);
पूर्ण

अटल अंतरभूत व्योम VGAwCR(u8 index, u8 val, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3d4, index, par);
	vga_out8(0x3d5, val, par);
पूर्ण

अटल अंतरभूत व्योम VGAwGR(u8 index, u8 val, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3ce, index, par);
	vga_out8(0x3cf, val, par);
पूर्ण

अटल अंतरभूत व्योम VGAwSEQ(u8 index, u8 val, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3c4, index, par);
	vga_out8 (0x3c5, val, par);
पूर्ण

अटल अंतरभूत व्योम VGAenablePalette(काष्ठा savagefb_par *par)
अणु
	vga_in8(0x3da, par);
	vga_out8(0x3c0, 0x00, par);
	par->paletteEnabled = 1;
पूर्ण

अटल अंतरभूत व्योम VGAdisablePalette(काष्ठा savagefb_par *par)
अणु
	vga_in8(0x3da, par);
	vga_out8(0x3c0, 0x20, par);
	par->paletteEnabled = 0;
पूर्ण

अटल अंतरभूत व्योम VGAwATTR(u8 index, u8 value, काष्ठा savagefb_par *par)
अणु
	अगर (par->paletteEnabled)
		index &= ~0x20;
	अन्यथा
		index |= 0x20;

	vga_in8(0x3da, par);
	vga_out8(0x3c0, index, par);
	vga_out8 (0x3c0, value, par);
पूर्ण

अटल अंतरभूत व्योम VGAwMISC(u8 value, काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3c2, value, par);
पूर्ण

#अगर_अघोषित CONFIG_FB_SAVAGE_ACCEL
#घोषणा savagefb_set_clip(x)
#पूर्ण_अगर

अटल अंतरभूत व्योम VerticalRetraceWait(काष्ठा savagefb_par *par)
अणु
	vga_out8(0x3d4, 0x17, par);
	अगर (vga_in8(0x3d5, par) & 0x80) अणु
		जबतक ((vga_in8(0x3da, par) & 0x08) == 0x08);
		जबतक ((vga_in8(0x3da, par) & 0x08) == 0x00);
	पूर्ण
पूर्ण

बाह्य पूर्णांक savagefb_probe_i2c_connector(काष्ठा fb_info *info,
					u8 **out_edid);
बाह्य व्योम savagefb_create_i2c_busses(काष्ठा fb_info *info);
बाह्य व्योम savagefb_delete_i2c_busses(काष्ठा fb_info *info);
बाह्य पूर्णांक  savagefb_sync(काष्ठा fb_info *info);
बाह्य व्योम savagefb_copyarea(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_copyarea *region);
बाह्य व्योम savagefb_fillrect(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम savagefb_imageblit(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_image *image);


#पूर्ण_अगर /* __SAVAGEFB_H__ */
