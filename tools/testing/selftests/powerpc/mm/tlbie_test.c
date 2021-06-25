<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2019, Nick Piggin, Gautham R. Shenoy, Aneesh Kumar K.V, IBM Corp.
 */

/*
 *
 * Test tlbie/mtpidr race. We have 4 thपढ़ोs करोing flush/load/compare/store
 * sequence in a loop. The same thपढ़ोs also rung a context चयन task
 * that करोes sched_yield() in loop.
 *
 * The snapshot thपढ़ो mark the mmap area PROT_READ in between, make a copy
 * and copy it back to the original area. This helps us to detect अगर any
 * store जारीd to happen after we marked the memory PROT_READ.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <linux/futex.h>
#समावेश <unistd.h>
#समावेश <यंत्र/unistd.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <समय.स>
#समावेश <मानकतर्क.स>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <sys/prctl.h>

अटल अंतरभूत व्योम dcbf(अस्थिर अचिन्हित पूर्णांक *addr)
अणु
	__यंत्र__ __अस्थिर__ ("dcbf %y0; sync" : : "Z"(*(अचिन्हित अक्षर *)addr) : "memory");
पूर्ण

अटल व्योम err_msg(अक्षर *msg)
अणु

	समय_प्रकार now;
	समय(&now);
	म_लिखो("=================================\n");
	म_लिखो("    Error: %s\n", msg);
	म_लिखो("    %s", स_समय(&now));
	म_लिखो("=================================\n");
	निकास(1);
पूर्ण

अटल अक्षर *map1;
अटल अक्षर *map2;
अटल pid_t rim_process_pid;

/*
 * A "rim-sequence" is defined to be the sequence of the following
 * operations perक्रमmed on a memory word:
 *	1) FLUSH the contents of that word.
 *	2) LOAD the contents of that word.
 *	3) COMPARE the contents of that word with the content that was
 *	           previously stored at that word
 *	4) STORE new content पूर्णांकo that word.
 *
 * The thपढ़ोs in this test that perक्रमm the rim-sequence are termed
 * as rim_thपढ़ोs.
 */

/*
 * A "corruption" is defined to be the failed COMPARE operation in a
 * rim-sequence.
 *
 * A rim_thपढ़ो that detects a corruption inक्रमms about it to all the
 * other rim_thपढ़ोs, and the mem_snapshot thपढ़ो.
 */
अटल अस्थिर अचिन्हित पूर्णांक corruption_found;

/*
 * This defines the maximum number of rim_thपढ़ोs in this test.
 *
 * The THREAD_ID_BITS denote the number of bits required
 * to represent the thपढ़ो_ids [0..MAX_THREADS - 1].
 * We are being a bit paranoid here and set it to 8 bits,
 * though 6 bits suffice.
 *
 */
#घोषणा MAX_THREADS 		64
#घोषणा THREAD_ID_BITS		8
#घोषणा THREAD_ID_MASK		((1 << THREAD_ID_BITS) - 1)
अटल अचिन्हित पूर्णांक rim_thपढ़ो_ids[MAX_THREADS];
अटल pthपढ़ो_t rim_thपढ़ोs[MAX_THREADS];


/*
 * Each rim_thपढ़ो works on an exclusive "chunk" of size
 * RIM_CHUNK_SIZE.
 *
 * The ith rim_thपढ़ो works on the ith chunk.
 *
 * The ith chunk begins at
 * map1 + (i * RIM_CHUNK_SIZE)
 */
#घोषणा RIM_CHUNK_SIZE  	1024
#घोषणा BITS_PER_BYTE 		8
#घोषणा WORD_SIZE     		(माप(अचिन्हित पूर्णांक))
#घोषणा WORD_BITS		(WORD_SIZE * BITS_PER_BYTE)
#घोषणा WORDS_PER_CHUNK		(RIM_CHUNK_SIZE/WORD_SIZE)

अटल अंतरभूत अक्षर *compute_chunk_start_addr(अचिन्हित पूर्णांक thपढ़ो_id)
अणु
	अक्षर *chunk_start;

	chunk_start = (अक्षर *)((अचिन्हित दीर्घ)map1 +
			       (thपढ़ो_id * RIM_CHUNK_SIZE));

	वापस chunk_start;
