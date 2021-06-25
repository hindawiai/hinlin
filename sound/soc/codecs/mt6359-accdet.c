<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6359-accdet.c  --  ALSA SoC mt6359 accdet driver
//
// Copyright (C) 2021 MediaTek Inc.
// Author: Argus Lin <argus.lin@mediatek.com>
//

#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/input.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <linux/mfd/mt6397/core.h>

#समावेश "mt6359-accdet.h"
#समावेश "mt6359.h"

/* global variable definitions */
#घोषणा REGISTER_VAL(x)	((x) - 1)

/* mt6359 accdet capability */
#घोषणा ACCDET_PMIC_EINT_IRQ		BIT(0)
#घोषणा ACCDET_AP_GPIO_EINT		BIT(1)

#घोषणा ACCDET_PMIC_EINT0		BIT(2)
#घोषणा ACCDET_PMIC_EINT1		BIT(3)
#घोषणा ACCDET_PMIC_BI_EINT		BIT(4)

#घोषणा ACCDET_PMIC_GPIO_TRIG_EINT	BIT(5)
#घोषणा ACCDET_PMIC_INVERTER_TRIG_EINT	BIT(6)
#घोषणा ACCDET_PMIC_RSV_EINT		BIT(7)

#घोषणा ACCDET_THREE_KEY		BIT(8)
#घोषणा ACCDET_FOUR_KEY			BIT(9)
#घोषणा ACCDET_TRI_KEY_CDD		BIT(10)
#घोषणा ACCDET_RSV_KEY			BIT(11)

#घोषणा ACCDET_ANALOG_FASTDISCHARGE	BIT(12)
#घोषणा ACCDET_DIGITAL_FASTDISCHARGE	BIT(13)
#घोषणा ACCDET_AD_FASTDISCHRAGE		BIT(14)

अटल काष्ठा platक्रमm_driver mt6359_accdet_driver;
अटल स्थिर काष्ठा snd_soc_component_driver mt6359_accdet_soc_driver;

/* local function declaration */
अटल व्योम accdet_set_debounce(काष्ठा mt6359_accdet *priv, पूर्णांक state,
				अचिन्हित पूर्णांक debounce);
अटल अचिन्हित पूर्णांक adjust_eपूर्णांक_analog_setting(काष्ठा mt6359_accdet *priv);
अटल व्योम config_digital_init_by_mode(काष्ठा mt6359_accdet *priv);
अटल व्योम config_eपूर्णांक_init_by_mode(काष्ठा mt6359_accdet *priv);
अटल अंतरभूत व्योम mt6359_accdet_init(काष्ठा mt6359_accdet *priv);
अटल अचिन्हित पूर्णांक mt6359_accdet_jd_setting(काष्ठा mt6359_accdet *priv);
अटल व्योम mt6359_accdet_recover_jd_setting(काष्ठा mt6359_accdet *priv);
अटल व्योम mt6359_accdet_jack_report(काष्ठा mt6359_accdet *priv);
अटल व्योम recover_eपूर्णांक_analog_setting(काष्ठा mt6359_accdet *priv);
अटल व्योम recover_eपूर्णांक_digital_setting(काष्ठा mt6359_accdet *priv);
अटल व्योम recover_eपूर्णांक_setting(काष्ठा mt6359_accdet *priv);

