<शैली गुरु>
/*
 * Platक्रमm CAN bus driver क्रम Bosch C_CAN controller
 *
 * Copyright (C) 2010 ST Microelectronics
 * Bhupesh Sharma <bhupesh.sharma@st.com>
 *
 * Borrowed heavily from the C_CAN driver originally written by:
 * Copyright (C) 2007
 * - Sascha Hauer, Marc Kleine-Budde, Pengutronix <s.hauer@pengutronix.de>
 * - Simon Kallweit, पूर्णांकefo AG <simon.kallweit@पूर्णांकefo.ch>
 *
 * Bosch C_CAN controller is compliant to CAN protocol version 2.0 part A and B.
 * Bosch C_CAN user manual can be obtained from:
 * http://www.semiconductors.bosch.de/media/en/pdf/ipmodules_1/c_can/
 * users_manual_c_can.pdf
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <linux/can/dev.h>

#समावेश "c_can.h"

#घोषणा DCAN_RAM_INIT_BIT BIT(3)

अटल DEFINE_SPINLOCK(raminit_lock);

/* 16-bit c_can रेजिस्टरs can be arranged dअगरferently in the memory
 * architecture of dअगरferent implementations. For example: 16-bit
 * रेजिस्टरs can be aligned to a 16-bit boundary or 32-bit boundary etc.
 * Handle the same by providing a common पढ़ो/ग_लिखो पूर्णांकerface.
 */
अटल u16 c_can_plat_पढ़ो_reg_aligned_to_16bit(स्थिर काष्ठा c_can_priv *priv,
						क्रमागत reg index)
अणु
	वापस पढ़ोw(priv->base + priv->regs[index]);
पूर्ण

अटल व्योम c_can_plat_ग_लिखो_reg_aligned_to_16bit(स्थिर काष्ठा c_can_priv *priv,
						  क्रमागत reg index, u16 val)
अणु
	ग_लिखोw(val, priv->base + priv->regs[index]);
पूर्ण

अटल u16 c_can_plat_पढ़ो_reg_aligned_to_32bit(स्थिर काष्ठा c_can_priv *priv,
						क्रमागत reg index)
अणु
	वापस पढ़ोw(priv->base + 2 * priv->regs[index]);
पूर्ण

अटल व्योम c_can_plat_ग_लिखो_reg_aligned_to_32bit(स्थिर काष्ठा c_can_priv *priv,
						  क्रमागत reg index, u16 val)
अणु
	ग_लिखोw(val, priv->base + 2 * priv->regs[index]);
पूर्ण

अटल व्योम c_can_hw_raminit_रुको_syscon(स्थिर काष्ठा c_can_priv *priv,
					 u32 mask, u32 val)
