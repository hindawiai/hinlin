<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
//
// Copyright (c) 2008 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>, <ben-linux@fluff.org>
//
// Samsung ADC device core

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/consumer.h>

#समावेश "regs-adc.h"
#समावेश <linux/soc/samsung/s3c-adc.h>

/* This driver is deचिन्हित to control the usage of the ADC block between
 * the touchscreen and any other drivers that may need to use it, such as
 * the hwmon driver.
 *
 * Priority will be given to the touchscreen driver, but as this itself is
 * rate limited it should not starve other requests which are processed in
 * order that they are received.
 *
 * Each user रेजिस्टरs to get a client block which uniquely identअगरies it
 * and stores inक्रमmation such as the necessary functions to callback when
 * action is required.
 */

क्रमागत s3c_cpu_type अणु
	TYPE_ADCV1, /* S3C24XX */
	TYPE_ADCV11, /* S3C2443 */
	TYPE_ADCV12, /* S3C2416, S3C2450 */
	TYPE_ADCV2, /* S3C64XX */
	TYPE_ADCV3, /* S5PV210, S5PC110, Exynos4210 */
पूर्ण;

काष्ठा s3c_adc_client अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा list_head	 pend;
	रुको_queue_head_t	*रुको;

	अचिन्हित पूर्णांक		 nr_samples;
	पूर्णांक			 result;
	अचिन्हित अक्षर		 is_ts;
	अचिन्हित अक्षर		 channel;

	व्योम	(*select_cb)(काष्ठा s3c_adc_client *c, अचिन्हित selected);
	व्योम	(*convert_cb)(काष्ठा s3c_adc_client *c,
			      अचिन्हित val1, अचिन्हित val2,
			      अचिन्हित *samples_left);
पूर्ण;

काष्ठा adc_device अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा platक्रमm_device	*owner;
	काष्ठा clk		*clk;
	काष्ठा s3c_adc_client	*cur;
	काष्ठा s3c_adc_client	*ts_pend;
	व्योम __iomem		*regs;
	spinlock_t		 lock;

	अचिन्हित पूर्णांक		 prescale;

	पूर्णांक			 irq;
	काष्ठा regulator	*vdd;
पूर्ण;

अटल काष्ठा adc_device *adc_dev;

अटल LIST_HEAD(adc_pending);	/* रक्षित by adc_device.lock */

#घोषणा adc_dbg(_adc, msg...) dev_dbg(&(_adc)->pdev->dev, msg)

अटल अंतरभूत व्योम s3c_adc_convert(काष्ठा adc_device *adc)
अणु
	अचिन्हित con = पढ़ोl(adc->regs + S3C2410_ADCCON);

	con |= S3C2410_ADCCON_ENABLE_START;
	ग_लिखोl(con, adc->regs + S3C2410_ADCCON);
पूर्ण

अटल अंतरभूत व्योम s3c_adc_select(काष्ठा adc_device *adc,
				  काष्ठा s3c_adc_client *client)
अणु
	अचिन्हित con = पढ़ोl(adc->regs + S3C2410_ADCCON);
	क्रमागत s3c_cpu_type cpu = platक्रमm_get_device_id(adc->pdev)->driver_data;

	client->select_cb(client, 1);

	अगर (cpu == TYPE_ADCV1 || cpu == TYPE_ADCV2)
		con &= ~S3C2410_ADCCON_MUXMASK;
	con &= ~S3C2410_ADCCON_STDBM;
	con &= ~S3C2410_ADCCON_STARTMASK;

	अगर (!client->is_ts) अणु
		अगर (cpu == TYPE_ADCV3)
			ग_लिखोl(client->channel & 0xf, adc->regs + S5P_ADCMUX);
		अन्यथा अगर (cpu == TYPE_ADCV11 || cpu == TYPE_ADCV12)
			ग_लिखोl(client->channel & 0xf,
						adc->regs + S3C2443_ADCMUX);
		अन्यथा
			con |= S3C2410_ADCCON_SELMUX(client->channel);
	पूर्ण

	ग_लिखोl(con, adc->regs + S3C2410_ADCCON);
