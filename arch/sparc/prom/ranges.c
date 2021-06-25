<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ranges.c: Handle ranges in newer proms क्रम obio/sbus.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/types.h>

अटल काष्ठा linux_prom_ranges promlib_obio_ranges[PROMREG_MAX];
अटल पूर्णांक num_obio_ranges;

/* Adjust रेजिस्टर values based upon the ranges parameters. */
अटल व्योम prom_adjust_regs(काष्ठा linux_prom_रेजिस्टरs *regp, पूर्णांक nregs,
			     काष्ठा linux_prom_ranges *rangep, पूर्णांक nranges)
अणु
	पूर्णांक regc, rngc;

	क्रम (regc = 0; regc < nregs; regc++) अणु
		क्रम (rngc = 0; rngc < nranges; rngc++)
			अगर (regp[regc].which_io == rangep[rngc].ot_child_space)
				अवरोध; /* Fount it */
		अगर (rngc == nranges) /* oops */
			prom_म_लिखो("adjust_regs: Could not find range with matching bus type...\n");
		regp[regc].which_io = rangep[rngc].ot_parent_space;
		regp[regc].phys_addr -= rangep[rngc].ot_child_base;
		regp[regc].phys_addr += rangep[rngc].ot_parent_base;
	पूर्ण
पूर्ण

अटल व्योम prom_adjust_ranges(काष्ठा linux_prom_ranges *ranges1, पूर्णांक nranges1,
			       काष्ठा linux_prom_ranges *ranges2, पूर्णांक nranges2)
अणु
	पूर्णांक rng1c, rng2c;

	क्रम (rng1c = 0; rng1c < nranges1; rng1c++) अणु
		क्रम (rng2c = 0; rng2c < nranges2; rng2c++)
			अगर (ranges1[rng1c].ot_parent_space == ranges2[rng2c].ot_child_space &&
			   ranges1[rng1c].ot_parent_base >= ranges2[rng2c].ot_child_base &&
			   ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size - ranges1[rng1c].ot_parent_base > 0U)
			अवरोध;
		अगर (rng2c == nranges2) /* oops */
			prom_म_लिखो("adjust_ranges: Could not find matching bus type...\n");
		अन्यथा अगर (ranges1[rng1c].ot_parent_base + ranges1[rng1c].or_size > ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size)
			ranges1[rng1c].or_size = ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size - ranges1[rng1c].ot_parent_base;
		ranges1[rng1c].ot_parent_space = ranges2[rng2c].ot_parent_space;
		ranges1[rng1c].ot_parent_base += ranges2[rng2c].ot_parent_base;
	पूर्ण
पूर्ण

/* Apply probed obio ranges to रेजिस्टरs passed, अगर no ranges वापस. */
व्योम prom_apply_obio_ranges(काष्ठा linux_prom_रेजिस्टरs *regs, पूर्णांक nregs)
अणु
	अगर (num_obio_ranges)
		prom_adjust_regs(regs, nregs, promlib_obio_ranges, num_obio_ranges);
पूर्ण
EXPORT_SYMBOL(prom_apply_obio_ranges);

व्योम __init prom_ranges_init(व्योम)
अणु
	phandle node, obio_node;
	पूर्णांक success;

	num_obio_ranges = 0;

	/* Check क्रम obio and sbus ranges. */
	node = prom_अ_लोhild(prom_root_node);
	obio_node = prom_searchsiblings(node, "obio");

	अगर (obio_node) अणु
		success = prom_getproperty(obio_node, "ranges",
					   (अक्षर *) promlib_obio_ranges,
					   माप(promlib_obio_ranges));
		अगर (success != -1)
			num_obio_ranges = (success / माप(काष्ठा linux_prom_ranges));
	पूर्ण

	अगर (num_obio_ranges)
		prom_म_लिखो("PROMLIB: obio_ranges %d\n", num_obio_ranges);
पूर्ण

व्योम prom_apply_generic_ranges(phandle node, phandle parent,
			       काष्ठा linux_prom_रेजिस्टरs *regs, पूर्णांक nregs)
अणु
	पूर्णांक success;
	पूर्णांक num_ranges;
	काष्ठा linux_prom_ranges ranges[PROMREG_MAX];

	success = prom_getproperty(node, "ranges",
				   (अक्षर *) ranges,
				   माप(ranges));
	अगर (success != -1) अणु
		num_ranges = (success / माप(काष्ठा linux_prom_ranges));
		अगर (parent) अणु
			काष्ठा linux_prom_ranges parent_ranges[PROMREG_MAX];
			पूर्णांक num_parent_ranges;

			success = prom_getproperty(parent, "ranges",
						   (अक्षर *) parent_ranges,
						   माप(parent_ranges));
			अगर (success != -1) अणु
				num_parent_ranges = (success / माप(काष्ठा linux_prom_ranges));
				prom_adjust_ranges(ranges, num_ranges, parent_ranges, num_parent_ranges);
			पूर्ण
		पूर्ण
		prom_adjust_regs(regs, nregs, ranges, num_ranges);
	पूर्ण
पूर्ण
