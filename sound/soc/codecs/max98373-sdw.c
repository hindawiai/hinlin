<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020, Maxim Integrated

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/of.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश "max98373.h"
#समावेश "max98373-sdw.h"

काष्ठा sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

अटल स्थिर u32 max98373_sdw_cache_reg[] = अणु
	MAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK,
	MAX98373_R2055_MEAS_ADC_THERM_CH_READBACK,
	MAX98373_R20B6_BDE_CUR_STATE_READBACK,
पूर्ण;

अटल काष्ठा reg_शेष max98373_reg[] = अणु
	अणुMAX98373_R0040_SCP_INIT_STAT_1, 0x00पूर्ण,
	अणुMAX98373_R0041_SCP_INIT_MASK_1, 0x00पूर्ण,
	अणुMAX98373_R0042_SCP_INIT_STAT_2, 0x00पूर्ण,
	अणुMAX98373_R0044_SCP_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0045_SCP_SYSTEM_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0046_SCP_DEV_NUMBER, 0x00पूर्ण,
	अणुMAX98373_R0050_SCP_DEV_ID_0, 0x21पूर्ण,
	अणुMAX98373_R0051_SCP_DEV_ID_1, 0x01पूर्ण,
	अणुMAX98373_R0052_SCP_DEV_ID_2, 0x9Fपूर्ण,
	अणुMAX98373_R0053_SCP_DEV_ID_3, 0x87पूर्ण,
	अणुMAX98373_R0054_SCP_DEV_ID_4, 0x08पूर्ण,
	अणुMAX98373_R0055_SCP_DEV_ID_5, 0x00पूर्ण,
	अणुMAX98373_R0060_SCP_FRAME_CTLR, 0x00पूर्ण,
	अणुMAX98373_R0070_SCP_FRAME_CTLR, 0x00पूर्ण,
	अणुMAX98373_R0100_DP1_INIT_STAT, 0x00पूर्ण,
	अणुMAX98373_R0101_DP1_INIT_MASK, 0x00पूर्ण,
	अणुMAX98373_R0102_DP1_PORT_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0103_DP1_BLOCK_CTRL_1, 0x00पूर्ण,
	अणुMAX98373_R0104_DP1_PREPARE_STATUS, 0x00पूर्ण,
	अणुMAX98373_R0105_DP1_PREPARE_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0120_DP1_CHANNEL_EN, 0x00पूर्ण,
	अणुMAX98373_R0122_DP1_SAMPLE_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0123_DP1_SAMPLE_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0124_DP1_OFFSET_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0125_DP1_OFFSET_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0126_DP1_HCTRL, 0x00पूर्ण,
	अणुMAX98373_R0127_DP1_BLOCK_CTRL3, 0x00पूर्ण,
	अणुMAX98373_R0130_DP1_CHANNEL_EN, 0x00पूर्ण,
	अणुMAX98373_R0132_DP1_SAMPLE_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0133_DP1_SAMPLE_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0134_DP1_OFFSET_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0135_DP1_OFFSET_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0136_DP1_HCTRL, 0x0136पूर्ण,
	अणुMAX98373_R0137_DP1_BLOCK_CTRL3, 0x00पूर्ण,
	अणुMAX98373_R0300_DP3_INIT_STAT, 0x00पूर्ण,
	अणुMAX98373_R0301_DP3_INIT_MASK, 0x00पूर्ण,
	अणुMAX98373_R0302_DP3_PORT_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0303_DP3_BLOCK_CTRL_1, 0x00पूर्ण,
	अणुMAX98373_R0304_DP3_PREPARE_STATUS, 0x00पूर्ण,
	अणुMAX98373_R0305_DP3_PREPARE_CTRL, 0x00पूर्ण,
	अणुMAX98373_R0320_DP3_CHANNEL_EN, 0x00पूर्ण,
	अणुMAX98373_R0322_DP3_SAMPLE_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0323_DP3_SAMPLE_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0324_DP3_OFFSET_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0325_DP3_OFFSET_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0326_DP3_HCTRL, 0x00पूर्ण,
	अणुMAX98373_R0327_DP3_BLOCK_CTRL3, 0x00पूर्ण,
	अणुMAX98373_R0330_DP3_CHANNEL_EN, 0x00पूर्ण,
	अणुMAX98373_R0332_DP3_SAMPLE_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0333_DP3_SAMPLE_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0334_DP3_OFFSET_CTRL1, 0x00पूर्ण,
	अणुMAX98373_R0335_DP3_OFFSET_CTRL2, 0x00पूर्ण,
	अणुMAX98373_R0336_DP3_HCTRL, 0x00पूर्ण,
	अणुMAX98373_R0337_DP3_BLOCK_CTRL3, 0x00पूर्ण,
	अणुMAX98373_R2000_SW_RESET, 0x00पूर्ण,
	अणुMAX98373_R2001_INT_RAW1, 0x00पूर्ण,
	अणुMAX98373_R2002_INT_RAW2, 0x00पूर्ण,
	अणुMAX98373_R2003_INT_RAW3, 0x00पूर्ण,
	अणुMAX98373_R2004_INT_STATE1, 0x00पूर्ण,
	अणुMAX98373_R2005_INT_STATE2, 0x00पूर्ण,
	अणुMAX98373_R2006_INT_STATE3, 0x00पूर्ण,
	अणुMAX98373_R2007_INT_FLAG1, 0x00पूर्ण,
	अणुMAX98373_R2008_INT_FLAG2, 0x00पूर्ण,
	अणुMAX98373_R2009_INT_FLAG3, 0x00पूर्ण,
	अणुMAX98373_R200A_INT_EN1, 0x00पूर्ण,
	अणुMAX98373_R200B_INT_EN2, 0x00पूर्ण,
	अणुMAX98373_R200C_INT_EN3, 0x00पूर्ण,
	अणुMAX98373_R200D_INT_FLAG_CLR1, 0x00पूर्ण,
	अणुMAX98373_R200E_INT_FLAG_CLR2, 0x00पूर्ण,
	अणुMAX98373_R200F_INT_FLAG_CLR3, 0x00पूर्ण,
	अणुMAX98373_R2010_IRQ_CTRL, 0x00पूर्ण,
	अणुMAX98373_R2014_THERM_WARN_THRESH, 0x10पूर्ण,
	अणुMAX98373_R2015_THERM_SHDN_THRESH, 0x27पूर्ण,
	अणुMAX98373_R2016_THERM_HYSTERESIS, 0x01पूर्ण,
	अणुMAX98373_R2017_THERM_FOLDBACK_SET, 0xC0पूर्ण,
	अणुMAX98373_R2018_THERM_FOLDBACK_EN, 0x00पूर्ण,
	अणुMAX98373_R201E_PIN_DRIVE_STRENGTH, 0x55पूर्ण,
	अणुMAX98373_R2020_PCM_TX_HIZ_EN_1, 0xFEपूर्ण,
	अणुMAX98373_R2021_PCM_TX_HIZ_EN_2, 0xFFपूर्ण,
	अणुMAX98373_R2022_PCM_TX_SRC_1, 0x00पूर्ण,
	अणुMAX98373_R2023_PCM_TX_SRC_2, 0x00पूर्ण,
	अणुMAX98373_R2024_PCM_DATA_FMT_CFG, 0xC0पूर्ण,
	अणुMAX98373_R2025_AUDIO_IF_MODE, 0x00पूर्ण,
	अणुMAX98373_R2026_PCM_CLOCK_RATIO, 0x04पूर्ण,
	अणुMAX98373_R2027_PCM_SR_SETUP_1, 0x08पूर्ण,
	अणुMAX98373_R2028_PCM_SR_SETUP_2, 0x88पूर्ण,
	अणुMAX98373_R2029_PCM_TO_SPK_MONO_MIX_1, 0x00पूर्ण,
	अणुMAX98373_R202A_PCM_TO_SPK_MONO_MIX_2, 0x00पूर्ण,
	अणुMAX98373_R202B_PCM_RX_EN, 0x00पूर्ण,
	अणुMAX98373_R202C_PCM_TX_EN, 0x00पूर्ण,
	अणुMAX98373_R202E_ICC_RX_CH_EN_1, 0x00पूर्ण,
	अणुMAX98373_R202F_ICC_RX_CH_EN_2, 0x00पूर्ण,
	अणुMAX98373_R2030_ICC_TX_HIZ_EN_1, 0xFFपूर्ण,
	अणुMAX98373_R2031_ICC_TX_HIZ_EN_2, 0xFFपूर्ण,
	अणुMAX98373_R2032_ICC_LINK_EN_CFG, 0x30पूर्ण,
	अणुMAX98373_R2034_ICC_TX_CNTL, 0x00पूर्ण,
	अणुMAX98373_R2035_ICC_TX_EN, 0x00पूर्ण,
	अणुMAX98373_R2036_SOUNDWIRE_CTRL, 0x05पूर्ण,
	अणुMAX98373_R203D_AMP_DIG_VOL_CTRL, 0x00पूर्ण,
	अणुMAX98373_R203E_AMP_PATH_GAIN, 0x08पूर्ण,
	अणुMAX98373_R203F_AMP_DSP_CFG, 0x02पूर्ण,
	अणुMAX98373_R2040_TONE_GEN_CFG, 0x00पूर्ण,
	अणुMAX98373_R2041_AMP_CFG, 0x03पूर्ण,
	अणुMAX98373_R2042_AMP_EDGE_RATE_CFG, 0x00पूर्ण,
	अणुMAX98373_R2043_AMP_EN, 0x00पूर्ण,
	अणुMAX98373_R2046_IV_SENSE_ADC_DSP_CFG, 0x04पूर्ण,
	अणुMAX98373_R2047_IV_SENSE_ADC_EN, 0x00पूर्ण,
	अणुMAX98373_R2051_MEAS_ADC_SAMPLING_RATE, 0x00पूर्ण,
	अणुMAX98373_R2052_MEAS_ADC_PVDD_FLT_CFG, 0x00पूर्ण,
	अणुMAX98373_R2053_MEAS_ADC_THERM_FLT_CFG, 0x00पूर्ण,
	अणुMAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK, 0x00पूर्ण,
	अणुMAX98373_R2055_MEAS_ADC_THERM_CH_READBACK, 0x00पूर्ण,
	अणुMAX98373_R2056_MEAS_ADC_PVDD_CH_EN, 0x00पूर्ण,
	अणुMAX98373_R2090_BDE_LVL_HOLD, 0x00पूर्ण,
	अणुMAX98373_R2091_BDE_GAIN_ATK_REL_RATE, 0x00पूर्ण,
	अणुMAX98373_R2092_BDE_CLIPPER_MODE, 0x00पूर्ण,
	अणुMAX98373_R2097_BDE_L1_THRESH, 0x00पूर्ण,
	अणुMAX98373_R2098_BDE_L2_THRESH, 0x00पूर्ण,
	अणुMAX98373_R2099_BDE_L3_THRESH, 0x00पूर्ण,
	अणुMAX98373_R209A_BDE_L4_THRESH, 0x00पूर्ण,
	अणुMAX98373_R209B_BDE_THRESH_HYST, 0x00पूर्ण,
	अणुMAX98373_R20A8_BDE_L1_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20A9_BDE_L1_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20AA_BDE_L1_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20AB_BDE_L2_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20AC_BDE_L2_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20AD_BDE_L2_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20AE_BDE_L3_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20AF_BDE_L3_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20B0_BDE_L3_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20B1_BDE_L4_CFG_1, 0x00पूर्ण,
	अणुMAX98373_R20B2_BDE_L4_CFG_2, 0x00पूर्ण,
	अणुMAX98373_R20B3_BDE_L4_CFG_3, 0x00पूर्ण,
	अणुMAX98373_R20B4_BDE_INFINITE_HOLD_RELEASE, 0x00पूर्ण,
	अणुMAX98373_R20B5_BDE_EN, 0x00पूर्ण,
	अणुMAX98373_R20B6_BDE_CUR_STATE_READBACK, 0x00पूर्ण,
	अणुMAX98373_R20D1_DHT_CFG, 0x01पूर्ण,
	अणुMAX98373_R20D2_DHT_ATTACK_CFG, 0x02पूर्ण,
	अणुMAX98373_R20D3_DHT_RELEASE_CFG, 0x03पूर्ण,
	अणुMAX98373_R20D4_DHT_EN, 0x00पूर्ण,
	अणुMAX98373_R20E0_LIMITER_THRESH_CFG, 0x00पूर्ण,
	अणुMAX98373_R20E1_LIMITER_ATK_REL_RATES, 0x00पूर्ण,
	अणुMAX98373_R20E2_LIMITER_EN, 0x00पूर्ण,
	अणुMAX98373_R20FE_DEVICE_AUTO_RESTART_CFG, 0x00पूर्ण,
	अणुMAX98373_R20FF_GLOBAL_SHDN, 0x00पूर्ण,
	अणुMAX98373_R21FF_REV_ID, 0x42पूर्ण,
