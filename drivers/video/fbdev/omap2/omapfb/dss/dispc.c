<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/dispc.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
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
#समावेश <linux/component.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"
#समावेश "dispc.h"

/* DISPC */
#घोषणा DISPC_SZ_REGS			SZ_4K

क्रमागत omap_burst_size अणु
	BURST_SIZE_X2 = 0,
	BURST_SIZE_X4 = 1,
	BURST_SIZE_X8 = 2,
पूर्ण;

#घोषणा REG_GET(idx, start, end) \
	FLD_GET(dispc_पढ़ो_reg(idx), start, end)

#घोषणा REG_FLD_MOD(idx, val, start, end)				\
	dispc_ग_लिखो_reg(idx, FLD_MOD(dispc_पढ़ो_reg(idx), val, start, end))

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
	पूर्णांक (*calc_scaling) (अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, पूर्णांक *decim_x, पूर्णांक *decim_y,
		u16 pos_x, अचिन्हित दीर्घ *core_clk, bool mem_to_mem);
	अचिन्हित दीर्घ (*calc_core_clk) (अचिन्हित दीर्घ pclk,
		u16 width, u16 height, u16 out_width, u16 out_height,
		bool mem_to_mem);
	u8 num_fअगरos;

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
पूर्ण;

#घोषणा DISPC_MAX_NR_FIFOS 5

अटल काष्ठा अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem    *base;

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

	स्थिर काष्ठा dispc_features *feat;

	bool is_enabled;

	काष्ठा regmap *syscon_pol;
	u32 syscon_pol_offset;

	/* DISPC_CONTROL & DISPC_CONFIG lock*/
	spinlock_t control_lock;
पूर्ण dispc;

