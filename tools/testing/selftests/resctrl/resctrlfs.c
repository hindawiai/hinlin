<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Basic resctrl file प्रणाली operations
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Authors:
 *    Sai Praneeth Prakhya <sai.praneeth.prakhya@पूर्णांकel.com>,
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 */
#समावेश "resctrl.h"

अटल पूर्णांक find_resctrl_mount(अक्षर *buffer)
अणु
	खाता *mounts;
	अक्षर line[256], *fs, *mntpoपूर्णांक;

	mounts = ख_खोलो("/proc/mounts", "r");
	अगर (!mounts) अणु
		लिखो_त्रुटि("/proc/mounts");
		वापस -ENXIO;
	पूर्ण
	जबतक (!ख_पूर्ण(mounts)) अणु
		अगर (!ख_माला_लो(line, 256, mounts))
			अवरोध;
		fs = म_मोहर(line, " \t");
		अगर (!fs)
			जारी;
		mntpoपूर्णांक = म_मोहर(शून्य, " \t");
		अगर (!mntpoपूर्णांक)
			जारी;
		fs = म_मोहर(शून्य, " \t");
		अगर (!fs)
			जारी;
		अगर (म_भेद(fs, "resctrl"))
			जारी;

		ख_बंद(mounts);
		अगर (buffer)
			म_नकलन(buffer, mntpoपूर्णांक, 256);

		वापस 0;
	पूर्ण

	ख_बंद(mounts);

	वापस -ENOENT;
पूर्ण

/*
 * remount_resctrlfs - Remount resctrl FS at /sys/fs/resctrl
 * @mum_resctrlfs:	Should the resctrl FS be remounted?
 *
 * If not mounted, mount it.
 * If mounted and mum_resctrlfs then remount resctrl FS.
 * If mounted and !mum_resctrlfs then noop
 *
 * Return: 0 on success, non-zero on failure
 */
पूर्णांक remount_resctrlfs(bool mum_resctrlfs)
अणु
	अक्षर mountpoपूर्णांक[256];
	पूर्णांक ret;

	ret = find_resctrl_mount(mountpoपूर्णांक);
	अगर (ret)
		म_नकल(mountpoपूर्णांक, RESCTRL_PATH);

	अगर (!ret && mum_resctrlfs && umount(mountpoपूर्णांक))
		ksft_prपूर्णांक_msg("Fail: unmounting \"%s\"\n", mountpoपूर्णांक);

	अगर (!ret && !mum_resctrlfs)
		वापस 0;

	ksft_prपूर्णांक_msg("Mounting resctrl to \"%s\"\n", RESCTRL_PATH);
	ret = mount("resctrl", RESCTRL_PATH, "resctrl", 0, शून्य);
	अगर (ret)
		लिखो_त्रुटि("# mount");

	वापस ret;
पूर्ण

पूर्णांक umount_resctrlfs(व्योम)
अणु
	अगर (find_resctrl_mount(शून्य))
		वापस 0;

	अगर (umount(RESCTRL_PATH)) अणु
		लिखो_त्रुटि("# Unable to umount resctrl");

		वापस त्रुटि_सं;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * get_resource_id - Get socket number/l3 id क्रम a specअगरied CPU
 * @cpu_no:	CPU number
 * @resource_id: Socket number or l3_id
 *
 * Return: >= 0 on success, < 0 on failure.
 */
पूर्णांक get_resource_id(पूर्णांक cpu_no, पूर्णांक *resource_id)
अणु
	अक्षर phys_pkg_path[1024];
	खाता *fp;

	अगर (is_amd)
		प्र_लिखो(phys_pkg_path, "%s%d/cache/index3/id",
			PHYS_ID_PATH, cpu_no);
	अन्यथा
		प्र_लिखो(phys_pkg_path, "%s%d/topology/physical_package_id",
			PHYS_ID_PATH, cpu_no);

	fp = ख_खोलो(phys_pkg_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open physical_package_id");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%d", resource_id) <= 0) अणु
		लिखो_त्रुटि("Could not get socket number or l3 id");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * get_cache_size - Get cache size क्रम a specअगरied CPU
 * @cpu_no:	CPU number
 * @cache_type:	Cache level L2/L3
 * @cache_size:	poपूर्णांकer to cache_size
 *
 * Return: = 0 on success, < 0 on failure.
 */
