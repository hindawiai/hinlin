<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Read/ग_लिखो thपढ़ो of a guest agent क्रम virtio-trace
 *
 * Copyright (C) 2012 Hitachi, Ltd.
 * Created by Yoshihiro Yunomae <yoshihiro.yunomae.ez@hitachi.com>
 *            Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश "trace-agent.h"

#घोषणा READ_WAIT_USEC	100000

व्योम *rw_thपढ़ो_info_new(व्योम)
अणु
	काष्ठा rw_thपढ़ो_info *rw_ti;

	rw_ti = zalloc(माप(काष्ठा rw_thपढ़ो_info));
	अगर (rw_ti == शून्य) अणु
		pr_err("rw_thread_info zalloc error\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	rw_ti->cpu_num = -1;
	rw_ti->in_fd = -1;
	rw_ti->out_fd = -1;
	rw_ti->पढ़ो_pipe = -1;
	rw_ti->ग_लिखो_pipe = -1;
	rw_ti->pipe_size = PIPE_INIT;

	वापस rw_ti;
पूर्ण

व्योम *rw_thपढ़ो_init(पूर्णांक cpu, स्थिर अक्षर *in_path, स्थिर अक्षर *out_path,
				bool मानक_निकास_flag, अचिन्हित दीर्घ pipe_size,
				काष्ठा rw_thपढ़ो_info *rw_ti)
अणु
	पूर्णांक data_pipe[2];

	rw_ti->cpu_num = cpu;

	/* set पढ़ो(input) fd */
	rw_ti->in_fd = खोलो(in_path, O_RDONLY);
	अगर (rw_ti->in_fd == -1) अणु
		pr_err("Could not open in_fd (CPU:%d)\n", cpu);
		जाओ error;
	पूर्ण

	/* set ग_लिखो(output) fd */
	अगर (!मानक_निकास_flag) अणु
		/* virtio-serial output mode */
		rw_ti->out_fd = खोलो(out_path, O_WRONLY);
		अगर (rw_ti->out_fd == -1) अणु
			pr_err("Could not open out_fd (CPU:%d)\n", cpu);
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा
		/* मानक_निकास mode */
		rw_ti->out_fd = STDOUT_खाताNO;

	अगर (pipe2(data_pipe, O_NONBLOCK) < 0) अणु
		pr_err("Could not create pipe in rw-thread(%d)\n", cpu);
		जाओ error;
	पूर्ण

	/*
	 * Size of pipe is 64kB in शेष based on fs/pipe.c.
	 * To पढ़ो/ग_लिखो trace data speedy, pipe size is changed.
	 */
	अगर (fcntl(*data_pipe, F_SETPIPE_SZ, pipe_size) < 0) अणु
		pr_err("Could not change pipe size in rw-thread(%d)\n", cpu);
		जाओ error;
	पूर्ण

	rw_ti->पढ़ो_pipe = data_pipe[1];
	rw_ti->ग_लिखो_pipe = data_pipe[0];
	rw_ti->pipe_size = pipe_size;

	वापस शून्य;

error:
	निकास(निकास_त्रुटि);
पूर्ण

/* Bind a thपढ़ो to a cpu */
अटल व्योम bind_cpu(पूर्णांक cpu_num)
अणु
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu_num, &mask);

	/* bind my thपढ़ो to cpu_num by assigning zero to the first argument */
	अगर (sched_setaffinity(0, माप(mask), &mask) == -1)
		pr_err("Could not set CPU#%d affinity\n", (पूर्णांक)cpu_num);
पूर्ण

अटल व्योम *rw_thपढ़ो_मुख्य(व्योम *thपढ़ो_info)
अणु
	sमाप_प्रकार rlen, wlen;
	sमाप_प्रकार ret;
	काष्ठा rw_thपढ़ो_info *ts = (काष्ठा rw_thपढ़ो_info *)thपढ़ो_info;

	bind_cpu(ts->cpu_num);

	जबतक (1) अणु
		/* Wait क्रम a पढ़ो order of trace data by Host OS */
		अगर (!global_run_operation) अणु
			pthपढ़ो_mutex_lock(&mutex_notअगरy);
			pthपढ़ो_cond_रुको(&cond_wakeup, &mutex_notअगरy);
			pthपढ़ो_mutex_unlock(&mutex_notअगरy);
		पूर्ण

		अगर (global_sig_receive)
			अवरोध;

		/*
		 * Each thपढ़ो पढ़ो trace_pipe_raw of each cpu bounding the
		 * thपढ़ो, so contention of multi-thपढ़ोs करोes not occur.
		 */
		rlen = splice(ts->in_fd, शून्य, ts->पढ़ो_pipe, शून्य,
				ts->pipe_size, SPLICE_F_MOVE | SPLICE_F_MORE);

		अगर (rlen < 0) अणु
			pr_err("Splice_read in rw-thread(%d)\n", ts->cpu_num);
			जाओ error;
		पूर्ण अन्यथा अगर (rlen == 0) अणु
			/*
			 * If trace data करो not exist or are unपढ़ोable not
			 * क्रम exceeding the page size, splice_पढ़ो वापसs
			 * शून्य. Then, this रुकोs क्रम being filled the data in a
			 * ring-buffer.
			 */
			usleep(READ_WAIT_USEC);
			pr_debug("Read retry(cpu:%d)\n", ts->cpu_num);
			जारी;
		पूर्ण

		wlen = 0;

		करो अणु
			ret = splice(ts->ग_लिखो_pipe, शून्य, ts->out_fd, शून्य,
					rlen - wlen,
					SPLICE_F_MOVE | SPLICE_F_MORE);

			अगर (ret < 0) अणु
				pr_err("Splice_write in rw-thread(%d)\n",
								ts->cpu_num);
				जाओ error;
			पूर्ण अन्यथा अगर (ret == 0)
				/*
				 * When host पढ़ोer is not in समय क्रम पढ़ोing
				 * trace data, guest will be stopped. This is
				 * because अक्षर dev in QEMU is not supported
				 * non-blocking mode. Then, ग_लिखोr might be
				 * sleep in that हाल.
				 * This sleep will be हटाओd by supporting
				 * non-blocking mode.
				 */
				sleep(1);
			wlen += ret;
		पूर्ण जबतक (wlen < rlen);
	पूर्ण

	वापस शून्य;

error:
	निकास(निकास_त्रुटि);
पूर्ण


pthपढ़ो_t rw_thपढ़ो_run(काष्ठा rw_thपढ़ो_info *rw_ti)
अणु
	पूर्णांक ret;
	pthपढ़ो_t rw_thपढ़ो_per_cpu;

	ret = pthपढ़ो_create(&rw_thपढ़ो_per_cpu, शून्य, rw_thपढ़ो_मुख्य, rw_ti);
	अगर (ret != 0) अणु
		pr_err("Could not create a rw thread(%d)\n", rw_ti->cpu_num);
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस rw_thपढ़ो_per_cpu;
पूर्ण
