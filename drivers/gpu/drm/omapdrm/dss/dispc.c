<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DISPC"

#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/component.h>
#समावेश <linux/sys_soc.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_blend.h>

#समावेश "omapdss.h"
#समावेश "dss.h"
#समावेश "dispc.h"

काष्ठा dispc_device;

/* DISPC */
#घोषणा DISPC_SZ_REGS			SZ_4K

क्रमागत omap_burst_size अणु
	BURST_SIZE_X2 = 0,
	BURST_SIZE_X4 = 1,
	BURST_SIZE_X8 = 2,
पूर्ण;

#घोषणा REG_GET(dispc, idx, start, end) \
	FLD_GET(dispc_पढ़ो_reg(dispc, idx), start, end)

#घोषणा REG_FLD_MOD(dispc, idx, val, start, end)			\
	dispc_ग_लिखो_reg(dispc, idx, \
			FLD_MOD(dispc_पढ़ो_reg(dispc, idx), val, start, end))

/* DISPC has feature id */
क्रमागत dispc_feature_id अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_MGR_LCD2,
	FEAT_MGR_LCD3,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	/* Independent core clk भागider */
	FEAT_CORE_CLK_DIV,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	/* An unknown HW bug causing the normal FIFO thresholds not to work */
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_BURST_2D,
	FEAT_MFLAG,
पूर्ण;

काष्ठा dispc_features अणु
	u8 sw_start;
	u8 fp_start;
	u8 bp_start;
	u16 sw_max;
	u16 vp_max;
	u16 hp_max;
	u8 mgr_width_start;
	u8 mgr_height_start;
	u16 mgr_width_max;
	u16 mgr_height_max;
	अचिन्हित दीर्घ max_lcd_pclk;
	अचिन्हित दीर्घ max_tv_pclk;
	अचिन्हित पूर्णांक max_करोwnscale;
	अचिन्हित पूर्णांक max_line_width;
	अचिन्हित पूर्णांक min_pcd;
	पूर्णांक (*calc_scaling)(काष्ठा dispc_device *dispc,
		अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा videomode *vm,
		u16 width, u16 height, u16 out_width, u16 out_height,
		u32 fourcc, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, पूर्णांक *decim_x, पूर्णांक *decim_y,
		u16 pos_x, अचिन्हित दीर्घ *core_clk, bool mem_to_mem);
	अचिन्हित दीर्घ (*calc_core_clk) (अचिन्हित दीर्घ pclk,
		u16 width, u16 height, u16 out_width, u16 out_height,
		bool mem_to_mem);
	u8 num_fअगरos;
	स्थिर क्रमागत dispc_feature_id *features;
	अचिन्हित पूर्णांक num_features;
	स्थिर काष्ठा dss_reg_field *reg_fields;
	स्थिर अचिन्हित पूर्णांक num_reg_fields;
	स्थिर क्रमागत omap_overlay_caps *overlay_caps;
	स्थिर u32 **supported_color_modes;
	स्थिर u32 *supported_scaler_color_modes;
	अचिन्हित पूर्णांक num_mgrs;
	अचिन्हित पूर्णांक num_ovls;
	अचिन्हित पूर्णांक buffer_size_unit;
	अचिन्हित पूर्णांक burst_size_unit;

	/* swap GFX & WB fअगरos */
	bool gfx_fअगरo_workaround:1;

	/* no DISPC_IRQ_FRAMEDONETV on this SoC */
	bool no_frameकरोne_tv:1;

	/* revert to the OMAP4 mechanism of DISPC Smart Standby operation */
	bool mstandby_workaround:1;

	bool set_max_preload:1;

	/* PIXEL_INC is not added to the last pixel of a line */
	bool last_pixel_inc_missing:1;

	/* POL_FREQ has ALIGN bit */
	bool supports_sync_align:1;

	bool has_ग_लिखोback:1;

	bool supports_द्विगुन_pixel:1;

	/*
	 * Field order क्रम VENC is dअगरferent than HDMI. We should handle this in
	 * some पूर्णांकelligent manner, but as the SoCs have either HDMI or VENC,
	 * never both, we can just use this flag क्रम now.
	 */
	bool reverse_ilace_field_order:1;

	bool has_gamma_table:1;

	bool has_gamma_i734_bug:1;
पूर्ण;

#घोषणा DISPC_MAX_NR_FIFOS 5
#घोषणा DISPC_MAX_CHANNEL_GAMMA 4

काष्ठा dispc_device अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem    *base;
	काष्ठा dss_device *dss;

	काष्ठा dss_debugfs_entry *debugfs;

	पूर्णांक irq;
	irq_handler_t user_handler;
	व्योम *user_data;

	अचिन्हित दीर्घ core_clk_rate;
	अचिन्हित दीर्घ tv_pclk_rate;

	u32 fअगरo_size[DISPC_MAX_NR_FIFOS];
	/* maps which plane is using a fअगरo. fअगरo-id -> plane-id */
	पूर्णांक fअगरo_assignment[DISPC_MAX_NR_FIFOS];

	bool		ctx_valid;
	u32		ctx[DISPC_SZ_REGS / माप(u32)];

	u32 *gamma_table[DISPC_MAX_CHANNEL_GAMMA];

	स्थिर काष्ठा dispc_features *feat;

	bool is_enabled;

	काष्ठा regmap *syscon_pol;
	u32 syscon_pol_offset;
पूर्ण;

क्रमागत omap_color_component अणु
	/* used क्रम all color क्रमmats क्रम OMAP3 and earlier
	 * and क्रम RGB and Y color component on OMAP4
	 */
	DISPC_COLOR_COMPONENT_RGB_Y		= 1 << 0,
	/* used क्रम UV component क्रम
	 * DRM_FORMAT_YUYV, DRM_FORMAT_UYVY, DRM_FORMAT_NV12
	 * color क्रमmats on OMAP4
	 */
	DISPC_COLOR_COMPONENT_UV		= 1 << 1,
पूर्ण;

क्रमागत mgr_reg_fields अणु
	DISPC_MGR_FLD_ENABLE,
	DISPC_MGR_FLD_STNTFT,
	DISPC_MGR_FLD_GO,
	DISPC_MGR_FLD_TFTDATALINES,
	DISPC_MGR_FLD_STALLMODE,
	DISPC_MGR_FLD_TCKENABLE,
	DISPC_MGR_FLD_TCKSELECTION,
	DISPC_MGR_FLD_CPR,
	DISPC_MGR_FLD_FIFOHANDCHECK,
	/* used to मुख्यtain a count of the above fields */
	DISPC_MGR_FLD_NUM,
पूर्ण;

/* DISPC रेजिस्टर field id */
क्रमागत dispc_feat_reg_field अणु
	FEAT_REG_FIRHINC,
	FEAT_REG_FIRVINC,
	FEAT_REG_FIFOHIGHTHRESHOLD,
	FEAT_REG_FIFOLOWTHRESHOLD,
	FEAT_REG_FIFOSIZE,
	FEAT_REG_HORIZONTALACCU,
	FEAT_REG_VERTICALACCU,
पूर्ण;

काष्ठा dispc_reg_field अणु
	u16 reg;
	u8 high;
	u8 low;
पूर्ण;

काष्ठा dispc_gamma_desc अणु
	u32 len;
	u32 bits;
	u16 reg;
	bool has_index;
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u32 vsync_irq;
	u32 frameकरोne_irq;
	u32 sync_lost_irq;
	काष्ठा dispc_gamma_desc gamma;
	काष्ठा dispc_reg_field reg_desc[DISPC_MGR_FLD_NUM];
पूर्ण mgr_desc[] = अणु
	[OMAP_DSS_CHANNEL_LCD] = अणु
		.name		= "LCD",
		.vsync_irq	= DISPC_IRQ_VSYNC,
		.frameकरोne_irq	= DISPC_IRQ_FRAMEDONE,
		.sync_lost_irq	= DISPC_IRQ_SYNC_LOST,
		.gamma		= अणु
			.len	= 256,
			.bits	= 8,
			.reg	= DISPC_GAMMA_TABLE0,
			.has_index = true,
		पूर्ण,
		.reg_desc	= अणु
			[DISPC_MGR_FLD_ENABLE]		= अणु DISPC_CONTROL,  0,  0 पूर्ण,
			[DISPC_MGR_FLD_STNTFT]		= अणु DISPC_CONTROL,  3,  3 पूर्ण,
			[DISPC_MGR_FLD_GO]		= अणु DISPC_CONTROL,  5,  5 पूर्ण,
			[DISPC_MGR_FLD_TFTDATALINES]	= अणु DISPC_CONTROL,  9,  8 पूर्ण,
			[DISPC_MGR_FLD_STALLMODE]	= अणु DISPC_CONTROL, 11, 11 पूर्ण,
			[DISPC_MGR_FLD_TCKENABLE]	= अणु DISPC_CONFIG,  10, 10 पूर्ण,
			[DISPC_MGR_FLD_TCKSELECTION]	= अणु DISPC_CONFIG,  11, 11 पूर्ण,
			[DISPC_MGR_FLD_CPR]		= अणु DISPC_CONFIG,  15, 15 पूर्ण,
			[DISPC_MGR_FLD_FIFOHANDCHECK]	= अणु DISPC_CONFIG,  16, 16 पूर्ण,
		पूर्ण,
	पूर्ण,
	[OMAP_DSS_CHANNEL_DIGIT] = अणु
		.name		= "DIGIT",
		.vsync_irq	= DISPC_IRQ_EVSYNC_ODD | DISPC_IRQ_EVSYNC_EVEN,
		.frameकरोne_irq	= DISPC_IRQ_FRAMEDONETV,
		.sync_lost_irq	= DISPC_IRQ_SYNC_LOST_DIGIT,
		.gamma		= अणु
			.len	= 1024,
			.bits	= 10,
			.reg	= DISPC_GAMMA_TABLE2,
			.has_index = false,
		पूर्ण,
		.reg_desc	= अणु
			[DISPC_MGR_FLD_ENABLE]		= अणु DISPC_CONTROL,  1,  1 पूर्ण,
			[DISPC_MGR_FLD_STNTFT]		= अणु पूर्ण,
			[DISPC_MGR_FLD_GO]		= अणु DISPC_CONTROL,  6,  6 पूर्ण,
			[DISPC_MGR_FLD_TFTDATALINES]	= अणु पूर्ण,
			[DISPC_MGR_FLD_STALLMODE]	= अणु पूर्ण,
			[DISPC_MGR_FLD_TCKENABLE]	= अणु DISPC_CONFIG,  12, 12 पूर्ण,
			[DISPC_MGR_FLD_TCKSELECTION]	= अणु DISPC_CONFIG,  13, 13 पूर्ण,
			[DISPC_MGR_FLD_CPR]		= अणु पूर्ण,
			[DISPC_MGR_FLD_FIFOHANDCHECK]	= अणु DISPC_CONFIG,  16, 16 पूर्ण,
		पूर्ण,
	पूर्ण,
	[OMAP_DSS_CHANNEL_LCD2] = अणु
		.name		= "LCD2",
		.vsync_irq	= DISPC_IRQ_VSYNC2,
		.frameकरोne_irq	= DISPC_IRQ_FRAMEDONE2,
		.sync_lost_irq	= DISPC_IRQ_SYNC_LOST2,
		.gamma		= अणु
			.len	= 256,
			.bits	= 8,
			.reg	= DISPC_GAMMA_TABLE1,
			.has_index = true,
		पूर्ण,
		.reg_desc	= अणु
			[DISPC_MGR_FLD_ENABLE]		= अणु DISPC_CONTROL2,  0,  0 पूर्ण,
			[DISPC_MGR_FLD_STNTFT]		= अणु DISPC_CONTROL2,  3,  3 पूर्ण,
			[DISPC_MGR_FLD_GO]		= अणु DISPC_CONTROL2,  5,  5 पूर्ण,
			[DISPC_MGR_FLD_TFTDATALINES]	= अणु DISPC_CONTROL2,  9,  8 पूर्ण,
			[DISPC_MGR_FLD_STALLMODE]	= अणु DISPC_CONTROL2, 11, 11 पूर्ण,
			[DISPC_MGR_FLD_TCKENABLE]	= अणु DISPC_CONFIG2,  10, 10 पूर्ण,
			[DISPC_MGR_FLD_TCKSELECTION]	= अणु DISPC_CONFIG2,  11, 11 पूर्ण,
			[DISPC_MGR_FLD_CPR]		= अणु DISPC_CONFIG2,  15, 15 पूर्ण,
			[DISPC_MGR_FLD_FIFOHANDCHECK]	= अणु DISPC_CONFIG2,  16, 16 पूर्ण,
		पूर्ण,
	पूर्ण,
	[OMAP_DSS_CHANNEL_LCD3] = अणु
		.name		= "LCD3",
		.vsync_irq	= DISPC_IRQ_VSYNC3,
		.frameकरोne_irq	= DISPC_IRQ_FRAMEDONE3,
		.sync_lost_irq	= DISPC_IRQ_SYNC_LOST3,
		.gamma		= अणु
			.len	= 256,
			.bits	= 8,
			.reg	= DISPC_GAMMA_TABLE3,
			.has_index = true,
		पूर्ण,
		.reg_desc	= अणु
			[DISPC_MGR_FLD_ENABLE]		= अणु DISPC_CONTROL3,  0,  0 पूर्ण,
			[DISPC_MGR_FLD_STNTFT]		= अणु DISPC_CONTROL3,  3,  3 पूर्ण,
			[DISPC_MGR_FLD_GO]		= अणु DISPC_CONTROL3,  5,  5 पूर्ण,
			[DISPC_MGR_FLD_TFTDATALINES]	= अणु DISPC_CONTROL3,  9,  8 पूर्ण,
			[DISPC_MGR_FLD_STALLMODE]	= अणु DISPC_CONTROL3, 11, 11 पूर्ण,
			[DISPC_MGR_FLD_TCKENABLE]	= अणु DISPC_CONFIG3,  10, 10 पूर्ण,
			[DISPC_MGR_FLD_TCKSELECTION]	= अणु DISPC_CONFIG3,  11, 11 पूर्ण,
			[DISPC_MGR_FLD_CPR]		= अणु DISPC_CONFIG3,  15, 15 पूर्ण,
			[DISPC_MGR_FLD_FIFOHANDCHECK]	= अणु DISPC_CONFIG3,  16, 16 पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ dispc_fclk_rate(काष्ठा dispc_device *dispc);
अटल अचिन्हित दीर्घ dispc_core_clk_rate(काष्ठा dispc_device *dispc);
अटल अचिन्हित दीर्घ dispc_mgr_lclk_rate(काष्ठा dispc_device *dispc,
					 क्रमागत omap_channel channel);
अटल अचिन्हित दीर्घ dispc_mgr_pclk_rate(काष्ठा dispc_device *dispc,
					 क्रमागत omap_channel channel);

अटल अचिन्हित दीर्घ dispc_plane_pclk_rate(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane);
अटल अचिन्हित दीर्घ dispc_plane_lclk_rate(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane);

अटल अंतरभूत व्योम dispc_ग_लिखो_reg(काष्ठा dispc_device *dispc, u16 idx, u32 val)
अणु
	__raw_ग_लिखोl(val, dispc->base + idx);
पूर्ण

अटल अंतरभूत u32 dispc_पढ़ो_reg(काष्ठा dispc_device *dispc, u16 idx)
अणु
	वापस __raw_पढ़ोl(dispc->base + idx);
पूर्ण

अटल u32 mgr_fld_पढ़ो(काष्ठा dispc_device *dispc, क्रमागत omap_channel channel,
			क्रमागत mgr_reg_fields regfld)
अणु
	स्थिर काष्ठा dispc_reg_field *rfld = &mgr_desc[channel].reg_desc[regfld];

	वापस REG_GET(dispc, rfld->reg, rfld->high, rfld->low);
पूर्ण

अटल व्योम mgr_fld_ग_लिखो(काष्ठा dispc_device *dispc, क्रमागत omap_channel channel,
			  क्रमागत mgr_reg_fields regfld, पूर्णांक val)
अणु
	स्थिर काष्ठा dispc_reg_field *rfld = &mgr_desc[channel].reg_desc[regfld];

	REG_FLD_MOD(dispc, rfld->reg, val, rfld->high, rfld->low);
पूर्ण

पूर्णांक dispc_get_num_ovls(काष्ठा dispc_device *dispc)
अणु
	वापस dispc->feat->num_ovls;
पूर्ण

पूर्णांक dispc_get_num_mgrs(काष्ठा dispc_device *dispc)
अणु
	वापस dispc->feat->num_mgrs;
पूर्ण

अटल व्योम dispc_get_reg_field(काष्ठा dispc_device *dispc,
				क्रमागत dispc_feat_reg_field id,
				u8 *start, u8 *end)
अणु
	BUG_ON(id >= dispc->feat->num_reg_fields);

	*start = dispc->feat->reg_fields[id].start;
	*end = dispc->feat->reg_fields[id].end;
पूर्ण

अटल bool dispc_has_feature(काष्ठा dispc_device *dispc,
			      क्रमागत dispc_feature_id id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dispc->feat->num_features; i++) अणु
		अगर (dispc->feat->features[i] == id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा SR(dispc, reg) \
	dispc->ctx[DISPC_##reg / माप(u32)] = dispc_पढ़ो_reg(dispc, DISPC_##reg)
#घोषणा RR(dispc, reg) \
	dispc_ग_लिखो_reg(dispc, DISPC_##reg, dispc->ctx[DISPC_##reg / माप(u32)])

अटल व्योम dispc_save_context(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक i, j;

	DSSDBG("dispc_save_context\n");

	SR(dispc, IRQENABLE);
	SR(dispc, CONTROL);
	SR(dispc, CONFIG);
	SR(dispc, LINE_NUMBER);
	अगर (dispc_has_feature(dispc, FEAT_ALPHA_FIXED_ZORDER) ||
			dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		SR(dispc, GLOBAL_ALPHA);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2)) अणु
		SR(dispc, CONTROL2);
		SR(dispc, CONFIG2);
	पूर्ण
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3)) अणु
		SR(dispc, CONTROL3);
		SR(dispc, CONFIG3);
	पूर्ण

	क्रम (i = 0; i < dispc_get_num_mgrs(dispc); i++) अणु
		SR(dispc, DEFAULT_COLOR(i));
		SR(dispc, TRANS_COLOR(i));
		SR(dispc, SIZE_MGR(i));
		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;
		SR(dispc, TIMING_H(i));
		SR(dispc, TIMING_V(i));
		SR(dispc, POL_FREQ(i));
		SR(dispc, DIVISORo(i));

		SR(dispc, DATA_CYCLE1(i));
		SR(dispc, DATA_CYCLE2(i));
		SR(dispc, DATA_CYCLE3(i));

		अगर (dispc_has_feature(dispc, FEAT_CPR)) अणु
			SR(dispc, CPR_COEF_R(i));
			SR(dispc, CPR_COEF_G(i));
			SR(dispc, CPR_COEF_B(i));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dispc_get_num_ovls(dispc); i++) अणु
		SR(dispc, OVL_BA0(i));
		SR(dispc, OVL_BA1(i));
		SR(dispc, OVL_POSITION(i));
		SR(dispc, OVL_SIZE(i));
		SR(dispc, OVL_ATTRIBUTES(i));
		SR(dispc, OVL_FIFO_THRESHOLD(i));
		SR(dispc, OVL_ROW_INC(i));
		SR(dispc, OVL_PIXEL_INC(i));
		अगर (dispc_has_feature(dispc, FEAT_PRELOAD))
			SR(dispc, OVL_PRELOAD(i));
		अगर (i == OMAP_DSS_GFX) अणु
			SR(dispc, OVL_WINDOW_SKIP(i));
			SR(dispc, OVL_TABLE_BA(i));
			जारी;
		पूर्ण
		SR(dispc, OVL_FIR(i));
		SR(dispc, OVL_PICTURE_SIZE(i));
		SR(dispc, OVL_ACCU0(i));
		SR(dispc, OVL_ACCU1(i));

		क्रम (j = 0; j < 8; j++)
			SR(dispc, OVL_FIR_COEF_H(i, j));

		क्रम (j = 0; j < 8; j++)
			SR(dispc, OVL_FIR_COEF_HV(i, j));

		क्रम (j = 0; j < 5; j++)
			SR(dispc, OVL_CONV_COEF(i, j));

		अगर (dispc_has_feature(dispc, FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_V(i, j));
		पूर्ण

		अगर (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) अणु
			SR(dispc, OVL_BA0_UV(i));
			SR(dispc, OVL_BA1_UV(i));
			SR(dispc, OVL_FIR2(i));
			SR(dispc, OVL_ACCU2_0(i));
			SR(dispc, OVL_ACCU2_1(i));

			क्रम (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_H2(i, j));

			क्रम (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_HV2(i, j));

			क्रम (j = 0; j < 8; j++)
				SR(dispc, OVL_FIR_COEF_V2(i, j));
		पूर्ण
		अगर (dispc_has_feature(dispc, FEAT_ATTR2))
			SR(dispc, OVL_ATTRIBUTES2(i));
	पूर्ण

	अगर (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV))
		SR(dispc, DIVISOR);

	dispc->ctx_valid = true;

	DSSDBG("context saved\n");
पूर्ण

