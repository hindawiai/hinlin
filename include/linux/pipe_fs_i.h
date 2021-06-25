<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PIPE_FS_I_H
#घोषणा _LINUX_PIPE_FS_I_H

#घोषणा PIPE_DEF_BUFFERS	16

#घोषणा PIPE_BUF_FLAG_LRU	0x01	/* page is on the LRU */
#घोषणा PIPE_BUF_FLAG_ATOMIC	0x02	/* was atomically mapped */
#घोषणा PIPE_BUF_FLAG_GIFT	0x04	/* page is a gअगरt */
#घोषणा PIPE_BUF_FLAG_PACKET	0x08	/* पढ़ो() as a packet */
#घोषणा PIPE_BUF_FLAG_CAN_MERGE	0x10	/* can merge buffers */
#घोषणा PIPE_BUF_FLAG_WHOLE	0x20	/* पढ़ो() must वापस entire buffer or error */
#अगर_घोषित CONFIG_WATCH_QUEUE
#घोषणा PIPE_BUF_FLAG_LOSS	0x40	/* Message loss happened after this buffer */
#पूर्ण_अगर

/**
 *	काष्ठा pipe_buffer - a linux kernel pipe buffer
 *	@page: the page containing the data क्रम the pipe buffer
 *	@offset: offset of data inside the @page
 *	@len: length of data inside the @page
 *	@ops: operations associated with this buffer. See @pipe_buf_operations.
 *	@flags: pipe buffer flags. See above.
 *	@निजी: निजी data owned by the ops.
 **/
काष्ठा pipe_buffer अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset, len;
	स्थिर काष्ठा pipe_buf_operations *ops;
	अचिन्हित पूर्णांक flags;
	अचिन्हित दीर्घ निजी;
पूर्ण;

/**
 *	काष्ठा pipe_inode_info - a linux kernel pipe
 *	@mutex: mutex protecting the whole thing
 *	@rd_रुको: पढ़ोer रुको poपूर्णांक in हाल of empty pipe
 *	@wr_रुको: ग_लिखोr रुको poपूर्णांक in हाल of full pipe
 *	@head: The poपूर्णांक of buffer production
 *	@tail: The poपूर्णांक of buffer consumption
 *	@note_loss: The next पढ़ो() should insert a data-lost message
 *	@max_usage: The maximum number of slots that may be used in the ring
 *	@ring_size: total number of buffers (should be a घातer of 2)
 *	@nr_accounted: The amount this pipe accounts क्रम in user->pipe_bufs
 *	@पंचांगp_page: cached released page
 *	@पढ़ोers: number of current पढ़ोers of this pipe
 *	@ग_लिखोrs: number of current ग_लिखोrs of this pipe
 *	@files: number of काष्ठा file referring this pipe (रक्षित by ->i_lock)
 *	@r_counter: पढ़ोer counter
 *	@w_counter: ग_लिखोr counter
 *	@fasync_पढ़ोers: पढ़ोer side fasync
 *	@fasync_ग_लिखोrs: ग_लिखोr side fasync
 *	@bufs: the circular array of pipe buffers
 *	@user: the user who created this pipe
 *	@watch_queue: If this pipe is a watch_queue, this is the stuff क्रम that
 **/
काष्ठा pipe_inode_info अणु
	काष्ठा mutex mutex;
	रुको_queue_head_t rd_रुको, wr_रुको;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
	अचिन्हित पूर्णांक max_usage;
	अचिन्हित पूर्णांक ring_size;
#अगर_घोषित CONFIG_WATCH_QUEUE
	bool note_loss;
#पूर्ण_अगर
	अचिन्हित पूर्णांक nr_accounted;
	अचिन्हित पूर्णांक पढ़ोers;
	अचिन्हित पूर्णांक ग_लिखोrs;
	अचिन्हित पूर्णांक files;
	अचिन्हित पूर्णांक r_counter;
	अचिन्हित पूर्णांक w_counter;
	काष्ठा page *पंचांगp_page;
	काष्ठा fasync_काष्ठा *fasync_पढ़ोers;
	काष्ठा fasync_काष्ठा *fasync_ग_लिखोrs;
	काष्ठा pipe_buffer *bufs;
	काष्ठा user_काष्ठा *user;