पूर्ण

अटल व्योम s3c_adc_dbgshow(काष्ठा adc_device *adc)
अणु
	adc_dbg(adc, "CON=%08x, TSC=%08x, DLY=%08x\n",
		पढ़ोl(adc->regs + S3C2410_ADCCON),
		पढ़ोl(adc->regs + S3C2410_ADCTSC),
		पढ़ोl(adc->regs + S3C2410_ADCDLY));
पूर्ण

अटल व्योम s3c_adc_try(काष्ठा adc_device *adc)
अणु
	काष्ठा s3c_adc_client *next = adc->ts_pend;

	अगर (!next && !list_empty(&adc_pending)) अणु
		next = list_first_entry(&adc_pending,
					काष्ठा s3c_adc_client, pend);
		list_del(&next->pend);
	पूर्ण अन्यथा
		adc->ts_pend = शून्य;

	अगर (next) अणु
		adc_dbg(adc, "new client is %p\n", next);
		adc->cur = next;
		s3c_adc_select(adc, next);
		s3c_adc_convert(adc);
		s3c_adc_dbgshow(adc);
	पूर्ण
पूर्ण

पूर्णांक s3c_adc_start(काष्ठा s3c_adc_client *client,
		  अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक nr_samples)
अणु
	काष्ठा adc_device *adc = adc_dev;
	अचिन्हित दीर्घ flags;

	अगर (!adc) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to find adc\n", __func__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&adc->lock, flags);

	अगर (client->is_ts && adc->ts_pend) अणु
		spin_unlock_irqrestore(&adc->lock, flags);
		वापस -EAGAIN;
	पूर्ण

	client->channel = channel;
	client->nr_samples = nr_samples;

	अगर (client->is_ts)
		adc->ts_pend = client;
	अन्यथा
		list_add_tail(&client->pend, &adc_pending);

	अगर (!adc->cur)
		s3c_adc_try(adc);

	spin_unlock_irqrestore(&adc->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_adc_start);

अटल व्योम s3c_convert_करोne(काष्ठा s3c_adc_client *client,
			     अचिन्हित v, अचिन्हित u, अचिन्हित *left)
अणु
	client->result = v;
	wake_up(client->रुको);
पूर्ण

पूर्णांक s3c_adc_पढ़ो(काष्ठा s3c_adc_client *client, अचिन्हित पूर्णांक ch)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wake);
	पूर्णांक ret;

	client->convert_cb = s3c_convert_करोne;
	client->रुको = &wake;
	client->result = -1;

	ret = s3c_adc_start(client, ch, 1);
	अगर (ret < 0)
		जाओ err;

	ret = रुको_event_समयout(wake, client->result >= 0, HZ / 2);
	अगर (client->result < 0) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	client->convert_cb = शून्य;
	वापस client->result;

err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_adc_पढ़ो);

अटल व्योम s3c_adc_शेष_select(काष्ठा s3c_adc_client *client,
				   अचिन्हित select)
अणु
पूर्ण

काष्ठा s3c_adc_client *s3c_adc_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					व्योम (*select)(काष्ठा s3c_adc_client *client,
						       अचिन्हित पूर्णांक selected),
					व्योम (*conv)(काष्ठा s3c_adc_client *client,
						     अचिन्हित d0, अचिन्हित d1,
						     अचिन्हित *samples_left),
					अचिन्हित पूर्णांक is_ts)
अणु
	काष्ठा s3c_adc_client *client;

	WARN_ON(!pdev);

	अगर (!select)
		select = s3c_adc_शेष_select;

	अगर (!pdev)
		वापस ERR_PTR(-EINVAL);

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस ERR_PTR(-ENOMEM);

	client->pdev = pdev;
	client->is_ts = is_ts;
	client->select_cb = select;
	client->convert_cb = conv;

	वापस client;
पूर्ण
EXPORT_SYMBOL_GPL(s3c_adc_रेजिस्टर);

