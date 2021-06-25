<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2014 Darius Rad <darius@bluespec.com>
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र-generic/mman-common.h>

अटल दीर्घ riscv_sys_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			   अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			   अचिन्हित दीर्घ fd, off_t offset,
			   अचिन्हित दीर्घ page_shअगरt_offset)
अणु
	अगर (unlikely(offset & (~PAGE_MASK >> page_shअगरt_offset)))
		वापस -EINVAL;

	अगर ((prot & PROT_WRITE) && (prot & PROT_EXEC))
		अगर (unlikely(!(prot & PROT_READ)))
			वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       offset >> (PAGE_SHIFT - page_shअगरt_offset));
पूर्ण

#अगर_घोषित CONFIG_64BIT
SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
	अचिन्हित दीर्घ, fd, off_t, offset)
अणु
	वापस riscv_sys_mmap(addr, len, prot, flags, fd, offset, 0);
पूर्ण
#अन्यथा
SYSCALL_DEFINE6(mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
	अचिन्हित दीर्घ, fd, off_t, offset)
अणु
	/*
	 * Note that the shअगरt क्रम mmap2 is स्थिरant (12),
	 * regardless of PAGE_SIZE
	 */
	वापस riscv_sys_mmap(addr, len, prot, flags, fd, offset, 12);
पूर्ण
#पूर्ण_अगर /* !CONFIG_64BIT */

/*
 * Allows the inकाष्ठाion cache to be flushed from userspace.  Despite RISC-V
 * having a direct 'fence.i' inकाष्ठाion available to userspace (which we
 * can't trap!), that's not actually viable when running on Linux because the
 * kernel might schedule a process on another hart.  There is no way क्रम
 * userspace to handle this without invoking the kernel (as it करोesn't know the
 * thपढ़ो->hart mappings), so we've defined a RISC-V specअगरic प्रणाली call to
 * flush the inकाष्ठाion cache.
 *
 * sys_riscv_flush_icache() is defined to flush the inकाष्ठाion cache over an
 * address range, with the flush applying to either all thपढ़ोs or just the
 * caller.  We करोn't currently do anything with the address range, that's just
 * in there क्रम क्रमwards compatibility.
 */
SYSCALL_DEFINE3(riscv_flush_icache, uपूर्णांकptr_t, start, uपूर्णांकptr_t, end,
	uपूर्णांकptr_t, flags)
अणु
	/* Check the reserved flags. */
	अगर (unlikely(flags & ~SYS_RISCV_FLUSH_ICACHE_ALL))
		वापस -EINVAL;

	flush_icache_mm(current->mm, flags & SYS_RISCV_FLUSH_ICACHE_LOCAL);

	वापस 0;
पूर्ण