#अगर_घोषित CONFIG_WATCH_QUEUE
	काष्ठा watch_queue *watch_queue;
#पूर्ण_अगर
पूर्ण;

/*
 * Note on the nesting of these functions:
 *
 * ->confirm()
 *	->try_steal()
 *
 * That is, ->try_steal() must be called on a confirmed buffer.  See below क्रम
 * the meaning of each operation.  Also see the kernelकरोc in fs/pipe.c क्रम the
 * pipe and generic variants of these hooks.
 */
काष्ठा pipe_buf_operations अणु
	/*
	 * ->confirm() verअगरies that the data in the pipe buffer is there
	 * and that the contents are good. If the pages in the pipe beदीर्घ
	 * to a file प्रणाली, we may need to रुको क्रम IO completion in this
	 * hook. Returns 0 क्रम good, or a negative error value in हाल of
	 * error.  If not present all pages are considered good.
	 */
	पूर्णांक (*confirm)(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);

	/*
	 * When the contents of this pipe buffer has been completely
	 * consumed by a पढ़ोer, ->release() is called.
	 */
	व्योम (*release)(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);

	/*
	 * Attempt to take ownership of the pipe buffer and its contents.
	 * ->try_steal() वापसs %true क्रम success, in which हाल the contents
	 * of the pipe (the buf->page) is locked and now completely owned by the
	 * caller. The page may then be transferred to a dअगरferent mapping, the
	 * most often used हाल is insertion पूर्णांकo dअगरferent file address space
	 * cache.
	 */
	bool (*try_steal)(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);

	/*
	 * Get a reference to the pipe buffer.
	 */
	bool (*get)(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);
पूर्ण;

/**
 * pipe_empty - Return true अगर the pipe is empty
 * @head: The pipe ring head poपूर्णांकer
 * @tail: The pipe ring tail poपूर्णांकer
 */
अटल अंतरभूत bool pipe_empty(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail)
अणु
	वापस head == tail;
पूर्ण

/**
 * pipe_occupancy - Return number of slots used in the pipe
 * @head: The pipe ring head poपूर्णांकer
 * @tail: The pipe ring tail poपूर्णांकer
 */
अटल अंतरभूत अचिन्हित पूर्णांक pipe_occupancy(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail)
अणु
	वापस head - tail;
पूर्ण

/**
 * pipe_full - Return true अगर the pipe is full
 * @head: The pipe ring head poपूर्णांकer
 * @tail: The pipe ring tail poपूर्णांकer
 * @limit: The maximum amount of slots available.
 */
अटल अंतरभूत bool pipe_full(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail,
			     अचिन्हित पूर्णांक limit)
अणु
	वापस pipe_occupancy(head, tail) >= limit;
पूर्ण

/**
 * pipe_space_क्रम_user - Return number of slots available to userspace
 * @head: The pipe ring head poपूर्णांकer
 * @tail: The pipe ring tail poपूर्णांकer
 * @pipe: The pipe info काष्ठाure
 */
अटल अंतरभूत अचिन्हित पूर्णांक pipe_space_क्रम_user(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail,
					       काष्ठा pipe_inode_info *pipe)
अणु
	अचिन्हित पूर्णांक p_occupancy, p_space;

	p_occupancy = pipe_occupancy(head, tail);
	अगर (p_occupancy >= pipe->max_usage)
		वापस 0;
	p_space = pipe->ring_size - p_occupancy;
	अगर (p_space > pipe->max_usage)
		p_space = pipe->max_usage;
	वापस p_space;
पूर्ण

/**
 * pipe_buf_get - get a reference to a pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to get a reference to
 *
 * Return: %true अगर the reference was successfully obtained.
 */
अटल अंतरभूत __must_check bool pipe_buf_get(काष्ठा pipe_inode_info *pipe,
				काष्ठा pipe_buffer *buf)
अणु
	वापस buf->ops->get(pipe, buf);
