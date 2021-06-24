<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Memory detection code
 */

#समावेश "boot.h"

#घोषणा SMAP	0x534d4150	/* ASCII "SMAP" */

अटल व्योम detect_memory_e820(व्योम)
अणु
	पूर्णांक count = 0;
	काष्ठा biosregs ireg, oreg;
	काष्ठा boot_e820_entry *desc = boot_params.e820_table;
	अटल काष्ठा boot_e820_entry buf; /* अटल so it is zeroed */

	initregs(&ireg);
	ireg.ax  = 0xe820;
	ireg.cx  = माप(buf);
	ireg.edx = SMAP;
	ireg.di  = (माप_प्रकार)&buf;

	/*
	 * Note: at least one BIOS is known which assumes that the
	 * buffer poपूर्णांकed to by one e820 call is the same one as
	 * the previous call, and only changes modअगरied fields.  Thereक्रमe,
	 * we use a temporary buffer and copy the results entry by entry.
	 *
	 * This routine deliberately करोes not try to account क्रम
	 * ACPI 3+ extended attributes.  This is because there are
	 * BIOSes in the field which report zero क्रम the valid bit क्रम
	 * all ranges, and we करोn't currently make any use of the
	 * other attribute bits.  Revisit this अगर we see the extended
	 * attribute bits deployed in a meaningful way in the future.
	 */

	करो अणु
		पूर्णांकcall(0x15, &ireg, &oreg);
		ireg.ebx = oreg.ebx; /* क्रम next iteration... */

		/* BIOSes which terminate the chain with CF = 1 as opposed
		   to %ebx = 0 करोn't always report the SMAP signature on
		   the final, failing, probe. */
		अगर (oreg.eflags & X86_EFLAGS_CF)
			अवरोध;

		/* Some BIOSes stop वापसing SMAP in the middle of
		   the search loop.  We करोn't know exactly how the BIOS
		   screwed up the map at that poपूर्णांक, we might have a
		   partial map, the full map, or complete garbage, so
		   just वापस failure. */
		अगर (oreg.eax != SMAP) अणु
			count = 0;
			अवरोध;
		पूर्ण

		*desc++ = buf;
		count++;
	पूर्ण जबतक (ireg.ebx && count < ARRAY_SIZE(boot_params.e820_table));

	boot_params.e820_entries = count;
पूर्ण

अटल व्योम detect_memory_e801(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ax = 0xe801;
	पूर्णांकcall(0x15, &ireg, &oreg);

	अगर (oreg.eflags & X86_EFLAGS_CF)
		वापस;

	/* Do we really need to करो this? */
	अगर (oreg.cx || oreg.dx) अणु
		oreg.ax = oreg.cx;
		oreg.bx = oreg.dx;
	पूर्ण

	अगर (oreg.ax > 15*1024) अणु
		वापस;	/* Bogus! */
	पूर्ण अन्यथा अगर (oreg.ax == 15*1024) अणु
		boot_params.alt_mem_k = (oreg.bx << 6) + oreg.ax;
	पूर्ण अन्यथा अणु
		/*
		 * This ignores memory above 16MB अगर we have a memory
		 * hole there.  If someone actually finds a machine
		 * with a memory hole at 16MB and no support क्रम
		 * 0E820h they should probably generate a fake e820
		 * map.
		 */
		boot_params.alt_mem_k = oreg.ax;
	पूर्ण
पूर्ण

अटल व्योम detect_memory_88(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ah = 0x88;
	पूर्णांकcall(0x15, &ireg, &oreg);

	boot_params.screen_info.ext_mem_k = oreg.ax;
पूर्ण

व्योम detect_memory(व्योम)
अणु
	detect_memory_e820();

	detect_memory_e801();

	detect_memory_88();
पूर्ण
