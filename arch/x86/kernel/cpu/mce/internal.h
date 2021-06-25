<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __X86_MCE_INTERNAL_H__
#घोषणा __X86_MCE_INTERNAL_H__

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "mce: " fmt

#समावेश <linux/device.h>
#समावेश <यंत्र/mce.h>

/* Poपूर्णांकer to the installed machine check handler क्रम this CPU setup. */
बाह्य व्योम (*machine_check_vector)(काष्ठा pt_regs *);

क्रमागत severity_level अणु
	MCE_NO_SEVERITY,
	MCE_DEFERRED_SEVERITY,
	MCE_UCNA_SEVERITY = MCE_DEFERRED_SEVERITY,
	MCE_KEEP_SEVERITY,
	MCE_SOME_SEVERITY,
	MCE_AO_SEVERITY,
	MCE_UC_SEVERITY,
	MCE_AR_SEVERITY,
	MCE_PANIC_SEVERITY,
पूर्ण;

बाह्य काष्ठा blocking_notअगरier_head x86_mce_decoder_chain;

#घोषणा INITIAL_CHECK_INTERVAL	5 * 60 /* 5 minutes */

काष्ठा mce_evt_llist अणु
	काष्ठा llist_node llnode;
	काष्ठा mce mce;
पूर्ण;

व्योम mce_gen_pool_process(काष्ठा work_काष्ठा *__unused);
bool mce_gen_pool_empty(व्योम);
पूर्णांक mce_gen_pool_add(काष्ठा mce *mce);
पूर्णांक mce_gen_pool_init(व्योम);
काष्ठा llist_node *mce_gen_pool_prepare_records(व्योम);

बाह्य पूर्णांक (*mce_severity)(काष्ठा mce *a, काष्ठा pt_regs *regs,
			   पूर्णांक tolerant, अक्षर **msg, bool is_excp);
काष्ठा dentry *mce_get_debugfs_dir(व्योम);

बाह्य mce_banks_t mce_banks_ce_disabled;

