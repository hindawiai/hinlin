<शैली गुरु>
/*
 * POSIX message queues fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 2003,2004  Krzysztof Benedyczak    (golbi@mat.uni.torun.pl)
 *                          Michal Wronski          (michal.wronski@gmail.com)
 *
 * Spinlocks:               Mohamed Abbas           (abbas.mohamed@पूर्णांकel.com)
 * Lockless receive & send, fd based notअगरy:
 *			    Manfred Spraul	    (manfred@colorfullअगरe.com)
 *
 * Audit:                   George Wilson           (ltcgcw@us.ibm.com)
 *
 * This file is released under the GPL.
 */

#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/namei.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/poll.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/msg.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netlink.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/audit.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mutex.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/pid.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/user.h>

#समावेश <net/sock.h>
#समावेश "util.h"

काष्ठा mqueue_fs_context अणु
	काष्ठा ipc_namespace	*ipc_ns;
पूर्ण;

#घोषणा MQUEUE_MAGIC	0x19800202
#घोषणा सूचीENT_SIZE	20
#घोषणा खाताNT_SIZE	80

#घोषणा SEND		0
#घोषणा RECV		1

#घोषणा STATE_NONE	0
#घोषणा STATE_READY	1

काष्ठा posix_msg_tree_node अणु
	काष्ठा rb_node		rb_node;
	काष्ठा list_head	msg_list;
	पूर्णांक			priority;
पूर्ण;

/*
 * Locking:
 *
 * Accesses to a message queue are synchronized by acquiring info->lock.
 *
 * There are two notable exceptions:
 * - The actual wakeup of a sleeping task is perक्रमmed using the wake_q
 *   framework. info->lock is alपढ़ोy released when wake_up_q is called.
 * - The निकास codepaths after sleeping check ext_रुको_queue->state without
 *   any locks. If it is STATE_READY, then the syscall is completed without
 *   acquiring info->lock.
 *
 * MQ_BARRIER:
 * To achieve proper release/acquire memory barrier pairing, the state is set to
 * STATE_READY with smp_store_release(), and it is पढ़ो with READ_ONCE followed
 * by smp_acquire__after_ctrl_dep(). In addition, wake_q_add_safe() is used.
 *
 * This prevents the following races:
 *
 * 1) With the simple wake_q_add(), the task could be gone alपढ़ोy beक्रमe
 *    the increase of the reference happens
 * Thपढ़ो A
 *				Thपढ़ो B
 * WRITE_ONCE(रुको.state, STATE_NONE);
 * schedule_hrसमयout()
 *				wake_q_add(A)
 *				अगर (cmpxchg()) // success
 *				   ->state = STATE_READY (reordered)
 * <समयout वापसs>
 * अगर (रुको.state == STATE_READY) वापस;
 * sysret to user space
 * sys_निकास()
 *				get_task_काष्ठा() // UaF
 *
 * Solution: Use wake_q_add_safe() and perक्रमm the get_task_काष्ठा() beक्रमe
 * the smp_store_release() that करोes ->state = STATE_READY.
 *
 * 2) Without proper _release/_acquire barriers, the woken up task
 *    could पढ़ो stale data
 *
 * Thपढ़ो A
 *				Thपढ़ो B
 * करो_mq_समयdreceive
 * WRITE_ONCE(रुको.state, STATE_NONE);
 * schedule_hrसमयout()
 *				state = STATE_READY;
 * <समयout वापसs>
 * अगर (रुको.state == STATE_READY) वापस;
 * msg_ptr = रुको.msg;		// Access to stale data!
 *				receiver->msg = message; (reordered)
 *
 * Solution: use _release and _acquire barriers.
 *
 * 3) There is पूर्णांकentionally no barrier when setting current->state
 *    to TASK_INTERRUPTIBLE: spin_unlock(&info->lock) provides the
 *    release memory barrier, and the wakeup is triggered when holding
 *    info->lock, i.e. spin_lock(&info->lock) provided a pairing
 *    acquire memory barrier.
 */

काष्ठा ext_रुको_queue अणु		/* queue of sleeping tasks */
	काष्ठा task_काष्ठा *task;
	काष्ठा list_head list;
	काष्ठा msg_msg *msg;	/* ptr of loaded message */
	पूर्णांक state;		/* one of STATE_* values */
पूर्ण;

काष्ठा mqueue_inode_info अणु
	spinlock_t lock;
	काष्ठा inode vfs_inode;
	रुको_queue_head_t रुको_q;

	काष्ठा rb_root msg_tree;
	काष्ठा rb_node *msg_tree_righपंचांगost;
	काष्ठा posix_msg_tree_node *node_cache;
	काष्ठा mq_attr attr;

	काष्ठा sigevent notअगरy;
	काष्ठा pid *notअगरy_owner;
	u32 notअगरy_self_exec_id;
	काष्ठा user_namespace *notअगरy_user_ns;
	काष्ठा user_काष्ठा *user;	/* user who created, क्रम accounting */
	काष्ठा sock *notअगरy_sock;
	काष्ठा sk_buff *notअगरy_cookie;

	/* क्रम tasks रुकोing क्रम मुक्त space and messages, respectively */
	काष्ठा ext_रुको_queue e_रुको_q[2];

	अचिन्हित दीर्घ qsize; /* size of queue in memory (sum of all msgs) */
पूर्ण;

अटल काष्ठा file_प्रणाली_type mqueue_fs_type;
अटल स्थिर काष्ठा inode_operations mqueue_dir_inode_operations;
अटल स्थिर काष्ठा file_operations mqueue_file_operations;
अटल स्थिर काष्ठा super_operations mqueue_super_ops;
अटल स्थिर काष्ठा fs_context_operations mqueue_fs_context_ops;
अटल व्योम हटाओ_notअगरication(काष्ठा mqueue_inode_info *info);

अटल काष्ठा kmem_cache *mqueue_inode_cachep;

अटल काष्ठा ctl_table_header *mq_sysctl_table;

अटल अंतरभूत काष्ठा mqueue_inode_info *MQUEUE_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा mqueue_inode_info, vfs_inode);
पूर्ण

/*
 * This routine should be called with the mq_lock held.
 */
अटल अंतरभूत काष्ठा ipc_namespace *__get_ns_from_inode(काष्ठा inode *inode)
अणु
	वापस get_ipc_ns(inode->i_sb->s_fs_info);
पूर्ण

अटल काष्ठा ipc_namespace *get_ns_from_inode(काष्ठा inode *inode)
अणु
	काष्ठा ipc_namespace *ns;

	spin_lock(&mq_lock);
	ns = __get_ns_from_inode(inode);
	spin_unlock(&mq_lock);
	वापस ns;
पूर्ण

/* Auxiliary functions to manipulate messages' list */
अटल पूर्णांक msg_insert(काष्ठा msg_msg *msg, काष्ठा mqueue_inode_info *info)
अणु
	काष्ठा rb_node **p, *parent = शून्य;
	काष्ठा posix_msg_tree_node *leaf;
	bool righपंचांगost = true;

	p = &info->msg_tree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		leaf = rb_entry(parent, काष्ठा posix_msg_tree_node, rb_node);

		अगर (likely(leaf->priority == msg->m_type))
			जाओ insert_msg;
		अन्यथा अगर (msg->m_type < leaf->priority) अणु
			p = &(*p)->rb_left;
			righपंचांगost = false;
		पूर्ण अन्यथा
			p = &(*p)->rb_right;
	पूर्ण
	अगर (info->node_cache) अणु
		leaf = info->node_cache;
		info->node_cache = शून्य;
	पूर्ण अन्यथा अणु
		leaf = kदो_स्मृति(माप(*leaf), GFP_ATOMIC);
		अगर (!leaf)
			वापस -ENOMEM;
		INIT_LIST_HEAD(&leaf->msg_list);
	पूर्ण
	leaf->priority = msg->m_type;

	अगर (righपंचांगost)
		info->msg_tree_righपंचांगost = &leaf->rb_node;

	rb_link_node(&leaf->rb_node, parent, p);
	rb_insert_color(&leaf->rb_node, &info->msg_tree);
