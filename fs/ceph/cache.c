<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ceph cache definitions.
 *
 *  Copyright (C) 2013 by Adfin Solutions, Inc. All Rights Reserved.
 *  Written by Milosz Tanski (milosz@adfin.com)
 */

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/fs_context.h>
#समावेश "super.h"
#समावेश "cache.h"

काष्ठा ceph_aux_inode अणु
	u64 	version;
	u64	mसमय_sec;
	u64	mसमय_nsec;
पूर्ण;

काष्ठा fscache_netfs ceph_cache_netfs = अणु
	.name		= "ceph",
	.version	= 0,
पूर्ण;

अटल DEFINE_MUTEX(ceph_fscache_lock);
अटल LIST_HEAD(ceph_fscache_list);

काष्ठा ceph_fscache_entry अणु
	काष्ठा list_head list;
	काष्ठा fscache_cookie *fscache;
	माप_प्रकार uniq_len;
	/* The following members must be last */
	काष्ठा ceph_fsid fsid;
	अक्षर uniquअगरier[];
पूर्ण;

अटल स्थिर काष्ठा fscache_cookie_def ceph_fscache_fsid_object_def = अणु
	.name		= "CEPH.fsid",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

पूर्णांक __init ceph_fscache_रेजिस्टर(व्योम)
अणु
	वापस fscache_रेजिस्टर_netfs(&ceph_cache_netfs);
पूर्ण

व्योम ceph_fscache_unरेजिस्टर(व्योम)
अणु
	fscache_unरेजिस्टर_netfs(&ceph_cache_netfs);
पूर्ण

पूर्णांक ceph_fscache_रेजिस्टर_fs(काष्ठा ceph_fs_client* fsc, काष्ठा fs_context *fc)
अणु
	स्थिर काष्ठा ceph_fsid *fsid = &fsc->client->fsid;
	स्थिर अक्षर *fscache_uniq = fsc->mount_options->fscache_uniq;
	माप_प्रकार uniq_len = fscache_uniq ? म_माप(fscache_uniq) : 0;
	काष्ठा ceph_fscache_entry *ent;
	पूर्णांक err = 0;

	mutex_lock(&ceph_fscache_lock);
	list_क्रम_each_entry(ent, &ceph_fscache_list, list) अणु
		अगर (स_भेद(&ent->fsid, fsid, माप(*fsid)))
			जारी;
		अगर (ent->uniq_len != uniq_len)
			जारी;
		अगर (uniq_len && स_भेद(ent->uniquअगरier, fscache_uniq, uniq_len))
			जारी;

		errorfc(fc, "fscache cookie already registered for fsid %pU, use fsc=<uniquifier> option",
		       fsid);
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ent = kzalloc(माप(*ent) + uniq_len, GFP_KERNEL);
	अगर (!ent) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	स_नकल(&ent->fsid, fsid, माप(*fsid));
	अगर (uniq_len > 0) अणु
		स_नकल(&ent->uniquअगरier, fscache_uniq, uniq_len);
		ent->uniq_len = uniq_len;
	पूर्ण

	fsc->fscache = fscache_acquire_cookie(ceph_cache_netfs.primary_index,
					      &ceph_fscache_fsid_object_def,
					      &ent->fsid, माप(ent->fsid) + uniq_len,
					      शून्य, 0,
					      fsc, 0, true);

	अगर (fsc->fscache) अणु
		ent->fscache = fsc->fscache;
		list_add_tail(&ent->list, &ceph_fscache_list);
	पूर्ण अन्यथा अणु
		kमुक्त(ent);
		errorfc(fc, "unable to register fscache cookie for fsid %pU",
		       fsid);
		/* all other fs ignore this error */
	पूर्ण
out_unlock:
	mutex_unlock(&ceph_fscache_lock);
	वापस err;
पूर्ण

अटल क्रमागत fscache_checkaux ceph_fscache_inode_check_aux(
	व्योम *cookie_netfs_data, स्थिर व्योम *data, uपूर्णांक16_t dlen,
	loff_t object_size)