पूर्ण;

अटल bool max98373_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98373_R21FF_REV_ID:
	हाल MAX98373_R2010_IRQ_CTRL:
	/* SoundWire Control Port Registers */
	हाल MAX98373_R0040_SCP_INIT_STAT_1 ... MAX98373_R0070_SCP_FRAME_CTLR:
	/* Soundwire Data Port 1 Registers */
	हाल MAX98373_R0100_DP1_INIT_STAT ... MAX98373_R0137_DP1_BLOCK_CTRL3:
	/* Soundwire Data Port 3 Registers */
	हाल MAX98373_R0300_DP3_INIT_STAT ... MAX98373_R0337_DP3_BLOCK_CTRL3:
	हाल MAX98373_R2000_SW_RESET ... MAX98373_R200C_INT_EN3:
	हाल MAX98373_R2014_THERM_WARN_THRESH
		... MAX98373_R2018_THERM_FOLDBACK_EN:
	हाल MAX98373_R201E_PIN_DRIVE_STRENGTH
		... MAX98373_R2036_SOUNDWIRE_CTRL:
	हाल MAX98373_R203D_AMP_DIG_VOL_CTRL ... MAX98373_R2043_AMP_EN:
	हाल MAX98373_R2046_IV_SENSE_ADC_DSP_CFG
		... MAX98373_R2047_IV_SENSE_ADC_EN:
	हाल MAX98373_R2051_MEAS_ADC_SAMPLING_RATE
		... MAX98373_R2056_MEAS_ADC_PVDD_CH_EN:
	हाल MAX98373_R2090_BDE_LVL_HOLD ... MAX98373_R2092_BDE_CLIPPER_MODE:
	हाल MAX98373_R2097_BDE_L1_THRESH
		... MAX98373_R209B_BDE_THRESH_HYST:
	हाल MAX98373_R20A8_BDE_L1_CFG_1 ... MAX98373_R20B3_BDE_L4_CFG_3:
	हाल MAX98373_R20B5_BDE_EN ... MAX98373_R20B6_BDE_CUR_STATE_READBACK:
	हाल MAX98373_R20D1_DHT_CFG ... MAX98373_R20D4_DHT_EN:
	हाल MAX98373_R20E0_LIMITER_THRESH_CFG ... MAX98373_R20E2_LIMITER_EN:
	हाल MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG
		... MAX98373_R20FF_GLOBAL_SHDN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण;

