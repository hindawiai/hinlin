<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450.
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Portions Copyright (c) 2001 Matrox Graphics Inc.
 *
 * Version: 1.65 2002/08/14
 *
 */

#समावेश "matroxfb_maven.h"
#समावेश "matroxfb_crtc2.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_DAC1064.h"
#समावेश <linux/matroxfb.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

/* **************************************************** */

अटल पूर्णांक mem = 8192;

module_param(mem, पूर्णांक, 0);
MODULE_PARM_DESC(mem, "Memory size reserved for dualhead (default=8MB)");

/* **************************************************** */

अटल पूर्णांक matroxfb_dh_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
		अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info* info) अणु
	u_पूर्णांक32_t col;
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))

	अगर (regno >= 16)
		वापस 1;
	अगर (m2info->fbcon.var.grayscale) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण
	red = CNVT_TOHW(red, m2info->fbcon.var.red.length);
	green = CNVT_TOHW(green, m2info->fbcon.var.green.length);
	blue = CNVT_TOHW(blue, m2info->fbcon.var.blue.length);
	transp = CNVT_TOHW(transp, m2info->fbcon.var.transp.length);

	col = (red << m2info->fbcon.var.red.offset)     |
	      (green << m2info->fbcon.var.green.offset) |
	      (blue << m2info->fbcon.var.blue.offset)   |
	      (transp << m2info->fbcon.var.transp.offset);

	चयन (m2info->fbcon.var.bits_per_pixel) अणु
		हाल 16:
			m2info->cmap[regno] = col | (col << 16);
			अवरोध;
		हाल 32:
			m2info->cmap[regno] = col;
			अवरोध;
	पूर्ण
	वापस 0;
#अघोषित m2info
पूर्ण

अटल व्योम matroxfb_dh_restore(काष्ठा matroxfb_dh_fb_info* m2info,
		काष्ठा my_timming* mt,
		पूर्णांक mode,
		अचिन्हित पूर्णांक pos) अणु
	u_पूर्णांक32_t पंचांगp;
	u_पूर्णांक32_t datactl;
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	चयन (mode) अणु
		हाल 15:
			पंचांगp = 0x00200000;
			अवरोध;
		हाल 16:
			पंचांगp = 0x00400000;
			अवरोध;
