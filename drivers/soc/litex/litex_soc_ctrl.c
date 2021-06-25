<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LiteX SoC Controller Driver
 *
 * Copyright (C) 2020 Anपंचांगicro <www.anपंचांगicro.com>
 *
 */

#समावेश <linux/litex.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

/* reset रेजिस्टर located at the base address */
#घोषणा RESET_REG_OFF           0x00
#घोषणा RESET_REG_VALUE         0x00000001

#घोषणा SCRATCH_REG_OFF         0x04
#घोषणा SCRATCH_REG_VALUE       0x12345678
#घोषणा SCRATCH_TEST_VALUE      0xdeadbeef

/*
 * Check LiteX CSR पढ़ो/ग_लिखो access
 *
 * This function पढ़ोs and ग_लिखोs a scratch रेजिस्टर in order to verअगरy अगर CSR
 * access works.
 *
 * In हाल any problems are detected, the driver should panic.
 *
 * Access to the LiteX CSR is, by design, करोne in CPU native endianness.
 * The driver should not dynamically configure access functions when
 * the endianness mismatch is detected. Such situation indicates problems in
 * the soft SoC design and should be solved at the LiteX generator level,
 * not in the software.
 */
अटल पूर्णांक litex_check_csr_access(व्योम __iomem *reg_addr)
अणु
	अचिन्हित दीर्घ reg;

	reg = litex_पढ़ो32(reg_addr + SCRATCH_REG_OFF);

	अगर (reg != SCRATCH_REG_VALUE) अणु
		panic("Scratch register read error - the system is probably broken! Expected: 0x%x but got: 0x%lx",
			SCRATCH_REG_VALUE, reg);
		वापस -EINVAL;
	पूर्ण

	litex_ग_लिखो32(reg_addr + SCRATCH_REG_OFF, SCRATCH_TEST_VALUE);
	reg = litex_पढ़ो32(reg_addr + SCRATCH_REG_OFF);

	अगर (reg != SCRATCH_TEST_VALUE) अणु
		panic("Scratch register write error - the system is probably broken! Expected: 0x%x but got: 0x%lx",
			SCRATCH_TEST_VALUE, reg);
		वापस -EINVAL;
	पूर्ण

	/* restore original value of the SCRATCH रेजिस्टर */
	litex_ग_लिखो32(reg_addr + SCRATCH_REG_OFF, SCRATCH_REG_VALUE);

	pr_info("LiteX SoC Controller driver initialized: subreg:%d, align:%d",
		LITEX_SUBREG_SIZE, LITEX_SUBREG_ALIGN);

	वापस 0;
पूर्ण

काष्ठा litex_soc_ctrl_device अणु
	व्योम __iomem *base;
	काष्ठा notअगरier_block reset_nb;
पूर्ण;

अटल पूर्णांक litex_reset_handler(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
			       व्योम *cmd)
अणु
	काष्ठा litex_soc_ctrl_device *soc_ctrl_dev =
		container_of(this, काष्ठा litex_soc_ctrl_device, reset_nb);

	litex_ग_लिखो32(soc_ctrl_dev->base + RESET_REG_OFF, RESET_REG_VALUE);
	वापस NOTIFY_DONE;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id litex_soc_ctrl_of_match[] = अणु
	अणु.compatible = "litex,soc-controller"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, litex_soc_ctrl_of_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक litex_soc_ctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा litex_soc_ctrl_device *soc_ctrl_dev;
	पूर्णांक error;

	soc_ctrl_dev = devm_kzalloc(&pdev->dev, माप(*soc_ctrl_dev), GFP_KERNEL);
	अगर (!soc_ctrl_dev)
		वापस -ENOMEM;

	soc_ctrl_dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(soc_ctrl_dev->base))
		वापस PTR_ERR(soc_ctrl_dev->base);

	error = litex_check_csr_access(soc_ctrl_dev->base);
	अगर (error)
		वापस error;

	platक्रमm_set_drvdata(pdev, soc_ctrl_dev);

	soc_ctrl_dev->reset_nb.notअगरier_call = litex_reset_handler;
	soc_ctrl_dev->reset_nb.priority = 128;
	error = रेजिस्टर_restart_handler(&soc_ctrl_dev->reset_nb);
	अगर (error) अणु
		dev_warn(&pdev->dev, "cannot register restart handler: %d\n",
			 error);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक litex_soc_ctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा litex_soc_ctrl_device *soc_ctrl_dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_restart_handler(&soc_ctrl_dev->reset_nb);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver litex_soc_ctrl_driver = अणु
	.driver = अणु
		.name = "litex-soc-controller",
		.of_match_table = of_match_ptr(litex_soc_ctrl_of_match)
	पूर्ण,
	.probe = litex_soc_ctrl_probe,
	.हटाओ = litex_soc_ctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(litex_soc_ctrl_driver);
MODULE_DESCRIPTION("LiteX SoC Controller driver");
MODULE_AUTHOR("Antmicro <www.antmicro.com>");
MODULE_LICENSE("GPL v2");
