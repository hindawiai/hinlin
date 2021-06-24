<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश <linux/auxvec.h>
#समावेश <sys/auxv.h>
#समावेश <sys/mman.h>
#समावेश <sys/prctl.h>

#समावेश <यंत्र/hwcap.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

#घोषणा INIT_BUFFER_SIZE       256

काष्ठा mte_fault_cxt cur_mte_cxt;
अटल अचिन्हित पूर्णांक mte_cur_mode;
अटल अचिन्हित पूर्णांक mte_cur_pstate_tco;

व्योम mte_शेष_handler(पूर्णांक signum, siginfo_t *si, व्योम *uc)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)si->si_addr;

	अगर (signum == संक_अंश) अणु
#अगर_घोषित DEBUG
		ksft_prपूर्णांक_msg("INFO: SIGSEGV signal at pc=%lx, fault addr=%lx, si_code=%lx\n",
				((ucontext_t *)uc)->uc_mcontext.pc, addr, si->si_code);
#पूर्ण_अगर
		अगर (si->si_code == SEGV_MTEAERR) अणु
			अगर (cur_mte_cxt.trig_si_code == si->si_code)
				cur_mte_cxt.fault_valid = true;
			वापस;
		पूर्ण
		/* Compare the context क्रम precise error */
		अन्यथा अगर (si->si_code == SEGV_MTESERR) अणु
			अगर (cur_mte_cxt.trig_si_code == si->si_code &&
			    ((cur_mte_cxt.trig_range >= 0 &&
			      addr >= MT_CLEAR_TAG(cur_mte_cxt.trig_addr) &&
			      addr <= (MT_CLEAR_TAG(cur_mte_cxt.trig_addr) + cur_mte_cxt.trig_range)) ||
			     (cur_mte_cxt.trig_range < 0 &&
			      addr <= MT_CLEAR_TAG(cur_mte_cxt.trig_addr) &&
			      addr >= (MT_CLEAR_TAG(cur_mte_cxt.trig_addr) + cur_mte_cxt.trig_range)))) अणु
				cur_mte_cxt.fault_valid = true;
				/* Adjust the pc by 4 */
				((ucontext_t *)uc)->uc_mcontext.pc += 4;
			पूर्ण अन्यथा अणु
				ksft_prपूर्णांक_msg("Invalid MTE synchronous exception caught!\n");
				निकास(1);
			पूर्ण
		पूर्ण अन्यथा अणु
			ksft_prपूर्णांक_msg("Unknown SIGSEGV exception caught!\n");
			निकास(1);
		पूर्ण
	पूर्ण अन्यथा अगर (signum == SIGBUS) अणु
		ksft_prपूर्णांक_msg("INFO: SIGBUS signal at pc=%lx, fault addr=%lx, si_code=%lx\n",
				((ucontext_t *)uc)->uc_mcontext.pc, addr, si->si_code);
		अगर ((cur_mte_cxt.trig_range >= 0 &&
		     addr >= MT_CLEAR_TAG(cur_mte_cxt.trig_addr) &&
		     addr <= (MT_CLEAR_TAG(cur_mte_cxt.trig_addr) + cur_mte_cxt.trig_range)) ||
		    (cur_mte_cxt.trig_range < 0 &&
		     addr <= MT_CLEAR_TAG(cur_mte_cxt.trig_addr) &&
		     addr >= (MT_CLEAR_TAG(cur_mte_cxt.trig_addr) + cur_mte_cxt.trig_range))) अणु
			cur_mte_cxt.fault_valid = true;
			/* Adjust the pc by 4 */
			((ucontext_t *)uc)->uc_mcontext.pc += 4;
		पूर्ण
	पूर्ण
पूर्ण

व्योम mte_रेजिस्टर_संकेत(पूर्णांक संकेत, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *))
अणु
	काष्ठा sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(संकेत, &sa, शून्य);
पूर्ण

व्योम mte_रुको_after_trig(व्योम)
अणु
	sched_yield();
पूर्ण

