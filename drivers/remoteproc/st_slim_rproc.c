<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SLIM core rproc driver
 *
 * Copyright (C) 2016 STMicroelectronics
 *
 * Author: Peter Grअगरfin <peter.grअगरfin@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/remoteproc/st_slim_rproc.h>
#समावेश "remoteproc_internal.h"

/* SLIM core रेजिस्टरs */
#घोषणा SLIM_ID_OFST		0x0
#घोषणा SLIM_VER_OFST		0x4

#घोषणा SLIM_EN_OFST		0x8
#घोषणा SLIM_EN_RUN			BIT(0)

#घोषणा SLIM_CLK_GATE_OFST	0xC
#घोषणा SLIM_CLK_GATE_DIS		BIT(0)
#घोषणा SLIM_CLK_GATE_RESET		BIT(2)

#घोषणा SLIM_SLIM_PC_OFST	0x20

/* DMEM रेजिस्टरs */
#घोषणा SLIM_REV_ID_OFST	0x0
#घोषणा SLIM_REV_ID_MIN_MASK		GENMASK(15, 8)
#घोषणा SLIM_REV_ID_MIN(id)		((id & SLIM_REV_ID_MIN_MASK) >> 8)
#घोषणा SLIM_REV_ID_MAJ_MASK		GENMASK(23, 16)
#घोषणा SLIM_REV_ID_MAJ(id)		((id & SLIM_REV_ID_MAJ_MASK) >> 16)


/* peripherals रेजिस्टरs */
#घोषणा SLIM_STBUS_SYNC_OFST	0xF88
#घोषणा SLIM_STBUS_SYNC_DIS		BIT(0)

#घोषणा SLIM_INT_SET_OFST	0xFD4
#घोषणा SLIM_INT_CLR_OFST	0xFD8
#घोषणा SLIM_INT_MASK_OFST	0xFDC

#घोषणा SLIM_CMD_CLR_OFST	0xFC8
#घोषणा SLIM_CMD_MASK_OFST	0xFCC

अटल स्थिर अक्षर *mem_names[ST_SLIM_MEM_MAX] = अणु
	[ST_SLIM_DMEM]	= "dmem",
	[ST_SLIM_IMEM]	= "imem",
पूर्ण;

अटल पूर्णांक slim_clk_get(काष्ठा st_slim_rproc *slim_rproc, काष्ठा device *dev)
अणु
	पूर्णांक clk, err;

	क्रम (clk = 0; clk < ST_SLIM_MAX_CLK; clk++) अणु
		slim_rproc->clks[clk] = of_clk_get(dev->of_node, clk);
		अगर (IS_ERR(slim_rproc->clks[clk])) अणु
			err = PTR_ERR(slim_rproc->clks[clk]);
			अगर (err == -EPROBE_DEFER)
				जाओ err_put_clks;
			slim_rproc->clks[clk] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

err_put_clks:
	जबतक (--clk >= 0)
		clk_put(slim_rproc->clks[clk]);

	वापस err;
पूर्ण

अटल व्योम slim_clk_disable(काष्ठा st_slim_rproc *slim_rproc)
अणु
	पूर्णांक clk;

	क्रम (clk = 0; clk < ST_SLIM_MAX_CLK && slim_rproc->clks[clk]; clk++)
		clk_disable_unprepare(slim_rproc->clks[clk]);
पूर्ण

अटल पूर्णांक slim_clk_enable(काष्ठा st_slim_rproc *slim_rproc)
अणु
	पूर्णांक clk, ret;

	क्रम (clk = 0; clk < ST_SLIM_MAX_CLK && slim_rproc->clks[clk]; clk++) अणु
		ret = clk_prepare_enable(slim_rproc->clks[clk]);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण

	वापस 0;

err_disable_clks:
	जबतक (--clk >= 0)
		clk_disable_unprepare(slim_rproc->clks[clk]);

	वापस ret;
पूर्ण

/*
 * Remoteproc slim specअगरic device handlers
 */
