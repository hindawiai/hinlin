<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_HVCALL_H
#घोषणा _ASM_POWERPC_HVCALL_H
#अगर_घोषित __KERNEL__

#घोषणा HVSC			.दीर्घ 0x44000022

#घोषणा H_SUCCESS	0
#घोषणा H_BUSY		1	/* Hardware busy -- retry later */
#घोषणा H_CLOSED	2	/* Resource बंदd */
#घोषणा H_NOT_AVAILABLE 3
#घोषणा H_CONSTRAINED	4	/* Resource request स्थिरrained to max allowed */
#घोषणा H_PARTIAL       5
#घोषणा H_IN_PROGRESS	14	/* Kind of like busy */
#घोषणा H_PAGE_REGISTERED 15
#घोषणा H_PARTIAL_STORE   16
#घोषणा H_PENDING	17	/* वापसed from H_POLL_PENDING */
#घोषणा H_CONTINUE	18	/* Returned from H_Join on success */
#घोषणा H_LONG_BUSY_START_RANGE		9900  /* Start of दीर्घ busy range */
#घोषणा H_LONG_BUSY_ORDER_1_MSEC	9900  /* Long busy, hपूर्णांक that 1msec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_ORDER_10_MSEC	9901  /* Long busy, hपूर्णांक that 10msec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_ORDER_100_MSEC 	9902  /* Long busy, hपूर्णांक that 100msec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_ORDER_1_SEC		9903  /* Long busy, hपूर्णांक that 1sec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_ORDER_10_SEC	9904  /* Long busy, hपूर्णांक that 10sec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_ORDER_100_SEC	9905  /* Long busy, hपूर्णांक that 100sec \
						 is a good समय to retry */
#घोषणा H_LONG_BUSY_END_RANGE		9905  /* End of दीर्घ busy range */

/* Internal value used in book3s_hv kvm support; not वापसed to guests */
#घोषणा H_TOO_HARD	9999

#घोषणा H_HARDWARE	-1	/* Hardware error */
#घोषणा H_FUNCTION	-2	/* Function not supported */
#घोषणा H_PRIVILEGE	-3	/* Caller not privileged */
#घोषणा H_PARAMETER	-4	/* Parameter invalid, out-of-range or conflicting */
#घोषणा H_BAD_MODE	-5	/* Illegal msr value */
#घोषणा H_PTEG_FULL	-6	/* PTEG is full */
#घोषणा H_NOT_FOUND	-7	/* PTE was not found" */
#घोषणा H_RESERVED_DABR	-8	/* DABR address is reserved by the hypervisor on this processor" */
#घोषणा H_NO_MEM	-9
#घोषणा H_AUTHORITY	-10
#घोषणा H_PERMISSION	-11
#घोषणा H_DROPPED	-12
#घोषणा H_SOURCE_PARM	-13
#घोषणा H_DEST_PARM	-14
#घोषणा H_REMOTE_PARM	-15
#घोषणा H_RESOURCE	-16
#घोषणा H_ADAPTER_PARM  -17
#घोषणा H_RH_PARM       -18
#घोषणा H_RCQ_PARM      -19
#घोषणा H_SCQ_PARM      -20
#घोषणा H_EQ_PARM       -21
#घोषणा H_RT_PARM       -22
#घोषणा H_ST_PARM       -23
#घोषणा H_SIGT_PARM     -24
#घोषणा H_TOKEN_PARM    -25
#घोषणा H_MLENGTH_PARM  -27
#घोषणा H_MEM_PARM      -28
#घोषणा H_MEM_ACCESS_PARM -29
#घोषणा H_ATTR_PARM     -30
#घोषणा H_PORT_PARM     -31
#घोषणा H_MCG_PARM      -32
#घोषणा H_VL_PARM       -33
#घोषणा H_TSIZE_PARM    -34
#घोषणा H_TRACE_PARM    -35

