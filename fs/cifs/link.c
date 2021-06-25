<शैली गुरु>
/*
 *   fs/cअगरs/link.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
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
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "smb2proto.h"
#समावेश "cifs_ioctl.h"

/*
 * M-F Symlink Functions - Begin
 */

#घोषणा CIFS_MF_SYMLINK_LEN_OFFSET (4+1)
#घोषणा CIFS_MF_SYMLINK_MD5_OFFSET (CIFS_MF_SYMLINK_LEN_OFFSET+(4+1))
#घोषणा CIFS_MF_SYMLINK_LINK_OFFSET (CIFS_MF_SYMLINK_MD5_OFFSET+(32+1))
#घोषणा CIFS_MF_SYMLINK_LINK_MAXLEN (1024)
#घोषणा CIFS_MF_SYMLINK_खाता_SIZE \
	(CIFS_MF_SYMLINK_LINK_OFFSET + CIFS_MF_SYMLINK_LINK_MAXLEN)

#घोषणा CIFS_MF_SYMLINK_LEN_FORMAT "XSym\n%04u\n"
#घोषणा CIFS_MF_SYMLINK_MD5_FORMAT "%16phN\n"
#घोषणा CIFS_MF_SYMLINK_MD5_ARGS(md5_hash) md5_hash

अटल पूर्णांक
symlink_hash(अचिन्हित पूर्णांक link_len, स्थिर अक्षर *link_str, u8 *md5_hash)
अणु
	पूर्णांक rc;
	काष्ठा crypto_shash *md5 = शून्य;
	काष्ठा sdesc *sdescmd5 = शून्य;

	rc = cअगरs_alloc_hash("md5", &md5, &sdescmd5);
	अगर (rc)
		जाओ symlink_hash_err;

	rc = crypto_shash_init(&sdescmd5->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init md5 shash\n", __func__);
		जाओ symlink_hash_err;
	पूर्ण
	rc = crypto_shash_update(&sdescmd5->shash, link_str, link_len);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with link_str\n", __func__);
		जाओ symlink_hash_err;
	पूर्ण
	rc = crypto_shash_final(&sdescmd5->shash, md5_hash);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate md5 hash\n", __func__);

symlink_hash_err:
	cअगरs_मुक्त_hash(&md5, &sdescmd5);
	वापस rc;
पूर्ण

अटल पूर्णांक
parse_mf_symlink(स्थिर u8 *buf, अचिन्हित पूर्णांक buf_len, अचिन्हित पूर्णांक *_link_len,
		 अक्षर **_link_str)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक link_len;
	स्थिर अक्षर *md5_str1;
	स्थिर अक्षर *link_str;
	u8 md5_hash[16];
	अक्षर md5_str2[34];

	अगर (buf_len != CIFS_MF_SYMLINK_खाता_SIZE)
		वापस -EINVAL;

	md5_str1 = (स्थिर अक्षर *)&buf[CIFS_MF_SYMLINK_MD5_OFFSET];
	link_str = (स्थिर अक्षर *)&buf[CIFS_MF_SYMLINK_LINK_OFFSET];

	rc = माला_पूछो(buf, CIFS_MF_SYMLINK_LEN_FORMAT, &link_len);
	अगर (rc != 1)
		वापस -EINVAL;

	rc = symlink_hash(link_len, link_str, md5_hash);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: MD5 hash failure: %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	scnम_लिखो(md5_str2, माप(md5_str2),
		  CIFS_MF_SYMLINK_MD5_FORMAT,
		  CIFS_MF_SYMLINK_MD5_ARGS(md5_hash));

	अगर (म_भेदन(md5_str1, md5_str2, 17) != 0)
		वापस -EINVAL;

	अगर (_link_str) अणु
		*_link_str = kstrndup(link_str, link_len, GFP_KERNEL);
		अगर (!*_link_str)
			वापस -ENOMEM;
	पूर्ण

	*_link_len = link_len;
	वापस 0;
पूर्ण

अटल पूर्णांक
क्रमmat_mf_symlink(u8 *buf, अचिन्हित पूर्णांक buf_len, स्थिर अक्षर *link_str)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक link_len;
	अचिन्हित पूर्णांक ofs;
	u8 md5_hash[16];

	अगर (buf_len != CIFS_MF_SYMLINK_खाता_SIZE)
		वापस -EINVAL;

	link_len = म_माप(link_str);

	अगर (link_len > CIFS_MF_SYMLINK_LINK_MAXLEN)
		वापस -ENAMETOOLONG;

	rc = symlink_hash(link_len, link_str, md5_hash);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s: MD5 hash failure: %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	scnम_लिखो(buf, buf_len,
		  CIFS_MF_SYMLINK_LEN_FORMAT CIFS_MF_SYMLINK_MD5_FORMAT,
		  link_len,
		  CIFS_MF_SYMLINK_MD5_ARGS(md5_hash));

	ofs = CIFS_MF_SYMLINK_LINK_OFFSET;
	स_नकल(buf + ofs, link_str, link_len);

	ofs += link_len;
	अगर (ofs < CIFS_MF_SYMLINK_खाता_SIZE) अणु
		buf[ofs] = '\n';
		ofs++;
	पूर्ण

	जबतक (ofs < CIFS_MF_SYMLINK_खाता_SIZE) अणु
		buf[ofs] = ' ';
		ofs++;
	पूर्ण

	वापस 0;
पूर्ण

bool
couldbe_mf_symlink(स्थिर काष्ठा cअगरs_fattr *fattr)
अणु
	अगर (!S_ISREG(fattr->cf_mode))
		/* it's not a symlink */
		वापस false;

	अगर (fattr->cf_eof != CIFS_MF_SYMLINK_खाता_SIZE)
		/* it's not a symlink */
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
create_mf_symlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		  काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *fromName,
		  स्थिर अक्षर *toName)
