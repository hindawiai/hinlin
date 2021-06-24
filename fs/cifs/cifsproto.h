<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsproto.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2008
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
#अगर_अघोषित _CIFSPROTO_H
#घोषणा _CIFSPROTO_H
#समावेश <linux/nls.h>
#समावेश "trace.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर

काष्ठा statfs;
काष्ठा smb_rqst;
काष्ठा smb3_fs_context;

/*
 *****************************************************************
 * All Prototypes
 *****************************************************************
 */

बाह्य काष्ठा smb_hdr *cअगरs_buf_get(व्योम);
बाह्य व्योम cअगरs_buf_release(व्योम *);
बाह्य काष्ठा smb_hdr *cअगरs_small_buf_get(व्योम);
बाह्य व्योम cअगरs_small_buf_release(व्योम *);
बाह्य व्योम मुक्त_rsp_buf(पूर्णांक, व्योम *);
बाह्य पूर्णांक smb_send(काष्ठा TCP_Server_Info *, काष्ठा smb_hdr *,
			अचिन्हित पूर्णांक /* length */);
बाह्य अचिन्हित पूर्णांक _get_xid(व्योम);
बाह्य व्योम _मुक्त_xid(अचिन्हित पूर्णांक);
#घोषणा get_xid()							\
(अणु									\
	अचिन्हित पूर्णांक __xid = _get_xid();				\
	cअगरs_dbg(FYI, "VFS: in %s as Xid: %u with uid: %d\n",		\
		 __func__, __xid,					\
		 from_kuid(&init_user_ns, current_fsuid()));		\
	trace_smb3_enter(__xid, __func__);				\
	__xid;								\
पूर्ण)

#घोषणा मुक्त_xid(curr_xid)						\
करो अणु									\
	_मुक्त_xid(curr_xid);						\
	cअगरs_dbg(FYI, "VFS: leaving %s (xid = %u) rc = %d\n",		\
		 __func__, curr_xid, (पूर्णांक)rc);				\
	अगर (rc)								\
		trace_smb3_निकास_err(curr_xid, __func__, (पूर्णांक)rc);	\
	अन्यथा								\
		trace_smb3_निकास_करोne(curr_xid, __func__);		\
पूर्ण जबतक (0)
बाह्य पूर्णांक init_cअगरs_idmap(व्योम);
बाह्य व्योम निकास_cअगरs_idmap(व्योम);
बाह्य पूर्णांक init_cअगरs_spnego(व्योम);
बाह्य व्योम निकास_cअगरs_spnego(व्योम);
बाह्य स्थिर अक्षर *build_path_from_dentry(काष्ठा dentry *, व्योम *);
बाह्य अक्षर *build_path_from_dentry_optional_prefix(काष्ठा dentry *direntry,
						    व्योम *page, bool prefix);
अटल अंतरभूत व्योम *alloc_dentry_path(व्योम)
अणु
	वापस __getname();
पूर्ण

अटल अंतरभूत व्योम मुक्त_dentry_path(व्योम *page)
अणु
	अगर (page)
		__putname(page);
पूर्ण

बाह्य अक्षर *cअगरs_build_path_to_root(काष्ठा smb3_fs_context *ctx,
				     काष्ठा cअगरs_sb_info *cअगरs_sb,
				     काष्ठा cअगरs_tcon *tcon,
				     पूर्णांक add_treename);
बाह्य अक्षर *build_wildcard_path_from_dentry(काष्ठा dentry *direntry);
बाह्य अक्षर *cअगरs_compose_mount_options(स्थिर अक्षर *sb_mountdata,
		स्थिर अक्षर *fullpath, स्थिर काष्ठा dfs_info3_param *ref,
		अक्षर **devname);
/* बाह्य व्योम renew_parental_बारtamps(काष्ठा dentry *direntry);*/
बाह्य काष्ठा mid_q_entry *AllocMidQEntry(स्थिर काष्ठा smb_hdr *smb_buffer,
					काष्ठा TCP_Server_Info *server);
बाह्य व्योम DeleteMidQEntry(काष्ठा mid_q_entry *midEntry);
बाह्य व्योम cअगरs_delete_mid(काष्ठा mid_q_entry *mid);
बाह्य व्योम cअगरs_mid_q_entry_release(काष्ठा mid_q_entry *midEntry);
बाह्य व्योम cअगरs_wake_up_task(काष्ठा mid_q_entry *mid);
बाह्य पूर्णांक cअगरs_handle_standard(काष्ठा TCP_Server_Info *server,
				काष्ठा mid_q_entry *mid);
बाह्य पूर्णांक smb3_parse_devname(स्थिर अक्षर *devname, काष्ठा smb3_fs_context *ctx);
बाह्य पूर्णांक smb3_parse_opt(स्थिर अक्षर *options, स्थिर अक्षर *key, अक्षर **val);
बाह्य bool cअगरs_match_ipaddr(काष्ठा sockaddr *srcaddr, काष्ठा sockaddr *rhs);
बाह्य पूर्णांक cअगरs_discard_reमुख्यing_data(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक cअगरs_call_async(काष्ठा TCP_Server_Info *server,
			काष्ठा smb_rqst *rqst,
			mid_receive_t *receive, mid_callback_t *callback,
			mid_handle_t *handle, व्योम *cbdata, स्थिर पूर्णांक flags,
			स्थिर काष्ठा cअगरs_credits *exist_credits);
बाह्य काष्ठा TCP_Server_Info *cअगरs_pick_channel(काष्ठा cअगरs_ses *ses);
बाह्य पूर्णांक cअगरs_send_recv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			  काष्ठा TCP_Server_Info *server,
			  काष्ठा smb_rqst *rqst, पूर्णांक *resp_buf_type,
			  स्थिर पूर्णांक flags, काष्ठा kvec *resp_iov);
