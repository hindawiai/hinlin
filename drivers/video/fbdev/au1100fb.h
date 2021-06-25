<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Hardware definitions क्रम the Au1100 LCD controller
 *
 * Copyright 2002 MontaVista Software
 * Copyright 2002 Alchemy Semiconductor
 * Author:	Alchemy Semiconductor, MontaVista Software
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _AU1100LCD_H
#घोषणा _AU1100LCD_H

#समावेश <यंत्र/mach-au1x00/au1000.h>

#घोषणा prपूर्णांक_err(f, arg...) prपूर्णांकk(KERN_ERR DRIVER_NAME ": " f "\n", ## arg)
#घोषणा prपूर्णांक_warn(f, arg...) prपूर्णांकk(KERN_WARNING DRIVER_NAME ": " f "\n", ## arg)
#घोषणा prपूर्णांक_info(f, arg...) prपूर्णांकk(KERN_INFO DRIVER_NAME ": " f "\n", ## arg)

#अगर DEBUG
#घोषणा prपूर्णांक_dbg(f, arg...) prपूर्णांकk(__खाता__ ": " f "\n", ## arg)
#अन्यथा
#घोषणा prपूर्णांक_dbg(f, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(__BIG_ENDIAN)
#घोषणा LCD_CONTROL_DEFAULT_PO LCD_CONTROL_PO_11
#अन्यथा
#घोषणा LCD_CONTROL_DEFAULT_PO LCD_CONTROL_PO_00
#पूर्ण_अगर
#घोषणा LCD_CONTROL_DEFAULT_SBPPF LCD_CONTROL_SBPPF_565

/********************************************************************/

/* LCD controller restrictions */
#घोषणा AU1100_LCD_MAX_XRES	800
#घोषणा AU1100_LCD_MAX_YRES	600
#घोषणा AU1100_LCD_MAX_BPP	16
#घोषणा AU1100_LCD_MAX_CLK	48000000
#घोषणा AU1100_LCD_NBR_PALETTE_ENTRIES 256

/* Default number of visible screen buffer to allocate */
#घोषणा AU1100FB_NBR_VIDEO_BUFFERS 4

/********************************************************************/

काष्ठा au1100fb_panel
अणु
	स्थिर अक्षर name[25];		/* Full name <venकरोr>_<model> */

	u32   	control_base;		/* Mode-independent control values */
	u32	clkcontrol_base;	/* Panel pixघड़ी preferences */

	u32	horztiming;
	u32	verttiming;

	u32	xres;		/* Maximum horizontal resolution */
	u32 	yres;		/* Maximum vertical resolution */
	u32 	bpp;		/* Maximum depth supported */
पूर्ण;

काष्ठा au1100fb_regs
अणु
	u32  lcd_control;
	u32  lcd_पूर्णांकstatus;
	u32  lcd_पूर्णांकenable;
	u32  lcd_horztiming;
	u32  lcd_verttiming;
	u32  lcd_clkcontrol;
	u32  lcd_dmaaddr0;
	u32  lcd_dmaaddr1;
	u32  lcd_words;
	u32  lcd_pwmभाग;
	u32  lcd_pwmhi;
	u32  reserved[(0x0400-0x002C)/4];
	u32  lcd_pallettebase[256];
पूर्ण;

काष्ठा au1100fb_device अणु

	काष्ठा fb_info info;			/* FB driver info record */

	काष्ठा au1100fb_panel 	*panel;		/* Panel connected to this device */

	काष्ठा au1100fb_regs* 	regs;		/* Registers memory map */
	माप_प्रकार       		regs_len;
	अचिन्हित पूर्णांक 		regs_phys;

	अचिन्हित अक्षर* 		fb_mem;		/* FrameBuffer memory map */
	माप_प्रकार	      		fb_len;
	dma_addr_t    		fb_phys;
	पूर्णांक			panel_idx;
	काष्ठा clk		*lcdclk;
	काष्ठा device		*dev;
पूर्ण;

/********************************************************************/