अटल व्योम dispc_restore_context(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक i, j;

	DSSDBG("dispc_restore_context\n");

	अगर (!dispc->ctx_valid)
		वापस;

	/*RR(dispc, IRQENABLE);*/
	/*RR(dispc, CONTROL);*/
	RR(dispc, CONFIG);
	RR(dispc, LINE_NUMBER);
	अगर (dispc_has_feature(dispc, FEAT_ALPHA_FIXED_ZORDER) ||
			dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		RR(dispc, GLOBAL_ALPHA);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2))
		RR(dispc, CONFIG2);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3))
		RR(dispc, CONFIG3);

	क्रम (i = 0; i < dispc_get_num_mgrs(dispc); i++) अणु
		RR(dispc, DEFAULT_COLOR(i));
		RR(dispc, TRANS_COLOR(i));
		RR(dispc, SIZE_MGR(i));
		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;
		RR(dispc, TIMING_H(i));
		RR(dispc, TIMING_V(i));
		RR(dispc, POL_FREQ(i));
		RR(dispc, DIVISORo(i));

		RR(dispc, DATA_CYCLE1(i));
		RR(dispc, DATA_CYCLE2(i));
		RR(dispc, DATA_CYCLE3(i));

		अगर (dispc_has_feature(dispc, FEAT_CPR)) अणु
			RR(dispc, CPR_COEF_R(i));
			RR(dispc, CPR_COEF_G(i));
			RR(dispc, CPR_COEF_B(i));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dispc_get_num_ovls(dispc); i++) अणु
		RR(dispc, OVL_BA0(i));
		RR(dispc, OVL_BA1(i));
		RR(dispc, OVL_POSITION(i));
		RR(dispc, OVL_SIZE(i));
		RR(dispc, OVL_ATTRIBUTES(i));
		RR(dispc, OVL_FIFO_THRESHOLD(i));
		RR(dispc, OVL_ROW_INC(i));
		RR(dispc, OVL_PIXEL_INC(i));
		अगर (dispc_has_feature(dispc, FEAT_PRELOAD))
			RR(dispc, OVL_PRELOAD(i));
		अगर (i == OMAP_DSS_GFX) अणु
			RR(dispc, OVL_WINDOW_SKIP(i));
			RR(dispc, OVL_TABLE_BA(i));
			जारी;
		पूर्ण
		RR(dispc, OVL_FIR(i));
		RR(dispc, OVL_PICTURE_SIZE(i));
		RR(dispc, OVL_ACCU0(i));
		RR(dispc, OVL_ACCU1(i));

		क्रम (j = 0; j < 8; j++)
			RR(dispc, OVL_FIR_COEF_H(i, j));

		क्रम (j = 0; j < 8; j++)
			RR(dispc, OVL_FIR_COEF_HV(i, j));

		क्रम (j = 0; j < 5; j++)
			RR(dispc, OVL_CONV_COEF(i, j));

		अगर (dispc_has_feature(dispc, FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				RR(dispc, OVL_FIR_COEF_V(i, j));
		पूर्ण

		अगर (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) अणु
			RR(dispc, OVL_BA0_UV(i));
			RR(dispc, OVL_BA1_UV(i));
			RR(dispc, OVL_FIR2(i));
			RR(dispc, OVL_ACCU2_0(i));
			RR(dispc, OVL_ACCU2_1(i));

			क्रम (j = 0; j < 8; j++)
				RR(dispc, OVL_FIR_COEF_H2(i, j));

			क्रम (j = 0; j < 8; j++)
				RR(dispc, OVL_FIR_COEF_HV2(i, j));

			क्रम (j = 0; j < 8; j++)
				RR(dispc, OVL_FIR_COEF_V2(i, j));
		पूर्ण
		अगर (dispc_has_feature(dispc, FEAT_ATTR2))
			RR(dispc, OVL_ATTRIBUTES2(i));
	पूर्ण

	अगर (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV))
		RR(dispc, DIVISOR);

	/* enable last, because LCD & DIGIT enable are here */
	RR(dispc, CONTROL);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2))
		RR(dispc, CONTROL2);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3))
		RR(dispc, CONTROL3);
	/* clear spurious SYNC_LOST_DIGIT पूर्णांकerrupts */
	dispc_clear_irqstatus(dispc, DISPC_IRQ_SYNC_LOST_DIGIT);

	/*
	 * enable last so IRQs won't trigger beक्रमe
	 * the context is fully restored
	 */
	RR(dispc, IRQENABLE);

	DSSDBG("context restored\n");
पूर्ण

#अघोषित SR
#अघोषित RR

पूर्णांक dispc_runसमय_get(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक r;

	DSSDBG("dispc_runtime_get\n");

	r = pm_runसमय_get_sync(&dispc->pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_noidle(&dispc->pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dispc_runसमय_put(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक r;

	DSSDBG("dispc_runtime_put\n");

	r = pm_runसमय_put_sync(&dispc->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

u32 dispc_mgr_get_vsync_irq(काष्ठा dispc_device *dispc,
				   क्रमागत omap_channel channel)
अणु
	वापस mgr_desc[channel].vsync_irq;
पूर्ण

u32 dispc_mgr_get_frameकरोne_irq(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel)
अणु
	अगर (channel == OMAP_DSS_CHANNEL_DIGIT && dispc->feat->no_frameकरोne_tv)
		वापस 0;

	वापस mgr_desc[channel].frameकरोne_irq;
पूर्ण

u32 dispc_mgr_get_sync_lost_irq(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel)
अणु
	वापस mgr_desc[channel].sync_lost_irq;
पूर्ण

u32 dispc_wb_get_frameकरोne_irq(काष्ठा dispc_device *dispc)
अणु
	वापस DISPC_IRQ_FRAMEDONEWB;
पूर्ण

व्योम dispc_mgr_enable(काष्ठा dispc_device *dispc,
			     क्रमागत omap_channel channel, bool enable)
अणु
	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_ENABLE, enable);
	/* flush posted ग_लिखो */
	mgr_fld_पढ़ो(dispc, channel, DISPC_MGR_FLD_ENABLE);
पूर्ण

अटल bool dispc_mgr_is_enabled(काष्ठा dispc_device *dispc,
				 क्रमागत omap_channel channel)
अणु
	वापस !!mgr_fld_पढ़ो(dispc, channel, DISPC_MGR_FLD_ENABLE);
पूर्ण

bool dispc_mgr_go_busy(काष्ठा dispc_device *dispc,
			      क्रमागत omap_channel channel)
अणु
	वापस mgr_fld_पढ़ो(dispc, channel, DISPC_MGR_FLD_GO) == 1;
पूर्ण

व्योम dispc_mgr_go(काष्ठा dispc_device *dispc, क्रमागत omap_channel channel)
अणु
	WARN_ON(!dispc_mgr_is_enabled(dispc, channel));
	WARN_ON(dispc_mgr_go_busy(dispc, channel));

	DSSDBG("GO %s\n", mgr_desc[channel].name);

	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_GO, 1);
पूर्ण

bool dispc_wb_go_busy(काष्ठा dispc_device *dispc)
अणु
	वापस REG_GET(dispc, DISPC_CONTROL2, 6, 6) == 1;
पूर्ण

व्योम dispc_wb_go(काष्ठा dispc_device *dispc)
अणु
	क्रमागत omap_plane_id plane = OMAP_DSS_WB;
	bool enable, go;

	enable = REG_GET(dispc, DISPC_OVL_ATTRIBUTES(plane), 0, 0) == 1;

	अगर (!enable)
		वापस;

	go = REG_GET(dispc, DISPC_CONTROL2, 6, 6) == 1;
	अगर (go) अणु
		DSSERR("GO bit not down for WB\n");
		वापस;
	पूर्ण

	REG_FLD_MOD(dispc, DISPC_CONTROL2, 1, 6, 6);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firh_reg(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane, पूर्णांक reg,
				     u32 value)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_H(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firhv_reg(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक reg,
				      u32 value)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_HV(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firv_reg(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane, पूर्णांक reg,
				     u32 value)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_V(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firh2_reg(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक reg,
				      u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_H2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firhv2_reg(काष्ठा dispc_device *dispc,
				       क्रमागत omap_plane_id plane, पूर्णांक reg,
				       u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_HV2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firv2_reg(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक reg,
				      u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR_COEF_V2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_set_scale_coef(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane, पूर्णांक fir_hinc,
				     पूर्णांक fir_vinc, पूर्णांक five_taps,
				     क्रमागत omap_color_component color_comp)
अणु
	स्थिर काष्ठा dispc_coef *h_coef, *v_coef;
	पूर्णांक i;

	h_coef = dispc_ovl_get_scale_coef(fir_hinc, true);
	v_coef = dispc_ovl_get_scale_coef(fir_vinc, five_taps);

	अगर (!h_coef || !v_coef) अणु
		dev_err(&dispc->pdev->dev, "%s: failed to find scale coefs\n",
			__func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		u32 h, hv;

		h = FLD_VAL(h_coef[i].hc0_vc00, 7, 0)
			| FLD_VAL(h_coef[i].hc1_vc0, 15, 8)
			| FLD_VAL(h_coef[i].hc2_vc1, 23, 16)
			| FLD_VAL(h_coef[i].hc3_vc2, 31, 24);
		hv = FLD_VAL(h_coef[i].hc4_vc22, 7, 0)
			| FLD_VAL(v_coef[i].hc1_vc0, 15, 8)
			| FLD_VAL(v_coef[i].hc2_vc1, 23, 16)
			| FLD_VAL(v_coef[i].hc3_vc2, 31, 24);

		अगर (color_comp == DISPC_COLOR_COMPONENT_RGB_Y) अणु
			dispc_ovl_ग_लिखो_firh_reg(dispc, plane, i, h);
			dispc_ovl_ग_लिखो_firhv_reg(dispc, plane, i, hv);
		पूर्ण अन्यथा अणु
			dispc_ovl_ग_लिखो_firh2_reg(dispc, plane, i, h);
			dispc_ovl_ग_लिखो_firhv2_reg(dispc, plane, i, hv);
		पूर्ण

	पूर्ण

	अगर (five_taps) अणु
		क्रम (i = 0; i < 8; i++) अणु
			u32 v;
			v = FLD_VAL(v_coef[i].hc0_vc00, 7, 0)
				| FLD_VAL(v_coef[i].hc4_vc22, 15, 8);
			अगर (color_comp == DISPC_COLOR_COMPONENT_RGB_Y)
				dispc_ovl_ग_लिखो_firv_reg(dispc, plane, i, v);
			अन्यथा
				dispc_ovl_ग_लिखो_firv2_reg(dispc, plane, i, v);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा csc_coef_yuv2rgb अणु
	पूर्णांक ry, rcb, rcr, gy, gcb, gcr, by, bcb, bcr;
	bool full_range;
पूर्ण;

काष्ठा csc_coef_rgb2yuv अणु
	पूर्णांक yr, yg, yb, cbr, cbg, cbb, crr, crg, crb;
	bool full_range;
पूर्ण;

अटल व्योम dispc_ovl_ग_लिखो_color_conv_coef(काष्ठा dispc_device *dispc,
					    क्रमागत omap_plane_id plane,
					    स्थिर काष्ठा csc_coef_yuv2rgb *ct)
अणु
#घोषणा CVAL(x, y) (FLD_VAL(x, 26, 16) | FLD_VAL(y, 10, 0))

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_CONV_COEF(plane, 0), CVAL(ct->rcr, ct->ry));
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_CONV_COEF(plane, 1), CVAL(ct->gy,  ct->rcb));
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_CONV_COEF(plane, 2), CVAL(ct->gcb, ct->gcr));
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_CONV_COEF(plane, 3), CVAL(ct->bcr, ct->by));
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_CONV_COEF(plane, 4), CVAL(0, ct->bcb));

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), ct->full_range, 11, 11);

#अघोषित CVAL
पूर्ण

/* YUV -> RGB, ITU-R BT.601, full range */
अटल स्थिर काष्ठा csc_coef_yuv2rgb coefs_yuv2rgb_bt601_full = अणु
	256,   0,  358,		/* ry, rcb, rcr |1.000  0.000  1.402|*/
	256, -88, -182,		/* gy, gcb, gcr |1.000 -0.344 -0.714|*/
	256, 452,    0,		/* by, bcb, bcr |1.000  1.772  0.000|*/
	true,			/* full range */
पूर्ण;

/* YUV -> RGB, ITU-R BT.601, limited range */
अटल स्थिर काष्ठा csc_coef_yuv2rgb coefs_yuv2rgb_bt601_lim = अणु
	298,    0,  409,	/* ry, rcb, rcr |1.164  0.000  1.596|*/
	298, -100, -208,	/* gy, gcb, gcr |1.164 -0.392 -0.813|*/
	298,  516,    0,	/* by, bcb, bcr |1.164  2.017  0.000|*/
	false,			/* limited range */
पूर्ण;

/* YUV -> RGB, ITU-R BT.709, full range */
अटल स्थिर काष्ठा csc_coef_yuv2rgb coefs_yuv2rgb_bt709_full = अणु
	256,    0,  402,        /* ry, rcb, rcr |1.000  0.000  1.570|*/
	256,  -48, -120,        /* gy, gcb, gcr |1.000 -0.187 -0.467|*/
	256,  475,    0,        /* by, bcb, bcr |1.000  1.856  0.000|*/
	true,                   /* full range */
पूर्ण;

/* YUV -> RGB, ITU-R BT.709, limited range */
अटल स्थिर काष्ठा csc_coef_yuv2rgb coefs_yuv2rgb_bt709_lim = अणु
	298,    0,  459,	/* ry, rcb, rcr |1.164  0.000  1.793|*/
	298,  -55, -136,	/* gy, gcb, gcr |1.164 -0.213 -0.533|*/
	298,  541,    0,	/* by, bcb, bcr |1.164  2.112  0.000|*/
	false,			/* limited range */
पूर्ण;

अटल व्योम dispc_ovl_set_csc(काष्ठा dispc_device *dispc,
			      क्रमागत omap_plane_id plane,
			      क्रमागत drm_color_encoding color_encoding,
			      क्रमागत drm_color_range color_range)
अणु
	स्थिर काष्ठा csc_coef_yuv2rgb *csc;

	चयन (color_encoding) अणु
	शेष:
	हाल DRM_COLOR_YCBCR_BT601:
		अगर (color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			csc = &coefs_yuv2rgb_bt601_full;
		अन्यथा
			csc = &coefs_yuv2rgb_bt601_lim;
		अवरोध;
	हाल DRM_COLOR_YCBCR_BT709:
		अगर (color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			csc = &coefs_yuv2rgb_bt709_full;
		अन्यथा
			csc = &coefs_yuv2rgb_bt709_lim;
		अवरोध;
	पूर्ण

	dispc_ovl_ग_लिखो_color_conv_coef(dispc, plane, csc);
पूर्ण

अटल व्योम dispc_ovl_set_ba0(काष्ठा dispc_device *dispc,
			      क्रमागत omap_plane_id plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_BA0(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba1(काष्ठा dispc_device *dispc,
			      क्रमागत omap_plane_id plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_BA1(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba0_uv(काष्ठा dispc_device *dispc,
				 क्रमागत omap_plane_id plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_BA0_UV(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba1_uv(काष्ठा dispc_device *dispc,
				 क्रमागत omap_plane_id plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_BA1_UV(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_pos(काष्ठा dispc_device *dispc,
			      क्रमागत omap_plane_id plane,
			      क्रमागत omap_overlay_caps caps, पूर्णांक x, पूर्णांक y)
अणु
	u32 val;

	अगर ((caps & OMAP_DSS_OVL_CAP_POS) == 0)
		वापस;

	val = FLD_VAL(y, 26, 16) | FLD_VAL(x, 10, 0);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_POSITION(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_input_size(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane, पूर्णांक width,
				     पूर्णांक height)
अणु
	u32 val = FLD_VAL(height - 1, 26, 16) | FLD_VAL(width - 1, 10, 0);

	अगर (plane == OMAP_DSS_GFX || plane == OMAP_DSS_WB)
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_SIZE(plane), val);
	अन्यथा
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_PICTURE_SIZE(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_output_size(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक width,
				      पूर्णांक height)
अणु
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = FLD_VAL(height - 1, 26, 16) | FLD_VAL(width - 1, 10, 0);

	अगर (plane == OMAP_DSS_WB)
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_PICTURE_SIZE(plane), val);
	अन्यथा
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_SIZE(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_zorder(काष्ठा dispc_device *dispc,
				 क्रमागत omap_plane_id plane,
				 क्रमागत omap_overlay_caps caps, u8 zorder)
अणु
	अगर ((caps & OMAP_DSS_OVL_CAP_ZORDER) == 0)
		वापस;

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), zorder, 27, 26);
पूर्ण

अटल व्योम dispc_ovl_enable_zorder_planes(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक i;

	अगर (!dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		वापस;

	क्रम (i = 0; i < dispc_get_num_ovls(dispc); i++)
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(i), 1, 25, 25);
पूर्ण

अटल व्योम dispc_ovl_set_pre_mult_alpha(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane,
					 क्रमागत omap_overlay_caps caps,
					 bool enable)
अणु
	अगर ((caps & OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA) == 0)
		वापस;

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), enable ? 1 : 0, 28, 28);
पूर्ण

अटल व्योम dispc_ovl_setup_global_alpha(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane,
					 क्रमागत omap_overlay_caps caps,
					 u8 global_alpha)
अणु
	अटल स्थिर अचिन्हित पूर्णांक shअगरts[] = अणु 0, 8, 16, 24, पूर्ण;
	पूर्णांक shअगरt;

	अगर ((caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
		वापस;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(dispc, DISPC_GLOBAL_ALPHA, global_alpha, shअगरt + 7, shअगरt);
पूर्ण

अटल व्योम dispc_ovl_set_pix_inc(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane, s32 inc)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_PIXEL_INC(plane), inc);
पूर्ण

अटल व्योम dispc_ovl_set_row_inc(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane, s32 inc)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ROW_INC(plane), inc);
पूर्ण

अटल व्योम dispc_ovl_set_color_mode(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane, u32 fourcc)
अणु
	u32 m = 0;
	अगर (plane != OMAP_DSS_GFX) अणु
		चयन (fourcc) अणु
		हाल DRM_FORMAT_NV12:
			m = 0x0; अवरोध;
		हाल DRM_FORMAT_XRGB4444:
			m = 0x1; अवरोध;
		हाल DRM_FORMAT_RGBA4444:
			m = 0x2; अवरोध;
		हाल DRM_FORMAT_RGBX4444:
			m = 0x4; अवरोध;
		हाल DRM_FORMAT_ARGB4444:
			m = 0x5; अवरोध;
		हाल DRM_FORMAT_RGB565:
			m = 0x6; अवरोध;
		हाल DRM_FORMAT_ARGB1555:
			m = 0x7; अवरोध;
		हाल DRM_FORMAT_XRGB8888:
			m = 0x8; अवरोध;
		हाल DRM_FORMAT_RGB888:
			m = 0x9; अवरोध;
		हाल DRM_FORMAT_YUYV:
			m = 0xa; अवरोध;
		हाल DRM_FORMAT_UYVY:
			m = 0xb; अवरोध;
		हाल DRM_FORMAT_ARGB8888:
			m = 0xc; अवरोध;
		हाल DRM_FORMAT_RGBA8888:
			m = 0xd; अवरोध;
		हाल DRM_FORMAT_RGBX8888:
			m = 0xe; अवरोध;
		हाल DRM_FORMAT_XRGB1555:
			m = 0xf; अवरोध;
		शेष:
			BUG(); वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (fourcc) अणु
		हाल DRM_FORMAT_RGBX4444:
			m = 0x4; अवरोध;
		हाल DRM_FORMAT_ARGB4444:
			m = 0x5; अवरोध;
		हाल DRM_FORMAT_RGB565:
			m = 0x6; अवरोध;
		हाल DRM_FORMAT_ARGB1555:
			m = 0x7; अवरोध;
		हाल DRM_FORMAT_XRGB8888:
			m = 0x8; अवरोध;
		हाल DRM_FORMAT_RGB888:
			m = 0x9; अवरोध;
		हाल DRM_FORMAT_XRGB4444:
			m = 0xa; अवरोध;
		हाल DRM_FORMAT_RGBA4444:
			m = 0xb; अवरोध;
		हाल DRM_FORMAT_ARGB8888:
			m = 0xc; अवरोध;
		हाल DRM_FORMAT_RGBA8888:
			m = 0xd; अवरोध;
		हाल DRM_FORMAT_RGBX8888:
			m = 0xe; अवरोध;
		हाल DRM_FORMAT_XRGB1555:
			m = 0xf; अवरोध;
		शेष:
			BUG(); वापस;
		पूर्ण
	पूर्ण

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), m, 4, 1);
पूर्ण

अटल व्योम dispc_ovl_configure_burst_type(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane,
					   क्रमागत omap_dss_rotation_type rotation)
अणु
	अगर (dispc_has_feature(dispc, FEAT_BURST_2D) == 0)
		वापस;

	अगर (rotation == OMAP_DSS_ROT_TILER)
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), 1, 29, 29);
	अन्यथा
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), 0, 29, 29);
पूर्ण

अटल व्योम dispc_ovl_set_channel_out(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane,
				      क्रमागत omap_channel channel)
अणु
	पूर्णांक shअगरt;
	u32 val;
	पूर्णांक chan = 0, chan2 = 0;

	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		shअगरt = 8;
		अवरोध;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
	हाल OMAP_DSS_VIDEO3:
		shअगरt = 16;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	val = dispc_पढ़ो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2)) अणु
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
			chan = 0;
			chan2 = 0;
			अवरोध;
		हाल OMAP_DSS_CHANNEL_DIGIT:
			chan = 1;
			chan2 = 0;
			अवरोध;
		हाल OMAP_DSS_CHANNEL_LCD2:
			chan = 0;
			chan2 = 1;
			अवरोध;
		हाल OMAP_DSS_CHANNEL_LCD3:
			अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3)) अणु
				chan = 0;
				chan2 = 2;
			पूर्ण अन्यथा अणु
				BUG();
				वापस;
			पूर्ण
			अवरोध;
		हाल OMAP_DSS_CHANNEL_WB:
			chan = 0;
			chan2 = 3;
			अवरोध;
		शेष:
			BUG();
			वापस;
		पूर्ण

		val = FLD_MOD(val, chan, shअगरt, shअगरt);
		val = FLD_MOD(val, chan2, 31, 30);
	पूर्ण अन्यथा अणु
		val = FLD_MOD(val, channel, shअगरt, shअगरt);
	पूर्ण
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), val);
पूर्ण

अटल क्रमागत omap_channel dispc_ovl_get_channel_out(काष्ठा dispc_device *dispc,
						   क्रमागत omap_plane_id plane)
