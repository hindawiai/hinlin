<शैली गुरु>
/*
 * BRIEF MODULE DESCRIPTION
 *	Au1200 LCD Driver.
 *
 * Copyright 2004-2005 AMD
 * Author: AMD
 *
 * Based on:
 * linux/drivers/video/skeletonfb.c -- Skeleton क्रम a frame buffer device
 *  Created 28 Dec 1997 by Geert Uytterhoeven
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

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1200fb.h>	/* platक्रमm_data */
#समावेश "au1200fb.h"

#घोषणा DRIVER_NAME "au1200fb"
#घोषणा DRIVER_DESC "LCD controller driver for AU1200 processors"

#घोषणा DEBUG 0

#घोषणा prपूर्णांक_err(f, arg...) prपूर्णांकk(KERN_ERR DRIVER_NAME ": " f "\n", ## arg)
#घोषणा prपूर्णांक_warn(f, arg...) prपूर्णांकk(KERN_WARNING DRIVER_NAME ": " f "\n", ## arg)
#घोषणा prपूर्णांक_info(f, arg...) prपूर्णांकk(KERN_INFO DRIVER_NAME ": " f "\n", ## arg)

#अगर DEBUG
#घोषणा prपूर्णांक_dbg(f, arg...) prपूर्णांकk(KERN_DEBUG __खाता__ ": " f "\n", ## arg)
#अन्यथा
#घोषणा prपूर्णांक_dbg(f, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर


#घोषणा AU1200_LCD_FB_IOCTL 0x46FF

#घोषणा AU1200_LCD_SET_SCREEN 1
#घोषणा AU1200_LCD_GET_SCREEN 2
#घोषणा AU1200_LCD_SET_WINDOW 3
#घोषणा AU1200_LCD_GET_WINDOW 4
#घोषणा AU1200_LCD_SET_PANEL  5
#घोषणा AU1200_LCD_GET_PANEL  6

#घोषणा SCREEN_SIZE		    (1<< 1)
#घोषणा SCREEN_BACKCOLOR    (1<< 2)
#घोषणा SCREEN_BRIGHTNESS   (1<< 3)
#घोषणा SCREEN_COLORKEY     (1<< 4)
#घोषणा SCREEN_MASK         (1<< 5)

काष्ठा au1200_lcd_global_regs_t अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक xsize;
	अचिन्हित पूर्णांक ysize;
	अचिन्हित पूर्णांक backcolor;
	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक colorkey;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक panel_choice;
	अक्षर panel_desc[80];

पूर्ण;

#घोषणा WIN_POSITION            (1<< 0)
#घोषणा WIN_ALPHA_COLOR         (1<< 1)
#घोषणा WIN_ALPHA_MODE          (1<< 2)
#घोषणा WIN_PRIORITY            (1<< 3)
#घोषणा WIN_CHANNEL             (1<< 4)
#घोषणा WIN_BUFFER_FORMAT       (1<< 5)
#घोषणा WIN_COLOR_ORDER         (1<< 6)
#घोषणा WIN_PIXEL_ORDER         (1<< 7)
#घोषणा WIN_SIZE                (1<< 8)
#घोषणा WIN_COLORKEY_MODE       (1<< 9)
#घोषणा WIN_DOUBLE_BUFFER_MODE  (1<< 10)
#घोषणा WIN_RAM_ARRAY_MODE      (1<< 11)
#घोषणा WIN_BUFFER_SCALE        (1<< 12)
#घोषणा WIN_ENABLE	            (1<< 13)

काष्ठा au1200_lcd_winकरोw_regs_t अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक xpos;
	अचिन्हित पूर्णांक ypos;
	अचिन्हित पूर्णांक alpha_color;
	अचिन्हित पूर्णांक alpha_mode;
	अचिन्हित पूर्णांक priority;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक buffer_क्रमmat;
	अचिन्हित पूर्णांक color_order;
	अचिन्हित पूर्णांक pixel_order;
	अचिन्हित पूर्णांक xsize;
	अचिन्हित पूर्णांक ysize;
	अचिन्हित पूर्णांक colorkey_mode;
	अचिन्हित पूर्णांक द्विगुन_buffer_mode;
	अचिन्हित पूर्णांक ram_array_mode;
	अचिन्हित पूर्णांक xscale;
	अचिन्हित पूर्णांक yscale;
	अचिन्हित पूर्णांक enable;
पूर्ण;


काष्ठा au1200_lcd_iodata_t अणु
	अचिन्हित पूर्णांक subcmd;
	काष्ठा au1200_lcd_global_regs_t global;
	काष्ठा au1200_lcd_winकरोw_regs_t winकरोw;
पूर्ण;

#अगर defined(__BIG_ENDIAN)
#घोषणा LCD_CONTROL_DEFAULT_PO LCD_CONTROL_PO_11
#अन्यथा
#घोषणा LCD_CONTROL_DEFAULT_PO LCD_CONTROL_PO_00
#पूर्ण_अगर
#घोषणा LCD_CONTROL_DEFAULT_SBPPF LCD_CONTROL_SBPPF_565

/* Private, per-framebuffer management inक्रमmation (independent of the panel itself) */
काष्ठा au1200fb_device अणु
	काष्ठा fb_info *fb_info;		/* FB driver info record */
	काष्ठा au1200fb_platdata *pd;
	काष्ठा device *dev;

	पूर्णांक					plane;
	अचिन्हित अक्षर* 		fb_mem;		/* FrameBuffer memory map */
	अचिन्हित पूर्णांक		fb_len;
	dma_addr_t    		fb_phys;
पूर्ण;

/********************************************************************/

/* LCD controller restrictions */
#घोषणा AU1200_LCD_MAX_XRES	1280
#घोषणा AU1200_LCD_MAX_YRES	1024
#घोषणा AU1200_LCD_MAX_BPP	32
#घोषणा AU1200_LCD_MAX_CLK	96000000 /* fixme: this needs to go away ? */
#घोषणा AU1200_LCD_NBR_PALETTE_ENTRIES 256

/* Default number of visible screen buffer to allocate */
#घोषणा AU1200FB_NBR_VIDEO_BUFFERS 1

/* Default maximum number of fb devices to create */
#घोषणा MAX_DEVICE_COUNT	4

/* Default winकरोw configuration entry to use (see winकरोws[]) */
#घोषणा DEFAULT_WINDOW_INDEX	2

/********************************************************************/

अटल काष्ठा fb_info *_au1200fb_infos[MAX_DEVICE_COUNT];
अटल काष्ठा au1200_lcd *lcd = (काष्ठा au1200_lcd *) AU1200_LCD_ADDR;
अटल पूर्णांक device_count = MAX_DEVICE_COUNT;
अटल पूर्णांक winकरोw_index = DEFAULT_WINDOW_INDEX;	/* शेष is zero */
अटल पूर्णांक panel_index = 2; /* शेष is zero */
अटल काष्ठा winकरोw_settings *win;
अटल काष्ठा panel_settings *panel;
अटल पूर्णांक noblanking = 1;
अटल पूर्णांक nohwcursor = 0;

काष्ठा winकरोw_settings अणु
	अचिन्हित अक्षर name[64];
	uपूर्णांक32 mode_backcolor;
	uपूर्णांक32 mode_colorkey;
	uपूर्णांक32 mode_colorkeymsk;
	काष्ठा अणु
		पूर्णांक xres;
		पूर्णांक yres;
		पूर्णांक xpos;
		पूर्णांक ypos;
		uपूर्णांक32 mode_winctrl1; /* winctrl1[FRM,CCO,PO,PIPE] */
		uपूर्णांक32 mode_winenable;
	पूर्ण w[4];
पूर्ण;

#अगर defined(__BIG_ENDIAN)
#घोषणा LCD_WINCTRL1_PO_16BPP LCD_WINCTRL1_PO_00
#अन्यथा
#घोषणा LCD_WINCTRL1_PO_16BPP LCD_WINCTRL1_PO_01
#पूर्ण_अगर

/*
 * Default winकरोw configurations
 */