बाह्य पूर्णांक compound_send_recv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			      काष्ठा TCP_Server_Info *server,
			      स्थिर पूर्णांक flags, स्थिर पूर्णांक num_rqst,
			      काष्ठा smb_rqst *rqst, पूर्णांक *resp_buf_type,
			      काष्ठा kvec *resp_iov);
बाह्य पूर्णांक SendReceive(स्थिर अचिन्हित पूर्णांक /* xid */ , काष्ठा cअगरs_ses *,
			काष्ठा smb_hdr * /* input */ ,
			काष्ठा smb_hdr * /* out */ ,
			पूर्णांक * /* bytes वापसed */ , स्थिर पूर्णांक);
बाह्य पूर्णांक SendReceiveNoRsp(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			    अक्षर *in_buf, पूर्णांक flags);
बाह्य काष्ठा mid_q_entry *cअगरs_setup_request(काष्ठा cअगरs_ses *,
				काष्ठा TCP_Server_Info *,
				काष्ठा smb_rqst *);
बाह्य काष्ठा mid_q_entry *cअगरs_setup_async_request(काष्ठा TCP_Server_Info *,
						काष्ठा smb_rqst *);
बाह्य पूर्णांक cअगरs_check_receive(काष्ठा mid_q_entry *mid,
			काष्ठा TCP_Server_Info *server, bool log_error);
बाह्य पूर्णांक cअगरs_रुको_mtu_credits(काष्ठा TCP_Server_Info *server,
				 अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक *num,
				 काष्ठा cअगरs_credits *credits);
बाह्य पूर्णांक SendReceive2(स्थिर अचिन्हित पूर्णांक /* xid */ , काष्ठा cअगरs_ses *,
			काष्ठा kvec *, पूर्णांक /* nvec to send */,
			पूर्णांक * /* type of buf वापसed */, स्थिर पूर्णांक flags,
			काष्ठा kvec * /* resp vec */);
बाह्य पूर्णांक SendReceiveBlockingLock(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *ptcon,
			काष्ठा smb_hdr *in_buf ,
			काष्ठा smb_hdr *out_buf,
			पूर्णांक *bytes_वापसed);
