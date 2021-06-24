<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV APIC functions (note: not an Intel compatible APIC)
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2007-2014 Silicon Graphics, Inc. All rights reserved.
 */
#समावेश <linux/crash_dump.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/memory.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/uv/uv_mmrs.h>
#समावेश <यंत्र/uv/uv_hub.h>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/apic.h>

अटल क्रमागत uv_प्रणाली_type	uv_प्रणाली_type;
अटल पूर्णांक			uv_hubbed_प्रणाली;
अटल पूर्णांक			uv_hubless_प्रणाली;
अटल u64			gru_start_paddr, gru_end_paddr;
अटल जोड़ uvh_apicid		uvh_apicid;
अटल पूर्णांक			uv_node_id;

/* Unpack AT/OEM/TABLE ID's to be शून्य terminated strings */
अटल u8 uv_archtype[UV_AT_SIZE + 1];
अटल u8 oem_id[ACPI_OEM_ID_SIZE + 1];
अटल u8 oem_table_id[ACPI_OEM_TABLE_ID_SIZE + 1];

/* Inक्रमmation derived from CPUID and some UV MMRs */
अटल काष्ठा अणु
	अचिन्हित पूर्णांक apicid_shअगरt;
	अचिन्हित पूर्णांक apicid_mask;
	अचिन्हित पूर्णांक socketid_shअगरt;	/* aka pnode_shअगरt क्रम UV2/3 */
	अचिन्हित पूर्णांक pnode_mask;
	अचिन्हित पूर्णांक nasid_shअगरt;
	अचिन्हित पूर्णांक gpa_shअगरt;
	अचिन्हित पूर्णांक gnode_shअगरt;
	अचिन्हित पूर्णांक m_skt;
	अचिन्हित पूर्णांक n_skt;
पूर्ण uv_cpuid;

अटल पूर्णांक uv_min_hub_revision_id;

अटल काष्ठा apic apic_x2apic_uv_x;
अटल काष्ठा uv_hub_info_s uv_hub_info_node0;

/* Set this to use hardware error handler instead of kernel panic: */
अटल पूर्णांक disable_uv_undefined_panic = 1;

अचिन्हित दीर्घ uv_undefined(अक्षर *str)
अणु
	अगर (likely(!disable_uv_undefined_panic))
		panic("UV: error: undefined MMR: %s\n", str);
	अन्यथा
		pr_crit("UV: error: undefined MMR: %s\n", str);

	/* Cause a machine fault: */
	वापस ~0ul;
पूर्ण
EXPORT_SYMBOL(uv_undefined);

अटल अचिन्हित दीर्घ __init uv_early_पढ़ो_mmr(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ val, *mmr;

	mmr = early_ioremap(UV_LOCAL_MMR_BASE | addr, माप(*mmr));
	val = *mmr;
	early_iounmap(mmr, माप(*mmr));

	वापस val;
पूर्ण

अटल अंतरभूत bool is_GRU_range(u64 start, u64 end)
अणु
	अगर (!gru_start_paddr)
		वापस false;

	वापस start >= gru_start_paddr && end <= gru_end_paddr;
पूर्ण

अटल bool uv_is_untracked_pat_range(u64 start, u64 end)
अणु
	वापस is_ISA_range(start, end) || is_GRU_range(start, end);
पूर्ण

अटल व्योम __init early_get_pnodeid(व्योम)
अणु
	पूर्णांक pnode;

	uv_cpuid.m_skt = 0;
	अगर (UVH_RH10_GAM_ADDR_MAP_CONFIG) अणु
		जोड़ uvh_rh10_gam_addr_map_config_u  m_n_config;

		m_n_config.v = uv_early_पढ़ो_mmr(UVH_RH10_GAM_ADDR_MAP_CONFIG);
		uv_cpuid.n_skt = m_n_config.s.n_skt;
		uv_cpuid.nasid_shअगरt = 0;
	पूर्ण अन्यथा अगर (UVH_RH_GAM_ADDR_MAP_CONFIG) अणु
		जोड़ uvh_rh_gam_addr_map_config_u  m_n_config;

	m_n_config.v = uv_early_पढ़ो_mmr(UVH_RH_GAM_ADDR_MAP_CONFIG);
		uv_cpuid.n_skt = m_n_config.s.n_skt;
		अगर (is_uv(UV3))
			uv_cpuid.m_skt = m_n_config.s3.m_skt;
		अगर (is_uv(UV2))
			uv_cpuid.m_skt = m_n_config.s2.m_skt;
		uv_cpuid.nasid_shअगरt = 1;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ GAM_ADDR_MAP_CONFIG = 0;

		WARN(GAM_ADDR_MAP_CONFIG == 0,
			"UV: WARN: GAM_ADDR_MAP_CONFIG is not available\n");
		uv_cpuid.n_skt = 0;
		uv_cpuid.nasid_shअगरt = 0;
	पूर्ण

	अगर (is_uv(UV4|UVY))
		uv_cpuid.gnode_shअगरt = 2; /* min partition is 4 sockets */

	uv_cpuid.pnode_mask = (1 << uv_cpuid.n_skt) - 1;
	pnode = (uv_node_id >> uv_cpuid.nasid_shअगरt) & uv_cpuid.pnode_mask;
	uv_cpuid.gpa_shअगरt = 46;	/* Default unless changed */

	pr_info("UV: n_skt:%d pnmsk:%x pn:%x\n",
		uv_cpuid.n_skt, uv_cpuid.pnode_mask, pnode);
पूर्ण

/* Running on a UV Hubbed प्रणाली, determine which UV Hub Type it is */
अटल पूर्णांक __init early_set_hub_type(व्योम)
अणु
	जोड़ uvh_node_id_u node_id;

	/*
	 * The NODE_ID MMR is always at offset 0.
	 * Contains the chip part # + revision.
	 * Node_id field started with 15 bits,
	 * ... now 7 but upper 8 are masked to 0.
	 * All blades/nodes have the same part # and hub revision.
	 */
	node_id.v = uv_early_पढ़ो_mmr(UVH_NODE_ID);
	uv_node_id = node_id.sx.node_id;

	चयन (node_id.s.part_number) अणु

	हाल UV5_HUB_PART_NUMBER:
		uv_min_hub_revision_id = node_id.s.revision
					 + UV5_HUB_REVISION_BASE;
		uv_hub_type_set(UV5);
		अवरोध;

	/* UV4/4A only have a revision dअगरference */
	हाल UV4_HUB_PART_NUMBER:
		uv_min_hub_revision_id = node_id.s.revision
					 + UV4_HUB_REVISION_BASE - 1;
		uv_hub_type_set(UV4);
		अगर (uv_min_hub_revision_id == UV4A_HUB_REVISION_BASE)
			uv_hub_type_set(UV4|UV4A);
		अवरोध;

	हाल UV3_HUB_PART_NUMBER:
	हाल UV3_HUB_PART_NUMBER_X:
		uv_min_hub_revision_id = node_id.s.revision
					 + UV3_HUB_REVISION_BASE;
		uv_hub_type_set(UV3);
		अवरोध;

	हाल UV2_HUB_PART_NUMBER:
	हाल UV2_HUB_PART_NUMBER_X:
		uv_min_hub_revision_id = node_id.s.revision
					 + UV2_HUB_REVISION_BASE - 1;
		uv_hub_type_set(UV2);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	pr_info("UV: part#:%x rev:%d rev_id:%d UVtype:0x%x\n",
		node_id.s.part_number, node_id.s.revision,
		uv_min_hub_revision_id, is_uv(~0));

	वापस 1;
पूर्ण

अटल व्योम __init uv_tsc_check_sync(व्योम)
अणु
	u64 mmr;
	पूर्णांक sync_state;
	पूर्णांक mmr_shअगरt;
	अक्षर *state;

	/* Dअगरferent वापसs from dअगरferent UV BIOS versions */
	mmr = uv_early_पढ़ो_mmr(UVH_TSC_SYNC_MMR);
	mmr_shअगरt =
		is_uv2_hub() ? UVH_TSC_SYNC_SHIFT_UV2K : UVH_TSC_SYNC_SHIFT;
	sync_state = (mmr >> mmr_shअगरt) & UVH_TSC_SYNC_MASK;

	/* Check अगर TSC is valid क्रम all sockets */
	चयन (sync_state) अणु
	हाल UVH_TSC_SYNC_VALID:
		state = "in sync";
		mark_tsc_async_resets("UV BIOS");
		अवरोध;

	/* If BIOS state unknown, करोn't करो anything */
	हाल UVH_TSC_SYNC_UNKNOWN:
		state = "unknown";
		अवरोध;

	/* Otherwise, BIOS indicates problem with TSC */
	शेष:
		state = "unstable";
		mark_tsc_unstable("UV BIOS");
		अवरोध;
	पूर्ण
	pr_info("UV: TSC sync state from BIOS:0%d(%s)\n", sync_state, state);
पूर्ण

/* Selector क्रम (4|4A|5) काष्ठाs */
#घोषणा uvxy_field(sname, field, undef) (	\
	is_uv(UV4A) ? sname.s4a.field :		\
	is_uv(UV4) ? sname.s4.field :		\
	is_uv(UV3) ? sname.s3.field :		\
	undef)

/* [Copied from arch/x86/kernel/cpu/topology.c:detect_extended_topology()] */

