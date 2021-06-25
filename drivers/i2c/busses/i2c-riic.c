<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RIIC driver
 *
 * Copyright (C) 2013 Wolfram Sang <wsa@sang-engineering.com>
 * Copyright (C) 2013 Renesas Solutions Corp.
 */

/*
 * This i2c core has a lot of पूर्णांकerrupts, namely 8. We use their chaining as
 * some kind of state machine.
 *
 * 1) The मुख्य xfer routine kicks off a transmission by putting the start bit
 * (or repeated start) on the bus and enabling the transmit पूर्णांकerrupt (TIE)
 * since we need to send the slave address + RW bit in every हाल.
 *
 * 2) TIE sends slave address + RW bit and selects how to जारी.
 *
 * 3a) Write हाल: We keep utilizing TIE as दीर्घ as we have data to send. If we
 * are करोne, we चयन over to the transmission करोne पूर्णांकerrupt (TEIE) and mark
 * the message as completed (includes sending STOP) there.
 *
 * 3b) Read हाल: We चयन over to receive पूर्णांकerrupt (RIE). One dummy पढ़ो is
 * needed to start घड़ीing, then we keep receiving until we are करोne. Note
 * that we use the RDRFS mode all the समय, i.e. we ACK/NACK every byte by
 * writing to the ACKBT bit. I tried using the RDRFS mode only at the end of a
 * message to create the final NACK as sketched in the datasheet. This caused
 * some subtle races (when byte n was processed and byte n+1 was alपढ़ोy
 * रुकोing), though, and I started with the safe approach.
 *
 * 4) If we got a NACK somewhere, we flag the error and stop the transmission
 * via NAKIE.
 *
 * Also check the comments in the पूर्णांकerrupt routines क्रम some gory details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा RIIC_ICCR1	0x00
#घोषणा RIIC_ICCR2	0x04
#घोषणा RIIC_ICMR1	0x08
#घोषणा RIIC_ICMR3	0x10
#घोषणा RIIC_ICSER	0x18
#घोषणा RIIC_ICIER	0x1c
#घोषणा RIIC_ICSR2	0x24
#घोषणा RIIC_ICBRL	0x34
#घोषणा RIIC_ICBRH	0x38
#घोषणा RIIC_ICDRT	0x3c
#घोषणा RIIC_ICDRR	0x40

#घोषणा ICCR1_ICE	0x80
#घोषणा ICCR1_IICRST	0x40
#घोषणा ICCR1_SOWP	0x10

#घोषणा ICCR2_BBSY	0x80
#घोषणा ICCR2_SP	0x08
#घोषणा ICCR2_RS	0x04
#घोषणा ICCR2_ST	0x02

#घोषणा ICMR1_CKS_MASK	0x70
#घोषणा ICMR1_BCWP	0x08
#घोषणा ICMR1_CKS(_x)	((((_x) << 4) & ICMR1_CKS_MASK) | ICMR1_BCWP)

#घोषणा ICMR3_RDRFS	0x20
#घोषणा ICMR3_ACKWP	0x10
#घोषणा ICMR3_ACKBT	0x08

#घोषणा ICIER_TIE	0x80
#घोषणा ICIER_TEIE	0x40
#घोषणा ICIER_RIE	0x20
#घोषणा ICIER_NAKIE	0x10
#घोषणा ICIER_SPIE	0x08

#घोषणा ICSR2_NACKF	0x10

#घोषणा ICBR_RESERVED	0xe0 /* Should be 1 on ग_लिखोs */

#घोषणा RIIC_INIT_MSG	-1

काष्ठा riic_dev अणु
	व्योम __iomem *base;
	u8 *buf;
	काष्ठा i2c_msg *msg;
	पूर्णांक bytes_left;
	पूर्णांक err;
	पूर्णांक is_last;
	काष्ठा completion msg_करोne;
	काष्ठा i2c_adapter adapter;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा riic_irq_desc अणु
	पूर्णांक res_num;
	irq_handler_t isr;
	अक्षर *name;
पूर्ण;

अटल अंतरभूत व्योम riic_clear_set_bit(काष्ठा riic_dev *riic, u8 clear, u8 set, u8 reg)
अणु
	ग_लिखोb((पढ़ोb(riic->base + reg) & ~clear) | set, riic->base + reg);
पूर्ण

