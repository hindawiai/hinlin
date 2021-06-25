<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 * Copyright 2018 Omnibond Systems, L.L.C.
 *
 * See COPYING in top-level directory.
 */

/*
 *  Linux VFS extended attribute operations.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/xattr.h>
#समावेश <linux/hashtable.h>

#घोषणा SYSTEM_ORANGEFS_KEY "system.pvfs2."
#घोषणा SYSTEM_ORANGEFS_KEY_LEN 13

/*
 * this function वापसs
 *   0 अगर the key corresponding to name is not meant to be prपूर्णांकed as part
 *     of a listxattr.
 *   1 अगर the key corresponding to name is meant to be वापसed as part of
 *     a listxattr.
 * The ones that start SYSTEM_ORANGEFS_KEY are the ones to aव्योम prपूर्णांकing.
 */
अटल पूर्णांक is_reserved_key(स्थिर अक्षर *key, माप_प्रकार size)
अणु

	अगर (size < SYSTEM_ORANGEFS_KEY_LEN)
		वापस 1;

	वापस म_भेदन(key, SYSTEM_ORANGEFS_KEY, SYSTEM_ORANGEFS_KEY_LEN) ?  1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक convert_to_पूर्णांकernal_xattr_flags(पूर्णांक setxattr_flags)
अणु
	पूर्णांक पूर्णांकernal_flag = 0;

	अगर (setxattr_flags & XATTR_REPLACE) अणु
		/* Attribute must exist! */
		पूर्णांकernal_flag = ORANGEFS_XATTR_REPLACE;
	पूर्ण अन्यथा अगर (setxattr_flags & XATTR_CREATE) अणु
		/* Attribute must not exist */
		पूर्णांकernal_flag = ORANGEFS_XATTR_CREATE;
	पूर्ण
	वापस पूर्णांकernal_flag;
पूर्ण

अटल अचिन्हित पूर्णांक xattr_key(स्थिर अक्षर *key)
अणु
	अचिन्हित पूर्णांक i = 0;
	जबतक (key)
		i += *key++;
	वापस i % 16;
पूर्ण

अटल काष्ठा orangefs_cached_xattr *find_cached_xattr(काष्ठा inode *inode,
    स्थिर अक्षर *key)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_cached_xattr *cx;
	काष्ठा hlist_head *h;
	काष्ठा hlist_node *पंचांगp;
	h = &orangefs_inode->xattr_cache[xattr_key(key)];
	अगर (hlist_empty(h))
		वापस शून्य;
	hlist_क्रम_each_entry_safe(cx, पंचांगp, h, node) अणु
/*		अगर (!समय_beक्रमe(jअगरfies, cx->समयout)) अणु
			hlist_del(&cx->node);
			kमुक्त(cx);
			जारी;
		पूर्ण*/
		अगर (!म_भेद(cx->key, key))
			वापस cx;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Tries to get a specअगरied key's attributes of a given
 * file पूर्णांकo a user-specअगरied buffer. Note that the getxattr
 * पूर्णांकerface allows क्रम the users to probe the size of an
 * extended attribute by passing in a value of 0 to size.
 * Thus our वापस value is always the size of the attribute
 * unless the key करोes not exist क्रम the file and/or अगर
 * there were errors in fetching the attribute value.
 */