#घोषणा SMT_LEVEL			0	/* Leaf 0xb SMT level */
#घोषणा INVALID_TYPE			0	/* Leaf 0xb sub-leaf types */
#घोषणा SMT_TYPE			1
#घोषणा CORE_TYPE			2
#घोषणा LEAFB_SUBTYPE(ecx)		(((ecx) >> 8) & 0xff)
#घोषणा BITS_SHIFT_NEXT_LEVEL(eax)	((eax) & 0x1f)

अटल व्योम set_x2apic_bits(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx, sub_index;
	अचिन्हित पूर्णांक sid_shअगरt;

	cpuid(0, &eax, &ebx, &ecx, &edx);
	अगर (eax < 0xb) अणु
		pr_info("UV: CPU does not have CPUID.11\n");
		वापस;
	पूर्ण

	cpuid_count(0xb, SMT_LEVEL, &eax, &ebx, &ecx, &edx);
	अगर (ebx == 0 || (LEAFB_SUBTYPE(ecx) != SMT_TYPE)) अणु
		pr_info("UV: CPUID.11 not implemented\n");
		वापस;
	पूर्ण

	sid_shअगरt = BITS_SHIFT_NEXT_LEVEL(eax);
	sub_index = 1;
	करो अणु
		cpuid_count(0xb, sub_index, &eax, &ebx, &ecx, &edx);
		अगर (LEAFB_SUBTYPE(ecx) == CORE_TYPE) अणु
			sid_shअगरt = BITS_SHIFT_NEXT_LEVEL(eax);
			अवरोध;
		पूर्ण
		sub_index++;
	पूर्ण जबतक (LEAFB_SUBTYPE(ecx) != INVALID_TYPE);

	uv_cpuid.apicid_shअगरt	= 0;
	uv_cpuid.apicid_mask	= (~(-1 << sid_shअगरt));
	uv_cpuid.socketid_shअगरt = sid_shअगरt;
पूर्ण

अटल व्योम __init early_get_apic_socketid_shअगरt(व्योम)
अणु
	अगर (is_uv2_hub() || is_uv3_hub())
		uvh_apicid.v = uv_early_पढ़ो_mmr(UVH_APICID);

	set_x2apic_bits();

	pr_info("UV: apicid_shift:%d apicid_mask:0x%x\n", uv_cpuid.apicid_shअगरt, uv_cpuid.apicid_mask);
	pr_info("UV: socketid_shift:%d pnode_mask:0x%x\n", uv_cpuid.socketid_shअगरt, uv_cpuid.pnode_mask);
पूर्ण

अटल व्योम __init uv_stringअगरy(पूर्णांक len, अक्षर *to, अक्षर *from)
अणु
	/* Relies on 'to' being शून्य अक्षरs so result will be शून्य terminated */
	म_नकलन(to, from, len-1);

	/* Trim trailing spaces */
	(व्योम)strim(to);
पूर्ण

/* Find UV arch type entry in UVsystab */
अटल अचिन्हित दीर्घ __init early_find_archtype(काष्ठा uv_systab *st)
अणु
	पूर्णांक i;

	क्रम (i = 0; st->entry[i].type != UV_SYSTAB_TYPE_UNUSED; i++) अणु
		अचिन्हित दीर्घ ptr = st->entry[i].offset;

		अगर (!ptr)
			जारी;
		ptr += (अचिन्हित दीर्घ)st;
		अगर (st->entry[i].type == UV_SYSTAB_TYPE_ARCH_TYPE)
			वापस ptr;
	पूर्ण
	वापस 0;
पूर्ण

/* Validate UV arch type field in UVsystab */
अटल पूर्णांक __init decode_arch_type(अचिन्हित दीर्घ ptr)
अणु
	काष्ठा uv_arch_type_entry *uv_ate = (काष्ठा uv_arch_type_entry *)ptr;
	पूर्णांक n = म_माप(uv_ate->archtype);

	अगर (n > 0 && n < माप(uv_ate->archtype)) अणु
		pr_info("UV: UVarchtype received from BIOS\n");
		uv_stringअगरy(माप(uv_archtype), uv_archtype, uv_ate->archtype);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Determine अगर UV arch type entry might exist in UVsystab */
अटल पूर्णांक __init early_get_arch_type(व्योम)
अणु
	अचिन्हित दीर्घ uvst_physaddr, uvst_size, ptr;
	काष्ठा uv_systab *st;
	u32 rev;
	पूर्णांक ret;

	uvst_physaddr = get_uv_systab_phys(0);
	अगर (!uvst_physaddr)
		वापस 0;

	st = early_memremap_ro(uvst_physaddr, माप(काष्ठा uv_systab));
	अगर (!st) अणु
		pr_err("UV: Cannot access UVsystab, remap failed\n");
		वापस 0;
	पूर्ण

	rev = st->revision;
	अगर (rev < UV_SYSTAB_VERSION_UV5) अणु
		early_memunmap(st, माप(काष्ठा uv_systab));
		वापस 0;
	पूर्ण

	uvst_size = st->size;
	early_memunmap(st, माप(काष्ठा uv_systab));
	st = early_memremap_ro(uvst_physaddr, uvst_size);
	अगर (!st) अणु
		pr_err("UV: Cannot access UVarchtype, remap failed\n");
		वापस 0;
	पूर्ण

	ptr = early_find_archtype(st);
	अगर (!ptr) अणु
		early_memunmap(st, uvst_size);
		वापस 0;
	पूर्ण

	ret = decode_arch_type(ptr);
	early_memunmap(st, uvst_size);
	वापस ret;
पूर्ण

/* UV प्रणाली found, check which APIC MODE BIOS alपढ़ोy selected */
अटल व्योम __init early_set_apic_mode(व्योम)
अणु
	अगर (x2apic_enabled())
		uv_प्रणाली_type = UV_X2APIC;
	अन्यथा
		uv_प्रणाली_type = UV_LEGACY_APIC;
पूर्ण

अटल पूर्णांक __init uv_set_प्रणाली_type(अक्षर *_oem_id, अक्षर *_oem_table_id)
अणु
	/* Save OEM_ID passed from ACPI MADT */
	uv_stringअगरy(माप(oem_id), oem_id, _oem_id);

	/* Check अगर BIOS sent us a UVarchtype */
	अगर (!early_get_arch_type())

		/* If not use OEM ID क्रम UVarchtype */
		uv_stringअगरy(माप(uv_archtype), uv_archtype, oem_id);

	/* Check अगर not hubbed */
	अगर (म_भेदन(uv_archtype, "SGI", 3) != 0) अणु

		/* (Not hubbed), check अगर not hubless */
		अगर (म_भेदन(uv_archtype, "NSGI", 4) != 0)

			/* (Not hubless), not a UV */
			वापस 0;

		/* Is UV hubless प्रणाली */
		uv_hubless_प्रणाली = 0x01;

		/* UV5 Hubless */
		अगर (म_भेदन(uv_archtype, "NSGI5", 5) == 0)
			uv_hubless_प्रणाली |= 0x20;

		/* UV4 Hubless: CH */
		अन्यथा अगर (म_भेदन(uv_archtype, "NSGI4", 5) == 0)
			uv_hubless_प्रणाली |= 0x10;

		/* UV3 Hubless: UV300/MC990X w/o hub */
		अन्यथा
			uv_hubless_प्रणाली |= 0x8;

		/* Copy OEM Table ID */
		uv_stringअगरy(माप(oem_table_id), oem_table_id, _oem_table_id);

		pr_info("UV: OEM IDs %s/%s, SystemType %d, HUBLESS ID %x\n",
			oem_id, oem_table_id, uv_प्रणाली_type, uv_hubless_प्रणाली);

		वापस 0;
	पूर्ण

	अगर (numa_off) अणु
		pr_err("UV: NUMA is off, disabling UV support\n");
		वापस 0;
	पूर्ण

	/* Set hubbed type अगर true */
	uv_hub_info->hub_revision =
		!म_भेदन(uv_archtype, "SGI5", 4) ? UV5_HUB_REVISION_BASE :
		!म_भेदन(uv_archtype, "SGI4", 4) ? UV4_HUB_REVISION_BASE :
		!म_भेदन(uv_archtype, "SGI3", 4) ? UV3_HUB_REVISION_BASE :
		!म_भेद(uv_archtype, "SGI2") ? UV2_HUB_REVISION_BASE : 0;

	चयन (uv_hub_info->hub_revision) अणु
	हाल UV5_HUB_REVISION_BASE:
		uv_hubbed_प्रणाली = 0x21;
		uv_hub_type_set(UV5);
		अवरोध;

	हाल UV4_HUB_REVISION_BASE:
		uv_hubbed_प्रणाली = 0x11;
		uv_hub_type_set(UV4);
		अवरोध;

	हाल UV3_HUB_REVISION_BASE:
		uv_hubbed_प्रणाली = 0x9;
		uv_hub_type_set(UV3);
		अवरोध;

	हाल UV2_HUB_REVISION_BASE:
		uv_hubbed_प्रणाली = 0x5;
		uv_hub_type_set(UV2);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	/* Get UV hub chip part number & revision */
	early_set_hub_type();

	/* Other UV setup functions */
	early_set_apic_mode();
	early_get_pnodeid();
	early_get_apic_socketid_shअगरt();
	x86_platक्रमm.is_untracked_pat_range = uv_is_untracked_pat_range;
	x86_platक्रमm.nmi_init = uv_nmi_init;
	uv_tsc_check_sync();

	वापस 1;
पूर्ण

/* Called early to probe क्रम the correct APIC driver */
अटल पूर्णांक __init uv_acpi_madt_oem_check(अक्षर *_oem_id, अक्षर *_oem_table_id)
अणु
	/* Set up early hub info fields क्रम Node 0 */
	uv_cpu_info->p_uv_hub_info = &uv_hub_info_node0;

	/* If not UV, वापस. */
	अगर (uv_set_प्रणाली_type(_oem_id, _oem_table_id) == 0)
		वापस 0;

	/* Save क्रम display of the OEM Table ID */
	uv_stringअगरy(माप(oem_table_id), oem_table_id, _oem_table_id);

	pr_info("UV: OEM IDs %s/%s, System/UVType %d/0x%x, HUB RevID %d\n",
		oem_id, oem_table_id, uv_प्रणाली_type, is_uv(UV_ANY),
		uv_min_hub_revision_id);

	वापस 0;
पूर्ण

क्रमागत uv_प्रणाली_type get_uv_प्रणाली_type(व्योम)
अणु
	वापस uv_प्रणाली_type;
पूर्ण

पूर्णांक uv_get_hubless_प्रणाली(व्योम)
अणु
	वापस uv_hubless_प्रणाली;
पूर्ण
EXPORT_SYMBOL_GPL(uv_get_hubless_प्रणाली);

sमाप_प्रकार uv_get_archtype(अक्षर *buf, पूर्णांक len)
अणु
	वापस scnम_लिखो(buf, len, "%s/%s", uv_archtype, oem_table_id);
पूर्ण
EXPORT_SYMBOL_GPL(uv_get_archtype);

पूर्णांक is_uv_प्रणाली(व्योम)
अणु
	वापस uv_प्रणाली_type != UV_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(is_uv_प्रणाली);

पूर्णांक is_uv_hubbed(पूर्णांक uvtype)
अणु
	वापस (uv_hubbed_प्रणाली & uvtype);
पूर्ण
EXPORT_SYMBOL_GPL(is_uv_hubbed);

अटल पूर्णांक is_uv_hubless(पूर्णांक uvtype)
अणु
	वापस (uv_hubless_प्रणाली & uvtype);
पूर्ण

व्योम **__uv_hub_info_list;
EXPORT_SYMBOL_GPL(__uv_hub_info_list);

DEFINE_PER_CPU(काष्ठा uv_cpu_info_s, __uv_cpu_info);
EXPORT_PER_CPU_SYMBOL_GPL(__uv_cpu_info);

लघु uv_possible_blades;
EXPORT_SYMBOL_GPL(uv_possible_blades);

अचिन्हित दीर्घ sn_rtc_cycles_per_second;
EXPORT_SYMBOL(sn_rtc_cycles_per_second);

/* The following values are used क्रम the per node hub info काष्ठा */
अटल __initdata अचिन्हित लघु		*_node_to_pnode;
अटल __initdata अचिन्हित लघु		_min_socket, _max_socket;
अटल __initdata अचिन्हित लघु		_min_pnode, _max_pnode, _gr_table_len;
अटल __initdata काष्ठा uv_gam_range_entry	*uv_gre_table;
अटल __initdata काष्ठा uv_gam_parameters	*uv_gp_table;
अटल __initdata अचिन्हित लघु		*_socket_to_node;
अटल __initdata अचिन्हित लघु		*_socket_to_pnode;
अटल __initdata अचिन्हित लघु		*_pnode_to_socket;

अटल __initdata काष्ठा uv_gam_range_s		*_gr_table;

#घोषणा	SOCK_EMPTY	((अचिन्हित लघु)~0)

/* Default UV memory block size is 2GB */
अटल अचिन्हित दीर्घ mem_block_size __initdata = (2UL << 30);

/* Kernel parameter to specअगरy UV mem block size */
अटल पूर्णांक __init parse_mem_block_size(अक्षर *ptr)
अणु
	अचिन्हित दीर्घ size = memparse(ptr, शून्य);

	/* Size will be rounded करोwn by set_block_size() below */
	mem_block_size = size;
	वापस 0;
पूर्ण
early_param("uv_memblksize", parse_mem_block_size);

अटल __init पूर्णांक adj_blksize(u32 lgre)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)lgre << UV_GAM_RANGE_SHFT;
	अचिन्हित दीर्घ size;

	क्रम (size = mem_block_size; size > MIN_MEMORY_BLOCK_SIZE; size >>= 1)
		अगर (IS_ALIGNED(base, size))
			अवरोध;

	अगर (size >= mem_block_size)
		वापस 0;

	mem_block_size = size;
	वापस 1;
