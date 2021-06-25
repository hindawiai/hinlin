<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * Changes by Acxiom Corporation to add protocol version to kernel
 * communication, Copyright Acxiom Corporation, 2005.
 *
 * See COPYING in top-level directory.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-dev-proto.h"
#समावेश "orangefs-bufmap.h"
#समावेश "orangefs-debugfs.h"

#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

/* this file implements the /dev/pvfs2-req device node */

uपूर्णांक32_t orangefs_userspace_version;

अटल पूर्णांक खोलो_access_count;

अटल DEFINE_MUTEX(devreq_mutex);

#घोषणा DUMP_DEVICE_ERROR()                                                   \
करो अणु                                                                          \
	gossip_err("*****************************************************\n");\
	gossip_err("ORANGEFS Device Error:  You cannot open the device file ");  \
	gossip_err("\n/dev/%s more than once.  Please make sure that\nthere " \
		   "are no ", ORANGEFS_REQDEVICE_NAME);                          \
	gossip_err("instances of a program using this device\ncurrently "     \
		   "running. (You must verify this!)\n");                     \
	gossip_err("For example, you can use the lsof program as follows:\n");\
	gossip_err("'lsof | grep %s' (run this as root)\n",                   \
		   ORANGEFS_REQDEVICE_NAME);                                     \
	gossip_err("  open_access_count = %d\n", खोलो_access_count);          \
	gossip_err("*****************************************************\n");\
पूर्ण जबतक (0)

अटल पूर्णांक hash_func(__u64 tag, पूर्णांक table_size)
अणु
	वापस करो_भाग(tag, (अचिन्हित पूर्णांक)table_size);
पूर्ण

अटल व्योम orangefs_devreq_add_op(काष्ठा orangefs_kernel_op_s *op)
अणु
	पूर्णांक index = hash_func(op->tag, hash_table_size);

	list_add_tail(&op->list, &orangefs_htable_ops_in_progress[index]);
पूर्ण

/*
 * find the op with this tag and हटाओ it from the in progress
 * hash table.
 */
अटल काष्ठा orangefs_kernel_op_s *orangefs_devreq_हटाओ_op(__u64 tag)
अणु
	काष्ठा orangefs_kernel_op_s *op, *next;
	पूर्णांक index;

	index = hash_func(tag, hash_table_size);

	spin_lock(&orangefs_htable_ops_in_progress_lock);
	list_क्रम_each_entry_safe(op,
				 next,
				 &orangefs_htable_ops_in_progress[index],
				 list) अणु
		अगर (op->tag == tag && !op_state_purged(op) &&
		    !op_state_given_up(op)) अणु
			list_del_init(&op->list);
			spin_unlock(&orangefs_htable_ops_in_progress_lock);
			वापस op;
		पूर्ण
	पूर्ण

	spin_unlock(&orangefs_htable_ops_in_progress_lock);
	वापस शून्य;
पूर्ण

/* Returns whether any FS are still pending remounted */
अटल पूर्णांक mark_all_pending_mounts(व्योम)
अणु
	पूर्णांक unmounted = 1;
	काष्ठा orangefs_sb_info_s *orangefs_sb = शून्य;

	spin_lock(&orangefs_superblocks_lock);
	list_क्रम_each_entry(orangefs_sb, &orangefs_superblocks, list) अणु
		/* All of these file प्रणाली require a remount */
		orangefs_sb->mount_pending = 1;
		unmounted = 0;
	पूर्ण
	spin_unlock(&orangefs_superblocks_lock);
	वापस unmounted;
पूर्ण

/*
 * Determine अगर a given file प्रणाली needs to be remounted or not
 *  Returns -1 on error
 *           0 अगर alपढ़ोy mounted
 *           1 अगर needs remount
 */
अटल पूर्णांक fs_mount_pending(__s32 fsid)
अणु
	पूर्णांक mount_pending = -1;
	काष्ठा orangefs_sb_info_s *orangefs_sb = शून्य;

	spin_lock(&orangefs_superblocks_lock);
	list_क्रम_each_entry(orangefs_sb, &orangefs_superblocks, list) अणु
		अगर (orangefs_sb->fs_id == fsid) अणु
			mount_pending = orangefs_sb->mount_pending;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&orangefs_superblocks_lock);
	वापस mount_pending;
पूर्ण

