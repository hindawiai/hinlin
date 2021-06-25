<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_H
#घोषणा __LIBPERF_INTERNAL_H

#समावेश <perf/core.h>

व्योम libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
		   स्थिर अक्षर *क्रमmat, ...)
	__attribute__((क्रमmat(म_लिखो, 2, 3)));

#घोषणा __pr(level, fmt, ...)   \
करो अणु                            \
	libperf_prपूर्णांक(level, "libperf: " fmt, ##__VA_ARGS__);     \
पूर्ण जबतक (0)

#घोषणा pr_err(fmt, ...)        __pr(LIBPERF_ERR, fmt, ##__VA_ARGS__)
#घोषणा pr_warning(fmt, ...)    __pr(LIBPERF_WARN, fmt, ##__VA_ARGS__)
#घोषणा pr_info(fmt, ...)       __pr(LIBPERF_INFO, fmt, ##__VA_ARGS__)
#घोषणा pr_debug(fmt, ...)      __pr(LIBPERF_DEBUG, fmt, ##__VA_ARGS__)
#घोषणा pr_debug2(fmt, ...)     __pr(LIBPERF_DEBUG2, fmt, ##__VA_ARGS__)
#घोषणा pr_debug3(fmt, ...)     __pr(LIBPERF_DEBUG3, fmt, ##__VA_ARGS__)

#पूर्ण_अगर /* __LIBPERF_INTERNAL_H */
