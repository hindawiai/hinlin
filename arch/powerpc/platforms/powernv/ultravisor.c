<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ultravisor high level पूर्णांकerfaces
 *
 * Copyright 2019, IBM Corporation.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/machdep.h>

#समावेश "powernv.h"

अटल काष्ठा kobject *ultravisor_kobj;

पूर्णांक __init early_init_dt_scan_ultravisor(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					 पूर्णांक depth, व्योम *data)
अणु
	अगर (!of_flat_dt_is_compatible(node, "ibm,ultravisor"))
		वापस 0;

	घातerpc_firmware_features |= FW_FEATURE_ULTRAVISOR;
	pr_debug("Ultravisor detected!\n");
	वापस 1;
पूर्ण

अटल काष्ठा memcons *uv_memcons;

अटल sमाप_प्रकार uv_msglog_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr, अक्षर *to,
			      loff_t pos, माप_प्रकार count)
अणु
	वापस memcons_copy(uv_memcons, to, pos, count);
पूर्ण

अटल काष्ठा bin_attribute uv_msglog_attr = अणु
	.attr = अणु.name = "msglog", .mode = 0400पूर्ण,
	.पढ़ो = uv_msglog_पढ़ो
पूर्ण;

अटल पूर्णांक __init uv_init(व्योम)
अणु
	काष्ठा device_node *node;

	अगर (!firmware_has_feature(FW_FEATURE_ULTRAVISOR))
		वापस 0;

	node = of_find_compatible_node(शून्य, शून्य, "ibm,uv-firmware");
	अगर (!node)
		वापस -ENODEV;

	uv_memcons = memcons_init(node, "memcons");
	अगर (!uv_memcons)
		वापस -ENOENT;

	uv_msglog_attr.size = memcons_get_size(uv_memcons);

	ultravisor_kobj = kobject_create_and_add("ultravisor", firmware_kobj);
	अगर (!ultravisor_kobj)
		वापस -ENOMEM;

	वापस sysfs_create_bin_file(ultravisor_kobj, &uv_msglog_attr);
पूर्ण
machine_subsys_initcall(घातernv, uv_init);
