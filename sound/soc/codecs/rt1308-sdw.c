<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt1308-sdw.c -- rt1308 ALSA SoC audio driver
//
// Copyright(c) 2019 Realtek Semiconductor Corp.
//
//
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>

#समावेश "rt1308.h"
#समावेश "rt1308-sdw.h"

अटल bool rt1308_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00e0:
	हाल 0x00f0:
	हाल 0x2f01 ... 0x2f07:
	हाल 0x3000 ... 0x3001:
	हाल 0x3004 ... 0x3005:
	हाल 0x3008:
	हाल 0x300a:
	हाल 0xc000 ... 0xcff3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1308_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2f01 ... 0x2f07:
	हाल 0x3000 ... 0x3001:
	हाल 0x3004 ... 0x3005:
	हाल 0x3008:
	हाल 0x300a:
	हाल 0xc000:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt1308_sdw_regmap = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.पढ़ोable_reg = rt1308_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt1308_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0xcfff,
	.reg_शेषs = rt1308_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rt1308_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

/* Bus घड़ी frequency */
#घोषणा RT1308_CLK_FREQ_9600000HZ 9600000
#घोषणा RT1308_CLK_FREQ_12000000HZ 12000000
#घोषणा RT1308_CLK_FREQ_6000000HZ 6000000
#घोषणा RT1308_CLK_FREQ_4800000HZ 4800000
#घोषणा RT1308_CLK_FREQ_2400000HZ 2400000
#घोषणा RT1308_CLK_FREQ_12288000HZ 12288000