अटल काष्ठा winकरोw_settings winकरोws[] = अणु
	अणु /* Index 0 */
		"0-FS gfx, 1-video, 2-ovly gfx, 3-ovly gfx",
		/* mode_backcolor	*/ 0x006600ff,
		/* mode_colorkey,msk*/ 0, 0,
		अणु
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP,
			/* mode_winenable*/ LCD_WINENABLE_WEN0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 100, 100, 100, 100,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP |
				LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ LCD_WINENABLE_WEN1,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP,
			/* mode_winenable*/ 0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP |
				LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ 0,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	अणु /* Index 1 */
		"0-FS gfx, 1-video, 2-ovly gfx, 3-ovly gfx",
		/* mode_backcolor	*/ 0x006600ff,
		/* mode_colorkey,msk*/ 0, 0,
		अणु
			अणु
			/* xres, yres, xpos, ypos */ 320, 240, 5, 5,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_24BPP |
				LCD_WINCTRL1_PO_00,
			/* mode_winenable*/ LCD_WINENABLE_WEN0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565
				| LCD_WINCTRL1_PO_16BPP,
			/* mode_winenable*/ 0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 100, 100, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP |
				LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ 0/*LCD_WINENABLE_WEN2*/,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 200, 25, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP |
				LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ 0,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु /* Index 2 */
		"0-FS gfx, 1-video, 2-ovly gfx, 3-ovly gfx",
		/* mode_backcolor	*/ 0x006600ff,
		/* mode_colorkey,msk*/ 0, 0,
		अणु
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP,
			/* mode_winenable*/ LCD_WINENABLE_WEN0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP,
			/* mode_winenable*/ 0,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_32BPP |
				LCD_WINCTRL1_PO_00|LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ 0/*LCD_WINENABLE_WEN2*/,
			पूर्ण,
			अणु
			/* xres, yres, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctrl1 */ LCD_WINCTRL1_FRM_16BPP565 |
				LCD_WINCTRL1_PO_16BPP |
				LCD_WINCTRL1_PIPE,
			/* mode_winenable*/ 0,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	/* Need VGA 640 @ 24bpp, @ 32bpp */
	/* Need VGA 800 @ 24bpp, @ 32bpp */
	/* Need VGA 1024 @ 24bpp, @ 32bpp */
पूर्ण;

/*
 * Controller configurations क्रम various panels.
 */

काष्ठा panel_settings
अणु
	स्थिर अक्षर name[25];		/* Full name <venकरोr>_<model> */

	काष्ठा 	fb_monspecs monspecs; 	/* FB monitor specs */

	/* panel timings */
	uपूर्णांक32 mode_screen;
	uपूर्णांक32 mode_horztiming;
	uपूर्णांक32 mode_verttiming;
	uपूर्णांक32 mode_clkcontrol;
	uपूर्णांक32 mode_pwmभाग;
	uपूर्णांक32 mode_pwmhi;
	uपूर्णांक32 mode_ouपंचांगask;
	uपूर्णांक32 mode_fअगरoctrl;
	uपूर्णांक32 mode_backlight;
	uपूर्णांक32 lcdclk;
#घोषणा Xres min_xres
#घोषणा Yres min_yres
	u32	min_xres;		/* Minimum horizontal resolution */
	u32	max_xres;		/* Maximum horizontal resolution */
	u32 	min_yres;		/* Minimum vertical resolution */
	u32 	max_yres;		/* Maximum vertical resolution */
पूर्ण;

/********************************************************************/
/* fixme: Maybe a modedb क्रम the CRT ? otherwise panels should be as-is */

/* List of panels known to work with the AU1200 LCD controller.
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
अटल काष्ठा panel_settings known_lcd_panels[] =
अणु
	[0] = अणु /* QVGA 320x240 H:33.3kHz V:110Hz */
		.name = "QVGA_320x240",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= LCD_SCREEN_SX_N(320) |
			LCD_SCREEN_SY_N(240),
		.mode_horztiming	= 0x00c4623b,
		.mode_verttiming	= 0x00502814,
		.mode_clkcontrol	= 0x00020002, /* /4=24Mhz */
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		320, 320,
		240, 240,
	पूर्ण,

	[1] = अणु /* VGA 640x480 H:30.3kHz V:58Hz */
		.name = "VGA_640x480",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= 0x13f9df80,
		.mode_horztiming	= 0x003c5859,
		.mode_verttiming	= 0x00741201,
		.mode_clkcontrol	= 0x00020001, /* /4=24Mhz */
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		640, 480,
		640, 480,
	पूर्ण,

	[2] = अणु /* SVGA 800x600 H:46.1kHz V:69Hz */
		.name = "SVGA_800x600",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= 0x18fa5780,
		.mode_horztiming	= 0x00dc7e77,
		.mode_verttiming	= 0x00584805,
		.mode_clkcontrol	= 0x00020000, /* /2=48Mhz */
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		800, 800,
		600, 600,
	पूर्ण,

	[3] = अणु /* XVGA 1024x768 H:56.2kHz V:70Hz */
		.name = "XVGA_1024x768",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= 0x1ffaff80,
		.mode_horztiming	= 0x007d0e57,
		.mode_verttiming	= 0x00740a01,
		.mode_clkcontrol	= 0x000A0000, /* /1 */
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 72,
		1024, 1024,
		768, 768,
	पूर्ण,

	[4] = अणु /* XVGA XVGA 1280x1024 H:68.5kHz V:65Hz */
		.name = "XVGA_1280x1024",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= 0x27fbff80,
		.mode_horztiming	= 0x00cdb2c7,
		.mode_verttiming	= 0x00600002,
		.mode_clkcontrol	= 0x000A0000, /* /1 */
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 120,
		1280, 1280,
		1024, 1024,
	पूर्ण,

	[5] = अणु /* Samsung 1024x768 TFT */
		.name = "Samsung_1024x768_TFT",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= 0x1ffaff80,
		.mode_horztiming	= 0x018cc677,
		.mode_verttiming	= 0x00241217,
		.mode_clkcontrol	= 0x00000000, /* SCB 0x1 /4=24Mhz */
		.mode_pwmभाग		= 0x8000063f, /* SCB 0x0 */
		.mode_pwmhi		= 0x03400000, /* SCB 0x0 */
		.mode_ouपंचांगask	= 0x00FFFFFF,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		1024, 1024,
		768, 768,
	पूर्ण,

	[6] = अणु /* Toshiba 640x480 TFT */
		.name = "Toshiba_640x480_TFT",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= LCD_SCREEN_SX_N(640) |
			LCD_SCREEN_SY_N(480),
		.mode_horztiming	= LCD_HORZTIMING_HPW_N(96) |
			LCD_HORZTIMING_HND1_N(13) | LCD_HORZTIMING_HND2_N(51),
		.mode_verttiming	= LCD_VERTTIMING_VPW_N(2) |
			LCD_VERTTIMING_VND1_N(11) | LCD_VERTTIMING_VND2_N(32),
		.mode_clkcontrol	= 0x00000000, /* /4=24Mhz */
		.mode_pwmभाग		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_ouपंचांगask	= 0x00fcfcfc,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		640, 480,
		640, 480,
	पूर्ण,

	[7] = अणु /* Sharp 320x240 TFT */
		.name = "Sharp_320x240_TFT",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 12500,
			.hfmax = 20000,
			.vfmin = 38,
			.vfmax = 81,
			.dclkmin = 4500000,
			.dclkmax = 6800000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= LCD_SCREEN_SX_N(320) |
			LCD_SCREEN_SY_N(240),
		.mode_horztiming	= LCD_HORZTIMING_HPW_N(60) |
			LCD_HORZTIMING_HND1_N(13) | LCD_HORZTIMING_HND2_N(2),
		.mode_verttiming	= LCD_VERTTIMING_VPW_N(2) |
			LCD_VERTTIMING_VND1_N(2) | LCD_VERTTIMING_VND2_N(5),
		.mode_clkcontrol	= LCD_CLKCONTROL_PCD_N(7), /*16=6Mhz*/
		.mode_pwmभाग		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_ouपंचांगask	= 0x00fcfcfc,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96, /* 96MHz AUXPLL */
		320, 320,
		240, 240,
	पूर्ण,

	[8] = अणु /* Toppoly TD070WGCB2 7" 856x480 TFT */
		.name = "Toppoly_TD070WGCB2",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= LCD_SCREEN_SX_N(856) |
			LCD_SCREEN_SY_N(480),
		.mode_horztiming	= LCD_HORZTIMING_HND2_N(43) |
			LCD_HORZTIMING_HND1_N(43) | LCD_HORZTIMING_HPW_N(114),
		.mode_verttiming	= LCD_VERTTIMING_VND2_N(20) |
			LCD_VERTTIMING_VND1_N(21) | LCD_VERTTIMING_VPW_N(4),
		.mode_clkcontrol	= 0x00020001, /* /4=24Mhz */
		.mode_pwmभाग		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_ouपंचांगask	= 0x00fcfcfc,
		.mode_fअगरoctrl	= 0x2f2f2f2f,
		.mode_backlight	= 0x00000000,
		.lcdclk		= 96,
		856, 856,
		480, 480,
	पूर्ण,
	[9] = अणु
		.name = "DB1300_800x480",
		.monspecs = अणु
			.modedb = शून्य,
			.modedb_len = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dclkmin = 6000000,
			.dclkmax = 28000000,
			.input = FB_DISP_RGB,
		पूर्ण,
		.mode_screen		= LCD_SCREEN_SX_N(800) |
					  LCD_SCREEN_SY_N(480),
		.mode_horztiming	= LCD_HORZTIMING_HPW_N(5) |
					  LCD_HORZTIMING_HND1_N(16) |
					  LCD_HORZTIMING_HND2_N(8),
		.mode_verttiming	= LCD_VERTTIMING_VPW_N(4) |
					  LCD_VERTTIMING_VND1_N(8) |
					  LCD_VERTTIMING_VND2_N(5),
		.mode_clkcontrol	= LCD_CLKCONTROL_PCD_N(1) |
					  LCD_CLKCONTROL_IV |
					  LCD_CLKCONTROL_IH,
		.mode_pwmभाग		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_ouपंचांगask		= 0x00FFFFFF,
		.mode_fअगरoctrl		= 0x2f2f2f2f,
		.mode_backlight		= 0x00000000,
		.lcdclk			= 96,
		800, 800,
		480, 480,
	पूर्ण,