व्योम *mte_insert_tags(व्योम *ptr, माप_प्रकार size)
अणु
	व्योम *tag_ptr;
	पूर्णांक align_size;

	अगर (!ptr || (अचिन्हित दीर्घ)(ptr) & MT_ALIGN_GRANULE) अणु
		ksft_prपूर्णांक_msg("FAIL: Addr=%lx: invalid\n", ptr);
		वापस शून्य;
	पूर्ण
	align_size = MT_ALIGN_UP(size);
	tag_ptr = mte_insert_अक्रमom_tag(ptr);
	mte_set_tag_address_range(tag_ptr, align_size);
	वापस tag_ptr;
पूर्ण

व्योम mte_clear_tags(व्योम *ptr, माप_प्रकार size)
अणु
	अगर (!ptr || (अचिन्हित दीर्घ)(ptr) & MT_ALIGN_GRANULE) अणु
		ksft_prपूर्णांक_msg("FAIL: Addr=%lx: invalid\n", ptr);
		वापस;
	पूर्ण
	size = MT_ALIGN_UP(size);
	ptr = (व्योम *)MT_CLEAR_TAG((अचिन्हित दीर्घ)ptr);
	mte_clear_tag_address_range(ptr, size);
पूर्ण

अटल व्योम *__mte_allocate_memory_range(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
					 माप_प्रकार range_beक्रमe, माप_प्रकार range_after,
					 bool tags, पूर्णांक fd)
अणु
	व्योम *ptr;
	पूर्णांक prot_flag, map_flag;
	माप_प्रकार entire_size = size + range_beक्रमe + range_after;

	अगर (mem_type != USE_MALLOC && mem_type != USE_MMAP &&
	    mem_type != USE_MPROTECT) अणु
		ksft_prपूर्णांक_msg("FAIL: Invalid allocate request\n");
		वापस शून्य;
	पूर्ण
	अगर (mem_type == USE_MALLOC)
		वापस दो_स्मृति(entire_size) + range_beक्रमe;

	prot_flag = PROT_READ | PROT_WRITE;
	अगर (mem_type == USE_MMAP)
		prot_flag |= PROT_MTE;

	map_flag = mapping;
	अगर (fd == -1)
		map_flag = MAP_ANONYMOUS | map_flag;
	अगर (!(mapping & MAP_SHARED))
		map_flag |= MAP_PRIVATE;
	ptr = mmap(शून्य, entire_size, prot_flag, map_flag, fd, 0);
	अगर (ptr == MAP_FAILED) अणु
		ksft_prपूर्णांक_msg("FAIL: mmap allocation\n");
		वापस शून्य;
	पूर्ण
	अगर (mem_type == USE_MPROTECT) अणु
		अगर (mprotect(ptr, entire_size, prot_flag | PROT_MTE)) अणु
			munmap(ptr, size);
			ksft_prपूर्णांक_msg("FAIL: mprotect PROT_MTE property\n");
			वापस शून्य;
		पूर्ण
	पूर्ण
	अगर (tags)
		ptr = mte_insert_tags(ptr + range_beक्रमe, size);
	वापस ptr;
पूर्ण

व्योम *mte_allocate_memory_tag_range(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
				    माप_प्रकार range_beक्रमe, माप_प्रकार range_after)
अणु
	वापस __mte_allocate_memory_range(size, mem_type, mapping, range_beक्रमe,
					   range_after, true, -1);
पूर्ण

व्योम *mte_allocate_memory(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping, bool tags)
अणु
	वापस __mte_allocate_memory_range(size, mem_type, mapping, 0, 0, tags, -1);
पूर्ण

