<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MPSPEC_H
#घोषणा _ASM_X86_MPSPEC_H


#समावेश <यंत्र/mpspec_def.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/apicdef.h>

बाह्य पूर्णांक pic_mode;

#अगर_घोषित CONFIG_X86_32

/*
 * Summit or generic (i.e. installer) kernels need lots of bus entries.
 * Maximum 256 PCI busses, plus 1 ISA bus in each of 4 cabinets.
 */
#अगर CONFIG_BASE_SMALL == 0
# define MAX_MP_BUSSES		260
#अन्यथा
# define MAX_MP_BUSSES		32
#पूर्ण_अगर

#घोषणा MAX_IRQ_SOURCES		256

बाह्य अचिन्हित पूर्णांक def_to_bigsmp;

#अन्यथा /* CONFIG_X86_64: */

#घोषणा MAX_MP_BUSSES		256
/* Each PCI slot may be a combo card with its own bus.  4 IRQ pins per slot. */
#घोषणा MAX_IRQ_SOURCES		(MAX_MP_BUSSES * 4)

#पूर्ण_अगर /* CONFIG_X86_64 */

#अगर_घोषित CONFIG_EISA
बाह्य पूर्णांक mp_bus_id_to_type[MAX_MP_BUSSES];
#पूर्ण_अगर

बाह्य DECLARE_BITMAP(mp_bus_not_pci, MAX_MP_BUSSES);

बाह्य अचिन्हित पूर्णांक boot_cpu_physical_apicid;
बाह्य u8 boot_cpu_apic_version;
बाह्य अचिन्हित दीर्घ mp_lapic_addr;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
बाह्य पूर्णांक smp_found_config;
#अन्यथा
# define smp_found_config 0
#पूर्ण_अगर

अटल अंतरभूत व्योम get_smp_config(व्योम)
अणु
	x86_init.mpparse.get_smp_config(0);
पूर्ण

अटल अंतरभूत व्योम early_get_smp_config(व्योम)
अणु
	x86_init.mpparse.get_smp_config(1);
पूर्ण

अटल अंतरभूत व्योम find_smp_config(व्योम)
अणु
	x86_init.mpparse.find_smp_config();
पूर्ण

#अगर_घोषित CONFIG_X86_MPPARSE
बाह्य व्योम e820__memblock_alloc_reserved_mpc_new(व्योम);
बाह्य पूर्णांक enable_update_mptable;
बाह्य व्योम शेष_find_smp_config(व्योम);
बाह्य व्योम शेष_get_smp_config(अचिन्हित पूर्णांक early);
#अन्यथा
अटल अंतरभूत व्योम e820__memblock_alloc_reserved_mpc_new(व्योम) अणु पूर्ण
#घोषणा enable_update_mptable 0
#घोषणा शेष_find_smp_config x86_init_noop
#घोषणा शेष_get_smp_config x86_init_uपूर्णांक_noop
#पूर्ण_अगर

पूर्णांक generic_processor_info(पूर्णांक apicid, पूर्णांक version);

#घोषणा PHYSID_ARRAY_SIZE	BITS_TO_LONGS(MAX_LOCAL_APIC)

काष्ठा physid_mask अणु
	अचिन्हित दीर्घ mask[PHYSID_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा physid_mask physid_mask_t;

#घोषणा physid_set(physid, map)			set_bit(physid, (map).mask)
#घोषणा physid_clear(physid, map)		clear_bit(physid, (map).mask)
#घोषणा physid_isset(physid, map)		test_bit(physid, (map).mask)
#घोषणा physid_test_and_set(physid, map)			\
	test_and_set_bit(physid, (map).mask)

#घोषणा physids_and(dst, src1, src2)					\
	biपंचांगap_and((dst).mask, (src1).mask, (src2).mask, MAX_LOCAL_APIC)

#घोषणा physids_or(dst, src1, src2)					\
	biपंचांगap_or((dst).mask, (src1).mask, (src2).mask, MAX_LOCAL_APIC)

#घोषणा physids_clear(map)					\
	biपंचांगap_zero((map).mask, MAX_LOCAL_APIC)

#घोषणा physids_complement(dst, src)				\
	biपंचांगap_complement((dst).mask, (src).mask, MAX_LOCAL_APIC)

#घोषणा physids_empty(map)					\
	biपंचांगap_empty((map).mask, MAX_LOCAL_APIC)

#घोषणा physids_equal(map1, map2)				\
	biपंचांगap_equal((map1).mask, (map2).mask, MAX_LOCAL_APIC)

#घोषणा physids_weight(map)					\
	biपंचांगap_weight((map).mask, MAX_LOCAL_APIC)

#घोषणा physids_shअगरt_right(d, s, n)				\
	biपंचांगap_shअगरt_right((d).mask, (s).mask, n, MAX_LOCAL_APIC)

#घोषणा physids_shअगरt_left(d, s, n)				\
	biपंचांगap_shअगरt_left((d).mask, (s).mask, n, MAX_LOCAL_APIC)

अटल अंतरभूत अचिन्हित दीर्घ physids_coerce(physid_mask_t *map)
अणु
	वापस map->mask[0];
पूर्ण

अटल अंतरभूत व्योम physids_promote(अचिन्हित दीर्घ physids, physid_mask_t *map)
अणु
	physids_clear(*map);
	map->mask[0] = physids;
पूर्ण

अटल अंतरभूत व्योम physid_set_mask_of_physid(पूर्णांक physid, physid_mask_t *map)
अणु
	physids_clear(*map);
	physid_set(physid, *map);
पूर्ण

#घोषणा PHYSID_MASK_ALL		अणु अणु[0 ... PHYSID_ARRAY_SIZE-1] = ~0ULपूर्ण पूर्ण
#घोषणा PHYSID_MASK_NONE	अणु अणु[0 ... PHYSID_ARRAY_SIZE-1] = 0ULपूर्ण पूर्ण

बाह्य physid_mask_t phys_cpu_present_map;

#पूर्ण_अगर /* _ASM_X86_MPSPEC_H */