पूर्णांक get_cache_size(पूर्णांक cpu_no, अक्षर *cache_type, अचिन्हित दीर्घ *cache_size)
अणु
	अक्षर cache_path[1024], cache_str[64];
	पूर्णांक length, i, cache_num;
	खाता *fp;

	अगर (!म_भेद(cache_type, "L3")) अणु
		cache_num = 3;
	पूर्ण अन्यथा अगर (!म_भेद(cache_type, "L2")) अणु
		cache_num = 2;
	पूर्ण अन्यथा अणु
		लिखो_त्रुटि("Invalid cache level");
		वापस -1;
	पूर्ण

	प्र_लिखो(cache_path, "/sys/bus/cpu/devices/cpu%d/cache/index%d/size",
		cpu_no, cache_num);
	fp = ख_खोलो(cache_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open cache size");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%s", cache_str) <= 0) अणु
		लिखो_त्रुटि("Could not get cache_size");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	length = (पूर्णांक)म_माप(cache_str);

	*cache_size = 0;

	क्रम (i = 0; i < length; i++) अणु
		अगर ((cache_str[i] >= '0') && (cache_str[i] <= '9'))

			*cache_size = *cache_size * 10 + (cache_str[i] - '0');

		अन्यथा अगर (cache_str[i] == 'K')

			*cache_size = *cache_size * 1024;

		अन्यथा अगर (cache_str[i] == 'M')

			*cache_size = *cache_size * 1024 * 1024;

		अन्यथा
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CORE_SIBLINGS_PATH	"/sys/bus/cpu/devices/cpu"

/*
 * get_cbm_mask - Get cbm mask क्रम given cache
 * @cache_type:	Cache level L2/L3
 * @cbm_mask:	cbm_mask वापसed as a string
 *
 * Return: = 0 on success, < 0 on failure.
 */
पूर्णांक get_cbm_mask(अक्षर *cache_type, अक्षर *cbm_mask)
अणु
	अक्षर cbm_mask_path[1024];
	खाता *fp;

	अगर (!cbm_mask)
		वापस -1;

	प्र_लिखो(cbm_mask_path, "%s/%s/cbm_mask", CBM_MASK_PATH, cache_type);

	fp = ख_खोलो(cbm_mask_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open cache level");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%s", cbm_mask) <= 0) अणु
		लिखो_त्रुटि("Could not get max cbm_mask");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * get_core_sibling - Get sibling core id from the same socket क्रम given CPU
 * @cpu_no:	CPU number
 *
 * Return:	> 0 on success, < 0 on failure.
 */
पूर्णांक get_core_sibling(पूर्णांक cpu_no)
अणु
	अक्षर core_siblings_path[1024], cpu_list_str[64];
	पूर्णांक sibling_cpu_no = -1;
	खाता *fp;

	प्र_लिखो(core_siblings_path, "%s%d/topology/core_siblings_list",
		CORE_SIBLINGS_PATH, cpu_no);

	fp = ख_खोलो(core_siblings_path, "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open core siblings path");

		वापस -1;
	पूर्ण
	अगर (ख_पूछो(fp, "%s", cpu_list_str) <= 0) अणु
		लिखो_त्रुटि("Could not get core_siblings list");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	अक्षर *token = म_मोहर(cpu_list_str, "-,");

	जबतक (token) अणु
		sibling_cpu_no = म_से_प(token);
		/* Skipping core 0 as we करोn't want to run test on core 0 */
		अगर (sibling_cpu_no != 0 && sibling_cpu_no != cpu_no)
			अवरोध;
		token = म_मोहर(शून्य, "-,");
	पूर्ण

	वापस sibling_cpu_no;
पूर्ण

/*
 * taskset_benchmark - Taskset PID (i.e. benchmark) to a specअगरied cpu
 * @bm_pid:	PID that should be binded
 * @cpu_no:	CPU number at which the PID would be binded
 *
 * Return: 0 on success, non-zero on failure
 */
