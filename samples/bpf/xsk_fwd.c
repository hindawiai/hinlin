<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. */

#घोषणा _GNU_SOURCE
#समावेश <poll.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/resource.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <getopt.h>
#समावेश <netinet/ether.h>
#समावेश <net/अगर.h>

#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_xdp.h>

#समावेश <bpf/libbpf.h>
#समावेश <bpf/xsk.h>
#समावेश <bpf/bpf.h>

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

प्रकार __u64 u64;
प्रकार __u32 u32;
प्रकार __u16 u16;
प्रकार __u8  u8;

/* This program illustrates the packet क्रमwarding between multiple AF_XDP
 * sockets in multi-thपढ़ोed environment. All thपढ़ोs are sharing a common
 * buffer pool, with each socket having its own निजी buffer cache.
 *
 * Example 1: Single thपढ़ो handling two sockets. The packets received by socket
 * A (पूर्णांकerface IFA, queue QA) are क्रमwarded to socket B (पूर्णांकerface IFB, queue
 * QB), जबतक the packets received by socket B are क्रमwarded to socket A. The
 * thपढ़ो is running on CPU core X:
 *
 *         ./xsk_fwd -i IFA -q QA -i IFB -q QB -c X
 *
 * Example 2: Two thपढ़ोs, each handling two sockets. The thपढ़ो running on CPU
 * core X क्रमwards all the packets received by socket A to socket B, and all the
 * packets received by socket B to socket A. The thपढ़ो running on CPU core Y is
 * perक्रमming the same packet क्रमwarding between sockets C and D:
 *
 *         ./xsk_fwd -i IFA -q QA -i IFB -q QB -i IFC -q QC -i IFD -q QD
 *         -c CX -c CY
 */

/*
 * Buffer pool and buffer cache
 *
 * For packet क्रमwarding, the packet buffers are typically allocated from the
 * pool क्रम packet reception and मुक्तd back to the pool क्रम further reuse once
 * the packet transmission is completed.
 *
 * The buffer pool is shared between multiple thपढ़ोs. In order to minimize the
 * access latency to the shared buffer pool, each thपढ़ो creates one (or
 * several) buffer caches, which, unlike the buffer pool, are निजी to the
 * thपढ़ो that creates them and thereक्रमe cannot be shared with other thपढ़ोs.
 * The access to the shared pool is only needed either (A) when the cache माला_लो
 * empty due to repeated buffer allocations and it needs to be replenished from
 * the pool, or (B) when the cache माला_लो full due to repeated buffer मुक्त and it
 * needs to be flushed back to the pull.
 *
 * In a packet क्रमwarding प्रणाली, a packet received on any input port can
 * potentially be transmitted on any output port, depending on the क्रमwarding
 * configuration. For AF_XDP sockets, क्रम this to work with zero-copy of the
 * packet buffers when, it is required that the buffer pool memory fits पूर्णांकo the
 * UMEM area shared by all the sockets.
 */

काष्ठा bpool_params अणु
	u32 n_buffers;
	u32 buffer_size;
	पूर्णांक mmap_flags;

	u32 n_users_max;
	u32 n_buffers_per_slab;
पूर्ण;

/* This buffer pool implementation organizes the buffers पूर्णांकo equally sized
 * sद_असल of *n_buffers_per_slab*. Initially, there are *n_sद_असल* sद_असल in the
 * pool that are completely filled with buffer poपूर्णांकers (full sद_असल).
 *
 * Each buffer cache has a slab क्रम buffer allocation and a slab क्रम buffer
 * मुक्त, with both of these sद_असल initially empty. When the cache's allocation
 * slab goes empty, it is swapped with one of the available full sद_असल from the
 * pool, अगर any is available. When the cache's मुक्त slab goes full, it is
 * swapped क्रम one of the empty sद_असल from the pool, which is guaranteed to
 * succeed.
 *
 * Partially filled sद_असल never get traded between the cache and the pool
 * (except when the cache itself is destroyed), which enables fast operation
 * through poपूर्णांकer swapping.
 */
काष्ठा bpool अणु
	काष्ठा bpool_params params;
	pthपढ़ो_mutex_t lock;
	व्योम *addr;

	u64 **sद_असल;
	u64 **sद_असल_reserved;
	u64 *buffers;
	u64 *buffers_reserved;

	u64 n_sद_असल;
	u64 n_sद_असल_reserved;
	u64 n_buffers;

	u64 n_sद_असल_available;
	u64 n_sद_असल_reserved_available;

	काष्ठा xsk_umem_config umem_cfg;
	काष्ठा xsk_ring_prod umem_fq;
	काष्ठा xsk_ring_cons umem_cq;
	काष्ठा xsk_umem *umem;
पूर्ण;

अटल काष्ठा bpool *
bpool_init(काष्ठा bpool_params *params,
	   काष्ठा xsk_umem_config *umem_cfg)
