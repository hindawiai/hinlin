<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple benchmark program that uses the various features of io_uring
 * to provide fast अक्रमom access to a device/file. It has various
 * options that are control how we use io_uring, see the OPTIONS section
 * below. This uses the raw io_uring पूर्णांकerface.
 *
 * Copyright (C) 2018-2019 Jens Axboe
 */
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <मानकघोष.स>
#समावेश <संकेत.स>
#समावेश <पूर्णांकtypes.h>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश <sys/resource.h>
#समावेश <sys/mman.h>
#समावेश <sys/uपन.स>
#समावेश <linux/fs.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>

#समावेश "liburing.h"
#समावेश "barrier.h"

#घोषणा min(a, b)		((a < b) ? (a) : (b))

काष्ठा io_sq_ring अणु
	अचिन्हित *head;
	अचिन्हित *tail;
	अचिन्हित *ring_mask;
	अचिन्हित *ring_entries;
	अचिन्हित *flags;
	अचिन्हित *array;
पूर्ण;

काष्ठा io_cq_ring अणु
	अचिन्हित *head;
	अचिन्हित *tail;
	अचिन्हित *ring_mask;
	अचिन्हित *ring_entries;
	काष्ठा io_uring_cqe *cqes;
पूर्ण;

#घोषणा DEPTH			128

#घोषणा BATCH_SUBMIT		32
#घोषणा BATCH_COMPLETE		32

#घोषणा BS			4096

#घोषणा MAX_FDS			16

अटल अचिन्हित sq_ring_mask, cq_ring_mask;

काष्ठा file अणु
	अचिन्हित दीर्घ max_blocks;
	अचिन्हित pending_ios;
	पूर्णांक real_fd;
	पूर्णांक fixed_fd;
पूर्ण;

काष्ठा submitter अणु
	pthपढ़ो_t thपढ़ो;
	पूर्णांक ring_fd;
	काष्ठा dअक्रम48_data अक्रम;
	काष्ठा io_sq_ring sq_ring;
	काष्ठा io_uring_sqe *sqes;
	काष्ठा iovec iovecs[DEPTH];
	काष्ठा io_cq_ring cq_ring;
	पूर्णांक inflight;
	अचिन्हित दीर्घ reaps;
	अचिन्हित दीर्घ करोne;
	अचिन्हित दीर्घ calls;
	अस्थिर पूर्णांक finish;

	__s32 *fds;

	काष्ठा file files[MAX_FDS];
	अचिन्हित nr_files;
	अचिन्हित cur_file;
पूर्ण;

अटल काष्ठा submitter submitters[1];
अटल अस्थिर पूर्णांक finish;

/*
 * OPTIONS: Set these to test the various features of io_uring.
 */
अटल पूर्णांक polled = 1;		/* use IO polling */
अटल पूर्णांक fixedbufs = 1;	/* use fixed user buffers */
अटल पूर्णांक रेजिस्टर_files = 1;	/* use fixed files */
अटल पूर्णांक buffered = 0;	/* use buffered IO, not O_सूचीECT */
अटल पूर्णांक sq_thपढ़ो_poll = 0;	/* use kernel submission/poller thपढ़ो */
अटल पूर्णांक sq_thपढ़ो_cpu = -1;	/* pin above thपढ़ो to this CPU */
अटल पूर्णांक करो_nop = 0;		/* no-op SQ ring commands */

अटल पूर्णांक io_uring_रेजिस्टर_buffers(काष्ठा submitter *s)
अणु
	अगर (करो_nop)
		वापस 0;

	वापस io_uring_रेजिस्टर(s->ring_fd, IORING_REGISTER_BUFFERS, s->iovecs,
					DEPTH);
पूर्ण

अटल पूर्णांक io_uring_रेजिस्टर_files(काष्ठा submitter *s)
अणु
	अचिन्हित i;

	अगर (करो_nop)
		वापस 0;

	s->fds = सुस्मृति(s->nr_files, माप(__s32));
	क्रम (i = 0; i < s->nr_files; i++) अणु
		s->fds[i] = s->files[i].real_fd;
		s->files[i].fixed_fd = i;
	पूर्ण

	वापस io_uring_रेजिस्टर(s->ring_fd, IORING_REGISTER_खाताS, s->fds,
					s->nr_files);
