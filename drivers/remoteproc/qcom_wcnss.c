<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Wireless Connectivity Subप्रणाली Peripheral Image Loader
 *
 * Copyright (C) 2016 Linaro Ltd
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>
#समावेश <linux/rpmsg/qcom_smd.h>

#समावेश "qcom_common.h"
#समावेश "remoteproc_internal.h"
#समावेश "qcom_pil_info.h"
#समावेश "qcom_wcnss.h"

#घोषणा WCNSS_CRASH_REASON_SMEM		422
#घोषणा WCNSS_FIRMWARE_NAME		"wcnss.mdt"
#घोषणा WCNSS_PAS_ID			6
#घोषणा WCNSS_SSCTL_ID			0x13

#घोषणा WCNSS_SPARE_NVBIN_DLND		BIT(25)

#घोषणा WCNSS_PMU_IRIS_XO_CFG		BIT(3)
#घोषणा WCNSS_PMU_IRIS_XO_EN		BIT(4)
#घोषणा WCNSS_PMU_GC_BUS_MUX_SEL_TOP	BIT(5)
#घोषणा WCNSS_PMU_IRIS_XO_CFG_STS	BIT(6) /* 1: in progress, 0: करोne */

#घोषणा WCNSS_PMU_IRIS_RESET		BIT(7)
#घोषणा WCNSS_PMU_IRIS_RESET_STS	BIT(8) /* 1: in progress, 0: करोne */
#घोषणा WCNSS_PMU_IRIS_XO_READ		BIT(9)
#घोषणा WCNSS_PMU_IRIS_XO_READ_STS	BIT(10)

#घोषणा WCNSS_PMU_XO_MODE_MASK		GENMASK(2, 1)
#घोषणा WCNSS_PMU_XO_MODE_19p2		0
#घोषणा WCNSS_PMU_XO_MODE_48		3

#घोषणा WCNSS_MAX_PDS			2

काष्ठा wcnss_data अणु
	माप_प्रकार pmu_offset;
	माप_प्रकार spare_offset;

	स्थिर अक्षर *pd_names[WCNSS_MAX_PDS];
	स्थिर काष्ठा wcnss_vreg_info *vregs;
	माप_प्रकार num_vregs, num_pd_vregs;
पूर्ण;

काष्ठा qcom_wcnss अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;

	व्योम __iomem *pmu_cfg;
	व्योम __iomem *spare_out;

	bool use_48mhz_xo;

	पूर्णांक wकरोg_irq;
	पूर्णांक fatal_irq;
	पूर्णांक पढ़ोy_irq;
	पूर्णांक hanकरोver_irq;
	पूर्णांक stop_ack_irq;

	काष्ठा qcom_smem_state *state;
	अचिन्हित stop_bit;

	काष्ठा mutex iris_lock;
	काष्ठा qcom_iris *iris;

	काष्ठा device *pds[WCNSS_MAX_PDS];
	माप_प्रकार num_pds;
	काष्ठा regulator_bulk_data *vregs;
	माप_प्रकार num_vregs;

	काष्ठा completion start_करोne;
	काष्ठा completion stop_करोne;

	phys_addr_t mem_phys;
	phys_addr_t mem_reloc;
	व्योम *mem_region;
	माप_प्रकार mem_size;

	काष्ठा qcom_rproc_subdev smd_subdev;
	काष्ठा qcom_sysmon *sysmon;
पूर्ण;

अटल स्थिर काष्ठा wcnss_data riva_data = अणु
	.pmu_offset = 0x28,
	.spare_offset = 0xb4,

	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddmx",  1050000, 1150000, 0 पूर्ण,
		अणु "vddcx",  1050000, 1150000, 0 पूर्ण,
		अणु "vddpx",  1800000, 1800000, 0 पूर्ण,
	पूर्ण,
	.num_vregs = 3,
पूर्ण;

अटल स्थिर काष्ठा wcnss_data pronto_v1_data = अणु
	.pmu_offset = 0x1004,
	.spare_offset = 0x1088,

	.pd_names = अणु "mx", "cx" पूर्ण,
	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddmx", 950000, 1150000, 0 पूर्ण,
		अणु "vddcx", .super_turbo = trueपूर्ण,
		अणु "vddpx", 1800000, 1800000, 0 पूर्ण,
	पूर्ण,
	.num_pd_vregs = 2,
	.num_vregs = 1,
पूर्ण;

