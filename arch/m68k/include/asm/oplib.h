<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * oplib.h:  Describes the पूर्णांकerface and available routines in the
 *           Linux Prom library.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित __SPARC_OPLIB_H
#घोषणा __SPARC_OPLIB_H

#समावेश <यंत्र/खोलोprom.h>

/* The master romvec poपूर्णांकer... */
बाह्य काष्ठा linux_romvec *romvec;

/* Enumeration to describe the prom major version we have detected. */
क्रमागत prom_major_version अणु
	PROM_V0,      /* Original sun4c V0 prom */
	PROM_V2,      /* sun4c and early sun4m V2 prom */
	PROM_V3,      /* sun4m and later, up to sun4d/sun4e machines V3 */
	PROM_P1275,   /* IEEE compliant ISA based Sun PROM, only sun4u */
पूर्ण;

बाह्य क्रमागत prom_major_version prom_vers;
/* Revision, and firmware revision. */
बाह्य अचिन्हित पूर्णांक prom_rev, prom_prev;

/* Root node of the prom device tree, this stays स्थिरant after
 * initialization is complete.
 */
बाह्य पूर्णांक prom_root_node;

/* Poपूर्णांकer to prom काष्ठाure containing the device tree traversal
 * and usage utility functions.  Only prom-lib should use these,
 * users use the पूर्णांकerface defined by the library only!
 */
बाह्य काष्ठा linux_nodeops *prom_nodeops;

/* The functions... */

/* You must call prom_init() beक्रमe using any of the library services,
 * preferably as early as possible.  Pass it the romvec poपूर्णांकer.
 */
बाह्य व्योम prom_init(काष्ठा linux_romvec *rom_ptr);

/* Boot argument acquisition, वापसs the boot command line string. */
बाह्य अक्षर *prom_getbootargs(व्योम);

/* Device utilities. */

/* Map and unmap devices in IO space at भव addresses. Note that the
 * भव address you pass is a request and the prom may put your mappings
 * somewhere अन्यथा, so check your वापस value as that is where your new
 * mappings really are!
 *
 * Another note, these are only available on V2 or higher proms!
 */
बाह्य अक्षर *prom_mapio(अक्षर *virt_hपूर्णांक, पूर्णांक io_space, अचिन्हित पूर्णांक phys_addr, अचिन्हित पूर्णांक num_bytes);
बाह्य व्योम prom_unmapio(अक्षर *virt_addr, अचिन्हित पूर्णांक num_bytes);

/* Device operations. */

/* Open the device described by the passed string.  Note, that the क्रमmat
 * of the string is dअगरferent on V0 vs. V2->higher proms.  The caller must
 * know what he/she is करोing!  Returns the device descriptor, an पूर्णांक.
 */
बाह्य पूर्णांक prom_devखोलो(अक्षर *device_string);

/* Close a previously खोलोed device described by the passed पूर्णांकeger
 * descriptor.
 */
बाह्य पूर्णांक prom_devबंद(पूर्णांक device_handle);

/* Do a seek operation on the device described by the passed पूर्णांकeger
 * descriptor.
 */
बाह्य व्योम prom_seek(पूर्णांक device_handle, अचिन्हित पूर्णांक seek_hival,
		      अचिन्हित पूर्णांक seek_lowval);

/* Machine memory configuration routine. */

/* This function वापसs a V0 क्रमmat memory descriptor table, it has three
 * entries.  One क्रम the total amount of physical ram on the machine, one
 * क्रम the amount of physical ram available, and one describing the भव
 * areas which are allocated by the prom.  So, in a sense the physical
 * available is a calculation of the total physical minus the physical mapped
 * by the prom with भव mappings.
 *
 * These lists are वापसed pre-sorted, this should make your lअगरe easier
 * since the prom itself is way too lazy to करो such nice things.
 */
बाह्य काष्ठा linux_mem_v0 *prom_meminfo(व्योम);

/* Miscellaneous routines, करोn't really fit in any category per se. */

/* Reboot the machine with the command line passed. */
बाह्य व्योम prom_reboot(अक्षर *boot_command);

/* Evaluate the क्रमth string passed. */
बाह्य व्योम prom_feval(अक्षर *क्रमth_string);

