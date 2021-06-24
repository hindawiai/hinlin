<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Mans Rullgard <mans@mansr.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME "tango-ir"

#घोषणा IR_NEC_CTRL	0x00
#घोषणा IR_NEC_DATA	0x04
#घोषणा IR_CTRL		0x08
#घोषणा IR_RC5_CLK_DIV	0x0c
#घोषणा IR_RC5_DATA	0x10
#घोषणा IR_INT		0x14

#घोषणा NEC_TIME_BASE	560
#घोषणा RC5_TIME_BASE	1778

#घोषणा RC6_CTRL	0x00
#घोषणा RC6_CLKDIV	0x04
#घोषणा RC6_DATA0	0x08
#घोषणा RC6_DATA1	0x0c
#घोषणा RC6_DATA2	0x10
#घोषणा RC6_DATA3	0x14
#घोषणा RC6_DATA4	0x18

#घोषणा RC6_CARRIER	36000
#घोषणा RC6_TIME_BASE	16

#घोषणा NEC_CAP(n)	((n) << 24)
#घोषणा GPIO_SEL(n)	((n) << 16)
#घोषणा DISABLE_NEC	(BIT(4) | BIT(8))
#घोषणा ENABLE_RC5	(BIT(0) | BIT(9))
#घोषणा ENABLE_RC6	(BIT(0) | BIT(7))
#घोषणा ACK_IR_INT	(BIT(0) | BIT(1))
#घोषणा ACK_RC6_INT	(BIT(31))

#घोषणा NEC_ANY (RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32)

काष्ठा tango_ir अणु
	व्योम __iomem *rc5_base;
	व्योम __iomem *rc6_base;
	काष्ठा rc_dev *rc;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम tango_ir_handle_nec(काष्ठा tango_ir *ir)
अणु
	u32 v, code;
	क्रमागत rc_proto proto;

	v = पढ़ोl_relaxed(ir->rc5_base + IR_NEC_DATA);
	अगर (!v) अणु
		rc_repeat(ir->rc);
		वापस;
	पूर्ण

	code = ir_nec_bytes_to_scancode(v, v >> 8, v >> 16, v >> 24, &proto);
	rc_keyकरोwn(ir->rc, proto, code, 0);
पूर्ण

अटल व्योम tango_ir_handle_rc5(काष्ठा tango_ir *ir)
अणु
	u32 data, field, toggle, addr, cmd, code;

	data = पढ़ोl_relaxed(ir->rc5_base + IR_RC5_DATA);
	अगर (data & BIT(31))
		वापस;

	field = data >> 12 & 1;
	toggle = data >> 11 & 1;
	addr = data >> 6 & 0x1f;
	cmd = (data & 0x3f) | (field ^ 1) << 6;

	code = RC_SCANCODE_RC5(addr, cmd);
	rc_keyकरोwn(ir->rc, RC_PROTO_RC5, code, toggle);
पूर्ण

अटल व्योम tango_ir_handle_rc6(काष्ठा tango_ir *ir)
अणु
	u32 data0, data1, toggle, mode, addr, cmd, code;

	data0 = पढ़ोl_relaxed(ir->rc6_base + RC6_DATA0);
	data1 = पढ़ोl_relaxed(ir->rc6_base + RC6_DATA1);

	mode = data0 >> 1 & 7;
	अगर (mode != 0)
		वापस;

	toggle = data0 & 1;
	addr = data0 >> 16;
	cmd = data1;

	code = RC_SCANCODE_RC6_0(addr, cmd);
	rc_keyकरोwn(ir->rc, RC_PROTO_RC6_0, code, toggle);
पूर्ण

अटल irqवापस_t tango_ir_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tango_ir *ir = dev_id;
	अचिन्हित पूर्णांक rc5_stat;
	अचिन्हित पूर्णांक rc6_stat;

	rc5_stat = पढ़ोl_relaxed(ir->rc5_base + IR_INT);
	ग_लिखोl_relaxed(rc5_stat, ir->rc5_base + IR_INT);

	rc6_stat = पढ़ोl_relaxed(ir->rc6_base + RC6_CTRL);
	ग_लिखोl_relaxed(rc6_stat, ir->rc6_base + RC6_CTRL);

	अगर (!(rc5_stat & 3) && !(rc6_stat & BIT(31)))
		वापस IRQ_NONE;

	अगर (rc5_stat & BIT(0))
		tango_ir_handle_rc5(ir);

	अगर (rc5_stat & BIT(1))
		tango_ir_handle_nec(ir);

	अगर (rc6_stat & BIT(31))
		tango_ir_handle_rc6(ir);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tango_change_protocol(काष्ठा rc_dev *dev, u64 *rc_type)
