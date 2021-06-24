<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm831x-auxadc.c  --  AUXADC क्रम Wolfson WM831x PMICs
 *
 * Copyright 2009-2011 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/irq.h>
#समावेश <linux/mfd/wm831x/auxadc.h>
#समावेश <linux/mfd/wm831x/otp.h>
#समावेश <linux/mfd/wm831x/regulator.h>

काष्ठा wm831x_auxadc_req अणु
	काष्ठा list_head list;
	क्रमागत wm831x_auxadc input;
	पूर्णांक val;
	काष्ठा completion करोne;
पूर्ण;

अटल पूर्णांक wm831x_auxadc_पढ़ो_irq(काष्ठा wm831x *wm831x,
				  क्रमागत wm831x_auxadc input)
अणु
	काष्ठा wm831x_auxadc_req *req;
	पूर्णांक ret;
	bool ena = false;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	init_completion(&req->करोne);
	req->input = input;
	req->val = -ETIMEDOUT;

	mutex_lock(&wm831x->auxadc_lock);

	/* Enqueue the request */
	list_add(&req->list, &wm831x->auxadc_pending);

	ena = !wm831x->auxadc_active;

	अगर (ena) अणु
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
				      WM831X_AUX_ENA, WM831X_AUX_ENA);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "Failed to enable AUXADC: %d\n",
				ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Enable the conversion अगर not alपढ़ोy running */
	अगर (!(wm831x->auxadc_active & (1 << input))) अणु
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_SOURCE,
				      1 << input, 1 << input);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev,
				"Failed to set AUXADC source: %d\n", ret);
			जाओ out;
		पूर्ण

		wm831x->auxadc_active |= 1 << input;
	पूर्ण

	/* We convert at the fastest rate possible */
	अगर (ena) अणु
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_RATE_MASK,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_RATE_MASK);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "Failed to start AUXADC: %d\n",
				ret);
			जाओ out;
		पूर्ण
	पूर्ण

	mutex_unlock(&wm831x->auxadc_lock);

	/* Wait क्रम an पूर्णांकerrupt */
	रुको_क्रम_completion_समयout(&req->करोne, msecs_to_jअगरfies(500));

	mutex_lock(&wm831x->auxadc_lock);
	ret = req->val;

out:
	list_del(&req->list);
	mutex_unlock(&wm831x->auxadc_lock);

	kमुक्त(req);

	वापस ret;
पूर्ण