sमाप_प्रकार orangefs_inode_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	काष्ठा orangefs_cached_xattr *cx;
	sमाप_प्रकार ret = -ENOMEM;
	sमाप_प्रकार length = 0;
	पूर्णांक fsuid;
	पूर्णांक fsgid;

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "%s: name %s, buffer_size %zd\n",
		     __func__, name, size);

	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;

	अगर (म_माप(name) >= ORANGEFS_MAX_XATTR_NAMELEN)
		वापस -EINVAL;

	fsuid = from_kuid(&init_user_ns, current_fsuid());
	fsgid = from_kgid(&init_user_ns, current_fsgid());

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "getxattr on inode %pU, name %s "
		     "(uid %o, gid %o)\n",
		     get_khandle_from_ino(inode),
		     name,
		     fsuid,
		     fsgid);

	करोwn_पढ़ो(&orangefs_inode->xattr_sem);

	cx = find_cached_xattr(inode, name);
	अगर (cx && समय_beक्रमe(jअगरfies, cx->समयout)) अणु
		अगर (cx->length == -1) अणु
			ret = -ENODATA;
			जाओ out_unlock;
		पूर्ण अन्यथा अणु
			अगर (size == 0) अणु
				ret = cx->length;
				जाओ out_unlock;
			पूर्ण
			अगर (cx->length > size) अणु
				ret = -दुस्फल;
				जाओ out_unlock;
			पूर्ण
			स_नकल(buffer, cx->val, cx->length);
			स_रखो(buffer + cx->length, 0, size - cx->length);
			ret = cx->length;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	new_op = op_alloc(ORANGEFS_VFS_OP_GETXATTR);
	अगर (!new_op)
		जाओ out_unlock;

	new_op->upcall.req.getxattr.refn = orangefs_inode->refn;
	म_नकल(new_op->upcall.req.getxattr.key, name);

	/*
	 * NOTE: Although keys are meant to be शून्य terminated textual
	 * strings, I am going to explicitly pass the length just in हाल
	 * we change this later on...
	 */
	new_op->upcall.req.getxattr.key_sz = म_माप(name) + 1;

	ret = service_operation(new_op, "orangefs_inode_getxattr",
				get_पूर्णांकerruptible_flag(inode));
	अगर (ret != 0) अणु
		अगर (ret == -ENOENT) अणु
			ret = -ENODATA;
			gossip_debug(GOSSIP_XATTR_DEBUG,
				     "orangefs_inode_getxattr: inode %pU key %s"
				     " does not exist!\n",
				     get_khandle_from_ino(inode),
				     (अक्षर *)new_op->upcall.req.getxattr.key);
			cx = kदो_स्मृति(माप *cx, GFP_KERNEL);
			अगर (cx) अणु
				म_नकल(cx->key, name);
				cx->length = -1;
				cx->समयout = jअगरfies +
				    orangefs_getattr_समयout_msecs*HZ/1000;
				hash_add(orangefs_inode->xattr_cache, &cx->node,
				    xattr_key(cx->key));
			पूर्ण
		पूर्ण
		जाओ out_release_op;
	पूर्ण

	/*
	 * Length वापसed includes null terminator.
	 */
	length = new_op->करोwncall.resp.getxattr.val_sz;

	/*
	 * Just वापस the length of the queried attribute.
	 */
	अगर (size == 0) अणु
		ret = length;
		जाओ out_release_op;
	पूर्ण

	/*
	 * Check to see अगर key length is > provided buffer size.
	 */
	अगर (length > size) अणु
		ret = -दुस्फल;
		जाओ out_release_op;
	पूर्ण

	स_नकल(buffer, new_op->करोwncall.resp.getxattr.val, length);
	स_रखो(buffer + length, 0, size - length);
	gossip_debug(GOSSIP_XATTR_DEBUG,
	     "orangefs_inode_getxattr: inode %pU "
	     "key %s key_sz %d, val_len %d\n",
	     get_khandle_from_ino(inode),
	     (अक्षर *)new_op->
		upcall.req.getxattr.key,
		     (पूर्णांक)new_op->
		upcall.req.getxattr.key_sz,
	     (पूर्णांक)ret);

	ret = length;

	अगर (cx) अणु
		म_नकल(cx->key, name);
		स_नकल(cx->val, buffer, length);
		cx->length = length;
		cx->समयout = jअगरfies + HZ;
	पूर्ण अन्यथा अणु
		cx = kदो_स्मृति(माप *cx, GFP_KERNEL);
		अगर (cx) अणु
			म_नकल(cx->key, name);
			स_नकल(cx->val, buffer, length);
			cx->length = length;
			cx->समयout = jअगरfies + HZ;
			hash_add(orangefs_inode->xattr_cache, &cx->node,
			    xattr_key(cx->key));
		पूर्ण
	पूर्ण

