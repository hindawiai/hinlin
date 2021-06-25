<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "hda.h"
#समावेश "hdmi.h"
#समावेश "drm.h"
#समावेश "dc.h"
#समावेश "trace.h"

#घोषणा HDMI_ELD_BUFFER_SIZE 96

काष्ठा पंचांगds_config अणु
	अचिन्हित पूर्णांक pclk;
	u32 pll0;
	u32 pll1;
	u32 pe_current;
	u32 drive_current;
	u32 peak_current;
पूर्ण;

काष्ठा tegra_hdmi_config अणु
	स्थिर काष्ठा पंचांगds_config *पंचांगds;
	अचिन्हित पूर्णांक num_पंचांगds;

	अचिन्हित दीर्घ fuse_override_offset;
	u32 fuse_override_value;

	bool has_sor_io_peak_current;
	bool has_hda;
	bool has_hbr;
पूर्ण;

काष्ठा tegra_hdmi अणु
	काष्ठा host1x_client client;
	काष्ठा tegra_output output;
	काष्ठा device *dev;

	काष्ठा regulator *hdmi;
	काष्ठा regulator *pll;
	काष्ठा regulator *vdd;

	व्योम __iomem *regs;
	अचिन्हित पूर्णांक irq;

	काष्ठा clk *clk_parent;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;

	स्थिर काष्ठा tegra_hdmi_config *config;

	अचिन्हित पूर्णांक audio_source;
	काष्ठा tegra_hda_क्रमmat क्रमmat;

	अचिन्हित पूर्णांक pixel_घड़ी;
	bool stereo;
	bool dvi;

	काष्ठा drm_info_list *debugfs_files;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_hdmi *
