<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <vmlinux.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#समावेश "profiler.h"

#अगर_अघोषित शून्य
#घोषणा शून्य 0
#पूर्ण_अगर

#घोषणा O_WRONLY 00000001
#घोषणा O_RDWR 00000002
#घोषणा O_सूचीECTORY 00200000
#घोषणा __O_TMPखाता 020000000
#घोषणा O_TMPखाता (__O_TMPखाता | O_सूचीECTORY)
#घोषणा MAX_ERRNO 4095
#घोषणा S_IFMT 00170000
#घोषणा S_IFSOCK 0140000
#घोषणा S_IFLNK 0120000
#घोषणा S_IFREG 0100000
#घोषणा S_IFBLK 0060000
#घोषणा S_IFसूची 0040000
#घोषणा S_IFCHR 0020000
#घोषणा S_IFIFO 0010000
#घोषणा S_ISUID 0004000
#घोषणा S_ISGID 0002000
#घोषणा S_ISVTX 0001000
#घोषणा S_ISLNK(m) (((m)&S_IFMT) == S_IFLNK)
#घोषणा S_ISसूची(m) (((m)&S_IFMT) == S_IFसूची)
#घोषणा S_ISCHR(m) (((m)&S_IFMT) == S_IFCHR)
#घोषणा S_ISBLK(m) (((m)&S_IFMT) == S_IFBLK)
#घोषणा S_ISFIFO(m) (((m)&S_IFMT) == S_IFIFO)
#घोषणा S_ISSOCK(m) (((m)&S_IFMT) == S_IFSOCK)
#घोषणा IS_ERR_VALUE(x) (अचिन्हित दीर्घ)(व्योम*)(x) >= (अचिन्हित दीर्घ)-MAX_ERRNO

#घोषणा KILL_DATA_ARRAY_SIZE 8

काष्ठा var_समाप्त_data_arr_t अणु
	काष्ठा var_समाप्त_data_t array[KILL_DATA_ARRAY_SIZE];
पूर्ण;

जोड़ any_profiler_data_t अणु
	काष्ठा var_exec_data_t var_exec;
	काष्ठा var_समाप्त_data_t var_समाप्त;
	काष्ठा var_sysctl_data_t var_sysctl;
	काष्ठा var_filemod_data_t var_filemod;
	काष्ठा var_विभाजन_data_t var_विभाजन;
	काष्ठा var_समाप्त_data_arr_t var_समाप्त_data_arr;
पूर्ण;

अस्थिर काष्ठा profiler_config_काष्ठा bpf_config = अणुपूर्ण;

#घोषणा FETCH_CGROUPS_FROM_BPF (bpf_config.fetch_cgroups_from_bpf)
#घोषणा CGROUP_FS_INODE (bpf_config.cgroup_fs_inode)
#घोषणा CGROUP_LOGIN_SESSION_INODE \
	(bpf_config.cgroup_login_session_inode)
#घोषणा KILL_SIGNALS (bpf_config.समाप्त_संकेतs_mask)
#घोषणा STALE_INFO (bpf_config.stale_info_secs)
#घोषणा INODE_FILTER (bpf_config.inode_filter)
#घोषणा READ_ENVIRON_FROM_EXEC (bpf_config.पढ़ो_environ_from_exec)
#घोषणा ENABLE_CGROUP_V1_RESOLVER (bpf_config.enable_cgroup_v1_resolver)

काष्ठा kernfs_iattrs___52 अणु
	काष्ठा iattr ia_iattr;
पूर्ण;

काष्ठा kernfs_node___52 अणु
	जोड़ /* kernfs_node_id */ अणु
		काष्ठा अणु
			u32 ino;
			u32 generation;
		पूर्ण;
		u64 id;
	पूर्ण id;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, u32);
	__type(value, जोड़ any_profiler_data_t);
पूर्ण data_heap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण events SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, KILL_DATA_ARRAY_SIZE);
	__type(key, u32);
	__type(value, काष्ठा var_समाप्त_data_arr_t);
पूर्ण var_tpid_to_data SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, profiler_bpf_max_function_id);
	__type(key, u32);
	__type(value, काष्ठा bpf_func_stats_data);
पूर्ण bpf_func_stats SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, bool);
	__uपूर्णांक(max_entries, 16);
पूर्ण allowed_devices SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u64);
	__type(value, bool);
	__uपूर्णांक(max_entries, 1024);
पूर्ण allowed_file_inodes SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u64);
	__type(value, bool);
	__uपूर्णांक(max_entries, 1024);
पूर्ण allowed_directory_inodes SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, bool);
	__uपूर्णांक(max_entries, 16);
पूर्ण disallowed_exec_inodes SEC(".maps");

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप(arr[0]))
#पूर्ण_अगर

अटल INLINE bool IS_ERR(स्थिर व्योम* ptr)
अणु
	वापस IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण

अटल INLINE u32 get_userspace_pid()
अणु
	वापस bpf_get_current_pid_tgid() >> 32;
पूर्ण

अटल INLINE bool is_init_process(u32 tgid)
अणु
	वापस tgid == 1 || tgid == 0;
पूर्ण

