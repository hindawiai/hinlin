<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V9FS FID Management
 *
 *  Copyright (C) 2007 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2005, 2006 by Eric Van Hensbergen <ericvh@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/idr.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"

/**
 * v9fs_fid_add - add a fid to a dentry
 * @dentry: dentry that the fid is being added to
 * @fid: fid to add
 *
 */

अटल अंतरभूत व्योम __add_fid(काष्ठा dentry *dentry, काष्ठा p9_fid *fid)
अणु
	hlist_add_head(&fid->dlist, (काष्ठा hlist_head *)&dentry->d_fsdata);
पूर्ण

व्योम v9fs_fid_add(काष्ठा dentry *dentry, काष्ठा p9_fid *fid)
अणु
	spin_lock(&dentry->d_lock);
	__add_fid(dentry, fid);
	spin_unlock(&dentry->d_lock);
पूर्ण

/**
 * v9fs_fid_find_inode - search क्रम an खोलो fid off of the inode list
 * @inode: वापस a fid poपूर्णांकing to a specअगरic inode
 * @uid: वापस a fid beदीर्घing to the specअगरied user
 *
 */

अटल काष्ठा p9_fid *v9fs_fid_find_inode(काष्ठा inode *inode, kuid_t uid)
अणु
	काष्ठा hlist_head *h;
	काष्ठा p9_fid *fid, *ret = शून्य;

	p9_debug(P9_DEBUG_VFS, " inode: %p\n", inode);

	spin_lock(&inode->i_lock);
	h = (काष्ठा hlist_head *)&inode->i_निजी;
	hlist_क्रम_each_entry(fid, h, ilist) अणु
		अगर (uid_eq(fid->uid, uid)) अणु
			refcount_inc(&fid->count);
			ret = fid;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

/**
 * v9fs_खोलो_fid_add - add an खोलो fid to an inode
 * @dentry: inode that the fid is being added to
 * @fid: fid to add
 *
 */

व्योम v9fs_खोलो_fid_add(काष्ठा inode *inode, काष्ठा p9_fid *fid)
अणु
	spin_lock(&inode->i_lock);
	hlist_add_head(&fid->ilist, (काष्ठा hlist_head *)&inode->i_निजी);
	spin_unlock(&inode->i_lock);
पूर्ण


/**
 * v9fs_fid_find - retrieve a fid that beदीर्घs to the specअगरied uid
 * @dentry: dentry to look क्रम fid in
 * @uid: वापस fid that beदीर्घs to the specअगरied user
 * @any: अगर non-zero, वापस any fid associated with the dentry
 *
 */

अटल काष्ठा p9_fid *v9fs_fid_find(काष्ठा dentry *dentry, kuid_t uid, पूर्णांक any)
अणु
	काष्ठा p9_fid *fid, *ret;

	p9_debug(P9_DEBUG_VFS, " dentry: %pd (%p) uid %d any %d\n",
		 dentry, dentry, from_kuid(&init_user_ns, uid),
		 any);
	ret = शून्य;

	अगर (d_inode(dentry))
		ret = v9fs_fid_find_inode(d_inode(dentry), uid);

	/* we'll recheck under lock if there's anything to look in */
	अगर (!ret && dentry->d_fsdata) अणु
		काष्ठा hlist_head *h = (काष्ठा hlist_head *)&dentry->d_fsdata;
		spin_lock(&dentry->d_lock);
		hlist_क्रम_each_entry(fid, h, dlist) अणु
			अगर (any || uid_eq(fid->uid, uid)) अणु
				ret = fid;
				refcount_inc(&ret->count);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&dentry->d_lock);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * We need to hold v9ses->नाम_sem as दीर्घ as we hold references
 * to वापसed path array. Array element contain poपूर्णांकers to
 * dentry names.
 */
अटल पूर्णांक build_path_from_dentry(काष्ठा v9fs_session_info *v9ses,
				  काष्ठा dentry *dentry, स्थिर अचिन्हित अक्षर ***names)
अणु
	पूर्णांक n = 0, i;
	स्थिर अचिन्हित अक्षर **wnames;
	काष्ठा dentry *ds;

	क्रम (ds = dentry; !IS_ROOT(ds); ds = ds->d_parent)
		n++;

	wnames = kदो_स्मृति_array(n, माप(अक्षर *), GFP_KERNEL);
	अगर (!wnames)
		जाओ err_out;

	क्रम (ds = dentry, i = (n-1); i >= 0; i--, ds = ds->d_parent)
		wnames[i] = ds->d_name.name;

	*names = wnames;
	वापस n;
err_out:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा p9_fid *v9fs_fid_lookup_with_uid(काष्ठा dentry *dentry,
					       kuid_t uid, पूर्णांक any)
