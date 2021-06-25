<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SESSION_H
#घोषणा __PERF_SESSION_H

#समावेश "trace-event.h"
#समावेश "event.h"
#समावेश "header.h"
#समावेश "machine.h"
#समावेश "data.h"
#समावेश "ordered-events.h"
#समावेश "util/compress.h"
#समावेश <linux/kernel.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/perf_event.h>

काष्ठा ip_callchain;
काष्ठा symbol;
काष्ठा thपढ़ो;

काष्ठा auxtrace;
काष्ठा itrace_synth_opts;

काष्ठा perf_session अणु
	काष्ठा perf_header	header;
	काष्ठा machines		machines;
	काष्ठा evlist	*evlist;
	काष्ठा auxtrace		*auxtrace;
	काष्ठा itrace_synth_opts *itrace_synth_opts;
	काष्ठा list_head	auxtrace_index;
	काष्ठा trace_event	tevent;
	काष्ठा perf_record_समय_conv	समय_conv;
	bool			repipe;
	bool			one_mmap;
	व्योम			*one_mmap_addr;
	u64			one_mmap_offset;
	काष्ठा ordered_events	ordered_events;
	काष्ठा perf_data	*data;
	काष्ठा perf_tool	*tool;
	u64			bytes_transferred;
	u64			bytes_compressed;
	काष्ठा zstd_data	zstd_data;
	काष्ठा decomp		*decomp;
	काष्ठा decomp		*decomp_last;
पूर्ण;

काष्ठा decomp अणु
	काष्ठा decomp *next;
	u64 file_pos;
	माप_प्रकार mmap_len;
	u64 head;
	माप_प्रकार size;
	अक्षर data[];
पूर्ण;

काष्ठा perf_tool;

काष्ठा perf_session *perf_session__new(काष्ठा perf_data *data,
				       bool repipe, काष्ठा perf_tool *tool);
व्योम perf_session__delete(काष्ठा perf_session *session);

व्योम perf_event_header__bswap(काष्ठा perf_event_header *hdr);

पूर्णांक perf_session__peek_event(काष्ठा perf_session *session, off_t file_offset,
			     व्योम *buf, माप_प्रकार buf_sz,
			     जोड़ perf_event **event_ptr,
			     काष्ठा perf_sample *sample);
प्रकार पूर्णांक (*peek_events_cb_t)(काष्ठा perf_session *session,
				जोड़ perf_event *event, u64 offset,
				व्योम *data);
पूर्णांक perf_session__peek_events(काष्ठा perf_session *session, u64 offset,
			      u64 size, peek_events_cb_t cb, व्योम *data);

पूर्णांक perf_session__process_events(काष्ठा perf_session *session);

पूर्णांक perf_session__queue_event(काष्ठा perf_session *s, जोड़ perf_event *event,
			      u64 बारtamp, u64 file_offset);

व्योम perf_tool__fill_शेषs(काष्ठा perf_tool *tool);

पूर्णांक perf_session__resolve_callchain(काष्ठा perf_session *session,
				    काष्ठा evsel *evsel,
				    काष्ठा thपढ़ो *thपढ़ो,
				    काष्ठा ip_callchain *chain,
				    काष्ठा symbol **parent);

bool perf_session__has_traces(काष्ठा perf_session *session, स्थिर अक्षर *msg);

व्योम perf_event__attr_swap(काष्ठा perf_event_attr *attr);

पूर्णांक perf_session__create_kernel_maps(काष्ठा perf_session *session);

व्योम perf_session__set_id_hdr_size(काष्ठा perf_session *session);

अटल अंतरभूत
काष्ठा machine *perf_session__find_machine(काष्ठा perf_session *session, pid_t pid)
अणु
	वापस machines__find(&session->machines, pid);
पूर्ण

अटल अंतरभूत
काष्ठा machine *perf_session__findnew_machine(काष्ठा perf_session *session, pid_t pid)
अणु
	वापस machines__findnew(&session->machines, pid);
पूर्ण

काष्ठा thपढ़ो *perf_session__findnew(काष्ठा perf_session *session, pid_t pid);
पूर्णांक perf_session__रेजिस्टर_idle_thपढ़ो(काष्ठा perf_session *session);

माप_प्रकार perf_session__ख_लिखो(काष्ठा perf_session *session, खाता *fp);

माप_प्रकार perf_session__ख_लिखो_dsos(काष्ठा perf_session *session, खाता *fp);

माप_प्रकार perf_session__ख_लिखो_dsos_buildid(काष्ठा perf_session *session, खाता *fp,
					  bool (fn)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm);

माप_प्रकार perf_session__ख_लिखो_nr_events(काष्ठा perf_session *session, खाता *fp,
				       bool skip_empty);

काष्ठा evsel *perf_session__find_first_evtype(काष्ठा perf_session *session,
					    अचिन्हित पूर्णांक type);

पूर्णांक perf_session__cpu_biपंचांगap(काष्ठा perf_session *session,
			     स्थिर अक्षर *cpu_list, अचिन्हित दीर्घ *cpu_biपंचांगap);

व्योम perf_session__ख_लिखो_info(काष्ठा perf_session *s, खाता *fp, bool full);

काष्ठा evsel_str_handler;

#घोषणा perf_session__set_tracepoपूर्णांकs_handlers(session, array) \
	__evlist__set_tracepoपूर्णांकs_handlers(session->evlist, array, ARRAY_SIZE(array))

बाह्य अस्थिर पूर्णांक session_करोne;

#घोषणा session_करोne()	READ_ONCE(session_करोne)

पूर्णांक perf_session__deliver_synth_event(काष्ठा perf_session *session,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample);

पूर्णांक perf_event__process_id_index(काष्ठा perf_session *session,
				 जोड़ perf_event *event);

#पूर्ण_अगर /* __PERF_SESSION_H */