अटल INLINE अचिन्हित दीर्घ
probe_पढ़ो_lim(व्योम* dst, व्योम* src, अचिन्हित दीर्घ len, अचिन्हित दीर्घ max)
अणु
	len = len < max ? len : max;
	अगर (len > 1) अणु
		अगर (bpf_probe_पढ़ो(dst, len, src))
			वापस 0;
	पूर्ण अन्यथा अगर (len == 1) अणु
		अगर (bpf_probe_पढ़ो(dst, 1, src))
			वापस 0;
	पूर्ण
	वापस len;
पूर्ण

अटल INLINE पूर्णांक get_var_spid_index(काष्ठा var_समाप्त_data_arr_t* arr_काष्ठा,
				     पूर्णांक spid)
अणु
#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < ARRAY_SIZE(arr_काष्ठा->array); i++)
		अगर (arr_काष्ठा->array[i].meta.pid == spid)
			वापस i;
	वापस -1;
पूर्ण

अटल INLINE व्योम populate_ancestors(काष्ठा task_काष्ठा* task,
				      काष्ठा ancestors_data_t* ancestors_data)
अणु
	काष्ठा task_काष्ठा* parent = task;
	u32 num_ancestors, ppid;

	ancestors_data->num_ancestors = 0;
#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (num_ancestors = 0; num_ancestors < MAX_ANCESTORS; num_ancestors++) अणु
		parent = BPF_CORE_READ(parent, real_parent);
		अगर (parent == शून्य)
			अवरोध;
		ppid = BPF_CORE_READ(parent, tgid);
		अगर (is_init_process(ppid))
			अवरोध;
		ancestors_data->ancestor_pids[num_ancestors] = ppid;
		ancestors_data->ancestor_exec_ids[num_ancestors] =
			BPF_CORE_READ(parent, self_exec_id);
		ancestors_data->ancestor_start_बार[num_ancestors] =
			BPF_CORE_READ(parent, start_समय);
		ancestors_data->num_ancestors = num_ancestors;
	पूर्ण
पूर्ण

अटल INLINE व्योम* पढ़ो_full_cgroup_path(काष्ठा kernfs_node* cgroup_node,
					  काष्ठा kernfs_node* cgroup_root_node,
					  व्योम* payload,
					  पूर्णांक* root_pos)
अणु
	व्योम* payload_start = payload;
	माप_प्रकार filepart_length;

#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < MAX_CGROUPS_PATH_DEPTH; i++) अणु
		filepart_length =
			bpf_probe_पढ़ो_str(payload, MAX_PATH, BPF_CORE_READ(cgroup_node, name));
		अगर (!cgroup_node)
			वापस payload;
		अगर (cgroup_node == cgroup_root_node)
			*root_pos = payload - payload_start;
		अगर (filepart_length <= MAX_PATH) अणु
			barrier_var(filepart_length);
			payload += filepart_length;
		पूर्ण
		cgroup_node = BPF_CORE_READ(cgroup_node, parent);
	पूर्ण
	वापस payload;
पूर्ण

अटल ino_t get_inode_from_kernfs(काष्ठा kernfs_node* node)
अणु
	काष्ठा kernfs_node___52* node52 = (व्योम*)node;

	अगर (bpf_core_field_exists(node52->id.ino)) अणु
		barrier_var(node52);
		वापस BPF_CORE_READ(node52, id.ino);
	पूर्ण अन्यथा अणु
		barrier_var(node);
		वापस (u64)BPF_CORE_READ(node, id);
	पूर्ण
पूर्ण

बाह्य bool CONFIG_CGROUP_PIDS __kconfig __weak;
क्रमागत cgroup_subsys_id___local अणु
	pids_cgrp_id___local = 123, /* value करोesn't matter */
पूर्ण;

अटल INLINE व्योम* populate_cgroup_info(काष्ठा cgroup_data_t* cgroup_data,
					 काष्ठा task_काष्ठा* task,
					 व्योम* payload)
अणु
	काष्ठा kernfs_node* root_kernfs =
		BPF_CORE_READ(task, nsproxy, cgroup_ns, root_cset, dfl_cgrp, kn);
	काष्ठा kernfs_node* proc_kernfs = BPF_CORE_READ(task, cgroups, dfl_cgrp, kn);

#अगर __has_builtin(__builtin_preserve_क्रमागत_value)
	अगर (ENABLE_CGROUP_V1_RESOLVER && CONFIG_CGROUP_PIDS) अणु
		पूर्णांक cgrp_id = bpf_core_क्रमागत_value(क्रमागत cgroup_subsys_id___local,
						  pids_cgrp_id___local);
