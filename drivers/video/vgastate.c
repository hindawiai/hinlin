<शैली गुरु>
/*
 * linux/drivers/video/vgastate.c -- VGA state save/restore
 *
 * Copyright 2002 James Simmons
 *
 * Copyright history from vga16fb.c:
 *	Copyright 1999 Ben Pfaff and Petr Vandrovec
 *	Based on VGA info at http://www.goodnet.com/~tinara/FreeVGA/home.hपंचांग
 *	Based on VESA framebuffer (c) 1998 Gerd Knorr
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <video/vga.h>

काष्ठा regstate अणु
	__u8 *vga_font0;
	__u8 *vga_font1;
	__u8 *vga_text;
	__u8 *vga_cmap;
	__u8 *attr;
	__u8 *crtc;
	__u8 *gfx;
	__u8 *seq;
	__u8 misc;
पूर्ण;

अटल अंतरभूत अचिन्हित अक्षर vga_rcrtcs(व्योम __iomem *regbase, अचिन्हित लघु iobase,
				       अचिन्हित अक्षर reg)
अणु
	vga_w(regbase, iobase + 0x4, reg);
	वापस vga_r(regbase, iobase + 0x5);
पूर्ण

अटल अंतरभूत व्योम vga_wcrtcs(व्योम __iomem *regbase, अचिन्हित लघु iobase,
			      अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	vga_w(regbase, iobase + 0x4, reg);
	vga_w(regbase, iobase + 0x5, val);
पूर्ण

अटल व्योम save_vga_text(काष्ठा vgastate *state, व्योम __iomem *fbbase)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	पूर्णांक i;
	u8 misc, attr10, gr4, gr5, gr6, seq1, seq2, seq4;
	अचिन्हित लघु iobase;

	/* अगर in graphics mode, no need to save */
	misc = vga_r(state->vgabase, VGA_MIS_R);
	iobase = (misc & 1) ? 0x3d0 : 0x3b0;

	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x00);
	attr10 = vga_rattr(state->vgabase, 0x10);
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);

	अगर (attr10 & 1)
		वापस;

	/* save regs */
	gr4 = vga_rgfx(state->vgabase, VGA_GFX_PLANE_READ);
	gr5 = vga_rgfx(state->vgabase, VGA_GFX_MODE);
	gr6 = vga_rgfx(state->vgabase, VGA_GFX_MISC);
	seq2 = vga_rseq(state->vgabase, VGA_SEQ_PLANE_WRITE);
	seq4 = vga_rseq(state->vgabase, VGA_SEQ_MEMORY_MODE);

	/* blank screen */
	seq1 = vga_rseq(state->vgabase, VGA_SEQ_CLOCK_MODE);
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1 | 1 << 5);
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x3);

	/* save font at plane 2 */
	अगर (state->flags & VGA_SAVE_FONT0) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x4);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x2);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 4 * 8192; i++)
			saved->vga_font0[i] = vga_r(fbbase, i);
	पूर्ण

	/* save font at plane 3 */
	अगर (state->flags & VGA_SAVE_FONT1) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x8);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x3);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < state->memsize; i++)
			saved->vga_font1[i] = vga_r(fbbase, i);
	पूर्ण

	/* save font at plane 0/1 */
	अगर (state->flags & VGA_SAVE_TEXT) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x1);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 8192; i++)
			saved->vga_text[i] = vga_r(fbbase, i);

		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x2);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x1);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 8192; i++)
			saved->vga_text[8192+i] = vga_r(fbbase + 2 * 8192, i);
	पूर्ण

	/* restore regs */
	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, seq2);
	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, seq4);

	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, gr4);
	vga_wgfx(state->vgabase, VGA_GFX_MODE, gr5);
	vga_wgfx(state->vgabase, VGA_GFX_MISC, gr6);

	/* unblank screen */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1 & ~(1 << 5));
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x3);

	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1);
पूर्ण

