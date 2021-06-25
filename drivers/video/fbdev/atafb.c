<शैली गुरु>
/*
 * linux/drivers/video/atafb.c -- Atari builtin chipset frame buffer device
 *
 *  Copyright (C) 1994 Martin Schaller & Roman Hodek
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * History:
 *   - 03 Jan 95: Original version by Martin Schaller: The TT driver and
 *                all the device independent stuff
 *   - 09 Jan 95: Roman: I've added the hardware असलtraction (hw_चयन)
 *                and wrote the Falcon, ST(E), and External drivers
 *                based on the original TT driver.
 *   - 07 May 95: Martin: Added colormap operations क्रम the बाह्यal driver
 *   - 21 May 95: Martin: Added support क्रम overscan
 *		  Andreas: some bug fixes क्रम this
 *   -    Jul 95: Guenther Kelleter <guenther@pool.inक्रमmatik.rwth-aachen.de>:
 *                Programmable Falcon video modes
 *                (thanks to Christian Cartus क्रम करोcumentation
 *                of VIDEL रेजिस्टरs).
 *   - 27 Dec 95: Guenther: Implemented user definable video modes "user[0-7]"
 *                on minor 24...31. "user0" may be set on commandline by
 *                "R<x>;<y>;<depth>". (Makes sense only on Falcon)
 *                Video mode चयन on Falcon now करोne at next VBL पूर्णांकerrupt
 *                to aव्योम the annoying right shअगरt of the screen.
 *   - 23 Sep 97: Juergen: added xres_भव क्रम cards like ProMST
 *                The बाह्यal-part is legacy, thereक्रमe hardware-specअगरic
 *                functions like panning/hardwarescrolling/blanking isn't
 *				  supported.
 *   - 29 Sep 97: Juergen: added Romans suggestion क्रम pan_display
 *				  (var->xoffset was changed even अगर no set_screen_base avail.)
 *	 - 05 Oct 97: Juergen: extfb (PACKED_PIXEL) is FB_PSEUDOCOLOR 'cause
 *				  we know how to set the colors
 *				  ext_*palette: पढ़ो from ext_colors (क्रमmer MV300_colors)
 *							    ग_लिखो to ext_colors and RAMDAC
 *
 * To करो:
 *   - For the Falcon it is not possible to set अक्रमom video modes on
 *     SM124 and SC/TV, only the bootup resolution is supported.
 *
 */

#घोषणा ATAFB_TT
#घोषणा ATAFB_STE
#घोषणा ATAFB_EXT
#घोषणा ATAFB_FALCON

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stram.h>

#समावेश <linux/fb.h>
#समावेश <यंत्र/atarikb.h>

#समावेश "c2p.h"
#समावेश "atafb.h"

#घोषणा SWITCH_ACIA 0x01		/* modes क्रम चयन on OverScan */
#घोषणा SWITCH_SND6 0x40
#घोषणा SWITCH_SND7 0x80
#घोषणा SWITCH_NONE 0x00

#घोषणा up(x, r) (((x) + (r) - 1) & ~((r)-1))


अटल पूर्णांक शेष_par;		/* शेष resolution (0=none) */

अटल अचिन्हित दीर्घ शेष_mem_req;

अटल पूर्णांक hwscroll = -1;

अटल पूर्णांक use_hwscroll = 1;

अटल पूर्णांक sttt_xres = 640, st_yres = 400, tt_yres = 480;
अटल पूर्णांक sttt_xres_भव = 640, sttt_yres_भव = 400;
अटल पूर्णांक ovsc_offset, ovsc_addlen;

	/*
	 * Hardware parameters क्रम current mode
	 */

अटल काष्ठा atafb_par अणु
	व्योम *screen_base;
	पूर्णांक yres_भव;
	u_दीर्घ next_line;
#अगर defined ATAFB_TT || defined ATAFB_STE
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक mode;
			पूर्णांक sync;
		पूर्ण tt, st;
#पूर्ण_अगर
#अगर_घोषित ATAFB_FALCON
		काष्ठा falcon_hw अणु
			/* Here are fields क्रम storing a video mode, as direct
			 * parameters क्रम the hardware.
			 */
			लघु sync;
			लघु line_width;
			लघु line_offset;
			लघु st_shअगरt;
			लघु f_shअगरt;
			लघु vid_control;
			लघु vid_mode;
			लघु xoffset;
			लघु hht, hbb, hbe, hdb, hde, hss;
			लघु vft, vbb, vbe, vdb, vde, vss;
			/* auxiliary inक्रमmation */
			लघु mono;
			लघु ste_mode;
			लघु bpp;
			u32 pseuकरो_palette[16];
		पूर्ण falcon;
#पूर्ण_अगर
		/* Nothing needed क्रम बाह्यal mode */
	पूर्ण hw;
पूर्ण current_par;

/* Don't calculate an own resolution, and thus don't change the one found when
 * booting (currently used क्रम the Falcon to keep settings क्रम पूर्णांकernal video
 * hardware extensions (e.g. ScreenBlaster)  */
अटल पूर्णांक DontCalcRes = 0;

#अगर_घोषित ATAFB_FALCON
#घोषणा HHT hw.falcon.hht
#घोषणा HBB hw.falcon.hbb
#घोषणा HBE hw.falcon.hbe
#घोषणा HDB hw.falcon.hdb
#घोषणा HDE hw.falcon.hde
#घोषणा HSS hw.falcon.hss
#घोषणा VFT hw.falcon.vft
#घोषणा VBB hw.falcon.vbb
#घोषणा VBE hw.falcon.vbe
#घोषणा VDB hw.falcon.vdb
#घोषणा VDE hw.falcon.vde
#घोषणा VSS hw.falcon.vss
#घोषणा VCO_CLOCK25		0x04
#घोषणा VCO_CSYPOS		0x10
#घोषणा VCO_VSYPOS		0x20
#घोषणा VCO_HSYPOS		0x40
#घोषणा VCO_SHORTOFFS	0x100
#घोषणा VMO_DOUBLE		0x01
#घोषणा VMO_INTER		0x02
#घोषणा VMO_PREMASK		0x0c
#पूर्ण_अगर

अटल काष्ठा fb_info fb_info = अणु
	.fix = अणु
		.id	= "Atari ",
		.visual	= FB_VISUAL_PSEUDOCOLOR,
		.accel	= FB_ACCEL_NONE,
	पूर्ण
पूर्ण;

अटल व्योम *screen_base;	/* base address of screen */
अटल अचिन्हित दीर्घ phys_screen_base;	/* (only क्रम Overscan) */

अटल पूर्णांक screen_len;

अटल पूर्णांक current_par_valid;

अटल पूर्णांक mono_moni;


#अगर_घोषित ATAFB_EXT

/* बाह्यal video handling */
अटल अचिन्हित पूर्णांक बाह्यal_xres;
अटल अचिन्हित पूर्णांक बाह्यal_xres_भव;
अटल अचिन्हित पूर्णांक बाह्यal_yres;

/*
 * not needed - atafb will never support panning/hardwarescroll with बाह्यal
 * अटल अचिन्हित पूर्णांक बाह्यal_yres_भव;
 */
अटल अचिन्हित पूर्णांक बाह्यal_depth;
अटल पूर्णांक बाह्यal_pmode;
अटल व्योम *बाह्यal_screen_base;
अटल अचिन्हित दीर्घ बाह्यal_addr;
अटल अचिन्हित दीर्घ बाह्यal_len;
अटल अचिन्हित दीर्घ बाह्यal_vgaiobase;
अटल अचिन्हित पूर्णांक बाह्यal_bitspercol = 6;

/*
 * JOE <joe@amber.dinoco.de>:
 * added card type क्रम बाह्यal driver, is only needed क्रम
 * colormap handling.
 */
क्रमागत cardtype अणु IS_VGA, IS_MV300 पूर्ण;
अटल क्रमागत cardtype बाह्यal_card_type = IS_VGA;

/*
 * The MV300 mixes the color रेजिस्टरs. So we need an array of munged
 * indices in order to access the correct reg.
 */
अटल पूर्णांक MV300_reg_1bit[2] = अणु
	0, 1
पूर्ण;
अटल पूर्णांक MV300_reg_4bit[16] = अणु
	0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
पूर्ण;
अटल पूर्णांक MV300_reg_8bit[256] = अणु
	0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240,
	8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248,
	4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244,
	12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252,
	2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242,
	10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250,
	6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246,
	14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254,
	1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241,
	9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249,
	5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245,
	13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253,
	3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243,
	11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251,
	7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247,
	15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255
पूर्ण;

अटल पूर्णांक *MV300_reg = MV300_reg_8bit;
#पूर्ण_अगर /* ATAFB_EXT */


अटल पूर्णांक inverse;

/*
 * काष्ठा fb_ops अणु
 *	* खोलो/release and usage marking
 *	काष्ठा module *owner;
 *	पूर्णांक (*fb_खोलो)(काष्ठा fb_info *info, पूर्णांक user);
 *	पूर्णांक (*fb_release)(काष्ठा fb_info *info, पूर्णांक user);
 *
 *	* For framebuffers with strange non linear layouts or that करो not
 *	* work with normal memory mapped access
 *	sमाप_प्रकार (*fb_पढ़ो)(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
 *	sमाप_प्रकार (*fb_ग_लिखो)(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
 *
 *	* checks var and eventually tweaks it to something supported,
 *	* DOES NOT MODIFY PAR *
 *	पूर्णांक (*fb_check_var)(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);
 *
 *	* set the video mode according to info->var *
 *	पूर्णांक (*fb_set_par)(काष्ठा fb_info *info);
 *
 *	* set color रेजिस्टर *
 *	पूर्णांक (*fb_setcolreg)(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red, अचिन्हित पूर्णांक green,
 *			    अचिन्हित पूर्णांक blue, अचिन्हित पूर्णांक transp, काष्ठा fb_info *info);
 *
 *	* set color रेजिस्टरs in batch *
 *	पूर्णांक (*fb_setcmap)(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info);
 *
 *	* blank display *
 *	पूर्णांक (*fb_blank)(पूर्णांक blank, काष्ठा fb_info *info);
 *
 *	* pan display *
 *	पूर्णांक (*fb_pan_display)(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);
 *
 *	*** The meat of the drawing engine ***
 *	* Draws a rectangle *
 *	व्योम (*fb_fillrect) (काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
 *	* Copy data from area to another *
 *	व्योम (*fb_copyarea) (काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region);
 *	* Draws a image to the display *
 *	व्योम (*fb_imageblit) (काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
 *
 *	* Draws cursor *
 *	पूर्णांक (*fb_cursor) (काष्ठा fb_info *info, काष्ठा fb_cursor *cursor);
 *
 *	* रुको क्रम blit idle, optional *
 *	पूर्णांक (*fb_sync)(काष्ठा fb_info *info);
 *
 *	* perक्रमm fb specअगरic ioctl (optional) *
 *	पूर्णांक (*fb_ioctl)(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
 *			अचिन्हित दीर्घ arg);
 *
 *	* Handle 32bit compat ioctl (optional) *
 *	पूर्णांक (*fb_compat_ioctl)(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
 *			अचिन्हित दीर्घ arg);
 *
 *	* perक्रमm fb specअगरic mmap *
 *	पूर्णांक (*fb_mmap)(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);
 * पूर्ण ;
 */


/* ++roman: This काष्ठाure असलtracts from the underlying hardware (ST(e),
 * TT, or Falcon.
 *
 * पूर्णांक (*detect)(व्योम)
 *   This function should detect the current video mode settings and
 *   store them in atafb_predefined[0] क्रम later reference by the
 *   user. Return the index+1 of an equivalent predefined mode or 0
 *   अगर there is no such.
 *
 * पूर्णांक (*encode_fix)(काष्ठा fb_fix_screeninfo *fix,
 *                   काष्ठा atafb_par *par)
 *   This function should fill in the 'fix' काष्ठाure based on the
 *   values in the 'par' काष्ठाure.
 * !!! Obsolete, perhaps !!!
 *
 * पूर्णांक (*decode_var)(काष्ठा fb_var_screeninfo *var,
 *                   काष्ठा atafb_par *par)
 *   Get the video params out of 'var'. If a value doesn't fit, round
 *   it up, अगर it's too big, वापस EINVAL.
 *   Round up in the following order: bits_per_pixel, xres, yres,
 *   xres_भव, yres_भव, xoffset, yoffset, grayscale, bitfields,
 *   horizontal timing, vertical timing.
 *
 * पूर्णांक (*encode_var)(काष्ठा fb_var_screeninfo *var,
 *                   काष्ठा atafb_par *par);
 *   Fill the 'var' structure based on the values in 'par' and maybe
 *   other values पढ़ो out of the hardware.
 *
 * व्योम (*get_par)(काष्ठा atafb_par *par)
 *   Fill the hardware's 'par' काष्ठाure.
 *   !!! Used only by detect() !!!
 *
 * व्योम (*set_par)(काष्ठा atafb_par *par)
 *   Set the hardware according to 'par'.
 *
 * व्योम (*set_screen_base)(व्योम *s_base)
 *   Set the base address of the displayed frame buffer. Only called
 *   अगर yres_भव > yres or xres_भव > xres.
 *
 * पूर्णांक (*blank)(पूर्णांक blank_mode)
 *   Blank the screen अगर blank_mode != 0, अन्यथा unblank. If blank == शून्य then
 *   the caller blanks by setting the CLUT to all black. Return 0 अगर blanking
 *   succeeded, !=0 अगर un-/blanking failed due to e.g. a video mode which
 *   करोesn't support it. Implements VESA suspend and घातerकरोwn modes on
 *   hardware that supports disabling hsync/vsync:
 *       blank_mode == 2: suspend vsync, 3:suspend hsync, 4: घातerकरोwn.
 */

अटल काष्ठा fb_hwचयन अणु
	पूर्णांक (*detect)(व्योम);
	पूर्णांक (*encode_fix)(काष्ठा fb_fix_screeninfo *fix,
			  काष्ठा atafb_par *par);
	पूर्णांक (*decode_var)(काष्ठा fb_var_screeninfo *var,
			  काष्ठा atafb_par *par);
	पूर्णांक (*encode_var)(काष्ठा fb_var_screeninfo *var,
			  काष्ठा atafb_par *par);
	व्योम (*get_par)(काष्ठा atafb_par *par);
	व्योम (*set_par)(काष्ठा atafb_par *par);
	व्योम (*set_screen_base)(व्योम *s_base);
	पूर्णांक (*blank)(पूर्णांक blank_mode);
	पूर्णांक (*pan_display)(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info);
पूर्ण *fbhw;