#घोषणा H_MASK_PARM     -37
#घोषणा H_MCG_FULL      -38
#घोषणा H_ALIAS_EXIST   -39
#घोषणा H_P_COUNTER     -40
#घोषणा H_TABLE_FULL    -41
#घोषणा H_ALT_TABLE     -42
#घोषणा H_MR_CONDITION  -43
#घोषणा H_NOT_ENOUGH_RESOURCES -44
#घोषणा H_R_STATE       -45
#घोषणा H_RESCINDED     -46
#घोषणा H_P2		-55
#घोषणा H_P3		-56
#घोषणा H_P4		-57
#घोषणा H_P5		-58
#घोषणा H_P6		-59
#घोषणा H_P7		-60
#घोषणा H_P8		-61
#घोषणा H_P9		-62
#घोषणा H_TOO_BIG	-64
#घोषणा H_UNSUPPORTED	-67
#घोषणा H_OVERLAP	-68
#घोषणा H_INTERRUPT	-69
#घोषणा H_BAD_DATA	-70
#घोषणा H_NOT_ACTIVE	-71
#घोषणा H_SG_LIST	-72
#घोषणा H_OP_MODE	-73
#घोषणा H_COP_HW	-74
#घोषणा H_STATE		-75
#घोषणा H_UNSUPPORTED_FLAG_START	-256
#घोषणा H_UNSUPPORTED_FLAG_END		-511
#घोषणा H_MULTI_THREADS_ACTIVE	-9005
#घोषणा H_OUTSTANDING_COP_OPS	-9006


/* Long Busy is a condition that can be वापसed by the firmware
 * when a call cannot be completed now, but the identical call
 * should be retried later.  This prevents calls blocking in the
 * firmware क्रम दीर्घ periods of समय.  Annoyingly the firmware can वापस
 * a range of वापस codes, hपूर्णांकing at how दीर्घ we should रुको beक्रमe
 * retrying.  If you करोn't care क्रम the hपूर्णांक, the macro below is a good
 * way to check क्रम the दीर्घ_busy वापस codes
 */
#घोषणा H_IS_LONG_BUSY(x)  ((x >= H_LONG_BUSY_START_RANGE) \
			     && (x <= H_LONG_BUSY_END_RANGE))

/* Flags */
#घोषणा H_LARGE_PAGE		(1UL<<(63-16))
#घोषणा H_EXACT			(1UL<<(63-24))	/* Use exact PTE or वापस H_PTEG_FULL */
#घोषणा H_R_XLATE		(1UL<<(63-25))	/* include a valid logical page num in the pte अगर the valid bit is set */
#घोषणा H_READ_4		(1UL<<(63-26))	/* Return 4 PTEs */
#घोषणा H_PAGE_STATE_CHANGE	(1UL<<(63-28))
#घोषणा H_PAGE_UNUSED		((1UL<<(63-29)) | (1UL<<(63-30)))
#घोषणा H_PAGE_SET_UNUSED	(H_PAGE_STATE_CHANGE | H_PAGE_UNUSED)
#घोषणा H_PAGE_SET_LOANED	(H_PAGE_SET_UNUSED | (1UL<<(63-31)))
#घोषणा H_PAGE_SET_ACTIVE	H_PAGE_STATE_CHANGE
#घोषणा H_AVPN			(1UL<<(63-32))	/* An avpn is provided as a sanity test */
#घोषणा H_ANDCOND		(1UL<<(63-33))
#घोषणा H_LOCAL			(1UL<<(63-35))
#घोषणा H_ICACHE_INVALIDATE	(1UL<<(63-40))	/* icbi, etc.  (ignored क्रम IO pages) */
#घोषणा H_ICACHE_SYNCHRONIZE	(1UL<<(63-41))	/* dcbst, icbi, etc (ignored क्रम IO pages */
#घोषणा H_COALESCE_CAND	(1UL<<(63-42))	/* page is a good candidate क्रम coalescing */
#घोषणा H_ZERO_PAGE		(1UL<<(63-48))	/* zero the page beक्रमe mapping (ignored क्रम IO pages) */
#घोषणा H_COPY_PAGE		(1UL<<(63-49))
#घोषणा H_N			(1UL<<(63-61))
#घोषणा H_PP1			(1UL<<(63-62))
#घोषणा H_PP2			(1UL<<(63-63))

/* Flags क्रम H_REGISTER_VPA subfunction field */
#घोषणा H_VPA_FUNC_SHIFT	(63-18)	/* Bit posn of subfunction code */
#घोषणा H_VPA_FUNC_MASK		7UL
#घोषणा H_VPA_REG_VPA		1UL	/* Register Virtual Processor Area */
#घोषणा H_VPA_REG_DTL		2UL	/* Register Dispatch Trace Log */
#घोषणा H_VPA_REG_SLB		3UL	/* Register SLB shaकरोw buffer */
#घोषणा H_VPA_DEREG_VPA		5UL	/* Deरेजिस्टर Virtual Processor Area */
#घोषणा H_VPA_DEREG_DTL		6UL	/* Deरेजिस्टर Dispatch Trace Log */
#घोषणा H_VPA_DEREG_SLB		7UL	/* Deरेजिस्टर SLB shaकरोw buffer */