अटल पूर्णांक slim_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	काष्ठा st_slim_rproc *slim_rproc = rproc->priv;
	अचिन्हित दीर्घ hw_id, hw_ver, fw_rev;
	u32 val;

	/* disable CPU pipeline घड़ी & reset CPU pipeline */
	val = SLIM_CLK_GATE_DIS | SLIM_CLK_GATE_RESET;
	ग_लिखोl(val, slim_rproc->slimcore + SLIM_CLK_GATE_OFST);

	/* disable SLIM core STBus sync */
	ग_लिखोl(SLIM_STBUS_SYNC_DIS, slim_rproc->peri + SLIM_STBUS_SYNC_OFST);

	/* enable cpu pipeline घड़ी */
	ग_लिखोl(!SLIM_CLK_GATE_DIS,
		slim_rproc->slimcore + SLIM_CLK_GATE_OFST);

	/* clear पूर्णांक & cmd mailbox */
	ग_लिखोl(~0U, slim_rproc->peri + SLIM_INT_CLR_OFST);
	ग_लिखोl(~0U, slim_rproc->peri + SLIM_CMD_CLR_OFST);

	/* enable all channels cmd & पूर्णांक */
	ग_लिखोl(~0U, slim_rproc->peri + SLIM_INT_MASK_OFST);
	ग_लिखोl(~0U, slim_rproc->peri + SLIM_CMD_MASK_OFST);

	/* enable cpu */
	ग_लिखोl(SLIM_EN_RUN, slim_rproc->slimcore + SLIM_EN_OFST);

	hw_id = पढ़ोl_relaxed(slim_rproc->slimcore + SLIM_ID_OFST);
	hw_ver = पढ़ोl_relaxed(slim_rproc->slimcore + SLIM_VER_OFST);

	fw_rev = पढ़ोl(slim_rproc->mem[ST_SLIM_DMEM].cpu_addr +
			SLIM_REV_ID_OFST);

	dev_info(dev, "fw rev:%ld.%ld on SLIM %ld.%ld\n",
		 SLIM_REV_ID_MAJ(fw_rev), SLIM_REV_ID_MIN(fw_rev),
		 hw_id, hw_ver);

	वापस 0;
पूर्ण

अटल पूर्णांक slim_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा st_slim_rproc *slim_rproc = rproc->priv;
	u32 val;

	/* mask all (cmd & पूर्णांक) channels */
	ग_लिखोl(0UL, slim_rproc->peri + SLIM_INT_MASK_OFST);
	ग_लिखोl(0UL, slim_rproc->peri + SLIM_CMD_MASK_OFST);

	/* disable cpu pipeline घड़ी */
	ग_लिखोl(SLIM_CLK_GATE_DIS, slim_rproc->slimcore + SLIM_CLK_GATE_OFST);

	ग_लिखोl(!SLIM_EN_RUN, slim_rproc->slimcore + SLIM_EN_OFST);

	val = पढ़ोl(slim_rproc->slimcore + SLIM_EN_OFST);
	अगर (val & SLIM_EN_RUN)
		dev_warn(&rproc->dev, "Failed to disable SLIM");

	dev_dbg(&rproc->dev, "slim stopped\n");

	वापस 0;
पूर्ण

अटल व्योम *slim_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा st_slim_rproc *slim_rproc = rproc->priv;
	व्योम *va = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ST_SLIM_MEM_MAX; i++) अणु
		अगर (da != slim_rproc->mem[i].bus_addr)
			जारी;

		अगर (len <= slim_rproc->mem[i].size) अणु
			/* __क्रमce to make sparse happy with type conversion */
			va = (__क्रमce व्योम *)slim_rproc->mem[i].cpu_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg(&rproc->dev, "da = 0x%llx len = 0x%zx va = 0x%pK\n",
		da, len, va);

	वापस va;
पूर्ण

अटल स्थिर काष्ठा rproc_ops slim_rproc_ops = अणु
	.start		= slim_rproc_start,
	.stop		= slim_rproc_stop,
	.da_to_va       = slim_rproc_da_to_va,
	.get_boot_addr	= rproc_elf_get_boot_addr,
	.load		= rproc_elf_load_segments,
	.sanity_check	= rproc_elf_sanity_check,
पूर्ण;

