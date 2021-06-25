<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vdso_test_अ_लोpu.c: Sample code to test parse_vdso.c and vDSO अ_लोpu()
 *
 * Copyright (c) 2020 Arm Ltd
 */

#समावेश <मानक_निवेशt.h>
#समावेश <elf.h>
#समावेश <मानकपन.स>
#समावेश <sys/auxv.h>
#समावेश <sys/समय.स>

#समावेश "../kselftest.h"
#समावेश "parse_vdso.h"

स्थिर अक्षर *version = "LINUX_2.6";
स्थिर अक्षर *name = "__vdso_getcpu";

काष्ठा अ_लोpu_cache;
प्रकार दीर्घ (*अ_लोpu_t)(अचिन्हित पूर्णांक *, अचिन्हित पूर्णांक *,
			 काष्ठा अ_लोpu_cache *);

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित दीर्घ sysinfo_ehdr;
	अचिन्हित पूर्णांक cpu, node;
	अ_लोpu_t get_cpu;
	दीर्घ ret;

	sysinfo_ehdr = getauxval(AT_SYSINFO_EHDR);
	अगर (!sysinfo_ehdr) अणु
		म_लिखो("AT_SYSINFO_EHDR is not present!\n");
		वापस KSFT_SKIP;
	पूर्ण

	vdso_init_from_sysinfo_ehdr(getauxval(AT_SYSINFO_EHDR));

	get_cpu = (अ_लोpu_t)vdso_sym(version, name);
	अगर (!get_cpu) अणु
		म_लिखो("Could not find %s\n", name);
		वापस KSFT_SKIP;
	पूर्ण

	ret = get_cpu(&cpu, &node, 0);
	अगर (ret == 0) अणु
		म_लिखो("Running on CPU %u node %u\n", cpu, node);
	पूर्ण अन्यथा अणु
		म_लिखो("%s failed\n", name);
		वापस KSFT_FAIL;
	पूर्ण

	वापस 0;
पूर्ण
