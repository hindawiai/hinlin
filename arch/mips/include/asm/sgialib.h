<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI ARCS firmware पूर्णांकerface library क्रम the Linux kernel.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 2001, 2002 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_SGIALIB_H
#घोषणा _ASM_SGIALIB_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/sgiarcs.h>

बाह्य काष्ठा linux_romvec *romvec;

बाह्य पूर्णांक prom_flags;

#घोषणा PROM_FLAG_ARCS			1
#घोषणा PROM_FLAG_USE_AS_CONSOLE	2
#घोषणा PROM_FLAG_DONT_FREE_TEMP	4

/* Simple अक्षर-by-अक्षर console I/O. */
बाह्य अक्षर prom_अक्षर_लो(व्योम);

/* Get next memory descriptor after CURR, वापसs first descriptor
 * in chain is CURR is शून्य.
 */
बाह्य काष्ठा linux_mdesc *prom_geपंचांगdesc(काष्ठा linux_mdesc *curr);
#घोषणा PROM_शून्य_MDESC	  ((काष्ठा linux_mdesc *) 0)

/* Called by prom_init to setup the physical memory pmemblock
 * array.
 */
बाह्य व्योम prom_meminit(व्योम);

/* PROM device tree library routines. */
#घोषणा PROM_शून्य_COMPONENT ((pcomponent *) 0)

/* This is called at prom_init समय to identअगरy the
 * ARC architecture we are running on
 */
बाह्य व्योम prom_identअगरy_arch(व्योम);

/* Environment variable routines. */
बाह्य PCHAR ArcGetEnvironmentVariable(PCHAR name);

/* ARCS command line parsing. */
बाह्य व्योम prom_init_cmdline(पूर्णांक argc, LONG *argv);

/* File operations. */
बाह्य LONG ArcRead(ULONG fd, PVOID buf, ULONG num, PULONG cnt);
बाह्य LONG ArcWrite(ULONG fd, PVOID buf, ULONG num, PULONG cnt);

/* Misc. routines. */
बाह्य VOID ArcEnterInteractiveMode(VOID) __noवापस;
बाह्य DISPLAY_STATUS *ArcGetDisplayStatus(ULONG FileID);

#पूर्ण_अगर /* _ASM_SGIALIB_H */