पूर्णांक taskset_benchmark(pid_t bm_pid, पूर्णांक cpu_no)
अणु
	cpu_set_t my_set;

	CPU_ZERO(&my_set);
	CPU_SET(cpu_no, &my_set);

	अगर (sched_setaffinity(bm_pid, माप(cpu_set_t), &my_set)) अणु
		लिखो_त्रुटि("Unable to taskset benchmark");

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * run_benchmark - Run a specअगरied benchmark or fill_buf (शेष benchmark)
 *		   in specअगरied संकेत. Direct benchmark stdio to /dev/null.
 * @signum:	संकेत number
 * @info:	संकेत info
 * @ucontext:	user context in संकेत handling
 *
 * Return: व्योम
 */
व्योम run_benchmark(पूर्णांक signum, siginfo_t *info, व्योम *ucontext)
अणु
	पूर्णांक operation, ret, दो_स्मृति_and_init_memory, memflush;
	अचिन्हित दीर्घ span, buffer_span;
	अक्षर **benchmark_cmd;
	अक्षर resctrl_val[64];
	खाता *fp;

	benchmark_cmd = info->si_ptr;

	/*
	 * Direct stdio of child to /dev/null, so that only parent ग_लिखोs to
	 * stdio (console)
	 */
	fp = ख_व_खोलो("/dev/null", "w", मानक_निकास);
	अगर (!fp)
		PARENT_EXIT("Unable to direct benchmark status to /dev/null");

	अगर (म_भेद(benchmark_cmd[0], "fill_buf") == 0) अणु
		/* Execute शेष fill_buf benchmark */
		span = म_से_अदीर्घ(benchmark_cmd[1], शून्य, 10);
		दो_स्मृति_and_init_memory = म_से_प(benchmark_cmd[2]);
		memflush =  म_से_प(benchmark_cmd[3]);
		operation = म_से_प(benchmark_cmd[4]);
		प्र_लिखो(resctrl_val, "%s", benchmark_cmd[5]);

		अगर (म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)))
			buffer_span = span * MB;
		अन्यथा
			buffer_span = span;

		अगर (run_fill_buf(buffer_span, दो_स्मृति_and_init_memory, memflush,
				 operation, resctrl_val))
			ख_लिखो(मानक_त्रुटि, "Error in running fill buffer\n");
	पूर्ण अन्यथा अणु
		/* Execute specअगरied benchmark */
		ret = execvp(benchmark_cmd[0], benchmark_cmd);
		अगर (ret)
			लिखो_त्रुटि("wrong\n");
	पूर्ण

	ख_बंद(मानक_निकास);
	PARENT_EXIT("Unable to run specified benchmark");
पूर्ण

/*
 * create_grp - Create a group only अगर one करोesn't exist
 * @grp_name:	Name of the group
 * @grp:	Full path and name of the group
 * @parent_grp:	Full path and name of the parent group
 *
 * Return: 0 on success, non-zero on failure
 */
अटल पूर्णांक create_grp(स्थिर अक्षर *grp_name, अक्षर *grp, स्थिर अक्षर *parent_grp)
अणु
	पूर्णांक found_grp = 0;
	काष्ठा dirent *ep;
	सूची *dp;

	/*
	 * At this poपूर्णांक, we are guaranteed to have resctrl FS mounted and अगर
	 * length of grp_name == 0, it means, user wants to use root con_mon
	 * grp, so करो nothing
	 */
	अगर (म_माप(grp_name) == 0)
		वापस 0;

	/* Check अगर requested grp exists or not */
	dp = सूची_खोलो(parent_grp);
	अगर (dp) अणु
		जबतक ((ep = सूची_पढ़ो(dp)) != शून्य) अणु
			अगर (म_भेद(ep->d_name, grp_name) == 0)
				found_grp = 1;
		पूर्ण
		बंद_सूची(dp);
	पूर्ण अन्यथा अणु
		लिखो_त्रुटि("Unable to open resctrl for group");

		वापस -1;
	पूर्ण

	/* Requested grp करोesn't exist, hence create it */
	अगर (found_grp == 0) अणु
		अगर (सूची_गढ़ो(grp, 0) == -1) अणु
			लिखो_त्रुटि("Unable to create group");

			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_pid_to_tasks(अक्षर *tasks, pid_t pid)
