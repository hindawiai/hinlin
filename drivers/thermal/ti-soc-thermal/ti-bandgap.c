<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI Bandgap temperature sensor driver
 *
 * Copyright (C) 2011-2012 Texas Instruments Incorporated - http://www.ti.com/
 * Author: J Keerthy <j-keerthy@ti.com>
 * Author: Moiz Sonasath <m-sonasath@ti.com>
 * Couple of fixes, DT and MFD adaptation:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/types.h>

#समावेश "ti-bandgap.h"

अटल पूर्णांक ti_bandgap_क्रमce_single_पढ़ो(काष्ठा ti_bandgap *bgp, पूर्णांक id);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bandgap_omap_cpu_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ cmd, व्योम *v);
#पूर्ण_अगर

/***   Helper functions to access रेजिस्टरs and their bitfields   ***/

/**
 * ti_bandgap_पढ़ोl() - simple पढ़ो helper function
 * @bgp: poपूर्णांकer to ti_bandgap काष्ठाure
 * @reg: desired रेजिस्टर (offset) to be पढ़ो
 *
 * Helper function to पढ़ो bandgap रेजिस्टरs. It uses the io remapped area.
 * Return: the रेजिस्टर value.
 */
अटल u32 ti_bandgap_पढ़ोl(काष्ठा ti_bandgap *bgp, u32 reg)
अणु
	वापस पढ़ोl(bgp->base + reg);
पूर्ण

/**
 * ti_bandgap_ग_लिखोl() - simple ग_लिखो helper function
 * @bgp: poपूर्णांकer to ti_bandgap काष्ठाure
 * @val: desired रेजिस्टर value to be written
 * @reg: desired रेजिस्टर (offset) to be written
 *
 * Helper function to ग_लिखो bandgap रेजिस्टरs. It uses the io remapped area.
 */
अटल व्योम ti_bandgap_ग_लिखोl(काष्ठा ti_bandgap *bgp, u32 val, u32 reg)
अणु
	ग_लिखोl(val, bgp->base + reg);
पूर्ण

/**
 * DOC: macro to update bits.
 *
 * RMW_BITS() - used to पढ़ो, modअगरy and update bandgap bitfields.
 *            The value passed will be shअगरted.
 */
#घोषणा RMW_BITS(bgp, id, reg, mask, val)			\
करो अणु								\
	काष्ठा temp_sensor_रेजिस्टरs *t;			\
	u32 r;							\
								\
	t = bgp->conf->sensors[(id)].रेजिस्टरs;		\
	r = ti_bandgap_पढ़ोl(bgp, t->reg);			\
	r &= ~t->mask;						\
	r |= (val) << __ffs(t->mask);				\
	ti_bandgap_ग_लिखोl(bgp, r, t->reg);			\
पूर्ण जबतक (0)

/***   Basic helper functions   ***/

/**
 * ti_bandgap_घातer() - controls the घातer state of a bandgap device
 * @bgp: poपूर्णांकer to ti_bandgap काष्ठाure
 * @on: desired घातer state (1 - on, 0 - off)
 *
 * Used to घातer on/off a bandgap device instance. Only used on those
 * that features tempsoff bit.
 *
 * Return: 0 on success, -ENOTSUPP अगर tempsoff is not supported.
 */
अटल पूर्णांक ti_bandgap_घातer(काष्ठा ti_bandgap *bgp, bool on)
अणु
	पूर्णांक i;

	अगर (!TI_BANDGAP_HAS(bgp, POWER_SWITCH))
		वापस -ENOTSUPP;

	क्रम (i = 0; i < bgp->conf->sensor_count; i++)
		/* active on 0 */
		RMW_BITS(bgp, i, temp_sensor_ctrl, bgap_tempsoff_mask, !on);
	वापस 0;
पूर्ण

/**
 * ti_errata814_bandgap_पढ़ो_temp() - helper function to पढ़ो dra7 sensor temperature
 * @bgp: poपूर्णांकer to ti_bandgap काष्ठाure
 * @reg: desired रेजिस्टर (offset) to be पढ़ो
 *
 * Function to पढ़ो dra7 bandgap sensor temperature. This is करोne separately
 * so as to workaround the errata "Bandgap Temperature पढ़ो Dtemp can be
 * corrupted" - Errata ID: i814".
 * Read accesses to रेजिस्टरs listed below can be corrupted due to incorrect
 * resynchronization between घड़ी करोमुख्यs.
 * Read access to रेजिस्टरs below can be corrupted :
 * CTRL_CORE_DTEMP_MPU/GPU/CORE/DSPEVE/IVA_n (n = 0 to 4)
 * CTRL_CORE_TEMP_SENSOR_MPU/GPU/CORE/DSPEVE/IVA_n
 *
 * Return: the रेजिस्टर value.
 */
अटल u32 ti_errata814_bandgap_पढ़ो_temp(काष्ठा ti_bandgap *bgp,  u32 reg)
अणु
	u32 val1, val2;

	val1 = ti_bandgap_पढ़ोl(bgp, reg);
	val2 = ti_bandgap_पढ़ोl(bgp, reg);

	/* If both बार we पढ़ो the same value then that is right */
	अगर (val1 == val2)
		वापस val1;

	/* अगर val1 and val2 are dअगरferent पढ़ो it third समय */
	वापस ti_bandgap_पढ़ोl(bgp, reg);
पूर्ण

/**
 * ti_bandgap_पढ़ो_temp() - helper function to पढ़ो sensor temperature
 * @bgp: poपूर्णांकer to ti_bandgap काष्ठाure
 * @id: bandgap sensor id
 *
 * Function to concentrate the steps to पढ़ो sensor temperature रेजिस्टर.
 * This function is desired because, depending on bandgap device version,
 * it might be needed to मुक्तze the bandgap state machine, beक्रमe fetching
 * the रेजिस्टर value.
 *
 * Return: temperature in ADC values.
 */
