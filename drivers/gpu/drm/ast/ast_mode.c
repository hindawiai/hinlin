<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 * Parts based on xf86-video-ast
 * Copyright (c) 2005 ASPEED Technology Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "ast_drv.h"
#समावेश "ast_tables.h"

अटल काष्ठा ast_i2c_chan *ast_i2c_create(काष्ठा drm_device *dev);
अटल व्योम ast_i2c_destroy(काष्ठा ast_i2c_chan *i2c);

अटल अंतरभूत व्योम ast_load_palette_index(काष्ठा ast_निजी *ast,
				     u8 index, u8 red, u8 green,
				     u8 blue)
अणु
	ast_io_ग_लिखो8(ast, AST_IO_DAC_INDEX_WRITE, index);
	ast_io_पढ़ो8(ast, AST_IO_SEQ_PORT);
	ast_io_ग_लिखो8(ast, AST_IO_DAC_DATA, red);
	ast_io_पढ़ो8(ast, AST_IO_SEQ_PORT);
	ast_io_ग_लिखो8(ast, AST_IO_DAC_DATA, green);
	ast_io_पढ़ो8(ast, AST_IO_SEQ_PORT);
	ast_io_ग_लिखो8(ast, AST_IO_DAC_DATA, blue);
	ast_io_पढ़ो8(ast, AST_IO_SEQ_PORT);
पूर्ण

अटल व्योम ast_crtc_load_lut(काष्ठा ast_निजी *ast, काष्ठा drm_crtc *crtc)
अणु
	u16 *r, *g, *b;
	पूर्णांक i;

	अगर (!crtc->enabled)
		वापस;

	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	क्रम (i = 0; i < 256; i++)
		ast_load_palette_index(ast, i, *r++ >> 8, *g++ >> 8, *b++ >> 8);
पूर्ण

अटल bool ast_get_vbios_mode_info(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode,
				    काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	u32 refresh_rate_index = 0, refresh_rate;
	स्थिर काष्ठा ast_vbios_enhtable *best = शून्य;
	u32 hborder, vborder;
	bool check_sync;

	चयन (क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		vbios_mode->std_table = &vbios_stdtable[VGAModeIndex];
		अवरोध;
	हाल 16:
		vbios_mode->std_table = &vbios_stdtable[HiCModeIndex];
		अवरोध;
	हाल 24:
	हाल 32:
		vbios_mode->std_table = &vbios_stdtable[TrueCModeIndex];
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (mode->crtc_hdisplay) अणु
	हाल 640:
		vbios_mode->enh_table = &res_640x480[refresh_rate_index];
		अवरोध;
	हाल 800:
		vbios_mode->enh_table = &res_800x600[refresh_rate_index];
		अवरोध;
	हाल 1024:
		vbios_mode->enh_table = &res_1024x768[refresh_rate_index];
		अवरोध;
	हाल 1280:
		अगर (mode->crtc_vdisplay == 800)
			vbios_mode->enh_table = &res_1280x800[refresh_rate_index];
		अन्यथा
			vbios_mode->enh_table = &res_1280x1024[refresh_rate_index];
		अवरोध;
	हाल 1360:
		vbios_mode->enh_table = &res_1360x768[refresh_rate_index];
		अवरोध;
	हाल 1440:
		vbios_mode->enh_table = &res_1440x900[refresh_rate_index];
		अवरोध;
	हाल 1600:
		अगर (mode->crtc_vdisplay == 900)
			vbios_mode->enh_table = &res_1600x900[refresh_rate_index];
		अन्यथा
			vbios_mode->enh_table = &res_1600x1200[refresh_rate_index];
		अवरोध;
	हाल 1680:
		vbios_mode->enh_table = &res_1680x1050[refresh_rate_index];
		अवरोध;
	हाल 1920:
		अगर (mode->crtc_vdisplay == 1080)
			vbios_mode->enh_table = &res_1920x1080[refresh_rate_index];
		अन्यथा
			vbios_mode->enh_table = &res_1920x1200[refresh_rate_index];
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	refresh_rate = drm_mode_vrefresh(mode);
	check_sync = vbios_mode->enh_table->flags & WideScreenMode;

	जबतक (1) अणु
		स्थिर काष्ठा ast_vbios_enhtable *loop = vbios_mode->enh_table;

		जबतक (loop->refresh_rate != 0xff) अणु
			अगर ((check_sync) &&
			    (((mode->flags & DRM_MODE_FLAG_NVSYNC)  &&
			      (loop->flags & PVSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_PVSYNC)  &&
			      (loop->flags & NVSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_NHSYNC)  &&
			      (loop->flags & PHSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_PHSYNC)  &&
			      (loop->flags & NHSync)))) अणु
				loop++;
				जारी;
			पूर्ण
			अगर (loop->refresh_rate <= refresh_rate
			    && (!best || loop->refresh_rate > best->refresh_rate))
				best = loop;
			loop++;
		पूर्ण
		अगर (best || !check_sync)
			अवरोध;
		check_sync = 0;
	पूर्ण

	अगर (best)
		vbios_mode->enh_table = best;

	hborder = (vbios_mode->enh_table->flags & HBorder) ? 8 : 0;
	vborder = (vbios_mode->enh_table->flags & VBorder) ? 8 : 0;

	adjusted_mode->crtc_htotal = vbios_mode->enh_table->ht;
	adjusted_mode->crtc_hblank_start = vbios_mode->enh_table->hde + hborder;
	adjusted_mode->crtc_hblank_end = vbios_mode->enh_table->ht - hborder;
	adjusted_mode->crtc_hsync_start = vbios_mode->enh_table->hde + hborder +
		vbios_mode->enh_table->hfp;
	adjusted_mode->crtc_hsync_end = (vbios_mode->enh_table->hde + hborder +
					 vbios_mode->enh_table->hfp +
					 vbios_mode->enh_table->hsync);

	adjusted_mode->crtc_vtotal = vbios_mode->enh_table->vt;
	adjusted_mode->crtc_vblank_start = vbios_mode->enh_table->vde + vborder;
	adjusted_mode->crtc_vblank_end = vbios_mode->enh_table->vt - vborder;
	adjusted_mode->crtc_vsync_start = vbios_mode->enh_table->vde + vborder +
		vbios_mode->enh_table->vfp;
	adjusted_mode->crtc_vsync_end = (vbios_mode->enh_table->vde + vborder +
					 vbios_mode->enh_table->vfp +
					 vbios_mode->enh_table->vsync);

	वापस true;
पूर्ण

अटल व्योम ast_set_vbios_color_reg(काष्ठा ast_निजी *ast,
				    स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				    स्थिर काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	u32 color_index;

	चयन (क्रमmat->cpp[0]) अणु
	हाल 1:
		color_index = VGAModeIndex - 1;
		अवरोध;
	हाल 2:
		color_index = HiCModeIndex;
		अवरोध;
	हाल 3:
	हाल 4:
		color_index = TrueCModeIndex;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8c, (u8)((color_index & 0x0f) << 4));

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0x00);

	अगर (vbios_mode->enh_table->flags & NewModeInfo) अणु
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0xa8);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x92, क्रमmat->cpp[0] * 8);
	पूर्ण
