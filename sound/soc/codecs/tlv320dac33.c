<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC Texas Instruments TLV320DAC33 codec driver
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Copyright:   (C) 2009 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश <sound/tlv320dac33-plat.h>
#समावेश "tlv320dac33.h"

/*
 * The पूर्णांकernal FIFO is 24576 bytes दीर्घ
 * It can be configured to hold 16bit or 24bit samples
 * In 16bit configuration the FIFO can hold 6144 stereo samples
 * In 24bit configuration the FIFO can hold 4096 stereo samples
 */
#घोषणा DAC33_FIFO_SIZE_16BIT	6144
#घोषणा DAC33_FIFO_SIZE_24BIT	4096
#घोषणा DAC33_MODE7_MARGIN	10	/* Safety margin क्रम FIFO in Mode7 */

#घोषणा BURST_BASEFREQ_HZ	49152000

#घोषणा SAMPLES_TO_US(rate, samples) \
	(1000000000 / (((rate) * 1000) / (samples)))

#घोषणा US_TO_SAMPLES(rate, us) \
	((rate) / (1000000 / ((us) < 1000000 ? (us) : 1000000)))

#घोषणा UTHR_FROM_PERIOD_SIZE(samples, playrate, burstrate) \
	(((samples)*5000) / (((burstrate)*5000) / ((burstrate) - (playrate))))

अटल व्योम dac33_calculate_बार(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_component *component);
अटल पूर्णांक dac33_prepare_chip(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_component *component);

क्रमागत dac33_state अणु
	DAC33_IDLE = 0,
	DAC33_PREFILL,
	DAC33_PLAYBACK,
	DAC33_FLUSH,
पूर्ण;

क्रमागत dac33_fअगरo_modes अणु
	DAC33_FIFO_BYPASS = 0,
	DAC33_FIFO_MODE1,
	DAC33_FIFO_MODE7,
	DAC33_FIFO_LAST_MODE,
पूर्ण;

#घोषणा DAC33_NUM_SUPPLIES 3
अटल स्थिर अक्षर *dac33_supply_names[DAC33_NUM_SUPPLIES] = अणु
	"AVDD",
	"DVDD",
	"IOVDD",
पूर्ण;

काष्ठा tlv320dac33_priv अणु
	काष्ठा mutex mutex;
	काष्ठा work_काष्ठा work;
	काष्ठा snd_soc_component *component;
	काष्ठा regulator_bulk_data supplies[DAC33_NUM_SUPPLIES];
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक घातer_gpio;
	पूर्णांक chip_घातer;
	पूर्णांक irq;
	अचिन्हित पूर्णांक refclk;

	अचिन्हित पूर्णांक alarm_threshold;	/* set to be half of LATENCY_TIME_MS */
	क्रमागत dac33_fअगरo_modes fअगरo_mode;/* FIFO mode selection */
	अचिन्हित पूर्णांक fअगरo_size;		/* Size of the FIFO in samples */
	अचिन्हित पूर्णांक nsample;		/* burst पढ़ो amount from host */
	पूर्णांक mode1_latency;		/* latency caused by the i2c ग_लिखोs in
					 * us */
	u8 burst_bclkभाग;		/* BCLK भागider value in burst mode */
	u8 *reg_cache;
	अचिन्हित पूर्णांक burst_rate;	/* Interface speed in Burst modes */

	पूर्णांक keep_bclk;			/* Keep the BCLK continuously running
					 * in FIFO modes */
	spinlock_t lock;
	अचिन्हित दीर्घ दीर्घ t_stamp1;	/* Time stamp क्रम FIFO modes to */
	अचिन्हित दीर्घ दीर्घ t_stamp2;	/* calculate the FIFO caused delay */

	अचिन्हित पूर्णांक mode1_us_burst;	/* Time to burst पढ़ो n number of
					 * samples */
	अचिन्हित पूर्णांक mode7_us_to_lthr;	/* Time to reach lthr from uthr */

	अचिन्हित पूर्णांक uthr;

	क्रमागत dac33_state state;
	काष्ठा i2c_client *i2c;
पूर्ण;

अटल स्थिर u8 dac33_reg[DAC33_CACHEREGNUM] = अणु
0x00, 0x00, 0x00, 0x00, /* 0x00 - 0x03 */
0x00, 0x00, 0x00, 0x00, /* 0x04 - 0x07 */
0x00, 0x00, 0x00, 0x00, /* 0x08 - 0x0b */
0x00, 0x00, 0x00, 0x00, /* 0x0c - 0x0f */
0x00, 0x00, 0x00, 0x00, /* 0x10 - 0x13 */
0x00, 0x00, 0x00, 0x00, /* 0x14 - 0x17 */
0x00, 0x00, 0x00, 0x00, /* 0x18 - 0x1b */
0x00, 0x00, 0x00, 0x00, /* 0x1c - 0x1f */
0x00, 0x00, 0x00, 0x00, /* 0x20 - 0x23 */
0x00, 0x00, 0x00, 0x00, /* 0x24 - 0x27 */
0x00, 0x00, 0x00, 0x00, /* 0x28 - 0x2b */
0x00, 0x00, 0x00, 0x80, /* 0x2c - 0x2f */
0x80, 0x00, 0x00, 0x00, /* 0x30 - 0x33 */
0x00, 0x00, 0x00, 0x00, /* 0x34 - 0x37 */
0x00, 0x00,             /* 0x38 - 0x39 */
/* Registers 0x3a - 0x3f are reserved  */
            0x00, 0x00, /* 0x3a - 0x3b */
0x00, 0x00, 0x00, 0x00, /* 0x3c - 0x3f */

0x00, 0x00, 0x00, 0x00, /* 0x40 - 0x43 */
0x00, 0x80,             /* 0x44 - 0x45 */
/* Registers 0x46 - 0x47 are reserved  */
            0x80, 0x80, /* 0x46 - 0x47 */

0x80, 0x00, 0x00,       /* 0x48 - 0x4a */
/* Registers 0x4b - 0x7c are reserved  */
                  0x00, /* 0x4b        */
0x00, 0x00, 0x00, 0x00, /* 0x4c - 0x4f */
0x00, 0x00, 0x00, 0x00, /* 0x50 - 0x53 */
0x00, 0x00, 0x00, 0x00, /* 0x54 - 0x57 */
0x00, 0x00, 0x00, 0x00, /* 0x58 - 0x5b */
0x00, 0x00, 0x00, 0x00, /* 0x5c - 0x5f */
0x00, 0x00, 0x00, 0x00, /* 0x60 - 0x63 */
0x00, 0x00, 0x00, 0x00, /* 0x64 - 0x67 */
0x00, 0x00, 0x00, 0x00, /* 0x68 - 0x6b */
0x00, 0x00, 0x00, 0x00, /* 0x6c - 0x6f */
0x00, 0x00, 0x00, 0x00, /* 0x70 - 0x73 */
0x00, 0x00, 0x00, 0x00, /* 0x74 - 0x77 */
0x00, 0x00, 0x00, 0x00, /* 0x78 - 0x7b */
0x00,                   /* 0x7c        */

      0xda, 0x33, 0x03, /* 0x7d - 0x7f */