/* VASI States */
#घोषणा H_VASI_INVALID          0
#घोषणा H_VASI_ENABLED          1
#घोषणा H_VASI_ABORTED          2
#घोषणा H_VASI_SUSPENDING       3
#घोषणा H_VASI_SUSPENDED        4
#घोषणा H_VASI_RESUMED          5
#घोषणा H_VASI_COMPLETED        6

/* VASI संकेत codes. Only the Cancel code is valid क्रम H_VASI_SIGNAL. */
#घोषणा H_VASI_SIGNAL_CANCEL    1
#घोषणा H_VASI_SIGNAL_ABORT     2
#घोषणा H_VASI_SIGNAL_SUSPEND   3
#घोषणा H_VASI_SIGNAL_COMPLETE  4
#घोषणा H_VASI_SIGNAL_ENABLE    5
#घोषणा H_VASI_SIGNAL_FAILOVER  6

/* Each control block has to be on a 4K boundary */
#घोषणा H_CB_ALIGNMENT          4096

/* pSeries hypervisor opcodes */
#घोषणा H_REMOVE		0x04
#घोषणा H_ENTER			0x08
#घोषणा H_READ			0x0c
#घोषणा H_CLEAR_MOD		0x10
#घोषणा H_CLEAR_REF		0x14
#घोषणा H_PROTECT		0x18
#घोषणा H_GET_TCE		0x1c
#घोषणा H_PUT_TCE		0x20
#घोषणा H_SET_SPRG0		0x24
#घोषणा H_SET_DABR		0x28
#घोषणा H_PAGE_INIT		0x2c
#घोषणा H_SET_ASR		0x30
#घोषणा H_ASR_ON		0x34
#घोषणा H_ASR_OFF		0x38
#घोषणा H_LOGICAL_CI_LOAD	0x3c
#घोषणा H_LOGICAL_CI_STORE	0x40
#घोषणा H_LOGICAL_CACHE_LOAD	0x44
#घोषणा H_LOGICAL_CACHE_STORE	0x48
#घोषणा H_LOGICAL_ICBI		0x4c
#घोषणा H_LOGICAL_DCBF		0x50
#घोषणा H_GET_TERM_CHAR		0x54
#घोषणा H_PUT_TERM_CHAR		0x58
#घोषणा H_REAL_TO_LOGICAL	0x5c
#घोषणा H_HYPERVISOR_DATA	0x60
#घोषणा H_EOI			0x64
#घोषणा H_CPPR			0x68
#घोषणा H_IPI			0x6c
#घोषणा H_IPOLL			0x70
#घोषणा H_XIRR			0x74
#घोषणा H_PERFMON		0x7c
#घोषणा H_MIGRATE_DMA		0x78
#घोषणा H_REGISTER_VPA		0xDC
#घोषणा H_CEDE			0xE0
#घोषणा H_CONFER		0xE4
#घोषणा H_PROD			0xE8
#घोषणा H_GET_PPP		0xEC
#घोषणा H_SET_PPP		0xF0
#घोषणा H_PURR			0xF4
#घोषणा H_PIC			0xF8
#घोषणा H_REG_CRQ		0xFC
#घोषणा H_FREE_CRQ		0x100
#घोषणा H_VIO_SIGNAL		0x104
#घोषणा H_SEND_CRQ		0x108
#घोषणा H_COPY_RDMA		0x110
#घोषणा H_REGISTER_LOGICAL_LAN	0x114
#घोषणा H_FREE_LOGICAL_LAN	0x118
#घोषणा H_ADD_LOGICAL_LAN_BUFFER 0x11C
#घोषणा H_SEND_LOGICAL_LAN	0x120
#घोषणा H_BULK_REMOVE		0x124
#घोषणा H_MULTICAST_CTRL	0x130
#घोषणा H_SET_XDABR		0x134
#घोषणा H_STUFF_TCE		0x138
#घोषणा H_PUT_TCE_INसूचीECT	0x13C
#घोषणा H_CHANGE_LOGICAL_LAN_MAC 0x14C
#घोषणा H_VTERM_PARTNER_INFO	0x150
#घोषणा H_REGISTER_VTERM	0x154
#घोषणा H_FREE_VTERM		0x158
#घोषणा H_RESET_EVENTS          0x15C
#घोषणा H_ALLOC_RESOURCE        0x160
#घोषणा H_FREE_RESOURCE         0x164
#घोषणा H_MODIFY_QP             0x168
#घोषणा H_QUERY_QP              0x16C
#घोषणा H_REREGISTER_PMR        0x170
#घोषणा H_REGISTER_SMR          0x174
#घोषणा H_QUERY_MR              0x178
#घोषणा H_QUERY_MW              0x17C
#घोषणा H_QUERY_HCA             0x180
#घोषणा H_QUERY_PORT            0x184
#घोषणा H_MODIFY_PORT           0x188
#घोषणा H_DEFINE_AQP1           0x18C
#घोषणा H_GET_TRACE_BUFFER      0x190
#घोषणा H_DEFINE_AQP0           0x194
#घोषणा H_RESIZE_MR             0x198
#घोषणा H_ATTACH_MCQP           0x19C
#घोषणा H_DETACH_MCQP           0x1A0
#घोषणा H_CREATE_RPT            0x1A4
#घोषणा H_REMOVE_RPT            0x1A8
#घोषणा H_REGISTER_RPAGES       0x1AC
#घोषणा H_DISABLE_AND_GET       0x1B0
#घोषणा H_ERROR_DATA            0x1B4
#घोषणा H_GET_HCA_INFO          0x1B8
#घोषणा H_GET_PERF_COUNT        0x1BC
#घोषणा H_MANAGE_TRACE          0x1C0
#घोषणा H_GET_CPU_CHARACTERISTICS 0x1C8
#घोषणा H_FREE_LOGICAL_LAN_BUFFER 0x1D4
#घोषणा H_QUERY_INT_STATE       0x1E4
#घोषणा H_POLL_PENDING		0x1D8
#घोषणा H_ILLAN_ATTRIBUTES	0x244
#घोषणा H_MODIFY_HEA_QP		0x250
#घोषणा H_QUERY_HEA_QP		0x254
#घोषणा H_QUERY_HEA		0x258
#घोषणा H_QUERY_HEA_PORT	0x25C
#घोषणा H_MODIFY_HEA_PORT	0x260
#घोषणा H_REG_BCMC		0x264
#घोषणा H_DEREG_BCMC		0x268
#घोषणा H_REGISTER_HEA_RPAGES	0x26C
#घोषणा H_DISABLE_AND_GET_HEA	0x270
#घोषणा H_GET_HEA_INFO		0x274
#घोषणा H_ALLOC_HEA_RESOURCE	0x278
#घोषणा H_ADD_CONN		0x284
#घोषणा H_DEL_CONN		0x288
#घोषणा H_JOIN			0x298
#घोषणा H_VASI_SIGNAL           0x2A0
#घोषणा H_VASI_STATE            0x2A4
#घोषणा H_VIOCTL		0x2A8
#घोषणा H_ENABLE_CRQ		0x2B0
#घोषणा H_GET_EM_PARMS		0x2B8
#घोषणा H_SET_MPP		0x2D0
#घोषणा H_GET_MPP		0x2D4
#घोषणा H_REG_SUB_CRQ		0x2DC
#घोषणा H_HOME_NODE_ASSOCIATIVITY 0x2EC
#घोषणा H_FREE_SUB_CRQ		0x2E0
#घोषणा H_SEND_SUB_CRQ		0x2E4
#घोषणा H_SEND_SUB_CRQ_INसूचीECT	0x2E8
#घोषणा H_BEST_ENERGY		0x2F4
#घोषणा H_XIRR_X		0x2FC
#घोषणा H_RANDOM		0x300
#घोषणा H_COP			0x304
#घोषणा H_GET_MPP_X		0x314
#घोषणा H_SET_MODE		0x31C
#घोषणा H_BLOCK_REMOVE		0x328
#घोषणा H_CLEAR_HPT		0x358
#घोषणा H_REQUEST_VMC		0x360
#घोषणा H_RESIZE_HPT_PREPARE	0x36C
#घोषणा H_RESIZE_HPT_COMMIT	0x370
#घोषणा H_REGISTER_PROC_TBL	0x37C
#घोषणा H_SIGNAL_SYS_RESET	0x380
#घोषणा H_INT_GET_SOURCE_INFO   0x3A8
#घोषणा H_INT_SET_SOURCE_CONFIG 0x3AC
#घोषणा H_INT_GET_SOURCE_CONFIG 0x3B0
#घोषणा H_INT_GET_QUEUE_INFO    0x3B4
#घोषणा H_INT_SET_QUEUE_CONFIG  0x3B8
#घोषणा H_INT_GET_QUEUE_CONFIG  0x3BC
#घोषणा H_INT_SET_OS_REPORTING_LINE 0x3C0
#घोषणा H_INT_GET_OS_REPORTING_LINE 0x3C4
#घोषणा H_INT_ESB               0x3C8
#घोषणा H_INT_SYNC              0x3CC
#घोषणा H_INT_RESET             0x3D0
#घोषणा H_SCM_READ_METADATA     0x3E4
#घोषणा H_SCM_WRITE_METADATA    0x3E8
#घोषणा H_SCM_BIND_MEM          0x3EC
#घोषणा H_SCM_UNBIND_MEM        0x3F0
#घोषणा H_SCM_QUERY_BLOCK_MEM_BINDING 0x3F4
#घोषणा H_SCM_QUERY_LOGICAL_MEM_BINDING 0x3F8
#घोषणा H_SCM_UNBIND_ALL        0x3FC
#घोषणा H_SCM_HEALTH            0x400
#घोषणा H_SCM_PERFORMANCE_STATS 0x418
#घोषणा H_RPT_INVALIDATE	0x448
#घोषणा H_SCM_FLUSH		0x44C
#घोषणा MAX_HCALL_OPCODE	H_SCM_FLUSH