पूर्ण;

#घोषणा NUM_PANELS (ARRAY_SIZE(known_lcd_panels))

/********************************************************************/

अटल पूर्णांक winbpp (अचिन्हित पूर्णांक winctrl1)
अणु
	पूर्णांक bits = 0;

	/* how many bits are needed क्रम each pixel क्रमmat */
	चयन (winctrl1 & LCD_WINCTRL1_FRM) अणु
	हाल LCD_WINCTRL1_FRM_1BPP:
		bits = 1;
		अवरोध;
	हाल LCD_WINCTRL1_FRM_2BPP:
		bits = 2;
		अवरोध;
	हाल LCD_WINCTRL1_FRM_4BPP:
		bits = 4;
		अवरोध;
	हाल LCD_WINCTRL1_FRM_8BPP:
		bits = 8;
		अवरोध;
	हाल LCD_WINCTRL1_FRM_12BPP:
	हाल LCD_WINCTRL1_FRM_16BPP655:
	हाल LCD_WINCTRL1_FRM_16BPP565:
	हाल LCD_WINCTRL1_FRM_16BPP556:
	हाल LCD_WINCTRL1_FRM_16BPPI1555:
	हाल LCD_WINCTRL1_FRM_16BPPI5551:
	हाल LCD_WINCTRL1_FRM_16BPPA1555:
	हाल LCD_WINCTRL1_FRM_16BPPA5551:
		bits = 16;
		अवरोध;
	हाल LCD_WINCTRL1_FRM_24BPP:
	हाल LCD_WINCTRL1_FRM_32BPP:
		bits = 32;
		अवरोध;
	पूर्ण

	वापस bits;
पूर्ण

अटल पूर्णांक fbinfo2index (काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < device_count; ++i) अणु
		अगर (fb_info == _au1200fb_infos[i])
			वापस i;
	पूर्ण
	prपूर्णांकk("au1200fb: ERROR: fbinfo2index failed!\n");
	वापस -1;
पूर्ण

अटल पूर्णांक au1200_setlocation (काष्ठा au1200fb_device *fbdev, पूर्णांक plane,
	पूर्णांक xpos, पूर्णांक ypos)
अणु
	uपूर्णांक32 winctrl0, winctrl1, winenable, fb_offset = 0;
	पूर्णांक xsz, ysz;

	/* FIX!!! NOT CHECKING FOR COMPLETE OFFSCREEN YET */

	winctrl0 = lcd->winकरोw[plane].winctrl0;
	winctrl1 = lcd->winकरोw[plane].winctrl1;
	winctrl0 &= (LCD_WINCTRL0_A | LCD_WINCTRL0_AEN);
	winctrl1 &= ~(LCD_WINCTRL1_SZX | LCD_WINCTRL1_SZY);

	/* Check क्रम off-screen adjusपंचांगents */
	xsz = win->w[plane].xres;
	ysz = win->w[plane].yres;
	अगर ((xpos + win->w[plane].xres) > panel->Xres) अणु
		/* Off-screen to the right */
		xsz = panel->Xres - xpos; /* off by 1 ??? */
		/*prपूर्णांकk("off screen right\n");*/
	पूर्ण

	अगर ((ypos + win->w[plane].yres) > panel->Yres) अणु
		/* Off-screen to the bottom */
		ysz = panel->Yres - ypos; /* off by 1 ??? */
		/*prपूर्णांकk("off screen bottom\n");*/
	पूर्ण

	अगर (xpos < 0) अणु
		/* Off-screen to the left */
		xsz = win->w[plane].xres + xpos;
		fb_offset += (((0 - xpos) * winbpp(lcd->winकरोw[plane].winctrl1))/8);
		xpos = 0;
		/*prपूर्णांकk("off screen left\n");*/
	पूर्ण

	अगर (ypos < 0) अणु
		/* Off-screen to the top */
		ysz = win->w[plane].yres + ypos;
		/* fixme: fb_offset += ((0-ypos)*fb_pars[plane].line_length); */
		ypos = 0;
		/*prपूर्णांकk("off screen top\n");*/
	पूर्ण

	/* record settings */
	win->w[plane].xpos = xpos;
	win->w[plane].ypos = ypos;

	xsz -= 1;
	ysz -= 1;
	winctrl0 |= (xpos << 21);
	winctrl0 |= (ypos << 10);
	winctrl1 |= (xsz << 11);
	winctrl1 |= (ysz << 0);

	/* Disable the winकरोw जबतक making changes, then restore WINEN */
	winenable = lcd->winenable & (1 << plane);
	wmb(); /* drain ग_लिखोbuffer */
	lcd->winenable &= ~(1 << plane);
	lcd->winकरोw[plane].winctrl0 = winctrl0;
	lcd->winकरोw[plane].winctrl1 = winctrl1;
	lcd->winकरोw[plane].winbuf0 =
	lcd->winकरोw[plane].winbuf1 = fbdev->fb_phys;
	lcd->winकरोw[plane].winbufctrl = 0; /* select winbuf0 */
	lcd->winenable |= winenable;
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल व्योम au1200_setpanel(काष्ठा panel_settings *newpanel,
			    काष्ठा au1200fb_platdata *pd)