अणु
	पूर्णांक shअगरt;
	u32 val;

	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		shअगरt = 8;
		अवरोध;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
	हाल OMAP_DSS_VIDEO3:
		shअगरt = 16;
		अवरोध;
	शेष:
		BUG();
		वापस 0;
	पूर्ण

	val = dispc_पढ़ो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));

	अगर (FLD_GET(val, shअगरt, shअगरt) == 1)
		वापस OMAP_DSS_CHANNEL_DIGIT;

	अगर (!dispc_has_feature(dispc, FEAT_MGR_LCD2))
		वापस OMAP_DSS_CHANNEL_LCD;

	चयन (FLD_GET(val, 31, 30)) अणु
	हाल 0:
	शेष:
		वापस OMAP_DSS_CHANNEL_LCD;
	हाल 1:
		वापस OMAP_DSS_CHANNEL_LCD2;
	हाल 2:
		वापस OMAP_DSS_CHANNEL_LCD3;
	हाल 3:
		वापस OMAP_DSS_CHANNEL_WB;
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_burst_size(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane,
				     क्रमागत omap_burst_size burst_size)
अणु
	अटल स्थिर अचिन्हित पूर्णांक shअगरts[] = अणु 6, 14, 14, 14, 14, पूर्ण;
	पूर्णांक shअगरt;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), burst_size,
		    shअगरt + 1, shअगरt);
पूर्ण

अटल व्योम dispc_configure_burst_sizes(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक burst_size = BURST_SIZE_X8;

	/* Configure burst size always to maximum size */
	क्रम (i = 0; i < dispc_get_num_ovls(dispc); ++i)
		dispc_ovl_set_burst_size(dispc, i, burst_size);
	अगर (dispc->feat->has_ग_लिखोback)
		dispc_ovl_set_burst_size(dispc, OMAP_DSS_WB, burst_size);
पूर्ण

अटल u32 dispc_ovl_get_burst_size(काष्ठा dispc_device *dispc,
				    क्रमागत omap_plane_id plane)
अणु
	/* burst multiplier is always x8 (see dispc_configure_burst_sizes()) */
	वापस dispc->feat->burst_size_unit * 8;
पूर्ण

अटल bool dispc_ovl_color_mode_supported(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane, u32 fourcc)
अणु
	स्थिर u32 *modes;
	अचिन्हित पूर्णांक i;

	modes = dispc->feat->supported_color_modes[plane];

	क्रम (i = 0; modes[i]; ++i) अणु
		अगर (modes[i] == fourcc)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

स्थिर u32 *dispc_ovl_get_color_modes(काष्ठा dispc_device *dispc,
					    क्रमागत omap_plane_id plane)
अणु
	वापस dispc->feat->supported_color_modes[plane];
पूर्ण

अटल व्योम dispc_mgr_enable_cpr(काष्ठा dispc_device *dispc,
				 क्रमागत omap_channel channel, bool enable)
अणु
	अगर (channel == OMAP_DSS_CHANNEL_DIGIT)
		वापस;

	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_CPR, enable);
पूर्ण

अटल व्योम dispc_mgr_set_cpr_coef(काष्ठा dispc_device *dispc,
				   क्रमागत omap_channel channel,
				   स्थिर काष्ठा omap_dss_cpr_coefs *coefs)
अणु
	u32 coef_r, coef_g, coef_b;

	अगर (!dss_mgr_is_lcd(channel))
		वापस;

	coef_r = FLD_VAL(coefs->rr, 31, 22) | FLD_VAL(coefs->rg, 20, 11) |
		FLD_VAL(coefs->rb, 9, 0);
	coef_g = FLD_VAL(coefs->gr, 31, 22) | FLD_VAL(coefs->gg, 20, 11) |
		FLD_VAL(coefs->gb, 9, 0);
	coef_b = FLD_VAL(coefs->br, 31, 22) | FLD_VAL(coefs->bg, 20, 11) |
		FLD_VAL(coefs->bb, 9, 0);

	dispc_ग_लिखो_reg(dispc, DISPC_CPR_COEF_R(channel), coef_r);
	dispc_ग_लिखो_reg(dispc, DISPC_CPR_COEF_G(channel), coef_g);
	dispc_ग_लिखो_reg(dispc, DISPC_CPR_COEF_B(channel), coef_b);
पूर्ण

अटल व्योम dispc_ovl_set_vid_color_conv(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane, bool enable)
अणु
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = dispc_पढ़ो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));
	val = FLD_MOD(val, enable, 9, 9);
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), val);
पूर्ण

अटल व्योम dispc_ovl_enable_replication(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane,
					 क्रमागत omap_overlay_caps caps,
					 bool enable)
अणु
	अटल स्थिर अचिन्हित पूर्णांक shअगरts[] = अणु 5, 10, 10, 10 पूर्ण;
	पूर्णांक shअगरt;

	अगर ((caps & OMAP_DSS_OVL_CAP_REPLICATION) == 0)
		वापस;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), enable, shअगरt, shअगरt);
पूर्ण

अटल व्योम dispc_mgr_set_size(काष्ठा dispc_device *dispc,
			       क्रमागत omap_channel channel, u16 width, u16 height)
अणु
	u32 val;

	val = FLD_VAL(height - 1, dispc->feat->mgr_height_start, 16) |
		FLD_VAL(width - 1, dispc->feat->mgr_width_start, 0);

	dispc_ग_लिखो_reg(dispc, DISPC_SIZE_MGR(channel), val);
पूर्ण

अटल व्योम dispc_init_fअगरos(काष्ठा dispc_device *dispc)
अणु
	u32 size;
	पूर्णांक fअगरo;
	u8 start, end;
	u32 unit;
	पूर्णांक i;

	unit = dispc->feat->buffer_size_unit;

	dispc_get_reg_field(dispc, FEAT_REG_FIFOSIZE, &start, &end);

	क्रम (fअगरo = 0; fअगरo < dispc->feat->num_fअगरos; ++fअगरo) अणु
		size = REG_GET(dispc, DISPC_OVL_FIFO_SIZE_STATUS(fअगरo),
			       start, end);
		size *= unit;
		dispc->fअगरo_size[fअगरo] = size;

		/*
		 * By शेष fअगरos are mapped directly to overlays, fअगरo 0 to
		 * ovl 0, fअगरo 1 to ovl 1, etc.
		 */
		dispc->fअगरo_assignment[fअगरo] = fअगरo;
	पूर्ण

	/*
	 * The GFX fअगरo on OMAP4 is smaller than the other fअगरos. The small fअगरo
	 * causes problems with certain use हालs, like using the tiler in 2D
	 * mode. The below hack swaps the fअगरos of GFX and WB planes, thus
	 * giving GFX plane a larger fअगरo. WB but should work fine with a
	 * smaller fअगरo.
	 */
	अगर (dispc->feat->gfx_fअगरo_workaround) अणु
		u32 v;

		v = dispc_पढ़ो_reg(dispc, DISPC_GLOBAL_BUFFER);

		v = FLD_MOD(v, 4, 2, 0); /* GFX BUF top to WB */
		v = FLD_MOD(v, 4, 5, 3); /* GFX BUF bottom to WB */
		v = FLD_MOD(v, 0, 26, 24); /* WB BUF top to GFX */
		v = FLD_MOD(v, 0, 29, 27); /* WB BUF bottom to GFX */

		dispc_ग_लिखो_reg(dispc, DISPC_GLOBAL_BUFFER, v);

		dispc->fअगरo_assignment[OMAP_DSS_GFX] = OMAP_DSS_WB;
		dispc->fअगरo_assignment[OMAP_DSS_WB] = OMAP_DSS_GFX;
	पूर्ण

	/*
	 * Setup शेष fअगरo thresholds.
	 */
	क्रम (i = 0; i < dispc_get_num_ovls(dispc); ++i) अणु
		u32 low, high;
		स्थिर bool use_fअगरomerge = false;
		स्थिर bool manual_update = false;

		dispc_ovl_compute_fअगरo_thresholds(dispc, i, &low, &high,
						  use_fअगरomerge, manual_update);

		dispc_ovl_set_fअगरo_threshold(dispc, i, low, high);
	पूर्ण

	अगर (dispc->feat->has_ग_लिखोback) अणु
		u32 low, high;
		स्थिर bool use_fअगरomerge = false;
		स्थिर bool manual_update = false;

		dispc_ovl_compute_fअगरo_thresholds(dispc, OMAP_DSS_WB,
						  &low, &high, use_fअगरomerge,
						  manual_update);

		dispc_ovl_set_fअगरo_threshold(dispc, OMAP_DSS_WB, low, high);
	पूर्ण
पूर्ण

अटल u32 dispc_ovl_get_fअगरo_size(काष्ठा dispc_device *dispc,
				   क्रमागत omap_plane_id plane)
अणु
	पूर्णांक fअगरo;
	u32 size = 0;

	क्रम (fअगरo = 0; fअगरo < dispc->feat->num_fअगरos; ++fअगरo) अणु
		अगर (dispc->fअगरo_assignment[fअगरo] == plane)
			size += dispc->fअगरo_size[fअगरo];
	पूर्ण

	वापस size;
पूर्ण

व्योम dispc_ovl_set_fअगरo_threshold(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane,
				  u32 low, u32 high)
अणु
	u8 hi_start, hi_end, lo_start, lo_end;
	u32 unit;

	unit = dispc->feat->buffer_size_unit;

	WARN_ON(low % unit != 0);
	WARN_ON(high % unit != 0);

	low /= unit;
	high /= unit;

	dispc_get_reg_field(dispc, FEAT_REG_FIFOHIGHTHRESHOLD,
			    &hi_start, &hi_end);
	dispc_get_reg_field(dispc, FEAT_REG_FIFOLOWTHRESHOLD,
			    &lo_start, &lo_end);

	DSSDBG("fifo(%d) threshold (bytes), old %u/%u, new %u/%u\n",
			plane,
			REG_GET(dispc, DISPC_OVL_FIFO_THRESHOLD(plane),
				lo_start, lo_end) * unit,
			REG_GET(dispc, DISPC_OVL_FIFO_THRESHOLD(plane),
				hi_start, hi_end) * unit,
			low * unit, high * unit);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIFO_THRESHOLD(plane),
			FLD_VAL(high, hi_start, hi_end) |
			FLD_VAL(low, lo_start, lo_end));

	/*
	 * configure the preload to the pipeline's high threhold, if HT it's too
	 * large क्रम the preload field, set the threshold to the maximum value
	 * that can be held by the preload रेजिस्टर
	 */
	अगर (dispc_has_feature(dispc, FEAT_PRELOAD) &&
	    dispc->feat->set_max_preload && plane != OMAP_DSS_WB)
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_PRELOAD(plane),
				min(high, 0xfffu));
पूर्ण

व्योम dispc_enable_fअगरomerge(काष्ठा dispc_device *dispc, bool enable)
अणु
	अगर (!dispc_has_feature(dispc, FEAT_FIFO_MERGE)) अणु
		WARN_ON(enable);
		वापस;
	पूर्ण

	DSSDBG("FIFO merge %s\n", enable ? "enabled" : "disabled");
	REG_FLD_MOD(dispc, DISPC_CONFIG, enable ? 1 : 0, 14, 14);
पूर्ण

व्योम dispc_ovl_compute_fअगरo_thresholds(काष्ठा dispc_device *dispc,
				       क्रमागत omap_plane_id plane,
				       u32 *fअगरo_low, u32 *fअगरo_high,
				       bool use_fअगरomerge, bool manual_update)
अणु
	/*
	 * All sizes are in bytes. Both the buffer and burst are made of
	 * buffer_units, and the fअगरo thresholds must be buffer_unit aligned.
	 */
	अचिन्हित पूर्णांक buf_unit = dispc->feat->buffer_size_unit;
	अचिन्हित पूर्णांक ovl_fअगरo_size, total_fअगरo_size, burst_size;
	पूर्णांक i;

	burst_size = dispc_ovl_get_burst_size(dispc, plane);
	ovl_fअगरo_size = dispc_ovl_get_fअगरo_size(dispc, plane);

	अगर (use_fअगरomerge) अणु
		total_fअगरo_size = 0;
		क्रम (i = 0; i < dispc_get_num_ovls(dispc); ++i)
			total_fअगरo_size += dispc_ovl_get_fअगरo_size(dispc, i);
	पूर्ण अन्यथा अणु
		total_fअगरo_size = ovl_fअगरo_size;
	पूर्ण

	/*
	 * We use the same low threshold क्रम both fअगरomerge and non-fअगरomerge
	 * हालs, but क्रम fअगरomerge we calculate the high threshold using the
	 * combined fअगरo size
	 */

	अगर (manual_update && dispc_has_feature(dispc, FEAT_OMAP3_DSI_FIFO_BUG)) अणु
		*fअगरo_low = ovl_fअगरo_size - burst_size * 2;
		*fअगरo_high = total_fअगरo_size - burst_size;
	पूर्ण अन्यथा अगर (plane == OMAP_DSS_WB) अणु
		/*
		 * Most optimal configuration क्रम ग_लिखोback is to push out data
		 * to the पूर्णांकerconnect the moment ग_लिखोback pushes enough pixels
		 * in the FIFO to क्रमm a burst
		 */
		*fअगरo_low = 0;
		*fअगरo_high = burst_size;
	पूर्ण अन्यथा अणु
		*fअगरo_low = ovl_fअगरo_size - burst_size;
		*fअगरo_high = total_fअगरo_size - buf_unit;
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_mflag(काष्ठा dispc_device *dispc,
				क्रमागत omap_plane_id plane, bool enable)
अणु
	पूर्णांक bit;

	अगर (plane == OMAP_DSS_GFX)
		bit = 14;
	अन्यथा
		bit = 23;

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), enable, bit, bit);
पूर्ण

अटल व्योम dispc_ovl_set_mflag_threshold(काष्ठा dispc_device *dispc,
					  क्रमागत omap_plane_id plane,
					  पूर्णांक low, पूर्णांक high)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_MFLAG_THRESHOLD(plane),
		FLD_VAL(high, 31, 16) |	FLD_VAL(low, 15, 0));
पूर्ण

अटल व्योम dispc_init_mflag(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक i;

	/*
	 * HACK: NV12 color क्रमmat and MFLAG seem to have problems working
	 * together: using two displays, and having an NV12 overlay on one of
	 * the displays will cause underflows/synclosts when MFLAG_CTRL=2.
	 * Changing MFLAG thresholds and PRELOAD to certain values seem to
	 * हटाओ the errors, but there करोesn't seem to be a clear logic on
	 * which values work and which not.
	 *
	 * As a work-around, set क्रमce MFLAG to always on.
	 */
	dispc_ग_लिखो_reg(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE,
		(1 << 0) |	/* MFLAG_CTRL = क्रमce always on */
		(0 << 2));	/* MFLAG_START = disable */

	क्रम (i = 0; i < dispc_get_num_ovls(dispc); ++i) अणु
		u32 size = dispc_ovl_get_fअगरo_size(dispc, i);
		u32 unit = dispc->feat->buffer_size_unit;
		u32 low, high;

		dispc_ovl_set_mflag(dispc, i, true);

		/*
		 * Simulation team suggests below thesholds:
		 * HT = fअगरosize * 5 / 8;
		 * LT = fअगरosize * 4 / 8;
		 */

		low = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovl_set_mflag_threshold(dispc, i, low, high);
	पूर्ण

	अगर (dispc->feat->has_ग_लिखोback) अणु
		u32 size = dispc_ovl_get_fअगरo_size(dispc, OMAP_DSS_WB);
		u32 unit = dispc->feat->buffer_size_unit;
		u32 low, high;

		dispc_ovl_set_mflag(dispc, OMAP_DSS_WB, true);

		/*
		 * Simulation team suggests below thesholds:
		 * HT = fअगरosize * 5 / 8;
		 * LT = fअगरosize * 4 / 8;
		 */

		low = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovl_set_mflag_threshold(dispc, OMAP_DSS_WB, low, high);
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_fir(काष्ठा dispc_device *dispc,
			      क्रमागत omap_plane_id plane,
			      पूर्णांक hinc, पूर्णांक vinc,
			      क्रमागत omap_color_component color_comp)
अणु
	u32 val;

	अगर (color_comp == DISPC_COLOR_COMPONENT_RGB_Y) अणु
		u8 hinc_start, hinc_end, vinc_start, vinc_end;

		dispc_get_reg_field(dispc, FEAT_REG_FIRHINC,
				    &hinc_start, &hinc_end);
		dispc_get_reg_field(dispc, FEAT_REG_FIRVINC,
				    &vinc_start, &vinc_end);
		val = FLD_VAL(vinc, vinc_start, vinc_end) |
				FLD_VAL(hinc, hinc_start, hinc_end);

		dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR(plane), val);
	पूर्ण अन्यथा अणु
		val = FLD_VAL(vinc, 28, 16) | FLD_VAL(hinc, 12, 0);
		dispc_ग_लिखो_reg(dispc, DISPC_OVL_FIR2(plane), val);
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu0(काष्ठा dispc_device *dispc,
				    क्रमागत omap_plane_id plane, पूर्णांक haccu,
				    पूर्णांक vaccu)
अणु
	u32 val;
	u8 hor_start, hor_end, vert_start, vert_end;

	dispc_get_reg_field(dispc, FEAT_REG_HORIZONTALACCU,
			    &hor_start, &hor_end);
	dispc_get_reg_field(dispc, FEAT_REG_VERTICALACCU,
			    &vert_start, &vert_end);

	val = FLD_VAL(vaccu, vert_start, vert_end) |
			FLD_VAL(haccu, hor_start, hor_end);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ACCU0(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu1(काष्ठा dispc_device *dispc,
				    क्रमागत omap_plane_id plane, पूर्णांक haccu,
				    पूर्णांक vaccu)
अणु
	u32 val;
	u8 hor_start, hor_end, vert_start, vert_end;

	dispc_get_reg_field(dispc, FEAT_REG_HORIZONTALACCU,
			    &hor_start, &hor_end);
	dispc_get_reg_field(dispc, FEAT_REG_VERTICALACCU,
			    &vert_start, &vert_end);

	val = FLD_VAL(vaccu, vert_start, vert_end) |
			FLD_VAL(haccu, hor_start, hor_end);

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ACCU1(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu2_0(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक haccu,
				      पूर्णांक vaccu)
अणु
	u32 val;

	val = FLD_VAL(vaccu, 26, 16) | FLD_VAL(haccu, 10, 0);
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ACCU2_0(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu2_1(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane, पूर्णांक haccu,
				      पूर्णांक vaccu)
अणु
	u32 val;

	val = FLD_VAL(vaccu, 26, 16) | FLD_VAL(haccu, 10, 0);
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ACCU2_1(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_scale_param(काष्ठा dispc_device *dispc,
				      क्रमागत omap_plane_id plane,
				      u16 orig_width, u16 orig_height,
				      u16 out_width, u16 out_height,
				      bool five_taps, u8 rotation,
				      क्रमागत omap_color_component color_comp)
अणु
	पूर्णांक fir_hinc, fir_vinc;

	fir_hinc = 1024 * orig_width / out_width;
	fir_vinc = 1024 * orig_height / out_height;

	dispc_ovl_set_scale_coef(dispc, plane, fir_hinc, fir_vinc, five_taps,
				 color_comp);
	dispc_ovl_set_fir(dispc, plane, fir_hinc, fir_vinc, color_comp);
पूर्ण

अटल व्योम dispc_ovl_set_accu_uv(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane,
				  u16 orig_width, u16 orig_height,
				  u16 out_width, u16 out_height,
				  bool ilace, u32 fourcc, u8 rotation)
अणु
	पूर्णांक h_accu2_0, h_accu2_1;
	पूर्णांक v_accu2_0, v_accu2_1;
	पूर्णांक chroma_hinc, chroma_vinc;
	पूर्णांक idx;

	काष्ठा accu अणु
		s8 h0_m, h0_n;
		s8 h1_m, h1_n;
		s8 v0_m, v0_n;
		s8 v1_m, v1_n;
	पूर्ण;

	स्थिर काष्ठा accu *accu_table;
	स्थिर काष्ठा accu *accu_val;

	अटल स्थिर काष्ठा accu accu_nv12[4] = अणु
		अणु  0, 1,  0, 1 , -1, 2, 0, 1 पूर्ण,
		अणु  1, 2, -3, 4 ,  0, 1, 0, 1 पूर्ण,
		अणु -1, 1,  0, 1 , -1, 2, 0, 1 पूर्ण,
		अणु -1, 2, -1, 2 , -1, 1, 0, 1 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा accu accu_nv12_ilace[4] = अणु
		अणु  0, 1,  0, 1 , -3, 4, -1, 4 पूर्ण,
		अणु -1, 4, -3, 4 ,  0, 1,  0, 1 पूर्ण,
		अणु -1, 1,  0, 1 , -1, 4, -3, 4 पूर्ण,
		अणु -3, 4, -3, 4 , -1, 1,  0, 1 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा accu accu_yuv[4] = अणु
		अणु  0, 1, 0, 1,  0, 1, 0, 1 पूर्ण,
		अणु  0, 1, 0, 1,  0, 1, 0, 1 पूर्ण,
		अणु -1, 1, 0, 1,  0, 1, 0, 1 पूर्ण,
		अणु  0, 1, 0, 1, -1, 1, 0, 1 पूर्ण,
	पूर्ण;

	/* Note: DSS HW rotates घड़ीwise, DRM_MODE_ROTATE_* counter-घड़ीwise */
	चयन (rotation & DRM_MODE_ROTATE_MASK) अणु
	शेष:
	हाल DRM_MODE_ROTATE_0:
		idx = 0;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		idx = 3;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		idx = 2;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		idx = 1;
		अवरोध;
	पूर्ण

	चयन (fourcc) अणु
	हाल DRM_FORMAT_NV12:
		अगर (ilace)
			accu_table = accu_nv12_ilace;
		अन्यथा
			accu_table = accu_nv12;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
		accu_table = accu_yuv;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	accu_val = &accu_table[idx];

	chroma_hinc = 1024 * orig_width / out_width;
	chroma_vinc = 1024 * orig_height / out_height;

	h_accu2_0 = (accu_val->h0_m * chroma_hinc / accu_val->h0_n) % 1024;
	h_accu2_1 = (accu_val->h1_m * chroma_hinc / accu_val->h1_n) % 1024;
	v_accu2_0 = (accu_val->v0_m * chroma_vinc / accu_val->v0_n) % 1024;
	v_accu2_1 = (accu_val->v1_m * chroma_vinc / accu_val->v1_n) % 1024;

	dispc_ovl_set_vid_accu2_0(dispc, plane, h_accu2_0, v_accu2_0);
	dispc_ovl_set_vid_accu2_1(dispc, plane, h_accu2_1, v_accu2_1);
पूर्ण

अटल व्योम dispc_ovl_set_scaling_common(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane,
					 u16 orig_width, u16 orig_height,
					 u16 out_width, u16 out_height,
					 bool ilace, bool five_taps,
					 bool fieldmode, u32 fourcc,
					 u8 rotation)
अणु
	पूर्णांक accu0 = 0;
	पूर्णांक accu1 = 0;
	u32 l;

	dispc_ovl_set_scale_param(dispc, plane, orig_width, orig_height,
				  out_width, out_height, five_taps,
				  rotation, DISPC_COLOR_COMPONENT_RGB_Y);
	l = dispc_पढ़ो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));

	/* RESIZEENABLE and VERTICALTAPS */
	l &= ~((0x3 << 5) | (0x1 << 21));
	l |= (orig_width != out_width) ? (1 << 5) : 0;
	l |= (orig_height != out_height) ? (1 << 6) : 0;
	l |= five_taps ? (1 << 21) : 0;

	/* VRESIZECONF and HRESIZECONF */
	अगर (dispc_has_feature(dispc, FEAT_RESIZECONF)) अणु
		l &= ~(0x3 << 7);
		l |= (orig_width <= out_width) ? 0 : (1 << 7);
		l |= (orig_height <= out_height) ? 0 : (1 << 8);
	पूर्ण

	/* LINEBUFFERSPLIT */
	अगर (dispc_has_feature(dispc, FEAT_LINEBUFFERSPLIT)) अणु
		l &= ~(0x1 << 22);
		l |= five_taps ? (1 << 22) : 0;
	पूर्ण

	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), l);

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	अगर (ilace && !fieldmode) अणु
		accu1 = 0;
		accu0 = ((1024 * orig_height / out_height) / 2) & 0x3ff;
		अगर (accu0 >= 1024/2) अणु
			accu1 = 1024/2;
			accu0 -= accu1;
		पूर्ण
	पूर्ण

	dispc_ovl_set_vid_accu0(dispc, plane, 0, accu0);
	dispc_ovl_set_vid_accu1(dispc, plane, 0, accu1);
