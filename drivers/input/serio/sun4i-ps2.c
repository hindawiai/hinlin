<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Driver क्रम Allwinner A10 PS2 host controller
 *
 *	Author: Vishnu Patekar <vishnupatekar0510@gmail.com>
 *		Aaron.maoye <leafy.myeh@newbietech.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRIVER_NAME		"sun4i-ps2"

/* रेजिस्टर offset definitions */
#घोषणा PS2_REG_GCTL		0x00	/* PS2 Module Global Control Reg */
#घोषणा PS2_REG_DATA		0x04	/* PS2 Module Data Reg		*/
#घोषणा PS2_REG_LCTL		0x08	/* PS2 Module Line Control Reg */
#घोषणा PS2_REG_LSTS		0x0C	/* PS2 Module Line Status Reg	*/
#घोषणा PS2_REG_FCTL		0x10	/* PS2 Module FIFO Control Reg */
#घोषणा PS2_REG_FSTS		0x14	/* PS2 Module FIFO Status Reg	*/
#घोषणा PS2_REG_CLKDR		0x18	/* PS2 Module Clock Divider Reg*/

/*  PS2 GLOBAL CONTROL REGISTER PS2_GCTL */
#घोषणा PS2_GCTL_INTFLAG	BIT(4)
#घोषणा PS2_GCTL_INTEN		BIT(3)
#घोषणा PS2_GCTL_RESET		BIT(2)
#घोषणा PS2_GCTL_MASTER		BIT(1)
#घोषणा PS2_GCTL_BUSEN		BIT(0)

/* PS2 LINE CONTROL REGISTER */
#घोषणा PS2_LCTL_NOACK		BIT(18)
#घोषणा PS2_LCTL_TXDTOEN	BIT(8)
#घोषणा PS2_LCTL_STOPERREN	BIT(3)
#घोषणा PS2_LCTL_ACKERREN	BIT(2)
#घोषणा PS2_LCTL_PARERREN	BIT(1)
#घोषणा PS2_LCTL_RXDTOEN	BIT(0)

/* PS2 LINE STATUS REGISTER */
#घोषणा PS2_LSTS_TXTDO		BIT(8)
#घोषणा PS2_LSTS_STOPERR	BIT(3)
#घोषणा PS2_LSTS_ACKERR		BIT(2)
#घोषणा PS2_LSTS_PARERR		BIT(1)
#घोषणा PS2_LSTS_RXTDO		BIT(0)

#घोषणा PS2_LINE_ERROR_BIT \
	(PS2_LSTS_TXTDO | PS2_LSTS_STOPERR | PS2_LSTS_ACKERR | \
	PS2_LSTS_PARERR | PS2_LSTS_RXTDO)

/* PS2 FIFO CONTROL REGISTER */
#घोषणा PS2_FCTL_TXRST		BIT(17)
#घोषणा PS2_FCTL_RXRST		BIT(16)
#घोषणा PS2_FCTL_TXUFIEN	BIT(10)
#घोषणा PS2_FCTL_TXOFIEN	BIT(9)
#घोषणा PS2_FCTL_TXRDYIEN	BIT(8)
#घोषणा PS2_FCTL_RXUFIEN	BIT(2)
#घोषणा PS2_FCTL_RXOFIEN	BIT(1)
#घोषणा PS2_FCTL_RXRDYIEN	BIT(0)

/* PS2 FIFO STATUS REGISTER */
#घोषणा PS2_FSTS_TXUF		BIT(10)
#घोषणा PS2_FSTS_TXOF		BIT(9)
#घोषणा PS2_FSTS_TXRDY		BIT(8)
#घोषणा PS2_FSTS_RXUF		BIT(2)
#घोषणा PS2_FSTS_RXOF		BIT(1)
#घोषणा PS2_FSTS_RXRDY		BIT(0)

#घोषणा PS2_FIFO_ERROR_BIT \
	(PS2_FSTS_TXUF | PS2_FSTS_TXOF | PS2_FSTS_RXUF | PS2_FSTS_RXOF)

#घोषणा PS2_SAMPLE_CLK		1000000
#घोषणा PS2_SCLK		125000

काष्ठा sun4i_ps2data अणु
	काष्ठा serio *serio;
	काष्ठा device *dev;

	/* IO mapping base */
	व्योम __iomem	*reg_base;

	/* घड़ी management */
	काष्ठा clk	*clk;

	/* irq */
	spinlock_t	lock;
	पूर्णांक		irq;
पूर्ण;