अणु
	/*
	 * Perक्रमm global setup/init of LCD controller
	 */
	uपूर्णांक32 winenable;

	/* Make sure all winकरोws disabled */
	winenable = lcd->winenable;
	lcd->winenable = 0;
	wmb(); /* drain ग_लिखोbuffer */
	/*
	 * Ensure everything is disabled beक्रमe reconfiguring
	 */
	अगर (lcd->screen & LCD_SCREEN_SEN) अणु
		/* Wait क्रम vertical sync period */
		lcd->पूर्णांकstatus = LCD_INT_SS;
		जबतक ((lcd->पूर्णांकstatus & LCD_INT_SS) == 0)
			;

		lcd->screen &= ~LCD_SCREEN_SEN;	/*disable the controller*/

		करो अणु
			lcd->पूर्णांकstatus = lcd->पूर्णांकstatus; /*clear पूर्णांकerrupts*/
			wmb(); /* drain ग_लिखोbuffer */
		/*रुको क्रम controller to shut करोwn*/
		पूर्ण जबतक ((lcd->पूर्णांकstatus & LCD_INT_SD) == 0);

		/* Call shutकरोwn of current panel (अगर up) */
		/* this must occur last, because अगर an बाह्यal घड़ी is driving
		    the controller, the घड़ी cannot be turned off beक्रमe first
			shutting करोwn the controller.
		 */
		अगर (pd->panel_shutकरोwn)
			pd->panel_shutकरोwn();
	पूर्ण

	/* Newpanel == शून्य indicates a shutकरोwn operation only */
	अगर (newpanel == शून्य)
		वापस;

	panel = newpanel;

	prपूर्णांकk("Panel(%s), %dx%d\n", panel->name, panel->Xres, panel->Yres);

	/*
	 * Setup घड़ीing अगर पूर्णांकernal LCD घड़ी source (assumes sys_auxpll valid)
	 */
	अगर (!(panel->mode_clkcontrol & LCD_CLKCONTROL_EXT))
	अणु
		काष्ठा clk *c = clk_get(शून्य, "lcd_intclk");
		दीर्घ r, pc = panel->lcdclk * 1000000;

		अगर (!IS_ERR(c)) अणु
			r = clk_round_rate(c, pc);
			अगर ((pc - r) < (pc / 10)) अणु	/* 10% slack */
				clk_set_rate(c, r);
				clk_prepare_enable(c);
			पूर्ण
			clk_put(c);
		पूर्ण
	पूर्ण

	/*
	 * Configure panel timings
	 */
	lcd->screen = panel->mode_screen;
	lcd->horztiming = panel->mode_horztiming;
	lcd->verttiming = panel->mode_verttiming;
	lcd->clkcontrol = panel->mode_clkcontrol;
	lcd->pwmभाग = panel->mode_pwmभाग;
	lcd->pwmhi = panel->mode_pwmhi;
	lcd->ouपंचांगask = panel->mode_ouपंचांगask;
	lcd->fअगरoctrl = panel->mode_fअगरoctrl;
	wmb(); /* drain ग_लिखोbuffer */

	/* fixme: Check winकरोw settings to make sure still valid
	 * क्रम new geometry */
#अगर 0
	au1200_setlocation(fbdev, 0, win->w[0].xpos, win->w[0].ypos);
	au1200_setlocation(fbdev, 1, win->w[1].xpos, win->w[1].ypos);
	au1200_setlocation(fbdev, 2, win->w[2].xpos, win->w[2].ypos);
	au1200_setlocation(fbdev, 3, win->w[3].xpos, win->w[3].ypos);
#पूर्ण_अगर
	lcd->winenable = winenable;

	/*
	 * Re-enable screen now that it is configured
	 */
	lcd->screen |= LCD_SCREEN_SEN;
	wmb(); /* drain ग_लिखोbuffer */

	/* Call init of panel */
	अगर (pd->panel_init)
		pd->panel_init();

	/* FIX!!!! not appropriate on panel change!!! Global setup/init */
	lcd->पूर्णांकenable = 0;
	lcd->पूर्णांकstatus = ~0;
	lcd->backcolor = win->mode_backcolor;

	/* Setup Color Key - FIX!!! */
	lcd->colorkey = win->mode_colorkey;
	lcd->colorkeymsk = win->mode_colorkeymsk;

	/* Setup HWCursor - FIX!!! Need to support this eventually */
	lcd->hwc.cursorctrl = 0;
	lcd->hwc.cursorpos = 0;
	lcd->hwc.cursorcolor0 = 0;
	lcd->hwc.cursorcolor1 = 0;
	lcd->hwc.cursorcolor2 = 0;
	lcd->hwc.cursorcolor3 = 0;


#अगर 0
#घोषणा D(X) prपूर्णांकk("%25s: %08X\n", #X, X)
	D(lcd->screen);
	D(lcd->horztiming);
	D(lcd->verttiming);
	D(lcd->clkcontrol);
	D(lcd->pwmभाग);
	D(lcd->pwmhi);
	D(lcd->ouपंचांगask);
	D(lcd->fअगरoctrl);
	D(lcd->winकरोw[0].winctrl0);
	D(lcd->winकरोw[0].winctrl1);
	D(lcd->winकरोw[0].winctrl2);
	D(lcd->winकरोw[0].winbuf0);
	D(lcd->winकरोw[0].winbuf1);
	D(lcd->winकरोw[0].winbufctrl);
	D(lcd->winकरोw[1].winctrl0);
	D(lcd->winकरोw[1].winctrl1);
	D(lcd->winकरोw[1].winctrl2);
	D(lcd->winकरोw[1].winbuf0);
	D(lcd->winकरोw[1].winbuf1);
	D(lcd->winकरोw[1].winbufctrl);
	D(lcd->winकरोw[2].winctrl0);
	D(lcd->winकरोw[2].winctrl1);
	D(lcd->winकरोw[2].winctrl2);
	D(lcd->winकरोw[2].winbuf0);
	D(lcd->winकरोw[2].winbuf1);
	D(lcd->winकरोw[2].winbufctrl);
	D(lcd->winकरोw[3].winctrl0);
	D(lcd->winकरोw[3].winctrl1);
	D(lcd->winकरोw[3].winctrl2);
	D(lcd->winकरोw[3].winbuf0);
	D(lcd->winकरोw[3].winbuf1);
	D(lcd->winकरोw[3].winbufctrl);
	D(lcd->winenable);
	D(lcd->पूर्णांकenable);
	D(lcd->पूर्णांकstatus);
	D(lcd->backcolor);
	D(lcd->winenable);
	D(lcd->colorkey);
    D(lcd->colorkeymsk);
	D(lcd->hwc.cursorctrl);
	D(lcd->hwc.cursorpos);
	D(lcd->hwc.cursorcolor0);
	D(lcd->hwc.cursorcolor1);
	D(lcd->hwc.cursorcolor2);
	D(lcd->hwc.cursorcolor3);
#पूर्ण_अगर
पूर्ण

अटल व्योम au1200_seपंचांगode(काष्ठा au1200fb_device *fbdev)
अणु
	पूर्णांक plane = fbdev->plane;
	/* Winकरोw/plane setup */
	lcd->winकरोw[plane].winctrl1 = ( 0
		| LCD_WINCTRL1_PRI_N(plane)
		| win->w[plane].mode_winctrl1 /* FRM,CCO,PO,PIPE */
		) ;

	au1200_setlocation(fbdev, plane, win->w[plane].xpos, win->w[plane].ypos);

	lcd->winकरोw[plane].winctrl2 = ( 0
		| LCD_WINCTRL2_CKMODE_00
		| LCD_WINCTRL2_DBM
		| LCD_WINCTRL2_BX_N(fbdev->fb_info->fix.line_length)
		| LCD_WINCTRL2_SCX_1
		| LCD_WINCTRL2_SCY_1
		) ;
	lcd->winenable |= win->w[plane].mode_winenable;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण


/* Inline helpers */

/*#घोषणा panel_is_dual(panel)  ((panel->mode_screen & LCD_SCREEN_PT) == LCD_SCREEN_PT_010)*/
/*#घोषणा panel_is_active(panel)((panel->mode_screen & LCD_SCREEN_PT) == LCD_SCREEN_PT_010)*/

#घोषणा panel_is_color(panel) ((panel->mode_screen & LCD_SCREEN_PT) <= LCD_SCREEN_PT_CDSTN)

/* Bitfields क्रमmat supported by the controller. */
अटल काष्ठा fb_bitfield rgb_bitfields[][4] = अणु
  	/*     Red, 	   Green, 	 Blue, 	     Transp   */
	[LCD_WINCTRL1_FRM_16BPP655 >> 25] =
		अणु अणु 10, 6, 0 पूर्ण, अणु 5, 5, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPP565 >> 25] =
		अणु अणु 11, 5, 0 पूर्ण, अणु 5, 6, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPP556 >> 25] =
		अणु अणु 11, 5, 0 पूर्ण, अणु 6, 5, 0 पूर्ण, अणु 0, 6, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPPI1555 >> 25] =
		अणु अणु 10, 5, 0 पूर्ण, अणु 5, 5, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPPI5551 >> 25] =
		अणु अणु 11, 5, 0 पूर्ण, अणु 6, 5, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPPA1555 >> 25] =
		अणु अणु 10, 5, 0 पूर्ण, अणु 5, 5, 0 पूर्ण, अणु 0, 5, 0 पूर्ण, अणु 15, 1, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_16BPPA5551 >> 25] =
		अणु अणु 11, 5, 0 पूर्ण, अणु 6, 5, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 0, 1, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_24BPP >> 25] =
		अणु अणु 16, 8, 0 पूर्ण, अणु 8, 8, 0 पूर्ण, अणु 0, 8, 0 पूर्ण, अणु 0, 0, 0 पूर्ण पूर्ण,

	[LCD_WINCTRL1_FRM_32BPP >> 25] =
		अणु अणु 16, 8, 0 पूर्ण, अणु 8, 8, 0 पूर्ण, अणु 0, 8, 0 पूर्ण, अणु 24, 0, 0 पूर्ण पूर्ण,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Helpers */