अटल व्योम restore_vga_text(काष्ठा vgastate *state, व्योम __iomem *fbbase)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	पूर्णांक i;
	u8 gr1, gr3, gr4, gr5, gr6, gr8;
	u8 seq1, seq2, seq4;

	/* save regs */
	gr1 = vga_rgfx(state->vgabase, VGA_GFX_SR_ENABLE);
	gr3 = vga_rgfx(state->vgabase, VGA_GFX_DATA_ROTATE);
	gr4 = vga_rgfx(state->vgabase, VGA_GFX_PLANE_READ);
	gr5 = vga_rgfx(state->vgabase, VGA_GFX_MODE);
	gr6 = vga_rgfx(state->vgabase, VGA_GFX_MISC);
	gr8 = vga_rgfx(state->vgabase, VGA_GFX_BIT_MASK);
	seq2 = vga_rseq(state->vgabase, VGA_SEQ_PLANE_WRITE);
	seq4 = vga_rseq(state->vgabase, VGA_SEQ_MEMORY_MODE);

	/* blank screen */
	seq1 = vga_rseq(state->vgabase, VGA_SEQ_CLOCK_MODE);
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1 | 1 << 5);
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x3);

	अगर (state->depth == 4) अणु
		vga_wgfx(state->vgabase, VGA_GFX_DATA_ROTATE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_BIT_MASK, 0xff);
		vga_wgfx(state->vgabase, VGA_GFX_SR_ENABLE, 0x00);
	पूर्ण

	/* restore font at plane 2 */
	अगर (state->flags & VGA_SAVE_FONT0) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x4);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x2);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 4 * 8192; i++)
			vga_w(fbbase, i, saved->vga_font0[i]);
	पूर्ण

	/* restore font at plane 3 */
	अगर (state->flags & VGA_SAVE_FONT1) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x8);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x3);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < state->memsize; i++)
			vga_w(fbbase, i, saved->vga_font1[i]);
	पूर्ण

	/* restore font at plane 0/1 */
	अगर (state->flags & VGA_SAVE_TEXT) अणु
		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x1);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 8192; i++)
			vga_w(fbbase, i, saved->vga_text[i]);

		vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x2);
		vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x6);
		vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x1);
		vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x0);
		vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x5);
		क्रम (i = 0; i < 8192; i++)
			vga_w(fbbase, i, saved->vga_text[8192+i]);
	पूर्ण

	/* unblank screen */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1 & ~(1 << 5));
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x3);

	/* restore regs */
	vga_wgfx(state->vgabase, VGA_GFX_SR_ENABLE, gr1);
	vga_wgfx(state->vgabase, VGA_GFX_DATA_ROTATE, gr3);
	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, gr4);
	vga_wgfx(state->vgabase, VGA_GFX_MODE, gr5);
	vga_wgfx(state->vgabase, VGA_GFX_MISC, gr6);
	vga_wgfx(state->vgabase, VGA_GFX_BIT_MASK, gr8);

	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, seq1);
	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, seq2);
	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, seq4);
पूर्ण

अटल व्योम save_vga_mode(काष्ठा vgastate *state)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	अचिन्हित लघु iobase;
	पूर्णांक i;

	saved->misc = vga_r(state->vgabase, VGA_MIS_R);
	अगर (saved->misc & 1)
		iobase = 0x3d0;
	अन्यथा
		iobase = 0x3b0;

	क्रम (i = 0; i < state->num_crtc; i++)
		saved->crtc[i] = vga_rcrtcs(state->vgabase, iobase, i);

	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x00);
	क्रम (i = 0; i < state->num_attr; i++) अणु
		vga_r(state->vgabase, iobase + 0xa);
		saved->attr[i] = vga_rattr(state->vgabase, i);
	पूर्ण
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);

	क्रम (i = 0; i < state->num_gfx; i++)
		saved->gfx[i] = vga_rgfx(state->vgabase, i);

	क्रम (i = 0; i < state->num_seq; i++)
		saved->seq[i] = vga_rseq(state->vgabase, i);
पूर्ण

अटल व्योम restore_vga_mode(काष्ठा vgastate *state)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	अचिन्हित लघु iobase;
	पूर्णांक i;

	vga_w(state->vgabase, VGA_MIS_W, saved->misc);

	अगर (saved->misc & 1)
		iobase = 0x3d0;
	अन्यथा
		iobase = 0x3b0;

	/* turn off display */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE,
		 saved->seq[VGA_SEQ_CLOCK_MODE] | 0x20);

	/* disable sequencer */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x01);

	/* enable palette addressing */
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x00);

	क्रम (i = 2; i < state->num_seq; i++)
		vga_wseq(state->vgabase, i, saved->seq[i]);


	/* unprotect vga regs */
	vga_wcrtcs(state->vgabase, iobase, 17, saved->crtc[17] & ~0x80);
	क्रम (i = 0; i < state->num_crtc; i++)
		vga_wcrtcs(state->vgabase, iobase, i, saved->crtc[i]);

	क्रम (i = 0; i < state->num_gfx; i++)
		vga_wgfx(state->vgabase, i, saved->gfx[i]);

	क्रम (i = 0; i < state->num_attr; i++) अणु
		vga_r(state->vgabase, iobase + 0xa);
		vga_wattr(state->vgabase, i, saved->attr[i]);
	पूर्ण

	/* reenable sequencer */
	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);
	/* turn display on */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE,
		 saved->seq[VGA_SEQ_CLOCK_MODE] & ~(1 << 5));

	/* disable video/palette source */
	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);
पूर्ण

अटल व्योम save_vga_cmap(काष्ठा vgastate *state)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	पूर्णांक i;

	vga_w(state->vgabase, VGA_PEL_MSK, 0xff);

	/* assumes DAC is पढ़ोable and writable */
	vga_w(state->vgabase, VGA_PEL_IR, 0x00);
	क्रम (i = 0; i < 768; i++)
		saved->vga_cmap[i] = vga_r(state->vgabase, VGA_PEL_D);
पूर्ण

