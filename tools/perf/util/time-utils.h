<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TIME_UTILS_H_
#घोषणा _TIME_UTILS_H_

#समावेश <मानकघोष.स>
#समावेश <समय.स>
#समावेश <linux/types.h>

काष्ठा perf_समय_पूर्णांकerval अणु
	u64 start, end;
पूर्ण;

पूर्णांक parse_nsec_समय(स्थिर अक्षर *str, u64 *pसमय);

पूर्णांक perf_समय__parse_str(काष्ठा perf_समय_पूर्णांकerval *pसमय, स्थिर अक्षर *ostr);

पूर्णांक perf_समय__percent_parse_str(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf, पूर्णांक num,
				 स्थिर अक्षर *ostr, u64 start, u64 end);

काष्ठा perf_समय_पूर्णांकerval *perf_समय__range_alloc(स्थिर अक्षर *ostr, पूर्णांक *size);

bool perf_समय__skip_sample(काष्ठा perf_समय_पूर्णांकerval *pसमय, u64 बारtamp);

bool perf_समय__ranges_skip_sample(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf,
				   पूर्णांक num, u64 बारtamp);

काष्ठा perf_session;

पूर्णांक perf_समय__parse_क्रम_ranges_relसमय(स्थिर अक्षर *str, काष्ठा perf_session *session,
				काष्ठा perf_समय_पूर्णांकerval **ranges,
				पूर्णांक *range_size, पूर्णांक *range_num,
				bool relसमय);

पूर्णांक perf_समय__parse_क्रम_ranges(स्थिर अक्षर *str, काष्ठा perf_session *session,
				काष्ठा perf_समय_पूर्णांकerval **ranges,
				पूर्णांक *range_size, पूर्णांक *range_num);

पूर्णांक बारtamp__scnम_लिखो_usec(u64 बारtamp, अक्षर *buf, माप_प्रकार sz);
पूर्णांक बारtamp__scnम_लिखो_nsec(u64 बारtamp, अक्षर *buf, माप_प्रकार sz);

पूर्णांक fetch_current_बारtamp(अक्षर *buf, माप_प्रकार sz);

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ rdघड़ी(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ULL + ts.tv_nsec;
पूर्ण

#पूर्ण_अगर