पूर्ण

अटल व्योम ast_set_vbios_mode_reg(काष्ठा ast_निजी *ast,
				   स्थिर काष्ठा drm_display_mode *adjusted_mode,
				   स्थिर काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	u32 refresh_rate_index, mode_id;

	refresh_rate_index = vbios_mode->enh_table->refresh_rate_index;
	mode_id = vbios_mode->enh_table->mode_id;

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8d, refresh_rate_index & 0xff);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8e, mode_id & 0xff);

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0x00);

	अगर (vbios_mode->enh_table->flags & NewModeInfo) अणु
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0xa8);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x93, adjusted_mode->घड़ी / 1000);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x94, adjusted_mode->crtc_hdisplay);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x95, adjusted_mode->crtc_hdisplay >> 8);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x96, adjusted_mode->crtc_vdisplay);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x97, adjusted_mode->crtc_vdisplay >> 8);
	पूर्ण
पूर्ण

अटल व्योम ast_set_std_reg(काष्ठा ast_निजी *ast,
			    काष्ठा drm_display_mode *mode,
			    काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	स्थिर काष्ठा ast_vbios_stdtable *stdtable;
	u32 i;
	u8 jreg;

	stdtable = vbios_mode->std_table;

	jreg = stdtable->misc;
	ast_io_ग_लिखो8(ast, AST_IO_MISC_PORT_WRITE, jreg);

	/* Set SEQ; except Screen Disable field */
	ast_set_index_reg(ast, AST_IO_SEQ_PORT, 0x00, 0x03);
	ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x01, 0xdf, stdtable->seq[0]);
	क्रम (i = 1; i < 4; i++) अणु
		jreg = stdtable->seq[i];
		ast_set_index_reg(ast, AST_IO_SEQ_PORT, (i + 1) , jreg);
	पूर्ण

	/* Set CRTC; except base address and offset */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x11, 0x7f, 0x00);
	क्रम (i = 0; i < 12; i++)
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, i, stdtable->crtc[i]);
	क्रम (i = 14; i < 19; i++)
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, i, stdtable->crtc[i]);
	क्रम (i = 20; i < 25; i++)
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, i, stdtable->crtc[i]);

	/* set AR */
	jreg = ast_io_पढ़ो8(ast, AST_IO_INPUT_STATUS1_READ);
	क्रम (i = 0; i < 20; i++) अणु
		jreg = stdtable->ar[i];
		ast_io_ग_लिखो8(ast, AST_IO_AR_PORT_WRITE, (u8)i);
		ast_io_ग_लिखो8(ast, AST_IO_AR_PORT_WRITE, jreg);
	पूर्ण
	ast_io_ग_लिखो8(ast, AST_IO_AR_PORT_WRITE, 0x14);
	ast_io_ग_लिखो8(ast, AST_IO_AR_PORT_WRITE, 0x00);

	jreg = ast_io_पढ़ो8(ast, AST_IO_INPUT_STATUS1_READ);
	ast_io_ग_लिखो8(ast, AST_IO_AR_PORT_WRITE, 0x20);

	/* Set GR */
	क्रम (i = 0; i < 9; i++)
		ast_set_index_reg(ast, AST_IO_GR_PORT, i, stdtable->gr[i]);
पूर्ण

