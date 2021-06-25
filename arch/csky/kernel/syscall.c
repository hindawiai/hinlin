<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/syscalls.h>

SYSCALL_DEFINE1(set_thपढ़ो_area, अचिन्हित दीर्घ, addr)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(current);
	काष्ठा pt_regs *reg = current_pt_regs();

	reg->tls = addr;
	ti->tp_value = addr;

	वापस 0;
पूर्ण

SYSCALL_DEFINE6(mmap2,
	अचिन्हित दीर्घ, addr,
	अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot,
	अचिन्हित दीर्घ, flags,
	अचिन्हित दीर्घ, fd,
	off_t, offset)
अणु
	अगर (unlikely(offset & (~PAGE_MASK >> 12)))
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       offset >> (PAGE_SHIFT - 12));
पूर्ण

/*
 * क्रम abiv1 the 64bits args should be even th, So we need mov the advice
 * क्रमward.
 */
SYSCALL_DEFINE4(csky_fadvise64_64,
	पूर्णांक, fd,
	पूर्णांक, advice,
	loff_t, offset,
	loff_t, len)
अणु
	वापस ksys_fadvise64_64(fd, offset, len, advice);
पूर्ण
