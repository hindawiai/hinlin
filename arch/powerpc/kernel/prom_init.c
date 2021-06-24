<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Procedures क्रम पूर्णांकerfacing to Open Firmware.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 * 
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com 
 */

#अघोषित DEBUG_PROM

/* we cannot use FORTIFY as it brings in new symbols */
#घोषणा __NO_FORTIFY

#समावेश <मानकतर्क.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/ultravisor-api.h>

#समावेश <linux/linux_logo.h>

/* All of prom_init bss lives here */
#घोषणा __prombss __section(".bss.prominit")

/*
 * Eventually bump that one up
 */
#घोषणा DEVTREE_CHUNK_SIZE	0x100000

/*
 * This is the size of the local memory reserve map that माला_लो copied
 * पूर्णांकo the boot params passed to the kernel. That size is totally
 * flexible as the kernel just पढ़ोs the list until it encounters an
 * entry with size 0, so it can be changed without अवरोधing binary
 * compatibility
 */
#घोषणा MEM_RESERVE_MAP_SIZE	8

/*
 * prom_init() is called very early on, beक्रमe the kernel text
 * and data have been mapped to KERNELBASE.  At this poपूर्णांक the code
 * is running at whatever address it has been loaded at.
 * On ppc32 we compile with -mrelocatable, which means that references
 * to बाह्य and अटल variables get relocated स्वतःmatically.
 * ppc64 objects are always relocatable, we just need to relocate the
 * TOC.
 *
 * Because OF may have mapped I/O devices पूर्णांकo the area starting at
 * KERNELBASE, particularly on CHRP machines, we can't safely call
 * OF once the kernel has been mapped to KERNELBASE.  Thereक्रमe all
 * OF calls must be करोne within prom_init().
 *
 * ADDR is used in calls to call_prom.  The 4th and following
 * arguments to call_prom should be 32-bit values.
 * On ppc64, 64 bit values are truncated to 32 bits (and
 * क्रमtunately करोn't get पूर्णांकerpreted as two arguments).
 */
#घोषणा ADDR(x)		(u32)(अचिन्हित दीर्घ)(x)

#अगर_घोषित CONFIG_PPC64
#घोषणा OF_WORKAROUNDS	0
#अन्यथा
#घोषणा OF_WORKAROUNDS	of_workarounds
अटल पूर्णांक of_workarounds __prombss;
#पूर्ण_अगर

#घोषणा OF_WA_CLAIM	1	/* करो phys/virt claim separately, then map */
#घोषणा OF_WA_LONGTRAIL	2	/* work around दीर्घtrail bugs */

#घोषणा PROM_BUG() करो अणु						\
        prom_म_लिखो("kernel BUG at %s line 0x%x!\n",		\
		    __खाता__, __LINE__);			\
	__builtin_trap();					\
पूर्ण जबतक (0)

#अगर_घोषित DEBUG_PROM
#घोषणा prom_debug(x...)	prom_म_लिखो(x)
#अन्यथा
#घोषणा prom_debug(x...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


प्रकार u32 prom_arg_t;

काष्ठा prom_args अणु
        __be32 service;
        __be32 nargs;
        __be32 nret;
        __be32 args[10];
पूर्ण;

काष्ठा prom_t अणु
	ihandle root;
	phandle chosen;
	पूर्णांक cpu;
	ihandle मानक_निकास;
	ihandle mmumap;
	ihandle memory;
पूर्ण;

काष्ठा mem_map_entry अणु
	__be64	base;
	__be64	size;
पूर्ण;

प्रकार __be32 cell_t;

बाह्य व्योम __start(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		    अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7, अचिन्हित दीर्घ r8,
		    अचिन्हित दीर्घ r9);

#अगर_घोषित CONFIG_PPC64
बाह्य पूर्णांक enter_prom(काष्ठा prom_args *args, अचिन्हित दीर्घ entry);
#अन्यथा
अटल अंतरभूत पूर्णांक enter_prom(काष्ठा prom_args *args, अचिन्हित दीर्घ entry)
अणु
	वापस ((पूर्णांक (*)(काष्ठा prom_args *))entry)(args);
पूर्ण
#पूर्ण_अगर

बाह्य व्योम copy_and_flush(अचिन्हित दीर्घ dest, अचिन्हित दीर्घ src,
			   अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset);

/* prom काष्ठाure */
अटल काष्ठा prom_t __prombss prom;

अटल अचिन्हित दीर्घ __prombss prom_entry;

अटल अक्षर __prombss of_मानक_निकास_device[256];
अटल अक्षर __prombss prom_scratch[256];

अटल अचिन्हित दीर्घ __prombss dt_header_start;
अटल अचिन्हित दीर्घ __prombss dt_काष्ठा_start, dt_काष्ठा_end;
अटल अचिन्हित दीर्घ __prombss dt_string_start, dt_string_end;

अटल अचिन्हित दीर्घ __prombss prom_initrd_start, prom_initrd_end;

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक __prombss prom_iommu_क्रमce_on;
अटल पूर्णांक __prombss prom_iommu_off;
अटल अचिन्हित दीर्घ __prombss prom_tce_alloc_start;
अटल अचिन्हित दीर्घ __prombss prom_tce_alloc_end;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
अटल bool __prombss prom_radix_disable;
अटल bool __prombss prom_radix_gtse_disable;
अटल bool __prombss prom_xive_disable;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SVM
अटल bool __prombss prom_svm_enable;
#पूर्ण_अगर

काष्ठा platक्रमm_support अणु
	bool hash_mmu;
	bool radix_mmu;
	bool radix_gtse;
	bool xive;
पूर्ण;

/* Platक्रमms codes are now obsolete in the kernel. Now only used within this
 * file and ultimately gone too. Feel मुक्त to change them अगर you need, they
 * are not shared with anything outside of this file anymore
 */
#घोषणा PLATFORM_PSERIES	0x0100
#घोषणा PLATFORM_PSERIES_LPAR	0x0101
#घोषणा PLATFORM_LPAR		0x0001
#घोषणा PLATFORM_POWERMAC	0x0400
#घोषणा PLATFORM_GENERIC	0x0500

अटल पूर्णांक __prombss of_platक्रमm;

अटल अक्षर __prombss prom_cmd_line[COMMAND_LINE_SIZE];

अटल अचिन्हित दीर्घ __prombss prom_memory_limit;

अटल अचिन्हित दीर्घ __prombss alloc_top;
अटल अचिन्हित दीर्घ __prombss alloc_top_high;
अटल अचिन्हित दीर्घ __prombss alloc_bottom;
अटल अचिन्हित दीर्घ __prombss rmo_top;
अटल अचिन्हित दीर्घ __prombss ram_top;

अटल काष्ठा mem_map_entry __prombss mem_reserve_map[MEM_RESERVE_MAP_SIZE];
अटल पूर्णांक __prombss mem_reserve_cnt;

अटल cell_t __prombss regbuf[1024];

अटल bool  __prombss rtas_has_query_cpu_stopped;


/*
 * Error results ... some OF calls will वापस "-1" on error, some
 * will वापस 0, some will वापस either. To simplअगरy, here are
 * macros to use with any ihandle or phandle वापस value to check अगर
 * it is valid
 */

#घोषणा PROM_ERROR		(-1u)
#घोषणा PHANDLE_VALID(p)	((p) != 0 && (p) != PROM_ERROR)
#घोषणा IHANDLE_VALID(i)	((i) != 0 && (i) != PROM_ERROR)

/* Copied from lib/string.c and lib/kstrtox.c */

अटल पूर्णांक __init prom_म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (1) अणु
		c1 = *cs++;
		c2 = *ct++;
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		अगर (!c1)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर __init *prom_म_नकल(अक्षर *dest, स्थिर अक्षर *src)
अणु
	अक्षर *पंचांगp = dest;

	जबतक ((*dest++ = *src++) != '\0')
		/* nothing */;
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक __init prom_म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (count) अणु
		c1 = *cs++;
		c2 = *ct++;
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		अगर (!c1)
			अवरोध;
		count--;
	पूर्ण
	वापस 0;
पूर्ण

