<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"

#समावेश "of.h"

प्रकार u32 prom_arg_t;

/* The following काष्ठाure is used to communicate with खोलो firmware.
 * All arguments in and out are in big endian क्रमmat. */
काष्ठा prom_args अणु
	__be32 service;	/* Address of service name string. */
	__be32 nargs;	/* Number of input arguments. */
	__be32 nret;	/* Number of output arguments. */
	__be32 args[10];	/* Input/output arguments. */
पूर्ण;

#अगर_घोषित __घातerpc64__
बाह्य पूर्णांक prom(व्योम *);
#अन्यथा
अटल पूर्णांक (*prom) (व्योम *);
#पूर्ण_अगर

व्योम of_init(व्योम *promptr)
अणु
#अगर_अघोषित __घातerpc64__
	prom = (पूर्णांक (*)(व्योम *))promptr;
#पूर्ण_अगर
पूर्ण

#घोषणा ADDR(x)		(u32)(अचिन्हित दीर्घ)(x)

पूर्णांक of_call_prom(स्थिर अक्षर *service, पूर्णांक nargs, पूर्णांक nret, ...)
अणु
	पूर्णांक i;
	काष्ठा prom_args args;
	बहु_सूची list;

	args.service = cpu_to_be32(ADDR(service));
	args.nargs = cpu_to_be32(nargs);
	args.nret = cpu_to_be32(nret);

	बहु_शुरू(list, nret);
	क्रम (i = 0; i < nargs; i++)
		args.args[i] = cpu_to_be32(बहु_तर्क(list, prom_arg_t));
	बहु_पूर्ण(list);

	क्रम (i = 0; i < nret; i++)
		args.args[nargs+i] = 0;

	अगर (prom(&args) < 0)
		वापस PROM_ERROR;

	वापस (nret > 0) ? be32_to_cpu(args.args[nargs]) : 0;
पूर्ण

अटल पूर्णांक of_call_prom_ret(स्थिर अक्षर *service, पूर्णांक nargs, पूर्णांक nret,
			    prom_arg_t *rets, ...)
अणु
	पूर्णांक i;
	काष्ठा prom_args args;
	बहु_सूची list;

	args.service = cpu_to_be32(ADDR(service));
	args.nargs = cpu_to_be32(nargs);
	args.nret = cpu_to_be32(nret);

	बहु_शुरू(list, rets);
	क्रम (i = 0; i < nargs; i++)
		args.args[i] = cpu_to_be32(बहु_तर्क(list, prom_arg_t));
	बहु_पूर्ण(list);

	क्रम (i = 0; i < nret; i++)
		args.args[nargs+i] = 0;

	अगर (prom(&args) < 0)
		वापस PROM_ERROR;

	अगर (rets != शून्य)
		क्रम (i = 1; i < nret; ++i)
			rets[i-1] = be32_to_cpu(args.args[nargs+i]);

	वापस (nret > 0) ? be32_to_cpu(args.args[nargs]) : 0;
पूर्ण

/* वापसs true अगर s2 is a prefix of s1 */
अटल पूर्णांक string_match(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	क्रम (; *s2; ++s2)
		अगर (*s1++ != *s2)
			वापस 0;
	वापस 1;
पूर्ण

/*
 * Older OF's require that when claiming a specअगरic range of addresses,
 * we claim the physical space in the /memory node and the भव
 * space in the chosen mmu node, and then करो a map operation to
 * map भव to physical.
 */
अटल पूर्णांक need_map = -1;
अटल ihandle chosen_mmu;
अटल ihandle memory;

अटल पूर्णांक check_of_version(व्योम)
अणु
	phandle oprom, chosen;
	अक्षर version[64];

	oprom = of_finddevice("/openprom");
	अगर (oprom == (phandle) -1)
		वापस 0;
	अगर (of_getprop(oprom, "model", version, माप(version)) <= 0)
		वापस 0;
	version[माप(version)-1] = 0;
	म_लिखो("OF version = '%s'\r\n", version);
	अगर (!string_match(version, "Open Firmware, 1.")
	    && !string_match(version, "FirmWorks,3."))
		वापस 0;
	chosen = of_finddevice("/chosen");
	अगर (chosen == (phandle) -1) अणु
		chosen = of_finddevice("/chosen@0");
		अगर (chosen == (phandle) -1) अणु
			म_लिखो("no chosen\n");
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (of_getprop(chosen, "mmu", &chosen_mmu, माप(chosen_mmu)) <= 0) अणु
		म_लिखो("no mmu\n");
		वापस 0;
	पूर्ण
	memory = of_call_prom("open", 1, 1, "/memory");
	अगर (memory == PROM_ERROR) अणु
		memory = of_call_prom("open", 1, 1, "/memory@0");
		अगर (memory == PROM_ERROR) अणु
			म_लिखो("no memory node\n");
			वापस 0;
		पूर्ण
	पूर्ण
	म_लिखो("old OF detected\r\n");
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक of_claim(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ size,
		      अचिन्हित दीर्घ align)
अणु
	पूर्णांक ret;
	prom_arg_t result;

	अगर (need_map < 0)
		need_map = check_of_version();
	अगर (align || !need_map)
		वापस of_call_prom("claim", 3, 1, virt, size, align);

	ret = of_call_prom_ret("call-method", 5, 2, &result, "claim", memory,
			       align, size, virt);
	अगर (ret != 0 || result == -1)
		वापस  -1;
	ret = of_call_prom_ret("call-method", 5, 2, &result, "claim", chosen_mmu,
			       align, size, virt);
	/* 0x12 == coherent + पढ़ो/ग_लिखो */
	ret = of_call_prom("call-method", 6, 1, "map", chosen_mmu,
			   0x12, size, virt, virt);
	वापस virt;
पूर्ण

व्योम *of_vmlinux_alloc(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)_start, end = (अचिन्हित दीर्घ)_end;
	अचिन्हित दीर्घ addr;
	व्योम *p;

	/* With some older POWER4 firmware we need to claim the area the kernel
	 * will reside in.  Newer firmwares करोn't need this so we just ignore
	 * the वापस value.
	 */
	addr = (अचिन्हित दीर्घ) of_claim(start, end - start, 0);
	म_लिखो("Trying to claim from 0x%lx to 0x%lx (0x%lx) got %lx\r\n",
	       start, end, end - start, addr);

	p = दो_स्मृति(size);
	अगर (!p)
		fatal("Can't allocate memory for kernel image!\n\r");

	वापस p;
पूर्ण

व्योम of_निकास(व्योम)
अणु
	of_call_prom("exit", 0, 0);
पूर्ण

/*
 * OF device tree routines
 */
व्योम *of_finddevice(स्थिर अक्षर *name)
अणु
	वापस (व्योम *) (अचिन्हित दीर्घ) of_call_prom("finddevice", 1, 1, name);
पूर्ण

पूर्णांक of_getprop(स्थिर व्योम *phandle, स्थिर अक्षर *name, व्योम *buf,
	       स्थिर पूर्णांक buflen)
अणु
	वापस of_call_prom("getprop", 4, 1, phandle, name, buf, buflen);
पूर्ण

पूर्णांक of_setprop(स्थिर व्योम *phandle, स्थिर अक्षर *name, स्थिर व्योम *buf,
	       स्थिर पूर्णांक buflen)
अणु
	वापस of_call_prom("setprop", 4, 1, phandle, name, buf, buflen);
पूर्ण
