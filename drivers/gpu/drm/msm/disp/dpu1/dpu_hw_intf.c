<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#समावेश "dpu_hwio.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_intf.h"
#समावेश "dpu_kms.h"

#घोषणा INTF_TIMING_ENGINE_EN           0x000
#घोषणा INTF_CONFIG                     0x004
#घोषणा INTF_HSYNC_CTL                  0x008
#घोषणा INTF_VSYNC_PERIOD_F0            0x00C
#घोषणा INTF_VSYNC_PERIOD_F1            0x010
#घोषणा INTF_VSYNC_PULSE_WIDTH_F0       0x014
#घोषणा INTF_VSYNC_PULSE_WIDTH_F1       0x018
#घोषणा INTF_DISPLAY_V_START_F0         0x01C
#घोषणा INTF_DISPLAY_V_START_F1         0x020
#घोषणा INTF_DISPLAY_V_END_F0           0x024
#घोषणा INTF_DISPLAY_V_END_F1           0x028
#घोषणा INTF_ACTIVE_V_START_F0          0x02C
#घोषणा INTF_ACTIVE_V_START_F1          0x030
#घोषणा INTF_ACTIVE_V_END_F0            0x034
#घोषणा INTF_ACTIVE_V_END_F1            0x038
#घोषणा INTF_DISPLAY_HCTL               0x03C
#घोषणा INTF_ACTIVE_HCTL                0x040
#घोषणा INTF_BORDER_COLOR               0x044
#घोषणा INTF_UNDERFLOW_COLOR            0x048
#घोषणा INTF_HSYNC_SKEW                 0x04C
#घोषणा INTF_POLARITY_CTL               0x050
#घोषणा INTF_TEST_CTL                   0x054
#घोषणा INTF_TP_COLOR0                  0x058
#घोषणा INTF_TP_COLOR1                  0x05C
#घोषणा INTF_CONFIG2                    0x060
#घोषणा INTF_DISPLAY_DATA_HCTL          0x064
#घोषणा INTF_FRAME_LINE_COUNT_EN        0x0A8
#घोषणा INTF_FRAME_COUNT                0x0AC
#घोषणा   INTF_LINE_COUNT               0x0B0

#घोषणा   INTF_DEFLICKER_CONFIG         0x0F0
#घोषणा   INTF_DEFLICKER_STRNG_COEFF    0x0F4
#घोषणा   INTF_DEFLICKER_WEAK_COEFF     0x0F8

#घोषणा   INTF_DSI_CMD_MODE_TRIGGER_EN  0x084
#घोषणा   INTF_PANEL_FORMAT             0x090
#घोषणा   INTF_TPG_ENABLE               0x100
#घोषणा   INTF_TPG_MAIN_CONTROL         0x104
#घोषणा   INTF_TPG_VIDEO_CONFIG         0x108
#घोषणा   INTF_TPG_COMPONENT_LIMITS     0x10C
#घोषणा   INTF_TPG_RECTANGLE            0x110
#घोषणा   INTF_TPG_INITIAL_VALUE        0x114
#घोषणा   INTF_TPG_BLK_WHITE_PATTERN_FRAMES   0x118
#घोषणा   INTF_TPG_RGB_MAPPING          0x11C
#घोषणा   INTF_PROG_FETCH_START         0x170
#घोषणा   INTF_PROG_ROT_START           0x174

#घोषणा   INTF_FRAME_LINE_COUNT_EN      0x0A8
#घोषणा   INTF_FRAME_COUNT              0x0AC
#घोषणा   INTF_LINE_COUNT               0x0B0

#घोषणा   INTF_MUX                      0x25C

