<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM PL353 SMC driver
 *
 * Copyright (C) 2012 - 2018 Xilinx, Inc
 * Author: Punnaiah Choudary Kalluri <punnaiah@xilinx.com>
 * Author: Naga Sureshkumar Relli <nagasure@xilinx.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/pl353-smc.h>
#समावेश <linux/amba/bus.h>

/* Register definitions */
#घोषणा PL353_SMC_MEMC_STATUS_OFFS	0	/* Controller status reg, RO */
#घोषणा PL353_SMC_CFG_CLR_OFFS		0xC	/* Clear config reg, WO */
#घोषणा PL353_SMC_सूचीECT_CMD_OFFS	0x10	/* Direct command reg, WO */
#घोषणा PL353_SMC_SET_CYCLES_OFFS	0x14	/* Set cycles रेजिस्टर, WO */
#घोषणा PL353_SMC_SET_OPMODE_OFFS	0x18	/* Set opmode रेजिस्टर, WO */
#घोषणा PL353_SMC_ECC_STATUS_OFFS	0x400	/* ECC status रेजिस्टर */
#घोषणा PL353_SMC_ECC_MEMCFG_OFFS	0x404	/* ECC mem config reg */
#घोषणा PL353_SMC_ECC_MEMCMD1_OFFS	0x408	/* ECC mem cmd1 reg */
#घोषणा PL353_SMC_ECC_MEMCMD2_OFFS	0x40C	/* ECC mem cmd2 reg */
#घोषणा PL353_SMC_ECC_VALUE0_OFFS	0x418	/* ECC value 0 reg */

/* Controller status रेजिस्टर specअगरic स्थिरants */
#घोषणा PL353_SMC_MEMC_STATUS_RAW_INT_1_SHIFT	6

/* Clear configuration रेजिस्टर specअगरic स्थिरants */
#घोषणा PL353_SMC_CFG_CLR_INT_CLR_1	0x10
#घोषणा PL353_SMC_CFG_CLR_ECC_INT_DIS_1	0x40
#घोषणा PL353_SMC_CFG_CLR_INT_DIS_1	0x2
#घोषणा PL353_SMC_CFG_CLR_DEFAULT_MASK	(PL353_SMC_CFG_CLR_INT_CLR_1 | \
					 PL353_SMC_CFG_CLR_ECC_INT_DIS_1 | \
					 PL353_SMC_CFG_CLR_INT_DIS_1)

/* Set cycles रेजिस्टर specअगरic स्थिरants */
#घोषणा PL353_SMC_SET_CYCLES_T0_MASK	0xF
#घोषणा PL353_SMC_SET_CYCLES_T0_SHIFT	0
#घोषणा PL353_SMC_SET_CYCLES_T1_MASK	0xF
#घोषणा PL353_SMC_SET_CYCLES_T1_SHIFT	4
#घोषणा PL353_SMC_SET_CYCLES_T2_MASK	0x7
#घोषणा PL353_SMC_SET_CYCLES_T2_SHIFT	8
#घोषणा PL353_SMC_SET_CYCLES_T3_MASK	0x7
#घोषणा PL353_SMC_SET_CYCLES_T3_SHIFT	11
#घोषणा PL353_SMC_SET_CYCLES_T4_MASK	0x7
#घोषणा PL353_SMC_SET_CYCLES_T4_SHIFT	14
#घोषणा PL353_SMC_SET_CYCLES_T5_MASK	0x7
#घोषणा PL353_SMC_SET_CYCLES_T5_SHIFT	17
#घोषणा PL353_SMC_SET_CYCLES_T6_MASK	0xF
#घोषणा PL353_SMC_SET_CYCLES_T6_SHIFT	20

/* ECC status रेजिस्टर specअगरic स्थिरants */
#घोषणा PL353_SMC_ECC_STATUS_BUSY	BIT(6)
#घोषणा PL353_SMC_ECC_REG_SIZE_OFFS	4

/* ECC memory config रेजिस्टर specअगरic स्थिरants */
#घोषणा PL353_SMC_ECC_MEMCFG_MODE_MASK	0xC
#घोषणा PL353_SMC_ECC_MEMCFG_MODE_SHIFT	2
#घोषणा PL353_SMC_ECC_MEMCFG_PGSIZE_MASK	0x3

#घोषणा PL353_SMC_DC_UPT_न_अंकD_REGS	((4 << 23) |	/* CS: न_अंकD chip */ \
				 (2 << 21))	/* UpdateRegs operation */

#घोषणा PL353_न_अंकD_ECC_CMD1	((0x80)       |	/* Write command */ \
				 (0 << 8)     |	/* Read command */ \
				 (0x30 << 16) |	/* Read End command */ \
				 (1 << 24))	/* Read End command calid */