अणु
	काष्ठा dentry *ds;
	स्थिर अचिन्हित अक्षर **wnames, *uname;
	पूर्णांक i, n, l, clone, access;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid, *old_fid = शून्य;

	v9ses = v9fs_dentry2v9ses(dentry);
	access = v9ses->flags & V9FS_ACCESS_MASK;
	fid = v9fs_fid_find(dentry, uid, any);
	अगर (fid)
		वापस fid;
	/*
	 * we करोn't have a matching fid. To करो a TWALK we need
	 * parent fid. We need to prevent नाम when we want to
	 * look at the parent.
	 */
	करोwn_पढ़ो(&v9ses->नाम_sem);
	ds = dentry->d_parent;
	fid = v9fs_fid_find(ds, uid, any);
	अगर (fid) अणु
		/* Found the parent fid करो a lookup with that */
		काष्ठा p9_fid *ofid = fid;

		fid = p9_client_walk(ofid, 1, &dentry->d_name.name, 1);
		p9_client_clunk(ofid);
		जाओ fid_out;
	पूर्ण
	up_पढ़ो(&v9ses->नाम_sem);

	/* start from the root and try to करो a lookup */
	fid = v9fs_fid_find(dentry->d_sb->s_root, uid, any);
	अगर (!fid) अणु
		/* the user is not attached to the fs yet */
		अगर (access == V9FS_ACCESS_SINGLE)
			वापस ERR_PTR(-EPERM);

		अगर (v9fs_proto_करोtu(v9ses) || v9fs_proto_करोtl(v9ses))
				uname = शून्य;
		अन्यथा
			uname = v9ses->uname;

		fid = p9_client_attach(v9ses->clnt, शून्य, uname, uid,
				       v9ses->aname);
		अगर (IS_ERR(fid))
			वापस fid;

		v9fs_fid_add(dentry->d_sb->s_root, fid);
	पूर्ण
	/* If we are root ourself just वापस that */
	अगर (dentry->d_sb->s_root == dentry) अणु
		refcount_inc(&fid->count);
		वापस fid;
	पूर्ण
	/*
	 * Do a multipath walk with attached root.
	 * When walking parent we need to make sure we
	 * करोn't have a parallel नाम happening
	 */
	करोwn_पढ़ो(&v9ses->नाम_sem);
	n  = build_path_from_dentry(v9ses, dentry, &wnames);
	अगर (n < 0) अणु
		fid = ERR_PTR(n);
		जाओ err_out;
	पूर्ण
	clone = 1;
	i = 0;
	जबतक (i < n) अणु
		l = min(n - i, P9_MAXWELEM);
		/*
		 * We need to hold नाम lock when करोing a multipath
		 * walk to ensure none of the patch component change
		 */
		fid = p9_client_walk(fid, l, &wnames[i], clone);
		अगर (IS_ERR(fid)) अणु
			अगर (old_fid) अणु
				/*
				 * If we fail, clunk fid which are mapping
				 * to path component and not the last component
				 * of the path.
				 */
				p9_client_clunk(old_fid);
			पूर्ण
			kमुक्त(wnames);
			जाओ err_out;
		पूर्ण
		old_fid = fid;
		i += l;
		clone = 0;
	पूर्ण
	kमुक्त(wnames);
fid_out:
	अगर (!IS_ERR(fid)) अणु
		spin_lock(&dentry->d_lock);
		अगर (d_unhashed(dentry)) अणु
			spin_unlock(&dentry->d_lock);
			p9_client_clunk(fid);
			fid = ERR_PTR(-ENOENT);
		पूर्ण अन्यथा अणु
			__add_fid(dentry, fid);
			refcount_inc(&fid->count);
			spin_unlock(&dentry->d_lock);
		पूर्ण
	पूर्ण
err_out:
	up_पढ़ो(&v9ses->नाम_sem);
	वापस fid;
पूर्ण

/**
 * v9fs_fid_lookup - lookup क्रम a fid, try to walk अगर not found
 * @dentry: dentry to look क्रम fid in
 *
 * Look क्रम a fid in the specअगरied dentry क्रम the current user.
 * If no fid is found, try to create one walking from a fid from the parent
 * dentry (अगर it has one), or the root dentry. If the user haven't accessed
 * the fs yet, attach now and walk from the root.
 */

काष्ठा p9_fid *v9fs_fid_lookup(काष्ठा dentry *dentry)
अणु
	kuid_t uid;
	पूर्णांक  any, access;
	काष्ठा v9fs_session_info *v9ses;

	v9ses = v9fs_dentry2v9ses(dentry);
	access = v9ses->flags & V9FS_ACCESS_MASK;
	चयन (access) अणु
	हाल V9FS_ACCESS_SINGLE:
	हाल V9FS_ACCESS_USER:
	हाल V9FS_ACCESS_CLIENT:
		uid = current_fsuid();
		any = 0;
		अवरोध;

	हाल V9FS_ACCESS_ANY:
		uid = v9ses->uid;
		any = 1;
		अवरोध;

	शेष:
		uid = INVALID_UID;
		any = 0;
		अवरोध;
	पूर्ण
	वापस v9fs_fid_lookup_with_uid(dentry, uid, any);
पूर्ण

काष्ठा p9_fid *v9fs_ग_लिखोback_fid(काष्ठा dentry *dentry)
अणु
	पूर्णांक err;
	काष्ठा p9_fid *fid, *ofid;

	ofid = v9fs_fid_lookup_with_uid(dentry, GLOBAL_ROOT_UID, 0);
	fid = clone_fid(ofid);
	अगर (IS_ERR(fid))
		जाओ error_out;
	p9_client_clunk(ofid);
	/*
	 * ग_लिखोback fid will only be used to ग_लिखो back the
	 * dirty pages. We always request क्रम the खोलो fid in पढ़ो-ग_लिखो
	 * mode so that a partial page ग_लिखो which result in page
	 * पढ़ो can work.
	 */
	err = p9_client_खोलो(fid, O_RDWR);
	अगर (err < 0) अणु
		p9_client_clunk(fid);
		fid = ERR_PTR(err);
		जाओ error_out;
	पूर्ण
error_out:
	वापस fid;
पूर्ण