पूर्ण

अटल __init व्योम set_block_size(व्योम)
अणु
	अचिन्हित पूर्णांक order = ffs(mem_block_size);

	अगर (order) अणु
		/* adjust क्रम ffs वापस of 1..64 */
		set_memory_block_size_order(order - 1);
		pr_info("UV: mem_block_size set to 0x%lx\n", mem_block_size);
	पूर्ण अन्यथा अणु
		/* bad or zero value, शेष to 1UL << 31 (2GB) */
		pr_err("UV: mem_block_size error with 0x%lx\n", mem_block_size);
		set_memory_block_size_order(31);
	पूर्ण
पूर्ण

/* Build GAM range lookup table: */
अटल __init व्योम build_uv_gr_table(व्योम)
अणु
	काष्ठा uv_gam_range_entry *gre = uv_gre_table;
	काष्ठा uv_gam_range_s *grt;
	अचिन्हित दीर्घ last_limit = 0, ram_limit = 0;
	पूर्णांक bytes, i, sid, lsid = -1, indx = 0, lindx = -1;

	अगर (!gre)
		वापस;

	bytes = _gr_table_len * माप(काष्ठा uv_gam_range_s);
	grt = kzalloc(bytes, GFP_KERNEL);
	BUG_ON(!grt);
	_gr_table = grt;

	क्रम (; gre->type != UV_GAM_RANGE_TYPE_UNUSED; gre++) अणु
		अगर (gre->type == UV_GAM_RANGE_TYPE_HOLE) अणु
			अगर (!ram_limit) अणु
				/* Mark hole between RAM/non-RAM: */
				ram_limit = last_limit;
				last_limit = gre->limit;
				lsid++;
				जारी;
			पूर्ण
			last_limit = gre->limit;
			pr_info("UV: extra hole in GAM RE table @%d\n", (पूर्णांक)(gre - uv_gre_table));
			जारी;
		पूर्ण
		अगर (_max_socket < gre->sockid) अणु
			pr_err("UV: GAM table sockid(%d) too large(>%d) @%d\n", gre->sockid, _max_socket, (पूर्णांक)(gre - uv_gre_table));
			जारी;
		पूर्ण
		sid = gre->sockid - _min_socket;
		अगर (lsid < sid) अणु
			/* New range: */
			grt = &_gr_table[indx];
			grt->base = lindx;
			grt->nasid = gre->nasid;
			grt->limit = last_limit = gre->limit;
			lsid = sid;
			lindx = indx++;
			जारी;
		पूर्ण
		/* Update range: */
		अगर (lsid == sid && !ram_limit) अणु
			/* .. अगर contiguous: */
			अगर (grt->limit == last_limit) अणु
				grt->limit = last_limit = gre->limit;
				जारी;
			पूर्ण
		पूर्ण
		/* Non-contiguous RAM range: */
		अगर (!ram_limit) अणु
			grt++;
			grt->base = lindx;
			grt->nasid = gre->nasid;
			grt->limit = last_limit = gre->limit;
			जारी;
		पूर्ण
		/* Non-contiguous/non-RAM: */
		grt++;
		/* base is this entry */
		grt->base = grt - _gr_table;
		grt->nasid = gre->nasid;
		grt->limit = last_limit = gre->limit;
		lsid++;
	पूर्ण

	/* Shorten table अगर possible */
	grt++;
	i = grt - _gr_table;
	अगर (i < _gr_table_len) अणु
		व्योम *ret;

		bytes = i * माप(काष्ठा uv_gam_range_s);
		ret = kपुनः_स्मृति(_gr_table, bytes, GFP_KERNEL);
		अगर (ret) अणु
			_gr_table = ret;
			_gr_table_len = i;
		पूर्ण
	पूर्ण

	/* Display resultant GAM range table: */
	क्रम (i = 0, grt = _gr_table; i < _gr_table_len; i++, grt++) अणु
		अचिन्हित दीर्घ start, end;
		पूर्णांक gb = grt->base;

		start = gb < 0 ?  0 : (अचिन्हित दीर्घ)_gr_table[gb].limit << UV_GAM_RANGE_SHFT;
		end = (अचिन्हित दीर्घ)grt->limit << UV_GAM_RANGE_SHFT;

		pr_info("UV: GAM Range %2d %04x 0x%013lx-0x%013lx (%d)\n", i, grt->nasid, start, end, gb);
	पूर्ण
पूर्ण

अटल पूर्णांक uv_wakeup_secondary(पूर्णांक phys_apicid, अचिन्हित दीर्घ start_rip)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक pnode;

	pnode = uv_apicid_to_pnode(phys_apicid);

	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((start_rip << UVH_IPI_INT_VECTOR_SHFT) >> 12) |
	    APIC_DM_INIT;

	uv_ग_लिखो_global_mmr64(pnode, UVH_IPI_INT, val);

	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((start_rip << UVH_IPI_INT_VECTOR_SHFT) >> 12) |
	    APIC_DM_STARTUP;

	uv_ग_लिखो_global_mmr64(pnode, UVH_IPI_INT, val);

	वापस 0;
