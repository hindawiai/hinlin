<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * x86_emulate.h
 *
 * Generic x86 (32-bit and 64-bit) inकाष्ठाion decoder and emulator.
 *
 * Copyright (c) 2005 Keir Fraser
 *
 * From: xen-unstable 10676:af9809f51f81a3c43f276f00c81a52ef558afda4
 */

#अगर_अघोषित _ASM_X86_KVM_X86_EMULATE_H
#घोषणा _ASM_X86_KVM_X86_EMULATE_H

#समावेश <यंत्र/desc_defs.h>

काष्ठा x86_emulate_ctxt;
क्रमागत x86_पूर्णांकercept;
क्रमागत x86_पूर्णांकercept_stage;

काष्ठा x86_exception अणु
	u8 vector;
	bool error_code_valid;
	u16 error_code;
	bool nested_page_fault;
	u64 address; /* cr2 or nested page fault gpa */
	u8 async_page_fault;
पूर्ण;

/*
 * This काष्ठा is used to carry enough inक्रमmation from the inकाष्ठाion
 * decoder to मुख्य KVM so that a decision can be made whether the
 * inकाष्ठाion needs to be पूर्णांकercepted or not.
 */
काष्ठा x86_inकाष्ठाion_info अणु
	u8  पूर्णांकercept;          /* which पूर्णांकercept                      */
	u8  rep_prefix;         /* rep prefix?                          */
	u8  modrm_mod;		/* mod part of modrm			*/
	u8  modrm_reg;          /* index of रेजिस्टर used               */
	u8  modrm_rm;		/* rm part of modrm			*/
	u64 src_val;            /* value of source opeअक्रम              */
	u64 dst_val;            /* value of destination opeअक्रम         */
	u8  src_bytes;          /* size of source opeअक्रम               */
	u8  dst_bytes;          /* size of destination opeअक्रम          */
	u8  ad_bytes;           /* size of src/dst address              */
	u64 next_rip;           /* rip following the inकाष्ठाion        */
पूर्ण;

/*
 * x86_emulate_ops:
 *
 * These operations represent the inकाष्ठाion emulator's पूर्णांकerface to memory.
 * There are two categories of operation: those that act on ordinary memory
 * regions (*_std), and those that act on memory regions known to require
 * special treaपंचांगent or emulation (*_emulated).
 *
 * The emulator assumes that an inकाष्ठाion accesses only one 'emulated memory'
 * location, that this location is the given linear faulting address (cr2), and
 * that this is one of the inकाष्ठाion's data opeअक्रमs. Inकाष्ठाion fetches and
 * stack operations are assumed never to access emulated memory. The emulator
 * स्वतःmatically deduces which opeअक्रम of a string-move operation is accessing
 * emulated memory, and assumes that the other opeअक्रम accesses normal memory.
 *
 * NOTES:
 *  1. The emulator isn't very smart about emulated vs. standard memory.
 *     'Emulated memory' access addresses should be checked क्रम sanity.
 *     'Normal memory' accesses may fault, and the caller must arrange to
 *     detect and handle reentrancy पूर्णांकo the emulator via recursive faults.
 *     Accesses may be unaligned and may cross page boundaries.
 *  2. If the access fails (cannot emulate, or a standard access faults) then
 *     it is up to the memop to propagate the fault to the guest VM via
 *     some out-of-band mechanism, unknown to the emulator. The memop संकेतs
 *     failure by वापसing X86EMUL_PROPAGATE_FAULT to the emulator, which will
 *     then immediately bail.
 *  3. Valid access sizes are 1, 2, 4 and 8 bytes. On x86/32 प्रणालीs only
 *     cmpxchg8b_emulated need support 8-byte accesses.
 *  4. The emulator cannot handle 64-bit mode emulation on an x86/32 प्रणाली.
 */
/* Access completed successfully: जारी emulation as normal. */
#घोषणा X86EMUL_CONTINUE        0
/* Access is unhandleable: bail from emulation and वापस error to caller. */
#घोषणा X86EMUL_UNHANDLEABLE    1
/* Terminate emulation but वापस success to the caller. */
#घोषणा X86EMUL_PROPAGATE_FAULT 2 /* propagate a generated fault to guest */
#घोषणा X86EMUL_RETRY_INSTR     3 /* retry the inकाष्ठाion क्रम some reason */
#घोषणा X86EMUL_CMPXCHG_FAILED  4 /* cmpxchg did not see expected value */
#घोषणा X86EMUL_IO_NEEDED       5 /* IO is needed to complete emulation */
#घोषणा X86EMUL_INTERCEPTED     6 /* Intercepted by nested VMCB/VMCS */