#घोषणा LCD_CONTROL                (AU1100_LCD_BASE + 0x0)
  #घोषणा LCD_CONTROL_SBB_BIT      21
  #घोषणा LCD_CONTROL_SBB_MASK     (0x3 << LCD_CONTROL_SBB_BIT)
    #घोषणा LCD_CONTROL_SBB_1        (0 << LCD_CONTROL_SBB_BIT)
    #घोषणा LCD_CONTROL_SBB_2        (1 << LCD_CONTROL_SBB_BIT)
    #घोषणा LCD_CONTROL_SBB_3        (2 << LCD_CONTROL_SBB_BIT)
    #घोषणा LCD_CONTROL_SBB_4        (3 << LCD_CONTROL_SBB_BIT)
  #घोषणा LCD_CONTROL_SBPPF_BIT    18
  #घोषणा LCD_CONTROL_SBPPF_MASK   (0x7 << LCD_CONTROL_SBPPF_BIT)
    #घोषणा LCD_CONTROL_SBPPF_655    (0 << LCD_CONTROL_SBPPF_BIT)
    #घोषणा LCD_CONTROL_SBPPF_565    (1 << LCD_CONTROL_SBPPF_BIT)
    #घोषणा LCD_CONTROL_SBPPF_556    (2 << LCD_CONTROL_SBPPF_BIT)
    #घोषणा LCD_CONTROL_SBPPF_1555   (3 << LCD_CONTROL_SBPPF_BIT)
    #घोषणा LCD_CONTROL_SBPPF_5551   (4 << LCD_CONTROL_SBPPF_BIT)
  #घोषणा LCD_CONTROL_WP           (1<<17)
  #घोषणा LCD_CONTROL_WD           (1<<16)
  #घोषणा LCD_CONTROL_C            (1<<15)
  #घोषणा LCD_CONTROL_SM_BIT       13
  #घोषणा LCD_CONTROL_SM_MASK      (0x3 << LCD_CONTROL_SM_BIT)
    #घोषणा LCD_CONTROL_SM_0         (0 << LCD_CONTROL_SM_BIT)
    #घोषणा LCD_CONTROL_SM_90        (1 << LCD_CONTROL_SM_BIT)
    #घोषणा LCD_CONTROL_SM_180       (2 << LCD_CONTROL_SM_BIT)
    #घोषणा LCD_CONTROL_SM_270       (3 << LCD_CONTROL_SM_BIT)
  #घोषणा LCD_CONTROL_DB           (1<<12)
  #घोषणा LCD_CONTROL_CCO          (1<<11)
  #घोषणा LCD_CONTROL_DP           (1<<10)
  #घोषणा LCD_CONTROL_PO_BIT       8
  #घोषणा LCD_CONTROL_PO_MASK      (0x3 << LCD_CONTROL_PO_BIT)
    #घोषणा LCD_CONTROL_PO_00        (0 << LCD_CONTROL_PO_BIT)
    #घोषणा LCD_CONTROL_PO_01        (1 << LCD_CONTROL_PO_BIT)
    #घोषणा LCD_CONTROL_PO_10        (2 << LCD_CONTROL_PO_BIT)
    #घोषणा LCD_CONTROL_PO_11        (3 << LCD_CONTROL_PO_BIT)
  #घोषणा LCD_CONTROL_MPI          (1<<7)
  #घोषणा LCD_CONTROL_PT           (1<<6)
  #घोषणा LCD_CONTROL_PC           (1<<5)
  #घोषणा LCD_CONTROL_BPP_BIT      1
  #घोषणा LCD_CONTROL_BPP_MASK     (0x7 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_1        (0 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_2        (1 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_4        (2 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_8        (3 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_12       (4 << LCD_CONTROL_BPP_BIT)
    #घोषणा LCD_CONTROL_BPP_16       (5 << LCD_CONTROL_BPP_BIT)
  #घोषणा LCD_CONTROL_GO           (1<<0)

#घोषणा LCD_INTSTATUS              (AU1100_LCD_BASE + 0x4)
#घोषणा LCD_INTENABLE              (AU1100_LCD_BASE + 0x8)
  #घोषणा LCD_INT_SD               (1<<7)
  #घोषणा LCD_INT_OF               (1<<6)
  #घोषणा LCD_INT_UF               (1<<5)
  #घोषणा LCD_INT_SA               (1<<3)
  #घोषणा LCD_INT_SS               (1<<2)
  #घोषणा LCD_INT_S1               (1<<1)
  #घोषणा LCD_INT_S0               (1<<0)