बाह्य पूर्णांक cअगरs_reconnect(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक checkSMB(अक्षर *buf, अचिन्हित पूर्णांक len, काष्ठा TCP_Server_Info *srvr);
बाह्य bool is_valid_oplock_अवरोध(अक्षर *, काष्ठा TCP_Server_Info *);
बाह्य bool backup_cred(काष्ठा cअगरs_sb_info *);
बाह्य bool is_size_safe_to_change(काष्ठा cअगरsInodeInfo *, __u64 eof);
बाह्य व्योम cअगरs_update_eof(काष्ठा cअगरsInodeInfo *cअगरsi, loff_t offset,
			    अचिन्हित पूर्णांक bytes_written);
बाह्य काष्ठा cअगरsFileInfo *find_writable_file(काष्ठा cअगरsInodeInfo *, पूर्णांक);
बाह्य पूर्णांक cअगरs_get_writable_file(काष्ठा cअगरsInodeInfo *cअगरs_inode,
				  पूर्णांक flags,
				  काष्ठा cअगरsFileInfo **ret_file);
बाह्य पूर्णांक cअगरs_get_writable_path(काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
				  पूर्णांक flags,
				  काष्ठा cअगरsFileInfo **ret_file);
बाह्य काष्ठा cअगरsFileInfo *find_पढ़ोable_file(काष्ठा cअगरsInodeInfo *, bool);
बाह्य पूर्णांक cअगरs_get_पढ़ोable_path(काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
				  काष्ठा cअगरsFileInfo **ret_file);
बाह्य अचिन्हित पूर्णांक smbCalcSize(व्योम *buf, काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक decode_negTokenInit(अचिन्हित अक्षर *security_blob, पूर्णांक length,
			काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक cअगरs_convert_address(काष्ठा sockaddr *dst, स्थिर अक्षर *src, पूर्णांक len);
बाह्य व्योम cअगरs_set_port(काष्ठा sockaddr *addr, स्थिर अचिन्हित लघु पूर्णांक port);
बाह्य पूर्णांक map_smb_to_linux_error(अक्षर *buf, bool logErr);
बाह्य पूर्णांक map_and_check_smb_error(काष्ठा mid_q_entry *mid, bool logErr);
बाह्य व्योम header_assemble(काष्ठा smb_hdr *, अक्षर /* command */ ,
			    स्थिर काष्ठा cअगरs_tcon *, पूर्णांक /* length of
			    fixed section (word count) in two byte units */);
बाह्य पूर्णांक small_smb_init_no_tc(स्थिर पूर्णांक smb_cmd, स्थिर पूर्णांक wct,
				काष्ठा cअगरs_ses *ses,
				व्योम **request_buf);
बाह्य क्रमागत securityEnum select_sectype(काष्ठा TCP_Server_Info *server,
				क्रमागत securityEnum requested);
बाह्य पूर्णांक CIFS_SessSetup(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			  स्थिर काष्ठा nls_table *nls_cp);
बाह्य काष्ठा बारpec64 cअगरs_NTसमयToUnix(__le64 utc_nanoseconds_since_1601);
बाह्य u64 cअगरs_UnixTimeToNT(काष्ठा बारpec64);
बाह्य काष्ठा बारpec64 cnvrtDosUnixTm(__le16 le_date, __le16 le_समय,
				      पूर्णांक offset);
बाह्य व्योम cअगरs_set_oplock_level(काष्ठा cअगरsInodeInfo *cinode, __u32 oplock);
बाह्य पूर्णांक cअगरs_get_ग_लिखोr(काष्ठा cअगरsInodeInfo *cinode);
बाह्य व्योम cअगरs_put_ग_लिखोr(काष्ठा cअगरsInodeInfo *cinode);
बाह्य व्योम cअगरs_करोne_oplock_अवरोध(काष्ठा cअगरsInodeInfo *cinode);
बाह्य पूर्णांक cअगरs_unlock_range(काष्ठा cअगरsFileInfo *cfile,
			     काष्ठा file_lock *flock, स्थिर अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक cअगरs_push_mandatory_locks(काष्ठा cअगरsFileInfo *cfile);

बाह्य व्योम cअगरs_करोwn_ग_लिखो(काष्ठा rw_semaphore *sem);
बाह्य काष्ठा cअगरsFileInfo *cअगरs_new_fileinfo(काष्ठा cअगरs_fid *fid,
					      काष्ठा file *file,
					      काष्ठा tcon_link *tlink,
					      __u32 oplock);
बाह्य पूर्णांक cअगरs_posix_खोलो(स्थिर अक्षर *full_path, काष्ठा inode **inode,
			   काष्ठा super_block *sb, पूर्णांक mode,
			   अचिन्हित पूर्णांक f_flags, __u32 *oplock, __u16 *netfid,
			   अचिन्हित पूर्णांक xid);
व्योम cअगरs_fill_uniqueid(काष्ठा super_block *sb, काष्ठा cअगरs_fattr *fattr);
बाह्य व्योम cअगरs_unix_basic_to_fattr(काष्ठा cअगरs_fattr *fattr,
				     खाता_UNIX_BASIC_INFO *info,
				     काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य व्योम cअगरs_dir_info_to_fattr(काष्ठा cअगरs_fattr *, खाता_सूचीECTORY_INFO *,
					काष्ठा cअगरs_sb_info *);
बाह्य पूर्णांक cअगरs_fattr_to_inode(काष्ठा inode *inode, काष्ठा cअगरs_fattr *fattr);
बाह्य काष्ठा inode *cअगरs_iget(काष्ठा super_block *sb,
			       काष्ठा cअगरs_fattr *fattr);

बाह्य पूर्णांक cअगरs_get_inode_info(काष्ठा inode **inode, स्थिर अक्षर *full_path,
			       खाता_ALL_INFO *data, काष्ठा super_block *sb,
			       पूर्णांक xid, स्थिर काष्ठा cअगरs_fid *fid);
बाह्य पूर्णांक smb311_posix_get_inode_info(काष्ठा inode **pinode, स्थिर अक्षर *search_path,
			काष्ठा super_block *sb, अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक cअगरs_get_inode_info_unix(काष्ठा inode **pinode,
			स्थिर अचिन्हित अक्षर *search_path,
			काष्ठा super_block *sb, अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक cअगरs_set_file_info(काष्ठा inode *inode, काष्ठा iattr *attrs,
			      अचिन्हित पूर्णांक xid, स्थिर अक्षर *full_path, __u32 करोsattr);
बाह्य पूर्णांक cअगरs_नाम_pending_delete(स्थिर अक्षर *full_path,
				      काष्ठा dentry *dentry,
				      स्थिर अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक sid_to_id(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_sid *psid,
				काष्ठा cअगरs_fattr *fattr, uपूर्णांक sidtype);
बाह्य पूर्णांक cअगरs_acl_to_fattr(काष्ठा cअगरs_sb_info *cअगरs_sb,
			      काष्ठा cअगरs_fattr *fattr, काष्ठा inode *inode,
			      bool get_mode_from_special_sid,
			      स्थिर अक्षर *path, स्थिर काष्ठा cअगरs_fid *pfid);
बाह्य पूर्णांक id_mode_to_cअगरs_acl(काष्ठा inode *inode, स्थिर अक्षर *path, __u64 *pnmode,
					kuid_t uid, kgid_t gid);
बाह्य काष्ठा cअगरs_ntsd *get_cअगरs_acl(काष्ठा cअगरs_sb_info *, काष्ठा inode *,
				      स्थिर अक्षर *, u32 *, u32);
बाह्य काष्ठा cअगरs_ntsd *get_cअगरs_acl_by_fid(काष्ठा cअगरs_sb_info *,
				स्थिर काष्ठा cअगरs_fid *, u32 *, u32);
बाह्य पूर्णांक set_cअगरs_acl(काष्ठा cअगरs_ntsd *, __u32, काष्ठा inode *,
				स्थिर अक्षर *, पूर्णांक);
बाह्य अचिन्हित पूर्णांक setup_authusers_ACE(काष्ठा cअगरs_ace *pace);
बाह्य अचिन्हित पूर्णांक setup_special_mode_ACE(काष्ठा cअगरs_ace *pace, __u64 nmode);
बाह्य अचिन्हित पूर्णांक setup_special_user_owner_ACE(काष्ठा cअगरs_ace *pace);

बाह्य व्योम dequeue_mid(काष्ठा mid_q_entry *mid, bool malक्रमmed);
बाह्य पूर्णांक cअगरs_पढ़ो_from_socket(काष्ठा TCP_Server_Info *server, अक्षर *buf,
			         अचिन्हित पूर्णांक to_पढ़ो);
बाह्य sमाप_प्रकार cअगरs_discard_from_socket(काष्ठा TCP_Server_Info *server,
					माप_प्रकार to_पढ़ो);
बाह्य पूर्णांक cअगरs_पढ़ो_page_from_socket(काष्ठा TCP_Server_Info *server,
					काष्ठा page *page,
					अचिन्हित पूर्णांक page_offset,
					अचिन्हित पूर्णांक to_पढ़ो);
बाह्य पूर्णांक cअगरs_setup_cअगरs_sb(काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक cअगरs_match_super(काष्ठा super_block *, व्योम *);
बाह्य पूर्णांक cअगरs_mount(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा smb3_fs_context *ctx);
बाह्य व्योम cअगरs_umount(काष्ठा cअगरs_sb_info *);
बाह्य व्योम cअगरs_mark_खोलो_files_invalid(काष्ठा cअगरs_tcon *tcon);
बाह्य व्योम cअगरs_reखोलो_persistent_handles(काष्ठा cअगरs_tcon *tcon);

बाह्य bool cअगरs_find_lock_conflict(काष्ठा cअगरsFileInfo *cfile, __u64 offset,
				    __u64 length, __u8 type, __u16 flags,
				    काष्ठा cअगरsLockInfo **conf_lock,
				    पूर्णांक rw_check);
बाह्य व्योम cअगरs_add_pending_खोलो(काष्ठा cअगरs_fid *fid,
				  काष्ठा tcon_link *tlink,
				  काष्ठा cअगरs_pending_खोलो *खोलो);
बाह्य व्योम cअगरs_add_pending_खोलो_locked(काष्ठा cअगरs_fid *fid,
					 काष्ठा tcon_link *tlink,
					 काष्ठा cअगरs_pending_खोलो *खोलो);
बाह्य व्योम cअगरs_del_pending_खोलो(काष्ठा cअगरs_pending_खोलो *खोलो);

बाह्य bool cअगरs_is_deferred_बंद(काष्ठा cअगरsFileInfo *cfile,
				काष्ठा cअगरs_deferred_बंद **dबंद);

बाह्य व्योम cअगरs_add_deferred_बंद(काष्ठा cअगरsFileInfo *cfile,
				काष्ठा cअगरs_deferred_बंद *dबंद);

बाह्य व्योम cअगरs_del_deferred_बंद(काष्ठा cअगरsFileInfo *cfile);

बाह्य व्योम cअगरs_बंद_deferred_file(काष्ठा cअगरsInodeInfo *cअगरs_inode);

बाह्य व्योम cअगरs_बंद_all_deferred_files(काष्ठा cअगरs_tcon *cअगरs_tcon);

बाह्य काष्ठा TCP_Server_Info *cअगरs_get_tcp_session(काष्ठा smb3_fs_context *ctx);
बाह्य व्योम cअगरs_put_tcp_session(काष्ठा TCP_Server_Info *server,
				 पूर्णांक from_reconnect);
बाह्य व्योम cअगरs_put_tcon(काष्ठा cअगरs_tcon *tcon);

#अगर IS_ENABLED(CONFIG_CIFS_DFS_UPCALL)
बाह्य व्योम cअगरs_dfs_release_स्वतःmount_समयr(व्योम);
#अन्यथा /* ! IS_ENABLED(CONFIG_CIFS_DFS_UPCALL) */
#घोषणा cअगरs_dfs_release_स्वतःmount_समयr()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* ! IS_ENABLED(CONFIG_CIFS_DFS_UPCALL) */

व्योम cअगरs_proc_init(व्योम);
व्योम cअगरs_proc_clean(व्योम);

बाह्य व्योम cअगरs_move_llist(काष्ठा list_head *source, काष्ठा list_head *dest);
बाह्य व्योम cअगरs_मुक्त_llist(काष्ठा list_head *llist);
बाह्य व्योम cअगरs_del_lock_रुकोers(काष्ठा cअगरsLockInfo *lock);

बाह्य पूर्णांक cअगरs_tree_connect(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			     स्थिर काष्ठा nls_table *nlsc);

बाह्य पूर्णांक cअगरs_negotiate_protocol(स्थिर अचिन्हित पूर्णांक xid,
				   काष्ठा cअगरs_ses *ses);
बाह्य पूर्णांक cअगरs_setup_session(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			      काष्ठा nls_table *nls_info);
बाह्य पूर्णांक cअगरs_enable_signing(काष्ठा TCP_Server_Info *server, bool mnt_sign_required);
बाह्य पूर्णांक CIFSSMBNegotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses);

बाह्य पूर्णांक CIFSTCon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		    स्थिर अक्षर *tree, काष्ठा cअगरs_tcon *tcon,
		    स्थिर काष्ठा nls_table *);

बाह्य पूर्णांक CIFSFindFirst(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अक्षर *searchName, काष्ठा cअगरs_sb_info *cअगरs_sb,
		__u16 *searchHandle, __u16 search_flags,
		काष्ठा cअगरs_search_info *psrch_inf,
		bool msearch);

बाह्य पूर्णांक CIFSFindNext(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		__u16 searchHandle, __u16 search_flags,
		काष्ठा cअगरs_search_info *psrch_inf);

बाह्य पूर्णांक CIFSFindClose(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर __u16 search_handle);

बाह्य पूर्णांक CIFSSMBQFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u16 netfid, खाता_ALL_INFO *pFindData);
बाह्य पूर्णांक CIFSSMBQPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			    स्थिर अक्षर *search_Name, खाता_ALL_INFO *data,
			    पूर्णांक legacy /* whether to use old info level */,
			    स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);
बाह्य पूर्णांक SMBQueryInक्रमmation(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			       स्थिर अक्षर *search_name, खाता_ALL_INFO *data,
			       स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);

बाह्य पूर्णांक CIFSSMBUnixQFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u16 netfid, खाता_UNIX_BASIC_INFO *pFindData);
बाह्य पूर्णांक CIFSSMBUnixQPathInfo(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *tcon,
			स्थिर अचिन्हित अक्षर *searchName,
			खाता_UNIX_BASIC_INFO *pFindData,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);

बाह्य पूर्णांक CIFSGetDFSRefer(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			   स्थिर अक्षर *search_name,
			   काष्ठा dfs_info3_param **target_nodes,
			   अचिन्हित पूर्णांक *num_of_nodes,
			   स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);

बाह्य पूर्णांक parse_dfs_referrals(काष्ठा get_dfs_referral_rsp *rsp, u32 rsp_size,
			       अचिन्हित पूर्णांक *num_of_nodes,
			       काष्ठा dfs_info3_param **target_nodes,
			       स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap,
			       स्थिर अक्षर *searchName, bool is_unicode);
बाह्य व्योम reset_cअगरs_unix_caps(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				 काष्ठा cअगरs_sb_info *cअगरs_sb,
				 काष्ठा smb3_fs_context *ctx);
बाह्य पूर्णांक CIFSSMBQFSInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा kstatfs *FSData);
बाह्य पूर्णांक SMBOldQFSInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा kstatfs *FSData);
बाह्य पूर्णांक CIFSSMBSetFSUnixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			__u64 cap);

बाह्य पूर्णांक CIFSSMBQFSAttributeInfo(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक CIFSSMBQFSDeviceInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक CIFSSMBQFSUnixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक CIFSSMBQFSPosixInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा kstatfs *FSData);

बाह्य पूर्णांक CIFSSMBSetPathInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *fileName, स्थिर खाता_BASIC_INFO *data,
			स्थिर काष्ठा nls_table *nls_codepage,
			काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBSetFileInfo(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर खाता_BASIC_INFO *data, __u16 fid,
			__u32 pid_of_खोलोer);
बाह्य पूर्णांक CIFSSMBSetFileDisposition(स्थिर अचिन्हित पूर्णांक xid,
				     काष्ठा cअगरs_tcon *tcon,
				     bool delete_file, __u16 fid,
				     __u32 pid_of_खोलोer);
बाह्य पूर्णांक CIFSSMBSetखातापूर्ण(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 स्थिर अक्षर *file_name, __u64 size,
			 काष्ठा cअगरs_sb_info *cअगरs_sb, bool set_allocation);
बाह्य पूर्णांक CIFSSMBSetFileSize(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			      काष्ठा cअगरsFileInfo *cfile, __u64 size,
			      bool set_allocation);

काष्ठा cअगरs_unix_set_info_args अणु
	__u64	स_समय;
	__u64	aसमय;
	__u64	mसमय;
	__u64	mode;
	kuid_t	uid;
	kgid_t	gid;
	dev_t	device;
पूर्ण;

बाह्य पूर्णांक CIFSSMBUnixSetFileInfo(स्थिर अचिन्हित पूर्णांक xid,
				  काष्ठा cअगरs_tcon *tcon,
				  स्थिर काष्ठा cअगरs_unix_set_info_args *args,
				  u16 fid, u32 pid_of_खोलोer);

बाह्य पूर्णांक CIFSSMBUnixSetPathInfo(स्थिर अचिन्हित पूर्णांक xid,
				  काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *file_name,
				  स्थिर काष्ठा cअगरs_unix_set_info_args *args,
				  स्थिर काष्ठा nls_table *nls_codepage,
				  पूर्णांक remap);

बाह्य पूर्णांक CIFSSMBMkDir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
			umode_t mode, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBRmDir(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSPOSIXDelFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *name, __u16 type,
			स्थिर काष्ठा nls_table *nls_codepage,
			पूर्णांक remap_special_अक्षरs);
बाह्य पूर्णांक CIFSSMBDelFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBRename(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
			 काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBRenameOpenFile(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				 पूर्णांक netfid, स्थिर अक्षर *target_name,
				 स्थिर काष्ठा nls_table *nls_codepage,
				 पूर्णांक remap_special_अक्षरs);
बाह्य पूर्णांक CIFSCreateHardLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			      स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
			      काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSUnixCreateHardLink(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *fromName, स्थिर अक्षर *toName,
			स्थिर काष्ठा nls_table *nls_codepage,
			पूर्णांक remap_special_अक्षरs);
बाह्य पूर्णांक CIFSUnixCreateSymLink(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *fromName, स्थिर अक्षर *toName,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);
बाह्य पूर्णांक CIFSSMBUnixQuerySymLink(स्थिर अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *tcon,
			स्थिर अचिन्हित अक्षर *searchName, अक्षर **syminfo,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);
बाह्य पूर्णांक CIFSSMBQuerySymLink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			       __u16 fid, अक्षर **symlinkinfo,
			       स्थिर काष्ठा nls_table *nls_codepage);
बाह्य पूर्णांक CIFSSMB_set_compression(स्थिर अचिन्हित पूर्णांक xid,
				   काष्ठा cअगरs_tcon *tcon, __u16 fid);
बाह्य पूर्णांक CIFS_खोलो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms,
		     पूर्णांक *oplock, खाता_ALL_INFO *buf);
