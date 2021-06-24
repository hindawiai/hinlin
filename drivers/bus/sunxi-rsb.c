<शैली गुरु>
/*
 * RSB (Reduced Serial Bus) driver.
 *
 * Author: Chen-Yu Tsai <wens@csie.org>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * The RSB controller looks like an SMBus controller which only supports
 * byte and word data transfers. But, it dअगरfers from standard SMBus
 * protocol on several aspects:
 * - it uses addresses set at runसमय to address slaves. Runसमय addresses
 *   are sent to slaves using their 12bit hardware addresses. Up to 15
 *   runसमय addresses are available.
 * - it adds a parity bit every 8bits of data and address क्रम पढ़ो and
 *   ग_लिखो accesses; this replaces the ack bit
 * - only one पढ़ो access is required to पढ़ो a byte (instead of a ग_लिखो
 *   followed by a पढ़ो access in standard SMBus protocol)
 * - there's no Ack bit after each पढ़ो access
 *
 * This means this bus cannot be used to पूर्णांकerface with standard SMBus
 * devices. Devices known to support this पूर्णांकerface include the AXP223,
 * AXP809, and AXP806 PMICs, and the AC100 audio codec, all from X-Powers.
 *
 * A description of the operation and wire protocol can be found in the
 * RSB section of Allwinner's A80 user manual, which can be found at
 *
 *     https://github.com/allwinner-zh/करोcuments/tree/master/A80
 *
 * This करोcument is officially released by Allwinner.
 *
 * This driver is based on i2c-sun6i-p2wi.c, the P2WI bus driver.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunxi-rsb.h>
#समावेश <linux/types.h>

/* RSB रेजिस्टरs */
#घोषणा RSB_CTRL	0x0	/* Global control */
#घोषणा RSB_CCR		0x4	/* Clock control */
#घोषणा RSB_INTE	0x8	/* Interrupt controls */
#घोषणा RSB_INTS	0xc	/* Interrupt status */
#घोषणा RSB_ADDR	0x10	/* Address to send with पढ़ो/ग_लिखो command */
#घोषणा RSB_DATA	0x1c	/* Data to पढ़ो/ग_लिखो */
#घोषणा RSB_LCR		0x24	/* Line control */
#घोषणा RSB_DMCR	0x28	/* Device mode (init) control */
#घोषणा RSB_CMD		0x2c	/* RSB Command */
#घोषणा RSB_DAR		0x30	/* Device address / runसमय address */

/* CTRL fields */
#घोषणा RSB_CTRL_START_TRANS		BIT(7)
#घोषणा RSB_CTRL_ABORT_TRANS		BIT(6)
#घोषणा RSB_CTRL_GLOBAL_INT_ENB		BIT(1)
#घोषणा RSB_CTRL_SOFT_RST		BIT(0)

/* CLK CTRL fields */
#घोषणा RSB_CCR_SDA_OUT_DELAY(v)	(((v) & 0x7) << 8)
#घोषणा RSB_CCR_MAX_CLK_DIV		0xff
#घोषणा RSB_CCR_CLK_DIV(v)		((v) & RSB_CCR_MAX_CLK_DIV)

/* STATUS fields */
#घोषणा RSB_INTS_TRANS_ERR_ACK		BIT(16)
#घोषणा RSB_INTS_TRANS_ERR_DATA_BIT(v)	(((v) >> 8) & 0xf)
#घोषणा RSB_INTS_TRANS_ERR_DATA		GENMASK(11, 8)
#घोषणा RSB_INTS_LOAD_BSY		BIT(2)
#घोषणा RSB_INTS_TRANS_ERR		BIT(1)
#घोषणा RSB_INTS_TRANS_OVER		BIT(0)

/* LINE CTRL fields*/
#घोषणा RSB_LCR_SCL_STATE		BIT(5)
#घोषणा RSB_LCR_SDA_STATE		BIT(4)
#घोषणा RSB_LCR_SCL_CTL			BIT(3)
#घोषणा RSB_LCR_SCL_CTL_EN		BIT(2)
#घोषणा RSB_LCR_SDA_CTL			BIT(1)
#घोषणा RSB_LCR_SDA_CTL_EN		BIT(0)

/* DEVICE MODE CTRL field values */
#घोषणा RSB_DMCR_DEVICE_START		BIT(31)
#घोषणा RSB_DMCR_MODE_DATA		(0x7c << 16)
#घोषणा RSB_DMCR_MODE_REG		(0x3e << 8)
#घोषणा RSB_DMCR_DEV_ADDR		0x00

