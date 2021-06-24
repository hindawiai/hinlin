<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/prom.h
 *
 *	DECstation PROM पूर्णांकerface.
 *
 *	Copyright (C) 2002  Maciej W. Rozycki
 *
 *	Based on arch/mips/dec/prom/prom.h by the Anonymous.
 */
#अगर_अघोषित _ASM_DEC_PROM_H
#घोषणा _ASM_DEC_PROM_H

#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>

/*
 * PMAX/3MAX PROM entry poपूर्णांकs क्रम DS2100/3100's and DS5000/2xx's.
 * Many of these will work क्रम MIPSen as well!
 */
#घोषणा VEC_RESET		(u64 *)CKSEG1ADDR(0x1fc00000)
							/* Prom base address */

#घोषणा PMAX_PROM_ENTRY(x)	(VEC_RESET + (x))	/* Prom jump table */

#घोषणा PMAX_PROM_HALT		PMAX_PROM_ENTRY(2)	/* valid on MIPSen */
#घोषणा PMAX_PROM_AUTOBOOT	PMAX_PROM_ENTRY(5)	/* valid on MIPSen */
#घोषणा PMAX_PROM_OPEN		PMAX_PROM_ENTRY(6)
#घोषणा PMAX_PROM_READ		PMAX_PROM_ENTRY(7)
#घोषणा PMAX_PROM_CLOSE		PMAX_PROM_ENTRY(10)
#घोषणा PMAX_PROM_LSEEK		PMAX_PROM_ENTRY(11)
#घोषणा PMAX_PROM_GETCHAR	PMAX_PROM_ENTRY(12)
#घोषणा PMAX_PROM_PUTCHAR	PMAX_PROM_ENTRY(13)	/* 12 on MIPSen */
#घोषणा PMAX_PROM_GETS		PMAX_PROM_ENTRY(15)
#घोषणा PMAX_PROM_PRINTF	PMAX_PROM_ENTRY(17)
#घोषणा PMAX_PROM_GETENV	PMAX_PROM_ENTRY(33)	/* valid on MIPSen */


/*
 * Magic number indicating REX PROM available on DECstation.  Found in
 * रेजिस्टर a2 on transfer of control to program from PROM.
 */
#घोषणा REX_PROM_MAGIC		0x30464354

#अगर_घोषित CONFIG_64BIT

#घोषणा prom_is_rex(magic)	1	/* KN04 and KN05 are REX PROMs.  */

#अन्यथा /* !CONFIG_64BIT */

#घोषणा prom_is_rex(magic)	((magic) == REX_PROM_MAGIC)

#पूर्ण_अगर /* !CONFIG_64BIT */


/*
 * 3MIN/MAXINE PROM entry poपूर्णांकs क्रम DS5000/1xx's, DS5000/xx's and
 * DS5000/2x0.
 */
#घोषणा REX_PROM_GETBITMAP	0x84/4	/* get mem biपंचांगap */
#घोषणा REX_PROM_GETCHAR	0x24/4	/* अ_लोh() */
#घोषणा REX_PROM_GETENV		0x64/4	/* get env. variable */
#घोषणा REX_PROM_GETSYSID	0x80/4	/* get प्रणाली id */
#घोषणा REX_PROM_GETTCINFO	0xa4/4
#घोषणा REX_PROM_PRINTF		0x30/4	/* म_लिखो() */
#घोषणा REX_PROM_SLOTADDR	0x6c/4	/* slotaddr */
#घोषणा REX_PROM_BOOTINIT	0x54/4	/* खोलो() */
#घोषणा REX_PROM_BOOTREAD	0x58/4	/* पढ़ो() */
#घोषणा REX_PROM_CLEARCACHE	0x7c/4


/*
 * Used by rex_getbiपंचांगap().
 */
प्रकार काष्ठा अणु
	पूर्णांक pagesize;
	अचिन्हित अक्षर biपंचांगap[0];
पूर्ण memmap;


/*
 * Function poपूर्णांकers as पढ़ो from a PROM's callback vector.
 */
बाह्य पूर्णांक (*__rex_bootinit)(व्योम);
बाह्य पूर्णांक (*__rex_bootपढ़ो)(व्योम);
बाह्य पूर्णांक (*__rex_getbiपंचांगap)(memmap *);
बाह्य अचिन्हित दीर्घ *(*__rex_slot_address)(पूर्णांक);
बाह्य व्योम *(*__rex_gettcinfo)(व्योम);
बाह्य पूर्णांक (*__rex_माला_लोysid)(व्योम);
बाह्य व्योम (*__rex_clear_cache)(व्योम);

बाह्य पूर्णांक (*__prom_अक्षर_लो)(व्योम);
बाह्य अक्षर *(*__prom_दो_पर्या)(अक्षर *);
बाह्य पूर्णांक (*__prom_म_लिखो)(अक्षर *, ...);