पूर्ण

अटल पूर्णांक lk_gettid(व्योम)
अणु
	वापस syscall(__NR_gettid);
पूर्ण

अटल अचिन्हित file_depth(काष्ठा submitter *s)
अणु
	वापस (DEPTH + s->nr_files - 1) / s->nr_files;
पूर्ण

अटल व्योम init_io(काष्ठा submitter *s, अचिन्हित index)
अणु
	काष्ठा io_uring_sqe *sqe = &s->sqes[index];
	अचिन्हित दीर्घ offset;
	काष्ठा file *f;
	दीर्घ r;

	अगर (करो_nop) अणु
		sqe->opcode = IORING_OP_NOP;
		वापस;
	पूर्ण

	अगर (s->nr_files == 1) अणु
		f = &s->files[0];
	पूर्ण अन्यथा अणु
		f = &s->files[s->cur_file];
		अगर (f->pending_ios >= file_depth(s)) अणु
			s->cur_file++;
			अगर (s->cur_file == s->nr_files)
				s->cur_file = 0;
			f = &s->files[s->cur_file];
		पूर्ण
	पूर्ण
	f->pending_ios++;

	lअक्रम48_r(&s->अक्रम, &r);
	offset = (r % (f->max_blocks - 1)) * BS;

	अगर (रेजिस्टर_files) अणु
		sqe->flags = IOSQE_FIXED_खाता;
		sqe->fd = f->fixed_fd;
	पूर्ण अन्यथा अणु
		sqe->flags = 0;
		sqe->fd = f->real_fd;
	पूर्ण
	अगर (fixedbufs) अणु
		sqe->opcode = IORING_OP_READ_FIXED;
		sqe->addr = (अचिन्हित दीर्घ) s->iovecs[index].iov_base;
		sqe->len = BS;
		sqe->buf_index = index;
	पूर्ण अन्यथा अणु
		sqe->opcode = IORING_OP_READV;
		sqe->addr = (अचिन्हित दीर्घ) &s->iovecs[index];
		sqe->len = 1;
		sqe->buf_index = 0;
	पूर्ण
	sqe->ioprio = 0;
	sqe->off = offset;
	sqe->user_data = (अचिन्हित दीर्घ) f;
पूर्ण

अटल पूर्णांक prep_more_ios(काष्ठा submitter *s, अचिन्हित max_ios)
अणु
	काष्ठा io_sq_ring *ring = &s->sq_ring;
	अचिन्हित index, tail, next_tail, prepped = 0;

	next_tail = tail = *ring->tail;
	करो अणु
		next_tail++;
		पढ़ो_barrier();
		अगर (next_tail == *ring->head)
			अवरोध;

		index = tail & sq_ring_mask;
		init_io(s, index);
		ring->array[index] = index;
		prepped++;
		tail = next_tail;
	पूर्ण जबतक (prepped < max_ios);

	अगर (*ring->tail != tail) अणु
		/* order tail store with ग_लिखोs to sqes above */
		ग_लिखो_barrier();
		*ring->tail = tail;
		ग_लिखो_barrier();
	पूर्ण
	वापस prepped;
पूर्ण

अटल पूर्णांक get_file_size(काष्ठा file *f)
अणु
	काष्ठा stat st;

	अगर (ख_स्थिति(f->real_fd, &st) < 0)
		वापस -1;
	अगर (S_ISBLK(st.st_mode)) अणु
		अचिन्हित दीर्घ दीर्घ bytes;

		अगर (ioctl(f->real_fd, BLKGETSIZE64, &bytes) != 0)
			वापस -1;

		f->max_blocks = bytes / BS;
		वापस 0;
	पूर्ण अन्यथा अगर (S_ISREG(st.st_mode)) अणु
		f->max_blocks = st.st_size / BS;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक reap_events(काष्ठा submitter *s)
