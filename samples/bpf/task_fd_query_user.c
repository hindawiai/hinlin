<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <fcntl.h>
#समावेश <linux/bpf.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/resource.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/perf_event.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "bpf_util.h"
#समावेश "perf-sys.h"
#समावेश "trace_helpers.h"

अटल काष्ठा bpf_program *progs[2];
अटल काष्ठा bpf_link *links[2];

#घोषणा CHECK_PERROR_RET(condition) (अणु			\
	पूर्णांक __ret = !!(condition);			\
	अगर (__ret) अणु					\
		म_लिखो("FAIL: %s:\n", __func__);	\
		लिखो_त्रुटि("    ");			\
		वापस -1;				\
	पूर्ण						\
पूर्ण)

#घोषणा CHECK_AND_RET(condition) (अणु			\
	पूर्णांक __ret = !!(condition);			\
	अगर (__ret)					\
		वापस -1;				\
पूर्ण)

अटल __u64 ptr_to_u64(व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

#घोषणा PMU_TYPE_खाता "/sys/bus/event_source/devices/%s/type"
अटल पूर्णांक bpf_find_probe_type(स्थिर अक्षर *event_type)
अणु
	अक्षर buf[256];
	पूर्णांक fd, ret;

	ret = snम_लिखो(buf, माप(buf), PMU_TYPE_खाता, event_type);
	CHECK_PERROR_RET(ret < 0 || ret >= माप(buf));

	fd = खोलो(buf, O_RDONLY);
	CHECK_PERROR_RET(fd < 0);

	ret = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	CHECK_PERROR_RET(ret < 0 || ret >= माप(buf));

	त्रुटि_सं = 0;
	ret = (पूर्णांक)म_से_दीर्घ(buf, शून्य, 10);
	CHECK_PERROR_RET(त्रुटि_सं);
	वापस ret;
पूर्ण

#घोषणा PMU_RETPROBE_खाता "/sys/bus/event_source/devices/%s/format/retprobe"
अटल पूर्णांक bpf_get_retprobe_bit(स्थिर अक्षर *event_type)
अणु
	अक्षर buf[256];
	पूर्णांक fd, ret;

	ret = snम_लिखो(buf, माप(buf), PMU_RETPROBE_खाता, event_type);
	CHECK_PERROR_RET(ret < 0 || ret >= माप(buf));

	fd = खोलो(buf, O_RDONLY);
	CHECK_PERROR_RET(fd < 0);

	ret = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	CHECK_PERROR_RET(ret < 0 || ret >= माप(buf));
	CHECK_PERROR_RET(म_माप(buf) < म_माप("config:"));

	त्रुटि_सं = 0;
	ret = (पूर्णांक)म_से_दीर्घ(buf + म_माप("config:"), शून्य, 10);
	CHECK_PERROR_RET(त्रुटि_सं);
	वापस ret;
पूर्ण

अटल पूर्णांक test_debug_fs_kprobe(पूर्णांक link_idx, स्थिर अक्षर *fn_name,
				__u32 expected_fd_type)
अणु
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	पूर्णांक err, event_fd;
	अक्षर buf[256];

	len = माप(buf);
	event_fd = bpf_link__fd(links[link_idx]);
	err = bpf_task_fd_query(getpid(), event_fd, 0, buf, &len,
				&prog_id, &fd_type, &probe_offset,
				&probe_addr);
	अगर (err < 0) अणु
		म_लिखो("FAIL: %s, for event_fd idx %d, fn_name %s\n",
		       __func__, link_idx, fn_name);
		लिखो_त्रुटि("    :");
		वापस -1;
	पूर्ण
	अगर (म_भेद(buf, fn_name) != 0 ||
	    fd_type != expected_fd_type ||
	    probe_offset != 0x0 || probe_addr != 0x0) अणु
		म_लिखो("FAIL: bpf_trace_event_query(event_fd[%d]):\n",
		       link_idx);
		म_लिखो("buf: %s, fd_type: %u, probe_offset: 0x%llx,"
		       " probe_addr: 0x%llx\n",
		       buf, fd_type, probe_offset, probe_addr);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_nondebug_fs_kuprobe_common(स्थिर अक्षर *event_type,
	स्थिर अक्षर *name, __u64 offset, __u64 addr, bool is_वापस,
	अक्षर *buf, __u32 *buf_len, __u32 *prog_id, __u32 *fd_type,
	__u64 *probe_offset, __u64 *probe_addr)
अणु
	पूर्णांक is_वापस_bit = bpf_get_retprobe_bit(event_type);
	पूर्णांक type = bpf_find_probe_type(event_type);
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	काष्ठा bpf_link *link;
	पूर्णांक fd, err = -1;

	अगर (type < 0 || is_वापस_bit < 0) अणु
		म_लिखो("FAIL: %s incorrect type (%d) or is_return_bit (%d)\n",
			__func__, type, is_वापस_bit);
		वापस err;
	पूर्ण

	attr.sample_period = 1;
	attr.wakeup_events = 1;
	अगर (is_वापस)
		attr.config |= 1 << is_वापस_bit;

	अगर (name) अणु
		attr.config1 = ptr_to_u64((व्योम *)name);
		attr.config2 = offset;
	पूर्ण अन्यथा अणु
		attr.config1 = 0;
		attr.config2 = addr;
	पूर्ण
	attr.size = माप(attr);
	attr.type = type;

	fd = sys_perf_event_खोलो(&attr, -1, 0, -1, 0);
	link = bpf_program__attach_perf_event(progs[0], fd);
	अगर (libbpf_get_error(link)) अणु
		म_लिखो("ERROR: bpf_program__attach_perf_event failed\n");
		link = शून्य;
		बंद(fd);
		जाओ cleanup;
	पूर्ण

	CHECK_PERROR_RET(bpf_task_fd_query(getpid(), fd, 0, buf, buf_len,
			 prog_id, fd_type, probe_offset, probe_addr) < 0);
	err = 0;

cleanup:
	bpf_link__destroy(link);
	वापस err;
पूर्ण

अटल पूर्णांक test_nondebug_fs_probe(स्थिर अक्षर *event_type, स्थिर अक्षर *name,
				  __u64 offset, __u64 addr, bool is_वापस,
				  __u32 expected_fd_type,
				  __u32 expected_ret_fd_type,
				  अक्षर *buf, __u32 buf_len)
अणु
	__u64 probe_offset, probe_addr;
	__u32 prog_id, fd_type;
	पूर्णांक err;

	err = test_nondebug_fs_kuprobe_common(event_type, name,
					      offset, addr, is_वापस,
					      buf, &buf_len, &prog_id,
					      &fd_type, &probe_offset,
					      &probe_addr);
	अगर (err < 0) अणु
		म_लिखो("FAIL: %s, "
		       "for name %s, offset 0x%llx, addr 0x%llx, is_return %d\n",
		       __func__, name ? name : "", offset, addr, is_वापस);
		लिखो_त्रुटि("    :");
		वापस -1;
	पूर्ण
	अगर ((is_वापस && fd_type != expected_ret_fd_type) ||
	    (!is_वापस && fd_type != expected_fd_type)) अणु
		म_लिखो("FAIL: %s, incorrect fd_type %u\n",
		       __func__, fd_type);
		वापस -1;
	पूर्ण
	अगर (name) अणु
		अगर (म_भेद(name, buf) != 0) अणु
			म_लिखो("FAIL: %s, incorrect buf %s\n", __func__, buf);
			वापस -1;
		पूर्ण
		अगर (probe_offset != offset) अणु
			म_लिखो("FAIL: %s, incorrect probe_offset 0x%llx\n",
			       __func__, probe_offset);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (buf_len != 0) अणु
			म_लिखो("FAIL: %s, incorrect buf %p\n",
			       __func__, buf);
			वापस -1;
		पूर्ण

		अगर (probe_addr != addr) अणु
			म_लिखो("FAIL: %s, incorrect probe_addr 0x%llx\n",
			       __func__, probe_addr);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_debug_fs_uprobe(अक्षर *binary_path, दीर्घ offset, bool is_वापस)
अणु
	अक्षर buf[256], event_alias[माप("test_1234567890")];
	स्थिर अक्षर *event_type = "uprobe";
	काष्ठा perf_event_attr attr = अणुपूर्ण;
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	पूर्णांक err = -1, res, kfd, efd;
	काष्ठा bpf_link *link;
	sमाप_प्रकार bytes;

	snम_लिखो(buf, माप(buf), "/sys/kernel/debug/tracing/%s_events",
		 event_type);
	kfd = खोलो(buf, O_WRONLY | O_TRUNC, 0);
	CHECK_PERROR_RET(kfd < 0);

	res = snम_लिखो(event_alias, माप(event_alias), "test_%d", getpid());
	CHECK_PERROR_RET(res < 0 || res >= माप(event_alias));

	res = snम_लिखो(buf, माप(buf), "%c:%ss/%s %s:0x%lx",
		       is_वापस ? 'r' : 'p', event_type, event_alias,
		       binary_path, offset);
	CHECK_PERROR_RET(res < 0 || res >= माप(buf));
	CHECK_PERROR_RET(ग_लिखो(kfd, buf, म_माप(buf)) < 0);

	बंद(kfd);
	kfd = -1;

	snम_लिखो(buf, माप(buf), "/sys/kernel/debug/tracing/events/%ss/%s/id",
		 event_type, event_alias);
	efd = खोलो(buf, O_RDONLY, 0);
	CHECK_PERROR_RET(efd < 0);

	bytes = पढ़ो(efd, buf, माप(buf));
	CHECK_PERROR_RET(bytes <= 0 || bytes >= माप(buf));
	बंद(efd);
	buf[bytes] = '\0';

	attr.config = म_से_दीर्घ(buf, शून्य, 0);
	attr.type = PERF_TYPE_TRACEPOINT;
	attr.sample_period = 1;
	attr.wakeup_events = 1;

	kfd = sys_perf_event_खोलो(&attr, -1, 0, -1, PERF_FLAG_FD_CLOEXEC);
	link = bpf_program__attach_perf_event(progs[0], kfd);
	अगर (libbpf_get_error(link)) अणु
		म_लिखो("ERROR: bpf_program__attach_perf_event failed\n");
		link = शून्य;
		बंद(kfd);
		जाओ cleanup;
	पूर्ण

	len = माप(buf);
	err = bpf_task_fd_query(getpid(), kfd, 0, buf, &len,
				&prog_id, &fd_type, &probe_offset,
				&probe_addr);
	अगर (err < 0) अणु
		म_लिखो("FAIL: %s, binary_path %s\n", __func__, binary_path);
		लिखो_त्रुटि("    :");
		वापस -1;
	पूर्ण
	अगर ((is_वापस && fd_type != BPF_FD_TYPE_URETPROBE) ||
	    (!is_वापस && fd_type != BPF_FD_TYPE_UPROBE)) अणु
		म_लिखो("FAIL: %s, incorrect fd_type %u\n", __func__,
		       fd_type);
		वापस -1;
	पूर्ण
	अगर (म_भेद(binary_path, buf) != 0) अणु
		म_लिखो("FAIL: %s, incorrect buf %s\n", __func__, buf);
		वापस -1;
	पूर्ण
	अगर (probe_offset != offset) अणु
		म_लिखो("FAIL: %s, incorrect probe_offset 0x%llx\n", __func__,
		       probe_offset);
		वापस -1;
	पूर्ण
	err = 0;

cleanup:
	bpf_link__destroy(link);
	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर __executable_start;
	अक्षर filename[256], buf[256];
	__u64 uprobe_file_offset;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक i = 0, err = -1;

	अगर (load_kallsyms()) अणु
		म_लिखो("failed to process /proc/kallsyms\n");
		वापस err;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस err;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		progs[i] = prog;
		links[i] = bpf_program__attach(progs[i]);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[i] = शून्य;
			जाओ cleanup;
		पूर्ण
		i++;
	पूर्ण

	/* test two functions in the corresponding *_kern.c file */
	CHECK_AND_RET(test_debug_fs_kprobe(0, "blk_mq_start_request",
					   BPF_FD_TYPE_KPROBE));
	CHECK_AND_RET(test_debug_fs_kprobe(1, "blk_account_io_done",
					   BPF_FD_TYPE_KRETPROBE));

	/* test nondebug fs kprobe */
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x0, 0x0,
					     false, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, माप(buf)));