अटल अचिन्हित पूर्णांक adjust_eपूर्णांक_analog_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->data->eपूर्णांक_detect_mode == 0x3 ||
	    priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		/* ESD चयनes off */
		regmap_update_bits(priv->regmap,
				   RG_ACCDETSPARE_ADDR, 1 << 8, 0);
	पूर्ण
	अगर (priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			/* enable RG_EINT0CONFIGACCDET */
			regmap_update_bits(priv->regmap,
					   RG_EINT0CONFIGACCDET_ADDR,
					   RG_EINT0CONFIGACCDET_MASK_SFT,
					   BIT(RG_EINT0CONFIGACCDET_SFT));
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			/* enable RG_EINT1CONFIGACCDET */
			regmap_update_bits(priv->regmap,
					   RG_EINT1CONFIGACCDET_ADDR,
					   RG_EINT1CONFIGACCDET_MASK_SFT,
					   BIT(RG_EINT1CONFIGACCDET_SFT));
		पूर्ण
		अगर (priv->data->eपूर्णांक_use_ext_res == 0x3 ||
		    priv->data->eपूर्णांक_use_ext_res == 0x4) अणु
			/*select 500k, use पूर्णांकernal resistor */
			regmap_update_bits(priv->regmap,
					   RG_EINT0HIRENB_ADDR,
					   RG_EINT0HIRENB_MASK_SFT,
					   BIT(RG_EINT0HIRENB_SFT));
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक adjust_eपूर्णांक_digital_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
		/* disable inverter */
		regmap_update_bits(priv->regmap,
				   ACCDET_EINT0_INVERTER_SW_EN_ADDR,
				   ACCDET_EINT0_INVERTER_SW_EN_MASK_SFT, 0);
	पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
		/* disable inverter */
		regmap_update_bits(priv->regmap,
				   ACCDET_EINT1_INVERTER_SW_EN_ADDR,
				   ACCDET_EINT1_INVERTER_SW_EN_MASK_SFT, 0);
	पूर्ण

	अगर (priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			/* set DA stable संकेत */
			regmap_update_bits(priv->regmap,
					   ACCDET_DA_STABLE_ADDR,
					   ACCDET_EINT0_CEN_STABLE_MASK_SFT, 0);
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			/* set DA stable संकेत */
			regmap_update_bits(priv->regmap,
					   ACCDET_DA_STABLE_ADDR,
					   ACCDET_EINT1_CEN_STABLE_MASK_SFT, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mt6359_accdet_jd_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->jd_sts == M_PLUG_IN) अणु
		/* adjust digital setting */
		adjust_eपूर्णांक_digital_setting(priv);
		/* adjust analog setting */
		adjust_eपूर्णांक_analog_setting(priv);
	पूर्ण अन्यथा अगर (priv->jd_sts == M_PLUG_OUT) अणु
		/* set debounce to 1ms */
		accdet_set_debounce(priv, eपूर्णांक_state000,
				    priv->data->pwm_deb->eपूर्णांक_debounce0);
	पूर्ण अन्यथा अणु
		dev_dbg(priv->dev, "should not be here %s()\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम recover_eपूर्णांक_analog_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->data->eपूर्णांक_detect_mode == 0x3 ||
	    priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		/* ESD चयनes on */
		regmap_update_bits(priv->regmap, RG_ACCDETSPARE_ADDR,
				   1 << 8, 1 << 8);
	पूर्ण
	अगर (priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			/* disable RG_EINT0CONFIGACCDET */
			regmap_update_bits(priv->regmap,
					   RG_EINT0CONFIGACCDET_ADDR,
					   RG_EINT0CONFIGACCDET_MASK_SFT, 0);
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			/* disable RG_EINT1CONFIGACCDET */
			regmap_update_bits(priv->regmap,
					   RG_EINT1CONFIGACCDET_ADDR,
					   RG_EINT1CONFIGACCDET_MASK_SFT, 0);
		पूर्ण
		regmap_update_bits(priv->regmap, RG_EINT0HIRENB_ADDR,
				   RG_EINT0HIRENB_MASK_SFT, 0);
	पूर्ण
पूर्ण

अटल व्योम recover_eपूर्णांक_digital_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
		regmap_update_bits(priv->regmap,
				   ACCDET_EINT0_M_SW_EN_ADDR,
				   ACCDET_EINT0_M_SW_EN_MASK_SFT, 0);
	पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
		regmap_update_bits(priv->regmap,
				   ACCDET_EINT1_M_SW_EN_ADDR,
				   ACCDET_EINT1_M_SW_EN_MASK_SFT, 0);
	पूर्ण
	अगर (priv->data->eपूर्णांक_detect_mode == 0x4) अणु
		/* enable eपूर्णांक0cen */
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			/* enable eपूर्णांक0cen */
			regmap_update_bits(priv->regmap,
					   ACCDET_DA_STABLE_ADDR,
					   ACCDET_EINT0_CEN_STABLE_MASK_SFT,
					   BIT(ACCDET_EINT0_CEN_STABLE_SFT));
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			/* enable eपूर्णांक1cen */
			regmap_update_bits(priv->regmap,
					   ACCDET_DA_STABLE_ADDR,
					   ACCDET_EINT1_CEN_STABLE_MASK_SFT,
					   BIT(ACCDET_EINT1_CEN_STABLE_SFT));
		पूर्ण
	पूर्ण

	अगर (priv->data->eपूर्णांक_detect_mode != 0x1) अणु
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			/* enable inverter */
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT0_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT0_INVERTER_SW_EN_MASK_SFT,
					   BIT(ACCDET_EINT0_INVERTER_SW_EN_SFT));
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			/* enable inverter */
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT1_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT1_INVERTER_SW_EN_MASK_SFT,
					   BIT(ACCDET_EINT1_INVERTER_SW_EN_SFT));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम recover_eपूर्णांक_setting(काष्ठा mt6359_accdet *priv)
अणु
	अगर (priv->jd_sts == M_PLUG_OUT) अणु
		recover_eपूर्णांक_analog_setting(priv);
		recover_eपूर्णांक_digital_setting(priv);
	पूर्ण
पूर्ण

अटल व्योम mt6359_accdet_recover_jd_setting(काष्ठा mt6359_accdet *priv)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक value = 0;

	regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
			   ACCDET_IRQ_CLR_MASK_SFT, BIT(ACCDET_IRQ_CLR_SFT));
	usleep_range(200, 300);
	ret = regmap_पढ़ो_poll_समयout(priv->regmap,
				       ACCDET_IRQ_ADDR,
				       value,
				       (value & ACCDET_IRQ_MASK_SFT) == 0,
				       0,
				       1000);
	अगर (ret)
		dev_warn(priv->dev, "%s(), ret %d\n", __func__, ret);
	/* clear accdet पूर्णांक, modअगरy  क्रम fix पूर्णांकerrupt trigger twice error */
	regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
			   ACCDET_IRQ_CLR_MASK_SFT, 0);
	regmap_update_bits(priv->regmap, RG_INT_STATUS_ACCDET_ADDR,
			   RG_INT_STATUS_ACCDET_MASK_SFT,
			   BIT(RG_INT_STATUS_ACCDET_SFT));

	/* recover accdet debounce0,3 */
	accdet_set_debounce(priv, accdet_state000,
			    priv->data->pwm_deb->debounce0);
	accdet_set_debounce(priv, accdet_state001,
			    priv->data->pwm_deb->debounce1);
	accdet_set_debounce(priv, accdet_state011,
			    priv->data->pwm_deb->debounce3);

	priv->jack_type = 0;
	priv->btn_type = 0;
	priv->accdet_status = 0x3;
	mt6359_accdet_jack_report(priv);
पूर्ण

अटल व्योम accdet_set_debounce(काष्ठा mt6359_accdet *priv, पूर्णांक state,
				अचिन्हित पूर्णांक debounce)
