<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Motorola PCAP2 as present in EZX phones
 *
 * Copyright (C) 2006 Harald Welte <laक्रमge@खोलोezx.org>
 * Copyright (C) 2009 Daniel Ribeiro <drwyrm@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/ezx-pcap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#घोषणा PCAP_ADC_MAXQ		8
काष्ठा pcap_adc_request अणु
	u8 bank;
	u8 ch[2];
	u32 flags;
	व्योम (*callback)(व्योम *, u16[]);
	व्योम *data;
पूर्ण;

काष्ठा pcap_adc_sync_request अणु
	u16 res[2];
	काष्ठा completion completion;
पूर्ण;

काष्ठा pcap_chip अणु
	काष्ठा spi_device *spi;

	/* IO */
	u32 buf;
	spinlock_t io_lock;

	/* IRQ */
	अचिन्हित पूर्णांक irq_base;
	u32 msr;
	काष्ठा work_काष्ठा isr_work;
	काष्ठा work_काष्ठा msr_work;
	काष्ठा workqueue_काष्ठा *workqueue;

	/* ADC */
	काष्ठा pcap_adc_request *adc_queue[PCAP_ADC_MAXQ];
	u8 adc_head;
	u8 adc_tail;
	spinlock_t adc_lock;
पूर्ण;

/* IO */
अटल पूर्णांक ezx_pcap_putget(काष्ठा pcap_chip *pcap, u32 *data)
अणु
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;
	पूर्णांक status;

	स_रखो(&t, 0, माप(t));
	spi_message_init(&m);
	t.len = माप(u32);
	spi_message_add_tail(&t, &m);

	pcap->buf = *data;
	t.tx_buf = (u8 *) &pcap->buf;
	t.rx_buf = (u8 *) &pcap->buf;
	status = spi_sync(pcap->spi, &m);

	अगर (status == 0)
		*data = pcap->buf;

	वापस status;
पूर्ण

पूर्णांक ezx_pcap_ग_लिखो(काष्ठा pcap_chip *pcap, u8 reg_num, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&pcap->io_lock, flags);
	value &= PCAP_REGISTER_VALUE_MASK;
	value |= PCAP_REGISTER_WRITE_OP_BIT
		| (reg_num << PCAP_REGISTER_ADDRESS_SHIFT);
	ret = ezx_pcap_putget(pcap, &value);
	spin_unlock_irqrestore(&pcap->io_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ezx_pcap_ग_लिखो);

पूर्णांक ezx_pcap_पढ़ो(काष्ठा pcap_chip *pcap, u8 reg_num, u32 *value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&pcap->io_lock, flags);
	*value = PCAP_REGISTER_READ_OP_BIT
		| (reg_num << PCAP_REGISTER_ADDRESS_SHIFT);

	ret = ezx_pcap_putget(pcap, value);
	spin_unlock_irqrestore(&pcap->io_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ezx_pcap_पढ़ो);

