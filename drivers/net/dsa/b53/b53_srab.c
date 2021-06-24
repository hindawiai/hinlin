<शैली गुरु>
/*
 * B53 रेजिस्टर access through Switch Register Access Bridge Registers
 *
 * Copyright (C) 2013 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/b53.h>
#समावेश <linux/of.h>

#समावेश "b53_priv.h"
#समावेश "b53_serdes.h"

/* command and status रेजिस्टर of the SRAB */
#घोषणा B53_SRAB_CMDSTAT		0x2c
#घोषणा  B53_SRAB_CMDSTAT_RST		BIT(2)
#घोषणा  B53_SRAB_CMDSTAT_WRITE		BIT(1)
#घोषणा  B53_SRAB_CMDSTAT_GORDYN	BIT(0)
#घोषणा  B53_SRAB_CMDSTAT_PAGE		24
#घोषणा  B53_SRAB_CMDSTAT_REG		16

/* high order word of ग_लिखो data to चयन registe */
#घोषणा B53_SRAB_WD_H			0x30

/* low order word of ग_लिखो data to चयन registe */
#घोषणा B53_SRAB_WD_L			0x34

/* high order word of पढ़ो data from चयन रेजिस्टर */
#घोषणा B53_SRAB_RD_H			0x38

/* low order word of पढ़ो data from चयन रेजिस्टर */
#घोषणा B53_SRAB_RD_L			0x3c

/* command and status रेजिस्टर of the SRAB */
#घोषणा B53_SRAB_CTRLS			0x40
#घोषणा  B53_SRAB_CTRLS_HOST_INTR	BIT(1)
#घोषणा  B53_SRAB_CTRLS_RCAREQ		BIT(3)
#घोषणा  B53_SRAB_CTRLS_RCAGNT		BIT(4)
#घोषणा  B53_SRAB_CTRLS_SW_INIT_DONE	BIT(6)

/* the रेजिस्टर captures पूर्णांकerrupt pulses from the चयन */
#घोषणा B53_SRAB_INTR			0x44
#घोषणा  B53_SRAB_INTR_P(x)		BIT(x)
#घोषणा  B53_SRAB_SWITCH_PHY		BIT(8)
#घोषणा  B53_SRAB_1588_SYNC		BIT(9)
#घोषणा  B53_SRAB_IMP1_SLEEP_TIMER	BIT(10)
#घोषणा  B53_SRAB_P7_SLEEP_TIMER	BIT(11)
#घोषणा  B53_SRAB_IMP0_SLEEP_TIMER	BIT(12)

/* Port mux configuration रेजिस्टरs */
#घोषणा B53_MUX_CONFIG_P5		0x00
#घोषणा  MUX_CONFIG_SGMII		0
#घोषणा  MUX_CONFIG_MII_LITE		1
#घोषणा  MUX_CONFIG_RGMII		2
#घोषणा  MUX_CONFIG_GMII		3
#घोषणा  MUX_CONFIG_GPHY		4
#घोषणा  MUX_CONFIG_INTERNAL		5
#घोषणा  MUX_CONFIG_MASK		0x7
#घोषणा B53_MUX_CONFIG_P4		0x04

काष्ठा b53_srab_port_priv अणु
	पूर्णांक irq;
	bool irq_enabled;
	काष्ठा b53_device *dev;
	अचिन्हित पूर्णांक num;
	phy_पूर्णांकerface_t mode;
पूर्ण;

काष्ठा b53_srab_priv अणु
	व्योम __iomem *regs;
	व्योम __iomem *mux_config;
	काष्ठा b53_srab_port_priv port_पूर्णांकrs[B53_N_PORTS];
पूर्ण;

अटल पूर्णांक b53_srab_request_grant(काष्ठा b53_device *dev)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	u32 ctrls;
	पूर्णांक i;

	ctrls = पढ़ोl(regs + B53_SRAB_CTRLS);
	ctrls |= B53_SRAB_CTRLS_RCAREQ;
	ग_लिखोl(ctrls, regs + B53_SRAB_CTRLS);

	क्रम (i = 0; i < 20; i++) अणु
		ctrls = पढ़ोl(regs + B53_SRAB_CTRLS);
		अगर (ctrls & B53_SRAB_CTRLS_RCAGNT)
			अवरोध;
		usleep_range(10, 100);
	पूर्ण
	अगर (WARN_ON(i == 5))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम b53_srab_release_grant(काष्ठा b53_device *dev)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	u32 ctrls;

	ctrls = पढ़ोl(regs + B53_SRAB_CTRLS);
	ctrls &= ~B53_SRAB_CTRLS_RCAREQ;
	ग_लिखोl(ctrls, regs + B53_SRAB_CTRLS);
