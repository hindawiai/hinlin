<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Broadcom
 */

/**
 * DOC: VC4 SDTV module
 *
 * The VEC encoder generates PAL or NTSC composite video output.
 *
 * TV mode selection is करोne by an atomic property on the encoder,
 * because a drm_mode_modeinfo is insufficient to distinguish between
 * PAL and PAL-M or NTSC and NTSC-J.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

/* WSE Registers */
#घोषणा VEC_WSE_RESET			0xc0

#घोषणा VEC_WSE_CONTROL			0xc4
#घोषणा VEC_WSE_WSS_ENABLE		BIT(7)

#घोषणा VEC_WSE_WSS_DATA		0xc8
#घोषणा VEC_WSE_VPS_DATA1		0xcc
#घोषणा VEC_WSE_VPS_CONTROL		0xd0

/* VEC Registers */
#घोषणा VEC_REVID			0x100

#घोषणा VEC_CONFIG0			0x104
#घोषणा VEC_CONFIG0_YDEL_MASK		GENMASK(28, 26)
#घोषणा VEC_CONFIG0_YDEL(x)		((x) << 26)
#घोषणा VEC_CONFIG0_CDEL_MASK		GENMASK(25, 24)
#घोषणा VEC_CONFIG0_CDEL(x)		((x) << 24)
#घोषणा VEC_CONFIG0_PBPR_FIL		BIT(18)
#घोषणा VEC_CONFIG0_CHROMA_GAIN_MASK	GENMASK(17, 16)
#घोषणा VEC_CONFIG0_CHROMA_GAIN_UNITY	(0 << 16)
#घोषणा VEC_CONFIG0_CHROMA_GAIN_1_32	(1 << 16)
#घोषणा VEC_CONFIG0_CHROMA_GAIN_1_16	(2 << 16)
#घोषणा VEC_CONFIG0_CHROMA_GAIN_1_8	(3 << 16)
#घोषणा VEC_CONFIG0_CBURST_GAIN_MASK	GENMASK(14, 13)
#घोषणा VEC_CONFIG0_CBURST_GAIN_UNITY	(0 << 13)
#घोषणा VEC_CONFIG0_CBURST_GAIN_1_128	(1 << 13)
#घोषणा VEC_CONFIG0_CBURST_GAIN_1_64	(2 << 13)
#घोषणा VEC_CONFIG0_CBURST_GAIN_1_32	(3 << 13)
#घोषणा VEC_CONFIG0_CHRBW1		BIT(11)
#घोषणा VEC_CONFIG0_CHRBW0		BIT(10)
#घोषणा VEC_CONFIG0_SYNCDIS		BIT(9)
#घोषणा VEC_CONFIG0_BURDIS		BIT(8)
#घोषणा VEC_CONFIG0_CHRDIS		BIT(7)
#घोषणा VEC_CONFIG0_PDEN		BIT(6)
#घोषणा VEC_CONFIG0_YCDELAY		BIT(4)
#घोषणा VEC_CONFIG0_RAMPEN		BIT(2)
#घोषणा VEC_CONFIG0_YCDIS		BIT(2)
#घोषणा VEC_CONFIG0_STD_MASK		GENMASK(1, 0)
#घोषणा VEC_CONFIG0_NTSC_STD		0
#घोषणा VEC_CONFIG0_PAL_BDGHI_STD	1
#घोषणा VEC_CONFIG0_PAL_N_STD		3

#घोषणा VEC_SCHPH			0x108
#घोषणा VEC_SOFT_RESET			0x10c
#घोषणा VEC_CLMP0_START			0x144
#घोषणा VEC_CLMP0_END			0x148
#घोषणा VEC_FREQ3_2			0x180
#घोषणा VEC_FREQ1_0			0x184