अटल स्थिर काष्ठा dpu_पूर्णांकf_cfg *_पूर्णांकf_offset(क्रमागत dpu_पूर्णांकf पूर्णांकf,
		स्थिर काष्ठा dpu_mdss_cfg *m,
		व्योम __iomem *addr,
		काष्ठा dpu_hw_blk_reg_map *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->पूर्णांकf_count; i++) अणु
		अगर ((पूर्णांकf == m->पूर्णांकf[i].id) &&
		(m->पूर्णांकf[i].type != INTF_NONE)) अणु
			b->base_off = addr;
			b->blk_off = m->पूर्णांकf[i].base;
			b->length = m->पूर्णांकf[i].len;
			b->hwversion = m->hwversion;
			b->log_mask = DPU_DBG_MASK_INTF;
			वापस &m->पूर्णांकf[i];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_setup_timing_engine(काष्ठा dpu_hw_पूर्णांकf *ctx,
		स्थिर काष्ठा पूर्णांकf_timing_params *p,
		स्थिर काष्ठा dpu_क्रमmat *fmt)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 hsync_period, vsync_period;
	u32 display_v_start, display_v_end;
	u32 hsync_start_x, hsync_end_x;
	u32 active_h_start, active_h_end;
	u32 active_v_start, active_v_end;
	u32 active_hctl, display_hctl, hsync_ctl;
	u32 polarity_ctl, den_polarity, hsync_polarity, vsync_polarity;
	u32 panel_क्रमmat;
	u32 पूर्णांकf_cfg, पूर्णांकf_cfg2 = 0, display_data_hctl = 0;

	/* पढ़ो पूर्णांकerface_cfg */
	पूर्णांकf_cfg = DPU_REG_READ(c, INTF_CONFIG);
	hsync_period = p->hsync_pulse_width + p->h_back_porch + p->width +
	p->h_front_porch;
	vsync_period = p->vsync_pulse_width + p->v_back_porch + p->height +
	p->v_front_porch;

	display_v_start = ((p->vsync_pulse_width + p->v_back_porch) *
	hsync_period) + p->hsync_skew;
	display_v_end = ((vsync_period - p->v_front_porch) * hsync_period) +
	p->hsync_skew - 1;

	hsync_start_x = p->h_back_porch + p->hsync_pulse_width;
	hsync_end_x = hsync_period - p->h_front_porch - 1;

	अगर (p->width != p->xres) अणु
		active_h_start = hsync_start_x;
		active_h_end = active_h_start + p->xres - 1;
	पूर्ण अन्यथा अणु
		active_h_start = 0;
		active_h_end = 0;
	पूर्ण

	अगर (p->height != p->yres) अणु
		active_v_start = display_v_start;
		active_v_end = active_v_start + (p->yres * hsync_period) - 1;
	पूर्ण अन्यथा अणु
		active_v_start = 0;
		active_v_end = 0;
	पूर्ण

	अगर (active_h_end) अणु
		active_hctl = (active_h_end << 16) | active_h_start;
		पूर्णांकf_cfg |= BIT(29);	/* ACTIVE_H_ENABLE */
	पूर्ण अन्यथा अणु
		active_hctl = 0;
	पूर्ण

	अगर (active_v_end)
		पूर्णांकf_cfg |= BIT(30); /* ACTIVE_V_ENABLE */

	hsync_ctl = (hsync_period << 16) | p->hsync_pulse_width;
	display_hctl = (hsync_end_x << 16) | hsync_start_x;

	अगर (ctx->cap->type == INTF_EDP || ctx->cap->type == INTF_DP) अणु
		active_h_start = hsync_start_x;
		active_h_end = active_h_start + p->xres - 1;
		active_v_start = display_v_start;
		active_v_end = active_v_start + (p->yres * hsync_period) - 1;

		display_v_start += p->hsync_pulse_width + p->h_back_porch;

		active_hctl = (active_h_end << 16) | active_h_start;
		display_hctl = active_hctl;
	पूर्ण

	den_polarity = 0;
	अगर (ctx->cap->type == INTF_HDMI) अणु
		hsync_polarity = p->yres >= 720 ? 0 : 1;
		vsync_polarity = p->yres >= 720 ? 0 : 1;
	पूर्ण अन्यथा अगर (ctx->cap->type == INTF_DP) अणु
		hsync_polarity = p->hsync_polarity;
		vsync_polarity = p->vsync_polarity;
	पूर्ण अन्यथा अणु
		hsync_polarity = 0;
		vsync_polarity = 0;
	पूर्ण
	polarity_ctl = (den_polarity << 2) | /*  DEN Polarity  */
		(vsync_polarity << 1) | /* VSYNC Polarity */
		(hsync_polarity << 0);  /* HSYNC Polarity */

	अगर (!DPU_FORMAT_IS_YUV(fmt))
		panel_क्रमmat = (fmt->bits[C0_G_Y] |
				(fmt->bits[C1_B_Cb] << 2) |
				(fmt->bits[C2_R_Cr] << 4) |
				(0x21 << 8));
	अन्यथा
		/* Interface treats all the pixel data in RGB888 क्रमmat */
		panel_क्रमmat = (COLOR_8BIT |
				(COLOR_8BIT << 2) |
				(COLOR_8BIT << 4) |
				(0x21 << 8));

	अगर (ctx->cap->features & BIT(DPU_DATA_HCTL_EN)) अणु
		पूर्णांकf_cfg2 |= BIT(4);
		display_data_hctl = display_hctl;
		DPU_REG_WRITE(c, INTF_CONFIG2, पूर्णांकf_cfg2);
		DPU_REG_WRITE(c, INTF_DISPLAY_DATA_HCTL, display_data_hctl);
	पूर्ण

	DPU_REG_WRITE(c, INTF_HSYNC_CTL, hsync_ctl);
	DPU_REG_WRITE(c, INTF_VSYNC_PERIOD_F0, vsync_period * hsync_period);
	DPU_REG_WRITE(c, INTF_VSYNC_PULSE_WIDTH_F0,
			p->vsync_pulse_width * hsync_period);
	DPU_REG_WRITE(c, INTF_DISPLAY_HCTL, display_hctl);
	DPU_REG_WRITE(c, INTF_DISPLAY_V_START_F0, display_v_start);
	DPU_REG_WRITE(c, INTF_DISPLAY_V_END_F0, display_v_end);
	DPU_REG_WRITE(c, INTF_ACTIVE_HCTL,  active_hctl);
	DPU_REG_WRITE(c, INTF_ACTIVE_V_START_F0, active_v_start);
	DPU_REG_WRITE(c, INTF_ACTIVE_V_END_F0, active_v_end);
	DPU_REG_WRITE(c, INTF_BORDER_COLOR, p->border_clr);
	DPU_REG_WRITE(c, INTF_UNDERFLOW_COLOR, p->underflow_clr);
	DPU_REG_WRITE(c, INTF_HSYNC_SKEW, p->hsync_skew);
	DPU_REG_WRITE(c, INTF_POLARITY_CTL, polarity_ctl);
	DPU_REG_WRITE(c, INTF_FRAME_LINE_COUNT_EN, 0x3);
	DPU_REG_WRITE(c, INTF_CONFIG, पूर्णांकf_cfg);
	DPU_REG_WRITE(c, INTF_PANEL_FORMAT, panel_क्रमmat);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_enable_timing_engine(
		काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
		u8 enable)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &पूर्णांकf->hw;
	/* Note: Display पूर्णांकerface select is handled in top block hw layer */
	DPU_REG_WRITE(c, INTF_TIMING_ENGINE_EN, enable != 0);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_setup_prg_fetch(
		काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
		स्थिर काष्ठा पूर्णांकf_prog_fetch *fetch)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &पूर्णांकf->hw;
	पूर्णांक fetch_enable;

	/*
	 * Fetch should always be outside the active lines. If the fetching
	 * is programmed within active region, hardware behavior is unknown.
	 */

	fetch_enable = DPU_REG_READ(c, INTF_CONFIG);
	अगर (fetch->enable) अणु
		fetch_enable |= BIT(31);
		DPU_REG_WRITE(c, INTF_PROG_FETCH_START,
				fetch->fetch_start);
	पूर्ण अन्यथा अणु
		fetch_enable &= ~BIT(31);
	पूर्ण

	DPU_REG_WRITE(c, INTF_CONFIG, fetch_enable);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_bind_pingpong_blk(
		काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
		bool enable,
		स्थिर क्रमागत dpu_pingpong pp)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &पूर्णांकf->hw;
	u32 mux_cfg;

	mux_cfg = DPU_REG_READ(c, INTF_MUX);
	mux_cfg &= ~0xf;

	अगर (enable)
		mux_cfg |= (pp - PINGPONG_0) & 0x7;
	अन्यथा
		mux_cfg |= 0xf;

	DPU_REG_WRITE(c, INTF_MUX, mux_cfg);
