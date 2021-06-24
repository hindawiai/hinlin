<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010,2015,2019 The Linux Foundation. All rights reserved.
 * Copyright (C) 2015 Linaro Ltd.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/arm-smccc.h>

#समावेश "qcom_scm.h"

अटल bool करोwnload_mode = IS_ENABLED(CONFIG_QCOM_SCM_DOWNLOAD_MODE_DEFAULT);
module_param(करोwnload_mode, bool, 0);

#घोषणा SCM_HAS_CORE_CLK	BIT(0)
#घोषणा SCM_HAS_IFACE_CLK	BIT(1)
#घोषणा SCM_HAS_BUS_CLK		BIT(2)

काष्ठा qcom_scm अणु
	काष्ठा device *dev;
	काष्ठा clk *core_clk;
	काष्ठा clk *अगरace_clk;
	काष्ठा clk *bus_clk;
	काष्ठा reset_controller_dev reset;

	u64 dload_mode_addr;
पूर्ण;

काष्ठा qcom_scm_current_perm_info अणु
	__le32 vmid;
	__le32 perm;
	__le64 ctx;
	__le32 ctx_size;
	__le32 unused;
पूर्ण;

काष्ठा qcom_scm_mem_map_info अणु
	__le64 mem_addr;
	__le64 mem_size;
पूर्ण;

#घोषणा QCOM_SCM_FLAG_COLDBOOT_CPU0	0x00
#घोषणा QCOM_SCM_FLAG_COLDBOOT_CPU1	0x01
#घोषणा QCOM_SCM_FLAG_COLDBOOT_CPU2	0x08
#घोषणा QCOM_SCM_FLAG_COLDBOOT_CPU3	0x20

#घोषणा QCOM_SCM_FLAG_WARMBOOT_CPU0	0x04
#घोषणा QCOM_SCM_FLAG_WARMBOOT_CPU1	0x02
#घोषणा QCOM_SCM_FLAG_WARMBOOT_CPU2	0x10
#घोषणा QCOM_SCM_FLAG_WARMBOOT_CPU3	0x40

काष्ठा qcom_scm_wb_entry अणु
	पूर्णांक flag;
	व्योम *entry;
पूर्ण;

अटल काष्ठा qcom_scm_wb_entry qcom_scm_wb[] = अणु
	अणु .flag = QCOM_SCM_FLAG_WARMBOOT_CPU0 पूर्ण,
	अणु .flag = QCOM_SCM_FLAG_WARMBOOT_CPU1 पूर्ण,
	अणु .flag = QCOM_SCM_FLAG_WARMBOOT_CPU2 पूर्ण,
	अणु .flag = QCOM_SCM_FLAG_WARMBOOT_CPU3 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *qcom_scm_convention_names[] = अणु
	[SMC_CONVENTION_UNKNOWN] = "unknown",
	[SMC_CONVENTION_ARM_32] = "smc arm 32",
	[SMC_CONVENTION_ARM_64] = "smc arm 64",
	[SMC_CONVENTION_LEGACY] = "smc legacy",
पूर्ण;

अटल काष्ठा qcom_scm *__scm;

अटल पूर्णांक qcom_scm_clk_enable(व्योम)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(__scm->core_clk);
	अगर (ret)
		जाओ bail;

	ret = clk_prepare_enable(__scm->अगरace_clk);
	अगर (ret)
		जाओ disable_core;

	ret = clk_prepare_enable(__scm->bus_clk);
	अगर (ret)
		जाओ disable_अगरace;

	वापस 0;

disable_अगरace:
	clk_disable_unprepare(__scm->अगरace_clk);
disable_core:
	clk_disable_unprepare(__scm->core_clk);
bail:
	वापस ret;
पूर्ण

अटल व्योम qcom_scm_clk_disable(व्योम)
अणु
	clk_disable_unprepare(__scm->core_clk);
	clk_disable_unprepare(__scm->अगरace_clk);
	clk_disable_unprepare(__scm->bus_clk);
पूर्ण

क्रमागत qcom_scm_convention qcom_scm_convention = SMC_CONVENTION_UNKNOWN;
अटल DEFINE_SPINLOCK(scm_query_lock);