अटल irqवापस_t sun4i_ps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_ps2data *drvdata = dev_id;
	u32 पूर्णांकr_status;
	u32 fअगरo_status;
	अचिन्हित अक्षर byte;
	अचिन्हित पूर्णांक rxflags = 0;
	u32 rval;

	spin_lock(&drvdata->lock);

	/* Get the PS/2 पूर्णांकerrupts and clear them */
	पूर्णांकr_status  = पढ़ोl(drvdata->reg_base + PS2_REG_LSTS);
	fअगरo_status  = पढ़ोl(drvdata->reg_base + PS2_REG_FSTS);

	/* Check line status रेजिस्टर */
	अगर (पूर्णांकr_status & PS2_LINE_ERROR_BIT) अणु
		rxflags = (पूर्णांकr_status & PS2_LINE_ERROR_BIT) ? SERIO_FRAME : 0;
		rxflags |= (पूर्णांकr_status & PS2_LSTS_PARERR) ? SERIO_PARITY : 0;
		rxflags |= (पूर्णांकr_status & PS2_LSTS_PARERR) ? SERIO_TIMEOUT : 0;

		rval = PS2_LSTS_TXTDO | PS2_LSTS_STOPERR | PS2_LSTS_ACKERR |
			PS2_LSTS_PARERR | PS2_LSTS_RXTDO;
		ग_लिखोl(rval, drvdata->reg_base + PS2_REG_LSTS);
	पूर्ण

	/* Check FIFO status रेजिस्टर */
	अगर (fअगरo_status & PS2_FIFO_ERROR_BIT) अणु
		rval = PS2_FSTS_TXUF | PS2_FSTS_TXOF | PS2_FSTS_TXRDY |
			PS2_FSTS_RXUF | PS2_FSTS_RXOF | PS2_FSTS_RXRDY;
		ग_लिखोl(rval, drvdata->reg_base + PS2_REG_FSTS);
	पूर्ण

	rval = (fअगरo_status >> 16) & 0x3;
	जबतक (rval--) अणु
		byte = पढ़ोl(drvdata->reg_base + PS2_REG_DATA) & 0xff;
		serio_पूर्णांकerrupt(drvdata->serio, byte, rxflags);
	पूर्ण

	ग_लिखोl(पूर्णांकr_status, drvdata->reg_base + PS2_REG_LSTS);
	ग_लिखोl(fअगरo_status, drvdata->reg_base + PS2_REG_FSTS);

	spin_unlock(&drvdata->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_ps2_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा sun4i_ps2data *drvdata = serio->port_data;
	u32 src_clk = 0;
	u32 clk_scdf;
	u32 clk_pcdf;
	u32 rval;
	अचिन्हित दीर्घ flags;

	/* Set line control and enable पूर्णांकerrupt */
	rval = PS2_LCTL_STOPERREN | PS2_LCTL_ACKERREN
		| PS2_LCTL_PARERREN | PS2_LCTL_RXDTOEN;
	ग_लिखोl(rval, drvdata->reg_base + PS2_REG_LCTL);

	/* Reset FIFO */
	rval = PS2_FCTL_TXRST | PS2_FCTL_RXRST | PS2_FCTL_TXUFIEN
		| PS2_FCTL_TXOFIEN | PS2_FCTL_RXUFIEN
		| PS2_FCTL_RXOFIEN | PS2_FCTL_RXRDYIEN;

	ग_लिखोl(rval, drvdata->reg_base + PS2_REG_FCTL);

	src_clk = clk_get_rate(drvdata->clk);
	/* Set घड़ी भागider रेजिस्टर */
	clk_scdf = src_clk / PS2_SAMPLE_CLK - 1;
	clk_pcdf = PS2_SAMPLE_CLK / PS2_SCLK - 1;
	rval = (clk_scdf << 8) | clk_pcdf;
	ग_लिखोl(rval, drvdata->reg_base + PS2_REG_CLKDR);

	/* Set global control रेजिस्टर */
	rval = PS2_GCTL_RESET | PS2_GCTL_INTEN | PS2_GCTL_MASTER
		| PS2_GCTL_BUSEN;

	spin_lock_irqsave(&drvdata->lock, flags);
	ग_लिखोl(rval, drvdata->reg_base + PS2_REG_GCTL);
	spin_unlock_irqrestore(&drvdata->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sun4i_ps2_बंद(काष्ठा serio *serio)
अणु
	काष्ठा sun4i_ps2data *drvdata = serio->port_data;
	u32 rval;

	/* Shut off the पूर्णांकerrupt */
	rval = पढ़ोl(drvdata->reg_base + PS2_REG_GCTL);
	ग_लिखोl(rval & ~(PS2_GCTL_INTEN), drvdata->reg_base + PS2_REG_GCTL);

	synchronize_irq(drvdata->irq);
पूर्ण

अटल पूर्णांक sun4i_ps2_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ expire = jअगरfies + msecs_to_jअगरfies(10000);
	काष्ठा sun4i_ps2data *drvdata = serio->port_data;

	करो अणु
		अगर (पढ़ोl(drvdata->reg_base + PS2_REG_FSTS) & PS2_FSTS_TXRDY) अणु
			ग_लिखोl(val, drvdata->reg_base + PS2_REG_DATA);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire));

	वापस SERIO_TIMEOUT;
