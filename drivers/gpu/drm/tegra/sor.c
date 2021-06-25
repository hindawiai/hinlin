<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश <soc/tegra/pmc.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_scdc_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "dc.h"
#समावेश "dp.h"
#समावेश "drm.h"
#समावेश "hda.h"
#समावेश "sor.h"
#समावेश "trace.h"

#घोषणा SOR_REKEY 0x38

काष्ठा tegra_sor_hdmi_settings अणु
	अचिन्हित दीर्घ frequency;

	u8 vcocap;
	u8 filter;
	u8 ichpmp;
	u8 loadadj;
	u8 पंचांगds_termadj;
	u8 tx_pu_value;
	u8 bg_temp_coef;
	u8 bg_vref_level;
	u8 avdd10_level;
	u8 avdd14_level;
	u8 sparepll;

	u8 drive_current[4];
	u8 preemphasis[4];
पूर्ण;

#अगर 1
अटल स्थिर काष्ठा tegra_sor_hdmi_settings tegra210_sor_hdmi_शेषs[] = अणु
	अणु
		.frequency = 54000000,
		.vcocap = 0x0,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x10,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x33, 0x3a, 0x3a, 0x3a पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 75000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x40,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x33, 0x3a, 0x3a, 0x3a पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 150000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x33, 0x3a, 0x3a, 0x3a पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 300000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0xa,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x33, 0x3f, 0x3f, 0x3f पूर्ण,
		.preemphasis = अणु 0x00, 0x17, 0x17, 0x17 पूर्ण,
	पूर्ण, अणु
		.frequency = 600000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x33, 0x3f, 0x3f, 0x3f पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा tegra_sor_hdmi_settings tegra210_sor_hdmi_शेषs[] = अणु
	अणु
		.frequency = 75000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x40,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x29, 0x29, 0x29, 0x29 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 150000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x1,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0x8,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x30, 0x37, 0x37, 0x37 पूर्ण,
		.preemphasis = अणु 0x01, 0x02, 0x02, 0x02 पूर्ण,
	पूर्ण, अणु
		.frequency = 300000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0x6,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0x9,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0xf,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x30, 0x37, 0x37, 0x37 पूर्ण,
		.preemphasis = अणु 0x10, 0x3e, 0x3e, 0x3e पूर्ण,
	पूर्ण, अणु
		.frequency = 600000000,
		.vcocap = 0x3,
		.filter = 0x0,
		.ichpmp = 0xa,
		.loadadj = 0x3,
		.पंचांगds_termadj = 0xb,
		.tx_pu_value = 0x66,
		.bg_temp_coef = 0x3,
		.bg_vref_level = 0xe,
		.avdd10_level = 0x4,
		.avdd14_level = 0x4,
		.sparepll = 0x0,
		.drive_current = अणु 0x35, 0x3e, 0x3e, 0x3e पूर्ण,
		.preemphasis = अणु 0x02, 0x3f, 0x3f, 0x3f पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा tegra_sor_hdmi_settings tegra186_sor_hdmi_शेषs[] = अणु
	अणु
		.frequency = 54000000,
		.vcocap = 0,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 0xf,
		.tx_pu_value = 0,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x54,
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 75000000,
		.vcocap = 1,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 0xf,
		.tx_pu_value = 0,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x44,
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 150000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 15,
		.tx_pu_value = 0x66 /* 0 */,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x00, /* 0x34 */
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x37 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 300000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 15,
		.tx_pu_value = 64,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x34,
		.drive_current = अणु 0x3d, 0x3d, 0x3d, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 600000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 12,
		.tx_pu_value = 96,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x34,
		.drive_current = अणु 0x3d, 0x3d, 0x3d, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_hdmi_settings tegra194_sor_hdmi_शेषs[] = अणु
	अणु
		.frequency = 54000000,
		.vcocap = 0,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 0xf,
		.tx_pu_value = 0,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x54,
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 75000000,
		.vcocap = 1,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 0xf,
		.tx_pu_value = 0,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x44,
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 150000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 15,
		.tx_pu_value = 0x66 /* 0 */,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x00, /* 0x34 */
		.drive_current = अणु 0x3a, 0x3a, 0x3a, 0x37 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 300000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 15,
		.tx_pu_value = 64,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x34,
		.drive_current = अणु 0x3d, 0x3d, 0x3d, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण, अणु
		.frequency = 600000000,
		.vcocap = 3,
		.filter = 5,
		.ichpmp = 5,
		.loadadj = 3,
		.पंचांगds_termadj = 12,
		.tx_pu_value = 96,
		.bg_temp_coef = 3,
		.bg_vref_level = 8,
		.avdd10_level = 4,
		.avdd14_level = 4,
		.sparepll = 0x34,
		.drive_current = अणु 0x3d, 0x3d, 0x3d, 0x33 पूर्ण,
		.preemphasis = अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
	पूर्ण
पूर्ण;

काष्ठा tegra_sor_regs अणु
	अचिन्हित पूर्णांक head_state0;
	अचिन्हित पूर्णांक head_state1;
	अचिन्हित पूर्णांक head_state2;
	अचिन्हित पूर्णांक head_state3;
	अचिन्हित पूर्णांक head_state4;
	अचिन्हित पूर्णांक head_state5;
	अचिन्हित पूर्णांक pll0;
	अचिन्हित पूर्णांक pll1;
	अचिन्हित पूर्णांक pll2;
	अचिन्हित पूर्णांक pll3;
	अचिन्हित पूर्णांक dp_padctl0;
	अचिन्हित पूर्णांक dp_padctl2;
पूर्ण;

काष्ठा tegra_sor_soc अणु
	bool supports_lvds;
	bool supports_hdmi;
	bool supports_dp;
	bool supports_audio;
	bool supports_hdcp;

	स्थिर काष्ठा tegra_sor_regs *regs;
	bool has_nvdisplay;

	स्थिर काष्ठा tegra_sor_hdmi_settings *settings;
	अचिन्हित पूर्णांक num_settings;

	स्थिर u8 *xbar_cfg;
	स्थिर u8 *lane_map;

	स्थिर u8 (*voltage_swing)[4][4];
	स्थिर u8 (*pre_emphasis)[4][4];
	स्थिर u8 (*post_cursor)[4][4];
	स्थिर u8 (*tx_pu)[4][4];
पूर्ण;

काष्ठा tegra_sor;

काष्ठा tegra_sor_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक (*probe)(काष्ठा tegra_sor *sor);
	व्योम (*audio_enable)(काष्ठा tegra_sor *sor);
	व्योम (*audio_disable)(काष्ठा tegra_sor *sor);
पूर्ण;

काष्ठा tegra_sor अणु
	काष्ठा host1x_client client;
	काष्ठा tegra_output output;
	काष्ठा device *dev;

	स्थिर काष्ठा tegra_sor_soc *soc;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक irq;

	काष्ठा reset_control *rst;
	काष्ठा clk *clk_parent;
	काष्ठा clk *clk_safe;
	काष्ठा clk *clk_out;
	काष्ठा clk *clk_pad;
	काष्ठा clk *clk_dp;
	काष्ठा clk *clk;

	u8 xbar_cfg[5];

	काष्ठा drm_dp_link link;
	काष्ठा drm_dp_aux *aux;

	काष्ठा drm_info_list *debugfs_files;

	स्थिर काष्ठा tegra_sor_ops *ops;
	क्रमागत tegra_io_pad pad;

	/* क्रम HDMI 2.0 */
	काष्ठा tegra_sor_hdmi_settings *settings;
	अचिन्हित पूर्णांक num_settings;

	काष्ठा regulator *avdd_io_supply;
	काष्ठा regulator *vdd_pll_supply;
	काष्ठा regulator *hdmi_supply;

	काष्ठा delayed_work scdc;
	bool scdc_enabled;

	काष्ठा tegra_hda_क्रमmat क्रमmat;
पूर्ण;

काष्ठा tegra_sor_state अणु
	काष्ठा drm_connector_state base;

	अचिन्हित पूर्णांक link_speed;
	अचिन्हित दीर्घ pclk;
	अचिन्हित पूर्णांक bpc;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_sor_state *
to_sor_state(काष्ठा drm_connector_state *state)
अणु
	वापस container_of(state, काष्ठा tegra_sor_state, base);
पूर्ण

काष्ठा tegra_sor_config अणु
	u32 bits_per_pixel;

	u32 active_polarity;
	u32 active_count;
	u32 tu_size;
	u32 active_frac;
	u32 watermark;

	u32 hblank_symbols;
	u32 vblank_symbols;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_sor *
host1x_client_to_sor(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_sor, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_sor *to_sor(काष्ठा tegra_output *output)
अणु
	वापस container_of(output, काष्ठा tegra_sor, output);
पूर्ण

अटल अंतरभूत u32 tegra_sor_पढ़ोl(काष्ठा tegra_sor *sor, अचिन्हित पूर्णांक offset)
अणु
	u32 value = पढ़ोl(sor->regs + (offset << 2));

	trace_sor_पढ़ोl(sor->dev, offset, value);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम tegra_sor_ग_लिखोl(काष्ठा tegra_sor *sor, u32 value,
				    अचिन्हित पूर्णांक offset)
अणु
	trace_sor_ग_लिखोl(sor->dev, offset, value);
	ग_लिखोl(value, sor->regs + (offset << 2));
पूर्ण

अटल पूर्णांक tegra_sor_set_parent_घड़ी(काष्ठा tegra_sor *sor, काष्ठा clk *parent)
अणु
	पूर्णांक err;

	clk_disable_unprepare(sor->clk);

	err = clk_set_parent(sor->clk_out, parent);
	अगर (err < 0)
		वापस err;

	err = clk_prepare_enable(sor->clk);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

काष्ठा tegra_clk_sor_pad अणु
	काष्ठा clk_hw hw;
	काष्ठा tegra_sor *sor;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_clk_sor_pad *to_pad(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा tegra_clk_sor_pad, hw);
पूर्ण

अटल स्थिर अक्षर * स्थिर tegra_clk_sor_pad_parents[2][2] = अणु
	अणु "pll_d_out0", "pll_dp" पूर्ण,
	अणु "pll_d2_out0", "pll_dp" पूर्ण,
पूर्ण;

/*
 * Implementing ->set_parent() here isn't really required because the parent
 * will be explicitly selected in the driver code via the DP_CLK_SEL mux in
 * the SOR_CLK_CNTRL रेजिस्टर. This is primarily क्रम compatibility with the
 * Tegra186 and later SoC generations where the BPMP implements this घड़ी
 * and करोesn't expose the mux via the common घड़ी framework.
 */

अटल पूर्णांक tegra_clk_sor_pad_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_clk_sor_pad *pad = to_pad(hw);
	काष्ठा tegra_sor *sor = pad->sor;
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;

	चयन (index) अणु
	हाल 0:
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK;
		अवरोध;

	हाल 1:
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK;
		अवरोध;
	पूर्ण

	tegra_sor_ग_लिखोl(sor, value, SOR_CLK_CNTRL);

	वापस 0;
पूर्ण

अटल u8 tegra_clk_sor_pad_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_sor_pad *pad = to_pad(hw);
	काष्ठा tegra_sor *sor = pad->sor;
	u8 parent = U8_MAX;
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_CLK_CNTRL);

	चयन (value & SOR_CLK_CNTRL_DP_CLK_SEL_MASK) अणु
	हाल SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK:
	हाल SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_PCLK:
		parent = 0;
		अवरोध;

	हाल SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK:
	हाल SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_DPCLK:
		parent = 1;
		अवरोध;
	पूर्ण

	वापस parent;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_sor_pad_ops = अणु
	.set_parent = tegra_clk_sor_pad_set_parent,
	.get_parent = tegra_clk_sor_pad_get_parent,
पूर्ण;

अटल काष्ठा clk *tegra_clk_sor_pad_रेजिस्टर(काष्ठा tegra_sor *sor,
					      स्थिर अक्षर *name)
अणु
	काष्ठा tegra_clk_sor_pad *pad;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	pad = devm_kzalloc(sor->dev, माप(*pad), GFP_KERNEL);
	अगर (!pad)
		वापस ERR_PTR(-ENOMEM);

	pad->sor = sor;

	init.name = name;
	init.flags = 0;
	init.parent_names = tegra_clk_sor_pad_parents[sor->index];
	init.num_parents = ARRAY_SIZE(tegra_clk_sor_pad_parents[sor->index]);
	init.ops = &tegra_clk_sor_pad_ops;

	pad->hw.init = &init;

	clk = devm_clk_रेजिस्टर(sor->dev, &pad->hw);

	वापस clk;
पूर्ण

अटल व्योम tegra_sor_filter_rates(काष्ठा tegra_sor *sor)
अणु
	काष्ठा drm_dp_link *link = &sor->link;
	अचिन्हित पूर्णांक i;

	/* Tegra only supports RBR, HBR and HBR2 */
	क्रम (i = 0; i < link->num_rates; i++) अणु
		चयन (link->rates[i]) अणु
		हाल 1620000:
		हाल 2700000:
		हाल 5400000:
			अवरोध;

		शेष:
			DRM_DEBUG_KMS("link rate %lu kHz not supported\n",
				      link->rates[i]);
			link->rates[i] = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	drm_dp_link_update_rates(link);
पूर्ण

अटल पूर्णांक tegra_sor_घातer_up_lanes(काष्ठा tegra_sor *sor, अचिन्हित पूर्णांक lanes)
अणु
	अचिन्हित दीर्घ समयout;
	u32 value;

	/*
	 * Clear or set the PD_TXD bit corresponding to each lane, depending
	 * on whether it is used or not.
	 */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);

	अगर (lanes <= 2)
		value &= ~(SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[3]) |
			   SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[2]));
	अन्यथा
		value |= SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[3]) |
			 SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[2]);

	अगर (lanes <= 1)
		value &= ~SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[1]);
	अन्यथा
		value |= SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[1]);

	अगर (lanes == 0)
		value &= ~SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[0]);
	अन्यथा
		value |= SOR_DP_PADCTL_PD_TXD(sor->soc->lane_map[0]);

	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	/* start lane sequencer */
	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_DOWN |
		SOR_LANE_SEQ_CTL_POWER_STATE_UP;
	tegra_sor_ग_लिखोl(sor, value, SOR_LANE_SEQ_CTL);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_LANE_SEQ_CTL);
		अगर ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			अवरोध;

		usleep_range(250, 1000);
	पूर्ण

	अगर ((value & SOR_LANE_SEQ_CTL_TRIGGER) != 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_घातer_करोwn_lanes(काष्ठा tegra_sor *sor)
अणु
	अचिन्हित दीर्घ समयout;
	u32 value;

	/* घातer करोwn all lanes */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~(SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_0 |
		   SOR_DP_PADCTL_PD_TXD_1 | SOR_DP_PADCTL_PD_TXD_2);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	/* start lane sequencer */
	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_UP |
		SOR_LANE_SEQ_CTL_POWER_STATE_DOWN;
	tegra_sor_ग_लिखोl(sor, value, SOR_LANE_SEQ_CTL);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_LANE_SEQ_CTL);
		अगर ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			अवरोध;

		usleep_range(25, 100);
	पूर्ण

	अगर ((value & SOR_LANE_SEQ_CTL_TRIGGER) != 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम tegra_sor_dp_preअक्षरge(काष्ठा tegra_sor *sor, अचिन्हित पूर्णांक lanes)
अणु
	u32 value;

	/* pre-अक्षरge all used lanes */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);

	अगर (lanes <= 2)
		value &= ~(SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[3]) |
			   SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[2]));
	अन्यथा
		value |= SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[3]) |
			 SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[2]);

	अगर (lanes <= 1)
		value &= ~SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[1]);
	अन्यथा
		value |= SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[1]);

	अगर (lanes == 0)
		value &= ~SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[0]);
	अन्यथा
		value |= SOR_DP_PADCTL_CM_TXD(sor->soc->lane_map[0]);

	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	usleep_range(15, 100);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~(SOR_DP_PADCTL_CM_TXD_3 | SOR_DP_PADCTL_CM_TXD_2 |
		   SOR_DP_PADCTL_CM_TXD_1 | SOR_DP_PADCTL_CM_TXD_0);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);