अणु
	चयन (state) अणु
	हाल accdet_state000:
		regmap_ग_लिखो(priv->regmap, ACCDET_DEBOUNCE0_ADDR, debounce);
		अवरोध;
	हाल accdet_state001:
		regmap_ग_लिखो(priv->regmap, ACCDET_DEBOUNCE1_ADDR, debounce);
		अवरोध;
	हाल accdet_state010:
		regmap_ग_लिखो(priv->regmap, ACCDET_DEBOUNCE2_ADDR, debounce);
		अवरोध;
	हाल accdet_state011:
		regmap_ग_लिखो(priv->regmap, ACCDET_DEBOUNCE3_ADDR, debounce);
		अवरोध;
	हाल accdet_auxadc:
		regmap_ग_लिखो(priv->regmap,
			     ACCDET_CONNECT_AUXADC_TIME_DIG_ADDR, debounce);
		अवरोध;
	हाल eपूर्णांक_state000:
		regmap_update_bits(priv->regmap, ACCDET_EINT_DEBOUNCE0_ADDR,
				   0xF << ACCDET_EINT_DEBOUNCE0_SFT,
				   debounce << ACCDET_EINT_DEBOUNCE0_SFT);
		अवरोध;
	हाल eपूर्णांक_state001:
		regmap_update_bits(priv->regmap, ACCDET_EINT_DEBOUNCE1_ADDR,
				   0xF << ACCDET_EINT_DEBOUNCE1_SFT,
				   debounce << ACCDET_EINT_DEBOUNCE1_SFT);
		अवरोध;
	हाल eपूर्णांक_state010:
		regmap_update_bits(priv->regmap, ACCDET_EINT_DEBOUNCE2_ADDR,
				   0xF << ACCDET_EINT_DEBOUNCE2_SFT,
				   debounce << ACCDET_EINT_DEBOUNCE2_SFT);
		अवरोध;
	हाल eपूर्णांक_state011:
		regmap_update_bits(priv->regmap, ACCDET_EINT_DEBOUNCE3_ADDR,
				   0xF << ACCDET_EINT_DEBOUNCE3_SFT,
				   debounce << ACCDET_EINT_DEBOUNCE3_SFT);
		अवरोध;
	हाल eपूर्णांक_inverter_state000:
		regmap_ग_लिखो(priv->regmap, ACCDET_EINT_INVERTER_DEBOUNCE_ADDR,
			     debounce);
		अवरोध;
	शेष:
		dev_warn(priv->dev, "Error: %s error state (%d)\n", __func__,
			 state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt6359_accdet_jack_report(काष्ठा mt6359_accdet *priv)
अणु
	पूर्णांक report = 0;

	अगर (!priv->jack)
		वापस;

	report = priv->jack_type | priv->btn_type;
	snd_soc_jack_report(priv->jack, report, MT6359_ACCDET_JACK_MASK);
पूर्ण

अटल अचिन्हित पूर्णांक check_button(काष्ठा mt6359_accdet *priv, अचिन्हित पूर्णांक v)
अणु
	अगर (priv->caps & ACCDET_FOUR_KEY) अणु
		अगर (v < priv->data->four_key.करोwn &&
		    v >= priv->data->four_key.up)
			priv->btn_type = SND_JACK_BTN_1;
		अगर (v < priv->data->four_key.up &&
		    v >= priv->data->four_key.voice)
			priv->btn_type = SND_JACK_BTN_2;
		अगर (v < priv->data->four_key.voice &&
		    v >= priv->data->four_key.mid)
			priv->btn_type = SND_JACK_BTN_3;
		अगर (v < priv->data->four_key.mid)
			priv->btn_type = SND_JACK_BTN_0;
	पूर्ण अन्यथा अणु
		अगर (v < priv->data->three_key.करोwn &&
		    v >= priv->data->three_key.up)
			priv->btn_type = SND_JACK_BTN_1;
		अगर (v < priv->data->three_key.up &&
		    v >= priv->data->three_key.mid)
			priv->btn_type = SND_JACK_BTN_2;
		अगर (v < priv->data->three_key.mid)
			priv->btn_type = SND_JACK_BTN_0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम is_key_pressed(काष्ठा mt6359_accdet *priv, bool pressed)
अणु
	priv->btn_type = priv->jack_type & ~MT6359_ACCDET_BTN_MASK;

	अगर (pressed)
		check_button(priv, priv->cali_voltage);
पूर्ण

अटल अंतरभूत व्योम check_jack_btn_type(काष्ठा mt6359_accdet *priv)
अणु
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(priv->regmap, ACCDET_MEM_IN_ADDR, &val);

	priv->accdet_status =
		(val >> ACCDET_STATE_MEM_IN_OFFSET) & ACCDET_STATE_AB_MASK;

	चयन (priv->accdet_status) अणु
	हाल 0:
		अगर (priv->jack_type == SND_JACK_HEADSET)
			is_key_pressed(priv, true);
		अन्यथा
			priv->jack_type = SND_JACK_HEADPHONE;
		अवरोध;
	हाल 1:
		अगर (priv->jack_type == SND_JACK_HEADSET) अणु
			is_key_pressed(priv, false);
		पूर्ण अन्यथा अणु
			priv->jack_type = SND_JACK_HEADSET;
			accdet_set_debounce(priv, eपूर्णांक_state011, 0x1);
		पूर्ण
		अवरोध;
	हाल 3:
	शेष:
		priv->jack_type = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt6359_accdet_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt6359_accdet *priv =
		container_of(work, काष्ठा mt6359_accdet, accdet_work);

	mutex_lock(&priv->res_lock);
	priv->pre_accdet_status = priv->accdet_status;
	check_jack_btn_type(priv);

	अगर (priv->jack_plugged &&
	    priv->pre_accdet_status != priv->accdet_status)
		mt6359_accdet_jack_report(priv);
	mutex_unlock(&priv->res_lock);
पूर्ण

अटल व्योम mt6359_accdet_jd_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक value = 0;

	काष्ठा mt6359_accdet *priv =
		container_of(work, काष्ठा mt6359_accdet, jd_work);

	mutex_lock(&priv->res_lock);
	अगर (priv->jd_sts == M_PLUG_IN) अणु
		priv->jack_plugged = true;

		/* set and clear initial bit every eपूर्णांक पूर्णांकerrupt */
		regmap_update_bits(priv->regmap, ACCDET_SEQ_INIT_ADDR,
				   ACCDET_SEQ_INIT_MASK_SFT,
				   BIT(ACCDET_SEQ_INIT_SFT));
		regmap_update_bits(priv->regmap, ACCDET_SEQ_INIT_ADDR,
				   ACCDET_SEQ_INIT_MASK_SFT, 0);
		ret = regmap_पढ़ो_poll_समयout(priv->regmap,
					       ACCDET_SEQ_INIT_ADDR,
					       value,
					       (value & ACCDET_SEQ_INIT_MASK_SFT) == 0,
					       0,
					       1000);
		अगर (ret)
			dev_err(priv->dev, "%s(), ret %d\n", __func__, ret);

		/* enable ACCDET unit */
		regmap_update_bits(priv->regmap, ACCDET_SW_EN_ADDR,
				   ACCDET_SW_EN_MASK_SFT, BIT(ACCDET_SW_EN_SFT));
	पूर्ण अन्यथा अगर (priv->jd_sts == M_PLUG_OUT) अणु
		priv->jack_plugged = false;

		accdet_set_debounce(priv, accdet_state011,
				    priv->data->pwm_deb->debounce3);
		regmap_update_bits(priv->regmap, ACCDET_SW_EN_ADDR,
				   ACCDET_SW_EN_MASK_SFT, 0);
		mt6359_accdet_recover_jd_setting(priv);
	पूर्ण

	अगर (priv->caps & ACCDET_PMIC_EINT_IRQ)
		recover_eपूर्णांक_setting(priv);
	mutex_unlock(&priv->res_lock);
पूर्ण

अटल irqवापस_t mt6359_accdet_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mt6359_accdet *priv = data;
	अचिन्हित पूर्णांक irq_val = 0, val = 0, value = 0;
	पूर्णांक ret = 0;

	mutex_lock(&priv->res_lock);
	regmap_पढ़ो(priv->regmap, ACCDET_IRQ_ADDR, &irq_val);

	अगर (irq_val & ACCDET_IRQ_MASK_SFT) अणु
		regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
				   ACCDET_IRQ_CLR_MASK_SFT,
				   BIT(ACCDET_IRQ_CLR_SFT));
		ret = regmap_पढ़ो_poll_समयout(priv->regmap,
					       ACCDET_IRQ_ADDR,
					       value,
					       (value & ACCDET_IRQ_MASK_SFT) == 0,
					       0,
					       1000);
		अगर (ret) अणु
			dev_err(priv->dev, "%s(), ret %d\n", __func__, ret);
			mutex_unlock(&priv->res_lock);
			वापस IRQ_NONE;
		पूर्ण
		regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
				   ACCDET_IRQ_CLR_MASK_SFT, 0);
		regmap_update_bits(priv->regmap, RG_INT_STATUS_ACCDET_ADDR,
				   RG_INT_STATUS_ACCDET_MASK_SFT,
				   BIT(RG_INT_STATUS_ACCDET_SFT));

		queue_work(priv->accdet_workqueue, &priv->accdet_work);
	पूर्ण अन्यथा अणु
		अगर (irq_val & ACCDET_EINT0_IRQ_MASK_SFT) अणु
			regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
					   ACCDET_EINT0_IRQ_CLR_MASK_SFT,
					   BIT(ACCDET_EINT0_IRQ_CLR_SFT));
			ret = regmap_पढ़ो_poll_समयout(priv->regmap,
						       ACCDET_IRQ_ADDR,
						       value,
						       (value & ACCDET_EINT0_IRQ_MASK_SFT) == 0,
						       0,
						       1000);
			अगर (ret) अणु
				dev_err(priv->dev, "%s(), ret %d\n", __func__,
					ret);
				mutex_unlock(&priv->res_lock);
				वापस IRQ_NONE;
			पूर्ण
			regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
					   ACCDET_EINT0_IRQ_CLR_MASK_SFT, 0);
			regmap_update_bits(priv->regmap,
					   RG_INT_STATUS_ACCDET_ADDR,
					   RG_INT_STATUS_ACCDET_EINT0_MASK_SFT,
					   BIT(RG_INT_STATUS_ACCDET_EINT0_SFT));
		पूर्ण
		अगर (irq_val & ACCDET_EINT1_IRQ_MASK_SFT) अणु
			regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
					   ACCDET_EINT1_IRQ_CLR_MASK_SFT,
					   BIT(ACCDET_EINT1_IRQ_CLR_SFT));
			ret = regmap_पढ़ो_poll_समयout(priv->regmap,
						       ACCDET_IRQ_ADDR,
						       value,
						       (value & ACCDET_EINT1_IRQ_MASK_SFT) == 0,
						       0,
						       1000);
			अगर (ret) अणु
				dev_err(priv->dev, "%s(), ret %d\n", __func__,
					ret);
				mutex_unlock(&priv->res_lock);
				वापस IRQ_NONE;
			पूर्ण
			regmap_update_bits(priv->regmap, ACCDET_IRQ_ADDR,
					   ACCDET_EINT1_IRQ_CLR_MASK_SFT, 0);
			regmap_update_bits(priv->regmap,
					   RG_INT_STATUS_ACCDET_ADDR,
					   RG_INT_STATUS_ACCDET_EINT1_MASK_SFT,
					   BIT(RG_INT_STATUS_ACCDET_EINT1_SFT));
		पूर्ण
		/* get jack detection status */
		regmap_पढ़ो(priv->regmap, ACCDET_EINT0_MEM_IN_ADDR, &val);
		priv->jd_sts = ((val >> ACCDET_EINT0_MEM_IN_SFT) &
				   ACCDET_EINT0_MEM_IN_MASK);
		/* adjust eपूर्णांक digital/analog setting */
		mt6359_accdet_jd_setting(priv);

		queue_work(priv->jd_workqueue, &priv->jd_work);
	पूर्ण
	mutex_unlock(&priv->res_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mt6359_accdet_parse_dt(काष्ठा mt6359_accdet *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = priv->dev;
	काष्ठा device_node *node = शून्य;
	पूर्णांक pwm_deb[15] = अणु0पूर्ण;
	अचिन्हित पूर्णांक पंचांगp = 0;

	node = of_get_child_by_name(dev->parent->of_node, "accdet");
	अगर (!node)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32(node, "mediatek,mic-vol",
				   &priv->data->mic_vol);
	अगर (ret)
		priv->data->mic_vol = 8;

	ret = of_property_पढ़ो_u32(node, "mediatek,plugout-debounce",
				   &priv->data->plugout_deb);
	अगर (ret)
		priv->data->plugout_deb = 1;

	ret = of_property_पढ़ो_u32(node, "mediatek,mic-mode",
				   &priv->data->mic_mode);
	अगर (ret)
		priv->data->mic_mode = 2;

	ret = of_property_पढ़ो_u32_array(node, "mediatek,pwm-deb-setting",
					 pwm_deb, ARRAY_SIZE(pwm_deb));
	/* debounce8(auxadc debounce) is शेष, needn't get from dts */
	अगर (!ret)
		स_नकल(priv->data->pwm_deb, pwm_deb, माप(pwm_deb));

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-level-pol",
				   &priv->data->eपूर्णांक_pol);
	अगर (ret)
		priv->data->eपूर्णांक_pol = 8;

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-use-ap", &पंचांगp);
	अगर (ret)
		पंचांगp = 0;
	अगर (पंचांगp == 0)
		priv->caps |= ACCDET_PMIC_EINT_IRQ;
	अन्यथा अगर (पंचांगp == 1)
		priv->caps |= ACCDET_AP_GPIO_EINT;

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-detect-mode",
				   &priv->data->eपूर्णांक_detect_mode);
	अगर (ret) अणु
		/* eपूर्णांक detection mode equals to EINT HW Mode */
		priv->data->eपूर्णांक_detect_mode = 0x4;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-num", &पंचांगp);
	अगर (ret)
		पंचांगp = 0;
	अगर (पंचांगp == 0)
		priv->caps |= ACCDET_PMIC_EINT0;
	अन्यथा अगर (पंचांगp == 1)
		priv->caps |= ACCDET_PMIC_EINT1;
	अन्यथा अगर (पंचांगp == 2)
		priv->caps |= ACCDET_PMIC_BI_EINT;

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-trig-mode",
				   &पंचांगp);
	अगर (ret)
		पंचांगp = 0;
	अगर (पंचांगp == 0)
		priv->caps |= ACCDET_PMIC_GPIO_TRIG_EINT;
	अन्यथा अगर (पंचांगp == 1)
		priv->caps |= ACCDET_PMIC_INVERTER_TRIG_EINT;

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-use-ext-res",
				   &priv->data->eपूर्णांक_use_ext_res);
	अगर (ret) अणु
		/* eपूर्णांक use पूर्णांकernal resister */
		priv->data->eपूर्णांक_use_ext_res = 0x0;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "mediatek,eint-comp-vth",
				   &priv->data->eपूर्णांक_comp_vth);
	अगर (ret)
		priv->data->eपूर्णांक_comp_vth = 0x0;

	ret = of_property_पढ़ो_u32(node, "mediatek,key-mode", &पंचांगp);
	अगर (ret)
		पंचांगp = 0;
	अगर (पंचांगp == 0) अणु
		पूर्णांक three_key[4];

		priv->caps |= ACCDET_THREE_KEY;
		ret = of_property_पढ़ो_u32_array(node,
						 "mediatek,three-key-thr",
						 three_key,
						 ARRAY_SIZE(three_key));
		अगर (!ret)
			स_नकल(&priv->data->three_key, three_key + 1,
			       माप(काष्ठा three_key_threshold));
	पूर्ण अन्यथा अगर (पंचांगp == 1) अणु
		पूर्णांक four_key[5];

		priv->caps |= ACCDET_FOUR_KEY;
		ret = of_property_पढ़ो_u32_array(node,
						 "mediatek,four-key-thr",
						 four_key,
						 ARRAY_SIZE(four_key));
		अगर (!ret) अणु
			स_नकल(&priv->data->four_key, four_key + 1,
			       माप(काष्ठा four_key_threshold));
		पूर्ण अन्यथा अणु
			dev_warn(priv->dev,
				 "accdet no 4-key-thrsh dts, use efuse\n");
		पूर्ण
	पूर्ण अन्यथा अगर (पंचांगp == 2) अणु
		पूर्णांक three_key[4];

		priv->caps |= ACCDET_TRI_KEY_CDD;
		ret = of_property_पढ़ो_u32_array(node,
						 "mediatek,tri-key-cdd-thr",
						 three_key,
						 ARRAY_SIZE(three_key));
		अगर (!ret)
			स_नकल(&priv->data->three_key, three_key + 1,
			       माप(काष्ठा three_key_threshold));
	पूर्ण

	dev_warn(priv->dev, "accdet caps=%x\n", priv->caps);

	वापस 0;
