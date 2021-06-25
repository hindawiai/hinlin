<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell EBU Armada SoCs thermal sensor driver
 *
 * Copyright (C) 2013 Marvell
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/thermal.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "thermal_core.h"

/* Thermal Manager Control and Status Register */
#घोषणा PMU_TDC0_SW_RST_MASK		(0x1 << 1)
#घोषणा PMU_TM_DISABLE_OFFS		0
#घोषणा PMU_TM_DISABLE_MASK		(0x1 << PMU_TM_DISABLE_OFFS)
#घोषणा PMU_TDC0_REF_CAL_CNT_OFFS	11
#घोषणा PMU_TDC0_REF_CAL_CNT_MASK	(0x1ff << PMU_TDC0_REF_CAL_CNT_OFFS)
#घोषणा PMU_TDC0_OTF_CAL_MASK		(0x1 << 30)
#घोषणा PMU_TDC0_START_CAL_MASK		(0x1 << 25)

#घोषणा A375_UNIT_CONTROL_SHIFT		27
#घोषणा A375_UNIT_CONTROL_MASK		0x7
#घोषणा A375_READOUT_INVERT		BIT(15)
#घोषणा A375_HW_RESETn			BIT(8)

/* Errata fields */
#घोषणा CONTROL0_TSEN_TC_TRIM_MASK	0x7
#घोषणा CONTROL0_TSEN_TC_TRIM_VAL	0x3

#घोषणा CONTROL0_TSEN_START		BIT(0)
#घोषणा CONTROL0_TSEN_RESET		BIT(1)
#घोषणा CONTROL0_TSEN_ENABLE		BIT(2)
#घोषणा CONTROL0_TSEN_AVG_BYPASS	BIT(6)
#घोषणा CONTROL0_TSEN_CHAN_SHIFT	13
#घोषणा CONTROL0_TSEN_CHAN_MASK		0xF
#घोषणा CONTROL0_TSEN_OSR_SHIFT		24
#घोषणा CONTROL0_TSEN_OSR_MAX		0x3
#घोषणा CONTROL0_TSEN_MODE_SHIFT	30
#घोषणा CONTROL0_TSEN_MODE_EXTERNAL	0x2
#घोषणा CONTROL0_TSEN_MODE_MASK		0x3

#घोषणा CONTROL1_TSEN_AVG_MASK		0x7
#घोषणा CONTROL1_EXT_TSEN_SW_RESET	BIT(7)
#घोषणा CONTROL1_EXT_TSEN_HW_RESETn	BIT(8)
#घोषणा CONTROL1_TSEN_INT_EN		BIT(25)
#घोषणा CONTROL1_TSEN_SELECT_OFF	21
#घोषणा CONTROL1_TSEN_SELECT_MASK	0x3

#घोषणा STATUS_POLL_PERIOD_US		1000
#घोषणा STATUS_POLL_TIMEOUT_US		100000
#घोषणा OVERHEAT_INT_POLL_DELAY_MS	1000

काष्ठा armada_thermal_data;

/* Marvell EBU Thermal Sensor Dev Structure */
काष्ठा armada_thermal_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *syscon;
	अक्षर zone_name[THERMAL_NAME_LENGTH];
	/* serialize temperature पढ़ोs/updates */
	काष्ठा mutex update_lock;
	काष्ठा armada_thermal_data *data;
	काष्ठा thermal_zone_device *overheat_sensor;
	पूर्णांक पूर्णांकerrupt_source;
	पूर्णांक current_channel;
	दीर्घ current_threshold;
	दीर्घ current_hysteresis;
पूर्ण;