पूर्ण

अटल व्योम tegra_sor_dp_term_calibrate(काष्ठा tegra_sor *sor)
अणु
	u32 mask = 0x08, adj = 0, value;

	/* enable pad calibration logic */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
	value |= SOR_PLL1_TMDS_TERM;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll1);

	जबतक (mask) अणु
		adj |= mask;

		value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
		value &= ~SOR_PLL1_TMDS_TERMADJ_MASK;
		value |= SOR_PLL1_TMDS_TERMADJ(adj);
		tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll1);

		usleep_range(100, 200);

		value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
		अगर (value & SOR_PLL1_TERM_COMPOUT)
			adj &= ~mask;

		mask >>= 1;
	पूर्ण

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
	value &= ~SOR_PLL1_TMDS_TERMADJ_MASK;
	value |= SOR_PLL1_TMDS_TERMADJ(adj);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll1);

	/* disable pad calibration logic */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);
पूर्ण

अटल पूर्णांक tegra_sor_dp_link_apply_training(काष्ठा drm_dp_link *link)
अणु
	काष्ठा tegra_sor *sor = container_of(link, काष्ठा tegra_sor, link);
	u32 voltage_swing = 0, pre_emphasis = 0, post_cursor = 0;
	स्थिर काष्ठा tegra_sor_soc *soc = sor->soc;
	u32 pattern = 0, tx_pu = 0, value;
	अचिन्हित पूर्णांक i;

	क्रम (value = 0, i = 0; i < link->lanes; i++) अणु
		u8 vs = link->train.request.voltage_swing[i];
		u8 pe = link->train.request.pre_emphasis[i];
		u8 pc = link->train.request.post_cursor[i];
		u8 shअगरt = sor->soc->lane_map[i] << 3;

		voltage_swing |= soc->voltage_swing[pc][vs][pe] << shअगरt;
		pre_emphasis |= soc->pre_emphasis[pc][vs][pe] << shअगरt;
		post_cursor |= soc->post_cursor[pc][vs][pe] << shअगरt;

		अगर (sor->soc->tx_pu[pc][vs][pe] > tx_pu)
			tx_pu = sor->soc->tx_pu[pc][vs][pe];

		चयन (link->train.pattern) अणु
		हाल DP_TRAINING_PATTERN_DISABLE:
			value = SOR_DP_TPG_SCRAMBLER_GALIOS |
				SOR_DP_TPG_PATTERN_NONE;
			अवरोध;

		हाल DP_TRAINING_PATTERN_1:
			value = SOR_DP_TPG_SCRAMBLER_NONE |
				SOR_DP_TPG_PATTERN_TRAIN1;
			अवरोध;

		हाल DP_TRAINING_PATTERN_2:
			value = SOR_DP_TPG_SCRAMBLER_NONE |
				SOR_DP_TPG_PATTERN_TRAIN2;
			अवरोध;

		हाल DP_TRAINING_PATTERN_3:
			value = SOR_DP_TPG_SCRAMBLER_NONE |
				SOR_DP_TPG_PATTERN_TRAIN3;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (link->caps.channel_coding)
			value |= SOR_DP_TPG_CHANNEL_CODING;

		pattern = pattern << 8 | value;
	पूर्ण

	tegra_sor_ग_लिखोl(sor, voltage_swing, SOR_LANE_DRIVE_CURRENT0);
	tegra_sor_ग_लिखोl(sor, pre_emphasis, SOR_LANE_PREEMPHASIS0);

	अगर (link->caps.tps3_supported)
		tegra_sor_ग_लिखोl(sor, post_cursor, SOR_LANE_POSTCURSOR0);

	tegra_sor_ग_लिखोl(sor, pattern, SOR_DP_TPG);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_TX_PU_MASK;
	value |= SOR_DP_PADCTL_TX_PU_ENABLE;
	value |= SOR_DP_PADCTL_TX_PU(tx_pu);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	usleep_range(20, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_dp_link_configure(काष्ठा drm_dp_link *link)
अणु
	काष्ठा tegra_sor *sor = container_of(link, काष्ठा tegra_sor, link);
	अचिन्हित पूर्णांक rate, lanes;
	u32 value;
	पूर्णांक err;

	rate = drm_dp_link_rate_to_bw_code(link->rate);
	lanes = link->lanes;

	/* configure link speed and lane count */
	value = tegra_sor_पढ़ोl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value |= SOR_CLK_CNTRL_DP_LINK_SPEED(rate);
	tegra_sor_ग_लिखोl(sor, value, SOR_CLK_CNTRL);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_LANE_COUNT_MASK;
	value |= SOR_DP_LINKCTL_LANE_COUNT(lanes);

	अगर (link->caps.enhanced_framing)
		value |= SOR_DP_LINKCTL_ENHANCED_FRAME;

	tegra_sor_ग_लिखोl(sor, value, SOR_DP_LINKCTL0);

	usleep_range(400, 1000);

	/* configure load pulse position adjusपंचांगent */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
	value &= ~SOR_PLL1_LOADADJ_MASK;

	चयन (rate) अणु
	हाल DP_LINK_BW_1_62:
		value |= SOR_PLL1_LOADADJ(0x3);
		अवरोध;

	हाल DP_LINK_BW_2_7:
		value |= SOR_PLL1_LOADADJ(0x4);
		अवरोध;

	हाल DP_LINK_BW_5_4:
		value |= SOR_PLL1_LOADADJ(0x6);
		अवरोध;
	पूर्ण

	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll1);

	/* use alternate scrambler reset क्रम eDP */
	value = tegra_sor_पढ़ोl(sor, SOR_DP_SPARE0);

	अगर (link->edp == 0)
		value &= ~SOR_DP_SPARE_PANEL_INTERNAL;
	अन्यथा
		value |= SOR_DP_SPARE_PANEL_INTERNAL;

	tegra_sor_ग_लिखोl(sor, value, SOR_DP_SPARE0);

	err = tegra_sor_घातer_करोwn_lanes(sor);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to power down lanes: %d\n", err);
		वापस err;
	पूर्ण

	/* घातer up and pre-अक्षरge lanes */
	err = tegra_sor_घातer_up_lanes(sor, lanes);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to power up %u lane%s: %d\n",
			lanes, (lanes != 1) ? "s" : "", err);
		वापस err;
	पूर्ण

	tegra_sor_dp_preअक्षरge(sor, lanes);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_dp_link_ops tegra_sor_dp_link_ops = अणु
	.apply_training = tegra_sor_dp_link_apply_training,
	.configure = tegra_sor_dp_link_configure,
पूर्ण;

अटल व्योम tegra_sor_super_update(काष्ठा tegra_sor *sor)
अणु
	tegra_sor_ग_लिखोl(sor, 0, SOR_SUPER_STATE0);
	tegra_sor_ग_लिखोl(sor, 1, SOR_SUPER_STATE0);
	tegra_sor_ग_लिखोl(sor, 0, SOR_SUPER_STATE0);
पूर्ण

अटल व्योम tegra_sor_update(काष्ठा tegra_sor *sor)
अणु
	tegra_sor_ग_लिखोl(sor, 0, SOR_STATE0);
	tegra_sor_ग_लिखोl(sor, 1, SOR_STATE0);
	tegra_sor_ग_लिखोl(sor, 0, SOR_STATE0);
पूर्ण

अटल पूर्णांक tegra_sor_setup_pwm(काष्ठा tegra_sor *sor, अचिन्हित दीर्घ समयout)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_PWM_DIV);
	value &= ~SOR_PWM_DIV_MASK;
	value |= 0x400; /* period */
	tegra_sor_ग_लिखोl(sor, value, SOR_PWM_DIV);

	value = tegra_sor_पढ़ोl(sor, SOR_PWM_CTL);
	value &= ~SOR_PWM_CTL_DUTY_CYCLE_MASK;
	value |= 0x400; /* duty cycle */
	value &= ~SOR_PWM_CTL_CLK_SEL; /* घड़ी source: PCLK */
	value |= SOR_PWM_CTL_TRIGGER;
	tegra_sor_ग_लिखोl(sor, value, SOR_PWM_CTL);

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_PWM_CTL);
		अगर ((value & SOR_PWM_CTL_TRIGGER) == 0)
			वापस 0;

		usleep_range(25, 100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_sor_attach(काष्ठा tegra_sor *sor)
अणु
	अचिन्हित दीर्घ value, समयout;

	/* wake up in normal mode */
	value = tegra_sor_पढ़ोl(sor, SOR_SUPER_STATE1);
	value |= SOR_SUPER_STATE_HEAD_MODE_AWAKE;
	value |= SOR_SUPER_STATE_MODE_NORMAL;
	tegra_sor_ग_लिखोl(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	/* attach */
	value = tegra_sor_पढ़ोl(sor, SOR_SUPER_STATE1);
	value |= SOR_SUPER_STATE_ATTACHED;
	tegra_sor_ग_लिखोl(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_TEST);
		अगर ((value & SOR_TEST_ATTACHED) != 0)
			वापस 0;

		usleep_range(25, 100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_sor_wakeup(काष्ठा tegra_sor *sor)
अणु
	अचिन्हित दीर्घ value, समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	/* रुको क्रम head to wake up */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_TEST);
		value &= SOR_TEST_HEAD_MODE_MASK;

		अगर (value == SOR_TEST_HEAD_MODE_AWAKE)
			वापस 0;

		usleep_range(25, 100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_sor_घातer_up(काष्ठा tegra_sor *sor, अचिन्हित दीर्घ समयout)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_PWR);
	value |= SOR_PWR_TRIGGER | SOR_PWR_NORMAL_STATE_PU;
	tegra_sor_ग_लिखोl(sor, value, SOR_PWR);

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_PWR);
		अगर ((value & SOR_PWR_TRIGGER) == 0)
			वापस 0;

		usleep_range(25, 100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

काष्ठा tegra_sor_params अणु
	/* number of link घड़ीs per line */
	अचिन्हित पूर्णांक num_घड़ीs;
	/* ratio between input and output */
	u64 ratio;
	/* precision factor */
	u64 precision;

	अचिन्हित पूर्णांक active_polarity;
	अचिन्हित पूर्णांक active_count;
	अचिन्हित पूर्णांक active_frac;
	अचिन्हित पूर्णांक tu_size;
	अचिन्हित पूर्णांक error;
पूर्ण;

अटल पूर्णांक tegra_sor_compute_params(काष्ठा tegra_sor *sor,
				    काष्ठा tegra_sor_params *params,
				    अचिन्हित पूर्णांक tu_size)
अणु
	u64 active_sym, active_count, frac, approx;
	u32 active_polarity, active_frac = 0;
	स्थिर u64 f = params->precision;
	s64 error;

	active_sym = params->ratio * tu_size;
	active_count = भाग_u64(active_sym, f) * f;
	frac = active_sym - active_count;

	/* fraction < 0.5 */
	अगर (frac >= (f / 2)) अणु
		active_polarity = 1;
		frac = f - frac;
	पूर्ण अन्यथा अणु
		active_polarity = 0;
	पूर्ण

	अगर (frac != 0) अणु
		frac = भाग_u64(f * f,  frac); /* 1/fraction */
		अगर (frac <= (15 * f)) अणु
			active_frac = भाग_u64(frac, f);

			/* round up */
			अगर (active_polarity)
				active_frac++;
		पूर्ण अन्यथा अणु
			active_frac = active_polarity ? 1 : 15;
		पूर्ण
	पूर्ण

	अगर (active_frac == 1)
		active_polarity = 0;

	अगर (active_polarity == 1) अणु
		अगर (active_frac) अणु
			approx = active_count + (active_frac * (f - 1)) * f;
			approx = भाग_u64(approx, active_frac * f);
		पूर्ण अन्यथा अणु
			approx = active_count + f;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (active_frac)
			approx = active_count + भाग_u64(f, active_frac);
		अन्यथा
			approx = active_count;
	पूर्ण

	error = भाग_s64(active_sym - approx, tu_size);
	error *= params->num_घड़ीs;

	अगर (error <= 0 && असल(error) < params->error) अणु
		params->active_count = भाग_u64(active_count, f);
		params->active_polarity = active_polarity;
		params->active_frac = active_frac;
		params->error = असल(error);
		params->tu_size = tu_size;

		अगर (error == 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tegra_sor_compute_config(काष्ठा tegra_sor *sor,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा tegra_sor_config *config,
				    काष्ठा drm_dp_link *link)
अणु
	स्थिर u64 f = 100000, link_rate = link->rate * 1000;
	स्थिर u64 pclk = mode->घड़ी * 1000;
	u64 input, output, watermark, num;
	काष्ठा tegra_sor_params params;
	u32 num_syms_per_line;
	अचिन्हित पूर्णांक i;

	अगर (!link_rate || !link->lanes || !pclk || !config->bits_per_pixel)
		वापस -EINVAL;

	input = pclk * config->bits_per_pixel;
	output = link_rate * 8 * link->lanes;

	अगर (input >= output)
		वापस -दुस्फल;

	स_रखो(&params, 0, माप(params));
	params.ratio = भाग64_u64(input * f, output);
	params.num_घड़ीs = भाग_u64(link_rate * mode->hdisplay, pclk);
	params.precision = f;
	params.error = 64 * f;
	params.tu_size = 64;

	क्रम (i = params.tu_size; i >= 32; i--)
		अगर (tegra_sor_compute_params(sor, &params, i))
			अवरोध;

	अगर (params.active_frac == 0) अणु
		config->active_polarity = 0;
		config->active_count = params.active_count;

		अगर (!params.active_polarity)
			config->active_count--;

		config->tu_size = params.tu_size;
		config->active_frac = 1;
	पूर्ण अन्यथा अणु
		config->active_polarity = params.active_polarity;
		config->active_count = params.active_count;
		config->active_frac = params.active_frac;
		config->tu_size = params.tu_size;
	पूर्ण

	dev_dbg(sor->dev,
		"polarity: %d active count: %d tu size: %d active frac: %d\n",
		config->active_polarity, config->active_count,
		config->tu_size, config->active_frac);

	watermark = params.ratio * config->tu_size * (f - params.ratio);
	watermark = भाग_u64(watermark, f);

	watermark = भाग_u64(watermark + params.error, f);
	config->watermark = watermark + (config->bits_per_pixel / 8) + 2;
	num_syms_per_line = (mode->hdisplay * config->bits_per_pixel) *
			    (link->lanes * 8);

	अगर (config->watermark > 30) अणु
		config->watermark = 30;
		dev_err(sor->dev,
			"unable to compute TU size, forcing watermark to %u\n",
			config->watermark);
	पूर्ण अन्यथा अगर (config->watermark > num_syms_per_line) अणु
		config->watermark = num_syms_per_line;
		dev_err(sor->dev, "watermark too high, forcing to %u\n",
			config->watermark);
	पूर्ण

	/* compute the number of symbols per horizontal blanking पूर्णांकerval */
	num = ((mode->htotal - mode->hdisplay) - 7) * link_rate;
	config->hblank_symbols = भाग_u64(num, pclk);

	अगर (link->caps.enhanced_framing)
		config->hblank_symbols -= 3;

	config->hblank_symbols -= 12 / link->lanes;

	/* compute the number of symbols per vertical blanking पूर्णांकerval */
	num = (mode->hdisplay - 25) * link_rate;
	config->vblank_symbols = भाग_u64(num, pclk);
	config->vblank_symbols -= 36 / link->lanes + 4;

	dev_dbg(sor->dev, "blank symbols: H:%u V:%u\n", config->hblank_symbols,
		config->vblank_symbols);

	वापस 0;
पूर्ण

अटल व्योम tegra_sor_apply_config(काष्ठा tegra_sor *sor,
				   स्थिर काष्ठा tegra_sor_config *config)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_TU_SIZE_MASK;
	value |= SOR_DP_LINKCTL_TU_SIZE(config->tu_size);
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_LINKCTL0);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_CONFIG0);
	value &= ~SOR_DP_CONFIG_WATERMARK_MASK;
	value |= SOR_DP_CONFIG_WATERMARK(config->watermark);

	value &= ~SOR_DP_CONFIG_ACTIVE_SYM_COUNT_MASK;
	value |= SOR_DP_CONFIG_ACTIVE_SYM_COUNT(config->active_count);

	value &= ~SOR_DP_CONFIG_ACTIVE_SYM_FRAC_MASK;
	value |= SOR_DP_CONFIG_ACTIVE_SYM_FRAC(config->active_frac);

	अगर (config->active_polarity)
		value |= SOR_DP_CONFIG_ACTIVE_SYM_POLARITY;
	अन्यथा
		value &= ~SOR_DP_CONFIG_ACTIVE_SYM_POLARITY;

	value |= SOR_DP_CONFIG_ACTIVE_SYM_ENABLE;
	value |= SOR_DP_CONFIG_DISPARITY_NEGATIVE;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_CONFIG0);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_AUDIO_HBLANK_SYMBOLS);
	value &= ~SOR_DP_AUDIO_HBLANK_SYMBOLS_MASK;
	value |= config->hblank_symbols & 0xffff;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_AUDIO_HBLANK_SYMBOLS);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_AUDIO_VBLANK_SYMBOLS);
	value &= ~SOR_DP_AUDIO_VBLANK_SYMBOLS_MASK;
	value |= config->vblank_symbols & 0xffff;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_AUDIO_VBLANK_SYMBOLS);
