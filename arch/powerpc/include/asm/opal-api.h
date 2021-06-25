<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OPAL API definitions.
 *
 * Copyright 2011-2015 IBM Corp.
 */

#अगर_अघोषित __OPAL_API_H
#घोषणा __OPAL_API_H

/****** OPAL APIs ******/

/* Return codes */
#घोषणा OPAL_SUCCESS		0
#घोषणा OPAL_PARAMETER		-1
#घोषणा OPAL_BUSY		-2
#घोषणा OPAL_PARTIAL		-3
#घोषणा OPAL_CONSTRAINED	-4
#घोषणा OPAL_CLOSED		-5
#घोषणा OPAL_HARDWARE		-6
#घोषणा OPAL_UNSUPPORTED	-7
#घोषणा OPAL_PERMISSION		-8
#घोषणा OPAL_NO_MEM		-9
#घोषणा OPAL_RESOURCE		-10
#घोषणा OPAL_INTERNAL_ERROR	-11
#घोषणा OPAL_BUSY_EVENT		-12
#घोषणा OPAL_HARDWARE_FROZEN	-13
#घोषणा OPAL_WRONG_STATE	-14
#घोषणा OPAL_ASYNC_COMPLETION	-15
#घोषणा OPAL_EMPTY		-16
#घोषणा OPAL_I2C_TIMEOUT	-17
#घोषणा OPAL_I2C_INVALID_CMD	-18
#घोषणा OPAL_I2C_LBUS_PARITY	-19
#घोषणा OPAL_I2C_BKEND_OVERRUN	-20
#घोषणा OPAL_I2C_BKEND_ACCESS	-21
#घोषणा OPAL_I2C_ARBT_LOST	-22
#घोषणा OPAL_I2C_NACK_RCVD	-23
#घोषणा OPAL_I2C_STOP_ERR	-24
#घोषणा OPAL_XIVE_PROVISIONING	-31
#घोषणा OPAL_XIVE_FREE_ACTIVE	-32
#घोषणा OPAL_TIMEOUT		-33