अणु
	खाता *fp;

	fp = ख_खोलो(tasks, "w");
	अगर (!fp) अणु
		लिखो_त्रुटि("Failed to open tasks file");

		वापस -1;
	पूर्ण
	अगर (ख_लिखो(fp, "%d\n", pid) < 0) अणु
		लिखो_त्रुटि("Failed to wr pid to tasks file");
		ख_बंद(fp);

		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * ग_लिखो_bm_pid_to_resctrl - Write a PID (i.e. benchmark) to resctrl FS
 * @bm_pid:		PID that should be written
 * @ctrlgrp:		Name of the control monitor group (con_mon grp)
 * @mongrp:		Name of the monitor group (mon grp)
 * @resctrl_val:	Resctrl feature (Eg: mbm, mba.. etc)
 *
 * If a con_mon grp is requested, create it and ग_लिखो pid to it, otherwise
 * ग_लिखो pid to root con_mon grp.
 * If a mon grp is requested, create it and ग_लिखो pid to it, otherwise
 * pid is not written, this means that pid is in con_mon grp and hence
 * should consult con_mon grp's mon_data directory क्रम results.
 *
 * Return: 0 on success, non-zero on failure
 */
पूर्णांक ग_लिखो_bm_pid_to_resctrl(pid_t bm_pid, अक्षर *ctrlgrp, अक्षर *mongrp,
			    अक्षर *resctrl_val)
अणु
	अक्षर controlgroup[128], monitorgroup[512], monitorgroup_p[256];
	अक्षर tasks[1024];
	पूर्णांक ret = 0;

	अगर (म_माप(ctrlgrp))
		प्र_लिखो(controlgroup, "%s/%s", RESCTRL_PATH, ctrlgrp);
	अन्यथा
		प्र_लिखो(controlgroup, "%s", RESCTRL_PATH);

	/* Create control and monitoring group and ग_लिखो pid पूर्णांकo it */
	ret = create_grp(ctrlgrp, controlgroup, RESCTRL_PATH);
	अगर (ret)
		जाओ out;
	प्र_लिखो(tasks, "%s/tasks", controlgroup);
	ret = ग_लिखो_pid_to_tasks(tasks, bm_pid);
	अगर (ret)
		जाओ out;

	/* Create mon grp and ग_लिखो pid पूर्णांकo it क्रम "mbm" and "cmt" test */
	अगर (!म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)) ||
	    !म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR))) अणु
		अगर (म_माप(mongrp)) अणु
			प्र_लिखो(monitorgroup_p, "%s/mon_groups", controlgroup);
			प्र_लिखो(monitorgroup, "%s/%s", monitorgroup_p, mongrp);
			ret = create_grp(mongrp, monitorgroup, monitorgroup_p);
			अगर (ret)
				जाओ out;

			प्र_लिखो(tasks, "%s/mon_groups/%s/tasks",
				controlgroup, mongrp);
			ret = ग_लिखो_pid_to_tasks(tasks, bm_pid);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	ksft_prपूर्णांक_msg("Writing benchmark parameters to resctrl FS\n");
	अगर (ret)
		लिखो_त्रुटि("# writing to resctrlfs");

	वापस ret;
पूर्ण

/*
 * ग_लिखो_schemata - Update schemata of a con_mon grp
 * @ctrlgrp:		Name of the con_mon grp
 * @schemata:		Schemata that should be updated to
 * @cpu_no:		CPU number that the benchmark PID is binded to
 * @resctrl_val:	Resctrl feature (Eg: mbm, mba.. etc)
 *
 * Update schemata of a con_mon grp *only* अगर requested resctrl feature is
 * allocation type
 *
 * Return: 0 on success, non-zero on failure
 */