अणु
	स्थिर काष्ठा c_can_raminit *raminit = &priv->raminit_sys;
	पूर्णांक समयout = 0;
	u32 ctrl = 0;

	/* We look only at the bits of our instance. */
	val &= mask;
	करो अणु
		udelay(1);
		समयout++;

		regmap_पढ़ो(raminit->syscon, raminit->reg, &ctrl);
		अगर (समयout == 1000) अणु
			dev_err(&priv->dev->dev, "%s: time out\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((ctrl & mask) != val);
पूर्ण

अटल व्योम c_can_hw_raminit_syscon(स्थिर काष्ठा c_can_priv *priv, bool enable)
अणु
	स्थिर काष्ठा c_can_raminit *raminit = &priv->raminit_sys;
	u32 ctrl = 0;
	u32 mask;

	spin_lock(&raminit_lock);

	mask = 1 << raminit->bits.start | 1 << raminit->bits.करोne;
	regmap_पढ़ो(raminit->syscon, raminit->reg, &ctrl);

	/* We clear the start bit first. The start bit is
	 * looking at the 0 -> transition, but is not self clearing;
	 * NOTE: DONE must be written with 1 to clear it.
	 * We can't clear the DONE bit here using regmap_update_bits()
	 * as it will bypass the ग_लिखो अगर initial condition is START:0 DONE:1
	 * e.g. on DRA7 which needs START pulse.
	 */
	ctrl &= ~mask;	/* START = 0, DONE = 0 */
	regmap_update_bits(raminit->syscon, raminit->reg, mask, ctrl);

	/* check अगर START bit is 0. Ignore DONE bit क्रम now
	 * as it can be either 0 or 1.
	 */
	c_can_hw_raminit_रुको_syscon(priv, 1 << raminit->bits.start, ctrl);

	अगर (enable) अणु
		/* Clear DONE bit & set START bit. */
		ctrl |= 1 << raminit->bits.start;
		/* DONE must be written with 1 to clear it */
		ctrl |= 1 << raminit->bits.करोne;
		regmap_update_bits(raminit->syscon, raminit->reg, mask, ctrl);
		/* prevent further clearing of DONE bit */
		ctrl &= ~(1 << raminit->bits.करोne);
		/* clear START bit अगर start pulse is needed */
		अगर (raminit->needs_pulse) अणु
			ctrl &= ~(1 << raminit->bits.start);
			regmap_update_bits(raminit->syscon, raminit->reg,
					   mask, ctrl);
		पूर्ण

		ctrl |= 1 << raminit->bits.करोne;
		c_can_hw_raminit_रुको_syscon(priv, mask, ctrl);
	पूर्ण
	spin_unlock(&raminit_lock);
पूर्ण

अटल u32 c_can_plat_पढ़ो_reg32(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index)
अणु
	u32 val;

	val = priv->पढ़ो_reg(priv, index);
	val |= ((u32)priv->पढ़ो_reg(priv, index + 1)) << 16;

	वापस val;
पूर्ण

अटल व्योम c_can_plat_ग_लिखो_reg32(स्थिर काष्ठा c_can_priv *priv,
				   क्रमागत reg index, u32 val)
अणु
	priv->ग_लिखो_reg(priv, index + 1, val >> 16);
	priv->ग_लिखो_reg(priv, index, val);
पूर्ण

अटल u32 d_can_plat_पढ़ो_reg32(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index)
अणु
	वापस पढ़ोl(priv->base + priv->regs[index]);
पूर्ण

अटल व्योम d_can_plat_ग_लिखो_reg32(स्थिर काष्ठा c_can_priv *priv,
				   क्रमागत reg index, u32 val)
अणु
	ग_लिखोl(val, priv->base + priv->regs[index]);
पूर्ण

अटल व्योम c_can_hw_raminit_रुको(स्थिर काष्ठा c_can_priv *priv, u32 mask)
अणु
	जबतक (priv->पढ़ो_reg32(priv, C_CAN_FUNCTION_REG) & mask)
		udelay(1);
पूर्ण

अटल व्योम c_can_hw_raminit(स्थिर काष्ठा c_can_priv *priv, bool enable)
अणु
	u32 ctrl;

	ctrl = priv->पढ़ो_reg32(priv, C_CAN_FUNCTION_REG);
	ctrl &= ~DCAN_RAM_INIT_BIT;
	priv->ग_लिखो_reg32(priv, C_CAN_FUNCTION_REG, ctrl);
	c_can_hw_raminit_रुको(priv, ctrl);

	अगर (enable) अणु
		ctrl |= DCAN_RAM_INIT_BIT;
		priv->ग_लिखो_reg32(priv, C_CAN_FUNCTION_REG, ctrl);
		c_can_hw_raminit_रुको(priv, ctrl);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा c_can_driver_data c_can_drvdata = अणु
	.id = BOSCH_C_CAN,
	.msg_obj_num = 32,
पूर्ण;

अटल स्थिर काष्ठा c_can_driver_data d_can_drvdata = अणु
	.id = BOSCH_D_CAN,
	.msg_obj_num = 32,
पूर्ण;

अटल स्थिर काष्ठा raminit_bits dra7_raminit_bits[] = अणु
	[0] = अणु .start = 3, .करोne = 1, पूर्ण,
	[1] = अणु .start = 5, .करोne = 2, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा c_can_driver_data dra7_dcan_drvdata = अणु
	.id = BOSCH_D_CAN,
	.msg_obj_num = 64,
	.raminit_num = ARRAY_SIZE(dra7_raminit_bits),
	.raminit_bits = dra7_raminit_bits,
	.raminit_pulse = true,
पूर्ण;

अटल स्थिर काष्ठा raminit_bits am3352_raminit_bits[] = अणु
	[0] = अणु .start = 0, .करोne = 8, पूर्ण,
	[1] = अणु .start = 1, .करोne = 9, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा c_can_driver_data am3352_dcan_drvdata = अणु
	.id = BOSCH_D_CAN,
	.msg_obj_num = 64,
	.raminit_num = ARRAY_SIZE(am3352_raminit_bits),
	.raminit_bits = am3352_raminit_bits,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id c_can_id_table[] = अणु
	अणु
		.name = KBUILD_MODNAME,
		.driver_data = (kernel_uदीर्घ_t)&c_can_drvdata,
	पूर्ण,
	अणु
		.name = "c_can",
		.driver_data = (kernel_uदीर्घ_t)&c_can_drvdata,
	पूर्ण,
	अणु
		.name = "d_can",
		.driver_data = (kernel_uदीर्घ_t)&d_can_drvdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, c_can_id_table);