अटल अक्षर *स्वतःdetect_names[] = अणु "autodetect", शून्य पूर्ण;
अटल अक्षर *stlow_names[] = अणु "stlow", शून्य पूर्ण;
अटल अक्षर *sपंचांगid_names[] = अणु "stmid", "default5", शून्य पूर्ण;
अटल अक्षर *sthigh_names[] = अणु "sthigh", "default4", शून्य पूर्ण;
अटल अक्षर *ttlow_names[] = अणु "ttlow", शून्य पूर्ण;
अटल अक्षर *tपंचांगid_names[] = अणु "ttmid", "default1", शून्य पूर्ण;
अटल अक्षर *tthigh_names[] = अणु "tthigh", "default2", शून्य पूर्ण;
अटल अक्षर *vga2_names[] = अणु "vga2", शून्य पूर्ण;
अटल अक्षर *vga4_names[] = अणु "vga4", शून्य पूर्ण;
अटल अक्षर *vga16_names[] = अणु "vga16", "default3", शून्य पूर्ण;
अटल अक्षर *vga256_names[] = अणु "vga256", शून्य पूर्ण;
अटल अक्षर *falh2_names[] = अणु "falh2", शून्य पूर्ण;
अटल अक्षर *falh16_names[] = अणु "falh16", शून्य पूर्ण;

अटल अक्षर **fb_var_names[] = अणु
	स्वतःdetect_names,
	stlow_names,
	sपंचांगid_names,
	sthigh_names,
	ttlow_names,
	tपंचांगid_names,
	tthigh_names,
	vga2_names,
	vga4_names,
	vga16_names,
	vga256_names,
	falh2_names,
	falh16_names,
	शून्य
पूर्ण;

अटल काष्ठा fb_var_screeninfo atafb_predefined[] = अणु
	/*
	 * yres_भव == 0 means use hw-scrolling अगर possible, अन्यथा yres
	 */
	अणु /* स्वतःdetect */
	  0, 0, 0, 0, 0, 0, 0, 0,		/* xres-grayscale */
	  अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण, अणु0, 0, 0पूर्ण,	/* red green blue tran*/
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* st low */
	  320, 200, 320, 0, 0, 0, 4, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* st mid */
	  640, 200, 640, 0, 0, 0, 2, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* st high */
	  640, 400, 640, 0, 0, 0, 1, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* tt low */
	  320, 480, 320, 0, 0, 0, 8, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* tt mid */
	  640, 480, 640, 0, 0, 0, 4, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* tt high */
	  1280, 960, 1280, 0, 0, 0, 1, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* vga2 */
	  640, 480, 640, 0, 0, 0, 1, 0,
	  अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* vga4 */
	  640, 480, 640, 0, 0, 0, 2, 0,
	  अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 4, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* vga16 */
	  640, 480, 640, 0, 0, 0, 4, 0,
	  अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* vga256 */
	  640, 480, 640, 0, 0, 0, 8, 0,
	  अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* falh2 */
	  896, 608, 896, 0, 0, 0, 1, 0,
	  अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु /* falh16 */
	  896, 608, 896, 0, 0, 0, 4, 0,
	  अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 6, 0पूर्ण, अणु0, 0, 0पूर्ण,
	  0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक num_atafb_predefined = ARRAY_SIZE(atafb_predefined);

अटल काष्ठा fb_videomode atafb_modedb[] __initdata = अणु
	/*
	 *  Atari Video Modes
	 *
	 *  If you change these, make sure to update DEFMODE_* as well!
	 */

	/*
	 *  ST/TT Video Modes
	 */

	अणु
		/* 320x200, 15 kHz, 60 Hz (ST low) */
		"st-low", 60, 320, 200, 32000, 32, 16, 31, 14, 96, 4,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x200, 15 kHz, 60 Hz (ST medium) */
		"st-mid", 60, 640, 200, 32000, 32, 16, 31, 14, 96, 4,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 30.25 kHz, 63.5 Hz (ST high) */
		"st-high", 63, 640, 400, 32000, 128, 0, 40, 14, 128, 4,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 320x480, 15 kHz, 60 Hz (TT low) */
		"tt-low", 60, 320, 480, 31041, 120, 100, 8, 16, 140, 30,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x480, 29 kHz, 57 Hz (TT medium) */
		"tt-mid", 60, 640, 480, 31041, 120, 100, 8, 16, 140, 30,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 1280x960, 29 kHz, 60 Hz (TT high) */
		"tt-high", 57, 640, 960, 31041, 120, 100, 8, 16, 140, 30,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण,

	/*
	 *  VGA Video Modes
	 */

	अणु
		/* 640x480, 31 kHz, 60 Hz (VGA) */
		"vga", 63.5, 640, 480, 32000, 18, 42, 31, 11, 96, 3,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण, अणु
		/* 640x400, 31 kHz, 70 Hz (VGA) */
		"vga70", 70, 640, 400, 32000, 18, 42, 31, 11, 96, 3,
		FB_SYNC_VERT_HIGH_ACT | FB_SYNC_COMP_HIGH_ACT, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण,

	/*
	 *  Falcon HiRes Video Modes
	 */

	अणु
		/* 896x608, 31 kHz, 60 Hz (Falcon High) */
		"falh", 60, 896, 608, 32000, 18, 42, 31, 1, 96,3,
		0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
	पूर्ण,
पूर्ण;

#घोषणा NUM_TOTAL_MODES  ARRAY_SIZE(atafb_modedb)

अटल अक्षर *mode_option __initdata = शून्य;

 /* शेष modes */

#घोषणा DEFMODE_TT	5		/* "tt-high" क्रम TT */
#घोषणा DEFMODE_F30	7		/* "vga70" क्रम Falcon */
#घोषणा DEFMODE_STE	2		/* "st-high" क्रम ST/E */
#घोषणा DEFMODE_EXT	6		/* "vga" क्रम बाह्यal */


अटल पूर्णांक get_video_mode(अक्षर *vname)
अणु
	अक्षर ***name_list;
	अक्षर **name;
	पूर्णांक i;

	name_list = fb_var_names;
	क्रम (i = 0; i < num_atafb_predefined; i++) अणु
		name = *name_list++;
		अगर (!name || !*name)
			अवरोध;
		जबतक (*name) अणु
			अगर (!म_भेद(vname, *name))
				वापस i + 1;
			name++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण



/* ------------------- TT specअगरic functions ---------------------- */

#अगर_घोषित ATAFB_TT

अटल पूर्णांक tt_encode_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा atafb_par *par)
अणु
	पूर्णांक mode;

	म_नकल(fix->id, "Atari Builtin");
	fix->smem_start = phys_screen_base;
	fix->smem_len = screen_len;
	fix->type = FB_TYPE_INTERLEAVED_PLANES;
	fix->type_aux = 2;
	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	mode = par->hw.tt.mode & TT_SHIFTER_MODEMASK;
	अगर (mode == TT_SHIFTER_TTHIGH || mode == TT_SHIFTER_STHIGH) अणु
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		अगर (mode == TT_SHIFTER_TTHIGH)
			fix->visual = FB_VISUAL_MONO01;
	पूर्ण
	fix->xpanstep = 0;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->line_length = par->next_line;
	fix->accel = FB_ACCEL_ATARIBLITT;
	वापस 0;
पूर्ण

अटल पूर्णांक tt_decode_var(काष्ठा fb_var_screeninfo *var, काष्ठा atafb_par *par)
अणु
	पूर्णांक xres = var->xres;
	पूर्णांक yres = var->yres;
	पूर्णांक bpp = var->bits_per_pixel;
	पूर्णांक linelen;
	पूर्णांक yres_भव = var->yres_भव;

	अगर (mono_moni) अणु
		अगर (bpp > 1 || xres > sttt_xres * 2 || yres > tt_yres * 2)
			वापस -EINVAL;
		par->hw.tt.mode = TT_SHIFTER_TTHIGH;
		xres = sttt_xres * 2;
		yres = tt_yres * 2;
		bpp = 1;
	पूर्ण अन्यथा अणु
		अगर (bpp > 8 || xres > sttt_xres || yres > tt_yres)
			वापस -EINVAL;
		अगर (bpp > 4) अणु
			अगर (xres > sttt_xres / 2 || yres > tt_yres)
				वापस -EINVAL;
			par->hw.tt.mode = TT_SHIFTER_TTLOW;
			xres = sttt_xres / 2;
			yres = tt_yres;
			bpp = 8;
		पूर्ण अन्यथा अगर (bpp > 2) अणु
			अगर (xres > sttt_xres || yres > tt_yres)
				वापस -EINVAL;
			अगर (xres > sttt_xres / 2 || yres > st_yres / 2) अणु
				par->hw.tt.mode = TT_SHIFTER_TTMID;
				xres = sttt_xres;
				yres = tt_yres;
				bpp = 4;
			पूर्ण अन्यथा अणु
				par->hw.tt.mode = TT_SHIFTER_STLOW;
				xres = sttt_xres / 2;
				yres = st_yres / 2;
				bpp = 4;
			पूर्ण
		पूर्ण अन्यथा अगर (bpp > 1) अणु
			अगर (xres > sttt_xres || yres > st_yres / 2)
				वापस -EINVAL;
			par->hw.tt.mode = TT_SHIFTER_STMID;
			xres = sttt_xres;
			yres = st_yres / 2;
			bpp = 2;
		पूर्ण अन्यथा अगर (var->xres > sttt_xres || var->yres > st_yres) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			par->hw.tt.mode = TT_SHIFTER_STHIGH;
			xres = sttt_xres;
			yres = st_yres;
			bpp = 1;
		पूर्ण
	पूर्ण
	अगर (yres_भव <= 0)
		yres_भव = 0;
	अन्यथा अगर (yres_भव < yres)
		yres_भव = yres;
	अगर (var->sync & FB_SYNC_EXT)
		par->hw.tt.sync = 0;
	अन्यथा
		par->hw.tt.sync = 1;
	linelen = xres * bpp / 8;
	अगर (yres_भव * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (yres * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (var->yoffset + yres > yres_भव && yres_भव)
		वापस -EINVAL;
	par->yres_भव = yres_भव;
	par->screen_base = screen_base + var->yoffset * linelen;
	par->next_line = linelen;
	वापस 0;
पूर्ण

अटल पूर्णांक tt_encode_var(काष्ठा fb_var_screeninfo *var, काष्ठा atafb_par *par)
अणु
	पूर्णांक linelen;
	स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));
	var->red.offset = 0;
	var->red.length = 4;
	var->red.msb_right = 0;
	var->grayscale = 0;

	var->pixघड़ी = 31041;
	var->left_margin = 120;		/* these may be incorrect */
	var->right_margin = 100;
	var->upper_margin = 8;
	var->lower_margin = 16;
	var->hsync_len = 140;
	var->vsync_len = 30;

	var->height = -1;
	var->width = -1;

	अगर (par->hw.tt.sync & 1)
		var->sync = 0;
	अन्यथा
		var->sync = FB_SYNC_EXT;

	चयन (par->hw.tt.mode & TT_SHIFTER_MODEMASK) अणु
	हाल TT_SHIFTER_STLOW:
		var->xres = sttt_xres / 2;
		var->xres_भव = sttt_xres_भव / 2;
		var->yres = st_yres / 2;
		var->bits_per_pixel = 4;
		अवरोध;
	हाल TT_SHIFTER_STMID:
		var->xres = sttt_xres;
		var->xres_भव = sttt_xres_भव;
		var->yres = st_yres / 2;
		var->bits_per_pixel = 2;
		अवरोध;
	हाल TT_SHIFTER_STHIGH:
		var->xres = sttt_xres;
		var->xres_भव = sttt_xres_भव;
		var->yres = st_yres;
		var->bits_per_pixel = 1;
		अवरोध;
	हाल TT_SHIFTER_TTLOW:
		var->xres = sttt_xres / 2;
		var->xres_भव = sttt_xres_भव / 2;
		var->yres = tt_yres;
		var->bits_per_pixel = 8;
		अवरोध;
	हाल TT_SHIFTER_TTMID:
		var->xres = sttt_xres;
		var->xres_भव = sttt_xres_भव;
		var->yres = tt_yres;
		var->bits_per_pixel = 4;
		अवरोध;
	हाल TT_SHIFTER_TTHIGH:
		var->red.length = 0;
		var->xres = sttt_xres * 2;
		var->xres_भव = sttt_xres_भव * 2;
		var->yres = tt_yres * 2;
		var->bits_per_pixel = 1;
		अवरोध;
	पूर्ण
	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	linelen = var->xres_भव * var->bits_per_pixel / 8;
	अगर (!use_hwscroll)
		var->yres_भव = var->yres;
	अन्यथा अगर (screen_len) अणु
		अगर (par->yres_भव)
			var->yres_भव = par->yres_भव;
		अन्यथा
			/* yres_भव == 0 means use maximum */
			var->yres_भव = screen_len / linelen;
	पूर्ण अन्यथा अणु
		अगर (hwscroll < 0)
			var->yres_भव = 2 * var->yres;
		अन्यथा
			var->yres_भव = var->yres + hwscroll * 16;
	पूर्ण
	var->xoffset = 0;
	अगर (screen_base)
		var->yoffset = (par->screen_base - screen_base) / linelen;
	अन्यथा
		var->yoffset = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->vmode = FB_VMODE_NONINTERLACED;
	वापस 0;
पूर्ण

अटल व्योम tt_get_par(काष्ठा atafb_par *par)
अणु
	अचिन्हित दीर्घ addr;
	par->hw.tt.mode = shअगरter_tt.tt_shअगरपंचांगode;
	par->hw.tt.sync = shअगरter_st.syncmode;
	addr = ((shअगरter_st.bas_hi & 0xff) << 16) |
	       ((shअगरter_st.bas_md & 0xff) << 8)  |
	       ((shअगरter_st.bas_lo & 0xff));
	par->screen_base = atari_stram_to_virt(addr);
पूर्ण

अटल व्योम tt_set_par(काष्ठा atafb_par *par)
अणु
	shअगरter_tt.tt_shअगरपंचांगode = par->hw.tt.mode;
	shअगरter_st.syncmode = par->hw.tt.sync;
	/* only set screen_base अगर really necessary */
	अगर (current_par.screen_base != par->screen_base)
		fbhw->set_screen_base(par->screen_base);
पूर्ण