/* Scope args क्रम H_SCM_UNBIND_ALL */
#घोषणा H_UNBIND_SCOPE_ALL (0x1)
#घोषणा H_UNBIND_SCOPE_DRC (0x2)

/* H_VIOCTL functions */
#घोषणा H_GET_VIOA_DUMP_SIZE	0x01
#घोषणा H_GET_VIOA_DUMP		0x02
#घोषणा H_GET_ILLAN_NUM_VLAN_IDS 0x03
#घोषणा H_GET_ILLAN_VLAN_ID_LIST 0x04
#घोषणा H_GET_ILLAN_SWITCH_ID	0x05
#घोषणा H_DISABLE_MIGRATION	0x06
#घोषणा H_ENABLE_MIGRATION	0x07
#घोषणा H_GET_PARTNER_INFO	0x08
#घोषणा H_GET_PARTNER_WWPN_LIST	0x09
#घोषणा H_DISABLE_ALL_VIO_INTS	0x0A
#घोषणा H_DISABLE_VIO_INTERRUPT	0x0B
#घोषणा H_ENABLE_VIO_INTERRUPT	0x0C
#घोषणा H_GET_SESSION_TOKEN	0x19
#घोषणा H_SESSION_ERR_DETECTED	0x1A


/* Platक्रमm specअगरic hcalls, used by KVM */
#घोषणा H_RTAS			0xf000