काष्ठा x86_emulate_ops अणु
	/*
	 * पढ़ो_gpr: पढ़ो a general purpose रेजिस्टर (rax - r15)
	 *
	 * @reg: gpr number.
	 */
	uदीर्घ (*पढ़ो_gpr)(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित reg);
	/*
	 * ग_लिखो_gpr: ग_लिखो a general purpose रेजिस्टर (rax - r15)
	 *
	 * @reg: gpr number.
	 * @val: value to ग_लिखो.
	 */
	व्योम (*ग_लिखो_gpr)(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित reg, uदीर्घ val);
	/*
	 * पढ़ो_std: Read bytes of standard (non-emulated/special) memory.
	 *           Used क्रम descriptor पढ़ोing.
	 *  @addr:  [IN ] Linear address from which to पढ़ो.
	 *  @val:   [OUT] Value पढ़ो from memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to पढ़ो from memory.
	 *  @प्रणाली:[IN ] Whether the access is क्रमced to be at CPL0.
	 */
	पूर्णांक (*पढ़ो_std)(काष्ठा x86_emulate_ctxt *ctxt,
			अचिन्हित दीर्घ addr, व्योम *val,
			अचिन्हित पूर्णांक bytes,
			काष्ठा x86_exception *fault, bool प्रणाली);

	/*
	 * पढ़ो_phys: Read bytes of standard (non-emulated/special) memory.
	 *            Used क्रम descriptor पढ़ोing.
	 *  @addr:  [IN ] Physical address from which to पढ़ो.
	 *  @val:   [OUT] Value पढ़ो from memory.
	 *  @bytes: [IN ] Number of bytes to पढ़ो from memory.
	 */
	पूर्णांक (*पढ़ो_phys)(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित दीर्घ addr,
			व्योम *val, अचिन्हित पूर्णांक bytes);

	/*
	 * ग_लिखो_std: Write bytes of standard (non-emulated/special) memory.
	 *            Used क्रम descriptor writing.
	 *  @addr:  [IN ] Linear address to which to ग_लिखो.
	 *  @val:   [OUT] Value ग_लिखो to memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to ग_लिखो to memory.
	 *  @प्रणाली:[IN ] Whether the access is क्रमced to be at CPL0.
	 */
	पूर्णांक (*ग_लिखो_std)(काष्ठा x86_emulate_ctxt *ctxt,
			 अचिन्हित दीर्घ addr, व्योम *val, अचिन्हित पूर्णांक bytes,
			 काष्ठा x86_exception *fault, bool प्रणाली);
	/*
	 * fetch: Read bytes of standard (non-emulated/special) memory.
	 *        Used क्रम inकाष्ठाion fetch.
	 *  @addr:  [IN ] Linear address from which to पढ़ो.
	 *  @val:   [OUT] Value पढ़ो from memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to पढ़ो from memory.
	 */
	पूर्णांक (*fetch)(काष्ठा x86_emulate_ctxt *ctxt,
		     अचिन्हित दीर्घ addr, व्योम *val, अचिन्हित पूर्णांक bytes,
		     काष्ठा x86_exception *fault);

	/*
	 * पढ़ो_emulated: Read bytes from emulated/special memory area.
	 *  @addr:  [IN ] Linear address from which to पढ़ो.
	 *  @val:   [OUT] Value पढ़ो from memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to पढ़ो from memory.
	 */
	पूर्णांक (*पढ़ो_emulated)(काष्ठा x86_emulate_ctxt *ctxt,
			     अचिन्हित दीर्घ addr, व्योम *val, अचिन्हित पूर्णांक bytes,
			     काष्ठा x86_exception *fault);

	/*
	 * ग_लिखो_emulated: Write bytes to emulated/special memory area.
	 *  @addr:  [IN ] Linear address to which to ग_लिखो.
	 *  @val:   [IN ] Value to ग_लिखो to memory (low-order bytes used as
	 *                required).
	 *  @bytes: [IN ] Number of bytes to ग_लिखो to memory.
	 */
	पूर्णांक (*ग_लिखो_emulated)(काष्ठा x86_emulate_ctxt *ctxt,
			      अचिन्हित दीर्घ addr, स्थिर व्योम *val,
			      अचिन्हित पूर्णांक bytes,
			      काष्ठा x86_exception *fault);

	/*
	 * cmpxchg_emulated: Emulate an atomic (LOCKed) CMPXCHG operation on an
	 *                   emulated/special memory area.
	 *  @addr:  [IN ] Linear address to access.
	 *  @old:   [IN ] Value expected to be current at @addr.
	 *  @new:   [IN ] Value to ग_लिखो to @addr.
	 *  @bytes: [IN ] Number of bytes to access using CMPXCHG.
	 */
	पूर्णांक (*cmpxchg_emulated)(काष्ठा x86_emulate_ctxt *ctxt,
				अचिन्हित दीर्घ addr,
				स्थिर व्योम *old,
				स्थिर व्योम *new,
				अचिन्हित पूर्णांक bytes,
				काष्ठा x86_exception *fault);
	व्योम (*invlpg)(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ addr);

	पूर्णांक (*pio_in_emulated)(काष्ठा x86_emulate_ctxt *ctxt,
			       पूर्णांक size, अचिन्हित लघु port, व्योम *val,
			       अचिन्हित पूर्णांक count);

	पूर्णांक (*pio_out_emulated)(काष्ठा x86_emulate_ctxt *ctxt,
				पूर्णांक size, अचिन्हित लघु port, स्थिर व्योम *val,
				अचिन्हित पूर्णांक count);

	bool (*get_segment)(काष्ठा x86_emulate_ctxt *ctxt, u16 *selector,
			    काष्ठा desc_काष्ठा *desc, u32 *base3, पूर्णांक seg);
	व्योम (*set_segment)(काष्ठा x86_emulate_ctxt *ctxt, u16 selector,
			    काष्ठा desc_काष्ठा *desc, u32 base3, पूर्णांक seg);
	अचिन्हित दीर्घ (*get_cached_segment_base)(काष्ठा x86_emulate_ctxt *ctxt,
						 पूर्णांक seg);
	व्योम (*get_gdt)(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt);
	व्योम (*get_idt)(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt);
	व्योम (*set_gdt)(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt);
	व्योम (*set_idt)(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt);
	uदीर्घ (*get_cr)(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक cr);
	पूर्णांक (*set_cr)(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक cr, uदीर्घ val);
	पूर्णांक (*cpl)(काष्ठा x86_emulate_ctxt *ctxt);
	व्योम (*get_dr)(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक dr, uदीर्घ *dest);
	पूर्णांक (*set_dr)(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक dr, uदीर्घ value);
	u64 (*get_smbase)(काष्ठा x86_emulate_ctxt *ctxt);
	व्योम (*set_smbase)(काष्ठा x86_emulate_ctxt *ctxt, u64 smbase);
	पूर्णांक (*set_msr)(काष्ठा x86_emulate_ctxt *ctxt, u32 msr_index, u64 data);
	पूर्णांक (*get_msr)(काष्ठा x86_emulate_ctxt *ctxt, u32 msr_index, u64 *pdata);
	पूर्णांक (*check_pmc)(काष्ठा x86_emulate_ctxt *ctxt, u32 pmc);
	पूर्णांक (*पढ़ो_pmc)(काष्ठा x86_emulate_ctxt *ctxt, u32 pmc, u64 *pdata);
	व्योम (*halt)(काष्ठा x86_emulate_ctxt *ctxt);
	व्योम (*wbinvd)(काष्ठा x86_emulate_ctxt *ctxt);
	पूर्णांक (*fix_hypercall)(काष्ठा x86_emulate_ctxt *ctxt);
	पूर्णांक (*पूर्णांकercept)(काष्ठा x86_emulate_ctxt *ctxt,
			 काष्ठा x86_inकाष्ठाion_info *info,
			 क्रमागत x86_पूर्णांकercept_stage stage);

	bool (*get_cpuid)(काष्ठा x86_emulate_ctxt *ctxt, u32 *eax, u32 *ebx,
			  u32 *ecx, u32 *edx, bool exact_only);
	bool (*guest_has_दीर्घ_mode)(काष्ठा x86_emulate_ctxt *ctxt);
	bool (*guest_has_movbe)(काष्ठा x86_emulate_ctxt *ctxt);
	bool (*guest_has_fxsr)(काष्ठा x86_emulate_ctxt *ctxt);

	व्योम (*set_nmi_mask)(काष्ठा x86_emulate_ctxt *ctxt, bool masked);

	अचिन्हित (*get_hflags)(काष्ठा x86_emulate_ctxt *ctxt);
	व्योम (*set_hflags)(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित hflags);
	पूर्णांक (*pre_leave_smm)(काष्ठा x86_emulate_ctxt *ctxt,
			     स्थिर अक्षर *smstate);
	व्योम (*post_leave_smm)(काष्ठा x86_emulate_ctxt *ctxt);
	पूर्णांक (*set_xcr)(काष्ठा x86_emulate_ctxt *ctxt, u32 index, u64 xcr);