पूर्ण

/*
 * The "word-offset" of a word-aligned address inside a chunk, is
 * defined to be the number of words that precede the address in that
 * chunk.
 *
 * WORD_OFFSET_BITS denote the number of bits required to represent
 * the word-offsets of all the word-aligned addresses of a chunk.
 */
#घोषणा WORD_OFFSET_BITS	(__builtin_ctz(WORDS_PER_CHUNK))
#घोषणा WORD_OFFSET_MASK	((1 << WORD_OFFSET_BITS) - 1)

अटल अंतरभूत अचिन्हित पूर्णांक compute_word_offset(अक्षर *start, अचिन्हित पूर्णांक *addr)
अणु
	अचिन्हित पूर्णांक delta_bytes, ret;
	delta_bytes = (अचिन्हित दीर्घ)addr - (अचिन्हित दीर्घ)start;

	ret = delta_bytes/WORD_SIZE;

	वापस ret;
पूर्ण

/*
 * A "sweep" is defined to be the sequential execution of the
 * rim-sequence by a rim_thपढ़ो on its chunk one word at a समय,
 * starting from the first word of its chunk and ending with the last
 * word of its chunk.
 *
 * Each sweep of a rim_thपढ़ो is uniquely identअगरied by a sweep_id.
 * SWEEP_ID_BITS denote the number of bits required to represent
 * the sweep_ids of rim_thपढ़ोs.
 *
 * As to why SWEEP_ID_BITS are computed as a function of THREAD_ID_BITS,
 * WORD_OFFSET_BITS, and WORD_BITS, see the "store-pattern" below.
 */
#घोषणा SWEEP_ID_BITS		(WORD_BITS - (THREAD_ID_BITS + WORD_OFFSET_BITS))
#घोषणा SWEEP_ID_MASK		((1 << SWEEP_ID_BITS) - 1)

/*
 * A "store-pattern" is the word-pattern that is stored पूर्णांकo a word
 * location in the 4)STORE step of the rim-sequence.
 *
 * In the store-pattern, we shall encode:
 *
 *      - The thपढ़ो-id of the rim_thपढ़ो perक्रमming the store
 *        (The most signअगरicant THREAD_ID_BITS)
 *
 *      - The word-offset of the address पूर्णांकo which the store is being
 *        perक्रमmed (The next WORD_OFFSET_BITS)
 *
 *      - The sweep_id of the current sweep in which the store is
 *        being perक्रमmed. (The lower SWEEP_ID_BITS)
 *
 * Store Pattern: 32 bits
 * |------------------|--------------------|---------------------------------|
 * |    Thपढ़ो id     |  Word offset       |         sweep_id                |
 * |------------------|--------------------|---------------------------------|
 *    THREAD_ID_BITS     WORD_OFFSET_BITS          SWEEP_ID_BITS
 *
 * In the store pattern, the (Thपढ़ो-id + Word-offset) uniquely identअगरy the
 * address to which the store is being perक्रमmed i.e,
 *    address == map1 +
 *              (Thपढ़ो-id * RIM_CHUNK_SIZE) + (Word-offset * WORD_SIZE)
 *
 * And the sweep_id in the store pattern identअगरies the समय when the
 * store was perक्रमmed by the rim_thपढ़ो.
 *
 * We shall use this property in the 3)COMPARE step of the
 * rim-sequence.
 */
#घोषणा SWEEP_ID_SHIFT	0
#घोषणा WORD_OFFSET_SHIFT	(SWEEP_ID_BITS)
#घोषणा THREAD_ID_SHIFT		(WORD_OFFSET_BITS + SWEEP_ID_BITS)

/*
 * Compute the store pattern क्रम a given thपढ़ो with id @tid, at
 * location @addr in the sweep identअगरied by @sweep_id
 */
अटल अंतरभूत अचिन्हित पूर्णांक compute_store_pattern(अचिन्हित पूर्णांक tid,
						 अचिन्हित पूर्णांक *addr,
						 अचिन्हित पूर्णांक sweep_id)