out_release_op:
	op_release(new_op);
out_unlock:
	up_पढ़ो(&orangefs_inode->xattr_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_inode_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				      पूर्णांक flags)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	काष्ठा orangefs_cached_xattr *cx;
	काष्ठा hlist_head *h;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक ret = -ENOMEM;

	अगर (म_माप(name) >= ORANGEFS_MAX_XATTR_NAMELEN)
		वापस -EINVAL;

	करोwn_ग_लिखो(&orangefs_inode->xattr_sem);
	new_op = op_alloc(ORANGEFS_VFS_OP_REMOVEXATTR);
	अगर (!new_op)
		जाओ out_unlock;

	new_op->upcall.req.हटाओxattr.refn = orangefs_inode->refn;
	/*
	 * NOTE: Although keys are meant to be शून्य terminated
	 * textual strings, I am going to explicitly pass the
	 * length just in हाल we change this later on...
	 */
	म_नकल(new_op->upcall.req.हटाओxattr.key, name);
	new_op->upcall.req.हटाओxattr.key_sz = म_माप(name) + 1;

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_removexattr: key %s, key_sz %d\n",
		     (अक्षर *)new_op->upcall.req.हटाओxattr.key,
		     (पूर्णांक)new_op->upcall.req.हटाओxattr.key_sz);

	ret = service_operation(new_op,
				"orangefs_inode_removexattr",
				get_पूर्णांकerruptible_flag(inode));
	अगर (ret == -ENOENT) अणु
		/*
		 * Request to replace a non-existent attribute is an error.
		 */
		अगर (flags & XATTR_REPLACE)
			ret = -ENODATA;
		अन्यथा
			ret = 0;
	पूर्ण

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_removexattr: returning %d\n", ret);

	op_release(new_op);

	h = &orangefs_inode->xattr_cache[xattr_key(name)];
	hlist_क्रम_each_entry_safe(cx, पंचांगp, h, node) अणु
		अगर (!म_भेद(cx->key, name)) अणु
			hlist_del(&cx->node);
			kमुक्त(cx);
			अवरोध;
		पूर्ण
	पूर्ण

out_unlock:
	up_ग_लिखो(&orangefs_inode->xattr_sem);
	वापस ret;
पूर्ण

/*
 * Tries to set an attribute क्रम a given key on a file.
 *
 * Returns a -ve number on error and 0 on success.  Key is text, but value
 * can be binary!
 */
