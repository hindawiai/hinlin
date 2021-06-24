<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/percpu.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/opal-api.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#अगर_घोषित CONFIG_TRACEPOINTS
/*
 * Since the tracing code might execute OPAL calls we need to guard against
 * recursion.
 */
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, opal_trace_depth);

अटल व्योम __trace_opal_entry(s64 a0, s64 a1, s64 a2, s64 a3,
			       s64 a4, s64 a5, s64 a6, s64 a7,
			       अचिन्हित दीर्घ opcode)
अणु
	अचिन्हित पूर्णांक *depth;
	अचिन्हित दीर्घ args[8];

	depth = this_cpu_ptr(&opal_trace_depth);

	अगर (*depth)
		वापस;

	args[0] = a0;
	args[1] = a1;
	args[2] = a2;
	args[3] = a3;
	args[4] = a4;
	args[5] = a5;
	args[6] = a6;
	args[7] = a7;

	(*depth)++;
	trace_opal_entry(opcode, &args[0]);
	(*depth)--;
पूर्ण

अटल व्योम __trace_opal_निकास(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ retval)
अणु
	अचिन्हित पूर्णांक *depth;

	depth = this_cpu_ptr(&opal_trace_depth);

	अगर (*depth)
		वापस;

	(*depth)++;
	trace_opal_निकास(opcode, retval);
	(*depth)--;
पूर्ण

अटल DEFINE_STATIC_KEY_FALSE(opal_tracepoपूर्णांक_key);

पूर्णांक opal_tracepoपूर्णांक_regfunc(व्योम)
अणु
	अटल_branch_inc(&opal_tracepoपूर्णांक_key);
	वापस 0;
पूर्ण

व्योम opal_tracepoपूर्णांक_unregfunc(व्योम)
अणु
	अटल_branch_dec(&opal_tracepoपूर्णांक_key);
पूर्ण

अटल s64 __opal_call_trace(s64 a0, s64 a1, s64 a2, s64 a3,
			     s64 a4, s64 a5, s64 a6, s64 a7,
			      अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ msr)
अणु
	s64 ret;

	__trace_opal_entry(a0, a1, a2, a3, a4, a5, a6, a7, opcode);
	ret = __opal_call(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msr);
	__trace_opal_निकास(opcode, ret);

	वापस ret;
पूर्ण

#घोषणा DO_TRACE (अटल_branch_unlikely(&opal_tracepoपूर्णांक_key))

#अन्यथा /* CONFIG_TRACEPOINTS */

अटल s64 __opal_call_trace(s64 a0, s64 a1, s64 a2, s64 a3,
			     s64 a4, s64 a5, s64 a6, s64 a7,
			      अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ msr)
अणु
	वापस 0;
पूर्ण

#घोषणा DO_TRACE false
#पूर्ण_अगर /* CONFIG_TRACEPOINTS */

अटल पूर्णांक64_t opal_call(पूर्णांक64_t a0, पूर्णांक64_t a1, पूर्णांक64_t a2, पूर्णांक64_t a3,
	     पूर्णांक64_t a4, पूर्णांक64_t a5, पूर्णांक64_t a6, पूर्णांक64_t a7, पूर्णांक64_t opcode)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ msr = mfmsr();
	bool mmu = (msr & (MSR_IR|MSR_DR));
	पूर्णांक64_t ret;

	msr &= ~MSR_EE;

	अगर (unlikely(!mmu))
		वापस __opal_call(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msr);

	local_save_flags(flags);
	hard_irq_disable();

	अगर (DO_TRACE) अणु
		ret = __opal_call_trace(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msr);
	पूर्ण अन्यथा अणु
		ret = __opal_call(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msr);
	पूर्ण

	local_irq_restore(flags);

	वापस ret;
पूर्ण

#घोषणा OPAL_CALL(name, opcode)					\
पूर्णांक64_t name(पूर्णांक64_t a0, पूर्णांक64_t a1, पूर्णांक64_t a2, पूर्णांक64_t a3,	\
	     पूर्णांक64_t a4, पूर्णांक64_t a5, पूर्णांक64_t a6, पूर्णांक64_t a7);	\
पूर्णांक64_t name(पूर्णांक64_t a0, पूर्णांक64_t a1, पूर्णांक64_t a2, पूर्णांक64_t a3,	\
	     पूर्णांक64_t a4, पूर्णांक64_t a5, पूर्णांक64_t a6, पूर्णांक64_t a7)	\