अटल bool max98373_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK:
	हाल MAX98373_R2055_MEAS_ADC_THERM_CH_READBACK:
	हाल MAX98373_R20B6_BDE_CUR_STATE_READBACK:
	हाल MAX98373_R20FF_GLOBAL_SHDN:
	हाल MAX98373_R21FF_REV_ID:
	/* SoundWire Control Port Registers */
	हाल MAX98373_R0040_SCP_INIT_STAT_1 ... MAX98373_R0070_SCP_FRAME_CTLR:
	/* Soundwire Data Port 1 Registers */
	हाल MAX98373_R0100_DP1_INIT_STAT ... MAX98373_R0137_DP1_BLOCK_CTRL3:
	/* Soundwire Data Port 3 Registers */
	हाल MAX98373_R0300_DP3_INIT_STAT ... MAX98373_R0337_DP3_BLOCK_CTRL3:
	हाल MAX98373_R2000_SW_RESET ... MAX98373_R2009_INT_FLAG3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max98373_sdw_regmap = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.max_रेजिस्टर = MAX98373_R21FF_REV_ID,
	.reg_शेषs  = max98373_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98373_reg),
	.पढ़ोable_reg = max98373_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = max98373_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

/* Power management functions and काष्ठाure */
अटल __maybe_unused पूर्णांक max98373_suspend(काष्ठा device *dev)
अणु
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);
	पूर्णांक i;

	/* cache feedback रेजिस्टर values beक्रमe suspend */
	क्रम (i = 0; i < max98373->cache_num; i++)
		regmap_पढ़ो(max98373->regmap, max98373->cache[i].reg, &max98373->cache[i].val);

	regcache_cache_only(max98373->regmap, true);

	वापस 0;
