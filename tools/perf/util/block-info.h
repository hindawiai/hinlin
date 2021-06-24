<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_BLOCK_H
#घोषणा __PERF_BLOCK_H

#समावेश <linux/types.h>
#समावेश <linux/refcount.h>
#समावेश "hist.h"
#समावेश "symbol.h"
#समावेश "sort.h"
#समावेश "ui/ui.h"

काष्ठा block_info अणु
	काष्ठा symbol		*sym;
	u64			start;
	u64			end;
	u64			cycles;
	u64			cycles_aggr;
	s64			cycles_spark[NUM_SPARKS];
	u64			total_cycles;
	पूर्णांक			num;
	पूर्णांक			num_aggr;
	refcount_t		refcnt;
पूर्ण;

काष्ठा block_fmt अणु
	काष्ठा perf_hpp_fmt	fmt;
	पूर्णांक			idx;
	पूर्णांक			width;
	स्थिर अक्षर		*header;
	u64			total_cycles;
	u64			block_cycles;
पूर्ण;

क्रमागत अणु
	PERF_HPP_REPORT__BLOCK_TOTAL_CYCLES_PCT,
	PERF_HPP_REPORT__BLOCK_LBR_CYCLES,
	PERF_HPP_REPORT__BLOCK_CYCLES_PCT,
	PERF_HPP_REPORT__BLOCK_AVG_CYCLES,
	PERF_HPP_REPORT__BLOCK_RANGE,
	PERF_HPP_REPORT__BLOCK_DSO,
	PERF_HPP_REPORT__BLOCK_MAX_INDEX
पूर्ण;

काष्ठा block_report अणु
	काष्ठा block_hist	hist;
	u64			cycles;
	काष्ठा block_fmt	fmts[PERF_HPP_REPORT__BLOCK_MAX_INDEX];
	पूर्णांक			nr_fmts;
पूर्ण;

काष्ठा block_hist;

काष्ठा block_info *block_info__new(व्योम);
काष्ठा block_info *block_info__get(काष्ठा block_info *bi);
व्योम   block_info__put(काष्ठा block_info *bi);

अटल अंतरभूत व्योम __block_info__zput(काष्ठा block_info **bi)
अणु
	block_info__put(*bi);
	*bi = शून्य;
पूर्ण

#घोषणा block_info__zput(bi) __block_info__zput(&bi)

पूर्णांक64_t __block_info__cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right);

पूर्णांक64_t block_info__cmp(काष्ठा perf_hpp_fmt *fmt __maybe_unused,
			काष्ठा hist_entry *left, काष्ठा hist_entry *right);

पूर्णांक block_info__process_sym(काष्ठा hist_entry *he, काष्ठा block_hist *bh,
			    u64 *block_cycles_aggr, u64 total_cycles);

काष्ठा block_report *block_info__create_report(काष्ठा evlist *evlist,
					       u64 total_cycles,
					       पूर्णांक *block_hpps, पूर्णांक nr_hpps,
					       पूर्णांक *nr_reps);

व्योम block_info__मुक्त_report(काष्ठा block_report *reps, पूर्णांक nr_reps);

पूर्णांक report__browse_block_hists(काष्ठा block_hist *bh, भग्न min_percent,
			       काष्ठा evsel *evsel, काष्ठा perf_env *env,
			       काष्ठा annotation_options *annotation_opts);

भग्न block_info__total_cycles_percent(काष्ठा hist_entry *he);

#पूर्ण_अगर /* __PERF_BLOCK_H */