पूर्ण;

प्रकार u32 __attribute__((vector_size(16))) sse128_t;

/* Type, address-of, and value of an inकाष्ठाion's opeअक्रम. */
काष्ठा opeअक्रम अणु
	क्रमागत अणु OP_REG, OP_MEM, OP_MEM_STR, OP_IMM, OP_XMM, OP_MM, OP_NONE पूर्ण type;
	अचिन्हित पूर्णांक bytes;
	अचिन्हित पूर्णांक count;
	जोड़ अणु
		अचिन्हित दीर्घ orig_val;
		u64 orig_val64;
	पूर्ण;
	जोड़ अणु
		अचिन्हित दीर्घ *reg;
		काष्ठा segmented_address अणु
			uदीर्घ ea;
			अचिन्हित seg;
		पूर्ण mem;
		अचिन्हित xmm;
		अचिन्हित mm;
	पूर्ण addr;
	जोड़ अणु
		अचिन्हित दीर्घ val;
		u64 val64;
		अक्षर valptr[माप(sse128_t)];
		sse128_t vec_val;
		u64 mm_val;
		व्योम *data;
	पूर्ण;
पूर्ण;

काष्ठा fetch_cache अणु
	u8 data[15];
	u8 *ptr;
	u8 *end;
पूर्ण;