पूर्ण

अटल व्योम tegra_sor_mode_set(काष्ठा tegra_sor *sor,
			       स्थिर काष्ठा drm_display_mode *mode,
			       काष्ठा tegra_sor_state *state)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(sor->output.encoder.crtc);
	अचिन्हित पूर्णांक vbe, vse, hbe, hse, vbs, hbs;
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PIXELDEPTH_MASK;
	value &= ~SOR_STATE_ASY_CRC_MODE_MASK;
	value &= ~SOR_STATE_ASY_OWNER_MASK;

	value |= SOR_STATE_ASY_CRC_MODE_COMPLETE |
		 SOR_STATE_ASY_OWNER(dc->pipe + 1);

	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		value &= ~SOR_STATE_ASY_HSYNCPOL;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		value |= SOR_STATE_ASY_HSYNCPOL;

	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		value &= ~SOR_STATE_ASY_VSYNCPOL;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		value |= SOR_STATE_ASY_VSYNCPOL;

	चयन (state->bpc) अणु
	हाल 16:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_48_444;
		अवरोध;

	हाल 12:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_36_444;
		अवरोध;

	हाल 10:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_30_444;
		अवरोध;

	हाल 8:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_24_444;
		अवरोध;

	हाल 6:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_18_444;
		अवरोध;

	शेष:
		value |= SOR_STATE_ASY_PIXELDEPTH_BPP_24_444;
		अवरोध;
	पूर्ण

	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);

	/*
	 * TODO: The video timing programming below करोesn't seem to match the
	 * रेजिस्टर definitions.
	 */

	value = ((mode->vtotal & 0x7fff) << 16) | (mode->htotal & 0x7fff);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state1 + dc->pipe);

	/* sync end = sync width - 1 */
	vse = mode->vsync_end - mode->vsync_start - 1;
	hse = mode->hsync_end - mode->hsync_start - 1;

	value = ((vse & 0x7fff) << 16) | (hse & 0x7fff);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state2 + dc->pipe);

	/* blank end = sync end + back porch */
	vbe = vse + (mode->vtotal - mode->vsync_end);
	hbe = hse + (mode->htotal - mode->hsync_end);

	value = ((vbe & 0x7fff) << 16) | (hbe & 0x7fff);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state3 + dc->pipe);

	/* blank start = blank end + active */
	vbs = vbe + mode->vdisplay;
	hbs = hbe + mode->hdisplay;

	value = ((vbs & 0x7fff) << 16) | (hbs & 0x7fff);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state4 + dc->pipe);

	/* XXX पूर्णांकerlacing support */
	tegra_sor_ग_लिखोl(sor, 0x001, sor->soc->regs->head_state5 + dc->pipe);
पूर्ण

अटल पूर्णांक tegra_sor_detach(काष्ठा tegra_sor *sor)
अणु
	अचिन्हित दीर्घ value, समयout;

	/* चयन to safe mode */
	value = tegra_sor_पढ़ोl(sor, SOR_SUPER_STATE1);
	value &= ~SOR_SUPER_STATE_MODE_NORMAL;
	tegra_sor_ग_लिखोl(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_PWR);
		अगर (value & SOR_PWR_MODE_SAFE)
			अवरोध;
	पूर्ण

	अगर ((value & SOR_PWR_MODE_SAFE) == 0)
		वापस -ETIMEDOUT;

	/* go to sleep */
	value = tegra_sor_पढ़ोl(sor, SOR_SUPER_STATE1);
	value &= ~SOR_SUPER_STATE_HEAD_MODE_MASK;
	tegra_sor_ग_लिखोl(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	/* detach */
	value = tegra_sor_पढ़ोl(sor, SOR_SUPER_STATE1);
	value &= ~SOR_SUPER_STATE_ATTACHED;
	tegra_sor_ग_लिखोl(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_TEST);
		अगर ((value & SOR_TEST_ATTACHED) == 0)
			अवरोध;

		usleep_range(25, 100);
	पूर्ण

	अगर ((value & SOR_TEST_ATTACHED) != 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_घातer_करोwn(काष्ठा tegra_sor *sor)
अणु
	अचिन्हित दीर्घ value, समयout;
	पूर्णांक err;

	value = tegra_sor_पढ़ोl(sor, SOR_PWR);
	value &= ~SOR_PWR_NORMAL_STATE_PU;
	value |= SOR_PWR_TRIGGER;
	tegra_sor_ग_लिखोl(sor, value, SOR_PWR);

	समयout = jअगरfies + msecs_to_jअगरfies(250);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_PWR);
		अगर ((value & SOR_PWR_TRIGGER) == 0)
			वापस 0;

		usleep_range(25, 100);
	पूर्ण

	अगर ((value & SOR_PWR_TRIGGER) != 0)
		वापस -ETIMEDOUT;

	/* चयन to safe parent घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_safe);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);
		वापस err;
	पूर्ण

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll0);
	value |= SOR_PLL0_VCOPD | SOR_PLL0_PWR;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_SEQ_PLLCAPPD;
	value |= SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_crc_रुको(काष्ठा tegra_sor *sor, अचिन्हित दीर्घ समयout)
अणु
	u32 value;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_CRCA);
		अगर (value & SOR_CRCA_VALID)
			वापस 0;

		usleep_range(100, 200);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_sor_show_crc(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_sor *sor = node->info_ent->data;
	काष्ठा drm_crtc *crtc = sor->output.encoder.crtc;
	काष्ठा drm_device *drm = node->minor->dev;
	पूर्णांक err = 0;
	u32 value;

	drm_modeset_lock_all(drm);

	अगर (!crtc || !crtc->state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_CRC_MODE_MASK;
	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);

	value = tegra_sor_पढ़ोl(sor, SOR_CRC_CNTRL);
	value |= SOR_CRC_CNTRL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_CRC_CNTRL);

	value = tegra_sor_पढ़ोl(sor, SOR_TEST);
	value &= ~SOR_TEST_CRC_POST_SERIALIZE;
	tegra_sor_ग_लिखोl(sor, value, SOR_TEST);

	err = tegra_sor_crc_रुको(sor, 100);
	अगर (err < 0)
		जाओ unlock;

	tegra_sor_ग_लिखोl(sor, SOR_CRCA_RESET, SOR_CRCA);
	value = tegra_sor_पढ़ोl(sor, SOR_CRCB);

	seq_म_लिखो(s, "%08x\n", value);

unlock:
	drm_modeset_unlock_all(drm);
	वापस err;
पूर्ण

#घोषणा DEBUGFS_REG32(_name) अणु .name = #_name, .offset = _name पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 tegra_sor_regs[] = अणु
	DEBUGFS_REG32(SOR_CTXSW),
	DEBUGFS_REG32(SOR_SUPER_STATE0),
	DEBUGFS_REG32(SOR_SUPER_STATE1),
	DEBUGFS_REG32(SOR_STATE0),
	DEBUGFS_REG32(SOR_STATE1),
	DEBUGFS_REG32(SOR_HEAD_STATE0(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE0(1)),
	DEBUGFS_REG32(SOR_HEAD_STATE1(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE1(1)),
	DEBUGFS_REG32(SOR_HEAD_STATE2(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE2(1)),
	DEBUGFS_REG32(SOR_HEAD_STATE3(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE3(1)),
	DEBUGFS_REG32(SOR_HEAD_STATE4(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE4(1)),
	DEBUGFS_REG32(SOR_HEAD_STATE5(0)),
	DEBUGFS_REG32(SOR_HEAD_STATE5(1)),
	DEBUGFS_REG32(SOR_CRC_CNTRL),
	DEBUGFS_REG32(SOR_DP_DEBUG_MVID),
	DEBUGFS_REG32(SOR_CLK_CNTRL),
	DEBUGFS_REG32(SOR_CAP),
	DEBUGFS_REG32(SOR_PWR),
	DEBUGFS_REG32(SOR_TEST),
	DEBUGFS_REG32(SOR_PLL0),
	DEBUGFS_REG32(SOR_PLL1),
	DEBUGFS_REG32(SOR_PLL2),
	DEBUGFS_REG32(SOR_PLL3),
	DEBUGFS_REG32(SOR_CSTM),
	DEBUGFS_REG32(SOR_LVDS),
	DEBUGFS_REG32(SOR_CRCA),
	DEBUGFS_REG32(SOR_CRCB),
	DEBUGFS_REG32(SOR_BLANK),
	DEBUGFS_REG32(SOR_SEQ_CTL),
	DEBUGFS_REG32(SOR_LANE_SEQ_CTL),
	DEBUGFS_REG32(SOR_SEQ_INST(0)),
	DEBUGFS_REG32(SOR_SEQ_INST(1)),
	DEBUGFS_REG32(SOR_SEQ_INST(2)),
	DEBUGFS_REG32(SOR_SEQ_INST(3)),
	DEBUGFS_REG32(SOR_SEQ_INST(4)),
	DEBUGFS_REG32(SOR_SEQ_INST(5)),
	DEBUGFS_REG32(SOR_SEQ_INST(6)),
	DEBUGFS_REG32(SOR_SEQ_INST(7)),
	DEBUGFS_REG32(SOR_SEQ_INST(8)),
	DEBUGFS_REG32(SOR_SEQ_INST(9)),
	DEBUGFS_REG32(SOR_SEQ_INST(10)),
	DEBUGFS_REG32(SOR_SEQ_INST(11)),
	DEBUGFS_REG32(SOR_SEQ_INST(12)),
	DEBUGFS_REG32(SOR_SEQ_INST(13)),
	DEBUGFS_REG32(SOR_SEQ_INST(14)),
	DEBUGFS_REG32(SOR_SEQ_INST(15)),
	DEBUGFS_REG32(SOR_PWM_DIV),
	DEBUGFS_REG32(SOR_PWM_CTL),
	DEBUGFS_REG32(SOR_VCRC_A0),
	DEBUGFS_REG32(SOR_VCRC_A1),
	DEBUGFS_REG32(SOR_VCRC_B0),
	DEBUGFS_REG32(SOR_VCRC_B1),
	DEBUGFS_REG32(SOR_CCRC_A0),
	DEBUGFS_REG32(SOR_CCRC_A1),
	DEBUGFS_REG32(SOR_CCRC_B0),
	DEBUGFS_REG32(SOR_CCRC_B1),
	DEBUGFS_REG32(SOR_EDATA_A0),
	DEBUGFS_REG32(SOR_EDATA_A1),
	DEBUGFS_REG32(SOR_EDATA_B0),
	DEBUGFS_REG32(SOR_EDATA_B1),
	DEBUGFS_REG32(SOR_COUNT_A0),
	DEBUGFS_REG32(SOR_COUNT_A1),
	DEBUGFS_REG32(SOR_COUNT_B0),
	DEBUGFS_REG32(SOR_COUNT_B1),
	DEBUGFS_REG32(SOR_DEBUG_A0),
	DEBUGFS_REG32(SOR_DEBUG_A1),
	DEBUGFS_REG32(SOR_DEBUG_B0),
	DEBUGFS_REG32(SOR_DEBUG_B1),
	DEBUGFS_REG32(SOR_TRIG),
	DEBUGFS_REG32(SOR_MSCHECK),
	DEBUGFS_REG32(SOR_XBAR_CTRL),
	DEBUGFS_REG32(SOR_XBAR_POL),
	DEBUGFS_REG32(SOR_DP_LINKCTL0),
	DEBUGFS_REG32(SOR_DP_LINKCTL1),
	DEBUGFS_REG32(SOR_LANE_DRIVE_CURRENT0),
	DEBUGFS_REG32(SOR_LANE_DRIVE_CURRENT1),
	DEBUGFS_REG32(SOR_LANE4_DRIVE_CURRENT0),
	DEBUGFS_REG32(SOR_LANE4_DRIVE_CURRENT1),
	DEBUGFS_REG32(SOR_LANE_PREEMPHASIS0),
	DEBUGFS_REG32(SOR_LANE_PREEMPHASIS1),
	DEBUGFS_REG32(SOR_LANE4_PREEMPHASIS0),
	DEBUGFS_REG32(SOR_LANE4_PREEMPHASIS1),
	DEBUGFS_REG32(SOR_LANE_POSTCURSOR0),
	DEBUGFS_REG32(SOR_LANE_POSTCURSOR1),
	DEBUGFS_REG32(SOR_DP_CONFIG0),
	DEBUGFS_REG32(SOR_DP_CONFIG1),
	DEBUGFS_REG32(SOR_DP_MN0),
	DEBUGFS_REG32(SOR_DP_MN1),
	DEBUGFS_REG32(SOR_DP_PADCTL0),
	DEBUGFS_REG32(SOR_DP_PADCTL1),
	DEBUGFS_REG32(SOR_DP_PADCTL2),
	DEBUGFS_REG32(SOR_DP_DEBUG0),
	DEBUGFS_REG32(SOR_DP_DEBUG1),
	DEBUGFS_REG32(SOR_DP_SPARE0),
	DEBUGFS_REG32(SOR_DP_SPARE1),
	DEBUGFS_REG32(SOR_DP_AUDIO_CTRL),
	DEBUGFS_REG32(SOR_DP_AUDIO_HBLANK_SYMBOLS),
	DEBUGFS_REG32(SOR_DP_AUDIO_VBLANK_SYMBOLS),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_HEADER),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK0),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK1),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK2),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK3),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK4),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK5),
	DEBUGFS_REG32(SOR_DP_GENERIC_INFOFRAME_SUBPACK6),
	DEBUGFS_REG32(SOR_DP_TPG),
	DEBUGFS_REG32(SOR_DP_TPG_CONFIG),
	DEBUGFS_REG32(SOR_DP_LQ_CSTM0),
	DEBUGFS_REG32(SOR_DP_LQ_CSTM1),
	DEBUGFS_REG32(SOR_DP_LQ_CSTM2),
पूर्ण;

अटल पूर्णांक tegra_sor_show_regs(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_sor *sor = node->info_ent->data;
	काष्ठा drm_crtc *crtc = sor->output.encoder.crtc;
	काष्ठा drm_device *drm = node->minor->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	drm_modeset_lock_all(drm);

	अगर (!crtc || !crtc->state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tegra_sor_regs); i++) अणु
		अचिन्हित पूर्णांक offset = tegra_sor_regs[i].offset;

		seq_म_लिखो(s, "%-38s %#05x %08x\n", tegra_sor_regs[i].name,
			   offset, tegra_sor_पढ़ोl(sor, offset));
	पूर्ण

unlock:
	drm_modeset_unlock_all(drm);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_info_list debugfs_files[] = अणु
	अणु "crc", tegra_sor_show_crc, 0, शून्य पूर्ण,
	अणु "regs", tegra_sor_show_regs, 0, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_sor_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	अचिन्हित पूर्णांक i, count = ARRAY_SIZE(debugfs_files);
	काष्ठा drm_minor *minor = connector->dev->primary;
	काष्ठा dentry *root = connector->debugfs_entry;
	काष्ठा tegra_sor *sor = to_sor(output);

	sor->debugfs_files = kmemdup(debugfs_files, माप(debugfs_files),
				     GFP_KERNEL);
	अगर (!sor->debugfs_files)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++)
		sor->debugfs_files[i].data = sor;

	drm_debugfs_create_files(sor->debugfs_files, count, root, minor);

	वापस 0;
पूर्ण

अटल व्योम tegra_sor_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	अचिन्हित पूर्णांक count = ARRAY_SIZE(debugfs_files);
	काष्ठा tegra_sor *sor = to_sor(output);

	drm_debugfs_हटाओ_files(sor->debugfs_files, count,
				 connector->dev->primary);
	kमुक्त(sor->debugfs_files);
	sor->debugfs_files = शून्य;
पूर्ण

अटल व्योम tegra_sor_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_sor_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस;

	अगर (connector->state) अणु
		__drm_atomic_helper_connector_destroy_state(connector->state);
		kमुक्त(connector->state);
	पूर्ण

	__drm_atomic_helper_connector_reset(connector, &state->base);
पूर्ण

अटल क्रमागत drm_connector_status
tegra_sor_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा tegra_sor *sor = to_sor(output);

	अगर (sor->aux)
		वापस drm_dp_aux_detect(sor->aux);

	वापस tegra_output_connector_detect(connector, क्रमce);
पूर्ण

अटल काष्ठा drm_connector_state *
tegra_sor_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_sor_state *state = to_sor_state(connector->state);
	काष्ठा tegra_sor_state *copy;

	copy = kmemdup(state, माप(*state), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &copy->base);

	वापस &copy->base;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tegra_sor_connector_funcs = अणु
	.reset = tegra_sor_connector_reset,
	.detect = tegra_sor_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = tegra_output_connector_destroy,
	.atomic_duplicate_state = tegra_sor_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = tegra_sor_late_रेजिस्टर,
	.early_unरेजिस्टर = tegra_sor_early_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक tegra_sor_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा tegra_sor *sor = to_sor(output);
	पूर्णांक err;

	अगर (sor->aux)
		drm_dp_aux_enable(sor->aux);

	err = tegra_output_connector_get_modes(connector);

	अगर (sor->aux)
		drm_dp_aux_disable(sor->aux);

	वापस err;
पूर्ण

अटल क्रमागत drm_mode_status
tegra_sor_connector_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs tegra_sor_connector_helper_funcs = अणु
	.get_modes = tegra_sor_connector_get_modes,
	.mode_valid = tegra_sor_connector_mode_valid,
पूर्ण;

अटल पूर्णांक
tegra_sor_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_sor_state *state = to_sor_state(conn_state);
	काष्ठा tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	अचिन्हित दीर्घ pclk = crtc_state->mode.घड़ी * 1000;
	काष्ठा tegra_sor *sor = to_sor(output);
	काष्ठा drm_display_info *info;
	पूर्णांक err;

	info = &output->connector.display_info;

	/*
	 * For HBR2 modes, the SOR brick needs to use the x20 multiplier, so
	 * the pixel घड़ी must be corrected accordingly.
	 */
	अगर (pclk >= 340000000) अणु
		state->link_speed = 20;
		state->pclk = pclk / 2;
	पूर्ण अन्यथा अणु
		state->link_speed = 10;
		state->pclk = pclk;
	पूर्ण

	err = tegra_dc_state_setup_घड़ी(dc, crtc_state, sor->clk_parent,
					 pclk, 0);
	अगर (err < 0) अणु
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		वापस err;
	पूर्ण

	चयन (info->bpc) अणु
	हाल 8:
	हाल 6:
		state->bpc = info->bpc;
		अवरोध;

	शेष:
		DRM_DEBUG_KMS("%u bits-per-color not supported\n", info->bpc);
		state->bpc = 8;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 tegra_sor_hdmi_subpack(स्थिर u8 *ptr, माप_प्रकार size)
अणु
	u32 value = 0;
	माप_प्रकार i;

	क्रम (i = size; i > 0; i--)
		value = (value << 8) | ptr[i - 1];

	वापस value;
पूर्ण

अटल व्योम tegra_sor_hdmi_ग_लिखो_infopack(काष्ठा tegra_sor *sor,
					  स्थिर व्योम *data, माप_प्रकार size)
अणु
	स्थिर u8 *ptr = data;
	अचिन्हित दीर्घ offset;
	माप_प्रकार i, j;
	u32 value;

	चयन (ptr[0]) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		offset = SOR_HDMI_AVI_INFOFRAME_HEADER;
		अवरोध;

	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		offset = SOR_HDMI_AUDIO_INFOFRAME_HEADER;
		अवरोध;

	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		offset = SOR_HDMI_VSI_INFOFRAME_HEADER;
		अवरोध;

	शेष:
		dev_err(sor->dev, "unsupported infoframe type: %02x\n",
			ptr[0]);
		वापस;
	पूर्ण

	value = INFOFRAME_HEADER_TYPE(ptr[0]) |
		INFOFRAME_HEADER_VERSION(ptr[1]) |
		INFOFRAME_HEADER_LEN(ptr[2]);
	tegra_sor_ग_लिखोl(sor, value, offset);
	offset++;

	/*
	 * Each subpack contains 7 bytes, भागided पूर्णांकo:
	 * - subpack_low: bytes 0 - 3
	 * - subpack_high: bytes 4 - 6 (with byte 7 padded to 0x00)
	 */
	क्रम (i = 3, j = 0; i < size; i += 7, j += 8) अणु
		माप_प्रकार rem = size - i, num = min_t(माप_प्रकार, rem, 4);

		value = tegra_sor_hdmi_subpack(&ptr[i], num);
		tegra_sor_ग_लिखोl(sor, value, offset++);

		num = min_t(माप_प्रकार, rem - num, 3);

		value = tegra_sor_hdmi_subpack(&ptr[i + 4], num);
		tegra_sor_ग_लिखोl(sor, value, offset++);
	पूर्ण
पूर्ण

अटल पूर्णांक
tegra_sor_hdmi_setup_avi_infoframe(काष्ठा tegra_sor *sor,
				   स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];
	काष्ठा hdmi_avi_infoframe frame;
	u32 value;
	पूर्णांक err;

	/* disable AVI infoframe */
	value = tegra_sor_पढ़ोl(sor, SOR_HDMI_AVI_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_SINGLE;
	value &= ~INFOFRAME_CTRL_OTHER;
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AVI_INFOFRAME_CTRL);

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &sor->output.connector, mode);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to setup AVI infoframe: %d\n", err);
		वापस err;
	पूर्ण

	err = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to pack AVI infoframe: %d\n", err);
		वापस err;
	पूर्ण

	tegra_sor_hdmi_ग_लिखो_infopack(sor, buffer, err);

	/* enable AVI infoframe */
	value = tegra_sor_पढ़ोl(sor, SOR_HDMI_AVI_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_CHECKSUM_ENABLE;
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AVI_INFOFRAME_CTRL);

	वापस 0;