#घोषणा VEC_CONFIG1			0x188
#घोषणा VEC_CONFIG_VEC_RESYNC_OFF	BIT(18)
#घोषणा VEC_CONFIG_RGB219		BIT(17)
#घोषणा VEC_CONFIG_CBAR_EN		BIT(16)
#घोषणा VEC_CONFIG_TC_OBB		BIT(15)
#घोषणा VEC_CONFIG1_OUTPUT_MODE_MASK	GENMASK(12, 10)
#घोषणा VEC_CONFIG1_C_Y_CVBS		(0 << 10)
#घोषणा VEC_CONFIG1_CVBS_Y_C		(1 << 10)
#घोषणा VEC_CONFIG1_PR_Y_PB		(2 << 10)
#घोषणा VEC_CONFIG1_RGB			(4 << 10)
#घोषणा VEC_CONFIG1_Y_C_CVBS		(5 << 10)
#घोषणा VEC_CONFIG1_C_CVBS_Y		(6 << 10)
#घोषणा VEC_CONFIG1_C_CVBS_CVBS		(7 << 10)
#घोषणा VEC_CONFIG1_DIS_CHR		BIT(9)
#घोषणा VEC_CONFIG1_DIS_LUMA		BIT(8)
#घोषणा VEC_CONFIG1_YCBCR_IN		BIT(6)
#घोषणा VEC_CONFIG1_DITHER_TYPE_LFSR	0
#घोषणा VEC_CONFIG1_DITHER_TYPE_COUNTER	BIT(5)
#घोषणा VEC_CONFIG1_DITHER_EN		BIT(4)
#घोषणा VEC_CONFIG1_CYDELAY		BIT(3)
#घोषणा VEC_CONFIG1_LUMADIS		BIT(2)
#घोषणा VEC_CONFIG1_COMPDIS		BIT(1)
#घोषणा VEC_CONFIG1_CUSTOM_FREQ		BIT(0)

#घोषणा VEC_CONFIG2			0x18c
#घोषणा VEC_CONFIG2_PROG_SCAN		BIT(15)
#घोषणा VEC_CONFIG2_SYNC_ADJ_MASK	GENMASK(14, 12)
#घोषणा VEC_CONFIG2_SYNC_ADJ(x)		(((x) / 2) << 12)
#घोषणा VEC_CONFIG2_PBPR_EN		BIT(10)
#घोषणा VEC_CONFIG2_UV_DIG_DIS		BIT(6)
#घोषणा VEC_CONFIG2_RGB_DIG_DIS		BIT(5)
#घोषणा VEC_CONFIG2_TMUX_MASK		GENMASK(3, 2)
#घोषणा VEC_CONFIG2_TMUX_DRIVE0		(0 << 2)
#घोषणा VEC_CONFIG2_TMUX_RG_COMP	(1 << 2)
#घोषणा VEC_CONFIG2_TMUX_UV_YC		(2 << 2)
#घोषणा VEC_CONFIG2_TMUX_SYNC_YC	(3 << 2)

#घोषणा VEC_INTERRUPT_CONTROL		0x190
#घोषणा VEC_INTERRUPT_STATUS		0x194
#घोषणा VEC_FCW_SECAM_B			0x198
#घोषणा VEC_SECAM_GAIN_VAL		0x19c

#घोषणा VEC_CONFIG3			0x1a0
#घोषणा VEC_CONFIG3_HORIZ_LEN_STD	(0 << 0)
#घोषणा VEC_CONFIG3_HORIZ_LEN_MPEG1_SIF	(1 << 0)
#घोषणा VEC_CONFIG3_SHAPE_NON_LINEAR	BIT(1)

#घोषणा VEC_STATUS0			0x200
#घोषणा VEC_MASK0			0x204

#घोषणा VEC_CFG				0x208
#घोषणा VEC_CFG_SG_MODE_MASK		GENMASK(6, 5)
#घोषणा VEC_CFG_SG_MODE(x)		((x) << 5)
#घोषणा VEC_CFG_SG_EN			BIT(4)
#घोषणा VEC_CFG_VEC_EN			BIT(3)
#घोषणा VEC_CFG_MB_EN			BIT(2)
#घोषणा VEC_CFG_ENABLE			BIT(1)
#घोषणा VEC_CFG_TB_EN			BIT(0)

#घोषणा VEC_DAC_TEST			0x20c

#घोषणा VEC_DAC_CONFIG			0x210
#घोषणा VEC_DAC_CONFIG_LDO_BIAS_CTRL(x)	((x) << 24)
#घोषणा VEC_DAC_CONFIG_DRIVER_CTRL(x)	((x) << 16)
#घोषणा VEC_DAC_CONFIG_DAC_CTRL(x)	(x)