अटल क्रमागत qcom_scm_convention __get_convention(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_INFO,
		.cmd = QCOM_SCM_INFO_IS_CALL_AVAIL,
		.args[0] = SCM_SMC_FNID(QCOM_SCM_SVC_INFO,
					   QCOM_SCM_INFO_IS_CALL_AVAIL) |
			   (ARM_SMCCC_OWNER_SIP << ARM_SMCCC_OWNER_SHIFT),
		.arginfo = QCOM_SCM_ARGS(1),
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	क्रमागत qcom_scm_convention probed_convention;
	पूर्णांक ret;
	bool क्रमced = false;

	अगर (likely(qcom_scm_convention != SMC_CONVENTION_UNKNOWN))
		वापस qcom_scm_convention;

	/*
	 * Device isn't required as there is only one argument - no device
	 * needed to dma_map_single to secure world
	 */
	probed_convention = SMC_CONVENTION_ARM_64;
	ret = __scm_smc_call(शून्य, &desc, probed_convention, &res, true);
	अगर (!ret && res.result[0] == 1)
		जाओ found;

	/*
	 * Some SC7180 firmwares didn't implement the
	 * QCOM_SCM_INFO_IS_CALL_AVAIL call, so we fallback to क्रमcing ARM_64
	 * calling conventions on these firmwares. Luckily we करोn't make any
	 * early calls पूर्णांकo the firmware on these SoCs so the device poपूर्णांकer
	 * will be valid here to check अगर the compatible matches.
	 */
	अगर (of_device_is_compatible(__scm ? __scm->dev->of_node : शून्य, "qcom,scm-sc7180")) अणु
		क्रमced = true;
		जाओ found;
	पूर्ण

	probed_convention = SMC_CONVENTION_ARM_32;
	ret = __scm_smc_call(शून्य, &desc, probed_convention, &res, true);
	अगर (!ret && res.result[0] == 1)
		जाओ found;

	probed_convention = SMC_CONVENTION_LEGACY;
found:
	spin_lock_irqsave(&scm_query_lock, flags);
	अगर (probed_convention != qcom_scm_convention) अणु
		qcom_scm_convention = probed_convention;
		pr_info("qcom_scm: convention: %s%s\n",
			qcom_scm_convention_names[qcom_scm_convention],
			क्रमced ? " (forced)" : "");
	पूर्ण
	spin_unlock_irqrestore(&scm_query_lock, flags);

	वापस qcom_scm_convention;
पूर्ण

/**
 * qcom_scm_call() - Invoke a syscall in the secure world
 * @dev:	device
 * @svc_id:	service identअगरier
 * @cmd_id:	command identअगरier
 * @desc:	Descriptor काष्ठाure containing arguments and वापस values
 *
 * Sends a command to the SCM and रुकोs क्रम the command to finish processing.
 * This should *only* be called in pre-emptible context.
 */
अटल पूर्णांक qcom_scm_call(काष्ठा device *dev, स्थिर काष्ठा qcom_scm_desc *desc,
			 काष्ठा qcom_scm_res *res)
अणु
	might_sleep();
	चयन (__get_convention()) अणु
	हाल SMC_CONVENTION_ARM_32:
	हाल SMC_CONVENTION_ARM_64:
		वापस scm_smc_call(dev, desc, res, false);
	हाल SMC_CONVENTION_LEGACY:
		वापस scm_legacy_call(dev, desc, res);
	शेष:
		pr_err("Unknown current SCM calling convention.\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * qcom_scm_call_atomic() - atomic variation of qcom_scm_call()
 * @dev:	device
 * @svc_id:	service identअगरier
 * @cmd_id:	command identअगरier
 * @desc:	Descriptor काष्ठाure containing arguments and वापस values
 * @res:	Structure containing results from SMC/HVC call
 *
 * Sends a command to the SCM and रुकोs क्रम the command to finish processing.
 * This can be called in atomic context.
 */
अटल पूर्णांक qcom_scm_call_atomic(काष्ठा device *dev,
				स्थिर काष्ठा qcom_scm_desc *desc,
				काष्ठा qcom_scm_res *res)
अणु
	चयन (__get_convention()) अणु
	हाल SMC_CONVENTION_ARM_32:
	हाल SMC_CONVENTION_ARM_64:
		वापस scm_smc_call(dev, desc, res, true);
	हाल SMC_CONVENTION_LEGACY:
		वापस scm_legacy_call_atomic(dev, desc, res);
	शेष:
		pr_err("Unknown current SCM calling convention.\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool __qcom_scm_is_call_available(काष्ठा device *dev, u32 svc_id,
					 u32 cmd_id)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_INFO,
		.cmd = QCOM_SCM_INFO_IS_CALL_AVAIL,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	desc.arginfo = QCOM_SCM_ARGS(1);
	चयन (__get_convention()) अणु
	हाल SMC_CONVENTION_ARM_32:
	हाल SMC_CONVENTION_ARM_64:
		desc.args[0] = SCM_SMC_FNID(svc_id, cmd_id) |
				(ARM_SMCCC_OWNER_SIP << ARM_SMCCC_OWNER_SHIFT);
		अवरोध;
	हाल SMC_CONVENTION_LEGACY:
		desc.args[0] = SCM_LEGACY_FNID(svc_id, cmd_id);
		अवरोध;
	शेष:
		pr_err("Unknown SMC convention being used\n");
		वापस -EINVAL;
	पूर्ण

	ret = qcom_scm_call(dev, &desc, &res);

	वापस ret ? false : !!res.result[0];
पूर्ण

/**
 * qcom_scm_set_warm_boot_addr() - Set the warm boot address क्रम cpus
 * @entry: Entry poपूर्णांक function क्रम the cpus
 * @cpus: The cpumask of cpus that will use the entry poपूर्णांक
 *
 * Set the Linux entry poपूर्णांक क्रम the SCM to transfer control to when coming
 * out of a घातer करोwn. CPU घातer करोwn may be executed on cpuidle or hotplug.
 */
पूर्णांक qcom_scm_set_warm_boot_addr(व्योम *entry, स्थिर cpumask_t *cpus)
अणु
	पूर्णांक ret;
	पूर्णांक flags = 0;
	पूर्णांक cpu;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_ADDR,
		.arginfo = QCOM_SCM_ARGS(2),
	पूर्ण;

	/*
	 * Reassign only अगर we are चयनing from hotplug entry poपूर्णांक
	 * to cpuidle entry poपूर्णांक or vice versa.
	 */
	क्रम_each_cpu(cpu, cpus) अणु
		अगर (entry == qcom_scm_wb[cpu].entry)
			जारी;
		flags |= qcom_scm_wb[cpu].flag;
	पूर्ण

	/* No change in entry function */
	अगर (!flags)
		वापस 0;

	desc.args[0] = flags;
	desc.args[1] = virt_to_phys(entry);

	ret = qcom_scm_call(__scm->dev, &desc, शून्य);
	अगर (!ret) अणु
		क्रम_each_cpu(cpu, cpus)
			qcom_scm_wb[cpu].entry = entry;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_scm_set_warm_boot_addr);

/**
 * qcom_scm_set_cold_boot_addr() - Set the cold boot address क्रम cpus
 * @entry: Entry poपूर्णांक function क्रम the cpus
 * @cpus: The cpumask of cpus that will use the entry poपूर्णांक
 *
 * Set the cold boot address of the cpus. Any cpu outside the supported
 * range would be हटाओd from the cpu present mask.
 */
पूर्णांक qcom_scm_set_cold_boot_addr(व्योम *entry, स्थिर cpumask_t *cpus)
अणु
	पूर्णांक flags = 0;
	पूर्णांक cpu;
	पूर्णांक scm_cb_flags[] = अणु
		QCOM_SCM_FLAG_COLDBOOT_CPU0,
		QCOM_SCM_FLAG_COLDBOOT_CPU1,
		QCOM_SCM_FLAG_COLDBOOT_CPU2,
		QCOM_SCM_FLAG_COLDBOOT_CPU3,
	पूर्ण;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_ADDR,
		.arginfo = QCOM_SCM_ARGS(2),
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;

	अगर (!cpus || (cpus && cpumask_empty(cpus)))
		वापस -EINVAL;

	क्रम_each_cpu(cpu, cpus) अणु
		अगर (cpu < ARRAY_SIZE(scm_cb_flags))
			flags |= scm_cb_flags[cpu];
		अन्यथा
			set_cpu_present(cpu, false);
	पूर्ण

	desc.args[0] = flags;
	desc.args[1] = virt_to_phys(entry);

	वापस qcom_scm_call_atomic(__scm ? __scm->dev : शून्य, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_set_cold_boot_addr);

/**
 * qcom_scm_cpu_घातer_करोwn() - Power करोwn the cpu
 * @flags - Flags to flush cache
 *
 * This is an end poपूर्णांक to घातer करोwn cpu. If there was a pending पूर्णांकerrupt,
 * the control would वापस from this function, otherwise, the cpu jumps to the
 * warm boot entry poपूर्णांक set क्रम this cpu upon reset.
 */
व्योम qcom_scm_cpu_घातer_करोwn(u32 flags)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_TERMINATE_PC,
		.args[0] = flags & QCOM_SCM_FLUSH_FLAG_MASK,
		.arginfo = QCOM_SCM_ARGS(1),
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;

	qcom_scm_call_atomic(__scm ? __scm->dev : शून्य, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_cpu_घातer_करोwn);

पूर्णांक qcom_scm_set_remote_state(u32 state, u32 id)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_REMOTE_STATE,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = state,
		.args[1] = id,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	पूर्णांक ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_set_remote_state);

