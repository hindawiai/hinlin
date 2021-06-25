<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra210_ahub.c - Tegra210 AHUB driver
//
// Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "tegra210_ahub.h"

अटल पूर्णांक tegra_ahub_get_value_क्रमागत(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_kcontrol_component(kctl);
	काष्ठा tegra_ahub *ahub = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kctl->निजी_value;
	अचिन्हित पूर्णांक reg, i, bit_pos = 0;

	/*
	 * Find the bit position of current MUX input.
	 * If nothing is set, position would be 0 and it corresponds to 'None'.
	 */
	क्रम (i = 0; i < ahub->soc_data->reg_count; i++) अणु
		अचिन्हित पूर्णांक reg_val;

		reg = e->reg + (TEGRA210_XBAR_PART1_RX * i);
		reg_val = snd_soc_component_पढ़ो(cmpnt, reg);
		reg_val &= ahub->soc_data->mask[i];

		अगर (reg_val) अणु
			bit_pos = ffs(reg_val) +
				  (8 * cmpnt->val_bytes * i);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Find index related to the item in array *_ahub_mux_texts[] */
	क्रम (i = 0; i < e->items; i++) अणु
		अगर (bit_pos == e->values[i]) अणु
			uctl->value.क्रमागतerated.item[0] = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_ahub_put_value_क्रमागत(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_kcontrol_component(kctl);
	काष्ठा tegra_ahub *ahub = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kctl);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kctl->निजी_value;
	काष्ठा snd_soc_dapm_update update[TEGRA_XBAR_UPDATE_MAX_REG] = अणु पूर्ण;
	अचिन्हित पूर्णांक *item = uctl->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक value = e->values[item[0]];
	अचिन्हित पूर्णांक i, bit_pos, reg_idx = 0, reg_val = 0;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	अगर (value) अणु
		/* Get the रेजिस्टर index and value to set */
		reg_idx = (value - 1) / (8 * cmpnt->val_bytes);
		bit_pos = (value - 1) % (8 * cmpnt->val_bytes);
		reg_val = BIT(bit_pos);
	पूर्ण

	/*
	 * Run through all parts of a MUX रेजिस्टर to find the state changes.
	 * There will be an additional update अगर new MUX input value is from
	 * dअगरferent part of the MUX रेजिस्टर.
	 */
	क्रम (i = 0; i < ahub->soc_data->reg_count; i++) अणु
		update[i].reg = e->reg + (TEGRA210_XBAR_PART1_RX * i);
		update[i].val = (i == reg_idx) ? reg_val : 0;
		update[i].mask = ahub->soc_data->mask[i];
		update[i].kcontrol = kctl;

		/* Update widget घातer अगर state has changed */
		अगर (snd_soc_component_test_bits(cmpnt, update[i].reg,
						update[i].mask, update[i].val))
			snd_soc_dapm_mux_update_घातer(dapm, kctl, item[0], e,
						      &update[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver tegra210_ahub_dais[] = अणु
	DAI(ADMAIF1),
	DAI(ADMAIF2),
	DAI(ADMAIF3),
	DAI(ADMAIF4),
	DAI(ADMAIF5),
	DAI(ADMAIF6),
	DAI(ADMAIF7),
	DAI(ADMAIF8),
	DAI(ADMAIF9),
	DAI(ADMAIF10),
	DAI(I2S1),
	DAI(I2S2),
	DAI(I2S3),
	DAI(I2S4),
	DAI(I2S5),
	DAI(DMIC1),
	DAI(DMIC2),
	DAI(DMIC3),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra186_ahub_dais[] = अणु
	DAI(ADMAIF1),
	DAI(ADMAIF2),
	DAI(ADMAIF3),
	DAI(ADMAIF4),
	DAI(ADMAIF5),
	DAI(ADMAIF6),
	DAI(ADMAIF7),
	DAI(ADMAIF8),
	DAI(ADMAIF9),
	DAI(ADMAIF10),
	DAI(ADMAIF11),
	DAI(ADMAIF12),
	DAI(ADMAIF13),
	DAI(ADMAIF14),
	DAI(ADMAIF15),
	DAI(ADMAIF16),
	DAI(ADMAIF17),
	DAI(ADMAIF18),
	DAI(ADMAIF19),
	DAI(ADMAIF20),
	DAI(I2S1),
	DAI(I2S2),
	DAI(I2S3),
	DAI(I2S4),
	DAI(I2S5),
	DAI(I2S6),
	DAI(DMIC1),
	DAI(DMIC2),
	DAI(DMIC3),
	DAI(DMIC4),
	DAI(DSPK1),
	DAI(DSPK2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_ahub_mux_texts[] = अणु
	"None",
	"ADMAIF1",
	"ADMAIF2",
	"ADMAIF3",
	"ADMAIF4",
	"ADMAIF5",
	"ADMAIF6",
	"ADMAIF7",
	"ADMAIF8",
	"ADMAIF9",
	"ADMAIF10",
	"I2S1",
	"I2S2",
	"I2S3",
	"I2S4",
	"I2S5",
	"DMIC1",
	"DMIC2",
	"DMIC3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_ahub_mux_texts[] = अणु
	"None",
	"ADMAIF1",
	"ADMAIF2",
	"ADMAIF3",
	"ADMAIF4",
	"ADMAIF5",
	"ADMAIF6",
	"ADMAIF7",
	"ADMAIF8",
	"ADMAIF9",
	"ADMAIF10",
	"ADMAIF11",
	"ADMAIF12",
	"ADMAIF13",
	"ADMAIF14",
	"ADMAIF15",
	"ADMAIF16",
	"I2S1",
	"I2S2",
	"I2S3",
	"I2S4",
	"I2S5",
	"I2S6",
	"ADMAIF17",
	"ADMAIF18",
	"ADMAIF19",
	"ADMAIF20",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra210_ahub_mux_values[] = अणु
	0,
	MUX_VALUE(0, 0),
	MUX_VALUE(0, 1),
	MUX_VALUE(0, 2),
	MUX_VALUE(0, 3),
	MUX_VALUE(0, 4),
	MUX_VALUE(0, 5),
	MUX_VALUE(0, 6),
	MUX_VALUE(0, 7),
	MUX_VALUE(0, 8),
	MUX_VALUE(0, 9),
	MUX_VALUE(0, 16),
	MUX_VALUE(0, 17),
	MUX_VALUE(0, 18),
	MUX_VALUE(0, 19),
	MUX_VALUE(0, 20),
	MUX_VALUE(2, 18),
	MUX_VALUE(2, 19),
	MUX_VALUE(2, 20),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra186_ahub_mux_values[] = अणु
	0,
	MUX_VALUE(0, 0),
	MUX_VALUE(0, 1),
	MUX_VALUE(0, 2),
	MUX_VALUE(0, 3),
	MUX_VALUE(0, 4),
	MUX_VALUE(0, 5),
	MUX_VALUE(0, 6),
	MUX_VALUE(0, 7),
	MUX_VALUE(0, 8),
	MUX_VALUE(0, 9),
	MUX_VALUE(0, 10),
	MUX_VALUE(0, 11),
	MUX_VALUE(0, 12),
	MUX_VALUE(0, 13),
	MUX_VALUE(0, 14),
	MUX_VALUE(0, 15),
	MUX_VALUE(0, 16),
	MUX_VALUE(0, 17),
	MUX_VALUE(0, 18),
	MUX_VALUE(0, 19),
	MUX_VALUE(0, 20),
	MUX_VALUE(0, 21),
	MUX_VALUE(3, 16),
	MUX_VALUE(3, 17),
	MUX_VALUE(3, 18),
	MUX_VALUE(3, 19),
	MUX_VALUE(2, 18),
	MUX_VALUE(2, 19),
	MUX_VALUE(2, 20),
	MUX_VALUE(2, 21),
पूर्ण;

/* Controls क्रम t210 */
MUX_ENUM_CTRL_DECL(t210_admaअगर1_tx, 0x00);
MUX_ENUM_CTRL_DECL(t210_admaअगर2_tx, 0x01);
MUX_ENUM_CTRL_DECL(t210_admaअगर3_tx, 0x02);
MUX_ENUM_CTRL_DECL(t210_admaअगर4_tx, 0x03);
MUX_ENUM_CTRL_DECL(t210_admaअगर5_tx, 0x04);
MUX_ENUM_CTRL_DECL(t210_admaअगर6_tx, 0x05);
MUX_ENUM_CTRL_DECL(t210_admaअगर7_tx, 0x06);
MUX_ENUM_CTRL_DECL(t210_admaअगर8_tx, 0x07);
MUX_ENUM_CTRL_DECL(t210_admaअगर9_tx, 0x08);
MUX_ENUM_CTRL_DECL(t210_admaअगर10_tx, 0x09);
MUX_ENUM_CTRL_DECL(t210_i2s1_tx, 0x10);
MUX_ENUM_CTRL_DECL(t210_i2s2_tx, 0x11);
MUX_ENUM_CTRL_DECL(t210_i2s3_tx, 0x12);
MUX_ENUM_CTRL_DECL(t210_i2s4_tx, 0x13);
MUX_ENUM_CTRL_DECL(t210_i2s5_tx, 0x14);

/* Controls क्रम t186 */
MUX_ENUM_CTRL_DECL_186(t186_admaअगर1_tx, 0x00);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर2_tx, 0x01);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर3_tx, 0x02);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर4_tx, 0x03);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर5_tx, 0x04);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर6_tx, 0x05);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर7_tx, 0x06);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर8_tx, 0x07);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर9_tx, 0x08);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर10_tx, 0x09);
MUX_ENUM_CTRL_DECL_186(t186_i2s1_tx, 0x10);
MUX_ENUM_CTRL_DECL_186(t186_i2s2_tx, 0x11);
MUX_ENUM_CTRL_DECL_186(t186_i2s3_tx, 0x12);
MUX_ENUM_CTRL_DECL_186(t186_i2s4_tx, 0x13);
MUX_ENUM_CTRL_DECL_186(t186_i2s5_tx, 0x14);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर11_tx, 0x0a);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर12_tx, 0x0b);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर13_tx, 0x0c);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर14_tx, 0x0d);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर15_tx, 0x0e);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर16_tx, 0x0f);
MUX_ENUM_CTRL_DECL_186(t186_i2s6_tx, 0x15);
MUX_ENUM_CTRL_DECL_186(t186_dspk1_tx, 0x30);
MUX_ENUM_CTRL_DECL_186(t186_dspk2_tx, 0x31);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर17_tx, 0x68);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर18_tx, 0x69);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर19_tx, 0x6a);
MUX_ENUM_CTRL_DECL_186(t186_admaअगर20_tx, 0x6b);