अणु
	पूर्णांक rc;
	u8 *buf;
	अचिन्हित पूर्णांक bytes_written = 0;

	buf = kदो_स्मृति(CIFS_MF_SYMLINK_खाता_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rc = क्रमmat_mf_symlink(buf, CIFS_MF_SYMLINK_खाता_SIZE, toName);
	अगर (rc)
		जाओ out;

	अगर (tcon->ses->server->ops->create_mf_symlink)
		rc = tcon->ses->server->ops->create_mf_symlink(xid, tcon,
					cअगरs_sb, fromName, buf, &bytes_written);
	अन्यथा
		rc = -EOPNOTSUPP;

	अगर (rc)
		जाओ out;

	अगर (bytes_written != CIFS_MF_SYMLINK_खाता_SIZE)
		rc = -EIO;
out:
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
query_mf_symlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
		 अक्षर **symlinkinfo)
अणु
	पूर्णांक rc;
	u8 *buf = शून्य;
	अचिन्हित पूर्णांक link_len = 0;
	अचिन्हित पूर्णांक bytes_पढ़ो = 0;

	buf = kदो_स्मृति(CIFS_MF_SYMLINK_खाता_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (tcon->ses->server->ops->query_mf_symlink)
		rc = tcon->ses->server->ops->query_mf_symlink(xid, tcon,
					      cअगरs_sb, path, buf, &bytes_पढ़ो);
	अन्यथा
		rc = -ENOSYS;

	अगर (rc)
		जाओ out;

	अगर (bytes_पढ़ो == 0) अणु /* not a symlink */
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = parse_mf_symlink(buf, bytes_पढ़ो, &link_len, symlinkinfo);
out:
	kमुक्त(buf);
	वापस rc;
पूर्ण

पूर्णांक
check_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		 काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_fattr *fattr,
		 स्थिर अचिन्हित अक्षर *path)
अणु
	पूर्णांक rc;
	u8 *buf = शून्य;
	अचिन्हित पूर्णांक link_len = 0;
	अचिन्हित पूर्णांक bytes_पढ़ो = 0;

	अगर (!couldbe_mf_symlink(fattr))
		/* it's not a symlink */
		वापस 0;

	buf = kदो_स्मृति(CIFS_MF_SYMLINK_खाता_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (tcon->ses->server->ops->query_mf_symlink)
		rc = tcon->ses->server->ops->query_mf_symlink(xid, tcon,
					      cअगरs_sb, path, buf, &bytes_पढ़ो);
	अन्यथा
		rc = -ENOSYS;

	अगर (rc)
		जाओ out;

	अगर (bytes_पढ़ो == 0) /* not a symlink */
		जाओ out;

	rc = parse_mf_symlink(buf, bytes_पढ़ो, &link_len, शून्य);
	अगर (rc == -EINVAL) अणु
		/* it's not a symlink */
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (rc != 0)
		जाओ out;

	/* it is a symlink */
	fattr->cf_eof = link_len;
	fattr->cf_mode &= ~S_IFMT;
	fattr->cf_mode |= S_IFLNK | S_IRWXU | S_IRWXG | S_IRWXO;
	fattr->cf_dtype = DT_LNK;
out:
	kमुक्त(buf);
	वापस rc;
पूर्ण

/*
 * SMB 1.0 Protocol specअगरic functions
 */

पूर्णांक
cअगरs_query_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
		      अक्षर *pbuf, अचिन्हित पूर्णांक *pbytes_पढ़ो)
