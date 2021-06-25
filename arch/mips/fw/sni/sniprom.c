<शैली गुरु>
/*
 * Big Endian PROM code क्रम SNI RM machines
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005-2006 Florian Lohoff (flo@rfc822.org)
 * Copyright (C) 2005-2006 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/माला.स>
#समावेश <linux/console.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/mipsprom.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/setup.h>

/* special SNI prom calls */
/*
 * This करोes not exist in all proms - SINIX compares
 * the prom env variable "version" against "2.0008"
 * or greater. If lesser it tries to probe पूर्णांकeresting
 * रेजिस्टरs
 */
#घोषणा PROM_GET_MEMCONF	58
#घोषणा PROM_GET_HWCONF		61

#घोषणा PROM_VEC		(u64 *)CKSEG1ADDR(0x1fc00000)
#घोषणा PROM_ENTRY(x)		(PROM_VEC + (x))

#घोषणा ___prom_अक्षर_दो		((पूर्णांक *(*)(पूर्णांक))PROM_ENTRY(PROM_PUTCHAR))
#घोषणा ___prom_दो_पर्या		((अक्षर *(*)(अक्षर *))PROM_ENTRY(PROM_GETENV))
#घोषणा ___prom_get_memconf	((व्योम (*)(व्योम *))PROM_ENTRY(PROM_GET_MEMCONF))
#घोषणा ___prom_get_hwconf	((u32 (*)(व्योम))PROM_ENTRY(PROM_GET_HWCONF))

#अगर_घोषित CONFIG_64BIT

/* O32 stack has to be 8-byte aligned. */
अटल u64 o32_stk[4096];
#घोषणा O32_STK	  (&o32_stk[ARRAY_SIZE(o32_stk)])

#घोषणा __PROM_O32(fun, arg) fun arg __यंत्र__(#fun); \
				     __यंत्र__(#fun " = call_o32")

पूर्णांक   __PROM_O32(__prom_अक्षर_दो, (पूर्णांक *(*)(पूर्णांक), व्योम *, पूर्णांक));
अक्षर *__PROM_O32(__prom_दो_पर्या, (अक्षर *(*)(अक्षर *), व्योम *, अक्षर *));
व्योम  __PROM_O32(__prom_get_memconf, (व्योम (*)(व्योम *), व्योम *, व्योम *));
u32   __PROM_O32(__prom_get_hwconf, (u32 (*)(व्योम), व्योम *));

#घोषणा _prom_अक्षर_दो(x)     __prom_अक्षर_दो(___prom_अक्षर_दो, O32_STK, x)
#घोषणा _prom_दो_पर्या(x)	     __prom_दो_पर्या(___prom_दो_पर्या, O32_STK, x)
#घोषणा _prom_get_memconf(x) __prom_get_memconf(___prom_get_memconf, O32_STK, x)
#घोषणा _prom_get_hwconf()   __prom_get_hwconf(___prom_get_hwconf, O32_STK)

#अन्यथा
#घोषणा _prom_अक्षर_दो(x)     ___prom_अक्षर_दो(x)
#घोषणा _prom_दो_पर्या(x)	     ___prom_दो_पर्या(x)
#घोषणा _prom_get_memconf(x) ___prom_get_memconf(x)
#घोषणा _prom_get_hwconf(x)  ___prom_get_hwconf(x)
#पूर्ण_अगर

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	_prom_अक्षर_दो(c);
पूर्ण


अक्षर *prom_दो_पर्या(अक्षर *s)
अणु
	वापस _prom_दो_पर्या(s);
पूर्ण

व्योम *prom_get_hwconf(व्योम)
अणु
	u32 hwconf = _prom_get_hwconf();

	अगर (hwconf == 0xffffffff)
		वापस शून्य;

	वापस (व्योम *)CKSEG1ADDR(hwconf);
पूर्ण

/*
 * /proc/cpuinfo प्रणाली type
 *
 */
अक्षर *प्रणाली_type = "Unknown";
स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस प्रणाली_type;
पूर्ण

अटल व्योम __init sni_mem_init(व्योम)
अणु
	पूर्णांक i, memsize;
	काष्ठा membank अणु
		u32		size;
		u32		base;
		u32		size2;
		u32		pad1;
		u32		pad2;
	पूर्ण memconf[8];
	पूर्णांक brd_type = *(अचिन्हित अक्षर *)SNI_IDPROM_BRDTYPE;


	/* MemSIZE from prom in 16MByte chunks */
	memsize = *((अचिन्हित अक्षर *) SNI_IDPROM_MEMSIZE) * 16;

	pr_debug("IDProm memsize: %u MByte\n", memsize);

	/* get memory bank layout from prom */
	_prom_get_memconf(&memconf);

	pr_debug("prom_get_mem_conf memory configuration:\n");
	क्रम (i = 0; i < 8 && memconf[i].size; i++) अणु
		अगर (brd_type == SNI_BRD_PCI_TOWER ||
		    brd_type == SNI_BRD_PCI_TOWER_CPLUS) अणु
			अगर (memconf[i].base >= 0x20000000 &&
			    memconf[i].base <  0x30000000)
				memconf[i].base -= 0x20000000;
		पूर्ण
		pr_debug("Bank%d: %08x @ %08x\n", i,
			memconf[i].size, memconf[i].base);
		memblock_add(memconf[i].base, memconf[i].size);
	पूर्ण
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	पूर्णांक argc = fw_arg0;
	u32 *argv = (u32 *)CKSEG0ADDR(fw_arg1);
	पूर्णांक i;

	sni_mem_init();

	/* copy prom cmdline parameters to kernel cmdline */
	क्रम (i = 1; i < argc; i++) अणु
		म_जोड़ो(arcs_cmdline, (अक्षर *)CKSEG0ADDR(argv[i]));
		अगर (i < (argc - 1))
			म_जोड़ो(arcs_cmdline, " ");
	पूर्ण
पूर्ण
