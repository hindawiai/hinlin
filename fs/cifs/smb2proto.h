<शैली गुरु>
/*
 *   fs/cअगरs/smb2proto.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002, 2011
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
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
#अगर_अघोषित _SMB2PROTO_H
#घोषणा _SMB2PROTO_H
#समावेश <linux/nls.h>
#समावेश <linux/key-type.h>

काष्ठा statfs;
काष्ठा smb_rqst;

/*
 *****************************************************************
 * All Prototypes
 *****************************************************************
 */
बाह्य पूर्णांक map_smb2_to_linux_error(अक्षर *buf, bool log_err);
बाह्य पूर्णांक smb2_check_message(अक्षर *buf, अचिन्हित पूर्णांक length,
			      काष्ठा TCP_Server_Info *server);
बाह्य अचिन्हित पूर्णांक smb2_calc_size(व्योम *buf, काष्ठा TCP_Server_Info *server);
बाह्य अक्षर *smb2_get_data_area_len(पूर्णांक *off, पूर्णांक *len,
				    काष्ठा smb2_sync_hdr *shdr);
बाह्य __le16 *cअगरs_convert_path_to_utf16(स्थिर अक्षर *from,
					  काष्ठा cअगरs_sb_info *cअगरs_sb);

बाह्य पूर्णांक smb2_verअगरy_signature(काष्ठा smb_rqst *, काष्ठा TCP_Server_Info *);
बाह्य पूर्णांक smb2_check_receive(काष्ठा mid_q_entry *mid,
			      काष्ठा TCP_Server_Info *server, bool log_error);
बाह्य काष्ठा mid_q_entry *smb2_setup_request(काष्ठा cअगरs_ses *ses,
					      काष्ठा TCP_Server_Info *,
					      काष्ठा smb_rqst *rqst);
बाह्य काष्ठा mid_q_entry *smb2_setup_async_request(
			काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst);
बाह्य काष्ठा cअगरs_ses *smb2_find_smb_ses(काष्ठा TCP_Server_Info *server,
					   __u64 ses_id);
बाह्य काष्ठा cअगरs_tcon *smb2_find_smb_tcon(काष्ठा TCP_Server_Info *server,
						__u64 ses_id, __u32  tid);
बाह्य पूर्णांक smb2_calc_signature(काष्ठा smb_rqst *rqst,
				काष्ठा TCP_Server_Info *server,
				bool allocate_crypto);
बाह्य पूर्णांक smb3_calc_signature(काष्ठा smb_rqst *rqst,
				काष्ठा TCP_Server_Info *server,
				bool allocate_crypto);
बाह्य व्योम smb2_echo_request(काष्ठा work_काष्ठा *work);
बाह्य __le32 smb2_get_lease_state(काष्ठा cअगरsInodeInfo *cinode);
बाह्य bool smb2_is_valid_oplock_अवरोध(अक्षर *buffer,
				       काष्ठा TCP_Server_Info *srv);
बाह्य काष्ठा cअगरs_ses *smb2_find_smb_ses(काष्ठा TCP_Server_Info *server,
					  __u64 ses_id);
बाह्य पूर्णांक smb3_handle_पढ़ो_data(काष्ठा TCP_Server_Info *server,
				 काष्ठा mid_q_entry *mid);

बाह्य पूर्णांक खोलो_cached_dir(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			   स्थिर अक्षर *path,
			   काष्ठा cअगरs_sb_info *cअगरs_sb,
			   काष्ठा cached_fid **cfid);
बाह्य पूर्णांक खोलो_cached_dir_by_dentry(काष्ठा cअगरs_tcon *tcon,
				     काष्ठा dentry *dentry,
				     काष्ठा cached_fid **cfid);
बाह्य व्योम बंद_cached_dir(काष्ठा cached_fid *cfid);
बाह्य व्योम बंद_cached_dir_lease(काष्ठा cached_fid *cfid);
बाह्य व्योम बंद_cached_dir_lease_locked(काष्ठा cached_fid *cfid);
बाह्य व्योम move_smb2_info_to_cअगरs(खाता_ALL_INFO *dst,
				   काष्ठा smb2_file_all_info *src);
बाह्य पूर्णांक smb2_query_reparse_tag(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *path,
				__u32 *reparse_tag);
बाह्य पूर्णांक smb2_query_path_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				काष्ठा cअगरs_sb_info *cअगरs_sb,
				स्थिर अक्षर *full_path, खाता_ALL_INFO *data,
				bool *adjust_tz, bool *symlink);
बाह्य पूर्णांक smb2_set_path_size(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			      स्थिर अक्षर *full_path, __u64 size,
			      काष्ठा cअगरs_sb_info *cअगरs_sb, bool set_alloc);
