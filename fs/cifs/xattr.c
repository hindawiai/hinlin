<शैली गुरु>
/*
 *   fs/cअगरs/xattr.c
 *
 *   Copyright (c) International Business Machines  Corp., 2003, 2007
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#समावेश <linux/fs.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_ioctl.h"

#घोषणा MAX_EA_VALUE_SIZE CIFSMaxBufSize
#घोषणा CIFS_XATTR_CIFS_ACL "system.cifs_acl" /* DACL only */
#घोषणा CIFS_XATTR_CIFS_NTSD "system.cifs_ntsd" /* owner plus DACL */
#घोषणा CIFS_XATTR_CIFS_NTSD_FULL "system.cifs_ntsd_full" /* owner/DACL/SACL */
#घोषणा CIFS_XATTR_ATTRIB "cifs.dosattrib"  /* full name: user.cअगरs.करोsattrib */
#घोषणा CIFS_XATTR_CREATETIME "cifs.creationtime"  /* user.cअगरs.creationसमय */
/*
 * Although these three are just aliases क्रम the above, need to move away from
 * confusing users and using the 20+ year old term 'cifs' when it is no दीर्घer
 * secure, replaced by SMB2 (then even more highly secure SMB3) many years ago
 */
#घोषणा SMB3_XATTR_CIFS_ACL "system.smb3_acl" /* DACL only */
#घोषणा SMB3_XATTR_CIFS_NTSD "system.smb3_ntsd" /* owner plus DACL */
#घोषणा SMB3_XATTR_CIFS_NTSD_FULL "system.smb3_ntsd_full" /* owner/DACL/SACL */
#घोषणा SMB3_XATTR_ATTRIB "smb3.dosattrib"  /* full name: user.smb3.करोsattrib */
#घोषणा SMB3_XATTR_CREATETIME "smb3.creationtime"  /* user.smb3.creationसमय */
/* BB need to add server (Samba e.g) support क्रम security and trusted prefix */

क्रमागत अणु XATTR_USER, XATTR_CIFS_ACL, XATTR_ACL_ACCESS, XATTR_ACL_DEFAULT,
	XATTR_CIFS_NTSD, XATTR_CIFS_NTSD_FULL पूर्ण;