अणु
	अचिन्हित पूर्णांक ret = 0;
	अक्षर *start = compute_chunk_start_addr(tid);
	अचिन्हित पूर्णांक word_offset = compute_word_offset(start, addr);

	ret += (tid & THREAD_ID_MASK) << THREAD_ID_SHIFT;
	ret += (word_offset & WORD_OFFSET_MASK) << WORD_OFFSET_SHIFT;
	ret += (sweep_id & SWEEP_ID_MASK) << SWEEP_ID_SHIFT;
	वापस ret;
पूर्ण

/* Extract the thपढ़ो-id from the given store-pattern */
अटल अंतरभूत अचिन्हित पूर्णांक extract_tid(अचिन्हित पूर्णांक pattern)
अणु
	अचिन्हित पूर्णांक ret;

	ret = (pattern >> THREAD_ID_SHIFT) & THREAD_ID_MASK;
	वापस ret;
पूर्ण

/* Extract the word-offset from the given store-pattern */
अटल अंतरभूत अचिन्हित पूर्णांक extract_word_offset(अचिन्हित पूर्णांक pattern)
अणु
	अचिन्हित पूर्णांक ret;

	ret = (pattern >> WORD_OFFSET_SHIFT) & WORD_OFFSET_MASK;

	वापस ret;
पूर्ण

/* Extract the sweep-id from the given store-pattern */
अटल अंतरभूत अचिन्हित पूर्णांक extract_sweep_id(अचिन्हित पूर्णांक pattern)

अणु
	अचिन्हित पूर्णांक ret;

	ret = (pattern >> SWEEP_ID_SHIFT) & SWEEP_ID_MASK;

	वापस ret;
पूर्ण

/************************************************************
 *                                                          *
 *          Logging the output of the verअगरication          *
 *                                                          *
 ************************************************************/
#घोषणा LOGसूची_NAME_SIZE 100
अटल अक्षर logdir[LOGसूची_NAME_SIZE];

अटल खाता *fp[MAX_THREADS];
अटल स्थिर अक्षर logfilename[] ="Thread-%02d-Chunk";

अटल अंतरभूत व्योम start_verअगरication_log(अचिन्हित पूर्णांक tid,
					  अचिन्हित पूर्णांक *addr,
					  अचिन्हित पूर्णांक cur_sweep_id,
					  अचिन्हित पूर्णांक prev_sweep_id)
अणु
	खाता *f;
	अक्षर logfile[30];
	अक्षर path[LOGसूची_NAME_SIZE + 30];
	अक्षर separator[2] = "/";
	अक्षर *chunk_start = compute_chunk_start_addr(tid);
	अचिन्हित पूर्णांक size = RIM_CHUNK_SIZE;

	प्र_लिखो(logfile, logfilename, tid);
	म_नकल(path, logdir);
	म_जोड़ो(path, separator);
	म_जोड़ो(path, logfile);
	f = ख_खोलो(path, "w");

	अगर (!f) अणु
		err_msg("Unable to create logfile\n");
	पूर्ण

	fp[tid] = f;

	ख_लिखो(f, "----------------------------------------------------------\n");
	ख_लिखो(f, "PID                = %d\n", rim_process_pid);
	ख_लिखो(f, "Thread id          = %02d\n", tid);
	ख_लिखो(f, "Chunk Start Addr   = 0x%016lx\n", (अचिन्हित दीर्घ)chunk_start);
	ख_लिखो(f, "Chunk Size         = %d\n", size);
	ख_लिखो(f, "Next Store Addr    = 0x%016lx\n", (अचिन्हित दीर्घ)addr);
	ख_लिखो(f, "Current sweep-id   = 0x%08x\n", cur_sweep_id);
	ख_लिखो(f, "Previous sweep-id  = 0x%08x\n", prev_sweep_id);
	ख_लिखो(f, "----------------------------------------------------------\n");
पूर्ण

अटल अंतरभूत व्योम log_anamoly(अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक *addr,
			       अचिन्हित पूर्णांक expected, अचिन्हित पूर्णांक observed)