बाह्य पूर्णांक smb2_set_file_info(काष्ठा inode *inode, स्थिर अक्षर *full_path,
			      खाता_BASIC_INFO *buf, स्थिर अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक smb311_posix_सूची_गढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
			       umode_t mode, काष्ठा cअगरs_tcon *tcon,
			       स्थिर अक्षर *full_path,
			       काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक smb2_सूची_गढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
		      umode_t mode, काष्ठा cअगरs_tcon *tcon,
		      स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य व्योम smb2_सूची_गढ़ो_setinfo(काष्ठा inode *inode, स्थिर अक्षर *full_path,
			       काष्ठा cअगरs_sb_info *cअगरs_sb,
			       काष्ठा cअगरs_tcon *tcon, स्थिर अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक smb2_सूची_हटाओ(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक smb2_unlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       स्थिर अक्षर *name, काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक smb2_नाम_path(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			    स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
			    काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक smb2_create_hardlink(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				स्थिर अक्षर *from_name, स्थिर अक्षर *to_name,
				काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य पूर्णांक smb3_create_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अचिन्हित अक्षर *path,
			अक्षर *pbuf, अचिन्हित पूर्णांक *pbytes_written);
बाह्य पूर्णांक smb3_query_mf_symlink(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  काष्ठा cअगरs_sb_info *cअगरs_sb,
			  स्थिर अचिन्हित अक्षर *path, अक्षर *pbuf,
			  अचिन्हित पूर्णांक *pbytes_पढ़ो);
बाह्य पूर्णांक smb2_खोलो_file(स्थिर अचिन्हित पूर्णांक xid,
			  काष्ठा cअगरs_खोलो_parms *oparms,
			  __u32 *oplock, खाता_ALL_INFO *buf);
बाह्य पूर्णांक smb2_unlock_range(काष्ठा cअगरsFileInfo *cfile,
			     काष्ठा file_lock *flock, स्थिर अचिन्हित पूर्णांक xid);
बाह्य पूर्णांक smb2_push_mandatory_locks(काष्ठा cअगरsFileInfo *cfile);
बाह्य व्योम smb2_reconnect_server(काष्ठा work_काष्ठा *work);
बाह्य पूर्णांक smb3_crypto_aead_allocate(काष्ठा TCP_Server_Info *server);
बाह्य अचिन्हित दीर्घ smb_rqst_len(काष्ठा TCP_Server_Info *server,
				  काष्ठा smb_rqst *rqst);
बाह्य व्योम smb2_set_next_command(काष्ठा cअगरs_tcon *tcon,
				  काष्ठा smb_rqst *rqst);
बाह्य व्योम smb2_set_related(काष्ठा smb_rqst *rqst);

/*
 * SMB2 Worker functions - most of protocol specअगरic implementation details
 * are contained within these calls.
 */
बाह्य पूर्णांक SMB2_negotiate(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses);
बाह्य पूर्णांक SMB2_sess_setup(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
			   स्थिर काष्ठा nls_table *nls_cp);
बाह्य पूर्णांक SMB2_logoff(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses);
बाह्य पूर्णांक SMB2_tcon(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		     स्थिर अक्षर *tree, काष्ठा cअगरs_tcon *tcon,
		     स्थिर काष्ठा nls_table *);
बाह्य पूर्णांक SMB2_tdis(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक SMB2_खोलो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_खोलो_parms *oparms,
		     __le16 *path, __u8 *oplock,
		     काष्ठा smb2_file_all_info *buf,
		     काष्ठा create_posix_rsp *posix,
		     काष्ठा kvec *err_iov, पूर्णांक *resp_buftype);
बाह्य पूर्णांक SMB2_खोलो_init(काष्ठा cअगरs_tcon *tcon,
			  काष्ठा TCP_Server_Info *server,
			  काष्ठा smb_rqst *rqst,
			  __u8 *oplock, काष्ठा cअगरs_खोलो_parms *oparms,
			  __le16 *path);
बाह्य व्योम SMB2_खोलो_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_ioctl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     u64 persistent_fid, u64 अस्थिर_fid, u32 opcode,
		     bool is_fsctl, अक्षर *in_data, u32 indatalen, u32 maxoutlen,
		     अक्षर **out_data, u32 *plen /* वापसed data len */);
बाह्य पूर्णांक SMB2_ioctl_init(काष्ठा cअगरs_tcon *tcon,
			   काष्ठा TCP_Server_Info *server,
			   काष्ठा smb_rqst *rqst,
			   u64 persistent_fid, u64 अस्थिर_fid, u32 opcode,
			   bool is_fsctl, अक्षर *in_data, u32 indatalen,
			   __u32 max_response_size);
बाह्य व्योम SMB2_ioctl_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_change_notअगरy(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u64 persistent_fid, u64 अस्थिर_fid, bool watch_tree,
			u32 completion_filter);

बाह्य पूर्णांक __SMB2_बंद(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u64 persistent_fid, u64 अस्थिर_fid,
			काष्ठा smb2_file_network_खोलो_info *pbuf);
बाह्य पूर्णांक SMB2_बंद(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      u64 persistent_file_id, u64 अस्थिर_file_id);
बाह्य पूर्णांक SMB2_बंद_init(काष्ठा cअगरs_tcon *tcon,
			   काष्ठा TCP_Server_Info *server,
			   काष्ठा smb_rqst *rqst,
			   u64 persistent_fid, u64 अस्थिर_fid,
			   bool query_attrs);
बाह्य व्योम SMB2_बंद_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_flush(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      u64 persistent_file_id, u64 अस्थिर_file_id);
बाह्य पूर्णांक SMB2_flush_init(स्थिर अचिन्हित पूर्णांक xid, काष्ठा smb_rqst *rqst,
			   काष्ठा cअगरs_tcon *tcon,
			   काष्ठा TCP_Server_Info *server,
			   u64 persistent_file_id, u64 अस्थिर_file_id);
बाह्य व्योम SMB2_flush_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB311_posix_query_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		u64 persistent_fid, u64 अस्थिर_fid, काष्ठा smb311_posix_qinfo *data, u32 *plen);
बाह्य पूर्णांक SMB2_query_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			   u64 persistent_file_id, u64 अस्थिर_file_id,
			   काष्ठा smb2_file_all_info *data);
बाह्य पूर्णांक SMB2_query_info_init(काष्ठा cअगरs_tcon *tcon,
				काष्ठा TCP_Server_Info *server,
				काष्ठा smb_rqst *rqst,
				u64 persistent_fid, u64 अस्थिर_fid,
				u8 info_class, u8 info_type,
				u32 additional_info, माप_प्रकार output_len,
				माप_प्रकार input_len, व्योम *input);
बाह्य व्योम SMB2_query_info_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_query_acl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			  u64 persistent_file_id, u64 अस्थिर_file_id,
			  व्योम **data, अचिन्हित पूर्णांक *plen, u32 info);