पूर्ण

#घोषणा MAX98373_PROBE_TIMEOUT 5000

अटल __maybe_unused पूर्णांक max98373_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!max98373->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
					   msecs_to_jअगरfies(MAX98373_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(max98373->regmap, false);
	regcache_sync(max98373->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops max98373_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max98373_suspend, max98373_resume)
	SET_RUNTIME_PM_OPS(max98373_suspend, max98373_resume, शून्य)
पूर्ण;

अटल पूर्णांक max98373_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval, i;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_BUS_CLASH | SDW_SCP_INT1_PARITY;

	/* BITMAP: 00001000  Dataport 3 is active */
	prop->source_ports = BIT(3);
	/* BITMAP: 00000010  Dataport 1 is active */
	prop->sink_ports = BIT(1);
	prop->paging_support = true;
	prop->clk_stop_समयout = 20;

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					  माप(*prop->src_dpn_prop),
					  GFP_KERNEL);
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

	वापस 0;
पूर्ण

अटल पूर्णांक max98373_io_init(काष्ठा sdw_slave *slave)
अणु
	काष्ठा device *dev = &slave->dev;
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);

	अगर (max98373->pm_init_once) अणु
		regcache_cache_only(max98373->regmap, false);
		regcache_cache_bypass(max98373->regmap, true);
	पूर्ण

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!max98373->pm_init_once) अणु
		/* set स्वतःsuspend parameters */
		pm_runसमय_set_स्वतःsuspend_delay(dev, 3000);
		pm_runसमय_use_स्वतःsuspend(dev);

		/* update count of parent 'active' children */
		pm_runसमय_set_active(dev);

		/* make sure the device करोes not suspend immediately */
		pm_runसमय_mark_last_busy(dev);

		pm_runसमय_enable(dev);
	पूर्ण

	pm_runसमय_get_noresume(dev);

	/* Software Reset */
	max98373_reset(max98373, dev);

	/* Set soundwire mode */
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2025_AUDIO_IF_MODE, 3);
	/* Enable ADC */
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2047_IV_SENSE_ADC_EN, 3);
	/* Set शेष Soundwire घड़ी */
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2036_SOUNDWIRE_CTRL, 5);
	/* Set शेष sampling rate क्रम speaker and IVDAC */
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2028_PCM_SR_SETUP_2, 0x88);
	/* IV शेष slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2020_PCM_TX_HIZ_EN_1,
		     0xFF);
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2021_PCM_TX_HIZ_EN_2,
		     0xFF);
	/* L/R mix configuration */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1,
		     0x80);
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R202A_PCM_TO_SPK_MONO_MIX_2,
		     0x1);
	/* Enable DC blocker */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R203F_AMP_DSP_CFG,
		     0x3);
	/* Enable IMON VMON DC blocker */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2046_IV_SENSE_ADC_DSP_CFG,
		     0x7);
	/* voltage, current slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2022_PCM_TX_SRC_1,
		     (max98373->i_slot << MAX98373_PCM_TX_CH_SRC_A_I_SHIFT |
		     max98373->v_slot) & 0xFF);
	अगर (max98373->v_slot < 8)
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2020_PCM_TX_HIZ_EN_1,
				   1 << max98373->v_slot, 0);
	अन्यथा
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2021_PCM_TX_HIZ_EN_2,
				   1 << (max98373->v_slot - 8), 0);

	अगर (max98373->i_slot < 8)
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2020_PCM_TX_HIZ_EN_1,
				   1 << max98373->i_slot, 0);
	अन्यथा
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2021_PCM_TX_HIZ_EN_2,
				   1 << (max98373->i_slot - 8), 0);

	/* speaker feedback slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		     MAX98373_R2023_PCM_TX_SRC_2,
		     max98373->spkfb_slot & 0xFF);

	/* Set पूर्णांकerleave mode */
	अगर (max98373->पूर्णांकerleave_mode)
		regmap_update_bits(max98373->regmap,
				   MAX98373_R2024_PCM_DATA_FMT_CFG,
				   MAX98373_PCM_TX_CH_INTERLEAVE_MASK,
				   MAX98373_PCM_TX_CH_INTERLEAVE_MASK);

	/* Speaker enable */
	regmap_update_bits(max98373->regmap,
			   MAX98373_R2043_AMP_EN,
			   MAX98373_SPK_EN_MASK, 1);

	regmap_ग_लिखो(max98373->regmap, MAX98373_R20B5_BDE_EN, 1);
	regmap_ग_लिखो(max98373->regmap, MAX98373_R20E2_LIMITER_EN, 1);

	अगर (max98373->pm_init_once) अणु
		regcache_cache_bypass(max98373->regmap, false);
		regcache_mark_dirty(max98373->regmap);
	पूर्ण

	max98373->pm_init_once = true;
	max98373->hw_init = true;

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक max98373_घड़ी_calculate(काष्ठा sdw_slave *slave,
				    अचिन्हित पूर्णांक clk_freq)