क्रमागत omap_color_component अणु
	/* used क्रम all color क्रमmats क्रम OMAP3 and earlier
	 * and क्रम RGB and Y color component on OMAP4
	 */
	DISPC_COLOR_COMPONENT_RGB_Y		= 1 << 0,
	/* used क्रम UV component क्रम
	 * OMAP_DSS_COLOR_YUV2, OMAP_DSS_COLOR_UYVY, OMAP_DSS_COLOR_NV12
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

काष्ठा dispc_reg_field अणु
	u16 reg;
	u8 high;
	u8 low;
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u32 vsync_irq;
	u32 frameकरोne_irq;
	u32 sync_lost_irq;
	काष्ठा dispc_reg_field reg_desc[DISPC_MGR_FLD_NUM];
पूर्ण mgr_desc[] = अणु
	[OMAP_DSS_CHANNEL_LCD] = अणु
		.name		= "LCD",
		.vsync_irq	= DISPC_IRQ_VSYNC,
		.frameकरोne_irq	= DISPC_IRQ_FRAMEDONE,
		.sync_lost_irq	= DISPC_IRQ_SYNC_LOST,
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

काष्ठा color_conv_coef अणु
	पूर्णांक ry, rcr, rcb, gy, gcr, gcb, by, bcr, bcb;
	पूर्णांक full_range;
पूर्ण;

अटल अचिन्हित दीर्घ dispc_fclk_rate(व्योम);
अटल अचिन्हित दीर्घ dispc_core_clk_rate(व्योम);
अटल अचिन्हित दीर्घ dispc_mgr_lclk_rate(क्रमागत omap_channel channel);
अटल अचिन्हित दीर्घ dispc_mgr_pclk_rate(क्रमागत omap_channel channel);

अटल अचिन्हित दीर्घ dispc_plane_pclk_rate(क्रमागत omap_plane plane);
अटल अचिन्हित दीर्घ dispc_plane_lclk_rate(क्रमागत omap_plane plane);

अटल अंतरभूत व्योम dispc_ग_लिखो_reg(स्थिर u16 idx, u32 val)
अणु
	__raw_ग_लिखोl(val, dispc.base + idx);
पूर्ण

अटल अंतरभूत u32 dispc_पढ़ो_reg(स्थिर u16 idx)
अणु
	वापस __raw_पढ़ोl(dispc.base + idx);
पूर्ण

अटल u32 mgr_fld_पढ़ो(क्रमागत omap_channel channel, क्रमागत mgr_reg_fields regfld)
अणु
	स्थिर काष्ठा dispc_reg_field rfld = mgr_desc[channel].reg_desc[regfld];
	वापस REG_GET(rfld.reg, rfld.high, rfld.low);
पूर्ण

अटल व्योम mgr_fld_ग_लिखो(क्रमागत omap_channel channel,
					क्रमागत mgr_reg_fields regfld, पूर्णांक val) अणु
	स्थिर काष्ठा dispc_reg_field rfld = mgr_desc[channel].reg_desc[regfld];
	स्थिर bool need_lock = rfld.reg == DISPC_CONTROL || rfld.reg == DISPC_CONFIG;
	अचिन्हित दीर्घ flags;

	अगर (need_lock)
		spin_lock_irqsave(&dispc.control_lock, flags);

	REG_FLD_MOD(rfld.reg, val, rfld.high, rfld.low);

	अगर (need_lock)
		spin_unlock_irqrestore(&dispc.control_lock, flags);
पूर्ण

#घोषणा SR(reg) \
	dispc.ctx[DISPC_##reg / माप(u32)] = dispc_पढ़ो_reg(DISPC_##reg)
#घोषणा RR(reg) \
	dispc_ग_लिखो_reg(DISPC_##reg, dispc.ctx[DISPC_##reg / माप(u32)])

अटल व्योम dispc_save_context(व्योम)
अणु
	पूर्णांक i, j;

	DSSDBG("dispc_save_context\n");

	SR(IRQENABLE);
	SR(CONTROL);
	SR(CONFIG);
	SR(LINE_NUMBER);
	अगर (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER) ||
			dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		SR(GLOBAL_ALPHA);
	अगर (dss_has_feature(FEAT_MGR_LCD2)) अणु
		SR(CONTROL2);
		SR(CONFIG2);
	पूर्ण
	अगर (dss_has_feature(FEAT_MGR_LCD3)) अणु
		SR(CONTROL3);
		SR(CONFIG3);
	पूर्ण

	क्रम (i = 0; i < dss_feat_get_num_mgrs(); i++) अणु
		SR(DEFAULT_COLOR(i));
		SR(TRANS_COLOR(i));
		SR(SIZE_MGR(i));
		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;
		SR(TIMING_H(i));
		SR(TIMING_V(i));
		SR(POL_FREQ(i));
		SR(DIVISORo(i));

		SR(DATA_CYCLE1(i));
		SR(DATA_CYCLE2(i));
		SR(DATA_CYCLE3(i));

		अगर (dss_has_feature(FEAT_CPR)) अणु
			SR(CPR_COEF_R(i));
			SR(CPR_COEF_G(i));
			SR(CPR_COEF_B(i));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dss_feat_get_num_ovls(); i++) अणु
		SR(OVL_BA0(i));
		SR(OVL_BA1(i));
		SR(OVL_POSITION(i));
		SR(OVL_SIZE(i));
		SR(OVL_ATTRIBUTES(i));
		SR(OVL_FIFO_THRESHOLD(i));
		SR(OVL_ROW_INC(i));
		SR(OVL_PIXEL_INC(i));
		अगर (dss_has_feature(FEAT_PRELOAD))
			SR(OVL_PRELOAD(i));
		अगर (i == OMAP_DSS_GFX) अणु
			SR(OVL_WINDOW_SKIP(i));
			SR(OVL_TABLE_BA(i));
			जारी;
		पूर्ण
		SR(OVL_FIR(i));
		SR(OVL_PICTURE_SIZE(i));
		SR(OVL_ACCU0(i));
		SR(OVL_ACCU1(i));

		क्रम (j = 0; j < 8; j++)
			SR(OVL_FIR_COEF_H(i, j));

		क्रम (j = 0; j < 8; j++)
			SR(OVL_FIR_COEF_HV(i, j));

		क्रम (j = 0; j < 5; j++)
			SR(OVL_CONV_COEF(i, j));

		अगर (dss_has_feature(FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_V(i, j));
		पूर्ण

		अगर (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) अणु
			SR(OVL_BA0_UV(i));
			SR(OVL_BA1_UV(i));
			SR(OVL_FIR2(i));
			SR(OVL_ACCU2_0(i));
			SR(OVL_ACCU2_1(i));

			क्रम (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_H2(i, j));

			क्रम (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_HV2(i, j));

			क्रम (j = 0; j < 8; j++)
				SR(OVL_FIR_COEF_V2(i, j));
		पूर्ण
		अगर (dss_has_feature(FEAT_ATTR2))
			SR(OVL_ATTRIBUTES2(i));
	पूर्ण

	अगर (dss_has_feature(FEAT_CORE_CLK_DIV))
		SR(DIVISOR);

	dispc.ctx_valid = true;

	DSSDBG("context saved\n");
पूर्ण

अटल व्योम dispc_restore_context(व्योम)
अणु
	पूर्णांक i, j;

	DSSDBG("dispc_restore_context\n");

	अगर (!dispc.ctx_valid)
		वापस;

	/*RR(IRQENABLE);*/
	/*RR(CONTROL);*/
	RR(CONFIG);
	RR(LINE_NUMBER);
	अगर (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER) ||
			dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		RR(GLOBAL_ALPHA);
	अगर (dss_has_feature(FEAT_MGR_LCD2))
		RR(CONFIG2);
	अगर (dss_has_feature(FEAT_MGR_LCD3))
		RR(CONFIG3);

	क्रम (i = 0; i < dss_feat_get_num_mgrs(); i++) अणु
		RR(DEFAULT_COLOR(i));
		RR(TRANS_COLOR(i));
		RR(SIZE_MGR(i));
		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;
		RR(TIMING_H(i));
		RR(TIMING_V(i));
		RR(POL_FREQ(i));
		RR(DIVISORo(i));

		RR(DATA_CYCLE1(i));
		RR(DATA_CYCLE2(i));
		RR(DATA_CYCLE3(i));

		अगर (dss_has_feature(FEAT_CPR)) अणु
			RR(CPR_COEF_R(i));
			RR(CPR_COEF_G(i));
			RR(CPR_COEF_B(i));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dss_feat_get_num_ovls(); i++) अणु
		RR(OVL_BA0(i));
		RR(OVL_BA1(i));
		RR(OVL_POSITION(i));
		RR(OVL_SIZE(i));
		RR(OVL_ATTRIBUTES(i));
		RR(OVL_FIFO_THRESHOLD(i));
		RR(OVL_ROW_INC(i));
		RR(OVL_PIXEL_INC(i));
		अगर (dss_has_feature(FEAT_PRELOAD))
			RR(OVL_PRELOAD(i));
		अगर (i == OMAP_DSS_GFX) अणु
			RR(OVL_WINDOW_SKIP(i));
			RR(OVL_TABLE_BA(i));
			जारी;
		पूर्ण
		RR(OVL_FIR(i));
		RR(OVL_PICTURE_SIZE(i));
		RR(OVL_ACCU0(i));
		RR(OVL_ACCU1(i));

		क्रम (j = 0; j < 8; j++)
			RR(OVL_FIR_COEF_H(i, j));

		क्रम (j = 0; j < 8; j++)
			RR(OVL_FIR_COEF_HV(i, j));

		क्रम (j = 0; j < 5; j++)
			RR(OVL_CONV_COEF(i, j));

		अगर (dss_has_feature(FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				RR(OVL_FIR_COEF_V(i, j));
		पूर्ण

		अगर (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) अणु
			RR(OVL_BA0_UV(i));
			RR(OVL_BA1_UV(i));
			RR(OVL_FIR2(i));
			RR(OVL_ACCU2_0(i));
			RR(OVL_ACCU2_1(i));

			क्रम (j = 0; j < 8; j++)
				RR(OVL_FIR_COEF_H2(i, j));

			क्रम (j = 0; j < 8; j++)
				RR(OVL_FIR_COEF_HV2(i, j));

			क्रम (j = 0; j < 8; j++)
				RR(OVL_FIR_COEF_V2(i, j));
		पूर्ण
		अगर (dss_has_feature(FEAT_ATTR2))
			RR(OVL_ATTRIBUTES2(i));
	पूर्ण

	अगर (dss_has_feature(FEAT_CORE_CLK_DIV))
		RR(DIVISOR);

	/* enable last, because LCD & DIGIT enable are here */
	RR(CONTROL);
	अगर (dss_has_feature(FEAT_MGR_LCD2))
		RR(CONTROL2);
	अगर (dss_has_feature(FEAT_MGR_LCD3))
		RR(CONTROL3);
	/* clear spurious SYNC_LOST_DIGIT पूर्णांकerrupts */
	dispc_clear_irqstatus(DISPC_IRQ_SYNC_LOST_DIGIT);

	/*
	 * enable last so IRQs won't trigger beक्रमe
	 * the context is fully restored
	 */
	RR(IRQENABLE);

	DSSDBG("context restored\n");
पूर्ण

#अघोषित SR
#अघोषित RR

पूर्णांक dispc_runसमय_get(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("dispc_runtime_get\n");

	r = pm_runसमय_get_sync(&dispc.pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_sync(&dispc.pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dispc_runसमय_get);

व्योम dispc_runसमय_put(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("dispc_runtime_put\n");

	r = pm_runसमय_put_sync(&dispc.pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण
EXPORT_SYMBOL(dispc_runसमय_put);

u32 dispc_mgr_get_vsync_irq(क्रमागत omap_channel channel)
अणु
	वापस mgr_desc[channel].vsync_irq;
पूर्ण
EXPORT_SYMBOL(dispc_mgr_get_vsync_irq);

u32 dispc_mgr_get_frameकरोne_irq(क्रमागत omap_channel channel)
अणु
	अगर (channel == OMAP_DSS_CHANNEL_DIGIT && dispc.feat->no_frameकरोne_tv)
		वापस 0;

	वापस mgr_desc[channel].frameकरोne_irq;
पूर्ण
EXPORT_SYMBOL(dispc_mgr_get_frameकरोne_irq);

u32 dispc_mgr_get_sync_lost_irq(क्रमागत omap_channel channel)
अणु
	वापस mgr_desc[channel].sync_lost_irq;
पूर्ण
EXPORT_SYMBOL(dispc_mgr_get_sync_lost_irq);

bool dispc_mgr_go_busy(क्रमागत omap_channel channel)
अणु
	वापस mgr_fld_पढ़ो(channel, DISPC_MGR_FLD_GO) == 1;
पूर्ण
EXPORT_SYMBOL(dispc_mgr_go_busy);

व्योम dispc_mgr_go(क्रमागत omap_channel channel)
अणु
	WARN_ON(!dispc_mgr_is_enabled(channel));
	WARN_ON(dispc_mgr_go_busy(channel));

	DSSDBG("GO %s\n", mgr_desc[channel].name);

	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_GO, 1);
पूर्ण
EXPORT_SYMBOL(dispc_mgr_go);

अटल व्योम dispc_ovl_ग_लिखो_firh_reg(क्रमागत omap_plane plane, पूर्णांक reg, u32 value)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_H(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firhv_reg(क्रमागत omap_plane plane, पूर्णांक reg, u32 value)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_HV(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firv_reg(क्रमागत omap_plane plane, पूर्णांक reg, u32 value)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_V(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firh2_reg(क्रमागत omap_plane plane, पूर्णांक reg, u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_H2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firhv2_reg(क्रमागत omap_plane plane, पूर्णांक reg,
		u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_HV2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_ग_लिखो_firv2_reg(क्रमागत omap_plane plane, पूर्णांक reg, u32 value)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ग_लिखो_reg(DISPC_OVL_FIR_COEF_V2(plane, reg), value);
पूर्ण

अटल व्योम dispc_ovl_set_scale_coef(क्रमागत omap_plane plane, पूर्णांक fir_hinc,
				पूर्णांक fir_vinc, पूर्णांक five_taps,
				क्रमागत omap_color_component color_comp)
अणु
	स्थिर काष्ठा dispc_coef *h_coef, *v_coef;
	पूर्णांक i;

	h_coef = dispc_ovl_get_scale_coef(fir_hinc, true);
	v_coef = dispc_ovl_get_scale_coef(fir_vinc, five_taps);

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
			dispc_ovl_ग_लिखो_firh_reg(plane, i, h);
			dispc_ovl_ग_लिखो_firhv_reg(plane, i, hv);
		पूर्ण अन्यथा अणु
			dispc_ovl_ग_लिखो_firh2_reg(plane, i, h);
			dispc_ovl_ग_लिखो_firhv2_reg(plane, i, hv);
		पूर्ण

	पूर्ण

	अगर (five_taps) अणु
		क्रम (i = 0; i < 8; i++) अणु
			u32 v;
			v = FLD_VAL(v_coef[i].hc0_vc00, 7, 0)
				| FLD_VAL(v_coef[i].hc4_vc22, 15, 8);
			अगर (color_comp == DISPC_COLOR_COMPONENT_RGB_Y)
				dispc_ovl_ग_लिखो_firv_reg(plane, i, v);
			अन्यथा
				dispc_ovl_ग_लिखो_firv2_reg(plane, i, v);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम dispc_ovl_ग_लिखो_color_conv_coef(क्रमागत omap_plane plane,
		स्थिर काष्ठा color_conv_coef *ct)
अणु
#घोषणा CVAL(x, y) (FLD_VAL(x, 26, 16) | FLD_VAL(y, 10, 0))

	dispc_ग_लिखो_reg(DISPC_OVL_CONV_COEF(plane, 0), CVAL(ct->rcr, ct->ry));
	dispc_ग_लिखो_reg(DISPC_OVL_CONV_COEF(plane, 1), CVAL(ct->gy,  ct->rcb));
	dispc_ग_लिखो_reg(DISPC_OVL_CONV_COEF(plane, 2), CVAL(ct->gcb, ct->gcr));
	dispc_ग_लिखो_reg(DISPC_OVL_CONV_COEF(plane, 3), CVAL(ct->bcr, ct->by));
	dispc_ग_लिखो_reg(DISPC_OVL_CONV_COEF(plane, 4), CVAL(0, ct->bcb));

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), ct->full_range, 11, 11);

#अघोषित CVAL
पूर्ण

अटल व्योम dispc_setup_color_conv_coef(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक num_ovl = dss_feat_get_num_ovls();
	स्थिर काष्ठा color_conv_coef ctbl_bt601_5_ovl = अणु
		/* YUV -> RGB */
		298, 409, 0, 298, -208, -100, 298, 0, 517, 0,
	पूर्ण;
	स्थिर काष्ठा color_conv_coef ctbl_bt601_5_wb = अणु
		/* RGB -> YUV */
		66, 129, 25, 112, -94, -18, -38, -74, 112, 0,
	पूर्ण;

	क्रम (i = 1; i < num_ovl; i++)
		dispc_ovl_ग_लिखो_color_conv_coef(i, &ctbl_bt601_5_ovl);

	अगर (dispc.feat->has_ग_लिखोback)
		dispc_ovl_ग_लिखो_color_conv_coef(OMAP_DSS_WB, &ctbl_bt601_5_wb);
पूर्ण

अटल व्योम dispc_ovl_set_ba0(क्रमागत omap_plane plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_BA0(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba1(क्रमागत omap_plane plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_BA1(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba0_uv(क्रमागत omap_plane plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_BA0_UV(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_ba1_uv(क्रमागत omap_plane plane, u32 paddr)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_BA1_UV(plane), paddr);
पूर्ण

अटल व्योम dispc_ovl_set_pos(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, पूर्णांक x, पूर्णांक y)
अणु
	u32 val;

	अगर ((caps & OMAP_DSS_OVL_CAP_POS) == 0)
		वापस;

	val = FLD_VAL(y, 26, 16) | FLD_VAL(x, 10, 0);

	dispc_ग_लिखो_reg(DISPC_OVL_POSITION(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_input_size(क्रमागत omap_plane plane, पूर्णांक width,
		पूर्णांक height)
अणु
	u32 val = FLD_VAL(height - 1, 26, 16) | FLD_VAL(width - 1, 10, 0);

	अगर (plane == OMAP_DSS_GFX || plane == OMAP_DSS_WB)
		dispc_ग_लिखो_reg(DISPC_OVL_SIZE(plane), val);
	अन्यथा
		dispc_ग_लिखो_reg(DISPC_OVL_PICTURE_SIZE(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_output_size(क्रमागत omap_plane plane, पूर्णांक width,
		पूर्णांक height)
अणु
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = FLD_VAL(height - 1, 26, 16) | FLD_VAL(width - 1, 10, 0);

	अगर (plane == OMAP_DSS_WB)
		dispc_ग_लिखो_reg(DISPC_OVL_PICTURE_SIZE(plane), val);
	अन्यथा
		dispc_ग_लिखो_reg(DISPC_OVL_SIZE(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_zorder(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, u8 zorder)
अणु
	अगर ((caps & OMAP_DSS_OVL_CAP_ZORDER) == 0)
		वापस;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), zorder, 27, 26);
पूर्ण

अटल व्योम dispc_ovl_enable_zorder_planes(व्योम)
अणु
	पूर्णांक i;

	अगर (!dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		वापस;

	क्रम (i = 0; i < dss_feat_get_num_ovls(); i++)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(i), 1, 25, 25);
पूर्ण

अटल व्योम dispc_ovl_set_pre_mult_alpha(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, bool enable)
अणु
	अगर ((caps & OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA) == 0)
		वापस;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), enable ? 1 : 0, 28, 28);
पूर्ण

अटल व्योम dispc_ovl_setup_global_alpha(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, u8 global_alpha)
अणु
	अटल स्थिर अचिन्हित shअगरts[] = अणु 0, 8, 16, 24, पूर्ण;
	पूर्णांक shअगरt;

	अगर ((caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
		वापस;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(DISPC_GLOBAL_ALPHA, global_alpha, shअगरt + 7, shअगरt);
पूर्ण

अटल व्योम dispc_ovl_set_pix_inc(क्रमागत omap_plane plane, s32 inc)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_PIXEL_INC(plane), inc);
पूर्ण

अटल व्योम dispc_ovl_set_row_inc(क्रमागत omap_plane plane, s32 inc)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_ROW_INC(plane), inc);
पूर्ण

अटल व्योम dispc_ovl_set_color_mode(क्रमागत omap_plane plane,
		क्रमागत omap_color_mode color_mode)
अणु
	u32 m = 0;
	अगर (plane != OMAP_DSS_GFX) अणु
		चयन (color_mode) अणु
		हाल OMAP_DSS_COLOR_NV12:
			m = 0x0; अवरोध;
		हाल OMAP_DSS_COLOR_RGBX16:
			m = 0x1; अवरोध;
		हाल OMAP_DSS_COLOR_RGBA16:
			m = 0x2; अवरोध;
		हाल OMAP_DSS_COLOR_RGB12U:
			m = 0x4; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB16:
			m = 0x5; अवरोध;
		हाल OMAP_DSS_COLOR_RGB16:
			m = 0x6; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB16_1555:
			m = 0x7; अवरोध;
		हाल OMAP_DSS_COLOR_RGB24U:
			m = 0x8; अवरोध;
		हाल OMAP_DSS_COLOR_RGB24P:
			m = 0x9; अवरोध;
		हाल OMAP_DSS_COLOR_YUV2:
			m = 0xa; अवरोध;
		हाल OMAP_DSS_COLOR_UYVY:
			m = 0xb; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB32:
			m = 0xc; अवरोध;
		हाल OMAP_DSS_COLOR_RGBA32:
			m = 0xd; अवरोध;
		हाल OMAP_DSS_COLOR_RGBX32:
			m = 0xe; अवरोध;
		हाल OMAP_DSS_COLOR_XRGB16_1555:
			m = 0xf; अवरोध;
		शेष:
			BUG(); वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (color_mode) अणु
		हाल OMAP_DSS_COLOR_CLUT1:
			m = 0x0; अवरोध;
		हाल OMAP_DSS_COLOR_CLUT2:
			m = 0x1; अवरोध;
		हाल OMAP_DSS_COLOR_CLUT4:
			m = 0x2; अवरोध;
		हाल OMAP_DSS_COLOR_CLUT8:
			m = 0x3; अवरोध;
		हाल OMAP_DSS_COLOR_RGB12U:
			m = 0x4; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB16:
			m = 0x5; अवरोध;
		हाल OMAP_DSS_COLOR_RGB16:
			m = 0x6; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB16_1555:
			m = 0x7; अवरोध;
		हाल OMAP_DSS_COLOR_RGB24U:
			m = 0x8; अवरोध;
		हाल OMAP_DSS_COLOR_RGB24P:
			m = 0x9; अवरोध;
		हाल OMAP_DSS_COLOR_RGBX16:
			m = 0xa; अवरोध;
		हाल OMAP_DSS_COLOR_RGBA16:
			m = 0xb; अवरोध;
		हाल OMAP_DSS_COLOR_ARGB32:
			m = 0xc; अवरोध;
		हाल OMAP_DSS_COLOR_RGBA32:
			m = 0xd; अवरोध;
		हाल OMAP_DSS_COLOR_RGBX32:
			m = 0xe; अवरोध;
		हाल OMAP_DSS_COLOR_XRGB16_1555:
			m = 0xf; अवरोध;
		शेष:
			BUG(); वापस;
		पूर्ण
	पूर्ण

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), m, 4, 1);
पूर्ण

अटल व्योम dispc_ovl_configure_burst_type(क्रमागत omap_plane plane,
		क्रमागत omap_dss_rotation_type rotation_type)
अणु
	अगर (!dss_has_feature(FEAT_BURST_2D))
		वापस;

	अगर (rotation_type == OMAP_DSS_ROT_TILER)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), 1, 29, 29);
	अन्यथा
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), 0, 29, 29);
पूर्ण

व्योम dispc_ovl_set_channel_out(क्रमागत omap_plane plane, क्रमागत omap_channel channel)
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

	val = dispc_पढ़ो_reg(DISPC_OVL_ATTRIBUTES(plane));
	अगर (dss_has_feature(FEAT_MGR_LCD2)) अणु
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
			अगर (dss_has_feature(FEAT_MGR_LCD3)) अणु
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
	dispc_ग_लिखो_reg(DISPC_OVL_ATTRIBUTES(plane), val);
पूर्ण
EXPORT_SYMBOL(dispc_ovl_set_channel_out);

अटल क्रमागत omap_channel dispc_ovl_get_channel_out(क्रमागत omap_plane plane)
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

	val = dispc_पढ़ो_reg(DISPC_OVL_ATTRIBUTES(plane));

	अगर (FLD_GET(val, shअगरt, shअगरt) == 1)
		वापस OMAP_DSS_CHANNEL_DIGIT;

	अगर (!dss_has_feature(FEAT_MGR_LCD2))
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

अटल व्योम dispc_ovl_set_burst_size(क्रमागत omap_plane plane,
		क्रमागत omap_burst_size burst_size)
अणु
	अटल स्थिर अचिन्हित shअगरts[] = अणु 6, 14, 14, 14, 14, पूर्ण;
	पूर्णांक shअगरt;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), burst_size, shअगरt + 1, shअगरt);
पूर्ण

अटल व्योम dispc_configure_burst_sizes(व्योम)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक burst_size = BURST_SIZE_X8;

	/* Configure burst size always to maximum size */
	क्रम (i = 0; i < dss_feat_get_num_ovls(); ++i)
		dispc_ovl_set_burst_size(i, burst_size);
	अगर (dispc.feat->has_ग_लिखोback)
		dispc_ovl_set_burst_size(OMAP_DSS_WB, burst_size);
पूर्ण

अटल u32 dispc_ovl_get_burst_size(क्रमागत omap_plane plane)
अणु
	अचिन्हित unit = dss_feat_get_burst_size_unit();
	/* burst multiplier is always x8 (see dispc_configure_burst_sizes()) */
	वापस unit * 8;
पूर्ण

व्योम dispc_enable_gamma_table(bool enable)
अणु
	/*
	 * This is partially implemented to support only disabling of
	 * the gamma table.
	 */
	अगर (enable) अणु
		DSSWARN("Gamma table enabling for TV not yet supported");
		वापस;
	पूर्ण

	REG_FLD_MOD(DISPC_CONFIG, enable, 9, 9);
पूर्ण

अटल व्योम dispc_mgr_enable_cpr(क्रमागत omap_channel channel, bool enable)
अणु
	अगर (channel == OMAP_DSS_CHANNEL_DIGIT)
		वापस;

	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_CPR, enable);
पूर्ण

अटल व्योम dispc_mgr_set_cpr_coef(क्रमागत omap_channel channel,
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

	dispc_ग_लिखो_reg(DISPC_CPR_COEF_R(channel), coef_r);
	dispc_ग_लिखो_reg(DISPC_CPR_COEF_G(channel), coef_g);
	dispc_ग_लिखो_reg(DISPC_CPR_COEF_B(channel), coef_b);
पूर्ण

अटल व्योम dispc_ovl_set_vid_color_conv(क्रमागत omap_plane plane, bool enable)
अणु
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = dispc_पढ़ो_reg(DISPC_OVL_ATTRIBUTES(plane));
	val = FLD_MOD(val, enable, 9, 9);
	dispc_ग_लिखो_reg(DISPC_OVL_ATTRIBUTES(plane), val);
पूर्ण

अटल व्योम dispc_ovl_enable_replication(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, bool enable)
अणु
	अटल स्थिर अचिन्हित shअगरts[] = अणु 5, 10, 10, 10 पूर्ण;
	पूर्णांक shअगरt;

	अगर ((caps & OMAP_DSS_OVL_CAP_REPLICATION) == 0)
		वापस;

	shअगरt = shअगरts[plane];
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), enable, shअगरt, shअगरt);
पूर्ण

अटल व्योम dispc_mgr_set_size(क्रमागत omap_channel channel, u16 width,
		u16 height)
अणु
	u32 val;

	val = FLD_VAL(height - 1, dispc.feat->mgr_height_start, 16) |
		FLD_VAL(width - 1, dispc.feat->mgr_width_start, 0);

	dispc_ग_लिखो_reg(DISPC_SIZE_MGR(channel), val);
पूर्ण

अटल व्योम dispc_init_fअगरos(व्योम)
अणु
	u32 size;
	पूर्णांक fअगरo;
	u8 start, end;
	u32 unit;
	पूर्णांक i;

	unit = dss_feat_get_buffer_size_unit();

	dss_feat_get_reg_field(FEAT_REG_FIFOSIZE, &start, &end);

	क्रम (fअगरo = 0; fअगरo < dispc.feat->num_fअगरos; ++fअगरo) अणु
		size = REG_GET(DISPC_OVL_FIFO_SIZE_STATUS(fअगरo), start, end);
		size *= unit;
		dispc.fअगरo_size[fअगरo] = size;

		/*
		 * By शेष fअगरos are mapped directly to overlays, fअगरo 0 to
		 * ovl 0, fअगरo 1 to ovl 1, etc.
		 */
		dispc.fअगरo_assignment[fअगरo] = fअगरo;
	पूर्ण

	/*
	 * The GFX fअगरo on OMAP4 is smaller than the other fअगरos. The small fअगरo
	 * causes problems with certain use हालs, like using the tiler in 2D
	 * mode. The below hack swaps the fअगरos of GFX and WB planes, thus
	 * giving GFX plane a larger fअगरo. WB but should work fine with a
	 * smaller fअगरo.
	 */
	अगर (dispc.feat->gfx_fअगरo_workaround) अणु
		u32 v;

		v = dispc_पढ़ो_reg(DISPC_GLOBAL_BUFFER);

		v = FLD_MOD(v, 4, 2, 0); /* GFX BUF top to WB */
		v = FLD_MOD(v, 4, 5, 3); /* GFX BUF bottom to WB */
		v = FLD_MOD(v, 0, 26, 24); /* WB BUF top to GFX */
		v = FLD_MOD(v, 0, 29, 27); /* WB BUF bottom to GFX */

		dispc_ग_लिखो_reg(DISPC_GLOBAL_BUFFER, v);

		dispc.fअगरo_assignment[OMAP_DSS_GFX] = OMAP_DSS_WB;
		dispc.fअगरo_assignment[OMAP_DSS_WB] = OMAP_DSS_GFX;
	पूर्ण

	/*
	 * Setup शेष fअगरo thresholds.
	 */
	क्रम (i = 0; i < dss_feat_get_num_ovls(); ++i) अणु
		u32 low, high;
		स्थिर bool use_fअगरomerge = false;
		स्थिर bool manual_update = false;

		dispc_ovl_compute_fअगरo_thresholds(i, &low, &high,
			use_fअगरomerge, manual_update);

		dispc_ovl_set_fअगरo_threshold(i, low, high);
	पूर्ण

	अगर (dispc.feat->has_ग_लिखोback) अणु
		u32 low, high;
		स्थिर bool use_fअगरomerge = false;
		स्थिर bool manual_update = false;

		dispc_ovl_compute_fअगरo_thresholds(OMAP_DSS_WB, &low, &high,
			use_fअगरomerge, manual_update);

		dispc_ovl_set_fअगरo_threshold(OMAP_DSS_WB, low, high);
	पूर्ण
पूर्ण

अटल u32 dispc_ovl_get_fअगरo_size(क्रमागत omap_plane plane)
अणु
	पूर्णांक fअगरo;
	u32 size = 0;

	क्रम (fअगरo = 0; fअगरo < dispc.feat->num_fअगरos; ++fअगरo) अणु
		अगर (dispc.fअगरo_assignment[fअगरo] == plane)
			size += dispc.fअगरo_size[fअगरo];
	पूर्ण

	वापस size;
पूर्ण

व्योम dispc_ovl_set_fअगरo_threshold(क्रमागत omap_plane plane, u32 low, u32 high)
अणु
	u8 hi_start, hi_end, lo_start, lo_end;
	u32 unit;

	unit = dss_feat_get_buffer_size_unit();

	WARN_ON(low % unit != 0);
	WARN_ON(high % unit != 0);

	low /= unit;
	high /= unit;

	dss_feat_get_reg_field(FEAT_REG_FIFOHIGHTHRESHOLD, &hi_start, &hi_end);
	dss_feat_get_reg_field(FEAT_REG_FIFOLOWTHRESHOLD, &lo_start, &lo_end);

	DSSDBG("fifo(%d) threshold (bytes), old %u/%u, new %u/%u\n",
			plane,
			REG_GET(DISPC_OVL_FIFO_THRESHOLD(plane),
				lo_start, lo_end) * unit,
			REG_GET(DISPC_OVL_FIFO_THRESHOLD(plane),
				hi_start, hi_end) * unit,
			low * unit, high * unit);

	dispc_ग_लिखो_reg(DISPC_OVL_FIFO_THRESHOLD(plane),
			FLD_VAL(high, hi_start, hi_end) |
			FLD_VAL(low, lo_start, lo_end));

	/*
	 * configure the preload to the pipeline's high threhold, if HT it's too
	 * large क्रम the preload field, set the threshold to the maximum value
	 * that can be held by the preload रेजिस्टर
	 */
	अगर (dss_has_feature(FEAT_PRELOAD) && dispc.feat->set_max_preload &&
			plane != OMAP_DSS_WB)
		dispc_ग_लिखो_reg(DISPC_OVL_PRELOAD(plane), min(high, 0xfffu));
पूर्ण

व्योम dispc_enable_fअगरomerge(bool enable)
अणु
	अगर (!dss_has_feature(FEAT_FIFO_MERGE)) अणु
		WARN_ON(enable);
		वापस;
	पूर्ण

	DSSDBG("FIFO merge %s\n", enable ? "enabled" : "disabled");
	REG_FLD_MOD(DISPC_CONFIG, enable ? 1 : 0, 14, 14);
पूर्ण

व्योम dispc_ovl_compute_fअगरo_thresholds(क्रमागत omap_plane plane,
		u32 *fअगरo_low, u32 *fअगरo_high, bool use_fअगरomerge,
		bool manual_update)
अणु
	/*
	 * All sizes are in bytes. Both the buffer and burst are made of
	 * buffer_units, and the fअगरo thresholds must be buffer_unit aligned.
	 */

	अचिन्हित buf_unit = dss_feat_get_buffer_size_unit();
	अचिन्हित ovl_fअगरo_size, total_fअगरo_size, burst_size;
	पूर्णांक i;

	burst_size = dispc_ovl_get_burst_size(plane);
	ovl_fअगरo_size = dispc_ovl_get_fअगरo_size(plane);

	अगर (use_fअगरomerge) अणु
		total_fअगरo_size = 0;
		क्रम (i = 0; i < dss_feat_get_num_ovls(); ++i)
			total_fअगरo_size += dispc_ovl_get_fअगरo_size(i);
	पूर्ण अन्यथा अणु
		total_fअगरo_size = ovl_fअगरo_size;
	पूर्ण

	/*
	 * We use the same low threshold क्रम both fअगरomerge and non-fअगरomerge
	 * हालs, but क्रम fअगरomerge we calculate the high threshold using the
	 * combined fअगरo size
	 */

	अगर (manual_update && dss_has_feature(FEAT_OMAP3_DSI_FIFO_BUG)) अणु
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

अटल व्योम dispc_ovl_set_mflag(क्रमागत omap_plane plane, bool enable)
अणु
	पूर्णांक bit;

	अगर (plane == OMAP_DSS_GFX)
		bit = 14;
	अन्यथा
		bit = 23;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), enable, bit, bit);
पूर्ण

अटल व्योम dispc_ovl_set_mflag_threshold(क्रमागत omap_plane plane,
	पूर्णांक low, पूर्णांक high)
अणु
	dispc_ग_लिखो_reg(DISPC_OVL_MFLAG_THRESHOLD(plane),
		FLD_VAL(high, 31, 16) |	FLD_VAL(low, 15, 0));
पूर्ण

अटल व्योम dispc_init_mflag(व्योम)
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
	dispc_ग_लिखो_reg(DISPC_GLOBAL_MFLAG_ATTRIBUTE,
		(1 << 0) |	/* MFLAG_CTRL = क्रमce always on */
		(0 << 2));	/* MFLAG_START = disable */

	क्रम (i = 0; i < dss_feat_get_num_ovls(); ++i) अणु
		u32 size = dispc_ovl_get_fअगरo_size(i);
		u32 unit = dss_feat_get_buffer_size_unit();
		u32 low, high;

		dispc_ovl_set_mflag(i, true);

		/*
		 * Simulation team suggests below thesholds:
		 * HT = fअगरosize * 5 / 8;
		 * LT = fअगरosize * 4 / 8;
		 */

		low = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovl_set_mflag_threshold(i, low, high);
	पूर्ण

	अगर (dispc.feat->has_ग_लिखोback) अणु
		u32 size = dispc_ovl_get_fअगरo_size(OMAP_DSS_WB);
		u32 unit = dss_feat_get_buffer_size_unit();
		u32 low, high;

		dispc_ovl_set_mflag(OMAP_DSS_WB, true);

		/*
		 * Simulation team suggests below thesholds:
		 * HT = fअगरosize * 5 / 8;
		 * LT = fअगरosize * 4 / 8;
		 */

		low = size * 4 / 8 / unit;
		high = size * 5 / 8 / unit;

		dispc_ovl_set_mflag_threshold(OMAP_DSS_WB, low, high);
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_fir(क्रमागत omap_plane plane,
				पूर्णांक hinc, पूर्णांक vinc,
				क्रमागत omap_color_component color_comp)
अणु
	u32 val;

	अगर (color_comp == DISPC_COLOR_COMPONENT_RGB_Y) अणु
		u8 hinc_start, hinc_end, vinc_start, vinc_end;

		dss_feat_get_reg_field(FEAT_REG_FIRHINC,
					&hinc_start, &hinc_end);
		dss_feat_get_reg_field(FEAT_REG_FIRVINC,
					&vinc_start, &vinc_end);
		val = FLD_VAL(vinc, vinc_start, vinc_end) |
				FLD_VAL(hinc, hinc_start, hinc_end);

		dispc_ग_लिखो_reg(DISPC_OVL_FIR(plane), val);
	पूर्ण अन्यथा अणु
		val = FLD_VAL(vinc, 28, 16) | FLD_VAL(hinc, 12, 0);
		dispc_ग_लिखो_reg(DISPC_OVL_FIR2(plane), val);
	पूर्ण
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu0(क्रमागत omap_plane plane, पूर्णांक haccu, पूर्णांक vaccu)
अणु
	u32 val;
	u8 hor_start, hor_end, vert_start, vert_end;

	dss_feat_get_reg_field(FEAT_REG_HORIZONTALACCU, &hor_start, &hor_end);
	dss_feat_get_reg_field(FEAT_REG_VERTICALACCU, &vert_start, &vert_end);

	val = FLD_VAL(vaccu, vert_start, vert_end) |
			FLD_VAL(haccu, hor_start, hor_end);

	dispc_ग_लिखो_reg(DISPC_OVL_ACCU0(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu1(क्रमागत omap_plane plane, पूर्णांक haccu, पूर्णांक vaccu)
अणु
	u32 val;
	u8 hor_start, hor_end, vert_start, vert_end;

	dss_feat_get_reg_field(FEAT_REG_HORIZONTALACCU, &hor_start, &hor_end);
	dss_feat_get_reg_field(FEAT_REG_VERTICALACCU, &vert_start, &vert_end);

	val = FLD_VAL(vaccu, vert_start, vert_end) |
			FLD_VAL(haccu, hor_start, hor_end);

	dispc_ग_लिखो_reg(DISPC_OVL_ACCU1(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu2_0(क्रमागत omap_plane plane, पूर्णांक haccu,
		पूर्णांक vaccu)
अणु
	u32 val;

	val = FLD_VAL(vaccu, 26, 16) | FLD_VAL(haccu, 10, 0);
	dispc_ग_लिखो_reg(DISPC_OVL_ACCU2_0(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_vid_accu2_1(क्रमागत omap_plane plane, पूर्णांक haccu,
		पूर्णांक vaccu)
अणु
	u32 val;

	val = FLD_VAL(vaccu, 26, 16) | FLD_VAL(haccu, 10, 0);
	dispc_ग_लिखो_reg(DISPC_OVL_ACCU2_1(plane), val);
पूर्ण

अटल व्योम dispc_ovl_set_scale_param(क्रमागत omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool five_taps, u8 rotation,
		क्रमागत omap_color_component color_comp)
अणु
	पूर्णांक fir_hinc, fir_vinc;

	fir_hinc = 1024 * orig_width / out_width;
	fir_vinc = 1024 * orig_height / out_height;

	dispc_ovl_set_scale_coef(plane, fir_hinc, fir_vinc, five_taps,
				color_comp);
	dispc_ovl_set_fir(plane, fir_hinc, fir_vinc, color_comp);
पूर्ण

अटल व्योम dispc_ovl_set_accu_uv(क्रमागत omap_plane plane,
		u16 orig_width,	u16 orig_height, u16 out_width, u16 out_height,
		bool ilace, क्रमागत omap_color_mode color_mode, u8 rotation)
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

	चयन (rotation) अणु
	हाल OMAP_DSS_ROT_0:
		idx = 0;
		अवरोध;
	हाल OMAP_DSS_ROT_90:
		idx = 1;
		अवरोध;
	हाल OMAP_DSS_ROT_180:
		idx = 2;
		अवरोध;
	हाल OMAP_DSS_ROT_270:
		idx = 3;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_NV12:
		अगर (ilace)
			accu_table = accu_nv12_ilace;
		अन्यथा
			accu_table = accu_nv12;
		अवरोध;
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
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

	dispc_ovl_set_vid_accu2_0(plane, h_accu2_0, v_accu2_0);
	dispc_ovl_set_vid_accu2_1(plane, h_accu2_1, v_accu2_1);
पूर्ण

अटल व्योम dispc_ovl_set_scaling_common(क्रमागत omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool ilace, bool five_taps,
		bool fieldmode, क्रमागत omap_color_mode color_mode,
		u8 rotation)
अणु
	पूर्णांक accu0 = 0;
	पूर्णांक accu1 = 0;
	u32 l;

	dispc_ovl_set_scale_param(plane, orig_width, orig_height,
				out_width, out_height, five_taps,
				rotation, DISPC_COLOR_COMPONENT_RGB_Y);
	l = dispc_पढ़ो_reg(DISPC_OVL_ATTRIBUTES(plane));

	/* RESIZEENABLE and VERTICALTAPS */
	l &= ~((0x3 << 5) | (0x1 << 21));
	l |= (orig_width != out_width) ? (1 << 5) : 0;
	l |= (orig_height != out_height) ? (1 << 6) : 0;
	l |= five_taps ? (1 << 21) : 0;

	/* VRESIZECONF and HRESIZECONF */
	अगर (dss_has_feature(FEAT_RESIZECONF)) अणु
		l &= ~(0x3 << 7);
		l |= (orig_width <= out_width) ? 0 : (1 << 7);
		l |= (orig_height <= out_height) ? 0 : (1 << 8);
	पूर्ण

	/* LINEBUFFERSPLIT */
	अगर (dss_has_feature(FEAT_LINEBUFFERSPLIT)) अणु
		l &= ~(0x1 << 22);
		l |= five_taps ? (1 << 22) : 0;
	पूर्ण

	dispc_ग_लिखो_reg(DISPC_OVL_ATTRIBUTES(plane), l);

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

	dispc_ovl_set_vid_accu0(plane, 0, accu0);
	dispc_ovl_set_vid_accu1(plane, 0, accu1);
पूर्ण

अटल व्योम dispc_ovl_set_scaling_uv(क्रमागत omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool ilace, bool five_taps,
		bool fieldmode, क्रमागत omap_color_mode color_mode,
		u8 rotation)
अणु
	पूर्णांक scale_x = out_width != orig_width;
	पूर्णांक scale_y = out_height != orig_height;
	bool chroma_upscale = plane != OMAP_DSS_WB;

	अगर (!dss_has_feature(FEAT_HANDLE_UV_SEPARATE))
		वापस;
	अगर ((color_mode != OMAP_DSS_COLOR_YUV2 &&
			color_mode != OMAP_DSS_COLOR_UYVY &&
			color_mode != OMAP_DSS_COLOR_NV12)) अणु
		/* reset chroma resampling क्रम RGB क्रमmats  */
		अगर (plane != OMAP_DSS_WB)
			REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane), 0, 8, 8);
		वापस;
	पूर्ण

	dispc_ovl_set_accu_uv(plane, orig_width, orig_height, out_width,
			out_height, ilace, color_mode, rotation);

	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_NV12:
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
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
		/* For YUV422 with 90/270 rotation, we करोn't upsample chroma */
		अगर (rotation == OMAP_DSS_ROT_0 ||
				rotation == OMAP_DSS_ROT_180) अणु
			अगर (chroma_upscale)
				/* UV is subsampled by 2 horizontally */
				orig_width >>= 1;
			अन्यथा
				/* UV is करोwnsampled by 2 horizontally */
				orig_width <<= 1;
		पूर्ण

		/* must use FIR क्रम YUV422 अगर rotated */
		अगर (rotation != OMAP_DSS_ROT_0)
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

	dispc_ovl_set_scale_param(plane, orig_width, orig_height,
			out_width, out_height, five_taps,
				rotation, DISPC_COLOR_COMPONENT_UV);

	अगर (plane != OMAP_DSS_WB)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane),
			(scale_x || scale_y) ? 1 : 0, 8, 8);

	/* set H scaling */
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), scale_x ? 1 : 0, 5, 5);
	/* set V scaling */
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), scale_y ? 1 : 0, 6, 6);
पूर्ण

अटल व्योम dispc_ovl_set_scaling(क्रमागत omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool ilace, bool five_taps,
		bool fieldmode, क्रमागत omap_color_mode color_mode,
		u8 rotation)
अणु
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ovl_set_scaling_common(plane,
			orig_width, orig_height,
			out_width, out_height,
			ilace, five_taps,
			fieldmode, color_mode,
			rotation);

	dispc_ovl_set_scaling_uv(plane,
		orig_width, orig_height,
		out_width, out_height,
		ilace, five_taps,
		fieldmode, color_mode,
		rotation);
पूर्ण

अटल व्योम dispc_ovl_set_rotation_attrs(क्रमागत omap_plane plane, u8 rotation,
		क्रमागत omap_dss_rotation_type rotation_type,
		bool mirroring, क्रमागत omap_color_mode color_mode)
अणु
	bool row_repeat = false;
	पूर्णांक vidrot = 0;

	अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY) अणु

		अगर (mirroring) अणु
			चयन (rotation) अणु
			हाल OMAP_DSS_ROT_0:
				vidrot = 2;
				अवरोध;
			हाल OMAP_DSS_ROT_90:
				vidrot = 1;
				अवरोध;
			हाल OMAP_DSS_ROT_180:
				vidrot = 0;
				अवरोध;
			हाल OMAP_DSS_ROT_270:
				vidrot = 3;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (rotation) अणु
			हाल OMAP_DSS_ROT_0:
				vidrot = 0;
				अवरोध;
			हाल OMAP_DSS_ROT_90:
				vidrot = 1;
				अवरोध;
			हाल OMAP_DSS_ROT_180:
				vidrot = 2;
				अवरोध;
			हाल OMAP_DSS_ROT_270:
				vidrot = 3;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (rotation == OMAP_DSS_ROT_90 || rotation == OMAP_DSS_ROT_270)
			row_repeat = true;
		अन्यथा
			row_repeat = false;
	पूर्ण

	/*
	 * OMAP4/5 Errata i631:
	 * NV12 in 1D mode must use ROTATION=1. Otherwise DSS will fetch extra
	 * rows beyond the framebuffer, which may cause OCP error.
	 */
	अगर (color_mode == OMAP_DSS_COLOR_NV12 &&
			rotation_type != OMAP_DSS_ROT_TILER)
		vidrot = 1;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), vidrot, 13, 12);
	अगर (dss_has_feature(FEAT_ROWREPEATENABLE))
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane),
			row_repeat ? 1 : 0, 18, 18);

	अगर (color_mode == OMAP_DSS_COLOR_NV12) अणु
		bool द्विगुनstride = (rotation_type == OMAP_DSS_ROT_TILER) &&
					(rotation == OMAP_DSS_ROT_0 ||
					rotation == OMAP_DSS_ROT_180);
		/* DOUBLESTRIDE */
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), द्विगुनstride, 22, 22);
	पूर्ण

