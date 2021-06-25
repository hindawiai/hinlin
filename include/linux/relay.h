<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/relay.h
 *
 * Copyright (C) 2002, 2003 - Tom Zanussi (zanussi@us.ibm.com), IBM Corp
 * Copyright (C) 1999, 2000, 2001, 2002 - Karim Yaghmour (karim@opersys.com)
 *
 * CONFIG_RELAY definitions and declarations
 */

#अगर_अघोषित _LINUX_RELAY_H
#घोषणा _LINUX_RELAY_H

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/bug.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/kref.h>
#समावेश <linux/percpu.h>

/*
 * Tracks changes to rchan/rchan_buf काष्ठाs
 */
#घोषणा RELAYFS_CHANNEL_VERSION		7

/*
 * Per-cpu relay channel buffer
 */
काष्ठा rchan_buf
अणु
	व्योम *start;			/* start of channel buffer */
	व्योम *data;			/* start of current sub-buffer */
	माप_प्रकार offset;			/* current offset पूर्णांकo sub-buffer */
	माप_प्रकार subbufs_produced;	/* count of sub-buffers produced */
	माप_प्रकार subbufs_consumed;	/* count of sub-buffers consumed */
	काष्ठा rchan *chan;		/* associated channel */
	रुको_queue_head_t पढ़ो_रुको;	/* पढ़ोer रुको queue */
	काष्ठा irq_work wakeup_work;	/* पढ़ोer wakeup */
	काष्ठा dentry *dentry;		/* channel file dentry */
	काष्ठा kref kref;		/* channel buffer refcount */
	काष्ठा page **page_array;	/* array of current buffer pages */
	अचिन्हित पूर्णांक page_count;	/* number of current buffer pages */
	अचिन्हित पूर्णांक finalized;		/* buffer has been finalized */
	माप_प्रकार *padding;		/* padding counts per sub-buffer */
	माप_प्रकार prev_padding;		/* temporary variable */
	माप_प्रकार bytes_consumed;		/* bytes consumed in cur पढ़ो subbuf */
	माप_प्रकार early_bytes;		/* bytes consumed beक्रमe VFS inited */
	अचिन्हित पूर्णांक cpu;		/* this buf's cpu */
पूर्ण ____cacheline_aligned;

/*
 * Relay channel data काष्ठाure
 */
काष्ठा rchan
अणु
	u32 version;			/* the version of this काष्ठा */
	माप_प्रकार subbuf_size;		/* sub-buffer size */
	माप_प्रकार n_subbufs;		/* number of sub-buffers per buffer */
	माप_प्रकार alloc_size;		/* total buffer size allocated */
	स्थिर काष्ठा rchan_callbacks *cb; /* client callbacks */
	काष्ठा kref kref;		/* channel refcount */
	व्योम *निजी_data;		/* क्रम user-defined data */
	माप_प्रकार last_toobig;		/* tried to log event > subbuf size */
	काष्ठा rchan_buf * __percpu *buf; /* per-cpu channel buffers */
	पूर्णांक is_global;			/* One global buffer ? */
	काष्ठा list_head list;		/* क्रम channel list */
	काष्ठा dentry *parent;		/* parent dentry passed to खोलो */
	पूर्णांक has_base_filename;		/* has a filename associated? */
	अक्षर base_filename[NAME_MAX];	/* saved base filename */
पूर्ण;

/*
 * Relay channel client callbacks
 */
काष्ठा rchan_callbacks
अणु
	/*
	 * subbuf_start - called on buffer-चयन to a new sub-buffer
	 * @buf: the channel buffer containing the new sub-buffer
	 * @subbuf: the start of the new sub-buffer
	 * @prev_subbuf: the start of the previous sub-buffer
	 * @prev_padding: unused space at the end of previous sub-buffer
	 *
	 * The client should वापस 1 to जारी logging, 0 to stop
	 * logging.
	 *
	 * This callback is optional.
	 *
	 * NOTE: subbuf_start will also be invoked when the buffer is
	 *       created, so that the first sub-buffer can be initialized
	 *       अगर necessary.  In this हाल, prev_subbuf will be शून्य.
	 *
	 * NOTE: the client can reserve bytes at the beginning of the new
	 *       sub-buffer by calling subbuf_start_reserve() in this callback.
	 */
	पूर्णांक (*subbuf_start) (काष्ठा rchan_buf *buf,
			     व्योम *subbuf,
			     व्योम *prev_subbuf,
			     माप_प्रकार prev_padding);

	/*
	 * create_buf_file - create file to represent a relay channel buffer
	 * @filename: the name of the file to create
	 * @parent: the parent of the file to create
	 * @mode: the mode of the file to create
	 * @buf: the channel buffer
	 * @is_global: outparam - set non-zero अगर the buffer should be global
	 *
	 * Called during relay_खोलो(), once क्रम each per-cpu buffer,
	 * to allow the client to create a file to be used to
	 * represent the corresponding channel buffer.  If the file is
	 * created outside of relay, the parent must also exist in
	 * that fileप्रणाली.
	 *
	 * The callback should वापस the dentry of the file created
	 * to represent the relay buffer.
	 *
	 * Setting the is_global outparam to a non-zero value will
	 * cause relay_खोलो() to create a single global buffer rather
	 * than the शेष set of per-cpu buffers.
	 *
	 * This callback is mandatory.
	 *
	 * See Documentation/fileप्रणालीs/relay.rst क्रम more info.
	 */
	काष्ठा dentry *(*create_buf_file)(स्थिर अक्षर *filename,
					  काष्ठा dentry *parent,
					  umode_t mode,
					  काष्ठा rchan_buf *buf,
					  पूर्णांक *is_global);

	/*
	 * हटाओ_buf_file - हटाओ file representing a relay channel buffer
	 * @dentry: the dentry of the file to हटाओ
	 *
	 * Called during relay_बंद(), once क्रम each per-cpu buffer,
	 * to allow the client to हटाओ a file used to represent a
	 * channel buffer.
	 *
	 * The callback should वापस 0 अगर successful, negative अगर not.
	 *
	 * This callback is mandatory.
	 */
	पूर्णांक (*हटाओ_buf_file)(काष्ठा dentry *dentry);
