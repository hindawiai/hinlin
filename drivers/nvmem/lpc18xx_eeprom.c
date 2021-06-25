<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NXP LPC18xx/LPC43xx EEPROM memory NVMEM driver
 *
 * Copyright (c) 2015 Ariel D'Alessandro <ariel@vanguardiasur.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

/* Registers */
#घोषणा LPC18XX_EEPROM_AUTOPROG			0x00c
#घोषणा LPC18XX_EEPROM_AUTOPROG_WORD		0x1

#घोषणा LPC18XX_EEPROM_CLKDIV			0x014

#घोषणा LPC18XX_EEPROM_PWRDWN			0x018
#घोषणा LPC18XX_EEPROM_PWRDWN_NO		0x0
#घोषणा LPC18XX_EEPROM_PWRDWN_YES		0x1

#घोषणा LPC18XX_EEPROM_INTSTAT			0xfe0
#घोषणा LPC18XX_EEPROM_INTSTAT_END_OF_PROG	BIT(2)

#घोषणा LPC18XX_EEPROM_INTSTATCLR		0xfe8
#घोषणा LPC18XX_EEPROM_INTSTATCLR_PROG_CLR_ST	BIT(2)

/* Fixed page size (bytes) */
#घोषणा LPC18XX_EEPROM_PAGE_SIZE		0x80

/* EEPROM device requires a ~1500 kHz घड़ी (min 800 kHz, max 1600 kHz) */
#घोषणा LPC18XX_EEPROM_CLOCK_HZ			1500000

/* EEPROM requires 3 ms of erase/program समय between each writing */
#घोषणा LPC18XX_EEPROM_PROGRAM_TIME		3

काष्ठा lpc18xx_eeprom_dev अणु
	काष्ठा clk *clk;
	व्योम __iomem *reg_base;
	व्योम __iomem *mem_base;
	काष्ठा nvmem_device *nvmem;
	अचिन्हित reg_bytes;
	अचिन्हित val_bytes;
	पूर्णांक size;
पूर्ण;

अटल अंतरभूत व्योम lpc18xx_eeprom_ग_लिखोl(काष्ठा lpc18xx_eeprom_dev *eeprom,
					 u32 reg, u32 val)
अणु
	ग_लिखोl(val, eeprom->reg_base + reg);
पूर्ण

अटल अंतरभूत u32 lpc18xx_eeprom_पढ़ोl(काष्ठा lpc18xx_eeprom_dev *eeprom,
				       u32 reg)
अणु
	वापस पढ़ोl(eeprom->reg_base + reg);
पूर्ण

अटल पूर्णांक lpc18xx_eeprom_busyरुको_until_prog(काष्ठा lpc18xx_eeprom_dev *eeprom)
अणु
	अचिन्हित दीर्घ end;
	u32 val;

	/* Wait until EEPROM program operation has finished */
	end = jअगरfies + msecs_to_jअगरfies(LPC18XX_EEPROM_PROGRAM_TIME * 10);

	जबतक (समय_is_after_jअगरfies(end)) अणु
		val = lpc18xx_eeprom_पढ़ोl(eeprom, LPC18XX_EEPROM_INTSTAT);

		अगर (val & LPC18XX_EEPROM_INTSTAT_END_OF_PROG) अणु
			lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_INTSTATCLR,
					LPC18XX_EEPROM_INTSTATCLR_PROG_CLR_ST);
			वापस 0;
		पूर्ण

		usleep_range(LPC18XX_EEPROM_PROGRAM_TIME * USEC_PER_MSEC,
			     (LPC18XX_EEPROM_PROGRAM_TIME + 1) * USEC_PER_MSEC);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक lpc18xx_eeprom_gather_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा lpc18xx_eeprom_dev *eeprom = context;
	अचिन्हित पूर्णांक offset = reg;
	पूर्णांक ret;

	/*
	 * The last page contains the EEPROM initialization data and is not
	 * writable.
	 */
	अगर ((reg > eeprom->size - LPC18XX_EEPROM_PAGE_SIZE) ||
			(reg + bytes > eeprom->size - LPC18XX_EEPROM_PAGE_SIZE))
		वापस -EINVAL;


	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_NO);

	/* Wait 100 us जबतक the EEPROM wakes up */
	usleep_range(100, 200);

	जबतक (bytes) अणु
		ग_लिखोl(*(u32 *)val, eeprom->mem_base + offset);
		ret = lpc18xx_eeprom_busyरुको_until_prog(eeprom);
		अगर (ret < 0)
			वापस ret;

		bytes -= eeprom->val_bytes;
		val += eeprom->val_bytes;
		offset += eeprom->val_bytes;
	पूर्ण

	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_YES);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_eeprom_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			       व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा lpc18xx_eeprom_dev *eeprom = context;

	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_NO);

	/* Wait 100 us जबतक the EEPROM wakes up */
	usleep_range(100, 200);

	जबतक (bytes) अणु
		*(u32 *)val = पढ़ोl(eeprom->mem_base + offset);
		bytes -= eeprom->val_bytes;
		val += eeprom->val_bytes;
		offset += eeprom->val_bytes;
	पूर्ण

	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_YES);

	वापस 0;