पूर्ण

अटल व्योम tegra_sor_ग_लिखो_eld(काष्ठा tegra_sor *sor)
अणु
	माप_प्रकार length = drm_eld_size(sor->output.connector.eld), i;

	क्रम (i = 0; i < length; i++)
		tegra_sor_ग_लिखोl(sor, i << 8 | sor->output.connector.eld[i],
				 SOR_AUDIO_HDA_ELD_BUFWR);

	/*
	 * The HDA codec will always report an ELD buffer size of 96 bytes and
	 * the HDA codec driver will check that each byte पढ़ो from the buffer
	 * is valid. Thereक्रमe every byte must be written, even अगर no 96 bytes
	 * were parsed from EDID.
	 */
	क्रम (i = length; i < 96; i++)
		tegra_sor_ग_लिखोl(sor, i << 8 | 0, SOR_AUDIO_HDA_ELD_BUFWR);
पूर्ण

अटल व्योम tegra_sor_audio_prepare(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	/*
	 * Enable and unmask the HDA codec SCRATCH0 रेजिस्टर पूर्णांकerrupt. This
	 * is used क्रम पूर्णांकeroperability between the HDA codec driver and the
	 * HDMI/DP driver.
	 */
	value = SOR_INT_CODEC_SCRATCH1 | SOR_INT_CODEC_SCRATCH0;
	tegra_sor_ग_लिखोl(sor, value, SOR_INT_ENABLE);
	tegra_sor_ग_लिखोl(sor, value, SOR_INT_MASK);

	tegra_sor_ग_लिखो_eld(sor);

	value = SOR_AUDIO_HDA_PRESENSE_ELDV | SOR_AUDIO_HDA_PRESENSE_PD;
	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_HDA_PRESENSE);
पूर्ण

अटल व्योम tegra_sor_audio_unprepare(काष्ठा tegra_sor *sor)
अणु
	tegra_sor_ग_लिखोl(sor, 0, SOR_AUDIO_HDA_PRESENSE);
	tegra_sor_ग_लिखोl(sor, 0, SOR_INT_MASK);
	tegra_sor_ग_लिखोl(sor, 0, SOR_INT_ENABLE);
पूर्ण

अटल व्योम tegra_sor_audio_enable(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_AUDIO_CNTRL);

	/* select HDA audio input */
	value &= ~SOR_AUDIO_CNTRL_SOURCE_SELECT(SOURCE_SELECT_MASK);
	value |= SOR_AUDIO_CNTRL_SOURCE_SELECT(SOURCE_SELECT_HDA);

	/* inject null samples */
	अगर (sor->क्रमmat.channels != 2)
		value &= ~SOR_AUDIO_CNTRL_INJECT_शून्यSMPL;
	अन्यथा
		value |= SOR_AUDIO_CNTRL_INJECT_शून्यSMPL;

	value |= SOR_AUDIO_CNTRL_AFIFO_FLUSH;

	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_CNTRL);

	/* enable advertising HBR capability */
	tegra_sor_ग_लिखोl(sor, SOR_AUDIO_SPARE_HBR_ENABLE, SOR_AUDIO_SPARE);
पूर्ण

अटल पूर्णांक tegra_sor_hdmi_enable_audio_infoframe(काष्ठा tegra_sor *sor)
अणु
	u8 buffer[HDMI_INFOFRAME_SIZE(AUDIO)];
	काष्ठा hdmi_audio_infoframe frame;
	u32 value;
	पूर्णांक err;

	err = hdmi_audio_infoframe_init(&frame);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to setup audio infoframe: %d\n", err);
		वापस err;
	पूर्ण

	frame.channels = sor->क्रमmat.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to pack audio infoframe: %d\n", err);
		वापस err;
	पूर्ण

	tegra_sor_hdmi_ग_लिखो_infopack(sor, buffer, err);

	value = tegra_sor_पढ़ोl(sor, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_CHECKSUM_ENABLE;
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AUDIO_INFOFRAME_CTRL);

	वापस 0;
पूर्ण

अटल व्योम tegra_sor_hdmi_audio_enable(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	tegra_sor_audio_enable(sor);

	tegra_sor_ग_लिखोl(sor, 0, SOR_HDMI_ACR_CTRL);

	value = SOR_HDMI_SPARE_ACR_PRIORITY_HIGH |
		SOR_HDMI_SPARE_CTS_RESET(1) |
		SOR_HDMI_SPARE_HW_CTS_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_SPARE);

	/* enable HW CTS */
	value = SOR_HDMI_ACR_SUBPACK_LOW_SB1(0);
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_ACR_0441_SUBPACK_LOW);

	/* allow packet to be sent */
	value = SOR_HDMI_ACR_SUBPACK_HIGH_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_ACR_0441_SUBPACK_HIGH);

	/* reset N counter and enable lookup */
	value = SOR_HDMI_AUDIO_N_RESET | SOR_HDMI_AUDIO_N_LOOKUP;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AUDIO_N);

	value = (24000 * 4096) / (128 * sor->क्रमmat.sample_rate / 1000);
	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_AVAL_0320);
	tegra_sor_ग_लिखोl(sor, 4096, SOR_AUDIO_NVAL_0320);

	tegra_sor_ग_लिखोl(sor, 20000, SOR_AUDIO_AVAL_0441);
	tegra_sor_ग_लिखोl(sor, 4704, SOR_AUDIO_NVAL_0441);

	tegra_sor_ग_लिखोl(sor, 20000, SOR_AUDIO_AVAL_0882);
	tegra_sor_ग_लिखोl(sor, 9408, SOR_AUDIO_NVAL_0882);

	tegra_sor_ग_लिखोl(sor, 20000, SOR_AUDIO_AVAL_1764);
	tegra_sor_ग_लिखोl(sor, 18816, SOR_AUDIO_NVAL_1764);

	value = (24000 * 6144) / (128 * sor->क्रमmat.sample_rate / 1000);
	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_AVAL_0480);
	tegra_sor_ग_लिखोl(sor, 6144, SOR_AUDIO_NVAL_0480);

	value = (24000 * 12288) / (128 * sor->क्रमmat.sample_rate / 1000);
	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_AVAL_0960);
	tegra_sor_ग_लिखोl(sor, 12288, SOR_AUDIO_NVAL_0960);

	value = (24000 * 24576) / (128 * sor->क्रमmat.sample_rate / 1000);
	tegra_sor_ग_लिखोl(sor, value, SOR_AUDIO_AVAL_1920);
	tegra_sor_ग_लिखोl(sor, 24576, SOR_AUDIO_NVAL_1920);

	value = tegra_sor_पढ़ोl(sor, SOR_HDMI_AUDIO_N);
	value &= ~SOR_HDMI_AUDIO_N_RESET;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AUDIO_N);

	tegra_sor_hdmi_enable_audio_infoframe(sor);
