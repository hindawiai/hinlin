<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt1316-sdw.c -- rt1316 SDCA ALSA SoC amplअगरier audio driver
//
// Copyright(c) 2021 Realtek Semiconductor Corp.
//
//
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश "rt1316-sdw.h"

अटल स्थिर काष्ठा reg_शेष rt1316_reg_शेषs[] = अणु
	अणु 0x3004, 0x00 पूर्ण,
	अणु 0x3005, 0x00 पूर्ण,
	अणु 0x3206, 0x00 पूर्ण,
	अणु 0xc001, 0x00 पूर्ण,
	अणु 0xc002, 0x00 पूर्ण,
	अणु 0xc003, 0x00 पूर्ण,
	अणु 0xc004, 0x00 पूर्ण,
	अणु 0xc005, 0x00 पूर्ण,
	अणु 0xc006, 0x00 पूर्ण,
	अणु 0xc007, 0x00 पूर्ण,
	अणु 0xc008, 0x00 पूर्ण,
	अणु 0xc009, 0x00 पूर्ण,
	अणु 0xc00a, 0x00 पूर्ण,
	अणु 0xc00b, 0x00 पूर्ण,
	अणु 0xc00c, 0x00 पूर्ण,
	अणु 0xc00d, 0x00 पूर्ण,
	अणु 0xc00e, 0x00 पूर्ण,
	अणु 0xc00f, 0x00 पूर्ण,
	अणु 0xc010, 0xa5 पूर्ण,
	अणु 0xc011, 0x00 पूर्ण,
	अणु 0xc012, 0xff पूर्ण,
	अणु 0xc013, 0xff पूर्ण,
	अणु 0xc014, 0x40 पूर्ण,
	अणु 0xc015, 0x00 पूर्ण,
	अणु 0xc016, 0x00 पूर्ण,
	अणु 0xc017, 0x00 पूर्ण,
	अणु 0xc605, 0x30 पूर्ण,
	अणु 0xc700, 0x0a पूर्ण,
	अणु 0xc701, 0xaa पूर्ण,
	अणु 0xc702, 0x1a पूर्ण,
	अणु 0xc703, 0x0a पूर्ण,
	अणु 0xc710, 0x80 पूर्ण,
	अणु 0xc711, 0x00 पूर्ण,
	अणु 0xc712, 0x3e पूर्ण,
	अणु 0xc713, 0x80 पूर्ण,
	अणु 0xc714, 0x80 पूर्ण,
	अणु 0xc715, 0x06 पूर्ण,
	अणु 0xd101, 0x00 पूर्ण,
	अणु 0xd102, 0x30 पूर्ण,
	अणु 0xd103, 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_UDMPU21, RT1316_SDCA_CTL_UDMPU_CLUSTER, 0), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_L), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_R), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_XU24, RT1316_SDCA_CTL_BYPASS, 0), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE23, RT1316_SDCA_CTL_REQ_POWER_STATE, 0), 0x03 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE22, RT1316_SDCA_CTL_REQ_POWER_STATE, 0), 0x03 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE24, RT1316_SDCA_CTL_REQ_POWER_STATE, 0), 0x03 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence rt1316_blind_ग_लिखो[] = अणु
	अणु 0xc710, 0x17 पूर्ण,
	अणु 0xc711, 0x80 पूर्ण,
	अणु 0xc712, 0x26 पूर्ण,
	अणु 0xc713, 0x06 पूर्ण,
	अणु 0xc714, 0x80 पूर्ण,
	अणु 0xc715, 0x06 पूर्ण,
	अणु 0xc702, 0x0a पूर्ण,
	अणु 0xc703, 0x0a पूर्ण,
	अणु 0xc001, 0x45 पूर्ण,
	अणु 0xc003, 0x00 पूर्ण,
	अणु 0xc004, 0x11 पूर्ण,
	अणु 0xc005, 0x00 पूर्ण,
	अणु 0xc006, 0x00 पूर्ण,
	अणु 0xc106, 0x00 पूर्ण,
	अणु 0xc007, 0x11 पूर्ण,
	अणु 0xc008, 0x11 पूर्ण,
	अणु 0xc009, 0x00 पूर्ण,

	अणु 0x2f0a, 0x00 पूर्ण,
	अणु 0xd101, 0xf0 पूर्ण,
	अणु 0xd103, 0x9b पूर्ण,
	अणु 0x2f36, 0x8e पूर्ण,
	अणु 0x3206, 0x80 पूर्ण,
	अणु 0x3211, 0x0b पूर्ण,
	अणु 0x3216, 0x06 पूर्ण,
	अणु 0xc614, 0x20 पूर्ण,
	अणु 0xc615, 0x0a पूर्ण,
	अणु 0xc616, 0x02 पूर्ण,
	अणु 0xc617, 0x00 पूर्ण,
	अणु 0xc60b, 0x10 पूर्ण,
	अणु 0xc60e, 0x05 पूर्ण,
	अणु 0xc102, 0x00 पूर्ण,
	अणु 0xc090, 0xb0 पूर्ण,
	अणु 0xc00f, 0x01 पूर्ण,
	अणु 0xc09c, 0x7b पूर्ण,

	अणु 0xc602, 0x07 पूर्ण,
	अणु 0xc603, 0x07 पूर्ण,
	अणु 0xc0a3, 0x71 पूर्ण,
	अणु 0xc00b, 0x30 पूर्ण,
	अणु 0xc093, 0x80 पूर्ण,
	अणु 0xc09d, 0x80 पूर्ण,
	अणु 0xc0b0, 0x77 पूर्ण,
	अणु 0xc010, 0xa5 पूर्ण,
	अणु 0xc050, 0x83 पूर्ण,
	अणु 0x2f55, 0x03 पूर्ण,
	अणु 0x3217, 0xb5 पूर्ण,
	अणु 0x3202, 0x02 पूर्ण,

	अणु SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_XU24, RT1316_SDCA_CTL_BYPASS, 0), 0x00 पूर्ण,

	/* क्रम IV sense */
	अणु 0x2232, 0x80 पूर्ण,
	अणु 0xc0b0, 0x77 पूर्ण,
	अणु 0xc011, 0x00 पूर्ण,
	अणु 0xc020, 0x00 पूर्ण,
	अणु 0xc023, 0x00 पूर्ण,
	अणु 0x3101, 0x00 पूर्ण,
	अणु 0x3004, 0xa0 पूर्ण,
	अणु 0x3005, 0xb1 पूर्ण,
	अणु 0xc007, 0x11 पूर्ण,
	अणु 0xc008, 0x11 पूर्ण,
	अणु 0xc009, 0x00 पूर्ण,
	अणु 0xc022, 0xd6 पूर्ण,
	अणु 0xc025, 0xd6 पूर्ण,

	अणु 0xd001, 0x03 पूर्ण,
	अणु 0xd002, 0xbf पूर्ण,
	अणु 0xd003, 0x03 पूर्ण,
	अणु 0xd004, 0xbf पूर्ण,