पूर्ण

अटल पूर्णांक color_mode_to_bpp(क्रमागत omap_color_mode color_mode)
अणु
	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_CLUT1:
		वापस 1;
	हाल OMAP_DSS_COLOR_CLUT2:
		वापस 2;
	हाल OMAP_DSS_COLOR_CLUT4:
		वापस 4;
	हाल OMAP_DSS_COLOR_CLUT8:
	हाल OMAP_DSS_COLOR_NV12:
		वापस 8;
	हाल OMAP_DSS_COLOR_RGB12U:
	हाल OMAP_DSS_COLOR_RGB16:
	हाल OMAP_DSS_COLOR_ARGB16:
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
	हाल OMAP_DSS_COLOR_RGBA16:
	हाल OMAP_DSS_COLOR_RGBX16:
	हाल OMAP_DSS_COLOR_ARGB16_1555:
	हाल OMAP_DSS_COLOR_XRGB16_1555:
		वापस 16;
	हाल OMAP_DSS_COLOR_RGB24P:
		वापस 24;
	हाल OMAP_DSS_COLOR_RGB24U:
	हाल OMAP_DSS_COLOR_ARGB32:
	हाल OMAP_DSS_COLOR_RGBA32:
	हाल OMAP_DSS_COLOR_RGBX32:
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
	अन्यथा
		BUG();
	वापस 0;