व्योम s3c_adc_release(काष्ठा s3c_adc_client *client)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adc_dev->lock, flags);

	/* We should really check that nothing is in progress. */
	अगर (adc_dev->cur == client)
		adc_dev->cur = शून्य;
	अगर (adc_dev->ts_pend == client)
		adc_dev->ts_pend = शून्य;
	अन्यथा अणु
		काष्ठा list_head *p, *n;
		काष्ठा s3c_adc_client *पंचांगp;

		list_क्रम_each_safe(p, n, &adc_pending) अणु
			पंचांगp = list_entry(p, काष्ठा s3c_adc_client, pend);
			अगर (पंचांगp == client)
				list_del(&पंचांगp->pend);
		पूर्ण
	पूर्ण

	अगर (adc_dev->cur == शून्य)
		s3c_adc_try(adc_dev);

	spin_unlock_irqrestore(&adc_dev->lock, flags);
	kमुक्त(client);
पूर्ण
EXPORT_SYMBOL_GPL(s3c_adc_release);

अटल irqवापस_t s3c_adc_irq(पूर्णांक irq, व्योम *pw)
अणु
	काष्ठा adc_device *adc = pw;
	काष्ठा s3c_adc_client *client = adc->cur;
	क्रमागत s3c_cpu_type cpu = platक्रमm_get_device_id(adc->pdev)->driver_data;
	अचिन्हित data0, data1;

	अगर (!client) अणु
		dev_warn(&adc->pdev->dev, "%s: no adc pending\n", __func__);
		जाओ निकास;
	पूर्ण

	data0 = पढ़ोl(adc->regs + S3C2410_ADCDAT0);
	data1 = पढ़ोl(adc->regs + S3C2410_ADCDAT1);
	adc_dbg(adc, "read %d: 0x%04x, 0x%04x\n", client->nr_samples, data0, data1);

	client->nr_samples--;

	अगर (cpu == TYPE_ADCV1 || cpu == TYPE_ADCV11) अणु
		data0 &= 0x3ff;
		data1 &= 0x3ff;
	पूर्ण अन्यथा अणु
		/* S3C2416/S3C64XX/S5P ADC resolution is 12-bit */
		data0 &= 0xfff;
		data1 &= 0xfff;
	पूर्ण

	अगर (client->convert_cb)
		(client->convert_cb)(client, data0, data1, &client->nr_samples);

	अगर (client->nr_samples > 0) अणु
		/* fire another conversion क्रम this */

		client->select_cb(client, 1);
		s3c_adc_convert(adc);
	पूर्ण अन्यथा अणु
		spin_lock(&adc->lock);
		(client->select_cb)(client, 0);
		adc->cur = शून्य;

		s3c_adc_try(adc);
		spin_unlock(&adc->lock);
	पूर्ण

