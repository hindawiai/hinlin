<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) Intel Corp. 2007.
 * All Rights Reserved.
 *
 * Intel funded Tungsten Graphics (http://www.tungstengraphics.com) to
 * develop this driver.
 *
 * This file is part of the Vermilion Range fb driver.
 *
 * Authors:
 *   Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#अगर_अघोषित _VERMILION_H_
#घोषणा _VERMILION_H_

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mutex.h>

#घोषणा VML_DEVICE_GPU 0x5002
#घोषणा VML_DEVICE_VDC 0x5009

#घोषणा VML_VRAM_AREAS 3
#घोषणा VML_MAX_XRES 1024
#घोषणा VML_MAX_YRES 768
#घोषणा VML_MAX_XRES_VIRTUAL 1040

/*
 * Display controller रेजिस्टरs:
 */

/* Display controller 10-bit color representation */

#घोषणा VML_R_MASK                   0x3FF00000
#घोषणा VML_R_SHIFT                  20
#घोषणा VML_G_MASK                   0x000FFC00
#घोषणा VML_G_SHIFT                  10
#घोषणा VML_B_MASK                   0x000003FF
#घोषणा VML_B_SHIFT                  0

/* Graphics plane control */
#घोषणा VML_DSPCCNTR                 0x00072180
#घोषणा VML_GFX_ENABLE               0x80000000
#घोषणा VML_GFX_GAMMABYPASS          0x40000000
#घोषणा VML_GFX_ARGB1555             0x0C000000
#घोषणा VML_GFX_RGB0888              0x18000000
#घोषणा VML_GFX_ARGB8888             0x1C000000
#घोषणा VML_GFX_ALPHACONST           0x02000000
#घोषणा VML_GFX_ALPHAMULT            0x01000000
#घोषणा VML_GFX_CONST_ALPHA          0x000000FF

/* Graphics plane start address. Pixel aligned. */
#घोषणा VML_DSPCADDR                 0x00072184

/* Graphics plane stride रेजिस्टर. */
#घोषणा VML_DSPCSTRIDE               0x00072188

/* Graphics plane position रेजिस्टर. */
#घोषणा VML_DSPCPOS                  0x0007218C
#घोषणा VML_POS_YMASK                0x0FFF0000
#घोषणा VML_POS_YSHIFT               16
#घोषणा VML_POS_XMASK                0x00000FFF
#घोषणा VML_POS_XSHIFT               0

/* Graphics plane height and width */
#घोषणा VML_DSPCSIZE                 0x00072190
#घोषणा VML_SIZE_HMASK               0x0FFF0000
#घोषणा VML_SIZE_HSHIFT              16
#घोषणा VML_SISE_WMASK               0x00000FFF
#घोषणा VML_SIZE_WSHIFT              0

/* Graphics plane gamma correction lookup table रेजिस्टरs (129 * 32 bits) */
#घोषणा VML_DSPCGAMLUT               0x00072200

/* Pixel video output configuration रेजिस्टर */
#घोषणा VML_PVOCONFIG                0x00061140
#घोषणा VML_CONFIG_BASE              0x80000000
#घोषणा VML_CONFIG_PIXEL_SWAP        0x04000000
#घोषणा VML_CONFIG_DE_INV            0x01000000
#घोषणा VML_CONFIG_HREF_INV          0x00400000
#घोषणा VML_CONFIG_VREF_INV          0x00100000
#घोषणा VML_CONFIG_CLK_INV           0x00040000
#घोषणा VML_CONFIG_CLK_DIV2          0x00010000
#घोषणा VML_CONFIG_ESTRB_INV         0x00008000

/* Pipe A Horizontal total रेजिस्टर */
#घोषणा VML_HTOTAL_A                 0x00060000
#घोषणा VML_HTOTAL_MASK              0x1FFF0000
#घोषणा VML_HTOTAL_SHIFT             16
#घोषणा VML_HTOTAL_VAL               8192
#घोषणा VML_HACTIVE_MASK             0x000007FF
#घोषणा VML_HACTIVE_SHIFT            0
#घोषणा VML_HACTIVE_VAL              4096

/* Pipe A Horizontal Blank रेजिस्टर */
#घोषणा VML_HBLANK_A                 0x00060004
#घोषणा VML_HBLANK_END_MASK          0x1FFF0000
#घोषणा VML_HBLANK_END_SHIFT         16
#घोषणा VML_HBLANK_END_VAL           8192
#घोषणा VML_HBLANK_START_MASK        0x00001FFF
#घोषणा VML_HBLANK_START_SHIFT       0
#घोषणा VML_HBLANK_START_VAL         8192

/* Pipe A Horizontal Sync रेजिस्टर */
#घोषणा VML_HSYNC_A                  0x00060008
#घोषणा VML_HSYNC_END_MASK           0x1FFF0000
#घोषणा VML_HSYNC_END_SHIFT          16
#घोषणा VML_HSYNC_END_VAL            8192
#घोषणा VML_HSYNC_START_MASK         0x00001FFF
#घोषणा VML_HSYNC_START_SHIFT        0
#घोषणा VML_HSYNC_START_VAL          8192

/* Pipe A Vertical total रेजिस्टर */
#घोषणा VML_VTOTAL_A                 0x0006000C
#घोषणा VML_VTOTAL_MASK              0x1FFF0000
#घोषणा VML_VTOTAL_SHIFT             16
#घोषणा VML_VTOTAL_VAL               8192
#घोषणा VML_VACTIVE_MASK             0x000007FF
#घोषणा VML_VACTIVE_SHIFT            0
#घोषणा VML_VACTIVE_VAL              4096

/* Pipe A Vertical Blank रेजिस्टर */
#घोषणा VML_VBLANK_A                 0x00060010
#घोषणा VML_VBLANK_END_MASK          0x1FFF0000
#घोषणा VML_VBLANK_END_SHIFT         16
#घोषणा VML_VBLANK_END_VAL           8192
#घोषणा VML_VBLANK_START_MASK        0x00001FFF
#घोषणा VML_VBLANK_START_SHIFT       0
#घोषणा VML_VBLANK_START_VAL         8192

/* Pipe A Vertical Sync रेजिस्टर */
#घोषणा VML_VSYNC_A                  0x00060014
#घोषणा VML_VSYNC_END_MASK           0x1FFF0000
#घोषणा VML_VSYNC_END_SHIFT          16
#घोषणा VML_VSYNC_END_VAL            8192
#घोषणा VML_VSYNC_START_MASK         0x00001FFF
#घोषणा VML_VSYNC_START_SHIFT        0
#घोषणा VML_VSYNC_START_VAL          8192

/* Pipe A Source Image size (minus one - equal to active size)
 * Programmable जबतक pipe is enabled.
 */
#घोषणा VML_PIPEASRC                 0x0006001C
#घोषणा VML_PIPEASRC_HMASK           0x0FFF0000
#घोषणा VML_PIPEASRC_HSHIFT          16
#घोषणा VML_PIPEASRC_VMASK           0x00000FFF
#घोषणा VML_PIPEASRC_VSHIFT          0

/* Pipe A Border Color Pattern रेजिस्टर (10 bit color) */
#घोषणा VML_BCLRPAT_A                0x00060020

/* Pipe A Canvas Color रेजिस्टर  (10 bit color) */
#घोषणा VML_CANVSCLR_A               0x00060024

/* Pipe A Configuration रेजिस्टर */
#घोषणा VML_PIPEACONF                0x00070008
#घोषणा VML_PIPE_BASE                0x00000000
#घोषणा VML_PIPE_ENABLE              0x80000000
#घोषणा VML_PIPE_FORCE_BORDER        0x02000000
#घोषणा VML_PIPE_PLANES_OFF          0x00080000
#घोषणा VML_PIPE_ARGB_OUTPUT_MODE    0x00040000

/* Pipe A FIFO setting */
#घोषणा VML_DSPARB                   0x00070030
#घोषणा VML_FIFO_DEFAULT             0x00001D9C

/* MDVO rcomp status & pads control रेजिस्टर */
#घोषणा VML_RCOMPSTAT                0x00070048
#घोषणा VML_MDVO_VDC_I_RCOMP         0x80000000
#घोषणा VML_MDVO_POWERSAVE_OFF       0x00000008
#घोषणा VML_MDVO_PAD_ENABLE          0x00000004
#घोषणा VML_MDVO_PULLDOWN_ENABLE     0x00000001

काष्ठा vml_par अणु
	काष्ठा pci_dev *vdc;
	u64 vdc_mem_base;
	u64 vdc_mem_size;
	अक्षर __iomem *vdc_mem;

	काष्ठा pci_dev *gpu;
	u64 gpu_mem_base;
	u64 gpu_mem_size;
	अक्षर __iomem *gpu_mem;

	atomic_t refcount;
पूर्ण;

काष्ठा vram_area अणु
	अचिन्हित दीर्घ logical;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ size;
	अचिन्हित order;
पूर्ण;

काष्ठा vml_info अणु
	काष्ठा fb_info info;
	काष्ठा vml_par *par;
	काष्ठा list_head head;
	काष्ठा vram_area vram[VML_VRAM_AREAS];
	u64 vram_start;
	u64 vram_contig_size;
	u32 num_areas;
	व्योम __iomem *vram_logical;
	u32 pseuकरो_palette[16];
	u32 stride;
	u32 bytes_per_pixel;
	atomic_t vmas;
	पूर्णांक cur_blank_mode;
	पूर्णांक pipe_disabled;
पूर्ण;

/*
 * Subप्रणाली
 */

काष्ठा vml_sys अणु
	अक्षर *name;

	/*
	 * Save / Restore;
	 */

	पूर्णांक (*save) (काष्ठा vml_sys * sys);
	पूर्णांक (*restore) (काष्ठा vml_sys * sys);

	/*
	 * PLL programming;
	 */

	पूर्णांक (*set_घड़ी) (काष्ठा vml_sys * sys, पूर्णांक घड़ी);
	पूर्णांक (*nearest_घड़ी) (स्थिर काष्ठा vml_sys * sys, पूर्णांक घड़ी);
पूर्ण;

बाह्य पूर्णांक vmlfb_रेजिस्टर_subsys(काष्ठा vml_sys *sys);
बाह्य व्योम vmlfb_unरेजिस्टर_subsys(काष्ठा vml_sys *sys);

#घोषणा VML_READ32(_par, _offset) \
	(ioपढ़ो32((_par)->vdc_mem + (_offset)))
#घोषणा VML_WRITE32(_par, _offset, _value)				\
	ioग_लिखो32(_value, (_par)->vdc_mem + (_offset))

#पूर्ण_अगर