पूर्णांक ग_लिखो_schemata(अक्षर *ctrlgrp, अक्षर *schemata, पूर्णांक cpu_no, अक्षर *resctrl_val)
अणु
	अक्षर controlgroup[1024], schema[1024], reason[64];
	पूर्णांक resource_id, ret = 0;
	खाता *fp;

	अगर (म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR)) &&
	    म_भेदन(resctrl_val, CAT_STR, माप(CAT_STR)) &&
	    म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)))
		वापस -ENOENT;

	अगर (!schemata) अणु
		ksft_prपूर्णांक_msg("Skipping empty schemata update\n");

		वापस -1;
	पूर्ण

	अगर (get_resource_id(cpu_no, &resource_id) < 0) अणु
		प्र_लिखो(reason, "Failed to get resource id");
		ret = -1;

		जाओ out;
	पूर्ण

	अगर (म_माप(ctrlgrp) != 0)
		प्र_लिखो(controlgroup, "%s/%s/schemata", RESCTRL_PATH, ctrlgrp);
	अन्यथा
		प्र_लिखो(controlgroup, "%s/schemata", RESCTRL_PATH);

	अगर (!म_भेदन(resctrl_val, CAT_STR, माप(CAT_STR)) ||
	    !म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR)))
		प्र_लिखो(schema, "%s%d%c%s", "L3:", resource_id, '=', schemata);
	अगर (!म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR)))
		प्र_लिखो(schema, "%s%d%c%s", "MB:", resource_id, '=', schemata);

	fp = ख_खोलो(controlgroup, "w");
	अगर (!fp) अणु
		प्र_लिखो(reason, "Failed to open control group");
		ret = -1;

		जाओ out;
	पूर्ण

	अगर (ख_लिखो(fp, "%s\n", schema) < 0) अणु
		प्र_लिखो(reason, "Failed to write schemata in control group");
		ख_बंद(fp);
		ret = -1;

		जाओ out;
	पूर्ण
	ख_बंद(fp);

out:
	ksft_prपूर्णांक_msg("Write schema \"%s\" to resctrl FS%s%s\n",
		       schema, ret ? " # " : "",
		       ret ? reason : "");

	वापस ret;
पूर्ण

bool check_resctrlfs_support(व्योम)
अणु
	खाता *inf = ख_खोलो("/proc/filesystems", "r");
	सूची *dp;
	अक्षर *res;
	bool ret = false;

	अगर (!inf)
		वापस false;

	res = fgrep(inf, "nodev\tresctrl\n");

	अगर (res) अणु
		ret = true;
		मुक्त(res);
	पूर्ण

	ख_बंद(inf);

	ksft_prपूर्णांक_msg("%s Check kernel supports resctrl filesystem\n",
		       ret ? "Pass:" : "Fail:");

	अगर (!ret)
		वापस ret;

	dp = सूची_खोलो(RESCTRL_PATH);
	ksft_prपूर्णांक_msg("%s Check resctrl mountpoint \"%s\" exists\n",
		       dp ? "Pass:" : "Fail:", RESCTRL_PATH);
	अगर (dp)
		बंद_सूची(dp);

	ksft_prपूर्णांक_msg("resctrl filesystem %s mounted\n",
		       find_resctrl_mount(शून्य) ? "not" : "is");

	वापस ret;
पूर्ण

अक्षर *fgrep(खाता *inf, स्थिर अक्षर *str)
अणु
	अक्षर line[256];
	पूर्णांक slen = म_माप(str);

	जबतक (!ख_पूर्ण(inf)) अणु
		अगर (!ख_माला_लो(line, 256, inf))
			अवरोध;
		अगर (म_भेदन(line, str, slen))
			जारी;

		वापस strdup(line);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * validate_resctrl_feature_request - Check अगर requested feature is valid.
 * @resctrl_val:	Requested feature
 *
 * Return: True अगर the feature is supported, अन्यथा false
 */
