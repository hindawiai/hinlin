<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Mediatek IR Receiver Controller
 *
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>
#समावेश <media/rc-core.h>

#घोषणा MTK_IR_DEV KBUILD_MODNAME

/* Register to enable PWM and IR */
#घोषणा MTK_CONFIG_HIGH_REG       0x0c

/* Bit to enable IR pulse width detection */
#घोषणा MTK_PWM_EN		  BIT(13)

/*
 * Register to setting ok count whose unit based on hardware sampling period
 * indicating IR receiving completion and then making IRQ fires
 */
#घोषणा MTK_OK_COUNT(x)		  (((x) & GENMASK(23, 16)) << 16)

/* Bit to enable IR hardware function */
#घोषणा MTK_IR_EN		  BIT(0)

/* Bit to restart IR receiving */
#घोषणा MTK_IRCLR		  BIT(0)

/* Fields containing pulse width data */
#घोषणा MTK_WIDTH_MASK		  (GENMASK(7, 0))

/* IR threshold */
#घोषणा MTK_IRTHD		 0x14
#घोषणा MTK_DG_CNT_MASK		 (GENMASK(12, 8))
#घोषणा MTK_DG_CNT(x)		 ((x) << 8)

/* Bit to enable पूर्णांकerrupt */
#घोषणा MTK_IRINT_EN		  BIT(0)

/* Bit to clear पूर्णांकerrupt status */
#घोषणा MTK_IRINT_CLR		  BIT(0)

/* Maximum count of samples */
#घोषणा MTK_MAX_SAMPLES		  0xff
/* Indicate the end of IR message */
#घोषणा MTK_IR_END(v, p)	  ((v) == MTK_MAX_SAMPLES && (p) == 0)
/* Number of रेजिस्टरs to record the pulse width */
#घोषणा MTK_CHKDATA_SZ		  17
/* Sample period in us */
#घोषणा MTK_IR_SAMPLE		  46

क्रमागत mtk_fields अणु
	/* Register to setting software sampling period */
	MTK_CHK_PERIOD,
	/* Register to setting hardware sampling period */
	MTK_HW_PERIOD,
पूर्ण;

क्रमागत mtk_regs अणु
	/* Register to clear state of state machine */
	MTK_IRCLR_REG,
	/* Register containing pulse width data */
	MTK_CHKDATA_REG,
	/* Register to enable IR पूर्णांकerrupt */
	MTK_IRINT_EN_REG,
	/* Register to ack IR पूर्णांकerrupt */
	MTK_IRINT_CLR_REG
पूर्ण;

अटल स्थिर u32 mt7623_regs[] = अणु
	[MTK_IRCLR_REG] =	0x20,
	[MTK_CHKDATA_REG] =	0x88,
	[MTK_IRINT_EN_REG] =	0xcc,
	[MTK_IRINT_CLR_REG] =	0xd0,
पूर्ण;

अटल स्थिर u32 mt7622_regs[] = अणु
	[MTK_IRCLR_REG] =	0x18,
	[MTK_CHKDATA_REG] =	0x30,
	[MTK_IRINT_EN_REG] =	0x1c,
	[MTK_IRINT_CLR_REG] =	0x20,
पूर्ण;

काष्ठा mtk_field_type अणु
	u32 reg;
	u8 offset;
	u32 mask;
पूर्ण;

/*
 * काष्ठा mtk_ir_data -	This is the काष्ठाure holding all dअगरferences among
			various hardwares
 * @regs:		The poपूर्णांकer to the array holding रेजिस्टरs offset
 * @fields:		The poपूर्णांकer to the array holding fields location
 * @भाग:		The पूर्णांकernal भागisor क्रम the based reference घड़ी
 * @ok_count:		The count indicating the completion of IR data
 *			receiving when count is reached
 * @hw_period:		The value indicating the hardware sampling period
 */
काष्ठा mtk_ir_data अणु
	स्थिर u32 *regs;
	स्थिर काष्ठा mtk_field_type *fields;
	u8 भाग;
	u8 ok_count;
	u32 hw_period;
पूर्ण;