/* "Platform specific hcalls", provided by PHYP */
#घोषणा H_GET_24X7_CATALOG_PAGE	0xF078
#घोषणा H_GET_24X7_DATA		0xF07C
#घोषणा H_GET_PERF_COUNTER_INFO	0xF080

/* Platक्रमm-specअगरic hcalls used क्रम nested HV KVM */
#घोषणा H_SET_PARTITION_TABLE	0xF800
#घोषणा H_ENTER_NESTED		0xF804
#घोषणा H_TLB_INVALIDATE	0xF808
#घोषणा H_COPY_TOFROM_GUEST	0xF80C

/* Flags क्रम H_SVM_PAGE_IN */
#घोषणा H_PAGE_IN_SHARED        0x1

/* Platक्रमm-specअगरic hcalls used by the Ultravisor */
#घोषणा H_SVM_PAGE_IN		0xEF00
#घोषणा H_SVM_PAGE_OUT		0xEF04
#घोषणा H_SVM_INIT_START	0xEF08
#घोषणा H_SVM_INIT_DONE		0xEF0C
#घोषणा H_SVM_INIT_ABORT	0xEF14

/* Values क्रम 2nd argument to H_SET_MODE */
#घोषणा H_SET_MODE_RESOURCE_SET_CIABR		1
#घोषणा H_SET_MODE_RESOURCE_SET_DAWR0		2
#घोषणा H_SET_MODE_RESOURCE_ADDR_TRANS_MODE	3
#घोषणा H_SET_MODE_RESOURCE_LE			4
#घोषणा H_SET_MODE_RESOURCE_SET_DAWR1		5