अणु
	पूर्णांक x, y;
	अटल स्थिर पूर्णांक max98373_clk_family[] = अणु
		7680000, 8400000, 9600000, 11289600,
		12000000, 12288000, 13000000
	पूर्ण;

	क्रम (x = 0; x < 4; x++)
		क्रम (y = 0; y < ARRAY_SIZE(max98373_clk_family); y++)
			अगर (clk_freq == (max98373_clk_family[y] >> x))
				वापस (x << 3) + y;

	/* Set शेष घड़ी (12.288 Mhz) अगर the value is not in the list */
	dev_err(&slave->dev, "Requested clock not found. (clk_freq = %d)\n",
		clk_freq);
	वापस 0x5;
पूर्ण

अटल पूर्णांक max98373_घड़ी_config(काष्ठा sdw_slave *slave,
				 काष्ठा sdw_bus_params *params)
अणु
	काष्ठा device *dev = &slave->dev;
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक clk_freq, value;

	clk_freq = (params->curr_dr_freq >> 1);

	/*
	 *	Select the proper value क्रम the रेजिस्टर based on the
	 *	requested घड़ी. If the value is not in the list,
	 *	use reasonable शेष - 12.288 Mhz
	 */
	value = max98373_घड़ी_calculate(slave, clk_freq);

	/* SWCLK */
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2036_SOUNDWIRE_CTRL, value);

	/* The शेष Sampling Rate value क्रम IV is 48KHz*/
	regmap_ग_लिखो(max98373->regmap, MAX98373_R2028_PCM_SR_SETUP_2, 0x88);

	वापस 0;