अटल स्थिर काष्ठा mtk_field_type mt7623_fields[] = अणु
	[MTK_CHK_PERIOD] = अणु0x10, 8, GENMASK(20, 8)पूर्ण,
	[MTK_HW_PERIOD] = अणु0x10, 0, GENMASK(7, 0)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_field_type mt7622_fields[] = अणु
	[MTK_CHK_PERIOD] = अणु0x24, 0, GENMASK(24, 0)पूर्ण,
	[MTK_HW_PERIOD] = अणु0x10, 0, GENMASK(24, 0)पूर्ण,
पूर्ण;

/*
 * काष्ठा mtk_ir -	This is the मुख्य datasructure क्रम holding the state
 *			of the driver
 * @dev:		The device poपूर्णांकer
 * @rc:			The rc instrance
 * @base:		The mapped रेजिस्टर i/o base
 * @irq:		The IRQ that we are using
 * @clk:		The घड़ी that IR पूर्णांकernal is using
 * @bus:		The घड़ी that software decoder is using
 * @data:		Holding specअगरic data क्रम vaious platक्रमm
 */
काष्ठा mtk_ir अणु
	काष्ठा device	*dev;
	काष्ठा rc_dev	*rc;
	व्योम __iomem	*base;
	पूर्णांक		irq;
	काष्ठा clk	*clk;
	काष्ठा clk	*bus;
	स्थिर काष्ठा mtk_ir_data *data;
पूर्ण;

अटल अंतरभूत u32 mtk_chkdata_reg(काष्ठा mtk_ir *ir, u32 i)
अणु
	वापस ir->data->regs[MTK_CHKDATA_REG] + 4 * i;
पूर्ण

अटल अंतरभूत u32 mtk_chk_period(काष्ठा mtk_ir *ir)
अणु
	u32 val;

	/*
	 * Period क्रम software decoder used in the
	 * unit of raw software sampling
	 */
	val = DIV_ROUND_CLOSEST(clk_get_rate(ir->bus),
				USEC_PER_SEC * ir->data->भाग / MTK_IR_SAMPLE);

	dev_dbg(ir->dev, "@pwm clk  = \t%lu\n",
		clk_get_rate(ir->bus) / ir->data->भाग);
	dev_dbg(ir->dev, "@chkperiod = %08x\n", val);

	वापस val;
पूर्ण

अटल व्योम mtk_w32_mask(काष्ठा mtk_ir *ir, u32 val, u32 mask, अचिन्हित पूर्णांक reg)
अणु
	u32 पंचांगp;

	पंचांगp = __raw_पढ़ोl(ir->base + reg);
	पंचांगp = (पंचांगp & ~mask) | val;
	__raw_ग_लिखोl(पंचांगp, ir->base + reg);
पूर्ण

