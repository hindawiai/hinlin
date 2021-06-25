<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"

#समावेश "of.h"

/* Value picked to match that used by yaboot */
#घोषणा PROG_START	0x01400000	/* only used on 64-bit प्रणालीs */
#घोषणा RAM_END		(512<<20)	/* Fixme: use OF */
#घोषणा	ONE_MB		0x100000



अटल अचिन्हित दीर्घ claim_base;

व्योम epapr_platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
			 अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7);

अटल व्योम *of_try_claim(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr = 0;

	अगर (claim_base == 0)
		claim_base = _ALIGN_UP((अचिन्हित दीर्घ)_end, ONE_MB);

	क्रम(; claim_base < RAM_END; claim_base += ONE_MB) अणु
#अगर_घोषित DEBUG
		म_लिखो("    trying: 0x%08lx\n\r", claim_base);
#पूर्ण_अगर
		addr = (अचिन्हित दीर्घ) of_claim(claim_base, size, 0);
		अगर (addr != PROM_ERROR)
			अवरोध;
	पूर्ण
	अगर (addr == 0)
		वापस शून्य;
	claim_base = PAGE_ALIGN(claim_base + size);
	वापस (व्योम *)addr;
पूर्ण

अटल व्योम of_image_hdr(स्थिर व्योम *hdr)
अणु
	स्थिर Elf64_Ehdr *elf64 = hdr;

	अगर (elf64->e_ident[EI_CLASS] == ELFCLASS64) अणु
		/*
		 * Maपूर्णांकain a "magic" minimum address. This keeps some older
		 * firmware platक्रमms running.
		 */
		अगर (claim_base < PROG_START)
			claim_base = PROG_START;
	पूर्ण
पूर्ण

अटल व्योम of_platक्रमm_init(अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2, व्योम *promptr)
अणु
	platक्रमm_ops.image_hdr = of_image_hdr;
	platक्रमm_ops.दो_स्मृति = of_try_claim;
	platक्रमm_ops.निकास = of_निकास;
	platक्रमm_ops.vmlinux_alloc = of_vmlinux_alloc;

	dt_ops.finddevice = of_finddevice;
	dt_ops.getprop = of_getprop;
	dt_ops.setprop = of_setprop;

	of_console_init();

	of_init(promptr);
	loader_info.promptr = promptr;
	अगर (a1 && a2 && a2 != 0xdeadbeef) अणु
		loader_info.initrd_addr = a1;
		loader_info.initrd_size = a2;
	पूर्ण
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	/* Detect OF vs. ePAPR boot */
	अगर (r5)
		of_platक्रमm_init(r3, r4, (व्योम *)r5);
	अन्यथा
		epapr_platक्रमm_init(r3, r4, r5, r6, r7);
पूर्ण

