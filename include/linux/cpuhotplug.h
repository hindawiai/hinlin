<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPUHOTPLUG_H
#घोषणा __CPUHOTPLUG_H

#समावेश <linux/types.h>

/*
 * CPU-up			CPU-करोwn
 *
 * BP		AP		BP		AP
 *
 * OFFLINE			OFFLINE
 *   |				  ^
 *   v				  |
 * BRINGUP_CPU->AP_OFFLINE	BRINGUP_CPU  <- AP_IDLE_DEAD (idle thपढ़ो/play_dead)
 *		  |				AP_OFFLINE
 *		  v (IRQ-off)	  ,---------------^
 *		AP_ONLNE	  | (stop_machine)
 *		  |		TEARDOWN_CPU <-	AP_ONLINE_IDLE
 *		  |				  ^
 *		  v				  |
 *              AP_ACTIVE			AP_ACTIVE
 */

क्रमागत cpuhp_state अणु
	CPUHP_INVALID = -1,
	CPUHP_OFFLINE = 0,
	CPUHP_CREATE_THREADS,
	CPUHP_PERF_PREPARE,
	CPUHP_PERF_X86_PREPARE,
	CPUHP_PERF_X86_AMD_UNCORE_PREP,
	CPUHP_PERF_POWER,
	CPUHP_PERF_SUPERH,
	CPUHP_X86_HPET_DEAD,
	CPUHP_X86_APB_DEAD,
	CPUHP_X86_MCE_DEAD,
	CPUHP_VIRT_NET_DEAD,
	CPUHP_SLUB_DEAD,
	CPUHP_DEBUG_OBJ_DEAD,
	CPUHP_MM_WRITEBACK_DEAD,
	CPUHP_MM_VMSTAT_DEAD,
	CPUHP_SOFTIRQ_DEAD,
	CPUHP_NET_MVNETA_DEAD,
	CPUHP_CPUIDLE_DEAD,
	CPUHP_ARM64_FPSIMD_DEAD,
	CPUHP_ARM_OMAP_WAKE_DEAD,
	CPUHP_IRQ_POLL_DEAD,
	CPUHP_BLOCK_SOFTIRQ_DEAD,
	CPUHP_ACPI_CPUDRV_DEAD,
	CPUHP_S390_PFAULT_DEAD,
	CPUHP_BLK_MQ_DEAD,
	CPUHP_FS_BUFF_DEAD,
	CPUHP_PRINTK_DEAD,
	CPUHP_MM_MEMCQ_DEAD,
	CPUHP_PERCPU_CNT_DEAD,
	CPUHP_RADIX_DEAD,
	CPUHP_PAGE_ALLOC_DEAD,
	CPUHP_NET_DEV_DEAD,
	CPUHP_PCI_XGENE_DEAD,
	CPUHP_IOMMU_IOVA_DEAD,
	CPUHP_LUSTRE_CFS_DEAD,
	CPUHP_AP_ARM_CACHE_B15_RAC_DEAD,
	CPUHP_PADATA_DEAD,
	CPUHP_WORKQUEUE_PREP,
	CPUHP_POWER_NUMA_PREPARE,
	CPUHP_HRTIMERS_PREPARE,
	CPUHP_PROखाता_PREPARE,
	CPUHP_X2APIC_PREPARE,
	CPUHP_SMPCFD_PREPARE,
	CPUHP_RELAY_PREPARE,
	CPUHP_SLAB_PREPARE,
	CPUHP_MD_RAID5_PREPARE,
	CPUHP_RCUTREE_PREP,
	CPUHP_CPUIDLE_COUPLED_PREPARE,
	CPUHP_POWERPC_PMAC_PREPARE,
	CPUHP_POWERPC_MMU_CTX_PREPARE,
	CPUHP_XEN_PREPARE,
	CPUHP_XEN_EVTCHN_PREPARE,
	CPUHP_ARM_SHMOBILE_SCU_PREPARE,
	CPUHP_SH_SH3X_PREPARE,
	CPUHP_NET_FLOW_PREPARE,
	CPUHP_TOPOLOGY_PREPARE,
	CPUHP_NET_IUCV_PREPARE,
	CPUHP_ARM_BL_PREPARE,
	CPUHP_TRACE_RB_PREPARE,
	CPUHP_MM_ZS_PREPARE,
	CPUHP_MM_ZSWP_MEM_PREPARE,
	CPUHP_MM_ZSWP_POOL_PREPARE,
	CPUHP_KVM_PPC_BOOK3S_PREPARE,
	CPUHP_ZCOMP_PREPARE,
	CPUHP_TIMERS_PREPARE,
	CPUHP_MIPS_SOC_PREPARE,
	CPUHP_BP_PREPARE_DYN,
	CPUHP_BP_PREPARE_DYN_END		= CPUHP_BP_PREPARE_DYN + 20,
	CPUHP_BRINGUP_CPU,
	CPUHP_AP_IDLE_DEAD,
	CPUHP_AP_OFFLINE,
	CPUHP_AP_SCHED_STARTING,
	CPUHP_AP_RCUTREE_DYING,
	CPUHP_AP_CPU_PM_STARTING,
	CPUHP_AP_IRQ_GIC_STARTING,
	CPUHP_AP_IRQ_HIP04_STARTING,
	CPUHP_AP_IRQ_APPLE_AIC_STARTING,
	CPUHP_AP_IRQ_ARMADA_XP_STARTING,
	CPUHP_AP_IRQ_BCM2836_STARTING,
	CPUHP_AP_IRQ_MIPS_GIC_STARTING,
	CPUHP_AP_IRQ_RISCV_STARTING,
	CPUHP_AP_IRQ_SIFIVE_PLIC_STARTING,
	CPUHP_AP_ARM_MVEBU_COHERENCY,
	CPUHP_AP_MICROCODE_LOADER,
	CPUHP_AP_PERF_X86_AMD_UNCORE_STARTING,
	CPUHP_AP_PERF_X86_STARTING,
	CPUHP_AP_PERF_X86_AMD_IBS_STARTING,
	CPUHP_AP_PERF_X86_CQM_STARTING,
	CPUHP_AP_PERF_X86_CSTATE_STARTING,
	CPUHP_AP_PERF_XTENSA_STARTING,
	CPUHP_AP_MIPS_OP_LOONGSON3_STARTING,
	CPUHP_AP_ARM_SDEI_STARTING,
	CPUHP_AP_ARM_VFP_STARTING,
	CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING,
	CPUHP_AP_PERF_ARM_HW_BREAKPOINT_STARTING,
	CPUHP_AP_PERF_ARM_ACPI_STARTING,
	CPUHP_AP_PERF_ARM_STARTING,
	CPUHP_AP_ARM_L2X0_STARTING,
	CPUHP_AP_EXYNOS4_MCT_TIMER_STARTING,
	CPUHP_AP_ARM_ARCH_TIMER_STARTING,
	CPUHP_AP_ARM_GLOBAL_TIMER_STARTING,
	CPUHP_AP_JCORE_TIMER_STARTING,
	CPUHP_AP_ARM_TWD_STARTING,
	CPUHP_AP_QCOM_TIMER_STARTING,
	CPUHP_AP_TEGRA_TIMER_STARTING,
	CPUHP_AP_ARMADA_TIMER_STARTING,
	CPUHP_AP_MARCO_TIMER_STARTING,
	CPUHP_AP_MIPS_GIC_TIMER_STARTING,
	CPUHP_AP_ARC_TIMER_STARTING,
	CPUHP_AP_RISCV_TIMER_STARTING,
	CPUHP_AP_CLINT_TIMER_STARTING,
	CPUHP_AP_CSKY_TIMER_STARTING,
	CPUHP_AP_TI_GP_TIMER_STARTING,
	CPUHP_AP_HYPERV_TIMER_STARTING,
	CPUHP_AP_KVM_STARTING,
	CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING,
	CPUHP_AP_KVM_ARM_VGIC_STARTING,
	CPUHP_AP_KVM_ARM_TIMER_STARTING,
	/* Must be the last समयr callback */
	CPUHP_AP_DUMMY_TIMER_STARTING,
	CPUHP_AP_ARM_XEN_STARTING,
	CPUHP_AP_ARM_CORESIGHT_STARTING,
	CPUHP_AP_ARM_CORESIGHT_CTI_STARTING,
	CPUHP_AP_ARM64_ISNDEP_STARTING,
	CPUHP_AP_SMPCFD_DYING,
	CPUHP_AP_X86_TBOOT_DYING,
	CPUHP_AP_ARM_CACHE_B15_RAC_DYING,
	CPUHP_AP_ONLINE,
	CPUHP_TEARDOWN_CPU,
	CPUHP_AP_ONLINE_IDLE,
	CPUHP_AP_SCHED_WAIT_EMPTY,
	CPUHP_AP_SMPBOOT_THREADS,
	CPUHP_AP_X86_VDSO_VMA_ONLINE,
	CPUHP_AP_IRQ_AFFINITY_ONLINE,
	CPUHP_AP_BLK_MQ_ONLINE,
	CPUHP_AP_ARM_MVEBU_SYNC_CLOCKS,
	CPUHP_AP_X86_INTEL_EPB_ONLINE,
	CPUHP_AP_PERF_ONLINE,
	CPUHP_AP_PERF_X86_ONLINE,
	CPUHP_AP_PERF_X86_UNCORE_ONLINE,
	CPUHP_AP_PERF_X86_AMD_UNCORE_ONLINE,
	CPUHP_AP_PERF_X86_AMD_POWER_ONLINE,
	CPUHP_AP_PERF_X86_RAPL_ONLINE,
	CPUHP_AP_PERF_X86_CQM_ONLINE,
	CPUHP_AP_PERF_X86_CSTATE_ONLINE,
	CPUHP_AP_PERF_X86_IDXD_ONLINE,
	CPUHP_AP_PERF_S390_CF_ONLINE,
	CPUHP_AP_PERF_S390_CFD_ONLINE,
	CPUHP_AP_PERF_S390_SF_ONLINE,
	CPUHP_AP_PERF_ARM_CCI_ONLINE,
	CPUHP_AP_PERF_ARM_CCN_ONLINE,
	CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE,
	CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE,
	CPUHP_AP_PERF_ARM_HISI_L3_ONLINE,
	CPUHP_AP_PERF_ARM_HISI_PA_ONLINE,
	CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE,
	CPUHP_AP_PERF_ARM_L2X0_ONLINE,
	CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
	CPUHP_AP_PERF_ARM_QCOM_L3_ONLINE,
	CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
	CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE,
	CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE,
	CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE,
	CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE,
	CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE,
	CPUHP_AP_PERF_POWERPC_HV_24x7_ONLINE,
	CPUHP_AP_PERF_POWERPC_HV_GPCI_ONLINE,
	CPUHP_AP_PERF_CSKY_ONLINE,
	CPUHP_AP_WATCHDOG_ONLINE,
	CPUHP_AP_WORKQUEUE_ONLINE,
	CPUHP_AP_RCUTREE_ONLINE,
	CPUHP_AP_BASE_CACHEINFO_ONLINE,
	CPUHP_AP_ONLINE_DYN,
	CPUHP_AP_ONLINE_DYN_END		= CPUHP_AP_ONLINE_DYN + 30,
	CPUHP_AP_X86_HPET_ONLINE,
	CPUHP_AP_X86_KVM_CLK_ONLINE,
	CPUHP_AP_DTPM_CPU_ONLINE,
	CPUHP_AP_ACTIVE,
	CPUHP_ONLINE,
