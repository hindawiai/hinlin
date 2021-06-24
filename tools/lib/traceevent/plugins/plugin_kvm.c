<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

#अगर_घोषित HAVE_UDIS86

#समावेश <udis86.h>

अटल ud_t ud;

अटल व्योम init_disassembler(व्योम)
अणु
	ud_init(&ud);
	ud_set_syntax(&ud, UD_SYN_ATT);
पूर्ण

अटल स्थिर अक्षर *disassemble(अचिन्हित अक्षर *insn, पूर्णांक len, uपूर्णांक64_t rip,
			       पूर्णांक cr0_pe, पूर्णांक eflags_vm,
			       पूर्णांक cs_d, पूर्णांक cs_l)
अणु
	पूर्णांक mode;

	अगर (!cr0_pe)
		mode = 16;
	अन्यथा अगर (eflags_vm)
		mode = 16;
	अन्यथा अगर (cs_l)
		mode = 64;
	अन्यथा अगर (cs_d)
		mode = 32;
	अन्यथा
		mode = 16;

	ud_set_pc(&ud, rip);
	ud_set_mode(&ud, mode);
	ud_set_input_buffer(&ud, insn, len);
	ud_disassemble(&ud);
	वापस ud_insn_यंत्र(&ud);
पूर्ण

#अन्यथा

अटल व्योम init_disassembler(व्योम)
अणु
पूर्ण

अटल स्थिर अक्षर *disassemble(अचिन्हित अक्षर *insn, पूर्णांक len, uपूर्णांक64_t rip,
			       पूर्णांक cr0_pe, पूर्णांक eflags_vm,
			       पूर्णांक cs_d, पूर्णांक cs_l)
अणु
	अटल अक्षर out[15*3+1];
	पूर्णांक i;

	क्रम (i = 0; i < len; ++i)
		प्र_लिखो(out + i * 3, "%02x ", insn[i]);
	out[len*3-1] = '\0';
	वापस out;
पूर्ण

#पूर्ण_अगर


#घोषणा VMX_EXIT_REASONS			\
	_ER(EXCEPTION_NMI,	 0)		\
	_ER(EXTERNAL_INTERRUPT,	 1)		\
	_ER(TRIPLE_FAULT,	 2)		\
	_ER(PENDING_INTERRUPT,	 7)		\
	_ER(NMI_WINDOW,		 8)		\
	_ER(TASK_SWITCH,	 9)		\
	_ER(CPUID,		 10)		\
	_ER(HLT,		 12)		\
	_ER(INVD,		 13)		\
	_ER(INVLPG,		 14)		\
	_ER(RDPMC,		 15)		\
	_ER(RDTSC,		 16)		\
	_ER(VMCALL,		 18)		\
	_ER(VMCLEAR,		 19)		\
	_ER(VMLAUNCH,		 20)		\
	_ER(VMPTRLD,		 21)		\
	_ER(VMPTRST,		 22)		\
	_ER(VMREAD,		 23)		\
	_ER(VMRESUME,		 24)		\
	_ER(VMWRITE,		 25)		\
	_ER(VMOFF,		 26)		\
	_ER(VMON,		 27)		\
	_ER(CR_ACCESS,		 28)		\
	_ER(DR_ACCESS,		 29)		\
	_ER(IO_INSTRUCTION,	 30)		\
	_ER(MSR_READ,		 31)		\
	_ER(MSR_WRITE,		 32)		\
	_ER(MWAIT_INSTRUCTION,	 36)		\
	_ER(MONITOR_INSTRUCTION, 39)		\
	_ER(PAUSE_INSTRUCTION,	 40)		\
	_ER(MCE_DURING_VMENTRY,	 41)		\
	_ER(TPR_BELOW_THRESHOLD, 43)		\
	_ER(APIC_ACCESS,	 44)		\
	_ER(EOI_INDUCED,	 45)		\
	_ER(EPT_VIOLATION,	 48)		\
	_ER(EPT_MISCONFIG,	 49)		\
	_ER(INVEPT,		 50)		\
	_ER(PREEMPTION_TIMER,	 52)		\
	_ER(WBINVD,		 54)		\
	_ER(XSETBV,		 55)		\
	_ER(APIC_WRITE,		 56)		\
	_ER(INVPCID,		 58)		\
	_ER(PML_FULL,		 62)		\
	_ER(XSAVES,		 63)		\
	_ER(XRSTORS,		 64)