पूर्ण

अटल पूर्णांक b53_srab_op(काष्ठा b53_device *dev, u8 page, u8 reg, u32 op)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक i;
	u32 cmdstat;

	/* set रेजिस्टर address */
	cmdstat = (page << B53_SRAB_CMDSTAT_PAGE) |
		  (reg << B53_SRAB_CMDSTAT_REG) |
		  B53_SRAB_CMDSTAT_GORDYN |
		  op;
	ग_लिखोl(cmdstat, regs + B53_SRAB_CMDSTAT);

	/* check अगर operation completed */
	क्रम (i = 0; i < 5; ++i) अणु
		cmdstat = पढ़ोl(regs + B53_SRAB_CMDSTAT);
		अगर (!(cmdstat & B53_SRAB_CMDSTAT_GORDYN))
			अवरोध;
		usleep_range(10, 100);
	पूर्ण

	अगर (WARN_ON(i == 5))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_srab_पढ़ो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *val)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ret = b53_srab_op(dev, page, reg, 0);
	अगर (ret)
		जाओ err;

	*val = पढ़ोl(regs + B53_SRAB_RD_L) & 0xff;

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_पढ़ो16(काष्ठा b53_device *dev, u8 page, u8 reg, u16 *val)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ret = b53_srab_op(dev, page, reg, 0);
	अगर (ret)
		जाओ err;

	*val = पढ़ोl(regs + B53_SRAB_RD_L) & 0xffff;

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_पढ़ो32(काष्ठा b53_device *dev, u8 page, u8 reg, u32 *val)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ret = b53_srab_op(dev, page, reg, 0);
	अगर (ret)
		जाओ err;

	*val = पढ़ोl(regs + B53_SRAB_RD_L);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_पढ़ो48(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ret = b53_srab_op(dev, page, reg, 0);
	अगर (ret)
		जाओ err;

	*val = पढ़ोl(regs + B53_SRAB_RD_L);
	*val += ((u64)पढ़ोl(regs + B53_SRAB_RD_H) & 0xffff) << 32;

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_पढ़ो64(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ret = b53_srab_op(dev, page, reg, 0);
	अगर (ret)
		जाओ err;

	*val = पढ़ोl(regs + B53_SRAB_RD_L);
	*val += (u64)पढ़ोl(regs + B53_SRAB_RD_H) << 32;

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_ग_लिखो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 value)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ग_लिखोl(value, regs + B53_SRAB_WD_L);

	ret = b53_srab_op(dev, page, reg, B53_SRAB_CMDSTAT_WRITE);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_ग_लिखो16(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u16 value)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ग_लिखोl(value, regs + B53_SRAB_WD_L);

	ret = b53_srab_op(dev, page, reg, B53_SRAB_CMDSTAT_WRITE);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_ग_लिखो32(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u32 value)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ग_लिखोl(value, regs + B53_SRAB_WD_L);

	ret = b53_srab_op(dev, page, reg, B53_SRAB_CMDSTAT_WRITE);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_ग_लिखो48(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ग_लिखोl((u32)value, regs + B53_SRAB_WD_L);
	ग_लिखोl((u16)(value >> 32), regs + B53_SRAB_WD_H);

	ret = b53_srab_op(dev, page, reg, B53_SRAB_CMDSTAT_WRITE);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_srab_ग_लिखो64(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	u8 __iomem *regs = priv->regs;
	पूर्णांक ret = 0;

	ret = b53_srab_request_grant(dev);
	अगर (ret)
		जाओ err;

	ग_लिखोl((u32)value, regs + B53_SRAB_WD_L);
	ग_लिखोl((u32)(value >> 32), regs + B53_SRAB_WD_H);

	ret = b53_srab_op(dev, page, reg, B53_SRAB_CMDSTAT_WRITE);

err:
	b53_srab_release_grant(dev);

	वापस ret;
पूर्ण

अटल irqवापस_t b53_srab_port_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा b53_srab_port_priv *port = dev_id;
	काष्ठा b53_device *dev = port->dev;

	अगर (port->mode == PHY_INTERFACE_MODE_SGMII)
		b53_port_event(dev->ds, port->num);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t b53_srab_port_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा b53_srab_port_priv *port = dev_id;
	काष्ठा b53_device *dev = port->dev;
	काष्ठा b53_srab_priv *priv = dev->priv;

	/* Acknowledge the पूर्णांकerrupt */
	ग_लिखोl(BIT(port->num), priv->regs + B53_SRAB_INTR);

	वापस IRQ_WAKE_THREAD;
पूर्ण

#अगर IS_ENABLED(CONFIG_B53_SERDES)
अटल u8 b53_srab_serdes_map_lane(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	काष्ठा b53_srab_port_priv *p = &priv->port_पूर्णांकrs[port];

	अगर (p->mode != PHY_INTERFACE_MODE_SGMII)
		वापस B53_INVALID_LANE;

	चयन (port) अणु
	हाल 5:
		वापस 0;
	हाल 4:
		वापस 1;
	शेष:
		वापस B53_INVALID_LANE;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक b53_srab_irq_enable(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	काष्ठा b53_srab_port_priv *p = &priv->port_पूर्णांकrs[port];
	पूर्णांक ret = 0;

	/* Interrupt is optional and was not specअगरied, करो not make
	 * this fatal
	 */
	अगर (p->irq == -ENXIO)
		वापस ret;

	ret = request_thपढ़ोed_irq(p->irq, b53_srab_port_isr,
				   b53_srab_port_thपढ़ो, 0,
				   dev_name(dev->dev), p);
	अगर (!ret)
		p->irq_enabled = true;

	वापस ret;
पूर्ण

अटल व्योम b53_srab_irq_disable(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	काष्ठा b53_srab_priv *priv = dev->priv;
	काष्ठा b53_srab_port_priv *p = &priv->port_पूर्णांकrs[port];

	अगर (p->irq_enabled) अणु
		मुक्त_irq(p->irq, p);
		p->irq_enabled = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा b53_io_ops b53_srab_ops = अणु
	.पढ़ो8 = b53_srab_पढ़ो8,
	.पढ़ो16 = b53_srab_पढ़ो16,
	.पढ़ो32 = b53_srab_पढ़ो32,
	.पढ़ो48 = b53_srab_पढ़ो48,
	.पढ़ो64 = b53_srab_पढ़ो64,
	.ग_लिखो8 = b53_srab_ग_लिखो8,
	.ग_लिखो16 = b53_srab_ग_लिखो16,
	.ग_लिखो32 = b53_srab_ग_लिखो32,
	.ग_लिखो48 = b53_srab_ग_लिखो48,
	.ग_लिखो64 = b53_srab_ग_लिखो64,
	.irq_enable = b53_srab_irq_enable,
	.irq_disable = b53_srab_irq_disable,
#अगर IS_ENABLED(CONFIG_B53_SERDES)
	.serdes_map_lane = b53_srab_serdes_map_lane,
	.serdes_link_state = b53_serdes_link_state,
	.serdes_config = b53_serdes_config,
	.serdes_an_restart = b53_serdes_an_restart,
	.serdes_link_set = b53_serdes_link_set,
	.serdes_phylink_validate = b53_serdes_phylink_validate,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id b53_srab_of_match[] = अणु
	अणु .compatible = "brcm,bcm53010-srab" पूर्ण,
	अणु .compatible = "brcm,bcm53011-srab" पूर्ण,
	अणु .compatible = "brcm,bcm53012-srab" पूर्ण,
	अणु .compatible = "brcm,bcm53018-srab" पूर्ण,
	अणु .compatible = "brcm,bcm53019-srab" पूर्ण,
	अणु .compatible = "brcm,bcm5301x-srab" पूर्ण,
	अणु .compatible = "brcm,bcm11360-srab", .data = (व्योम *)BCM583XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58522-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58525-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58535-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58622-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58623-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm58625-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,bcm88312-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,cygnus-srab", .data = (व्योम *)BCM583XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,nsp-srab", .data = (व्योम *)BCM58XX_DEVICE_ID पूर्ण,
	अणु .compatible = "brcm,omega-srab", .data = (व्योम *)BCM583XX_DEVICE_ID पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, b53_srab_of_match);

अटल व्योम b53_srab_पूर्णांकr_set(काष्ठा b53_srab_priv *priv, bool set)
अणु
	u32 reg;

	reg = पढ़ोl(priv->regs + B53_SRAB_CTRLS);
	अगर (set)
		reg |= B53_SRAB_CTRLS_HOST_INTR;
	अन्यथा
		reg &= ~B53_SRAB_CTRLS_HOST_INTR;
	ग_लिखोl(reg, priv->regs + B53_SRAB_CTRLS);
पूर्ण

अटल व्योम b53_srab_prepare_irq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा b53_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा b53_srab_priv *priv = dev->priv;
	काष्ठा b53_srab_port_priv *port;
	अचिन्हित पूर्णांक i;
	अक्षर *name;

	/* Clear all pending पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, priv->regs + B53_SRAB_INTR);

	क्रम (i = 0; i < B53_N_PORTS; i++) अणु
		port = &priv->port_पूर्णांकrs[i];

		/* There is no port 6 */
		अगर (i == 6)
			जारी;

		name = kaप्र_लिखो(GFP_KERNEL, "link_state_p%d", i);
		अगर (!name)
			वापस;

		port->num = i;
		port->dev = dev;
		port->irq = platक्रमm_get_irq_byname_optional(pdev, name);
		kमुक्त(name);
	पूर्ण

	b53_srab_पूर्णांकr_set(priv, true);
पूर्ण

अटल व्योम b53_srab_mux_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा b53_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा b53_srab_priv *priv = dev->priv;
	काष्ठा b53_srab_port_priv *p;
	अचिन्हित पूर्णांक port;
	u32 reg, off = 0;
	पूर्णांक ret;

	अगर (dev->pdata && dev->pdata->chip_id != BCM58XX_DEVICE_ID)
		वापस;

	priv->mux_config = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->mux_config))
		वापस;

	/* Obtain the port mux configuration so we know which lanes
	 * actually map to SerDes lanes
	 */
	क्रम (port = 5; port > 3; port--, off += 4) अणु
		p = &priv->port_पूर्णांकrs[port];

		reg = पढ़ोl(priv->mux_config + B53_MUX_CONFIG_P5 + off);
		चयन (reg & MUX_CONFIG_MASK) अणु
		हाल MUX_CONFIG_SGMII:
			p->mode = PHY_INTERFACE_MODE_SGMII;
			ret = b53_serdes_init(dev, port);
			अगर (ret)
				जारी;
			अवरोध;
		हाल MUX_CONFIG_MII_LITE:
			p->mode = PHY_INTERFACE_MODE_MII;
			अवरोध;
		हाल MUX_CONFIG_GMII:
			p->mode = PHY_INTERFACE_MODE_GMII;
			अवरोध;
		हाल MUX_CONFIG_RGMII:
			p->mode = PHY_INTERFACE_MODE_RGMII;
			अवरोध;
		हाल MUX_CONFIG_INTERNAL:
			p->mode = PHY_INTERFACE_MODE_INTERNAL;
			अवरोध;
		शेष:
			p->mode = PHY_INTERFACE_MODE_NA;
			अवरोध;
		पूर्ण

		अगर (p->mode != PHY_INTERFACE_MODE_NA)
			dev_info(&pdev->dev, "Port %d mode: %s\n",
				 port, phy_modes(p->mode));
	पूर्ण
पूर्ण

अटल पूर्णांक b53_srab_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा b53_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device_node *dn = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	काष्ठा b53_srab_priv *priv;
	काष्ठा b53_device *dev;

	अगर (dn)
		of_id = of_match_node(b53_srab_of_match, dn);

	अगर (of_id) अणु
		pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		pdata->chip_id = (u32)(अचिन्हित दीर्घ)of_id->data;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	dev = b53_चयन_alloc(&pdev->dev, &b53_srab_ops, priv);
	अगर (!dev)
		वापस -ENOMEM;

	अगर (pdata)
		dev->pdata = pdata;

	platक्रमm_set_drvdata(pdev, dev);

	b53_srab_prepare_irq(pdev);
	b53_srab_mux_init(pdev);

	वापस b53_चयन_रेजिस्टर(dev);
पूर्ण

अटल पूर्णांक b53_srab_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा b53_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा b53_srab_priv *priv = dev->priv;

	b53_srab_पूर्णांकr_set(priv, false);
	अगर (dev)
		b53_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver b53_srab_driver = अणु
	.probe = b53_srab_probe,
	.हटाओ = b53_srab_हटाओ,
	.driver = अणु
		.name = "b53-srab-switch",
		.of_match_table = b53_srab_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(b53_srab_driver);
MODULE_AUTHOR("Hauke Mehrtens <hauke@hauke-m.de>");
MODULE_DESCRIPTION("B53 Switch Register Access Bridge Registers (SRAB) access driver");
MODULE_LICENSE("Dual BSD/GPL");