पूर्णांक ezx_pcap_set_bits(काष्ठा pcap_chip *pcap, u8 reg_num, u32 mask, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 पंचांगp = PCAP_REGISTER_READ_OP_BIT |
		(reg_num << PCAP_REGISTER_ADDRESS_SHIFT);

	spin_lock_irqsave(&pcap->io_lock, flags);
	ret = ezx_pcap_putget(pcap, &पंचांगp);
	अगर (ret)
		जाओ out_unlock;

	पंचांगp &= (PCAP_REGISTER_VALUE_MASK & ~mask);
	पंचांगp |= (val & mask) | PCAP_REGISTER_WRITE_OP_BIT |
		(reg_num << PCAP_REGISTER_ADDRESS_SHIFT);

	ret = ezx_pcap_putget(pcap, &पंचांगp);
out_unlock:
	spin_unlock_irqrestore(&pcap->io_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ezx_pcap_set_bits);

/* IRQ */
पूर्णांक irq_to_pcap(काष्ठा pcap_chip *pcap, पूर्णांक irq)
अणु
	वापस irq - pcap->irq_base;
पूर्ण
EXPORT_SYMBOL_GPL(irq_to_pcap);

पूर्णांक pcap_to_irq(काष्ठा pcap_chip *pcap, पूर्णांक irq)
अणु
	वापस pcap->irq_base + irq;
पूर्ण
EXPORT_SYMBOL_GPL(pcap_to_irq);

अटल व्योम pcap_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pcap_chip *pcap = irq_data_get_irq_chip_data(d);

	pcap->msr |= 1 << irq_to_pcap(pcap, d->irq);
	queue_work(pcap->workqueue, &pcap->msr_work);
पूर्ण

अटल व्योम pcap_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pcap_chip *pcap = irq_data_get_irq_chip_data(d);

	pcap->msr &= ~(1 << irq_to_pcap(pcap, d->irq));
	queue_work(pcap->workqueue, &pcap->msr_work);
पूर्ण

अटल काष्ठा irq_chip pcap_irq_chip = अणु
	.name		= "pcap",
	.irq_disable	= pcap_mask_irq,
	.irq_mask	= pcap_mask_irq,
	.irq_unmask	= pcap_unmask_irq,
पूर्ण;

अटल व्योम pcap_msr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcap_chip *pcap = container_of(work, काष्ठा pcap_chip, msr_work);

	ezx_pcap_ग_लिखो(pcap, PCAP_REG_MSR, pcap->msr);
पूर्ण

अटल व्योम pcap_isr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pcap_chip *pcap = container_of(work, काष्ठा pcap_chip, isr_work);
	काष्ठा pcap_platक्रमm_data *pdata = dev_get_platdata(&pcap->spi->dev);
	u32 msr, isr, पूर्णांक_sel, service;
	पूर्णांक irq;

	करो अणु
		ezx_pcap_पढ़ो(pcap, PCAP_REG_MSR, &msr);
		ezx_pcap_पढ़ो(pcap, PCAP_REG_ISR, &isr);

		/* We can't service/ack irqs that are asचिन्हित to port 2 */
		अगर (!(pdata->config & PCAP_SECOND_PORT)) अणु
			ezx_pcap_पढ़ो(pcap, PCAP_REG_INT_SEL, &पूर्णांक_sel);
			isr &= ~पूर्णांक_sel;
		पूर्ण

		ezx_pcap_ग_लिखो(pcap, PCAP_REG_MSR, isr | msr);
		ezx_pcap_ग_लिखो(pcap, PCAP_REG_ISR, isr);

		local_irq_disable();
		service = isr & ~msr;
		क्रम (irq = pcap->irq_base; service; service >>= 1, irq++) अणु
			अगर (service & 1)
				generic_handle_irq(irq);
		पूर्ण
		local_irq_enable();
		ezx_pcap_ग_लिखो(pcap, PCAP_REG_MSR, pcap->msr);
	पूर्ण जबतक (gpio_get_value(pdata->gpio));
पूर्ण

अटल व्योम pcap_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pcap_chip *pcap = irq_desc_get_handler_data(desc);

	desc->irq_data.chip->irq_ack(&desc->irq_data);
	queue_work(pcap->workqueue, &pcap->isr_work);
पूर्ण

/* ADC */
व्योम pcap_set_ts_bits(काष्ठा pcap_chip *pcap, u32 bits)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&pcap->adc_lock, flags);
	ezx_pcap_पढ़ो(pcap, PCAP_REG_ADC, &पंचांगp);
	पंचांगp &= ~(PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	पंचांगp |= bits & (PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ADC, पंचांगp);
	spin_unlock_irqrestore(&pcap->adc_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pcap_set_ts_bits);

अटल व्योम pcap_disable_adc(काष्ठा pcap_chip *pcap)
अणु
	u32 पंचांगp;

	ezx_pcap_पढ़ो(pcap, PCAP_REG_ADC, &पंचांगp);
	पंचांगp &= ~(PCAP_ADC_ADEN|PCAP_ADC_BATT_I_ADC|PCAP_ADC_BATT_I_POLARITY);
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ADC, पंचांगp);
पूर्ण

अटल व्योम pcap_adc_trigger(काष्ठा pcap_chip *pcap)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;
	u8 head;

	spin_lock_irqsave(&pcap->adc_lock, flags);
	head = pcap->adc_head;
	अगर (!pcap->adc_queue[head]) अणु
		/* queue is empty, save घातer */
		pcap_disable_adc(pcap);
		spin_unlock_irqrestore(&pcap->adc_lock, flags);
		वापस;
	पूर्ण
	/* start conversion on requested bank, save TS_M bits */
	ezx_pcap_पढ़ो(pcap, PCAP_REG_ADC, &पंचांगp);
	पंचांगp &= (PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	पंचांगp |= pcap->adc_queue[head]->flags | PCAP_ADC_ADEN;

	अगर (pcap->adc_queue[head]->bank == PCAP_ADC_BANK_1)
		पंचांगp |= PCAP_ADC_AD_SEL1;

	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ADC, पंचांगp);
	spin_unlock_irqrestore(&pcap->adc_lock, flags);
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ADR, PCAP_ADR_ASC);
पूर्ण