बाह्य पूर्णांक SMBLegacyOpen(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *fileName, स्थिर पूर्णांक disposition,
			स्थिर पूर्णांक access_flags, स्थिर पूर्णांक omode,
			__u16 *netfid, पूर्णांक *pOplock, खाता_ALL_INFO *,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);
बाह्य पूर्णांक CIFSPOSIXCreate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u32 posix_flags, __u64 mode, __u16 *netfid,
			खाता_UNIX_BASIC_INFO *pRetData,
			__u32 *pOplock, स्थिर अक्षर *name,
			स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap);
बाह्य पूर्णांक CIFSSMBClose(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर पूर्णांक smb_file_id);

बाह्य पूर्णांक CIFSSMBFlush(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर पूर्णांक smb_file_id);

बाह्य पूर्णांक CIFSSMBRead(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
			अचिन्हित पूर्णांक *nbytes, अक्षर **buf,
			पूर्णांक *वापस_buf_type);
बाह्य पूर्णांक CIFSSMBWrite(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
			अचिन्हित पूर्णांक *nbytes, स्थिर अक्षर *buf);
बाह्य पूर्णांक CIFSSMBWrite2(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
			अचिन्हित पूर्णांक *nbytes, काष्ठा kvec *iov, स्थिर पूर्णांक nvec);
