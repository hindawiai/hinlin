<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * segbuf.h - NILFS Segment buffer prototypes and definitions
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */
#अगर_अघोषित _NILFS_SEGBUF_H
#घोषणा _NILFS_SEGBUF_H

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/bपन.स>
#समावेश <linux/completion.h>

/**
 * काष्ठा nilfs_segsum_info - On-memory segment summary
 * @flags: Flags
 * @nfinfo: Number of file inक्रमmation काष्ठाures
 * @nblocks: Number of blocks included in the partial segment
 * @nsumblk: Number of summary blocks
 * @sumbytes: Byte count of segment summary
 * @nfileblk: Total number of file blocks
 * @seg_seq: Segment sequence number
 * @cno: Checkpoपूर्णांक number
 * @स_समय: Creation समय
 * @next: Block number of the next full segment
 */
काष्ठा nilfs_segsum_info अणु
	अचिन्हित पूर्णांक		flags;
	अचिन्हित दीर्घ		nfinfo;
	अचिन्हित दीर्घ		nblocks;
	अचिन्हित दीर्घ		nsumblk;
	अचिन्हित दीर्घ		sumbytes;
	अचिन्हित दीर्घ		nfileblk;
	u64			seg_seq;
	__u64			cno;
	समय64_t		स_समय;
	sector_t		next;
पूर्ण;

/**
 * काष्ठा nilfs_segment_buffer - Segment buffer
 * @sb_super: back poपूर्णांकer to a superblock काष्ठा
 * @sb_list: List head to chain this काष्ठाure
 * @sb_sum: On-memory segment summary
 * @sb_segnum: Index number of the full segment
 * @sb_nextnum: Index number of the next full segment
 * @sb_fseg_start: Start block number of the full segment
 * @sb_fseg_end: End block number of the full segment
 * @sb_pseg_start: Disk block number of partial segment
 * @sb_rest_blocks: Number of residual blocks in the current segment
 * @sb_segsum_buffers: List of buffers क्रम segment summaries
 * @sb_payload_buffers: List of buffers क्रम segment payload
 * @sb_super_root: Poपूर्णांकer to buffer storing a super root block (अगर exists)
 * @sb_nbio: Number of flying bio requests
 * @sb_err: I/O error status
 * @sb_bio_event: Completion event of log writing
 */
काष्ठा nilfs_segment_buffer अणु
	काष्ठा super_block     *sb_super;
	काष्ठा list_head	sb_list;

	/* Segment inक्रमmation */
	काष्ठा nilfs_segsum_info sb_sum;
	__u64			sb_segnum;
	__u64			sb_nextnum;
	sector_t		sb_fseg_start, sb_fseg_end;
	sector_t		sb_pseg_start;
	अचिन्हित पूर्णांक		sb_rest_blocks;

	/* Buffers */
	काष्ठा list_head	sb_segsum_buffers;
	काष्ठा list_head	sb_payload_buffers; /* including super root */
	काष्ठा buffer_head     *sb_super_root;

	/* io status */
	पूर्णांक			sb_nbio;
	atomic_t		sb_err;
	काष्ठा completion	sb_bio_event;
पूर्ण;

#घोषणा NILFS_LIST_SEGBUF(head)  \
	list_entry((head), काष्ठा nilfs_segment_buffer, sb_list)
#घोषणा NILFS_NEXT_SEGBUF(segbuf)  NILFS_LIST_SEGBUF((segbuf)->sb_list.next)
#घोषणा NILFS_PREV_SEGBUF(segbuf)  NILFS_LIST_SEGBUF((segbuf)->sb_list.prev)
#घोषणा NILFS_LAST_SEGBUF(head)    NILFS_LIST_SEGBUF((head)->prev)
#घोषणा NILFS_FIRST_SEGBUF(head)   NILFS_LIST_SEGBUF((head)->next)
#घोषणा NILFS_SEGBUF_IS_LAST(segbuf, head)  ((segbuf)->sb_list.next == (head))

#घोषणा nilfs_क्रम_each_segbuf_beक्रमe(s, t, h) \
	क्रम ((s) = NILFS_FIRST_SEGBUF(h); (s) != (t); \
	     (s) = NILFS_NEXT_SEGBUF(s))

