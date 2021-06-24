<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_RECORD_H
#घोषणा _PERF_RECORD_H

#समावेश <समय.स>
#समावेश <stdbool.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/perf_event.h>
#समावेश "util/target.h"

काष्ठा option;

काष्ठा record_opts अणु
	काष्ठा target target;
	bool	      group;
	bool	      inherit_stat;
	bool	      no_buffering;
	bool	      no_inherit;
	bool	      no_inherit_set;
	bool	      no_samples;
	bool	      raw_samples;
	bool	      sample_address;
	bool	      sample_phys_addr;
	bool	      sample_data_page_size;
	bool	      sample_code_page_size;
	bool	      sample_weight;
	bool	      sample_समय;
	bool	      sample_समय_set;
	bool	      sample_cpu;
	bool	      period;
	bool	      period_set;
	bool	      running_समय;
	bool	      full_auxtrace;
	bool	      auxtrace_snapshot_mode;
	bool	      auxtrace_snapshot_on_निकास;
	bool	      auxtrace_sample_mode;
	bool	      record_namespaces;
	bool	      record_cgroup;
	bool	      record_चयन_events;
	bool	      record_चयन_events_set;
	bool	      all_kernel;
	bool	      all_user;
	bool	      kernel_callchains;
	bool	      user_callchains;
	bool	      tail_synthesize;
	bool	      overग_लिखो;
	bool	      ignore_missing_thपढ़ो;
	bool	      strict_freq;
	bool	      sample_id;
	bool	      no_bpf_event;
	bool	      kcore;
	bool	      text_poke;
	bool	      build_id;
	अचिन्हित पूर्णांक  freq;
	अचिन्हित पूर्णांक  mmap_pages;
	अचिन्हित पूर्णांक  auxtrace_mmap_pages;
	अचिन्हित पूर्णांक  user_freq;
	u64	      branch_stack;
	u64	      sample_पूर्णांकr_regs;
	u64	      sample_user_regs;
	u64	      शेष_पूर्णांकerval;
	u64	      user_पूर्णांकerval;
	माप_प्रकार	      auxtrace_snapshot_size;
	स्थिर अक्षर    *auxtrace_snapshot_opts;
	स्थिर अक्षर    *auxtrace_sample_opts;
	bool	      sample_transaction;
	पूर्णांक	      initial_delay;
	bool	      use_घड़ीid;
	घड़ीid_t     घड़ीid;
	u64	      घड़ीid_res_ns;
	पूर्णांक	      nr_cblocks;
	पूर्णांक	      affinity;
	पूर्णांक	      mmap_flush;
	अचिन्हित पूर्णांक  comp_level;
	अचिन्हित पूर्णांक  nr_thपढ़ोs_synthesize;
	पूर्णांक	      ctl_fd;
	पूर्णांक	      ctl_fd_ack;
	bool	      ctl_fd_बंद;
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर *record_usage;
बाह्य काष्ठा option *record_options;

पूर्णांक record__parse_freq(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);

अटल अंतरभूत bool record_opts__no_चयन_events(स्थिर काष्ठा record_opts *opts)
अणु
	वापस opts->record_चयन_events_set && !opts->record_चयन_events;
पूर्ण

#पूर्ण_अगर // _PERF_RECORD_H