host1x_client_to_hdmi(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_hdmi, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_hdmi *to_hdmi(काष्ठा tegra_output *output)
अणु
	वापस container_of(output, काष्ठा tegra_hdmi, output);
पूर्ण

#घोषणा HDMI_AUDIOCLK_FREQ 216000000
#घोषणा HDMI_REKEY_DEFAULT 56

क्रमागत अणु
	AUTO = 0,
	SPDIF,
	HDA,
पूर्ण;

अटल अंतरभूत u32 tegra_hdmi_पढ़ोl(काष्ठा tegra_hdmi *hdmi,
				   अचिन्हित पूर्णांक offset)
अणु
	u32 value = पढ़ोl(hdmi->regs + (offset << 2));

	trace_hdmi_पढ़ोl(hdmi->dev, offset, value);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम tegra_hdmi_ग_लिखोl(काष्ठा tegra_hdmi *hdmi, u32 value,
				     अचिन्हित पूर्णांक offset)
अणु
	trace_hdmi_ग_लिखोl(hdmi->dev, offset, value);
	ग_लिखोl(value, hdmi->regs + (offset << 2));
पूर्ण

काष्ठा tegra_hdmi_audio_config अणु
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक cts;
	अचिन्हित पूर्णांक aval;
पूर्ण;

अटल स्थिर काष्ठा पंचांगds_config tegra20_पंचांगds_config[] = अणु
	अणु /* slow pixel घड़ी modes */
		.pclk = 27000000,
		.pll0 = SOR_PLL_BG_V17_S(3) | SOR_PLL_ICHPMP(1) |
			SOR_PLL_RESISTORSEL | SOR_PLL_VCOCAP(0) |
			SOR_PLL_TX_REG_LOAD(3),
		.pll1 = SOR_PLL_TMDS_TERM_ENABLE,
		.pe_current = PE_CURRENT0(PE_CURRENT_0_0_mA) |
			PE_CURRENT1(PE_CURRENT_0_0_mA) |
			PE_CURRENT2(PE_CURRENT_0_0_mA) |
			PE_CURRENT3(PE_CURRENT_0_0_mA),
		.drive_current = DRIVE_CURRENT_LANE0(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE1(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE2(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE3(DRIVE_CURRENT_7_125_mA),
	पूर्ण,
	अणु /* high pixel घड़ी modes */
		.pclk = अच_पूर्णांक_उच्च,
		.pll0 = SOR_PLL_BG_V17_S(3) | SOR_PLL_ICHPMP(1) |
			SOR_PLL_RESISTORSEL | SOR_PLL_VCOCAP(1) |
			SOR_PLL_TX_REG_LOAD(3),
		.pll1 = SOR_PLL_TMDS_TERM_ENABLE | SOR_PLL_PE_EN,
		.pe_current = PE_CURRENT0(PE_CURRENT_6_0_mA) |
			PE_CURRENT1(PE_CURRENT_6_0_mA) |
			PE_CURRENT2(PE_CURRENT_6_0_mA) |
			PE_CURRENT3(PE_CURRENT_6_0_mA),
		.drive_current = DRIVE_CURRENT_LANE0(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE1(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE2(DRIVE_CURRENT_7_125_mA) |
			DRIVE_CURRENT_LANE3(DRIVE_CURRENT_7_125_mA),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पंचांगds_config tegra30_पंचांगds_config[] = अणु
	अणु /* 480p modes */
		.pclk = 27000000,
		.pll0 = SOR_PLL_BG_V17_S(3) | SOR_PLL_ICHPMP(1) |
			SOR_PLL_RESISTORSEL | SOR_PLL_VCOCAP(0) |
			SOR_PLL_TX_REG_LOAD(0),
		.pll1 = SOR_PLL_TMDS_TERM_ENABLE,
		.pe_current = PE_CURRENT0(PE_CURRENT_0_0_mA) |
			PE_CURRENT1(PE_CURRENT_0_0_mA) |
			PE_CURRENT2(PE_CURRENT_0_0_mA) |
			PE_CURRENT3(PE_CURRENT_0_0_mA),
		.drive_current = DRIVE_CURRENT_LANE0(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE1(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE2(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE3(DRIVE_CURRENT_5_250_mA),
	पूर्ण, अणु /* 720p modes */
		.pclk = 74250000,
		.pll0 = SOR_PLL_BG_V17_S(3) | SOR_PLL_ICHPMP(1) |
			SOR_PLL_RESISTORSEL | SOR_PLL_VCOCAP(1) |
			SOR_PLL_TX_REG_LOAD(0),
		.pll1 = SOR_PLL_TMDS_TERM_ENABLE | SOR_PLL_PE_EN,
		.pe_current = PE_CURRENT0(PE_CURRENT_5_0_mA) |
			PE_CURRENT1(PE_CURRENT_5_0_mA) |
			PE_CURRENT2(PE_CURRENT_5_0_mA) |
			PE_CURRENT3(PE_CURRENT_5_0_mA),
		.drive_current = DRIVE_CURRENT_LANE0(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE1(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE2(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE3(DRIVE_CURRENT_5_250_mA),
	पूर्ण, अणु /* 1080p modes */
		.pclk = अच_पूर्णांक_उच्च,
		.pll0 = SOR_PLL_BG_V17_S(3) | SOR_PLL_ICHPMP(1) |
			SOR_PLL_RESISTORSEL | SOR_PLL_VCOCAP(3) |
			SOR_PLL_TX_REG_LOAD(0),
		.pll1 = SOR_PLL_TMDS_TERM_ENABLE | SOR_PLL_PE_EN,
		.pe_current = PE_CURRENT0(PE_CURRENT_5_0_mA) |
			PE_CURRENT1(PE_CURRENT_5_0_mA) |
			PE_CURRENT2(PE_CURRENT_5_0_mA) |
			PE_CURRENT3(PE_CURRENT_5_0_mA),
		.drive_current = DRIVE_CURRENT_LANE0(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE1(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE2(DRIVE_CURRENT_5_250_mA) |
			DRIVE_CURRENT_LANE3(DRIVE_CURRENT_5_250_mA),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पंचांगds_config tegra114_पंचांगds_config[] = अणु
	अणु /* 480p/576p / 25.2MHz/27MHz modes */
		.pclk = 27000000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(0) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_LOADADJ(3) | SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_0_mA_T114) |
			PE_CURRENT1(PE_CURRENT_0_mA_T114) |
			PE_CURRENT2(PE_CURRENT_0_mA_T114) |
			PE_CURRENT3(PE_CURRENT_0_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_10_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 720p / 74.25MHz modes */
		.pclk = 74250000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(1) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_PE_EN | SOR_PLL_LOADADJ(3) |
			SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_15_mA_T114) |
			PE_CURRENT1(PE_CURRENT_15_mA_T114) |
			PE_CURRENT2(PE_CURRENT_15_mA_T114) |
			PE_CURRENT3(PE_CURRENT_15_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_10_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 1080p / 148.5MHz modes */
		.pclk = 148500000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(3) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_PE_EN | SOR_PLL_LOADADJ(3) |
			SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_10_mA_T114) |
			PE_CURRENT1(PE_CURRENT_10_mA_T114) |
			PE_CURRENT2(PE_CURRENT_10_mA_T114) |
			PE_CURRENT3(PE_CURRENT_10_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_12_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 225/297MHz modes */
		.pclk = अच_पूर्णांक_उच्च,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(0xf) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_LOADADJ(3) | SOR_PLL_TMDS_TERMADJ(7)
			| SOR_PLL_TMDS_TERM_ENABLE,
		.pe_current = PE_CURRENT0(PE_CURRENT_0_mA_T114) |
			PE_CURRENT1(PE_CURRENT_0_mA_T114) |
			PE_CURRENT2(PE_CURRENT_0_mA_T114) |
			PE_CURRENT3(PE_CURRENT_0_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_19_200_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_800_mA),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पंचांगds_config tegra124_पंचांगds_config[] = अणु
	अणु /* 480p/576p / 25.2MHz/27MHz modes */
		.pclk = 27000000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(0) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_LOADADJ(3) | SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_0_mA_T114) |
			PE_CURRENT1(PE_CURRENT_0_mA_T114) |
			PE_CURRENT2(PE_CURRENT_0_mA_T114) |
			PE_CURRENT3(PE_CURRENT_0_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_10_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 720p / 74.25MHz modes */
		.pclk = 74250000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(1) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_PE_EN | SOR_PLL_LOADADJ(3) |
			SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_15_mA_T114) |
			PE_CURRENT1(PE_CURRENT_15_mA_T114) |
			PE_CURRENT2(PE_CURRENT_15_mA_T114) |
			PE_CURRENT3(PE_CURRENT_15_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_10_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_10_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 1080p / 148.5MHz modes */
		.pclk = 148500000,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(3) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_PE_EN | SOR_PLL_LOADADJ(3) |
			SOR_PLL_TMDS_TERMADJ(0),
		.pe_current = PE_CURRENT0(PE_CURRENT_10_mA_T114) |
			PE_CURRENT1(PE_CURRENT_10_mA_T114) |
			PE_CURRENT2(PE_CURRENT_10_mA_T114) |
			PE_CURRENT3(PE_CURRENT_10_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_12_400_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_12_400_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_0_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_000_mA),
	पूर्ण, अणु /* 225/297MHz modes */
		.pclk = अच_पूर्णांक_उच्च,
		.pll0 = SOR_PLL_ICHPMP(1) | SOR_PLL_BG_V17_S(3) |
			SOR_PLL_VCOCAP(0xf) | SOR_PLL_RESISTORSEL,
		.pll1 = SOR_PLL_LOADADJ(3) | SOR_PLL_TMDS_TERMADJ(7)
			| SOR_PLL_TMDS_TERM_ENABLE,
		.pe_current = PE_CURRENT0(PE_CURRENT_0_mA_T114) |
			PE_CURRENT1(PE_CURRENT_0_mA_T114) |
			PE_CURRENT2(PE_CURRENT_0_mA_T114) |
			PE_CURRENT3(PE_CURRENT_0_mA_T114),
		.drive_current =
			DRIVE_CURRENT_LANE0_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE1_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE2_T114(DRIVE_CURRENT_25_200_mA_T114) |
			DRIVE_CURRENT_LANE3_T114(DRIVE_CURRENT_19_200_mA_T114),
		.peak_current = PEAK_CURRENT_LANE0(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE1(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE2(PEAK_CURRENT_3_000_mA) |
			PEAK_CURRENT_LANE3(PEAK_CURRENT_0_800_mA),
	पूर्ण,
पूर्ण;

अटल पूर्णांक
tegra_hdmi_get_audio_config(अचिन्हित पूर्णांक audio_freq, अचिन्हित पूर्णांक pix_घड़ी,
			    काष्ठा tegra_hdmi_audio_config *config)
अणु
	स्थिर अचिन्हित पूर्णांक afreq = 128 * audio_freq;
	स्थिर अचिन्हित पूर्णांक min_n = afreq / 1500;
	स्थिर अचिन्हित पूर्णांक max_n = afreq / 300;
	स्थिर अचिन्हित पूर्णांक ideal_n = afreq / 1000;
	पूर्णांक64_t min_err = (uपूर्णांक64_t)-1 >> 1;
	अचिन्हित पूर्णांक min_delta = -1;
	पूर्णांक n;

	स_रखो(config, 0, माप(*config));
	config->n = -1;

	क्रम (n = min_n; n <= max_n; n++) अणु
		uपूर्णांक64_t cts_f, aval_f;
		अचिन्हित पूर्णांक delta;
		पूर्णांक64_t cts, err;

		/* compute aval in 48.16 fixed poपूर्णांक */
		aval_f = ((पूर्णांक64_t)24000000 << 16) * n;
		करो_भाग(aval_f, afreq);
		/* It should round without any rest */
		अगर (aval_f & 0xFFFF)
			जारी;

		/* Compute cts in 48.16 fixed poपूर्णांक */
		cts_f = ((पूर्णांक64_t)pix_घड़ी << 16) * n;
		करो_भाग(cts_f, afreq);
		/* Round it to the nearest पूर्णांकeger */
		cts = (cts_f & ~0xFFFF) + ((cts_f & BIT(15)) << 1);

		delta = असल(n - ideal_n);

		/* Compute the असलolute error */
		err = असल((पूर्णांक64_t)cts_f - cts);
		अगर (err < min_err || (err == min_err && delta < min_delta)) अणु
			config->n = n;
			config->cts = cts >> 16;
			config->aval = aval_f >> 16;
			min_delta = delta;
			min_err = err;
		पूर्ण
	पूर्ण

	वापस config->n != -1 ? 0 : -EINVAL;
पूर्ण

अटल व्योम tegra_hdmi_setup_audio_fs_tables(काष्ठा tegra_hdmi *hdmi)
अणु
	स्थिर अचिन्हित पूर्णांक freqs[] = अणु
		32000, 44100, 48000, 88200, 96000, 176400, 192000
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(freqs); i++) अणु
		अचिन्हित पूर्णांक f = freqs[i];
		अचिन्हित पूर्णांक eight_half;
		अचिन्हित पूर्णांक delta;
		u32 value;

		अगर (f > 96000)
			delta = 2;
		अन्यथा अगर (f > 48000)
			delta = 6;
		अन्यथा
			delta = 9;

		eight_half = (8 * HDMI_AUDIOCLK_FREQ) / (f * 128);
		value = AUDIO_FS_LOW(eight_half - delta) |
			AUDIO_FS_HIGH(eight_half + delta);
		tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_AUDIO_FS(i));
	पूर्ण
पूर्ण

अटल व्योम tegra_hdmi_ग_लिखो_aval(काष्ठा tegra_hdmi *hdmi, u32 value)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक sample_rate;
		अचिन्हित पूर्णांक offset;
	पूर्ण regs[] = अणु
		अणु  32000, HDMI_NV_PDISP_SOR_AUDIO_AVAL_0320 पूर्ण,
		अणु  44100, HDMI_NV_PDISP_SOR_AUDIO_AVAL_0441 पूर्ण,
		अणु  48000, HDMI_NV_PDISP_SOR_AUDIO_AVAL_0480 पूर्ण,
		अणु  88200, HDMI_NV_PDISP_SOR_AUDIO_AVAL_0882 पूर्ण,
		अणु  96000, HDMI_NV_PDISP_SOR_AUDIO_AVAL_0960 पूर्ण,
		अणु 176400, HDMI_NV_PDISP_SOR_AUDIO_AVAL_1764 पूर्ण,
		अणु 192000, HDMI_NV_PDISP_SOR_AUDIO_AVAL_1920 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		अगर (regs[i].sample_rate == hdmi->क्रमmat.sample_rate) अणु
			tegra_hdmi_ग_लिखोl(hdmi, value, regs[i].offset);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_hdmi_setup_audio(काष्ठा tegra_hdmi *hdmi)
अणु
	काष्ठा tegra_hdmi_audio_config config;
	u32 source, value;
	पूर्णांक err;

	चयन (hdmi->audio_source) अणु
	हाल HDA:
		अगर (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_HDAL;
		अन्यथा
			वापस -EINVAL;

		अवरोध;

	हाल SPDIF:
		अगर (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_SPDIF;
		अन्यथा
			source = AUDIO_CNTRL0_SOURCE_SELECT_SPDIF;
		अवरोध;

	शेष:
		अगर (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_AUTO;
		अन्यथा
			source = AUDIO_CNTRL0_SOURCE_SELECT_AUTO;
		अवरोध;
	पूर्ण

	/*
	 * Tegra30 and later use a slightly modअगरied version of the रेजिस्टर
	 * layout to accomodate क्रम changes related to supporting HDA as the
	 * audio input source क्रम HDMI. The source select field has moved to
	 * the SOR_AUDIO_CNTRL0 रेजिस्टर, but the error tolerance and frames
	 * per block fields reमुख्य in the AUDIO_CNTRL0 रेजिस्टर.
	 */
	अगर (hdmi->config->has_hda) अणु
		/*
		 * Inject null samples पूर्णांकo the audio FIFO क्रम every frame in
		 * which the codec did not receive any samples. This applies
		 * to stereo LPCM only.
		 *
		 * XXX: This seems to be a remnant of MCP days when this was
		 * used to work around issues with monitors not being able to
		 * play back प्रणाली startup sounds early. It is possibly not
		 * needed on Linux at all.
		 */
		अगर (hdmi->क्रमmat.channels == 2)
			value = SOR_AUDIO_CNTRL0_INJECT_शून्यSMPL;
		अन्यथा
			value = 0;

		value |= source;

		tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_CNTRL0);
	पूर्ण

	/*
	 * On Tegra20, HDA is not a supported audio source and the source
	 * select field is part of the AUDIO_CNTRL0 रेजिस्टर.
	 */
	value = AUDIO_CNTRL0_FRAMES_PER_BLOCK(0xc0) |
		AUDIO_CNTRL0_ERROR_TOLERANCE(6);

	अगर (!hdmi->config->has_hda)
		value |= source;

	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_AUDIO_CNTRL0);

	/*
	 * Advertise support क्रम High Bit-Rate on Tegra114 and later.
	 */
	अगर (hdmi->config->has_hbr) अणु
		value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_AUDIO_SPARE0);
		value |= SOR_AUDIO_SPARE0_HBR_ENABLE;
		tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_SPARE0);
	पूर्ण

	err = tegra_hdmi_get_audio_config(hdmi->क्रमmat.sample_rate,
					  hdmi->pixel_घड़ी, &config);
	अगर (err < 0) अणु
		dev_err(hdmi->dev,
			"cannot set audio to %u Hz at %u Hz pixel clock\n",
			hdmi->क्रमmat.sample_rate, hdmi->pixel_घड़ी);
		वापस err;
	पूर्ण

	dev_dbg(hdmi->dev, "audio: pixclk=%u, n=%u, cts=%u, aval=%u\n",
		hdmi->pixel_घड़ी, config.n, config.cts, config.aval);

	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_HDMI_ACR_CTRL);

	value = AUDIO_N_RESETF | AUDIO_N_GENERATE_ALTERNATE |
		AUDIO_N_VALUE(config.n - 1);
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_AUDIO_N);

	tegra_hdmi_ग_लिखोl(hdmi, ACR_SUBPACK_N(config.n) | ACR_ENABLE,
			  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH);

	tegra_hdmi_ग_लिखोl(hdmi, ACR_SUBPACK_CTS(config.cts),
			  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW);

	value = SPARE_HW_CTS | SPARE_FORCE_SW_CTS | SPARE_CTS_RESET_VAL(1);
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_SPARE);

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_AUDIO_N);
	value &= ~AUDIO_N_RESETF;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_AUDIO_N);

	अगर (hdmi->config->has_hda)
		tegra_hdmi_ग_लिखो_aval(hdmi, config.aval);

	tegra_hdmi_setup_audio_fs_tables(hdmi);

	वापस 0;
पूर्ण

अटल व्योम tegra_hdmi_disable_audio(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	value &= ~GENERIC_CTRL_AUDIO;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_enable_audio(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	value |= GENERIC_CTRL_AUDIO;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_ग_लिखो_eld(काष्ठा tegra_hdmi *hdmi)
अणु
	माप_प्रकार length = drm_eld_size(hdmi->output.connector.eld), i;
	u32 value;

	क्रम (i = 0; i < length; i++)
		tegra_hdmi_ग_लिखोl(hdmi, i << 8 | hdmi->output.connector.eld[i],
				  HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR);

	/*
	 * The HDA codec will always report an ELD buffer size of 96 bytes and
	 * the HDA codec driver will check that each byte पढ़ो from the buffer
	 * is valid. Thereक्रमe every byte must be written, even अगर no 96 bytes
	 * were parsed from EDID.
	 */
	क्रम (i = length; i < HDMI_ELD_BUFFER_SIZE; i++)
		tegra_hdmi_ग_लिखोl(hdmi, i << 8 | 0,
				  HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR);

	value = SOR_AUDIO_HDA_PRESENSE_VALID | SOR_AUDIO_HDA_PRESENSE_PRESENT;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_HDA_PRESENSE);
पूर्ण

अटल अंतरभूत u32 tegra_hdmi_subpack(स्थिर u8 *ptr, माप_प्रकार size)
अणु
	u32 value = 0;
	माप_प्रकार i;

	क्रम (i = size; i > 0; i--)
		value = (value << 8) | ptr[i - 1];

	वापस value;
पूर्ण

अटल व्योम tegra_hdmi_ग_लिखो_infopack(काष्ठा tegra_hdmi *hdmi, स्थिर व्योम *data,
				      माप_प्रकार size)
अणु
	स्थिर u8 *ptr = data;
	अचिन्हित दीर्घ offset;
	माप_प्रकार i, j;
	u32 value;

	चयन (ptr[0]) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		offset = HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_HEADER;
		अवरोध;

	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		offset = HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_HEADER;
		अवरोध;

	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		offset = HDMI_NV_PDISP_HDMI_GENERIC_HEADER;
		अवरोध;

	शेष:
		dev_err(hdmi->dev, "unsupported infoframe type: %02x\n",
			ptr[0]);
		वापस;
	पूर्ण

	value = INFOFRAME_HEADER_TYPE(ptr[0]) |
		INFOFRAME_HEADER_VERSION(ptr[1]) |
		INFOFRAME_HEADER_LEN(ptr[2]);
	tegra_hdmi_ग_लिखोl(hdmi, value, offset);
	offset++;

	/*
	 * Each subpack contains 7 bytes, भागided पूर्णांकo:
	 * - subpack_low: bytes 0 - 3
	 * - subpack_high: bytes 4 - 6 (with byte 7 padded to 0x00)
	 */
	क्रम (i = 3, j = 0; i < size; i += 7, j += 8) अणु
		माप_प्रकार rem = size - i, num = min_t(माप_प्रकार, rem, 4);

		value = tegra_hdmi_subpack(&ptr[i], num);
		tegra_hdmi_ग_लिखोl(hdmi, value, offset++);

		num = min_t(माप_प्रकार, rem - num, 3);

		value = tegra_hdmi_subpack(&ptr[i + 4], num);
		tegra_hdmi_ग_लिखोl(hdmi, value, offset++);
	पूर्ण
पूर्ण

अटल व्योम tegra_hdmi_setup_avi_infoframe(काष्ठा tegra_hdmi *hdmi,
					   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_avi_infoframe frame;
	u8 buffer[17];
	sमाप_प्रकार err;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &hdmi->output.connector, mode);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to setup AVI infoframe: %zd\n", err);
		वापस;
	पूर्ण

	err = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to pack AVI infoframe: %zd\n", err);
		वापस;
	पूर्ण

	tegra_hdmi_ग_लिखो_infopack(hdmi, buffer, err);
पूर्ण

अटल व्योम tegra_hdmi_disable_avi_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_enable_avi_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_setup_audio_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	काष्ठा hdmi_audio_infoframe frame;
	u8 buffer[14];
	sमाप_प्रकार err;

	err = hdmi_audio_infoframe_init(&frame);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to setup audio infoframe: %zd\n",
			err);
		वापस;
	पूर्ण

	frame.channels = hdmi->क्रमmat.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to pack audio infoframe: %zd\n",
			err);
		वापस;
	पूर्ण

	/*
	 * The audio infoframe has only one set of subpack रेजिस्टरs, so the
	 * infoframe needs to be truncated. One set of subpack रेजिस्टरs can
	 * contain 7 bytes. Including the 3 byte header only the first 10
	 * bytes can be programmed.
	 */
	tegra_hdmi_ग_लिखो_infopack(hdmi, buffer, min_t(माप_प्रकार, 10, err));
पूर्ण

अटल व्योम tegra_hdmi_disable_audio_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_enable_audio_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_setup_stereo_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	काष्ठा hdmi_venकरोr_infoframe frame;
	u8 buffer[10];
	sमाप_प्रकार err;

	hdmi_venकरोr_infoframe_init(&frame);
	frame.s3d_काष्ठा = HDMI_3D_STRUCTURE_FRAME_PACKING;

	err = hdmi_venकरोr_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to pack vendor infoframe: %zd\n",
			err);
		वापस;
	पूर्ण

	tegra_hdmi_ग_लिखो_infopack(hdmi, buffer, err);
पूर्ण

अटल व्योम tegra_hdmi_disable_stereo_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	value &= ~GENERIC_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_enable_stereo_infoframe(काष्ठा tegra_hdmi *hdmi)
अणु
	u32 value;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	value |= GENERIC_CTRL_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
पूर्ण

अटल व्योम tegra_hdmi_setup_पंचांगds(काष्ठा tegra_hdmi *hdmi,
				  स्थिर काष्ठा पंचांगds_config *पंचांगds)
अणु
	u32 value;

	tegra_hdmi_ग_लिखोl(hdmi, पंचांगds->pll0, HDMI_NV_PDISP_SOR_PLL0);
	tegra_hdmi_ग_लिखोl(hdmi, पंचांगds->pll1, HDMI_NV_PDISP_SOR_PLL1);
	tegra_hdmi_ग_लिखोl(hdmi, पंचांगds->pe_current, HDMI_NV_PDISP_PE_CURRENT);

	tegra_hdmi_ग_लिखोl(hdmi, पंचांगds->drive_current,
			  HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT);

	value = tegra_hdmi_पढ़ोl(hdmi, hdmi->config->fuse_override_offset);
	value |= hdmi->config->fuse_override_value;
	tegra_hdmi_ग_लिखोl(hdmi, value, hdmi->config->fuse_override_offset);

	अगर (hdmi->config->has_sor_io_peak_current)
		tegra_hdmi_ग_लिखोl(hdmi, पंचांगds->peak_current,
				  HDMI_NV_PDISP_SOR_IO_PEAK_CURRENT);
पूर्ण

अटल bool tegra_output_is_hdmi(काष्ठा tegra_output *output)
अणु
	काष्ठा edid *edid;

	अगर (!output->connector.edid_blob_ptr)
		वापस false;

	edid = (काष्ठा edid *)output->connector.edid_blob_ptr->data;

	वापस drm_detect_hdmi_monitor(edid);
पूर्ण

अटल क्रमागत drm_connector_status
tegra_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);
	क्रमागत drm_connector_status status;

	status = tegra_output_connector_detect(connector, क्रमce);
	अगर (status == connector_status_connected)
		वापस status;

	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_SOR_AUDIO_HDA_PRESENSE);
	वापस status;
पूर्ण

#घोषणा DEBUGFS_REG32(_name) अणु .name = #_name, .offset = _name पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 tegra_hdmi_regs[] = अणु
	DEBUGFS_REG32(HDMI_CTXSW),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_STATE0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_STATE1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_STATE2),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_AN_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_AN_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CN_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CN_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_AKSV_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_AKSV_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_BKSV_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_BKSV_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CKSV_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CKSV_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_DKSV_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_DKSV_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CMODE),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_MPRIME_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_MPRIME_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_SPRIME_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_SPRIME_LSB2),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_SPRIME_LSB1),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_RI),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CS_MSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_RG_HDCP_CS_LSB),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_EMU0),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_EMU_RDATA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_EMU1),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_EMU2),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_STATUS),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_HEADER),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_STATUS),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_HEADER),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_SUBPACK0_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_SUBPACK0_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_SUBPACK1_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_AVI_INFOFRAME_SUBPACK1_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_STATUS),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_HEADER),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK0_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK0_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK1_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK1_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK2_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK2_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK3_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GENERIC_SUBPACK3_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0320_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0320_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0882_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0882_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_1764_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_1764_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0480_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0480_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0960_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_0960_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_1920_SUBPACK_LOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_ACR_1920_SUBPACK_HIGH),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_VSYNC_KEEPOUT),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_VSYNC_WINDOW),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GCP_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GCP_STATUS),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_GCP_SUBPACK),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_CHANNEL_STATUS1),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_CHANNEL_STATUS2),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_EMU0),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_EMU1),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_EMU1_RDATA),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_SPARE),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_SPDIF_CHN_STATUS1),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_SPDIF_CHN_STATUS2),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDMI_HDCPRIF_ROM_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CAP),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_PWR),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_TEST),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_PLL0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_PLL1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_PLL2),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CSTM),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_LVDS),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CRCA),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CRCB),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_BLANK),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_CTL),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(0)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(1)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(2)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(3)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(4)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(5)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(6)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(7)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(8)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(9)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(10)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(11)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(12)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(13)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(14)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_SEQ_INST(15)),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_VCRCA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_VCRCA1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CCRCA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_CCRCA1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_EDATAA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_EDATAA1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_COUNTA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_COUNTA1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_DEBUGA0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_DEBUGA1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_TRIG),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_MSCHECK),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_DEBUG0),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_DEBUG1),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_DEBUG2),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(0)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(1)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(2)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(3)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(4)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(5)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_FS(6)),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_PULSE_WIDTH),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_THRESHOLD),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_CNTRL0),
	DEBUGFS_REG32(HDMI_NV_PDISP_AUDIO_N),
	DEBUGFS_REG32(HDMI_NV_PDISP_HDCPRIF_ROM_TIMING),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_REFCLK),
	DEBUGFS_REG32(HDMI_NV_PDISP_CRC_CONTROL),
	DEBUGFS_REG32(HDMI_NV_PDISP_INPUT_CONTROL),
	DEBUGFS_REG32(HDMI_NV_PDISP_SCRATCH),
	DEBUGFS_REG32(HDMI_NV_PDISP_PE_CURRENT),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_CTRL),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_DEBUG0),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_DEBUG1),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_DEBUG2),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_HDCP_KEY_0),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_HDCP_KEY_1),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_HDCP_KEY_2),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_HDCP_KEY_3),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_HDCP_KEY_TRIG),
	DEBUGFS_REG32(HDMI_NV_PDISP_KEY_SKEY_INDEX),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_CNTRL0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_SPARE0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_HDA_CODEC_SCRATCH0),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_HDA_CODEC_SCRATCH1),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_AUDIO_HDA_PRESENSE),
	DEBUGFS_REG32(HDMI_NV_PDISP_INT_STATUS),
	DEBUGFS_REG32(HDMI_NV_PDISP_INT_MASK),
	DEBUGFS_REG32(HDMI_NV_PDISP_INT_ENABLE),
	DEBUGFS_REG32(HDMI_NV_PDISP_SOR_IO_PEAK_CURRENT),