पूर्ण

अटल पूर्णांक sun4i_ps2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res; /* IO mem resources */
	काष्ठा sun4i_ps2data *drvdata;
	काष्ठा serio *serio;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error;

	drvdata = kzalloc(माप(काष्ठा sun4i_ps2data), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!drvdata || !serio) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	spin_lock_init(&drvdata->lock);

	/* IO */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to locate registers\n");
		error = -ENXIO;
		जाओ err_मुक्त_mem;
	पूर्ण

	drvdata->reg_base = ioremap(res->start, resource_size(res));
	अगर (!drvdata->reg_base) अणु
		dev_err(dev, "failed to map registers\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	drvdata->clk = clk_get(dev, शून्य);
	अगर (IS_ERR(drvdata->clk)) अणु
		error = PTR_ERR(drvdata->clk);
		dev_err(dev, "couldn't get clock %d\n", error);
		जाओ err_ioremap;
	पूर्ण

	error = clk_prepare_enable(drvdata->clk);
	अगर (error) अणु
		dev_err(dev, "failed to enable clock %d\n", error);
		जाओ err_clk;
	पूर्ण

	serio->id.type = SERIO_8042;
	serio->ग_लिखो = sun4i_ps2_ग_लिखो;
	serio->खोलो = sun4i_ps2_खोलो;
	serio->बंद = sun4i_ps2_बंद;
	serio->port_data = drvdata;
	serio->dev.parent = dev;
	strlcpy(serio->name, dev_name(dev), माप(serio->name));
	strlcpy(serio->phys, dev_name(dev), माप(serio->phys));

	/* shutoff पूर्णांकerrupt */
	ग_लिखोl(0, drvdata->reg_base + PS2_REG_GCTL);

	/* Get IRQ क्रम the device */
	drvdata->irq = platक्रमm_get_irq(pdev, 0);
	अगर (drvdata->irq < 0) अणु
		error = drvdata->irq;
		जाओ err_disable_clk;
	पूर्ण

	drvdata->serio = serio;
	drvdata->dev = dev;

	error = request_irq(drvdata->irq, sun4i_ps2_पूर्णांकerrupt, 0,
			    DRIVER_NAME, drvdata);
	अगर (error) अणु
		dev_err(drvdata->dev, "failed to allocate interrupt %d: %d\n",
			drvdata->irq, error);
		जाओ err_disable_clk;
	पूर्ण

	serio_रेजिस्टर_port(serio);
	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;	/* success */

err_disable_clk:
	clk_disable_unprepare(drvdata->clk);
err_clk:
	clk_put(drvdata->clk);
err_ioremap:
	iounmap(drvdata->reg_base);
err_मुक्त_mem:
	kमुक्त(serio);
	kमुक्त(drvdata);
	वापस error;
पूर्ण

अटल पूर्णांक sun4i_ps2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_ps2data *drvdata = platक्रमm_get_drvdata(pdev);

	serio_unरेजिस्टर_port(drvdata->serio);

	मुक्त_irq(drvdata->irq, drvdata);

	clk_disable_unprepare(drvdata->clk);
	clk_put(drvdata->clk);

	iounmap(drvdata->reg_base);

	kमुक्त(drvdata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_ps2_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-ps2", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sun4i_ps2_match);

अटल काष्ठा platक्रमm_driver sun4i_ps2_driver = अणु
	.probe		= sun4i_ps2_probe,
	.हटाओ		= sun4i_ps2_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = sun4i_ps2_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_ps2_driver);

MODULE_AUTHOR("Vishnu Patekar <vishnupatekar0510@gmail.com>");
MODULE_AUTHOR("Aaron.maoye <leafy.myeh@newbietech.com>");
MODULE_DESCRIPTION("Allwinner A10/Sun4i PS/2 driver");
MODULE_LICENSE("GPL v2");