/* API Tokens (in r0) */
#घोषणा OPAL_INVALID_CALL		       -1
#घोषणा OPAL_TEST				0
#घोषणा OPAL_CONSOLE_WRITE			1
#घोषणा OPAL_CONSOLE_READ			2
#घोषणा OPAL_RTC_READ				3
#घोषणा OPAL_RTC_WRITE				4
#घोषणा OPAL_CEC_POWER_DOWN			5
#घोषणा OPAL_CEC_REBOOT				6
#घोषणा OPAL_READ_NVRAM				7
#घोषणा OPAL_WRITE_NVRAM			8
#घोषणा OPAL_HANDLE_INTERRUPT			9
#घोषणा OPAL_POLL_EVENTS			10
#घोषणा OPAL_PCI_SET_HUB_TCE_MEMORY		11
#घोषणा OPAL_PCI_SET_PHB_TCE_MEMORY		12
#घोषणा OPAL_PCI_CONFIG_READ_BYTE		13
#घोषणा OPAL_PCI_CONFIG_READ_HALF_WORD  	14
#घोषणा OPAL_PCI_CONFIG_READ_WORD		15
#घोषणा OPAL_PCI_CONFIG_WRITE_BYTE		16
#घोषणा OPAL_PCI_CONFIG_WRITE_HALF_WORD		17
#घोषणा OPAL_PCI_CONFIG_WRITE_WORD		18
#घोषणा OPAL_SET_XIVE				19
#घोषणा OPAL_GET_XIVE				20
#घोषणा OPAL_GET_COMPLETION_TOKEN_STATUS	21 /* obsolete */
#घोषणा OPAL_REGISTER_OPAL_EXCEPTION_HANDLER	22
#घोषणा OPAL_PCI_EEH_FREEZE_STATUS		23
#घोषणा OPAL_PCI_SHPC				24
#घोषणा OPAL_CONSOLE_WRITE_BUFFER_SPACE		25
#घोषणा OPAL_PCI_EEH_FREEZE_CLEAR		26
#घोषणा OPAL_PCI_PHB_MMIO_ENABLE		27
#घोषणा OPAL_PCI_SET_PHB_MEM_WINDOW		28
#घोषणा OPAL_PCI_MAP_PE_MMIO_WINDOW		29
#घोषणा OPAL_PCI_SET_PHB_TABLE_MEMORY		30
#घोषणा OPAL_PCI_SET_PE				31
#घोषणा OPAL_PCI_SET_PELTV			32
#घोषणा OPAL_PCI_SET_MVE			33
#घोषणा OPAL_PCI_SET_MVE_ENABLE			34
#घोषणा OPAL_PCI_GET_XIVE_REISSUE		35
#घोषणा OPAL_PCI_SET_XIVE_REISSUE		36
#घोषणा OPAL_PCI_SET_XIVE_PE			37
#घोषणा OPAL_GET_XIVE_SOURCE			38
#घोषणा OPAL_GET_MSI_32				39
#घोषणा OPAL_GET_MSI_64				40
#घोषणा OPAL_START_CPU				41
#घोषणा OPAL_QUERY_CPU_STATUS			42
#घोषणा OPAL_WRITE_OPPANEL			43 /* unimplemented */
#घोषणा OPAL_PCI_MAP_PE_DMA_WINDOW		44
#घोषणा OPAL_PCI_MAP_PE_DMA_WINDOW_REAL		45
#घोषणा OPAL_PCI_RESET				49
#घोषणा OPAL_PCI_GET_HUB_DIAG_DATA		50
#घोषणा OPAL_PCI_GET_PHB_DIAG_DATA		51
#घोषणा OPAL_PCI_FENCE_PHB			52
#घोषणा OPAL_PCI_REINIT				53
#घोषणा OPAL_PCI_MASK_PE_ERROR			54
#घोषणा OPAL_SET_SLOT_LED_STATUS		55
#घोषणा OPAL_GET_EPOW_STATUS			56
#घोषणा OPAL_SET_SYSTEM_ATTENTION_LED		57
#घोषणा OPAL_RESERVED1				58
#घोषणा OPAL_RESERVED2				59
#घोषणा OPAL_PCI_NEXT_ERROR			60
#घोषणा OPAL_PCI_EEH_FREEZE_STATUS2		61
#घोषणा OPAL_PCI_POLL				62
#घोषणा OPAL_PCI_MSI_EOI			63
#घोषणा OPAL_PCI_GET_PHB_DIAG_DATA2		64
#घोषणा OPAL_XSCOM_READ				65
#घोषणा OPAL_XSCOM_WRITE			66
#घोषणा OPAL_LPC_READ				67
#घोषणा OPAL_LPC_WRITE				68
#घोषणा OPAL_RETURN_CPU				69
#घोषणा OPAL_REINIT_CPUS			70
#घोषणा OPAL_ELOG_READ				71
#घोषणा OPAL_ELOG_WRITE				72
#घोषणा OPAL_ELOG_ACK				73
#घोषणा OPAL_ELOG_RESEND			74
#घोषणा OPAL_ELOG_SIZE				75
#घोषणा OPAL_FLASH_VALIDATE			76
#घोषणा OPAL_FLASH_MANAGE			77
#घोषणा OPAL_FLASH_UPDATE			78
#घोषणा OPAL_RESYNC_TIMEBASE			79
#घोषणा OPAL_CHECK_TOKEN			80
#घोषणा OPAL_DUMP_INIT				81
#घोषणा OPAL_DUMP_INFO				82
#घोषणा OPAL_DUMP_READ				83
#घोषणा OPAL_DUMP_ACK				84
#घोषणा OPAL_GET_MSG				85
#घोषणा OPAL_CHECK_ASYNC_COMPLETION		86
#घोषणा OPAL_SYNC_HOST_REBOOT			87
#घोषणा OPAL_SENSOR_READ			88
#घोषणा OPAL_GET_PARAM				89
#घोषणा OPAL_SET_PARAM				90
#घोषणा OPAL_DUMP_RESEND			91
#घोषणा OPAL_ELOG_SEND				92	/* Deprecated */
#घोषणा OPAL_PCI_SET_PHB_CAPI_MODE		93
#घोषणा OPAL_DUMP_INFO2				94
#घोषणा OPAL_WRITE_OPPANEL_ASYNC		95
#घोषणा OPAL_PCI_ERR_INJECT			96
#घोषणा OPAL_PCI_EEH_FREEZE_SET			97
#घोषणा OPAL_HANDLE_HMI				98
#घोषणा OPAL_CONFIG_CPU_IDLE_STATE		99
#घोषणा OPAL_SLW_SET_REG			100
#घोषणा OPAL_REGISTER_DUMP_REGION		101
#घोषणा OPAL_UNREGISTER_DUMP_REGION		102
#घोषणा OPAL_WRITE_TPO				103
#घोषणा OPAL_READ_TPO				104
#घोषणा OPAL_GET_DPO_STATUS			105
#घोषणा OPAL_OLD_I2C_REQUEST			106	/* Deprecated */
#घोषणा OPAL_IPMI_SEND				107
#घोषणा OPAL_IPMI_RECV				108
#घोषणा OPAL_I2C_REQUEST			109
#घोषणा OPAL_FLASH_READ				110
#घोषणा OPAL_FLASH_WRITE			111
#घोषणा OPAL_FLASH_ERASE			112
#घोषणा OPAL_PRD_MSG				113
#घोषणा OPAL_LEDS_GET_INDICATOR			114
#घोषणा OPAL_LEDS_SET_INDICATOR			115
#घोषणा OPAL_CEC_REBOOT2			116
#घोषणा OPAL_CONSOLE_FLUSH			117
#घोषणा OPAL_GET_DEVICE_TREE			118
#घोषणा OPAL_PCI_GET_PRESENCE_STATE		119
#घोषणा OPAL_PCI_GET_POWER_STATE		120
#घोषणा OPAL_PCI_SET_POWER_STATE		121
#घोषणा OPAL_INT_GET_XIRR			122
#घोषणा	OPAL_INT_SET_CPPR			123
#घोषणा OPAL_INT_EOI				124
#घोषणा OPAL_INT_SET_MFRR			125
#घोषणा OPAL_PCI_TCE_KILL			126
#घोषणा OPAL_NMMU_SET_PTCR			127
#घोषणा OPAL_XIVE_RESET				128
#घोषणा OPAL_XIVE_GET_IRQ_INFO			129
#घोषणा OPAL_XIVE_GET_IRQ_CONFIG		130
#घोषणा OPAL_XIVE_SET_IRQ_CONFIG		131
#घोषणा OPAL_XIVE_GET_QUEUE_INFO		132
#घोषणा OPAL_XIVE_SET_QUEUE_INFO		133
#घोषणा OPAL_XIVE_DONATE_PAGE			134
#घोषणा OPAL_XIVE_ALLOCATE_VP_BLOCK		135
#घोषणा OPAL_XIVE_FREE_VP_BLOCK			136
#घोषणा OPAL_XIVE_GET_VP_INFO			137
#घोषणा OPAL_XIVE_SET_VP_INFO			138
#घोषणा OPAL_XIVE_ALLOCATE_IRQ			139
#घोषणा OPAL_XIVE_FREE_IRQ			140
#घोषणा OPAL_XIVE_SYNC				141
#घोषणा OPAL_XIVE_DUMP				142
#घोषणा OPAL_XIVE_GET_QUEUE_STATE		143
#घोषणा OPAL_XIVE_SET_QUEUE_STATE		144
#घोषणा OPAL_SIGNAL_SYSTEM_RESET		145
#घोषणा OPAL_NPU_INIT_CONTEXT			146
#घोषणा OPAL_NPU_DESTROY_CONTEXT		147
#घोषणा OPAL_NPU_MAP_LPAR			148
#घोषणा OPAL_IMC_COUNTERS_INIT			149
#घोषणा OPAL_IMC_COUNTERS_START			150
#घोषणा OPAL_IMC_COUNTERS_STOP			151
#घोषणा OPAL_GET_POWERCAP			152
#घोषणा OPAL_SET_POWERCAP			153
#घोषणा OPAL_GET_POWER_SHIFT_RATIO		154
#घोषणा OPAL_SET_POWER_SHIFT_RATIO		155
#घोषणा OPAL_SENSOR_GROUP_CLEAR			156
#घोषणा OPAL_PCI_SET_P2P			157
#घोषणा OPAL_QUIESCE				158
#घोषणा OPAL_NPU_SPA_SETUP			159
#घोषणा OPAL_NPU_SPA_CLEAR_CACHE		160
#घोषणा OPAL_NPU_TL_SET				161
#घोषणा OPAL_SENSOR_READ_U64			162
#घोषणा OPAL_SENSOR_GROUP_ENABLE		163
#घोषणा OPAL_PCI_GET_PBCQ_TUNNEL_BAR		164
#घोषणा OPAL_PCI_SET_PBCQ_TUNNEL_BAR		165
#घोषणा OPAL_HANDLE_HMI2			166
#घोषणा	OPAL_NX_COPROC_INIT			167
#घोषणा OPAL_XIVE_GET_VP_STATE			170
#घोषणा OPAL_MPIPL_UPDATE			173
#घोषणा OPAL_MPIPL_REGISTER_TAG			174
#घोषणा OPAL_MPIPL_QUERY_TAG			175
#घोषणा OPAL_SECVAR_GET				176
#घोषणा OPAL_SECVAR_GET_NEXT			177
#घोषणा OPAL_SECVAR_ENQUEUE_UPDATE		178
#घोषणा OPAL_LAST				178

#घोषणा QUIESCE_HOLD			1 /* Spin all calls at entry */
#घोषणा QUIESCE_REJECT			2 /* Fail all calls with OPAL_BUSY */
#घोषणा QUIESCE_LOCK_BREAK		3 /* Set to ignore locks. */
#घोषणा QUIESCE_RESUME			4 /* Un-quiesce */
#घोषणा QUIESCE_RESUME_FAST_REBOOT	5 /* Un-quiesce, fast reboot */

/* Device tree flags */

/*
 * Flags set in घातer-mgmt nodes in device tree describing
 * idle states that are supported in the platक्रमm.
 */

