<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017 Google Inc
 *
 * Provides a simple driver to control the ASPEED LPC snoop पूर्णांकerface which
 * allows the BMC to listen on and save the data written by
 * the host to an arbitrary LPC I/O port.
 *
 * Typically used by the BMC to "watch" host boot progress via port
 * 0x80 ग_लिखोs made by the BIOS during the boot process.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/regmap.h>

#घोषणा DEVICE_NAME	"aspeed-lpc-snoop"

#घोषणा NUM_SNOOP_CHANNELS 2
#घोषणा SNOOP_FIFO_SIZE 2048

#घोषणा HICR5	0x80
#घोषणा HICR5_EN_SNP0W		BIT(0)
#घोषणा HICR5_ENINT_SNP0W	BIT(1)
#घोषणा HICR5_EN_SNP1W		BIT(2)
#घोषणा HICR5_ENINT_SNP1W	BIT(3)
#घोषणा HICR6	0x84
#घोषणा HICR6_STR_SNP0W		BIT(0)
#घोषणा HICR6_STR_SNP1W		BIT(1)
#घोषणा SNPWADR	0x90
#घोषणा SNPWADR_CH0_MASK	GENMASK(15, 0)
#घोषणा SNPWADR_CH0_SHIFT	0
#घोषणा SNPWADR_CH1_MASK	GENMASK(31, 16)
#घोषणा SNPWADR_CH1_SHIFT	16
#घोषणा SNPWDR	0x94
#घोषणा SNPWDR_CH0_MASK		GENMASK(7, 0)
#घोषणा SNPWDR_CH0_SHIFT	0
#घोषणा SNPWDR_CH1_MASK		GENMASK(15, 8)
#घोषणा SNPWDR_CH1_SHIFT	8
#घोषणा HICRB	0x100
#घोषणा HICRB_ENSNP0D		BIT(14)
#घोषणा HICRB_ENSNP1D		BIT(15)

काष्ठा aspeed_lpc_snoop_model_data अणु
	/* The ast2400 has bits 14 and 15 as reserved, whereas the ast2500
	 * can use them.
	 */
	अचिन्हित पूर्णांक has_hicrb_ensnp;
पूर्ण;

काष्ठा aspeed_lpc_snoop_channel अणु
	काष्ठा kfअगरo		fअगरo;
	रुको_queue_head_t	wq;
	काष्ठा miscdevice	miscdev;
पूर्ण;

काष्ठा aspeed_lpc_snoop अणु
	काष्ठा regmap		*regmap;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	काष्ठा aspeed_lpc_snoop_channel chan[NUM_SNOOP_CHANNELS];
पूर्ण;

अटल काष्ठा aspeed_lpc_snoop_channel *snoop_file_to_chan(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data,
			    काष्ठा aspeed_lpc_snoop_channel,
			    miscdev);
पूर्ण

अटल sमाप_प्रकार snoop_file_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा aspeed_lpc_snoop_channel *chan = snoop_file_to_chan(file);
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret = 0;

	अगर (kfअगरo_is_empty(&chan->fअगरo)) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		ret = रुको_event_पूर्णांकerruptible(chan->wq,
				!kfअगरo_is_empty(&chan->fअगरo));
		अगर (ret == -ERESTARTSYS)
			वापस -EINTR;
	पूर्ण
	ret = kfअगरo_to_user(&chan->fअगरo, buffer, count, &copied);
	अगर (ret)
		वापस ret;

	वापस copied;
पूर्ण