व्योम *mte_allocate_file_memory(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping, bool tags, पूर्णांक fd)
अणु
	पूर्णांक index;
	अक्षर buffer[INIT_BUFFER_SIZE];

	अगर (mem_type != USE_MPROTECT && mem_type != USE_MMAP) अणु
		ksft_prपूर्णांक_msg("FAIL: Invalid mmap file request\n");
		वापस शून्य;
	पूर्ण
	/* Initialize the file क्रम mappable size */
	lseek(fd, 0, शुरू_से);
	क्रम (index = INIT_BUFFER_SIZE; index < size; index += INIT_BUFFER_SIZE) अणु
		अगर (ग_लिखो(fd, buffer, INIT_BUFFER_SIZE) != INIT_BUFFER_SIZE) अणु
			लिखो_त्रुटि("initialising buffer");
			वापस शून्य;
		पूर्ण
	पूर्ण
	index -= INIT_BUFFER_SIZE;
	अगर (ग_लिखो(fd, buffer, size - index) != size - index) अणु
		लिखो_त्रुटि("initialising buffer");
		वापस शून्य;
	पूर्ण
	वापस __mte_allocate_memory_range(size, mem_type, mapping, 0, 0, tags, fd);
पूर्ण

व्योम *mte_allocate_file_memory_tag_range(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
					 माप_प्रकार range_beक्रमe, माप_प्रकार range_after, पूर्णांक fd)
अणु
	पूर्णांक index;
	अक्षर buffer[INIT_BUFFER_SIZE];
	पूर्णांक map_size = size + range_beक्रमe + range_after;

	अगर (mem_type != USE_MPROTECT && mem_type != USE_MMAP) अणु
		ksft_prपूर्णांक_msg("FAIL: Invalid mmap file request\n");
		वापस शून्य;
	पूर्ण
	/* Initialize the file क्रम mappable size */
	lseek(fd, 0, शुरू_से);
	क्रम (index = INIT_BUFFER_SIZE; index < map_size; index += INIT_BUFFER_SIZE)
		अगर (ग_लिखो(fd, buffer, INIT_BUFFER_SIZE) != INIT_BUFFER_SIZE) अणु
			लिखो_त्रुटि("initialising buffer");
			वापस शून्य;
		पूर्ण
	index -= INIT_BUFFER_SIZE;
	अगर (ग_लिखो(fd, buffer, map_size - index) != map_size - index) अणु
		लिखो_त्रुटि("initialising buffer");
		वापस शून्य;
	पूर्ण
	वापस __mte_allocate_memory_range(size, mem_type, mapping, range_beक्रमe,
					   range_after, true, fd);
पूर्ण

अटल व्योम __mte_मुक्त_memory_range(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type,
				    माप_प्रकार range_beक्रमe, माप_प्रकार range_after, bool tags)
अणु
	चयन (mem_type) अणु
	हाल USE_MALLOC:
		मुक्त(ptr - range_beक्रमe);
		अवरोध;
	हाल USE_MMAP:
	हाल USE_MPROTECT:
		अगर (tags)
			mte_clear_tags(ptr, size);
		munmap(ptr - range_beक्रमe, size + range_beक्रमe + range_after);
		अवरोध;
	शेष:
		ksft_prपूर्णांक_msg("FAIL: Invalid free request\n");
		अवरोध;
	पूर्ण
पूर्ण

व्योम mte_मुक्त_memory_tag_range(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type,
			       माप_प्रकार range_beक्रमe, माप_प्रकार range_after)
अणु
	__mte_मुक्त_memory_range(ptr, size, mem_type, range_beक्रमe, range_after, true);
पूर्ण

व्योम mte_मुक्त_memory(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type, bool tags)
अणु
	__mte_मुक्त_memory_range(ptr, size, mem_type, 0, 0, tags);
पूर्ण

व्योम mte_initialize_current_context(पूर्णांक mode, uपूर्णांकptr_t ptr, sमाप_प्रकार range)
अणु
	cur_mte_cxt.fault_valid = false;
	cur_mte_cxt.trig_addr = ptr;
	cur_mte_cxt.trig_range = range;
	अगर (mode == MTE_SYNC_ERR)
		cur_mte_cxt.trig_si_code = SEGV_MTESERR;
	अन्यथा अगर (mode == MTE_ASYNC_ERR)
		cur_mte_cxt.trig_si_code = SEGV_MTEAERR;
	अन्यथा
		cur_mte_cxt.trig_si_code = 0;