अणु
	काष्ठा rlimit r = अणुRLIM_अनन्त, RLIM_अनन्तपूर्ण;
	u64 n_sद_असल, n_sद_असल_reserved, n_buffers, n_buffers_reserved;
	u64 sद_असल_size, sद_असल_reserved_size;
	u64 buffers_size, buffers_reserved_size;
	u64 total_size, i;
	काष्ठा bpool *bp;
	u8 *p;
	पूर्णांक status;

	/* mmap prep. */
	अगर (setrlimit(RLIMIT_MEMLOCK, &r))
		वापस शून्य;

	/* bpool पूर्णांकernals dimensioning. */
	n_sद_असल = (params->n_buffers + params->n_buffers_per_slab - 1) /
		params->n_buffers_per_slab;
	n_sद_असल_reserved = params->n_users_max * 2;
	n_buffers = n_sद_असल * params->n_buffers_per_slab;
	n_buffers_reserved = n_sद_असल_reserved * params->n_buffers_per_slab;

	sद_असल_size = n_sद_असल * माप(u64 *);
	sद_असल_reserved_size = n_sद_असल_reserved * माप(u64 *);
	buffers_size = n_buffers * माप(u64);
	buffers_reserved_size = n_buffers_reserved * माप(u64);

	total_size = माप(काष्ठा bpool) +
		sद_असल_size + sद_असल_reserved_size +
		buffers_size + buffers_reserved_size;

	/* bpool memory allocation. */
	p = सुस्मृति(total_size, माप(u8));
	अगर (!p)
		वापस शून्य;

	/* bpool memory initialization. */
	bp = (काष्ठा bpool *)p;
	स_नकल(&bp->params, params, माप(*params));
	bp->params.n_buffers = n_buffers;

	bp->sद_असल = (u64 **)&p[माप(काष्ठा bpool)];
	bp->sद_असल_reserved = (u64 **)&p[माप(काष्ठा bpool) +
		sद_असल_size];
	bp->buffers = (u64 *)&p[माप(काष्ठा bpool) +
		sद_असल_size + sद_असल_reserved_size];
	bp->buffers_reserved = (u64 *)&p[माप(काष्ठा bpool) +
		sद_असल_size + sद_असल_reserved_size + buffers_size];

	bp->n_sद_असल = n_sद_असल;
	bp->n_sद_असल_reserved = n_sद_असल_reserved;
	bp->n_buffers = n_buffers;

	क्रम (i = 0; i < n_sद_असल; i++)
		bp->sद_असल[i] = &bp->buffers[i * params->n_buffers_per_slab];
	bp->n_sद_असल_available = n_sद_असल;

	क्रम (i = 0; i < n_sद_असल_reserved; i++)
		bp->sद_असल_reserved[i] = &bp->buffers_reserved[i *
			params->n_buffers_per_slab];
	bp->n_sद_असल_reserved_available = n_sद_असल_reserved;

	क्रम (i = 0; i < n_buffers; i++)
		bp->buffers[i] = i * params->buffer_size;

	/* lock. */
	status = pthपढ़ो_mutex_init(&bp->lock, शून्य);
	अगर (status) अणु
		मुक्त(p);
		वापस शून्य;
	पूर्ण

	/* mmap. */
	bp->addr = mmap(शून्य,
			n_buffers * params->buffer_size,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS | params->mmap_flags,
			-1,
			0);
	अगर (bp->addr == MAP_FAILED) अणु
		pthपढ़ो_mutex_destroy(&bp->lock);
		मुक्त(p);
		वापस शून्य;
	पूर्ण

	/* umem. */
	status = xsk_umem__create(&bp->umem,
				  bp->addr,
				  bp->params.n_buffers * bp->params.buffer_size,
				  &bp->umem_fq,
				  &bp->umem_cq,
				  umem_cfg);
	अगर (status) अणु
		munmap(bp->addr, bp->params.n_buffers * bp->params.buffer_size);
		pthपढ़ो_mutex_destroy(&bp->lock);
		मुक्त(p);
		वापस शून्य;
	पूर्ण
	स_नकल(&bp->umem_cfg, umem_cfg, माप(*umem_cfg));

	वापस bp;
पूर्ण

अटल व्योम
bpool_मुक्त(काष्ठा bpool *bp)
अणु
	अगर (!bp)
		वापस;

	xsk_umem__delete(bp->umem);
	munmap(bp->addr, bp->params.n_buffers * bp->params.buffer_size);
	pthपढ़ो_mutex_destroy(&bp->lock);
	मुक्त(bp);
पूर्ण

काष्ठा bcache अणु
	काष्ठा bpool *bp;

	u64 *slab_cons;
	u64 *slab_prod;

	u64 n_buffers_cons;
	u64 n_buffers_prod;