अटल पूर्णांक orangefs_devreq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = -EINVAL;

	/* in order to ensure that the fileप्रणाली driver sees correct UIDs */
	अगर (file->f_cred->user_ns != &init_user_ns) अणु
		gossip_err("%s: device cannot be opened outside init_user_ns\n",
			   __func__);
		जाओ out;
	पूर्ण

	अगर (!(file->f_flags & O_NONBLOCK)) अणु
		gossip_err("%s: device cannot be opened in blocking mode\n",
			   __func__);
		जाओ out;
	पूर्ण
	ret = -EACCES;
	gossip_debug(GOSSIP_DEV_DEBUG, "client-core: opening device\n");
	mutex_lock(&devreq_mutex);

	अगर (खोलो_access_count == 0) अणु
		खोलो_access_count = 1;
		ret = 0;
	पूर्ण अन्यथा अणु
		DUMP_DEVICE_ERROR();
	पूर्ण
	mutex_unlock(&devreq_mutex);

out:

	gossip_debug(GOSSIP_DEV_DEBUG,
		     "pvfs2-client-core: open device complete (ret = %d)\n",
		     ret);
	वापस ret;
पूर्ण

/* Function क्रम पढ़ो() callers पूर्णांकo the device */
अटल sमाप_प्रकार orangefs_devreq_पढ़ो(काष्ठा file *file,
				 अक्षर __user *buf,
				 माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा orangefs_kernel_op_s *op, *temp;
	__s32 proto_ver = ORANGEFS_KERNEL_PROTO_VERSION;
	अटल __s32 magic = ORANGEFS_DEVREQ_MAGIC;
	काष्ठा orangefs_kernel_op_s *cur_op;
	अचिन्हित दीर्घ ret;

	/* We करो not support blocking IO. */
	अगर (!(file->f_flags & O_NONBLOCK)) अणु
		gossip_err("%s: blocking read from client-core.\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The client will करो an ioctl to find MAX_DEV_REQ_UPSIZE, then
	 * always पढ़ो with that size buffer.
	 */
	अगर (count != MAX_DEV_REQ_UPSIZE) अणु
		gossip_err("orangefs: client-core tried to read wrong size\n");
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम an empty list beक्रमe locking. */
	अगर (list_empty(&orangefs_request_list))
		वापस -EAGAIN;

restart:
	cur_op = शून्य;
	/* Get next op (अगर any) from top of list. */
	spin_lock(&orangefs_request_list_lock);
	list_क्रम_each_entry_safe(op, temp, &orangefs_request_list, list) अणु
		__s32 fsid;
		/* This lock is held past the end of the loop when we अवरोध. */
		spin_lock(&op->lock);
		अगर (unlikely(op_state_purged(op) || op_state_given_up(op))) अणु
			spin_unlock(&op->lock);
			जारी;
		पूर्ण

		fsid = fsid_of_op(op);
		अगर (fsid != ORANGEFS_FS_ID_शून्य) अणु
			पूर्णांक ret;
			/* Skip ops whose fileप्रणाली needs to be mounted. */
			ret = fs_mount_pending(fsid);
			अगर (ret == 1) अणु
				gossip_debug(GOSSIP_DEV_DEBUG,
				    "%s: mount pending, skipping op tag "
				    "%llu %s\n",
				    __func__,
				    llu(op->tag),
				    get_opname_string(op));
				spin_unlock(&op->lock);
				जारी;
			/*
			 * Skip ops whose fileप्रणाली we करोn't know about unless
			 * it is being mounted or unmounted.  It is possible क्रम
			 * a fileप्रणाली we करोn't know about to be unmounted अगर
			 * it fails to mount in the kernel after userspace has
			 * been sent the mount request.
			 */
			/* XXX: is there a better way to detect this? */
			पूर्ण अन्यथा अगर (ret == -1 &&
				   !(op->upcall.type ==
					ORANGEFS_VFS_OP_FS_MOUNT ||
				     op->upcall.type ==
					ORANGEFS_VFS_OP_GETATTR ||
				     op->upcall.type ==
					ORANGEFS_VFS_OP_FS_UMOUNT)) अणु
				gossip_debug(GOSSIP_DEV_DEBUG,
				    "orangefs: skipping op tag %llu %s\n",
				    llu(op->tag), get_opname_string(op));
				gossip_err(
				    "orangefs: ERROR: fs_mount_pending %d\n",
				    fsid);
				spin_unlock(&op->lock);
				जारी;
			पूर्ण
		पूर्ण
		/*
		 * Either this op करोes not pertain to a fileप्रणाली, is mounting
		 * a fileप्रणाली, or pertains to a mounted fileप्रणाली. Let it
		 * through.
		 */
		cur_op = op;
		अवरोध;
	पूर्ण

	/*
	 * At this poपूर्णांक we either have a valid op and can जारी or have not
	 * found an op and must ask the client to try again later.
	 */
	अगर (!cur_op) अणु
		spin_unlock(&orangefs_request_list_lock);
		वापस -EAGAIN;
	पूर्ण

	gossip_debug(GOSSIP_DEV_DEBUG, "%s: reading op tag %llu %s\n",
		     __func__,
		     llu(cur_op->tag),
		     get_opname_string(cur_op));

	/*
	 * Such an op should never be on the list in the first place. If so, we
	 * will पात.
	 */
	अगर (op_state_in_progress(cur_op) || op_state_serviced(cur_op)) अणु
		gossip_err("orangefs: ERROR: Current op already queued.\n");
		list_del_init(&cur_op->list);
		spin_unlock(&cur_op->lock);
		spin_unlock(&orangefs_request_list_lock);
		वापस -EAGAIN;
	पूर्ण

	list_del_init(&cur_op->list);
	spin_unlock(&orangefs_request_list_lock);

	spin_unlock(&cur_op->lock);

	/* Push the upcall out. */
	ret = copy_to_user(buf, &proto_ver, माप(__s32));
	अगर (ret != 0)
		जाओ error;
	ret = copy_to_user(buf + माप(__s32), &magic, माप(__s32));
	अगर (ret != 0)
		जाओ error;
	ret = copy_to_user(buf + 2 * माप(__s32),
		&cur_op->tag,
		माप(__u64));
	अगर (ret != 0)
		जाओ error;
	ret = copy_to_user(buf + 2 * माप(__s32) + माप(__u64),
		&cur_op->upcall,
		माप(काष्ठा orangefs_upcall_s));
	अगर (ret != 0)
		जाओ error;

	spin_lock(&orangefs_htable_ops_in_progress_lock);
	spin_lock(&cur_op->lock);
	अगर (unlikely(op_state_given_up(cur_op))) अणु
		spin_unlock(&cur_op->lock);
		spin_unlock(&orangefs_htable_ops_in_progress_lock);
		complete(&cur_op->रुकोq);
		जाओ restart;
	पूर्ण

	/*
	 * Set the operation to be in progress and move it between lists since
	 * it has been sent to the client.
	 */
	set_op_state_inprogress(cur_op);
	gossip_debug(GOSSIP_DEV_DEBUG,
		     "%s: 1 op:%s: op_state:%d: process:%s:\n",
		     __func__,
		     get_opname_string(cur_op),
		     cur_op->op_state,
		     current->comm);
	orangefs_devreq_add_op(cur_op);
	spin_unlock(&cur_op->lock);
	spin_unlock(&orangefs_htable_ops_in_progress_lock);

	/* The client only asks to पढ़ो one size buffer. */
	वापस MAX_DEV_REQ_UPSIZE;
error:
	/*
	 * We were unable to copy the op data to the client. Put the op back in
	 * list. If client has crashed, the op will be purged later when the
	 * device is released.
	 */
	gossip_err("orangefs: Failed to copy data to user space\n");
	spin_lock(&orangefs_request_list_lock);
	spin_lock(&cur_op->lock);
	अगर (likely(!op_state_given_up(cur_op))) अणु
		set_op_state_रुकोing(cur_op);
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: 2 op:%s: op_state:%d: process:%s:\n",
			     __func__,
			     get_opname_string(cur_op),
			     cur_op->op_state,
			     current->comm);
		list_add(&cur_op->list, &orangefs_request_list);
		spin_unlock(&cur_op->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&cur_op->lock);
		complete(&cur_op->रुकोq);
	पूर्ण
	spin_unlock(&orangefs_request_list_lock);
	वापस -EFAULT;
पूर्ण

/*
 * Function क्रम ग_लिखोv() callers पूर्णांकo the device.
 *
 * Userspace should have written:
 *  - __u32 version
 *  - __u32 magic
 *  - __u64 tag
 *  - काष्ठा orangefs_करोwncall_s
 *  - trailer buffer (in the हाल of READसूची operations)
 */
अटल sमाप_प्रकार orangefs_devreq_ग_लिखो_iter(काष्ठा kiocb *iocb,
				      काष्ठा iov_iter *iter)
अणु
	sमाप_प्रकार ret;
	काष्ठा orangefs_kernel_op_s *op = शून्य;
	काष्ठा अणु
		__u32 version;
		__u32 magic;
		__u64 tag;
	पूर्ण head;
	पूर्णांक total = ret = iov_iter_count(iter);
	पूर्णांक करोwncall_size = माप(काष्ठा orangefs_करोwncall_s);
	पूर्णांक head_size = माप(head);

	gossip_debug(GOSSIP_DEV_DEBUG, "%s: total:%d: ret:%zd:\n",
		     __func__,
		     total,
		     ret);

        अगर (total < MAX_DEV_REQ_DOWNSIZE) अणु
		gossip_err("%s: total:%d: must be at least:%u:\n",
			   __func__,
			   total,
			   (अचिन्हित पूर्णांक) MAX_DEV_REQ_DOWNSIZE);
		वापस -EFAULT;
	पूर्ण

	अगर (!copy_from_iter_full(&head, head_size, iter)) अणु
		gossip_err("%s: failed to copy head.\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (head.version < ORANGEFS_MINIMUM_USERSPACE_VERSION) अणु
		gossip_err("%s: userspace claims version"
			   "%d, minimum version required: %d.\n",
			   __func__,
			   head.version,
			   ORANGEFS_MINIMUM_USERSPACE_VERSION);
		वापस -EPROTO;
	पूर्ण

	अगर (head.magic != ORANGEFS_DEVREQ_MAGIC) अणु
		gossip_err("Error: Device magic number does not match.\n");
		वापस -EPROTO;
	पूर्ण

	अगर (!orangefs_userspace_version) अणु
		orangefs_userspace_version = head.version;
	पूर्ण अन्यथा अगर (orangefs_userspace_version != head.version) अणु
		gossip_err("Error: userspace version changes\n");
		वापस -EPROTO;
	पूर्ण

	/* हटाओ the op from the in progress hash table */
	op = orangefs_devreq_हटाओ_op(head.tag);
	अगर (!op) अणु
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: No one's waiting for tag %llu\n",
			     __func__, llu(head.tag));
		वापस ret;
	पूर्ण

	अगर (!copy_from_iter_full(&op->करोwncall, करोwncall_size, iter)) अणु
		gossip_err("%s: failed to copy downcall.\n", __func__);
		जाओ Efault;
	पूर्ण

	अगर (op->करोwncall.status)
		जाओ wakeup;

	/*
	 * We've successfully peeled off the head and the करोwncall.
	 * Something has gone awry अगर total करोesn't equal the
	 * sum of head_size, करोwncall_size and trailer_size.
	 */
	अगर ((head_size + करोwncall_size + op->करोwncall.trailer_size) != total) अणु
		gossip_err("%s: funky write, head_size:%d"
			   ": downcall_size:%d: trailer_size:%lld"
			   ": total size:%d:\n",
			   __func__,
			   head_size,
			   करोwncall_size,
			   op->करोwncall.trailer_size,
			   total);
		जाओ Efault;
	पूर्ण

	/* Only READसूची operations should have trailers. */
	अगर ((op->करोwncall.type != ORANGEFS_VFS_OP_READसूची) &&
	    (op->करोwncall.trailer_size != 0)) अणु
		gossip_err("%s: %x operation with trailer.",
			   __func__,
			   op->करोwncall.type);
		जाओ Efault;
	पूर्ण

	/* READसूची operations should always have trailers. */
	अगर ((op->करोwncall.type == ORANGEFS_VFS_OP_READसूची) &&
	    (op->करोwncall.trailer_size == 0)) अणु
		gossip_err("%s: %x operation with no trailer.",
			   __func__,
			   op->करोwncall.type);
		जाओ Efault;
	पूर्ण

	अगर (op->करोwncall.type != ORANGEFS_VFS_OP_READसूची)
		जाओ wakeup;

	op->करोwncall.trailer_buf = vzalloc(op->करोwncall.trailer_size);
	अगर (!op->करोwncall.trailer_buf)
		जाओ Enomem;

	अगर (!copy_from_iter_full(op->करोwncall.trailer_buf,
			         op->करोwncall.trailer_size, iter)) अणु
		gossip_err("%s: failed to copy trailer.\n", __func__);
		vमुक्त(op->करोwncall.trailer_buf);
		जाओ Efault;
	पूर्ण

wakeup:
	/*
	 * Return to vfs रुकोqueue, and back to service_operation
	 * through रुको_क्रम_matching_करोwncall.
	 */
	spin_lock(&op->lock);
	अगर (unlikely(op_is_cancel(op))) अणु
		spin_unlock(&op->lock);
		put_cancel(op);
	पूर्ण अन्यथा अगर (unlikely(op_state_given_up(op))) अणु
		spin_unlock(&op->lock);
		complete(&op->रुकोq);
	पूर्ण अन्यथा अणु
		set_op_state_serviced(op);
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: op:%s: op_state:%d: process:%s:\n",
			     __func__,
			     get_opname_string(op),
			     op->op_state,
			     current->comm);
		spin_unlock(&op->lock);
	पूर्ण
	वापस ret;