अणु
	खाता *f = fp[tid];

	ख_लिखो(f, "Thread %02d: Addr 0x%lx: Expected 0x%x, Observed 0x%x\n",
	        tid, (अचिन्हित दीर्घ)addr, expected, observed);
	ख_लिखो(f, "Thread %02d: Expected Thread id   = %02d\n", tid, extract_tid(expected));
	ख_लिखो(f, "Thread %02d: Observed Thread id   = %02d\n", tid, extract_tid(observed));
	ख_लिखो(f, "Thread %02d: Expected Word offset = %03d\n", tid, extract_word_offset(expected));
	ख_लिखो(f, "Thread %02d: Observed Word offset = %03d\n", tid, extract_word_offset(observed));
	ख_लिखो(f, "Thread %02d: Expected sweep-id    = 0x%x\n", tid, extract_sweep_id(expected));
	ख_लिखो(f, "Thread %02d: Observed sweep-id    = 0x%x\n", tid, extract_sweep_id(observed));
	ख_लिखो(f, "----------------------------------------------------------\n");
पूर्ण

अटल अंतरभूत व्योम end_verअगरication_log(अचिन्हित पूर्णांक tid, अचिन्हित nr_anamolies)
अणु
	खाता *f = fp[tid];
	अक्षर logfile[30];
	अक्षर path[LOGसूची_NAME_SIZE + 30];
	अक्षर separator[] = "/";

	ख_बंद(f);

	अगर (nr_anamolies == 0) अणु
		हटाओ(path);
		वापस;
	पूर्ण

	प्र_लिखो(logfile, logfilename, tid);
	म_नकल(path, logdir);
	म_जोड़ो(path, separator);
	म_जोड़ो(path, logfile);

	म_लिखो("Thread %02d chunk has %d corrupted words. For details check %s\n",
		tid, nr_anamolies, path);
पूर्ण

/*
 * When a COMPARE step of a rim-sequence fails, the rim_thपढ़ो inक्रमms
 * everyone अन्यथा via the shared_memory poपूर्णांकed to by
 * corruption_found variable. On seeing this, every thपढ़ो verअगरies the
 * content of its chunk as follows.
 *
 * Suppose a thपढ़ो identअगरied with @tid was about to store (but not
 * yet stored) to @next_store_addr in its current sweep identअगरied
 * @cur_sweep_id. Let @prev_sweep_id indicate the previous sweep_id.
 *
 * This implies that क्रम all the addresses @addr < @next_store_addr,
 * Thपढ़ो @tid has alपढ़ोy perक्रमmed a store as part of its current
 * sweep. Hence we expect the content of such @addr to be:
 *    |-------------------------------------------------|
 *    | tid   | word_offset(addr) |    cur_sweep_id     |
 *    |-------------------------------------------------|
 *
 * Since Thपढ़ो @tid is yet to perक्रमm stores on address
 * @next_store_addr and above, we expect the content of such an
 * address @addr to be:
 *    |-------------------------------------------------|
 *    | tid   | word_offset(addr) |    prev_sweep_id    |
 *    |-------------------------------------------------|
 *
 * The verअगरier function @verअगरy_chunk करोes this verअगरication and logs
 * any anamolies that it finds.
 */
अटल व्योम verअगरy_chunk(अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक *next_store_addr,
		  अचिन्हित पूर्णांक cur_sweep_id,
		  अचिन्हित पूर्णांक prev_sweep_id)
अणु
	अचिन्हित पूर्णांक *iter_ptr;
	अचिन्हित पूर्णांक size = RIM_CHUNK_SIZE;
	अचिन्हित पूर्णांक expected;
	अचिन्हित पूर्णांक observed;
	अक्षर *chunk_start = compute_chunk_start_addr(tid);

	पूर्णांक nr_anamolies = 0;

	start_verअगरication_log(tid, next_store_addr,
			       cur_sweep_id, prev_sweep_id);

	क्रम (iter_ptr = (अचिन्हित पूर्णांक *)chunk_start;
	     (अचिन्हित दीर्घ)iter_ptr < (अचिन्हित दीर्घ)chunk_start + size;
	     iter_ptr++) अणु
		अचिन्हित पूर्णांक expected_sweep_id;

		अगर (iter_ptr < next_store_addr) अणु
			expected_sweep_id = cur_sweep_id;
		पूर्ण अन्यथा अणु
			expected_sweep_id = prev_sweep_id;
		पूर्ण

		expected = compute_store_pattern(tid, iter_ptr, expected_sweep_id);

		dcbf((अस्थिर अचिन्हित पूर्णांक*)iter_ptr); //Flush beक्रमe पढ़ोing
		observed = *iter_ptr;

	        अगर (observed != expected) अणु
			nr_anamolies++;
			log_anamoly(tid, iter_ptr, expected, observed);
		पूर्ण
	पूर्ण

	end_verअगरication_log(tid, nr_anamolies);