पूर्ण;

अटल u32
bcache_slab_size(काष्ठा bcache *bc)
अणु
	काष्ठा bpool *bp = bc->bp;

	वापस bp->params.n_buffers_per_slab;
पूर्ण

अटल काष्ठा bcache *
bcache_init(काष्ठा bpool *bp)
अणु
	काष्ठा bcache *bc;

	bc = सुस्मृति(1, माप(काष्ठा bcache));
	अगर (!bc)
		वापस शून्य;

	bc->bp = bp;
	bc->n_buffers_cons = 0;
	bc->n_buffers_prod = 0;

	pthपढ़ो_mutex_lock(&bp->lock);
	अगर (bp->n_sद_असल_reserved_available == 0) अणु
		pthपढ़ो_mutex_unlock(&bp->lock);
		मुक्त(bc);
		वापस शून्य;
	पूर्ण

	bc->slab_cons = bp->sद_असल_reserved[bp->n_sद_असल_reserved_available - 1];
	bc->slab_prod = bp->sद_असल_reserved[bp->n_sद_असल_reserved_available - 2];
	bp->n_sद_असल_reserved_available -= 2;
	pthपढ़ो_mutex_unlock(&bp->lock);

	वापस bc;
पूर्ण

अटल व्योम
bcache_मुक्त(काष्ठा bcache *bc)
अणु
	काष्ठा bpool *bp;

	अगर (!bc)
		वापस;

	/* In order to keep this example simple, the हाल of मुक्तing any
	 * existing buffers from the cache back to the pool is ignored.
	 */

	bp = bc->bp;
	pthपढ़ो_mutex_lock(&bp->lock);
	bp->sद_असल_reserved[bp->n_sद_असल_reserved_available] = bc->slab_prod;
	bp->sद_असल_reserved[bp->n_sद_असल_reserved_available + 1] = bc->slab_cons;
	bp->n_sद_असल_reserved_available += 2;
	pthपढ़ो_mutex_unlock(&bp->lock);

	मुक्त(bc);
पूर्ण

/* To work correctly, the implementation requires that the *n_buffers* input
 * argument is never greater than the buffer pool's *n_buffers_per_slab*. This
 * is typically the हाल, with one exception taking place when large number of
 * buffers are allocated at init समय (e.g. क्रम the UMEM fill queue setup).
 */
अटल अंतरभूत u32
bcache_cons_check(काष्ठा bcache *bc, u32 n_buffers)
अणु
	काष्ठा bpool *bp = bc->bp;
	u64 n_buffers_per_slab = bp->params.n_buffers_per_slab;
	u64 n_buffers_cons = bc->n_buffers_cons;
	u64 n_sद_असल_available;
	u64 *slab_full;

	/*
	 * Consumer slab is not empty: Use what's available locally. Do not
	 * look क्रम more buffers from the pool when the ask can only be
	 * partially satisfied.
	 */
	अगर (n_buffers_cons)
		वापस (n_buffers_cons < n_buffers) ?
			n_buffers_cons :
			n_buffers;

	/*
	 * Consumer slab is empty: look to trade the current consumer slab
	 * (full) क्रम a full slab from the pool, अगर any is available.
	 */
	pthपढ़ो_mutex_lock(&bp->lock);
	n_sद_असल_available = bp->n_sद_असल_available;
	अगर (!n_sद_असल_available) अणु
		pthपढ़ो_mutex_unlock(&bp->lock);
		वापस 0;
	पूर्ण

	n_sद_असल_available--;
	slab_full = bp->sद_असल[n_sद_असल_available];
	bp->sद_असल[n_sद_असल_available] = bc->slab_cons;
	bp->n_sद_असल_available = n_sद_असल_available;
	pthपढ़ो_mutex_unlock(&bp->lock);

	bc->slab_cons = slab_full;
	bc->n_buffers_cons = n_buffers_per_slab;
	वापस n_buffers;
पूर्ण

अटल अंतरभूत u64
bcache_cons(काष्ठा bcache *bc)
अणु
	u64 n_buffers_cons = bc->n_buffers_cons - 1;
	u64 buffer;

	buffer = bc->slab_cons[n_buffers_cons];
	bc->n_buffers_cons = n_buffers_cons;
	वापस buffer;
पूर्ण

