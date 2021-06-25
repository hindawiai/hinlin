<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2010 Texas Instruments Inc
 * Copyright (C) 2007 MontaVista Software, Inc.
 *
 * Andy Lowe (alowe@mvista.com), MontaVista Software
 * - Initial version
 * Murali Karicheri (mkaricheri@gmail.com), Texas Instruments Ltd.
 * - ported to sub device पूर्णांकerface
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>

#समावेश <media/davinci/vpss.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe_osd.h>

#समावेश <linux/पन.स>
#समावेश "vpbe_osd_regs.h"

#घोषणा MODULE_NAME	"davinci-vpbe-osd"

अटल स्थिर काष्ठा platक्रमm_device_id vpbe_osd_devtype[] = अणु
	अणु
		.name = DM644X_VPBE_OSD_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_1,
	पूर्ण, अणु
		.name = DM365_VPBE_OSD_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_2,
	पूर्ण, अणु
		.name = DM355_VPBE_OSD_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_3,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, vpbe_osd_devtype);

/* रेजिस्टर access routines */
अटल अंतरभूत u32 osd_पढ़ो(काष्ठा osd_state *sd, u32 offset)
अणु
	काष्ठा osd_state *osd = sd;

	वापस पढ़ोl(osd->osd_base + offset);
पूर्ण

अटल अंतरभूत u32 osd_ग_लिखो(काष्ठा osd_state *sd, u32 val, u32 offset)
अणु
	काष्ठा osd_state *osd = sd;

	ग_लिखोl(val, osd->osd_base + offset);

	वापस val;
पूर्ण

अटल अंतरभूत u32 osd_set(काष्ठा osd_state *sd, u32 mask, u32 offset)
अणु
	काष्ठा osd_state *osd = sd;

	व्योम __iomem *addr = osd->osd_base + offset;
	u32 val = पढ़ोl(addr) | mask;

	ग_लिखोl(val, addr);

	वापस val;
पूर्ण

अटल अंतरभूत u32 osd_clear(काष्ठा osd_state *sd, u32 mask, u32 offset)
अणु
	काष्ठा osd_state *osd = sd;

	व्योम __iomem *addr = osd->osd_base + offset;
	u32 val = पढ़ोl(addr) & ~mask;

	ग_लिखोl(val, addr);

	वापस val;
पूर्ण

अटल अंतरभूत u32 osd_modअगरy(काष्ठा osd_state *sd, u32 mask, u32 val,
				 u32 offset)
अणु
	काष्ठा osd_state *osd = sd;

	व्योम __iomem *addr = osd->osd_base + offset;
	u32 new_val = (पढ़ोl(addr) & ~mask) | (val & mask);

	ग_लिखोl(new_val, addr);

	वापस new_val;
पूर्ण

/* define some macros क्रम layer and pixfmt classअगरication */
#घोषणा is_osd_win(layer) (((layer) == WIN_OSD0) || ((layer) == WIN_OSD1))
#घोषणा is_vid_win(layer) (((layer) == WIN_VID0) || ((layer) == WIN_VID1))
#घोषणा is_rgb_pixfmt(pixfmt) \
	(((pixfmt) == PIXFMT_RGB565) || ((pixfmt) == PIXFMT_RGB888))
#घोषणा is_yc_pixfmt(pixfmt) \
	(((pixfmt) == PIXFMT_YCBCRI) || ((pixfmt) == PIXFMT_YCRCBI) || \
	((pixfmt) == PIXFMT_NV12))
#घोषणा MAX_WIN_SIZE OSD_VIDWIN0XP_V0X
#घोषणा MAX_LINE_LENGTH (OSD_VIDWIN0OFST_V0LO << 5)

/**
 * _osd_dm6446_vid0_pingpong() - field inversion fix क्रम DM6446
 * @sd: ptr to काष्ठा osd_state
 * @field_inversion: inversion flag
 * @fb_base_phys: frame buffer address
 * @lconfig: ptr to layer config
 *
 * This routine implements a workaround क्रम the field संकेत inversion silicon
 * erratum described in Advisory 1.3.8 क्रम the DM6446.  The fb_base_phys and
 * lconfig parameters apply to the vid0 winकरोw.  This routine should be called
 * whenever the vid0 layer configuration or start address is modअगरied, or when
 * the OSD field inversion setting is modअगरied.
 * Returns: 1 अगर the ping-pong buffers need to be toggled in the vsync isr, or
 *          0 otherwise
 */
अटल पूर्णांक _osd_dm6446_vid0_pingpong(काष्ठा osd_state *sd,
				     पूर्णांक field_inversion,
				     अचिन्हित दीर्घ fb_base_phys,
				     स्थिर काष्ठा osd_layer_config *lconfig)
अणु
	काष्ठा osd_platक्रमm_data *pdata;

	pdata = (काष्ठा osd_platक्रमm_data *)sd->dev->platक्रमm_data;
	अगर (pdata != शून्य && pdata->field_inv_wa_enable) अणु

		अगर (!field_inversion || !lconfig->पूर्णांकerlaced) अणु
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_VIDWIN0ADR);
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_PPVWIN0ADR);
			osd_modअगरy(sd, OSD_MISCCTL_PPSW | OSD_MISCCTL_PPRV, 0,
				   OSD_MISCCTL);
			वापस 0;
		पूर्ण अन्यथा अणु
			अचिन्हित miscctl = OSD_MISCCTL_PPRV;

			osd_ग_लिखो(sd,
				(fb_base_phys & ~0x1F) - lconfig->line_length,
				OSD_VIDWIN0ADR);
			osd_ग_लिखो(sd,
				(fb_base_phys & ~0x1F) + lconfig->line_length,
				OSD_PPVWIN0ADR);
			osd_modअगरy(sd,
				OSD_MISCCTL_PPSW | OSD_MISCCTL_PPRV, miscctl,
				OSD_MISCCTL);

			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _osd_set_field_inversion(काष्ठा osd_state *sd, पूर्णांक enable)
अणु
	अचिन्हित fsinv = 0;

	अगर (enable)
		fsinv = OSD_MODE_FSINV;

	osd_modअगरy(sd, OSD_MODE_FSINV, fsinv, OSD_MODE);
पूर्ण

अटल व्योम _osd_set_blink_attribute(काष्ठा osd_state *sd, पूर्णांक enable,
				     क्रमागत osd_blink_पूर्णांकerval blink)
अणु
	u32 osdatrmd = 0;

	अगर (enable) अणु
		osdatrmd |= OSD_OSDATRMD_BLNK;
		osdatrmd |= blink << OSD_OSDATRMD_BLNKINT_SHIFT;
	पूर्ण
	/* caller must ensure that OSD1 is configured in attribute mode */
	osd_modअगरy(sd, OSD_OSDATRMD_BLNKINT | OSD_OSDATRMD_BLNK, osdatrmd,
		  OSD_OSDATRMD);
पूर्ण

अटल व्योम _osd_set_rom_clut(काष्ठा osd_state *sd,
			      क्रमागत osd_rom_clut rom_clut)
अणु
	अगर (rom_clut == ROM_CLUT0)
		osd_clear(sd, OSD_MISCCTL_RSEL, OSD_MISCCTL);
	अन्यथा
		osd_set(sd, OSD_MISCCTL_RSEL, OSD_MISCCTL);
पूर्ण

अटल व्योम _osd_set_palette_map(काष्ठा osd_state *sd,
				 क्रमागत osd_win_layer osdwin,
				 अचिन्हित अक्षर pixel_value,
				 अचिन्हित अक्षर clut_index,
				 क्रमागत osd_pix_क्रमmat pixfmt)