#घोषणा SVM_EXIT_REASONS \
	_ER(EXIT_READ_CR0,	0x000)		\
	_ER(EXIT_READ_CR3,	0x003)		\
	_ER(EXIT_READ_CR4,	0x004)		\
	_ER(EXIT_READ_CR8,	0x008)		\
	_ER(EXIT_WRITE_CR0,	0x010)		\
	_ER(EXIT_WRITE_CR3,	0x013)		\
	_ER(EXIT_WRITE_CR4,	0x014)		\
	_ER(EXIT_WRITE_CR8,	0x018)		\
	_ER(EXIT_READ_DR0,	0x020)		\
	_ER(EXIT_READ_DR1,	0x021)		\
	_ER(EXIT_READ_DR2,	0x022)		\
	_ER(EXIT_READ_DR3,	0x023)		\
	_ER(EXIT_READ_DR4,	0x024)		\
	_ER(EXIT_READ_DR5,	0x025)		\
	_ER(EXIT_READ_DR6,	0x026)		\
	_ER(EXIT_READ_DR7,	0x027)		\
	_ER(EXIT_WRITE_DR0,	0x030)		\
	_ER(EXIT_WRITE_DR1,	0x031)		\
	_ER(EXIT_WRITE_DR2,	0x032)		\
	_ER(EXIT_WRITE_DR3,	0x033)		\
	_ER(EXIT_WRITE_DR4,	0x034)		\
	_ER(EXIT_WRITE_DR5,	0x035)		\
	_ER(EXIT_WRITE_DR6,	0x036)		\
	_ER(EXIT_WRITE_DR7,	0x037)		\
	_ER(EXIT_EXCP_DE,	0x040)		\
	_ER(EXIT_EXCP_DB,	0x041)		\
	_ER(EXIT_EXCP_BP,	0x043)		\
	_ER(EXIT_EXCP_OF,	0x044)		\
	_ER(EXIT_EXCP_BR,	0x045)		\
	_ER(EXIT_EXCP_UD,	0x046)		\
	_ER(EXIT_EXCP_NM,	0x047)		\
	_ER(EXIT_EXCP_DF,	0x048)		\
	_ER(EXIT_EXCP_TS,	0x04a)		\
	_ER(EXIT_EXCP_NP,	0x04b)		\
	_ER(EXIT_EXCP_SS,	0x04c)		\
	_ER(EXIT_EXCP_GP,	0x04d)		\
	_ER(EXIT_EXCP_PF,	0x04e)		\
	_ER(EXIT_EXCP_MF,	0x050)		\
	_ER(EXIT_EXCP_AC,	0x051)		\
	_ER(EXIT_EXCP_MC,	0x052)		\
	_ER(EXIT_EXCP_XF,	0x053)		\
	_ER(EXIT_INTR,		0x060)		\
	_ER(EXIT_NMI,		0x061)		\
	_ER(EXIT_SMI,		0x062)		\
	_ER(EXIT_INIT,		0x063)		\
	_ER(EXIT_VINTR,		0x064)		\
	_ER(EXIT_CR0_SEL_WRITE,	0x065)		\
	_ER(EXIT_IDTR_READ,	0x066)		\
	_ER(EXIT_GDTR_READ,	0x067)		\
	_ER(EXIT_LDTR_READ,	0x068)		\
	_ER(EXIT_TR_READ,	0x069)		\
	_ER(EXIT_IDTR_WRITE,	0x06a)		\
	_ER(EXIT_GDTR_WRITE,	0x06b)		\
	_ER(EXIT_LDTR_WRITE,	0x06c)		\
	_ER(EXIT_TR_WRITE,	0x06d)		\
	_ER(EXIT_RDTSC,		0x06e)		\
	_ER(EXIT_RDPMC,		0x06f)		\
	_ER(EXIT_PUSHF,		0x070)		\
	_ER(EXIT_POPF,		0x071)		\
	_ER(EXIT_CPUID,		0x072)		\
	_ER(EXIT_RSM,		0x073)		\
	_ER(EXIT_IRET,		0x074)		\
	_ER(EXIT_SWINT,		0x075)		\
	_ER(EXIT_INVD,		0x076)		\
	_ER(EXIT_PAUSE,		0x077)		\
	_ER(EXIT_HLT,		0x078)		\
	_ER(EXIT_INVLPG,	0x079)		\
	_ER(EXIT_INVLPGA,	0x07a)		\
	_ER(EXIT_IOIO,		0x07b)		\
	_ER(EXIT_MSR,		0x07c)		\
	_ER(EXIT_TASK_SWITCH,	0x07d)		\
	_ER(EXIT_FERR_FREEZE,	0x07e)		\
	_ER(EXIT_SHUTDOWN,	0x07f)		\
	_ER(EXIT_VMRUN,		0x080)		\
	_ER(EXIT_VMMCALL,	0x081)		\
	_ER(EXIT_VMLOAD,	0x082)		\
	_ER(EXIT_VMSAVE,	0x083)		\
	_ER(EXIT_STGI,		0x084)		\
	_ER(EXIT_CLGI,		0x085)		\
	_ER(EXIT_SKINIT,	0x086)		\
	_ER(EXIT_RDTSCP,	0x087)		\
	_ER(EXIT_ICEBP,		0x088)		\
	_ER(EXIT_WBINVD,	0x089)		\
	_ER(EXIT_MONITOR,	0x08a)		\
	_ER(EXIT_MWAIT,		0x08b)		\
	_ER(EXIT_MWAIT_COND,	0x08c)		\
	_ER(EXIT_XSETBV,	0x08d)		\
	_ER(EXIT_NPF, 		0x400)		\
	_ER(EXIT_AVIC_INCOMPLETE_IPI,		0x401)	\
	_ER(EXIT_AVIC_UNACCELERATED_ACCESS,	0x402)	\
	_ER(EXIT_ERR,		-1)

