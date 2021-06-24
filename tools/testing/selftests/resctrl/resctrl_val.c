<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Memory bandwidth monitoring and allocation library
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Authors:
 *    Sai Praneeth Prakhya <sai.praneeth.prakhya@पूर्णांकel.com>,
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 */
#समावेश "resctrl.h"

#घोषणा UNCORE_IMC		"uncore_imc"
#घोषणा READ_खाता_NAME		"events/cas_count_read"
#घोषणा WRITE_खाता_NAME		"events/cas_count_write"
#घोषणा DYN_PMU_PATH		"/sys/bus/event_source/devices"
#घोषणा SCALE			0.00006103515625
#घोषणा MAX_IMCS		20
#घोषणा MAX_TOKENS		5
#घोषणा READ			0
#घोषणा WRITE			1
#घोषणा CON_MON_MBM_LOCAL_BYTES_PATH				\
	"%s/%s/mon_groups/%s/mon_data/mon_L3_%02d/mbm_local_bytes"

#घोषणा CON_MBM_LOCAL_BYTES_PATH		\
	"%s/%s/mon_data/mon_L3_%02d/mbm_local_bytes"

#घोषणा MON_MBM_LOCAL_BYTES_PATH		\
	"%s/mon_groups/%s/mon_data/mon_L3_%02d/mbm_local_bytes"

#घोषणा MBM_LOCAL_BYTES_PATH			\
	"%s/mon_data/mon_L3_%02d/mbm_local_bytes"

#घोषणा CON_MON_LCC_OCCUP_PATH		\
	"%s/%s/mon_groups/%s/mon_data/mon_L3_%02d/llc_occupancy"

#घोषणा CON_LCC_OCCUP_PATH		\
	"%s/%s/mon_data/mon_L3_%02d/llc_occupancy"

#घोषणा MON_LCC_OCCUP_PATH		\
	"%s/mon_groups/%s/mon_data/mon_L3_%02d/llc_occupancy"

#घोषणा LCC_OCCUP_PATH			\
	"%s/mon_data/mon_L3_%02d/llc_occupancy"

काष्ठा membw_पढ़ो_क्रमmat अणु
	__u64 value;         /* The value of the event */
	__u64 समय_enabled;  /* अगर PERF_FORMAT_TOTAL_TIME_ENABLED */
	__u64 समय_running;  /* अगर PERF_FORMAT_TOTAL_TIME_RUNNING */
	__u64 id;            /* अगर PERF_FORMAT_ID */
पूर्ण;

काष्ठा imc_counter_config अणु
	__u32 type;
	__u64 event;
	__u64 umask;
	काष्ठा perf_event_attr pe;
	काष्ठा membw_पढ़ो_क्रमmat वापस_value;
	पूर्णांक fd;
पूर्ण;

अटल अक्षर mbm_total_path[1024];
अटल पूर्णांक imcs;
अटल काष्ठा imc_counter_config imc_counters_config[MAX_IMCS][2];

व्योम membw_initialize_perf_event_attr(पूर्णांक i, पूर्णांक j)
अणु
	स_रखो(&imc_counters_config[i][j].pe, 0,
	       माप(काष्ठा perf_event_attr));
	imc_counters_config[i][j].pe.type = imc_counters_config[i][j].type;
	imc_counters_config[i][j].pe.size = माप(काष्ठा perf_event_attr);
	imc_counters_config[i][j].pe.disabled = 1;
	imc_counters_config[i][j].pe.inherit = 1;
	imc_counters_config[i][j].pe.exclude_guest = 0;
	imc_counters_config[i][j].pe.config =
		imc_counters_config[i][j].umask << 8 |
		imc_counters_config[i][j].event;
	imc_counters_config[i][j].pe.sample_type = PERF_SAMPLE_IDENTIFIER;
	imc_counters_config[i][j].pe.पढ़ो_क्रमmat =
		PERF_FORMAT_TOTAL_TIME_ENABLED | PERF_FORMAT_TOTAL_TIME_RUNNING;
पूर्ण