/* Enter the prom, with possibility of continuation with the 'go'
 * command in newer proms.
 */
बाह्य व्योम prom_cmdline(व्योम);

/* Enter the prom, with no chance of continuation क्रम the stand-alone
 * which calls this.
 */
बाह्य व्योम prom_halt(व्योम);

/* Set the PROM 'sync' callback function to the passed function poपूर्णांकer.
 * When the user gives the 'sync' command at the prom prompt जबतक the
 * kernel is still active, the prom will call this routine.
 *
 * XXX The arguments are dअगरferent on V0 vs. V2->higher proms, grrr! XXX
 */
प्रकार व्योम (*sync_func_t)(व्योम);
बाह्य व्योम prom_setsync(sync_func_t func_ptr);

/* Acquire the IDPROM of the root node in the prom device tree.  This
 * माला_लो passed a buffer where you would like it stuffed.  The वापस value
 * is the क्रमmat type of this idprom or 0xff on error.
 */
बाह्य अचिन्हित अक्षर prom_get_idprom(अक्षर *idp_buffer, पूर्णांक idpbuf_size);

/* Get the prom major version. */
बाह्य पूर्णांक prom_version(व्योम);

/* Get the prom plugin revision. */
बाह्य पूर्णांक prom_getrev(व्योम);

/* Get the prom firmware revision. */
बाह्य पूर्णांक prom_getprev(व्योम);

/* Character operations to/from the console.... */

/* Non-blocking get अक्षरacter from console. */
बाह्य पूर्णांक prom_nbअक्षर_लो(व्योम);

/* Non-blocking put अक्षरacter to console. */
बाह्य पूर्णांक prom_nbअक्षर_दो(अक्षर अक्षरacter);

/* Blocking get अक्षरacter from console. */
बाह्य अक्षर prom_अक्षर_लो(व्योम);

/* Blocking put अक्षरacter to console. */
बाह्य व्योम prom_अक्षर_दो(अक्षर अक्षरacter);

/* Prom's internal printf routine, don't use in kernel/boot code. */
व्योम prom_म_लिखो(अक्षर *fmt, ...);

/* Query क्रम input device type */

क्रमागत prom_input_device अणु
	PROMDEV_IKBD,			/* input from keyboard */
	PROMDEV_ITTYA,			/* input from ttya */
	PROMDEV_ITTYB,			/* input from ttyb */
	PROMDEV_I_UNK,
पूर्ण;

बाह्य क्रमागत prom_input_device prom_query_input_device(व्योम);

/* Query क्रम output device type */

क्रमागत prom_output_device अणु
	PROMDEV_OSCREEN,		/* to screen */
	PROMDEV_OTTYA,			/* to ttya */
	PROMDEV_OTTYB,			/* to ttyb */
	PROMDEV_O_UNK,
पूर्ण;

बाह्य क्रमागत prom_output_device prom_query_output_device(व्योम);

/* Multiprocessor operations... */

/* Start the CPU with the given device tree node, context table, and context
 * at the passed program counter.
 */
बाह्य पूर्णांक prom_startcpu(पूर्णांक cpunode, काष्ठा linux_prom_रेजिस्टरs *context_table,
			 पूर्णांक context, अक्षर *program_counter);

/* Stop the CPU with the passed device tree node. */
बाह्य पूर्णांक prom_stopcpu(पूर्णांक cpunode);

/* Idle the CPU with the passed device tree node. */
बाह्य पूर्णांक prom_idlecpu(पूर्णांक cpunode);

/* Re-Start the CPU with the passed device tree node. */
बाह्य पूर्णांक prom_restartcpu(पूर्णांक cpunode);

/* PROM memory allocation facilities... */

/* Allocated at possibly the given भव address a chunk of the
 * indicated size.
 */
बाह्य अक्षर *prom_alloc(अक्षर *virt_hपूर्णांक, अचिन्हित पूर्णांक size);

/* Free a previously allocated chunk. */
बाह्य व्योम prom_मुक्त(अक्षर *virt_addr, अचिन्हित पूर्णांक size);

/* Sun4/sun4c specअगरic memory-management startup hook. */

/* Map the passed segment in the given context at the passed
 * भव address.
 */
बाह्य व्योम prom_माला_दोegment(पूर्णांक context, अचिन्हित दीर्घ virt_addr,
			    पूर्णांक physical_segment);