अणु
	काष्ठा ceph_aux_inode aux;
	काष्ठा ceph_inode_info* ci = cookie_netfs_data;
	काष्ठा inode* inode = &ci->vfs_inode;

	अगर (dlen != माप(aux) ||
	    i_size_पढ़ो(inode) != object_size)
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	स_रखो(&aux, 0, माप(aux));
	aux.version = ci->i_version;
	aux.mसमय_sec = inode->i_mसमय.tv_sec;
	aux.mसमय_nsec = inode->i_mसमय.tv_nsec;

	अगर (स_भेद(data, &aux, माप(aux)) != 0)
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	करोut("ceph inode 0x%p cached okay\n", ci);
	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण

अटल स्थिर काष्ठा fscache_cookie_def ceph_fscache_inode_object_def = अणु
	.name		= "CEPH.inode",
	.type		= FSCACHE_COOKIE_TYPE_DATAखाता,
	.check_aux	= ceph_fscache_inode_check_aux,
पूर्ण;

व्योम ceph_fscache_रेजिस्टर_inode_cookie(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_aux_inode aux;

	/* No caching क्रम fileप्रणाली */
	अगर (!fsc->fscache)
		वापस;

	/* Only cache क्रम regular files that are पढ़ो only */
	अगर (!S_ISREG(inode->i_mode))
		वापस;

	inode_lock_nested(inode, I_MUTEX_CHILD);
	अगर (!ci->fscache) अणु
		स_रखो(&aux, 0, माप(aux));
		aux.version = ci->i_version;
		aux.mसमय_sec = inode->i_mसमय.tv_sec;
		aux.mसमय_nsec = inode->i_mसमय.tv_nsec;
		ci->fscache = fscache_acquire_cookie(fsc->fscache,
						     &ceph_fscache_inode_object_def,
						     &ci->i_vino, माप(ci->i_vino),
						     &aux, माप(aux),
						     ci, i_size_पढ़ो(inode), false);
	पूर्ण
	inode_unlock(inode);
पूर्ण

व्योम ceph_fscache_unरेजिस्टर_inode_cookie(काष्ठा ceph_inode_info* ci)
अणु
	काष्ठा fscache_cookie* cookie;

	अगर ((cookie = ci->fscache) == शून्य)
		वापस;

	ci->fscache = शून्य;

	fscache_relinquish_cookie(cookie, &ci->i_vino, false);
पूर्ण

अटल bool ceph_fscache_can_enable(व्योम *data)
अणु
	काष्ठा inode *inode = data;
	वापस !inode_is_खोलो_क्रम_ग_लिखो(inode);
पूर्ण

व्योम ceph_fscache_file_set_cookie(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	अगर (!fscache_cookie_valid(ci->fscache))
		वापस;

	अगर (inode_is_खोलो_क्रम_ग_लिखो(inode)) अणु
		करोut("fscache_file_set_cookie %p %p disabling cache\n",
		     inode, filp);
		fscache_disable_cookie(ci->fscache, &ci->i_vino, false);
	पूर्ण अन्यथा अणु
		fscache_enable_cookie(ci->fscache, &ci->i_vino, i_size_पढ़ो(inode),
				      ceph_fscache_can_enable, inode);
		अगर (fscache_cookie_enabled(ci->fscache)) अणु
			करोut("fscache_file_set_cookie %p %p enabling cache\n",
			     inode, filp);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ceph_fscache_unरेजिस्टर_fs(काष्ठा ceph_fs_client* fsc)
अणु
	अगर (fscache_cookie_valid(fsc->fscache)) अणु
		काष्ठा ceph_fscache_entry *ent;
		bool found = false;

		mutex_lock(&ceph_fscache_lock);
		list_क्रम_each_entry(ent, &ceph_fscache_list, list) अणु
			अगर (ent->fscache == fsc->fscache) अणु
				list_del(&ent->list);
				kमुक्त(ent);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		WARN_ON_ONCE(!found);
		mutex_unlock(&ceph_fscache_lock);

		__fscache_relinquish_cookie(fsc->fscache, शून्य, false);
	पूर्ण
	fsc->fscache = शून्य;
पूर्ण