पूर्ण;

/*
 * CONFIG_RELAY kernel API, kernel/relay.c
 */

काष्ठा rchan *relay_खोलो(स्थिर अक्षर *base_filename,
			 काष्ठा dentry *parent,
			 माप_प्रकार subbuf_size,
			 माप_प्रकार n_subbufs,
			 स्थिर काष्ठा rchan_callbacks *cb,
			 व्योम *निजी_data);
बाह्य पूर्णांक relay_late_setup_files(काष्ठा rchan *chan,
				  स्थिर अक्षर *base_filename,
				  काष्ठा dentry *parent);
बाह्य व्योम relay_बंद(काष्ठा rchan *chan);
बाह्य व्योम relay_flush(काष्ठा rchan *chan);
बाह्य व्योम relay_subbufs_consumed(काष्ठा rchan *chan,
				   अचिन्हित पूर्णांक cpu,
				   माप_प्रकार consumed);
बाह्य व्योम relay_reset(काष्ठा rchan *chan);
बाह्य पूर्णांक relay_buf_full(काष्ठा rchan_buf *buf);

बाह्य माप_प्रकार relay_चयन_subbuf(काष्ठा rchan_buf *buf,
				  माप_प्रकार length);

/**
 *	relay_ग_लिखो - ग_लिखो data पूर्णांकo the channel
 *	@chan: relay channel
 *	@data: data to be written
 *	@length: number of bytes to ग_लिखो
 *
 *	Writes data पूर्णांकo the current cpu's channel buffer.
 *
 *	Protects the buffer by disabling पूर्णांकerrupts.  Use this
 *	अगर you might be logging from पूर्णांकerrupt context.  Try
 *	__relay_ग_लिखो() अगर you know you	won't be logging from
 *	पूर्णांकerrupt context.
 */
अटल अंतरभूत व्योम relay_ग_लिखो(काष्ठा rchan *chan,
			       स्थिर व्योम *data,
			       माप_प्रकार length)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rchan_buf *buf;

	local_irq_save(flags);
	buf = *this_cpu_ptr(chan->buf);
	अगर (unlikely(buf->offset + length > chan->subbuf_size))
		length = relay_चयन_subbuf(buf, length);
	स_नकल(buf->data + buf->offset, data, length);
	buf->offset += length;
	local_irq_restore(flags);
पूर्ण

/**
 *	__relay_ग_लिखो - ग_लिखो data पूर्णांकo the channel
 *	@chan: relay channel
 *	@data: data to be written
 *	@length: number of bytes to ग_लिखो
 *
 *	Writes data पूर्णांकo the current cpu's channel buffer.
 *
 *	Protects the buffer by disabling preemption.  Use
 *	relay_ग_लिखो() अगर you might be logging from पूर्णांकerrupt
 *	context.
 */
अटल अंतरभूत व्योम __relay_ग_लिखो(काष्ठा rchan *chan,
				 स्थिर व्योम *data,
				 माप_प्रकार length)
अणु
	काष्ठा rchan_buf *buf;

	buf = *get_cpu_ptr(chan->buf);
	अगर (unlikely(buf->offset + length > buf->chan->subbuf_size))
		length = relay_चयन_subbuf(buf, length);
	स_नकल(buf->data + buf->offset, data, length);
	buf->offset += length;
	put_cpu_ptr(chan->buf);
पूर्ण

/**
 *	relay_reserve - reserve slot in channel buffer
 *	@chan: relay channel
 *	@length: number of bytes to reserve
 *
 *	Returns poपूर्णांकer to reserved slot, शून्य अगर full.
 *
 *	Reserves a slot in the current cpu's channel buffer.
 *	Does not protect the buffer at all - caller must provide
 *	appropriate synchronization.
 */
अटल अंतरभूत व्योम *relay_reserve(काष्ठा rchan *chan, माप_प्रकार length)
अणु
	व्योम *reserved = शून्य;
	काष्ठा rchan_buf *buf = *get_cpu_ptr(chan->buf);

	अगर (unlikely(buf->offset + length > buf->chan->subbuf_size)) अणु
		length = relay_चयन_subbuf(buf, length);
		अगर (!length)
			जाओ end;
	पूर्ण
	reserved = buf->data + buf->offset;
	buf->offset += length;

end:
	put_cpu_ptr(chan->buf);
	वापस reserved;
पूर्ण

/**
 *	subbuf_start_reserve - reserve bytes at the start of a sub-buffer
 *	@buf: relay channel buffer
 *	@length: number of bytes to reserve
 *
 *	Helper function used to reserve bytes at the beginning of
 *	a sub-buffer in the subbuf_start() callback.
 */
अटल अंतरभूत व्योम subbuf_start_reserve(काष्ठा rchan_buf *buf,
					माप_प्रकार length)
अणु
	BUG_ON(length >= buf->chan->subbuf_size - 1);
	buf->offset = length;
पूर्ण

/*
 * exported relay file operations, kernel/relay.c
 */
बाह्य स्थिर काष्ठा file_operations relay_file_operations;

#अगर_घोषित CONFIG_RELAY
पूर्णांक relay_prepare_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा relay_prepare_cpu     शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_RELAY_H */