अटल अंतरभूत व्योम
bcache_prod(काष्ठा bcache *bc, u64 buffer)
अणु
	काष्ठा bpool *bp = bc->bp;
	u64 n_buffers_per_slab = bp->params.n_buffers_per_slab;
	u64 n_buffers_prod = bc->n_buffers_prod;
	u64 n_sद_असल_available;
	u64 *slab_empty;

	/*
	 * Producer slab is not yet full: store the current buffer to it.
	 */
	अगर (n_buffers_prod < n_buffers_per_slab) अणु
		bc->slab_prod[n_buffers_prod] = buffer;
		bc->n_buffers_prod = n_buffers_prod + 1;
		वापस;
	पूर्ण

	/*
	 * Producer slab is full: trade the cache's current producer slab
	 * (full) क्रम an empty slab from the pool, then store the current
	 * buffer to the new producer slab. As one full slab exists in the
	 * cache, it is guaranteed that there is at least one empty slab
	 * available in the pool.
	 */
	pthपढ़ो_mutex_lock(&bp->lock);
	n_sद_असल_available = bp->n_sद_असल_available;
	slab_empty = bp->sद_असल[n_sद_असल_available];
	bp->sद_असल[n_sद_असल_available] = bc->slab_prod;
	bp->n_sद_असल_available = n_sद_असल_available + 1;
	pthपढ़ो_mutex_unlock(&bp->lock);

	slab_empty[0] = buffer;
	bc->slab_prod = slab_empty;
	bc->n_buffers_prod = 1;
पूर्ण

/*
 * Port
 *
 * Each of the क्रमwarding ports sits on top of an AF_XDP socket. In order क्रम
 * packet क्रमwarding to happen with no packet buffer copy, all the sockets need
 * to share the same UMEM area, which is used as the buffer pool memory.
 */
#अगर_अघोषित MAX_BURST_RX
#घोषणा MAX_BURST_RX 64
#पूर्ण_अगर

#अगर_अघोषित MAX_BURST_TX
#घोषणा MAX_BURST_TX 64
#पूर्ण_अगर

काष्ठा burst_rx अणु
	u64 addr[MAX_BURST_RX];
	u32 len[MAX_BURST_RX];
पूर्ण;

काष्ठा burst_tx अणु
	u64 addr[MAX_BURST_TX];
	u32 len[MAX_BURST_TX];
	u32 n_pkts;
पूर्ण;

काष्ठा port_params अणु
	काष्ठा xsk_socket_config xsk_cfg;
	काष्ठा bpool *bp;
	स्थिर अक्षर *अगरace;
	u32 अगरace_queue;
पूर्ण;

काष्ठा port अणु
	काष्ठा port_params params;

	काष्ठा bcache *bc;

	काष्ठा xsk_ring_cons rxq;
	काष्ठा xsk_ring_prod txq;
	काष्ठा xsk_ring_prod umem_fq;
	काष्ठा xsk_ring_cons umem_cq;
	काष्ठा xsk_socket *xsk;
	पूर्णांक umem_fq_initialized;

	u64 n_pkts_rx;
	u64 n_pkts_tx;
पूर्ण;

अटल व्योम
port_मुक्त(काष्ठा port *p)
अणु
	अगर (!p)
		वापस;

	/* To keep this example simple, the code to मुक्त the buffers from the
	 * socket's receive and transmit queues, as well as from the UMEM fill
	 * and completion queues, is not included.
	 */

	अगर (p->xsk)
		xsk_socket__delete(p->xsk);

	bcache_मुक्त(p->bc);

	मुक्त(p);
पूर्ण

अटल काष्ठा port *
port_init(काष्ठा port_params *params)
अणु
	काष्ठा port *p;
	u32 umem_fq_size, pos = 0;
	पूर्णांक status, i;

	/* Memory allocation and initialization. */
	p = सुस्मृति(माप(काष्ठा port), 1);
	अगर (!p)
		वापस शून्य;

	स_नकल(&p->params, params, माप(p->params));
	umem_fq_size = params->bp->umem_cfg.fill_size;

	/* bcache. */
	p->bc = bcache_init(params->bp);
	अगर (!p->bc ||
	    (bcache_slab_size(p->bc) < umem_fq_size) ||
	    (bcache_cons_check(p->bc, umem_fq_size) < umem_fq_size)) अणु
		port_मुक्त(p);
		वापस शून्य;
	पूर्ण

	/* xsk socket. */
	status = xsk_socket__create_shared(&p->xsk,
					   params->अगरace,
					   params->अगरace_queue,
					   params->bp->umem,
					   &p->rxq,
					   &p->txq,
					   &p->umem_fq,
					   &p->umem_cq,
					   &params->xsk_cfg);
	अगर (status) अणु
		port_मुक्त(p);
		वापस शून्य;
	पूर्ण

	/* umem fq. */
	xsk_ring_prod__reserve(&p->umem_fq, umem_fq_size, &pos);

	क्रम (i = 0; i < umem_fq_size; i++)
		*xsk_ring_prod__fill_addr(&p->umem_fq, pos + i) =
			bcache_cons(p->bc);

	xsk_ring_prod__submit(&p->umem_fq, umem_fq_size);
	p->umem_fq_initialized = 1;

	वापस p;
पूर्ण