काष्ठा पढ़ो_cache अणु
	u8 data[1024];
	अचिन्हित दीर्घ pos;
	अचिन्हित दीर्घ end;
पूर्ण;

/* Execution mode, passed to the emulator. */
क्रमागत x86emul_mode अणु
	X86EMUL_MODE_REAL,	/* Real mode.             */
	X86EMUL_MODE_VM86,	/* Virtual 8086 mode.     */
	X86EMUL_MODE_PROT16,	/* 16-bit रक्षित mode. */
	X86EMUL_MODE_PROT32,	/* 32-bit रक्षित mode. */
	X86EMUL_MODE_PROT64,	/* 64-bit (दीर्घ) mode.    */
पूर्ण;

/* These match some of the HF_* flags defined in kvm_host.h  */
#घोषणा X86EMUL_GUEST_MASK           (1 << 5) /* VCPU is in guest-mode */
#घोषणा X86EMUL_SMM_MASK             (1 << 6)
#घोषणा X86EMUL_SMM_INSIDE_NMI_MASK  (1 << 7)

/*
 * fastop functions are declared as taking a never-defined fastop parameter,
 * so they can't be called from C directly.
 */
काष्ठा fastop;

प्रकार व्योम (*fastop_t)(काष्ठा fastop *);

काष्ठा x86_emulate_ctxt अणु
	व्योम *vcpu;
	स्थिर काष्ठा x86_emulate_ops *ops;

	/* Register state beक्रमe/after emulation. */
	अचिन्हित दीर्घ eflags;
	अचिन्हित दीर्घ eip; /* eip beक्रमe inकाष्ठाion emulation */
	/* Emulated execution mode, represented by an X86EMUL_MODE value. */
	क्रमागत x86emul_mode mode;

	/* पूर्णांकerruptibility state, as a result of execution of STI or MOV SS */
	पूर्णांक पूर्णांकerruptibility;

	bool perm_ok; /* करो not check permissions अगर true */
	bool tf;	/* TF value beक्रमe inकाष्ठाion (after क्रम syscall/sysret) */

	bool have_exception;
	काष्ठा x86_exception exception;

	/* GPA available */
	bool gpa_available;
	gpa_t gpa_val;

	/*
	 * decode cache
	 */

	/* current opcode length in bytes */
	u8 opcode_len;
	u8 b;
	u8 पूर्णांकercept;
	u8 op_bytes;
	u8 ad_bytes;
	जोड़ अणु
		पूर्णांक (*execute)(काष्ठा x86_emulate_ctxt *ctxt);
		fastop_t fop;
	पूर्ण;
	पूर्णांक (*check_perm)(काष्ठा x86_emulate_ctxt *ctxt);
	/*
	 * The following six fields are cleared together,
	 * the rest are initialized unconditionally in x86_decode_insn
	 * or अन्यथाwhere
	 */
	bool rip_relative;
	u8 rex_prefix;
	u8 lock_prefix;
	u8 rep_prefix;
	/* biपंचांगaps of रेजिस्टरs in _regs[] that can be पढ़ो */
	u32 regs_valid;
	/* biपंचांगaps of रेजिस्टरs in _regs[] that have been written */
	u32 regs_dirty;
	/* modrm */
	u8 modrm;
	u8 modrm_mod;
	u8 modrm_reg;
	u8 modrm_rm;
	u8 modrm_seg;
	u8 seg_override;
	u64 d;
	अचिन्हित दीर्घ _eip;

	/* Here begins the usercopy section. */
	काष्ठा opeअक्रम src;
	काष्ठा opeअक्रम src2;
	काष्ठा opeअक्रम dst;
	काष्ठा opeअक्रम memop;
	अचिन्हित दीर्घ _regs[NR_VCPU_REGS];
	काष्ठा opeअक्रम *memopp;
	काष्ठा fetch_cache fetch;
	काष्ठा पढ़ो_cache io_पढ़ो;
	काष्ठा पढ़ो_cache mem_पढ़ो;