पूर्ण;

/* Register पढ़ो and ग_लिखो */
अटल अंतरभूत अचिन्हित पूर्णांक dac33_पढ़ो_reg_cache(काष्ठा snd_soc_component *component,
						अचिन्हित reg)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 *cache = dac33->reg_cache;
	अगर (reg >= DAC33_CACHEREGNUM)
		वापस 0;

	वापस cache[reg];
पूर्ण

अटल अंतरभूत व्योम dac33_ग_लिखो_reg_cache(काष्ठा snd_soc_component *component,
					 u8 reg, u8 value)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 *cache = dac33->reg_cache;
	अगर (reg >= DAC33_CACHEREGNUM)
		वापस;

	cache[reg] = value;
पूर्ण

अटल पूर्णांक dac33_पढ़ो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
		      u8 *value)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, ret = 0;

	*value = reg & 0xff;

	/* If घातered off, वापस the cached value */
	अगर (dac33->chip_घातer) अणु
		val = i2c_smbus_पढ़ो_byte_data(dac33->i2c, value[0]);
		अगर (val < 0) अणु
			dev_err(component->dev, "Read failed (%d)\n", val);
			value[0] = dac33_पढ़ो_reg_cache(component, reg);
			ret = val;
		पूर्ण अन्यथा अणु
			value[0] = val;
			dac33_ग_लिखो_reg_cache(component, reg, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		value[0] = dac33_पढ़ो_reg_cache(component, reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dac33_ग_लिखो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
		       अचिन्हित पूर्णांक value)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 data[2];
	पूर्णांक ret = 0;

	/*
	 * data is
	 *   D15..D8 dac33 रेजिस्टर offset
	 *   D7...D0 रेजिस्टर data
	 */
	data[0] = reg & 0xff;
	data[1] = value & 0xff;

	dac33_ग_लिखो_reg_cache(component, data[0], data[1]);
	अगर (dac33->chip_घातer) अणु
		ret = i2c_master_send(dac33->i2c, data, 2);
		अगर (ret != 2)
			dev_err(component->dev, "Write failed (%d)\n", ret);
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dac33_ग_लिखो_locked(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक value)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&dac33->mutex);
	ret = dac33_ग_लिखो(component, reg, value);
	mutex_unlock(&dac33->mutex);

	वापस ret;
पूर्ण

#घोषणा DAC33_I2C_ADDR_AUTOINC	0x80
अटल पूर्णांक dac33_ग_लिखो16(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
		       अचिन्हित पूर्णांक value)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 data[3];
	पूर्णांक ret = 0;

	/*
	 * data is
	 *   D23..D16 dac33 रेजिस्टर offset
	 *   D15..D8  रेजिस्टर data MSB
	 *   D7...D0  रेजिस्टर data LSB
	 */
	data[0] = reg & 0xff;
	data[1] = (value >> 8) & 0xff;
	data[2] = value & 0xff;

	dac33_ग_लिखो_reg_cache(component, data[0], data[1]);
	dac33_ग_लिखो_reg_cache(component, data[0] + 1, data[2]);

	अगर (dac33->chip_घातer) अणु
		/* We need to set स्वतःincrement mode क्रम 16 bit ग_लिखोs */
		data[0] |= DAC33_I2C_ADDR_AUTOINC;
		ret = i2c_master_send(dac33->i2c, data, 3);
		अगर (ret != 3)
			dev_err(component->dev, "Write failed (%d)\n", ret);
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dac33_init_chip(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	अगर (unlikely(!dac33->chip_घातer))
		वापस;

	/* A : DAC sample rate Fsref/1.5 */
	dac33_ग_लिखो(component, DAC33_DAC_CTRL_A, DAC33_DACRATE(0));
	/* B : DAC src=normal, not muted */
	dac33_ग_लिखो(component, DAC33_DAC_CTRL_B, DAC33_DACSRCR_RIGHT |
					     DAC33_DACSRCL_LEFT);
	/* C : (शेषs) */
	dac33_ग_लिखो(component, DAC33_DAC_CTRL_C, 0x00);

	/* 73 : volume soft stepping control,
	 घड़ी source = पूर्णांकernal osc (?) */
	dac33_ग_लिखो(component, DAC33_ANA_VOL_SOFT_STEP_CTRL, DAC33_VOLCLKEN);

	/* Restore only selected रेजिस्टरs (gains mostly) */
	dac33_ग_लिखो(component, DAC33_LDAC_DIG_VOL_CTRL,
		    dac33_पढ़ो_reg_cache(component, DAC33_LDAC_DIG_VOL_CTRL));
	dac33_ग_लिखो(component, DAC33_RDAC_DIG_VOL_CTRL,
		    dac33_पढ़ो_reg_cache(component, DAC33_RDAC_DIG_VOL_CTRL));

	dac33_ग_लिखो(component, DAC33_LINEL_TO_LLO_VOL,
		    dac33_पढ़ो_reg_cache(component, DAC33_LINEL_TO_LLO_VOL));
	dac33_ग_लिखो(component, DAC33_LINER_TO_RLO_VOL,
		    dac33_पढ़ो_reg_cache(component, DAC33_LINER_TO_RLO_VOL));

	dac33_ग_लिखो(component, DAC33_OUT_AMP_CTRL,
		    dac33_पढ़ो_reg_cache(component, DAC33_OUT_AMP_CTRL));

	dac33_ग_लिखो(component, DAC33_LDAC_PWR_CTRL,
		    dac33_पढ़ो_reg_cache(component, DAC33_LDAC_PWR_CTRL));
	dac33_ग_लिखो(component, DAC33_RDAC_PWR_CTRL,
		    dac33_पढ़ो_reg_cache(component, DAC33_RDAC_PWR_CTRL));
पूर्ण

अटल अंतरभूत पूर्णांक dac33_पढ़ो_id(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i, ret = 0;
	u8 reg;

	क्रम (i = 0; i < 3; i++) अणु
		ret = dac33_पढ़ो(component, DAC33_DEVICE_ID_MSB + i, &reg);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम dac33_soft_घातer(काष्ठा snd_soc_component *component, पूर्णांक घातer)
अणु
	u8 reg;

	reg = dac33_पढ़ो_reg_cache(component, DAC33_PWR_CTRL);
	अगर (घातer)
		reg |= DAC33_PDNALLB;
	अन्यथा
		reg &= ~(DAC33_PDNALLB | DAC33_OSCPDNB |
			 DAC33_DACRPDNB | DAC33_DACLPDNB);
	dac33_ग_लिखो(component, DAC33_PWR_CTRL, reg);
पूर्ण

अटल अंतरभूत व्योम dac33_disable_digital(काष्ठा snd_soc_component *component)
अणु
	u8 reg;

	/* Stop the DAI घड़ी */
	reg = dac33_पढ़ो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);
	reg &= ~DAC33_BCLKON;
	dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_B, reg);

	/* Power करोwn the Oscillator, and DACs */
	reg = dac33_पढ़ो_reg_cache(component, DAC33_PWR_CTRL);
	reg &= ~(DAC33_OSCPDNB | DAC33_DACRPDNB | DAC33_DACLPDNB);
	dac33_ग_लिखो(component, DAC33_PWR_CTRL, reg);