पूर्ण

अटल व्योम calc_vrfb_rotation_offset(u8 rotation, bool mirror,
		u16 screen_width,
		u16 width, u16 height,
		क्रमागत omap_color_mode color_mode, bool fieldmode,
		अचिन्हित पूर्णांक field_offset,
		अचिन्हित *offset0, अचिन्हित *offset1,
		s32 *row_inc, s32 *pix_inc, पूर्णांक x_predecim, पूर्णांक y_predecim)
अणु
	u8 ps;

	/* FIXME CLUT क्रमmats */
	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_CLUT1:
	हाल OMAP_DSS_COLOR_CLUT2:
	हाल OMAP_DSS_COLOR_CLUT4:
	हाल OMAP_DSS_COLOR_CLUT8:
		BUG();
		वापस;
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
		ps = 4;
		अवरोध;
	शेष:
		ps = color_mode_to_bpp(color_mode) / 8;
		अवरोध;
	पूर्ण

	DSSDBG("calc_rot(%d): scrw %d, %dx%d\n", rotation, screen_width,
			width, height);

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	चयन (rotation + mirror * 4) अणु
	हाल OMAP_DSS_ROT_0:
	हाल OMAP_DSS_ROT_180:
		/*
		 * If the pixel क्रमmat is YUV or UYVY भागide the width
		 * of the image by 2 क्रम 0 and 180 degree rotation.
		 */
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			width = width >> 1;
		fallthrough;
	हाल OMAP_DSS_ROT_90:
	हाल OMAP_DSS_ROT_270:
		*offset1 = 0;
		अगर (field_offset)
			*offset0 = field_offset * screen_width * ps;
		अन्यथा
			*offset0 = 0;

		*row_inc = pixinc(1 +
			(y_predecim * screen_width - x_predecim * width) +
			(fieldmode ? screen_width : 0), ps);
		*pix_inc = pixinc(x_predecim, ps);
		अवरोध;

	हाल OMAP_DSS_ROT_0 + 4:
	हाल OMAP_DSS_ROT_180 + 4:
		/* If the pixel क्रमmat is YUV or UYVY भागide the width
		 * of the image by 2  क्रम 0 degree and 180 degree
		 */
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			width = width >> 1;
		fallthrough;
	हाल OMAP_DSS_ROT_90 + 4:
	हाल OMAP_DSS_ROT_270 + 4:
		*offset1 = 0;
		अगर (field_offset)
			*offset0 = field_offset * screen_width * ps;
		अन्यथा
			*offset0 = 0;
		*row_inc = pixinc(1 -
			(y_predecim * screen_width + x_predecim * width) -
			(fieldmode ? screen_width : 0), ps);
		*pix_inc = pixinc(x_predecim, ps);
		अवरोध;

	शेष:
		BUG();
		वापस;
	पूर्ण
पूर्ण

अटल व्योम calc_dma_rotation_offset(u8 rotation, bool mirror,
		u16 screen_width,
		u16 width, u16 height,
		क्रमागत omap_color_mode color_mode, bool fieldmode,
		अचिन्हित पूर्णांक field_offset,
		अचिन्हित *offset0, अचिन्हित *offset1,
		s32 *row_inc, s32 *pix_inc, पूर्णांक x_predecim, पूर्णांक y_predecim)