#घोषणा LCD_HORZTIMING             (AU1100_LCD_BASE + 0xC)
  #घोषणा LCD_HORZTIMING_HN2_BIT   24
  #घोषणा LCD_HORZTIMING_HN2_MASK  (0xFF << LCD_HORZTIMING_HN2_BIT)
  #घोषणा LCD_HORZTIMING_HN2_N(N)  ((((N)-1) << LCD_HORZTIMING_HN2_BIT) & LCD_HORZTIMING_HN2_MASK)
  #घोषणा LCD_HORZTIMING_HN1_BIT   16
  #घोषणा LCD_HORZTIMING_HN1_MASK  (0xFF << LCD_HORZTIMING_HN1_BIT)
  #घोषणा LCD_HORZTIMING_HN1_N(N)  ((((N)-1) << LCD_HORZTIMING_HN1_BIT) & LCD_HORZTIMING_HN1_MASK)
  #घोषणा LCD_HORZTIMING_HPW_BIT   10
  #घोषणा LCD_HORZTIMING_HPW_MASK  (0x3F << LCD_HORZTIMING_HPW_BIT)
  #घोषणा LCD_HORZTIMING_HPW_N(N)  ((((N)-1) << LCD_HORZTIMING_HPW_BIT) & LCD_HORZTIMING_HPW_MASK)
  #घोषणा LCD_HORZTIMING_PPL_BIT   0
  #घोषणा LCD_HORZTIMING_PPL_MASK  (0x3FF << LCD_HORZTIMING_PPL_BIT)
  #घोषणा LCD_HORZTIMING_PPL_N(N)  ((((N)-1) << LCD_HORZTIMING_PPL_BIT) & LCD_HORZTIMING_PPL_MASK)

#घोषणा LCD_VERTTIMING             (AU1100_LCD_BASE + 0x10)
  #घोषणा LCD_VERTTIMING_VN2_BIT   24
  #घोषणा LCD_VERTTIMING_VN2_MASK  (0xFF << LCD_VERTTIMING_VN2_BIT)
  #घोषणा LCD_VERTTIMING_VN2_N(N)  ((((N)-1) << LCD_VERTTIMING_VN2_BIT) & LCD_VERTTIMING_VN2_MASK)
  #घोषणा LCD_VERTTIMING_VN1_BIT   16
  #घोषणा LCD_VERTTIMING_VN1_MASK  (0xFF << LCD_VERTTIMING_VN1_BIT)
  #घोषणा LCD_VERTTIMING_VN1_N(N)  ((((N)-1) << LCD_VERTTIMING_VN1_BIT) & LCD_VERTTIMING_VN1_MASK)
  #घोषणा LCD_VERTTIMING_VPW_BIT   10
  #घोषणा LCD_VERTTIMING_VPW_MASK  (0x3F << LCD_VERTTIMING_VPW_BIT)
  #घोषणा LCD_VERTTIMING_VPW_N(N)  ((((N)-1) << LCD_VERTTIMING_VPW_BIT) & LCD_VERTTIMING_VPW_MASK)
  #घोषणा LCD_VERTTIMING_LPP_BIT   0
  #घोषणा LCD_VERTTIMING_LPP_MASK  (0x3FF << LCD_VERTTIMING_LPP_BIT)
  #घोषणा LCD_VERTTIMING_LPP_N(N)  ((((N)-1) << LCD_VERTTIMING_LPP_BIT) & LCD_VERTTIMING_LPP_MASK)

#घोषणा LCD_CLKCONTROL             (AU1100_LCD_BASE + 0x14)
  #घोषणा LCD_CLKCONTROL_IB        (1<<18)
  #घोषणा LCD_CLKCONTROL_IC        (1<<17)
  #घोषणा LCD_CLKCONTROL_IH        (1<<16)
  #घोषणा LCD_CLKCONTROL_IV        (1<<15)
  #घोषणा LCD_CLKCONTROL_BF_BIT    10
  #घोषणा LCD_CLKCONTROL_BF_MASK   (0x1F << LCD_CLKCONTROL_BF_BIT)
  #घोषणा LCD_CLKCONTROL_BF_N(N)   ((((N)-1) << LCD_CLKCONTROL_BF_BIT) & LCD_CLKCONTROL_BF_MASK)
  #घोषणा LCD_CLKCONTROL_PCD_BIT   0
  #घोषणा LCD_CLKCONTROL_PCD_MASK  (0x3FF << LCD_CLKCONTROL_PCD_BIT)
  #घोषणा LCD_CLKCONTROL_PCD_N(N)  (((N) << LCD_CLKCONTROL_PCD_BIT) & LCD_CLKCONTROL_PCD_MASK)

#घोषणा LCD_DMAADDR0               (AU1100_LCD_BASE + 0x18)
#घोषणा LCD_DMAADDR1               (AU1100_LCD_BASE + 0x1C)
  #घोषणा LCD_DMA_SA_BIT           5
  #घोषणा LCD_DMA_SA_MASK          (0x7FFFFFF << LCD_DMA_SA_BIT)
  #घोषणा LCD_DMA_SA_N(N)          ((N) & LCD_DMA_SA_MASK)