पूर्ण

अटल पूर्णांक dac33_hard_घातer(काष्ठा snd_soc_component *component, पूर्णांक घातer)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	mutex_lock(&dac33->mutex);

	/* Safety check */
	अगर (unlikely(घातer == dac33->chip_घातer)) अणु
		dev_dbg(component->dev, "Trying to set the same power state: %s\n",
			घातer ? "ON" : "OFF");
		जाओ निकास;
	पूर्ण

	अगर (घातer) अणु
		ret = regulator_bulk_enable(ARRAY_SIZE(dac33->supplies),
					  dac33->supplies);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to enable supplies: %d\n", ret);
			जाओ निकास;
		पूर्ण

		अगर (dac33->घातer_gpio >= 0)
			gpio_set_value(dac33->घातer_gpio, 1);

		dac33->chip_घातer = 1;
	पूर्ण अन्यथा अणु
		dac33_soft_घातer(component, 0);
		अगर (dac33->घातer_gpio >= 0)
			gpio_set_value(dac33->घातer_gpio, 0);

		ret = regulator_bulk_disable(ARRAY_SIZE(dac33->supplies),
					     dac33->supplies);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to disable supplies: %d\n", ret);
			जाओ निकास;
		पूर्ण

		dac33->chip_घातer = 0;
	पूर्ण