पूर्ण

अटल व्योम tegra_sor_hdmi_disable_audio_infoframe(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
पूर्ण

अटल व्योम tegra_sor_hdmi_audio_disable(काष्ठा tegra_sor *sor)
अणु
	tegra_sor_hdmi_disable_audio_infoframe(sor);
पूर्ण

अटल काष्ठा tegra_sor_hdmi_settings *
tegra_sor_hdmi_find_settings(काष्ठा tegra_sor *sor, अचिन्हित दीर्घ frequency)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sor->num_settings; i++)
		अगर (frequency <= sor->settings[i].frequency)
			वापस &sor->settings[i];

	वापस शून्य;
पूर्ण

अटल व्योम tegra_sor_hdmi_disable_scrambling(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_HDMI2_CTRL);
	value &= ~SOR_HDMI2_CTRL_CLOCK_MODE_DIV_BY_4;
	value &= ~SOR_HDMI2_CTRL_SCRAMBLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI2_CTRL);
पूर्ण

अटल व्योम tegra_sor_hdmi_scdc_disable(काष्ठा tegra_sor *sor)
अणु
	काष्ठा i2c_adapter *ddc = sor->output.ddc;

	drm_scdc_set_high_पंचांगds_घड़ी_ratio(ddc, false);
	drm_scdc_set_scrambling(ddc, false);

	tegra_sor_hdmi_disable_scrambling(sor);
पूर्ण

अटल व्योम tegra_sor_hdmi_scdc_stop(काष्ठा tegra_sor *sor)
अणु
	अगर (sor->scdc_enabled) अणु
		cancel_delayed_work_sync(&sor->scdc);
		tegra_sor_hdmi_scdc_disable(sor);
	पूर्ण
पूर्ण

अटल व्योम tegra_sor_hdmi_enable_scrambling(काष्ठा tegra_sor *sor)
अणु
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_HDMI2_CTRL);
	value |= SOR_HDMI2_CTRL_CLOCK_MODE_DIV_BY_4;
	value |= SOR_HDMI2_CTRL_SCRAMBLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI2_CTRL);
पूर्ण

अटल व्योम tegra_sor_hdmi_scdc_enable(काष्ठा tegra_sor *sor)
अणु
	काष्ठा i2c_adapter *ddc = sor->output.ddc;

	drm_scdc_set_high_पंचांगds_घड़ी_ratio(ddc, true);
	drm_scdc_set_scrambling(ddc, true);

	tegra_sor_hdmi_enable_scrambling(sor);
पूर्ण

अटल व्योम tegra_sor_hdmi_scdc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_sor *sor = container_of(work, काष्ठा tegra_sor, scdc.work);
	काष्ठा i2c_adapter *ddc = sor->output.ddc;

	अगर (!drm_scdc_get_scrambling_status(ddc)) अणु
		DRM_DEBUG_KMS("SCDC not scrambled\n");
		tegra_sor_hdmi_scdc_enable(sor);
	पूर्ण

	schedule_delayed_work(&sor->scdc, msecs_to_jअगरfies(5000));
पूर्ण

अटल व्योम tegra_sor_hdmi_scdc_start(काष्ठा tegra_sor *sor)
अणु
	काष्ठा drm_scdc *scdc = &sor->output.connector.display_info.hdmi.scdc;
	काष्ठा drm_display_mode *mode;

	mode = &sor->output.encoder.crtc->state->adjusted_mode;

	अगर (mode->घड़ी >= 340000 && scdc->supported) अणु
		schedule_delayed_work(&sor->scdc, msecs_to_jअगरfies(5000));
		tegra_sor_hdmi_scdc_enable(sor);
		sor->scdc_enabled = true;
	पूर्ण
पूर्ण

अटल व्योम tegra_sor_hdmi_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_sor *sor = to_sor(output);
	u32 value;
	पूर्णांक err;

	tegra_sor_audio_unprepare(sor);
	tegra_sor_hdmi_scdc_stop(sor);

	err = tegra_sor_detach(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to detach SOR: %d\n", err);

	tegra_sor_ग_लिखोl(sor, 0, SOR_STATE1);
	tegra_sor_update(sor);

	/* disable display to SOR घड़ी */
	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);

	अगर (!sor->soc->has_nvdisplay)
		value &= ~SOR1_TIMING_CYA;

	value &= ~SOR_ENABLE(sor->index);

	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	err = tegra_sor_घातer_करोwn(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power down SOR: %d\n", err);

	err = tegra_io_pad_घातer_disable(sor->pad);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power off I/O pad: %d\n", err);

	host1x_client_suspend(&sor->client);
पूर्ण

अटल व्योम tegra_sor_hdmi_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	अचिन्हित पूर्णांक h_ref_to_sync = 1, pulse_start, max_ac;
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_sor_hdmi_settings *settings;
	काष्ठा tegra_sor *sor = to_sor(output);
	काष्ठा tegra_sor_state *state;
	काष्ठा drm_display_mode *mode;
	अचिन्हित दीर्घ rate, pclk;
	अचिन्हित पूर्णांक भाग, i;
	u32 value;
	पूर्णांक err;

	state = to_sor_state(output->connector.state);
	mode = &encoder->crtc->state->adjusted_mode;
	pclk = mode->घड़ी * 1000;

	err = host1x_client_resume(&sor->client);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	/* चयन to safe parent घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_safe);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);
		वापस;
	पूर्ण

	भाग = clk_get_rate(sor->clk) / 1000000 * 4;

	err = tegra_io_pad_घातer_enable(sor->pad);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power on I/O pad: %d\n", err);

	usleep_range(20, 100);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll3);
	value &= ~SOR_PLL3_PLL_VDD_MODE_3V3;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll3);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_VCOPD;
	value &= ~SOR_PLL0_PWR;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(200, 400);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_POWERDOWN_OVERRIDE;
	value &= ~SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_0 |
		 SOR_DP_PADCTL_PD_TXD_1 | SOR_DP_PADCTL_PD_TXD_2;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	जबतक (true) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_LANE_SEQ_CTL);
		अगर ((value & SOR_LANE_SEQ_CTL_STATE_BUSY) == 0)
			अवरोध;

		usleep_range(250, 1000);
	पूर्ण

	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_DOWN |
		SOR_LANE_SEQ_CTL_POWER_STATE_UP | SOR_LANE_SEQ_CTL_DELAY(5);
	tegra_sor_ग_लिखोl(sor, value, SOR_LANE_SEQ_CTL);

	जबतक (true) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_LANE_SEQ_CTL);
		अगर ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			अवरोध;

		usleep_range(250, 1000);
	पूर्ण

	value = tegra_sor_पढ़ोl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;

	अगर (mode->घड़ी < 340000) अणु
		DRM_DEBUG_KMS("setting 2.7 GHz link speed\n");
		value |= SOR_CLK_CNTRL_DP_LINK_SPEED_G2_70;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("setting 5.4 GHz link speed\n");
		value |= SOR_CLK_CNTRL_DP_LINK_SPEED_G5_40;
	पूर्ण

	value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK;
	tegra_sor_ग_लिखोl(sor, value, SOR_CLK_CNTRL);

	/* SOR pad PLL stabilization समय */
	usleep_range(250, 1000);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_LANE_COUNT_MASK;
	value |= SOR_DP_LINKCTL_LANE_COUNT(4);
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_LINKCTL0);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_SPARE0);
	value &= ~SOR_DP_SPARE_DISP_VIDEO_PREAMBLE;
	value &= ~SOR_DP_SPARE_PANEL_INTERNAL;
	value &= ~SOR_DP_SPARE_SEQ_ENABLE;
	value &= ~SOR_DP_SPARE_MACRO_SOR_CLK;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_SPARE0);

	value = SOR_SEQ_CTL_PU_PC(0) | SOR_SEQ_CTL_PU_PC_ALT(0) |
		SOR_SEQ_CTL_PD_PC(8) | SOR_SEQ_CTL_PD_PC_ALT(8);
	tegra_sor_ग_लिखोl(sor, value, SOR_SEQ_CTL);

	value = SOR_SEQ_INST_DRIVE_PWM_OUT_LO | SOR_SEQ_INST_HALT |
		SOR_SEQ_INST_WAIT_VSYNC | SOR_SEQ_INST_WAIT(1);
	tegra_sor_ग_लिखोl(sor, value, SOR_SEQ_INST(0));
	tegra_sor_ग_लिखोl(sor, value, SOR_SEQ_INST(8));

	अगर (!sor->soc->has_nvdisplay) अणु
		/* program the reference घड़ी */
		value = SOR_REFCLK_DIV_INT(भाग) | SOR_REFCLK_DIV_FRAC(भाग);
		tegra_sor_ग_लिखोl(sor, value, SOR_REFCLK);
	पूर्ण

	/* XXX not in TRM */
	क्रम (value = 0, i = 0; i < 5; i++)
		value |= SOR_XBAR_CTRL_LINK0_XSEL(i, sor->xbar_cfg[i]) |
			 SOR_XBAR_CTRL_LINK1_XSEL(i, i);

	tegra_sor_ग_लिखोl(sor, 0x00000000, SOR_XBAR_POL);
	tegra_sor_ग_लिखोl(sor, value, SOR_XBAR_CTRL);

	/*
	 * Switch the pad घड़ी to the DP घड़ी. Note that we cannot actually
	 * करो this because Tegra186 and later करोn't support clk_set_parent()
	 * on the sorX_pad_clkout घड़ीs. We alपढ़ोy करो the equivalent above
	 * using the DP_CLK_SEL mux of the SOR_CLK_CNTRL रेजिस्टर.
	 */