Efault:
	op->करोwncall.status = -(ORANGEFS_ERROR_BIT | 9);
	ret = -EFAULT;
	जाओ wakeup;

Enomem:
	op->करोwncall.status = -(ORANGEFS_ERROR_BIT | 8);
	ret = -ENOMEM;
	जाओ wakeup;
पूर्ण

/*
 * NOTE: माला_लो called when the last reference to this device is dropped.
 * Using the खोलो_access_count variable, we enक्रमce a reference count
 * on this file so that it can be खोलोed by only one process at a समय.
 * the devreq_mutex is used to make sure all i/o has completed
 * beक्रमe we call orangefs_bufmap_finalize, and similar such tricky
 * situations
 */
अटल पूर्णांक orangefs_devreq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक unmounted = 0;

	gossip_debug(GOSSIP_DEV_DEBUG,
		     "%s:pvfs2-client-core: exiting, closing device\n",
		     __func__);

	mutex_lock(&devreq_mutex);
	orangefs_bufmap_finalize();

	खोलो_access_count = -1;

	unmounted = mark_all_pending_mounts();
	gossip_debug(GOSSIP_DEV_DEBUG, "ORANGEFS Device Close: Filesystem(s) %s\n",
		     (unmounted ? "UNMOUNTED" : "MOUNTED"));

	purge_रुकोing_ops();
	purge_inprogress_ops();

	orangefs_bufmap_run_करोwn();

	gossip_debug(GOSSIP_DEV_DEBUG,
		     "pvfs2-client-core: device close complete\n");
	खोलो_access_count = 0;
	orangefs_userspace_version = 0;
	mutex_unlock(&devreq_mutex);
	वापस 0;
