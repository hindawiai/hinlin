<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2021 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/bcm47xx_nvram.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "ofpart_linksys_ns.h"

#घोषणा NVRAM_BOOT_PART		"bootpartition"

अटल पूर्णांक ofpart_linksys_ns_bootpartition(व्योम)
अणु
	अक्षर buf[4];
	पूर्णांक bootpartition;

	/* Check CFE environment variable */
	अगर (bcm47xx_nvram_दो_पर्या(NVRAM_BOOT_PART, buf, माप(buf)) > 0) अणु
		अगर (!kstrtoपूर्णांक(buf, 0, &bootpartition))
			वापस bootpartition;
		pr_warn("Failed to parse %s value \"%s\"\n", NVRAM_BOOT_PART,
			buf);
	पूर्ण अन्यथा अणु
		pr_warn("Failed to get NVRAM \"%s\"\n", NVRAM_BOOT_PART);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक linksys_ns_partitions_post_parse(काष्ठा mtd_info *mtd,
				     काष्ठा mtd_partition *parts,
				     पूर्णांक nr_parts)
अणु
	पूर्णांक bootpartition = ofpart_linksys_ns_bootpartition();
	पूर्णांक trx_idx = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nr_parts; i++) अणु
		अगर (of_device_is_compatible(parts[i].of_node, "linksys,ns-firmware")) अणु
			अगर (trx_idx++ == bootpartition)
				parts[i].name = "firmware";
			अन्यथा
				parts[i].name = "backup";
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
