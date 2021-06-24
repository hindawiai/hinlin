<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -----------------------------------------------------------------------
 *
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Simple helper function क्रम initializing a रेजिस्टर set.
 *
 * Note that this sets EFLAGS_CF in the input रेजिस्टर set; this
 * makes it easier to catch functions which करो nothing but करोn't
 * explicitly set CF.
 */

#समावेश "boot.h"
#समावेश "string.h"

व्योम initregs(काष्ठा biosregs *reg)
अणु
	स_रखो(reg, 0, माप(*reg));
	reg->eflags |= X86_EFLAGS_CF;
	reg->ds = ds();
	reg->es = ds();
	reg->fs = fs();
	reg->gs = gs();
पूर्ण