insert_msg:
	info->attr.mq_curmsgs++;
	info->qsize += msg->m_ts;
	list_add_tail(&msg->m_list, &leaf->msg_list);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम msg_tree_erase(काष्ठा posix_msg_tree_node *leaf,
				  काष्ठा mqueue_inode_info *info)
अणु
	काष्ठा rb_node *node = &leaf->rb_node;

	अगर (info->msg_tree_righपंचांगost == node)
		info->msg_tree_righपंचांगost = rb_prev(node);

	rb_erase(node, &info->msg_tree);
	अगर (info->node_cache)
		kमुक्त(leaf);
	अन्यथा
		info->node_cache = leaf;
पूर्ण

अटल अंतरभूत काष्ठा msg_msg *msg_get(काष्ठा mqueue_inode_info *info)
अणु
	काष्ठा rb_node *parent = शून्य;
	काष्ठा posix_msg_tree_node *leaf;
	काष्ठा msg_msg *msg;

try_again:
	/*
	 * During insert, low priorities go to the left and high to the
	 * right.  On receive, we want the highest priorities first, so
	 * walk all the way to the right.
	 */
	parent = info->msg_tree_righपंचांगost;
	अगर (!parent) अणु
		अगर (info->attr.mq_curmsgs) अणु
			pr_warn_once("Inconsistency in POSIX message queue, "
				     "no tree element, but supposedly messages "
				     "should exist!\n");
			info->attr.mq_curmsgs = 0;
		पूर्ण
		वापस शून्य;
	पूर्ण
	leaf = rb_entry(parent, काष्ठा posix_msg_tree_node, rb_node);
	अगर (unlikely(list_empty(&leaf->msg_list))) अणु
		pr_warn_once("Inconsistency in POSIX message queue, "
			     "empty leaf node but we haven't implemented "
			     "lazy leaf delete!\n");
		msg_tree_erase(leaf, info);
		जाओ try_again;
	पूर्ण अन्यथा अणु
		msg = list_first_entry(&leaf->msg_list,
				       काष्ठा msg_msg, m_list);
		list_del(&msg->m_list);
		अगर (list_empty(&leaf->msg_list)) अणु
			msg_tree_erase(leaf, info);
		पूर्ण
	पूर्ण
	info->attr.mq_curmsgs--;
	info->qsize -= msg->m_ts;
	वापस msg;
पूर्ण

अटल काष्ठा inode *mqueue_get_inode(काष्ठा super_block *sb,
		काष्ठा ipc_namespace *ipc_ns, umode_t mode,
		काष्ठा mq_attr *attr)
अणु
	काष्ठा user_काष्ठा *u = current_user();
	काष्ठा inode *inode;
	पूर्णांक ret = -ENOMEM;

	inode = new_inode(sb);
	अगर (!inode)
		जाओ err;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_mसमय = inode->i_स_समय = inode->i_aसमय = current_समय(inode);

	अगर (S_ISREG(mode)) अणु
		काष्ठा mqueue_inode_info *info;
		अचिन्हित दीर्घ mq_bytes, mq_treesize;

		inode->i_fop = &mqueue_file_operations;
		inode->i_size = खाताNT_SIZE;
		/* mqueue specअगरic info */
		info = MQUEUE_I(inode);
		spin_lock_init(&info->lock);
		init_रुकोqueue_head(&info->रुको_q);
		INIT_LIST_HEAD(&info->e_रुको_q[0].list);
		INIT_LIST_HEAD(&info->e_रुको_q[1].list);
		info->notअगरy_owner = शून्य;
		info->notअगरy_user_ns = शून्य;
		info->qsize = 0;
		info->user = शून्य;	/* set when all is ok */
		info->msg_tree = RB_ROOT;
		info->msg_tree_righपंचांगost = शून्य;
		info->node_cache = शून्य;
		स_रखो(&info->attr, 0, माप(info->attr));
		info->attr.mq_maxmsg = min(ipc_ns->mq_msg_max,
					   ipc_ns->mq_msg_शेष);
		info->attr.mq_msgsize = min(ipc_ns->mq_msgsize_max,
					    ipc_ns->mq_msgsize_शेष);
		अगर (attr) अणु
			info->attr.mq_maxmsg = attr->mq_maxmsg;
			info->attr.mq_msgsize = attr->mq_msgsize;
		पूर्ण
		/*
		 * We used to allocate a अटल array of poपूर्णांकers and account
		 * the size of that array as well as one msg_msg काष्ठा per
		 * possible message पूर्णांकo the queue size. That's no दीर्घer
		 * accurate as the queue is now an rbtree and will grow and
		 * shrink depending on usage patterns.  We can, however, still
		 * account one msg_msg काष्ठा per message, but the nodes are
		 * allocated depending on priority usage, and most programs
		 * only use one, or a handful, of priorities.  However, since
		 * this is pinned memory, we need to assume worst हाल, so
		 * that means the min(mq_maxmsg, max_priorities) * काष्ठा
		 * posix_msg_tree_node.
		 */

		ret = -EINVAL;
		अगर (info->attr.mq_maxmsg <= 0 || info->attr.mq_msgsize <= 0)
			जाओ out_inode;
		अगर (capable(CAP_SYS_RESOURCE)) अणु
			अगर (info->attr.mq_maxmsg > HARD_MSGMAX ||
			    info->attr.mq_msgsize > HARD_MSGSIZEMAX)
				जाओ out_inode;
		पूर्ण अन्यथा अणु
			अगर (info->attr.mq_maxmsg > ipc_ns->mq_msg_max ||
					info->attr.mq_msgsize > ipc_ns->mq_msgsize_max)
				जाओ out_inode;
		पूर्ण
		ret = -EOVERFLOW;
		/* check क्रम overflow */
		अगर (info->attr.mq_msgsize > अच_दीर्घ_उच्च/info->attr.mq_maxmsg)
			जाओ out_inode;
		mq_treesize = info->attr.mq_maxmsg * माप(काष्ठा msg_msg) +
			min_t(अचिन्हित पूर्णांक, info->attr.mq_maxmsg, MQ_PRIO_MAX) *
			माप(काष्ठा posix_msg_tree_node);
		mq_bytes = info->attr.mq_maxmsg * info->attr.mq_msgsize;
		अगर (mq_bytes + mq_treesize < mq_bytes)
			जाओ out_inode;
		mq_bytes += mq_treesize;
		spin_lock(&mq_lock);
		अगर (u->mq_bytes + mq_bytes < u->mq_bytes ||
		    u->mq_bytes + mq_bytes > rlimit(RLIMIT_MSGQUEUE)) अणु
			spin_unlock(&mq_lock);
			/* mqueue_evict_inode() releases info->messages */
			ret = -EMखाता;
			जाओ out_inode;
		पूर्ण
		u->mq_bytes += mq_bytes;
		spin_unlock(&mq_lock);

		/* all is ok */
		info->user = get_uid(u);
	पूर्ण अन्यथा अगर (S_ISसूची(mode)) अणु
		inc_nlink(inode);
		/* Some things misbehave अगर size == 0 on a directory */
		inode->i_size = 2 * सूचीENT_SIZE;
		inode->i_op = &mqueue_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
	पूर्ण

	वापस inode;
out_inode:
	iput(inode);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक mqueue_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *inode;
	काष्ठा ipc_namespace *ns = sb->s_fs_info;

	sb->s_अगरlags |= SB_I_NOEXEC | SB_I_NODEV;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = MQUEUE_MAGIC;
	sb->s_op = &mqueue_super_ops;

	inode = mqueue_get_inode(sb, ns, S_IFसूची | S_ISVTX | S_IRWXUGO, शून्य);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक mqueue_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा mqueue_fs_context *ctx = fc->fs_निजी;

	वापस get_tree_keyed(fc, mqueue_fill_super, ctx->ipc_ns);
पूर्ण

अटल व्योम mqueue_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा mqueue_fs_context *ctx = fc->fs_निजी;

	put_ipc_ns(ctx->ipc_ns);
	kमुक्त(ctx);