पूर्ण

अटल व्योम uv_send_IPI_one(पूर्णांक cpu, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ apicid = per_cpu(x86_cpu_to_apicid, cpu);
	पूर्णांक pnode = uv_apicid_to_pnode(apicid);
	अचिन्हित दीर्घ dmode, val;

	अगर (vector == NMI_VECTOR)
		dmode = APIC_DELIVERY_MODE_NMI;
	अन्यथा
		dmode = APIC_DELIVERY_MODE_FIXED;

	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
		(apicid << UVH_IPI_INT_APIC_ID_SHFT) |
		(dmode << UVH_IPI_INT_DELIVERY_MODE_SHFT) |
		(vector << UVH_IPI_INT_VECTOR_SHFT);

	uv_ग_लिखो_global_mmr64(pnode, UVH_IPI_INT, val);
पूर्ण

अटल व्योम uv_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		uv_send_IPI_one(cpu, vector);
पूर्ण

अटल व्योम uv_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		अगर (cpu != this_cpu)
			uv_send_IPI_one(cpu, vector);
	पूर्ण
पूर्ण

अटल व्योम uv_send_IPI_allbutself(पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu != this_cpu)
			uv_send_IPI_one(cpu, vector);
	पूर्ण
पूर्ण

अटल व्योम uv_send_IPI_all(पूर्णांक vector)
अणु
	uv_send_IPI_mask(cpu_online_mask, vector);
पूर्ण

अटल पूर्णांक uv_apic_id_valid(u32 apicid)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक uv_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस 1;
पूर्ण

अटल व्योम uv_init_apic_ldr(व्योम)
अणु
पूर्ण

अटल u32 apic_uv_calc_apicid(अचिन्हित पूर्णांक cpu)
अणु
	वापस apic_शेष_calc_apicid(cpu);
पूर्ण

अटल अचिन्हित पूर्णांक x2apic_get_apic_id(अचिन्हित दीर्घ id)
अणु
	वापस id;
पूर्ण

अटल u32 set_apic_id(अचिन्हित पूर्णांक id)
अणु
	वापस id;
पूर्ण

अटल अचिन्हित पूर्णांक uv_पढ़ो_apic_id(व्योम)
अणु
	वापस x2apic_get_apic_id(apic_पढ़ो(APIC_ID));
पूर्ण

अटल पूर्णांक uv_phys_pkg_id(पूर्णांक initial_apicid, पूर्णांक index_msb)
अणु
	वापस uv_पढ़ो_apic_id() >> index_msb;
पूर्ण

अटल व्योम uv_send_IPI_self(पूर्णांक vector)
अणु
	apic_ग_लिखो(APIC_SELF_IPI, vector);
पूर्ण

अटल पूर्णांक uv_probe(व्योम)
अणु
	वापस apic == &apic_x2apic_uv_x;
पूर्ण

अटल काष्ठा apic apic_x2apic_uv_x __ro_after_init = अणु

	.name				= "UV large system",
	.probe				= uv_probe,
	.acpi_madt_oem_check		= uv_acpi_madt_oem_check,
	.apic_id_valid			= uv_apic_id_valid,
	.apic_id_रेजिस्टरed		= uv_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= uv_init_apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= uv_phys_pkg_id,

	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= set_apic_id,

	.calc_dest_apicid		= apic_uv_calc_apicid,

	.send_IPI			= uv_send_IPI_one,
	.send_IPI_mask			= uv_send_IPI_mask,
	.send_IPI_mask_allbutself	= uv_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= uv_send_IPI_allbutself,
	.send_IPI_all			= uv_send_IPI_all,
	.send_IPI_self			= uv_send_IPI_self,

	.wakeup_secondary_cpu		= uv_wakeup_secondary,
	.inquire_remote_apic		= शून्य,

	.पढ़ो				= native_apic_msr_पढ़ो,
	.ग_लिखो				= native_apic_msr_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_msr_eoi_ग_लिखो,
	.icr_पढ़ो			= native_x2apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_x2apic_icr_ग_लिखो,
	.रुको_icr_idle			= native_x2apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= native_safe_x2apic_रुको_icr_idle,
पूर्ण;

#घोषणा	UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_LENGTH	3
#घोषणा DEST_SHIFT UVXH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG_DEST_BASE_SHFT

अटल __init व्योम get_lowmem_redirect(अचिन्हित दीर्घ *base, अचिन्हित दीर्घ *size)
अणु
	जोड़ uvh_rh_gam_alias_2_overlay_config_u alias;
	जोड़ uvh_rh_gam_alias_2_redirect_config_u redirect;
	अचिन्हित दीर्घ m_redirect;
	अचिन्हित दीर्घ m_overlay;
	पूर्णांक i;

	क्रम (i = 0; i < UVH_RH_GAM_ALIAS210_REसूचीECT_CONFIG_LENGTH; i++) अणु
		चयन (i) अणु
		हाल 0:
			m_redirect = UVH_RH_GAM_ALIAS_0_REसूचीECT_CONFIG;
			m_overlay  = UVH_RH_GAM_ALIAS_0_OVERLAY_CONFIG;
			अवरोध;
		हाल 1:
			m_redirect = UVH_RH_GAM_ALIAS_1_REसूचीECT_CONFIG;
			m_overlay  = UVH_RH_GAM_ALIAS_1_OVERLAY_CONFIG;
			अवरोध;
		हाल 2:
			m_redirect = UVH_RH_GAM_ALIAS_2_REसूचीECT_CONFIG;
			m_overlay  = UVH_RH_GAM_ALIAS_2_OVERLAY_CONFIG;
			अवरोध;
		पूर्ण
		alias.v = uv_पढ़ो_local_mmr(m_overlay);
		अगर (alias.s.enable && alias.s.base == 0) अणु
			*size = (1UL << alias.s.m_alias);
			redirect.v = uv_पढ़ो_local_mmr(m_redirect);
			*base = (अचिन्हित दीर्घ)redirect.s.dest_base << DEST_SHIFT;
			वापस;
		पूर्ण
	पूर्ण
	*base = *size = 0;
पूर्ण

क्रमागत map_type अणुmap_wb, map_ucपूर्ण;
अटल स्थिर अक्षर * स्थिर mt[] = अणु "WB", "UC" पूर्ण;

अटल __init व्योम map_high(अक्षर *id, अचिन्हित दीर्घ base, पूर्णांक pshअगरt, पूर्णांक bshअगरt, पूर्णांक max_pnode, क्रमागत map_type map_type)
अणु
	अचिन्हित दीर्घ bytes, paddr;

	paddr = base << pshअगरt;
	bytes = (1UL << bshअगरt) * (max_pnode + 1);
	अगर (!paddr) अणु
		pr_info("UV: Map %s_HI base address NULL\n", id);
		वापस;
	पूर्ण
	अगर (map_type == map_uc)
		init_extra_mapping_uc(paddr, bytes);
	अन्यथा
		init_extra_mapping_wb(paddr, bytes);

	pr_info("UV: Map %s_HI 0x%lx - 0x%lx %s (%d segments)\n",
		id, paddr, paddr + bytes, mt[map_type], max_pnode + 1);
पूर्ण

अटल __init व्योम map_gru_high(पूर्णांक max_pnode)
अणु
	जोड़ uvh_rh_gam_gru_overlay_config_u gru;
	अचिन्हित दीर्घ mask, base;
	पूर्णांक shअगरt;

	अगर (UVH_RH_GAM_GRU_OVERLAY_CONFIG) अणु
		gru.v = uv_पढ़ो_local_mmr(UVH_RH_GAM_GRU_OVERLAY_CONFIG);
		shअगरt = UVH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT;
		mask = UVH_RH_GAM_GRU_OVERLAY_CONFIG_BASE_MASK;
	पूर्ण अन्यथा अगर (UVH_RH10_GAM_GRU_OVERLAY_CONFIG) अणु
		gru.v = uv_पढ़ो_local_mmr(UVH_RH10_GAM_GRU_OVERLAY_CONFIG);
		shअगरt = UVH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_SHFT;
		mask = UVH_RH10_GAM_GRU_OVERLAY_CONFIG_BASE_MASK;
	पूर्ण अन्यथा अणु
		pr_err("UV: GRU unavailable (no MMR)\n");
		वापस;
	पूर्ण

	अगर (!gru.s.enable) अणु
		pr_info("UV: GRU disabled (by BIOS)\n");
		वापस;
	पूर्ण

	base = (gru.v & mask) >> shअगरt;
	map_high("GRU", base, shअगरt, shअगरt, max_pnode, map_wb);
	gru_start_paddr = ((u64)base << shअगरt);
	gru_end_paddr = gru_start_paddr + (1UL << shअगरt) * (max_pnode + 1);
पूर्ण

अटल __init व्योम map_mmr_high(पूर्णांक max_pnode)
अणु
	अचिन्हित दीर्घ base;
	पूर्णांक shअगरt;
	bool enable;

	अगर (UVH_RH10_GAM_MMR_OVERLAY_CONFIG) अणु
		जोड़ uvh_rh10_gam_mmr_overlay_config_u mmr;

		mmr.v = uv_पढ़ो_local_mmr(UVH_RH10_GAM_MMR_OVERLAY_CONFIG);
		enable = mmr.s.enable;
		base = mmr.s.base;
		shअगरt = UVH_RH10_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT;
	पूर्ण अन्यथा अगर (UVH_RH_GAM_MMR_OVERLAY_CONFIG) अणु
		जोड़ uvh_rh_gam_mmr_overlay_config_u mmr;

		mmr.v = uv_पढ़ो_local_mmr(UVH_RH_GAM_MMR_OVERLAY_CONFIG);
		enable = mmr.s.enable;
		base = mmr.s.base;
		shअगरt = UVH_RH_GAM_MMR_OVERLAY_CONFIG_BASE_SHFT;
	पूर्ण अन्यथा अणु
		pr_err("UV:%s:RH_GAM_MMR_OVERLAY_CONFIG MMR undefined?\n",
			__func__);
		वापस;
	पूर्ण

	अगर (enable)
		map_high("MMR", base, shअगरt, shअगरt, max_pnode, map_uc);
	अन्यथा
		pr_info("UV: MMR disabled\n");
पूर्ण

/* Arch specअगरic ENUM हालs */
क्रमागत mmioh_arch अणु
	UV2_MMIOH = -1,
	UVY_MMIOH0, UVY_MMIOH1,
	UVX_MMIOH0, UVX_MMIOH1,
पूर्ण;

/* Calculate and Map MMIOH Regions */
अटल व्योम __init calc_mmioh_map(क्रमागत mmioh_arch index,
	पूर्णांक min_pnode, पूर्णांक max_pnode,
	पूर्णांक shअगरt, अचिन्हित दीर्घ base, पूर्णांक m_io, पूर्णांक n_io)
अणु
	अचिन्हित दीर्घ mmr, nasid_mask;
	पूर्णांक nasid, min_nasid, max_nasid, lnasid, mapped;
	पूर्णांक i, fi, li, n, max_io;
	अक्षर id[8];

	/* One (UV2) mapping */
	अगर (index == UV2_MMIOH) अणु
		म_नकलन(id, "MMIOH", माप(id));
		max_io = max_pnode;
		mapped = 0;
		जाओ map_निकास;
	पूर्ण

	/* small and large MMIOH mappings */
	चयन (index) अणु
	हाल UVY_MMIOH0:
		mmr = UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0;
		nasid_mask = UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK;
		n = UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG0_DEPTH;
		min_nasid = min_pnode;
		max_nasid = max_pnode;
		mapped = 1;
		अवरोध;
	हाल UVY_MMIOH1:
		mmr = UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1;
		nasid_mask = UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK;
		n = UVH_RH10_GAM_MMIOH_REसूचीECT_CONFIG1_DEPTH;
		min_nasid = min_pnode;
		max_nasid = max_pnode;
		mapped = 1;
		अवरोध;
	हाल UVX_MMIOH0:
		mmr = UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG0;
		nasid_mask = UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_MASK;
		n = UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG0_DEPTH;
		min_nasid = min_pnode * 2;
		max_nasid = max_pnode * 2;
		mapped = 1;
		अवरोध;
	हाल UVX_MMIOH1:
		mmr = UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG1;
		nasid_mask = UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_MASK;
		n = UVH_RH_GAM_MMIOH_REसूचीECT_CONFIG1_DEPTH;
		min_nasid = min_pnode * 2;
		max_nasid = max_pnode * 2;
		mapped = 1;
		अवरोध;
	शेष:
		pr_err("UV:%s:Invalid mapping type:%d\n", __func__, index);
		वापस;
	पूर्ण

	/* क्रमागत values chosen so (index mod 2) is MMIOH 0/1 (low/high) */
	snम_लिखो(id, माप(id), "MMIOH%d", index%2);

	max_io = lnasid = fi = li = -1;
	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित दीर्घ m_redirect = mmr + i * 8;
		अचिन्हित दीर्घ redirect = uv_पढ़ो_local_mmr(m_redirect);

		nasid = redirect & nasid_mask;
		अगर (i == 0)
			pr_info("UV: %s redirect base 0x%lx(@0x%lx) 0x%04x\n",
				id, redirect, m_redirect, nasid);

		/* Invalid NASID check */
		अगर (nasid < min_nasid || max_nasid < nasid) अणु
			pr_err("UV:%s:Invalid NASID:%x (range:%x..%x)\n",
				__func__, index, min_nasid, max_nasid);
			nasid = -1;
		पूर्ण

		अगर (nasid == lnasid) अणु
			li = i;
			/* Last entry check: */
			अगर (i != n-1)
				जारी;
		पूर्ण

		/* Check अगर we have a cached (or last) redirect to prपूर्णांक: */
		अगर (lnasid != -1 || (i == n-1 && nasid != -1))  अणु
			अचिन्हित दीर्घ addr1, addr2;
			पूर्णांक f, l;

			अगर (lnasid == -1) अणु
				f = l = i;
				lnasid = nasid;
			पूर्ण अन्यथा अणु
				f = fi;
				l = li;
			पूर्ण
			addr1 = (base << shअगरt) + f * (1ULL << m_io);
			addr2 = (base << shअगरt) + (l + 1) * (1ULL << m_io);
			pr_info("UV: %s[%03d..%03d] NASID 0x%04x ADDR 0x%016lx - 0x%016lx\n",
				id, fi, li, lnasid, addr1, addr2);
			अगर (max_io < l)
				max_io = l;
		पूर्ण
		fi = li = i;
		lnasid = nasid;
	पूर्ण

map_निकास:
	pr_info("UV: %s base:0x%lx shift:%d m_io:%d max_io:%d max_pnode:0x%x\n",
		id, base, shअगरt, m_io, max_io, max_pnode);

	अगर (max_io >= 0 && !mapped)
		map_high(id, base, shअगरt, m_io, max_io, map_uc);
पूर्ण

अटल __init व्योम map_mmioh_high(पूर्णांक min_pnode, पूर्णांक max_pnode)
अणु
	/* UVY flavor */
	अगर (UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0) अणु
		जोड़ uvh_rh10_gam_mmioh_overlay_config0_u mmioh0;
		जोड़ uvh_rh10_gam_mmioh_overlay_config1_u mmioh1;

		mmioh0.v = uv_पढ़ो_local_mmr(UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0);
		अगर (unlikely(mmioh0.s.enable == 0))
			pr_info("UV: MMIOH0 disabled\n");
		अन्यथा
			calc_mmioh_map(UVY_MMIOH0, min_pnode, max_pnode,
				UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT,
				mmioh0.s.base, mmioh0.s.m_io, mmioh0.s.n_io);

		mmioh1.v = uv_पढ़ो_local_mmr(UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1);
		अगर (unlikely(mmioh1.s.enable == 0))
			pr_info("UV: MMIOH1 disabled\n");
		अन्यथा
			calc_mmioh_map(UVY_MMIOH1, min_pnode, max_pnode,
				UVH_RH10_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT,
				mmioh1.s.base, mmioh1.s.m_io, mmioh1.s.n_io);
		वापस;
	पूर्ण
	/* UVX flavor */
	अगर (UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0) अणु
		जोड़ uvh_rh_gam_mmioh_overlay_config0_u mmioh0;
		जोड़ uvh_rh_gam_mmioh_overlay_config1_u mmioh1;

		mmioh0.v = uv_पढ़ो_local_mmr(UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0);
		अगर (unlikely(mmioh0.s.enable == 0))
			pr_info("UV: MMIOH0 disabled\n");
		अन्यथा अणु
			अचिन्हित दीर्घ base = uvxy_field(mmioh0, base, 0);
			पूर्णांक m_io = uvxy_field(mmioh0, m_io, 0);
			पूर्णांक n_io = uvxy_field(mmioh0, n_io, 0);

			calc_mmioh_map(UVX_MMIOH0, min_pnode, max_pnode,
				UVH_RH_GAM_MMIOH_OVERLAY_CONFIG0_BASE_SHFT,
				base, m_io, n_io);
		पूर्ण

		mmioh1.v = uv_पढ़ो_local_mmr(UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1);
		अगर (unlikely(mmioh1.s.enable == 0))
			pr_info("UV: MMIOH1 disabled\n");
		अन्यथा अणु
			अचिन्हित दीर्घ base = uvxy_field(mmioh1, base, 0);
			पूर्णांक m_io = uvxy_field(mmioh1, m_io, 0);
			पूर्णांक n_io = uvxy_field(mmioh1, n_io, 0);

			calc_mmioh_map(UVX_MMIOH1, min_pnode, max_pnode,
				UVH_RH_GAM_MMIOH_OVERLAY_CONFIG1_BASE_SHFT,
				base, m_io, n_io);
		पूर्ण
		वापस;
	पूर्ण

	/* UV2 flavor */
	अगर (UVH_RH_GAM_MMIOH_OVERLAY_CONFIG) अणु
		जोड़ uvh_rh_gam_mmioh_overlay_config_u mmioh;

		mmioh.v	= uv_पढ़ो_local_mmr(UVH_RH_GAM_MMIOH_OVERLAY_CONFIG);
		अगर (unlikely(mmioh.s2.enable == 0))
			pr_info("UV: MMIOH disabled\n");
		अन्यथा
			calc_mmioh_map(UV2_MMIOH, min_pnode, max_pnode,
				UV2H_RH_GAM_MMIOH_OVERLAY_CONFIG_BASE_SHFT,
				mmioh.s2.base, mmioh.s2.m_io, mmioh.s2.n_io);
		वापस;
	पूर्ण
पूर्ण

अटल __init व्योम map_low_mmrs(व्योम)
अणु
	अगर (UV_GLOBAL_MMR32_BASE)
		init_extra_mapping_uc(UV_GLOBAL_MMR32_BASE, UV_GLOBAL_MMR32_SIZE);

	अगर (UV_LOCAL_MMR_BASE)
		init_extra_mapping_uc(UV_LOCAL_MMR_BASE, UV_LOCAL_MMR_SIZE);
पूर्ण

अटल __init व्योम uv_rtc_init(व्योम)
अणु
	दीर्घ status;
	u64 ticks_per_sec;

	status = uv_bios_freq_base(BIOS_FREQ_BASE_REALTIME_CLOCK, &ticks_per_sec);

	अगर (status != BIOS_STATUS_SUCCESS || ticks_per_sec < 100000) अणु
		pr_warn("UV: unable to determine platform RTC clock frequency, guessing.\n");

		/* BIOS gives wrong value क्रम घड़ी frequency, so guess: */
		sn_rtc_cycles_per_second = 1000000000000UL / 30000UL;
	पूर्ण अन्यथा अणु
		sn_rtc_cycles_per_second = ticks_per_sec;
	पूर्ण
पूर्ण

/* Direct Legacy VGA I/O traffic to designated IOH */
अटल पूर्णांक uv_set_vga_state(काष्ठा pci_dev *pdev, bool decode, अचिन्हित पूर्णांक command_bits, u32 flags)
अणु
	पूर्णांक करोमुख्य, bus, rc;

	अगर (!(flags & PCI_VGA_STATE_CHANGE_BRIDGE))
		वापस 0;

	अगर ((command_bits & PCI_COMMAND_IO) == 0)
		वापस 0;

	करोमुख्य = pci_करोमुख्य_nr(pdev->bus);
	bus = pdev->bus->number;

	rc = uv_bios_set_legacy_vga_target(decode, करोमुख्य, bus);

	वापस rc;
पूर्ण

/*
 * Called on each CPU to initialize the per_cpu UV data area.
 * FIXME: hotplug not supported yet
 */
व्योम uv_cpu_init(व्योम)
अणु
	/* CPU 0 initialization will be करोne via uv_प्रणाली_init. */
	अगर (smp_processor_id() == 0)
		वापस;

	uv_hub_info->nr_online_cpus++;
पूर्ण

काष्ठा mn अणु
	अचिन्हित अक्षर	m_val;
	अचिन्हित अक्षर	n_val;
	अचिन्हित अक्षर	m_shअगरt;
	अचिन्हित अक्षर	n_lshअगरt;
पूर्ण;

/* Initialize caller's MN काष्ठा and fill in values */
अटल व्योम get_mn(काष्ठा mn *mnp)
अणु
	स_रखो(mnp, 0, माप(*mnp));
	mnp->n_val	= uv_cpuid.n_skt;
	अगर (is_uv(UV4|UVY)) अणु
		mnp->m_val	= 0;
		mnp->n_lshअगरt	= 0;
	पूर्ण अन्यथा अगर (is_uv3_hub()) अणु
		जोड़ uvyh_gr0_gam_gr_config_u m_gr_config;

		mnp->m_val	= uv_cpuid.m_skt;
		m_gr_config.v	= uv_पढ़ो_local_mmr(UVH_GR0_GAM_GR_CONFIG);
		mnp->n_lshअगरt	= m_gr_config.s3.m_skt;
	पूर्ण अन्यथा अगर (is_uv2_hub()) अणु
		mnp->m_val	= uv_cpuid.m_skt;
		mnp->n_lshअगरt	= mnp->m_val == 40 ? 40 : 39;
	पूर्ण
	mnp->m_shअगरt = mnp->m_val ? 64 - mnp->m_val : 0;
पूर्ण

अटल व्योम __init uv_init_hub_info(काष्ठा uv_hub_info_s *hi)
अणु
	काष्ठा mn mn;

	get_mn(&mn);
	hi->gpa_mask = mn.m_val ?
		(1UL << (mn.m_val + mn.n_val)) - 1 :
		(1UL << uv_cpuid.gpa_shअगरt) - 1;

	hi->m_val		= mn.m_val;
	hi->n_val		= mn.n_val;
	hi->m_shअगरt		= mn.m_shअगरt;
	hi->n_lshअगरt		= mn.n_lshअगरt ? mn.n_lshअगरt : 0;
	hi->hub_revision	= uv_hub_info->hub_revision;
	hi->hub_type		= uv_hub_info->hub_type;
	hi->pnode_mask		= uv_cpuid.pnode_mask;
	hi->nasid_shअगरt		= uv_cpuid.nasid_shअगरt;
	hi->min_pnode		= _min_pnode;
	hi->min_socket		= _min_socket;
	hi->pnode_to_socket	= _pnode_to_socket;
	hi->socket_to_node	= _socket_to_node;
	hi->socket_to_pnode	= _socket_to_pnode;
	hi->gr_table_len	= _gr_table_len;
	hi->gr_table		= _gr_table;

	uv_cpuid.gnode_shअगरt	= max_t(अचिन्हित पूर्णांक, uv_cpuid.gnode_shअगरt, mn.n_val);
	hi->gnode_extra		= (uv_node_id & ~((1 << uv_cpuid.gnode_shअगरt) - 1)) >> 1;
	अगर (mn.m_val)
		hi->gnode_upper	= (u64)hi->gnode_extra << mn.m_val;

	अगर (uv_gp_table) अणु
		hi->global_mmr_base	= uv_gp_table->mmr_base;
		hi->global_mmr_shअगरt	= uv_gp_table->mmr_shअगरt;
		hi->global_gru_base	= uv_gp_table->gru_base;
		hi->global_gru_shअगरt	= uv_gp_table->gru_shअगरt;
		hi->gpa_shअगरt		= uv_gp_table->gpa_shअगरt;
		hi->gpa_mask		= (1UL << hi->gpa_shअगरt) - 1;
	पूर्ण अन्यथा अणु
		hi->global_mmr_base	=
			uv_पढ़ो_local_mmr(UVH_RH_GAM_MMR_OVERLAY_CONFIG) &
			~UV_MMR_ENABLE;
		hi->global_mmr_shअगरt	= _UV_GLOBAL_MMR64_PNODE_SHIFT;
	पूर्ण

	get_lowmem_redirect(&hi->lowmem_remap_base, &hi->lowmem_remap_top);

	hi->apic_pnode_shअगरt = uv_cpuid.socketid_shअगरt;

	/* Show प्रणाली specअगरic info: */
	pr_info("UV: N:%d M:%d m_shift:%d n_lshift:%d\n", hi->n_val, hi->m_val, hi->m_shअगरt, hi->n_lshअगरt);
	pr_info("UV: gpa_mask/shift:0x%lx/%d pnode_mask:0x%x apic_pns:%d\n", hi->gpa_mask, hi->gpa_shअगरt, hi->pnode_mask, hi->apic_pnode_shअगरt);
	pr_info("UV: mmr_base/shift:0x%lx/%ld\n", hi->global_mmr_base, hi->global_mmr_shअगरt);
	अगर (hi->global_gru_base)
		pr_info("UV: gru_base/shift:0x%lx/%ld\n",
			hi->global_gru_base, hi->global_gru_shअगरt);

	pr_info("UV: gnode_upper:0x%lx gnode_extra:0x%x\n", hi->gnode_upper, hi->gnode_extra);
पूर्ण

अटल व्योम __init decode_gam_params(अचिन्हित दीर्घ ptr)
अणु
	uv_gp_table = (काष्ठा uv_gam_parameters *)ptr;

	pr_info("UV: GAM Params...\n");
	pr_info("UV: mmr_base/shift:0x%llx/%d gru_base/shift:0x%llx/%d gpa_shift:%d\n",
		uv_gp_table->mmr_base, uv_gp_table->mmr_shअगरt,
		uv_gp_table->gru_base, uv_gp_table->gru_shअगरt,
		uv_gp_table->gpa_shअगरt);
पूर्ण

अटल व्योम __init decode_gam_rng_tbl(अचिन्हित दीर्घ ptr)
अणु
	काष्ठा uv_gam_range_entry *gre = (काष्ठा uv_gam_range_entry *)ptr;
	अचिन्हित दीर्घ lgre = 0;
	पूर्णांक index = 0;
	पूर्णांक sock_min = 999999, pnode_min = 99999;
	पूर्णांक sock_max = -1, pnode_max = -1;

	uv_gre_table = gre;
	क्रम (; gre->type != UV_GAM_RANGE_TYPE_UNUSED; gre++) अणु
		अचिन्हित दीर्घ size = ((अचिन्हित दीर्घ)(gre->limit - lgre)
					<< UV_GAM_RANGE_SHFT);
		पूर्णांक order = 0;
		अक्षर suffix[] = " KMGTPE";
		पूर्णांक flag = ' ';

		जबतक (size > 9999 && order < माप(suffix)) अणु
			size /= 1024;
			order++;
		पूर्ण

		/* adjust max block size to current range start */
		अगर (gre->type == 1 || gre->type == 2)
			अगर (adj_blksize(lgre))
				flag = '*';

		अगर (!index) अणु
			pr_info("UV: GAM Range Table...\n");
			pr_info("UV:  # %20s %14s %6s %4s %5s %3s %2s\n", "Range", "", "Size", "Type", "NASID", "SID", "PN");
		पूर्ण
		pr_info("UV: %2d: 0x%014lx-0x%014lx%c %5lu%c %3d   %04x  %02x %02x\n",
			index++,
			(अचिन्हित दीर्घ)lgre << UV_GAM_RANGE_SHFT,
			(अचिन्हित दीर्घ)gre->limit << UV_GAM_RANGE_SHFT,
			flag, size, suffix[order],
			gre->type, gre->nasid, gre->sockid, gre->pnode);

		/* update to next range start */
		lgre = gre->limit;
		अगर (sock_min > gre->sockid)
			sock_min = gre->sockid;
		अगर (sock_max < gre->sockid)
			sock_max = gre->sockid;
		अगर (pnode_min > gre->pnode)
			pnode_min = gre->pnode;
		अगर (pnode_max < gre->pnode)
			pnode_max = gre->pnode;
	पूर्ण
	_min_socket	= sock_min;
	_max_socket	= sock_max;
	_min_pnode	= pnode_min;
	_max_pnode	= pnode_max;
	_gr_table_len	= index;

	pr_info("UV: GRT: %d entries, sockets(min:%x,max:%x) pnodes(min:%x,max:%x)\n", index, _min_socket, _max_socket, _min_pnode, _max_pnode);
पूर्ण

/* Walk through UVsystab decoding the fields */
अटल पूर्णांक __init decode_uv_systab(व्योम)
अणु
	काष्ठा uv_systab *st;
	पूर्णांक i;

	/* Get mapped UVsystab poपूर्णांकer */
	st = uv_systab;

	/* If UVsystab is version 1, there is no extended UVsystab */
	अगर (st && st->revision == UV_SYSTAB_VERSION_1)
		वापस 0;

	अगर ((!st) || (st->revision < UV_SYSTAB_VERSION_UV4_LATEST)) अणु
		पूर्णांक rev = st ? st->revision : 0;

		pr_err("UV: BIOS UVsystab mismatch, (%x < %x)\n",
			rev, UV_SYSTAB_VERSION_UV4_LATEST);
		pr_err("UV: Does not support UV, switch to non-UV x86_64\n");
		uv_प्रणाली_type = UV_NONE;

		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; st->entry[i].type != UV_SYSTAB_TYPE_UNUSED; i++) अणु
		अचिन्हित दीर्घ ptr = st->entry[i].offset;

		अगर (!ptr)
			जारी;

		/* poपूर्णांक to payload */
		ptr += (अचिन्हित दीर्घ)st;

		चयन (st->entry[i].type) अणु
		हाल UV_SYSTAB_TYPE_GAM_PARAMS:
			decode_gam_params(ptr);
			अवरोध;

		हाल UV_SYSTAB_TYPE_GAM_RNG_TBL:
			decode_gam_rng_tbl(ptr);
			अवरोध;

		हाल UV_SYSTAB_TYPE_ARCH_TYPE:
			/* alपढ़ोy processed in early startup */
			अवरोध;

		शेष:
			pr_err("UV:%s:Unrecognized UV_SYSTAB_TYPE:%d, skipped\n",
				__func__, st->entry[i].type);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Set up physical blade translations from UVH_NODE_PRESENT_TABLE */
