<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2015 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"

क्रमागत tlb_flush_reason अणु
	TLB_FLUSH_ON_TASK_SWITCH,
	TLB_REMOTE_SHOOTDOWN,
	TLB_LOCAL_SHOOTDOWN,
	TLB_LOCAL_MM_SHOOTDOWN,
	NR_TLB_FLUSH_REASONS,
पूर्ण;

अटल पूर्णांक tlb_flush_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			     काष्ठा tep_event *event, व्योम *context)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	trace_seq_म_लिखो(s, "pages=");

	tep_prपूर्णांक_num_field(s, "%ld", event, "pages", record, 1);

	अगर (tep_get_field_val(s, event, "reason", record, &val, 1) < 0)
		वापस -1;

	trace_seq_माला_दो(s, " reason=");

	चयन (val) अणु
	हाल TLB_FLUSH_ON_TASK_SWITCH:
		trace_seq_माला_दो(s, "flush on task switch");
		अवरोध;
	हाल TLB_REMOTE_SHOOTDOWN:
		trace_seq_माला_दो(s, "remote shootdown");
		अवरोध;
	हाल TLB_LOCAL_SHOOTDOWN:
		trace_seq_माला_दो(s, "local shootdown");
		अवरोध;
	हाल TLB_LOCAL_MM_SHOOTDOWN:
		trace_seq_माला_दो(s, "local mm shootdown");
		अवरोध;
	पूर्ण

	trace_seq_म_लिखो(s, " (%lld)", val);

	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "tlb", "tlb_flush",
				   tlb_flush_handler, शून्य);

	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1,
				     "tlb", "tlb_flush",
				     tlb_flush_handler, शून्य);
पूर्ण