निकास:
	mutex_unlock(&dac33->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dac33_playback_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (likely(dac33->substream)) अणु
			dac33_calculate_बार(dac33->substream, component);
			dac33_prepare_chip(dac33->substream, component);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		dac33_disable_digital(component);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dac33_get_fअगरo_mode(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = dac33->fअगरo_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक dac33_set_fअगरo_mode(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर (dac33->fअगरo_mode == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;
	/* Do not allow changes जबतक stream is running*/
	अगर (snd_soc_component_active(component))
		वापस -EPERM;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= DAC33_FIFO_LAST_MODE)
		ret = -EINVAL;
	अन्यथा
		dac33->fअगरo_mode = ucontrol->value.क्रमागतerated.item[0];

	वापस ret;
पूर्ण

/* Codec operation modes */
अटल स्थिर अक्षर *dac33_fअगरo_mode_texts[] = अणु
	"Bypass", "Mode 1", "Mode 7"
पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(dac33_fअगरo_mode_क्रमागत, dac33_fअगरo_mode_texts);

/* L/R Line Output Gain */
अटल स्थिर अक्षर *lr_lineout_gain_texts[] = अणु
	"Line -12dB DAC 0dB", "Line -6dB DAC 6dB",
	"Line 0dB DAC 12dB", "Line 6dB DAC 18dB",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(l_lineout_gain_क्रमागत,
			    DAC33_LDAC_PWR_CTRL, 0,
			    lr_lineout_gain_texts);

अटल SOC_ENUM_SINGLE_DECL(r_lineout_gain_क्रमागत,
			    DAC33_RDAC_PWR_CTRL, 0,
			    lr_lineout_gain_texts);

/*
 * DACL/R digital volume control:
 * from 0 dB to -63.5 in 0.5 dB steps
 * Need to be inverted later on:
 * 0x00 == 0 dB
 * 0x7f == -63.5 dB
 */
अटल DECLARE_TLV_DB_SCALE(dac_digivol_tlv, -6350, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new dac33_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC Digital Playback Volume",
		DAC33_LDAC_DIG_VOL_CTRL, DAC33_RDAC_DIG_VOL_CTRL,
		0, 0x7f, 1, dac_digivol_tlv),
	SOC_DOUBLE_R("DAC Digital Playback Switch",
		 DAC33_LDAC_DIG_VOL_CTRL, DAC33_RDAC_DIG_VOL_CTRL, 7, 1, 1),
	SOC_DOUBLE_R("Line to Line Out Volume",
		 DAC33_LINEL_TO_LLO_VOL, DAC33_LINER_TO_RLO_VOL, 0, 127, 1),
	SOC_ENUM("Left Line Output Gain", l_lineout_gain_क्रमागत),
	SOC_ENUM("Right Line Output Gain", r_lineout_gain_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac33_mode_snd_controls[] = अणु
	SOC_ENUM_EXT("FIFO Mode", dac33_fअगरo_mode_क्रमागत,
		 dac33_get_fअगरo_mode, dac33_set_fअगरo_mode),
पूर्ण;

/* Analog bypass */
अटल स्थिर काष्ठा snd_kcontrol_new dac33_dapm_abypassl_control =
	SOC_DAPM_SINGLE("Switch", DAC33_LINEL_TO_LLO_VOL, 7, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new dac33_dapm_abypassr_control =
	SOC_DAPM_SINGLE("Switch", DAC33_LINER_TO_RLO_VOL, 7, 1, 1);

/* LOP L/R invert selection */
अटल स्थिर अक्षर *dac33_lr_lom_texts[] = अणु"DAC", "LOP"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac33_left_lom_क्रमागत,
			    DAC33_OUT_AMP_CTRL, 3,
			    dac33_lr_lom_texts);

अटल स्थिर काष्ठा snd_kcontrol_new dac33_dapm_left_lom_control =
SOC_DAPM_ENUM("Route", dac33_left_lom_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(dac33_right_lom_क्रमागत,
			    DAC33_OUT_AMP_CTRL, 2,
			    dac33_lr_lom_texts);

अटल स्थिर काष्ठा snd_kcontrol_new dac33_dapm_right_lom_control =
SOC_DAPM_ENUM("Route", dac33_right_lom_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget dac33_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("LEFT_LO"),
	SND_SOC_DAPM_OUTPUT("RIGHT_LO"),

	SND_SOC_DAPM_INPUT("LINEL"),
	SND_SOC_DAPM_INPUT("LINER"),

	SND_SOC_DAPM_DAC("DACL", "Left Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACR", "Right Playback", SND_SOC_NOPM, 0, 0),

	/* Analog bypass */
	SND_SOC_DAPM_SWITCH("Analog Left Bypass", SND_SOC_NOPM, 0, 0,
				&dac33_dapm_abypassl_control),
	SND_SOC_DAPM_SWITCH("Analog Right Bypass", SND_SOC_NOPM, 0, 0,
				&dac33_dapm_abypassr_control),

	SND_SOC_DAPM_MUX("Left LOM Inverted From", SND_SOC_NOPM, 0, 0,
		&dac33_dapm_left_lom_control),
	SND_SOC_DAPM_MUX("Right LOM Inverted From", SND_SOC_NOPM, 0, 0,
		&dac33_dapm_right_lom_control),
	/*
	 * For DAPM path, when only the anlog bypass path is enabled, and the
	 * LOP inverted from the corresponding DAC side.
	 * This is needed, so we can attach the DAC घातer supply in this हाल.
	 */
	SND_SOC_DAPM_PGA("Left Bypass PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Bypass PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_REG(snd_soc_dapm_mixer, "Output Left Amplifier",
			 DAC33_OUT_AMP_PWR_CTRL, 6, 3, 3, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_mixer, "Output Right Amplifier",
			 DAC33_OUT_AMP_PWR_CTRL, 4, 3, 3, 0),

	SND_SOC_DAPM_SUPPLY("Left DAC Power",
			    DAC33_LDAC_PWR_CTRL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Right DAC Power",
			    DAC33_RDAC_PWR_CTRL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Codec Power",
			    DAC33_PWR_CTRL, 4, 0, शून्य, 0),

	SND_SOC_DAPM_PRE("Pre Playback", dac33_playback_event),
	SND_SOC_DAPM_POST("Post Playback", dac33_playback_event),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Analog bypass */
	अणु"Analog Left Bypass", "Switch", "LINEL"पूर्ण,
	अणु"Analog Right Bypass", "Switch", "LINER"पूर्ण,

	अणु"Output Left Amplifier", शून्य, "DACL"पूर्ण,
	अणु"Output Right Amplifier", शून्य, "DACR"पूर्ण,

	अणु"Left Bypass PGA", शून्य, "Analog Left Bypass"पूर्ण,
	अणु"Right Bypass PGA", शून्य, "Analog Right Bypass"पूर्ण,

	अणु"Left LOM Inverted From", "DAC", "Left Bypass PGA"पूर्ण,
	अणु"Right LOM Inverted From", "DAC", "Right Bypass PGA"पूर्ण,
	अणु"Left LOM Inverted From", "LOP", "Analog Left Bypass"पूर्ण,
	अणु"Right LOM Inverted From", "LOP", "Analog Right Bypass"पूर्ण,

	अणु"Output Left Amplifier", शून्य, "Left LOM Inverted From"पूर्ण,
	अणु"Output Right Amplifier", शून्य, "Right LOM Inverted From"पूर्ण,

	अणु"DACL", शून्य, "Left DAC Power"पूर्ण,
	अणु"DACR", शून्य, "Right DAC Power"पूर्ण,

	अणु"Left Bypass PGA", शून्य, "Left DAC Power"पूर्ण,
	अणु"Right Bypass PGA", शून्य, "Right DAC Power"पूर्ण,

	/* output */
	अणु"LEFT_LO", शून्य, "Output Left Amplifier"पूर्ण,
	अणु"RIGHT_LO", शून्य, "Output Right Amplifier"पूर्ण,

	अणु"LEFT_LO", शून्य, "Codec Power"पूर्ण,
	अणु"RIGHT_LO", शून्य, "Codec Power"पूर्ण,
पूर्ण;

अटल पूर्णांक dac33_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Coming from OFF, चयन on the component */
			ret = dac33_hard_घातer(component, 1);
			अगर (ret != 0)
				वापस ret;

			dac33_init_chip(component);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Do not घातer off, when the component is alपढ़ोy off */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			वापस 0;
		ret = dac33_hard_घातer(component, 0);
		अगर (ret != 0)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dac33_prefill_handler(काष्ठा tlv320dac33_priv *dac33)
अणु
	काष्ठा snd_soc_component *component = dac33->component;
	अचिन्हित पूर्णांक delay;
	अचिन्हित दीर्घ flags;

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		dac33_ग_लिखो16(component, DAC33_NSAMPLE_MSB,
			DAC33_THRREG(dac33->nsample));

		/* Take the बारtamps */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp2 = kसमय_प्रकारo_us(kसमय_get());
		dac33->t_stamp1 = dac33->t_stamp2;
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_ग_लिखो16(component, DAC33_PREFILL_MSB,
				DAC33_THRREG(dac33->alarm_threshold));
		/* Enable Alarm Threshold IRQ with a delay */
		delay = SAMPLES_TO_US(dac33->burst_rate,
				     dac33->alarm_threshold) + 1000;
		usleep_range(delay, delay + 500);
		dac33_ग_लिखो(component, DAC33_FIFO_IRQ_MASK, DAC33_MAT);
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		/* Take the बारtamp */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp1 = kसमय_प्रकारo_us(kसमय_get());
		/* Move back the बारtamp with drain समय */
		dac33->t_stamp1 -= dac33->mode7_us_to_lthr;
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_ग_लिखो16(component, DAC33_PREFILL_MSB,
				DAC33_THRREG(DAC33_MODE7_MARGIN));

		/* Enable Upper Threshold IRQ */
		dac33_ग_लिखो(component, DAC33_FIFO_IRQ_MASK, DAC33_MUT);
		अवरोध;
	शेष:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fअगरo_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dac33_playback_handler(काष्ठा tlv320dac33_priv *dac33)
अणु
	काष्ठा snd_soc_component *component = dac33->component;
	अचिन्हित दीर्घ flags;

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		/* Take the बारtamp */
		spin_lock_irqsave(&dac33->lock, flags);
		dac33->t_stamp2 = kसमय_प्रकारo_us(kसमय_get());
		spin_unlock_irqrestore(&dac33->lock, flags);

		dac33_ग_लिखो16(component, DAC33_NSAMPLE_MSB,
				DAC33_THRREG(dac33->nsample));
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		/* At the moment we are not using पूर्णांकerrupts in mode7 */
		अवरोध;
	शेष:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fअगरo_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dac33_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा tlv320dac33_priv *dac33;
	u8 reg;

	dac33 = container_of(work, काष्ठा tlv320dac33_priv, work);
	component = dac33->component;

	mutex_lock(&dac33->mutex);
	चयन (dac33->state) अणु
	हाल DAC33_PREFILL:
		dac33->state = DAC33_PLAYBACK;
		dac33_prefill_handler(dac33);
		अवरोध;
	हाल DAC33_PLAYBACK:
		dac33_playback_handler(dac33);
		अवरोध;
	हाल DAC33_IDLE:
		अवरोध;
	हाल DAC33_FLUSH:
		dac33->state = DAC33_IDLE;
		/* Mask all पूर्णांकerrupts from dac33 */
		dac33_ग_लिखो(component, DAC33_FIFO_IRQ_MASK, 0);

		/* flush fअगरo */
		reg = dac33_पढ़ो_reg_cache(component, DAC33_FIFO_CTRL_A);
		reg |= DAC33_FIFOFLUSH;
		dac33_ग_लिखो(component, DAC33_FIFO_CTRL_A, reg);
		अवरोध;
	पूर्ण
	mutex_unlock(&dac33->mutex);
पूर्ण

अटल irqवापस_t dac33_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा snd_soc_component *component = dev;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dac33->lock, flags);
	dac33->t_stamp1 = kसमय_प्रकारo_us(kसमय_get());
	spin_unlock_irqrestore(&dac33->lock, flags);

	/* Do not schedule the workqueue in Mode7 */
	अगर (dac33->fअगरo_mode != DAC33_FIFO_MODE7)
		schedule_work(&dac33->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dac33_oscरुको(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक समयout = 60;
	u8 reg;

	करो अणु
		usleep_range(1000, 2000);
		dac33_पढ़ो(component, DAC33_INT_OSC_STATUS, &reg);
	पूर्ण जबतक (((reg & 0x03) != DAC33_OSCSTATUS_NORMAL) && समयout--);
	अगर ((reg & 0x03) != DAC33_OSCSTATUS_NORMAL)
		dev_err(component->dev,
			"internal oscillator calibration failed\n");
पूर्ण

अटल पूर्णांक dac33_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	/* Stream started, save the substream poपूर्णांकer */
	dac33->substream = substream;

	वापस 0;
पूर्ण

अटल व्योम dac33_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	dac33->substream = शून्य;
पूर्ण

#घोषणा CALC_BURST_RATE(bclkभाग, bclk_per_sample) \
	(BURST_BASEFREQ_HZ / bclkभाग / bclk_per_sample)
अटल पूर्णांक dac33_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	/* Check parameters क्रम validity */
	चयन (params_rate(params)) अणु
	हाल 44100:
	हाल 48000:
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported rate %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		dac33->fअगरo_size = DAC33_FIFO_SIZE_16BIT;
		dac33->burst_rate = CALC_BURST_RATE(dac33->burst_bclkभाग, 32);
		अवरोध;
	हाल 32:
		dac33->fअगरo_size = DAC33_FIFO_SIZE_24BIT;
		dac33->burst_rate = CALC_BURST_RATE(dac33->burst_bclkभाग, 64);
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported width %d\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CALC_OSCSET(rate, refclk) ( \
	((((rate * 10000) / refclk) * 4096) + 7000) / 10000)
#घोषणा CALC_RATIOSET(rate, refclk) ( \
	((((refclk  * 100000) / rate) * 16384) + 50000) / 100000)

/*
 * tlv320dac33 is strict on the sequence of the रेजिस्टर ग_लिखोs, अगर the रेजिस्टर
 * ग_लिखोs happens in dअगरferent order, than dac33 might end up in unknown state.
 * Use the known, working sequence of रेजिस्टर ग_लिखोs to initialize the dac33.
 */
अटल पूर्णांक dac33_prepare_chip(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_component *component)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक oscset, ratioset, pwr_ctrl, reg_पंचांगp;
	u8 aictrl_a, aictrl_b, fअगरoctrl_a;

	चयन (substream->runसमय->rate) अणु
	हाल 44100:
	हाल 48000:
		oscset = CALC_OSCSET(substream->runसमय->rate, dac33->refclk);
		ratioset = CALC_RATIOSET(substream->runसमय->rate,
					 dac33->refclk);
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported rate %d\n",
			substream->runसमय->rate);
		वापस -EINVAL;
	पूर्ण


	aictrl_a = dac33_पढ़ो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A);
	aictrl_a &= ~(DAC33_NCYCL_MASK | DAC33_WLEN_MASK);
	/* Read FIFO control A, and clear FIFO flush bit */
	fअगरoctrl_a = dac33_पढ़ो_reg_cache(component, DAC33_FIFO_CTRL_A);
	fअगरoctrl_a &= ~DAC33_FIFOFLUSH;

	fअगरoctrl_a &= ~DAC33_WIDTH;
	चयन (substream->runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		aictrl_a |= (DAC33_NCYCL_16 | DAC33_WLEN_16);
		fअगरoctrl_a |= DAC33_WIDTH;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		aictrl_a |= (DAC33_NCYCL_32 | DAC33_WLEN_24);
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported format %d\n",
			substream->runसमय->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dac33->mutex);

	अगर (!dac33->chip_घातer) अणु
		/*
		 * Chip is not घातered yet.
		 * Do the init in the dac33_set_bias_level later.
		 */
		mutex_unlock(&dac33->mutex);
		वापस 0;
	पूर्ण

	dac33_soft_घातer(component, 0);
	dac33_soft_घातer(component, 1);

	reg_पंचांगp = dac33_पढ़ो_reg_cache(component, DAC33_INT_OSC_CTRL);
	dac33_ग_लिखो(component, DAC33_INT_OSC_CTRL, reg_पंचांगp);

	/* Write रेजिस्टरs 0x08 and 0x09 (MSB, LSB) */
	dac33_ग_लिखो16(component, DAC33_INT_OSC_FREQ_RAT_A, oscset);

	/* OSC calibration समय */
	dac33_ग_लिखो(component, DAC33_CALIB_TIME, 96);

	/* adjusपंचांगent treshold & step */
	dac33_ग_लिखो(component, DAC33_INT_OSC_CTRL_B, DAC33_ADJTHRSHLD(2) |
						 DAC33_ADJSTEP(1));

	/* भाग=4 / gain=1 / भाग */
	dac33_ग_लिखो(component, DAC33_INT_OSC_CTRL_C, DAC33_REFDIV(4));

	pwr_ctrl = dac33_पढ़ो_reg_cache(component, DAC33_PWR_CTRL);
	pwr_ctrl |= DAC33_OSCPDNB | DAC33_DACRPDNB | DAC33_DACLPDNB;
	dac33_ग_लिखो(component, DAC33_PWR_CTRL, pwr_ctrl);

	dac33_oscरुको(component);

	अगर (dac33->fअगरo_mode) अणु
		/* Generic क्रम all FIFO modes */
		/* 50-51 : ASRC Control रेजिस्टरs */
		dac33_ग_लिखो(component, DAC33_ASRC_CTRL_A, DAC33_SRCLKDIV(1));
		dac33_ग_लिखो(component, DAC33_ASRC_CTRL_B, 1); /* ??? */

		/* Write रेजिस्टरs 0x34 and 0x35 (MSB, LSB) */
		dac33_ग_लिखो16(component, DAC33_SRC_REF_CLK_RATIO_A, ratioset);

		/* Set पूर्णांकerrupts to high active */
		dac33_ग_लिखो(component, DAC33_INTP_CTRL_A, DAC33_INTPM_AHIGH);
	पूर्ण अन्यथा अणु
		/* FIFO bypass mode */
		/* 50-51 : ASRC Control रेजिस्टरs */
		dac33_ग_लिखो(component, DAC33_ASRC_CTRL_A, DAC33_SRCBYP);
		dac33_ग_लिखो(component, DAC33_ASRC_CTRL_B, 0); /* ??? */
	पूर्ण

	/* Interrupt behaviour configuration */
	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		dac33_ग_लिखो(component, DAC33_FIFO_IRQ_MODE_B,
			    DAC33_ATM(DAC33_FIFO_IRQ_MODE_LEVEL));
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		dac33_ग_लिखो(component, DAC33_FIFO_IRQ_MODE_A,
			DAC33_UTM(DAC33_FIFO_IRQ_MODE_LEVEL));
		अवरोध;
	शेष:
		/* in FIFO bypass mode, the पूर्णांकerrupts are not used */
		अवरोध;
	पूर्ण

	aictrl_b = dac33_पढ़ो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		/*
		 * For mode1:
		 * Disable the FIFO bypass (Enable the use of FIFO)
		 * Select nSample mode
		 * BCLK is only running when data is needed by DAC33
		 */
		fअगरoctrl_a &= ~DAC33_FBYPAS;
		fअगरoctrl_a &= ~DAC33_FAUTO;
		अगर (dac33->keep_bclk)
			aictrl_b |= DAC33_BCLKON;
		अन्यथा
			aictrl_b &= ~DAC33_BCLKON;
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		/*
		 * For mode1:
		 * Disable the FIFO bypass (Enable the use of FIFO)
		 * Select Threshold mode
		 * BCLK is only running when data is needed by DAC33
		 */
		fअगरoctrl_a &= ~DAC33_FBYPAS;
		fअगरoctrl_a |= DAC33_FAUTO;
		अगर (dac33->keep_bclk)
			aictrl_b |= DAC33_BCLKON;
		अन्यथा
			aictrl_b &= ~DAC33_BCLKON;
		अवरोध;
	शेष:
		/*
		 * For FIFO bypass mode:
		 * Enable the FIFO bypass (Disable the FIFO use)
		 * Set the BCLK as continuous
		 */
		fअगरoctrl_a |= DAC33_FBYPAS;
		aictrl_b |= DAC33_BCLKON;
		अवरोध;
	पूर्ण

	dac33_ग_लिखो(component, DAC33_FIFO_CTRL_A, fअगरoctrl_a);
	dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_A, aictrl_a);
	dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_B, aictrl_b);

	/*
	 * BCLK भागide ratio
	 * 0: 1.5
	 * 1: 1
	 * 2: 2
	 * ...
	 * 254: 254
	 * 255: 255
	 */
	अगर (dac33->fअगरo_mode)
		dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_C,
							dac33->burst_bclkभाग);
	अन्यथा
		अगर (substream->runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
			dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_C, 32);
		अन्यथा
			dac33_ग_लिखो(component, DAC33_SER_AUDIOIF_CTRL_C, 16);

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		dac33_ग_लिखो16(component, DAC33_ATHR_MSB,
			      DAC33_THRREG(dac33->alarm_threshold));
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		/*
		 * Configure the threshold levels, and leave 10 sample space
		 * at the bottom, and also at the top of the FIFO
		 */
		dac33_ग_लिखो16(component, DAC33_UTHR_MSB, DAC33_THRREG(dac33->uthr));
		dac33_ग_लिखो16(component, DAC33_LTHR_MSB,
			      DAC33_THRREG(DAC33_MODE7_MARGIN));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&dac33->mutex);

	वापस 0;