पूर्ण


अटल काष्ठा nvmem_config lpc18xx_nvmem_config = अणु
	.name = "lpc18xx-eeprom",
	.stride = 4,
	.word_size = 4,
	.reg_पढ़ो = lpc18xx_eeprom_पढ़ो,
	.reg_ग_लिखो = lpc18xx_eeprom_gather_ग_लिखो,
पूर्ण;

अटल पूर्णांक lpc18xx_eeprom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_eeprom_dev *eeprom;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा reset_control *rst;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा resource *res;
	पूर्णांक ret;

	eeprom = devm_kzalloc(dev, माप(*eeprom), GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "reg");
	eeprom->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(eeprom->reg_base))
		वापस PTR_ERR(eeprom->reg_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mem");
	eeprom->mem_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(eeprom->mem_base))
		वापस PTR_ERR(eeprom->mem_base);

	eeprom->clk = devm_clk_get(&pdev->dev, "eeprom");
	अगर (IS_ERR(eeprom->clk)) अणु
		dev_err(&pdev->dev, "failed to get eeprom clock\n");
		वापस PTR_ERR(eeprom->clk);
	पूर्ण

	ret = clk_prepare_enable(eeprom->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to prepare/enable eeprom clk: %d\n", ret);
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		dev_err(dev, "failed to get reset: %ld\n", PTR_ERR(rst));
		ret = PTR_ERR(rst);
		जाओ err_clk;
	पूर्ण

	ret = reset_control_निश्चित(rst);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to assert reset: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	eeprom->val_bytes = 4;
	eeprom->reg_bytes = 4;

	/*
	 * Clock rate is generated by भागiding the प्रणाली bus घड़ी by the
	 * भागision factor, contained in the भागider रेजिस्टर (minus 1 encoded).
	 */
	clk_rate = clk_get_rate(eeprom->clk);
	clk_rate = DIV_ROUND_UP(clk_rate, LPC18XX_EEPROM_CLOCK_HZ) - 1;
	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_CLKDIV, clk_rate);

	/*
	 * Writing a single word to the page will start the erase/program cycle
	 * स्वतःmatically
	 */
	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_AUTOPROG,
			      LPC18XX_EEPROM_AUTOPROG_WORD);

	lpc18xx_eeprom_ग_लिखोl(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_YES);

	eeprom->size = resource_size(res);
	lpc18xx_nvmem_config.size = resource_size(res);
	lpc18xx_nvmem_config.dev = dev;
	lpc18xx_nvmem_config.priv = eeprom;

	eeprom->nvmem = devm_nvmem_रेजिस्टर(dev, &lpc18xx_nvmem_config);
	अगर (IS_ERR(eeprom->nvmem)) अणु
		ret = PTR_ERR(eeprom->nvmem);
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, eeprom);

	वापस 0;

err_clk:
	clk_disable_unprepare(eeprom->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक lpc18xx_eeprom_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_eeprom_dev *eeprom = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(eeprom->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_eeprom_of_match[] = अणु
	अणु .compatible = "nxp,lpc1857-eeprom" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_eeprom_of_match);

अटल काष्ठा platक्रमm_driver lpc18xx_eeprom_driver = अणु
	.probe = lpc18xx_eeprom_probe,
	.हटाओ = lpc18xx_eeprom_हटाओ,
	.driver = अणु
		.name = "lpc18xx-eeprom",
		.of_match_table = lpc18xx_eeprom_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc18xx_eeprom_driver);

MODULE_AUTHOR("Ariel D'Alessandro <ariel@vanguardiasur.com.ar>");
MODULE_DESCRIPTION("NXP LPC18xx EEPROM memory Driver");
MODULE_LICENSE("GPL v2");