/*		हाल 32: */
		शेष:
			पंचांगp = 0x00800000;
			अवरोध;
	पूर्ण
	पंचांगp |= 0x00000001;	/* enable CRTC2 */
	datactl = 0;
	अगर (minfo->outमाला_दो[1].src == MATROXFB_SRC_CRTC2) अणु
		अगर (minfo->devflags.g450dac) अणु
			पंचांगp |= 0x00000006; /* source from secondary pixel PLL */
			/* no vidrst when in monitor mode */
			अगर (minfo->outमाला_दो[1].mode != MATROXFB_OUTPUT_MODE_MONITOR) अणु
				पंचांगp |=  0xC0001000; /* Enable H/V vidrst */
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp |= 0x00000002; /* source from VDOCLK */
			पंचांगp |= 0xC0000000; /* enable vvidrst & hvidrst */
			/* MGA TVO is our घड़ी source */
		पूर्ण
	पूर्ण अन्यथा अगर (minfo->outमाला_दो[0].src == MATROXFB_SRC_CRTC2) अणु
		पंचांगp |= 0x00000004; /* source from pixघड़ी */
		/* PIXPLL is our घड़ी source */
	पूर्ण
	अगर (minfo->outमाला_दो[0].src == MATROXFB_SRC_CRTC2) अणु
		पंचांगp |= 0x00100000;	/* connect CRTC2 to DAC */
	पूर्ण
	अगर (mt->पूर्णांकerlaced) अणु
		पंचांगp |= 0x02000000;	/* पूर्णांकerlaced, second field is bigger, as G450 apparently ignores it */
		mt->VDisplay >>= 1;
		mt->VSyncStart >>= 1;
		mt->VSyncEnd >>= 1;
		mt->VTotal >>= 1;
	पूर्ण
	अगर ((mt->HTotal & 7) == 2) अणु
		datactl |= 0x00000010;
		mt->HTotal &= ~7;
	पूर्ण
	पंचांगp |= 0x10000000;	/* 0x10000000 is VIDRST polarity */
	mga_outl(0x3C14, ((mt->HDisplay - 8) << 16) | (mt->HTotal - 8));
	mga_outl(0x3C18, ((mt->HSyncEnd - 8) << 16) | (mt->HSyncStart - 8));
	mga_outl(0x3C1C, ((mt->VDisplay - 1) << 16) | (mt->VTotal - 1));
	mga_outl(0x3C20, ((mt->VSyncEnd - 1) << 16) | (mt->VSyncStart - 1));
	mga_outl(0x3C24, ((mt->VSyncStart) << 16) | (mt->HSyncStart));	/* preload */
	अणु
		u_पूर्णांक32_t linelen = m2info->fbcon.var.xres_भव * (m2info->fbcon.var.bits_per_pixel >> 3);
		अगर (पंचांगp & 0x02000000) अणु
			/* field #0 is smaller, so... */
			mga_outl(0x3C2C, pos);			/* field #1 vmemory start */
			mga_outl(0x3C28, pos + linelen);	/* field #0 vmemory start */
			linelen <<= 1;
			m2info->पूर्णांकerlaced = 1;
		पूर्ण अन्यथा अणु
			mga_outl(0x3C28, pos);		/* vmemory start */
			m2info->पूर्णांकerlaced = 0;
		पूर्ण
		mga_outl(0x3C40, linelen);
	पूर्ण
	mga_outl(0x3C4C, datactl);	/* data control */
	अगर (पंचांगp & 0x02000000) अणु
		पूर्णांक i;

		mga_outl(0x3C10, पंचांगp & ~0x02000000);
		क्रम (i = 0; i < 2; i++) अणु
			अचिन्हित पूर्णांक nl;
			अचिन्हित पूर्णांक lastl = 0;

			जबतक ((nl = mga_inl(0x3C48) & 0xFFF) >= lastl) अणु
				lastl = nl;
			पूर्ण
		पूर्ण
	पूर्ण
	mga_outl(0x3C10, पंचांगp);
	minfo->hw.crtc2.ctl = पंचांगp;

	पंचांगp = mt->VDisplay << 16;	/* line compare */
	अगर (mt->sync & FB_SYNC_HOR_HIGH_ACT)
		पंचांगp |= 0x00000100;
	अगर (mt->sync & FB_SYNC_VERT_HIGH_ACT)
		पंचांगp |= 0x00000200;
	mga_outl(0x3C44, पंचांगp);
पूर्ण

अटल व्योम matroxfb_dh_disable(काष्ठा matroxfb_dh_fb_info* m2info) अणु
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	mga_outl(0x3C10, 0x00000004);	/* disable CRTC2, CRTC1->DAC1, PLL as घड़ी source */
	minfo->hw.crtc2.ctl = 0x00000004;
पूर्ण

अटल व्योम matroxfb_dh_pan_var(काष्ठा matroxfb_dh_fb_info* m2info,
		काष्ठा fb_var_screeninfo* var) अणु
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक linelen;
	अचिन्हित पूर्णांक pixelsize;
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	m2info->fbcon.var.xoffset = var->xoffset;
	m2info->fbcon.var.yoffset = var->yoffset;
	pixelsize = m2info->fbcon.var.bits_per_pixel >> 3;
	linelen = m2info->fbcon.var.xres_भव * pixelsize;
	pos = m2info->fbcon.var.yoffset * linelen + m2info->fbcon.var.xoffset * pixelsize;
	pos += m2info->video.offbase;
	अगर (m2info->पूर्णांकerlaced) अणु
		mga_outl(0x3C2C, pos);
		mga_outl(0x3C28, pos + linelen);
	पूर्ण अन्यथा अणु
		mga_outl(0x3C28, pos);
	पूर्ण
पूर्ण