बाह्य पूर्णांक SMB2_get_srv_num(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			    u64 persistent_fid, u64 अस्थिर_fid,
			    __le64 *uniqueid);
बाह्य पूर्णांक smb2_async_पढ़ोv(काष्ठा cअगरs_पढ़ोdata *rdata);
बाह्य पूर्णांक SMB2_पढ़ो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
		     अचिन्हित पूर्णांक *nbytes, अक्षर **buf, पूर्णांक *buf_type);
बाह्य पूर्णांक smb2_async_ग_लिखोv(काष्ठा cअगरs_ग_लिखोdata *wdata,
			     व्योम (*release)(काष्ठा kref *kref));
बाह्य पूर्णांक SMB2_ग_लिखो(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_io_parms *io_parms,
		      अचिन्हित पूर्णांक *nbytes, काष्ठा kvec *iov, पूर्णांक n_vec);
बाह्य पूर्णांक SMB2_echo(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक SMB2_query_directory(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				u64 persistent_fid, u64 अस्थिर_fid, पूर्णांक index,
				काष्ठा cअगरs_search_info *srch_inf);
बाह्य पूर्णांक SMB2_query_directory_init(अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				     काष्ठा TCP_Server_Info *server,
				     काष्ठा smb_rqst *rqst,
				     u64 persistent_fid, u64 अस्थिर_fid,
				     पूर्णांक index, पूर्णांक info_level);
बाह्य व्योम SMB2_query_directory_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_set_eof(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u64 persistent_fid, u64 अस्थिर_fid, u32 pid,
			__le64 *eof);
बाह्य पूर्णांक SMB2_set_info_init(काष्ठा cअगरs_tcon *tcon,
			      काष्ठा TCP_Server_Info *server,
			      काष्ठा smb_rqst *rqst,
			      u64 persistent_fid, u64 अस्थिर_fid, u32 pid,
			      u8 info_class, u8 info_type, u32 additional_info,
			      व्योम **data, अचिन्हित पूर्णांक *size);
बाह्य व्योम SMB2_set_info_मुक्त(काष्ठा smb_rqst *rqst);
बाह्य पूर्णांक SMB2_set_acl(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			u64 persistent_fid, u64 अस्थिर_fid,
			काष्ठा cअगरs_ntsd *pnntsd, पूर्णांक pacllen, पूर्णांक aclflag);
बाह्य पूर्णांक SMB2_set_ea(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		       u64 persistent_fid, u64 अस्थिर_fid,
		       काष्ठा smb2_file_full_ea_info *buf, पूर्णांक len);
बाह्य पूर्णांक SMB2_set_compression(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				u64 persistent_fid, u64 अस्थिर_fid);
बाह्य पूर्णांक SMB2_oplock_अवरोध(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			     स्थिर u64 persistent_fid, स्थिर u64 अस्थिर_fid,
			     स्थिर __u8 oplock_level);
बाह्य पूर्णांक smb2_handle_cancelled_बंद(काष्ठा cअगरs_tcon *tcon,
				       __u64 persistent_fid,
				       __u64 अस्थिर_fid);
बाह्य पूर्णांक smb2_handle_cancelled_mid(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server);
व्योम smb2_cancelled_बंद_fid(काष्ठा work_काष्ठा *work);
बाह्य पूर्णांक SMB2_QFS_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 u64 persistent_file_id, u64 अस्थिर_file_id,
			 काष्ठा kstatfs *FSData);