अटल irqवापस_t pcap_adc_irq(पूर्णांक irq, व्योम *_pcap)
अणु
	काष्ठा pcap_chip *pcap = _pcap;
	काष्ठा pcap_adc_request *req;
	u16 res[2];
	u32 पंचांगp;

	spin_lock(&pcap->adc_lock);
	req = pcap->adc_queue[pcap->adc_head];

	अगर (WARN(!req, "adc irq without pending request\n")) अणु
		spin_unlock(&pcap->adc_lock);
		वापस IRQ_HANDLED;
	पूर्ण

	/* पढ़ो requested channels results */
	ezx_pcap_पढ़ो(pcap, PCAP_REG_ADC, &पंचांगp);
	पंचांगp &= ~(PCAP_ADC_ADA1_MASK | PCAP_ADC_ADA2_MASK);
	पंचांगp |= (req->ch[0] << PCAP_ADC_ADA1_SHIFT);
	पंचांगp |= (req->ch[1] << PCAP_ADC_ADA2_SHIFT);
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ADC, पंचांगp);
	ezx_pcap_पढ़ो(pcap, PCAP_REG_ADR, &पंचांगp);
	res[0] = (पंचांगp & PCAP_ADR_ADD1_MASK) >> PCAP_ADR_ADD1_SHIFT;
	res[1] = (पंचांगp & PCAP_ADR_ADD2_MASK) >> PCAP_ADR_ADD2_SHIFT;

	pcap->adc_queue[pcap->adc_head] = शून्य;
	pcap->adc_head = (pcap->adc_head + 1) & (PCAP_ADC_MAXQ - 1);
	spin_unlock(&pcap->adc_lock);

	/* pass the results and release memory */
	req->callback(req->data, res);
	kमुक्त(req);

	/* trigger next conversion (अगर any) on queue */
	pcap_adc_trigger(pcap);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक pcap_adc_async(काष्ठा pcap_chip *pcap, u8 bank, u32 flags, u8 ch[],
						व्योम *callback, व्योम *data)
अणु
	काष्ठा pcap_adc_request *req;
	अचिन्हित दीर्घ irq_flags;

	/* This will be मुक्तd after we have a result */
	req = kदो_स्मृति(माप(काष्ठा pcap_adc_request), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->bank = bank;
	req->flags = flags;
	req->ch[0] = ch[0];
	req->ch[1] = ch[1];
	req->callback = callback;
	req->data = data;

	spin_lock_irqsave(&pcap->adc_lock, irq_flags);
	अगर (pcap->adc_queue[pcap->adc_tail]) अणु
		spin_unlock_irqrestore(&pcap->adc_lock, irq_flags);
		kमुक्त(req);
		वापस -EBUSY;
	पूर्ण
	pcap->adc_queue[pcap->adc_tail] = req;
	pcap->adc_tail = (pcap->adc_tail + 1) & (PCAP_ADC_MAXQ - 1);
	spin_unlock_irqrestore(&pcap->adc_lock, irq_flags);

	/* start conversion */
	pcap_adc_trigger(pcap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcap_adc_async);

अटल व्योम pcap_adc_sync_cb(व्योम *param, u16 res[])
अणु
	काष्ठा pcap_adc_sync_request *req = param;

	req->res[0] = res[0];
	req->res[1] = res[1];
	complete(&req->completion);
पूर्ण

पूर्णांक pcap_adc_sync(काष्ठा pcap_chip *pcap, u8 bank, u32 flags, u8 ch[],
								u16 res[])
अणु
	काष्ठा pcap_adc_sync_request sync_data;
	पूर्णांक ret;

	init_completion(&sync_data.completion);
	ret = pcap_adc_async(pcap, bank, flags, ch, pcap_adc_sync_cb,
								&sync_data);
	अगर (ret)
		वापस ret;
	रुको_क्रम_completion(&sync_data.completion);
	res[0] = sync_data.res[0];
	res[1] = sync_data.res[1];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcap_adc_sync);

