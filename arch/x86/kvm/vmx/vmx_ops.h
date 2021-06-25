<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_INSN_H
#घोषणा __KVM_X86_VMX_INSN_H

#समावेश <linux/nospec.h>

#समावेश <यंत्र/kvm_host.h>
#समावेश <यंत्र/vmx.h>

#समावेश "evmcs.h"
#समावेश "vmcs.h"

#घोषणा __ex(x) __kvm_handle_fault_on_reboot(x)

यंत्रlinkage व्योम vmपढ़ो_error(अचिन्हित दीर्घ field, bool fault);
__attribute__((regparm(0))) व्योम vmपढ़ो_error_trampoline(अचिन्हित दीर्घ field,
							 bool fault);
व्योम vmग_लिखो_error(अचिन्हित दीर्घ field, अचिन्हित दीर्घ value);
व्योम vmclear_error(काष्ठा vmcs *vmcs, u64 phys_addr);
व्योम vmptrld_error(काष्ठा vmcs *vmcs, u64 phys_addr);
व्योम invvpid_error(अचिन्हित दीर्घ ext, u16 vpid, gva_t gva);
व्योम invept_error(अचिन्हित दीर्घ ext, u64 eptp, gpa_t gpa);

अटल __always_अंतरभूत व्योम vmcs_check16(अचिन्हित दीर्घ field)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2000,
			 "16-bit accessor invalid for 64-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2001,
			 "16-bit accessor invalid for 64-bit high field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x4000,
			 "16-bit accessor invalid for 32-bit high field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x6000,
			 "16-bit accessor invalid for natural width field");
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_check32(अचिन्हित दीर्घ field)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0,
			 "32-bit accessor invalid for 16-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2000,
			 "32-bit accessor invalid for 64-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2001,
			 "32-bit accessor invalid for 64-bit high field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x6000,
			 "32-bit accessor invalid for natural width field");
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_check64(अचिन्हित दीर्घ field)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0,
			 "64-bit accessor invalid for 16-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2001,
			 "64-bit accessor invalid for 64-bit high field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x4000,
			 "64-bit accessor invalid for 32-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x6000,
			 "64-bit accessor invalid for natural width field");
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_checkl(अचिन्हित दीर्घ field)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0,
			 "Natural width accessor invalid for 16-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2000,
			 "Natural width accessor invalid for 64-bit field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6001) == 0x2001,
			 "Natural width accessor invalid for 64-bit high field");
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x4000,
			 "Natural width accessor invalid for 32-bit field");
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ __vmcs_पढ़ोl(अचिन्हित दीर्घ field)
अणु
	अचिन्हित दीर्घ value;

	यंत्र अस्थिर("1: vmread %2, %1\n\t"
		     ".byte 0x3e\n\t" /* branch taken hपूर्णांक */
		     "ja 3f\n\t"

		     /*
		      * VMREAD failed.  Push '0' क्रम @fault, push the failing
		      * @field, and bounce through the trampoline to preserve
		      * अस्थिर रेजिस्टरs.
		      */
		     "push $0\n\t"
		     "push %2\n\t"
		     "2:call vmread_error_trampoline\n\t"

		     /*
		      * Unwind the stack.  Note, the trampoline zeros out the
		      * memory क्रम @fault so that the result is '0' on error.
		      */
		     "pop %2\n\t"
		     "pop %1\n\t"
		     "3:\n\t"

		     /* VMREAD faulted.  As above, except push '1' क्रम @fault. */
		     ".pushsection .fixup, \"ax\"\n\t"
		     "4: push $1\n\t"
		     "push %2\n\t"
		     "jmp 2b\n\t"
		     ".popsection\n\t"
		     _ASM_EXTABLE(1b, 4b)
		     : ASM_CALL_CONSTRAINT, "=r"(value) : "r"(field) : "cc");
	वापस value;
पूर्ण

