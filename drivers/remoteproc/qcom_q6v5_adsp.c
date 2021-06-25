<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm Technology Inc. ADSP Peripheral Image Loader क्रम SDM845.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>

#समावेश "qcom_common.h"
#समावेश "qcom_pil_info.h"
#समावेश "qcom_q6v5.h"
#समावेश "remoteproc_internal.h"

/* समय out value */
#घोषणा ACK_TIMEOUT			1000
#घोषणा BOOT_FSM_TIMEOUT		10000
/* mask values */
#घोषणा EVB_MASK			GENMASK(27, 4)
/*QDSP6SS रेजिस्टर offsets*/
#घोषणा RST_EVB_REG			0x10
#घोषणा CORE_START_REG			0x400
#घोषणा BOOT_CMD_REG			0x404
#घोषणा BOOT_STATUS_REG			0x408
#घोषणा RET_CFG_REG			0x1C
/*TCSR रेजिस्टर offsets*/
#घोषणा LPASS_MASTER_IDLE_REG		0x8
#घोषणा LPASS_HALTACK_REG		0x4
#घोषणा LPASS_PWR_ON_REG		0x10
#घोषणा LPASS_HALTREQ_REG		0x0

#घोषणा QDSP6SS_XO_CBCR		0x38
#घोषणा QDSP6SS_CORE_CBCR	0x20
#घोषणा QDSP6SS_SLEEP_CBCR	0x3c

काष्ठा adsp_pil_data अणु
	पूर्णांक crash_reason_smem;
	स्थिर अक्षर *firmware_name;

	स्थिर अक्षर *ssr_name;
	स्थिर अक्षर *sysmon_name;
	पूर्णांक ssctl_id;

	स्थिर अक्षर **clk_ids;
	पूर्णांक num_clks;
पूर्ण;

काष्ठा qcom_adsp अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;

	काष्ठा qcom_q6v5 q6v5;

	काष्ठा clk *xo;

	पूर्णांक num_clks;
	काष्ठा clk_bulk_data *clks;

	व्योम __iomem *qdsp6ss_base;

	काष्ठा reset_control *pdc_sync_reset;
	काष्ठा reset_control *restart;

	काष्ठा regmap *halt_map;
	अचिन्हित पूर्णांक halt_lpass;

	पूर्णांक crash_reason_smem;
	स्थिर अक्षर *info_name;

	काष्ठा completion start_करोne;
	काष्ठा completion stop_करोne;

	phys_addr_t mem_phys;
	phys_addr_t mem_reloc;
	व्योम *mem_region;
	माप_प्रकार mem_size;

	काष्ठा qcom_rproc_glink glink_subdev;
	काष्ठा qcom_rproc_ssr ssr_subdev;
	काष्ठा qcom_sysmon *sysmon;
पूर्ण;

अटल पूर्णांक qcom_adsp_shutकरोwn(काष्ठा qcom_adsp *adsp)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Reset the retention logic */
	val = पढ़ोl(adsp->qdsp6ss_base + RET_CFG_REG);
	val |= 0x1;
	ग_लिखोl(val, adsp->qdsp6ss_base + RET_CFG_REG);

	clk_bulk_disable_unprepare(adsp->num_clks, adsp->clks);

	/* QDSP6 master port needs to be explicitly halted */
	ret = regmap_पढ़ो(adsp->halt_map,
			adsp->halt_lpass + LPASS_PWR_ON_REG, &val);
	अगर (ret || !val)
		जाओ reset;

	ret = regmap_पढ़ो(adsp->halt_map,
			adsp->halt_lpass + LPASS_MASTER_IDLE_REG,
			&val);
	अगर (ret || val)
		जाओ reset;

	regmap_ग_लिखो(adsp->halt_map,
			adsp->halt_lpass + LPASS_HALTREQ_REG, 1);

	/* Wait क्रम halt ACK from QDSP6 */
	समयout = jअगरfies + msecs_to_jअगरfies(ACK_TIMEOUT);
	क्रम (;;) अणु
		ret = regmap_पढ़ो(adsp->halt_map,
			adsp->halt_lpass + LPASS_HALTACK_REG, &val);
		अगर (ret || val || समय_after(jअगरfies, समयout))
			अवरोध;

		usleep_range(1000, 1100);
	पूर्ण

	ret = regmap_पढ़ो(adsp->halt_map,
			adsp->halt_lpass + LPASS_MASTER_IDLE_REG, &val);
	अगर (ret || !val)
		dev_err(adsp->dev, "port failed halt\n");