पूर्णांक orangefs_inode_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			    स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक पूर्णांकernal_flag = 0;
	काष्ठा orangefs_cached_xattr *cx;
	काष्ठा hlist_head *h;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक ret = -ENOMEM;

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "%s: name %s, buffer_size %zd\n",
		     __func__, name, size);

	अगर (size > ORANGEFS_MAX_XATTR_VALUELEN)
		वापस -EINVAL;
	अगर (म_माप(name) >= ORANGEFS_MAX_XATTR_NAMELEN)
		वापस -EINVAL;

	पूर्णांकernal_flag = convert_to_पूर्णांकernal_xattr_flags(flags);

	/* This is equivalent to a हटाओxattr */
	अगर (size == 0 && !value) अणु
		gossip_debug(GOSSIP_XATTR_DEBUG,
			     "removing xattr (%s)\n",
			     name);
		वापस orangefs_inode_हटाओxattr(inode, name, flags);
	पूर्ण

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "setxattr on inode %pU, name %s\n",
		     get_khandle_from_ino(inode),
		     name);

	करोwn_ग_लिखो(&orangefs_inode->xattr_sem);
	new_op = op_alloc(ORANGEFS_VFS_OP_SETXATTR);
	अगर (!new_op)
		जाओ out_unlock;


	new_op->upcall.req.setxattr.refn = orangefs_inode->refn;
	new_op->upcall.req.setxattr.flags = पूर्णांकernal_flag;
	/*
	 * NOTE: Although keys are meant to be शून्य terminated textual
	 * strings, I am going to explicitly pass the length just in
	 * हाल we change this later on...
	 */
	म_नकल(new_op->upcall.req.setxattr.keyval.key, name);
	new_op->upcall.req.setxattr.keyval.key_sz = म_माप(name) + 1;
	स_नकल(new_op->upcall.req.setxattr.keyval.val, value, size);
	new_op->upcall.req.setxattr.keyval.val_sz = size;

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_setxattr: key %s, key_sz %d "
		     " value size %zd\n",
		     (अक्षर *)new_op->upcall.req.setxattr.keyval.key,
		     (पूर्णांक)new_op->upcall.req.setxattr.keyval.key_sz,
		     size);

	ret = service_operation(new_op,
				"orangefs_inode_setxattr",
				get_पूर्णांकerruptible_flag(inode));

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_setxattr: returning %d\n",
		     ret);

	/* when request is serviced properly, मुक्त req op काष्ठा */
	op_release(new_op);

	h = &orangefs_inode->xattr_cache[xattr_key(name)];
	hlist_क्रम_each_entry_safe(cx, पंचांगp, h, node) अणु
		अगर (!म_भेद(cx->key, name)) अणु
			hlist_del(&cx->node);
			kमुक्त(cx);
			अवरोध;
		पूर्ण
	पूर्ण

out_unlock:
	up_ग_लिखो(&orangefs_inode->xattr_sem);
	वापस ret;
पूर्ण

/*
 * Tries to get a specअगरied object's keys पूर्णांकo a user-specअगरied buffer of a
 * given size.  Note that like the previous instances of xattr routines, this
 * also allows you to pass in a शून्य poपूर्णांकer and 0 size to probe the size क्रम
 * subsequent memory allocations. Thus our वापस value is always the size of
 * all the keys unless there were errors in fetching the keys!
 */
sमाप_प्रकार orangefs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	__u64 token = ORANGEFS_ITERATE_START;
	sमाप_प्रकार ret = -ENOMEM;
	sमाप_प्रकार total = 0;
	पूर्णांक count_keys = 0;
	पूर्णांक key_size;
	पूर्णांक i = 0;
	पूर्णांक वापसed_count = 0;

	अगर (size > 0 && !buffer) अणु
		gossip_err("%s: bogus NULL pointers\n", __func__);
		वापस -EINVAL;
	पूर्ण

	करोwn_पढ़ो(&orangefs_inode->xattr_sem);
	new_op = op_alloc(ORANGEFS_VFS_OP_LISTXATTR);
	अगर (!new_op)
		जाओ out_unlock;

	अगर (buffer && size > 0)
		स_रखो(buffer, 0, size);