पूर्ण;

अटल पूर्णांक tegra_hdmi_show_regs(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_hdmi *hdmi = node->info_ent->data;
	काष्ठा drm_crtc *crtc = hdmi->output.encoder.crtc;
	काष्ठा drm_device *drm = node->minor->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	drm_modeset_lock_all(drm);

	अगर (!crtc || !crtc->state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tegra_hdmi_regs); i++) अणु
		अचिन्हित पूर्णांक offset = tegra_hdmi_regs[i].offset;

		seq_म_लिखो(s, "%-56s %#05x %08x\n", tegra_hdmi_regs[i].name,
			   offset, tegra_hdmi_पढ़ोl(hdmi, offset));
	पूर्ण

unlock:
	drm_modeset_unlock_all(drm);
	वापस err;
पूर्ण

अटल काष्ठा drm_info_list debugfs_files[] = अणु
	अणु "regs", tegra_hdmi_show_regs, 0, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_hdmi_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	अचिन्हित पूर्णांक i, count = ARRAY_SIZE(debugfs_files);
	काष्ठा drm_minor *minor = connector->dev->primary;
	काष्ठा dentry *root = connector->debugfs_entry;
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);

	hdmi->debugfs_files = kmemdup(debugfs_files, माप(debugfs_files),
				      GFP_KERNEL);
	अगर (!hdmi->debugfs_files)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++)
		hdmi->debugfs_files[i].data = hdmi;

	drm_debugfs_create_files(hdmi->debugfs_files, count, root, minor);

	वापस 0;
