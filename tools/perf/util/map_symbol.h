<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __PERF_MAP_SYMBOL
#घोषणा __PERF_MAP_SYMBOL 1

#समावेश <linux/types.h>

काष्ठा maps;
काष्ठा map;
काष्ठा symbol;

काष्ठा map_symbol अणु
	काष्ठा maps   *maps;
	काष्ठा map    *map;
	काष्ठा symbol *sym;
पूर्ण;

काष्ठा addr_map_symbol अणु
	काष्ठा map_symbol ms;
	u64	      addr;
	u64	      al_addr;
	u64	      phys_addr;
	u64	      data_page_size;
पूर्ण;
#पूर्ण_अगर // __PERF_MAP_SYMBOL
