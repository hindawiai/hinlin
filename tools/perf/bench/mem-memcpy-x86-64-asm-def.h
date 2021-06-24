<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

MEMCPY_FN(स_नकल_orig,
	"x86-64-unrolled",
	"unrolled memcpy() in arch/x86/lib/memcpy_64.S")

MEMCPY_FN(__स_नकल,
	"x86-64-movsq",
	"movsq-based memcpy() in arch/x86/lib/memcpy_64.S")

MEMCPY_FN(स_नकल_erms,
	"x86-64-movsb",
	"movsb-based memcpy() in arch/x86/lib/memcpy_64.S")
