<शैली गुरु>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश "liburing.h"

अटल पूर्णांक io_uring_mmap(पूर्णांक fd, काष्ठा io_uring_params *p,
			 काष्ठा io_uring_sq *sq, काष्ठा io_uring_cq *cq)
अणु
	माप_प्रकार size;
	व्योम *ptr;
	पूर्णांक ret;

	sq->ring_sz = p->sq_off.array + p->sq_entries * माप(अचिन्हित);
	ptr = mmap(0, sq->ring_sz, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_SQ_RING);
	अगर (ptr == MAP_FAILED)
		वापस -त्रुटि_सं;
	sq->khead = ptr + p->sq_off.head;
	sq->ktail = ptr + p->sq_off.tail;
	sq->kring_mask = ptr + p->sq_off.ring_mask;
	sq->kring_entries = ptr + p->sq_off.ring_entries;
	sq->kflags = ptr + p->sq_off.flags;
	sq->kdropped = ptr + p->sq_off.dropped;
	sq->array = ptr + p->sq_off.array;

	size = p->sq_entries * माप(काष्ठा io_uring_sqe);
	sq->sqes = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_POPULATE, fd,
				IORING_OFF_SQES);
	अगर (sq->sqes == MAP_FAILED) अणु
		ret = -त्रुटि_सं;
err:
		munmap(sq->khead, sq->ring_sz);
		वापस ret;
	पूर्ण

	cq->ring_sz = p->cq_off.cqes + p->cq_entries * माप(काष्ठा io_uring_cqe);
	ptr = mmap(0, cq->ring_sz, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_CQ_RING);
	अगर (ptr == MAP_FAILED) अणु
		ret = -त्रुटि_सं;
		munmap(sq->sqes, p->sq_entries * माप(काष्ठा io_uring_sqe));
		जाओ err;
	पूर्ण
	cq->khead = ptr + p->cq_off.head;
	cq->ktail = ptr + p->cq_off.tail;
	cq->kring_mask = ptr + p->cq_off.ring_mask;
	cq->kring_entries = ptr + p->cq_off.ring_entries;
	cq->koverflow = ptr + p->cq_off.overflow;
	cq->cqes = ptr + p->cq_off.cqes;
	वापस 0;
पूर्ण

/*
 * For users that want to specअगरy sq_thपढ़ो_cpu or sq_thपढ़ो_idle, this
 * पूर्णांकerface is a convenient helper क्रम mmap()ing the rings.
 * Returns -1 on error, or zero on success.  On success, 'ring'
 * contains the necessary inक्रमmation to पढ़ो/ग_लिखो to the rings.
 */
पूर्णांक io_uring_queue_mmap(पूर्णांक fd, काष्ठा io_uring_params *p, काष्ठा io_uring *ring)
अणु
	पूर्णांक ret;

	स_रखो(ring, 0, माप(*ring));
	ret = io_uring_mmap(fd, p, &ring->sq, &ring->cq);
	अगर (!ret)
		ring->ring_fd = fd;
	वापस ret;
पूर्ण

/*
 * Returns -1 on error, or zero on success. On success, 'ring'
 * contains the necessary inक्रमmation to पढ़ो/ग_लिखो to the rings.
 */
पूर्णांक io_uring_queue_init(अचिन्हित entries, काष्ठा io_uring *ring, अचिन्हित flags)
अणु
	काष्ठा io_uring_params p;
	पूर्णांक fd, ret;

	स_रखो(&p, 0, माप(p));
	p.flags = flags;

	fd = io_uring_setup(entries, &p);
	अगर (fd < 0)
		वापस fd;

	ret = io_uring_queue_mmap(fd, &p, ring);
	अगर (ret)
		बंद(fd);

	वापस ret;
पूर्ण

व्योम io_uring_queue_निकास(काष्ठा io_uring *ring)
अणु
	काष्ठा io_uring_sq *sq = &ring->sq;
	काष्ठा io_uring_cq *cq = &ring->cq;

	munmap(sq->sqes, *sq->kring_entries * माप(काष्ठा io_uring_sqe));
	munmap(sq->khead, sq->ring_sz);
	munmap(cq->khead, cq->ring_sz);
	बंद(ring->ring_fd);
पूर्ण