#घोषणा OPAL_PM_TIMEBASE_STOP		0x00000002
#घोषणा OPAL_PM_LOSE_HYP_CONTEXT	0x00002000
#घोषणा OPAL_PM_LOSE_FULL_CONTEXT	0x00004000
#घोषणा OPAL_PM_NAP_ENABLED		0x00010000
#घोषणा OPAL_PM_SLEEP_ENABLED		0x00020000
#घोषणा OPAL_PM_WINKLE_ENABLED		0x00040000
#घोषणा OPAL_PM_SLEEP_ENABLED_ER1	0x00080000 /* with workaround */
#घोषणा OPAL_PM_STOP_INST_FAST		0x00100000
#घोषणा OPAL_PM_STOP_INST_DEEP		0x00200000

/*
 * OPAL_CONFIG_CPU_IDLE_STATE parameters
 */
#घोषणा OPAL_CONFIG_IDLE_FASTSLEEP	1
#घोषणा OPAL_CONFIG_IDLE_UNDO		0
#घोषणा OPAL_CONFIG_IDLE_APPLY		1

#अगर_अघोषित __ASSEMBLY__

/* Other क्रमागतs */
क्रमागत OpalFreezeState अणु
	OPAL_EEH_STOPPED_NOT_FROZEN = 0,
	OPAL_EEH_STOPPED_MMIO_FREEZE = 1,
	OPAL_EEH_STOPPED_DMA_FREEZE = 2,
	OPAL_EEH_STOPPED_MMIO_DMA_FREEZE = 3,
	OPAL_EEH_STOPPED_RESET = 4,
	OPAL_EEH_STOPPED_TEMP_UNAVAIL = 5,
	OPAL_EEH_STOPPED_PERM_UNAVAIL = 6
पूर्ण;

क्रमागत OpalEehFreezeActionToken अणु
	OPAL_EEH_ACTION_CLEAR_FREEZE_MMIO = 1,
	OPAL_EEH_ACTION_CLEAR_FREEZE_DMA = 2,
	OPAL_EEH_ACTION_CLEAR_FREEZE_ALL = 3,

	OPAL_EEH_ACTION_SET_FREEZE_MMIO = 1,
	OPAL_EEH_ACTION_SET_FREEZE_DMA  = 2,
	OPAL_EEH_ACTION_SET_FREEZE_ALL  = 3
पूर्ण;

क्रमागत OpalPciStatusToken अणु
	OPAL_EEH_NO_ERROR	= 0,
	OPAL_EEH_IOC_ERROR	= 1,
	OPAL_EEH_PHB_ERROR	= 2,
	OPAL_EEH_PE_ERROR	= 3,
	OPAL_EEH_PE_MMIO_ERROR	= 4,
	OPAL_EEH_PE_DMA_ERROR	= 5
पूर्ण;

क्रमागत OpalPciErrorSeverity अणु
	OPAL_EEH_SEV_NO_ERROR	= 0,
	OPAL_EEH_SEV_IOC_DEAD	= 1,
	OPAL_EEH_SEV_PHB_DEAD	= 2,
	OPAL_EEH_SEV_PHB_FENCED	= 3,
	OPAL_EEH_SEV_PE_ER	= 4,
	OPAL_EEH_SEV_INF	= 5
पूर्ण;

क्रमागत OpalErrinjectType अणु
	OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR	= 0,
	OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR64	= 1,
पूर्ण;

क्रमागत OpalErrinjectFunc अणु
	/* IOA bus specअगरic errors */
	OPAL_ERR_INJECT_FUNC_IOA_LD_MEM_ADDR	= 0,
	OPAL_ERR_INJECT_FUNC_IOA_LD_MEM_DATA	= 1,
	OPAL_ERR_INJECT_FUNC_IOA_LD_IO_ADDR	= 2,
	OPAL_ERR_INJECT_FUNC_IOA_LD_IO_DATA	= 3,
	OPAL_ERR_INJECT_FUNC_IOA_LD_CFG_ADDR	= 4,
	OPAL_ERR_INJECT_FUNC_IOA_LD_CFG_DATA	= 5,
	OPAL_ERR_INJECT_FUNC_IOA_ST_MEM_ADDR	= 6,
	OPAL_ERR_INJECT_FUNC_IOA_ST_MEM_DATA	= 7,
	OPAL_ERR_INJECT_FUNC_IOA_ST_IO_ADDR	= 8,
	OPAL_ERR_INJECT_FUNC_IOA_ST_IO_DATA	= 9,
	OPAL_ERR_INJECT_FUNC_IOA_ST_CFG_ADDR	= 10,
	OPAL_ERR_INJECT_FUNC_IOA_ST_CFG_DATA	= 11,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_ADDR	= 12,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_DATA	= 13,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_MASTER	= 14,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_TARGET	= 15,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_ADDR	= 16,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_DATA	= 17,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_MASTER	= 18,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_TARGET	= 19,
पूर्ण;

क्रमागत OpalMmioWinकरोwType अणु
	OPAL_M32_WINDOW_TYPE = 1,
	OPAL_M64_WINDOW_TYPE = 2,
	OPAL_IO_WINDOW_TYPE  = 3
पूर्ण;

क्रमागत OpalExceptionHandler अणु
	OPAL_MACHINE_CHECK_HANDLER	    = 1,
	OPAL_HYPERVISOR_MAINTEन_अंकCE_HANDLER = 2,
	OPAL_SOFTPATCH_HANDLER		    = 3
पूर्ण;

क्रमागत OpalPendingState अणु
	OPAL_EVENT_OPAL_INTERNAL   = 0x1,
	OPAL_EVENT_NVRAM	   = 0x2,
	OPAL_EVENT_RTC		   = 0x4,
	OPAL_EVENT_CONSOLE_OUTPUT  = 0x8,
	OPAL_EVENT_CONSOLE_INPUT   = 0x10,
	OPAL_EVENT_ERROR_LOG_AVAIL = 0x20,
	OPAL_EVENT_ERROR_LOG	   = 0x40,
	OPAL_EVENT_EPOW		   = 0x80,
	OPAL_EVENT_LED_STATUS	   = 0x100,
	OPAL_EVENT_PCI_ERROR	   = 0x200,
	OPAL_EVENT_DUMP_AVAIL	   = 0x400,
	OPAL_EVENT_MSG_PENDING	   = 0x800,
पूर्ण;

क्रमागत OpalThपढ़ोStatus अणु
	OPAL_THREAD_INACTIVE = 0x0,
	OPAL_THREAD_STARTED = 0x1,
	OPAL_THREAD_UNAVAILABLE = 0x2 /* opal-v3 */
पूर्ण;

क्रमागत OpalPciBusCompare अणु
	OpalPciBusAny	= 0,	/* Any bus number match */
	OpalPciBus3Bits	= 2,	/* Match top 3 bits of bus number */
	OpalPciBus4Bits	= 3,	/* Match top 4 bits of bus number */
	OpalPciBus5Bits	= 4,	/* Match top 5 bits of bus number */
	OpalPciBus6Bits	= 5,	/* Match top 6 bits of bus number */
	OpalPciBus7Bits	= 6,	/* Match top 7 bits of bus number */
	OpalPciBusAll	= 7,	/* Match bus number exactly */