#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
		क्रम (पूर्णांक i = 0; i < CGROUP_SUBSYS_COUNT; i++) अणु
			काष्ठा cgroup_subsys_state* subsys =
				BPF_CORE_READ(task, cgroups, subsys[i]);
			अगर (subsys != शून्य) अणु
				पूर्णांक subsys_id = BPF_CORE_READ(subsys, ss, id);
				अगर (subsys_id == cgrp_id) अणु
					proc_kernfs = BPF_CORE_READ(subsys, cgroup, kn);
					root_kernfs = BPF_CORE_READ(subsys, ss, root, kf_root, kn);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	cgroup_data->cgroup_root_inode = get_inode_from_kernfs(root_kernfs);
	cgroup_data->cgroup_proc_inode = get_inode_from_kernfs(proc_kernfs);

	अगर (bpf_core_field_exists(root_kernfs->iattr->ia_mसमय)) अणु
		cgroup_data->cgroup_root_mसमय =
			BPF_CORE_READ(root_kernfs, iattr, ia_mसमय.tv_nsec);
		cgroup_data->cgroup_proc_mसमय =
			BPF_CORE_READ(proc_kernfs, iattr, ia_mसमय.tv_nsec);
	पूर्ण अन्यथा अणु
		काष्ठा kernfs_iattrs___52* root_iattr =
			(काष्ठा kernfs_iattrs___52*)BPF_CORE_READ(root_kernfs, iattr);
		cgroup_data->cgroup_root_mसमय =
			BPF_CORE_READ(root_iattr, ia_iattr.ia_mसमय.tv_nsec);

		काष्ठा kernfs_iattrs___52* proc_iattr =
			(काष्ठा kernfs_iattrs___52*)BPF_CORE_READ(proc_kernfs, iattr);
		cgroup_data->cgroup_proc_mसमय =
			BPF_CORE_READ(proc_iattr, ia_iattr.ia_mसमय.tv_nsec);
	पूर्ण

	cgroup_data->cgroup_root_length = 0;
	cgroup_data->cgroup_proc_length = 0;
	cgroup_data->cgroup_full_length = 0;

	माप_प्रकार cgroup_root_length =
		bpf_probe_पढ़ो_str(payload, MAX_PATH, BPF_CORE_READ(root_kernfs, name));
	barrier_var(cgroup_root_length);
	अगर (cgroup_root_length <= MAX_PATH) अणु
		barrier_var(cgroup_root_length);
		cgroup_data->cgroup_root_length = cgroup_root_length;
		payload += cgroup_root_length;
	पूर्ण

	माप_प्रकार cgroup_proc_length =
		bpf_probe_पढ़ो_str(payload, MAX_PATH, BPF_CORE_READ(proc_kernfs, name));
	barrier_var(cgroup_proc_length);
	अगर (cgroup_proc_length <= MAX_PATH) अणु
		barrier_var(cgroup_proc_length);
		cgroup_data->cgroup_proc_length = cgroup_proc_length;
		payload += cgroup_proc_length;
	पूर्ण

	अगर (FETCH_CGROUPS_FROM_BPF) अणु
		cgroup_data->cgroup_full_path_root_pos = -1;
		व्योम* payload_end_pos = पढ़ो_full_cgroup_path(proc_kernfs, root_kernfs, payload,
							      &cgroup_data->cgroup_full_path_root_pos);
		cgroup_data->cgroup_full_length = payload_end_pos - payload;
		payload = payload_end_pos;
	पूर्ण

	वापस (व्योम*)payload;
पूर्ण

अटल INLINE व्योम* populate_var_metadata(काष्ठा var_metadata_t* metadata,
					  काष्ठा task_काष्ठा* task,
					  u32 pid, व्योम* payload)
अणु
	u64 uid_gid = bpf_get_current_uid_gid();

	metadata->uid = (u32)uid_gid;
	metadata->gid = uid_gid >> 32;
	metadata->pid = pid;
	metadata->exec_id = BPF_CORE_READ(task, self_exec_id);
	metadata->start_समय = BPF_CORE_READ(task, start_समय);
	metadata->comm_length = 0;

	माप_प्रकार comm_length = bpf_core_पढ़ो_str(payload, TASK_COMM_LEN, &task->comm);
	barrier_var(comm_length);
	अगर (comm_length <= TASK_COMM_LEN) अणु
		barrier_var(comm_length);
		metadata->comm_length = comm_length;
		payload += comm_length;
	पूर्ण

	वापस (व्योम*)payload;
पूर्ण

अटल INLINE काष्ठा var_समाप्त_data_t*
get_var_समाप्त_data(काष्ठा pt_regs* ctx, पूर्णांक spid, पूर्णांक tpid, पूर्णांक sig)
अणु
	पूर्णांक zero = 0;
	काष्ठा var_समाप्त_data_t* समाप्त_data = bpf_map_lookup_elem(&data_heap, &zero);

	अगर (समाप्त_data == शून्य)
		वापस शून्य;
	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();

	व्योम* payload = populate_var_metadata(&समाप्त_data->meta, task, spid, समाप्त_data->payload);
	payload = populate_cgroup_info(&समाप्त_data->cgroup_data, task, payload);
	माप_प्रकार payload_length = payload - (व्योम*)समाप्त_data->payload;
	समाप्त_data->payload_length = payload_length;
	populate_ancestors(task, &समाप्त_data->ancestors_info);
	समाप्त_data->meta.type = KILL_EVENT;
	समाप्त_data->समाप्त_target_pid = tpid;
	समाप्त_data->समाप्त_sig = sig;
	समाप्त_data->समाप्त_count = 1;
	समाप्त_data->last_समाप्त_समय = bpf_kसमय_get_ns();
	वापस समाप्त_data;
पूर्ण