पूर्ण

अटल व्योम dispc_ovl_set_scaling_uv(काष्ठा dispc_device *dispc,
				     क्रमागत omap_plane_id plane,
				     u16 orig_width, u16 orig_height,
				     u16 out_width, u16 out_height,
				     bool ilace, bool five_taps,
				     bool fieldmode, u32 fourcc,
				     u8 rotation)
अणु
	पूर्णांक scale_x = out_width != orig_width;
	पूर्णांक scale_y = out_height != orig_height;
	bool chroma_upscale = plane != OMAP_DSS_WB;
	स्थिर काष्ठा drm_क्रमmat_info *info;

	info = drm_क्रमmat_info(fourcc);

	अगर (!dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE))
		वापस;

	अगर (!info->is_yuv) अणु
		/* reset chroma resampling क्रम RGB क्रमmats  */
		अगर (plane != OMAP_DSS_WB)
			REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane),
				    0, 8, 8);
		वापस;
	पूर्ण

	dispc_ovl_set_accu_uv(dispc, plane, orig_width, orig_height, out_width,
			      out_height, ilace, fourcc, rotation);

	चयन (fourcc) अणु
	हाल DRM_FORMAT_NV12:
		अगर (chroma_upscale) अणु
			/* UV is subsampled by 2 horizontally and vertically */
			orig_height >>= 1;
			orig_width >>= 1;
		पूर्ण अन्यथा अणु
			/* UV is करोwnsampled by 2 horizontally and vertically */
			orig_height <<= 1;
			orig_width <<= 1;
		पूर्ण

		अवरोध;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
		/* For YUV422 with 90/270 rotation, we करोn't upsample chroma */
		अगर (!drm_rotation_90_or_270(rotation)) अणु
			अगर (chroma_upscale)
				/* UV is subsampled by 2 horizontally */
				orig_width >>= 1;
			अन्यथा
				/* UV is करोwnsampled by 2 horizontally */
				orig_width <<= 1;
		पूर्ण

		/* must use FIR क्रम YUV422 अगर rotated */
		अगर ((rotation & DRM_MODE_ROTATE_MASK) != DRM_MODE_ROTATE_0)
			scale_x = scale_y = true;

		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	अगर (out_width != orig_width)
		scale_x = true;
	अगर (out_height != orig_height)
		scale_y = true;

	dispc_ovl_set_scale_param(dispc, plane, orig_width, orig_height,
				  out_width, out_height, five_taps,
				  rotation, DISPC_COLOR_COMPONENT_UV);

	अगर (plane != OMAP_DSS_WB)
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane),
			(scale_x || scale_y) ? 1 : 0, 8, 8);

	/* set H scaling */
	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), scale_x ? 1 : 0, 5, 5);
	/* set V scaling */
	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), scale_y ? 1 : 0, 6, 6);
पूर्ण

अटल व्योम dispc_ovl_set_scaling(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane,
				  u16 orig_width, u16 orig_height,
				  u16 out_width, u16 out_height,
				  bool ilace, bool five_taps,
				  bool fieldmode, u32 fourcc,
				  u8 rotation)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ovl_set_scaling_common(dispc, plane, orig_width, orig_height,
				     out_width, out_height, ilace, five_taps,
				     fieldmode, fourcc, rotation);

	dispc_ovl_set_scaling_uv(dispc, plane, orig_width, orig_height,
				 out_width, out_height, ilace, five_taps,
				 fieldmode, fourcc, rotation);
पूर्ण

अटल व्योम dispc_ovl_set_rotation_attrs(काष्ठा dispc_device *dispc,
					 क्रमागत omap_plane_id plane, u8 rotation,
					 क्रमागत omap_dss_rotation_type rotation_type,
					 u32 fourcc)
अणु
	bool row_repeat = false;
	पूर्णांक vidrot = 0;

	/* Note: DSS HW rotates घड़ीwise, DRM_MODE_ROTATE_* counter-घड़ीwise */
	अगर (fourcc == DRM_FORMAT_YUYV || fourcc == DRM_FORMAT_UYVY) अणु

		अगर (rotation & DRM_MODE_REFLECT_X) अणु
			चयन (rotation & DRM_MODE_ROTATE_MASK) अणु
			हाल DRM_MODE_ROTATE_0:
				vidrot = 2;
				अवरोध;
			हाल DRM_MODE_ROTATE_90:
				vidrot = 1;
				अवरोध;
			हाल DRM_MODE_ROTATE_180:
				vidrot = 0;
				अवरोध;
			हाल DRM_MODE_ROTATE_270:
				vidrot = 3;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (rotation & DRM_MODE_ROTATE_MASK) अणु
			हाल DRM_MODE_ROTATE_0:
				vidrot = 0;
				अवरोध;
			हाल DRM_MODE_ROTATE_90:
				vidrot = 3;
				अवरोध;
			हाल DRM_MODE_ROTATE_180:
				vidrot = 2;
				अवरोध;
			हाल DRM_MODE_ROTATE_270:
				vidrot = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (drm_rotation_90_or_270(rotation))
			row_repeat = true;
		अन्यथा
			row_repeat = false;
	पूर्ण

	/*
	 * OMAP4/5 Errata i631:
	 * NV12 in 1D mode must use ROTATION=1. Otherwise DSS will fetch extra
	 * rows beyond the framebuffer, which may cause OCP error.
	 */
	अगर (fourcc == DRM_FORMAT_NV12 && rotation_type != OMAP_DSS_ROT_TILER)
		vidrot = 1;

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), vidrot, 13, 12);
	अगर (dispc_has_feature(dispc, FEAT_ROWREPEATENABLE))
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane),
			row_repeat ? 1 : 0, 18, 18);

	अगर (dispc_ovl_color_mode_supported(dispc, plane, DRM_FORMAT_NV12)) अणु
		bool द्विगुनstride =
			fourcc == DRM_FORMAT_NV12 &&
			rotation_type == OMAP_DSS_ROT_TILER &&
			!drm_rotation_90_or_270(rotation);

		/* DOUBLESTRIDE */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane),
			    द्विगुनstride, 22, 22);
	पूर्ण
पूर्ण