पूर्ण;

/* Repeat String Operation Prefix */
#घोषणा REPE_PREFIX	0xf3
#घोषणा REPNE_PREFIX	0xf2

/* CPUID venकरोrs */
#घोषणा X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx 0x68747541
#घोषणा X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx 0x444d4163
#घोषणा X86EMUL_CPUID_VENDOR_AuthenticAMD_edx 0x69746e65

#घोषणा X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx 0x69444d41
#घोषणा X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx 0x21726574
#घोषणा X86EMUL_CPUID_VENDOR_AMDisbetterI_edx 0x74656273

#घोषणा X86EMUL_CPUID_VENDOR_HygonGenuine_ebx 0x6f677948
#घोषणा X86EMUL_CPUID_VENDOR_HygonGenuine_ecx 0x656e6975
#घोषणा X86EMUL_CPUID_VENDOR_HygonGenuine_edx 0x6e65476e

#घोषणा X86EMUL_CPUID_VENDOR_GenuineIntel_ebx 0x756e6547
#घोषणा X86EMUL_CPUID_VENDOR_GenuineIntel_ecx 0x6c65746e
#घोषणा X86EMUL_CPUID_VENDOR_GenuineIntel_edx 0x49656e69

#घोषणा X86EMUL_CPUID_VENDOR_CentaurHauls_ebx 0x746e6543
#घोषणा X86EMUL_CPUID_VENDOR_CentaurHauls_ecx 0x736c7561
#घोषणा X86EMUL_CPUID_VENDOR_CentaurHauls_edx 0x48727561

अटल अंतरभूत bool is_guest_venकरोr_पूर्णांकel(u32 ebx, u32 ecx, u32 edx)
अणु
	वापस ebx == X86EMUL_CPUID_VENDOR_GenuineIntel_ebx &&
	       ecx == X86EMUL_CPUID_VENDOR_GenuineIntel_ecx &&
	       edx == X86EMUL_CPUID_VENDOR_GenuineIntel_edx;
पूर्ण

अटल अंतरभूत bool is_guest_venकरोr_amd(u32 ebx, u32 ecx, u32 edx)
अणु
	वापस (ebx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx &&
		ecx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx &&
		edx == X86EMUL_CPUID_VENDOR_AuthenticAMD_edx) ||
	       (ebx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx &&
		ecx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx &&
		edx == X86EMUL_CPUID_VENDOR_AMDisbetterI_edx);
पूर्ण

अटल अंतरभूत bool is_guest_venकरोr_hygon(u32 ebx, u32 ecx, u32 edx)
अणु
	वापस ebx == X86EMUL_CPUID_VENDOR_HygonGenuine_ebx &&
	       ecx == X86EMUL_CPUID_VENDOR_HygonGenuine_ecx &&
	       edx == X86EMUL_CPUID_VENDOR_HygonGenuine_edx;
पूर्ण

क्रमागत x86_पूर्णांकercept_stage अणु
	X86_ICTP_NONE = 0,   /* Allow zero-init to not match anything */
	X86_ICPT_PRE_EXCEPT,
	X86_ICPT_POST_EXCEPT,
	X86_ICPT_POST_MEMACCESS,