अणु
	u8 ps;
	u16 fbw, fbh;

	/* FIXME CLUT क्रमmats */
	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_CLUT1:
	हाल OMAP_DSS_COLOR_CLUT2:
	हाल OMAP_DSS_COLOR_CLUT4:
	हाल OMAP_DSS_COLOR_CLUT8:
		BUG();
		वापस;
	शेष:
		ps = color_mode_to_bpp(color_mode) / 8;
		अवरोध;
	पूर्ण

	DSSDBG("calc_rot(%d): scrw %d, %dx%d\n", rotation, screen_width,
			width, height);

	/* width & height are overlay sizes, convert to fb sizes */

	अगर (rotation == OMAP_DSS_ROT_0 || rotation == OMAP_DSS_ROT_180) अणु
		fbw = width;
		fbh = height;
	पूर्ण अन्यथा अणु
		fbw = height;
		fbh = width;
	पूर्ण

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	चयन (rotation + mirror * 4) अणु
	हाल OMAP_DSS_ROT_0:
		*offset1 = 0;
		अगर (field_offset)
			*offset0 = *offset1 + field_offset * screen_width * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(1 +
			(y_predecim * screen_width - fbw * x_predecim) +
			(fieldmode ? screen_width : 0),	ps);
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(x_predecim, 2 * ps);
		अन्यथा
			*pix_inc = pixinc(x_predecim, ps);
		अवरोध;
	हाल OMAP_DSS_ROT_90:
		*offset1 = screen_width * (fbh - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 + field_offset * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(screen_width * (fbh * x_predecim - 1) +
				y_predecim + (fieldmode ? 1 : 0), ps);
		*pix_inc = pixinc(-x_predecim * screen_width, ps);
		अवरोध;
	हाल OMAP_DSS_ROT_180:
		*offset1 = (screen_width * (fbh - 1) + fbw - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 - field_offset * screen_width * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(-1 -
			(y_predecim * screen_width - fbw * x_predecim) -
			(fieldmode ? screen_width : 0),	ps);
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(-x_predecim, 2 * ps);
		अन्यथा
			*pix_inc = pixinc(-x_predecim, ps);
		अवरोध;
	हाल OMAP_DSS_ROT_270:
		*offset1 = (fbw - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 - field_offset * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(-screen_width * (fbh * x_predecim - 1) -
				y_predecim - (fieldmode ? 1 : 0), ps);
		*pix_inc = pixinc(x_predecim * screen_width, ps);
		अवरोध;

	/* mirroring */
	हाल OMAP_DSS_ROT_0 + 4:
		*offset1 = (fbw - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 + field_offset * screen_width * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(y_predecim * screen_width * 2 - 1 +
				(fieldmode ? screen_width : 0),
				ps);
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(-x_predecim, 2 * ps);
		अन्यथा
			*pix_inc = pixinc(-x_predecim, ps);
		अवरोध;

	हाल OMAP_DSS_ROT_90 + 4:
		*offset1 = 0;
		अगर (field_offset)
			*offset0 = *offset1 + field_offset * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(-screen_width * (fbh * x_predecim - 1) +
				y_predecim + (fieldmode ? 1 : 0),
				ps);
		*pix_inc = pixinc(x_predecim * screen_width, ps);
		अवरोध;

	हाल OMAP_DSS_ROT_180 + 4:
		*offset1 = screen_width * (fbh - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 - field_offset * screen_width * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(1 - y_predecim * screen_width * 2 -
				(fieldmode ? screen_width : 0),
				ps);
		अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(x_predecim, 2 * ps);
		अन्यथा
			*pix_inc = pixinc(x_predecim, ps);
		अवरोध;

	हाल OMAP_DSS_ROT_270 + 4:
		*offset1 = (screen_width * (fbh - 1) + fbw - 1) * ps;
		अगर (field_offset)
			*offset0 = *offset1 - field_offset * ps;
		अन्यथा
			*offset0 = *offset1;
		*row_inc = pixinc(screen_width * (fbh * x_predecim - 1) -
				y_predecim - (fieldmode ? 1 : 0),
				ps);
		*pix_inc = pixinc(-x_predecim * screen_width, ps);
		अवरोध;

	शेष:
		BUG();
		वापस;
	पूर्ण
पूर्ण

अटल व्योम calc_tiler_rotation_offset(u16 screen_width, u16 width,
		क्रमागत omap_color_mode color_mode, bool fieldmode,
		अचिन्हित पूर्णांक field_offset, अचिन्हित *offset0, अचिन्हित *offset1,
		s32 *row_inc, s32 *pix_inc, पूर्णांक x_predecim, पूर्णांक y_predecim)
अणु
	u8 ps;

	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_CLUT1:
	हाल OMAP_DSS_COLOR_CLUT2:
	हाल OMAP_DSS_COLOR_CLUT4:
	हाल OMAP_DSS_COLOR_CLUT8:
		BUG();
		वापस;
	शेष:
		ps = color_mode_to_bpp(color_mode) / 8;
		अवरोध;
	पूर्ण

	DSSDBG("scrw %d, width %d\n", screen_width, width);

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	*offset1 = 0;
	अगर (field_offset)
		*offset0 = *offset1 + field_offset * screen_width * ps;
	अन्यथा
		*offset0 = *offset1;
	*row_inc = pixinc(1 + (y_predecim * screen_width - width * x_predecim) +
			(fieldmode ? screen_width : 0), ps);
	अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
		color_mode == OMAP_DSS_COLOR_UYVY)
		*pix_inc = pixinc(x_predecim, 2 * ps);
	अन्यथा
		*pix_inc = pixinc(x_predecim, ps);
पूर्ण

/*
 * This function is used to aव्योम synclosts in OMAP3, because of some
 * unकरोcumented horizontal position and timing related limitations.
 */
अटल पूर्णांक check_horiz_timing_omap3(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा omap_video_timings *t, u16 pos_x,
		u16 width, u16 height, u16 out_width, u16 out_height,
		bool five_taps)
अणु
	स्थिर पूर्णांक ds = DIV_ROUND_UP(height, out_height);
	अचिन्हित दीर्घ nonactive;
	अटल स्थिर u8 limits[3] = अणु 8, 10, 20 पूर्ण;
	u64 val, blank;
	पूर्णांक i;

	nonactive = t->x_res + t->hfp + t->hsw + t->hbp - out_width;

	i = 0;
	अगर (out_height < height)
		i++;
	अगर (out_width < width)
		i++;
	blank = भाग_u64((u64)(t->hbp + t->hsw + t->hfp) * lclk, pclk);
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
		स्थिर काष्ठा omap_video_timings *mgr_timings, u16 width,
		u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode)
अणु
	u32 core_clk = 0;
	u64 पंचांगp;

	अगर (height <= out_height && width <= out_width)
		वापस (अचिन्हित दीर्घ) pclk;

	अगर (height > out_height) अणु
		अचिन्हित पूर्णांक ppl = mgr_timings->x_res;

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

		अगर (color_mode == OMAP_DSS_COLOR_RGB24U)
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

अटल पूर्णांक dispc_ovl_calc_scaling_24xx(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, पूर्णांक *decim_x, पूर्णांक *decim_y,
		u16 pos_x, अचिन्हित दीर्घ *core_clk, bool mem_to_mem)
अणु
	पूर्णांक error;
	u16 in_width, in_height;
	पूर्णांक min_factor = min(*decim_x, *decim_y);
	स्थिर पूर्णांक maxsinglelinewidth =
			dss_feat_get_param_max(FEAT_PARAM_LINEWIDTH);

	*five_taps = false;

	करो अणु
		in_height = height / *decim_y;
		in_width = width / *decim_x;
		*core_clk = dispc.feat->calc_core_clk(pclk, in_width,
				in_height, out_width, out_height, mem_to_mem);
		error = (in_width > maxsinglelinewidth || !*core_clk ||
			*core_clk > dispc_core_clk_rate());
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
		DSSERR("Cannot scale max input width exceeded");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_ovl_calc_scaling_34xx(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, पूर्णांक *decim_x, पूर्णांक *decim_y,
		u16 pos_x, अचिन्हित दीर्घ *core_clk, bool mem_to_mem)
अणु
	पूर्णांक error;
	u16 in_width, in_height;
	स्थिर पूर्णांक maxsinglelinewidth =
			dss_feat_get_param_max(FEAT_PARAM_LINEWIDTH);

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
			*core_clk = calc_core_clk_five_taps(pclk, mgr_timings,
						in_width, in_height, out_width,
						out_height, color_mode);
		अन्यथा
			*core_clk = dispc.feat->calc_core_clk(pclk, in_width,
					in_height, out_width, out_height,
					mem_to_mem);

		error = check_horiz_timing_omap3(pclk, lclk, mgr_timings,
				pos_x, in_width, in_height, out_width,
				out_height, *five_taps);
		अगर (error && *five_taps) अणु
			*five_taps = false;
			जाओ again;
		पूर्ण

		error = (error || in_width > maxsinglelinewidth * 2 ||
			(in_width > maxsinglelinewidth && *five_taps) ||
			!*core_clk || *core_clk > dispc_core_clk_rate());

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

	अगर (check_horiz_timing_omap3(pclk, lclk, mgr_timings, pos_x, in_width,
				in_height, out_width, out_height, *five_taps)) अणु
			DSSERR("horizontal timing too tight\n");
			वापस -EINVAL;
	पूर्ण

	अगर (in_width > (maxsinglelinewidth * 2)) अणु
		DSSERR("Cannot setup scaling");
		DSSERR("width exceeds maximum width possible");
		वापस -EINVAL;
	पूर्ण

	अगर (in_width > maxsinglelinewidth && *five_taps) अणु
		DSSERR("cannot setup scaling with five taps");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dispc_ovl_calc_scaling_44xx(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, पूर्णांक *decim_x, पूर्णांक *decim_y,
		u16 pos_x, अचिन्हित दीर्घ *core_clk, bool mem_to_mem)
अणु
	u16 in_width, in_width_max;
	पूर्णांक decim_x_min = *decim_x;
	u16 in_height = height / *decim_y;
	स्थिर पूर्णांक maxsinglelinewidth =
				dss_feat_get_param_max(FEAT_PARAM_LINEWIDTH);
	स्थिर पूर्णांक maxकरोwnscale = dss_feat_get_param_max(FEAT_PARAM_DOWNSCALE);

	अगर (mem_to_mem) अणु
		in_width_max = out_width * maxकरोwnscale;
	पूर्ण अन्यथा अणु
		in_width_max = dispc_core_clk_rate() /
					DIV_ROUND_UP(pclk, out_width);
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
		DSSERR("Cannot scale width exceeds max line width");
		वापस -EINVAL;
	पूर्ण

	*core_clk = dispc.feat->calc_core_clk(pclk, in_width, in_height,
				out_width, out_height, mem_to_mem);
	वापस 0;
पूर्ण

#घोषणा DIV_FRAC(भागidend, भागisor) \
	((भागidend) * 100 / (भागisor) - ((भागidend) / (भागisor) * 100))

अटल पूर्णांक dispc_ovl_calc_scaling(अचिन्हित दीर्घ pclk, अचिन्हित दीर्घ lclk,
		क्रमागत omap_overlay_caps caps,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		u16 width, u16 height, u16 out_width, u16 out_height,
		क्रमागत omap_color_mode color_mode, bool *five_taps,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim, u16 pos_x,
		क्रमागत omap_dss_rotation_type rotation_type, bool mem_to_mem)
अणु
	स्थिर पूर्णांक maxकरोwnscale = dss_feat_get_param_max(FEAT_PARAM_DOWNSCALE);
	स्थिर पूर्णांक max_decim_limit = 16;
	अचिन्हित दीर्घ core_clk = 0;
	पूर्णांक decim_x, decim_y, ret;

	अगर (width == out_width && height == out_height)
		वापस 0;

	अगर (!mem_to_mem && (pclk == 0 || mgr_timings->pixelघड़ी == 0)) अणु
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
				dss_has_feature(FEAT_BURST_2D)) ?
				2 : max_decim_limit;
	पूर्ण

	अगर (color_mode == OMAP_DSS_COLOR_CLUT1 ||
	    color_mode == OMAP_DSS_COLOR_CLUT2 ||
	    color_mode == OMAP_DSS_COLOR_CLUT4 ||
	    color_mode == OMAP_DSS_COLOR_CLUT8) अणु
		*x_predecim = 1;
		*y_predecim = 1;
		*five_taps = false;
		वापस 0;
	पूर्ण

	decim_x = DIV_ROUND_UP(DIV_ROUND_UP(width, out_width), maxकरोwnscale);
	decim_y = DIV_ROUND_UP(DIV_ROUND_UP(height, out_height), maxकरोwnscale);

	अगर (decim_x > *x_predecim || out_width > width * 8)
		वापस -EINVAL;

	अगर (decim_y > *y_predecim || out_height > height * 8)
		वापस -EINVAL;

	ret = dispc.feat->calc_scaling(pclk, lclk, mgr_timings, width, height,
		out_width, out_height, color_mode, five_taps,
		x_predecim, y_predecim, &decim_x, &decim_y, pos_x, &core_clk,
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
		core_clk, dispc_core_clk_rate());

	अगर (!core_clk || core_clk > dispc_core_clk_rate()) अणु
		DSSERR("failed to set up scaling, "
			"required core clk rate = %lu Hz, "
			"current core clk rate = %lu Hz\n",
			core_clk, dispc_core_clk_rate());
		वापस -EINVAL;
	पूर्ण

	*x_predecim = decim_x;
	*y_predecim = decim_y;
	वापस 0;
पूर्ण

पूर्णांक dispc_ovl_check(क्रमागत omap_plane plane, क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_overlay_info *oi,
		स्थिर काष्ठा omap_video_timings *timings,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim)
अणु
	क्रमागत omap_overlay_caps caps = dss_feat_get_overlay_caps(plane);
	bool five_taps = true;
	bool fieldmode = false;
	u16 in_height = oi->height;
	u16 in_width = oi->width;
	bool ilace = timings->पूर्णांकerlace;
	u16 out_width, out_height;
	पूर्णांक pos_x = oi->pos_x;
	अचिन्हित दीर्घ pclk = dispc_mgr_pclk_rate(channel);
	अचिन्हित दीर्घ lclk = dispc_mgr_lclk_rate(channel);

	out_width = oi->out_width == 0 ? oi->width : oi->out_width;
	out_height = oi->out_height == 0 ? oi->height : oi->out_height;

	अगर (ilace && oi->height == out_height)
		fieldmode = true;

	अगर (ilace) अणु
		अगर (fieldmode)
			in_height /= 2;
		out_height /= 2;

		DSSDBG("adjusting for ilace: height %d, out_height %d\n",
				in_height, out_height);
	पूर्ण

	अगर (!dss_feat_color_mode_supported(plane, oi->color_mode))
		वापस -EINVAL;

	वापस dispc_ovl_calc_scaling(pclk, lclk, caps, timings, in_width,
			in_height, out_width, out_height, oi->color_mode,
			&five_taps, x_predecim, y_predecim, pos_x,
			oi->rotation_type, false);
पूर्ण
EXPORT_SYMBOL(dispc_ovl_check);

अटल पूर्णांक dispc_ovl_setup_common(क्रमागत omap_plane plane,
		क्रमागत omap_overlay_caps caps, u32 paddr, u32 p_uv_addr,
		u16 screen_width, पूर्णांक pos_x, पूर्णांक pos_y, u16 width, u16 height,
		u16 out_width, u16 out_height, क्रमागत omap_color_mode color_mode,
		u8 rotation, bool mirror, u8 zorder, u8 pre_mult_alpha,
		u8 global_alpha, क्रमागत omap_dss_rotation_type rotation_type,
		bool replication, स्थिर काष्ठा omap_video_timings *mgr_timings,
		bool mem_to_mem)
अणु
	bool five_taps = true;
	bool fieldmode = false;
	पूर्णांक r, cconv = 0;
	अचिन्हित offset0, offset1;
	s32 row_inc;
	s32 pix_inc;
	u16 frame_width, frame_height;
	अचिन्हित पूर्णांक field_offset = 0;
	u16 in_height = height;
	u16 in_width = width;
	पूर्णांक x_predecim = 1, y_predecim = 1;
	bool ilace = mgr_timings->पूर्णांकerlace;
	अचिन्हित दीर्घ pclk = dispc_plane_pclk_rate(plane);
	अचिन्हित दीर्घ lclk = dispc_plane_lclk_rate(plane);

	अगर (paddr == 0 && rotation_type != OMAP_DSS_ROT_TILER)
		वापस -EINVAL;

	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
	हाल OMAP_DSS_COLOR_NV12:
		अगर (in_width & 1) अणु
			DSSERR("input width %d is not even for YUV format\n",
				in_width);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	out_width = out_width == 0 ? width : out_width;
	out_height = out_height == 0 ? height : out_height;

	अगर (ilace && height == out_height)
		fieldmode = true;

	अगर (ilace) अणु
		अगर (fieldmode)
			in_height /= 2;
		pos_y /= 2;
		out_height /= 2;

		DSSDBG("adjusting for ilace: height %d, pos_y %d, "
			"out_height %d\n", in_height, pos_y,
			out_height);
	पूर्ण

	अगर (!dss_feat_color_mode_supported(plane, color_mode))
		वापस -EINVAL;

	r = dispc_ovl_calc_scaling(pclk, lclk, caps, mgr_timings, in_width,
			in_height, out_width, out_height, color_mode,
			&five_taps, &x_predecim, &y_predecim, pos_x,
			rotation_type, mem_to_mem);
	अगर (r)
		वापस r;

	in_width = in_width / x_predecim;
	in_height = in_height / y_predecim;

	अगर (x_predecim > 1 || y_predecim > 1)
		DSSDBG("predecimation %d x %x, new input size %d x %d\n",
			x_predecim, y_predecim, in_width, in_height);

	चयन (color_mode) अणु
	हाल OMAP_DSS_COLOR_YUV2:
	हाल OMAP_DSS_COLOR_UYVY:
	हाल OMAP_DSS_COLOR_NV12:
		अगर (in_width & 1) अणु
			DSSDBG("predecimated input width is not even for YUV format\n");
			DSSDBG("adjusting input width %d -> %d\n",
				in_width, in_width & ~1);

			in_width &= ~1;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY ||
			color_mode == OMAP_DSS_COLOR_NV12)
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

	अगर (plane == OMAP_DSS_WB) अणु
		frame_width = out_width;
		frame_height = out_height;
	पूर्ण अन्यथा अणु
		frame_width = in_width;
		frame_height = height;
	पूर्ण

	अगर (rotation_type == OMAP_DSS_ROT_TILER)
		calc_tiler_rotation_offset(screen_width, frame_width,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);
	अन्यथा अगर (rotation_type == OMAP_DSS_ROT_DMA)
		calc_dma_rotation_offset(rotation, mirror, screen_width,
				frame_width, frame_height,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);
	अन्यथा
		calc_vrfb_rotation_offset(rotation, mirror,
				screen_width, frame_width, frame_height,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);

	DSSDBG("offset0 %u, offset1 %u, row_inc %d, pix_inc %d\n",
			offset0, offset1, row_inc, pix_inc);

	dispc_ovl_set_color_mode(plane, color_mode);

	dispc_ovl_configure_burst_type(plane, rotation_type);

	dispc_ovl_set_ba0(plane, paddr + offset0);
	dispc_ovl_set_ba1(plane, paddr + offset1);

	अगर (OMAP_DSS_COLOR_NV12 == color_mode) अणु
		dispc_ovl_set_ba0_uv(plane, p_uv_addr + offset0);
		dispc_ovl_set_ba1_uv(plane, p_uv_addr + offset1);
	पूर्ण

	अगर (dispc.feat->last_pixel_inc_missing)
		row_inc += pix_inc - 1;

	dispc_ovl_set_row_inc(plane, row_inc);
	dispc_ovl_set_pix_inc(plane, pix_inc);

	DSSDBG("%d,%d %dx%d -> %dx%d\n", pos_x, pos_y, in_width,
			in_height, out_width, out_height);

	dispc_ovl_set_pos(plane, caps, pos_x, pos_y);

	dispc_ovl_set_input_size(plane, in_width, in_height);

	अगर (caps & OMAP_DSS_OVL_CAP_SCALE) अणु
		dispc_ovl_set_scaling(plane, in_width, in_height, out_width,
				   out_height, ilace, five_taps, fieldmode,
				   color_mode, rotation);
		dispc_ovl_set_output_size(plane, out_width, out_height);
		dispc_ovl_set_vid_color_conv(plane, cconv);
	पूर्ण

	dispc_ovl_set_rotation_attrs(plane, rotation, rotation_type, mirror,
			color_mode);

	dispc_ovl_set_zorder(plane, caps, zorder);
	dispc_ovl_set_pre_mult_alpha(plane, caps, pre_mult_alpha);
	dispc_ovl_setup_global_alpha(plane, caps, global_alpha);

	dispc_ovl_enable_replication(plane, caps, replication);

	वापस 0;
पूर्ण

पूर्णांक dispc_ovl_setup(क्रमागत omap_plane plane, स्थिर काष्ठा omap_overlay_info *oi,
		bool replication, स्थिर काष्ठा omap_video_timings *mgr_timings,
		bool mem_to_mem)
अणु
	पूर्णांक r;
	क्रमागत omap_overlay_caps caps = dss_feat_get_overlay_caps(plane);
	क्रमागत omap_channel channel;

	channel = dispc_ovl_get_channel_out(plane);

	DSSDBG("dispc_ovl_setup %d, pa %pad, pa_uv %pad, sw %d, %d,%d, %dx%d ->"
		" %dx%d, cmode %x, rot %d, mir %d, chan %d repl %d\n",
		plane, &oi->paddr, &oi->p_uv_addr, oi->screen_width, oi->pos_x,
		oi->pos_y, oi->width, oi->height, oi->out_width, oi->out_height,
		oi->color_mode, oi->rotation, oi->mirror, channel, replication);

	r = dispc_ovl_setup_common(plane, caps, oi->paddr, oi->p_uv_addr,
		oi->screen_width, oi->pos_x, oi->pos_y, oi->width, oi->height,
		oi->out_width, oi->out_height, oi->color_mode, oi->rotation,
		oi->mirror, oi->zorder, oi->pre_mult_alpha, oi->global_alpha,
		oi->rotation_type, replication, mgr_timings, mem_to_mem);

	वापस r;
पूर्ण
EXPORT_SYMBOL(dispc_ovl_setup);

पूर्णांक dispc_ovl_enable(क्रमागत omap_plane plane, bool enable)
अणु
	DSSDBG("dispc_enable_plane %d, %d\n", plane, enable);

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), enable ? 1 : 0, 0, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dispc_ovl_enable);

