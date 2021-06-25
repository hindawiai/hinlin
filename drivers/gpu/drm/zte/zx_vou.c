<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "zx_common_regs.h"
#समावेश "zx_drm_drv.h"
#समावेश "zx_plane.h"
#समावेश "zx_vou.h"
#समावेश "zx_vou_regs.h"

#घोषणा GL_NUM	2
#घोषणा VL_NUM	3

क्रमागत vou_chn_type अणु
	VOU_CHN_MAIN,
	VOU_CHN_AUX,
पूर्ण;

काष्ठा zx_crtc_regs अणु
	u32 fir_active;
	u32 fir_htiming;
	u32 fir_vtiming;
	u32 sec_vtiming;
	u32 timing_shअगरt;
	u32 timing_pi_shअगरt;
पूर्ण;

अटल स्थिर काष्ठा zx_crtc_regs मुख्य_crtc_regs = अणु
	.fir_active = FIR_MAIN_ACTIVE,
	.fir_htiming = FIR_MAIN_H_TIMING,
	.fir_vtiming = FIR_MAIN_V_TIMING,
	.sec_vtiming = SEC_MAIN_V_TIMING,
	.timing_shअगरt = TIMING_MAIN_SHIFT,
	.timing_pi_shअगरt = TIMING_MAIN_PI_SHIFT,
पूर्ण;

अटल स्थिर काष्ठा zx_crtc_regs aux_crtc_regs = अणु
	.fir_active = FIR_AUX_ACTIVE,
	.fir_htiming = FIR_AUX_H_TIMING,
	.fir_vtiming = FIR_AUX_V_TIMING,
	.sec_vtiming = SEC_AUX_V_TIMING,
	.timing_shअगरt = TIMING_AUX_SHIFT,
	.timing_pi_shअगरt = TIMING_AUX_PI_SHIFT,
पूर्ण;

काष्ठा zx_crtc_bits अणु
	u32 polarity_mask;
	u32 polarity_shअगरt;
	u32 पूर्णांक_frame_mask;
	u32 tc_enable;
	u32 sec_vactive_shअगरt;
	u32 sec_vactive_mask;
	u32 पूर्णांकerlace_select;
	u32 pi_enable;
	u32 भाग_vga_shअगरt;
	u32 भाग_pic_shअगरt;
	u32 भाग_प्रकारvenc_shअगरt;
	u32 भाग_hdmi_pnx_shअगरt;
	u32 भाग_hdmi_shअगरt;
	u32 भाग_inf_shअगरt;
	u32 भाग_layer_shअगरt;
पूर्ण;

अटल स्थिर काष्ठा zx_crtc_bits मुख्य_crtc_bits = अणु
	.polarity_mask = MAIN_POL_MASK,
	.polarity_shअगरt = MAIN_POL_SHIFT,
	.पूर्णांक_frame_mask = TIMING_INT_MAIN_FRAME,
	.tc_enable = MAIN_TC_EN,
	.sec_vactive_shअगरt = SEC_VACT_MAIN_SHIFT,
	.sec_vactive_mask = SEC_VACT_MAIN_MASK,
	.पूर्णांकerlace_select = MAIN_INTERLACE_SEL,
	.pi_enable = MAIN_PI_EN,
	.भाग_vga_shअगरt = VGA_MAIN_DIV_SHIFT,
	.भाग_pic_shअगरt = PIC_MAIN_DIV_SHIFT,
	.भाग_प्रकारvenc_shअगरt = TVENC_MAIN_DIV_SHIFT,
	.भाग_hdmi_pnx_shअगरt = HDMI_MAIN_PNX_DIV_SHIFT,
	.भाग_hdmi_shअगरt = HDMI_MAIN_DIV_SHIFT,
	.भाग_inf_shअगरt = INF_MAIN_DIV_SHIFT,
	.भाग_layer_shअगरt = LAYER_MAIN_DIV_SHIFT,
पूर्ण;