#घोषणा VEC_DAC_MISC			0x214
#घोषणा VEC_DAC_MISC_VCD_CTRL_MASK	GENMASK(31, 16)
#घोषणा VEC_DAC_MISC_VCD_CTRL(x)	((x) << 16)
#घोषणा VEC_DAC_MISC_VID_ACT		BIT(8)
#घोषणा VEC_DAC_MISC_VCD_PWRDN		BIT(6)
#घोषणा VEC_DAC_MISC_BIAS_PWRDN		BIT(5)
#घोषणा VEC_DAC_MISC_DAC_PWRDN		BIT(2)
#घोषणा VEC_DAC_MISC_LDO_PWRDN		BIT(1)
#घोषणा VEC_DAC_MISC_DAC_RST_N		BIT(0)


/* General VEC hardware state. */
काष्ठा vc4_vec अणु
	काष्ठा platक्रमm_device *pdev;

	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;

	व्योम __iomem *regs;

	काष्ठा clk *घड़ी;

	स्थिर काष्ठा vc4_vec_tv_mode *tv_mode;

	काष्ठा debugfs_regset32 regset;
पूर्ण;

#घोषणा VEC_READ(offset) पढ़ोl(vec->regs + (offset))
#घोषणा VEC_WRITE(offset, val) ग_लिखोl(val, vec->regs + (offset))

/* VC4 VEC encoder KMS काष्ठा */
काष्ठा vc4_vec_encoder अणु
	काष्ठा vc4_encoder base;
	काष्ठा vc4_vec *vec;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_vec_encoder *
to_vc4_vec_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_vec_encoder, base.base);
पूर्ण

/* VC4 VEC connector KMS काष्ठा */
काष्ठा vc4_vec_connector अणु
	काष्ठा drm_connector base;
	काष्ठा vc4_vec *vec;

	/* Since the connector is attached to just the one encoder,
	 * this is the reference to it so we can करो the best_encoder()
	 * hook.
	 */
	काष्ठा drm_encoder *encoder;
पूर्ण;

क्रमागत vc4_vec_tv_mode_id अणु
	VC4_VEC_TV_MODE_NTSC,
	VC4_VEC_TV_MODE_NTSC_J,
	VC4_VEC_TV_MODE_PAL,
	VC4_VEC_TV_MODE_PAL_M,
पूर्ण;

काष्ठा vc4_vec_tv_mode अणु
	स्थिर काष्ठा drm_display_mode *mode;
	व्योम (*mode_set)(काष्ठा vc4_vec *vec);
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 vec_regs[] = अणु
	VC4_REG32(VEC_WSE_CONTROL),
	VC4_REG32(VEC_WSE_WSS_DATA),
	VC4_REG32(VEC_WSE_VPS_DATA1),
	VC4_REG32(VEC_WSE_VPS_CONTROL),
	VC4_REG32(VEC_REVID),
	VC4_REG32(VEC_CONFIG0),
	VC4_REG32(VEC_SCHPH),
	VC4_REG32(VEC_CLMP0_START),
	VC4_REG32(VEC_CLMP0_END),
	VC4_REG32(VEC_FREQ3_2),
	VC4_REG32(VEC_FREQ1_0),
	VC4_REG32(VEC_CONFIG1),
	VC4_REG32(VEC_CONFIG2),
	VC4_REG32(VEC_INTERRUPT_CONTROL),
	VC4_REG32(VEC_INTERRUPT_STATUS),
	VC4_REG32(VEC_FCW_SECAM_B),
	VC4_REG32(VEC_SECAM_GAIN_VAL),
	VC4_REG32(VEC_CONFIG3),
	VC4_REG32(VEC_STATUS0),
	VC4_REG32(VEC_MASK0),
	VC4_REG32(VEC_CFG),
	VC4_REG32(VEC_DAC_TEST),
	VC4_REG32(VEC_DAC_CONFIG),
	VC4_REG32(VEC_DAC_MISC),
पूर्ण;

अटल व्योम vc4_vec_ntsc_mode_set(काष्ठा vc4_vec *vec)
अणु
	VEC_WRITE(VEC_CONFIG0, VEC_CONFIG0_NTSC_STD | VEC_CONFIG0_PDEN);
	VEC_WRITE(VEC_CONFIG1, VEC_CONFIG1_C_CVBS_CVBS);