bool dispc_ovl_enabled(क्रमागत omap_plane plane)
अणु
	वापस REG_GET(DISPC_OVL_ATTRIBUTES(plane), 0, 0);
पूर्ण
EXPORT_SYMBOL(dispc_ovl_enabled);

व्योम dispc_mgr_enable(क्रमागत omap_channel channel, bool enable)
अणु
	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_ENABLE, enable);
	/* flush posted ग_लिखो */
	mgr_fld_पढ़ो(channel, DISPC_MGR_FLD_ENABLE);
पूर्ण
EXPORT_SYMBOL(dispc_mgr_enable);

bool dispc_mgr_is_enabled(क्रमागत omap_channel channel)
अणु
	वापस !!mgr_fld_पढ़ो(channel, DISPC_MGR_FLD_ENABLE);
पूर्ण
EXPORT_SYMBOL(dispc_mgr_is_enabled);

अटल व्योम dispc_lcd_enable_संकेत_polarity(bool act_high)
अणु
	अगर (!dss_has_feature(FEAT_LCDENABLEPOL))
		वापस;

	REG_FLD_MOD(DISPC_CONTROL, act_high ? 1 : 0, 29, 29);
पूर्ण

व्योम dispc_lcd_enable_संकेत(bool enable)
अणु
	अगर (!dss_has_feature(FEAT_LCDENABLESIGNAL))
		वापस;

	REG_FLD_MOD(DISPC_CONTROL, enable ? 1 : 0, 28, 28);
पूर्ण

व्योम dispc_pck_मुक्त_enable(bool enable)
अणु
	अगर (!dss_has_feature(FEAT_PCKFREEENABLE))
		वापस;

	REG_FLD_MOD(DISPC_CONTROL, enable ? 1 : 0, 27, 27);
पूर्ण

अटल व्योम dispc_mgr_enable_fअगरohandcheck(क्रमागत omap_channel channel, bool enable)
अणु
	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_FIFOHANDCHECK, enable);
पूर्ण


अटल व्योम dispc_mgr_set_lcd_type_tft(क्रमागत omap_channel channel)
अणु
	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_STNTFT, 1);
पूर्ण

अटल व्योम dispc_set_loadmode(क्रमागत omap_dss_load_mode mode)
अणु
	REG_FLD_MOD(DISPC_CONFIG, mode, 2, 1);
पूर्ण


अटल व्योम dispc_mgr_set_शेष_color(क्रमागत omap_channel channel, u32 color)
अणु
	dispc_ग_लिखो_reg(DISPC_DEFAULT_COLOR(channel), color);
पूर्ण

अटल व्योम dispc_mgr_set_trans_key(क्रमागत omap_channel ch,
		क्रमागत omap_dss_trans_key_type type,
		u32 trans_key)
अणु
	mgr_fld_ग_लिखो(ch, DISPC_MGR_FLD_TCKSELECTION, type);

	dispc_ग_लिखो_reg(DISPC_TRANS_COLOR(ch), trans_key);
पूर्ण

अटल व्योम dispc_mgr_enable_trans_key(क्रमागत omap_channel ch, bool enable)
अणु
	mgr_fld_ग_लिखो(ch, DISPC_MGR_FLD_TCKENABLE, enable);
पूर्ण

अटल व्योम dispc_mgr_enable_alpha_fixed_zorder(क्रमागत omap_channel ch,
		bool enable)
अणु
	अगर (!dss_has_feature(FEAT_ALPHA_FIXED_ZORDER))
		वापस;

	अगर (ch == OMAP_DSS_CHANNEL_LCD)
		REG_FLD_MOD(DISPC_CONFIG, enable, 18, 18);
	अन्यथा अगर (ch == OMAP_DSS_CHANNEL_DIGIT)
		REG_FLD_MOD(DISPC_CONFIG, enable, 19, 19);
पूर्ण

व्योम dispc_mgr_setup(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_overlay_manager_info *info)
अणु
	dispc_mgr_set_शेष_color(channel, info->शेष_color);
	dispc_mgr_set_trans_key(channel, info->trans_key_type, info->trans_key);
	dispc_mgr_enable_trans_key(channel, info->trans_enabled);
	dispc_mgr_enable_alpha_fixed_zorder(channel,
			info->partial_alpha_enabled);
	अगर (dss_has_feature(FEAT_CPR)) अणु
		dispc_mgr_enable_cpr(channel, info->cpr_enable);
		dispc_mgr_set_cpr_coef(channel, &info->cpr_coefs);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dispc_mgr_setup);

अटल व्योम dispc_mgr_set_tft_data_lines(क्रमागत omap_channel channel, u8 data_lines)
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

	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_TFTDATALINES, code);
पूर्ण

अटल व्योम dispc_mgr_set_io_pad_mode(क्रमागत dss_io_pad_mode mode)
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

	l = dispc_पढ़ो_reg(DISPC_CONTROL);
	l = FLD_MOD(l, gpout0, 15, 15);
	l = FLD_MOD(l, gpout1, 16, 16);
	dispc_ग_लिखो_reg(DISPC_CONTROL, l);
पूर्ण

अटल व्योम dispc_mgr_enable_stallmode(क्रमागत omap_channel channel, bool enable)
अणु
	mgr_fld_ग_लिखो(channel, DISPC_MGR_FLD_STALLMODE, enable);
पूर्ण