अटल पूर्णांक tt_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर ((shअगरter_tt.tt_shअगरपंचांगode & TT_SHIFTER_MODEMASK) == TT_SHIFTER_STHIGH)
		regno += 254;
	अगर (regno > 255)
		वापस 1;
	tt_palette[regno] = (((red >> 12) << 8) | ((green >> 12) << 4) |
			     (blue >> 12));
	अगर ((shअगरter_tt.tt_shअगरपंचांगode & TT_SHIFTER_MODEMASK) ==
	    TT_SHIFTER_STHIGH && regno == 254)
		tt_palette[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tt_detect(व्योम)
अणु
	काष्ठा atafb_par par;

	/* Determine the connected monitor: The DMA sound must be
	 * disabled beक्रमe पढ़ोing the MFP GPIP, because the Sound
	 * Done Signal and the Monochrome Detect are XORed together!
	 *
	 * Even on a TT, we should look अगर there is a DMA sound. It was
	 * announced that the Eagle is TT compatible, but only the PCM is
	 * missing...
	 */
	अगर (ATARIHW_PRESENT(PCM_8BIT)) अणु
		tt_dmasnd.ctrl = DMASND_CTRL_OFF;
		udelay(20);		/* रुको a जबतक क्रम things to settle करोwn */
	पूर्ण
	mono_moni = (st_mfp.par_dt_reg & 0x80) == 0;

	tt_get_par(&par);
	tt_encode_var(&atafb_predefined[0], &par);

	वापस 1;
पूर्ण

#पूर्ण_अगर /* ATAFB_TT */

/* ------------------- Falcon specअगरic functions ---------------------- */

#अगर_घोषित ATAFB_FALCON

अटल पूर्णांक mon_type;		/* Falcon connected monitor */
अटल पूर्णांक f030_bus_width;	/* Falcon ram bus width (क्रम vid_control) */
#घोषणा F_MON_SM	0
#घोषणा F_MON_SC	1
#घोषणा F_MON_VGA	2
#घोषणा F_MON_TV	3

अटल काष्ठा pixel_घड़ी अणु
	अचिन्हित दीर्घ f;	/* f/[Hz] */
	अचिन्हित दीर्घ t;	/* t/[ps] (=1/f) */
	पूर्णांक right, hsync, left;	/* standard timing in घड़ी cycles, not pixel */
	/* hsync initialized in falcon_detect() */
	पूर्णांक sync_mask;		/* or-mask क्रम hw.falcon.sync to set this घड़ी */
	पूर्णांक control_mask;	/* ditto, क्रम hw.falcon.vid_control */
पूर्ण f25 = अणु
	25175000, 39721, 18, 0, 42, 0x0, VCO_CLOCK25
पूर्ण, f32 = अणु
	32000000, 31250, 18, 0, 42, 0x0, 0
पूर्ण, fext = अणु
	0, 0, 18, 0, 42, 0x1, 0
पूर्ण;

/* VIDEL-prescale values [mon_type][pixel_length from VCO] */
अटल पूर्णांक vdl_prescale[4][3] = अणु
	अणु 4,2,1 पूर्ण, अणु 4,2,1 पूर्ण, अणु 4,2,2 पूर्ण, अणु 4,2,1 पूर्ण
पूर्ण;

/* Default hsync timing [mon_type] in picoseconds */
अटल दीर्घ h_syncs[4] = अणु 3000000, 4875000, 4000000, 4875000 पूर्ण;

अटल अंतरभूत पूर्णांक hxx_prescale(काष्ठा falcon_hw *hw)
अणु
	वापस hw->ste_mode ? 16
			    : vdl_prescale[mon_type][hw->vid_mode >> 2 & 0x3];
पूर्ण

अटल पूर्णांक falcon_encode_fix(काष्ठा fb_fix_screeninfo *fix,
			     काष्ठा atafb_par *par)
अणु
	म_नकल(fix->id, "Atari Builtin");
	fix->smem_start = phys_screen_base;
	fix->smem_len = screen_len;
	fix->type = FB_TYPE_INTERLEAVED_PLANES;
	fix->type_aux = 2;
	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	अगर (par->hw.falcon.mono) अणु
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		/* no smooth scrolling with दीर्घword aligned video mem */
		fix->xpanstep = 32;
	पूर्ण अन्यथा अगर (par->hw.falcon.f_shअगरt & 0x100) अणु
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		/* Is this ok or should it be सूचीECTCOLOR? */
		fix->visual = FB_VISUAL_TRUECOLOR;
		fix->xpanstep = 2;
	पूर्ण
	fix->line_length = par->next_line;
	fix->accel = FB_ACCEL_ATARIBLITT;
	वापस 0;
पूर्ण

अटल पूर्णांक falcon_decode_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा atafb_par *par)
अणु
	पूर्णांक bpp = var->bits_per_pixel;
	पूर्णांक xres = var->xres;
	पूर्णांक yres = var->yres;
	पूर्णांक xres_भव = var->xres_भव;
	पूर्णांक yres_भव = var->yres_भव;
	पूर्णांक left_margin, right_margin, hsync_len;
	पूर्णांक upper_margin, lower_margin, vsync_len;
	पूर्णांक linelen;
	पूर्णांक पूर्णांकerlace = 0, द्विगुनline = 0;
	काष्ठा pixel_घड़ी *pघड़ी;
	पूर्णांक plen;			/* width of pixel in घड़ी cycles */
	पूर्णांक xstretch;
	पूर्णांक prescale;
	पूर्णांक दीर्घoffset = 0;
	पूर्णांक hfreq, vfreq;
	पूर्णांक hdb_off, hde_off, base_off;
	पूर्णांक gstart, gend1, gend2, align;

/*
	Get the video params out of 'var'. If a value doesn't fit, round
	it up, अगर it's too big, वापस EINVAL.
	Round up in the following order: bits_per_pixel, xres, yres,
	xres_भव, yres_भव, xoffset, yoffset, grayscale, bitfields,
	horizontal timing, vertical timing.

	There is a maximum of screen resolution determined by pixelघड़ी
	and minimum frame rate -- (X+hmarg.)*(Y+vmarg.)*vfmin <= pixelघड़ी.
	In पूर्णांकerlace mode this is     "     *    "     *vfmin <= pixelघड़ी.
	Additional स्थिरraपूर्णांकs: hfreq.
	Frequency range क्रम multisync monitors is given via command line.
	For TV and SM124 both frequencies are fixed.

	X % 16 == 0 to fit 8x?? font (except 1 bitplane modes must use X%32 == 0)
	Y % 16 == 0 to fit 8x16 font
	Y % 8 == 0 अगर Y<400

	Currently पूर्णांकerlace and द्विगुनline mode in var are ignored.
	On SM124 and TV only the standard resolutions can be used.
*/

	/* Reject uninitialized mode */
	अगर (!xres || !yres || !bpp)
		वापस -EINVAL;

	अगर (mon_type == F_MON_SM && bpp != 1)
		वापस -EINVAL;

	अगर (bpp <= 1) अणु
		bpp = 1;
		par->hw.falcon.f_shअगरt = 0x400;
		par->hw.falcon.st_shअगरt = 0x200;
	पूर्ण अन्यथा अगर (bpp <= 2) अणु
		bpp = 2;
		par->hw.falcon.f_shअगरt = 0x000;
		par->hw.falcon.st_shअगरt = 0x100;
	पूर्ण अन्यथा अगर (bpp <= 4) अणु
		bpp = 4;
		par->hw.falcon.f_shअगरt = 0x000;
		par->hw.falcon.st_shअगरt = 0x000;
	पूर्ण अन्यथा अगर (bpp <= 8) अणु
		bpp = 8;
		par->hw.falcon.f_shअगरt = 0x010;
	पूर्ण अन्यथा अगर (bpp <= 16) अणु
		bpp = 16;		/* packed pixel mode */
		par->hw.falcon.f_shअगरt = 0x100;	/* hicolor, no overlay */
	पूर्ण अन्यथा
		वापस -EINVAL;
	par->hw.falcon.bpp = bpp;

	अगर (mon_type == F_MON_SM || DontCalcRes) अणु
		/* Skip all calculations. VGA/TV/SC1224 only supported. */
		काष्ठा fb_var_screeninfo *myvar = &atafb_predefined[0];

		अगर (bpp > myvar->bits_per_pixel ||
		    var->xres > myvar->xres ||
		    var->yres > myvar->yres)
			वापस -EINVAL;
		fbhw->get_par(par);	/* Current par will be new par */
		जाओ set_screen_base;	/* Don't क्रमget this */
	पूर्ण

	/* Only some fixed resolutions < 640x400 */
	अगर (xres <= 320)
		xres = 320;
	अन्यथा अगर (xres <= 640 && bpp != 16)
		xres = 640;
	अगर (yres <= 200)
		yres = 200;
	अन्यथा अगर (yres <= 240)
		yres = 240;
	अन्यथा अगर (yres <= 400)
		yres = 400;

	/* 2 planes must use STE compatibility mode */
	par->hw.falcon.ste_mode = bpp == 2;
	par->hw.falcon.mono = bpp == 1;

	/* Total and visible scanline length must be a multiple of one दीर्घword,
	 * this and the console fontwidth yields the alignment क्रम xres and
	 * xres_भव.
	 * TODO: this way "odd" fontheights are not supported
	 *
	 * Special हाल in STE mode: blank and graphic positions करोn't align,
	 * aव्योम trash at right margin
	 */
	अगर (par->hw.falcon.ste_mode)
		xres = (xres + 63) & ~63;
	अन्यथा अगर (bpp == 1)
		xres = (xres + 31) & ~31;
	अन्यथा
		xres = (xres + 15) & ~15;
	अगर (yres >= 400)
		yres = (yres + 15) & ~15;
	अन्यथा
		yres = (yres + 7) & ~7;

	अगर (xres_भव < xres)
		xres_भव = xres;
	अन्यथा अगर (bpp == 1)
		xres_भव = (xres_भव + 31) & ~31;
	अन्यथा
		xres_भव = (xres_भव + 15) & ~15;

	अगर (yres_भव <= 0)
		yres_भव = 0;
	अन्यथा अगर (yres_भव < yres)
		yres_भव = yres;

	/* backward bug-compatibility */
	अगर (var->pixघड़ी > 1)
		var->pixघड़ी -= 1;

	par->hw.falcon.line_width = bpp * xres / 16;
	par->hw.falcon.line_offset = bpp * (xres_भव - xres) / 16;

	/* single or द्विगुन pixel width */
	xstretch = (xres < 640) ? 2 : 1;

#अगर 0 /* SM124 supports only 640x400, this is rejected above */
	अगर (mon_type == F_MON_SM) अणु
		अगर (xres != 640 && yres != 400)
			वापस -EINVAL;
		plen = 1;
		pघड़ी = &f32;
		/* SM124-mode is special */
		par->hw.falcon.ste_mode = 1;
		par->hw.falcon.f_shअगरt = 0x000;
		par->hw.falcon.st_shअगरt = 0x200;
		left_margin = hsync_len = 128 / plen;
		right_margin = 0;
		/* TODO set all margins */
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (mon_type == F_MON_SC || mon_type == F_MON_TV) अणु
		plen = 2 * xstretch;
		अगर (var->pixघड़ी > f32.t * plen)
			वापस -EINVAL;
		pघड़ी = &f32;
		अगर (yres > 240)
			पूर्णांकerlace = 1;
		अगर (var->pixघड़ी == 0) अणु
			/* set some minimal margins which center the screen */
			left_margin = 32;
			right_margin = 18;
			hsync_len = pघड़ी->hsync / plen;
			upper_margin = 31;
			lower_margin = 14;
			vsync_len = पूर्णांकerlace ? 3 : 4;
		पूर्ण अन्यथा अणु
			left_margin = var->left_margin;
			right_margin = var->right_margin;
			hsync_len = var->hsync_len;
			upper_margin = var->upper_margin;
			lower_margin = var->lower_margin;
			vsync_len = var->vsync_len;
			अगर (var->vmode & FB_VMODE_INTERLACED) अणु
				upper_margin = (upper_margin + 1) / 2;
				lower_margin = (lower_margin + 1) / 2;
				vsync_len = (vsync_len + 1) / 2;
			पूर्ण अन्यथा अगर (var->vmode & FB_VMODE_DOUBLE) अणु
				upper_margin *= 2;
				lower_margin *= 2;
				vsync_len *= 2;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु			/* F_MON_VGA */
		अगर (bpp == 16)
			xstretch = 2;	/* Double pixel width only क्रम hicolor */
		/* Default values are used क्रम vert./hor. timing अगर no pixelघड़ी given. */
		अगर (var->pixघड़ी == 0) अणु
			पूर्णांक linesize;

			/* Choose master pixelघड़ी depending on hor. timing */
			plen = 1 * xstretch;
			अगर ((plen * xres + f25.right + f25.hsync + f25.left) *
			    fb_info.monspecs.hfmin < f25.f)
				pघड़ी = &f25;
			अन्यथा अगर ((plen * xres + f32.right + f32.hsync +
				  f32.left) * fb_info.monspecs.hfmin < f32.f)
				pघड़ी = &f32;
			अन्यथा अगर ((plen * xres + fext.right + fext.hsync +
				  fext.left) * fb_info.monspecs.hfmin < fext.f &&
			         fext.f)
				pघड़ी = &fext;
			अन्यथा
				वापस -EINVAL;

			left_margin = pघड़ी->left / plen;
			right_margin = pघड़ी->right / plen;
			hsync_len = pघड़ी->hsync / plen;
			linesize = left_margin + xres + right_margin + hsync_len;
			upper_margin = 31;
			lower_margin = 11;
			vsync_len = 3;
		पूर्ण अन्यथा अणु
			/* Choose largest pixelघड़ी <= wanted घड़ी */
			पूर्णांक i;
			अचिन्हित दीर्घ pcl = अच_दीर्घ_उच्च;
			pघड़ी = 0;
			क्रम (i = 1; i <= 4; i *= 2) अणु
				अगर (f25.t * i >= var->pixघड़ी &&
				    f25.t * i < pcl) अणु
					pcl = f25.t * i;
					pघड़ी = &f25;
				पूर्ण
				अगर (f32.t * i >= var->pixघड़ी &&
				    f32.t * i < pcl) अणु
					pcl = f32.t * i;
					pघड़ी = &f32;
				पूर्ण
				अगर (fext.t && fext.t * i >= var->pixघड़ी &&
				    fext.t * i < pcl) अणु
					pcl = fext.t * i;
					pघड़ी = &fext;
				पूर्ण
			पूर्ण
			अगर (!pघड़ी)
				वापस -EINVAL;
			plen = pcl / pघड़ी->t;

			left_margin = var->left_margin;
			right_margin = var->right_margin;
			hsync_len = var->hsync_len;
			upper_margin = var->upper_margin;
			lower_margin = var->lower_margin;
			vsync_len = var->vsync_len;
			/* Internal unit is [single lines per (half-)frame] */
			अगर (var->vmode & FB_VMODE_INTERLACED) अणु
				/* # lines in half frame */
				/* External unit is [lines per full frame] */
				upper_margin = (upper_margin + 1) / 2;
				lower_margin = (lower_margin + 1) / 2;
				vsync_len = (vsync_len + 1) / 2;
			पूर्ण अन्यथा अगर (var->vmode & FB_VMODE_DOUBLE) अणु
				/* External unit is [द्विगुन lines per frame] */
				upper_margin *= 2;
				lower_margin *= 2;
				vsync_len *= 2;
			पूर्ण
		पूर्ण
		अगर (pघड़ी == &fext)
			दीर्घoffset = 1;	/* VIDEL करोesn't synchronize on लघु offset */
	पूर्ण
	/* Is video bus bandwidth (32MB/s) too low क्रम this resolution? */
	/* this is definitely wrong अगर bus घड़ी != 32MHz */
	अगर (pघड़ी->f / plen / 8 * bpp > 32000000L)
		वापस -EINVAL;

	अगर (vsync_len < 1)
		vsync_len = 1;

	/* include sync lengths in right/lower margin क्रम all calculations */
	right_margin += hsync_len;
	lower_margin += vsync_len;

	/* ! In all calculations of margins we use # of lines in half frame
	 * (which is a full frame in non-पूर्णांकerlace mode), so we can चयन
	 * between पूर्णांकerlace and non-पूर्णांकerlace without messing around
	 * with these.
	 */