अणु
	अटल स्थिर पूर्णांक map_2bpp[] = अणु 0, 5, 10, 15 पूर्ण;
	अटल स्थिर पूर्णांक map_1bpp[] = अणु 0, 15 पूर्ण;
	पूर्णांक bmp_offset;
	पूर्णांक bmp_shअगरt;
	पूर्णांक bmp_mask;
	पूर्णांक bmp_reg;

	चयन (pixfmt) अणु
	हाल PIXFMT_1BPP:
		bmp_reg = map_1bpp[pixel_value & 0x1];
		अवरोध;
	हाल PIXFMT_2BPP:
		bmp_reg = map_2bpp[pixel_value & 0x3];
		अवरोध;
	हाल PIXFMT_4BPP:
		bmp_reg = pixel_value & 0xf;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		bmp_offset = OSD_W0BMP01 + (bmp_reg >> 1) * माप(u32);
		अवरोध;
	हाल OSDWIN_OSD1:
		bmp_offset = OSD_W1BMP01 + (bmp_reg >> 1) * माप(u32);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (bmp_reg & 1) अणु
		bmp_shअगरt = 8;
		bmp_mask = 0xff << 8;
	पूर्ण अन्यथा अणु
		bmp_shअगरt = 0;
		bmp_mask = 0xff;
	पूर्ण

	osd_modअगरy(sd, bmp_mask, clut_index << bmp_shअगरt, bmp_offset);
पूर्ण

अटल व्योम _osd_set_rec601_attenuation(काष्ठा osd_state *sd,
					क्रमागत osd_win_layer osdwin, पूर्णांक enable)
अणु
	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		osd_modअगरy(sd, OSD_OSDWIN0MD_ATN0E,
			  enable ? OSD_OSDWIN0MD_ATN0E : 0,
			  OSD_OSDWIN0MD);
		अगर (sd->vpbe_type == VPBE_VERSION_1)
			osd_modअगरy(sd, OSD_OSDWIN0MD_ATN0E,
				  enable ? OSD_OSDWIN0MD_ATN0E : 0,
				  OSD_OSDWIN0MD);
		अन्यथा अगर ((sd->vpbe_type == VPBE_VERSION_3) ||
			   (sd->vpbe_type == VPBE_VERSION_2))
			osd_modअगरy(sd, OSD_EXTMODE_ATNOSD0EN,
				  enable ? OSD_EXTMODE_ATNOSD0EN : 0,
				  OSD_EXTMODE);
		अवरोध;
	हाल OSDWIN_OSD1:
		osd_modअगरy(sd, OSD_OSDWIN1MD_ATN1E,
			  enable ? OSD_OSDWIN1MD_ATN1E : 0,
			  OSD_OSDWIN1MD);
		अगर (sd->vpbe_type == VPBE_VERSION_1)
			osd_modअगरy(sd, OSD_OSDWIN1MD_ATN1E,
				  enable ? OSD_OSDWIN1MD_ATN1E : 0,
				  OSD_OSDWIN1MD);
		अन्यथा अगर ((sd->vpbe_type == VPBE_VERSION_3) ||
			   (sd->vpbe_type == VPBE_VERSION_2))
			osd_modअगरy(sd, OSD_EXTMODE_ATNOSD1EN,
				  enable ? OSD_EXTMODE_ATNOSD1EN : 0,
				  OSD_EXTMODE);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_set_blending_factor(काष्ठा osd_state *sd,
				     क्रमागत osd_win_layer osdwin,
				     क्रमागत osd_blending_factor blend)