#घोषणा _ER(reason, val)	अणु #reason, val पूर्ण,
काष्ठा str_values अणु
	स्थिर अक्षर	*str;
	पूर्णांक		val;
पूर्ण;

अटल काष्ठा str_values vmx_निकास_reasons[] = अणु
	VMX_EXIT_REASONS
	अणु शून्य, -1पूर्ण
पूर्ण;

अटल काष्ठा str_values svm_निकास_reasons[] = अणु
	SVM_EXIT_REASONS
	अणु शून्य, -1पूर्ण
पूर्ण;

अटल काष्ठा isa_निकास_reasons अणु
	अचिन्हित isa;
	काष्ठा str_values *strings;
पूर्ण isa_निकास_reasons[] = अणु
	अणु .isa = 1, .strings = vmx_निकास_reasons पूर्ण,
	अणु .isa = 2, .strings = svm_निकास_reasons पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर अक्षर *find_निकास_reason(अचिन्हित isa, पूर्णांक val)
अणु
	काष्ठा str_values *strings = शून्य;
	पूर्णांक i;

	क्रम (i = 0; isa_निकास_reasons[i].strings; ++i)
		अगर (isa_निकास_reasons[i].isa == isa) अणु
			strings = isa_निकास_reasons[i].strings;
			अवरोध;
		पूर्ण
	अगर (!strings)
		वापस "UNKNOWN-ISA";
	क्रम (i = 0; strings[i].str; i++)
		अगर (strings[i].val == val)
			अवरोध;

	वापस strings[i].str;
पूर्ण

अटल पूर्णांक prपूर्णांक_निकास_reason(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			     काष्ठा tep_event *event, स्थिर अक्षर *field)
अणु
	अचिन्हित दीर्घ दीर्घ isa;
	अचिन्हित दीर्घ दीर्घ val;
	स्थिर अक्षर *reason;

	अगर (tep_get_field_val(s, event, field, record, &val, 1) < 0)
		वापस -1;

	अगर (tep_get_field_val(s, event, "isa", record, &isa, 0) < 0)
		isa = 1;

	reason = find_निकास_reason(isa, val);
	अगर (reason)
		trace_seq_म_लिखो(s, "reason %s", reason);
	अन्यथा
		trace_seq_म_लिखो(s, "reason UNKNOWN (%llu)", val);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_निकास_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			    काष्ठा tep_event *event, व्योम *context)
अणु
	अचिन्हित दीर्घ दीर्घ info1 = 0, info2 = 0;

	अगर (prपूर्णांक_निकास_reason(s, record, event, "exit_reason") < 0)
		वापस -1;

	tep_prपूर्णांक_num_field(s, " rip 0x%lx", event, "guest_rip", record, 1);

	अगर (tep_get_field_val(s, event, "info1", record, &info1, 0) >= 0
	    && tep_get_field_val(s, event, "info2", record, &info2, 0) >= 0)
		trace_seq_म_लिखो(s, " info %llx %llx", info1, info2);

	वापस 0;
