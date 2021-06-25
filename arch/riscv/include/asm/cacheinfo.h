<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 SiFive
 */

#अगर_अघोषित _ASM_RISCV_CACHEINFO_H
#घोषणा _ASM_RISCV_CACHEINFO_H

#समावेश <linux/cacheinfo.h>

काष्ठा riscv_cacheinfo_ops अणु
	स्थिर काष्ठा attribute_group * (*get_priv_group)(काष्ठा cacheinfo
							*this_leaf);
पूर्ण;

व्योम riscv_set_cacheinfo_ops(काष्ठा riscv_cacheinfo_ops *ops);
uपूर्णांकptr_t get_cache_size(u32 level, क्रमागत cache_type type);
uपूर्णांकptr_t get_cache_geometry(u32 level, क्रमागत cache_type type);

#पूर्ण_अगर /* _ASM_RISCV_CACHEINFO_H */
