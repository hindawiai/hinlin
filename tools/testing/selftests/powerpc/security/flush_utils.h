<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

/*
 * Copyright 2018 IBM Corporation.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_SECURITY_FLUSH_UTILS_H
#घोषणा _SELFTESTS_POWERPC_SECURITY_FLUSH_UTILS_H

#घोषणा CACHELINE_SIZE 128

#घोषणा PERF_L1D_READ_MISS_CONFIG	((PERF_COUNT_HW_CACHE_L1D) | 		\
					(PERF_COUNT_HW_CACHE_OP_READ << 8) |	\
					(PERF_COUNT_HW_CACHE_RESULT_MISS << 16))

व्योम syscall_loop(अक्षर *p, अचिन्हित दीर्घ iterations,
		  अचिन्हित दीर्घ zero_size);

व्योम syscall_loop_uaccess(अक्षर *p, अचिन्हित दीर्घ iterations,
			  अचिन्हित दीर्घ zero_size);

व्योम set_dscr(अचिन्हित दीर्घ val);

#पूर्ण_अगर /* _SELFTESTS_POWERPC_SECURITY_FLUSH_UTILS_H */