पूर्ण

अटल व्योम dac33_calculate_बार(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_component *component)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक period_size = substream->runसमय->period_size;
	अचिन्हित पूर्णांक rate = substream->runसमय->rate;
	अचिन्हित पूर्णांक nsample_limit;

	/* In bypass mode we करोn't need to calculate */
	अगर (!dac33->fअगरo_mode)
		वापस;

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_MODE1:
		/* Number of samples under i2c latency */
		dac33->alarm_threshold = US_TO_SAMPLES(rate,
						dac33->mode1_latency);
		nsample_limit = dac33->fअगरo_size - dac33->alarm_threshold;

		अगर (period_size <= dac33->alarm_threshold)
			/*
			 * Configure nSamaple to number of periods,
			 * which covers the latency requironment.
			 */
			dac33->nsample = period_size *
				((dac33->alarm_threshold / period_size) +
				 ((dac33->alarm_threshold % period_size) ?
				1 : 0));
		अन्यथा अगर (period_size > nsample_limit)
			dac33->nsample = nsample_limit;
		अन्यथा
			dac33->nsample = period_size;

		dac33->mode1_us_burst = SAMPLES_TO_US(dac33->burst_rate,
						      dac33->nsample);
		dac33->t_stamp1 = 0;
		dac33->t_stamp2 = 0;
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		dac33->uthr = UTHR_FROM_PERIOD_SIZE(period_size, rate,
						    dac33->burst_rate) + 9;
		अगर (dac33->uthr > (dac33->fअगरo_size - DAC33_MODE7_MARGIN))
			dac33->uthr = dac33->fअगरo_size - DAC33_MODE7_MARGIN;
		अगर (dac33->uthr < (DAC33_MODE7_MARGIN + 10))
			dac33->uthr = (DAC33_MODE7_MARGIN + 10);

		dac33->mode7_us_to_lthr =
				SAMPLES_TO_US(substream->runसमय->rate,
					dac33->uthr - DAC33_MODE7_MARGIN + 1);
		dac33->t_stamp1 = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल पूर्णांक dac33_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (dac33->fअगरo_mode) अणु
			dac33->state = DAC33_PREFILL;
			schedule_work(&dac33->work);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (dac33->fअगरo_mode) अणु
			dac33->state = DAC33_FLUSH;
			schedule_work(&dac33->work);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_sframes_t dac33_dai_delay(
			काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ दीर्घ t0, t1, t_now;
	अचिन्हित पूर्णांक समय_delta, uthr;
	पूर्णांक samples_out, samples_in, samples;
	snd_pcm_sframes_t delay = 0;
	अचिन्हित दीर्घ flags;

	चयन (dac33->fअगरo_mode) अणु
	हाल DAC33_FIFO_BYPASS:
		अवरोध;
	हाल DAC33_FIFO_MODE1:
		spin_lock_irqsave(&dac33->lock, flags);
		t0 = dac33->t_stamp1;
		t1 = dac33->t_stamp2;
		spin_unlock_irqrestore(&dac33->lock, flags);
		t_now = kसमय_प्रकारo_us(kसमय_get());

		/* We have not started to fill the FIFO yet, delay is 0 */
		अगर (!t1)
			जाओ out;

		अगर (t0 > t1) अणु
			/*
			 * Phase 1:
			 * After Alarm threshold, and beक्रमe nSample ग_लिखो
			 */
			समय_delta = t_now - t0;
			samples_out = समय_delta ? US_TO_SAMPLES(
						substream->runसमय->rate,
						समय_delta) : 0;

			अगर (likely(dac33->alarm_threshold > samples_out))
				delay = dac33->alarm_threshold - samples_out;
			अन्यथा
				delay = 0;
		पूर्ण अन्यथा अगर ((t_now - t1) <= dac33->mode1_us_burst) अणु
			/*
			 * Phase 2:
			 * After nSample ग_लिखो (during burst operation)
			 */
			समय_delta = t_now - t0;
			samples_out = समय_delta ? US_TO_SAMPLES(
						substream->runसमय->rate,
						समय_delta) : 0;

			समय_delta = t_now - t1;
			samples_in = समय_delta ? US_TO_SAMPLES(
						dac33->burst_rate,
						समय_delta) : 0;

			samples = dac33->alarm_threshold;
			samples += (samples_in - samples_out);

			अगर (likely(samples > 0))
				delay = samples;
			अन्यथा
				delay = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Phase 3:
			 * After burst operation, beक्रमe next alarm threshold
			 */
			समय_delta = t_now - t0;
			samples_out = समय_delta ? US_TO_SAMPLES(
						substream->runसमय->rate,
						समय_delta) : 0;

			samples_in = dac33->nsample;
			samples = dac33->alarm_threshold;
			samples += (samples_in - samples_out);

			अगर (likely(samples > 0))
				delay = samples > dac33->fअगरo_size ?
					dac33->fअगरo_size : samples;
			अन्यथा
				delay = 0;
		पूर्ण
		अवरोध;
	हाल DAC33_FIFO_MODE7:
		spin_lock_irqsave(&dac33->lock, flags);
		t0 = dac33->t_stamp1;
		uthr = dac33->uthr;
		spin_unlock_irqrestore(&dac33->lock, flags);
		t_now = kसमय_प्रकारo_us(kसमय_get());

		/* We have not started to fill the FIFO yet, delay is 0 */
		अगर (!t0)
			जाओ out;

		अगर (t_now <= t0) अणु
			/*
			 * Either the बारtamps are messed or equal. Report
			 * maximum delay
			 */
			delay = uthr;
			जाओ out;
		पूर्ण

		समय_delta = t_now - t0;
		अगर (समय_delta <= dac33->mode7_us_to_lthr) अणु
			/*
			* Phase 1:
			* After burst (draining phase)
			*/
			samples_out = US_TO_SAMPLES(
					substream->runसमय->rate,
					समय_delta);

			अगर (likely(uthr > samples_out))
				delay = uthr - samples_out;
			अन्यथा
				delay = 0;
		पूर्ण अन्यथा अणु
			/*
			* Phase 2:
			* During burst operation
			*/
			समय_delta = समय_delta - dac33->mode7_us_to_lthr;

			samples_out = US_TO_SAMPLES(
					substream->runसमय->rate,
					समय_delta);
			samples_in = US_TO_SAMPLES(
					dac33->burst_rate,
					समय_delta);
			delay = DAC33_MODE7_MARGIN + samples_in - samples_out;

			अगर (unlikely(delay > uthr))
				delay = uthr;
		पूर्ण
		अवरोध;
	शेष:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fअगरo_mode);
		अवरोध;
	पूर्ण