अटल व्योम au1200fb_update_fbinfo(काष्ठा fb_info *fbi)
अणु
	/* FIX!!!! This also needs to take the winकरोw pixel क्रमmat पूर्णांकo account!!! */

	/* Update var-dependent FB info */
	अगर (panel_is_color(panel)) अणु
		अगर (fbi->var.bits_per_pixel <= 8) अणु
			/* palettized */
			fbi->fix.visual = FB_VISUAL_PSEUDOCOLOR;
			fbi->fix.line_length = fbi->var.xres_भव /
				(8/fbi->var.bits_per_pixel);
		पूर्ण अन्यथा अणु
			/* non-palettized */
			fbi->fix.visual = FB_VISUAL_TRUECOLOR;
			fbi->fix.line_length = fbi->var.xres_भव * (fbi->var.bits_per_pixel / 8);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* mono FIX!!! mono 8 and 4 bits */
		fbi->fix.visual = FB_VISUAL_MONO10;
		fbi->fix.line_length = fbi->var.xres_भव / 8;
	पूर्ण

	fbi->screen_size = fbi->fix.line_length * fbi->var.yres_भव;
	prपूर्णांक_dbg("line length: %d\n", fbi->fix.line_length);
	prपूर्णांक_dbg("bits_per_pixel: %d\n", fbi->var.bits_per_pixel);
पूर्ण

/*-------------------------------------------------------------------------*/

/* AU1200 framebuffer driver */

/* fb_check_var
 * Validate var settings with hardware restrictions and modअगरy it अगर necessary
 */
अटल पूर्णांक au1200fb_fb_check_var(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_info *fbi)
अणु
	काष्ठा au1200fb_device *fbdev = fbi->par;
	u32 pixघड़ी;
	पूर्णांक screen_size, plane;

	plane = fbdev->plane;

	/* Make sure that the mode respect all LCD controller and
	 * panel restrictions. */
	var->xres = win->w[plane].xres;
	var->yres = win->w[plane].yres;

	/* No need क्रम भव resolution support */
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;

	var->bits_per_pixel = winbpp(win->w[plane].mode_winctrl1);

	screen_size = var->xres_भव * var->yres_भव;
	अगर (var->bits_per_pixel > 8) screen_size *= (var->bits_per_pixel / 8);
	अन्यथा screen_size /= (8/var->bits_per_pixel);

	अगर (fbdev->fb_len < screen_size)
		वापस -EINVAL; /* Virtual screen is to big, पात */

	/* FIX!!!! what are the implicaitons of ignoring this क्रम winकरोws ??? */
	/* The max LCD घड़ी is fixed to 48MHz (value of AUX_CLK). The pixel
	 * घड़ी can only be obtain by भागiding this value by an even पूर्णांकeger.
	 * Fallback to a slower pixel घड़ी अगर necessary. */
	pixघड़ी = max((u32)(PICOS2KHZ(var->pixघड़ी) * 1000), fbi->monspecs.dclkmin);
	pixघड़ी = min3(pixघड़ी, fbi->monspecs.dclkmax, (u32)AU1200_LCD_MAX_CLK/2);

	अगर (AU1200_LCD_MAX_CLK % pixघड़ी) अणु
		पूर्णांक dअगरf = AU1200_LCD_MAX_CLK % pixघड़ी;
		pixघड़ी -= dअगरf;
	पूर्ण

	var->pixघड़ी = KHZ2PICOS(pixघड़ी/1000);
#अगर 0
	अगर (!panel_is_active(panel)) अणु
		पूर्णांक pcd = AU1200_LCD_MAX_CLK / (pixघड़ी * 2) - 1;

		अगर (!panel_is_color(panel)
			&& (panel->control_base & LCD_CONTROL_MPI) && (pcd < 3)) अणु
			/* STN 8bit mono panel support is up to 6MHz pixघड़ी */
			var->pixघड़ी = KHZ2PICOS(6000);
		पूर्ण अन्यथा अगर (!pcd) अणु
			/* Other STN panel support is up to 12MHz  */
			var->pixघड़ी = KHZ2PICOS(12000);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Set bitfield accordingly */
	चयन (var->bits_per_pixel) अणु
		हाल 16:
		अणु
			/* 16bpp True color.
			 * These must be set to MATCH WINCTRL[FORM] */
			पूर्णांक idx;
			idx = (win->w[0].mode_winctrl1 & LCD_WINCTRL1_FRM) >> 25;
			var->red    = rgb_bitfields[idx][0];
			var->green  = rgb_bitfields[idx][1];
			var->blue   = rgb_bitfields[idx][2];
			var->transp = rgb_bitfields[idx][3];
			अवरोध;
		पूर्ण

		हाल 32:
		अणु
			/* 32bpp True color.
			 * These must be set to MATCH WINCTRL[FORM] */
			पूर्णांक idx;
			idx = (win->w[0].mode_winctrl1 & LCD_WINCTRL1_FRM) >> 25;
			var->red    = rgb_bitfields[idx][0];
			var->green  = rgb_bitfields[idx][1];
			var->blue   = rgb_bitfields[idx][2];
			var->transp = rgb_bitfields[idx][3];
			अवरोध;
		पूर्ण
		शेष:
			prपूर्णांक_dbg("Unsupported depth %dbpp", var->bits_per_pixel);
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* fb_set_par
 * Set hardware with var settings. This will enable the controller with a
 * specअगरic mode, normally validated with the fb_check_var method
 */
अटल पूर्णांक au1200fb_fb_set_par(काष्ठा fb_info *fbi)
अणु
	काष्ठा au1200fb_device *fbdev = fbi->par;

	au1200fb_update_fbinfo(fbi);
	au1200_seपंचांगode(fbdev);

	वापस 0;
पूर्ण

/* fb_setcolreg
 * Set color in LCD palette.
 */
अटल पूर्णांक au1200fb_fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
	अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *fbi)
अणु
	अस्थिर u32 *palette = lcd->palette;
	u32 value;

	अगर (regno > (AU1200_LCD_NBR_PALETTE_ENTRIES - 1))
		वापस -EINVAL;

	अगर (fbi->var.grayscale) अणु
		/* Convert color to grayscale */
		red = green = blue =
			(19595 * red + 38470 * green + 7471 * blue) >> 16;
	पूर्ण

	अगर (fbi->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		/* Place color in the pseuकरोpalette */
		अगर (regno > 16)
			वापस -EINVAL;

		palette = (u32*) fbi->pseuकरो_palette;

		red   >>= (16 - fbi->var.red.length);
		green >>= (16 - fbi->var.green.length);
		blue  >>= (16 - fbi->var.blue.length);

		value = (red   << fbi->var.red.offset) 	|
			(green << fbi->var.green.offset)|
			(blue  << fbi->var.blue.offset);
		value &= 0xFFFF;

	पूर्ण अन्यथा अगर (1 /*FIX!!! panel_is_active(fbdev->panel)*/) अणु
		/* COLOR TFT PALLETTIZED (use RGB 565) */
		value = (red & 0xF800)|((green >> 5) &
				0x07E0)|((blue >> 11) & 0x001F);
		value &= 0xFFFF;

	पूर्ण अन्यथा अगर (0 /*panel_is_color(fbdev->panel)*/) अणु
		/* COLOR STN MODE */
		value = 0x1234;
		value &= 0xFFF;
	पूर्ण अन्यथा अणु
		/* MONOCHROME MODE */
		value = (green >> 12) & 0x000F;
		value &= 0xF;
	पूर्ण

	palette[regno] = value;

	वापस 0;
पूर्ण

/* fb_blank
 * Blank the screen. Depending on the mode, the screen will be
 * activated with the backlight color, or desactivated
 */
अटल पूर्णांक au1200fb_fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *fbi)
अणु
	काष्ठा au1200fb_device *fbdev = fbi->par;

	/* Short-circuit screen blanking */
	अगर (noblanking)
		वापस 0;

	चयन (blank_mode) अणु

	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		/* prपूर्णांकk("turn on panel\n"); */
		au1200_setpanel(panel, fbdev->pd);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		/* prपूर्णांकk("turn off panel\n"); */
		au1200_setpanel(शून्य, fbdev->pd);
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	/* FB_BLANK_NORMAL is a soft blank */
	वापस (blank_mode == FB_BLANK_NORMAL) ? -EINVAL : 0;