अणु
	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		osd_modअगरy(sd, OSD_OSDWIN0MD_BLND0,
			  blend << OSD_OSDWIN0MD_BLND0_SHIFT, OSD_OSDWIN0MD);
		अवरोध;
	हाल OSDWIN_OSD1:
		osd_modअगरy(sd, OSD_OSDWIN1MD_BLND1,
			  blend << OSD_OSDWIN1MD_BLND1_SHIFT, OSD_OSDWIN1MD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_enable_rgb888_pixblend(काष्ठा osd_state *sd,
					क्रमागत osd_win_layer osdwin)
अणु

	osd_modअगरy(sd, OSD_MISCCTL_BLDSEL, 0, OSD_MISCCTL);
	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		osd_modअगरy(sd, OSD_EXTMODE_OSD0BLDCHR,
			  OSD_EXTMODE_OSD0BLDCHR, OSD_EXTMODE);
		अवरोध;
	हाल OSDWIN_OSD1:
		osd_modअगरy(sd, OSD_EXTMODE_OSD1BLDCHR,
			  OSD_EXTMODE_OSD1BLDCHR, OSD_EXTMODE);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_enable_color_key(काष्ठा osd_state *sd,
				  क्रमागत osd_win_layer osdwin,
				  अचिन्हित colorkey,
				  क्रमागत osd_pix_क्रमmat pixfmt)
अणु
	चयन (pixfmt) अणु
	हाल PIXFMT_1BPP:
	हाल PIXFMT_2BPP:
	हाल PIXFMT_4BPP:
	हाल PIXFMT_8BPP:
		अगर (sd->vpbe_type == VPBE_VERSION_3) अणु
			चयन (osdwin) अणु
			हाल OSDWIN_OSD0:
				osd_modअगरy(sd, OSD_TRANSPBMPIDX_BMP0,
					  colorkey <<
					  OSD_TRANSPBMPIDX_BMP0_SHIFT,
					  OSD_TRANSPBMPIDX);
				अवरोध;
			हाल OSDWIN_OSD1:
				osd_modअगरy(sd, OSD_TRANSPBMPIDX_BMP1,
					  colorkey <<
					  OSD_TRANSPBMPIDX_BMP1_SHIFT,
					  OSD_TRANSPBMPIDX);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PIXFMT_RGB565:
		अगर (sd->vpbe_type == VPBE_VERSION_1)
			osd_ग_लिखो(sd, colorkey & OSD_TRANSPVAL_RGBTRANS,
				  OSD_TRANSPVAL);
		अन्यथा अगर (sd->vpbe_type == VPBE_VERSION_3)
			osd_ग_लिखो(sd, colorkey & OSD_TRANSPVALL_RGBL,
				  OSD_TRANSPVALL);
		अवरोध;
	हाल PIXFMT_YCBCRI:
	हाल PIXFMT_YCRCBI:
		अगर (sd->vpbe_type == VPBE_VERSION_3)
			osd_modअगरy(sd, OSD_TRANSPVALU_Y, colorkey,
				   OSD_TRANSPVALU);
		अवरोध;
	हाल PIXFMT_RGB888:
		अगर (sd->vpbe_type == VPBE_VERSION_3) अणु
			osd_ग_लिखो(sd, colorkey & OSD_TRANSPVALL_RGBL,
				  OSD_TRANSPVALL);
			osd_modअगरy(sd, OSD_TRANSPVALU_RGBU, colorkey >> 16,
				  OSD_TRANSPVALU);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		osd_set(sd, OSD_OSDWIN0MD_TE0, OSD_OSDWIN0MD);
		अवरोध;
	हाल OSDWIN_OSD1:
		osd_set(sd, OSD_OSDWIN1MD_TE1, OSD_OSDWIN1MD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_disable_color_key(काष्ठा osd_state *sd,
				   क्रमागत osd_win_layer osdwin)
अणु
	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		osd_clear(sd, OSD_OSDWIN0MD_TE0, OSD_OSDWIN0MD);
		अवरोध;
	हाल OSDWIN_OSD1:
		osd_clear(sd, OSD_OSDWIN1MD_TE1, OSD_OSDWIN1MD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_set_osd_clut(काष्ठा osd_state *sd,
			      क्रमागत osd_win_layer osdwin,
			      क्रमागत osd_clut clut)
अणु
	u32 winmd = 0;

	चयन (osdwin) अणु
	हाल OSDWIN_OSD0:
		अगर (clut == RAM_CLUT)
			winmd |= OSD_OSDWIN0MD_CLUTS0;
		osd_modअगरy(sd, OSD_OSDWIN0MD_CLUTS0, winmd, OSD_OSDWIN0MD);
		अवरोध;
	हाल OSDWIN_OSD1:
		अगर (clut == RAM_CLUT)
			winmd |= OSD_OSDWIN1MD_CLUTS1;
		osd_modअगरy(sd, OSD_OSDWIN1MD_CLUTS1, winmd, OSD_OSDWIN1MD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_set_zoom(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			  क्रमागत osd_zoom_factor h_zoom,
			  क्रमागत osd_zoom_factor v_zoom)
अणु
	u32 winmd = 0;

	चयन (layer) अणु
	हाल WIN_OSD0:
		winmd |= (h_zoom << OSD_OSDWIN0MD_OHZ0_SHIFT);
		winmd |= (v_zoom << OSD_OSDWIN0MD_OVZ0_SHIFT);
		osd_modअगरy(sd, OSD_OSDWIN0MD_OHZ0 | OSD_OSDWIN0MD_OVZ0, winmd,
			  OSD_OSDWIN0MD);
		अवरोध;
	हाल WIN_VID0:
		winmd |= (h_zoom << OSD_VIDWINMD_VHZ0_SHIFT);
		winmd |= (v_zoom << OSD_VIDWINMD_VVZ0_SHIFT);
		osd_modअगरy(sd, OSD_VIDWINMD_VHZ0 | OSD_VIDWINMD_VVZ0, winmd,
			  OSD_VIDWINMD);
		अवरोध;
	हाल WIN_OSD1:
		winmd |= (h_zoom << OSD_OSDWIN1MD_OHZ1_SHIFT);
		winmd |= (v_zoom << OSD_OSDWIN1MD_OVZ1_SHIFT);
		osd_modअगरy(sd, OSD_OSDWIN1MD_OHZ1 | OSD_OSDWIN1MD_OVZ1, winmd,
			  OSD_OSDWIN1MD);
		अवरोध;
	हाल WIN_VID1:
		winmd |= (h_zoom << OSD_VIDWINMD_VHZ1_SHIFT);
		winmd |= (v_zoom << OSD_VIDWINMD_VVZ1_SHIFT);
		osd_modअगरy(sd, OSD_VIDWINMD_VHZ1 | OSD_VIDWINMD_VVZ1, winmd,
			  OSD_VIDWINMD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _osd_disable_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	चयन (layer) अणु
	हाल WIN_OSD0:
		osd_clear(sd, OSD_OSDWIN0MD_OACT0, OSD_OSDWIN0MD);
		अवरोध;
	हाल WIN_VID0:
		osd_clear(sd, OSD_VIDWINMD_ACT0, OSD_VIDWINMD);
		अवरोध;
	हाल WIN_OSD1:
		/* disable attribute mode as well as disabling the winकरोw */
		osd_clear(sd, OSD_OSDWIN1MD_OASW | OSD_OSDWIN1MD_OACT1,
			  OSD_OSDWIN1MD);
		अवरोध;
	हाल WIN_VID1:
		osd_clear(sd, OSD_VIDWINMD_ACT1, OSD_VIDWINMD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम osd_disable_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	अगर (!win->is_enabled) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस;
	पूर्ण
	win->is_enabled = 0;

	_osd_disable_layer(sd, layer);

	spin_unlock_irqrestore(&osd->lock, flags);
पूर्ण

अटल व्योम _osd_enable_attribute_mode(काष्ठा osd_state *sd)
अणु
	/* enable attribute mode क्रम OSD1 */
	osd_set(sd, OSD_OSDWIN1MD_OASW, OSD_OSDWIN1MD);
पूर्ण

अटल व्योम _osd_enable_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	चयन (layer) अणु
	हाल WIN_OSD0:
		osd_set(sd, OSD_OSDWIN0MD_OACT0, OSD_OSDWIN0MD);
		अवरोध;
	हाल WIN_VID0:
		osd_set(sd, OSD_VIDWINMD_ACT0, OSD_VIDWINMD);
		अवरोध;
	हाल WIN_OSD1:
		/* enable OSD1 and disable attribute mode */
		osd_modअगरy(sd, OSD_OSDWIN1MD_OASW | OSD_OSDWIN1MD_OACT1,
			  OSD_OSDWIN1MD_OACT1, OSD_OSDWIN1MD);
		अवरोध;
	हाल WIN_VID1:
		osd_set(sd, OSD_VIDWINMD_ACT1, OSD_VIDWINMD);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक osd_enable_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			    पूर्णांक otherwin)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	काष्ठा osd_layer_config *cfg = &win->lconfig;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	/*
	 * use otherwin flag to know this is the other vid winकरोw
	 * in YUV420 mode, अगर is, skip this check
	 */
	अगर (!otherwin && (!win->is_allocated ||
			!win->fb_base_phys ||
			!cfg->line_length ||
			!cfg->xsize ||
			!cfg->ysize)) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस -1;
	पूर्ण

	अगर (win->is_enabled) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस 0;
	पूर्ण
	win->is_enabled = 1;

	अगर (cfg->pixfmt != PIXFMT_OSD_ATTR)
		_osd_enable_layer(sd, layer);
	अन्यथा अणु
		_osd_enable_attribute_mode(sd);
		_osd_set_blink_attribute(sd, osd->is_blinking, osd->blink);
	पूर्ण

	spin_unlock_irqrestore(&osd->lock, flags);

	वापस 0;
पूर्ण

#घोषणा OSD_SRC_ADDR_HIGH4	0x7800000
#घोषणा OSD_SRC_ADDR_HIGH7	0x7F0000
#घोषणा OSD_SRCADD_OFSET_SFT	23
#घोषणा OSD_SRCADD_ADD_SFT	16
#घोषणा OSD_WINADL_MASK		0xFFFF
#घोषणा OSD_WINOFST_MASK	0x1000
#घोषणा VPBE_REG_BASE		0x80000000

अटल व्योम _osd_start_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			     अचिन्हित दीर्घ fb_base_phys,
			     अचिन्हित दीर्घ cbcr_ofst)
अणु

	अगर (sd->vpbe_type == VPBE_VERSION_1) अणु
		चयन (layer) अणु
		हाल WIN_OSD0:
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_OSDWIN0ADR);
			अवरोध;
		हाल WIN_VID0:
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_VIDWIN0ADR);
			अवरोध;
		हाल WIN_OSD1:
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_OSDWIN1ADR);
			अवरोध;
		हाल WIN_VID1:
			osd_ग_लिखो(sd, fb_base_phys & ~0x1F, OSD_VIDWIN1ADR);
			अवरोध;
	      पूर्ण
	पूर्ण अन्यथा अगर (sd->vpbe_type == VPBE_VERSION_3) अणु
		अचिन्हित दीर्घ fb_offset_32 =
		    (fb_base_phys - VPBE_REG_BASE) >> 5;

		चयन (layer) अणु
		हाल WIN_OSD0:
			osd_modअगरy(sd, OSD_OSDWINADH_O0AH,
				  fb_offset_32 >> (OSD_SRCADD_ADD_SFT -
						   OSD_OSDWINADH_O0AH_SHIFT),
				  OSD_OSDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_OSDWIN0ADL_O0AL,
				  OSD_OSDWIN0ADL);
			अवरोध;
		हाल WIN_VID0:
			osd_modअगरy(sd, OSD_VIDWINADH_V0AH,
				  fb_offset_32 >> (OSD_SRCADD_ADD_SFT -
						   OSD_VIDWINADH_V0AH_SHIFT),
				  OSD_VIDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_VIDWIN0ADL_V0AL,
				  OSD_VIDWIN0ADL);
			अवरोध;
		हाल WIN_OSD1:
			osd_modअगरy(sd, OSD_OSDWINADH_O1AH,
				  fb_offset_32 >> (OSD_SRCADD_ADD_SFT -
						   OSD_OSDWINADH_O1AH_SHIFT),
				  OSD_OSDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_OSDWIN1ADL_O1AL,
				  OSD_OSDWIN1ADL);
			अवरोध;
		हाल WIN_VID1:
			osd_modअगरy(sd, OSD_VIDWINADH_V1AH,
				  fb_offset_32 >> (OSD_SRCADD_ADD_SFT -
						   OSD_VIDWINADH_V1AH_SHIFT),
				  OSD_VIDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_VIDWIN1ADL_V1AL,
				  OSD_VIDWIN1ADL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (sd->vpbe_type == VPBE_VERSION_2) अणु
		काष्ठा osd_winकरोw_state *win = &sd->win[layer];
		अचिन्हित दीर्घ fb_offset_32, cbcr_offset_32;

		fb_offset_32 = fb_base_phys - VPBE_REG_BASE;
		अगर (cbcr_ofst)
			cbcr_offset_32 = cbcr_ofst;
		अन्यथा
			cbcr_offset_32 = win->lconfig.line_length *
					 win->lconfig.ysize;
		cbcr_offset_32 += fb_offset_32;
		fb_offset_32 = fb_offset_32 >> 5;
		cbcr_offset_32 = cbcr_offset_32 >> 5;
		/*
		 * DM365: start address is 27-bit दीर्घ address b26 - b23 are
		 * in offset रेजिस्टर b12 - b9, and * bit 26 has to be '1'
		 */
		अगर (win->lconfig.pixfmt == PIXFMT_NV12) अणु
			चयन (layer) अणु
			हाल WIN_VID0:
			हाल WIN_VID1:
				/* Y is in VID0 */
				osd_modअगरy(sd, OSD_VIDWIN0OFST_V0AH,
					 ((fb_offset_32 & OSD_SRC_ADDR_HIGH4) >>
					 (OSD_SRCADD_OFSET_SFT -
					 OSD_WINOFST_AH_SHIFT)) |
					 OSD_WINOFST_MASK, OSD_VIDWIN0OFST);
				osd_modअगरy(sd, OSD_VIDWINADH_V0AH,
					  (fb_offset_32 & OSD_SRC_ADDR_HIGH7) >>
					  (OSD_SRCADD_ADD_SFT -
					  OSD_VIDWINADH_V0AH_SHIFT),
					   OSD_VIDWINADH);
				osd_ग_लिखो(sd, fb_offset_32 & OSD_WINADL_MASK,
					  OSD_VIDWIN0ADL);
				/* CbCr is in VID1 */
				osd_modअगरy(sd, OSD_VIDWIN1OFST_V1AH,
					 ((cbcr_offset_32 &
					 OSD_SRC_ADDR_HIGH4) >>
					 (OSD_SRCADD_OFSET_SFT -
					 OSD_WINOFST_AH_SHIFT)) |
					 OSD_WINOFST_MASK, OSD_VIDWIN1OFST);
				osd_modअगरy(sd, OSD_VIDWINADH_V1AH,
					  (cbcr_offset_32 &
					  OSD_SRC_ADDR_HIGH7) >>
					  (OSD_SRCADD_ADD_SFT -
					  OSD_VIDWINADH_V1AH_SHIFT),
					  OSD_VIDWINADH);
				osd_ग_लिखो(sd, cbcr_offset_32 & OSD_WINADL_MASK,
					  OSD_VIDWIN1ADL);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		चयन (layer) अणु
		हाल WIN_OSD0:
			osd_modअगरy(sd, OSD_OSDWIN0OFST_O0AH,
				 ((fb_offset_32 & OSD_SRC_ADDR_HIGH4) >>
				 (OSD_SRCADD_OFSET_SFT -
				 OSD_WINOFST_AH_SHIFT)) | OSD_WINOFST_MASK,
				  OSD_OSDWIN0OFST);
			osd_modअगरy(sd, OSD_OSDWINADH_O0AH,
				 (fb_offset_32 & OSD_SRC_ADDR_HIGH7) >>
				 (OSD_SRCADD_ADD_SFT -
				 OSD_OSDWINADH_O0AH_SHIFT), OSD_OSDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_WINADL_MASK,
					OSD_OSDWIN0ADL);
			अवरोध;
		हाल WIN_VID0:
			अगर (win->lconfig.pixfmt != PIXFMT_NV12) अणु
				osd_modअगरy(sd, OSD_VIDWIN0OFST_V0AH,
					 ((fb_offset_32 & OSD_SRC_ADDR_HIGH4) >>
					 (OSD_SRCADD_OFSET_SFT -
					 OSD_WINOFST_AH_SHIFT)) |
					 OSD_WINOFST_MASK, OSD_VIDWIN0OFST);
				osd_modअगरy(sd, OSD_VIDWINADH_V0AH,
					  (fb_offset_32 & OSD_SRC_ADDR_HIGH7) >>
					  (OSD_SRCADD_ADD_SFT -
					  OSD_VIDWINADH_V0AH_SHIFT),
					  OSD_VIDWINADH);
				osd_ग_लिखो(sd, fb_offset_32 & OSD_WINADL_MASK,
					  OSD_VIDWIN0ADL);
			पूर्ण
			अवरोध;
		हाल WIN_OSD1:
			osd_modअगरy(sd, OSD_OSDWIN1OFST_O1AH,
				 ((fb_offset_32 & OSD_SRC_ADDR_HIGH4) >>
				 (OSD_SRCADD_OFSET_SFT -
				 OSD_WINOFST_AH_SHIFT)) | OSD_WINOFST_MASK,
				  OSD_OSDWIN1OFST);
			osd_modअगरy(sd, OSD_OSDWINADH_O1AH,
				  (fb_offset_32 & OSD_SRC_ADDR_HIGH7) >>
				  (OSD_SRCADD_ADD_SFT -
				  OSD_OSDWINADH_O1AH_SHIFT),
				  OSD_OSDWINADH);
			osd_ग_लिखो(sd, fb_offset_32 & OSD_WINADL_MASK,
					OSD_OSDWIN1ADL);
			अवरोध;
		हाल WIN_VID1:
			अगर (win->lconfig.pixfmt != PIXFMT_NV12) अणु
				osd_modअगरy(sd, OSD_VIDWIN1OFST_V1AH,
					 ((fb_offset_32 & OSD_SRC_ADDR_HIGH4) >>
					 (OSD_SRCADD_OFSET_SFT -
					 OSD_WINOFST_AH_SHIFT)) |
					 OSD_WINOFST_MASK, OSD_VIDWIN1OFST);
				osd_modअगरy(sd, OSD_VIDWINADH_V1AH,
					  (fb_offset_32 & OSD_SRC_ADDR_HIGH7) >>
					  (OSD_SRCADD_ADD_SFT -
					  OSD_VIDWINADH_V1AH_SHIFT),
					  OSD_VIDWINADH);
				osd_ग_लिखो(sd, fb_offset_32 & OSD_WINADL_MASK,
					  OSD_VIDWIN1ADL);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम osd_start_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			    अचिन्हित दीर्घ fb_base_phys,
			    अचिन्हित दीर्घ cbcr_ofst)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	काष्ठा osd_layer_config *cfg = &win->lconfig;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	win->fb_base_phys = fb_base_phys & ~0x1F;
	_osd_start_layer(sd, layer, fb_base_phys, cbcr_ofst);

	अगर (layer == WIN_VID0) अणु
		osd->pingpong =
		    _osd_dm6446_vid0_pingpong(sd, osd->field_inversion,
						       win->fb_base_phys,
						       cfg);
	पूर्ण

	spin_unlock_irqrestore(&osd->lock, flags);
पूर्ण

अटल व्योम osd_get_layer_config(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				 काष्ठा osd_layer_config *lconfig)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	*lconfig = win->lconfig;

	spin_unlock_irqrestore(&osd->lock, flags);
पूर्ण

/**
 * try_layer_config() - Try a specअगरic configuration क्रम the layer
 * @sd: ptr to काष्ठा osd_state
 * @layer: layer to configure
 * @lconfig: layer configuration to try
 *
 * If the requested lconfig is completely rejected and the value of lconfig on
 * निकास is the current lconfig, then try_layer_config() वापसs 1.  Otherwise,
 * try_layer_config() वापसs 0.  A वापस value of 0 करोes not necessarily mean
 * that the value of lconfig on निकास is identical to the value of lconfig on
 * entry, but merely that it represents a change from the current lconfig.
 */
अटल पूर्णांक try_layer_config(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			    काष्ठा osd_layer_config *lconfig)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	पूर्णांक bad_config = 0;

	/* verअगरy that the pixel क्रमmat is compatible with the layer */
	चयन (lconfig->pixfmt) अणु
	हाल PIXFMT_1BPP:
	हाल PIXFMT_2BPP:
	हाल PIXFMT_4BPP:
	हाल PIXFMT_8BPP:
	हाल PIXFMT_RGB565:
		अगर (osd->vpbe_type == VPBE_VERSION_1)
			bad_config = !is_vid_win(layer);
		अवरोध;
	हाल PIXFMT_YCBCRI:
	हाल PIXFMT_YCRCBI:
		bad_config = !is_vid_win(layer);
		अवरोध;
	हाल PIXFMT_RGB888:
		अगर (osd->vpbe_type == VPBE_VERSION_1)
			bad_config = !is_vid_win(layer);
		अन्यथा अगर ((osd->vpbe_type == VPBE_VERSION_3) ||
			 (osd->vpbe_type == VPBE_VERSION_2))
			bad_config = !is_osd_win(layer);
		अवरोध;
	हाल PIXFMT_NV12:
		अगर (osd->vpbe_type != VPBE_VERSION_2)
			bad_config = 1;
		अन्यथा
			bad_config = is_osd_win(layer);
		अवरोध;
	हाल PIXFMT_OSD_ATTR:
		bad_config = (layer != WIN_OSD1);
		अवरोध;
	शेष:
		bad_config = 1;
		अवरोध;
	पूर्ण
	अगर (bad_config) अणु
		/*
		 * The requested pixel क्रमmat is incompatible with the layer,
		 * so keep the current layer configuration.
		 */
		*lconfig = win->lconfig;
		वापस bad_config;
	पूर्ण

	/* DM6446: */
	/* only one OSD winकरोw at a समय can use RGB pixel क्रमmats */
	अगर ((osd->vpbe_type == VPBE_VERSION_1) &&
	    is_osd_win(layer) && is_rgb_pixfmt(lconfig->pixfmt)) अणु
		क्रमागत osd_pix_क्रमmat pixfmt;

		अगर (layer == WIN_OSD0)
			pixfmt = osd->win[WIN_OSD1].lconfig.pixfmt;
		अन्यथा
			pixfmt = osd->win[WIN_OSD0].lconfig.pixfmt;

		अगर (is_rgb_pixfmt(pixfmt)) अणु
			/*
			 * The other OSD winकरोw is alपढ़ोy configured क्रम an
			 * RGB, so keep the current layer configuration.
			 */
			*lconfig = win->lconfig;
			वापस 1;
		पूर्ण
	पूर्ण

	/* DM6446: only one video winकरोw at a समय can use RGB888 */
	अगर ((osd->vpbe_type == VPBE_VERSION_1) && is_vid_win(layer) &&
		lconfig->pixfmt == PIXFMT_RGB888) अणु
		क्रमागत osd_pix_क्रमmat pixfmt;

		अगर (layer == WIN_VID0)
			pixfmt = osd->win[WIN_VID1].lconfig.pixfmt;
		अन्यथा
			pixfmt = osd->win[WIN_VID0].lconfig.pixfmt;

		अगर (pixfmt == PIXFMT_RGB888) अणु
			/*
			 * The other video winकरोw is alपढ़ोy configured क्रम
			 * RGB888, so keep the current layer configuration.
			 */
			*lconfig = win->lconfig;
			वापस 1;
		पूर्ण
	पूर्ण

	/* winकरोw dimensions must be non-zero */
	अगर (!lconfig->line_length || !lconfig->xsize || !lconfig->ysize) अणु
		*lconfig = win->lconfig;
		वापस 1;
	पूर्ण

	/* round line_length up to a multiple of 32 */
	lconfig->line_length = ((lconfig->line_length + 31) / 32) * 32;
	lconfig->line_length =
	    min(lconfig->line_length, (अचिन्हित)MAX_LINE_LENGTH);
	lconfig->xsize = min(lconfig->xsize, (अचिन्हित)MAX_WIN_SIZE);
	lconfig->ysize = min(lconfig->ysize, (अचिन्हित)MAX_WIN_SIZE);
	lconfig->xpos = min(lconfig->xpos, (अचिन्हित)MAX_WIN_SIZE);
	lconfig->ypos = min(lconfig->ypos, (अचिन्हित)MAX_WIN_SIZE);
	lconfig->पूर्णांकerlaced = (lconfig->पूर्णांकerlaced != 0);
	अगर (lconfig->पूर्णांकerlaced) अणु
		/* ysize and ypos must be even क्रम पूर्णांकerlaced displays */
		lconfig->ysize &= ~1;
		lconfig->ypos &= ~1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _osd_disable_vid_rgb888(काष्ठा osd_state *sd)
अणु
	/*
	 * The DM6446 supports RGB888 pixel क्रमmat in a single video winकरोw.
	 * This routine disables RGB888 pixel क्रमmat क्रम both video winकरोws.
	 * The caller must ensure that neither video winकरोw is currently
	 * configured क्रम RGB888 pixel क्रमmat.
	 */
	अगर (sd->vpbe_type == VPBE_VERSION_1)
		osd_clear(sd, OSD_MISCCTL_RGBEN, OSD_MISCCTL);
पूर्ण

अटल व्योम _osd_enable_vid_rgb888(काष्ठा osd_state *sd,
				   क्रमागत osd_layer layer)
अणु
	/*
	 * The DM6446 supports RGB888 pixel क्रमmat in a single video winकरोw.
	 * This routine enables RGB888 pixel क्रमmat क्रम the specअगरied video
	 * winकरोw.  The caller must ensure that the other video winकरोw is not
	 * currently configured क्रम RGB888 pixel क्रमmat, as this routine will
	 * disable RGB888 pixel क्रमmat क्रम the other winकरोw.
	 */
	अगर (sd->vpbe_type == VPBE_VERSION_1) अणु
		अगर (layer == WIN_VID0)
			osd_modअगरy(sd, OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL_RGBEN, OSD_MISCCTL);
		अन्यथा अगर (layer == WIN_VID1)
			osd_modअगरy(sd, OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL);
	पूर्ण
पूर्ण

अटल व्योम _osd_set_cbcr_order(काष्ठा osd_state *sd,
				क्रमागत osd_pix_क्रमmat pixfmt)
अणु
	/*
	 * The caller must ensure that all winकरोws using YC pixfmt use the same
	 * Cb/Cr order.
	 */
	अगर (pixfmt == PIXFMT_YCBCRI)
		osd_clear(sd, OSD_MODE_CS, OSD_MODE);
	अन्यथा अगर (pixfmt == PIXFMT_YCRCBI)
		osd_set(sd, OSD_MODE_CS, OSD_MODE);
पूर्ण

अटल व्योम _osd_set_layer_config(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				  स्थिर काष्ठा osd_layer_config *lconfig)
अणु
	u32 winmd = 0, winmd_mask = 0, bmw = 0;

	_osd_set_cbcr_order(sd, lconfig->pixfmt);

	चयन (layer) अणु
	हाल WIN_OSD0:
		अगर (sd->vpbe_type == VPBE_VERSION_1) अणु
			winmd_mask |= OSD_OSDWIN0MD_RGB0E;
			अगर (lconfig->pixfmt == PIXFMT_RGB565)
				winmd |= OSD_OSDWIN0MD_RGB0E;
		पूर्ण अन्यथा अगर ((sd->vpbe_type == VPBE_VERSION_3) ||
		  (sd->vpbe_type == VPBE_VERSION_2)) अणु
			winmd_mask |= OSD_OSDWIN0MD_BMP0MD;
			चयन (lconfig->pixfmt) अणु
			हाल PIXFMT_RGB565:
					winmd |= (1 <<
					OSD_OSDWIN0MD_BMP0MD_SHIFT);
					अवरोध;
			हाल PIXFMT_RGB888:
				winmd |= (2 << OSD_OSDWIN0MD_BMP0MD_SHIFT);
				_osd_enable_rgb888_pixblend(sd, OSDWIN_OSD0);
				अवरोध;
			हाल PIXFMT_YCBCRI:
			हाल PIXFMT_YCRCBI:
				winmd |= (3 << OSD_OSDWIN0MD_BMP0MD_SHIFT);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		winmd_mask |= OSD_OSDWIN0MD_BMW0 | OSD_OSDWIN0MD_OFF0;

		चयन (lconfig->pixfmt) अणु
		हाल PIXFMT_1BPP:
			bmw = 0;
			अवरोध;
		हाल PIXFMT_2BPP:
			bmw = 1;
			अवरोध;
		हाल PIXFMT_4BPP:
			bmw = 2;
			अवरोध;
		हाल PIXFMT_8BPP:
			bmw = 3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		winmd |= (bmw << OSD_OSDWIN0MD_BMW0_SHIFT);

		अगर (lconfig->पूर्णांकerlaced)
			winmd |= OSD_OSDWIN0MD_OFF0;

		osd_modअगरy(sd, winmd_mask, winmd, OSD_OSDWIN0MD);
		osd_ग_लिखो(sd, lconfig->line_length >> 5, OSD_OSDWIN0OFST);
		osd_ग_लिखो(sd, lconfig->xpos, OSD_OSDWIN0XP);
		osd_ग_लिखो(sd, lconfig->xsize, OSD_OSDWIN0XL);
		अगर (lconfig->पूर्णांकerlaced) अणु
			osd_ग_लिखो(sd, lconfig->ypos >> 1, OSD_OSDWIN0YP);
			osd_ग_लिखो(sd, lconfig->ysize >> 1, OSD_OSDWIN0YL);
		पूर्ण अन्यथा अणु
			osd_ग_लिखो(sd, lconfig->ypos, OSD_OSDWIN0YP);
			osd_ग_लिखो(sd, lconfig->ysize, OSD_OSDWIN0YL);
		पूर्ण
		अवरोध;
	हाल WIN_VID0:
		winmd_mask |= OSD_VIDWINMD_VFF0;
		अगर (lconfig->पूर्णांकerlaced)
			winmd |= OSD_VIDWINMD_VFF0;

		osd_modअगरy(sd, winmd_mask, winmd, OSD_VIDWINMD);
		osd_ग_लिखो(sd, lconfig->line_length >> 5, OSD_VIDWIN0OFST);
		osd_ग_लिखो(sd, lconfig->xpos, OSD_VIDWIN0XP);
		osd_ग_लिखो(sd, lconfig->xsize, OSD_VIDWIN0XL);
		/*
		 * For YUV420P क्रमmat the रेजिस्टर contents are
		 * duplicated in both VID रेजिस्टरs
		 */
		अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				(lconfig->pixfmt == PIXFMT_NV12)) अणु
			/* other winकरोw also */
			अगर (lconfig->पूर्णांकerlaced) अणु
				winmd_mask |= OSD_VIDWINMD_VFF1;
				winmd |= OSD_VIDWINMD_VFF1;
				osd_modअगरy(sd, winmd_mask, winmd,
					  OSD_VIDWINMD);
			पूर्ण

			osd_modअगरy(sd, OSD_MISCCTL_S420D,
				    OSD_MISCCTL_S420D, OSD_MISCCTL);
			osd_ग_लिखो(sd, lconfig->line_length >> 5,
				  OSD_VIDWIN1OFST);
			osd_ग_लिखो(sd, lconfig->xpos, OSD_VIDWIN1XP);
			osd_ग_लिखो(sd, lconfig->xsize, OSD_VIDWIN1XL);
			/*
			  * अगर NV21 pixfmt and line length not 32B
			  * aligned (e.g. NTSC), Need to set winकरोw
			  * X pixel size to be 32B aligned as well
			  */
			अगर (lconfig->xsize % 32) अणु
				osd_ग_लिखो(sd,
					  ((lconfig->xsize + 31) & ~31),
					  OSD_VIDWIN1XL);
				osd_ग_लिखो(sd,
					  ((lconfig->xsize + 31) & ~31),
					  OSD_VIDWIN0XL);
			पूर्ण
		पूर्ण अन्यथा अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				(lconfig->pixfmt != PIXFMT_NV12)) अणु
			osd_modअगरy(sd, OSD_MISCCTL_S420D, ~OSD_MISCCTL_S420D,
						OSD_MISCCTL);
		पूर्ण

		अगर (lconfig->पूर्णांकerlaced) अणु
			osd_ग_लिखो(sd, lconfig->ypos >> 1, OSD_VIDWIN0YP);
			osd_ग_लिखो(sd, lconfig->ysize >> 1, OSD_VIDWIN0YL);
			अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				lconfig->pixfmt == PIXFMT_NV12) अणु
				osd_ग_लिखो(sd, lconfig->ypos >> 1,
					  OSD_VIDWIN1YP);
				osd_ग_लिखो(sd, lconfig->ysize >> 1,
					  OSD_VIDWIN1YL);
			पूर्ण
		पूर्ण अन्यथा अणु
			osd_ग_लिखो(sd, lconfig->ypos, OSD_VIDWIN0YP);
			osd_ग_लिखो(sd, lconfig->ysize, OSD_VIDWIN0YL);
			अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				lconfig->pixfmt == PIXFMT_NV12) अणु
				osd_ग_लिखो(sd, lconfig->ypos, OSD_VIDWIN1YP);
				osd_ग_लिखो(sd, lconfig->ysize, OSD_VIDWIN1YL);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WIN_OSD1:
		/*
		 * The caller must ensure that OSD1 is disabled prior to
		 * चयनing from a normal mode to attribute mode or from
		 * attribute mode to a normal mode.
		 */
		अगर (lconfig->pixfmt == PIXFMT_OSD_ATTR) अणु
			अगर (sd->vpbe_type == VPBE_VERSION_1) अणु
				winmd_mask |= OSD_OSDWIN1MD_ATN1E |
				OSD_OSDWIN1MD_RGB1E | OSD_OSDWIN1MD_CLUTS1 |
				OSD_OSDWIN1MD_BLND1 | OSD_OSDWIN1MD_TE1;
			पूर्ण अन्यथा अणु
				winmd_mask |= OSD_OSDWIN1MD_BMP1MD |
				OSD_OSDWIN1MD_CLUTS1 | OSD_OSDWIN1MD_BLND1 |
				OSD_OSDWIN1MD_TE1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sd->vpbe_type == VPBE_VERSION_1) अणु
				winmd_mask |= OSD_OSDWIN1MD_RGB1E;
				अगर (lconfig->pixfmt == PIXFMT_RGB565)
					winmd |= OSD_OSDWIN1MD_RGB1E;
			पूर्ण अन्यथा अगर ((sd->vpbe_type == VPBE_VERSION_3)
				   || (sd->vpbe_type == VPBE_VERSION_2)) अणु
				winmd_mask |= OSD_OSDWIN1MD_BMP1MD;
				चयन (lconfig->pixfmt) अणु
				हाल PIXFMT_RGB565:
					winmd |=
					    (1 << OSD_OSDWIN1MD_BMP1MD_SHIFT);
					अवरोध;
				हाल PIXFMT_RGB888:
					winmd |=
					    (2 << OSD_OSDWIN1MD_BMP1MD_SHIFT);
					_osd_enable_rgb888_pixblend(sd,
							OSDWIN_OSD1);
					अवरोध;
				हाल PIXFMT_YCBCRI:
				हाल PIXFMT_YCRCBI:
					winmd |=
					    (3 << OSD_OSDWIN1MD_BMP1MD_SHIFT);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण

			winmd_mask |= OSD_OSDWIN1MD_BMW1;
			चयन (lconfig->pixfmt) अणु
			हाल PIXFMT_1BPP:
				bmw = 0;
				अवरोध;
			हाल PIXFMT_2BPP:
				bmw = 1;
				अवरोध;
			हाल PIXFMT_4BPP:
				bmw = 2;
				अवरोध;
			हाल PIXFMT_8BPP:
				bmw = 3;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			winmd |= (bmw << OSD_OSDWIN1MD_BMW1_SHIFT);
		पूर्ण

		winmd_mask |= OSD_OSDWIN1MD_OFF1;
		अगर (lconfig->पूर्णांकerlaced)
			winmd |= OSD_OSDWIN1MD_OFF1;

		osd_modअगरy(sd, winmd_mask, winmd, OSD_OSDWIN1MD);
		osd_ग_लिखो(sd, lconfig->line_length >> 5, OSD_OSDWIN1OFST);
		osd_ग_लिखो(sd, lconfig->xpos, OSD_OSDWIN1XP);
		osd_ग_लिखो(sd, lconfig->xsize, OSD_OSDWIN1XL);
		अगर (lconfig->पूर्णांकerlaced) अणु
			osd_ग_लिखो(sd, lconfig->ypos >> 1, OSD_OSDWIN1YP);
			osd_ग_लिखो(sd, lconfig->ysize >> 1, OSD_OSDWIN1YL);
		पूर्ण अन्यथा अणु
			osd_ग_लिखो(sd, lconfig->ypos, OSD_OSDWIN1YP);
			osd_ग_लिखो(sd, lconfig->ysize, OSD_OSDWIN1YL);
		पूर्ण
		अवरोध;
	हाल WIN_VID1:
		winmd_mask |= OSD_VIDWINMD_VFF1;
		अगर (lconfig->पूर्णांकerlaced)
			winmd |= OSD_VIDWINMD_VFF1;

		osd_modअगरy(sd, winmd_mask, winmd, OSD_VIDWINMD);
		osd_ग_लिखो(sd, lconfig->line_length >> 5, OSD_VIDWIN1OFST);
		osd_ग_लिखो(sd, lconfig->xpos, OSD_VIDWIN1XP);
		osd_ग_लिखो(sd, lconfig->xsize, OSD_VIDWIN1XL);
		/*
		 * For YUV420P क्रमmat the रेजिस्टर contents are
		 * duplicated in both VID रेजिस्टरs
		 */
		अगर (sd->vpbe_type == VPBE_VERSION_2) अणु
			अगर (lconfig->pixfmt == PIXFMT_NV12) अणु
				/* other winकरोw also */
				अगर (lconfig->पूर्णांकerlaced) अणु
					winmd_mask |= OSD_VIDWINMD_VFF0;
					winmd |= OSD_VIDWINMD_VFF0;
					osd_modअगरy(sd, winmd_mask, winmd,
						  OSD_VIDWINMD);
				पूर्ण
				osd_modअगरy(sd, OSD_MISCCTL_S420D,
					   OSD_MISCCTL_S420D, OSD_MISCCTL);
				osd_ग_लिखो(sd, lconfig->line_length >> 5,
					  OSD_VIDWIN0OFST);
				osd_ग_लिखो(sd, lconfig->xpos, OSD_VIDWIN0XP);
				osd_ग_लिखो(sd, lconfig->xsize, OSD_VIDWIN0XL);
			पूर्ण अन्यथा अणु
				osd_modअगरy(sd, OSD_MISCCTL_S420D,
					   ~OSD_MISCCTL_S420D, OSD_MISCCTL);
			पूर्ण
		पूर्ण

		अगर (lconfig->पूर्णांकerlaced) अणु
			osd_ग_लिखो(sd, lconfig->ypos >> 1, OSD_VIDWIN1YP);
			osd_ग_लिखो(sd, lconfig->ysize >> 1, OSD_VIDWIN1YL);
			अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				lconfig->pixfmt == PIXFMT_NV12) अणु
				osd_ग_लिखो(sd, lconfig->ypos >> 1,
					  OSD_VIDWIN0YP);
				osd_ग_लिखो(sd, lconfig->ysize >> 1,
					  OSD_VIDWIN0YL);
			पूर्ण
		पूर्ण अन्यथा अणु
			osd_ग_लिखो(sd, lconfig->ypos, OSD_VIDWIN1YP);
			osd_ग_लिखो(sd, lconfig->ysize, OSD_VIDWIN1YL);
			अगर ((sd->vpbe_type == VPBE_VERSION_2) &&
				lconfig->pixfmt == PIXFMT_NV12) अणु
				osd_ग_लिखो(sd, lconfig->ypos, OSD_VIDWIN0YP);
				osd_ग_लिखो(sd, lconfig->ysize, OSD_VIDWIN0YL);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक osd_set_layer_config(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				काष्ठा osd_layer_config *lconfig)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	काष्ठा osd_layer_config *cfg = &win->lconfig;
	अचिन्हित दीर्घ flags;
	पूर्णांक reject_config;

	spin_lock_irqsave(&osd->lock, flags);

	reject_config = try_layer_config(sd, layer, lconfig);
	अगर (reject_config) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस reject_config;
	पूर्ण

	/* update the current Cb/Cr order */
	अगर (is_yc_pixfmt(lconfig->pixfmt))
		osd->yc_pixfmt = lconfig->pixfmt;

	/*
	 * If we are चयनing OSD1 from normal mode to attribute mode or from
	 * attribute mode to normal mode, then we must disable the winकरोw.
	 */
	अगर (layer == WIN_OSD1) अणु
		अगर (((lconfig->pixfmt == PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt != PIXFMT_OSD_ATTR)) ||
		  ((lconfig->pixfmt != PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt == PIXFMT_OSD_ATTR))) अणु
			win->is_enabled = 0;
			_osd_disable_layer(sd, layer);
		पूर्ण
	पूर्ण

	_osd_set_layer_config(sd, layer, lconfig);

	अगर (layer == WIN_OSD1) अणु
		काष्ठा osd_osdwin_state *osdwin_state =
		    &osd->osdwin[OSDWIN_OSD1];

		अगर ((lconfig->pixfmt != PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt == PIXFMT_OSD_ATTR)) अणु
			/*
			 * We just चयनed OSD1 from attribute mode to normal
			 * mode, so we must initialize the CLUT select, the
			 * blend factor, transparency colorkey enable, and
			 * attenuation enable (DM6446 only) bits in the
			 * OSDWIN1MD रेजिस्टर.
			 */
			_osd_set_osd_clut(sd, OSDWIN_OSD1,
						   osdwin_state->clut);
			_osd_set_blending_factor(sd, OSDWIN_OSD1,
							  osdwin_state->blend);
			अगर (osdwin_state->colorkey_blending) अणु
				_osd_enable_color_key(sd, OSDWIN_OSD1,
							       osdwin_state->
							       colorkey,
							       lconfig->pixfmt);
			पूर्ण अन्यथा
				_osd_disable_color_key(sd, OSDWIN_OSD1);
			_osd_set_rec601_attenuation(sd, OSDWIN_OSD1,
						    osdwin_state->
						    rec601_attenuation);
		पूर्ण अन्यथा अगर ((lconfig->pixfmt == PIXFMT_OSD_ATTR) &&
		  (cfg->pixfmt != PIXFMT_OSD_ATTR)) अणु
			/*
			 * We just चयनed OSD1 from normal mode to attribute
			 * mode, so we must initialize the blink enable and
			 * blink पूर्णांकerval bits in the OSDATRMD रेजिस्टर.
			 */
			_osd_set_blink_attribute(sd, osd->is_blinking,
							  osd->blink);
		पूर्ण
	पूर्ण

	/*
	 * If we just चयनed to a 1-, 2-, or 4-bits-per-pixel biपंचांगap क्रमmat
	 * then configure a शेष palette map.
	 */
	अगर ((lconfig->pixfmt != cfg->pixfmt) &&
	  ((lconfig->pixfmt == PIXFMT_1BPP) ||
	  (lconfig->pixfmt == PIXFMT_2BPP) ||
	  (lconfig->pixfmt == PIXFMT_4BPP))) अणु
		क्रमागत osd_win_layer osdwin =
		    ((layer == WIN_OSD0) ? OSDWIN_OSD0 : OSDWIN_OSD1);
		काष्ठा osd_osdwin_state *osdwin_state =
		    &osd->osdwin[osdwin];
		अचिन्हित अक्षर clut_index;
		अचिन्हित अक्षर clut_entries = 0;

		चयन (lconfig->pixfmt) अणु
		हाल PIXFMT_1BPP:
			clut_entries = 2;
			अवरोध;
		हाल PIXFMT_2BPP:
			clut_entries = 4;
			अवरोध;
		हाल PIXFMT_4BPP:
			clut_entries = 16;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		/*
		 * The शेष palette map maps the pixel value to the clut
		 * index, i.e. pixel value 0 maps to clut entry 0, pixel value
		 * 1 maps to clut entry 1, etc.
		 */
		क्रम (clut_index = 0; clut_index < 16; clut_index++) अणु
			osdwin_state->palette_map[clut_index] = clut_index;
			अगर (clut_index < clut_entries) अणु
				_osd_set_palette_map(sd, osdwin, clut_index,
						     clut_index,
						     lconfig->pixfmt);
			पूर्ण
		पूर्ण
	पूर्ण

	*cfg = *lconfig;
	/* DM6446: configure the RGB888 enable and winकरोw selection */
	अगर (osd->win[WIN_VID0].lconfig.pixfmt == PIXFMT_RGB888)
		_osd_enable_vid_rgb888(sd, WIN_VID0);
	अन्यथा अगर (osd->win[WIN_VID1].lconfig.pixfmt == PIXFMT_RGB888)
		_osd_enable_vid_rgb888(sd, WIN_VID1);
	अन्यथा
		_osd_disable_vid_rgb888(sd);

	अगर (layer == WIN_VID0) अणु
		osd->pingpong =
		    _osd_dm6446_vid0_pingpong(sd, osd->field_inversion,
						       win->fb_base_phys,
						       cfg);
	पूर्ण

	spin_unlock_irqrestore(&osd->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम osd_init_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	क्रमागत osd_win_layer osdwin;
	काष्ठा osd_osdwin_state *osdwin_state;
	काष्ठा osd_layer_config *cfg = &win->lconfig;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	win->is_enabled = 0;
	_osd_disable_layer(sd, layer);

	win->h_zoom = ZOOM_X1;
	win->v_zoom = ZOOM_X1;
	_osd_set_zoom(sd, layer, win->h_zoom, win->v_zoom);

	win->fb_base_phys = 0;
	_osd_start_layer(sd, layer, win->fb_base_phys, 0);

	cfg->line_length = 0;
	cfg->xsize = 0;
	cfg->ysize = 0;
	cfg->xpos = 0;
	cfg->ypos = 0;
	cfg->पूर्णांकerlaced = 0;
	चयन (layer) अणु
	हाल WIN_OSD0:
	हाल WIN_OSD1:
		osdwin = (layer == WIN_OSD0) ? OSDWIN_OSD0 : OSDWIN_OSD1;
		osdwin_state = &osd->osdwin[osdwin];
		/*
		 * Other code relies on the fact that OSD winकरोws शेष to a
		 * biपंचांगap pixel क्रमmat when they are deallocated, so करोn't
		 * change this शेष pixel क्रमmat.
		 */
		cfg->pixfmt = PIXFMT_8BPP;
		_osd_set_layer_config(sd, layer, cfg);
		osdwin_state->clut = RAM_CLUT;
		_osd_set_osd_clut(sd, osdwin, osdwin_state->clut);
		osdwin_state->colorkey_blending = 0;
		_osd_disable_color_key(sd, osdwin);
		osdwin_state->blend = OSD_8_VID_0;
		_osd_set_blending_factor(sd, osdwin, osdwin_state->blend);
		osdwin_state->rec601_attenuation = 0;
		_osd_set_rec601_attenuation(sd, osdwin,
						     osdwin_state->
						     rec601_attenuation);
		अगर (osdwin == OSDWIN_OSD1) अणु
			osd->is_blinking = 0;
			osd->blink = BLINK_X1;
		पूर्ण
		अवरोध;
	हाल WIN_VID0:
	हाल WIN_VID1:
		cfg->pixfmt = osd->yc_pixfmt;
		_osd_set_layer_config(sd, layer, cfg);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&osd->lock, flags);
