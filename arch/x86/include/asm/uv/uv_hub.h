<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV architectural definitions
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2007-2014 Silicon Graphics, Inc. All rights reserved.
 */

#अगर_अघोषित _ASM_X86_UV_UV_HUB_H
#घोषणा _ASM_X86_UV_UV_HUB_H

#अगर_घोषित CONFIG_X86_64
#समावेश <linux/numa.h>
#समावेश <linux/percpu.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/topology.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/uv/uv_mmrs.h>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/io_apic.h>


/*
 * Addressing Terminology
 *
 *	M       - The low M bits of a physical address represent the offset
 *		  पूर्णांकo the blade local memory. RAM memory on a blade is physically
 *		  contiguous (although various IO spaces may punch holes in
 *		  it)..
 *
 *	N	- Number of bits in the node portion of a socket physical
 *		  address.
 *
 *	NASID   - network ID of a router, Mbrick or Cbrick. Nasid values of
 *		  routers always have low bit of 1, C/MBricks have low bit
 *		  equal to 0. Most addressing macros that target UV hub chips
 *		  right shअगरt the NASID by 1 to exclude the always-zero bit.
 *		  NASIDs contain up to 15 bits.
 *
 *	GNODE   - NASID right shअगरted by 1 bit. Most mmrs contain gnodes instead
 *		  of nasids.
 *
 *	PNODE   - the low N bits of the GNODE. The PNODE is the most useful variant
 *		  of the nasid क्रम socket usage.
 *
 *	GPA	- (global physical address) a socket physical address converted
 *		  so that it can be used by the GRU as a global address. Socket
 *		  physical addresses 1) need additional NASID (node) bits added
 *		  to the high end of the address, and 2) unaliased अगर the
 *		  partition करोes not have a physical address 0. In addition, on
 *		  UV2 rev 1, GPAs need the gnode left shअगरted to bits 39 or 40.
 *
 *
 *  NumaLink Global Physical Address Format:
 *  +--------------------------------+---------------------+
 *  |00..000|      GNODE             |      NodeOffset     |
 *  +--------------------------------+---------------------+
 *          |<-------53 - M bits --->|<--------M bits ----->
 *
 *	M - number of node offset bits (35 .. 40)
 *
 *
 *  Memory/UV-HUB Processor Socket Address Format:
 *  +----------------+---------------+---------------------+
 *  |00..000000000000|   PNODE       |      NodeOffset     |
 *  +----------------+---------------+---------------------+
 *                   <--- N bits --->|<--------M bits ----->
 *
 *	M - number of node offset bits (35 .. 40)
 *	N - number of PNODE bits (0 .. 10)
 *
 *		Note: M + N cannot currently exceed 44 (x86_64) or 46 (IA64).
 *		The actual values are configuration dependent and are set at
 *		boot समय. M & N values are set by the hardware/BIOS at boot.
 *
 *
 * APICID क्रमmat
 *	NOTE!!!!!! This is the current क्रमmat of the APICID. However, code
 *	should assume that this will change in the future. Use functions
 *	in this file क्रम all APICID bit manipulations and conversion.
 *
 *		1111110000000000
 *		5432109876543210
 *		pppppppppplc0cch	Nehalem-EX (12 bits in hdw reg)
 *		ppppppppplcc0cch	Wesपंचांगere-EX (12 bits in hdw reg)
 *		pppppppppppcccch	SandyBridge (15 bits in hdw reg)
 *		sssssssssss
 *
 *			p  = pnode bits
 *			l =  socket number on board
 *			c  = core
 *			h  = hyperthपढ़ो
 *			s  = bits that are in the SOCKET_ID CSR
 *
 *	Note: Processor may support fewer bits in the APICID रेजिस्टर. The ACPI
 *	      tables hold all 16 bits. Software needs to be aware of this.
 *
 *	      Unless otherwise specअगरied, all references to APICID refer to
 *	      the FULL value contained in ACPI tables, not the subset in the
 *	      processor APICID रेजिस्टर.
 */

/*
 * Maximum number of bricks in all partitions and in all coherency करोमुख्यs.
 * This is the total number of bricks accessible in the numalink fabric. It
 * includes all C & M bricks. Routers are NOT included.
 *
 * This value is also the value of the maximum number of non-router NASIDs
 * in the numalink fabric.
 *
 * NOTE: a brick may contain 1 or 2 OS nodes. Don't get these confused.
 */