again:
	/* Set base_offset 128 and video bus width */
	par->hw.falcon.vid_control = mon_type | f030_bus_width;
	अगर (!दीर्घoffset)
		par->hw.falcon.vid_control |= VCO_SHORTOFFS;	/* base_offset 64 */
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		par->hw.falcon.vid_control |= VCO_HSYPOS;
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		par->hw.falcon.vid_control |= VCO_VSYPOS;
	/* Pixelघड़ी */
	par->hw.falcon.vid_control |= pघड़ी->control_mask;
	/* External or पूर्णांकernal घड़ी */
	par->hw.falcon.sync = pघड़ी->sync_mask | 0x2;
	/* Pixellength and prescale */
	par->hw.falcon.vid_mode = (2 / plen) << 2;
	अगर (द्विगुनline)
		par->hw.falcon.vid_mode |= VMO_DOUBLE;
	अगर (पूर्णांकerlace)
		par->hw.falcon.vid_mode |= VMO_INTER;

	/*********************
	 * Horizontal timing: unit = [master घड़ी cycles]
	 * unit of hxx-रेजिस्टरs: [master घड़ी cycles * prescale]
	 * Hxx-रेजिस्टरs are 9 bit wide
	 *
	 * 1 line = ((hht + 2) * 2 * prescale) घड़ी cycles
	 *
	 * graphic output = hdb & 0x200 ?
	 *        ((hht + 2) * 2 - hdb + hde) * prescale - hdboff + hdeoff:
	 *        (hht + 2  - hdb + hde) * prescale - hdboff + hdeoff
	 * (this must be a multiple of plen*128/bpp, on VGA pixels
	 *  to the right may be cut off with a bigger right margin)
	 *
	 * start of graphics relative to start of 1st halfline = hdb & 0x200 ?
	 *        (hdb - hht - 2) * prescale + hdboff :
	 *        hdb * prescale + hdboff
	 *
	 * end of graphics relative to start of 1st halfline =
	 *        (hde + hht + 2) * prescale + hdeoff
	 *********************/
	/* Calculate VIDEL रेजिस्टरs */
अणु
	prescale = hxx_prescale(&par->hw.falcon);
	base_off = par->hw.falcon.vid_control & VCO_SHORTOFFS ? 64 : 128;

	/* Offsets depend on video mode */
	/* Offsets are in घड़ी cycles, भागide by prescale to
	 * calculate hd[be]-रेजिस्टरs
	 */
	अगर (par->hw.falcon.f_shअगरt & 0x100) अणु
		align = 1;
		hde_off = 0;
		hdb_off = (base_off + 16 * plen) + prescale;
	पूर्ण अन्यथा अणु
		align = 128 / bpp;
		hde_off = ((128 / bpp + 2) * plen);
		अगर (par->hw.falcon.ste_mode)
			hdb_off = (64 + base_off + (128 / bpp + 2) * plen) + prescale;
		अन्यथा
			hdb_off = (base_off + (128 / bpp + 18) * plen) + prescale;
	पूर्ण

	gstart = (prescale / 2 + plen * left_margin) / prescale;
	/* gend1 is क्रम hde (gend-gstart multiple of align), shअगरter's xres */
	gend1 = gstart + roundup(xres, align) * plen / prescale;
	/* gend2 is क्रम hbb, visible xres (rest to gend1 is cut off by hblank) */
	gend2 = gstart + xres * plen / prescale;
	par->HHT = plen * (left_margin + xres + right_margin) /
			   (2 * prescale) - 2;
/*	par->HHT = (gend2 + plen * right_margin / prescale) / 2 - 2;*/

	par->HDB = gstart - hdb_off / prescale;
	par->HBE = gstart;
	अगर (par->HDB < 0)
		par->HDB += par->HHT + 2 + 0x200;
	par->HDE = gend1 - par->HHT - 2 - hde_off / prescale;
	par->HBB = gend2 - par->HHT - 2;
#अगर 0
	/* One more Videl स्थिरraपूर्णांक: data fetch of two lines must not overlap */
	अगर ((par->HDB & 0x200) && (par->HDB & ~0x200) - par->HDE <= 5) अणु
		/* अगर this happens increase margins, decrease hfreq. */
	पूर्ण
#पूर्ण_अगर
	अगर (hde_off % prescale)
		par->HBB++;		/* compensate क्रम non matching hde and hbb */
	par->HSS = par->HHT + 2 - plen * hsync_len / prescale;
	अगर (par->HSS < par->HBB)
		par->HSS = par->HBB;
पूर्ण

	/*  check hor. frequency */
	hfreq = pघड़ी->f / ((par->HHT + 2) * prescale * 2);
	अगर (hfreq > fb_info.monspecs.hfmax && mon_type != F_MON_VGA) अणु
		/* ++guenther:   ^^^^^^^^^^^^^^^^^^^ can't remember why I did this */
		/* Too high -> enlarge margin */
		left_margin += 1;
		right_margin += 1;
		जाओ again;
	पूर्ण
	अगर (hfreq > fb_info.monspecs.hfmax || hfreq < fb_info.monspecs.hfmin)
		वापस -EINVAL;

	/* Vxx-रेजिस्टरs */
	/* All Vxx must be odd in non-पूर्णांकerlace, since frame starts in the middle
	 * of the first displayed line!
	 * One frame consists of VFT+1 half lines. VFT+1 must be even in
	 * non-पूर्णांकerlace, odd in पूर्णांकerlace mode क्रम synchronisation.
	 * Vxx-रेजिस्टरs are 11 bit wide
	 */
	par->VBE = (upper_margin * 2 + 1); /* must begin on odd halfline */
	par->VDB = par->VBE;
	par->VDE = yres;
	अगर (!पूर्णांकerlace)
		par->VDE <<= 1;
	अगर (द्विगुनline)
		par->VDE <<= 1;		/* VDE now half lines per (half-)frame */
	par->VDE += par->VDB;
	par->VBB = par->VDE;
	par->VFT = par->VBB + (lower_margin * 2 - 1) - 1;
	par->VSS = par->VFT + 1 - (vsync_len * 2 - 1);
	/* vbb,vss,vft must be even in पूर्णांकerlace mode */
	अगर (पूर्णांकerlace) अणु
		par->VBB++;
		par->VSS++;
		par->VFT++;
	पूर्ण

	/* V-frequency check, hope I didn't create any loop here. */
	/* Interlace and द्विगुनline are mutually exclusive. */
	vfreq = (hfreq * 2) / (par->VFT + 1);
	अगर (vfreq > fb_info.monspecs.vfmax && !द्विगुनline && !पूर्णांकerlace) अणु
		/* Too high -> try again with द्विगुनline */
		द्विगुनline = 1;
		जाओ again;
	पूर्ण अन्यथा अगर (vfreq < fb_info.monspecs.vfmin && !पूर्णांकerlace && !द्विगुनline) अणु
		/* Too low -> try again with पूर्णांकerlace */
		पूर्णांकerlace = 1;
		जाओ again;
	पूर्ण अन्यथा अगर (vfreq < fb_info.monspecs.vfmin && द्विगुनline) अणु
		/* Doubleline too low -> clear द्विगुनline and enlarge margins */
		पूर्णांक lines;
		द्विगुनline = 0;
		क्रम (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines - 2 * yres) >
		     fb_info.monspecs.vfmax;
		     lines++)
			;
		upper_margin += lines;
		lower_margin += lines;
		जाओ again;
	पूर्ण अन्यथा अगर (vfreq > fb_info.monspecs.vfmax && द्विगुनline) अणु
		/* Doubleline too high -> enlarge margins */
		पूर्णांक lines;
		क्रम (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines) >
		     fb_info.monspecs.vfmax;
		     lines += 2)
			;
		upper_margin += lines;
		lower_margin += lines;
		जाओ again;
	पूर्ण अन्यथा अगर (vfreq > fb_info.monspecs.vfmax && पूर्णांकerlace) अणु
		/* Interlace, too high -> enlarge margins */
		पूर्णांक lines;
		क्रम (lines = 0;
		     (hfreq * 2) / (par->VFT + 1 + 4 * lines) >
		     fb_info.monspecs.vfmax;
		     lines++)
			;
		upper_margin += lines;
		lower_margin += lines;
		जाओ again;
	पूर्ण अन्यथा अगर (vfreq < fb_info.monspecs.vfmin ||
		   vfreq > fb_info.monspecs.vfmax)
		वापस -EINVAL;

set_screen_base:
	linelen = xres_भव * bpp / 8;
	अगर (yres_भव * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (yres * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (var->yoffset + yres > yres_भव && yres_भव)
		वापस -EINVAL;
	par->yres_भव = yres_भव;
	par->screen_base = screen_base + var->yoffset * linelen;
	par->hw.falcon.xoffset = 0;

	par->next_line = linelen;

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_encode_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा atafb_par *par)
अणु
/* !!! only क्रम VGA !!! */
	पूर्णांक linelen;
	पूर्णांक prescale, plen;
	पूर्णांक hdb_off, hde_off, base_off;
	काष्ठा falcon_hw *hw = &par->hw.falcon;

	स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));
	/* possible frequencies: 25.175 or 32MHz */
	var->pixघड़ी = hw->sync & 0x1 ? fext.t :
	                hw->vid_control & VCO_CLOCK25 ? f25.t : f32.t;

	var->height = -1;
	var->width = -1;

	var->sync = 0;
	अगर (hw->vid_control & VCO_HSYPOS)
		var->sync |= FB_SYNC_HOR_HIGH_ACT;
	अगर (hw->vid_control & VCO_VSYPOS)
		var->sync |= FB_SYNC_VERT_HIGH_ACT;

	var->vmode = FB_VMODE_NONINTERLACED;
	अगर (hw->vid_mode & VMO_INTER)
		var->vmode |= FB_VMODE_INTERLACED;
	अगर (hw->vid_mode & VMO_DOUBLE)
		var->vmode |= FB_VMODE_DOUBLE;

	/* visible y resolution:
	 * Graphics display starts at line VDB and ends at line
	 * VDE. If पूर्णांकerlace mode off unit of VC-रेजिस्टरs is
	 * half lines, अन्यथा lines.
	 */
	var->yres = hw->vde - hw->vdb;
	अगर (!(var->vmode & FB_VMODE_INTERLACED))
		var->yres >>= 1;
	अगर (var->vmode & FB_VMODE_DOUBLE)
		var->yres >>= 1;

	/*
	 * to get bpp, we must examine f_shअगरt and st_shअगरt.
	 * f_shअगरt is valid अगर any of bits no. 10, 8 or 4
	 * is set. Priority in f_shअगरt is: 10 ">" 8 ">" 4, i.e.
	 * अगर bit 10 set then bit 8 and bit 4 करोn't care...
	 * If all these bits are 0 get display depth from st_shअगरt
	 * (as क्रम ST and STE)
	 */
	अगर (hw->f_shअगरt & 0x400)	/* 2 colors */
		var->bits_per_pixel = 1;
	अन्यथा अगर (hw->f_shअगरt & 0x100)	/* hicolor */
		var->bits_per_pixel = 16;
	अन्यथा अगर (hw->f_shअगरt & 0x010)	/* 8 bitplanes */
		var->bits_per_pixel = 8;
	अन्यथा अगर (hw->st_shअगरt == 0)
		var->bits_per_pixel = 4;
	अन्यथा अगर (hw->st_shअगरt == 0x100)
		var->bits_per_pixel = 2;
	अन्यथा				/* अगर (hw->st_shअगरt == 0x200) */
		var->bits_per_pixel = 1;

	var->xres = hw->line_width * 16 / var->bits_per_pixel;
	var->xres_भव = var->xres + hw->line_offset * 16 / var->bits_per_pixel;
	अगर (hw->xoffset)
		var->xres_भव += 16;

	अगर (var->bits_per_pixel == 16) अणु
		var->red.offset = 11;
		var->red.length = 5;
		var->red.msb_right = 0;
		var->green.offset = 5;
		var->green.length = 6;
		var->green.msb_right = 0;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->blue.msb_right = 0;
	पूर्ण अन्यथा अणु
		var->red.offset = 0;
		var->red.length = hw->ste_mode ? 4 : 6;
		अगर (var->red.length > var->bits_per_pixel)
			var->red.length = var->bits_per_pixel;
		var->red.msb_right = 0;
		var->grayscale = 0;
		var->blue = var->green = var->red;
	पूर्ण
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;

	linelen = var->xres_भव * var->bits_per_pixel / 8;
	अगर (screen_len) अणु
		अगर (par->yres_भव)
			var->yres_भव = par->yres_भव;
		अन्यथा
			/* yres_भव == 0 means use maximum */
			var->yres_भव = screen_len / linelen;
	पूर्ण अन्यथा अणु
		अगर (hwscroll < 0)
			var->yres_भव = 2 * var->yres;
		अन्यथा
			var->yres_भव = var->yres + hwscroll * 16;
	पूर्ण
	var->xoffset = 0;		/* TODO change this */

	/* hdX-offsets */
	prescale = hxx_prescale(hw);
	plen = 4 >> (hw->vid_mode >> 2 & 0x3);
	base_off = hw->vid_control & VCO_SHORTOFFS ? 64 : 128;
	अगर (hw->f_shअगरt & 0x100) अणु
		hde_off = 0;
		hdb_off = (base_off + 16 * plen) + prescale;
	पूर्ण अन्यथा अणु
		hde_off = ((128 / var->bits_per_pixel + 2) * plen);
		अगर (hw->ste_mode)
			hdb_off = (64 + base_off + (128 / var->bits_per_pixel + 2) * plen)
					 + prescale;
		अन्यथा
			hdb_off = (base_off + (128 / var->bits_per_pixel + 18) * plen)
					 + prescale;
	पूर्ण

	/* Right margin includes hsync */
	var->left_margin = hdb_off + prescale * ((hw->hdb & 0x1ff) -
					   (hw->hdb & 0x200 ? 2 + hw->hht : 0));
	अगर (hw->ste_mode || mon_type != F_MON_VGA)
		var->right_margin = prescale * (hw->hht + 2 - hw->hde) - hde_off;
	अन्यथा
		/* can't use this in ste_mode, because hbb is +1 off */
		var->right_margin = prescale * (hw->hht + 2 - hw->hbb);
	var->hsync_len = prescale * (hw->hht + 2 - hw->hss);

	/* Lower margin includes vsync */
	var->upper_margin = hw->vdb / 2;	/* round करोwn to full lines */
	var->lower_margin = (hw->vft + 1 - hw->vde + 1) / 2;	/* round up */
	var->vsync_len = (hw->vft + 1 - hw->vss + 1) / 2;	/* round up */
	अगर (var->vmode & FB_VMODE_INTERLACED) अणु
		var->upper_margin *= 2;
		var->lower_margin *= 2;
		var->vsync_len *= 2;
	पूर्ण अन्यथा अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		var->upper_margin = (var->upper_margin + 1) / 2;
		var->lower_margin = (var->lower_margin + 1) / 2;
		var->vsync_len = (var->vsync_len + 1) / 2;
	पूर्ण

	var->pixघड़ी *= plen;
	var->left_margin /= plen;
	var->right_margin /= plen;
	var->hsync_len /= plen;

	var->right_margin -= var->hsync_len;
	var->lower_margin -= var->vsync_len;

	अगर (screen_base)
		var->yoffset = (par->screen_base - screen_base) / linelen;
	अन्यथा
		var->yoffset = 0;
	var->nonstd = 0;		/* what is this क्रम? */
	var->activate = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक f_change_mode;
