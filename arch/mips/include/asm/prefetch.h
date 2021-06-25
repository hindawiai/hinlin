<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 by Ralf Baechle
 */
#अगर_अघोषित __ASM_PREFETCH_H
#घोषणा __ASM_PREFETCH_H


/*
 * R5000 and RM5200 implements pref and prefx inकाष्ठाions but they're nops, so
 * rather than wasting समय we pretend these processors करोn't support
 * prefetching at all.
 *
 * R5432 implements Load, Store, LoadStreamed, StoreStreamed, LoadRetained,
 * StoreRetained and WriteBackInvalidate but not Pref_PrepareForStore.
 *
 * Hell (and the book on my shelf I can't खोलो ...) know what the R8000 करोes.
 *
 * RM7000 version 1.0 पूर्णांकerprets all hपूर्णांकs as Pref_Load; version 2.0 implements
 * Pref_PrepareForStore also.
 *
 * RM9000 is MIPS IV but implements prefetching like MIPS32/MIPS64; it's
 * Pref_WriteBackInvalidate is a nop and Pref_PrepareForStore is broken in
 * current versions due to erratum G105.
 *
 * VR5500 (including VR5701 and VR7701) only implement load prefetch.
 *
 * Finally MIPS32 and MIPS64 implement all of the following hपूर्णांकs.
 */

#घोषणा Pref_Load			0
#घोषणा Pref_Store			1
						/* 2 and 3 are reserved */
#घोषणा Pref_LoadStreamed		4
#घोषणा Pref_StoreStreamed		5
#घोषणा Pref_LoadRetained		6
#घोषणा Pref_StoreRetained		7
						/* 8 ... 24 are reserved */
#घोषणा Pref_WriteBackInvalidate	25
#घोषणा Pref_PrepareForStore		30

#अगर_घोषित __ASSEMBLY__

	.macro	__pref hपूर्णांक addr
#अगर_घोषित CONFIG_CPU_HAS_PREFETCH
	pref	\hपूर्णांक, \चddr
#पूर्ण_अगर
	.endm

	.macro	pref_load addr
	__pref	Pref_Load, \चddr
	.endm

	.macro	pref_store addr
	__pref	Pref_Store, \चddr
	.endm

	.macro	pref_load_streamed addr
	__pref	Pref_LoadStreamed, \चddr
	.endm

	.macro	pref_store_streamed addr
	__pref	Pref_StoreStreamed, \चddr
	.endm

	.macro	pref_load_retained addr
	__pref	Pref_LoadRetained, \चddr
	.endm

	.macro	pref_store_retained addr
	__pref	Pref_StoreRetained, \चddr
	.endm

	.macro	pref_wback_inv addr
	__pref	Pref_WriteBackInvalidate, \चddr
	.endm

	.macro	pref_prepare_क्रम_store addr
	__pref	Pref_PrepareForStore, \चddr
	.endm

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_PREFETCH_H */