पूर्ण;

पूर्णांक __cpuhp_setup_state(क्रमागत cpuhp_state state,	स्थिर अक्षर *name, bool invoke,
			पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
			पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu), bool multi_instance);

पूर्णांक __cpuhp_setup_state_cpuslocked(क्रमागत cpuhp_state state, स्थिर अक्षर *name,
				   bool invoke,
				   पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
				   पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu),
				   bool multi_instance);
/**
 * cpuhp_setup_state - Setup hotplug state callbacks with calling the callbacks
 * @state:	The state क्रम which the calls are installed
 * @name:	Name of the callback (will be used in debug output)
 * @startup:	startup callback function
 * @tearकरोwn:	tearकरोwn callback function
 *
 * Installs the callback functions and invokes the startup callback on
 * the present cpus which have alपढ़ोy reached the @state.
 */
अटल अंतरभूत पूर्णांक cpuhp_setup_state(क्रमागत cpuhp_state state,
				    स्थिर अक्षर *name,
				    पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
				    पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu))
अणु
	वापस __cpuhp_setup_state(state, name, true, startup, tearकरोwn, false);
पूर्ण

अटल अंतरभूत पूर्णांक cpuhp_setup_state_cpuslocked(क्रमागत cpuhp_state state,
					       स्थिर अक्षर *name,
					       पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
					       पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu))
