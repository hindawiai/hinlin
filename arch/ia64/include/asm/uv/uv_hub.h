<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV architectural definitions
 *
 * Copyright (C) 2008 Silicon Graphics, Inc. All rights reserved.
 */

#अगर_अघोषित __ASM_IA64_UV_HUB_H__
#घोषणा __ASM_IA64_UV_HUB_H__

#समावेश <linux/numa.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/percpu.h>


/*
 * Addressing Terminology
 *
 *	M       - The low M bits of a physical address represent the offset
 *		  पूर्णांकo the blade local memory. RAM memory on a blade is physically
 *		  contiguous (although various IO spaces may punch holes in
 *		  it)..
 *
 * 	N	- Number of bits in the node portion of a socket physical
 * 		  address.
 *
 * 	NASID   - network ID of a router, Mbrick or Cbrick. Nasid values of
 * 	 	  routers always have low bit of 1, C/MBricks have low bit
 * 		  equal to 0. Most addressing macros that target UV hub chips
 * 		  right shअगरt the NASID by 1 to exclude the always-zero bit.
 * 		  NASIDs contain up to 15 bits.
 *
 *	GNODE   - NASID right shअगरted by 1 bit. Most mmrs contain gnodes instead
 *		  of nasids.
 *
 * 	PNODE   - the low N bits of the GNODE. The PNODE is the most useful variant
 * 		  of the nasid क्रम socket usage.
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
#घोषणा UV_MAX_SSI_BLADES	1

/*
 * The largest possible NASID of a C or M brick (+ 2)
 */
#घोषणा UV_MAX_NASID_VALUE	(UV_MAX_NUMALINK_NODES * 2)

/*
 * The following defines attributes of the HUB chip. These attributes are
 * frequently referenced and are kept in the per-cpu data areas of each cpu.
 * They are kept together in a काष्ठा to minimize cache misses.
 */
काष्ठा uv_hub_info_s अणु
	अचिन्हित दीर्घ	global_mmr_base;
	अचिन्हित दीर्घ	gpa_mask;
	अचिन्हित दीर्घ	gnode_upper;
	अचिन्हित दीर्घ	lowmem_remap_top;
	अचिन्हित दीर्घ	lowmem_remap_base;
	अचिन्हित लघु	pnode;
	अचिन्हित लघु	pnode_mask;
	अचिन्हित लघु	coherency_करोमुख्य_number;
	अचिन्हित लघु	numa_blade_id;
	अचिन्हित अक्षर	blade_processor_id;
	अचिन्हित अक्षर	m_val;
	अचिन्हित अक्षर	n_val;
पूर्ण;
DECLARE_PER_CPU(काष्ठा uv_hub_info_s, __uv_hub_info);
#घोषणा uv_hub_info 		this_cpu_ptr(&__uv_hub_info)
#घोषणा uv_cpu_hub_info(cpu)	(&per_cpu(__uv_hub_info, cpu))

/*
 * Local & Global MMR space macros.
 * 	Note: macros are पूर्णांकended to be used ONLY by अंतरभूत functions
 * 	in this file - not by other kernel code.
 * 		n -  NASID (full 15-bit global nasid)
 * 		g -  GNODE (full 15-bit global nasid, right shअगरted 1)
 * 		p -  PNODE (local part of nsids, right shअगरted 1)
 */
#घोषणा UV_NASID_TO_PNODE(n)		(((n) >> 1) & uv_hub_info->pnode_mask)
#घोषणा UV_PNODE_TO_NASID(p)		(((p) << 1) | uv_hub_info->gnode_upper)

#घोषणा UV_LOCAL_MMR_BASE		0xf4000000UL
#घोषणा UV_GLOBAL_MMR32_BASE		0xf8000000UL
#घोषणा UV_GLOBAL_MMR64_BASE		(uv_hub_info->global_mmr_base)

#घोषणा UV_GLOBAL_MMR32_PNODE_SHIFT	15
#घोषणा UV_GLOBAL_MMR64_PNODE_SHIFT	26

#घोषणा UV_GLOBAL_MMR32_PNODE_BITS(p)	((p) << (UV_GLOBAL_MMR32_PNODE_SHIFT))

#घोषणा UV_GLOBAL_MMR64_PNODE_BITS(p)					\
	((अचिन्हित दीर्घ)(p) << UV_GLOBAL_MMR64_PNODE_SHIFT)

/*
 * Macros क्रम converting between kernel भव addresses, socket local physical
 * addresses, and UV global physical addresses.
 * 	Note: use the standard __pa() & __va() macros क्रम converting
 * 	      between socket भव and socket physical addresses.
 */

/* socket phys RAM --> UV global physical address */
अटल अंतरभूत अचिन्हित दीर्घ uv_soc_phys_ram_to_gpa(अचिन्हित दीर्घ paddr)
अणु
	अगर (paddr < uv_hub_info->lowmem_remap_top)
		paddr += uv_hub_info->lowmem_remap_base;
	वापस paddr | uv_hub_info->gnode_upper;
पूर्ण