/* subdevs */
अटल पूर्णांक pcap_हटाओ_subdev(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक pcap_add_subdev(काष्ठा pcap_chip *pcap,
						काष्ठा pcap_subdev *subdev)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(subdev->name, subdev->id);
	अगर (!pdev)
		वापस -ENOMEM;

	pdev->dev.parent = &pcap->spi->dev;
	pdev->dev.platक्रमm_data = subdev->platक्रमm_data;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक ezx_pcap_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा pcap_chip *pcap = spi_get_drvdata(spi);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* हटाओ all रेजिस्टरed subdevs */
	device_क्रम_each_child(&spi->dev, शून्य, pcap_हटाओ_subdev);

	/* cleanup ADC */
	spin_lock_irqsave(&pcap->adc_lock, flags);
	क्रम (i = 0; i < PCAP_ADC_MAXQ; i++)
		kमुक्त(pcap->adc_queue[i]);
	spin_unlock_irqrestore(&pcap->adc_lock, flags);

	/* cleanup irqchip */
	क्रम (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++)
		irq_set_chip_and_handler(i, शून्य, शून्य);

	destroy_workqueue(pcap->workqueue);

	वापस 0;
पूर्ण

अटल पूर्णांक ezx_pcap_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा pcap_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा pcap_chip *pcap;
	पूर्णांक i, adc_irq;
	पूर्णांक ret = -ENODEV;

	/* platक्रमm data is required */
	अगर (!pdata)
		जाओ ret;

	pcap = devm_kzalloc(&spi->dev, माप(*pcap), GFP_KERNEL);
	अगर (!pcap) अणु
		ret = -ENOMEM;
		जाओ ret;
	पूर्ण

	spin_lock_init(&pcap->io_lock);
	spin_lock_init(&pcap->adc_lock);
	INIT_WORK(&pcap->isr_work, pcap_isr_work);
	INIT_WORK(&pcap->msr_work, pcap_msr_work);
	spi_set_drvdata(spi, pcap);

	/* setup spi */
	spi->bits_per_word = 32;
	spi->mode = SPI_MODE_0 | (pdata->config & PCAP_CS_AH ? SPI_CS_HIGH : 0);
	ret = spi_setup(spi);
	अगर (ret)
		जाओ ret;

	pcap->spi = spi;

	/* setup irq */
	pcap->irq_base = pdata->irq_base;
	pcap->workqueue = create_singlethपढ़ो_workqueue("pcapd");
	अगर (!pcap->workqueue) अणु
		ret = -ENOMEM;
		dev_err(&spi->dev, "can't create pcap thread\n");
		जाओ ret;
	पूर्ण

	/* redirect पूर्णांकerrupts to AP, except adcकरोne2 */
	अगर (!(pdata->config & PCAP_SECOND_PORT))
		ezx_pcap_ग_लिखो(pcap, PCAP_REG_INT_SEL,
					(1 << PCAP_IRQ_ADCDONE2));

	/* setup irq chip */
	क्रम (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++) अणु
		irq_set_chip_and_handler(i, &pcap_irq_chip, handle_simple_irq);
		irq_set_chip_data(i, pcap);
		irq_clear_status_flags(i, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	/* mask/ack all PCAP पूर्णांकerrupts */
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_MSR, PCAP_MASK_ALL_INTERRUPT);
	ezx_pcap_ग_लिखो(pcap, PCAP_REG_ISR, PCAP_CLEAR_INTERRUPT_REGISTER);
	pcap->msr = PCAP_MASK_ALL_INTERRUPT;

	irq_set_irq_type(spi->irq, IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler_and_data(spi->irq, pcap_irq_handler, pcap);
	irq_set_irq_wake(spi->irq, 1);

	/* ADC */
	adc_irq = pcap_to_irq(pcap, (pdata->config & PCAP_SECOND_PORT) ?
					PCAP_IRQ_ADCDONE2 : PCAP_IRQ_ADCDONE);

	ret = devm_request_irq(&spi->dev, adc_irq, pcap_adc_irq, 0, "ADC",
				pcap);
	अगर (ret)
		जाओ मुक्त_irqchip;

	/* setup subdevs */
	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु
		ret = pcap_add_subdev(pcap, &pdata->subdevs[i]);
		अगर (ret)
			जाओ हटाओ_subdevs;
	पूर्ण

	/* board specअगरic quirks */
	अगर (pdata->init)
		pdata->init(pcap);

	वापस 0;

हटाओ_subdevs:
	device_क्रम_each_child(&spi->dev, शून्य, pcap_हटाओ_subdev);
मुक्त_irqchip:
	क्रम (i = pcap->irq_base; i < (pcap->irq_base + PCAP_NIRQS); i++)
		irq_set_chip_and_handler(i, शून्य, शून्य);
/* destroy_workqueue: */
	destroy_workqueue(pcap->workqueue);
ret:
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver ezxpcap_driver = अणु
	.probe	= ezx_pcap_probe,
	.हटाओ = ezx_pcap_हटाओ,
	.driver = अणु
		.name	= "ezx-pcap",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ezx_pcap_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&ezxpcap_driver);
पूर्ण

अटल व्योम __निकास ezx_pcap_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&ezxpcap_driver);
पूर्ण

subsys_initcall(ezx_pcap_init);
module_निकास(ezx_pcap_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Ribeiro / Harald Welte");
MODULE_DESCRIPTION("Motorola PCAP2 ASIC Driver");
MODULE_ALIAS("spi:ezx-pcap");
