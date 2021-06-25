<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 ADC Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte, Andy Green and Werner Almesberger
 *
 *  NOTE: This driver करोes not yet support subtractive ADC mode, which means
 *  you can करो only one measurement per पढ़ो request.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/adc.h>

काष्ठा pcf50633_adc_request अणु
	पूर्णांक mux;
	पूर्णांक avg;
	व्योम (*callback)(काष्ठा pcf50633 *, व्योम *, पूर्णांक);
	व्योम *callback_param;
पूर्ण;

काष्ठा pcf50633_adc_sync_request अणु
	पूर्णांक result;
	काष्ठा completion completion;
पूर्ण;

#घोषणा PCF50633_MAX_ADC_FIFO_DEPTH 8

काष्ठा pcf50633_adc अणु
	काष्ठा pcf50633 *pcf;

	/* Private stuff */
	काष्ठा pcf50633_adc_request *queue[PCF50633_MAX_ADC_FIFO_DEPTH];
	पूर्णांक queue_head;
	पूर्णांक queue_tail;
	काष्ठा mutex queue_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा pcf50633_adc *__to_adc(काष्ठा pcf50633 *pcf)
अणु
	वापस platक्रमm_get_drvdata(pcf->adc_pdev);
पूर्ण

अटल व्योम adc_setup(काष्ठा pcf50633 *pcf, पूर्णांक channel, पूर्णांक avg)
अणु
	channel &= PCF50633_ADCC1_ADCMUX_MASK;

	/* समाप्त ratiometric, but enable ACCSW biasing */
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_ADCC2, 0x00);
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_ADCC3, 0x01);

	/* start ADC conversion on selected channel */
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_ADCC1, channel | avg |
		    PCF50633_ADCC1_ADCSTART | PCF50633_ADCC1_RES_10BIT);
पूर्ण

अटल व्योम trigger_next_adc_job_अगर_any(काष्ठा pcf50633 *pcf)
अणु
	काष्ठा pcf50633_adc *adc = __to_adc(pcf);
	पूर्णांक head;

	head = adc->queue_head;

	अगर (!adc->queue[head])
		वापस;

	adc_setup(pcf, adc->queue[head]->mux, adc->queue[head]->avg);
पूर्ण

अटल पूर्णांक
adc_enqueue_request(काष्ठा pcf50633 *pcf, काष्ठा pcf50633_adc_request *req)
अणु
	काष्ठा pcf50633_adc *adc = __to_adc(pcf);
	पूर्णांक head, tail;

	mutex_lock(&adc->queue_mutex);

	head = adc->queue_head;
	tail = adc->queue_tail;

	अगर (adc->queue[tail]) अणु
		mutex_unlock(&adc->queue_mutex);
		dev_err(pcf->dev, "ADC queue is full, dropping request\n");
		वापस -EBUSY;
	पूर्ण

	adc->queue[tail] = req;
	अगर (head == tail)
		trigger_next_adc_job_अगर_any(pcf);
	adc->queue_tail = (tail + 1) & (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	mutex_unlock(&adc->queue_mutex);

	वापस 0;
पूर्ण

अटल व्योम pcf50633_adc_sync_पढ़ो_callback(काष्ठा pcf50633 *pcf, व्योम *param,
	पूर्णांक result)
अणु
	काष्ठा pcf50633_adc_sync_request *req = param;

	req->result = result;
	complete(&req->completion);
पूर्ण

पूर्णांक pcf50633_adc_sync_पढ़ो(काष्ठा pcf50633 *pcf, पूर्णांक mux, पूर्णांक avg)
अणु
	काष्ठा pcf50633_adc_sync_request req;
	पूर्णांक ret;

	init_completion(&req.completion);

	ret = pcf50633_adc_async_पढ़ो(pcf, mux, avg,
		pcf50633_adc_sync_पढ़ो_callback, &req);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion(&req.completion);

	वापस req.result;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_adc_sync_पढ़ो);

पूर्णांक pcf50633_adc_async_पढ़ो(काष्ठा pcf50633 *pcf, पूर्णांक mux, पूर्णांक avg,
			     व्योम (*callback)(काष्ठा pcf50633 *, व्योम *, पूर्णांक),
			     व्योम *callback_param)
अणु
	काष्ठा pcf50633_adc_request *req;

	/* req is मुक्तd when the result is पढ़ोy, in पूर्णांकerrupt handler */
	req = kदो_स्मृति(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->mux = mux;
	req->avg = avg;
	req->callback = callback;
	req->callback_param = callback_param;

	वापस adc_enqueue_request(pcf, req);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_adc_async_पढ़ो);

अटल पूर्णांक adc_result(काष्ठा pcf50633 *pcf)
अणु
	u8 adcs1, adcs3;
	u16 result;

	adcs1 = pcf50633_reg_पढ़ो(pcf, PCF50633_REG_ADCS1);
	adcs3 = pcf50633_reg_पढ़ो(pcf, PCF50633_REG_ADCS3);
	result = (adcs1 << 2) | (adcs3 & PCF50633_ADCS3_ADCDAT1L_MASK);

	dev_dbg(pcf->dev, "adc result = %d\n", result);

	वापस result;
पूर्ण

अटल व्योम pcf50633_adc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf50633_adc *adc = data;
	काष्ठा pcf50633 *pcf = adc->pcf;
	काष्ठा pcf50633_adc_request *req;
	पूर्णांक head, res;

	mutex_lock(&adc->queue_mutex);
	head = adc->queue_head;

	req = adc->queue[head];
	अगर (WARN_ON(!req)) अणु
		dev_err(pcf->dev, "pcf50633-adc irq: ADC queue empty!\n");
		mutex_unlock(&adc->queue_mutex);
		वापस;
	पूर्ण
	adc->queue[head] = शून्य;
	adc->queue_head = (head + 1) &
				      (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	res = adc_result(pcf);
	trigger_next_adc_job_अगर_any(pcf);

	mutex_unlock(&adc->queue_mutex);

	req->callback(pcf, req->callback_param, res);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक pcf50633_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_adc *adc;

	adc = devm_kzalloc(&pdev->dev, माप(*adc), GFP_KERNEL);
	अगर (!adc)
		वापस -ENOMEM;

	adc->pcf = dev_to_pcf50633(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, adc);

	pcf50633_रेजिस्टर_irq(adc->pcf, PCF50633_IRQ_ADCRDY,
					pcf50633_adc_irq, adc);

	mutex_init(&adc->queue_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_adc *adc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, head;

	pcf50633_मुक्त_irq(adc->pcf, PCF50633_IRQ_ADCRDY);

	mutex_lock(&adc->queue_mutex);
	head = adc->queue_head;

	अगर (WARN_ON(adc->queue[head]))
		dev_err(adc->pcf->dev,
			"adc driver removed with request pending\n");

	क्रम (i = 0; i < PCF50633_MAX_ADC_FIFO_DEPTH; i++)
		kमुक्त(adc->queue[i]);

	mutex_unlock(&adc->queue_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_adc_driver = अणु
	.driver = अणु
		.name = "pcf50633-adc",
	पूर्ण,
	.probe = pcf50633_adc_probe,
	.हटाओ = pcf50633_adc_हटाओ,
पूर्ण;

module_platक्रमm_driver(pcf50633_adc_driver);

MODULE_AUTHOR("Balaji Rao <balajirrao@openmoko.org>");
MODULE_DESCRIPTION("PCF50633 adc driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcf50633-adc");

