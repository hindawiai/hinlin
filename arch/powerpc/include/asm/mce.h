<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Machine check exception header file.
 *
 * Copyright 2013 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अगर_अघोषित __ASM_PPC64_MCE_H__
#घोषणा __ASM_PPC64_MCE_H__

#समावेश <linux/bitops.h>

क्रमागत MCE_Version अणु
	MCE_V1 = 1,
पूर्ण;

क्रमागत MCE_Severity अणु
	MCE_SEV_NO_ERROR = 0,
	MCE_SEV_WARNING = 1,
	MCE_SEV_SEVERE = 2,
	MCE_SEV_FATAL = 3,
पूर्ण;

क्रमागत MCE_Disposition अणु
	MCE_DISPOSITION_RECOVERED = 0,
	MCE_DISPOSITION_NOT_RECOVERED = 1,
पूर्ण;

क्रमागत MCE_Initiator अणु
	MCE_INITIATOR_UNKNOWN = 0,
	MCE_INITIATOR_CPU = 1,
	MCE_INITIATOR_PCI = 2,
	MCE_INITIATOR_ISA = 3,
	MCE_INITIATOR_MEMORY= 4,
	MCE_INITIATOR_POWERMGM = 5,
पूर्ण;

क्रमागत MCE_ErrorType अणु
	MCE_ERROR_TYPE_UNKNOWN = 0,
	MCE_ERROR_TYPE_UE = 1,
	MCE_ERROR_TYPE_SLB = 2,
	MCE_ERROR_TYPE_ERAT = 3,
	MCE_ERROR_TYPE_TLB = 4,
	MCE_ERROR_TYPE_USER = 5,
	MCE_ERROR_TYPE_RA = 6,
	MCE_ERROR_TYPE_LINK = 7,
	MCE_ERROR_TYPE_DCACHE = 8,
	MCE_ERROR_TYPE_ICACHE = 9,
पूर्ण;

क्रमागत MCE_ErrorClass अणु
	MCE_ECLASS_UNKNOWN = 0,
	MCE_ECLASS_HARDWARE,
	MCE_ECLASS_HARD_INDETERMINATE,
	MCE_ECLASS_SOFTWARE,
	MCE_ECLASS_SOFT_INDETERMINATE,
पूर्ण;

क्रमागत MCE_UeErrorType अणु
	MCE_UE_ERROR_INDETERMINATE = 0,
	MCE_UE_ERROR_IFETCH = 1,
	MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH = 2,
	MCE_UE_ERROR_LOAD_STORE = 3,
	MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE = 4,
पूर्ण;

क्रमागत MCE_SlbErrorType अणु
	MCE_SLB_ERROR_INDETERMINATE = 0,
	MCE_SLB_ERROR_PARITY = 1,
	MCE_SLB_ERROR_MULTIHIT = 2,
पूर्ण;

क्रमागत MCE_EratErrorType अणु
	MCE_ERAT_ERROR_INDETERMINATE = 0,
	MCE_ERAT_ERROR_PARITY = 1,
	MCE_ERAT_ERROR_MULTIHIT = 2,
पूर्ण;

क्रमागत MCE_TlbErrorType अणु
	MCE_TLB_ERROR_INDETERMINATE = 0,
	MCE_TLB_ERROR_PARITY = 1,
	MCE_TLB_ERROR_MULTIHIT = 2,
पूर्ण;

क्रमागत MCE_UserErrorType अणु
	MCE_USER_ERROR_INDETERMINATE = 0,
	MCE_USER_ERROR_TLBIE = 1,
	MCE_USER_ERROR_SCV = 2,
पूर्ण;

क्रमागत MCE_RaErrorType अणु
	MCE_RA_ERROR_INDETERMINATE = 0,
	MCE_RA_ERROR_IFETCH = 1,
	MCE_RA_ERROR_IFETCH_FOREIGN = 2,
	MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH = 3,
	MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH_FOREIGN = 4,
	MCE_RA_ERROR_LOAD = 5,
	MCE_RA_ERROR_STORE = 6,
	MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE = 7,
	MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE_FOREIGN = 8,
	MCE_RA_ERROR_LOAD_STORE_FOREIGN = 9,
पूर्ण;

क्रमागत MCE_LinkErrorType अणु
	MCE_LINK_ERROR_INDETERMINATE = 0,
	MCE_LINK_ERROR_IFETCH_TIMEOUT = 1,
	MCE_LINK_ERROR_PAGE_TABLE_WALK_IFETCH_TIMEOUT = 2,
	MCE_LINK_ERROR_LOAD_TIMEOUT = 3,
	MCE_LINK_ERROR_STORE_TIMEOUT = 4,
	MCE_LINK_ERROR_PAGE_TABLE_WALK_LOAD_STORE_TIMEOUT = 5,
पूर्ण;