अटल पूर्णांक riic_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा riic_dev *riic = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समय_left;
	पूर्णांक i;
	u8 start_bit;

	pm_runसमय_get_sync(adap->dev.parent);

	अगर (पढ़ोb(riic->base + RIIC_ICCR2) & ICCR2_BBSY) अणु
		riic->err = -EBUSY;
		जाओ out;
	पूर्ण

	reinit_completion(&riic->msg_करोne);
	riic->err = 0;

	ग_लिखोb(0, riic->base + RIIC_ICSR2);

	क्रम (i = 0, start_bit = ICCR2_ST; i < num; i++) अणु
		riic->bytes_left = RIIC_INIT_MSG;
		riic->buf = msgs[i].buf;
		riic->msg = &msgs[i];
		riic->is_last = (i == num - 1);

		ग_लिखोb(ICIER_NAKIE | ICIER_TIE, riic->base + RIIC_ICIER);

		ग_लिखोb(start_bit, riic->base + RIIC_ICCR2);

		समय_left = रुको_क्रम_completion_समयout(&riic->msg_करोne, riic->adapter.समयout);
		अगर (समय_left == 0)
			riic->err = -ETIMEDOUT;

		अगर (riic->err)
			अवरोध;

		start_bit = ICCR2_RS;
	पूर्ण

 out:
	pm_runसमय_put(adap->dev.parent);

	वापस riic->err ?: num;
पूर्ण