अटल INLINE पूर्णांक trace_var_sys_समाप्त(व्योम* ctx, पूर्णांक tpid, पूर्णांक sig)
अणु
	अगर ((KILL_SIGNALS & (1ULL << sig)) == 0)
		वापस 0;

	u32 spid = get_userspace_pid();
	काष्ठा var_समाप्त_data_arr_t* arr_काष्ठा = bpf_map_lookup_elem(&var_tpid_to_data, &tpid);

	अगर (arr_काष्ठा == शून्य) अणु
		काष्ठा var_समाप्त_data_t* समाप्त_data = get_var_समाप्त_data(ctx, spid, tpid, sig);
		पूर्णांक zero = 0;

		अगर (समाप्त_data == शून्य)
			वापस 0;
		arr_काष्ठा = bpf_map_lookup_elem(&data_heap, &zero);
		अगर (arr_काष्ठा == शून्य)
			वापस 0;
		bpf_probe_पढ़ो(&arr_काष्ठा->array[0], माप(arr_काष्ठा->array[0]), समाप्त_data);
	पूर्ण अन्यथा अणु
		पूर्णांक index = get_var_spid_index(arr_काष्ठा, spid);

		अगर (index == -1) अणु
			काष्ठा var_समाप्त_data_t* समाप्त_data =
				get_var_समाप्त_data(ctx, spid, tpid, sig);
			अगर (समाप्त_data == शून्य)
				वापस 0;
#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
			क्रम (पूर्णांक i = 0; i < ARRAY_SIZE(arr_काष्ठा->array); i++)
				अगर (arr_काष्ठा->array[i].meta.pid == 0) अणु
					bpf_probe_पढ़ो(&arr_काष्ठा->array[i],
						       माप(arr_काष्ठा->array[i]), समाप्त_data);
					bpf_map_update_elem(&var_tpid_to_data, &tpid,
							    arr_काष्ठा, 0);

					वापस 0;
				पूर्ण
			वापस 0;
		पूर्ण

		काष्ठा var_समाप्त_data_t* समाप्त_data = &arr_काष्ठा->array[index];

		u64 delta_sec =
			(bpf_kसमय_get_ns() - समाप्त_data->last_समाप्त_समय) / 1000000000;

		अगर (delta_sec < STALE_INFO) अणु
			समाप्त_data->समाप्त_count++;
			समाप्त_data->last_समाप्त_समय = bpf_kसमय_get_ns();
			bpf_probe_पढ़ो(&arr_काष्ठा->array[index],
				       माप(arr_काष्ठा->array[index]),
				       समाप्त_data);
		पूर्ण अन्यथा अणु
			काष्ठा var_समाप्त_data_t* समाप्त_data =
				get_var_समाप्त_data(ctx, spid, tpid, sig);
			अगर (समाप्त_data == शून्य)
				वापस 0;
			bpf_probe_पढ़ो(&arr_काष्ठा->array[index],
				       माप(arr_काष्ठा->array[index]),
				       समाप्त_data);
		पूर्ण
	पूर्ण
	bpf_map_update_elem(&var_tpid_to_data, &tpid, arr_काष्ठा, 0);
	वापस 0;
पूर्ण

अटल INLINE व्योम bpf_stats_enter(काष्ठा bpf_func_stats_ctx* bpf_stat_ctx,
				   क्रमागत bpf_function_id func_id)
अणु
	पूर्णांक func_id_key = func_id;

	bpf_stat_ctx->start_समय_ns = bpf_kसमय_get_ns();
	bpf_stat_ctx->bpf_func_stats_data_val =
		bpf_map_lookup_elem(&bpf_func_stats, &func_id_key);
	अगर (bpf_stat_ctx->bpf_func_stats_data_val)
		bpf_stat_ctx->bpf_func_stats_data_val->num_executions++;
पूर्ण

अटल INLINE व्योम bpf_stats_निकास(काष्ठा bpf_func_stats_ctx* bpf_stat_ctx)
अणु
	अगर (bpf_stat_ctx->bpf_func_stats_data_val)
		bpf_stat_ctx->bpf_func_stats_data_val->समय_elapsed_ns +=
			bpf_kसमय_get_ns() - bpf_stat_ctx->start_समय_ns;
पूर्ण

अटल INLINE व्योम
bpf_stats_pre_submit_var_perf_event(काष्ठा bpf_func_stats_ctx* bpf_stat_ctx,
				    काष्ठा var_metadata_t* meta)
अणु
	अगर (bpf_stat_ctx->bpf_func_stats_data_val) अणु
		bpf_stat_ctx->bpf_func_stats_data_val->num_perf_events++;
		meta->bpf_stats_num_perf_events =
			bpf_stat_ctx->bpf_func_stats_data_val->num_perf_events;
	पूर्ण
	meta->bpf_stats_start_kसमय_ns = bpf_stat_ctx->start_समय_ns;
	meta->cpu_id = bpf_get_smp_processor_id();
पूर्ण

अटल INLINE माप_प्रकार
पढ़ो_असलolute_file_path_from_dentry(काष्ठा dentry* filp_dentry, व्योम* payload)
अणु
	माप_प्रकार length = 0;
	माप_प्रकार filepart_length;
	काष्ठा dentry* parent_dentry;