अटल स्थिर काष्ठा zx_crtc_bits aux_crtc_bits = अणु
	.polarity_mask = AUX_POL_MASK,
	.polarity_shअगरt = AUX_POL_SHIFT,
	.पूर्णांक_frame_mask = TIMING_INT_AUX_FRAME,
	.tc_enable = AUX_TC_EN,
	.sec_vactive_shअगरt = SEC_VACT_AUX_SHIFT,
	.sec_vactive_mask = SEC_VACT_AUX_MASK,
	.पूर्णांकerlace_select = AUX_INTERLACE_SEL,
	.pi_enable = AUX_PI_EN,
	.भाग_vga_shअगरt = VGA_AUX_DIV_SHIFT,
	.भाग_pic_shअगरt = PIC_AUX_DIV_SHIFT,
	.भाग_प्रकारvenc_shअगरt = TVENC_AUX_DIV_SHIFT,
	.भाग_hdmi_pnx_shअगरt = HDMI_AUX_PNX_DIV_SHIFT,
	.भाग_hdmi_shअगरt = HDMI_AUX_DIV_SHIFT,
	.भाग_inf_shअगरt = INF_AUX_DIV_SHIFT,
	.भाग_layer_shअगरt = LAYER_AUX_DIV_SHIFT,
पूर्ण;

काष्ठा zx_crtc अणु
	काष्ठा drm_crtc crtc;
	काष्ठा drm_plane *primary;
	काष्ठा zx_vou_hw *vou;
	व्योम __iomem *chnreg;
	व्योम __iomem *chncsc;
	व्योम __iomem *dither;
	स्थिर काष्ठा zx_crtc_regs *regs;
	स्थिर काष्ठा zx_crtc_bits *bits;
	क्रमागत vou_chn_type chn_type;
	काष्ठा clk *pixclk;
पूर्ण;

#घोषणा to_zx_crtc(x) container_of(x, काष्ठा zx_crtc, crtc)

काष्ठा vou_layer_bits अणु
	u32 enable;
	u32 chnsel;
	u32 clksel;
पूर्ण;

अटल स्थिर काष्ठा vou_layer_bits zx_gl_bits[GL_NUM] = अणु
	अणु
		.enable = OSD_CTRL0_GL0_EN,
		.chnsel = OSD_CTRL0_GL0_SEL,
		.clksel = VOU_CLK_GL0_SEL,
	पूर्ण, अणु
		.enable = OSD_CTRL0_GL1_EN,
		.chnsel = OSD_CTRL0_GL1_SEL,
		.clksel = VOU_CLK_GL1_SEL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vou_layer_bits zx_vl_bits[VL_NUM] = अणु
	अणु
		.enable = OSD_CTRL0_VL0_EN,
		.chnsel = OSD_CTRL0_VL0_SEL,
		.clksel = VOU_CLK_VL0_SEL,
	पूर्ण, अणु
		.enable = OSD_CTRL0_VL1_EN,
		.chnsel = OSD_CTRL0_VL1_SEL,
		.clksel = VOU_CLK_VL1_SEL,
	पूर्ण, अणु
		.enable = OSD_CTRL0_VL2_EN,
		.chnsel = OSD_CTRL0_VL2_SEL,
		.clksel = VOU_CLK_VL2_SEL,
	पूर्ण,
पूर्ण;

काष्ठा zx_vou_hw अणु
	काष्ठा device *dev;
	व्योम __iomem *osd;
	व्योम __iomem *timing;
	व्योम __iomem *vouctl;
	व्योम __iomem *otfppu;
	व्योम __iomem *dtrc;
	काष्ठा clk *axi_clk;
	काष्ठा clk *ppu_clk;
	काष्ठा clk *मुख्य_clk;
	काष्ठा clk *aux_clk;
	काष्ठा zx_crtc *मुख्य_crtc;
	काष्ठा zx_crtc *aux_crtc;
पूर्ण;

क्रमागत vou_inf_data_sel अणु
	VOU_YUV444	= 0,
	VOU_RGB_101010	= 1,
	VOU_RGB_888	= 2,
	VOU_RGB_666	= 3,
पूर्ण;

काष्ठा vou_inf अणु
	क्रमागत vou_inf_id id;
	क्रमागत vou_inf_data_sel data_sel;
	u32 घड़ीs_en_bits;
	u32 घड़ीs_sel_bits;
पूर्ण;

अटल काष्ठा vou_inf vou_infs[] = अणु
	[VOU_HDMI] = अणु
		.data_sel = VOU_YUV444,
		.घड़ीs_en_bits = BIT(24) | BIT(18) | BIT(6),
		.घड़ीs_sel_bits = BIT(13) | BIT(2),
	पूर्ण,
	[VOU_TV_ENC] = अणु
		.data_sel = VOU_YUV444,
		.घड़ीs_en_bits = BIT(15),
		.घड़ीs_sel_bits = BIT(11) | BIT(0),
	पूर्ण,
	[VOU_VGA] = अणु
		.data_sel = VOU_RGB_888,
		.घड़ीs_en_bits = BIT(1),
		.घड़ीs_sel_bits = BIT(10),
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा zx_vou_hw *crtc_to_vou(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);

	वापस zcrtc->vou;