पूर्ण;

अटल bool rt1316_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2f0a:
	हाल 0x2f36:
	हाल 0x3203 ... 0x320e:
	हाल 0xc000 ... 0xc7b4:
	हाल 0xcf00 ... 0xcf03:
	हाल 0xd101 ... 0xd103:
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_UDMPU21, RT1316_SDCA_CTL_UDMPU_CLUSTER, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_L):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_R):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE23, RT1316_SDCA_CTL_REQ_POWER_STATE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE27, RT1316_SDCA_CTL_REQ_POWER_STATE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE22, RT1316_SDCA_CTL_REQ_POWER_STATE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE24, RT1316_SDCA_CTL_REQ_POWER_STATE, 0):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1316_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0xc000:
	हाल 0xc093:
	हाल 0xc09d:
	हाल 0xc0a3:
	हाल 0xc201:
	हाल 0xc427 ... 0xc428:
	हाल 0xd102:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt1316_sdw_regmap = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.पढ़ोable_reg = rt1316_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt1316_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x4108ffff,
	.reg_शेषs = rt1316_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rt1316_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक rt1316_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval;
	पूर्णांक i, j;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_BUS_CLASH | SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;
	prop->is_sdca = true;

	prop->paging_support = true;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x04; /* BITMAP: 00000100 */
	prop->sink_ports = 0x2; /* BITMAP:  00000010 */

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
		माप(*prop->src_dpn_prop), GFP_KERNEL);
	अगर (!prop->src_dpn_prop)
		वापस -ENOMEM;

	i = 0;
	dpn = prop->src_dpn_prop;
	addr = prop->source_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FULL;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* करो this again क्रम sink now */
	nval = hweight32(prop->sink_ports);
	prop->sink_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
		माप(*prop->sink_dpn_prop), GFP_KERNEL);
	अगर (!prop->sink_dpn_prop)
		वापस -ENOMEM;

	j = 0;
	dpn = prop->sink_dpn_prop;
	addr = prop->sink_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[j].num = bit;
		dpn[j].type = SDW_DPN_FULL;
		dpn[j].simple_ch_prep_sm = true;
		dpn[j].ch_prep_समयout = 10;
		j++;
	पूर्ण

	/* set the समयout values */
	prop->clk_stop_समयout = 20;

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1316_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt1316_sdw_priv *rt1316 = dev_get_drvdata(dev);

	अगर (rt1316->hw_init)
		वापस 0;

	अगर (rt1316->first_hw_init) अणु
		regcache_cache_only(rt1316->regmap, false);
		regcache_cache_bypass(rt1316->regmap, true);
	पूर्ण अन्यथा अणु
		/*
		 * PM runसमय is only enabled when a Slave reports as Attached
		 */

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
	regmap_ग_लिखो(rt1316->regmap, 0xc000, 0x02);

	/* initial settings - blind ग_लिखो */
	regmap_multi_reg_ग_लिखो(rt1316->regmap, rt1316_blind_ग_लिखो,
		ARRAY_SIZE(rt1316_blind_ग_लिखो));

	अगर (rt1316->first_hw_init) अणु
		regcache_cache_bypass(rt1316->regmap, false);
		regcache_mark_dirty(rt1316->regmap);
	पूर्ण अन्यथा
		rt1316->first_hw_init = true;

	/* Mark Slave initialization complete */
	rt1316->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	dev_dbg(&slave->dev, "%s hw_init complete\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक rt1316_update_status(काष्ठा sdw_slave *slave,
					क्रमागत sdw_slave_status status)