पूर्ण;

क्रमागत OpalDeviceCompare अणु
	OPAL_IGNORE_RID_DEVICE_NUMBER = 0,
	OPAL_COMPARE_RID_DEVICE_NUMBER = 1
पूर्ण;

क्रमागत OpalFuncCompare अणु
	OPAL_IGNORE_RID_FUNCTION_NUMBER = 0,
	OPAL_COMPARE_RID_FUNCTION_NUMBER = 1
पूर्ण;

क्रमागत OpalPeAction अणु
	OPAL_UNMAP_PE = 0,
	OPAL_MAP_PE = 1
पूर्ण;

क्रमागत OpalPeltvAction अणु
	OPAL_REMOVE_PE_FROM_DOMAIN = 0,
	OPAL_ADD_PE_TO_DOMAIN = 1
पूर्ण;

क्रमागत OpalMveEnableAction अणु
	OPAL_DISABLE_MVE = 0,
	OPAL_ENABLE_MVE = 1
पूर्ण;

क्रमागत OpalM64Action अणु
	OPAL_DISABLE_M64 = 0,
	OPAL_ENABLE_M64_SPLIT = 1,
	OPAL_ENABLE_M64_NON_SPLIT = 2
पूर्ण;

क्रमागत OpalPciResetScope अणु
	OPAL_RESET_PHB_COMPLETE		= 1,
	OPAL_RESET_PCI_LINK		= 2,
	OPAL_RESET_PHB_ERROR		= 3,
	OPAL_RESET_PCI_HOT		= 4,
	OPAL_RESET_PCI_FUNDAMENTAL	= 5,
	OPAL_RESET_PCI_IODA_TABLE	= 6
पूर्ण;

क्रमागत OpalPciReinitScope अणु
	/*
	 * Note: we chose values that करो not overlap
	 * OpalPciResetScope as OPAL v2 used the same
	 * क्रमागत क्रम both
	 */
	OPAL_REINIT_PCI_DEV = 1000
पूर्ण;

क्रमागत OpalPciResetState अणु
	OPAL_DEASSERT_RESET = 0,
	OPAL_ASSERT_RESET   = 1
पूर्ण;

क्रमागत OpalPciSlotPresence अणु
	OPAL_PCI_SLOT_EMPTY	= 0,
	OPAL_PCI_SLOT_PRESENT	= 1
पूर्ण;

क्रमागत OpalPciSlotPower अणु
	OPAL_PCI_SLOT_POWER_OFF	= 0,
	OPAL_PCI_SLOT_POWER_ON	= 1,
	OPAL_PCI_SLOT_OFFLINE	= 2,
	OPAL_PCI_SLOT_ONLINE	= 3
पूर्ण;

क्रमागत OpalSlotLedType अणु
	OPAL_SLOT_LED_TYPE_ID = 0,	/* IDENTIFY LED */
	OPAL_SLOT_LED_TYPE_FAULT = 1,	/* FAULT LED */
	OPAL_SLOT_LED_TYPE_ATTN = 2,	/* System Attention LED */
	OPAL_SLOT_LED_TYPE_MAX = 3
पूर्ण;

क्रमागत OpalSlotLedState अणु
	OPAL_SLOT_LED_STATE_OFF = 0,	/* LED is OFF */
	OPAL_SLOT_LED_STATE_ON = 1	/* LED is ON */
पूर्ण;

/*
 * Address cycle types क्रम LPC accesses. These also correspond
 * to the content of the first cell of the "reg" property क्रम
 * device nodes on the LPC bus
 */
क्रमागत OpalLPCAddressType अणु
	OPAL_LPC_MEM	= 0,
	OPAL_LPC_IO	= 1,
	OPAL_LPC_FW	= 2,
पूर्ण;

क्रमागत opal_msg_type अणु
	OPAL_MSG_ASYNC_COMP	= 0,	/* params[0] = token, params[1] = rc,
					 * additional params function-specअगरic
					 */
	OPAL_MSG_MEM_ERR	= 1,
	OPAL_MSG_EPOW		= 2,
	OPAL_MSG_SHUTDOWN	= 3,	/* params[0] = 1 reboot, 0 shutकरोwn */
	OPAL_MSG_HMI_EVT	= 4,
	OPAL_MSG_DPO		= 5,
	OPAL_MSG_PRD		= 6,
	OPAL_MSG_OCC		= 7,
	OPAL_MSG_PRD2		= 8,
	OPAL_MSG_TYPE_MAX,
पूर्ण;

काष्ठा opal_msg अणु
	__be32 msg_type;
	__be32 reserved;
	__be64 params[8];
पूर्ण;

/* System parameter permission */
क्रमागत OpalSysparamPerm अणु
	OPAL_SYSPARAM_READ  = 0x1,
	OPAL_SYSPARAM_WRITE = 0x2,
	OPAL_SYSPARAM_RW    = (OPAL_SYSPARAM_READ | OPAL_SYSPARAM_WRITE),
पूर्ण;

क्रमागत अणु
	OPAL_IPMI_MSG_FORMAT_VERSION_1 = 1,
पूर्ण;

काष्ठा opal_ipmi_msg अणु
	uपूर्णांक8_t version;
	uपूर्णांक8_t netfn;
	uपूर्णांक8_t cmd;
	uपूर्णांक8_t data[];
पूर्ण;

/* FSP memory errors handling */
क्रमागत OpalMemErr_Version अणु
	OpalMemErr_V1 = 1,
पूर्ण;

क्रमागत OpalMemErrType अणु
	OPAL_MEM_ERR_TYPE_RESILIENCE	= 0,
	OPAL_MEM_ERR_TYPE_DYN_DALLOC,
पूर्ण;

/* Memory Reilience error type */
क्रमागत OpalMemErr_ResilErrType अणु
	OPAL_MEM_RESILIENCE_CE		= 0,
	OPAL_MEM_RESILIENCE_UE,
	OPAL_MEM_RESILIENCE_UE_SCRUB,
पूर्ण;

/* Dynamic Memory Deallocation type */
क्रमागत OpalMemErr_DynErrType अणु
	OPAL_MEM_DYNAMIC_DEALLOC	= 0,
पूर्ण;

काष्ठा OpalMemoryErrorData अणु
	क्रमागत OpalMemErr_Version	version:8;	/* 0x00 */
	क्रमागत OpalMemErrType	type:8;		/* 0x01 */
	__be16			flags;		/* 0x02 */
	uपूर्णांक8_t			reserved_1[4];	/* 0x04 */

	जोड़ अणु
		/* Memory Resilience corrected/uncorrected error info */
		काष्ठा अणु
			क्रमागत OpalMemErr_ResilErrType	resil_err_type:8;
			uपूर्णांक8_t				reserved_1[7];
			__be64				physical_address_start;
			__be64				physical_address_end;
		पूर्ण resilience;
		/* Dynamic memory deallocation error info */
		काष्ठा अणु
			क्रमागत OpalMemErr_DynErrType	dyn_err_type:8;
			uपूर्णांक8_t				reserved_1[7];
			__be64				physical_address_start;
			__be64				physical_address_end;
		पूर्ण dyn_dealloc;
	पूर्ण u;
