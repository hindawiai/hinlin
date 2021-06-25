<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2021 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "ofpart_bcm4908.h"

#घोषणा BLPARAMS_FW_OFFSET		"NAND_RFS_OFS"

अटल दीर्घ दीर्घ bcm4908_partitions_fw_offset(व्योम)
अणु
	काष्ठा device_node *root;
	काष्ठा property *prop;
	स्थिर अक्षर *s;

	root = of_find_node_by_path("/");
	अगर (!root)
		वापस -ENOENT;

	of_property_क्रम_each_string(root, "brcm_blparms", prop, s) अणु
		माप_प्रकार len = म_माप(BLPARAMS_FW_OFFSET);
		अचिन्हित दीर्घ offset;
		पूर्णांक err;

		अगर (म_भेदन(s, BLPARAMS_FW_OFFSET, len) || s[len] != '=')
			जारी;

		err = kम_से_अदीर्घ(s + len + 1, 0, &offset);
		अगर (err) अणु
			pr_err("failed to parse %s\n", s + len + 1);
			वापस err;
		पूर्ण

		वापस offset << 10;
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक bcm4908_partitions_post_parse(काष्ठा mtd_info *mtd, काष्ठा mtd_partition *parts, पूर्णांक nr_parts)
अणु
	दीर्घ दीर्घ fw_offset;
	पूर्णांक i;

	fw_offset = bcm4908_partitions_fw_offset();

	क्रम (i = 0; i < nr_parts; i++) अणु
		अगर (of_device_is_compatible(parts[i].of_node, "brcm,bcm4908-firmware")) अणु
			अगर (fw_offset < 0 || parts[i].offset == fw_offset)
				parts[i].name = "firmware";
			अन्यथा
				parts[i].name = "backup";
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
