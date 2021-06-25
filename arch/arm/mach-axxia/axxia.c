<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the LSI Axxia SoC devices based on ARM cores.
 *
 * Copyright (C) 2012 LSI
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर *स्थिर axxia_dt_match[] __initस्थिर = अणु
	"lsi,axm5516",
	"lsi,axm5516-sim",
	"lsi,axm5516-emu",
	शून्य
पूर्ण;

DT_MACHINE_START(AXXIA_DT, "LSI Axxia AXM55XX")
	.dt_compat = axxia_dt_match,
MACHINE_END