काष्ठा machine_check_event अणु
	क्रमागत MCE_Version	version:8;
	u8			in_use;
	क्रमागत MCE_Severity	severity:8;
	क्रमागत MCE_Initiator	initiator:8;
	क्रमागत MCE_ErrorType	error_type:8;
	क्रमागत MCE_ErrorClass	error_class:8;
	क्रमागत MCE_Disposition	disposition:8;
	bool			sync_error;
	u16			cpu;
	u64			gpr3;
	u64			srr0;
	u64			srr1;
	जोड़ अणु
		काष्ठा अणु
			क्रमागत MCE_UeErrorType ue_error_type:8;
			u8		effective_address_provided;
			u8		physical_address_provided;
			u8		ignore_event;
			u8		reserved_1[4];
			u64		effective_address;
			u64		physical_address;
			u8		reserved_2[8];
		पूर्ण ue_error;

		काष्ठा अणु
			क्रमागत MCE_SlbErrorType slb_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण slb_error;

		काष्ठा अणु
			क्रमागत MCE_EratErrorType erat_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण erat_error;

		काष्ठा अणु
			क्रमागत MCE_TlbErrorType tlb_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण tlb_error;

		काष्ठा अणु
			क्रमागत MCE_UserErrorType user_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण user_error;

		काष्ठा अणु
			क्रमागत MCE_RaErrorType ra_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण ra_error;

		काष्ठा अणु
			क्रमागत MCE_LinkErrorType link_error_type:8;
			u8		effective_address_provided;
			u8		reserved_1[6];
			u64		effective_address;
			u8		reserved_2[16];
		पूर्ण link_error;
	पूर्ण u;
पूर्ण;

काष्ठा mce_error_info अणु
	क्रमागत MCE_ErrorType error_type:8;
	जोड़ अणु
		क्रमागत MCE_UeErrorType ue_error_type:8;
		क्रमागत MCE_SlbErrorType slb_error_type:8;
		क्रमागत MCE_EratErrorType erat_error_type:8;
		क्रमागत MCE_TlbErrorType tlb_error_type:8;
		क्रमागत MCE_UserErrorType user_error_type:8;
		क्रमागत MCE_RaErrorType ra_error_type:8;
		क्रमागत MCE_LinkErrorType link_error_type:8;
	पूर्ण u;
	क्रमागत MCE_Severity	severity:8;
	क्रमागत MCE_Initiator	initiator:8;
	क्रमागत MCE_ErrorClass	error_class:8;
	bool			sync_error;
	bool			ignore_event;
पूर्ण;

#घोषणा MAX_MC_EVT	10

काष्ठा mce_info अणु
	पूर्णांक mce_nest_count;
	काष्ठा machine_check_event mce_event[MAX_MC_EVT];
	/* Queue क्रम delayed MCE events. */
	पूर्णांक mce_queue_count;
	काष्ठा machine_check_event mce_event_queue[MAX_MC_EVT];
	/* Queue क्रम delayed MCE UE events. */
	पूर्णांक mce_ue_count;
	काष्ठा machine_check_event  mce_ue_event_queue[MAX_MC_EVT];
पूर्ण;

/* Release flags क्रम get_mce_event() */
#घोषणा MCE_EVENT_RELEASE	true
#घोषणा MCE_EVENT_DONTRELEASE	false

काष्ठा pt_regs;
काष्ठा notअगरier_block;

बाह्य व्योम save_mce_event(काष्ठा pt_regs *regs, दीर्घ handled,
			   काष्ठा mce_error_info *mce_err, uपूर्णांक64_t nip,
			   uपूर्णांक64_t addr, uपूर्णांक64_t phys_addr);
बाह्य पूर्णांक get_mce_event(काष्ठा machine_check_event *mce, bool release);
बाह्य व्योम release_mce_event(व्योम);
बाह्य व्योम machine_check_queue_event(व्योम);
बाह्य व्योम machine_check_prपूर्णांक_event_info(काष्ठा machine_check_event *evt,
					   bool user_mode, bool in_guest);
अचिन्हित दीर्घ addr_to_pfn(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);
बाह्य व्योम mce_common_process_ue(काष्ठा pt_regs *regs,
				  काष्ठा mce_error_info *mce_err);
पूर्णांक mce_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक mce_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम flush_and_reload_slb(व्योम);
व्योम flush_erat(व्योम);
दीर्घ __machine_check_early_realmode_p7(काष्ठा pt_regs *regs);
दीर्घ __machine_check_early_realmode_p8(काष्ठा pt_regs *regs);
दीर्घ __machine_check_early_realmode_p9(काष्ठा pt_regs *regs);
दीर्घ __machine_check_early_realmode_p10(काष्ठा pt_regs *regs);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम mce_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mce_init(व्योम) अणु पूर्ण;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#पूर्ण_अगर /* __ASM_PPC64_MCE_H__ */
