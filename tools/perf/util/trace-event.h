<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UTIL_TRACE_EVENT_H
#घोषणा _PERF_UTIL_TRACE_EVENT_H

#समावेश <traceevent/event-parse.h>
#समावेश "parse-events.h"

काष्ठा machine;
काष्ठा perf_sample;
जोड़ perf_event;
काष्ठा perf_tool;
काष्ठा thपढ़ो;
काष्ठा tep_plugin_list;

काष्ठा trace_event अणु
	काष्ठा tep_handle	*pevent;
	काष्ठा tep_plugin_list	*plugin_list;
पूर्ण;

पूर्णांक trace_event__init(काष्ठा trace_event *t);
व्योम trace_event__cleanup(काष्ठा trace_event *t);
पूर्णांक trace_event__रेजिस्टर_resolver(काष्ठा machine *machine,
				   tep_func_resolver_t *func);
काष्ठा tep_event*
trace_event__tp_क्रमmat(स्थिर अक्षर *sys, स्थिर अक्षर *name);

काष्ठा tep_event *trace_event__tp_क्रमmat_id(पूर्णांक id);

पूर्णांक bigendian(व्योम);

व्योम event_क्रमmat__ख_लिखो(काष्ठा tep_event *event,
			   पूर्णांक cpu, व्योम *data, पूर्णांक size, खाता *fp);

व्योम event_क्रमmat__prपूर्णांक(काष्ठा tep_event *event,
			 पूर्णांक cpu, व्योम *data, पूर्णांक size);

पूर्णांक parse_ftrace_file(काष्ठा tep_handle *pevent, अक्षर *buf, अचिन्हित दीर्घ size);
पूर्णांक parse_event_file(काष्ठा tep_handle *pevent,
		     अक्षर *buf, अचिन्हित दीर्घ size, अक्षर *sys);

अचिन्हित दीर्घ दीर्घ
raw_field_value(काष्ठा tep_event *event, स्थिर अक्षर *name, व्योम *data);

व्योम parse_proc_kallsyms(काष्ठा tep_handle *pevent, अक्षर *file, अचिन्हित पूर्णांक size);
व्योम parse_ftrace_prपूर्णांकk(काष्ठा tep_handle *pevent, अक्षर *file, अचिन्हित पूर्णांक size);
व्योम parse_saved_cmdline(काष्ठा tep_handle *pevent, अक्षर *file, अचिन्हित पूर्णांक size);

sमाप_प्रकार trace_report(पूर्णांक fd, काष्ठा trace_event *tevent, bool repipe);

अचिन्हित दीर्घ दीर्घ पढ़ो_size(काष्ठा tep_event *event, व्योम *ptr, पूर्णांक size);
अचिन्हित दीर्घ दीर्घ eval_flag(स्थिर अक्षर *flag);

पूर्णांक पढ़ो_tracing_data(पूर्णांक fd, काष्ठा list_head *pattrs);

काष्ठा tracing_data अणु
	/* size is only valid अगर temp is 'true' */
	sमाप_प्रकार size;
	bool temp;
	अक्षर temp_file[50];
पूर्ण;

काष्ठा tracing_data *tracing_data_get(काष्ठा list_head *pattrs,
				      पूर्णांक fd, bool temp);
पूर्णांक tracing_data_put(काष्ठा tracing_data *tdata);


काष्ठा addr_location;

काष्ठा perf_session;
काष्ठा perf_stat_config;

काष्ठा scripting_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक (*start_script) (स्थिर अक्षर *script, पूर्णांक argc, स्थिर अक्षर **argv);
	पूर्णांक (*flush_script) (व्योम);
	पूर्णांक (*stop_script) (व्योम);
	व्योम (*process_event) (जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा evsel *evsel,
			       काष्ठा addr_location *al);
	व्योम (*process_चयन)(जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine);
	व्योम (*process_stat)(काष्ठा perf_stat_config *config,
			     काष्ठा evsel *evsel, u64 tstamp);
	व्योम (*process_stat_पूर्णांकerval)(u64 tstamp);
	पूर्णांक (*generate_script) (काष्ठा tep_handle *pevent, स्थिर अक्षर *outfile);
पूर्ण;

बाह्य अचिन्हित पूर्णांक scripting_max_stack;

पूर्णांक script_spec_रेजिस्टर(स्थिर अक्षर *spec, काष्ठा scripting_ops *ops);

व्योम setup_perl_scripting(व्योम);
व्योम setup_python_scripting(व्योम);

काष्ठा scripting_context अणु
	काष्ठा tep_handle *pevent;
	व्योम *event_data;
पूर्ण;

पूर्णांक common_pc(काष्ठा scripting_context *context);
पूर्णांक common_flags(काष्ठा scripting_context *context);
पूर्णांक common_lock_depth(काष्ठा scripting_context *context);

#पूर्ण_अगर /* _PERF_UTIL_TRACE_EVENT_H */