अटल व्योम restore_vga_cmap(काष्ठा vgastate *state)
अणु
	काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;
	पूर्णांक i;

	vga_w(state->vgabase, VGA_PEL_MSK, 0xff);

	/* assumes DAC is पढ़ोable and writable */
	vga_w(state->vgabase, VGA_PEL_IW, 0x00);
	क्रम (i = 0; i < 768; i++)
		vga_w(state->vgabase, VGA_PEL_D, saved->vga_cmap[i]);
पूर्ण

अटल व्योम vga_cleanup(काष्ठा vgastate *state)
अणु
	अगर (state->vidstate != शून्य) अणु
		काष्ठा regstate *saved = (काष्ठा regstate *) state->vidstate;

		vमुक्त(saved->vga_font0);
		vमुक्त(saved->vga_font1);
		vमुक्त(saved->vga_text);
		vमुक्त(saved->vga_cmap);
		vमुक्त(saved->attr);
		kमुक्त(saved);
		state->vidstate = शून्य;
	पूर्ण
पूर्ण

पूर्णांक save_vga(काष्ठा vgastate *state)
अणु
	काष्ठा regstate *saved;

	saved = kzalloc(माप(काष्ठा regstate), GFP_KERNEL);

	अगर (saved == शून्य)
		वापस 1;

	state->vidstate = (व्योम *)saved;

	अगर (state->flags & VGA_SAVE_CMAP) अणु
		saved->vga_cmap = vदो_स्मृति(768);
		अगर (!saved->vga_cmap) अणु
			vga_cleanup(state);
			वापस 1;
		पूर्ण
		save_vga_cmap(state);
	पूर्ण

	अगर (state->flags & VGA_SAVE_MODE) अणु
		पूर्णांक total;

		अगर (state->num_attr < 21)
			state->num_attr = 21;
		अगर (state->num_crtc < 25)
			state->num_crtc = 25;
		अगर (state->num_gfx < 9)
			state->num_gfx = 9;
		अगर (state->num_seq < 5)
			state->num_seq = 5;
		total = state->num_attr + state->num_crtc +
			state->num_gfx + state->num_seq;

		saved->attr = vदो_स्मृति(total);
		अगर (!saved->attr) अणु
			vga_cleanup(state);
			वापस 1;
		पूर्ण
		saved->crtc = saved->attr + state->num_attr;
		saved->gfx = saved->crtc + state->num_crtc;
		saved->seq = saved->gfx + state->num_gfx;

		save_vga_mode(state);
	पूर्ण

	अगर (state->flags & VGA_SAVE_FONTS) अणु
		व्योम __iomem *fbbase;

		/* निकास अगर winकरोw is less than 32K */
		अगर (state->memsize && state->memsize < 4 * 8192) अणु
			vga_cleanup(state);
			वापस 1;
		पूर्ण
		अगर (!state->memsize)
			state->memsize = 8 * 8192;

		अगर (!state->membase)
			state->membase = 0xA0000;

		fbbase = ioremap(state->membase, state->memsize);

		अगर (!fbbase) अणु
			vga_cleanup(state);
			वापस 1;
		पूर्ण

		/*
		 * save only first 32K used by vgacon
		 */
		अगर (state->flags & VGA_SAVE_FONT0) अणु
			saved->vga_font0 = vदो_स्मृति(4 * 8192);
			अगर (!saved->vga_font0) अणु
				iounmap(fbbase);
				vga_cleanup(state);
				वापस 1;
			पूर्ण
		पूर्ण
		/*
		 * largely unused, but अगर required by the caller
		 * we'll just save everything.
		 */
		अगर (state->flags & VGA_SAVE_FONT1) अणु
			saved->vga_font1 = vदो_स्मृति(state->memsize);
			अगर (!saved->vga_font1) अणु
				iounmap(fbbase);
				vga_cleanup(state);
				वापस 1;
			पूर्ण
		पूर्ण
		/*
		 * Save 8K at plane0[0], and 8K at plane1[16K]
		 */
		अगर (state->flags & VGA_SAVE_TEXT) अणु
			saved->vga_text = vदो_स्मृति(8192 * 2);
			अगर (!saved->vga_text) अणु
				iounmap(fbbase);
				vga_cleanup(state);
				वापस 1;
			पूर्ण
		पूर्ण

		save_vga_text(state, fbbase);
		iounmap(fbbase);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक restore_vga(काष्ठा vgastate *state)
अणु
	अगर (state->vidstate == शून्य)
		वापस 1;

	अगर (state->flags & VGA_SAVE_MODE)
		restore_vga_mode(state);

	अगर (state->flags & VGA_SAVE_FONTS) अणु
		व्योम __iomem *fbbase = ioremap(state->membase, state->memsize);

		अगर (!fbbase) अणु
			vga_cleanup(state);
			वापस 1;
		पूर्ण
		restore_vga_text(state, fbbase);
		iounmap(fbbase);
	पूर्ण

	अगर (state->flags & VGA_SAVE_CMAP)
		restore_vga_cmap(state);

	vga_cleanup(state);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(save_vga);
EXPORT_SYMBOL(restore_vga);

MODULE_AUTHOR("James Simmons <jsimmons@users.sf.net>");
MODULE_DESCRIPTION("VGA State Save/Restore");
MODULE_LICENSE("GPL");