अटल __init व्योम boot_init_possible_blades(काष्ठा uv_hub_info_s *hub_info)
अणु
	अचिन्हित दीर्घ np;
	पूर्णांक i, uv_pb = 0;

	अगर (UVH_NODE_PRESENT_TABLE) अणु
		pr_info("UV: NODE_PRESENT_DEPTH = %d\n",
			UVH_NODE_PRESENT_TABLE_DEPTH);
		क्रम (i = 0; i < UVH_NODE_PRESENT_TABLE_DEPTH; i++) अणु
			np = uv_पढ़ो_local_mmr(UVH_NODE_PRESENT_TABLE + i * 8);
			pr_info("UV: NODE_PRESENT(%d) = 0x%016lx\n", i, np);
			uv_pb += hweight64(np);
		पूर्ण
	पूर्ण
	अगर (UVH_NODE_PRESENT_0) अणु
		np = uv_पढ़ो_local_mmr(UVH_NODE_PRESENT_0);
		pr_info("UV: NODE_PRESENT_0 = 0x%016lx\n", np);
		uv_pb += hweight64(np);
	पूर्ण
	अगर (UVH_NODE_PRESENT_1) अणु
		np = uv_पढ़ो_local_mmr(UVH_NODE_PRESENT_1);
		pr_info("UV: NODE_PRESENT_1 = 0x%016lx\n", np);
		uv_pb += hweight64(np);
	पूर्ण
	अगर (uv_possible_blades != uv_pb)
		uv_possible_blades = uv_pb;

	pr_info("UV: number nodes/possible blades %d\n", uv_pb);