/* Values क्रम argument to H_SIGNAL_SYS_RESET */
#घोषणा H_SIGNAL_SYS_RESET_ALL			-1
#घोषणा H_SIGNAL_SYS_RESET_ALL_OTHERS		-2
/* >= 0 values are CPU number */

/* H_GET_CPU_CHARACTERISTICS वापस values */
#घोषणा H_CPU_CHAR_SPEC_BAR_ORI31	(1ull << 63) // IBM bit 0
#घोषणा H_CPU_CHAR_BCCTRL_SERIALISED	(1ull << 62) // IBM bit 1
#घोषणा H_CPU_CHAR_L1D_FLUSH_ORI30	(1ull << 61) // IBM bit 2
#घोषणा H_CPU_CHAR_L1D_FLUSH_TRIG2	(1ull << 60) // IBM bit 3
#घोषणा H_CPU_CHAR_L1D_THREAD_PRIV	(1ull << 59) // IBM bit 4
#घोषणा H_CPU_CHAR_BRANCH_HINTS_HONORED	(1ull << 58) // IBM bit 5
#घोषणा H_CPU_CHAR_THREAD_RECONFIG_CTRL	(1ull << 57) // IBM bit 6
#घोषणा H_CPU_CHAR_COUNT_CACHE_DISABLED	(1ull << 56) // IBM bit 7
#घोषणा H_CPU_CHAR_BCCTR_FLUSH_ASSIST	(1ull << 54) // IBM bit 9
#घोषणा H_CPU_CHAR_BCCTR_LINK_FLUSH_ASSIST (1ull << 52) // IBM bit 11

#घोषणा H_CPU_BEHAV_FAVOUR_SECURITY	(1ull << 63) // IBM bit 0
#घोषणा H_CPU_BEHAV_L1D_FLUSH_PR	(1ull << 62) // IBM bit 1
#घोषणा H_CPU_BEHAV_BNDS_CHK_SPEC_BAR	(1ull << 61) // IBM bit 2
#घोषणा H_CPU_BEHAV_FAVOUR_SECURITY_H	(1ull << 60) // IBM bit 3
#घोषणा H_CPU_BEHAV_FLUSH_COUNT_CACHE	(1ull << 58) // IBM bit 5
#घोषणा H_CPU_BEHAV_FLUSH_LINK_STACK	(1ull << 57) // IBM bit 6

/* Flag values used in H_REGISTER_PROC_TBL hcall */
#घोषणा PROC_TABLE_OP_MASK	0x18
#घोषणा PROC_TABLE_DEREG	0x10
#घोषणा PROC_TABLE_NEW		0x18
#घोषणा PROC_TABLE_TYPE_MASK	0x06
#घोषणा PROC_TABLE_HPT_SLB	0x00
#घोषणा PROC_TABLE_HPT_PT	0x02
#घोषणा PROC_TABLE_RADIX	0x04
#घोषणा PROC_TABLE_GTSE		0x01

/*
 * Defines क्रम
 * H_RPT_INVALIDATE - Invalidate RPT translation lookaside inक्रमmation.
 */

/* Type of translation to invalidate (type) */
#घोषणा H_RPTI_TYPE_NESTED	0x0001	/* Invalidate nested guest partition-scope */
#घोषणा H_RPTI_TYPE_TLB		0x0002	/* Invalidate TLB */
#घोषणा H_RPTI_TYPE_PWC		0x0004	/* Invalidate Page Walk Cache */
/* Invalidate Process Table Entries अगर H_RPTI_TYPE_NESTED is clear */
#घोषणा H_RPTI_TYPE_PRT		0x0008
/* Invalidate Partition Table Entries अगर H_RPTI_TYPE_NESTED is set */
#घोषणा H_RPTI_TYPE_PAT		0x0008
#घोषणा H_RPTI_TYPE_ALL		(H_RPTI_TYPE_TLB | H_RPTI_TYPE_PWC | \
				 H_RPTI_TYPE_PRT)