#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < MAX_PATH_DEPTH; i++) अणु
		filepart_length = bpf_probe_पढ़ो_str(payload, MAX_PATH,
						     BPF_CORE_READ(filp_dentry, d_name.name));
		barrier_var(filepart_length);
		अगर (filepart_length > MAX_PATH)
			अवरोध;
		barrier_var(filepart_length);
		payload += filepart_length;
		length += filepart_length;

		parent_dentry = BPF_CORE_READ(filp_dentry, d_parent);
		अगर (filp_dentry == parent_dentry)
			अवरोध;
		filp_dentry = parent_dentry;
	पूर्ण

	वापस length;
पूर्ण

अटल INLINE bool
is_ancestor_in_allowed_inodes(काष्ठा dentry* filp_dentry)
अणु
	काष्ठा dentry* parent_dentry;
#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < MAX_PATH_DEPTH; i++) अणु
		u64 dir_ino = BPF_CORE_READ(filp_dentry, d_inode, i_ino);
		bool* allowed_dir = bpf_map_lookup_elem(&allowed_directory_inodes, &dir_ino);

		अगर (allowed_dir != शून्य)
			वापस true;
		parent_dentry = BPF_CORE_READ(filp_dentry, d_parent);
		अगर (filp_dentry == parent_dentry)
			अवरोध;
		filp_dentry = parent_dentry;
	पूर्ण
	वापस false;
पूर्ण

अटल INLINE bool is_dentry_allowed_क्रम_filemod(काष्ठा dentry* file_dentry,
						 u32* device_id,
						 u64* file_ino)
अणु
	u32 dev_id = BPF_CORE_READ(file_dentry, d_sb, s_dev);
	*device_id = dev_id;
	bool* allowed_device = bpf_map_lookup_elem(&allowed_devices, &dev_id);

	अगर (allowed_device == शून्य)
		वापस false;

	u64 ino = BPF_CORE_READ(file_dentry, d_inode, i_ino);
	*file_ino = ino;
	bool* allowed_file = bpf_map_lookup_elem(&allowed_file_inodes, &ino);

	अगर (allowed_file == शून्य)
		अगर (!is_ancestor_in_allowed_inodes(BPF_CORE_READ(file_dentry, d_parent)))
			वापस false;
	वापस true;
पूर्ण

SEC("kprobe/proc_sys_write")
sमाप_प्रकार BPF_KPROBE(kprobe__proc_sys_ग_लिखो,
		   काष्ठा file* filp, स्थिर अक्षर* buf,
		   माप_प्रकार count, loff_t* ppos)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_proc_sys_ग_लिखो);

	u32 pid = get_userspace_pid();
	पूर्णांक zero = 0;
	काष्ठा var_sysctl_data_t* sysctl_data =
		bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!sysctl_data)
		जाओ out;

	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();
	sysctl_data->meta.type = SYSCTL_EVENT;
	व्योम* payload = populate_var_metadata(&sysctl_data->meta, task, pid, sysctl_data->payload);
	payload = populate_cgroup_info(&sysctl_data->cgroup_data, task, payload);

	populate_ancestors(task, &sysctl_data->ancestors_info);

	sysctl_data->sysctl_val_length = 0;
	sysctl_data->sysctl_path_length = 0;

	माप_प्रकार sysctl_val_length = bpf_probe_पढ़ो_str(payload, CTL_MAXNAME, buf);
	barrier_var(sysctl_val_length);
	अगर (sysctl_val_length <= CTL_MAXNAME) अणु
		barrier_var(sysctl_val_length);
		sysctl_data->sysctl_val_length = sysctl_val_length;
		payload += sysctl_val_length;
	पूर्ण

	माप_प्रकार sysctl_path_length = bpf_probe_पढ़ो_str(payload, MAX_PATH,
						       BPF_CORE_READ(filp, f_path.dentry, d_name.name));
	barrier_var(sysctl_path_length);
	अगर (sysctl_path_length <= MAX_PATH) अणु
		barrier_var(sysctl_path_length);
		sysctl_data->sysctl_path_length = sysctl_path_length;
		payload += sysctl_path_length;
	पूर्ण

	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &sysctl_data->meta);
	अचिन्हित दीर्घ data_len = payload - (व्योम*)sysctl_data;
	data_len = data_len > माप(काष्ठा var_sysctl_data_t)
		? माप(काष्ठा var_sysctl_data_t)
		: data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, sysctl_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("tracepoint/syscalls/sys_enter_kill")
पूर्णांक tracepoपूर्णांक__syscalls__sys_enter_समाप्त(काष्ठा trace_event_raw_sys_enter* ctx)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;

	bpf_stats_enter(&stats_ctx, profiler_bpf_sys_enter_समाप्त);
	पूर्णांक pid = ctx->args[0];
	पूर्णांक sig = ctx->args[1];
	पूर्णांक ret = trace_var_sys_समाप्त(ctx, pid, sig);
	bpf_stats_निकास(&stats_ctx);
	वापस ret;
पूर्ण;

