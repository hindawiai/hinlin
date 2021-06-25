<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश "tests/tests.h"
#समावेश "arch-tests.h"

काष्ठा test arch_tests[] = अणु
	अणु
		.desc = "x86 rdpmc",
		.func = test__rdpmc,
	पूर्ण,
#अगर_घोषित HAVE_DWARF_UNWIND_SUPPORT
	अणु
		.desc = "DWARF unwind",
		.func = test__dwarf_unwind,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित HAVE_AUXTRACE_SUPPORT
	अणु
		.desc = "x86 instruction decoder - new instructions",
		.func = test__insn_x86,
	पूर्ण,
	अणु
		.desc = "Intel PT packet decoder",
		.func = test__पूर्णांकel_pt_pkt_decoder,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(__x86_64__)
	अणु
		.desc = "x86 bp modify",
		.func = test__bp_modअगरy,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "x86 Sample parsing",
		.func = test__x86_sample_parsing,
	पूर्ण,
	अणु
		.func = शून्य,
	पूर्ण,

पूर्ण;
