<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकघोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <init.h>
#समावेश <as-layout.h>
#समावेश <mm_id.h>
#समावेश <os.h>
#समावेश <ptrace_user.h>
#समावेश <रेजिस्टरs.h>
#समावेश <skas.h>
#समावेश <sysdep/ptrace.h>
#समावेश <sysdep/stub.h>

बाह्य अक्षर batch_syscall_stub[], __syscall_stub_start[];

बाह्य व्योम रुको_stub_करोne(पूर्णांक pid);

अटल अंतरभूत अचिन्हित दीर्घ *check_init_stack(काष्ठा mm_id * mm_idp,
					      अचिन्हित दीर्घ *stack)
अणु
	अगर (stack == शून्य) अणु
		stack = (अचिन्हित दीर्घ *) mm_idp->stack + 2;
		*stack = 0;
	पूर्ण
	वापस stack;
पूर्ण

अटल अचिन्हित दीर्घ syscall_regs[MAX_REG_NR];

अटल पूर्णांक __init init_syscall_regs(व्योम)
अणु
	get_safe_रेजिस्टरs(syscall_regs, शून्य);
	syscall_regs[REGS_IP_INDEX] = STUB_CODE +
		((अचिन्हित दीर्घ) batch_syscall_stub -
		 (अचिन्हित दीर्घ) __syscall_stub_start);
	syscall_regs[REGS_SP_INDEX] = STUB_DATA;

	वापस 0;
पूर्ण

__initcall(init_syscall_regs);

अटल अंतरभूत दीर्घ करो_syscall_stub(काष्ठा mm_id * mm_idp, व्योम **addr)
अणु
	पूर्णांक n, i;
	दीर्घ ret, offset;
	अचिन्हित दीर्घ * data;
	अचिन्हित दीर्घ * syscall;
	पूर्णांक err, pid = mm_idp->u.pid;

	n = ptrace_setregs(pid, syscall_regs);
	अगर (n < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Registers - \n");
		क्रम (i = 0; i < MAX_REG_NR; i++)
			prपूर्णांकk(UM_KERN_ERR "\t%d\t0x%lx\n", i, syscall_regs[i]);
		panic("do_syscall_stub : PTRACE_SETREGS failed, errno = %d\n",
		      -n);
	पूर्ण

	err = ptrace(PTRACE_CONT, pid, 0, 0);
	अगर (err)
		panic("Failed to continue stub, pid = %d, errno = %d\n", pid,
		      त्रुटि_सं);

	रुको_stub_करोne(pid);

	/*
	 * When the stub stops, we find the following values on the
	 * beginning of the stack:
	 * (दीर्घ )वापस_value
	 * (दीर्घ )offset to failed sycall-data (0, अगर no error)
	 */
	ret = *((अचिन्हित दीर्घ *) mm_idp->stack);
	offset = *((अचिन्हित दीर्घ *) mm_idp->stack + 1);
	अगर (offset) अणु
		data = (अचिन्हित दीर्घ *)(mm_idp->stack + offset - STUB_DATA);
		prपूर्णांकk(UM_KERN_ERR "do_syscall_stub : ret = %ld, offset = %ld, "
		       "data = %p\n", ret, offset, data);
		syscall = (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)data + data[0]);
		prपूर्णांकk(UM_KERN_ERR "do_syscall_stub: syscall %ld failed, "
		       "return value = 0x%lx, expected return value = 0x%lx\n",
		       syscall[0], ret, syscall[7]);
		prपूर्णांकk(UM_KERN_ERR "    syscall parameters: "
		       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
		       syscall[1], syscall[2], syscall[3],
		       syscall[4], syscall[5], syscall[6]);
		क्रम (n = 1; n < data[0]/माप(दीर्घ); n++) अणु
			अगर (n == 1)
				prपूर्णांकk(UM_KERN_ERR "    additional syscall "
				       "data:");
			अगर (n % 4 == 1)
				prपूर्णांकk("\n" UM_KERN_ERR "      ");
			prपूर्णांकk("  0x%lx", data[n]);
		पूर्ण
		अगर (n > 1)
			prपूर्णांकk("\n");
	पूर्ण
	अन्यथा ret = 0;

	*addr = check_init_stack(mm_idp, शून्य);

	वापस ret;