अटल पूर्णांक color_mode_to_bpp(u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल DRM_FORMAT_NV12:
		वापस 8;
	हाल DRM_FORMAT_RGBX4444:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_RGBA4444:
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		वापस 16;
	हाल DRM_FORMAT_RGB888:
		वापस 24;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_RGBA8888:
	हाल DRM_FORMAT_RGBX8888:
		वापस 32;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल s32 pixinc(पूर्णांक pixels, u8 ps)
अणु
	अगर (pixels == 1)
		वापस 1;
	अन्यथा अगर (pixels > 1)
		वापस 1 + (pixels - 1) * ps;
	अन्यथा अगर (pixels < 0)
		वापस 1 - (-pixels + 1) * ps;

	BUG();
पूर्ण

अटल व्योम calc_offset(u16 screen_width, u16 width,
		u32 fourcc, bool fieldmode, अचिन्हित पूर्णांक field_offset,
		अचिन्हित पूर्णांक *offset0, अचिन्हित पूर्णांक *offset1,
		s32 *row_inc, s32 *pix_inc, पूर्णांक x_predecim, पूर्णांक y_predecim,
		क्रमागत omap_dss_rotation_type rotation_type, u8 rotation)
अणु
	u8 ps;

	ps = color_mode_to_bpp(fourcc) / 8;

	DSSDBG("scrw %d, width %d\n", screen_width, width);

	अगर (rotation_type == OMAP_DSS_ROT_TILER &&
	    (fourcc == DRM_FORMAT_UYVY || fourcc == DRM_FORMAT_YUYV) &&
	    drm_rotation_90_or_270(rotation)) अणु
		/*
		 * HACK: ROW_INC needs to be calculated with TILER units.
		 * We get such 'screen_width' that multiplying it with the
		 * YUV422 pixel size gives the correct TILER container width.
		 * However, 'width' is in pixels and multiplying it with YUV422
		 * pixel size gives incorrect result. We thus multiply it here
		 * with 2 to match the 32 bit TILER unit size.
		 */
		width *= 2;
	पूर्ण

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	*offset0 = field_offset * screen_width * ps;
	*offset1 = 0;

	*row_inc = pixinc(1 + (y_predecim * screen_width - width * x_predecim) +
			(fieldmode ? screen_width : 0), ps);
	अगर (fourcc == DRM_FORMAT_YUYV || fourcc == DRM_FORMAT_UYVY)
		*pix_inc = pixinc(x_predecim, 2 * ps);
	अन्यथा
		*pix_inc = pixinc(x_predecim, ps);
पूर्ण

/*
 * This function is used to aव्योम synclosts in OMAP3, because of some
 * unकरोcumented horizontal position and timing related limitations.
 */
अटल पूर्णांक check_horiz_timing_omap3(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा videomode *vm, u16 pos_x,
		u16 width, u16 height, u16 out_width, u16 out_height,
		bool five_taps)
अणु
	स्थिर पूर्णांक ds = DIV_ROUND_UP(height, out_height);
	अचिन्हित दीर्घ nonactive;
	अटल स्थिर u8 limits[3] = अणु 8, 10, 20 पूर्ण;
	u64 val, blank;
	पूर्णांक i;

	nonactive = vm->hactive + vm->hfront_porch + vm->hsync_len +
		    vm->hback_porch - out_width;

	i = 0;
	अगर (out_height < height)
		i++;
	अगर (out_width < width)
		i++;
	blank = भाग_u64((u64)(vm->hback_porch + vm->hsync_len + vm->hfront_porch) *
			lclk, pclk);
	DSSDBG("blanking period + ppl = %llu (limit = %u)\n", blank, limits[i]);
	अगर (blank <= limits[i])
		वापस -EINVAL;

	/* FIXME add checks क्रम 3-tap filter once the limitations are known */
	अगर (!five_taps)
		वापस 0;

	/*
	 * Pixel data should be prepared beक्रमe visible display poपूर्णांक starts.
	 * So, atleast DS-2 lines must have alपढ़ोy been fetched by DISPC
	 * during nonactive - pos_x period.
	 */
	val = भाग_u64((u64)(nonactive - pos_x) * lclk, pclk);
	DSSDBG("(nonactive - pos_x) * pcd = %llu max(0, DS - 2) * width = %d\n",
		val, max(0, ds - 2) * width);
	अगर (val < max(0, ds - 2) * width)
		वापस -EINVAL;

	/*
	 * All lines need to be refilled during the nonactive period of which
	 * only one line can be loaded during the active period. So, atleast
	 * DS - 1 lines should be loaded during nonactive period.
	 */
	val =  भाग_u64((u64)nonactive * lclk, pclk);
	DSSDBG("nonactive * pcd  = %llu, max(0, DS - 1) * width = %d\n",
		val, max(0, ds - 1) * width);
	अगर (val < max(0, ds - 1) * width)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ calc_core_clk_five_taps(अचिन्हित दीर्घ pclk,
		स्थिर काष्ठा videomode *vm, u16 width,
		u16 height, u16 out_width, u16 out_height,
		u32 fourcc)
अणु
	u32 core_clk = 0;
	u64 पंचांगp;

	अगर (height <= out_height && width <= out_width)
		वापस (अचिन्हित दीर्घ) pclk;

	अगर (height > out_height) अणु
		अचिन्हित पूर्णांक ppl = vm->hactive;

		पंचांगp = (u64)pclk * height * out_width;
		करो_भाग(पंचांगp, 2 * out_height * ppl);
		core_clk = पंचांगp;

		अगर (height > 2 * out_height) अणु
			अगर (ppl == out_width)
				वापस 0;

			पंचांगp = (u64)pclk * (height - 2 * out_height) * out_width;
			करो_भाग(पंचांगp, 2 * out_height * (ppl - out_width));
			core_clk = max_t(u32, core_clk, पंचांगp);
		पूर्ण
	पूर्ण

	अगर (width > out_width) अणु
		पंचांगp = (u64)pclk * width;
		करो_भाग(पंचांगp, out_width);
		core_clk = max_t(u32, core_clk, पंचांगp);

		अगर (fourcc == DRM_FORMAT_XRGB8888)
			core_clk <<= 1;
	पूर्ण

	वापस core_clk;
पूर्ण

अटल अचिन्हित दीर्घ calc_core_clk_24xx(अचिन्हित दीर्घ pclk, u16 width,
		u16 height, u16 out_width, u16 out_height, bool mem_to_mem)
अणु
	अगर (height > out_height && width > out_width)
		वापस pclk * 4;
	अन्यथा
		वापस pclk * 2;
पूर्ण

अटल अचिन्हित दीर्घ calc_core_clk_34xx(अचिन्हित दीर्घ pclk, u16 width,
		u16 height, u16 out_width, u16 out_height, bool mem_to_mem)
अणु
	अचिन्हित पूर्णांक hf, vf;

	/*
	 * FIXME how to determine the 'A' factor
	 * क्रम the no करोwnscaling हाल ?
	 */

	अगर (width > 3 * out_width)
		hf = 4;
	अन्यथा अगर (width > 2 * out_width)
		hf = 3;
	अन्यथा अगर (width > out_width)
		hf = 2;
	अन्यथा
		hf = 1;
	अगर (height > out_height)
		vf = 2;
	अन्यथा
		vf = 1;

	वापस pclk * vf * hf;
पूर्ण

अटल अचिन्हित दीर्घ calc_core_clk_44xx(अचिन्हित दीर्घ pclk, u16 width,
		u16 height, u16 out_width, u16 out_height, bool mem_to_mem)
अणु
	/*
	 * If the overlay/ग_लिखोback is in mem to mem mode, there are no
	 * करोwnscaling limitations with respect to pixel घड़ी, वापस 1 as
	 * required core घड़ी to represent that we have sufficient enough
	 * core घड़ी to करो maximum करोwnscaling
	 */
	अगर (mem_to_mem)
		वापस 1;

	अगर (width > out_width)
		वापस DIV_ROUND_UP(pclk, out_width) * width;
	अन्यथा
		वापस pclk;
पूर्ण

अटल पूर्णांक dispc_ovl_calc_scaling_24xx(काष्ठा dispc_device *dispc,
				       अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
				       स्थिर काष्ठा videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fourcc, bool *five_taps,
				       पूर्णांक *x_predecim, पूर्णांक *y_predecim,
				       पूर्णांक *decim_x, पूर्णांक *decim_y,
				       u16 pos_x, अचिन्हित दीर्घ *core_clk,
				       bool mem_to_mem)
अणु
	पूर्णांक error;
	u16 in_width, in_height;
	पूर्णांक min_factor = min(*decim_x, *decim_y);
	स्थिर पूर्णांक maxsinglelinewidth = dispc->feat->max_line_width;

	*five_taps = false;

	करो अणु
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*core_clk = dispc->feat->calc_core_clk(pclk, in_width,
				in_height, out_width, out_height, mem_to_mem);
		error = (in_width > maxsinglelinewidth || !*core_clk ||
			*core_clk > dispc_core_clk_rate(dispc));
		अगर (error) अणु
			अगर (*decim_x == *decim_y) अणु
				*decim_x = min_factor;
				++*decim_y;
			पूर्ण अन्यथा अणु
				swap(*decim_x, *decim_y);
				अगर (*decim_x < *decim_y)
					++*decim_x;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (*decim_x <= *x_predecim && *decim_y <= *y_predecim && error);

	अगर (error) अणु
		DSSERR("failed to find scaling settings\n");
		वापस -EINVAL;
	पूर्ण

	अगर (in_width > maxsinglelinewidth) अणु
		DSSERR("Cannot scale max input width exceeded\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_ovl_calc_scaling_34xx(काष्ठा dispc_device *dispc,
				       अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
				       स्थिर काष्ठा videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fourcc, bool *five_taps,
				       पूर्णांक *x_predecim, पूर्णांक *y_predecim,
				       पूर्णांक *decim_x, पूर्णांक *decim_y,
				       u16 pos_x, अचिन्हित दीर्घ *core_clk,
				       bool mem_to_mem)
अणु
	पूर्णांक error;
	u16 in_width, in_height;
	स्थिर पूर्णांक maxsinglelinewidth = dispc->feat->max_line_width;

	करो अणु
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*five_taps = in_height > out_height;

		अगर (in_width > maxsinglelinewidth)
			अगर (in_height > out_height &&
						in_height < out_height * 2)
				*five_taps = false;
again:
		अगर (*five_taps)
			*core_clk = calc_core_clk_five_taps(pclk, vm,
						in_width, in_height, out_width,
						out_height, fourcc);
		अन्यथा
			*core_clk = dispc->feat->calc_core_clk(pclk, in_width,
					in_height, out_width, out_height,
					mem_to_mem);

		error = check_horiz_timing_omap3(pclk, lclk, vm,
				pos_x, in_width, in_height, out_width,
				out_height, *five_taps);
		अगर (error && *five_taps) अणु
			*five_taps = false;
			जाओ again;
		पूर्ण

		error = (error || in_width > maxsinglelinewidth * 2 ||
			(in_width > maxsinglelinewidth && *five_taps) ||
			!*core_clk || *core_clk > dispc_core_clk_rate(dispc));

		अगर (!error) अणु
			/* verअगरy that we're inside the limits of scaler */
			अगर (in_width / 4 > out_width)
					error = 1;

			अगर (*five_taps) अणु
				अगर (in_height / 4 > out_height)
					error = 1;
			पूर्ण अन्यथा अणु
				अगर (in_height / 2 > out_height)
					error = 1;
			पूर्ण
		पूर्ण

		अगर (error)
			++*decim_y;
	पूर्ण जबतक (*decim_x <= *x_predecim && *decim_y <= *y_predecim && error);

	अगर (error) अणु
		DSSERR("failed to find scaling settings\n");
		वापस -EINVAL;
	पूर्ण

	अगर (check_horiz_timing_omap3(pclk, lclk, vm, pos_x, in_width,
				in_height, out_width, out_height, *five_taps)) अणु
			DSSERR("horizontal timing too tight\n");
			वापस -EINVAL;
	पूर्ण

	अगर (in_width > (maxsinglelinewidth * 2)) अणु
		DSSERR("Cannot setup scaling\n");
		DSSERR("width exceeds maximum width possible\n");
		वापस -EINVAL;
	पूर्ण

	अगर (in_width > maxsinglelinewidth && *five_taps) अणु
		DSSERR("cannot setup scaling with five taps\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_ovl_calc_scaling_44xx(काष्ठा dispc_device *dispc,
				       अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
				       स्थिर काष्ठा videomode *vm,
				       u16 width, u16 height,
				       u16 out_width, u16 out_height,
				       u32 fourcc, bool *five_taps,
				       पूर्णांक *x_predecim, पूर्णांक *y_predecim,
				       पूर्णांक *decim_x, पूर्णांक *decim_y,
				       u16 pos_x, अचिन्हित दीर्घ *core_clk,
				       bool mem_to_mem)
अणु
	u16 in_width, in_width_max;
	पूर्णांक decim_x_min = *decim_x;
	u16 in_height = height / *decim_y;
	स्थिर पूर्णांक maxsinglelinewidth = dispc->feat->max_line_width;
	स्थिर पूर्णांक maxकरोwnscale = dispc->feat->max_करोwnscale;

	अगर (mem_to_mem) अणु
		in_width_max = out_width * maxकरोwnscale;
	पूर्ण अन्यथा अणु
		in_width_max = dispc_core_clk_rate(dispc)
			     / DIV_ROUND_UP(pclk, out_width);
	पूर्ण

	*decim_x = DIV_ROUND_UP(width, in_width_max);

	*decim_x = *decim_x > decim_x_min ? *decim_x : decim_x_min;
	अगर (*decim_x > *x_predecim)
		वापस -EINVAL;

	करो अणु
		in_width = width / *decim_x;
	पूर्ण जबतक (*decim_x <= *x_predecim &&
			in_width > maxsinglelinewidth && ++*decim_x);

	अगर (in_width > maxsinglelinewidth) अणु
		DSSERR("Cannot scale width exceeds max line width\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*decim_x > 4 && fourcc != DRM_FORMAT_NV12) अणु
		/*
		 * Let's disable all scaling that requires horizontal
		 * decimation with higher factor than 4, until we have
		 * better estimates of what we can and can not
		 * करो. However, NV12 color क्रमmat appears to work Ok
		 * with all decimation factors.
		 *
		 * When decimating horizontally by more that 4 the dss
		 * is not able to fetch the data in burst mode. When
		 * this happens it is hard to tell अगर there enough
		 * bandwidth. Despite what theory says this appears to
		 * be true also क्रम 16-bit color क्रमmats.
		 */
		DSSERR("Not enough bandwidth, too much downscaling (x-decimation factor %d > 4)\n", *decim_x);

		वापस -EINVAL;
	पूर्ण

	*core_clk = dispc->feat->calc_core_clk(pclk, in_width, in_height,
				out_width, out_height, mem_to_mem);
	वापस 0;
पूर्ण

#घोषणा DIV_FRAC(भागidend, भागisor) \
	((भागidend) * 100 / (भागisor) - ((भागidend) / (भागisor) * 100))

अटल पूर्णांक dispc_ovl_calc_scaling(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane,
				  अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
				  क्रमागत omap_overlay_caps caps,
				  स्थिर काष्ठा videomode *vm,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fourcc, bool *five_taps,
				  पूर्णांक *x_predecim, पूर्णांक *y_predecim, u16 pos_x,
				  क्रमागत omap_dss_rotation_type rotation_type,
				  bool mem_to_mem)
अणु
	पूर्णांक maxhकरोwnscale = dispc->feat->max_करोwnscale;
	पूर्णांक maxvकरोwnscale = dispc->feat->max_करोwnscale;
	स्थिर पूर्णांक max_decim_limit = 16;
	अचिन्हित दीर्घ core_clk = 0;
	पूर्णांक decim_x, decim_y, ret;

	अगर (width == out_width && height == out_height)
		वापस 0;

	अगर (dispc->feat->supported_scaler_color_modes) अणु
		स्थिर u32 *modes = dispc->feat->supported_scaler_color_modes;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; modes[i]; ++i) अणु
			अगर (modes[i] == fourcc)
				अवरोध;
		पूर्ण

		अगर (modes[i] == 0)
			वापस -EINVAL;
	पूर्ण

	अगर (plane == OMAP_DSS_WB) अणु
		चयन (fourcc) अणु
		हाल DRM_FORMAT_NV12:
			maxhकरोwnscale = maxvकरोwnscale = 2;
			अवरोध;
		हाल DRM_FORMAT_YUYV:
		हाल DRM_FORMAT_UYVY:
			maxhकरोwnscale = 2;
			maxvकरोwnscale = 4;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!mem_to_mem && (pclk == 0 || vm->pixelघड़ी == 0)) अणु
		DSSERR("cannot calculate scaling settings: pclk is zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((caps & OMAP_DSS_OVL_CAP_SCALE) == 0)
		वापस -EINVAL;

	अगर (mem_to_mem) अणु
		*x_predecim = *y_predecim = 1;
	पूर्ण अन्यथा अणु
		*x_predecim = max_decim_limit;
		*y_predecim = (rotation_type == OMAP_DSS_ROT_TILER &&
				dispc_has_feature(dispc, FEAT_BURST_2D)) ?
				2 : max_decim_limit;
	पूर्ण

	decim_x = DIV_ROUND_UP(DIV_ROUND_UP(width, out_width), maxhकरोwnscale);
	decim_y = DIV_ROUND_UP(DIV_ROUND_UP(height, out_height), maxvकरोwnscale);

	अगर (decim_x > *x_predecim || out_width > width * 8)
		वापस -EINVAL;

	अगर (decim_y > *y_predecim || out_height > height * 8)
		वापस -EINVAL;

	ret = dispc->feat->calc_scaling(dispc, pclk, lclk, vm, width, height,
					out_width, out_height, fourcc,
					five_taps, x_predecim, y_predecim,
					&decim_x, &decim_y, pos_x, &core_clk,
					mem_to_mem);
	अगर (ret)
		वापस ret;

	DSSDBG("%dx%d -> %dx%d (%d.%02d x %d.%02d), decim %dx%d %dx%d (%d.%02d x %d.%02d), taps %d, req clk %lu, cur clk %lu\n",
		width, height,
		out_width, out_height,
		out_width / width, DIV_FRAC(out_width, width),
		out_height / height, DIV_FRAC(out_height, height),

		decim_x, decim_y,
		width / decim_x, height / decim_y,
		out_width / (width / decim_x), DIV_FRAC(out_width, width / decim_x),
		out_height / (height / decim_y), DIV_FRAC(out_height, height / decim_y),

		*five_taps ? 5 : 3,
		core_clk, dispc_core_clk_rate(dispc));

	अगर (!core_clk || core_clk > dispc_core_clk_rate(dispc)) अणु
		DSSERR("failed to set up scaling, "
			"required core clk rate = %lu Hz, "
			"current core clk rate = %lu Hz\n",
			core_clk, dispc_core_clk_rate(dispc));
		वापस -EINVAL;
	पूर्ण

	*x_predecim = decim_x;
	*y_predecim = decim_y;
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_ovl_setup_common(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane,
				  क्रमागत omap_overlay_caps caps,
				  u32 paddr, u32 p_uv_addr,
				  u16 screen_width, पूर्णांक pos_x, पूर्णांक pos_y,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fourcc, u8 rotation, u8 zorder,
				  u8 pre_mult_alpha, u8 global_alpha,
				  क्रमागत omap_dss_rotation_type rotation_type,
				  bool replication, स्थिर काष्ठा videomode *vm,
				  bool mem_to_mem,
				  क्रमागत drm_color_encoding color_encoding,
				  क्रमागत drm_color_range color_range)
अणु
	bool five_taps = true;
	bool fieldmode = false;
	पूर्णांक r, cconv = 0;
	अचिन्हित पूर्णांक offset0, offset1;
	s32 row_inc;
	s32 pix_inc;
	u16 frame_width;
	अचिन्हित पूर्णांक field_offset = 0;
	u16 in_height = height;
	u16 in_width = width;
	पूर्णांक x_predecim = 1, y_predecim = 1;
	bool ilace = !!(vm->flags & DISPLAY_FLAGS_INTERLACED);
	अचिन्हित दीर्घ pclk = dispc_plane_pclk_rate(dispc, plane);
	अचिन्हित दीर्घ lclk = dispc_plane_lclk_rate(dispc, plane);
	स्थिर काष्ठा drm_क्रमmat_info *info;

	info = drm_क्रमmat_info(fourcc);

	/* when setting up WB, dispc_plane_pclk_rate() वापसs 0 */
	अगर (plane == OMAP_DSS_WB)
		pclk = vm->pixelघड़ी;

	अगर (paddr == 0 && rotation_type != OMAP_DSS_ROT_TILER)
		वापस -EINVAL;

	अगर (info->is_yuv && (in_width & 1)) अणु
		DSSERR("input width %d is not even for YUV format\n", in_width);
		वापस -EINVAL;
	पूर्ण

	out_width = out_width == 0 ? width : out_width;
	out_height = out_height == 0 ? height : out_height;

	अगर (plane != OMAP_DSS_WB) अणु
		अगर (ilace && height == out_height)
			fieldmode = true;

		अगर (ilace) अणु
			अगर (fieldmode)
				in_height /= 2;
			pos_y /= 2;
			out_height /= 2;

			DSSDBG("adjusting for ilace: height %d, pos_y %d, out_height %d\n",
				in_height, pos_y, out_height);
		पूर्ण
	पूर्ण

	अगर (!dispc_ovl_color_mode_supported(dispc, plane, fourcc))
		वापस -EINVAL;

	r = dispc_ovl_calc_scaling(dispc, plane, pclk, lclk, caps, vm, in_width,
				   in_height, out_width, out_height, fourcc,
				   &five_taps, &x_predecim, &y_predecim, pos_x,
				   rotation_type, mem_to_mem);
	अगर (r)
		वापस r;

	in_width = in_width / x_predecim;
	in_height = in_height / y_predecim;

	अगर (x_predecim > 1 || y_predecim > 1)
		DSSDBG("predecimation %d x %x, new input size %d x %d\n",
			x_predecim, y_predecim, in_width, in_height);

	अगर (info->is_yuv && (in_width & 1)) अणु
		DSSDBG("predecimated input width is not even for YUV format\n");
		DSSDBG("adjusting input width %d -> %d\n",
			in_width, in_width & ~1);

		in_width &= ~1;
	पूर्ण

	अगर (info->is_yuv)
		cconv = 1;

	अगर (ilace && !fieldmode) अणु
		/*
		 * when करोwnscaling the bottom field may have to start several
		 * source lines below the top field. Unक्रमtunately ACCUI
		 * रेजिस्टरs will only hold the fractional part of the offset
		 * so the पूर्णांकeger part must be added to the base address of the
		 * bottom field.
		 */
		अगर (!in_height || in_height == out_height)
			field_offset = 0;
		अन्यथा
			field_offset = in_height / out_height / 2;
	पूर्ण

	/* Fields are independent but पूर्णांकerleaved in memory. */
	अगर (fieldmode)
		field_offset = 1;

	offset0 = 0;
	offset1 = 0;
	row_inc = 0;
	pix_inc = 0;

	अगर (plane == OMAP_DSS_WB)
		frame_width = out_width;
	अन्यथा
		frame_width = in_width;

	calc_offset(screen_width, frame_width,
			fourcc, fieldmode, field_offset,
			&offset0, &offset1, &row_inc, &pix_inc,
			x_predecim, y_predecim,
			rotation_type, rotation);

	DSSDBG("offset0 %u, offset1 %u, row_inc %d, pix_inc %d\n",
			offset0, offset1, row_inc, pix_inc);

	dispc_ovl_set_color_mode(dispc, plane, fourcc);

	dispc_ovl_configure_burst_type(dispc, plane, rotation_type);

	अगर (dispc->feat->reverse_ilace_field_order)
		swap(offset0, offset1);

	dispc_ovl_set_ba0(dispc, plane, paddr + offset0);
	dispc_ovl_set_ba1(dispc, plane, paddr + offset1);

	अगर (fourcc == DRM_FORMAT_NV12) अणु
		dispc_ovl_set_ba0_uv(dispc, plane, p_uv_addr + offset0);
		dispc_ovl_set_ba1_uv(dispc, plane, p_uv_addr + offset1);
	पूर्ण

	अगर (dispc->feat->last_pixel_inc_missing)
		row_inc += pix_inc - 1;

	dispc_ovl_set_row_inc(dispc, plane, row_inc);
	dispc_ovl_set_pix_inc(dispc, plane, pix_inc);

	DSSDBG("%d,%d %dx%d -> %dx%d\n", pos_x, pos_y, in_width,
			in_height, out_width, out_height);

	dispc_ovl_set_pos(dispc, plane, caps, pos_x, pos_y);

	dispc_ovl_set_input_size(dispc, plane, in_width, in_height);

	अगर (caps & OMAP_DSS_OVL_CAP_SCALE) अणु
		dispc_ovl_set_scaling(dispc, plane, in_width, in_height,
				      out_width, out_height, ilace, five_taps,
				      fieldmode, fourcc, rotation);
		dispc_ovl_set_output_size(dispc, plane, out_width, out_height);
		dispc_ovl_set_vid_color_conv(dispc, plane, cconv);

		अगर (plane != OMAP_DSS_WB)
			dispc_ovl_set_csc(dispc, plane, color_encoding, color_range);
	पूर्ण

	dispc_ovl_set_rotation_attrs(dispc, plane, rotation, rotation_type,
				     fourcc);

	dispc_ovl_set_zorder(dispc, plane, caps, zorder);
	dispc_ovl_set_pre_mult_alpha(dispc, plane, caps, pre_mult_alpha);
	dispc_ovl_setup_global_alpha(dispc, plane, caps, global_alpha);

	dispc_ovl_enable_replication(dispc, plane, caps, replication);

	वापस 0;
पूर्ण

पूर्णांक dispc_ovl_setup(काष्ठा dispc_device *dispc,
			   क्रमागत omap_plane_id plane,
			   स्थिर काष्ठा omap_overlay_info *oi,
			   स्थिर काष्ठा videomode *vm, bool mem_to_mem,
			   क्रमागत omap_channel channel)
अणु
	पूर्णांक r;
	क्रमागत omap_overlay_caps caps = dispc->feat->overlay_caps[plane];
	स्थिर bool replication = true;

	DSSDBG("dispc_ovl_setup %d, pa %pad, pa_uv %pad, sw %d, %d,%d, %dx%d ->"
		" %dx%d, cmode %x, rot %d, chan %d repl %d\n",
		plane, &oi->paddr, &oi->p_uv_addr, oi->screen_width, oi->pos_x,
		oi->pos_y, oi->width, oi->height, oi->out_width, oi->out_height,
		oi->fourcc, oi->rotation, channel, replication);

	dispc_ovl_set_channel_out(dispc, plane, channel);

	r = dispc_ovl_setup_common(dispc, plane, caps, oi->paddr, oi->p_uv_addr,
		oi->screen_width, oi->pos_x, oi->pos_y, oi->width, oi->height,
		oi->out_width, oi->out_height, oi->fourcc, oi->rotation,
		oi->zorder, oi->pre_mult_alpha, oi->global_alpha,
		oi->rotation_type, replication, vm, mem_to_mem,
		oi->color_encoding, oi->color_range);

	वापस r;
पूर्ण

पूर्णांक dispc_wb_setup(काष्ठा dispc_device *dispc,
		   स्थिर काष्ठा omap_dss_ग_लिखोback_info *wi,
		   bool mem_to_mem, स्थिर काष्ठा videomode *vm,
		   क्रमागत dss_ग_लिखोback_channel channel_in)
अणु
	पूर्णांक r;
	u32 l;
	क्रमागत omap_plane_id plane = OMAP_DSS_WB;
	स्थिर पूर्णांक pos_x = 0, pos_y = 0;
	स्थिर u8 zorder = 0, global_alpha = 0;
	स्थिर bool replication = true;
	bool truncation;
	पूर्णांक in_width = vm->hactive;
	पूर्णांक in_height = vm->vactive;
	क्रमागत omap_overlay_caps caps =
		OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA;

	अगर (vm->flags & DISPLAY_FLAGS_INTERLACED)
		in_height /= 2;

	DSSDBG("dispc_wb_setup, pa %x, pa_uv %x, %d,%d -> %dx%d, cmode %x, "
		"rot %d\n", wi->paddr, wi->p_uv_addr, in_width,
		in_height, wi->width, wi->height, wi->fourcc, wi->rotation);

	r = dispc_ovl_setup_common(dispc, plane, caps, wi->paddr, wi->p_uv_addr,
		wi->buf_width, pos_x, pos_y, in_width, in_height, wi->width,
		wi->height, wi->fourcc, wi->rotation, zorder,
		wi->pre_mult_alpha, global_alpha, wi->rotation_type,
		replication, vm, mem_to_mem, DRM_COLOR_YCBCR_BT601,
		DRM_COLOR_YCBCR_LIMITED_RANGE);
	अगर (r)
		वापस r;

	चयन (wi->fourcc) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_RGBA4444:
	हाल DRM_FORMAT_RGBX4444:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_XRGB4444:
		truncation = true;
		अवरोध;
	शेष:
		truncation = false;
		अवरोध;
	पूर्ण

	/* setup extra DISPC_WB_ATTRIBUTES */
	l = dispc_पढ़ो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));
	l = FLD_MOD(l, truncation, 10, 10);	/* TRUNCATIONENABLE */
	l = FLD_MOD(l, channel_in, 18, 16);	/* CHANNELIN */
	l = FLD_MOD(l, mem_to_mem, 19, 19);	/* WRITEBACKMODE */
	अगर (mem_to_mem)
		l = FLD_MOD(l, 1, 26, 24);	/* CAPTUREMODE */
	अन्यथा
		l = FLD_MOD(l, 0, 26, 24);	/* CAPTUREMODE */
	dispc_ग_लिखो_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), l);

	अगर (mem_to_mem) अणु
		/* WBDELAYCOUNT */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane), 0, 7, 0);
	पूर्ण अन्यथा अणु
		u32 wbdelay;

		अगर (channel_in == DSS_WB_TV_MGR)
			wbdelay = vm->vsync_len + vm->vback_porch;
		अन्यथा
			wbdelay = vm->vfront_porch + vm->vsync_len +
				vm->vback_porch;

		अगर (vm->flags & DISPLAY_FLAGS_INTERLACED)
			wbdelay /= 2;

		wbdelay = min(wbdelay, 255u);

		/* WBDELAYCOUNT */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane), wbdelay, 7, 0);
	पूर्ण

	वापस 0;
पूर्ण

bool dispc_has_ग_लिखोback(काष्ठा dispc_device *dispc)
अणु
	वापस dispc->feat->has_ग_लिखोback;
पूर्ण

पूर्णांक dispc_ovl_enable(काष्ठा dispc_device *dispc,
			    क्रमागत omap_plane_id plane, bool enable)
अणु
	DSSDBG("dispc_enable_plane %d, %d\n", plane, enable);

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), enable ? 1 : 0, 0, 0);

	वापस 0;
पूर्ण

अटल व्योम dispc_lcd_enable_संकेत_polarity(काष्ठा dispc_device *dispc,
					     bool act_high)
अणु
	अगर (!dispc_has_feature(dispc, FEAT_LCDENABLEPOL))
		वापस;

	REG_FLD_MOD(dispc, DISPC_CONTROL, act_high ? 1 : 0, 29, 29);
पूर्ण

व्योम dispc_lcd_enable_संकेत(काष्ठा dispc_device *dispc, bool enable)
अणु
	अगर (!dispc_has_feature(dispc, FEAT_LCDENABLESIGNAL))
		वापस;

	REG_FLD_MOD(dispc, DISPC_CONTROL, enable ? 1 : 0, 28, 28);
पूर्ण

व्योम dispc_pck_मुक्त_enable(काष्ठा dispc_device *dispc, bool enable)
अणु
	अगर (!dispc_has_feature(dispc, FEAT_PCKFREEENABLE))
		वापस;

	REG_FLD_MOD(dispc, DISPC_CONTROL, enable ? 1 : 0, 27, 27);
पूर्ण

अटल व्योम dispc_mgr_enable_fअगरohandcheck(काष्ठा dispc_device *dispc,
					   क्रमागत omap_channel channel,
					   bool enable)
अणु
	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_FIFOHANDCHECK, enable);
पूर्ण


अटल व्योम dispc_mgr_set_lcd_type_tft(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel)
अणु
	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_STNTFT, 1);
पूर्ण

अटल व्योम dispc_set_loadmode(काष्ठा dispc_device *dispc,
			       क्रमागत omap_dss_load_mode mode)
अणु
	REG_FLD_MOD(dispc, DISPC_CONFIG, mode, 2, 1);
पूर्ण


अटल व्योम dispc_mgr_set_शेष_color(काष्ठा dispc_device *dispc,
					क्रमागत omap_channel channel, u32 color)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_DEFAULT_COLOR(channel), color);
पूर्ण

अटल व्योम dispc_mgr_set_trans_key(काष्ठा dispc_device *dispc,
				    क्रमागत omap_channel ch,
				    क्रमागत omap_dss_trans_key_type type,
				    u32 trans_key)
अणु
	mgr_fld_ग_लिखो(dispc, ch, DISPC_MGR_FLD_TCKSELECTION, type);

	dispc_ग_लिखो_reg(dispc, DISPC_TRANS_COLOR(ch), trans_key);
पूर्ण

अटल व्योम dispc_mgr_enable_trans_key(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel ch, bool enable)
अणु
	mgr_fld_ग_लिखो(dispc, ch, DISPC_MGR_FLD_TCKENABLE, enable);
पूर्ण

अटल व्योम dispc_mgr_enable_alpha_fixed_zorder(काष्ठा dispc_device *dispc,
						क्रमागत omap_channel ch,
						bool enable)
अणु
	अगर (!dispc_has_feature(dispc, FEAT_ALPHA_FIXED_ZORDER))
		वापस;

	अगर (ch == OMAP_DSS_CHANNEL_LCD)
		REG_FLD_MOD(dispc, DISPC_CONFIG, enable, 18, 18);
	अन्यथा अगर (ch == OMAP_DSS_CHANNEL_DIGIT)
		REG_FLD_MOD(dispc, DISPC_CONFIG, enable, 19, 19);
पूर्ण

व्योम dispc_mgr_setup(काष्ठा dispc_device *dispc,
			    क्रमागत omap_channel channel,
			    स्थिर काष्ठा omap_overlay_manager_info *info)
अणु
	dispc_mgr_set_शेष_color(dispc, channel, info->शेष_color);
	dispc_mgr_set_trans_key(dispc, channel, info->trans_key_type,
				info->trans_key);
	dispc_mgr_enable_trans_key(dispc, channel, info->trans_enabled);
	dispc_mgr_enable_alpha_fixed_zorder(dispc, channel,
			info->partial_alpha_enabled);
	अगर (dispc_has_feature(dispc, FEAT_CPR)) अणु
		dispc_mgr_enable_cpr(dispc, channel, info->cpr_enable);
		dispc_mgr_set_cpr_coef(dispc, channel, &info->cpr_coefs);
	पूर्ण
पूर्ण

अटल व्योम dispc_mgr_set_tft_data_lines(काष्ठा dispc_device *dispc,
					 क्रमागत omap_channel channel,
					 u8 data_lines)
अणु
	पूर्णांक code;

	चयन (data_lines) अणु
	हाल 12:
		code = 0;
		अवरोध;
	हाल 16:
		code = 1;
		अवरोध;
	हाल 18:
		code = 2;
		अवरोध;
	हाल 24:
		code = 3;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_TFTDATALINES, code);
पूर्ण

अटल व्योम dispc_mgr_set_io_pad_mode(काष्ठा dispc_device *dispc,
				      क्रमागत dss_io_pad_mode mode)