अणु
	काष्ठा tango_ir *ir = dev->priv;
	u32 rc5_ctrl = DISABLE_NEC;
	u32 rc6_ctrl = 0;

	अगर (*rc_type & NEC_ANY)
		rc5_ctrl = 0;

	अगर (*rc_type & RC_PROTO_BIT_RC5)
		rc5_ctrl |= ENABLE_RC5;

	अगर (*rc_type & RC_PROTO_BIT_RC6_0)
		rc6_ctrl = ENABLE_RC6;

	ग_लिखोl_relaxed(rc5_ctrl, ir->rc5_base + IR_CTRL);
	ग_लिखोl_relaxed(rc6_ctrl, ir->rc6_base + RC6_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक tango_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *map_name = RC_MAP_TANGO;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rc_dev *rc;
	काष्ठा tango_ir *ir;
	u64 clkrate, clkभाग;
	पूर्णांक irq, err;
	u32 val;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -EINVAL;

	ir = devm_kzalloc(dev, माप(*ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	ir->rc5_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ir->rc5_base))
		वापस PTR_ERR(ir->rc5_base);

	ir->rc6_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(ir->rc6_base))
		वापस PTR_ERR(ir->rc6_base);

	ir->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ir->clk))
		वापस PTR_ERR(ir->clk);

	rc = devm_rc_allocate_device(dev, RC_DRIVER_SCANCODE);
	अगर (!rc)
		वापस -ENOMEM;

	of_property_पढ़ो_string(dev->of_node, "linux,rc-map-name", &map_name);

	rc->device_name = DRIVER_NAME;
	rc->driver_name = DRIVER_NAME;
	rc->input_phys = DRIVER_NAME "/input0";
	rc->map_name = map_name;
	rc->allowed_protocols = NEC_ANY | RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_0;
	rc->change_protocol = tango_change_protocol;
	rc->priv = ir;
	ir->rc = rc;

	err = clk_prepare_enable(ir->clk);
	अगर (err)
		वापस err;

	clkrate = clk_get_rate(ir->clk);

	clkभाग = clkrate * NEC_TIME_BASE;
	करो_भाग(clkभाग, 1000000);

	val = NEC_CAP(31) | GPIO_SEL(12) | clkभाग;
	ग_लिखोl_relaxed(val, ir->rc5_base + IR_NEC_CTRL);

	clkभाग = clkrate * RC5_TIME_BASE;
	करो_भाग(clkभाग, 1000000);

	ग_लिखोl_relaxed(DISABLE_NEC, ir->rc5_base + IR_CTRL);
	ग_लिखोl_relaxed(clkभाग, ir->rc5_base + IR_RC5_CLK_DIV);
	ग_लिखोl_relaxed(ACK_IR_INT, ir->rc5_base + IR_INT);

	clkभाग = clkrate * RC6_TIME_BASE;
	करो_भाग(clkभाग, RC6_CARRIER);

	ग_लिखोl_relaxed(ACK_RC6_INT, ir->rc6_base + RC6_CTRL);
	ग_लिखोl_relaxed((clkभाग >> 2) << 18 | clkभाग, ir->rc6_base + RC6_CLKDIV);

	err = devm_request_irq(dev, irq, tango_ir_irq, IRQF_SHARED,
			       dev_name(dev), ir);
	अगर (err)
		जाओ err_clk;

	err = devm_rc_रेजिस्टर_device(dev, rc);
	अगर (err)
		जाओ err_clk;

	platक्रमm_set_drvdata(pdev, ir);
	वापस 0;

err_clk:
	clk_disable_unprepare(ir->clk);
	वापस err;
पूर्ण

अटल पूर्णांक tango_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tango_ir *ir = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(ir->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tango_ir_dt_ids[] = अणु
	अणु .compatible = "sigma,smp8642-ir" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tango_ir_dt_ids);

अटल काष्ठा platक्रमm_driver tango_ir_driver = अणु
	.probe	= tango_ir_probe,
	.हटाओ	= tango_ir_हटाओ,
	.driver	= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= tango_ir_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tango_ir_driver);

MODULE_DESCRIPTION("SMP86xx IR decoder driver");
MODULE_AUTHOR("Mans Rullgard <mans@mansr.com>");
MODULE_LICENSE("GPL");