पूर्ण;

/* HMI पूर्णांकerrupt event */
क्रमागत OpalHMI_Version अणु
	OpalHMIEvt_V1 = 1,
	OpalHMIEvt_V2 = 2,
पूर्ण;

क्रमागत OpalHMI_Severity अणु
	OpalHMI_SEV_NO_ERROR = 0,
	OpalHMI_SEV_WARNING = 1,
	OpalHMI_SEV_ERROR_SYNC = 2,
	OpalHMI_SEV_FATAL = 3,
पूर्ण;

क्रमागत OpalHMI_Disposition अणु
	OpalHMI_DISPOSITION_RECOVERED = 0,
	OpalHMI_DISPOSITION_NOT_RECOVERED = 1,
पूर्ण;

क्रमागत OpalHMI_ErrType अणु
	OpalHMI_ERROR_MALFUNC_ALERT	= 0,
	OpalHMI_ERROR_PROC_RECOV_DONE,
	OpalHMI_ERROR_PROC_RECOV_DONE_AGAIN,
	OpalHMI_ERROR_PROC_RECOV_MASKED,
	OpalHMI_ERROR_TFAC,
	OpalHMI_ERROR_TFMR_PARITY,
	OpalHMI_ERROR_HA_OVERFLOW_WARN,
	OpalHMI_ERROR_XSCOM_FAIL,
	OpalHMI_ERROR_XSCOM_DONE,
	OpalHMI_ERROR_SCOM_FIR,
	OpalHMI_ERROR_DEBUG_TRIG_FIR,
	OpalHMI_ERROR_HYP_RESOURCE,
	OpalHMI_ERROR_CAPP_RECOVERY,
पूर्ण;

क्रमागत OpalHMI_XstopType अणु
	CHECKSTOP_TYPE_UNKNOWN	=	0,
	CHECKSTOP_TYPE_CORE	=	1,
	CHECKSTOP_TYPE_NX	=	2,
	CHECKSTOP_TYPE_NPU	=	3
पूर्ण;

क्रमागत OpalHMI_CoreXstopReason अणु
	CORE_CHECKSTOP_IFU_REGखाता		= 0x00000001,
	CORE_CHECKSTOP_IFU_LOGIC		= 0x00000002,
	CORE_CHECKSTOP_PC_DURING_RECOV		= 0x00000004,
	CORE_CHECKSTOP_ISU_REGखाता		= 0x00000008,
	CORE_CHECKSTOP_ISU_LOGIC		= 0x00000010,
	CORE_CHECKSTOP_FXU_LOGIC		= 0x00000020,
	CORE_CHECKSTOP_VSU_LOGIC		= 0x00000040,
	CORE_CHECKSTOP_PC_RECOV_IN_MAINT_MODE	= 0x00000080,
	CORE_CHECKSTOP_LSU_REGखाता		= 0x00000100,
	CORE_CHECKSTOP_PC_FWD_PROGRESS		= 0x00000200,
	CORE_CHECKSTOP_LSU_LOGIC		= 0x00000400,
	CORE_CHECKSTOP_PC_LOGIC			= 0x00000800,
	CORE_CHECKSTOP_PC_HYP_RESOURCE		= 0x00001000,
	CORE_CHECKSTOP_PC_HANG_RECOV_FAILED	= 0x00002000,
	CORE_CHECKSTOP_PC_AMBI_HANG_DETECTED	= 0x00004000,
	CORE_CHECKSTOP_PC_DEBUG_TRIG_ERR_INJ	= 0x00008000,
	CORE_CHECKSTOP_PC_SPRD_HYP_ERR_INJ	= 0x00010000,
पूर्ण;

क्रमागत OpalHMI_NestAccelXstopReason अणु
	NX_CHECKSTOP_SHM_INVAL_STATE_ERR	= 0x00000001,
	NX_CHECKSTOP_DMA_INVAL_STATE_ERR_1	= 0x00000002,
	NX_CHECKSTOP_DMA_INVAL_STATE_ERR_2	= 0x00000004,
	NX_CHECKSTOP_DMA_CH0_INVAL_STATE_ERR	= 0x00000008,
	NX_CHECKSTOP_DMA_CH1_INVAL_STATE_ERR	= 0x00000010,
	NX_CHECKSTOP_DMA_CH2_INVAL_STATE_ERR	= 0x00000020,
	NX_CHECKSTOP_DMA_CH3_INVAL_STATE_ERR	= 0x00000040,
	NX_CHECKSTOP_DMA_CH4_INVAL_STATE_ERR	= 0x00000080,
	NX_CHECKSTOP_DMA_CH5_INVAL_STATE_ERR	= 0x00000100,
	NX_CHECKSTOP_DMA_CH6_INVAL_STATE_ERR	= 0x00000200,
	NX_CHECKSTOP_DMA_CH7_INVAL_STATE_ERR	= 0x00000400,
	NX_CHECKSTOP_DMA_CRB_UE			= 0x00000800,
	NX_CHECKSTOP_DMA_CRB_SUE		= 0x00001000,
	NX_CHECKSTOP_PBI_ISN_UE			= 0x00002000,
पूर्ण;

काष्ठा OpalHMIEvent अणु
	uपूर्णांक8_t		version;	/* 0x00 */
	uपूर्णांक8_t		severity;	/* 0x01 */
	uपूर्णांक8_t		type;		/* 0x02 */
	uपूर्णांक8_t		disposition;	/* 0x03 */
	uपूर्णांक8_t		reserved_1[4];	/* 0x04 */

	__be64		hmer;
	/* TFMR रेजिस्टर. Valid only क्रम TFAC and TFMR_PARITY error type. */
	__be64		tfmr;

	/* version 2 and later */
	जोड़ अणु
		/*
		 * checkstop info (Core/NX).
		 * Valid क्रम OpalHMI_ERROR_MALFUNC_ALERT.
		 */
		काष्ठा अणु
			uपूर्णांक8_t	xstop_type;	/* क्रमागत OpalHMI_XstopType */
			uपूर्णांक8_t reserved_1[3];
			__be32  xstop_reason;
			जोड़ अणु
				__be32 pir;	/* क्रम CHECKSTOP_TYPE_CORE */
				__be32 chip_id;	/* क्रम CHECKSTOP_TYPE_NX */
			पूर्ण u;
		पूर्ण xstop_error;
	पूर्ण u;
पूर्ण;

/* OPAL_HANDLE_HMI2 out_flags */
क्रमागत अणु
	OPAL_HMI_FLAGS_TB_RESYNC	= (1ull << 0), /* Timebase has been resynced */
	OPAL_HMI_FLAGS_DEC_LOST		= (1ull << 1), /* DEC lost, needs to be reprogrammed */
	OPAL_HMI_FLAGS_HDEC_LOST	= (1ull << 2), /* HDEC lost, needs to be reprogrammed */
	OPAL_HMI_FLAGS_TOD_TB_FAIL	= (1ull << 3), /* TOD/TB recovery failed. */
	OPAL_HMI_FLAGS_NEW_EVENT	= (1ull << 63), /* An event has been created */
