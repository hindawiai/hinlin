<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (c) 2015 Cadence Design Systems Inc.
 */

#समावेश <मानकघोष.स>
#समावेश <dwarf-regs.h>

#घोषणा XTENSA_MAX_REGS 16

स्थिर अक्षर *xtensa_regs_table[XTENSA_MAX_REGS] = अणु
	"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
	"a8", "a9", "a10", "a11", "a12", "a13", "a14", "a15",
पूर्ण;

स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस n < XTENSA_MAX_REGS ? xtensa_regs_table[n] : शून्य;
पूर्ण