अणु
	काष्ठा io_cq_ring *ring = &s->cq_ring;
	काष्ठा io_uring_cqe *cqe;
	अचिन्हित head, reaped = 0;

	head = *ring->head;
	करो अणु
		काष्ठा file *f;

		पढ़ो_barrier();
		अगर (head == *ring->tail)
			अवरोध;
		cqe = &ring->cqes[head & cq_ring_mask];
		अगर (!करो_nop) अणु
			f = (काष्ठा file *) (uपूर्णांकptr_t) cqe->user_data;
			f->pending_ios--;
			अगर (cqe->res != BS) अणु
				म_लिखो("io: unexpected ret=%d\n", cqe->res);
				अगर (polled && cqe->res == -EOPNOTSUPP)
					म_लिखो("Your filesystem doesn't support poll\n");
				वापस -1;
			पूर्ण
		पूर्ण
		reaped++;
		head++;
	पूर्ण जबतक (1);

	s->inflight -= reaped;
	*ring->head = head;
	ग_लिखो_barrier();
	वापस reaped;
पूर्ण

अटल व्योम *submitter_fn(व्योम *data)
अणु
	काष्ठा submitter *s = data;
	काष्ठा io_sq_ring *ring = &s->sq_ring;
	पूर्णांक ret, prepped;

	म_लिखो("submitter=%d\n", lk_gettid());

	बेक्रम48_r(pthपढ़ो_self(), &s->अक्रम);

	prepped = 0;
	करो अणु
		पूर्णांक to_रुको, to_submit, this_reap, to_prep;

		अगर (!prepped && s->inflight < DEPTH) अणु
			to_prep = min(DEPTH - s->inflight, BATCH_SUBMIT);
			prepped = prep_more_ios(s, to_prep);
		पूर्ण
		s->inflight += prepped;
submit_more:
		to_submit = prepped;
