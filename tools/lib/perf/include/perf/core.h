<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_CORE_H
#घोषणा __LIBPERF_CORE_H

#समावेश <मानकतर्क.स>

#अगर_अघोषित LIBPERF_API
#घोषणा LIBPERF_API __attribute__((visibility("default")))
#पूर्ण_अगर

क्रमागत libperf_prपूर्णांक_level अणु
	LIBPERF_ERR,
	LIBPERF_WARN,
	LIBPERF_INFO,
	LIBPERF_DEBUG,
	LIBPERF_DEBUG2,
	LIBPERF_DEBUG3,
पूर्ण;

प्रकार पूर्णांक (*libperf_prपूर्णांक_fn_t)(क्रमागत libperf_prपूर्णांक_level level,
				  स्थिर अक्षर *, बहु_सूची ap);

LIBPERF_API व्योम libperf_init(libperf_prपूर्णांक_fn_t fn);

#पूर्ण_अगर /* __LIBPERF_CORE_H */
