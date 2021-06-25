<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (C) 2010 Matt Fleming <matt@console-pimps.org>
 */

#समावेश <मानकघोष.स>
#समावेश <dwarf-regs.h>

/*
 * Generic dwarf analysis helpers
 */

#घोषणा SH_MAX_REGS 18
स्थिर अक्षर *sh_regs_table[SH_MAX_REGS] = अणु
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7",
	"r8",
	"r9",
	"r10",
	"r11",
	"r12",
	"r13",
	"r14",
	"r15",
	"pc",
	"pr",
पूर्ण;

/* Return architecture dependent रेजिस्टर string (क्रम kprobe-tracer) */
स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस (n < SH_MAX_REGS) ? sh_regs_table[n] : शून्य;
पूर्ण
