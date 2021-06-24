<शैली गुरु>
/*
 * Support क्रम भव IRQ subgroups debugfs mapping.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * Modelled after arch/घातerpc/kernel/irq.c.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/debugfs.h>
#समावेश "internals.h"

अटल पूर्णांक पूर्णांकc_irq_xlate_show(काष्ठा seq_file *m, व्योम *priv)
अणु
	पूर्णांक i;

	seq_म_लिखो(m, "%-5s  %-7s  %-15s\n", "irq", "enum", "chip name");

	क्रम (i = 1; i < nr_irqs; i++) अणु
		काष्ठा पूर्णांकc_map_entry *entry = पूर्णांकc_irq_xlate_get(i);
		काष्ठा पूर्णांकc_desc_पूर्णांक *desc = entry->desc;

		अगर (!desc)
			जारी;

		seq_म_लिखो(m, "%5d  ", i);
		seq_म_लिखो(m, "0x%05x  ", entry->क्रमागत_id);
		seq_म_लिखो(m, "%-15s\n", desc->chip.name);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(पूर्णांकc_irq_xlate);

अटल पूर्णांक __init पूर्णांकc_irq_xlate_init(व्योम)
अणु
	/*
	 * XXX.. use arch_debugfs_dir here when all of the पूर्णांकc users are
	 * converted.
	 */
	अगर (debugfs_create_file("intc_irq_xlate", S_IRUGO, शून्य, शून्य,
				&पूर्णांकc_irq_xlate_fops) == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
fs_initcall(पूर्णांकc_irq_xlate_init);