पूर्ण

/* fb_mmap
 * Map video memory in user space. We करोn't use the generic fb_mmap
 * method मुख्यly to allow the use of the TLB streaming flag (CCA=6)
 */
अटल पूर्णांक au1200fb_fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा au1200fb_device *fbdev = info->par;

	वापस dma_mmap_attrs(fbdev->dev, vma, fbdev->fb_mem, fbdev->fb_phys,
			fbdev->fb_len, 0);
पूर्ण

अटल व्योम set_global(u_पूर्णांक cmd, काष्ठा au1200_lcd_global_regs_t *pdata)
अणु

	अचिन्हित पूर्णांक hi1, भागider;

	/* SCREEN_SIZE: user cannot reset size, must चयन panel choice */

	अगर (pdata->flags & SCREEN_BACKCOLOR)
		lcd->backcolor = pdata->backcolor;

	अगर (pdata->flags & SCREEN_BRIGHTNESS) अणु

		// limit brightness pwm duty to >= 30/1600
		अगर (pdata->brightness < 30) अणु
			pdata->brightness = 30;
		पूर्ण
		भागider = (lcd->pwmभाग & 0x3FFFF) + 1;
		hi1 = (((pdata->brightness & 0xFF)+1) * भागider >> 8);
		lcd->pwmhi &= 0xFFFF;
		lcd->pwmhi |= (hi1 << 16);
	पूर्ण

	अगर (pdata->flags & SCREEN_COLORKEY)
		lcd->colorkey = pdata->colorkey;

	अगर (pdata->flags & SCREEN_MASK)
		lcd->colorkeymsk = pdata->mask;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम get_global(u_पूर्णांक cmd, काष्ठा au1200_lcd_global_regs_t *pdata)
अणु
	अचिन्हित पूर्णांक hi1, भागider;

	pdata->xsize = ((lcd->screen & LCD_SCREEN_SX) >> 19) + 1;
	pdata->ysize = ((lcd->screen & LCD_SCREEN_SY) >> 8) + 1;

	pdata->backcolor = lcd->backcolor;
	pdata->colorkey = lcd->colorkey;
	pdata->mask = lcd->colorkeymsk;

	// brightness
	hi1 = (lcd->pwmhi >> 16) + 1;
	भागider = (lcd->pwmभाग & 0x3FFFF) + 1;
	pdata->brightness = ((hi1 << 8) / भागider) - 1;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम set_winकरोw(अचिन्हित पूर्णांक plane,
	काष्ठा au1200_lcd_winकरोw_regs_t *pdata)
अणु
	अचिन्हित पूर्णांक val, bpp;

	/* Winकरोw control रेजिस्टर 0 */
	अगर (pdata->flags & WIN_POSITION) अणु
		val = lcd->winकरोw[plane].winctrl0 & ~(LCD_WINCTRL0_OX |
				LCD_WINCTRL0_OY);
		val |= ((pdata->xpos << 21) & LCD_WINCTRL0_OX);
		val |= ((pdata->ypos << 10) & LCD_WINCTRL0_OY);
		lcd->winकरोw[plane].winctrl0 = val;
	पूर्ण
	अगर (pdata->flags & WIN_ALPHA_COLOR) अणु
		val = lcd->winकरोw[plane].winctrl0 & ~(LCD_WINCTRL0_A);
		val |= ((pdata->alpha_color << 2) & LCD_WINCTRL0_A);
		lcd->winकरोw[plane].winctrl0 = val;
	पूर्ण
	अगर (pdata->flags & WIN_ALPHA_MODE) अणु
		val = lcd->winकरोw[plane].winctrl0 & ~(LCD_WINCTRL0_AEN);
		val |= ((pdata->alpha_mode << 1) & LCD_WINCTRL0_AEN);
		lcd->winकरोw[plane].winctrl0 = val;
	पूर्ण

	/* Winकरोw control रेजिस्टर 1 */
	अगर (pdata->flags & WIN_PRIORITY) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_PRI);
		val |= ((pdata->priority << 30) & LCD_WINCTRL1_PRI);
		lcd->winकरोw[plane].winctrl1 = val;
	पूर्ण
	अगर (pdata->flags & WIN_CHANNEL) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_PIPE);
		val |= ((pdata->channel << 29) & LCD_WINCTRL1_PIPE);
		lcd->winकरोw[plane].winctrl1 = val;
	पूर्ण
	अगर (pdata->flags & WIN_BUFFER_FORMAT) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_FRM);
		val |= ((pdata->buffer_क्रमmat << 25) & LCD_WINCTRL1_FRM);
		lcd->winकरोw[plane].winctrl1 = val;
	पूर्ण
	अगर (pdata->flags & WIN_COLOR_ORDER) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_CCO);
		val |= ((pdata->color_order << 24) & LCD_WINCTRL1_CCO);
		lcd->winकरोw[plane].winctrl1 = val;
	पूर्ण
	अगर (pdata->flags & WIN_PIXEL_ORDER) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_PO);
		val |= ((pdata->pixel_order << 22) & LCD_WINCTRL1_PO);
		lcd->winकरोw[plane].winctrl1 = val;
	पूर्ण
	अगर (pdata->flags & WIN_SIZE) अणु
		val = lcd->winकरोw[plane].winctrl1 & ~(LCD_WINCTRL1_SZX |
				LCD_WINCTRL1_SZY);
		val |= (((pdata->xsize << 11) - 1) & LCD_WINCTRL1_SZX);
		val |= (((pdata->ysize) - 1) & LCD_WINCTRL1_SZY);
		lcd->winकरोw[plane].winctrl1 = val;
		/* program buffer line width */
		bpp = winbpp(val) / 8;
		val = lcd->winकरोw[plane].winctrl2 & ~(LCD_WINCTRL2_BX);
		val |= (((pdata->xsize * bpp) << 8) & LCD_WINCTRL2_BX);
		lcd->winकरोw[plane].winctrl2 = val;
	पूर्ण

	/* Winकरोw control रेजिस्टर 2 */
	अगर (pdata->flags & WIN_COLORKEY_MODE) अणु
		val = lcd->winकरोw[plane].winctrl2 & ~(LCD_WINCTRL2_CKMODE);
		val |= ((pdata->colorkey_mode << 24) & LCD_WINCTRL2_CKMODE);
		lcd->winकरोw[plane].winctrl2 = val;
	पूर्ण
	अगर (pdata->flags & WIN_DOUBLE_BUFFER_MODE) अणु
		val = lcd->winकरोw[plane].winctrl2 & ~(LCD_WINCTRL2_DBM);
		val |= ((pdata->द्विगुन_buffer_mode << 23) & LCD_WINCTRL2_DBM);
		lcd->winकरोw[plane].winctrl2 = val;
	पूर्ण
	अगर (pdata->flags & WIN_RAM_ARRAY_MODE) अणु
		val = lcd->winकरोw[plane].winctrl2 & ~(LCD_WINCTRL2_RAM);
		val |= ((pdata->ram_array_mode << 21) & LCD_WINCTRL2_RAM);
		lcd->winकरोw[plane].winctrl2 = val;
	पूर्ण

	/* Buffer line width programmed with WIN_SIZE */

	अगर (pdata->flags & WIN_BUFFER_SCALE) अणु
		val = lcd->winकरोw[plane].winctrl2 & ~(LCD_WINCTRL2_SCX |
				LCD_WINCTRL2_SCY);
		val |= ((pdata->xsize << 11) & LCD_WINCTRL2_SCX);
		val |= ((pdata->ysize) & LCD_WINCTRL2_SCY);
		lcd->winकरोw[plane].winctrl2 = val;
	पूर्ण

	अगर (pdata->flags & WIN_ENABLE) अणु
		val = lcd->winenable;
		val &= ~(1<<plane);
		val |= (pdata->enable & 1) << plane;
		lcd->winenable = val;
	पूर्ण
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम get_winकरोw(अचिन्हित पूर्णांक plane,
	काष्ठा au1200_lcd_winकरोw_regs_t *pdata)