बाह्य पूर्णांक CIFSGetSrvInodeNumber(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				 स्थिर अक्षर *search_name, __u64 *inode_number,
				 स्थिर काष्ठा nls_table *nls_codepage,
				 पूर्णांक remap);

बाह्य पूर्णांक cअगरs_lockv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      स्थिर __u16 netfid, स्थिर __u8 lock_type,
		      स्थिर __u32 num_unlock, स्थिर __u32 num_lock,
		      LOCKING_ANDX_RANGE *buf);
बाह्य पूर्णांक CIFSSMBLock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर __u16 netfid, स्थिर __u32 netpid, स्थिर __u64 len,
			स्थिर __u64 offset, स्थिर __u32 numUnlock,
			स्थिर __u32 numLock, स्थिर __u8 lockType,
			स्थिर bool रुकोFlag, स्थिर __u8 oplock_level);
बाह्य पूर्णांक CIFSSMBPosixLock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर __u16 smb_file_id, स्थिर __u32 netpid,
			स्थिर loff_t start_offset, स्थिर __u64 len,
			काष्ठा file_lock *, स्थिर __u16 lock_type,
			स्थिर bool रुकोFlag);
बाह्य पूर्णांक CIFSSMBTDis(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक CIFSSMBEcho(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक CIFSSMBLogoff(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses);

बाह्य काष्ठा cअगरs_ses *sesInfoAlloc(व्योम);
बाह्य व्योम sesInfoFree(काष्ठा cअगरs_ses *);
बाह्य काष्ठा cअगरs_tcon *tconInfoAlloc(व्योम);
बाह्य व्योम tconInfoFree(काष्ठा cअगरs_tcon *);

बाह्य पूर्णांक cअगरs_sign_rqst(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server,
		   __u32 *pexpected_response_sequence_number);
बाह्य पूर्णांक cअगरs_sign_smbv(काष्ठा kvec *iov, पूर्णांक n_vec, काष्ठा TCP_Server_Info *,
			  __u32 *);
बाह्य पूर्णांक cअगरs_sign_smb(काष्ठा smb_hdr *, काष्ठा TCP_Server_Info *, __u32 *);
बाह्य पूर्णांक cअगरs_verअगरy_signature(काष्ठा smb_rqst *rqst,
				 काष्ठा TCP_Server_Info *server,
				__u32 expected_sequence_number);
बाह्य पूर्णांक SMBNTencrypt(अचिन्हित अक्षर *, अचिन्हित अक्षर *, अचिन्हित अक्षर *,
			स्थिर काष्ठा nls_table *);
बाह्य पूर्णांक setup_ntlm_response(काष्ठा cअगरs_ses *, स्थिर काष्ठा nls_table *);
बाह्य पूर्णांक setup_ntlmv2_rsp(काष्ठा cअगरs_ses *, स्थिर काष्ठा nls_table *);
बाह्य व्योम cअगरs_crypto_secmech_release(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक calc_seckey(काष्ठा cअगरs_ses *);
बाह्य पूर्णांक generate_smb30signingkey(काष्ठा cअगरs_ses *);
बाह्य पूर्णांक generate_smb311signingkey(काष्ठा cअगरs_ses *);

#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
बाह्य पूर्णांक calc_lanman_hash(स्थिर अक्षर *password, स्थिर अक्षर *cryptkey,
				bool encrypt, अक्षर *lnm_session_key);
#पूर्ण_अगर /* CIFS_WEAK_PW_HASH */
बाह्य पूर्णांक CIFSSMBCopy(अचिन्हित पूर्णांक xid,
			काष्ठा cअगरs_tcon *source_tcon,
			स्थिर अक्षर *fromName,
			स्थिर __u16 target_tid,
			स्थिर अक्षर *toName, स्थिर पूर्णांक flags,
			स्थिर काष्ठा nls_table *nls_codepage,
			पूर्णांक remap_special_अक्षरs);
बाह्य sमाप_प्रकार CIFSSMBQAllEAs(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर अचिन्हित अक्षर *searchName,
			स्थिर अचिन्हित अक्षर *ea_name, अक्षर *EAData,
			माप_प्रकार bufsize, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBSetEA(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अक्षर *fileName, स्थिर अक्षर *ea_name,
		स्थिर व्योम *ea_value, स्थिर __u16 ea_value_len,
		स्थिर काष्ठा nls_table *nls_codepage,
		काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक CIFSSMBGetCIFSACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			__u16 fid, काष्ठा cअगरs_ntsd **acl_inf, __u32 *buflen);
बाह्य पूर्णांक CIFSSMBSetCIFSACL(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, __u16,
			काष्ठा cअगरs_ntsd *, __u32, पूर्णांक);
बाह्य पूर्णांक CIFSSMBGetPosixACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अचिन्हित अक्षर *searchName,
		अक्षर *acl_inf, स्थिर पूर्णांक buflen, स्थिर पूर्णांक acl_type,
		स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap_special_अक्षरs);
बाह्य पूर्णांक CIFSSMBSetPosixACL(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		स्थिर अचिन्हित अक्षर *fileName,
		स्थिर अक्षर *local_acl, स्थिर पूर्णांक buflen, स्थिर पूर्णांक acl_type,
		स्थिर काष्ठा nls_table *nls_codepage, पूर्णांक remap_special_अक्षरs);
बाह्य पूर्णांक CIFSGetExtAttr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			स्थिर पूर्णांक netfid, __u64 *pExtAttrBits, __u64 *pMask);
बाह्य व्योम cअगरs_स्वतःdisable_serverino(काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य bool couldbe_mf_symlink(स्थिर काष्ठा cअगरs_fattr *fattr);
बाह्य पूर्णांक check_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			      काष्ठा cअगरs_sb_info *cअगरs_sb,
			      काष्ठा cअगरs_fattr *fattr,
			      स्थिर अचिन्हित अक्षर *path);
बाह्य पूर्णांक mdfour(अचिन्हित अक्षर *, अचिन्हित अक्षर *, पूर्णांक);
बाह्य पूर्णांक E_md4hash(स्थिर अचिन्हित अक्षर *passwd, अचिन्हित अक्षर *p16,
			स्थिर काष्ठा nls_table *codepage);
बाह्य पूर्णांक SMBencrypt(अचिन्हित अक्षर *passwd, स्थिर अचिन्हित अक्षर *c8,
			अचिन्हित अक्षर *p24);

बाह्य पूर्णांक
cअगरs_setup_volume_info(काष्ठा smb3_fs_context *ctx, स्थिर अक्षर *mntopts, स्थिर अक्षर *devname);

बाह्य काष्ठा TCP_Server_Info *
cअगरs_find_tcp_session(काष्ठा smb3_fs_context *ctx);

बाह्य व्योम cअगरs_put_smb_ses(काष्ठा cअगरs_ses *ses);

बाह्य काष्ठा cअगरs_ses *
cअगरs_get_smb_ses(काष्ठा TCP_Server_Info *server, काष्ठा smb3_fs_context *ctx);

व्योम cअगरs_पढ़ोdata_release(काष्ठा kref *refcount);
पूर्णांक cअगरs_async_पढ़ोv(काष्ठा cअगरs_पढ़ोdata *rdata);
पूर्णांक cअगरs_पढ़ोv_receive(काष्ठा TCP_Server_Info *server, काष्ठा mid_q_entry *mid);

पूर्णांक cअगरs_async_ग_लिखोv(काष्ठा cअगरs_ग_लिखोdata *wdata,
		      व्योम (*release)(काष्ठा kref *kref));
व्योम cअगरs_ग_लिखोv_complete(काष्ठा work_काष्ठा *work);
काष्ठा cअगरs_ग_लिखोdata *cअगरs_ग_लिखोdata_alloc(अचिन्हित पूर्णांक nr_pages,
						work_func_t complete);
काष्ठा cअगरs_ग_लिखोdata *cअगरs_ग_लिखोdata_direct_alloc(काष्ठा page **pages,
						work_func_t complete);
व्योम cअगरs_ग_लिखोdata_release(काष्ठा kref *refcount);
पूर्णांक cअगरs_query_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  काष्ठा cअगरs_sb_info *cअगरs_sb,
			  स्थिर अचिन्हित अक्षर *path, अक्षर *pbuf,
			  अचिन्हित पूर्णांक *pbytes_पढ़ो);
पूर्णांक cअगरs_create_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			   काष्ठा cअगरs_sb_info *cअगरs_sb,
			   स्थिर अचिन्हित अक्षर *path, अक्षर *pbuf,
			   अचिन्हित पूर्णांक *pbytes_written);