पूर्ण

अटल व्योम tegra_hdmi_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा drm_minor *minor = connector->dev->primary;
	अचिन्हित पूर्णांक count = ARRAY_SIZE(debugfs_files);
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);

	drm_debugfs_हटाओ_files(hdmi->debugfs_files, count, minor);
	kमुक्त(hdmi->debugfs_files);
	hdmi->debugfs_files = शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tegra_hdmi_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.detect = tegra_hdmi_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = tegra_output_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = tegra_hdmi_late_रेजिस्टर,
	.early_unरेजिस्टर = tegra_hdmi_early_unरेजिस्टर,
पूर्ण;

अटल क्रमागत drm_mode_status
tegra_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
				काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);
	अचिन्हित दीर्घ pclk = mode->घड़ी * 1000;
	क्रमागत drm_mode_status status = MODE_OK;
	काष्ठा clk *parent;
	दीर्घ err;

	parent = clk_get_parent(hdmi->clk_parent);

	err = clk_round_rate(parent, pclk * 4);
	अगर (err <= 0)
		status = MODE_NOCLOCK;

	वापस status;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
tegra_hdmi_connector_helper_funcs = अणु
	.get_modes = tegra_output_connector_get_modes,
	.mode_valid = tegra_hdmi_connector_mode_valid,