अटल पूर्णांक __qcom_scm_set_dload_mode(काष्ठा device *dev, bool enable)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_DLOAD_MODE,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = QCOM_SCM_BOOT_SET_DLOAD_MODE,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;

	desc.args[1] = enable ? QCOM_SCM_BOOT_SET_DLOAD_MODE : 0;

	वापस qcom_scm_call_atomic(__scm->dev, &desc, शून्य);
पूर्ण

अटल व्योम qcom_scm_set_करोwnload_mode(bool enable)
अणु
	bool avail;
	पूर्णांक ret = 0;

	avail = __qcom_scm_is_call_available(__scm->dev,
					     QCOM_SCM_SVC_BOOT,
					     QCOM_SCM_BOOT_SET_DLOAD_MODE);
	अगर (avail) अणु
		ret = __qcom_scm_set_dload_mode(__scm->dev, enable);
	पूर्ण अन्यथा अगर (__scm->dload_mode_addr) अणु
		ret = qcom_scm_io_ग_लिखोl(__scm->dload_mode_addr,
				enable ? QCOM_SCM_BOOT_SET_DLOAD_MODE : 0);
	पूर्ण अन्यथा अणु
		dev_err(__scm->dev,
			"No available mechanism for setting download mode\n");
	पूर्ण

	अगर (ret)
		dev_err(__scm->dev, "failed to set download mode: %d\n", ret);
पूर्ण

/**
 * qcom_scm_pas_init_image() - Initialize peripheral authentication service
 *			       state machine क्रम a given peripheral, using the
 *			       metadata
 * @peripheral: peripheral id
 * @metadata:	poपूर्णांकer to memory containing ELF header, program header table
 *		and optional blob of data used क्रम authenticating the metadata
 *		and the rest of the firmware
 * @size:	size of the metadata
 *
 * Returns 0 on success.
 */
