<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BLKTRACE_H
#घोषणा BLKTRACE_H

#समावेश <linux/blkdev.h>
#समावेश <linux/relay.h>
#समावेश <linux/compat.h>
#समावेश <uapi/linux/blktrace_api.h>
#समावेश <linux/list.h>

#अगर defined(CONFIG_BLK_DEV_IO_TRACE)

#समावेश <linux/sysfs.h>

काष्ठा blk_trace अणु
	पूर्णांक trace_state;
	काष्ठा rchan *rchan;
	अचिन्हित दीर्घ __percpu *sequence;
	अचिन्हित अक्षर __percpu *msg_data;
	u16 act_mask;
	u64 start_lba;
	u64 end_lba;
	u32 pid;
	u32 dev;
	काष्ठा dentry *dir;
	काष्ठा list_head running_list;
	atomic_t dropped;
पूर्ण;

काष्ठा blkcg;

बाह्य पूर्णांक blk_trace_ioctl(काष्ठा block_device *, अचिन्हित, अक्षर __user *);
बाह्य व्योम blk_trace_shutकरोwn(काष्ठा request_queue *);
बाह्य __म_लिखो(3, 4)
व्योम __trace_note_message(काष्ठा blk_trace *, काष्ठा blkcg *blkcg, स्थिर अक्षर *fmt, ...);

/**
 * blk_add_trace_msg - Add a (simple) message to the blktrace stream
 * @q:		queue the io is क्रम
 * @fmt:	क्रमmat to prपूर्णांक message in
 * args...	Variable argument list क्रम क्रमmat
 *
 * Description:
 *     Records a (simple) message onto the blktrace stream.
 *
 *     NOTE: BLK_TN_MAX_MSG अक्षरacters are output at most.
 *     NOTE: Can not use 'static inline' due to presence of var args...
 *
 **/
#घोषणा blk_add_cgroup_trace_msg(q, cg, fmt, ...)			\
	करो अणु								\
		काष्ठा blk_trace *bt;					\
									\
		rcu_पढ़ो_lock();					\
		bt = rcu_dereference((q)->blk_trace);			\
		अगर (unlikely(bt))					\
			__trace_note_message(bt, cg, fmt, ##__VA_ARGS__);\
		rcu_पढ़ो_unlock();					\
	पूर्ण जबतक (0)
#घोषणा blk_add_trace_msg(q, fmt, ...)					\
	blk_add_cgroup_trace_msg(q, शून्य, fmt, ##__VA_ARGS__)
#घोषणा BLK_TN_MAX_MSG		128

अटल अंतरभूत bool blk_trace_note_message_enabled(काष्ठा request_queue *q)
अणु
	काष्ठा blk_trace *bt;
	bool ret;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	ret = bt && (bt->act_mask & BLK_TC_NOTIFY);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

बाह्य व्योम blk_add_driver_data(काष्ठा request *rq, व्योम *data, माप_प्रकार len);
बाह्य पूर्णांक blk_trace_setup(काष्ठा request_queue *q, अक्षर *name, dev_t dev,
			   काष्ठा block_device *bdev,
			   अक्षर __user *arg);
बाह्य पूर्णांक blk_trace_startstop(काष्ठा request_queue *q, पूर्णांक start);
बाह्य पूर्णांक blk_trace_हटाओ(काष्ठा request_queue *q);
बाह्य व्योम blk_trace_हटाओ_sysfs(काष्ठा device *dev);
बाह्य पूर्णांक blk_trace_init_sysfs(काष्ठा device *dev);

बाह्य काष्ठा attribute_group blk_trace_attr_group;

#अन्यथा /* !CONFIG_BLK_DEV_IO_TRACE */
# define blk_trace_ioctl(bdev, cmd, arg)		(-ENOTTY)
# define blk_trace_shutकरोwn(q)				करो अणु पूर्ण जबतक (0)
# define blk_add_driver_data(rq, data, len)		करो अणुपूर्ण जबतक (0)
# define blk_trace_setup(q, name, dev, bdev, arg)	(-ENOTTY)
# define blk_trace_startstop(q, start)			(-ENOTTY)
# define blk_trace_हटाओ(q)				(-ENOTTY)
# define blk_add_trace_msg(q, fmt, ...)			करो अणु पूर्ण जबतक (0)
# define blk_add_cgroup_trace_msg(q, cg, fmt, ...)	करो अणु पूर्ण जबतक (0)
# define blk_trace_हटाओ_sysfs(dev)			करो अणु पूर्ण जबतक (0)
# define blk_trace_note_message_enabled(q)		(false)
अटल अंतरभूत पूर्णांक blk_trace_init_sysfs(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_IO_TRACE */

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_blk_user_trace_setup अणु
	अक्षर name[BLKTRACE_BDEV_SIZE];
	u16 act_mask;
	u32 buf_size;
	u32 buf_nr;
	compat_u64 start_lba;
	compat_u64 end_lba;
	u32 pid;
पूर्ण;
#घोषणा BLKTRACESETUP32 _IOWR(0x12, 115, काष्ठा compat_blk_user_trace_setup)

#पूर्ण_अगर

व्योम blk_fill_rwbs(अक्षर *rwbs, अचिन्हित पूर्णांक op);

अटल अंतरभूत sector_t blk_rq_trace_sector(काष्ठा request *rq)
अणु
	/*
	 * Tracing should ignore starting sector क्रम passthrough requests and
	 * requests where starting sector didn't get set.
	 */
	अगर (blk_rq_is_passthrough(rq) || blk_rq_pos(rq) == (sector_t)-1)
		वापस 0;
	वापस blk_rq_pos(rq);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_trace_nr_sectors(काष्ठा request *rq)
अणु
	वापस blk_rq_is_passthrough(rq) ? 0 : blk_rq_sectors(rq);
पूर्ण

#पूर्ण_अगर