काष्ठा armada_thermal_data अणु
	/* Initialize the thermal IC */
	व्योम (*init)(काष्ठा platक्रमm_device *pdev,
		     काष्ठा armada_thermal_priv *priv);

	/* Formula coeficients: temp = (b - m * reg) / भाग */
	s64 coef_b;
	s64 coef_m;
	u32 coef_भाग;
	bool inverted;
	bool चिन्हित_sample;

	/* Register shअगरt and mask to access the sensor temperature */
	अचिन्हित पूर्णांक temp_shअगरt;
	अचिन्हित पूर्णांक temp_mask;
	अचिन्हित पूर्णांक thresh_shअगरt;
	अचिन्हित पूर्णांक hyst_shअगरt;
	अचिन्हित पूर्णांक hyst_mask;
	u32 is_valid_bit;

	/* Syscon access */
	अचिन्हित पूर्णांक syscon_control0_off;
	अचिन्हित पूर्णांक syscon_control1_off;
	अचिन्हित पूर्णांक syscon_status_off;
	अचिन्हित पूर्णांक dfx_irq_cause_off;
	अचिन्हित पूर्णांक dfx_irq_mask_off;
	अचिन्हित पूर्णांक dfx_overheat_irq;
	अचिन्हित पूर्णांक dfx_server_irq_mask_off;
	अचिन्हित पूर्णांक dfx_server_irq_en;

	/* One sensor is in the thermal IC, the others are in the CPUs अगर any */
	अचिन्हित पूर्णांक cpu_nr;
पूर्ण;

काष्ठा armada_drvdata अणु
	क्रमागत drvtype अणु
		LEGACY,
		SYSCON
	पूर्ण type;
	जोड़ अणु
		काष्ठा armada_thermal_priv *priv;
		काष्ठा thermal_zone_device *tz;
	पूर्ण data;
पूर्ण;

/*
 * काष्ठा armada_thermal_sensor - hold the inक्रमmation of one thermal sensor
 * @thermal: poपूर्णांकer to the local निजी काष्ठाure
 * @tzd: poपूर्णांकer to the thermal zone device
 * @id: identअगरier of the thermal sensor
 */
काष्ठा armada_thermal_sensor अणु
	काष्ठा armada_thermal_priv *priv;
	पूर्णांक id;
पूर्ण;

अटल व्योम armadaxp_init(काष्ठा platक्रमm_device *pdev,
			  काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg |= PMU_TDC0_OTF_CAL_MASK;

	/* Reference calibration value */
	reg &= ~PMU_TDC0_REF_CAL_CNT_MASK;
	reg |= (0xf1 << PMU_TDC0_REF_CAL_CNT_OFFS);

	/* Reset the sensor */
	reg |= PMU_TDC0_SW_RST_MASK;

	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	reg &= ~PMU_TDC0_SW_RST_MASK;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	/* Enable the sensor */
	regmap_पढ़ो(priv->syscon, data->syscon_status_off, &reg);
	reg &= ~PMU_TM_DISABLE_MASK;
	regmap_ग_लिखो(priv->syscon, data->syscon_status_off, reg);
पूर्ण

अटल व्योम armada370_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg |= PMU_TDC0_OTF_CAL_MASK;

	/* Reference calibration value */
	reg &= ~PMU_TDC0_REF_CAL_CNT_MASK;
	reg |= (0xf1 << PMU_TDC0_REF_CAL_CNT_OFFS);

	/* Reset the sensor */
	reg &= ~PMU_TDC0_START_CAL_MASK;

	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	msleep(10);
पूर्ण

अटल व्योम armada375_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg &= ~(A375_UNIT_CONTROL_MASK << A375_UNIT_CONTROL_SHIFT);
	reg &= ~A375_READOUT_INVERT;
	reg &= ~A375_HW_RESETn;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	msleep(20);

	reg |= A375_HW_RESETn;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	msleep(50);
पूर्ण

अटल पूर्णांक armada_रुको_sensor_validity(काष्ठा armada_thermal_priv *priv)
अणु
	u32 reg;

	वापस regmap_पढ़ो_poll_समयout(priv->syscon,
					priv->data->syscon_status_off, reg,
					reg & priv->data->is_valid_bit,
					STATUS_POLL_PERIOD_US,
					STATUS_POLL_TIMEOUT_US);
पूर्ण

अटल व्योम armada380_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	/* Disable the HW/SW reset */
	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg |= CONTROL1_EXT_TSEN_HW_RESETn;
	reg &= ~CONTROL1_EXT_TSEN_SW_RESET;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);

	/* Set Tsen Tc Trim to correct शेष value (errata #132698) */
	regmap_पढ़ो(priv->syscon, data->syscon_control0_off, &reg);
	reg &= ~CONTROL0_TSEN_TC_TRIM_MASK;
	reg |= CONTROL0_TSEN_TC_TRIM_VAL;
	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, reg);
पूर्ण