out:
	वापस delay;
पूर्ण

अटल पूर्णांक dac33_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 ioc_reg, asrcb_reg;

	ioc_reg = dac33_पढ़ो_reg_cache(component, DAC33_INT_OSC_CTRL);
	asrcb_reg = dac33_पढ़ो_reg_cache(component, DAC33_ASRC_CTRL_B);
	चयन (clk_id) अणु
	हाल TLV320DAC33_MCLK:
		ioc_reg |= DAC33_REFSEL;
		asrcb_reg |= DAC33_SRCREFSEL;
		अवरोध;
	हाल TLV320DAC33_SLEEPCLK:
		ioc_reg &= ~DAC33_REFSEL;
		asrcb_reg &= ~DAC33_SRCREFSEL;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock ID (%d)\n", clk_id);
		अवरोध;
	पूर्ण
	dac33->refclk = freq;

	dac33_ग_लिखो_reg_cache(component, DAC33_INT_OSC_CTRL, ioc_reg);
	dac33_ग_लिखो_reg_cache(component, DAC33_ASRC_CTRL_B, asrcb_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dac33_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			     अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 aictrl_a, aictrl_b;

	aictrl_a = dac33_पढ़ो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A);
	aictrl_b = dac33_पढ़ो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);
	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* Codec Master */
		aictrl_a |= (DAC33_MSBCLK | DAC33_MSWCLK);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* Codec Slave */
		अगर (dac33->fअगरo_mode) अणु
			dev_err(component->dev, "FIFO mode requires master mode\n");
			वापस -EINVAL;
		पूर्ण अन्यथा
			aictrl_a &= ~(DAC33_MSBCLK | DAC33_MSWCLK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	aictrl_a &= ~DAC33_AFMT_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		aictrl_a |= DAC33_AFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		aictrl_a |= DAC33_AFMT_DSP;
		aictrl_b &= ~DAC33_DATA_DELAY_MASK;
		aictrl_b |= DAC33_DATA_DELAY(0);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		aictrl_a |= DAC33_AFMT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aictrl_a |= DAC33_AFMT_LEFT_J;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported format (%u)\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	dac33_ग_लिखो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A, aictrl_a);
	dac33_ग_लिखो_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B, aictrl_b);

	वापस 0;