#घोषणा UV_MAX_NUMALINK_BLADES	16384

/*
 * Maximum number of C/Mbricks within a software SSI (hardware may support
 * more).
 */
#घोषणा UV_MAX_SSI_BLADES	256

/*
 * The largest possible NASID of a C or M brick (+ 2)
 */
#घोषणा UV_MAX_NASID_VALUE	(UV_MAX_NUMALINK_BLADES * 2)

/* GAM (globally addressed memory) range table */
काष्ठा uv_gam_range_s अणु
	u32	limit;		/* PA bits 56:26 (GAM_RANGE_SHFT) */
	u16	nasid;		/* node's global physical address */
	s8	base;		/* entry index of node's base addr */
	u8	reserved;
पूर्ण;

/*
 * The following defines attributes of the HUB chip. These attributes are
 * frequently referenced and are kept in a common per hub काष्ठा.
 * After setup, the काष्ठा is पढ़ो only, so it should be पढ़ोily
 * available in the L3 cache on the cpu socket क्रम the node.
 */
काष्ठा uv_hub_info_s अणु
	अचिन्हित पूर्णांक		hub_type;
	अचिन्हित अक्षर		hub_revision;
	अचिन्हित दीर्घ		global_mmr_base;
	अचिन्हित दीर्घ		global_mmr_shअगरt;
	अचिन्हित दीर्घ		gpa_mask;
	अचिन्हित लघु		*socket_to_node;
	अचिन्हित लघु		*socket_to_pnode;
	अचिन्हित लघु		*pnode_to_socket;
	काष्ठा uv_gam_range_s	*gr_table;
	अचिन्हित लघु		min_socket;
	अचिन्हित लघु		min_pnode;
	अचिन्हित अक्षर		m_val;
	अचिन्हित अक्षर		n_val;
	अचिन्हित अक्षर		gr_table_len;
	अचिन्हित अक्षर		apic_pnode_shअगरt;
	अचिन्हित अक्षर		gpa_shअगरt;
	अचिन्हित अक्षर		nasid_shअगरt;
	अचिन्हित अक्षर		m_shअगरt;
	अचिन्हित अक्षर		n_lshअगरt;
	अचिन्हित पूर्णांक		gnode_extra;
	अचिन्हित दीर्घ		gnode_upper;
	अचिन्हित दीर्घ		lowmem_remap_top;
	अचिन्हित दीर्घ		lowmem_remap_base;
	अचिन्हित दीर्घ		global_gru_base;
	अचिन्हित दीर्घ		global_gru_shअगरt;
	अचिन्हित लघु		pnode;
	अचिन्हित लघु		pnode_mask;
	अचिन्हित लघु		coherency_करोमुख्य_number;
	अचिन्हित लघु		numa_blade_id;
	अचिन्हित लघु		nr_possible_cpus;
	अचिन्हित लघु		nr_online_cpus;
	लघु			memory_nid;
पूर्ण;

/* CPU specअगरic info with a poपूर्णांकer to the hub common info काष्ठा */
काष्ठा uv_cpu_info_s अणु
	व्योम			*p_uv_hub_info;
	अचिन्हित अक्षर		blade_cpu_id;
	व्योम			*reserved;
पूर्ण;
DECLARE_PER_CPU(काष्ठा uv_cpu_info_s, __uv_cpu_info);

#घोषणा uv_cpu_info		this_cpu_ptr(&__uv_cpu_info)
#घोषणा uv_cpu_info_per(cpu)	(&per_cpu(__uv_cpu_info, cpu))

/* Node specअगरic hub common info काष्ठा */
बाह्य व्योम **__uv_hub_info_list;
अटल अंतरभूत काष्ठा uv_hub_info_s *uv_hub_info_list(पूर्णांक node)
अणु
	वापस (काष्ठा uv_hub_info_s *)__uv_hub_info_list[node];
पूर्ण

अटल अंतरभूत काष्ठा uv_hub_info_s *_uv_hub_info(व्योम)
अणु
	वापस (काष्ठा uv_hub_info_s *)uv_cpu_info->p_uv_hub_info;
पूर्ण
#घोषणा	uv_hub_info	_uv_hub_info()

अटल अंतरभूत काष्ठा uv_hub_info_s *uv_cpu_hub_info(पूर्णांक cpu)
अणु
	वापस (काष्ठा uv_hub_info_s *)uv_cpu_info_per(cpu)->p_uv_hub_info;
पूर्ण