पूर्ण;

क्रमागत अणु
	OPAL_P7IOC_DIAG_TYPE_NONE	= 0,
	OPAL_P7IOC_DIAG_TYPE_RGC	= 1,
	OPAL_P7IOC_DIAG_TYPE_BI		= 2,
	OPAL_P7IOC_DIAG_TYPE_CI		= 3,
	OPAL_P7IOC_DIAG_TYPE_MISC	= 4,
	OPAL_P7IOC_DIAG_TYPE_I2C	= 5,
	OPAL_P7IOC_DIAG_TYPE_LAST	= 6
पूर्ण;

काष्ठा OpalIoP7IOCErrorData अणु
	__be16 type;

	/* GEM */
	__be64 gemXfir;
	__be64 gemRfir;
	__be64 gemRirqfir;
	__be64 gemMask;
	__be64 gemRwof;

	/* LEM */
	__be64 lemFir;
	__be64 lemErrMask;
	__be64 lemAction0;
	__be64 lemAction1;
	__be64 lemWof;

	जोड़ अणु
		काष्ठा OpalIoP7IOCRgcErrorData अणु
			__be64 rgcStatus;	/* 3E1C10 */
			__be64 rgcLdcp;		/* 3E1C18 */
		पूर्णrgc;
		काष्ठा OpalIoP7IOCBiErrorData अणु
			__be64 biLdcp0;		/* 3C0100, 3C0118 */
			__be64 biLdcp1;		/* 3C0108, 3C0120 */
			__be64 biLdcp2;		/* 3C0110, 3C0128 */
			__be64 biFenceStatus;	/* 3C0130, 3C0130 */

			uपूर्णांक8_t biDownbound;	/* BI Downbound or Upbound */
		पूर्णbi;
		काष्ठा OpalIoP7IOCCiErrorData अणु
			__be64 ciPortStatus;	/* 3Dn008 */
			__be64 ciPortLdcp;	/* 3Dn010 */

			uपूर्णांक8_t ciPort;		/* Index of CI port: 0/1 */
		पूर्णci;
	पूर्ण;
पूर्ण;

/**
 * This काष्ठाure defines the overlay which will be used to store PHB error
 * data upon request.
 */
क्रमागत अणु
	OPAL_PHB_ERROR_DATA_VERSION_1 = 1,
पूर्ण;

क्रमागत अणु
	OPAL_PHB_ERROR_DATA_TYPE_P7IOC = 1,
	OPAL_PHB_ERROR_DATA_TYPE_PHB3 = 2,
	OPAL_PHB_ERROR_DATA_TYPE_PHB4 = 3
पूर्ण;

क्रमागत अणु
	OPAL_P7IOC_NUM_PEST_REGS = 128,
	OPAL_PHB3_NUM_PEST_REGS = 256,
	OPAL_PHB4_NUM_PEST_REGS = 512
पूर्ण;

काष्ठा OpalIoPhbErrorCommon अणु
	__be32 version;
	__be32 ioType;
	__be32 len;
पूर्ण;

काष्ठा OpalIoP7IOCPhbErrorData अणु
	काष्ठा OpalIoPhbErrorCommon common;

	__be32 brdgCtl;

	// P7IOC utl regs
	__be32 portStatusReg;
	__be32 rootCmplxStatus;
	__be32 busAgentStatus;

	// P7IOC cfg regs
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;

	// cfg AER regs
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;

	__be32 rsv3;

	// Record data about the call to allocate a buffer.
	__be64 errorClass;
	__be64 correlator;

	//P7IOC MMIO Error Regs
	__be64 p7iocPlssr;                // n120
	__be64 p7iocCsr;                  // n110
	__be64 lemFir;                    // nC00
	__be64 lemErrorMask;              // nC18
	__be64 lemWOF;                    // nC40
	__be64 phbErrorStatus;            // nC80
	__be64 phbFirstErrorStatus;       // nC88
	__be64 phbErrorLog0;              // nCC0
	__be64 phbErrorLog1;              // nCC8
	__be64 mmioErrorStatus;           // nD00
	__be64 mmioFirstErrorStatus;      // nD08
	__be64 mmioErrorLog0;             // nD40
	__be64 mmioErrorLog1;             // nD48
	__be64 dma0ErrorStatus;           // nD80
	__be64 dma0FirstErrorStatus;      // nD88
	__be64 dma0ErrorLog0;             // nDC0
	__be64 dma0ErrorLog1;             // nDC8
	__be64 dma1ErrorStatus;           // nE00
	__be64 dma1FirstErrorStatus;      // nE08
	__be64 dma1ErrorLog0;             // nE40
	__be64 dma1ErrorLog1;             // nE48
	__be64 pestA[OPAL_P7IOC_NUM_PEST_REGS];
	__be64 pestB[OPAL_P7IOC_NUM_PEST_REGS];
पूर्ण;

काष्ठा OpalIoPhb3ErrorData अणु
	काष्ठा OpalIoPhbErrorCommon common;

	__be32 brdgCtl;

	/* PHB3 UTL regs */
	__be32 portStatusReg;
	__be32 rootCmplxStatus;
	__be32 busAgentStatus;

	/* PHB3 cfg regs */
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;

	/* cfg AER regs */
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;

	__be32 rsv3;

	/* Record data about the call to allocate a buffer */
	__be64 errorClass;
	__be64 correlator;

	/* PHB3 MMIO Error Regs */
	__be64 nFir;			/* 000 */
	__be64 nFirMask;		/* 003 */
	__be64 nFirWOF;		/* 008 */
	__be64 phbPlssr;		/* 120 */
	__be64 phbCsr;		/* 110 */
	__be64 lemFir;		/* C00 */
	__be64 lemErrorMask;		/* C18 */
	__be64 lemWOF;		/* C40 */
	__be64 phbErrorStatus;	/* C80 */
	__be64 phbFirstErrorStatus;	/* C88 */
	__be64 phbErrorLog0;		/* CC0 */
	__be64 phbErrorLog1;		/* CC8 */
	__be64 mmioErrorStatus;	/* D00 */
	__be64 mmioFirstErrorStatus;	/* D08 */
	__be64 mmioErrorLog0;		/* D40 */
	__be64 mmioErrorLog1;		/* D48 */
	__be64 dma0ErrorStatus;	/* D80 */
	__be64 dma0FirstErrorStatus;	/* D88 */
	__be64 dma0ErrorLog0;		/* DC0 */
	__be64 dma0ErrorLog1;		/* DC8 */
	__be64 dma1ErrorStatus;	/* E00 */
	__be64 dma1FirstErrorStatus;	/* E08 */
	__be64 dma1ErrorLog0;		/* E40 */
	__be64 dma1ErrorLog1;		/* E48 */
	__be64 pestA[OPAL_PHB3_NUM_PEST_REGS];
	__be64 pestB[OPAL_PHB3_NUM_PEST_REGS];
पूर्ण;

