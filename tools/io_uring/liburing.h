<शैली गुरु>
#अगर_अघोषित LIB_URING_H
#घोषणा LIB_URING_H

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#समावेश <sys/uपन.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश "../../include/uapi/linux/io_uring.h"
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/swab.h>
#समावेश "barrier.h"

/*
 * Library पूर्णांकerface to io_uring
 */
काष्ठा io_uring_sq अणु
	अचिन्हित *khead;
	अचिन्हित *ktail;
	अचिन्हित *kring_mask;
	अचिन्हित *kring_entries;
	अचिन्हित *kflags;
	अचिन्हित *kdropped;
	अचिन्हित *array;
	काष्ठा io_uring_sqe *sqes;

	अचिन्हित sqe_head;
	अचिन्हित sqe_tail;

	माप_प्रकार ring_sz;
पूर्ण;

काष्ठा io_uring_cq अणु
	अचिन्हित *khead;
	अचिन्हित *ktail;
	अचिन्हित *kring_mask;
	अचिन्हित *kring_entries;
	अचिन्हित *koverflow;
	काष्ठा io_uring_cqe *cqes;

	माप_प्रकार ring_sz;
पूर्ण;

काष्ठा io_uring अणु
	काष्ठा io_uring_sq sq;
	काष्ठा io_uring_cq cq;
	पूर्णांक ring_fd;
पूर्ण;

/*
 * System calls
 */
बाह्य पूर्णांक io_uring_setup(अचिन्हित entries, काष्ठा io_uring_params *p);
बाह्य पूर्णांक io_uring_enter(पूर्णांक fd, अचिन्हित to_submit,
	अचिन्हित min_complete, अचिन्हित flags, sigset_t *sig);
बाह्य पूर्णांक io_uring_रेजिस्टर(पूर्णांक fd, अचिन्हित पूर्णांक opcode, व्योम *arg,
	अचिन्हित पूर्णांक nr_args);

/*
 * Library पूर्णांकerface
 */
बाह्य पूर्णांक io_uring_queue_init(अचिन्हित entries, काष्ठा io_uring *ring,
	अचिन्हित flags);
बाह्य पूर्णांक io_uring_queue_mmap(पूर्णांक fd, काष्ठा io_uring_params *p,
	काष्ठा io_uring *ring);
बाह्य व्योम io_uring_queue_निकास(काष्ठा io_uring *ring);
बाह्य पूर्णांक io_uring_peek_cqe(काष्ठा io_uring *ring,
	काष्ठा io_uring_cqe **cqe_ptr);
बाह्य पूर्णांक io_uring_रुको_cqe(काष्ठा io_uring *ring,
	काष्ठा io_uring_cqe **cqe_ptr);
बाह्य पूर्णांक io_uring_submit(काष्ठा io_uring *ring);
बाह्य काष्ठा io_uring_sqe *io_uring_get_sqe(काष्ठा io_uring *ring);

/*
 * Must be called after io_uring_अणुpeek,रुकोपूर्ण_cqe() after the cqe has
 * been processed by the application.
 */
अटल अंतरभूत व्योम io_uring_cqe_seen(काष्ठा io_uring *ring,
				     काष्ठा io_uring_cqe *cqe)
अणु
	अगर (cqe) अणु
		काष्ठा io_uring_cq *cq = &ring->cq;

		(*cq->khead)++;
		/*
		 * Ensure that the kernel sees our new head, the kernel has
		 * the matching पढ़ो barrier.
		 */
		ग_लिखो_barrier();
	पूर्ण
पूर्ण

/*
 * Command prep helpers
 */
अटल अंतरभूत व्योम io_uring_sqe_set_data(काष्ठा io_uring_sqe *sqe, व्योम *data)
अणु
	sqe->user_data = (अचिन्हित दीर्घ) data;
पूर्ण

अटल अंतरभूत व्योम *io_uring_cqe_get_data(काष्ठा io_uring_cqe *cqe)
अणु
	वापस (व्योम *) (uपूर्णांकptr_t) cqe->user_data;
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_rw(पूर्णांक op, काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
				    स्थिर व्योम *addr, अचिन्हित len,
				    off_t offset)
अणु
	स_रखो(sqe, 0, माप(*sqe));
	sqe->opcode = op;
	sqe->fd = fd;
	sqe->off = offset;
	sqe->addr = (अचिन्हित दीर्घ) addr;
	sqe->len = len;
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_पढ़ोv(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
				       स्थिर काष्ठा iovec *iovecs,
				       अचिन्हित nr_vecs, off_t offset)
अणु
	io_uring_prep_rw(IORING_OP_READV, sqe, fd, iovecs, nr_vecs, offset);
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_पढ़ो_fixed(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
					    व्योम *buf, अचिन्हित nbytes,
					    off_t offset)
अणु
	io_uring_prep_rw(IORING_OP_READ_FIXED, sqe, fd, buf, nbytes, offset);
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_ग_लिखोv(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
					स्थिर काष्ठा iovec *iovecs,
					अचिन्हित nr_vecs, off_t offset)
अणु
	io_uring_prep_rw(IORING_OP_WRITEV, sqe, fd, iovecs, nr_vecs, offset);
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_ग_लिखो_fixed(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
					     स्थिर व्योम *buf, अचिन्हित nbytes,
					     off_t offset)
अणु
	io_uring_prep_rw(IORING_OP_WRITE_FIXED, sqe, fd, buf, nbytes, offset);
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_poll_add(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
					  अचिन्हित poll_mask)
अणु
	स_रखो(sqe, 0, माप(*sqe));
	sqe->opcode = IORING_OP_POLL_ADD;
	sqe->fd = fd;
#अगर __BYTE_ORDER == __BIG_ENDIAN
	poll_mask = __swahw32(poll_mask);
#पूर्ण_अगर
	sqe->poll_events = poll_mask;
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_poll_हटाओ(काष्ठा io_uring_sqe *sqe,
					     व्योम *user_data)
अणु
	स_रखो(sqe, 0, माप(*sqe));
	sqe->opcode = IORING_OP_POLL_REMOVE;
	sqe->addr = (अचिन्हित दीर्घ) user_data;
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_fsync(काष्ठा io_uring_sqe *sqe, पूर्णांक fd,
				       अचिन्हित fsync_flags)
अणु
	स_रखो(sqe, 0, माप(*sqe));
	sqe->opcode = IORING_OP_FSYNC;
	sqe->fd = fd;
	sqe->fsync_flags = fsync_flags;
पूर्ण

अटल अंतरभूत व्योम io_uring_prep_nop(काष्ठा io_uring_sqe *sqe)
अणु
	स_रखो(sqe, 0, माप(*sqe));
	sqe->opcode = IORING_OP_NOP;
पूर्ण

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