अटल व्योम armada_ap806_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_पढ़ो(priv->syscon, data->syscon_control0_off, &reg);
	reg &= ~CONTROL0_TSEN_RESET;
	reg |= CONTROL0_TSEN_START | CONTROL0_TSEN_ENABLE;

	/* Sample every ~2ms */
	reg |= CONTROL0_TSEN_OSR_MAX << CONTROL0_TSEN_OSR_SHIFT;

	/* Enable average (2 samples by शेष) */
	reg &= ~CONTROL0_TSEN_AVG_BYPASS;

	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, reg);
पूर्ण

अटल व्योम armada_cp110_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	armada380_init(pdev, priv);

	/* Sample every ~2ms */
	regmap_पढ़ो(priv->syscon, data->syscon_control0_off, &reg);
	reg |= CONTROL0_TSEN_OSR_MAX << CONTROL0_TSEN_OSR_SHIFT;
	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, reg);

	/* Average the output value over 2^1 = 2 samples */
	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg &= ~CONTROL1_TSEN_AVG_MASK;
	reg |= 1;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);
पूर्ण

अटल bool armada_is_valid(काष्ठा armada_thermal_priv *priv)
अणु
	u32 reg;

	अगर (!priv->data->is_valid_bit)
		वापस true;

	regmap_पढ़ो(priv->syscon, priv->data->syscon_status_off, &reg);

	वापस reg & priv->data->is_valid_bit;
पूर्ण

अटल व्योम armada_enable_overheat_पूर्णांकerrupt(काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	/* Clear DFX temperature IRQ cause */
	regmap_पढ़ो(priv->syscon, data->dfx_irq_cause_off, &reg);

	/* Enable DFX Temperature IRQ */
	regmap_पढ़ो(priv->syscon, data->dfx_irq_mask_off, &reg);
	reg |= data->dfx_overheat_irq;
	regmap_ग_लिखो(priv->syscon, data->dfx_irq_mask_off, reg);

	/* Enable DFX server IRQ */
	regmap_पढ़ो(priv->syscon, data->dfx_server_irq_mask_off, &reg);
	reg |= data->dfx_server_irq_en;
	regmap_ग_लिखो(priv->syscon, data->dfx_server_irq_mask_off, reg);

	/* Enable overheat पूर्णांकerrupt */
	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg |= CONTROL1_TSEN_INT_EN;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);
पूर्ण

अटल व्योम __maybe_unused
armada_disable_overheat_पूर्णांकerrupt(काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &reg);
	reg &= ~CONTROL1_TSEN_INT_EN;
	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, reg);
पूर्ण