काष्ठा OpalIoPhb4ErrorData अणु
	काष्ठा OpalIoPhbErrorCommon common;

	__be32 brdgCtl;

	/* PHB4 cfg regs */
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;

	/* cfg AER regs */
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;

	/* PHB4 ETU Error Regs */
	__be64 nFir;				/* 000 */
	__be64 nFirMask;			/* 003 */
	__be64 nFirWOF;				/* 008 */
	__be64 phbPlssr;			/* 120 */
	__be64 phbCsr;				/* 110 */
	__be64 lemFir;				/* C00 */
	__be64 lemErrorMask;			/* C18 */
	__be64 lemWOF;				/* C40 */
	__be64 phbErrorStatus;			/* C80 */
	__be64 phbFirstErrorStatus;		/* C88 */
	__be64 phbErrorLog0;			/* CC0 */
	__be64 phbErrorLog1;			/* CC8 */
	__be64 phbTxeErrorStatus;		/* D00 */
	__be64 phbTxeFirstErrorStatus;		/* D08 */
	__be64 phbTxeErrorLog0;			/* D40 */
	__be64 phbTxeErrorLog1;			/* D48 */
	__be64 phbRxeArbErrorStatus;		/* D80 */
	__be64 phbRxeArbFirstErrorStatus;	/* D88 */
	__be64 phbRxeArbErrorLog0;		/* DC0 */
	__be64 phbRxeArbErrorLog1;		/* DC8 */
	__be64 phbRxeMrgErrorStatus;		/* E00 */
	__be64 phbRxeMrgFirstErrorStatus;	/* E08 */
	__be64 phbRxeMrgErrorLog0;		/* E40 */
	__be64 phbRxeMrgErrorLog1;		/* E48 */
	__be64 phbRxeTceErrorStatus;		/* E80 */
	__be64 phbRxeTceFirstErrorStatus;	/* E88 */
	__be64 phbRxeTceErrorLog0;		/* EC0 */
	__be64 phbRxeTceErrorLog1;		/* EC8 */

	/* PHB4 REGB Error Regs */
	__be64 phbPblErrorStatus;		/* 1900 */
	__be64 phbPblFirstErrorStatus;		/* 1908 */
	__be64 phbPblErrorLog0;			/* 1940 */
	__be64 phbPblErrorLog1;			/* 1948 */
	__be64 phbPcieDlpErrorLog1;		/* 1AA0 */
	__be64 phbPcieDlpErrorLog2;		/* 1AA8 */
	__be64 phbPcieDlpErrorStatus;		/* 1AB0 */
	__be64 phbRegbErrorStatus;		/* 1C00 */
	__be64 phbRegbFirstErrorStatus;		/* 1C08 */
	__be64 phbRegbErrorLog0;		/* 1C40 */
	__be64 phbRegbErrorLog1;		/* 1C48 */

	__be64 pestA[OPAL_PHB4_NUM_PEST_REGS];
	__be64 pestB[OPAL_PHB4_NUM_PEST_REGS];
पूर्ण;

क्रमागत अणु
	OPAL_REINIT_CPUS_HILE_BE	= (1 << 0),
	OPAL_REINIT_CPUS_HILE_LE	= (1 << 1),

	/* These two define the base MMU mode of the host on P9
	 *
	 * On P9 Nimbus DD2.0 and Cumlus (and later), KVM can still
	 * create hash guests in "radix" mode with care (full core
	 * चयन only).
	 */
	OPAL_REINIT_CPUS_MMU_HASH	= (1 << 2),
	OPAL_REINIT_CPUS_MMU_RADIX	= (1 << 3),

	OPAL_REINIT_CPUS_TM_SUSPEND_DISABLED = (1 << 4),
पूर्ण;

प्रकार काष्ठा oppanel_line अणु
	__be64 line;
	__be64 line_len;
पूर्ण oppanel_line_t;

क्रमागत opal_prd_msg_type अणु
	OPAL_PRD_MSG_TYPE_INIT = 0,	/* HBRT --> OPAL */
	OPAL_PRD_MSG_TYPE_FINI,		/* HBRT/kernel --> OPAL */
	OPAL_PRD_MSG_TYPE_ATTN,		/* HBRT <-- OPAL */
	OPAL_PRD_MSG_TYPE_ATTN_ACK,	/* HBRT --> OPAL */
	OPAL_PRD_MSG_TYPE_OCC_ERROR,	/* HBRT <-- OPAL */
	OPAL_PRD_MSG_TYPE_OCC_RESET,	/* HBRT <-- OPAL */
पूर्ण;

काष्ठा opal_prd_msg_header अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		pad[1];
	__be16		size;
पूर्ण;

काष्ठा opal_prd_msg;

#घोषणा OCC_RESET                       0
#घोषणा OCC_LOAD                        1
#घोषणा OCC_THROTTLE                    2
#घोषणा OCC_MAX_THROTTLE_STATUS         5

काष्ठा opal_occ_msg अणु
	__be64 type;
	__be64 chip;
	__be64 throttle_status;
पूर्ण;

/*
 * SG entries
 *
 * WARNING: The current implementation requires each entry
 * to represent a block that is 4k aligned *and* each block
 * size except the last one in the list to be as well.
 */
काष्ठा opal_sg_entry अणु
	__be64 data;
	__be64 length;
पूर्ण;

/*
 * Candidate image SG list.
 *
 * length = VER | length
 */
काष्ठा opal_sg_list अणु
	__be64 length;
	__be64 next;
	काष्ठा opal_sg_entry entry[];
पूर्ण;

/*
 * Dump region ID range usable by the OS
 */
#घोषणा OPAL_DUMP_REGION_HOST_START		0x80
#घोषणा OPAL_DUMP_REGION_LOG_BUF		0x80
#घोषणा OPAL_DUMP_REGION_HOST_END		0xFF

/* CAPI modes क्रम PHB */
क्रमागत अणु
	OPAL_PHB_CAPI_MODE_PCIE		= 0,
	OPAL_PHB_CAPI_MODE_CAPI		= 1,
	OPAL_PHB_CAPI_MODE_SNOOP_OFF    = 2,
	OPAL_PHB_CAPI_MODE_SNOOP_ON	= 3,
	OPAL_PHB_CAPI_MODE_DMA		= 4,
	OPAL_PHB_CAPI_MODE_DMA_TVT1	= 5,
पूर्ण;

/* OPAL I2C request */
काष्ठा opal_i2c_request अणु
	uपूर्णांक8_t	type;
#घोषणा OPAL_I2C_RAW_READ	0
#घोषणा OPAL_I2C_RAW_WRITE	1
#घोषणा OPAL_I2C_SM_READ	2
#घोषणा OPAL_I2C_SM_WRITE	3
	uपूर्णांक8_t flags;
#घोषणा OPAL_I2C_ADDR_10	0x01	/* Not supported yet */
	uपूर्णांक8_t	subaddr_sz;		/* Max 4 */
	uपूर्णांक8_t reserved;
	__be16 addr;			/* 7 or 10 bit address */
	__be16 reserved2;
	__be32 subaddr;		/* Sub-address अगर any */
	__be32 size;			/* Data size */
	__be64 buffer_ra;		/* Buffer real address */
पूर्ण;

