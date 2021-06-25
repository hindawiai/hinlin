<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    EBCDIC -> ASCII, ASCII -> EBCDIC conversion routines.
 *
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _EBCDIC_H
#घोषणा _EBCDIC_H

#समावेश <linux/types.h>

बाह्य __u8 _ascebc_500[256];   /* ASCII -> EBCDIC 500 conversion table */
बाह्य __u8 _ebcasc_500[256];   /* EBCDIC 500 -> ASCII conversion table */
बाह्य __u8 _ascebc[256];   /* ASCII -> EBCDIC conversion table */
बाह्य __u8 _ebcasc[256];   /* EBCDIC -> ASCII conversion table */
बाह्य __u8 _ebc_छोटे[256]; /* EBCDIC -> lowerहाल */
बाह्य __u8 _ebc_बड़े[256]; /* EBCDIC -> upperहाल */

अटल अंतरभूत व्योम
codepage_convert(स्थिर __u8 *codepage, अस्थिर अक्षर *addr, अचिन्हित दीर्घ nr)
अणु
	अगर (nr-- <= 0)
		वापस;
	यंत्र अस्थिर(
		"	bras	1,1f\n"
		"	tr	0(1,%0),0(%2)\n"
		"0:	tr	0(256,%0),0(%2)\n"
		"	la	%0,256(%0)\n"
		"1:	ahi	%1,-256\n"
		"	jnm	0b\n"
		"	ex	%1,0(1)"
		: "+&a" (addr), "+&a" (nr)
		: "a" (codepage) : "cc", "memory", "1");
पूर्ण

#घोषणा ASCEBC(addr,nr) codepage_convert(_ascebc, addr, nr)
#घोषणा EBCASC(addr,nr) codepage_convert(_ebcasc, addr, nr)
#घोषणा ASCEBC_500(addr,nr) codepage_convert(_ascebc_500, addr, nr)
#घोषणा EBCASC_500(addr,nr) codepage_convert(_ebcasc_500, addr, nr)
#घोषणा EBC_TOLOWER(addr,nr) codepage_convert(_ebc_छोटे, addr, nr)
#घोषणा EBC_TOUPPER(addr,nr) codepage_convert(_ebc_बड़े, addr, nr)

#पूर्ण_अगर