#घोषणा LCD_WORDS                  (AU1100_LCD_BASE + 0x20)
  #घोषणा LCD_WRD_WRDS_BIT         0
  #घोषणा LCD_WRD_WRDS_MASK        (0xFFFFFFFF << LCD_WRD_WRDS_BIT)
  #घोषणा LCD_WRD_WRDS_N(N)        ((((N)-1) << LCD_WRD_WRDS_BIT) & LCD_WRD_WRDS_MASK)

#घोषणा LCD_PWMDIV                 (AU1100_LCD_BASE + 0x24)
  #घोषणा LCD_PWMDIV_EN            (1<<12)
  #घोषणा LCD_PWMDIV_PWMDIV_BIT    0
  #घोषणा LCD_PWMDIV_PWMDIV_MASK   (0xFFF << LCD_PWMDIV_PWMDIV_BIT)
  #घोषणा LCD_PWMDIV_PWMDIV_N(N)   ((((N)-1) << LCD_PWMDIV_PWMDIV_BIT) & LCD_PWMDIV_PWMDIV_MASK)

#घोषणा LCD_PWMHI                  (AU1100_LCD_BASE + 0x28)
  #घोषणा LCD_PWMHI_PWMHI1_BIT     12
  #घोषणा LCD_PWMHI_PWMHI1_MASK    (0xFFF << LCD_PWMHI_PWMHI1_BIT)
  #घोषणा LCD_PWMHI_PWMHI1_N(N)    (((N) << LCD_PWMHI_PWMHI1_BIT) & LCD_PWMHI_PWMHI1_MASK)
  #घोषणा LCD_PWMHI_PWMHI0_BIT     0
  #घोषणा LCD_PWMHI_PWMHI0_MASK    (0xFFF << LCD_PWMHI_PWMHI0_BIT)
  #घोषणा LCD_PWMHI_PWMHI0_N(N)    (((N) << LCD_PWMHI_PWMHI0_BIT) & LCD_PWMHI_PWMHI0_MASK)

#घोषणा LCD_PALLETTEBASE                (AU1100_LCD_BASE + 0x400)
  #घोषणा LCD_PALLETTE_MONO_MI_BIT      0
  #घोषणा LCD_PALLETTE_MONO_MI_MASK     (0xF << LCD_PALLETTE_MONO_MI_BIT)
  #घोषणा LCD_PALLETTE_MONO_MI_N(N)     (((N)<< LCD_PALLETTE_MONO_MI_BIT) & LCD_PALLETTE_MONO_MI_MASK)

  #घोषणा LCD_PALLETTE_COLOR_RI_BIT     8
  #घोषणा LCD_PALLETTE_COLOR_RI_MASK    (0xF << LCD_PALLETTE_COLOR_RI_BIT)
  #घोषणा LCD_PALLETTE_COLOR_RI_N(N)    (((N)<< LCD_PALLETTE_COLOR_RI_BIT) & LCD_PALLETTE_COLOR_RI_MASK)
  #घोषणा LCD_PALLETTE_COLOR_GI_BIT     4
  #घोषणा LCD_PALLETTE_COLOR_GI_MASK    (0xF << LCD_PALLETTE_COLOR_GI_BIT)
  #घोषणा LCD_PALLETTE_COLOR_GI_N(N)    (((N)<< LCD_PALLETTE_COLOR_GI_BIT) & LCD_PALLETTE_COLOR_GI_MASK)
  #घोषणा LCD_PALLETTE_COLOR_BI_BIT     0
  #घोषणा LCD_PALLETTE_COLOR_BI_MASK    (0xF << LCD_PALLETTE_COLOR_BI_BIT)
  #घोषणा LCD_PALLETTE_COLOR_BI_N(N)    (((N)<< LCD_PALLETTE_COLOR_BI_BIT) & LCD_PALLETTE_COLOR_BI_MASK)

  #घोषणा LCD_PALLETTE_TFT_DC_BIT       0
  #घोषणा LCD_PALLETTE_TFT_DC_MASK      (0xFFFF << LCD_PALLETTE_TFT_DC_BIT)
  #घोषणा LCD_PALLETTE_TFT_DC_N(N)      (((N)<< LCD_PALLETTE_TFT_DC_BIT) & LCD_PALLETTE_TFT_DC_MASK)

/********************************************************************/

/* List of panels known to work with the AU1100 LCD controller.
 * To add a new panel, enter the same specअगरications as the
 * Generic_TFT one, and MAKE SURE that it करोesn't conflicts
 * with the controller restrictions. Restrictions are:
 *
 * STN color panels: max_bpp <= 12
 * STN mono panels: max_bpp <= 4
 * TFT panels: max_bpp <= 16
 * max_xres <= 800
 * max_yres <= 600
 */
