<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा MAX_PATH_LEN		128
#घोषणा MAX_खाताS		7

pid_t my_pid = 0;
__u32 cnt_stat = 0;
__u32 cnt_बंद = 0;
अक्षर paths_stat[MAX_खाताS][MAX_PATH_LEN] = अणुपूर्ण;
अक्षर paths_बंद[MAX_खाताS][MAX_PATH_LEN] = अणुपूर्ण;
पूर्णांक rets_stat[MAX_खाताS] = अणुपूर्ण;
पूर्णांक rets_बंद[MAX_खाताS] = अणुपूर्ण;

पूर्णांक called_stat = 0;
पूर्णांक called_बंद = 0;

SEC("fentry/security_inode_getattr")
पूर्णांक BPF_PROG(prog_stat, काष्ठा path *path, काष्ठा kstat *stat,
	     __u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	pid_t pid = bpf_get_current_pid_tgid() >> 32;
	__u32 cnt = cnt_stat;
	पूर्णांक ret;

	called_stat = 1;

	अगर (pid != my_pid)
		वापस 0;

	अगर (cnt >= MAX_खाताS)
		वापस 0;
	ret = bpf_d_path(path, paths_stat[cnt], MAX_PATH_LEN);

	rets_stat[cnt] = ret;
	cnt_stat++;
	वापस 0;
पूर्ण

SEC("fentry/filp_close")
पूर्णांक BPF_PROG(prog_बंद, काष्ठा file *file, व्योम *id)
अणु
	pid_t pid = bpf_get_current_pid_tgid() >> 32;
	__u32 cnt = cnt_बंद;
	पूर्णांक ret;

	called_बंद = 1;

	अगर (pid != my_pid)
		वापस 0;

	अगर (cnt >= MAX_खाताS)
		वापस 0;
	ret = bpf_d_path(&file->f_path,
			 paths_बंद[cnt], MAX_PATH_LEN);

	rets_बंद[cnt] = ret;
	cnt_बंद++;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