पूर्ण

अटल पूर्णांक mqueue_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा mqueue_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा mqueue_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->ipc_ns = get_ipc_ns(current->nsproxy->ipc_ns);
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ipc_ns->user_ns);
	fc->fs_निजी = ctx;
	fc->ops = &mqueue_fs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा vfsmount *mq_create_mount(काष्ठा ipc_namespace *ns)
अणु
	काष्ठा mqueue_fs_context *ctx;
	काष्ठा fs_context *fc;
	काष्ठा vfsmount *mnt;

	fc = fs_context_क्रम_mount(&mqueue_fs_type, SB_KERNMOUNT);
	अगर (IS_ERR(fc))
		वापस ERR_CAST(fc);

	ctx = fc->fs_निजी;
	put_ipc_ns(ctx->ipc_ns);
	ctx->ipc_ns = get_ipc_ns(ns);
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ipc_ns->user_ns);

	mnt = fc_mount(fc);
	put_fs_context(fc);
	वापस mnt;
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा mqueue_inode_info *p = (काष्ठा mqueue_inode_info *) foo;

	inode_init_once(&p->vfs_inode);
पूर्ण

अटल काष्ठा inode *mqueue_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा mqueue_inode_info *ei;

	ei = kmem_cache_alloc(mqueue_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम mqueue_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(mqueue_inode_cachep, MQUEUE_I(inode));
पूर्ण

अटल व्योम mqueue_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा mqueue_inode_info *info;
	काष्ठा user_काष्ठा *user;
	काष्ठा ipc_namespace *ipc_ns;
	काष्ठा msg_msg *msg, *nmsg;
	LIST_HEAD(पंचांगp_msg);

	clear_inode(inode);

	अगर (S_ISसूची(inode->i_mode))
		वापस;

	ipc_ns = get_ns_from_inode(inode);
	info = MQUEUE_I(inode);
	spin_lock(&info->lock);
	जबतक ((msg = msg_get(info)) != शून्य)
		list_add_tail(&msg->m_list, &पंचांगp_msg);
	kमुक्त(info->node_cache);
	spin_unlock(&info->lock);

	list_क्रम_each_entry_safe(msg, nmsg, &पंचांगp_msg, m_list) अणु
		list_del(&msg->m_list);
		मुक्त_msg(msg);
	पूर्ण

	user = info->user;
	अगर (user) अणु
		अचिन्हित दीर्घ mq_bytes, mq_treesize;

		/* Total amount of bytes accounted क्रम the mqueue */
		mq_treesize = info->attr.mq_maxmsg * माप(काष्ठा msg_msg) +
			min_t(अचिन्हित पूर्णांक, info->attr.mq_maxmsg, MQ_PRIO_MAX) *
			माप(काष्ठा posix_msg_tree_node);

		mq_bytes = mq_treesize + (info->attr.mq_maxmsg *
					  info->attr.mq_msgsize);

		spin_lock(&mq_lock);
		user->mq_bytes -= mq_bytes;
		/*
		 * get_ns_from_inode() ensures that the
		 * (ipc_ns = sb->s_fs_info) is either a valid ipc_ns
		 * to which we now hold a reference, or it is शून्य.
		 * We can't put it here under mq_lock, though.
		 */
		अगर (ipc_ns)
			ipc_ns->mq_queues_count--;
		spin_unlock(&mq_lock);
		मुक्त_uid(user);
	पूर्ण
	अगर (ipc_ns)
		put_ipc_ns(ipc_ns);
पूर्ण

अटल पूर्णांक mqueue_create_attr(काष्ठा dentry *dentry, umode_t mode, व्योम *arg)
अणु
	काष्ठा inode *dir = dentry->d_parent->d_inode;
	काष्ठा inode *inode;
	काष्ठा mq_attr *attr = arg;
	पूर्णांक error;
	काष्ठा ipc_namespace *ipc_ns;

	spin_lock(&mq_lock);
	ipc_ns = __get_ns_from_inode(dir);
	अगर (!ipc_ns) अणु
		error = -EACCES;
		जाओ out_unlock;
	पूर्ण

	अगर (ipc_ns->mq_queues_count >= ipc_ns->mq_queues_max &&
	    !capable(CAP_SYS_RESOURCE)) अणु
		error = -ENOSPC;
		जाओ out_unlock;
	पूर्ण
	ipc_ns->mq_queues_count++;
	spin_unlock(&mq_lock);

	inode = mqueue_get_inode(dir->i_sb, ipc_ns, mode, attr);
	अगर (IS_ERR(inode)) अणु
		error = PTR_ERR(inode);
		spin_lock(&mq_lock);
		ipc_ns->mq_queues_count--;
		जाओ out_unlock;
	पूर्ण

	put_ipc_ns(ipc_ns);
	dir->i_size += सूचीENT_SIZE;
	dir->i_स_समय = dir->i_mसमय = dir->i_aसमय = current_समय(dir);

	d_instantiate(dentry, inode);
	dget(dentry);
	वापस 0;
out_unlock:
	spin_unlock(&mq_lock);
	अगर (ipc_ns)
		put_ipc_ns(ipc_ns);
	वापस error;
पूर्ण

अटल पूर्णांक mqueue_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस mqueue_create_attr(dentry, mode, शून्य);
पूर्ण

अटल पूर्णांक mqueue_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	dir->i_स_समय = dir->i_mसमय = dir->i_aसमय = current_समय(dir);
	dir->i_size -= सूचीENT_SIZE;
	drop_nlink(inode);
	dput(dentry);
	वापस 0;
पूर्ण

/*
*	This is routine क्रम प्रणाली पढ़ो from queue file.
*	To aव्योम mess with करोing here some sort of mq_receive we allow
*	to पढ़ो only queue size & notअगरication info (the only values
*	that are पूर्णांकeresting from user poपूर्णांक of view and aren't accessible
*	through std routines)
*/
अटल sमाप_प्रकार mqueue_पढ़ो_file(काष्ठा file *filp, अक्षर __user *u_data,
				माप_प्रकार count, loff_t *off)
अणु
	काष्ठा mqueue_inode_info *info = MQUEUE_I(file_inode(filp));
	अक्षर buffer[खाताNT_SIZE];
	sमाप_प्रकार ret;

	spin_lock(&info->lock);
	snम_लिखो(buffer, माप(buffer),
			"QSIZE:%-10lu NOTIFY:%-5d SIGNO:%-5d NOTIFY_PID:%-6d\n",
			info->qsize,
			info->notअगरy_owner ? info->notअगरy.sigev_notअगरy : 0,
			(info->notअगरy_owner &&
			 info->notअगरy.sigev_notअगरy == SIGEV_SIGNAL) ?
				info->notअगरy.sigev_signo : 0,
			pid_vnr(info->notअगरy_owner));
	spin_unlock(&info->lock);
	buffer[माप(buffer)-1] = '\0';

	ret = simple_पढ़ो_from_buffer(u_data, count, off, buffer,
				म_माप(buffer));
	अगर (ret <= 0)
		वापस ret;

	file_inode(filp)->i_aसमय = file_inode(filp)->i_स_समय = current_समय(file_inode(filp));
	वापस ret;
पूर्ण

अटल पूर्णांक mqueue_flush_file(काष्ठा file *filp, fl_owner_t id)
अणु
	काष्ठा mqueue_inode_info *info = MQUEUE_I(file_inode(filp));

	spin_lock(&info->lock);
	अगर (task_tgid(current) == info->notअगरy_owner)
		हटाओ_notअगरication(info);

	spin_unlock(&info->lock);
	वापस 0;
पूर्ण

अटल __poll_t mqueue_poll_file(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *poll_tab)
अणु
	काष्ठा mqueue_inode_info *info = MQUEUE_I(file_inode(filp));
	__poll_t retval = 0;

	poll_रुको(filp, &info->रुको_q, poll_tab);

	spin_lock(&info->lock);
	अगर (info->attr.mq_curmsgs)
		retval = EPOLLIN | EPOLLRDNORM;

	अगर (info->attr.mq_curmsgs < info->attr.mq_maxmsg)
		retval |= EPOLLOUT | EPOLLWRNORM;
	spin_unlock(&info->lock);

	वापस retval;
पूर्ण

/* Adds current to info->e_रुको_q[sr] beक्रमe element with smaller prio */
अटल व्योम wq_add(काष्ठा mqueue_inode_info *info, पूर्णांक sr,
			काष्ठा ext_रुको_queue *ewp)
अणु
	काष्ठा ext_रुको_queue *walk;

	list_क्रम_each_entry(walk, &info->e_रुको_q[sr].list, list) अणु
		अगर (walk->task->prio <= current->prio) अणु
			list_add_tail(&ewp->list, &walk->list);
			वापस;
		पूर्ण
	पूर्ण
	list_add_tail(&ewp->list, &info->e_रुको_q[sr].list);
पूर्ण

/*
 * Puts current task to sleep. Caller must hold queue lock. After वापस
 * lock isn't held.
 * sr: SEND or RECV
 */
अटल पूर्णांक wq_sleep(काष्ठा mqueue_inode_info *info, पूर्णांक sr,
		    kसमय_प्रकार *समयout, काष्ठा ext_रुको_queue *ewp)
	__releases(&info->lock)
अणु
	पूर्णांक retval;
	चिन्हित दीर्घ समय;

	wq_add(info, sr, ewp);

	क्रम (;;) अणु
		/* memory barrier not required, we hold info->lock */
		__set_current_state(TASK_INTERRUPTIBLE);

		spin_unlock(&info->lock);
		समय = schedule_hrसमयout_range_घड़ी(समयout, 0,
			HRTIMER_MODE_ABS, CLOCK_REALTIME);

		अगर (READ_ONCE(ewp->state) == STATE_READY) अणु
			/* see MQ_BARRIER क्रम purpose/pairing */
			smp_acquire__after_ctrl_dep();
			retval = 0;
			जाओ out;
		पूर्ण
		spin_lock(&info->lock);

		/* we hold info->lock, so no memory barrier required */
		अगर (READ_ONCE(ewp->state) == STATE_READY) अणु
			retval = 0;
			जाओ out_unlock;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (समय == 0) अणु
			retval = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण
	list_del(&ewp->list);
out_unlock:
	spin_unlock(&info->lock);
out:
	वापस retval;
पूर्ण

/*
 * Returns रुकोing task that should be serviced first or शून्य अगर none exists
 */
अटल काष्ठा ext_रुको_queue *wq_get_first_रुकोer(
		काष्ठा mqueue_inode_info *info, पूर्णांक sr)
अणु
	काष्ठा list_head *ptr;

	ptr = info->e_रुको_q[sr].list.prev;
	अगर (ptr == &info->e_रुको_q[sr].list)
		वापस शून्य;
	वापस list_entry(ptr, काष्ठा ext_रुको_queue, list);
पूर्ण


अटल अंतरभूत व्योम set_cookie(काष्ठा sk_buff *skb, अक्षर code)
अणु
	((अक्षर *)skb->data)[NOTIFY_COOKIE_LEN-1] = code;
पूर्ण

/*
 * The next function is only to split too दीर्घ sys_mq_समयdsend
 */
अटल व्योम __करो_notअगरy(काष्ठा mqueue_inode_info *info)
अणु
	/* notअगरication
	 * invoked when there is रेजिस्टरed process and there isn't process
	 * रुकोing synchronously क्रम message AND state of queue changed from
	 * empty to not empty. Here we are sure that no one is रुकोing
	 * synchronously. */
	अगर (info->notअगरy_owner &&
	    info->attr.mq_curmsgs == 1) अणु
		चयन (info->notअगरy.sigev_notअगरy) अणु
		हाल SIGEV_NONE:
			अवरोध;
		हाल SIGEV_SIGNAL: अणु
			काष्ठा kernel_siginfo sig_i;
			काष्ठा task_काष्ठा *task;

			/* करो_mq_notअगरy() accepts sigev_signo == 0, why?? */
			अगर (!info->notअगरy.sigev_signo)
				अवरोध;

			clear_siginfo(&sig_i);
			sig_i.si_signo = info->notअगरy.sigev_signo;
			sig_i.si_त्रुटि_सं = 0;
			sig_i.si_code = SI_MESGQ;
			sig_i.si_value = info->notअगरy.sigev_value;
			rcu_पढ़ो_lock();
			/* map current pid/uid पूर्णांकo info->owner's namespaces */
			sig_i.si_pid = task_tgid_nr_ns(current,
						ns_of_pid(info->notअगरy_owner));
			sig_i.si_uid = from_kuid_munged(info->notअगरy_user_ns,
						current_uid());
			/*
			 * We can't use समाप्त_pid_info(), this संकेत should
			 * bypass check_समाप्त_permission(). It is from kernel
			 * but si_fromuser() can't know this.
			 * We करो check the self_exec_id, to aव्योम sending
			 * संकेतs to programs that करोn't expect them.
			 */
			task = pid_task(info->notअगरy_owner, PIDTYPE_TGID);
			अगर (task && task->self_exec_id ==
						info->notअगरy_self_exec_id) अणु
				करो_send_sig_info(info->notअगरy.sigev_signo,
						&sig_i, task, PIDTYPE_TGID);
			पूर्ण
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		हाल SIGEV_THREAD:
			set_cookie(info->notअगरy_cookie, NOTIFY_WOKENUP);
			netlink_sendskb(info->notअगरy_sock, info->notअगरy_cookie);
			अवरोध;
		पूर्ण
		/* after notअगरication unरेजिस्टरs process */
		put_pid(info->notअगरy_owner);
		put_user_ns(info->notअगरy_user_ns);
		info->notअगरy_owner = शून्य;
		info->notअगरy_user_ns = शून्य;
	पूर्ण
	wake_up(&info->रुको_q);
पूर्ण

अटल पूर्णांक prepare_समयout(स्थिर काष्ठा __kernel_बारpec __user *u_असल_समयout,
			   काष्ठा बारpec64 *ts)
अणु
	अगर (get_बारpec64(ts, u_असल_समयout))
		वापस -EFAULT;
	अगर (!बारpec64_valid(ts))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम हटाओ_notअगरication(काष्ठा mqueue_inode_info *info)
अणु
	अगर (info->notअगरy_owner != शून्य &&
	    info->notअगरy.sigev_notअगरy == SIGEV_THREAD) अणु
		set_cookie(info->notअगरy_cookie, NOTIFY_REMOVED);
		netlink_sendskb(info->notअगरy_sock, info->notअगरy_cookie);
	पूर्ण
	put_pid(info->notअगरy_owner);
	put_user_ns(info->notअगरy_user_ns);
	info->notअगरy_owner = शून्य;
	info->notअगरy_user_ns = शून्य;
पूर्ण

अटल पूर्णांक prepare_खोलो(काष्ठा dentry *dentry, पूर्णांक oflag, पूर्णांक ro,
			umode_t mode, काष्ठा filename *name,
			काष्ठा mq_attr *attr)
अणु
	अटल स्थिर पूर्णांक oflag2acc[O_ACCMODE] = अणु MAY_READ, MAY_WRITE,
						  MAY_READ | MAY_WRITE पूर्ण;
	पूर्णांक acc;

	अगर (d_really_is_negative(dentry)) अणु
		अगर (!(oflag & O_CREAT))
			वापस -ENOENT;
		अगर (ro)
			वापस ro;
		audit_inode_parent_hidden(name, dentry->d_parent);
		वापस vfs_mkobj(dentry, mode & ~current_umask(),
				  mqueue_create_attr, attr);
	पूर्ण
	/* it alपढ़ोy existed */
	audit_inode(name, dentry, 0);
	अगर ((oflag & (O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL))
		वापस -EEXIST;
	अगर ((oflag & O_ACCMODE) == (O_RDWR | O_WRONLY))
		वापस -EINVAL;
	acc = oflag2acc[oflag & O_ACCMODE];
	वापस inode_permission(&init_user_ns, d_inode(dentry), acc);
पूर्ण

अटल पूर्णांक करो_mq_खोलो(स्थिर अक्षर __user *u_name, पूर्णांक oflag, umode_t mode,
		      काष्ठा mq_attr *attr)
अणु
	काष्ठा vfsmount *mnt = current->nsproxy->ipc_ns->mq_mnt;
	काष्ठा dentry *root = mnt->mnt_root;
	काष्ठा filename *name;
	काष्ठा path path;
	पूर्णांक fd, error;
	पूर्णांक ro;

	audit_mq_खोलो(oflag, mode, attr);

	अगर (IS_ERR(name = getname(u_name)))
		वापस PTR_ERR(name);

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0)
		जाओ out_putname;

	ro = mnt_want_ग_लिखो(mnt);	/* we'll drop it in any हाल */
	inode_lock(d_inode(root));
	path.dentry = lookup_one_len(name->name, root, म_माप(name->name));
	अगर (IS_ERR(path.dentry)) अणु
		error = PTR_ERR(path.dentry);
		जाओ out_putfd;
	पूर्ण
	path.mnt = mntget(mnt);
	error = prepare_खोलो(path.dentry, oflag, ro, mode, name, attr);
	अगर (!error) अणु
		काष्ठा file *file = dentry_खोलो(&path, oflag, current_cred());
		अगर (!IS_ERR(file))
			fd_install(fd, file);
		अन्यथा
			error = PTR_ERR(file);
	पूर्ण
	path_put(&path);
out_putfd:
	अगर (error) अणु
		put_unused_fd(fd);
		fd = error;
	पूर्ण
	inode_unlock(d_inode(root));
	अगर (!ro)
		mnt_drop_ग_लिखो(mnt);
out_putname:
	putname(name);
	वापस fd;
पूर्ण

SYSCALL_DEFINE4(mq_खोलो, स्थिर अक्षर __user *, u_name, पूर्णांक, oflag, umode_t, mode,
		काष्ठा mq_attr __user *, u_attr)
अणु
	काष्ठा mq_attr attr;
	अगर (u_attr && copy_from_user(&attr, u_attr, माप(काष्ठा mq_attr)))
		वापस -EFAULT;

	वापस करो_mq_खोलो(u_name, oflag, mode, u_attr ? &attr : शून्य);
पूर्ण

SYSCALL_DEFINE1(mq_unlink, स्थिर अक्षर __user *, u_name)
अणु
	पूर्णांक err;
	काष्ठा filename *name;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode = शून्य;
	काष्ठा ipc_namespace *ipc_ns = current->nsproxy->ipc_ns;
	काष्ठा vfsmount *mnt = ipc_ns->mq_mnt;

	name = getname(u_name);
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	audit_inode_parent_hidden(name, mnt->mnt_root);
	err = mnt_want_ग_लिखो(mnt);
	अगर (err)
		जाओ out_name;
	inode_lock_nested(d_inode(mnt->mnt_root), I_MUTEX_PARENT);
	dentry = lookup_one_len(name->name, mnt->mnt_root,
				म_माप(name->name));
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ out_unlock;
	पूर्ण

	inode = d_inode(dentry);
	अगर (!inode) अणु
		err = -ENOENT;
	पूर्ण अन्यथा अणु
		ihold(inode);
		err = vfs_unlink(&init_user_ns, d_inode(dentry->d_parent),
				 dentry, शून्य);
	पूर्ण
	dput(dentry);

out_unlock:
	inode_unlock(d_inode(mnt->mnt_root));
	अगर (inode)
		iput(inode);
	mnt_drop_ग_लिखो(mnt);
out_name:
	putname(name);

	वापस err;
पूर्ण

/* Pipelined send and receive functions.
 *
 * If a receiver finds no रुकोing message, then it रेजिस्टरs itself in the
 * list of रुकोing receivers. A sender checks that list beक्रमe adding the new
 * message पूर्णांकo the message array. If there is a रुकोing receiver, then it
 * bypasses the message array and directly hands the message over to the
 * receiver. The receiver accepts the message and वापसs without grabbing the
 * queue spinlock:
 *
 * - Set poपूर्णांकer to message.
 * - Queue the receiver task क्रम later wakeup (without the info->lock).
 * - Update its state to STATE_READY. Now the receiver can जारी.
 * - Wake up the process after the lock is dropped. Should the process wake up
 *   beक्रमe this wakeup (due to a समयout or a संकेत) it will either see
 *   STATE_READY and जारी or acquire the lock to check the state again.
 *
 * The same algorithm is used क्रम senders.
 */

अटल अंतरभूत व्योम __pipelined_op(काष्ठा wake_q_head *wake_q,
				  काष्ठा mqueue_inode_info *info,
				  काष्ठा ext_रुको_queue *this)
अणु
	काष्ठा task_काष्ठा *task;

	list_del(&this->list);
	task = get_task_काष्ठा(this->task);

	/* see MQ_BARRIER क्रम purpose/pairing */
	smp_store_release(&this->state, STATE_READY);
	wake_q_add_safe(wake_q, task);
पूर्ण

/* pipelined_send() - send a message directly to the task रुकोing in
 * sys_mq_समयdreceive() (without inserting message पूर्णांकo a queue).
 */
अटल अंतरभूत व्योम pipelined_send(काष्ठा wake_q_head *wake_q,
				  काष्ठा mqueue_inode_info *info,
				  काष्ठा msg_msg *message,
				  काष्ठा ext_रुको_queue *receiver)
अणु
	receiver->msg = message;
	__pipelined_op(wake_q, info, receiver);
पूर्ण

/* pipelined_receive() - अगर there is task रुकोing in sys_mq_समयdsend()
 * माला_लो its message and put to the queue (we have one मुक्त place क्रम sure). */
अटल अंतरभूत व्योम pipelined_receive(काष्ठा wake_q_head *wake_q,
				     काष्ठा mqueue_inode_info *info)
अणु
	काष्ठा ext_रुको_queue *sender = wq_get_first_रुकोer(info, SEND);

	अगर (!sender) अणु
		/* क्रम poll */
		wake_up_पूर्णांकerruptible(&info->रुको_q);
		वापस;
	पूर्ण
	अगर (msg_insert(sender->msg, info))
		वापस;

	__pipelined_op(wake_q, info, sender);
पूर्ण

अटल पूर्णांक करो_mq_समयdsend(mqd_t mqdes, स्थिर अक्षर __user *u_msg_ptr,
		माप_प्रकार msg_len, अचिन्हित पूर्णांक msg_prio,
		काष्ठा बारpec64 *ts)
अणु
	काष्ठा fd f;
	काष्ठा inode *inode;
	काष्ठा ext_रुको_queue रुको;
	काष्ठा ext_रुको_queue *receiver;
	काष्ठा msg_msg *msg_ptr;
	काष्ठा mqueue_inode_info *info;
	kसमय_प्रकार expires, *समयout = शून्य;
	काष्ठा posix_msg_tree_node *new_leaf = शून्य;
	पूर्णांक ret = 0;
	DEFINE_WAKE_Q(wake_q);

	अगर (unlikely(msg_prio >= (अचिन्हित दीर्घ) MQ_PRIO_MAX))
		वापस -EINVAL;

	अगर (ts) अणु
		expires = बारpec64_to_kसमय(*ts);
		समयout = &expires;
	पूर्ण

	audit_mq_sendrecv(mqdes, msg_len, msg_prio, ts);

	f = fdget(mqdes);
	अगर (unlikely(!f.file)) अणु
		ret = -EBADF;
		जाओ out;
	पूर्ण

	inode = file_inode(f.file);
	अगर (unlikely(f.file->f_op != &mqueue_file_operations)) अणु
		ret = -EBADF;
		जाओ out_fput;
	पूर्ण
	info = MQUEUE_I(inode);
	audit_file(f.file);

	अगर (unlikely(!(f.file->f_mode & FMODE_WRITE))) अणु
		ret = -EBADF;
		जाओ out_fput;
	पूर्ण

	अगर (unlikely(msg_len > info->attr.mq_msgsize)) अणु
		ret = -EMSGSIZE;
		जाओ out_fput;
	पूर्ण

	/* First try to allocate memory, beक्रमe करोing anything with
	 * existing queues. */
	msg_ptr = load_msg(u_msg_ptr, msg_len);
	अगर (IS_ERR(msg_ptr)) अणु
		ret = PTR_ERR(msg_ptr);
		जाओ out_fput;
	पूर्ण
	msg_ptr->m_ts = msg_len;
	msg_ptr->m_type = msg_prio;

	/*
	 * msg_insert really wants us to have a valid, spare node काष्ठा so
	 * it करोesn't have to kदो_स्मृति a GFP_ATOMIC allocation, but it will
	 * fall back to that अगर necessary.
	 */
	अगर (!info->node_cache)
		new_leaf = kदो_स्मृति(माप(*new_leaf), GFP_KERNEL);

	spin_lock(&info->lock);

	अगर (!info->node_cache && new_leaf) अणु
		/* Save our speculative allocation पूर्णांकo the cache */
		INIT_LIST_HEAD(&new_leaf->msg_list);
		info->node_cache = new_leaf;
		new_leaf = शून्य;
	पूर्ण अन्यथा अणु
		kमुक्त(new_leaf);
	पूर्ण

	अगर (info->attr.mq_curmsgs == info->attr.mq_maxmsg) अणु
		अगर (f.file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
		पूर्ण अन्यथा अणु
			रुको.task = current;
			रुको.msg = (व्योम *) msg_ptr;

			/* memory barrier not required, we hold info->lock */
			WRITE_ONCE(रुको.state, STATE_NONE);
			ret = wq_sleep(info, SEND, समयout, &रुको);
			/*
			 * wq_sleep must be called with info->lock held, and
			 * वापसs with the lock released
			 */
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		receiver = wq_get_first_रुकोer(info, RECV);
		अगर (receiver) अणु
			pipelined_send(&wake_q, info, msg_ptr, receiver);
		पूर्ण अन्यथा अणु
			/* adds message to the queue */
			ret = msg_insert(msg_ptr, info);
			अगर (ret)
				जाओ out_unlock;
			__करो_notअगरy(info);
		पूर्ण
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय =
				current_समय(inode);
	पूर्ण
out_unlock:
	spin_unlock(&info->lock);
	wake_up_q(&wake_q);
out_मुक्त:
	अगर (ret)
		मुक्त_msg(msg_ptr);
out_fput:
	fdput(f);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_mq_समयdreceive(mqd_t mqdes, अक्षर __user *u_msg_ptr,
		माप_प्रकार msg_len, अचिन्हित पूर्णांक __user *u_msg_prio,
		काष्ठा बारpec64 *ts)
अणु
	sमाप_प्रकार ret;
	काष्ठा msg_msg *msg_ptr;
	काष्ठा fd f;
	काष्ठा inode *inode;
	काष्ठा mqueue_inode_info *info;
	काष्ठा ext_रुको_queue रुको;
	kसमय_प्रकार expires, *समयout = शून्य;
	काष्ठा posix_msg_tree_node *new_leaf = शून्य;

	अगर (ts) अणु
		expires = बारpec64_to_kसमय(*ts);
		समयout = &expires;
	पूर्ण

	audit_mq_sendrecv(mqdes, msg_len, 0, ts);

	f = fdget(mqdes);
	अगर (unlikely(!f.file)) अणु
		ret = -EBADF;
		जाओ out;
	पूर्ण

	inode = file_inode(f.file);
	अगर (unlikely(f.file->f_op != &mqueue_file_operations)) अणु
		ret = -EBADF;
		जाओ out_fput;
	पूर्ण
	info = MQUEUE_I(inode);
	audit_file(f.file);

	अगर (unlikely(!(f.file->f_mode & FMODE_READ))) अणु
		ret = -EBADF;
		जाओ out_fput;
	पूर्ण

	/* checks अगर buffer is big enough */
	अगर (unlikely(msg_len < info->attr.mq_msgsize)) अणु
		ret = -EMSGSIZE;
		जाओ out_fput;
	पूर्ण

	/*
	 * msg_insert really wants us to have a valid, spare node काष्ठा so
	 * it करोesn't have to kदो_स्मृति a GFP_ATOMIC allocation, but it will
	 * fall back to that अगर necessary.
	 */
	अगर (!info->node_cache)
		new_leaf = kदो_स्मृति(माप(*new_leaf), GFP_KERNEL);

	spin_lock(&info->lock);

	अगर (!info->node_cache && new_leaf) अणु
		/* Save our speculative allocation पूर्णांकo the cache */
		INIT_LIST_HEAD(&new_leaf->msg_list);
		info->node_cache = new_leaf;
	पूर्ण अन्यथा अणु
		kमुक्त(new_leaf);
	पूर्ण

	अगर (info->attr.mq_curmsgs == 0) अणु
		अगर (f.file->f_flags & O_NONBLOCK) अणु
			spin_unlock(&info->lock);
			ret = -EAGAIN;
		पूर्ण अन्यथा अणु
			रुको.task = current;

			/* memory barrier not required, we hold info->lock */
			WRITE_ONCE(रुको.state, STATE_NONE);
			ret = wq_sleep(info, RECV, समयout, &रुको);
			msg_ptr = रुको.msg;
		पूर्ण
	पूर्ण अन्यथा अणु
		DEFINE_WAKE_Q(wake_q);

		msg_ptr = msg_get(info);

		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय =
				current_समय(inode);

		/* There is now मुक्त space in queue. */
		pipelined_receive(&wake_q, info);
		spin_unlock(&info->lock);
		wake_up_q(&wake_q);
		ret = 0;
	पूर्ण
	अगर (ret == 0) अणु
		ret = msg_ptr->m_ts;

		अगर ((u_msg_prio && put_user(msg_ptr->m_type, u_msg_prio)) ||
			store_msg(u_msg_ptr, msg_ptr, msg_ptr->m_ts)) अणु
			ret = -EFAULT;
		पूर्ण
		मुक्त_msg(msg_ptr);
	पूर्ण
out_fput:
	fdput(f);
out:
	वापस ret;
पूर्ण

SYSCALL_DEFINE5(mq_समयdsend, mqd_t, mqdes, स्थिर अक्षर __user *, u_msg_ptr,
		माप_प्रकार, msg_len, अचिन्हित पूर्णांक, msg_prio,
		स्थिर काष्ठा __kernel_बारpec __user *, u_असल_समयout)
अणु
	काष्ठा बारpec64 ts, *p = शून्य;
	अगर (u_असल_समयout) अणु
		पूर्णांक res = prepare_समयout(u_असल_समयout, &ts);
		अगर (res)
			वापस res;
		p = &ts;
	पूर्ण
	वापस करो_mq_समयdsend(mqdes, u_msg_ptr, msg_len, msg_prio, p);
पूर्ण

SYSCALL_DEFINE5(mq_समयdreceive, mqd_t, mqdes, अक्षर __user *, u_msg_ptr,
		माप_प्रकार, msg_len, अचिन्हित पूर्णांक __user *, u_msg_prio,
		स्थिर काष्ठा __kernel_बारpec __user *, u_असल_समयout)
अणु
	काष्ठा बारpec64 ts, *p = शून्य;
	अगर (u_असल_समयout) अणु
		पूर्णांक res = prepare_समयout(u_असल_समयout, &ts);
		अगर (res)
			वापस res;
		p = &ts;
	पूर्ण
	वापस करो_mq_समयdreceive(mqdes, u_msg_ptr, msg_len, u_msg_prio, p);
पूर्ण

/*
 * Notes: the हाल when user wants us to deरेजिस्टर (with शून्य as poपूर्णांकer)
 * and he isn't currently owner of notअगरication, will be silently discarded.
 * It isn't explicitly defined in the POSIX.
 */
अटल पूर्णांक करो_mq_notअगरy(mqd_t mqdes, स्थिर काष्ठा sigevent *notअगरication)
अणु
	पूर्णांक ret;
	काष्ठा fd f;
	काष्ठा sock *sock;
	काष्ठा inode *inode;
	काष्ठा mqueue_inode_info *info;
	काष्ठा sk_buff *nc;

	audit_mq_notअगरy(mqdes, notअगरication);

	nc = शून्य;
	sock = शून्य;
	अगर (notअगरication != शून्य) अणु
		अगर (unlikely(notअगरication->sigev_notअगरy != SIGEV_NONE &&
			     notअगरication->sigev_notअगरy != SIGEV_SIGNAL &&
			     notअगरication->sigev_notअगरy != SIGEV_THREAD))
			वापस -EINVAL;
		अगर (notअगरication->sigev_notअगरy == SIGEV_SIGNAL &&
			!valid_संकेत(notअगरication->sigev_signo)) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (notअगरication->sigev_notअगरy == SIGEV_THREAD) अणु
			दीर्घ समयo;

			/* create the notअगरy skb */
			nc = alloc_skb(NOTIFY_COOKIE_LEN, GFP_KERNEL);
			अगर (!nc)
				वापस -ENOMEM;

			अगर (copy_from_user(nc->data,
					notअगरication->sigev_value.sival_ptr,
					NOTIFY_COOKIE_LEN)) अणु
				ret = -EFAULT;
				जाओ मुक्त_skb;
			पूर्ण

			/* TODO: add a header? */
			skb_put(nc, NOTIFY_COOKIE_LEN);
			/* and attach it to the socket */
retry:
			f = fdget(notअगरication->sigev_signo);
			अगर (!f.file) अणु
				ret = -EBADF;
				जाओ out;
			पूर्ण
			sock = netlink_माला_लोockbyfilp(f.file);
			fdput(f);
			अगर (IS_ERR(sock)) अणु
				ret = PTR_ERR(sock);
				जाओ मुक्त_skb;
			पूर्ण

			समयo = MAX_SCHEDULE_TIMEOUT;
			ret = netlink_attachskb(sock, nc, &समयo, शून्य);
			अगर (ret == 1) अणु
				sock = शून्य;
				जाओ retry;
			पूर्ण
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	f = fdget(mqdes);
	अगर (!f.file) अणु
		ret = -EBADF;
		जाओ out;
	पूर्ण

	inode = file_inode(f.file);
	अगर (unlikely(f.file->f_op != &mqueue_file_operations)) अणु
		ret = -EBADF;
		जाओ out_fput;
	पूर्ण
	info = MQUEUE_I(inode);

	ret = 0;
	spin_lock(&info->lock);
	अगर (notअगरication == शून्य) अणु
		अगर (info->notअगरy_owner == task_tgid(current)) अणु
			हटाओ_notअगरication(info);
			inode->i_aसमय = inode->i_स_समय = current_समय(inode);
		पूर्ण
	पूर्ण अन्यथा अगर (info->notअगरy_owner != शून्य) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		चयन (notअगरication->sigev_notअगरy) अणु
		हाल SIGEV_NONE:
			info->notअगरy.sigev_notअगरy = SIGEV_NONE;
			अवरोध;
		हाल SIGEV_THREAD:
			info->notअगरy_sock = sock;
			info->notअगरy_cookie = nc;
			sock = शून्य;
			nc = शून्य;
			info->notअगरy.sigev_notअगरy = SIGEV_THREAD;
			अवरोध;
		हाल SIGEV_SIGNAL:
			info->notअगरy.sigev_signo = notअगरication->sigev_signo;
			info->notअगरy.sigev_value = notअगरication->sigev_value;
			info->notअगरy.sigev_notअगरy = SIGEV_SIGNAL;
			info->notअगरy_self_exec_id = current->self_exec_id;
			अवरोध;
		पूर्ण

		info->notअगरy_owner = get_pid(task_tgid(current));
		info->notअगरy_user_ns = get_user_ns(current_user_ns());
		inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	पूर्ण
	spin_unlock(&info->lock);
out_fput:
	fdput(f);
out:
	अगर (sock)
		netlink_detachskb(sock, nc);
	अन्यथा
मुक्त_skb:
		dev_kमुक्त_skb(nc);

	वापस ret;
पूर्ण

SYSCALL_DEFINE2(mq_notअगरy, mqd_t, mqdes,
		स्थिर काष्ठा sigevent __user *, u_notअगरication)
अणु
	काष्ठा sigevent n, *p = शून्य;
	अगर (u_notअगरication) अणु
		अगर (copy_from_user(&n, u_notअगरication, माप(काष्ठा sigevent)))
			वापस -EFAULT;
		p = &n;
	पूर्ण
	वापस करो_mq_notअगरy(mqdes, p);
पूर्ण

अटल पूर्णांक करो_mq_माला_लोetattr(पूर्णांक mqdes, काष्ठा mq_attr *new, काष्ठा mq_attr *old)
अणु
	काष्ठा fd f;
	काष्ठा inode *inode;
	काष्ठा mqueue_inode_info *info;

	अगर (new && (new->mq_flags & (~O_NONBLOCK)))
		वापस -EINVAL;

	f = fdget(mqdes);
	अगर (!f.file)
		वापस -EBADF;

	अगर (unlikely(f.file->f_op != &mqueue_file_operations)) अणु
		fdput(f);
		वापस -EBADF;
	पूर्ण

	inode = file_inode(f.file);
	info = MQUEUE_I(inode);

	spin_lock(&info->lock);

	अगर (old) अणु
		*old = info->attr;
		old->mq_flags = f.file->f_flags & O_NONBLOCK;
	पूर्ण
	अगर (new) अणु
		audit_mq_माला_लोetattr(mqdes, new);
		spin_lock(&f.file->f_lock);
		अगर (new->mq_flags & O_NONBLOCK)
			f.file->f_flags |= O_NONBLOCK;
		अन्यथा
			f.file->f_flags &= ~O_NONBLOCK;
		spin_unlock(&f.file->f_lock);

		inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	पूर्ण

	spin_unlock(&info->lock);
	fdput(f);
	वापस 0;
पूर्ण

SYSCALL_DEFINE3(mq_माला_लोetattr, mqd_t, mqdes,
		स्थिर काष्ठा mq_attr __user *, u_mqstat,
		काष्ठा mq_attr __user *, u_omqstat)
अणु
	पूर्णांक ret;
	काष्ठा mq_attr mqstat, omqstat;
	काष्ठा mq_attr *new = शून्य, *old = शून्य;

	अगर (u_mqstat) अणु
		new = &mqstat;
		अगर (copy_from_user(new, u_mqstat, माप(काष्ठा mq_attr)))
			वापस -EFAULT;
	पूर्ण
	अगर (u_omqstat)
		old = &omqstat;

	ret = करो_mq_माला_लोetattr(mqdes, new, old);
	अगर (ret || !old)
		वापस ret;

	अगर (copy_to_user(u_omqstat, old, माप(काष्ठा mq_attr)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_mq_attr अणु
	compat_दीर्घ_t mq_flags;      /* message queue flags		     */
	compat_दीर्घ_t mq_maxmsg;     /* maximum number of messages	     */
	compat_दीर्घ_t mq_msgsize;    /* maximum message size		     */
	compat_दीर्घ_t mq_curmsgs;    /* number of messages currently queued  */
	compat_दीर्घ_t __reserved[4]; /* ignored क्रम input, zeroed क्रम output */
पूर्ण;

अटल अंतरभूत पूर्णांक get_compat_mq_attr(काष्ठा mq_attr *attr,
			स्थिर काष्ठा compat_mq_attr __user *uattr)
अणु
	काष्ठा compat_mq_attr v;

	अगर (copy_from_user(&v, uattr, माप(*uattr)))
		वापस -EFAULT;

	स_रखो(attr, 0, माप(*attr));
	attr->mq_flags = v.mq_flags;
	attr->mq_maxmsg = v.mq_maxmsg;
	attr->mq_msgsize = v.mq_msgsize;
	attr->mq_curmsgs = v.mq_curmsgs;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक put_compat_mq_attr(स्थिर काष्ठा mq_attr *attr,
			काष्ठा compat_mq_attr __user *uattr)
अणु
	काष्ठा compat_mq_attr v;

	स_रखो(&v, 0, माप(v));
	v.mq_flags = attr->mq_flags;
	v.mq_maxmsg = attr->mq_maxmsg;
	v.mq_msgsize = attr->mq_msgsize;
	v.mq_curmsgs = attr->mq_curmsgs;
	अगर (copy_to_user(uattr, &v, माप(*uattr)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE4(mq_खोलो, स्थिर अक्षर __user *, u_name,
		       पूर्णांक, oflag, compat_mode_t, mode,
		       काष्ठा compat_mq_attr __user *, u_attr)
अणु
	काष्ठा mq_attr attr, *p = शून्य;
	अगर (u_attr && oflag & O_CREAT) अणु
		p = &attr;
		अगर (get_compat_mq_attr(&attr, u_attr))
			वापस -EFAULT;
	पूर्ण
	वापस करो_mq_खोलो(u_name, oflag, mode, p);
पूर्ण

COMPAT_SYSCALL_DEFINE2(mq_notअगरy, mqd_t, mqdes,
		       स्थिर काष्ठा compat_sigevent __user *, u_notअगरication)
अणु
	काष्ठा sigevent n, *p = शून्य;
	अगर (u_notअगरication) अणु
		अगर (get_compat_sigevent(&n, u_notअगरication))
			वापस -EFAULT;
		अगर (n.sigev_notअगरy == SIGEV_THREAD)
			n.sigev_value.sival_ptr = compat_ptr(n.sigev_value.sival_पूर्णांक);
		p = &n;
	पूर्ण
	वापस करो_mq_notअगरy(mqdes, p);
पूर्ण

COMPAT_SYSCALL_DEFINE3(mq_माला_लोetattr, mqd_t, mqdes,
		       स्थिर काष्ठा compat_mq_attr __user *, u_mqstat,
		       काष्ठा compat_mq_attr __user *, u_omqstat)
अणु
	पूर्णांक ret;
	काष्ठा mq_attr mqstat, omqstat;
	काष्ठा mq_attr *new = शून्य, *old = शून्य;

	अगर (u_mqstat) अणु
		new = &mqstat;
		अगर (get_compat_mq_attr(new, u_mqstat))
			वापस -EFAULT;
	पूर्ण
	अगर (u_omqstat)
		old = &omqstat;

	ret = करो_mq_माला_लोetattr(mqdes, new, old);
	अगर (ret || !old)
		वापस ret;

	अगर (put_compat_mq_attr(old, u_omqstat))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
अटल पूर्णांक compat_prepare_समयout(स्थिर काष्ठा old_बारpec32 __user *p,
				   काष्ठा बारpec64 *ts)
अणु
	अगर (get_old_बारpec32(ts, p))
		वापस -EFAULT;
	अगर (!बारpec64_valid(ts))
		वापस -EINVAL;
	वापस 0;
पूर्ण

SYSCALL_DEFINE5(mq_समयdsend_समय32, mqd_t, mqdes,
		स्थिर अक्षर __user *, u_msg_ptr,
		अचिन्हित पूर्णांक, msg_len, अचिन्हित पूर्णांक, msg_prio,
		स्थिर काष्ठा old_बारpec32 __user *, u_असल_समयout)
अणु
	काष्ठा बारpec64 ts, *p = शून्य;
	अगर (u_असल_समयout) अणु
		पूर्णांक res = compat_prepare_समयout(u_असल_समयout, &ts);
		अगर (res)
			वापस res;
		p = &ts;
	पूर्ण
	वापस करो_mq_समयdsend(mqdes, u_msg_ptr, msg_len, msg_prio, p);
पूर्ण

SYSCALL_DEFINE5(mq_समयdreceive_समय32, mqd_t, mqdes,
		अक्षर __user *, u_msg_ptr,
		अचिन्हित पूर्णांक, msg_len, अचिन्हित पूर्णांक __user *, u_msg_prio,
		स्थिर काष्ठा old_बारpec32 __user *, u_असल_समयout)
अणु
	काष्ठा बारpec64 ts, *p = शून्य;
	अगर (u_असल_समयout) अणु
		पूर्णांक res = compat_prepare_समयout(u_असल_समयout, &ts);
		अगर (res)
			वापस res;
		p = &ts;
	पूर्ण
	वापस करो_mq_समयdreceive(mqdes, u_msg_ptr, msg_len, u_msg_prio, p);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा inode_operations mqueue_dir_inode_operations = अणु
	.lookup = simple_lookup,
	.create = mqueue_create,
	.unlink = mqueue_unlink,
पूर्ण;

अटल स्थिर काष्ठा file_operations mqueue_file_operations = अणु
	.flush = mqueue_flush_file,
	.poll = mqueue_poll_file,
	.पढ़ो = mqueue_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा super_operations mqueue_super_ops = अणु
	.alloc_inode = mqueue_alloc_inode,
	.मुक्त_inode = mqueue_मुक्त_inode,
	.evict_inode = mqueue_evict_inode,
	.statfs = simple_statfs,
पूर्ण;

अटल स्थिर काष्ठा fs_context_operations mqueue_fs_context_ops = अणु
	.मुक्त		= mqueue_fs_context_मुक्त,
	.get_tree	= mqueue_get_tree,
पूर्ण;

अटल काष्ठा file_प्रणाली_type mqueue_fs_type = अणु
	.name			= "mqueue",
	.init_fs_context	= mqueue_init_fs_context,
	.समाप्त_sb		= समाप्त_litter_super,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;

पूर्णांक mq_init_ns(काष्ठा ipc_namespace *ns)
अणु
	काष्ठा vfsmount *m;

	ns->mq_queues_count  = 0;
	ns->mq_queues_max    = DFLT_QUEUESMAX;
	ns->mq_msg_max       = DFLT_MSGMAX;
	ns->mq_msgsize_max   = DFLT_MSGSIZEMAX;
	ns->mq_msg_शेष   = DFLT_MSG;
	ns->mq_msgsize_शेष  = DFLT_MSGSIZE;

	m = mq_create_mount(ns);
	अगर (IS_ERR(m))
		वापस PTR_ERR(m);
	ns->mq_mnt = m;
	वापस 0;
पूर्ण

व्योम mq_clear_sbinfo(काष्ठा ipc_namespace *ns)
अणु
	ns->mq_mnt->mnt_sb->s_fs_info = शून्य;
पूर्ण

व्योम mq_put_mnt(काष्ठा ipc_namespace *ns)
अणु
	kern_unmount(ns->mq_mnt);
पूर्ण

अटल पूर्णांक __init init_mqueue_fs(व्योम)
अणु
	पूर्णांक error;

	mqueue_inode_cachep = kmem_cache_create("mqueue_inode_cache",
				माप(काष्ठा mqueue_inode_info), 0,
				SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT, init_once);
	अगर (mqueue_inode_cachep == शून्य)
		वापस -ENOMEM;

	/* ignore failures - they are not fatal */
	mq_sysctl_table = mq_रेजिस्टर_sysctl_table();

	error = रेजिस्टर_fileप्रणाली(&mqueue_fs_type);
	अगर (error)
		जाओ out_sysctl;

	spin_lock_init(&mq_lock);

	error = mq_init_ns(&init_ipc_ns);
	अगर (error)
		जाओ out_fileप्रणाली;

	वापस 0;

out_fileप्रणाली:
	unरेजिस्टर_fileप्रणाली(&mqueue_fs_type);
out_sysctl:
	अगर (mq_sysctl_table)
		unरेजिस्टर_sysctl_table(mq_sysctl_table);
	kmem_cache_destroy(mqueue_inode_cachep);
	वापस error;
पूर्ण

device_initcall(init_mqueue_fs);
