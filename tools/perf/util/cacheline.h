<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_CACHELINE_H
#घोषणा PERF_CACHELINE_H

#समावेश <linux/compiler.h>

पूर्णांक __pure cacheline_size(व्योम);

अटल अंतरभूत u64 cl_address(u64 address)
अणु
	/* वापस the cacheline of the address */
	वापस (address & ~(cacheline_size() - 1));
पूर्ण

अटल अंतरभूत u64 cl_offset(u64 address)
अणु
	/* वापस the cacheline of the address */
	वापस (address & (cacheline_size() - 1));
पूर्ण

#पूर्ण_अगर // PERF_CACHELINE_H
