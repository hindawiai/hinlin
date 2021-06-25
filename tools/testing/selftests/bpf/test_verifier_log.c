<शैली गुरु>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/समय.स>

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/unistd.h>

#समावेश <bpf/bpf.h>

#समावेश "bpf_rlimit.h"

#घोषणा LOG_SIZE (1 << 20)

#घोषणा err(str...)	म_लिखो("ERROR: " str)

अटल स्थिर काष्ठा bpf_insn code_sample[] = अणु
	/* We need a few inकाष्ठाions to pass the min log length */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
		     BPF_FUNC_map_lookup_elem),
	BPF_EXIT_INSN(),
पूर्ण;

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

अटल पूर्णांक load(अक्षर *log, माप_प्रकार log_len, पूर्णांक log_level)
अणु
	जोड़ bpf_attr attr;

	bzero(&attr, माप(attr));
	attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	attr.insn_cnt = (__u32)(माप(code_sample) / माप(काष्ठा bpf_insn));
	attr.insns = ptr_to_u64(code_sample);
	attr.license = ptr_to_u64("GPL");
	attr.log_buf = ptr_to_u64(log);
	attr.log_size = log_len;
	attr.log_level = log_level;

	वापस syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
पूर्ण

अटल व्योम check_ret(पूर्णांक ret, पूर्णांक exp_त्रुटि_सं)
अणु
	अगर (ret > 0) अणु
		बंद(ret);
		err("broken sample loaded successfully!?\n");
		निकास(1);
	पूर्ण

	अगर (!ret || त्रुटि_सं != exp_त्रुटि_सं) अणु
		err("Program load returned: ret:%d/errno:%d, expected ret:%d/errno:%d\n",
		    ret, त्रुटि_सं, -1, exp_त्रुटि_सं);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम check_ones(स्थिर अक्षर *buf, माप_प्रकार len, स्थिर अक्षर *msg)
अणु
	जबतक (len--)
		अगर (buf[len] != 1) अणु
			err("%s", msg);
			निकास(1);
		पूर्ण
पूर्ण

अटल व्योम test_log_good(अक्षर *log, माप_प्रकार buf_len, माप_प्रकार log_len,
			  माप_प्रकार exp_len, पूर्णांक exp_त्रुटि_सं, स्थिर अक्षर *full_log)
अणु
	माप_प्रकार len;
	पूर्णांक ret;

	स_रखो(log, 1, buf_len);

	ret = load(log, log_len, 1);
	check_ret(ret, exp_त्रुटि_सं);

	len = strnlen(log, buf_len);
	अगर (len == buf_len) अणु
		err("verifier did not NULL terminate the log\n");
		निकास(1);
	पूर्ण
	अगर (exp_len && len != exp_len) अणु
		err("incorrect log length expected:%zd have:%zd\n",
		    exp_len, len);
		निकास(1);
	पूर्ण

	अगर (म_अक्षर(log, 1)) अणु
		err("verifier leaked a byte through\n");
		निकास(1);
	पूर्ण

	check_ones(log + len + 1, buf_len - len - 1,
		   "verifier wrote bytes past NULL termination\n");

	अगर (स_भेद(full_log, log, LOG_SIZE)) अणु
		err("log did not match expected output\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम test_log_bad(अक्षर *log, माप_प्रकार log_len, पूर्णांक log_level)
अणु
	पूर्णांक ret;

	ret = load(log, log_len, log_level);
	check_ret(ret, EINVAL);
	अगर (log)
		check_ones(log, LOG_SIZE,
			   "verifier touched log with bad parameters\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर full_log[LOG_SIZE];
	अक्षर log[LOG_SIZE];
	माप_प्रकार want_len;
	पूर्णांक i;

	स_रखो(log, 1, LOG_SIZE);

	/* Test incorrect attr */
	म_लिखो("Test log_level 0...\n");
	test_log_bad(log, LOG_SIZE, 0);

	म_लिखो("Test log_size < 128...\n");
	test_log_bad(log, 15, 1);

	म_लिखो("Test log_buff = NULL...\n");
	test_log_bad(शून्य, LOG_SIZE, 1);

	/* Test with log big enough */
	म_लिखो("Test oversized buffer...\n");
	test_log_good(full_log, LOG_SIZE, LOG_SIZE, 0, EACCES, full_log);

	want_len = म_माप(full_log);

	म_लिखो("Test exact buffer...\n");
	test_log_good(log, LOG_SIZE, want_len + 2, want_len, EACCES, full_log);

	म_लिखो("Test undersized buffers...\n");
	क्रम (i = 0; i < 64; i++) अणु
		full_log[want_len - i + 1] = 1;
		full_log[want_len - i] = 0;

		test_log_good(log, LOG_SIZE, want_len + 1 - i, want_len - i,
			      ENOSPC, full_log);
	पूर्ण

	म_लिखो("test_verifier_log: OK\n");
	वापस 0;
पूर्ण