अटल पूर्णांक cअगरs_attrib_set(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *pTcon,
			   काष्ठा inode *inode, स्थिर अक्षर *full_path,
			   स्थिर व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार rc = -EOPNOTSUPP;
	__u32 *pattrib = (__u32 *)value;
	__u32 attrib;
	खाता_BASIC_INFO info_buf;

	अगर ((value == शून्य) || (size != माप(__u32)))
		वापस -दुस्फल;

	स_रखो(&info_buf, 0, माप(info_buf));
	attrib = *pattrib;
	info_buf.Attributes = cpu_to_le32(attrib);
	अगर (pTcon->ses->server->ops->set_file_info)
		rc = pTcon->ses->server->ops->set_file_info(inode, full_path,
				&info_buf, xid);
	अगर (rc == 0)
		CIFS_I(inode)->cअगरsAttrs = attrib;

	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_creation_समय_set(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *pTcon,
				  काष्ठा inode *inode, स्थिर अक्षर *full_path,
				  स्थिर व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार rc = -EOPNOTSUPP;
	__u64 *pcreation_समय = (__u64 *)value;
	__u64 creation_समय;
	खाता_BASIC_INFO info_buf;

	अगर ((value == शून्य) || (size != माप(__u64)))
		वापस -दुस्फल;

	स_रखो(&info_buf, 0, माप(info_buf));
	creation_समय = *pcreation_समय;
	info_buf.CreationTime = cpu_to_le64(creation_समय);
	अगर (pTcon->ses->server->ops->set_file_info)
		rc = pTcon->ses->server->ops->set_file_info(inode, full_path,
				&info_buf, xid);
	अगर (rc == 0)
		CIFS_I(inode)->createसमय = creation_समय;

	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			  काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा inode *inode,
			  स्थिर अक्षर *name, स्थिर व्योम *value,
			  माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक rc = -EOPNOTSUPP;
	अचिन्हित पूर्णांक xid;
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	स्थिर अक्षर *full_path;
	व्योम *page;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = get_xid();
	page = alloc_dentry_path();

	full_path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ out;
	पूर्ण
	/* वापस करोs attributes as pseuकरो xattr */
	/* वापस alt name अगर available as pseuकरो attr */

	/* अगर proc/fs/cअगरs/streamstoxattr is set then
		search server क्रम EAs or streams to
		वापसs as xattrs */
	अगर (size > MAX_EA_VALUE_SIZE) अणु
		cअगरs_dbg(FYI, "size of EA value too large\n");
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	चयन (handler->flags) अणु
	हाल XATTR_USER:
		cअगरs_dbg(FYI, "%s:setting user xattr %s\n", __func__, name);
		अगर ((म_भेद(name, CIFS_XATTR_ATTRIB) == 0) ||
		    (म_भेद(name, SMB3_XATTR_ATTRIB) == 0)) अणु
			rc = cअगरs_attrib_set(xid, pTcon, inode, full_path,
					value, size);
			अगर (rc == 0) /* क्रमce revalidate of the inode */
				CIFS_I(inode)->समय = 0;
			अवरोध;
		पूर्ण अन्यथा अगर ((म_भेद(name, CIFS_XATTR_CREATETIME) == 0) ||
			   (म_भेद(name, SMB3_XATTR_CREATETIME) == 0)) अणु
			rc = cअगरs_creation_समय_set(xid, pTcon, inode,
					full_path, value, size);
			अगर (rc == 0) /* क्रमce revalidate of the inode */
				CIFS_I(inode)->समय = 0;
			अवरोध;
		पूर्ण

		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_XATTR)
			जाओ out;

		अगर (pTcon->ses->server->ops->set_EA)
			rc = pTcon->ses->server->ops->set_EA(xid, pTcon,
				full_path, name, value, (__u16)size,
				cअगरs_sb->local_nls, cअगरs_sb);
		अवरोध;

	हाल XATTR_CIFS_ACL:
	हाल XATTR_CIFS_NTSD:
	हाल XATTR_CIFS_NTSD_FULL: अणु
		काष्ठा cअगरs_ntsd *pacl;

		अगर (!value)
			जाओ out;
		pacl = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!pacl) अणु
			rc = -ENOMEM;
		पूर्ण अन्यथा अणु
			स_नकल(pacl, value, size);
			अगर (pTcon->ses->server->ops->set_acl) अणु
				पूर्णांक aclflags = 0;
				rc = 0;

				चयन (handler->flags) अणु
				हाल XATTR_CIFS_NTSD_FULL:
					aclflags = (CIFS_ACL_OWNER |
						    CIFS_ACL_DACL |
						    CIFS_ACL_SACL);
					अवरोध;
				हाल XATTR_CIFS_NTSD:
					aclflags = (CIFS_ACL_OWNER |
						    CIFS_ACL_DACL);
					अवरोध;
				हाल XATTR_CIFS_ACL:
				शेष:
					aclflags = CIFS_ACL_DACL;
				पूर्ण

				rc = pTcon->ses->server->ops->set_acl(pacl,
					size, inode, full_path, aclflags);
			पूर्ण अन्यथा अणु
				rc = -EOPNOTSUPP;
			पूर्ण
			अगर (rc == 0) /* क्रमce revalidate of the inode */
				CIFS_I(inode)->समय = 0;
			kमुक्त(pacl);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल XATTR_ACL_ACCESS:
#अगर_घोषित CONFIG_CIFS_POSIX
		अगर (!value)
			जाओ out;
		अगर (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBSetPosixACL(xid, pTcon, full_path,
				value, (स्थिर पूर्णांक)size,
				ACL_TYPE_ACCESS, cअगरs_sb->local_nls,
				cअगरs_remap(cअगरs_sb));
#पूर्ण_अगर  /* CONFIG_CIFS_POSIX */
		अवरोध;

	हाल XATTR_ACL_DEFAULT:
#अगर_घोषित CONFIG_CIFS_POSIX
		अगर (!value)
			जाओ out;
		अगर (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBSetPosixACL(xid, pTcon, full_path,
				value, (स्थिर पूर्णांक)size,
				ACL_TYPE_DEFAULT, cअगरs_sb->local_nls,
				cअगरs_remap(cअगरs_sb));
#पूर्ण_अगर  /* CONFIG_CIFS_POSIX */
		अवरोध;
	पूर्ण

out:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल पूर्णांक cअगरs_attrib_get(काष्ठा dentry *dentry,
			   काष्ठा inode *inode, व्योम *value,
			   माप_प्रकार size)
अणु
	sमाप_प्रकार rc;
	__u32 *pattribute;

	rc = cअगरs_revalidate_dentry_attr(dentry);

	अगर (rc)
		वापस rc;

	अगर ((value == शून्य) || (size == 0))
		वापस माप(__u32);
	अन्यथा अगर (size < माप(__u32))
		वापस -दुस्फल;

	/* वापस करोs attributes as pseuकरो xattr */
	pattribute = (__u32 *)value;
	*pattribute = CIFS_I(inode)->cअगरsAttrs;

	वापस माप(__u32);
पूर्ण

अटल पूर्णांक cअगरs_creation_समय_get(काष्ठा dentry *dentry, काष्ठा inode *inode,
				  व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार rc;
	__u64 *pcreateसमय;

	rc = cअगरs_revalidate_dentry_attr(dentry);
	अगर (rc)
		वापस rc;

	अगर ((value == शून्य) || (size == 0))
		वापस माप(__u64);
	अन्यथा अगर (size < माप(__u64))
		वापस -दुस्फल;

	/* वापस करोs attributes as pseuकरो xattr */
	pcreateसमय = (__u64 *)value;
	*pcreateसमय = CIFS_I(inode)->createसमय;
	वापस माप(__u64);
पूर्ण


अटल पूर्णांक cअगरs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			  काष्ठा dentry *dentry, काष्ठा inode *inode,
			  स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार rc = -EOPNOTSUPP;
	अचिन्हित पूर्णांक xid;
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	स्थिर अक्षर *full_path;
	व्योम *page;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = get_xid();
	page = alloc_dentry_path();

	full_path = build_path_from_dentry(dentry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ out;
	पूर्ण

	/* वापस alt name अगर available as pseuकरो attr */
	चयन (handler->flags) अणु
	हाल XATTR_USER:
		cअगरs_dbg(FYI, "%s:querying user xattr %s\n", __func__, name);
		अगर ((म_भेद(name, CIFS_XATTR_ATTRIB) == 0) ||
		    (म_भेद(name, SMB3_XATTR_ATTRIB) == 0)) अणु
			rc = cअगरs_attrib_get(dentry, inode, value, size);
			अवरोध;
		पूर्ण अन्यथा अगर ((म_भेद(name, CIFS_XATTR_CREATETIME) == 0) ||
		    (म_भेद(name, SMB3_XATTR_CREATETIME) == 0)) अणु
			rc = cअगरs_creation_समय_get(dentry, inode, value, size);
			अवरोध;
		पूर्ण

		अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_XATTR)
			जाओ out;

		अगर (pTcon->ses->server->ops->query_all_EAs)
			rc = pTcon->ses->server->ops->query_all_EAs(xid, pTcon,
				full_path, name, value, size, cअगरs_sb);
		अवरोध;

	हाल XATTR_CIFS_ACL:
	हाल XATTR_CIFS_NTSD:
	हाल XATTR_CIFS_NTSD_FULL: अणु
		/*
		 * fetch owner, DACL, and SACL अगर asked क्रम full descriptor,
		 * fetch owner and DACL otherwise
		 */
		u32 acllen, extra_info;
		काष्ठा cअगरs_ntsd *pacl;

		अगर (pTcon->ses->server->ops->get_acl == शून्य)
			जाओ out; /* rc alपढ़ोy EOPNOTSUPP */

		अगर (handler->flags == XATTR_CIFS_NTSD_FULL) अणु
			extra_info = SACL_SECINFO;
		पूर्ण अन्यथा अणु
			extra_info = 0;
		पूर्ण
		pacl = pTcon->ses->server->ops->get_acl(cअगरs_sb,
				inode, full_path, &acllen, extra_info);
		अगर (IS_ERR(pacl)) अणु
			rc = PTR_ERR(pacl);
			cअगरs_dbg(VFS, "%s: error %zd getting sec desc\n",
				 __func__, rc);
		पूर्ण अन्यथा अणु
			अगर (value) अणु
				अगर (acllen > size)
					acllen = -दुस्फल;
				अन्यथा
					स_नकल(value, pacl, acllen);
			पूर्ण
			rc = acllen;
			kमुक्त(pacl);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल XATTR_ACL_ACCESS:
#अगर_घोषित CONFIG_CIFS_POSIX
		अगर (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBGetPosixACL(xid, pTcon, full_path,
				value, size, ACL_TYPE_ACCESS,
				cअगरs_sb->local_nls,
				cअगरs_remap(cअगरs_sb));
#पूर्ण_अगर  /* CONFIG_CIFS_POSIX */
		अवरोध;

	हाल XATTR_ACL_DEFAULT:
#अगर_घोषित CONFIG_CIFS_POSIX
		अगर (sb->s_flags & SB_POSIXACL)
			rc = CIFSSMBGetPosixACL(xid, pTcon, full_path,
				value, size, ACL_TYPE_DEFAULT,
				cअगरs_sb->local_nls,
				cअगरs_remap(cअगरs_sb));
#पूर्ण_अगर  /* CONFIG_CIFS_POSIX */
		अवरोध;
	पूर्ण

	/* We could add an additional check क्रम streams ie
	    अगर proc/fs/cअगरs/streamstoxattr is set then
		search server क्रम EAs or streams to
		वापसs as xattrs */

	अगर (rc == -EINVAL)
		rc = -EOPNOTSUPP;

out:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

sमाप_प्रकार cअगरs_listxattr(काष्ठा dentry *direntry, अक्षर *data, माप_प्रकार buf_size)
अणु
	sमाप_प्रकार rc = -EOPNOTSUPP;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(direntry->d_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	स्थिर अक्षर *full_path;
	व्योम *page;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_XATTR)
		वापस -EOPNOTSUPP;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = get_xid();
	page = alloc_dentry_path();

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ list_ea_निकास;
	पूर्ण
	/* वापस करोs attributes as pseuकरो xattr */
	/* वापस alt name अगर available as pseuकरो attr */

	/* अगर proc/fs/cअगरs/streamstoxattr is set then
		search server क्रम EAs or streams to
		वापसs as xattrs */

	अगर (pTcon->ses->server->ops->query_all_EAs)
		rc = pTcon->ses->server->ops->query_all_EAs(xid, pTcon,
				full_path, शून्य, data, buf_size, cअगरs_sb);
list_ea_निकास:
	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा xattr_handler cअगरs_user_xattr_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.flags = XATTR_USER,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

/* os2.* attributes are treated like user.* attributes */
अटल स्थिर काष्ठा xattr_handler cअगरs_os2_xattr_handler = अणु
	.prefix = XATTR_OS2_PREFIX,
	.flags = XATTR_USER,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler cअगरs_cअगरs_acl_xattr_handler = अणु
	.name = CIFS_XATTR_CIFS_ACL,
	.flags = XATTR_CIFS_ACL,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

/*
 * Although this is just an alias क्रम the above, need to move away from
 * confusing users and using the 20 year old term 'cifs' when it is no
 * दीर्घer secure and was replaced by SMB2/SMB3 a दीर्घ समय ago, and
 * SMB3 and later are highly secure.
 */
अटल स्थिर काष्ठा xattr_handler smb3_acl_xattr_handler = अणु
	.name = SMB3_XATTR_CIFS_ACL,
	.flags = XATTR_CIFS_ACL,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler cअगरs_cअगरs_ntsd_xattr_handler = अणु
	.name = CIFS_XATTR_CIFS_NTSD,
	.flags = XATTR_CIFS_NTSD,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

/*
 * Although this is just an alias क्रम the above, need to move away from
 * confusing users and using the 20 year old term 'cifs' when it is no
 * दीर्घer secure and was replaced by SMB2/SMB3 a दीर्घ समय ago, and
 * SMB3 and later are highly secure.
 */
अटल स्थिर काष्ठा xattr_handler smb3_ntsd_xattr_handler = अणु
	.name = SMB3_XATTR_CIFS_NTSD,
	.flags = XATTR_CIFS_NTSD,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler cअगरs_cअगरs_ntsd_full_xattr_handler = अणु
	.name = CIFS_XATTR_CIFS_NTSD_FULL,
	.flags = XATTR_CIFS_NTSD_FULL,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

/*
 * Although this is just an alias क्रम the above, need to move away from
 * confusing users and using the 20 year old term 'cifs' when it is no
 * दीर्घer secure and was replaced by SMB2/SMB3 a दीर्घ समय ago, and
 * SMB3 and later are highly secure.
 */
अटल स्थिर काष्ठा xattr_handler smb3_ntsd_full_xattr_handler = अणु
	.name = SMB3_XATTR_CIFS_NTSD_FULL,
	.flags = XATTR_CIFS_NTSD_FULL,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;


अटल स्थिर काष्ठा xattr_handler cअगरs_posix_acl_access_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_ACCESS,
	.flags = XATTR_ACL_ACCESS,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler cअगरs_posix_acl_शेष_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_DEFAULT,
	.flags = XATTR_ACL_DEFAULT,
	.get = cअगरs_xattr_get,
	.set = cअगरs_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *cअगरs_xattr_handlers[] = अणु
	&cअगरs_user_xattr_handler,
	&cअगरs_os2_xattr_handler,
	&cअगरs_cअगरs_acl_xattr_handler,
	&smb3_acl_xattr_handler, /* alias क्रम above since aव्योमing "cifs" */
	&cअगरs_cअगरs_ntsd_xattr_handler,
	&smb3_ntsd_xattr_handler, /* alias क्रम above since aव्योमing "cifs" */
	&cअगरs_cअगरs_ntsd_full_xattr_handler,
	&smb3_ntsd_full_xattr_handler, /* alias क्रम above since aव्योमing "cifs" */
	&cअगरs_posix_acl_access_xattr_handler,
	&cअगरs_posix_acl_शेष_xattr_handler,
	शून्य
पूर्ण;
