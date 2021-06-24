<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __TRACE_STAT_H
#घोषणा __TRACE_STAT_H

#समावेश <linux/seq_file.h>

/*
 * If you want to provide a stat file (one-shot statistics), fill
 * an iterator with stat_start/stat_next and a stat_show callbacks.
 * The others callbacks are optional.
 */
काष्ठा tracer_stat अणु
	/* The name of your stat file */
	स्थिर अक्षर		*name;
	/* Iteration over statistic entries */
	व्योम			*(*stat_start)(काष्ठा tracer_stat *trace);
	व्योम			*(*stat_next)(व्योम *prev, पूर्णांक idx);
	/* Compare two entries क्रम stats sorting */
	cmp_func_t		stat_cmp;
	/* Prपूर्णांक a stat entry */
	पूर्णांक			(*stat_show)(काष्ठा seq_file *s, व्योम *p);
	/* Release an entry */
	व्योम			(*stat_release)(व्योम *stat);
	/* Prपूर्णांक the headers of your stat entries */
	पूर्णांक			(*stat_headers)(काष्ठा seq_file *s);
पूर्ण;

/*
 * Destroy or create a stat file
 */
बाह्य पूर्णांक रेजिस्टर_stat_tracer(काष्ठा tracer_stat *trace);
बाह्य व्योम unरेजिस्टर_stat_tracer(काष्ठा tracer_stat *trace);

#पूर्ण_अगर /* __TRACE_STAT_H */