/* socket भव --> UV global physical address */
अटल अंतरभूत अचिन्हित दीर्घ uv_gpa(व्योम *v)
अणु
	वापस __pa(v) | uv_hub_info->gnode_upper;
पूर्ण

/* socket भव --> UV global physical address */
अटल अंतरभूत व्योम *uv_vgpa(व्योम *v)
अणु
	वापस (व्योम *)uv_gpa(v);
पूर्ण

/* UV global physical address --> socket भव */
अटल अंतरभूत व्योम *uv_va(अचिन्हित दीर्घ gpa)
अणु
	वापस __va(gpa & uv_hub_info->gpa_mask);
पूर्ण

/* pnode, offset --> socket भव */
अटल अंतरभूत व्योम *uv_pnode_offset_to_vaddr(पूर्णांक pnode, अचिन्हित दीर्घ offset)
अणु
	वापस __va(((अचिन्हित दीर्घ)pnode << uv_hub_info->m_val) | offset);
पूर्ण


/*
 * Access global MMRs using the low memory MMR32 space. This region supports
 * faster MMR access but not all MMRs are accessible in this space.
 */
अटल अंतरभूत अचिन्हित दीर्घ *uv_global_mmr32_address(पूर्णांक pnode,
				अचिन्हित दीर्घ offset)
अणु
	वापस __va(UV_GLOBAL_MMR32_BASE |
		       UV_GLOBAL_MMR32_PNODE_BITS(pnode) | offset);
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_global_mmr32(पूर्णांक pnode, अचिन्हित दीर्घ offset,
				 अचिन्हित दीर्घ val)
अणु
	*uv_global_mmr32_address(pnode, offset) = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ uv_पढ़ो_global_mmr32(पूर्णांक pnode,
						 अचिन्हित दीर्घ offset)
अणु
	वापस *uv_global_mmr32_address(pnode, offset);
पूर्ण

/*
 * Access Global MMR space using the MMR space located at the top of physical
 * memory.
 */
अटल अंतरभूत अचिन्हित दीर्घ *uv_global_mmr64_address(पूर्णांक pnode,
				अचिन्हित दीर्घ offset)
अणु
	वापस __va(UV_GLOBAL_MMR64_BASE |
		    UV_GLOBAL_MMR64_PNODE_BITS(pnode) | offset);
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_global_mmr64(पूर्णांक pnode, अचिन्हित दीर्घ offset,
				अचिन्हित दीर्घ val)
अणु
	*uv_global_mmr64_address(pnode, offset) = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ uv_पढ़ो_global_mmr64(पूर्णांक pnode,
						 अचिन्हित दीर्घ offset)
अणु
	वापस *uv_global_mmr64_address(pnode, offset);
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
	वापस *uv_local_mmr_address(offset);
पूर्ण

अटल अंतरभूत व्योम uv_ग_लिखो_local_mmr(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ val)
अणु
	*uv_local_mmr_address(offset) = val;
पूर्ण

/*
 * Structures and definitions क्रम converting between cpu, node, pnode, and blade
 * numbers.
 */

/* Blade-local cpu number of current cpu. Numbered 0 .. <# cpus on the blade> */
अटल अंतरभूत पूर्णांक uv_blade_processor_id(व्योम)
अणु
	वापस smp_processor_id();
पूर्ण

/* Blade number of current cpu. Numnbered 0 .. <#blades -1> */
अटल अंतरभूत पूर्णांक uv_numa_blade_id(व्योम)
अणु
	वापस 0;
पूर्ण

/* Convert a cpu number to the the UV blade number */
अटल अंतरभूत पूर्णांक uv_cpu_to_blade_id(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

/* Convert linux node number to the UV blade number */
अटल अंतरभूत पूर्णांक uv_node_to_blade_id(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण

/* Convert a blade id to the PNODE of the blade */
अटल अंतरभूत पूर्णांक uv_blade_to_pnode(पूर्णांक bid)
अणु
	वापस 0;
पूर्ण

/* Determine the number of possible cpus on a blade */
अटल अंतरभूत पूर्णांक uv_blade_nr_possible_cpus(पूर्णांक bid)
अणु
	वापस num_possible_cpus();
पूर्ण

/* Determine the number of online cpus on a blade */
अटल अंतरभूत पूर्णांक uv_blade_nr_online_cpus(पूर्णांक bid)
अणु
	वापस num_online_cpus();
पूर्ण

/* Convert a cpu id to the PNODE of the blade containing the cpu */
अटल अंतरभूत पूर्णांक uv_cpu_to_pnode(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

/* Convert a linux node number to the PNODE of the blade */
अटल अंतरभूत पूर्णांक uv_node_to_pnode(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण

/* Maximum possible number of blades */
अटल अंतरभूत पूर्णांक uv_num_possible_blades(व्योम)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम uv_hub_send_ipi(पूर्णांक pnode, पूर्णांक apicid, पूर्णांक vector)
अणु
	/* not currently needed on ia64 */
पूर्ण


#पूर्ण_अगर /* __ASM_IA64_UV_HUB__ */

