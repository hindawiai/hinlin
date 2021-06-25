<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL in-memory console पूर्णांकerface
 *
 * Copyright 2014 IBM Corp.
 */

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/opal.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/barrier.h>

#समावेश "powernv.h"

/* OPAL in-memory console. Defined in OPAL source at core/console.c */
काष्ठा memcons अणु
	__be64 magic;
#घोषणा MEMCONS_MAGIC	0x6630696567726173L
	__be64 obuf_phys;
	__be64 ibuf_phys;
	__be32 obuf_size;
	__be32 ibuf_size;
	__be32 out_pos;
#घोषणा MEMCONS_OUT_POS_WRAP	0x80000000u
#घोषणा MEMCONS_OUT_POS_MASK	0x00ffffffu
	__be32 in_prod;
	__be32 in_cons;
पूर्ण;

अटल काष्ठा memcons *opal_memcons = शून्य;

sमाप_प्रकार memcons_copy(काष्ठा memcons *mc, अक्षर *to, loff_t pos, माप_प्रकार count)
अणु
	स्थिर अक्षर *conbuf;
	sमाप_प्रकार ret;
	माप_प्रकार first_पढ़ो = 0;
	uपूर्णांक32_t out_pos, avail;

	अगर (!mc)
		वापस -ENODEV;

	out_pos = be32_to_cpu(READ_ONCE(mc->out_pos));

	/* Now we've पढ़ो out_pos, put a barrier in beक्रमe पढ़ोing the new
	 * data it poपूर्णांकs to in conbuf. */
	smp_rmb();

	conbuf = phys_to_virt(be64_to_cpu(mc->obuf_phys));

	/* When the buffer has wrapped, पढ़ो from the out_pos marker to the end
	 * of the buffer, and then पढ़ो the reमुख्यing data as in the un-wrapped
	 * हाल. */
	अगर (out_pos & MEMCONS_OUT_POS_WRAP) अणु

		out_pos &= MEMCONS_OUT_POS_MASK;
		avail = be32_to_cpu(mc->obuf_size) - out_pos;

		ret = memory_पढ़ो_from_buffer(to, count, &pos,
				conbuf + out_pos, avail);

		अगर (ret < 0)
			जाओ out;

		first_पढ़ो = ret;
		to += first_पढ़ो;
		count -= first_पढ़ो;
		pos -= avail;

		अगर (count <= 0)
			जाओ out;
	पूर्ण

	/* Sanity check. The firmware should not करो this to us. */
	अगर (out_pos > be32_to_cpu(mc->obuf_size)) अणु
		pr_err("OPAL: memory console corruption. Aborting read.\n");
		वापस -EINVAL;
	पूर्ण

	ret = memory_पढ़ो_from_buffer(to, count, &pos, conbuf, out_pos);

	अगर (ret < 0)
		जाओ out;

	ret += first_पढ़ो;
out:
	वापस ret;
पूर्ण

sमाप_प्रकार opal_msglog_copy(अक्षर *to, loff_t pos, माप_प्रकार count)
अणु
	वापस memcons_copy(opal_memcons, to, pos, count);
पूर्ण

अटल sमाप_प्रकार opal_msglog_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *to,
				loff_t pos, माप_प्रकार count)
अणु
	वापस opal_msglog_copy(to, pos, count);
पूर्ण

अटल काष्ठा bin_attribute opal_msglog_attr = अणु
	.attr = अणु.name = "msglog", .mode = 0400पूर्ण,
	.पढ़ो = opal_msglog_पढ़ो
पूर्ण;

काष्ठा memcons *memcons_init(काष्ठा device_node *node, स्थिर अक्षर *mc_prop_name)
अणु
	u64 mcaddr;
	काष्ठा memcons *mc;

	अगर (of_property_पढ़ो_u64(node, mc_prop_name, &mcaddr)) अणु
		pr_warn("%s property not found, no message log\n",
			mc_prop_name);
		जाओ out_err;
	पूर्ण

	mc = phys_to_virt(mcaddr);
	अगर (!mc) अणु
		pr_warn("memory console address is invalid\n");
		जाओ out_err;
	पूर्ण

	अगर (be64_to_cpu(mc->magic) != MEMCONS_MAGIC) अणु
		pr_warn("memory console version is invalid\n");
		जाओ out_err;
	पूर्ण

	वापस mc;

out_err:
	वापस शून्य;
पूर्ण

u32 memcons_get_size(काष्ठा memcons *mc)
अणु
	वापस be32_to_cpu(mc->ibuf_size) + be32_to_cpu(mc->obuf_size);
पूर्ण

व्योम __init opal_msglog_init(व्योम)
अणु
	opal_memcons = memcons_init(opal_node, "ibm,opal-memcons");
	अगर (!opal_memcons) अणु
		pr_warn("OPAL: memcons failed to load from ibm,opal-memcons\n");
		वापस;
	पूर्ण

	opal_msglog_attr.size = memcons_get_size(opal_memcons);
पूर्ण

व्योम __init opal_msglog_sysfs_init(व्योम)
अणु
	अगर (!opal_memcons) अणु
		pr_warn("OPAL: message log initialisation failed, not creating sysfs entry\n");
		वापस;
	पूर्ण

	अगर (sysfs_create_bin_file(opal_kobj, &opal_msglog_attr) != 0)
		pr_warn("OPAL: sysfs file creation failed\n");
पूर्ण