निकास:
	अगर (cpu == TYPE_ADCV2 || cpu == TYPE_ADCV3) अणु
		/* Clear ADC पूर्णांकerrupt */
		ग_लिखोl(0, adc->regs + S3C64XX_ADCCLRINT);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s3c_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा adc_device *adc;
	क्रमागत s3c_cpu_type cpu = platक्रमm_get_device_id(pdev)->driver_data;
	पूर्णांक ret;
	अचिन्हित पंचांगp;

	adc = devm_kzalloc(dev, माप(*adc), GFP_KERNEL);
	अगर (!adc)
		वापस -ENOMEM;

	spin_lock_init(&adc->lock);

	adc->pdev = pdev;
	adc->prescale = S3C2410_ADCCON_PRSCVL(49);

	adc->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(adc->vdd)) अणु
		dev_err(dev, "operating without regulator \"vdd\" .\n");
		वापस PTR_ERR(adc->vdd);
	पूर्ण

	adc->irq = platक्रमm_get_irq(pdev, 1);
	अगर (adc->irq <= 0)
		वापस -ENOENT;

	ret = devm_request_irq(dev, adc->irq, s3c_adc_irq, 0, dev_name(dev),
				adc);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to attach adc irq\n");
		वापस ret;
	पूर्ण

	adc->clk = devm_clk_get(dev, "adc");
	अगर (IS_ERR(adc->clk)) अणु
		dev_err(dev, "failed to get adc clock\n");
		वापस PTR_ERR(adc->clk);
	पूर्ण

	adc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adc->regs))
		वापस PTR_ERR(adc->regs);

	ret = regulator_enable(adc->vdd);
	अगर (ret)
		वापस ret;

	clk_prepare_enable(adc->clk);

	पंचांगp = adc->prescale | S3C2410_ADCCON_PRSCEN;

	/* Enable 12-bit ADC resolution */
	अगर (cpu == TYPE_ADCV12)
		पंचांगp |= S3C2416_ADCCON_RESSEL;
	अगर (cpu == TYPE_ADCV2 || cpu == TYPE_ADCV3)
		पंचांगp |= S3C64XX_ADCCON_RESSEL;

	ग_लिखोl(पंचांगp, adc->regs + S3C2410_ADCCON);

	dev_info(dev, "attached adc driver\n");

	platक्रमm_set_drvdata(pdev, adc);
	adc_dev = adc;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adc_device *adc = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(adc->clk);
	regulator_disable(adc->vdd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा adc_device *adc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 con;

	spin_lock_irqsave(&adc->lock, flags);

	con = पढ़ोl(adc->regs + S3C2410_ADCCON);
	con |= S3C2410_ADCCON_STDBM;
	ग_लिखोl(con, adc->regs + S3C2410_ADCCON);

	disable_irq(adc->irq);
	spin_unlock_irqrestore(&adc->lock, flags);
	clk_disable(adc->clk);
	regulator_disable(adc->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा adc_device *adc = platक्रमm_get_drvdata(pdev);
	क्रमागत s3c_cpu_type cpu = platक्रमm_get_device_id(pdev)->driver_data;
	पूर्णांक ret;
	अचिन्हित दीर्घ पंचांगp;

	ret = regulator_enable(adc->vdd);
	अगर (ret)
		वापस ret;
	clk_enable(adc->clk);
	enable_irq(adc->irq);

	पंचांगp = adc->prescale | S3C2410_ADCCON_PRSCEN;

	/* Enable 12-bit ADC resolution */
	अगर (cpu == TYPE_ADCV12)
		पंचांगp |= S3C2416_ADCCON_RESSEL;
	अगर (cpu == TYPE_ADCV2 || cpu == TYPE_ADCV3)
		पंचांगp |= S3C64XX_ADCCON_RESSEL;

	ग_लिखोl(पंचांगp, adc->regs + S3C2410_ADCCON);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा s3c_adc_suspend शून्य
#घोषणा s3c_adc_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id s3c_adc_driver_ids[] = अणु
	अणु
		.name           = "s3c24xx-adc",
		.driver_data    = TYPE_ADCV1,
	पूर्ण, अणु
		.name		= "s3c2443-adc",
		.driver_data	= TYPE_ADCV11,
	पूर्ण, अणु
		.name		= "s3c2416-adc",
		.driver_data	= TYPE_ADCV12,
	पूर्ण, अणु
		.name           = "s3c64xx-adc",
		.driver_data    = TYPE_ADCV2,
	पूर्ण, अणु
		.name		= "samsung-adc-v3",
		.driver_data	= TYPE_ADCV3,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c_adc_driver_ids);

अटल स्थिर काष्ठा dev_pm_ops adc_pm_ops = अणु
	.suspend	= s3c_adc_suspend,
	.resume		= s3c_adc_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver s3c_adc_driver = अणु
	.id_table	= s3c_adc_driver_ids,
	.driver		= अणु
		.name	= "s3c-adc",
		.pm	= &adc_pm_ops,
	पूर्ण,
	.probe		= s3c_adc_probe,
	.हटाओ		= s3c_adc_हटाओ,
पूर्ण;

अटल पूर्णांक __init adc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&s3c_adc_driver);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "%s: failed to add adc driver\n", __func__);

	वापस ret;
पूर्ण

module_init(adc_init);