पूर्ण

अटल व्योम dpu_hw_पूर्णांकf_get_status(
		काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf,
		काष्ठा पूर्णांकf_status *s)
अणु
	काष्ठा dpu_hw_blk_reg_map *c = &पूर्णांकf->hw;

	s->is_en = DPU_REG_READ(c, INTF_TIMING_ENGINE_EN);
	s->is_prog_fetch_en = !!(DPU_REG_READ(c, INTF_CONFIG) & BIT(31));
	अगर (s->is_en) अणु
		s->frame_count = DPU_REG_READ(c, INTF_FRAME_COUNT);
		s->line_count = DPU_REG_READ(c, INTF_LINE_COUNT);
	पूर्ण अन्यथा अणु
		s->line_count = 0;
		s->frame_count = 0;
	पूर्ण
पूर्ण

अटल u32 dpu_hw_पूर्णांकf_get_line_count(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf)
अणु
	काष्ठा dpu_hw_blk_reg_map *c;

	अगर (!पूर्णांकf)
		वापस 0;

	c = &पूर्णांकf->hw;

	वापस DPU_REG_READ(c, INTF_LINE_COUNT);
पूर्ण

अटल व्योम _setup_पूर्णांकf_ops(काष्ठा dpu_hw_पूर्णांकf_ops *ops,
		अचिन्हित दीर्घ cap)