अटल व्योम ast_set_crtc_reg(काष्ठा ast_निजी *ast,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	u8 jreg05 = 0, jreg07 = 0, jreg09 = 0, jregAC = 0, jregAD = 0, jregAE = 0;
	u16 temp, precache = 0;

	अगर ((ast->chip == AST2500) &&
	    (vbios_mode->enh_table->flags & AST2500PreCatchCRT))
		precache = 40;

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x11, 0x7f, 0x00);

	temp = (mode->crtc_htotal >> 3) - 5;
	अगर (temp & 0x100)
		jregAC |= 0x01; /* HT D[8] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x00, 0x00, temp);

	temp = (mode->crtc_hdisplay >> 3) - 1;
	अगर (temp & 0x100)
		jregAC |= 0x04; /* HDE D[8] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x01, 0x00, temp);

	temp = (mode->crtc_hblank_start >> 3) - 1;
	अगर (temp & 0x100)
		jregAC |= 0x10; /* HBS D[8] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x02, 0x00, temp);

	temp = ((mode->crtc_hblank_end >> 3) - 1) & 0x7f;
	अगर (temp & 0x20)
		jreg05 |= 0x80;  /* HBE D[5] */
	अगर (temp & 0x40)
		jregAD |= 0x01;  /* HBE D[5] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x03, 0xE0, (temp & 0x1f));

	temp = ((mode->crtc_hsync_start-precache) >> 3) - 1;
	अगर (temp & 0x100)
		jregAC |= 0x40; /* HRS D[5] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x04, 0x00, temp);

	temp = (((mode->crtc_hsync_end-precache) >> 3) - 1) & 0x3f;
	अगर (temp & 0x20)
		jregAD |= 0x04; /* HRE D[5] */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x05, 0x60, (u8)((temp & 0x1f) | jreg05));

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xAC, 0x00, jregAC);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xAD, 0x00, jregAD);

	/* vert timings */
	temp = (mode->crtc_vtotal) - 2;
	अगर (temp & 0x100)
		jreg07 |= 0x01;
	अगर (temp & 0x200)
		jreg07 |= 0x20;
	अगर (temp & 0x400)
		jregAE |= 0x01;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x06, 0x00, temp);

	temp = (mode->crtc_vsync_start) - 1;
	अगर (temp & 0x100)
		jreg07 |= 0x04;
	अगर (temp & 0x200)
		jreg07 |= 0x80;
	अगर (temp & 0x400)
		jregAE |= 0x08;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x10, 0x00, temp);

	temp = (mode->crtc_vsync_end - 1) & 0x3f;
	अगर (temp & 0x10)
		jregAE |= 0x20;
	अगर (temp & 0x20)
		jregAE |= 0x40;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x11, 0x70, temp & 0xf);

	temp = mode->crtc_vdisplay - 1;
	अगर (temp & 0x100)
		jreg07 |= 0x02;
	अगर (temp & 0x200)
		jreg07 |= 0x40;
	अगर (temp & 0x400)
		jregAE |= 0x02;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x12, 0x00, temp);

	temp = mode->crtc_vblank_start - 1;
	अगर (temp & 0x100)
		jreg07 |= 0x08;
	अगर (temp & 0x200)
		jreg09 |= 0x20;
	अगर (temp & 0x400)
		jregAE |= 0x04;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x15, 0x00, temp);

	temp = mode->crtc_vblank_end - 1;
	अगर (temp & 0x100)
		jregAE |= 0x10;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x16, 0x00, temp);

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x07, 0x00, jreg07);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x09, 0xdf, jreg09);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xAE, 0x00, (jregAE | 0x80));

	अगर (precache)
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb6, 0x3f, 0x80);
	अन्यथा
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb6, 0x3f, 0x00);

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x11, 0x7f, 0x80);
पूर्ण

अटल व्योम ast_set_offset_reg(काष्ठा ast_निजी *ast,
			       काष्ठा drm_framebuffer *fb)
अणु
	u16 offset;

	offset = fb->pitches[0] >> 3;
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x13, (offset & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xb0, (offset >> 8) & 0x3f);
पूर्ण

अटल व्योम ast_set_dclk_reg(काष्ठा ast_निजी *ast,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	स्थिर काष्ठा ast_vbios_dclk_info *clk_info;

	अगर (ast->chip == AST2500)
		clk_info = &dclk_table_ast2500[vbios_mode->enh_table->dclk_index];
	अन्यथा
		clk_info = &dclk_table[vbios_mode->enh_table->dclk_index];

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xc0, 0x00, clk_info->param1);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xc1, 0x00, clk_info->param2);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xbb, 0x0f,
			       (clk_info->param3 & 0xc0) |
			       ((clk_info->param3 & 0x3) << 4));
पूर्ण

अटल व्योम ast_set_color_reg(काष्ठा ast_निजी *ast,
			      स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	u8 jregA0 = 0, jregA3 = 0, jregA8 = 0;

	चयन (क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		jregA0 = 0x70;
		jregA3 = 0x01;
		jregA8 = 0x00;
		अवरोध;
	हाल 15:
	हाल 16:
		jregA0 = 0x70;
		jregA3 = 0x04;
		jregA8 = 0x02;
		अवरोध;
	हाल 32:
		jregA0 = 0x70;
		jregA3 = 0x08;
		jregA8 = 0x02;
		अवरोध;
	पूर्ण

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa0, 0x8f, jregA0);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xf0, jregA3);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa8, 0xfd, jregA8);
पूर्ण

अटल व्योम ast_set_crtthd_reg(काष्ठा ast_निजी *ast)
अणु
	/* Set Threshold */
	अगर (ast->chip == AST2300 || ast->chip == AST2400 ||
	    ast->chip == AST2500) अणु
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x78);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x60);
	पूर्ण अन्यथा अगर (ast->chip == AST2100 ||
		   ast->chip == AST1100 ||
		   ast->chip == AST2200 ||
		   ast->chip == AST2150) अणु
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x3f);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x2f);
	पूर्ण अन्यथा अणु
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x2f);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x1f);
	पूर्ण
पूर्ण

अटल व्योम ast_set_sync_reg(काष्ठा ast_निजी *ast,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा ast_vbios_mode_info *vbios_mode)
अणु
	u8 jreg;

	jreg  = ast_io_पढ़ो8(ast, AST_IO_MISC_PORT_READ);
	jreg &= ~0xC0;
	अगर (vbios_mode->enh_table->flags & NVSync) jreg |= 0x80;
	अगर (vbios_mode->enh_table->flags & NHSync) jreg |= 0x40;
	ast_io_ग_लिखो8(ast, AST_IO_MISC_PORT_WRITE, jreg);
पूर्ण

अटल व्योम ast_set_start_address_crt1(काष्ठा ast_निजी *ast,
				       अचिन्हित offset)