अटल माप_प्रकार __init prom_म_माप(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	वापस sc - s;
पूर्ण

अटल पूर्णांक __init prom_स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1, *su2;
	पूर्णांक res = 0;

	क्रम (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		अगर ((res = *su1 - *su2) != 0)
			अवरोध;
	वापस res;
पूर्ण

अटल अक्षर __init *prom_म_माला(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	माप_प्रकार l1, l2;

	l2 = prom_म_माप(s2);
	अगर (!l2)
		वापस (अक्षर *)s1;
	l1 = prom_म_माप(s1);
	जबतक (l1 >= l2) अणु
		l1--;
		अगर (!prom_स_भेद(s1, s2, l2))
			वापस (अक्षर *)s1;
		s1++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल माप_प्रकार __init prom_strlcat(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	माप_प्रकार dsize = prom_म_माप(dest);
	माप_प्रकार len = prom_म_माप(src);
	माप_प्रकार res = dsize + len;

	/* This would be a bug */
	अगर (dsize >= count)
		वापस count;

	dest += dsize;
	count -= dsize;
	अगर (len >= count)
		len = count-1;
	स_नकल(dest, src, len);
	dest[len] = 0;
	वापस res;

पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
अटल पूर्णांक __init prom_strtobool(स्थिर अक्षर *s, bool *res)
अणु
	अगर (!s)
		वापस -EINVAL;

	चयन (s[0]) अणु
	हाल 'y':
	हाल 'Y':
	हाल '1':
		*res = true;
		वापस 0;
	हाल 'n':
	हाल 'N':
	हाल '0':
		*res = false;
		वापस 0;
	हाल 'o':
	हाल 'O':
		चयन (s[1]) अणु
		हाल 'n':
		हाल 'N':
			*res = true;
			वापस 0;
		हाल 'f':
		हाल 'F':
			*res = false;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/* This is the one and *ONLY* place where we actually call खोलो
 * firmware.
 */

अटल पूर्णांक __init call_prom(स्थिर अक्षर *service, पूर्णांक nargs, पूर्णांक nret, ...)
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

	अगर (enter_prom(&args, prom_entry) < 0)
		वापस PROM_ERROR;

	वापस (nret > 0) ? be32_to_cpu(args.args[nargs]) : 0;
पूर्ण

अटल पूर्णांक __init call_prom_ret(स्थिर अक्षर *service, पूर्णांक nargs, पूर्णांक nret,
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

	अगर (enter_prom(&args, prom_entry) < 0)
		वापस PROM_ERROR;

	अगर (rets != शून्य)
		क्रम (i = 1; i < nret; ++i)
			rets[i-1] = be32_to_cpu(args.args[nargs+i]);

	वापस (nret > 0) ? be32_to_cpu(args.args[nargs]) : 0;
पूर्ण


अटल व्योम __init prom_prपूर्णांक(स्थिर अक्षर *msg)
अणु
	स्थिर अक्षर *p, *q;

	अगर (prom.मानक_निकास == 0)
		वापस;

	क्रम (p = msg; *p != 0; p = q) अणु
		क्रम (q = p; *q != 0 && *q != '\n'; ++q)
			;
		अगर (q > p)
			call_prom("write", 3, 1, prom.मानक_निकास, p, q - p);
		अगर (*q == 0)
			अवरोध;
		++q;
		call_prom("write", 3, 1, prom.मानक_निकास, ADDR("\r\n"), 2);
	पूर्ण
पूर्ण


/*
 * Both prom_prपूर्णांक_hex & prom_prपूर्णांक_dec takes an अचिन्हित दीर्घ as input so that
 * we करो not need __uभागdi3 or __umoddi3 on 32bits.
 */
अटल व्योम __init prom_prपूर्णांक_hex(अचिन्हित दीर्घ val)
अणु
	पूर्णांक i, nibbles = माप(val)*2;
	अक्षर buf[माप(val)*2+1];

	क्रम (i = nibbles-1;  i >= 0;  i--) अणु
		buf[i] = (val & 0xf) + '0';
		अगर (buf[i] > '9')
			buf[i] += ('a'-'0'-10);
		val >>= 4;
	पूर्ण
	buf[nibbles] = '\0';
	call_prom("write", 3, 1, prom.मानक_निकास, buf, nibbles);
पूर्ण

/* max number of decimal digits in an अचिन्हित दीर्घ */
#घोषणा UL_DIGITS 21
अटल व्योम __init prom_prपूर्णांक_dec(अचिन्हित दीर्घ val)
अणु
	पूर्णांक i, size;
	अक्षर buf[UL_DIGITS+1];

	क्रम (i = UL_DIGITS-1; i >= 0;  i--) अणु
		buf[i] = (val % 10) + '0';
		val = val/10;
		अगर (val == 0)
			अवरोध;
	पूर्ण
	/* shअगरt stuff करोwn */
	size = UL_DIGITS - i;
	call_prom("write", 3, 1, prom.मानक_निकास, buf+i, size);
पूर्ण

__म_लिखो(1, 2)
अटल व्योम __init prom_म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	स्थिर अक्षर *p, *q, *s;
	बहु_सूची args;
	अचिन्हित दीर्घ v;
	दीर्घ vs;
	पूर्णांक n = 0;

	बहु_शुरू(args, क्रमmat);
	क्रम (p = क्रमmat; *p != 0; p = q) अणु
		क्रम (q = p; *q != 0 && *q != '\n' && *q != '%'; ++q)
			;
		अगर (q > p)
			call_prom("write", 3, 1, prom.मानक_निकास, p, q - p);
		अगर (*q == 0)
			अवरोध;
		अगर (*q == '\n') अणु
			++q;
			call_prom("write", 3, 1, prom.मानक_निकास,
				  ADDR("\r\n"), 2);
			जारी;
		पूर्ण
		++q;
		अगर (*q == 0)
			अवरोध;
		जबतक (*q == 'l') अणु
			++q;
			++n;
		पूर्ण
		चयन (*q) अणु
		हाल 's':
			++q;
			s = बहु_तर्क(args, स्थिर अक्षर *);
			prom_prपूर्णांक(s);
			अवरोध;
		हाल 'x':
			++q;
			चयन (n) अणु
			हाल 0:
				v = बहु_तर्क(args, अचिन्हित पूर्णांक);
				अवरोध;
			हाल 1:
				v = बहु_तर्क(args, अचिन्हित दीर्घ);
				अवरोध;
			हाल 2:
			शेष:
				v = बहु_तर्क(args, अचिन्हित दीर्घ दीर्घ);
				अवरोध;
			पूर्ण
			prom_prपूर्णांक_hex(v);
			अवरोध;
		हाल 'u':
			++q;
			चयन (n) अणु
			हाल 0:
				v = बहु_तर्क(args, अचिन्हित पूर्णांक);
				अवरोध;
			हाल 1:
				v = बहु_तर्क(args, अचिन्हित दीर्घ);
				अवरोध;
			हाल 2:
			शेष:
				v = बहु_तर्क(args, अचिन्हित दीर्घ दीर्घ);
				अवरोध;
			पूर्ण
			prom_prपूर्णांक_dec(v);
			अवरोध;
		हाल 'd':
			++q;
			चयन (n) अणु
			हाल 0:
				vs = बहु_तर्क(args, पूर्णांक);
				अवरोध;
			हाल 1:
				vs = बहु_तर्क(args, दीर्घ);
				अवरोध;
			हाल 2:
			शेष:
				vs = बहु_तर्क(args, दीर्घ दीर्घ);
				अवरोध;
			पूर्ण
			अगर (vs < 0) अणु
				prom_prपूर्णांक("-");
				vs = -vs;
			पूर्ण
			prom_prपूर्णांक_dec(vs);
			अवरोध;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(args);
पूर्ण


अटल अचिन्हित पूर्णांक __init prom_claim(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ align)
अणु

	अगर (align == 0 && (OF_WORKAROUNDS & OF_WA_CLAIM)) अणु
		/*
		 * Old OF requires we claim physical and भव separately
		 * and then map explicitly (assuming भव mode)
		 */
		पूर्णांक ret;
		prom_arg_t result;

		ret = call_prom_ret("call-method", 5, 2, &result,
				    ADDR("claim"), prom.memory,
				    align, size, virt);
		अगर (ret != 0 || result == -1)
			वापस -1;
		ret = call_prom_ret("call-method", 5, 2, &result,
				    ADDR("claim"), prom.mmumap,
				    align, size, virt);
		अगर (ret != 0) अणु
			call_prom("call-method", 4, 1, ADDR("release"),
				  prom.memory, size, virt);
			वापस -1;
		पूर्ण
		/* the 0x12 is M (coherence) + PP == पढ़ो/ग_लिखो */
		call_prom("call-method", 6, 1,
			  ADDR("map"), prom.mmumap, 0x12, size, virt, virt);
		वापस virt;
	पूर्ण
	वापस call_prom("claim", 3, 1, (prom_arg_t)virt, (prom_arg_t)size,
			 (prom_arg_t)align);
पूर्ण

अटल व्योम __init __attribute__((noवापस)) prom_panic(स्थिर अक्षर *reason)
अणु
	prom_prपूर्णांक(reason);
	/* Do not call निकास because it clears the screen on pmac
	 * it also causes some sort of द्विगुन-fault on early pmacs */
	अगर (of_platक्रमm == PLATFORM_POWERMAC)
		यंत्र("trap\n");

	/* ToDo: should put up an SRC here on pSeries */
	call_prom("exit", 0, 0);

	क्रम (;;)			/* should never get here */
		;
पूर्ण


अटल पूर्णांक __init prom_next_node(phandle *nodep)
अणु
	phandle node;

	अगर ((node = *nodep) != 0
	    && (*nodep = call_prom("child", 1, 1, node)) != 0)
		वापस 1;
	अगर ((*nodep = call_prom("peer", 1, 1, node)) != 0)
		वापस 1;
	क्रम (;;) अणु
		अगर ((node = call_prom("parent", 1, 1, node)) == 0)
			वापस 0;
		अगर ((*nodep = call_prom("peer", 1, 1, node)) != 0)
			वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __init prom_getprop(phandle node, स्थिर अक्षर *pname,
				      व्योम *value, माप_प्रकार valuelen)
अणु
	वापस call_prom("getprop", 4, 1, node, ADDR(pname),
			 (u32)(अचिन्हित दीर्घ) value, (u32) valuelen);
पूर्ण

अटल अंतरभूत पूर्णांक __init prom_getproplen(phandle node, स्थिर अक्षर *pname)
अणु
	वापस call_prom("getproplen", 2, 1, node, ADDR(pname));
पूर्ण

अटल व्योम add_string(अक्षर **str, स्थिर अक्षर *q)
अणु
	अक्षर *p = *str;

	जबतक (*q)
		*p++ = *q++;
	*p++ = ' ';
	*str = p;
पूर्ण

अटल अक्षर *tohex(अचिन्हित पूर्णांक x)
अणु
	अटल स्थिर अक्षर digits[] __initस्थिर = "0123456789abcdef";
	अटल अक्षर result[9] __prombss;
	पूर्णांक i;

	result[8] = 0;
	i = 8;
	करो अणु
		--i;
		result[i] = digits[x & 0xf];
		x >>= 4;
	पूर्ण जबतक (x != 0 && i > 0);
	वापस &result[i];
पूर्ण

अटल पूर्णांक __init prom_setprop(phandle node, स्थिर अक्षर *nodename,
			       स्थिर अक्षर *pname, व्योम *value, माप_प्रकार valuelen)
अणु
	अक्षर cmd[256], *p;

	अगर (!(OF_WORKAROUNDS & OF_WA_LONGTRAIL))
		वापस call_prom("setprop", 4, 1, node, ADDR(pname),
				 (u32)(अचिन्हित दीर्घ) value, (u32) valuelen);

	/* gah... setprop करोesn't work on दीर्घtrail, have to use पूर्णांकerpret */
	p = cmd;
	add_string(&p, "dev");
	add_string(&p, nodename);
	add_string(&p, tohex((u32)(अचिन्हित दीर्घ) value));
	add_string(&p, tohex(valuelen));
	add_string(&p, tohex(ADDR(pname)));
	add_string(&p, tohex(prom_म_माप(pname)));
	add_string(&p, "property");
	*p = 0;
	वापस call_prom("interpret", 1, 1, (u32)(अचिन्हित दीर्घ) cmd);
पूर्ण

/* We can't use the standard versions because of relocation headaches. */
#घोषणा है_षष्ठादशक(c)	(('0' <= (c) && (c) <= '9') \
			 || ('a' <= (c) && (c) <= 'f') \
			 || ('A' <= (c) && (c) <= 'F'))

#घोषणा है_अंक(c)	('0' <= (c) && (c) <= '9')
#घोषणा है_छोटा(c)	('a' <= (c) && (c) <= 'z')
#घोषणा बड़े(c)	(है_छोटा(c) ? ((c) - 'a' + 'A') : (c))

अटल अचिन्हित दीर्घ prom_म_से_अदीर्घ(स्थिर अक्षर *cp, स्थिर अक्षर **endp)
अणु
	अचिन्हित दीर्घ result = 0, base = 10, value;

	अगर (*cp == '0') अणु
		base = 8;
		cp++;
		अगर (बड़े(*cp) == 'X') अणु
			cp++;
			base = 16;
		पूर्ण
	पूर्ण

	जबतक (है_षष्ठादशक(*cp) &&
	       (value = है_अंक(*cp) ? *cp - '0' : toupper(*cp) - 'A' + 10) < base) अणु
		result = result * base + value;
		cp++;
	पूर्ण

	अगर (endp)
		*endp = cp;

	वापस result;
पूर्ण

अटल अचिन्हित दीर्घ prom_memparse(स्थिर अक्षर *ptr, स्थिर अक्षर **retptr)
अणु
	अचिन्हित दीर्घ ret = prom_म_से_अदीर्घ(ptr, retptr);
	पूर्णांक shअगरt = 0;

	/*
	 * We can't use a चयन here because GCC *may* generate a
	 * jump table which won't work, because we're not running at
	 * the address we're linked at.
	 */
	अगर ('G' == **retptr || 'g' == **retptr)
		shअगरt = 30;

	अगर ('M' == **retptr || 'm' == **retptr)
		shअगरt = 20;

	अगर ('K' == **retptr || 'k' == **retptr)
		shअगरt = 10;

	अगर (shअगरt) अणु
		ret <<= shअगरt;
		(*retptr)++;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Early parsing of the command line passed to the kernel, used क्रम
 * "mem=x" and the options that affect the iommu
 */
अटल व्योम __init early_cmdline_parse(व्योम)
अणु
	स्थिर अक्षर *opt;

	अक्षर *p;
	पूर्णांक l = 0;

	prom_cmd_line[0] = 0;
	p = prom_cmd_line;

	अगर (!IS_ENABLED(CONFIG_CMDLINE_FORCE) && (दीर्घ)prom.chosen > 0)
		l = prom_getprop(prom.chosen, "bootargs", p, COMMAND_LINE_SIZE-1);

	अगर (IS_ENABLED(CONFIG_CMDLINE_EXTEND) || l <= 0 || p[0] == '\0')
		prom_strlcat(prom_cmd_line, " " CONFIG_CMDLINE,
			     माप(prom_cmd_line));

	prom_म_लिखो("command line: %s\n", prom_cmd_line);

#अगर_घोषित CONFIG_PPC64
	opt = prom_म_माला(prom_cmd_line, "iommu=");
	अगर (opt) अणु
		prom_म_लिखो("iommu opt is: %s\n", opt);
		opt += 6;
		जबतक (*opt && *opt == ' ')
			opt++;
		अगर (!prom_म_भेदन(opt, "off", 3))
			prom_iommu_off = 1;
		अन्यथा अगर (!prom_म_भेदन(opt, "force", 5))
			prom_iommu_क्रमce_on = 1;
	पूर्ण
#पूर्ण_अगर
	opt = prom_म_माला(prom_cmd_line, "mem=");
	अगर (opt) अणु
		opt += 4;
		prom_memory_limit = prom_memparse(opt, (स्थिर अक्षर **)&opt);
#अगर_घोषित CONFIG_PPC64
		/* Align to 16 MB == size of ppc64 large page */
		prom_memory_limit = ALIGN(prom_memory_limit, 0x1000000);
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
	prom_radix_disable = !IS_ENABLED(CONFIG_PPC_RADIX_MMU_DEFAULT);
	opt = prom_म_माला(prom_cmd_line, "disable_radix");
	अगर (opt) अणु
		opt += 13;
		अगर (*opt && *opt == '=') अणु
			bool val;

			अगर (prom_strtobool(++opt, &val))
				prom_radix_disable = false;
			अन्यथा
				prom_radix_disable = val;
		पूर्ण अन्यथा
			prom_radix_disable = true;
	पूर्ण
	अगर (prom_radix_disable)
		prom_debug("Radix disabled from cmdline\n");

	opt = prom_म_माला(prom_cmd_line, "radix_hcall_invalidate=on");
	अगर (opt) अणु
		prom_radix_gtse_disable = true;
		prom_debug("Radix GTSE disabled from cmdline\n");
	पूर्ण

	opt = prom_म_माला(prom_cmd_line, "xive=off");
	अगर (opt) अणु
		prom_xive_disable = true;
		prom_debug("XIVE disabled from cmdline\n");
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

#अगर_घोषित CONFIG_PPC_SVM
	opt = prom_म_माला(prom_cmd_line, "svm=");
	अगर (opt) अणु
		bool val;

		opt += माप("svm=") - 1;
		अगर (!prom_strtobool(opt, &val))
			prom_svm_enable = val;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SVM */
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
/*
 * The architecture vector has an array of PVR mask/value pairs,
 * followed by # option vectors - 1, followed by the option vectors.
 *
 * See prom.h क्रम the definition of the bits specअगरied in the
 * architecture vector.
 */

/* Firmware expects the value to be n - 1, where n is the # of vectors */
#घोषणा NUM_VECTORS(n)		((n) - 1)

/*
 * Firmware expects 1 + n - 2, where n is the length of the option vector in
 * bytes. The 1 accounts क्रम the length byte itself, the - 2 .. ?
 */
#घोषणा VECTOR_LENGTH(n)	(1 + (n) - 2)

काष्ठा option_vector1 अणु
	u8 byte1;
	u8 arch_versions;
	u8 arch_versions3;
पूर्ण __packed;

काष्ठा option_vector2 अणु
	u8 byte1;
	__be16 reserved;
	__be32 real_base;
	__be32 real_size;
	__be32 virt_base;
	__be32 virt_size;
	__be32 load_base;
	__be32 min_rma;
	__be32 min_load;
	u8 min_rma_percent;
	u8 max_pft_size;
पूर्ण __packed;

काष्ठा option_vector3 अणु
	u8 byte1;
	u8 byte2;
पूर्ण __packed;

काष्ठा option_vector4 अणु
	u8 byte1;
	u8 min_vp_cap;
पूर्ण __packed;

काष्ठा option_vector5 अणु
	u8 byte1;
	u8 byte2;
	u8 byte3;
	u8 cmo;
	u8 associativity;
	u8 bin_opts;
	u8 micro_checkpoपूर्णांक;
	u8 reserved0;
	__be32 max_cpus;
	__be16 papr_level;
	__be16 reserved1;
	u8 platक्रमm_facilities;
	u8 reserved2;
	__be16 reserved3;
	u8 subprocessors;
	u8 byte22;
	u8 पूर्णांकarch;
	u8 mmu;
	u8 hash_ext;
	u8 radix_ext;
पूर्ण __packed;

काष्ठा option_vector6 अणु
	u8 reserved;
	u8 secondary_pteg;
	u8 os_name;
पूर्ण __packed;

काष्ठा ibm_arch_vec अणु
	काष्ठा अणु u32 mask, val; पूर्ण pvrs[14];

	u8 num_vectors;

	u8 vec1_len;
	काष्ठा option_vector1 vec1;

	u8 vec2_len;
	काष्ठा option_vector2 vec2;

	u8 vec3_len;
	काष्ठा option_vector3 vec3;

	u8 vec4_len;
	काष्ठा option_vector4 vec4;

	u8 vec5_len;
	काष्ठा option_vector5 vec5;

	u8 vec6_len;
	काष्ठा option_vector6 vec6;
पूर्ण __packed;

अटल स्थिर काष्ठा ibm_arch_vec ibm_architecture_vec_ढाँचा __initस्थिर = अणु
	.pvrs = अणु
		अणु
			.mask = cpu_to_be32(0xfffe0000), /* POWER5/POWER5+ */
			.val  = cpu_to_be32(0x003a0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER6 */
			.val  = cpu_to_be32(0x003e0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER7 */
			.val  = cpu_to_be32(0x003f0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER8E */
			.val  = cpu_to_be32(0x004b0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER8NVL */
			.val  = cpu_to_be32(0x004c0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER8 */
			.val  = cpu_to_be32(0x004d0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER9 */
			.val  = cpu_to_be32(0x004e0000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffff0000), /* POWER10 */
			.val  = cpu_to_be32(0x00800000),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffffffff), /* all 3.1-compliant */
			.val  = cpu_to_be32(0x0f000006),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffffffff), /* all 3.00-compliant */
			.val  = cpu_to_be32(0x0f000005),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffffffff), /* all 2.07-compliant */
			.val  = cpu_to_be32(0x0f000004),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffffffff), /* all 2.06-compliant */
			.val  = cpu_to_be32(0x0f000003),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xffffffff), /* all 2.05-compliant */
			.val  = cpu_to_be32(0x0f000002),
		पूर्ण,
		अणु
			.mask = cpu_to_be32(0xfffffffe), /* all 2.04-compliant and earlier */
			.val  = cpu_to_be32(0x0f000001),
		पूर्ण,
	पूर्ण,

	.num_vectors = NUM_VECTORS(6),

	.vec1_len = VECTOR_LENGTH(माप(काष्ठा option_vector1)),
	.vec1 = अणु
		.byte1 = 0,
		.arch_versions = OV1_PPC_2_00 | OV1_PPC_2_01 | OV1_PPC_2_02 | OV1_PPC_2_03 |
				 OV1_PPC_2_04 | OV1_PPC_2_05 | OV1_PPC_2_06 | OV1_PPC_2_07,
		.arch_versions3 = OV1_PPC_3_00 | OV1_PPC_3_1,
	पूर्ण,

	.vec2_len = VECTOR_LENGTH(माप(काष्ठा option_vector2)),
	/* option vector 2: Open Firmware options supported */
	.vec2 = अणु
		.byte1 = OV2_REAL_MODE,
		.reserved = 0,
		.real_base = cpu_to_be32(0xffffffff),
		.real_size = cpu_to_be32(0xffffffff),
		.virt_base = cpu_to_be32(0xffffffff),
		.virt_size = cpu_to_be32(0xffffffff),
		.load_base = cpu_to_be32(0xffffffff),
		.min_rma = cpu_to_be32(512),		/* 512MB min RMA */
		.min_load = cpu_to_be32(0xffffffff),	/* full client load */
		.min_rma_percent = 0,	/* min RMA percentage of total RAM */
		.max_pft_size = 48,	/* max log_2(hash table size) */
	पूर्ण,

	.vec3_len = VECTOR_LENGTH(माप(काष्ठा option_vector3)),
	/* option vector 3: processor options supported */
	.vec3 = अणु
		.byte1 = 0,			/* करोn't ignore, don't halt */
		.byte2 = OV3_FP | OV3_VMX | OV3_DFP,
	पूर्ण,

	.vec4_len = VECTOR_LENGTH(माप(काष्ठा option_vector4)),
	/* option vector 4: IBM PAPR implementation */
	.vec4 = अणु
		.byte1 = 0,			/* करोn't halt */
		.min_vp_cap = OV4_MIN_ENT_CAP,	/* minimum VP entitled capacity */
	पूर्ण,

	.vec5_len = VECTOR_LENGTH(माप(काष्ठा option_vector5)),
	/* option vector 5: PAPR/OF options */
	.vec5 = अणु
		.byte1 = 0,				/* करोn't ignore, don't halt */
		.byte2 = OV5_FEAT(OV5_LPAR) | OV5_FEAT(OV5_SPLPAR) | OV5_FEAT(OV5_LARGE_PAGES) |
		OV5_FEAT(OV5_DRCONF_MEMORY) | OV5_FEAT(OV5_DONATE_DEDICATE_CPU) |
#अगर_घोषित CONFIG_PCI_MSI
		/* PCIe/MSI support.  Without MSI full PCIe is not supported */
		OV5_FEAT(OV5_MSI),
#अन्यथा
		0,
#पूर्ण_अगर
		.byte3 = 0,
		.cmo =
#अगर_घोषित CONFIG_PPC_SMLPAR
		OV5_FEAT(OV5_CMO) | OV5_FEAT(OV5_XCMO),
#अन्यथा
		0,
#पूर्ण_अगर
		.associativity = OV5_FEAT(OV5_TYPE1_AFFINITY) | OV5_FEAT(OV5_PRRN),
		.bin_opts = OV5_FEAT(OV5_RESIZE_HPT) | OV5_FEAT(OV5_HP_EVT),
		.micro_checkpoपूर्णांक = 0,
		.reserved0 = 0,
		.max_cpus = cpu_to_be32(NR_CPUS),	/* number of cores supported */
		.papr_level = 0,
		.reserved1 = 0,
		.platक्रमm_facilities = OV5_FEAT(OV5_PFO_HW_RNG) | OV5_FEAT(OV5_PFO_HW_ENCR) | OV5_FEAT(OV5_PFO_HW_842),
		.reserved2 = 0,
		.reserved3 = 0,
		.subprocessors = 1,
		.byte22 = OV5_FEAT(OV5_DRMEM_V2) | OV5_FEAT(OV5_DRC_INFO),
		.पूर्णांकarch = 0,
		.mmu = 0,
		.hash_ext = 0,
		.radix_ext = 0,
	पूर्ण,

	/* option vector 6: IBM PAPR hपूर्णांकs */
	.vec6_len = VECTOR_LENGTH(माप(काष्ठा option_vector6)),
	.vec6 = अणु
		.reserved = 0,
		.secondary_pteg = 0,
		.os_name = OV6_LINUX,
	पूर्ण,
पूर्ण;

अटल काष्ठा ibm_arch_vec __prombss ibm_architecture_vec  ____cacheline_aligned;

/* Old method - ELF header with PT_NOTE sections only works on BE */
#अगर_घोषित __BIG_ENDIAN__
अटल स्थिर काष्ठा fake_elf अणु
	Elf32_Ehdr	elfhdr;
	Elf32_Phdr	phdr[2];
	काष्ठा chrpnote अणु
		u32	namesz;
		u32	descsz;
		u32	type;
		अक्षर	name[8];	/* "PowerPC" */
		काष्ठा chrpdesc अणु
			u32	real_mode;
			u32	real_base;
			u32	real_size;
			u32	virt_base;
			u32	virt_size;
			u32	load_base;
		पूर्ण chrpdesc;
	पूर्ण chrpnote;
	काष्ठा rpanote अणु
		u32	namesz;
		u32	descsz;
		u32	type;
		अक्षर	name[24];	/* "IBM,RPA-Client-Config" */
		काष्ठा rpadesc अणु
			u32	lpar_affinity;
			u32	min_rmo_size;
			u32	min_rmo_percent;
			u32	max_pft_size;
			u32	splpar;
			u32	min_load;
			u32	new_mem_def;
			u32	ignore_me;
		पूर्ण rpadesc;
	पूर्ण rpanote;
पूर्ण fake_elf __initस्थिर = अणु
	.elfhdr = अणु
		.e_ident = अणु 0x7f, 'E', 'L', 'F',
			     ELFCLASS32, ELFDATA2MSB, EV_CURRENT पूर्ण,
		.e_type = ET_EXEC,	/* yeah right */
		.e_machine = EM_PPC,
		.e_version = EV_CURRENT,
		.e_phoff = दुरत्व(काष्ठा fake_elf, phdr),
		.e_phentsize = माप(Elf32_Phdr),
		.e_phnum = 2
	पूर्ण,
	.phdr = अणु
		[0] = अणु
			.p_type = PT_NOTE,
			.p_offset = दुरत्व(काष्ठा fake_elf, chrpnote),
			.p_filesz = माप(काष्ठा chrpnote)
		पूर्ण, [1] = अणु
			.p_type = PT_NOTE,
			.p_offset = दुरत्व(काष्ठा fake_elf, rpanote),
			.p_filesz = माप(काष्ठा rpanote)
		पूर्ण
	पूर्ण,
	.chrpnote = अणु
		.namesz = माप("PowerPC"),
		.descsz = माप(काष्ठा chrpdesc),
		.type = 0x1275,
		.name = "PowerPC",
		.chrpdesc = अणु
			.real_mode = ~0U,	/* ~0 means "don't care" */
			.real_base = ~0U,
			.real_size = ~0U,
			.virt_base = ~0U,
			.virt_size = ~0U,
			.load_base = ~0U
		पूर्ण,
	पूर्ण,
	.rpanote = अणु
		.namesz = माप("IBM,RPA-Client-Config"),
		.descsz = माप(काष्ठा rpadesc),
		.type = 0x12759999,
		.name = "IBM,RPA-Client-Config",
		.rpadesc = अणु
			.lpar_affinity = 0,
			.min_rmo_size = 64,	/* in megabytes */
			.min_rmo_percent = 0,
			.max_pft_size = 48,	/* 2^48 bytes max PFT size */
			.splpar = 1,
			.min_load = ~0U,
			.new_mem_def = 0
		पूर्ण
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* __BIG_ENDIAN__ */

अटल पूर्णांक __init prom_count_smt_thपढ़ोs(व्योम)
अणु
	phandle node;
	अक्षर type[64];
	अचिन्हित पूर्णांक plen;

	/* Pick up th first CPU node we can find */
	क्रम (node = 0; prom_next_node(&node); ) अणु
		type[0] = 0;
		prom_getprop(node, "device_type", type, माप(type));

		अगर (prom_म_भेद(type, "cpu"))
			जारी;
		/*
		 * There is an entry क्रम each smt thपढ़ो, each entry being
		 * 4 bytes दीर्घ.  All cpus should have the same number of
		 * smt thपढ़ोs, so वापस after finding the first.
		 */
		plen = prom_getproplen(node, "ibm,ppc-interrupt-server#s");
		अगर (plen == PROM_ERROR)
			अवरोध;
		plen >>= 2;
		prom_debug("Found %lu smt threads per core\n", (अचिन्हित दीर्घ)plen);

		/* Sanity check */
		अगर (plen < 1 || plen > 64) अणु
			prom_म_लिखो("Threads per core %lu out of bounds, assuming 1\n",
				    (अचिन्हित दीर्घ)plen);
			वापस 1;
		पूर्ण
		वापस plen;
	पूर्ण
	prom_debug("No threads found, assuming 1 per core\n");

	वापस 1;

पूर्ण

अटल व्योम __init prom_parse_mmu_model(u8 val,
					काष्ठा platक्रमm_support *support)
अणु
	चयन (val) अणु
	हाल OV5_FEAT(OV5_MMU_DYNAMIC):
	हाल OV5_FEAT(OV5_MMU_EITHER): /* Either Available */
		prom_debug("MMU - either supported\n");
		support->radix_mmu = !prom_radix_disable;
		support->hash_mmu = true;
		अवरोध;
	हाल OV5_FEAT(OV5_MMU_RADIX): /* Only Radix */
		prom_debug("MMU - radix only\n");
		अगर (prom_radix_disable) अणु
			/*
			 * If we __have__ to करो radix, we're better off ignoring
			 * the command line rather than not booting.
			 */
			prom_म_लिखो("WARNING: Ignoring cmdline option disable_radix\n");
		पूर्ण
		support->radix_mmu = true;
		अवरोध;
	हाल OV5_FEAT(OV5_MMU_HASH):
		prom_debug("MMU - hash only\n");
		support->hash_mmu = true;
		अवरोध;
	शेष:
		prom_debug("Unknown mmu support option: 0x%x\n", val);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init prom_parse_xive_model(u8 val,
					 काष्ठा platक्रमm_support *support)
अणु
	चयन (val) अणु
	हाल OV5_FEAT(OV5_XIVE_EITHER): /* Either Available */
		prom_debug("XIVE - either mode supported\n");
		support->xive = !prom_xive_disable;
		अवरोध;
	हाल OV5_FEAT(OV5_XIVE_EXPLOIT): /* Only Exploitation mode */
		prom_debug("XIVE - exploitation mode supported\n");
		अगर (prom_xive_disable) अणु
			/*
			 * If we __have__ to करो XIVE, we're better off ignoring
			 * the command line rather than not booting.
			 */
			prom_म_लिखो("WARNING: Ignoring cmdline option xive=off\n");
		पूर्ण
		support->xive = true;
		अवरोध;
	हाल OV5_FEAT(OV5_XIVE_LEGACY): /* Only Legacy mode */
		prom_debug("XIVE - legacy mode supported\n");
		अवरोध;
	शेष:
		prom_debug("Unknown xive support option: 0x%x\n", val);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init prom_parse_platक्रमm_support(u8 index, u8 val,
					       काष्ठा platक्रमm_support *support)
अणु
	चयन (index) अणु
	हाल OV5_INDX(OV5_MMU_SUPPORT): /* MMU Model */
		prom_parse_mmu_model(val & OV5_FEAT(OV5_MMU_SUPPORT), support);
		अवरोध;
	हाल OV5_INDX(OV5_RADIX_GTSE): /* Radix Extensions */
		अगर (val & OV5_FEAT(OV5_RADIX_GTSE))
			support->radix_gtse = !prom_radix_gtse_disable;
		अवरोध;
	हाल OV5_INDX(OV5_XIVE_SUPPORT): /* Interrupt mode */
		prom_parse_xive_model(val & OV5_FEAT(OV5_XIVE_SUPPORT),
				      support);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init prom_check_platक्रमm_support(व्योम)
अणु
	काष्ठा platक्रमm_support supported = अणु
		.hash_mmu = false,
		.radix_mmu = false,
		.radix_gtse = false,
		.xive = false
	पूर्ण;
	पूर्णांक prop_len = prom_getproplen(prom.chosen,
				       "ibm,arch-vec-5-platform-support");

	/*
	 * First copy the architecture vec ढाँचा
	 *
	 * use स_नकल() instead of *vec = *vec_ढाँचा so that GCC replaces it
	 * by __स_नकल() when KASAN is active
	 */
	स_नकल(&ibm_architecture_vec, &ibm_architecture_vec_ढाँचा,
	       माप(ibm_architecture_vec));

	अगर (prop_len > 1) अणु
		पूर्णांक i;
		u8 vec[8];
		prom_debug("Found ibm,arch-vec-5-platform-support, len: %d\n",
			   prop_len);
		अगर (prop_len > माप(vec))
			prom_म_लिखो("WARNING: ibm,arch-vec-5-platform-support longer than expected (len: %d)\n",
				    prop_len);
		prom_getprop(prom.chosen, "ibm,arch-vec-5-platform-support", &vec, माप(vec));
		क्रम (i = 0; i < prop_len; i += 2) अणु
			prom_debug("%d: index = 0x%x val = 0x%x\n", i / 2, vec[i], vec[i + 1]);
			prom_parse_platक्रमm_support(vec[i], vec[i + 1], &supported);
		पूर्ण
	पूर्ण

	अगर (supported.radix_mmu && IS_ENABLED(CONFIG_PPC_RADIX_MMU)) अणु
		/* Radix preferred - Check अगर GTSE is also supported */
		prom_debug("Asking for radix\n");
		ibm_architecture_vec.vec5.mmu = OV5_FEAT(OV5_MMU_RADIX);
		अगर (supported.radix_gtse)
			ibm_architecture_vec.vec5.radix_ext =
					OV5_FEAT(OV5_RADIX_GTSE);
		अन्यथा
			prom_debug("Radix GTSE isn't supported\n");
	पूर्ण अन्यथा अगर (supported.hash_mmu) अणु
		/* Default to hash mmu (अगर we can) */
		prom_debug("Asking for hash\n");
		ibm_architecture_vec.vec5.mmu = OV5_FEAT(OV5_MMU_HASH);
	पूर्ण अन्यथा अणु
		/* We're probably on a legacy hypervisor */
		prom_debug("Assuming legacy hash support\n");
	पूर्ण

	अगर (supported.xive) अणु
		prom_debug("Asking for XIVE\n");
		ibm_architecture_vec.vec5.पूर्णांकarch = OV5_FEAT(OV5_XIVE_EXPLOIT);
	पूर्ण
पूर्ण

अटल व्योम __init prom_send_capabilities(व्योम)
अणु
	ihandle root;
	prom_arg_t ret;
	u32 cores;

	/* Check ibm,arch-vec-5-platक्रमm-support and fixup vec5 अगर required */
	prom_check_platक्रमm_support();

	root = call_prom("open", 1, 1, ADDR("/"));
	अगर (root != 0) अणु
		/* We need to tell the FW about the number of cores we support.
		 *
		 * To करो that, we count the number of thपढ़ोs on the first core
		 * (we assume this is the same क्रम all cores) and use it to
		 * भागide NR_CPUS.
		 */

		cores = DIV_ROUND_UP(NR_CPUS, prom_count_smt_thपढ़ोs());
		prom_म_लिखो("Max number of cores passed to firmware: %u (NR_CPUS = %d)\n",
			    cores, NR_CPUS);

		ibm_architecture_vec.vec5.max_cpus = cpu_to_be32(cores);

		/* try calling the ibm,client-architecture-support method */
		prom_म_लिखो("Calling ibm,client-architecture-support...");
		अगर (call_prom_ret("call-method", 3, 2, &ret,
				  ADDR("ibm,client-architecture-support"),
				  root,
				  ADDR(&ibm_architecture_vec)) == 0) अणु
			/* the call exists... */
			अगर (ret)
				prom_म_लिखो("\nWARNING: ibm,client-architecture"
					    "-support call FAILED!\n");
			call_prom("close", 1, 0, root);
			prom_म_लिखो(" done\n");
			वापस;
		पूर्ण
		call_prom("close", 1, 0, root);
		prom_म_लिखो(" not implemented\n");
	पूर्ण

#अगर_घोषित __BIG_ENDIAN__
	अणु
		ihandle elfloader;

		/* no ibm,client-architecture-support call, try the old way */
		elfloader = call_prom("open", 1, 1,
				      ADDR("/packages/elf-loader"));
		अगर (elfloader == 0) अणु
			prom_म_लिखो("couldn't open /packages/elf-loader\n");
			वापस;
		पूर्ण
		call_prom("call-method", 3, 1, ADDR("process-elf-header"),
			  elfloader, ADDR(&fake_elf));
		call_prom("close", 1, 0, elfloader);
	पूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN__ */
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

/*
 * Memory allocation strategy... our layout is normally:
 *
 *  at 14Mb or more we have vmlinux, then a gap and initrd.  In some
 *  rare हालs, initrd might end up being beक्रमe the kernel though.
 *  We assume this won't override the final kernel at 0, we have no
 *  provision to handle that in this version, but it should hopefully
 *  never happen.
 *
 *  alloc_top is set to the top of RMO, eventually shrink करोwn अगर the
 *  TCEs overlap
 *
 *  alloc_bottom is set to the top of kernel/initrd
 *
 *  from there, allocations are करोne this way : rtas is allocated
 *  topmost, and the device-tree is allocated from the bottom. We try
 *  to grow the device-tree allocation as we progress. If we can't,
 *  then we fail, we करोn't currently have a facility to restart
 *  अन्यथाwhere, but that shouldn't be necessary.
 *
 *  Note that calls to reserve_mem have to be करोne explicitly, memory
 *  allocated with either alloc_up or alloc_करोwn isn't स्वतःmatically
 *  reserved.
 */


/*
 * Allocates memory in the RMO upward from the kernel/initrd
 *
 * When align is 0, this is a special हाल, it means to allocate in place
 * at the current location of alloc_bottom or fail (that is basically
 * extending the previous allocation). Used क्रम the device-tree flattening
 */
अटल अचिन्हित दीर्घ __init alloc_up(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align)
अणु
	अचिन्हित दीर्घ base = alloc_bottom;
	अचिन्हित दीर्घ addr = 0;

	अगर (align)
		base = ALIGN(base, align);
	prom_debug("%s(%lx, %lx)\n", __func__, size, align);
	अगर (ram_top == 0)
		prom_panic("alloc_up() called with mem not initialized\n");

	अगर (align)
		base = ALIGN(alloc_bottom, align);
	अन्यथा
		base = alloc_bottom;

	क्रम(; (base + size) <= alloc_top; 
	    base = ALIGN(base + 0x100000, align)) अणु
		prom_debug("    trying: 0x%lx\n\r", base);
		addr = (अचिन्हित दीर्घ)prom_claim(base, size, 0);
		अगर (addr != PROM_ERROR && addr != 0)
			अवरोध;
		addr = 0;
		अगर (align == 0)
			अवरोध;
	पूर्ण
	अगर (addr == 0)
		वापस 0;
	alloc_bottom = addr + size;

	prom_debug(" -> %lx\n", addr);
	prom_debug("  alloc_bottom : %lx\n", alloc_bottom);
	prom_debug("  alloc_top    : %lx\n", alloc_top);
	prom_debug("  alloc_top_hi : %lx\n", alloc_top_high);
	prom_debug("  rmo_top      : %lx\n", rmo_top);
	prom_debug("  ram_top      : %lx\n", ram_top);

	वापस addr;
पूर्ण

/*
 * Allocates memory करोwnward, either from top of RMO, or अगर highmem
 * is set, from the top of RAM.  Note that this one करोesn't handle
 * failures.  It करोes claim memory अगर highmem is not set.
 */
अटल अचिन्हित दीर्घ __init alloc_करोwn(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
				       पूर्णांक highmem)
अणु
	अचिन्हित दीर्घ base, addr = 0;

	prom_debug("%s(%lx, %lx, %s)\n", __func__, size, align,
		   highmem ? "(high)" : "(low)");
	अगर (ram_top == 0)
		prom_panic("alloc_down() called with mem not initialized\n");

	अगर (highmem) अणु
		/* Carve out storage क्रम the TCE table. */
		addr = ALIGN_DOWN(alloc_top_high - size, align);
		अगर (addr <= alloc_bottom)
			वापस 0;
		/* Will we bump पूर्णांकo the RMO ? If yes, check out that we
		 * didn't overlap existing allocations there, अगर we did,
		 * we are dead, we must be the first in town !
		 */
		अगर (addr < rmo_top) अणु
			/* Good, we are first */
			अगर (alloc_top == rmo_top)
				alloc_top = rmo_top = addr;
			अन्यथा
				वापस 0;
		पूर्ण
		alloc_top_high = addr;
		जाओ bail;
	पूर्ण

	base = ALIGN_DOWN(alloc_top - size, align);
	क्रम (; base > alloc_bottom;
	     base = ALIGN_DOWN(base - 0x100000, align))  अणु
		prom_debug("    trying: 0x%lx\n\r", base);
		addr = (अचिन्हित दीर्घ)prom_claim(base, size, 0);
		अगर (addr != PROM_ERROR && addr != 0)
			अवरोध;
		addr = 0;
	पूर्ण
	अगर (addr == 0)
		वापस 0;
	alloc_top = addr;

 bail:
	prom_debug(" -> %lx\n", addr);
	prom_debug("  alloc_bottom : %lx\n", alloc_bottom);
	prom_debug("  alloc_top    : %lx\n", alloc_top);
	prom_debug("  alloc_top_hi : %lx\n", alloc_top_high);
	prom_debug("  rmo_top      : %lx\n", rmo_top);
	prom_debug("  ram_top      : %lx\n", ram_top);

	वापस addr;
पूर्ण

/*
 * Parse a "reg" cell
 */
अटल अचिन्हित दीर्घ __init prom_next_cell(पूर्णांक s, cell_t **cellp)
अणु
	cell_t *p = *cellp;
	अचिन्हित दीर्घ r = 0;

	/* Ignore more than 2 cells */
	जबतक (s > माप(अचिन्हित दीर्घ) / 4) अणु
		p++;
		s--;
	पूर्ण
	r = be32_to_cpu(*p++);
#अगर_घोषित CONFIG_PPC64
	अगर (s > 1) अणु
		r <<= 32;
		r |= be32_to_cpu(*(p++));
	पूर्ण
#पूर्ण_अगर
	*cellp = p;
	वापस r;
पूर्ण

/*
 * Very dumb function क्रम adding to the memory reserve list, but
 * we करोn't need anything smarter at this poपूर्णांक
 *
 * XXX Eventually check क्रम collisions.  They should NEVER happen.
 * If problems seem to show up, it would be a good start to track
 * them करोwn.
 */
अटल व्योम __init reserve_mem(u64 base, u64 size)
अणु
	u64 top = base + size;
	अचिन्हित दीर्घ cnt = mem_reserve_cnt;

	अगर (size == 0)
		वापस;

	/* We need to always keep one empty entry so that we
	 * have our terminator with "size" set to 0 since we are
	 * dumb and just copy this entire array to the boot params
	 */
	base = ALIGN_DOWN(base, PAGE_SIZE);
	top = ALIGN(top, PAGE_SIZE);
	size = top - base;

	अगर (cnt >= (MEM_RESERVE_MAP_SIZE - 1))
		prom_panic("Memory reserve map exhausted !\n");
	mem_reserve_map[cnt].base = cpu_to_be64(base);
	mem_reserve_map[cnt].size = cpu_to_be64(size);
	mem_reserve_cnt = cnt + 1;
पूर्ण

/*
 * Initialize memory allocation mechanism, parse "memory" nodes and
 * obtain that way the top of memory and RMO to setup out local allocator
 */
अटल व्योम __init prom_init_mem(व्योम)
अणु
	phandle node;
	अक्षर type[64];
	अचिन्हित पूर्णांक plen;
	cell_t *p, *endp;
	__be32 val;
	u32 rac, rsc;

	/*
	 * We iterate the memory nodes to find
	 * 1) top of RMO (first node)
	 * 2) top of memory
	 */
	val = cpu_to_be32(2);
	prom_getprop(prom.root, "#address-cells", &val, माप(val));
	rac = be32_to_cpu(val);
	val = cpu_to_be32(1);
	prom_getprop(prom.root, "#size-cells", &val, माप(rsc));
	rsc = be32_to_cpu(val);
	prom_debug("root_addr_cells: %x\n", rac);
	prom_debug("root_size_cells: %x\n", rsc);

	prom_debug("scanning memory:\n");

	क्रम (node = 0; prom_next_node(&node); ) अणु
		type[0] = 0;
		prom_getprop(node, "device_type", type, माप(type));

		अगर (type[0] == 0) अणु
			/*
			 * CHRP Longtrail machines have no device_type
			 * on the memory node, so check the name instead...
			 */
			prom_getprop(node, "name", type, माप(type));
		पूर्ण
		अगर (prom_म_भेद(type, "memory"))
			जारी;

		plen = prom_getprop(node, "reg", regbuf, माप(regbuf));
		अगर (plen > माप(regbuf)) अणु
			prom_म_लिखो("memory node too large for buffer !\n");
			plen = माप(regbuf);
		पूर्ण
		p = regbuf;
		endp = p + (plen / माप(cell_t));

#अगर_घोषित DEBUG_PROM
		स_रखो(prom_scratch, 0, माप(prom_scratch));
		call_prom("package-to-path", 3, 1, node, prom_scratch,
			  माप(prom_scratch) - 1);
		prom_debug("  node %s :\n", prom_scratch);
#पूर्ण_अगर /* DEBUG_PROM */

		जबतक ((endp - p) >= (rac + rsc)) अणु
			अचिन्हित दीर्घ base, size;

			base = prom_next_cell(rac, &p);
			size = prom_next_cell(rsc, &p);

			अगर (size == 0)
				जारी;
			prom_debug("    %lx %lx\n", base, size);
			अगर (base == 0 && (of_platक्रमm & PLATFORM_LPAR))
				rmo_top = size;
			अगर ((base + size) > ram_top)
				ram_top = base + size;
		पूर्ण
	पूर्ण

	alloc_bottom = PAGE_ALIGN((अचिन्हित दीर्घ)&_end + 0x4000);

	/*
	 * If prom_memory_limit is set we reduce the upper limits *except* क्रम
	 * alloc_top_high. This must be the real top of RAM so we can put
	 * TCE's up there.
	 */

	alloc_top_high = ram_top;

	अगर (prom_memory_limit) अणु
		अगर (prom_memory_limit <= alloc_bottom) अणु
			prom_म_लिखो("Ignoring mem=%lx <= alloc_bottom.\n",
				    prom_memory_limit);
			prom_memory_limit = 0;
		पूर्ण अन्यथा अगर (prom_memory_limit >= ram_top) अणु
			prom_म_लिखो("Ignoring mem=%lx >= ram_top.\n",
				    prom_memory_limit);
			prom_memory_limit = 0;
		पूर्ण अन्यथा अणु
			ram_top = prom_memory_limit;
			rmo_top = min(rmo_top, prom_memory_limit);
		पूर्ण
	पूर्ण

	/*
	 * Setup our top alloc poपूर्णांक, that is top of RMO or top of
	 * segment 0 when running non-LPAR.
	 * Some RS64 machines have buggy firmware where claims up at
	 * 1GB fail.  Cap at 768MB as a workaround.
	 * Since 768MB is plenty of room, and we need to cap to something
	 * reasonable on 32-bit, cap at 768MB on all machines.
	 */
	अगर (!rmo_top)
		rmo_top = ram_top;
	rmo_top = min(0x30000000ul, rmo_top);
	alloc_top = rmo_top;
	alloc_top_high = ram_top;

	/*
	 * Check अगर we have an initrd after the kernel but still inside
	 * the RMO.  If we करो move our bottom poपूर्णांक to after it.
	 */
	अगर (prom_initrd_start &&
	    prom_initrd_start < rmo_top &&
	    prom_initrd_end > alloc_bottom)
		alloc_bottom = PAGE_ALIGN(prom_initrd_end);

	prom_म_लिखो("memory layout at init:\n");
	prom_म_लिखो("  memory_limit : %lx (16 MB aligned)\n",
		    prom_memory_limit);
	prom_म_लिखो("  alloc_bottom : %lx\n", alloc_bottom);
	prom_म_लिखो("  alloc_top    : %lx\n", alloc_top);
	prom_म_लिखो("  alloc_top_hi : %lx\n", alloc_top_high);
	prom_म_लिखो("  rmo_top      : %lx\n", rmo_top);
	prom_म_लिखो("  ram_top      : %lx\n", ram_top);
पूर्ण

अटल व्योम __init prom_बंद_मानक_निवेश(व्योम)
अणु
	__be32 val;
	ihandle मानक_निवेश;

	अगर (prom_getprop(prom.chosen, "stdin", &val, माप(val)) > 0) अणु
		मानक_निवेश = be32_to_cpu(val);
		call_prom("close", 1, 0, मानक_निवेश);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_SVM
अटल पूर्णांक prom_rtas_hcall(uपूर्णांक64_t args)
अणु
	रेजिस्टर uपूर्णांक64_t arg1 यंत्र("r3") = H_RTAS;
	रेजिस्टर uपूर्णांक64_t arg2 यंत्र("r4") = args;

	यंत्र अस्थिर("sc 1\n" : "=r" (arg1) :
			"r" (arg1),
			"r" (arg2) :);
	वापस arg1;
पूर्ण

अटल काष्ठा rtas_args __prombss os_term_args;

अटल व्योम __init prom_rtas_os_term(अक्षर *str)
अणु
	phandle rtas_node;
	__be32 val;
	u32 token;

	prom_debug("%s: start...\n", __func__);
	rtas_node = call_prom("finddevice", 1, 1, ADDR("/rtas"));
	prom_debug("rtas_node: %x\n", rtas_node);
	अगर (!PHANDLE_VALID(rtas_node))
		वापस;

	val = 0;
	prom_getprop(rtas_node, "ibm,os-term", &val, माप(val));
	token = be32_to_cpu(val);
	prom_debug("ibm,os-term: %x\n", token);
	अगर (token == 0)
		prom_panic("Could not get token for ibm,os-term\n");
	os_term_args.token = cpu_to_be32(token);
	os_term_args.nargs = cpu_to_be32(1);
	os_term_args.nret = cpu_to_be32(1);
	os_term_args.args[0] = cpu_to_be32(__pa(str));
	prom_rtas_hcall((uपूर्णांक64_t)&os_term_args);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SVM */

/*
 * Allocate room क्रम and instantiate RTAS
 */
अटल व्योम __init prom_instantiate_rtas(व्योम)
अणु
	phandle rtas_node;
	ihandle rtas_inst;
	u32 base, entry = 0;
	__be32 val;
	u32 size = 0;

	prom_debug("prom_instantiate_rtas: start...\n");

	rtas_node = call_prom("finddevice", 1, 1, ADDR("/rtas"));
	prom_debug("rtas_node: %x\n", rtas_node);
	अगर (!PHANDLE_VALID(rtas_node))
		वापस;

	val = 0;
	prom_getprop(rtas_node, "rtas-size", &val, माप(size));
	size = be32_to_cpu(val);
	अगर (size == 0)
		वापस;

	base = alloc_करोwn(size, PAGE_SIZE, 0);
	अगर (base == 0)
		prom_panic("Could not allocate memory for RTAS\n");

	rtas_inst = call_prom("open", 1, 1, ADDR("/rtas"));
	अगर (!IHANDLE_VALID(rtas_inst)) अणु
		prom_म_लिखो("opening rtas package failed (%x)\n", rtas_inst);
		वापस;
	पूर्ण

	prom_म_लिखो("instantiating rtas at 0x%x...", base);

	अगर (call_prom_ret("call-method", 3, 2, &entry,
			  ADDR("instantiate-rtas"),
			  rtas_inst, base) != 0
	    || entry == 0) अणु
		prom_म_लिखो(" failed\n");
		वापस;
	पूर्ण
	prom_म_लिखो(" done\n");

	reserve_mem(base, size);

	val = cpu_to_be32(base);
	prom_setprop(rtas_node, "/rtas", "linux,rtas-base",
		     &val, माप(val));
	val = cpu_to_be32(entry);
	prom_setprop(rtas_node, "/rtas", "linux,rtas-entry",
		     &val, माप(val));

	/* Check अगर it supports "query-cpu-stopped-state" */
	अगर (prom_getprop(rtas_node, "query-cpu-stopped-state",
			 &val, माप(val)) != PROM_ERROR)
		rtas_has_query_cpu_stopped = true;

	prom_debug("rtas base     = 0x%x\n", base);
	prom_debug("rtas entry    = 0x%x\n", entry);
	prom_debug("rtas size     = 0x%x\n", size);

	prom_debug("prom_instantiate_rtas: end...\n");
पूर्ण

#अगर_घोषित CONFIG_PPC64
/*
 * Allocate room क्रम and instantiate Stored Measurement Log (SML)
 */
अटल व्योम __init prom_instantiate_sml(व्योम)
अणु
	phandle ibmvtpm_node;
	ihandle ibmvtpm_inst;
	u32 entry = 0, size = 0, succ = 0;
	u64 base;
	__be32 val;

	prom_debug("prom_instantiate_sml: start...\n");

	ibmvtpm_node = call_prom("finddevice", 1, 1, ADDR("/vdevice/vtpm"));
	prom_debug("ibmvtpm_node: %x\n", ibmvtpm_node);
	अगर (!PHANDLE_VALID(ibmvtpm_node))
		वापस;

	ibmvtpm_inst = call_prom("open", 1, 1, ADDR("/vdevice/vtpm"));
	अगर (!IHANDLE_VALID(ibmvtpm_inst)) अणु
		prom_म_लिखो("opening vtpm package failed (%x)\n", ibmvtpm_inst);
		वापस;
	पूर्ण

	अगर (prom_getprop(ibmvtpm_node, "ibm,sml-efi-reformat-supported",
			 &val, माप(val)) != PROM_ERROR) अणु
		अगर (call_prom_ret("call-method", 2, 2, &succ,
				  ADDR("reformat-sml-to-efi-alignment"),
				  ibmvtpm_inst) != 0 || succ == 0) अणु
			prom_म_लिखो("Reformat SML to EFI alignment failed\n");
			वापस;
		पूर्ण

		अगर (call_prom_ret("call-method", 2, 2, &size,
				  ADDR("sml-get-allocated-size"),
				  ibmvtpm_inst) != 0 || size == 0) अणु
			prom_म_लिखो("SML get allocated size failed\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (call_prom_ret("call-method", 2, 2, &size,
				  ADDR("sml-get-handover-size"),
				  ibmvtpm_inst) != 0 || size == 0) अणु
			prom_म_लिखो("SML get handover size failed\n");
			वापस;
		पूर्ण
	पूर्ण

	base = alloc_करोwn(size, PAGE_SIZE, 0);
	अगर (base == 0)
		prom_panic("Could not allocate memory for sml\n");

	prom_म_लिखो("instantiating sml at 0x%llx...", base);

	स_रखो((व्योम *)base, 0, size);

	अगर (call_prom_ret("call-method", 4, 2, &entry,
			  ADDR("sml-handover"),
			  ibmvtpm_inst, size, base) != 0 || entry == 0) अणु
		prom_म_लिखो("SML handover failed\n");
		वापस;
	पूर्ण
	prom_म_लिखो(" done\n");

	reserve_mem(base, size);

	prom_setprop(ibmvtpm_node, "/vdevice/vtpm", "linux,sml-base",
		     &base, माप(base));
	prom_setprop(ibmvtpm_node, "/vdevice/vtpm", "linux,sml-size",
		     &size, माप(size));

	prom_debug("sml base     = 0x%llx\n", base);
	prom_debug("sml size     = 0x%x\n", size);

	prom_debug("prom_instantiate_sml: end...\n");
पूर्ण

/*
 * Allocate room क्रम and initialize TCE tables
 */
#अगर_घोषित __BIG_ENDIAN__
अटल व्योम __init prom_initialize_tce_table(व्योम)
अणु
	phandle node;
	ihandle phb_node;
	अक्षर compatible[64], type[64], model[64];
	अक्षर *path = prom_scratch;
	u64 base, align;
	u32 minalign, minsize;
	u64 tce_entry, *tce_entryp;
	u64 local_alloc_top, local_alloc_bottom;
	u64 i;

	अगर (prom_iommu_off)
		वापस;

	prom_debug("starting prom_initialize_tce_table\n");

	/* Cache current top of allocs so we reserve a single block */
	local_alloc_top = alloc_top_high;
	local_alloc_bottom = local_alloc_top;

	/* Search all nodes looking क्रम PHBs. */
	क्रम (node = 0; prom_next_node(&node); ) अणु
		compatible[0] = 0;
		type[0] = 0;
		model[0] = 0;
		prom_getprop(node, "compatible",
			     compatible, माप(compatible));
		prom_getprop(node, "device_type", type, माप(type));
		prom_getprop(node, "model", model, माप(model));

		अगर ((type[0] == 0) || (prom_म_माला(type, "pci") == शून्य))
			जारी;

		/* Keep the old logic पूर्णांकact to aव्योम regression. */
		अगर (compatible[0] != 0) अणु
			अगर ((prom_म_माला(compatible, "python") == शून्य) &&
			    (prom_म_माला(compatible, "Speedwagon") == शून्य) &&
			    (prom_म_माला(compatible, "Winnipeg") == शून्य))
				जारी;
		पूर्ण अन्यथा अगर (model[0] != 0) अणु
			अगर ((prom_म_माला(model, "ython") == शून्य) &&
			    (prom_म_माला(model, "peedwagon") == शून्य) &&
			    (prom_म_माला(model, "innipeg") == शून्य))
				जारी;
		पूर्ण

		अगर (prom_getprop(node, "tce-table-minalign", &minalign,
				 माप(minalign)) == PROM_ERROR)
			minalign = 0;
		अगर (prom_getprop(node, "tce-table-minsize", &minsize,
				 माप(minsize)) == PROM_ERROR)
			minsize = 4UL << 20;

		/*
		 * Even though we पढ़ो what OF wants, we just set the table
		 * size to 4 MB.  This is enough to map 2GB of PCI DMA space.
		 * By करोing this, we aव्योम the pitfalls of trying to DMA to
		 * MMIO space and the DMA alias hole.
		 */
		minsize = 4UL << 20;

		/* Align to the greater of the align or size */
		align = max(minalign, minsize);
		base = alloc_करोwn(minsize, align, 1);
		अगर (base == 0)
			prom_panic("ERROR, cannot find space for TCE table.\n");
		अगर (base < local_alloc_bottom)
			local_alloc_bottom = base;

		/* It seems OF करोesn't null-terminate the path :-( */
		स_रखो(path, 0, माप(prom_scratch));
		/* Call OF to setup the TCE hardware */
		अगर (call_prom("package-to-path", 3, 1, node,
			      path, माप(prom_scratch) - 1) == PROM_ERROR) अणु
			prom_म_लिखो("package-to-path failed\n");
		पूर्ण

		/* Save away the TCE table attributes क्रम later use. */
		prom_setprop(node, path, "linux,tce-base", &base, माप(base));
		prom_setprop(node, path, "linux,tce-size", &minsize, माप(minsize));

		prom_debug("TCE table: %s\n", path);
		prom_debug("\tnode = 0x%x\n", node);
		prom_debug("\tbase = 0x%llx\n", base);
		prom_debug("\tsize = 0x%x\n", minsize);

		/* Initialize the table to have a one-to-one mapping
		 * over the allocated size.
		 */
		tce_entryp = (u64 *)base;
		क्रम (i = 0; i < (minsize >> 3) ;tce_entryp++, i++) अणु
			tce_entry = (i << PAGE_SHIFT);
			tce_entry |= 0x3;
			*tce_entryp = tce_entry;
		पूर्ण

		prom_म_लिखो("opening PHB %s", path);
		phb_node = call_prom("open", 1, 1, path);
		अगर (phb_node == 0)
			prom_म_लिखो("... failed\n");
		अन्यथा
			prom_म_लिखो("... done\n");

		call_prom("call-method", 6, 0, ADDR("set-64-bit-addressing"),
			  phb_node, -1, minsize,
			  (u32) base, (u32) (base >> 32));
		call_prom("close", 1, 0, phb_node);
	पूर्ण

	reserve_mem(local_alloc_bottom, local_alloc_top - local_alloc_bottom);

	/* These are only really needed अगर there is a memory limit in
	 * effect, but we करोn't know so export them always. */
	prom_tce_alloc_start = local_alloc_bottom;
	prom_tce_alloc_end = local_alloc_top;

	/* Flag the first invalid entry */
	prom_debug("ending prom_initialize_tce_table\n");
पूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN__ */
#पूर्ण_अगर /* CONFIG_PPC64 */

/*
 * With CHRP SMP we need to use the OF to start the other processors.
 * We can't रुको until smp_boot_cpus (the OF is trashed by then)
 * so we have to put the processors पूर्णांकo a holding pattern controlled
 * by the kernel (not OF) beक्रमe we destroy the OF.
 *
 * This uses a chunk of low memory, माला_दो some holding pattern
 * code there and sends the other processors off to there until
 * smp_boot_cpus tells them to करो something.  The holding pattern
 * checks that address until its cpu # is there, when it is that
 * cpu jumps to __secondary_start().  smp_boot_cpus() takes care
 * of setting those values.
 *
 * We also use physical address 0x4 here to tell when a cpu
 * is in its holding pattern code.
 *
 * -- Cort
 */
/*
 * We want to reference the copy of __secondary_hold_* in the
 * 0 - 0x100 address range
 */
#घोषणा LOW_ADDR(x)	(((अचिन्हित दीर्घ) &(x)) & 0xff)

अटल व्योम __init prom_hold_cpus(व्योम)
अणु
	अचिन्हित दीर्घ i;
	phandle node;
	अक्षर type[64];
	अचिन्हित दीर्घ *spinloop
		= (व्योम *) LOW_ADDR(__secondary_hold_spinloop);
	अचिन्हित दीर्घ *acknowledge
		= (व्योम *) LOW_ADDR(__secondary_hold_acknowledge);
	अचिन्हित दीर्घ secondary_hold = LOW_ADDR(__secondary_hold);

	/*
	 * On pseries, अगर RTAS supports "query-cpu-stopped-state",
	 * we skip this stage, the CPUs will be started by the
	 * kernel using RTAS.
	 */
	अगर ((of_platक्रमm == PLATFORM_PSERIES ||
	     of_platक्रमm == PLATFORM_PSERIES_LPAR) &&
	    rtas_has_query_cpu_stopped) अणु
		prom_म_लिखो("prom_hold_cpus: skipped\n");
		वापस;
	पूर्ण

	prom_debug("prom_hold_cpus: start...\n");
	prom_debug("    1) spinloop       = 0x%lx\n", (अचिन्हित दीर्घ)spinloop);
	prom_debug("    1) *spinloop      = 0x%lx\n", *spinloop);
	prom_debug("    1) acknowledge    = 0x%lx\n",
		   (अचिन्हित दीर्घ)acknowledge);
	prom_debug("    1) *acknowledge   = 0x%lx\n", *acknowledge);
	prom_debug("    1) secondary_hold = 0x%lx\n", secondary_hold);

	/* Set the common spinloop variable, so all of the secondary cpus
	 * will block when they are awakened from their OF spinloop.
	 * This must occur क्रम both SMP and non SMP kernels, since OF will
	 * be trashed when we move the kernel.
	 */
	*spinloop = 0;

	/* look क्रम cpus */
	क्रम (node = 0; prom_next_node(&node); ) अणु
		अचिन्हित पूर्णांक cpu_no;
		__be32 reg;

		type[0] = 0;
		prom_getprop(node, "device_type", type, माप(type));
		अगर (prom_म_भेद(type, "cpu") != 0)
			जारी;

		/* Skip non-configured cpus. */
		अगर (prom_getprop(node, "status", type, माप(type)) > 0)
			अगर (prom_म_भेद(type, "okay") != 0)
				जारी;

		reg = cpu_to_be32(-1); /* make sparse happy */
		prom_getprop(node, "reg", &reg, माप(reg));
		cpu_no = be32_to_cpu(reg);

		prom_debug("cpu hw idx   = %u\n", cpu_no);

		/* Init the acknowledge var which will be reset by
		 * the secondary cpu when it awakens from its OF
		 * spinloop.
		 */
		*acknowledge = (अचिन्हित दीर्घ)-1;

		अगर (cpu_no != prom.cpu) अणु
			/* Primary Thपढ़ो of non-boot cpu or any thपढ़ो */
			prom_म_लिखो("starting cpu hw idx %u... ", cpu_no);
			call_prom("start-cpu", 3, 0, node,
				  secondary_hold, cpu_no);

			क्रम (i = 0; (i < 100000000) && 
			     (*acknowledge == ((अचिन्हित दीर्घ)-1)); i++ )
				mb();

			अगर (*acknowledge == cpu_no)
				prom_म_लिखो("done\n");
			अन्यथा
				prom_म_लिखो("failed: %lx\n", *acknowledge);
		पूर्ण
#अगर_घोषित CONFIG_SMP
		अन्यथा
			prom_म_लिखो("boot cpu hw idx %u\n", cpu_no);
#पूर्ण_अगर /* CONFIG_SMP */
	पूर्ण

	prom_debug("prom_hold_cpus: end...\n");
पूर्ण


अटल व्योम __init prom_init_client_services(अचिन्हित दीर्घ pp)
अणु
	/* Get a handle to the prom entry poपूर्णांक beक्रमe anything अन्यथा */
	prom_entry = pp;

	/* get a handle क्रम the मानक_निकास device */
	prom.chosen = call_prom("finddevice", 1, 1, ADDR("/chosen"));
	अगर (!PHANDLE_VALID(prom.chosen))
		prom_panic("cannot find chosen"); /* msg won't be prपूर्णांकed :( */

	/* get device tree root */
	prom.root = call_prom("finddevice", 1, 1, ADDR("/"));
	अगर (!PHANDLE_VALID(prom.root))
		prom_panic("cannot find device tree root"); /* msg won't be prपूर्णांकed :( */

	prom.mmumap = 0;
पूर्ण

#अगर_घोषित CONFIG_PPC32
/*
 * For really old घातermacs, we need to map things we claim.
 * For that, we need the ihandle of the mmu.
 * Also, on the दीर्घtrail, we need to work around other bugs.
 */
अटल व्योम __init prom_find_mmu(व्योम)
अणु
	phandle oprom;
	अक्षर version[64];

	oprom = call_prom("finddevice", 1, 1, ADDR("/openprom"));
	अगर (!PHANDLE_VALID(oprom))
		वापस;
	अगर (prom_getprop(oprom, "model", version, माप(version)) <= 0)
		वापस;
	version[माप(version) - 1] = 0;
	/* XXX might need to add other versions here */
	अगर (prom_म_भेद(version, "Open Firmware, 1.0.5") == 0)
		of_workarounds = OF_WA_CLAIM;
	अन्यथा अगर (prom_म_भेदन(version, "FirmWorks,3.", 12) == 0) अणु
		of_workarounds = OF_WA_CLAIM | OF_WA_LONGTRAIL;
		call_prom("interpret", 1, 1, "dev /memory 0 to allow-reclaim");
	पूर्ण अन्यथा
		वापस;
	prom.memory = call_prom("open", 1, 1, ADDR("/memory"));
	prom_getprop(prom.chosen, "mmu", &prom.mmumap,
		     माप(prom.mmumap));
	prom.mmumap = be32_to_cpu(prom.mmumap);
	अगर (!IHANDLE_VALID(prom.memory) || !IHANDLE_VALID(prom.mmumap))
		of_workarounds &= ~OF_WA_CLAIM;		/* hmmm */
पूर्ण
#अन्यथा
#घोषणा prom_find_mmu()
#पूर्ण_अगर

अटल व्योम __init prom_init_मानक_निकास(व्योम)
अणु
	अक्षर *path = of_मानक_निकास_device;
	अक्षर type[16];
	phandle मानक_निकास_node;
	__be32 val;

	अगर (prom_getprop(prom.chosen, "stdout", &val, माप(val)) <= 0)
		prom_panic("cannot find stdout");

	prom.मानक_निकास = be32_to_cpu(val);

	/* Get the full OF pathname of the मानक_निकास device */
	स_रखो(path, 0, 256);
	call_prom("instance-to-path", 3, 1, prom.मानक_निकास, path, 255);
	prom_म_लिखो("OF stdout device is: %s\n", of_मानक_निकास_device);
	prom_setprop(prom.chosen, "/chosen", "linux,stdout-path",
		     path, prom_म_माप(path) + 1);

	/* instance-to-package fails on PA-Semi */
	मानक_निकास_node = call_prom("instance-to-package", 1, 1, prom.मानक_निकास);
	अगर (मानक_निकास_node != PROM_ERROR) अणु
		val = cpu_to_be32(मानक_निकास_node);

		/* If it's a display, note it */
		स_रखो(type, 0, माप(type));
		prom_getprop(मानक_निकास_node, "device_type", type, माप(type));
		अगर (prom_म_भेद(type, "display") == 0)
			prom_setprop(मानक_निकास_node, path, "linux,boot-display", शून्य, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक __init prom_find_machine_type(व्योम)
अणु
	अक्षर compat[256];
	पूर्णांक len, i = 0;
#अगर_घोषित CONFIG_PPC64
	phandle rtas;
	पूर्णांक x;
#पूर्ण_अगर

	/* Look क्रम a PowerMac or a Cell */
	len = prom_getprop(prom.root, "compatible",
			   compat, माप(compat)-1);
	अगर (len > 0) अणु
		compat[len] = 0;
		जबतक (i < len) अणु
			अक्षर *p = &compat[i];
			पूर्णांक sl = prom_म_माप(p);
			अगर (sl == 0)
				अवरोध;
			अगर (prom_म_माला(p, "Power Macintosh") ||
			    prom_म_माला(p, "MacRISC"))
				वापस PLATFORM_POWERMAC;
#अगर_घोषित CONFIG_PPC64
			/* We must make sure we करोn't detect the IBM Cell
			 * blades as pSeries due to some firmware issues,
			 * so we करो it here.
			 */
			अगर (prom_म_माला(p, "IBM,CBEA") ||
			    prom_म_माला(p, "IBM,CPBW-1.0"))
				वापस PLATFORM_GENERIC;
#पूर्ण_अगर /* CONFIG_PPC64 */
			i += sl + 1;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_PPC64
	/* Try to figure out अगर it's an IBM pSeries or any other
	 * PAPR compliant platक्रमm. We assume it is अगर :
	 *  - /device_type is "chrp" (please, करो NOT use that क्रम future
	 *    non-IBM designs !
	 *  - it has /rtas
	 */
	len = prom_getprop(prom.root, "device_type",
			   compat, माप(compat)-1);
	अगर (len <= 0)
		वापस PLATFORM_GENERIC;
	अगर (prom_म_भेद(compat, "chrp"))
		वापस PLATFORM_GENERIC;

	/* Default to pSeries. We need to know अगर we are running LPAR */
	rtas = call_prom("finddevice", 1, 1, ADDR("/rtas"));
	अगर (!PHANDLE_VALID(rtas))
		वापस PLATFORM_GENERIC;
	x = prom_getproplen(rtas, "ibm,hypertas-functions");
	अगर (x != PROM_ERROR) अणु
		prom_debug("Hypertas detected, assuming LPAR !\n");
		वापस PLATFORM_PSERIES_LPAR;
	पूर्ण
	वापस PLATFORM_PSERIES;
#अन्यथा
	वापस PLATFORM_GENERIC;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init prom_set_color(ihandle ih, पूर्णांक i, पूर्णांक r, पूर्णांक g, पूर्णांक b)
अणु
	वापस call_prom("call-method", 6, 1, ADDR("color!"), ih, i, b, g, r);
पूर्ण

/*
 * If we have a display that we करोn't know how to drive,
 * we will want to try to execute OF's खोलो method क्रम it
 * later.  However, OF will probably fall over अगर we करो that
 * we've taken over the MMU.
 * So we check whether we will need to खोलो the display,
 * and अगर so, खोलो it now.
 */
अटल व्योम __init prom_check_displays(व्योम)
अणु
	अक्षर type[16], *path;
	phandle node;
	ihandle ih;
	पूर्णांक i;

	अटल स्थिर अचिन्हित अक्षर शेष_colors[] __initस्थिर = अणु
		0x00, 0x00, 0x00,
		0x00, 0x00, 0xaa,
		0x00, 0xaa, 0x00,
		0x00, 0xaa, 0xaa,
		0xaa, 0x00, 0x00,
		0xaa, 0x00, 0xaa,
		0xaa, 0xaa, 0x00,
		0xaa, 0xaa, 0xaa,
		0x55, 0x55, 0x55,
		0x55, 0x55, 0xff,
		0x55, 0xff, 0x55,
		0x55, 0xff, 0xff,
		0xff, 0x55, 0x55,
		0xff, 0x55, 0xff,
		0xff, 0xff, 0x55,
		0xff, 0xff, 0xff
	पूर्ण;
	स्थिर अचिन्हित अक्षर *clut;

	prom_debug("Looking for displays\n");
	क्रम (node = 0; prom_next_node(&node); ) अणु
		स_रखो(type, 0, माप(type));
		prom_getprop(node, "device_type", type, माप(type));
		अगर (prom_म_भेद(type, "display") != 0)
			जारी;

		/* It seems OF करोesn't null-terminate the path :-( */
		path = prom_scratch;
		स_रखो(path, 0, माप(prom_scratch));

		/*
		 * leave some room at the end of the path क्रम appending extra
		 * arguments
		 */
		अगर (call_prom("package-to-path", 3, 1, node, path,
			      माप(prom_scratch) - 10) == PROM_ERROR)
			जारी;
		prom_म_लिखो("found display   : %s, opening... ", path);
		
		ih = call_prom("open", 1, 1, path);
		अगर (ih == 0) अणु
			prom_म_लिखो("failed\n");
			जारी;
		पूर्ण

		/* Success */
		prom_म_लिखो("done\n");
		prom_setprop(node, path, "linux,opened", शून्य, 0);

		/* Setup a usable color table when the appropriate
		 * method is available. Should update this to set-colors */
		clut = शेष_colors;
		क्रम (i = 0; i < 16; i++, clut += 3)
			अगर (prom_set_color(ih, i, clut[0], clut[1],
					   clut[2]) != 0)
				अवरोध;

#अगर_घोषित CONFIG_LOGO_LINUX_CLUT224
		clut = PTRRELOC(logo_linux_clut224.clut);
		क्रम (i = 0; i < logo_linux_clut224.clutsize; i++, clut += 3)
			अगर (prom_set_color(ih, i + 32, clut[0], clut[1],
					   clut[2]) != 0)
				अवरोध;
#पूर्ण_अगर /* CONFIG_LOGO_LINUX_CLUT224 */

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_BOOTX
		अगर (prom_getprop(node, "linux,boot-display", शून्य, 0) !=
		    PROM_ERROR) अणु
			u32 width, height, pitch, addr;

			prom_म_लिखो("Setting btext !\n");

			अगर (prom_getprop(node, "width", &width, 4) == PROM_ERROR)
				वापस;

			अगर (prom_getprop(node, "height", &height, 4) == PROM_ERROR)
				वापस;

			अगर (prom_getprop(node, "linebytes", &pitch, 4) == PROM_ERROR)
				वापस;

			अगर (prom_getprop(node, "address", &addr, 4) == PROM_ERROR)
				वापस;

			prom_म_लिखो("W=%d H=%d LB=%d addr=0x%x\n",
				    width, height, pitch, addr);
			btext_setup_display(width, height, 8, pitch, addr);
			btext_prepare_BAT();
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_BOOTX */
	पूर्ण
पूर्ण


/* Return (relocated) poपूर्णांकer to this much memory: moves initrd अगर reqd. */
अटल व्योम __init *make_room(अचिन्हित दीर्घ *mem_start, अचिन्हित दीर्घ *mem_end,
			      अचिन्हित दीर्घ needed, अचिन्हित दीर्घ align)
अणु
	व्योम *ret;

	*mem_start = ALIGN(*mem_start, align);
	जबतक ((*mem_start + needed) > *mem_end) अणु
		अचिन्हित दीर्घ room, chunk;

		prom_debug("Chunk exhausted, claiming more at %lx...\n",
			   alloc_bottom);
		room = alloc_top - alloc_bottom;
		अगर (room > DEVTREE_CHUNK_SIZE)
			room = DEVTREE_CHUNK_SIZE;
		अगर (room < PAGE_SIZE)
			prom_panic("No memory for flatten_device_tree "
				   "(no room)\n");
		chunk = alloc_up(room, 0);
		अगर (chunk == 0)
			prom_panic("No memory for flatten_device_tree "
				   "(claim failed)\n");
		*mem_end = chunk + room;
	पूर्ण

	ret = (व्योम *)*mem_start;
	*mem_start += needed;

	वापस ret;
पूर्ण

#घोषणा dt_push_token(token, mem_start, mem_end) करो अणु 			\
		व्योम *room = make_room(mem_start, mem_end, 4, 4);	\
		*(__be32 *)room = cpu_to_be32(token);			\
	पूर्ण जबतक(0)

अटल अचिन्हित दीर्घ __init dt_find_string(अक्षर *str)
अणु
	अक्षर *s, *os;

	s = os = (अक्षर *)dt_string_start;
	s += 4;
	जबतक (s <  (अक्षर *)dt_string_end) अणु
		अगर (prom_म_भेद(s, str) == 0)
			वापस s - os;
		s += prom_म_माप(s) + 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The Open Firmware 1275 specअगरication states properties must be 31 bytes or
 * less, however not all firmwares obey this. Make it 64 bytes to be safe.
 */
#घोषणा MAX_PROPERTY_NAME 64

अटल व्योम __init scan_dt_build_strings(phandle node,
					 अचिन्हित दीर्घ *mem_start,
					 अचिन्हित दीर्घ *mem_end)
अणु
	अक्षर *prev_name, *namep, *sstart;
	अचिन्हित दीर्घ soff;
	phandle child;

	sstart =  (अक्षर *)dt_string_start;

	/* get and store all property names */
	prev_name = "";
	क्रम (;;) अणु
		/* 64 is max len of name including nul. */
		namep = make_room(mem_start, mem_end, MAX_PROPERTY_NAME, 1);
		अगर (call_prom("nextprop", 3, 1, node, prev_name, namep) != 1) अणु
			/* No more nodes: unwind alloc */
			*mem_start = (अचिन्हित दीर्घ)namep;
			अवरोध;
		पूर्ण

 		/* skip "name" */
		अगर (prom_म_भेद(namep, "name") == 0) अणु
 			*mem_start = (अचिन्हित दीर्घ)namep;
 			prev_name = "name";
 			जारी;
 		पूर्ण
		/* get/create string entry */
		soff = dt_find_string(namep);
		अगर (soff != 0) अणु
			*mem_start = (अचिन्हित दीर्घ)namep;
			namep = sstart + soff;
		पूर्ण अन्यथा अणु
			/* Trim off some अगर we can */
			*mem_start = (अचिन्हित दीर्घ)namep + prom_म_माप(namep) + 1;
			dt_string_end = *mem_start;
		पूर्ण
		prev_name = namep;
	पूर्ण

	/* करो all our children */
	child = call_prom("child", 1, 1, node);
	जबतक (child != 0) अणु
		scan_dt_build_strings(child, mem_start, mem_end);
		child = call_prom("peer", 1, 1, child);
	पूर्ण
पूर्ण

अटल व्योम __init scan_dt_build_काष्ठा(phandle node, अचिन्हित दीर्घ *mem_start,
					अचिन्हित दीर्घ *mem_end)
अणु
	phandle child;
	अक्षर *namep, *prev_name, *sstart, *p, *ep, *lp, *path;
	अचिन्हित दीर्घ soff;
	अचिन्हित अक्षर *valp;
	अटल अक्षर pname[MAX_PROPERTY_NAME] __prombss;
	पूर्णांक l, room, has_phandle = 0;

	dt_push_token(OF_DT_BEGIN_NODE, mem_start, mem_end);

	/* get the node's full name */
	namep = (अक्षर *)*mem_start;
	room = *mem_end - *mem_start;
	अगर (room > 255)
		room = 255;
	l = call_prom("package-to-path", 3, 1, node, namep, room);
	अगर (l >= 0) अणु
		/* Didn't fit?  Get more room. */
		अगर (l >= room) अणु
			अगर (l >= *mem_end - *mem_start)
				namep = make_room(mem_start, mem_end, l+1, 1);
			call_prom("package-to-path", 3, 1, node, namep, l);
		पूर्ण
		namep[l] = '\0';

		/* Fixup an Apple bug where they have bogus \0 अक्षरs in the
		 * middle of the path in some properties, and extract
		 * the unit name (everything after the last '/').
		 */
		क्रम (lp = p = namep, ep = namep + l; p < ep; p++) अणु
			अगर (*p == '/')
				lp = namep;
			अन्यथा अगर (*p != 0)
				*lp++ = *p;
		पूर्ण
		*lp = 0;
		*mem_start = ALIGN((अचिन्हित दीर्घ)lp + 1, 4);
	पूर्ण

	/* get it again क्रम debugging */
	path = prom_scratch;
	स_रखो(path, 0, माप(prom_scratch));
	call_prom("package-to-path", 3, 1, node, path, माप(prom_scratch) - 1);

	/* get and store all properties */
	prev_name = "";
	sstart = (अक्षर *)dt_string_start;
	क्रम (;;) अणु
		अगर (call_prom("nextprop", 3, 1, node, prev_name,
			      pname) != 1)
			अवरोध;

 		/* skip "name" */
		अगर (prom_म_भेद(pname, "name") == 0) अणु
 			prev_name = "name";
 			जारी;
 		पूर्ण

		/* find string offset */
		soff = dt_find_string(pname);
		अगर (soff == 0) अणु
			prom_म_लिखो("WARNING: Can't find string index for"
				    " <%s>, node %s\n", pname, path);
			अवरोध;
		पूर्ण
		prev_name = sstart + soff;

		/* get length */
		l = call_prom("getproplen", 2, 1, node, pname);

		/* sanity checks */
		अगर (l == PROM_ERROR)
			जारी;

		/* push property head */
		dt_push_token(OF_DT_PROP, mem_start, mem_end);
		dt_push_token(l, mem_start, mem_end);
		dt_push_token(soff, mem_start, mem_end);

		/* push property content */
		valp = make_room(mem_start, mem_end, l, 4);
		call_prom("getprop", 4, 1, node, pname, valp, l);
		*mem_start = ALIGN(*mem_start, 4);

		अगर (!prom_म_भेद(pname, "phandle"))
			has_phandle = 1;
	पूर्ण

	/* Add a "phandle" property अगर none alपढ़ोy exist */
	अगर (!has_phandle) अणु
		soff = dt_find_string("phandle");
		अगर (soff == 0)
			prom_म_लिखो("WARNING: Can't find string index for <phandle> node %s\n", path);
		अन्यथा अणु
			dt_push_token(OF_DT_PROP, mem_start, mem_end);
			dt_push_token(4, mem_start, mem_end);
			dt_push_token(soff, mem_start, mem_end);
			valp = make_room(mem_start, mem_end, 4, 4);
			*(__be32 *)valp = cpu_to_be32(node);
		पूर्ण
	पूर्ण

	/* करो all our children */
	child = call_prom("child", 1, 1, node);
	जबतक (child != 0) अणु
		scan_dt_build_काष्ठा(child, mem_start, mem_end);
		child = call_prom("peer", 1, 1, child);
	पूर्ण

	dt_push_token(OF_DT_END_NODE, mem_start, mem_end);
पूर्ण

अटल व्योम __init flatten_device_tree(व्योम)
अणु
	phandle root;
	अचिन्हित दीर्घ mem_start, mem_end, room;
	काष्ठा boot_param_header *hdr;
	अक्षर *namep;
	u64 *rsvmap;

	/*
	 * Check how much room we have between alloc top & bottom (+/- a
	 * few pages), crop to 1MB, as this is our "chunk" size
	 */
	room = alloc_top - alloc_bottom - 0x4000;
	अगर (room > DEVTREE_CHUNK_SIZE)
		room = DEVTREE_CHUNK_SIZE;
	prom_debug("starting device tree allocs at %lx\n", alloc_bottom);

	/* Now try to claim that */
	mem_start = (अचिन्हित दीर्घ)alloc_up(room, PAGE_SIZE);
	अगर (mem_start == 0)
		prom_panic("Can't allocate initial device-tree chunk\n");
	mem_end = mem_start + room;

	/* Get root of tree */
	root = call_prom("peer", 1, 1, (phandle)0);
	अगर (root == (phandle)0)
		prom_panic ("couldn't get device tree root\n");

	/* Build header and make room क्रम mem rsv map */ 
	mem_start = ALIGN(mem_start, 4);
	hdr = make_room(&mem_start, &mem_end,
			माप(काष्ठा boot_param_header), 4);
	dt_header_start = (अचिन्हित दीर्घ)hdr;
	rsvmap = make_room(&mem_start, &mem_end, माप(mem_reserve_map), 8);

	/* Start of strings */
	mem_start = PAGE_ALIGN(mem_start);
	dt_string_start = mem_start;
	mem_start += 4; /* hole */

	/* Add "phandle" in there, we'll need it */
	namep = make_room(&mem_start, &mem_end, 16, 1);
	prom_म_नकल(namep, "phandle");
	mem_start = (अचिन्हित दीर्घ)namep + prom_म_माप(namep) + 1;

	/* Build string array */
	prom_म_लिखो("Building dt strings...\n"); 
	scan_dt_build_strings(root, &mem_start, &mem_end);
	dt_string_end = mem_start;

	/* Build काष्ठाure */
	mem_start = PAGE_ALIGN(mem_start);
	dt_काष्ठा_start = mem_start;
	prom_म_लिखो("Building dt structure...\n"); 
	scan_dt_build_काष्ठा(root, &mem_start, &mem_end);
	dt_push_token(OF_DT_END, &mem_start, &mem_end);
	dt_काष्ठा_end = PAGE_ALIGN(mem_start);

	/* Finish header */
	hdr->boot_cpuid_phys = cpu_to_be32(prom.cpu);
	hdr->magic = cpu_to_be32(OF_DT_HEADER);
	hdr->totalsize = cpu_to_be32(dt_काष्ठा_end - dt_header_start);
	hdr->off_dt_काष्ठा = cpu_to_be32(dt_काष्ठा_start - dt_header_start);
	hdr->off_dt_strings = cpu_to_be32(dt_string_start - dt_header_start);
	hdr->dt_strings_size = cpu_to_be32(dt_string_end - dt_string_start);
	hdr->off_mem_rsvmap = cpu_to_be32(((अचिन्हित दीर्घ)rsvmap) - dt_header_start);
	hdr->version = cpu_to_be32(OF_DT_VERSION);
	/* Version 16 is not backward compatible */
	hdr->last_comp_version = cpu_to_be32(0x10);

	/* Copy the reserve map in */
	स_नकल(rsvmap, mem_reserve_map, माप(mem_reserve_map));

#अगर_घोषित DEBUG_PROM
	अणु
		पूर्णांक i;
		prom_म_लिखो("reserved memory map:\n");
		क्रम (i = 0; i < mem_reserve_cnt; i++)
			prom_म_लिखो("  %llx - %llx\n",
				    be64_to_cpu(mem_reserve_map[i].base),
				    be64_to_cpu(mem_reserve_map[i].size));
	पूर्ण
#पूर्ण_अगर
	/* Bump mem_reserve_cnt to cause further reservations to fail
	 * since it's too late.
	 */
	mem_reserve_cnt = MEM_RESERVE_MAP_SIZE;

	prom_म_लिखो("Device tree strings 0x%lx -> 0x%lx\n",
		    dt_string_start, dt_string_end);
	prom_म_लिखो("Device tree struct  0x%lx -> 0x%lx\n",
		    dt_काष्ठा_start, dt_काष्ठा_end);
पूर्ण

#अगर_घोषित CONFIG_PPC_MAPLE
/* PIBS Version 1.05.0000 04/26/2005 has an incorrect /ht/isa/ranges property.
 * The values are bad, and it करोesn't even have the right number of cells. */
अटल व्योम __init fixup_device_tree_maple(व्योम)
अणु
	phandle isa;
	u32 rloc = 0x01002000; /* IO space; PCI device = 4 */
	u32 isa_ranges[6];
	अक्षर *name;

	name = "/ht@0/isa@4";
	isa = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (!PHANDLE_VALID(isa)) अणु
		name = "/ht@0/isa@6";
		isa = call_prom("finddevice", 1, 1, ADDR(name));
		rloc = 0x01003000; /* IO space; PCI device = 6 */
	पूर्ण
	अगर (!PHANDLE_VALID(isa))
		वापस;

	अगर (prom_getproplen(isa, "ranges") != 12)
		वापस;
	अगर (prom_getprop(isa, "ranges", isa_ranges, माप(isa_ranges))
		== PROM_ERROR)
		वापस;

	अगर (isa_ranges[0] != 0x1 ||
		isa_ranges[1] != 0xf4000000 ||
		isa_ranges[2] != 0x00010000)
		वापस;

	prom_म_लिखो("Fixing up bogus ISA range on Maple/Apache...\n");

	isa_ranges[0] = 0x1;
	isa_ranges[1] = 0x0;
	isa_ranges[2] = rloc;
	isa_ranges[3] = 0x0;
	isa_ranges[4] = 0x0;
	isa_ranges[5] = 0x00010000;
	prom_setprop(isa, name, "ranges",
			isa_ranges, माप(isa_ranges));
पूर्ण

#घोषणा CPC925_MC_START		0xf8000000
#घोषणा CPC925_MC_LENGTH	0x1000000
/* The values क्रम memory-controller करोn't have right number of cells */
अटल व्योम __init fixup_device_tree_maple_memory_controller(व्योम)
अणु
	phandle mc;
	u32 mc_reg[4];
	अक्षर *name = "/hostbridge@f8000000";
	u32 ac, sc;

	mc = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (!PHANDLE_VALID(mc))
		वापस;

	अगर (prom_getproplen(mc, "reg") != 8)
		वापस;

	prom_getprop(prom.root, "#address-cells", &ac, माप(ac));
	prom_getprop(prom.root, "#size-cells", &sc, माप(sc));
	अगर ((ac != 2) || (sc != 2))
		वापस;

	अगर (prom_getprop(mc, "reg", mc_reg, माप(mc_reg)) == PROM_ERROR)
		वापस;

	अगर (mc_reg[0] != CPC925_MC_START || mc_reg[1] != CPC925_MC_LENGTH)
		वापस;

	prom_म_लिखो("Fixing up bogus hostbridge on Maple...\n");

	mc_reg[0] = 0x0;
	mc_reg[1] = CPC925_MC_START;
	mc_reg[2] = 0x0;
	mc_reg[3] = CPC925_MC_LENGTH;
	prom_setprop(mc, name, "reg", mc_reg, माप(mc_reg));
पूर्ण
#अन्यथा
#घोषणा fixup_device_tree_maple()
#घोषणा fixup_device_tree_maple_memory_controller()
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_CHRP
/*
 * Pegasos and BriQ lacks the "ranges" property in the isa node
 * Pegasos needs decimal IRQ 14/15, not hexadecimal
 * Pegasos has the IDE configured in legacy mode, but advertised as native
 */
अटल व्योम __init fixup_device_tree_chrp(व्योम)
अणु
	phandle ph;
	u32 prop[6];
	u32 rloc = 0x01006000; /* IO space; PCI device = 12 */
	अक्षर *name;
	पूर्णांक rc;

	name = "/pci@80000000/isa@c";
	ph = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (!PHANDLE_VALID(ph)) अणु
		name = "/pci@ff500000/isa@6";
		ph = call_prom("finddevice", 1, 1, ADDR(name));
		rloc = 0x01003000; /* IO space; PCI device = 6 */
	पूर्ण
	अगर (PHANDLE_VALID(ph)) अणु
		rc = prom_getproplen(ph, "ranges");
		अगर (rc == 0 || rc == PROM_ERROR) अणु
			prom_म_लिखो("Fixing up missing ISA range on Pegasos...\n");

			prop[0] = 0x1;
			prop[1] = 0x0;
			prop[2] = rloc;
			prop[3] = 0x0;
			prop[4] = 0x0;
			prop[5] = 0x00010000;
			prom_setprop(ph, name, "ranges", prop, माप(prop));
		पूर्ण
	पूर्ण

	name = "/pci@80000000/ide@C,1";
	ph = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (PHANDLE_VALID(ph)) अणु
		prom_म_लिखो("Fixing up IDE interrupt on Pegasos...\n");
		prop[0] = 14;
		prop[1] = 0x0;
		prom_setprop(ph, name, "interrupts", prop, 2*माप(u32));
		prom_म_लिखो("Fixing up IDE class-code on Pegasos...\n");
		rc = prom_getprop(ph, "class-code", prop, माप(u32));
		अगर (rc == माप(u32)) अणु
			prop[0] &= ~0x5;
			prom_setprop(ph, name, "class-code", prop, माप(u32));
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा fixup_device_tree_chrp()
#पूर्ण_अगर

#अगर defined(CONFIG_PPC64) && defined(CONFIG_PPC_PMAC)
अटल व्योम __init fixup_device_tree_pmac(व्योम)
अणु
	phandle u3, i2c, mpic;
	u32 u3_rev;
	u32 पूर्णांकerrupts[2];
	u32 parent;

	/* Some G5s have a missing पूर्णांकerrupt definition, fix it up here */
	u3 = call_prom("finddevice", 1, 1, ADDR("/u3@0,f8000000"));
	अगर (!PHANDLE_VALID(u3))
		वापस;
	i2c = call_prom("finddevice", 1, 1, ADDR("/u3@0,f8000000/i2c@f8001000"));
	अगर (!PHANDLE_VALID(i2c))
		वापस;
	mpic = call_prom("finddevice", 1, 1, ADDR("/u3@0,f8000000/mpic@f8040000"));
	अगर (!PHANDLE_VALID(mpic))
		वापस;

	/* check अगर proper rev of u3 */
	अगर (prom_getprop(u3, "device-rev", &u3_rev, माप(u3_rev))
	    == PROM_ERROR)
		वापस;
	अगर (u3_rev < 0x35 || u3_rev > 0x39)
		वापस;
	/* करोes it need fixup ? */
	अगर (prom_getproplen(i2c, "interrupts") > 0)
		वापस;

	prom_म_लिखो("fixing up bogus interrupts for u3 i2c...\n");

	/* पूर्णांकerrupt on this revision of u3 is number 0 and level */
	पूर्णांकerrupts[0] = 0;
	पूर्णांकerrupts[1] = 1;
	prom_setprop(i2c, "/u3@0,f8000000/i2c@f8001000", "interrupts",
		     &पूर्णांकerrupts, माप(पूर्णांकerrupts));
	parent = (u32)mpic;
	prom_setprop(i2c, "/u3@0,f8000000/i2c@f8001000", "interrupt-parent",
		     &parent, माप(parent));
पूर्ण
#अन्यथा
#घोषणा fixup_device_tree_pmac()
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_EFIKA
/*
 * The MPC5200 FEC driver requires an phy-handle property to tell it how
 * to talk to the phy.  If the phy-handle property is missing, then this
 * function is called to add the appropriate nodes and link it to the
 * ethernet node.
 */
अटल व्योम __init fixup_device_tree_efika_add_phy(व्योम)
अणु
	u32 node;
	अक्षर prop[64];
	पूर्णांक rv;

	/* Check अगर /builtin/ethernet exists - bail अगर it करोesn't */
	node = call_prom("finddevice", 1, 1, ADDR("/builtin/ethernet"));
	अगर (!PHANDLE_VALID(node))
		वापस;

	/* Check अगर the phy-handle property exists - bail अगर it करोes */
	rv = prom_getprop(node, "phy-handle", prop, माप(prop));
	अगर (!rv)
		वापस;

	/*
	 * At this poपूर्णांक the ethernet device करोesn't have a phy described.
	 * Now we need to add the missing phy node and linkage
	 */

	/* Check क्रम an MDIO bus node - अगर missing then create one */
	node = call_prom("finddevice", 1, 1, ADDR("/builtin/mdio"));
	अगर (!PHANDLE_VALID(node)) अणु
		prom_म_लिखो("Adding Ethernet MDIO node\n");
		call_prom("interpret", 1, 1,
			" s\" /builtin\" find-device"
			" new-device"
				" 1 encode-int s\" #address-cells\" property"
				" 0 encode-int s\" #size-cells\" property"
				" s\" mdio\" device-name"
				" s\" fsl,mpc5200b-mdio\" encode-string"
				" s\" compatible\" property"
				" 0xf0003000 0x400 reg"
				" 0x2 encode-int"
				" 0x5 encode-int encode+"
				" 0x3 encode-int encode+"
				" s\" interrupts\" property"
			" finish-device");
	पूर्ण

	/* Check क्रम a PHY device node - अगर missing then create one and
	 * give it's phandle to the ethernet node */
	node = call_prom("finddevice", 1, 1,
			 ADDR("/builtin/mdio/ethernet-phy"));
	अगर (!PHANDLE_VALID(node)) अणु
		prom_म_लिखो("Adding Ethernet PHY node\n");
		call_prom("interpret", 1, 1,
			" s\" /builtin/mdio\" find-device"
			" new-device"
				" s\" ethernet-phy\" device-name"
				" 0x10 encode-int s\" reg\" property"
				" my-self"
				" ihandle>phandle"
			" finish-device"
			" s\" /builtin/ethernet\" find-device"
				" encode-int"
				" s\" phy-handle\" property"
			" device-end");
	पूर्ण
पूर्ण

अटल व्योम __init fixup_device_tree_efika(व्योम)
अणु
	पूर्णांक sound_irq[3] = अणु 2, 2, 0 पूर्ण;
	पूर्णांक bcomm_irq[3*16] = अणु 3,0,0, 3,1,0, 3,2,0, 3,3,0,
				3,4,0, 3,5,0, 3,6,0, 3,7,0,
				3,8,0, 3,9,0, 3,10,0, 3,11,0,
				3,12,0, 3,13,0, 3,14,0, 3,15,0 पूर्ण;
	u32 node;
	अक्षर prop[64];
	पूर्णांक rv, len;

	/* Check अगर we're really running on a EFIKA */
	node = call_prom("finddevice", 1, 1, ADDR("/"));
	अगर (!PHANDLE_VALID(node))
		वापस;

	rv = prom_getprop(node, "model", prop, माप(prop));
	अगर (rv == PROM_ERROR)
		वापस;
	अगर (prom_म_भेद(prop, "EFIKA5K2"))
		वापस;

	prom_म_लिखो("Applying EFIKA device tree fixups\n");

	/* Claiming to be 'chrp' is death */
	node = call_prom("finddevice", 1, 1, ADDR("/"));
	rv = prom_getprop(node, "device_type", prop, माप(prop));
	अगर (rv != PROM_ERROR && (prom_म_भेद(prop, "chrp") == 0))
		prom_setprop(node, "/", "device_type", "efika", माप("efika"));

	/* CODEGEN,description is exposed in /proc/cpuinfo so
	   fix that too */
	rv = prom_getprop(node, "CODEGEN,description", prop, माप(prop));
	अगर (rv != PROM_ERROR && (prom_म_माला(prop, "CHRP")))
		prom_setprop(node, "/", "CODEGEN,description",
			     "Efika 5200B PowerPC System",
			     माप("Efika 5200B PowerPC System"));

	/* Fixup bestcomm पूर्णांकerrupts property */
	node = call_prom("finddevice", 1, 1, ADDR("/builtin/bestcomm"));
	अगर (PHANDLE_VALID(node)) अणु
		len = prom_getproplen(node, "interrupts");
		अगर (len == 12) अणु
			prom_म_लिखो("Fixing bestcomm interrupts property\n");
			prom_setprop(node, "/builtin/bestcom", "interrupts",
				     bcomm_irq, माप(bcomm_irq));
		पूर्ण
	पूर्ण

	/* Fixup sound पूर्णांकerrupts property */
	node = call_prom("finddevice", 1, 1, ADDR("/builtin/sound"));
	अगर (PHANDLE_VALID(node)) अणु
		rv = prom_getprop(node, "interrupts", prop, माप(prop));
		अगर (rv == PROM_ERROR) अणु
			prom_म_लिखो("Adding sound interrupts property\n");
			prom_setprop(node, "/builtin/sound", "interrupts",
				     sound_irq, माप(sound_irq));
		पूर्ण
	पूर्ण

	/* Make sure ethernet phy-handle property exists */
	fixup_device_tree_efika_add_phy();
पूर्ण
#अन्यथा
#घोषणा fixup_device_tree_efika()
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PASEMI_NEMO
/*
 * CFE supplied on Nemo is broken in several ways, biggest
 * problem is that it reassigns ISA पूर्णांकerrupts to unused mpic पूर्णांकs.
 * Add an पूर्णांकerrupt-controller property क्रम the io-bridge to use
 * and correct the पूर्णांकs so we can attach them to an irq_करोमुख्य
 */
अटल व्योम __init fixup_device_tree_pasemi(व्योम)
अणु
	u32 पूर्णांकerrupts[2], parent, rval, val = 0;
	अक्षर *name, *pci_name;
	phandle iob, node;

	/* Find the root pci node */
	name = "/pxp@0,e0000000";
	iob = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (!PHANDLE_VALID(iob))
		वापस;

	/* check अगर पूर्णांकerrupt-controller node set yet */
	अगर (prom_getproplen(iob, "interrupt-controller") !=PROM_ERROR)
		वापस;

	prom_म_लिखो("adding interrupt-controller property for SB600...\n");

	prom_setprop(iob, name, "interrupt-controller", &val, 0);

	pci_name = "/pxp@0,e0000000/pci@11";
	node = call_prom("finddevice", 1, 1, ADDR(pci_name));
	parent = ADDR(iob);

	क्रम( ; prom_next_node(&node); ) अणु
		/* scan each node क्रम one with an पूर्णांकerrupt */
		अगर (!PHANDLE_VALID(node))
			जारी;

		rval = prom_getproplen(node, "interrupts");
		अगर (rval == 0 || rval == PROM_ERROR)
			जारी;

		prom_getprop(node, "interrupts", &पूर्णांकerrupts, माप(पूर्णांकerrupts));
		अगर ((पूर्णांकerrupts[0] < 212) || (पूर्णांकerrupts[0] > 222))
			जारी;

		/* found a node, update both पूर्णांकerrupts and पूर्णांकerrupt-parent */
		अगर ((पूर्णांकerrupts[0] >= 212) && (पूर्णांकerrupts[0] <= 215))
			पूर्णांकerrupts[0] -= 203;
		अगर ((पूर्णांकerrupts[0] >= 216) && (पूर्णांकerrupts[0] <= 220))
			पूर्णांकerrupts[0] -= 213;
		अगर (पूर्णांकerrupts[0] == 221)
			पूर्णांकerrupts[0] = 14;
		अगर (पूर्णांकerrupts[0] == 222)
			पूर्णांकerrupts[0] = 8;

		prom_setprop(node, pci_name, "interrupts", पूर्णांकerrupts,
					माप(पूर्णांकerrupts));
		prom_setprop(node, pci_name, "interrupt-parent", &parent,
					माप(parent));
	पूर्ण

	/*
	 * The io-bridge has device_type set to 'io-bridge' change it to 'isa'
	 * so that generic isa-bridge code can add the SB600 and its on-board
	 * peripherals.
	 */
	name = "/pxp@0,e0000000/io-bridge@0";
	iob = call_prom("finddevice", 1, 1, ADDR(name));
	अगर (!PHANDLE_VALID(iob))
		वापस;

	/* device_type is alपढ़ोy set, just change it. */

	prom_म_लिखो("Changing device_type of SB600 node...\n");

	prom_setprop(iob, name, "device_type", "isa", माप("isa"));
पूर्ण
#अन्यथा	/* !CONFIG_PPC_PASEMI_NEMO */
अटल अंतरभूत व्योम fixup_device_tree_pasemi(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init fixup_device_tree(व्योम)
अणु
	fixup_device_tree_maple();
	fixup_device_tree_maple_memory_controller();
	fixup_device_tree_chrp();
	fixup_device_tree_pmac();
	fixup_device_tree_efika();
	fixup_device_tree_pasemi();
पूर्ण

अटल व्योम __init prom_find_boot_cpu(व्योम)
अणु
	__be32 rval;
	ihandle prom_cpu;
	phandle cpu_pkg;

	rval = 0;
	अगर (prom_getprop(prom.chosen, "cpu", &rval, माप(rval)) <= 0)
		वापस;
	prom_cpu = be32_to_cpu(rval);

	cpu_pkg = call_prom("instance-to-package", 1, 1, prom_cpu);

	अगर (!PHANDLE_VALID(cpu_pkg))
		वापस;

	prom_getprop(cpu_pkg, "reg", &rval, माप(rval));
	prom.cpu = be32_to_cpu(rval);

	prom_debug("Booting CPU hw index = %d\n", prom.cpu);
पूर्ण

अटल व्योम __init prom_check_initrd(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (r3 && r4 && r4 != 0xdeadbeef) अणु
		__be64 val;

		prom_initrd_start = is_kernel_addr(r3) ? __pa(r3) : r3;
		prom_initrd_end = prom_initrd_start + r4;

		val = cpu_to_be64(prom_initrd_start);
		prom_setprop(prom.chosen, "/chosen", "linux,initrd-start",
			     &val, माप(val));
		val = cpu_to_be64(prom_initrd_end);
		prom_setprop(prom.chosen, "/chosen", "linux,initrd-end",
			     &val, माप(val));

		reserve_mem(prom_initrd_start,
			    prom_initrd_end - prom_initrd_start);

		prom_debug("initrd_start=0x%lx\n", prom_initrd_start);
		prom_debug("initrd_end=0x%lx\n", prom_initrd_end);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */
पूर्ण

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_RELOCATABLE
अटल व्योम reloc_toc(व्योम)
अणु
पूर्ण

अटल व्योम unreloc_toc(व्योम)
अणु
पूर्ण
#अन्यथा
अटल व्योम __reloc_toc(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ nr_entries)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ *toc_entry;

	/* Get the start of the TOC by using r2 directly. */
	यंत्र अस्थिर("addi %0,2,-0x8000" : "=b" (toc_entry));

	क्रम (i = 0; i < nr_entries; i++) अणु
		*toc_entry = *toc_entry + offset;
		toc_entry++;
	पूर्ण
पूर्ण

अटल व्योम reloc_toc(व्योम)
अणु
	अचिन्हित दीर्घ offset = reloc_offset();
	अचिन्हित दीर्घ nr_entries =
		(__prom_init_toc_end - __prom_init_toc_start) / माप(दीर्घ);

	__reloc_toc(offset, nr_entries);

	mb();
पूर्ण

अटल व्योम unreloc_toc(व्योम)
अणु
	अचिन्हित दीर्घ offset = reloc_offset();
	अचिन्हित दीर्घ nr_entries =
		(__prom_init_toc_end - __prom_init_toc_start) / माप(दीर्घ);

	mb();

	__reloc_toc(-offset, nr_entries);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SVM
/*
 * Perक्रमm the Enter Secure Mode ultracall.
 */
अटल पूर्णांक enter_secure_mode(अचिन्हित दीर्घ kbase, अचिन्हित दीर्घ fdt)
अणु
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("r3") = UV_ESM;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("r4") = kbase;
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("r5") = fdt;

	यंत्र अस्थिर("sc 2" : "+r"(r3) : "r"(r4), "r"(r5));

	वापस r3;
पूर्ण

/*
 * Call the Ultravisor to transfer us to secure memory अगर we have an ESM blob.
 */
अटल व्योम __init setup_secure_guest(अचिन्हित दीर्घ kbase, अचिन्हित दीर्घ fdt)
अणु
	पूर्णांक ret;

	अगर (!prom_svm_enable)
		वापस;

	/* Switch to secure mode. */
	prom_म_लिखो("Switching to secure mode.\n");

	/*
	 * The ultravisor will करो an पूर्णांकegrity check of the kernel image but we
	 * relocated it so the check will fail. Restore the original image by
	 * relocating it back to the kernel भव base address.
	 */
	अगर (IS_ENABLED(CONFIG_RELOCATABLE))
		relocate(KERNELBASE);

	ret = enter_secure_mode(kbase, fdt);

	/* Relocate the kernel again. */
	अगर (IS_ENABLED(CONFIG_RELOCATABLE))
		relocate(kbase);

	अगर (ret != U_SUCCESS) अणु
		prom_म_लिखो("Returned %d from switching to secure mode.\n", ret);
		prom_rtas_os_term("Switch to secure mode failed.\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init setup_secure_guest(अचिन्हित दीर्घ kbase, अचिन्हित दीर्घ fdt)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SVM */

/*
 * We enter here early on, when the Open Firmware prom is still
 * handling exceptions and the MMU hash table क्रम us.
 */

अचिन्हित दीर्घ __init prom_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4,
			       अचिन्हित दीर्घ pp,
			       अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7,
			       अचिन्हित दीर्घ kbase)
अणु	
	अचिन्हित दीर्घ hdr;

#अगर_घोषित CONFIG_PPC32
	अचिन्हित दीर्घ offset = reloc_offset();
	reloc_got2(offset);
#अन्यथा
	reloc_toc();
#पूर्ण_अगर

	/*
	 * First zero the BSS
	 */
	स_रखो(&__bss_start, 0, __bss_stop - __bss_start);

	/*
	 * Init पूर्णांकerface to Open Firmware, get some node references,
	 * like /chosen
	 */
	prom_init_client_services(pp);

	/*
	 * See अगर this OF is old enough that we need to करो explicit maps
	 * and other workarounds
	 */
	prom_find_mmu();

	/*
	 * Init prom मानक_निकास device
	 */
	prom_init_मानक_निकास();

	prom_म_लिखो("Preparing to boot %s", linux_banner);

	/*
	 * Get शेष machine type. At this poपूर्णांक, we करो not dअगरferentiate
	 * between pSeries SMP and pSeries LPAR
	 */
	of_platक्रमm = prom_find_machine_type();
	prom_म_लिखो("Detected machine type: %x\n", of_platक्रमm);

#अगर_अघोषित CONFIG_NONSTATIC_KERNEL
	/* Bail अगर this is a kdump kernel. */
	अगर (PHYSICAL_START > 0)
		prom_panic("Error: You can't boot a kdump kernel from OF!\n");
#पूर्ण_अगर

	/*
	 * Check क्रम an initrd
	 */
	prom_check_initrd(r3, r4);

	/*
	 * Do early parsing of command line
	 */
	early_cmdline_parse();

#अगर_घोषित CONFIG_PPC_PSERIES
	/*
	 * On pSeries, inक्रमm the firmware about our capabilities
	 */
	अगर (of_platक्रमm == PLATFORM_PSERIES ||
	    of_platक्रमm == PLATFORM_PSERIES_LPAR)
		prom_send_capabilities();
#पूर्ण_अगर

	/*
	 * Copy the CPU hold code
	 */
	अगर (of_platक्रमm != PLATFORM_POWERMAC)
		copy_and_flush(0, kbase, 0x100, 0);

	/*
	 * Initialize memory management within prom_init
	 */
	prom_init_mem();

	/*
	 * Determine which cpu is actually running right _now_
	 */
	prom_find_boot_cpu();

	/* 
	 * Initialize display devices
	 */
	prom_check_displays();

#अगर defined(CONFIG_PPC64) && defined(__BIG_ENDIAN__)
	/*
	 * Initialize IOMMU (TCE tables) on pSeries. Do that beक्रमe anything अन्यथा
	 * that uses the allocator, we need to make sure we get the top of memory
	 * available क्रम us here...
	 */
	अगर (of_platक्रमm == PLATFORM_PSERIES)
		prom_initialize_tce_table();
#पूर्ण_अगर

	/*
	 * On non-घातermacs, try to instantiate RTAS. PowerMacs करोn't
	 * have a usable RTAS implementation.
	 */
	अगर (of_platक्रमm != PLATFORM_POWERMAC)
		prom_instantiate_rtas();

#अगर_घोषित CONFIG_PPC64
	/* instantiate sml */
	prom_instantiate_sml();
#पूर्ण_अगर

	/*
	 * On non-घातermacs, put all CPUs in spin-loops.
	 *
	 * PowerMacs use a dअगरferent mechanism to spin CPUs
	 *
	 * (This must be करोne after instanciating RTAS)
	 */
	अगर (of_platक्रमm != PLATFORM_POWERMAC)
		prom_hold_cpus();

	/*
	 * Fill in some infos क्रम use by the kernel later on
	 */
	अगर (prom_memory_limit) अणु
		__be64 val = cpu_to_be64(prom_memory_limit);
		prom_setprop(prom.chosen, "/chosen", "linux,memory-limit",
			     &val, माप(val));
	पूर्ण
#अगर_घोषित CONFIG_PPC64
	अगर (prom_iommu_off)
		prom_setprop(prom.chosen, "/chosen", "linux,iommu-off",
			     शून्य, 0);

	अगर (prom_iommu_क्रमce_on)
		prom_setprop(prom.chosen, "/chosen", "linux,iommu-force-on",
			     शून्य, 0);

	अगर (prom_tce_alloc_start) अणु
		prom_setprop(prom.chosen, "/chosen", "linux,tce-alloc-start",
			     &prom_tce_alloc_start,
			     माप(prom_tce_alloc_start));
		prom_setprop(prom.chosen, "/chosen", "linux,tce-alloc-end",
			     &prom_tce_alloc_end,
			     माप(prom_tce_alloc_end));
	पूर्ण
#पूर्ण_अगर

	/*
	 * Fixup any known bugs in the device-tree
	 */
	fixup_device_tree();

	/*
	 * Now finally create the flattened device-tree
	 */
	prom_म_लिखो("copying OF device tree...\n");
	flatten_device_tree();

	/*
	 * in हाल मानक_निवेश is USB and still active on IBM machines...
	 * Unक्रमtunately quiesce crashes on some घातermacs अगर we have
	 * बंदd मानक_निवेश alपढ़ोy (in particular the घातerbook 101).
	 */
	अगर (of_platक्रमm != PLATFORM_POWERMAC)
		prom_बंद_मानक_निवेश();

	/*
	 * Call OF "quiesce" method to shut करोwn pending DMA's from
	 * devices etc...
	 */
	prom_म_लिखो("Quiescing Open Firmware ...\n");
	call_prom("quiesce", 0, 0);

	/*
	 * And finally, call the kernel passing it the flattened device
	 * tree and शून्य as r5, thus triggering the new entry poपूर्णांक which
	 * is common to us and kexec
	 */
	hdr = dt_header_start;

	prom_म_लिखो("Booting Linux via __start() @ 0x%lx ...\n", kbase);
	prom_debug("->dt_header_start=0x%lx\n", hdr);

#अगर_घोषित CONFIG_PPC32
	reloc_got2(-offset);
#अन्यथा
	unreloc_toc();
#पूर्ण_अगर

	/* Move to secure memory अगर we're supposed to be secure guests. */
	setup_secure_guest(kbase, hdr);

	__start(hdr, kbase, 0, 0, 0, 0, 0);

	वापस 0;
पूर्ण