अणु
	पूर्णांक rc;
	पूर्णांक oplock = 0;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	पूर्णांक buf_type = CIFS_NO_BUFFER;
	खाता_ALL_INFO file_info;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_READ;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, &file_info);
	अगर (rc)
		वापस rc;

	अगर (file_info.EndOfFile != cpu_to_le64(CIFS_MF_SYMLINK_खाता_SIZE)) अणु
		rc = -ENOENT;
		/* it's not a symlink */
		जाओ out;
	पूर्ण

	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_खाता_SIZE;

	rc = CIFSSMBRead(xid, &io_parms, pbytes_पढ़ो, &pbuf, &buf_type);
out:
	CIFSSMBClose(xid, tcon, fid.netfid);
	वापस rc;
पूर्ण

पूर्णांक
cअगरs_create_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
		       अक्षर *pbuf, अचिन्हित पूर्णांक *pbytes_written)
अणु
	पूर्णांक rc;
	पूर्णांक oplock = 0;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_WRITE;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_CREATE;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_खोलो(xid, &oparms, &oplock, शून्य);
	अगर (rc)
		वापस rc;

	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_खाता_SIZE;

	rc = CIFSSMBWrite(xid, &io_parms, pbytes_written, pbuf);
	CIFSSMBClose(xid, tcon, fid.netfid);
	वापस rc;
पूर्ण

/*
 * SMB 2.1/SMB3 Protocol specअगरic functions
 */
पूर्णांक
smb3_query_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
		      अक्षर *pbuf, अचिन्हित पूर्णांक *pbytes_पढ़ो)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	पूर्णांक buf_type = CIFS_NO_BUFFER;
	__le16 *utf16_path;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा smb2_file_all_info *pfile_info = शून्य;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_READ;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_OPEN;
	oparms.fid = &fid;
	oparms.reconnect = false;

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (utf16_path == शून्य)
		वापस -ENOMEM;

	pfile_info = kzalloc(माप(काष्ठा smb2_file_all_info) + PATH_MAX * 2,
			     GFP_KERNEL);

	अगर (pfile_info == शून्य) अणु
		kमुक्त(utf16_path);
		वापस  -ENOMEM;
	पूर्ण

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, pfile_info, शून्य,
		       शून्य, शून्य);
	अगर (rc)
		जाओ qmf_out_खोलो_fail;

	अगर (pfile_info->EndOfFile != cpu_to_le64(CIFS_MF_SYMLINK_खाता_SIZE)) अणु
		/* it's not a symlink */
		rc = -ENOENT; /* Is there a better rc to वापस? */
		जाओ qmf_out;
	पूर्ण

	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_खाता_SIZE;
	io_parms.persistent_fid = fid.persistent_fid;
	io_parms.अस्थिर_fid = fid.अस्थिर_fid;
	rc = SMB2_पढ़ो(xid, &io_parms, pbytes_पढ़ो, &pbuf, &buf_type);
qmf_out:
	SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);
qmf_out_खोलो_fail:
	kमुक्त(utf16_path);
	kमुक्त(pfile_info);
	वापस rc;
पूर्ण

पूर्णांक
smb3_create_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
		       अक्षर *pbuf, अचिन्हित पूर्णांक *pbytes_written)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_fid fid;
	काष्ठा cअगरs_खोलो_parms oparms;
	काष्ठा cअगरs_io_parms io_parms = अणु0पूर्ण;
	__le16 *utf16_path;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	काष्ठा kvec iov[2];

	cअगरs_dbg(FYI, "%s: path: %s\n", __func__, path);

	utf16_path = cअगरs_convert_path_to_utf16(path, cअगरs_sb);
	अगर (!utf16_path)
		वापस -ENOMEM;

	oparms.tcon = tcon;
	oparms.cअगरs_sb = cअगरs_sb;
	oparms.desired_access = GENERIC_WRITE;
	oparms.create_options = cअगरs_create_options(cअगरs_sb, CREATE_NOT_सूची);
	oparms.disposition = खाता_CREATE;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = SMB2_खोलो(xid, &oparms, utf16_path, &oplock, शून्य, शून्य,
		       शून्य, शून्य);
	अगर (rc) अणु
		kमुक्त(utf16_path);
		वापस rc;
	पूर्ण

	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_खाता_SIZE;
	io_parms.persistent_fid = fid.persistent_fid;
	io_parms.अस्थिर_fid = fid.अस्थिर_fid;

	/* iov[0] is reserved क्रम smb header */
	iov[1].iov_base = pbuf;
	iov[1].iov_len = CIFS_MF_SYMLINK_खाता_SIZE;

	rc = SMB2_ग_लिखो(xid, &io_parms, pbytes_written, iov, 1);

	/* Make sure we wrote all of the symlink data */
	अगर ((rc == 0) && (*pbytes_written != CIFS_MF_SYMLINK_खाता_SIZE))
		rc = -EIO;

	SMB2_बंद(xid, tcon, fid.persistent_fid, fid.अस्थिर_fid);

	kमुक्त(utf16_path);
	वापस rc;