bool validate_resctrl_feature_request(स्थिर अक्षर *resctrl_val)
अणु
	काष्ठा stat statbuf;
	bool found = false;
	अक्षर *res;
	खाता *inf;

	अगर (!resctrl_val)
		वापस false;

	अगर (remount_resctrlfs(false))
		वापस false;

	अगर (!म_भेदन(resctrl_val, CAT_STR, माप(CAT_STR))) अणु
		अगर (!stat(L3_PATH, &statbuf))
			वापस true;
	पूर्ण अन्यथा अगर (!म_भेदन(resctrl_val, MBA_STR, माप(MBA_STR))) अणु
		अगर (!stat(MB_PATH, &statbuf))
			वापस true;
	पूर्ण अन्यथा अगर (!म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR)) ||
		   !म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR))) अणु
		अगर (!stat(L3_MON_PATH, &statbuf)) अणु
			inf = ख_खोलो(L3_MON_FEATURES_PATH, "r");
			अगर (!inf)
				वापस false;

			अगर (!म_भेदन(resctrl_val, CMT_STR, माप(CMT_STR))) अणु
				res = fgrep(inf, "llc_occupancy");
				अगर (res) अणु
					found = true;
					मुक्त(res);
				पूर्ण
			पूर्ण

			अगर (!म_भेदन(resctrl_val, MBM_STR, माप(MBM_STR))) अणु
				res = fgrep(inf, "mbm_total_bytes");
				अगर (res) अणु
					मुक्त(res);
					res = fgrep(inf, "mbm_local_bytes");
					अगर (res) अणु
						found = true;
						मुक्त(res);
					पूर्ण
				पूर्ण
			पूर्ण
			ख_बंद(inf);
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

पूर्णांक filter_dmesg(व्योम)
अणु
	अक्षर line[1024];
	खाता *fp;
	पूर्णांक pipefds[2];
	pid_t pid;
	पूर्णांक ret;

	ret = pipe(pipefds);
	अगर (ret) अणु
		लिखो_त्रुटि("pipe");
		वापस ret;
	पूर्ण
	pid = विभाजन();
	अगर (pid == 0) अणु
		बंद(pipefds[0]);
		dup2(pipefds[1], STDOUT_खाताNO);
		execlp("dmesg", "dmesg", शून्य);
		लिखो_त्रुटि("executing dmesg");
		निकास(1);
	पूर्ण
	बंद(pipefds[1]);
	fp = fकरोpen(pipefds[0], "r");
	अगर (!fp) अणु
		लिखो_त्रुटि("fdopen(pipe)");
		समाप्त(pid, संक_इति);

		वापस -1;
	पूर्ण

	जबतक (ख_माला_लो(line, 1024, fp)) अणु
		अगर (म_माला(line, "intel_rdt:"))
			ksft_prपूर्णांक_msg("dmesg: %s", line);
		अगर (म_माला(line, "resctrl:"))
			ksft_prपूर्णांक_msg("dmesg: %s", line);
	पूर्ण
	ख_बंद(fp);
	रुकोpid(pid, शून्य, 0);

	वापस 0;
पूर्ण

पूर्णांक validate_bw_report_request(अक्षर *bw_report)
अणु
	अगर (म_भेद(bw_report, "reads") == 0)
		वापस 0;
	अगर (म_भेद(bw_report, "writes") == 0)
		वापस 0;
	अगर (म_भेद(bw_report, "nt-writes") == 0) अणु
		म_नकल(bw_report, "writes");
		वापस 0;
	पूर्ण
	अगर (म_भेद(bw_report, "total") == 0)
		वापस 0;

	ख_लिखो(मानक_त्रुटि, "Requested iMC B/W report type unavailable\n");

	वापस -1;
पूर्ण

पूर्णांक perf_event_खोलो(काष्ठा perf_event_attr *hw_event, pid_t pid, पूर्णांक cpu,
		    पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;

	ret = syscall(__NR_perf_event_खोलो, hw_event, pid, cpu,
		      group_fd, flags);
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक count_bits(अचिन्हित दीर्घ n)
अणु
	अचिन्हित पूर्णांक count = 0;

	जबतक (n) अणु
		count += n & 1;
		n >>= 1;
	पूर्ण

	वापस count;
पूर्ण