पूर्ण

अटल पूर्णांक dac33_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	dac33->component = component;

	/* Read the tlv320dac33 ID रेजिस्टरs */
	ret = dac33_hard_घातer(component, 1);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to power up component: %d\n", ret);
		जाओ err_घातer;
	पूर्ण
	ret = dac33_पढ़ो_id(component);
	dac33_hard_घातer(component, 0);

	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to read chip ID: %d\n", ret);
		ret = -ENODEV;
		जाओ err_घातer;
	पूर्ण

	/* Check अगर the IRQ number is valid and request it */
	अगर (dac33->irq >= 0) अणु
		ret = request_irq(dac33->irq, dac33_पूर्णांकerrupt_handler,
				  IRQF_TRIGGER_RISING,
				  component->name, component);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Could not request IRQ%d (%d)\n",
						dac33->irq, ret);
			dac33->irq = -1;
		पूर्ण
		अगर (dac33->irq != -1) अणु
			INIT_WORK(&dac33->work, dac33_work);
		पूर्ण
	पूर्ण

	/* Only add the FIFO controls, अगर we have valid IRQ number */
	अगर (dac33->irq >= 0)
		snd_soc_add_component_controls(component, dac33_mode_snd_controls,
				     ARRAY_SIZE(dac33_mode_snd_controls));

