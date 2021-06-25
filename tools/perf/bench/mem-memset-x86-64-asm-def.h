<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

MEMSET_FN(स_रखो_orig,
	"x86-64-unrolled",
	"unrolled memset() in arch/x86/lib/memset_64.S")

MEMSET_FN(__स_रखो,
	"x86-64-stosq",
	"movsq-based memset() in arch/x86/lib/memset_64.S")

MEMSET_FN(स_रखो_erms,
	"x86-64-stosb",
	"movsb-based memset() in arch/x86/lib/memset_64.S")