व्योम membw_ioctl_perf_event_ioc_reset_enable(पूर्णांक i, पूर्णांक j)
अणु
	ioctl(imc_counters_config[i][j].fd, PERF_EVENT_IOC_RESET, 0);
	ioctl(imc_counters_config[i][j].fd, PERF_EVENT_IOC_ENABLE, 0);
पूर्ण

व्योम membw_ioctl_perf_event_ioc_disable(पूर्णांक i, पूर्णांक j)
अणु
	ioctl(imc_counters_config[i][j].fd, PERF_EVENT_IOC_DISABLE, 0);
पूर्ण

/*
 * get_event_and_umask:	Parse config पूर्णांकo event and umask
 * @cas_count_cfg:	Config
 * @count:		iMC number
 * @op:			Operation (पढ़ो/ग_लिखो)
 */
व्योम get_event_and_umask(अक्षर *cas_count_cfg, पूर्णांक count, bool op)
अणु
	अक्षर *token[MAX_TOKENS];
	पूर्णांक i = 0;

	म_जोड़ो(cas_count_cfg, ",");
	token[0] = म_मोहर(cas_count_cfg, "=,");

	क्रम (i = 1; i < MAX_TOKENS; i++)
		token[i] = म_मोहर(शून्य, "=,");

	क्रम (i = 0; i < MAX_TOKENS; i++) अणु
		अगर (!token[i])
			अवरोध;
		अगर (म_भेद(token[i], "event") == 0) अणु
			अगर (op == READ)
				imc_counters_config[count][READ].event =
				म_से_दीर्घ(token[i + 1], शून्य, 16);
			अन्यथा
				imc_counters_config[count][WRITE].event =
				म_से_दीर्घ(token[i + 1], शून्य, 16);
		पूर्ण
		अगर (म_भेद(token[i], "umask") == 0) अणु
			अगर (op == READ)
				imc_counters_config[count][READ].umask =
				म_से_दीर्घ(token[i + 1], शून्य, 16);
			अन्यथा
				imc_counters_config[count][WRITE].umask =
				म_से_दीर्घ(token[i + 1], शून्य, 16);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक खोलो_perf_event(पूर्णांक i, पूर्णांक cpu_no, पूर्णांक j)
