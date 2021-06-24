<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/init.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/soc.h>

/*
 * This is called extremly early, beक्रमe parse_dtb(), to allow initializing
 * SoC hardware beक्रमe memory or any device driver initialization.
 */
व्योम __init soc_early_init(व्योम)
अणु
	व्योम (*early_fn)(स्थिर व्योम *fdt);
	स्थिर काष्ठा of_device_id *s;
	स्थिर व्योम *fdt = dtb_early_va;

	क्रम (s = (व्योम *)&__soc_early_init_table_start;
	     (व्योम *)s < (व्योम *)&__soc_early_init_table_end; s++) अणु
		अगर (!fdt_node_check_compatible(fdt, 0, s->compatible)) अणु
			early_fn = s->data;
			early_fn(fdt);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