पूर्णांक qcom_scm_pas_init_image(u32 peripheral, स्थिर व्योम *metadata, माप_प्रकार size)
अणु
	dma_addr_t mdata_phys;
	व्योम *mdata_buf;
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_INIT_IMAGE,
		.arginfo = QCOM_SCM_ARGS(2, QCOM_SCM_VAL, QCOM_SCM_RW),
		.args[0] = peripheral,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	/*
	 * During the scm call memory protection will be enabled क्रम the meta
	 * data blob, so make sure it's physically contiguous, 4K aligned and
	 * non-cachable to aव्योम XPU violations.
	 */
	mdata_buf = dma_alloc_coherent(__scm->dev, size, &mdata_phys,
				       GFP_KERNEL);
	अगर (!mdata_buf) अणु
		dev_err(__scm->dev, "Allocation of metadata buffer failed.\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(mdata_buf, metadata, size);

	ret = qcom_scm_clk_enable();
	अगर (ret)
		जाओ मुक्त_metadata;

	desc.args[1] = mdata_phys;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	qcom_scm_clk_disable();

मुक्त_metadata:
	dma_मुक्त_coherent(__scm->dev, size, mdata_buf, mdata_phys);

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_pas_init_image);

/**
 * qcom_scm_pas_mem_setup() - Prepare the memory related to a given peripheral
 *			      क्रम firmware loading
 * @peripheral:	peripheral id
 * @addr:	start address of memory area to prepare
 * @size:	size of the memory area to prepare
 *
 * Returns 0 on success.
 */
पूर्णांक qcom_scm_pas_mem_setup(u32 peripheral, phys_addr_t addr, phys_addr_t size)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_MEM_SETUP,
		.arginfo = QCOM_SCM_ARGS(3),
		.args[0] = peripheral,
		.args[1] = addr,
		.args[2] = size,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	ret = qcom_scm_clk_enable();
	अगर (ret)
		वापस ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);
	qcom_scm_clk_disable();

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_pas_mem_setup);

/**
 * qcom_scm_pas_auth_and_reset() - Authenticate the given peripheral firmware
 *				   and reset the remote processor
 * @peripheral:	peripheral id
 *
 * Return 0 on success.
 */
पूर्णांक qcom_scm_pas_auth_and_reset(u32 peripheral)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_AUTH_AND_RESET,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = peripheral,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	ret = qcom_scm_clk_enable();
	अगर (ret)
		वापस ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);
	qcom_scm_clk_disable();

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_pas_auth_and_reset);

/**
 * qcom_scm_pas_shutकरोwn() - Shut करोwn the remote processor
 * @peripheral: peripheral id
 *
 * Returns 0 on success.
 */
पूर्णांक qcom_scm_pas_shutकरोwn(u32 peripheral)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_SHUTDOWN,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = peripheral,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	ret = qcom_scm_clk_enable();
	अगर (ret)
		वापस ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	qcom_scm_clk_disable();

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_pas_shutकरोwn);

/**
 * qcom_scm_pas_supported() - Check अगर the peripheral authentication service is
 *			      available क्रम the given peripherial
 * @peripheral:	peripheral id
 *
 * Returns true अगर PAS is supported क्रम this peripheral, otherwise false.
 */
bool qcom_scm_pas_supported(u32 peripheral)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_IS_SUPPORTED,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = peripheral,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	अगर (!__qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_PIL,
					  QCOM_SCM_PIL_PAS_IS_SUPPORTED))
		वापस false;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	वापस ret ? false : !!res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_pas_supported);

अटल पूर्णांक __qcom_scm_pas_mss_reset(काष्ठा device *dev, bool reset)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_PIL,
		.cmd = QCOM_SCM_PIL_PAS_MSS_RESET,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = reset,
		.args[1] = 0,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	पूर्णांक ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	वापस ret ? : res.result[0];
पूर्ण

अटल पूर्णांक qcom_scm_pas_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				     अचिन्हित दीर्घ idx)
अणु
	अगर (idx != 0)
		वापस -EINVAL;

	वापस __qcom_scm_pas_mss_reset(__scm->dev, 1);
पूर्ण

अटल पूर्णांक qcom_scm_pas_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				       अचिन्हित दीर्घ idx)
अणु
	अगर (idx != 0)
		वापस -EINVAL;

	वापस __qcom_scm_pas_mss_reset(__scm->dev, 0);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops qcom_scm_pas_reset_ops = अणु
	.निश्चित = qcom_scm_pas_reset_निश्चित,
	.deनिश्चित = qcom_scm_pas_reset_deनिश्चित,
पूर्ण;

पूर्णांक qcom_scm_io_पढ़ोl(phys_addr_t addr, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_IO,
		.cmd = QCOM_SCM_IO_READ,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = addr,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	पूर्णांक ret;


	ret = qcom_scm_call_atomic(__scm->dev, &desc, &res);
	अगर (ret >= 0)
		*val = res.result[0];

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL(qcom_scm_io_पढ़ोl);

पूर्णांक qcom_scm_io_ग_लिखोl(phys_addr_t addr, अचिन्हित पूर्णांक val)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_IO,
		.cmd = QCOM_SCM_IO_WRITE,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = addr,
		.args[1] = val,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;

	वापस qcom_scm_call_atomic(__scm->dev, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_io_ग_लिखोl);

/**
 * qcom_scm_restore_sec_cfg_available() - Check अगर secure environment
 * supports restore security config पूर्णांकerface.
 *
 * Return true अगर restore-cfg पूर्णांकerface is supported, false अगर not.
 */
bool qcom_scm_restore_sec_cfg_available(व्योम)
अणु
	वापस __qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_MP,
					    QCOM_SCM_MP_RESTORE_SEC_CFG);
पूर्ण
EXPORT_SYMBOL(qcom_scm_restore_sec_cfg_available);

पूर्णांक qcom_scm_restore_sec_cfg(u32 device_id, u32 spare)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_RESTORE_SEC_CFG,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = device_id,
		.args[1] = spare,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	पूर्णांक ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_restore_sec_cfg);

