<शैली गुरु>
/*
 * linux/drivers/video/fbcvt.c - VESA(TM) Coordinated Video Timings
 *
 * Copyright (C) 2005 Antonino Daplas <adaplas@pol.net>
 *
 *      Based from the VESA(TM) Coordinated Video Timing Generator by
 *      Graham Loveridge April 9, 2003 available at
 *      http://www.elo.utfsm.cl/~elo212/करोcs/CVTd6r1.xls
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#घोषणा FB_CVT_CELLSIZE               8
#घोषणा FB_CVT_GTF_C                 40
#घोषणा FB_CVT_GTF_J                 20
#घोषणा FB_CVT_GTF_K                128
#घोषणा FB_CVT_GTF_M                600
#घोषणा FB_CVT_MIN_VSYNC_BP         550
#घोषणा FB_CVT_MIN_VPORCH             3
#घोषणा FB_CVT_MIN_BPORCH             6

#घोषणा FB_CVT_RB_MIN_VBLANK        460
#घोषणा FB_CVT_RB_HBLANK            160
#घोषणा FB_CVT_RB_V_FPORCH            3

#घोषणा FB_CVT_FLAG_REDUCED_BLANK 1
#घोषणा FB_CVT_FLAG_MARGINS       2
#घोषणा FB_CVT_FLAG_INTERLACED    4

काष्ठा fb_cvt_data अणु
	u32 xres;
	u32 yres;
	u32 refresh;
	u32 f_refresh;
	u32 pixघड़ी;
	u32 hperiod;
	u32 hblank;
	u32 hfreq;
	u32 htotal;
	u32 vtotal;
	u32 vsync;
	u32 hsync;
	u32 h_front_porch;
	u32 h_back_porch;
	u32 v_front_porch;
	u32 v_back_porch;
	u32 h_margin;
	u32 v_margin;
	u32 पूर्णांकerlace;
	u32 aspect_ratio;
	u32 active_pixels;
	u32 flags;
	u32 status;
पूर्ण;

अटल स्थिर अचिन्हित अक्षर fb_cvt_vbi_tab[] = अणु
	4,        /* 4:3      */
	5,        /* 16:9     */
	6,        /* 16:10    */
	7,        /* 5:4      */
	7,        /* 15:9     */
	8,        /* reserved */
	9,        /* reserved */
	10        /* custom   */
पूर्ण;

/* वापसs hperiod * 1000 */
अटल u32 fb_cvt_hperiod(काष्ठा fb_cvt_data *cvt)
अणु
	u32 num = 1000000000/cvt->f_refresh;
	u32 den;

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK) अणु
		num -= FB_CVT_RB_MIN_VBLANK * 1000;
		den = 2 * (cvt->yres/cvt->पूर्णांकerlace + 2 * cvt->v_margin);
	पूर्ण अन्यथा अणु
		num -= FB_CVT_MIN_VSYNC_BP * 1000;
		den = 2 * (cvt->yres/cvt->पूर्णांकerlace + cvt->v_margin * 2
			   + FB_CVT_MIN_VPORCH + cvt->पूर्णांकerlace/2);
	पूर्ण

	वापस 2 * (num/den);
पूर्ण

/* वापसs ideal duty cycle * 1000 */
अटल u32 fb_cvt_ideal_duty_cycle(काष्ठा fb_cvt_data *cvt)
अणु
	u32 c_prime = (FB_CVT_GTF_C - FB_CVT_GTF_J) *
		(FB_CVT_GTF_K) + 256 * FB_CVT_GTF_J;
	u32 m_prime = (FB_CVT_GTF_K * FB_CVT_GTF_M);
	u32 h_period_est = cvt->hperiod;

	वापस (1000 * c_prime  - ((m_prime * h_period_est)/1000))/256;
पूर्ण