पूर्ण

अटल व्योम set_pthपढ़ो_cpu(pthपढ़ो_t th, पूर्णांक cpu)
अणु
	cpu_set_t run_cpu_mask;
	काष्ठा sched_param param;

	CPU_ZERO(&run_cpu_mask);
	CPU_SET(cpu, &run_cpu_mask);
	pthपढ़ो_setaffinity_np(th, माप(cpu_set_t), &run_cpu_mask);

	param.sched_priority = 1;
	अगर (0 && sched_setscheduler(0, SCHED_FIFO, &param) == -1) अणु
		/* haven't reproduced with this setting, it समाप्तs अक्रमom preemption which may be a factor */
		ख_लिखो(मानक_त्रुटि, "could not set SCHED_FIFO, run as root?\n");
	पूर्ण
पूर्ण

अटल व्योम set_mycpu(पूर्णांक cpu)
अणु
	cpu_set_t run_cpu_mask;
	काष्ठा sched_param param;

	CPU_ZERO(&run_cpu_mask);
	CPU_SET(cpu, &run_cpu_mask);
	sched_setaffinity(0, माप(cpu_set_t), &run_cpu_mask);

	param.sched_priority = 1;
	अगर (0 && sched_setscheduler(0, SCHED_FIFO, &param) == -1) अणु
		ख_लिखो(मानक_त्रुटि, "could not set SCHED_FIFO, run as root?\n");
	पूर्ण
पूर्ण

अटल अस्थिर पूर्णांक segv_रुको;

अटल व्योम segv_handler(पूर्णांक signo, siginfo_t *info, व्योम *extra)
अणु
	जबतक (segv_रुको) अणु
		sched_yield();
	पूर्ण

पूर्ण

अटल व्योम set_segv_handler(व्योम)
अणु
	काष्ठा sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = segv_handler;

	अगर (sigaction(संक_अंश, &sa, शून्य) == -1) अणु
		लिखो_त्रुटि("sigaction");
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

पूर्णांक समयout = 0;
/*
 * This function is executed by every rim_thपढ़ो.
 *
 * This function perक्रमms sweeps over the exclusive chunks of the
 * rim_thपढ़ोs executing the rim-sequence one word at a समय.
 */