अणु
	imc_counters_config[i][j].fd =
		perf_event_खोलो(&imc_counters_config[i][j].pe, -1, cpu_no, -1,
				PERF_FLAG_FD_CLOEXEC);

	अगर (imc_counters_config[i][j].fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Error opening leader %llx\n",
			imc_counters_config[i][j].pe.config);

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* Get type and config (पढ़ो and ग_लिखो) of an iMC counter */
अटल पूर्णांक पढ़ो_from_imc_dir(अक्षर *imc_dir, पूर्णांक count)
अणु
	अक्षर cas_count_cfg[1024], imc_counter_cfg[1024], imc_counter_type[1024];
	खाता *fp;

	/* Get type of iMC counter */
	प्र_लिखो(imc_counter_type, "%s%s", imc_dir, "type");
	fp = ख_खोलो(imc_counter_type, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open imc counter type file");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%u", &imc_counters_config[count][READ].type) <= 0) अणु
		लिखो_त्रुटि("Could not get imc type");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	imc_counters_config[count][WRITE].type =
				imc_counters_config[count][READ].type;

	/* Get पढ़ो config */
	प्र_लिखो(imc_counter_cfg, "%s%s", imc_dir, READ_खाता_NAME);
	fp = ख_खोलो(imc_counter_cfg, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open imc config file");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%s", cas_count_cfg) <= 0) अणु
		लिखो_त्रुटि("Could not get imc cas count read");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	get_event_and_umask(cas_count_cfg, count, READ);

	/* Get ग_लिखो config */
	प्र_लिखो(imc_counter_cfg, "%s%s", imc_dir, WRITE_खाता_NAME);
	fp = ख_खोलो(imc_counter_cfg, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open imc config file");

		वापस -1;
	पूर्ण
	अगर  (ख_पूछो(fp, "%s", cas_count_cfg) <= 0) अणु
		लिखो_त्रुटि("Could not get imc cas count write");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	get_event_and_umask(cas_count_cfg, count, WRITE);

	वापस 0;
पूर्ण

/*
 * A प्रणाली can have 'n' number of iMC (Integrated Memory Controller)
 * counters, get that 'n'. For each iMC counter get it's type and config.
 * Also, each counter has two configs, one क्रम पढ़ो and the other क्रम ग_लिखो.
 * A config again has two parts, event and umask.
 * Enumerate all these details पूर्णांकo an array of काष्ठाures.
 *
 * Return: >= 0 on success. < 0 on failure.
 */
अटल पूर्णांक num_of_imcs(व्योम)
अणु
	अक्षर imc_dir[512], *temp;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा dirent *ep;
	पूर्णांक ret;
	सूची *dp;

	dp = सूची_खोलो(DYN_PMU_PATH);
	अगर (dp) अणु
		जबतक ((ep = सूची_पढ़ो(dp))) अणु
			temp = म_माला(ep->d_name, UNCORE_IMC);
			अगर (!temp)
				जारी;

			/*
			 * imc counters are named as "uncore_imc_<n>", hence
			 * increment the poपूर्णांकer to poपूर्णांक to <n>. Note that
			 * माप(UNCORE_IMC) would count क्रम null अक्षरacter as
			 * well and hence the last underscore अक्षरacter in
			 * uncore_imc'_' need not be counted.
			 */
			temp = temp + माप(UNCORE_IMC);

			/*
			 * Some directories under "DYN_PMU_PATH" could have
			 * names like "uncore_imc_free_running", hence, check अगर
			 * first अक्षरacter is a numerical digit or not.
			 */
			अगर (temp[0] >= '0' && temp[0] <= '9') अणु
				प्र_लिखो(imc_dir, "%s/%s/", DYN_PMU_PATH,
					ep->d_name);
				ret = पढ़ो_from_imc_dir(imc_dir, count);
				अगर (ret) अणु
					बंद_सूची(dp);

					वापस ret;
				पूर्ण
				count++;
			पूर्ण
		पूर्ण
		बंद_सूची(dp);
		अगर (count == 0) अणु
			लिखो_त्रुटि("Unable find iMC counters!\n");

			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		लिखो_त्रुटि("Unable to open PMU directory!\n");

		वापस -1;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक initialize_mem_bw_imc(व्योम)
अणु
	पूर्णांक imc, j;

	imcs = num_of_imcs();
	अगर (imcs <= 0)
		वापस imcs;

	/* Initialize perf_event_attr काष्ठाures क्रम all iMC's */
	क्रम (imc = 0; imc < imcs; imc++) अणु
		क्रम (j = 0; j < 2; j++)
			membw_initialize_perf_event_attr(imc, j);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * get_mem_bw_imc:	Memory band width as reported by iMC counters
 * @cpu_no:		CPU number that the benchmark PID is binded to
 * @bw_report:		Bandwidth report type (पढ़ोs, ग_लिखोs)
 *
 * Memory B/W utilized by a process on a socket can be calculated using
 * iMC counters. Perf events are used to पढ़ो these counters.
 *
 * Return: = 0 on success. < 0 on failure.
 */
अटल पूर्णांक get_mem_bw_imc(पूर्णांक cpu_no, अक्षर *bw_report, भग्न *bw_imc)
अणु
	भग्न पढ़ोs, ग_लिखोs, of_mul_पढ़ो, of_mul_ग_लिखो;
	पूर्णांक imc, j, ret;

	/* Start all iMC counters to log values (both पढ़ो and ग_लिखो) */
	पढ़ोs = 0, ग_लिखोs = 0, of_mul_पढ़ो = 1, of_mul_ग_लिखो = 1;
	क्रम (imc = 0; imc < imcs; imc++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			ret = खोलो_perf_event(imc, cpu_no, j);
			अगर (ret)
				वापस -1;
		पूर्ण
		क्रम (j = 0; j < 2; j++)
			membw_ioctl_perf_event_ioc_reset_enable(imc, j);
	पूर्ण

	sleep(1);

	/* Stop counters after a second to get results (both पढ़ो and ग_लिखो) */
	क्रम (imc = 0; imc < imcs; imc++) अणु
		क्रम (j = 0; j < 2; j++)
			membw_ioctl_perf_event_ioc_disable(imc, j);
	पूर्ण

	/*
	 * Get results which are stored in काष्ठा type imc_counter_config
	 * Take over flow पूर्णांकo consideration beक्रमe calculating total b/w
	 */
	क्रम (imc = 0; imc < imcs; imc++) अणु
		काष्ठा imc_counter_config *r =
			&imc_counters_config[imc][READ];
		काष्ठा imc_counter_config *w =
			&imc_counters_config[imc][WRITE];

		अगर (पढ़ो(r->fd, &r->वापस_value,
			 माप(काष्ठा membw_पढ़ो_क्रमmat)) == -1) अणु
			लिखो_त्रुटि("Couldn't get read b/w through iMC");

			वापस -1;
		पूर्ण

		अगर (पढ़ो(w->fd, &w->वापस_value,
			 माप(काष्ठा membw_पढ़ो_क्रमmat)) == -1) अणु
			लिखो_त्रुटि("Couldn't get write bw through iMC");

			वापस -1;
		पूर्ण

		__u64 r_समय_enabled = r->वापस_value.समय_enabled;
		__u64 r_समय_running = r->वापस_value.समय_running;

		अगर (r_समय_enabled != r_समय_running)
			of_mul_पढ़ो = (भग्न)r_समय_enabled /
					(भग्न)r_समय_running;

		__u64 w_समय_enabled = w->वापस_value.समय_enabled;
		__u64 w_समय_running = w->वापस_value.समय_running;

		अगर (w_समय_enabled != w_समय_running)
			of_mul_ग_लिखो = (भग्न)w_समय_enabled /
					(भग्न)w_समय_running;
		पढ़ोs += r->वापस_value.value * of_mul_पढ़ो * SCALE;
		ग_लिखोs += w->वापस_value.value * of_mul_ग_लिखो * SCALE;
	पूर्ण

	क्रम (imc = 0; imc < imcs; imc++) अणु
		बंद(imc_counters_config[imc][READ].fd);
		बंद(imc_counters_config[imc][WRITE].fd);
	पूर्ण

	अगर (म_भेद(bw_report, "reads") == 0) अणु
		*bw_imc = पढ़ोs;
		वापस 0;
	पूर्ण

	अगर (म_भेद(bw_report, "writes") == 0) अणु
		*bw_imc = ग_लिखोs;
		वापस 0;
	पूर्ण

	*bw_imc = पढ़ोs + ग_लिखोs;
	वापस 0;
पूर्ण

व्योम set_mbm_path(स्थिर अक्षर *ctrlgrp, स्थिर अक्षर *mongrp, पूर्णांक resource_id)
अणु
	अगर (ctrlgrp && mongrp)
		प्र_लिखो(mbm_total_path, CON_MON_MBM_LOCAL_BYTES_PATH,
			RESCTRL_PATH, ctrlgrp, mongrp, resource_id);
	अन्यथा अगर (!ctrlgrp && mongrp)
		प्र_लिखो(mbm_total_path, MON_MBM_LOCAL_BYTES_PATH, RESCTRL_PATH,
			mongrp, resource_id);
	अन्यथा अगर (ctrlgrp && !mongrp)
		प्र_लिखो(mbm_total_path, CON_MBM_LOCAL_BYTES_PATH, RESCTRL_PATH,
			ctrlgrp, resource_id);
	अन्यथा अगर (!ctrlgrp && !mongrp)
		प्र_लिखो(mbm_total_path, MBM_LOCAL_BYTES_PATH, RESCTRL_PATH,
			resource_id);
पूर्ण

/*
 * initialize_mem_bw_resctrl:	Appropriately populate "mbm_total_path"
 * @ctrlgrp:			Name of the control monitor group (con_mon grp)
 * @mongrp:			Name of the monitor group (mon grp)
 * @cpu_no:			CPU number that the benchmark PID is binded to
 * @resctrl_val:		Resctrl feature (Eg: mbm, mba.. etc)
 */
अटल व्योम initialize_mem_bw_resctrl(स्थिर अक्षर *ctrlgrp, स्थिर अक्षर *mongrp,
				      पूर्णांक cpu_no, अक्षर *resctrl_val)
अणु
	पूर्णांक resource_id;

	अगर (get_resource_id(cpu_no, &resource_id) < 0) अणु
		लिखो_त्रुटि("Could not get resource_id");
		वापस;
	पूर्ण

	अगर (!म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR)))
		set_mbm_path(ctrlgrp, mongrp, resource_id);

	अगर (!म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR))) अणु
		अगर (ctrlgrp)
			प्र_लिखो(mbm_total_path, CON_MBM_LOCAL_BYTES_PATH,
				RESCTRL_PATH, ctrlgrp, resource_id);
		अन्यथा
			प्र_लिखो(mbm_total_path, MBM_LOCAL_BYTES_PATH,
				RESCTRL_PATH, resource_id);
	पूर्ण
