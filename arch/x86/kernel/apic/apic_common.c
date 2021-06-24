<शैली गुरु>
/*
 * Common functions shared between the various APIC flavours
 *
 * SPDX-License-Identअगरier: GPL-2.0
 */
#समावेश <linux/irq.h>
#समावेश <यंत्र/apic.h>

u32 apic_शेष_calc_apicid(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu(x86_cpu_to_apicid, cpu);
पूर्ण

u32 apic_flat_calc_apicid(अचिन्हित पूर्णांक cpu)
अणु
	वापस 1U << cpu;
पूर्ण

bool शेष_check_apicid_used(physid_mask_t *map, पूर्णांक apicid)
अणु
	वापस physid_isset(apicid, *map);
पूर्ण

व्योम शेष_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *reपंचांगap)
अणु
	*reपंचांगap = *phys_map;
पूर्ण

पूर्णांक शेष_cpu_present_to_apicid(पूर्णांक mps_cpu)
अणु
	अगर (mps_cpu < nr_cpu_ids && cpu_present(mps_cpu))
		वापस (पूर्णांक)per_cpu(x86_bios_cpu_apicid, mps_cpu);
	अन्यथा
		वापस BAD_APICID;
पूर्ण
EXPORT_SYMBOL_GPL(शेष_cpu_present_to_apicid);

पूर्णांक शेष_check_phys_apicid_present(पूर्णांक phys_apicid)
अणु
	वापस physid_isset(phys_apicid, phys_cpu_present_map);
पूर्ण

पूर्णांक शेष_apic_id_valid(u32 apicid)
अणु
	वापस (apicid < 255);
पूर्ण