पूर्ण

अटल व्योम __init build_socket_tables(व्योम)
अणु
	काष्ठा uv_gam_range_entry *gre = uv_gre_table;
	पूर्णांक num, nump;
	पूर्णांक cpu, i, lnid;
	पूर्णांक minsock = _min_socket;
	पूर्णांक maxsock = _max_socket;
	पूर्णांक minpnode = _min_pnode;
	पूर्णांक maxpnode = _max_pnode;
	माप_प्रकार bytes;

	अगर (!gre) अणु
		अगर (is_uv2_hub() || is_uv3_hub()) अणु
			pr_info("UV: No UVsystab socket table, ignoring\n");
			वापस;
		पूर्ण
		pr_err("UV: Error: UVsystab address translations not available!\n");
		BUG();
	पूर्ण

	/* Build socket id -> node id, pnode */
	num = maxsock - minsock + 1;
	bytes = num * माप(_socket_to_node[0]);
	_socket_to_node = kदो_स्मृति(bytes, GFP_KERNEL);
	_socket_to_pnode = kदो_स्मृति(bytes, GFP_KERNEL);

	nump = maxpnode - minpnode + 1;
	bytes = nump * माप(_pnode_to_socket[0]);
	_pnode_to_socket = kदो_स्मृति(bytes, GFP_KERNEL);
	BUG_ON(!_socket_to_node || !_socket_to_pnode || !_pnode_to_socket);

	क्रम (i = 0; i < num; i++)
		_socket_to_node[i] = _socket_to_pnode[i] = SOCK_EMPTY;

	क्रम (i = 0; i < nump; i++)
		_pnode_to_socket[i] = SOCK_EMPTY;

	/* Fill in pnode/node/addr conversion list values: */
	pr_info("UV: GAM Building socket/pnode conversion tables\n");
	क्रम (; gre->type != UV_GAM_RANGE_TYPE_UNUSED; gre++) अणु
		अगर (gre->type == UV_GAM_RANGE_TYPE_HOLE)
			जारी;
		i = gre->sockid - minsock;
		/* Duplicate: */
		अगर (_socket_to_pnode[i] != SOCK_EMPTY)
			जारी;
		_socket_to_pnode[i] = gre->pnode;

		i = gre->pnode - minpnode;
		_pnode_to_socket[i] = gre->sockid;

		pr_info("UV: sid:%02x type:%d nasid:%04x pn:%02x pn2s:%2x\n",
			gre->sockid, gre->type, gre->nasid,
			_socket_to_pnode[gre->sockid - minsock],
			_pnode_to_socket[gre->pnode - minpnode]);
	पूर्ण

	/* Set socket -> node values: */
	lnid = NUMA_NO_NODE;
	क्रम_each_present_cpu(cpu) अणु
		पूर्णांक nid = cpu_to_node(cpu);
		पूर्णांक apicid, sockid;

		अगर (lnid == nid)
			जारी;
		lnid = nid;
		apicid = per_cpu(x86_cpu_to_apicid, cpu);
		sockid = apicid >> uv_cpuid.socketid_shअगरt;
		_socket_to_node[sockid - minsock] = nid;
		pr_info("UV: sid:%02x: apicid:%04x node:%2d\n",
			sockid, apicid, nid);
	पूर्ण

	/* Set up physical blade to pnode translation from GAM Range Table: */
	bytes = num_possible_nodes() * माप(_node_to_pnode[0]);
	_node_to_pnode = kदो_स्मृति(bytes, GFP_KERNEL);
	BUG_ON(!_node_to_pnode);

	क्रम (lnid = 0; lnid < num_possible_nodes(); lnid++) अणु
		अचिन्हित लघु sockid;

		क्रम (sockid = minsock; sockid <= maxsock; sockid++) अणु
			अगर (lnid == _socket_to_node[sockid - minsock]) अणु
				_node_to_pnode[lnid] = _socket_to_pnode[sockid - minsock];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (sockid > maxsock) अणु
			pr_err("UV: socket for node %d not found!\n", lnid);
			BUG();
		पूर्ण
	पूर्ण

	/*
	 * If socket id == pnode or socket id == node क्रम all nodes,
	 *   प्रणाली runs faster by removing corresponding conversion table.
	 */
	pr_info("UV: Checking socket->node/pnode for identity maps\n");
	अगर (minsock == 0) अणु
		क्रम (i = 0; i < num; i++)
			अगर (_socket_to_node[i] == SOCK_EMPTY || i != _socket_to_node[i])
				अवरोध;
		अगर (i >= num) अणु
			kमुक्त(_socket_to_node);
			_socket_to_node = शून्य;
			pr_info("UV: 1:1 socket_to_node table removed\n");
		पूर्ण
	पूर्ण
	अगर (minsock == minpnode) अणु
		क्रम (i = 0; i < num; i++)
			अगर (_socket_to_pnode[i] != SOCK_EMPTY &&
				_socket_to_pnode[i] != i + minpnode)
				अवरोध;
		अगर (i >= num) अणु
			kमुक्त(_socket_to_pnode);
			_socket_to_pnode = शून्य;
			pr_info("UV: 1:1 socket_to_pnode table removed\n");
		पूर्ण
	पूर्ण