अटल अंतरभूत पूर्णांक uv_hub_type(व्योम)
अणु
	वापस uv_hub_info->hub_type;
पूर्ण

अटल अंतरभूत __init व्योम uv_hub_type_set(पूर्णांक uvmask)
अणु
	uv_hub_info->hub_type = uvmask;
पूर्ण


/*
 * HUB revision ranges क्रम each UV HUB architecture.
 * This is a software convention - NOT the hardware revision numbers in
 * the hub chip.
 */
#घोषणा UV2_HUB_REVISION_BASE		3
#घोषणा UV3_HUB_REVISION_BASE		5
#घोषणा UV4_HUB_REVISION_BASE		7
#घोषणा UV4A_HUB_REVISION_BASE		8	/* UV4 (fixed) rev 2 */
#घोषणा UV5_HUB_REVISION_BASE		9

अटल अंतरभूत पूर्णांक is_uv(पूर्णांक uvmask) अणु वापस uv_hub_type() & uvmask; पूर्ण
अटल अंतरभूत पूर्णांक is_uv1_hub(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक is_uv2_hub(व्योम) अणु वापस is_uv(UV2); पूर्ण
अटल अंतरभूत पूर्णांक is_uv3_hub(व्योम) अणु वापस is_uv(UV3); पूर्ण
अटल अंतरभूत पूर्णांक is_uv4a_hub(व्योम) अणु वापस is_uv(UV4A); पूर्ण
अटल अंतरभूत पूर्णांक is_uv4_hub(व्योम) अणु वापस is_uv(UV4); पूर्ण
अटल अंतरभूत पूर्णांक is_uv5_hub(व्योम) अणु वापस is_uv(UV5); पूर्ण

/*
 * UV4A is a revision of UV4.  So on UV4A, both is_uv4_hub() and
 * is_uv4a_hub() वापस true, While on UV4, only is_uv4_hub()
 * वापसs true.  So to get true results, first test अगर is UV4A,
 * then test अगर is UV4.
 */

/* UVX class: UV2,3,4 */
अटल अंतरभूत पूर्णांक is_uvx_hub(व्योम) अणु वापस is_uv(UVX); पूर्ण

/* UVY class: UV5,..? */
अटल अंतरभूत पूर्णांक is_uvy_hub(व्योम) अणु वापस is_uv(UVY); पूर्ण

/* Any UV Hubbed System */
अटल अंतरभूत पूर्णांक is_uv_hub(व्योम) अणु वापस is_uv(UV_ANY); पूर्ण

जोड़ uvh_apicid अणु
    अचिन्हित दीर्घ       v;
    काष्ठा uvh_apicid_s अणु
        अचिन्हित दीर्घ   local_apic_mask  : 24;
        अचिन्हित दीर्घ   local_apic_shअगरt :  5;
        अचिन्हित दीर्घ   unused1          :  3;
        अचिन्हित दीर्घ   pnode_mask       : 24;
        अचिन्हित दीर्घ   pnode_shअगरt      :  5;
        अचिन्हित दीर्घ   unused2          :  3;
    पूर्ण s;
पूर्ण;

/*
 * Local & Global MMR space macros.
 *	Note: macros are पूर्णांकended to be used ONLY by अंतरभूत functions
 *	in this file - not by other kernel code.
 *		n -  NASID (full 15-bit global nasid)
 *		g -  GNODE (full 15-bit global nasid, right shअगरted 1)
 *		p -  PNODE (local part of nsids, right shअगरted 1)
 */
#घोषणा UV_NASID_TO_PNODE(n)		\
		(((n) >> uv_hub_info->nasid_shअगरt) & uv_hub_info->pnode_mask)
#घोषणा UV_PNODE_TO_GNODE(p)		((p) |uv_hub_info->gnode_extra)
#घोषणा UV_PNODE_TO_NASID(p)		\
		(UV_PNODE_TO_GNODE(p) << uv_hub_info->nasid_shअगरt)

#घोषणा UV2_LOCAL_MMR_BASE		0xfa000000UL
#घोषणा UV2_GLOBAL_MMR32_BASE		0xfc000000UL
#घोषणा UV2_LOCAL_MMR_SIZE		(32UL * 1024 * 1024)
#घोषणा UV2_GLOBAL_MMR32_SIZE		(32UL * 1024 * 1024)

#घोषणा UV3_LOCAL_MMR_BASE		0xfa000000UL
#घोषणा UV3_GLOBAL_MMR32_BASE		0xfc000000UL
#घोषणा UV3_LOCAL_MMR_SIZE		(32UL * 1024 * 1024)
#घोषणा UV3_GLOBAL_MMR32_SIZE		(32UL * 1024 * 1024)

#घोषणा UV4_LOCAL_MMR_BASE		0xfa000000UL
#घोषणा UV4_GLOBAL_MMR32_BASE		0
#घोषणा UV4_LOCAL_MMR_SIZE		(32UL * 1024 * 1024)
#घोषणा UV4_GLOBAL_MMR32_SIZE		0

#घोषणा UV5_LOCAL_MMR_BASE		0xfa000000UL
#घोषणा UV5_GLOBAL_MMR32_BASE		0
#घोषणा UV5_LOCAL_MMR_SIZE		(32UL * 1024 * 1024)
#घोषणा UV5_GLOBAL_MMR32_SIZE		0

#घोषणा UV_LOCAL_MMR_BASE		(				\
					is_uv(UV2) ? UV2_LOCAL_MMR_BASE : \
					is_uv(UV3) ? UV3_LOCAL_MMR_BASE : \
					is_uv(UV4) ? UV4_LOCAL_MMR_BASE : \
					is_uv(UV5) ? UV5_LOCAL_MMR_BASE : \
					0)

