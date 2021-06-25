<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 * Copyright (C) 2020 Google, Inc
 */

#अगर_अघोषित _ASM_RISCV_SOC_H
#घोषणा _ASM_RISCV_SOC_H

#समावेश <linux/of.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>

#घोषणा SOC_EARLY_INIT_DECLARE(name, compat, fn)			\
	अटल स्थिर काष्ठा of_device_id __soc_early_init__##name	\
		__used __section("__soc_early_init_table")		\
		 = अणु .compatible = compat, .data = fn  पूर्ण

व्योम soc_early_init(व्योम);

बाह्य अचिन्हित दीर्घ __soc_early_init_table_start;
बाह्य अचिन्हित दीर्घ __soc_early_init_table_end;

#पूर्ण_अगर
