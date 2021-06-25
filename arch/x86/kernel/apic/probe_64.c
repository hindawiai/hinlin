<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2004 James Cleverकरोn, IBM.
 *
 * Generic APIC sub-arch probe layer.
 *
 * Hacked क्रम x86-64 by James Cleverकरोn from i386 architecture code by
 * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and
 * James Cleverकरोn.
 */
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/apic.h>

#समावेश "local.h"

/*
 * Check the APIC IDs in bios_cpu_apicid and choose the APIC mode.
 */
व्योम __init शेष_setup_apic_routing(व्योम)
अणु
	काष्ठा apic **drv;

	enable_IR_x2apic();

	क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
		अगर ((*drv)->probe && (*drv)->probe()) अणु
			अगर (apic != *drv) अणु
				apic = *drv;
				pr_info("Switched APIC routing to %s.\n",
					apic->name);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init शेष_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	काष्ठा apic **drv;

	क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
		अगर ((*drv)->acpi_madt_oem_check(oem_id, oem_table_id)) अणु
			अगर (apic != *drv) अणु
				apic = *drv;
				pr_info("Setting APIC routing to %s.\n",
					apic->name);
			पूर्ण
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
