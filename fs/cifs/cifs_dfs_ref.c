<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Contains the CIFS DFS referral mounting routines used क्रम handling
 *   traversal via DFS junction poपूर्णांक
 *
 *   Copyright (c) 2007 Igor Mammeकरोv
 *   Copyright (C) International Business Machines  Corp., 2008
 *   Author(s): Igor Mammeकरोv (niallain@gmail.com)
 *		Steve French (sfrench@us.ibm.com)
 */

#समावेश <linux/dcache.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/inet.h>
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifsfs.h"
#समावेश "dns_resolve.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_unicode.h"
#समावेश "dfs_cache.h"
#समावेश "fs_context.h"

अटल LIST_HEAD(cअगरs_dfs_स्वतःmount_list);

अटल व्योम cअगरs_dfs_expire_स्वतःmounts(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(cअगरs_dfs_स्वतःmount_task,
			    cअगरs_dfs_expire_स्वतःmounts);
अटल पूर्णांक cअगरs_dfs_mountpoपूर्णांक_expiry_समयout = 500 * HZ;

अटल व्योम cअगरs_dfs_expire_स्वतःmounts(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा list_head *list = &cअगरs_dfs_स्वतःmount_list;

	mark_mounts_क्रम_expiry(list);
	अगर (!list_empty(list))
		schedule_delayed_work(&cअगरs_dfs_स्वतःmount_task,
				      cअगरs_dfs_mountpoपूर्णांक_expiry_समयout);
पूर्ण

व्योम cअगरs_dfs_release_स्वतःmount_समयr(व्योम)
अणु
	BUG_ON(!list_empty(&cअगरs_dfs_स्वतःmount_list));
	cancel_delayed_work_sync(&cअगरs_dfs_स्वतःmount_task);
पूर्ण

/**
 * cअगरs_build_devname - build a devicename from a UNC and optional prepath
 * @nodename:	poपूर्णांकer to UNC string
 * @prepath:	poपूर्णांकer to prefixpath (or शून्य अगर there isn't one)
 *
 * Build a new cअगरs devicename after chasing a DFS referral. Allocate a buffer
 * big enough to hold the final thing. Copy the UNC from the nodename, and
 * concatenate the prepath onto the end of it अगर there is one.
 *
 * Returns poपूर्णांकer to the built string, or a ERR_PTR. Caller is responsible
 * क्रम मुक्तing the वापसed string.
 */
अटल अक्षर *
cअगरs_build_devname(अक्षर *nodename, स्थिर अक्षर *prepath)
अणु
	माप_प्रकार pplen;
	माप_प्रकार unclen;
	अक्षर *dev;
	अक्षर *pos;

	/* skip over any preceding delimiters */
	nodename += म_अखोज(nodename, "\\");
	अगर (!*nodename)
		वापस ERR_PTR(-EINVAL);

	/* get length of UNC and set pos to last अक्षर */
	unclen = म_माप(nodename);
	pos = nodename + unclen - 1;

	/* trim off any trailing delimiters */
	जबतक (*pos == '\\') अणु
		--pos;
		--unclen;
	पूर्ण

	/* allocate a buffer:
	 * +2 क्रम preceding "//"
	 * +1 क्रम delimiter between UNC and prepath
	 * +1 क्रम trailing शून्य
	 */
	pplen = prepath ? म_माप(prepath) : 0;
	dev = kदो_स्मृति(2 + unclen + 1 + pplen + 1, GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	pos = dev;
	/* add the initial "//" */
	*pos = '/';
	++pos;
	*pos = '/';
	++pos;

	/* copy in the UNC portion from referral */
	स_नकल(pos, nodename, unclen);
	pos += unclen;

	/* copy the prefixpath reमुख्यder (अगर there is one) */
	अगर (pplen) अणु
		*pos = '/';
		++pos;
		स_नकल(pos, prepath, pplen);
		pos += pplen;
	पूर्ण

	/* शून्य terminator */
	*pos = '\0';

	convert_delimiter(dev, '/');
	वापस dev;
पूर्ण


/**
 * cअगरs_compose_mount_options	-	creates mount options क्रम referral
 * @sb_mountdata:	parent/root DFS mount options (ढाँचा)
 * @fullpath:		full path in UNC क्रमmat
 * @ref:		optional server's referral
 *
 * creates mount options क्रम submount based on ढाँचा options sb_mountdata
 * and replacing unc,ip,prefixpath options with ones we've got क्रमm ref_unc.
 *
 * Returns: poपूर्णांकer to new mount options or ERR_PTR.
 * Caller is responsible क्रम मुक्तing वापसed value अगर it is not error.
 */
अक्षर *cअगरs_compose_mount_options(स्थिर अक्षर *sb_mountdata,
				 स्थिर अक्षर *fullpath,
				 स्थिर काष्ठा dfs_info3_param *ref,
				 अक्षर **devname)
अणु
	पूर्णांक rc;
	अक्षर *name;
	अक्षर *mountdata = शून्य;
	स्थिर अक्षर *prepath = शून्य;
	पूर्णांक md_len;
	अक्षर *tkn_e;
	अक्षर *srvIP = शून्य;
	अक्षर sep = ',';
	पूर्णांक off, noff;

	अगर (sb_mountdata == शून्य)
		वापस ERR_PTR(-EINVAL);

	अगर (ref) अणु
		अगर (म_माप(fullpath) - ref->path_consumed) अणु
			prepath = fullpath + ref->path_consumed;
			/* skip initial delimiter */
			अगर (*prepath == '/' || *prepath == '\\')
				prepath++;
		पूर्ण

		name = cअगरs_build_devname(ref->node_name, prepath);
		अगर (IS_ERR(name)) अणु
			rc = PTR_ERR(name);
			name = शून्य;
			जाओ compose_mount_options_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		name = cअगरs_build_devname((अक्षर *)fullpath, शून्य);
		अगर (IS_ERR(name)) अणु
			rc = PTR_ERR(name);
			name = शून्य;
			जाओ compose_mount_options_err;
		पूर्ण
	पूर्ण

	rc = dns_resolve_server_name_to_ip(name, &srvIP);
	अगर (rc < 0) अणु
		cअगरs_dbg(FYI, "%s: Failed to resolve server part of %s to IP: %d\n",
			 __func__, name, rc);
		जाओ compose_mount_options_err;
	पूर्ण

	/*
	 * In most हालs, we'll be building a लघुer string than the original,
	 * but we करो have to assume that the address in the ip= option may be
	 * much दीर्घer than the original. Add the max length of an address
	 * string to the length of the original string to allow क्रम worst हाल.
	 */
	md_len = म_माप(sb_mountdata) + INET6_ADDRSTRLEN;
	mountdata = kzalloc(md_len + माप("ip=") + 1, GFP_KERNEL);
	अगर (mountdata == शून्य) अणु
		rc = -ENOMEM;
		जाओ compose_mount_options_err;
	पूर्ण

	/* copy all options except of unc,ip,prefixpath */
	off = 0;
	अगर (म_भेदन(sb_mountdata, "sep=", 4) == 0) अणु
			sep = sb_mountdata[4];
			म_नकलन(mountdata, sb_mountdata, 5);
			off += 5;
	पूर्ण

	करो अणु
		tkn_e = म_अक्षर(sb_mountdata + off, sep);
		अगर (tkn_e == शून्य)
			noff = म_माप(sb_mountdata + off);
		अन्यथा
			noff = tkn_e - (sb_mountdata + off) + 1;

		अगर (strnहालcmp(sb_mountdata + off, "unc=", 4) == 0) अणु
			off += noff;
			जारी;
		पूर्ण
		अगर (strnहालcmp(sb_mountdata + off, "ip=", 3) == 0) अणु
			off += noff;
			जारी;
		पूर्ण
		अगर (strnहालcmp(sb_mountdata + off, "prefixpath=", 11) == 0) अणु
			off += noff;
			जारी;
		पूर्ण
		म_जोड़न(mountdata, sb_mountdata + off, noff);
		off += noff;
	पूर्ण जबतक (tkn_e);
	म_जोड़ो(mountdata, sb_mountdata + off);
	mountdata[md_len] = '\0';

	/* copy new IP and ref share name */
	अगर (mountdata[म_माप(mountdata) - 1] != sep)
		म_जोड़न(mountdata, &sep, 1);
	म_जोड़ो(mountdata, "ip=");
	म_जोड़ो(mountdata, srvIP);

	अगर (devname)
		*devname = name;
	अन्यथा
		kमुक्त(name);

	/*cअगरs_dbg(FYI, "%s: parent mountdata: %s\n", __func__, sb_mountdata);*/
	/*cअगरs_dbg(FYI, "%s: submount mountdata: %s\n", __func__, mountdata );*/

compose_mount_options_out:
	kमुक्त(srvIP);
	वापस mountdata;

compose_mount_options_err:
	kमुक्त(mountdata);
	mountdata = ERR_PTR(rc);
	kमुक्त(name);
	जाओ compose_mount_options_out;
पूर्ण

/**
 * cअगरs_dfs_करो_mount - mounts specअगरied path using DFS full path
 *
 * Always pass करोwn @fullpath to smb3_करो_mount() so we can use the root server
 * to perक्रमm failover in हाल we failed to connect to the first target in the
 * referral.
 *
 * @mntpt:		directory entry क्रम the path we are trying to स्वतःmount
 * @cअगरs_sb:		parent/root superblock
 * @fullpath:		full path in UNC क्रमmat
 */
अटल काष्ठा vfsmount *cअगरs_dfs_करो_mount(काष्ठा dentry *mntpt,
					  काष्ठा cअगरs_sb_info *cअगरs_sb,
					  स्थिर अक्षर *fullpath)
अणु
	काष्ठा vfsmount *mnt;
	अक्षर *mountdata;
	अक्षर *devname;

	devname = kstrdup(fullpath, GFP_KERNEL);
	अगर (!devname)
		वापस ERR_PTR(-ENOMEM);

	convert_delimiter(devname, '/');

	/* TODO: change to call fs_context_क्रम_mount(), fill in context directly, call fc_mount */

	/* See afs_mntpt_करो_स्वतःmount in fs/afs/mntpt.c क्रम an example */

	/* strip first '\' from fullpath */
	mountdata = cअगरs_compose_mount_options(cअगरs_sb->ctx->mount_options,
					       fullpath + 1, शून्य, शून्य);
	अगर (IS_ERR(mountdata)) अणु
		kमुक्त(devname);
		वापस (काष्ठा vfsmount *)mountdata;
	पूर्ण

	mnt = vfs_submount(mntpt, &cअगरs_fs_type, devname, mountdata);
	kमुक्त(mountdata);
	kमुक्त(devname);
	वापस mnt;
पूर्ण

/*
 * Create a vfsmount that we can स्वतःmount
 */
अटल काष्ठा vfsmount *cअगरs_dfs_करो_स्वतःmount(काष्ठा dentry *mntpt)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;
	व्योम *page;
	अक्षर *full_path, *root_path;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc;
	काष्ठा vfsmount *mnt;

	cअगरs_dbg(FYI, "in %s\n", __func__);
	BUG_ON(IS_ROOT(mntpt));

	/*
	 * The MSDFS spec states that paths in DFS referral requests and
	 * responses must be prefixed by a single '\' अक्षरacter instead of
	 * the द्विगुन backslashes usually used in the UNC. This function
	 * gives us the latter, so we must adjust the result.
	 */
	mnt = ERR_PTR(-ENOMEM);

	cअगरs_sb = CIFS_SB(mntpt->d_sb);
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_DFS) अणु
		mnt = ERR_PTR(-EREMOTE);
		जाओ cdda_निकास;
	पूर्ण

	page = alloc_dentry_path();
	/* always use tree name prefix */
	full_path = build_path_from_dentry_optional_prefix(mntpt, page, true);
	अगर (IS_ERR(full_path)) अणु
		mnt = ERR_CAST(full_path);
		जाओ मुक्त_full_path;
	पूर्ण

	convert_delimiter(full_path, '\\');

	cअगरs_dbg(FYI, "%s: full_path: %s\n", __func__, full_path);

	अगर (!cअगरs_sb_master_tlink(cअगरs_sb)) अणु
		cअगरs_dbg(FYI, "%s: master tlink is NULL\n", __func__);
		जाओ मुक्त_full_path;
	पूर्ण

	tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	अगर (!tcon) अणु
		cअगरs_dbg(FYI, "%s: master tcon is NULL\n", __func__);
		जाओ मुक्त_full_path;
	पूर्ण

	root_path = kstrdup(tcon->treeName, GFP_KERNEL);
	अगर (!root_path) अणु
		mnt = ERR_PTR(-ENOMEM);
		जाओ मुक्त_full_path;
	पूर्ण
	cअगरs_dbg(FYI, "%s: root path: %s\n", __func__, root_path);

	ses = tcon->ses;
	xid = get_xid();

	/*
	 * If DFS root has been expired, then unconditionally fetch it again to
	 * refresh DFS referral cache.
	 */
	rc = dfs_cache_find(xid, ses, cअगरs_sb->local_nls, cअगरs_remap(cअगरs_sb),
			    root_path + 1, शून्य, शून्य);
	अगर (!rc) अणु
		rc = dfs_cache_find(xid, ses, cअगरs_sb->local_nls,
				    cअगरs_remap(cअगरs_sb), full_path + 1,
				    शून्य, शून्य);
	पूर्ण

	मुक्त_xid(xid);

	अगर (rc) अणु
		mnt = ERR_PTR(rc);
		जाओ मुक्त_root_path;
	पूर्ण
	/*
	 * OK - we were able to get and cache a referral क्रम @full_path.
	 *
	 * Now, pass it करोwn to cअगरs_mount() and it will retry every available
	 * node server in हाल of failures - no need to करो it here.
	 */
	mnt = cअगरs_dfs_करो_mount(mntpt, cअगरs_sb, full_path);
	cअगरs_dbg(FYI, "%s: cifs_dfs_do_mount:%s , mnt:%p\n", __func__,
		 full_path + 1, mnt);

मुक्त_root_path:
	kमुक्त(root_path);
मुक्त_full_path:
	मुक्त_dentry_path(page);
cdda_निकास:
	cअगरs_dbg(FYI, "leaving %s\n" , __func__);
	वापस mnt;
पूर्ण

/*
 * Attempt to स्वतःmount the referral
 */
काष्ठा vfsmount *cअगरs_dfs_d_स्वतःmount(काष्ठा path *path)
अणु
	काष्ठा vfsmount *newmnt;

	cअगरs_dbg(FYI, "in %s\n", __func__);

	newmnt = cअगरs_dfs_करो_स्वतःmount(path->dentry);
	अगर (IS_ERR(newmnt)) अणु
		cअगरs_dbg(FYI, "leaving %s [automount failed]\n" , __func__);
		वापस newmnt;
	पूर्ण

	mntget(newmnt); /* prevent immediate expiration */
	mnt_set_expiry(newmnt, &cअगरs_dfs_स्वतःmount_list);
	schedule_delayed_work(&cअगरs_dfs_स्वतःmount_task,
			      cअगरs_dfs_mountpoपूर्णांक_expiry_समयout);
	cअगरs_dbg(FYI, "leaving %s [ok]\n" , __func__);
	वापस newmnt;
पूर्ण

स्थिर काष्ठा inode_operations cअगरs_dfs_referral_inode_operations = अणु
पूर्ण;