#घोषणा PL353_न_अंकD_ECC_CMD2	((0x85)	      |	/* Write col change cmd */ \
				 (5 << 8)     |	/* Read col change cmd */ \
				 (0xE0 << 16) |	/* Read col change end cmd */ \
				 (1 << 24)) /* Read col change end cmd valid */
#घोषणा PL353_न_अंकD_ECC_BUSY_TIMEOUT	(1 * HZ)
/**
 * काष्ठा pl353_smc_data - Private smc driver काष्ठाure
 * @memclk:		Poपूर्णांकer to the peripheral घड़ी
 * @aclk:		Poपूर्णांकer to the APER घड़ी
 */
काष्ठा pl353_smc_data अणु
	काष्ठा clk		*memclk;
	काष्ठा clk		*aclk;
पूर्ण;

/* SMC भव रेजिस्टर base */
अटल व्योम __iomem *pl353_smc_base;

/**
 * pl353_smc_set_buswidth - Set memory buswidth
 * @bw: Memory buswidth (8 | 16)
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक pl353_smc_set_buswidth(अचिन्हित पूर्णांक bw)
अणु
	अगर (bw != PL353_SMC_MEM_WIDTH_8  && bw != PL353_SMC_MEM_WIDTH_16)
		वापस -EINVAL;

	ग_लिखोl(bw, pl353_smc_base + PL353_SMC_SET_OPMODE_OFFS);
	ग_लिखोl(PL353_SMC_DC_UPT_न_अंकD_REGS, pl353_smc_base +
	       PL353_SMC_सूचीECT_CMD_OFFS);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_set_buswidth);

/**
 * pl353_smc_set_cycles - Set memory timing parameters
 * @timings: न_अंकD controller timing parameters
 *
 * Sets न_अंकD chip specअगरic timing parameters.
 */
व्योम pl353_smc_set_cycles(u32 timings[])
अणु
	/*
	 * Set ग_लिखो pulse timing. This one is easy to extract:
	 *
	 * NWE_PULSE = tWP
	 */
	timings[0] &= PL353_SMC_SET_CYCLES_T0_MASK;
	timings[1] = (timings[1] & PL353_SMC_SET_CYCLES_T1_MASK) <<
			PL353_SMC_SET_CYCLES_T1_SHIFT;
	timings[2] = (timings[2]  & PL353_SMC_SET_CYCLES_T2_MASK) <<
			PL353_SMC_SET_CYCLES_T2_SHIFT;
	timings[3] = (timings[3]  & PL353_SMC_SET_CYCLES_T3_MASK) <<
			PL353_SMC_SET_CYCLES_T3_SHIFT;
	timings[4] = (timings[4] & PL353_SMC_SET_CYCLES_T4_MASK) <<
			PL353_SMC_SET_CYCLES_T4_SHIFT;
	timings[5]  = (timings[5]  & PL353_SMC_SET_CYCLES_T5_MASK) <<
			PL353_SMC_SET_CYCLES_T5_SHIFT;
	timings[6]  = (timings[6]  & PL353_SMC_SET_CYCLES_T6_MASK) <<
			PL353_SMC_SET_CYCLES_T6_SHIFT;
	timings[0] |= timings[1] | timings[2] | timings[3] |
			timings[4] | timings[5] | timings[6];

	ग_लिखोl(timings[0], pl353_smc_base + PL353_SMC_SET_CYCLES_OFFS);
	ग_लिखोl(PL353_SMC_DC_UPT_न_अंकD_REGS, pl353_smc_base +
	       PL353_SMC_सूचीECT_CMD_OFFS);
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_set_cycles);

/**
 * pl353_smc_ecc_is_busy - Read ecc busy flag
 * Return: the ecc_status bit from the ecc_status रेजिस्टर. 1 = busy, 0 = idle
 */
bool pl353_smc_ecc_is_busy(व्योम)
अणु
	वापस ((पढ़ोl(pl353_smc_base + PL353_SMC_ECC_STATUS_OFFS) &
		  PL353_SMC_ECC_STATUS_BUSY) == PL353_SMC_ECC_STATUS_BUSY);
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_ecc_is_busy);

/**
 * pl353_smc_get_ecc_val - Read ecc_valueN रेजिस्टरs
 * @ecc_reg: Index of the ecc_value reg (0..3)
 * Return: the content of the requested ecc_value रेजिस्टर.
 *
 * There are four valid ecc_value रेजिस्टरs. The argument is truncated to stay
 * within this valid boundary.
 */
u32 pl353_smc_get_ecc_val(पूर्णांक ecc_reg)
अणु
	u32 addr, reg;

	addr = PL353_SMC_ECC_VALUE0_OFFS +
		(ecc_reg * PL353_SMC_ECC_REG_SIZE_OFFS);
	reg = पढ़ोl(pl353_smc_base + addr);

	वापस reg;
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_get_ecc_val);