पूर्ण

#घोषणा MAX98373_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा MAX98373_FORMATS (SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक max98373_sdw_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98373_priv *max98373 =
		snd_soc_component_get_drvdata(component);

	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक ret, chan_sz, sampling_rate;

	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!max98373->slave)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port_config.num = 1;
	पूर्ण अन्यथा अणु
		direction = SDW_DATA_सूची_TX;
		port_config.num = 3;
	पूर्ण

	stream_config.frame_rate = params_rate(params);
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	अगर (max98373->slot && direction == SDW_DATA_सूची_RX) अणु
		stream_config.ch_count = max98373->slot;
		port_config.ch_mask = max98373->rx_mask;
	पूर्ण अन्यथा अणु
		/* only IV are supported by capture */
		अगर (direction == SDW_DATA_सूची_TX)
			stream_config.ch_count = 2;
		अन्यथा
			stream_config.ch_count = params_channels(params);

		port_config.ch_mask = GENMASK((पूर्णांक)stream_config.ch_count - 1, 0);
	पूर्ण

	ret = sdw_stream_add_slave(max98373->slave, &stream_config,
				   &port_config, 1, stream->sdw_stream);
	अगर (ret) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस ret;
	पूर्ण

	अगर (params_channels(params) > 16) अणु
		dev_err(component->dev, "Unsupported channels %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	/* Channel size configuration */
	चयन (snd_pcm_क्रमmat_width(params_क्रमmat(params))) अणु
	हाल 16:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_16;
		अवरोध;
	हाल 24:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_24;
		अवरोध;
	हाल 32:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_32;
		अवरोध;
	शेष:
		dev_err(component->dev, "Channel size unsupported %d\n",
			params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	max98373->ch_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));

	regmap_update_bits(max98373->regmap,
			   MAX98373_R2024_PCM_DATA_FMT_CFG,
			   MAX98373_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "Format supported %d", params_क्रमmat(params));

	/* Sampling rate configuration */
	चयन (params_rate(params)) अणु
	हाल 8000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_8000;
		अवरोध;
	हाल 11025:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_11025;
		अवरोध;
	हाल 12000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_12000;
		अवरोध;
	हाल 16000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_16000;
		अवरोध;
	हाल 22050:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_22050;
		अवरोध;
	हाल 24000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_24000;
		अवरोध;
	हाल 32000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_32000;
		अवरोध;
	हाल 44100:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_44100;
		अवरोध;
	हाल 48000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_48000;
		अवरोध;
	हाल 88200:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_88200;
		अवरोध;
	हाल 96000:
		sampling_rate = MAX98373_PCM_SR_SET1_SR_96000;
		अवरोध;
	शेष:
		dev_err(component->dev, "Rate %d is not supported\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	/* set correct sampling frequency */
	regmap_update_bits(max98373->regmap,
			   MAX98373_R2028_PCM_SR_SETUP_2,
			   MAX98373_PCM_SR_SET2_SR_MASK,
			   sampling_rate << MAX98373_PCM_SR_SET2_SR_SHIFT);

	/* set sampling rate of IV */
	regmap_update_bits(max98373->regmap,
			   MAX98373_R2028_PCM_SR_SETUP_2,
			   MAX98373_PCM_SR_SET2_IVADC_SR_MASK,
			   sampling_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक max98373_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98373_priv *max98373 =
		snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!max98373->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(max98373->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

अटल पूर्णांक max98373_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				   व्योम *sdw_stream, पूर्णांक direction)
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

अटल व्योम max98373_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक max98373_sdw_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				     अचिन्हित पूर्णांक tx_mask,
				     अचिन्हित पूर्णांक rx_mask,
				     पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98373_priv *max98373 =
		snd_soc_component_get_drvdata(component);

	/* tx_mask is unused since it's irrelevant क्रम I/V feedback */
	अगर (tx_mask)
		वापस -EINVAL;

	अगर (!rx_mask && !slots && !slot_width)
		max98373->tdm_mode = false;
	अन्यथा
		max98373->tdm_mode = true;

	max98373->rx_mask = rx_mask;
	max98373->slot = slots;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops max98373_dai_sdw_ops = अणु
	.hw_params = max98373_sdw_dai_hw_params,
	.hw_मुक्त = max98373_pcm_hw_मुक्त,
	.set_sdw_stream = max98373_set_sdw_stream,
	.shutकरोwn = max98373_shutकरोwn,
	.set_tdm_slot = max98373_sdw_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98373_sdw_dai[] = अणु
	अणु
		.name = "max98373-aif1",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98373_RATES,
			.क्रमmats = MAX98373_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MAX98373_RATES,
			.क्रमmats = MAX98373_FORMATS,
		पूर्ण,
		.ops = &max98373_dai_sdw_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक max98373_init(काष्ठा sdw_slave *slave, काष्ठा regmap *regmap)
अणु
	काष्ठा max98373_priv *max98373;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा device *dev = &slave->dev;

	/*  Allocate and assign निजी driver data काष्ठाure  */
	max98373 = devm_kzalloc(dev, माप(*max98373), GFP_KERNEL);
	अगर (!max98373)
		वापस -ENOMEM;

	dev_set_drvdata(dev, max98373);
	max98373->regmap = regmap;
	max98373->slave = slave;

	max98373->cache_num = ARRAY_SIZE(max98373_sdw_cache_reg);
	max98373->cache = devm_kसुस्मृति(dev, max98373->cache_num,
				       माप(*max98373->cache),
				       GFP_KERNEL);

	क्रम (i = 0; i < max98373->cache_num; i++)
		max98373->cache[i].reg = max98373_sdw_cache_reg[i];

	/* Read voltage and slot configuration */
	max98373_slot_config(dev, max98373);

	max98373->hw_init = false;
	max98373->pm_init_once = false;

	/* codec registration  */
	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_codec_dev_max98373_sdw,
					      max98373_sdw_dai,
					      ARRAY_SIZE(max98373_sdw_dai));
	अगर (ret < 0)
		dev_err(dev, "Failed to register codec: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max98373_update_status(काष्ठा sdw_slave *slave,
				  क्रमागत sdw_slave_status status)
अणु
	काष्ठा max98373_priv *max98373 = dev_get_drvdata(&slave->dev);

	अगर (status == SDW_SLAVE_UNATTACHED)
		max98373->hw_init = false;

	/*
	 * Perक्रमm initialization only अगर slave status is SDW_SLAVE_ATTACHED
	 */
	अगर (max98373->hw_init || status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस max98373_io_init(slave);
पूर्ण

अटल पूर्णांक max98373_bus_config(काष्ठा sdw_slave *slave,
			       काष्ठा sdw_bus_params *params)
अणु
	पूर्णांक ret;

	ret = max98373_घड़ी_config(slave, params);
	अगर (ret < 0)
		dev_err(&slave->dev, "Invalid clk config");

	वापस ret;
पूर्ण

/*
 * slave_ops: callbacks क्रम get_घड़ी_stop_mode, घड़ी_stop and
 * port_prep are not defined क्रम now
 */
अटल काष्ठा sdw_slave_ops max98373_slave_ops = अणु
	.पढ़ो_prop = max98373_पढ़ो_prop,
	.update_status = max98373_update_status,
	.bus_config = max98373_bus_config,
पूर्ण;

अटल पूर्णांक max98373_sdw_probe(काष्ठा sdw_slave *slave,
			      स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *regmap;

	/* Regmap Initialization */
	regmap = devm_regmap_init_sdw(slave, &max98373_sdw_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस max98373_init(slave, regmap);
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id max98373_of_match[] = अणु
	अणु .compatible = "maxim,max98373", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max98373_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max98373_acpi_match[] = अणु
	अणु "MX98373", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max98373_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा sdw_device_id max98373_id[] = अणु
	SDW_SLAVE_ENTRY(0x019F, 0x8373, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, max98373_id);

अटल काष्ठा sdw_driver max98373_sdw_driver = अणु
	.driver = अणु
		.name = "max98373",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(max98373_of_match),
		.acpi_match_table = ACPI_PTR(max98373_acpi_match),
		.pm = &max98373_pm,
	पूर्ण,
	.probe = max98373_sdw_probe,
	.हटाओ = शून्य,
	.ops = &max98373_slave_ops,
	.id_table = max98373_id,
पूर्ण;

module_sdw_driver(max98373_sdw_driver);

MODULE_DESCRIPTION("ASoC MAX98373 driver SDW");
MODULE_AUTHOR("Oleg Sherbakov <oleg.sherbakov@maximintegrated.com>");
MODULE_LICENSE("GPL v2");