अटल __always_अंतरभूत u16 vmcs_पढ़ो16(अचिन्हित दीर्घ field)
अणु
	vmcs_check16(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_पढ़ो16(field);
	वापस __vmcs_पढ़ोl(field);
पूर्ण

अटल __always_अंतरभूत u32 vmcs_पढ़ो32(अचिन्हित दीर्घ field)
अणु
	vmcs_check32(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_पढ़ो32(field);
	वापस __vmcs_पढ़ोl(field);
पूर्ण

अटल __always_अंतरभूत u64 vmcs_पढ़ो64(अचिन्हित दीर्घ field)
अणु
	vmcs_check64(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_पढ़ो64(field);
#अगर_घोषित CONFIG_X86_64
	वापस __vmcs_पढ़ोl(field);
#अन्यथा
	वापस __vmcs_पढ़ोl(field) | ((u64)__vmcs_पढ़ोl(field+1) << 32);
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ vmcs_पढ़ोl(अचिन्हित दीर्घ field)
अणु
	vmcs_checkl(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_पढ़ो64(field);
	वापस __vmcs_पढ़ोl(field);
पूर्ण

#घोषणा vmx_यंत्र1(insn, op1, error_args...)				\
करो अणु									\
	यंत्र_अस्थिर_जाओ("1: " __stringअगरy(insn) " %0\n\t"		\
			  ".byte 0x2e\n\t" /* branch not taken hपूर्णांक */	\
			  "jna %l[error]\n\t"				\
			  _ASM_EXTABLE(1b, %l[fault])			\
			  : : op1 : "cc" : error, fault);		\
	वापस;								\
error:									\
	instrumentation_begin();					\
	insn##_error(error_args);					\
	instrumentation_end();						\
	वापस;								\
fault:									\
	kvm_spurious_fault();						\
पूर्ण जबतक (0)

#घोषणा vmx_यंत्र2(insn, op1, op2, error_args...)				\
करो अणु									\
	यंत्र_अस्थिर_जाओ("1: "  __stringअगरy(insn) " %1, %0\n\t"	\
			  ".byte 0x2e\n\t" /* branch not taken hपूर्णांक */	\
			  "jna %l[error]\n\t"				\
			  _ASM_EXTABLE(1b, %l[fault])			\
			  : : op1, op2 : "cc" : error, fault);		\
	वापस;								\
error:									\
	instrumentation_begin();					\
	insn##_error(error_args);					\
	instrumentation_end();						\
	वापस;								\
fault:									\
	kvm_spurious_fault();						\
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम __vmcs_ग_लिखोl(अचिन्हित दीर्घ field, अचिन्हित दीर्घ value)
अणु
	vmx_यंत्र2(vmग_लिखो, "r"(field), "rm"(value), field, value);
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_ग_लिखो16(अचिन्हित दीर्घ field, u16 value)
अणु
	vmcs_check16(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो16(field, value);

	__vmcs_ग_लिखोl(field, value);
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_ग_लिखो32(अचिन्हित दीर्घ field, u32 value)
अणु
	vmcs_check32(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो32(field, value);

	__vmcs_ग_लिखोl(field, value);
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_ग_लिखो64(अचिन्हित दीर्घ field, u64 value)
अणु
	vmcs_check64(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो64(field, value);

	__vmcs_ग_लिखोl(field, value);
#अगर_अघोषित CONFIG_X86_64
	__vmcs_ग_लिखोl(field+1, value >> 32);
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_ग_लिखोl(अचिन्हित दीर्घ field, अचिन्हित दीर्घ value)
अणु
	vmcs_checkl(field);
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो64(field, value);

	__vmcs_ग_लिखोl(field, value);
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_clear_bits(अचिन्हित दीर्घ field, u32 mask)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x2000,
			 "vmcs_clear_bits does not support 64-bit fields");
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो32(field, evmcs_पढ़ो32(field) & ~mask);

	__vmcs_ग_लिखोl(field, __vmcs_पढ़ोl(field) & ~mask);
पूर्ण

अटल __always_अंतरभूत व्योम vmcs_set_bits(अचिन्हित दीर्घ field, u32 mask)
अणु
	BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(field) && ((field) & 0x6000) == 0x2000,
			 "vmcs_set_bits does not support 64-bit fields");
	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_ग_लिखो32(field, evmcs_पढ़ो32(field) | mask);

	__vmcs_ग_लिखोl(field, __vmcs_पढ़ोl(field) | mask);
पूर्ण

अटल अंतरभूत व्योम vmcs_clear(काष्ठा vmcs *vmcs)
अणु
	u64 phys_addr = __pa(vmcs);

	vmx_यंत्र1(vmclear, "m"(phys_addr), vmcs, phys_addr);
पूर्ण

अटल अंतरभूत व्योम vmcs_load(काष्ठा vmcs *vmcs)
अणु
	u64 phys_addr = __pa(vmcs);

	अगर (अटल_branch_unlikely(&enable_evmcs))
		वापस evmcs_load(phys_addr);

	vmx_यंत्र1(vmptrld, "m"(phys_addr), vmcs, phys_addr);
पूर्ण

अटल अंतरभूत व्योम __invvpid(अचिन्हित दीर्घ ext, u16 vpid, gva_t gva)
अणु
	काष्ठा अणु
		u64 vpid : 16;
		u64 rsvd : 48;
		u64 gva;
	पूर्ण opeअक्रम = अणु vpid, 0, gva पूर्ण;

	vmx_यंत्र2(invvpid, "r"(ext), "m"(opeअक्रम), ext, vpid, gva);
पूर्ण

अटल अंतरभूत व्योम __invept(अचिन्हित दीर्घ ext, u64 eptp, gpa_t gpa)
अणु
	काष्ठा अणु
		u64 eptp, gpa;
	पूर्ण opeअक्रम = अणुeptp, gpaपूर्ण;

	vmx_यंत्र2(invept, "r"(ext), "m"(opeअक्रम), ext, eptp, gpa);
पूर्ण

अटल अंतरभूत व्योम vpid_sync_vcpu_single(पूर्णांक vpid)
अणु
	अगर (vpid == 0)
		वापस;

	__invvpid(VMX_VPID_EXTENT_SINGLE_CONTEXT, vpid, 0);
पूर्ण

अटल अंतरभूत व्योम vpid_sync_vcpu_global(व्योम)
अणु
	__invvpid(VMX_VPID_EXTENT_ALL_CONTEXT, 0, 0);
पूर्ण

अटल अंतरभूत व्योम vpid_sync_context(पूर्णांक vpid)
अणु
	अगर (cpu_has_vmx_invvpid_single())
		vpid_sync_vcpu_single(vpid);
	अन्यथा अगर (vpid != 0)
		vpid_sync_vcpu_global();
पूर्ण

अटल अंतरभूत व्योम vpid_sync_vcpu_addr(पूर्णांक vpid, gva_t addr)
अणु
	अगर (vpid == 0)
		वापस;

	अगर (cpu_has_vmx_invvpid_inभागidual_addr())
		__invvpid(VMX_VPID_EXTENT_INDIVIDUAL_ADDR, vpid, addr);
	अन्यथा
		vpid_sync_context(vpid);
पूर्ण

अटल अंतरभूत व्योम ept_sync_global(व्योम)
अणु
	__invept(VMX_EPT_EXTENT_GLOBAL, 0, 0);
पूर्ण

अटल अंतरभूत व्योम ept_sync_context(u64 eptp)
अणु
	अगर (cpu_has_vmx_invept_context())
		__invept(VMX_EPT_EXTENT_CONTEXT, eptp, 0);
	अन्यथा
		ept_sync_global();
पूर्ण

#पूर्ण_अगर /* __KVM_X86_VMX_INSN_H */
