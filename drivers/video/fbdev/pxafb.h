<शैली गुरु>
#अगर_अघोषित __PXAFB_H__
#घोषणा __PXAFB_H__

/*
 * linux/drivers/video/pxafb.h
 *    -- Intel PXA250/210 LCD Controller Frame Buffer Device
 *
 *  Copyright (C) 1999 Eric A. Thomas.
 *  Copyright (C) 2004 Jean-Frederic Clere.
 *  Copyright (C) 2004 Ian Campbell.
 *  Copyright (C) 2004 Jeff Lackey.
 *   Based on sa1100fb.c Copyright (C) 1999 Eric A. Thomas
 *  which in turn is
 *   Based on acornfb.c Copyright (C) Russell King.
 *
 *  2001-08-03: Clअगरf Brake <cbrake@acclent.com>
 *	 - ported SA1100 code to PXA
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/* PXA LCD DMA descriptor */
काष्ठा pxafb_dma_descriptor अणु
	अचिन्हित पूर्णांक fdadr;
	अचिन्हित पूर्णांक fsadr;
	अचिन्हित पूर्णांक fidr;
	अचिन्हित पूर्णांक ldcmd;
पूर्ण;

क्रमागत अणु
	PAL_NONE	= -1,
	PAL_BASE	= 0,
	PAL_OV1		= 1,
	PAL_OV2		= 2,
	PAL_MAX,
पूर्ण;

क्रमागत अणु
	DMA_BASE	= 0,
	DMA_UPPER	= 0,
	DMA_LOWER	= 1,
	DMA_OV1		= 1,
	DMA_OV2_Y	= 2,
	DMA_OV2_Cb	= 3,
	DMA_OV2_Cr	= 4,
	DMA_CURSOR	= 5,
	DMA_CMD		= 6,
	DMA_MAX,
पूर्ण;

/* maximum palette size - 256 entries, each 4 bytes दीर्घ */
#घोषणा PALETTE_SIZE	(256 * 4)
#घोषणा CMD_BUFF_SIZE	(1024 * 50)

/* NOTE: the palette and frame dma descriptors are द्विगुनd to allow
 * the 2nd set क्रम branch settings (FBRx)
 */
काष्ठा pxafb_dma_buff अणु
	अचिन्हित अक्षर palette[PAL_MAX * PALETTE_SIZE];
	uपूर्णांक16_t cmd_buff[CMD_BUFF_SIZE];
	काष्ठा pxafb_dma_descriptor pal_desc[PAL_MAX * 2];
	काष्ठा pxafb_dma_descriptor dma_desc[DMA_MAX * 2];
पूर्ण;

क्रमागत अणु
	OVERLAY1,
	OVERLAY2,
पूर्ण;

क्रमागत अणु
	OVERLAY_FORMAT_RGB = 0,
	OVERLAY_FORMAT_YUV444_PACKED,
	OVERLAY_FORMAT_YUV444_PLANAR,
	OVERLAY_FORMAT_YUV422_PLANAR,
	OVERLAY_FORMAT_YUV420_PLANAR,
पूर्ण;

#घोषणा NONSTD_TO_XPOS(x)	(((x) >> 0)  & 0x3ff)
#घोषणा NONSTD_TO_YPOS(x)	(((x) >> 10) & 0x3ff)
#घोषणा NONSTD_TO_PFOR(x)	(((x) >> 20) & 0x7)

काष्ठा pxafb_layer;

काष्ठा pxafb_layer_ops अणु
	व्योम (*enable)(काष्ठा pxafb_layer *);
	व्योम (*disable)(काष्ठा pxafb_layer *);
	व्योम (*setup)(काष्ठा pxafb_layer *);
पूर्ण;

काष्ठा pxafb_layer अणु
	काष्ठा fb_info		fb;
	पूर्णांक			id;
	पूर्णांक			रेजिस्टरed;
	uपूर्णांक32_t		usage;
	uपूर्णांक32_t		control[2];

	काष्ठा pxafb_layer_ops	*ops;

	व्योम __iomem		*video_mem;
	अचिन्हित दीर्घ		video_mem_phys;
	माप_प्रकार			video_mem_size;
	काष्ठा completion	branch_करोne;

	काष्ठा pxafb_info	*fbi;
पूर्ण;

काष्ठा pxafb_info अणु
	काष्ठा fb_info		fb;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;

	व्योम __iomem		*mmio_base;

	काष्ठा pxafb_dma_buff	*dma_buff;
	माप_प्रकार			dma_buff_size;
	dma_addr_t		dma_buff_phys;
	dma_addr_t		fdadr[DMA_MAX * 2];

	व्योम __iomem		*video_mem;	/* भव address of frame buffer */
	अचिन्हित दीर्घ		video_mem_phys;	/* physical address of frame buffer */
	माप_प्रकार			video_mem_size;	/* size of the frame buffer */
	u16 *			palette_cpu;	/* भव address of palette memory */
	u_पूर्णांक			palette_size;

	u_पूर्णांक			lccr0;
	u_पूर्णांक			lccr3;
	u_पूर्णांक			lccr4;
	u_पूर्णांक			cmap_inverse:1,
				cmap_अटल:1,
				unused:30;

	u_पूर्णांक			reg_lccr0;
	u_पूर्णांक			reg_lccr1;
	u_पूर्णांक			reg_lccr2;
	u_पूर्णांक			reg_lccr3;
	u_पूर्णांक			reg_lccr4;
	u_पूर्णांक			reg_cmdcr;

	अचिन्हित दीर्घ	hsync_समय;

	अस्थिर u_अक्षर		state;
	अस्थिर u_अक्षर		task_state;
	काष्ठा mutex		ctrlr_lock;
	रुको_queue_head_t	ctrlr_रुको;
	काष्ठा work_काष्ठा	task;

	काष्ठा completion	disable_करोne;

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
	uपूर्णांक16_t		*smart_cmds;
	माप_प्रकार			n_smart_cmds;
	काष्ठा completion	command_करोne;
	काष्ठा completion	refresh_करोne;
	काष्ठा task_काष्ठा	*smart_thपढ़ो;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_PXA_OVERLAY
	काष्ठा pxafb_layer	overlay[2];
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर

	काष्ठा regulator *lcd_supply;
	bool lcd_supply_enabled;

	व्योम (*lcd_घातer)(पूर्णांक, काष्ठा fb_var_screeninfo *);
	व्योम (*backlight_घातer)(पूर्णांक);

	काष्ठा pxafb_mach_info	*inf;
पूर्ण;

#घोषणा TO_INF(ptr,member) container_of(ptr,काष्ठा pxafb_info,member)

/*
 * These are the actions क्रम set_ctrlr_state
 */
#घोषणा C_DISABLE		(0)
#घोषणा C_ENABLE		(1)
#घोषणा C_DISABLE_CLKCHANGE	(2)
#घोषणा C_ENABLE_CLKCHANGE	(3)
#घोषणा C_REENABLE		(4)
#घोषणा C_DISABLE_PM		(5)
#घोषणा C_ENABLE_PM		(6)
#घोषणा C_STARTUP		(7)

#घोषणा PXA_NAME	"PXA"

/*
 * Minimum X and Y resolutions
 */
#घोषणा MIN_XRES	64
#घोषणा MIN_YRES	64

/* maximum X and Y resolutions - note these are limits from the रेजिस्टर
 * bits length instead of the real ones
 */
#घोषणा MAX_XRES	1024
#घोषणा MAX_YRES	1024

#पूर्ण_अगर /* __PXAFB_H__ */
