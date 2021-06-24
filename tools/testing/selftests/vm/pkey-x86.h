<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _PKEYS_X86_H
#घोषणा _PKEYS_X86_H

#अगर_घोषित __i386__

#अगर_अघोषित SYS_mprotect_key
# define SYS_mprotect_key	380
#पूर्ण_अगर

#अगर_अघोषित SYS_pkey_alloc
# define SYS_pkey_alloc		381
# define SYS_pkey_मुक्त		382
#पूर्ण_अगर

#घोषणा REG_IP_IDX		REG_EIP
#घोषणा si_pkey_offset		0x14

#अन्यथा

#अगर_अघोषित SYS_mprotect_key
# define SYS_mprotect_key	329
#पूर्ण_अगर

#अगर_अघोषित SYS_pkey_alloc
# define SYS_pkey_alloc		330
# define SYS_pkey_मुक्त		331
#पूर्ण_अगर

#घोषणा REG_IP_IDX		REG_RIP
#घोषणा si_pkey_offset		0x20

#पूर्ण_अगर

#अगर_अघोषित PKEY_DISABLE_ACCESS
# define PKEY_DISABLE_ACCESS	0x1
#पूर्ण_अगर

#अगर_अघोषित PKEY_DISABLE_WRITE
# define PKEY_DISABLE_WRITE	0x2
#पूर्ण_अगर

#घोषणा NR_PKEYS		16
#घोषणा NR_RESERVED_PKEYS	2 /* pkey-0 and exec-only-pkey */
#घोषणा PKEY_BITS_PER_PKEY	2
#घोषणा HPAGE_SIZE		(1UL<<21)
#घोषणा PAGE_SIZE		4096
#घोषणा MB			(1<<20)

अटल अंतरभूत व्योम __page_o_noops(व्योम)
अणु
	/* 8-bytes of inकाष्ठाion * 512 bytes = 1 page */
	यंत्र(".rept 512 ; nopl 0x7eeeeeee(%eax) ; .endr");
पूर्ण

अटल अंतरभूत u64 __पढ़ो_pkey_reg(व्योम)
अणु
	अचिन्हित पूर्णांक eax, edx;
	अचिन्हित पूर्णांक ecx = 0;
	अचिन्हित pkey_reg;

	यंत्र अस्थिर(".byte 0x0f,0x01,0xee\n\t"
		     : "=a" (eax), "=d" (edx)
		     : "c" (ecx));
	pkey_reg = eax;
	वापस pkey_reg;
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_pkey_reg(u64 pkey_reg)
अणु
	अचिन्हित पूर्णांक eax = pkey_reg;
	अचिन्हित पूर्णांक ecx = 0;
	अचिन्हित पूर्णांक edx = 0;

	dम_लिखो4("%s() changing %016llx to %016llx\n", __func__,
			__पढ़ो_pkey_reg(), pkey_reg);
	यंत्र अस्थिर(".byte 0x0f,0x01,0xef\n\t"
		     : : "a" (eax), "c" (ecx), "d" (edx));
	निश्चित(pkey_reg == __पढ़ो_pkey_reg());
पूर्ण

अटल अंतरभूत व्योम __cpuid(अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
		अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	/* ecx is often an input as well as an output. */
	यंत्र अस्थिर(
		"cpuid;"
		: "=a" (*eax),
		  "=b" (*ebx),
		  "=c" (*ecx),
		  "=d" (*edx)
		: "0" (*eax), "2" (*ecx));
पूर्ण

/* Intel-defined CPU features, CPUID level 0x00000007:0 (ecx) */
#घोषणा X86_FEATURE_PKU        (1<<3) /* Protection Keys क्रम Userspace */
#घोषणा X86_FEATURE_OSPKE      (1<<4) /* OS Protection Keys Enable */

अटल अंतरभूत पूर्णांक cpu_has_pkeys(व्योम)
अणु
	अचिन्हित पूर्णांक eax;
	अचिन्हित पूर्णांक ebx;
	अचिन्हित पूर्णांक ecx;
	अचिन्हित पूर्णांक edx;

	eax = 0x7;
	ecx = 0x0;
	__cpuid(&eax, &ebx, &ecx, &edx);

	अगर (!(ecx & X86_FEATURE_PKU)) अणु
		dम_लिखो2("cpu does not have PKU\n");
		वापस 0;
	पूर्ण
	अगर (!(ecx & X86_FEATURE_OSPKE)) अणु
		dम_लिखो2("cpu does not have OSPKE\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत u32 pkey_bit_position(पूर्णांक pkey)
अणु
	वापस pkey * PKEY_BITS_PER_PKEY;
पूर्ण

#घोषणा XSTATE_PKEY_BIT	(9)
#घोषणा XSTATE_PKEY	0x200

पूर्णांक pkey_reg_xstate_offset(व्योम)
अणु
	अचिन्हित पूर्णांक eax;
	अचिन्हित पूर्णांक ebx;
	अचिन्हित पूर्णांक ecx;
	अचिन्हित पूर्णांक edx;
	पूर्णांक xstate_offset;
	पूर्णांक xstate_size;
	अचिन्हित दीर्घ XSTATE_CPUID = 0xd;
	पूर्णांक leaf;

	/* assume that XSTATE_PKEY is set in XCR0 */
	leaf = XSTATE_PKEY_BIT;
	अणु
		eax = XSTATE_CPUID;
		ecx = leaf;
		__cpuid(&eax, &ebx, &ecx, &edx);

		अगर (leaf == XSTATE_PKEY_BIT) अणु
			xstate_offset = ebx;
			xstate_size = eax;
		पूर्ण
	पूर्ण

	अगर (xstate_size == 0) अणु
		म_लिखो("could not find size/offset of PKEY in xsave state\n");
		वापस 0;
	पूर्ण

	वापस xstate_offset;
पूर्ण

अटल अंतरभूत पूर्णांक get_arch_reserved_keys(व्योम)
अणु
	वापस NR_RESERVED_PKEYS;
पूर्ण

व्योम expect_fault_on_पढ़ो_execonly_key(व्योम *p1, पूर्णांक pkey)
अणु
	पूर्णांक ptr_contents;

	ptr_contents = पढ़ो_ptr(p1);
	dम_लिखो2("ptr (%p) contents@%d: %x\n", p1, __LINE__, ptr_contents);
	expected_pkey_fault(pkey);
पूर्ण

व्योम *दो_स्मृति_pkey_with_mprotect_subpage(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	वापस PTR_ERR_ENOTSUP;
पूर्ण

#पूर्ण_अगर /* _PKEYS_X86_H */