#घोषणा UV_GLOBAL_MMR32_BASE		(				\
					is_uv(UV2) ? UV2_GLOBAL_MMR32_BASE : \
					is_uv(UV3) ? UV3_GLOBAL_MMR32_BASE : \
					is_uv(UV4) ? UV4_GLOBAL_MMR32_BASE : \
					is_uv(UV5) ? UV5_GLOBAL_MMR32_BASE : \
					0)

#घोषणा UV_LOCAL_MMR_SIZE		(				\
					is_uv(UV2) ? UV2_LOCAL_MMR_SIZE : \
					is_uv(UV3) ? UV3_LOCAL_MMR_SIZE : \
					is_uv(UV4) ? UV4_LOCAL_MMR_SIZE : \
					is_uv(UV5) ? UV5_LOCAL_MMR_SIZE : \
					0)

#घोषणा UV_GLOBAL_MMR32_SIZE		(				\
					is_uv(UV2) ? UV2_GLOBAL_MMR32_SIZE : \
					is_uv(UV3) ? UV3_GLOBAL_MMR32_SIZE : \
					is_uv(UV4) ? UV4_GLOBAL_MMR32_SIZE : \
					is_uv(UV5) ? UV5_GLOBAL_MMR32_SIZE : \
					0)

#घोषणा UV_GLOBAL_MMR64_BASE		(uv_hub_info->global_mmr_base)

#घोषणा UV_GLOBAL_GRU_MMR_BASE		0x4000000

#घोषणा UV_GLOBAL_MMR32_PNODE_SHIFT	15
#घोषणा _UV_GLOBAL_MMR64_PNODE_SHIFT	26
#घोषणा UV_GLOBAL_MMR64_PNODE_SHIFT	(uv_hub_info->global_mmr_shअगरt)

#घोषणा UV_GLOBAL_MMR32_PNODE_BITS(p)	((p) << (UV_GLOBAL_MMR32_PNODE_SHIFT))

#घोषणा UV_GLOBAL_MMR64_PNODE_BITS(p)					\
	(((अचिन्हित दीर्घ)(p)) << UV_GLOBAL_MMR64_PNODE_SHIFT)

#घोषणा UVH_APICID		0x002D0E00L
#घोषणा UV_APIC_PNODE_SHIFT	6

/* Local Bus from cpu's perspective */
#घोषणा LOCAL_BUS_BASE		0x1c00000
#घोषणा LOCAL_BUS_SIZE		(4 * 1024 * 1024)

/*
 * System Controller Interface Reg
 *
 * Note there are NO leds on a UV प्रणाली.  This रेजिस्टर is only
 * used by the प्रणाली controller to monitor प्रणाली-wide operation.
 * There are 64 regs per node.  With Nehalem cpus (2 cores per node,
 * 8 cpus per core, 2 thपढ़ोs per cpu) there are 32 cpu thपढ़ोs on
 * a node.
 *
 * The winकरोw is located at top of ACPI MMR space
 */