/**
 * pl353_smc_get_nand_पूर्णांक_status_raw - Get न_अंकD पूर्णांकerrupt status bit
 * Return: the raw_पूर्णांक_status1 bit from the memc_status रेजिस्टर
 */
पूर्णांक pl353_smc_get_nand_पूर्णांक_status_raw(व्योम)
अणु
	u32 reg;

	reg = पढ़ोl(pl353_smc_base + PL353_SMC_MEMC_STATUS_OFFS);
	reg >>= PL353_SMC_MEMC_STATUS_RAW_INT_1_SHIFT;
	reg &= 1;

	वापस reg;
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_get_nand_पूर्णांक_status_raw);

/**
 * pl353_smc_clr_nand_पूर्णांक - Clear न_अंकD पूर्णांकerrupt
 */
व्योम pl353_smc_clr_nand_पूर्णांक(व्योम)
अणु
	ग_लिखोl(PL353_SMC_CFG_CLR_INT_CLR_1,
	       pl353_smc_base + PL353_SMC_CFG_CLR_OFFS);
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_clr_nand_पूर्णांक);

/**
 * pl353_smc_set_ecc_mode - Set SMC ECC mode
 * @mode: ECC mode (BYPASS, APB, MEM)
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक pl353_smc_set_ecc_mode(क्रमागत pl353_smc_ecc_mode mode)
अणु
	u32 reg;
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल PL353_SMC_ECCMODE_BYPASS:
	हाल PL353_SMC_ECCMODE_APB:
	हाल PL353_SMC_ECCMODE_MEM:

		reg = पढ़ोl(pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);
		reg &= ~PL353_SMC_ECC_MEMCFG_MODE_MASK;
		reg |= mode << PL353_SMC_ECC_MEMCFG_MODE_SHIFT;
		ग_लिखोl(reg, pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_set_ecc_mode);

/**
 * pl353_smc_set_ecc_pg_size - Set SMC ECC page size
 * @pg_sz: ECC page size
 * Return: 0 on success or negative त्रुटि_सं.
 */
पूर्णांक pl353_smc_set_ecc_pg_size(अचिन्हित पूर्णांक pg_sz)
अणु
	u32 reg, sz;

	चयन (pg_sz) अणु
	हाल 0:
		sz = 0;
		अवरोध;
	हाल SZ_512:
		sz = 1;
		अवरोध;
	हाल SZ_1K:
		sz = 2;
		अवरोध;
	हाल SZ_2K:
		sz = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = पढ़ोl(pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);
	reg &= ~PL353_SMC_ECC_MEMCFG_PGSIZE_MASK;
	reg |= sz;
	ग_लिखोl(reg, pl353_smc_base + PL353_SMC_ECC_MEMCFG_OFFS);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pl353_smc_set_ecc_pg_size);