अटल स्थिर काष्ठा wcnss_data pronto_v2_data = अणु
	.pmu_offset = 0x1004,
	.spare_offset = 0x1088,

	.pd_names = अणु "mx", "cx" पूर्ण,
	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddmx", 1287500, 1287500, 0 पूर्ण,
		अणु "vddcx", .super_turbo = true पूर्ण,
		अणु "vddpx", 1800000, 1800000, 0 पूर्ण,
	पूर्ण,
	.num_pd_vregs = 2,
	.num_vregs = 1,
पूर्ण;

व्योम qcom_wcnss_assign_iris(काष्ठा qcom_wcnss *wcnss,
			    काष्ठा qcom_iris *iris,
			    bool use_48mhz_xo)
अणु
	mutex_lock(&wcnss->iris_lock);

	wcnss->iris = iris;
	wcnss->use_48mhz_xo = use_48mhz_xo;

	mutex_unlock(&wcnss->iris_lock);
पूर्ण

अटल पूर्णांक wcnss_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा qcom_wcnss *wcnss = (काष्ठा qcom_wcnss *)rproc->priv;
	पूर्णांक ret;

	ret = qcom_mdt_load(wcnss->dev, fw, rproc->firmware, WCNSS_PAS_ID,
			    wcnss->mem_region, wcnss->mem_phys,
			    wcnss->mem_size, &wcnss->mem_reloc);
	अगर (ret)
		वापस ret;

	qcom_pil_info_store("wcnss", wcnss->mem_phys, wcnss->mem_size);

	वापस 0;
पूर्ण

अटल व्योम wcnss_indicate_nv_करोwnload(काष्ठा qcom_wcnss *wcnss)
अणु
	u32 val;

	/* Indicate NV करोwnload capability */
	val = पढ़ोl(wcnss->spare_out);
	val |= WCNSS_SPARE_NVBIN_DLND;
	ग_लिखोl(val, wcnss->spare_out);
पूर्ण

अटल व्योम wcnss_configure_iris(काष्ठा qcom_wcnss *wcnss)
अणु
	u32 val;

	/* Clear PMU cfg रेजिस्टर */
	ग_लिखोl(0, wcnss->pmu_cfg);

	val = WCNSS_PMU_GC_BUS_MUX_SEL_TOP | WCNSS_PMU_IRIS_XO_EN;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Clear XO_MODE */
	val &= ~WCNSS_PMU_XO_MODE_MASK;
	अगर (wcnss->use_48mhz_xo)
		val |= WCNSS_PMU_XO_MODE_48 << 1;
	अन्यथा
		val |= WCNSS_PMU_XO_MODE_19p2 << 1;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Reset IRIS */
	val |= WCNSS_PMU_IRIS_RESET;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Wait क्रम PMU.iris_reg_reset_sts */
	जबतक (पढ़ोl(wcnss->pmu_cfg) & WCNSS_PMU_IRIS_RESET_STS)
		cpu_relax();

	/* Clear IRIS reset */
	val &= ~WCNSS_PMU_IRIS_RESET;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Start IRIS XO configuration */
	val |= WCNSS_PMU_IRIS_XO_CFG;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Wait क्रम XO configuration to finish */
	जबतक (पढ़ोl(wcnss->pmu_cfg) & WCNSS_PMU_IRIS_XO_CFG_STS)
		cpu_relax();

	/* Stop IRIS XO configuration */
	val &= ~WCNSS_PMU_GC_BUS_MUX_SEL_TOP;
	val &= ~WCNSS_PMU_IRIS_XO_CFG;
	ग_लिखोl(val, wcnss->pmu_cfg);

	/* Add some delay क्रम XO to settle */
	msleep(20);
पूर्ण

अटल पूर्णांक wcnss_start(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_wcnss *wcnss = (काष्ठा qcom_wcnss *)rproc->priv;
	पूर्णांक ret, i;

	mutex_lock(&wcnss->iris_lock);
	अगर (!wcnss->iris) अणु
		dev_err(wcnss->dev, "no iris registered\n");
		ret = -EINVAL;
		जाओ release_iris_lock;
	पूर्ण

	क्रम (i = 0; i < wcnss->num_pds; i++) अणु
		dev_pm_genpd_set_perक्रमmance_state(wcnss->pds[i], पूर्णांक_उच्च);
		ret = pm_runसमय_get_sync(wcnss->pds[i]);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(wcnss->pds[i]);
			जाओ disable_pds;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(wcnss->num_vregs, wcnss->vregs);
	अगर (ret)
		जाओ disable_pds;

	ret = qcom_iris_enable(wcnss->iris);
	अगर (ret)
		जाओ disable_regulators;

	wcnss_indicate_nv_करोwnload(wcnss);
	wcnss_configure_iris(wcnss);

	ret = qcom_scm_pas_auth_and_reset(WCNSS_PAS_ID);
	अगर (ret) अणु
		dev_err(wcnss->dev,
			"failed to authenticate image and release reset\n");
		जाओ disable_iris;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&wcnss->start_करोne,
					  msecs_to_jअगरfies(5000));
	अगर (wcnss->पढ़ोy_irq > 0 && ret == 0) अणु
		/* We have a पढ़ोy_irq, but it didn't fire in समय. */
		dev_err(wcnss->dev, "start timed out\n");
		qcom_scm_pas_shutकरोwn(WCNSS_PAS_ID);
		ret = -ETIMEDOUT;
		जाओ disable_iris;
	पूर्ण

	ret = 0;

