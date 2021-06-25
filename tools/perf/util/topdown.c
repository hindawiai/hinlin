<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश "pmu.h"
#समावेश "topdown.h"

पूर्णांक topकरोwn_filter_events(स्थिर अक्षर **attr, अक्षर **str, bool use_group)
अणु
	पूर्णांक off = 0;
	पूर्णांक i;
	पूर्णांक len = 0;
	अक्षर *s;

	क्रम (i = 0; attr[i]; i++) अणु
		अगर (pmu_have_event("cpu", attr[i])) अणु
			len += म_माप(attr[i]) + 1;
			attr[i - off] = attr[i];
		पूर्ण अन्यथा
			off++;
	पूर्ण
	attr[i - off] = शून्य;

	*str = दो_स्मृति(len + 1 + 2);
	अगर (!*str)
		वापस -1;
	s = *str;
	अगर (i - off == 0) अणु
		*s = 0;
		वापस 0;
	पूर्ण
	अगर (use_group)
		*s++ = '{';
	क्रम (i = 0; attr[i]; i++) अणु
		म_नकल(s, attr[i]);
		s += म_माप(s);
		*s++ = ',';
	पूर्ण
	अगर (use_group) अणु
		s[-1] = '}';
		*s = 0;
	पूर्ण अन्यथा
		s[-1] = 0;
	वापस 0;
पूर्ण

__weak bool arch_topकरोwn_check_group(bool *warn)
अणु
	*warn = false;
	वापस false;
पूर्ण

__weak व्योम arch_topकरोwn_group_warn(व्योम)
अणु
पूर्ण

__weak bool arch_topकरोwn_sample_पढ़ो(काष्ठा evsel *leader __maybe_unused)
अणु
	वापस false;
पूर्ण