पूर्ण

अटल व्योम vc4_vec_ntsc_j_mode_set(काष्ठा vc4_vec *vec)
अणु
	VEC_WRITE(VEC_CONFIG0, VEC_CONFIG0_NTSC_STD);
	VEC_WRITE(VEC_CONFIG1, VEC_CONFIG1_C_CVBS_CVBS);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode ntsc_mode = अणु
	DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 13500,
		 720, 720 + 14, 720 + 14 + 64, 720 + 14 + 64 + 60, 0,
		 480, 480 + 3, 480 + 3 + 3, 480 + 3 + 3 + 16, 0,
		 DRM_MODE_FLAG_INTERLACE)
पूर्ण;

अटल व्योम vc4_vec_pal_mode_set(काष्ठा vc4_vec *vec)
अणु
	VEC_WRITE(VEC_CONFIG0, VEC_CONFIG0_PAL_BDGHI_STD);
	VEC_WRITE(VEC_CONFIG1, VEC_CONFIG1_C_CVBS_CVBS);
पूर्ण

अटल व्योम vc4_vec_pal_m_mode_set(काष्ठा vc4_vec *vec)
अणु
	VEC_WRITE(VEC_CONFIG0, VEC_CONFIG0_PAL_BDGHI_STD);
	VEC_WRITE(VEC_CONFIG1,
		  VEC_CONFIG1_C_CVBS_CVBS | VEC_CONFIG1_CUSTOM_FREQ);
	VEC_WRITE(VEC_FREQ3_2, 0x223b);
	VEC_WRITE(VEC_FREQ1_0, 0x61d1);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode pal_mode = अणु
	DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 13500,
		 720, 720 + 20, 720 + 20 + 64, 720 + 20 + 64 + 60, 0,
		 576, 576 + 2, 576 + 2 + 3, 576 + 2 + 3 + 20, 0,
		 DRM_MODE_FLAG_INTERLACE)
पूर्ण;

अटल स्थिर काष्ठा vc4_vec_tv_mode vc4_vec_tv_modes[] = अणु
	[VC4_VEC_TV_MODE_NTSC] = अणु
		.mode = &ntsc_mode,
		.mode_set = vc4_vec_ntsc_mode_set,
	पूर्ण,
	[VC4_VEC_TV_MODE_NTSC_J] = अणु
		.mode = &ntsc_mode,
		.mode_set = vc4_vec_ntsc_j_mode_set,
	पूर्ण,
	[VC4_VEC_TV_MODE_PAL] = अणु
		.mode = &pal_mode,
		.mode_set = vc4_vec_pal_mode_set,
	पूर्ण,
	[VC4_VEC_TV_MODE_PAL_M] = अणु
		.mode = &pal_mode,
		.mode_set = vc4_vec_pal_m_mode_set,
	पूर्ण,
पूर्ण;

अटल क्रमागत drm_connector_status
vc4_vec_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector_status_unknown;
पूर्ण

अटल व्योम vc4_vec_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल पूर्णांक vc4_vec_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_connector_state *state = connector->state;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev,
				  vc4_vec_tv_modes[state->tv.mode].mode);
	अगर (!mode) अणु
		DRM_ERROR("Failed to create a new display mode\n");
		वापस -ENOMEM;
	पूर्ण

	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vc4_vec_connector_funcs = अणु
	.detect = vc4_vec_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = vc4_vec_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs vc4_vec_connector_helper_funcs = अणु
	.get_modes = vc4_vec_connector_get_modes,
पूर्ण;

अटल काष्ठा drm_connector *vc4_vec_connector_init(काष्ठा drm_device *dev,
						    काष्ठा vc4_vec *vec)