पूर्ण

पूर्णांक mte_चयन_mode(पूर्णांक mte_option, अचिन्हित दीर्घ incl_mask)
अणु
	अचिन्हित दीर्घ en = 0;

	अगर (!(mte_option == MTE_SYNC_ERR || mte_option == MTE_ASYNC_ERR ||
	      mte_option == MTE_NONE_ERR || incl_mask <= MTE_ALLOW_NON_ZERO_TAG)) अणु
		ksft_prपूर्णांक_msg("FAIL: Invalid mte config option\n");
		वापस -EINVAL;
	पूर्ण
	en = PR_TAGGED_ADDR_ENABLE;
	अगर (mte_option == MTE_SYNC_ERR)
		en |= PR_MTE_TCF_SYNC;
	अन्यथा अगर (mte_option == MTE_ASYNC_ERR)
		en |= PR_MTE_TCF_ASYNC;
	अन्यथा अगर (mte_option == MTE_NONE_ERR)
		en |= PR_MTE_TCF_NONE;

	en |= (incl_mask << PR_MTE_TAG_SHIFT);
	/* Enable address tagging ABI, mte error reporting mode and tag inclusion mask. */
	अगर (prctl(PR_SET_TAGGED_ADDR_CTRL, en, 0, 0, 0) != 0) अणु
		ksft_prपूर्णांक_msg("FAIL:prctl PR_SET_TAGGED_ADDR_CTRL for mte mode\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mte_शेष_setup(व्योम)
अणु
	अचिन्हित दीर्घ hwcaps2 = getauxval(AT_HWCAP2);
	अचिन्हित दीर्घ en = 0;
	पूर्णांक ret;

	अगर (!(hwcaps2 & HWCAP2_MTE)) अणु
		ksft_prपूर्णांक_msg("FAIL: MTE features unavailable\n");
		वापस KSFT_SKIP;
	पूर्ण
	/* Get current mte mode */
	ret = prctl(PR_GET_TAGGED_ADDR_CTRL, en, 0, 0, 0);
	अगर (ret < 0) अणु
		ksft_prपूर्णांक_msg("FAIL:prctl PR_GET_TAGGED_ADDR_CTRL with error =%d\n", ret);
		वापस KSFT_FAIL;
	पूर्ण
	अगर (ret & PR_MTE_TCF_SYNC)
		mte_cur_mode = MTE_SYNC_ERR;
	अन्यथा अगर (ret & PR_MTE_TCF_ASYNC)
		mte_cur_mode = MTE_ASYNC_ERR;
	अन्यथा अगर (ret & PR_MTE_TCF_NONE)
		mte_cur_mode = MTE_NONE_ERR;

	mte_cur_pstate_tco = mte_get_pstate_tco();
	/* Disable PSTATE.TCO */
	mte_disable_pstate_tco();
	वापस 0;
पूर्ण

व्योम mte_restore_setup(व्योम)
अणु
	mte_चयन_mode(mte_cur_mode, MTE_ALLOW_NON_ZERO_TAG);
	अगर (mte_cur_pstate_tco == MT_PSTATE_TCO_EN)
		mte_enable_pstate_tco();
	अन्यथा अगर (mte_cur_pstate_tco == MT_PSTATE_TCO_DIS)
		mte_disable_pstate_tco();
पूर्ण

पूर्णांक create_temp_file(व्योम)
अणु
	पूर्णांक fd;
	अक्षर filename[] = "/dev/shm/tmp_XXXXXX";

	/* Create a file in the पंचांगpfs fileप्रणाली */
	fd = mkstemp(&filename[0]);
	अगर (fd == -1) अणु
		लिखो_त्रुटि(filename);
		ksft_prपूर्णांक_msg("FAIL: Unable to open temporary file\n");
		वापस 0;
	पूर्ण
	unlink(&filename[0]);
	वापस fd;
पूर्ण
