<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * memory.c: PROM library functions क्रम acquiring/using memory descriptors
 *	     given to us from the ARCS firmware.
 *
 * Copyright (C) 1996 by David S. Miller
 * Copyright (C) 1999, 2000, 2001 by Ralf Baechle
 * Copyright (C) 1999, 2000 by Silicon Graphics, Inc.
 *
 * PROM library functions क्रम acquiring/using memory descriptors given to us
 * from the ARCS firmware.  This is only used when CONFIG_ARC_MEMORY is set
 * because on some machines like SGI IP27 the ARC memory configuration data
 * completely bogus and alternate easier to use mechanisms are available.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swap.h>

#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/bootinfo.h>

#अघोषित DEBUG

#घोषणा MAX_PROM_MEM 5
अटल phys_addr_t prom_mem_base[MAX_PROM_MEM] __initdata;
अटल phys_addr_t prom_mem_size[MAX_PROM_MEM] __initdata;
अटल अचिन्हित पूर्णांक nr_prom_mem __initdata;

/*
 * For ARC firmware memory functions the unit of meassuring memory is always
 * a 4k page of memory
 */
#घोषणा ARC_PAGE_SHIFT	12

काष्ठा linux_mdesc * __init ArcGetMemoryDescriptor(काष्ठा linux_mdesc *Current)
अणु
	वापस (काष्ठा linux_mdesc *) ARC_CALL1(get_mdesc, Current);
पूर्ण

#अगर_घोषित DEBUG /* convenient क्रम debugging */
अटल अक्षर *arcs_mtypes[8] = अणु
	"Exception Block",
	"ARCS Romvec Page",
	"Free/Contig RAM",
	"Generic Free RAM",
	"Bad Memory",
	"Standalone Program Pages",
	"ARCS Temp Storage Area",
	"ARCS Permanent Storage Area"
पूर्ण;

अटल अक्षर *arc_mtypes[8] = अणु
	"Exception Block",
	"SystemParameterBlock",
	"FreeMemory",
	"Bad Memory",
	"LoadedProgram",
	"FirmwareTemporary",
	"FirmwarePermanent",
	"FreeContiguous"
पूर्ण;
#घोषणा mtypes(a) (prom_flags & PROM_FLAG_ARCS) ? arcs_mtypes[a.arcs] \
						: arc_mtypes[a.arc]
#पूर्ण_अगर

क्रमागत अणु
	mem_मुक्त, mem_prom_used, mem_reserved
पूर्ण;

अटल अंतरभूत पूर्णांक memtype_classअगरy_arcs(जोड़ linux_memtypes type)
अणु
	चयन (type.arcs) अणु
	हाल arcs_fcontig:
	हाल arcs_मुक्त:
		वापस mem_मुक्त;
	हाल arcs_aपंचांगp:
		वापस mem_prom_used;
	हाल arcs_eblock:
	हाल arcs_rvpage:
	हाल arcs_bmem:
	हाल arcs_prog:
	हाल arcs_aperm:
		वापस mem_reserved;
	शेष:
		BUG();
	पूर्ण
	जबतक(1);				/* Nuke warning.  */
पूर्ण

अटल अंतरभूत पूर्णांक memtype_classअगरy_arc(जोड़ linux_memtypes type)
अणु
	चयन (type.arc) अणु
	हाल arc_मुक्त:
	हाल arc_fcontig:
		वापस mem_मुक्त;
	हाल arc_aपंचांगp:
		वापस mem_prom_used;
	हाल arc_eblock:
	हाल arc_rvpage:
	हाल arc_bmem:
	हाल arc_prog:
	हाल arc_aperm:
		वापस mem_reserved;
	शेष:
		BUG();
	पूर्ण
	जबतक(1);				/* Nuke warning.  */
पूर्ण

अटल पूर्णांक __init prom_memtype_classअगरy(जोड़ linux_memtypes type)
अणु
	अगर (prom_flags & PROM_FLAG_ARCS)	/* SGI is ``dअगरferent'' ... */
		वापस memtype_classअगरy_arcs(type);

	वापस memtype_classअगरy_arc(type);
पूर्ण

व्योम __weak __init prom_meminit(व्योम)
अणु
	काष्ठा linux_mdesc *p;

#अगर_घोषित DEBUG
	पूर्णांक i = 0;

	prपूर्णांकk("ARCS MEMORY DESCRIPTOR dump:\n");
	p = ArcGetMemoryDescriptor(PROM_शून्य_MDESC);
	जबतक(p) अणु
		prपूर्णांकk("[%d,%p]: base<%08lx> pages<%08lx> type<%s>\n",
		       i, p, p->base, p->pages, mtypes(p->type));
		p = ArcGetMemoryDescriptor(p);
		i++;
	पूर्ण
#पूर्ण_अगर

	nr_prom_mem = 0;
	p = PROM_शून्य_MDESC;
	जबतक ((p = ArcGetMemoryDescriptor(p))) अणु
		अचिन्हित दीर्घ base, size;
		दीर्घ type;

		base = p->base << ARC_PAGE_SHIFT;
		size = p->pages << ARC_PAGE_SHIFT;
		type = prom_memtype_classअगरy(p->type);

		/* ignore mirrored RAM on IP28/IP30 */
		अगर (base < PHYS_OFFSET)
			जारी;

		memblock_add(base, size);

		अगर (type == mem_reserved)
			memblock_reserve(base, size);

		अगर (type == mem_prom_used) अणु
			memblock_reserve(base, size);
			अगर (nr_prom_mem >= 5) अणु
				pr_err("Too many ROM DATA regions");
				जारी;
			पूर्ण
			prom_mem_base[nr_prom_mem] = base;
			prom_mem_size[nr_prom_mem] = size;
			nr_prom_mem++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __weak __init prom_cleanup(व्योम)
अणु
पूर्ण

व्योम __init prom_मुक्त_prom_memory(व्योम)
अणु
	पूर्णांक i;

	अगर (prom_flags & PROM_FLAG_DONT_FREE_TEMP)
		वापस;

	क्रम (i = 0; i < nr_prom_mem; i++) अणु
		मुक्त_init_pages("prom memory",
			prom_mem_base[i], prom_mem_base[i] + prom_mem_size[i]);
	पूर्ण
	/*
	 * at this poपूर्णांक it isn't safe to call PROM functions
	 * give platक्रमms a way to करो PROM cleanups
	 */
	prom_cleanup();
पूर्ण
