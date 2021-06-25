<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/wbflush.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/prom.h>

#समावेश <loongson.h>

व्योम *loongson_fdt_blob;

अटल व्योम wbflush_loongson(व्योम)
अणु
	यंत्र(".set\tpush\n\t"
	    ".set\tnoreorder\n\t"
	    ".set mips3\n\t"
	    "sync\n\t"
	    "nop\n\t"
	    ".set\tpop\n\t"
	    ".set mips0\n\t");
पूर्ण

व्योम (*__wbflush)(व्योम) = wbflush_loongson;
EXPORT_SYMBOL(__wbflush);

व्योम __init plat_mem_setup(व्योम)
अणु
	अगर (loongson_fdt_blob)
		__dt_setup_arch(loongson_fdt_blob);
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	अगर (!initial_boot_params)
		वापस;

	unflatten_and_copy_device_tree();
पूर्ण
