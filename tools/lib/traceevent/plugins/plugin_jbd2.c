<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

#घोषणा MINORBITS	20
#घोषणा MINORMASK	((1U << MINORBITS) - 1)

#घोषणा MAJOR(dev)	((अचिन्हित पूर्णांक) ((dev) >> MINORBITS))
#घोषणा MINOR(dev)	((अचिन्हित पूर्णांक) ((dev) & MINORMASK))

अटल अचिन्हित दीर्घ दीर्घ
process_jbd2_dev_to_name(काष्ठा trace_seq *s, अचिन्हित दीर्घ दीर्घ *args)
अणु
	अचिन्हित पूर्णांक dev = args[0];

	trace_seq_म_लिखो(s, "%d:%d", MAJOR(dev), MINOR(dev));
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
process_jअगरfies_to_msecs(काष्ठा trace_seq *s, अचिन्हित दीर्घ दीर्घ *args)
अणु
	अचिन्हित दीर्घ दीर्घ jअगरfies = args[0];

	trace_seq_म_लिखो(s, "%lld", jअगरfies);
	वापस jअगरfies;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process_jbd2_dev_to_name,
				    TEP_FUNC_ARG_STRING,
				    "jbd2_dev_to_name",
				    TEP_FUNC_ARG_INT,
				    TEP_FUNC_ARG_VOID);

	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process_jअगरfies_to_msecs,
				    TEP_FUNC_ARG_LONG,
				    "jiffies_to_msecs",
				    TEP_FUNC_ARG_LONG,
				    TEP_FUNC_ARG_VOID);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_prपूर्णांक_function(tep, process_jbd2_dev_to_name,
				      "jbd2_dev_to_name");

	tep_unरेजिस्टर_prपूर्णांक_function(tep, process_jअगरfies_to_msecs,
				      "jiffies_to_msecs");
पूर्ण