अटल व्योम *rim_fn(व्योम *arg)
अणु
	अचिन्हित पूर्णांक tid = *((अचिन्हित पूर्णांक *)arg);

	पूर्णांक size = RIM_CHUNK_SIZE;
	अक्षर *chunk_start = compute_chunk_start_addr(tid);

	अचिन्हित पूर्णांक prev_sweep_id;
	अचिन्हित पूर्णांक cur_sweep_id = 0;

	/* word access */
	अचिन्हित पूर्णांक pattern = cur_sweep_id;
	अचिन्हित पूर्णांक *pattern_ptr = &pattern;
	अचिन्हित पूर्णांक *w_ptr, पढ़ो_data;

	set_segv_handler();

	/*
	 * Let us initialize the chunk:
	 *
	 * Each word-aligned address addr in the chunk,
	 * is initialized to :
	 *    |-------------------------------------------------|
	 *    | tid   | word_offset(addr) |         0           |
	 *    |-------------------------------------------------|
	 */
	क्रम (w_ptr = (अचिन्हित पूर्णांक *)chunk_start;
	     (अचिन्हित दीर्घ)w_ptr < (अचिन्हित दीर्घ)(chunk_start) + size;
	     w_ptr++) अणु

		*pattern_ptr = compute_store_pattern(tid, w_ptr, cur_sweep_id);
		*w_ptr = *pattern_ptr;
	पूर्ण

	जबतक (!corruption_found && !समयout) अणु
		prev_sweep_id = cur_sweep_id;
		cur_sweep_id = cur_sweep_id + 1;

		क्रम (w_ptr = (अचिन्हित पूर्णांक *)chunk_start;
		     (अचिन्हित दीर्घ)w_ptr < (अचिन्हित दीर्घ)(chunk_start) + size;
		     w_ptr++)  अणु
			अचिन्हित पूर्णांक old_pattern;

			/*
			 * Compute the pattern that we would have
			 * stored at this location in the previous
			 * sweep.
			 */
			old_pattern = compute_store_pattern(tid, w_ptr, prev_sweep_id);

			/*
			 * FLUSH:Ensure that we flush the contents of
			 *       the cache beक्रमe loading
			 */
			dcbf((अस्थिर अचिन्हित पूर्णांक*)w_ptr); //Flush

			/* LOAD: Read the value */
			पढ़ो_data = *w_ptr; //Load

			/*
			 * COMPARE: Is it the same as what we had stored
			 *          in the previous sweep ? It better be!
			 */
			अगर (पढ़ो_data != old_pattern) अणु
				/* No it isn't! Tell everyone */
				corruption_found = 1;
			पूर्ण

			/*
			 * Beक्रमe perक्रमming a store, let us check अगर
			 * any rim_thपढ़ो has found a corruption.
			 */
			अगर (corruption_found || समयout) अणु
				/*
				 * Yes. Someone (including us!) has found
				 * a corruption :(
				 *
				 * Let us verअगरy that our chunk is
				 * correct.
				 */
				/* But first, let us allow the dust to settle करोwn! */
				verअगरy_chunk(tid, w_ptr, cur_sweep_id, prev_sweep_id);

				वापस 0;
			पूर्ण

			/*
			 * Compute the new pattern that we are going
			 * to ग_लिखो to this location
			 */
			*pattern_ptr = compute_store_pattern(tid, w_ptr, cur_sweep_id);

			/*
			 * STORE: Now let us ग_लिखो this pattern पूर्णांकo
			 *        the location
			 */
			*w_ptr = *pattern_ptr;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण


अटल अचिन्हित दीर्घ start_cpu = 0;
अटल अचिन्हित दीर्घ nrthपढ़ोs = 4;

अटल pthपढ़ो_t mem_snapshot_thपढ़ो;

अटल व्योम *mem_snapshot_fn(व्योम *arg)
अणु
	पूर्णांक page_size = getpagesize();
	माप_प्रकार size = page_size;
	व्योम *पंचांगp = दो_स्मृति(size);

	जबतक (!corruption_found && !समयout) अणु
		/* Stop memory migration once corruption is found */
		segv_रुको = 1;

		mprotect(map1, size, PROT_READ);

		/*
		 * Load from the working alias (map1). Loading from map2
		 * also fails.
		 */
		स_नकल(पंचांगp, map1, size);

		/*
		 * Stores must go via map2 which has ग_लिखो permissions, but
		 * the corrupted data tends to be seen in the snapshot buffer,
		 * so corruption करोes not appear to be पूर्णांकroduced at the
		 * copy-back via map2 alias here.
		 */
		स_नकल(map2, पंचांगp, size);
		/*
		 * Beक्रमe releasing other thपढ़ोs, must ensure the copy
		 * back to
		 */
		यंत्र अस्थिर("sync" ::: "memory");
		mprotect(map1, size, PROT_READ|PROT_WRITE);
		यंत्र अस्थिर("sync" ::: "memory");
		segv_रुको = 0;

		usleep(1); /* This value makes a big dअगरference */
	पूर्ण

	वापस 0;
पूर्ण