अटल पूर्णांक rt1308_घड़ी_config(काष्ठा device *dev)
अणु
	काष्ठा rt1308_sdw_priv *rt1308 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक clk_freq, value;

	clk_freq = (rt1308->params.curr_dr_freq >> 1);

	चयन (clk_freq) अणु
	हाल RT1308_CLK_FREQ_12000000HZ:
		value = 0x0;
		अवरोध;
	हाल RT1308_CLK_FREQ_6000000HZ:
		value = 0x1;
		अवरोध;
	हाल RT1308_CLK_FREQ_9600000HZ:
		value = 0x2;
		अवरोध;
	हाल RT1308_CLK_FREQ_4800000HZ:
		value = 0x3;
		अवरोध;
	हाल RT1308_CLK_FREQ_2400000HZ:
		value = 0x4;
		अवरोध;
	हाल RT1308_CLK_FREQ_12288000HZ:
		value = 0x5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(rt1308->regmap, 0xe0, value);
	regmap_ग_लिखो(rt1308->regmap, 0xf0, value);

	dev_dbg(dev, "%s complete, clk_freq=%d\n", __func__, clk_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval, i;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_BUS_CLASH | SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;

	prop->paging_support = true;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x00; /* BITMAP: 00010100 (not enable yet) */
	prop->sink_ports = 0x2; /* BITMAP:  00000010 */

	/* क्रम sink */
	nval = hweight32(prop->sink_ports);
	prop->sink_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
						माप(*prop->sink_dpn_prop),
						GFP_KERNEL);
	अगर (!prop->sink_dpn_prop)
		वापस -ENOMEM;

	i = 0;
	dpn = prop->sink_dpn_prop;
	addr = prop->sink_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FULL;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* set the समयout values */
	prop->clk_stop_समयout = 20;

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt1308_sdw_priv *rt1308 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक efuse_m_btl_l, efuse_m_btl_r, पंचांगp;
	अचिन्हित पूर्णांक efuse_c_btl_l, efuse_c_btl_r;

	अगर (rt1308->hw_init)
		वापस 0;

	अगर (rt1308->first_hw_init) अणु
		regcache_cache_only(rt1308->regmap, false);
		regcache_cache_bypass(rt1308->regmap, true);
	पूर्ण

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!rt1308->first_hw_init) अणु
		/* set स्वतःsuspend parameters */
		pm_runसमय_set_स्वतःsuspend_delay(&slave->dev, 3000);
		pm_runसमय_use_स्वतःsuspend(&slave->dev);

		/* update count of parent 'active' children */
		pm_runसमय_set_active(&slave->dev);

		/* make sure the device करोes not suspend immediately */
		pm_runसमय_mark_last_busy(&slave->dev);

		pm_runसमय_enable(&slave->dev);
	पूर्ण

	pm_runसमय_get_noresume(&slave->dev);

	/* sw reset */
	regmap_ग_लिखो(rt1308->regmap, RT1308_SDW_RESET, 0);

	/* पढ़ो efuse */
	regmap_ग_लिखो(rt1308->regmap, 0xc360, 0x01);
	regmap_ग_लिखो(rt1308->regmap, 0xc361, 0x80);
	regmap_ग_लिखो(rt1308->regmap, 0xc7f0, 0x04);
	regmap_ग_लिखो(rt1308->regmap, 0xc7f1, 0xfe);
	msleep(100);
	regmap_ग_लिखो(rt1308->regmap, 0xc7f0, 0x44);
	msleep(20);
	regmap_ग_लिखो(rt1308->regmap, 0xc240, 0x10);

	regmap_पढ़ो(rt1308->regmap, 0xc861, &पंचांगp);
	efuse_m_btl_l = पंचांगp;
	regmap_पढ़ो(rt1308->regmap, 0xc860, &पंचांगp);
	efuse_m_btl_l = efuse_m_btl_l | (पंचांगp << 8);
	regmap_पढ़ो(rt1308->regmap, 0xc863, &पंचांगp);
	efuse_c_btl_l = पंचांगp;
	regmap_पढ़ो(rt1308->regmap, 0xc862, &पंचांगp);
	efuse_c_btl_l = efuse_c_btl_l | (पंचांगp << 8);
	regmap_पढ़ो(rt1308->regmap, 0xc871, &पंचांगp);
	efuse_m_btl_r = पंचांगp;
	regmap_पढ़ो(rt1308->regmap, 0xc870, &पंचांगp);
	efuse_m_btl_r = efuse_m_btl_r | (पंचांगp << 8);
	regmap_पढ़ो(rt1308->regmap, 0xc873, &पंचांगp);
	efuse_c_btl_r = पंचांगp;
	regmap_पढ़ो(rt1308->regmap, 0xc872, &पंचांगp);
	efuse_c_btl_r = efuse_c_btl_r | (पंचांगp << 8);
	dev_dbg(&slave->dev, "%s m_btl_l=0x%x, m_btl_r=0x%x\n", __func__,
		efuse_m_btl_l, efuse_m_btl_r);
	dev_dbg(&slave->dev, "%s c_btl_l=0x%x, c_btl_r=0x%x\n", __func__,
		efuse_c_btl_l, efuse_c_btl_r);

	/* initial settings */
	regmap_ग_लिखो(rt1308->regmap, 0xc103, 0xc0);
	regmap_ग_लिखो(rt1308->regmap, 0xc030, 0x17);
	regmap_ग_लिखो(rt1308->regmap, 0xc031, 0x81);
	regmap_ग_लिखो(rt1308->regmap, 0xc032, 0x26);
	regmap_ग_लिखो(rt1308->regmap, 0xc040, 0x80);
	regmap_ग_लिखो(rt1308->regmap, 0xc041, 0x80);
	regmap_ग_लिखो(rt1308->regmap, 0xc042, 0x06);
	regmap_ग_लिखो(rt1308->regmap, 0xc052, 0x0a);
	regmap_ग_लिखो(rt1308->regmap, 0xc080, 0x0a);
	regmap_ग_लिखो(rt1308->regmap, 0xc060, 0x02);
	regmap_ग_लिखो(rt1308->regmap, 0xc061, 0x75);
	regmap_ग_लिखो(rt1308->regmap, 0xc062, 0x05);
	regmap_ग_लिखो(rt1308->regmap, 0xc171, 0x07);
	regmap_ग_लिखो(rt1308->regmap, 0xc173, 0x0d);
	regmap_ग_लिखो(rt1308->regmap, 0xc311, 0x7f);
	regmap_ग_लिखो(rt1308->regmap, 0xc900, 0x90);
	regmap_ग_लिखो(rt1308->regmap, 0xc1a0, 0x84);
	regmap_ग_लिखो(rt1308->regmap, 0xc1a1, 0x01);
	regmap_ग_लिखो(rt1308->regmap, 0xc360, 0x78);
	regmap_ग_लिखो(rt1308->regmap, 0xc361, 0x87);
	regmap_ग_लिखो(rt1308->regmap, 0xc0a1, 0x71);
	regmap_ग_लिखो(rt1308->regmap, 0xc210, 0x00);
	regmap_ग_लिखो(rt1308->regmap, 0xc070, 0x00);
	regmap_ग_लिखो(rt1308->regmap, 0xc100, 0xd7);
	regmap_ग_लिखो(rt1308->regmap, 0xc101, 0xd7);
	regmap_ग_लिखो(rt1308->regmap, 0xc300, 0x09);

	अगर (rt1308->first_hw_init) अणु
		regcache_cache_bypass(rt1308->regmap, false);
		regcache_mark_dirty(rt1308->regmap);
	पूर्ण अन्यथा
		rt1308->first_hw_init = true;

	/* Mark Slave initialization complete */
	rt1308->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	dev_dbg(&slave->dev, "%s hw_init complete\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक rt1308_update_status(काष्ठा sdw_slave *slave,
					क्रमागत sdw_slave_status status)