#अगर_घोषित __x86_64__
	/* set a kprobe on "bpf_check + 0x5", which is x64 specअगरic */
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x5, 0x0,
					     false, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, माप(buf)));
#पूर्ण_अगर
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", "bpf_check", 0x0, 0x0,
					     true, BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, माप(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", शून्य, 0x0,
					     ksym_get_addr("bpf_check"), false,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, माप(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", शून्य, 0x0,
					     ksym_get_addr("bpf_check"), false,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     शून्य, 0));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", शून्य, 0x0,
					     ksym_get_addr("bpf_check"), true,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     buf, माप(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("kprobe", शून्य, 0x0,
					     ksym_get_addr("bpf_check"), true,
					     BPF_FD_TYPE_KPROBE,
					     BPF_FD_TYPE_KRETPROBE,
					     0, 0));

	/* test nondebug fs uprobe */
	/* the calculation of uprobe file offset is based on gcc 7.3.1 on x64
	 * and the शेष linker script, which defines __executable_start as
	 * the start of the .text section. The calculation could be dअगरferent
	 * on dअगरferent प्रणालीs with dअगरferent compilers. The right way is
	 * to parse the ELF file. We took a लघुcut here.
	 */
	uprobe_file_offset = (__u64)मुख्य - (__u64)&__executable_start;
	CHECK_AND_RET(test_nondebug_fs_probe("uprobe", (अक्षर *)argv[0],
					     uprobe_file_offset, 0x0, false,
					     BPF_FD_TYPE_UPROBE,
					     BPF_FD_TYPE_URETPROBE,
					     buf, माप(buf)));
	CHECK_AND_RET(test_nondebug_fs_probe("uprobe", (अक्षर *)argv[0],
					     uprobe_file_offset, 0x0, true,
					     BPF_FD_TYPE_UPROBE,
					     BPF_FD_TYPE_URETPROBE,
					     buf, माप(buf)));

	/* test debug fs uprobe */
	CHECK_AND_RET(test_debug_fs_uprobe((अक्षर *)argv[0], uprobe_file_offset,
					   false));
	CHECK_AND_RET(test_debug_fs_uprobe((अक्षर *)argv[0], uprobe_file_offset,
					   true));
	err = 0;

cleanup:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);

	bpf_object__बंद(obj);
	वापस err;
पूर्ण
