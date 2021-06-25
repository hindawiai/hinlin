<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Embedded Planet EP8248E support
 *
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpc8260.h>
#समावेश <यंत्र/prom.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "pq2.h"

अटल u8 __iomem *ep8248e_bcsr;
अटल काष्ठा device_node *ep8248e_bcsr_node;

#घोषणा BCSR7_SCC2_ENABLE 0x10

#घोषणा BCSR8_PHY1_ENABLE 0x80
#घोषणा BCSR8_PHY1_POWER  0x40
#घोषणा BCSR8_PHY2_ENABLE 0x20
#घोषणा BCSR8_PHY2_POWER  0x10
#घोषणा BCSR8_MDIO_READ   0x04
#घोषणा BCSR8_MDIO_CLOCK  0x02
#घोषणा BCSR8_MDIO_DATA   0x01

#घोषणा BCSR9_USB_ENABLE  0x80
#घोषणा BCSR9_USB_POWER   0x40
#घोषणा BCSR9_USB_HOST    0x20
#घोषणा BCSR9_USB_FULL_SPEED_TARGET 0x10

अटल व्योम __init ep8248e_pic_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_compatible_node(शून्य, शून्य, "fsl,pq2-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "PIC init: can not find cpm-pic node\n");
		वापस;
	पूर्ण

	cpm2_pic_init(np);
	of_node_put(np);
पूर्ण

अटल व्योम ep8248e_set_mdc(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक level)
अणु
	अगर (level)
		setbits8(&ep8248e_bcsr[8], BCSR8_MDIO_CLOCK);
	अन्यथा
		clrbits8(&ep8248e_bcsr[8], BCSR8_MDIO_CLOCK);

	/* Read back to flush the ग_लिखो. */
	in_8(&ep8248e_bcsr[8]);
पूर्ण

अटल व्योम ep8248e_set_mdio_dir(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक output)
अणु
	अगर (output)
		clrbits8(&ep8248e_bcsr[8], BCSR8_MDIO_READ);
	अन्यथा
		setbits8(&ep8248e_bcsr[8], BCSR8_MDIO_READ);

	/* Read back to flush the ग_लिखो. */
	in_8(&ep8248e_bcsr[8]);
पूर्ण

अटल व्योम ep8248e_set_mdio_data(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक data)
अणु
	अगर (data)
		setbits8(&ep8248e_bcsr[8], BCSR8_MDIO_DATA);
	अन्यथा
		clrbits8(&ep8248e_bcsr[8], BCSR8_MDIO_DATA);

	/* Read back to flush the ग_लिखो. */
	in_8(&ep8248e_bcsr[8]);
पूर्ण

अटल पूर्णांक ep8248e_get_mdio_data(काष्ठा mdiobb_ctrl *ctrl)
अणु
	वापस in_8(&ep8248e_bcsr[8]) & BCSR8_MDIO_DATA;
पूर्ण

अटल स्थिर काष्ठा mdiobb_ops ep8248e_mdio_ops = अणु
	.set_mdc = ep8248e_set_mdc,
	.set_mdio_dir = ep8248e_set_mdio_dir,
	.set_mdio_data = ep8248e_set_mdio_data,
	.get_mdio_data = ep8248e_get_mdio_data,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा mdiobb_ctrl ep8248e_mdio_ctrl = अणु
	.ops = &ep8248e_mdio_ops,
पूर्ण;

अटल पूर्णांक ep8248e_mdio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mii_bus *bus;
	काष्ठा resource res;
	काष्ठा device_node *node;
	पूर्णांक ret;

	node = of_get_parent(ofdev->dev.of_node);
	of_node_put(node);
	अगर (node != ep8248e_bcsr_node)
		वापस -ENODEV;

	ret = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	अगर (ret)
		वापस ret;

	bus = alloc_mdio_bitbang(&ep8248e_mdio_ctrl);
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "ep8248e-mdio-bitbang";
	bus->parent = &ofdev->dev;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	ret = of_mdiobus_रेजिस्टर(bus, ofdev->dev.of_node);
	अगर (ret)
		जाओ err_मुक्त_bus;

	वापस 0;
err_मुक्त_bus:
	मुक्त_mdio_bitbang(bus);
	वापस ret;
पूर्ण

अटल पूर्णांक ep8248e_mdio_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ep8248e_mdio_match[] = अणु
	अणु
		.compatible = "fsl,ep8248e-mdio-bitbang",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ep8248e_mdio_driver = अणु
	.driver = अणु
		.name = "ep8248e-mdio-bitbang",
		.of_match_table = ep8248e_mdio_match,
	पूर्ण,
	.probe = ep8248e_mdio_probe,
	.हटाओ = ep8248e_mdio_हटाओ,
पूर्ण;

काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल __initdata काष्ठा cpm_pin ep8248e_pins[] = अणु
	/* SMC1 */
	अणु2, 4, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 5, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC1 */
	अणु2, 14, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 15, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 29, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC1 */
	अणु0, 14, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 15, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 18, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 19, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 21, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 26, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 27, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 28, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 30, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 31, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु2, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC2 */
	अणु1, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 20, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 22, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 25, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 26, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 27, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु1, 30, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 31, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* I2C */
	अणु4, 14, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु4, 15, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,

	/* USB */
	अणु2, 10, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 11, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 24, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 25, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ep8248e_pins); i++) अणु
		स्थिर काष्ठा cpm_pin *pin = &ep8248e_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_smc_clk_setup(CPM_CLK_SMC1, CPM_BRG7);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC3, CPM_CLK8, CPM_CLK_TX); /* USB */
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK11, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK10, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK13, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK14, CPM_CLK_TX);
पूर्ण