अटल पूर्णांक matroxfb_dh_decode_var(काष्ठा matroxfb_dh_fb_info* m2info,
		काष्ठा fb_var_screeninfo* var,
		पूर्णांक *visual,
		पूर्णांक *video_cmap_len,
		पूर्णांक *mode) अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक memlen;
	अचिन्हित पूर्णांक vramlen;

	चयन (var->bits_per_pixel) अणु
		हाल 16:	mask = 0x1F;
				अवरोध;
		हाल 32:	mask = 0x0F;
				अवरोध;
		शेष:	वापस -EINVAL;
	पूर्ण
	vramlen = m2info->video.len_usable;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	var->xres_भव = (var->xres_भव + mask) & ~mask;
	अगर (var->yres_भव > 32767)
		वापस -EINVAL;
	memlen = var->xres_भव * var->yres_भव * (var->bits_per_pixel >> 3);
	अगर (memlen > vramlen)
		वापस -EINVAL;
	अगर (var->xoffset + var->xres > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yoffset + var->yres > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	var->xres &= ~7;
	var->left_margin &= ~7;
	var->right_margin &= ~7;
	var->hsync_len &= ~7;

	*mode = var->bits_per_pixel;
	अगर (var->bits_per_pixel == 16) अणु
		अगर (var->green.length == 5) अणु
			var->red.offset = 10;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 5;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 15;
			var->transp.length = 1;
			*mode = 15;
		पूर्ण अन्यथा अणु
			var->red.offset = 11;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
	पूर्ण
	*visual = FB_VISUAL_TRUECOLOR;
	*video_cmap_len = 16;
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_dh_खोलो(काष्ठा fb_info* info, पूर्णांक user) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	अगर (minfo) अणु
		पूर्णांक err;

		अगर (minfo->dead) अणु
			वापस -ENXIO;
		पूर्ण
		err = minfo->fbops.fb_खोलो(&minfo->fbcon, user);
		अगर (err) अणु
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
#अघोषित m2info
पूर्ण

अटल पूर्णांक matroxfb_dh_release(काष्ठा fb_info* info, पूर्णांक user) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	पूर्णांक err = 0;
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	अगर (minfo) अणु
		err = minfo->fbops.fb_release(&minfo->fbcon, user);
	पूर्ण
	वापस err;
#अघोषित m2info
पूर्ण

/*
 * This function is called beक्रमe the रेजिस्टर_framebuffer so
 * no locking is needed.
 */
अटल व्योम matroxfb_dh_init_fix(काष्ठा matroxfb_dh_fb_info *m2info)
अणु
	काष्ठा fb_fix_screeninfo *fix = &m2info->fbcon.fix;

	म_नकल(fix->id, "MATROX DH");

	fix->smem_start = m2info->video.base;
	fix->smem_len = m2info->video.len_usable;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->xpanstep = 8;	/* TBD */
	fix->mmio_start = m2info->mmio.base;
	fix->mmio_len = m2info->mmio.len;
	fix->accel = 0;		/* no accel... */
पूर्ण

अटल पूर्णांक matroxfb_dh_check_var(काष्ठा fb_var_screeninfo* var, काष्ठा fb_info* info) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	पूर्णांक visual;
	पूर्णांक cmap_len;
	पूर्णांक mode;

	वापस matroxfb_dh_decode_var(m2info, var, &visual, &cmap_len, &mode);
#अघोषित m2info
पूर्ण

अटल पूर्णांक matroxfb_dh_set_par(काष्ठा fb_info* info) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	पूर्णांक visual;
	पूर्णांक cmap_len;
	पूर्णांक mode;
	पूर्णांक err;
	काष्ठा fb_var_screeninfo* var = &info->var;
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	अगर ((err = matroxfb_dh_decode_var(m2info, var, &visual, &cmap_len, &mode)) != 0)
		वापस err;
	/* cmap */
	अणु
		m2info->fbcon.screen_base = vaddr_va(m2info->video.vbase);
		m2info->fbcon.fix.visual = visual;
		m2info->fbcon.fix.type = FB_TYPE_PACKED_PIXELS;
		m2info->fbcon.fix.type_aux = 0;
		m2info->fbcon.fix.line_length = (var->xres_भव * var->bits_per_pixel) >> 3;
	पूर्ण
	अणु
		काष्ठा my_timming mt;
		अचिन्हित पूर्णांक pos;
		पूर्णांक out;
		पूर्णांक cnt;

		matroxfb_var2my(&m2info->fbcon.var, &mt);
		mt.crtc = MATROXFB_SRC_CRTC2;
		/* CRTC2 delay */
		mt.delay = 34;

		pos = (m2info->fbcon.var.yoffset * m2info->fbcon.var.xres_भव + m2info->fbcon.var.xoffset) * m2info->fbcon.var.bits_per_pixel >> 3;
		pos += m2info->video.offbase;
		cnt = 0;
		करोwn_पढ़ो(&minfo->altout.lock);
		क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
			अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC2) अणु
				cnt++;
				अगर (minfo->outमाला_दो[out].output->compute) अणु
					minfo->outमाला_दो[out].output->compute(minfo->outमाला_दो[out].data, &mt);
				पूर्ण
			पूर्ण
		पूर्ण
		minfo->crtc2.pixघड़ी = mt.pixघड़ी;
		minfo->crtc2.mnp = mt.mnp;
		up_पढ़ो(&minfo->altout.lock);
		अगर (cnt) अणु
			matroxfb_dh_restore(m2info, &mt, mode, pos);
		पूर्ण अन्यथा अणु
			matroxfb_dh_disable(m2info);
		पूर्ण
		DAC1064_global_init(minfo);
		DAC1064_global_restore(minfo);
		करोwn_पढ़ो(&minfo->altout.lock);
		क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
			अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC2 &&
			    minfo->outमाला_दो[out].output->program) अणु
				minfo->outमाला_दो[out].output->program(minfo->outमाला_दो[out].data);
			पूर्ण
		पूर्ण
		क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
			अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC2 &&
			    minfo->outमाला_दो[out].output->start) अणु
				minfo->outमाला_दो[out].output->start(minfo->outमाला_दो[out].data);
			पूर्ण
		पूर्ण
		up_पढ़ो(&minfo->altout.lock);
	पूर्ण
	m2info->initialized = 1;
	वापस 0;