पूर्ण

अटल व्योम osd_release_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	अगर (!win->is_allocated) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&osd->lock, flags);
	osd_init_layer(sd, layer);
	spin_lock_irqsave(&osd->lock, flags);

	win->is_allocated = 0;

	spin_unlock_irqrestore(&osd->lock, flags);
पूर्ण

अटल पूर्णांक osd_request_layer(काष्ठा osd_state *sd, क्रमागत osd_layer layer)
अणु
	काष्ठा osd_state *osd = sd;
	काष्ठा osd_winकरोw_state *win = &osd->win[layer];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&osd->lock, flags);

	अगर (win->is_allocated) अणु
		spin_unlock_irqrestore(&osd->lock, flags);
		वापस -1;
	पूर्ण
	win->is_allocated = 1;

	spin_unlock_irqrestore(&osd->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम _osd_init(काष्ठा osd_state *sd)
अणु
	osd_ग_लिखो(sd, 0, OSD_MODE);
	osd_ग_लिखो(sd, 0, OSD_VIDWINMD);
	osd_ग_लिखो(sd, 0, OSD_OSDWIN0MD);
	osd_ग_लिखो(sd, 0, OSD_OSDWIN1MD);
	osd_ग_लिखो(sd, 0, OSD_RECTCUR);
	osd_ग_लिखो(sd, 0, OSD_MISCCTL);
	अगर (sd->vpbe_type == VPBE_VERSION_3) अणु
		osd_ग_लिखो(sd, 0, OSD_VBNDRY);
		osd_ग_लिखो(sd, 0, OSD_EXTMODE);
		osd_ग_लिखो(sd, OSD_MISCCTL_DMANG, OSD_MISCCTL);
	पूर्ण
पूर्ण

अटल व्योम osd_set_left_margin(काष्ठा osd_state *sd, u32 val)
अणु
	osd_ग_लिखो(sd, val, OSD_BASEPX);
पूर्ण

अटल व्योम osd_set_top_margin(काष्ठा osd_state *sd, u32 val)
अणु
	osd_ग_लिखो(sd, val, OSD_BASEPY);
पूर्ण

अटल पूर्णांक osd_initialize(काष्ठा osd_state *osd)
अणु
	अगर (osd == शून्य)
		वापस -ENODEV;
	_osd_init(osd);

	/* set शेष Cb/Cr order */
	osd->yc_pixfmt = PIXFMT_YCBCRI;

	अगर (osd->vpbe_type == VPBE_VERSION_3) अणु
		/*
		 * ROM CLUT1 on the DM355 is similar (identical?) to ROM CLUT0
		 * on the DM6446, so make ROM_CLUT1 the शेष on the DM355.
		 */
		osd->rom_clut = ROM_CLUT1;
	पूर्ण

	_osd_set_field_inversion(osd, osd->field_inversion);
	_osd_set_rom_clut(osd, osd->rom_clut);

	osd_init_layer(osd, WIN_OSD0);
	osd_init_layer(osd, WIN_VID0);
	osd_init_layer(osd, WIN_OSD1);
	osd_init_layer(osd, WIN_VID1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vpbe_osd_ops osd_ops = अणु
	.initialize = osd_initialize,
	.request_layer = osd_request_layer,
	.release_layer = osd_release_layer,
	.enable_layer = osd_enable_layer,
	.disable_layer = osd_disable_layer,
	.set_layer_config = osd_set_layer_config,
	.get_layer_config = osd_get_layer_config,
	.start_layer = osd_start_layer,
	.set_left_margin = osd_set_left_margin,
	.set_top_margin = osd_set_top_margin,
पूर्ण;

अटल पूर्णांक osd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *pdev_id;
	काष्ठा osd_state *osd;
	काष्ठा resource *res;

	pdev_id = platक्रमm_get_device_id(pdev);
	अगर (!pdev_id)
		वापस -EINVAL;

	osd = devm_kzalloc(&pdev->dev, माप(काष्ठा osd_state), GFP_KERNEL);
	अगर (osd == शून्य)
		वापस -ENOMEM;


	osd->dev = &pdev->dev;
	osd->vpbe_type = pdev_id->driver_data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	osd->osd_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(osd->osd_base))
		वापस PTR_ERR(osd->osd_base);

	osd->osd_base_phys = res->start;
	osd->osd_size = resource_size(res);
	spin_lock_init(&osd->lock);
	osd->ops = osd_ops;
	platक्रमm_set_drvdata(pdev, osd);
	dev_notice(osd->dev, "OSD sub device probe success\n");

	वापस 0;
पूर्ण

अटल पूर्णांक osd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver osd_driver = अणु
	.probe		= osd_probe,
	.हटाओ		= osd_हटाओ,
	.driver		= अणु
		.name	= MODULE_NAME,
	पूर्ण,
	.id_table	= vpbe_osd_devtype
पूर्ण;

module_platक्रमm_driver(osd_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DaVinci OSD Manager Driver");
MODULE_AUTHOR("Texas Instruments");