disable_iris:
	qcom_iris_disable(wcnss->iris);
disable_regulators:
	regulator_bulk_disable(wcnss->num_vregs, wcnss->vregs);
disable_pds:
	क्रम (i--; i >= 0; i--) अणु
		pm_runसमय_put(wcnss->pds[i]);
		dev_pm_genpd_set_perक्रमmance_state(wcnss->pds[i], 0);
	पूर्ण
release_iris_lock:
	mutex_unlock(&wcnss->iris_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wcnss_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_wcnss *wcnss = (काष्ठा qcom_wcnss *)rproc->priv;
	पूर्णांक ret;

	अगर (wcnss->state) अणु
		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    BIT(wcnss->stop_bit));

		ret = रुको_क्रम_completion_समयout(&wcnss->stop_करोne,
						  msecs_to_jअगरfies(5000));
		अगर (ret == 0)
			dev_err(wcnss->dev, "timed out on wait\n");

		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    0);
	पूर्ण

	ret = qcom_scm_pas_shutकरोwn(WCNSS_PAS_ID);
	अगर (ret)
		dev_err(wcnss->dev, "failed to shutdown: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम *wcnss_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा qcom_wcnss *wcnss = (काष्ठा qcom_wcnss *)rproc->priv;
	पूर्णांक offset;

	offset = da - wcnss->mem_reloc;
	अगर (offset < 0 || offset + len > wcnss->mem_size)
		वापस शून्य;

	वापस wcnss->mem_region + offset;
पूर्ण

अटल स्थिर काष्ठा rproc_ops wcnss_ops = अणु
	.start = wcnss_start,
	.stop = wcnss_stop,
	.da_to_va = wcnss_da_to_va,
	.parse_fw = qcom_रेजिस्टर_dump_segments,
	.load = wcnss_load,
पूर्ण;

अटल irqवापस_t wcnss_wकरोg_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_wcnss *wcnss = dev;

	rproc_report_crash(wcnss->rproc, RPROC_WATCHDOG);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wcnss_fatal_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_wcnss *wcnss = dev;
	माप_प्रकार len;
	अक्षर *msg;

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, WCNSS_CRASH_REASON_SMEM, &len);
	अगर (!IS_ERR(msg) && len > 0 && msg[0])
		dev_err(wcnss->dev, "fatal error received: %s\n", msg);

	rproc_report_crash(wcnss->rproc, RPROC_FATAL_ERROR);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wcnss_पढ़ोy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_wcnss *wcnss = dev;

	complete(&wcnss->start_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wcnss_hanकरोver_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	/*
	 * XXX: At this poपूर्णांक we're supposed to release the resources that we
	 * have been holding on behalf of the WCNSS. Unक्रमtunately this
	 * पूर्णांकerrupt comes way beक्रमe the other side seems to be करोne.
	 *
	 * So we're currently relying on the पढ़ोy पूर्णांकerrupt firing later then
	 * this and we just disable the resources at the end of wcnss_start().
	 */

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wcnss_stop_ack_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_wcnss *wcnss = dev;

	complete(&wcnss->stop_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wcnss_init_pds(काष्ठा qcom_wcnss *wcnss,
			  स्थिर अक्षर * स्थिर pd_names[WCNSS_MAX_PDS])
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < WCNSS_MAX_PDS; i++) अणु
		अगर (!pd_names[i])
			अवरोध;

		wcnss->pds[i] = dev_pm_करोमुख्य_attach_by_name(wcnss->dev, pd_names[i]);
		अगर (IS_ERR_OR_शून्य(wcnss->pds[i])) अणु
			ret = PTR_ERR(wcnss->pds[i]) ? : -ENODATA;
			क्रम (i--; i >= 0; i--)
				dev_pm_करोमुख्य_detach(wcnss->pds[i], false);
			वापस ret;
		पूर्ण
	पूर्ण
	wcnss->num_pds = i;

	वापस 0;
पूर्ण

अटल व्योम wcnss_release_pds(काष्ठा qcom_wcnss *wcnss)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wcnss->num_pds; i++)
		dev_pm_करोमुख्य_detach(wcnss->pds[i], false);