/*
 * The number of entries in, and order of, this array is बंदly tied to the
 * calculation of tegra210_ahub_codec.num_dapm_widमाला_लो near the end of
 * tegra210_ahub_probe()
 */
अटल स्थिर काष्ठा snd_soc_dapm_widget tegra210_ahub_widमाला_लो[] = अणु
	WIDGETS("ADMAIF1", t210_admaअगर1_tx),
	WIDGETS("ADMAIF2", t210_admaअगर2_tx),
	WIDGETS("ADMAIF3", t210_admaअगर3_tx),
	WIDGETS("ADMAIF4", t210_admaअगर4_tx),
	WIDGETS("ADMAIF5", t210_admaअगर5_tx),
	WIDGETS("ADMAIF6", t210_admaअगर6_tx),
	WIDGETS("ADMAIF7", t210_admaअगर7_tx),
	WIDGETS("ADMAIF8", t210_admaअगर8_tx),
	WIDGETS("ADMAIF9", t210_admaअगर9_tx),
	WIDGETS("ADMAIF10", t210_admaअगर10_tx),
	WIDGETS("I2S1", t210_i2s1_tx),
	WIDGETS("I2S2", t210_i2s2_tx),
	WIDGETS("I2S3", t210_i2s3_tx),
	WIDGETS("I2S4", t210_i2s4_tx),
	WIDGETS("I2S5", t210_i2s5_tx),
	TX_WIDGETS("DMIC1"),
	TX_WIDGETS("DMIC2"),
	TX_WIDGETS("DMIC3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra186_ahub_widमाला_लो[] = अणु
	WIDGETS("ADMAIF1", t186_admaअगर1_tx),
	WIDGETS("ADMAIF2", t186_admaअगर2_tx),
	WIDGETS("ADMAIF3", t186_admaअगर3_tx),
	WIDGETS("ADMAIF4", t186_admaअगर4_tx),
	WIDGETS("ADMAIF5", t186_admaअगर5_tx),
	WIDGETS("ADMAIF6", t186_admaअगर6_tx),
	WIDGETS("ADMAIF7", t186_admaअगर7_tx),
	WIDGETS("ADMAIF8", t186_admaअगर8_tx),
	WIDGETS("ADMAIF9", t186_admaअगर9_tx),
	WIDGETS("ADMAIF10", t186_admaअगर10_tx),
	WIDGETS("ADMAIF11", t186_admaअगर11_tx),
	WIDGETS("ADMAIF12", t186_admaअगर12_tx),
	WIDGETS("ADMAIF13", t186_admaअगर13_tx),
	WIDGETS("ADMAIF14", t186_admaअगर14_tx),
	WIDGETS("ADMAIF15", t186_admaअगर15_tx),
	WIDGETS("ADMAIF16", t186_admaअगर16_tx),
	WIDGETS("ADMAIF17", t186_admaअगर17_tx),
	WIDGETS("ADMAIF18", t186_admaअगर18_tx),
	WIDGETS("ADMAIF19", t186_admaअगर19_tx),
	WIDGETS("ADMAIF20", t186_admaअगर20_tx),
	WIDGETS("I2S1", t186_i2s1_tx),
	WIDGETS("I2S2", t186_i2s2_tx),
	WIDGETS("I2S3", t186_i2s3_tx),
	WIDGETS("I2S4", t186_i2s4_tx),
	WIDGETS("I2S5", t186_i2s5_tx),
	WIDGETS("I2S6", t186_i2s6_tx),
	TX_WIDGETS("DMIC1"),
	TX_WIDGETS("DMIC2"),
	TX_WIDGETS("DMIC3"),
	TX_WIDGETS("DMIC4"),
	WIDGETS("DSPK1", t186_dspk1_tx),
	WIDGETS("DSPK2", t186_dspk2_tx),
पूर्ण;

#घोषणा TEGRA_COMMON_MUX_ROUTES(name)					\
	अणु name " XBAR-TX",	 शून्य,		name " Mux" पूर्ण,		\
	अणु name " Mux",		"ADMAIF1",	"ADMAIF1 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF2",	"ADMAIF2 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF3",	"ADMAIF3 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF4",	"ADMAIF4 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF5",	"ADMAIF5 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF6",	"ADMAIF6 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF7",	"ADMAIF7 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF8",	"ADMAIF8 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF9",	"ADMAIF9 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF10",	"ADMAIF10 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S1",		"I2S1 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S2",		"I2S2 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S3",		"I2S3 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S4",		"I2S4 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S5",		"I2S5 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"DMIC1",	"DMIC1 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"DMIC2",	"DMIC2 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"DMIC3",	"DMIC3 XBAR-RX" पूर्ण,

#घोषणा TEGRA186_ONLY_MUX_ROUTES(name)					\
	अणु name " Mux",		"ADMAIF11",	"ADMAIF11 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF12",	"ADMAIF12 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF13",	"ADMAIF13 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF14",	"ADMAIF14 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF15",	"ADMAIF15 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF16",	"ADMAIF16 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF17",	"ADMAIF17 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF18",	"ADMAIF18 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF19",	"ADMAIF19 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"ADMAIF20",	"ADMAIF20 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"I2S6",		"I2S6 XBAR-RX" पूर्ण,	\
	अणु name " Mux",		"DMIC4",	"DMIC4 XBAR-RX" पूर्ण,

#घोषणा TEGRA210_MUX_ROUTES(name)						\
	TEGRA_COMMON_MUX_ROUTES(name)

#घोषणा TEGRA186_MUX_ROUTES(name)						\
	TEGRA_COMMON_MUX_ROUTES(name)					\
	TEGRA186_ONLY_MUX_ROUTES(name)

/* Connect FEs with XBAR */
#घोषणा TEGRA_FE_ROUTES(name) \
	अणु name " XBAR-Playback",	शून्य,	name " Playback" पूर्ण,	\
	अणु name " XBAR-RX",		शून्य,	name " XBAR-Playback"पूर्ण, \
	अणु name " XBAR-Capture",		शून्य,	name " XBAR-TX" पूर्ण,      \
	अणु name " Capture",		शून्य,	name " XBAR-Capture" पूर्ण,

/*
 * The number of entries in, and order of, this array is बंदly tied to the
 * calculation of tegra210_ahub_codec.num_dapm_routes near the end of
 * tegra210_ahub_probe()
 */
अटल स्थिर काष्ठा snd_soc_dapm_route tegra210_ahub_routes[] = अणु
	TEGRA_FE_ROUTES("ADMAIF1")
	TEGRA_FE_ROUTES("ADMAIF2")
	TEGRA_FE_ROUTES("ADMAIF3")
	TEGRA_FE_ROUTES("ADMAIF4")
	TEGRA_FE_ROUTES("ADMAIF5")
	TEGRA_FE_ROUTES("ADMAIF6")
	TEGRA_FE_ROUTES("ADMAIF7")
	TEGRA_FE_ROUTES("ADMAIF8")
	TEGRA_FE_ROUTES("ADMAIF9")
	TEGRA_FE_ROUTES("ADMAIF10")
	TEGRA210_MUX_ROUTES("ADMAIF1")
	TEGRA210_MUX_ROUTES("ADMAIF2")
	TEGRA210_MUX_ROUTES("ADMAIF3")
	TEGRA210_MUX_ROUTES("ADMAIF4")
	TEGRA210_MUX_ROUTES("ADMAIF5")
	TEGRA210_MUX_ROUTES("ADMAIF6")
	TEGRA210_MUX_ROUTES("ADMAIF7")
	TEGRA210_MUX_ROUTES("ADMAIF8")
	TEGRA210_MUX_ROUTES("ADMAIF9")
	TEGRA210_MUX_ROUTES("ADMAIF10")
	TEGRA210_MUX_ROUTES("I2S1")
	TEGRA210_MUX_ROUTES("I2S2")
	TEGRA210_MUX_ROUTES("I2S3")
	TEGRA210_MUX_ROUTES("I2S4")
	TEGRA210_MUX_ROUTES("I2S5")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tegra186_ahub_routes[] = अणु
	TEGRA_FE_ROUTES("ADMAIF1")
	TEGRA_FE_ROUTES("ADMAIF2")
	TEGRA_FE_ROUTES("ADMAIF3")
	TEGRA_FE_ROUTES("ADMAIF4")
	TEGRA_FE_ROUTES("ADMAIF5")
	TEGRA_FE_ROUTES("ADMAIF6")
	TEGRA_FE_ROUTES("ADMAIF7")
	TEGRA_FE_ROUTES("ADMAIF8")
	TEGRA_FE_ROUTES("ADMAIF9")
	TEGRA_FE_ROUTES("ADMAIF10")
	TEGRA_FE_ROUTES("ADMAIF11")
	TEGRA_FE_ROUTES("ADMAIF12")
	TEGRA_FE_ROUTES("ADMAIF13")
	TEGRA_FE_ROUTES("ADMAIF14")
	TEGRA_FE_ROUTES("ADMAIF15")
	TEGRA_FE_ROUTES("ADMAIF16")
	TEGRA_FE_ROUTES("ADMAIF17")
	TEGRA_FE_ROUTES("ADMAIF18")
	TEGRA_FE_ROUTES("ADMAIF19")
	TEGRA_FE_ROUTES("ADMAIF20")
	TEGRA186_MUX_ROUTES("ADMAIF1")
	TEGRA186_MUX_ROUTES("ADMAIF2")
	TEGRA186_MUX_ROUTES("ADMAIF3")
	TEGRA186_MUX_ROUTES("ADMAIF4")
	TEGRA186_MUX_ROUTES("ADMAIF5")
	TEGRA186_MUX_ROUTES("ADMAIF6")
	TEGRA186_MUX_ROUTES("ADMAIF7")
	TEGRA186_MUX_ROUTES("ADMAIF8")
	TEGRA186_MUX_ROUTES("ADMAIF9")
	TEGRA186_MUX_ROUTES("ADMAIF10")
	TEGRA186_MUX_ROUTES("ADMAIF11")
	TEGRA186_MUX_ROUTES("ADMAIF12")
	TEGRA186_MUX_ROUTES("ADMAIF13")
	TEGRA186_MUX_ROUTES("ADMAIF14")
	TEGRA186_MUX_ROUTES("ADMAIF15")
	TEGRA186_MUX_ROUTES("ADMAIF16")
	TEGRA186_MUX_ROUTES("ADMAIF17")
	TEGRA186_MUX_ROUTES("ADMAIF18")
	TEGRA186_MUX_ROUTES("ADMAIF19")
	TEGRA186_MUX_ROUTES("ADMAIF20")
	TEGRA186_MUX_ROUTES("I2S1")
	TEGRA186_MUX_ROUTES("I2S2")
	TEGRA186_MUX_ROUTES("I2S3")
	TEGRA186_MUX_ROUTES("I2S4")
	TEGRA186_MUX_ROUTES("I2S5")
	TEGRA186_MUX_ROUTES("I2S6")
	TEGRA186_MUX_ROUTES("DSPK1")
	TEGRA186_MUX_ROUTES("DSPK2")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra210_ahub_component = अणु
	.dapm_widमाला_लो		= tegra210_ahub_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tegra210_ahub_widमाला_लो),
	.dapm_routes		= tegra210_ahub_routes,
	.num_dapm_routes	= ARRAY_SIZE(tegra210_ahub_routes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra186_ahub_component = अणु
	.dapm_widमाला_लो = tegra186_ahub_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra186_ahub_widमाला_लो),
	.dapm_routes = tegra186_ahub_routes,
	.num_dapm_routes = ARRAY_SIZE(tegra186_ahub_routes),