पूर्णांक qcom_scm_iommu_secure_ptbl_size(u32 spare, माप_प्रकार *size)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_IOMMU_SECURE_PTBL_SIZE,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = spare,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;
	पूर्णांक ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	अगर (size)
		*size = res.result[0];

	वापस ret ? : res.result[1];
पूर्ण
EXPORT_SYMBOL(qcom_scm_iommu_secure_ptbl_size);

पूर्णांक qcom_scm_iommu_secure_ptbl_init(u64 addr, u32 size, u32 spare)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_IOMMU_SECURE_PTBL_INIT,
		.arginfo = QCOM_SCM_ARGS(3, QCOM_SCM_RW, QCOM_SCM_VAL,
					 QCOM_SCM_VAL),
		.args[0] = addr,
		.args[1] = size,
		.args[2] = spare,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	पूर्णांक ret;

	desc.args[0] = addr;
	desc.args[1] = size;
	desc.args[2] = spare;
	desc.arginfo = QCOM_SCM_ARGS(3, QCOM_SCM_RW, QCOM_SCM_VAL,
				     QCOM_SCM_VAL);

	ret = qcom_scm_call(__scm->dev, &desc, शून्य);

	/* the pg table has been initialized alपढ़ोy, ignore the error */
	अगर (ret == -EPERM)
		ret = 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_scm_iommu_secure_ptbl_init);

पूर्णांक qcom_scm_mem_protect_video_var(u32 cp_start, u32 cp_size,
				   u32 cp_nonpixel_start,
				   u32 cp_nonpixel_size)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_VIDEO_VAR,
		.arginfo = QCOM_SCM_ARGS(4, QCOM_SCM_VAL, QCOM_SCM_VAL,
					 QCOM_SCM_VAL, QCOM_SCM_VAL),
		.args[0] = cp_start,
		.args[1] = cp_size,
		.args[2] = cp_nonpixel_start,
		.args[3] = cp_nonpixel_size,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	ret = qcom_scm_call(__scm->dev, &desc, &res);

	वापस ret ? : res.result[0];
पूर्ण
EXPORT_SYMBOL(qcom_scm_mem_protect_video_var);

अटल पूर्णांक __qcom_scm_assign_mem(काष्ठा device *dev, phys_addr_t mem_region,
				 माप_प्रकार mem_sz, phys_addr_t src, माप_प्रकार src_sz,
				 phys_addr_t dest, माप_प्रकार dest_sz)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_ASSIGN,
		.arginfo = QCOM_SCM_ARGS(7, QCOM_SCM_RO, QCOM_SCM_VAL,
					 QCOM_SCM_RO, QCOM_SCM_VAL, QCOM_SCM_RO,
					 QCOM_SCM_VAL, QCOM_SCM_VAL),
		.args[0] = mem_region,
		.args[1] = mem_sz,
		.args[2] = src,
		.args[3] = src_sz,
		.args[4] = dest,
		.args[5] = dest_sz,
		.args[6] = 0,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	ret = qcom_scm_call(dev, &desc, &res);

	वापस ret ? : res.result[0];
पूर्ण

/**
 * qcom_scm_assign_mem() - Make a secure call to reassign memory ownership
 * @mem_addr: mem region whose ownership need to be reasचिन्हित
 * @mem_sz:   size of the region.
 * @srcvm:    vmid क्रम current set of owners, each set bit in
 *            flag indicate a unique owner
 * @newvm:    array having new owners and corresponding permission
 *            flags
 * @dest_cnt: number of owners in next set.
 *
 * Return negative त्रुटि_सं on failure or 0 on success with @srcvm updated.
 */
पूर्णांक qcom_scm_assign_mem(phys_addr_t mem_addr, माप_प्रकार mem_sz,
			अचिन्हित पूर्णांक *srcvm,
			स्थिर काष्ठा qcom_scm_vmperm *newvm,
			अचिन्हित पूर्णांक dest_cnt)