#अघोषित m2info
पूर्ण

अटल पूर्णांक matroxfb_dh_pan_display(काष्ठा fb_var_screeninfo* var, काष्ठा fb_info* info) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	matroxfb_dh_pan_var(m2info, var);
	वापस 0;
#अघोषित m2info
पूर्ण

अटल पूर्णांक matroxfb_dh_get_vblank(स्थिर काष्ठा matroxfb_dh_fb_info* m2info, काष्ठा fb_vblank* vblank) अणु
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	matroxfb_enable_irq(minfo, 0);
	स_रखो(vblank, 0, माप(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VCOUNT | FB_VBLANK_HAVE_VBLANK;
	/* mask out reserved bits + field number (odd/even) */
	vblank->vcount = mga_inl(0x3C48) & 0x000007FF;
	/* compatibility stuff */
	अगर (vblank->vcount >= m2info->fbcon.var.yres)
		vblank->flags |= FB_VBLANK_VBLANKING;
	अगर (test_bit(0, &minfo->irq_flags)) अणु
                vblank->flags |= FB_VBLANK_HAVE_COUNT;
                /* Only one ग_लिखोr, aligned पूर्णांक value...
                   it should work without lock and without atomic_t */
		vblank->count = minfo->crtc2.vsync.cnt;
        पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_dh_ioctl(काष्ठा fb_info *info,
		अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	काष्ठा matrox_fb_info *minfo = m2info->primary_dev;

	DBG(__func__)

	चयन (cmd) अणु
		हाल FBIOGET_VBLANK:
			अणु
				काष्ठा fb_vblank vblank;
				पूर्णांक err;

				err = matroxfb_dh_get_vblank(m2info, &vblank);
				अगर (err)
					वापस err;
				अगर (copy_to_user((व्योम __user *)arg, &vblank, माप(vblank)))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल FBIO_WAITFORVSYNC:
			अणु
				u_पूर्णांक32_t crt;

				अगर (get_user(crt, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;

				अगर (crt != 0)
					वापस -ENODEV;
				वापस matroxfb_रुको_क्रम_sync(minfo, 1);
			पूर्ण
		हाल MATROXFB_SET_OUTPUT_MODE:
		हाल MATROXFB_GET_OUTPUT_MODE:
		हाल MATROXFB_GET_ALL_OUTPUTS:
			अणु
				वापस minfo->fbcon.fbops->fb_ioctl(&minfo->fbcon, cmd, arg);
			पूर्ण
		हाल MATROXFB_SET_OUTPUT_CONNECTION:
			अणु
				u_पूर्णांक32_t पंचांगp;
				पूर्णांक out;
				पूर्णांक changes;

				अगर (get_user(पंचांगp, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				क्रम (out = 0; out < 32; out++) अणु
					अगर (पंचांगp & (1 << out)) अणु
						अगर (out >= MATROXFB_MAX_OUTPUTS)
							वापस -ENXIO;
						अगर (!minfo->outमाला_दो[out].output)
							वापस -ENXIO;
						चयन (minfo->outमाला_दो[out].src) अणु
							हाल MATROXFB_SRC_NONE:
							हाल MATROXFB_SRC_CRTC2:
								अवरोध;
							शेष:
								वापस -EBUSY;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (minfo->devflags.panellink) अणु
					अगर (पंचांगp & MATROXFB_OUTPUT_CONN_DFP)
						वापस -EINVAL;
					अगर ((minfo->outमाला_दो[2].src == MATROXFB_SRC_CRTC1) && पंचांगp)
						वापस -EBUSY;
				पूर्ण
				changes = 0;
				क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
					अगर (पंचांगp & (1 << out)) अणु
						अगर (minfo->outमाला_दो[out].src != MATROXFB_SRC_CRTC2) अणु
							changes = 1;
							minfo->outमाला_दो[out].src = MATROXFB_SRC_CRTC2;
						पूर्ण
					पूर्ण अन्यथा अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC2) अणु
						changes = 1;
						minfo->outमाला_दो[out].src = MATROXFB_SRC_NONE;
					पूर्ण
				पूर्ण
				अगर (!changes)
					वापस 0;
				matroxfb_dh_set_par(info);
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_OUTPUT_CONNECTION:
			अणु
				u_पूर्णांक32_t conn = 0;
				पूर्णांक out;

				क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
					अगर (minfo->outमाला_दो[out].src == MATROXFB_SRC_CRTC2) अणु
						conn |= 1 << out;
					पूर्ण
				पूर्ण
				अगर (put_user(conn, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
		हाल MATROXFB_GET_AVAILABLE_OUTPUTS:
			अणु
				u_पूर्णांक32_t पंचांगp = 0;
				पूर्णांक out;

				क्रम (out = 0; out < MATROXFB_MAX_OUTPUTS; out++) अणु
					अगर (minfo->outमाला_दो[out].output) अणु
						चयन (minfo->outमाला_दो[out].src) अणु
							हाल MATROXFB_SRC_NONE:
							हाल MATROXFB_SRC_CRTC2:
								पंचांगp |= 1 << out;
								अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (minfo->devflags.panellink) अणु
					पंचांगp &= ~MATROXFB_OUTPUT_CONN_DFP;
					अगर (minfo->outमाला_दो[2].src == MATROXFB_SRC_CRTC1) अणु
						पंचांगp = 0;
					पूर्ण
				पूर्ण
				अगर (put_user(पंचांगp, (u_पूर्णांक32_t __user *)arg))
					वापस -EFAULT;
				वापस 0;
			पूर्ण
	पूर्ण
	वापस -ENOTTY;
#अघोषित m2info
पूर्ण

अटल पूर्णांक matroxfb_dh_blank(पूर्णांक blank, काष्ठा fb_info* info) अणु
#घोषणा m2info (container_of(info, काष्ठा matroxfb_dh_fb_info, fbcon))
	चयन (blank) अणु
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		शेष:;
	पूर्ण
	/* करो something... */
	वापस 0;
#अघोषित m2info
पूर्ण

अटल स्थिर काष्ठा fb_ops matroxfb_dh_ops = अणु
	.owner =	THIS_MODULE,
	.fb_खोलो =	matroxfb_dh_खोलो,
	.fb_release =	matroxfb_dh_release,
	.fb_check_var =	matroxfb_dh_check_var,
	.fb_set_par =	matroxfb_dh_set_par,
	.fb_setcolreg =	matroxfb_dh_setcolreg,
	.fb_pan_display =matroxfb_dh_pan_display,
	.fb_blank =	matroxfb_dh_blank,
	.fb_ioctl =	matroxfb_dh_ioctl,
	.fb_fillrect =	cfb_fillrect,
	.fb_copyarea =	cfb_copyarea,
	.fb_imageblit =	cfb_imageblit,
पूर्ण;

अटल काष्ठा fb_var_screeninfo matroxfb_dh_defined = अणु
		640,480,640,480,/* W,H, भव W,H */
		0,0,		/* offset */
		32,		/* depth */
		0,		/* gray */
		अणु0,0,0पूर्ण,	/* R */
		अणु0,0,0पूर्ण,	/* G */
		अणु0,0,0पूर्ण,	/* B */
		अणु0,0,0पूर्ण,	/* alpha */
		0,		/* nonstd */
		FB_ACTIVATE_NOW,
		-1,-1,		/* display size */
		0,		/* accel flags */
		39721L,48L,16L,33L,10L,
		96L,2,0,	/* no sync info */
		FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक matroxfb_dh_regit(स्थिर काष्ठा matrox_fb_info *minfo,
			     काष्ठा matroxfb_dh_fb_info *m2info)
अणु
#घोषणा minfo (m2info->primary_dev)
	व्योम* oldcrtc2;

	m2info->fbcon.fbops = &matroxfb_dh_ops;
	m2info->fbcon.flags = FBINFO_FLAG_DEFAULT;
	m2info->fbcon.flags |= FBINFO_HWACCEL_XPAN |
			       FBINFO_HWACCEL_YPAN;
	m2info->fbcon.pseuकरो_palette = m2info->cmap;
	fb_alloc_cmap(&m2info->fbcon.cmap, 256, 1);

	अगर (mem < 64)
		mem *= 1024;
	अगर (mem < 64*1024)
		mem *= 1024;
	mem &= ~0x00000FFF;	/* PAGE_MASK? */
	अगर (minfo->video.len_usable + mem <= minfo->video.len)
		m2info->video.offbase = minfo->video.len - mem;
	अन्यथा अगर (minfo->video.len < mem) अणु
		वापस -ENOMEM;
	पूर्ण अन्यथा अणु /* check yres on first head... */
		m2info->video.borrowed = mem;
		minfo->video.len_usable -= mem;
		m2info->video.offbase = minfo->video.len_usable;
	पूर्ण
	m2info->video.base = minfo->video.base + m2info->video.offbase;
	m2info->video.len = m2info->video.len_usable = m2info->video.len_maximum = mem;
	m2info->video.vbase.vaddr = vaddr_va(minfo->video.vbase) + m2info->video.offbase;
	m2info->mmio.base = minfo->mmio.base;
	m2info->mmio.vbase = minfo->mmio.vbase;
	m2info->mmio.len = minfo->mmio.len;

	matroxfb_dh_init_fix(m2info);
	अगर (रेजिस्टर_framebuffer(&m2info->fbcon)) अणु
		वापस -ENXIO;
	पूर्ण
	अगर (!m2info->initialized)
		fb_set_var(&m2info->fbcon, &matroxfb_dh_defined);
	करोwn_ग_लिखो(&minfo->crtc2.lock);
	oldcrtc2 = minfo->crtc2.info;
	minfo->crtc2.info = m2info;
	up_ग_लिखो(&minfo->crtc2.lock);
	अगर (oldcrtc2) अणु
		prपूर्णांकk(KERN_ERR "matroxfb_crtc2: Internal consistency check failed: crtc2 already present: %p\n",
			oldcrtc2);
	पूर्ण
	वापस 0;
#अघोषित minfo
पूर्ण

/* ************************** */

अटल पूर्णांक matroxfb_dh_रेजिस्टरfb(काष्ठा matroxfb_dh_fb_info* m2info) अणु
#घोषणा minfo (m2info->primary_dev)
	अगर (matroxfb_dh_regit(minfo, m2info)) अणु
		prपूर्णांकk(KERN_ERR "matroxfb_crtc2: secondary head failed to register\n");
		वापस -1;
	पूर्ण
	prपूर्णांकk(KERN_INFO "matroxfb_crtc2: secondary head of fb%u was registered as fb%u\n",
		minfo->fbcon.node, m2info->fbcon.node);
	m2info->fbcon_रेजिस्टरed = 1;
	वापस 0;
#अघोषित minfo
पूर्ण

अटल व्योम matroxfb_dh_deरेजिस्टरfb(काष्ठा matroxfb_dh_fb_info* m2info) अणु
#घोषणा minfo (m2info->primary_dev)
	अगर (m2info->fbcon_रेजिस्टरed) अणु
		पूर्णांक id;
		काष्ठा matroxfb_dh_fb_info* crtc2;

		करोwn_ग_लिखो(&minfo->crtc2.lock);
		crtc2 = minfo->crtc2.info;
		अगर (crtc2 == m2info)
			minfo->crtc2.info = शून्य;
		up_ग_लिखो(&minfo->crtc2.lock);
		अगर (crtc2 != m2info) अणु
			prपूर्णांकk(KERN_ERR "matroxfb_crtc2: Internal consistency check failed: crtc2 mismatch at unload: %p != %p\n",
				crtc2, m2info);
			prपूर्णांकk(KERN_ERR "matroxfb_crtc2: Expect kernel crash after module unload.\n");
			वापस;
		पूर्ण
		id = m2info->fbcon.node;
		unरेजिस्टर_framebuffer(&m2info->fbcon);
		/* वापस memory back to primary head */
		minfo->video.len_usable += m2info->video.borrowed;
		prपूर्णांकk(KERN_INFO "matroxfb_crtc2: fb%u unregistered\n", id);
		m2info->fbcon_रेजिस्टरed = 0;
	पूर्ण
#अघोषित minfo
पूर्ण

अटल व्योम* matroxfb_crtc2_probe(काष्ठा matrox_fb_info* minfo) अणु
	काष्ठा matroxfb_dh_fb_info* m2info;

	/* hardware is CRTC2 incapable... */
	अगर (!minfo->devflags.crtc2)
		वापस शून्य;
	m2info = kzalloc(माप(*m2info), GFP_KERNEL);
	अगर (!m2info)
		वापस शून्य;

	m2info->primary_dev = minfo;
	अगर (matroxfb_dh_रेजिस्टरfb(m2info)) अणु
		kमुक्त(m2info);
		prपूर्णांकk(KERN_ERR "matroxfb_crtc2: CRTC2 framebuffer failed to register\n");
		वापस शून्य;
	पूर्ण
	वापस m2info;
पूर्ण

अटल व्योम matroxfb_crtc2_हटाओ(काष्ठा matrox_fb_info* minfo, व्योम* crtc2) अणु
	matroxfb_dh_deरेजिस्टरfb(crtc2);
	kमुक्त(crtc2);
पूर्ण

अटल काष्ठा matroxfb_driver crtc2 = अणु
		.name =		"Matrox G400 CRTC2",
		.probe =	matroxfb_crtc2_probe,
		.हटाओ =	matroxfb_crtc2_हटाओ पूर्ण;

अटल पूर्णांक matroxfb_crtc2_init(व्योम) अणु
	अगर (fb_get_options("matrox_crtc2fb", शून्य))
		वापस -ENODEV;

	matroxfb_रेजिस्टर_driver(&crtc2);
	वापस 0;
पूर्ण

अटल व्योम matroxfb_crtc2_निकास(व्योम) अणु
	matroxfb_unरेजिस्टर_driver(&crtc2);
पूर्ण

MODULE_AUTHOR("(c) 1999-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Matrox G400 CRTC2 driver");
MODULE_LICENSE("GPL");
module_init(matroxfb_crtc2_init);
module_निकास(matroxfb_crtc2_निकास);
/* we करो not have __setup() yet */