अणु
	ops->setup_timing_gen = dpu_hw_पूर्णांकf_setup_timing_engine;
	ops->setup_prg_fetch  = dpu_hw_पूर्णांकf_setup_prg_fetch;
	ops->get_status = dpu_hw_पूर्णांकf_get_status;
	ops->enable_timing = dpu_hw_पूर्णांकf_enable_timing_engine;
	ops->get_line_count = dpu_hw_पूर्णांकf_get_line_count;
	अगर (cap & BIT(DPU_INTF_INPUT_CTRL))
		ops->bind_pingpong_blk = dpu_hw_पूर्णांकf_bind_pingpong_blk;
पूर्ण

अटल काष्ठा dpu_hw_blk_ops dpu_hw_ops;

काष्ठा dpu_hw_पूर्णांकf *dpu_hw_पूर्णांकf_init(क्रमागत dpu_पूर्णांकf idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m)
अणु
	काष्ठा dpu_hw_पूर्णांकf *c;
	स्थिर काष्ठा dpu_पूर्णांकf_cfg *cfg;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस ERR_PTR(-ENOMEM);

	cfg = _पूर्णांकf_offset(idx, m, addr, &c->hw);
	अगर (IS_ERR_OR_शून्य(cfg)) अणु
		kमुक्त(c);
		pr_err("failed to create dpu_hw_intf %d\n", idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Assign ops
	 */
	c->idx = idx;
	c->cap = cfg;
	c->mdss = m;
	_setup_पूर्णांकf_ops(&c->ops, c->cap->features);

	dpu_hw_blk_init(&c->base, DPU_HW_BLK_INTF, idx, &dpu_hw_ops);

	वापस c;
पूर्ण

व्योम dpu_hw_पूर्णांकf_destroy(काष्ठा dpu_hw_पूर्णांकf *पूर्णांकf)
अणु
	अगर (पूर्णांकf)
		dpu_hw_blk_destroy(&पूर्णांकf->base);
	kमुक्त(पूर्णांकf);
पूर्ण

