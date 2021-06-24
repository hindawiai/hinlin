<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  arch/um/kernel/elf_aux.c
 *
 *  Scan the Elf auxiliary vector provided by the host to extract
 *  inक्रमmation about vsyscall-page, etc.
 *
 *  Copyright (C) 2004 Fujitsu Siemens Computers GmbH
 *  Author: Boकरो Stroesser (boकरो.stroesser@fujitsu-siemens.com)
 */
#समावेश <elf.h>
#समावेश <मानकघोष.स>
#समावेश <init.h>
#समावेश <elf_user.h>
#समावेश <mem_user.h>

प्रकार Elf32_auxv_t elf_auxv_t;

/* These are initialized very early in boot and never changed */
अक्षर * elf_aux_platक्रमm;
बाह्य दीर्घ elf_aux_hwcap;
अचिन्हित दीर्घ vsyscall_ehdr;
अचिन्हित दीर्घ vsyscall_end;
अचिन्हित दीर्घ __kernel_vsyscall;

__init व्योम scan_elf_aux( अक्षर **envp)
अणु
	दीर्घ page_size = 0;
	elf_auxv_t * auxv;

	जबतक ( *envp++ != शून्य) ;

	क्रम ( auxv = (elf_auxv_t *)envp; auxv->a_type != AT_शून्य; auxv++) अणु
		चयन ( auxv->a_type ) अणु
			हाल AT_SYSINFO:
				__kernel_vsyscall = auxv->a_un.a_val;
				/* See अगर the page is under TASK_SIZE */
				अगर (__kernel_vsyscall < (अचिन्हित दीर्घ) envp)
					__kernel_vsyscall = 0;
				अवरोध;
			हाल AT_SYSINFO_EHDR:
				vsyscall_ehdr = auxv->a_un.a_val;
				/* See अगर the page is under TASK_SIZE */
				अगर (vsyscall_ehdr < (अचिन्हित दीर्घ) envp)
					vsyscall_ehdr = 0;
				अवरोध;
			हाल AT_HWCAP:
				elf_aux_hwcap = auxv->a_un.a_val;
				अवरोध;
			हाल AT_PLATFORM:
                                /* elf.h हटाओd the poपूर्णांकer elements from
                                 * a_un, so we have to use a_val, which is
                                 * all that's left.
                                 */
				elf_aux_platक्रमm =
					(अक्षर *) (दीर्घ) auxv->a_un.a_val;
				अवरोध;
			हाल AT_PAGESZ:
				page_size = auxv->a_un.a_val;
				अवरोध;
		पूर्ण
	पूर्ण
	अगर ( ! __kernel_vsyscall || ! vsyscall_ehdr ||
	     ! elf_aux_hwcap || ! elf_aux_platक्रमm ||
	     ! page_size || (vsyscall_ehdr % page_size) ) अणु
		__kernel_vsyscall = 0;
		vsyscall_ehdr = 0;
		elf_aux_hwcap = 0;
		elf_aux_platक्रमm = "i586";
	पूर्ण
	अन्यथा अणु
		vsyscall_end = vsyscall_ehdr + page_size;
	पूर्ण
पूर्ण