अटल u32 ti_bandgap_पढ़ो_temp(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा temp_sensor_रेजिस्टरs *tsr;
	u32 temp, reg;

	tsr = bgp->conf->sensors[id].रेजिस्टरs;
	reg = tsr->temp_sensor_ctrl;

	अगर (TI_BANDGAP_HAS(bgp, FREEZE_BIT)) अणु
		RMW_BITS(bgp, id, bgap_mask_ctrl, mask_मुक्तze_mask, 1);
		/*
		 * In हाल we cannot पढ़ो from cur_dtemp / dtemp_0,
		 * then we पढ़ो from the last valid temp पढ़ो
		 */
		reg = tsr->ctrl_dtemp_1;
	पूर्ण

	/* पढ़ो temperature */
	अगर (TI_BANDGAP_HAS(bgp, ERRATA_814))
		temp = ti_errata814_bandgap_पढ़ो_temp(bgp, reg);
	अन्यथा
		temp = ti_bandgap_पढ़ोl(bgp, reg);

	temp &= tsr->bgap_dtemp_mask;

	अगर (TI_BANDGAP_HAS(bgp, FREEZE_BIT))
		RMW_BITS(bgp, id, bgap_mask_ctrl, mask_मुक्तze_mask, 0);

	वापस temp;
पूर्ण

/***   IRQ handlers   ***/

/**
 * ti_bandgap_talert_irq_handler() - handles Temperature alert IRQs
 * @irq: IRQ number
 * @data: निजी data (काष्ठा ti_bandgap *)
 *
 * This is the Talert handler. Use it only अगर bandgap device features
 * HAS(TALERT). This handler goes over all sensors and checks their
 * conditions and acts accordingly. In हाल there are events pending,
 * it will reset the event mask to रुको क्रम the opposite event (next event).
 * Every समय there is a new event, it will be reported to thermal layer.
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t ti_bandgap_talert_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ti_bandgap *bgp = data;
	काष्ठा temp_sensor_रेजिस्टरs *tsr;
	u32 t_hot = 0, t_cold = 0, ctrl;
	पूर्णांक i;

	spin_lock(&bgp->lock);
	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		tsr = bgp->conf->sensors[i].रेजिस्टरs;
		ctrl = ti_bandgap_पढ़ोl(bgp, tsr->bgap_status);

		/* Read the status of t_hot */
		t_hot = ctrl & tsr->status_hot_mask;

		/* Read the status of t_cold */
		t_cold = ctrl & tsr->status_cold_mask;

		अगर (!t_cold && !t_hot)
			जारी;

		ctrl = ti_bandgap_पढ़ोl(bgp, tsr->bgap_mask_ctrl);
		/*
		 * One TALERT पूर्णांकerrupt: Two sources
		 * If the पूर्णांकerrupt is due to t_hot then mask t_hot and
		 * and unmask t_cold अन्यथा mask t_cold and unmask t_hot
		 */
		अगर (t_hot) अणु
			ctrl &= ~tsr->mask_hot_mask;
			ctrl |= tsr->mask_cold_mask;
		पूर्ण अन्यथा अगर (t_cold) अणु
			ctrl &= ~tsr->mask_cold_mask;
			ctrl |= tsr->mask_hot_mask;
		पूर्ण

		ti_bandgap_ग_लिखोl(bgp, ctrl, tsr->bgap_mask_ctrl);

		dev_dbg(bgp->dev,
			"%s: IRQ from %s sensor: hotevent %d coldevent %d\n",
			__func__, bgp->conf->sensors[i].करोमुख्य,
			t_hot, t_cold);

		/* report temperature to whom may concern */
		अगर (bgp->conf->report_temperature)
			bgp->conf->report_temperature(bgp, i);
	पूर्ण
	spin_unlock(&bgp->lock);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ti_bandgap_tshut_irq_handler() - handles Temperature shutकरोwn संकेत
 * @irq: IRQ number
 * @data: निजी data (unused)
 *
 * This is the Tshut handler. Use it only अगर bandgap device features
 * HAS(TSHUT). If any sensor fires the Tshut संकेत, we simply shutकरोwn
 * the प्रणाली.
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t ti_bandgap_tshut_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	pr_emerg("%s: TSHUT temperature reached. Needs shut down...\n",
		 __func__);

	orderly_घातeroff(true);

	वापस IRQ_HANDLED;
पूर्ण

/***   Helper functions which manipulate conversion ADC <-> mi Celsius   ***/

/**
 * ti_bandgap_adc_to_mcelsius() - converts an ADC value to mCelsius scale
 * @bgp: काष्ठा ti_bandgap poपूर्णांकer
 * @adc_val: value in ADC representation
 * @t: address where to ग_लिखो the resulting temperature in mCelsius
 *
 * Simple conversion from ADC representation to mCelsius. In हाल the ADC value
 * is out of the ADC conv table range, it वापसs -दुस्फल, 0 on success.
 * The conversion table is indexed by the ADC values.
 *
 * Return: 0 अगर conversion was successful, अन्यथा -दुस्फल in हाल the @adc_val
 * argument is out of the ADC conv table range.
 */
अटल
पूर्णांक ti_bandgap_adc_to_mcelsius(काष्ठा ti_bandgap *bgp, पूर्णांक adc_val, पूर्णांक *t)
अणु
	स्थिर काष्ठा ti_bandgap_data *conf = bgp->conf;

	/* look up क्रम temperature in the table and वापस the temperature */
	अगर (adc_val < conf->adc_start_val || adc_val > conf->adc_end_val)
		वापस -दुस्फल;

	*t = bgp->conf->conv_table[adc_val - conf->adc_start_val];
	वापस 0;
पूर्ण

/**
 * ti_bandgap_validate() - helper to check the sanity of a काष्ठा ti_bandgap
 * @bgp: काष्ठा ti_bandgap poपूर्णांकer
 * @id: bandgap sensor id
 *
 * Checks अगर the bandgap poपूर्णांकer is valid and अगर the sensor id is also
 * applicable.
 *
 * Return: 0 अगर no errors, -EINVAL क्रम invalid @bgp poपूर्णांकer or -दुस्फल अगर
 * @id cannot index @bgp sensors.
 */
अटल अंतरभूत पूर्णांक ti_bandgap_validate(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	अगर (!bgp || IS_ERR(bgp)) अणु
		pr_err("%s: invalid bandgap pointer\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर ((id < 0) || (id >= bgp->conf->sensor_count)) अणु
		dev_err(bgp->dev, "%s: sensor id out of range (%d)\n",
			__func__, id);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ti_bandgap_पढ़ो_counter() - पढ़ो the sensor counter
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: resulting update पूर्णांकerval in miliseconds
 */
अटल व्योम ti_bandgap_पढ़ो_counter(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				    पूर्णांक *पूर्णांकerval)
अणु
	काष्ठा temp_sensor_रेजिस्टरs *tsr;
	पूर्णांक समय;

	tsr = bgp->conf->sensors[id].रेजिस्टरs;
	समय = ti_bandgap_पढ़ोl(bgp, tsr->bgap_counter);
	समय = (समय & tsr->counter_mask) >>
					__ffs(tsr->counter_mask);
	समय = समय * 1000 / bgp->clk_rate;
	*पूर्णांकerval = समय;
पूर्ण

/**
 * ti_bandgap_पढ़ो_counter_delay() - पढ़ो the sensor counter delay
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: resulting update पूर्णांकerval in miliseconds
 */
अटल व्योम ti_bandgap_पढ़ो_counter_delay(काष्ठा ti_bandgap *bgp, पूर्णांक id,
					  पूर्णांक *पूर्णांकerval)
अणु
	काष्ठा temp_sensor_रेजिस्टरs *tsr;
	पूर्णांक reg_val;

	tsr = bgp->conf->sensors[id].रेजिस्टरs;

	reg_val = ti_bandgap_पढ़ोl(bgp, tsr->bgap_mask_ctrl);
	reg_val = (reg_val & tsr->mask_counter_delay_mask) >>
				__ffs(tsr->mask_counter_delay_mask);
	चयन (reg_val) अणु
	हाल 0:
		*पूर्णांकerval = 0;
		अवरोध;
	हाल 1:
		*पूर्णांकerval = 1;
		अवरोध;
	हाल 2:
		*पूर्णांकerval = 10;
		अवरोध;
	हाल 3:
		*पूर्णांकerval = 100;
		अवरोध;
	हाल 4:
		*पूर्णांकerval = 250;
		अवरोध;
	हाल 5:
		*पूर्णांकerval = 500;
		अवरोध;
	शेष:
		dev_warn(bgp->dev, "Wrong counter delay value read from register %X",
			 reg_val);
	पूर्ण
पूर्ण

/**
 * ti_bandgap_पढ़ो_update_पूर्णांकerval() - पढ़ो the sensor update पूर्णांकerval
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: resulting update पूर्णांकerval in miliseconds
 *
 * Return: 0 on success or the proper error code
 */
पूर्णांक ti_bandgap_पढ़ो_update_पूर्णांकerval(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				    पूर्णांक *पूर्णांकerval)
अणु
	पूर्णांक ret = 0;

	ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		जाओ निकास;

	अगर (!TI_BANDGAP_HAS(bgp, COUNTER) &&
	    !TI_BANDGAP_HAS(bgp, COUNTER_DELAY)) अणु
		ret = -ENOTSUPP;
		जाओ निकास;
	पूर्ण

	अगर (TI_BANDGAP_HAS(bgp, COUNTER)) अणु
		ti_bandgap_पढ़ो_counter(bgp, id, पूर्णांकerval);
		जाओ निकास;
	पूर्ण

	ti_bandgap_पढ़ो_counter_delay(bgp, id, पूर्णांकerval);
निकास:
	वापस ret;
पूर्ण

/**
 * ti_bandgap_ग_लिखो_counter_delay() - set the counter_delay
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: desired update पूर्णांकerval in miliseconds
 *
 * Return: 0 on success or the proper error code
 */
अटल पूर्णांक ti_bandgap_ग_लिखो_counter_delay(काष्ठा ti_bandgap *bgp, पूर्णांक id,
					  u32 पूर्णांकerval)
अणु
	पूर्णांक rval;

	चयन (पूर्णांकerval) अणु
	हाल 0: /* Immediate conversion */
		rval = 0x0;
		अवरोध;
	हाल 1: /* Conversion after ever 1ms */
		rval = 0x1;
		अवरोध;
	हाल 10: /* Conversion after ever 10ms */
		rval = 0x2;
		अवरोध;
	हाल 100: /* Conversion after ever 100ms */
		rval = 0x3;
		अवरोध;
	हाल 250: /* Conversion after ever 250ms */
		rval = 0x4;
		अवरोध;
	हाल 500: /* Conversion after ever 500ms */
		rval = 0x5;
		अवरोध;
	शेष:
		dev_warn(bgp->dev, "Delay %d ms is not supported\n", पूर्णांकerval);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&bgp->lock);
	RMW_BITS(bgp, id, bgap_mask_ctrl, mask_counter_delay_mask, rval);
	spin_unlock(&bgp->lock);

	वापस 0;
पूर्ण

/**
 * ti_bandgap_ग_लिखो_counter() - set the bandgap sensor counter
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: desired update पूर्णांकerval in miliseconds
 */
अटल व्योम ti_bandgap_ग_लिखो_counter(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				     u32 पूर्णांकerval)
अणु
	पूर्णांकerval = पूर्णांकerval * bgp->clk_rate / 1000;
	spin_lock(&bgp->lock);
	RMW_BITS(bgp, id, bgap_counter, counter_mask, पूर्णांकerval);
	spin_unlock(&bgp->lock);
पूर्ण

/**
 * ti_bandgap_ग_लिखो_update_पूर्णांकerval() - set the update पूर्णांकerval
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @पूर्णांकerval: desired update पूर्णांकerval in miliseconds
 *
 * Return: 0 on success or the proper error code
 */
पूर्णांक ti_bandgap_ग_लिखो_update_पूर्णांकerval(काष्ठा ti_bandgap *bgp,
				     पूर्णांक id, u32 पूर्णांकerval)
अणु
	पूर्णांक ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		जाओ निकास;

	अगर (!TI_BANDGAP_HAS(bgp, COUNTER) &&
	    !TI_BANDGAP_HAS(bgp, COUNTER_DELAY)) अणु
		ret = -ENOTSUPP;
		जाओ निकास;
	पूर्ण

	अगर (TI_BANDGAP_HAS(bgp, COUNTER)) अणु
		ti_bandgap_ग_लिखो_counter(bgp, id, पूर्णांकerval);
		जाओ निकास;
	पूर्ण

	ret = ti_bandgap_ग_लिखो_counter_delay(bgp, id, पूर्णांकerval);
निकास:
	वापस ret;
पूर्ण

/**
 * ti_bandgap_पढ़ो_temperature() - report current temperature
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @temperature: resulting temperature
 *
 * Return: 0 on success or the proper error code
 */
पूर्णांक ti_bandgap_पढ़ो_temperature(काष्ठा ti_bandgap *bgp, पूर्णांक id,
				पूर्णांक *temperature)
अणु
	u32 temp;
	पूर्णांक ret;

	ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		वापस ret;

	अगर (!TI_BANDGAP_HAS(bgp, MODE_CONFIG)) अणु
		ret = ti_bandgap_क्रमce_single_पढ़ो(bgp, id);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock(&bgp->lock);
	temp = ti_bandgap_पढ़ो_temp(bgp, id);
	spin_unlock(&bgp->lock);

	ret = ti_bandgap_adc_to_mcelsius(bgp, temp, &temp);
	अगर (ret)
		वापस -EIO;

	*temperature = temp;

	वापस 0;
पूर्ण

/**
 * ti_bandgap_set_sensor_data() - helper function to store thermal
 * framework related data.
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 * @data: thermal framework related data to be stored
 *
 * Return: 0 on success or the proper error code
 */
पूर्णांक ti_bandgap_set_sensor_data(काष्ठा ti_bandgap *bgp, पूर्णांक id, व्योम *data)
अणु
	पूर्णांक ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		वापस ret;

	bgp->regval[id].data = data;

	वापस 0;
पूर्ण

/**
 * ti_bandgap_get_sensor_data() - helper function to get thermal
 * framework related data.
 * @bgp: poपूर्णांकer to bandgap instance
 * @id: sensor id
 *
 * Return: data stored by set function with sensor id on success or शून्य
 */
व्योम *ti_bandgap_get_sensor_data(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	पूर्णांक ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस bgp->regval[id].data;
पूर्ण

/***   Helper functions used during device initialization   ***/

/**
 * ti_bandgap_क्रमce_single_पढ़ो() - executes 1 single ADC conversion
 * @bgp: poपूर्णांकer to काष्ठा ti_bandgap
 * @id: sensor id which it is desired to पढ़ो 1 temperature
 *
 * Used to initialize the conversion state machine and set it to a valid
 * state. Called during device initialization and context restore events.
 *
 * Return: 0
 */
अटल पूर्णांक
ti_bandgap_क्रमce_single_पढ़ो(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा temp_sensor_रेजिस्टरs *tsr = bgp->conf->sensors[id].रेजिस्टरs;
	व्योम __iomem *temp_sensor_ctrl = bgp->base + tsr->temp_sensor_ctrl;
	पूर्णांक error;
	u32 val;

	/* Select continuous or single conversion mode */
	अगर (TI_BANDGAP_HAS(bgp, MODE_CONFIG)) अणु
		अगर (TI_BANDGAP_HAS(bgp, CONT_MODE_ONLY))
			RMW_BITS(bgp, id, bgap_mode_ctrl, mode_ctrl_mask, 1);
		अन्यथा
			RMW_BITS(bgp, id, bgap_mode_ctrl, mode_ctrl_mask, 0);
	पूर्ण

	/* Set Start of Conversion अगर available */
	अगर (tsr->bgap_soc_mask) अणु
		RMW_BITS(bgp, id, temp_sensor_ctrl, bgap_soc_mask, 1);

		/* Wait क्रम EOCZ going up */
		error = पढ़ोl_poll_समयout_atomic(temp_sensor_ctrl, val,
						  val & tsr->bgap_eocz_mask,
						  1, 1000);
		अगर (error)
			dev_warn(bgp->dev, "eocz timed out waiting high\n");

		/* Clear Start of Conversion अगर available */
		RMW_BITS(bgp, id, temp_sensor_ctrl, bgap_soc_mask, 0);
	पूर्ण

	/* Wait क्रम EOCZ going करोwn, always needed even अगर no bgap_soc_mask */
	error = पढ़ोl_poll_समयout_atomic(temp_sensor_ctrl, val,
					  !(val & tsr->bgap_eocz_mask),
					  1, 1500);
	अगर (error)
		dev_warn(bgp->dev, "eocz timed out waiting low\n");

	वापस 0;
पूर्ण

/**
 * ti_bandgap_set_continuous_mode() - One समय enabling of continuous mode
 * @bgp: poपूर्णांकer to काष्ठा ti_bandgap
 *
 * Call this function only अगर HAS(MODE_CONFIG) is set. As this driver may
 * be used क्रम junction temperature monitoring, it is desirable that the
 * sensors are operational all the समय, so that alerts are generated
 * properly.
 *
 * Return: 0
 */
अटल पूर्णांक ti_bandgap_set_continuous_mode(काष्ठा ti_bandgap *bgp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		/* Perक्रमm a single पढ़ो just beक्रमe enabling continuous */
		ti_bandgap_क्रमce_single_पढ़ो(bgp, i);
		RMW_BITS(bgp, i, bgap_mode_ctrl, mode_ctrl_mask, 1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ti_bandgap_get_trend() - To fetch the temperature trend of a sensor
 * @bgp: poपूर्णांकer to काष्ठा ti_bandgap
 * @id: id of the inभागidual sensor
 * @trend: Poपूर्णांकer to trend.
 *
 * This function needs to be called to fetch the temperature trend of a
 * Particular sensor. The function computes the dअगरference in temperature
 * w.r.t समय. For the bandgaps with built in history buffer the temperatures
 * are पढ़ो from the buffer and क्रम those without the Buffer -ENOTSUPP is
 * वापसed.
 *
 * Return: 0 अगर no error, अन्यथा वापस corresponding error. If no
 *		error then the trend value is passed on to trend parameter
 */
पूर्णांक ti_bandgap_get_trend(काष्ठा ti_bandgap *bgp, पूर्णांक id, पूर्णांक *trend)
अणु
	काष्ठा temp_sensor_रेजिस्टरs *tsr;
	u32 temp1, temp2, reg1, reg2;
	पूर्णांक t1, t2, पूर्णांकerval, ret = 0;

	ret = ti_bandgap_validate(bgp, id);
	अगर (ret)
		जाओ निकास;

	अगर (!TI_BANDGAP_HAS(bgp, HISTORY_BUFFER) ||
	    !TI_BANDGAP_HAS(bgp, FREEZE_BIT)) अणु
		ret = -ENOTSUPP;
		जाओ निकास;
	पूर्ण

	spin_lock(&bgp->lock);

	tsr = bgp->conf->sensors[id].रेजिस्टरs;

	/* Freeze and पढ़ो the last 2 valid पढ़ोings */
	RMW_BITS(bgp, id, bgap_mask_ctrl, mask_मुक्तze_mask, 1);
	reg1 = tsr->ctrl_dtemp_1;
	reg2 = tsr->ctrl_dtemp_2;

	/* पढ़ो temperature from history buffer */
	temp1 = ti_bandgap_पढ़ोl(bgp, reg1);
	temp1 &= tsr->bgap_dtemp_mask;

	temp2 = ti_bandgap_पढ़ोl(bgp, reg2);
	temp2 &= tsr->bgap_dtemp_mask;

	/* Convert from adc values to mCelsius temperature */
	ret = ti_bandgap_adc_to_mcelsius(bgp, temp1, &t1);
	अगर (ret)
		जाओ unमुक्तze;

	ret = ti_bandgap_adc_to_mcelsius(bgp, temp2, &t2);
	अगर (ret)
		जाओ unमुक्तze;

	/* Fetch the update पूर्णांकerval */
	ret = ti_bandgap_पढ़ो_update_पूर्णांकerval(bgp, id, &पूर्णांकerval);
	अगर (ret)
		जाओ unमुक्तze;

	/* Set the पूर्णांकerval to 1 ms अगर bandgap counter delay is not set */
	अगर (पूर्णांकerval == 0)
		पूर्णांकerval = 1;

	*trend = (t1 - t2) / पूर्णांकerval;

	dev_dbg(bgp->dev, "The temperatures are t1 = %d and t2 = %d and trend =%d\n",
		t1, t2, *trend);

unमुक्तze:
	RMW_BITS(bgp, id, bgap_mask_ctrl, mask_मुक्तze_mask, 0);
	spin_unlock(&bgp->lock);
निकास:
	वापस ret;
पूर्ण

/**
 * ti_bandgap_tshut_init() - setup and initialize tshut handling
 * @bgp: poपूर्णांकer to काष्ठा ti_bandgap
 * @pdev: poपूर्णांकer to device काष्ठा platक्रमm_device
 *
 * Call this function only in हाल the bandgap features HAS(TSHUT).
 * In this हाल, the driver needs to handle the TSHUT संकेत as an IRQ.
 * The IRQ is wired as a GPIO, and क्रम this purpose, it is required
 * to specअगरy which GPIO line is used. TSHUT IRQ is fired anyसमय
 * one of the bandgap sensors violates the TSHUT high/hot threshold.
 * And in that हाल, the प्रणाली must go off.
 *
 * Return: 0 अगर no error, अन्यथा error status
 */
अटल पूर्णांक ti_bandgap_tshut_init(काष्ठा ti_bandgap *bgp,
				 काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;

	status = request_irq(gpiod_to_irq(bgp->tshut_gpiod),
			     ti_bandgap_tshut_irq_handler,
			     IRQF_TRIGGER_RISING, "tshut", शून्य);
	अगर (status)
		dev_err(bgp->dev, "request irq failed for TSHUT");

	वापस 0;
पूर्ण

/**
 * ti_bandgap_talert_init() - setup and initialize talert handling
 * @bgp: poपूर्णांकer to काष्ठा ti_bandgap
 * @pdev: poपूर्णांकer to device काष्ठा platक्रमm_device
 *
 * Call this function only in हाल the bandgap features HAS(TALERT).
 * In this हाल, the driver needs to handle the TALERT संकेतs as an IRQs.
 * TALERT is a normal IRQ and it is fired any समय thresholds (hot or cold)
 * are violated. In these situation, the driver must reprogram the thresholds,
 * accordingly to specअगरied policy.
 *
 * Return: 0 अगर no error, अन्यथा वापस corresponding error.
 */
अटल पूर्णांक ti_bandgap_talert_init(काष्ठा ti_bandgap *bgp,
				  काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	bgp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bgp->irq < 0)
		वापस bgp->irq;

	ret = request_thपढ़ोed_irq(bgp->irq, शून्य,
				   ti_bandgap_talert_irq_handler,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   "talert", bgp);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Request threaded irq failed.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_ti_bandgap_match[];
/**
 * ti_bandgap_build() - parse DT and setup a काष्ठा ti_bandgap
 * @pdev: poपूर्णांकer to device काष्ठा platक्रमm_device
 *
 * Used to पढ़ो the device tree properties accordingly to the bandgap
 * matching version. Based on bandgap version and its capabilities it
 * will build a काष्ठा ti_bandgap out of the required DT entries.
 *
 * Return: valid bandgap काष्ठाure अगर successful, अन्यथा वापसs ERR_PTR
 * वापस value must be verअगरied with IS_ERR.
 */
अटल काष्ठा ti_bandgap *ti_bandgap_build(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा ti_bandgap *bgp;
	काष्ठा resource *res;
	पूर्णांक i;

	/* just क्रम the sake */
	अगर (!node) अणु
		dev_err(&pdev->dev, "no platform information available\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	bgp = devm_kzalloc(&pdev->dev, माप(*bgp), GFP_KERNEL);
	अगर (!bgp)
		वापस ERR_PTR(-ENOMEM);

	of_id = of_match_device(of_ti_bandgap_match, &pdev->dev);
	अगर (of_id)
		bgp->conf = of_id->data;

	/* रेजिस्टर shaकरोw क्रम context save and restore */
	bgp->regval = devm_kसुस्मृति(&pdev->dev, bgp->conf->sensor_count,
				   माप(*bgp->regval), GFP_KERNEL);
	अगर (!bgp->regval)
		वापस ERR_PTR(-ENOMEM);

	i = 0;
	करो अणु
		व्योम __iomem *chunk;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			अवरोध;
		chunk = devm_ioremap_resource(&pdev->dev, res);
		अगर (i == 0)
			bgp->base = chunk;
		अगर (IS_ERR(chunk))
			वापस ERR_CAST(chunk);

		i++;
	पूर्ण जबतक (res);

	अगर (TI_BANDGAP_HAS(bgp, TSHUT)) अणु
		bgp->tshut_gpiod = devm_gpiod_get(&pdev->dev, शून्य, GPIOD_IN);
		अगर (IS_ERR(bgp->tshut_gpiod)) अणु
			dev_err(&pdev->dev, "invalid gpio for tshut\n");
			वापस ERR_CAST(bgp->tshut_gpiod);
		पूर्ण
	पूर्ण

	वापस bgp;
पूर्ण

/*
 * List of SoCs on which the CPU PM notअगरier can cause erros on the DTEMP
 * पढ़ोout.
 * Enabled notअगरier on these machines results in erroneous, अक्रमom values which
 * could trigger unexpected thermal shutकरोwn.
 */
अटल स्थिर काष्ठा soc_device_attribute soc_no_cpu_notअगरier[] = अणु
	अणु .machine = "OMAP4430" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/***   Device driver call backs   ***/

अटल
पूर्णांक ti_bandgap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_bandgap *bgp;
	पूर्णांक clk_rate, ret, i;

	bgp = ti_bandgap_build(pdev);
	अगर (IS_ERR(bgp)) अणु
		dev_err(&pdev->dev, "failed to fetch platform data\n");
		वापस PTR_ERR(bgp);
	पूर्ण
	bgp->dev = &pdev->dev;

	अगर (TI_BANDGAP_HAS(bgp, UNRELIABLE))
		dev_warn(&pdev->dev,
			 "This OMAP thermal sensor is unreliable. You've been warned\n");

	अगर (TI_BANDGAP_HAS(bgp, TSHUT)) अणु
		ret = ti_bandgap_tshut_init(bgp, pdev);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed to initialize system tshut IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	bgp->fघड़ी = clk_get(शून्य, bgp->conf->fघड़ी_name);
	अगर (IS_ERR(bgp->fघड़ी)) अणु
		dev_err(&pdev->dev, "failed to request fclock reference\n");
		ret = PTR_ERR(bgp->fघड़ी);
		जाओ मुक्त_irqs;
	पूर्ण

	bgp->भाग_clk = clk_get(शून्य, bgp->conf->भाग_ck_name);
	अगर (IS_ERR(bgp->भाग_clk)) अणु
		dev_err(&pdev->dev, "failed to request div_ts_ck clock ref\n");
		ret = PTR_ERR(bgp->भाग_clk);
		जाओ put_fघड़ी;
	पूर्ण

	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		काष्ठा temp_sensor_रेजिस्टरs *tsr;
		u32 val;

		tsr = bgp->conf->sensors[i].रेजिस्टरs;
		/*
		 * check अगर the efuse has a non-zero value अगर not
		 * it is an untrimmed sample and the temperatures
		 * may not be accurate
		 */
		val = ti_bandgap_पढ़ोl(bgp, tsr->bgap_efuse);
		अगर (!val)
			dev_info(&pdev->dev,
				 "Non-trimmed BGAP, Temp not accurate\n");
	पूर्ण

	clk_rate = clk_round_rate(bgp->भाग_clk,
				  bgp->conf->sensors[0].ts_data->max_freq);
	अगर (clk_rate < bgp->conf->sensors[0].ts_data->min_freq ||
	    clk_rate <= 0) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev, "wrong clock rate (%d)\n", clk_rate);
		जाओ put_clks;
	पूर्ण

	ret = clk_set_rate(bgp->भाग_clk, clk_rate);
	अगर (ret)
		dev_err(&pdev->dev, "Cannot re-set clock rate. Continuing\n");

	bgp->clk_rate = clk_rate;
	अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_prepare_enable(bgp->fघड़ी);


	spin_lock_init(&bgp->lock);
	bgp->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, bgp);

	ti_bandgap_घातer(bgp, true);

	/* Set शेष counter to 1 क्रम now */
	अगर (TI_BANDGAP_HAS(bgp, COUNTER))
		क्रम (i = 0; i < bgp->conf->sensor_count; i++)
			RMW_BITS(bgp, i, bgap_counter, counter_mask, 1);

	/* Set शेष thresholds क्रम alert and shutकरोwn */
	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		काष्ठा temp_sensor_data *ts_data;

		ts_data = bgp->conf->sensors[i].ts_data;

		अगर (TI_BANDGAP_HAS(bgp, TALERT)) अणु
			/* Set initial Talert thresholds */
			RMW_BITS(bgp, i, bgap_threshold,
				 threshold_tcold_mask, ts_data->t_cold);
			RMW_BITS(bgp, i, bgap_threshold,
				 threshold_thot_mask, ts_data->t_hot);
			/* Enable the alert events */
			RMW_BITS(bgp, i, bgap_mask_ctrl, mask_hot_mask, 1);
			RMW_BITS(bgp, i, bgap_mask_ctrl, mask_cold_mask, 1);
		पूर्ण

		अगर (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG)) अणु
			/* Set initial Tshut thresholds */
			RMW_BITS(bgp, i, tshut_threshold,
				 tshut_hot_mask, ts_data->tshut_hot);
			RMW_BITS(bgp, i, tshut_threshold,
				 tshut_cold_mask, ts_data->tshut_cold);
		पूर्ण
	पूर्ण

	अगर (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
		ti_bandgap_set_continuous_mode(bgp);

	/* Set .250 seconds समय as शेष counter */
	अगर (TI_BANDGAP_HAS(bgp, COUNTER))
		क्रम (i = 0; i < bgp->conf->sensor_count; i++)
			RMW_BITS(bgp, i, bgap_counter, counter_mask,
				 bgp->clk_rate / 4);

	/* Every thing is good? Then expose the sensors */
	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		अक्षर *करोमुख्य;

		अगर (bgp->conf->sensors[i].रेजिस्टर_cooling) अणु
			ret = bgp->conf->sensors[i].रेजिस्टर_cooling(bgp, i);
			अगर (ret)
				जाओ हटाओ_sensors;
		पूर्ण

		अगर (bgp->conf->expose_sensor) अणु
			करोमुख्य = bgp->conf->sensors[i].करोमुख्य;
			ret = bgp->conf->expose_sensor(bgp, i, करोमुख्य);
			अगर (ret)
				जाओ हटाओ_last_cooling;
		पूर्ण
	पूर्ण

	/*
	 * Enable the Interrupts once everything is set. Otherwise irq handler
	 * might be called as soon as it is enabled where as rest of framework
	 * is still getting initialised.
	 */
	अगर (TI_BANDGAP_HAS(bgp, TALERT)) अणु
		ret = ti_bandgap_talert_init(bgp, pdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to initialize Talert IRQ\n");
			i = bgp->conf->sensor_count;
			जाओ disable_clk;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	bgp->nb.notअगरier_call = bandgap_omap_cpu_notअगरier;
	अगर (!soc_device_match(soc_no_cpu_notअगरier))
		cpu_pm_रेजिस्टर_notअगरier(&bgp->nb);
#पूर्ण_अगर

	वापस 0;

हटाओ_last_cooling:
	अगर (bgp->conf->sensors[i].unरेजिस्टर_cooling)
		bgp->conf->sensors[i].unरेजिस्टर_cooling(bgp, i);
हटाओ_sensors:
	क्रम (i--; i >= 0; i--) अणु
		अगर (bgp->conf->sensors[i].unरेजिस्टर_cooling)
			bgp->conf->sensors[i].unरेजिस्टर_cooling(bgp, i);
		अगर (bgp->conf->हटाओ_sensor)
			bgp->conf->हटाओ_sensor(bgp, i);
	पूर्ण
	ti_bandgap_घातer(bgp, false);
disable_clk:
	अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_disable_unprepare(bgp->fघड़ी);
put_clks:
	clk_put(bgp->भाग_clk);
put_fघड़ी:
	clk_put(bgp->fघड़ी);
मुक्त_irqs:
	अगर (TI_BANDGAP_HAS(bgp, TSHUT))
		मुक्त_irq(gpiod_to_irq(bgp->tshut_gpiod), शून्य);

	वापस ret;
पूर्ण

अटल
पूर्णांक ti_bandgap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_bandgap *bgp = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	अगर (!soc_device_match(soc_no_cpu_notअगरier))
		cpu_pm_unरेजिस्टर_notअगरier(&bgp->nb);

	/* Remove sensor पूर्णांकerfaces */
	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		अगर (bgp->conf->sensors[i].unरेजिस्टर_cooling)
			bgp->conf->sensors[i].unरेजिस्टर_cooling(bgp, i);

		अगर (bgp->conf->हटाओ_sensor)
			bgp->conf->हटाओ_sensor(bgp, i);
	पूर्ण

	ti_bandgap_घातer(bgp, false);

	अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_disable_unprepare(bgp->fघड़ी);
	clk_put(bgp->fघड़ी);
	clk_put(bgp->भाग_clk);

	अगर (TI_BANDGAP_HAS(bgp, TALERT))
		मुक्त_irq(bgp->irq, bgp);

	अगर (TI_BANDGAP_HAS(bgp, TSHUT))
		मुक्त_irq(gpiod_to_irq(bgp->tshut_gpiod), शून्य);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ti_bandgap_save_ctxt(काष्ठा ti_bandgap *bgp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		काष्ठा temp_sensor_रेजिस्टरs *tsr;
		काष्ठा temp_sensor_regval *rval;

		rval = &bgp->regval[i];
		tsr = bgp->conf->sensors[i].रेजिस्टरs;

		अगर (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
			rval->bg_mode_ctrl = ti_bandgap_पढ़ोl(bgp,
							tsr->bgap_mode_ctrl);
		अगर (TI_BANDGAP_HAS(bgp, COUNTER))
			rval->bg_counter = ti_bandgap_पढ़ोl(bgp,
							tsr->bgap_counter);
		अगर (TI_BANDGAP_HAS(bgp, TALERT)) अणु
			rval->bg_threshold = ti_bandgap_पढ़ोl(bgp,
							tsr->bgap_threshold);
			rval->bg_ctrl = ti_bandgap_पढ़ोl(bgp,
						   tsr->bgap_mask_ctrl);
		पूर्ण

		अगर (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG))
			rval->tshut_threshold = ti_bandgap_पढ़ोl(bgp,
						   tsr->tshut_threshold);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_bandgap_restore_ctxt(काष्ठा ti_bandgap *bgp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bgp->conf->sensor_count; i++) अणु
		काष्ठा temp_sensor_रेजिस्टरs *tsr;
		काष्ठा temp_sensor_regval *rval;

		rval = &bgp->regval[i];
		tsr = bgp->conf->sensors[i].रेजिस्टरs;

		अगर (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG))
			ti_bandgap_ग_लिखोl(bgp, rval->tshut_threshold,
					  tsr->tshut_threshold);
		/* Force immediate temperature measurement and update
		 * of the DTEMP field
		 */
		ti_bandgap_क्रमce_single_पढ़ो(bgp, i);

		अगर (TI_BANDGAP_HAS(bgp, COUNTER))
			ti_bandgap_ग_लिखोl(bgp, rval->bg_counter,
					  tsr->bgap_counter);
		अगर (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
			ti_bandgap_ग_लिखोl(bgp, rval->bg_mode_ctrl,
					  tsr->bgap_mode_ctrl);
		अगर (TI_BANDGAP_HAS(bgp, TALERT)) अणु
			ti_bandgap_ग_लिखोl(bgp, rval->bg_threshold,
					  tsr->bgap_threshold);
			ti_bandgap_ग_लिखोl(bgp, rval->bg_ctrl,
					  tsr->bgap_mask_ctrl);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_bandgap_suspend(काष्ठा device *dev)
अणु
	काष्ठा ti_bandgap *bgp = dev_get_drvdata(dev);
	पूर्णांक err;

	err = ti_bandgap_save_ctxt(bgp);
	ti_bandgap_घातer(bgp, false);

	अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_disable_unprepare(bgp->fघड़ी);

	bgp->is_suspended = true;

	वापस err;
पूर्ण

अटल पूर्णांक bandgap_omap_cpu_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा ti_bandgap *bgp;

	bgp = container_of(nb, काष्ठा ti_bandgap, nb);

	spin_lock(&bgp->lock);
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (bgp->is_suspended)
			अवरोध;
		ti_bandgap_save_ctxt(bgp);
		ti_bandgap_घातer(bgp, false);
		अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
			clk_disable(bgp->fघड़ी);
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (bgp->is_suspended)
			अवरोध;
		अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
			clk_enable(bgp->fघड़ी);
		ti_bandgap_घातer(bgp, true);
		ti_bandgap_restore_ctxt(bgp);
		अवरोध;
	पूर्ण
	spin_unlock(&bgp->lock);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक ti_bandgap_resume(काष्ठा device *dev)
अणु
	काष्ठा ti_bandgap *bgp = dev_get_drvdata(dev);

	अगर (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_prepare_enable(bgp->fघड़ी);

	ti_bandgap_घातer(bgp, true);
	bgp->is_suspended = false;

	वापस ti_bandgap_restore_ctxt(bgp);
पूर्ण
अटल SIMPLE_DEV_PM_OPS(ti_bandgap_dev_pm_ops, ti_bandgap_suspend,
			 ti_bandgap_resume);

#घोषणा DEV_PM_OPS	(&ti_bandgap_dev_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id of_ti_bandgap_match[] = अणु
#अगर_घोषित CONFIG_OMAP3_THERMAL
	अणु
		.compatible = "ti,omap34xx-bandgap",
		.data = (व्योम *)&omap34xx_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap36xx-bandgap",
		.data = (व्योम *)&omap36xx_data,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP4_THERMAL
	अणु
		.compatible = "ti,omap4430-bandgap",
		.data = (व्योम *)&omap4430_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap4460-bandgap",
		.data = (व्योम *)&omap4460_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap4470-bandgap",
		.data = (व्योम *)&omap4470_data,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP5_THERMAL
	अणु
		.compatible = "ti,omap5430-bandgap",
		.data = (व्योम *)&omap5430_data,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRA752_THERMAL
	अणु
		.compatible = "ti,dra752-bandgap",
		.data = (व्योम *)&dra752_data,
	पूर्ण,
#पूर्ण_अगर
	/* Sentinel */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ti_bandgap_match);

अटल काष्ठा platक्रमm_driver ti_bandgap_sensor_driver = अणु
	.probe = ti_bandgap_probe,
	.हटाओ = ti_bandgap_हटाओ,
	.driver = अणु
			.name = "ti-soc-thermal",
			.pm = DEV_PM_OPS,
			.of_match_table	= of_ti_bandgap_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ti_bandgap_sensor_driver);

MODULE_DESCRIPTION("OMAP4+ bandgap temperature sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ti-soc-thermal");
MODULE_AUTHOR("Texas Instrument Inc.");
