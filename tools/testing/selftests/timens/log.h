<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __SELFTEST_TIMENS_LOG_H__
#घोषणा __SELFTEST_TIMENS_LOG_H__

#घोषणा pr_msg(fmt, lvl, ...)						\
	ksft_prपूर्णांक_msg("[%s] (%s:%d)\t" fmt "\n",			\
			lvl, __खाता__, __LINE__, ##__VA_ARGS__)

#घोषणा pr_p(func, fmt, ...)	func(fmt ": %m", ##__VA_ARGS__)

#घोषणा pr_err(fmt, ...)						\
	(अणु								\
		ksft_test_result_error(fmt "\n", ##__VA_ARGS__);		\
		-1;							\
	पूर्ण)

#घोषणा pr_fail(fmt, ...)					\
	(अणु							\
		ksft_test_result_fail(fmt, ##__VA_ARGS__);	\
		-1;						\
	पूर्ण)

#घोषणा pr_लिखो_त्रुटि(fmt, ...)	pr_p(pr_err, fmt, ##__VA_ARGS__)

#पूर्ण_अगर