try_again:
	key_size = 0;
	new_op->upcall.req.listxattr.refn = orangefs_inode->refn;
	new_op->upcall.req.listxattr.token = token;
	new_op->upcall.req.listxattr.requested_count =
	    (size == 0) ? 0 : ORANGEFS_MAX_XATTR_LISTLEN;
	ret = service_operation(new_op, __func__,
				get_पूर्णांकerruptible_flag(inode));
	अगर (ret != 0)
		जाओ करोne;

	अगर (size == 0) अणु
		/*
		 * This is a bit of a big upper limit, but I did not want to
		 * spend too much समय getting this correct, since users end
		 * up allocating memory rather than us...
		 */
		total = new_op->करोwncall.resp.listxattr.वापसed_count *
			ORANGEFS_MAX_XATTR_NAMELEN;
		जाओ करोne;
	पूर्ण

	वापसed_count = new_op->करोwncall.resp.listxattr.वापसed_count;
	अगर (वापसed_count < 0 ||
	    वापसed_count > ORANGEFS_MAX_XATTR_LISTLEN) अणु
		gossip_err("%s: impossible value for returned_count:%d:\n",
		__func__,
		वापसed_count);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/*
	 * Check to see how much can be fit in the buffer. Fit only whole keys.
	 */
	क्रम (i = 0; i < वापसed_count; i++) अणु
		अगर (new_op->करोwncall.resp.listxattr.lengths[i] < 0 ||
		    new_op->करोwncall.resp.listxattr.lengths[i] >
		    ORANGEFS_MAX_XATTR_NAMELEN) अणु
			gossip_err("%s: impossible value for lengths[%d]\n",
			    __func__,
			    new_op->करोwncall.resp.listxattr.lengths[i]);
			ret = -EIO;
			जाओ करोne;
		पूर्ण
		अगर (total + new_op->करोwncall.resp.listxattr.lengths[i] > size)
			जाओ करोne;

		/*
		 * Since many dumb programs try to setxattr() on our reserved
		 * xattrs this is a feeble attempt at defeating those by not
		 * listing them in the output of listxattr.. sigh
		 */
		अगर (is_reserved_key(new_op->करोwncall.resp.listxattr.key +
				    key_size,
				    new_op->करोwncall.resp.
					listxattr.lengths[i])) अणु
			gossip_debug(GOSSIP_XATTR_DEBUG, "Copying key %d -> %s\n",
					i, new_op->करोwncall.resp.listxattr.key +
						key_size);
			स_नकल(buffer + total,
				new_op->करोwncall.resp.listxattr.key + key_size,
				new_op->करोwncall.resp.listxattr.lengths[i]);
			total += new_op->करोwncall.resp.listxattr.lengths[i];
			count_keys++;
		पूर्ण अन्यथा अणु
			gossip_debug(GOSSIP_XATTR_DEBUG, "[RESERVED] key %d -> %s\n",
					i, new_op->करोwncall.resp.listxattr.key +
						key_size);
		पूर्ण
		key_size += new_op->करोwncall.resp.listxattr.lengths[i];
	पूर्ण

	/*
	 * Since the buffer was large enough, we might have to जारी
	 * fetching more keys!
	 */
	token = new_op->करोwncall.resp.listxattr.token;
	अगर (token != ORANGEFS_ITERATE_END)
		जाओ try_again;

करोne:
	gossip_debug(GOSSIP_XATTR_DEBUG, "%s: returning %d"
		     " [size of buffer %ld] (filled in %d keys)\n",
		     __func__,
		     ret ? (पूर्णांक)ret : (पूर्णांक)total,
		     (दीर्घ)size,
		     count_keys);
	op_release(new_op);
	अगर (ret == 0)
		ret = total;
out_unlock:
	up_पढ़ो(&orangefs_inode->xattr_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_xattr_set_शेष(स्थिर काष्ठा xattr_handler *handler,
				      काष्ठा user_namespace *mnt_userns,
				      काष्ठा dentry *unused,
				      काष्ठा inode *inode,
				      स्थिर अक्षर *name,
				      स्थिर व्योम *buffer,
				      माप_प्रकार size,
				      पूर्णांक flags)
अणु
	वापस orangefs_inode_setxattr(inode, name, buffer, size, flags);
पूर्ण

अटल पूर्णांक orangefs_xattr_get_शेष(स्थिर काष्ठा xattr_handler *handler,
				      काष्ठा dentry *unused,
				      काष्ठा inode *inode,
				      स्थिर अक्षर *name,
				      व्योम *buffer,
				      माप_प्रकार size)
अणु
	वापस orangefs_inode_getxattr(inode, name, buffer, size);

पूर्ण

अटल स्थिर काष्ठा xattr_handler orangefs_xattr_शेष_handler = अणु
	.prefix = "",  /* match any name => handlers called with full name */
	.get = orangefs_xattr_get_शेष,
	.set = orangefs_xattr_set_शेष,
पूर्ण;

स्थिर काष्ठा xattr_handler *orangefs_xattr_handlers[] = अणु
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
	&orangefs_xattr_शेष_handler,
	शून्य
पूर्ण;