अटल काष्ठा falcon_hw f_new_mode;
अटल पूर्णांक f_pan_display;

अटल व्योम falcon_get_par(काष्ठा atafb_par *par)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा falcon_hw *hw = &par->hw.falcon;

	hw->line_width = shअगरter_f030.scn_width;
	hw->line_offset = shअगरter_f030.off_next;
	hw->st_shअगरt = videl.st_shअगरt & 0x300;
	hw->f_shअगरt = videl.f_shअगरt;
	hw->vid_control = videl.control;
	hw->vid_mode = videl.mode;
	hw->sync = shअगरter_st.syncmode & 0x1;
	hw->xoffset = videl.xoffset & 0xf;
	hw->hht = videl.hht;
	hw->hbb = videl.hbb;
	hw->hbe = videl.hbe;
	hw->hdb = videl.hdb;
	hw->hde = videl.hde;
	hw->hss = videl.hss;
	hw->vft = videl.vft;
	hw->vbb = videl.vbb;
	hw->vbe = videl.vbe;
	hw->vdb = videl.vdb;
	hw->vde = videl.vde;
	hw->vss = videl.vss;

	addr = (shअगरter_st.bas_hi & 0xff) << 16 |
	       (shअगरter_st.bas_md & 0xff) << 8  |
	       (shअगरter_st.bas_lo & 0xff);
	par->screen_base = atari_stram_to_virt(addr);

	/* derived parameters */
	hw->ste_mode = (hw->f_shअगरt & 0x510) == 0 && hw->st_shअगरt == 0x100;
	hw->mono = (hw->f_shअगरt & 0x400) ||
	           ((hw->f_shअगरt & 0x510) == 0 && hw->st_shअगरt == 0x200);
पूर्ण

अटल व्योम falcon_set_par(काष्ठा atafb_par *par)
अणु
	f_change_mode = 0;

	/* only set screen_base अगर really necessary */
	अगर (current_par.screen_base != par->screen_base)
		fbhw->set_screen_base(par->screen_base);

	/* Don't touch any other रेजिस्टरs अगर we keep the शेष resolution */
	अगर (DontCalcRes)
		वापस;

	/* Tell vbl-handler to change video mode.
	 * We change modes only on next VBL, to aव्योम desynchronisation
	 * (a shअगरt to the right and wrap around by a अक्रमom number of pixels
	 * in all monochrome modes).
	 * This seems to work on my Falcon.
	 */
	f_new_mode = par->hw.falcon;
	f_change_mode = 1;
पूर्ण

अटल irqवापस_t falcon_vbl_चयनer(पूर्णांक irq, व्योम *dummy)
अणु
	काष्ठा falcon_hw *hw = &f_new_mode;

	अगर (f_change_mode) अणु
		f_change_mode = 0;

		अगर (hw->sync & 0x1) अणु
			/* Enable बाह्यal pixelघड़ी. This code only क्रम ScreenWonder */
			*(अस्थिर अचिन्हित लघु *)0xffff9202 = 0xffbf;
		पूर्ण अन्यथा अणु
			/* Turn off बाह्यal घड़ीs. Read sets all output bits to 1. */
			*(अस्थिर अचिन्हित लघु *)0xffff9202;
		पूर्ण
		shअगरter_st.syncmode = hw->sync;

		videl.hht = hw->hht;
		videl.hbb = hw->hbb;
		videl.hbe = hw->hbe;
		videl.hdb = hw->hdb;
		videl.hde = hw->hde;
		videl.hss = hw->hss;
		videl.vft = hw->vft;
		videl.vbb = hw->vbb;
		videl.vbe = hw->vbe;
		videl.vdb = hw->vdb;
		videl.vde = hw->vde;
		videl.vss = hw->vss;

		videl.f_shअगरt = 0;	/* ग_लिखो enables Falcon palette, 0: 4 planes */
		अगर (hw->ste_mode) अणु
			videl.st_shअगरt = hw->st_shअगरt;	/* ग_लिखो enables STE palette */
		पूर्ण अन्यथा अणु
			/* IMPORTANT:
			 * set st_shअगरt 0, so we can tell the screen-depth अगर f_shअगरt == 0.
			 * Writing 0 to f_shअगरt enables 4 plane Falcon mode but
			 * करोesn't set st_shअगरt. st_shअगरt != 0 (!= 4planes) is impossible
			 * with Falcon palette.
			 */
			videl.st_shअगरt = 0;
			/* now back to Falcon palette mode */
			videl.f_shअगरt = hw->f_shअगरt;
		पूर्ण
		/* writing to st_shअगरt changed scn_width and vid_mode */
		videl.xoffset = hw->xoffset;
		shअगरter_f030.scn_width = hw->line_width;
		shअगरter_f030.off_next = hw->line_offset;
		videl.control = hw->vid_control;
		videl.mode = hw->vid_mode;
	पूर्ण
	अगर (f_pan_display) अणु
		f_pan_display = 0;
		videl.xoffset = current_par.hw.falcon.xoffset;
		shअगरter_f030.off_next = current_par.hw.falcon.line_offset;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक falcon_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;

	पूर्णांक xoffset;
	पूर्णांक bpp = info->var.bits_per_pixel;

	अगर (bpp == 1)
		var->xoffset = up(var->xoffset, 32);
	अगर (bpp != 16)
		par->hw.falcon.xoffset = var->xoffset & 15;
	अन्यथा अणु
		par->hw.falcon.xoffset = 0;
		var->xoffset = up(var->xoffset, 2);
	पूर्ण
	par->hw.falcon.line_offset = bpp *
		(info->var.xres_भव - info->var.xres) / 16;
	अगर (par->hw.falcon.xoffset)
		par->hw.falcon.line_offset -= bpp;
	xoffset = var->xoffset - par->hw.falcon.xoffset;

	par->screen_base = screen_base +
	        (var->yoffset * info->var.xres_भव + xoffset) * bpp / 8;
	अगर (fbhw->set_screen_base)
		fbhw->set_screen_base(par->screen_base);
	अन्यथा
		वापस -EINVAL;		/* shouldn't happen */
	f_pan_display = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक falcon_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			    अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			    अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno > 255)
		वापस 1;
	f030_col[regno] = (((red & 0xfc00) << 16) |
			   ((green & 0xfc00) << 8) |
			   ((blue & 0xfc00) >> 8));
	अगर (regno < 16) अणु
		shअगरter_tt.color_reg[regno] =
			(((red & 0xe000) >> 13) | ((red & 0x1000) >> 12) << 8) |
			(((green & 0xe000) >> 13) | ((green & 0x1000) >> 12) << 4) |
			((blue & 0xe000) >> 13) | ((blue & 0x1000) >> 12);
		((u32 *)info->pseuकरो_palette)[regno] = ((red & 0xf800) |
						       ((green & 0xfc00) >> 5) |
						       ((blue & 0xf800) >> 11));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक falcon_blank(पूर्णांक blank_mode)
अणु
	/* ++guenther: we can चयन off graphics by changing VDB and VDE,
	 * so VIDEL करोesn't hog the bus जबतक saving.
	 * (this may affect usleep()).
	 */
	पूर्णांक vdb, vss, hbe, hss;

	अगर (mon_type == F_MON_SM)	/* this करोesn't work on SM124 */
		वापस 1;

	vdb = current_par.VDB;
	vss = current_par.VSS;
	hbe = current_par.HBE;
	hss = current_par.HSS;

	अगर (blank_mode >= 1) अणु
		/* disable graphics output (this speeds up the CPU) ... */
		vdb = current_par.VFT + 1;
		/* ... and blank all lines */
		hbe = current_par.HHT + 2;
	पूर्ण
	/* use VESA suspend modes on VGA monitors */
	अगर (mon_type == F_MON_VGA) अणु
		अगर (blank_mode == 2 || blank_mode == 4)
			vss = current_par.VFT + 1;
		अगर (blank_mode == 3 || blank_mode == 4)
			hss = current_par.HHT + 2;
	पूर्ण

	videl.vdb = vdb;
	videl.vss = vss;
	videl.hbe = hbe;
	videl.hss = hss;

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_detect(व्योम)
अणु
	काष्ठा atafb_par par;
	अचिन्हित अक्षर fhw;

	/* Determine connected monitor and set monitor parameters */
	fhw = *(अचिन्हित अक्षर *)0xffff8006;
	mon_type = fhw >> 6 & 0x3;
	/* bit 1 of fhw: 1=32 bit ram bus, 0=16 bit */
	f030_bus_width = fhw << 6 & 0x80;
	चयन (mon_type) अणु
	हाल F_MON_SM:
		fb_info.monspecs.vfmin = 70;
		fb_info.monspecs.vfmax = 72;
		fb_info.monspecs.hfmin = 35713;
		fb_info.monspecs.hfmax = 35715;
		अवरोध;
	हाल F_MON_SC:
	हाल F_MON_TV:
		/* PAL...NTSC */
		fb_info.monspecs.vfmin = 49;	/* not 50, since TOS शेषs to 49.9x Hz */
		fb_info.monspecs.vfmax = 60;
		fb_info.monspecs.hfmin = 15620;
		fb_info.monspecs.hfmax = 15755;
		अवरोध;
	पूर्ण
	/* initialize hsync-len */
	f25.hsync = h_syncs[mon_type] / f25.t;
	f32.hsync = h_syncs[mon_type] / f32.t;
	अगर (fext.t)
		fext.hsync = h_syncs[mon_type] / fext.t;

	falcon_get_par(&par);
	falcon_encode_var(&atafb_predefined[0], &par);

	/* Detected mode is always the "autodetect" slot */
	वापस 1;
पूर्ण

#पूर्ण_अगर /* ATAFB_FALCON */

/* ------------------- ST(E) specअगरic functions ---------------------- */

#अगर_घोषित ATAFB_STE

अटल पूर्णांक stste_encode_fix(काष्ठा fb_fix_screeninfo *fix,
			    काष्ठा atafb_par *par)
अणु
	पूर्णांक mode;

	म_नकल(fix->id, "Atari Builtin");
	fix->smem_start = phys_screen_base;
	fix->smem_len = screen_len;
	fix->type = FB_TYPE_INTERLEAVED_PLANES;
	fix->type_aux = 2;
	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	mode = par->hw.st.mode & 3;
	अगर (mode == ST_HIGH) अणु
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->type_aux = 0;
		fix->visual = FB_VISUAL_MONO10;
	पूर्ण
	अगर (ATARIHW_PRESENT(EXTD_SHIFTER)) अणु
		fix->xpanstep = 16;
		fix->ypanstep = 1;
	पूर्ण अन्यथा अणु
		fix->xpanstep = 0;
		fix->ypanstep = 0;
	पूर्ण
	fix->ywrapstep = 0;
	fix->line_length = par->next_line;
	fix->accel = FB_ACCEL_ATARIBLITT;
	वापस 0;
पूर्ण

अटल पूर्णांक stste_decode_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा atafb_par *par)
अणु
	पूर्णांक xres = var->xres;
	पूर्णांक yres = var->yres;
	पूर्णांक bpp = var->bits_per_pixel;
	पूर्णांक linelen;
	पूर्णांक yres_भव = var->yres_भव;

	अगर (mono_moni) अणु
		अगर (bpp > 1 || xres > sttt_xres || yres > st_yres)
			वापस -EINVAL;
		par->hw.st.mode = ST_HIGH;
		xres = sttt_xres;
		yres = st_yres;
		bpp = 1;
	पूर्ण अन्यथा अणु
		अगर (bpp > 4 || xres > sttt_xres || yres > st_yres)
			वापस -EINVAL;
		अगर (bpp > 2) अणु
			अगर (xres > sttt_xres / 2 || yres > st_yres / 2)
				वापस -EINVAL;
			par->hw.st.mode = ST_LOW;
			xres = sttt_xres / 2;
			yres = st_yres / 2;
			bpp = 4;
		पूर्ण अन्यथा अगर (bpp > 1) अणु
			अगर (xres > sttt_xres || yres > st_yres / 2)
				वापस -EINVAL;
			par->hw.st.mode = ST_MID;
			xres = sttt_xres;
			yres = st_yres / 2;
			bpp = 2;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण
	अगर (yres_भव <= 0)
		yres_भव = 0;
	अन्यथा अगर (yres_भव < yres)
		yres_भव = yres;
	अगर (var->sync & FB_SYNC_EXT)
		par->hw.st.sync = (par->hw.st.sync & ~1) | 1;
	अन्यथा
		par->hw.st.sync = (par->hw.st.sync & ~1);
	linelen = xres * bpp / 8;
	अगर (yres_भव * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (yres * linelen > screen_len && screen_len)
		वापस -EINVAL;
	अगर (var->yoffset + yres > yres_भव && yres_भव)
		वापस -EINVAL;
	par->yres_भव = yres_भव;
	par->screen_base = screen_base + var->yoffset * linelen;
	par->next_line = linelen;
	वापस 0;
पूर्ण

अटल पूर्णांक stste_encode_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा atafb_par *par)
अणु
	पूर्णांक linelen;
	स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));
	var->red.offset = 0;
	var->red.length = ATARIHW_PRESENT(EXTD_SHIFTER) ? 4 : 3;
	var->red.msb_right = 0;
	var->grayscale = 0;

	var->pixघड़ी = 31041;
	var->left_margin = 120;		/* these are incorrect */
	var->right_margin = 100;
	var->upper_margin = 8;
	var->lower_margin = 16;
	var->hsync_len = 140;
	var->vsync_len = 30;

	var->height = -1;
	var->width = -1;

	अगर (!(par->hw.st.sync & 1))
		var->sync = 0;
	अन्यथा
		var->sync = FB_SYNC_EXT;

	चयन (par->hw.st.mode & 3) अणु
	हाल ST_LOW:
		var->xres = sttt_xres / 2;
		var->yres = st_yres / 2;
		var->bits_per_pixel = 4;
		अवरोध;
	हाल ST_MID:
		var->xres = sttt_xres;
		var->yres = st_yres / 2;
		var->bits_per_pixel = 2;
		अवरोध;
	हाल ST_HIGH:
		var->xres = sttt_xres;
		var->yres = st_yres;
		var->bits_per_pixel = 1;
		अवरोध;
	पूर्ण
	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->xres_भव = sttt_xres_भव;
	linelen = var->xres_भव * var->bits_per_pixel / 8;
	ovsc_addlen = linelen * (sttt_yres_भव - st_yres);

	अगर (!use_hwscroll)
		var->yres_भव = var->yres;
	अन्यथा अगर (screen_len) अणु
		अगर (par->yres_भव)
			var->yres_भव = par->yres_भव;
		अन्यथा
			/* yres_भव == 0 means use maximum */
			var->yres_भव = screen_len / linelen;
	पूर्ण अन्यथा अणु
		अगर (hwscroll < 0)
			var->yres_भव = 2 * var->yres;
		अन्यथा
			var->yres_भव = var->yres + hwscroll * 16;
	पूर्ण
	var->xoffset = 0;
	अगर (screen_base)
		var->yoffset = (par->screen_base - screen_base) / linelen;
	अन्यथा
		var->yoffset = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->vmode = FB_VMODE_NONINTERLACED;
	वापस 0;
