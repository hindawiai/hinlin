<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#आशय once

#घोषणा TASK_COMM_LEN 16
#घोषणा MAX_ANCESTORS 4
#घोषणा MAX_PATH 256
#घोषणा KILL_TARGET_LEN 64
#घोषणा CTL_MAXNAME 10
#घोषणा MAX_ARGS_LEN 4096
#घोषणा MAX_खाताNAME_LEN 512
#घोषणा MAX_ENVIRON_LEN 8192
#घोषणा MAX_PATH_DEPTH 32
#घोषणा MAX_खाताPATH_LENGTH (MAX_PATH_DEPTH * MAX_PATH)
#घोषणा MAX_CGROUPS_PATH_DEPTH 8

#घोषणा MAX_METADATA_PAYLOAD_LEN TASK_COMM_LEN

#घोषणा MAX_CGROUP_PAYLOAD_LEN \
	(MAX_PATH * 2 + (MAX_PATH * MAX_CGROUPS_PATH_DEPTH))

#घोषणा MAX_CAP_PAYLOAD_LEN (MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN)

#घोषणा MAX_SYSCTL_PAYLOAD_LEN \
	(MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN + CTL_MAXNAME + MAX_PATH)

#घोषणा MAX_KILL_PAYLOAD_LEN \
	(MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN + TASK_COMM_LEN + \
	 KILL_TARGET_LEN)

#घोषणा MAX_EXEC_PAYLOAD_LEN \
	(MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN + MAX_खाताNAME_LEN + \
	 MAX_ARGS_LEN + MAX_ENVIRON_LEN)

#घोषणा MAX_खाताMOD_PAYLOAD_LEN \
	(MAX_METADATA_PAYLOAD_LEN + MAX_CGROUP_PAYLOAD_LEN + MAX_खाताPATH_LENGTH + \
	 MAX_खाताPATH_LENGTH)

क्रमागत data_type अणु
	INVALID_EVENT,
	EXEC_EVENT,
	FORK_EVENT,
	KILL_EVENT,
	SYSCTL_EVENT,
	खाताMOD_EVENT,
	MAX_DATA_TYPE_EVENT
पूर्ण;

क्रमागत filemod_type अणु
	FMOD_OPEN,
	FMOD_LINK,
	FMOD_SYMLINK,
पूर्ण;

काष्ठा ancestors_data_t अणु
	pid_t ancestor_pids[MAX_ANCESTORS];
	uपूर्णांक32_t ancestor_exec_ids[MAX_ANCESTORS];
	uपूर्णांक64_t ancestor_start_बार[MAX_ANCESTORS];
	uपूर्णांक32_t num_ancestors;
पूर्ण;

काष्ठा var_metadata_t अणु
	क्रमागत data_type type;
	pid_t pid;
	uपूर्णांक32_t exec_id;
	uid_t uid;
	gid_t gid;
	uपूर्णांक64_t start_समय;
	uपूर्णांक32_t cpu_id;
	uपूर्णांक64_t bpf_stats_num_perf_events;
	uपूर्णांक64_t bpf_stats_start_kसमय_ns;
	uपूर्णांक8_t comm_length;
पूर्ण;

काष्ठा cgroup_data_t अणु
	ino_t cgroup_root_inode;
	ino_t cgroup_proc_inode;
	uपूर्णांक64_t cgroup_root_mसमय;
	uपूर्णांक64_t cgroup_proc_mसमय;
	uपूर्णांक16_t cgroup_root_length;
	uपूर्णांक16_t cgroup_proc_length;
	uपूर्णांक16_t cgroup_full_length;
	पूर्णांक cgroup_full_path_root_pos;
पूर्ण;

काष्ठा var_sysctl_data_t अणु
	काष्ठा var_metadata_t meta;
	काष्ठा cgroup_data_t cgroup_data;
	काष्ठा ancestors_data_t ancestors_info;
	uपूर्णांक8_t sysctl_val_length;
	uपूर्णांक16_t sysctl_path_length;
	अक्षर payload[MAX_SYSCTL_PAYLOAD_LEN];