अणु
	वापस __cpuhp_setup_state_cpuslocked(state, name, true, startup,
					      tearकरोwn, false);
पूर्ण

/**
 * cpuhp_setup_state_nocalls - Setup hotplug state callbacks without calling the
 *			       callbacks
 * @state:	The state क्रम which the calls are installed
 * @name:	Name of the callback.
 * @startup:	startup callback function
 * @tearकरोwn:	tearकरोwn callback function
 *
 * Same as @cpuhp_setup_state except that no calls are executed are invoked
 * during installation of this callback. NOP अगर SMP=n or HOTPLUG_CPU=n.
 */
अटल अंतरभूत पूर्णांक cpuhp_setup_state_nocalls(क्रमागत cpuhp_state state,
					    स्थिर अक्षर *name,
					    पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
					    पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu))
अणु
	वापस __cpuhp_setup_state(state, name, false, startup, tearकरोwn,
				   false);
पूर्ण

अटल अंतरभूत पूर्णांक cpuhp_setup_state_nocalls_cpuslocked(क्रमागत cpuhp_state state,
						     स्थिर अक्षर *name,
						     पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
						     पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu))
अणु
	वापस __cpuhp_setup_state_cpuslocked(state, name, false, startup,
					    tearकरोwn, false);
पूर्ण

