<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Early init beक्रमe relocation
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

/*
 * We're called here very early in the boot.
 *
 * Note that the kernel may be running at an address which is dअगरferent
 * from the address that it was linked at, so we must use RELOC/PTRRELOC
 * to access अटल data (including strings).  -- paulus
 */
notrace अचिन्हित दीर्घ __init early_init(अचिन्हित दीर्घ dt_ptr)
अणु
	अचिन्हित दीर्घ kva, offset = reloc_offset();

	kva = *PTRRELOC(&kernstart_virt_addr);

	/* First zero the BSS */
	अगर (kva == KERNELBASE)
		स_रखो(PTRRELOC(&__bss_start), 0, __bss_stop - __bss_start);

	/*
	 * Identअगरy the CPU type and fix up code sections
	 * that depend on which cpu we have.
	 */
	identअगरy_cpu(offset, mfspr(SPRN_PVR));

	apply_feature_fixups();

	वापस kva + offset;
पूर्ण