पूर्ण

अटल व्योम stste_get_par(काष्ठा atafb_par *par)
अणु
	अचिन्हित दीर्घ addr;
	par->hw.st.mode = shअगरter_tt.st_shअगरपंचांगode;
	par->hw.st.sync = shअगरter_st.syncmode;
	addr = ((shअगरter_st.bas_hi & 0xff) << 16) |
	       ((shअगरter_st.bas_md & 0xff) << 8);
	अगर (ATARIHW_PRESENT(EXTD_SHIFTER))
		addr |= (shअगरter_st.bas_lo & 0xff);
	par->screen_base = atari_stram_to_virt(addr);
पूर्ण

अटल व्योम stste_set_par(काष्ठा atafb_par *par)
अणु
	shअगरter_tt.st_shअगरपंचांगode = par->hw.st.mode;
	shअगरter_st.syncmode = par->hw.st.sync;
	/* only set screen_base अगर really necessary */
	अगर (current_par.screen_base != par->screen_base)
		fbhw->set_screen_base(par->screen_base);
पूर्ण

अटल पूर्णांक stste_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			   अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			   अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno > 15)
		वापस 1;
	red >>= 12;
	blue >>= 12;
	green >>= 12;
	अगर (ATARIHW_PRESENT(EXTD_SHIFTER))
		shअगरter_tt.color_reg[regno] =
			(((red & 0xe) >> 1) | ((red & 1) << 3) << 8) |
			(((green & 0xe) >> 1) | ((green & 1) << 3) << 4) |
			((blue & 0xe) >> 1) | ((blue & 1) << 3);
	अन्यथा
		shअगरter_tt.color_reg[regno] =
			((red & 0xe) << 7) |
			((green & 0xe) << 3) |
			((blue & 0xe) >> 1);
	वापस 0;
पूर्ण

अटल पूर्णांक stste_detect(व्योम)
अणु
	काष्ठा atafb_par par;

	/* Determine the connected monitor: The DMA sound must be
	 * disabled beक्रमe पढ़ोing the MFP GPIP, because the Sound
	 * Done Signal and the Monochrome Detect are XORed together!
	 */
	अगर (ATARIHW_PRESENT(PCM_8BIT)) अणु
		tt_dmasnd.ctrl = DMASND_CTRL_OFF;
		udelay(20);		/* रुको a जबतक क्रम things to settle करोwn */
	पूर्ण
	mono_moni = (st_mfp.par_dt_reg & 0x80) == 0;

	stste_get_par(&par);
	stste_encode_var(&atafb_predefined[0], &par);

	अगर (!ATARIHW_PRESENT(EXTD_SHIFTER))
		use_hwscroll = 0;
	वापस 1;
पूर्ण

अटल व्योम stste_set_screen_base(व्योम *s_base)
अणु
	अचिन्हित दीर्घ addr;
	addr = atari_stram_to_phys(s_base);
	/* Setup Screen Memory */
	shअगरter_st.bas_hi = (अचिन्हित अक्षर)((addr & 0xff0000) >> 16);
	shअगरter_st.bas_md = (अचिन्हित अक्षर)((addr & 0x00ff00) >> 8);
	अगर (ATARIHW_PRESENT(EXTD_SHIFTER))
		shअगरter_st.bas_lo = (अचिन्हित अक्षर)(addr & 0x0000ff);
पूर्ण

#पूर्ण_अगर /* ATAFB_STE */

/* Switching the screen size should be करोne during vsync, otherwise
 * the margins may get messed up. This is a well known problem of
 * the ST's video प्रणाली.
 *
 * Unक्रमtunately there is hardly any way to find the vsync, as the
 * vertical blank पूर्णांकerrupt is no दीर्घer in समय on machines with
 * overscan type modअगरications.
 *
 * We can, however, use Timer B to safely detect the black shoulder,
 * but then we've got to guess an appropriate delay to find the vsync.
 * This might not work on every machine.
 *
 * martin_rogge @ ki.maus.de, 8th Aug 1995
 */

#घोषणा LINE_DELAY  (mono_moni ? 30 : 70)
#घोषणा SYNC_DELAY  (mono_moni ? 1500 : 2000)

/* SWITCH_ACIA may be used क्रम Falcon (ScreenBlaster III पूर्णांकernal!) */
अटल व्योम st_ovsc_चयन(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	रेजिस्टर अचिन्हित अक्षर old, new;

	अगर (!(atari_चयनes & ATARI_SWITCH_OVSC_MASK))
		वापस;
	local_irq_save(flags);

	st_mfp.tim_ct_b = 0x10;
	st_mfp.active_edge |= 8;
	st_mfp.tim_ct_b = 0;
	st_mfp.tim_dt_b = 0xf0;
	st_mfp.tim_ct_b = 8;
	जबतक (st_mfp.tim_dt_b > 1)	/* TOS करोes it this way, करोn't ask why */
		;
	new = st_mfp.tim_dt_b;
	करो अणु
		udelay(LINE_DELAY);
		old = new;
		new = st_mfp.tim_dt_b;
	पूर्ण जबतक (old != new);
	st_mfp.tim_ct_b = 0x10;
	udelay(SYNC_DELAY);

	अगर (atari_चयनes & ATARI_SWITCH_OVSC_IKBD)
		acia.key_ctrl = ACIA_DIV64 | ACIA_D8N1S | ACIA_RHTID | ACIA_RIE;
	अगर (atari_चयनes & ATARI_SWITCH_OVSC_MIDI)
		acia.mid_ctrl = ACIA_DIV16 | ACIA_D8N1S | ACIA_RHTID;
	अगर (atari_चयनes & (ATARI_SWITCH_OVSC_SND6|ATARI_SWITCH_OVSC_SND7)) अणु
		sound_ym.rd_data_reg_sel = 14;
		sound_ym.wd_data = sound_ym.rd_data_reg_sel |
				   ((atari_चयनes & ATARI_SWITCH_OVSC_SND6) ? 0x40:0) |
				   ((atari_चयनes & ATARI_SWITCH_OVSC_SND7) ? 0x80:0);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/* ------------------- External Video ---------------------- */

#अगर_घोषित ATAFB_EXT

अटल पूर्णांक ext_encode_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा atafb_par *par)
अणु
	म_नकल(fix->id, "Unknown Extern");
	fix->smem_start = बाह्यal_addr;
	fix->smem_len = PAGE_ALIGN(बाह्यal_len);
	अगर (बाह्यal_depth == 1) अणु
		fix->type = FB_TYPE_PACKED_PIXELS;
		/* The letters 'n' and 'i' in the "atavideo=external:" stand
		 * क्रम "normal" and "inverted", rsp., in the monochrome हाल */
		fix->visual =
			(बाह्यal_pmode == FB_TYPE_INTERLEAVED_PLANES ||
			 बाह्यal_pmode == FB_TYPE_PACKED_PIXELS) ?
				FB_VISUAL_MONO10 : FB_VISUAL_MONO01;
	पूर्ण अन्यथा अणु
		/* Use STATIC अगर we करोn't know how to access color रेजिस्टरs */
		पूर्णांक visual = बाह्यal_vgaiobase ?
					 FB_VISUAL_PSEUDOCOLOR :
					 FB_VISUAL_STATIC_PSEUDOCOLOR;
		चयन (बाह्यal_pmode) अणु
		हाल -1:		/* truecolor */
			fix->type = FB_TYPE_PACKED_PIXELS;
			fix->visual = FB_VISUAL_TRUECOLOR;
			अवरोध;
		हाल FB_TYPE_PACKED_PIXELS:
			fix->type = FB_TYPE_PACKED_PIXELS;
			fix->visual = visual;
			अवरोध;
		हाल FB_TYPE_PLANES:
			fix->type = FB_TYPE_PLANES;
			fix->visual = visual;
			अवरोध;
		हाल FB_TYPE_INTERLEAVED_PLANES:
			fix->type = FB_TYPE_INTERLEAVED_PLANES;
			fix->type_aux = 2;
			fix->visual = visual;
			अवरोध;
		पूर्ण
	पूर्ण
	fix->xpanstep = 0;
	fix->ypanstep = 0;
	fix->ywrapstep = 0;
	fix->line_length = par->next_line;
	वापस 0;
पूर्ण

अटल पूर्णांक ext_decode_var(काष्ठा fb_var_screeninfo *var, काष्ठा atafb_par *par)
अणु
	काष्ठा fb_var_screeninfo *myvar = &atafb_predefined[0];

	अगर (var->bits_per_pixel > myvar->bits_per_pixel ||
	    var->xres > myvar->xres ||
	    var->xres_भव > myvar->xres_भव ||
	    var->yres > myvar->yres ||
	    var->xoffset > 0 ||
	    var->yoffset > 0)
		वापस -EINVAL;

	par->next_line = बाह्यal_xres_भव * बाह्यal_depth / 8;
	वापस 0;
पूर्ण

अटल पूर्णांक ext_encode_var(काष्ठा fb_var_screeninfo *var, काष्ठा atafb_par *par)
अणु
	स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));
	var->red.offset = 0;
	var->red.length = (बाह्यal_pmode == -1) ? बाह्यal_depth / 3 :
			(बाह्यal_vgaiobase ? बाह्यal_bitspercol : 0);
	var->red.msb_right = 0;
	var->grayscale = 0;

	var->pixघड़ी = 31041;
	var->left_margin = 120;		/* these are surely incorrect */
	var->right_margin = 100;
	var->upper_margin = 8;
	var->lower_margin = 16;
	var->hsync_len = 140;
	var->vsync_len = 30;

	var->height = -1;
	var->width = -1;

	var->sync = 0;

	var->xres = बाह्यal_xres;
	var->yres = बाह्यal_yres;
	var->xres_भव = बाह्यal_xres_भव;
	var->bits_per_pixel = बाह्यal_depth;

	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->yres_भव = var->yres;
	var->xoffset = 0;
	var->yoffset = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->vmode = FB_VMODE_NONINTERLACED;
	वापस 0;
पूर्ण

अटल व्योम ext_get_par(काष्ठा atafb_par *par)
अणु
	par->screen_base = बाह्यal_screen_base;
पूर्ण

अटल व्योम ext_set_par(काष्ठा atafb_par *par)
अणु
पूर्ण

#घोषणा OUTB(port,val) \
	*((अचिन्हित अस्थिर अक्षर *) ((port)+बाह्यal_vgaiobase)) = (val)
#घोषणा INB(port) \
	(*((अचिन्हित अस्थिर अक्षर *) ((port)+बाह्यal_vgaiobase)))
#घोषणा DACDelay				\
	करो अणु					\
		अचिन्हित अक्षर पंचांगp = INB(0x3da);	\
		पंचांगp = INB(0x3da);			\
	पूर्ण जबतक (0)

अटल पूर्णांक ext_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			 अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			 अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अचिन्हित अक्षर colmask = (1 << बाह्यal_bitspercol) - 1;

	अगर (!बाह्यal_vgaiobase)
		वापस 1;

	अगर (regno > 255)
		वापस 1;

	चयन (बाह्यal_card_type) अणु
	हाल IS_VGA:
		OUTB(0x3c8, regno);
		DACDelay;
		OUTB(0x3c9, red & colmask);
		DACDelay;
		OUTB(0x3c9, green & colmask);
		DACDelay;
		OUTB(0x3c9, blue & colmask);
		DACDelay;
		वापस 0;

	हाल IS_MV300:
		OUTB((MV300_reg[regno] << 2) + 1, red);
		OUTB((MV300_reg[regno] << 2) + 1, green);
		OUTB((MV300_reg[regno] << 2) + 1, blue);
		वापस 0;

	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक ext_detect(व्योम)
अणु
	काष्ठा fb_var_screeninfo *myvar = &atafb_predefined[0];
	काष्ठा atafb_par dummy_par;

	myvar->xres = बाह्यal_xres;
	myvar->xres_भव = बाह्यal_xres_भव;
	myvar->yres = बाह्यal_yres;
	myvar->bits_per_pixel = बाह्यal_depth;
	ext_encode_var(myvar, &dummy_par);
	वापस 1;
पूर्ण

#पूर्ण_अगर /* ATAFB_EXT */

/* ------ This is the same क्रम most hardware types -------- */

अटल व्योम set_screen_base(व्योम *s_base)
अणु
	अचिन्हित दीर्घ addr;

	addr = atari_stram_to_phys(s_base);
	/* Setup Screen Memory */
	shअगरter_st.bas_hi = (अचिन्हित अक्षर)((addr & 0xff0000) >> 16);
	shअगरter_st.bas_md = (अचिन्हित अक्षर)((addr & 0x00ff00) >> 8);
	shअगरter_st.bas_lo = (अचिन्हित अक्षर)(addr & 0x0000ff);
पूर्ण

अटल पूर्णांक pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;

	अगर (!fbhw->set_screen_base ||
	    (!ATARIHW_PRESENT(EXTD_SHIFTER) && var->xoffset))
		वापस -EINVAL;
	var->xoffset = up(var->xoffset, 16);
	par->screen_base = screen_base +
	        (var->yoffset * info->var.xres_भव + var->xoffset)
	        * info->var.bits_per_pixel / 8;
	fbhw->set_screen_base(par->screen_base);
	वापस 0;
पूर्ण

/* ------------ Interfaces to hardware functions ------------ */

#अगर_घोषित ATAFB_TT
अटल काष्ठा fb_hwचयन tt_चयन = अणु
	.detect		= tt_detect,
	.encode_fix	= tt_encode_fix,
	.decode_var	= tt_decode_var,
	.encode_var	= tt_encode_var,
	.get_par	= tt_get_par,
	.set_par	= tt_set_par,
	.set_screen_base = set_screen_base,
	.pan_display	= pan_display,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित ATAFB_FALCON
अटल काष्ठा fb_hwचयन falcon_चयन = अणु
	.detect		= falcon_detect,
	.encode_fix	= falcon_encode_fix,
	.decode_var	= falcon_decode_var,
	.encode_var	= falcon_encode_var,
	.get_par	= falcon_get_par,
	.set_par	= falcon_set_par,
	.set_screen_base = set_screen_base,
	.blank		= falcon_blank,
	.pan_display	= falcon_pan_display,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित ATAFB_STE