पूर्ण;

अटल स्थिर काष्ठा regmap_config tegra210_ahub_regmap_config = अणु
	.reg_bits		= 32,
	.val_bits		= 32,
	.reg_stride		= 4,
	.max_रेजिस्टर		= TEGRA210_MAX_REGISTER_ADDR,
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tegra186_ahub_regmap_config = अणु
	.reg_bits		= 32,
	.val_bits		= 32,
	.reg_stride		= 4,
	.max_रेजिस्टर		= TEGRA186_MAX_REGISTER_ADDR,
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा tegra_ahub_soc_data soc_data_tegra210 = अणु
	.cmpnt_drv	= &tegra210_ahub_component,
	.dai_drv	= tegra210_ahub_dais,
	.num_dais	= ARRAY_SIZE(tegra210_ahub_dais),
	.regmap_config	= &tegra210_ahub_regmap_config,
	.mask[0]	= TEGRA210_XBAR_REG_MASK_0,
	.mask[1]	= TEGRA210_XBAR_REG_MASK_1,
	.mask[2]	= TEGRA210_XBAR_REG_MASK_2,
	.mask[3]	= TEGRA210_XBAR_REG_MASK_3,
	.reg_count	= TEGRA210_XBAR_UPDATE_MAX_REG,
पूर्ण;