व्योम alrm_sighandler(पूर्णांक sig)
अणु
	समयout = 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;
	पूर्णांक page_size = getpagesize();
	समय_प्रकार now;
	पूर्णांक i, dir_error;
	pthपढ़ो_attr_t attr;
	key_t shm_key = (key_t) getpid();
	पूर्णांक shmid, run_समय = 20 * 60;
	काष्ठा sigaction sa_alrm;

	snम_लिखो(logdir, LOGसूची_NAME_SIZE,
		 "/tmp/logdir-%u", (अचिन्हित पूर्णांक)getpid());
	जबतक ((c = getopt(argc, argv, "r:hn:l:t:")) != -1) अणु
		चयन(c) अणु
		हाल 'r':
			start_cpu = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'h':
			म_लिखो("%s [-r <start_cpu>] [-n <nrthreads>] [-l <logdir>] [-t <timeout>]\n", argv[0]);
			निकास(0);
			अवरोध;
		हाल 'n':
			nrthपढ़ोs = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'l':
			म_नकलन(logdir, optarg, LOGसूची_NAME_SIZE - 1);
			अवरोध;
		हाल 't':
			run_समय = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		शेष:
			म_लिखो("invalid option\n");
			निकास(0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nrthपढ़ोs > MAX_THREADS)
		nrthपढ़ोs = MAX_THREADS;

	shmid = shmget(shm_key, page_size, IPC_CREAT|0666);
	अगर (shmid < 0) अणु
		err_msg("Failed shmget\n");
	पूर्ण

	map1 = shmat(shmid, शून्य, 0);
	अगर (map1 == (व्योम *) -1) अणु
		err_msg("Failed shmat");
	पूर्ण

	map2 = shmat(shmid, शून्य, 0);
	अगर (map2 == (व्योम *) -1) अणु
		err_msg("Failed shmat");
	पूर्ण

	dir_error = सूची_गढ़ो(logdir, 0755);

	अगर (dir_error) अणु
		err_msg("Failed mkdir");
	पूर्ण

	म_लिखो("start_cpu list:%lu\n", start_cpu);
	म_लिखो("number of worker threads:%lu + 1 snapshot thread\n", nrthपढ़ोs);
	म_लिखो("Allocated address:0x%016lx + secondary map:0x%016lx\n", (अचिन्हित दीर्घ)map1, (अचिन्हित दीर्घ)map2);
	म_लिखो("logdir at : %s\n", logdir);
	म_लिखो("Timeout: %d seconds\n", run_समय);

	समय(&now);
	म_लिखो("=================================\n");
	म_लिखो("     Starting Test\n");
	म_लिखो("     %s", स_समय(&now));
	म_लिखो("=================================\n");

	क्रम (i = 0; i < nrthपढ़ोs; i++) अणु
		अगर (1 && !विभाजन()) अणु
			prctl(PR_SET_PDEATHSIG, SIGKILL);
			set_mycpu(start_cpu + i);
			क्रम (;;)
				sched_yield();
			निकास(0);
		पूर्ण
	पूर्ण


	sa_alrm.sa_handler = &alrm_sighandler;
	sigemptyset(&sa_alrm.sa_mask);
	sa_alrm.sa_flags = 0;

	अगर (sigaction(SIGALRM, &sa_alrm, 0) == -1) अणु
		err_msg("Failed signal handler registration\n");
	पूर्ण

	alarm(run_समय);

	pthपढ़ो_attr_init(&attr);
	क्रम (i = 0; i < nrthपढ़ोs; i++) अणु
		rim_thपढ़ो_ids[i] = i;
		pthपढ़ो_create(&rim_thपढ़ोs[i], &attr, rim_fn, &rim_thपढ़ो_ids[i]);
		set_pthपढ़ो_cpu(rim_thपढ़ोs[i], start_cpu + i);
	पूर्ण

	pthपढ़ो_create(&mem_snapshot_thपढ़ो, &attr, mem_snapshot_fn, map1);
	set_pthपढ़ो_cpu(mem_snapshot_thपढ़ो, start_cpu + i);


	pthपढ़ो_join(mem_snapshot_thपढ़ो, शून्य);
	क्रम (i = 0; i < nrthपढ़ोs; i++) अणु
		pthपढ़ो_join(rim_thपढ़ोs[i], शून्य);
	पूर्ण

	अगर (!समयout) अणु
		समय(&now);
		म_लिखो("=================================\n");
		म_लिखो("      Data Corruption Detected\n");
		म_लिखो("      %s", स_समय(&now));
		म_लिखो("      See logfiles in %s\n", logdir);
		म_लिखो("=================================\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
