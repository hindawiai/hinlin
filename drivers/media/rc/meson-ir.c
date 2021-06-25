<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Amlogic Meson IR remote receiver
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitfield.h>

#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME		"meson-ir"

/* valid on all Meson platक्रमms */
#घोषणा IR_DEC_LDR_ACTIVE	0x00
#घोषणा IR_DEC_LDR_IDLE		0x04
#घोषणा IR_DEC_LDR_REPEAT	0x08
#घोषणा IR_DEC_BIT_0		0x0c
#घोषणा IR_DEC_REG0		0x10
#घोषणा IR_DEC_FRAME		0x14
#घोषणा IR_DEC_STATUS		0x18
#घोषणा IR_DEC_REG1		0x1c
/* only available on Meson 8b and newer */
#घोषणा IR_DEC_REG2		0x20

#घोषणा REG0_RATE_MASK		GENMASK(11, 0)

#घोषणा DECODE_MODE_NEC		0x0
#घोषणा DECODE_MODE_RAW		0x2

/* Meson 6b uses REG1 to configure the mode */
#घोषणा REG1_MODE_MASK		GENMASK(8, 7)
#घोषणा REG1_MODE_SHIFT		7

/* Meson 8b / GXBB use REG2 to configure the mode */
#घोषणा REG2_MODE_MASK		GENMASK(3, 0)
#घोषणा REG2_MODE_SHIFT		0

#घोषणा REG1_TIME_IV_MASK	GENMASK(28, 16)

#घोषणा REG1_IRQSEL_MASK	GENMASK(3, 2)
#घोषणा REG1_IRQSEL_NEC_MODE	0
#घोषणा REG1_IRQSEL_RISE_FALL	1
#घोषणा REG1_IRQSEL_FALL	2
#घोषणा REG1_IRQSEL_RISE	3

#घोषणा REG1_RESET		BIT(0)
#घोषणा REG1_ENABLE		BIT(15)

#घोषणा STATUS_IR_DEC_IN	BIT(8)

#घोषणा MESON_TRATE		10	/* us */

काष्ठा meson_ir अणु
	व्योम __iomem	*reg;
	काष्ठा rc_dev	*rc;
	spinlock_t	lock;
पूर्ण;

अटल व्योम meson_ir_set_mask(काष्ठा meson_ir *ir, अचिन्हित पूर्णांक reg,
			      u32 mask, u32 value)
अणु
	u32 data;

	data = पढ़ोl(ir->reg + reg);
	data &= ~mask;
	data |= (value & mask);
	ग_लिखोl(data, ir->reg + reg);
पूर्ण