अणु
	काष्ठा qcom_scm_current_perm_info *destvm;
	काष्ठा qcom_scm_mem_map_info *mem_to_map;
	phys_addr_t mem_to_map_phys;
	phys_addr_t dest_phys;
	dma_addr_t ptr_phys;
	माप_प्रकार mem_to_map_sz;
	माप_प्रकार dest_sz;
	माप_प्रकार src_sz;
	माप_प्रकार ptr_sz;
	पूर्णांक next_vm;
	__le32 *src;
	व्योम *ptr;
	पूर्णांक ret, i, b;
	अचिन्हित दीर्घ srcvm_bits = *srcvm;

	src_sz = hweight_दीर्घ(srcvm_bits) * माप(*src);
	mem_to_map_sz = माप(*mem_to_map);
	dest_sz = dest_cnt * माप(*destvm);
	ptr_sz = ALIGN(src_sz, SZ_64) + ALIGN(mem_to_map_sz, SZ_64) +
			ALIGN(dest_sz, SZ_64);

	ptr = dma_alloc_coherent(__scm->dev, ptr_sz, &ptr_phys, GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	/* Fill source vmid detail */
	src = ptr;
	i = 0;
	क्रम_each_set_bit(b, &srcvm_bits, BITS_PER_LONG)
		src[i++] = cpu_to_le32(b);

	/* Fill details of mem buff to map */
	mem_to_map = ptr + ALIGN(src_sz, SZ_64);
	mem_to_map_phys = ptr_phys + ALIGN(src_sz, SZ_64);
	mem_to_map->mem_addr = cpu_to_le64(mem_addr);
	mem_to_map->mem_size = cpu_to_le64(mem_sz);

	next_vm = 0;
	/* Fill details of next vmid detail */
	destvm = ptr + ALIGN(mem_to_map_sz, SZ_64) + ALIGN(src_sz, SZ_64);
	dest_phys = ptr_phys + ALIGN(mem_to_map_sz, SZ_64) + ALIGN(src_sz, SZ_64);
	क्रम (i = 0; i < dest_cnt; i++, destvm++, newvm++) अणु
		destvm->vmid = cpu_to_le32(newvm->vmid);
		destvm->perm = cpu_to_le32(newvm->perm);
		destvm->ctx = 0;
		destvm->ctx_size = 0;
		next_vm |= BIT(newvm->vmid);
	पूर्ण

	ret = __qcom_scm_assign_mem(__scm->dev, mem_to_map_phys, mem_to_map_sz,
				    ptr_phys, src_sz, dest_phys, dest_sz);
	dma_मुक्त_coherent(__scm->dev, ptr_sz, ptr, ptr_phys);
	अगर (ret) अणु
		dev_err(__scm->dev,
			"Assign memory protection call failed %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	*srcvm = next_vm;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qcom_scm_assign_mem);

/**
 * qcom_scm_ocmem_lock_available() - is OCMEM lock/unlock पूर्णांकerface available
 */
bool qcom_scm_ocmem_lock_available(व्योम)
अणु
	वापस __qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_OCMEM,
					    QCOM_SCM_OCMEM_LOCK_CMD);
पूर्ण
EXPORT_SYMBOL(qcom_scm_ocmem_lock_available);

/**
 * qcom_scm_ocmem_lock() - call OCMEM lock पूर्णांकerface to assign an OCMEM
 * region to the specअगरied initiator
 *
 * @id:     tz initiator id
 * @offset: OCMEM offset
 * @size:   OCMEM size
 * @mode:   access mode (WIDE/NARROW)
 */
पूर्णांक qcom_scm_ocmem_lock(क्रमागत qcom_scm_ocmem_client id, u32 offset, u32 size,
			u32 mode)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_OCMEM,
		.cmd = QCOM_SCM_OCMEM_LOCK_CMD,
		.args[0] = id,
		.args[1] = offset,
		.args[2] = size,
		.args[3] = mode,
		.arginfo = QCOM_SCM_ARGS(4),
	पूर्ण;

	वापस qcom_scm_call(__scm->dev, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_ocmem_lock);

/**
 * qcom_scm_ocmem_unlock() - call OCMEM unlock पूर्णांकerface to release an OCMEM
 * region from the specअगरied initiator
 *
 * @id:     tz initiator id
 * @offset: OCMEM offset
 * @size:   OCMEM size
 */
पूर्णांक qcom_scm_ocmem_unlock(क्रमागत qcom_scm_ocmem_client id, u32 offset, u32 size)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_OCMEM,
		.cmd = QCOM_SCM_OCMEM_UNLOCK_CMD,
		.args[0] = id,
		.args[1] = offset,
		.args[2] = size,
		.arginfo = QCOM_SCM_ARGS(3),
	पूर्ण;

	वापस qcom_scm_call(__scm->dev, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_ocmem_unlock);

/**
 * qcom_scm_ice_available() - Is the ICE key programming पूर्णांकerface available?
 *
 * Return: true अगरf the SCM calls wrapped by qcom_scm_ice_invalidate_key() and
 *	   qcom_scm_ice_set_key() are available.
 */
bool qcom_scm_ice_available(व्योम)
अणु
	वापस __qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_ES,
					    QCOM_SCM_ES_INVALIDATE_ICE_KEY) &&
		__qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_ES,
					     QCOM_SCM_ES_CONFIG_SET_ICE_KEY);
पूर्ण
EXPORT_SYMBOL(qcom_scm_ice_available);

/**
 * qcom_scm_ice_invalidate_key() - Invalidate an अंतरभूत encryption key
 * @index: the keyslot to invalidate
 *
 * The UFSHCI and eMMC standards define a standard way to करो this, but it
 * करोesn't work on these SoCs; only this SCM call करोes.
 *
 * It is assumed that the SoC has only one ICE instance being used, as this SCM
 * call करोesn't specअगरy which ICE instance the keyslot beदीर्घs to.
 *
 * Return: 0 on success; -त्रुटि_सं on failure.
 */
पूर्णांक qcom_scm_ice_invalidate_key(u32 index)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_ES,
		.cmd = QCOM_SCM_ES_INVALIDATE_ICE_KEY,
		.arginfo = QCOM_SCM_ARGS(1),
		.args[0] = index,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;

	वापस qcom_scm_call(__scm->dev, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_ice_invalidate_key);

/**
 * qcom_scm_ice_set_key() - Set an अंतरभूत encryption key
 * @index: the keyslot पूर्णांकo which to set the key
 * @key: the key to program
 * @key_size: the size of the key in bytes
 * @cipher: the encryption algorithm the key is क्रम
 * @data_unit_size: the encryption data unit size, i.e. the size of each
 *		    inभागidual plaपूर्णांकext and ciphertext.  Given in 512-byte
 *		    units, e.g. 1 = 512 bytes, 8 = 4096 bytes, etc.
 *
 * Program a key पूर्णांकo a keyslot of Qualcomm ICE (Inline Crypto Engine), where it
 * can then be used to encrypt/decrypt UFS or eMMC I/O requests अंतरभूत.
 *
 * The UFSHCI and eMMC standards define a standard way to करो this, but it
 * करोesn't work on these SoCs; only this SCM call करोes.
 *
 * It is assumed that the SoC has only one ICE instance being used, as this SCM
 * call करोesn't specअगरy which ICE instance the keyslot beदीर्घs to.
 *
 * Return: 0 on success; -त्रुटि_सं on failure.
 */