अटल u32 fb_cvt_hblank(काष्ठा fb_cvt_data *cvt)
अणु
	u32 hblank = 0;

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		hblank = FB_CVT_RB_HBLANK;
	अन्यथा अणु
		u32 ideal_duty_cycle = fb_cvt_ideal_duty_cycle(cvt);
		u32 active_pixels = cvt->active_pixels;

		अगर (ideal_duty_cycle < 20000)
			hblank = (active_pixels * 20000)/
				(100000 - 20000);
		अन्यथा अणु
			hblank = (active_pixels * ideal_duty_cycle)/
				(100000 - ideal_duty_cycle);
		पूर्ण
	पूर्ण

	hblank &= ~((2 * FB_CVT_CELLSIZE) - 1);

	वापस hblank;
पूर्ण

अटल u32 fb_cvt_hsync(काष्ठा fb_cvt_data *cvt)
अणु
	u32 hsync;

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		hsync = 32;
	अन्यथा
		hsync = (FB_CVT_CELLSIZE * cvt->htotal)/100;

	hsync &= ~(FB_CVT_CELLSIZE - 1);
	वापस hsync;
पूर्ण

अटल u32 fb_cvt_vbi_lines(काष्ठा fb_cvt_data *cvt)
अणु
	u32 vbi_lines, min_vbi_lines, act_vbi_lines;

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK) अणु
		vbi_lines = (1000 * FB_CVT_RB_MIN_VBLANK)/cvt->hperiod + 1;
		min_vbi_lines =  FB_CVT_RB_V_FPORCH + cvt->vsync +
			FB_CVT_MIN_BPORCH;

	पूर्ण अन्यथा अणु
		vbi_lines = (FB_CVT_MIN_VSYNC_BP * 1000)/cvt->hperiod + 1 +
			 FB_CVT_MIN_VPORCH;
		min_vbi_lines = cvt->vsync + FB_CVT_MIN_BPORCH +
			FB_CVT_MIN_VPORCH;
	पूर्ण

	अगर (vbi_lines < min_vbi_lines)
		act_vbi_lines = min_vbi_lines;
	अन्यथा
		act_vbi_lines = vbi_lines;

	वापस act_vbi_lines;
पूर्ण

अटल u32 fb_cvt_vtotal(काष्ठा fb_cvt_data *cvt)
अणु
	u32 vtotal = cvt->yres/cvt->पूर्णांकerlace;

	vtotal += 2 * cvt->v_margin + cvt->पूर्णांकerlace/2 + fb_cvt_vbi_lines(cvt);
	vtotal |= cvt->पूर्णांकerlace/2;

	वापस vtotal;
पूर्ण

अटल u32 fb_cvt_pixघड़ी(काष्ठा fb_cvt_data *cvt)
अणु
	u32 pixघड़ी;

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		pixघड़ी = (cvt->f_refresh * cvt->vtotal * cvt->htotal)/1000;
	अन्यथा
		pixघड़ी = (cvt->htotal * 1000000)/cvt->hperiod;

	pixघड़ी /= 250;
	pixघड़ी *= 250;
	pixघड़ी *= 1000;

	वापस pixघड़ी;
पूर्ण

अटल u32 fb_cvt_aspect_ratio(काष्ठा fb_cvt_data *cvt)
अणु
	u32 xres = cvt->xres;
	u32 yres = cvt->yres;
	u32 aspect = -1;

	अगर (xres == (yres * 4)/3 && !((yres * 4) % 3))
		aspect = 0;
	अन्यथा अगर (xres == (yres * 16)/9 && !((yres * 16) % 9))
		aspect = 1;
	अन्यथा अगर (xres == (yres * 16)/10 && !((yres * 16) % 10))
		aspect = 2;
	अन्यथा अगर (xres == (yres * 5)/4 && !((yres * 5) % 4))
		aspect = 3;
	अन्यथा अगर (xres == (yres * 15)/9 && !((yres * 15) % 9))
		aspect = 4;
	अन्यथा अणु
		prपूर्णांकk(KERN_INFO "fbcvt: Aspect ratio not CVT "
		       "standard\n");
		aspect = 7;
		cvt->status = 1;
	पूर्ण

	वापस aspect;