अटल स्थिर काष्ठा tegra_ahub_soc_data soc_data_tegra186 = अणु
	.cmpnt_drv	= &tegra186_ahub_component,
	.dai_drv	= tegra186_ahub_dais,
	.num_dais	= ARRAY_SIZE(tegra186_ahub_dais),
	.regmap_config	= &tegra186_ahub_regmap_config,
	.mask[0]	= TEGRA186_XBAR_REG_MASK_0,
	.mask[1]	= TEGRA186_XBAR_REG_MASK_1,
	.mask[2]	= TEGRA186_XBAR_REG_MASK_2,
	.mask[3]	= TEGRA186_XBAR_REG_MASK_3,
	.reg_count	= TEGRA186_XBAR_UPDATE_MAX_REG,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_ahub_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-ahub", .data = &soc_data_tegra210 पूर्ण,
	अणु .compatible = "nvidia,tegra186-ahub", .data = &soc_data_tegra186 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_ahub_of_match);

अटल पूर्णांक __maybe_unused tegra_ahub_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_ahub *ahub = dev_get_drvdata(dev);

	regcache_cache_only(ahub->regmap, true);
	regcache_mark_dirty(ahub->regmap);

	clk_disable_unprepare(ahub->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_ahub_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_ahub *ahub = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(ahub->clk);
	अगर (err) अणु
		dev_err(dev, "failed to enable AHUB clock, err: %d\n", err);
		वापस err;
	पूर्ण

	regcache_cache_only(ahub->regmap, false);
	regcache_sync(ahub->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_ahub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_ahub *ahub;
	व्योम __iomem *regs;
	पूर्णांक err;

	ahub = devm_kzalloc(&pdev->dev, माप(*ahub), GFP_KERNEL);
	अगर (!ahub)
		वापस -ENOMEM;

	ahub->soc_data = of_device_get_match_data(&pdev->dev);

	platक्रमm_set_drvdata(pdev, ahub);

	ahub->clk = devm_clk_get(&pdev->dev, "ahub");
	अगर (IS_ERR(ahub->clk)) अणु
		dev_err(&pdev->dev, "can't retrieve AHUB clock\n");
		वापस PTR_ERR(ahub->clk);
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	ahub->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					     ahub->soc_data->regmap_config);
	अगर (IS_ERR(ahub->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		वापस PTR_ERR(ahub->regmap);
	पूर्ण

	regcache_cache_only(ahub->regmap, true);

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      ahub->soc_data->cmpnt_drv,
					      ahub->soc_data->dai_drv,
					      ahub->soc_data->num_dais);
	अगर (err) अणु
		dev_err(&pdev->dev, "can't register AHUB component, err: %d\n",
			err);
		वापस err;
	पूर्ण

	err = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (err)
		वापस err;

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_ahub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_ahub_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_ahub_runसमय_suspend,
			   tegra_ahub_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_ahub_driver = अणु
	.probe = tegra_ahub_probe,
	.हटाओ = tegra_ahub_हटाओ,
	.driver = अणु
		.name = "tegra210-ahub",
		.of_match_table = tegra_ahub_of_match,
		.pm = &tegra_ahub_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_ahub_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_AUTHOR("Mohan Kumar <mkumard@nvidia.com>");
MODULE_DESCRIPTION("Tegra210 ASoC AHUB driver");
MODULE_LICENSE("GPL v2");