पूर्णांक qcom_scm_ice_set_key(u32 index, स्थिर u8 *key, u32 key_size,
			 क्रमागत qcom_scm_ice_cipher cipher, u32 data_unit_size)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_ES,
		.cmd = QCOM_SCM_ES_CONFIG_SET_ICE_KEY,
		.arginfo = QCOM_SCM_ARGS(5, QCOM_SCM_VAL, QCOM_SCM_RW,
					 QCOM_SCM_VAL, QCOM_SCM_VAL,
					 QCOM_SCM_VAL),
		.args[0] = index,
		.args[2] = key_size,
		.args[3] = cipher,
		.args[4] = data_unit_size,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	व्योम *keybuf;
	dma_addr_t key_phys;
	पूर्णांक ret;

	/*
	 * 'key' may point to vmalloc()'ed memory, but we need to pass a
	 * physical address that's been properly flushed.  The sanctioned way to
	 * करो this is by using the DMA API.  But as is best practice क्रम crypto
	 * keys, we also must wipe the key after use.  This makes kmemdup() +
	 * dma_map_single() not clearly correct, since the DMA API can use
	 * bounce buffers.  Instead, just use dma_alloc_coherent().  Programming
	 * keys is normally rare and thus not perक्रमmance-critical.
	 */

	keybuf = dma_alloc_coherent(__scm->dev, key_size, &key_phys,
				    GFP_KERNEL);
	अगर (!keybuf)
		वापस -ENOMEM;
	स_नकल(keybuf, key, key_size);
	desc.args[1] = key_phys;

	ret = qcom_scm_call(__scm->dev, &desc, शून्य);

	memzero_explicit(keybuf, key_size);

	dma_मुक्त_coherent(__scm->dev, key_size, keybuf, key_phys);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_scm_ice_set_key);

/**
 * qcom_scm_hdcp_available() - Check अगर secure environment supports HDCP.
 *
 * Return true अगर HDCP is supported, false अगर not.
 */
bool qcom_scm_hdcp_available(व्योम)
अणु
	bool avail;
	पूर्णांक ret = qcom_scm_clk_enable();

	अगर (ret)
		वापस ret;

	avail = __qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_HDCP,
						QCOM_SCM_HDCP_INVOKE);

	qcom_scm_clk_disable();

	वापस avail;
पूर्ण
EXPORT_SYMBOL(qcom_scm_hdcp_available);

/**
 * qcom_scm_hdcp_req() - Send HDCP request.
 * @req: HDCP request array
 * @req_cnt: HDCP request array count
 * @resp: response buffer passed to SCM
 *
 * Write HDCP रेजिस्टर(s) through SCM.
 */
पूर्णांक qcom_scm_hdcp_req(काष्ठा qcom_scm_hdcp_req *req, u32 req_cnt, u32 *resp)
अणु
	पूर्णांक ret;
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_HDCP,
		.cmd = QCOM_SCM_HDCP_INVOKE,
		.arginfo = QCOM_SCM_ARGS(10),
		.args = अणु
			req[0].addr,
			req[0].val,
			req[1].addr,
			req[1].val,
			req[2].addr,
			req[2].val,
			req[3].addr,
			req[3].val,
			req[4].addr,
			req[4].val
		पूर्ण,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;
	काष्ठा qcom_scm_res res;

	अगर (req_cnt > QCOM_SCM_HDCP_MAX_REQ_CNT)
		वापस -दुस्फल;

	ret = qcom_scm_clk_enable();
	अगर (ret)
		वापस ret;

	ret = qcom_scm_call(__scm->dev, &desc, &res);
	*resp = res.result[0];

	qcom_scm_clk_disable();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_scm_hdcp_req);

पूर्णांक qcom_scm_qsmmu500_रुको_safe_toggle(bool en)
अणु
	काष्ठा qcom_scm_desc desc = अणु
		.svc = QCOM_SCM_SVC_SMMU_PROGRAM,
		.cmd = QCOM_SCM_SMMU_CONFIG_ERRATA1,
		.arginfo = QCOM_SCM_ARGS(2),
		.args[0] = QCOM_SCM_SMMU_CONFIG_ERRATA1_CLIENT_ALL,
		.args[1] = en,
		.owner = ARM_SMCCC_OWNER_SIP,
	पूर्ण;


	वापस qcom_scm_call_atomic(__scm->dev, &desc, शून्य);
पूर्ण
EXPORT_SYMBOL(qcom_scm_qsmmu500_रुको_safe_toggle);

अटल पूर्णांक qcom_scm_find_dload_address(काष्ठा device *dev, u64 *addr)
अणु
	काष्ठा device_node *tcsr;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource res;
	u32 offset;
	पूर्णांक ret;

	tcsr = of_parse_phandle(np, "qcom,dload-mode", 0);
	अगर (!tcsr)
		वापस 0;

	ret = of_address_to_resource(tcsr, 0, &res);
	of_node_put(tcsr);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32_index(np, "qcom,dload-mode", 1, &offset);
	अगर (ret < 0)
		वापस ret;

	*addr = res.start + offset;

	वापस 0;