SEC("raw_tracepoint/sched_process_exit")
पूर्णांक raw_tracepoपूर्णांक__sched_process_निकास(व्योम* ctx)
अणु
	पूर्णांक zero = 0;
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_sched_process_निकास);

	u32 tpid = get_userspace_pid();

	काष्ठा var_समाप्त_data_arr_t* arr_काष्ठा = bpf_map_lookup_elem(&var_tpid_to_data, &tpid);
	काष्ठा var_समाप्त_data_t* समाप्त_data = bpf_map_lookup_elem(&data_heap, &zero);

	अगर (arr_काष्ठा == शून्य || समाप्त_data == शून्य)
		जाओ out;

	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();
	काष्ठा kernfs_node* proc_kernfs = BPF_CORE_READ(task, cgroups, dfl_cgrp, kn);

#अगर_घोषित UNROLL
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < ARRAY_SIZE(arr_काष्ठा->array); i++) अणु
		काष्ठा var_समाप्त_data_t* past_समाप्त_data = &arr_काष्ठा->array[i];

		अगर (past_समाप्त_data != शून्य && past_समाप्त_data->समाप्त_target_pid == tpid) अणु
			bpf_probe_पढ़ो(समाप्त_data, माप(*past_समाप्त_data), past_समाप्त_data);
			व्योम* payload = समाप्त_data->payload;
			माप_प्रकार offset = समाप्त_data->payload_length;
			अगर (offset >= MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN)
				वापस 0;
			payload += offset;

			समाप्त_data->समाप्त_target_name_length = 0;
			समाप्त_data->समाप्त_target_cgroup_proc_length = 0;

			माप_प्रकार comm_length = bpf_core_पढ़ो_str(payload, TASK_COMM_LEN, &task->comm);
			barrier_var(comm_length);
			अगर (comm_length <= TASK_COMM_LEN) अणु
				barrier_var(comm_length);
				समाप्त_data->समाप्त_target_name_length = comm_length;
				payload += comm_length;
			पूर्ण

			माप_प्रकार cgroup_proc_length = bpf_probe_पढ़ो_str(payload, KILL_TARGET_LEN,
								       BPF_CORE_READ(proc_kernfs, name));
			barrier_var(cgroup_proc_length);
			अगर (cgroup_proc_length <= KILL_TARGET_LEN) अणु
				barrier_var(cgroup_proc_length);
				समाप्त_data->समाप्त_target_cgroup_proc_length = cgroup_proc_length;
				payload += cgroup_proc_length;
			पूर्ण

			bpf_stats_pre_submit_var_perf_event(&stats_ctx, &समाप्त_data->meta);
			अचिन्हित दीर्घ data_len = (व्योम*)payload - (व्योम*)समाप्त_data;
			data_len = data_len > माप(काष्ठा var_समाप्त_data_t)
				? माप(काष्ठा var_समाप्त_data_t)
				: data_len;
			bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, समाप्त_data, data_len);
		पूर्ण
	पूर्ण
	bpf_map_delete_elem(&var_tpid_to_data, &tpid);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("raw_tracepoint/sched_process_exec")
पूर्णांक raw_tracepoपूर्णांक__sched_process_exec(काष्ठा bpf_raw_tracepoपूर्णांक_args* ctx)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_sched_process_exec);

	काष्ठा linux_binprm* bprm = (काष्ठा linux_binprm*)ctx->args[2];
	u64 inode = BPF_CORE_READ(bprm, file, f_inode, i_ino);

	bool* should_filter_binprm = bpf_map_lookup_elem(&disallowed_exec_inodes, &inode);
	अगर (should_filter_binprm != शून्य)
		जाओ out;

	पूर्णांक zero = 0;
	काष्ठा var_exec_data_t* proc_exec_data = bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!proc_exec_data)
		जाओ out;

	अगर (INODE_FILTER && inode != INODE_FILTER)
		वापस 0;

	u32 pid = get_userspace_pid();
	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();

	proc_exec_data->meta.type = EXEC_EVENT;
	proc_exec_data->bin_path_length = 0;
	proc_exec_data->cmdline_length = 0;
	proc_exec_data->environment_length = 0;
	व्योम* payload = populate_var_metadata(&proc_exec_data->meta, task, pid,
					      proc_exec_data->payload);
	payload = populate_cgroup_info(&proc_exec_data->cgroup_data, task, payload);

	काष्ठा task_काष्ठा* parent_task = BPF_CORE_READ(task, real_parent);
	proc_exec_data->parent_pid = BPF_CORE_READ(parent_task, tgid);
	proc_exec_data->parent_uid = BPF_CORE_READ(parent_task, real_cred, uid.val);
	proc_exec_data->parent_exec_id = BPF_CORE_READ(parent_task, self_exec_id);
	proc_exec_data->parent_start_समय = BPF_CORE_READ(parent_task, start_समय);

	स्थिर अक्षर* filename = BPF_CORE_READ(bprm, filename);
	माप_प्रकार bin_path_length = bpf_probe_पढ़ो_str(payload, MAX_खाताNAME_LEN, filename);
	barrier_var(bin_path_length);
	अगर (bin_path_length <= MAX_खाताNAME_LEN) अणु
		barrier_var(bin_path_length);
		proc_exec_data->bin_path_length = bin_path_length;
		payload += bin_path_length;
	पूर्ण

	व्योम* arg_start = (व्योम*)BPF_CORE_READ(task, mm, arg_start);
	व्योम* arg_end = (व्योम*)BPF_CORE_READ(task, mm, arg_end);
	अचिन्हित पूर्णांक cmdline_length = probe_पढ़ो_lim(payload, arg_start,
						     arg_end - arg_start, MAX_ARGS_LEN);

	अगर (cmdline_length <= MAX_ARGS_LEN) अणु
		barrier_var(cmdline_length);
		proc_exec_data->cmdline_length = cmdline_length;
		payload += cmdline_length;
	पूर्ण

	अगर (READ_ENVIRON_FROM_EXEC) अणु
		व्योम* env_start = (व्योम*)BPF_CORE_READ(task, mm, env_start);
		व्योम* env_end = (व्योम*)BPF_CORE_READ(task, mm, env_end);
		अचिन्हित दीर्घ env_len = probe_पढ़ो_lim(payload, env_start,
						       env_end - env_start, MAX_ENVIRON_LEN);
		अगर (cmdline_length <= MAX_ENVIRON_LEN) अणु
			proc_exec_data->environment_length = env_len;
			payload += env_len;
		पूर्ण
	पूर्ण

	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &proc_exec_data->meta);
	अचिन्हित दीर्घ data_len = payload - (व्योम*)proc_exec_data;
	data_len = data_len > माप(काष्ठा var_exec_data_t)
		? माप(काष्ठा var_exec_data_t)
		: data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, proc_exec_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("kretprobe/do_filp_open")
