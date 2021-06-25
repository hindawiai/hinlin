<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Ingenic JZ47xx remoteproc driver
 * Copyright 2019, Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>

#समावेश "remoteproc_internal.h"

#घोषणा REG_AUX_CTRL		0x0
#घोषणा REG_AUX_MSG_ACK		0x10
#घोषणा REG_AUX_MSG		0x14
#घोषणा REG_CORE_MSG_ACK	0x18
#घोषणा REG_CORE_MSG		0x1C

#घोषणा AUX_CTRL_SLEEP		BIT(31)
#घोषणा AUX_CTRL_MSG_IRQ_EN	BIT(3)
#घोषणा AUX_CTRL_NMI_RESETS	BIT(2)
#घोषणा AUX_CTRL_NMI		BIT(1)
#घोषणा AUX_CTRL_SW_RESET	BIT(0)

अटल bool स्वतः_boot;
module_param(स्वतः_boot, bool, 0400);
MODULE_PARM_DESC(स्वतः_boot,
		 "Auto-boot the remote processor [default=false]");

काष्ठा vpu_mem_map अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक da;
पूर्ण;

काष्ठा vpu_mem_info अणु
	स्थिर काष्ठा vpu_mem_map *map;
	अचिन्हित दीर्घ len;
	व्योम __iomem *base;
पूर्ण;

अटल स्थिर काष्ठा vpu_mem_map vpu_mem_map[] = अणु
	अणु "tcsm0", 0x132b0000 पूर्ण,
	अणु "tcsm1", 0xf4000000 पूर्ण,
	अणु "sram",  0x132f0000 पूर्ण,
पूर्ण;

/**
 * काष्ठा vpu - Ingenic VPU remoteproc निजी काष्ठाure
 * @irq: पूर्णांकerrupt number
 * @clks: poपूर्णांकers to the VPU and AUX घड़ीs
 * @aux_base: raw poपूर्णांकer to the AUX पूर्णांकerface रेजिस्टरs
 * @mem_info: array of काष्ठा vpu_mem_info, which contain the mapping info of
 *            each of the बाह्यal memories
 * @dev: निजी poपूर्णांकer to the device
 */
काष्ठा vpu अणु
	पूर्णांक irq;
	काष्ठा clk_bulk_data clks[2];
	व्योम __iomem *aux_base;
	काष्ठा vpu_mem_info mem_info[ARRAY_SIZE(vpu_mem_map)];
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक ingenic_rproc_prepare(काष्ठा rproc *rproc)
अणु
	काष्ठा vpu *vpu = rproc->priv;
	पूर्णांक ret;

	/* The घड़ीs must be enabled क्रम the firmware to be loaded in TCSM */
	ret = clk_bulk_prepare_enable(ARRAY_SIZE(vpu->clks), vpu->clks);
	अगर (ret)
		dev_err(vpu->dev, "Unable to start clocks: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_rproc_unprepare(काष्ठा rproc *rproc)
अणु
	काष्ठा vpu *vpu = rproc->priv;

	clk_bulk_disable_unprepare(ARRAY_SIZE(vpu->clks), vpu->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा vpu *vpu = rproc->priv;
	u32 ctrl;

	enable_irq(vpu->irq);

	/* Reset the AUX and enable message IRQ */
	ctrl = AUX_CTRL_NMI_RESETS | AUX_CTRL_NMI | AUX_CTRL_MSG_IRQ_EN;
	ग_लिखोl(ctrl, vpu->aux_base + REG_AUX_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा vpu *vpu = rproc->priv;

	disable_irq(vpu->irq);

	/* Keep AUX in reset mode */
	ग_लिखोl(AUX_CTRL_SW_RESET, vpu->aux_base + REG_AUX_CTRL);

	वापस 0;
पूर्ण

अटल व्योम ingenic_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा vpu *vpu = rproc->priv;

	ग_लिखोl(vqid, vpu->aux_base + REG_CORE_MSG);
पूर्ण

अटल व्योम *ingenic_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा vpu *vpu = rproc->priv;
	व्योम __iomem *va = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vpu_mem_map); i++) अणु
		स्थिर काष्ठा vpu_mem_info *info = &vpu->mem_info[i];
		स्थिर काष्ठा vpu_mem_map *map = info->map;

		अगर (da >= map->da && (da + len) < (map->da + info->len)) अणु
			va = info->base + (da - map->da);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (__क्रमce व्योम *)va;
पूर्ण

अटल स्थिर काष्ठा rproc_ops ingenic_rproc_ops = अणु
	.prepare = ingenic_rproc_prepare,
	.unprepare = ingenic_rproc_unprepare,
	.start = ingenic_rproc_start,
	.stop = ingenic_rproc_stop,
	.kick = ingenic_rproc_kick,
	.da_to_va = ingenic_rproc_da_to_va,
पूर्ण;

अटल irqवापस_t vpu_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rproc *rproc = data;
	काष्ठा vpu *vpu = rproc->priv;
	u32 vring;

	vring = पढ़ोl(vpu->aux_base + REG_AUX_MSG);

	/* Ack the पूर्णांकerrupt */
	ग_लिखोl(0, vpu->aux_base + REG_AUX_MSG_ACK);

	वापस rproc_vq_पूर्णांकerrupt(rproc, vring);
पूर्ण

अटल पूर्णांक ingenic_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *mem;
	काष्ठा rproc *rproc;
	काष्ठा vpu *vpu;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	rproc = devm_rproc_alloc(dev, "ingenic-vpu",
				 &ingenic_rproc_ops, शून्य, माप(*vpu));
	अगर (!rproc)
		वापस -ENOMEM;

	rproc->स्वतः_boot = स्वतः_boot;

	vpu = rproc->priv;
	vpu->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, vpu);

	mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "aux");
	vpu->aux_base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(vpu->aux_base)) अणु
		dev_err(dev, "Failed to ioremap\n");
		वापस PTR_ERR(vpu->aux_base);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vpu_mem_map); i++) अणु
		mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   vpu_mem_map[i].name);

		vpu->mem_info[i].base = devm_ioremap_resource(dev, mem);
		अगर (IS_ERR(vpu->mem_info[i].base)) अणु
			ret = PTR_ERR(vpu->mem_info[i].base);
			dev_err(dev, "Failed to ioremap\n");
			वापस ret;
		पूर्ण

		vpu->mem_info[i].len = resource_size(mem);
		vpu->mem_info[i].map = &vpu_mem_map[i];
	पूर्ण

	vpu->clks[0].id = "vpu";
	vpu->clks[1].id = "aux";

	ret = devm_clk_bulk_get(dev, ARRAY_SIZE(vpu->clks), vpu->clks);
	अगर (ret) अणु
		dev_err(dev, "Failed to get clocks\n");
		वापस ret;
	पूर्ण

	vpu->irq = platक्रमm_get_irq(pdev, 0);
	अगर (vpu->irq < 0)
		वापस vpu->irq;

	ret = devm_request_irq(dev, vpu->irq, vpu_पूर्णांकerrupt, 0, "VPU", rproc);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request IRQ\n");
		वापस ret;
	पूर्ण

	disable_irq(vpu->irq);

	ret = devm_rproc_add(dev, rproc);
	अगर (ret) अणु
		dev_err(dev, "Failed to register remote processor\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_rproc_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4770-vpu-rproc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_rproc_of_matches);

अटल काष्ठा platक्रमm_driver ingenic_rproc_driver = अणु
	.probe = ingenic_rproc_probe,
	.driver = अणु
		.name = "ingenic-vpu",
		.of_match_table = ingenic_rproc_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ingenic_rproc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic JZ47xx Remote Processor control driver");