अटल अंतरभूत u32
port_rx_burst(काष्ठा port *p, काष्ठा burst_rx *b)
अणु
	u32 n_pkts, pos, i;

	/* Free buffers क्रम FQ replenish. */
	n_pkts = ARRAY_SIZE(b->addr);

	n_pkts = bcache_cons_check(p->bc, n_pkts);
	अगर (!n_pkts)
		वापस 0;

	/* RXQ. */
	n_pkts = xsk_ring_cons__peek(&p->rxq, n_pkts, &pos);
	अगर (!n_pkts) अणु
		अगर (xsk_ring_prod__needs_wakeup(&p->umem_fq)) अणु
			काष्ठा pollfd pollfd = अणु
				.fd = xsk_socket__fd(p->xsk),
				.events = POLLIN,
			पूर्ण;

			poll(&pollfd, 1, 0);
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < n_pkts; i++) अणु
		b->addr[i] = xsk_ring_cons__rx_desc(&p->rxq, pos + i)->addr;
		b->len[i] = xsk_ring_cons__rx_desc(&p->rxq, pos + i)->len;
	पूर्ण

	xsk_ring_cons__release(&p->rxq, n_pkts);
	p->n_pkts_rx += n_pkts;

	/* UMEM FQ. */
	क्रम ( ; ; ) अणु
		पूर्णांक status;

		status = xsk_ring_prod__reserve(&p->umem_fq, n_pkts, &pos);
		अगर (status == n_pkts)
			अवरोध;

		अगर (xsk_ring_prod__needs_wakeup(&p->umem_fq)) अणु
			काष्ठा pollfd pollfd = अणु
				.fd = xsk_socket__fd(p->xsk),
				.events = POLLIN,
			पूर्ण;

			poll(&pollfd, 1, 0);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < n_pkts; i++)
		*xsk_ring_prod__fill_addr(&p->umem_fq, pos + i) =
			bcache_cons(p->bc);

	xsk_ring_prod__submit(&p->umem_fq, n_pkts);

	वापस n_pkts;
पूर्ण

अटल अंतरभूत व्योम
port_tx_burst(काष्ठा port *p, काष्ठा burst_tx *b)
अणु
	u32 n_pkts, pos, i;
	पूर्णांक status;

	/* UMEM CQ. */
	n_pkts = p->params.bp->umem_cfg.comp_size;

	n_pkts = xsk_ring_cons__peek(&p->umem_cq, n_pkts, &pos);

	क्रम (i = 0; i < n_pkts; i++) अणु
		u64 addr = *xsk_ring_cons__comp_addr(&p->umem_cq, pos + i);

		bcache_prod(p->bc, addr);
	पूर्ण

	xsk_ring_cons__release(&p->umem_cq, n_pkts);

	/* TXQ. */
	n_pkts = b->n_pkts;

	क्रम ( ; ; ) अणु
		status = xsk_ring_prod__reserve(&p->txq, n_pkts, &pos);
		अगर (status == n_pkts)
			अवरोध;

		अगर (xsk_ring_prod__needs_wakeup(&p->txq))
			sendto(xsk_socket__fd(p->xsk), शून्य, 0, MSG_DONTWAIT,
			       शून्य, 0);
	पूर्ण

	क्रम (i = 0; i < n_pkts; i++) अणु
		xsk_ring_prod__tx_desc(&p->txq, pos + i)->addr = b->addr[i];
		xsk_ring_prod__tx_desc(&p->txq, pos + i)->len = b->len[i];
	पूर्ण

	xsk_ring_prod__submit(&p->txq, n_pkts);
	अगर (xsk_ring_prod__needs_wakeup(&p->txq))
		sendto(xsk_socket__fd(p->xsk), शून्य, 0, MSG_DONTWAIT, शून्य, 0);
	p->n_pkts_tx += n_pkts;
पूर्ण

/*
 * Thपढ़ो
 *
 * Packet क्रमwarding thपढ़ोs.
 */
#अगर_अघोषित MAX_PORTS_PER_THREAD
#घोषणा MAX_PORTS_PER_THREAD 16
#पूर्ण_अगर

काष्ठा thपढ़ो_data अणु
	काष्ठा port *ports_rx[MAX_PORTS_PER_THREAD];
	काष्ठा port *ports_tx[MAX_PORTS_PER_THREAD];
	u32 n_ports_rx;
	काष्ठा burst_rx burst_rx;
	काष्ठा burst_tx burst_tx[MAX_PORTS_PER_THREAD];
	u32 cpu_core_id;
	पूर्णांक quit;
पूर्ण;

अटल व्योम swap_mac_addresses(व्योम *data)
अणु
	काष्ठा ether_header *eth = (काष्ठा ether_header *)data;
	काष्ठा ether_addr *src_addr = (काष्ठा ether_addr *)&eth->ether_shost;
	काष्ठा ether_addr *dst_addr = (काष्ठा ether_addr *)&eth->ether_dhost;
	काष्ठा ether_addr पंचांगp;

	पंचांगp = *src_addr;
	*src_addr = *dst_addr;
	*dst_addr = पंचांगp;
