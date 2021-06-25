<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _RALINK_COMMON_H__
#घोषणा _RALINK_COMMON_H__

#घोषणा RAMIPS_SYS_TYPE_LEN	32

काष्ठा ralink_soc_info अणु
	अचिन्हित अक्षर sys_type[RAMIPS_SYS_TYPE_LEN];
	अचिन्हित अक्षर *compatible;

	अचिन्हित दीर्घ mem_base;
	अचिन्हित दीर्घ mem_size;
	अचिन्हित दीर्घ mem_size_min;
	अचिन्हित दीर्घ mem_size_max;
	व्योम (*mem_detect)(व्योम);
पूर्ण;
बाह्य काष्ठा ralink_soc_info soc_info;

बाह्य व्योम ralink_of_remap(व्योम);

बाह्य व्योम ralink_clk_init(व्योम);
बाह्य व्योम ralink_clk_add(स्थिर अक्षर *dev, अचिन्हित दीर्घ rate);

बाह्य व्योम ralink_rst_init(व्योम);

बाह्य व्योम __init prom_soc_init(काष्ठा ralink_soc_info *soc_info);

__iomem व्योम *plat_of_remap_node(स्थिर अक्षर *node);

#पूर्ण_अगर /* _RALINK_COMMON_H__ */