अणु
	u32 l;
	पूर्णांक gpout0, gpout1;

	चयन (mode) अणु
	हाल DSS_IO_PAD_MODE_RESET:
		gpout0 = 0;
		gpout1 = 0;
		अवरोध;
	हाल DSS_IO_PAD_MODE_RFBI:
		gpout0 = 1;
		gpout1 = 0;
		अवरोध;
	हाल DSS_IO_PAD_MODE_BYPASS:
		gpout0 = 1;
		gpout1 = 1;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	l = dispc_पढ़ो_reg(dispc, DISPC_CONTROL);
	l = FLD_MOD(l, gpout0, 15, 15);
	l = FLD_MOD(l, gpout1, 16, 16);
	dispc_ग_लिखो_reg(dispc, DISPC_CONTROL, l);
पूर्ण

अटल व्योम dispc_mgr_enable_stallmode(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel, bool enable)
अणु
	mgr_fld_ग_लिखो(dispc, channel, DISPC_MGR_FLD_STALLMODE, enable);
पूर्ण

व्योम dispc_mgr_set_lcd_config(काष्ठा dispc_device *dispc,
				     क्रमागत omap_channel channel,
				     स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	dispc_mgr_set_io_pad_mode(dispc, config->io_pad_mode);

	dispc_mgr_enable_stallmode(dispc, channel, config->stallmode);
	dispc_mgr_enable_fअगरohandcheck(dispc, channel, config->fअगरohandcheck);

	dispc_mgr_set_घड़ी_भाग(dispc, channel, &config->घड़ी_info);

	dispc_mgr_set_tft_data_lines(dispc, channel, config->video_port_width);

	dispc_lcd_enable_संकेत_polarity(dispc, config->lcden_sig_polarity);

	dispc_mgr_set_lcd_type_tft(dispc, channel);
पूर्ण

अटल bool _dispc_mgr_size_ok(काष्ठा dispc_device *dispc,
			       u16 width, u16 height)
अणु
	वापस width <= dispc->feat->mgr_width_max &&
		height <= dispc->feat->mgr_height_max;
पूर्ण

अटल bool _dispc_lcd_timings_ok(काष्ठा dispc_device *dispc,
				  पूर्णांक hsync_len, पूर्णांक hfp, पूर्णांक hbp,
				  पूर्णांक vsw, पूर्णांक vfp, पूर्णांक vbp)
अणु
	अगर (hsync_len < 1 || hsync_len > dispc->feat->sw_max ||
	    hfp < 1 || hfp > dispc->feat->hp_max ||
	    hbp < 1 || hbp > dispc->feat->hp_max ||
	    vsw < 1 || vsw > dispc->feat->sw_max ||
	    vfp < 0 || vfp > dispc->feat->vp_max ||
	    vbp < 0 || vbp > dispc->feat->vp_max)
		वापस false;
	वापस true;
पूर्ण

अटल bool _dispc_mgr_pclk_ok(काष्ठा dispc_device *dispc,
			       क्रमागत omap_channel channel,
			       अचिन्हित दीर्घ pclk)
अणु
	अगर (dss_mgr_is_lcd(channel))
		वापस pclk <= dispc->feat->max_lcd_pclk;
	अन्यथा
		वापस pclk <= dispc->feat->max_tv_pclk;
पूर्ण

पूर्णांक dispc_mgr_check_timings(काष्ठा dispc_device *dispc,
				   क्रमागत omap_channel channel,
				   स्थिर काष्ठा videomode *vm)
अणु
	अगर (!_dispc_mgr_size_ok(dispc, vm->hactive, vm->vactive))
		वापस MODE_BAD;

	अगर (!_dispc_mgr_pclk_ok(dispc, channel, vm->pixelघड़ी))
		वापस MODE_BAD;

	अगर (dss_mgr_is_lcd(channel)) अणु
		/* TODO: OMAP4+ supports पूर्णांकerlace क्रम LCD outमाला_दो */
		अगर (vm->flags & DISPLAY_FLAGS_INTERLACED)
			वापस MODE_BAD;

		अगर (!_dispc_lcd_timings_ok(dispc, vm->hsync_len,
				vm->hfront_porch, vm->hback_porch,
				vm->vsync_len, vm->vfront_porch,
				vm->vback_porch))
			वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल व्योम _dispc_mgr_set_lcd_timings(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel,
				       स्थिर काष्ठा videomode *vm)
अणु
	u32 timing_h, timing_v, l;
	bool onoff, rf, ipc, vs, hs, de;

	timing_h = FLD_VAL(vm->hsync_len - 1, dispc->feat->sw_start, 0) |
		   FLD_VAL(vm->hfront_porch - 1, dispc->feat->fp_start, 8) |
		   FLD_VAL(vm->hback_porch - 1, dispc->feat->bp_start, 20);
	timing_v = FLD_VAL(vm->vsync_len - 1, dispc->feat->sw_start, 0) |
		   FLD_VAL(vm->vfront_porch, dispc->feat->fp_start, 8) |
		   FLD_VAL(vm->vback_porch, dispc->feat->bp_start, 20);

	dispc_ग_लिखो_reg(dispc, DISPC_TIMING_H(channel), timing_h);
	dispc_ग_लिखो_reg(dispc, DISPC_TIMING_V(channel), timing_v);

	vs = !!(vm->flags & DISPLAY_FLAGS_VSYNC_LOW);
	hs = !!(vm->flags & DISPLAY_FLAGS_HSYNC_LOW);
	de = !!(vm->flags & DISPLAY_FLAGS_DE_LOW);
	ipc = !!(vm->flags & DISPLAY_FLAGS_PIXDATA_NEGEDGE);
	onoff = true; /* always use the 'rf' setting */
	rf = !!(vm->flags & DISPLAY_FLAGS_SYNC_POSEDGE);

	l = FLD_VAL(onoff, 17, 17) |
		FLD_VAL(rf, 16, 16) |
		FLD_VAL(de, 15, 15) |
		FLD_VAL(ipc, 14, 14) |
		FLD_VAL(hs, 13, 13) |
		FLD_VAL(vs, 12, 12);

	/* always set ALIGN bit when available */
	अगर (dispc->feat->supports_sync_align)
		l |= (1 << 18);

	dispc_ग_लिखो_reg(dispc, DISPC_POL_FREQ(channel), l);

	अगर (dispc->syscon_pol) अणु
		स्थिर पूर्णांक shअगरts[] = अणु
			[OMAP_DSS_CHANNEL_LCD] = 0,
			[OMAP_DSS_CHANNEL_LCD2] = 1,
			[OMAP_DSS_CHANNEL_LCD3] = 2,
		पूर्ण;

		u32 mask, val;

		mask = (1 << 0) | (1 << 3) | (1 << 6);
		val = (rf << 0) | (ipc << 3) | (onoff << 6);

		mask <<= 16 + shअगरts[channel];
		val <<= 16 + shअगरts[channel];

		regmap_update_bits(dispc->syscon_pol, dispc->syscon_pol_offset,
				   mask, val);
	पूर्ण
पूर्ण

अटल पूर्णांक vm_flag_to_पूर्णांक(क्रमागत display_flags flags, क्रमागत display_flags high,
	क्रमागत display_flags low)
अणु
	अगर (flags & high)
		वापस 1;
	अगर (flags & low)
		वापस -1;
	वापस 0;
पूर्ण

/* change name to mode? */
व्योम dispc_mgr_set_timings(काष्ठा dispc_device *dispc,
				  क्रमागत omap_channel channel,
				  स्थिर काष्ठा videomode *vm)
अणु
	अचिन्हित पूर्णांक xtot, ytot;
	अचिन्हित दीर्घ ht, vt;
	काष्ठा videomode t = *vm;

	DSSDBG("channel %d xres %u yres %u\n", channel, t.hactive, t.vactive);

	अगर (dispc_mgr_check_timings(dispc, channel, &t)) अणु
		BUG();
		वापस;
	पूर्ण

	अगर (dss_mgr_is_lcd(channel)) अणु
		_dispc_mgr_set_lcd_timings(dispc, channel, &t);

		xtot = t.hactive + t.hfront_porch + t.hsync_len + t.hback_porch;
		ytot = t.vactive + t.vfront_porch + t.vsync_len + t.vback_porch;

		ht = vm->pixelघड़ी / xtot;
		vt = vm->pixelघड़ी / xtot / ytot;

		DSSDBG("pck %lu\n", vm->pixelघड़ी);
		DSSDBG("hsync_len %d hfp %d hbp %d vsw %d vfp %d vbp %d\n",
			t.hsync_len, t.hfront_porch, t.hback_porch,
			t.vsync_len, t.vfront_porch, t.vback_porch);
		DSSDBG("vsync_level %d hsync_level %d data_pclk_edge %d de_level %d sync_pclk_edge %d\n",
			vm_flag_to_पूर्णांक(t.flags, DISPLAY_FLAGS_VSYNC_HIGH, DISPLAY_FLAGS_VSYNC_LOW),
			vm_flag_to_पूर्णांक(t.flags, DISPLAY_FLAGS_HSYNC_HIGH, DISPLAY_FLAGS_HSYNC_LOW),
			vm_flag_to_पूर्णांक(t.flags, DISPLAY_FLAGS_PIXDATA_POSEDGE, DISPLAY_FLAGS_PIXDATA_NEGEDGE),
			vm_flag_to_पूर्णांक(t.flags, DISPLAY_FLAGS_DE_HIGH, DISPLAY_FLAGS_DE_LOW),
			vm_flag_to_पूर्णांक(t.flags, DISPLAY_FLAGS_SYNC_POSEDGE, DISPLAY_FLAGS_SYNC_NEGEDGE));

		DSSDBG("hsync %luHz, vsync %luHz\n", ht, vt);
	पूर्ण अन्यथा अणु
		अगर (t.flags & DISPLAY_FLAGS_INTERLACED)
			t.vactive /= 2;

		अगर (dispc->feat->supports_द्विगुन_pixel)
			REG_FLD_MOD(dispc, DISPC_CONTROL,
				    !!(t.flags & DISPLAY_FLAGS_DOUBLECLK),
				    19, 17);
	पूर्ण

	dispc_mgr_set_size(dispc, channel, t.hactive, t.vactive);
पूर्ण

अटल व्योम dispc_mgr_set_lcd_भागisor(काष्ठा dispc_device *dispc,
				      क्रमागत omap_channel channel, u16 lck_भाग,
				      u16 pck_भाग)
अणु
	BUG_ON(lck_भाग < 1);
	BUG_ON(pck_भाग < 1);

	dispc_ग_लिखो_reg(dispc, DISPC_DIVISORo(channel),
			FLD_VAL(lck_भाग, 23, 16) | FLD_VAL(pck_भाग, 7, 0));

	अगर (!dispc_has_feature(dispc, FEAT_CORE_CLK_DIV) &&
			channel == OMAP_DSS_CHANNEL_LCD)
		dispc->core_clk_rate = dispc_fclk_rate(dispc) / lck_भाग;
पूर्ण

अटल व्योम dispc_mgr_get_lcd_भागisor(काष्ठा dispc_device *dispc,
				      क्रमागत omap_channel channel, पूर्णांक *lck_भाग,
				      पूर्णांक *pck_भाग)
अणु
	u32 l;
	l = dispc_पढ़ो_reg(dispc, DISPC_DIVISORo(channel));
	*lck_भाग = FLD_GET(l, 23, 16);
	*pck_भाग = FLD_GET(l, 7, 0);
पूर्ण

अटल अचिन्हित दीर्घ dispc_fclk_rate(काष्ठा dispc_device *dispc)
अणु
	अचिन्हित दीर्घ r;
	क्रमागत dss_clk_source src;

	src = dss_get_dispc_clk_source(dispc->dss);

	अगर (src == DSS_CLK_SRC_FCK) अणु
		r = dss_get_dispc_clk_rate(dispc->dss);
	पूर्ण अन्यथा अणु
		काष्ठा dss_pll *pll;
		अचिन्हित पूर्णांक clkout_idx;

		pll = dss_pll_find_by_src(dispc->dss, src);
		clkout_idx = dss_pll_get_clkout_idx_क्रम_src(src);

		r = pll->cinfo.clkout[clkout_idx];
	पूर्ण

	वापस r;
पूर्ण

अटल अचिन्हित दीर्घ dispc_mgr_lclk_rate(काष्ठा dispc_device *dispc,
					 क्रमागत omap_channel channel)
अणु
	पूर्णांक lcd;
	अचिन्हित दीर्घ r;
	क्रमागत dss_clk_source src;

	/* क्रम TV, LCLK rate is the FCLK rate */
	अगर (!dss_mgr_is_lcd(channel))
		वापस dispc_fclk_rate(dispc);

	src = dss_get_lcd_clk_source(dispc->dss, channel);

	अगर (src == DSS_CLK_SRC_FCK) अणु
		r = dss_get_dispc_clk_rate(dispc->dss);
	पूर्ण अन्यथा अणु
		काष्ठा dss_pll *pll;
		अचिन्हित पूर्णांक clkout_idx;

		pll = dss_pll_find_by_src(dispc->dss, src);
		clkout_idx = dss_pll_get_clkout_idx_क्रम_src(src);

		r = pll->cinfo.clkout[clkout_idx];
	पूर्ण

	lcd = REG_GET(dispc, DISPC_DIVISORo(channel), 23, 16);

	वापस r / lcd;
पूर्ण

अटल अचिन्हित दीर्घ dispc_mgr_pclk_rate(काष्ठा dispc_device *dispc,
					 क्रमागत omap_channel channel)
अणु
	अचिन्हित दीर्घ r;

	अगर (dss_mgr_is_lcd(channel)) अणु
		पूर्णांक pcd;
		u32 l;

		l = dispc_पढ़ो_reg(dispc, DISPC_DIVISORo(channel));

		pcd = FLD_GET(l, 7, 0);

		r = dispc_mgr_lclk_rate(dispc, channel);

		वापस r / pcd;
	पूर्ण अन्यथा अणु
		वापस dispc->tv_pclk_rate;
	पूर्ण
पूर्ण

व्योम dispc_set_tv_pclk(काष्ठा dispc_device *dispc, अचिन्हित दीर्घ pclk)
अणु
	dispc->tv_pclk_rate = pclk;
पूर्ण

अटल अचिन्हित दीर्घ dispc_core_clk_rate(काष्ठा dispc_device *dispc)
अणु
	वापस dispc->core_clk_rate;
पूर्ण

अटल अचिन्हित दीर्घ dispc_plane_pclk_rate(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane)
अणु
	क्रमागत omap_channel channel;

	अगर (plane == OMAP_DSS_WB)
		वापस 0;

	channel = dispc_ovl_get_channel_out(dispc, plane);

	वापस dispc_mgr_pclk_rate(dispc, channel);
पूर्ण

अटल अचिन्हित दीर्घ dispc_plane_lclk_rate(काष्ठा dispc_device *dispc,
					   क्रमागत omap_plane_id plane)
अणु
	क्रमागत omap_channel channel;

	अगर (plane == OMAP_DSS_WB)
		वापस 0;

	channel	= dispc_ovl_get_channel_out(dispc, plane);

	वापस dispc_mgr_lclk_rate(dispc, channel);
पूर्ण

अटल व्योम dispc_dump_घड़ीs_channel(काष्ठा dispc_device *dispc,
				      काष्ठा seq_file *s,
				      क्रमागत omap_channel channel)
अणु
	पूर्णांक lcd, pcd;
	क्रमागत dss_clk_source lcd_clk_src;

	seq_म_लिखो(s, "- %s -\n", mgr_desc[channel].name);

	lcd_clk_src = dss_get_lcd_clk_source(dispc->dss, channel);

	seq_म_लिखो(s, "%s clk source = %s\n", mgr_desc[channel].name,
		dss_get_clk_source_name(lcd_clk_src));

	dispc_mgr_get_lcd_भागisor(dispc, channel, &lcd, &pcd);

	seq_म_लिखो(s, "lck\t\t%-16lulck div\t%u\n",
		dispc_mgr_lclk_rate(dispc, channel), lcd);
	seq_म_लिखो(s, "pck\t\t%-16lupck div\t%u\n",
		dispc_mgr_pclk_rate(dispc, channel), pcd);
पूर्ण

व्योम dispc_dump_घड़ीs(काष्ठा dispc_device *dispc, काष्ठा seq_file *s)
अणु
	क्रमागत dss_clk_source dispc_clk_src;
	पूर्णांक lcd;
	u32 l;

	अगर (dispc_runसमय_get(dispc))
		वापस;

	seq_म_लिखो(s, "- DISPC -\n");

	dispc_clk_src = dss_get_dispc_clk_source(dispc->dss);
	seq_म_लिखो(s, "dispc fclk source = %s\n",
			dss_get_clk_source_name(dispc_clk_src));

	seq_म_लिखो(s, "fck\t\t%-16lu\n", dispc_fclk_rate(dispc));

	अगर (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV)) अणु
		seq_म_लिखो(s, "- DISPC-CORE-CLK -\n");
		l = dispc_पढ़ो_reg(dispc, DISPC_DIVISOR);
		lcd = FLD_GET(l, 23, 16);

		seq_म_लिखो(s, "lck\t\t%-16lulck div\t%u\n",
				(dispc_fclk_rate(dispc)/lcd), lcd);
	पूर्ण

	dispc_dump_घड़ीs_channel(dispc, s, OMAP_DSS_CHANNEL_LCD);

	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2))
		dispc_dump_घड़ीs_channel(dispc, s, OMAP_DSS_CHANNEL_LCD2);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3))
		dispc_dump_घड़ीs_channel(dispc, s, OMAP_DSS_CHANNEL_LCD3);

	dispc_runसमय_put(dispc);
पूर्ण

अटल पूर्णांक dispc_dump_regs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dispc_device *dispc = s->निजी;
	पूर्णांक i, j;
	स्थिर अक्षर *mgr_names[] = अणु
		[OMAP_DSS_CHANNEL_LCD]		= "LCD",
		[OMAP_DSS_CHANNEL_DIGIT]	= "TV",
		[OMAP_DSS_CHANNEL_LCD2]		= "LCD2",
		[OMAP_DSS_CHANNEL_LCD3]		= "LCD3",
	पूर्ण;
	स्थिर अक्षर *ovl_names[] = अणु
		[OMAP_DSS_GFX]		= "GFX",
		[OMAP_DSS_VIDEO1]	= "VID1",
		[OMAP_DSS_VIDEO2]	= "VID2",
		[OMAP_DSS_VIDEO3]	= "VID3",
		[OMAP_DSS_WB]		= "WB",
	पूर्ण;
	स्थिर अक्षर **p_names;

#घोषणा DUMPREG(dispc, r) \
	seq_म_लिखो(s, "%-50s %08x\n", #r, dispc_पढ़ो_reg(dispc, r))

	अगर (dispc_runसमय_get(dispc))
		वापस 0;

	/* DISPC common रेजिस्टरs */
	DUMPREG(dispc, DISPC_REVISION);
	DUMPREG(dispc, DISPC_SYSCONFIG);
	DUMPREG(dispc, DISPC_SYSSTATUS);
	DUMPREG(dispc, DISPC_IRQSTATUS);
	DUMPREG(dispc, DISPC_IRQENABLE);
	DUMPREG(dispc, DISPC_CONTROL);
	DUMPREG(dispc, DISPC_CONFIG);
	DUMPREG(dispc, DISPC_CAPABLE);
	DUMPREG(dispc, DISPC_LINE_STATUS);
	DUMPREG(dispc, DISPC_LINE_NUMBER);
	अगर (dispc_has_feature(dispc, FEAT_ALPHA_FIXED_ZORDER) ||
			dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		DUMPREG(dispc, DISPC_GLOBAL_ALPHA);
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2)) अणु
		DUMPREG(dispc, DISPC_CONTROL2);
		DUMPREG(dispc, DISPC_CONFIG2);
	पूर्ण
	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3)) अणु
		DUMPREG(dispc, DISPC_CONTROL3);
		DUMPREG(dispc, DISPC_CONFIG3);
	पूर्ण
	अगर (dispc_has_feature(dispc, FEAT_MFLAG))
		DUMPREG(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE);

#अघोषित DUMPREG