/**
 * st_slim_rproc_alloc() - allocate and initialise slim rproc
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठा
 * @fw_name: Name of firmware क्रम rproc to use
 *
 * Function क्रम allocating and initialising a slim rproc क्रम use by
 * device drivers whose IP is based around the SLIM core. It
 * obtains and enables any घड़ीs required by the SLIM core and also
 * ioremaps the various IO.
 *
 * Returns st_slim_rproc poपूर्णांकer or PTR_ERR() on error.
 */

काष्ठा st_slim_rproc *st_slim_rproc_alloc(काष्ठा platक्रमm_device *pdev,
				अक्षर *fw_name)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा st_slim_rproc *slim_rproc;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rproc *rproc;
	काष्ठा resource *res;
	पूर्णांक err, i;

	अगर (!fw_name)
		वापस ERR_PTR(-EINVAL);

	अगर (!of_device_is_compatible(np, "st,slim-rproc"))
		वापस ERR_PTR(-EINVAL);

	rproc = rproc_alloc(dev, np->name, &slim_rproc_ops,
			fw_name, माप(*slim_rproc));
	अगर (!rproc)
		वापस ERR_PTR(-ENOMEM);

	rproc->has_iommu = false;

	slim_rproc = rproc->priv;
	slim_rproc->rproc = rproc;

	/* get imem and dmem */
	क्रम (i = 0; i < ARRAY_SIZE(mem_names); i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						mem_names[i]);

		slim_rproc->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(slim_rproc->mem[i].cpu_addr)) अणु
			dev_err(&pdev->dev, "devm_ioremap_resource failed\n");
			err = PTR_ERR(slim_rproc->mem[i].cpu_addr);
			जाओ err;
		पूर्ण
		slim_rproc->mem[i].bus_addr = res->start;
		slim_rproc->mem[i].size = resource_size(res);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "slimcore");
	slim_rproc->slimcore = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(slim_rproc->slimcore)) अणु
		dev_err(&pdev->dev, "failed to ioremap slimcore IO\n");
		err = PTR_ERR(slim_rproc->slimcore);
		जाओ err;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "peripherals");
	slim_rproc->peri = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(slim_rproc->peri)) अणु
		dev_err(&pdev->dev, "failed to ioremap peripherals IO\n");
		err = PTR_ERR(slim_rproc->peri);
		जाओ err;
	पूर्ण

	err = slim_clk_get(slim_rproc, dev);
	अगर (err)
		जाओ err;

	err = slim_clk_enable(slim_rproc);
	अगर (err) अणु
		dev_err(dev, "Failed to enable clocks\n");
		जाओ err_clk_put;
	पूर्ण

	/* Register as a remoteproc device */
	err = rproc_add(rproc);
	अगर (err) अणु
		dev_err(dev, "registration of slim remoteproc failed\n");
		जाओ err_clk_dis;
	पूर्ण

	वापस slim_rproc;

err_clk_dis:
	slim_clk_disable(slim_rproc);
err_clk_put:
	क्रम (i = 0; i < ST_SLIM_MAX_CLK && slim_rproc->clks[i]; i++)
		clk_put(slim_rproc->clks[i]);
err:
	rproc_मुक्त(rproc);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(st_slim_rproc_alloc);

/**
  * st_slim_rproc_put() - put slim rproc resources
  * @slim_rproc: Poपूर्णांकer to the st_slim_rproc काष्ठा
  *
  * Function क्रम calling respective _put() functions on slim_rproc resources.
  *
  */
व्योम st_slim_rproc_put(काष्ठा st_slim_rproc *slim_rproc)
अणु
	पूर्णांक clk;

	अगर (!slim_rproc)
		वापस;

	slim_clk_disable(slim_rproc);

	क्रम (clk = 0; clk < ST_SLIM_MAX_CLK && slim_rproc->clks[clk]; clk++)
		clk_put(slim_rproc->clks[clk]);

	rproc_del(slim_rproc->rproc);
	rproc_मुक्त(slim_rproc->rproc);
पूर्ण
EXPORT_SYMBOL(st_slim_rproc_put);

MODULE_AUTHOR("Peter Griffin <peter.griffin@linaro.org>");
MODULE_DESCRIPTION("STMicroelectronics SLIM core rproc driver");
MODULE_LICENSE("GPL v2");
