<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

/*
 *  Implementation of dentry (directory cache) functions.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"

/* Returns 1 अगर dentry can still be trusted, अन्यथा 0. */
अटल पूर्णांक orangefs_revalidate_lookup(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent_dentry = dget_parent(dentry);
	काष्ठा inode *parent_inode = parent_dentry->d_inode;
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(parent_inode);
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक ret = 0;
	पूर्णांक err = 0;

	gossip_debug(GOSSIP_DCACHE_DEBUG, "%s: attempting lookup.\n", __func__);

	new_op = op_alloc(ORANGEFS_VFS_OP_LOOKUP);
	अगर (!new_op)
		जाओ out_put_parent;

	new_op->upcall.req.lookup.sym_follow = ORANGEFS_LOOKUP_LINK_NO_FOLLOW;
	new_op->upcall.req.lookup.parent_refn = parent->refn;
	म_नकलन(new_op->upcall.req.lookup.d_name,
		dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);

	gossip_debug(GOSSIP_DCACHE_DEBUG,
		     "%s:%s:%d interrupt flag [%d]\n",
		     __खाता__,
		     __func__,
		     __LINE__,
		     get_पूर्णांकerruptible_flag(parent_inode));

	err = service_operation(new_op, "orangefs_lookup",
			get_पूर्णांकerruptible_flag(parent_inode));

	/* Positive dentry: reject अगर error or not the same inode. */
	अगर (inode) अणु
		अगर (err) अणु
			gossip_debug(GOSSIP_DCACHE_DEBUG,
			    "%s:%s:%d lookup failure.\n",
			    __खाता__, __func__, __LINE__);
			जाओ out_drop;
		पूर्ण
		अगर (!match_handle(new_op->करोwncall.resp.lookup.refn.khandle,
		    inode)) अणु
			gossip_debug(GOSSIP_DCACHE_DEBUG,
			    "%s:%s:%d no match.\n",
			    __खाता__, __func__, __LINE__);
			जाओ out_drop;
		पूर्ण

	/* Negative dentry: reject अगर success or error other than ENOENT. */
	पूर्ण अन्यथा अणु
		gossip_debug(GOSSIP_DCACHE_DEBUG, "%s: negative dentry.\n",
		    __func__);
		अगर (!err || err != -ENOENT) अणु
			अगर (new_op->करोwncall.status != 0)
				gossip_debug(GOSSIP_DCACHE_DEBUG,
				    "%s:%s:%d lookup failure.\n",
				    __खाता__, __func__, __LINE__);
			जाओ out_drop;
		पूर्ण
	पूर्ण

	orangefs_set_समयout(dentry);
	ret = 1;
out_release_op:
	op_release(new_op);
out_put_parent:
	dput(parent_dentry);
	वापस ret;
out_drop:
	gossip_debug(GOSSIP_DCACHE_DEBUG, "%s:%s:%d revalidate failed\n",
	    __खाता__, __func__, __LINE__);
	जाओ out_release_op;
पूर्ण

/*
 * Verअगरy that dentry is valid.
 *
 * Should वापस 1 अगर dentry can still be trusted, अन्यथा 0.
 */
अटल पूर्णांक orangefs_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय = (अचिन्हित दीर्घ) dentry->d_fsdata;

	अगर (समय_beक्रमe(jअगरfies, समय))
		वापस 1;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	gossip_debug(GOSSIP_DCACHE_DEBUG, "%s: called on dentry %p.\n",
		     __func__, dentry);

	/* skip root handle lookups. */
	अगर (dentry->d_inode && is_root_handle(dentry->d_inode))
		वापस 1;

	/*
	 * If this passes, the positive dentry still exists or the negative
	 * dentry still करोes not exist.
	 */
	अगर (!orangefs_revalidate_lookup(dentry))
		वापस 0;

	/* We करो not need to जारी with negative dentries. */
	अगर (!dentry->d_inode) अणु
		gossip_debug(GOSSIP_DCACHE_DEBUG,
		    "%s: negative dentry or positive dentry and inode valid.\n",
		    __func__);
		वापस 1;
	पूर्ण

	/* Now we must perक्रमm a getattr to validate the inode contents. */

	ret = orangefs_inode_check_changed(dentry->d_inode);
	अगर (ret < 0) अणु
		gossip_debug(GOSSIP_DCACHE_DEBUG, "%s:%s:%d getattr failure.\n",
		    __खाता__, __func__, __LINE__);
		वापस 0;
	पूर्ण
	वापस !ret;
पूर्ण

स्थिर काष्ठा dentry_operations orangefs_dentry_operations = अणु
	.d_revalidate = orangefs_d_revalidate,
पूर्ण;