अटल __poll_t snoop_file_poll(काष्ठा file *file,
				    काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा aspeed_lpc_snoop_channel *chan = snoop_file_to_chan(file);

	poll_रुको(file, &chan->wq, pt);
	वापस !kfअगरo_is_empty(&chan->fअगरo) ? EPOLLIN : 0;
पूर्ण

अटल स्थिर काष्ठा file_operations snoop_fops = अणु
	.owner  = THIS_MODULE,
	.पढ़ो   = snoop_file_पढ़ो,
	.poll   = snoop_file_poll,
	.llseek = noop_llseek,
पूर्ण;

/* Save a byte to a FIFO and discard the oldest byte अगर FIFO is full */
अटल व्योम put_fअगरo_with_discard(काष्ठा aspeed_lpc_snoop_channel *chan, u8 val)
अणु
	अगर (!kfअगरo_initialized(&chan->fअगरo))
		वापस;
	अगर (kfअगरo_is_full(&chan->fअगरo))
		kfअगरo_skip(&chan->fअगरo);
	kfअगरo_put(&chan->fअगरo, val);
	wake_up_पूर्णांकerruptible(&chan->wq);
पूर्ण

अटल irqवापस_t aspeed_lpc_snoop_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा aspeed_lpc_snoop *lpc_snoop = arg;
	u32 reg, data;

	अगर (regmap_पढ़ो(lpc_snoop->regmap, HICR6, &reg))
		वापस IRQ_NONE;

	/* Check अगर one of the snoop channels is पूर्णांकerrupting */
	reg &= (HICR6_STR_SNP0W | HICR6_STR_SNP1W);
	अगर (!reg)
		वापस IRQ_NONE;

	/* Ack pending IRQs */
	regmap_ग_लिखो(lpc_snoop->regmap, HICR6, reg);

	/* Read and save most recent snoop'ed data byte to FIFO */
	regmap_पढ़ो(lpc_snoop->regmap, SNPWDR, &data);

	अगर (reg & HICR6_STR_SNP0W) अणु
		u8 val = (data & SNPWDR_CH0_MASK) >> SNPWDR_CH0_SHIFT;

		put_fअगरo_with_discard(&lpc_snoop->chan[0], val);
	पूर्ण
	अगर (reg & HICR6_STR_SNP1W) अणु
		u8 val = (data & SNPWDR_CH1_MASK) >> SNPWDR_CH1_SHIFT;

		put_fअगरo_with_discard(&lpc_snoop->chan[1], val);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aspeed_lpc_snoop_config_irq(काष्ठा aspeed_lpc_snoop *lpc_snoop,
				       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;

	lpc_snoop->irq = platक्रमm_get_irq(pdev, 0);
	अगर (!lpc_snoop->irq)
		वापस -ENODEV;

	rc = devm_request_irq(dev, lpc_snoop->irq,
			      aspeed_lpc_snoop_irq, IRQF_SHARED,
			      DEVICE_NAME, lpc_snoop);
	अगर (rc < 0) अणु
		dev_warn(dev, "Unable to request IRQ %d\n", lpc_snoop->irq);
		lpc_snoop->irq = 0;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_lpc_enable_snoop(काष्ठा aspeed_lpc_snoop *lpc_snoop,
				   काष्ठा device *dev,
				   पूर्णांक channel, u16 lpc_port)
अणु
	पूर्णांक rc = 0;
	u32 hicr5_en, snpwadr_mask, snpwadr_shअगरt, hicrb_en;
	स्थिर काष्ठा aspeed_lpc_snoop_model_data *model_data =
		of_device_get_match_data(dev);

	init_रुकोqueue_head(&lpc_snoop->chan[channel].wq);
	/* Create FIFO dataकाष्ठाure */
	rc = kfअगरo_alloc(&lpc_snoop->chan[channel].fअगरo,
			 SNOOP_FIFO_SIZE, GFP_KERNEL);
	अगर (rc)
		वापस rc;

	lpc_snoop->chan[channel].miscdev.minor = MISC_DYNAMIC_MINOR;
	lpc_snoop->chan[channel].miscdev.name =
		devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%d", DEVICE_NAME, channel);
	lpc_snoop->chan[channel].miscdev.fops = &snoop_fops;
	lpc_snoop->chan[channel].miscdev.parent = dev;
	rc = misc_रेजिस्टर(&lpc_snoop->chan[channel].miscdev);
	अगर (rc)
		वापस rc;

	/* Enable LPC snoop channel at requested port */
	चयन (channel) अणु
	हाल 0:
		hicr5_en = HICR5_EN_SNP0W | HICR5_ENINT_SNP0W;
		snpwadr_mask = SNPWADR_CH0_MASK;
		snpwadr_shअगरt = SNPWADR_CH0_SHIFT;
		hicrb_en = HICRB_ENSNP0D;
		अवरोध;
	हाल 1:
		hicr5_en = HICR5_EN_SNP1W | HICR5_ENINT_SNP1W;
		snpwadr_mask = SNPWADR_CH1_MASK;
		snpwadr_shअगरt = SNPWADR_CH1_SHIFT;
		hicrb_en = HICRB_ENSNP1D;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(lpc_snoop->regmap, HICR5, hicr5_en, hicr5_en);
	regmap_update_bits(lpc_snoop->regmap, SNPWADR, snpwadr_mask,
			   lpc_port << snpwadr_shअगरt);
	अगर (model_data->has_hicrb_ensnp)
		regmap_update_bits(lpc_snoop->regmap, HICRB,
				hicrb_en, hicrb_en);

	वापस rc;
पूर्ण

अटल व्योम aspeed_lpc_disable_snoop(काष्ठा aspeed_lpc_snoop *lpc_snoop,
				     पूर्णांक channel)
अणु
	चयन (channel) अणु
	हाल 0:
		regmap_update_bits(lpc_snoop->regmap, HICR5,
				   HICR5_EN_SNP0W | HICR5_ENINT_SNP0W,
				   0);
		अवरोध;
	हाल 1:
		regmap_update_bits(lpc_snoop->regmap, HICR5,
				   HICR5_EN_SNP1W | HICR5_ENINT_SNP1W,
				   0);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	kfअगरo_मुक्त(&lpc_snoop->chan[channel].fअगरo);
	misc_deरेजिस्टर(&lpc_snoop->chan[channel].miscdev);
पूर्ण

अटल पूर्णांक aspeed_lpc_snoop_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_lpc_snoop *lpc_snoop;
	काष्ठा device *dev;
	काष्ठा device_node *np;
	u32 port;
	पूर्णांक rc;

	dev = &pdev->dev;

	lpc_snoop = devm_kzalloc(dev, माप(*lpc_snoop), GFP_KERNEL);
	अगर (!lpc_snoop)
		वापस -ENOMEM;

	np = pdev->dev.parent->of_node;
	अगर (!of_device_is_compatible(np, "aspeed,ast2400-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2500-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2600-lpc-v2")) अणु
		dev_err(dev, "unsupported LPC device binding\n");
		वापस -ENODEV;
	पूर्ण

	lpc_snoop->regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(lpc_snoop->regmap)) अणु
		dev_err(dev, "Couldn't get regmap\n");
		वापस -ENODEV;
	पूर्ण

	dev_set_drvdata(&pdev->dev, lpc_snoop);

	rc = of_property_पढ़ो_u32_index(dev->of_node, "snoop-ports", 0, &port);
	अगर (rc) अणु
		dev_err(dev, "no snoop ports configured\n");
		वापस -ENODEV;
	पूर्ण

	lpc_snoop->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(lpc_snoop->clk)) अणु
		rc = PTR_ERR(lpc_snoop->clk);
		अगर (rc != -EPROBE_DEFER)
			dev_err(dev, "couldn't get clock\n");
		वापस rc;
	पूर्ण
	rc = clk_prepare_enable(lpc_snoop->clk);
	अगर (rc) अणु
		dev_err(dev, "couldn't enable clock\n");
		वापस rc;
	पूर्ण

	rc = aspeed_lpc_snoop_config_irq(lpc_snoop, pdev);
	अगर (rc)
		जाओ err;

	rc = aspeed_lpc_enable_snoop(lpc_snoop, dev, 0, port);
	अगर (rc)
		जाओ err;

	/* Configuration of 2nd snoop channel port is optional */
	अगर (of_property_पढ़ो_u32_index(dev->of_node, "snoop-ports",
				       1, &port) == 0) अणु
		rc = aspeed_lpc_enable_snoop(lpc_snoop, dev, 1, port);
		अगर (rc) अणु
			aspeed_lpc_disable_snoop(lpc_snoop, 0);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_disable_unprepare(lpc_snoop->clk);

	वापस rc;
