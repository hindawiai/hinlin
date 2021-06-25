<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TRACE_H
#घोषणा _LINUX_TRACE_H

#अगर_घोषित CONFIG_TRACING

#घोषणा TRACE_EXPORT_FUNCTION	BIT(0)
#घोषणा TRACE_EXPORT_EVENT	BIT(1)
#घोषणा TRACE_EXPORT_MARKER	BIT(2)

/*
 * The trace export - an export of Ftrace output. The trace_export
 * can process traces and export them to a रेजिस्टरed destination as
 * an addition to the current only output of Ftrace - i.e. ring buffer.
 *
 * If you want traces to be sent to some other place rather than ring
 * buffer only, just need to रेजिस्टर a new trace_export and implement
 * its own .ग_लिखो() function क्रम writing traces to the storage.
 *
 * next		- poपूर्णांकer to the next trace_export
 * ग_लिखो	- copy traces which have been delt with ->commit() to
 *		  the destination
 * flags	- which ftrace to be exported
 */
काष्ठा trace_export अणु
	काष्ठा trace_export __rcu	*next;
	व्योम (*ग_लिखो)(काष्ठा trace_export *, स्थिर व्योम *, अचिन्हित पूर्णांक);
	पूर्णांक flags;
पूर्ण;

पूर्णांक रेजिस्टर_ftrace_export(काष्ठा trace_export *export);
पूर्णांक unरेजिस्टर_ftrace_export(काष्ठा trace_export *export);

काष्ठा trace_array;

व्योम trace_prपूर्णांकk_init_buffers(व्योम);
__म_लिखो(3, 4)
पूर्णांक trace_array_prपूर्णांकk(काष्ठा trace_array *tr, अचिन्हित दीर्घ ip,
		       स्थिर अक्षर *fmt, ...);
पूर्णांक trace_array_init_prपूर्णांकk(काष्ठा trace_array *tr);
व्योम trace_array_put(काष्ठा trace_array *tr);
काष्ठा trace_array *trace_array_get_by_name(स्थिर अक्षर *name);
पूर्णांक trace_array_destroy(काष्ठा trace_array *tr);
#पूर्ण_अगर	/* CONFIG_TRACING */

#पूर्ण_अगर	/* _LINUX_TRACE_H */