अटल व्योम mtk_w32(काष्ठा mtk_ir *ir, u32 val, अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl(val, ir->base + reg);
पूर्ण

अटल u32 mtk_r32(काष्ठा mtk_ir *ir, अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(ir->base + reg);
पूर्ण

अटल अंतरभूत व्योम mtk_irq_disable(काष्ठा mtk_ir *ir, u32 mask)
अणु
	u32 val;

	val = mtk_r32(ir, ir->data->regs[MTK_IRINT_EN_REG]);
	mtk_w32(ir, val & ~mask, ir->data->regs[MTK_IRINT_EN_REG]);
पूर्ण

अटल अंतरभूत व्योम mtk_irq_enable(काष्ठा mtk_ir *ir, u32 mask)
अणु
	u32 val;

	val = mtk_r32(ir, ir->data->regs[MTK_IRINT_EN_REG]);
	mtk_w32(ir, val | mask, ir->data->regs[MTK_IRINT_EN_REG]);
पूर्ण

अटल irqवापस_t mtk_ir_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा mtk_ir *ir = dev_id;
	u8  wid = 0;
	u32 i, j, val;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	/*
	 * Reset decoder state machine explicitly is required
	 * because 1) the दीर्घest duration क्रम space MTK IR hardware
	 * could record is not safely दीर्घ. e.g  12ms अगर rx resolution
	 * is 46us by शेष. There is still the risk to satisfying
	 * every decoder to reset themselves through दीर्घ enough
	 * trailing spaces and 2) the IRQ handler guarantees that
	 * start of IR message is always contained in and starting
	 * from रेजिस्टर mtk_chkdata_reg(ir, i).
	 */
	ir_raw_event_reset(ir->rc);

	/* First message must be pulse */
	rawir.pulse = false;

	/* Handle all pulse and space IR controller captures */
	क्रम (i = 0 ; i < MTK_CHKDATA_SZ ; i++) अणु
		val = mtk_r32(ir, mtk_chkdata_reg(ir, i));
		dev_dbg(ir->dev, "@reg%d=0x%08x\n", i, val);

		क्रम (j = 0 ; j < 4 ; j++) अणु
			wid = (val & (MTK_WIDTH_MASK << j * 8)) >> j * 8;
			rawir.pulse = !rawir.pulse;
			rawir.duration = wid * (MTK_IR_SAMPLE + 1);
			ir_raw_event_store_with_filter(ir->rc, &rawir);
		पूर्ण
	पूर्ण

	/*
	 * The maximum number of edges the IR controller can
	 * hold is MTK_CHKDATA_SZ * 4. So अगर received IR messages
	 * is over the limit, the last incomplete IR message would
	 * be appended trailing space and still would be sent पूर्णांकo
	 * ir-rc-raw to decode. That helps it is possible that it
	 * has enough inक्रमmation to decode a scancode even अगर the
	 * trailing end of the message is missing.
	 */
	अगर (!MTK_IR_END(wid, rawir.pulse)) अणु
		rawir.pulse = false;
		rawir.duration = MTK_MAX_SAMPLES * (MTK_IR_SAMPLE + 1);
		ir_raw_event_store_with_filter(ir->rc, &rawir);
	पूर्ण

	ir_raw_event_handle(ir->rc);

	/*
	 * Restart controller क्रम the next receive that would
	 * clear up all CHKDATA रेजिस्टरs
	 */
	mtk_w32_mask(ir, 0x1, MTK_IRCLR, ir->data->regs[MTK_IRCLR_REG]);

	/* Clear पूर्णांकerrupt status */
	mtk_w32_mask(ir, 0x1, MTK_IRINT_CLR,
		     ir->data->regs[MTK_IRINT_CLR_REG]);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा mtk_ir_data mt7623_data = अणु
	.regs = mt7623_regs,
	.fields = mt7623_fields,
	.ok_count = 0xf,
	.hw_period = 0xff,
	.भाग	= 4,
पूर्ण;

अटल स्थिर काष्ठा mtk_ir_data mt7622_data = अणु
	.regs = mt7622_regs,
	.fields = mt7622_fields,
	.ok_count = 0xf,
	.hw_period = 0xffff,
	.भाग	= 32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_ir_match[] = अणु
	अणु .compatible = "mediatek,mt7623-cir", .data = &mt7623_dataपूर्ण,
	अणु .compatible = "mediatek,mt7622-cir", .data = &mt7622_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_ir_match);

अटल पूर्णांक mtk_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node;
	काष्ठा resource *res;
	काष्ठा mtk_ir *ir;
	u32 val;
	पूर्णांक ret = 0;
	स्थिर अक्षर *map_name;

	ir = devm_kzalloc(dev, माप(काष्ठा mtk_ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	ir->dev = dev;
	ir->data = of_device_get_match_data(dev);

	ir->clk = devm_clk_get(dev, "clk");
	अगर (IS_ERR(ir->clk)) अणु
		dev_err(dev, "failed to get a ir clock.\n");
		वापस PTR_ERR(ir->clk);
	पूर्ण

	ir->bus = devm_clk_get(dev, "bus");
	अगर (IS_ERR(ir->bus)) अणु
		/*
		 * For compatibility with older device trees try unnamed
		 * ir->bus uses the same घड़ी as ir->घड़ी.
		 */
		ir->bus = ir->clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ir->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ir->base))
		वापस PTR_ERR(ir->base);

	ir->rc = devm_rc_allocate_device(dev, RC_DRIVER_IR_RAW);
	अगर (!ir->rc) अणु
		dev_err(dev, "failed to allocate device\n");
		वापस -ENOMEM;
	पूर्ण

	ir->rc->priv = ir;
	ir->rc->device_name = MTK_IR_DEV;
	ir->rc->input_phys = MTK_IR_DEV "/input0";
	ir->rc->input_id.bustype = BUS_HOST;
	ir->rc->input_id.venकरोr = 0x0001;
	ir->rc->input_id.product = 0x0001;
	ir->rc->input_id.version = 0x0001;
	map_name = of_get_property(dn, "linux,rc-map-name", शून्य);
	ir->rc->map_name = map_name ?: RC_MAP_EMPTY;
	ir->rc->dev.parent = dev;
	ir->rc->driver_name = MTK_IR_DEV;
	ir->rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	ir->rc->rx_resolution = MTK_IR_SAMPLE;
	ir->rc->समयout = MTK_MAX_SAMPLES * (MTK_IR_SAMPLE + 1);

	ret = devm_rc_रेजिस्टर_device(dev, ir->rc);
	अगर (ret) अणु
		dev_err(dev, "failed to register rc device\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ir);

	ir->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ir->irq < 0)
		वापस -ENODEV;

	अगर (clk_prepare_enable(ir->clk)) अणु
		dev_err(dev, "try to enable ir_clk failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (clk_prepare_enable(ir->bus)) अणु
		dev_err(dev, "try to enable ir_clk failed\n");
		ret = -EINVAL;
		जाओ निकास_clkdisable_clk;
	पूर्ण

	/*
	 * Enable पूर्णांकerrupt after proper hardware
	 * setup and IRQ handler registration
	 */
	mtk_irq_disable(ir, MTK_IRINT_EN);

	ret = devm_request_irq(dev, ir->irq, mtk_ir_irq, 0, MTK_IR_DEV, ir);
	अगर (ret) अणु
		dev_err(dev, "failed request irq\n");
		जाओ निकास_clkdisable_bus;
	पूर्ण

	/*
	 * Setup software sample period as the reference of software decoder
	 */
	val = (mtk_chk_period(ir) << ir->data->fields[MTK_CHK_PERIOD].offset) &
	       ir->data->fields[MTK_CHK_PERIOD].mask;
	mtk_w32_mask(ir, val, ir->data->fields[MTK_CHK_PERIOD].mask,
		     ir->data->fields[MTK_CHK_PERIOD].reg);

	/*
	 * Setup hardware sampling period used to setup the proper समयout क्रम
	 * indicating end of IR receiving completion
	 */
	val = (ir->data->hw_period << ir->data->fields[MTK_HW_PERIOD].offset) &
	       ir->data->fields[MTK_HW_PERIOD].mask;
	mtk_w32_mask(ir, val, ir->data->fields[MTK_HW_PERIOD].mask,
		     ir->data->fields[MTK_HW_PERIOD].reg);

	/* Set de-glitch counter */
	mtk_w32_mask(ir, MTK_DG_CNT(1), MTK_DG_CNT_MASK, MTK_IRTHD);

	/* Enable IR and PWM */
	val = mtk_r32(ir, MTK_CONFIG_HIGH_REG);
	val |= MTK_OK_COUNT(ir->data->ok_count) |  MTK_PWM_EN | MTK_IR_EN;
	mtk_w32(ir, val, MTK_CONFIG_HIGH_REG);

	mtk_irq_enable(ir, MTK_IRINT_EN);

	dev_info(dev, "Initialized MT7623 IR driver, sample period = %dus\n",
		 MTK_IR_SAMPLE);

	वापस 0;

निकास_clkdisable_bus:
	clk_disable_unprepare(ir->bus);
निकास_clkdisable_clk:
	clk_disable_unprepare(ir->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_ir *ir = platक्रमm_get_drvdata(pdev);

	/*
	 * Aव्योम contention between हटाओ handler and
	 * IRQ handler so that disabling IR पूर्णांकerrupt and
	 * रुकोing क्रम pending IRQ handler to complete
	 */
	mtk_irq_disable(ir, MTK_IRINT_EN);
	synchronize_irq(ir->irq);

	clk_disable_unprepare(ir->bus);
	clk_disable_unprepare(ir->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_ir_driver = अणु
	.probe          = mtk_ir_probe,
	.हटाओ         = mtk_ir_हटाओ,
	.driver = अणु
		.name = MTK_IR_DEV,
		.of_match_table = mtk_ir_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_ir_driver);

MODULE_DESCRIPTION("Mediatek IR Receiver Controller Driver");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL");
