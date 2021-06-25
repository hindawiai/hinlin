<शैली गुरु>
/*
 * linux/drivers/video/sa1100fb.h
 *    -- StrongARM 1100 LCD Controller Frame Buffer Device
 *
 *  Copyright (C) 1999 Eric A. Thomas
 *   Based on acornfb.c Copyright (C) Russell King.
 *  
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

काष्ठा gpio_desc;

#घोषणा LCCR0           0x0000          /* LCD Control Reg. 0 */
#घोषणा LCSR            0x0004          /* LCD Status Reg. */
#घोषणा DBAR1           0x0010          /* LCD DMA Base Address Reg. channel 1 */
#घोषणा DCAR1           0x0014          /* LCD DMA Current Address Reg. channel 1 */
#घोषणा DBAR2           0x0018          /* LCD DMA Base Address Reg.  channel 2 */
#घोषणा DCAR2           0x001C          /* LCD DMA Current Address Reg. channel 2 */
#घोषणा LCCR1           0x0020          /* LCD Control Reg. 1 */
#घोषणा LCCR2           0x0024          /* LCD Control Reg. 2 */
#घोषणा LCCR3           0x0028          /* LCD Control Reg. 3 */

/* Shaकरोws क्रम LCD controller रेजिस्टरs */
काष्ठा sa1100fb_lcd_reg अणु
	अचिन्हित दीर्घ lccr0;
	अचिन्हित दीर्घ lccr1;
	अचिन्हित दीर्घ lccr2;
	अचिन्हित दीर्घ lccr3;
पूर्ण;

काष्ठा sa1100fb_info अणु
	काष्ठा fb_info		fb;
	काष्ठा device		*dev;
	स्थिर काष्ठा sa1100fb_rgb *rgb[NR_RGB];
	व्योम __iomem		*base;
	काष्ठा gpio_desc	*shannon_lcden;

	/*
	 * These are the addresses we mapped
	 * the framebuffer memory region to.
	 */
	dma_addr_t		map_dma;
	u_अक्षर *		map_cpu;
	u_पूर्णांक			map_size;

	u_अक्षर *		screen_cpu;
	dma_addr_t		screen_dma;
	u16 *			palette_cpu;
	dma_addr_t		palette_dma;
	u_पूर्णांक			palette_size;

	dma_addr_t		dbar1;
	dma_addr_t		dbar2;

	u_पूर्णांक			reg_lccr0;
	u_पूर्णांक			reg_lccr1;
	u_पूर्णांक			reg_lccr2;
	u_पूर्णांक			reg_lccr3;

	अस्थिर u_अक्षर		state;
	अस्थिर u_अक्षर		task_state;
	काष्ठा mutex		ctrlr_lock;
	रुको_queue_head_t	ctrlr_रुको;
	काष्ठा work_काष्ठा	task;

#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर

	स्थिर काष्ठा sa1100fb_mach_info *inf;
	काष्ठा clk *clk;

	u32 pseuकरो_palette[16];
पूर्ण;

#घोषणा TO_INF(ptr,member)	container_of(ptr,काष्ठा sa1100fb_info,member)

#घोषणा SA1100_PALETTE_MODE_VAL(bpp)    (((bpp) & 0x018) << 9)

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

#घोषणा SA1100_NAME	"SA1100"

/*
 * Minimum X and Y resolutions
 */
#घोषणा MIN_XRES	64
#घोषणा MIN_YRES	64

