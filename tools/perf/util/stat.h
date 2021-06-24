<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_STATS_H
#घोषणा __PERF_STATS_H

#समावेश <linux/types.h>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/resource.h>
#समावेश "cpumap.h"
#समावेश "rblist.h"

काष्ठा perf_cpu_map;
काष्ठा perf_stat_config;
काष्ठा बारpec;

काष्ठा stats अणु
	द्विगुन n, mean, M2;
	u64 max, min;
पूर्ण;

क्रमागत perf_stat_evsel_id अणु
	PERF_STAT_EVSEL_ID__NONE = 0,
	PERF_STAT_EVSEL_ID__CYCLES_IN_TX,
	PERF_STAT_EVSEL_ID__TRANSACTION_START,
	PERF_STAT_EVSEL_ID__ELISION_START,
	PERF_STAT_EVSEL_ID__CYCLES_IN_TX_CP,
	PERF_STAT_EVSEL_ID__TOPDOWN_TOTAL_SLOTS,
	PERF_STAT_EVSEL_ID__TOPDOWN_SLOTS_ISSUED,
	PERF_STAT_EVSEL_ID__TOPDOWN_SLOTS_RETIRED,
	PERF_STAT_EVSEL_ID__TOPDOWN_FETCH_BUBBLES,
	PERF_STAT_EVSEL_ID__TOPDOWN_RECOVERY_BUBBLES,
	PERF_STAT_EVSEL_ID__TOPDOWN_RETIRING,
	PERF_STAT_EVSEL_ID__TOPDOWN_BAD_SPEC,
	PERF_STAT_EVSEL_ID__TOPDOWN_FE_BOUND,
	PERF_STAT_EVSEL_ID__TOPDOWN_BE_BOUND,
	PERF_STAT_EVSEL_ID__TOPDOWN_HEAVY_OPS,
	PERF_STAT_EVSEL_ID__TOPDOWN_BR_MISPREDICT,
	PERF_STAT_EVSEL_ID__TOPDOWN_FETCH_LAT,
	PERF_STAT_EVSEL_ID__TOPDOWN_MEM_BOUND,
	PERF_STAT_EVSEL_ID__SMI_NUM,
	PERF_STAT_EVSEL_ID__APERF,
	PERF_STAT_EVSEL_ID__MAX,
पूर्ण;

काष्ठा perf_stat_evsel अणु
	काष्ठा stats		 res_stats[3];
	क्रमागत perf_stat_evsel_id	 id;
	u64			*group_data;
पूर्ण;

क्रमागत aggr_mode अणु
	AGGR_NONE,
	AGGR_GLOBAL,
	AGGR_SOCKET,
	AGGR_DIE,
	AGGR_CORE,
	AGGR_THREAD,
	AGGR_UNSET,
	AGGR_NODE,
पूर्ण;

क्रमागत अणु
	CTX_BIT_USER	= 1 << 0,
	CTX_BIT_KERNEL	= 1 << 1,
	CTX_BIT_HV	= 1 << 2,
	CTX_BIT_HOST	= 1 << 3,
	CTX_BIT_IDLE	= 1 << 4,
	CTX_BIT_MAX	= 1 << 5,
पूर्ण;

#घोषणा NUM_CTX CTX_BIT_MAX