पूर्ण

व्योम vou_inf_hdmi_audio_sel(काष्ठा drm_crtc *crtc,
			    क्रमागत vou_inf_hdmi_audio aud)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;

	zx_ग_लिखोl_mask(vou->vouctl + VOU_INF_HDMI_CTRL, VOU_HDMI_AUD_MASK, aud);
पूर्ण

व्योम vou_inf_enable(क्रमागत vou_inf_id id, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;
	काष्ठा vou_inf *inf = &vou_infs[id];
	व्योम __iomem *dither = zcrtc->dither;
	व्योम __iomem *csc = zcrtc->chncsc;
	bool is_मुख्य = zcrtc->chn_type == VOU_CHN_MAIN;
	u32 data_sel_shअगरt = id << 1;

	अगर (inf->data_sel != VOU_YUV444) अणु
		/* Enable channel CSC क्रम RGB output */
		zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_COV_MODE_MASK,
			       CSC_BT709_IMAGE_YCBCR2RGB << CSC_COV_MODE_SHIFT);
		zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_WORK_ENABLE,
			       CSC_WORK_ENABLE);

		/* Bypass Dither block क्रम RGB output */
		zx_ग_लिखोl_mask(dither + OSD_DITHER_CTRL0, DITHER_BYSPASS,
			       DITHER_BYSPASS);
	पूर्ण अन्यथा अणु
		zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_WORK_ENABLE, 0);
		zx_ग_लिखोl_mask(dither + OSD_DITHER_CTRL0, DITHER_BYSPASS, 0);
	पूर्ण

	/* Select data क्रमmat */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_INF_DATA_SEL, 0x3 << data_sel_shअगरt,
		       inf->data_sel << data_sel_shअगरt);

	/* Select channel */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_INF_CH_SEL, 0x1 << id,
		       zcrtc->chn_type << id);

	/* Select पूर्णांकerface घड़ीs */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_CLK_SEL, inf->घड़ीs_sel_bits,
		       is_मुख्य ? 0 : inf->घड़ीs_sel_bits);

	/* Enable पूर्णांकerface घड़ीs */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_CLK_EN, inf->घड़ीs_en_bits,
		       inf->घड़ीs_en_bits);

	/* Enable the device */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_INF_EN, 1 << id, 1 << id);
पूर्ण

व्योम vou_inf_disable(क्रमागत vou_inf_id id, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zx_vou_hw *vou = crtc_to_vou(crtc);
	काष्ठा vou_inf *inf = &vou_infs[id];

	/* Disable the device */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_INF_EN, 1 << id, 0);

	/* Disable पूर्णांकerface घड़ीs */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_CLK_EN, inf->घड़ीs_en_bits, 0);
पूर्ण

व्योम zx_vou_config_भागiders(काष्ठा drm_crtc *crtc,
			    काष्ठा vou_भाग_config *configs, पूर्णांक num)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;
	स्थिर काष्ठा zx_crtc_bits *bits = zcrtc->bits;
	पूर्णांक i;

	/* Clear update flag bit */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_DIV_PARA, DIV_PARA_UPDATE, 0);

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा vou_भाग_config *cfg = configs + i;
		u32 reg, shअगरt;

		चयन (cfg->id) अणु
		हाल VOU_DIV_VGA:
			reg = VOU_CLK_SEL;
			shअगरt = bits->भाग_vga_shअगरt;
			अवरोध;
		हाल VOU_DIV_PIC:
			reg = VOU_CLK_SEL;
			shअगरt = bits->भाग_pic_shअगरt;
			अवरोध;
		हाल VOU_DIV_TVENC:
			reg = VOU_DIV_PARA;
			shअगरt = bits->भाग_प्रकारvenc_shअगरt;
			अवरोध;
		हाल VOU_DIV_HDMI_PNX:
			reg = VOU_DIV_PARA;
			shअगरt = bits->भाग_hdmi_pnx_shअगरt;
			अवरोध;
		हाल VOU_DIV_HDMI:
			reg = VOU_DIV_PARA;
			shअगरt = bits->भाग_hdmi_shअगरt;
			अवरोध;
		हाल VOU_DIV_INF:
			reg = VOU_DIV_PARA;
			shअगरt = bits->भाग_inf_shअगरt;
			अवरोध;
		हाल VOU_DIV_LAYER:
			reg = VOU_DIV_PARA;
			shअगरt = bits->भाग_layer_shअगरt;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		/* Each भागider occupies 3 bits */
		zx_ग_लिखोl_mask(vou->vouctl + reg, 0x7 << shअगरt,
			       cfg->val << shअगरt);
	पूर्ण

	/* Set update flag bit to get भागiders effected */
	zx_ग_लिखोl_mask(vou->vouctl + VOU_DIV_PARA, DIV_PARA_UPDATE,
		       DIV_PARA_UPDATE);