पूर्ण;

अटल व्योम tegra_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);
	u32 value;
	पूर्णांक err;

	/*
	 * The following accesses रेजिस्टरs of the display controller, so make
	 * sure it's only executed when the output is attached to one.
	 */
	अगर (dc) अणु
		value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
		value &= ~HDMI_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

		tegra_dc_commit(dc);
	पूर्ण

	अगर (!hdmi->dvi) अणु
		अगर (hdmi->stereo)
			tegra_hdmi_disable_stereo_infoframe(hdmi);

		tegra_hdmi_disable_audio_infoframe(hdmi);
		tegra_hdmi_disable_avi_infoframe(hdmi);
		tegra_hdmi_disable_audio(hdmi);
	पूर्ण

	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_INT_ENABLE);
	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_INT_MASK);

	err = host1x_client_suspend(&hdmi->client);
	अगर (err < 0)
		dev_err(hdmi->dev, "failed to suspend: %d\n", err);
पूर्ण

अटल व्योम tegra_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	अचिन्हित पूर्णांक h_sync_width, h_front_porch, h_back_porch, i, rekey;
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(encoder->crtc);
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);
	अचिन्हित पूर्णांक pulse_start, भाग82;
	पूर्णांक retries = 1000;
	u32 value;
	पूर्णांक err;

	err = host1x_client_resume(&hdmi->client);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	/*
	 * Enable and unmask the HDA codec SCRATCH0 रेजिस्टर पूर्णांकerrupt. This
	 * is used क्रम पूर्णांकeroperability between the HDA codec driver and the
	 * HDMI driver.
	 */
	tegra_hdmi_ग_लिखोl(hdmi, INT_CODEC_SCRATCH0, HDMI_NV_PDISP_INT_ENABLE);
	tegra_hdmi_ग_लिखोl(hdmi, INT_CODEC_SCRATCH0, HDMI_NV_PDISP_INT_MASK);

	hdmi->pixel_घड़ी = mode->घड़ी * 1000;
	h_sync_width = mode->hsync_end - mode->hsync_start;
	h_back_porch = mode->htotal - mode->hsync_end;
	h_front_porch = mode->hsync_start - mode->hdisplay;

	err = clk_set_rate(hdmi->clk, hdmi->pixel_घड़ी);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to set HDMI clock frequency: %d\n",
			err);
	पूर्ण

	DRM_DEBUG_KMS("HDMI clock rate: %lu Hz\n", clk_get_rate(hdmi->clk));

	/* घातer up sequence */
	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_PLL0);
	value &= ~SOR_PLL_PDBG;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_PLL0);

	usleep_range(10, 20);

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_PLL0);
	value &= ~SOR_PLL_PWR;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_PLL0);

	tegra_dc_ग_लिखोl(dc, VSYNC_H_POSITION(1),
			DC_DISP_DISP_TIMING_OPTIONS);
	tegra_dc_ग_लिखोl(dc, DITHER_CONTROL_DISABLE | BASE_COLOR_SIZE_888,
			DC_DISP_DISP_COLOR_CONTROL);

	/* video_preamble uses h_pulse2 */
	pulse_start = 1 + h_sync_width + h_back_porch - 10;

	tegra_dc_ग_लिखोl(dc, H_PULSE2_ENABLE, DC_DISP_DISP_SIGNAL_OPTIONS0);

	value = PULSE_MODE_NORMAL | PULSE_POLARITY_HIGH | PULSE_QUAL_VACTIVE |
		PULSE_LAST_END_A;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_H_PULSE2_CONTROL);

	value = PULSE_START(pulse_start) | PULSE_END(pulse_start + 8);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_H_PULSE2_POSITION_A);

	value = VSYNC_WINDOW_END(0x210) | VSYNC_WINDOW_START(0x200) |
		VSYNC_WINDOW_ENABLE;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_VSYNC_WINDOW);

	अगर (dc->pipe)
		value = HDMI_SRC_DISPLAYB;
	अन्यथा
		value = HDMI_SRC_DISPLAYA;

	अगर ((mode->hdisplay == 720) && ((mode->vdisplay == 480) ||
					(mode->vdisplay == 576)))
		tegra_hdmi_ग_लिखोl(hdmi,
				  value | ARM_VIDEO_RANGE_FULL,
				  HDMI_NV_PDISP_INPUT_CONTROL);
	अन्यथा
		tegra_hdmi_ग_लिखोl(hdmi,
				  value | ARM_VIDEO_RANGE_LIMITED,
				  HDMI_NV_PDISP_INPUT_CONTROL);

	भाग82 = clk_get_rate(hdmi->clk) / 1000000 * 4;
	value = SOR_REFCLK_DIV_INT(भाग82 >> 2) | SOR_REFCLK_DIV_FRAC(भाग82);
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_REFCLK);

	hdmi->dvi = !tegra_output_is_hdmi(output);
	अगर (!hdmi->dvi) अणु
		/*
		 * Make sure that the audio क्रमmat has been configured beक्रमe
		 * enabling audio, otherwise we may try to भागide by zero.
		*/
		अगर (hdmi->क्रमmat.sample_rate > 0) अणु
			err = tegra_hdmi_setup_audio(hdmi);
			अगर (err < 0)
				hdmi->dvi = true;
		पूर्ण
	पूर्ण

	अगर (hdmi->config->has_hda)
		tegra_hdmi_ग_लिखो_eld(hdmi);

	rekey = HDMI_REKEY_DEFAULT;
	value = HDMI_CTRL_REKEY(rekey);
	value |= HDMI_CTRL_MAX_AC_PACKET((h_sync_width + h_back_porch +
					  h_front_porch - rekey - 18) / 32);

	अगर (!hdmi->dvi)
		value |= HDMI_CTRL_ENABLE;

	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_HDMI_CTRL);

	अगर (!hdmi->dvi) अणु
		tegra_hdmi_setup_avi_infoframe(hdmi, mode);
		tegra_hdmi_setup_audio_infoframe(hdmi);

		अगर (hdmi->stereo)
			tegra_hdmi_setup_stereo_infoframe(hdmi);
	पूर्ण

	/* TMDS CONFIG */
	क्रम (i = 0; i < hdmi->config->num_पंचांगds; i++) अणु
		अगर (hdmi->pixel_घड़ी <= hdmi->config->पंचांगds[i].pclk) अणु
			tegra_hdmi_setup_पंचांगds(hdmi, &hdmi->config->पंचांगds[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	tegra_hdmi_ग_लिखोl(hdmi,
			  SOR_SEQ_PU_PC(0) |
			  SOR_SEQ_PU_PC_ALT(0) |
			  SOR_SEQ_PD_PC(8) |
			  SOR_SEQ_PD_PC_ALT(8),
			  HDMI_NV_PDISP_SOR_SEQ_CTL);

	value = SOR_SEQ_INST_WAIT_TIME(1) |
		SOR_SEQ_INST_WAIT_UNITS_VSYNC |
		SOR_SEQ_INST_HALT |
		SOR_SEQ_INST_PIN_A_LOW |
		SOR_SEQ_INST_PIN_B_LOW |
		SOR_SEQ_INST_DRIVE_PWM_OUT_LO;

	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_SEQ_INST(0));
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_SEQ_INST(8));

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_CSTM);
	value &= ~SOR_CSTM_ROTCLK(~0);
	value |= SOR_CSTM_ROTCLK(2);
	value |= SOR_CSTM_PLLDIV;
	value &= ~SOR_CSTM_LVDS_ENABLE;
	value &= ~SOR_CSTM_MODE_MASK;
	value |= SOR_CSTM_MODE_TMDS;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_CSTM);

	/* start SOR */
	tegra_hdmi_ग_लिखोl(hdmi,
			  SOR_PWR_NORMAL_STATE_PU |
			  SOR_PWR_NORMAL_START_NORMAL |
			  SOR_PWR_SAFE_STATE_PD |
			  SOR_PWR_SETTING_NEW_TRIGGER,
			  HDMI_NV_PDISP_SOR_PWR);
	tegra_hdmi_ग_लिखोl(hdmi,
			  SOR_PWR_NORMAL_STATE_PU |
			  SOR_PWR_NORMAL_START_NORMAL |
			  SOR_PWR_SAFE_STATE_PD |
			  SOR_PWR_SETTING_NEW_DONE,
			  HDMI_NV_PDISP_SOR_PWR);

	करो अणु
		BUG_ON(--retries < 0);
		value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_PWR);
	पूर्ण जबतक (value & SOR_PWR_SETTING_NEW_PENDING);

	value = SOR_STATE_ASY_CRCMODE_COMPLETE |
		SOR_STATE_ASY_OWNER_HEAD0 |
		SOR_STATE_ASY_SUBOWNER_BOTH |
		SOR_STATE_ASY_PROTOCOL_SINGLE_TMDS_A |
		SOR_STATE_ASY_DEPOL_POS;

	/* setup sync polarities */
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		value |= SOR_STATE_ASY_HSYNCPOL_POS;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		value |= SOR_STATE_ASY_HSYNCPOL_NEG;

	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		value |= SOR_STATE_ASY_VSYNCPOL_POS;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		value |= SOR_STATE_ASY_VSYNCPOL_NEG;

	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_STATE2);

	value = SOR_STATE_ASY_HEAD_OPMODE_AWAKE | SOR_STATE_ASY_ORMODE_NORMAL;
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_SOR_STATE1);

	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_SOR_STATE0);
	tegra_hdmi_ग_लिखोl(hdmi, SOR_STATE_UPDATE, HDMI_NV_PDISP_SOR_STATE0);
	tegra_hdmi_ग_लिखोl(hdmi, value | SOR_STATE_ATTACHED,
			  HDMI_NV_PDISP_SOR_STATE1);
	tegra_hdmi_ग_लिखोl(hdmi, 0, HDMI_NV_PDISP_SOR_STATE0);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= HDMI_ENABLE;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	अगर (!hdmi->dvi) अणु
		tegra_hdmi_enable_avi_infoframe(hdmi);
		tegra_hdmi_enable_audio_infoframe(hdmi);
		tegra_hdmi_enable_audio(hdmi);

		अगर (hdmi->stereo)
			tegra_hdmi_enable_stereo_infoframe(hdmi);
	पूर्ण

	/* TODO: add HDCP support */