अणु
	/* Winकरोw control रेजिस्टर 0 */
	pdata->xpos = (lcd->winकरोw[plane].winctrl0 & LCD_WINCTRL0_OX) >> 21;
	pdata->ypos = (lcd->winकरोw[plane].winctrl0 & LCD_WINCTRL0_OY) >> 10;
	pdata->alpha_color = (lcd->winकरोw[plane].winctrl0 & LCD_WINCTRL0_A) >> 2;
	pdata->alpha_mode = (lcd->winकरोw[plane].winctrl0 & LCD_WINCTRL0_AEN) >> 1;

	/* Winकरोw control रेजिस्टर 1 */
	pdata->priority = (lcd->winकरोw[plane].winctrl1& LCD_WINCTRL1_PRI) >> 30;
	pdata->channel = (lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_PIPE) >> 29;
	pdata->buffer_क्रमmat = (lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_FRM) >> 25;
	pdata->color_order = (lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_CCO) >> 24;
	pdata->pixel_order = (lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_PO) >> 22;
	pdata->xsize = ((lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_SZX) >> 11) + 1;
	pdata->ysize = (lcd->winकरोw[plane].winctrl1 & LCD_WINCTRL1_SZY) + 1;

	/* Winकरोw control रेजिस्टर 2 */
	pdata->colorkey_mode = (lcd->winकरोw[plane].winctrl2 & LCD_WINCTRL2_CKMODE) >> 24;
	pdata->द्विगुन_buffer_mode = (lcd->winकरोw[plane].winctrl2 & LCD_WINCTRL2_DBM) >> 23;
	pdata->ram_array_mode = (lcd->winकरोw[plane].winctrl2 & LCD_WINCTRL2_RAM) >> 21;

	pdata->enable = (lcd->winenable >> plane) & 1;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल पूर्णांक au1200fb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
                          अचिन्हित दीर्घ arg)
अणु
	काष्ठा au1200fb_device *fbdev = info->par;
	पूर्णांक plane;
	पूर्णांक val;

	plane = fbinfo2index(info);
	prपूर्णांक_dbg("au1200fb: ioctl %d on plane %d\n", cmd, plane);

	अगर (cmd == AU1200_LCD_FB_IOCTL) अणु
		काष्ठा au1200_lcd_iodata_t iodata;

		अगर (copy_from_user(&iodata, (व्योम __user *) arg, माप(iodata)))
			वापस -EFAULT;

		prपूर्णांक_dbg("FB IOCTL called\n");

		चयन (iodata.subcmd) अणु
		हाल AU1200_LCD_SET_SCREEN:
			prपूर्णांक_dbg("AU1200_LCD_SET_SCREEN\n");
			set_global(cmd, &iodata.global);
			अवरोध;

		हाल AU1200_LCD_GET_SCREEN:
			prपूर्णांक_dbg("AU1200_LCD_GET_SCREEN\n");
			get_global(cmd, &iodata.global);
			अवरोध;

		हाल AU1200_LCD_SET_WINDOW:
			prपूर्णांक_dbg("AU1200_LCD_SET_WINDOW\n");
			set_winकरोw(plane, &iodata.winकरोw);
			अवरोध;

		हाल AU1200_LCD_GET_WINDOW:
			prपूर्णांक_dbg("AU1200_LCD_GET_WINDOW\n");
			get_winकरोw(plane, &iodata.winकरोw);
			अवरोध;

		हाल AU1200_LCD_SET_PANEL:
			prपूर्णांक_dbg("AU1200_LCD_SET_PANEL\n");
			अगर ((iodata.global.panel_choice >= 0) &&
					(iodata.global.panel_choice <
					 NUM_PANELS))
			अणु
				काष्ठा panel_settings *newpanel;
				panel_index = iodata.global.panel_choice;
				newpanel = &known_lcd_panels[panel_index];
				au1200_setpanel(newpanel, fbdev->pd);
			पूर्ण
			अवरोध;

		हाल AU1200_LCD_GET_PANEL:
			prपूर्णांक_dbg("AU1200_LCD_GET_PANEL\n");
			iodata.global.panel_choice = panel_index;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		val = copy_to_user((व्योम __user *) arg, &iodata, माप(iodata));
		अगर (val) अणु
			prपूर्णांक_dbg("error: could not copy %d bytes\n", val);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा fb_ops au1200fb_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= au1200fb_fb_check_var,
	.fb_set_par	= au1200fb_fb_set_par,
	.fb_setcolreg	= au1200fb_fb_setcolreg,
	.fb_blank	= au1200fb_fb_blank,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_पढ़ो	= fb_sys_पढ़ो,
	.fb_ग_लिखो	= fb_sys_ग_लिखो,
	.fb_sync	= शून्य,
	.fb_ioctl	= au1200fb_ioctl,
	.fb_mmap	= au1200fb_fb_mmap,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल irqवापस_t au1200fb_handle_irq(पूर्णांक irq, व्योम* dev_id)
अणु
	/* Nothing to करो क्रम now, just clear any pending पूर्णांकerrupt */
	lcd->पूर्णांकstatus = lcd->पूर्णांकstatus;
	wmb(); /* drain ग_लिखोbuffer */

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

/* AU1200 LCD device probe helpers */

अटल पूर्णांक au1200fb_init_fbinfo(काष्ठा au1200fb_device *fbdev)
अणु
	काष्ठा fb_info *fbi = fbdev->fb_info;
	पूर्णांक bpp, ret;

	fbi->fbops = &au1200fb_fb_ops;

	bpp = winbpp(win->w[fbdev->plane].mode_winctrl1);

	/* Copy monitor specs from panel data */
	/* fixme: we're setting up LCD controller winकरोws, so these करोnt give a
	damn as to what the monitor specs are (the panel itself करोes, but that
	isn't करोne here...so maybe need a generic catchall monitor setting??? */
	स_नकल(&fbi->monspecs, &panel->monspecs, माप(काष्ठा fb_monspecs));

	/* We first try the user mode passed in argument. If that failed,
	 * or अगर no one has been specअगरied, we शेष to the first mode of the
	 * panel list. Note that after this call, var data will be set */
	अगर (!fb_find_mode(&fbi->var,
			  fbi,
			  शून्य, /* drv_info.opt_mode, */
			  fbi->monspecs.modedb,
			  fbi->monspecs.modedb_len,
			  fbi->monspecs.modedb,
			  bpp)) अणु

		prपूर्णांक_err("Cannot find valid mode for panel %s", panel->name);
		वापस -EFAULT;
	पूर्ण

	fbi->pseuकरो_palette = kसुस्मृति(16, माप(u32), GFP_KERNEL);
	अगर (!fbi->pseuकरो_palette)
		वापस -ENOMEM;

	ret = fb_alloc_cmap(&fbi->cmap, AU1200_LCD_NBR_PALETTE_ENTRIES, 0);
	अगर (ret < 0) अणु
		prपूर्णांक_err("Fail to allocate colormap (%d entries)",
			  AU1200_LCD_NBR_PALETTE_ENTRIES);
		वापस ret;
	पूर्ण

	म_नकलन(fbi->fix.id, "AU1200", माप(fbi->fix.id));
	fbi->fix.smem_start = fbdev->fb_phys;
	fbi->fix.smem_len = fbdev->fb_len;
	fbi->fix.type = FB_TYPE_PACKED_PIXELS;
	fbi->fix.xpanstep = 0;
	fbi->fix.ypanstep = 0;
	fbi->fix.mmio_start = 0;
	fbi->fix.mmio_len = 0;
	fbi->fix.accel = FB_ACCEL_NONE;

	fbi->screen_base = (अक्षर __iomem *) fbdev->fb_mem;

	au1200fb_update_fbinfo(fbi);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/