अणु								\
	वापस opal_call(a0, a1, a2, a3, a4, a5, a6, a7, opcode); \
पूर्ण

OPAL_CALL(opal_invalid_call,			OPAL_INVALID_CALL);
OPAL_CALL(opal_console_ग_लिखो,			OPAL_CONSOLE_WRITE);
OPAL_CALL(opal_console_पढ़ो,			OPAL_CONSOLE_READ);
OPAL_CALL(opal_console_ग_लिखो_buffer_space,	OPAL_CONSOLE_WRITE_BUFFER_SPACE);
OPAL_CALL(opal_rtc_पढ़ो,			OPAL_RTC_READ);
OPAL_CALL(opal_rtc_ग_लिखो,			OPAL_RTC_WRITE);
OPAL_CALL(opal_cec_घातer_करोwn,			OPAL_CEC_POWER_DOWN);
OPAL_CALL(opal_cec_reboot,			OPAL_CEC_REBOOT);
OPAL_CALL(opal_cec_reboot2,			OPAL_CEC_REBOOT2);
OPAL_CALL(opal_पढ़ो_nvram,			OPAL_READ_NVRAM);
OPAL_CALL(opal_ग_लिखो_nvram,			OPAL_WRITE_NVRAM);
OPAL_CALL(opal_handle_पूर्णांकerrupt,		OPAL_HANDLE_INTERRUPT);
OPAL_CALL(opal_poll_events,			OPAL_POLL_EVENTS);
OPAL_CALL(opal_pci_set_hub_tce_memory,		OPAL_PCI_SET_HUB_TCE_MEMORY);
OPAL_CALL(opal_pci_set_phb_tce_memory,		OPAL_PCI_SET_PHB_TCE_MEMORY);
OPAL_CALL(opal_pci_config_पढ़ो_byte,		OPAL_PCI_CONFIG_READ_BYTE);
OPAL_CALL(opal_pci_config_पढ़ो_half_word,	OPAL_PCI_CONFIG_READ_HALF_WORD);
OPAL_CALL(opal_pci_config_पढ़ो_word,		OPAL_PCI_CONFIG_READ_WORD);
OPAL_CALL(opal_pci_config_ग_लिखो_byte,		OPAL_PCI_CONFIG_WRITE_BYTE);
OPAL_CALL(opal_pci_config_ग_लिखो_half_word,	OPAL_PCI_CONFIG_WRITE_HALF_WORD);
OPAL_CALL(opal_pci_config_ग_लिखो_word,		OPAL_PCI_CONFIG_WRITE_WORD);
OPAL_CALL(opal_set_xive,			OPAL_SET_XIVE);
OPAL_CALL(opal_get_xive,			OPAL_GET_XIVE);
OPAL_CALL(opal_रेजिस्टर_exception_handler,	OPAL_REGISTER_OPAL_EXCEPTION_HANDLER);
OPAL_CALL(opal_pci_eeh_मुक्तze_status,		OPAL_PCI_EEH_FREEZE_STATUS);
OPAL_CALL(opal_pci_eeh_मुक्तze_clear,		OPAL_PCI_EEH_FREEZE_CLEAR);
OPAL_CALL(opal_pci_eeh_मुक्तze_set,		OPAL_PCI_EEH_FREEZE_SET);
OPAL_CALL(opal_pci_err_inject,			OPAL_PCI_ERR_INJECT);
OPAL_CALL(opal_pci_shpc,			OPAL_PCI_SHPC);
OPAL_CALL(opal_pci_phb_mmio_enable,		OPAL_PCI_PHB_MMIO_ENABLE);
OPAL_CALL(opal_pci_set_phb_mem_winकरोw,		OPAL_PCI_SET_PHB_MEM_WINDOW);
OPAL_CALL(opal_pci_map_pe_mmio_winकरोw,		OPAL_PCI_MAP_PE_MMIO_WINDOW);
OPAL_CALL(opal_pci_set_phb_table_memory,	OPAL_PCI_SET_PHB_TABLE_MEMORY);
OPAL_CALL(opal_pci_set_pe,			OPAL_PCI_SET_PE);
OPAL_CALL(opal_pci_set_peltv,			OPAL_PCI_SET_PELTV);
OPAL_CALL(opal_pci_set_mve,			OPAL_PCI_SET_MVE);
OPAL_CALL(opal_pci_set_mve_enable,		OPAL_PCI_SET_MVE_ENABLE);
OPAL_CALL(opal_pci_get_xive_reissue,		OPAL_PCI_GET_XIVE_REISSUE);
OPAL_CALL(opal_pci_set_xive_reissue,		OPAL_PCI_SET_XIVE_REISSUE);
OPAL_CALL(opal_pci_set_xive_pe,			OPAL_PCI_SET_XIVE_PE);
OPAL_CALL(opal_get_xive_source,			OPAL_GET_XIVE_SOURCE);
OPAL_CALL(opal_get_msi_32,			OPAL_GET_MSI_32);
OPAL_CALL(opal_get_msi_64,			OPAL_GET_MSI_64);
OPAL_CALL(opal_start_cpu,			OPAL_START_CPU);
OPAL_CALL(opal_query_cpu_status,		OPAL_QUERY_CPU_STATUS);
OPAL_CALL(opal_ग_लिखो_oppanel,			OPAL_WRITE_OPPANEL);
OPAL_CALL(opal_pci_map_pe_dma_winकरोw,		OPAL_PCI_MAP_PE_DMA_WINDOW);
OPAL_CALL(opal_pci_map_pe_dma_winकरोw_real,	OPAL_PCI_MAP_PE_DMA_WINDOW_REAL);
OPAL_CALL(opal_pci_reset,			OPAL_PCI_RESET);
OPAL_CALL(opal_pci_get_hub_diag_data,		OPAL_PCI_GET_HUB_DIAG_DATA);
OPAL_CALL(opal_pci_get_phb_diag_data,		OPAL_PCI_GET_PHB_DIAG_DATA);
OPAL_CALL(opal_pci_fence_phb,			OPAL_PCI_FENCE_PHB);
OPAL_CALL(opal_pci_reinit,			OPAL_PCI_REINIT);
OPAL_CALL(opal_pci_mask_pe_error,		OPAL_PCI_MASK_PE_ERROR);
OPAL_CALL(opal_set_slot_led_status,		OPAL_SET_SLOT_LED_STATUS);
OPAL_CALL(opal_get_eघात_status,			OPAL_GET_EPOW_STATUS);
OPAL_CALL(opal_get_dpo_status,			OPAL_GET_DPO_STATUS);
OPAL_CALL(opal_set_प्रणाली_attention_led,	OPAL_SET_SYSTEM_ATTENTION_LED);
OPAL_CALL(opal_pci_next_error,			OPAL_PCI_NEXT_ERROR);
OPAL_CALL(opal_pci_poll,			OPAL_PCI_POLL);
OPAL_CALL(opal_pci_msi_eoi,			OPAL_PCI_MSI_EOI);
OPAL_CALL(opal_pci_get_phb_diag_data2,		OPAL_PCI_GET_PHB_DIAG_DATA2);
OPAL_CALL(opal_xscom_पढ़ो,			OPAL_XSCOM_READ);
OPAL_CALL(opal_xscom_ग_लिखो,			OPAL_XSCOM_WRITE);
OPAL_CALL(opal_lpc_पढ़ो,			OPAL_LPC_READ);
OPAL_CALL(opal_lpc_ग_लिखो,			OPAL_LPC_WRITE);
OPAL_CALL(opal_वापस_cpu,			OPAL_RETURN_CPU);
OPAL_CALL(opal_reinit_cpus,			OPAL_REINIT_CPUS);
OPAL_CALL(opal_पढ़ो_elog,			OPAL_ELOG_READ);
OPAL_CALL(opal_send_ack_elog,			OPAL_ELOG_ACK);
OPAL_CALL(opal_get_elog_size,			OPAL_ELOG_SIZE);
OPAL_CALL(opal_resend_pending_logs,		OPAL_ELOG_RESEND);
OPAL_CALL(opal_ग_लिखो_elog,			OPAL_ELOG_WRITE);
OPAL_CALL(opal_validate_flash,			OPAL_FLASH_VALIDATE);
OPAL_CALL(opal_manage_flash,			OPAL_FLASH_MANAGE);
OPAL_CALL(opal_update_flash,			OPAL_FLASH_UPDATE);
OPAL_CALL(opal_resync_समयbase,			OPAL_RESYNC_TIMEBASE);
OPAL_CALL(opal_check_token,			OPAL_CHECK_TOKEN);
OPAL_CALL(opal_dump_init,			OPAL_DUMP_INIT);
OPAL_CALL(opal_dump_info,			OPAL_DUMP_INFO);
OPAL_CALL(opal_dump_info2,			OPAL_DUMP_INFO2);
OPAL_CALL(opal_dump_पढ़ो,			OPAL_DUMP_READ);
OPAL_CALL(opal_dump_ack,			OPAL_DUMP_ACK);
OPAL_CALL(opal_get_msg,				OPAL_GET_MSG);
OPAL_CALL(opal_ग_लिखो_oppanel_async,		OPAL_WRITE_OPPANEL_ASYNC);
OPAL_CALL(opal_check_completion,		OPAL_CHECK_ASYNC_COMPLETION);
OPAL_CALL(opal_dump_resend_notअगरication,	OPAL_DUMP_RESEND);
OPAL_CALL(opal_sync_host_reboot,		OPAL_SYNC_HOST_REBOOT);
OPAL_CALL(opal_sensor_पढ़ो,			OPAL_SENSOR_READ);
OPAL_CALL(opal_get_param,			OPAL_GET_PARAM);
OPAL_CALL(opal_set_param,			OPAL_SET_PARAM);
OPAL_CALL(opal_handle_hmi,			OPAL_HANDLE_HMI);
OPAL_CALL(opal_handle_hmi2,			OPAL_HANDLE_HMI2);
OPAL_CALL(opal_config_cpu_idle_state,		OPAL_CONFIG_CPU_IDLE_STATE);
OPAL_CALL(opal_slw_set_reg,			OPAL_SLW_SET_REG);
OPAL_CALL(opal_रेजिस्टर_dump_region,		OPAL_REGISTER_DUMP_REGION);
OPAL_CALL(opal_unरेजिस्टर_dump_region,		OPAL_UNREGISTER_DUMP_REGION);
OPAL_CALL(opal_pci_set_phb_cxl_mode,		OPAL_PCI_SET_PHB_CAPI_MODE);
OPAL_CALL(opal_tpo_ग_लिखो,			OPAL_WRITE_TPO);
OPAL_CALL(opal_tpo_पढ़ो,			OPAL_READ_TPO);
OPAL_CALL(opal_ipmi_send,			OPAL_IPMI_SEND);
OPAL_CALL(opal_ipmi_recv,			OPAL_IPMI_RECV);
OPAL_CALL(opal_i2c_request,			OPAL_I2C_REQUEST);
OPAL_CALL(opal_flash_पढ़ो,			OPAL_FLASH_READ);
OPAL_CALL(opal_flash_ग_लिखो,			OPAL_FLASH_WRITE);
OPAL_CALL(opal_flash_erase,			OPAL_FLASH_ERASE);
OPAL_CALL(opal_prd_msg,				OPAL_PRD_MSG);
OPAL_CALL(opal_leds_get_ind,			OPAL_LEDS_GET_INDICATOR);
OPAL_CALL(opal_leds_set_ind,			OPAL_LEDS_SET_INDICATOR);
OPAL_CALL(opal_console_flush,			OPAL_CONSOLE_FLUSH);
OPAL_CALL(opal_get_device_tree,			OPAL_GET_DEVICE_TREE);
OPAL_CALL(opal_pci_get_presence_state,		OPAL_PCI_GET_PRESENCE_STATE);
OPAL_CALL(opal_pci_get_घातer_state,		OPAL_PCI_GET_POWER_STATE);
OPAL_CALL(opal_pci_set_घातer_state,		OPAL_PCI_SET_POWER_STATE);
OPAL_CALL(opal_पूर्णांक_get_xirr,			OPAL_INT_GET_XIRR);
OPAL_CALL(opal_पूर्णांक_set_cppr,			OPAL_INT_SET_CPPR);
OPAL_CALL(opal_पूर्णांक_eoi,				OPAL_INT_EOI);
OPAL_CALL(opal_पूर्णांक_set_mfrr,			OPAL_INT_SET_MFRR);
OPAL_CALL(opal_pci_tce_समाप्त,			OPAL_PCI_TCE_KILL);
OPAL_CALL(opal_nmmu_set_ptcr,			OPAL_NMMU_SET_PTCR);
OPAL_CALL(opal_xive_reset,			OPAL_XIVE_RESET);
OPAL_CALL(opal_xive_get_irq_info,		OPAL_XIVE_GET_IRQ_INFO);
OPAL_CALL(opal_xive_get_irq_config,		OPAL_XIVE_GET_IRQ_CONFIG);
OPAL_CALL(opal_xive_set_irq_config,		OPAL_XIVE_SET_IRQ_CONFIG);
OPAL_CALL(opal_xive_get_queue_info,		OPAL_XIVE_GET_QUEUE_INFO);
OPAL_CALL(opal_xive_set_queue_info,		OPAL_XIVE_SET_QUEUE_INFO);
OPAL_CALL(opal_xive_करोnate_page,		OPAL_XIVE_DONATE_PAGE);
OPAL_CALL(opal_xive_alloc_vp_block,		OPAL_XIVE_ALLOCATE_VP_BLOCK);
OPAL_CALL(opal_xive_मुक्त_vp_block,		OPAL_XIVE_FREE_VP_BLOCK);
OPAL_CALL(opal_xive_allocate_irq_raw,		OPAL_XIVE_ALLOCATE_IRQ);
OPAL_CALL(opal_xive_मुक्त_irq,			OPAL_XIVE_FREE_IRQ);
OPAL_CALL(opal_xive_get_vp_info,		OPAL_XIVE_GET_VP_INFO);
OPAL_CALL(opal_xive_set_vp_info,		OPAL_XIVE_SET_VP_INFO);
OPAL_CALL(opal_xive_sync,			OPAL_XIVE_SYNC);
OPAL_CALL(opal_xive_dump,			OPAL_XIVE_DUMP);
OPAL_CALL(opal_xive_get_queue_state,		OPAL_XIVE_GET_QUEUE_STATE);
OPAL_CALL(opal_xive_set_queue_state,		OPAL_XIVE_SET_QUEUE_STATE);
OPAL_CALL(opal_xive_get_vp_state,		OPAL_XIVE_GET_VP_STATE);
OPAL_CALL(opal_संकेत_प्रणाली_reset,		OPAL_SIGNAL_SYSTEM_RESET);
OPAL_CALL(opal_npu_map_lpar,			OPAL_NPU_MAP_LPAR);
OPAL_CALL(opal_imc_counters_init,		OPAL_IMC_COUNTERS_INIT);
OPAL_CALL(opal_imc_counters_start,		OPAL_IMC_COUNTERS_START);
OPAL_CALL(opal_imc_counters_stop,		OPAL_IMC_COUNTERS_STOP);
OPAL_CALL(opal_get_घातercap,			OPAL_GET_POWERCAP);
OPAL_CALL(opal_set_घातercap,			OPAL_SET_POWERCAP);
OPAL_CALL(opal_get_घातer_shअगरt_ratio,		OPAL_GET_POWER_SHIFT_RATIO);
OPAL_CALL(opal_set_घातer_shअगरt_ratio,		OPAL_SET_POWER_SHIFT_RATIO);
OPAL_CALL(opal_sensor_group_clear,		OPAL_SENSOR_GROUP_CLEAR);
OPAL_CALL(opal_quiesce,				OPAL_QUIESCE);
OPAL_CALL(opal_npu_spa_setup,			OPAL_NPU_SPA_SETUP);
OPAL_CALL(opal_npu_spa_clear_cache,		OPAL_NPU_SPA_CLEAR_CACHE);
OPAL_CALL(opal_npu_tl_set,			OPAL_NPU_TL_SET);
OPAL_CALL(opal_pci_get_pbcq_tunnel_bar,		OPAL_PCI_GET_PBCQ_TUNNEL_BAR);
OPAL_CALL(opal_pci_set_pbcq_tunnel_bar,		OPAL_PCI_SET_PBCQ_TUNNEL_BAR);
OPAL_CALL(opal_sensor_पढ़ो_u64,			OPAL_SENSOR_READ_U64);
OPAL_CALL(opal_sensor_group_enable,		OPAL_SENSOR_GROUP_ENABLE);
OPAL_CALL(opal_nx_coproc_init,			OPAL_NX_COPROC_INIT);
OPAL_CALL(opal_mpipl_update,			OPAL_MPIPL_UPDATE);
OPAL_CALL(opal_mpipl_रेजिस्टर_tag,		OPAL_MPIPL_REGISTER_TAG);
OPAL_CALL(opal_mpipl_query_tag,			OPAL_MPIPL_QUERY_TAG);
OPAL_CALL(opal_secvar_get,			OPAL_SECVAR_GET);
OPAL_CALL(opal_secvar_get_next,			OPAL_SECVAR_GET_NEXT);
OPAL_CALL(opal_secvar_enqueue_update,		OPAL_SECVAR_ENQUEUE_UPDATE);
