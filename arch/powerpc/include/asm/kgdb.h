<शैली गुरु>
/*
 * The PowerPC (32/64) specअगरic defines / बाह्यs क्रम KGDB.  Based on
 * the previous 32bit and 64bit specअगरic files, which had the following
 * copyrights:
 *
 * PPC64 Mods (C) 2005 Frank Rowand (frowand@mvista.com)
 * PPC Mods (C) 2004 Tom Rini (trini@mvista.com)
 * PPC Mods (C) 2003 John Whitney (john.whitney@बारys.com)
 * PPC Mods (C) 1998 Michael Tesch (tesch@cs.wisc.edu)
 *
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Author: Tom Rini <trini@kernel.crashing.org>
 *
 * 2006 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __POWERPC_KGDB_H__
#घोषणा __POWERPC_KGDB_H__

#अगर_अघोषित __ASSEMBLY__

#घोषणा BREAK_INSTR_SIZE	4
#घोषणा BUFMAX			((NUMREGBYTES * 2) + 512)
#घोषणा OUTBUFMAX		((NUMREGBYTES * 2) + 512)

#घोषणा BREAK_INSTR		0x7d821008	/* twge r2, r2 */

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र(stringअगरy_in_c(.दीर्घ BREAK_INSTR));
पूर्ण
#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा DBG_MAX_REG_NUM     70

/* The number bytes of रेजिस्टरs we have to save depends on a few
 * things.  For 64bit we शेष to not including vector रेजिस्टरs and
 * vector state रेजिस्टरs. */
#अगर_घोषित CONFIG_PPC64
/*
 * 64 bit (8 byte) रेजिस्टरs:
 *   32 gpr, 32 fpr, nip, msr, link, ctr
 * 32 bit (4 byte) रेजिस्टरs:
 *   ccr, xer, fpscr
 */
#घोषणा NUMREGBYTES		((68 * 8) + (3 * 4))
#घोषणा NUMCRITREGBYTES		184
#अन्यथा /* CONFIG_PPC32 */
/* On non-E500 family PPC32 we determine the size by picking the last
 * रेजिस्टर we need, but on E500 we skip sections so we list what we
 * need to store, and add it up. */
#अगर_अघोषित CONFIG_E500
#घोषणा MAXREG			(PT_FPSCR+1)
#अन्यथा
/* 32 GPRs (8 bytes), nip, msr, ccr, link, ctr, xer, acc (8 bytes), spefscr*/
#घोषणा MAXREG                 ((32*2)+6+2+1)
#पूर्ण_अगर
#घोषणा NUMREGBYTES		(MAXREG * माप(पूर्णांक))
/* CR/LR, R1, R2, R13-R31 inclusive. */
#घोषणा NUMCRITREGBYTES		(23 * माप(पूर्णांक))
#पूर्ण_अगर /* 32/64 */
#पूर्ण_अगर /* !(__ASSEMBLY__) */
#पूर्ण_अगर /* !__POWERPC_KGDB_H__ */
#पूर्ण_अगर /* __KERNEL__ */