पूर्ण

अटल पूर्णांक aspeed_lpc_snoop_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_lpc_snoop *lpc_snoop = dev_get_drvdata(&pdev->dev);

	/* Disable both snoop channels */
	aspeed_lpc_disable_snoop(lpc_snoop, 0);
	aspeed_lpc_disable_snoop(lpc_snoop, 1);

	clk_disable_unprepare(lpc_snoop->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aspeed_lpc_snoop_model_data ast2400_model_data = अणु
	.has_hicrb_ensnp = 0,
पूर्ण;

अटल स्थिर काष्ठा aspeed_lpc_snoop_model_data ast2500_model_data = अणु
	.has_hicrb_ensnp = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_lpc_snoop_match[] = अणु
	अणु .compatible = "aspeed,ast2400-lpc-snoop",
	  .data = &ast2400_model_data पूर्ण,
	अणु .compatible = "aspeed,ast2500-lpc-snoop",
	  .data = &ast2500_model_data पूर्ण,
	अणु .compatible = "aspeed,ast2600-lpc-snoop",
	  .data = &ast2500_model_data पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_lpc_snoop_driver = अणु
	.driver = अणु
		.name		= DEVICE_NAME,
		.of_match_table = aspeed_lpc_snoop_match,
	पूर्ण,
	.probe = aspeed_lpc_snoop_probe,
	.हटाओ = aspeed_lpc_snoop_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_lpc_snoop_driver);

MODULE_DEVICE_TABLE(of, aspeed_lpc_snoop_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Lippert <rlippert@google.com>");
MODULE_DESCRIPTION("Linux driver to control Aspeed LPC snoop functionality");