अणु
	u32 addr;

	addr = offset >> 2;
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x0d, (u8)(addr & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x0c, (u8)((addr >> 8) & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xaf, (u8)((addr >> 16) & 0xff));

पूर्ण

अटल व्योम ast_रुको_क्रम_vretrace(काष्ठा ast_निजी *ast)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	u8 vgair1;

	करो अणु
		vgair1 = ast_io_पढ़ो8(ast, AST_IO_INPUT_STATUS1_READ);
	पूर्ण जबतक (!(vgair1 & AST_IO_VGAIR1_VREFRESH) && समय_beक्रमe(jअगरfies, समयout));
पूर्ण

/*
 * Primary plane
 */

अटल स्थिर uपूर्णांक32_t ast_primary_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_C8,
पूर्ण;

अटल पूर्णांक ast_primary_plane_helper_atomic_check(काष्ठा drm_plane *plane,
						 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा ast_crtc_state *ast_crtc_state;
	पूर्णांक ret;

	अगर (!new_plane_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_new_crtc_state(state,
						   new_plane_state->crtc);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);
	अगर (ret)
		वापस ret;

	अगर (!new_plane_state->visible)
		वापस 0;

	ast_crtc_state = to_ast_crtc_state(crtc_state);

	ast_crtc_state->क्रमmat = new_plane_state->fb->क्रमmat;

	वापस 0;
पूर्ण

अटल व्योम
ast_primary_plane_helper_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_gem_vram_object *gbo;
	s64 gpu_addr;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_framebuffer *old_fb = old_state->fb;

	अगर (!old_fb || (fb->क्रमmat != old_fb->क्रमmat)) अणु
		काष्ठा drm_crtc_state *crtc_state = new_state->crtc->state;
		काष्ठा ast_crtc_state *ast_crtc_state = to_ast_crtc_state(crtc_state);
		काष्ठा ast_vbios_mode_info *vbios_mode_info = &ast_crtc_state->vbios_mode_info;

		ast_set_color_reg(ast, fb->क्रमmat);
		ast_set_vbios_color_reg(ast, fb->क्रमmat, vbios_mode_info);
	पूर्ण

	gbo = drm_gem_vram_of_gem(fb->obj[0]);
	gpu_addr = drm_gem_vram_offset(gbo);
	अगर (drm_WARN_ON_ONCE(dev, gpu_addr < 0))
		वापस; /* Bug: we didn't pin the BO to VRAM in prepare_fb. */

	ast_set_offset_reg(ast, fb);
	ast_set_start_address_crt1(ast, (u32)gpu_addr);

	ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x1, 0xdf, 0x00);
पूर्ण

अटल व्योम
ast_primary_plane_helper_atomic_disable(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(plane->dev);

	ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x1, 0xdf, 0x20);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs ast_primary_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_vram_plane_helper_prepare_fb,
	.cleanup_fb = drm_gem_vram_plane_helper_cleanup_fb,
	.atomic_check = ast_primary_plane_helper_atomic_check,
	.atomic_update = ast_primary_plane_helper_atomic_update,
	.atomic_disable = ast_primary_plane_helper_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs ast_primary_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल पूर्णांक ast_primary_plane_init(काष्ठा ast_निजी *ast)
अणु
	काष्ठा drm_device *dev = &ast->base;
	काष्ठा drm_plane *primary_plane = &ast->primary_plane;
	पूर्णांक ret;

	ret = drm_universal_plane_init(dev, primary_plane, 0x01,
				       &ast_primary_plane_funcs,
				       ast_primary_plane_क्रमmats,
				       ARRAY_SIZE(ast_primary_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		drm_err(dev, "drm_universal_plane_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण
	drm_plane_helper_add(primary_plane, &ast_primary_plane_helper_funcs);

	वापस 0;
पूर्ण

/*
 * Cursor plane
 */

अटल व्योम ast_update_cursor_image(u8 __iomem *dst, स्थिर u8 *src, पूर्णांक width, पूर्णांक height)
अणु
	जोड़ अणु
		u32 ul;
		u8 b[4];
	पूर्ण srcdata32[2], data32;
	जोड़ अणु
		u16 us;
		u8 b[2];
	पूर्ण data16;
	u32 csum = 0;
	s32 alpha_dst_delta, last_alpha_dst_delta;
	u8 __iomem *dstxor;
	स्थिर u8 *srcxor;
	पूर्णांक i, j;
	u32 per_pixel_copy, two_pixel_copy;

	alpha_dst_delta = AST_MAX_HWC_WIDTH << 1;
	last_alpha_dst_delta = alpha_dst_delta - (width << 1);

	srcxor = src;
	dstxor = (u8 *)dst + last_alpha_dst_delta + (AST_MAX_HWC_HEIGHT - height) * alpha_dst_delta;
	per_pixel_copy = width & 1;
	two_pixel_copy = width >> 1;

	क्रम (j = 0; j < height; j++) अणु
		क्रम (i = 0; i < two_pixel_copy; i++) अणु
			srcdata32[0].ul = *((u32 *)srcxor) & 0xf0f0f0f0;
			srcdata32[1].ul = *((u32 *)(srcxor + 4)) & 0xf0f0f0f0;
			data32.b[0] = srcdata32[0].b[1] | (srcdata32[0].b[0] >> 4);
			data32.b[1] = srcdata32[0].b[3] | (srcdata32[0].b[2] >> 4);
			data32.b[2] = srcdata32[1].b[1] | (srcdata32[1].b[0] >> 4);
			data32.b[3] = srcdata32[1].b[3] | (srcdata32[1].b[2] >> 4);

			ग_लिखोl(data32.ul, dstxor);
			csum += data32.ul;

			dstxor += 4;
			srcxor += 8;

		पूर्ण

		क्रम (i = 0; i < per_pixel_copy; i++) अणु
			srcdata32[0].ul = *((u32 *)srcxor) & 0xf0f0f0f0;
			data16.b[0] = srcdata32[0].b[1] | (srcdata32[0].b[0] >> 4);
			data16.b[1] = srcdata32[0].b[3] | (srcdata32[0].b[2] >> 4);
			ग_लिखोw(data16.us, dstxor);
			csum += (u32)data16.us;

			dstxor += 2;
			srcxor += 4;
		पूर्ण
		dstxor += last_alpha_dst_delta;
	पूर्ण

	/* ग_लिखो checksum + signature */
	dst += AST_HWC_SIZE;
	ग_लिखोl(csum, dst);
	ग_लिखोl(width, dst + AST_HWC_SIGNATURE_SizeX);
	ग_लिखोl(height, dst + AST_HWC_SIGNATURE_SizeY);
	ग_लिखोl(0, dst + AST_HWC_SIGNATURE_HOTSPOTX);
	ग_लिखोl(0, dst + AST_HWC_SIGNATURE_HOTSPOTY);
पूर्ण

अटल व्योम ast_set_cursor_base(काष्ठा ast_निजी *ast, u64 address)
अणु
	u8 addr0 = (address >> 3) & 0xff;
	u8 addr1 = (address >> 11) & 0xff;
	u8 addr2 = (address >> 19) & 0xff;

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc8, addr0);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc9, addr1);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xca, addr2);
पूर्ण

अटल व्योम ast_set_cursor_location(काष्ठा ast_निजी *ast, u16 x, u16 y,
				    u8 x_offset, u8 y_offset)
अणु
	u8 x0 = (x & 0x00ff);
	u8 x1 = (x & 0x0f00) >> 8;
	u8 y0 = (y & 0x00ff);
	u8 y1 = (y & 0x0700) >> 8;

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc2, x_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc3, y_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc4, x0);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc5, x1);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc6, y0);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc7, y1);
पूर्ण