पूर्ण

अटल व्योम *
thपढ़ो_func(व्योम *arg)
अणु
	काष्ठा thपढ़ो_data *t = arg;
	cpu_set_t cpu_cores;
	u32 i;

	CPU_ZERO(&cpu_cores);
	CPU_SET(t->cpu_core_id, &cpu_cores);
	pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set_t), &cpu_cores);

	क्रम (i = 0; !t->quit; i = (i + 1) & (t->n_ports_rx - 1)) अणु
		काष्ठा port *port_rx = t->ports_rx[i];
		काष्ठा port *port_tx = t->ports_tx[i];
		काष्ठा burst_rx *brx = &t->burst_rx;
		काष्ठा burst_tx *btx = &t->burst_tx[i];
		u32 n_pkts, j;

		/* RX. */
		n_pkts = port_rx_burst(port_rx, brx);
		अगर (!n_pkts)
			जारी;

		/* Process & TX. */
		क्रम (j = 0; j < n_pkts; j++) अणु
			u64 addr = xsk_umem__add_offset_to_addr(brx->addr[j]);
			u8 *pkt = xsk_umem__get_data(port_rx->params.bp->addr,
						     addr);

			swap_mac_addresses(pkt);

			btx->addr[btx->n_pkts] = brx->addr[j];
			btx->len[btx->n_pkts] = brx->len[j];
			btx->n_pkts++;

			अगर (btx->n_pkts == MAX_BURST_TX) अणु
				port_tx_burst(port_tx, btx);
				btx->n_pkts = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Process
 */
अटल स्थिर काष्ठा bpool_params bpool_params_शेष = अणु
	.n_buffers = 64 * 1024,
	.buffer_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
	.mmap_flags = 0,

	.n_users_max = 16,
	.n_buffers_per_slab = XSK_RING_PROD__DEFAULT_NUM_DESCS * 2,
पूर्ण;

अटल स्थिर काष्ठा xsk_umem_config umem_cfg_शेष = अणु
	.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS * 2,
	.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
	.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
	.frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा port_params port_params_शेष = अणु
	.xsk_cfg = अणु
		.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.libbpf_flags = 0,
		.xdp_flags = XDP_FLAGS_DRV_MODE,
		.bind_flags = XDP_USE_NEED_WAKEUP | XDP_ZEROCOPY,
	पूर्ण,

	.bp = शून्य,
	.अगरace = शून्य,
	.अगरace_queue = 0,
पूर्ण;

#अगर_अघोषित MAX_PORTS
#घोषणा MAX_PORTS 64
#पूर्ण_अगर

#अगर_अघोषित MAX_THREADS
#घोषणा MAX_THREADS 64
#पूर्ण_अगर

अटल काष्ठा bpool_params bpool_params;
अटल काष्ठा xsk_umem_config umem_cfg;
अटल काष्ठा bpool *bp;

अटल काष्ठा port_params port_params[MAX_PORTS];
अटल काष्ठा port *ports[MAX_PORTS];
अटल u64 n_pkts_rx[MAX_PORTS];
अटल u64 n_pkts_tx[MAX_PORTS];
अटल पूर्णांक n_ports;

अटल pthपढ़ो_t thपढ़ोs[MAX_THREADS];
अटल काष्ठा thपढ़ो_data thपढ़ो_data[MAX_THREADS];
अटल पूर्णांक n_thपढ़ोs;

अटल व्योम
prपूर्णांक_usage(अक्षर *prog_name)
अणु
	स्थिर अक्षर *usage =
		"Usage:\n"
		"\t%s [ -b SIZE ] -c CORE -i INTERFACE [ -q QUEUE ]\n"
		"\n"
		"-c CORE        CPU core to run a packet forwarding thread\n"
		"               on. May be invoked multiple times.\n"
		"\n"
		"-b SIZE        Number of buffers in the buffer pool shared\n"
		"               by all the forwarding threads. Default: %u.\n"
		"\n"
		"-i INTERFACE   Network interface. Each (INTERFACE, QUEUE)\n"
		"               pair specifies one forwarding port. May be\n"
		"               invoked multiple times.\n"
		"\n"
		"-q QUEUE       Network interface queue for RX and TX. Each\n"
		"               (INTERFACE, QUEUE) pair specified one\n"
		"               forwarding port. Default: %u. May be invoked\n"
		"               multiple times.\n"
		"\n";
	म_लिखो(usage,
	       prog_name,
	       bpool_params_शेष.n_buffers,
	       port_params_शेष.अगरace_queue);
पूर्ण