पूर्ण

अटल व्योम fb_cvt_prपूर्णांक_name(काष्ठा fb_cvt_data *cvt)
अणु
	u32 pixcount, pixcount_mod;
	पूर्णांक cnt = 255, offset = 0, पढ़ो = 0;
	u8 *buf = kzalloc(256, GFP_KERNEL);

	अगर (!buf)
		वापस;

	pixcount = (cvt->xres * (cvt->yres/cvt->पूर्णांकerlace))/1000000;
	pixcount_mod = (cvt->xres * (cvt->yres/cvt->पूर्णांकerlace)) % 1000000;
	pixcount_mod /= 1000;

	पढ़ो = snम_लिखो(buf+offset, cnt, "fbcvt: %dx%d@%d: CVT Name - ",
			cvt->xres, cvt->yres, cvt->refresh);
	offset += पढ़ो;
	cnt -= पढ़ो;

	अगर (cvt->status)
		snम_लिखो(buf+offset, cnt, "Not a CVT standard - %d.%03d Mega "
			 "Pixel Image\n", pixcount, pixcount_mod);
	अन्यथा अणु
		अगर (pixcount) अणु
			पढ़ो = snम_लिखो(buf+offset, cnt, "%d", pixcount);
			cnt -= पढ़ो;
			offset += पढ़ो;
		पूर्ण

		पढ़ो = snम_लिखो(buf+offset, cnt, ".%03dM", pixcount_mod);
		cnt -= पढ़ो;
		offset += पढ़ो;

		अगर (cvt->aspect_ratio == 0)
			पढ़ो = snम_लिखो(buf+offset, cnt, "3");
		अन्यथा अगर (cvt->aspect_ratio == 3)
			पढ़ो = snम_लिखो(buf+offset, cnt, "4");
		अन्यथा अगर (cvt->aspect_ratio == 1 || cvt->aspect_ratio == 4)
			पढ़ो = snम_लिखो(buf+offset, cnt, "9");
		अन्यथा अगर (cvt->aspect_ratio == 2)
			पढ़ो = snम_लिखो(buf+offset, cnt, "A");
		अन्यथा
			पढ़ो = 0;
		cnt -= पढ़ो;
		offset += पढ़ो;

		अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK) अणु
			पढ़ो = snम_लिखो(buf+offset, cnt, "-R");
			cnt -= पढ़ो;
			offset += पढ़ो;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s\n", buf);
	kमुक्त(buf);
पूर्ण

अटल व्योम fb_cvt_convert_to_mode(काष्ठा fb_cvt_data *cvt,
				   काष्ठा fb_videomode *mode)