reset:
	/* Assert the LPASS PDC Reset */
	reset_control_निश्चित(adsp->pdc_sync_reset);
	/* Place the LPASS processor पूर्णांकo reset */
	reset_control_निश्चित(adsp->restart);
	/* रुको after निश्चितing subप्रणाली restart from AOSS */
	usleep_range(200, 300);

	/* Clear the halt request क्रम the AXIM and AHBM क्रम Q6 */
	regmap_ग_लिखो(adsp->halt_map, adsp->halt_lpass + LPASS_HALTREQ_REG, 0);

	/* De-निश्चित the LPASS PDC Reset */
	reset_control_deनिश्चित(adsp->pdc_sync_reset);
	/* Remove the LPASS reset */
	reset_control_deनिश्चित(adsp->restart);
	/* रुको after de-निश्चितing subप्रणाली restart from AOSS */
	usleep_range(200, 300);

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक ret;

	ret = qcom_mdt_load_no_init(adsp->dev, fw, rproc->firmware, 0,
				    adsp->mem_region, adsp->mem_phys,
				    adsp->mem_size, &adsp->mem_reloc);
	अगर (ret)
		वापस ret;

	qcom_pil_info_store(adsp->info_name, adsp->mem_phys, adsp->mem_size);

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_start(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	qcom_q6v5_prepare(&adsp->q6v5);

	ret = clk_prepare_enable(adsp->xo);
	अगर (ret)
		जाओ disable_irqs;

	dev_pm_genpd_set_perक्रमmance_state(adsp->dev, पूर्णांक_उच्च);
	ret = pm_runसमय_get_sync(adsp->dev);
	अगर (ret) अणु
		pm_runसमय_put_noidle(adsp->dev);
		जाओ disable_xo_clk;
	पूर्ण

	ret = clk_bulk_prepare_enable(adsp->num_clks, adsp->clks);
	अगर (ret) अणु
		dev_err(adsp->dev, "adsp clk_enable failed\n");
		जाओ disable_घातer_करोमुख्य;
	पूर्ण

	/* Enable the XO घड़ी */
	ग_लिखोl(1, adsp->qdsp6ss_base + QDSP6SS_XO_CBCR);

	/* Enable the QDSP6SS sleep घड़ी */
	ग_लिखोl(1, adsp->qdsp6ss_base + QDSP6SS_SLEEP_CBCR);

	/* Enable the QDSP6 core घड़ी */
	ग_लिखोl(1, adsp->qdsp6ss_base + QDSP6SS_CORE_CBCR);

	/* Program boot address */
	ग_लिखोl(adsp->mem_phys >> 4, adsp->qdsp6ss_base + RST_EVB_REG);

	/* De-निश्चित QDSP6 stop core. QDSP6 will execute after out of reset */
	ग_लिखोl(0x1, adsp->qdsp6ss_base + CORE_START_REG);

	/* Trigger boot FSM to start QDSP6 */
	ग_लिखोl(0x1, adsp->qdsp6ss_base + BOOT_CMD_REG);

	/* Wait क्रम core to come out of reset */
	ret = पढ़ोl_poll_समयout(adsp->qdsp6ss_base + BOOT_STATUS_REG,
			val, (val & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
	अगर (ret) अणु
		dev_err(adsp->dev, "failed to bootup adsp\n");
		जाओ disable_adsp_clks;
	पूर्ण

	ret = qcom_q6v5_रुको_क्रम_start(&adsp->q6v5, msecs_to_jअगरfies(5 * HZ));
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(adsp->dev, "start timed out\n");
		जाओ disable_adsp_clks;
	पूर्ण

	वापस 0;

disable_adsp_clks:
	clk_bulk_disable_unprepare(adsp->num_clks, adsp->clks);
disable_घातer_करोमुख्य:
	dev_pm_genpd_set_perक्रमmance_state(adsp->dev, 0);
	pm_runसमय_put(adsp->dev);
disable_xo_clk:
	clk_disable_unprepare(adsp->xo);
disable_irqs:
	qcom_q6v5_unprepare(&adsp->q6v5);

	वापस ret;
पूर्ण

अटल व्योम qcom_adsp_pil_hanकरोver(काष्ठा qcom_q6v5 *q6v5)
अणु
	काष्ठा qcom_adsp *adsp = container_of(q6v5, काष्ठा qcom_adsp, q6v5);

	clk_disable_unprepare(adsp->xo);
	dev_pm_genpd_set_perक्रमmance_state(adsp->dev, 0);
	pm_runसमय_put(adsp->dev);
पूर्ण

अटल पूर्णांक adsp_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक hanकरोver;
	पूर्णांक ret;

	ret = qcom_q6v5_request_stop(&adsp->q6v5, adsp->sysmon);
	अगर (ret == -ETIMEDOUT)
		dev_err(adsp->dev, "timed out on wait\n");

	ret = qcom_adsp_shutकरोwn(adsp);
	अगर (ret)
		dev_err(adsp->dev, "failed to shutdown: %d\n", ret);

	hanकरोver = qcom_q6v5_unprepare(&adsp->q6v5);
	अगर (hanकरोver)
		qcom_adsp_pil_hanकरोver(&adsp->q6v5);

	वापस ret;
पूर्ण

अटल व्योम *adsp_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक offset;

	offset = da - adsp->mem_reloc;
	अगर (offset < 0 || offset + len > adsp->mem_size)
		वापस शून्य;

	वापस adsp->mem_region + offset;
पूर्ण

अटल अचिन्हित दीर्घ adsp_panic(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = rproc->priv;

	वापस qcom_q6v5_panic(&adsp->q6v5);
पूर्ण

अटल स्थिर काष्ठा rproc_ops adsp_ops = अणु
	.start = adsp_start,
	.stop = adsp_stop,
	.da_to_va = adsp_da_to_va,
	.parse_fw = qcom_रेजिस्टर_dump_segments,
	.load = adsp_load,
	.panic = adsp_panic,
पूर्ण;

अटल पूर्णांक adsp_init_घड़ी(काष्ठा qcom_adsp *adsp, स्थिर अक्षर **clk_ids)
अणु
	पूर्णांक num_clks = 0;
	पूर्णांक i, ret;

	adsp->xo = devm_clk_get(adsp->dev, "xo");
	अगर (IS_ERR(adsp->xo)) अणु
		ret = PTR_ERR(adsp->xo);
		अगर (ret != -EPROBE_DEFER)
			dev_err(adsp->dev, "failed to get xo clock");
		वापस ret;
	पूर्ण

	क्रम (i = 0; clk_ids[i]; i++)
		num_clks++;

	adsp->num_clks = num_clks;
	adsp->clks = devm_kसुस्मृति(adsp->dev, adsp->num_clks,
				माप(*adsp->clks), GFP_KERNEL);
	अगर (!adsp->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < adsp->num_clks; i++)
		adsp->clks[i].id = clk_ids[i];

	वापस devm_clk_bulk_get(adsp->dev, adsp->num_clks, adsp->clks);
पूर्ण

अटल पूर्णांक adsp_init_reset(काष्ठा qcom_adsp *adsp)
अणु
	adsp->pdc_sync_reset = devm_reset_control_get_optional_exclusive(adsp->dev,
			"pdc_sync");
	अगर (IS_ERR(adsp->pdc_sync_reset)) अणु
		dev_err(adsp->dev, "failed to acquire pdc_sync reset\n");
		वापस PTR_ERR(adsp->pdc_sync_reset);
	पूर्ण

	adsp->restart = devm_reset_control_get_optional_exclusive(adsp->dev, "restart");

	/* Fall back to the  old "cc_lpass" अगर "restart" is असलent */
	अगर (!adsp->restart)
		adsp->restart = devm_reset_control_get_exclusive(adsp->dev, "cc_lpass");

	अगर (IS_ERR(adsp->restart)) अणु
		dev_err(adsp->dev, "failed to acquire restart\n");
		वापस PTR_ERR(adsp->restart);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_init_mmio(काष्ठा qcom_adsp *adsp,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *syscon;
	पूर्णांक ret;

	adsp->qdsp6ss_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adsp->qdsp6ss_base)) अणु
		dev_err(adsp->dev, "failed to map QDSP6SS registers\n");
		वापस PTR_ERR(adsp->qdsp6ss_base);
	पूर्ण

	syscon = of_parse_phandle(pdev->dev.of_node, "qcom,halt-regs", 0);
	अगर (!syscon) अणु
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		वापस -EINVAL;
	पूर्ण

	adsp->halt_map = syscon_node_to_regmap(syscon);
	of_node_put(syscon);
	अगर (IS_ERR(adsp->halt_map))
		वापस PTR_ERR(adsp->halt_map);

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "qcom,halt-regs",
			1, &adsp->halt_lpass);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no offset in syscon\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_alloc_memory_region(काष्ठा qcom_adsp *adsp)
अणु
	काष्ठा device_node *node;
	काष्ठा resource r;
	पूर्णांक ret;

	node = of_parse_phandle(adsp->dev->of_node, "memory-region", 0);
	अगर (!node) अणु
		dev_err(adsp->dev, "no memory-region specified\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(node, 0, &r);
	अगर (ret)
		वापस ret;

	adsp->mem_phys = adsp->mem_reloc = r.start;
	adsp->mem_size = resource_size(&r);
	adsp->mem_region = devm_ioremap_wc(adsp->dev,
				adsp->mem_phys, adsp->mem_size);
	अगर (!adsp->mem_region) अणु
		dev_err(adsp->dev, "unable to map memory region: %pa+%zx\n",
			&r.start, adsp->mem_size);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा adsp_pil_data *desc;
	काष्ठा qcom_adsp *adsp;
	काष्ठा rproc *rproc;
	पूर्णांक ret;

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	rproc = rproc_alloc(&pdev->dev, pdev->name, &adsp_ops,
			    desc->firmware_name, माप(*adsp));
	अगर (!rproc) अणु
		dev_err(&pdev->dev, "unable to allocate remoteproc\n");
		वापस -ENOMEM;
	पूर्ण
	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	adsp = (काष्ठा qcom_adsp *)rproc->priv;
	adsp->dev = &pdev->dev;
	adsp->rproc = rproc;
	adsp->info_name = desc->sysmon_name;
	platक्रमm_set_drvdata(pdev, adsp);

	ret = adsp_alloc_memory_region(adsp);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = adsp_init_घड़ी(adsp, desc->clk_ids);
	अगर (ret)
		जाओ मुक्त_rproc;

	pm_runसमय_enable(adsp->dev);

	ret = adsp_init_reset(adsp);
	अगर (ret)
		जाओ disable_pm;

	ret = adsp_init_mmio(adsp, pdev);
	अगर (ret)
		जाओ disable_pm;

	ret = qcom_q6v5_init(&adsp->q6v5, pdev, rproc, desc->crash_reason_smem,
			     qcom_adsp_pil_hanकरोver);
	अगर (ret)
		जाओ disable_pm;

	qcom_add_glink_subdev(rproc, &adsp->glink_subdev, desc->ssr_name);
	qcom_add_ssr_subdev(rproc, &adsp->ssr_subdev, desc->ssr_name);
	adsp->sysmon = qcom_add_sysmon_subdev(rproc,
					      desc->sysmon_name,
					      desc->ssctl_id);
	अगर (IS_ERR(adsp->sysmon)) अणु
		ret = PTR_ERR(adsp->sysmon);
		जाओ disable_pm;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ disable_pm;

	वापस 0;

disable_pm:
	pm_runसमय_disable(adsp->dev);
मुक्त_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक adsp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_adsp *adsp = platक्रमm_get_drvdata(pdev);

	rproc_del(adsp->rproc);

	qcom_हटाओ_glink_subdev(adsp->rproc, &adsp->glink_subdev);
	qcom_हटाओ_sysmon_subdev(adsp->sysmon);
	qcom_हटाओ_ssr_subdev(adsp->rproc, &adsp->ssr_subdev);
	pm_runसमय_disable(adsp->dev);
	rproc_मुक्त(adsp->rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adsp_pil_data adsp_resource_init = अणु
	.crash_reason_smem = 423,
	.firmware_name = "adsp.mdt",
	.ssr_name = "lpass",
	.sysmon_name = "adsp",
	.ssctl_id = 0x14,
	.clk_ids = (स्थिर अक्षर*[]) अणु
		"sway_cbcr", "lpass_ahbs_aon_cbcr", "lpass_ahbm_aon_cbcr",
		"qdsp6ss_xo", "qdsp6ss_sleep", "qdsp6ss_core", शून्य
	पूर्ण,
	.num_clks = 7,
पूर्ण;

अटल स्थिर काष्ठा adsp_pil_data cdsp_resource_init = अणु
	.crash_reason_smem = 601,
	.firmware_name = "cdsp.mdt",
	.ssr_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctl_id = 0x17,
	.clk_ids = (स्थिर अक्षर*[]) अणु
		"sway", "tbu", "bimc", "ahb_aon", "q6ss_slave", "q6ss_master",
		"q6_axim", शून्य
	पूर्ण,
	.num_clks = 7,
पूर्ण;

अटल स्थिर काष्ठा of_device_id adsp_of_match[] = अणु
	अणु .compatible = "qcom,qcs404-cdsp-pil", .data = &cdsp_resource_init पूर्ण,
	अणु .compatible = "qcom,sdm845-adsp-pil", .data = &adsp_resource_init पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adsp_of_match);

अटल काष्ठा platक्रमm_driver adsp_pil_driver = अणु
	.probe = adsp_probe,
	.हटाओ = adsp_हटाओ,
	.driver = अणु
		.name = "qcom_q6v5_adsp",
		.of_match_table = adsp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(adsp_pil_driver);
MODULE_DESCRIPTION("QTI SDM845 ADSP Peripheral Image Loader");
MODULE_LICENSE("GPL v2");
