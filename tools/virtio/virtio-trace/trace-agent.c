<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Guest agent क्रम virtio-trace
 *
 * Copyright (C) 2012 Hitachi, Ltd.
 * Created by Yoshihiro Yunomae <yoshihiro.yunomae.ez@hitachi.com>
 *            Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 */

#घोषणा _GNU_SOURCE
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश "trace-agent.h"

#घोषणा PAGE_SIZE		(sysconf(_SC_PAGE_SIZE))
#घोषणा PIPE_DEF_BUFS		16
#घोषणा PIPE_MIN_SIZE		(PAGE_SIZE*PIPE_DEF_BUFS)
#घोषणा PIPE_MAX_SIZE		(1024*1024)
#घोषणा READ_PATH_FMT	\
		"/sys/kernel/debug/tracing/per_cpu/cpu%d/trace_pipe_raw"
#घोषणा WRITE_PATH_FMT		"/dev/virtio-ports/trace-path-cpu%d"
#घोषणा CTL_PATH		"/dev/virtio-ports/agent-ctl-path"

pthपढ़ो_mutex_t mutex_notअगरy = PTHREAD_MUTEX_INITIALIZER;
pthपढ़ो_cond_t cond_wakeup = PTHREAD_COND_INITIALIZER;

अटल पूर्णांक get_total_cpus(व्योम)
अणु
	पूर्णांक nr_cpus = (पूर्णांक)sysconf(_SC_NPROCESSORS_CONF);

	अगर (nr_cpus <= 0) अणु
		pr_err("Could not read cpus\n");
		जाओ error;
	पूर्ण अन्यथा अगर (nr_cpus > MAX_CPUS) अणु
		pr_err("Exceed max cpus(%d)\n", (पूर्णांक)MAX_CPUS);
		जाओ error;
	पूर्ण

	वापस nr_cpus;