अणु
	काष्ठा  rt1308_sdw_priv *rt1308 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt1308->status = status;

	अगर (status == SDW_SLAVE_UNATTACHED)
		rt1308->hw_init = false;

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt1308->hw_init || rt1308->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt1308_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt1308_bus_config(काष्ठा sdw_slave *slave,
				काष्ठा sdw_bus_params *params)
अणु
	काष्ठा rt1308_sdw_priv *rt1308 = dev_get_drvdata(&slave->dev);
	पूर्णांक ret;

	स_नकल(&rt1308->params, params, माप(*params));

	ret = rt1308_घड़ी_config(&slave->dev);
	अगर (ret < 0)
		dev_err(&slave->dev, "Invalid clk config");

	वापस ret;
पूर्ण

अटल पूर्णांक rt1308_पूर्णांकerrupt_callback(काष्ठा sdw_slave *slave,
					काष्ठा sdw_slave_पूर्णांकr_status *status)
अणु
	dev_dbg(&slave->dev,
		"%s control_port_stat=%x", __func__, status->control_port);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_classd_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(30);
		snd_soc_component_update_bits(component,
			RT1308_SDW_OFFSET | (RT1308_POWER_STATUS << 4),
			0x3,	0x3);
		msleep(40);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component,
			RT1308_SDW_OFFSET | (RT1308_POWER_STATUS << 4),
			0x3, 0);
		usleep_range(150000, 200000);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rt1308_rx_data_ch_select[] = अणु
	"LR",
	"LL",
	"RL",
	"RR",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1308_rx_data_ch_क्रमागत,
	RT1308_SDW_OFFSET | (RT1308_DATA_PATH << 4), 0,
	rt1308_rx_data_ch_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_snd_controls[] = अणु

	/* I2S Data Channel Selection */
	SOC_ENUM("RX Channel Select", rt1308_rx_data_ch_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_sto_dac_l =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch",
		RT1308_SDW_OFFSET_BYTE3 | (RT1308_DAC_SET << 4),
		RT1308_DVOL_MUTE_L_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_sto_dac_r =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch",
		RT1308_SDW_OFFSET_BYTE3 | (RT1308_DAC_SET << 4),
		RT1308_DVOL_MUTE_R_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1308_dapm_widमाला_लो[] = अणु
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "DP1 Playback", 0, SND_SOC_NOPM, 0, 0),

	/* Supply Widमाला_लो */
	SND_SOC_DAPM_SUPPLY("MBIAS20U",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ALDO",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DBG",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DACL",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK25M",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC_R",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC_L",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Power",
		RT1308_SDW_OFFSET | (RT1308_POWER << 4),	3, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DLDO",
		RT1308_SDW_OFFSET_BYTE1 | (RT1308_POWER << 4),	5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF",
		RT1308_SDW_OFFSET_BYTE1 | (RT1308_POWER << 4),	4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIXER_R",
		RT1308_SDW_OFFSET_BYTE1 | (RT1308_POWER << 4),	2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIXER_L",
		RT1308_SDW_OFFSET_BYTE1 | (RT1308_POWER << 4),	1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS4U",
		RT1308_SDW_OFFSET_BYTE1 | (RT1308_POWER << 4),	0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("PLL2_LDO",
		RT1308_SDW_OFFSET_BYTE2 | (RT1308_POWER << 4), 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2B",
		RT1308_SDW_OFFSET_BYTE2 | (RT1308_POWER << 4), 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2F",
		RT1308_SDW_OFFSET_BYTE2 | (RT1308_POWER << 4), 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2F2",
		RT1308_SDW_OFFSET_BYTE2 | (RT1308_POWER << 4), 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2B2",
		RT1308_SDW_OFFSET_BYTE2 | (RT1308_POWER << 4), 0, 0, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("DAC L", SND_SOC_NOPM, 0, 0, &rt1308_sto_dac_l),
	SND_SOC_DAPM_SWITCH("DAC R", SND_SOC_NOPM, 0, 0, &rt1308_sto_dac_r),

	/* Output Lines */
	SND_SOC_DAPM_PGA_E("CLASS D", SND_SOC_NOPM, 0, 0, शून्य, 0,
		rt1308_classd_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1308_dapm_routes[] = अणु

	अणु "DAC", शून्य, "AIF1RX" पूर्ण,

	अणु "DAC", शून्य, "MBIAS20U" पूर्ण,
	अणु "DAC", शून्य, "ALDO" पूर्ण,
	अणु "DAC", शून्य, "DBG" पूर्ण,
	अणु "DAC", शून्य, "DACL" पूर्ण,
	अणु "DAC", शून्य, "CLK25M" पूर्ण,
	अणु "DAC", शून्य, "ADC_R" पूर्ण,
	अणु "DAC", शून्य, "ADC_L" पूर्ण,
	अणु "DAC", शून्य, "DLDO" पूर्ण,
	अणु "DAC", शून्य, "VREF" पूर्ण,
	अणु "DAC", शून्य, "MIXER_R" पूर्ण,
	अणु "DAC", शून्य, "MIXER_L" पूर्ण,
	अणु "DAC", शून्य, "MBIAS4U" पूर्ण,
	अणु "DAC", शून्य, "PLL2_LDO" पूर्ण,
	अणु "DAC", शून्य, "PLL2B" पूर्ण,
	अणु "DAC", शून्य, "PLL2F" पूर्ण,
	अणु "DAC", शून्य, "PLL2F2" पूर्ण,
	अणु "DAC", शून्य, "PLL2B2" पूर्ण,

	अणु "DAC L", "Switch", "DAC" पूर्ण,
	अणु "DAC R", "Switch", "DAC" पूर्ण,
	अणु "DAC L", शून्य, "DAC Power" पूर्ण,
	अणु "DAC R", शून्य, "DAC Power" पूर्ण,

	अणु "CLASS D", शून्य, "DAC L" पूर्ण,
	अणु "CLASS D", शून्य, "DAC R" पूर्ण,
	अणु "SPOL", शून्य, "CLASS D" पूर्ण,
	अणु "SPOR", शून्य, "CLASS D" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1308_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
				पूर्णांक direction)
अणु
	काष्ठा sdw_stream_data *stream;

	अगर (!sdw_stream)
		वापस 0;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	stream->sdw_stream = sdw_stream;

	/* Use tx_mask or rx_mask to configure stream tag and set dma_data */
	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		dai->playback_dma_data = stream;
	अन्यथा
		dai->capture_dma_data = stream;

	वापस 0;
पूर्ण

अटल व्योम rt1308_sdw_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt1308_sdw_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक tx_mask,
				   अचिन्हित पूर्णांक rx_mask,
				   पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1308_sdw_priv *rt1308 =
		snd_soc_component_get_drvdata(component);

	अगर (tx_mask)
		वापस -EINVAL;

	अगर (slots > 2)
		वापस -EINVAL;

	rt1308->rx_mask = rx_mask;
	rt1308->slots = slots;
	/* slot_width is not used since it's irrelevant क्रम SoundWire */

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_sdw_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1308_sdw_priv *rt1308 =
		snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels, ch_mask;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!rt1308->sdw_slave)
		वापस -EINVAL;

	/* SoundWire specअगरic configuration */
	/* port 1 क्रम playback */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port = 1;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (rt1308->slots) अणु
		num_channels = rt1308->slots;
		ch_mask = rt1308->rx_mask;
	पूर्ण अन्यथा अणु
		num_channels = params_channels(params);
		ch_mask = (1 << num_channels) - 1;
	पूर्ण

	stream_config.frame_rate = params_rate(params);
	stream_config.ch_count = num_channels;
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	port_config.ch_mask = ch_mask;
	port_config.num = port;

	retval = sdw_stream_add_slave(rt1308->sdw_slave, &stream_config,
				&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक rt1308_sdw_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1308_sdw_priv *rt1308 =
		snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt1308->sdw_slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt1308->sdw_slave, stream->sdw_stream);
	वापस 0;
पूर्ण

/*
 * slave_ops: callbacks क्रम get_घड़ी_stop_mode, घड़ी_stop and
 * port_prep are not defined क्रम now
 */
अटल स्थिर काष्ठा sdw_slave_ops rt1308_slave_ops = अणु
	.पढ़ो_prop = rt1308_पढ़ो_prop,
	.पूर्णांकerrupt_callback = rt1308_पूर्णांकerrupt_callback,
	.update_status = rt1308_update_status,
	.bus_config = rt1308_bus_config,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_sdw_rt1308 = अणु
	.controls = rt1308_snd_controls,
	.num_controls = ARRAY_SIZE(rt1308_snd_controls),
	.dapm_widमाला_लो = rt1308_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1308_dapm_widमाला_लो),
	.dapm_routes = rt1308_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1308_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops rt1308_aअगर_dai_ops = अणु
	.hw_params = rt1308_sdw_hw_params,
	.hw_मुक्त	= rt1308_sdw_pcm_hw_मुक्त,
	.set_sdw_stream	= rt1308_set_sdw_stream,
	.shutकरोwn	= rt1308_sdw_shutकरोwn,
	.set_tdm_slot	= rt1308_sdw_set_tdm_slot,
