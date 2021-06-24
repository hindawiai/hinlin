<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2020, Sandipan Das, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_PKEYS_H
#घोषणा _SELFTESTS_POWERPC_PKEYS_H

#समावेश <sys/mman.h>

#समावेश "reg.h"
#समावेश "utils.h"

/*
 * Older versions of libc use the Intel-specअगरic access rights.
 * Hence, override the definitions as they might be incorrect.
 */
#अघोषित PKEY_DISABLE_ACCESS
#घोषणा PKEY_DISABLE_ACCESS	0x3

#अघोषित PKEY_DISABLE_WRITE
#घोषणा PKEY_DISABLE_WRITE	0x2

#अघोषित PKEY_DISABLE_EXECUTE
#घोषणा PKEY_DISABLE_EXECUTE	0x4

/* Older versions of libc करो not not define this */
#अगर_अघोषित SEGV_PKUERR
#घोषणा SEGV_PKUERR	4
#पूर्ण_अगर

#घोषणा SI_PKEY_OFFSET	0x20

#घोषणा __NR_pkey_mprotect	386
#घोषणा __NR_pkey_alloc		384
#घोषणा __NR_pkey_मुक्त		385

#घोषणा PKEY_BITS_PER_PKEY	2
#घोषणा NR_PKEYS		32
#घोषणा PKEY_BITS_MASK		((1UL << PKEY_BITS_PER_PKEY) - 1)

अंतरभूत अचिन्हित दीर्घ pkeyreg_get(व्योम)
अणु
	वापस mfspr(SPRN_AMR);
पूर्ण

अंतरभूत व्योम pkeyreg_set(अचिन्हित दीर्घ amr)
अणु
	set_amr(amr);
पूर्ण

व्योम pkey_set_rights(पूर्णांक pkey, अचिन्हित दीर्घ rights)
अणु
	अचिन्हित दीर्घ amr, shअगरt;

	shअगरt = (NR_PKEYS - pkey - 1) * PKEY_BITS_PER_PKEY;
	amr = pkeyreg_get();
	amr &= ~(PKEY_BITS_MASK << shअगरt);
	amr |= (rights & PKEY_BITS_MASK) << shअगरt;
	pkeyreg_set(amr);
पूर्ण

पूर्णांक sys_pkey_mprotect(व्योम *addr, माप_प्रकार len, पूर्णांक prot, पूर्णांक pkey)
अणु
	वापस syscall(__NR_pkey_mprotect, addr, len, prot, pkey);
पूर्ण

पूर्णांक sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ rights)
अणु
	वापस syscall(__NR_pkey_alloc, flags, rights);
पूर्ण

पूर्णांक sys_pkey_मुक्त(पूर्णांक pkey)
अणु
	वापस syscall(__NR_pkey_मुक्त, pkey);
पूर्ण

पूर्णांक pkeys_unsupported(व्योम)
अणु
	bool hash_mmu = false;
	पूर्णांक pkey;

	/* Protection keys are currently supported on Hash MMU only */
	FAIL_IF(using_hash_mmu(&hash_mmu));
	SKIP_IF(!hash_mmu);

	/* Check अगर the प्रणाली call is supported */
	pkey = sys_pkey_alloc(0, 0);
	SKIP_IF(pkey < 0);
	sys_pkey_मुक्त(pkey);

	वापस 0;
पूर्ण

पूर्णांक siginfo_pkey(siginfo_t *si)
अणु
	/*
	 * In older versions of libc, siginfo_t करोes not have si_pkey as
	 * a member.
	 */
#अगर_घोषित si_pkey
	वापस si->si_pkey;
#अन्यथा
	वापस *((पूर्णांक *)(((अक्षर *) si) + SI_PKEY_OFFSET));
#पूर्ण_अगर
पूर्ण

#घोषणा pkey_rights(r) (अणु						\
	अटल अक्षर buf[4] = "rwx";					\
	अचिन्हित पूर्णांक amr_bits;						\
	अगर ((r) & PKEY_DISABLE_EXECUTE)					\
		buf[2] = '-';						\
	amr_bits = (r) & PKEY_BITS_MASK;				\
	अगर (amr_bits & PKEY_DISABLE_WRITE)				\
		buf[1] = '-';						\
	अगर (amr_bits & PKEY_DISABLE_ACCESS & ~PKEY_DISABLE_WRITE)	\
		buf[0] = '-';						\
	buf;								\
पूर्ण)

अचिन्हित दीर्घ next_pkey_rights(अचिन्हित दीर्घ rights)
अणु
	अगर (rights == PKEY_DISABLE_ACCESS)
		वापस PKEY_DISABLE_EXECUTE;
	अन्यथा अगर (rights == (PKEY_DISABLE_ACCESS | PKEY_DISABLE_EXECUTE))
		वापस 0;

	अगर ((rights & PKEY_BITS_MASK) == 0)
		rights |= PKEY_DISABLE_WRITE;
	अन्यथा अगर ((rights & PKEY_BITS_MASK) == PKEY_DISABLE_WRITE)
		rights |= PKEY_DISABLE_ACCESS;

	वापस rights;
पूर्ण

#पूर्ण_अगर /* _SELFTESTS_POWERPC_PKEYS_H */
