<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC simulation Platक्रमm support code
 *
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/init.h>
#समावेश <यंत्र/mach_desc.h>

/*----------------------- Machine Descriptions ------------------------------
 *
 * Machine description is simply a set of platक्रमm/board specअगरic callbacks
 * This is not directly related to DeviceTree based dynamic device creation,
 * however as part of early device tree scan, we also select the right
 * callback set, by matching the DT compatible name.
 */

अटल स्थिर अक्षर *simulation_compat[] __initस्थिर = अणु
#अगर_घोषित CONFIG_ISA_ARCOMPACT
	"snps,nsim",
	"snps,nsimosci",
#अन्यथा
	"snps,nsimosci_hs",
	"snps,zebu_hs",
#पूर्ण_अगर
	शून्य,
पूर्ण;

MACHINE_START(SIMULATION, "simulation")
	.dt_compat	= simulation_compat,
MACHINE_END