/*
 * EPOW status sharing (OPAL and the host)
 *
 * The host will pass on OPAL, a buffer of length OPAL_SYSEPOW_MAX
 * with inभागidual elements being 16 bits wide to fetch the प्रणाली
 * wide EPOW status. Each element in the buffer will contain the
 * EPOW status in it's bit representation क्रम a particular EPOW sub
 * class as defined here. So multiple detailed EPOW status bits
 * specअगरic क्रम any sub class can be represented in a single buffer
 * element as it's bit representation.
 */

/* System EPOW type */
क्रमागत OpalSysEघात अणु
	OPAL_SYSEPOW_POWER	= 0,	/* Power EPOW */
	OPAL_SYSEPOW_TEMP	= 1,	/* Temperature EPOW */
	OPAL_SYSEPOW_COOLING	= 2,	/* Cooling EPOW */
	OPAL_SYSEPOW_MAX	= 3,	/* Max EPOW categories */
पूर्ण;

/* Power EPOW */
क्रमागत OpalSysPower अणु
	OPAL_SYSPOWER_UPS	= 0x0001, /* System on UPS घातer */
	OPAL_SYSPOWER_CHNG	= 0x0002, /* System घातer config change */
	OPAL_SYSPOWER_FAIL	= 0x0004, /* System impending घातer failure */
	OPAL_SYSPOWER_INCL	= 0x0008, /* System incomplete घातer */
पूर्ण;

/* Temperature EPOW */
क्रमागत OpalSysTemp अणु
	OPAL_SYSTEMP_AMB	= 0x0001, /* System over ambient temperature */
	OPAL_SYSTEMP_INT	= 0x0002, /* System over पूर्णांकernal temperature */
	OPAL_SYSTEMP_HMD	= 0x0004, /* System over ambient humidity */
पूर्ण;

/* Cooling EPOW */
क्रमागत OpalSysCooling अणु
	OPAL_SYSCOOL_INSF	= 0x0001, /* System insufficient cooling */
पूर्ण;

/* Argument to OPAL_CEC_REBOOT2() */
क्रमागत अणु
	OPAL_REBOOT_NORMAL		= 0,
	OPAL_REBOOT_PLATFORM_ERROR	= 1,
	OPAL_REBOOT_FULL_IPL		= 2,
	OPAL_REBOOT_MPIPL		= 3,
	OPAL_REBOOT_FAST		= 4,
पूर्ण;

/* Argument to OPAL_PCI_TCE_KILL */
क्रमागत अणु
	OPAL_PCI_TCE_KILL_PAGES,
	OPAL_PCI_TCE_KILL_PE,
	OPAL_PCI_TCE_KILL_ALL,
पूर्ण;

/* The xive operation mode indicates the active "API" and
 * corresponds to the "mode" parameter of the opal_xive_reset()
 * call
 */
क्रमागत अणु
	OPAL_XIVE_MODE_EMU	= 0,
	OPAL_XIVE_MODE_EXPL	= 1,
पूर्ण;

/* Flags क्रम OPAL_XIVE_GET_IRQ_INFO */
क्रमागत अणु
	OPAL_XIVE_IRQ_TRIGGER_PAGE	= 0x00000001,
	OPAL_XIVE_IRQ_STORE_EOI		= 0x00000002,
	OPAL_XIVE_IRQ_LSI		= 0x00000004,
	OPAL_XIVE_IRQ_SHIFT_BUG		= 0x00000008, /* P9 DD1.0 workaround */
	OPAL_XIVE_IRQ_MASK_VIA_FW	= 0x00000010, /* P9 DD1.0 workaround */
	OPAL_XIVE_IRQ_EOI_VIA_FW	= 0x00000020, /* P9 DD1.0 workaround */
पूर्ण;

/* Flags क्रम OPAL_XIVE_GET/SET_QUEUE_INFO */
क्रमागत अणु
	OPAL_XIVE_EQ_ENABLED		= 0x00000001,
	OPAL_XIVE_EQ_ALWAYS_NOTIFY	= 0x00000002,
	OPAL_XIVE_EQ_ESCALATE		= 0x00000004,
पूर्ण;

/* Flags क्रम OPAL_XIVE_GET/SET_VP_INFO */
क्रमागत अणु
	OPAL_XIVE_VP_ENABLED		= 0x00000001,
	OPAL_XIVE_VP_SINGLE_ESCALATION	= 0x00000002,
पूर्ण;

/* "Any chip" replacement क्रम chip ID क्रम allocation functions */
क्रमागत अणु
	OPAL_XIVE_ANY_CHIP		= 0xffffffff,
पूर्ण;

/* Xive sync options */
क्रमागत अणु
	/* This bits are cumulative, arg is a girq */
	XIVE_SYNC_EAS			= 0x00000001, /* Sync irq source */
	XIVE_SYNC_QUEUE			= 0x00000002, /* Sync irq target */
पूर्ण;

/* Dump options */
क्रमागत अणु
	XIVE_DUMP_TM_HYP	= 0,
	XIVE_DUMP_TM_POOL	= 1,
	XIVE_DUMP_TM_OS		= 2,
	XIVE_DUMP_TM_USER	= 3,
	XIVE_DUMP_VP		= 4,
	XIVE_DUMP_EMU_STATE	= 5,
पूर्ण;

/* "type" argument options क्रम OPAL_IMC_COUNTERS_* calls */
क्रमागत अणु
	OPAL_IMC_COUNTERS_NEST = 1,
	OPAL_IMC_COUNTERS_CORE = 2,
	OPAL_IMC_COUNTERS_TRACE = 3,
पूर्ण;


/* PCI p2p descriptor */
#घोषणा OPAL_PCI_P2P_ENABLE		0x1
#घोषणा OPAL_PCI_P2P_LOAD		0x2
#घोषणा OPAL_PCI_P2P_STORE		0x4

/* MPIPL update operations */
क्रमागत opal_mpipl_ops अणु
	OPAL_MPIPL_ADD_RANGE			= 0,
	OPAL_MPIPL_REMOVE_RANGE			= 1,
	OPAL_MPIPL_REMOVE_ALL			= 2,
	OPAL_MPIPL_FREE_PRESERVED_MEMORY	= 3,
पूर्ण;

/* Tag will poपूर्णांक to various metadata area. Kernel will
 * use tag to get metadata value.
 */
क्रमागत opal_mpipl_tags अणु
	OPAL_MPIPL_TAG_CPU	= 0,
	OPAL_MPIPL_TAG_OPAL	= 1,
	OPAL_MPIPL_TAG_KERNEL	= 2,
	OPAL_MPIPL_TAG_BOOT_MEM	= 3,
पूर्ण;

/* Preserved memory details */
काष्ठा opal_mpipl_region अणु
	__be64	src;
	__be64	dest;
	__be64	size;
पूर्ण;

/* Structure version */
#घोषणा OPAL_MPIPL_VERSION		0x01

काष्ठा opal_mpipl_fadump अणु
	u8	version;
	u8	reserved[7];
	__be32	crashing_pir;	/* OPAL crashing CPU PIR */
	__be32	cpu_data_version;
	__be32	cpu_data_size;
	__be32	region_cnt;
	काष्ठा	opal_mpipl_region region[];
पूर्ण __packed;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __OPAL_API_H */