पूर्ण

अटल अंतरभूत व्योम vou_chn_set_update(काष्ठा zx_crtc *zcrtc)
अणु
	zx_ग_लिखोl(zcrtc->chnreg + CHN_UPDATE, 1);
पूर्ण

अटल व्योम zx_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	bool पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;
	स्थिर काष्ठा zx_crtc_regs *regs = zcrtc->regs;
	स्थिर काष्ठा zx_crtc_bits *bits = zcrtc->bits;
	काष्ठा videomode vm;
	u32 scan_mask;
	u32 pol = 0;
	u32 val;
	पूर्णांक ret;

	drm_display_mode_to_videomode(mode, &vm);

	/* Set up timing parameters */
	val = V_ACTIVE((पूर्णांकerlaced ? vm.vactive / 2 : vm.vactive) - 1);
	val |= H_ACTIVE(vm.hactive - 1);
	zx_ग_लिखोl(vou->timing + regs->fir_active, val);

	val = SYNC_WIDE(vm.hsync_len - 1);
	val |= BACK_PORCH(vm.hback_porch - 1);
	val |= FRONT_PORCH(vm.hfront_porch - 1);
	zx_ग_लिखोl(vou->timing + regs->fir_htiming, val);

	val = SYNC_WIDE(vm.vsync_len - 1);
	val |= BACK_PORCH(vm.vback_porch - 1);
	val |= FRONT_PORCH(vm.vfront_porch - 1);
	zx_ग_लिखोl(vou->timing + regs->fir_vtiming, val);

	अगर (पूर्णांकerlaced) अणु
		u32 shअगरt = bits->sec_vactive_shअगरt;
		u32 mask = bits->sec_vactive_mask;

		val = zx_पढ़ोl(vou->timing + SEC_V_ACTIVE);
		val &= ~mask;
		val |= ((vm.vactive / 2 - 1) << shअगरt) & mask;
		zx_ग_लिखोl(vou->timing + SEC_V_ACTIVE, val);

		val = SYNC_WIDE(vm.vsync_len - 1);
		/*
		 * The vback_porch क्रम the second field needs to shअगरt one on
		 * the value क्रम the first field.
		 */
		val |= BACK_PORCH(vm.vback_porch);
		val |= FRONT_PORCH(vm.vfront_porch - 1);
		zx_ग_लिखोl(vou->timing + regs->sec_vtiming, val);
	पूर्ण

	/* Set up polarities */
	अगर (vm.flags & DISPLAY_FLAGS_VSYNC_LOW)
		pol |= 1 << POL_VSYNC_SHIFT;
	अगर (vm.flags & DISPLAY_FLAGS_HSYNC_LOW)
		pol |= 1 << POL_HSYNC_SHIFT;

	zx_ग_लिखोl_mask(vou->timing + TIMING_CTRL, bits->polarity_mask,
		       pol << bits->polarity_shअगरt);

	/* Setup SHIFT रेजिस्टर by following what ZTE BSP करोes */
	val = H_SHIFT_VAL;
	अगर (पूर्णांकerlaced)
		val |= V_SHIFT_VAL << 16;
	zx_ग_लिखोl(vou->timing + regs->timing_shअगरt, val);
	zx_ग_लिखोl(vou->timing + regs->timing_pi_shअगरt, H_PI_SHIFT_VAL);

	/* Progressive or पूर्णांकerlace scan select */
	scan_mask = bits->पूर्णांकerlace_select | bits->pi_enable;
	zx_ग_लिखोl_mask(vou->timing + SCAN_CTRL, scan_mask,
		       पूर्णांकerlaced ? scan_mask : 0);

	/* Enable TIMING_CTRL */
	zx_ग_लिखोl_mask(vou->timing + TIMING_TC_ENABLE, bits->tc_enable,
		       bits->tc_enable);

	/* Configure channel screen size */
	zx_ग_लिखोl_mask(zcrtc->chnreg + CHN_CTRL1, CHN_SCREEN_W_MASK,
		       vm.hactive << CHN_SCREEN_W_SHIFT);
	zx_ग_लिखोl_mask(zcrtc->chnreg + CHN_CTRL1, CHN_SCREEN_H_MASK,
		       vm.vactive << CHN_SCREEN_H_SHIFT);

	/* Configure channel पूर्णांकerlace buffer control */
	zx_ग_लिखोl_mask(zcrtc->chnreg + CHN_INTERLACE_BUF_CTRL, CHN_INTERLACE_EN,
		       पूर्णांकerlaced ? CHN_INTERLACE_EN : 0);

	/* Update channel */
	vou_chn_set_update(zcrtc);

	/* Enable channel */
	zx_ग_लिखोl_mask(zcrtc->chnreg + CHN_CTRL0, CHN_ENABLE, CHN_ENABLE);

	drm_crtc_vblank_on(crtc);

	ret = clk_set_rate(zcrtc->pixclk, mode->घड़ी * 1000);
	अगर (ret) अणु
		DRM_DEV_ERROR(vou->dev, "failed to set pixclk rate: %d\n", ret);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(zcrtc->pixclk);
	अगर (ret)
		DRM_DEV_ERROR(vou->dev, "failed to enable pixclk: %d\n", ret);