#घोषणा H_RPTI_TYPE_NESTED_ALL	(H_RPTI_TYPE_TLB | H_RPTI_TYPE_PWC | \
				 H_RPTI_TYPE_PAT)

/* Invalidation tarमाला_लो (target) */
#घोषणा H_RPTI_TARGET_CMMU		0x01 /* All भव processors in the partition */
#घोषणा H_RPTI_TARGET_CMMU_LOCAL	0x02 /* Current भव processor */
/* All nest/accelerator agents in use by the partition */
#घोषणा H_RPTI_TARGET_NMMU		0x04

/* Page size mask (page sizes) */
#घोषणा H_RPTI_PAGE_4K	0x01
#घोषणा H_RPTI_PAGE_64K	0x02
#घोषणा H_RPTI_PAGE_2M	0x04
#घोषणा H_RPTI_PAGE_1G	0x08
#घोषणा H_RPTI_PAGE_ALL (-1UL)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

/**
 * plpar_hcall_norets: - Make a pseries hypervisor call with no वापस arguments
 * @opcode: The hypervisor call to make.
 *
 * This call supports up to 7 arguments and only वापसs the status of
 * the hcall. Use this version where possible, its slightly faster than
 * the other plpar_hcalls.
 */
दीर्घ plpar_hcall_norets(अचिन्हित दीर्घ opcode, ...);

/* Variant which करोes not करो hcall tracing */
दीर्घ plpar_hcall_norets_notrace(अचिन्हित दीर्घ opcode, ...);

/**
 * plpar_hcall: - Make a pseries hypervisor call
 * @opcode: The hypervisor call to make.
 * @retbuf: Buffer to store up to 4 वापस arguments in.
 *
 * This call supports up to 6 arguments and 4 वापस arguments. Use
 * PLPAR_HCALL_बफ_मानE to size the वापस argument buffer.
 *
 * Used क्रम all but the craziest of phyp पूर्णांकerfaces (see plpar_hcall9)
 */
#घोषणा PLPAR_HCALL_बफ_मानE 4
दीर्घ plpar_hcall(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *retbuf, ...);

/**
 * plpar_hcall_raw: - Make a hypervisor call without calculating hcall stats
 * @opcode: The hypervisor call to make.
 * @retbuf: Buffer to store up to 4 वापस arguments in.
 *
 * This call supports up to 6 arguments and 4 वापस arguments. Use
 * PLPAR_HCALL_बफ_मानE to size the वापस argument buffer.
 *
 * Used when phyp पूर्णांकerface needs to be called in real mode. Similar to
 * plpar_hcall, but plpar_hcall_raw works in real mode and करोes not
 * calculate hypervisor call statistics.
 */
दीर्घ plpar_hcall_raw(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *retbuf, ...);

/**
 * plpar_hcall9: - Make a pseries hypervisor call with up to 9 वापस arguments
 * @opcode: The hypervisor call to make.
 * @retbuf: Buffer to store up to 9 वापस arguments in.
 *
 * This call supports up to 9 arguments and 9 वापस arguments. Use
 * PLPAR_HCALL9_बफ_मानE to size the वापस argument buffer.
 */
#घोषणा PLPAR_HCALL9_बफ_मानE 9
दीर्घ plpar_hcall9(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *retbuf, ...);
दीर्घ plpar_hcall9_raw(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *retbuf, ...);

काष्ठा hvcall_mpp_data अणु
	अचिन्हित दीर्घ entitled_mem;
	अचिन्हित दीर्घ mapped_mem;
	अचिन्हित लघु group_num;
	अचिन्हित लघु pool_num;
	अचिन्हित अक्षर mem_weight;
	अचिन्हित अक्षर unallocated_mem_weight;
	अचिन्हित दीर्घ unallocated_entitlement;  /* value in bytes */
	अचिन्हित दीर्घ pool_size;
	चिन्हित दीर्घ loan_request;
	अचिन्हित दीर्घ backing_mem;
पूर्ण;

पूर्णांक h_get_mpp(काष्ठा hvcall_mpp_data *);