/**
 * cpuhp_setup_state_multi - Add callbacks क्रम multi state
 * @state:	The state क्रम which the calls are installed
 * @name:	Name of the callback.
 * @startup:	startup callback function
 * @tearकरोwn:	tearकरोwn callback function
 *
 * Sets the पूर्णांकernal multi_instance flag and prepares a state to work as a multi
 * instance callback. No callbacks are invoked at this poपूर्णांक. The callbacks are
 * invoked once an instance क्रम this state are रेजिस्टरed via
 * @cpuhp_state_add_instance or @cpuhp_state_add_instance_nocalls.
 */
अटल अंतरभूत पूर्णांक cpuhp_setup_state_multi(क्रमागत cpuhp_state state,
					  स्थिर अक्षर *name,
					  पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu,
							 काष्ठा hlist_node *node),
					  पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu,
							  काष्ठा hlist_node *node))
अणु
	वापस __cpuhp_setup_state(state, name, false,
				   (व्योम *) startup,
				   (व्योम *) tearकरोwn, true);
पूर्ण

पूर्णांक __cpuhp_state_add_instance(क्रमागत cpuhp_state state, काष्ठा hlist_node *node,
			       bool invoke);
पूर्णांक __cpuhp_state_add_instance_cpuslocked(क्रमागत cpuhp_state state,
					  काष्ठा hlist_node *node, bool invoke);

/**
 * cpuhp_state_add_instance - Add an instance क्रम a state and invoke startup
 *                            callback.
 * @state:	The state क्रम which the instance is installed
 * @node:	The node क्रम this inभागidual state.
 *
 * Installs the instance क्रम the @state and invokes the startup callback on
 * the present cpus which have alपढ़ोy reached the @state. The @state must have
 * been earlier marked as multi-instance by @cpuhp_setup_state_multi.
 */
अटल अंतरभूत पूर्णांक cpuhp_state_add_instance(क्रमागत cpuhp_state state,
					   काष्ठा hlist_node *node)
अणु
	वापस __cpuhp_state_add_instance(state, node, true);
पूर्ण

/**
 * cpuhp_state_add_instance_nocalls - Add an instance क्रम a state without
 *                                    invoking the startup callback.
 * @state:	The state क्रम which the instance is installed
 * @node:	The node क्रम this inभागidual state.
 *
 * Installs the instance क्रम the @state The @state must have been earlier
 * marked as multi-instance by @cpuhp_setup_state_multi.
 */
