<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <traceevent/trace-seq.h>

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक rv = 0;
	काष्ठा trace_seq s;
	trace_seq_init(&s);
	rv += !(s.state == TRACE_SEQ__GOOD);
	trace_seq_destroy(&s);
	वापस rv;
पूर्ण