क्रमागत stat_type अणु
	STAT_NONE = 0,
	STAT_NSECS,
	STAT_CYCLES,
	STAT_STALLED_CYCLES_FRONT,
	STAT_STALLED_CYCLES_BACK,
	STAT_BRANCHES,
	STAT_CACHEREFS,
	STAT_L1_DCACHE,
	STAT_L1_ICACHE,
	STAT_LL_CACHE,
	STAT_ITLB_CACHE,
	STAT_DTLB_CACHE,
	STAT_CYCLES_IN_TX,
	STAT_TRANSACTION,
	STAT_ELISION,
	STAT_TOPDOWN_TOTAL_SLOTS,
	STAT_TOPDOWN_SLOTS_ISSUED,
	STAT_TOPDOWN_SLOTS_RETIRED,
	STAT_TOPDOWN_FETCH_BUBBLES,
	STAT_TOPDOWN_RECOVERY_BUBBLES,
	STAT_TOPDOWN_RETIRING,
	STAT_TOPDOWN_BAD_SPEC,
	STAT_TOPDOWN_FE_BOUND,
	STAT_TOPDOWN_BE_BOUND,
	STAT_TOPDOWN_HEAVY_OPS,
	STAT_TOPDOWN_BR_MISPREDICT,
	STAT_TOPDOWN_FETCH_LAT,
	STAT_TOPDOWN_MEM_BOUND,
	STAT_SMI_NUM,
	STAT_APERF,
	STAT_MAX
पूर्ण;

काष्ठा runसमय_stat अणु
	काष्ठा rblist value_list;
पूर्ण;

प्रकार काष्ठा aggr_cpu_id (*aggr_get_id_t)(काष्ठा perf_stat_config *config,
			     काष्ठा perf_cpu_map *m, पूर्णांक cpu);

काष्ठा perf_stat_config अणु
	क्रमागत aggr_mode		 aggr_mode;
	bool			 scale;
	bool			 no_inherit;
	bool			 identअगरier;
	bool			 csv_output;
	bool			 पूर्णांकerval_clear;
	bool			 metric_only;
	bool			 null_run;
	bool			 ru_display;
	bool			 big_num;
	bool			 no_merge;
	bool			 wallसमय_run_table;
	bool			 all_kernel;
	bool			 all_user;
	bool			 percore_show_thपढ़ो;
	bool			 summary;
	bool			 no_csv_summary;
	bool			 metric_no_group;
	bool			 metric_no_merge;
	bool			 stop_पढ़ो_counter;
	bool			 quiet;
	bool			 iostat_run;
	खाता			*output;
	अचिन्हित पूर्णांक		 पूर्णांकerval;
	अचिन्हित पूर्णांक		 समयout;
	पूर्णांक			 initial_delay;
	अचिन्हित पूर्णांक		 unit_width;
	अचिन्हित पूर्णांक		 metric_only_len;
	पूर्णांक			 बार;
	पूर्णांक			 run_count;
	पूर्णांक			 prपूर्णांक_मुक्त_counters_hपूर्णांक;
	पूर्णांक			 prपूर्णांक_mixed_hw_group_error;
	काष्ठा runसमय_stat	*stats;
	पूर्णांक			 stats_num;
	स्थिर अक्षर		*csv_sep;
	काष्ठा stats		*wallसमय_nsecs_stats;
	काष्ठा rusage		 ru_data;
	काष्ठा cpu_aggr_map	*aggr_map;
	aggr_get_id_t		 aggr_get_id;
	काष्ठा cpu_aggr_map	*cpus_aggr_map;
	u64			*wallसमय_run;
	काष्ठा rblist		 metric_events;
	पूर्णांक			 ctl_fd;
	पूर्णांक			 ctl_fd_ack;
	bool			 ctl_fd_बंद;
	स्थिर अक्षर		*cgroup_list;
	अचिन्हित पूर्णांक		topकरोwn_level;
पूर्ण;

व्योम perf_stat__set_big_num(पूर्णांक set);
व्योम perf_stat__set_no_csv_summary(पूर्णांक set);

व्योम update_stats(काष्ठा stats *stats, u64 val);
द्विगुन avg_stats(काष्ठा stats *stats);
द्विगुन stddev_stats(काष्ठा stats *stats);
द्विगुन rel_stddev_stats(द्विगुन stddev, द्विगुन avg);

अटल अंतरभूत व्योम init_stats(काष्ठा stats *stats)
अणु
	stats->n    = 0.0;
	stats->mean = 0.0;
	stats->M2   = 0.0;
	stats->min  = (u64) -1;
	stats->max  = 0;
पूर्ण

काष्ठा evsel;
काष्ठा evlist;