पूर्ण

अटल व्योम config_digital_init_by_mode(काष्ठा mt6359_accdet *priv)
अणु
	/* enable eपूर्णांक cmpmem pwm */
	regmap_ग_लिखो(priv->regmap, ACCDET_EINT_CMPMEN_PWM_THRESH_ADDR,
		     (priv->data->pwm_deb->eपूर्णांक_pwm_width << 4 |
		     priv->data->pwm_deb->eपूर्णांक_pwm_thresh));
	/* DA संकेत stable */
	अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
		regmap_ग_लिखो(priv->regmap, ACCDET_DA_STABLE_ADDR,
			     ACCDET_EINT0_STABLE_VAL);
	पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
		regmap_ग_लिखो(priv->regmap, ACCDET_DA_STABLE_ADDR,
			     ACCDET_EINT1_STABLE_VAL);
	पूर्ण
	/* after receive n+1 number, पूर्णांकerrupt issued. */
	regmap_update_bits(priv->regmap, ACCDET_EINT_M_PLUG_IN_NUM_ADDR,
			   ACCDET_EINT_M_PLUG_IN_NUM_MASK_SFT,
			   BIT(ACCDET_EINT_M_PLUG_IN_NUM_SFT));
	/* setting HW mode, enable digital fast disअक्षरge
	 * अगर use EINT0 & EINT1 detection, please modअगरy
	 * ACCDET_HWMODE_EN_ADDR[2:1]
	 */
	regmap_ग_लिखो(priv->regmap, ACCDET_HWMODE_EN_ADDR, 0x100);

	regmap_update_bits(priv->regmap, ACCDET_EINT_M_DETECT_EN_ADDR,
			   ACCDET_EINT_M_DETECT_EN_MASK_SFT, 0);

	/* enable PWM */
	regmap_ग_लिखो(priv->regmap, ACCDET_CMP_PWM_EN_ADDR, 0x67);
	/* enable inverter detection */
	अगर (priv->data->eपूर्णांक_detect_mode == 0x1) अणु
		/* disable inverter detection */
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT0_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT0_INVERTER_SW_EN_MASK_SFT,
					   0);
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT1_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT1_INVERTER_SW_EN_MASK_SFT,
					   0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT0_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT0_INVERTER_SW_EN_MASK_SFT,
					   BIT(ACCDET_EINT0_INVERTER_SW_EN_SFT));
		पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
			regmap_update_bits(priv->regmap,
					   ACCDET_EINT1_INVERTER_SW_EN_ADDR,
					   ACCDET_EINT1_INVERTER_SW_EN_MASK_SFT,
					   BIT(ACCDET_EINT1_INVERTER_SW_EN_SFT));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम config_eपूर्णांक_init_by_mode(काष्ठा mt6359_accdet *priv)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
		regmap_update_bits(priv->regmap, RG_EINT0EN_ADDR,
				   RG_EINT0EN_MASK_SFT, BIT(RG_EINT0EN_SFT));
	पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
		regmap_update_bits(priv->regmap, RG_EINT1EN_ADDR,
				   RG_EINT1EN_MASK_SFT, BIT(RG_EINT1EN_SFT));
	पूर्ण
	/* ESD चयनes on */
	regmap_update_bits(priv->regmap, RG_ACCDETSPARE_ADDR,
			   1 << 8, 1 << 8);
	/* beक्रमe playback, set NCP pull low beक्रमe nagative voltage */
	regmap_update_bits(priv->regmap, RG_NCP_PDDIS_EN_ADDR,
			   RG_NCP_PDDIS_EN_MASK_SFT, BIT(RG_NCP_PDDIS_EN_SFT));

	अगर (priv->data->eपूर्णांक_detect_mode == 0x1 ||
	    priv->data->eपूर्णांक_detect_mode == 0x2 ||
	    priv->data->eपूर्णांक_detect_mode == 0x3) अणु
		अगर (priv->data->eपूर्णांक_use_ext_res == 0x1) अणु
			अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
				regmap_update_bits(priv->regmap,
						   RG_EINT0CONFIGACCDET_ADDR,
						   RG_EINT0CONFIGACCDET_MASK_SFT,
						   0);
			पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
				regmap_update_bits(priv->regmap,
						   RG_EINT1CONFIGACCDET_ADDR,
						   RG_EINT1CONFIGACCDET_MASK_SFT,
						   0);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
				regmap_update_bits(priv->regmap,
						   RG_EINT0CONFIGACCDET_ADDR,
						   RG_EINT0CONFIGACCDET_MASK_SFT,
						   BIT(RG_EINT0CONFIGACCDET_SFT));
			पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
				regmap_update_bits(priv->regmap,
						   RG_EINT1CONFIGACCDET_ADDR,
						   RG_EINT1CONFIGACCDET_MASK_SFT,
						   BIT(RG_EINT1CONFIGACCDET_SFT));
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->data->eपूर्णांक_detect_mode != 0x1) अणु
		/* current detect set 0.25uA */
		regmap_update_bits(priv->regmap, RG_ACCDETSPARE_ADDR,
				   0x3 << RG_ACCDETSPARE_SFT,
				   0x3 << RG_ACCDETSPARE_SFT);
	पूर्ण
	regmap_ग_लिखो(priv->regmap, RG_EINTCOMPVTH_ADDR,
		     val | priv->data->eपूर्णांक_comp_vth << RG_EINTCOMPVTH_SFT);