अटल irqवापस_t riic_tdre_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा riic_dev *riic = data;
	u8 val;

	अगर (!riic->bytes_left)
		वापस IRQ_NONE;

	अगर (riic->bytes_left == RIIC_INIT_MSG) अणु
		अगर (riic->msg->flags & I2C_M_RD)
			/* On पढ़ो, चयन over to receive पूर्णांकerrupt */
			riic_clear_set_bit(riic, ICIER_TIE, ICIER_RIE, RIIC_ICIER);
		अन्यथा
			/* On ग_लिखो, initialize length */
			riic->bytes_left = riic->msg->len;

		val = i2c_8bit_addr_from_msg(riic->msg);
	पूर्ण अन्यथा अणु
		val = *riic->buf;
		riic->buf++;
		riic->bytes_left--;
	पूर्ण

	/*
	 * Switch to transmission ended पूर्णांकerrupt when करोne. Do check here
	 * after bytes_left was initialized to support SMBUS_QUICK (new msg has
	 * 0 length then)
	 */
	अगर (riic->bytes_left == 0)
		riic_clear_set_bit(riic, ICIER_TIE, ICIER_TEIE, RIIC_ICIER);

	/*
	 * This acks the TIE पूर्णांकerrupt. We get another TIE immediately अगर our
	 * value could be moved to the shaकरोw shअगरt रेजिस्टर right away. So
	 * this must be after updates to ICIER (where we want to disable TIE)!
	 */
	ग_लिखोb(val, riic->base + RIIC_ICDRT);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t riic_tend_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा riic_dev *riic = data;

	अगर (पढ़ोb(riic->base + RIIC_ICSR2) & ICSR2_NACKF) अणु
		/* We got a NACKIE */
		पढ़ोb(riic->base + RIIC_ICDRR);	/* dummy पढ़ो */
		riic_clear_set_bit(riic, ICSR2_NACKF, 0, RIIC_ICSR2);
		riic->err = -ENXIO;
	पूर्ण अन्यथा अगर (riic->bytes_left) अणु
		वापस IRQ_NONE;
	पूर्ण

	अगर (riic->is_last || riic->err) अणु
		riic_clear_set_bit(riic, ICIER_TEIE, ICIER_SPIE, RIIC_ICIER);
		ग_लिखोb(ICCR2_SP, riic->base + RIIC_ICCR2);
	पूर्ण अन्यथा अणु
		/* Transfer is complete, but करो not send STOP */
		riic_clear_set_bit(riic, ICIER_TEIE, 0, RIIC_ICIER);
		complete(&riic->msg_करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t riic_rdrf_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा riic_dev *riic = data;

	अगर (!riic->bytes_left)
		वापस IRQ_NONE;

	अगर (riic->bytes_left == RIIC_INIT_MSG) अणु
		riic->bytes_left = riic->msg->len;
		पढ़ोb(riic->base + RIIC_ICDRR);	/* dummy पढ़ो */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (riic->bytes_left == 1) अणु
		/* STOP must come beक्रमe we set ACKBT! */
		अगर (riic->is_last) अणु
			riic_clear_set_bit(riic, 0, ICIER_SPIE, RIIC_ICIER);
			ग_लिखोb(ICCR2_SP, riic->base + RIIC_ICCR2);
		पूर्ण

		riic_clear_set_bit(riic, 0, ICMR3_ACKBT, RIIC_ICMR3);

	पूर्ण अन्यथा अणु
		riic_clear_set_bit(riic, ICMR3_ACKBT, 0, RIIC_ICMR3);
	पूर्ण

	/* Reading acks the RIE पूर्णांकerrupt */
	*riic->buf = पढ़ोb(riic->base + RIIC_ICDRR);
	riic->buf++;
	riic->bytes_left--;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t riic_stop_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा riic_dev *riic = data;

	/* पढ़ो back रेजिस्टरs to confirm ग_लिखोs have fully propagated */
	ग_लिखोb(0, riic->base + RIIC_ICSR2);
	पढ़ोb(riic->base + RIIC_ICSR2);
	ग_लिखोb(0, riic->base + RIIC_ICIER);
	पढ़ोb(riic->base + RIIC_ICIER);

	complete(&riic->msg_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 riic_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm riic_algo = अणु
	.master_xfer	= riic_xfer,
	.functionality	= riic_func,
पूर्ण;

अटल पूर्णांक riic_init_hw(काष्ठा riic_dev *riic, काष्ठा i2c_timings *t)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ rate;
	पूर्णांक total_ticks, cks, brl, brh;

	pm_runसमय_get_sync(riic->adapter.dev.parent);

	अगर (t->bus_freq_hz > I2C_MAX_FAST_MODE_FREQ) अणु
		dev_err(&riic->adapter.dev,
			"unsupported bus speed (%dHz). %d max\n",
			t->bus_freq_hz, I2C_MAX_FAST_MODE_FREQ);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rate = clk_get_rate(riic->clk);

	/*
	 * Assume the शेष रेजिस्टर settings:
	 *  FER.SCLE = 1 (SCL sync circuit enabled, adds 2 or 3 cycles)
	 *  FER.NFE = 1 (noise circuit enabled)
	 *  MR3.NF = 0 (1 cycle of noise filtered out)
	 *
	 * Freq (CKS=000) = (I2CCLK + tr + tf)/ (BRH + 3 + 1) + (BRL + 3 + 1)
	 * Freq (CKS!=000) = (I2CCLK + tr + tf)/ (BRH + 2 + 1) + (BRL + 2 + 1)
	 */

	/*
	 * Determine reference घड़ी rate. We must be able to get the desired
	 * frequency with only 62 घड़ी ticks max (31 high, 31 low).
	 * Aim क्रम a duty of 60% LOW, 40% HIGH.
	 */
	total_ticks = DIV_ROUND_UP(rate, t->bus_freq_hz);

	क्रम (cks = 0; cks < 7; cks++) अणु
		/*
		 * 60% low समय must be less than BRL + 2 + 1
		 * BRL max रेजिस्टर value is 0x1F.
		 */
		brl = ((total_ticks * 6) / 10);
		अगर (brl <= (0x1F + 3))
			अवरोध;

		total_ticks /= 2;
		rate /= 2;
	पूर्ण

	अगर (brl > (0x1F + 3)) अणु
		dev_err(&riic->adapter.dev, "invalid speed (%lu). Too slow.\n",
			(अचिन्हित दीर्घ)t->bus_freq_hz);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	brh = total_ticks - brl;

	/* Remove स्वतःmatic घड़ी ticks क्रम sync circuit and NF */
	अगर (cks == 0) अणु
		brl -= 4;
		brh -= 4;
	पूर्ण अन्यथा अणु
		brl -= 3;
		brh -= 3;
	पूर्ण

	/*
	 * Remove घड़ी ticks क्रम rise and fall बार. Convert ns to घड़ी
	 * ticks.
	 */
	brl -= t->scl_fall_ns / (1000000000 / rate);
	brh -= t->scl_rise_ns / (1000000000 / rate);

	/* Adjust क्रम min रेजिस्टर values क्रम when SCLE=1 and NFE=1 */
	अगर (brl < 1)
		brl = 1;
	अगर (brh < 1)
		brh = 1;

	pr_debug("i2c-riic: freq=%lu, duty=%d, fall=%lu, rise=%lu, cks=%d, brl=%d, brh=%d\n",
		 rate / total_ticks, ((brl + 3) * 100) / (brl + brh + 6),
		 t->scl_fall_ns / (1000000000 / rate),
		 t->scl_rise_ns / (1000000000 / rate), cks, brl, brh);

	/* Changing the order of accessing IICRST and ICE may अवरोध things! */
	ग_लिखोb(ICCR1_IICRST | ICCR1_SOWP, riic->base + RIIC_ICCR1);
	riic_clear_set_bit(riic, 0, ICCR1_ICE, RIIC_ICCR1);

	ग_लिखोb(ICMR1_CKS(cks), riic->base + RIIC_ICMR1);
	ग_लिखोb(brh | ICBR_RESERVED, riic->base + RIIC_ICBRH);
	ग_लिखोb(brl | ICBR_RESERVED, riic->base + RIIC_ICBRL);

	ग_लिखोb(0, riic->base + RIIC_ICSER);
	ग_लिखोb(ICMR3_ACKWP | ICMR3_RDRFS, riic->base + RIIC_ICMR3);

	riic_clear_set_bit(riic, ICCR1_IICRST, 0, RIIC_ICCR1);

out:
	pm_runसमय_put(riic->adapter.dev.parent);
	वापस ret;
पूर्ण

अटल काष्ठा riic_irq_desc riic_irqs[] = अणु
	अणु .res_num = 0, .isr = riic_tend_isr, .name = "riic-tend" पूर्ण,
	अणु .res_num = 1, .isr = riic_rdrf_isr, .name = "riic-rdrf" पूर्ण,
	अणु .res_num = 2, .isr = riic_tdre_isr, .name = "riic-tdre" पूर्ण,
	अणु .res_num = 3, .isr = riic_stop_isr, .name = "riic-stop" पूर्ण,
	अणु .res_num = 5, .isr = riic_tend_isr, .name = "riic-nack" पूर्ण,
पूर्ण;

अटल पूर्णांक riic_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा riic_dev *riic;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *res;
	काष्ठा i2c_timings i2c_t;
	पूर्णांक i, ret;

	riic = devm_kzalloc(&pdev->dev, माप(*riic), GFP_KERNEL);
	अगर (!riic)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	riic->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(riic->base))
		वापस PTR_ERR(riic->base);

	riic->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(riic->clk)) अणु
		dev_err(&pdev->dev, "missing controller clock");
		वापस PTR_ERR(riic->clk);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(riic_irqs); i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, riic_irqs[i].res_num);
		अगर (!res)
			वापस -ENODEV;

		ret = devm_request_irq(&pdev->dev, res->start, riic_irqs[i].isr,
					0, riic_irqs[i].name, riic);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request irq %s\n", riic_irqs[i].name);
			वापस ret;
		पूर्ण
	पूर्ण

	adap = &riic->adapter;
	i2c_set_adapdata(adap, riic);
	strlcpy(adap->name, "Renesas RIIC adapter", माप(adap->name));
	adap->owner = THIS_MODULE;
	adap->algo = &riic_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&riic->msg_करोne);

	i2c_parse_fw_timings(&pdev->dev, &i2c_t, true);

	pm_runसमय_enable(&pdev->dev);

	ret = riic_init_hw(riic, &i2c_t);
	अगर (ret)
		जाओ out;

	ret = i2c_add_adapter(adap);
	अगर (ret)
		जाओ out;

	platक्रमm_set_drvdata(pdev, riic);

	dev_info(&pdev->dev, "registered with %dHz bus speed\n",
		 i2c_t.bus_freq_hz);
	वापस 0;

out:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक riic_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा riic_dev *riic = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);
	ग_लिखोb(0, riic->base + RIIC_ICIER);
	pm_runसमय_put(&pdev->dev);
	i2c_del_adapter(&riic->adapter);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id riic_i2c_dt_ids[] = अणु
	अणु .compatible = "renesas,riic-rz" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver riic_i2c_driver = अणु
	.probe		= riic_i2c_probe,
	.हटाओ		= riic_i2c_हटाओ,
	.driver		= अणु
		.name	= "i2c-riic",
		.of_match_table = riic_i2c_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(riic_i2c_driver);

MODULE_DESCRIPTION("Renesas RIIC adapter");
MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, riic_i2c_dt_ids);