पूर्ण

अटल पूर्णांक
tegra_hdmi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	अचिन्हित दीर्घ pclk = crtc_state->mode.घड़ी * 1000;
	काष्ठा tegra_hdmi *hdmi = to_hdmi(output);
	पूर्णांक err;

	err = tegra_dc_state_setup_घड़ी(dc, crtc_state, hdmi->clk_parent,
					 pclk, 0);
	अगर (err < 0) अणु
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs tegra_hdmi_encoder_helper_funcs = अणु
	.disable = tegra_hdmi_encoder_disable,
	.enable = tegra_hdmi_encoder_enable,
	.atomic_check = tegra_hdmi_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक tegra_hdmi_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_hdmi *hdmi = host1x_client_to_hdmi(client);
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	पूर्णांक err;

	hdmi->output.dev = client->dev;

	drm_connector_init_with_ddc(drm, &hdmi->output.connector,
				    &tegra_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->output.ddc);
	drm_connector_helper_add(&hdmi->output.connector,
				 &tegra_hdmi_connector_helper_funcs);
	hdmi->output.connector.dpms = DRM_MODE_DPMS_OFF;

	drm_simple_encoder_init(drm, &hdmi->output.encoder,
				DRM_MODE_ENCODER_TMDS);
	drm_encoder_helper_add(&hdmi->output.encoder,
			       &tegra_hdmi_encoder_helper_funcs);

	drm_connector_attach_encoder(&hdmi->output.connector,
					  &hdmi->output.encoder);
	drm_connector_रेजिस्टर(&hdmi->output.connector);

	err = tegra_output_init(drm, &hdmi->output);
	अगर (err < 0) अणु
		dev_err(client->dev, "failed to initialize output: %d\n", err);
		वापस err;
	पूर्ण

	hdmi->output.encoder.possible_crtcs = 0x3;

	err = regulator_enable(hdmi->hdmi);
	अगर (err < 0) अणु
		dev_err(client->dev, "failed to enable HDMI regulator: %d\n",
			err);
		वापस err;
	पूर्ण

	err = regulator_enable(hdmi->pll);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to enable PLL regulator: %d\n", err);
		वापस err;
	पूर्ण

	err = regulator_enable(hdmi->vdd);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "failed to enable VDD regulator: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hdmi_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_hdmi *hdmi = host1x_client_to_hdmi(client);

	tegra_output_निकास(&hdmi->output);

	regulator_disable(hdmi->vdd);
	regulator_disable(hdmi->pll);
	regulator_disable(hdmi->hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hdmi_runसमय_suspend(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_hdmi *hdmi = host1x_client_to_hdmi(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = reset_control_निश्चित(hdmi->rst);
	अगर (err < 0) अणु
		dev_err(dev, "failed to assert reset: %d\n", err);
		वापस err;
	पूर्ण

	usleep_range(1000, 2000);

	clk_disable_unprepare(hdmi->clk);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hdmi_runसमय_resume(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_hdmi *hdmi = host1x_client_to_hdmi(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(hdmi->clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable clock: %d\n", err);
		जाओ put_rpm;
	पूर्ण

	usleep_range(1000, 2000);

	err = reset_control_deनिश्चित(hdmi->rst);
	अगर (err < 0) अणु
		dev_err(dev, "failed to deassert reset: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	वापस 0;

disable_clk:
	clk_disable_unprepare(hdmi->clk);
put_rpm:
	pm_runसमय_put_sync(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops hdmi_client_ops = अणु
	.init = tegra_hdmi_init,
	.निकास = tegra_hdmi_निकास,
	.suspend = tegra_hdmi_runसमय_suspend,
	.resume = tegra_hdmi_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा tegra_hdmi_config tegra20_hdmi_config = अणु
	.पंचांगds = tegra20_पंचांगds_config,
	.num_पंचांगds = ARRAY_SIZE(tegra20_पंचांगds_config),
	.fuse_override_offset = HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT,
	.fuse_override_value = 1 << 31,
	.has_sor_io_peak_current = false,
	.has_hda = false,
	.has_hbr = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_hdmi_config tegra30_hdmi_config = अणु
	.पंचांगds = tegra30_पंचांगds_config,
	.num_पंचांगds = ARRAY_SIZE(tegra30_पंचांगds_config),
	.fuse_override_offset = HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT,
	.fuse_override_value = 1 << 31,
	.has_sor_io_peak_current = false,
	.has_hda = true,
	.has_hbr = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_hdmi_config tegra114_hdmi_config = अणु
	.पंचांगds = tegra114_पंचांगds_config,
	.num_पंचांगds = ARRAY_SIZE(tegra114_पंचांगds_config),
	.fuse_override_offset = HDMI_NV_PDISP_SOR_PAD_CTLS0,
	.fuse_override_value = 1 << 31,
	.has_sor_io_peak_current = true,
	.has_hda = true,
	.has_hbr = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_hdmi_config tegra124_hdmi_config = अणु
	.पंचांगds = tegra124_पंचांगds_config,
	.num_पंचांगds = ARRAY_SIZE(tegra124_पंचांगds_config),
	.fuse_override_offset = HDMI_NV_PDISP_SOR_PAD_CTLS0,
	.fuse_override_value = 1 << 31,
	.has_sor_io_peak_current = true,
	.has_hda = true,
	.has_hbr = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_hdmi_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-hdmi", .data = &tegra124_hdmi_config पूर्ण,
	अणु .compatible = "nvidia,tegra114-hdmi", .data = &tegra114_hdmi_config पूर्ण,
	अणु .compatible = "nvidia,tegra30-hdmi", .data = &tegra30_hdmi_config पूर्ण,
	अणु .compatible = "nvidia,tegra20-hdmi", .data = &tegra20_hdmi_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_hdmi_of_match);

अटल irqवापस_t tegra_hdmi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_hdmi *hdmi = data;
	u32 value;
	पूर्णांक err;

	value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_INT_STATUS);
	tegra_hdmi_ग_लिखोl(hdmi, value, HDMI_NV_PDISP_INT_STATUS);

	अगर (value & INT_CODEC_SCRATCH0) अणु
		अचिन्हित पूर्णांक क्रमmat;
		u32 value;

		value = tegra_hdmi_पढ़ोl(hdmi, HDMI_NV_PDISP_SOR_AUDIO_HDA_CODEC_SCRATCH0);

		अगर (value & SOR_AUDIO_HDA_CODEC_SCRATCH0_VALID) अणु
			क्रमmat = value & SOR_AUDIO_HDA_CODEC_SCRATCH0_FMT_MASK;

			tegra_hda_parse_क्रमmat(क्रमmat, &hdmi->क्रमmat);

			err = tegra_hdmi_setup_audio(hdmi);
			अगर (err < 0) अणु
				tegra_hdmi_disable_audio_infoframe(hdmi);
				tegra_hdmi_disable_audio(hdmi);
			पूर्ण अन्यथा अणु
				tegra_hdmi_setup_audio_infoframe(hdmi);
				tegra_hdmi_enable_audio_infoframe(hdmi);
				tegra_hdmi_enable_audio(hdmi);
			पूर्ण
		पूर्ण अन्यथा अणु
			tegra_hdmi_disable_audio_infoframe(hdmi);
			tegra_hdmi_disable_audio(hdmi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *level = KERN_ERR;
	काष्ठा tegra_hdmi *hdmi;
	काष्ठा resource *regs;
	पूर्णांक err;

	hdmi = devm_kzalloc(&pdev->dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->config = of_device_get_match_data(&pdev->dev);
	hdmi->dev = &pdev->dev;

	hdmi->audio_source = AUTO;
	hdmi->stereo = false;
	hdmi->dvi = false;

	hdmi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hdmi->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(hdmi->clk);
	पूर्ण

	hdmi->rst = devm_reset_control_get(&pdev->dev, "hdmi");
	अगर (IS_ERR(hdmi->rst)) अणु
		dev_err(&pdev->dev, "failed to get reset\n");
		वापस PTR_ERR(hdmi->rst);
	पूर्ण

	hdmi->clk_parent = devm_clk_get(&pdev->dev, "parent");
	अगर (IS_ERR(hdmi->clk_parent))
		वापस PTR_ERR(hdmi->clk_parent);

	err = clk_set_parent(hdmi->clk, hdmi->clk_parent);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to setup clocks: %d\n", err);
		वापस err;
	पूर्ण

	hdmi->hdmi = devm_regulator_get(&pdev->dev, "hdmi");
	err = PTR_ERR_OR_ZERO(hdmi->hdmi);
	अगर (err) अणु
		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, &pdev->dev,
			   "failed to get HDMI regulator: %d\n", err);
		वापस err;
	पूर्ण

	hdmi->pll = devm_regulator_get(&pdev->dev, "pll");
	err = PTR_ERR_OR_ZERO(hdmi->pll);
	अगर (err) अणु
		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, &pdev->dev,
			   "failed to get PLL regulator: %d\n", err);
		वापस err;
	पूर्ण

	hdmi->vdd = devm_regulator_get(&pdev->dev, "vdd");
	err = PTR_ERR_OR_ZERO(hdmi->vdd);
	अगर (err) अणु
		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, &pdev->dev,
			   "failed to get VDD regulator: %d\n", err);
		वापस err;
	पूर्ण

	hdmi->output.dev = &pdev->dev;

	err = tegra_output_probe(&hdmi->output);
	अगर (err < 0)
		वापस err;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(hdmi->regs))
		वापस PTR_ERR(hdmi->regs);

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0)
		वापस err;

	hdmi->irq = err;

	err = devm_request_irq(hdmi->dev, hdmi->irq, tegra_hdmi_irq, 0,
			       dev_name(hdmi->dev), hdmi);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ#%u: %d\n",
			hdmi->irq, err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hdmi);
	pm_runसमय_enable(&pdev->dev);

	INIT_LIST_HEAD(&hdmi->client.list);
	hdmi->client.ops = &hdmi_client_ops;
	hdmi->client.dev = &pdev->dev;

	err = host1x_client_रेजिस्टर(&hdmi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_hdmi *hdmi = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	pm_runसमय_disable(&pdev->dev);

	err = host1x_client_unरेजिस्टर(&hdmi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	tegra_output_हटाओ(&hdmi->output);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver tegra_hdmi_driver = अणु
	.driver = अणु
		.name = "tegra-hdmi",
		.of_match_table = tegra_hdmi_of_match,
	पूर्ण,
	.probe = tegra_hdmi_probe,
	.हटाओ = tegra_hdmi_हटाओ,
पूर्ण;