पूर्ण

/**
 * pipe_buf_release - put a reference to a pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to put a reference to
 */
अटल अंतरभूत व्योम pipe_buf_release(काष्ठा pipe_inode_info *pipe,
				    काष्ठा pipe_buffer *buf)
अणु
	स्थिर काष्ठा pipe_buf_operations *ops = buf->ops;

	buf->ops = शून्य;
	ops->release(pipe, buf);
पूर्ण

/**
 * pipe_buf_confirm - verअगरy contents of the pipe buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to confirm
 */
अटल अंतरभूत पूर्णांक pipe_buf_confirm(काष्ठा pipe_inode_info *pipe,
				   काष्ठा pipe_buffer *buf)
अणु
	अगर (!buf->ops->confirm)
		वापस 0;
	वापस buf->ops->confirm(pipe, buf);
पूर्ण

/**
 * pipe_buf_try_steal - attempt to take ownership of a pipe_buffer
 * @pipe:	the pipe that the buffer beदीर्घs to
 * @buf:	the buffer to attempt to steal
 */
अटल अंतरभूत bool pipe_buf_try_steal(काष्ठा pipe_inode_info *pipe,
		काष्ठा pipe_buffer *buf)
अणु
	अगर (!buf->ops->try_steal)
		वापस false;
	वापस buf->ops->try_steal(pipe, buf);
पूर्ण

/* Dअगरfers from PIPE_BUF in that PIPE_SIZE is the length of the actual
   memory allocation, whereas PIPE_BUF makes atomicity guarantees.  */
#घोषणा PIPE_SIZE		PAGE_SIZE

/* Pipe lock and unlock operations */
व्योम pipe_lock(काष्ठा pipe_inode_info *);
व्योम pipe_unlock(काष्ठा pipe_inode_info *);
व्योम pipe_द्विगुन_lock(काष्ठा pipe_inode_info *, काष्ठा pipe_inode_info *);

बाह्य अचिन्हित पूर्णांक pipe_max_size;
बाह्य अचिन्हित दीर्घ pipe_user_pages_hard;
बाह्य अचिन्हित दीर्घ pipe_user_pages_soft;

/* Wait क्रम a pipe to be पढ़ोable/writable जबतक dropping the pipe lock */
व्योम pipe_रुको_पढ़ोable(काष्ठा pipe_inode_info *);
व्योम pipe_रुको_writable(काष्ठा pipe_inode_info *);

काष्ठा pipe_inode_info *alloc_pipe_info(व्योम);
व्योम मुक्त_pipe_info(काष्ठा pipe_inode_info *);

/* Generic pipe buffer ops functions */
bool generic_pipe_buf_get(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);
bool generic_pipe_buf_try_steal(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);
व्योम generic_pipe_buf_release(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *);

बाह्य स्थिर काष्ठा pipe_buf_operations nosteal_pipe_buf_ops;

#अगर_घोषित CONFIG_WATCH_QUEUE
अचिन्हित दीर्घ account_pipe_buffers(काष्ठा user_काष्ठा *user,
				   अचिन्हित दीर्घ old, अचिन्हित दीर्घ new);
bool too_many_pipe_buffers_soft(अचिन्हित दीर्घ user_bufs);
bool too_many_pipe_buffers_hard(अचिन्हित दीर्घ user_bufs);
bool pipe_is_unprivileged_user(व्योम);
#पूर्ण_अगर

/* क्रम F_SETPIPE_SZ and F_GETPIPE_SZ */
#अगर_घोषित CONFIG_WATCH_QUEUE
पूर्णांक pipe_resize_ring(काष्ठा pipe_inode_info *pipe, अचिन्हित पूर्णांक nr_slots);
#पूर्ण_अगर
दीर्घ pipe_fcntl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ arg);
काष्ठा pipe_inode_info *get_pipe_info(काष्ठा file *file, bool क्रम_splice);

पूर्णांक create_pipe_files(काष्ठा file **, पूर्णांक);
अचिन्हित पूर्णांक round_pipe_size(अचिन्हित दीर्घ size);

#पूर्ण_अगर