/* PROM device tree traversal functions... */

/* Get the child node of the given node, or zero अगर no child exists. */
बाह्य पूर्णांक prom_अ_लोhild(पूर्णांक parent_node);

/* Get the next sibling node of the given node, or zero अगर no further
 * siblings exist.
 */
बाह्य पूर्णांक prom_माला_लोibling(पूर्णांक node);

/* Get the length, at the passed node, of the given property type.
 * Returns -1 on error (ie. no such property at this node).
 */
बाह्य पूर्णांक prom_getproplen(पूर्णांक thisnode, अक्षर *property);

/* Fetch the requested property using the given buffer.  Returns
 * the number of bytes the prom put पूर्णांकo your buffer or -1 on error.
 */
बाह्य पूर्णांक prom_getproperty(पूर्णांक thisnode, अक्षर *property,
			    अक्षर *prop_buffer, पूर्णांक propbuf_size);

/* Acquire an पूर्णांकeger property. */
बाह्य पूर्णांक prom_getपूर्णांक(पूर्णांक node, अक्षर *property);

/* Acquire an पूर्णांकeger property, with a शेष value. */
बाह्य पूर्णांक prom_getपूर्णांकशेष(पूर्णांक node, अक्षर *property, पूर्णांक defval);

/* Acquire a boolean property, 0=FALSE 1=TRUE. */
बाह्य पूर्णांक prom_getbool(पूर्णांक node, अक्षर *prop);

/* Acquire a string property, null string on error. */
बाह्य व्योम prom_माला_लोtring(पूर्णांक node, अक्षर *prop, अक्षर *buf, पूर्णांक bufsize);

/* Does the passed node have the given "name"? YES=1 NO=0 */
बाह्य पूर्णांक prom_nodematch(पूर्णांक thisnode, अक्षर *name);

/* Search all siblings starting at the passed node क्रम "name" matching
 * the given string.  Returns the node on success, zero on failure.
 */
बाह्य पूर्णांक prom_searchsiblings(पूर्णांक node_start, अक्षर *name);

/* Return the first property type, as a string, क्रम the given node.
 * Returns a null string on error.
 */
बाह्य अक्षर *prom_firstprop(पूर्णांक node);

/* Returns the next property after the passed property क्रम the given
 * node.  Returns null string on failure.
 */
बाह्य अक्षर *prom_nextprop(पूर्णांक node, अक्षर *prev_property);

/* Returns 1 अगर the specअगरied node has given property. */
बाह्य पूर्णांक prom_node_has_property(पूर्णांक node, अक्षर *property);

/* Set the indicated property at the given node with the passed value.
 * Returns the number of bytes of your value that the prom took.
 */
बाह्य पूर्णांक prom_setprop(पूर्णांक node, अक्षर *prop_name, अक्षर *prop_value,
			पूर्णांक value_size);

बाह्य पूर्णांक prom_pathtoinode(अक्षर *path);
बाह्य पूर्णांक prom_inst2pkg(पूर्णांक);

/* Dorking with Bus ranges... */

/* Adjust reg values with the passed ranges. */
बाह्य व्योम prom_adjust_regs(काष्ठा linux_prom_रेजिस्टरs *regp, पूर्णांक nregs,
			     काष्ठा linux_prom_ranges *rangep, पूर्णांक nranges);

/* Adjust child ranges with the passed parent ranges. */
बाह्य व्योम prom_adjust_ranges(काष्ठा linux_prom_ranges *cranges, पूर्णांक ncranges,
			       काष्ठा linux_prom_ranges *pranges, पूर्णांक npranges);

/* Apply promlib probed OBIO ranges to रेजिस्टरs. */
बाह्य व्योम prom_apply_obio_ranges(काष्ठा linux_prom_रेजिस्टरs *obioregs, पूर्णांक nregs);

/* Apply ranges of any prom node (and optionally parent node as well) to रेजिस्टरs. */
बाह्य व्योम prom_apply_generic_ranges(पूर्णांक node, पूर्णांक parent,
				      काष्ठा linux_prom_रेजिस्टरs *sbusregs, पूर्णांक nregs);


#पूर्ण_अगर /* !(__SPARC_OPLIB_H) */