पूर्ण

/**
 * qcom_scm_is_available() - Checks अगर SCM is available
 */
bool qcom_scm_is_available(व्योम)
अणु
	वापस !!__scm;
पूर्ण
EXPORT_SYMBOL(qcom_scm_is_available);

अटल पूर्णांक qcom_scm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_scm *scm;
	अचिन्हित दीर्घ clks;
	पूर्णांक ret;

	scm = devm_kzalloc(&pdev->dev, माप(*scm), GFP_KERNEL);
	अगर (!scm)
		वापस -ENOMEM;

	ret = qcom_scm_find_dload_address(&pdev->dev, &scm->dload_mode_addr);
	अगर (ret < 0)
		वापस ret;

	clks = (अचिन्हित दीर्घ)of_device_get_match_data(&pdev->dev);

	scm->core_clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(scm->core_clk)) अणु
		अगर (PTR_ERR(scm->core_clk) == -EPROBE_DEFER)
			वापस PTR_ERR(scm->core_clk);

		अगर (clks & SCM_HAS_CORE_CLK) अणु
			dev_err(&pdev->dev, "failed to acquire core clk\n");
			वापस PTR_ERR(scm->core_clk);
		पूर्ण

		scm->core_clk = शून्य;
	पूर्ण

	scm->अगरace_clk = devm_clk_get(&pdev->dev, "iface");
	अगर (IS_ERR(scm->अगरace_clk)) अणु
		अगर (PTR_ERR(scm->अगरace_clk) == -EPROBE_DEFER)
			वापस PTR_ERR(scm->अगरace_clk);

		अगर (clks & SCM_HAS_IFACE_CLK) अणु
			dev_err(&pdev->dev, "failed to acquire iface clk\n");
			वापस PTR_ERR(scm->अगरace_clk);
		पूर्ण

		scm->अगरace_clk = शून्य;
	पूर्ण

	scm->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(scm->bus_clk)) अणु
		अगर (PTR_ERR(scm->bus_clk) == -EPROBE_DEFER)
			वापस PTR_ERR(scm->bus_clk);

		अगर (clks & SCM_HAS_BUS_CLK) अणु
			dev_err(&pdev->dev, "failed to acquire bus clk\n");
			वापस PTR_ERR(scm->bus_clk);
		पूर्ण

		scm->bus_clk = शून्य;
	पूर्ण

	scm->reset.ops = &qcom_scm_pas_reset_ops;
	scm->reset.nr_resets = 1;
	scm->reset.of_node = pdev->dev.of_node;
	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &scm->reset);
	अगर (ret)
		वापस ret;

	/* vote क्रम max clk rate क्रम highest perक्रमmance */
	ret = clk_set_rate(scm->core_clk, पूर्णांक_उच्च);
	अगर (ret)
		वापस ret;

	__scm = scm;
	__scm->dev = &pdev->dev;

	__get_convention();

	/*
	 * If requested enable "download mode", from this poपूर्णांक on warmboot
	 * will cause the the boot stages to enter करोwnload mode, unless
	 * disabled below by a clean shutकरोwn/reboot.
	 */
	अगर (करोwnload_mode)
		qcom_scm_set_करोwnload_mode(true);

	वापस 0;
पूर्ण

अटल व्योम qcom_scm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/* Clean shutकरोwn, disable करोwnload mode to allow normal restart */
	अगर (करोwnload_mode)
		qcom_scm_set_करोwnload_mode(false);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_scm_dt_match[] = अणु
	अणु .compatible = "qcom,scm-apq8064",
	  /* FIXME: This should have .data = (व्योम *) SCM_HAS_CORE_CLK */
	पूर्ण,
	अणु .compatible = "qcom,scm-apq8084", .data = (व्योम *)(SCM_HAS_CORE_CLK |
							     SCM_HAS_IFACE_CLK |
							     SCM_HAS_BUS_CLK)
	पूर्ण,
	अणु .compatible = "qcom,scm-ipq4019" पूर्ण,
	अणु .compatible = "qcom,scm-msm8660", .data = (व्योम *) SCM_HAS_CORE_CLK पूर्ण,
	अणु .compatible = "qcom,scm-msm8960", .data = (व्योम *) SCM_HAS_CORE_CLK पूर्ण,
	अणु .compatible = "qcom,scm-msm8916", .data = (व्योम *)(SCM_HAS_CORE_CLK |
							     SCM_HAS_IFACE_CLK |
							     SCM_HAS_BUS_CLK)
	पूर्ण,
	अणु .compatible = "qcom,scm-msm8974", .data = (व्योम *)(SCM_HAS_CORE_CLK |
							     SCM_HAS_IFACE_CLK |
							     SCM_HAS_BUS_CLK)
	पूर्ण,
	अणु .compatible = "qcom,scm-msm8994" पूर्ण,
	अणु .compatible = "qcom,scm-msm8996" पूर्ण,
	अणु .compatible = "qcom,scm" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_scm_driver = अणु
	.driver = अणु
		.name	= "qcom_scm",
		.of_match_table = qcom_scm_dt_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = qcom_scm_probe,
	.shutकरोwn = qcom_scm_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init qcom_scm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_scm_driver);
पूर्ण
subsys_initcall(qcom_scm_init);