पूर्णांक kprobe_ret__करो_filp_खोलो(काष्ठा pt_regs* ctx)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_करो_filp_खोलो_ret);

	काष्ठा file* filp = (काष्ठा file*)PT_REGS_RC_CORE(ctx);

	अगर (filp == शून्य || IS_ERR(filp))
		जाओ out;
	अचिन्हित पूर्णांक flags = BPF_CORE_READ(filp, f_flags);
	अगर ((flags & (O_RDWR | O_WRONLY)) == 0)
		जाओ out;
	अगर ((flags & O_TMPखाता) > 0)
		जाओ out;
	काष्ठा inode* file_inode = BPF_CORE_READ(filp, f_inode);
	umode_t mode = BPF_CORE_READ(file_inode, i_mode);
	अगर (S_ISसूची(mode) || S_ISCHR(mode) || S_ISBLK(mode) || S_ISFIFO(mode) ||
	    S_ISSOCK(mode))
		जाओ out;

	काष्ठा dentry* filp_dentry = BPF_CORE_READ(filp, f_path.dentry);
	u32 device_id = 0;
	u64 file_ino = 0;
	अगर (!is_dentry_allowed_क्रम_filemod(filp_dentry, &device_id, &file_ino))
		जाओ out;

	पूर्णांक zero = 0;
	काष्ठा var_filemod_data_t* filemod_data = bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!filemod_data)
		जाओ out;

	u32 pid = get_userspace_pid();
	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();

	filemod_data->meta.type = खाताMOD_EVENT;
	filemod_data->भ_शेष_type = FMOD_OPEN;
	filemod_data->dst_flags = flags;
	filemod_data->src_inode = 0;
	filemod_data->dst_inode = file_ino;
	filemod_data->src_device_id = 0;
	filemod_data->dst_device_id = device_id;
	filemod_data->src_filepath_length = 0;
	filemod_data->dst_filepath_length = 0;

	व्योम* payload = populate_var_metadata(&filemod_data->meta, task, pid,
					      filemod_data->payload);
	payload = populate_cgroup_info(&filemod_data->cgroup_data, task, payload);

	माप_प्रकार len = पढ़ो_असलolute_file_path_from_dentry(filp_dentry, payload);
	barrier_var(len);
	अगर (len <= MAX_खाताPATH_LENGTH) अणु
		barrier_var(len);
		payload += len;
		filemod_data->dst_filepath_length = len;
	पूर्ण
	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &filemod_data->meta);
	अचिन्हित दीर्घ data_len = payload - (व्योम*)filemod_data;
	data_len = data_len > माप(*filemod_data) ? माप(*filemod_data) : data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, filemod_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("kprobe/vfs_link")