#घोषणा SCIR_WINDOW_COUNT	64
#घोषणा SCIR_LOCAL_MMR_BASE	(LOCAL_BUS_BASE + \
				 LOCAL_BUS_SIZE - \
				 SCIR_WINDOW_COUNT)

#घोषणा SCIR_CPU_HEARTBEAT	0x01	/* समयr पूर्णांकerrupt */
#घोषणा SCIR_CPU_ACTIVITY	0x02	/* not idle */
#घोषणा SCIR_CPU_HB_INTERVAL	(HZ)	/* once per second */

/* Loop through all installed blades */
#घोषणा क्रम_each_possible_blade(bid)		\
	क्रम ((bid) = 0; (bid) < uv_num_possible_blades(); (bid)++)

/*
 * Macros क्रम converting between kernel भव addresses, socket local physical
 * addresses, and UV global physical addresses.
 *	Note: use the standard __pa() & __va() macros क्रम converting
 *	      between socket भव and socket physical addresses.
 */

/* global bits offset - number of local address bits in gpa क्रम this UV arch */
अटल अंतरभूत अचिन्हित पूर्णांक uv_gpa_shअगरt(व्योम)
अणु
	वापस uv_hub_info->gpa_shअगरt;
पूर्ण
#घोषणा	_uv_gpa_shअगरt

/* Find node that has the address range that contains global address  */
अटल अंतरभूत काष्ठा uv_gam_range_s *uv_gam_range(अचिन्हित दीर्घ pa)
अणु
	काष्ठा uv_gam_range_s *gr = uv_hub_info->gr_table;
	अचिन्हित दीर्घ pal = (pa & uv_hub_info->gpa_mask) >> UV_GAM_RANGE_SHFT;
	पूर्णांक i, num = uv_hub_info->gr_table_len;

	अगर (gr) अणु
		क्रम (i = 0; i < num; i++, gr++) अणु
			अगर (pal < gr->limit)
				वापस gr;
		पूर्ण
	पूर्ण
	pr_crit("UV: GAM Range for 0x%lx not found at %p!\n", pa, gr);
	BUG();
पूर्ण

/* Return base address of node that contains global address  */
अटल अंतरभूत अचिन्हित दीर्घ uv_gam_range_base(अचिन्हित दीर्घ pa)
अणु
	काष्ठा uv_gam_range_s *gr = uv_gam_range(pa);
	पूर्णांक base = gr->base;

	अगर (base < 0)
		वापस 0UL;

	वापस uv_hub_info->gr_table[base].limit;
पूर्ण

/* socket phys RAM --> UV global NASID (UV4+) */
अटल अंतरभूत अचिन्हित दीर्घ uv_soc_phys_ram_to_nasid(अचिन्हित दीर्घ paddr)
अणु
	वापस uv_gam_range(paddr)->nasid;
पूर्ण
#घोषणा	_uv_soc_phys_ram_to_nasid

/* socket भव --> UV global NASID (UV4+) */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa_nasid(व्योम *v)
अणु
	वापस uv_soc_phys_ram_to_nasid(__pa(v));
पूर्ण

