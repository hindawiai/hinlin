<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device tree support
 *
 * Copyright (C) 2013, 2015 Altera Corporation
 * Copyright (C) 2010 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on MIPS support क्रम CONFIG_OF device tree support
 *
 * Copyright (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/sections.h>

व्योम __init early_init_devtree(व्योम *params)
अणु
	__be32 *dtb = (u32 *)__dtb_start;
#अगर defined(CONFIG_NIOS2_DTB_AT_PHYS_ADDR)
	अगर (be32_to_cpup((__be32 *)CONFIG_NIOS2_DTB_PHYS_ADDR) ==
		 OF_DT_HEADER) अणु
		params = (व्योम *)CONFIG_NIOS2_DTB_PHYS_ADDR;
		early_init_dt_scan(params);
		वापस;
	पूर्ण
#पूर्ण_अगर
	अगर (be32_to_cpu((__be32) *dtb) == OF_DT_HEADER)
		params = (व्योम *)__dtb_start;

	early_init_dt_scan(params);
पूर्ण