पूर्णांक __cअगरs_calc_signature(काष्ठा smb_rqst *rqst,
			काष्ठा TCP_Server_Info *server, अक्षर *signature,
			काष्ठा shash_desc *shash);
क्रमागत securityEnum cअगरs_select_sectype(काष्ठा TCP_Server_Info *,
					क्रमागत securityEnum);
काष्ठा cअगरs_aio_ctx *cअगरs_aio_ctx_alloc(व्योम);
व्योम cअगरs_aio_ctx_release(काष्ठा kref *refcount);
पूर्णांक setup_aio_ctx_iter(काष्ठा cअगरs_aio_ctx *ctx, काष्ठा iov_iter *iter, पूर्णांक rw);
व्योम smb2_cached_lease_अवरोध(काष्ठा work_काष्ठा *work);

पूर्णांक cअगरs_alloc_hash(स्थिर अक्षर *name, काष्ठा crypto_shash **shash,
		    काष्ठा sdesc **sdesc);
व्योम cअगरs_मुक्त_hash(काष्ठा crypto_shash **shash, काष्ठा sdesc **sdesc);

बाह्य व्योम rqst_page_get_length(काष्ठा smb_rqst *rqst, अचिन्हित पूर्णांक page,
				अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक *offset);
काष्ठा cअगरs_chan *
cअगरs_ses_find_chan(काष्ठा cअगरs_ses *ses, काष्ठा TCP_Server_Info *server);
पूर्णांक cअगरs_try_adding_channels(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses);
bool is_server_using_अगरace(काष्ठा TCP_Server_Info *server,
			   काष्ठा cअगरs_server_अगरace *अगरace);