पूर्ण

अटल व्योम mt6359_accdet_init(काष्ठा mt6359_accdet *priv)
अणु
	अचिन्हित पूर्णांक reg = 0;

	regmap_update_bits(priv->regmap, ACCDET_SEQ_INIT_ADDR,
			   ACCDET_SEQ_INIT_MASK_SFT, BIT(ACCDET_SEQ_INIT_SFT));
	mdelay(2);
	regmap_update_bits(priv->regmap, ACCDET_SEQ_INIT_ADDR,
			   ACCDET_SEQ_INIT_MASK_SFT, 0);
	mdelay(1);
	/* init the debounce समय (debounce/32768)sec */
	accdet_set_debounce(priv, accdet_state000,
			    priv->data->pwm_deb->debounce0);
	accdet_set_debounce(priv, accdet_state001,
			    priv->data->pwm_deb->debounce1);
	accdet_set_debounce(priv, accdet_state011,
			    priv->data->pwm_deb->debounce3);
	accdet_set_debounce(priv, accdet_auxadc,
			    priv->data->pwm_deb->debounce4);

	accdet_set_debounce(priv, eपूर्णांक_state000,
			    priv->data->pwm_deb->eपूर्णांक_debounce0);
	accdet_set_debounce(priv, eपूर्णांक_state001,
			    priv->data->pwm_deb->eपूर्णांक_debounce1);
	accdet_set_debounce(priv, eपूर्णांक_state011,
			    priv->data->pwm_deb->eपूर्णांक_debounce3);
	accdet_set_debounce(priv, eपूर्णांक_inverter_state000,
			    priv->data->pwm_deb->eपूर्णांक_inverter_debounce);

	regmap_update_bits(priv->regmap, RG_ACCDET_RST_ADDR,
			   RG_ACCDET_RST_MASK_SFT, BIT(RG_ACCDET_RST_SFT));
	regmap_update_bits(priv->regmap, RG_ACCDET_RST_ADDR,
			   RG_ACCDET_RST_MASK_SFT, 0);

	/* clear high micbias1 voltage setting */
	regmap_update_bits(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
			   0x3 << RG_AUDMICBIAS1HVEN_SFT, 0);
	regmap_update_bits(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
			   0x7 << RG_AUDMICBIAS1VREF_SFT, 0);

	/* init pwm frequency, duty & rise/falling delay */
	regmap_ग_लिखो(priv->regmap, ACCDET_PWM_WIDTH_ADDR,
		     REGISTER_VAL(priv->data->pwm_deb->pwm_width));
	regmap_ग_लिखो(priv->regmap, ACCDET_PWM_THRESH_ADDR,
		     REGISTER_VAL(priv->data->pwm_deb->pwm_thresh));
	regmap_ग_लिखो(priv->regmap, ACCDET_RISE_DELAY_ADDR,
		     (priv->data->pwm_deb->fall_delay << 15 |
		      priv->data->pwm_deb->rise_delay));

	regmap_पढ़ो(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR, &reg);
	अगर (priv->data->mic_vol <= 7) अणु
		/* micbias1 <= 2.7V */
		regmap_ग_लिखो(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
			     reg | (priv->data->mic_vol << RG_AUDMICBIAS1VREF_SFT) |
			     RG_AUDMICBIAS1LOWPEN_MASK_SFT);
	पूर्ण अन्यथा अगर (priv->data->mic_vol == 8) अणु
		/* micbias1 = 2.8v */
		regmap_ग_लिखो(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
			     reg | (3 << RG_AUDMICBIAS1HVEN_SFT) |
			     RG_AUDMICBIAS1LOWPEN_MASK_SFT);
	पूर्ण अन्यथा अगर (priv->data->mic_vol == 9) अणु
		/* micbias1 = 2.85v */
		regmap_ग_लिखो(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
			     reg | (1 << RG_AUDMICBIAS1HVEN_SFT) |
			     RG_AUDMICBIAS1LOWPEN_MASK_SFT);
	पूर्ण
	/* mic mode setting */
	regmap_पढ़ो(priv->regmap, RG_AUDACCDETMICBIAS0PULLLOW_ADDR, &reg);
	अगर (priv->data->mic_mode == HEADSET_MODE_1) अणु
		/* ACC mode*/
		regmap_ग_लिखो(priv->regmap, RG_AUDACCDETMICBIAS0PULLLOW_ADDR,
			     reg | RG_ACCDET_MODE_ANA11_MODE1);
		/* enable analog fast disअक्षरge */
		regmap_update_bits(priv->regmap, RG_ANALOGFDEN_ADDR,
				   RG_ANALOGFDEN_MASK_SFT,
				   BIT(RG_ANALOGFDEN_SFT));
		regmap_update_bits(priv->regmap, RG_ACCDETSPARE_ADDR,
				   0x3 << 11, 0x3 << 11);
	पूर्ण अन्यथा अगर (priv->data->mic_mode == HEADSET_MODE_2) अणु
		/* DCC mode Low cost mode without पूर्णांकernal bias */
		regmap_ग_लिखो(priv->regmap, RG_AUDACCDETMICBIAS0PULLLOW_ADDR,
			     reg | RG_ACCDET_MODE_ANA11_MODE2);
		/* enable analog fast disअक्षरge */
		regmap_update_bits(priv->regmap, RG_ANALOGFDEN_ADDR,
				   0x3 << RG_ANALOGFDEN_SFT,
				   0x3 << RG_ANALOGFDEN_SFT);
	पूर्ण अन्यथा अगर (priv->data->mic_mode == HEADSET_MODE_6) अणु
		/* DCC mode Low cost mode with पूर्णांकernal bias,
		 * bit8 = 1 to use पूर्णांकernal bias
		 */
		regmap_ग_लिखो(priv->regmap, RG_AUDACCDETMICBIAS0PULLLOW_ADDR,
			     reg | RG_ACCDET_MODE_ANA11_MODE6);
		regmap_update_bits(priv->regmap, RG_AUDPWDBMICBIAS1_ADDR,
				   RG_AUDMICBIAS1DCSW1PEN_MASK_SFT,
				   BIT(RG_AUDMICBIAS1DCSW1PEN_SFT));
		/* enable analog fast disअक्षरge */
		regmap_update_bits(priv->regmap, RG_ANALOGFDEN_ADDR,
				   0x3 << RG_ANALOGFDEN_SFT,
				   0x3 << RG_ANALOGFDEN_SFT);
	पूर्ण

	अगर (priv->caps & ACCDET_PMIC_EINT_IRQ) अणु
		config_eपूर्णांक_init_by_mode(priv);
		config_digital_init_by_mode(priv);
	पूर्ण