/* There is currently no board with more than one sensor per channel */
अटल पूर्णांक armada_select_channel(काष्ठा armada_thermal_priv *priv, पूर्णांक channel)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	u32 ctrl0;

	अगर (channel < 0 || channel > priv->data->cpu_nr)
		वापस -EINVAL;

	अगर (priv->current_channel == channel)
		वापस 0;

	/* Stop the measurements */
	regmap_पढ़ो(priv->syscon, data->syscon_control0_off, &ctrl0);
	ctrl0 &= ~CONTROL0_TSEN_START;
	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, ctrl0);

	/* Reset the mode, पूर्णांकernal sensor will be स्वतःmatically selected */
	ctrl0 &= ~(CONTROL0_TSEN_MODE_MASK << CONTROL0_TSEN_MODE_SHIFT);

	/* Other channels are बाह्यal and should be selected accordingly */
	अगर (channel) अणु
		/* Change the mode to बाह्यal */
		ctrl0 |= CONTROL0_TSEN_MODE_EXTERNAL <<
			 CONTROL0_TSEN_MODE_SHIFT;
		/* Select the sensor */
		ctrl0 &= ~(CONTROL0_TSEN_CHAN_MASK << CONTROL0_TSEN_CHAN_SHIFT);
		ctrl0 |= (channel - 1) << CONTROL0_TSEN_CHAN_SHIFT;
	पूर्ण

	/* Actually set the mode/channel */
	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, ctrl0);
	priv->current_channel = channel;

	/* Re-start the measurements */
	ctrl0 |= CONTROL0_TSEN_START;
	regmap_ग_लिखो(priv->syscon, data->syscon_control0_off, ctrl0);

	/*
	 * The IP has a latency of ~15ms, so after updating the selected source,
	 * we must असलolutely रुको क्रम the sensor validity bit to ensure we पढ़ो
	 * actual data.
	 */
	अगर (armada_रुको_sensor_validity(priv)) अणु
		dev_err(priv->dev,
			"Temperature sensor reading not valid\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armada_पढ़ो_sensor(काष्ठा armada_thermal_priv *priv, पूर्णांक *temp)
अणु
	u32 reg, भाग;
	s64 sample, b, m;

	regmap_पढ़ो(priv->syscon, priv->data->syscon_status_off, &reg);
	reg = (reg >> priv->data->temp_shअगरt) & priv->data->temp_mask;
	अगर (priv->data->चिन्हित_sample)
		/* The most signअगरicant bit is the sign bit */
		sample = sign_extend32(reg, fls(priv->data->temp_mask) - 1);
	अन्यथा
		sample = reg;

	/* Get क्रमmula coeficients */
	b = priv->data->coef_b;
	m = priv->data->coef_m;
	भाग = priv->data->coef_भाग;

	अगर (priv->data->inverted)
		*temp = भाग_s64((m * sample) - b, भाग);
	अन्यथा
		*temp = भाग_s64(b - (m * sample), भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_get_temp_legacy(काष्ठा thermal_zone_device *thermal,
				  पूर्णांक *temp)
अणु
	काष्ठा armada_thermal_priv *priv = thermal->devdata;
	पूर्णांक ret;

	/* Valid check */
	अगर (!armada_is_valid(priv)) अणु
		dev_err(priv->dev,
			"Temperature sensor reading not valid\n");
		वापस -EIO;
	पूर्ण

	/* Do the actual पढ़ोing */
	ret = armada_पढ़ो_sensor(priv, temp);

	वापस ret;
पूर्ण

अटल काष्ठा thermal_zone_device_ops legacy_ops = अणु
	.get_temp = armada_get_temp_legacy,
पूर्ण;

अटल पूर्णांक armada_get_temp(व्योम *_sensor, पूर्णांक *temp)
अणु
	काष्ठा armada_thermal_sensor *sensor = _sensor;
	काष्ठा armada_thermal_priv *priv = sensor->priv;
	पूर्णांक ret;

	mutex_lock(&priv->update_lock);

	/* Select the desired channel */
	ret = armada_select_channel(priv, sensor->id);
	अगर (ret)
		जाओ unlock_mutex;

	/* Do the actual पढ़ोing */
	ret = armada_पढ़ो_sensor(priv, temp);
	अगर (ret)
		जाओ unlock_mutex;

	/*
	 * Select back the पूर्णांकerrupt source channel from which a potential
	 * critical trip poपूर्णांक has been set.
	 */
	ret = armada_select_channel(priv, priv->पूर्णांकerrupt_source);

unlock_mutex:
	mutex_unlock(&priv->update_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops of_ops = अणु
	.get_temp = armada_get_temp,
पूर्ण;

अटल अचिन्हित पूर्णांक armada_mc_to_reg_temp(काष्ठा armada_thermal_data *data,
					  अचिन्हित पूर्णांक temp_mc)
अणु
	s64 b = data->coef_b;
	s64 m = data->coef_m;
	s64 भाग = data->coef_भाग;
	अचिन्हित पूर्णांक sample;

	अगर (data->inverted)
		sample = भाग_s64(((temp_mc * भाग) + b), m);
	अन्यथा
		sample = भाग_s64((b - (temp_mc * भाग)), m);

	वापस sample & data->temp_mask;
पूर्ण

/*
 * The करोcumentation states:
 * high/low watermark = threshold +/- 0.4761 * 2^(hysteresis + 2)
 * which is the mathematical derivation क्रम:
 * 0x0 <=> 1.9तओC, 0x1 <=> 3.8तओC, 0x2 <=> 7.6तओC, 0x3 <=> 15.2तओC
 */
अटल अचिन्हित पूर्णांक hyst_levels_mc[] = अणु1900, 3800, 7600, 15200पूर्ण;

अटल अचिन्हित पूर्णांक armada_mc_to_reg_hyst(काष्ठा armada_thermal_data *data,
					  अचिन्हित पूर्णांक hyst_mc)
अणु
	पूर्णांक i;

	/*
	 * We will always take the smallest possible hysteresis to aव्योम risking
	 * the hardware पूर्णांकegrity by enlarging the threshold by +8तओC in the
	 * worst हाल.
	 */
	क्रम (i = ARRAY_SIZE(hyst_levels_mc) - 1; i > 0; i--)
		अगर (hyst_mc >= hyst_levels_mc[i])
			अवरोध;

	वापस i & data->hyst_mask;
पूर्ण

अटल व्योम armada_set_overheat_thresholds(काष्ठा armada_thermal_priv *priv,
					   पूर्णांक thresh_mc, पूर्णांक hyst_mc)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	अचिन्हित पूर्णांक threshold = armada_mc_to_reg_temp(data, thresh_mc);
	अचिन्हित पूर्णांक hysteresis = armada_mc_to_reg_hyst(data, hyst_mc);
	u32 ctrl1;

	regmap_पढ़ो(priv->syscon, data->syscon_control1_off, &ctrl1);

	/* Set Threshold */
	अगर (thresh_mc >= 0) अणु
		ctrl1 &= ~(data->temp_mask << data->thresh_shअगरt);
		ctrl1 |= threshold << data->thresh_shअगरt;
		priv->current_threshold = thresh_mc;
	पूर्ण

	/* Set Hysteresis */
	अगर (hyst_mc >= 0) अणु
		ctrl1 &= ~(data->hyst_mask << data->hyst_shअगरt);
		ctrl1 |= hysteresis << data->hyst_shअगरt;
		priv->current_hysteresis = hyst_mc;
	पूर्ण

	regmap_ग_लिखो(priv->syscon, data->syscon_control1_off, ctrl1);
पूर्ण

अटल irqवापस_t armada_overheat_isr(पूर्णांक irq, व्योम *blob)
अणु
	/*
	 * Disable the IRQ and जारी in thपढ़ो context (thermal core
	 * notअगरication and temperature monitoring).
	 */
	disable_irq_nosync(irq);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t armada_overheat_isr_thपढ़ो(पूर्णांक irq, व्योम *blob)
अणु
	काष्ठा armada_thermal_priv *priv = blob;
	पूर्णांक low_threshold = priv->current_threshold - priv->current_hysteresis;
	पूर्णांक temperature;
	u32 dummy;
	पूर्णांक ret;

	/* Notअगरy the core in thपढ़ो context */
	thermal_zone_device_update(priv->overheat_sensor,
				   THERMAL_EVENT_UNSPECIFIED);

	/*
	 * The overheat पूर्णांकerrupt must be cleared by पढ़ोing the DFX पूर्णांकerrupt
	 * cause _after_ the temperature has fallen करोwn to the low threshold.
	 * Otherwise future पूर्णांकerrupts might not be served.
	 */
	करो अणु
		msleep(OVERHEAT_INT_POLL_DELAY_MS);
		mutex_lock(&priv->update_lock);
		ret = armada_पढ़ो_sensor(priv, &temperature);
		mutex_unlock(&priv->update_lock);
		अगर (ret)
			जाओ enable_irq;
	पूर्ण जबतक (temperature >= low_threshold);

	regmap_पढ़ो(priv->syscon, priv->data->dfx_irq_cause_off, &dummy);

	/* Notअगरy the thermal core that the temperature is acceptable again */
	thermal_zone_device_update(priv->overheat_sensor,
				   THERMAL_EVENT_UNSPECIFIED);

enable_irq:
	enable_irq(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा armada_thermal_data armadaxp_data = अणु
	.init = armadaxp_init,
	.temp_shअगरt = 10,
	.temp_mask = 0x1ff,
	.coef_b = 3153000000ULL,
	.coef_m = 10000000ULL,
	.coef_भाग = 13825,
	.syscon_status_off = 0xb0,
	.syscon_control1_off = 0x2d0,
पूर्ण;

अटल स्थिर काष्ठा armada_thermal_data armada370_data = अणु
	.init = armada370_init,
	.is_valid_bit = BIT(9),
	.temp_shअगरt = 10,
	.temp_mask = 0x1ff,
	.coef_b = 3153000000ULL,
	.coef_m = 10000000ULL,
	.coef_भाग = 13825,
	.syscon_status_off = 0x0,
	.syscon_control1_off = 0x4,
पूर्ण;

अटल स्थिर काष्ठा armada_thermal_data armada375_data = अणु
	.init = armada375_init,
	.is_valid_bit = BIT(10),
	.temp_shअगरt = 0,
	.temp_mask = 0x1ff,
	.coef_b = 3171900000ULL,
	.coef_m = 10000000ULL,
	.coef_भाग = 13616,
	.syscon_status_off = 0x78,
	.syscon_control0_off = 0x7c,
	.syscon_control1_off = 0x80,
पूर्ण;

अटल स्थिर काष्ठा armada_thermal_data armada380_data = अणु
	.init = armada380_init,
	.is_valid_bit = BIT(10),
	.temp_shअगरt = 0,
	.temp_mask = 0x3ff,
	.coef_b = 1172499100ULL,
	.coef_m = 2000096ULL,
	.coef_भाग = 4201,
	.inverted = true,
	.syscon_control0_off = 0x70,
	.syscon_control1_off = 0x74,
	.syscon_status_off = 0x78,
पूर्ण;

अटल स्थिर काष्ठा armada_thermal_data armada_ap806_data = अणु
	.init = armada_ap806_init,
	.is_valid_bit = BIT(16),
	.temp_shअगरt = 0,
	.temp_mask = 0x3ff,
	.thresh_shअगरt = 3,
	.hyst_shअगरt = 19,
	.hyst_mask = 0x3,
	.coef_b = -150000LL,
	.coef_m = 423ULL,
	.coef_भाग = 1,
	.inverted = true,
	.चिन्हित_sample = true,
	.syscon_control0_off = 0x84,
	.syscon_control1_off = 0x88,
	.syscon_status_off = 0x8C,
	.dfx_irq_cause_off = 0x108,
	.dfx_irq_mask_off = 0x10C,
	.dfx_overheat_irq = BIT(22),
	.dfx_server_irq_mask_off = 0x104,
	.dfx_server_irq_en = BIT(1),
	.cpu_nr = 4,
पूर्ण;

अटल स्थिर काष्ठा armada_thermal_data armada_cp110_data = अणु
	.init = armada_cp110_init,
	.is_valid_bit = BIT(10),
	.temp_shअगरt = 0,
	.temp_mask = 0x3ff,
	.thresh_shअगरt = 16,
	.hyst_shअगरt = 26,
	.hyst_mask = 0x3,
	.coef_b = 1172499100ULL,
	.coef_m = 2000096ULL,
	.coef_भाग = 4201,
	.inverted = true,
	.syscon_control0_off = 0x70,
	.syscon_control1_off = 0x74,
	.syscon_status_off = 0x78,
	.dfx_irq_cause_off = 0x108,
	.dfx_irq_mask_off = 0x10C,
	.dfx_overheat_irq = BIT(20),
	.dfx_server_irq_mask_off = 0x104,
	.dfx_server_irq_en = BIT(1),
पूर्ण;

अटल स्थिर काष्ठा of_device_id armada_thermal_id_table[] = अणु
	अणु
		.compatible = "marvell,armadaxp-thermal",
		.data       = &armadaxp_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada370-thermal",
		.data       = &armada370_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada375-thermal",
		.data       = &armada375_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada380-thermal",
		.data       = &armada380_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-ap806-thermal",
		.data       = &armada_ap806_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-cp110-thermal",
		.data       = &armada_cp110_data,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, armada_thermal_id_table);

अटल स्थिर काष्ठा regmap_config armada_thermal_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक armada_thermal_probe_legacy(काष्ठा platक्रमm_device *pdev,
				       काष्ठा armada_thermal_priv *priv)
अणु
	काष्ठा armada_thermal_data *data = priv->data;
	काष्ठा resource *res;
	व्योम __iomem *base;

	/* First memory region poपूर्णांकs towards the status रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/*
	 * Fix up from the old inभागidual DT रेजिस्टर specअगरication to
	 * cover all the रेजिस्टरs.  We करो this by adjusting the ioremap()
	 * result, which should be fine as ioremap() deals with pages.
	 * However, validate that we करो not cross a page boundary जबतक
	 * making this adjusपंचांगent.
	 */
	अगर (((अचिन्हित दीर्घ)base & ~PAGE_MASK) < data->syscon_status_off)
		वापस -EINVAL;
	base -= data->syscon_status_off;

	priv->syscon = devm_regmap_init_mmio(&pdev->dev, base,
					     &armada_thermal_regmap_config);
	वापस PTR_ERR_OR_ZERO(priv->syscon);
पूर्ण

अटल पूर्णांक armada_thermal_probe_syscon(काष्ठा platक्रमm_device *pdev,
				       काष्ठा armada_thermal_priv *priv)
अणु
	priv->syscon = syscon_node_to_regmap(pdev->dev.parent->of_node);
	वापस PTR_ERR_OR_ZERO(priv->syscon);
पूर्ण

अटल व्योम armada_set_sane_name(काष्ठा platक्रमm_device *pdev,
				 काष्ठा armada_thermal_priv *priv)
अणु
	स्थिर अक्षर *name = dev_name(&pdev->dev);
	अक्षर *insane_अक्षर;

	अगर (म_माप(name) > THERMAL_NAME_LENGTH) अणु
		/*
		 * When inside a प्रणाली controller, the device name has the
		 * क्रमm: f06f8000.प्रणाली-controller:ap-thermal so stripping
		 * after the ':' should give us a लघुer but meaningful name.
		 */
		name = म_खोजप(name, ':');
		अगर (!name)
			name = "armada_thermal";
		अन्यथा
			name++;
	पूर्ण

	/* Save the name locally */
	म_नकलन(priv->zone_name, name, THERMAL_NAME_LENGTH - 1);
	priv->zone_name[THERMAL_NAME_LENGTH - 1] = '\0';

	/* Then check there are no '-' or hwmon core will complain */
	करो अणु
		insane_अक्षर = strpbrk(priv->zone_name, "-");
		अगर (insane_अक्षर)
			*insane_अक्षर = '_';
	पूर्ण जबतक (insane_अक्षर);
पूर्ण

/*
 * The IP can manage to trigger पूर्णांकerrupts on overheat situation from all the
 * sensors. However, the पूर्णांकerrupt source changes aदीर्घ with the last selected
 * source (ie. the last पढ़ो sensor), which is an inconsistent behavior. Aव्योम
 * possible glitches by always selecting back only one channel (arbitrarily: the
 * first in the DT which has a critical trip poपूर्णांक). We also disable sensor
 * चयन during overheat situations.
 */
अटल पूर्णांक armada_configure_overheat_पूर्णांक(काष्ठा armada_thermal_priv *priv,
					 काष्ठा thermal_zone_device *tz,
					 पूर्णांक sensor_id)
अणु
	/* Retrieve the critical trip poपूर्णांक to enable the overheat पूर्णांकerrupt */
	स्थिर काष्ठा thermal_trip *trips = of_thermal_get_trip_poपूर्णांकs(tz);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!trips)
		वापस -EINVAL;

	क्रम (i = 0; i < of_thermal_get_ntrips(tz); i++)
		अगर (trips[i].type == THERMAL_TRIP_CRITICAL)
			अवरोध;

	अगर (i == of_thermal_get_ntrips(tz))
		वापस -EINVAL;

	ret = armada_select_channel(priv, sensor_id);
	अगर (ret)
		वापस ret;

	armada_set_overheat_thresholds(priv,
				       trips[i].temperature,
				       trips[i].hysteresis);
	priv->overheat_sensor = tz;
	priv->पूर्णांकerrupt_source = sensor_id;

	armada_enable_overheat_पूर्णांकerrupt(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *tz;
	काष्ठा armada_thermal_sensor *sensor;
	काष्ठा armada_drvdata *drvdata;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा armada_thermal_priv *priv;
	पूर्णांक sensor_id, irq;
	पूर्णांक ret;

	match = of_match_device(armada_thermal_id_table, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(&pdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->data = (काष्ठा armada_thermal_data *)match->data;

	mutex_init(&priv->update_lock);

	/*
	 * Legacy DT bindings only described "control1" रेजिस्टर (also referred
	 * as "control MSB" on old करोcumentation). Then, bindings moved to cover
	 * "control0/control LSB" and "control1/control MSB" रेजिस्टरs within
	 * the same resource, which was then of size 8 instead of 4.
	 *
	 * The logic of defining sporadic रेजिस्टरs is broken. For instance, it
	 * blocked the addition of the overheat पूर्णांकerrupt feature that needed
	 * another resource somewhere अन्यथा in the same memory area. One solution
	 * is to define an overall प्रणाली controller and put the thermal node
	 * पूर्णांकo it, which requires the use of regmaps across all the driver.
	 */
	अगर (IS_ERR(syscon_node_to_regmap(pdev->dev.parent->of_node))) अणु
		/* Ensure device name is correct क्रम the thermal core */
		armada_set_sane_name(pdev, priv);

		ret = armada_thermal_probe_legacy(pdev, priv);
		अगर (ret)
			वापस ret;

		priv->data->init(pdev, priv);

		/* Wait the sensors to be valid */
		armada_रुको_sensor_validity(priv);

		tz = thermal_zone_device_रेजिस्टर(priv->zone_name, 0, 0, priv,
						  &legacy_ops, शून्य, 0, 0);
		अगर (IS_ERR(tz)) अणु
			dev_err(&pdev->dev,
				"Failed to register thermal zone device\n");
			वापस PTR_ERR(tz);
		पूर्ण

		ret = thermal_zone_device_enable(tz);
		अगर (ret) अणु
			thermal_zone_device_unरेजिस्टर(tz);
			वापस ret;
		पूर्ण

		drvdata->type = LEGACY;
		drvdata->data.tz = tz;
		platक्रमm_set_drvdata(pdev, drvdata);

		वापस 0;
	पूर्ण

	ret = armada_thermal_probe_syscon(pdev, priv);
	अगर (ret)
		वापस ret;

	priv->current_channel = -1;
	priv->data->init(pdev, priv);
	drvdata->type = SYSCON;
	drvdata->data.priv = priv;
	platक्रमm_set_drvdata(pdev, drvdata);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq == -EPROBE_DEFER)
		वापस irq;

	/* The overheat पूर्णांकerrupt feature is not mandatory */
	अगर (irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
						armada_overheat_isr,
						armada_overheat_isr_thपढ़ो,
						0, शून्य, priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Cannot request threaded IRQ %d\n",
				irq);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * There is one channel क्रम the IC and one per CPU (अगर any), each
	 * channel has one sensor.
	 */
	क्रम (sensor_id = 0; sensor_id <= priv->data->cpu_nr; sensor_id++) अणु
		sensor = devm_kzalloc(&pdev->dev,
				      माप(काष्ठा armada_thermal_sensor),
				      GFP_KERNEL);
		अगर (!sensor)
			वापस -ENOMEM;

		/* Register the sensor */
		sensor->priv = priv;
		sensor->id = sensor_id;
		tz = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
							  sensor->id, sensor,
							  &of_ops);
		अगर (IS_ERR(tz)) अणु
			dev_info(&pdev->dev, "Thermal sensor %d unavailable\n",
				 sensor_id);
			devm_kमुक्त(&pdev->dev, sensor);
			जारी;
		पूर्ण

		/*
		 * The first channel that has a critical trip poपूर्णांक रेजिस्टरed
		 * in the DT will serve as पूर्णांकerrupt source. Others possible
		 * critical trip poपूर्णांकs will simply be ignored by the driver.
		 */
		अगर (irq > 0 && !priv->overheat_sensor)
			armada_configure_overheat_पूर्णांक(priv, tz, sensor->id);
	पूर्ण

	/* Just complain अगर no overheat पूर्णांकerrupt was set up */
	अगर (!priv->overheat_sensor)
		dev_warn(&pdev->dev, "Overheat interrupt not available\n");

	वापस 0;
पूर्ण

अटल पूर्णांक armada_thermal_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा armada_drvdata *drvdata = platक्रमm_get_drvdata(pdev);

	अगर (drvdata->type == LEGACY)
		thermal_zone_device_unरेजिस्टर(drvdata->data.tz);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver armada_thermal_driver = अणु
	.probe = armada_thermal_probe,
	.हटाओ = armada_thermal_निकास,
	.driver = अणु
		.name = "armada_thermal",
		.of_match_table = armada_thermal_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(armada_thermal_driver);

MODULE_AUTHOR("Ezequiel Garcia <ezequiel.garcia@free-electrons.com>");
MODULE_DESCRIPTION("Marvell EBU Armada SoCs thermal driver");
MODULE_LICENSE("GPL v2");