अटल पूर्णांक __maybe_unused pl353_smc_suspend(काष्ठा device *dev)
अणु
	काष्ठा pl353_smc_data *pl353_smc = dev_get_drvdata(dev);

	clk_disable(pl353_smc->memclk);
	clk_disable(pl353_smc->aclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pl353_smc_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा pl353_smc_data *pl353_smc = dev_get_drvdata(dev);

	ret = clk_enable(pl353_smc->aclk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable axi domain clock.\n");
		वापस ret;
	पूर्ण

	ret = clk_enable(pl353_smc->memclk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable memory clock.\n");
		clk_disable(pl353_smc->aclk);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा amba_driver pl353_smc_driver;

अटल SIMPLE_DEV_PM_OPS(pl353_smc_dev_pm_ops, pl353_smc_suspend,
			 pl353_smc_resume);

/**
 * pl353_smc_init_nand_पूर्णांकerface - Initialize the न_अंकD पूर्णांकerface
 * @adev: Poपूर्णांकer to the amba_device काष्ठा
 * @nand_node: Poपूर्णांकer to the pl353_nand device_node काष्ठा
 */
अटल व्योम pl353_smc_init_nand_पूर्णांकerface(काष्ठा amba_device *adev,
					  काष्ठा device_node *nand_node)
अणु
	अचिन्हित दीर्घ समयout;

	pl353_smc_set_buswidth(PL353_SMC_MEM_WIDTH_8);
	ग_लिखोl(PL353_SMC_CFG_CLR_INT_CLR_1,
	       pl353_smc_base + PL353_SMC_CFG_CLR_OFFS);
	ग_लिखोl(PL353_SMC_DC_UPT_न_अंकD_REGS, pl353_smc_base +
	       PL353_SMC_सूचीECT_CMD_OFFS);

	समयout = jअगरfies + PL353_न_अंकD_ECC_BUSY_TIMEOUT;
	/* Wait till the ECC operation is complete */
	करो अणु
		अगर (pl353_smc_ecc_is_busy())
			cpu_relax();
		अन्यथा
			अवरोध;
	पूर्ण जबतक (!समय_after_eq(jअगरfies, समयout));

	अगर (समय_after_eq(jअगरfies, समयout))
		वापस;

	ग_लिखोl(PL353_न_अंकD_ECC_CMD1,
	       pl353_smc_base + PL353_SMC_ECC_MEMCMD1_OFFS);
	ग_लिखोl(PL353_न_अंकD_ECC_CMD2,
	       pl353_smc_base + PL353_SMC_ECC_MEMCMD2_OFFS);
पूर्ण

अटल स्थिर काष्ठा of_device_id pl353_smc_supported_children[] = अणु
	अणु
		.compatible = "cfi-flash"
	पूर्ण,
	अणु
		.compatible = "arm,pl353-nand-r2p1",
		.data = pl353_smc_init_nand_पूर्णांकerface
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक pl353_smc_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा pl353_smc_data *pl353_smc;
	काष्ठा device_node *child;
	काष्ठा resource *res;
	पूर्णांक err;
	काष्ठा device_node *of_node = adev->dev.of_node;
	अटल व्योम (*init)(काष्ठा amba_device *adev,
			    काष्ठा device_node *nand_node);
	स्थिर काष्ठा of_device_id *match = शून्य;

	pl353_smc = devm_kzalloc(&adev->dev, माप(*pl353_smc), GFP_KERNEL);
	अगर (!pl353_smc)
		वापस -ENOMEM;

	/* Get the न_अंकD controller भव address */
	res = &adev->res;
	pl353_smc_base = devm_ioremap_resource(&adev->dev, res);
	अगर (IS_ERR(pl353_smc_base))
		वापस PTR_ERR(pl353_smc_base);

	pl353_smc->aclk = devm_clk_get(&adev->dev, "apb_pclk");
	अगर (IS_ERR(pl353_smc->aclk)) अणु
		dev_err(&adev->dev, "aclk clock not found.\n");
		वापस PTR_ERR(pl353_smc->aclk);
	पूर्ण

	pl353_smc->memclk = devm_clk_get(&adev->dev, "memclk");
	अगर (IS_ERR(pl353_smc->memclk)) अणु
		dev_err(&adev->dev, "memclk clock not found.\n");
		वापस PTR_ERR(pl353_smc->memclk);
	पूर्ण

	err = clk_prepare_enable(pl353_smc->aclk);
	अगर (err) अणु
		dev_err(&adev->dev, "Unable to enable AXI clock.\n");
		वापस err;
	पूर्ण

	err = clk_prepare_enable(pl353_smc->memclk);
	अगर (err) अणु
		dev_err(&adev->dev, "Unable to enable memory clock.\n");
		जाओ out_clk_dis_aper;
	पूर्ण

	amba_set_drvdata(adev, pl353_smc);

	/* clear पूर्णांकerrupts */
	ग_लिखोl(PL353_SMC_CFG_CLR_DEFAULT_MASK,
	       pl353_smc_base + PL353_SMC_CFG_CLR_OFFS);

	/* Find compatible children. Only a single child is supported */
	क्रम_each_available_child_of_node(of_node, child) अणु
		match = of_match_node(pl353_smc_supported_children, child);
		अगर (!match) अणु
			dev_warn(&adev->dev, "unsupported child node\n");
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!match) अणु
		dev_err(&adev->dev, "no matching children\n");
		जाओ out_clk_disable;
	पूर्ण

	init = match->data;
	अगर (init)
		init(adev, child);
	of_platक्रमm_device_create(child, शून्य, &adev->dev);

	वापस 0;

out_clk_disable:
	clk_disable_unprepare(pl353_smc->memclk);
out_clk_dis_aper:
	clk_disable_unprepare(pl353_smc->aclk);

	वापस err;
पूर्ण

अटल व्योम pl353_smc_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा pl353_smc_data *pl353_smc = amba_get_drvdata(adev);

	clk_disable_unprepare(pl353_smc->memclk);
	clk_disable_unprepare(pl353_smc->aclk);
पूर्ण

अटल स्थिर काष्ठा amba_id pl353_ids[] = अणु
	अणु
	.id = 0x00041353,
	.mask = 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, pl353_ids);

अटल काष्ठा amba_driver pl353_smc_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = "pl353-smc",
		.pm = &pl353_smc_dev_pm_ops,
	पूर्ण,
	.id_table = pl353_ids,
	.probe = pl353_smc_probe,
	.हटाओ = pl353_smc_हटाओ,
पूर्ण;

module_amba_driver(pl353_smc_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("ARM PL353 SMC Driver");
MODULE_LICENSE("GPL");