बाह्य पूर्णांक SMB311_posix_qfs_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 u64 persistent_file_id, u64 अस्थिर_file_id,
			 काष्ठा kstatfs *FSData);
बाह्य पूर्णांक SMB2_QFS_attr(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			 u64 persistent_file_id, u64 अस्थिर_file_id, पूर्णांक lvl);
बाह्य पूर्णांक SMB2_lock(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		     स्थिर __u64 persist_fid, स्थिर __u64 अस्थिर_fid,
		     स्थिर __u32 pid, स्थिर __u64 length, स्थिर __u64 offset,
		     स्थिर __u32 lockFlags, स्थिर bool रुको);
बाह्य पूर्णांक smb2_lockv(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      स्थिर __u64 persist_fid, स्थिर __u64 अस्थिर_fid,
		      स्थिर __u32 pid, स्थिर __u32 num_lock,
		      काष्ठा smb2_lock_element *buf);
बाह्य पूर्णांक SMB2_lease_अवरोध(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			    __u8 *lease_key, स्थिर __le32 lease_state);
बाह्य पूर्णांक smb3_validate_negotiate(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *);

बाह्य क्रमागत securityEnum smb2_select_sectype(काष्ठा TCP_Server_Info *,
					क्रमागत securityEnum);
बाह्य व्योम smb2_parse_contexts(काष्ठा TCP_Server_Info *server,
				काष्ठा smb2_create_rsp *rsp,
				अचिन्हित पूर्णांक *epoch, अक्षर *lease_key,
				__u8 *oplock, काष्ठा smb2_file_all_info *buf,
				काष्ठा create_posix_rsp *posix);
बाह्य पूर्णांक smb3_encryption_required(स्थिर काष्ठा cअगरs_tcon *tcon);
बाह्य पूर्णांक smb2_validate_iov(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक buffer_length,
			     काष्ठा kvec *iov, अचिन्हित पूर्णांक min_buf_size);
बाह्य पूर्णांक smb2_validate_and_copy_iov(अचिन्हित पूर्णांक offset,
				      अचिन्हित पूर्णांक buffer_length,
				      काष्ठा kvec *iov,
				      अचिन्हित पूर्णांक minbufsize, अक्षर *data);
बाह्य व्योम smb2_copy_fs_info_to_kstatfs(
	 काष्ठा smb2_fs_full_size_info *pfs_inf,
	 काष्ठा kstatfs *kst);
बाह्य पूर्णांक smb311_crypto_shash_allocate(काष्ठा TCP_Server_Info *server);
बाह्य पूर्णांक smb311_update_preauth_hash(काष्ठा cअगरs_ses *ses,
				      काष्ठा kvec *iov, पूर्णांक nvec);
बाह्य पूर्णांक smb2_query_info_compound(स्थिर अचिन्हित पूर्णांक xid,
				    काष्ठा cअगरs_tcon *tcon,
				    __le16 *utf16_path, u32 desired_access,
				    u32 class, u32 type, u32 output_len,
				    काष्ठा kvec *rsp, पूर्णांक *buftype,
				    काष्ठा cअगरs_sb_info *cअगरs_sb);
/* query path info from the server using SMB311 POSIX extensions*/
बाह्य पूर्णांक smb311_posix_query_path_info(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			काष्ठा cअगरs_sb_info *sb, स्थिर अक्षर *path, काष्ठा smb311_posix_qinfo *qinf,
			bool *adjust_tx, bool *symlink);
पूर्णांक posix_info_parse(स्थिर व्योम *beg, स्थिर व्योम *end,
		     काष्ठा smb2_posix_info_parsed *out);
पूर्णांक posix_info_sid_size(स्थिर व्योम *beg, स्थिर व्योम *end);
#पूर्ण_अगर			/* _SMB2PROTO_H */