अटल काष्ठा fb_hwचयन st_चयन = अणु
	.detect		= stste_detect,
	.encode_fix	= stste_encode_fix,
	.decode_var	= stste_decode_var,
	.encode_var	= stste_encode_var,
	.get_par	= stste_get_par,
	.set_par	= stste_set_par,
	.set_screen_base = stste_set_screen_base,
	.pan_display	= pan_display
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित ATAFB_EXT
अटल काष्ठा fb_hwचयन ext_चयन = अणु
	.detect		= ext_detect,
	.encode_fix	= ext_encode_fix,
	.decode_var	= ext_decode_var,
	.encode_var	= ext_encode_var,
	.get_par	= ext_get_par,
	.set_par	= ext_set_par,
पूर्ण;
#पूर्ण_अगर

अटल व्योम ata_get_par(काष्ठा atafb_par *par)
अणु
	अगर (current_par_valid)
		*par = current_par;
	अन्यथा
		fbhw->get_par(par);
पूर्ण

अटल व्योम ata_set_par(काष्ठा atafb_par *par)
अणु
	fbhw->set_par(par);
	current_par = *par;
	current_par_valid = 1;
पूर्ण


/* =========================================================== */
/* ============== Hardware Independent Functions ============= */
/* =========================================================== */

/* used क्रम hardware scrolling */

अटल पूर्णांक करो_fb_set_var(काष्ठा fb_var_screeninfo *var, पूर्णांक isactive)
अणु
	पूर्णांक err, activate;
	काष्ठा atafb_par par;

	err = fbhw->decode_var(var, &par);
	अगर (err)
		वापस err;
	activate = var->activate;
	अगर (((var->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW) && isactive)
		ata_set_par(&par);
	fbhw->encode_var(var, &par);
	var->activate = activate;
	वापस 0;
पूर्ण

/* fbhw->encode_fix() must be called with fb_info->mm_lock held
 * अगर it is called after the रेजिस्टर_framebuffer() - not a हाल here
 */
अटल पूर्णांक atafb_get_fix(काष्ठा fb_fix_screeninfo *fix, काष्ठा fb_info *info)
अणु
	काष्ठा atafb_par par;
	पूर्णांक err;
	// Get fix directly (हाल con == -1 beक्रमe)??
	err = fbhw->decode_var(&info->var, &par);
	अगर (err)
		वापस err;
	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));
	err = fbhw->encode_fix(fix, &par);
	वापस err;
पूर्ण

अटल पूर्णांक atafb_get_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा atafb_par par;

	ata_get_par(&par);
	fbhw->encode_var(var, &par);

	वापस 0;
पूर्ण

// No दीर्घer called by fbcon!
// Still called by set_var पूर्णांकernally

अटल व्योम atafb_set_disp(काष्ठा fb_info *info)
अणु
	atafb_get_var(&info->var, info);
	atafb_get_fix(&info->fix, info);

	/* Note: smem_start derives from phys_screen_base, not screen_base! */
	info->screen_base = (बाह्यal_addr ? बाह्यal_screen_base :
				atari_stram_to_virt(info->fix.smem_start));
पूर्ण

अटल पूर्णांक atafb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	वापस info->fbops->fb_setcolreg(regno, red, green, blue, transp, info);
पूर्ण

अटल पूर्णांक
atafb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक xoffset = var->xoffset;
	पूर्णांक yoffset = var->yoffset;
	पूर्णांक err;

	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (yoffset < 0 || yoffset >= info->var.yres_भव || xoffset)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (xoffset + info->var.xres > info->var.xres_भव ||
		    yoffset + info->var.yres > info->var.yres_भव)
			वापस -EINVAL;
	पूर्ण

	अगर (fbhw->pan_display) अणु
		err = fbhw->pan_display(var, info);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		वापस -EINVAL;

	info->var.xoffset = xoffset;
	info->var.yoffset = yoffset;

	अगर (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		info->var.vmode &= ~FB_VMODE_YWRAP;

	वापस 0;
पूर्ण

/*
 * generic drawing routines; imageblit needs updating क्रम image depth > 1
 */

#अगर BITS_PER_LONG == 32
#घोषणा BYTES_PER_LONG	4
#घोषणा SHIFT_PER_LONG	5
#या_अगर BITS_PER_LONG == 64
#घोषणा BYTES_PER_LONG	8
#घोषणा SHIFT_PER_LONG	6
#अन्यथा
#घोषणा Please update me
#पूर्ण_अगर


अटल व्योम atafb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;
	पूर्णांक x2, y2;
	u32 width, height;

	अगर (!rect->width || !rect->height)
		वापस;

#अगर_घोषित ATAFB_FALCON
	अगर (info->var.bits_per_pixel == 16) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly.
	 * */
	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width = x2 - rect->dx;
	height = y2 - rect->dy;

	अगर (info->var.bits_per_pixel == 1)
		atafb_mfb_fillrect(info, par->next_line, rect->color,
				   rect->dy, rect->dx, height, width);
	अन्यथा अगर (info->var.bits_per_pixel == 2)
		atafb_iplan2p2_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);
	अन्यथा अगर (info->var.bits_per_pixel == 4)
		atafb_iplan2p4_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);
	अन्यथा
		atafb_iplan2p8_fillrect(info, par->next_line, rect->color,
					rect->dy, rect->dx, height, width);

	वापस;
पूर्ण

अटल व्योम atafb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;
	पूर्णांक x2, y2;
	u32 dx, dy, sx, sy, width, height;
	पूर्णांक rev_copy = 0;

#अगर_घोषित ATAFB_FALCON
	अगर (info->var.bits_per_pixel == 16) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* clip the destination */
	x2 = area->dx + area->width;
	y2 = area->dy + area->height;
	dx = area->dx > 0 ? area->dx : 0;
	dy = area->dy > 0 ? area->dy : 0;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width = x2 - dx;
	height = y2 - dy;

	अगर (area->sx + dx < area->dx || area->sy + dy < area->dy)
		वापस;

	/* update sx,sy */
	sx = area->sx + (dx - area->dx);
	sy = area->sy + (dy - area->dy);

	/* the source must be completely inside the भव screen */
	अगर (sx + width > info->var.xres_भव ||
			sy + height > info->var.yres_भव)
		वापस;

	अगर (dy > sy || (dy == sy && dx > sx)) अणु
		dy += height;
		sy += height;
		rev_copy = 1;
	पूर्ण

	अगर (info->var.bits_per_pixel == 1)
		atafb_mfb_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	अन्यथा अगर (info->var.bits_per_pixel == 2)
		atafb_iplan2p2_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	अन्यथा अगर (info->var.bits_per_pixel == 4)
		atafb_iplan2p4_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);
	अन्यथा
		atafb_iplan2p8_copyarea(info, par->next_line, sy, sx, dy, dx, height, width);

	वापस;
पूर्ण

अटल व्योम atafb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;
	पूर्णांक x2, y2;
	अचिन्हित दीर्घ *dst;
	पूर्णांक dst_idx;
	स्थिर अक्षर *src;
	u32 dx, dy, width, height, pitch;

#अगर_घोषित ATAFB_FALCON
	अगर (info->var.bits_per_pixel == 16) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly like we are
	 * करोing here.
	 */
	x2 = image->dx + image->width;
	y2 = image->dy + image->height;
	dx = image->dx;
	dy = image->dy;
	x2 = x2 < info->var.xres_भव ? x2 : info->var.xres_भव;
	y2 = y2 < info->var.yres_भव ? y2 : info->var.yres_भव;
	width = x2 - dx;
	height = y2 - dy;

	अगर (image->depth == 1) अणु
		// used क्रम font data
		dst = (अचिन्हित दीर्घ *)
			((अचिन्हित दीर्घ)info->screen_base & ~(BYTES_PER_LONG - 1));
		dst_idx = ((अचिन्हित दीर्घ)info->screen_base & (BYTES_PER_LONG - 1)) * 8;
		dst_idx += dy * par->next_line * 8 + dx;
		src = image->data;
		pitch = (image->width + 7) / 8;
		जबतक (height--) अणु

			अगर (info->var.bits_per_pixel == 1)
				atafb_mfb_linefill(info, par->next_line,
						   dy, dx, width, src,
						   image->bg_color, image->fg_color);
			अन्यथा अगर (info->var.bits_per_pixel == 2)
				atafb_iplan2p2_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			अन्यथा अगर (info->var.bits_per_pixel == 4)
				atafb_iplan2p4_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			अन्यथा
				atafb_iplan2p8_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			dy++;
			src += pitch;
		पूर्ण
	पूर्ण अन्यथा अणु
		c2p_iplan2(info->screen_base, image->data, dx, dy, width,
			   height, par->next_line, image->width,
			   info->var.bits_per_pixel);
	पूर्ण
पूर्ण

अटल पूर्णांक
atafb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
#अगर_घोषित FBCMD_GET_CURRENTPAR
	हाल FBCMD_GET_CURRENTPAR:
		अगर (copy_to_user((व्योम *)arg, (व्योम *)&current_par,
				 माप(काष्ठा atafb_par)))
			वापस -EFAULT;
		वापस 0;
#पूर्ण_अगर
#अगर_घोषित FBCMD_SET_CURRENTPAR
	हाल FBCMD_SET_CURRENTPAR:
		अगर (copy_from_user((व्योम *)&current_par, (व्योम *)arg,
				   माप(काष्ठा atafb_par)))
			वापस -EFAULT;
		ata_set_par(&current_par);
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* (un)blank/घातeroff
 * 0 = unblank
 * 1 = blank
 * 2 = suspend vsync
 * 3 = suspend hsync
 * 4 = off
 */
अटल पूर्णांक atafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	अचिन्हित लघु black[16];
	काष्ठा fb_cmap cmap;
	अगर (fbhw->blank && !fbhw->blank(blank))
		वापस 1;
	अगर (blank) अणु
		स_रखो(black, 0, 16 * माप(अचिन्हित लघु));
		cmap.red = black;
		cmap.green = black;
		cmap.blue = black;
		cmap.transp = शून्य;
		cmap.start = 0;
		cmap.len = 16;
		fb_set_cmap(&cmap, info);
	पूर्ण
#अगर 0
	अन्यथा
		करो_install_cmap(info);
#पूर्ण_अगर
	वापस 0;
पूर्ण

	/*
	 * New fbcon पूर्णांकerface ...
	 */

	 /* check var by decoding var पूर्णांकo hw par, rounding अगर necessary,
	  * then encoding hw par back पूर्णांकo new, validated var */
अटल पूर्णांक atafb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	पूर्णांक err;
	काष्ठा atafb_par par;

	/* Validate wanted screen parameters */
	// अगर ((err = ata_decode_var(var, &par)))
	err = fbhw->decode_var(var, &par);
	अगर (err)
		वापस err;

	/* Encode (possibly rounded) screen parameters */
	fbhw->encode_var(var, &par);
	वापस 0;
पूर्ण

	/* actually set hw par by decoding var, then setting hardware from
	 * hw par just decoded */
अटल पूर्णांक atafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा atafb_par *par = (काष्ठा atafb_par *)info->par;

	/* Decode wanted screen parameters */
	fbhw->decode_var(&info->var, par);
	mutex_lock(&info->mm_lock);
	fbhw->encode_fix(&info->fix, par);
	mutex_unlock(&info->mm_lock);

	/* Set new videomode */
	ata_set_par(par);

	वापस 0;
पूर्ण


अटल काष्ठा fb_ops atafb_ops = अणु
	.owner =	THIS_MODULE,
	.fb_check_var	= atafb_check_var,
	.fb_set_par	= atafb_set_par,
	.fb_setcolreg	= atafb_setcolreg,
	.fb_blank =	atafb_blank,
	.fb_pan_display	= atafb_pan_display,
	.fb_fillrect	= atafb_fillrect,
	.fb_copyarea	= atafb_copyarea,
	.fb_imageblit	= atafb_imageblit,
	.fb_ioctl =	atafb_ioctl,
पूर्ण;

अटल व्योम check_शेष_par(पूर्णांक detected_mode)
अणु
	अक्षर शेष_name[10];
	पूर्णांक i;
	काष्ठा fb_var_screeninfo var;
	अचिन्हित दीर्घ min_mem;

	/* First try the user supplied mode */
	अगर (शेष_par) अणु
		var = atafb_predefined[शेष_par - 1];
		var.activate = FB_ACTIVATE_TEST;
		अगर (करो_fb_set_var(&var, 1))
			शेष_par = 0;	/* failed */
	पूर्ण
	/* Next is the स्वतःdetected one */
	अगर (!शेष_par) अणु
		var = atafb_predefined[detected_mode - 1]; /* स्वतःdetect */
		var.activate = FB_ACTIVATE_TEST;
		अगर (!करो_fb_set_var(&var, 1))
			शेष_par = detected_mode;
	पूर्ण
	/* If that also failed, try some शेष modes... */
	अगर (!शेष_par) अणु
		/* try शेष1, शेष2... */
		क्रम (i = 1; i < 10; i++) अणु
			प्र_लिखो(शेष_name,"default%d", i);
			शेष_par = get_video_mode(शेष_name);
			अगर (!शेष_par)
				panic("can't set default video mode");
			var = atafb_predefined[शेष_par - 1];
			var.activate = FB_ACTIVATE_TEST;
			अगर (!करो_fb_set_var(&var,1))
				अवरोध;	/* ok */
		पूर्ण
	पूर्ण
	min_mem = var.xres_भव * var.yres_भव * var.bits_per_pixel / 8;
	अगर (शेष_mem_req < min_mem)
		शेष_mem_req = min_mem;
पूर्ण