#घोषणा DISPC_REG(i, name) name(i)
#घोषणा DUMPREG(dispc, i, r) seq_म_लिखो(s, "%s(%s)%*s %08x\n", #r, p_names[i], \
	(पूर्णांक)(48 - म_माप(#r) - म_माप(p_names[i])), " ", \
	dispc_पढ़ो_reg(dispc, DISPC_REG(i, r)))

	p_names = mgr_names;

	/* DISPC channel specअगरic रेजिस्टरs */
	क्रम (i = 0; i < dispc_get_num_mgrs(dispc); i++) अणु
		DUMPREG(dispc, i, DISPC_DEFAULT_COLOR);
		DUMPREG(dispc, i, DISPC_TRANS_COLOR);
		DUMPREG(dispc, i, DISPC_SIZE_MGR);

		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;

		DUMPREG(dispc, i, DISPC_TIMING_H);
		DUMPREG(dispc, i, DISPC_TIMING_V);
		DUMPREG(dispc, i, DISPC_POL_FREQ);
		DUMPREG(dispc, i, DISPC_DIVISORo);

		DUMPREG(dispc, i, DISPC_DATA_CYCLE1);
		DUMPREG(dispc, i, DISPC_DATA_CYCLE2);
		DUMPREG(dispc, i, DISPC_DATA_CYCLE3);

		अगर (dispc_has_feature(dispc, FEAT_CPR)) अणु
			DUMPREG(dispc, i, DISPC_CPR_COEF_R);
			DUMPREG(dispc, i, DISPC_CPR_COEF_G);
			DUMPREG(dispc, i, DISPC_CPR_COEF_B);
		पूर्ण
	पूर्ण

	p_names = ovl_names;

	क्रम (i = 0; i < dispc_get_num_ovls(dispc); i++) अणु
		DUMPREG(dispc, i, DISPC_OVL_BA0);
		DUMPREG(dispc, i, DISPC_OVL_BA1);
		DUMPREG(dispc, i, DISPC_OVL_POSITION);
		DUMPREG(dispc, i, DISPC_OVL_SIZE);
		DUMPREG(dispc, i, DISPC_OVL_ATTRIBUTES);
		DUMPREG(dispc, i, DISPC_OVL_FIFO_THRESHOLD);
		DUMPREG(dispc, i, DISPC_OVL_FIFO_SIZE_STATUS);
		DUMPREG(dispc, i, DISPC_OVL_ROW_INC);
		DUMPREG(dispc, i, DISPC_OVL_PIXEL_INC);

		अगर (dispc_has_feature(dispc, FEAT_PRELOAD))
			DUMPREG(dispc, i, DISPC_OVL_PRELOAD);
		अगर (dispc_has_feature(dispc, FEAT_MFLAG))
			DUMPREG(dispc, i, DISPC_OVL_MFLAG_THRESHOLD);

		अगर (i == OMAP_DSS_GFX) अणु
			DUMPREG(dispc, i, DISPC_OVL_WINDOW_SKIP);
			DUMPREG(dispc, i, DISPC_OVL_TABLE_BA);
			जारी;
		पूर्ण

		DUMPREG(dispc, i, DISPC_OVL_FIR);
		DUMPREG(dispc, i, DISPC_OVL_PICTURE_SIZE);
		DUMPREG(dispc, i, DISPC_OVL_ACCU0);
		DUMPREG(dispc, i, DISPC_OVL_ACCU1);
		अगर (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) अणु
			DUMPREG(dispc, i, DISPC_OVL_BA0_UV);
			DUMPREG(dispc, i, DISPC_OVL_BA1_UV);
			DUMPREG(dispc, i, DISPC_OVL_FIR2);
			DUMPREG(dispc, i, DISPC_OVL_ACCU2_0);
			DUMPREG(dispc, i, DISPC_OVL_ACCU2_1);
		पूर्ण
		अगर (dispc_has_feature(dispc, FEAT_ATTR2))
			DUMPREG(dispc, i, DISPC_OVL_ATTRIBUTES2);
	पूर्ण

	अगर (dispc->feat->has_ग_लिखोback) अणु
		i = OMAP_DSS_WB;
		DUMPREG(dispc, i, DISPC_OVL_BA0);
		DUMPREG(dispc, i, DISPC_OVL_BA1);
		DUMPREG(dispc, i, DISPC_OVL_SIZE);
		DUMPREG(dispc, i, DISPC_OVL_ATTRIBUTES);
		DUMPREG(dispc, i, DISPC_OVL_FIFO_THRESHOLD);
		DUMPREG(dispc, i, DISPC_OVL_FIFO_SIZE_STATUS);
		DUMPREG(dispc, i, DISPC_OVL_ROW_INC);
		DUMPREG(dispc, i, DISPC_OVL_PIXEL_INC);

		अगर (dispc_has_feature(dispc, FEAT_MFLAG))
			DUMPREG(dispc, i, DISPC_OVL_MFLAG_THRESHOLD);

		DUMPREG(dispc, i, DISPC_OVL_FIR);
		DUMPREG(dispc, i, DISPC_OVL_PICTURE_SIZE);
		DUMPREG(dispc, i, DISPC_OVL_ACCU0);
		DUMPREG(dispc, i, DISPC_OVL_ACCU1);
		अगर (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) अणु
			DUMPREG(dispc, i, DISPC_OVL_BA0_UV);
			DUMPREG(dispc, i, DISPC_OVL_BA1_UV);
			DUMPREG(dispc, i, DISPC_OVL_FIR2);
			DUMPREG(dispc, i, DISPC_OVL_ACCU2_0);
			DUMPREG(dispc, i, DISPC_OVL_ACCU2_1);
		पूर्ण
		अगर (dispc_has_feature(dispc, FEAT_ATTR2))
			DUMPREG(dispc, i, DISPC_OVL_ATTRIBUTES2);
	पूर्ण

#अघोषित DISPC_REG
#अघोषित DUMPREG

#घोषणा DISPC_REG(plane, name, i) name(plane, i)
#घोषणा DUMPREG(dispc, plane, name, i) \
	seq_म_लिखो(s, "%s_%d(%s)%*s %08x\n", #name, i, p_names[plane], \
	(पूर्णांक)(46 - म_माप(#name) - म_माप(p_names[plane])), " ", \
	dispc_पढ़ो_reg(dispc, DISPC_REG(plane, name, i)))

	/* Video pipeline coefficient रेजिस्टरs */

	/* start from OMAP_DSS_VIDEO1 */
	क्रम (i = 1; i < dispc_get_num_ovls(dispc); i++) अणु
		क्रम (j = 0; j < 8; j++)
			DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_H, j);

		क्रम (j = 0; j < 8; j++)
			DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_HV, j);

		क्रम (j = 0; j < 5; j++)
			DUMPREG(dispc, i, DISPC_OVL_CONV_COEF, j);

		अगर (dispc_has_feature(dispc, FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_V, j);
		पूर्ण

		अगर (dispc_has_feature(dispc, FEAT_HANDLE_UV_SEPARATE)) अणु
			क्रम (j = 0; j < 8; j++)
				DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_H2, j);

			क्रम (j = 0; j < 8; j++)
				DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_HV2, j);

			क्रम (j = 0; j < 8; j++)
				DUMPREG(dispc, i, DISPC_OVL_FIR_COEF_V2, j);
		पूर्ण
	पूर्ण

	dispc_runसमय_put(dispc);

#अघोषित DISPC_REG
#अघोषित DUMPREG

	वापस 0;
पूर्ण

/* calculate घड़ी rates using भागiders in cinfo */
पूर्णांक dispc_calc_घड़ी_rates(काष्ठा dispc_device *dispc,
			   अचिन्हित दीर्घ dispc_fclk_rate,
			   काष्ठा dispc_घड़ी_info *cinfo)
अणु
	अगर (cinfo->lck_भाग > 255 || cinfo->lck_भाग == 0)
		वापस -EINVAL;
	अगर (cinfo->pck_भाग < 1 || cinfo->pck_भाग > 255)
		वापस -EINVAL;

	cinfo->lck = dispc_fclk_rate / cinfo->lck_भाग;
	cinfo->pck = cinfo->lck / cinfo->pck_भाग;

	वापस 0;
पूर्ण

bool dispc_भाग_calc(काष्ठा dispc_device *dispc, अचिन्हित दीर्घ dispc_freq,
		    अचिन्हित दीर्घ pck_min, अचिन्हित दीर्घ pck_max,
		    dispc_भाग_calc_func func, व्योम *data)
अणु
	पूर्णांक lckd, lckd_start, lckd_stop;
	पूर्णांक pckd, pckd_start, pckd_stop;
	अचिन्हित दीर्घ pck, lck;
	अचिन्हित दीर्घ lck_max;
	अचिन्हित दीर्घ pckd_hw_min, pckd_hw_max;
	अचिन्हित पूर्णांक min_fck_per_pck;
	अचिन्हित दीर्घ fck;

#अगर_घोषित CONFIG_OMAP2_DSS_MIN_FCK_PER_PCK
	min_fck_per_pck = CONFIG_OMAP2_DSS_MIN_FCK_PER_PCK;
#अन्यथा
	min_fck_per_pck = 0;
#पूर्ण_अगर

	pckd_hw_min = dispc->feat->min_pcd;
	pckd_hw_max = 255;

	lck_max = dss_get_max_fck_rate(dispc->dss);

	pck_min = pck_min ? pck_min : 1;
	pck_max = pck_max ? pck_max : अच_दीर्घ_उच्च;

	lckd_start = max(DIV_ROUND_UP(dispc_freq, lck_max), 1ul);
	lckd_stop = min(dispc_freq / pck_min, 255ul);

	क्रम (lckd = lckd_start; lckd <= lckd_stop; ++lckd) अणु
		lck = dispc_freq / lckd;

		pckd_start = max(DIV_ROUND_UP(lck, pck_max), pckd_hw_min);
		pckd_stop = min(lck / pck_min, pckd_hw_max);

		क्रम (pckd = pckd_start; pckd <= pckd_stop; ++pckd) अणु
			pck = lck / pckd;

			/*
			 * For OMAP2/3 the DISPC fclk is the same as LCD's logic
			 * घड़ी, which means we're configuring DISPC fclk here
			 * also. Thus we need to use the calculated lck. For
			 * OMAP4+ the DISPC fclk is a separate घड़ी.
			 */
			अगर (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV))
				fck = dispc_core_clk_rate(dispc);
			अन्यथा
				fck = lck;

			अगर (fck < pck * min_fck_per_pck)
				जारी;

			अगर (func(lckd, pckd, lck, pck, data))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

व्योम dispc_mgr_set_घड़ी_भाग(काष्ठा dispc_device *dispc,
			     क्रमागत omap_channel channel,
			     स्थिर काष्ठा dispc_घड़ी_info *cinfo)
अणु
	DSSDBG("lck = %lu (%u)\n", cinfo->lck, cinfo->lck_भाग);
	DSSDBG("pck = %lu (%u)\n", cinfo->pck, cinfo->pck_भाग);

	dispc_mgr_set_lcd_भागisor(dispc, channel, cinfo->lck_भाग,
				  cinfo->pck_भाग);
पूर्ण

पूर्णांक dispc_mgr_get_घड़ी_भाग(काष्ठा dispc_device *dispc,
			    क्रमागत omap_channel channel,
			    काष्ठा dispc_घड़ी_info *cinfo)
अणु
	अचिन्हित दीर्घ fck;

	fck = dispc_fclk_rate(dispc);

	cinfo->lck_भाग = REG_GET(dispc, DISPC_DIVISORo(channel), 23, 16);
	cinfo->pck_भाग = REG_GET(dispc, DISPC_DIVISORo(channel), 7, 0);

	cinfo->lck = fck / cinfo->lck_भाग;
	cinfo->pck = cinfo->lck / cinfo->pck_भाग;

	वापस 0;
पूर्ण

u32 dispc_पढ़ो_irqstatus(काष्ठा dispc_device *dispc)
अणु
	वापस dispc_पढ़ो_reg(dispc, DISPC_IRQSTATUS);
पूर्ण

व्योम dispc_clear_irqstatus(काष्ठा dispc_device *dispc, u32 mask)
अणु
	dispc_ग_लिखो_reg(dispc, DISPC_IRQSTATUS, mask);
पूर्ण

व्योम dispc_ग_लिखो_irqenable(काष्ठा dispc_device *dispc, u32 mask)
अणु
	u32 old_mask = dispc_पढ़ो_reg(dispc, DISPC_IRQENABLE);

	/* clear the irqstatus क्रम newly enabled irqs */
	dispc_clear_irqstatus(dispc, (mask ^ old_mask) & mask);

	dispc_ग_लिखो_reg(dispc, DISPC_IRQENABLE, mask);

	/* flush posted ग_लिखो */
	dispc_पढ़ो_reg(dispc, DISPC_IRQENABLE);
पूर्ण

व्योम dispc_enable_sidle(काष्ठा dispc_device *dispc)
अणु
	/* SIDLEMODE: smart idle */
	REG_FLD_MOD(dispc, DISPC_SYSCONFIG, 2, 4, 3);
पूर्ण

व्योम dispc_disable_sidle(काष्ठा dispc_device *dispc)
अणु
	REG_FLD_MOD(dispc, DISPC_SYSCONFIG, 1, 4, 3);	/* SIDLEMODE: no idle */
पूर्ण

u32 dispc_mgr_gamma_size(काष्ठा dispc_device *dispc,
				क्रमागत omap_channel channel)
अणु
	स्थिर काष्ठा dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;

	अगर (!dispc->feat->has_gamma_table)
		वापस 0;

	वापस gdesc->len;
पूर्ण

अटल व्योम dispc_mgr_ग_लिखो_gamma_table(काष्ठा dispc_device *dispc,
					क्रमागत omap_channel channel)
अणु
	स्थिर काष्ठा dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;
	u32 *table = dispc->gamma_table[channel];
	अचिन्हित पूर्णांक i;

	DSSDBG("%s: channel %d\n", __func__, channel);

	क्रम (i = 0; i < gdesc->len; ++i) अणु
		u32 v = table[i];

		अगर (gdesc->has_index)
			v |= i << 24;
		अन्यथा अगर (i == 0)
			v |= 1 << 31;

		dispc_ग_लिखो_reg(dispc, gdesc->reg, v);
	पूर्ण
पूर्ण

अटल व्योम dispc_restore_gamma_tables(काष्ठा dispc_device *dispc)
अणु
	DSSDBG("%s()\n", __func__);

	अगर (!dispc->feat->has_gamma_table)
		वापस;

	dispc_mgr_ग_लिखो_gamma_table(dispc, OMAP_DSS_CHANNEL_LCD);

	dispc_mgr_ग_लिखो_gamma_table(dispc, OMAP_DSS_CHANNEL_DIGIT);

	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD2))
		dispc_mgr_ग_लिखो_gamma_table(dispc, OMAP_DSS_CHANNEL_LCD2);

	अगर (dispc_has_feature(dispc, FEAT_MGR_LCD3))
		dispc_mgr_ग_लिखो_gamma_table(dispc, OMAP_DSS_CHANNEL_LCD3);
पूर्ण

अटल स्थिर काष्ठा drm_color_lut dispc_mgr_gamma_शेष_lut[] = अणु
	अणु .red = 0, .green = 0, .blue = 0, पूर्ण,
	अणु .red = U16_MAX, .green = U16_MAX, .blue = U16_MAX, पूर्ण,
पूर्ण;

व्योम dispc_mgr_set_gamma(काष्ठा dispc_device *dispc,
				क्रमागत omap_channel channel,
				स्थिर काष्ठा drm_color_lut *lut,
				अचिन्हित पूर्णांक length)
अणु
	स्थिर काष्ठा dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;
	u32 *table = dispc->gamma_table[channel];
	uपूर्णांक i;

	DSSDBG("%s: channel %d, lut len %u, hw len %u\n", __func__,
	       channel, length, gdesc->len);

	अगर (!dispc->feat->has_gamma_table)
		वापस;

	अगर (lut == शून्य || length < 2) अणु
		lut = dispc_mgr_gamma_शेष_lut;
		length = ARRAY_SIZE(dispc_mgr_gamma_शेष_lut);
	पूर्ण

	क्रम (i = 0; i < length - 1; ++i) अणु
		uपूर्णांक first = i * (gdesc->len - 1) / (length - 1);
		uपूर्णांक last = (i + 1) * (gdesc->len - 1) / (length - 1);
		uपूर्णांक w = last - first;
		u16 r, g, b;
		uपूर्णांक j;

		अगर (w == 0)
			जारी;

		क्रम (j = 0; j <= w; j++) अणु
			r = (lut[i].red * (w - j) + lut[i+1].red * j) / w;
			g = (lut[i].green * (w - j) + lut[i+1].green * j) / w;
			b = (lut[i].blue * (w - j) + lut[i+1].blue * j) / w;

			r >>= 16 - gdesc->bits;
			g >>= 16 - gdesc->bits;
			b >>= 16 - gdesc->bits;

			table[first + j] = (r << (gdesc->bits * 2)) |
				(g << gdesc->bits) | b;
		पूर्ण
	पूर्ण

	अगर (dispc->is_enabled)
		dispc_mgr_ग_लिखो_gamma_table(dispc, channel);
पूर्ण

अटल पूर्णांक dispc_init_gamma_tables(काष्ठा dispc_device *dispc)
अणु
	पूर्णांक channel;

	अगर (!dispc->feat->has_gamma_table)
		वापस 0;

	क्रम (channel = 0; channel < ARRAY_SIZE(dispc->gamma_table); channel++) अणु
		स्थिर काष्ठा dispc_gamma_desc *gdesc = &mgr_desc[channel].gamma;
		u32 *gt;

		अगर (channel == OMAP_DSS_CHANNEL_LCD2 &&
		    !dispc_has_feature(dispc, FEAT_MGR_LCD2))
			जारी;

		अगर (channel == OMAP_DSS_CHANNEL_LCD3 &&
		    !dispc_has_feature(dispc, FEAT_MGR_LCD3))
			जारी;

		gt = devm_kदो_स्मृति_array(&dispc->pdev->dev, gdesc->len,
					माप(u32), GFP_KERNEL);
		अगर (!gt)
			वापस -ENOMEM;

		dispc->gamma_table[channel] = gt;

		dispc_mgr_set_gamma(dispc, channel, शून्य, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम _omap_dispc_initial_config(काष्ठा dispc_device *dispc)
अणु
	u32 l;

	/* Exclusively enable DISPC_CORE_CLK and set भागider to 1 */
	अगर (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV)) अणु
		l = dispc_पढ़ो_reg(dispc, DISPC_DIVISOR);
		/* Use DISPC_DIVISOR.LCD, instead of DISPC_DIVISOR1.LCD */
		l = FLD_MOD(l, 1, 0, 0);
		l = FLD_MOD(l, 1, 23, 16);
		dispc_ग_लिखो_reg(dispc, DISPC_DIVISOR, l);

		dispc->core_clk_rate = dispc_fclk_rate(dispc);
	पूर्ण

	/* Use gamma table mode, instead of palette mode */
	अगर (dispc->feat->has_gamma_table)
		REG_FLD_MOD(dispc, DISPC_CONFIG, 1, 3, 3);

	/* For older DSS versions (FEAT_FUNCGATED) this enables
	 * func-घड़ी स्वतः-gating. For newer versions
	 * (dispc->feat->has_gamma_table) this enables tv-out gamma tables.
	 */
	अगर (dispc_has_feature(dispc, FEAT_FUNCGATED) ||
	    dispc->feat->has_gamma_table)
		REG_FLD_MOD(dispc, DISPC_CONFIG, 1, 9, 9);

	dispc_set_loadmode(dispc, OMAP_DSS_LOAD_FRAME_ONLY);

	dispc_init_fअगरos(dispc);

	dispc_configure_burst_sizes(dispc);

	dispc_ovl_enable_zorder_planes(dispc);

	अगर (dispc->feat->mstandby_workaround)
		REG_FLD_MOD(dispc, DISPC_MSTANDBY_CTRL, 1, 0, 0);

	अगर (dispc_has_feature(dispc, FEAT_MFLAG))
		dispc_init_mflag(dispc);
पूर्ण

अटल स्थिर क्रमागत dispc_feature_id omap2_dispc_features_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
पूर्ण;

अटल स्थिर क्रमागत dispc_feature_id omap3_dispc_features_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
पूर्ण;

अटल स्थिर क्रमागत dispc_feature_id am43xx_dispc_features_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
पूर्ण;

अटल स्थिर क्रमागत dispc_feature_id omap4_dispc_features_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_CORE_CLK_DIV,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
पूर्ण;

अटल स्थिर क्रमागत dispc_feature_id omap5_dispc_features_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_MGR_LCD3,
	FEAT_CORE_CLK_DIV,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
	FEAT_MFLAG,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap2_dispc_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 11, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 27, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 8, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 24, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 8, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 9, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 25, 16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap3_dispc_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 11, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 27, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 10, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 9, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 25, 16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap4_dispc_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 15, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 31, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 15, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 10, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 26, 16 पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap2_dispc_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap3430_dispc_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap3630_dispc_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap4_dispc_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA |
		OMAP_DSS_OVL_CAP_ZORDER | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

#घोषणा COLOR_ARRAY(arr...) (स्थिर u32[]) अणु arr, 0 पूर्ण

अटल स्थिर u32 *omap2_dispc_supported_color_modes[] = अणु

	/* OMAP_DSS_GFX */
	COLOR_ARRAY(
	DRM_FORMAT_RGBX4444, DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888, DRM_FORMAT_RGB888),

	/* OMAP_DSS_VIDEO1 */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY),

	/* OMAP_DSS_VIDEO2 */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY),
पूर्ण;

अटल स्थिर u32 *omap3_dispc_supported_color_modes[] = अणु
	/* OMAP_DSS_GFX */
	COLOR_ARRAY(
	DRM_FORMAT_RGBX4444, DRM_FORMAT_ARGB4444,
	DRM_FORMAT_RGB565, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_RGBX8888),

	/* OMAP_DSS_VIDEO1 */
	COLOR_ARRAY(
	DRM_FORMAT_XRGB8888, DRM_FORMAT_RGB888,
	DRM_FORMAT_RGBX4444, DRM_FORMAT_RGB565,
	DRM_FORMAT_YUYV, DRM_FORMAT_UYVY),

	/* OMAP_DSS_VIDEO2 */
	COLOR_ARRAY(
	DRM_FORMAT_RGBX4444, DRM_FORMAT_ARGB4444,
	DRM_FORMAT_RGB565, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY, DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_RGBX8888),
पूर्ण;

अटल स्थिर u32 *omap4_dispc_supported_color_modes[] = अणु
	/* OMAP_DSS_GFX */
	COLOR_ARRAY(
	DRM_FORMAT_RGBX4444, DRM_FORMAT_ARGB4444,
	DRM_FORMAT_RGB565, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_RGBX8888,
	DRM_FORMAT_ARGB1555, DRM_FORMAT_XRGB4444,
	DRM_FORMAT_RGBA4444, DRM_FORMAT_XRGB1555),

	/* OMAP_DSS_VIDEO1 */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_RGBX4444,
	DRM_FORMAT_YUYV, DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_NV12,
	DRM_FORMAT_RGBA4444, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_UYVY,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_XRGB4444,
	DRM_FORMAT_RGBX8888),

       /* OMAP_DSS_VIDEO2 */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_RGBX4444,
	DRM_FORMAT_YUYV, DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_NV12,
	DRM_FORMAT_RGBA4444, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_UYVY,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_XRGB4444,
	DRM_FORMAT_RGBX8888),

	/* OMAP_DSS_VIDEO3 */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_RGBX4444,
	DRM_FORMAT_YUYV, DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_NV12,
	DRM_FORMAT_RGBA4444, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_UYVY,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_XRGB4444,
	DRM_FORMAT_RGBX8888),

	/* OMAP_DSS_WB */
	COLOR_ARRAY(
	DRM_FORMAT_RGB565, DRM_FORMAT_RGBX4444,
	DRM_FORMAT_YUYV, DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_NV12,
	DRM_FORMAT_RGBA4444, DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888, DRM_FORMAT_UYVY,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_XRGB4444,
	DRM_FORMAT_RGBX8888),
पूर्ण;

