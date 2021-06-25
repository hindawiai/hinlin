<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/fp_udfiex_crtl.h>

SYSCALL_DEFINE6(mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	       अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
	       अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, pgoff)
अणु
	अगर (pgoff & (~PAGE_MASK >> 12))
		वापस -EINVAL;

	वापस sys_mmap_pgoff(addr, len, prot, flags, fd,
			      pgoff >> (PAGE_SHIFT - 12));
पूर्ण

SYSCALL_DEFINE4(fadvise64_64_wrapper,पूर्णांक, fd, पूर्णांक, advice, loff_t, offset,
					 loff_t, len)
अणु
	वापस sys_fadvise64_64(fd, offset, len, advice);
पूर्ण

SYSCALL_DEFINE3(cacheflush, अचिन्हित पूर्णांक, start, अचिन्हित पूर्णांक, end, पूर्णांक, cache)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	bool flushi = true, wbd = true;

	vma = find_vma(current->mm, start);
	अगर (!vma)
		वापस -EFAULT;
	चयन (cache) अणु
	हाल ICACHE:
		wbd = false;
		अवरोध;
	हाल DCACHE:
		flushi = false;
		अवरोध;
	हाल BCACHE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	cpu_cache_wbinval_range_check(vma, start, end, flushi, wbd);

	वापस 0;
पूर्ण

SYSCALL_DEFINE2(fp_udfiex_crtl, अचिन्हित पूर्णांक, cmd, अचिन्हित पूर्णांक, act)
अणु
#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
	पूर्णांक old_udf_iex;

	अगर (!used_math()) अणु
		load_fpu(&init_fpuregs);
		current->thपढ़ो.fpu.UDF_IEX_trap = init_fpuregs.UDF_IEX_trap;
		set_used_math();
	पूर्ण

	old_udf_iex = current->thपढ़ो.fpu.UDF_IEX_trap;
	act &= (FPCSR_mskUDFE | FPCSR_mskIEXE);

	चयन (cmd) अणु
	हाल DISABLE_UDF_IEX_TRAP:
		current->thपढ़ो.fpu.UDF_IEX_trap &= ~act;
		अवरोध;
	हाल ENABLE_UDF_IEX_TRAP:
		current->thपढ़ो.fpu.UDF_IEX_trap |= act;
		अवरोध;
	हाल GET_UDF_IEX_TRAP:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस old_udf_iex;
#अन्यथा
	वापस -ENOTSUPP;
#पूर्ण_अगर
पूर्ण