पूर्ण;

काष्ठा var_समाप्त_data_t अणु
	काष्ठा var_metadata_t meta;
	काष्ठा cgroup_data_t cgroup_data;
	काष्ठा ancestors_data_t ancestors_info;
	pid_t समाप्त_target_pid;
	पूर्णांक समाप्त_sig;
	uपूर्णांक32_t समाप्त_count;
	uपूर्णांक64_t last_समाप्त_समय;
	uपूर्णांक8_t समाप्त_target_name_length;
	uपूर्णांक8_t समाप्त_target_cgroup_proc_length;
	अक्षर payload[MAX_KILL_PAYLOAD_LEN];
	माप_प्रकार payload_length;
पूर्ण;

काष्ठा var_exec_data_t अणु
	काष्ठा var_metadata_t meta;
	काष्ठा cgroup_data_t cgroup_data;
	pid_t parent_pid;
	uपूर्णांक32_t parent_exec_id;
	uid_t parent_uid;
	uपूर्णांक64_t parent_start_समय;
	uपूर्णांक16_t bin_path_length;
	uपूर्णांक16_t cmdline_length;
	uपूर्णांक16_t environment_length;
	अक्षर payload[MAX_EXEC_PAYLOAD_LEN];
पूर्ण;

काष्ठा var_विभाजन_data_t अणु
	काष्ठा var_metadata_t meta;
	pid_t parent_pid;
	uपूर्णांक32_t parent_exec_id;
	uपूर्णांक64_t parent_start_समय;
	अक्षर payload[MAX_METADATA_PAYLOAD_LEN];
पूर्ण;

काष्ठा var_filemod_data_t अणु
	काष्ठा var_metadata_t meta;
	काष्ठा cgroup_data_t cgroup_data;
	क्रमागत filemod_type भ_शेष_type;
	अचिन्हित पूर्णांक dst_flags;
	uपूर्णांक32_t src_device_id;
	uपूर्णांक32_t dst_device_id;
	ino_t src_inode;
	ino_t dst_inode;
	uपूर्णांक16_t src_filepath_length;
	uपूर्णांक16_t dst_filepath_length;
	अक्षर payload[MAX_खाताMOD_PAYLOAD_LEN];
पूर्ण;

काष्ठा profiler_config_काष्ठा अणु
	bool fetch_cgroups_from_bpf;
	ino_t cgroup_fs_inode;
	ino_t cgroup_login_session_inode;
	uपूर्णांक64_t समाप्त_संकेतs_mask;
	ino_t inode_filter;
	uपूर्णांक32_t stale_info_secs;
	bool use_variable_buffers;
	bool पढ़ो_environ_from_exec;
	bool enable_cgroup_v1_resolver;
पूर्ण;

काष्ठा bpf_func_stats_data अणु
	uपूर्णांक64_t समय_elapsed_ns;
	uपूर्णांक64_t num_executions;
	uपूर्णांक64_t num_perf_events;
पूर्ण;

काष्ठा bpf_func_stats_ctx अणु
	uपूर्णांक64_t start_समय_ns;
	काष्ठा bpf_func_stats_data* bpf_func_stats_data_val;
पूर्ण;

क्रमागत bpf_function_id अणु
	profiler_bpf_proc_sys_ग_लिखो,
	profiler_bpf_sched_process_exec,
	profiler_bpf_sched_process_निकास,
	profiler_bpf_sys_enter_समाप्त,
	profiler_bpf_करो_filp_खोलो_ret,
	profiler_bpf_sched_process_विभाजन,
	profiler_bpf_vfs_link,
	profiler_bpf_vfs_symlink,
	profiler_bpf_max_function_id
पूर्ण;