पूर्ण;

क्रमागत x86_पूर्णांकercept अणु
	x86_पूर्णांकercept_none,
	x86_पूर्णांकercept_cr_पढ़ो,
	x86_पूर्णांकercept_cr_ग_लिखो,
	x86_पूर्णांकercept_clts,
	x86_पूर्णांकercept_lmsw,
	x86_पूर्णांकercept_smsw,
	x86_पूर्णांकercept_dr_पढ़ो,
	x86_पूर्णांकercept_dr_ग_लिखो,
	x86_पूर्णांकercept_lidt,
	x86_पूर्णांकercept_sidt,
	x86_पूर्णांकercept_lgdt,
	x86_पूर्णांकercept_sgdt,
	x86_पूर्णांकercept_lldt,
	x86_पूर्णांकercept_sldt,
	x86_पूर्णांकercept_ltr,
	x86_पूर्णांकercept_str,
	x86_पूर्णांकercept_rdtsc,
	x86_पूर्णांकercept_rdpmc,
	x86_पूर्णांकercept_pushf,
	x86_पूर्णांकercept_popf,
	x86_पूर्णांकercept_cpuid,
	x86_पूर्णांकercept_rsm,
	x86_पूर्णांकercept_iret,
	x86_पूर्णांकercept_पूर्णांकn,
	x86_पूर्णांकercept_invd,
	x86_पूर्णांकercept_छोड़ो,
	x86_पूर्णांकercept_hlt,
	x86_पूर्णांकercept_invlpg,
	x86_पूर्णांकercept_invlpga,
	x86_पूर्णांकercept_vmrun,
	x86_पूर्णांकercept_vmload,
	x86_पूर्णांकercept_vmsave,
	x86_पूर्णांकercept_vmmcall,
	x86_पूर्णांकercept_stgi,
	x86_पूर्णांकercept_clgi,
	x86_पूर्णांकercept_skinit,
	x86_पूर्णांकercept_rdtscp,
	x86_पूर्णांकercept_rdpid,
	x86_पूर्णांकercept_icebp,
	x86_पूर्णांकercept_wbinvd,
	x86_पूर्णांकercept_monitor,
	x86_पूर्णांकercept_mरुको,
	x86_पूर्णांकercept_rdmsr,
	x86_पूर्णांकercept_wrmsr,
	x86_पूर्णांकercept_in,
	x86_पूर्णांकercept_ins,
	x86_पूर्णांकercept_out,
	x86_पूर्णांकercept_outs,
	x86_पूर्णांकercept_xsetbv,

	nr_x86_पूर्णांकercepts
पूर्ण;

/* Host execution mode. */
#अगर defined(CONFIG_X86_32)
#घोषणा X86EMUL_MODE_HOST X86EMUL_MODE_PROT32
#या_अगर defined(CONFIG_X86_64)
#घोषणा X86EMUL_MODE_HOST X86EMUL_MODE_PROT64
#पूर्ण_अगर

पूर्णांक x86_decode_insn(काष्ठा x86_emulate_ctxt *ctxt, व्योम *insn, पूर्णांक insn_len, पूर्णांक emulation_type);
bool x86_page_table_writing_insn(काष्ठा x86_emulate_ctxt *ctxt);
#घोषणा EMULATION_FAILED -1
#घोषणा EMULATION_OK 0
#घोषणा EMULATION_RESTART 1
#घोषणा EMULATION_INTERCEPTED 2
व्योम init_decode_cache(काष्ठा x86_emulate_ctxt *ctxt);
पूर्णांक x86_emulate_insn(काष्ठा x86_emulate_ctxt *ctxt);
पूर्णांक emulator_task_चयन(काष्ठा x86_emulate_ctxt *ctxt,
			 u16 tss_selector, पूर्णांक idt_index, पूर्णांक reason,
			 bool has_error_code, u32 error_code);
पूर्णांक emulate_पूर्णांक_real(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक irq);
व्योम emulator_invalidate_रेजिस्टर_cache(काष्ठा x86_emulate_ctxt *ctxt);
व्योम emulator_ग_लिखोback_रेजिस्टर_cache(काष्ठा x86_emulate_ctxt *ctxt);
bool emulator_can_use_gpa(काष्ठा x86_emulate_ctxt *ctxt);

#पूर्ण_अगर /* _ASM_X86_KVM_X86_EMULATE_H */