bool is_ses_using_अगरace(काष्ठा cअगरs_ses *ses, काष्ठा cअगरs_server_अगरace *अगरace);

व्योम extract_unc_hostname(स्थिर अक्षर *unc, स्थिर अक्षर **h, माप_प्रकार *len);
पूर्णांक copy_path_name(अक्षर *dst, स्थिर अक्षर *src);
पूर्णांक smb2_parse_query_directory(काष्ठा cअगरs_tcon *tcon, काष्ठा kvec *rsp_iov,
			       पूर्णांक resp_buftype,
			       काष्ठा cअगरs_search_info *srch_inf);

काष्ठा super_block *cअगरs_get_tcp_super(काष्ठा TCP_Server_Info *server);
व्योम cअगरs_put_tcp_super(काष्ठा super_block *sb);
पूर्णांक update_super_prepath(काष्ठा cअगरs_tcon *tcon, अक्षर *prefix);
अक्षर *extract_hostname(स्थिर अक्षर *unc);
अक्षर *extract_shaनाम(स्थिर अक्षर *unc);

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
अटल अंतरभूत पूर्णांक get_dfs_path(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			       स्थिर अक्षर *old_path,
			       स्थिर काष्ठा nls_table *nls_codepage,
			       काष्ठा dfs_info3_param *referral, पूर्णांक remap)
अणु
	वापस dfs_cache_find(xid, ses, nls_codepage, remap, old_path,
			      referral, शून्य);
पूर्ण

पूर्णांक match_target_ip(काष्ठा TCP_Server_Info *server,
		    स्थिर अक्षर *share, माप_प्रकार share_len,
		    bool *result);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक cअगरs_create_options(काष्ठा cअगरs_sb_info *cअगरs_sb, पूर्णांक options)
अणु
	अगर (cअगरs_sb && (backup_cred(cअगरs_sb)))
		वापस options | CREATE_OPEN_BACKUP_INTENT;
	अन्यथा
		वापस options;
पूर्ण

#पूर्ण_अगर			/* _CIFSPROTO_H */