पूर्ण

/*
 * Get MBM Local bytes as reported by resctrl FS
 * For MBM,
 * 1. If con_mon grp and mon grp are given, then पढ़ो from con_mon grp's mon grp
 * 2. If only con_mon grp is given, then पढ़ो from con_mon grp
 * 3. If both are not given, then पढ़ो from root con_mon grp
 * For MBA,
 * 1. If con_mon grp is given, then पढ़ो from it
 * 2. If con_mon grp is not given, then पढ़ो from root con_mon grp
 */
अटल पूर्णांक get_mem_bw_resctrl(अचिन्हित दीर्घ *mbm_total)
अणु
	खाता *fp;

	fp = ख_खोलो(mbm_total_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open total bw file");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%lu", mbm_total) <= 0) अणु
		लिखो_त्रुटि("Could not get mbm local bytes");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

pid_t bm_pid, ppid;

व्योम ctrlc_handler(पूर्णांक signum, siginfo_t *info, व्योम *ptr)
अणु
	समाप्त(bm_pid, SIGKILL);
	umount_resctrlfs();
	tests_cleanup();
	ksft_prपूर्णांक_msg("Ending\n\n");

	निकास(निकास_सफल);
पूर्ण

/*
 * prपूर्णांक_results_bw:	the memory bandwidth results are stored in a file
 * @filename:		file that stores the results
 * @bm_pid:		child pid that runs benchmark
 * @bw_imc:		perf imc counter value
 * @bw_resc:		memory bandwidth value
 *
 * Return:		0 on success. non-zero on failure.
 */
