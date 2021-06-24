<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Function declerations and data काष्ठाures related to the splice
 * implementation.
 *
 * Copyright (C) 2007 Jens Axboe <jens.axboe@oracle.com>
 *
 */
#अगर_अघोषित SPLICE_H
#घोषणा SPLICE_H

#समावेश <linux/pipe_fs_i.h>

/*
 * Flags passed in from splice/tee/vmsplice
 */
#घोषणा SPLICE_F_MOVE	(0x01)	/* move pages instead of copying */
#घोषणा SPLICE_F_NONBLOCK (0x02) /* करोn't block on the pipe splicing (but */
				 /* we may still block on the fd we splice */
				 /* from/to, of course */
#घोषणा SPLICE_F_MORE	(0x04)	/* expect more data */
#घोषणा SPLICE_F_GIFT	(0x08)	/* pages passed in are a gअगरt */

#घोषणा SPLICE_F_ALL (SPLICE_F_MOVE|SPLICE_F_NONBLOCK|SPLICE_F_MORE|SPLICE_F_GIFT)

/*
 * Passed to the actors
 */
काष्ठा splice_desc अणु
	माप_प्रकार total_len;		/* reमुख्यing length */
	अचिन्हित पूर्णांक len;		/* current length */
	अचिन्हित पूर्णांक flags;		/* splice flags */
	/*
	 * actor() निजी data
	 */
	जोड़ अणु
		व्योम __user *userptr;	/* memory to ग_लिखो to */
		काष्ठा file *file;	/* file to पढ़ो/ग_लिखो */
		व्योम *data;		/* cookie */
	पूर्ण u;
	loff_t pos;			/* file position */
	loff_t *opos;			/* sendfile: output position */
	माप_प्रकार num_spliced;		/* number of bytes alपढ़ोy spliced */
	bool need_wakeup;		/* need to wake up ग_लिखोr */
पूर्ण;

काष्ठा partial_page अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ निजी;
पूर्ण;

/*
 * Passed to splice_to_pipe
 */
काष्ठा splice_pipe_desc अणु
	काष्ठा page **pages;		/* page map */
	काष्ठा partial_page *partial;	/* pages[] may not be contig */
	पूर्णांक nr_pages;			/* number of populated pages in map */
	अचिन्हित पूर्णांक nr_pages_max;	/* pages[] & partial[] arrays size */
	स्थिर काष्ठा pipe_buf_operations *ops;/* ops associated with output pipe */
	व्योम (*spd_release)(काष्ठा splice_pipe_desc *, अचिन्हित पूर्णांक);
पूर्ण;

प्रकार पूर्णांक (splice_actor)(काष्ठा pipe_inode_info *, काष्ठा pipe_buffer *,
			   काष्ठा splice_desc *);
प्रकार पूर्णांक (splice_direct_actor)(काष्ठा pipe_inode_info *,
				  काष्ठा splice_desc *);

बाह्य sमाप_प्रकार splice_from_pipe(काष्ठा pipe_inode_info *, काष्ठा file *,
				loff_t *, माप_प्रकार, अचिन्हित पूर्णांक,
				splice_actor *);
बाह्य sमाप_प्रकार __splice_from_pipe(काष्ठा pipe_inode_info *,
				  काष्ठा splice_desc *, splice_actor *);
बाह्य sमाप_प्रकार splice_to_pipe(काष्ठा pipe_inode_info *,
			      काष्ठा splice_pipe_desc *);
बाह्य sमाप_प्रकार add_to_pipe(काष्ठा pipe_inode_info *,
			      काष्ठा pipe_buffer *);
बाह्य sमाप_प्रकार splice_direct_to_actor(काष्ठा file *, काष्ठा splice_desc *,
				      splice_direct_actor *);
बाह्य दीर्घ करो_splice(काष्ठा file *in, loff_t *off_in,
		      काष्ठा file *out, loff_t *off_out,
		      माप_प्रकार len, अचिन्हित पूर्णांक flags);

बाह्य दीर्घ करो_tee(काष्ठा file *in, काष्ठा file *out, माप_प्रकार len,
		   अचिन्हित पूर्णांक flags);

/*
 * क्रम dynamic pipe sizing
 */
बाह्य पूर्णांक splice_grow_spd(स्थिर काष्ठा pipe_inode_info *, काष्ठा splice_pipe_desc *);
बाह्य व्योम splice_shrink_spd(काष्ठा splice_pipe_desc *);

बाह्य स्थिर काष्ठा pipe_buf_operations page_cache_pipe_buf_ops;
बाह्य स्थिर काष्ठा pipe_buf_operations शेष_pipe_buf_ops;
#पूर्ण_अगर
