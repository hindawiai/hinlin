<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Ingenic JZ47xx KMS driver
//
// Copyright (C) 2019, Paul Cercueil <paul@crapouillou.net>

#समावेश "ingenic-drm.h"

#समावेश <linux/component.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

काष्ठा ingenic_dma_hwdesc अणु
	u32 next;
	u32 addr;
	u32 id;
	u32 cmd;
पूर्ण __aligned(16);

काष्ठा ingenic_dma_hwdescs अणु
	काष्ठा ingenic_dma_hwdesc hwdesc_f0;
	काष्ठा ingenic_dma_hwdesc hwdesc_f1;
	काष्ठा ingenic_dma_hwdesc hwdesc_pal;
	u16 palette[256] __aligned(16);
पूर्ण;

काष्ठा jz_soc_info अणु
	bool needs_dev_clk;
	bool has_osd;
	अचिन्हित पूर्णांक max_width, max_height;
	स्थिर u32 *क्रमmats_f0, *क्रमmats_f1;
	अचिन्हित पूर्णांक num_क्रमmats_f0, num_क्रमmats_f1;
पूर्ण;

काष्ठा ingenic_drm अणु
	काष्ठा drm_device drm;
	/*
	 * f1 (aka. क्रमeground1) is our primary plane, on top of which
	 * f0 (aka. क्रमeground0) can be overlayed. Z-order is fixed in
	 * hardware and cannot be changed.
	 */
	काष्ठा drm_plane f0, f1, *ipu_plane;
	काष्ठा drm_crtc crtc;

	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा clk *lcd_clk, *pix_clk;
	स्थिर काष्ठा jz_soc_info *soc_info;

	काष्ठा ingenic_dma_hwdescs *dma_hwdescs;
	dma_addr_t dma_hwdescs_phys;

	bool panel_is_sharp;
	bool no_vblank;

	/*
	 * clk_mutex is used to synchronize the pixel घड़ी rate update with
	 * the VBLANK. When the pixel घड़ी's parent घड़ी needs to be updated,
	 * घड़ी_nb's notअगरier function will lock the mutex, then रुको until the
	 * next VBLANK. At that poपूर्णांक, the parent घड़ी's rate can be updated,
	 * and the mutex is then unlocked. If an atomic commit happens in the
	 * meanसमय, it will lock on the mutex, effectively रुकोing until the
	 * घड़ी update process finishes. Finally, the pixel घड़ी's rate will
	 * be recomputed when the mutex has been released, in the pending atomic
	 * commit, or a future one.
	 */
	काष्ठा mutex clk_mutex;
	bool update_clk_rate;
	काष्ठा notअगरier_block घड़ी_nb;
पूर्ण;

अटल bool ingenic_drm_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल JZ_REG_LCD_IID:
	हाल JZ_REG_LCD_SA0:
	हाल JZ_REG_LCD_FID0:
	हाल JZ_REG_LCD_CMD0:
	हाल JZ_REG_LCD_SA1:
	हाल JZ_REG_LCD_FID1:
	हाल JZ_REG_LCD_CMD1:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config ingenic_drm_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,

	.max_रेजिस्टर = JZ_REG_LCD_SIZE1,
	.ग_लिखोable_reg = ingenic_drm_ग_लिखोable_reg,
पूर्ण;

अटल अंतरभूत काष्ठा ingenic_drm *drm_device_get_priv(काष्ठा drm_device *drm)
अणु
	वापस container_of(drm, काष्ठा ingenic_drm, drm);
पूर्ण

अटल अंतरभूत काष्ठा ingenic_drm *drm_crtc_get_priv(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा ingenic_drm, crtc);
पूर्ण

अटल अंतरभूत काष्ठा ingenic_drm *drm_nb_get_priv(काष्ठा notअगरier_block *nb)
अणु
	वापस container_of(nb, काष्ठा ingenic_drm, घड़ी_nb);
पूर्ण

अटल पूर्णांक ingenic_drm_update_pixclk(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action,
				     व्योम *data)
अणु
	काष्ठा ingenic_drm *priv = drm_nb_get_priv(nb);

	चयन (action) अणु
	हाल PRE_RATE_CHANGE:
		mutex_lock(&priv->clk_mutex);
		priv->update_clk_rate = true;
		drm_crtc_रुको_one_vblank(&priv->crtc);
		वापस NOTIFY_OK;
	शेष:
		mutex_unlock(&priv->clk_mutex);
		वापस NOTIFY_OK;
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_STATE, 0);

	regmap_update_bits(priv->map, JZ_REG_LCD_CTRL,
			   JZ_LCD_CTRL_ENABLE | JZ_LCD_CTRL_DISABLE,
			   JZ_LCD_CTRL_ENABLE);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम ingenic_drm_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);
	अचिन्हित पूर्णांक var;

	drm_crtc_vblank_off(crtc);

	regmap_update_bits(priv->map, JZ_REG_LCD_CTRL,
			   JZ_LCD_CTRL_DISABLE, JZ_LCD_CTRL_DISABLE);

	regmap_पढ़ो_poll_समयout(priv->map, JZ_REG_LCD_STATE, var,
				 var & JZ_LCD_STATE_DISABLED,
				 1000, 0);
पूर्ण