अटल व्योम __init ep8248e_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("ep8248e_setup_arch()", 0);

	cpm2_reset();

	/* When this is set, snooping CPM DMA from RAM causes
	 * machine checks.  See erratum SIU18.
	 */
	clrbits32(&cpm2_immr->im_siu_conf.siu_82xx.sc_bcr, MPC82XX_BCR_PLDP);

	ep8248e_bcsr_node =
		of_find_compatible_node(शून्य, शून्य, "fsl,ep8248e-bcsr");
	अगर (!ep8248e_bcsr_node) अणु
		prपूर्णांकk(KERN_ERR "No bcsr in device tree\n");
		वापस;
	पूर्ण

	ep8248e_bcsr = of_iomap(ep8248e_bcsr_node, 0);
	अगर (!ep8248e_bcsr) अणु
		prपूर्णांकk(KERN_ERR "Cannot map BCSR registers\n");
		of_node_put(ep8248e_bcsr_node);
		ep8248e_bcsr_node = शून्य;
		वापस;
	पूर्ण

	setbits8(&ep8248e_bcsr[7], BCSR7_SCC2_ENABLE);
	setbits8(&ep8248e_bcsr[8], BCSR8_PHY1_ENABLE | BCSR8_PHY1_POWER |
	                           BCSR8_PHY2_ENABLE | BCSR8_PHY2_POWER);

	init_ioports();

	अगर (ppc_md.progress)
		ppc_md.progress("ep8248e_setup_arch(), finish", 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .compatible = "fsl,ep8248e-bcsr", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	अगर (IS_ENABLED(CONFIG_MDIO_BITBANG))
		platक्रमm_driver_रेजिस्टर(&ep8248e_mdio_driver);

	वापस 0;
पूर्ण
machine_device_initcall(ep8248e, declare_of_platक्रमm_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init ep8248e_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,ep8248e");
पूर्ण

define_machine(ep8248e)
अणु
	.name = "Embedded Planet EP8248E",
	.probe = ep8248e_probe,
	.setup_arch = ep8248e_setup_arch,
	.init_IRQ = ep8248e_pic_init,
	.get_irq = cpm2_get_irq,
	.calibrate_decr = generic_calibrate_decr,
	.restart = pq2_restart,
	.progress = udbg_progress,
पूर्ण;