काष्ठा hvcall_mpp_x_data अणु
	अचिन्हित दीर्घ coalesced_bytes;
	अचिन्हित दीर्घ pool_coalesced_bytes;
	अचिन्हित दीर्घ pool_purr_cycles;
	अचिन्हित दीर्घ pool_spurr_cycles;
	अचिन्हित दीर्घ reserved[3];
पूर्ण;

पूर्णांक h_get_mpp_x(काष्ठा hvcall_mpp_x_data *mpp_x_data);

अटल अंतरभूत अचिन्हित पूर्णांक get_दीर्घbusy_msecs(पूर्णांक दीर्घbusy_rc)
अणु
	चयन (दीर्घbusy_rc) अणु
	हाल H_LONG_BUSY_ORDER_1_MSEC:
		वापस 1;
	हाल H_LONG_BUSY_ORDER_10_MSEC:
		वापस 10;
	हाल H_LONG_BUSY_ORDER_100_MSEC:
		वापस 100;
	हाल H_LONG_BUSY_ORDER_1_SEC:
		वापस 1000;
	हाल H_LONG_BUSY_ORDER_10_SEC:
		वापस 10000;
	हाल H_LONG_BUSY_ORDER_100_SEC:
		वापस 100000;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

काष्ठा h_cpu_अक्षर_result अणु
	u64 अक्षरacter;
	u64 behaviour;
पूर्ण;

/*
 * Register state क्रम entering a nested guest with H_ENTER_NESTED.
 * New member must be added at the end.
 */
काष्ठा hv_guest_state अणु
	u64 version;		/* version of this काष्ठाure layout, must be first */
	u32 lpid;
	u32 vcpu_token;
	/* These रेजिस्टरs are hypervisor privileged (at least क्रम writing) */
	u64 lpcr;
	u64 pcr;
	u64 amor;
	u64 dpdes;
	u64 hfscr;
	s64 tb_offset;
	u64 dawr0;
	u64 dawrx0;
	u64 ciabr;
	u64 hdec_expiry;
	u64 purr;
	u64 spurr;
	u64 ic;
	u64 vtb;
	u64 hdar;
	u64 hdsisr;
	u64 heir;
	u64 asdr;
	/* These are OS privileged but need to be set late in guest entry */
	u64 srr0;
	u64 srr1;
	u64 sprg[4];
	u64 pidr;
	u64 cfar;
	u64 ppr;
	/* Version 1 ends here */
	u64 dawr1;
	u64 dawrx1;
	/* Version 2 ends here */
पूर्ण;

/* Latest version of hv_guest_state काष्ठाure */
#घोषणा HV_GUEST_STATE_VERSION	2

अटल अंतरभूत पूर्णांक hv_guest_state_size(अचिन्हित पूर्णांक version)
अणु
	चयन (version) अणु
	हाल 1:
		वापस दुरत्वend(काष्ठा hv_guest_state, ppr);
	हाल 2:
		वापस दुरत्वend(काष्ठा hv_guest_state, dawrx1);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/*
 * From the करोcument "H_GetPerformanceCounterInfo Interface" v1.07
 *
 * H_GET_PERF_COUNTER_INFO argument
 */
काष्ठा hv_get_perf_counter_info_params अणु
	__be32 counter_request; /* I */
	__be32 starting_index;  /* IO */
	__be16 secondary_index; /* IO */
	__be16 वापसed_values; /* O */
	__be32 detail_rc; /* O, only needed when called via *_norets() */

	/*
	 * O, size each of counter_value element in bytes, only set क्रम version
	 * >= 0x3
	 */
	__be16 cv_element_size;

	/* I, 0 (zero) क्रम versions < 0x3 */
	__u8 counter_info_version_in;

	/* O, 0 (zero) अगर version < 0x3. Must be set to 0 when making hcall */
	__u8 counter_info_version_out;
	__u8 reserved[0xC];
	__u8 counter_value[];
पूर्ण __packed;

#घोषणा HGPCI_REQ_BUFFER_SIZE	4096
#घोषणा HGPCI_MAX_DATA_BYTES \
	(HGPCI_REQ_BUFFER_SIZE - माप(काष्ठा hv_get_perf_counter_info_params))

काष्ठा hv_gpci_request_buffer अणु
	काष्ठा hv_get_perf_counter_info_params params;
	uपूर्णांक8_t bytes[HGPCI_MAX_DATA_BYTES];
पूर्ण __packed;

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_HVCALL_H */