पूर्ण

#घोषणा KVM_EMUL_INSN_F_CR0_PE (1 << 0)
#घोषणा KVM_EMUL_INSN_F_EFL_VM (1 << 1)
#घोषणा KVM_EMUL_INSN_F_CS_D   (1 << 2)
#घोषणा KVM_EMUL_INSN_F_CS_L   (1 << 3)

अटल पूर्णांक kvm_emulate_insn_handler(काष्ठा trace_seq *s,
				    काष्ठा tep_record *record,
				    काष्ठा tep_event *event, व्योम *context)
अणु
	अचिन्हित दीर्घ दीर्घ rip, csbase, len, flags, failed;
	पूर्णांक llen;
	uपूर्णांक8_t *insn;
	स्थिर अक्षर *disयंत्र;

	अगर (tep_get_field_val(s, event, "rip", record, &rip, 1) < 0)
		वापस -1;

	अगर (tep_get_field_val(s, event, "csbase", record, &csbase, 1) < 0)
		वापस -1;

	अगर (tep_get_field_val(s, event, "len", record, &len, 1) < 0)
		वापस -1;

	अगर (tep_get_field_val(s, event, "flags", record, &flags, 1) < 0)
		वापस -1;

	अगर (tep_get_field_val(s, event, "failed", record, &failed, 1) < 0)
		वापस -1;

	insn = tep_get_field_raw(s, event, "insn", record, &llen, 1);
	अगर (!insn)
		वापस -1;

	disयंत्र = disassemble(insn, len, rip,
			     flags & KVM_EMUL_INSN_F_CR0_PE,
			     flags & KVM_EMUL_INSN_F_EFL_VM,
			     flags & KVM_EMUL_INSN_F_CS_D,
			     flags & KVM_EMUL_INSN_F_CS_L);

	trace_seq_म_लिखो(s, "%llx:%llx: %s%s", csbase, rip, disयंत्र,
			 failed ? " FAIL" : "");
	वापस 0;
पूर्ण


अटल पूर्णांक kvm_nested_vmनिकास_inject_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
					    काष्ठा tep_event *event, व्योम *context)
अणु
	अगर (prपूर्णांक_निकास_reason(s, record, event, "exit_code") < 0)
		वापस -1;

	tep_prपूर्णांक_num_field(s, " info1 %llx", event, "exit_info1", record, 1);
	tep_prपूर्णांक_num_field(s, " info2 %llx", event, "exit_info2", record, 1);
	tep_prपूर्णांक_num_field(s, " int_info %llx", event, "exit_int_info", record, 1);
	tep_prपूर्णांक_num_field(s, " int_info_err %llx", event, "exit_int_info_err", record, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_nested_vmनिकास_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
				     काष्ठा tep_event *event, व्योम *context)
अणु
	tep_prपूर्णांक_num_field(s, "rip %llx ", event, "rip", record, 1);

	वापस kvm_nested_vmनिकास_inject_handler(s, record, event, context);
पूर्ण

जोड़ kvm_mmu_page_role अणु
	अचिन्हित word;
	काष्ठा अणु
		अचिन्हित level:4;
		अचिन्हित cr4_pae:1;
		अचिन्हित quadrant:2;
		अचिन्हित direct:1;
		अचिन्हित access:3;
		अचिन्हित invalid:1;
		अचिन्हित nxe:1;
		अचिन्हित cr0_wp:1;
		अचिन्हित smep_and_not_wp:1;
		अचिन्हित smap_and_not_wp:1;
		अचिन्हित pad_क्रम_nice_hex_output:8;
		अचिन्हित smm:8;
	पूर्ण;
पूर्ण;