पूर्ण

पूर्णांक mt6359_accdet_enable_jack_detect(काष्ठा snd_soc_component *component,
				     काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा mt6359_accdet *priv =
		snd_soc_component_get_drvdata(component);

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOLUMEDOWN);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	priv->jack = jack;

	mt6359_accdet_jack_report(priv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt6359_accdet_enable_jack_detect);

अटल पूर्णांक mt6359_accdet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6359_accdet *priv;
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret = 0;

	dev_dbg(&pdev->dev, "%s(), dev name %s\n",
		__func__, dev_name(&pdev->dev));

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा mt6359_accdet),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->data = devm_kzalloc(&pdev->dev, माप(काष्ठा dts_data),
				  GFP_KERNEL);
	अगर (!priv->data)
		वापस -ENOMEM;

	priv->data->pwm_deb = devm_kzalloc(&pdev->dev,
					   माप(काष्ठा pwm_deb_settings),
					   GFP_KERNEL);
	अगर (!priv->data->pwm_deb)
		वापस -ENOMEM;

	priv->regmap = mt6397->regmap;
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&pdev->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण
	priv->dev = &pdev->dev;

	ret = mt6359_accdet_parse_dt(priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to parse dts\n");
		वापस ret;
	पूर्ण
	mutex_init(&priv->res_lock);

	priv->accdet_irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->accdet_irq) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, priv->accdet_irq,
						शून्य, mt6359_accdet_irq,
						IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
						"ACCDET_IRQ", priv);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to request IRQ: (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (priv->caps & ACCDET_PMIC_EINT0) अणु
		priv->accdet_eपूर्णांक0 = platक्रमm_get_irq(pdev, 1);
		अगर (priv->accdet_eपूर्णांक0) अणु
			ret = devm_request_thपढ़ोed_irq(&pdev->dev,
							priv->accdet_eपूर्णांक0,
							शून्य, mt6359_accdet_irq,
							IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
							"ACCDET_EINT0", priv);
			अगर (ret) अणु
				dev_err(&pdev->dev,
					"Failed to request eint0 IRQ (%d)\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (priv->caps & ACCDET_PMIC_EINT1) अणु
		priv->accdet_eपूर्णांक1 = platक्रमm_get_irq(pdev, 2);
		अगर (priv->accdet_eपूर्णांक1) अणु
			ret = devm_request_thपढ़ोed_irq(&pdev->dev,
							priv->accdet_eपूर्णांक1,
							शून्य, mt6359_accdet_irq,
							IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
							"ACCDET_EINT1", priv);
			अगर (ret) अणु
				dev_err(&pdev->dev,
					"Failed to request eint1 IRQ (%d)\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->accdet_workqueue = create_singlethपढ़ो_workqueue("accdet");
	INIT_WORK(&priv->accdet_work, mt6359_accdet_work);
	अगर (!priv->accdet_workqueue) अणु
		dev_err(&pdev->dev, "Failed to create accdet workqueue\n");
		ret = -1;
		जाओ err_accdet_wq;
	पूर्ण

	priv->jd_workqueue = create_singlethपढ़ो_workqueue("mt6359_accdet_jd");
	INIT_WORK(&priv->jd_work, mt6359_accdet_jd_work);
	अगर (!priv->jd_workqueue) अणु
		dev_err(&pdev->dev, "Failed to create jack detect workqueue\n");
		ret = -1;
		जाओ err_eपूर्णांक_wq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mt6359_accdet_soc_driver,
					      शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register component\n");
		वापस ret;
	पूर्ण

	priv->jd_sts = M_PLUG_OUT;
	priv->jack_type = 0;
	priv->btn_type = 0;
	priv->accdet_status = 0x3;
	mt6359_accdet_init(priv);

	mt6359_accdet_jack_report(priv);

	वापस 0;

err_eपूर्णांक_wq:
	destroy_workqueue(priv->accdet_workqueue);
err_accdet_wq:
	dev_err(&pdev->dev, "%s error. now exit.!\n", __func__);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mt6359_accdet_driver = अणु
	.driver = अणु
		.name = "pmic-codec-accdet",
	पूर्ण,
	.probe = mt6359_accdet_probe,
पूर्ण;

अटल पूर्णांक __init mt6359_accdet_driver_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = platक्रमm_driver_रेजिस्टर(&mt6359_accdet_driver);
	अगर (ret)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास mt6359_accdet_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mt6359_accdet_driver);
पूर्ण
module_init(mt6359_accdet_driver_init);
module_निकास(mt6359_accdet_driver_निकास);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT6359 ALSA SoC codec jack driver");
MODULE_AUTHOR("Argus Lin <argus.lin@mediatek.com>");
MODULE_LICENSE("GPL v2");