पूर्ण

दीर्घ run_syscall_stub(काष्ठा mm_id * mm_idp, पूर्णांक syscall,
		      अचिन्हित दीर्घ *args, दीर्घ expected, व्योम **addr,
		      पूर्णांक करोne)
अणु
	अचिन्हित दीर्घ *stack = check_init_stack(mm_idp, *addr);

	*stack += माप(दीर्घ);
	stack += *stack / माप(दीर्घ);

	*stack++ = syscall;
	*stack++ = args[0];
	*stack++ = args[1];
	*stack++ = args[2];
	*stack++ = args[3];
	*stack++ = args[4];
	*stack++ = args[5];
	*stack++ = expected;
	*stack = 0;

	अगर (!करोne && ((((अचिन्हित दीर्घ) stack) & ~UM_KERN_PAGE_MASK) <
		     UM_KERN_PAGE_SIZE - 10 * माप(दीर्घ))) अणु
		*addr = stack;
		वापस 0;
	पूर्ण

	वापस करो_syscall_stub(mm_idp, addr);
पूर्ण

दीर्घ syscall_stub_data(काष्ठा mm_id * mm_idp,
		       अचिन्हित दीर्घ *data, पूर्णांक data_count,
		       व्योम **addr, व्योम **stub_addr)
अणु
	अचिन्हित दीर्घ *stack;
	पूर्णांक ret = 0;

	/*
	 * If *addr still is uninitialized, it *must* contain शून्य.
	 * Thus in this हाल करो_syscall_stub correctly won't be called.
	 */
	अगर ((((अचिन्हित दीर्घ) *addr) & ~UM_KERN_PAGE_MASK) >=
	   UM_KERN_PAGE_SIZE - (10 + data_count) * माप(दीर्घ)) अणु
		ret = करो_syscall_stub(mm_idp, addr);
		/* in हाल of error, करोn't overग_लिखो data on stack */
		अगर (ret)
			वापस ret;
	पूर्ण

	stack = check_init_stack(mm_idp, *addr);
	*addr = stack;

	*stack = data_count * माप(दीर्घ);

	स_नकल(stack + 1, data, data_count * माप(दीर्घ));

	*stub_addr = (व्योम *)(((अचिन्हित दीर्घ)(stack + 1) &
			       ~UM_KERN_PAGE_MASK) + STUB_DATA);

	वापस 0;
पूर्ण

पूर्णांक map(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ virt, अचिन्हित दीर्घ len, पूर्णांक prot,
	पूर्णांक phys_fd, अचिन्हित दीर्घ दीर्घ offset, पूर्णांक करोne, व्योम **data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ args[] = अणु virt, len, prot,
				 MAP_SHARED | MAP_FIXED, phys_fd,
				 MMAP_OFFSET(offset) पूर्ण;

	ret = run_syscall_stub(mm_idp, STUB_MMAP_NR, args, virt,
			       data, करोne);

	वापस ret;
पूर्ण

पूर्णांक unmap(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	  पूर्णांक करोne, व्योम **data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ args[] = अणु (अचिन्हित दीर्घ) addr, len, 0, 0, 0,
				 0 पूर्ण;

	ret = run_syscall_stub(mm_idp, __NR_munmap, args, 0,
			       data, करोne);

	वापस ret;
पूर्ण

पूर्णांक protect(काष्ठा mm_id * mm_idp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	    अचिन्हित पूर्णांक prot, पूर्णांक करोne, व्योम **data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ args[] = अणु addr, len, prot, 0, 0, 0 पूर्ण;

	ret = run_syscall_stub(mm_idp, __NR_mprotect, args, 0,
			       data, करोne);

	वापस ret;
पूर्ण