अटल पूर्णांक prपूर्णांक_results_bw(अक्षर *filename,  पूर्णांक bm_pid, भग्न bw_imc,
			    अचिन्हित दीर्घ bw_resc)
अणु
	अचिन्हित दीर्घ dअगरf = भ_असल(bw_imc - bw_resc);
	खाता *fp;

	अगर (म_भेद(filename, "stdio") == 0 || म_भेद(filename, "stderr") == 0) अणु
		म_लिखो("Pid: %d \t Mem_BW_iMC: %f \t ", bm_pid, bw_imc);
		म_लिखो("Mem_BW_resc: %lu \t Difference: %lu\n", bw_resc, dअगरf);
	पूर्ण अन्यथा अणु
		fp = ख_खोलो(filename, "a");
		अगर (!fp) अणु
			लिखो_त्रुटि("Cannot open results file");

			वापस त्रुटि_सं;
		पूर्ण
		अगर (ख_लिखो(fp, "Pid: %d \t Mem_BW_iMC: %f \t Mem_BW_resc: %lu \t Difference: %lu\n",
			    bm_pid, bw_imc, bw_resc, dअगरf) <= 0) अणु
			ख_बंद(fp);
			लिखो_त्रुटि("Could not log results.");

			वापस त्रुटि_सं;
		पूर्ण
		ख_बंद(fp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_cmt_path(स्थिर अक्षर *ctrlgrp, स्थिर अक्षर *mongrp, अक्षर sock_num)
अणु
	अगर (म_माप(ctrlgrp) && म_माप(mongrp))
		प्र_लिखो(llc_occup_path,	CON_MON_LCC_OCCUP_PATH,	RESCTRL_PATH,
			ctrlgrp, mongrp, sock_num);
	अन्यथा अगर (!म_माप(ctrlgrp) && म_माप(mongrp))
		प्र_लिखो(llc_occup_path,	MON_LCC_OCCUP_PATH, RESCTRL_PATH,
			mongrp, sock_num);
	अन्यथा अगर (म_माप(ctrlgrp) && !म_माप(mongrp))
		प्र_लिखो(llc_occup_path,	CON_LCC_OCCUP_PATH, RESCTRL_PATH,
			ctrlgrp, sock_num);
	अन्यथा अगर (!म_माप(ctrlgrp) && !म_माप(mongrp))
		प्र_लिखो(llc_occup_path, LCC_OCCUP_PATH,	RESCTRL_PATH, sock_num);
पूर्ण

/*
 * initialize_llc_occu_resctrl:	Appropriately populate "llc_occup_path"
 * @ctrlgrp:			Name of the control monitor group (con_mon grp)
 * @mongrp:			Name of the monitor group (mon grp)
 * @cpu_no:			CPU number that the benchmark PID is binded to
 * @resctrl_val:		Resctrl feature (Eg: cat, cmt.. etc)
 */
अटल व्योम initialize_llc_occu_resctrl(स्थिर अक्षर *ctrlgrp, स्थिर अक्षर *mongrp,
					पूर्णांक cpu_no, अक्षर *resctrl_val)
अणु
	पूर्णांक resource_id;

	अगर (get_resource_id(cpu_no, &resource_id) < 0) अणु
		लिखो_त्रुटि("# Unable to resource_id");
		वापस;
	पूर्ण

	अगर (!म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)))
		set_cmt_path(ctrlgrp, mongrp, resource_id);