पूर्ण

/*
 * M-F Symlink Functions - End
 */

पूर्णांक
cअगरs_hardlink(काष्ठा dentry *old_file, काष्ठा inode *inode,
	      काष्ठा dentry *direntry)
अणु
	पूर्णांक rc = -EACCES;
	अचिन्हित पूर्णांक xid;
	स्थिर अक्षर *from_name, *to_name;
	व्योम *page1, *page2;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
	काष्ठा cअगरsInodeInfo *cअगरsInode;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink))
		वापस PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	xid = get_xid();
	page1 = alloc_dentry_path();
	page2 = alloc_dentry_path();

	from_name = build_path_from_dentry(old_file, page1);
	अगर (IS_ERR(from_name)) अणु
		rc = PTR_ERR(from_name);
		जाओ cअगरs_hl_निकास;
	पूर्ण
	to_name = build_path_from_dentry(direntry, page2);
	अगर (IS_ERR(to_name)) अणु
		rc = PTR_ERR(to_name);
		जाओ cअगरs_hl_निकास;
	पूर्ण

	अगर (tcon->unix_ext)
		rc = CIFSUnixCreateHardLink(xid, tcon, from_name, to_name,
					    cअगरs_sb->local_nls,
					    cअगरs_remap(cअगरs_sb));
	अन्यथा अणु
		server = tcon->ses->server;
		अगर (!server->ops->create_hardlink) अणु
			rc = -ENOSYS;
			जाओ cअगरs_hl_निकास;
		पूर्ण
		rc = server->ops->create_hardlink(xid, tcon, from_name, to_name,
						  cअगरs_sb);
		अगर ((rc == -EIO) || (rc == -EINVAL))
			rc = -EOPNOTSUPP;
	पूर्ण

	d_drop(direntry);	/* क्रमce new lookup from server of target */

	/*
	 * अगर source file is cached (oplocked) revalidate will not go to server
	 * until the file is बंदd or oplock broken so update nlinks locally
	 */
	अगर (d_really_is_positive(old_file)) अणु
		cअगरsInode = CIFS_I(d_inode(old_file));
		अगर (rc == 0) अणु
			spin_lock(&d_inode(old_file)->i_lock);
			inc_nlink(d_inode(old_file));
			spin_unlock(&d_inode(old_file)->i_lock);

			/*
			 * parent dir बारtamps will update from srv within a
			 * second, would it really be worth it to set the parent
			 * dir cअगरs inode समय to zero to क्रमce revalidate
			 * (faster) क्रम it too?
			 */
		पूर्ण
		/*
		 * अगर not oplocked will क्रमce revalidate to get info on source
		 * file from srv.  Note Samba server prior to 4.2 has bug -
		 * not updating src file स_समय on hardlinks but Winकरोws servers
		 * handle it properly
		 */
		cअगरsInode->समय = 0;

		/*
		 * Will update parent dir बारtamps from srv within a second.
		 * Would it really be worth it to set the parent dir (cअगरs
		 * inode) समय field to zero to क्रमce revalidate on parent
		 * directory faster ie
		 *
		 * CIFS_I(inode)->समय = 0;
		 */
	पूर्ण

cअगरs_hl_निकास:
	मुक्त_dentry_path(page1);
	मुक्त_dentry_path(page2);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	वापस rc;
पूर्ण

स्थिर अक्षर *
cअगरs_get_link(काष्ठा dentry *direntry, काष्ठा inode *inode,
	      काष्ठा delayed_call *करोne)