पूर्ण

अटल व्योम zx_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	स्थिर काष्ठा zx_crtc_bits *bits = zcrtc->bits;
	काष्ठा zx_vou_hw *vou = zcrtc->vou;

	clk_disable_unprepare(zcrtc->pixclk);

	drm_crtc_vblank_off(crtc);

	/* Disable channel */
	zx_ग_लिखोl_mask(zcrtc->chnreg + CHN_CTRL0, CHN_ENABLE, 0);

	/* Disable TIMING_CTRL */
	zx_ग_लिखोl_mask(vou->timing + TIMING_TC_ENABLE, bits->tc_enable, 0);
पूर्ण

अटल व्योम zx_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	अगर (!event)
		वापस;

	crtc->state->event = शून्य;

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (drm_crtc_vblank_get(crtc) == 0)
		drm_crtc_arm_vblank_event(crtc, event);
	अन्यथा
		drm_crtc_send_vblank_event(crtc, event);
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs zx_crtc_helper_funcs = अणु
	.atomic_flush = zx_crtc_atomic_flush,
	.atomic_enable = zx_crtc_atomic_enable,
	.atomic_disable = zx_crtc_atomic_disable,
पूर्ण;

अटल पूर्णांक zx_vou_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = crtc_to_vou(crtc);
	u32 पूर्णांक_frame_mask = zcrtc->bits->पूर्णांक_frame_mask;

	zx_ग_लिखोl_mask(vou->timing + TIMING_INT_CTRL, पूर्णांक_frame_mask,
		       पूर्णांक_frame_mask);

	वापस 0;
पूर्ण

अटल व्योम zx_vou_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(crtc);
	काष्ठा zx_vou_hw *vou = crtc_to_vou(crtc);

	zx_ग_लिखोl_mask(vou->timing + TIMING_INT_CTRL,
		       zcrtc->bits->पूर्णांक_frame_mask, 0);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs zx_crtc_funcs = अणु
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = zx_vou_enable_vblank,
	.disable_vblank = zx_vou_disable_vblank,
पूर्ण;

अटल पूर्णांक zx_crtc_init(काष्ठा drm_device *drm, काष्ठा zx_vou_hw *vou,
			क्रमागत vou_chn_type chn_type)