अणु
	mode->refresh = cvt->f_refresh;
	mode->pixघड़ी = KHZ2PICOS(cvt->pixघड़ी/1000);
	mode->left_margin = cvt->h_back_porch;
	mode->right_margin = cvt->h_front_porch;
	mode->hsync_len = cvt->hsync;
	mode->upper_margin = cvt->v_back_porch;
	mode->lower_margin = cvt->v_front_porch;
	mode->vsync_len = cvt->vsync;

	mode->sync &= ~(FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT);

	अगर (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		mode->sync |= FB_SYNC_HOR_HIGH_ACT;
	अन्यथा
		mode->sync |= FB_SYNC_VERT_HIGH_ACT;
पूर्ण

/*
 * fb_find_mode_cvt - calculate mode using VESA(TM) CVT
 * @mode: poपूर्णांकer to fb_videomode; xres, yres, refresh and vmode must be
 *        pre-filled with the desired values
 * @margins: add margin to calculation (1.8% of xres and yres)
 * @rb: compute with reduced blanking (क्रम flatpanels)
 *
 * RETURNS:
 * 0 क्रम success
 * @mode is filled with computed values.  If पूर्णांकerlaced, the refresh field
 * will be filled with the field rate (2x the frame rate)
 *
 * DESCRIPTION:
 * Computes video timings using VESA(TM) Coordinated Video Timings
 */
पूर्णांक fb_find_mode_cvt(काष्ठा fb_videomode *mode, पूर्णांक margins, पूर्णांक rb)
अणु
	काष्ठा fb_cvt_data cvt;

	स_रखो(&cvt, 0, माप(cvt));

	अगर (margins)
	    cvt.flags |= FB_CVT_FLAG_MARGINS;

	अगर (rb)
	    cvt.flags |= FB_CVT_FLAG_REDUCED_BLANK;

	अगर (mode->vmode & FB_VMODE_INTERLACED)
	    cvt.flags |= FB_CVT_FLAG_INTERLACED;

	cvt.xres = mode->xres;
	cvt.yres = mode->yres;
	cvt.refresh = mode->refresh;
	cvt.f_refresh = cvt.refresh;
	cvt.पूर्णांकerlace = 1;

	अगर (!cvt.xres || !cvt.yres || !cvt.refresh) अणु
		prपूर्णांकk(KERN_INFO "fbcvt: Invalid input parameters\n");
		वापस 1;
	पूर्ण

	अगर (!(cvt.refresh == 50 || cvt.refresh == 60 || cvt.refresh == 70 ||
	      cvt.refresh == 85)) अणु
		prपूर्णांकk(KERN_INFO "fbcvt: Refresh rate not CVT "
		       "standard\n");
		cvt.status = 1;
	पूर्ण

	cvt.xres &= ~(FB_CVT_CELLSIZE - 1);

	अगर (cvt.flags & FB_CVT_FLAG_INTERLACED) अणु
		cvt.पूर्णांकerlace = 2;
		cvt.f_refresh *= 2;
	पूर्ण

	अगर (cvt.flags & FB_CVT_FLAG_REDUCED_BLANK) अणु
		अगर (cvt.refresh != 60) अणु
			prपूर्णांकk(KERN_INFO "fbcvt: 60Hz refresh rate "
			       "advised for reduced blanking\n");
			cvt.status = 1;
		पूर्ण
	पूर्ण

	अगर (cvt.flags & FB_CVT_FLAG_MARGINS) अणु
		cvt.h_margin = (cvt.xres * 18)/1000;
		cvt.h_margin &= ~(FB_CVT_CELLSIZE - 1);
		cvt.v_margin = ((cvt.yres/cvt.पूर्णांकerlace)* 18)/1000;
	पूर्ण

	cvt.aspect_ratio = fb_cvt_aspect_ratio(&cvt);
	cvt.active_pixels = cvt.xres + 2 * cvt.h_margin;
	cvt.hperiod = fb_cvt_hperiod(&cvt);
	cvt.vsync = fb_cvt_vbi_tab[cvt.aspect_ratio];
	cvt.vtotal = fb_cvt_vtotal(&cvt);
	cvt.hblank = fb_cvt_hblank(&cvt);
	cvt.htotal = cvt.active_pixels + cvt.hblank;
	cvt.hsync = fb_cvt_hsync(&cvt);
	cvt.pixघड़ी = fb_cvt_pixघड़ी(&cvt);
	cvt.hfreq = cvt.pixघड़ी/cvt.htotal;
	cvt.h_back_porch = cvt.hblank/2 + cvt.h_margin;
	cvt.h_front_porch = cvt.hblank - cvt.hsync - cvt.h_back_porch +
		2 * cvt.h_margin;
	cvt.v_front_porch = 3 + cvt.v_margin;
	cvt.v_back_porch = cvt.vtotal - cvt.yres/cvt.पूर्णांकerlace -
	    cvt.v_front_porch - cvt.vsync;
	fb_cvt_prपूर्णांक_name(&cvt);
	fb_cvt_convert_to_mode(&cvt, mode);

	वापस 0;
पूर्ण
