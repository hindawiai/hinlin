<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>

/*
 * stores the physical address of elf header of crash image
 *
 * Note: elfcorehdr_addr is not just limited to vmcore. It is also used by
 * is_kdump_kernel() to determine अगर we are booting after a panic. Hence put
 * it under CONFIG_CRASH_DUMP and not CONFIG_PROC_VMCORE.
 */
अचिन्हित दीर्घ दीर्घ elfcorehdr_addr = ELFCORE_ADDR_MAX;
EXPORT_SYMBOL_GPL(elfcorehdr_addr);

/*
 * stores the size of elf header of crash image
 */
अचिन्हित दीर्घ दीर्घ elfcorehdr_size;

/*
 * elfcorehdr= specअगरies the location of elf core header stored by the crashed
 * kernel. This option will be passed by kexec loader to the capture kernel.
 *
 * Syntax: elfcorehdr=[size[KMG]@]offset[KMG]
 */
अटल पूर्णांक __init setup_elfcorehdr(अक्षर *arg)
अणु
	अक्षर *end;
	अगर (!arg)
		वापस -EINVAL;
	elfcorehdr_addr = memparse(arg, &end);
	अगर (*end == '@') अणु
		elfcorehdr_size = elfcorehdr_addr;
		elfcorehdr_addr = memparse(end + 1, &end);
	पूर्ण
	वापस end > arg ? 0 : -EINVAL;
पूर्ण
early_param("elfcorehdr", setup_elfcorehdr);