#अगर 0
	err = clk_set_parent(sor->clk_pad, sor->clk_dp);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select pad parent clock: %d\n",
			err);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* चयन the SOR घड़ी to the pad घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_pad);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select SOR parent clock: %d\n",
			err);
		वापस;
	पूर्ण

	/* चयन the output घड़ी to the parent pixel घड़ी */
	err = clk_set_parent(sor->clk, sor->clk_parent);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select output parent clock: %d\n",
			err);
		वापस;
	पूर्ण

	/* adjust घड़ी rate क्रम HDMI 2.0 modes */
	rate = clk_get_rate(sor->clk_parent);

	अगर (mode->घड़ी >= 340000)
		rate /= 2;

	DRM_DEBUG_KMS("setting clock to %lu Hz, mode: %lu Hz\n", rate, pclk);

	clk_set_rate(sor->clk, rate);

	अगर (!sor->soc->has_nvdisplay) अणु
		value = SOR_INPUT_CONTROL_HDMI_SRC_SELECT(dc->pipe);

		/* XXX is this the proper check? */
		अगर (mode->घड़ी < 75000)
			value |= SOR_INPUT_CONTROL_ARM_VIDEO_RANGE_LIMITED;

		tegra_sor_ग_लिखोl(sor, value, SOR_INPUT_CONTROL);
	पूर्ण

	max_ac = ((mode->htotal - mode->hdisplay) - SOR_REKEY - 18) / 32;

	value = SOR_HDMI_CTRL_ENABLE | SOR_HDMI_CTRL_MAX_AC_PACKET(max_ac) |
		SOR_HDMI_CTRL_AUDIO_LAYOUT | SOR_HDMI_CTRL_REKEY(SOR_REKEY);
	tegra_sor_ग_लिखोl(sor, value, SOR_HDMI_CTRL);

	अगर (!dc->soc->has_nvdisplay) अणु
		/* H_PULSE2 setup */
		pulse_start = h_ref_to_sync +
			      (mode->hsync_end - mode->hsync_start) +
			      (mode->htotal - mode->hsync_end) - 10;

		value = PULSE_LAST_END_A | PULSE_QUAL_VACTIVE |
			PULSE_POLARITY_HIGH | PULSE_MODE_NORMAL;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_H_PULSE2_CONTROL);

		value = PULSE_END(pulse_start + 8) | PULSE_START(pulse_start);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_H_PULSE2_POSITION_A);

		value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_SIGNAL_OPTIONS0);
		value |= H_PULSE2_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_SIGNAL_OPTIONS0);
	पूर्ण

	/* infoframe setup */
	err = tegra_sor_hdmi_setup_avi_infoframe(sor, mode);
	अगर (err < 0)
		dev_err(sor->dev, "failed to setup AVI infoframe: %d\n", err);

	/* XXX HDMI audio support not implemented yet */
	tegra_sor_hdmi_disable_audio_infoframe(sor);

	/* use single TMDS protocol */
	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PROTOCOL_MASK;
	value |= SOR_STATE_ASY_PROTOCOL_SINGLE_TMDS_A;
	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);

	/* घातer up pad calibration */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	/* production settings */
	settings = tegra_sor_hdmi_find_settings(sor, mode->घड़ी * 1000);
	अगर (!settings) अणु
		dev_err(sor->dev, "no settings for pixel clock %d Hz\n",
			mode->घड़ी * 1000);
		वापस;
	पूर्ण

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_ICHPMP_MASK;
	value &= ~SOR_PLL0_FILTER_MASK;
	value &= ~SOR_PLL0_VCOCAP_MASK;
	value |= SOR_PLL0_ICHPMP(settings->ichpmp);
	value |= SOR_PLL0_FILTER(settings->filter);
	value |= SOR_PLL0_VCOCAP(settings->vcocap);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll0);

	/* XXX not in TRM */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll1);
	value &= ~SOR_PLL1_LOADADJ_MASK;
	value &= ~SOR_PLL1_TMDS_TERMADJ_MASK;
	value |= SOR_PLL1_LOADADJ(settings->loadadj);
	value |= SOR_PLL1_TMDS_TERMADJ(settings->पंचांगds_termadj);
	value |= SOR_PLL1_TMDS_TERM;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll1);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll3);
	value &= ~SOR_PLL3_BG_TEMP_COEF_MASK;
	value &= ~SOR_PLL3_BG_VREF_LEVEL_MASK;
	value &= ~SOR_PLL3_AVDD10_LEVEL_MASK;
	value &= ~SOR_PLL3_AVDD14_LEVEL_MASK;
	value |= SOR_PLL3_BG_TEMP_COEF(settings->bg_temp_coef);
	value |= SOR_PLL3_BG_VREF_LEVEL(settings->bg_vref_level);
	value |= SOR_PLL3_AVDD10_LEVEL(settings->avdd10_level);
	value |= SOR_PLL3_AVDD14_LEVEL(settings->avdd14_level);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll3);

	value = settings->drive_current[3] << 24 |
		settings->drive_current[2] << 16 |
		settings->drive_current[1] <<  8 |
		settings->drive_current[0] <<  0;
	tegra_sor_ग_लिखोl(sor, value, SOR_LANE_DRIVE_CURRENT0);

	value = settings->preemphasis[3] << 24 |
		settings->preemphasis[2] << 16 |
		settings->preemphasis[1] <<  8 |
		settings->preemphasis[0] <<  0;
	tegra_sor_ग_लिखोl(sor, value, SOR_LANE_PREEMPHASIS0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_TX_PU_MASK;
	value |= SOR_DP_PADCTL_TX_PU_ENABLE;
	value |= SOR_DP_PADCTL_TX_PU(settings->tx_pu_value);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl2);
	value &= ~SOR_DP_PADCTL_SPAREPLL_MASK;
	value |= SOR_DP_PADCTL_SPAREPLL(settings->sparepll);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl2);

	/* घातer करोwn pad calibration */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->dp_padctl0);

	अगर (!dc->soc->has_nvdisplay) अणु
		/* miscellaneous display controller settings */
		value = VSYNC_H_POSITION(1);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_TIMING_OPTIONS);
	पूर्ण

	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_COLOR_CONTROL);
	value &= ~DITHER_CONTROL_MASK;
	value &= ~BASE_COLOR_SIZE_MASK;

	चयन (state->bpc) अणु
	हाल 6:
		value |= BASE_COLOR_SIZE_666;
		अवरोध;

	हाल 8:
		value |= BASE_COLOR_SIZE_888;
		अवरोध;

	हाल 10:
		value |= BASE_COLOR_SIZE_101010;
		अवरोध;

	हाल 12:
		value |= BASE_COLOR_SIZE_121212;
		अवरोध;

	शेष:
		WARN(1, "%u bits-per-color not supported\n", state->bpc);
		value |= BASE_COLOR_SIZE_888;
		अवरोध;
	पूर्ण

	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_COLOR_CONTROL);

	/* XXX set display head owner */
	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_OWNER_MASK;
	value |= SOR_STATE_ASY_OWNER(1 + dc->pipe);
	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);

	err = tegra_sor_घातer_up(sor, 250);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power up SOR: %d\n", err);

	/* configure dynamic range of output */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->head_state0 + dc->pipe);
	value &= ~SOR_HEAD_STATE_RANGECOMPRESS_MASK;
	value &= ~SOR_HEAD_STATE_DYNRANGE_MASK;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state0 + dc->pipe);

	/* configure colorspace */
	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->head_state0 + dc->pipe);
	value &= ~SOR_HEAD_STATE_COLORSPACE_MASK;
	value |= SOR_HEAD_STATE_COLORSPACE_RGB;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->head_state0 + dc->pipe);

	tegra_sor_mode_set(sor, mode, state);

	tegra_sor_update(sor);

	/* program preamble timing in SOR (XXX) */
	value = tegra_sor_पढ़ोl(sor, SOR_DP_SPARE0);
	value &= ~SOR_DP_SPARE_DISP_VIDEO_PREAMBLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_SPARE0);

	err = tegra_sor_attach(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to attach SOR: %d\n", err);

	/* enable display to SOR घड़ी and generate HDMI preamble */
	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);

	अगर (!sor->soc->has_nvdisplay)
		value |= SOR1_TIMING_CYA;

	value |= SOR_ENABLE(sor->index);

	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	अगर (dc->soc->has_nvdisplay) अणु
		value = tegra_dc_पढ़ोl(dc, DC_DISP_CORE_SOR_SET_CONTROL(sor->index));
		value &= ~PROTOCOL_MASK;
		value |= PROTOCOL_SINGLE_TMDS_A;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_CORE_SOR_SET_CONTROL(sor->index));
	पूर्ण

	tegra_dc_commit(dc);

	err = tegra_sor_wakeup(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to wakeup SOR: %d\n", err);

	tegra_sor_hdmi_scdc_start(sor);
	tegra_sor_audio_prepare(sor);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs tegra_sor_hdmi_helpers = अणु
	.disable = tegra_sor_hdmi_disable,
	.enable = tegra_sor_hdmi_enable,
	.atomic_check = tegra_sor_encoder_atomic_check,
पूर्ण;

अटल व्योम tegra_sor_dp_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_sor *sor = to_sor(output);
	u32 value;
	पूर्णांक err;

	अगर (output->panel)
		drm_panel_disable(output->panel);

	/*
	 * Do not attempt to घातer करोwn a DP link अगर we're not connected since
	 * the AUX transactions would just be timing out.
	 */
	अगर (output->connector.status != connector_status_disconnected) अणु
		err = drm_dp_link_घातer_करोwn(sor->aux, &sor->link);
		अगर (err < 0)
			dev_err(sor->dev, "failed to power down link: %d\n",
				err);
	पूर्ण

	err = tegra_sor_detach(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to detach SOR: %d\n", err);

	tegra_sor_ग_लिखोl(sor, 0, SOR_STATE1);
	tegra_sor_update(sor);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value &= ~SOR_ENABLE(sor->index);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);
	tegra_dc_commit(dc);

	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PROTOCOL_MASK;
	value &= ~SOR_STATE_ASY_SUBOWNER_MASK;
	value &= ~SOR_STATE_ASY_OWNER_MASK;
	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);
	tegra_sor_update(sor);

	/* चयन to safe parent घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_safe);
	अगर (err < 0)
		dev_err(sor->dev, "failed to set safe clock: %d\n", err);

	err = tegra_sor_घातer_करोwn(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power down SOR: %d\n", err);

	err = tegra_io_pad_घातer_disable(sor->pad);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power off I/O pad: %d\n", err);

	err = drm_dp_aux_disable(sor->aux);
	अगर (err < 0)
		dev_err(sor->dev, "failed disable DPAUX: %d\n", err);

	अगर (output->panel)
		drm_panel_unprepare(output->panel);

	host1x_client_suspend(&sor->client);
पूर्ण

अटल व्योम tegra_sor_dp_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_sor *sor = to_sor(output);
	काष्ठा tegra_sor_config config;
	काष्ठा tegra_sor_state *state;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_display_info *info;
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक err;

	state = to_sor_state(output->connector.state);
	mode = &encoder->crtc->state->adjusted_mode;
	info = &output->connector.display_info;

	err = host1x_client_resume(&sor->client);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	/* चयन to safe parent घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_safe);
	अगर (err < 0)
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);

	err = tegra_io_pad_घातer_enable(sor->pad);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power on LVDS rail: %d\n", err);

	usleep_range(20, 100);

	err = drm_dp_aux_enable(sor->aux);
	अगर (err < 0)
		dev_err(sor->dev, "failed to enable DPAUX: %d\n", err);

	err = drm_dp_link_probe(sor->aux, &sor->link);
	अगर (err < 0)
		dev_err(sor->dev, "failed to probe DP link: %d\n", err);

	tegra_sor_filter_rates(sor);

	err = drm_dp_link_choose(&sor->link, mode, info);
	अगर (err < 0)
		dev_err(sor->dev, "failed to choose link: %d\n", err);

	अगर (output->panel)
		drm_panel_prepare(output->panel);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 40);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll3);
	value |= SOR_PLL3_PLL_VDD_MODE_3V3;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll3);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll0);
	value &= ~(SOR_PLL0_VCOPD | SOR_PLL0_PWR);
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	value |= SOR_PLL2_SEQ_PLLCAPPD;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	usleep_range(200, 400);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_POWERDOWN_OVERRIDE;
	value &= ~SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll2);

	value = tegra_sor_पढ़ोl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;

	अगर (output->panel)
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK;
	अन्यथा
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_DPCLK;

	tegra_sor_ग_लिखोl(sor, value, SOR_CLK_CNTRL);

	usleep_range(200, 400);

	value = tegra_sor_पढ़ोl(sor, SOR_DP_SPARE0);
	/* XXX not in TRM */
	अगर (output->panel)
		value |= SOR_DP_SPARE_PANEL_INTERNAL;
	अन्यथा
		value &= ~SOR_DP_SPARE_PANEL_INTERNAL;

	value |= SOR_DP_SPARE_SEQ_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_SPARE0);

	/* XXX not in TRM */
	tegra_sor_ग_लिखोl(sor, 0, SOR_LVDS);

	value = tegra_sor_पढ़ोl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_ICHPMP_MASK;
	value &= ~SOR_PLL0_VCOCAP_MASK;
	value |= SOR_PLL0_ICHPMP(0x1);
	value |= SOR_PLL0_VCOCAP(0x3);
	value |= SOR_PLL0_RESISTOR_EXT;
	tegra_sor_ग_लिखोl(sor, value, sor->soc->regs->pll0);

	/* XXX not in TRM */
	क्रम (value = 0, i = 0; i < 5; i++)
		value |= SOR_XBAR_CTRL_LINK0_XSEL(i, sor->soc->xbar_cfg[i]) |
			 SOR_XBAR_CTRL_LINK1_XSEL(i, i);

	tegra_sor_ग_लिखोl(sor, 0x00000000, SOR_XBAR_POL);
	tegra_sor_ग_लिखोl(sor, value, SOR_XBAR_CTRL);

	/*
	 * Switch the pad घड़ी to the DP घड़ी. Note that we cannot actually
	 * करो this because Tegra186 and later करोn't support clk_set_parent()
	 * on the sorX_pad_clkout घड़ीs. We alपढ़ोy करो the equivalent above
	 * using the DP_CLK_SEL mux of the SOR_CLK_CNTRL रेजिस्टर.
	 */
#अगर 0
	err = clk_set_parent(sor->clk_pad, sor->clk_parent);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select pad parent clock: %d\n",
			err);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* चयन the SOR घड़ी to the pad घड़ी */
	err = tegra_sor_set_parent_घड़ी(sor, sor->clk_pad);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select SOR parent clock: %d\n",
			err);
		वापस;
	पूर्ण

	/* चयन the output घड़ी to the parent pixel घड़ी */
	err = clk_set_parent(sor->clk, sor->clk_parent);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to select output parent clock: %d\n",
			err);
		वापस;
	पूर्ण

	/* use DP-A protocol */
	value = tegra_sor_पढ़ोl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PROTOCOL_MASK;
	value |= SOR_STATE_ASY_PROTOCOL_DP_A;
	tegra_sor_ग_लिखोl(sor, value, SOR_STATE1);

	/* enable port */
	value = tegra_sor_पढ़ोl(sor, SOR_DP_LINKCTL0);
	value |= SOR_DP_LINKCTL_ENABLE;
	tegra_sor_ग_लिखोl(sor, value, SOR_DP_LINKCTL0);

	tegra_sor_dp_term_calibrate(sor);

	err = drm_dp_link_train(&sor->link);
	अगर (err < 0)
		dev_err(sor->dev, "link training failed: %d\n", err);
	अन्यथा
		dev_dbg(sor->dev, "link training succeeded\n");

	err = drm_dp_link_घातer_up(sor->aux, &sor->link);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power up DP link: %d\n", err);

	/* compute configuration */
	स_रखो(&config, 0, माप(config));
	config.bits_per_pixel = state->bpc * 3;

	err = tegra_sor_compute_config(sor, mode, &config, &sor->link);
	अगर (err < 0)
		dev_err(sor->dev, "failed to compute configuration: %d\n", err);

	tegra_sor_apply_config(sor, &config);
	tegra_sor_mode_set(sor, mode, state);

	अगर (output->panel) अणु
		/* CSTM (LVDS, link A/B, upper) */
		value = SOR_CSTM_LVDS | SOR_CSTM_LINK_ACT_A | SOR_CSTM_LINK_ACT_B |
			SOR_CSTM_UPPER;
		tegra_sor_ग_लिखोl(sor, value, SOR_CSTM);

		/* PWM setup */
		err = tegra_sor_setup_pwm(sor, 250);
		अगर (err < 0)
			dev_err(sor->dev, "failed to setup PWM: %d\n", err);
	पूर्ण

	tegra_sor_update(sor);

	err = tegra_sor_घातer_up(sor, 250);
	अगर (err < 0)
		dev_err(sor->dev, "failed to power up SOR: %d\n", err);

	/* attach and wake up */
	err = tegra_sor_attach(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to attach SOR: %d\n", err);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= SOR_ENABLE(sor->index);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	err = tegra_sor_wakeup(sor);
	अगर (err < 0)
		dev_err(sor->dev, "failed to wakeup SOR: %d\n", err);

	अगर (output->panel)
		drm_panel_enable(output->panel);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs tegra_sor_dp_helpers = अणु
	.disable = tegra_sor_dp_disable,
	.enable = tegra_sor_dp_enable,
	.atomic_check = tegra_sor_encoder_atomic_check,
पूर्ण;

अटल व्योम tegra_sor_disable_regulator(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल पूर्णांक tegra_sor_enable_regulator(काष्ठा tegra_sor *sor, काष्ठा regulator *reg)
अणु
	पूर्णांक err;

	err = regulator_enable(reg);
	अगर (err)
		वापस err;

	वापस devm_add_action_or_reset(sor->dev, tegra_sor_disable_regulator, reg);
पूर्ण

अटल पूर्णांक tegra_sor_hdmi_probe(काष्ठा tegra_sor *sor)
अणु
	पूर्णांक err;

	sor->avdd_io_supply = devm_regulator_get(sor->dev, "avdd-io-hdmi-dp");
	अगर (IS_ERR(sor->avdd_io_supply)) अणु
		dev_err(sor->dev, "cannot get AVDD I/O supply: %ld\n",
			PTR_ERR(sor->avdd_io_supply));
		वापस PTR_ERR(sor->avdd_io_supply);
	पूर्ण

	err = tegra_sor_enable_regulator(sor, sor->avdd_io_supply);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to enable AVDD I/O supply: %d\n",
			err);
		वापस err;
	पूर्ण

	sor->vdd_pll_supply = devm_regulator_get(sor->dev, "vdd-hdmi-dp-pll");
	अगर (IS_ERR(sor->vdd_pll_supply)) अणु
		dev_err(sor->dev, "cannot get VDD PLL supply: %ld\n",
			PTR_ERR(sor->vdd_pll_supply));
		वापस PTR_ERR(sor->vdd_pll_supply);
	पूर्ण

	err = tegra_sor_enable_regulator(sor, sor->vdd_pll_supply);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to enable VDD PLL supply: %d\n",
			err);
		वापस err;
	पूर्ण

	sor->hdmi_supply = devm_regulator_get(sor->dev, "hdmi");
	अगर (IS_ERR(sor->hdmi_supply)) अणु
		dev_err(sor->dev, "cannot get HDMI supply: %ld\n",
			PTR_ERR(sor->hdmi_supply));
		वापस PTR_ERR(sor->hdmi_supply);
	पूर्ण

	err = tegra_sor_enable_regulator(sor, sor->hdmi_supply);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to enable HDMI supply: %d\n", err);
		वापस err;
	पूर्ण

	INIT_DELAYED_WORK(&sor->scdc, tegra_sor_hdmi_scdc_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_sor_ops tegra_sor_hdmi_ops = अणु
	.name = "HDMI",
	.probe = tegra_sor_hdmi_probe,
	.audio_enable = tegra_sor_hdmi_audio_enable,
	.audio_disable = tegra_sor_hdmi_audio_disable,
पूर्ण;

अटल पूर्णांक tegra_sor_dp_probe(काष्ठा tegra_sor *sor)
अणु
	पूर्णांक err;

	sor->avdd_io_supply = devm_regulator_get(sor->dev, "avdd-io-hdmi-dp");
	अगर (IS_ERR(sor->avdd_io_supply))
		वापस PTR_ERR(sor->avdd_io_supply);

	err = tegra_sor_enable_regulator(sor, sor->avdd_io_supply);
	अगर (err < 0)
		वापस err;

	sor->vdd_pll_supply = devm_regulator_get(sor->dev, "vdd-hdmi-dp-pll");
	अगर (IS_ERR(sor->vdd_pll_supply))
		वापस PTR_ERR(sor->vdd_pll_supply);

	err = tegra_sor_enable_regulator(sor, sor->vdd_pll_supply);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_sor_ops tegra_sor_dp_ops = अणु
	.name = "DP",
	.probe = tegra_sor_dp_probe,
पूर्ण;

अटल पूर्णांक tegra_sor_init(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	स्थिर काष्ठा drm_encoder_helper_funcs *helpers = शून्य;
	काष्ठा tegra_sor *sor = host1x_client_to_sor(client);
	पूर्णांक connector = DRM_MODE_CONNECTOR_Unknown;
	पूर्णांक encoder = DRM_MODE_ENCODER_NONE;
	पूर्णांक err;

	अगर (!sor->aux) अणु
		अगर (sor->ops == &tegra_sor_hdmi_ops) अणु
			connector = DRM_MODE_CONNECTOR_HDMIA;
			encoder = DRM_MODE_ENCODER_TMDS;
			helpers = &tegra_sor_hdmi_helpers;
		पूर्ण अन्यथा अगर (sor->soc->supports_lvds) अणु
			connector = DRM_MODE_CONNECTOR_LVDS;
			encoder = DRM_MODE_ENCODER_LVDS;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sor->output.panel) अणु
			connector = DRM_MODE_CONNECTOR_eDP;
			encoder = DRM_MODE_ENCODER_TMDS;
			helpers = &tegra_sor_dp_helpers;
		पूर्ण अन्यथा अणु
			connector = DRM_MODE_CONNECTOR_DisplayPort;
			encoder = DRM_MODE_ENCODER_TMDS;
			helpers = &tegra_sor_dp_helpers;
		पूर्ण

		sor->link.ops = &tegra_sor_dp_link_ops;
		sor->link.aux = sor->aux;
	पूर्ण

	sor->output.dev = sor->dev;

	drm_connector_init_with_ddc(drm, &sor->output.connector,
				    &tegra_sor_connector_funcs,
				    connector,
				    sor->output.ddc);
	drm_connector_helper_add(&sor->output.connector,
				 &tegra_sor_connector_helper_funcs);
	sor->output.connector.dpms = DRM_MODE_DPMS_OFF;

	drm_simple_encoder_init(drm, &sor->output.encoder, encoder);
	drm_encoder_helper_add(&sor->output.encoder, helpers);

	drm_connector_attach_encoder(&sor->output.connector,
					  &sor->output.encoder);
	drm_connector_रेजिस्टर(&sor->output.connector);

	err = tegra_output_init(drm, &sor->output);
	अगर (err < 0) अणु
		dev_err(client->dev, "failed to initialize output: %d\n", err);
		वापस err;
	पूर्ण

	tegra_output_find_possible_crtcs(&sor->output, drm);

	अगर (sor->aux) अणु
		err = drm_dp_aux_attach(sor->aux, &sor->output);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to attach DP: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * XXX: Remove this reset once proper hand-over from firmware to
	 * kernel is possible.
	 */
	अगर (sor->rst) अणु
		err = pm_runसमय_resume_and_get(sor->dev);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to get runtime PM: %d\n", err);
			वापस err;
		पूर्ण

		err = reset_control_acquire(sor->rst);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to acquire SOR reset: %d\n",
				err);
			जाओ rpm_put;
		पूर्ण

		err = reset_control_निश्चित(sor->rst);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to assert SOR reset: %d\n",
				err);
			जाओ rpm_put;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(sor->clk);
	अगर (err < 0) अणु
		dev_err(sor->dev, "failed to enable clock: %d\n", err);
		जाओ rpm_put;
	पूर्ण

	usleep_range(1000, 3000);

	अगर (sor->rst) अणु
		err = reset_control_deनिश्चित(sor->rst);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to deassert SOR reset: %d\n",
				err);
			clk_disable_unprepare(sor->clk);
			जाओ rpm_put;
		पूर्ण

		reset_control_release(sor->rst);
		pm_runसमय_put(sor->dev);
	पूर्ण

	err = clk_prepare_enable(sor->clk_safe);
	अगर (err < 0) अणु
		clk_disable_unprepare(sor->clk);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(sor->clk_dp);
	अगर (err < 0) अणु
		clk_disable_unprepare(sor->clk_safe);
		clk_disable_unprepare(sor->clk);
		वापस err;
	पूर्ण

	वापस 0;