अणु
	पूर्णांक rc = -ENOMEM;
	अचिन्हित पूर्णांक xid;
	स्थिर अक्षर *full_path;
	व्योम *page;
	अक्षर *target_path = शून्य;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink = शून्य;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;

	अगर (!direntry)
		वापस ERR_PTR(-ECHILD);

	xid = get_xid();

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		मुक्त_xid(xid);
		वापस ERR_CAST(tlink);
	पूर्ण
	tcon = tlink_tcon(tlink);
	server = tcon->ses->server;

	page = alloc_dentry_path();
	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		मुक्त_xid(xid);
		cअगरs_put_tlink(tlink);
		मुक्त_dentry_path(page);
		वापस ERR_CAST(full_path);
	पूर्ण

	cअगरs_dbg(FYI, "Full path: %s inode = 0x%p\n", full_path, inode);

	rc = -EACCES;
	/*
	 * First try Minshall+French Symlinks, अगर configured
	 * and fallback to UNIX Extensions Symlinks.
	 */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = query_mf_symlink(xid, tcon, cअगरs_sb, full_path,
				      &target_path);

	अगर (rc != 0 && server->ops->query_symlink) अणु
		काष्ठा cअगरsInodeInfo *cअगरsi = CIFS_I(inode);
		bool reparse_poपूर्णांक = false;

		अगर (cअगरsi->cअगरsAttrs & ATTR_REPARSE)
			reparse_poपूर्णांक = true;

		rc = server->ops->query_symlink(xid, tcon, cअगरs_sb, full_path,
						&target_path, reparse_poपूर्णांक);
	पूर्ण

	मुक्त_dentry_path(page);
	मुक्त_xid(xid);
	cअगरs_put_tlink(tlink);
	अगर (rc != 0) अणु
		kमुक्त(target_path);
		वापस ERR_PTR(rc);
	पूर्ण
	set_delayed_call(करोne, kमुक्त_link, target_path);
	वापस target_path;
पूर्ण

पूर्णांक
cअगरs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	     काष्ठा dentry *direntry, स्थिर अक्षर *symname)
अणु
	पूर्णांक rc = -EOPNOTSUPP;
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);
	काष्ठा tcon_link *tlink;
	काष्ठा cअगरs_tcon *pTcon;
	स्थिर अक्षर *full_path;
	व्योम *page;
	काष्ठा inode *newinode = शून्य;

	अगर (unlikely(cअगरs_क्रमced_shutकरोwn(cअगरs_sb)))
		वापस -EIO;

	page = alloc_dentry_path();
	अगर (!page)
		वापस -ENOMEM;

	xid = get_xid();

	tlink = cअगरs_sb_tlink(cअगरs_sb);
	अगर (IS_ERR(tlink)) अणु
		rc = PTR_ERR(tlink);
		जाओ symlink_निकास;
	पूर्ण
	pTcon = tlink_tcon(tlink);

	full_path = build_path_from_dentry(direntry, page);
	अगर (IS_ERR(full_path)) अणु
		rc = PTR_ERR(full_path);
		जाओ symlink_निकास;
	पूर्ण

	cअगरs_dbg(FYI, "Full path: %s\n", full_path);
	cअगरs_dbg(FYI, "symname is %s\n", symname);

	/* BB what अगर DFS and this volume is on dअगरferent share? BB */
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = create_mf_symlink(xid, pTcon, cअगरs_sb, full_path, symname);
	अन्यथा अगर (pTcon->unix_ext)
		rc = CIFSUnixCreateSymLink(xid, pTcon, full_path, symname,
					   cअगरs_sb->local_nls,
					   cअगरs_remap(cअगरs_sb));
	/* अन्यथा
	   rc = CIFSCreateReparseSymLink(xid, pTcon, fromName, toName,
					cअगरs_sb_target->local_nls); */

	अगर (rc == 0) अणु
		अगर (pTcon->posix_extensions)
			rc = smb311_posix_get_inode_info(&newinode, full_path, inode->i_sb, xid);
		अन्यथा अगर (pTcon->unix_ext)
			rc = cअगरs_get_inode_info_unix(&newinode, full_path,
						      inode->i_sb, xid);
		अन्यथा
			rc = cअगरs_get_inode_info(&newinode, full_path, शून्य,
						 inode->i_sb, xid, शून्य);

		अगर (rc != 0) अणु
			cअगरs_dbg(FYI, "Create symlink ok, getinodeinfo fail rc = %d\n",
				 rc);
		पूर्ण अन्यथा अणु
			d_instantiate(direntry, newinode);
		पूर्ण
	पूर्ण
symlink_निकास:
	मुक्त_dentry_path(page);
	cअगरs_put_tlink(tlink);
	मुक्त_xid(xid);
	वापस rc;
पूर्ण