अटल irqवापस_t wm831x_auxadc_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा wm831x *wm831x = irq_data;
	काष्ठा wm831x_auxadc_req *req;
	पूर्णांक ret, input, val;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_AUXADC_DATA);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev,
			"Failed to read AUXADC data: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	input = ((ret & WM831X_AUX_DATA_SRC_MASK)
		 >> WM831X_AUX_DATA_SRC_SHIFT) - 1;

	अगर (input == 14)
		input = WM831X_AUX_CAL;

	val = ret & WM831X_AUX_DATA_MASK;

	mutex_lock(&wm831x->auxadc_lock);

	/* Disable this conversion, we're about to complete all users */
	wm831x_set_bits(wm831x, WM831X_AUXADC_SOURCE,
			1 << input, 0);
	wm831x->auxadc_active &= ~(1 << input);

	/* Turn off the entire convertor अगर idle */
	अगर (!wm831x->auxadc_active)
		wm831x_reg_ग_लिखो(wm831x, WM831X_AUXADC_CONTROL, 0);

	/* Wake up any thपढ़ोs रुकोing क्रम this request */
	list_क्रम_each_entry(req, &wm831x->auxadc_pending, list) अणु
		अगर (req->input == input) अणु
			req->val = val;
			complete(&req->करोne);
		पूर्ण
	पूर्ण

	mutex_unlock(&wm831x->auxadc_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm831x_auxadc_पढ़ो_polled(काष्ठा wm831x *wm831x,
				     क्रमागत wm831x_auxadc input)
अणु
	पूर्णांक ret, src, समयout;

	mutex_lock(&wm831x->auxadc_lock);

	ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
			      WM831X_AUX_ENA, WM831X_AUX_ENA);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to enable AUXADC: %d\n", ret);
		जाओ out;
	पूर्ण

	/* We क्रमce a single source at present */
	src = input;
	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_AUXADC_SOURCE,
			       1 << src);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to set AUXADC source: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
			      WM831X_AUX_CVT_ENA, WM831X_AUX_CVT_ENA);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to start AUXADC: %d\n", ret);
		जाओ disable;
	पूर्ण

	/* If we're not using पूर्णांकerrupts then poll the
	 * पूर्णांकerrupt status रेजिस्टर */
	समयout = 5;
	जबतक (समयout) अणु
		msleep(1);

		ret = wm831x_reg_पढ़ो(wm831x,
				      WM831X_INTERRUPT_STATUS_1);
		अगर (ret < 0) अणु
			dev_err(wm831x->dev,
				"ISR 1 read failed: %d\n", ret);
			जाओ disable;
		पूर्ण

		/* Did it complete? */
		अगर (ret & WM831X_AUXADC_DATA_EINT) अणु
			wm831x_reg_ग_लिखो(wm831x,
					 WM831X_INTERRUPT_STATUS_1,
					 WM831X_AUXADC_DATA_EINT);
			अवरोध;
		पूर्ण अन्यथा अणु
			dev_err(wm831x->dev,
				"AUXADC conversion timeout\n");
			ret = -EBUSY;
			जाओ disable;
		पूर्ण
	पूर्ण

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_AUXADC_DATA);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev,
			"Failed to read AUXADC data: %d\n", ret);
		जाओ disable;
	पूर्ण

	src = ((ret & WM831X_AUX_DATA_SRC_MASK)
	       >> WM831X_AUX_DATA_SRC_SHIFT) - 1;

	अगर (src == 14)
		src = WM831X_AUX_CAL;

	अगर (src != input) अणु
		dev_err(wm831x->dev, "Data from source %d not %d\n",
			src, input);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret &= WM831X_AUX_DATA_MASK;
	पूर्ण

disable:
	wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL, WM831X_AUX_ENA, 0);
out:
	mutex_unlock(&wm831x->auxadc_lock);
	वापस ret;
पूर्ण

/**
 * wm831x_auxadc_पढ़ो: Read a value from the WM831x AUXADC
 *
 * @wm831x: Device to पढ़ो from.
 * @input: AUXADC input to पढ़ो.
 */
पूर्णांक wm831x_auxadc_पढ़ो(काष्ठा wm831x *wm831x, क्रमागत wm831x_auxadc input)
अणु
	वापस wm831x->auxadc_पढ़ो(wm831x, input);
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_auxadc_पढ़ो);

/**
 * wm831x_auxadc_पढ़ो_uv: Read a voltage from the WM831x AUXADC
 *
 * @wm831x: Device to पढ़ो from.
 * @input: AUXADC input to पढ़ो.
 */
पूर्णांक wm831x_auxadc_पढ़ो_uv(काष्ठा wm831x *wm831x, क्रमागत wm831x_auxadc input)
अणु
	पूर्णांक ret;

	ret = wm831x_auxadc_पढ़ो(wm831x, input);
	अगर (ret < 0)
		वापस ret;

	ret *= 1465;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_auxadc_पढ़ो_uv);

व्योम wm831x_auxadc_init(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक ret;

	mutex_init(&wm831x->auxadc_lock);
	INIT_LIST_HEAD(&wm831x->auxadc_pending);

	अगर (wm831x->irq) अणु
		wm831x->auxadc_पढ़ो = wm831x_auxadc_पढ़ो_irq;

		ret = request_thपढ़ोed_irq(wm831x_irq(wm831x,
						      WM831X_IRQ_AUXADC_DATA),
					   शून्य, wm831x_auxadc_irq,
					   IRQF_ONESHOT,
					   "auxadc", wm831x);
		अगर (ret < 0) अणु
			dev_err(wm831x->dev, "AUXADC IRQ request failed: %d\n",
				ret);
			wm831x->auxadc_पढ़ो = शून्य;
		पूर्ण
	पूर्ण

	अगर (!wm831x->auxadc_पढ़ो)
		wm831x->auxadc_पढ़ो = wm831x_auxadc_पढ़ो_polled;
पूर्ण