अटल स्थिर काष्ठा of_device_id c_can_of_table[] = अणु
	अणु .compatible = "bosch,c_can", .data = &c_can_drvdata पूर्ण,
	अणु .compatible = "bosch,d_can", .data = &d_can_drvdata पूर्ण,
	अणु .compatible = "ti,dra7-d_can", .data = &dra7_dcan_drvdata पूर्ण,
	अणु .compatible = "ti,am3352-d_can", .data = &am3352_dcan_drvdata पूर्ण,
	अणु .compatible = "ti,am4372-d_can", .data = &am3352_dcan_drvdata पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, c_can_of_table);

अटल पूर्णांक c_can_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	व्योम __iomem *addr;
	काष्ठा net_device *dev;
	काष्ठा c_can_priv *priv;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *mem;
	पूर्णांक irq;
	काष्ठा clk *clk;
	स्थिर काष्ठा c_can_driver_data *drvdata;
	काष्ठा device_node *np = pdev->dev.of_node;

	match = of_match_device(c_can_of_table, &pdev->dev);
	अगर (match) अणु
		drvdata = match->data;
	पूर्ण अन्यथा अगर (pdev->id_entry->driver_data) अणु
		drvdata = (काष्ठा c_can_driver_data *)
			platक्रमm_get_device_id(pdev)->driver_data;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	/* get the appropriate clk */
	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ निकास;
	पूर्ण

	/* get the platक्रमm data */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -ENODEV;
		जाओ निकास;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	addr = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(addr)) अणु
		ret =  PTR_ERR(addr);
		जाओ निकास;
	पूर्ण

	/* allocate the c_can device */
	dev = alloc_c_can_dev(drvdata->msg_obj_num);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	priv = netdev_priv(dev);
	चयन (drvdata->id) अणु
	हाल BOSCH_C_CAN:
		priv->regs = reg_map_c_can;
		चयन (mem->flags & IORESOURCE_MEM_TYPE_MASK) अणु
		हाल IORESOURCE_MEM_32BIT:
			priv->पढ़ो_reg = c_can_plat_पढ़ो_reg_aligned_to_32bit;
			priv->ग_लिखो_reg = c_can_plat_ग_लिखो_reg_aligned_to_32bit;
			priv->पढ़ो_reg32 = c_can_plat_पढ़ो_reg32;
			priv->ग_लिखो_reg32 = c_can_plat_ग_लिखो_reg32;
			अवरोध;
		हाल IORESOURCE_MEM_16BIT:
		शेष:
			priv->पढ़ो_reg = c_can_plat_पढ़ो_reg_aligned_to_16bit;
			priv->ग_लिखो_reg = c_can_plat_ग_लिखो_reg_aligned_to_16bit;
			priv->पढ़ो_reg32 = c_can_plat_पढ़ो_reg32;
			priv->ग_लिखो_reg32 = c_can_plat_ग_लिखो_reg32;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BOSCH_D_CAN:
		priv->regs = reg_map_d_can;
		priv->पढ़ो_reg = c_can_plat_पढ़ो_reg_aligned_to_16bit;
		priv->ग_लिखो_reg = c_can_plat_ग_लिखो_reg_aligned_to_16bit;
		priv->पढ़ो_reg32 = d_can_plat_पढ़ो_reg32;
		priv->ग_लिखो_reg32 = d_can_plat_ग_लिखो_reg32;

		/* Check अगर we need custom RAMINIT via syscon. Mostly क्रम TI
		 * platक्रमms. Only supported with DT boot.
		 */
		अगर (np && of_property_पढ़ो_bool(np, "syscon-raminit")) अणु
			u32 id;
			काष्ठा c_can_raminit *raminit = &priv->raminit_sys;

			ret = -EINVAL;
			raminit->syscon = syscon_regmap_lookup_by_phandle(np,
									  "syscon-raminit");
			अगर (IS_ERR(raminit->syscon)) अणु
				/* can fail with -EPROBE_DEFER */
				ret = PTR_ERR(raminit->syscon);
				मुक्त_c_can_dev(dev);
				वापस ret;
			पूर्ण

			अगर (of_property_पढ़ो_u32_index(np, "syscon-raminit", 1,
						       &raminit->reg)) अणु
				dev_err(&pdev->dev,
					"couldn't get the RAMINIT reg. offset!\n");
				जाओ निकास_मुक्त_device;
			पूर्ण

			अगर (of_property_पढ़ो_u32_index(np, "syscon-raminit", 2,
						       &id)) अणु
				dev_err(&pdev->dev,
					"couldn't get the CAN instance ID\n");
				जाओ निकास_मुक्त_device;
			पूर्ण

			अगर (id >= drvdata->raminit_num) अणु
				dev_err(&pdev->dev,
					"Invalid CAN instance ID\n");
				जाओ निकास_मुक्त_device;
			पूर्ण

			raminit->bits = drvdata->raminit_bits[id];
			raminit->needs_pulse = drvdata->raminit_pulse;

			priv->raminit = c_can_hw_raminit_syscon;
		पूर्ण अन्यथा अणु
			priv->raminit = c_can_hw_raminit;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ निकास_मुक्त_device;
	पूर्ण

	dev->irq = irq;
	priv->base = addr;
	priv->device = &pdev->dev;
	priv->can.घड़ी.freq = clk_get_rate(clk);
	priv->priv = clk;
	priv->type = drvdata->id;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	pm_runसमय_enable(priv->device);
	ret = रेजिस्टर_c_can_dev(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			KBUILD_MODNAME, ret);
		जाओ निकास_मुक्त_device;
	पूर्ण

	dev_info(&pdev->dev, "%s device registered (regs=%p, irq=%d)\n",
		 KBUILD_MODNAME, priv->base, dev->irq);
	वापस 0;

