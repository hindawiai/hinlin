<शैली गुरु>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश "liburing.h"
#समावेश "barrier.h"

अटल पूर्णांक __io_uring_get_cqe(काष्ठा io_uring *ring,
			      काष्ठा io_uring_cqe **cqe_ptr, पूर्णांक रुको)
अणु
	काष्ठा io_uring_cq *cq = &ring->cq;
	स्थिर अचिन्हित mask = *cq->kring_mask;
	अचिन्हित head;
	पूर्णांक ret;

	*cqe_ptr = शून्य;
	head = *cq->khead;
	करो अणु
		/*
		 * It's necessary to use a पढ़ो_barrier() beक्रमe पढ़ोing
		 * the CQ tail, since the kernel updates it locklessly. The
		 * kernel has the matching store barrier क्रम the update. The
		 * kernel also ensures that previous stores to CQEs are ordered
		 * with the tail update.
		 */
		पढ़ो_barrier();
		अगर (head != *cq->ktail) अणु
			*cqe_ptr = &cq->cqes[head & mask];
			अवरोध;
		पूर्ण
		अगर (!रुको)
			अवरोध;
		ret = io_uring_enter(ring->ring_fd, 0, 1,
					IORING_ENTER_GETEVENTS, शून्य);
		अगर (ret < 0)
			वापस -त्रुटि_सं;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

/*
 * Return an IO completion, अगर one is पढ़ोily available. Returns 0 with
 * cqe_ptr filled in on success, -त्रुटि_सं on failure.
 */
पूर्णांक io_uring_peek_cqe(काष्ठा io_uring *ring, काष्ठा io_uring_cqe **cqe_ptr)
अणु
	वापस __io_uring_get_cqe(ring, cqe_ptr, 0);
पूर्ण

/*
 * Return an IO completion, रुकोing क्रम it अगर necessary. Returns 0 with
 * cqe_ptr filled in on success, -त्रुटि_सं on failure.
 */
पूर्णांक io_uring_रुको_cqe(काष्ठा io_uring *ring, काष्ठा io_uring_cqe **cqe_ptr)
अणु
	वापस __io_uring_get_cqe(ring, cqe_ptr, 1);
पूर्ण

/*
 * Submit sqes acquired from io_uring_get_sqe() to the kernel.
 *
 * Returns number of sqes submitted
 */
पूर्णांक io_uring_submit(काष्ठा io_uring *ring)
अणु
	काष्ठा io_uring_sq *sq = &ring->sq;
	स्थिर अचिन्हित mask = *sq->kring_mask;
	अचिन्हित ktail, ktail_next, submitted, to_submit;
	पूर्णांक ret;

	/*
	 * If we have pending IO in the kring, submit it first. We need a
	 * पढ़ो barrier here to match the kernels store barrier when updating
	 * the SQ head.
	 */
	पढ़ो_barrier();
	अगर (*sq->khead != *sq->ktail) अणु
		submitted = *sq->kring_entries;
		जाओ submit;
	पूर्ण

	अगर (sq->sqe_head == sq->sqe_tail)
		वापस 0;

	/*
	 * Fill in sqes that we have queued up, adding them to the kernel ring
	 */
	submitted = 0;
	ktail = ktail_next = *sq->ktail;
	to_submit = sq->sqe_tail - sq->sqe_head;
	जबतक (to_submit--) अणु
		ktail_next++;
		पढ़ो_barrier();

		sq->array[ktail & mask] = sq->sqe_head & mask;
		ktail = ktail_next;

		sq->sqe_head++;
		submitted++;
	पूर्ण

	अगर (!submitted)
		वापस 0;

	अगर (*sq->ktail != ktail) अणु
		/*
		 * First ग_लिखो barrier ensures that the SQE stores are updated
		 * with the tail update. This is needed so that the kernel
		 * will never see a tail update without the preceeding sQE
		 * stores being करोne.
		 */
		ग_लिखो_barrier();
		*sq->ktail = ktail;
		/*
		 * The kernel has the matching पढ़ो barrier क्रम पढ़ोing the
		 * SQ tail.
		 */
		ग_लिखो_barrier();
	पूर्ण

submit:
	ret = io_uring_enter(ring->ring_fd, submitted, 0,
				IORING_ENTER_GETEVENTS, शून्य);
	अगर (ret < 0)
		वापस -त्रुटि_सं;

	वापस ret;
पूर्ण

/*
 * Return an sqe to fill. Application must later call io_uring_submit()
 * when it's पढ़ोy to tell the kernel about it. The caller may call this
 * function multiple बार beक्रमe calling io_uring_submit().
 *
 * Returns a vacant sqe, or शून्य अगर we're full.
 */
काष्ठा io_uring_sqe *io_uring_get_sqe(काष्ठा io_uring *ring)
अणु
	काष्ठा io_uring_sq *sq = &ring->sq;
	अचिन्हित next = sq->sqe_tail + 1;
	काष्ठा io_uring_sqe *sqe;

	/*
	 * All sqes are used
	 */
	अगर (next - sq->sqe_head > *sq->kring_entries)
		वापस शून्य;

	sqe = &sq->sqes[sq->sqe_tail & *sq->kring_mask];
	sq->sqe_tail = next;
	वापस sqe;
पूर्ण