अटल स्थिर u32 omap3_dispc_supported_scaler_color_modes[] = अणु
	DRM_FORMAT_XRGB8888, DRM_FORMAT_RGB565, DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
	0,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap24xx_dispc_feats = अणु
	.sw_start		=	5,
	.fp_start		=	15,
	.bp_start		=	27,
	.sw_max			=	64,
	.vp_max			=	255,
	.hp_max			=	256,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	66500000,
	.max_करोwnscale		=	2,
	/*
	 * Assume the line width buffer to be 768 pixels as OMAP2 DISPC scaler
	 * cannot scale an image width larger than 768.
	 */
	.max_line_width		=	768,
	.min_pcd		=	2,
	.calc_scaling		=	dispc_ovl_calc_scaling_24xx,
	.calc_core_clk		=	calc_core_clk_24xx,
	.num_fअगरos		=	3,
	.features		=	omap2_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap2_dispc_features_list),
	.reg_fields		=	omap2_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap2_dispc_reg_fields),
	.overlay_caps		=	omap2_dispc_overlay_caps,
	.supported_color_modes	=	omap2_dispc_supported_color_modes,
	.supported_scaler_color_modes = COLOR_ARRAY(DRM_FORMAT_XRGB8888),
	.num_mgrs		=	2,
	.num_ovls		=	3,
	.buffer_size_unit	=	1,
	.burst_size_unit	=	8,
	.no_frameकरोne_tv	=	true,
	.set_max_preload	=	false,
	.last_pixel_inc_missing	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap34xx_rev1_0_dispc_feats = अणु
	.sw_start		=	5,
	.fp_start		=	15,
	.bp_start		=	27,
	.sw_max			=	64,
	.vp_max			=	255,
	.hp_max			=	256,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	173000000,
	.max_tv_pclk		=	59000000,
	.max_करोwnscale		=	4,
	.max_line_width		=	1024,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
	.features		=	omap3_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap3_dispc_features_list),
	.reg_fields		=	omap3_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap3_dispc_reg_fields),
	.overlay_caps		=	omap3430_dispc_overlay_caps,
	.supported_color_modes	=	omap3_dispc_supported_color_modes,
	.supported_scaler_color_modes = omap3_dispc_supported_scaler_color_modes,
	.num_mgrs		=	2,
	.num_ovls		=	3,
	.buffer_size_unit	=	1,
	.burst_size_unit	=	8,
	.no_frameकरोne_tv	=	true,
	.set_max_preload	=	false,
	.last_pixel_inc_missing	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap34xx_rev3_0_dispc_feats = अणु
	.sw_start		=	7,
	.fp_start		=	19,
	.bp_start		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	173000000,
	.max_tv_pclk		=	59000000,
	.max_करोwnscale		=	4,
	.max_line_width		=	1024,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
	.features		=	omap3_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap3_dispc_features_list),
	.reg_fields		=	omap3_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap3_dispc_reg_fields),
	.overlay_caps		=	omap3430_dispc_overlay_caps,
	.supported_color_modes	=	omap3_dispc_supported_color_modes,
	.supported_scaler_color_modes = omap3_dispc_supported_scaler_color_modes,
	.num_mgrs		=	2,
	.num_ovls		=	3,
	.buffer_size_unit	=	1,
	.burst_size_unit	=	8,
	.no_frameकरोne_tv	=	true,
	.set_max_preload	=	false,
	.last_pixel_inc_missing	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap36xx_dispc_feats = अणु
	.sw_start		=	7,
	.fp_start		=	19,
	.bp_start		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	173000000,
	.max_tv_pclk		=	59000000,
	.max_करोwnscale		=	4,
	.max_line_width		=	1024,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
	.features		=	omap3_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap3_dispc_features_list),
	.reg_fields		=	omap3_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap3_dispc_reg_fields),
	.overlay_caps		=	omap3630_dispc_overlay_caps,
	.supported_color_modes	=	omap3_dispc_supported_color_modes,
	.supported_scaler_color_modes = omap3_dispc_supported_scaler_color_modes,
	.num_mgrs		=	2,
	.num_ovls		=	3,
	.buffer_size_unit	=	1,
	.burst_size_unit	=	8,
	.no_frameकरोne_tv	=	true,
	.set_max_preload	=	false,
	.last_pixel_inc_missing	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features am43xx_dispc_feats = अणु
	.sw_start		=	7,
	.fp_start		=	19,
	.bp_start		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	173000000,
	.max_tv_pclk		=	59000000,
	.max_करोwnscale		=	4,
	.max_line_width		=	1024,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
	.features		=	am43xx_dispc_features_list,
	.num_features		=	ARRAY_SIZE(am43xx_dispc_features_list),
	.reg_fields		=	omap3_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap3_dispc_reg_fields),
	.overlay_caps		=	omap3430_dispc_overlay_caps,
	.supported_color_modes	=	omap3_dispc_supported_color_modes,
	.supported_scaler_color_modes = omap3_dispc_supported_scaler_color_modes,
	.num_mgrs		=	1,
	.num_ovls		=	3,
	.buffer_size_unit	=	1,
	.burst_size_unit	=	8,
	.no_frameकरोne_tv	=	true,
	.set_max_preload	=	false,
	.last_pixel_inc_missing	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap44xx_dispc_feats = अणु
	.sw_start		=	7,
	.fp_start		=	19,
	.bp_start		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgr_width_start	=	10,
	.mgr_height_start	=	26,
	.mgr_width_max		=	2048,
	.mgr_height_max		=	2048,
	.max_lcd_pclk		=	170000000,
	.max_tv_pclk		=	185625000,
	.max_करोwnscale		=	4,
	.max_line_width		=	2048,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_44xx,
	.calc_core_clk		=	calc_core_clk_44xx,
	.num_fअगरos		=	5,
	.features		=	omap4_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap4_dispc_features_list),
	.reg_fields		=	omap4_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap4_dispc_reg_fields),
	.overlay_caps		=	omap4_dispc_overlay_caps,
	.supported_color_modes	=	omap4_dispc_supported_color_modes,
	.num_mgrs		=	3,
	.num_ovls		=	4,
	.buffer_size_unit	=	16,
	.burst_size_unit	=	16,
	.gfx_fअगरo_workaround	=	true,
	.set_max_preload	=	true,
	.supports_sync_align	=	true,
	.has_ग_लिखोback		=	true,
	.supports_द्विगुन_pixel	=	true,
	.reverse_ilace_field_order =	true,
	.has_gamma_table	=	true,
	.has_gamma_i734_bug	=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features omap54xx_dispc_feats = अणु
	.sw_start		=	7,
	.fp_start		=	19,
	.bp_start		=	31,
	.sw_max			=	256,
	.vp_max			=	4095,
	.hp_max			=	4096,
	.mgr_width_start	=	11,
	.mgr_height_start	=	27,
	.mgr_width_max		=	4096,
	.mgr_height_max		=	4096,
	.max_lcd_pclk		=	170000000,
	.max_tv_pclk		=	186000000,
	.max_करोwnscale		=	4,
	.max_line_width		=	2048,
	.min_pcd		=	1,
	.calc_scaling		=	dispc_ovl_calc_scaling_44xx,
	.calc_core_clk		=	calc_core_clk_44xx,
	.num_fअगरos		=	5,
	.features		=	omap5_dispc_features_list,
	.num_features		=	ARRAY_SIZE(omap5_dispc_features_list),
	.reg_fields		=	omap4_dispc_reg_fields,
	.num_reg_fields		=	ARRAY_SIZE(omap4_dispc_reg_fields),
	.overlay_caps		=	omap4_dispc_overlay_caps,
	.supported_color_modes	=	omap4_dispc_supported_color_modes,
	.num_mgrs		=	4,
	.num_ovls		=	4,
	.buffer_size_unit	=	16,
	.burst_size_unit	=	16,
	.gfx_fअगरo_workaround	=	true,
	.mstandby_workaround	=	true,
	.set_max_preload	=	true,
	.supports_sync_align	=	true,
	.has_ग_लिखोback		=	true,
	.supports_द्विगुन_pixel	=	true,
	.reverse_ilace_field_order =	true,
	.has_gamma_table	=	true,
	.has_gamma_i734_bug	=	true,
पूर्ण;

अटल irqवापस_t dispc_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा dispc_device *dispc = arg;

	अगर (!dispc->is_enabled)
		वापस IRQ_NONE;

	वापस dispc->user_handler(irq, dispc->user_data);
पूर्ण

पूर्णांक dispc_request_irq(काष्ठा dispc_device *dispc, irq_handler_t handler,
			     व्योम *dev_id)
अणु
	पूर्णांक r;

	अगर (dispc->user_handler != शून्य)
		वापस -EBUSY;

	dispc->user_handler = handler;
	dispc->user_data = dev_id;

	/* ensure the dispc_irq_handler sees the values above */
	smp_wmb();

	r = devm_request_irq(&dispc->pdev->dev, dispc->irq, dispc_irq_handler,
			     IRQF_SHARED, "OMAP DISPC", dispc);
	अगर (r) अणु
		dispc->user_handler = शून्य;
		dispc->user_data = शून्य;
	पूर्ण

	वापस r;
पूर्ण

व्योम dispc_मुक्त_irq(काष्ठा dispc_device *dispc, व्योम *dev_id)
अणु
	devm_मुक्त_irq(&dispc->pdev->dev, dispc->irq, dispc);

	dispc->user_handler = शून्य;
	dispc->user_data = शून्य;
पूर्ण

u32 dispc_get_memory_bandwidth_limit(काष्ठा dispc_device *dispc)
अणु
	u32 limit = 0;

	/* Optional maximum memory bandwidth */
	of_property_पढ़ो_u32(dispc->pdev->dev.of_node, "max-memory-bandwidth",
			     &limit);

	वापस limit;
पूर्ण

/*
 * Workaround क्रम errata i734 in DSS dispc
 *  - LCD1 Gamma Correction Is Not Working When GFX Pipe Is Disabled
 *
 * For gamma tables to work on LCD1 the GFX plane has to be used at
 * least once after DSS HW has come out of reset. The workaround
 * sets up a minimal LCD setup with GFX plane and रुकोs क्रम one
 * vertical sync irq beक्रमe disabling the setup and continuing with
 * the context restore. The physical outमाला_दो are gated during the
 * operation. This workaround requires that gamma table's LOADMODE
 * is set to 0x2 in DISPC_CONTROL1 रेजिस्टर.
 *
 * For details see:
 * OMAP543x Mulसमयdia Device Silicon Revision 2.0 Silicon Errata
 * Literature Number: SWPZ037E
 * Or some other relevant errata करोcument क्रम the DSS IP version.
 */

अटल स्थिर काष्ठा dispc_errata_i734_data अणु
	काष्ठा videomode vm;
	काष्ठा omap_overlay_info ovli;
	काष्ठा omap_overlay_manager_info mgri;
	काष्ठा dss_lcd_mgr_config lcd_conf;
पूर्ण i734 = अणु
	.vm = अणु
		.hactive = 8, .vactive = 1,
		.pixelघड़ी = 16000000,
		.hsync_len = 8, .hfront_porch = 4, .hback_porch = 4,
		.vsync_len = 1, .vfront_porch = 1, .vback_porch = 1,

		.flags = DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW |
			 DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_SYNC_POSEDGE |
			 DISPLAY_FLAGS_PIXDATA_POSEDGE,
	पूर्ण,
	.ovli = अणु
		.screen_width = 1,
		.width = 1, .height = 1,
		.fourcc = DRM_FORMAT_XRGB8888,
		.rotation = DRM_MODE_ROTATE_0,
		.rotation_type = OMAP_DSS_ROT_NONE,
		.pos_x = 0, .pos_y = 0,
		.out_width = 0, .out_height = 0,
		.global_alpha = 0xff,
		.pre_mult_alpha = 0,
		.zorder = 0,
	पूर्ण,
	.mgri = अणु
		.शेष_color = 0,
		.trans_enabled = false,
		.partial_alpha_enabled = false,
		.cpr_enable = false,
	पूर्ण,
	.lcd_conf = अणु
		.io_pad_mode = DSS_IO_PAD_MODE_BYPASS,
		.stallmode = false,
		.fअगरohandcheck = false,
		.घड़ी_info = अणु
			.lck_भाग = 1,
			.pck_भाग = 2,
		पूर्ण,
		.video_port_width = 24,
		.lcden_sig_polarity = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा i734_buf अणु
	माप_प्रकार size;
	dma_addr_t paddr;
	व्योम *vaddr;
पूर्ण i734_buf;

अटल पूर्णांक dispc_errata_i734_wa_init(काष्ठा dispc_device *dispc)
अणु
	अगर (!dispc->feat->has_gamma_i734_bug)
		वापस 0;

	i734_buf.size = i734.ovli.width * i734.ovli.height *
		color_mode_to_bpp(i734.ovli.fourcc) / 8;

	i734_buf.vaddr = dma_alloc_wc(&dispc->pdev->dev, i734_buf.size,
				      &i734_buf.paddr, GFP_KERNEL);
	अगर (!i734_buf.vaddr) अणु
		dev_err(&dispc->pdev->dev, "%s: dma_alloc_wc failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dispc_errata_i734_wa_fini(काष्ठा dispc_device *dispc)
अणु
	अगर (!dispc->feat->has_gamma_i734_bug)
		वापस;

	dma_मुक्त_wc(&dispc->pdev->dev, i734_buf.size, i734_buf.vaddr,
		    i734_buf.paddr);
पूर्ण

अटल व्योम dispc_errata_i734_wa(काष्ठा dispc_device *dispc)
अणु
	u32 frameकरोne_irq = dispc_mgr_get_frameकरोne_irq(dispc,
							OMAP_DSS_CHANNEL_LCD);
	काष्ठा omap_overlay_info ovli;
	काष्ठा dss_lcd_mgr_config lcd_conf;
	u32 gatestate;
	अचिन्हित पूर्णांक count;

	अगर (!dispc->feat->has_gamma_i734_bug)
		वापस;

	gatestate = REG_GET(dispc, DISPC_CONFIG, 8, 4);

	ovli = i734.ovli;
	ovli.paddr = i734_buf.paddr;
	lcd_conf = i734.lcd_conf;

	/* Gate all LCD1 outमाला_दो */
	REG_FLD_MOD(dispc, DISPC_CONFIG, 0x1f, 8, 4);

	/* Setup and enable GFX plane */
	dispc_ovl_setup(dispc, OMAP_DSS_GFX, &ovli, &i734.vm, false,
			OMAP_DSS_CHANNEL_LCD);
	dispc_ovl_enable(dispc, OMAP_DSS_GFX, true);

	/* Set up and enable display manager क्रम LCD1 */
	dispc_mgr_setup(dispc, OMAP_DSS_CHANNEL_LCD, &i734.mgri);
	dispc_calc_घड़ी_rates(dispc, dss_get_dispc_clk_rate(dispc->dss),
			       &lcd_conf.घड़ी_info);
	dispc_mgr_set_lcd_config(dispc, OMAP_DSS_CHANNEL_LCD, &lcd_conf);
	dispc_mgr_set_timings(dispc, OMAP_DSS_CHANNEL_LCD, &i734.vm);

	dispc_clear_irqstatus(dispc, frameकरोne_irq);

	/* Enable and shut the channel to produce just one frame */
	dispc_mgr_enable(dispc, OMAP_DSS_CHANNEL_LCD, true);
	dispc_mgr_enable(dispc, OMAP_DSS_CHANNEL_LCD, false);

	/* Busy रुको क्रम frameकरोne. We can't fiddle with irq handlers
	 * in PM resume. Typically the loop runs less than 5 बार and
	 * रुकोs less than a micro second.
	 */
	count = 0;
	जबतक (!(dispc_पढ़ो_irqstatus(dispc) & frameकरोne_irq)) अणु
		अगर (count++ > 10000) अणु
			dev_err(&dispc->pdev->dev, "%s: framedone timeout\n",
				__func__);
			अवरोध;
		पूर्ण
	पूर्ण
	dispc_ovl_enable(dispc, OMAP_DSS_GFX, false);

	/* Clear all irq bits beक्रमe continuing */
	dispc_clear_irqstatus(dispc, 0xffffffff);

	/* Restore the original state to LCD1 output gates */
	REG_FLD_MOD(dispc, DISPC_CONFIG, gatestate, 8, 4);
पूर्ण

/* DISPC HW IP initialisation */
अटल स्थिर काष्ठा of_device_id dispc_of_match[] = अणु
	अणु .compatible = "ti,omap2-dispc", .data = &omap24xx_dispc_feats पूर्ण,
	अणु .compatible = "ti,omap3-dispc", .data = &omap36xx_dispc_feats पूर्ण,
	अणु .compatible = "ti,omap4-dispc", .data = &omap44xx_dispc_feats पूर्ण,
	अणु .compatible = "ti,omap5-dispc", .data = &omap54xx_dispc_feats पूर्ण,
	अणु .compatible = "ti,dra7-dispc",  .data = &omap54xx_dispc_feats पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute dispc_soc_devices[] = अणु
	अणु .machine = "OMAP3[45]*",
	  .revision = "ES[12].?",	.data = &omap34xx_rev1_0_dispc_feats पूर्ण,
	अणु .machine = "OMAP3[45]*",	.data = &omap34xx_rev3_0_dispc_feats पूर्ण,
	अणु .machine = "AM35*",		.data = &omap34xx_rev3_0_dispc_feats पूर्ण,
	अणु .machine = "AM43*",		.data = &am43xx_dispc_feats पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक dispc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा dss_device *dss = dss_get_device(master);
	काष्ठा dispc_device *dispc;
	u32 rev;
	पूर्णांक r = 0;
	काष्ठा resource *dispc_mem;
	काष्ठा device_node *np = pdev->dev.of_node;

	dispc = kzalloc(माप(*dispc), GFP_KERNEL);
	अगर (!dispc)
		वापस -ENOMEM;

	dispc->pdev = pdev;
	platक्रमm_set_drvdata(pdev, dispc);
	dispc->dss = dss;

	/*
	 * The OMAP3-based models can't be told apart using the compatible
	 * string, use SoC device matching.
	 */
	soc = soc_device_match(dispc_soc_devices);
	अगर (soc)
		dispc->feat = soc->data;
	अन्यथा
		dispc->feat = of_match_device(dispc_of_match, &pdev->dev)->data;

	r = dispc_errata_i734_wa_init(dispc);
	अगर (r)
		जाओ err_मुक्त;

	dispc_mem = platक्रमm_get_resource(dispc->pdev, IORESOURCE_MEM, 0);
	dispc->base = devm_ioremap_resource(&pdev->dev, dispc_mem);
	अगर (IS_ERR(dispc->base)) अणु
		r = PTR_ERR(dispc->base);
		जाओ err_मुक्त;
	पूर्ण

	dispc->irq = platक्रमm_get_irq(dispc->pdev, 0);
	अगर (dispc->irq < 0) अणु
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	अगर (np && of_property_पढ़ो_bool(np, "syscon-pol")) अणु
		dispc->syscon_pol = syscon_regmap_lookup_by_phandle(np, "syscon-pol");
		अगर (IS_ERR(dispc->syscon_pol)) अणु
			dev_err(&pdev->dev, "failed to get syscon-pol regmap\n");
			r = PTR_ERR(dispc->syscon_pol);
			जाओ err_मुक्त;
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(np, "syscon-pol", 1,
				&dispc->syscon_pol_offset)) अणु
			dev_err(&pdev->dev, "failed to get syscon-pol offset\n");
			r = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	r = dispc_init_gamma_tables(dispc);
	अगर (r)
		जाओ err_मुक्त;

	pm_runसमय_enable(&pdev->dev);

	r = dispc_runसमय_get(dispc);
	अगर (r)
		जाओ err_runसमय_get;

	_omap_dispc_initial_config(dispc);

	rev = dispc_पढ़ो_reg(dispc, DISPC_REVISION);
	dev_dbg(&pdev->dev, "OMAP DISPC rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dispc_runसमय_put(dispc);

	dss->dispc = dispc;

	dispc->debugfs = dss_debugfs_create_file(dss, "dispc", dispc_dump_regs,
						 dispc);

	वापस 0;

err_runसमय_get:
	pm_runसमय_disable(&pdev->dev);
err_मुक्त:
	kमुक्त(dispc);
	वापस r;
पूर्ण

अटल व्योम dispc_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dispc_device *dispc = dev_get_drvdata(dev);
	काष्ठा dss_device *dss = dispc->dss;

	dss_debugfs_हटाओ_file(dispc->debugfs);

	dss->dispc = शून्य;

	pm_runसमय_disable(dev);

	dispc_errata_i734_wa_fini(dispc);

	kमुक्त(dispc);
पूर्ण

अटल स्थिर काष्ठा component_ops dispc_component_ops = अणु
	.bind	= dispc_bind,
	.unbind	= dispc_unbind,
पूर्ण;

अटल पूर्णांक dispc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &dispc_component_ops);
पूर्ण

अटल पूर्णांक dispc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &dispc_component_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dispc_device *dispc = dev_get_drvdata(dev);

	dispc->is_enabled = false;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();
	/* रुको क्रम current handler to finish beक्रमe turning the DISPC off */
	synchronize_irq(dispc->irq);

	dispc_save_context(dispc);

	वापस 0;
पूर्ण

अटल पूर्णांक dispc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dispc_device *dispc = dev_get_drvdata(dev);

	/*
	 * The reset value क्रम load mode is 0 (OMAP_DSS_LOAD_CLUT_AND_FRAME)
	 * but we always initialize it to 2 (OMAP_DSS_LOAD_FRAME_ONLY) in
	 * _omap_dispc_initial_config(). We can thus use it to detect अगर
	 * we have lost रेजिस्टर context.
	 */
	अगर (REG_GET(dispc, DISPC_CONFIG, 2, 1) != OMAP_DSS_LOAD_FRAME_ONLY) अणु
		_omap_dispc_initial_config(dispc);

		dispc_errata_i734_wa(dispc);

		dispc_restore_context(dispc);

		dispc_restore_gamma_tables(dispc);
	पूर्ण

	dispc->is_enabled = true;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dispc_pm_ops = अणु
	.runसमय_suspend = dispc_runसमय_suspend,
	.runसमय_resume = dispc_runसमय_resume,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver omap_dispchw_driver = अणु
	.probe		= dispc_probe,
	.हटाओ         = dispc_हटाओ,
	.driver         = अणु
		.name   = "omapdss_dispc",
		.pm	= &dispc_pm_ops,
		.of_match_table = dispc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