अटल अंतरभूत पूर्णांक cpuhp_state_add_instance_nocalls(क्रमागत cpuhp_state state,
						   काष्ठा hlist_node *node)
अणु
	वापस __cpuhp_state_add_instance(state, node, false);
पूर्ण

अटल अंतरभूत पूर्णांक
cpuhp_state_add_instance_nocalls_cpuslocked(क्रमागत cpuhp_state state,
					    काष्ठा hlist_node *node)
अणु
	वापस __cpuhp_state_add_instance_cpuslocked(state, node, false);
पूर्ण

व्योम __cpuhp_हटाओ_state(क्रमागत cpuhp_state state, bool invoke);
व्योम __cpuhp_हटाओ_state_cpuslocked(क्रमागत cpuhp_state state, bool invoke);

/**
 * cpuhp_हटाओ_state - Remove hotplug state callbacks and invoke the tearकरोwn
 * @state:	The state क्रम which the calls are हटाओd
 *
 * Removes the callback functions and invokes the tearकरोwn callback on
 * the present cpus which have alपढ़ोy reached the @state.
 */
अटल अंतरभूत व्योम cpuhp_हटाओ_state(क्रमागत cpuhp_state state)
अणु
	__cpuhp_हटाओ_state(state, true);
पूर्ण

/**
 * cpuhp_हटाओ_state_nocalls - Remove hotplug state callbacks without invoking
 *				tearकरोwn
 * @state:	The state क्रम which the calls are हटाओd
 */
अटल अंतरभूत व्योम cpuhp_हटाओ_state_nocalls(क्रमागत cpuhp_state state)
अणु
	__cpuhp_हटाओ_state(state, false);
पूर्ण

अटल अंतरभूत व्योम cpuhp_हटाओ_state_nocalls_cpuslocked(क्रमागत cpuhp_state state)
अणु
	__cpuhp_हटाओ_state_cpuslocked(state, false);
पूर्ण

/**
 * cpuhp_हटाओ_multi_state - Remove hotplug multi state callback
 * @state:	The state क्रम which the calls are हटाओd
 *
 * Removes the callback functions from a multi state. This is the reverse of
 * cpuhp_setup_state_multi(). All instances should have been हटाओd beक्रमe
 * invoking this function.
 */
अटल अंतरभूत व्योम cpuhp_हटाओ_multi_state(क्रमागत cpuhp_state state)
अणु
	__cpuhp_हटाओ_state(state, false);
पूर्ण

पूर्णांक __cpuhp_state_हटाओ_instance(क्रमागत cpuhp_state state,
				  काष्ठा hlist_node *node, bool invoke);

/**
 * cpuhp_state_हटाओ_instance - Remove hotplug instance from state and invoke
 *                               the tearकरोwn callback
 * @state:	The state from which the instance is हटाओd
 * @node:	The node क्रम this inभागidual state.
 *
 * Removes the instance and invokes the tearकरोwn callback on the present cpus
 * which have alपढ़ोy reached the @state.
 */
अटल अंतरभूत पूर्णांक cpuhp_state_हटाओ_instance(क्रमागत cpuhp_state state,
					      काष्ठा hlist_node *node)
अणु
	वापस __cpuhp_state_हटाओ_instance(state, node, true);
पूर्ण

/**
 * cpuhp_state_हटाओ_instance_nocalls - Remove hotplug instance from state
 *					 without invoking the reatकरोwn callback
 * @state:	The state from which the instance is हटाओd
 * @node:	The node क्रम this inभागidual state.
 *
 * Removes the instance without invoking the tearकरोwn callback.
 */
अटल अंतरभूत पूर्णांक cpuhp_state_हटाओ_instance_nocalls(क्रमागत cpuhp_state state,
						      काष्ठा hlist_node *node)
अणु
	वापस __cpuhp_state_हटाओ_instance(state, node, false);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम cpuhp_online_idle(क्रमागत cpuhp_state state);
#अन्यथा
अटल अंतरभूत व्योम cpuhp_online_idle(क्रमागत cpuhp_state state) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
