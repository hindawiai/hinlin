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
#समावेश <linux/spinlock.h>
#समावेश <linux/compiler.h>

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
बाह्य phandle prom_root_node;

/* Poपूर्णांकer to prom काष्ठाure containing the device tree traversal
 * and usage utility functions.  Only prom-lib should use these,
 * users use the पूर्णांकerface defined by the library only!
 */
बाह्य काष्ठा linux_nodeops *prom_nodeops;

/* The functions... */

/* You must call prom_init() beक्रमe using any of the library services,
 * preferably as early as possible.  Pass it the romvec poपूर्णांकer.
 */
व्योम prom_init(काष्ठा linux_romvec *rom_ptr);

/* Boot argument acquisition, वापसs the boot command line string. */
अक्षर *prom_getbootargs(व्योम);

/* Miscellaneous routines, करोn't really fit in any category per se. */

/* Reboot the machine with the command line passed. */
व्योम prom_reboot(अक्षर *boot_command);

/* Evaluate the क्रमth string passed. */
व्योम prom_feval(अक्षर *क्रमth_string);

/* Enter the prom, with possibility of continuation with the 'go'
 * command in newer proms.
 */
व्योम prom_cmdline(व्योम);

/* Enter the prom, with no chance of continuation क्रम the stand-alone
 * which calls this.
 */
व्योम __noवापस prom_halt(व्योम);

/* Set the PROM 'sync' callback function to the passed function poपूर्णांकer.
 * When the user gives the 'sync' command at the prom prompt जबतक the
 * kernel is still active, the prom will call this routine.
 *
 * XXX The arguments are dअगरferent on V0 vs. V2->higher proms, grrr! XXX
 */
प्रकार व्योम (*sync_func_t)(व्योम);
व्योम prom_setsync(sync_func_t func_ptr);

/* Acquire the IDPROM of the root node in the prom device tree.  This
 * माला_लो passed a buffer where you would like it stuffed.  The वापस value
 * is the क्रमmat type of this idprom or 0xff on error.
 */
अचिन्हित अक्षर prom_get_idprom(अक्षर *idp_buffer, पूर्णांक idpbuf_size);

/* Get the prom major version. */
पूर्णांक prom_version(व्योम);

/* Get the prom plugin revision. */
पूर्णांक prom_getrev(व्योम);

/* Get the prom firmware revision. */
पूर्णांक prom_getprev(व्योम);

/* Write a buffer of अक्षरacters to the console. */
व्योम prom_console_ग_लिखो_buf(स्थिर अक्षर *buf, पूर्णांक len);

/* Prom's internal routines, don't use in kernel/boot code. */
__म_लिखो(1, 2) व्योम prom_म_लिखो(स्थिर अक्षर *fmt, ...);
व्योम prom_ग_लिखो(स्थिर अक्षर *buf, अचिन्हित पूर्णांक len);

/* Multiprocessor operations... */

/* Start the CPU with the given device tree node, context table, and context
 * at the passed program counter.
 */
पूर्णांक prom_startcpu(पूर्णांक cpunode, काष्ठा linux_prom_रेजिस्टरs *context_table,
		  पूर्णांक context, अक्षर *program_counter);

/* Initialize the memory lists based upon the prom version. */
व्योम prom_meminit(व्योम);

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
पूर्णांक __must_check prom_getproperty(phandle thisnode, स्थिर अक्षर *property,
				  अक्षर *prop_buffer, पूर्णांक propbuf_size);

/* Acquire an पूर्णांकeger property. */
पूर्णांक prom_getपूर्णांक(phandle node, अक्षर *property);

/* Acquire an पूर्णांकeger property, with a शेष value. */
पूर्णांक prom_getपूर्णांकशेष(phandle node, अक्षर *property, पूर्णांक defval);

/* Acquire a boolean property, 0=FALSE 1=TRUE. */
पूर्णांक prom_getbool(phandle node, अक्षर *prop);

/* Acquire a string property, null string on error. */
व्योम prom_माला_लोtring(phandle node, अक्षर *prop, अक्षर *buf, पूर्णांक bufsize);

/* Search all siblings starting at the passed node क्रम "name" matching
 * the given string.  Returns the node on success, zero on failure.
 */
phandle prom_searchsiblings(phandle node_start, अक्षर *name);

/* Returns the next property after the passed property क्रम the given
 * node.  Returns null string on failure.
 */
अक्षर *prom_nextprop(phandle node, अक्षर *prev_property, अक्षर *buffer);

/* Returns phandle of the path specअगरied */
phandle prom_finddevice(अक्षर *name);

/* Set the indicated property at the given node with the passed value.
 * Returns the number of bytes of your value that the prom took.
 */
पूर्णांक prom_setprop(phandle node, स्थिर अक्षर *prop_name, अक्षर *prop_value,
		 पूर्णांक value_size);

phandle prom_inst2pkg(पूर्णांक);

/* Dorking with Bus ranges... */

/* Apply promlib probes OBIO ranges to रेजिस्टरs. */
व्योम prom_apply_obio_ranges(काष्ठा linux_prom_रेजिस्टरs *obioregs, पूर्णांक nregs);

/* Apply ranges of any prom node (and optionally parent node as well) to रेजिस्टरs. */
व्योम prom_apply_generic_ranges(phandle node, phandle parent,
			       काष्ठा linux_prom_रेजिस्टरs *sbusregs, पूर्णांक nregs);

व्योम prom_ranges_init(व्योम);

/* CPU probing helpers.  */
पूर्णांक cpu_find_by_instance(पूर्णांक instance, phandle *prom_node, पूर्णांक *mid);
पूर्णांक cpu_find_by_mid(पूर्णांक mid, phandle *prom_node);
पूर्णांक cpu_get_hwmid(phandle prom_node);

बाह्य spinlock_t prom_lock;

#पूर्ण_अगर /* !(__SPARC_OPLIB_H) */
