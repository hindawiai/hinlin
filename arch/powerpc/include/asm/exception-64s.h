<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_EXCEPTION_H
#घोषणा _ASM_POWERPC_EXCEPTION_H
/*
 * Extracted from head_64.S
 *
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Rewritten by Cort Dougan (cort@cs.nmt.edu) क्रम PReP
 *    Copyright (C) 1996 Cort Dougan <cort@cs.nmt.edu>
 *  Adapted क्रम Power Macपूर्णांकosh by Paul Mackerras.
 *  Low-level exception handlers and MMU support
 *  rewritten by Paul Mackerras.
 *    Copyright (C) 1996 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen, Peter Bergner, and
 *    Mike Corrigan अणुengebret|bergner|mikejcपूर्ण@us.ibm.com
 *
 *  This file contains the low-level support and setup क्रम the
 *  PowerPC-64 platक्रमm, including trap and पूर्णांकerrupt dispatch.
 */
/*
 * The following macros define the code that appears as
 * the prologue to each of the exception handlers.  They
 * are split पूर्णांकo two parts to allow a single kernel binary
 * to be used क्रम pSeries and iSeries.
 *
 * We make as much of the exception code common between native
 * exception handlers (including pSeries LPAR) and iSeries LPAR
 * implementations as possible.
 */
#समावेश <यंत्र/feature-fixups.h>

/* PACA save area size in u64 units (exgen, exmc, etc) */
#घोषणा EX_SIZE		10

/*
 * maximum recursive depth of MCE exceptions
 */
#घोषणा MAX_MCE_DEPTH	4

#अगर_घोषित __ASSEMBLY__

#घोषणा STF_ENTRY_BARRIER_SLOT						\
	STF_ENTRY_BARRIER_FIXUP_SECTION;				\
	nop;								\
	nop;								\
	nop

#घोषणा STF_EXIT_BARRIER_SLOT						\
	STF_EXIT_BARRIER_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;								\
	nop;								\
	nop;								\
	nop

#घोषणा ENTRY_FLUSH_SLOT						\
	ENTRY_FLUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;

#घोषणा SCV_ENTRY_FLUSH_SLOT						\
	SCV_ENTRY_FLUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;

/*
 * r10 must be मुक्त to use, r13 must be paca
 */
#घोषणा INTERRUPT_TO_KERNEL						\
	STF_ENTRY_BARRIER_SLOT;						\
	ENTRY_FLUSH_SLOT

/*
 * r10, ctr must be मुक्त to use, r13 must be paca
 */
#घोषणा SCV_INTERRUPT_TO_KERNEL						\
	STF_ENTRY_BARRIER_SLOT;						\
	SCV_ENTRY_FLUSH_SLOT

/*
 * Macros क्रम annotating the expected destination of (h)rfid
 *
 * The nop inकाष्ठाions allow us to insert one or more inकाष्ठाions to flush the
 * L1-D cache when वापसing to userspace or a guest.
 *
 * घातerpc relies on वापस from पूर्णांकerrupt/syscall being context synchronising
 * (which hrfid, rfid, and rfscv are) to support ARCH_HAS_MEMBARRIER_SYNC_CORE
 * without additional synchronisation inकाष्ठाions.
 *
 * soft-masked पूर्णांकerrupt replay करोes not include a context-synchronising rfid,
 * but those always वापस to kernel, the sync is only required when वापसing
 * to user.
 */
#घोषणा RFI_FLUSH_SLOT							\
	RFI_FLUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop

#घोषणा RFI_TO_KERNEL							\
	rfid

#घोषणा RFI_TO_USER							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	rfid;								\
	b	rfi_flush_fallback

#घोषणा RFI_TO_USER_OR_KERNEL						\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	rfid;								\
	b	rfi_flush_fallback

#घोषणा RFI_TO_GUEST							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	rfid;								\
	b	rfi_flush_fallback

#घोषणा HRFI_TO_KERNEL							\
	hrfid

#घोषणा HRFI_TO_USER							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	hrfid;								\
	b	hrfi_flush_fallback

#घोषणा HRFI_TO_USER_OR_KERNEL						\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	hrfid;								\
	b	hrfi_flush_fallback

#घोषणा HRFI_TO_GUEST							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	hrfid;								\
	b	hrfi_flush_fallback

#घोषणा HRFI_TO_UNKNOWN							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	hrfid;								\
	b	hrfi_flush_fallback

#घोषणा RFSCV_TO_USER							\
	STF_EXIT_BARRIER_SLOT;						\
	RFI_FLUSH_SLOT;							\
	RFSCV;								\
	b	rfscv_flush_fallback

#अन्यथा /* __ASSEMBLY__ */
/* Prototype क्रम function defined in exceptions-64s.S */
व्योम करो_uaccess_flush(व्योम);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_POWERPC_EXCEPTION_H */