पूर्ण

अटल पूर्णांक wcnss_init_regulators(काष्ठा qcom_wcnss *wcnss,
				 स्थिर काष्ठा wcnss_vreg_info *info,
				 पूर्णांक num_vregs, पूर्णांक num_pd_vregs)
अणु
	काष्ठा regulator_bulk_data *bulk;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * If attaching the घातer करोमुख्यs suceeded we can skip requesting
	 * the regulators क्रम the घातer करोमुख्यs. For old device trees we need to
	 * reserve extra space to manage them through the regulator पूर्णांकerface.
	 */
	अगर (wcnss->num_pds)
		info += num_pd_vregs;
	अन्यथा
		num_vregs += num_pd_vregs;

	bulk = devm_kसुस्मृति(wcnss->dev,
			    num_vregs, माप(काष्ठा regulator_bulk_data),
			    GFP_KERNEL);
	अगर (!bulk)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_vregs; i++)
		bulk[i].supply = info[i].name;

	ret = devm_regulator_bulk_get(wcnss->dev, num_vregs, bulk);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_vregs; i++) अणु
		अगर (info[i].max_voltage)
			regulator_set_voltage(bulk[i].consumer,
					      info[i].min_voltage,
					      info[i].max_voltage);

		अगर (info[i].load_uA)
			regulator_set_load(bulk[i].consumer, info[i].load_uA);
	पूर्ण

	wcnss->vregs = bulk;
	wcnss->num_vregs = num_vregs;

	वापस 0;
पूर्ण

अटल पूर्णांक wcnss_request_irq(काष्ठा qcom_wcnss *wcnss,
			     काष्ठा platक्रमm_device *pdev,
			     स्थिर अक्षर *name,
			     bool optional,
			     irq_handler_t thपढ़ो_fn)
अणु
	पूर्णांक ret;

	ret = platक्रमm_get_irq_byname(pdev, name);
	अगर (ret < 0 && optional) अणु
		dev_dbg(&pdev->dev, "no %s IRQ defined, ignoring\n", name);
		वापस 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no %s IRQ defined\n", name);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, ret,
					शून्य, thपढ़ो_fn,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"wcnss", wcnss);
	अगर (ret)
		dev_err(&pdev->dev, "request %s IRQ failed\n", name);

	वापस ret;
पूर्ण

