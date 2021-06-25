<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, 2013, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/clk/tegra.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

#घोषणा AUDIO_SYNC_CLK_I2S0 0x4a0
#घोषणा AUDIO_SYNC_CLK_I2S1 0x4a4
#घोषणा AUDIO_SYNC_CLK_I2S2 0x4a8
#घोषणा AUDIO_SYNC_CLK_I2S3 0x4ac
#घोषणा AUDIO_SYNC_CLK_I2S4 0x4b0
#घोषणा AUDIO_SYNC_CLK_SPDIF 0x4b4
#घोषणा AUDIO_SYNC_CLK_DMIC1 0x560
#घोषणा AUDIO_SYNC_CLK_DMIC2 0x564
#घोषणा AUDIO_SYNC_CLK_DMIC3 0x6b8

#घोषणा AUDIO_SYNC_DOUBLER 0x49c

#घोषणा PLLA_OUT 0xb4

काष्ठा tegra_sync_source_initdata अणु
	अक्षर		*name;
	अचिन्हित दीर्घ	rate;
	अचिन्हित दीर्घ	max_rate;
	पूर्णांक		clk_id;
पूर्ण;

#घोषणा SYNC(_name) \
	अणु\
		.name		= #_name,\
		.clk_id		= tegra_clk_ ## _name,\
	पूर्ण

काष्ठा tegra_audio_clk_initdata अणु
	अक्षर		*gate_name;
	अक्षर		*mux_name;
	u32		offset;
	पूर्णांक		gate_clk_id;
	पूर्णांक		mux_clk_id;
पूर्ण;

#घोषणा AUDIO(_name, _offset) \
	अणु\
		.gate_name	= #_name,\
		.mux_name	= #_name"_mux",\
		.offset		= _offset,\
		.gate_clk_id	= tegra_clk_ ## _name,\
		.mux_clk_id	= tegra_clk_ ## _name ## _mux,\
	पूर्ण

काष्ठा tegra_audio2x_clk_initdata अणु
	अक्षर		*parent;
	अक्षर		*gate_name;
	अक्षर		*name_2x;
	अक्षर		*भाग_name;
	पूर्णांक		clk_id;
	पूर्णांक		clk_num;
	u8		भाग_offset;
पूर्ण;

#घोषणा AUDIO2X(_name, _num, _offset) \
	अणु\
		.parent		= #_name,\
		.gate_name	= #_name"_2x",\
		.name_2x	= #_name"_doubler",\
		.भाग_name	= #_name"_div",\
		.clk_id		= tegra_clk_ ## _name ## _2x,\
		.clk_num	= _num,\
		.भाग_offset	= _offset,\
	पूर्ण

अटल DEFINE_SPINLOCK(clk_द्विगुनr_lock);

अटल स्थिर अक्षर * स्थिर mux_audio_sync_clk[] = अणु "spdif_in_sync",
	"i2s0_sync", "i2s1_sync", "i2s2_sync", "i2s3_sync", "i2s4_sync",
	"pll_a_out0", "vimclk_sync",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mux_dmic_sync_clk[] = अणु "unused", "i2s0_sync",
	"i2s1_sync", "i2s2_sync", "i2s3_sync", "i2s4_sync", "pll_a_out0",
	"vimclk_sync",
पूर्ण;

अटल काष्ठा tegra_sync_source_initdata sync_source_clks[] __initdata = अणु
	SYNC(spdअगर_in_sync),
	SYNC(i2s0_sync),
	SYNC(i2s1_sync),
	SYNC(i2s2_sync),
	SYNC(i2s3_sync),
	SYNC(i2s4_sync),
	SYNC(vimclk_sync),
पूर्ण;

अटल काष्ठा tegra_audio_clk_initdata audio_clks[] = अणु
	AUDIO(audio0, AUDIO_SYNC_CLK_I2S0),
	AUDIO(audio1, AUDIO_SYNC_CLK_I2S1),
	AUDIO(audio2, AUDIO_SYNC_CLK_I2S2),
	AUDIO(audio3, AUDIO_SYNC_CLK_I2S3),
	AUDIO(audio4, AUDIO_SYNC_CLK_I2S4),
	AUDIO(spdअगर, AUDIO_SYNC_CLK_SPDIF),
पूर्ण;

अटल काष्ठा tegra_audio_clk_initdata dmic_clks[] = अणु
	AUDIO(dmic1_sync_clk, AUDIO_SYNC_CLK_DMIC1),
	AUDIO(dmic2_sync_clk, AUDIO_SYNC_CLK_DMIC2),
	AUDIO(dmic3_sync_clk, AUDIO_SYNC_CLK_DMIC3),
पूर्ण;

अटल काष्ठा tegra_audio2x_clk_initdata audio2x_clks[] = अणु
	AUDIO2X(audio0, 113, 24),
	AUDIO2X(audio1, 114, 25),
	AUDIO2X(audio2, 115, 26),
	AUDIO2X(audio3, 116, 27),
	AUDIO2X(audio4, 117, 28),
	AUDIO2X(spdअगर, 118, 29),
पूर्ण;