बाह्य पूर्णांक (*__pmax_खोलो)(अक्षर*, पूर्णांक);
बाह्य पूर्णांक (*__pmax_lseek)(पूर्णांक, दीर्घ, पूर्णांक);
बाह्य पूर्णांक (*__pmax_पढ़ो)(पूर्णांक, व्योम *, पूर्णांक);
बाह्य पूर्णांक (*__pmax_बंद)(पूर्णांक);


#अगर_घोषित CONFIG_64BIT

/*
 * On MIPS64 we have to call PROM functions via a helper
 * dispatcher to accommodate ABI incompatibilities.
 */
#घोषणा __DEC_PROM_O32(fun, arg) fun arg __यंत्र__(#fun); \
				 __यंत्र__(#fun " = call_o32")

पूर्णांक __DEC_PROM_O32(_rex_bootinit, (पूर्णांक (*)(व्योम), व्योम *));
पूर्णांक __DEC_PROM_O32(_rex_bootपढ़ो, (पूर्णांक (*)(व्योम), व्योम *));
पूर्णांक __DEC_PROM_O32(_rex_getbiपंचांगap, (पूर्णांक (*)(memmap *), व्योम *, memmap *));
अचिन्हित दीर्घ *__DEC_PROM_O32(_rex_slot_address,
			     (अचिन्हित दीर्घ *(*)(पूर्णांक), व्योम *, पूर्णांक));
व्योम *__DEC_PROM_O32(_rex_gettcinfo, (व्योम *(*)(व्योम), व्योम *));
पूर्णांक __DEC_PROM_O32(_rex_माला_लोysid, (पूर्णांक (*)(व्योम), व्योम *));
व्योम __DEC_PROM_O32(_rex_clear_cache, (व्योम (*)(व्योम), व्योम *));

पूर्णांक __DEC_PROM_O32(_prom_अक्षर_लो, (पूर्णांक (*)(व्योम), व्योम *));
अक्षर *__DEC_PROM_O32(_prom_दो_पर्या, (अक्षर *(*)(अक्षर *), व्योम *, अक्षर *));
पूर्णांक __DEC_PROM_O32(_prom_म_लिखो, (पूर्णांक (*)(अक्षर *, ...), व्योम *, अक्षर *, ...));


#घोषणा rex_bootinit()		_rex_bootinit(__rex_bootinit, शून्य)
#घोषणा rex_bootपढ़ो()		_rex_bootपढ़ो(__rex_bootपढ़ो, शून्य)
#घोषणा rex_getbiपंचांगap(x)	_rex_getbiपंचांगap(__rex_getbiपंचांगap, शून्य, x)
#घोषणा rex_slot_address(x)	_rex_slot_address(__rex_slot_address, शून्य, x)
#घोषणा rex_gettcinfo()		_rex_gettcinfo(__rex_gettcinfo, शून्य)
#घोषणा rex_माला_लोysid()		_rex_माला_लोysid(__rex_माला_लोysid, शून्य)
#घोषणा rex_clear_cache()	_rex_clear_cache(__rex_clear_cache, शून्य)

#घोषणा prom_अक्षर_लो()		_prom_अक्षर_लो(__prom_अक्षर_लो, शून्य)
#घोषणा prom_दो_पर्या(x)		_prom_दो_पर्या(__prom_दो_पर्या, शून्य, x)
#घोषणा prom_म_लिखो(x...)	_prom_म_लिखो(__prom_म_लिखो, शून्य, x)

#अन्यथा /* !CONFIG_64BIT */

/*
 * On plain MIPS we just call PROM functions directly.
 */
#घोषणा rex_bootinit		__rex_bootinit
#घोषणा rex_bootपढ़ो		__rex_bootपढ़ो
#घोषणा rex_getbiपंचांगap		__rex_getbiपंचांगap
#घोषणा rex_slot_address	__rex_slot_address
#घोषणा rex_gettcinfo		__rex_gettcinfo
#घोषणा rex_माला_लोysid		__rex_माला_लोysid
#घोषणा rex_clear_cache		__rex_clear_cache

#घोषणा prom_अक्षर_लो		__prom_अक्षर_लो
#घोषणा prom_दो_पर्या		__prom_दो_पर्या
#घोषणा prom_म_लिखो		__prom_म_लिखो

#घोषणा pmax_खोलो		__pmax_खोलो
#घोषणा pmax_lseek		__pmax_lseek
#घोषणा pmax_पढ़ो		__pmax_पढ़ो
#घोषणा pmax_बंद		__pmax_बंद

#पूर्ण_अगर /* !CONFIG_64BIT */


बाह्य व्योम prom_meminit(u32);
बाह्य व्योम prom_identअगरy_arch(u32);
बाह्य व्योम prom_init_cmdline(s32, s32 *, u32);

बाह्य व्योम रेजिस्टर_prom_console(व्योम);
बाह्य व्योम unरेजिस्टर_prom_console(व्योम);

#पूर्ण_अगर /* _ASM_DEC_PROM_H */
