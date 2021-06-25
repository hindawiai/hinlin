<शैली गुरु>
/*
 * Support क्रम MicroBlaze PVR (processor version रेजिस्टर)
 *
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/exceptions.h>
#समावेश <यंत्र/pvr.h>
#समावेश <linux/irqflags.h>

/*
 * Until we get an assembler that knows about the pvr रेजिस्टरs,
 * this horrible cruft will have to करो.
 * That hardcoded opcode is mfs r3, rpvrNN
 */

#घोषणा get_single_pvr(pvrid, val)				\
अणु								\
	रेजिस्टर अचिन्हित पंचांगp __यंत्र__("r3");			\
	पंचांगp = 0x0;	/* Prevent warning about unused */	\
	__यंत्र__ __अस्थिर__ (					\
			"mfs	%0, rpvr" #pvrid ";"		\
			: "=r" (पंचांगp) : : "memory");		\
	val = पंचांगp;						\
पूर्ण

/*
 * Does the CPU support the PVR रेजिस्टर?
 * वापस value:
 * 0: no PVR
 * 1: simple PVR
 * 2: full PVR
 *
 * This must work on all CPU versions, including those beक्रमe the
 * PVR was even an option.
 */

पूर्णांक cpu_has_pvr(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित pvr0;

	local_save_flags(flags);

	/* PVR bit in MSR tells us अगर there is any support */
	अगर (!(flags & PVR_MSR_BIT))
		वापस 0;

	get_single_pvr(0, pvr0);
	pr_debug("%s: pvr0 is 0x%08x\n", __func__, pvr0);

	अगर (pvr0 & PVR0_PVR_FULL_MASK)
		वापस 1;

	/* क्रम partial PVR use अटल cpuinfo */
	वापस 2;
पूर्ण

व्योम get_pvr(काष्ठा pvr_s *p)
अणु
	get_single_pvr(0, p->pvr[0]);
	get_single_pvr(1, p->pvr[1]);
	get_single_pvr(2, p->pvr[2]);
	get_single_pvr(3, p->pvr[3]);
	get_single_pvr(4, p->pvr[4]);
	get_single_pvr(5, p->pvr[5]);
	get_single_pvr(6, p->pvr[6]);
	get_single_pvr(7, p->pvr[7]);
	get_single_pvr(8, p->pvr[8]);
	get_single_pvr(9, p->pvr[9]);
	get_single_pvr(10, p->pvr[10]);
	get_single_pvr(11, p->pvr[11]);
पूर्ण