निकास_मुक्त_device:
	pm_runसमय_disable(priv->device);
	मुक्त_c_can_dev(dev);
निकास:
	dev_err(&pdev->dev, "probe failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक c_can_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	unरेजिस्टर_c_can_dev(dev);
	pm_runसमय_disable(priv->device);
	मुक्त_c_can_dev(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक c_can_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	पूर्णांक ret;
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा c_can_priv *priv = netdev_priv(ndev);

	अगर (priv->type != BOSCH_D_CAN) अणु
		dev_warn(&pdev->dev, "Not supported\n");
		वापस 0;
	पूर्ण

	अगर (netअगर_running(ndev)) अणु
		netअगर_stop_queue(ndev);
		netअगर_device_detach(ndev);
	पूर्ण

	ret = c_can_घातer_करोwn(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "failed to enter power down mode\n");
		वापस ret;
	पूर्ण

	priv->can.state = CAN_STATE_SLEEPING;

	वापस 0;
पूर्ण

अटल पूर्णांक c_can_resume(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा c_can_priv *priv = netdev_priv(ndev);

	अगर (priv->type != BOSCH_D_CAN) अणु
		dev_warn(&pdev->dev, "Not supported\n");
		वापस 0;
	पूर्ण

	ret = c_can_घातer_up(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Still in power down mode\n");
		वापस ret;
	पूर्ण

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (netअगर_running(ndev)) अणु
		netअगर_device_attach(ndev);
		netअगर_start_queue(ndev);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा c_can_suspend शून्य
#घोषणा c_can_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver c_can_plat_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = c_can_of_table,
	पूर्ण,
	.probe = c_can_plat_probe,
	.हटाओ = c_can_plat_हटाओ,
	.suspend = c_can_suspend,
	.resume = c_can_resume,
	.id_table = c_can_id_table,
पूर्ण;

module_platक्रमm_driver(c_can_plat_driver);

MODULE_AUTHOR("Bhupesh Sharma <bhupesh.sharma@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Platform CAN bus driver for Bosch C_CAN controller");
