<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा _GNU_SOURCE
#अगर_अघोषित RESCTRL_H
#घोषणा RESCTRL_H
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <गणित.स>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <dirent.h>
#समावेश <stdbool.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mount.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/select.h>
#समावेश <sys/समय.स>
#समावेश <sys/eventfd.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/perf_event.h>
#समावेश "../kselftest.h"

#घोषणा MB			(1024 * 1024)
#घोषणा RESCTRL_PATH		"/sys/fs/resctrl"
#घोषणा PHYS_ID_PATH		"/sys/devices/system/cpu/cpu"
#घोषणा CBM_MASK_PATH		"/sys/fs/resctrl/info"
#घोषणा L3_PATH			"/sys/fs/resctrl/info/L3"
#घोषणा MB_PATH			"/sys/fs/resctrl/info/MB"
#घोषणा L3_MON_PATH		"/sys/fs/resctrl/info/L3_MON"
#घोषणा L3_MON_FEATURES_PATH	"/sys/fs/resctrl/info/L3_MON/mon_features"

#घोषणा PARENT_EXIT(err_msg)			\
	करो अणु					\
		लिखो_त्रुटि(err_msg);		\
		समाप्त(ppid, SIGKILL);		\
		निकास(निकास_त्रुटि);		\
	पूर्ण जबतक (0)

/*
 * resctrl_val_param:	resctrl test parameters
 * @resctrl_val:	Resctrl feature (Eg: mbm, mba.. etc)
 * @ctrlgrp:		Name of the control monitor group (con_mon grp)
 * @mongrp:		Name of the monitor group (mon grp)
 * @cpu_no:		CPU number to which the benchmark would be binded
 * @span:		Memory bytes accessed in each benchmark iteration
 * @mum_resctrlfs:	Should the resctrl FS be remounted?
 * @filename:		Name of file to which the o/p should be written
 * @bw_report:		Bandwidth report type (पढ़ोs vs ग_लिखोs)
 * @setup:		Call back function to setup test environment
 */
काष्ठा resctrl_val_param अणु
	अक्षर		*resctrl_val;
	अक्षर		ctrlgrp[64];
	अक्षर		mongrp[64];
	पूर्णांक		cpu_no;
	अचिन्हित दीर्घ	span;
	पूर्णांक		mum_resctrlfs;
	अक्षर		filename[64];
	अक्षर		*bw_report;
	अचिन्हित दीर्घ	mask;
	पूर्णांक		num_of_runs;
	पूर्णांक		(*setup)(पूर्णांक num, ...);
पूर्ण;

#घोषणा MBM_STR			"mbm"
#घोषणा MBA_STR			"mba"
#घोषणा CMT_STR			"cmt"
#घोषणा CAT_STR			"cat"

बाह्य pid_t bm_pid, ppid;

बाह्य अक्षर llc_occup_path[1024];
बाह्य bool is_amd;

bool check_resctrlfs_support(व्योम);
पूर्णांक filter_dmesg(व्योम);
पूर्णांक remount_resctrlfs(bool mum_resctrlfs);
पूर्णांक get_resource_id(पूर्णांक cpu_no, पूर्णांक *resource_id);
पूर्णांक umount_resctrlfs(व्योम);
पूर्णांक validate_bw_report_request(अक्षर *bw_report);
bool validate_resctrl_feature_request(स्थिर अक्षर *resctrl_val);
अक्षर *fgrep(खाता *inf, स्थिर अक्षर *str);
पूर्णांक taskset_benchmark(pid_t bm_pid, पूर्णांक cpu_no);
व्योम run_benchmark(पूर्णांक signum, siginfo_t *info, व्योम *ucontext);
पूर्णांक ग_लिखो_schemata(अक्षर *ctrlgrp, अक्षर *schemata, पूर्णांक cpu_no,
		   अक्षर *resctrl_val);
पूर्णांक ग_लिखो_bm_pid_to_resctrl(pid_t bm_pid, अक्षर *ctrlgrp, अक्षर *mongrp,
			    अक्षर *resctrl_val);
पूर्णांक perf_event_खोलो(काष्ठा perf_event_attr *hw_event, pid_t pid, पूर्णांक cpu,
		    पूर्णांक group_fd, अचिन्हित दीर्घ flags);
पूर्णांक run_fill_buf(अचिन्हित दीर्घ span, पूर्णांक दो_स्मृति_and_init_memory, पूर्णांक memflush,
		 पूर्णांक op, अक्षर *resctrl_va);
पूर्णांक resctrl_val(अक्षर **benchmark_cmd, काष्ठा resctrl_val_param *param);
पूर्णांक mbm_bw_change(पूर्णांक span, पूर्णांक cpu_no, अक्षर *bw_report, अक्षर **benchmark_cmd);
व्योम tests_cleanup(व्योम);
व्योम mbm_test_cleanup(व्योम);
पूर्णांक mba_schemata_change(पूर्णांक cpu_no, अक्षर *bw_report, अक्षर **benchmark_cmd);
व्योम mba_test_cleanup(व्योम);
पूर्णांक get_cbm_mask(अक्षर *cache_type, अक्षर *cbm_mask);
पूर्णांक get_cache_size(पूर्णांक cpu_no, अक्षर *cache_type, अचिन्हित दीर्घ *cache_size);
व्योम ctrlc_handler(पूर्णांक signum, siginfo_t *info, व्योम *ptr);
पूर्णांक cat_val(काष्ठा resctrl_val_param *param);
व्योम cat_test_cleanup(व्योम);
पूर्णांक cat_perf_miss_val(पूर्णांक cpu_no, पूर्णांक no_of_bits, अक्षर *cache_type);
पूर्णांक cmt_resctrl_val(पूर्णांक cpu_no, पूर्णांक n, अक्षर **benchmark_cmd);
अचिन्हित पूर्णांक count_bits(अचिन्हित दीर्घ n);
व्योम cmt_test_cleanup(व्योम);
पूर्णांक get_core_sibling(पूर्णांक cpu_no);
पूर्णांक measure_cache_vals(काष्ठा resctrl_val_param *param, पूर्णांक bm_pid);
पूर्णांक show_cache_info(अचिन्हित दीर्घ sum_llc_val, पूर्णांक no_of_bits,
		    अचिन्हित दीर्घ cache_span, अचिन्हित दीर्घ max_dअगरf,
		    अचिन्हित दीर्घ max_dअगरf_percent, अचिन्हित दीर्घ num_of_runs,
		    bool platक्रमm, bool cmt);

#पूर्ण_अगर /* RESCTRL_H */