अणु
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा vc4_vec_connector *vec_connector;

	vec_connector = devm_kzalloc(dev->dev, माप(*vec_connector),
				     GFP_KERNEL);
	अगर (!vec_connector)
		वापस ERR_PTR(-ENOMEM);

	connector = &vec_connector->base;
	connector->पूर्णांकerlace_allowed = true;

	vec_connector->encoder = vec->encoder;
	vec_connector->vec = vec;

	drm_connector_init(dev, connector, &vc4_vec_connector_funcs,
			   DRM_MODE_CONNECTOR_Composite);
	drm_connector_helper_add(connector, &vc4_vec_connector_helper_funcs);

	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_mode_property,
				   VC4_VEC_TV_MODE_NTSC);
	vec->tv_mode = &vc4_vec_tv_modes[VC4_VEC_TV_MODE_NTSC];

	drm_connector_attach_encoder(connector, vec->encoder);

	वापस connector;
पूर्ण

अटल व्योम vc4_vec_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_vec_encoder *vc4_vec_encoder = to_vc4_vec_encoder(encoder);
	काष्ठा vc4_vec *vec = vc4_vec_encoder->vec;
	पूर्णांक ret;

	VEC_WRITE(VEC_CFG, 0);
	VEC_WRITE(VEC_DAC_MISC,
		  VEC_DAC_MISC_VCD_PWRDN |
		  VEC_DAC_MISC_BIAS_PWRDN |
		  VEC_DAC_MISC_DAC_PWRDN |
		  VEC_DAC_MISC_LDO_PWRDN);

	clk_disable_unprepare(vec->घड़ी);

	ret = pm_runसमय_put(&vec->pdev->dev);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to release power domain: %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम vc4_vec_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_vec_encoder *vc4_vec_encoder = to_vc4_vec_encoder(encoder);
	काष्ठा vc4_vec *vec = vc4_vec_encoder->vec;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&vec->pdev->dev);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to retain power domain: %d\n", ret);
		वापस;
	पूर्ण

	/*
	 * We need to set the घड़ी rate each समय we enable the encoder
	 * because there's a chance we share the same parent with the HDMI
	 * घड़ी, and both drivers are requesting dअगरferent rates.
	 * The good news is, these 2 encoders cannot be enabled at the same
	 * समय, thus preventing incompatible rate requests.
	 */
	ret = clk_set_rate(vec->घड़ी, 108000000);
	अगर (ret) अणु
		DRM_ERROR("Failed to set clock rate: %d\n", ret);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(vec->घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on core clock: %d\n", ret);
		वापस;
	पूर्ण

	/* Reset the dअगरferent blocks */
	VEC_WRITE(VEC_WSE_RESET, 1);
	VEC_WRITE(VEC_SOFT_RESET, 1);

	/* Disable the CGSM-A and WSE blocks */
	VEC_WRITE(VEC_WSE_CONTROL, 0);

	/* Write config common to all modes. */

	/*
	 * Color subcarrier phase: phase = 360 * SCHPH / 256.
	 * 0x28 <=> 39.375 deg.
	 */
	VEC_WRITE(VEC_SCHPH, 0x28);

	/*
	 * Reset to शेष values.
	 */
	VEC_WRITE(VEC_CLMP0_START, 0xac);
	VEC_WRITE(VEC_CLMP0_END, 0xec);
	VEC_WRITE(VEC_CONFIG2,
		  VEC_CONFIG2_UV_DIG_DIS | VEC_CONFIG2_RGB_DIG_DIS);
	VEC_WRITE(VEC_CONFIG3, VEC_CONFIG3_HORIZ_LEN_STD);
	VEC_WRITE(VEC_DAC_CONFIG,
		  VEC_DAC_CONFIG_DAC_CTRL(0xc) |
		  VEC_DAC_CONFIG_DRIVER_CTRL(0xc) |
		  VEC_DAC_CONFIG_LDO_BIAS_CTRL(0x46));

	/* Mask all पूर्णांकerrupts. */
	VEC_WRITE(VEC_MASK0, 0);

	vec->tv_mode->mode_set(vec);

	VEC_WRITE(VEC_DAC_MISC,
		  VEC_DAC_MISC_VID_ACT | VEC_DAC_MISC_DAC_RST_N);
	VEC_WRITE(VEC_CFG, VEC_CFG_VEC_EN);
पूर्ण


अटल bool vc4_vec_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				       स्थिर काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस true;
पूर्ण

अटल व्योम vc4_vec_encoder_atomic_mode_set(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा vc4_vec_encoder *vc4_vec_encoder = to_vc4_vec_encoder(encoder);
	काष्ठा vc4_vec *vec = vc4_vec_encoder->vec;

	vec->tv_mode = &vc4_vec_tv_modes[conn_state->tv.mode];
पूर्ण

अटल पूर्णांक vc4_vec_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	स्थिर काष्ठा vc4_vec_tv_mode *vec_mode;

	vec_mode = &vc4_vec_tv_modes[conn_state->tv.mode];

	अगर (conn_state->crtc &&
	    !drm_mode_equal(vec_mode->mode, &crtc_state->adjusted_mode))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs vc4_vec_encoder_helper_funcs = अणु
	.disable = vc4_vec_encoder_disable,
	.enable = vc4_vec_encoder_enable,
	.mode_fixup = vc4_vec_encoder_mode_fixup,
	.atomic_check = vc4_vec_encoder_atomic_check,
	.atomic_mode_set = vc4_vec_encoder_atomic_mode_set,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vc4_vec_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-vec", .data = शून्य पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tv_mode_names[] = अणु
	[VC4_VEC_TV_MODE_NTSC] = "NTSC",
	[VC4_VEC_TV_MODE_NTSC_J] = "NTSC-J",
	[VC4_VEC_TV_MODE_PAL] = "PAL",
	[VC4_VEC_TV_MODE_PAL_M] = "PAL-M",
पूर्ण;

अटल पूर्णांक vc4_vec_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_vec *vec;
	काष्ठा vc4_vec_encoder *vc4_vec_encoder;
	पूर्णांक ret;

	ret = drm_mode_create_tv_properties(drm, ARRAY_SIZE(tv_mode_names),
					    tv_mode_names);
	अगर (ret)
		वापस ret;

	vec = devm_kzalloc(dev, माप(*vec), GFP_KERNEL);
	अगर (!vec)
		वापस -ENOMEM;

	vc4_vec_encoder = devm_kzalloc(dev, माप(*vc4_vec_encoder),
				       GFP_KERNEL);
	अगर (!vc4_vec_encoder)
		वापस -ENOMEM;
	vc4_vec_encoder->base.type = VC4_ENCODER_TYPE_VEC;
	vc4_vec_encoder->vec = vec;
	vec->encoder = &vc4_vec_encoder->base.base;

	vec->pdev = pdev;
	vec->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(vec->regs))
		वापस PTR_ERR(vec->regs);
	vec->regset.base = vec->regs;
	vec->regset.regs = vec_regs;
	vec->regset.nregs = ARRAY_SIZE(vec_regs);

	vec->घड़ी = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(vec->घड़ी)) अणु
		ret = PTR_ERR(vec->घड़ी);
		अगर (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get clock: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	drm_simple_encoder_init(drm, vec->encoder, DRM_MODE_ENCODER_TVDAC);
	drm_encoder_helper_add(vec->encoder, &vc4_vec_encoder_helper_funcs);

	vec->connector = vc4_vec_connector_init(drm, vec);
	अगर (IS_ERR(vec->connector)) अणु
		ret = PTR_ERR(vec->connector);
		जाओ err_destroy_encoder;
	पूर्ण

	dev_set_drvdata(dev, vec);

	vc4->vec = vec;

	vc4_debugfs_add_regset32(drm, "vec_regs", &vec->regset);

	वापस 0;

err_destroy_encoder:
	drm_encoder_cleanup(vec->encoder);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल व्योम vc4_vec_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_vec *vec = dev_get_drvdata(dev);

	vc4_vec_connector_destroy(vec->connector);
	drm_encoder_cleanup(vec->encoder);
	pm_runसमय_disable(dev);

	vc4->vec = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_vec_ops = अणु
	.bind   = vc4_vec_bind,
	.unbind = vc4_vec_unbind,
पूर्ण;

अटल पूर्णांक vc4_vec_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_vec_ops);
पूर्ण

अटल पूर्णांक vc4_vec_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_vec_ops);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vc4_vec_driver = अणु
	.probe = vc4_vec_dev_probe,
	.हटाओ = vc4_vec_dev_हटाओ,
	.driver = अणु
		.name = "vc4_vec",
		.of_match_table = vc4_vec_dt_match,
	पूर्ण,
पूर्ण;
