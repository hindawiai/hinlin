<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/bug.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/of_fdt.h>

व्योम __init early_init_devtree(व्योम *params)
अणु
	अगर (!params || !early_init_dt_scan(params)) अणु
		pr_crit("\n"
			"Error: invalid device tree blob at (virtual address 0x%p)\n"
			"\nPlease check your bootloader.", params);

		BUG_ON(1);
	पूर्ण

	dump_stack_set_arch_desc("%s (DT)", of_flat_dt_get_machine_name());
पूर्ण
