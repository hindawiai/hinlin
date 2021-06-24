<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/auxv.h>
#समावेश "defines.h"
#समावेश "main.h"
#समावेश "../kselftest.h"

अटल स्थिर uपूर्णांक64_t MAGIC = 0x1122334455667788ULL;
vdso_sgx_enter_enclave_t eenter;

काष्ठा vdso_symtab अणु
	Elf64_Sym *elf_symtab;
	स्थिर अक्षर *elf_symstrtab;
	Elf64_Word *elf_hashtab;
पूर्ण;

अटल Elf64_Dyn *vdso_get_dyntab(व्योम *addr)
अणु
	Elf64_Ehdr *ehdr = addr;
	Elf64_Phdr *phdrtab = addr + ehdr->e_phoff;
	पूर्णांक i;

	क्रम (i = 0; i < ehdr->e_phnum; i++)
		अगर (phdrtab[i].p_type == PT_DYNAMIC)
			वापस addr + phdrtab[i].p_offset;

	वापस शून्य;
पूर्ण

अटल व्योम *vdso_get_dyn(व्योम *addr, Elf64_Dyn *dyntab, Elf64_Sxword tag)
अणु
	पूर्णांक i;

	क्रम (i = 0; dyntab[i].d_tag != DT_शून्य; i++)
		अगर (dyntab[i].d_tag == tag)
			वापस addr + dyntab[i].d_un.d_ptr;

	वापस शून्य;
पूर्ण

अटल bool vdso_get_symtab(व्योम *addr, काष्ठा vdso_symtab *symtab)
अणु
	Elf64_Dyn *dyntab = vdso_get_dyntab(addr);

	symtab->elf_symtab = vdso_get_dyn(addr, dyntab, DT_SYMTAB);
	अगर (!symtab->elf_symtab)
		वापस false;

	symtab->elf_symstrtab = vdso_get_dyn(addr, dyntab, DT_STRTAB);
	अगर (!symtab->elf_symstrtab)
		वापस false;

	symtab->elf_hashtab = vdso_get_dyn(addr, dyntab, DT_HASH);
	अगर (!symtab->elf_hashtab)
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ elf_sym_hash(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ h = 0, high;

	जबतक (*name) अणु
		h = (h << 4) + *name++;
		high = h & 0xf0000000;

		अगर (high)
			h ^= high >> 24;

		h &= ~high;
	पूर्ण

	वापस h;
पूर्ण

अटल Elf64_Sym *vdso_symtab_get(काष्ठा vdso_symtab *symtab, स्थिर अक्षर *name)
अणु
	Elf64_Word bucketnum = symtab->elf_hashtab[0];
	Elf64_Word *buckettab = &symtab->elf_hashtab[2];
	Elf64_Word *chaपूर्णांकab = &symtab->elf_hashtab[2 + bucketnum];
	Elf64_Sym *sym;
	Elf64_Word i;

	क्रम (i = buckettab[elf_sym_hash(name) % bucketnum]; i != STN_UNDEF;
	     i = chaपूर्णांकab[i]) अणु
		sym = &symtab->elf_symtab[i];
		अगर (!म_भेद(name, &symtab->elf_symstrtab[sym->st_name]))
			वापस sym;
	पूर्ण

	वापस शून्य;
पूर्ण

bool report_results(काष्ठा sgx_enclave_run *run, पूर्णांक ret, uपूर्णांक64_t result,
		  स्थिर अक्षर *test)
अणु
	bool valid = true;

	अगर (ret) अणु
		म_लिखो("FAIL: %s() returned: %d\n", test, ret);
		valid = false;
	पूर्ण

	अगर (run->function != EEXIT) अणु
		म_लिखो("FAIL: %s() function, expected: %u, got: %u\n", test, EEXIT,
		       run->function);
		valid = false;
	पूर्ण

	अगर (result != MAGIC) अणु
		म_लिखो("FAIL: %s(), expected: 0x%lx, got: 0x%lx\n", test, MAGIC,
		       result);
		valid = false;
	पूर्ण

	अगर (run->user_data) अणु
		म_लिखो("FAIL: %s() user data, expected: 0x0, got: 0x%llx\n",
		       test, run->user_data);
		valid = false;
	पूर्ण

	वापस valid;
पूर्ण

अटल पूर्णांक user_handler(दीर्घ rdi, दीर्घ rsi, दीर्घ rdx, दीर्घ ursp, दीर्घ r8, दीर्घ r9,
			काष्ठा sgx_enclave_run *run)
अणु
	run->user_data = 0;
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा sgx_enclave_run run;
	काष्ठा vdso_symtab symtab;
	Elf64_Sym *eenter_sym;
	uपूर्णांक64_t result = 0;
	काष्ठा encl encl;
	अचिन्हित पूर्णांक i;
	व्योम *addr;
	पूर्णांक ret;

	स_रखो(&run, 0, माप(run));

	अगर (!encl_load("test_encl.elf", &encl)) अणु
		encl_delete(&encl);
		ksft_निकास_skip("cannot load enclaves\n");
	पूर्ण

	अगर (!encl_measure(&encl))
		जाओ err;

	अगर (!encl_build(&encl))
		जाओ err;

	/*
	 * An enclave consumer only must करो this.
	 */
	क्रम (i = 0; i < encl.nr_segments; i++) अणु
		काष्ठा encl_segment *seg = &encl.segment_tbl[i];

		addr = mmap((व्योम *)encl.encl_base + seg->offset, seg->size,
			    seg->prot, MAP_SHARED | MAP_FIXED, encl.fd, 0);
		अगर (addr == MAP_FAILED) अणु
			लिखो_त्रुटि("mmap() segment failed");
			निकास(KSFT_FAIL);
		पूर्ण
	पूर्ण

	स_रखो(&run, 0, माप(run));
	run.tcs = encl.encl_base;

	/* Get vDSO base address */
	addr = (व्योम *)getauxval(AT_SYSINFO_EHDR);
	अगर (!addr)
		जाओ err;

	अगर (!vdso_get_symtab(addr, &symtab))
		जाओ err;

	eenter_sym = vdso_symtab_get(&symtab, "__vdso_sgx_enter_enclave");
	अगर (!eenter_sym)
		जाओ err;

	eenter = addr + eenter_sym->st_value;

	ret = sgx_call_vdso((व्योम *)&MAGIC, &result, 0, EENTER, शून्य, शून्य, &run);
	अगर (!report_results(&run, ret, result, "sgx_call_vdso"))
		जाओ err;


	/* Invoke the vDSO directly. */
	result = 0;
	ret = eenter((अचिन्हित दीर्घ)&MAGIC, (अचिन्हित दीर्घ)&result, 0, EENTER,
		     0, 0, &run);
	अगर (!report_results(&run, ret, result, "eenter"))
		जाओ err;

	/* And with an निकास handler. */
	run.user_handler = (__u64)user_handler;
	run.user_data = 0xdeadbeef;
	ret = eenter((अचिन्हित दीर्घ)&MAGIC, (अचिन्हित दीर्घ)&result, 0, EENTER,
		     0, 0, &run);
	अगर (!report_results(&run, ret, result, "user_handler"))
		जाओ err;

	म_लिखो("SUCCESS\n");
	encl_delete(&encl);
	निकास(KSFT_PASS);

err:
	encl_delete(&encl);
	निकास(KSFT_FAIL);
पूर्ण
