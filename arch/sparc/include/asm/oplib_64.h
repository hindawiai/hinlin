<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* oplib.h:  Describes the पूर्णांकerface and available routines in the
 *           Linux Prom library.
 *
 * Copyright (C) 1995, 2007 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#अगर_अघोषित __SPARC64_OPLIB_H
#घोषणा __SPARC64_OPLIB_H

#समावेश <यंत्र/खोलोprom.h>

/* OBP version string. */
बाह्य अक्षर prom_version[];

/* Root node of the prom device tree, this stays स्थिरant after
 * initialization is complete.
 */
बाह्य phandle prom_root_node;

/* PROM मानक_निकास */
बाह्य पूर्णांक prom_मानक_निकास;

/* /chosen node of the prom device tree, this stays स्थिरant after
 * initialization is complete.
 */
बाह्य phandle prom_chosen_node;

/* Helper values and strings in arch/sparc64/kernel/head.S */
बाह्य स्थिर अक्षर prom_peer_name[];
बाह्य स्थिर अक्षर prom_compatible_name[];
बाह्य स्थिर अक्षर prom_root_compatible[];
बाह्य स्थिर अक्षर prom_cpu_compatible[];
बाह्य स्थिर अक्षर prom_finddev_name[];
बाह्य स्थिर अक्षर prom_chosen_path[];
बाह्य स्थिर अक्षर prom_cpu_path[];
बाह्य स्थिर अक्षर prom_getprop_name[];
बाह्य स्थिर अक्षर prom_mmu_name[];
बाह्य स्थिर अक्षर prom_callmethod_name[];
बाह्य स्थिर अक्षर prom_translate_name[];
बाह्य स्थिर अक्षर prom_map_name[];
बाह्य स्थिर अक्षर prom_unmap_name[];
बाह्य पूर्णांक prom_mmu_ihandle_cache;
बाह्य अचिन्हित पूर्णांक prom_boot_mapped_pc;
बाह्य अचिन्हित पूर्णांक prom_boot_mapping_mode;
बाह्य अचिन्हित दीर्घ prom_boot_mapping_phys_high, prom_boot_mapping_phys_low;

काष्ठा linux_mlist_p1275 अणु
	काष्ठा linux_mlist_p1275 *theres_more;
	अचिन्हित दीर्घ start_adr;
	अचिन्हित दीर्घ num_bytes;
पूर्ण;

काष्ठा linux_mem_p1275 अणु
	काष्ठा linux_mlist_p1275 **p1275_totphys;
	काष्ठा linux_mlist_p1275 **p1275_prommap;
	काष्ठा linux_mlist_p1275 **p1275_available; /* What we can use */
पूर्ण;

/* The functions... */

/* You must call prom_init() beक्रमe using any of the library services,
 * preferably as early as possible.  Pass it the romvec poपूर्णांकer.
 */
व्योम prom_init(व्योम *cअगर_handler);
व्योम prom_init_report(व्योम);

/* Boot argument acquisition, वापसs the boot command line string. */
अक्षर *prom_getbootargs(व्योम);

/* Miscellaneous routines, करोn't really fit in any category per se. */

/* Reboot the machine with the command line passed. */
व्योम prom_reboot(स्थिर अक्षर *boot_command);

/* Evaluate the क्रमth string passed. */
व्योम prom_feval(स्थिर अक्षर *क्रमth_string);

/* Enter the prom, with possibility of continuation with the 'go'
 * command in newer proms.
 */
व्योम prom_cmdline(व्योम);

/* Enter the prom, with no chance of continuation क्रम the stand-alone
 * which calls this.
 */
व्योम prom_halt(व्योम) __attribute__ ((noवापस));

/* Halt and घातer-off the machine. */
व्योम prom_halt_घातer_off(व्योम) __attribute__ ((noवापस));

/* Acquire the IDPROM of the root node in the prom device tree.  This
 * माला_लो passed a buffer where you would like it stuffed.  The वापस value
 * is the क्रमmat type of this idprom or 0xff on error.
 */
अचिन्हित अक्षर prom_get_idprom(अक्षर *idp_buffer, पूर्णांक idpbuf_size);

/* Write a buffer of अक्षरacters to the console. */
व्योम prom_console_ग_लिखो_buf(स्थिर अक्षर *buf, पूर्णांक len);

/* Prom's internal routines, don't use in kernel/boot code. */
__म_लिखो(1, 2) व्योम prom_म_लिखो(स्थिर अक्षर *fmt, ...);
व्योम prom_ग_लिखो(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len);

/* Multiprocessor operations... */
#अगर_घोषित CONFIG_SMP
/* Start the CPU with the given device tree node at the passed program
 * counter with the given arg passed in via रेजिस्टर %o0.
 */
व्योम prom_startcpu(पूर्णांक cpunode, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ arg);

/* Start the CPU with the given cpu ID at the passed program
 * counter with the given arg passed in via रेजिस्टर %o0.
 */
व्योम prom_startcpu_cpuid(पूर्णांक cpuid, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ arg);

/* Stop the CPU with the given cpu ID.  */
व्योम prom_stopcpu_cpuid(पूर्णांक cpuid);

/* Stop the current CPU. */
व्योम prom_stopself(व्योम);

/* Idle the current CPU. */
व्योम prom_idleself(व्योम);

/* Resume the CPU with the passed device tree node. */
व्योम prom_resumecpu(पूर्णांक cpunode);
#पूर्ण_अगर

/* Power management पूर्णांकerfaces. */

/* Put the current CPU to sleep. */
व्योम prom_sleepself(व्योम);

/* Put the entire प्रणाली to sleep. */
पूर्णांक prom_sleepप्रणाली(व्योम);