काष्ठा perf_aggr_thपढ़ो_value अणु
	काष्ठा evsel *counter;
	काष्ठा aggr_cpu_id id;
	द्विगुन uval;
	u64 val;
	u64 run;
	u64 ena;
पूर्ण;

bool __perf_stat_evsel__is(काष्ठा evsel *evsel, क्रमागत perf_stat_evsel_id id);

#घोषणा perf_stat_evsel__is(evsel, id) \
	__perf_stat_evsel__is(evsel, PERF_STAT_EVSEL_ID__ ## id)

बाह्य काष्ठा runसमय_stat rt_stat;
बाह्य काष्ठा stats wallसमय_nsecs_stats;

प्रकार व्योम (*prपूर्णांक_metric_t)(काष्ठा perf_stat_config *config,
			       व्योम *ctx, स्थिर अक्षर *color, स्थिर अक्षर *unit,
			       स्थिर अक्षर *fmt, द्विगुन val);
प्रकार व्योम (*new_line_t)(काष्ठा perf_stat_config *config, व्योम *ctx);

व्योम runसमय_stat__init(काष्ठा runसमय_stat *st);
व्योम runसमय_stat__निकास(काष्ठा runसमय_stat *st);
व्योम perf_stat__init_shaकरोw_stats(व्योम);
व्योम perf_stat__reset_shaकरोw_stats(व्योम);
व्योम perf_stat__reset_shaकरोw_per_stat(काष्ठा runसमय_stat *st);
व्योम perf_stat__update_shaकरोw_stats(काष्ठा evsel *counter, u64 count,
				    पूर्णांक cpu, काष्ठा runसमय_stat *st);
काष्ठा perf_stat_output_ctx अणु
	व्योम *ctx;
	prपूर्णांक_metric_t prपूर्णांक_metric;
	new_line_t new_line;
	bool क्रमce_header;
पूर्ण;

व्योम perf_stat__prपूर्णांक_shaकरोw_stats(काष्ठा perf_stat_config *config,
				   काष्ठा evsel *evsel,
				   द्विगुन avg, पूर्णांक cpu,
				   काष्ठा perf_stat_output_ctx *out,
				   काष्ठा rblist *metric_events,
				   काष्ठा runसमय_stat *st);
व्योम perf_stat__collect_metric_expr(काष्ठा evlist *);

पूर्णांक evlist__alloc_stats(काष्ठा evlist *evlist, bool alloc_raw);
व्योम evlist__मुक्त_stats(काष्ठा evlist *evlist);
व्योम evlist__reset_stats(काष्ठा evlist *evlist);
व्योम evlist__reset_prev_raw_counts(काष्ठा evlist *evlist);
व्योम evlist__copy_prev_raw_counts(काष्ठा evlist *evlist);
व्योम evlist__save_aggr_prev_raw_counts(काष्ठा evlist *evlist);

पूर्णांक perf_stat_process_counter(काष्ठा perf_stat_config *config,
			      काष्ठा evsel *counter);
काष्ठा perf_tool;
जोड़ perf_event;
काष्ठा perf_session;
काष्ठा target;

पूर्णांक perf_event__process_stat_event(काष्ठा perf_session *session,
				   जोड़ perf_event *event);

माप_प्रकार perf_event__ख_लिखो_stat(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_stat_round(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_stat_config(जोड़ perf_event *event, खाता *fp);

पूर्णांक create_perf_stat_counter(काष्ठा evsel *evsel,
			     काष्ठा perf_stat_config *config,
			     काष्ठा target *target,
			     पूर्णांक cpu);
व्योम evlist__prपूर्णांक_counters(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config,
			    काष्ठा target *_target, काष्ठा बारpec *ts, पूर्णांक argc, स्थिर अक्षर **argv);

काष्ठा metric_expr;
द्विगुन test_generic_metric(काष्ठा metric_expr *mexp, पूर्णांक cpu, काष्ठा runसमय_stat *st);
#पूर्ण_अगर