error:
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम *agent_info_new(व्योम)
अणु
	काष्ठा agent_info *s;
	पूर्णांक i;

	s = zalloc(माप(काष्ठा agent_info));
	अगर (s == शून्य) अणु
		pr_err("agent_info zalloc error\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	s->pipe_size = PIPE_INIT;
	s->use_मानक_निकास = false;
	s->cpus = get_total_cpus();
	s->ctl_fd = -1;

	/* पढ़ो/ग_लिखो thपढ़ोs init */
	क्रम (i = 0; i < s->cpus; i++)
		s->rw_ti[i] = rw_thपढ़ो_info_new();

	वापस s;
पूर्ण

अटल अचिन्हित दीर्घ parse_size(स्थिर अक्षर *arg)
अणु
	अचिन्हित दीर्घ value, round;
	अक्षर *ptr;

	value = म_से_अदीर्घ(arg, &ptr, 10);
	चयन (*ptr) अणु
	हाल 'K': case 'k':
		value <<= 10;
		अवरोध;
	हाल 'M': case 'm':
		value <<= 20;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (value > PIPE_MAX_SIZE) अणु
		pr_err("Pipe size must be less than 1MB\n");
		जाओ error;
	पूर्ण अन्यथा अगर (value < PIPE_MIN_SIZE) अणु
		pr_err("Pipe size must be over 64KB\n");
		जाओ error;
	पूर्ण

	/* Align buffer size with page unit */
	round = value & (PAGE_SIZE - 1);
	value = value - round;

	वापस value;
error:
	वापस 0;
पूर्ण

अटल व्योम usage(अक्षर स्थिर *prg)
अणु
	pr_err("usage: %s [-h] [-o] [-s <size of pipe>]\n", prg);
पूर्ण

अटल स्थिर अक्षर *make_path(पूर्णांक cpu_num, bool this_is_ग_लिखो_path)
अणु
	पूर्णांक ret;
	अक्षर *buf;

	buf = zalloc(PATH_MAX);
	अगर (buf == शून्य) अणु
		pr_err("Could not allocate buffer\n");
		जाओ error;
	पूर्ण

	अगर (this_is_ग_लिखो_path)
		/* ग_लिखो(output) path */
		ret = snम_लिखो(buf, PATH_MAX, WRITE_PATH_FMT, cpu_num);
	अन्यथा
		/* पढ़ो(input) path */
		ret = snम_लिखो(buf, PATH_MAX, READ_PATH_FMT, cpu_num);

	अगर (ret <= 0) अणु
		pr_err("Failed to generate %s path(CPU#%d):%d\n",
			this_is_ग_लिखो_path ? "read" : "write", cpu_num, ret);
		जाओ error;
	पूर्ण

	वापस buf;

error:
	मुक्त(buf);
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *make_input_path(पूर्णांक cpu_num)
अणु
	वापस make_path(cpu_num, false);
पूर्ण

अटल स्थिर अक्षर *make_output_path(पूर्णांक cpu_num)
अणु
	वापस make_path(cpu_num, true);
पूर्ण

अटल व्योम *agent_info_init(काष्ठा agent_info *s)
अणु
	पूर्णांक cpu;
	स्थिर अक्षर *in_path = शून्य;
	स्थिर अक्षर *out_path = शून्य;

	/* init पढ़ो/ग_लिखो thपढ़ोs */
	क्रम (cpu = 0; cpu < s->cpus; cpu++) अणु
		/* set पढ़ो(input) path per पढ़ो/ग_लिखो thपढ़ो */
		in_path = make_input_path(cpu);
		अगर (in_path == शून्य)
			जाओ error;

		/* set ग_लिखो(output) path per पढ़ो/ग_लिखो thपढ़ो*/
		अगर (!s->use_मानक_निकास) अणु
			out_path = make_output_path(cpu);
			अगर (out_path == शून्य)
				जाओ error;
		पूर्ण अन्यथा
			/* मानक_निकास mode */
			pr_debug("stdout mode\n");

		rw_thपढ़ो_init(cpu, in_path, out_path, s->use_मानक_निकास,
						s->pipe_size, s->rw_ti[cpu]);
	पूर्ण

	/* init controller of पढ़ो/ग_लिखो thपढ़ोs */
	s->ctl_fd = rw_ctl_init((स्थिर अक्षर *)CTL_PATH);

	वापस शून्य;

error:
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम *parse_args(पूर्णांक argc, अक्षर *argv[], काष्ठा agent_info *s)
अणु
	पूर्णांक cmd;
	अचिन्हित दीर्घ size;

	जबतक ((cmd = getopt(argc, argv, "hos:")) != -1) अणु
		चयन (cmd) अणु
		/* मानक_निकास mode */
		हाल 'o':
			s->use_मानक_निकास = true;
			अवरोध;
		/* size of pipe */
		हाल 's':
			size = parse_size(optarg);
			अगर (size == 0)
				जाओ error;
			s->pipe_size = size;
			अवरोध;
		हाल 'h':
		शेष:
			usage(argv[0]);
			जाओ error;
		पूर्ण
	पूर्ण

	agent_info_init(s);

	वापस शून्य;

error:
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम agent_मुख्य_loop(काष्ठा agent_info *s)
अणु
	पूर्णांक cpu;
	pthपढ़ो_t rw_thपढ़ो_per_cpu[MAX_CPUS];

	/* Start all पढ़ो/ग_लिखो thपढ़ोs */
	क्रम (cpu = 0; cpu < s->cpus; cpu++)
		rw_thपढ़ो_per_cpu[cpu] = rw_thपढ़ो_run(s->rw_ti[cpu]);

	rw_ctl_loop(s->ctl_fd);

	/* Finish all पढ़ो/ग_लिखो thपढ़ोs */
	क्रम (cpu = 0; cpu < s->cpus; cpu++) अणु
		पूर्णांक ret;

		ret = pthपढ़ो_join(rw_thपढ़ो_per_cpu[cpu], शून्य);
		अगर (ret != 0) अणु
			pr_err("pthread_join() error:%d (cpu %d)\n", ret, cpu);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम agent_info_मुक्त(काष्ठा agent_info *s)
अणु
	पूर्णांक i;

	बंद(s->ctl_fd);
	क्रम (i = 0; i < s->cpus; i++) अणु
		बंद(s->rw_ti[i]->in_fd);
		बंद(s->rw_ti[i]->out_fd);
		बंद(s->rw_ti[i]->पढ़ो_pipe);
		बंद(s->rw_ti[i]->ग_लिखो_pipe);
		मुक्त(s->rw_ti[i]);
	पूर्ण
	मुक्त(s);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा agent_info *s = शून्य;

	s = agent_info_new();
	parse_args(argc, argv, s);

	agent_मुख्य_loop(s);

	agent_info_मुक्त(s);

	वापस 0;
पूर्ण