submit:
		अगर (to_submit && (s->inflight + to_submit <= DEPTH))
			to_रुको = 0;
		अन्यथा
			to_रुको = min(s->inflight + to_submit, BATCH_COMPLETE);

		/*
		 * Only need to call io_uring_enter अगर we're not using SQ thपढ़ो
		 * poll, or अगर IORING_SQ_NEED_WAKEUP is set.
		 */
		अगर (!sq_thपढ़ो_poll || (*ring->flags & IORING_SQ_NEED_WAKEUP)) अणु
			अचिन्हित flags = 0;

			अगर (to_रुको)
				flags = IORING_ENTER_GETEVENTS;
			अगर ((*ring->flags & IORING_SQ_NEED_WAKEUP))
				flags |= IORING_ENTER_SQ_WAKEUP;
			ret = io_uring_enter(s->ring_fd, to_submit, to_रुको,
						flags, शून्य);
			s->calls++;
		पूर्ण

		/*
		 * For non SQ thपढ़ो poll, we alपढ़ोy got the events we needed
		 * through the io_uring_enter() above. For SQ thपढ़ो poll, we
		 * need to loop here until we find enough events.
		 */
		this_reap = 0;
		करो अणु
			पूर्णांक r;
			r = reap_events(s);
			अगर (r == -1) अणु
				s->finish = 1;
				अवरोध;
			पूर्ण अन्यथा अगर (r > 0)
				this_reap += r;
		पूर्ण जबतक (sq_thपढ़ो_poll && this_reap < to_रुको);
		s->reaps += this_reap;

		अगर (ret >= 0) अणु
			अगर (!ret) अणु
				to_submit = 0;
				अगर (s->inflight)
					जाओ submit;
				जारी;
			पूर्ण अन्यथा अगर (ret < to_submit) अणु
				पूर्णांक dअगरf = to_submit - ret;

				s->करोne += ret;
				prepped -= dअगरf;
				जाओ submit_more;
			पूर्ण
			s->करोne += ret;
			prepped = 0;
			जारी;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			अगर (त्रुटि_सं == EAGAIN) अणु
				अगर (s->finish)
					अवरोध;
				अगर (this_reap)
					जाओ submit;
				to_submit = 0;
				जाओ submit;
			पूर्ण
			म_लिखो("io_submit: %s\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!s->finish);

	finish = 1;
	वापस शून्य;
पूर्ण

अटल व्योम sig_पूर्णांक(पूर्णांक sig)
अणु
	म_लिखो("Exiting on signal %d\n", sig);
	submitters[0].finish = 1;
	finish = 1;
पूर्ण

अटल व्योम arm_sig_पूर्णांक(व्योम)
अणु
	काष्ठा sigaction act;

	स_रखो(&act, 0, माप(act));
	act.sa_handler = sig_पूर्णांक;
	act.sa_flags = SA_RESTART;
	sigaction(संक_विघ्न, &act, शून्य);
पूर्ण

अटल पूर्णांक setup_ring(काष्ठा submitter *s)
अणु
	काष्ठा io_sq_ring *sring = &s->sq_ring;
	काष्ठा io_cq_ring *cring = &s->cq_ring;
	काष्ठा io_uring_params p;
	पूर्णांक ret, fd;
	व्योम *ptr;

	स_रखो(&p, 0, माप(p));

	अगर (polled && !करो_nop)
		p.flags |= IORING_SETUP_IOPOLL;
	अगर (sq_thपढ़ो_poll) अणु
		p.flags |= IORING_SETUP_SQPOLL;
		अगर (sq_thपढ़ो_cpu != -1) अणु
			p.flags |= IORING_SETUP_SQ_AFF;
			p.sq_thपढ़ो_cpu = sq_thपढ़ो_cpu;
		पूर्ण
	पूर्ण

	fd = io_uring_setup(DEPTH, &p);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("io_uring_setup");
		वापस 1;
	पूर्ण
	s->ring_fd = fd;

	अगर (fixedbufs) अणु
		ret = io_uring_रेजिस्टर_buffers(s);
		अगर (ret < 0) अणु
			लिखो_त्रुटि("io_uring_register_buffers");
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (रेजिस्टर_files) अणु
		ret = io_uring_रेजिस्टर_files(s);
		अगर (ret < 0) अणु
			लिखो_त्रुटि("io_uring_register_files");
			वापस 1;
		पूर्ण
	पूर्ण

	ptr = mmap(0, p.sq_off.array + p.sq_entries * माप(__u32),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_SQ_RING);
	म_लिखो("sq_ring ptr = 0x%p\n", ptr);
	sring->head = ptr + p.sq_off.head;
	sring->tail = ptr + p.sq_off.tail;
	sring->ring_mask = ptr + p.sq_off.ring_mask;
	sring->ring_entries = ptr + p.sq_off.ring_entries;
	sring->flags = ptr + p.sq_off.flags;
	sring->array = ptr + p.sq_off.array;
	sq_ring_mask = *sring->ring_mask;

	s->sqes = mmap(0, p.sq_entries * माप(काष्ठा io_uring_sqe),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_SQES);
	म_लिखो("sqes ptr    = 0x%p\n", s->sqes);

	ptr = mmap(0, p.cq_off.cqes + p.cq_entries * माप(काष्ठा io_uring_cqe),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_CQ_RING);
	म_लिखो("cq_ring ptr = 0x%p\n", ptr);
	cring->head = ptr + p.cq_off.head;
	cring->tail = ptr + p.cq_off.tail;
	cring->ring_mask = ptr + p.cq_off.ring_mask;
	cring->ring_entries = ptr + p.cq_off.ring_entries;
	cring->cqes = ptr + p.cq_off.cqes;
	cq_ring_mask = *cring->ring_mask;
	वापस 0;
पूर्ण

अटल व्योम file_depths(अक्षर *buf)
अणु
	काष्ठा submitter *s = &submitters[0];
	अचिन्हित i;
	अक्षर *p;

	buf[0] = '\0';
	p = buf;
	क्रम (i = 0; i < s->nr_files; i++) अणु
		काष्ठा file *f = &s->files[i];

		अगर (i + 1 == s->nr_files)
			p += प्र_लिखो(p, "%d", f->pending_ios);
		अन्यथा
			p += प्र_लिखो(p, "%d, ", f->pending_ios);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा submitter *s = &submitters[0];
	अचिन्हित दीर्घ करोne, calls, reap;
	पूर्णांक err, i, flags, fd;
	अक्षर *fdepths;
	व्योम *ret;

	अगर (!करो_nop && argc < 2) अणु
		म_लिखो("%s: filename\n", argv[0]);
		वापस 1;
	पूर्ण

	flags = O_RDONLY | O_NOATIME;
	अगर (!buffered)
		flags |= O_सूचीECT;

	i = 1;
	जबतक (!करो_nop && i < argc) अणु
		काष्ठा file *f;

		अगर (s->nr_files == MAX_FDS) अणु
			म_लिखो("Max number of files (%d) reached\n", MAX_FDS);
			अवरोध;
		पूर्ण
		fd = खोलो(argv[i], flags);
		अगर (fd < 0) अणु
			लिखो_त्रुटि("open");
			वापस 1;
		पूर्ण

		f = &s->files[s->nr_files];
		f->real_fd = fd;
		अगर (get_file_size(f)) अणु
			म_लिखो("failed getting size of device/file\n");
			वापस 1;
		पूर्ण
		अगर (f->max_blocks <= 1) अणु
			म_लिखो("Zero file/device size?\n");
			वापस 1;
		पूर्ण
		f->max_blocks--;

		म_लिखो("Added file %s\n", argv[i]);
		s->nr_files++;
		i++;
	पूर्ण

	अगर (fixedbufs) अणु
		काष्ठा rlimit rlim;

		rlim.rlim_cur = RLIM_अनन्त;
		rlim.rlim_max = RLIM_अनन्त;
		अगर (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0) अणु
			लिखो_त्रुटि("setrlimit");
			वापस 1;
		पूर्ण
	पूर्ण

	arm_sig_पूर्णांक();

	क्रम (i = 0; i < DEPTH; i++) अणु
		व्योम *buf;

		अगर (posix_memalign(&buf, BS, BS)) अणु
			म_लिखो("failed alloc\n");
			वापस 1;
		पूर्ण
		s->iovecs[i].iov_base = buf;
		s->iovecs[i].iov_len = BS;
	पूर्ण

	err = setup_ring(s);
	अगर (err) अणु
		म_लिखो("ring setup failed: %s, %d\n", म_त्रुटि(त्रुटि_सं), err);
		वापस 1;
	पूर्ण
	म_लिखो("polled=%d, fixedbufs=%d, buffered=%d", polled, fixedbufs, buffered);
	म_लिखो(" QD=%d, sq_ring=%d, cq_ring=%d\n", DEPTH, *s->sq_ring.ring_entries, *s->cq_ring.ring_entries);

	pthपढ़ो_create(&s->thपढ़ो, शून्य, submitter_fn, s);

	fdepths = दो_स्मृति(8 * s->nr_files);
	reap = calls = करोne = 0;
	करो अणु
		अचिन्हित दीर्घ this_करोne = 0;
		अचिन्हित दीर्घ this_reap = 0;
		अचिन्हित दीर्घ this_call = 0;
		अचिन्हित दीर्घ rpc = 0, ipc = 0;

		sleep(1);
		this_करोne += s->करोne;
		this_call += s->calls;
		this_reap += s->reaps;
		अगर (this_call - calls) अणु
			rpc = (this_करोne - करोne) / (this_call - calls);
			ipc = (this_reap - reap) / (this_call - calls);
		पूर्ण अन्यथा
			rpc = ipc = -1;
		file_depths(fdepths);
		म_लिखो("IOPS=%lu, IOS/call=%ld/%ld, inflight=%u (%s)\n",
				this_करोne - करोne, rpc, ipc, s->inflight,
				fdepths);
		करोne = this_करोne;
		calls = this_call;
		reap = this_reap;
	पूर्ण जबतक (!finish);

	pthपढ़ो_join(s->thपढ़ो, &ret);
	बंद(s->ring_fd);
	मुक्त(fdepths);
	वापस 0;
पूर्ण