अणु
	काष्ठा device *dev = vou->dev;
	काष्ठा zx_plane *zplane;
	काष्ठा zx_crtc *zcrtc;
	पूर्णांक ret;

	zcrtc = devm_kzalloc(dev, माप(*zcrtc), GFP_KERNEL);
	अगर (!zcrtc)
		वापस -ENOMEM;

	zcrtc->vou = vou;
	zcrtc->chn_type = chn_type;

	zplane = devm_kzalloc(dev, माप(*zplane), GFP_KERNEL);
	अगर (!zplane)
		वापस -ENOMEM;

	zplane->dev = dev;

	अगर (chn_type == VOU_CHN_MAIN) अणु
		zplane->layer = vou->osd + MAIN_GL_OFFSET;
		zplane->csc = vou->osd + MAIN_GL_CSC_OFFSET;
		zplane->hbsc = vou->osd + MAIN_HBSC_OFFSET;
		zplane->rsz = vou->otfppu + MAIN_RSZ_OFFSET;
		zplane->bits = &zx_gl_bits[0];
		zcrtc->chnreg = vou->osd + OSD_MAIN_CHN;
		zcrtc->chncsc = vou->osd + MAIN_CHN_CSC_OFFSET;
		zcrtc->dither = vou->osd + MAIN_DITHER_OFFSET;
		zcrtc->regs = &मुख्य_crtc_regs;
		zcrtc->bits = &मुख्य_crtc_bits;
	पूर्ण अन्यथा अणु
		zplane->layer = vou->osd + AUX_GL_OFFSET;
		zplane->csc = vou->osd + AUX_GL_CSC_OFFSET;
		zplane->hbsc = vou->osd + AUX_HBSC_OFFSET;
		zplane->rsz = vou->otfppu + AUX_RSZ_OFFSET;
		zplane->bits = &zx_gl_bits[1];
		zcrtc->chnreg = vou->osd + OSD_AUX_CHN;
		zcrtc->chncsc = vou->osd + AUX_CHN_CSC_OFFSET;
		zcrtc->dither = vou->osd + AUX_DITHER_OFFSET;
		zcrtc->regs = &aux_crtc_regs;
		zcrtc->bits = &aux_crtc_bits;
	पूर्ण

	zcrtc->pixclk = devm_clk_get(dev, (chn_type == VOU_CHN_MAIN) ?
					  "main_wclk" : "aux_wclk");
	अगर (IS_ERR(zcrtc->pixclk)) अणु
		ret = PTR_ERR(zcrtc->pixclk);
		DRM_DEV_ERROR(dev, "failed to get pix clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_plane_init(drm, zplane, DRM_PLANE_TYPE_PRIMARY);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init primary plane: %d\n", ret);
		वापस ret;
	पूर्ण

	zcrtc->primary = &zplane->plane;

	ret = drm_crtc_init_with_planes(drm, &zcrtc->crtc, zcrtc->primary, शून्य,
					&zx_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init drm crtc: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(&zcrtc->crtc, &zx_crtc_helper_funcs);

	अगर (chn_type == VOU_CHN_MAIN)
		vou->मुख्य_crtc = zcrtc;
	अन्यथा
		vou->aux_crtc = zcrtc;

	वापस 0;
पूर्ण

व्योम zx_vou_layer_enable(काष्ठा drm_plane *plane)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(plane->state->crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;
	काष्ठा zx_plane *zplane = to_zx_plane(plane);
	स्थिर काष्ठा vou_layer_bits *bits = zplane->bits;

	अगर (zcrtc->chn_type == VOU_CHN_MAIN) अणु
		zx_ग_लिखोl_mask(vou->osd + OSD_CTRL0, bits->chnsel, 0);
		zx_ग_लिखोl_mask(vou->vouctl + VOU_CLK_SEL, bits->clksel, 0);
	पूर्ण अन्यथा अणु
		zx_ग_लिखोl_mask(vou->osd + OSD_CTRL0, bits->chnsel,
			       bits->chnsel);
		zx_ग_लिखोl_mask(vou->vouctl + VOU_CLK_SEL, bits->clksel,
			       bits->clksel);
	पूर्ण

	zx_ग_लिखोl_mask(vou->osd + OSD_CTRL0, bits->enable, bits->enable);
पूर्ण

व्योम zx_vou_layer_disable(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा zx_crtc *zcrtc = to_zx_crtc(old_state->crtc);
	काष्ठा zx_vou_hw *vou = zcrtc->vou;
	काष्ठा zx_plane *zplane = to_zx_plane(plane);
	स्थिर काष्ठा vou_layer_bits *bits = zplane->bits;

	zx_ग_लिखोl_mask(vou->osd + OSD_CTRL0, bits->enable, 0);
पूर्ण

अटल व्योम zx_overlay_init(काष्ठा drm_device *drm, काष्ठा zx_vou_hw *vou)
अणु
	काष्ठा device *dev = vou->dev;
	काष्ठा zx_plane *zplane;
	पूर्णांक i;
	पूर्णांक ret;

	/*
	 * VL0 has some quirks on scaling support which need special handling.
	 * Let's leave it out क्रम now.
	 */
	क्रम (i = 1; i < VL_NUM; i++) अणु
		zplane = devm_kzalloc(dev, माप(*zplane), GFP_KERNEL);
		अगर (!zplane) अणु
			DRM_DEV_ERROR(dev, "failed to allocate zplane %d\n", i);
			वापस;
		पूर्ण

		zplane->layer = vou->osd + OSD_VL_OFFSET(i);
		zplane->hbsc = vou->osd + HBSC_VL_OFFSET(i);
		zplane->rsz = vou->otfppu + RSZ_VL_OFFSET(i);
		zplane->bits = &zx_vl_bits[i];

		ret = zx_plane_init(drm, zplane, DRM_PLANE_TYPE_OVERLAY);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "failed to init overlay %d\n", i);
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम zx_osd_पूर्णांक_update(काष्ठा zx_crtc *zcrtc)
अणु
	काष्ठा drm_crtc *crtc = &zcrtc->crtc;
	काष्ठा drm_plane *plane;

	vou_chn_set_update(zcrtc);

	drm_क्रम_each_plane_mask(plane, crtc->dev, crtc->state->plane_mask)
		zx_plane_set_update(plane);
पूर्ण

अटल irqवापस_t vou_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zx_vou_hw *vou = dev_id;
	u32 state;

	/* Handle TIMING_CTRL frame पूर्णांकerrupts */
	state = zx_पढ़ोl(vou->timing + TIMING_INT_STATE);
	zx_ग_लिखोl(vou->timing + TIMING_INT_STATE, state);

	अगर (state & TIMING_INT_MAIN_FRAME)
		drm_crtc_handle_vblank(&vou->मुख्य_crtc->crtc);

	अगर (state & TIMING_INT_AUX_FRAME)
		drm_crtc_handle_vblank(&vou->aux_crtc->crtc);

	/* Handle OSD पूर्णांकerrupts */
	state = zx_पढ़ोl(vou->osd + OSD_INT_STA);
	zx_ग_लिखोl(vou->osd + OSD_INT_CLRSTA, state);

	अगर (state & OSD_INT_MAIN_UPT)
		zx_osd_पूर्णांक_update(vou->मुख्य_crtc);

	अगर (state & OSD_INT_AUX_UPT)
		zx_osd_पूर्णांक_update(vou->aux_crtc);

	अगर (state & OSD_INT_ERROR)
		DRM_DEV_ERROR(vou->dev, "OSD ERROR: 0x%08x!\n", state);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vou_dtrc_init(काष्ठा zx_vou_hw *vou)
अणु
	/* Clear bit क्रम bypass by ID */
	zx_ग_लिखोl_mask(vou->dtrc + DTRC_DETILE_CTRL,
		       TILE2RASTESCAN_BYPASS_MODE, 0);

	/* Select ARIDR mode */
	zx_ग_लिखोl_mask(vou->dtrc + DTRC_DETILE_CTRL, DETILE_ARIDR_MODE_MASK,
		       DETILE_ARID_IN_ARIDR);

	/* Bypass decompression क्रम both frames */
	zx_ग_लिखोl_mask(vou->dtrc + DTRC_F0_CTRL, DTRC_DECOMPRESS_BYPASS,
		       DTRC_DECOMPRESS_BYPASS);
	zx_ग_लिखोl_mask(vou->dtrc + DTRC_F1_CTRL, DTRC_DECOMPRESS_BYPASS,
		       DTRC_DECOMPRESS_BYPASS);

	/* Set up ARID रेजिस्टर */
	zx_ग_लिखोl(vou->dtrc + DTRC_ARID, DTRC_ARID3(0xf) | DTRC_ARID2(0xe) |
		  DTRC_ARID1(0xf) | DTRC_ARID0(0xe));
पूर्ण

अटल व्योम vou_hw_init(काष्ठा zx_vou_hw *vou)
अणु
	/* Release reset क्रम all VOU modules */
	zx_ग_लिखोl(vou->vouctl + VOU_SOFT_RST, ~0);

	/* Enable all VOU module घड़ीs */
	zx_ग_लिखोl(vou->vouctl + VOU_CLK_EN, ~0);

	/* Clear both OSD and TIMING_CTRL पूर्णांकerrupt state */
	zx_ग_लिखोl(vou->osd + OSD_INT_CLRSTA, ~0);
	zx_ग_लिखोl(vou->timing + TIMING_INT_STATE, ~0);

	/* Enable OSD and TIMING_CTRL पूर्णांकerrrupts */
	zx_ग_लिखोl(vou->osd + OSD_INT_MSK, OSD_INT_ENABLE);
	zx_ग_लिखोl(vou->timing + TIMING_INT_CTRL, TIMING_INT_ENABLE);

	/* Select GPC as input to gl/vl scaler as a sane शेष setting */
	zx_ग_लिखोl(vou->otfppu + OTFPPU_RSZ_DATA_SOURCE, 0x2a);

	/*
	 * Needs to reset channel and layer logic per frame when frame starts
	 * to get VOU work properly.
	 */
	zx_ग_लिखोl_mask(vou->osd + OSD_RST_CLR, RST_PER_FRAME, RST_PER_FRAME);

	vou_dtrc_init(vou);
पूर्ण

अटल पूर्णांक zx_crtc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा zx_vou_hw *vou;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	vou = devm_kzalloc(dev, माप(*vou), GFP_KERNEL);
	अगर (!vou)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "osd");
	vou->osd = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vou->osd)) अणु
		ret = PTR_ERR(vou->osd);
		DRM_DEV_ERROR(dev, "failed to remap osd region: %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "timing_ctrl");
	vou->timing = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vou->timing)) अणु
		ret = PTR_ERR(vou->timing);
		DRM_DEV_ERROR(dev, "failed to remap timing_ctrl region: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dtrc");
	vou->dtrc = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vou->dtrc)) अणु
		ret = PTR_ERR(vou->dtrc);
		DRM_DEV_ERROR(dev, "failed to remap dtrc region: %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "vou_ctrl");
	vou->vouctl = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vou->vouctl)) अणु
		ret = PTR_ERR(vou->vouctl);
		DRM_DEV_ERROR(dev, "failed to remap vou_ctrl region: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "otfppu");
	vou->otfppu = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vou->otfppu)) अणु
		ret = PTR_ERR(vou->otfppu);
		DRM_DEV_ERROR(dev, "failed to remap otfppu region: %d\n", ret);
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	vou->axi_clk = devm_clk_get(dev, "aclk");
	अगर (IS_ERR(vou->axi_clk)) अणु
		ret = PTR_ERR(vou->axi_clk);
		DRM_DEV_ERROR(dev, "failed to get axi_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	vou->ppu_clk = devm_clk_get(dev, "ppu_wclk");
	अगर (IS_ERR(vou->ppu_clk)) अणु
		ret = PTR_ERR(vou->ppu_clk);
		DRM_DEV_ERROR(dev, "failed to get ppu_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(vou->axi_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to enable axi_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	clk_prepare_enable(vou->ppu_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to enable ppu_clk: %d\n", ret);
		जाओ disable_axi_clk;
	पूर्ण

	vou->dev = dev;
	dev_set_drvdata(dev, vou);

	vou_hw_init(vou);

	ret = devm_request_irq(dev, irq, vou_irq_handler, 0, "zx_vou", vou);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "failed to request vou irq: %d\n", ret);
		जाओ disable_ppu_clk;
	पूर्ण

	ret = zx_crtc_init(drm, vou, VOU_CHN_MAIN);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init main channel crtc: %d\n",
			      ret);
		जाओ disable_ppu_clk;
	पूर्ण

	ret = zx_crtc_init(drm, vou, VOU_CHN_AUX);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init aux channel crtc: %d\n",
			      ret);
		जाओ disable_ppu_clk;
	पूर्ण

	zx_overlay_init(drm, vou);

	वापस 0;

disable_ppu_clk:
	clk_disable_unprepare(vou->ppu_clk);
disable_axi_clk:
	clk_disable_unprepare(vou->axi_clk);
	वापस ret;
पूर्ण

अटल व्योम zx_crtc_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा zx_vou_hw *vou = dev_get_drvdata(dev);

	clk_disable_unprepare(vou->axi_clk);
	clk_disable_unprepare(vou->ppu_clk);
पूर्ण

अटल स्थिर काष्ठा component_ops zx_crtc_component_ops = अणु
	.bind = zx_crtc_bind,
	.unbind = zx_crtc_unbind,
पूर्ण;

अटल पूर्णांक zx_crtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &zx_crtc_component_ops);
पूर्ण

अटल पूर्णांक zx_crtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &zx_crtc_component_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zx_crtc_of_match[] = अणु
	अणु .compatible = "zte,zx296718-dpc", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zx_crtc_of_match);

काष्ठा platक्रमm_driver zx_crtc_driver = अणु
	.probe = zx_crtc_probe,
	.हटाओ = zx_crtc_हटाओ,
	.driver	= अणु
		.name = "zx-crtc",
		.of_match_table	= zx_crtc_of_match,
	पूर्ण,
पूर्ण;