अटल व्योम ingenic_drm_crtc_update_timings(काष्ठा ingenic_drm *priv,
					    काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक vpe, vds, vde, vt, hpe, hds, hde, ht;

	vpe = mode->crtc_vsync_end - mode->crtc_vsync_start;
	vds = mode->crtc_vtotal - mode->crtc_vsync_start;
	vde = vds + mode->crtc_vdisplay;
	vt = vde + mode->crtc_vsync_start - mode->crtc_vdisplay;

	hpe = mode->crtc_hsync_end - mode->crtc_hsync_start;
	hds = mode->crtc_htotal - mode->crtc_hsync_start;
	hde = hds + mode->crtc_hdisplay;
	ht = hde + mode->crtc_hsync_start - mode->crtc_hdisplay;

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_VSYNC,
		     0 << JZ_LCD_VSYNC_VPS_OFFSET |
		     vpe << JZ_LCD_VSYNC_VPE_OFFSET);

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_HSYNC,
		     0 << JZ_LCD_HSYNC_HPS_OFFSET |
		     hpe << JZ_LCD_HSYNC_HPE_OFFSET);

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_VAT,
		     ht << JZ_LCD_VAT_HT_OFFSET |
		     vt << JZ_LCD_VAT_VT_OFFSET);

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_DAH,
		     hds << JZ_LCD_DAH_HDS_OFFSET |
		     hde << JZ_LCD_DAH_HDE_OFFSET);
	regmap_ग_लिखो(priv->map, JZ_REG_LCD_DAV,
		     vds << JZ_LCD_DAV_VDS_OFFSET |
		     vde << JZ_LCD_DAV_VDE_OFFSET);

	अगर (priv->panel_is_sharp) अणु
		regmap_ग_लिखो(priv->map, JZ_REG_LCD_PS, hde << 16 | (hde + 1));
		regmap_ग_लिखो(priv->map, JZ_REG_LCD_CLS, hde << 16 | (hde + 1));
		regmap_ग_लिखो(priv->map, JZ_REG_LCD_SPL, hpe << 16 | (hpe + 1));
		regmap_ग_लिखो(priv->map, JZ_REG_LCD_REV, mode->htotal << 16);
	पूर्ण

	regmap_set_bits(priv->map, JZ_REG_LCD_CTRL,
			JZ_LCD_CTRL_OFUP | JZ_LCD_CTRL_BURST_16);

	/*
	 * IPU restart - specअगरy how much समय the LCDC will रुको beक्रमe
	 * transferring a new frame from the IPU. The value is the one
	 * suggested in the programming manual.
	 */
	regmap_ग_लिखो(priv->map, JZ_REG_LCD_IPUR, JZ_LCD_IPUR_IPUREN |
		     (ht * vpe / 3) << JZ_LCD_IPUR_IPUR_LSB);
पूर्ण