अटल व्योम __init tegra_audio_sync_clk_init(व्योम __iomem *clk_base,
				      काष्ठा tegra_clk *tegra_clks,
				      काष्ठा tegra_audio_clk_initdata *sync,
				      पूर्णांक num_sync_clks,
				      स्थिर अक्षर * स्थिर *mux_names,
				      पूर्णांक num_mux_inमाला_दो)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **dt_clk;
	काष्ठा tegra_audio_clk_initdata *data;
	पूर्णांक i;

	क्रम (i = 0, data = sync; i < num_sync_clks; i++, data++) अणु
		dt_clk = tegra_lookup_dt_id(data->mux_clk_id, tegra_clks);
		अगर (!dt_clk)
			जारी;

		clk = clk_रेजिस्टर_mux(शून्य, data->mux_name, mux_names,
					num_mux_inमाला_दो,
					CLK_SET_RATE_NO_REPARENT,
					clk_base + data->offset, 0, 3, 0,
					शून्य);
		*dt_clk = clk;

		dt_clk = tegra_lookup_dt_id(data->gate_clk_id, tegra_clks);
		अगर (!dt_clk)
			जारी;

		clk = clk_रेजिस्टर_gate(शून्य, data->gate_name, data->mux_name,
					0, clk_base + data->offset, 4,
					CLK_GATE_SET_TO_DISABLE, शून्य);
		*dt_clk = clk;
	पूर्ण
पूर्ण

व्योम __init tegra_audio_clk_init(व्योम __iomem *clk_base,
			व्योम __iomem *pmc_base, काष्ठा tegra_clk *tegra_clks,
			काष्ठा tegra_audio_clk_info *audio_info,
			अचिन्हित पूर्णांक num_plls, अचिन्हित दीर्घ sync_max_rate)
अणु
	काष्ठा clk *clk;
	काष्ठा clk **dt_clk;
	पूर्णांक i;

	अगर (!audio_info || num_plls < 1) अणु
		pr_err("No audio data passed to tegra_audio_clk_init\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_plls; i++) अणु
		काष्ठा tegra_audio_clk_info *info = &audio_info[i];

		dt_clk = tegra_lookup_dt_id(info->clk_id, tegra_clks);
		अगर (dt_clk) अणु
			clk = tegra_clk_रेजिस्टर_pll(info->name, info->parent,
					clk_base, pmc_base, 0, info->pll_params,
					शून्य);
			*dt_clk = clk;
		पूर्ण
	पूर्ण

	/* PLLA_OUT0 */
	dt_clk = tegra_lookup_dt_id(tegra_clk_pll_a_out0, tegra_clks);
	अगर (dt_clk) अणु
		clk = tegra_clk_रेजिस्टर_भागider("pll_a_out0_div", "pll_a",
				clk_base + PLLA_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, शून्य);
		clk = tegra_clk_रेजिस्टर_pll_out("pll_a_out0", "pll_a_out0_div",
				clk_base + PLLA_OUT, 1, 0, CLK_IGNORE_UNUSED |
				CLK_SET_RATE_PARENT, 0, शून्य);
		*dt_clk = clk;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sync_source_clks); i++) अणु
		काष्ठा tegra_sync_source_initdata *data;

		data = &sync_source_clks[i];

		dt_clk = tegra_lookup_dt_id(data->clk_id, tegra_clks);
		अगर (!dt_clk)
			जारी;

		clk = tegra_clk_रेजिस्टर_sync_source(data->name, sync_max_rate);
		*dt_clk = clk;
	पूर्ण

	tegra_audio_sync_clk_init(clk_base, tegra_clks, audio_clks,
				  ARRAY_SIZE(audio_clks), mux_audio_sync_clk,
				  ARRAY_SIZE(mux_audio_sync_clk));

	/* make sure the DMIC sync घड़ीs have a valid parent */
	क्रम (i = 0; i < ARRAY_SIZE(dmic_clks); i++)
		ग_लिखोl_relaxed(1, clk_base + dmic_clks[i].offset);

	tegra_audio_sync_clk_init(clk_base, tegra_clks, dmic_clks,
				  ARRAY_SIZE(dmic_clks), mux_dmic_sync_clk,
				  ARRAY_SIZE(mux_dmic_sync_clk));

	क्रम (i = 0; i < ARRAY_SIZE(audio2x_clks); i++) अणु
		काष्ठा tegra_audio2x_clk_initdata *data;

		data = &audio2x_clks[i];
		dt_clk = tegra_lookup_dt_id(data->clk_id, tegra_clks);
		अगर (!dt_clk)
			जारी;

		clk = clk_रेजिस्टर_fixed_factor(शून्य, data->name_2x,
				data->parent, CLK_SET_RATE_PARENT, 2, 1);
		clk = tegra_clk_रेजिस्टर_भागider(data->भाग_name,
				data->name_2x, clk_base + AUDIO_SYNC_DOUBLER,
				0, 0, data->भाग_offset, 1, 0,
				&clk_द्विगुनr_lock);
		clk = tegra_clk_रेजिस्टर_periph_gate(data->gate_name,
				data->भाग_name, TEGRA_PERIPH_NO_RESET,
				clk_base, CLK_SET_RATE_PARENT, data->clk_num,
				periph_clk_enb_refcnt);
		*dt_clk = clk;
	पूर्ण
पूर्ण

