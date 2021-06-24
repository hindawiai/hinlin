<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"

/* tags asचिन्हित to kernel upcall operations */
अटल __u64 next_tag_value;
अटल DEFINE_SPINLOCK(next_tag_value_lock);

/* the orangefs memory caches */

/* a cache क्रम orangefs upcall/करोwncall operations */
अटल काष्ठा kmem_cache *op_cache;

पूर्णांक op_cache_initialize(व्योम)
अणु
	op_cache = kmem_cache_create("orangefs_op_cache",
				     माप(काष्ठा orangefs_kernel_op_s),
				     0,
				     ORANGEFS_CACHE_CREATE_FLAGS,
				     शून्य);

	अगर (!op_cache) अणु
		gossip_err("Cannot create orangefs_op_cache\n");
		वापस -ENOMEM;
	पूर्ण

	/* initialize our atomic tag counter */
	spin_lock(&next_tag_value_lock);
	next_tag_value = 100;
	spin_unlock(&next_tag_value_lock);
	वापस 0;
पूर्ण

पूर्णांक op_cache_finalize(व्योम)
अणु
	kmem_cache_destroy(op_cache);
	वापस 0;
पूर्ण

अक्षर *get_opname_string(काष्ठा orangefs_kernel_op_s *new_op)
अणु
	अगर (new_op) अणु
		__s32 type = new_op->upcall.type;

		अगर (type == ORANGEFS_VFS_OP_खाता_IO)
			वापस "OP_FILE_IO";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_LOOKUP)
			वापस "OP_LOOKUP";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_CREATE)
			वापस "OP_CREATE";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_GETATTR)
			वापस "OP_GETATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_REMOVE)
			वापस "OP_REMOVE";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_MKसूची)
			वापस "OP_MKDIR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_READसूची)
			वापस "OP_READDIR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_READसूचीPLUS)
			वापस "OP_READDIRPLUS";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_SETATTR)
			वापस "OP_SETATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_SYMLINK)
			वापस "OP_SYMLINK";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_RENAME)
			वापस "OP_RENAME";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_STATFS)
			वापस "OP_STATFS";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_TRUNCATE)
			वापस "OP_TRUNCATE";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_RA_FLUSH)
			वापस "OP_RA_FLUSH";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_FS_MOUNT)
			वापस "OP_FS_MOUNT";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_FS_UMOUNT)
			वापस "OP_FS_UMOUNT";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_GETXATTR)
			वापस "OP_GETXATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_SETXATTR)
			वापस "OP_SETXATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_LISTXATTR)
			वापस "OP_LISTXATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_REMOVEXATTR)
			वापस "OP_REMOVEXATTR";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_PARAM)
			वापस "OP_PARAM";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_PERF_COUNT)
			वापस "OP_PERF_COUNT";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_CANCEL)
			वापस "OP_CANCEL";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_FSYNC)
			वापस "OP_FSYNC";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_FSKEY)
			वापस "OP_FSKEY";
		अन्यथा अगर (type == ORANGEFS_VFS_OP_FEATURES)
			वापस "OP_FEATURES";
	पूर्ण
	वापस "OP_UNKNOWN?";
पूर्ण

व्योम orangefs_new_tag(काष्ठा orangefs_kernel_op_s *op)
अणु
	spin_lock(&next_tag_value_lock);
	op->tag = next_tag_value++;
	अगर (next_tag_value == 0)
		next_tag_value = 100;
	spin_unlock(&next_tag_value_lock);
पूर्ण

काष्ठा orangefs_kernel_op_s *op_alloc(__s32 type)
अणु
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;

	new_op = kmem_cache_zalloc(op_cache, GFP_KERNEL);
	अगर (new_op) अणु
		INIT_LIST_HEAD(&new_op->list);
		spin_lock_init(&new_op->lock);
		init_completion(&new_op->रुकोq);

		new_op->upcall.type = ORANGEFS_VFS_OP_INVALID;
		new_op->करोwncall.type = ORANGEFS_VFS_OP_INVALID;
		new_op->करोwncall.status = -1;

		new_op->op_state = OP_VFS_STATE_UNKNOWN;

		/* initialize the op specअगरic tag and upcall credentials */
		orangefs_new_tag(new_op);
		new_op->upcall.type = type;
		new_op->attempts = 0;
		gossip_debug(GOSSIP_CACHE_DEBUG,
			     "Alloced OP (%p: %llu %s)\n",
			     new_op,
			     llu(new_op->tag),
			     get_opname_string(new_op));

		new_op->upcall.uid = from_kuid(&init_user_ns,
					       current_fsuid());

		new_op->upcall.gid = from_kgid(&init_user_ns,
					       current_fsgid());
	पूर्ण अन्यथा अणु
		gossip_err("op_alloc: kmem_cache_zalloc failed!\n");
	पूर्ण
	वापस new_op;
पूर्ण

व्योम op_release(काष्ठा orangefs_kernel_op_s *orangefs_op)
अणु
	अगर (orangefs_op) अणु
		gossip_debug(GOSSIP_CACHE_DEBUG,
			     "Releasing OP (%p: %llu)\n",
			     orangefs_op,
			     llu(orangefs_op->tag));
		kmem_cache_मुक्त(op_cache, orangefs_op);
	पूर्ण अन्यथा अणु
		gossip_err("NULL pointer in op_release\n");
	पूर्ण
पूर्ण
