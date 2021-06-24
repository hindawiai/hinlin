<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_TOP_H
#घोषणा __PERF_TOP_H 1

#समावेश "tool.h"
#समावेश "evswitch.h"
#समावेश "annotate.h"
#समावेश "ordered-events.h"
#समावेश "record.h"
#समावेश <linux/types.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <sys/ioctl.h>

काष्ठा evlist;
काष्ठा evsel;
काष्ठा perf_session;

काष्ठा perf_top अणु
	काष्ठा perf_tool   tool;
	काष्ठा evlist *evlist, *sb_evlist;
	काष्ठा record_opts record_opts;
	काष्ठा annotation_options annotation_opts;
	काष्ठा evचयन	   evचयन;
	/*
	 * Symbols will be added here in perf_event__process_sample and will
	 * get out after decayed.
	 */
	u64		   samples, lost, lost_total, drop, drop_total;
	u64		   kernel_samples, us_samples;
	u64		   exact_samples;
	u64		   guest_us_samples, guest_kernel_samples;
	पूर्णांक		   prपूर्णांक_entries, count_filter, delay_secs;
	पूर्णांक		   max_stack;
	bool		   hide_kernel_symbols, hide_user_symbols, zero;
	bool		   use_tui, use_stdio;
	bool		   vmlinux_warned;
	bool		   dump_symtab;
	bool		   stitch_lbr;
	काष्ठा hist_entry  *sym_filter_entry;
	काष्ठा evsel 	   *sym_evsel;
	काष्ठा perf_session *session;
	काष्ठा winsize	   winsize;
	पूर्णांक		   realसमय_prio;
	स्थिर अक्षर	   *sym_filter;
	भग्न		   min_percent;
	अचिन्हित पूर्णांक	   nr_thपढ़ोs_synthesize;

	काष्ठा अणु
		काष्ठा ordered_events	*in;
		काष्ठा ordered_events	 data[2];
		bool			 rotate;
		pthपढ़ो_mutex_t		 mutex;
		pthपढ़ो_cond_t		 cond;
	पूर्ण qe;
पूर्ण;

#घोषणा CONSOLE_CLEAR "[H[2J"

माप_प्रकार perf_top__header_snम_लिखो(काष्ठा perf_top *top, अक्षर *bf, माप_प्रकार size);
व्योम perf_top__reset_sample_counters(काष्ठा perf_top *top);
#पूर्ण_अगर /* __PERF_TOP_H */