/* CMD values */
#घोषणा RSB_CMD_RD8			0x8b
#घोषणा RSB_CMD_RD16			0x9c
#घोषणा RSB_CMD_RD32			0xa6
#घोषणा RSB_CMD_WR8			0x4e
#घोषणा RSB_CMD_WR16			0x59
#घोषणा RSB_CMD_WR32			0x63
#घोषणा RSB_CMD_STRA			0xe8

/* DAR fields */
#घोषणा RSB_DAR_RTA(v)			(((v) & 0xff) << 16)
#घोषणा RSB_DAR_DA(v)			((v) & 0xffff)

#घोषणा RSB_MAX_FREQ			20000000

#घोषणा RSB_CTRL_NAME			"sunxi-rsb"

काष्ठा sunxi_rsb_addr_map अणु
	u16 hwaddr;
	u8 rtaddr;
पूर्ण;

काष्ठा sunxi_rsb अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा reset_control *rstc;
	काष्ठा completion complete;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक status;
	u32 clk_freq;
पूर्ण;

/* bus / slave device related functions */
अटल काष्ठा bus_type sunxi_rsb_bus;

अटल पूर्णांक sunxi_rsb_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस of_driver_match_device(dev, drv);
पूर्ण

अटल पूर्णांक sunxi_rsb_device_probe(काष्ठा device *dev)
अणु
	स्थिर काष्ठा sunxi_rsb_driver *drv = to_sunxi_rsb_driver(dev->driver);
	काष्ठा sunxi_rsb_device *rdev = to_sunxi_rsb_device(dev);
	पूर्णांक ret;

	अगर (!drv->probe)
		वापस -ENODEV;

	अगर (!rdev->irq) अणु
		पूर्णांक irq = -ENOENT;

		अगर (dev->of_node)
			irq = of_irq_get(dev->of_node, 0);

		अगर (irq == -EPROBE_DEFER)
			वापस irq;
		अगर (irq < 0)
			irq = 0;

		rdev->irq = irq;
	पूर्ण

	ret = of_clk_set_शेषs(dev->of_node, false);
	अगर (ret < 0)
		वापस ret;

	वापस drv->probe(rdev);
पूर्ण

अटल पूर्णांक sunxi_rsb_device_हटाओ(काष्ठा device *dev)
अणु
	स्थिर काष्ठा sunxi_rsb_driver *drv = to_sunxi_rsb_driver(dev->driver);

	drv->हटाओ(to_sunxi_rsb_device(dev));

	वापस 0;
पूर्ण

अटल काष्ठा bus_type sunxi_rsb_bus = अणु
	.name		= RSB_CTRL_NAME,
	.match		= sunxi_rsb_device_match,
	.probe		= sunxi_rsb_device_probe,
	.हटाओ		= sunxi_rsb_device_हटाओ,
	.uevent		= of_device_uevent_modalias,
पूर्ण;

अटल व्योम sunxi_rsb_dev_release(काष्ठा device *dev)
अणु
	काष्ठा sunxi_rsb_device *rdev = to_sunxi_rsb_device(dev);

	kमुक्त(rdev);
पूर्ण

/**
 * sunxi_rsb_device_create() - allocate and add an RSB device
 * @rsb:	RSB controller
 * @node:	RSB slave device node
 * @hwaddr:	RSB slave hardware address
 * @rtaddr:	RSB slave runसमय address
 */
अटल काष्ठा sunxi_rsb_device *sunxi_rsb_device_create(काष्ठा sunxi_rsb *rsb,
		काष्ठा device_node *node, u16 hwaddr, u8 rtaddr)
अणु
	पूर्णांक err;
	काष्ठा sunxi_rsb_device *rdev;

	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (!rdev)
		वापस ERR_PTR(-ENOMEM);

	rdev->rsb = rsb;
	rdev->hwaddr = hwaddr;
	rdev->rtaddr = rtaddr;
	rdev->dev.bus = &sunxi_rsb_bus;
	rdev->dev.parent = rsb->dev;
	rdev->dev.of_node = node;
	rdev->dev.release = sunxi_rsb_dev_release;

	dev_set_name(&rdev->dev, "%s-%x", RSB_CTRL_NAME, hwaddr);

	err = device_रेजिस्टर(&rdev->dev);
	अगर (err < 0) अणु
		dev_err(&rdev->dev, "Can't add %s, status %d\n",
			dev_name(&rdev->dev), err);
		जाओ err_device_add;
	पूर्ण

	dev_dbg(&rdev->dev, "device %s registered\n", dev_name(&rdev->dev));

