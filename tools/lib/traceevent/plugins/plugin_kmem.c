<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

अटल पूर्णांक call_site_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			     काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ val, addr;
	व्योम *data = record->data;
	स्थिर अक्षर *func;

	field = tep_find_field(event, "call_site");
	अगर (!field)
		वापस 1;

	अगर (tep_पढ़ो_number_field(field, data, &val))
		वापस 1;

	func = tep_find_function(event->tep, val);
	अगर (!func)
		वापस 1;

	addr = tep_find_function_address(event->tep, val);

	trace_seq_म_लिखो(s, "(%s+0x%x) ", func, (पूर्णांक)(val - addr));
	वापस 1;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "kmem", "kfree",
				   call_site_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kmem", "kmalloc",
				   call_site_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kmem", "kmalloc_node",
				   call_site_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kmem", "kmem_cache_alloc",
				   call_site_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kmem",
				   "kmem_cache_alloc_node",
				   call_site_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "kmem", "kmem_cache_free",
				   call_site_handler, शून्य);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1, "kmem", "kfree",
				     call_site_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kmem", "kmalloc",
				     call_site_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kmem", "kmalloc_node",
				     call_site_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kmem", "kmem_cache_alloc",
				     call_site_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kmem",
				     "kmem_cache_alloc_node",
				     call_site_handler, शून्य);

	tep_unरेजिस्टर_event_handler(tep, -1, "kmem", "kmem_cache_free",
				     call_site_handler, शून्य);
पूर्ण