व्योम dispc_mgr_set_lcd_config(क्रमागत omap_channel channel,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	dispc_mgr_set_io_pad_mode(config->io_pad_mode);

	dispc_mgr_enable_stallmode(channel, config->stallmode);
	dispc_mgr_enable_fअगरohandcheck(channel, config->fअगरohandcheck);

	dispc_mgr_set_घड़ी_भाग(channel, &config->घड़ी_info);

	dispc_mgr_set_tft_data_lines(channel, config->video_port_width);

	dispc_lcd_enable_संकेत_polarity(config->lcden_sig_polarity);

	dispc_mgr_set_lcd_type_tft(channel);
पूर्ण
EXPORT_SYMBOL(dispc_mgr_set_lcd_config);

अटल bool _dispc_mgr_size_ok(u16 width, u16 height)
अणु
	वापस width <= dispc.feat->mgr_width_max &&
		height <= dispc.feat->mgr_height_max;
पूर्ण

अटल bool _dispc_lcd_timings_ok(पूर्णांक hsw, पूर्णांक hfp, पूर्णांक hbp,
		पूर्णांक vsw, पूर्णांक vfp, पूर्णांक vbp)
अणु
	अगर (hsw < 1 || hsw > dispc.feat->sw_max ||
			hfp < 1 || hfp > dispc.feat->hp_max ||
			hbp < 1 || hbp > dispc.feat->hp_max ||
			vsw < 1 || vsw > dispc.feat->sw_max ||
			vfp < 0 || vfp > dispc.feat->vp_max ||
			vbp < 0 || vbp > dispc.feat->vp_max)
		वापस false;
	वापस true;
पूर्ण

अटल bool _dispc_mgr_pclk_ok(क्रमागत omap_channel channel,
		अचिन्हित दीर्घ pclk)
अणु
	अगर (dss_mgr_is_lcd(channel))
		वापस pclk <= dispc.feat->max_lcd_pclk;
	अन्यथा
		वापस pclk <= dispc.feat->max_tv_pclk;
पूर्ण

bool dispc_mgr_timings_ok(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	अगर (!_dispc_mgr_size_ok(timings->x_res, timings->y_res))
		वापस false;

	अगर (!_dispc_mgr_pclk_ok(channel, timings->pixelघड़ी))
		वापस false;

	अगर (dss_mgr_is_lcd(channel)) अणु
		/* TODO: OMAP4+ supports पूर्णांकerlace क्रम LCD outमाला_दो */
		अगर (timings->पूर्णांकerlace)
			वापस false;

		अगर (!_dispc_lcd_timings_ok(timings->hsw, timings->hfp,
				timings->hbp, timings->vsw, timings->vfp,
				timings->vbp))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम _dispc_mgr_set_lcd_timings(क्रमागत omap_channel channel, पूर्णांक hsw,
		पूर्णांक hfp, पूर्णांक hbp, पूर्णांक vsw, पूर्णांक vfp, पूर्णांक vbp,
		क्रमागत omap_dss_संकेत_level vsync_level,
		क्रमागत omap_dss_संकेत_level hsync_level,
		क्रमागत omap_dss_संकेत_edge data_pclk_edge,
		क्रमागत omap_dss_संकेत_level de_level,
		क्रमागत omap_dss_संकेत_edge sync_pclk_edge)

अणु
	u32 timing_h, timing_v, l;
	bool onoff, rf, ipc, vs, hs, de;

	timing_h = FLD_VAL(hsw-1, dispc.feat->sw_start, 0) |
			FLD_VAL(hfp-1, dispc.feat->fp_start, 8) |
			FLD_VAL(hbp-1, dispc.feat->bp_start, 20);
	timing_v = FLD_VAL(vsw-1, dispc.feat->sw_start, 0) |
			FLD_VAL(vfp, dispc.feat->fp_start, 8) |
			FLD_VAL(vbp, dispc.feat->bp_start, 20);

	dispc_ग_लिखो_reg(DISPC_TIMING_H(channel), timing_h);
	dispc_ग_लिखो_reg(DISPC_TIMING_V(channel), timing_v);

	चयन (vsync_level) अणु
	हाल OMAPDSS_SIG_ACTIVE_LOW:
		vs = true;
		अवरोध;
	हाल OMAPDSS_SIG_ACTIVE_HIGH:
		vs = false;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (hsync_level) अणु
	हाल OMAPDSS_SIG_ACTIVE_LOW:
		hs = true;
		अवरोध;
	हाल OMAPDSS_SIG_ACTIVE_HIGH:
		hs = false;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (de_level) अणु
	हाल OMAPDSS_SIG_ACTIVE_LOW:
		de = true;
		अवरोध;
	हाल OMAPDSS_SIG_ACTIVE_HIGH:
		de = false;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (data_pclk_edge) अणु
	हाल OMAPDSS_DRIVE_SIG_RISING_EDGE:
		ipc = false;
		अवरोध;
	हाल OMAPDSS_DRIVE_SIG_FALLING_EDGE:
		ipc = true;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* always use the 'rf' setting */
	onoff = true;

	चयन (sync_pclk_edge) अणु
	हाल OMAPDSS_DRIVE_SIG_FALLING_EDGE:
		rf = false;
		अवरोध;
	हाल OMAPDSS_DRIVE_SIG_RISING_EDGE:
		rf = true;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	l = FLD_VAL(onoff, 17, 17) |
		FLD_VAL(rf, 16, 16) |
		FLD_VAL(de, 15, 15) |
		FLD_VAL(ipc, 14, 14) |
		FLD_VAL(hs, 13, 13) |
		FLD_VAL(vs, 12, 12);

	/* always set ALIGN bit when available */
	अगर (dispc.feat->supports_sync_align)
		l |= (1 << 18);

	dispc_ग_लिखो_reg(DISPC_POL_FREQ(channel), l);

	अगर (dispc.syscon_pol) अणु
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

		regmap_update_bits(dispc.syscon_pol, dispc.syscon_pol_offset,
			mask, val);
	पूर्ण
पूर्ण

/* change name to mode? */
व्योम dispc_mgr_set_timings(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	अचिन्हित xtot, ytot;
	अचिन्हित दीर्घ ht, vt;
	काष्ठा omap_video_timings t = *timings;

	DSSDBG("channel %d xres %u yres %u\n", channel, t.x_res, t.y_res);

	अगर (!dispc_mgr_timings_ok(channel, &t)) अणु
		BUG();
		वापस;
	पूर्ण

	अगर (dss_mgr_is_lcd(channel)) अणु
		_dispc_mgr_set_lcd_timings(channel, t.hsw, t.hfp, t.hbp, t.vsw,
				t.vfp, t.vbp, t.vsync_level, t.hsync_level,
				t.data_pclk_edge, t.de_level, t.sync_pclk_edge);

		xtot = t.x_res + t.hfp + t.hsw + t.hbp;
		ytot = t.y_res + t.vfp + t.vsw + t.vbp;

		ht = timings->pixelघड़ी / xtot;
		vt = timings->pixelघड़ी / xtot / ytot;

		DSSDBG("pck %u\n", timings->pixelघड़ी);
		DSSDBG("hsw %d hfp %d hbp %d vsw %d vfp %d vbp %d\n",
			t.hsw, t.hfp, t.hbp, t.vsw, t.vfp, t.vbp);
		DSSDBG("vsync_level %d hsync_level %d data_pclk_edge %d de_level %d sync_pclk_edge %d\n",
			t.vsync_level, t.hsync_level, t.data_pclk_edge,
			t.de_level, t.sync_pclk_edge);

		DSSDBG("hsync %luHz, vsync %luHz\n", ht, vt);
	पूर्ण अन्यथा अणु
		अगर (t.पूर्णांकerlace)
			t.y_res /= 2;
	पूर्ण

	dispc_mgr_set_size(channel, t.x_res, t.y_res);
पूर्ण
EXPORT_SYMBOL(dispc_mgr_set_timings);

अटल व्योम dispc_mgr_set_lcd_भागisor(क्रमागत omap_channel channel, u16 lck_भाग,
		u16 pck_भाग)
अणु
	BUG_ON(lck_भाग < 1);
	BUG_ON(pck_भाग < 1);

	dispc_ग_लिखो_reg(DISPC_DIVISORo(channel),
			FLD_VAL(lck_भाग, 23, 16) | FLD_VAL(pck_भाग, 7, 0));

	अगर (!dss_has_feature(FEAT_CORE_CLK_DIV) &&
			channel == OMAP_DSS_CHANNEL_LCD)
		dispc.core_clk_rate = dispc_fclk_rate() / lck_भाग;
पूर्ण

अटल व्योम dispc_mgr_get_lcd_भागisor(क्रमागत omap_channel channel, पूर्णांक *lck_भाग,
		पूर्णांक *pck_भाग)
अणु
	u32 l;
	l = dispc_पढ़ो_reg(DISPC_DIVISORo(channel));
	*lck_भाग = FLD_GET(l, 23, 16);
	*pck_भाग = FLD_GET(l, 7, 0);
पूर्ण

अटल अचिन्हित दीर्घ dispc_fclk_rate(व्योम)
अणु
	काष्ठा dss_pll *pll;
	अचिन्हित दीर्घ r = 0;

	चयन (dss_get_dispc_clk_source()) अणु
	हाल OMAP_DSS_CLK_SRC_FCK:
		r = dss_get_dispc_clk_rate();
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
		pll = dss_pll_find("dsi0");
		अगर (!pll)
			pll = dss_pll_find("video0");

		r = pll->cinfo.clkout[0];
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
		pll = dss_pll_find("dsi1");
		अगर (!pll)
			pll = dss_pll_find("video1");

		r = pll->cinfo.clkout[0];
		अवरोध;
	शेष:
		BUG();
		वापस 0;
	पूर्ण

	वापस r;
पूर्ण

अटल अचिन्हित दीर्घ dispc_mgr_lclk_rate(क्रमागत omap_channel channel)
अणु
	काष्ठा dss_pll *pll;
	पूर्णांक lcd;
	अचिन्हित दीर्घ r;
	u32 l;

	अगर (dss_mgr_is_lcd(channel)) अणु
		l = dispc_पढ़ो_reg(DISPC_DIVISORo(channel));

		lcd = FLD_GET(l, 23, 16);

		चयन (dss_get_lcd_clk_source(channel)) अणु
		हाल OMAP_DSS_CLK_SRC_FCK:
			r = dss_get_dispc_clk_rate();
			अवरोध;
		हाल OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
			pll = dss_pll_find("dsi0");
			अगर (!pll)
				pll = dss_pll_find("video0");

			r = pll->cinfo.clkout[0];
			अवरोध;
		हाल OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
			pll = dss_pll_find("dsi1");
			अगर (!pll)
				pll = dss_pll_find("video1");

			r = pll->cinfo.clkout[0];
			अवरोध;
		शेष:
			BUG();
			वापस 0;
		पूर्ण

		वापस r / lcd;
	पूर्ण अन्यथा अणु
		वापस dispc_fclk_rate();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ dispc_mgr_pclk_rate(क्रमागत omap_channel channel)
अणु
	अचिन्हित दीर्घ r;

	अगर (dss_mgr_is_lcd(channel)) अणु
		पूर्णांक pcd;
		u32 l;

		l = dispc_पढ़ो_reg(DISPC_DIVISORo(channel));

		pcd = FLD_GET(l, 7, 0);

		r = dispc_mgr_lclk_rate(channel);

		वापस r / pcd;
	पूर्ण अन्यथा अणु
		वापस dispc.tv_pclk_rate;
	पूर्ण
पूर्ण

व्योम dispc_set_tv_pclk(अचिन्हित दीर्घ pclk)
अणु
	dispc.tv_pclk_rate = pclk;
पूर्ण

अटल अचिन्हित दीर्घ dispc_core_clk_rate(व्योम)
अणु
	वापस dispc.core_clk_rate;
पूर्ण

अटल अचिन्हित दीर्घ dispc_plane_pclk_rate(क्रमागत omap_plane plane)
अणु
	क्रमागत omap_channel channel;

	अगर (plane == OMAP_DSS_WB)
		वापस 0;

	channel = dispc_ovl_get_channel_out(plane);

	वापस dispc_mgr_pclk_rate(channel);
पूर्ण

अटल अचिन्हित दीर्घ dispc_plane_lclk_rate(क्रमागत omap_plane plane)
अणु
	क्रमागत omap_channel channel;

	अगर (plane == OMAP_DSS_WB)
		वापस 0;

	channel	= dispc_ovl_get_channel_out(plane);

	वापस dispc_mgr_lclk_rate(channel);
पूर्ण

अटल व्योम dispc_dump_घड़ीs_channel(काष्ठा seq_file *s, क्रमागत omap_channel channel)
अणु
	पूर्णांक lcd, pcd;
	क्रमागत omap_dss_clk_source lcd_clk_src;

	seq_म_लिखो(s, "- %s -\n", mgr_desc[channel].name);

	lcd_clk_src = dss_get_lcd_clk_source(channel);

	seq_म_लिखो(s, "%s clk source = %s (%s)\n", mgr_desc[channel].name,
		dss_get_generic_clk_source_name(lcd_clk_src),
		dss_feat_get_clk_source_name(lcd_clk_src));

	dispc_mgr_get_lcd_भागisor(channel, &lcd, &pcd);

	seq_म_लिखो(s, "lck\t\t%-16lulck div\t%u\n",
		dispc_mgr_lclk_rate(channel), lcd);
	seq_म_लिखो(s, "pck\t\t%-16lupck div\t%u\n",
		dispc_mgr_pclk_rate(channel), pcd);
पूर्ण

व्योम dispc_dump_घड़ीs(काष्ठा seq_file *s)
अणु
	पूर्णांक lcd;
	u32 l;
	क्रमागत omap_dss_clk_source dispc_clk_src = dss_get_dispc_clk_source();

	अगर (dispc_runसमय_get())
		वापस;

	seq_म_लिखो(s, "- DISPC -\n");

	seq_म_लिखो(s, "dispc fclk source = %s (%s)\n",
			dss_get_generic_clk_source_name(dispc_clk_src),
			dss_feat_get_clk_source_name(dispc_clk_src));

	seq_म_लिखो(s, "fck\t\t%-16lu\n", dispc_fclk_rate());

	अगर (dss_has_feature(FEAT_CORE_CLK_DIV)) अणु
		seq_म_लिखो(s, "- DISPC-CORE-CLK -\n");
		l = dispc_पढ़ो_reg(DISPC_DIVISOR);
		lcd = FLD_GET(l, 23, 16);

		seq_म_लिखो(s, "lck\t\t%-16lulck div\t%u\n",
				(dispc_fclk_rate()/lcd), lcd);
	पूर्ण

	dispc_dump_घड़ीs_channel(s, OMAP_DSS_CHANNEL_LCD);

	अगर (dss_has_feature(FEAT_MGR_LCD2))
		dispc_dump_घड़ीs_channel(s, OMAP_DSS_CHANNEL_LCD2);
	अगर (dss_has_feature(FEAT_MGR_LCD3))
		dispc_dump_घड़ीs_channel(s, OMAP_DSS_CHANNEL_LCD3);

	dispc_runसमय_put();
पूर्ण

अटल व्योम dispc_dump_regs(काष्ठा seq_file *s)
अणु
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

#घोषणा DUMPREG(r) seq_म_लिखो(s, "%-50s %08x\n", #r, dispc_पढ़ो_reg(r))

	अगर (dispc_runसमय_get())
		वापस;

	/* DISPC common रेजिस्टरs */
	DUMPREG(DISPC_REVISION);
	DUMPREG(DISPC_SYSCONFIG);
	DUMPREG(DISPC_SYSSTATUS);
	DUMPREG(DISPC_IRQSTATUS);
	DUMPREG(DISPC_IRQENABLE);
	DUMPREG(DISPC_CONTROL);
	DUMPREG(DISPC_CONFIG);
	DUMPREG(DISPC_CAPABLE);
	DUMPREG(DISPC_LINE_STATUS);
	DUMPREG(DISPC_LINE_NUMBER);
	अगर (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER) ||
			dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		DUMPREG(DISPC_GLOBAL_ALPHA);
	अगर (dss_has_feature(FEAT_MGR_LCD2)) अणु
		DUMPREG(DISPC_CONTROL2);
		DUMPREG(DISPC_CONFIG2);
	पूर्ण
	अगर (dss_has_feature(FEAT_MGR_LCD3)) अणु
		DUMPREG(DISPC_CONTROL3);
		DUMPREG(DISPC_CONFIG3);
	पूर्ण
	अगर (dss_has_feature(FEAT_MFLAG))
		DUMPREG(DISPC_GLOBAL_MFLAG_ATTRIBUTE);

#अघोषित DUMPREG

#घोषणा DISPC_REG(i, name) name(i)
#घोषणा DUMPREG(i, r) seq_म_लिखो(s, "%s(%s)%*s %08x\n", #r, p_names[i], \
	(पूर्णांक)(48 - म_माप(#r) - म_माप(p_names[i])), " ", \
	dispc_पढ़ो_reg(DISPC_REG(i, r)))

	p_names = mgr_names;

	/* DISPC channel specअगरic रेजिस्टरs */
	क्रम (i = 0; i < dss_feat_get_num_mgrs(); i++) अणु
		DUMPREG(i, DISPC_DEFAULT_COLOR);
		DUMPREG(i, DISPC_TRANS_COLOR);
		DUMPREG(i, DISPC_SIZE_MGR);

		अगर (i == OMAP_DSS_CHANNEL_DIGIT)
			जारी;

		DUMPREG(i, DISPC_TIMING_H);
		DUMPREG(i, DISPC_TIMING_V);
		DUMPREG(i, DISPC_POL_FREQ);
		DUMPREG(i, DISPC_DIVISORo);

		DUMPREG(i, DISPC_DATA_CYCLE1);
		DUMPREG(i, DISPC_DATA_CYCLE2);
		DUMPREG(i, DISPC_DATA_CYCLE3);

		अगर (dss_has_feature(FEAT_CPR)) अणु
			DUMPREG(i, DISPC_CPR_COEF_R);
			DUMPREG(i, DISPC_CPR_COEF_G);
			DUMPREG(i, DISPC_CPR_COEF_B);
		पूर्ण
	पूर्ण

	p_names = ovl_names;

	क्रम (i = 0; i < dss_feat_get_num_ovls(); i++) अणु
		DUMPREG(i, DISPC_OVL_BA0);
		DUMPREG(i, DISPC_OVL_BA1);
		DUMPREG(i, DISPC_OVL_POSITION);
		DUMPREG(i, DISPC_OVL_SIZE);
		DUMPREG(i, DISPC_OVL_ATTRIBUTES);
		DUMPREG(i, DISPC_OVL_FIFO_THRESHOLD);
		DUMPREG(i, DISPC_OVL_FIFO_SIZE_STATUS);
		DUMPREG(i, DISPC_OVL_ROW_INC);
		DUMPREG(i, DISPC_OVL_PIXEL_INC);

		अगर (dss_has_feature(FEAT_PRELOAD))
			DUMPREG(i, DISPC_OVL_PRELOAD);
		अगर (dss_has_feature(FEAT_MFLAG))
			DUMPREG(i, DISPC_OVL_MFLAG_THRESHOLD);

		अगर (i == OMAP_DSS_GFX) अणु
			DUMPREG(i, DISPC_OVL_WINDOW_SKIP);
			DUMPREG(i, DISPC_OVL_TABLE_BA);
			जारी;
		पूर्ण

		DUMPREG(i, DISPC_OVL_FIR);
		DUMPREG(i, DISPC_OVL_PICTURE_SIZE);
		DUMPREG(i, DISPC_OVL_ACCU0);
		DUMPREG(i, DISPC_OVL_ACCU1);
		अगर (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) अणु
			DUMPREG(i, DISPC_OVL_BA0_UV);
			DUMPREG(i, DISPC_OVL_BA1_UV);
			DUMPREG(i, DISPC_OVL_FIR2);
			DUMPREG(i, DISPC_OVL_ACCU2_0);
			DUMPREG(i, DISPC_OVL_ACCU2_1);
		पूर्ण
		अगर (dss_has_feature(FEAT_ATTR2))
			DUMPREG(i, DISPC_OVL_ATTRIBUTES2);
	पूर्ण

	अगर (dispc.feat->has_ग_लिखोback) अणु
		i = OMAP_DSS_WB;
		DUMPREG(i, DISPC_OVL_BA0);
		DUMPREG(i, DISPC_OVL_BA1);
		DUMPREG(i, DISPC_OVL_SIZE);
		DUMPREG(i, DISPC_OVL_ATTRIBUTES);
		DUMPREG(i, DISPC_OVL_FIFO_THRESHOLD);
		DUMPREG(i, DISPC_OVL_FIFO_SIZE_STATUS);
		DUMPREG(i, DISPC_OVL_ROW_INC);
		DUMPREG(i, DISPC_OVL_PIXEL_INC);

		अगर (dss_has_feature(FEAT_MFLAG))
			DUMPREG(i, DISPC_OVL_MFLAG_THRESHOLD);

		DUMPREG(i, DISPC_OVL_FIR);
		DUMPREG(i, DISPC_OVL_PICTURE_SIZE);
		DUMPREG(i, DISPC_OVL_ACCU0);
		DUMPREG(i, DISPC_OVL_ACCU1);
		अगर (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) अणु
			DUMPREG(i, DISPC_OVL_BA0_UV);
			DUMPREG(i, DISPC_OVL_BA1_UV);
			DUMPREG(i, DISPC_OVL_FIR2);
			DUMPREG(i, DISPC_OVL_ACCU2_0);
			DUMPREG(i, DISPC_OVL_ACCU2_1);
		पूर्ण
		अगर (dss_has_feature(FEAT_ATTR2))
			DUMPREG(i, DISPC_OVL_ATTRIBUTES2);
	पूर्ण

#अघोषित DISPC_REG
#अघोषित DUMPREG

#घोषणा DISPC_REG(plane, name, i) name(plane, i)
#घोषणा DUMPREG(plane, name, i) \
	seq_म_लिखो(s, "%s_%d(%s)%*s %08x\n", #name, i, p_names[plane], \
	(पूर्णांक)(46 - म_माप(#name) - म_माप(p_names[plane])), " ", \
	dispc_पढ़ो_reg(DISPC_REG(plane, name, i)))

	/* Video pipeline coefficient रेजिस्टरs */

	/* start from OMAP_DSS_VIDEO1 */
	क्रम (i = 1; i < dss_feat_get_num_ovls(); i++) अणु
		क्रम (j = 0; j < 8; j++)
			DUMPREG(i, DISPC_OVL_FIR_COEF_H, j);

		क्रम (j = 0; j < 8; j++)
			DUMPREG(i, DISPC_OVL_FIR_COEF_HV, j);

		क्रम (j = 0; j < 5; j++)
			DUMPREG(i, DISPC_OVL_CONV_COEF, j);

		अगर (dss_has_feature(FEAT_FIR_COEF_V)) अणु
			क्रम (j = 0; j < 8; j++)
				DUMPREG(i, DISPC_OVL_FIR_COEF_V, j);
		पूर्ण

		अगर (dss_has_feature(FEAT_HANDLE_UV_SEPARATE)) अणु
			क्रम (j = 0; j < 8; j++)
				DUMPREG(i, DISPC_OVL_FIR_COEF_H2, j);

			क्रम (j = 0; j < 8; j++)
				DUMPREG(i, DISPC_OVL_FIR_COEF_HV2, j);

			क्रम (j = 0; j < 8; j++)
				DUMPREG(i, DISPC_OVL_FIR_COEF_V2, j);
		पूर्ण
	पूर्ण

	dispc_runसमय_put();

#अघोषित DISPC_REG
#अघोषित DUMPREG
पूर्ण

/* calculate घड़ी rates using भागiders in cinfo */
पूर्णांक dispc_calc_घड़ी_rates(अचिन्हित दीर्घ dispc_fclk_rate,
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

bool dispc_भाग_calc(अचिन्हित दीर्घ dispc,
		अचिन्हित दीर्घ pck_min, अचिन्हित दीर्घ pck_max,
		dispc_भाग_calc_func func, व्योम *data)
अणु
	पूर्णांक lckd, lckd_start, lckd_stop;
	पूर्णांक pckd, pckd_start, pckd_stop;
	अचिन्हित दीर्घ pck, lck;
	अचिन्हित दीर्घ lck_max;
	अचिन्हित दीर्घ pckd_hw_min, pckd_hw_max;
	अचिन्हित min_fck_per_pck;
	अचिन्हित दीर्घ fck;

#अगर_घोषित CONFIG_FB_OMAP2_DSS_MIN_FCK_PER_PCK
	min_fck_per_pck = CONFIG_FB_OMAP2_DSS_MIN_FCK_PER_PCK;
#अन्यथा
	min_fck_per_pck = 0;
#पूर्ण_अगर

	pckd_hw_min = dss_feat_get_param_min(FEAT_PARAM_DSS_PCD);
	pckd_hw_max = dss_feat_get_param_max(FEAT_PARAM_DSS_PCD);

	lck_max = dss_feat_get_param_max(FEAT_PARAM_DSS_FCK);

	pck_min = pck_min ? pck_min : 1;
	pck_max = pck_max ? pck_max : अच_दीर्घ_उच्च;

	lckd_start = max(DIV_ROUND_UP(dispc, lck_max), 1ul);
	lckd_stop = min(dispc / pck_min, 255ul);

	क्रम (lckd = lckd_start; lckd <= lckd_stop; ++lckd) अणु
		lck = dispc / lckd;

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
			अगर (dss_has_feature(FEAT_CORE_CLK_DIV))
				fck = dispc_core_clk_rate();
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

व्योम dispc_mgr_set_घड़ी_भाग(क्रमागत omap_channel channel,
		स्थिर काष्ठा dispc_घड़ी_info *cinfo)
अणु
	DSSDBG("lck = %lu (%u)\n", cinfo->lck, cinfo->lck_भाग);
	DSSDBG("pck = %lu (%u)\n", cinfo->pck, cinfo->pck_भाग);

	dispc_mgr_set_lcd_भागisor(channel, cinfo->lck_भाग, cinfo->pck_भाग);
पूर्ण

पूर्णांक dispc_mgr_get_घड़ी_भाग(क्रमागत omap_channel channel,
		काष्ठा dispc_घड़ी_info *cinfo)
अणु
	अचिन्हित दीर्घ fck;

	fck = dispc_fclk_rate();

	cinfo->lck_भाग = REG_GET(DISPC_DIVISORo(channel), 23, 16);
	cinfo->pck_भाग = REG_GET(DISPC_DIVISORo(channel), 7, 0);

	cinfo->lck = fck / cinfo->lck_भाग;
	cinfo->pck = cinfo->lck / cinfo->pck_भाग;

	वापस 0;
पूर्ण

u32 dispc_पढ़ो_irqstatus(व्योम)
अणु
	वापस dispc_पढ़ो_reg(DISPC_IRQSTATUS);
पूर्ण
EXPORT_SYMBOL(dispc_पढ़ो_irqstatus);

व्योम dispc_clear_irqstatus(u32 mask)
अणु
	dispc_ग_लिखो_reg(DISPC_IRQSTATUS, mask);
पूर्ण
EXPORT_SYMBOL(dispc_clear_irqstatus);

u32 dispc_पढ़ो_irqenable(व्योम)
अणु
	वापस dispc_पढ़ो_reg(DISPC_IRQENABLE);
पूर्ण
EXPORT_SYMBOL(dispc_पढ़ो_irqenable);

व्योम dispc_ग_लिखो_irqenable(u32 mask)
अणु
	u32 old_mask = dispc_पढ़ो_reg(DISPC_IRQENABLE);

	/* clear the irqstatus क्रम newly enabled irqs */
	dispc_clear_irqstatus((mask ^ old_mask) & mask);

	dispc_ग_लिखो_reg(DISPC_IRQENABLE, mask);
पूर्ण
EXPORT_SYMBOL(dispc_ग_लिखो_irqenable);

व्योम dispc_enable_sidle(व्योम)
अणु
	REG_FLD_MOD(DISPC_SYSCONFIG, 2, 4, 3);	/* SIDLEMODE: smart idle */
पूर्ण

व्योम dispc_disable_sidle(व्योम)
अणु
	REG_FLD_MOD(DISPC_SYSCONFIG, 1, 4, 3);	/* SIDLEMODE: no idle */
पूर्ण

अटल व्योम _omap_dispc_initial_config(व्योम)
अणु
	u32 l;

	/* Exclusively enable DISPC_CORE_CLK and set भागider to 1 */
	अगर (dss_has_feature(FEAT_CORE_CLK_DIV)) अणु
		l = dispc_पढ़ो_reg(DISPC_DIVISOR);
		/* Use DISPC_DIVISOR.LCD, instead of DISPC_DIVISOR1.LCD */
		l = FLD_MOD(l, 1, 0, 0);
		l = FLD_MOD(l, 1, 23, 16);
		dispc_ग_लिखो_reg(DISPC_DIVISOR, l);

		dispc.core_clk_rate = dispc_fclk_rate();
	पूर्ण

	/* FUNCGATED */
	अगर (dss_has_feature(FEAT_FUNCGATED))
		REG_FLD_MOD(DISPC_CONFIG, 1, 9, 9);

	dispc_setup_color_conv_coef();

	dispc_set_loadmode(OMAP_DSS_LOAD_FRAME_ONLY);

	dispc_init_fअगरos();

	dispc_configure_burst_sizes();

	dispc_ovl_enable_zorder_planes();

	अगर (dispc.feat->mstandby_workaround)
		REG_FLD_MOD(DISPC_MSTANDBY_CTRL, 1, 0, 0);

	अगर (dss_has_feature(FEAT_MFLAG))
		dispc_init_mflag();
पूर्ण

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
	.calc_scaling		=	dispc_ovl_calc_scaling_24xx,
	.calc_core_clk		=	calc_core_clk_24xx,
	.num_fअगरos		=	3,
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
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
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
	.calc_scaling		=	dispc_ovl_calc_scaling_34xx,
	.calc_core_clk		=	calc_core_clk_34xx,
	.num_fअगरos		=	3,
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
	.calc_scaling		=	dispc_ovl_calc_scaling_44xx,
	.calc_core_clk		=	calc_core_clk_44xx,
	.num_fअगरos		=	5,
	.gfx_fअगरo_workaround	=	true,
	.set_max_preload	=	true,
	.supports_sync_align	=	true,
	.has_ग_लिखोback		=	true,
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
	.calc_scaling		=	dispc_ovl_calc_scaling_44xx,
	.calc_core_clk		=	calc_core_clk_44xx,
	.num_fअगरos		=	5,
	.gfx_fअगरo_workaround	=	true,
	.mstandby_workaround	=	true,
	.set_max_preload	=	true,
	.supports_sync_align	=	true,
	.has_ग_लिखोback		=	true,
पूर्ण;

अटल स्थिर काष्ठा dispc_features *dispc_get_features(व्योम)
अणु
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP24xx:
		वापस &omap24xx_dispc_feats;

	हाल OMAPDSS_VER_OMAP34xx_ES1:
		वापस &omap34xx_rev1_0_dispc_feats;

	हाल OMAPDSS_VER_OMAP34xx_ES3:
	हाल OMAPDSS_VER_OMAP3630:
	हाल OMAPDSS_VER_AM35xx:
	हाल OMAPDSS_VER_AM43xx:
		वापस &omap34xx_rev3_0_dispc_feats;

	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		वापस &omap44xx_dispc_feats;

	हाल OMAPDSS_VER_OMAP5:
	हाल OMAPDSS_VER_DRA7xx:
		वापस &omap54xx_dispc_feats;

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल irqवापस_t dispc_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	अगर (!dispc.is_enabled)
		वापस IRQ_NONE;

	वापस dispc.user_handler(irq, dispc.user_data);
पूर्ण

पूर्णांक dispc_request_irq(irq_handler_t handler, व्योम *dev_id)
अणु
	पूर्णांक r;

	अगर (dispc.user_handler != शून्य)
		वापस -EBUSY;

	dispc.user_handler = handler;
	dispc.user_data = dev_id;

	/* ensure the dispc_irq_handler sees the values above */
	smp_wmb();

	r = devm_request_irq(&dispc.pdev->dev, dispc.irq, dispc_irq_handler,
			     IRQF_SHARED, "OMAP DISPC", &dispc);
	अगर (r) अणु
		dispc.user_handler = शून्य;
		dispc.user_data = शून्य;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL(dispc_request_irq);

व्योम dispc_मुक्त_irq(व्योम *dev_id)
अणु
	devm_मुक्त_irq(&dispc.pdev->dev, dispc.irq, &dispc);

	dispc.user_handler = शून्य;
	dispc.user_data = शून्य;
पूर्ण
EXPORT_SYMBOL(dispc_मुक्त_irq);

/* DISPC HW IP initialisation */
अटल पूर्णांक dispc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	u32 rev;
	पूर्णांक r = 0;
	काष्ठा resource *dispc_mem;
	काष्ठा device_node *np = pdev->dev.of_node;

	dispc.pdev = pdev;

	spin_lock_init(&dispc.control_lock);

	dispc.feat = dispc_get_features();
	अगर (!dispc.feat)
		वापस -ENODEV;

	dispc_mem = platक्रमm_get_resource(dispc.pdev, IORESOURCE_MEM, 0);
	अगर (!dispc_mem) अणु
		DSSERR("can't get IORESOURCE_MEM DISPC\n");
		वापस -EINVAL;
	पूर्ण

	dispc.base = devm_ioremap(&pdev->dev, dispc_mem->start,
				  resource_size(dispc_mem));
	अगर (!dispc.base) अणु
		DSSERR("can't ioremap DISPC\n");
		वापस -ENOMEM;
	पूर्ण

	dispc.irq = platक्रमm_get_irq(dispc.pdev, 0);
	अगर (dispc.irq < 0) अणु
		DSSERR("platform_get_irq failed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (np && of_property_पढ़ो_bool(np, "syscon-pol")) अणु
		dispc.syscon_pol = syscon_regmap_lookup_by_phandle(np, "syscon-pol");
		अगर (IS_ERR(dispc.syscon_pol)) अणु
			dev_err(&pdev->dev, "failed to get syscon-pol regmap\n");
			वापस PTR_ERR(dispc.syscon_pol);
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(np, "syscon-pol", 1,
				&dispc.syscon_pol_offset)) अणु
			dev_err(&pdev->dev, "failed to get syscon-pol offset\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	r = dispc_runसमय_get();
	अगर (r)
		जाओ err_runसमय_get;

	_omap_dispc_initial_config();

	rev = dispc_पढ़ो_reg(DISPC_REVISION);
	dev_dbg(&pdev->dev, "OMAP DISPC rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dispc_runसमय_put();

	dss_init_overlay_managers();

	dss_debugfs_create_file("dispc", dispc_dump_regs);

	वापस 0;

err_runसमय_get:
	pm_runसमय_disable(&pdev->dev);
	वापस r;
पूर्ण

अटल व्योम dispc_unbind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	pm_runसमय_disable(dev);

	dss_uninit_overlay_managers();
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
	dispc.is_enabled = false;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();
	/* रुको क्रम current handler to finish beक्रमe turning the DISPC off */
	synchronize_irq(dispc.irq);

	dispc_save_context();

	वापस 0;
पूर्ण

अटल पूर्णांक dispc_runसमय_resume(काष्ठा device *dev)
अणु
	/*
	 * The reset value क्रम load mode is 0 (OMAP_DSS_LOAD_CLUT_AND_FRAME)
	 * but we always initialize it to 2 (OMAP_DSS_LOAD_FRAME_ONLY) in
	 * _omap_dispc_initial_config(). We can thus use it to detect अगर
	 * we have lost रेजिस्टर context.
	 */
	अगर (REG_GET(DISPC_CONFIG, 2, 1) != OMAP_DSS_LOAD_FRAME_ONLY) अणु
		_omap_dispc_initial_config();

		dispc_restore_context();
	पूर्ण

	dispc.is_enabled = true;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dispc_pm_ops = अणु
	.runसमय_suspend = dispc_runसमय_suspend,
	.runसमय_resume = dispc_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dispc_of_match[] = अणु
	अणु .compatible = "ti,omap2-dispc", पूर्ण,
	अणु .compatible = "ti,omap3-dispc", पूर्ण,
	अणु .compatible = "ti,omap4-dispc", पूर्ण,
	अणु .compatible = "ti,omap5-dispc", पूर्ण,
	अणु .compatible = "ti,dra7-dispc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_dispchw_driver = अणु
	.probe		= dispc_probe,
	.हटाओ         = dispc_हटाओ,
	.driver         = अणु
		.name   = "omapdss_dispc",
		.pm	= &dispc_pm_ops,
		.of_match_table = dispc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init dispc_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_dispchw_driver);
पूर्ण

व्योम dispc_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_dispchw_driver);
पूर्ण