अटल पूर्णांक wcnss_alloc_memory_region(काष्ठा qcom_wcnss *wcnss)
अणु
	काष्ठा device_node *node;
	काष्ठा resource r;
	पूर्णांक ret;

	node = of_parse_phandle(wcnss->dev->of_node, "memory-region", 0);
	अगर (!node) अणु
		dev_err(wcnss->dev, "no memory-region specified\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(node, 0, &r);
	अगर (ret)
		वापस ret;

	wcnss->mem_phys = wcnss->mem_reloc = r.start;
	wcnss->mem_size = resource_size(&r);
	wcnss->mem_region = devm_ioremap_wc(wcnss->dev, wcnss->mem_phys, wcnss->mem_size);
	अगर (!wcnss->mem_region) अणु
		dev_err(wcnss->dev, "unable to map memory region: %pa+%zx\n",
			&r.start, wcnss->mem_size);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcnss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *fw_name = WCNSS_FIRMWARE_NAME;
	स्थिर काष्ठा wcnss_data *data;
	काष्ठा qcom_wcnss *wcnss;
	काष्ठा resource *res;
	काष्ठा rproc *rproc;
	व्योम __iomem *mmio;
	पूर्णांक ret;

	data = of_device_get_match_data(&pdev->dev);

	अगर (!qcom_scm_is_available())
		वापस -EPROBE_DEFER;

	अगर (!qcom_scm_pas_supported(WCNSS_PAS_ID)) अणु
		dev_err(&pdev->dev, "PAS is not available for WCNSS\n");
		वापस -ENXIO;
	पूर्ण

	ret = of_property_पढ़ो_string(pdev->dev.of_node, "firmware-name",
				      &fw_name);
	अगर (ret < 0 && ret != -EINVAL)
		वापस ret;

	rproc = rproc_alloc(&pdev->dev, pdev->name, &wcnss_ops,
			    fw_name, माप(*wcnss));
	अगर (!rproc) अणु
		dev_err(&pdev->dev, "unable to allocate remoteproc\n");
		वापस -ENOMEM;
	पूर्ण
	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	wcnss = (काष्ठा qcom_wcnss *)rproc->priv;
	wcnss->dev = &pdev->dev;
	wcnss->rproc = rproc;
	platक्रमm_set_drvdata(pdev, wcnss);

	init_completion(&wcnss->start_करोne);
	init_completion(&wcnss->stop_करोne);

	mutex_init(&wcnss->iris_lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pmu");
	mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mmio)) अणु
		ret = PTR_ERR(mmio);
		जाओ मुक्त_rproc;
	पूर्ण

	ret = wcnss_alloc_memory_region(wcnss);
	अगर (ret)
		जाओ मुक्त_rproc;

	wcnss->pmu_cfg = mmio + data->pmu_offset;
	wcnss->spare_out = mmio + data->spare_offset;

	/*
	 * We might need to fallback to regulators instead of घातer करोमुख्यs
	 * क्रम old device trees. Don't report an error in that हाल.
	 */
	ret = wcnss_init_pds(wcnss, data->pd_names);
	अगर (ret && (ret != -ENODATA || !data->num_pd_vregs))
		जाओ मुक्त_rproc;

	ret = wcnss_init_regulators(wcnss, data->vregs, data->num_vregs,
				    data->num_pd_vregs);
	अगर (ret)
		जाओ detach_pds;

	ret = wcnss_request_irq(wcnss, pdev, "wdog", false, wcnss_wकरोg_पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ detach_pds;
	wcnss->wकरोg_irq = ret;

	ret = wcnss_request_irq(wcnss, pdev, "fatal", false, wcnss_fatal_पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ detach_pds;
	wcnss->fatal_irq = ret;

	ret = wcnss_request_irq(wcnss, pdev, "ready", true, wcnss_पढ़ोy_पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ detach_pds;
	wcnss->पढ़ोy_irq = ret;

	ret = wcnss_request_irq(wcnss, pdev, "handover", true, wcnss_hanकरोver_पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ detach_pds;
	wcnss->hanकरोver_irq = ret;

	ret = wcnss_request_irq(wcnss, pdev, "stop-ack", true, wcnss_stop_ack_पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ detach_pds;
	wcnss->stop_ack_irq = ret;

	अगर (wcnss->stop_ack_irq) अणु
		wcnss->state = qcom_smem_state_get(&pdev->dev, "stop",
						   &wcnss->stop_bit);
		अगर (IS_ERR(wcnss->state)) अणु
			ret = PTR_ERR(wcnss->state);
			जाओ detach_pds;
		पूर्ण
	पूर्ण

	qcom_add_smd_subdev(rproc, &wcnss->smd_subdev);
	wcnss->sysmon = qcom_add_sysmon_subdev(rproc, "wcnss", WCNSS_SSCTL_ID);
	अगर (IS_ERR(wcnss->sysmon)) अणु
		ret = PTR_ERR(wcnss->sysmon);
		जाओ detach_pds;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ detach_pds;

	वापस of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);

detach_pds:
	wcnss_release_pds(wcnss);
मुक्त_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक wcnss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_wcnss *wcnss = platक्रमm_get_drvdata(pdev);

	of_platक्रमm_depopulate(&pdev->dev);

	qcom_smem_state_put(wcnss->state);
	rproc_del(wcnss->rproc);

	qcom_हटाओ_sysmon_subdev(wcnss->sysmon);
	qcom_हटाओ_smd_subdev(wcnss->rproc, &wcnss->smd_subdev);
	wcnss_release_pds(wcnss);
	rproc_मुक्त(wcnss->rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wcnss_of_match[] = अणु
	अणु .compatible = "qcom,riva-pil", &riva_data पूर्ण,
	अणु .compatible = "qcom,pronto-v1-pil", &pronto_v1_data पूर्ण,
	अणु .compatible = "qcom,pronto-v2-pil", &pronto_v2_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wcnss_of_match);

अटल काष्ठा platक्रमm_driver wcnss_driver = अणु
	.probe = wcnss_probe,
	.हटाओ = wcnss_हटाओ,
	.driver = अणु
		.name = "qcom-wcnss-pil",
		.of_match_table = wcnss_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wcnss_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&wcnss_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&qcom_iris_driver);
	अगर (ret)
		platक्रमm_driver_unरेजिस्टर(&wcnss_driver);

	वापस ret;
पूर्ण
module_init(wcnss_init);

अटल व्योम __निकास wcnss_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_iris_driver);
	platक्रमm_driver_unरेजिस्टर(&wcnss_driver);
पूर्ण
module_निकास(wcnss_निकास);

MODULE_DESCRIPTION("Qualcomm Peripheral Image Loader for Wireless Subsystem");
MODULE_LICENSE("GPL v2");