अटल पूर्णांक ingenic_drm_crtc_atomic_check(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);
	काष्ठा drm_plane_state *f1_state, *f0_state, *ipu_state = शून्य;

	अगर (crtc_state->gamma_lut &&
	    drm_color_lut_size(crtc_state->gamma_lut) != ARRAY_SIZE(priv->dma_hwdescs->palette)) अणु
		dev_dbg(priv->dev, "Invalid palette size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (drm_atomic_crtc_needs_modeset(crtc_state) && priv->soc_info->has_osd) अणु
		f1_state = drm_atomic_get_plane_state(crtc_state->state,
						      &priv->f1);
		अगर (IS_ERR(f1_state))
			वापस PTR_ERR(f1_state);

		f0_state = drm_atomic_get_plane_state(crtc_state->state,
						      &priv->f0);
		अगर (IS_ERR(f0_state))
			वापस PTR_ERR(f0_state);

		अगर (IS_ENABLED(CONFIG_DRM_INGENIC_IPU) && priv->ipu_plane) अणु
			ipu_state = drm_atomic_get_plane_state(crtc_state->state,
							       priv->ipu_plane);
			अगर (IS_ERR(ipu_state))
				वापस PTR_ERR(ipu_state);

			/* IPU and F1 planes cannot be enabled at the same समय. */
			अगर (f1_state->fb && ipu_state->fb) अणु
				dev_dbg(priv->dev, "Cannot enable both F1 and IPU\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* If all the planes are disabled, we won't get a VBLANK IRQ */
		priv->no_vblank = !f1_state->fb && !f0_state->fb &&
				  !(ipu_state && ipu_state->fb);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status
ingenic_drm_crtc_mode_valid(काष्ठा drm_crtc *crtc, स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);
	दीर्घ rate;

	अगर (mode->hdisplay > priv->soc_info->max_width)
		वापस MODE_BAD_HVALUE;
	अगर (mode->vdisplay > priv->soc_info->max_height)
		वापस MODE_BAD_VVALUE;

	rate = clk_round_rate(priv->pix_clk, mode->घड़ी * 1000);
	अगर (rate < 0)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल व्योम ingenic_drm_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);
	u32 ctrl = 0;

	अगर (priv->soc_info->has_osd &&
	    drm_atomic_crtc_needs_modeset(crtc_state)) अणु
		/*
		 * If IPU plane is enabled, enable IPU as source क्रम the F1
		 * plane; otherwise use regular DMA.
		 */
		अगर (priv->ipu_plane && priv->ipu_plane->state->fb)
			ctrl |= JZ_LCD_OSDCTRL_IPU;

		regmap_update_bits(priv->map, JZ_REG_LCD_OSDCTRL,
				   JZ_LCD_OSDCTRL_IPU, ctrl);
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_pending_vblank_event *event = crtc_state->event;

	अगर (drm_atomic_crtc_needs_modeset(crtc_state)) अणु
		ingenic_drm_crtc_update_timings(priv, &crtc_state->adjusted_mode);
		priv->update_clk_rate = true;
	पूर्ण

	अगर (priv->update_clk_rate) अणु
		mutex_lock(&priv->clk_mutex);
		clk_set_rate(priv->pix_clk,
			     crtc_state->adjusted_mode.घड़ी * 1000);
		priv->update_clk_rate = false;
		mutex_unlock(&priv->clk_mutex);
	पूर्ण

	अगर (event) अणु
		crtc_state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक ingenic_drm_plane_atomic_check(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_plane_state = drm_atomic_get_old_plane_state(state,
										 plane);
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा ingenic_drm *priv = drm_device_get_priv(plane->dev);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc = new_plane_state->crtc ?: old_plane_state->crtc;
	पूर्णांक ret;

	अगर (!crtc)
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  priv->soc_info->has_osd,
						  true);
	अगर (ret)
		वापस ret;

	/*
	 * If OSD is not available, check that the width/height match.
	 * Note that state->src_* are in 16.16 fixed-poपूर्णांक क्रमmat.
	 */
	अगर (!priv->soc_info->has_osd &&
	    (new_plane_state->src_x != 0 ||
	     (new_plane_state->src_w >> 16) != new_plane_state->crtc_w ||
	     (new_plane_state->src_h >> 16) != new_plane_state->crtc_h))
		वापस -EINVAL;

	/*
	 * Require full modeset अगर enabling or disabling a plane, or changing
	 * its position, size or depth.
	 */
	अगर (priv->soc_info->has_osd &&
	    (!old_plane_state->fb || !new_plane_state->fb ||
	     old_plane_state->crtc_x != new_plane_state->crtc_x ||
	     old_plane_state->crtc_y != new_plane_state->crtc_y ||
	     old_plane_state->crtc_w != new_plane_state->crtc_w ||
	     old_plane_state->crtc_h != new_plane_state->crtc_h ||
	     old_plane_state->fb->क्रमmat->क्रमmat != new_plane_state->fb->क्रमmat->क्रमmat))
		crtc_state->mode_changed = true;

	वापस 0;
पूर्ण

अटल व्योम ingenic_drm_plane_enable(काष्ठा ingenic_drm *priv,
				     काष्ठा drm_plane *plane)
अणु
	अचिन्हित पूर्णांक en_bit;

	अगर (priv->soc_info->has_osd) अणु
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
			en_bit = JZ_LCD_OSDC_F1EN;
		अन्यथा
			en_bit = JZ_LCD_OSDC_F0EN;

		regmap_set_bits(priv->map, JZ_REG_LCD_OSDC, en_bit);
	पूर्ण
पूर्ण

व्योम ingenic_drm_plane_disable(काष्ठा device *dev, काष्ठा drm_plane *plane)
अणु
	काष्ठा ingenic_drm *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक en_bit;

	अगर (priv->soc_info->has_osd) अणु
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
			en_bit = JZ_LCD_OSDC_F1EN;
		अन्यथा
			en_bit = JZ_LCD_OSDC_F0EN;

		regmap_clear_bits(priv->map, JZ_REG_LCD_OSDC, en_bit);
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_plane_atomic_disable(काष्ठा drm_plane *plane,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_drm *priv = drm_device_get_priv(plane->dev);

	ingenic_drm_plane_disable(priv->dev, plane);
पूर्ण

व्योम ingenic_drm_plane_config(काष्ठा device *dev,
			      काष्ठा drm_plane *plane, u32 fourcc)
अणु
	काष्ठा ingenic_drm *priv = dev_get_drvdata(dev);
	काष्ठा drm_plane_state *state = plane->state;
	अचिन्हित पूर्णांक xy_reg, size_reg;
	अचिन्हित पूर्णांक ctrl = 0;

	ingenic_drm_plane_enable(priv, plane);

	अगर (priv->soc_info->has_osd &&
	    plane->type == DRM_PLANE_TYPE_PRIMARY) अणु
		चयन (fourcc) अणु
		हाल DRM_FORMAT_XRGB1555:
			ctrl |= JZ_LCD_OSDCTRL_RGB555;
			fallthrough;
		हाल DRM_FORMAT_RGB565:
			ctrl |= JZ_LCD_OSDCTRL_BPP_15_16;
			अवरोध;
		हाल DRM_FORMAT_RGB888:
			ctrl |= JZ_LCD_OSDCTRL_BPP_24_COMP;
			अवरोध;
		हाल DRM_FORMAT_XRGB8888:
			ctrl |= JZ_LCD_OSDCTRL_BPP_18_24;
			अवरोध;
		हाल DRM_FORMAT_XRGB2101010:
			ctrl |= JZ_LCD_OSDCTRL_BPP_30;
			अवरोध;
		पूर्ण

		regmap_update_bits(priv->map, JZ_REG_LCD_OSDCTRL,
				   JZ_LCD_OSDCTRL_BPP_MASK, ctrl);
	पूर्ण अन्यथा अणु
		चयन (fourcc) अणु
		हाल DRM_FORMAT_C8:
			ctrl |= JZ_LCD_CTRL_BPP_8;
			अवरोध;
		हाल DRM_FORMAT_XRGB1555:
			ctrl |= JZ_LCD_CTRL_RGB555;
			fallthrough;
		हाल DRM_FORMAT_RGB565:
			ctrl |= JZ_LCD_CTRL_BPP_15_16;
			अवरोध;
		हाल DRM_FORMAT_RGB888:
			ctrl |= JZ_LCD_CTRL_BPP_24_COMP;
			अवरोध;
		हाल DRM_FORMAT_XRGB8888:
			ctrl |= JZ_LCD_CTRL_BPP_18_24;
			अवरोध;
		हाल DRM_FORMAT_XRGB2101010:
			ctrl |= JZ_LCD_CTRL_BPP_30;
			अवरोध;
		पूर्ण

		regmap_update_bits(priv->map, JZ_REG_LCD_CTRL,
				   JZ_LCD_CTRL_BPP_MASK, ctrl);
	पूर्ण

	अगर (priv->soc_info->has_osd) अणु
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY) अणु
			xy_reg = JZ_REG_LCD_XYP1;
			size_reg = JZ_REG_LCD_SIZE1;
		पूर्ण अन्यथा अणु
			xy_reg = JZ_REG_LCD_XYP0;
			size_reg = JZ_REG_LCD_SIZE0;
		पूर्ण

		regmap_ग_लिखो(priv->map, xy_reg,
			     state->crtc_x << JZ_LCD_XYP01_XPOS_LSB |
			     state->crtc_y << JZ_LCD_XYP01_YPOS_LSB);
		regmap_ग_लिखो(priv->map, size_reg,
			     state->crtc_w << JZ_LCD_SIZE01_WIDTH_LSB |
			     state->crtc_h << JZ_LCD_SIZE01_HEIGHT_LSB);
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_update_palette(काष्ठा ingenic_drm *priv,
				       स्थिर काष्ठा drm_color_lut *lut)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->dma_hwdescs->palette); i++) अणु
		u16 color = drm_color_lut_extract(lut[i].red, 5) << 11
			| drm_color_lut_extract(lut[i].green, 6) << 5
			| drm_color_lut_extract(lut[i].blue, 5);

		priv->dma_hwdescs->palette[i] = color;
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_plane_atomic_update(काष्ठा drm_plane *plane,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_drm *priv = drm_device_get_priv(plane->dev);
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  plane);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा ingenic_dma_hwdesc *hwdesc;
	अचिन्हित पूर्णांक width, height, cpp, offset;
	dma_addr_t addr;
	u32 fourcc;

	अगर (newstate && newstate->fb) अणु
		crtc_state = newstate->crtc->state;

		addr = drm_fb_cma_get_gem_addr(newstate->fb, newstate, 0);
		width = newstate->src_w >> 16;
		height = newstate->src_h >> 16;
		cpp = newstate->fb->क्रमmat->cpp[0];

		अगर (!priv->soc_info->has_osd || plane->type == DRM_PLANE_TYPE_OVERLAY)
			hwdesc = &priv->dma_hwdescs->hwdesc_f0;
		अन्यथा
			hwdesc = &priv->dma_hwdescs->hwdesc_f1;

		hwdesc->addr = addr;
		hwdesc->cmd = JZ_LCD_CMD_खातापूर्ण_IRQ | (width * height * cpp / 4);

		अगर (drm_atomic_crtc_needs_modeset(crtc_state)) अणु
			fourcc = newstate->fb->क्रमmat->क्रमmat;

			ingenic_drm_plane_config(priv->dev, plane, fourcc);

			अगर (fourcc == DRM_FORMAT_C8)
				offset = दुरत्व(काष्ठा ingenic_dma_hwdescs, hwdesc_pal);
			अन्यथा
				offset = दुरत्व(काष्ठा ingenic_dma_hwdescs, hwdesc_f0);

			priv->dma_hwdescs->hwdesc_f0.next = priv->dma_hwdescs_phys + offset;

			crtc_state->color_mgmt_changed = fourcc == DRM_FORMAT_C8;
		पूर्ण

		अगर (crtc_state->color_mgmt_changed)
			ingenic_drm_update_palette(priv, crtc_state->gamma_lut->data);
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_encoder_atomic_mode_set(काष्ठा drm_encoder *encoder,
						काष्ठा drm_crtc_state *crtc_state,
						काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा ingenic_drm *priv = drm_device_get_priv(encoder->dev);
	काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;
	काष्ठा drm_connector *conn = conn_state->connector;
	काष्ठा drm_display_info *info = &conn->display_info;
	अचिन्हित पूर्णांक cfg, rgbcfg = 0;

	priv->panel_is_sharp = info->bus_flags & DRM_BUS_FLAG_SHARP_SIGNALS;

	अगर (priv->panel_is_sharp) अणु
		cfg = JZ_LCD_CFG_MODE_SPECIAL_TFT_1 | JZ_LCD_CFG_REV_POLARITY;
	पूर्ण अन्यथा अणु
		cfg = JZ_LCD_CFG_PS_DISABLE | JZ_LCD_CFG_CLS_DISABLE
		    | JZ_LCD_CFG_SPL_DISABLE | JZ_LCD_CFG_REV_DISABLE;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		cfg |= JZ_LCD_CFG_HSYNC_ACTIVE_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		cfg |= JZ_LCD_CFG_VSYNC_ACTIVE_LOW;
	अगर (info->bus_flags & DRM_BUS_FLAG_DE_LOW)
		cfg |= JZ_LCD_CFG_DE_ACTIVE_LOW;
	अगर (info->bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		cfg |= JZ_LCD_CFG_PCLK_FALLING_EDGE;

	अगर (!priv->panel_is_sharp) अणु
		अगर (conn->connector_type == DRM_MODE_CONNECTOR_TV) अणु
			अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
				cfg |= JZ_LCD_CFG_MODE_TV_OUT_I;
			अन्यथा
				cfg |= JZ_LCD_CFG_MODE_TV_OUT_P;
		पूर्ण अन्यथा अणु
			चयन (*info->bus_क्रमmats) अणु
			हाल MEDIA_BUS_FMT_RGB565_1X16:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_16BIT;
				अवरोध;
			हाल MEDIA_BUS_FMT_RGB666_1X18:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_18BIT;
				अवरोध;
			हाल MEDIA_BUS_FMT_RGB888_1X24:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_24BIT;
				अवरोध;
			हाल MEDIA_BUS_FMT_RGB888_3X8_DELTA:
				rgbcfg = JZ_LCD_RGBC_EVEN_GBR | JZ_LCD_RGBC_ODD_RGB;
				fallthrough;
			हाल MEDIA_BUS_FMT_RGB888_3X8:
				cfg |= JZ_LCD_CFG_MODE_8BIT_SERIAL;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	regmap_ग_लिखो(priv->map, JZ_REG_LCD_CFG, cfg);
	regmap_ग_लिखो(priv->map, JZ_REG_LCD_RGBC, rgbcfg);
पूर्ण

अटल पूर्णांक ingenic_drm_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_crtc_state *crtc_state,
					    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_display_info *info = &conn_state->connector->display_info;
	काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;

	अगर (info->num_bus_क्रमmats != 1)
		वापस -EINVAL;

	अगर (conn_state->connector->connector_type == DRM_MODE_CONNECTOR_TV)
		वापस 0;

	चयन (*info->bus_क्रमmats) अणु
	हाल MEDIA_BUS_FMT_RGB888_3X8:
	हाल MEDIA_BUS_FMT_RGB888_3X8_DELTA:
		/*
		 * The LCD controller expects timing values in करोt-घड़ी ticks,
		 * which is 3x the timing values in pixels when using a 3x8-bit
		 * display; but it will count the display area size in pixels
		 * either way. Go figure.
		 */
		mode->crtc_घड़ी = mode->घड़ी * 3;
		mode->crtc_hsync_start = mode->hsync_start * 3 - mode->hdisplay * 2;
		mode->crtc_hsync_end = mode->hsync_end * 3 - mode->hdisplay * 2;
		mode->crtc_hdisplay = mode->hdisplay;
		mode->crtc_htotal = mode->htotal * 3 - mode->hdisplay * 2;
		वापस 0;
	हाल MEDIA_BUS_FMT_RGB565_1X16:
	हाल MEDIA_BUS_FMT_RGB666_1X18:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ingenic_drm_atomic_helper_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	/*
	 * Just your regular drm_atomic_helper_commit_tail(), but only calls
	 * drm_atomic_helper_रुको_क्रम_vblanks() अगर priv->no_vblank.
	 */
	काष्ठा drm_device *dev = old_state->dev;
	काष्ठा ingenic_drm *priv = drm_device_get_priv(dev);

	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	drm_atomic_helper_commit_planes(dev, old_state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);

	अगर (!priv->no_vblank)
		drm_atomic_helper_रुको_क्रम_vblanks(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण

अटल irqवापस_t ingenic_drm_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ingenic_drm *priv = drm_device_get_priv(arg);
	अचिन्हित पूर्णांक state;

	regmap_पढ़ो(priv->map, JZ_REG_LCD_STATE, &state);

	regmap_update_bits(priv->map, JZ_REG_LCD_STATE,
			   JZ_LCD_STATE_खातापूर्ण_IRQ, 0);

	अगर (state & JZ_LCD_STATE_खातापूर्ण_IRQ)
		drm_crtc_handle_vblank(&priv->crtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ingenic_drm_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);

	regmap_update_bits(priv->map, JZ_REG_LCD_CTRL,
			   JZ_LCD_CTRL_खातापूर्ण_IRQ, JZ_LCD_CTRL_खातापूर्ण_IRQ);

	वापस 0;
पूर्ण

अटल व्योम ingenic_drm_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ingenic_drm *priv = drm_crtc_get_priv(crtc);

	regmap_update_bits(priv->map, JZ_REG_LCD_CTRL, JZ_LCD_CTRL_खातापूर्ण_IRQ, 0);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(ingenic_drm_fops);

अटल स्थिर काष्ठा drm_driver ingenic_drm_driver_data = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.name			= "ingenic-drm",
	.desc			= "DRM module for Ingenic SoCs",
	.date			= "20200716",
	.major			= 1,
	.minor			= 1,
	.patchlevel		= 0,

	.fops			= &ingenic_drm_fops,
	DRM_GEM_CMA_DRIVER_OPS,

	.irq_handler		= ingenic_drm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs ingenic_drm_primary_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.reset			= drm_atomic_helper_plane_reset,
	.destroy		= drm_plane_cleanup,

	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs ingenic_drm_crtc_funcs = अणु
	.set_config		= drm_atomic_helper_set_config,
	.page_flip		= drm_atomic_helper_page_flip,
	.reset			= drm_atomic_helper_crtc_reset,
	.destroy		= drm_crtc_cleanup,

	.atomic_duplicate_state	= drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_crtc_destroy_state,

	.enable_vblank		= ingenic_drm_enable_vblank,
	.disable_vblank		= ingenic_drm_disable_vblank,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs ingenic_drm_plane_helper_funcs = अणु
	.atomic_update		= ingenic_drm_plane_atomic_update,
	.atomic_check		= ingenic_drm_plane_atomic_check,
	.atomic_disable		= ingenic_drm_plane_atomic_disable,
	.prepare_fb		= drm_gem_plane_helper_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs ingenic_drm_crtc_helper_funcs = अणु
	.atomic_enable		= ingenic_drm_crtc_atomic_enable,
	.atomic_disable		= ingenic_drm_crtc_atomic_disable,
	.atomic_begin		= ingenic_drm_crtc_atomic_begin,
	.atomic_flush		= ingenic_drm_crtc_atomic_flush,
	.atomic_check		= ingenic_drm_crtc_atomic_check,
	.mode_valid		= ingenic_drm_crtc_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs ingenic_drm_encoder_helper_funcs = अणु
	.atomic_mode_set	= ingenic_drm_encoder_atomic_mode_set,
	.atomic_check		= ingenic_drm_encoder_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs ingenic_drm_mode_config_funcs = अणु
	.fb_create		= drm_gem_fb_create,
	.output_poll_changed	= drm_fb_helper_output_poll_changed,
	.atomic_check		= drm_atomic_helper_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

अटल काष्ठा drm_mode_config_helper_funcs ingenic_drm_mode_config_helpers = अणु
	.atomic_commit_tail = ingenic_drm_atomic_helper_commit_tail,
पूर्ण;

अटल व्योम ingenic_drm_unbind_all(व्योम *d)
अणु
	काष्ठा ingenic_drm *priv = d;

	component_unbind_all(priv->dev, &priv->drm);
पूर्ण

अटल व्योम __maybe_unused ingenic_drm_release_rmem(व्योम *d)
अणु
	of_reserved_mem_device_release(d);
पूर्ण

अटल पूर्णांक ingenic_drm_bind(काष्ठा device *dev, bool has_components)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा jz_soc_info *soc_info;
	काष्ठा ingenic_drm *priv;
	काष्ठा clk *parent_clk;
	काष्ठा drm_plane *primary;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *drm;
	व्योम __iomem *base;
	दीर्घ parent_rate;
	अचिन्हित पूर्णांक i, clone_mask = 0;
	dma_addr_t dma_hwdesc_phys_f0, dma_hwdesc_phys_f1;
	पूर्णांक ret, irq;

	soc_info = of_device_get_match_data(dev);
	अगर (!soc_info) अणु
		dev_err(dev, "Missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF_RESERVED_MEM)) अणु
		ret = of_reserved_mem_device_init(dev);

		अगर (ret && ret != -ENODEV)
			dev_warn(dev, "Failed to get reserved memory: %d\n", ret);

		अगर (!ret) अणु
			ret = devm_add_action_or_reset(dev, ingenic_drm_release_rmem, dev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	priv = devm_drm_dev_alloc(dev, &ingenic_drm_driver_data,
				  काष्ठा ingenic_drm, drm);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	priv->soc_info = soc_info;
	priv->dev = dev;
	drm = &priv->drm;

	platक्रमm_set_drvdata(pdev, priv);

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = soc_info->max_width;
	drm->mode_config.max_height = 4095;
	drm->mode_config.funcs = &ingenic_drm_mode_config_funcs;
	drm->mode_config.helper_निजी = &ingenic_drm_mode_config_helpers;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "Failed to get memory resource\n");
		वापस PTR_ERR(base);
	पूर्ण

	priv->map = devm_regmap_init_mmio(dev, base,
					  &ingenic_drm_regmap_config);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(dev, "Failed to create regmap\n");
		वापस PTR_ERR(priv->map);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (soc_info->needs_dev_clk) अणु
		priv->lcd_clk = devm_clk_get(dev, "lcd");
		अगर (IS_ERR(priv->lcd_clk)) अणु
			dev_err(dev, "Failed to get lcd clock\n");
			वापस PTR_ERR(priv->lcd_clk);
		पूर्ण
	पूर्ण

	priv->pix_clk = devm_clk_get(dev, "lcd_pclk");
	अगर (IS_ERR(priv->pix_clk)) अणु
		dev_err(dev, "Failed to get pixel clock\n");
		वापस PTR_ERR(priv->pix_clk);
	पूर्ण

	priv->dma_hwdescs = dmam_alloc_coherent(dev,
						माप(*priv->dma_hwdescs),
						&priv->dma_hwdescs_phys,
						GFP_KERNEL);
	अगर (!priv->dma_hwdescs)
		वापस -ENOMEM;


	/* Configure DMA hwdesc क्रम क्रमeground0 plane */
	dma_hwdesc_phys_f0 = priv->dma_hwdescs_phys
		+ दुरत्व(काष्ठा ingenic_dma_hwdescs, hwdesc_f0);
	priv->dma_hwdescs->hwdesc_f0.next = dma_hwdesc_phys_f0;
	priv->dma_hwdescs->hwdesc_f0.id = 0xf0;

	/* Configure DMA hwdesc क्रम क्रमeground1 plane */
	dma_hwdesc_phys_f1 = priv->dma_hwdescs_phys
		+ दुरत्व(काष्ठा ingenic_dma_hwdescs, hwdesc_f1);
	priv->dma_hwdescs->hwdesc_f1.next = dma_hwdesc_phys_f1;
	priv->dma_hwdescs->hwdesc_f1.id = 0xf1;

	/* Configure DMA hwdesc क्रम palette */
	priv->dma_hwdescs->hwdesc_pal.next = priv->dma_hwdescs_phys
		+ दुरत्व(काष्ठा ingenic_dma_hwdescs, hwdesc_f0);
	priv->dma_hwdescs->hwdesc_pal.id = 0xc0;
	priv->dma_hwdescs->hwdesc_pal.addr = priv->dma_hwdescs_phys
		+ दुरत्व(काष्ठा ingenic_dma_hwdescs, palette);
	priv->dma_hwdescs->hwdesc_pal.cmd = JZ_LCD_CMD_ENABLE_PAL
		| (माप(priv->dma_hwdescs->palette) / 4);

	अगर (soc_info->has_osd)
		priv->ipu_plane = drm_plane_from_index(drm, 0);

	primary = priv->soc_info->has_osd ? &priv->f1 : &priv->f0;

	drm_plane_helper_add(primary, &ingenic_drm_plane_helper_funcs);

	ret = drm_universal_plane_init(drm, primary, 1,
				       &ingenic_drm_primary_plane_funcs,
				       priv->soc_info->क्रमmats_f1,
				       priv->soc_info->num_क्रमmats_f1,
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Failed to register plane: %i\n", ret);
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(&priv->crtc, &ingenic_drm_crtc_helper_funcs);

	ret = drm_crtc_init_with_planes(drm, &priv->crtc, primary,
					शून्य, &ingenic_drm_crtc_funcs, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Failed to init CRTC: %i\n", ret);
		वापस ret;
	पूर्ण

	drm_crtc_enable_color_mgmt(&priv->crtc, 0, false,
				   ARRAY_SIZE(priv->dma_hwdescs->palette));

	अगर (soc_info->has_osd) अणु
		drm_plane_helper_add(&priv->f0,
				     &ingenic_drm_plane_helper_funcs);

		ret = drm_universal_plane_init(drm, &priv->f0, 1,
					       &ingenic_drm_primary_plane_funcs,
					       priv->soc_info->क्रमmats_f0,
					       priv->soc_info->num_क्रमmats_f0,
					       शून्य, DRM_PLANE_TYPE_OVERLAY,
					       शून्य);
		अगर (ret) अणु
			dev_err(dev, "Failed to register overlay plane: %i\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (IS_ENABLED(CONFIG_DRM_INGENIC_IPU) && has_components) अणु
			ret = component_bind_all(dev, drm);
			अगर (ret) अणु
				अगर (ret != -EPROBE_DEFER)
					dev_err(dev, "Failed to bind components: %i\n", ret);
				वापस ret;
			पूर्ण

			ret = devm_add_action_or_reset(dev, ingenic_drm_unbind_all, priv);
			अगर (ret)
				वापस ret;

			priv->ipu_plane = drm_plane_from_index(drm, 2);
			अगर (!priv->ipu_plane) अणु
				dev_err(dev, "Failed to retrieve IPU plane\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; ; i++) अणु
		ret = drm_of_find_panel_or_bridge(dev->of_node, 0, i, &panel, &bridge);
		अगर (ret) अणु
			अगर (ret == -ENODEV)
				अवरोध; /* we're करोne */
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get bridge handle\n");
			वापस ret;
		पूर्ण

		अगर (panel)
			bridge = devm_drm_panel_bridge_add_typed(dev, panel,
								 DRM_MODE_CONNECTOR_DPI);

		encoder = drmm_plain_encoder_alloc(drm, शून्य, DRM_MODE_ENCODER_DPI, शून्य);
		अगर (IS_ERR(encoder)) अणु
			ret = PTR_ERR(encoder);
			dev_err(dev, "Failed to init encoder: %d\n", ret);
			वापस ret;
		पूर्ण

		encoder->possible_crtcs = 1;

		drm_encoder_helper_add(encoder, &ingenic_drm_encoder_helper_funcs);

		ret = drm_bridge_attach(encoder, bridge, शून्य, 0);
		अगर (ret) अणु
			dev_err(dev, "Unable to attach bridge\n");
			वापस ret;
		पूर्ण
	पूर्ण

	drm_क्रम_each_encoder(encoder, drm) अणु
		clone_mask |= BIT(drm_encoder_index(encoder));
	पूर्ण

	drm_क्रम_each_encoder(encoder, drm) अणु
		encoder->possible_clones = clone_mask;
	पूर्ण

	ret = drm_irq_install(drm, irq);
	अगर (ret) अणु
		dev_err(dev, "Unable to install IRQ handler\n");
		वापस ret;
	पूर्ण

	ret = drm_vblank_init(drm, 1);
	अगर (ret) अणु
		dev_err(dev, "Failed calling drm_vblank_init()\n");
		वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);

	ret = clk_prepare_enable(priv->pix_clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to start pixel clock\n");
		वापस ret;
	पूर्ण

	अगर (priv->lcd_clk) अणु
		parent_clk = clk_get_parent(priv->lcd_clk);
		parent_rate = clk_get_rate(parent_clk);

		/* LCD Device घड़ी must be 3x the pixel घड़ी क्रम STN panels,
		 * or 1.5x the pixel घड़ी क्रम TFT panels. To aव्योम having to
		 * check क्रम the LCD device घड़ी everyसमय we करो a mode change,
		 * we set the LCD device घड़ी to the highest rate possible.
		 */
		ret = clk_set_rate(priv->lcd_clk, parent_rate);
		अगर (ret) अणु
			dev_err(dev, "Unable to set LCD clock rate\n");
			जाओ err_pixclk_disable;
		पूर्ण

		ret = clk_prepare_enable(priv->lcd_clk);
		अगर (ret) अणु
			dev_err(dev, "Unable to start lcd clock\n");
			जाओ err_pixclk_disable;
		पूर्ण
	पूर्ण

	/* Set address of our DMA descriptor chain */
	regmap_ग_लिखो(priv->map, JZ_REG_LCD_DA0, dma_hwdesc_phys_f0);
	regmap_ग_लिखो(priv->map, JZ_REG_LCD_DA1, dma_hwdesc_phys_f1);

	/* Enable OSD अगर available */
	अगर (soc_info->has_osd)
		regmap_ग_लिखो(priv->map, JZ_REG_LCD_OSDC, JZ_LCD_OSDC_OSDEN);

	mutex_init(&priv->clk_mutex);
	priv->घड़ी_nb.notअगरier_call = ingenic_drm_update_pixclk;

	parent_clk = clk_get_parent(priv->pix_clk);
	ret = clk_notअगरier_रेजिस्टर(parent_clk, &priv->घड़ी_nb);
	अगर (ret) अणु
		dev_err(dev, "Unable to register clock notifier\n");
		जाओ err_devclk_disable;
	पूर्ण

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret) अणु
		dev_err(dev, "Failed to register DRM driver\n");
		जाओ err_clk_notअगरier_unरेजिस्टर;
	पूर्ण

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

err_clk_notअगरier_unरेजिस्टर:
	clk_notअगरier_unरेजिस्टर(parent_clk, &priv->घड़ी_nb);
err_devclk_disable:
	अगर (priv->lcd_clk)
		clk_disable_unprepare(priv->lcd_clk);
err_pixclk_disable:
	clk_disable_unprepare(priv->pix_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_drm_bind_with_components(काष्ठा device *dev)
अणु
	वापस ingenic_drm_bind(dev, true);
पूर्ण

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल व्योम ingenic_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा ingenic_drm *priv = dev_get_drvdata(dev);
	काष्ठा clk *parent_clk = clk_get_parent(priv->pix_clk);

	clk_notअगरier_unरेजिस्टर(parent_clk, &priv->घड़ी_nb);
	अगर (priv->lcd_clk)
		clk_disable_unprepare(priv->lcd_clk);
	clk_disable_unprepare(priv->pix_clk);

	drm_dev_unरेजिस्टर(&priv->drm);
	drm_atomic_helper_shutकरोwn(&priv->drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops ingenic_master_ops = अणु
	.bind = ingenic_drm_bind_with_components,
	.unbind = ingenic_drm_unbind,
पूर्ण;

अटल पूर्णांक ingenic_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा component_match *match = शून्य;
	काष्ठा device_node *np;

	अगर (!IS_ENABLED(CONFIG_DRM_INGENIC_IPU))
		वापस ingenic_drm_bind(dev, false);

	/* IPU is at port address 8 */
	np = of_graph_get_remote_node(dev->of_node, 8, 0);
	अगर (!np)
		वापस ingenic_drm_bind(dev, false);

	drm_of_component_match_add(dev, &match, compare_of, np);
	of_node_put(np);

	वापस component_master_add_with_match(dev, &ingenic_master_ops, match);
पूर्ण

अटल पूर्णांक ingenic_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	अगर (!IS_ENABLED(CONFIG_DRM_INGENIC_IPU))
		ingenic_drm_unbind(dev);
	अन्यथा
		component_master_del(dev, &ingenic_master_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ingenic_drm *priv = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(&priv->drm);
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा ingenic_drm *priv = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(&priv->drm);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ingenic_drm_pm_ops, ingenic_drm_suspend, ingenic_drm_resume);

अटल स्थिर u32 jz4740_क्रमmats[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर u32 jz4725b_क्रमmats_f1[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर u32 jz4725b_क्रमmats_f0[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर u32 jz4770_क्रमmats_f1[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XRGB2101010,
पूर्ण;

अटल स्थिर u32 jz4770_क्रमmats_f0[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XRGB2101010,
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4740_soc_info = अणु
	.needs_dev_clk = true,
	.has_osd = false,
	.max_width = 800,
	.max_height = 600,
	.क्रमmats_f1 = jz4740_क्रमmats,
	.num_क्रमmats_f1 = ARRAY_SIZE(jz4740_क्रमmats),
	/* JZ4740 has only one plane */
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4725b_soc_info = अणु
	.needs_dev_clk = false,
	.has_osd = true,
	.max_width = 800,
	.max_height = 600,
	.क्रमmats_f1 = jz4725b_क्रमmats_f1,
	.num_क्रमmats_f1 = ARRAY_SIZE(jz4725b_क्रमmats_f1),
	.क्रमmats_f0 = jz4725b_क्रमmats_f0,
	.num_क्रमmats_f0 = ARRAY_SIZE(jz4725b_क्रमmats_f0),
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4770_soc_info = अणु
	.needs_dev_clk = false,
	.has_osd = true,
	.max_width = 1280,
	.max_height = 720,
	.क्रमmats_f1 = jz4770_क्रमmats_f1,
	.num_क्रमmats_f1 = ARRAY_SIZE(jz4770_क्रमmats_f1),
	.क्रमmats_f0 = jz4770_क्रमmats_f0,
	.num_क्रमmats_f0 = ARRAY_SIZE(jz4770_क्रमmats_f0),
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_drm_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-lcd", .data = &jz4740_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4725b-lcd", .data = &jz4725b_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4770-lcd", .data = &jz4770_soc_info पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_drm_of_match);

अटल काष्ठा platक्रमm_driver ingenic_drm_driver = अणु
	.driver = अणु
		.name = "ingenic-drm",
		.pm = pm_ptr(&ingenic_drm_pm_ops),
		.of_match_table = of_match_ptr(ingenic_drm_of_match),
	पूर्ण,
	.probe = ingenic_drm_probe,
	.हटाओ = ingenic_drm_हटाओ,
पूर्ण;

अटल पूर्णांक ingenic_drm_init(व्योम)
अणु
	पूर्णांक err;

	अगर (IS_ENABLED(CONFIG_DRM_INGENIC_IPU)) अणु
		err = platक्रमm_driver_रेजिस्टर(ingenic_ipu_driver_ptr);
		अगर (err)
			वापस err;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&ingenic_drm_driver);
पूर्ण
module_init(ingenic_drm_init);

अटल व्योम ingenic_drm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ingenic_drm_driver);

	अगर (IS_ENABLED(CONFIG_DRM_INGENIC_IPU))
		platक्रमm_driver_unरेजिस्टर(ingenic_ipu_driver_ptr);
पूर्ण
module_निकास(ingenic_drm_निकास);

MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("DRM driver for the Ingenic SoCs\n");
MODULE_LICENSE("GPL v2");