पूर्ण

अटल पूर्णांक
measure_vals(काष्ठा resctrl_val_param *param, अचिन्हित दीर्घ *bw_resc_start)
अणु
	अचिन्हित दीर्घ bw_resc, bw_resc_end;
	भग्न bw_imc;
	पूर्णांक ret;

	/*
	 * Measure memory bandwidth from resctrl and from
	 * another source which is perf imc value or could
	 * be something अन्यथा अगर perf imc event is not available.
	 * Compare the two values to validate resctrl value.
	 * It takes 1sec to measure the data.
	 */
	ret = get_mem_bw_imc(param->cpu_no, param->bw_report, &bw_imc);
	अगर (ret < 0)
		वापस ret;

	ret = get_mem_bw_resctrl(&bw_resc_end);
	अगर (ret < 0)
		वापस ret;

	bw_resc = (bw_resc_end - *bw_resc_start) / MB;
	ret = prपूर्णांक_results_bw(param->filename, bm_pid, bw_imc, bw_resc);
	अगर (ret)
		वापस ret;

	*bw_resc_start = bw_resc_end;

	वापस 0;
पूर्ण

/*
 * resctrl_val:	execute benchmark and measure memory bandwidth on
 *			the benchmark
 * @benchmark_cmd:	benchmark command and its arguments
 * @param:		parameters passed to resctrl_val()
 *
 * Return:		0 on success. non-zero on failure.
 */
