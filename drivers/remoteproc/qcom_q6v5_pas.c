<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm ADSP/SLPI Peripheral Image Loader क्रम MSM8974 and MSM8996
 *
 * Copyright (C) 2016 Linaro Ltd
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
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

#समावेश "qcom_common.h"
#समावेश "qcom_pil_info.h"
#समावेश "qcom_q6v5.h"
#समावेश "remoteproc_internal.h"

काष्ठा adsp_data अणु
	पूर्णांक crash_reason_smem;
	स्थिर अक्षर *firmware_name;
	पूर्णांक pas_id;
	अचिन्हित पूर्णांक minidump_id;
	bool has_aggre2_clk;
	bool स्वतः_boot;

	अक्षर **active_pd_names;
	अक्षर **proxy_pd_names;

	स्थिर अक्षर *ssr_name;
	स्थिर अक्षर *sysmon_name;
	पूर्णांक ssctl_id;
पूर्ण;

काष्ठा qcom_adsp अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;

	काष्ठा qcom_q6v5 q6v5;

	काष्ठा clk *xo;
	काष्ठा clk *aggre2_clk;

	काष्ठा regulator *cx_supply;
	काष्ठा regulator *px_supply;

	काष्ठा device *active_pds[1];
	काष्ठा device *proxy_pds[3];

	पूर्णांक active_pd_count;
	पूर्णांक proxy_pd_count;

	पूर्णांक pas_id;
	अचिन्हित पूर्णांक minidump_id;
	पूर्णांक crash_reason_smem;
	bool has_aggre2_clk;
	स्थिर अक्षर *info_name;

	काष्ठा completion start_करोne;
	काष्ठा completion stop_करोne;

	phys_addr_t mem_phys;
	phys_addr_t mem_reloc;
	व्योम *mem_region;
	माप_प्रकार mem_size;

	काष्ठा qcom_rproc_glink glink_subdev;
	काष्ठा qcom_rproc_subdev smd_subdev;
	काष्ठा qcom_rproc_ssr ssr_subdev;
	काष्ठा qcom_sysmon *sysmon;
पूर्ण;

अटल व्योम adsp_minidump(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = rproc->priv;

	qcom_minidump(rproc, adsp->minidump_id);
पूर्ण

अटल पूर्णांक adsp_pds_enable(काष्ठा qcom_adsp *adsp, काष्ठा device **pds,
			   माप_प्रकार pd_count)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < pd_count; i++) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], पूर्णांक_उच्च);
		ret = pm_runसमय_get_sync(pds[i]);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(pds[i]);
			dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
			जाओ unroll_pd_votes;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_pd_votes:
	क्रम (i--; i >= 0; i--) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
		pm_runसमय_put(pds[i]);
	पूर्ण

	वापस ret;
पूर्ण;