rpm_put:
	अगर (sor->rst)
		pm_runसमय_put(sor->dev);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_sor_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_sor *sor = host1x_client_to_sor(client);
	पूर्णांक err;

	tegra_output_निकास(&sor->output);

	अगर (sor->aux) अणु
		err = drm_dp_aux_detach(sor->aux);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to detach DP: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	clk_disable_unprepare(sor->clk_safe);
	clk_disable_unprepare(sor->clk_dp);
	clk_disable_unprepare(sor->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_runसमय_suspend(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_sor *sor = host1x_client_to_sor(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	अगर (sor->rst) अणु
		err = reset_control_निश्चित(sor->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to assert reset: %d\n", err);
			वापस err;
		पूर्ण

		reset_control_release(sor->rst);
	पूर्ण

	usleep_range(1000, 2000);

	clk_disable_unprepare(sor->clk);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_sor_runसमय_resume(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_sor *sor = host1x_client_to_sor(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(sor->clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable clock: %d\n", err);
		जाओ put_rpm;
	पूर्ण

	usleep_range(1000, 2000);

	अगर (sor->rst) अणु
		err = reset_control_acquire(sor->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to acquire reset: %d\n", err);
			जाओ disable_clk;
		पूर्ण

		err = reset_control_deनिश्चित(sor->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to deassert reset: %d\n", err);
			जाओ release_reset;
		पूर्ण
	पूर्ण

	वापस 0;

release_reset:
	reset_control_release(sor->rst);
disable_clk:
	clk_disable_unprepare(sor->clk);
put_rpm:
	pm_runसमय_put_sync(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops sor_client_ops = अणु
	.init = tegra_sor_init,
	.निकास = tegra_sor_निकास,
	.suspend = tegra_sor_runसमय_suspend,
	.resume = tegra_sor_runसमय_resume,
पूर्ण;

अटल स्थिर u8 tegra124_sor_xbar_cfg[5] = अणु
	0, 1, 2, 3, 4
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_regs tegra124_sor_regs = अणु
	.head_state0 = 0x05,
	.head_state1 = 0x07,
	.head_state2 = 0x09,
	.head_state3 = 0x0b,
	.head_state4 = 0x0d,
	.head_state5 = 0x0f,
	.pll0 = 0x17,
	.pll1 = 0x18,
	.pll2 = 0x19,
	.pll3 = 0x1a,
	.dp_padctl0 = 0x5c,
	.dp_padctl2 = 0x73,
पूर्ण;

/* Tegra124 and Tegra132 have lanes 0 and 2 swapped. */
अटल स्थिर u8 tegra124_sor_lane_map[4] = अणु
	2, 1, 0, 3,
पूर्ण;

अटल स्थिर u8 tegra124_sor_voltage_swing[4][4][4] = अणु
	अणु
		अणु 0x13, 0x19, 0x1e, 0x28 पूर्ण,
		अणु 0x1e, 0x25, 0x2d, पूर्ण,
		अणु 0x28, 0x32, पूर्ण,
		अणु 0x3c, पूर्ण,
	पूर्ण, अणु
		अणु 0x12, 0x17, 0x1b, 0x25 पूर्ण,
		अणु 0x1c, 0x23, 0x2a, पूर्ण,
		अणु 0x25, 0x2f, पूर्ण,
		अणु 0x39, पूर्ण
	पूर्ण, अणु
		अणु 0x12, 0x16, 0x1a, 0x22 पूर्ण,
		अणु 0x1b, 0x20, 0x27, पूर्ण,
		अणु 0x24, 0x2d, पूर्ण,
		अणु 0x36, पूर्ण,
	पूर्ण, अणु
		अणु 0x11, 0x14, 0x17, 0x1f पूर्ण,
		अणु 0x19, 0x1e, 0x24, पूर्ण,
		अणु 0x22, 0x2a, पूर्ण,
		अणु 0x32, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 tegra124_sor_pre_emphasis[4][4][4] = अणु
	अणु
		अणु 0x00, 0x09, 0x13, 0x25 पूर्ण,
		अणु 0x00, 0x0f, 0x1e, पूर्ण,
		अणु 0x00, 0x14, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x0a, 0x14, 0x28 पूर्ण,
		अणु 0x00, 0x0f, 0x1e, पूर्ण,
		अणु 0x00, 0x14, पूर्ण,
		अणु 0x00 पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x0a, 0x14, 0x28 पूर्ण,
		अणु 0x00, 0x0f, 0x1e, पूर्ण,
		अणु 0x00, 0x14, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x0a, 0x14, 0x28 पूर्ण,
		अणु 0x00, 0x0f, 0x1e, पूर्ण,
		अणु 0x00, 0x14, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 tegra124_sor_post_cursor[4][4][4] = अणु
	अणु
		अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
		अणु 0x00, 0x00, 0x00, पूर्ण,
		अणु 0x00, 0x00, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x02, 0x02, 0x04, 0x05 पूर्ण,
		अणु 0x02, 0x04, 0x05, पूर्ण,
		अणु 0x04, 0x05, पूर्ण,
		अणु 0x05, पूर्ण,
	पूर्ण, अणु
		अणु 0x04, 0x05, 0x08, 0x0b पूर्ण,
		अणु 0x05, 0x09, 0x0b, पूर्ण,
		अणु 0x08, 0x0a, पूर्ण,
		अणु 0x0b, पूर्ण,
	पूर्ण, अणु
		अणु 0x05, 0x09, 0x0b, 0x12 पूर्ण,
		अणु 0x09, 0x0d, 0x12, पूर्ण,
		अणु 0x0b, 0x0f, पूर्ण,
		अणु 0x12, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 tegra124_sor_tx_pu[4][4][4] = अणु
	अणु
		अणु 0x20, 0x30, 0x40, 0x60 पूर्ण,
		अणु 0x30, 0x40, 0x60, पूर्ण,
		अणु 0x40, 0x60, पूर्ण,
		अणु 0x60, पूर्ण,
	पूर्ण, अणु
		अणु 0x20, 0x20, 0x30, 0x50 पूर्ण,
		अणु 0x30, 0x40, 0x50, पूर्ण,
		अणु 0x40, 0x50, पूर्ण,
		अणु 0x60, पूर्ण,
	पूर्ण, अणु
		अणु 0x20, 0x20, 0x30, 0x40, पूर्ण,
		अणु 0x30, 0x30, 0x40, पूर्ण,
		अणु 0x40, 0x50, पूर्ण,
		अणु 0x60, पूर्ण,
	पूर्ण, अणु
		अणु 0x20, 0x20, 0x20, 0x40, पूर्ण,
		अणु 0x30, 0x30, 0x40, पूर्ण,
		अणु 0x40, 0x40, पूर्ण,
		अणु 0x60, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra124_sor = अणु
	.supports_lvds = true,
	.supports_hdmi = false,
	.supports_dp = true,
	.supports_audio = false,
	.supports_hdcp = false,
	.regs = &tegra124_sor_regs,
	.has_nvdisplay = false,
	.xbar_cfg = tegra124_sor_xbar_cfg,
	.lane_map = tegra124_sor_lane_map,
	.voltage_swing = tegra124_sor_voltage_swing,
	.pre_emphasis = tegra124_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर u8 tegra132_sor_pre_emphasis[4][4][4] = अणु
	अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x01, 0x0e, 0x1d, पूर्ण,
		अणु 0x01, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00 पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra132_sor = अणु
	.supports_lvds = true,
	.supports_hdmi = false,
	.supports_dp = true,
	.supports_audio = false,
	.supports_hdcp = false,
	.regs = &tegra124_sor_regs,
	.has_nvdisplay = false,
	.xbar_cfg = tegra124_sor_xbar_cfg,
	.lane_map = tegra124_sor_lane_map,
	.voltage_swing = tegra124_sor_voltage_swing,
	.pre_emphasis = tegra132_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_regs tegra210_sor_regs = अणु
	.head_state0 = 0x05,
	.head_state1 = 0x07,
	.head_state2 = 0x09,
	.head_state3 = 0x0b,
	.head_state4 = 0x0d,
	.head_state5 = 0x0f,
	.pll0 = 0x17,
	.pll1 = 0x18,
	.pll2 = 0x19,
	.pll3 = 0x1a,
	.dp_padctl0 = 0x5c,
	.dp_padctl2 = 0x73,
पूर्ण;

अटल स्थिर u8 tegra210_sor_xbar_cfg[5] = अणु
	2, 1, 0, 3, 4
पूर्ण;

अटल स्थिर u8 tegra210_sor_lane_map[4] = अणु
	0, 1, 2, 3,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra210_sor = अणु
	.supports_lvds = false,
	.supports_hdmi = false,
	.supports_dp = true,
	.supports_audio = false,
	.supports_hdcp = false,

	.regs = &tegra210_sor_regs,
	.has_nvdisplay = false,

	.xbar_cfg = tegra210_sor_xbar_cfg,
	.lane_map = tegra210_sor_lane_map,
	.voltage_swing = tegra124_sor_voltage_swing,
	.pre_emphasis = tegra124_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra210_sor1 = अणु
	.supports_lvds = false,
	.supports_hdmi = true,
	.supports_dp = true,
	.supports_audio = true,
	.supports_hdcp = true,

	.regs = &tegra210_sor_regs,
	.has_nvdisplay = false,

	.num_settings = ARRAY_SIZE(tegra210_sor_hdmi_शेषs),
	.settings = tegra210_sor_hdmi_शेषs,
	.xbar_cfg = tegra210_sor_xbar_cfg,
	.lane_map = tegra210_sor_lane_map,
	.voltage_swing = tegra124_sor_voltage_swing,
	.pre_emphasis = tegra124_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_regs tegra186_sor_regs = अणु
	.head_state0 = 0x151,
	.head_state1 = 0x154,
	.head_state2 = 0x157,
	.head_state3 = 0x15a,
	.head_state4 = 0x15d,
	.head_state5 = 0x160,
	.pll0 = 0x163,
	.pll1 = 0x164,
	.pll2 = 0x165,
	.pll3 = 0x166,
	.dp_padctl0 = 0x168,
	.dp_padctl2 = 0x16a,
पूर्ण;

अटल स्थिर u8 tegra186_sor_voltage_swing[4][4][4] = अणु
	अणु
		अणु 0x13, 0x19, 0x1e, 0x28 पूर्ण,
		अणु 0x1e, 0x25, 0x2d, पूर्ण,
		अणु 0x28, 0x32, पूर्ण,
		अणु 0x39, पूर्ण,
	पूर्ण, अणु
		अणु 0x12, 0x16, 0x1b, 0x25 पूर्ण,
		अणु 0x1c, 0x23, 0x2a, पूर्ण,
		अणु 0x25, 0x2f, पूर्ण,
		अणु 0x37, पूर्ण
	पूर्ण, अणु
		अणु 0x12, 0x16, 0x1a, 0x22 पूर्ण,
		अणु 0x1b, 0x20, 0x27, पूर्ण,
		अणु 0x24, 0x2d, पूर्ण,
		अणु 0x35, पूर्ण,
	पूर्ण, अणु
		अणु 0x11, 0x14, 0x17, 0x1f पूर्ण,
		अणु 0x19, 0x1e, 0x24, पूर्ण,
		अणु 0x22, 0x2a, पूर्ण,
		अणु 0x32, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 tegra186_sor_pre_emphasis[4][4][4] = अणु
	अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x01, 0x0e, 0x1d, पूर्ण,
		अणु 0x01, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00 पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x14, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण, अणु
		अणु 0x00, 0x08, 0x12, 0x24 पूर्ण,
		अणु 0x00, 0x0e, 0x1d, पूर्ण,
		अणु 0x00, 0x13, पूर्ण,
		अणु 0x00, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra186_sor = अणु
	.supports_lvds = false,
	.supports_hdmi = true,
	.supports_dp = true,
	.supports_audio = true,
	.supports_hdcp = true,

	.regs = &tegra186_sor_regs,
	.has_nvdisplay = true,

	.num_settings = ARRAY_SIZE(tegra186_sor_hdmi_शेषs),
	.settings = tegra186_sor_hdmi_शेषs,
	.xbar_cfg = tegra124_sor_xbar_cfg,
	.lane_map = tegra124_sor_lane_map,
	.voltage_swing = tegra186_sor_voltage_swing,
	.pre_emphasis = tegra186_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_regs tegra194_sor_regs = अणु
	.head_state0 = 0x151,
	.head_state1 = 0x155,
	.head_state2 = 0x159,
	.head_state3 = 0x15d,
	.head_state4 = 0x161,
	.head_state5 = 0x165,
	.pll0 = 0x169,
	.pll1 = 0x16a,
	.pll2 = 0x16b,
	.pll3 = 0x16c,
	.dp_padctl0 = 0x16e,
	.dp_padctl2 = 0x16f,
पूर्ण;

अटल स्थिर काष्ठा tegra_sor_soc tegra194_sor = अणु
	.supports_lvds = false,
	.supports_hdmi = true,
	.supports_dp = true,
	.supports_audio = true,
	.supports_hdcp = true,

	.regs = &tegra194_sor_regs,
	.has_nvdisplay = true,

	.num_settings = ARRAY_SIZE(tegra194_sor_hdmi_शेषs),
	.settings = tegra194_sor_hdmi_शेषs,

	.xbar_cfg = tegra210_sor_xbar_cfg,
	.lane_map = tegra124_sor_lane_map,
	.voltage_swing = tegra186_sor_voltage_swing,
	.pre_emphasis = tegra186_sor_pre_emphasis,
	.post_cursor = tegra124_sor_post_cursor,
	.tx_pu = tegra124_sor_tx_pu,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_sor_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-sor", .data = &tegra194_sor पूर्ण,
	अणु .compatible = "nvidia,tegra186-sor", .data = &tegra186_sor पूर्ण,
	अणु .compatible = "nvidia,tegra210-sor1", .data = &tegra210_sor1 पूर्ण,
	अणु .compatible = "nvidia,tegra210-sor", .data = &tegra210_sor पूर्ण,
	अणु .compatible = "nvidia,tegra132-sor", .data = &tegra132_sor पूर्ण,
	अणु .compatible = "nvidia,tegra124-sor", .data = &tegra124_sor पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_sor_of_match);

अटल पूर्णांक tegra_sor_parse_dt(काष्ठा tegra_sor *sor)
अणु
	काष्ठा device_node *np = sor->dev->of_node;
	u32 xbar_cfg[5];
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक err;

	अगर (sor->soc->has_nvdisplay) अणु
		err = of_property_पढ़ो_u32(np, "nvidia,interface", &value);
		अगर (err < 0)
			वापस err;

		sor->index = value;

		/*
		 * override the शेष that we alपढ़ोy set क्रम Tegra210 and
		 * earlier
		 */
		sor->pad = TEGRA_IO_PAD_HDMI_DP0 + sor->index;
	पूर्ण अन्यथा अणु
		अगर (!sor->soc->supports_audio)
			sor->index = 0;
		अन्यथा
			sor->index = 1;
	पूर्ण

	err = of_property_पढ़ो_u32_array(np, "nvidia,xbar-cfg", xbar_cfg, 5);
	अगर (err < 0) अणु
		/* fall back to शेष per-SoC XBAR configuration */
		क्रम (i = 0; i < 5; i++)
			sor->xbar_cfg[i] = sor->soc->xbar_cfg[i];
	पूर्ण अन्यथा अणु
		/* copy cells to SOR XBAR configuration */
		क्रम (i = 0; i < 5; i++)
			sor->xbar_cfg[i] = xbar_cfg[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_sor_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_sor *sor = data;
	u32 value;

	value = tegra_sor_पढ़ोl(sor, SOR_INT_STATUS);
	tegra_sor_ग_लिखोl(sor, value, SOR_INT_STATUS);

	अगर (value & SOR_INT_CODEC_SCRATCH0) अणु
		value = tegra_sor_पढ़ोl(sor, SOR_AUDIO_HDA_CODEC_SCRATCH0);

		अगर (value & SOR_AUDIO_HDA_CODEC_SCRATCH0_VALID) अणु
			अचिन्हित पूर्णांक क्रमmat;

			क्रमmat = value & SOR_AUDIO_HDA_CODEC_SCRATCH0_FMT_MASK;

			tegra_hda_parse_क्रमmat(क्रमmat, &sor->क्रमmat);

			अगर (sor->ops->audio_enable)
				sor->ops->audio_enable(sor);
		पूर्ण अन्यथा अणु
			अगर (sor->ops->audio_disable)
				sor->ops->audio_disable(sor);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_sor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा tegra_sor *sor;
	काष्ठा resource *regs;
	पूर्णांक err;

	sor = devm_kzalloc(&pdev->dev, माप(*sor), GFP_KERNEL);
	अगर (!sor)
		वापस -ENOMEM;

	sor->soc = of_device_get_match_data(&pdev->dev);
	sor->output.dev = sor->dev = &pdev->dev;

	sor->settings = devm_kmemdup(&pdev->dev, sor->soc->settings,
				     sor->soc->num_settings *
					माप(*sor->settings),
				     GFP_KERNEL);
	अगर (!sor->settings)
		वापस -ENOMEM;

	sor->num_settings = sor->soc->num_settings;

	np = of_parse_phandle(pdev->dev.of_node, "nvidia,dpaux", 0);
	अगर (np) अणु
		sor->aux = drm_dp_aux_find_by_of_node(np);
		of_node_put(np);

		अगर (!sor->aux)
			वापस -EPROBE_DEFER;

		अगर (get_device(sor->aux->dev))
			sor->output.ddc = &sor->aux->ddc;
	पूर्ण

	अगर (!sor->aux) अणु
		अगर (sor->soc->supports_hdmi) अणु
			sor->ops = &tegra_sor_hdmi_ops;
			sor->pad = TEGRA_IO_PAD_HDMI;
		पूर्ण अन्यथा अगर (sor->soc->supports_lvds) अणु
			dev_err(&pdev->dev, "LVDS not supported yet\n");
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "unknown (non-DP) support\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		np = of_parse_phandle(pdev->dev.of_node, "nvidia,panel", 0);
		/*
		 * No need to keep this around since we only use it as a check
		 * to see अगर a panel is connected (eDP) or not (DP).
		 */
		of_node_put(np);

		sor->ops = &tegra_sor_dp_ops;
		sor->pad = TEGRA_IO_PAD_LVDS;
	पूर्ण

	err = tegra_sor_parse_dt(sor);
	अगर (err < 0)
		जाओ put_aux;

	err = tegra_output_probe(&sor->output);
	अगर (err < 0) अणु
		dev_err_probe(&pdev->dev, err, "failed to probe output\n");
		जाओ put_aux;
	पूर्ण

	अगर (sor->ops && sor->ops->probe) अणु
		err = sor->ops->probe(sor);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "failed to probe %s: %d\n",
				sor->ops->name, err);
			जाओ हटाओ;
		पूर्ण
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sor->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(sor->regs)) अणु
		err = PTR_ERR(sor->regs);
		जाओ हटाओ;
	पूर्ण

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to get IRQ: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	sor->irq = err;

	err = devm_request_irq(sor->dev, sor->irq, tegra_sor_irq, 0,
			       dev_name(sor->dev), sor);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	sor->rst = devm_reset_control_get_exclusive_released(&pdev->dev, "sor");
	अगर (IS_ERR(sor->rst)) अणु
		err = PTR_ERR(sor->rst);

		अगर (err != -EBUSY || WARN_ON(!pdev->dev.pm_करोमुख्य)) अणु
			dev_err(&pdev->dev, "failed to get reset control: %d\n",
				err);
			जाओ हटाओ;
		पूर्ण

		/*
		 * At this poपूर्णांक, the reset control is most likely being used
		 * by the generic घातer करोमुख्य implementation. With any luck
		 * the घातer करोमुख्य will have taken care of resetting the SOR
		 * and we करोn't have to करो anything.
		 */
		sor->rst = शून्य;
	पूर्ण

	sor->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sor->clk)) अणु
		err = PTR_ERR(sor->clk);
		dev_err(&pdev->dev, "failed to get module clock: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	अगर (sor->soc->supports_hdmi || sor->soc->supports_dp) अणु
		काष्ठा device_node *np = pdev->dev.of_node;
		स्थिर अक्षर *name;

		/*
		 * For backwards compatibility with Tegra210 device trees,
		 * fall back to the old घड़ी name "source" अगर the new "out"
		 * घड़ी is not available.
		 */
		अगर (of_property_match_string(np, "clock-names", "out") < 0)
			name = "source";
		अन्यथा
			name = "out";

		sor->clk_out = devm_clk_get(&pdev->dev, name);
		अगर (IS_ERR(sor->clk_out)) अणु
			err = PTR_ERR(sor->clk_out);
			dev_err(sor->dev, "failed to get %s clock: %d\n",
				name, err);
			जाओ हटाओ;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* fall back to the module घड़ी on SOR0 (eDP/LVDS only) */
		sor->clk_out = sor->clk;
	पूर्ण

	sor->clk_parent = devm_clk_get(&pdev->dev, "parent");
	अगर (IS_ERR(sor->clk_parent)) अणु
		err = PTR_ERR(sor->clk_parent);
		dev_err(&pdev->dev, "failed to get parent clock: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	sor->clk_safe = devm_clk_get(&pdev->dev, "safe");
	अगर (IS_ERR(sor->clk_safe)) अणु
		err = PTR_ERR(sor->clk_safe);
		dev_err(&pdev->dev, "failed to get safe clock: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	sor->clk_dp = devm_clk_get(&pdev->dev, "dp");
	अगर (IS_ERR(sor->clk_dp)) अणु
		err = PTR_ERR(sor->clk_dp);
		dev_err(&pdev->dev, "failed to get DP clock: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	/*
	 * Starting with Tegra186, the BPMP provides an implementation क्रम
	 * the pad output घड़ी, so we have to look it up from device tree.
	 */
	sor->clk_pad = devm_clk_get(&pdev->dev, "pad");
	अगर (IS_ERR(sor->clk_pad)) अणु
		अगर (sor->clk_pad != ERR_PTR(-ENOENT)) अणु
			err = PTR_ERR(sor->clk_pad);
			जाओ हटाओ;
		पूर्ण

		/*
		 * If the pad output घड़ी is not available, then we assume
		 * we're on Tegra210 or earlier and have to provide our own
		 * implementation.
		 */
		sor->clk_pad = शून्य;
	पूर्ण

	/*
	 * The bootloader may have set up the SOR such that it's module घड़ी
	 * is sourced by one of the display PLLs. However, that करोesn't work
	 * without properly having set up other bits of the SOR.
	 */
	err = clk_set_parent(sor->clk_out, sor->clk_safe);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to use safe clock: %d\n", err);
		जाओ हटाओ;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sor);
	pm_runसमय_enable(&pdev->dev);

	host1x_client_init(&sor->client);
	sor->client.ops = &sor_client_ops;
	sor->client.dev = &pdev->dev;

	/*
	 * On Tegra210 and earlier, provide our own implementation क्रम the
	 * pad output घड़ी.
	 */
	अगर (!sor->clk_pad) अणु
		अक्षर *name;

		name = devm_kaप्र_लिखो(sor->dev, GFP_KERNEL, "sor%u_pad_clkout",
				      sor->index);
		अगर (!name) अणु
			err = -ENOMEM;
			जाओ uninit;
		पूर्ण

		err = host1x_client_resume(&sor->client);
		अगर (err < 0) अणु
			dev_err(sor->dev, "failed to resume: %d\n", err);
			जाओ uninit;
		पूर्ण

		sor->clk_pad = tegra_clk_sor_pad_रेजिस्टर(sor, name);
		host1x_client_suspend(&sor->client);
	पूर्ण

	अगर (IS_ERR(sor->clk_pad)) अणु
		err = PTR_ERR(sor->clk_pad);
		dev_err(sor->dev, "failed to register SOR pad clock: %d\n",
			err);
		जाओ uninit;
	पूर्ण

	err = __host1x_client_रेजिस्टर(&sor->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		जाओ uninit;
	पूर्ण

	वापस 0;

uninit:
	host1x_client_निकास(&sor->client);
	pm_runसमय_disable(&pdev->dev);
हटाओ:
	अगर (sor->aux)
		sor->output.ddc = शून्य;

	tegra_output_हटाओ(&sor->output);
put_aux:
	अगर (sor->aux)
		put_device(sor->aux->dev);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_sor_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_sor *sor = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&sor->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	अगर (sor->aux) अणु
		put_device(sor->aux->dev);
		sor->output.ddc = शून्य;
	पूर्ण

	tegra_output_हटाओ(&sor->output);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_sor_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_sor *sor = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_output_suspend(&sor->output);
	अगर (err < 0) अणु
		dev_err(dev, "failed to suspend output: %d\n", err);
		वापस err;
	पूर्ण

	अगर (sor->hdmi_supply) अणु
		err = regulator_disable(sor->hdmi_supply);
		अगर (err < 0) अणु
			tegra_output_resume(&sor->output);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_sor_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_sor *sor = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (sor->hdmi_supply) अणु
		err = regulator_enable(sor->hdmi_supply);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = tegra_output_resume(&sor->output);
	अगर (err < 0) अणु
		dev_err(dev, "failed to resume output: %d\n", err);

		अगर (sor->hdmi_supply)
			regulator_disable(sor->hdmi_supply);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_sor_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra_sor_suspend, tegra_sor_resume)
पूर्ण;

काष्ठा platक्रमm_driver tegra_sor_driver = अणु
	.driver = अणु
		.name = "tegra-sor",
		.of_match_table = tegra_sor_of_match,
		.pm = &tegra_sor_pm_ops,
	पूर्ण,
	.probe = tegra_sor_probe,
	.हटाओ = tegra_sor_हटाओ,
पूर्ण;