#घोषणा NILFS_SEGBUF_FIRST_BH(head)  \
	(list_entry((head)->next, काष्ठा buffer_head, b_assoc_buffers))
#घोषणा NILFS_SEGBUF_NEXT_BH(bh)  \
	(list_entry((bh)->b_assoc_buffers.next, काष्ठा buffer_head, \
		    b_assoc_buffers))
#घोषणा NILFS_SEGBUF_BH_IS_LAST(bh, head)  ((bh)->b_assoc_buffers.next == head)

बाह्य काष्ठा kmem_cache *nilfs_segbuf_cachep;

काष्ठा nilfs_segment_buffer *nilfs_segbuf_new(काष्ठा super_block *);
व्योम nilfs_segbuf_मुक्त(काष्ठा nilfs_segment_buffer *);
व्योम nilfs_segbuf_map(काष्ठा nilfs_segment_buffer *, __u64, अचिन्हित दीर्घ,
		      काष्ठा the_nilfs *);
व्योम nilfs_segbuf_map_cont(काष्ठा nilfs_segment_buffer *segbuf,
			   काष्ठा nilfs_segment_buffer *prev);
व्योम nilfs_segbuf_set_next_segnum(काष्ठा nilfs_segment_buffer *, __u64,
				  काष्ठा the_nilfs *);
पूर्णांक nilfs_segbuf_reset(काष्ठा nilfs_segment_buffer *, अचिन्हित पूर्णांक, समय64_t,
		       __u64);
पूर्णांक nilfs_segbuf_extend_segsum(काष्ठा nilfs_segment_buffer *);
पूर्णांक nilfs_segbuf_extend_payload(काष्ठा nilfs_segment_buffer *,
				काष्ठा buffer_head **);
व्योम nilfs_segbuf_fill_in_segsum(काष्ठा nilfs_segment_buffer *);

अटल अंतरभूत पूर्णांक nilfs_segbuf_simplex(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	अचिन्हित पूर्णांक flags = segbuf->sb_sum.flags;

	वापस (flags & (NILFS_SS_LOGBGN | NILFS_SS_LOGEND)) ==
		(NILFS_SS_LOGBGN | NILFS_SS_LOGEND);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_segbuf_empty(काष्ठा nilfs_segment_buffer *segbuf)
अणु
	वापस segbuf->sb_sum.nblocks == segbuf->sb_sum.nsumblk;
पूर्ण

अटल अंतरभूत व्योम
nilfs_segbuf_add_segsum_buffer(काष्ठा nilfs_segment_buffer *segbuf,
			       काष्ठा buffer_head *bh)
अणु
	list_add_tail(&bh->b_assoc_buffers, &segbuf->sb_segsum_buffers);
	segbuf->sb_sum.nblocks++;
	segbuf->sb_sum.nsumblk++;
पूर्ण

अटल अंतरभूत व्योम
nilfs_segbuf_add_payload_buffer(काष्ठा nilfs_segment_buffer *segbuf,
				काष्ठा buffer_head *bh)
अणु
	list_add_tail(&bh->b_assoc_buffers, &segbuf->sb_payload_buffers);
	segbuf->sb_sum.nblocks++;
पूर्ण

अटल अंतरभूत व्योम
nilfs_segbuf_add_file_buffer(काष्ठा nilfs_segment_buffer *segbuf,
			     काष्ठा buffer_head *bh)
अणु
	get_bh(bh);
	nilfs_segbuf_add_payload_buffer(segbuf, bh);
	segbuf->sb_sum.nfileblk++;
पूर्ण

व्योम nilfs_clear_logs(काष्ठा list_head *logs);
व्योम nilfs_truncate_logs(काष्ठा list_head *logs,
			 काष्ठा nilfs_segment_buffer *last);
पूर्णांक nilfs_ग_लिखो_logs(काष्ठा list_head *logs, काष्ठा the_nilfs *nilfs);
पूर्णांक nilfs_रुको_on_logs(काष्ठा list_head *logs);
व्योम nilfs_add_checksums_on_logs(काष्ठा list_head *logs, u32 seed);

अटल अंतरभूत व्योम nilfs_destroy_logs(काष्ठा list_head *logs)
अणु
	nilfs_truncate_logs(logs, शून्य);
पूर्ण

#पूर्ण_अगर /* _NILFS_SEGBUF_H */
