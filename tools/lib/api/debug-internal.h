<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __API_DEBUG_INTERNAL_H__
#घोषणा __API_DEBUG_INTERNAL_H__

#समावेश "debug.h"

#घोषणा __pr(func, fmt, ...)	\
करो अणु				\
	अगर ((func))		\
		(func)("libapi: " fmt, ##__VA_ARGS__); \
पूर्ण जबतक (0)

बाह्य libapi_prपूर्णांक_fn_t __pr_warn;
बाह्य libapi_prपूर्णांक_fn_t __pr_info;
बाह्य libapi_prपूर्णांक_fn_t __pr_debug;

#घोषणा pr_warn(fmt, ...)	__pr(__pr_warn, fmt, ##__VA_ARGS__)
#घोषणा pr_info(fmt, ...)	__pr(__pr_info, fmt, ##__VA_ARGS__)
#घोषणा pr_debug(fmt, ...)	__pr(__pr_debug, fmt, ##__VA_ARGS__)

#पूर्ण_अगर /* __API_DEBUG_INTERNAL_H__ */