/* Initiate a wakeup event. */
पूर्णांक prom_wakeupप्रणाली(व्योम);

/* MMU and memory related OBP पूर्णांकerfaces. */

/* Get unique string identअगरying SIMM at given physical address. */
पूर्णांक prom_getunumber(पूर्णांक syndrome_code,
		    अचिन्हित दीर्घ phys_addr,
		    अक्षर *buf, पूर्णांक buflen);

/* Retain physical memory to the caller across soft resets. */
पूर्णांक prom_retain(स्थिर अक्षर *name, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ align, अचिन्हित दीर्घ *paddr);

/* Load explicit I/D TLB entries पूर्णांकo the calling processor. */
दीर्घ prom_itlb_load(अचिन्हित दीर्घ index,
		    अचिन्हित दीर्घ tte_data,
		    अचिन्हित दीर्घ vaddr);

दीर्घ prom_dtlb_load(अचिन्हित दीर्घ index,
		    अचिन्हित दीर्घ tte_data,
		    अचिन्हित दीर्घ vaddr);

/* Map/Unmap client program address ranges.  First the क्रमmat of
 * the mapping mode argument.
 */
#घोषणा PROM_MAP_WRITE	0x0001 /* Writable */
#घोषणा PROM_MAP_READ	0x0002 /* Readable - sw */
#घोषणा PROM_MAP_EXEC	0x0004 /* Executable - sw */
#घोषणा PROM_MAP_LOCKED	0x0010 /* Locked, use i/dtlb load calls क्रम this instead */
#घोषणा PROM_MAP_CACHED	0x0020 /* Cacheable in both L1 and L2 caches */
#घोषणा PROM_MAP_SE	0x0040 /* Side-Effects */
#घोषणा PROM_MAP_GLOB	0x0080 /* Global */
#घोषणा PROM_MAP_IE	0x0100 /* Invert-Endianness */
#घोषणा PROM_MAP_DEFAULT (PROM_MAP_WRITE | PROM_MAP_READ | PROM_MAP_EXEC | PROM_MAP_CACHED)

पूर्णांक prom_map(पूर्णांक mode, अचिन्हित दीर्घ size,
	     अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ paddr);
व्योम prom_unmap(अचिन्हित दीर्घ size, अचिन्हित दीर्घ vaddr);


/* PROM device tree traversal functions... */

/* Get the child node of the given node, or zero अगर no child exists. */
phandle prom_अ_लोhild(phandle parent_node);

/* Get the next sibling node of the given node, or zero अगर no further
 * siblings exist.
 */
phandle prom_माला_लोibling(phandle node);

/* Get the length, at the passed node, of the given property type.
 * Returns -1 on error (ie. no such property at this node).
 */
पूर्णांक prom_getproplen(phandle thisnode, स्थिर अक्षर *property);

/* Fetch the requested property using the given buffer.  Returns
 * the number of bytes the prom put पूर्णांकo your buffer or -1 on error.
 */
पूर्णांक prom_getproperty(phandle thisnode, स्थिर अक्षर *property,
		     अक्षर *prop_buffer, पूर्णांक propbuf_size);

/* Acquire an पूर्णांकeger property. */
पूर्णांक prom_getपूर्णांक(phandle node, स्थिर अक्षर *property);

/* Acquire an पूर्णांकeger property, with a शेष value. */
पूर्णांक prom_getपूर्णांकशेष(phandle node, स्थिर अक्षर *property, पूर्णांक defval);

/* Acquire a boolean property, 0=FALSE 1=TRUE. */
पूर्णांक prom_getbool(phandle node, स्थिर अक्षर *prop);

/* Acquire a string property, null string on error. */
व्योम prom_माला_लोtring(phandle node, स्थिर अक्षर *prop, अक्षर *buf,
		    पूर्णांक bufsize);

/* Does the passed node have the given "name"? YES=1 NO=0 */
पूर्णांक prom_nodematch(phandle thisnode, स्थिर अक्षर *name);

/* Search all siblings starting at the passed node क्रम "name" matching
 * the given string.  Returns the node on success, zero on failure.
 */
phandle prom_searchsiblings(phandle node_start, स्थिर अक्षर *name);

/* Return the first property type, as a string, क्रम the given node.
 * Returns a null string on error. Buffer should be at least 32B दीर्घ.
 */
अक्षर *prom_firstprop(phandle node, अक्षर *buffer);

/* Returns the next property after the passed property क्रम the given
 * node.  Returns null string on failure. Buffer should be at least 32B दीर्घ.
 */
अक्षर *prom_nextprop(phandle node, स्थिर अक्षर *prev_property, अक्षर *buf);

/* Returns 1 अगर the specअगरied node has given property. */
पूर्णांक prom_node_has_property(phandle node, स्थिर अक्षर *property);

/* Returns phandle of the path specअगरied */
phandle prom_finddevice(स्थिर अक्षर *name);

/* Set the indicated property at the given node with the passed value.
 * Returns the number of bytes of your value that the prom took.
 */
पूर्णांक prom_setprop(phandle node, स्थिर अक्षर *prop_name, अक्षर *prop_value,
		 पूर्णांक value_size);

phandle prom_inst2pkg(पूर्णांक);
व्योम prom_sun4v_guest_soft_state(व्योम);

पूर्णांक prom_ihandle2path(पूर्णांक handle, अक्षर *buffer, पूर्णांक bufsize);

/* Client पूर्णांकerface level routines. */
व्योम p1275_cmd_direct(अचिन्हित दीर्घ *);

#पूर्ण_अगर /* !(__SPARC64_OPLIB_H) */