अणु
	काष्ठा  rt1316_sdw_priv *rt1316 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt1316->status = status;

	अगर (status == SDW_SLAVE_UNATTACHED)
		rt1316->hw_init = false;

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt1316->hw_init || rt1316->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt1316_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt1316_classd_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt1316_sdw_priv *rt1316 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE23,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE27,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE22,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE23,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE27,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE22,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt1316_pde24_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt1316_sdw_priv *rt1316 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE24,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt1316->regmap,
			SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_PDE24,
				RT1316_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rt1316_rx_data_ch_select[] = अणु
	"L,R",
	"L,L",
	"L,R",
	"L,L+R",
	"R,L",
	"R,R",
	"R,L+R",
	"L+R,L",
	"L+R,R",
	"L+R,L+R",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1316_rx_data_ch_क्रमागत,
	SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_UDMPU21, RT1316_SDCA_CTL_UDMPU_CLUSTER, 0), 0,
	rt1316_rx_data_ch_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt1316_snd_controls[] = अणु

	/* I2S Data Channel Selection */
	SOC_ENUM("RX Channel Select", rt1316_rx_data_ch_क्रमागत),

	/* XU24 Bypass Control */
	SOC_SINGLE("XU24 Bypass Switch",
		SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_XU24, RT1316_SDCA_CTL_BYPASS, 0), 0, 1, 0),

	/* Left/Right IV tag */
	SOC_SINGLE("Left V Tag Select", 0x3004, 0, 7, 0),
	SOC_SINGLE("Left I Tag Select", 0x3004, 4, 7, 0),
	SOC_SINGLE("Right V Tag Select", 0x3005, 0, 7, 0),
	SOC_SINGLE("Right I Tag Select", 0x3005, 4, 7, 0),

	/* IV mixer Control */
	SOC_DOUBLE("Isense Mixer Switch", 0xc605, 2, 0, 1, 1),
	SOC_DOUBLE("Vsense Mixer Switch", 0xc605, 3, 1, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt1316_sto_dac =
	SOC_DAPM_DOUBLE_R("Switch",
		SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_SMART_AMP, RT1316_SDCA_ENT_FU21, RT1316_SDCA_CTL_FU_MUTE, CH_R),
		0, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1316_dapm_widमाला_लो[] = अणु
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("DP1RX", "DP1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SWITCH("DAC", SND_SOC_NOPM, 0, 0, &rt1316_sto_dac),

	/* Output Lines */
	SND_SOC_DAPM_PGA_E("CLASS D", SND_SOC_NOPM, 0, 0, शून्य, 0,
		rt1316_classd_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),

	SND_SOC_DAPM_SUPPLY("PDE 24", SND_SOC_NOPM, 0, 0,
		rt1316_pde24_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA("I Sense", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("V Sense", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SIGGEN("I Gen"),
	SND_SOC_DAPM_SIGGEN("V Gen"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1316_dapm_routes[] = अणु
	अणु "DAC", "Switch", "DP1RX" पूर्ण,
	अणु "CLASS D", शून्य, "DAC" पूर्ण,
	अणु "SPOL", शून्य, "CLASS D" पूर्ण,
	अणु "SPOR", शून्य, "CLASS D" पूर्ण,

	अणु "I Sense", शून्य, "I Gen" पूर्ण,
	अणु "V Sense", शून्य, "V Gen" पूर्ण,
	अणु "I Sense", शून्य, "PDE 24" पूर्ण,
	अणु "V Sense", शून्य, "PDE 24" पूर्ण,
	अणु "DP2TX", शून्य, "I Sense" पूर्ण,
	अणु "DP2TX", शून्य, "V Sense" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1316_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
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

अटल व्योम rt1316_sdw_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt1316_sdw_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1316_sdw_priv *rt1316 =
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

	अगर (!rt1316->sdw_slave)
		वापस -EINVAL;

	/* SoundWire specअगरic configuration */
	/* port 1 क्रम playback */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port = 1;
	पूर्ण अन्यथा अणु
		direction = SDW_DATA_सूची_TX;
		port = 2;
	पूर्ण

	num_channels = params_channels(params);
	ch_mask = (1 << num_channels) - 1;

	stream_config.frame_rate = params_rate(params);
	stream_config.ch_count = num_channels;
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	port_config.ch_mask = ch_mask;
	port_config.num = port;

	retval = sdw_stream_add_slave(rt1316->sdw_slave, &stream_config,
				&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt1316_sdw_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1316_sdw_priv *rt1316 =
		snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt1316->sdw_slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt1316->sdw_slave, stream->sdw_stream);
	वापस 0;
पूर्ण

/*
 * slave_ops: callbacks क्रम get_घड़ी_stop_mode, घड़ी_stop and
 * port_prep are not defined क्रम now
 */
अटल काष्ठा sdw_slave_ops rt1316_slave_ops = अणु
	.पढ़ो_prop = rt1316_पढ़ो_prop,
	.update_status = rt1316_update_status,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_sdw_rt1316 = अणु
	.controls = rt1316_snd_controls,
	.num_controls = ARRAY_SIZE(rt1316_snd_controls),
	.dapm_widमाला_लो = rt1316_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1316_dapm_widमाला_लो),
	.dapm_routes = rt1316_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1316_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops rt1316_aअगर_dai_ops = अणु
	.hw_params = rt1316_sdw_hw_params,
	.hw_मुक्त	= rt1316_sdw_pcm_hw_मुक्त,
	.set_sdw_stream	= rt1316_set_sdw_stream,
	.shutकरोwn	= rt1316_sdw_shutकरोwn,
पूर्ण;

#घोषणा RT1316_STEREO_RATES SNDRV_PCM_RATE_48000
#घोषणा RT1316_FORMATS (SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver rt1316_sdw_dai[] = अणु
	अणु
		.name = "rt1316-aif",
		.playback = अणु
			.stream_name = "DP1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1316_STEREO_RATES,
			.क्रमmats = RT1316_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DP2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1316_STEREO_RATES,
			.क्रमmats = RT1316_FORMATS,
		पूर्ण,
		.ops = &rt1316_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt1316_sdw_init(काष्ठा device *dev, काष्ठा regmap *regmap,
				काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt1316_sdw_priv *rt1316;
	पूर्णांक ret;

	rt1316 = devm_kzalloc(dev, माप(*rt1316), GFP_KERNEL);
	अगर (!rt1316)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt1316);
	rt1316->sdw_slave = slave;
	rt1316->regmap = regmap;

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt1316->hw_init = false;
	rt1316->first_hw_init = false;

	ret =  devm_snd_soc_रेजिस्टर_component(dev,
				&soc_component_sdw_rt1316,
				rt1316_sdw_dai,
				ARRAY_SIZE(rt1316_sdw_dai));

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक rt1316_sdw_probe(काष्ठा sdw_slave *slave,
				स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *regmap;

	/* Regmap Initialization */
	regmap = devm_regmap_init_sdw(slave, &rt1316_sdw_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rt1316_sdw_init(&slave->dev, regmap, slave);
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt1316_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x1316, 0x3, 0x1, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt1316_id);

अटल पूर्णांक __maybe_unused rt1316_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt1316_sdw_priv *rt1316 = dev_get_drvdata(dev);

	अगर (!rt1316->hw_init)
		वापस 0;

	regcache_cache_only(rt1316->regmap, true);

	वापस 0;
पूर्ण

#घोषणा RT1316_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt1316_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt1316_sdw_priv *rt1316 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt1316->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
				msecs_to_jअगरfies(RT1316_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt1316->regmap, false);
	regcache_sync(rt1316->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt1316_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt1316_dev_suspend, rt1316_dev_resume)
	SET_RUNTIME_PM_OPS(rt1316_dev_suspend, rt1316_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt1316_sdw_driver = अणु
	.driver = अणु
		.name = "rt1316-sdca",
		.owner = THIS_MODULE,
		.pm = &rt1316_pm,
	पूर्ण,
	.probe = rt1316_sdw_probe,
	.ops = &rt1316_slave_ops,
	.id_table = rt1316_id,
पूर्ण;
module_sdw_driver(rt1316_sdw_driver);

MODULE_DESCRIPTION("ASoC RT1316 driver SDCA SDW");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL");