पूर्ण;

#घोषणा RT1308_STEREO_RATES SNDRV_PCM_RATE_48000
#घोषणा RT1308_FORMATS (SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver rt1308_sdw_dai[] = अणु
	अणु
		.name = "rt1308-aif",
		.playback = अणु
			.stream_name = "DP1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1308_STEREO_RATES,
			.क्रमmats = RT1308_FORMATS,
		पूर्ण,
		.ops = &rt1308_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt1308_sdw_init(काष्ठा device *dev, काष्ठा regmap *regmap,
				काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt1308_sdw_priv *rt1308;
	पूर्णांक ret;

	rt1308 = devm_kzalloc(dev, माप(*rt1308), GFP_KERNEL);
	अगर (!rt1308)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt1308);
	rt1308->sdw_slave = slave;
	rt1308->regmap = regmap;

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt1308->hw_init = false;
	rt1308->first_hw_init = false;

	ret =  devm_snd_soc_रेजिस्टर_component(dev,
				&soc_component_sdw_rt1308,
				rt1308_sdw_dai,
				ARRAY_SIZE(rt1308_sdw_dai));

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक rt1308_sdw_probe(काष्ठा sdw_slave *slave,
				स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *regmap;

	/* Regmap Initialization */
	regmap = devm_regmap_init_sdw(slave, &rt1308_sdw_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	rt1308_sdw_init(&slave->dev, regmap, slave);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt1308_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x1308, 0x2, 0, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt1308_id);

अटल पूर्णांक __maybe_unused rt1308_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt1308_sdw_priv *rt1308 = dev_get_drvdata(dev);

	अगर (!rt1308->hw_init)
		वापस 0;

	regcache_cache_only(rt1308->regmap, true);

	वापस 0;
पूर्ण

#घोषणा RT1308_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt1308_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt1308_sdw_priv *rt1308 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt1308->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
				msecs_to_jअगरfies(RT1308_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt1308->regmap, false);
	regcache_sync_region(rt1308->regmap, 0xc000, 0xcfff);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt1308_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt1308_dev_suspend, rt1308_dev_resume)
	SET_RUNTIME_PM_OPS(rt1308_dev_suspend, rt1308_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt1308_sdw_driver = अणु
	.driver = अणु
		.name = "rt1308",
		.owner = THIS_MODULE,
		.pm = &rt1308_pm,
	पूर्ण,
	.probe = rt1308_sdw_probe,
	.ops = &rt1308_slave_ops,
	.id_table = rt1308_id,
पूर्ण;
module_sdw_driver(rt1308_sdw_driver);

MODULE_DESCRIPTION("ASoC RT1308 driver SDW");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL v2");