अटल व्योम ast_set_cursor_enabled(काष्ठा ast_निजी *ast, bool enabled)
अणु
	अटल स्थिर u8 mask = (u8)~(AST_IO_VGACRCB_HWC_16BPP |
				     AST_IO_VGACRCB_HWC_ENABLED);

	u8 vgacrcb = AST_IO_VGACRCB_HWC_16BPP;

	अगर (enabled)
		vgacrcb |= AST_IO_VGACRCB_HWC_ENABLED;

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xcb, mask, vgacrcb);
पूर्ण

अटल स्थिर uपूर्णांक32_t ast_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल पूर्णांक ast_cursor_plane_helper_atomic_check(काष्ठा drm_plane *plane,
						काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	अगर (!new_plane_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_new_crtc_state(state,
						   new_plane_state->crtc);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	अगर (ret)
		वापस ret;

	अगर (!new_plane_state->visible)
		वापस 0;

	अगर (fb->width > AST_MAX_HWC_WIDTH || fb->height > AST_MAX_HWC_HEIGHT)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम
ast_cursor_plane_helper_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ast_cursor_plane *ast_cursor_plane = to_ast_cursor_plane(plane);
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(new_state);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा ast_निजी *ast = to_ast_निजी(plane->dev);
	काष्ठा dma_buf_map dst_map =
		ast_cursor_plane->hwc[ast_cursor_plane->next_hwc_index].map;
	u64 dst_off =
		ast_cursor_plane->hwc[ast_cursor_plane->next_hwc_index].off;
	काष्ठा dma_buf_map src_map = shaकरोw_plane_state->map[0];
	अचिन्हित पूर्णांक offset_x, offset_y;
	u16 x, y;
	u8 x_offset, y_offset;
	u8 __iomem *dst;
	u8 __iomem *sig;
	स्थिर u8 *src;

	src = src_map.vaddr; /* TODO: Use mapping असलtraction properly */
	dst = dst_map.vaddr_iomem; /* TODO: Use mapping असलtraction properly */
	sig = dst + AST_HWC_SIZE; /* TODO: Use mapping असलtraction properly */

	/*
	 * Do data transfer to HW cursor BO. If a new cursor image was installed,
	 * poपूर्णांक the scanout engine to dst_gbo's offset and page-flip the HWC buffers.
	 */

	ast_update_cursor_image(dst, src, fb->width, fb->height);

	अगर (new_state->fb != old_state->fb) अणु
		ast_set_cursor_base(ast, dst_off);

		++ast_cursor_plane->next_hwc_index;
		ast_cursor_plane->next_hwc_index %= ARRAY_SIZE(ast_cursor_plane->hwc);
	पूर्ण

	/*
	 * Update location in HWC signature and रेजिस्टरs.
	 */

	ग_लिखोl(new_state->crtc_x, sig + AST_HWC_SIGNATURE_X);
	ग_लिखोl(new_state->crtc_y, sig + AST_HWC_SIGNATURE_Y);

	offset_x = AST_MAX_HWC_WIDTH - fb->width;
	offset_y = AST_MAX_HWC_HEIGHT - fb->height;

	अगर (new_state->crtc_x < 0) अणु
		x_offset = (-new_state->crtc_x) + offset_x;
		x = 0;
	पूर्ण अन्यथा अणु
		x_offset = offset_x;
		x = new_state->crtc_x;
	पूर्ण
	अगर (new_state->crtc_y < 0) अणु
		y_offset = (-new_state->crtc_y) + offset_y;
		y = 0;
	पूर्ण अन्यथा अणु
		y_offset = offset_y;
		y = new_state->crtc_y;
	पूर्ण

	ast_set_cursor_location(ast, x, y, x_offset, y_offset);

	/* Dummy ग_लिखो to enable HWC and make the HW pick-up the changes. */
	ast_set_cursor_enabled(ast, true);
पूर्ण

अटल व्योम
ast_cursor_plane_helper_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(plane->dev);

	ast_set_cursor_enabled(ast, false);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs ast_cursor_plane_helper_funcs = अणु
	DRM_GEM_SHADOW_PLANE_HELPER_FUNCS,
	.atomic_check = ast_cursor_plane_helper_atomic_check,
	.atomic_update = ast_cursor_plane_helper_atomic_update,
	.atomic_disable = ast_cursor_plane_helper_atomic_disable,
पूर्ण;

अटल व्योम ast_cursor_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा ast_cursor_plane *ast_cursor_plane = to_ast_cursor_plane(plane);
	माप_प्रकार i;
	काष्ठा drm_gem_vram_object *gbo;
	काष्ठा dma_buf_map map;

	क्रम (i = 0; i < ARRAY_SIZE(ast_cursor_plane->hwc); ++i) अणु
		gbo = ast_cursor_plane->hwc[i].gbo;
		map = ast_cursor_plane->hwc[i].map;
		drm_gem_vram_vunmap(gbo, &map);
		drm_gem_vram_unpin(gbo);
		drm_gem_vram_put(gbo);
	पूर्ण

	drm_plane_cleanup(plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs ast_cursor_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = ast_cursor_plane_destroy,
	DRM_GEM_SHADOW_PLANE_FUNCS,
पूर्ण;

अटल पूर्णांक ast_cursor_plane_init(काष्ठा ast_निजी *ast)
अणु
	काष्ठा drm_device *dev = &ast->base;
	काष्ठा ast_cursor_plane *ast_cursor_plane = &ast->cursor_plane;
	काष्ठा drm_plane *cursor_plane = &ast_cursor_plane->base;
	माप_प्रकार size, i;
	काष्ठा drm_gem_vram_object *gbo;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;
	s64 off;

	/*
	 * Allocate backing storage क्रम cursors. The BOs are permanently
	 * pinned to the top end of the VRAM.
	 */

	size = roundup(AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE, PAGE_SIZE);

	क्रम (i = 0; i < ARRAY_SIZE(ast_cursor_plane->hwc); ++i) अणु
		gbo = drm_gem_vram_create(dev, size, 0);
		अगर (IS_ERR(gbo)) अणु
			ret = PTR_ERR(gbo);
			जाओ err_hwc;
		पूर्ण
		ret = drm_gem_vram_pin(gbo, DRM_GEM_VRAM_PL_FLAG_VRAM |
					    DRM_GEM_VRAM_PL_FLAG_TOPDOWN);
		अगर (ret)
			जाओ err_drm_gem_vram_put;
		ret = drm_gem_vram_vmap(gbo, &map);
		अगर (ret)
			जाओ err_drm_gem_vram_unpin;
		off = drm_gem_vram_offset(gbo);
		अगर (off < 0) अणु
			ret = off;
			जाओ err_drm_gem_vram_vunmap;
		पूर्ण
		ast_cursor_plane->hwc[i].gbo = gbo;
		ast_cursor_plane->hwc[i].map = map;
		ast_cursor_plane->hwc[i].off = off;
	पूर्ण

	/*
	 * Create the cursor plane. The plane's destroy callback will release
	 * the backing storages' BO memory.
	 */

	ret = drm_universal_plane_init(dev, cursor_plane, 0x01,
				       &ast_cursor_plane_funcs,
				       ast_cursor_plane_क्रमmats,
				       ARRAY_SIZE(ast_cursor_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (ret) अणु
		drm_err(dev, "drm_universal_plane failed(): %d\n", ret);
		जाओ err_hwc;
	पूर्ण
	drm_plane_helper_add(cursor_plane, &ast_cursor_plane_helper_funcs);

	वापस 0;

err_hwc:
	जबतक (i) अणु
		--i;
		gbo = ast_cursor_plane->hwc[i].gbo;
		map = ast_cursor_plane->hwc[i].map;
err_drm_gem_vram_vunmap:
		drm_gem_vram_vunmap(gbo, &map);
err_drm_gem_vram_unpin:
		drm_gem_vram_unpin(gbo);
err_drm_gem_vram_put:
		drm_gem_vram_put(gbo);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * CRTC
 */

अटल व्योम ast_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(crtc->dev);

	/* TODO: Maybe control display संकेत generation with
	 *       Sync Enable (bit CR17.7).
	 */
	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
		अगर (ast->tx_chip_type == AST_TX_DP501)
			ast_set_dp501_video_output(crtc->dev, 1);
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		अगर (ast->tx_chip_type == AST_TX_DP501)
			ast_set_dp501_video_output(crtc->dev, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ast_crtc_helper_atomic_check(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा ast_crtc_state *ast_state;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
	bool succ;

	अगर (!crtc_state->enable)
		वापस 0; /* no mode checks अगर CRTC is being disabled */

	ast_state = to_ast_crtc_state(crtc_state);

	क्रमmat = ast_state->क्रमmat;
	अगर (drm_WARN_ON_ONCE(dev, !क्रमmat))
		वापस -EINVAL; /* BUG: We didn't set क्रमmat in primary check(). */

	succ = ast_get_vbios_mode_info(क्रमmat, &crtc_state->mode,
				       &crtc_state->adjusted_mode,
				       &ast_state->vbios_mode_info);
	अगर (!succ)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम
ast_crtc_helper_atomic_flush(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा ast_निजी *ast = to_ast_निजी(crtc->dev);
	काष्ठा ast_crtc_state *ast_crtc_state = to_ast_crtc_state(crtc_state);
	काष्ठा ast_crtc_state *old_ast_crtc_state = to_ast_crtc_state(old_crtc_state);

	/*
	 * The gamma LUT has to be reloaded after changing the primary
	 * plane's color क्रमmat.
	 */
	अगर (old_ast_crtc_state->क्रमmat != ast_crtc_state->क्रमmat)
		ast_crtc_load_lut(ast, crtc);
पूर्ण

अटल व्योम
ast_crtc_helper_atomic_enable(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा drm_crtc_state *crtc_state = crtc->state;
	काष्ठा ast_crtc_state *ast_crtc_state = to_ast_crtc_state(crtc_state);
	काष्ठा ast_vbios_mode_info *vbios_mode_info =
		&ast_crtc_state->vbios_mode_info;
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;

	ast_set_vbios_mode_reg(ast, adjusted_mode, vbios_mode_info);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa1, 0x06);
	ast_set_std_reg(ast, adjusted_mode, vbios_mode_info);
	ast_set_crtc_reg(ast, adjusted_mode, vbios_mode_info);
	ast_set_dclk_reg(ast, adjusted_mode, vbios_mode_info);
	ast_set_crtthd_reg(ast);
	ast_set_sync_reg(ast, adjusted_mode, vbios_mode_info);

	ast_crtc_dpms(crtc, DRM_MODE_DPMS_ON);
पूर्ण

अटल व्योम
ast_crtc_helper_atomic_disable(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);

	ast_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);

	/*
	 * HW cursors require the underlying primary plane and CRTC to
	 * display a valid mode and image. This is not the हाल during
	 * full modeset operations. So we temporarily disable any active
	 * plane, including the HW cursor. Each plane's atomic_update()
	 * helper will re-enable it अगर necessary.
	 *
	 * We only करो this during *full* modesets. It करोes not affect
	 * simple pageflips on the planes.
	 */
	drm_atomic_helper_disable_planes_on_crtc(old_crtc_state, false);

	/*
	 * Ensure that no scanout takes place beक्रमe reprogramming mode
	 * and क्रमmat रेजिस्टरs.
	 */
	ast_रुको_क्रम_vretrace(ast);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs ast_crtc_helper_funcs = अणु
	.atomic_check = ast_crtc_helper_atomic_check,
	.atomic_flush = ast_crtc_helper_atomic_flush,
	.atomic_enable = ast_crtc_helper_atomic_enable,
	.atomic_disable = ast_crtc_helper_atomic_disable,
पूर्ण;

अटल व्योम ast_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ast_crtc_state *ast_state =
		kzalloc(माप(*ast_state), GFP_KERNEL);

	अगर (crtc->state)
		crtc->funcs->atomic_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &ast_state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
ast_crtc_atomic_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ast_crtc_state *new_ast_state, *ast_state;
	काष्ठा drm_device *dev = crtc->dev;

	अगर (drm_WARN_ON(dev, !crtc->state))
		वापस शून्य;

	new_ast_state = kदो_स्मृति(माप(*new_ast_state), GFP_KERNEL);
	अगर (!new_ast_state)
		वापस शून्य;
	__drm_atomic_helper_crtc_duplicate_state(crtc, &new_ast_state->base);

	ast_state = to_ast_crtc_state(crtc->state);

	new_ast_state->क्रमmat = ast_state->क्रमmat;
	स_नकल(&new_ast_state->vbios_mode_info, &ast_state->vbios_mode_info,
	       माप(new_ast_state->vbios_mode_info));

	वापस &new_ast_state->base;
पूर्ण

अटल व्योम ast_crtc_atomic_destroy_state(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *state)
अणु
	काष्ठा ast_crtc_state *ast_state = to_ast_crtc_state(state);

	__drm_atomic_helper_crtc_destroy_state(&ast_state->base);
	kमुक्त(ast_state);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs ast_crtc_funcs = अणु
	.reset = ast_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = ast_crtc_atomic_duplicate_state,
	.atomic_destroy_state = ast_crtc_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक ast_crtc_init(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा drm_crtc *crtc = &ast->crtc;
	पूर्णांक ret;

	ret = drm_crtc_init_with_planes(dev, crtc, &ast->primary_plane,
					&ast->cursor_plane.base, &ast_crtc_funcs,
					शून्य);
	अगर (ret)
		वापस ret;

	drm_mode_crtc_set_gamma_size(crtc, 256);
	drm_crtc_helper_add(crtc, &ast_crtc_helper_funcs);

	वापस 0;
पूर्ण

/*
 * Encoder
 */

अटल पूर्णांक ast_encoder_init(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा drm_encoder *encoder = &ast->encoder;
	पूर्णांक ret;

	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_DAC);
	अगर (ret)
		वापस ret;

	encoder->possible_crtcs = 1;

	वापस 0;
पूर्ण

/*
 * Connector
 */

अटल पूर्णांक ast_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा ast_connector *ast_connector = to_ast_connector(connector);
	काष्ठा ast_निजी *ast = to_ast_निजी(connector->dev);
	काष्ठा edid *edid;
	पूर्णांक ret;
	bool flags = false;
	अगर (ast->tx_chip_type == AST_TX_DP501) अणु
		ast->dp501_maxclk = 0xff;
		edid = kदो_स्मृति(128, GFP_KERNEL);
		अगर (!edid)
			वापस -ENOMEM;

		flags = ast_dp501_पढ़ो_edid(connector->dev, (u8 *)edid);
		अगर (flags)
			ast->dp501_maxclk = ast_get_dp501_max_clk(connector->dev);
		अन्यथा
			kमुक्त(edid);
	पूर्ण
	अगर (!flags)
		edid = drm_get_edid(connector, &ast_connector->i2c->adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(&ast_connector->base, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
		वापस ret;
	पूर्ण अन्यथा
		drm_connector_update_edid_property(&ast_connector->base, शून्य);
	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status ast_mode_valid(काष्ठा drm_connector *connector,
			  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(connector->dev);
	पूर्णांक flags = MODE_NOMODE;
	uपूर्णांक32_t jtemp;

	अगर (ast->support_wide_screen) अणु
		अगर ((mode->hdisplay == 1680) && (mode->vdisplay == 1050))
			वापस MODE_OK;
		अगर ((mode->hdisplay == 1280) && (mode->vdisplay == 800))
			वापस MODE_OK;
		अगर ((mode->hdisplay == 1440) && (mode->vdisplay == 900))
			वापस MODE_OK;
		अगर ((mode->hdisplay == 1360) && (mode->vdisplay == 768))
			वापस MODE_OK;
		अगर ((mode->hdisplay == 1600) && (mode->vdisplay == 900))
			वापस MODE_OK;

		अगर ((ast->chip == AST2100) || (ast->chip == AST2200) ||
		    (ast->chip == AST2300) || (ast->chip == AST2400) ||
		    (ast->chip == AST2500)) अणु
			अगर ((mode->hdisplay == 1920) && (mode->vdisplay == 1080))
				वापस MODE_OK;

			अगर ((mode->hdisplay == 1920) && (mode->vdisplay == 1200)) अणु
				jtemp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
				अगर (jtemp & 0x01)
					वापस MODE_NOMODE;
				अन्यथा
					वापस MODE_OK;
			पूर्ण
		पूर्ण
	पूर्ण
	चयन (mode->hdisplay) अणु
	हाल 640:
		अगर (mode->vdisplay == 480) flags = MODE_OK;
		अवरोध;
	हाल 800:
		अगर (mode->vdisplay == 600) flags = MODE_OK;
		अवरोध;
	हाल 1024:
		अगर (mode->vdisplay == 768) flags = MODE_OK;
		अवरोध;
	हाल 1280:
		अगर (mode->vdisplay == 1024) flags = MODE_OK;
		अवरोध;
	हाल 1600:
		अगर (mode->vdisplay == 1200) flags = MODE_OK;
		अवरोध;
	शेष:
		वापस flags;
	पूर्ण

	वापस flags;
पूर्ण

अटल व्योम ast_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा ast_connector *ast_connector = to_ast_connector(connector);
	ast_i2c_destroy(ast_connector->i2c);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs ast_connector_helper_funcs = अणु
	.get_modes = ast_get_modes,
	.mode_valid = ast_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs ast_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = ast_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक ast_connector_init(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा ast_connector *ast_connector = &ast->connector;
	काष्ठा drm_connector *connector = &ast_connector->base;
	काष्ठा drm_encoder *encoder = &ast->encoder;

	ast_connector->i2c = ast_i2c_create(dev);
	अगर (!ast_connector->i2c)
		drm_err(dev, "failed to add ddc bus for connector\n");

	drm_connector_init_with_ddc(dev, connector,
				    &ast_connector_funcs,
				    DRM_MODE_CONNECTOR_VGA,
				    &ast_connector->i2c->adapter);

	drm_connector_helper_add(connector, &ast_connector_helper_funcs);

	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

/*
 * Mode config
 */

अटल स्थिर काष्ठा drm_mode_config_helper_funcs
ast_mode_config_helper_funcs = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs ast_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.mode_valid = drm_vram_helper_mode_valid,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक ast_mode_config_init(काष्ठा ast_निजी *ast)
अणु
	काष्ठा drm_device *dev = &ast->base;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक ret;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	dev->mode_config.funcs = &ast_mode_config_funcs;
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.prefer_shaकरोw = 1;
	dev->mode_config.fb_base = pci_resource_start(pdev, 0);

	अगर (ast->chip == AST2100 ||
	    ast->chip == AST2200 ||
	    ast->chip == AST2300 ||
	    ast->chip == AST2400 ||
	    ast->chip == AST2500) अणु
		dev->mode_config.max_width = 1920;
		dev->mode_config.max_height = 2048;
	पूर्ण अन्यथा अणु
		dev->mode_config.max_width = 1600;
		dev->mode_config.max_height = 1200;
	पूर्ण

	dev->mode_config.helper_निजी = &ast_mode_config_helper_funcs;


	ret = ast_primary_plane_init(ast);
	अगर (ret)
		वापस ret;

	ret = ast_cursor_plane_init(ast);
	अगर (ret)
		वापस ret;

	ast_crtc_init(dev);
	ast_encoder_init(dev);
	ast_connector_init(dev);

	drm_mode_config_reset(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक get_घड़ी(व्योम *i2c_priv)
अणु
	काष्ठा ast_i2c_chan *i2c = i2c_priv;
	काष्ठा ast_निजी *ast = to_ast_निजी(i2c->dev);
	uपूर्णांक32_t val, val2, count, pass;

	count = 0;
	pass = 0;
	val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x10) >> 4) & 0x01;
	करो अणु
		val2 = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x10) >> 4) & 0x01;
		अगर (val == val2) अणु
			pass++;
		पूर्ण अन्यथा अणु
			pass = 0;
			val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x10) >> 4) & 0x01;
		पूर्ण
	पूर्ण जबतक ((pass < 5) && (count++ < 0x10000));

	वापस val & 1 ? 1 : 0;
पूर्ण

अटल पूर्णांक get_data(व्योम *i2c_priv)
अणु
	काष्ठा ast_i2c_chan *i2c = i2c_priv;
	काष्ठा ast_निजी *ast = to_ast_निजी(i2c->dev);
	uपूर्णांक32_t val, val2, count, pass;

	count = 0;
	pass = 0;
	val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
	करो अणु
		val2 = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
		अगर (val == val2) अणु
			pass++;
		पूर्ण अन्यथा अणु
			pass = 0;
			val = (ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x20) >> 5) & 0x01;
		पूर्ण
	पूर्ण जबतक ((pass < 5) && (count++ < 0x10000));

	वापस val & 1 ? 1 : 0;
पूर्ण

अटल व्योम set_घड़ी(व्योम *i2c_priv, पूर्णांक घड़ी)
अणु
	काष्ठा ast_i2c_chan *i2c = i2c_priv;
	काष्ठा ast_निजी *ast = to_ast_निजी(i2c->dev);
	पूर्णांक i;
	u8 ujcrb7, jtemp;

	क्रम (i = 0; i < 0x10000; i++) अणु
		ujcrb7 = ((घड़ी & 0x01) ? 0 : 1);
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0xf4, ujcrb7);
		jtemp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x01);
		अगर (ujcrb7 == jtemp)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_data(व्योम *i2c_priv, पूर्णांक data)
अणु
	काष्ठा ast_i2c_chan *i2c = i2c_priv;
	काष्ठा ast_निजी *ast = to_ast_निजी(i2c->dev);
	पूर्णांक i;
	u8 ujcrb7, jtemp;

	क्रम (i = 0; i < 0x10000; i++) अणु
		ujcrb7 = ((data & 0x01) ? 0 : 1) << 2;
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0xf1, ujcrb7);
		jtemp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x04);
		अगर (ujcrb7 == jtemp)
			अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा ast_i2c_chan *ast_i2c_create(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_i2c_chan *i2c;
	पूर्णांक ret;

	i2c = kzalloc(माप(काष्ठा ast_i2c_chan), GFP_KERNEL);
	अगर (!i2c)
		वापस शून्य;

	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
		 "AST i2c bit bus");
	i2c->adapter.algo_data = &i2c->bit;

	i2c->bit.udelay = 20;
	i2c->bit.समयout = 2;
	i2c->bit.data = i2c;
	i2c->bit.setsda = set_data;
	i2c->bit.setscl = set_घड़ी;
	i2c->bit.माला_लोda = get_data;
	i2c->bit.माला_लोcl = get_घड़ी;
	ret = i2c_bit_add_bus(&i2c->adapter);
	अगर (ret) अणु
		drm_err(dev, "Failed to register bit i2c\n");
		जाओ out_मुक्त;
	पूर्ण

	वापस i2c;
out_मुक्त:
	kमुक्त(i2c);
	वापस शून्य;
पूर्ण

अटल व्योम ast_i2c_destroy(काष्ठा ast_i2c_chan *i2c)
अणु
	अगर (!i2c)
		वापस;
	i2c_del_adapter(&i2c->adapter);
	kमुक्त(i2c);
पूर्ण