#अगर_घोषित CONFIG_X86_MCE_INTEL
अचिन्हित दीर्घ cmci_पूर्णांकel_adjust_समयr(अचिन्हित दीर्घ पूर्णांकerval);
bool mce_पूर्णांकel_cmci_poll(व्योम);
व्योम mce_पूर्णांकel_hcpu_update(अचिन्हित दीर्घ cpu);
व्योम cmci_disable_bank(पूर्णांक bank);
व्योम पूर्णांकel_init_cmci(व्योम);
व्योम पूर्णांकel_init_lmce(व्योम);
व्योम पूर्णांकel_clear_lmce(व्योम);
bool पूर्णांकel_filter_mce(काष्ठा mce *m);
#अन्यथा
# define cmci_पूर्णांकel_adjust_समयr mce_adjust_समयr_शेष
अटल अंतरभूत bool mce_पूर्णांकel_cmci_poll(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम mce_पूर्णांकel_hcpu_update(अचिन्हित दीर्घ cpu) अणु पूर्ण
अटल अंतरभूत व्योम cmci_disable_bank(पूर्णांक bank) अणु पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_init_cmci(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_init_lmce(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_clear_lmce(व्योम) अणु पूर्ण
अटल अंतरभूत bool पूर्णांकel_filter_mce(काष्ठा mce *m) अणु वापस false; पूर्ण;
#पूर्ण_अगर

व्योम mce_समयr_kick(अचिन्हित दीर्घ पूर्णांकerval);

#अगर_घोषित CONFIG_ACPI_APEI
पूर्णांक apei_ग_लिखो_mce(काष्ठा mce *m);
sमाप_प्रकार apei_पढ़ो_mce(काष्ठा mce *m, u64 *record_id);
पूर्णांक apei_check_mce(व्योम);
पूर्णांक apei_clear_mce(u64 record_id);
#अन्यथा
अटल अंतरभूत पूर्णांक apei_ग_लिखो_mce(काष्ठा mce *m)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत sमाप_प्रकार apei_पढ़ो_mce(काष्ठा mce *m, u64 *record_id)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक apei_check_mce(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक apei_clear_mce(u64 record_id)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * We consider records to be equivalent अगर bank+status+addr+misc all match.
 * This is only used when the प्रणाली is going करोwn because of a fatal error
 * to aव्योम cluttering the console log with essentially repeated inक्रमmation.
 * In normal processing all errors seen are logged.
 */
अटल अंतरभूत bool mce_cmp(काष्ठा mce *m1, काष्ठा mce *m2)
अणु
	वापस m1->bank != m2->bank ||
		m1->status != m2->status ||
		m1->addr != m2->addr ||
		m1->misc != m2->misc;
पूर्ण

बाह्य काष्ठा device_attribute dev_attr_trigger;

#अगर_घोषित CONFIG_X86_MCELOG_LEGACY
व्योम mce_work_trigger(व्योम);
व्योम mce_रेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb);
व्योम mce_unरेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb);
#अन्यथा
अटल अंतरभूत व्योम mce_work_trigger(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम mce_रेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb)	अणु पूर्ण
अटल अंतरभूत व्योम mce_unरेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb)	अणु पूर्ण
#पूर्ण_अगर

काष्ठा mca_config अणु
	bool करोnt_log_ce;
	bool cmci_disabled;
	bool ignore_ce;
	bool prपूर्णांक_all;

	__u64 lmce_disabled		: 1,
	      disabled			: 1,
	      ser			: 1,
	      recovery			: 1,
	      bios_cmci_threshold	: 1,
	      __reserved		: 59;

	s8 bootlog;
	पूर्णांक tolerant;
	पूर्णांक monarch_समयout;
	पूर्णांक panic_समयout;
	u32 rip_msr;
पूर्ण;

बाह्य काष्ठा mca_config mca_cfg;
DECLARE_PER_CPU_READ_MOSTLY(अचिन्हित पूर्णांक, mce_num_banks);

काष्ठा mce_venकरोr_flags अणु
	/*
	 * Indicates that overflow conditions are not fatal, when set.
	 */
	__u64 overflow_recov	: 1,

	/*
	 * (AMD) SUCCOR stands क्रम S/W UnCorrectable error COntainment and
	 * Recovery. It indicates support क्रम data poisoning in HW and deferred
	 * error पूर्णांकerrupts.
	 */
	succor			: 1,

	/*
	 * (AMD) SMCA: This bit indicates support क्रम Scalable MCA which expands
	 * the रेजिस्टर space क्रम each MCA bank and also increases number of
	 * banks. Also, to accommodate the new banks and रेजिस्टरs, the MCA
	 * रेजिस्टर space is moved to a new MSR range.
	 */
	smca			: 1,

	/* AMD-style error thresholding banks present. */
	amd_threshold		: 1,

	__reserved_0		: 60;
पूर्ण;

बाह्य काष्ठा mce_venकरोr_flags mce_flags;

काष्ठा mca_msr_regs अणु
	u32 (*ctl)	(पूर्णांक bank);
	u32 (*status)	(पूर्णांक bank);
	u32 (*addr)	(पूर्णांक bank);
	u32 (*misc)	(पूर्णांक bank);
पूर्ण;

बाह्य काष्ठा mca_msr_regs msr_ops;

/* Decide whether to add MCE record to MCE event pool or filter it out. */
बाह्य bool filter_mce(काष्ठा mce *m);

#अगर_घोषित CONFIG_X86_MCE_AMD
बाह्य bool amd_filter_mce(काष्ठा mce *m);
#अन्यथा
अटल अंतरभूत bool amd_filter_mce(काष्ठा mce *m)			अणु वापस false; पूर्ण;
#पूर्ण_अगर

__visible bool ex_handler_rdmsr_fault(स्थिर काष्ठा exception_table_entry *fixup,
				      काष्ठा pt_regs *regs, पूर्णांक trapnr,
				      अचिन्हित दीर्घ error_code,
				      अचिन्हित दीर्घ fault_addr);

__visible bool ex_handler_wrmsr_fault(स्थिर काष्ठा exception_table_entry *fixup,
				      काष्ठा pt_regs *regs, पूर्णांक trapnr,
				      अचिन्हित दीर्घ error_code,
				      अचिन्हित दीर्घ fault_addr);

#पूर्ण_अगर /* __X86_MCE_INTERNAL_H__ */