अटल पूर्णांक kvm_mmu_prपूर्णांक_role(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			      काष्ठा tep_event *event, व्योम *context)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	अटल स्थिर अक्षर *access_str[] = अणु
		"---", "--x", "w--", "w-x", "-u-", "-ux", "wu-", "wux"
	पूर्ण;
	जोड़ kvm_mmu_page_role role;

	अगर (tep_get_field_val(s, event, "role", record, &val, 1) < 0)
		वापस -1;

	role.word = (पूर्णांक)val;

	/*
	 * We can only use the काष्ठाure अगर file is of the same
	 * endianness.
	 */
	अगर (tep_is_file_bigendian(event->tep) ==
	    tep_is_local_bigendian(event->tep)) अणु

		trace_seq_म_लिखो(s, "%u q%u%s %s%s %spae %snxe %swp%s%s%s",
				 role.level,
				 role.quadrant,
				 role.direct ? " direct" : "",
				 access_str[role.access],
				 role.invalid ? " invalid" : "",
				 role.cr4_pae ? "" : "!",
				 role.nxe ? "" : "!",
				 role.cr0_wp ? "" : "!",
				 role.smep_and_not_wp ? " smep" : "",
				 role.smap_and_not_wp ? " smap" : "",
				 role.smm ? " smm" : "");
	पूर्ण अन्यथा
		trace_seq_म_लिखो(s, "WORD: %08x", role.word);

	tep_prपूर्णांक_num_field(s, " root %u ",  event,
			    "root_count", record, 1);

	अगर (tep_get_field_val(s, event, "unsync", record, &val, 1) < 0)
		वापस -1;

	trace_seq_म_लिखो(s, "%s%c",  val ? "unsync" : "sync", 0);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_mmu_get_page_handler(काष्ठा trace_seq *s,
				    काष्ठा tep_record *record,
				    काष्ठा tep_event *event, व्योम *context)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	अगर (tep_get_field_val(s, event, "created", record, &val, 1) < 0)
		वापस -1;

	trace_seq_म_लिखो(s, "%s ", val ? "new" : "existing");

	अगर (tep_get_field_val(s, event, "gfn", record, &val, 1) < 0)
		वापस -1;

	trace_seq_म_लिखो(s, "sp gfn %llx ", val);
	वापस kvm_mmu_prपूर्णांक_role(s, record, event, context);
पूर्ण

#घोषणा PT_WRITABLE_SHIFT 1
#घोषणा PT_WRITABLE_MASK (1ULL << PT_WRITABLE_SHIFT)

अटल अचिन्हित दीर्घ दीर्घ
process_is_writable_pte(काष्ठा trace_seq *s, अचिन्हित दीर्घ दीर्घ *args)
अणु
	अचिन्हित दीर्घ pte = args[0];
	वापस pte & PT_WRITABLE_MASK;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	init_disassembler();

	tep_रेजिस्टर_event_handler(tep, -1, "kvm", "kvm_exit",
				   kvm_निकास_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvm", "kvm_emulate_insn",
				   kvm_emulate_insn_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvm", "kvm_nested_vmexit",
				   kvm_nested_vmनिकास_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvm", "kvm_nested_vmexit_inject",
				   kvm_nested_vmनिकास_inject_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_get_page",
				   kvm_mmu_get_page_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_sync_page",
				   kvm_mmu_prपूर्णांक_role, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1,
				   "kvmmmu", "kvm_mmu_unsync_page",
				   kvm_mmu_prपूर्णांक_role, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_zap_page",
				   kvm_mmu_prपूर्णांक_role, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kvmmmu",
			"kvm_mmu_prepare_zap_page", kvm_mmu_prपूर्णांक_role,
			शून्य);

	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process_is_writable_pte,
				    TEP_FUNC_ARG_INT,
				    "is_writable_pte",
				    TEP_FUNC_ARG_LONG,
				    TEP_FUNC_ARG_VOID);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1, "kvm", "kvm_exit",
				     kvm_निकास_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvm", "kvm_emulate_insn",
				     kvm_emulate_insn_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvm", "kvm_nested_vmexit",
				     kvm_nested_vmनिकास_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvm", "kvm_nested_vmexit_inject",
				     kvm_nested_vmनिकास_inject_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_get_page",
				     kvm_mmu_get_page_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_sync_page",
				     kvm_mmu_prपूर्णांक_role, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1,
				     "kvmmmu", "kvm_mmu_unsync_page",
				     kvm_mmu_prपूर्णांक_role, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvmmmu", "kvm_mmu_zap_page",
				     kvm_mmu_prपूर्णांक_role, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kvmmmu",
			"kvm_mmu_prepare_zap_page", kvm_mmu_prपूर्णांक_role,
			शून्य);

	tep_unरेजिस्टर_prपूर्णांक_function(tep, process_is_writable_pte,
				      "is_writable_pte");
पूर्ण