err_device_add:
	put_device(&rdev->dev);

	वापस ERR_PTR(err);
पूर्ण

/**
 * sunxi_rsb_device_unरेजिस्टर(): unरेजिस्टर an RSB device
 * @rdev:	rsb_device to be हटाओd
 */
अटल व्योम sunxi_rsb_device_unरेजिस्टर(काष्ठा sunxi_rsb_device *rdev)
अणु
	device_unरेजिस्टर(&rdev->dev);
पूर्ण

अटल पूर्णांक sunxi_rsb_हटाओ_devices(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा sunxi_rsb_device *rdev = to_sunxi_rsb_device(dev);

	अगर (dev->bus == &sunxi_rsb_bus)
		sunxi_rsb_device_unरेजिस्टर(rdev);

	वापस 0;
पूर्ण

/**
 * sunxi_rsb_driver_रेजिस्टर() - Register device driver with RSB core
 * @rdrv:	device driver to be associated with slave-device.
 *
 * This API will रेजिस्टर the client driver with the RSB framework.
 * It is typically called from the driver's module-init function.
 */
पूर्णांक sunxi_rsb_driver_रेजिस्टर(काष्ठा sunxi_rsb_driver *rdrv)
अणु
	rdrv->driver.bus = &sunxi_rsb_bus;
	वापस driver_रेजिस्टर(&rdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(sunxi_rsb_driver_रेजिस्टर);

/* common code that starts a transfer */
अटल पूर्णांक _sunxi_rsb_run_xfer(काष्ठा sunxi_rsb *rsb)
अणु
	अगर (पढ़ोl(rsb->regs + RSB_CTRL) & RSB_CTRL_START_TRANS) अणु
		dev_dbg(rsb->dev, "RSB transfer still in progress\n");
		वापस -EBUSY;
	पूर्ण

	reinit_completion(&rsb->complete);

	ग_लिखोl(RSB_INTS_LOAD_BSY | RSB_INTS_TRANS_ERR | RSB_INTS_TRANS_OVER,
	       rsb->regs + RSB_INTE);
	ग_लिखोl(RSB_CTRL_START_TRANS | RSB_CTRL_GLOBAL_INT_ENB,
	       rsb->regs + RSB_CTRL);

	अगर (!रुको_क्रम_completion_io_समयout(&rsb->complete,
					    msecs_to_jअगरfies(100))) अणु
		dev_dbg(rsb->dev, "RSB timeout\n");

		/* पात the transfer */
		ग_लिखोl(RSB_CTRL_ABORT_TRANS, rsb->regs + RSB_CTRL);

		/* clear any पूर्णांकerrupt flags */
		ग_लिखोl(पढ़ोl(rsb->regs + RSB_INTS), rsb->regs + RSB_INTS);

		वापस -ETIMEDOUT;
	पूर्ण

	अगर (rsb->status & RSB_INTS_LOAD_BSY) अणु
		dev_dbg(rsb->dev, "RSB busy\n");
		वापस -EBUSY;
	पूर्ण

	अगर (rsb->status & RSB_INTS_TRANS_ERR) अणु
		अगर (rsb->status & RSB_INTS_TRANS_ERR_ACK) अणु
			dev_dbg(rsb->dev, "RSB slave nack\n");
			वापस -EINVAL;
		पूर्ण

		अगर (rsb->status & RSB_INTS_TRANS_ERR_DATA) अणु
			dev_dbg(rsb->dev, "RSB transfer data error\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rsb_पढ़ो(काष्ठा sunxi_rsb *rsb, u8 rtaddr, u8 addr,
			  u32 *buf, माप_प्रकार len)
अणु
	u32 cmd;
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	चयन (len) अणु
	हाल 1:
		cmd = RSB_CMD_RD8;
		अवरोध;
	हाल 2:
		cmd = RSB_CMD_RD16;
		अवरोध;
	हाल 4:
		cmd = RSB_CMD_RD32;
		अवरोध;
	शेष:
		dev_err(rsb->dev, "Invalid access width: %zd\n", len);
		वापस -EINVAL;
	पूर्ण

	ret = pm_runसमय_resume_and_get(rsb->dev);
	अगर (ret)
		वापस ret;

	mutex_lock(&rsb->lock);

	ग_लिखोl(addr, rsb->regs + RSB_ADDR);
	ग_लिखोl(RSB_DAR_RTA(rtaddr), rsb->regs + RSB_DAR);
	ग_लिखोl(cmd, rsb->regs + RSB_CMD);

	ret = _sunxi_rsb_run_xfer(rsb);
	अगर (ret)
		जाओ unlock;

	*buf = पढ़ोl(rsb->regs + RSB_DATA) & GENMASK(len * 8 - 1, 0);

unlock:
	mutex_unlock(&rsb->lock);

	pm_runसमय_mark_last_busy(rsb->dev);
	pm_runसमय_put_स्वतःsuspend(rsb->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_rsb_ग_लिखो(काष्ठा sunxi_rsb *rsb, u8 rtaddr, u8 addr,
			   स्थिर u32 *buf, माप_प्रकार len)
अणु
	u32 cmd;
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	चयन (len) अणु
	हाल 1:
		cmd = RSB_CMD_WR8;
		अवरोध;
	हाल 2:
		cmd = RSB_CMD_WR16;
		अवरोध;
	हाल 4:
		cmd = RSB_CMD_WR32;
		अवरोध;
	शेष:
		dev_err(rsb->dev, "Invalid access width: %zd\n", len);
		वापस -EINVAL;
	पूर्ण

	ret = pm_runसमय_resume_and_get(rsb->dev);
	अगर (ret)
		वापस ret;

	mutex_lock(&rsb->lock);

	ग_लिखोl(addr, rsb->regs + RSB_ADDR);
	ग_लिखोl(RSB_DAR_RTA(rtaddr), rsb->regs + RSB_DAR);
	ग_लिखोl(*buf, rsb->regs + RSB_DATA);
	ग_लिखोl(cmd, rsb->regs + RSB_CMD);
	ret = _sunxi_rsb_run_xfer(rsb);

	mutex_unlock(&rsb->lock);

	pm_runसमय_mark_last_busy(rsb->dev);
	pm_runसमय_put_स्वतःsuspend(rsb->dev);

	वापस ret;
पूर्ण

/* RSB regmap functions */
काष्ठा sunxi_rsb_ctx अणु
	काष्ठा sunxi_rsb_device *rdev;
	पूर्णांक size;
पूर्ण;

अटल पूर्णांक regmap_sunxi_rsb_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक *val)
अणु
	काष्ठा sunxi_rsb_ctx *ctx = context;
	काष्ठा sunxi_rsb_device *rdev = ctx->rdev;

	अगर (reg > 0xff)
		वापस -EINVAL;

	वापस sunxi_rsb_पढ़ो(rdev->rsb, rdev->rtaddr, reg, val, ctx->size);
पूर्ण

अटल पूर्णांक regmap_sunxi_rsb_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				      अचिन्हित पूर्णांक val)
अणु
	काष्ठा sunxi_rsb_ctx *ctx = context;
	काष्ठा sunxi_rsb_device *rdev = ctx->rdev;

	वापस sunxi_rsb_ग_लिखो(rdev->rsb, rdev->rtaddr, reg, &val, ctx->size);
पूर्ण

अटल व्योम regmap_sunxi_rsb_मुक्त_ctx(व्योम *context)
अणु
	काष्ठा sunxi_rsb_ctx *ctx = context;

	kमुक्त(ctx);
पूर्ण

अटल काष्ठा regmap_bus regmap_sunxi_rsb = अणु
	.reg_ग_लिखो = regmap_sunxi_rsb_reg_ग_लिखो,
	.reg_पढ़ो = regmap_sunxi_rsb_reg_पढ़ो,
	.मुक्त_context = regmap_sunxi_rsb_मुक्त_ctx,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
पूर्ण;

अटल काष्ठा sunxi_rsb_ctx *regmap_sunxi_rsb_init_ctx(काष्ठा sunxi_rsb_device *rdev,
		स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा sunxi_rsb_ctx *ctx;

	चयन (config->val_bits) अणु
	हाल 8:
	हाल 16:
	हाल 32:
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->rdev = rdev;
	ctx->size = config->val_bits / 8;

	वापस ctx;
पूर्ण

काष्ठा regmap *__devm_regmap_init_sunxi_rsb(काष्ठा sunxi_rsb_device *rdev,
					    स्थिर काष्ठा regmap_config *config,
					    काष्ठा lock_class_key *lock_key,
					    स्थिर अक्षर *lock_name)
अणु
	काष्ठा sunxi_rsb_ctx *ctx = regmap_sunxi_rsb_init_ctx(rdev, config);

	अगर (IS_ERR(ctx))
		वापस ERR_CAST(ctx);

	वापस __devm_regmap_init(&rdev->dev, &regmap_sunxi_rsb, ctx, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_sunxi_rsb);

/* RSB controller driver functions */
अटल irqवापस_t sunxi_rsb_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sunxi_rsb *rsb = dev_id;
	u32 status;

	status = पढ़ोl(rsb->regs + RSB_INTS);
	rsb->status = status;

	/* Clear पूर्णांकerrupts */
	status &= (RSB_INTS_LOAD_BSY | RSB_INTS_TRANS_ERR |
		   RSB_INTS_TRANS_OVER);
	ग_लिखोl(status, rsb->regs + RSB_INTS);

	complete(&rsb->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sunxi_rsb_init_device_mode(काष्ठा sunxi_rsb *rsb)
अणु
	पूर्णांक ret = 0;
	u32 reg;

	/* send init sequence */
	ग_लिखोl(RSB_DMCR_DEVICE_START | RSB_DMCR_MODE_DATA |
	       RSB_DMCR_MODE_REG | RSB_DMCR_DEV_ADDR, rsb->regs + RSB_DMCR);

	पढ़ोl_poll_समयout(rsb->regs + RSB_DMCR, reg,
			   !(reg & RSB_DMCR_DEVICE_START), 100, 250000);
	अगर (reg & RSB_DMCR_DEVICE_START)
		ret = -ETIMEDOUT;

	/* clear पूर्णांकerrupt status bits */
	ग_लिखोl(पढ़ोl(rsb->regs + RSB_INTS), rsb->regs + RSB_INTS);

	वापस ret;
पूर्ण

/*
 * There are 15 valid runसमय addresses, though Allwinner typically
 * skips the first, क्रम unknown reasons, and uses the following three.
 *
 * 0x17, 0x2d, 0x3a, 0x4e, 0x59, 0x63, 0x74, 0x8b,
 * 0x9c, 0xa6, 0xb1, 0xc5, 0xd2, 0xe8, 0xff
 *
 * No designs with 2 RSB slave devices sharing identical hardware
 * addresses on the same bus have been seen in the wild. All designs
 * use 0x2d क्रम the primary PMIC, 0x3a क्रम the secondary PMIC अगर
 * there is one, and 0x45 क्रम peripheral ICs.
 *
 * The hardware करोes not seem to support re-setting runसमय addresses.
 * Attempts to करो so result in the slave devices वापसing a NACK.
 * Hence we just hardcode the mapping here, like Allwinner करोes.
 */

अटल स्थिर काष्ठा sunxi_rsb_addr_map sunxi_rsb_addr_maps[] = अणु
	अणु 0x3a3, 0x2d पूर्ण, /* Primary PMIC: AXP223, AXP809, AXP81X, ... */
	अणु 0x745, 0x3a पूर्ण, /* Secondary PMIC: AXP806, ... */
	अणु 0xe89, 0x4e पूर्ण, /* Peripheral IC: AC100, ... */
पूर्ण;

अटल u8 sunxi_rsb_get_rtaddr(u16 hwaddr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sunxi_rsb_addr_maps); i++)
		अगर (hwaddr == sunxi_rsb_addr_maps[i].hwaddr)
			वापस sunxi_rsb_addr_maps[i].rtaddr;

	वापस 0; /* 0 is an invalid runसमय address */
पूर्ण

अटल पूर्णांक of_rsb_रेजिस्टर_devices(काष्ठा sunxi_rsb *rsb)
अणु
	काष्ठा device *dev = rsb->dev;
	काष्ठा device_node *child, *np = dev->of_node;
	u32 hwaddr;
	u8 rtaddr;
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	/* Runसमय addresses क्रम all slaves should be set first */
	क्रम_each_available_child_of_node(np, child) अणु
		dev_dbg(dev, "setting child %pOF runtime address\n",
			child);

		ret = of_property_पढ़ो_u32(child, "reg", &hwaddr);
		अगर (ret) अणु
			dev_err(dev, "%pOF: invalid 'reg' property: %d\n",
				child, ret);
			जारी;
		पूर्ण

		rtaddr = sunxi_rsb_get_rtaddr(hwaddr);
		अगर (!rtaddr) अणु
			dev_err(dev, "%pOF: unknown hardware device address\n",
				child);
			जारी;
		पूर्ण

		/*
		 * Since no devices have been रेजिस्टरed yet, we are the
		 * only ones using the bus, we can skip locking the bus.
		 */

		/* setup command parameters */
		ग_लिखोl(RSB_CMD_STRA, rsb->regs + RSB_CMD);
		ग_लिखोl(RSB_DAR_RTA(rtaddr) | RSB_DAR_DA(hwaddr),
		       rsb->regs + RSB_DAR);

		/* send command */
		ret = _sunxi_rsb_run_xfer(rsb);
		अगर (ret)
			dev_warn(dev, "%pOF: set runtime address failed: %d\n",
				 child, ret);
	पूर्ण

	/* Then we start adding devices and probing them */
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा sunxi_rsb_device *rdev;

		dev_dbg(dev, "adding child %pOF\n", child);

		ret = of_property_पढ़ो_u32(child, "reg", &hwaddr);
		अगर (ret)
			जारी;

		rtaddr = sunxi_rsb_get_rtaddr(hwaddr);
		अगर (!rtaddr)
			जारी;

		rdev = sunxi_rsb_device_create(rsb, child, hwaddr, rtaddr);
		अगर (IS_ERR(rdev))
			dev_err(dev, "failed to add child device %pOF: %ld\n",
				child, PTR_ERR(rdev));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rsb_hw_init(काष्ठा sunxi_rsb *rsb)
अणु
	काष्ठा device *dev = rsb->dev;
	अचिन्हित दीर्घ p_clk_freq;
	u32 clk_delay, reg;
	पूर्णांक clk_भाग, ret;

	ret = clk_prepare_enable(rsb->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(rsb->rstc);
	अगर (ret) अणु
		dev_err(dev, "failed to deassert reset line: %d\n", ret);
		जाओ err_clk_disable;
	पूर्ण

	/* reset the controller */
	ग_लिखोl(RSB_CTRL_SOFT_RST, rsb->regs + RSB_CTRL);
	पढ़ोl_poll_समयout(rsb->regs + RSB_CTRL, reg,
			   !(reg & RSB_CTRL_SOFT_RST), 1000, 100000);

	/*
	 * Clock frequency and delay calculation code is from
	 * Allwinner U-boot sources.
	 *
	 * From A83 user manual:
	 * bus घड़ी frequency = parent घड़ी frequency / (2 * (भागider + 1))
	 */
	p_clk_freq = clk_get_rate(rsb->clk);
	clk_भाग = p_clk_freq / rsb->clk_freq / 2;
	अगर (!clk_भाग)
		clk_भाग = 1;
	अन्यथा अगर (clk_भाग > RSB_CCR_MAX_CLK_DIV + 1)
		clk_भाग = RSB_CCR_MAX_CLK_DIV + 1;

	clk_delay = clk_भाग >> 1;
	अगर (!clk_delay)
		clk_delay = 1;

	dev_info(dev, "RSB running at %lu Hz\n", p_clk_freq / clk_भाग / 2);
	ग_लिखोl(RSB_CCR_SDA_OUT_DELAY(clk_delay) | RSB_CCR_CLK_DIV(clk_भाग - 1),
	       rsb->regs + RSB_CCR);

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(rsb->clk);

	वापस ret;
पूर्ण

अटल व्योम sunxi_rsb_hw_निकास(काष्ठा sunxi_rsb *rsb)
अणु
	/* Keep the घड़ी and PM reference counts consistent. */
	अगर (pm_runसमय_status_suspended(rsb->dev))
		pm_runसमय_resume(rsb->dev);
	reset_control_निश्चित(rsb->rstc);
	clk_disable_unprepare(rsb->clk);
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_rsb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sunxi_rsb *rsb = dev_get_drvdata(dev);

	clk_disable_unprepare(rsb->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_rsb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sunxi_rsb *rsb = dev_get_drvdata(dev);

	वापस clk_prepare_enable(rsb->clk);
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_rsb_suspend(काष्ठा device *dev)
अणु
	काष्ठा sunxi_rsb *rsb = dev_get_drvdata(dev);

	sunxi_rsb_hw_निकास(rsb);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_rsb_resume(काष्ठा device *dev)
अणु
	काष्ठा sunxi_rsb *rsb = dev_get_drvdata(dev);

	वापस sunxi_rsb_hw_init(rsb);
पूर्ण

अटल पूर्णांक sunxi_rsb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *r;
	काष्ठा sunxi_rsb *rsb;
	u32 clk_freq = 3000000;
	पूर्णांक irq, ret;

	of_property_पढ़ो_u32(np, "clock-frequency", &clk_freq);
	अगर (clk_freq > RSB_MAX_FREQ) अणु
		dev_err(dev,
			"clock-frequency (%u Hz) is too high (max = 20MHz)\n",
			clk_freq);
		वापस -EINVAL;
	पूर्ण

	rsb = devm_kzalloc(dev, माप(*rsb), GFP_KERNEL);
	अगर (!rsb)
		वापस -ENOMEM;

	rsb->dev = dev;
	rsb->clk_freq = clk_freq;
	platक्रमm_set_drvdata(pdev, rsb);
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rsb->regs = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(rsb->regs))
		वापस PTR_ERR(rsb->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	rsb->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(rsb->clk)) अणु
		ret = PTR_ERR(rsb->clk);
		dev_err(dev, "failed to retrieve clk: %d\n", ret);
		वापस ret;
	पूर्ण

	rsb->rstc = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(rsb->rstc)) अणु
		ret = PTR_ERR(rsb->rstc);
		dev_err(dev, "failed to retrieve reset controller: %d\n", ret);
		वापस ret;
	पूर्ण

	init_completion(&rsb->complete);
	mutex_init(&rsb->lock);

	ret = devm_request_irq(dev, irq, sunxi_rsb_irq, 0, RSB_CTRL_NAME, rsb);
	अगर (ret) अणु
		dev_err(dev, "can't register interrupt handler irq %d: %d\n",
			irq, ret);
		वापस ret;
	पूर्ण

	ret = sunxi_rsb_hw_init(rsb);
	अगर (ret)
		वापस ret;

	/* initialize all devices on the bus पूर्णांकo RSB mode */
	ret = sunxi_rsb_init_device_mode(rsb);
	अगर (ret)
		dev_warn(dev, "Initialize device mode failed: %d\n", ret);

	pm_suspend_ignore_children(dev, true);
	pm_runसमय_set_active(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	of_rsb_रेजिस्टर_devices(rsb);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rsb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_rsb *rsb = platक्रमm_get_drvdata(pdev);

	device_क्रम_each_child(rsb->dev, शून्य, sunxi_rsb_हटाओ_devices);
	pm_runसमय_disable(&pdev->dev);
	sunxi_rsb_hw_निकास(rsb);

	वापस 0;
पूर्ण

अटल व्योम sunxi_rsb_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_rsb *rsb = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	sunxi_rsb_hw_निकास(rsb);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sunxi_rsb_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sunxi_rsb_runसमय_suspend,
			   sunxi_rsb_runसमय_resume, शून्य)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sunxi_rsb_suspend, sunxi_rsb_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_rsb_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun8i-a23-rsb" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_rsb_of_match_table);

अटल काष्ठा platक्रमm_driver sunxi_rsb_driver = अणु
	.probe = sunxi_rsb_probe,
	.हटाओ	= sunxi_rsb_हटाओ,
	.shutकरोwn = sunxi_rsb_shutकरोwn,
	.driver	= अणु
		.name = RSB_CTRL_NAME,
		.of_match_table = sunxi_rsb_of_match_table,
		.pm = &sunxi_rsb_dev_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sunxi_rsb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&sunxi_rsb_bus);
	अगर (ret) अणु
		pr_err("failed to register sunxi sunxi_rsb bus: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&sunxi_rsb_driver);
पूर्ण
module_init(sunxi_rsb_init);

अटल व्योम __निकास sunxi_rsb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sunxi_rsb_driver);
	bus_unरेजिस्टर(&sunxi_rsb_bus);
पूर्ण
module_निकास(sunxi_rsb_निकास);

MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_DESCRIPTION("Allwinner sunXi Reduced Serial Bus controller driver");
MODULE_LICENSE("GPL v2");
