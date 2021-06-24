<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#घोषणा pr_fmt(fmt)	"habanalabs: " fmt

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "habanalabs.h"

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

अटल u32 hl_debug_काष्ठा_size[HL_DEBUG_OP_TIMESTAMP + 1] = अणु
	[HL_DEBUG_OP_ETR] = माप(काष्ठा hl_debug_params_etr),
	[HL_DEBUG_OP_ETF] = माप(काष्ठा hl_debug_params_etf),
	[HL_DEBUG_OP_STM] = माप(काष्ठा hl_debug_params_sपंचांग),
	[HL_DEBUG_OP_FUNNEL] = 0,
	[HL_DEBUG_OP_BMON] = माप(काष्ठा hl_debug_params_bmon),
	[HL_DEBUG_OP_SPMU] = माप(काष्ठा hl_debug_params_spmu),
	[HL_DEBUG_OP_TIMESTAMP] = 0

पूर्ण;

अटल पूर्णांक device_status_info(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_device_status dev_stat = अणु0पूर्ण;
	u32 size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!size) || (!out))
		वापस -EINVAL;

	dev_stat.status = hl_device_status(hdev);

	वापस copy_to_user(out, &dev_stat,
			min((माप_प्रकार)size, माप(dev_stat))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक hw_ip_info(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_hw_ip_info hw_ip = अणु0पूर्ण;
	u32 size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 sram_kmd_size, dram_kmd_size;

	अगर ((!size) || (!out))
		वापस -EINVAL;

	sram_kmd_size = (prop->sram_user_base_address -
				prop->sram_base_address);
	dram_kmd_size = (prop->dram_user_base_address -
				prop->dram_base_address);

	hw_ip.device_id = hdev->asic_funcs->get_pci_id(hdev);
	hw_ip.sram_base_address = prop->sram_user_base_address;
	hw_ip.dram_base_address =
			hdev->mmu_enable && prop->dram_supports_भव_memory ?
			prop->dmmu.start_addr : prop->dram_user_base_address;
	hw_ip.tpc_enabled_mask = prop->tpc_enabled_mask;
	hw_ip.sram_size = prop->sram_size - sram_kmd_size;

	अगर (hdev->mmu_enable)
		hw_ip.dram_size =
			DIV_ROUND_DOWN_ULL(prop->dram_size - dram_kmd_size,
						prop->dram_page_size) *
							prop->dram_page_size;
	अन्यथा
		hw_ip.dram_size = prop->dram_size - dram_kmd_size;

	अगर (hw_ip.dram_size > PAGE_SIZE)
		hw_ip.dram_enabled = 1;
	hw_ip.dram_page_size = prop->dram_page_size;
	hw_ip.num_of_events = prop->num_of_events;

	स_नकल(hw_ip.cpucp_version, prop->cpucp_info.cpucp_version,
		min(VERSION_MAX_LEN, HL_INFO_VERSION_MAX_LEN));

	स_नकल(hw_ip.card_name, prop->cpucp_info.card_name,
		min(CARD_NAME_MAX_LEN, HL_INFO_CARD_NAME_MAX_LEN));

	hw_ip.cpld_version = le32_to_cpu(prop->cpucp_info.cpld_version);
	hw_ip.module_id = le32_to_cpu(prop->cpucp_info.card_location);

	hw_ip.psoc_pci_pll_nr = prop->psoc_pci_pll_nr;
	hw_ip.psoc_pci_pll_nf = prop->psoc_pci_pll_nf;
	hw_ip.psoc_pci_pll_od = prop->psoc_pci_pll_od;
	hw_ip.psoc_pci_pll_भाग_factor = prop->psoc_pci_pll_भाग_factor;

	hw_ip.first_available_पूर्णांकerrupt_id =
			prop->first_available_user_msix_पूर्णांकerrupt;
	वापस copy_to_user(out, &hw_ip,
		min((माप_प्रकार)size, माप(hw_ip))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक hw_events_info(काष्ठा hl_device *hdev, bool aggregate,
			काष्ठा hl_info_args *args)
अणु
	u32 size, max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	व्योम *arr;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	arr = hdev->asic_funcs->get_events_stat(hdev, aggregate, &size);

	वापस copy_to_user(out, arr, min(max_size, size)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक dram_usage_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_info_dram_usage dram_usage = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 dram_kmd_size;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	dram_kmd_size = (prop->dram_user_base_address -
				prop->dram_base_address);
	dram_usage.dram_मुक्त_mem = (prop->dram_size - dram_kmd_size) -
					atomic64_पढ़ो(&hdev->dram_used_mem);
	अगर (hpriv->ctx)
		dram_usage.ctx_dram_mem =
			atomic64_पढ़ो(&hpriv->ctx->dram_phys_mem);

	वापस copy_to_user(out, &dram_usage,
		min((माप_प्रकार) max_size, माप(dram_usage))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक hw_idle(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_hw_idle hw_idle = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	hw_idle.is_idle = hdev->asic_funcs->is_device_idle(hdev,
					hw_idle.busy_engines_mask_ext,
					HL_BUSY_ENGINES_MASK_EXT_SIZE, शून्य);
	hw_idle.busy_engines_mask =
			lower_32_bits(hw_idle.busy_engines_mask_ext[0]);

	वापस copy_to_user(out, &hw_idle,
		min((माप_प्रकार) max_size, माप(hw_idle))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक debug_coresight(काष्ठा hl_device *hdev, काष्ठा hl_debug_args *args)
अणु
	काष्ठा hl_debug_params *params;
	व्योम *input = शून्य, *output = शून्य;
	पूर्णांक rc;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	params->reg_idx = args->reg_idx;
	params->enable = args->enable;
	params->op = args->op;

	अगर (args->input_ptr && args->input_size) अणु
		input = kzalloc(hl_debug_काष्ठा_size[args->op], GFP_KERNEL);
		अगर (!input) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (copy_from_user(input, u64_to_user_ptr(args->input_ptr),
					args->input_size)) अणु
			rc = -EFAULT;
			dev_err(hdev->dev, "failed to copy input debug data\n");
			जाओ out;
		पूर्ण

		params->input = input;
	पूर्ण

	अगर (args->output_ptr && args->output_size) अणु
		output = kzalloc(args->output_size, GFP_KERNEL);
		अगर (!output) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		params->output = output;
		params->output_size = args->output_size;
	पूर्ण

	rc = hdev->asic_funcs->debug_coresight(hdev, params);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"debug coresight operation failed %d\n", rc);
		जाओ out;
	पूर्ण

	अगर (output && copy_to_user((व्योम __user *) (uपूर्णांकptr_t) args->output_ptr,
					output, args->output_size)) अणु
		dev_err(hdev->dev, "copy to user failed in debug ioctl\n");
		rc = -EFAULT;
		जाओ out;
	पूर्ण


out:
	kमुक्त(params);
	kमुक्त(output);
	kमुक्त(input);

	वापस rc;
पूर्ण

अटल पूर्णांक device_utilization(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_device_utilization device_util = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hl_device_utilization(hdev, &device_util.utilization);
	अगर (rc)
		वापस -EINVAL;

	वापस copy_to_user(out, &device_util,
		min((माप_प्रकार) max_size, माप(device_util))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक get_clk_rate(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_clk_rate clk_rate = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hdev->asic_funcs->get_clk_rate(hdev, &clk_rate.cur_clk_rate_mhz,
						&clk_rate.max_clk_rate_mhz);
	अगर (rc)
		वापस rc;

	वापस copy_to_user(out, &clk_rate,
		min((माप_प्रकार) max_size, माप(clk_rate))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक get_reset_count(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_reset_count reset_count = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	reset_count.hard_reset_cnt = hdev->hard_reset_cnt;
	reset_count.soft_reset_cnt = hdev->soft_reset_cnt;

	वापस copy_to_user(out, &reset_count,
		min((माप_प्रकार) max_size, माप(reset_count))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक समय_sync_info(काष्ठा hl_device *hdev, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_info_समय_sync समय_sync = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	समय_sync.device_समय = hdev->asic_funcs->get_device_समय(hdev);
	समय_sync.host_समय = kसमय_get_raw_ns();

	वापस copy_to_user(out, &समय_sync,
		min((माप_प्रकार) max_size, माप(समय_sync))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक pci_counters_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_info_pci_counters pci_counters = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hl_fw_cpucp_pci_counters_get(hdev, &pci_counters);
	अगर (rc)
		वापस rc;

	वापस copy_to_user(out, &pci_counters,
		min((माप_प्रकार) max_size, माप(pci_counters))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक clk_throttle_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_info_clk_throttle clk_throttle = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	clk_throttle.clk_throttling_reason = hdev->clk_throttling_reason;

	वापस copy_to_user(out, &clk_throttle,
		min((माप_प्रकार) max_size, माप(clk_throttle))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक cs_counters_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	काष्ठा hl_info_cs_counters cs_counters = अणु0पूर्ण;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_cs_counters_atomic *cntr;
	u32 max_size = args->वापस_size;

	cntr = &hdev->aggregated_cs_counters;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	cs_counters.total_out_of_mem_drop_cnt =
			atomic64_पढ़ो(&cntr->out_of_mem_drop_cnt);
	cs_counters.total_parsing_drop_cnt =
			atomic64_पढ़ो(&cntr->parsing_drop_cnt);
	cs_counters.total_queue_full_drop_cnt =
			atomic64_पढ़ो(&cntr->queue_full_drop_cnt);
	cs_counters.total_device_in_reset_drop_cnt =
			atomic64_पढ़ो(&cntr->device_in_reset_drop_cnt);
	cs_counters.total_max_cs_in_flight_drop_cnt =
			atomic64_पढ़ो(&cntr->max_cs_in_flight_drop_cnt);
	cs_counters.total_validation_drop_cnt =
			atomic64_पढ़ो(&cntr->validation_drop_cnt);

	अगर (hpriv->ctx) अणु
		cs_counters.ctx_out_of_mem_drop_cnt =
				atomic64_पढ़ो(
				&hpriv->ctx->cs_counters.out_of_mem_drop_cnt);
		cs_counters.ctx_parsing_drop_cnt =
				atomic64_पढ़ो(
				&hpriv->ctx->cs_counters.parsing_drop_cnt);
		cs_counters.ctx_queue_full_drop_cnt =
				atomic64_पढ़ो(
				&hpriv->ctx->cs_counters.queue_full_drop_cnt);
		cs_counters.ctx_device_in_reset_drop_cnt =
				atomic64_पढ़ो(
			&hpriv->ctx->cs_counters.device_in_reset_drop_cnt);
		cs_counters.ctx_max_cs_in_flight_drop_cnt =
				atomic64_पढ़ो(
			&hpriv->ctx->cs_counters.max_cs_in_flight_drop_cnt);
		cs_counters.ctx_validation_drop_cnt =
				atomic64_पढ़ो(
				&hpriv->ctx->cs_counters.validation_drop_cnt);
	पूर्ण

	वापस copy_to_user(out, &cs_counters,
		min((माप_प्रकार) max_size, माप(cs_counters))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक sync_manager_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_info_sync_manager sm_info = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	अगर (args->dcore_id >= HL_MAX_DCORES)
		वापस -EINVAL;

	sm_info.first_available_sync_object =
			prop->first_available_user_sob[args->dcore_id];
	sm_info.first_available_monitor =
			prop->first_available_user_mon[args->dcore_id];
	sm_info.first_available_cq =
			prop->first_available_cq[args->dcore_id];

	वापस copy_to_user(out, &sm_info, min_t(माप_प्रकार, (माप_प्रकार) max_size,
			माप(sm_info))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक total_energy_consumption_info(काष्ठा hl_fpriv *hpriv,
			काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_info_energy total_energy = अणु0पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hl_fw_cpucp_total_energy_get(hdev,
			&total_energy.total_energy_consumption);
	अगर (rc)
		वापस rc;

	वापस copy_to_user(out, &total_energy,
		min((माप_प्रकार) max_size, माप(total_energy))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक pll_frequency_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_pll_frequency_info freq_info = अणु अणु0पूर्ण पूर्ण;
	u32 max_size = args->वापस_size;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hl_fw_cpucp_pll_info_get(hdev, args->pll_index, freq_info.output);
	अगर (rc)
		वापस rc;

	वापस copy_to_user(out, &freq_info,
		min((माप_प्रकार) max_size, माप(freq_info))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक घातer_info(काष्ठा hl_fpriv *hpriv, काष्ठा hl_info_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	u32 max_size = args->वापस_size;
	काष्ठा hl_घातer_info घातer_info = अणु0पूर्ण;
	व्योम __user *out = (व्योम __user *) (uपूर्णांकptr_t) args->वापस_poपूर्णांकer;
	पूर्णांक rc;

	अगर ((!max_size) || (!out))
		वापस -EINVAL;

	rc = hl_fw_cpucp_घातer_get(hdev, &घातer_info.घातer);
	अगर (rc)
		वापस rc;

	वापस copy_to_user(out, &घातer_info,
		min((माप_प्रकार) max_size, माप(घातer_info))) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक _hl_info_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data,
				काष्ठा device *dev)
अणु
	क्रमागत hl_device_status status;
	काष्ठा hl_info_args *args = data;
	काष्ठा hl_device *hdev = hpriv->hdev;

	पूर्णांक rc;

	/*
	 * Inक्रमmation is वापसed क्रम the following opcodes even अगर the device
	 * is disabled or in reset.
	 */
	चयन (args->op) अणु
	हाल HL_INFO_HW_IP_INFO:
		वापस hw_ip_info(hdev, args);

	हाल HL_INFO_DEVICE_STATUS:
		वापस device_status_info(hdev, args);

	हाल HL_INFO_RESET_COUNT:
		वापस get_reset_count(hdev, args);

	शेष:
		अवरोध;
	पूर्ण

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_warn_ratelimited(dev,
			"Device is %s. Can't execute INFO IOCTL\n",
			hdev->status[status]);
		वापस -EBUSY;
	पूर्ण

	चयन (args->op) अणु
	हाल HL_INFO_HW_EVENTS:
		rc = hw_events_info(hdev, false, args);
		अवरोध;

	हाल HL_INFO_DRAM_USAGE:
		rc = dram_usage_info(hpriv, args);
		अवरोध;

	हाल HL_INFO_HW_IDLE:
		rc = hw_idle(hdev, args);
		अवरोध;

	हाल HL_INFO_DEVICE_UTILIZATION:
		rc = device_utilization(hdev, args);
		अवरोध;

	हाल HL_INFO_HW_EVENTS_AGGREGATE:
		rc = hw_events_info(hdev, true, args);
		अवरोध;

	हाल HL_INFO_CLK_RATE:
		rc = get_clk_rate(hdev, args);
		अवरोध;

	हाल HL_INFO_TIME_SYNC:
		वापस समय_sync_info(hdev, args);

	हाल HL_INFO_CS_COUNTERS:
		वापस cs_counters_info(hpriv, args);

	हाल HL_INFO_PCI_COUNTERS:
		वापस pci_counters_info(hpriv, args);

	हाल HL_INFO_CLK_THROTTLE_REASON:
		वापस clk_throttle_info(hpriv, args);

	हाल HL_INFO_SYNC_MANAGER:
		वापस sync_manager_info(hpriv, args);

	हाल HL_INFO_TOTAL_ENERGY:
		वापस total_energy_consumption_info(hpriv, args);

	हाल HL_INFO_PLL_FREQUENCY:
		वापस pll_frequency_info(hpriv, args);

	हाल HL_INFO_POWER:
		वापस घातer_info(hpriv, args);

	शेष:
		dev_err(dev, "Invalid request %d\n", args->op);
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक hl_info_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	वापस _hl_info_ioctl(hpriv, data, hpriv->hdev->dev);
पूर्ण

अटल पूर्णांक hl_info_ioctl_control(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	वापस _hl_info_ioctl(hpriv, data, hpriv->hdev->dev_ctrl);
पूर्ण

अटल पूर्णांक hl_debug_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	काष्ठा hl_debug_args *args = data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	क्रमागत hl_device_status status;

	पूर्णांक rc = 0;

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't execute DEBUG IOCTL\n",
			hdev->status[status]);
		वापस -EBUSY;
	पूर्ण

	चयन (args->op) अणु
	हाल HL_DEBUG_OP_ETR:
	हाल HL_DEBUG_OP_ETF:
	हाल HL_DEBUG_OP_STM:
	हाल HL_DEBUG_OP_FUNNEL:
	हाल HL_DEBUG_OP_BMON:
	हाल HL_DEBUG_OP_SPMU:
	हाल HL_DEBUG_OP_TIMESTAMP:
		अगर (!hdev->in_debug) अणु
			dev_err_ratelimited(hdev->dev,
				"Rejecting debug configuration request because device not in debug mode\n");
			वापस -EFAULT;
		पूर्ण
		args->input_size =
			min(args->input_size, hl_debug_काष्ठा_size[args->op]);
		rc = debug_coresight(hdev, args);
		अवरोध;
	हाल HL_DEBUG_OP_SET_MODE:
		rc = hl_device_set_debug_mode(hdev, (bool) args->enable);
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Invalid request %d\n", args->op);
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

#घोषणा HL_IOCTL_DEF(ioctl, _func) \
	[_IOC_NR(ioctl)] = अणु.cmd = ioctl, .func = _funcपूर्ण

अटल स्थिर काष्ठा hl_ioctl_desc hl_ioctls[] = अणु
	HL_IOCTL_DEF(HL_IOCTL_INFO, hl_info_ioctl),
	HL_IOCTL_DEF(HL_IOCTL_CB, hl_cb_ioctl),
	HL_IOCTL_DEF(HL_IOCTL_CS, hl_cs_ioctl),
	HL_IOCTL_DEF(HL_IOCTL_WAIT_CS, hl_रुको_ioctl),
	HL_IOCTL_DEF(HL_IOCTL_MEMORY, hl_mem_ioctl),
	HL_IOCTL_DEF(HL_IOCTL_DEBUG, hl_debug_ioctl)
पूर्ण;

अटल स्थिर काष्ठा hl_ioctl_desc hl_ioctls_control[] = अणु
	HL_IOCTL_DEF(HL_IOCTL_INFO, hl_info_ioctl_control)
पूर्ण;

अटल दीर्घ _hl_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		स्थिर काष्ठा hl_ioctl_desc *ioctl, काष्ठा device *dev)
अणु
	काष्ठा hl_fpriv *hpriv = filep->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	अचिन्हित पूर्णांक nr = _IOC_NR(cmd);
	अक्षर stack_kdata[128] = अणु0पूर्ण;
	अक्षर *kdata = शून्य;
	अचिन्हित पूर्णांक usize, asize;
	hl_ioctl_t *func;
	u32 hl_size;
	पूर्णांक retcode;

	अगर (hdev->hard_reset_pending) अणु
		dev_crit_ratelimited(dev,
			"Device HARD reset pending! Please close FD\n");
		वापस -ENODEV;
	पूर्ण

	/* Do not trust userspace, use our own definition */
	func = ioctl->func;

	अगर (unlikely(!func)) अणु
		dev_dbg(dev, "no function\n");
		retcode = -ENOTTY;
		जाओ out_err;
	पूर्ण

	hl_size = _IOC_SIZE(ioctl->cmd);
	usize = asize = _IOC_SIZE(cmd);
	अगर (hl_size > asize)
		asize = hl_size;

	cmd = ioctl->cmd;

	अगर (cmd & (IOC_IN | IOC_OUT)) अणु
		अगर (asize <= माप(stack_kdata)) अणु
			kdata = stack_kdata;
		पूर्ण अन्यथा अणु
			kdata = kzalloc(asize, GFP_KERNEL);
			अगर (!kdata) अणु
				retcode = -ENOMEM;
				जाओ out_err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cmd & IOC_IN) अणु
		अगर (copy_from_user(kdata, (व्योम __user *)arg, usize)) अणु
			retcode = -EFAULT;
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd & IOC_OUT) अणु
		स_रखो(kdata, 0, usize);
	पूर्ण

	retcode = func(hpriv, kdata);

	अगर ((cmd & IOC_OUT) && copy_to_user((व्योम __user *)arg, kdata, usize))
		retcode = -EFAULT;

out_err:
	अगर (retcode)
		dev_dbg(dev, "error in ioctl: pid=%d, cmd=0x%02x, nr=0x%02x\n",
			  task_pid_nr(current), cmd, nr);

	अगर (kdata != stack_kdata)
		kमुक्त(kdata);

	वापस retcode;
पूर्ण

दीर्घ hl_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hl_fpriv *hpriv = filep->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	स्थिर काष्ठा hl_ioctl_desc *ioctl = शून्य;
	अचिन्हित पूर्णांक nr = _IOC_NR(cmd);

	अगर (!hdev) अणु
		pr_err_ratelimited("Sending ioctl after device was removed! Please close FD\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((nr >= HL_COMMAND_START) && (nr < HL_COMMAND_END)) अणु
		ioctl = &hl_ioctls[nr];
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev, "invalid ioctl: pid=%d, nr=0x%02x\n",
			task_pid_nr(current), nr);
		वापस -ENOTTY;
	पूर्ण

	वापस _hl_ioctl(filep, cmd, arg, ioctl, hdev->dev);
पूर्ण

दीर्घ hl_ioctl_control(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hl_fpriv *hpriv = filep->निजी_data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	स्थिर काष्ठा hl_ioctl_desc *ioctl = शून्य;
	अचिन्हित पूर्णांक nr = _IOC_NR(cmd);

	अगर (!hdev) अणु
		pr_err_ratelimited("Sending ioctl after device was removed! Please close FD\n");
		वापस -ENODEV;
	पूर्ण

	अगर (nr == _IOC_NR(HL_IOCTL_INFO)) अणु
		ioctl = &hl_ioctls_control[nr];
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev_ctrl, "invalid ioctl: pid=%d, nr=0x%02x\n",
			task_pid_nr(current), nr);
		वापस -ENOTTY;
	पूर्ण

	वापस _hl_ioctl(filep, cmd, arg, ioctl, hdev->dev_ctrl);
पूर्ण