err_घातer:
	वापस ret;
पूर्ण

अटल व्योम dac33_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	अगर (dac33->irq >= 0) अणु
		मुक्त_irq(dac33->irq, dac33->component);
		flush_work(&dac33->work);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tlv320dac33 = अणु
	.पढ़ो			= dac33_पढ़ो_reg_cache,
	.ग_लिखो			= dac33_ग_लिखो_locked,
	.set_bias_level		= dac33_set_bias_level,
	.probe			= dac33_soc_probe,
	.हटाओ			= dac33_soc_हटाओ,
	.controls		= dac33_snd_controls,
	.num_controls		= ARRAY_SIZE(dac33_snd_controls),
	.dapm_widमाला_लो		= dac33_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(dac33_dapm_widमाला_लो),
	.dapm_routes		= audio_map,
	.num_dapm_routes	= ARRAY_SIZE(audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#घोषणा DAC33_RATES	(SNDRV_PCM_RATE_44100 | \
			 SNDRV_PCM_RATE_48000)
#घोषणा DAC33_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops dac33_dai_ops = अणु
	.startup	= dac33_startup,
	.shutकरोwn	= dac33_shutकरोwn,
	.hw_params	= dac33_hw_params,
	.trigger	= dac33_pcm_trigger,
	.delay		= dac33_dai_delay,
	.set_sysclk	= dac33_set_dai_sysclk,
	.set_fmt	= dac33_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver dac33_dai = अणु
	.name = "tlv320dac33-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = DAC33_RATES,
		.क्रमmats = DAC33_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.ops = &dac33_dai_ops,
पूर्ण;

अटल पूर्णांक dac33_i2c_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tlv320dac33_platक्रमm_data *pdata;
	काष्ठा tlv320dac33_priv *dac33;
	पूर्णांक ret, i;

	अगर (client->dev.platक्रमm_data == शून्य) अणु
		dev_err(&client->dev, "Platform data not set\n");
		वापस -ENODEV;
	पूर्ण
	pdata = client->dev.platक्रमm_data;

	dac33 = devm_kzalloc(&client->dev, माप(काष्ठा tlv320dac33_priv),
			     GFP_KERNEL);
	अगर (dac33 == शून्य)
		वापस -ENOMEM;

	dac33->reg_cache = devm_kmemdup(&client->dev,
					dac33_reg,
					ARRAY_SIZE(dac33_reg) * माप(u8),
					GFP_KERNEL);
	अगर (!dac33->reg_cache)
		वापस -ENOMEM;

	dac33->i2c = client;
	mutex_init(&dac33->mutex);
	spin_lock_init(&dac33->lock);

	i2c_set_clientdata(client, dac33);

	dac33->घातer_gpio = pdata->घातer_gpio;
	dac33->burst_bclkभाग = pdata->burst_bclkभाग;
	dac33->keep_bclk = pdata->keep_bclk;
	dac33->mode1_latency = pdata->mode1_latency;
	अगर (!dac33->mode1_latency)
		dac33->mode1_latency = 10000; /* 10ms */
	dac33->irq = client->irq;
	/* Disable FIFO use by शेष */
	dac33->fअगरo_mode = DAC33_FIFO_BYPASS;

	/* Check अगर the reset GPIO number is valid and request it */
	अगर (dac33->घातer_gpio >= 0) अणु
		ret = gpio_request(dac33->घातer_gpio, "tlv320dac33 reset");
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"Failed to request reset GPIO (%d)\n",
				dac33->घातer_gpio);
			जाओ err_gpio;
		पूर्ण
		gpio_direction_output(dac33->घातer_gpio, 0);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dac33->supplies); i++)
		dac33->supplies[i].supply = dac33_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev, ARRAY_SIZE(dac33->supplies),
				 dac33->supplies);

	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to request supplies: %d\n", ret);
		जाओ err_get;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&soc_component_dev_tlv320dac33, &dac33_dai, 1);
	अगर (ret < 0)
		जाओ err_get;

	वापस ret;
err_get:
	अगर (dac33->घातer_gpio >= 0)
		gpio_मुक्त(dac33->घातer_gpio);
err_gpio:
	वापस ret;
पूर्ण

अटल पूर्णांक dac33_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tlv320dac33_priv *dac33 = i2c_get_clientdata(client);

	अगर (unlikely(dac33->chip_घातer))
		dac33_hard_घातer(dac33->component, 0);

	अगर (dac33->घातer_gpio >= 0)
		gpio_मुक्त(dac33->घातer_gpio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tlv320dac33_i2c_id[] = अणु
	अणु
		.name = "tlv320dac33",
		.driver_data = 0,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tlv320dac33_i2c_id);

अटल काष्ठा i2c_driver tlv320dac33_i2c_driver = अणु
	.driver = अणु
		.name = "tlv320dac33-codec",
	पूर्ण,
	.probe		= dac33_i2c_probe,
	.हटाओ		= dac33_i2c_हटाओ,
	.id_table	= tlv320dac33_i2c_id,
पूर्ण;

module_i2c_driver(tlv320dac33_i2c_driver);

MODULE_DESCRIPTION("ASoC TLV320DAC33 codec driver");
MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_LICENSE("GPL");