अटल irqवापस_t meson_ir_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा meson_ir *ir = dev_id;
	u32 duration, status;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	spin_lock(&ir->lock);

	duration = पढ़ोl_relaxed(ir->reg + IR_DEC_REG1);
	duration = FIELD_GET(REG1_TIME_IV_MASK, duration);
	rawir.duration = duration * MESON_TRATE;

	status = पढ़ोl_relaxed(ir->reg + IR_DEC_STATUS);
	rawir.pulse = !!(status & STATUS_IR_DEC_IN);

	ir_raw_event_store_with_समयout(ir->rc, &rawir);

	spin_unlock(&ir->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक meson_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	स्थिर अक्षर *map_name;
	काष्ठा meson_ir *ir;
	पूर्णांक irq, ret;

	ir = devm_kzalloc(dev, माप(काष्ठा meson_ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ir->reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ir->reg))
		वापस PTR_ERR(ir->reg);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ir->rc = devm_rc_allocate_device(dev, RC_DRIVER_IR_RAW);
	अगर (!ir->rc) अणु
		dev_err(dev, "failed to allocate rc device\n");
		वापस -ENOMEM;
	पूर्ण

	ir->rc->priv = ir;
	ir->rc->device_name = DRIVER_NAME;
	ir->rc->input_phys = DRIVER_NAME "/input0";
	ir->rc->input_id.bustype = BUS_HOST;
	map_name = of_get_property(node, "linux,rc-map-name", शून्य);
	ir->rc->map_name = map_name ? map_name : RC_MAP_EMPTY;
	ir->rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	ir->rc->rx_resolution = MESON_TRATE;
	ir->rc->min_समयout = 1;
	ir->rc->समयout = IR_DEFAULT_TIMEOUT;
	ir->rc->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	ir->rc->driver_name = DRIVER_NAME;

	spin_lock_init(&ir->lock);
	platक्रमm_set_drvdata(pdev, ir);

	ret = devm_rc_रेजिस्टर_device(dev, ir->rc);
	अगर (ret) अणु
		dev_err(dev, "failed to register rc device\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, irq, meson_ir_irq, 0, शून्य, ir);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	/* Reset the decoder */
	meson_ir_set_mask(ir, IR_DEC_REG1, REG1_RESET, REG1_RESET);
	meson_ir_set_mask(ir, IR_DEC_REG1, REG1_RESET, 0);

	/* Set general operation mode (= raw/software decoding) */
	अगर (of_device_is_compatible(node, "amlogic,meson6-ir"))
		meson_ir_set_mask(ir, IR_DEC_REG1, REG1_MODE_MASK,
				  FIELD_PREP(REG1_MODE_MASK, DECODE_MODE_RAW));
	अन्यथा
		meson_ir_set_mask(ir, IR_DEC_REG2, REG2_MODE_MASK,
				  FIELD_PREP(REG2_MODE_MASK, DECODE_MODE_RAW));

	/* Set rate */
	meson_ir_set_mask(ir, IR_DEC_REG0, REG0_RATE_MASK, MESON_TRATE - 1);
	/* IRQ on rising and falling edges */
	meson_ir_set_mask(ir, IR_DEC_REG1, REG1_IRQSEL_MASK,
			  FIELD_PREP(REG1_IRQSEL_MASK, REG1_IRQSEL_RISE_FALL));
	/* Enable the decoder */
	meson_ir_set_mask(ir, IR_DEC_REG1, REG1_ENABLE, REG1_ENABLE);

	dev_info(dev, "receiver initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक meson_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ir *ir = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	/* Disable the decoder */
	spin_lock_irqsave(&ir->lock, flags);
	meson_ir_set_mask(ir, IR_DEC_REG1, REG1_ENABLE, 0);
	spin_unlock_irqrestore(&ir->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम meson_ir_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा meson_ir *ir = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ir->lock, flags);

	/*
	 * Set operation mode to NEC/hardware decoding to give
	 * bootloader a chance to घातer the प्रणाली back on
	 */
	अगर (of_device_is_compatible(node, "amlogic,meson6-ir"))
		meson_ir_set_mask(ir, IR_DEC_REG1, REG1_MODE_MASK,
				  DECODE_MODE_NEC << REG1_MODE_SHIFT);
	अन्यथा
		meson_ir_set_mask(ir, IR_DEC_REG2, REG2_MODE_MASK,
				  DECODE_MODE_NEC << REG2_MODE_SHIFT);

	/* Set rate to शेष value */
	meson_ir_set_mask(ir, IR_DEC_REG0, REG0_RATE_MASK, 0x13);

	spin_unlock_irqrestore(&ir->lock, flags);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_ir_match[] = अणु
	अणु .compatible = "amlogic,meson6-ir" पूर्ण,
	अणु .compatible = "amlogic,meson8b-ir" पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-ir" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_ir_match);

अटल काष्ठा platक्रमm_driver meson_ir_driver = अणु
	.probe		= meson_ir_probe,
	.हटाओ		= meson_ir_हटाओ,
	.shutकरोwn	= meson_ir_shutकरोwn,
	.driver = अणु
		.name		= DRIVER_NAME,
		.of_match_table	= meson_ir_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_ir_driver);

MODULE_DESCRIPTION("Amlogic Meson IR remote receiver driver");
MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_LICENSE("GPL v2");