पूर्ण

/* Check which reboot to use */
अटल व्योम check_efi_reboot(व्योम)
अणु
	/* If EFI reboot not available, use ACPI reboot */
	अगर (!efi_enabled(EFI_BOOT))
		reboot_type = BOOT_ACPI;
पूर्ण

/*
 * User proc fs file handling now deprecated.
 * Recommend using /sys/firmware/sgi_uv/... instead.
 */
अटल पूर्णांक __maybe_unused proc_hubbed_show(काष्ठा seq_file *file, व्योम *data)
अणु
	pr_notice_once("%s: using deprecated /proc/sgi_uv/hubbed, use /sys/firmware/sgi_uv/hub_type\n",
		       current->comm);
	seq_म_लिखो(file, "0x%x\n", uv_hubbed_प्रणाली);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused proc_hubless_show(काष्ठा seq_file *file, व्योम *data)
अणु
	pr_notice_once("%s: using deprecated /proc/sgi_uv/hubless, use /sys/firmware/sgi_uv/hubless\n",
		       current->comm);
	seq_म_लिखो(file, "0x%x\n", uv_hubless_प्रणाली);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused proc_archtype_show(काष्ठा seq_file *file, व्योम *data)
अणु
	pr_notice_once("%s: using deprecated /proc/sgi_uv/archtype, use /sys/firmware/sgi_uv/archtype\n",
		       current->comm);
	seq_म_लिखो(file, "%s/%s\n", uv_archtype, oem_table_id);
	वापस 0;