#अगर_घोषित ATAFB_EXT
अटल व्योम __init atafb_setup_ext(अक्षर *spec)
अणु
	पूर्णांक xres, xres_भव, yres, depth, planes;
	अचिन्हित दीर्घ addr, len;
	अक्षर *p;

	/* Format is: <xres>;<yres>;<depth>;<plane organ.>;
	 *            <screen mem addr>
	 *	      [;<screen mem length>[;<vgaiobase>[;<bits-per-col>[;<colorreg-type>
	 *	      [;<xres-भव>]]]]]
	 *
	 * 09/23/97	Juergen
	 * <xres_भव>:	hardware's x-resolution (f.e. ProMST)
	 *
	 * Even xres_भव is available, we neither support panning nor hw-scrolling!
	 */
	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	xres_भव = xres = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (xres <= 0)
		वापस;

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	yres = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (yres <= 0)
		वापस;

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	depth = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (depth != 1 && depth != 2 && depth != 4 && depth != 8 &&
	    depth != 16 && depth != 24)
		वापस;

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	अगर (*p == 'i')
		planes = FB_TYPE_INTERLEAVED_PLANES;
	अन्यथा अगर (*p == 'p')
		planes = FB_TYPE_PACKED_PIXELS;
	अन्यथा अगर (*p == 'n')
		planes = FB_TYPE_PLANES;
	अन्यथा अगर (*p == 't')
		planes = -1;		/* true color */
	अन्यथा
		वापस;

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	addr = simple_म_से_अदीर्घ(p, शून्य, 0);

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		len = xres * yres * depth / 8;
	अन्यथा
		len = simple_म_से_अदीर्घ(p, शून्य, 0);

	p = strsep(&spec, ";");
	अगर (p && *p)
		बाह्यal_vgaiobase = simple_म_से_अदीर्घ(p, शून्य, 0);

	p = strsep(&spec, ";");
	अगर (p && *p) अणु
		बाह्यal_bitspercol = simple_म_से_अदीर्घ(p, शून्य, 0);
		अगर (बाह्यal_bitspercol > 8)
			बाह्यal_bitspercol = 8;
		अन्यथा अगर (बाह्यal_bitspercol < 1)
			बाह्यal_bitspercol = 1;
	पूर्ण

	p = strsep(&spec, ";");
	अगर (p && *p) अणु
		अगर (!म_भेद(p, "vga"))
			बाह्यal_card_type = IS_VGA;
		अगर (!म_भेद(p, "mv300"))
			बाह्यal_card_type = IS_MV300;
	पूर्ण

	p = strsep(&spec, ";");
	अगर (p && *p) अणु
		xres_भव = simple_म_से_अदीर्घ(p, शून्य, 10);
		अगर (xres_भव < xres)
			xres_भव = xres;
		अगर (xres_भव * yres * depth / 8 > len)
			len = xres_भव * yres * depth / 8;
	पूर्ण

	बाह्यal_xres = xres;
	बाह्यal_xres_भव = xres_भव;
	बाह्यal_yres = yres;
	बाह्यal_depth = depth;
	बाह्यal_pmode = planes;
	बाह्यal_addr = addr;
	बाह्यal_len = len;

	अगर (बाह्यal_card_type == IS_MV300) अणु
		चयन (बाह्यal_depth) अणु
		हाल 1:
			MV300_reg = MV300_reg_1bit;
			अवरोध;
		हाल 4:
			MV300_reg = MV300_reg_4bit;
			अवरोध;
		हाल 8:
			MV300_reg = MV300_reg_8bit;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* ATAFB_EXT */

अटल व्योम __init atafb_setup_पूर्णांक(अक्षर *spec)
अणु
	/* Format to config extended पूर्णांकernal video hardware like OverScan:
	 * "internal:<xres>;<yres>;<xres_max>;<yres_max>;<offset>"
	 * Explanation:
	 * <xres>: x-resolution
	 * <yres>: y-resolution
	 * The following are only needed अगर you have an overscan which
	 * needs a black border:
	 * <xres_max>: max. length of a line in pixels your OverScan hardware would allow
	 * <yres_max>: max. number of lines your OverScan hardware would allow
	 * <offset>: Offset from physical beginning to visible beginning
	 *	  of screen in bytes
	 */
	पूर्णांक xres;
	अक्षर *p;

	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	xres = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	sttt_xres = xres;
	tt_yres = st_yres = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर ((p = strsep(&spec, ";")) && *p)
		sttt_xres_भव = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर ((p = strsep(&spec, ";")) && *p)
		sttt_yres_भव = simple_म_से_अदीर्घ(p, शून्य, 0);
	अगर ((p = strsep(&spec, ";")) && *p)
		ovsc_offset = simple_म_से_अदीर्घ(p, शून्य, 0);

	अगर (ovsc_offset || (sttt_yres_भव != st_yres))
		use_hwscroll = 0;
पूर्ण

#अगर_घोषित ATAFB_FALCON
अटल व्योम __init atafb_setup_mcap(अक्षर *spec)
अणु
	अक्षर *p;
	पूर्णांक vmin, vmax, hmin, hmax;

	/* Format क्रम monitor capabilities is: <Vmin>;<Vmax>;<Hmin>;<Hmax>
	 * <V*> vertical freq. in Hz
	 * <H*> horizontal freq. in kHz
	 */
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	vmin = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (vmin <= 0)
		वापस;
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	vmax = simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (vmax <= 0 || vmax <= vmin)
		वापस;
	अगर (!(p = strsep(&spec, ";")) || !*p)
		वापस;
	hmin = 1000 * simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (hmin <= 0)
		वापस;
	अगर (!(p = strsep(&spec, "")) || !*p)
		वापस;
	hmax = 1000 * simple_म_से_अदीर्घ(p, शून्य, 10);
	अगर (hmax <= 0 || hmax <= hmin)
		वापस;

	fb_info.monspecs.vfmin = vmin;
	fb_info.monspecs.vfmax = vmax;
	fb_info.monspecs.hfmin = hmin;
	fb_info.monspecs.hfmax = hmax;
पूर्ण
#पूर्ण_अगर /* ATAFB_FALCON */

अटल व्योम __init atafb_setup_user(अक्षर *spec)
अणु
	/* Format of user defined video mode is: <xres>;<yres>;<depth>
	 */
	अक्षर *p;
	पूर्णांक xres, yres, depth, temp;

	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	xres = simple_म_से_अदीर्घ(p, शून्य, 10);
	p = strsep(&spec, ";");
	अगर (!p || !*p)
		वापस;
	yres = simple_म_से_अदीर्घ(p, शून्य, 10);
	p = strsep(&spec, "");
	अगर (!p || !*p)
		वापस;
	depth = simple_म_से_अदीर्घ(p, शून्य, 10);
	temp = get_video_mode("user0");
	अगर (temp) अणु
		शेष_par = temp;
		atafb_predefined[शेष_par - 1].xres = xres;
		atafb_predefined[शेष_par - 1].yres = yres;
		atafb_predefined[शेष_par - 1].bits_per_pixel = depth;
	पूर्ण
पूर्ण

पूर्णांक __init atafb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;
	पूर्णांक temp;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		अगर ((temp = get_video_mode(this_opt))) अणु
			शेष_par = temp;
			mode_option = this_opt;
		पूर्ण अन्यथा अगर (!म_भेद(this_opt, "inverse"))
			inverse = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "hwscroll_", 9)) अणु
			hwscroll = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 10);
			अगर (hwscroll < 0)
				hwscroll = 0;
			अगर (hwscroll > 200)
				hwscroll = 200;
		पूर्ण
#अगर_घोषित ATAFB_EXT
		अन्यथा अगर (!म_भेद(this_opt, "mv300")) अणु
			बाह्यal_bitspercol = 8;
			बाह्यal_card_type = IS_MV300;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "external:", 9))
			atafb_setup_ext(this_opt + 9);
#पूर्ण_अगर
		अन्यथा अगर (!म_भेदन(this_opt, "internal:", 9))
			atafb_setup_पूर्णांक(this_opt + 9);
#अगर_घोषित ATAFB_FALCON
		अन्यथा अगर (!म_भेदन(this_opt, "eclock:", 7)) अणु
			fext.f = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 10);
			/* बाह्यal pixelघड़ी in kHz --> ps */
			fext.t = 1000000000 / fext.f;
			fext.f *= 1000;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "monitorcap:", 11))
			atafb_setup_mcap(this_opt + 11);
#पूर्ण_अगर
		अन्यथा अगर (!म_भेद(this_opt, "keep"))
			DontCalcRes = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "R", 1))
			atafb_setup_user(this_opt + 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init atafb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक pad, detected_mode, error;
	अचिन्हित पूर्णांक deभ_शेषe = 0;
	अचिन्हित दीर्घ mem_req;
	अक्षर *option = शून्य;

	अगर (fb_get_options("atafb", &option))
		वापस -ENODEV;
	atafb_setup(option);
	dev_dbg(&pdev->dev, "%s: start\n", __func__);

	करो अणु
#अगर_घोषित ATAFB_EXT
		अगर (बाह्यal_addr) अणु
			dev_dbg(&pdev->dev, "initializing external hw\n");
			fbhw = &ext_चयन;
			atafb_ops.fb_setcolreg = &ext_setcolreg;
			deभ_शेषe = DEFMODE_EXT;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित ATAFB_TT
		अगर (ATARIHW_PRESENT(TT_SHIFTER)) अणु
			dev_dbg(&pdev->dev, "initializing TT hw\n");
			fbhw = &tt_चयन;
			atafb_ops.fb_setcolreg = &tt_setcolreg;
			deभ_शेषe = DEFMODE_TT;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित ATAFB_FALCON
		अगर (ATARIHW_PRESENT(VIDEL_SHIFTER)) अणु
			dev_dbg(&pdev->dev, "initializing Falcon hw\n");
			fbhw = &falcon_चयन;
			atafb_ops.fb_setcolreg = &falcon_setcolreg;
			error = request_irq(IRQ_AUTO_4, falcon_vbl_चयनer, 0,
					    "framebuffer:modeswitch",
					    falcon_vbl_चयनer);
			अगर (error)
				वापस error;
			deभ_शेषe = DEFMODE_F30;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित ATAFB_STE
		अगर (ATARIHW_PRESENT(STND_SHIFTER) ||
		    ATARIHW_PRESENT(EXTD_SHIFTER)) अणु
			dev_dbg(&pdev->dev, "initializing ST/E hw\n");
			fbhw = &st_चयन;
			atafb_ops.fb_setcolreg = &stste_setcolreg;
			deभ_शेषe = DEFMODE_STE;
			अवरोध;
		पूर्ण
		fbhw = &st_चयन;
		atafb_ops.fb_setcolreg = &stste_setcolreg;
		dev_warn(&pdev->dev,
			 "Cannot determine video hardware; defaulting to ST(e)\n");
#अन्यथा /* ATAFB_STE */
		/* no शेष driver included */
		/* Nobody will ever see this message :-) */
		panic("Cannot initialize video hardware");
#पूर्ण_अगर
	पूर्ण जबतक (0);

	/* Multisync monitor capabilities */
	/* Atari-TOS शेषs अगर no boot option present */
	अगर (fb_info.monspecs.hfmin == 0) अणु
		fb_info.monspecs.hfmin = 31000;
		fb_info.monspecs.hfmax = 32000;
		fb_info.monspecs.vfmin = 58;
		fb_info.monspecs.vfmax = 62;
	पूर्ण

	detected_mode = fbhw->detect();
	check_शेष_par(detected_mode);
#अगर_घोषित ATAFB_EXT
	अगर (!बाह्यal_addr) अणु
#पूर्ण_अगर /* ATAFB_EXT */
		mem_req = शेष_mem_req + ovsc_offset + ovsc_addlen;
		mem_req = PAGE_ALIGN(mem_req) + PAGE_SIZE;
		screen_base = atari_stram_alloc(mem_req, "atafb");
		अगर (!screen_base)
			panic("Cannot allocate screen memory");
		स_रखो(screen_base, 0, mem_req);
		pad = -(अचिन्हित दीर्घ)screen_base & (PAGE_SIZE - 1);
		screen_base += pad;
		phys_screen_base = atari_stram_to_phys(screen_base + ovsc_offset);
		screen_len = (mem_req - pad - ovsc_offset) & PAGE_MASK;
		st_ovsc_चयन();
		अगर (CPU_IS_040_OR_060) अणु
			/* On a '040+, the cache mode of video RAM must be set to
			 * ग_लिखो-through also क्रम पूर्णांकernal video hardware! */
			cache_push(atari_stram_to_phys(screen_base), screen_len);
			kernel_set_cachemode(screen_base, screen_len,
					     IOMAP_WRITETHROUGH);
		पूर्ण
		dev_info(&pdev->dev, "phys_screen_base %lx screen_len %d\n",
			 phys_screen_base, screen_len);
#अगर_घोषित ATAFB_EXT
	पूर्ण अन्यथा अणु
		/* Map the video memory (physical address given) to somewhere
		 * in the kernel address space.
		 */
		बाह्यal_screen_base = ioremap_wt(बाह्यal_addr, बाह्यal_len);
		अगर (बाह्यal_vgaiobase)
			बाह्यal_vgaiobase =
			  (अचिन्हित दीर्घ)ioremap(बाह्यal_vgaiobase, 0x10000);
		screen_base = बाह्यal_screen_base;
		phys_screen_base = बाह्यal_addr;
		screen_len = बाह्यal_len & PAGE_MASK;
		स_रखो (screen_base, 0, बाह्यal_len);
	पूर्ण
#पूर्ण_अगर /* ATAFB_EXT */

//	म_नकल(fb_info.mode->name, "Atari Builtin ");
	fb_info.fbops = &atafb_ops;
	// try to set शेष (detected; requested) var
	करो_fb_set_var(&atafb_predefined[शेष_par - 1], 1);
	// पढ़ोs hw state पूर्णांकo current par, which may not be sane yet
	ata_get_par(&current_par);
	fb_info.par = &current_par;
	// tries to पढ़ो from HW which may not be initialized yet
	// so set sane var first, then call atafb_set_par
	atafb_get_var(&fb_info.var, &fb_info);

#अगर_घोषित ATAFB_FALCON
	fb_info.pseuकरो_palette = current_par.hw.falcon.pseuकरो_palette;
#पूर्ण_अगर
	fb_info.flags = FBINFO_FLAG_DEFAULT;

	अगर (!fb_find_mode(&fb_info.var, &fb_info, mode_option, atafb_modedb,
			  NUM_TOTAL_MODES, &atafb_modedb[deभ_शेषe],
			  fb_info.var.bits_per_pixel)) अणु
		वापस -EINVAL;
	पूर्ण

	fb_videomode_to_modelist(atafb_modedb, NUM_TOTAL_MODES,
				 &fb_info.modelist);

	atafb_set_disp(&fb_info);

	fb_alloc_cmap(&(fb_info.cmap), 1 << fb_info.var.bits_per_pixel, 0);


	dev_info(&pdev->dev, "Determined %dx%d, depth %d\n", fb_info.var.xres,
		 fb_info.var.yres, fb_info.var.bits_per_pixel);
	अगर ((fb_info.var.xres != fb_info.var.xres_भव) ||
	    (fb_info.var.yres != fb_info.var.yres_भव))
		dev_info(&pdev->dev, "   virtual %dx%d\n",
			 fb_info.var.xres_भव, fb_info.var.yres_भव);

	अगर (रेजिस्टर_framebuffer(&fb_info) < 0) अणु
#अगर_घोषित ATAFB_EXT
		अगर (बाह्यal_addr) अणु
			iounmap(बाह्यal_screen_base);
			बाह्यal_addr = 0;
		पूर्ण
		अगर (बाह्यal_vgaiobase) अणु
			iounmap((व्योम*)बाह्यal_vgaiobase);
			बाह्यal_vgaiobase = 0;
		पूर्ण
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	fb_info(&fb_info, "frame buffer device, using %dK of video memory\n",
		screen_len >> 10);

	/* TODO: This driver cannot be unloaded yet */
	वापस 0;
पूर्ण

अटल व्योम atafb_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/* Unblank beक्रमe kexec */
	अगर (fbhw->blank)
		fbhw->blank(0);
पूर्ण

अटल काष्ठा platक्रमm_driver atafb_driver = अणु
	.shutकरोwn	= atafb_shutकरोwn,
	.driver	= अणु
		.name	= "atafb",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init atafb_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!MACH_IS_ATARI)
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_simple("atafb", -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	वापस platक्रमm_driver_probe(&atafb_driver, atafb_probe);
पूर्ण

device_initcall(atafb_init);