पूर्णांक resctrl_val(अक्षर **benchmark_cmd, काष्ठा resctrl_val_param *param)
अणु
	अक्षर *resctrl_val = param->resctrl_val;
	अचिन्हित दीर्घ bw_resc_start = 0;
	काष्ठा sigaction sigact;
	पूर्णांक ret = 0, pipefd[2];
	अक्षर pipe_message = 0;
	जोड़ sigval value;

	अगर (म_भेद(param->filename, "") == 0)
		प्र_लिखो(param->filename, "stdio");

	अगर (!म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR)) ||
	    !म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR))) अणु
		ret = validate_bw_report_request(param->bw_report);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = remount_resctrlfs(param->mum_resctrlfs);
	अगर (ret)
		वापस ret;

	/*
	 * If benchmark wasn't successfully started by child, then child should
	 * समाप्त parent, so save parent's pid
	 */
	ppid = getpid();

	अगर (pipe(pipefd)) अणु
		लिखो_त्रुटि("# Unable to create pipe");

		वापस -1;
	पूर्ण

	/*
	 * Fork to start benchmark, save child's pid so that it can be समाप्तed
	 * when needed
	 */
	bm_pid = विभाजन();
	अगर (bm_pid == -1) अणु
		लिखो_त्रुटि("# Unable to fork");

		वापस -1;
	पूर्ण

	अगर (bm_pid == 0) अणु
		/*
		 * Mask all संकेतs except SIGUSR1, parent uses SIGUSR1 to
		 * start benchmark
		 */
		sigfillset(&sigact.sa_mask);
		sigdअन्यथाt(&sigact.sa_mask, SIGUSR1);

		sigact.sa_sigaction = run_benchmark;
		sigact.sa_flags = SA_SIGINFO;

		/* Register क्रम "SIGUSR1" संकेत from parent */
		अगर (sigaction(SIGUSR1, &sigact, शून्य))
			PARENT_EXIT("Can't register child for signal");

		/* Tell parent that child is पढ़ोy */
		बंद(pipefd[0]);
		pipe_message = 1;
		अगर (ग_लिखो(pipefd[1], &pipe_message, माप(pipe_message)) <
		    माप(pipe_message)) अणु
			लिखो_त्रुटि("# failed signaling parent process");
			बंद(pipefd[1]);
			वापस -1;
		पूर्ण
		बंद(pipefd[1]);

		/* Suspend child until delivery of "SIGUSR1" from parent */
		संक_रोको(&sigact.sa_mask);

		PARENT_EXIT("Child is done");
	पूर्ण

	ksft_prपूर्णांक_msg("Benchmark PID: %d\n", bm_pid);

	/*
	 * Register CTRL-C handler क्रम parent, as it has to समाप्त benchmark
	 * beक्रमe निकासing
	 */
	sigact.sa_sigaction = ctrlc_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	अगर (sigaction(संक_विघ्न, &sigact, शून्य) ||
	    sigaction(SIGHUP, &sigact, शून्य)) अणु
		लिखो_त्रुटि("# sigaction");
		ret = त्रुटि_सं;
		जाओ out;
	पूर्ण

	value.sival_ptr = benchmark_cmd;

	/* Taskset benchmark to specअगरied cpu */
	ret = taskset_benchmark(bm_pid, param->cpu_no);
	अगर (ret)
		जाओ out;

	/* Write benchmark to specअगरied control&monitoring grp in resctrl FS */
	ret = ग_लिखो_bm_pid_to_resctrl(bm_pid, param->ctrlgrp, param->mongrp,
				      resctrl_val);
	अगर (ret)
		जाओ out;

	अगर (!म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR)) ||
	    !म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR))) अणु
		ret = initialize_mem_bw_imc();
		अगर (ret)
			जाओ out;

		initialize_mem_bw_resctrl(param->ctrlgrp, param->mongrp,
					  param->cpu_no, resctrl_val);
	पूर्ण अन्यथा अगर (!म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)))
		initialize_llc_occu_resctrl(param->ctrlgrp, param->mongrp,
					    param->cpu_no, resctrl_val);

	/* Parent रुकोs क्रम child to be पढ़ोy. */
	बंद(pipefd[1]);
	जबतक (pipe_message != 1) अणु
		अगर (पढ़ो(pipefd[0], &pipe_message, माप(pipe_message)) <
		    माप(pipe_message)) अणु
			लिखो_त्रुटि("# failed reading message from child process");
			बंद(pipefd[0]);
			जाओ out;
		पूर्ण
	पूर्ण
	बंद(pipefd[0]);

	/* Signal child to start benchmark */
	अगर (sigqueue(bm_pid, SIGUSR1, value) == -1) अणु
		लिखो_त्रुटि("# sigqueue SIGUSR1 to child");
		ret = त्रुटि_सं;
		जाओ out;
	पूर्ण

	/* Give benchmark enough समय to fully run */
	sleep(1);

	/* Test runs until the callback setup() tells the test to stop. */
	जबतक (1) अणु
		अगर (!म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR)) ||
		    !म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR))) अणु
			ret = param->setup(1, param);
			अगर (ret) अणु
				ret = 0;
				अवरोध;
			पूर्ण

			ret = measure_vals(param, &bw_resc_start);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अगर (!म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR))) अणु
			ret = param->setup(1, param);
			अगर (ret) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			sleep(1);
			ret = measure_cache_vals(param, bm_pid);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

out:
	समाप्त(bm_pid, SIGKILL);
	umount_resctrlfs();

	वापस ret;
पूर्ण
