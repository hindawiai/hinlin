<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __TRACE_EVENTS_H
#घोषणा __TRACE_EVENTS_H

#समावेश <linux/trace_seq.h>
#समावेश "trace.h"

बाह्य क्रमागत prपूर्णांक_line_t
trace_prपूर्णांक_bमाला_दो_msg_only(काष्ठा trace_iterator *iter);
बाह्य क्रमागत prपूर्णांक_line_t
trace_prपूर्णांक_bprपूर्णांकk_msg_only(काष्ठा trace_iterator *iter);
बाह्य क्रमागत prपूर्णांक_line_t
trace_prपूर्णांक_prपूर्णांकk_msg_only(काष्ठा trace_iterator *iter);

बाह्य पूर्णांक
seq_prपूर्णांक_ip_sym(काष्ठा trace_seq *s, अचिन्हित दीर्घ ip,
		अचिन्हित दीर्घ sym_flags);

बाह्य व्योम trace_seq_prपूर्णांक_sym(काष्ठा trace_seq *s, अचिन्हित दीर्घ address, bool offset);
बाह्य पूर्णांक trace_prपूर्णांक_context(काष्ठा trace_iterator *iter);
बाह्य पूर्णांक trace_prपूर्णांक_lat_context(काष्ठा trace_iterator *iter);

बाह्य व्योम trace_event_पढ़ो_lock(व्योम);
बाह्य व्योम trace_event_पढ़ो_unlock(व्योम);
बाह्य काष्ठा trace_event *ftrace_find_event(पूर्णांक type);

बाह्य क्रमागत prपूर्णांक_line_t trace_nop_prपूर्णांक(काष्ठा trace_iterator *iter,
					 पूर्णांक flags, काष्ठा trace_event *event);
बाह्य पूर्णांक
trace_prपूर्णांक_lat_fmt(काष्ठा trace_seq *s, काष्ठा trace_entry *entry);

/* used by module unरेजिस्टरing */
बाह्य पूर्णांक __unरेजिस्टर_trace_event(काष्ठा trace_event *event);
बाह्य काष्ठा rw_semaphore trace_event_sem;

#घोषणा SEQ_PUT_FIELD(s, x)				\
	trace_seq_puपंचांगem(s, &(x), माप(x))

#घोषणा SEQ_PUT_HEX_FIELD(s, x)				\
	trace_seq_puपंचांगem_hex(s, &(x), माप(x))

#पूर्ण_अगर