अटल पूर्णांक au1200fb_setup(काष्ठा au1200fb_platdata *pd)
अणु
	अक्षर *options = शून्य;
	अक्षर *this_opt, *endptr;
	पूर्णांक num_panels = ARRAY_SIZE(known_lcd_panels);
	पूर्णांक panel_idx = -1;

	fb_get_options(DRIVER_NAME, &options);

	अगर (!options)
		जाओ out;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		/* Panel option - can be panel name,
		 * "bs" क्रम board-चयन, or number/index */
		अगर (!म_भेदन(this_opt, "panel:", 6)) अणु
			पूर्णांक i;
			दीर्घ पूर्णांक li;
			अक्षर *endptr;
			this_opt += 6;
			/* First check क्रम index, which allows
			 * to लघु circuit this mess */
			li = simple_म_से_दीर्घ(this_opt, &endptr, 0);
			अगर (*endptr == '\0')
				panel_idx = (पूर्णांक)li;
			अन्यथा अगर (म_भेद(this_opt, "bs") == 0)
				panel_idx = pd->panel_index();
			अन्यथा अणु
				क्रम (i = 0; i < num_panels; i++) अणु
					अगर (!म_भेद(this_opt,
						    known_lcd_panels[i].name)) अणु
						panel_idx = i;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर ((panel_idx < 0) || (panel_idx >= num_panels))
				prपूर्णांक_warn("Panel %s not supported!", this_opt);
			अन्यथा
				panel_index = panel_idx;

		पूर्ण अन्यथा अगर (म_भेदन(this_opt, "nohwcursor", 10) == 0)
			nohwcursor = 1;
		अन्यथा अगर (म_भेदन(this_opt, "devices:", 8) == 0) अणु
			this_opt += 8;
			device_count = simple_म_से_दीर्घ(this_opt, &endptr, 0);
			अगर ((device_count < 0) ||
			    (device_count > MAX_DEVICE_COUNT))
				device_count = MAX_DEVICE_COUNT;
		पूर्ण अन्यथा अगर (म_भेदन(this_opt, "wincfg:", 7) == 0) अणु
			this_opt += 7;
			winकरोw_index = simple_म_से_दीर्घ(this_opt, &endptr, 0);
			अगर ((winकरोw_index < 0) ||
			    (winकरोw_index >= ARRAY_SIZE(winकरोws)))
				winकरोw_index = DEFAULT_WINDOW_INDEX;
		पूर्ण अन्यथा अगर (म_भेदन(this_opt, "off", 3) == 0)
			वापस 1;
		अन्यथा
			prपूर्णांक_warn("Unsupported option \"%s\"", this_opt);
	पूर्ण

out:
	वापस 0;
पूर्ण

/* AU1200 LCD controller device driver */
अटल पूर्णांक au1200fb_drv_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा au1200fb_device *fbdev;
	काष्ठा au1200fb_platdata *pd;
	काष्ठा fb_info *fbi = शून्य;
	पूर्णांक bpp, plane, ret, irq;

	prपूर्णांक_info("" DRIVER_DESC "");

	pd = dev->dev.platक्रमm_data;
	अगर (!pd)
		वापस -ENODEV;

	/* Setup driver with options */
	अगर (au1200fb_setup(pd))
		वापस -ENODEV;

	/* Poपूर्णांक to the panel selected */
	panel = &known_lcd_panels[panel_index];
	win = &winकरोws[winकरोw_index];

	prपूर्णांकk(DRIVER_NAME ": Panel %d %s\n", panel_index, panel->name);
	prपूर्णांकk(DRIVER_NAME ": Win %d %s\n", winकरोw_index, win->name);

	क्रम (plane = 0; plane < device_count; ++plane) अणु
		bpp = winbpp(win->w[plane].mode_winctrl1);
		अगर (win->w[plane].xres == 0)
			win->w[plane].xres = panel->Xres;
		अगर (win->w[plane].yres == 0)
			win->w[plane].yres = panel->Yres;

		fbi = framebuffer_alloc(माप(काष्ठा au1200fb_device),
					&dev->dev);
		अगर (!fbi) अणु
			ret = -ENOMEM;
			जाओ failed;
		पूर्ण

		_au1200fb_infos[plane] = fbi;
		fbdev = fbi->par;
		fbdev->fb_info = fbi;
		fbdev->pd = pd;
		fbdev->dev = &dev->dev;

		fbdev->plane = plane;

		/* Allocate the framebuffer to the maximum screen size */
		fbdev->fb_len = (win->w[plane].xres * win->w[plane].yres * bpp) / 8;

		fbdev->fb_mem = dmam_alloc_attrs(&dev->dev,
				PAGE_ALIGN(fbdev->fb_len),
				&fbdev->fb_phys, GFP_KERNEL, 0);
		अगर (!fbdev->fb_mem) अणु
			prपूर्णांक_err("fail to allocate framebuffer (size: %dK))",
				  fbdev->fb_len / 1024);
			ret = -ENOMEM;
			जाओ failed;
		पूर्ण

		prपूर्णांक_dbg("Framebuffer memory map at %p", fbdev->fb_mem);
		prपूर्णांक_dbg("phys=0x%08x, size=%dK", fbdev->fb_phys, fbdev->fb_len / 1024);

		/* Init FB data */
		ret = au1200fb_init_fbinfo(fbdev);
		अगर (ret < 0)
			जाओ failed;

		/* Register new framebuffer */
		ret = रेजिस्टर_framebuffer(fbi);
		अगर (ret < 0) अणु
			prपूर्णांक_err("cannot register new framebuffer");
			जाओ failed;
		पूर्ण

		au1200fb_fb_set_par(fbi);

#अगर !defined(CONFIG_FRAMEBUFFER_CONSOLE) && defined(CONFIG_LOGO)
		अगर (plane == 0)
			अगर (fb_prepare_logo(fbi, FB_ROTATE_UR)) अणु
				/* Start display and show logo on boot */
				fb_set_cmap(&fbi->cmap, fbi);
				fb_show_logo(fbi, FB_ROTATE_UR);
			पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Now hook पूर्णांकerrupt too */
	irq = platक्रमm_get_irq(dev, 0);
	ret = request_irq(irq, au1200fb_handle_irq,
			  IRQF_SHARED, "lcd", (व्योम *)dev);
	अगर (ret) अणु
		prपूर्णांक_err("fail to request interrupt line %d (err: %d)",
			  irq, ret);
		जाओ failed;
	पूर्ण

	platक्रमm_set_drvdata(dev, pd);

	/* Kickstart the panel */
	au1200_setpanel(panel, pd);

	वापस 0;

failed:
	क्रम (plane = 0; plane < device_count; ++plane) अणु
		fbi = _au1200fb_infos[plane];
		अगर (!fbi)
			अवरोध;

		/* Clean up all probe data */
		unरेजिस्टर_framebuffer(fbi);
		अगर (fbi->cmap.len != 0)
			fb_dealloc_cmap(&fbi->cmap);
		kमुक्त(fbi->pseuकरो_palette);

		framebuffer_release(fbi);
		_au1200fb_infos[plane] = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक au1200fb_drv_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा au1200fb_platdata *pd = platक्रमm_get_drvdata(dev);
	काष्ठा fb_info *fbi;
	पूर्णांक plane;

	/* Turn off the panel */
	au1200_setpanel(शून्य, pd);

	क्रम (plane = 0; plane < device_count; ++plane)	अणु
		fbi = _au1200fb_infos[plane];

		/* Clean up all probe data */
		unरेजिस्टर_framebuffer(fbi);
		अगर (fbi->cmap.len != 0)
			fb_dealloc_cmap(&fbi->cmap);
		kमुक्त(fbi->pseuकरो_palette);

		framebuffer_release(fbi);
		_au1200fb_infos[plane] = शून्य;
	पूर्ण

	मुक्त_irq(platक्रमm_get_irq(dev, 0), (व्योम *)dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1200fb_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा au1200fb_platdata *pd = dev_get_drvdata(dev);
	au1200_setpanel(शून्य, pd);

	lcd->ouपंचांगask = 0;
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल पूर्णांक au1200fb_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा au1200fb_platdata *pd = dev_get_drvdata(dev);
	काष्ठा fb_info *fbi;
	पूर्णांक i;

	/* Kickstart the panel */
	au1200_setpanel(panel, pd);

	क्रम (i = 0; i < device_count; i++) अणु
		fbi = _au1200fb_infos[i];
		au1200fb_fb_set_par(fbi);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops au1200fb_pmops = अणु
	.suspend	= au1200fb_drv_suspend,
	.resume		= au1200fb_drv_resume,
	.मुक्तze		= au1200fb_drv_suspend,
	.thaw		= au1200fb_drv_resume,
पूर्ण;

#घोषणा AU1200FB_PMOPS	(&au1200fb_pmops)

#अन्यथा
#घोषणा AU1200FB_PMOPS	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver au1200fb_driver = अणु
	.driver = अणु
		.name	= "au1200-lcd",
		.pm	= AU1200FB_PMOPS,
	पूर्ण,
	.probe		= au1200fb_drv_probe,
	.हटाओ		= au1200fb_drv_हटाओ,
पूर्ण;
module_platक्रमm_driver(au1200fb_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