/* socket phys RAM --> UV global physical address */
अटल अंतरभूत अचिन्हित दीर्घ uv_soc_phys_ram_to_gpa(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित पूर्णांक m_val = uv_hub_info->m_val;

	अगर (paddr < uv_hub_info->lowmem_remap_top)
		paddr |= uv_hub_info->lowmem_remap_base;

	अगर (m_val) अणु
		paddr |= uv_hub_info->gnode_upper;
		paddr = ((paddr << uv_hub_info->m_shअगरt)
						>> uv_hub_info->m_shअगरt) |
			((paddr >> uv_hub_info->m_val)
						<< uv_hub_info->n_lshअगरt);
	पूर्ण अन्यथा अणु
		paddr |= uv_soc_phys_ram_to_nasid(paddr)
						<< uv_hub_info->gpa_shअगरt;
	पूर्ण
	वापस paddr;
पूर्ण

/* socket भव --> UV global physical address */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa(व्योम *v)
अणु
	वापस uv_soc_phys_ram_to_gpa(__pa(v));
पूर्ण

/* Top two bits indicate the requested address is in MMR space.  */
अटल अंतरभूत पूर्णांक
uv_gpa_in_mmr_space(अचिन्हित दीर्घ gpa)
अणु
	वापस (gpa >> 62) == 0x3UL;
पूर्ण

/* UV global physical address --> socket phys RAM */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa_to_soc_phys_ram(अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित दीर्घ paddr;
	अचिन्हित दीर्घ remap_base = uv_hub_info->lowmem_remap_base;
	अचिन्हित दीर्घ remap_top =  uv_hub_info->lowmem_remap_top;
	अचिन्हित पूर्णांक m_val = uv_hub_info->m_val;

	अगर (m_val)
		gpa = ((gpa << uv_hub_info->m_shअगरt) >> uv_hub_info->m_shअगरt) |
			((gpa >> uv_hub_info->n_lshअगरt) << uv_hub_info->m_val);

	paddr = gpa & uv_hub_info->gpa_mask;
	अगर (paddr >= remap_base && paddr < remap_base + remap_top)
		paddr -= remap_base;
	वापस paddr;
पूर्ण

/* gpa -> gnode */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa_to_gnode(अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित पूर्णांक n_lshअगरt = uv_hub_info->n_lshअगरt;

	अगर (n_lshअगरt)
		वापस gpa >> n_lshअगरt;

	वापस uv_gam_range(gpa)->nasid >> 1;
पूर्ण

/* gpa -> pnode */
अटल अंतरभूत पूर्णांक uv_gpa_to_pnode(अचिन्हित दीर्घ gpa)
अणु
	वापस uv_gpa_to_gnode(gpa) & uv_hub_info->pnode_mask;
पूर्ण

/* gpa -> node offset */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa_to_offset(अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित पूर्णांक m_shअगरt = uv_hub_info->m_shअगरt;

	अगर (m_shअगरt)
		वापस (gpa << m_shअगरt) >> m_shअगरt;

	वापस (gpa & uv_hub_info->gpa_mask) - uv_gam_range_base(gpa);
पूर्ण

/* Convert socket to node */
अटल अंतरभूत पूर्णांक _uv_socket_to_node(पूर्णांक socket, अचिन्हित लघु *s2nid)
अणु
	वापस s2nid ? s2nid[socket - uv_hub_info->min_socket] : socket;
पूर्ण

अटल अंतरभूत पूर्णांक uv_socket_to_node(पूर्णांक socket)
अणु
	वापस _uv_socket_to_node(socket, uv_hub_info->socket_to_node);
पूर्ण

/* pnode, offset --> socket भव */
अटल अंतरभूत व्योम *uv_pnode_offset_to_vaddr(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित पूर्णांक m_val = uv_hub_info->m_val;
	अचिन्हित दीर्घ base;
	अचिन्हित लघु sockid, node, *p2s;

	अगर (m_val)
		वापस __va(((अचिन्हित दीर्घ)pnode << m_val) | offset);

	p2s = uv_hub_info->pnode_to_socket;
	sockid = p2s ? p2s[pnode - uv_hub_info->min_pnode] : pnode;
	node = uv_socket_to_node(sockid);

	/* limit address of previous socket is our base, except node 0 is 0 */
	अगर (!node)
		वापस __va((अचिन्हित दीर्घ)offset);

	base = (अचिन्हित दीर्घ)(uv_hub_info->gr_table[node - 1].limit);
	वापस __va(base << UV_GAM_RANGE_SHFT | offset);
पूर्ण

/* Extract/Convert a PNODE from an APICID (full apicid, not processor subset) */
अटल अंतरभूत पूर्णांक uv_apicid_to_pnode(पूर्णांक apicid)
अणु
	पूर्णांक pnode = apicid >> uv_hub_info->apic_pnode_shअगरt;
	अचिन्हित लघु *s2pn = uv_hub_info->socket_to_pnode;

	वापस s2pn ? s2pn[pnode - uv_hub_info->min_socket] : pnode;
पूर्ण

/*
 * Access global MMRs using the low memory MMR32 space. This region supports
 * faster MMR access but not all MMRs are accessible in this space.
 */
अटल अंतरभूत अचिन्हित दीर्घ *uv_global_mmr32_address(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस __va(UV_GLOBAL_MMR32_BASE |
		       UV_GLOBAL_MMR32_PNODE_BITS(pnode) | offset);
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_global_mmr32(पूर्णांक pnode, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ val)
अणु
	ग_लिखोq(val, uv_global_mmr32_address(pnode, offset));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ uv_पढ़ो_global_mmr32(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोq(uv_global_mmr32_address(pnode, offset));
पूर्ण

/*
 * Access Global MMR space using the MMR space located at the top of physical
 * memory.
 */
अटल अंतरभूत अस्थिर व्योम __iomem *uv_global_mmr64_address(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस __va(UV_GLOBAL_MMR64_BASE |
		    UV_GLOBAL_MMR64_PNODE_BITS(pnode) | offset);
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_global_mmr64(पूर्णांक pnode, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ val)
अणु
	ग_लिखोq(val, uv_global_mmr64_address(pnode, offset));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ uv_पढ़ो_global_mmr64(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोq(uv_global_mmr64_address(pnode, offset));
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_global_mmr8(पूर्णांक pnode, अचिन्हित दीर्घ offset, अचिन्हित अक्षर val)
अणु
	ग_लिखोb(val, uv_global_mmr64_address(pnode, offset));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर uv_पढ़ो_global_mmr8(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोb(uv_global_mmr64_address(pnode, offset));
पूर्ण

/*
 * Access hub local MMRs. Faster than using global space but only local MMRs
 * are accessible.
 */
अटल अंतरभूत अचिन्हित दीर्घ *uv_local_mmr_address(अचिन्हित दीर्घ offset)
अणु
	वापस __va(UV_LOCAL_MMR_BASE | offset);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ uv_पढ़ो_local_mmr(अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोq(uv_local_mmr_address(offset));
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_local_mmr(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ val)
अणु
	ग_लिखोq(val, uv_local_mmr_address(offset));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर uv_पढ़ो_local_mmr8(अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोb(uv_local_mmr_address(offset));
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_local_mmr8(अचिन्हित दीर्घ offset, अचिन्हित अक्षर val)
अणु
	ग_लिखोb(val, uv_local_mmr_address(offset));
पूर्ण

/* Blade-local cpu number of current cpu. Numbered 0 .. <# cpus on the blade> */
अटल अंतरभूत पूर्णांक uv_blade_processor_id(व्योम)
अणु
	वापस uv_cpu_info->blade_cpu_id;
पूर्ण

/* Blade-local cpu number of cpu N. Numbered 0 .. <# cpus on the blade> */
अटल अंतरभूत पूर्णांक uv_cpu_blade_processor_id(पूर्णांक cpu)
अणु
	वापस uv_cpu_info_per(cpu)->blade_cpu_id;
पूर्ण

/* Blade number to Node number (UV2..UV4 is 1:1) */
अटल अंतरभूत पूर्णांक uv_blade_to_node(पूर्णांक blade)
अणु
	वापस blade;
पूर्ण

/* Blade number of current cpu. Numnbered 0 .. <#blades -1> */
अटल अंतरभूत पूर्णांक uv_numa_blade_id(व्योम)
अणु
	वापस uv_hub_info->numa_blade_id;
पूर्ण

/*
 * Convert linux node number to the UV blade number.
 * .. Currently क्रम UV2 thru UV4 the node and the blade are identical.
 * .. If this changes then you MUST check references to this function!
 */
अटल अंतरभूत पूर्णांक uv_node_to_blade_id(पूर्णांक nid)
अणु
	वापस nid;
पूर्ण

/* Convert a CPU number to the UV blade number */
अटल अंतरभूत पूर्णांक uv_cpu_to_blade_id(पूर्णांक cpu)
अणु
	वापस uv_node_to_blade_id(cpu_to_node(cpu));
पूर्ण

/* Convert a blade id to the PNODE of the blade */
अटल अंतरभूत पूर्णांक uv_blade_to_pnode(पूर्णांक bid)
अणु
	वापस uv_hub_info_list(uv_blade_to_node(bid))->pnode;
पूर्ण

/* Nid of memory node on blade. -1 अगर no blade-local memory */
अटल अंतरभूत पूर्णांक uv_blade_to_memory_nid(पूर्णांक bid)
अणु
	वापस uv_hub_info_list(uv_blade_to_node(bid))->memory_nid;
पूर्ण

/* Determine the number of possible cpus on a blade */
अटल अंतरभूत पूर्णांक uv_blade_nr_possible_cpus(पूर्णांक bid)
अणु
	वापस uv_hub_info_list(uv_blade_to_node(bid))->nr_possible_cpus;
पूर्ण

/* Determine the number of online cpus on a blade */
अटल अंतरभूत पूर्णांक uv_blade_nr_online_cpus(पूर्णांक bid)
अणु
	वापस uv_hub_info_list(uv_blade_to_node(bid))->nr_online_cpus;
पूर्ण

/* Convert a cpu id to the PNODE of the blade containing the cpu */
अटल अंतरभूत पूर्णांक uv_cpu_to_pnode(पूर्णांक cpu)
अणु
	वापस uv_cpu_hub_info(cpu)->pnode;
पूर्ण

/* Convert a linux node number to the PNODE of the blade */
अटल अंतरभूत पूर्णांक uv_node_to_pnode(पूर्णांक nid)
अणु
	वापस uv_hub_info_list(nid)->pnode;
पूर्ण

/* Maximum possible number of blades */
बाह्य लघु uv_possible_blades;
अटल अंतरभूत पूर्णांक uv_num_possible_blades(व्योम)
अणु
	वापस uv_possible_blades;
पूर्ण

/* Per Hub NMI support */
बाह्य व्योम uv_nmi_setup(व्योम);
बाह्य व्योम uv_nmi_setup_hubless(व्योम);

/* BIOS/Kernel flags exchange MMR */
#घोषणा UVH_BIOS_KERNEL_MMR		UVH_SCRATCH5
#घोषणा UVH_BIOS_KERNEL_MMR_ALIAS	UVH_SCRATCH5_ALIAS
#घोषणा UVH_BIOS_KERNEL_MMR_ALIAS_2	UVH_SCRATCH5_ALIAS_2

/* TSC sync valid, set by BIOS */
#घोषणा UVH_TSC_SYNC_MMR	UVH_BIOS_KERNEL_MMR
#घोषणा UVH_TSC_SYNC_SHIFT	10
#घोषणा UVH_TSC_SYNC_SHIFT_UV2K	16	/* UV2/3k have dअगरferent bits */
#घोषणा UVH_TSC_SYNC_MASK	3	/* 0011 */
#घोषणा UVH_TSC_SYNC_VALID	3	/* 0011 */
#घोषणा UVH_TSC_SYNC_UNKNOWN	0	/* 0000 */

/* BMC sets a bit this MMR non-zero beक्रमe sending an NMI */
#घोषणा UVH_NMI_MMR		UVH_BIOS_KERNEL_MMR
#घोषणा UVH_NMI_MMR_CLEAR	UVH_BIOS_KERNEL_MMR_ALIAS
#घोषणा UVH_NMI_MMR_SHIFT	63
#घोषणा UVH_NMI_MMR_TYPE	"SCRATCH5"

काष्ठा uv_hub_nmi_s अणु
	raw_spinlock_t	nmi_lock;
	atomic_t	in_nmi;		/* flag this node in UV NMI IRQ */
	atomic_t	cpu_owner;	/* last locker of this काष्ठा */
	atomic_t	पढ़ो_mmr_count;	/* count of MMR पढ़ोs */
	atomic_t	nmi_count;	/* count of true UV NMIs */
	अचिन्हित दीर्घ	nmi_value;	/* last value पढ़ो from NMI MMR */
	bool		hub_present;	/* false means UV hubless प्रणाली */
	bool		pch_owner;	/* indicates this hub owns PCH */
पूर्ण;

काष्ठा uv_cpu_nmi_s अणु
	काष्ठा uv_hub_nmi_s	*hub;
	पूर्णांक			state;
	पूर्णांक			pinging;
	पूर्णांक			queries;
	पूर्णांक			pings;
पूर्ण;

DECLARE_PER_CPU(काष्ठा uv_cpu_nmi_s, uv_cpu_nmi);

#घोषणा uv_hub_nmi			this_cpu_पढ़ो(uv_cpu_nmi.hub)
#घोषणा uv_cpu_nmi_per(cpu)		(per_cpu(uv_cpu_nmi, cpu))
#घोषणा uv_hub_nmi_per(cpu)		(uv_cpu_nmi_per(cpu).hub)

/* uv_cpu_nmi_states */
#घोषणा	UV_NMI_STATE_OUT		0
#घोषणा	UV_NMI_STATE_IN			1
#घोषणा	UV_NMI_STATE_DUMP		2
#घोषणा	UV_NMI_STATE_DUMP_DONE		3

/*
 * Get the minimum revision number of the hub chips within the partition.
 * (See UVx_HUB_REVISION_BASE above क्रम specअगरic values.)
 */
अटल अंतरभूत पूर्णांक uv_get_min_hub_revision_id(व्योम)
अणु
	वापस uv_hub_info->hub_revision;
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_64 */
#पूर्ण_अगर /* _ASM_X86_UV_UV_HUB_H */