पूर्ण

पूर्णांक is_daemon_in_service(व्योम)
अणु
	पूर्णांक in_service;

	/*
	 * What this function करोes is checks अगर client-core is alive
	 * based on the access count we मुख्यtain on the device.
	 */
	mutex_lock(&devreq_mutex);
	in_service = खोलो_access_count == 1 ? 0 : -EIO;
	mutex_unlock(&devreq_mutex);
	वापस in_service;
पूर्ण

bool __is_daemon_in_service(व्योम)
अणु
	वापस खोलो_access_count == 1;
पूर्ण

अटल अंतरभूत दीर्घ check_ioctl_command(अचिन्हित पूर्णांक command)
अणु
	/* Check क्रम valid ioctl codes */
	अगर (_IOC_TYPE(command) != ORANGEFS_DEV_MAGIC) अणु
		gossip_err("device ioctl magic numbers don't match! Did you rebuild pvfs2-client-core/libpvfs2? [cmd %x, magic %x != %x]\n",
			command,
			_IOC_TYPE(command),
			ORANGEFS_DEV_MAGIC);
		वापस -EINVAL;
	पूर्ण
	/* and valid ioctl commands */
	अगर (_IOC_NR(command) >= ORANGEFS_DEV_MAXNR || _IOC_NR(command) <= 0) अणु
		gossip_err("Invalid ioctl command number [%d >= %d]\n",
			   _IOC_NR(command), ORANGEFS_DEV_MAXNR);
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ dispatch_ioctl_command(अचिन्हित पूर्णांक command, अचिन्हित दीर्घ arg)
अणु
	अटल __s32 magic = ORANGEFS_DEVREQ_MAGIC;
	अटल __s32 max_up_size = MAX_DEV_REQ_UPSIZE;
	अटल __s32 max_करोwn_size = MAX_DEV_REQ_DOWNSIZE;
	काष्ठा ORANGEFS_dev_map_desc user_desc;
	पूर्णांक ret = 0;
	पूर्णांक upstream_kmod = 1;
	काष्ठा orangefs_sb_info_s *orangefs_sb;

	/* mपंचांगoore: add locking here */

	चयन (command) अणु
	हाल ORANGEFS_DEV_GET_MAGIC:
		वापस ((put_user(magic, (__s32 __user *) arg) == -EFAULT) ?
			-EIO :
			0);
	हाल ORANGEFS_DEV_GET_MAX_UPSIZE:
		वापस ((put_user(max_up_size,
				  (__s32 __user *) arg) == -EFAULT) ?
					-EIO :
					0);
	हाल ORANGEFS_DEV_GET_MAX_DOWNSIZE:
		वापस ((put_user(max_करोwn_size,
				  (__s32 __user *) arg) == -EFAULT) ?
					-EIO :
					0);
	हाल ORANGEFS_DEV_MAP:
		ret = copy_from_user(&user_desc,
				     (काष्ठा ORANGEFS_dev_map_desc __user *)
				     arg,
				     माप(काष्ठा ORANGEFS_dev_map_desc));
		/* WTF -EIO and not -EFAULT? */
		वापस ret ? -EIO : orangefs_bufmap_initialize(&user_desc);
	हाल ORANGEFS_DEV_REMOUNT_ALL:
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: got ORANGEFS_DEV_REMOUNT_ALL\n",
			     __func__);

		/*
		 * remount all mounted orangefs volumes to regain the lost
		 * dynamic mount tables (अगर any) -- NOTE: this is करोne
		 * without keeping the superblock list locked due to the
		 * upcall/करोwncall रुकोing.  also, the request mutex is
		 * used to ensure that no operations will be serviced until
		 * all of the remounts are serviced (to aव्योम ops between
		 * mounts to fail)
		 */
		ret = mutex_lock_पूर्णांकerruptible(&orangefs_request_mutex);
		अगर (ret < 0)
			वापस ret;
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: priority remount in progress\n",
			     __func__);
		spin_lock(&orangefs_superblocks_lock);
		list_क्रम_each_entry(orangefs_sb, &orangefs_superblocks, list) अणु
			/*
			 * We have to drop the spinlock, so entries can be
			 * हटाओd.  They can't be मुक्तd, though, so we just
			 * keep the क्रमward poपूर्णांकers and zero the back ones -
			 * that way we can get to the rest of the list.
			 */
			अगर (!orangefs_sb->list.prev)
				जारी;
			gossip_debug(GOSSIP_DEV_DEBUG,
				     "%s: Remounting SB %p\n",
				     __func__,
				     orangefs_sb);

			spin_unlock(&orangefs_superblocks_lock);
			ret = orangefs_remount(orangefs_sb);
			spin_lock(&orangefs_superblocks_lock);
			अगर (ret) अणु
				gossip_debug(GOSSIP_DEV_DEBUG,
					     "SB %p remount failed\n",
					     orangefs_sb);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&orangefs_superblocks_lock);
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: priority remount complete\n",
			     __func__);
		mutex_unlock(&orangefs_request_mutex);
		वापस ret;

	हाल ORANGEFS_DEV_UPSTREAM:
		ret = copy_to_user((व्योम __user *)arg,
				    &upstream_kmod,
				    माप(upstream_kmod));

		अगर (ret != 0)
			वापस -EIO;
		अन्यथा
			वापस ret;

	हाल ORANGEFS_DEV_CLIENT_MASK:
		वापस orangefs_debugfs_new_client_mask((व्योम __user *)arg);
	हाल ORANGEFS_DEV_CLIENT_STRING:
		वापस orangefs_debugfs_new_client_string((व्योम __user *)arg);
	हाल ORANGEFS_DEV_DEBUG:
		वापस orangefs_debugfs_new_debug((व्योम __user *)arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल दीर्घ orangefs_devreq_ioctl(काष्ठा file *file,
			       अचिन्हित पूर्णांक command, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	/* Check क्रम properly स्थिरructed commands */
	ret = check_ioctl_command(command);
	अगर (ret < 0)
		वापस (पूर्णांक)ret;

	वापस (पूर्णांक)dispatch_ioctl_command(command, arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT		/* CONFIG_COMPAT is in .config */

/*  Compat काष्ठाure क्रम the ORANGEFS_DEV_MAP ioctl */
काष्ठा ORANGEFS_dev_map_desc32 अणु
	compat_uptr_t ptr;
	__s32 total_size;
	__s32 size;
	__s32 count;
पूर्ण;

/*
 * 32 bit user-space apps' ioctl handlers when kernel modules
 * is compiled as a 64 bit one
 */
अटल दीर्घ orangefs_devreq_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ args)
अणु
	दीर्घ ret;

	/* Check क्रम properly स्थिरructed commands */
	ret = check_ioctl_command(cmd);
	अगर (ret < 0)
		वापस ret;
	अगर (cmd == ORANGEFS_DEV_MAP) अणु
		काष्ठा ORANGEFS_dev_map_desc desc;
		काष्ठा ORANGEFS_dev_map_desc32 d32;

		अगर (copy_from_user(&d32, (व्योम __user *)args, माप(d32)))
			वापस -EFAULT;

		desc.ptr = compat_ptr(d32.ptr);
		desc.total_size = d32.total_size;
		desc.size = d32.size;
		desc.count = d32.count;
		वापस orangefs_bufmap_initialize(&desc);
	पूर्ण
	/* no other ioctl requires translation */
	वापस dispatch_ioctl_command(cmd, args);
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT is in .config */

अटल __poll_t orangefs_devreq_poll(काष्ठा file *file,
				      काष्ठा poll_table_काष्ठा *poll_table)
अणु
	__poll_t poll_revent_mask = 0;

	poll_रुको(file, &orangefs_request_list_रुकोq, poll_table);

	अगर (!list_empty(&orangefs_request_list))
		poll_revent_mask |= EPOLLIN;
	वापस poll_revent_mask;
पूर्ण

/* the asचिन्हित अक्षरacter device major number */
अटल पूर्णांक orangefs_dev_major;

अटल स्थिर काष्ठा file_operations orangefs_devreq_file_operations = अणु
	.owner = THIS_MODULE,
	.पढ़ो = orangefs_devreq_पढ़ो,
	.ग_लिखो_iter = orangefs_devreq_ग_लिखो_iter,
	.खोलो = orangefs_devreq_खोलो,
	.release = orangefs_devreq_release,
	.unlocked_ioctl = orangefs_devreq_ioctl,

#अगर_घोषित CONFIG_COMPAT		/* CONFIG_COMPAT is in .config */
	.compat_ioctl = orangefs_devreq_compat_ioctl,
#पूर्ण_अगर
	.poll = orangefs_devreq_poll
पूर्ण;

/*
 * Initialize orangefs device specअगरic state:
 * Must be called at module load समय only
 */
पूर्णांक orangefs_dev_init(व्योम)
अणु
	/* रेजिस्टर orangefs-req device  */
	orangefs_dev_major = रेजिस्टर_chrdev(0,
					  ORANGEFS_REQDEVICE_NAME,
					  &orangefs_devreq_file_operations);
	अगर (orangefs_dev_major < 0) अणु
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "Failed to register /dev/%s (error %d)\n",
			     ORANGEFS_REQDEVICE_NAME, orangefs_dev_major);
		वापस orangefs_dev_major;
	पूर्ण

	gossip_debug(GOSSIP_DEV_DEBUG,
		     "*** /dev/%s character device registered ***\n",
		     ORANGEFS_REQDEVICE_NAME);
	gossip_debug(GOSSIP_DEV_DEBUG, "'mknod /dev/%s c %d 0'.\n",
		     ORANGEFS_REQDEVICE_NAME, orangefs_dev_major);
	वापस 0;
पूर्ण

व्योम orangefs_dev_cleanup(व्योम)
अणु
	unरेजिस्टर_chrdev(orangefs_dev_major, ORANGEFS_REQDEVICE_NAME);
	gossip_debug(GOSSIP_DEV_DEBUG,
		     "*** /dev/%s character device unregistered ***\n",
		     ORANGEFS_REQDEVICE_NAME);
पूर्ण
