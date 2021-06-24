<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _PKEYS_POWERPC_H
#घोषणा _PKEYS_POWERPC_H

#अगर_अघोषित SYS_mprotect_key
# define SYS_mprotect_key	386
#पूर्ण_अगर
#अगर_अघोषित SYS_pkey_alloc
# define SYS_pkey_alloc		384
# define SYS_pkey_मुक्त		385
#पूर्ण_अगर
#घोषणा REG_IP_IDX		PT_NIP
#घोषणा REG_TRAPNO		PT_TRAP
#घोषणा gregs			gp_regs
#घोषणा fpregs			fp_regs
#घोषणा si_pkey_offset		0x20

#अघोषित PKEY_DISABLE_ACCESS
#घोषणा PKEY_DISABLE_ACCESS	0x3  /* disable पढ़ो and ग_लिखो */

#अघोषित PKEY_DISABLE_WRITE
#घोषणा PKEY_DISABLE_WRITE	0x2

#घोषणा NR_PKEYS		32
#घोषणा NR_RESERVED_PKEYS_4K	27 /* pkey-0, pkey-1, exec-only-pkey
				      and 24 other keys that cannot be
				      represented in the PTE */
#घोषणा NR_RESERVED_PKEYS_64K_3KEYS	3 /* PowerNV and KVM: pkey-0,
					     pkey-1 and exec-only key */
#घोषणा NR_RESERVED_PKEYS_64K_4KEYS	4 /* PowerVM: pkey-0, pkey-1,
					     pkey-31 and exec-only key */
#घोषणा PKEY_BITS_PER_PKEY	2
#घोषणा HPAGE_SIZE		(1UL << 24)
#घोषणा PAGE_SIZE		sysconf(_SC_PAGESIZE)

अटल अंतरभूत u32 pkey_bit_position(पूर्णांक pkey)
अणु
	वापस (NR_PKEYS - pkey - 1) * PKEY_BITS_PER_PKEY;
पूर्ण

अटल अंतरभूत u64 __पढ़ो_pkey_reg(व्योम)
अणु
	u64 pkey_reg;

	यंत्र अस्थिर("mfspr %0, 0xd" : "=r" (pkey_reg));

	वापस pkey_reg;
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_pkey_reg(u64 pkey_reg)
अणु
	u64 amr = pkey_reg;

	dम_लिखो4("%s() changing %016llx to %016llx\n",
			 __func__, __पढ़ो_pkey_reg(), pkey_reg);

	यंत्र अस्थिर("isync; mtspr 0xd, %0; isync"
		     : : "r" ((अचिन्हित दीर्घ)(amr)) : "memory");

	dम_लिखो4("%s() pkey register after changing %016llx to %016llx\n",
			__func__, __पढ़ो_pkey_reg(), pkey_reg);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_has_pkeys(व्योम)
अणु
	/* No simple way to determine this */
	वापस 1;
पूर्ण

अटल अंतरभूत bool arch_is_घातervm()
अणु
	काष्ठा stat buf;

	अगर ((stat("/sys/firmware/devicetree/base/ibm,partition-name", &buf) == 0) &&
	    (stat("/sys/firmware/devicetree/base/hmc-managed?", &buf) == 0) &&
	    (stat("/sys/firmware/devicetree/base/chosen/qemu,graphic-width", &buf) == -1) )
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक get_arch_reserved_keys(व्योम)
अणु
	अगर (sysconf(_SC_PAGESIZE) == 4096)
		वापस NR_RESERVED_PKEYS_4K;
	अन्यथा
		अगर (arch_is_घातervm())
			वापस NR_RESERVED_PKEYS_64K_4KEYS;
		अन्यथा
			वापस NR_RESERVED_PKEYS_64K_3KEYS;
पूर्ण

व्योम expect_fault_on_पढ़ो_execonly_key(व्योम *p1, पूर्णांक pkey)
अणु
	/*
	 * घातerpc करोes not allow userspace to change permissions of exec-only
	 * keys since those keys are not allocated by userspace. The संकेत
	 * handler wont be able to reset the permissions, which means the code
	 * will infinitely जारी to segfault here.
	 */
	वापस;
पूर्ण

/* 4-byte inकाष्ठाions * 16384 = 64K page */
#घोषणा __page_o_noops() यंत्र(".rept 16384 ; nop; .endr")

व्योम *दो_स्मृति_pkey_with_mprotect_subpage(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	व्योम *ptr;
	पूर्णांक ret;

	dम_लिखो1("doing %s(size=%ld, prot=0x%x, pkey=%d)\n", __func__,
			size, prot, pkey);
	pkey_निश्चित(pkey < NR_PKEYS);
	ptr = mmap(शून्य, size, prot, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	pkey_निश्चित(ptr != (व्योम *)-1);

	ret = syscall(__NR_subpage_prot, ptr, size, शून्य);
	अगर (ret) अणु
		लिखो_त्रुटि("subpage_perm");
		वापस PTR_ERR_ENOTSUP;
	पूर्ण

	ret = mprotect_pkey((व्योम *)ptr, PAGE_SIZE, prot, pkey);
	pkey_निश्चित(!ret);
	record_pkey_दो_स्मृति(ptr, size, prot);

	dम_लिखो1("%s() for pkey %d @ %p\n", __func__, pkey, ptr);
	वापस ptr;
पूर्ण

#पूर्ण_अगर /* _PKEYS_POWERPC_H */
