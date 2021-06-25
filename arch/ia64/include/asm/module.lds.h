<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
SECTIONS अणु
	/* Group unwind sections पूर्णांकo a single section: */
	.IA_64.unwind_info : अणु *(.IA_64.unwind_info*) पूर्ण
	.IA_64.unwind : अणु *(.IA_64.unwind*) पूर्ण
	/*
	 * Create place-holder sections to hold the PLTs, GOT, and
	 * official procedure-descriptors (.opd).
	 */
	.core.plt : अणु BYTE(0) पूर्ण
	.init.plt : अणु BYTE(0) पूर्ण
	.got : अणु BYTE(0) पूर्ण
	.opd : अणु BYTE(0) पूर्ण
पूर्ण
