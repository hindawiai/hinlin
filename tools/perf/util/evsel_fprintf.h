<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __PERF_EVSEL_FPRINTF_H
#घोषणा __PERF_EVSEL_FPRINTF_H 1

#समावेश <मानकपन.स>
#समावेश <stdbool.h>

काष्ठा evsel;

काष्ठा perf_attr_details अणु
	bool freq;
	bool verbose;
	bool event_group;
	bool क्रमce;
	bool trace_fields;
पूर्ण;

पूर्णांक evsel__ख_लिखो(काष्ठा evsel *evsel, काष्ठा perf_attr_details *details, खाता *fp);

#घोषणा EVSEL__PRINT_IP			(1<<0)
#घोषणा EVSEL__PRINT_SYM		(1<<1)
#घोषणा EVSEL__PRINT_DSO		(1<<2)
#घोषणा EVSEL__PRINT_SYMOFFSET		(1<<3)
#घोषणा EVSEL__PRINT_ONELINE		(1<<4)
#घोषणा EVSEL__PRINT_SRCLINE		(1<<5)
#घोषणा EVSEL__PRINT_UNKNOWN_AS_ADDR	(1<<6)
#घोषणा EVSEL__PRINT_CALLCHAIN_ARROW	(1<<7)
#घोषणा EVSEL__PRINT_SKIP_IGNORED	(1<<8)

काष्ठा addr_location;
काष्ठा perf_event_attr;
काष्ठा perf_sample;
काष्ठा callchain_cursor;
काष्ठा strlist;

पूर्णांक sample__ख_लिखो_callchain(काष्ठा perf_sample *sample, पूर्णांक left_alignment,
			      अचिन्हित पूर्णांक prपूर्णांक_opts, काष्ठा callchain_cursor *cursor,
			      काष्ठा strlist *bt_stop_list, खाता *fp);

पूर्णांक sample__ख_लिखो_sym(काष्ठा perf_sample *sample, काष्ठा addr_location *al,
			पूर्णांक left_alignment, अचिन्हित पूर्णांक prपूर्णांक_opts,
			काष्ठा callchain_cursor *cursor,
			काष्ठा strlist *bt_stop_list, खाता *fp);

प्रकार पूर्णांक (*attr__ख_लिखो_f)(खाता *, स्थिर अक्षर *, स्थिर अक्षर *, व्योम *);

पूर्णांक perf_event_attr__ख_लिखो(खाता *fp, काष्ठा perf_event_attr *attr,
			     attr__ख_लिखो_f attr__ख_लिखो, व्योम *priv);
#पूर्ण_अगर // __PERF_EVSEL_H