अटल व्योम adsp_pds_disable(काष्ठा qcom_adsp *adsp, काष्ठा device **pds,
			     माप_प्रकार pd_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pd_count; i++) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
		pm_runसमय_put(pds[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक adsp_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक ret;

	ret = qcom_mdt_load(adsp->dev, fw, rproc->firmware, adsp->pas_id,
			    adsp->mem_region, adsp->mem_phys, adsp->mem_size,
			    &adsp->mem_reloc);
	अगर (ret)
		वापस ret;

	qcom_pil_info_store(adsp->info_name, adsp->mem_phys, adsp->mem_size);

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_start(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक ret;

	qcom_q6v5_prepare(&adsp->q6v5);

	ret = adsp_pds_enable(adsp, adsp->active_pds, adsp->active_pd_count);
	अगर (ret < 0)
		जाओ disable_irqs;

	ret = adsp_pds_enable(adsp, adsp->proxy_pds, adsp->proxy_pd_count);
	अगर (ret < 0)
		जाओ disable_active_pds;

	ret = clk_prepare_enable(adsp->xo);
	अगर (ret)
		जाओ disable_proxy_pds;

	ret = clk_prepare_enable(adsp->aggre2_clk);
	अगर (ret)
		जाओ disable_xo_clk;

	ret = regulator_enable(adsp->cx_supply);
	अगर (ret)
		जाओ disable_aggre2_clk;

	ret = regulator_enable(adsp->px_supply);
	अगर (ret)
		जाओ disable_cx_supply;

	ret = qcom_scm_pas_auth_and_reset(adsp->pas_id);
	अगर (ret) अणु
		dev_err(adsp->dev,
			"failed to authenticate image and release reset\n");
		जाओ disable_px_supply;
	पूर्ण

	ret = qcom_q6v5_रुको_क्रम_start(&adsp->q6v5, msecs_to_jअगरfies(5000));
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(adsp->dev, "start timed out\n");
		qcom_scm_pas_shutकरोwn(adsp->pas_id);
		जाओ disable_px_supply;
	पूर्ण

	वापस 0;

disable_px_supply:
	regulator_disable(adsp->px_supply);
disable_cx_supply:
	regulator_disable(adsp->cx_supply);
disable_aggre2_clk:
	clk_disable_unprepare(adsp->aggre2_clk);
disable_xo_clk:
	clk_disable_unprepare(adsp->xo);
disable_proxy_pds:
	adsp_pds_disable(adsp, adsp->proxy_pds, adsp->proxy_pd_count);
disable_active_pds:
	adsp_pds_disable(adsp, adsp->active_pds, adsp->active_pd_count);
disable_irqs:
	qcom_q6v5_unprepare(&adsp->q6v5);

	वापस ret;
पूर्ण

अटल व्योम qcom_pas_hanकरोver(काष्ठा qcom_q6v5 *q6v5)
अणु
	काष्ठा qcom_adsp *adsp = container_of(q6v5, काष्ठा qcom_adsp, q6v5);

	regulator_disable(adsp->px_supply);
	regulator_disable(adsp->cx_supply);
	clk_disable_unprepare(adsp->aggre2_clk);
	clk_disable_unprepare(adsp->xo);
	adsp_pds_disable(adsp, adsp->proxy_pds, adsp->proxy_pd_count);
पूर्ण

अटल पूर्णांक adsp_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;
	पूर्णांक hanकरोver;
	पूर्णांक ret;

	ret = qcom_q6v5_request_stop(&adsp->q6v5, adsp->sysmon);
	अगर (ret == -ETIMEDOUT)
		dev_err(adsp->dev, "timed out on wait\n");

	ret = qcom_scm_pas_shutकरोwn(adsp->pas_id);
	अगर (ret)
		dev_err(adsp->dev, "failed to shutdown: %d\n", ret);

	adsp_pds_disable(adsp, adsp->active_pds, adsp->active_pd_count);
	hanकरोver = qcom_q6v5_unprepare(&adsp->q6v5);
	अगर (hanकरोver)
		qcom_pas_hanकरोver(&adsp->q6v5);

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
	काष्ठा qcom_adsp *adsp = (काष्ठा qcom_adsp *)rproc->priv;

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

अटल स्थिर काष्ठा rproc_ops adsp_minidump_ops = अणु
	.start = adsp_start,
	.stop = adsp_stop,
	.da_to_va = adsp_da_to_va,
	.load = adsp_load,
	.panic = adsp_panic,
	.coredump = adsp_minidump,
पूर्ण;

अटल पूर्णांक adsp_init_घड़ी(काष्ठा qcom_adsp *adsp)
अणु
	पूर्णांक ret;

	adsp->xo = devm_clk_get(adsp->dev, "xo");
	अगर (IS_ERR(adsp->xo)) अणु
		ret = PTR_ERR(adsp->xo);
		अगर (ret != -EPROBE_DEFER)
			dev_err(adsp->dev, "failed to get xo clock");
		वापस ret;
	पूर्ण

	अगर (adsp->has_aggre2_clk) अणु
		adsp->aggre2_clk = devm_clk_get(adsp->dev, "aggre2");
		अगर (IS_ERR(adsp->aggre2_clk)) अणु
			ret = PTR_ERR(adsp->aggre2_clk);
			अगर (ret != -EPROBE_DEFER)
				dev_err(adsp->dev,
					"failed to get aggre2 clock");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_init_regulator(काष्ठा qcom_adsp *adsp)
अणु
	adsp->cx_supply = devm_regulator_get(adsp->dev, "cx");
	अगर (IS_ERR(adsp->cx_supply))
		वापस PTR_ERR(adsp->cx_supply);

	regulator_set_load(adsp->cx_supply, 100000);

	adsp->px_supply = devm_regulator_get(adsp->dev, "px");
	वापस PTR_ERR_OR_ZERO(adsp->px_supply);
पूर्ण

अटल पूर्णांक adsp_pds_attach(काष्ठा device *dev, काष्ठा device **devs,
			   अक्षर **pd_names)
अणु
	माप_प्रकार num_pds = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!pd_names)
		वापस 0;

	/* Handle single घातer करोमुख्य */
	अगर (dev->pm_करोमुख्य) अणु
		devs[0] = dev;
		pm_runसमय_enable(dev);
		वापस 1;
	पूर्ण

	जबतक (pd_names[num_pds])
		num_pds++;

	क्रम (i = 0; i < num_pds; i++) अणु
		devs[i] = dev_pm_करोमुख्य_attach_by_name(dev, pd_names[i]);
		अगर (IS_ERR_OR_शून्य(devs[i])) अणु
			ret = PTR_ERR(devs[i]) ? : -ENODATA;
			जाओ unroll_attach;
		पूर्ण
	पूर्ण

	वापस num_pds;

unroll_attach:
	क्रम (i--; i >= 0; i--)
		dev_pm_करोमुख्य_detach(devs[i], false);

	वापस ret;
पूर्ण;

अटल व्योम adsp_pds_detach(काष्ठा qcom_adsp *adsp, काष्ठा device **pds,
			    माप_प्रकार pd_count)
अणु
	काष्ठा device *dev = adsp->dev;
	पूर्णांक i;

	/* Handle single घातer करोमुख्य */
	अगर (dev->pm_करोमुख्य && pd_count) अणु
		pm_runसमय_disable(dev);
		वापस;
	पूर्ण

	क्रम (i = 0; i < pd_count; i++)
		dev_pm_करोमुख्य_detach(pds[i], false);
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
	adsp->mem_region = devm_ioremap_wc(adsp->dev, adsp->mem_phys, adsp->mem_size);
	अगर (!adsp->mem_region) अणु
		dev_err(adsp->dev, "unable to map memory region: %pa+%zx\n",
			&r.start, adsp->mem_size);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा adsp_data *desc;
	काष्ठा qcom_adsp *adsp;
	काष्ठा rproc *rproc;
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा rproc_ops *ops = &adsp_ops;
	पूर्णांक ret;

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	अगर (!qcom_scm_is_available())
		वापस -EPROBE_DEFER;

	fw_name = desc->firmware_name;
	ret = of_property_पढ़ो_string(pdev->dev.of_node, "firmware-name",
				      &fw_name);
	अगर (ret < 0 && ret != -EINVAL)
		वापस ret;

	अगर (desc->minidump_id)
		ops = &adsp_minidump_ops;

	rproc = rproc_alloc(&pdev->dev, pdev->name, ops, fw_name, माप(*adsp));

	अगर (!rproc) अणु
		dev_err(&pdev->dev, "unable to allocate remoteproc\n");
		वापस -ENOMEM;
	पूर्ण

	rproc->स्वतः_boot = desc->स्वतः_boot;
	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	adsp = (काष्ठा qcom_adsp *)rproc->priv;
	adsp->dev = &pdev->dev;
	adsp->rproc = rproc;
	adsp->minidump_id = desc->minidump_id;
	adsp->pas_id = desc->pas_id;
	adsp->has_aggre2_clk = desc->has_aggre2_clk;
	adsp->info_name = desc->sysmon_name;
	platक्रमm_set_drvdata(pdev, adsp);

	device_wakeup_enable(adsp->dev);

	ret = adsp_alloc_memory_region(adsp);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = adsp_init_घड़ी(adsp);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = adsp_init_regulator(adsp);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = adsp_pds_attach(&pdev->dev, adsp->active_pds,
			      desc->active_pd_names);
	अगर (ret < 0)
		जाओ मुक्त_rproc;
	adsp->active_pd_count = ret;

	ret = adsp_pds_attach(&pdev->dev, adsp->proxy_pds,
			      desc->proxy_pd_names);
	अगर (ret < 0)
		जाओ detach_active_pds;
	adsp->proxy_pd_count = ret;

	ret = qcom_q6v5_init(&adsp->q6v5, pdev, rproc, desc->crash_reason_smem,
			     qcom_pas_hanकरोver);
	अगर (ret)
		जाओ detach_proxy_pds;

	qcom_add_glink_subdev(rproc, &adsp->glink_subdev, desc->ssr_name);
	qcom_add_smd_subdev(rproc, &adsp->smd_subdev);
	qcom_add_ssr_subdev(rproc, &adsp->ssr_subdev, desc->ssr_name);
	adsp->sysmon = qcom_add_sysmon_subdev(rproc,
					      desc->sysmon_name,
					      desc->ssctl_id);
	अगर (IS_ERR(adsp->sysmon)) अणु
		ret = PTR_ERR(adsp->sysmon);
		जाओ detach_proxy_pds;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ detach_proxy_pds;

	वापस 0;

detach_proxy_pds:
	adsp_pds_detach(adsp, adsp->proxy_pds, adsp->proxy_pd_count);
detach_active_pds:
	adsp_pds_detach(adsp, adsp->active_pds, adsp->active_pd_count);
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
	qcom_हटाओ_smd_subdev(adsp->rproc, &adsp->smd_subdev);
	qcom_हटाओ_ssr_subdev(adsp->rproc, &adsp->ssr_subdev);
	rproc_मुक्त(adsp->rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adsp_data adsp_resource_init = अणु
		.crash_reason_smem = 423,
		.firmware_name = "adsp.mdt",
		.pas_id = 1,
		.has_aggre2_clk = false,
		.स्वतः_boot = true,
		.ssr_name = "lpass",
		.sysmon_name = "adsp",
		.ssctl_id = 0x14,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8150_adsp_resource = अणु
		.crash_reason_smem = 423,
		.firmware_name = "adsp.mdt",
		.pas_id = 1,
		.has_aggre2_clk = false,
		.स्वतः_boot = true,
		.active_pd_names = (अक्षर*[])अणु
			"load_state",
			शून्य
		पूर्ण,
		.proxy_pd_names = (अक्षर*[])अणु
			"cx",
			शून्य
		पूर्ण,
		.ssr_name = "lpass",
		.sysmon_name = "adsp",
		.ssctl_id = 0x14,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8250_adsp_resource = अणु
	.crash_reason_smem = 423,
	.firmware_name = "adsp.mdt",
	.pas_id = 1,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"lcx",
		"lmx",
		शून्य
	पूर्ण,
	.ssr_name = "lpass",
	.sysmon_name = "adsp",
	.ssctl_id = 0x14,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8350_adsp_resource = अणु
	.crash_reason_smem = 423,
	.firmware_name = "adsp.mdt",
	.pas_id = 1,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"lcx",
		"lmx",
		शून्य
	पूर्ण,
	.ssr_name = "lpass",
	.sysmon_name = "adsp",
	.ssctl_id = 0x14,
पूर्ण;

अटल स्थिर काष्ठा adsp_data msm8998_adsp_resource = अणु
		.crash_reason_smem = 423,
		.firmware_name = "adsp.mdt",
		.pas_id = 1,
		.has_aggre2_clk = false,
		.स्वतः_boot = true,
		.proxy_pd_names = (अक्षर*[])अणु
			"cx",
			शून्य
		पूर्ण,
		.ssr_name = "lpass",
		.sysmon_name = "adsp",
		.ssctl_id = 0x14,
पूर्ण;

अटल स्थिर काष्ठा adsp_data cdsp_resource_init = अणु
	.crash_reason_smem = 601,
	.firmware_name = "cdsp.mdt",
	.pas_id = 18,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.ssr_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctl_id = 0x17,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8150_cdsp_resource = अणु
	.crash_reason_smem = 601,
	.firmware_name = "cdsp.mdt",
	.pas_id = 18,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		शून्य
	पूर्ण,
	.ssr_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctl_id = 0x17,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8250_cdsp_resource = अणु
	.crash_reason_smem = 601,
	.firmware_name = "cdsp.mdt",
	.pas_id = 18,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		शून्य
	पूर्ण,
	.ssr_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctl_id = 0x17,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8350_cdsp_resource = अणु
	.crash_reason_smem = 601,
	.firmware_name = "cdsp.mdt",
	.pas_id = 18,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		शून्य
	पूर्ण,
	.ssr_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctl_id = 0x17,
पूर्ण;

अटल स्थिर काष्ठा adsp_data mpss_resource_init = अणु
	.crash_reason_smem = 421,
	.firmware_name = "modem.mdt",
	.pas_id = 4,
	.minidump_id = 3,
	.has_aggre2_clk = false,
	.स्वतः_boot = false,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		"mss",
		शून्य
	पूर्ण,
	.ssr_name = "mpss",
	.sysmon_name = "modem",
	.ssctl_id = 0x12,
पूर्ण;

अटल स्थिर काष्ठा adsp_data slpi_resource_init = अणु
		.crash_reason_smem = 424,
		.firmware_name = "slpi.mdt",
		.pas_id = 12,
		.has_aggre2_clk = true,
		.स्वतः_boot = true,
		.ssr_name = "dsps",
		.sysmon_name = "slpi",
		.ssctl_id = 0x16,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8150_slpi_resource = अणु
		.crash_reason_smem = 424,
		.firmware_name = "slpi.mdt",
		.pas_id = 12,
		.has_aggre2_clk = false,
		.स्वतः_boot = true,
		.active_pd_names = (अक्षर*[])अणु
			"load_state",
			शून्य
		पूर्ण,
		.proxy_pd_names = (अक्षर*[])अणु
			"lcx",
			"lmx",
			शून्य
		पूर्ण,
		.ssr_name = "dsps",
		.sysmon_name = "slpi",
		.ssctl_id = 0x16,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8250_slpi_resource = अणु
	.crash_reason_smem = 424,
	.firmware_name = "slpi.mdt",
	.pas_id = 12,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"lcx",
		"lmx",
		शून्य
	पूर्ण,
	.ssr_name = "dsps",
	.sysmon_name = "slpi",
	.ssctl_id = 0x16,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sm8350_slpi_resource = अणु
	.crash_reason_smem = 424,
	.firmware_name = "slpi.mdt",
	.pas_id = 12,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"lcx",
		"lmx",
		शून्य
	पूर्ण,
	.ssr_name = "dsps",
	.sysmon_name = "slpi",
	.ssctl_id = 0x16,
पूर्ण;

अटल स्थिर काष्ठा adsp_data msm8998_slpi_resource = अणु
		.crash_reason_smem = 424,
		.firmware_name = "slpi.mdt",
		.pas_id = 12,
		.has_aggre2_clk = true,
		.स्वतः_boot = true,
		.proxy_pd_names = (अक्षर*[])अणु
			"ssc_cx",
			शून्य
		पूर्ण,
		.ssr_name = "dsps",
		.sysmon_name = "slpi",
		.ssctl_id = 0x16,
पूर्ण;

अटल स्थिर काष्ठा adsp_data wcss_resource_init = अणु
	.crash_reason_smem = 421,
	.firmware_name = "wcnss.mdt",
	.pas_id = 6,
	.स्वतः_boot = true,
	.ssr_name = "mpss",
	.sysmon_name = "wcnss",
	.ssctl_id = 0x12,
पूर्ण;

अटल स्थिर काष्ठा adsp_data sdx55_mpss_resource = अणु
	.crash_reason_smem = 421,
	.firmware_name = "modem.mdt",
	.pas_id = 4,
	.has_aggre2_clk = false,
	.स्वतः_boot = true,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		"mss",
		शून्य
	पूर्ण,
	.ssr_name = "mpss",
	.sysmon_name = "modem",
	.ssctl_id = 0x22,
पूर्ण;

अटल स्थिर काष्ठा of_device_id adsp_of_match[] = अणु
	अणु .compatible = "qcom,msm8974-adsp-pil", .data = &adsp_resource_initपूर्ण,
	अणु .compatible = "qcom,msm8996-adsp-pil", .data = &adsp_resource_initपूर्ण,
	अणु .compatible = "qcom,msm8996-slpi-pil", .data = &slpi_resource_initपूर्ण,
	अणु .compatible = "qcom,msm8998-adsp-pas", .data = &msm8998_adsp_resourceपूर्ण,
	अणु .compatible = "qcom,msm8998-slpi-pas", .data = &msm8998_slpi_resourceपूर्ण,
	अणु .compatible = "qcom,qcs404-adsp-pas", .data = &adsp_resource_init पूर्ण,
	अणु .compatible = "qcom,qcs404-cdsp-pas", .data = &cdsp_resource_init पूर्ण,
	अणु .compatible = "qcom,qcs404-wcss-pas", .data = &wcss_resource_init पूर्ण,
	अणु .compatible = "qcom,sc7180-mpss-pas", .data = &mpss_resource_initपूर्ण,
	अणु .compatible = "qcom,sdm845-adsp-pas", .data = &adsp_resource_initपूर्ण,
	अणु .compatible = "qcom,sdm845-cdsp-pas", .data = &cdsp_resource_initपूर्ण,
	अणु .compatible = "qcom,sdx55-mpss-pas", .data = &sdx55_mpss_resourceपूर्ण,
	अणु .compatible = "qcom,sm8150-adsp-pas", .data = &sm8150_adsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8150-cdsp-pas", .data = &sm8150_cdsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8150-mpss-pas", .data = &mpss_resource_initपूर्ण,
	अणु .compatible = "qcom,sm8150-slpi-pas", .data = &sm8150_slpi_resourceपूर्ण,
	अणु .compatible = "qcom,sm8250-adsp-pas", .data = &sm8250_adsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8250-cdsp-pas", .data = &sm8250_cdsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8250-slpi-pas", .data = &sm8250_slpi_resourceपूर्ण,
	अणु .compatible = "qcom,sm8350-adsp-pas", .data = &sm8350_adsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8350-cdsp-pas", .data = &sm8350_cdsp_resourceपूर्ण,
	अणु .compatible = "qcom,sm8350-slpi-pas", .data = &sm8350_slpi_resourceपूर्ण,
	अणु .compatible = "qcom,sm8350-mpss-pas", .data = &mpss_resource_initपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adsp_of_match);

अटल काष्ठा platक्रमm_driver adsp_driver = अणु
	.probe = adsp_probe,
	.हटाओ = adsp_हटाओ,
	.driver = अणु
		.name = "qcom_q6v5_pas",
		.of_match_table = adsp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(adsp_driver);
MODULE_DESCRIPTION("Qualcomm Hexagon v5 Peripheral Authentication Service driver");
MODULE_LICENSE("GPL v2");