पूर्ण

अटल __init व्योम uv_setup_proc_files(पूर्णांक hubless)
अणु
	काष्ठा proc_dir_entry *pde;

	pde = proc_सूची_गढ़ो(UV_PROC_NODE, शून्य);
	proc_create_single("archtype", 0, pde, proc_archtype_show);
	अगर (hubless)
		proc_create_single("hubless", 0, pde, proc_hubless_show);
	अन्यथा
		proc_create_single("hubbed", 0, pde, proc_hubbed_show);
पूर्ण

/* Initialize UV hubless प्रणालीs */
अटल __init पूर्णांक uv_प्रणाली_init_hubless(व्योम)
अणु
	पूर्णांक rc;

	/* Setup PCH NMI handler */
	uv_nmi_setup_hubless();

	/* Init kernel/BIOS पूर्णांकerface */
	rc = uv_bios_init();
	अगर (rc < 0)
		वापस rc;

	/* Process UVsystab */
	rc = decode_uv_systab();
	अगर (rc < 0)
		वापस rc;

	/* Set section block size क्रम current node memory */
	set_block_size();

	/* Create user access node */
	अगर (rc >= 0)
		uv_setup_proc_files(1);

	check_efi_reboot();

	वापस rc;
पूर्ण

अटल व्योम __init uv_प्रणाली_init_hub(व्योम)
अणु
	काष्ठा uv_hub_info_s hub_info = अणु0पूर्ण;
	पूर्णांक bytes, cpu, nodeid;
	अचिन्हित लघु min_pnode = 9999, max_pnode = 0;
	अक्षर *hub = is_uv5_hub() ? "UV500" :
		    is_uv4_hub() ? "UV400" :
		    is_uv3_hub() ? "UV300" :
		    is_uv2_hub() ? "UV2000/3000" : शून्य;

	अगर (!hub) अणु
		pr_err("UV: Unknown/unsupported UV hub\n");
		वापस;
	पूर्ण
	pr_info("UV: Found %s hub\n", hub);

	map_low_mmrs();

	/* Get uv_systab क्रम decoding, setup UV BIOS calls */
	uv_bios_init();

	/* If there's an UVsystab problem then पात UV init: */
	अगर (decode_uv_systab() < 0) अणु
		pr_err("UV: Mangled UVsystab format\n");
		वापस;
	पूर्ण

	build_socket_tables();
	build_uv_gr_table();
	set_block_size();
	uv_init_hub_info(&hub_info);
	uv_possible_blades = num_possible_nodes();
	अगर (!_node_to_pnode)
		boot_init_possible_blades(&hub_info);

	/* uv_num_possible_blades() is really the hub count: */
	pr_info("UV: Found %d hubs, %d nodes, %d CPUs\n", uv_num_possible_blades(), num_possible_nodes(), num_possible_cpus());

	uv_bios_get_sn_info(0, &uv_type, &sn_partition_id, &sn_coherency_id, &sn_region_size, &प्रणाली_serial_number);
	hub_info.coherency_करोमुख्य_number = sn_coherency_id;
	uv_rtc_init();

	bytes = माप(व्योम *) * uv_num_possible_blades();
	__uv_hub_info_list = kzalloc(bytes, GFP_KERNEL);
	BUG_ON(!__uv_hub_info_list);

	bytes = माप(काष्ठा uv_hub_info_s);
	क्रम_each_node(nodeid) अणु
		काष्ठा uv_hub_info_s *new_hub;

		अगर (__uv_hub_info_list[nodeid]) अणु
			pr_err("UV: Node %d UV HUB already initialized!?\n", nodeid);
			BUG();
		पूर्ण

		/* Allocate new per hub info list */
		new_hub = (nodeid == 0) ?  &uv_hub_info_node0 : kzalloc_node(bytes, GFP_KERNEL, nodeid);
		BUG_ON(!new_hub);
		__uv_hub_info_list[nodeid] = new_hub;
		new_hub = uv_hub_info_list(nodeid);
		BUG_ON(!new_hub);
		*new_hub = hub_info;

		/* Use inक्रमmation from GAM table अगर available: */
		अगर (_node_to_pnode)
			new_hub->pnode = _node_to_pnode[nodeid];
		अन्यथा /* Or fill in during CPU loop: */
			new_hub->pnode = 0xffff;

		new_hub->numa_blade_id = uv_node_to_blade_id(nodeid);
		new_hub->memory_nid = NUMA_NO_NODE;
		new_hub->nr_possible_cpus = 0;
		new_hub->nr_online_cpus = 0;
	पूर्ण

	/* Initialize per CPU info: */
	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक apicid = per_cpu(x86_cpu_to_apicid, cpu);
		पूर्णांक numa_node_id;
		अचिन्हित लघु pnode;

		nodeid = cpu_to_node(cpu);
		numa_node_id = numa_cpu_node(cpu);
		pnode = uv_apicid_to_pnode(apicid);

		uv_cpu_info_per(cpu)->p_uv_hub_info = uv_hub_info_list(nodeid);
		uv_cpu_info_per(cpu)->blade_cpu_id = uv_cpu_hub_info(cpu)->nr_possible_cpus++;
		अगर (uv_cpu_hub_info(cpu)->memory_nid == NUMA_NO_NODE)
			uv_cpu_hub_info(cpu)->memory_nid = cpu_to_node(cpu);

		/* Init memoryless node: */
		अगर (nodeid != numa_node_id &&
		    uv_hub_info_list(numa_node_id)->pnode == 0xffff)
			uv_hub_info_list(numa_node_id)->pnode = pnode;
		अन्यथा अगर (uv_cpu_hub_info(cpu)->pnode == 0xffff)
			uv_cpu_hub_info(cpu)->pnode = pnode;
	पूर्ण

	क्रम_each_node(nodeid) अणु
		अचिन्हित लघु pnode = uv_hub_info_list(nodeid)->pnode;

		/* Add pnode info क्रम pre-GAM list nodes without CPUs: */
		अगर (pnode == 0xffff) अणु
			अचिन्हित दीर्घ paddr;

			paddr = node_start_pfn(nodeid) << PAGE_SHIFT;
			pnode = uv_gpa_to_pnode(uv_soc_phys_ram_to_gpa(paddr));
			uv_hub_info_list(nodeid)->pnode = pnode;
		पूर्ण
		min_pnode = min(pnode, min_pnode);
		max_pnode = max(pnode, max_pnode);
		pr_info("UV: UVHUB node:%2d pn:%02x nrcpus:%d\n",
			nodeid,
			uv_hub_info_list(nodeid)->pnode,
			uv_hub_info_list(nodeid)->nr_possible_cpus);
	पूर्ण

	pr_info("UV: min_pnode:%02x max_pnode:%02x\n", min_pnode, max_pnode);
	map_gru_high(max_pnode);
	map_mmr_high(max_pnode);
	map_mmioh_high(min_pnode, max_pnode);

	uv_nmi_setup();
	uv_cpu_init();
	uv_setup_proc_files(0);

	/* Register Legacy VGA I/O redirection handler: */
	pci_रेजिस्टर_set_vga_state(uv_set_vga_state);

	check_efi_reboot();
पूर्ण

/*
 * There is a dअगरferent code path needed to initialize a UV प्रणाली that करोes
 * not have a "UV HUB" (referred to as "hubless").
 */
व्योम __init uv_प्रणाली_init(व्योम)
अणु
	अगर (likely(!is_uv_प्रणाली() && !is_uv_hubless(1)))
		वापस;

	अगर (is_uv_प्रणाली())
		uv_प्रणाली_init_hub();
	अन्यथा
		uv_प्रणाली_init_hubless();
पूर्ण

apic_driver(apic_x2apic_uv_x);