अटल काष्ठा au1100fb_panel known_lcd_panels[] =
अणु
	/* 800x600x16bpp CRT */
	[0] = अणु
		.name = "CRT_800x600_16",
		.xres = 800,
		.yres = 600,
		.bpp = 16,
		.control_base =	0x0004886A |
			LCD_CONTROL_DEFAULT_PO | LCD_CONTROL_DEFAULT_SBPPF |
			LCD_CONTROL_BPP_16 | LCD_CONTROL_SBB_4,
		.clkcontrol_base = 0x00020000,
		.horztiming = 0x005aff1f,
		.verttiming = 0x16000e57,
	पूर्ण,
	/* just the standard LCD */
	[1] = अणु
		.name = "WWPC LCD",
		.xres = 240,
		.yres = 320,
		.bpp = 16,
		.control_base = 0x0006806A,
		.horztiming = 0x0A1010EF,
		.verttiming = 0x0301013F,
		.clkcontrol_base = 0x00018001,
	पूर्ण,
	/* Sharp 320x240 TFT panel */
	[2] = अणु
		.name = "Sharp_LQ038Q5DR01",
		.xres = 320,
		.yres = 240,
		.bpp = 16,
		.control_base =
		( LCD_CONTROL_SBPPF_565
		| LCD_CONTROL_C
		| LCD_CONTROL_SM_0
			| LCD_CONTROL_DEFAULT_PO
		| LCD_CONTROL_PT
		| LCD_CONTROL_PC
		| LCD_CONTROL_BPP_16 ),
		.horztiming =
		( LCD_HORZTIMING_HN2_N(8)
		| LCD_HORZTIMING_HN1_N(60)
		| LCD_HORZTIMING_HPW_N(12)
		| LCD_HORZTIMING_PPL_N(320) ),
		.verttiming =
		( LCD_VERTTIMING_VN2_N(5)
		| LCD_VERTTIMING_VN1_N(17)
		| LCD_VERTTIMING_VPW_N(1)
		| LCD_VERTTIMING_LPP_N(240) ),
		.clkcontrol_base = LCD_CLKCONTROL_PCD_N(1),
	पूर्ण,

	/* Hitachi SP14Q005 and possibly others */
	[3] = अणु
		.name = "Hitachi_SP14Qxxx",
		.xres = 320,
		.yres = 240,
		.bpp = 4,
		.control_base =
			( LCD_CONTROL_C
			| LCD_CONTROL_BPP_4 ),
		.horztiming =
			( LCD_HORZTIMING_HN2_N(1)
			| LCD_HORZTIMING_HN1_N(1)
			| LCD_HORZTIMING_HPW_N(1)
			| LCD_HORZTIMING_PPL_N(320) ),
		.verttiming =
			( LCD_VERTTIMING_VN2_N(1)
			| LCD_VERTTIMING_VN1_N(1)
			| LCD_VERTTIMING_VPW_N(1)
			| LCD_VERTTIMING_LPP_N(240) ),
		.clkcontrol_base = LCD_CLKCONTROL_PCD_N(4),
	पूर्ण,

	/* Generic 640x480 TFT panel */
	[4] = अणु
		.name = "TFT_640x480_16",
		.xres = 640,
		.yres = 480,
		.bpp = 16,
		.control_base = 0x004806a | LCD_CONTROL_DEFAULT_PO,
		.horztiming = 0x3434d67f,
		.verttiming = 0x0e0e39df,
		.clkcontrol_base = LCD_CLKCONTROL_PCD_N(1),
	पूर्ण,

	 /* Pb1100 LCDB 640x480 PrimeView TFT panel */
	[5] = अणु
		.name = "PrimeView_640x480_16",
		.xres = 640,
		.yres = 480,
		.bpp = 16,
		.control_base = 0x0004886a | LCD_CONTROL_DEFAULT_PO,
		.horztiming = 0x0e4bfe7f,
		.verttiming = 0x210805df,
		.clkcontrol_base = 0x00038001,
	पूर्ण,
पूर्ण;

/********************************************************************/

/* Inline helpers */

#घोषणा panel_is_dual(panel)  (panel->control_base & LCD_CONTROL_DP)
#घोषणा panel_is_active(panel)(panel->control_base & LCD_CONTROL_PT)
#घोषणा panel_is_color(panel) (panel->control_base & LCD_CONTROL_PC)
#घोषणा panel_swap_rgb(panel) (panel->control_base & LCD_CONTROL_CCO)

#पूर्ण_अगर /* _AU1100LCD_H */
