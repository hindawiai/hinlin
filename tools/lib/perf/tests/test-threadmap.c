<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <पूर्णांकernal/tests.h>

अटल पूर्णांक libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
			 स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस भख_लिखो(मानक_त्रुटि, fmt, ap);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	__T_START;

	libperf_init(libperf_prपूर्णांक);

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	अगर (!thपढ़ोs)
		वापस -1;

	perf_thपढ़ो_map__get(thपढ़ोs);
	perf_thपढ़ो_map__put(thपढ़ोs);
	perf_thपढ़ो_map__put(thपढ़ोs);

	__T_END;
	वापस tests_failed == 0 ? 0 : -1;
पूर्ण