पूर्णांक BPF_KPROBE(kprobe__vfs_link,
	       काष्ठा dentry* old_dentry, काष्ठा inode* dir,
	       काष्ठा dentry* new_dentry, काष्ठा inode** delegated_inode)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_vfs_link);

	u32 src_device_id = 0;
	u64 src_file_ino = 0;
	u32 dst_device_id = 0;
	u64 dst_file_ino = 0;
	अगर (!is_dentry_allowed_क्रम_filemod(old_dentry, &src_device_id, &src_file_ino) &&
	    !is_dentry_allowed_क्रम_filemod(new_dentry, &dst_device_id, &dst_file_ino))
		जाओ out;

	पूर्णांक zero = 0;
	काष्ठा var_filemod_data_t* filemod_data = bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!filemod_data)
		जाओ out;

	u32 pid = get_userspace_pid();
	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();

	filemod_data->meta.type = खाताMOD_EVENT;
	filemod_data->भ_शेष_type = FMOD_LINK;
	filemod_data->dst_flags = 0;
	filemod_data->src_inode = src_file_ino;
	filemod_data->dst_inode = dst_file_ino;
	filemod_data->src_device_id = src_device_id;
	filemod_data->dst_device_id = dst_device_id;
	filemod_data->src_filepath_length = 0;
	filemod_data->dst_filepath_length = 0;

	व्योम* payload = populate_var_metadata(&filemod_data->meta, task, pid,
					      filemod_data->payload);
	payload = populate_cgroup_info(&filemod_data->cgroup_data, task, payload);

	माप_प्रकार len = पढ़ो_असलolute_file_path_from_dentry(old_dentry, payload);
	barrier_var(len);
	अगर (len <= MAX_खाताPATH_LENGTH) अणु
		barrier_var(len);
		payload += len;
		filemod_data->src_filepath_length = len;
	पूर्ण

	len = पढ़ो_असलolute_file_path_from_dentry(new_dentry, payload);
	barrier_var(len);
	अगर (len <= MAX_खाताPATH_LENGTH) अणु
		barrier_var(len);
		payload += len;
		filemod_data->dst_filepath_length = len;
	पूर्ण

	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &filemod_data->meta);
	अचिन्हित दीर्घ data_len = payload - (व्योम*)filemod_data;
	data_len = data_len > माप(*filemod_data) ? माप(*filemod_data) : data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, filemod_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("kprobe/vfs_symlink")
पूर्णांक BPF_KPROBE(kprobe__vfs_symlink, काष्ठा inode* dir, काष्ठा dentry* dentry,
	       स्थिर अक्षर* oldname)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_vfs_symlink);

	u32 dst_device_id = 0;
	u64 dst_file_ino = 0;
	अगर (!is_dentry_allowed_क्रम_filemod(dentry, &dst_device_id, &dst_file_ino))
		जाओ out;

	पूर्णांक zero = 0;
	काष्ठा var_filemod_data_t* filemod_data = bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!filemod_data)
		जाओ out;

	u32 pid = get_userspace_pid();
	काष्ठा task_काष्ठा* task = (काष्ठा task_काष्ठा*)bpf_get_current_task();

	filemod_data->meta.type = खाताMOD_EVENT;
	filemod_data->भ_शेष_type = FMOD_SYMLINK;
	filemod_data->dst_flags = 0;
	filemod_data->src_inode = 0;
	filemod_data->dst_inode = dst_file_ino;
	filemod_data->src_device_id = 0;
	filemod_data->dst_device_id = dst_device_id;
	filemod_data->src_filepath_length = 0;
	filemod_data->dst_filepath_length = 0;

	व्योम* payload = populate_var_metadata(&filemod_data->meta, task, pid,
					      filemod_data->payload);
	payload = populate_cgroup_info(&filemod_data->cgroup_data, task, payload);

	माप_प्रकार len = bpf_probe_पढ़ो_str(payload, MAX_खाताPATH_LENGTH, oldname);
	barrier_var(len);
	अगर (len <= MAX_खाताPATH_LENGTH) अणु
		barrier_var(len);
		payload += len;
		filemod_data->src_filepath_length = len;
	पूर्ण
	len = पढ़ो_असलolute_file_path_from_dentry(dentry, payload);
	barrier_var(len);
	अगर (len <= MAX_खाताPATH_LENGTH) अणु
		barrier_var(len);
		payload += len;
		filemod_data->dst_filepath_length = len;
	पूर्ण
	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &filemod_data->meta);
	अचिन्हित दीर्घ data_len = payload - (व्योम*)filemod_data;
	data_len = data_len > माप(*filemod_data) ? माप(*filemod_data) : data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, filemod_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण

SEC("raw_tracepoint/sched_process_fork")
पूर्णांक raw_tracepoपूर्णांक__sched_process_विभाजन(काष्ठा bpf_raw_tracepoपूर्णांक_args* ctx)
अणु
	काष्ठा bpf_func_stats_ctx stats_ctx;
	bpf_stats_enter(&stats_ctx, profiler_bpf_sched_process_विभाजन);

	पूर्णांक zero = 0;
	काष्ठा var_विभाजन_data_t* विभाजन_data = bpf_map_lookup_elem(&data_heap, &zero);
	अगर (!विभाजन_data)
		जाओ out;

	काष्ठा task_काष्ठा* parent = (काष्ठा task_काष्ठा*)ctx->args[0];
	काष्ठा task_काष्ठा* child = (काष्ठा task_काष्ठा*)ctx->args[1];
	विभाजन_data->meta.type = FORK_EVENT;

	व्योम* payload = populate_var_metadata(&विभाजन_data->meta, child,
					      BPF_CORE_READ(child, pid), विभाजन_data->payload);
	विभाजन_data->parent_pid = BPF_CORE_READ(parent, pid);
	विभाजन_data->parent_exec_id = BPF_CORE_READ(parent, self_exec_id);
	विभाजन_data->parent_start_समय = BPF_CORE_READ(parent, start_समय);
	bpf_stats_pre_submit_var_perf_event(&stats_ctx, &विभाजन_data->meta);

	अचिन्हित दीर्घ data_len = payload - (व्योम*)विभाजन_data;
	data_len = data_len > माप(*विभाजन_data) ? माप(*विभाजन_data) : data_len;
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, विभाजन_data, data_len);
out:
	bpf_stats_निकास(&stats_ctx);
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