अटल पूर्णांक
parse_args(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा option lgopts[] = अणु
		अणु शून्य,  0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक opt, option_index;

	/* Parse the input arguments. */
	क्रम ( ; ;) अणु
		opt = getopt_दीर्घ(argc, argv, "c:i:q:", lgopts, &option_index);
		अगर (opt == खातापूर्ण)
			अवरोध;

		चयन (opt) अणु
		हाल 'b':
			bpool_params.n_buffers = म_से_प(optarg);
			अवरोध;

		हाल 'c':
			अगर (n_thपढ़ोs == MAX_THREADS) अणु
				म_लिखो("Max number of threads (%d) reached.\n",
				       MAX_THREADS);
				वापस -1;
			पूर्ण

			thपढ़ो_data[n_thपढ़ोs].cpu_core_id = म_से_प(optarg);
			n_thपढ़ोs++;
			अवरोध;

		हाल 'i':
			अगर (n_ports == MAX_PORTS) अणु
				म_लिखो("Max number of ports (%d) reached.\n",
				       MAX_PORTS);
				वापस -1;
			पूर्ण

			port_params[n_ports].अगरace = optarg;
			port_params[n_ports].अगरace_queue = 0;
			n_ports++;
			अवरोध;

		हाल 'q':
			अगर (n_ports == 0) अणु
				म_लिखो("No port specified for queue.\n");
				वापस -1;
			पूर्ण
			port_params[n_ports - 1].अगरace_queue = म_से_प(optarg);
			अवरोध;

		शेष:
			म_लिखो("Illegal argument.\n");
			वापस -1;
		पूर्ण
	पूर्ण

	optind = 1; /* reset getopt lib */

	/* Check the input arguments. */
	अगर (!n_ports) अणु
		म_लिखो("No ports specified.\n");
		वापस -1;
	पूर्ण

	अगर (!n_thपढ़ोs) अणु
		म_लिखो("No threads specified.\n");
		वापस -1;
	पूर्ण

	अगर (n_ports % n_thपढ़ोs) अणु
		म_लिखो("Ports cannot be evenly distributed to threads.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
prपूर्णांक_port(u32 port_id)
अणु
	काष्ठा port *port = ports[port_id];

	म_लिखो("Port %u: interface = %s, queue = %u\n",
	       port_id, port->params.अगरace, port->params.अगरace_queue);
पूर्ण

अटल व्योम
prपूर्णांक_thपढ़ो(u32 thपढ़ो_id)
अणु
	काष्ठा thपढ़ो_data *t = &thपढ़ो_data[thपढ़ो_id];
	u32 i;

	म_लिखो("Thread %u (CPU core %u): ",
	       thपढ़ो_id, t->cpu_core_id);

	क्रम (i = 0; i < t->n_ports_rx; i++) अणु
		काष्ठा port *port_rx = t->ports_rx[i];
		काष्ठा port *port_tx = t->ports_tx[i];

		म_लिखो("(%s, %u) -> (%s, %u), ",
		       port_rx->params.अगरace,
		       port_rx->params.अगरace_queue,
		       port_tx->params.अगरace,
		       port_tx->params.अगरace_queue);
	पूर्ण

	म_लिखो("\n");
पूर्ण

अटल व्योम
prपूर्णांक_port_stats_separator(व्योम)
अणु
	म_लिखो("+-%4s-+-%12s-+-%13s-+-%12s-+-%13s-+\n",
	       "----",
	       "------------",
	       "-------------",
	       "------------",
	       "-------------");
पूर्ण

अटल व्योम
prपूर्णांक_port_stats_header(व्योम)
अणु
	prपूर्णांक_port_stats_separator();
	म_लिखो("| %4s | %12s | %13s | %12s | %13s |\n",
	       "Port",
	       "RX packets",
	       "RX rate (pps)",
	       "TX packets",
	       "TX_rate (pps)");
	prपूर्णांक_port_stats_separator();
पूर्ण

अटल व्योम
prपूर्णांक_port_stats_trailer(व्योम)
अणु
	prपूर्णांक_port_stats_separator();
	म_लिखो("\n");
पूर्ण

अटल व्योम
prपूर्णांक_port_stats(पूर्णांक port_id, u64 ns_dअगरf)
अणु
	काष्ठा port *p = ports[port_id];
	द्विगुन rx_pps, tx_pps;

	rx_pps = (p->n_pkts_rx - n_pkts_rx[port_id]) * 1000000000. / ns_dअगरf;
	tx_pps = (p->n_pkts_tx - n_pkts_tx[port_id]) * 1000000000. / ns_dअगरf;

	म_लिखो("| %4d | %12llu | %13.0f | %12llu | %13.0f |\n",
	       port_id,
	       p->n_pkts_rx,
	       rx_pps,
	       p->n_pkts_tx,
	       tx_pps);

	n_pkts_rx[port_id] = p->n_pkts_rx;
	n_pkts_tx[port_id] = p->n_pkts_tx;
पूर्ण

अटल व्योम
prपूर्णांक_port_stats_all(u64 ns_dअगरf)
अणु
	पूर्णांक i;

	prपूर्णांक_port_stats_header();
	क्रम (i = 0; i < n_ports; i++)
		prपूर्णांक_port_stats(i, ns_dअगरf);
	prपूर्णांक_port_stats_trailer();
पूर्ण

अटल पूर्णांक quit;

अटल व्योम
संकेत_handler(पूर्णांक sig)
अणु
	quit = 1;
पूर्ण

अटल व्योम हटाओ_xdp_program(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < n_ports; i++)
		bpf_set_link_xdp_fd(अगर_nametoindex(port_params[i].अगरace), -1,
				    port_params[i].xsk_cfg.xdp_flags);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा बारpec समय;
	u64 ns0;
	पूर्णांक i;

	/* Parse args. */
	स_नकल(&bpool_params, &bpool_params_शेष,
	       माप(काष्ठा bpool_params));
	स_नकल(&umem_cfg, &umem_cfg_शेष,
	       माप(काष्ठा xsk_umem_config));
	क्रम (i = 0; i < MAX_PORTS; i++)
		स_नकल(&port_params[i], &port_params_शेष,
		       माप(काष्ठा port_params));

	अगर (parse_args(argc, argv)) अणु
		prपूर्णांक_usage(argv[0]);
		वापस -1;
	पूर्ण

	/* Buffer pool initialization. */
	bp = bpool_init(&bpool_params, &umem_cfg);
	अगर (!bp) अणु
		म_लिखो("Buffer pool initialization failed.\n");
		वापस -1;
	पूर्ण
	म_लिखो("Buffer pool created successfully.\n");

	/* Ports initialization. */
	क्रम (i = 0; i < MAX_PORTS; i++)
		port_params[i].bp = bp;

	क्रम (i = 0; i < n_ports; i++) अणु
		ports[i] = port_init(&port_params[i]);
		अगर (!ports[i]) अणु
			म_लिखो("Port %d initialization failed.\n", i);
			वापस -1;
		पूर्ण
		prपूर्णांक_port(i);
	पूर्ण
	म_लिखो("All ports created successfully.\n");

	/* Thपढ़ोs. */
	क्रम (i = 0; i < n_thपढ़ोs; i++) अणु
		काष्ठा thपढ़ो_data *t = &thपढ़ो_data[i];
		u32 n_ports_per_thपढ़ो = n_ports / n_thपढ़ोs, j;

		क्रम (j = 0; j < n_ports_per_thपढ़ो; j++) अणु
			t->ports_rx[j] = ports[i * n_ports_per_thपढ़ो + j];
			t->ports_tx[j] = ports[i * n_ports_per_thपढ़ो +
				(j + 1) % n_ports_per_thपढ़ो];
		पूर्ण

		t->n_ports_rx = n_ports_per_thपढ़ो;

		prपूर्णांक_thपढ़ो(i);
	पूर्ण

	क्रम (i = 0; i < n_thपढ़ोs; i++) अणु
		पूर्णांक status;

		status = pthपढ़ो_create(&thपढ़ोs[i],
					शून्य,
					thपढ़ो_func,
					&thपढ़ो_data[i]);
		अगर (status) अणु
			म_लिखो("Thread %d creation failed.\n", i);
			वापस -1;
		पूर्ण
	पूर्ण
	म_लिखो("All threads created successfully.\n");

	/* Prपूर्णांक statistics. */
	संकेत(संक_विघ्न, संकेत_handler);
	संकेत(संक_इति, संकेत_handler);
	संकेत(SIGABRT, संकेत_handler);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &समय);
	ns0 = समय.tv_sec * 1000000000UL + समय.tv_nsec;
	क्रम ( ; !quit; ) अणु
		u64 ns1, ns_dअगरf;

		sleep(1);
		घड़ी_समय_लो(CLOCK_MONOTONIC, &समय);
		ns1 = समय.tv_sec * 1000000000UL + समय.tv_nsec;
		ns_dअगरf = ns1 - ns0;
		ns0 = ns1;

		prपूर्णांक_port_stats_all(ns_dअगरf);
	पूर्ण

	/* Thपढ़ोs completion. */
	म_लिखो("Quit.\n");
	क्रम (i = 0; i < n_thपढ़ोs; i++)
		thपढ़ो_data[i].quit = 1;

	क्रम (i = 0; i < n_thपढ़ोs; i++)
		pthपढ़ो_join(thपढ़ोs[i], शून्य);

	क्रम (i = 0; i < n_ports; i++)
		port_मुक्त(ports[i]);

	bpool_मुक्त(bp);

	हटाओ_xdp_program();

	वापस 0;
पूर्ण
