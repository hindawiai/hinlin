<शैली गुरु>
/*
 *  fs/nfs/nfs4xdr.c
 *
 *  Client-side XDR क्रम NFSv4.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/param.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/module.h>
#समावेश <linux/utsname.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>

#समावेश "nfs4_fs.h"
#समावेश "nfs4trace.h"
#समावेश "internal.h"
#समावेश "nfs4idmap.h"
#समावेश "nfs4session.h"
#समावेश "pnfs.h"
#समावेश "netns.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_XDR

/* Mapping from NFS error code to "errno" error code. */
#घोषणा त्रुटि_सं_NFSERR_IO		EIO

काष्ठा compound_hdr;
अटल पूर्णांक nfs4_stat_to_त्रुटि_सं(पूर्णांक);
अटल व्योम encode_layoutget(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs4_layoutget_args *args,
			     काष्ठा compound_hdr *hdr);
अटल पूर्णांक decode_layoutget(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req,
			     काष्ठा nfs4_layoutget_res *res);

/* NFSv4 COMPOUND tags are only wanted क्रम debugging purposes */
#अगर_घोषित DEBUG
#घोषणा NFS4_MAXTAGLEN		20
#अन्यथा
#घोषणा NFS4_MAXTAGLEN		0
#पूर्ण_अगर

/* lock,खोलो owner id:
 * we currently use size 2 (u64) out of (NFS4_OPAQUE_LIMIT  >> 2)
 */
#घोषणा pagepad_maxsz		(1)
#घोषणा खोलो_owner_id_maxsz	(1 + 2 + 1 + 1 + 2)
#घोषणा lock_owner_id_maxsz	(1 + 1 + 4)
#घोषणा decode_lockowner_maxsz	(1 + XDR_QUADLEN(IDMAP_NAMESZ))
#घोषणा compound_encode_hdr_maxsz	(3 + (NFS4_MAXTAGLEN >> 2))
#घोषणा compound_decode_hdr_maxsz	(3 + (NFS4_MAXTAGLEN >> 2))
#घोषणा op_encode_hdr_maxsz	(1)
#घोषणा op_decode_hdr_maxsz	(2)
#घोषणा encode_stateid_maxsz	(XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा decode_stateid_maxsz	(XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा encode_verअगरier_maxsz	(XDR_QUADLEN(NFS4_VERIFIER_SIZE))
#घोषणा decode_verअगरier_maxsz	(XDR_QUADLEN(NFS4_VERIFIER_SIZE))
#घोषणा encode_putfh_maxsz	(op_encode_hdr_maxsz + 1 + \
				(NFS4_FHSIZE >> 2))
#घोषणा decode_putfh_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_putrootfh_maxsz	(op_encode_hdr_maxsz)
#घोषणा decode_putrootfh_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_getfh_maxsz      (op_encode_hdr_maxsz)
#घोषणा decode_getfh_maxsz      (op_decode_hdr_maxsz + 1 + \
				((3+NFS4_FHSIZE) >> 2))
#घोषणा nfs4_fattr_biपंचांगap_maxsz 4
#घोषणा encode_getattr_maxsz    (op_encode_hdr_maxsz + nfs4_fattr_biपंचांगap_maxsz)
#घोषणा nfsसमय4_maxsz		(3)
#घोषणा nfs4_name_maxsz		(1 + ((3 + NFS4_MAXNAMLEN) >> 2))
#घोषणा nfs4_path_maxsz		(1 + ((3 + NFS4_MAXPATHLEN) >> 2))
#घोषणा nfs4_owner_maxsz	(1 + XDR_QUADLEN(IDMAP_NAMESZ))
#घोषणा nfs4_group_maxsz	(1 + XDR_QUADLEN(IDMAP_NAMESZ))
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
/* PI(4 bytes) + LFS(4 bytes) + 1(क्रम null terminator?) + MAXLABELLEN */
#घोषणा	nfs4_label_maxsz	(4 + 4 + 1 + XDR_QUADLEN(NFS4_MAXLABELLEN))
#अन्यथा
#घोषणा	nfs4_label_maxsz	0
#पूर्ण_अगर
/* We support only one layout type per file प्रणाली */
#घोषणा decode_mdsthreshold_maxsz (1 + 1 + nfs4_fattr_biपंचांगap_maxsz + 1 + 8)
/* This is based on getfattr, which uses the most attributes: */
#घोषणा nfs4_fattr_value_maxsz	(1 + (1 + 2 + 2 + 4 + 2 + 1 + 1 + 2 + 2 + \
				3*nfsसमय4_maxsz + \
				nfs4_owner_maxsz + \
				nfs4_group_maxsz + nfs4_label_maxsz + \
				 decode_mdsthreshold_maxsz))
#घोषणा nfs4_fattr_maxsz	(nfs4_fattr_biपंचांगap_maxsz + \
				nfs4_fattr_value_maxsz)
#घोषणा decode_getattr_maxsz    (op_decode_hdr_maxsz + nfs4_fattr_maxsz)
#घोषणा encode_attrs_maxsz	(nfs4_fattr_biपंचांगap_maxsz + \
				 1 + 2 + 1 + \
				nfs4_owner_maxsz + \
				nfs4_group_maxsz + \
				nfs4_label_maxsz + \
				1 + nfsसमय4_maxsz + \
				1 + nfsसमय4_maxsz)
#घोषणा encode_savefh_maxsz     (op_encode_hdr_maxsz)
#घोषणा decode_savefh_maxsz     (op_decode_hdr_maxsz)
#घोषणा encode_restorefh_maxsz  (op_encode_hdr_maxsz)
#घोषणा decode_restorefh_maxsz  (op_decode_hdr_maxsz)
#घोषणा encode_fsinfo_maxsz	(encode_getattr_maxsz)
/* The 5 accounts क्रम the PNFS attributes, and assumes that at most three
 * layout types will be वापसed.
 */
#घोषणा decode_fsinfo_maxsz	(op_decode_hdr_maxsz + \
				 nfs4_fattr_biपंचांगap_maxsz + 1 + \
				 1 /* lease समय */ + \
				 2 /* max filesize */ + \
				 2 /* max पढ़ो */ + \
				 2 /* max ग_लिखो */ + \
				 nfsसमय4_maxsz /* समय delta */ + \
				 5 /* fs layout types */ + \
				 1 /* layout blksize */ + \
				 1 /* clone blksize */ + \
				 1 /* change attr type */ + \
				 1 /* xattr support */)
#घोषणा encode_renew_maxsz	(op_encode_hdr_maxsz + 3)
#घोषणा decode_renew_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_setclientid_maxsz \
				(op_encode_hdr_maxsz + \
				XDR_QUADLEN(NFS4_VERIFIER_SIZE) + \
				/* client name */ \
				1 + XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
				1 /* sc_prog */ + \
				1 + XDR_QUADLEN(RPCBIND_MAXNETIDLEN) + \
				1 + XDR_QUADLEN(RPCBIND_MAXUADDRLEN) + \
				1) /* sc_cb_ident */
#घोषणा decode_setclientid_maxsz \
				(op_decode_hdr_maxsz + \
				2 /* clientid */ + \
				XDR_QUADLEN(NFS4_VERIFIER_SIZE) + \
				1 + XDR_QUADLEN(RPCBIND_MAXNETIDLEN) + \
				1 + XDR_QUADLEN(RPCBIND_MAXUADDRLEN))
#घोषणा encode_setclientid_confirm_maxsz \
				(op_encode_hdr_maxsz + \
				3 + (NFS4_VERIFIER_SIZE >> 2))
#घोषणा decode_setclientid_confirm_maxsz \
				(op_decode_hdr_maxsz)
#घोषणा encode_lookup_maxsz	(op_encode_hdr_maxsz + nfs4_name_maxsz)
#घोषणा decode_lookup_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_lookupp_maxsz	(op_encode_hdr_maxsz)
#घोषणा decode_lookupp_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_share_access_maxsz \
				(2)
#घोषणा encode_createmode_maxsz	(1 + encode_attrs_maxsz + encode_verअगरier_maxsz)
#घोषणा encode_खोलोtype_maxsz	(1 + encode_createmode_maxsz)
#घोषणा encode_claim_null_maxsz	(1 + nfs4_name_maxsz)
#घोषणा encode_खोलो_maxsz	(op_encode_hdr_maxsz + \
				2 + encode_share_access_maxsz + 2 + \
				खोलो_owner_id_maxsz + \
				encode_खोलोtype_maxsz + \
				encode_claim_null_maxsz)
#घोषणा decode_space_limit_maxsz	(3)
#घोषणा decode_ace_maxsz	(3 + nfs4_owner_maxsz)
#घोषणा decode_delegation_maxsz	(1 + decode_stateid_maxsz + 1 + \
				decode_space_limit_maxsz + \
				decode_ace_maxsz)
#घोषणा decode_change_info_maxsz	(5)
#घोषणा decode_खोलो_maxsz	(op_decode_hdr_maxsz + \
				decode_stateid_maxsz + \
				decode_change_info_maxsz + 1 + \
				nfs4_fattr_biपंचांगap_maxsz + \
				decode_delegation_maxsz)
#घोषणा encode_खोलो_confirm_maxsz \
				(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + 1)
#घोषणा decode_खोलो_confirm_maxsz \
				(op_decode_hdr_maxsz + \
				 decode_stateid_maxsz)
#घोषणा encode_खोलो_करोwngrade_maxsz \
				(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + 1 + \
				 encode_share_access_maxsz)
#घोषणा decode_खोलो_करोwngrade_maxsz \
				(op_decode_hdr_maxsz + \
				 decode_stateid_maxsz)
#घोषणा encode_बंद_maxsz	(op_encode_hdr_maxsz + \
				 1 + encode_stateid_maxsz)
#घोषणा decode_बंद_maxsz	(op_decode_hdr_maxsz + \
				 decode_stateid_maxsz)
#घोषणा encode_setattr_maxsz	(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + \
				 encode_attrs_maxsz)
#घोषणा decode_setattr_maxsz	(op_decode_hdr_maxsz + \
				 nfs4_fattr_biपंचांगap_maxsz)
#घोषणा encode_पढ़ो_maxsz	(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + 3)
#घोषणा decode_पढ़ो_maxsz	(op_decode_hdr_maxsz + 2 + pagepad_maxsz)
#घोषणा encode_सूची_पढ़ो_maxsz	(op_encode_hdr_maxsz + \
				 2 + encode_verअगरier_maxsz + 5 + \
				nfs4_label_maxsz)
#घोषणा decode_सूची_पढ़ो_maxsz	(op_decode_hdr_maxsz + \
				 decode_verअगरier_maxsz + pagepad_maxsz)
#घोषणा encode_पढ़ोlink_maxsz	(op_encode_hdr_maxsz)
#घोषणा decode_पढ़ोlink_maxsz	(op_decode_hdr_maxsz + 1 + pagepad_maxsz)
#घोषणा encode_ग_लिखो_maxsz	(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + 4)
#घोषणा decode_ग_लिखो_maxsz	(op_decode_hdr_maxsz + \
				 2 + decode_verअगरier_maxsz)
#घोषणा encode_commit_maxsz	(op_encode_hdr_maxsz + 3)
#घोषणा decode_commit_maxsz	(op_decode_hdr_maxsz + \
				 decode_verअगरier_maxsz)
#घोषणा encode_हटाओ_maxsz	(op_encode_hdr_maxsz + \
				nfs4_name_maxsz)
#घोषणा decode_हटाओ_maxsz	(op_decode_hdr_maxsz + \
				 decode_change_info_maxsz)
#घोषणा encode_नाम_maxsz	(op_encode_hdr_maxsz + \
				2 * nfs4_name_maxsz)
#घोषणा decode_नाम_maxsz	(op_decode_hdr_maxsz + \
				 decode_change_info_maxsz + \
				 decode_change_info_maxsz)
#घोषणा encode_link_maxsz	(op_encode_hdr_maxsz + \
				nfs4_name_maxsz)
#घोषणा decode_link_maxsz	(op_decode_hdr_maxsz + decode_change_info_maxsz)
#घोषणा encode_lockowner_maxsz	(7)
#घोषणा encode_lock_maxsz	(op_encode_hdr_maxsz + \
				 7 + \
				 1 + encode_stateid_maxsz + 1 + \
				 encode_lockowner_maxsz)
#घोषणा decode_lock_denied_maxsz \
				(8 + decode_lockowner_maxsz)
#घोषणा decode_lock_maxsz	(op_decode_hdr_maxsz + \
				 decode_lock_denied_maxsz)
#घोषणा encode_lockt_maxsz	(op_encode_hdr_maxsz + 5 + \
				encode_lockowner_maxsz)
#घोषणा decode_lockt_maxsz	(op_decode_hdr_maxsz + \
				 decode_lock_denied_maxsz)
#घोषणा encode_locku_maxsz	(op_encode_hdr_maxsz + 3 + \
				 encode_stateid_maxsz + \
				 4)
#घोषणा decode_locku_maxsz	(op_decode_hdr_maxsz + \
				 decode_stateid_maxsz)
#घोषणा encode_release_lockowner_maxsz \
				(op_encode_hdr_maxsz + \
				 encode_lockowner_maxsz)
#घोषणा decode_release_lockowner_maxsz \
				(op_decode_hdr_maxsz)
#घोषणा encode_access_maxsz	(op_encode_hdr_maxsz + 1)
#घोषणा decode_access_maxsz	(op_decode_hdr_maxsz + 2)
#घोषणा encode_symlink_maxsz	(op_encode_hdr_maxsz + \
				1 + nfs4_name_maxsz + \
				1 + \
				nfs4_fattr_maxsz)
#घोषणा decode_symlink_maxsz	(op_decode_hdr_maxsz + 8)
#घोषणा encode_create_maxsz	(op_encode_hdr_maxsz + \
				1 + 2 + nfs4_name_maxsz + \
				encode_attrs_maxsz)
#घोषणा decode_create_maxsz	(op_decode_hdr_maxsz + \
				decode_change_info_maxsz + \
				nfs4_fattr_biपंचांगap_maxsz)
#घोषणा encode_statfs_maxsz	(encode_getattr_maxsz)
#घोषणा decode_statfs_maxsz	(decode_getattr_maxsz)
#घोषणा encode_delegवापस_maxsz (op_encode_hdr_maxsz + 4)
#घोषणा decode_delegवापस_maxsz (op_decode_hdr_maxsz)
#घोषणा encode_getacl_maxsz	(encode_getattr_maxsz)
#घोषणा decode_getacl_maxsz	(op_decode_hdr_maxsz + \
				 nfs4_fattr_biपंचांगap_maxsz + 1 + pagepad_maxsz)
#घोषणा encode_setacl_maxsz	(op_encode_hdr_maxsz + \
				 encode_stateid_maxsz + 3)
#घोषणा decode_setacl_maxsz	(decode_setattr_maxsz)
#घोषणा encode_fs_locations_maxsz \
				(encode_getattr_maxsz)
#घोषणा decode_fs_locations_maxsz \
				(pagepad_maxsz)
#घोषणा encode_secinfo_maxsz	(op_encode_hdr_maxsz + nfs4_name_maxsz)
#घोषणा decode_secinfo_maxsz	(op_decode_hdr_maxsz + 1 + ((NFS_MAX_SECFLAVORS * (16 + GSS_OID_MAX_LEN)) / 4))

#अगर defined(CONFIG_NFS_V4_1)
#घोषणा NFS4_MAX_MACHINE_NAME_LEN (64)
#घोषणा IMPL_NAME_LIMIT (माप(utsname()->sysname) + माप(utsname()->release) + \
			 माप(utsname()->version) + माप(utsname()->machine) + 8)

#घोषणा encode_exchange_id_maxsz (op_encode_hdr_maxsz + \
				encode_verअगरier_maxsz + \
				1 /* co_ownerid.len */ + \
				/* eia_clientowner */ \
				1 + XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
				1 /* flags */ + \
				1 /* spa_how */ + \
				/* max is SP4_MACH_CRED (क्रम now) */ + \
				1 + NFS4_OP_MAP_NUM_WORDS + \
				1 + NFS4_OP_MAP_NUM_WORDS + \
				1 /* implementation id array of size 1 */ + \
				1 /* nii_करोमुख्य */ + \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
				1 /* nii_name */ + \
				XDR_QUADLEN(IMPL_NAME_LIMIT) + \
				3 /* nii_date */)
#घोषणा decode_exchange_id_maxsz (op_decode_hdr_maxsz + \
				2 /* eir_clientid */ + \
				1 /* eir_sequenceid */ + \
				1 /* eir_flags */ + \
				1 /* spr_how */ + \
				  /* max is SP4_MACH_CRED (क्रम now) */ + \
				1 + NFS4_OP_MAP_NUM_WORDS + \
				1 + NFS4_OP_MAP_NUM_WORDS + \
				2 /* eir_server_owner.so_minor_id */ + \
				/* eir_server_owner.so_major_id<> */ \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + 1 + \
				/* eir_server_scope<> */ \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + 1 + \
				1 /* eir_server_impl_id array length */ + \
				1 /* nii_करोमुख्य */ + \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
				1 /* nii_name */ + \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + \
				3 /* nii_date */)
#घोषणा encode_channel_attrs_maxsz  (6 + 1 /* ca_rdma_ird.len (0) */)
#घोषणा decode_channel_attrs_maxsz  (6 + \
				     1 /* ca_rdma_ird.len */ + \
				     1 /* ca_rdma_ird */)
#घोषणा encode_create_session_maxsz  (op_encode_hdr_maxsz + \
				     2 /* csa_clientid */ + \
				     1 /* csa_sequence */ + \
				     1 /* csa_flags */ + \
				     encode_channel_attrs_maxsz + \
				     encode_channel_attrs_maxsz + \
				     1 /* csa_cb_program */ + \
				     1 /* csa_sec_parms.len (1) */ + \
				     1 /* cb_secflavor (AUTH_SYS) */ + \
				     1 /* stamp */ + \
				     1 /* machinename.len */ + \
				     XDR_QUADLEN(NFS4_MAX_MACHINE_NAME_LEN) + \
				     1 /* uid */ + \
				     1 /* gid */ + \
				     1 /* gids.len (0) */)
#घोषणा decode_create_session_maxsz  (op_decode_hdr_maxsz +	\
				     XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + \
				     1 /* csr_sequence */ + \
				     1 /* csr_flags */ + \
				     decode_channel_attrs_maxsz + \
				     decode_channel_attrs_maxsz)
#घोषणा encode_bind_conn_to_session_maxsz  (op_encode_hdr_maxsz + \
				     /* bctsa_sessid */ \
				     XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + \
				     1 /* bctsa_dir */ + \
				     1 /* bctsa_use_conn_in_rdma_mode */)
#घोषणा decode_bind_conn_to_session_maxsz  (op_decode_hdr_maxsz +	\
				     /* bctsr_sessid */ \
				     XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + \
				     1 /* bctsr_dir */ + \
				     1 /* bctsr_use_conn_in_rdma_mode */)
#घोषणा encode_destroy_session_maxsz    (op_encode_hdr_maxsz + 4)
#घोषणा decode_destroy_session_maxsz    (op_decode_hdr_maxsz)
#घोषणा encode_destroy_clientid_maxsz   (op_encode_hdr_maxsz + 2)
#घोषणा decode_destroy_clientid_maxsz   (op_decode_hdr_maxsz)
#घोषणा encode_sequence_maxsz	(op_encode_hdr_maxsz + \
				XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + 4)
#घोषणा decode_sequence_maxsz	(op_decode_hdr_maxsz + \
				XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + 5)
#घोषणा encode_reclaim_complete_maxsz	(op_encode_hdr_maxsz + 4)
#घोषणा decode_reclaim_complete_maxsz	(op_decode_hdr_maxsz + 4)
#घोषणा encode_getdeviceinfo_maxsz (op_encode_hdr_maxsz + \
				XDR_QUADLEN(NFS4_DEVICEID4_SIZE) + \
				1 /* layout type */ + \
				1 /* maxcount */ + \
				1 /* biपंचांगap size */ + \
				1 /* notअगरication biपंचांगap length */ + \
				1 /* notअगरication biपंचांगap, word 0 */)
#घोषणा decode_getdeviceinfo_maxsz (op_decode_hdr_maxsz + \
				1 /* layout type */ + \
				1 /* opaque devaddr4 length */ + \
				  /* devaddr4 payload is पढ़ो पूर्णांकo page */ \
				1 /* notअगरication biपंचांगap length */ + \
				1 /* notअगरication biपंचांगap, word 0 */ + \
				pagepad_maxsz /* possible XDR padding */)
#घोषणा encode_layoutget_maxsz	(op_encode_hdr_maxsz + 10 + \
				encode_stateid_maxsz)
#घोषणा decode_layoutget_maxsz	(op_decode_hdr_maxsz + 8 + \
				decode_stateid_maxsz + \
				XDR_QUADLEN(PNFS_LAYOUT_MAXSIZE) + \
				pagepad_maxsz)
#घोषणा encode_layoutcommit_maxsz (op_encode_hdr_maxsz +          \
				2 /* offset */ + \
				2 /* length */ + \
				1 /* reclaim */ + \
				encode_stateid_maxsz + \
				1 /* new offset (true) */ + \
				2 /* last byte written */ + \
				1 /* nt_समयchanged (false) */ + \
				1 /* layoutupdate4 layout type */ + \
				1 /* layoutupdate4 opaqueue len */)
				  /* the actual content of layoutupdate4 should
				     be allocated by drivers and spliced in
				     using xdr_ग_लिखो_pages */
#घोषणा decode_layoutcommit_maxsz (op_decode_hdr_maxsz + 3)
#घोषणा encode_layoutवापस_maxsz (8 + op_encode_hdr_maxsz + \
				encode_stateid_maxsz + \
				1 + \
				XDR_QUADLEN(NFS4_OPAQUE_LIMIT))
#घोषणा decode_layoutवापस_maxsz (op_decode_hdr_maxsz + \
				1 + decode_stateid_maxsz)
#घोषणा encode_secinfo_no_name_maxsz (op_encode_hdr_maxsz + 1)
#घोषणा decode_secinfo_no_name_maxsz decode_secinfo_maxsz
#घोषणा encode_test_stateid_maxsz	(op_encode_hdr_maxsz + 2 + \
					 XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा decode_test_stateid_maxsz	(op_decode_hdr_maxsz + 2 + 1)
#घोषणा encode_मुक्त_stateid_maxsz	(op_encode_hdr_maxsz + 1 + \
					 XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा decode_मुक्त_stateid_maxsz	(op_decode_hdr_maxsz)
#अन्यथा /* CONFIG_NFS_V4_1 */
#घोषणा encode_sequence_maxsz	0
#घोषणा decode_sequence_maxsz	0
#घोषणा encode_layoutवापस_maxsz 0
#घोषणा decode_layoutवापस_maxsz 0
#घोषणा encode_layoutget_maxsz	0
#घोषणा decode_layoutget_maxsz	0
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

#घोषणा NFS4_enc_compound_sz	(1024)  /* XXX: large enough? */
#घोषणा NFS4_dec_compound_sz	(1024)  /* XXX: large enough? */
#घोषणा NFS4_enc_पढ़ो_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_पढ़ो_maxsz)
#घोषणा NFS4_dec_पढ़ो_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_पढ़ो_maxsz)
#घोषणा NFS4_enc_पढ़ोlink_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_पढ़ोlink_maxsz)
#घोषणा NFS4_dec_पढ़ोlink_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_पढ़ोlink_maxsz)
#घोषणा NFS4_enc_सूची_पढ़ो_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_सूची_पढ़ो_maxsz)
#घोषणा NFS4_dec_सूची_पढ़ो_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_सूची_पढ़ो_maxsz)
#घोषणा NFS4_enc_ग_लिखो_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_ग_लिखो_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_ग_लिखो_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_ग_लिखो_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_commit_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_commit_maxsz)
#घोषणा NFS4_dec_commit_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_commit_maxsz)
#घोषणा NFS4_enc_खोलो_sz        (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_खोलो_maxsz + \
				encode_access_maxsz + \
				encode_getfh_maxsz + \
				encode_getattr_maxsz + \
				encode_layoutget_maxsz)
#घोषणा NFS4_dec_खोलो_sz        (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_खोलो_maxsz + \
				decode_access_maxsz + \
				decode_getfh_maxsz + \
				decode_getattr_maxsz + \
				decode_layoutget_maxsz)
#घोषणा NFS4_enc_खोलो_confirm_sz \
				(compound_encode_hdr_maxsz + \
				 encode_putfh_maxsz + \
				 encode_खोलो_confirm_maxsz)
#घोषणा NFS4_dec_खोलो_confirm_sz \
				(compound_decode_hdr_maxsz + \
				 decode_putfh_maxsz + \
				 decode_खोलो_confirm_maxsz)
#घोषणा NFS4_enc_खोलो_noattr_sz	(compound_encode_hdr_maxsz + \
					encode_sequence_maxsz + \
					encode_putfh_maxsz + \
					encode_खोलो_maxsz + \
					encode_access_maxsz + \
					encode_getattr_maxsz + \
					encode_layoutget_maxsz)
#घोषणा NFS4_dec_खोलो_noattr_sz	(compound_decode_hdr_maxsz + \
					decode_sequence_maxsz + \
					decode_putfh_maxsz + \
					decode_खोलो_maxsz + \
					decode_access_maxsz + \
					decode_getattr_maxsz + \
					decode_layoutget_maxsz)
#घोषणा NFS4_enc_खोलो_करोwngrade_sz \
				(compound_encode_hdr_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_layoutवापस_maxsz + \
				 encode_खोलो_करोwngrade_maxsz)
#घोषणा NFS4_dec_खोलो_करोwngrade_sz \
				(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_layoutवापस_maxsz + \
				 decode_खोलो_करोwngrade_maxsz)
#घोषणा NFS4_enc_बंद_sz	(compound_encode_hdr_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_layoutवापस_maxsz + \
				 encode_बंद_maxsz + \
				 encode_getattr_maxsz)
#घोषणा NFS4_dec_बंद_sz	(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_layoutवापस_maxsz + \
				 decode_बंद_maxsz + \
				 decode_getattr_maxsz)
#घोषणा NFS4_enc_setattr_sz	(compound_encode_hdr_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_setattr_maxsz + \
				 encode_getattr_maxsz)
#घोषणा NFS4_dec_setattr_sz	(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_setattr_maxsz + \
				 decode_getattr_maxsz)
#घोषणा NFS4_enc_fsinfo_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_fsinfo_maxsz)
#घोषणा NFS4_dec_fsinfo_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_fsinfo_maxsz)
#घोषणा NFS4_enc_renew_sz	(compound_encode_hdr_maxsz + \
				encode_renew_maxsz)
#घोषणा NFS4_dec_renew_sz	(compound_decode_hdr_maxsz + \
				decode_renew_maxsz)
#घोषणा NFS4_enc_setclientid_sz	(compound_encode_hdr_maxsz + \
				encode_setclientid_maxsz)
#घोषणा NFS4_dec_setclientid_sz	(compound_decode_hdr_maxsz + \
				decode_setclientid_maxsz)
#घोषणा NFS4_enc_setclientid_confirm_sz \
				(compound_encode_hdr_maxsz + \
				encode_setclientid_confirm_maxsz)
#घोषणा NFS4_dec_setclientid_confirm_sz \
				(compound_decode_hdr_maxsz + \
				decode_setclientid_confirm_maxsz)
#घोषणा NFS4_enc_lock_sz        (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_lock_maxsz)
#घोषणा NFS4_dec_lock_sz        (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_lock_maxsz)
#घोषणा NFS4_enc_lockt_sz       (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_lockt_maxsz)
#घोषणा NFS4_dec_lockt_sz       (compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_lockt_maxsz)
#घोषणा NFS4_enc_locku_sz       (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_locku_maxsz)
#घोषणा NFS4_dec_locku_sz       (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_locku_maxsz)
#घोषणा NFS4_enc_release_lockowner_sz \
				(compound_encode_hdr_maxsz + \
				 encode_lockowner_maxsz)
#घोषणा NFS4_dec_release_lockowner_sz \
				(compound_decode_hdr_maxsz + \
				 decode_lockowner_maxsz)
#घोषणा NFS4_enc_access_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_access_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_access_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_access_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_getattr_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattr_maxsz + \
				encode_renew_maxsz)
#घोषणा NFS4_dec_getattr_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattr_maxsz + \
				decode_renew_maxsz)
#घोषणा NFS4_enc_lookup_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_lookup_maxsz + \
				encode_getattr_maxsz + \
				encode_getfh_maxsz)
#घोषणा NFS4_dec_lookup_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_lookup_maxsz + \
				decode_getattr_maxsz + \
				decode_getfh_maxsz)
#घोषणा NFS4_enc_lookupp_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_lookupp_maxsz + \
				encode_getattr_maxsz + \
				encode_getfh_maxsz)
#घोषणा NFS4_dec_lookupp_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_lookupp_maxsz + \
				decode_getattr_maxsz + \
				decode_getfh_maxsz)
#घोषणा NFS4_enc_lookup_root_sz (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putrootfh_maxsz + \
				encode_getattr_maxsz + \
				encode_getfh_maxsz)
#घोषणा NFS4_dec_lookup_root_sz (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putrootfh_maxsz + \
				decode_getattr_maxsz + \
				decode_getfh_maxsz)
#घोषणा NFS4_enc_हटाओ_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_हटाओ_maxsz)
#घोषणा NFS4_dec_हटाओ_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_हटाओ_maxsz)
#घोषणा NFS4_enc_नाम_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_savefh_maxsz + \
				encode_putfh_maxsz + \
				encode_नाम_maxsz)
#घोषणा NFS4_dec_नाम_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_savefh_maxsz + \
				decode_putfh_maxsz + \
				decode_नाम_maxsz)
#घोषणा NFS4_enc_link_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_savefh_maxsz + \
				encode_putfh_maxsz + \
				encode_link_maxsz + \
				encode_restorefh_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_link_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_savefh_maxsz + \
				decode_putfh_maxsz + \
				decode_link_maxsz + \
				decode_restorefh_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_symlink_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_symlink_maxsz + \
				encode_getattr_maxsz + \
				encode_getfh_maxsz)
#घोषणा NFS4_dec_symlink_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_symlink_maxsz + \
				decode_getattr_maxsz + \
				decode_getfh_maxsz)
#घोषणा NFS4_enc_create_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_create_maxsz + \
				encode_getfh_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_create_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_create_maxsz + \
				decode_getfh_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_pathconf_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_pathconf_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_statfs_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_statfs_maxsz)
#घोषणा NFS4_dec_statfs_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_statfs_maxsz)
#घोषणा NFS4_enc_server_caps_sz (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_server_caps_sz (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_delegवापस_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_layoutवापस_maxsz + \
				encode_delegवापस_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_delegवापस_sz (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_layoutवापस_maxsz + \
				decode_delegवापस_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_getacl_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getacl_maxsz)
#घोषणा NFS4_dec_getacl_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getacl_maxsz)
#घोषणा NFS4_enc_setacl_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_setacl_maxsz)
#घोषणा NFS4_dec_setacl_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_setacl_maxsz)
#घोषणा NFS4_enc_fs_locations_sz \
				(compound_encode_hdr_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_lookup_maxsz + \
				 encode_fs_locations_maxsz + \
				 encode_renew_maxsz)
#घोषणा NFS4_dec_fs_locations_sz \
				(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_lookup_maxsz + \
				 decode_fs_locations_maxsz + \
				 decode_renew_maxsz)
#घोषणा NFS4_enc_secinfo_sz 	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_secinfo_maxsz)
#घोषणा NFS4_dec_secinfo_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_secinfo_maxsz)
#घोषणा NFS4_enc_fsid_present_sz \
				(compound_encode_hdr_maxsz + \
				 encode_sequence_maxsz + \
				 encode_putfh_maxsz + \
				 encode_getfh_maxsz + \
				 encode_renew_maxsz)
#घोषणा NFS4_dec_fsid_present_sz \
				(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz + \
				 decode_putfh_maxsz + \
				 decode_getfh_maxsz + \
				 decode_renew_maxsz)
#अगर defined(CONFIG_NFS_V4_1)
#घोषणा NFS4_enc_bind_conn_to_session_sz \
				(compound_encode_hdr_maxsz + \
				 encode_bind_conn_to_session_maxsz)
#घोषणा NFS4_dec_bind_conn_to_session_sz \
				(compound_decode_hdr_maxsz + \
				 decode_bind_conn_to_session_maxsz)
#घोषणा NFS4_enc_exchange_id_sz \
				(compound_encode_hdr_maxsz + \
				 encode_exchange_id_maxsz)
#घोषणा NFS4_dec_exchange_id_sz \
				(compound_decode_hdr_maxsz + \
				 decode_exchange_id_maxsz)
#घोषणा NFS4_enc_create_session_sz \
				(compound_encode_hdr_maxsz + \
				 encode_create_session_maxsz)
#घोषणा NFS4_dec_create_session_sz \
				(compound_decode_hdr_maxsz + \
				 decode_create_session_maxsz)
#घोषणा NFS4_enc_destroy_session_sz	(compound_encode_hdr_maxsz + \
					 encode_destroy_session_maxsz)
#घोषणा NFS4_dec_destroy_session_sz	(compound_decode_hdr_maxsz + \
					 decode_destroy_session_maxsz)
#घोषणा NFS4_enc_destroy_clientid_sz	(compound_encode_hdr_maxsz + \
					 encode_destroy_clientid_maxsz)
#घोषणा NFS4_dec_destroy_clientid_sz	(compound_decode_hdr_maxsz + \
					 decode_destroy_clientid_maxsz)
#घोषणा NFS4_enc_sequence_sz \
				(compound_decode_hdr_maxsz + \
				 encode_sequence_maxsz)
#घोषणा NFS4_dec_sequence_sz \
				(compound_decode_hdr_maxsz + \
				 decode_sequence_maxsz)
#पूर्ण_अगर
#घोषणा NFS4_enc_get_lease_समय_sz	(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putrootfh_maxsz + \
					 encode_fsinfo_maxsz)
#घोषणा NFS4_dec_get_lease_समय_sz	(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putrootfh_maxsz + \
					 decode_fsinfo_maxsz)
#अगर defined(CONFIG_NFS_V4_1)
#घोषणा NFS4_enc_reclaim_complete_sz	(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_reclaim_complete_maxsz)
#घोषणा NFS4_dec_reclaim_complete_sz	(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_reclaim_complete_maxsz)
#घोषणा NFS4_enc_getdeviceinfo_sz (compound_encode_hdr_maxsz +    \
				encode_sequence_maxsz +\
				encode_getdeviceinfo_maxsz)
#घोषणा NFS4_dec_getdeviceinfo_sz (compound_decode_hdr_maxsz +    \
				decode_sequence_maxsz + \
				decode_getdeviceinfo_maxsz)
#घोषणा NFS4_enc_layoutget_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz +        \
				encode_layoutget_maxsz)
#घोषणा NFS4_dec_layoutget_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz +        \
				decode_layoutget_maxsz)
#घोषणा NFS4_enc_layoutcommit_sz (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz +\
				encode_putfh_maxsz + \
				encode_layoutcommit_maxsz + \
				encode_getattr_maxsz)
#घोषणा NFS4_dec_layoutcommit_sz (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_layoutcommit_maxsz + \
				decode_getattr_maxsz)
#घोषणा NFS4_enc_layoutवापस_sz (compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_layoutवापस_maxsz)
#घोषणा NFS4_dec_layoutवापस_sz (compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_layoutवापस_maxsz)
#घोषणा NFS4_enc_secinfo_no_name_sz	(compound_encode_hdr_maxsz + \
					encode_sequence_maxsz + \
					encode_putrootfh_maxsz +\
					encode_secinfo_no_name_maxsz)
#घोषणा NFS4_dec_secinfo_no_name_sz	(compound_decode_hdr_maxsz + \
					decode_sequence_maxsz + \
					decode_putrootfh_maxsz + \
					decode_secinfo_no_name_maxsz)
#घोषणा NFS4_enc_test_stateid_sz	(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_test_stateid_maxsz)
#घोषणा NFS4_dec_test_stateid_sz	(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_test_stateid_maxsz)
#घोषणा NFS4_enc_मुक्त_stateid_sz	(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_मुक्त_stateid_maxsz)
#घोषणा NFS4_dec_मुक्त_stateid_sz	(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_मुक्त_stateid_maxsz)

स्थिर u32 nfs41_maxग_लिखो_overhead = ((RPC_MAX_HEADER_WITH_AUTH +
				      compound_encode_hdr_maxsz +
				      encode_sequence_maxsz +
				      encode_putfh_maxsz +
				      encode_getattr_maxsz) *
				     XDR_UNIT);

स्थिर u32 nfs41_maxपढ़ो_overhead = ((RPC_MAX_HEADER_WITH_AUTH +
				     compound_decode_hdr_maxsz +
				     decode_sequence_maxsz +
				     decode_putfh_maxsz) *
				    XDR_UNIT);

स्थिर u32 nfs41_maxgetdevinfo_overhead = ((RPC_MAX_REPHEADER_WITH_AUTH +
					   compound_decode_hdr_maxsz +
					   decode_sequence_maxsz) *
					  XDR_UNIT);
EXPORT_SYMBOL_GPL(nfs41_maxgetdevinfo_overhead);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल स्थिर umode_t nfs_type2fmt[] = अणु
	[NF4BAD] = 0,
	[NF4REG] = S_IFREG,
	[NF4सूची] = S_IFसूची,
	[NF4BLK] = S_IFBLK,
	[NF4CHR] = S_IFCHR,
	[NF4LNK] = S_IFLNK,
	[NF4SOCK] = S_IFSOCK,
	[NF4FIFO] = S_IFIFO,
	[NF4ATTRसूची] = 0,
	[NF4NAMEDATTR] = 0,
पूर्ण;

काष्ठा compound_hdr अणु
	पूर्णांक32_t		status;
	uपूर्णांक32_t	nops;
	__be32 *	nops_p;
	uपूर्णांक32_t	taglen;
	अक्षर *		tag;
	uपूर्णांक32_t	replen;		/* expected reply words */
	u32		minorversion;
पूर्ण;

अटल __be32 *reserve_space(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes)
अणु
	__be32 *p = xdr_reserve_space(xdr, nbytes);
	BUG_ON(!p);
	वापस p;
पूर्ण

अटल व्योम encode_opaque_fixed(काष्ठा xdr_stream *xdr, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	WARN_ON_ONCE(xdr_stream_encode_opaque_fixed(xdr, buf, len) < 0);
पूर्ण

अटल व्योम encode_string(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len, स्थिर अक्षर *str)
अणु
	WARN_ON_ONCE(xdr_stream_encode_opaque(xdr, str, len) < 0);
पूर्ण

अटल व्योम encode_uपूर्णांक32(काष्ठा xdr_stream *xdr, u32 n)
अणु
	WARN_ON_ONCE(xdr_stream_encode_u32(xdr, n) < 0);
पूर्ण

अटल व्योम encode_uपूर्णांक64(काष्ठा xdr_stream *xdr, u64 n)
अणु
	WARN_ON_ONCE(xdr_stream_encode_u64(xdr, n) < 0);
पूर्ण

अटल sमाप_प्रकार xdr_encode_biपंचांगap4(काष्ठा xdr_stream *xdr,
		स्थिर __u32 *biपंचांगap, माप_प्रकार len)
अणु
	sमाप_प्रकार ret;

	/* Trim empty words */
	जबतक (len > 0 && biपंचांगap[len-1] == 0)
		len--;
	ret = xdr_stream_encode_uपूर्णांक32_array(xdr, biपंचांगap, len);
	अगर (WARN_ON_ONCE(ret < 0))
		वापस ret;
	वापस len;
पूर्ण

अटल माप_प्रकार mask_biपंचांगap4(स्थिर __u32 *biपंचांगap, स्थिर __u32 *mask,
		__u32 *res, माप_प्रकार len)
अणु
	माप_प्रकार i;
	__u32 पंचांगp;

	जबतक (len > 0 && (biपंचांगap[len-1] == 0 || mask[len-1] == 0))
		len--;
	क्रम (i = len; i-- > 0;) अणु
		पंचांगp = biपंचांगap[i] & mask[i];
		res[i] = पंचांगp;
	पूर्ण
	वापस len;
पूर्ण

अटल व्योम encode_nfs4_seqid(काष्ठा xdr_stream *xdr,
		स्थिर काष्ठा nfs_seqid *seqid)
अणु
	अगर (seqid != शून्य)
		encode_uपूर्णांक32(xdr, seqid->sequence->counter);
	अन्यथा
		encode_uपूर्णांक32(xdr, 0);
पूर्ण

अटल व्योम encode_compound_hdr(काष्ठा xdr_stream *xdr,
				काष्ठा rpc_rqst *req,
				काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	/* initialize running count of expected bytes in reply.
	 * NOTE: the replied tag SHOULD be the same is the one sent,
	 * but this is not required as a MUST क्रम the server to करो so. */
	hdr->replen = 3 + hdr->taglen;

	WARN_ON_ONCE(hdr->taglen > NFS4_MAXTAGLEN);
	encode_string(xdr, hdr->taglen, hdr->tag);
	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(hdr->minorversion);
	hdr->nops_p = p;
	*p = cpu_to_be32(hdr->nops);
पूर्ण

अटल व्योम encode_op_hdr(काष्ठा xdr_stream *xdr, क्रमागत nfs_opnum4 op,
		uपूर्णांक32_t replen,
		काष्ठा compound_hdr *hdr)
अणु
	encode_uपूर्णांक32(xdr, op);
	hdr->nops++;
	hdr->replen += replen;
पूर्ण

अटल व्योम encode_nops(काष्ठा compound_hdr *hdr)
अणु
	WARN_ON_ONCE(hdr->nops > NFS4_MAX_OPS);
	*hdr->nops_p = htonl(hdr->nops);
पूर्ण

अटल व्योम encode_nfs4_stateid(काष्ठा xdr_stream *xdr, स्थिर nfs4_stateid *stateid)
अणु
	encode_opaque_fixed(xdr, stateid, NFS4_STATEID_SIZE);
पूर्ण

अटल व्योम encode_nfs4_verअगरier(काष्ठा xdr_stream *xdr, स्थिर nfs4_verअगरier *verf)
अणु
	encode_opaque_fixed(xdr, verf->data, NFS4_VERIFIER_SIZE);
पूर्ण

अटल __be32 *
xdr_encode_nfsसमय4(__be32 *p, स्थिर काष्ठा बारpec64 *t)
अणु
	p = xdr_encode_hyper(p, t->tv_sec);
	*p++ = cpu_to_be32(t->tv_nsec);
	वापस p;
पूर्ण

अटल व्योम encode_attrs(काष्ठा xdr_stream *xdr, स्थिर काष्ठा iattr *iap,
				स्थिर काष्ठा nfs4_label *label,
				स्थिर umode_t *umask,
				स्थिर काष्ठा nfs_server *server,
				स्थिर uपूर्णांक32_t attrmask[])
अणु
	अक्षर owner_name[IDMAP_NAMESZ];
	अक्षर owner_group[IDMAP_NAMESZ];
	पूर्णांक owner_namelen = 0;
	पूर्णांक owner_grouplen = 0;
	__be32 *p;
	uपूर्णांक32_t len = 0;
	uपूर्णांक32_t bmval[3] = अणु 0 पूर्ण;

	/*
	 * We reserve enough space to ग_लिखो the entire attribute buffer at once.
	 */
	अगर ((iap->ia_valid & ATTR_SIZE) && (attrmask[0] & FATTR4_WORD0_SIZE)) अणु
		bmval[0] |= FATTR4_WORD0_SIZE;
		len += 8;
	पूर्ण
	अगर (iap->ia_valid & ATTR_MODE) अणु
		अगर (umask && (attrmask[2] & FATTR4_WORD2_MODE_UMASK)) अणु
			bmval[2] |= FATTR4_WORD2_MODE_UMASK;
			len += 8;
		पूर्ण अन्यथा अगर (attrmask[1] & FATTR4_WORD1_MODE) अणु
			bmval[1] |= FATTR4_WORD1_MODE;
			len += 4;
		पूर्ण
	पूर्ण
	अगर ((iap->ia_valid & ATTR_UID) && (attrmask[1] & FATTR4_WORD1_OWNER)) अणु
		owner_namelen = nfs_map_uid_to_name(server, iap->ia_uid, owner_name, IDMAP_NAMESZ);
		अगर (owner_namelen < 0) अणु
			dprपूर्णांकk("nfs: couldn't resolve uid %d to string\n",
					from_kuid(&init_user_ns, iap->ia_uid));
			/* XXX */
			म_नकल(owner_name, "nobody");
			owner_namelen = माप("nobody") - 1;
			/* जाओ out; */
		पूर्ण
		bmval[1] |= FATTR4_WORD1_OWNER;
		len += 4 + (XDR_QUADLEN(owner_namelen) << 2);
	पूर्ण
	अगर ((iap->ia_valid & ATTR_GID) &&
	   (attrmask[1] & FATTR4_WORD1_OWNER_GROUP)) अणु
		owner_grouplen = nfs_map_gid_to_group(server, iap->ia_gid, owner_group, IDMAP_NAMESZ);
		अगर (owner_grouplen < 0) अणु
			dprपूर्णांकk("nfs: couldn't resolve gid %d to string\n",
					from_kgid(&init_user_ns, iap->ia_gid));
			म_नकल(owner_group, "nobody");
			owner_grouplen = माप("nobody") - 1;
			/* जाओ out; */
		पूर्ण
		bmval[1] |= FATTR4_WORD1_OWNER_GROUP;
		len += 4 + (XDR_QUADLEN(owner_grouplen) << 2);
	पूर्ण
	अगर (attrmask[1] & FATTR4_WORD1_TIME_ACCESS_SET) अणु
		अगर (iap->ia_valid & ATTR_ATIME_SET) अणु
			bmval[1] |= FATTR4_WORD1_TIME_ACCESS_SET;
			len += 4 + (nfsसमय4_maxsz << 2);
		पूर्ण अन्यथा अगर (iap->ia_valid & ATTR_ATIME) अणु
			bmval[1] |= FATTR4_WORD1_TIME_ACCESS_SET;
			len += 4;
		पूर्ण
	पूर्ण
	अगर (attrmask[1] & FATTR4_WORD1_TIME_MODIFY_SET) अणु
		अगर (iap->ia_valid & ATTR_MTIME_SET) अणु
			bmval[1] |= FATTR4_WORD1_TIME_MODIFY_SET;
			len += 4 + (nfsसमय4_maxsz << 2);
		पूर्ण अन्यथा अगर (iap->ia_valid & ATTR_MTIME) अणु
			bmval[1] |= FATTR4_WORD1_TIME_MODIFY_SET;
			len += 4;
		पूर्ण
	पूर्ण

	अगर (label && (attrmask[2] & FATTR4_WORD2_SECURITY_LABEL)) अणु
		len += 4 + 4 + 4 + (XDR_QUADLEN(label->len) << 2);
		bmval[2] |= FATTR4_WORD2_SECURITY_LABEL;
	पूर्ण

	xdr_encode_biपंचांगap4(xdr, bmval, ARRAY_SIZE(bmval));
	xdr_stream_encode_opaque_अंतरभूत(xdr, (व्योम **)&p, len);

	अगर (bmval[0] & FATTR4_WORD0_SIZE)
		p = xdr_encode_hyper(p, iap->ia_size);
	अगर (bmval[1] & FATTR4_WORD1_MODE)
		*p++ = cpu_to_be32(iap->ia_mode & S_IALLUGO);
	अगर (bmval[1] & FATTR4_WORD1_OWNER)
		p = xdr_encode_opaque(p, owner_name, owner_namelen);
	अगर (bmval[1] & FATTR4_WORD1_OWNER_GROUP)
		p = xdr_encode_opaque(p, owner_group, owner_grouplen);
	अगर (bmval[1] & FATTR4_WORD1_TIME_ACCESS_SET) अणु
		अगर (iap->ia_valid & ATTR_ATIME_SET) अणु
			*p++ = cpu_to_be32(NFS4_SET_TO_CLIENT_TIME);
			p = xdr_encode_nfsसमय4(p, &iap->ia_aसमय);
		पूर्ण अन्यथा
			*p++ = cpu_to_be32(NFS4_SET_TO_SERVER_TIME);
	पूर्ण
	अगर (bmval[1] & FATTR4_WORD1_TIME_MODIFY_SET) अणु
		अगर (iap->ia_valid & ATTR_MTIME_SET) अणु
			*p++ = cpu_to_be32(NFS4_SET_TO_CLIENT_TIME);
			p = xdr_encode_nfsसमय4(p, &iap->ia_mसमय);
		पूर्ण अन्यथा
			*p++ = cpu_to_be32(NFS4_SET_TO_SERVER_TIME);
	पूर्ण
	अगर (label && (bmval[2] & FATTR4_WORD2_SECURITY_LABEL)) अणु
		*p++ = cpu_to_be32(label->lfs);
		*p++ = cpu_to_be32(label->pi);
		*p++ = cpu_to_be32(label->len);
		p = xdr_encode_opaque_fixed(p, label->label, label->len);
	पूर्ण
	अगर (bmval[2] & FATTR4_WORD2_MODE_UMASK) अणु
		*p++ = cpu_to_be32(iap->ia_mode & S_IALLUGO);
		*p++ = cpu_to_be32(*umask);
	पूर्ण

/* out: */
पूर्ण

अटल व्योम encode_access(काष्ठा xdr_stream *xdr, u32 access, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_ACCESS, decode_access_maxsz, hdr);
	encode_uपूर्णांक32(xdr, access);
पूर्ण

अटल व्योम encode_बंद(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_बंदargs *arg, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_CLOSE, decode_बंद_maxsz, hdr);
	encode_nfs4_seqid(xdr, arg->seqid);
	encode_nfs4_stateid(xdr, &arg->stateid);
पूर्ण

अटल व्योम encode_commit(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_commitargs *args, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_COMMIT, decode_commit_maxsz, hdr);
	p = reserve_space(xdr, 12);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम encode_create(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_create_arg *create, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_CREATE, decode_create_maxsz, hdr);
	encode_uपूर्णांक32(xdr, create->ftype);

	चयन (create->ftype) अणु
	हाल NF4LNK:
		p = reserve_space(xdr, 4);
		*p = cpu_to_be32(create->u.symlink.len);
		xdr_ग_लिखो_pages(xdr, create->u.symlink.pages, 0,
				create->u.symlink.len);
		xdr->buf->flags |= XDRBUF_WRITE;
		अवरोध;

	हाल NF4BLK: हाल NF4CHR:
		p = reserve_space(xdr, 8);
		*p++ = cpu_to_be32(create->u.device.specdata1);
		*p = cpu_to_be32(create->u.device.specdata2);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	encode_string(xdr, create->name->len, create->name->name);
	encode_attrs(xdr, create->attrs, create->label, &create->umask,
			create->server, create->server->attr_biपंचांगask);
पूर्ण

अटल व्योम encode_getattr(काष्ठा xdr_stream *xdr,
		स्थिर __u32 *biपंचांगap, स्थिर __u32 *mask, माप_प्रकार len,
		काष्ठा compound_hdr *hdr)
अणु
	__u32 masked_biपंचांगap[nfs4_fattr_biपंचांगap_maxsz];

	encode_op_hdr(xdr, OP_GETATTR, decode_getattr_maxsz, hdr);
	अगर (mask) अणु
		अगर (WARN_ON_ONCE(len > ARRAY_SIZE(masked_biपंचांगap)))
			len = ARRAY_SIZE(masked_biपंचांगap);
		len = mask_biपंचांगap4(biपंचांगap, mask, masked_biपंचांगap, len);
		biपंचांगap = masked_biपंचांगap;
	पूर्ण
	xdr_encode_biपंचांगap4(xdr, biपंचांगap, len);
पूर्ण

अटल व्योम encode_getfattr(काष्ठा xdr_stream *xdr, स्थिर u32* biपंचांगask, काष्ठा compound_hdr *hdr)
अणु
	encode_getattr(xdr, nfs4_fattr_biपंचांगap, biपंचांगask,
			ARRAY_SIZE(nfs4_fattr_biपंचांगap), hdr);
पूर्ण

अटल व्योम encode_getfattr_खोलो(काष्ठा xdr_stream *xdr, स्थिर u32 *biपंचांगask,
				 स्थिर u32 *खोलो_biपंचांगap,
				 काष्ठा compound_hdr *hdr)
अणु
	encode_getattr(xdr, खोलो_biपंचांगap, biपंचांगask, 3, hdr);
पूर्ण

अटल व्योम encode_fsinfo(काष्ठा xdr_stream *xdr, स्थिर u32* biपंचांगask, काष्ठा compound_hdr *hdr)
अणु
	encode_getattr(xdr, nfs4_fsinfo_biपंचांगap, biपंचांगask,
			ARRAY_SIZE(nfs4_fsinfo_biपंचांगap), hdr);
पूर्ण

अटल व्योम encode_fs_locations(काष्ठा xdr_stream *xdr, स्थिर u32* biपंचांगask, काष्ठा compound_hdr *hdr)
अणु
	encode_getattr(xdr, nfs4_fs_locations_biपंचांगap, biपंचांगask,
			ARRAY_SIZE(nfs4_fs_locations_biपंचांगap), hdr);
पूर्ण

अटल व्योम encode_getfh(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_GETFH, decode_getfh_maxsz, hdr);
पूर्ण

अटल व्योम encode_link(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_LINK, decode_link_maxsz, hdr);
	encode_string(xdr, name->len, name->name);
पूर्ण

अटल अंतरभूत पूर्णांक nfs4_lock_type(काष्ठा file_lock *fl, पूर्णांक block)
अणु
	अगर (fl->fl_type == F_RDLCK)
		वापस block ? NFS4_READW_LT : NFS4_READ_LT;
	वापस block ? NFS4_WRITEW_LT : NFS4_WRITE_LT;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t nfs4_lock_length(काष्ठा file_lock *fl)
अणु
	अगर (fl->fl_end == OFFSET_MAX)
		वापस ~(uपूर्णांक64_t)0;
	वापस fl->fl_end - fl->fl_start + 1;
पूर्ण

अटल व्योम encode_lockowner(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_lowner *lowner)
अणु
	__be32 *p;

	p = reserve_space(xdr, 32);
	p = xdr_encode_hyper(p, lowner->clientid);
	*p++ = cpu_to_be32(20);
	p = xdr_encode_opaque_fixed(p, "lock id:", 8);
	*p++ = cpu_to_be32(lowner->s_dev);
	xdr_encode_hyper(p, lowner->id);
पूर्ण

/*
 * opcode,type,reclaim,offset,length,new_lock_owner = 32
 * खोलो_seqid,खोलो_stateid,lock_seqid,lock_owner.clientid, lock_owner.id = 40
 */
अटल व्योम encode_lock(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_lock_args *args, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LOCK, decode_lock_maxsz, hdr);
	p = reserve_space(xdr, 28);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, args->block));
	*p++ = cpu_to_be32(args->reclaim);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	*p = cpu_to_be32(args->new_lock_owner);
	अगर (args->new_lock_owner)अणु
		encode_nfs4_seqid(xdr, args->खोलो_seqid);
		encode_nfs4_stateid(xdr, &args->खोलो_stateid);
		encode_nfs4_seqid(xdr, args->lock_seqid);
		encode_lockowner(xdr, &args->lock_owner);
	पूर्ण
	अन्यथा अणु
		encode_nfs4_stateid(xdr, &args->lock_stateid);
		encode_nfs4_seqid(xdr, args->lock_seqid);
	पूर्ण
पूर्ण

अटल व्योम encode_lockt(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_lockt_args *args, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LOCKT, decode_lockt_maxsz, hdr);
	p = reserve_space(xdr, 20);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, 0));
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	encode_lockowner(xdr, &args->lock_owner);
पूर्ण

अटल व्योम encode_locku(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_locku_args *args, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LOCKU, decode_locku_maxsz, hdr);
	encode_uपूर्णांक32(xdr, nfs4_lock_type(args->fl, 0));
	encode_nfs4_seqid(xdr, args->seqid);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 16);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	xdr_encode_hyper(p, nfs4_lock_length(args->fl));
पूर्ण

अटल व्योम encode_release_lockowner(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_lowner *lowner, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_RELEASE_LOCKOWNER, decode_release_lockowner_maxsz, hdr);
	encode_lockowner(xdr, lowner);
पूर्ण

अटल व्योम encode_lookup(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_LOOKUP, decode_lookup_maxsz, hdr);
	encode_string(xdr, name->len, name->name);
पूर्ण

अटल व्योम encode_lookupp(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_LOOKUPP, decode_lookupp_maxsz, hdr);
पूर्ण

अटल व्योम encode_share_access(काष्ठा xdr_stream *xdr, u32 share_access)
अणु
	__be32 *p;

	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(share_access);
	*p = cpu_to_be32(0);		/* क्रम linux, share_deny = 0 always */
पूर्ण

अटल अंतरभूत व्योम encode_खोलोhdr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_खोलोargs *arg)
अणु
	__be32 *p;
 /*
 * opcode 4, seqid 4, share_access 4, share_deny 4, clientid 8, ownerlen 4,
 * owner 4 = 32
 */
	encode_nfs4_seqid(xdr, arg->seqid);
	encode_share_access(xdr, arg->share_access);
	p = reserve_space(xdr, 36);
	p = xdr_encode_hyper(p, arg->clientid);
	*p++ = cpu_to_be32(24);
	p = xdr_encode_opaque_fixed(p, "open id:", 8);
	*p++ = cpu_to_be32(arg->server->s_dev);
	*p++ = cpu_to_be32(arg->id.uniquअगरier);
	xdr_encode_hyper(p, arg->id.create_समय);
पूर्ण

अटल अंतरभूत व्योम encode_createmode(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_खोलोargs *arg)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	चयन(arg->createmode) अणु
	हाल NFS4_CREATE_UNCHECKED:
		*p = cpu_to_be32(NFS4_CREATE_UNCHECKED);
		encode_attrs(xdr, arg->u.attrs, arg->label, &arg->umask,
				arg->server, arg->server->attr_biपंचांगask);
		अवरोध;
	हाल NFS4_CREATE_GUARDED:
		*p = cpu_to_be32(NFS4_CREATE_GUARDED);
		encode_attrs(xdr, arg->u.attrs, arg->label, &arg->umask,
				arg->server, arg->server->attr_biपंचांगask);
		अवरोध;
	हाल NFS4_CREATE_EXCLUSIVE:
		*p = cpu_to_be32(NFS4_CREATE_EXCLUSIVE);
		encode_nfs4_verअगरier(xdr, &arg->u.verअगरier);
		अवरोध;
	हाल NFS4_CREATE_EXCLUSIVE4_1:
		*p = cpu_to_be32(NFS4_CREATE_EXCLUSIVE4_1);
		encode_nfs4_verअगरier(xdr, &arg->u.verअगरier);
		encode_attrs(xdr, arg->u.attrs, arg->label, &arg->umask,
				arg->server, arg->server->exclcreat_biपंचांगask);
	पूर्ण
पूर्ण

अटल व्योम encode_खोलोtype(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_खोलोargs *arg)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	चयन (arg->खोलो_flags & O_CREAT) अणु
	हाल 0:
		*p = cpu_to_be32(NFS4_OPEN_NOCREATE);
		अवरोध;
	शेष:
		*p = cpu_to_be32(NFS4_OPEN_CREATE);
		encode_createmode(xdr, arg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम encode_delegation_type(काष्ठा xdr_stream *xdr, भ_शेषe_t delegation_type)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	चयन (delegation_type) अणु
	हाल 0:
		*p = cpu_to_be32(NFS4_OPEN_DELEGATE_NONE);
		अवरोध;
	हाल FMODE_READ:
		*p = cpu_to_be32(NFS4_OPEN_DELEGATE_READ);
		अवरोध;
	हाल FMODE_WRITE|FMODE_READ:
		*p = cpu_to_be32(NFS4_OPEN_DELEGATE_WRITE);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम encode_claim_null(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_शून्य);
	encode_string(xdr, name->len, name->name);
पूर्ण

अटल अंतरभूत व्योम encode_claim_previous(काष्ठा xdr_stream *xdr, भ_शेषe_t type)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_PREVIOUS);
	encode_delegation_type(xdr, type);
पूर्ण

अटल अंतरभूत व्योम encode_claim_delegate_cur(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name, स्थिर nfs4_stateid *stateid)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_DELEGATE_CUR);
	encode_nfs4_stateid(xdr, stateid);
	encode_string(xdr, name->len, name->name);
पूर्ण

अटल अंतरभूत व्योम encode_claim_fh(काष्ठा xdr_stream *xdr)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_FH);
पूर्ण

अटल अंतरभूत व्योम encode_claim_delegate_cur_fh(काष्ठा xdr_stream *xdr, स्थिर nfs4_stateid *stateid)
अणु
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_DELEG_CUR_FH);
	encode_nfs4_stateid(xdr, stateid);
पूर्ण

अटल व्योम encode_खोलो(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_खोलोargs *arg, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_OPEN, decode_खोलो_maxsz, hdr);
	encode_खोलोhdr(xdr, arg);
	encode_खोलोtype(xdr, arg);
	चयन (arg->claim) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
		encode_claim_null(xdr, arg->name);
		अवरोध;
	हाल NFS4_OPEN_CLAIM_PREVIOUS:
		encode_claim_previous(xdr, arg->u.delegation_type);
		अवरोध;
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
		encode_claim_delegate_cur(xdr, arg->name, &arg->u.delegation);
		अवरोध;
	हाल NFS4_OPEN_CLAIM_FH:
		encode_claim_fh(xdr);
		अवरोध;
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		encode_claim_delegate_cur_fh(xdr, &arg->u.delegation);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम encode_खोलो_confirm(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_खोलो_confirmargs *arg, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_OPEN_CONFIRM, decode_खोलो_confirm_maxsz, hdr);
	encode_nfs4_stateid(xdr, arg->stateid);
	encode_nfs4_seqid(xdr, arg->seqid);
पूर्ण

अटल व्योम encode_खोलो_करोwngrade(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_बंदargs *arg, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_OPEN_DOWNGRADE, decode_खोलो_करोwngrade_maxsz, hdr);
	encode_nfs4_stateid(xdr, &arg->stateid);
	encode_nfs4_seqid(xdr, arg->seqid);
	encode_share_access(xdr, arg->share_access);
पूर्ण

अटल व्योम
encode_putfh(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_PUTFH, decode_putfh_maxsz, hdr);
	encode_string(xdr, fh->size, fh->data);
पूर्ण

अटल व्योम encode_putrootfh(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_PUTROOTFH, decode_putrootfh_maxsz, hdr);
पूर्ण

अटल व्योम encode_पढ़ो(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_pgio_args *args,
			काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_READ, decode_पढ़ो_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->stateid);

	p = reserve_space(xdr, 12);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
पूर्ण

अटल व्योम encode_सूची_पढ़ो(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_सूची_पढ़ो_arg *सूची_पढ़ो, काष्ठा rpc_rqst *req, काष्ठा compound_hdr *hdr)
अणु
	uपूर्णांक32_t attrs[3] = अणु
		FATTR4_WORD0_RDATTR_ERROR,
		FATTR4_WORD1_MOUNTED_ON_खाताID,
	पूर्ण;
	uपूर्णांक32_t dircount = सूची_पढ़ो->count >> 1;
	__be32 *p, verf[2];
	uपूर्णांक32_t attrlen = 0;
	अचिन्हित पूर्णांक i;

	अगर (सूची_पढ़ो->plus) अणु
		attrs[0] |= FATTR4_WORD0_TYPE|FATTR4_WORD0_CHANGE|FATTR4_WORD0_SIZE|
			FATTR4_WORD0_FSID|FATTR4_WORD0_खाताHANDLE|FATTR4_WORD0_खाताID;
		attrs[1] |= FATTR4_WORD1_MODE|FATTR4_WORD1_NUMLINKS|FATTR4_WORD1_OWNER|
			FATTR4_WORD1_OWNER_GROUP|FATTR4_WORD1_RAWDEV|
			FATTR4_WORD1_SPACE_USED|FATTR4_WORD1_TIME_ACCESS|
			FATTR4_WORD1_TIME_METADATA|FATTR4_WORD1_TIME_MODIFY;
		attrs[2] |= FATTR4_WORD2_SECURITY_LABEL;
		dircount >>= 1;
	पूर्ण
	/* Use mounted_on_fileid only अगर the server supports it */
	अगर (!(सूची_पढ़ो->biपंचांगask[1] & FATTR4_WORD1_MOUNTED_ON_खाताID))
		attrs[0] |= FATTR4_WORD0_खाताID;
	क्रम (i = 0; i < ARRAY_SIZE(attrs); i++) अणु
		attrs[i] &= सूची_पढ़ो->biपंचांगask[i];
		अगर (attrs[i] != 0)
			attrlen = i+1;
	पूर्ण

	encode_op_hdr(xdr, OP_READसूची, decode_सूची_पढ़ो_maxsz, hdr);
	encode_uपूर्णांक64(xdr, सूची_पढ़ो->cookie);
	encode_nfs4_verअगरier(xdr, &सूची_पढ़ो->verअगरier);
	p = reserve_space(xdr, 12 + (attrlen << 2));
	*p++ = cpu_to_be32(dircount);
	*p++ = cpu_to_be32(सूची_पढ़ो->count);
	*p++ = cpu_to_be32(attrlen);
	क्रम (i = 0; i < attrlen; i++)
		*p++ = cpu_to_be32(attrs[i]);
	स_नकल(verf, सूची_पढ़ो->verअगरier.data, माप(verf));

	dprपूर्णांकk("%s: cookie = %llu, verifier = %08x:%08x, bitmap = %08x:%08x:%08x\n",
			__func__,
			(अचिन्हित दीर्घ दीर्घ)सूची_पढ़ो->cookie,
			verf[0], verf[1],
			attrs[0] & सूची_पढ़ो->biपंचांगask[0],
			attrs[1] & सूची_पढ़ो->biपंचांगask[1],
			attrs[2] & सूची_पढ़ो->biपंचांगask[2]);
पूर्ण

अटल व्योम encode_पढ़ोlink(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_पढ़ोlink *पढ़ोlink, काष्ठा rpc_rqst *req, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_READLINK, decode_पढ़ोlink_maxsz, hdr);
पूर्ण

अटल व्योम encode_हटाओ(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_REMOVE, decode_हटाओ_maxsz, hdr);
	encode_string(xdr, name->len, name->name);
पूर्ण

अटल व्योम encode_नाम(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *oldname, स्थिर काष्ठा qstr *newname, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_RENAME, decode_नाम_maxsz, hdr);
	encode_string(xdr, oldname->len, oldname->name);
	encode_string(xdr, newname->len, newname->name);
पूर्ण

अटल व्योम encode_renew(काष्ठा xdr_stream *xdr, clientid4 clid,
			 काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_RENEW, decode_renew_maxsz, hdr);
	encode_uपूर्णांक64(xdr, clid);
पूर्ण

अटल व्योम
encode_restorefh(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_RESTOREFH, decode_restorefh_maxsz, hdr);
पूर्ण

अटल व्योम
encode_setacl(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_setaclargs *arg,
		काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_SETATTR, decode_setacl_maxsz, hdr);
	encode_nfs4_stateid(xdr, &zero_stateid);
	p = reserve_space(xdr, 2*4);
	*p++ = cpu_to_be32(1);
	*p = cpu_to_be32(FATTR4_WORD0_ACL);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(arg->acl_len);
	xdr_ग_लिखो_pages(xdr, arg->acl_pages, 0, arg->acl_len);
पूर्ण

अटल व्योम
encode_savefh(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SAVEFH, decode_savefh_maxsz, hdr);
पूर्ण

अटल व्योम encode_setattr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_setattrargs *arg, स्थिर काष्ठा nfs_server *server, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SETATTR, decode_setattr_maxsz, hdr);
	encode_nfs4_stateid(xdr, &arg->stateid);
	encode_attrs(xdr, arg->iap, arg->label, शून्य, server,
			server->attr_biपंचांगask);
पूर्ण

अटल व्योम encode_setclientid(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_setclientid *setclientid, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_SETCLIENTID, decode_setclientid_maxsz, hdr);
	encode_nfs4_verअगरier(xdr, setclientid->sc_verअगरier);

	encode_string(xdr, म_माप(setclientid->sc_clnt->cl_owner_id),
			setclientid->sc_clnt->cl_owner_id);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(setclientid->sc_prog);
	encode_string(xdr, setclientid->sc_netid_len, setclientid->sc_netid);
	encode_string(xdr, setclientid->sc_uaddr_len, setclientid->sc_uaddr);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(setclientid->sc_clnt->cl_cb_ident);
पूर्ण

अटल व्योम encode_setclientid_confirm(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_setclientid_res *arg, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SETCLIENTID_CONFIRM,
			decode_setclientid_confirm_maxsz, hdr);
	encode_uपूर्णांक64(xdr, arg->clientid);
	encode_nfs4_verअगरier(xdr, &arg->confirm);
पूर्ण

अटल व्योम encode_ग_लिखो(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_pgio_args *args,
			 काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_WRITE, decode_ग_लिखो_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->stateid);

	p = reserve_space(xdr, 16);
	p = xdr_encode_hyper(p, args->offset);
	*p++ = cpu_to_be32(args->stable);
	*p = cpu_to_be32(args->count);

	xdr_ग_लिखो_pages(xdr, args->pages, args->pgbase, args->count);
पूर्ण

अटल व्योम encode_delegवापस(काष्ठा xdr_stream *xdr, स्थिर nfs4_stateid *stateid, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_DELEGRETURN, decode_delegवापस_maxsz, hdr);
	encode_nfs4_stateid(xdr, stateid);
पूर्ण

अटल व्योम encode_secinfo(काष्ठा xdr_stream *xdr, स्थिर काष्ठा qstr *name, काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SECINFO, decode_secinfo_maxsz, hdr);
	encode_string(xdr, name->len, name->name);
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
/* NFSv4.1 operations */
अटल व्योम encode_bind_conn_to_session(काष्ठा xdr_stream *xdr,
				   स्थिर काष्ठा nfs41_bind_conn_to_session_args *args,
				   काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_BIND_CONN_TO_SESSION,
		decode_bind_conn_to_session_maxsz, hdr);
	encode_opaque_fixed(xdr, args->sessionid.data, NFS4_MAX_SESSIONID_LEN);
	p = xdr_reserve_space(xdr, 8);
	*p++ = cpu_to_be32(args->dir);
	*p = (args->use_conn_in_rdma_mode) ? cpu_to_be32(1) : cpu_to_be32(0);
पूर्ण

अटल व्योम encode_op_map(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs4_op_map *op_map)
अणु
	अचिन्हित पूर्णांक i;
	encode_uपूर्णांक32(xdr, NFS4_OP_MAP_NUM_WORDS);
	क्रम (i = 0; i < NFS4_OP_MAP_NUM_WORDS; i++)
		encode_uपूर्णांक32(xdr, op_map->u.words[i]);
पूर्ण

अटल व्योम encode_exchange_id(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs41_exchange_id_args *args,
			       काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;
	अक्षर impl_name[IMPL_NAME_LIMIT];
	पूर्णांक len = 0;

	encode_op_hdr(xdr, OP_EXCHANGE_ID, decode_exchange_id_maxsz, hdr);
	encode_nfs4_verअगरier(xdr, &args->verअगरier);

	encode_string(xdr, म_माप(args->client->cl_owner_id),
			args->client->cl_owner_id);

	encode_uपूर्णांक32(xdr, args->flags);
	encode_uपूर्णांक32(xdr, args->state_protect.how);

	चयन (args->state_protect.how) अणु
	हाल SP4_NONE:
		अवरोध;
	हाल SP4_MACH_CRED:
		encode_op_map(xdr, &args->state_protect.enक्रमce);
		encode_op_map(xdr, &args->state_protect.allow);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	अगर (send_implementation_id &&
	    माप(CONFIG_NFS_V4_1_IMPLEMENTATION_ID_DOMAIN) > 1 &&
	    माप(CONFIG_NFS_V4_1_IMPLEMENTATION_ID_DOMAIN)
		<= माप(impl_name) + 1)
		len = snम_लिखो(impl_name, माप(impl_name), "%s %s %s %s",
			       utsname()->sysname, utsname()->release,
			       utsname()->version, utsname()->machine);

	अगर (len > 0) अणु
		encode_uपूर्णांक32(xdr, 1);	/* implementation id array length=1 */

		encode_string(xdr,
			माप(CONFIG_NFS_V4_1_IMPLEMENTATION_ID_DOMAIN) - 1,
			CONFIG_NFS_V4_1_IMPLEMENTATION_ID_DOMAIN);
		encode_string(xdr, len, impl_name);
		/* just send zeros क्रम nii_date - the date is in nii_name */
		p = reserve_space(xdr, 12);
		p = xdr_encode_hyper(p, 0);
		*p = cpu_to_be32(0);
	पूर्ण अन्यथा
		encode_uपूर्णांक32(xdr, 0);	/* implementation id array length=0 */
पूर्ण

अटल व्योम encode_create_session(काष्ठा xdr_stream *xdr,
				  स्थिर काष्ठा nfs41_create_session_args *args,
				  काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;
	काष्ठा nfs_client *clp = args->client;
	काष्ठा rpc_clnt *clnt = clp->cl_rpcclient;
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
	u32 max_resp_sz_cached;

	/*
	 * Assumes OPEN is the biggest non-idempotent compound.
	 * 2 is the verअगरier.
	 */
	max_resp_sz_cached = (NFS4_dec_खोलो_sz + RPC_REPHDRSIZE + 2)
				* XDR_UNIT + RPC_MAX_AUTH_SIZE;

	encode_op_hdr(xdr, OP_CREATE_SESSION, decode_create_session_maxsz, hdr);
	p = reserve_space(xdr, 16 + 2*28 + 20 + clnt->cl_nodelen + 12);
	p = xdr_encode_hyper(p, args->clientid);
	*p++ = cpu_to_be32(args->seqid);			/*Sequence id */
	*p++ = cpu_to_be32(args->flags);			/*flags */

	/* Fore Channel */
	*p++ = cpu_to_be32(0);				/* header padding size */
	*p++ = cpu_to_be32(args->fc_attrs.max_rqst_sz);	/* max req size */
	*p++ = cpu_to_be32(args->fc_attrs.max_resp_sz);	/* max resp size */
	*p++ = cpu_to_be32(max_resp_sz_cached);		/* Max resp sz cached */
	*p++ = cpu_to_be32(args->fc_attrs.max_ops);	/* max operations */
	*p++ = cpu_to_be32(args->fc_attrs.max_reqs);	/* max requests */
	*p++ = cpu_to_be32(0);				/* rdmachannel_attrs */

	/* Back Channel */
	*p++ = cpu_to_be32(0);				/* header padding size */
	*p++ = cpu_to_be32(args->bc_attrs.max_rqst_sz);	/* max req size */
	*p++ = cpu_to_be32(args->bc_attrs.max_resp_sz);	/* max resp size */
	*p++ = cpu_to_be32(args->bc_attrs.max_resp_sz_cached);	/* Max resp sz cached */
	*p++ = cpu_to_be32(args->bc_attrs.max_ops);	/* max operations */
	*p++ = cpu_to_be32(args->bc_attrs.max_reqs);	/* max requests */
	*p++ = cpu_to_be32(0);				/* rdmachannel_attrs */

	*p++ = cpu_to_be32(args->cb_program);		/* cb_program */
	*p++ = cpu_to_be32(1);
	*p++ = cpu_to_be32(RPC_AUTH_UNIX);			/* auth_sys */

	/* authsys_parms rfc1831 */
	*p++ = cpu_to_be32(kसमय_प्रकारo_ns(nn->boot_समय));	/* stamp */
	p = xdr_encode_array(p, clnt->cl_nodename, clnt->cl_nodelen);
	*p++ = cpu_to_be32(0);				/* UID */
	*p++ = cpu_to_be32(0);				/* GID */
	*p = cpu_to_be32(0);				/* No more gids */
पूर्ण

अटल व्योम encode_destroy_session(काष्ठा xdr_stream *xdr,
				   स्थिर काष्ठा nfs4_session *session,
				   काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_DESTROY_SESSION, decode_destroy_session_maxsz, hdr);
	encode_opaque_fixed(xdr, session->sess_id.data, NFS4_MAX_SESSIONID_LEN);
पूर्ण

अटल व्योम encode_destroy_clientid(काष्ठा xdr_stream *xdr,
				   uपूर्णांक64_t clientid,
				   काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_DESTROY_CLIENTID, decode_destroy_clientid_maxsz, hdr);
	encode_uपूर्णांक64(xdr, clientid);
पूर्ण

अटल व्योम encode_reclaim_complete(काष्ठा xdr_stream *xdr,
				    स्थिर काष्ठा nfs41_reclaim_complete_args *args,
				    काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_RECLAIM_COMPLETE, decode_reclaim_complete_maxsz, hdr);
	encode_uपूर्णांक32(xdr, args->one_fs);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल व्योम encode_sequence(काष्ठा xdr_stream *xdr,
			    स्थिर काष्ठा nfs4_sequence_args *args,
			    काष्ठा compound_hdr *hdr)
अणु
#अगर defined(CONFIG_NFS_V4_1)
	काष्ठा nfs4_session *session;
	काष्ठा nfs4_slot_table *tp;
	काष्ठा nfs4_slot *slot = args->sa_slot;
	__be32 *p;

	tp = slot->table;
	session = tp->session;
	अगर (!session)
		वापस;

	encode_op_hdr(xdr, OP_SEQUENCE, decode_sequence_maxsz, hdr);

	/*
	 * Sessionid + seqid + slotid + max slotid + cache_this
	 */
	dprपूर्णांकk("%s: sessionid=%u:%u:%u:%u seqid=%d slotid=%d "
		"max_slotid=%d cache_this=%d\n",
		__func__,
		((u32 *)session->sess_id.data)[0],
		((u32 *)session->sess_id.data)[1],
		((u32 *)session->sess_id.data)[2],
		((u32 *)session->sess_id.data)[3],
		slot->seq_nr, slot->slot_nr,
		tp->highest_used_slotid, args->sa_cache_this);
	p = reserve_space(xdr, NFS4_MAX_SESSIONID_LEN + 16);
	p = xdr_encode_opaque_fixed(p, session->sess_id.data, NFS4_MAX_SESSIONID_LEN);
	*p++ = cpu_to_be32(slot->seq_nr);
	*p++ = cpu_to_be32(slot->slot_nr);
	*p++ = cpu_to_be32(tp->highest_used_slotid);
	*p = cpu_to_be32(args->sa_cache_this);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
अटल व्योम
encode_getdeviceinfo(काष्ठा xdr_stream *xdr,
		     स्थिर काष्ठा nfs4_getdeviceinfo_args *args,
		     काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_GETDEVICEINFO, decode_getdeviceinfo_maxsz, hdr);
	p = reserve_space(xdr, NFS4_DEVICEID4_SIZE + 4 + 4);
	p = xdr_encode_opaque_fixed(p, args->pdev->dev_id.data,
				    NFS4_DEVICEID4_SIZE);
	*p++ = cpu_to_be32(args->pdev->layout_type);
	*p++ = cpu_to_be32(args->pdev->maxcount);	/* gdia_maxcount */

	p = reserve_space(xdr, 4 + 4);
	*p++ = cpu_to_be32(1);			/* biपंचांगap length */
	*p++ = cpu_to_be32(args->notअगरy_types);
पूर्ण

अटल व्योम
encode_layoutget(काष्ठा xdr_stream *xdr,
		      स्थिर काष्ठा nfs4_layoutget_args *args,
		      काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LAYOUTGET, decode_layoutget_maxsz, hdr);
	p = reserve_space(xdr, 36);
	*p++ = cpu_to_be32(0);     /* Signal layout available */
	*p++ = cpu_to_be32(args->type);
	*p++ = cpu_to_be32(args->range.iomode);
	p = xdr_encode_hyper(p, args->range.offset);
	p = xdr_encode_hyper(p, args->range.length);
	p = xdr_encode_hyper(p, args->minlength);
	encode_nfs4_stateid(xdr, &args->stateid);
	encode_uपूर्णांक32(xdr, args->maxcount);

	dprपूर्णांकk("%s: 1st type:0x%x iomode:%d off:%lu len:%lu mc:%d\n",
		__func__,
		args->type,
		args->range.iomode,
		(अचिन्हित दीर्घ)args->range.offset,
		(अचिन्हित दीर्घ)args->range.length,
		args->maxcount);
पूर्ण

अटल पूर्णांक
encode_layoutcommit(काष्ठा xdr_stream *xdr,
		    काष्ठा inode *inode,
		    स्थिर काष्ठा nfs4_layoutcommit_args *args,
		    काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	dprपूर्णांकk("%s: lbw: %llu type: %d\n", __func__, args->lastbytewritten,
		NFS_SERVER(args->inode)->pnfs_curr_ld->id);

	encode_op_hdr(xdr, OP_LAYOUTCOMMIT, decode_layoutcommit_maxsz, hdr);
	p = reserve_space(xdr, 20);
	/* Only whole file layouts */
	p = xdr_encode_hyper(p, 0); /* offset */
	p = xdr_encode_hyper(p, args->lastbytewritten + 1);	/* length */
	*p = cpu_to_be32(0); /* reclaim */
	encode_nfs4_stateid(xdr, &args->stateid);
	अगर (args->lastbytewritten != U64_MAX) अणु
		p = reserve_space(xdr, 20);
		*p++ = cpu_to_be32(1); /* newoffset = TRUE */
		p = xdr_encode_hyper(p, args->lastbytewritten);
	पूर्ण अन्यथा अणु
		p = reserve_space(xdr, 12);
		*p++ = cpu_to_be32(0); /* newoffset = FALSE */
	पूर्ण
	*p++ = cpu_to_be32(0); /* Never send समय_modअगरy_changed */
	*p++ = cpu_to_be32(NFS_SERVER(args->inode)->pnfs_curr_ld->id);/* type */

	encode_uपूर्णांक32(xdr, args->layoutupdate_len);
	अगर (args->layoutupdate_pages)
		xdr_ग_लिखो_pages(xdr, args->layoutupdate_pages, 0,
				args->layoutupdate_len);

	वापस 0;
पूर्ण

अटल व्योम
encode_layoutवापस(काष्ठा xdr_stream *xdr,
		    स्थिर काष्ठा nfs4_layoutवापस_args *args,
		    काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LAYOUTRETURN, decode_layoutवापस_maxsz, hdr);
	p = reserve_space(xdr, 16);
	*p++ = cpu_to_be32(0);		/* reclaim. always 0 क्रम now */
	*p++ = cpu_to_be32(args->layout_type);
	*p++ = cpu_to_be32(args->range.iomode);
	*p = cpu_to_be32(RETURN_खाता);
	p = reserve_space(xdr, 16);
	p = xdr_encode_hyper(p, args->range.offset);
	p = xdr_encode_hyper(p, args->range.length);
	spin_lock(&args->inode->i_lock);
	encode_nfs4_stateid(xdr, &args->stateid);
	spin_unlock(&args->inode->i_lock);
	अगर (args->ld_निजी->ops && args->ld_निजी->ops->encode)
		args->ld_निजी->ops->encode(xdr, args, args->ld_निजी);
	अन्यथा
		encode_uपूर्णांक32(xdr, 0);
पूर्ण

अटल पूर्णांक
encode_secinfo_no_name(काष्ठा xdr_stream *xdr,
		       स्थिर काष्ठा nfs41_secinfo_no_name_args *args,
		       काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SECINFO_NO_NAME, decode_secinfo_no_name_maxsz, hdr);
	encode_uपूर्णांक32(xdr, args->style);
	वापस 0;
पूर्ण

अटल व्योम encode_test_stateid(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा nfs41_test_stateid_args *args,
				काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_TEST_STATEID, decode_test_stateid_maxsz, hdr);
	encode_uपूर्णांक32(xdr, 1);
	encode_nfs4_stateid(xdr, args->stateid);
पूर्ण

अटल व्योम encode_मुक्त_stateid(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा nfs41_मुक्त_stateid_args *args,
				काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_FREE_STATEID, decode_मुक्त_stateid_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->stateid);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
encode_layoutवापस(काष्ठा xdr_stream *xdr,
		    स्थिर काष्ठा nfs4_layoutवापस_args *args,
		    काष्ठा compound_hdr *hdr)
अणु
पूर्ण

अटल व्योम
encode_layoutget(काष्ठा xdr_stream *xdr,
		      स्थिर काष्ठा nfs4_layoutget_args *args,
		      काष्ठा compound_hdr *hdr)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

/*
 * END OF "GENERIC" ENCODE ROUTINES.
 */

अटल u32 nfs4_xdr_minorversion(स्थिर काष्ठा nfs4_sequence_args *args)
अणु
#अगर defined(CONFIG_NFS_V4_1)
	काष्ठा nfs4_session *session = args->sa_slot->table->session;
	अगर (session)
		वापस session->clp->cl_mvops->minor_version;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
	वापस 0;
पूर्ण

/*
 * Encode an ACCESS request
 */
अटल व्योम nfs4_xdr_enc_access(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_accessargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_access(xdr, args->access, &hdr);
	अगर (args->biपंचांगask)
		encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LOOKUP request
 */
अटल व्योम nfs4_xdr_enc_lookup(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_lookup_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->dir_fh, &hdr);
	encode_lookup(xdr, args->name, &hdr);
	encode_getfh(xdr, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LOOKUPP request
 */
अटल व्योम nfs4_xdr_enc_lookupp(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
		स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_lookupp_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_lookupp(xdr, &hdr);
	encode_getfh(xdr, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LOOKUP_ROOT request
 */
अटल व्योम nfs4_xdr_enc_lookup_root(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_lookup_root_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putrootfh(xdr, &hdr);
	encode_getfh(xdr, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode REMOVE request
 */
अटल व्योम nfs4_xdr_enc_हटाओ(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_हटाओargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_हटाओ(xdr, &args->name, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode RENAME request
 */
अटल व्योम nfs4_xdr_enc_नाम(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_नामargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->old_dir, &hdr);
	encode_savefh(xdr, &hdr);
	encode_putfh(xdr, args->new_dir, &hdr);
	encode_नाम(xdr, args->old_name, args->new_name, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LINK request
 */
अटल व्योम nfs4_xdr_enc_link(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_link_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_savefh(xdr, &hdr);
	encode_putfh(xdr, args->dir_fh, &hdr);
	encode_link(xdr, args->name, &hdr);
	encode_restorefh(xdr, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode CREATE request
 */
अटल व्योम nfs4_xdr_enc_create(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_create_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->dir_fh, &hdr);
	encode_create(xdr, args, &hdr);
	encode_getfh(xdr, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode SYMLINK request
 */
अटल व्योम nfs4_xdr_enc_symlink(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_create_arg *args = data;

	nfs4_xdr_enc_create(req, xdr, args);
पूर्ण

/*
 * Encode GETATTR request
 */
अटल व्योम nfs4_xdr_enc_getattr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_getattr_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a CLOSE request
 */
अटल व्योम nfs4_xdr_enc_बंद(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_बंदargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	अगर (args->lr_args)
		encode_layoutवापस(xdr, args->lr_args, &hdr);
	अगर (args->biपंचांगask != शून्य)
		encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_बंद(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode an OPEN request
 */
अटल व्योम nfs4_xdr_enc_खोलो(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_खोलोargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_खोलो(xdr, args, &hdr);
	encode_getfh(xdr, &hdr);
	अगर (args->access)
		encode_access(xdr, args->access, &hdr);
	encode_getfattr_खोलो(xdr, args->biपंचांगask, args->खोलो_biपंचांगap, &hdr);
	अगर (args->lg_args) अणु
		encode_layoutget(xdr, args->lg_args, &hdr);
		rpc_prepare_reply_pages(req, args->lg_args->layout.pages, 0,
					args->lg_args->layout.pglen,
					hdr.replen - pagepad_maxsz);
	पूर्ण
	encode_nops(&hdr);
पूर्ण

/*
 * Encode an OPEN_CONFIRM request
 */
अटल व्योम nfs4_xdr_enc_खोलो_confirm(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_खोलो_confirmargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.nops   = 0,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_खोलो_confirm(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode an OPEN request with no attributes.
 */
अटल व्योम nfs4_xdr_enc_खोलो_noattr(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_खोलोargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_खोलो(xdr, args, &hdr);
	अगर (args->access)
		encode_access(xdr, args->access, &hdr);
	encode_getfattr_खोलो(xdr, args->biपंचांगask, args->खोलो_biपंचांगap, &hdr);
	अगर (args->lg_args) अणु
		encode_layoutget(xdr, args->lg_args, &hdr);
		rpc_prepare_reply_pages(req, args->lg_args->layout.pages, 0,
					args->lg_args->layout.pglen,
					hdr.replen - pagepad_maxsz);
	पूर्ण
	encode_nops(&hdr);
पूर्ण

/*
 * Encode an OPEN_DOWNGRADE request
 */
अटल व्योम nfs4_xdr_enc_खोलो_करोwngrade(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_बंदargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	अगर (args->lr_args)
		encode_layoutवापस(xdr, args->lr_args, &hdr);
	encode_खोलो_करोwngrade(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a LOCK request
 */
अटल व्योम nfs4_xdr_enc_lock(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_lock_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_lock(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a LOCKT request
 */
अटल व्योम nfs4_xdr_enc_lockt(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_lockt_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_lockt(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a LOCKU request
 */
अटल व्योम nfs4_xdr_enc_locku(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_locku_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_locku(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

अटल व्योम nfs4_xdr_enc_release_lockowner(काष्ठा rpc_rqst *req,
					   काष्ठा xdr_stream *xdr,
					   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_release_lockowner_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = 0,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_release_lockowner(xdr, &args->lock_owner, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a READLINK request
 */
अटल व्योम nfs4_xdr_enc_पढ़ोlink(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_पढ़ोlink *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_पढ़ोlink(xdr, args, req, &hdr);

	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->pglen, hdr.replen - pagepad_maxsz);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a READसूची request
 */
अटल व्योम nfs4_xdr_enc_सूची_पढ़ो(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_सूची_पढ़ो_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_सूची_पढ़ो(xdr, args, req, &hdr);

	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->count, hdr.replen - pagepad_maxsz);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a READ request
 */
अटल व्योम nfs4_xdr_enc_पढ़ो(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_पढ़ो(xdr, args, &hdr);

	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->count, hdr.replen - pagepad_maxsz);
	req->rq_rcv_buf.flags |= XDRBUF_READ;
	encode_nops(&hdr);
पूर्ण

/*
 * Encode an SETATTR request
 */
अटल व्योम nfs4_xdr_enc_setattr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_setattrargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_setattr(xdr, args, args->server, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a GETACL request
 */
अटल व्योम nfs4_xdr_enc_getacl(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_getaclargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	स्थिर __u32 nfs4_acl_biपंचांगap[1] = अणु
		[0] = FATTR4_WORD0_ACL,
	पूर्ण;
	uपूर्णांक32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	replen = hdr.replen + op_decode_hdr_maxsz;
	encode_getattr(xdr, nfs4_acl_biपंचांगap, शून्य,
			ARRAY_SIZE(nfs4_acl_biपंचांगap), &hdr);

	rpc_prepare_reply_pages(req, args->acl_pages, 0,
				args->acl_len, replen);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode a WRITE request
 */
अटल व्योम nfs4_xdr_enc_ग_लिखो(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_ग_लिखो(xdr, args, &hdr);
	req->rq_snd_buf.flags |= XDRBUF_WRITE;
	अगर (args->biपंचांगask)
		encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 *  a COMMIT request
 */
अटल व्योम nfs4_xdr_enc_commit(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_commitargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_commit(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * FSINFO request
 */
अटल व्योम nfs4_xdr_enc_fsinfo(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_fsinfo_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_fsinfo(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a PATHCONF request
 */
अटल व्योम nfs4_xdr_enc_pathconf(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_pathconf_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_getattr(xdr, nfs4_pathconf_biपंचांगap, args->biपंचांगask,
			ARRAY_SIZE(nfs4_pathconf_biपंचांगap), &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a STATFS request
 */
अटल व्योम nfs4_xdr_enc_statfs(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_statfs_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_getattr(xdr, nfs4_statfs_biपंचांगap, args->biपंचांगask,
			ARRAY_SIZE(nfs4_statfs_biपंचांगap), &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * GETATTR_BITMAP request
 */
अटल व्योम nfs4_xdr_enc_server_caps(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_server_caps_arg *args = data;
	स्थिर u32 *biपंचांगask = args->biपंचांगask;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fhandle, &hdr);
	encode_getattr(xdr, biपंचांगask, शून्य, 3, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a RENEW request
 */
अटल व्योम nfs4_xdr_enc_renew(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)

अणु
	स्थिर काष्ठा nfs_client *clp = data;
	काष्ठा compound_hdr hdr = अणु
		.nops	= 0,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_renew(xdr, clp->cl_clientid, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a SETCLIENTID request
 */
अटल व्योम nfs4_xdr_enc_setclientid(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_setclientid *sc = data;
	काष्ठा compound_hdr hdr = अणु
		.nops	= 0,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_setclientid(xdr, sc, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a SETCLIENTID_CONFIRM request
 */
अटल व्योम nfs4_xdr_enc_setclientid_confirm(काष्ठा rpc_rqst *req,
					     काष्ठा xdr_stream *xdr,
					     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_setclientid_res *arg = data;
	काष्ठा compound_hdr hdr = अणु
		.nops	= 0,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_setclientid_confirm(xdr, arg, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * DELEGRETURN request
 */
अटल व्योम nfs4_xdr_enc_delegवापस(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_delegवापसargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fhandle, &hdr);
	अगर (args->lr_args)
		encode_layoutवापस(xdr, args->lr_args, &hdr);
	अगर (args->biपंचांगask)
		encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_delegवापस(xdr, args->stateid, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode FS_LOCATIONS request
 */
अटल व्योम nfs4_xdr_enc_fs_locations(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_fs_locations_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	uपूर्णांक32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	अगर (args->migration) अणु
		encode_putfh(xdr, args->fh, &hdr);
		replen = hdr.replen;
		encode_fs_locations(xdr, args->biपंचांगask, &hdr);
		अगर (args->renew)
			encode_renew(xdr, args->clientid, &hdr);
	पूर्ण अन्यथा अणु
		encode_putfh(xdr, args->dir_fh, &hdr);
		encode_lookup(xdr, args->name, &hdr);
		replen = hdr.replen;
		encode_fs_locations(xdr, args->biपंचांगask, &hdr);
	पूर्ण

	rpc_prepare_reply_pages(req, (काष्ठा page **)&args->page, 0,
				PAGE_SIZE, replen);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode SECINFO request
 */
अटल व्योम nfs4_xdr_enc_secinfo(काष्ठा rpc_rqst *req,
				काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_secinfo_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->dir_fh, &hdr);
	encode_secinfo(xdr, args->name, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode FSID_PRESENT request
 */
अटल व्योम nfs4_xdr_enc_fsid_present(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_fsid_present_arg *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_getfh(xdr, &hdr);
	अगर (args->renew)
		encode_renew(xdr, args->clientid, &hdr);
	encode_nops(&hdr);
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
/*
 * BIND_CONN_TO_SESSION request
 */
अटल व्योम nfs4_xdr_enc_bind_conn_to_session(काष्ठा rpc_rqst *req,
				काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_bind_conn_to_session_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = args->client->cl_mvops->minor_version,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_bind_conn_to_session(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * EXCHANGE_ID request
 */
अटल व्योम nfs4_xdr_enc_exchange_id(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_exchange_id_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = args->client->cl_mvops->minor_version,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_exchange_id(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a CREATE_SESSION request
 */
अटल व्योम nfs4_xdr_enc_create_session(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_create_session_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = args->client->cl_mvops->minor_version,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_create_session(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a DESTROY_SESSION request
 */
अटल व्योम nfs4_xdr_enc_destroy_session(काष्ठा rpc_rqst *req,
					 काष्ठा xdr_stream *xdr,
					 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_session *session = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = session->clp->cl_mvops->minor_version,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_destroy_session(xdr, session, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a DESTROY_CLIENTID request
 */
अटल व्योम nfs4_xdr_enc_destroy_clientid(काष्ठा rpc_rqst *req,
					 काष्ठा xdr_stream *xdr,
					 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_client *clp = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = clp->cl_mvops->minor_version,
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_destroy_clientid(xdr, clp->cl_clientid, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * a SEQUENCE request
 */
अटल व्योम nfs4_xdr_enc_sequence(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_sequence_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

#पूर्ण_अगर

/*
 * a GET_LEASE_TIME request
 */
अटल व्योम nfs4_xdr_enc_get_lease_समय(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_get_lease_समय_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->la_seq_args),
	पूर्ण;
	स्थिर u32 lease_biपंचांगap[3] = अणु FATTR4_WORD0_LEASE_TIME पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->la_seq_args, &hdr);
	encode_putrootfh(xdr, &hdr);
	encode_fsinfo(xdr, lease_biपंचांगap, &hdr);
	encode_nops(&hdr);
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1

/*
 * a RECLAIM_COMPLETE request
 */
अटल व्योम nfs4_xdr_enc_reclaim_complete(काष्ठा rpc_rqst *req,
					  काष्ठा xdr_stream *xdr,
					  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_reclaim_complete_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args)
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_reclaim_complete(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode GETDEVICEINFO request
 */
अटल व्योम nfs4_xdr_enc_getdeviceinfo(काष्ठा rpc_rqst *req,
				       काष्ठा xdr_stream *xdr,
				       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_getdeviceinfo_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	uपूर्णांक32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);

	replen = hdr.replen + op_decode_hdr_maxsz + 2;

	encode_getdeviceinfo(xdr, args, &hdr);

	/* set up reply kvec. device_addr4 opaque data is पढ़ो पूर्णांकo the
	 * pages */
	rpc_prepare_reply_pages(req, args->pdev->pages, args->pdev->pgbase,
				args->pdev->pglen, replen);
	encode_nops(&hdr);
पूर्ण

/*
 *  Encode LAYOUTGET request
 */
अटल व्योम nfs4_xdr_enc_layoutget(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_layoutget_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, NFS_FH(args->inode), &hdr);
	encode_layoutget(xdr, args, &hdr);

	rpc_prepare_reply_pages(req, args->layout.pages, 0,
				args->layout.pglen, hdr.replen - pagepad_maxsz);
	encode_nops(&hdr);
पूर्ण

/*
 *  Encode LAYOUTCOMMIT request
 */
अटल व्योम nfs4_xdr_enc_layoutcommit(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *priv)
अणु
	स्थिर काष्ठा nfs4_layoutcommit_args *args = priv;
	काष्ठा nfs4_layoutcommit_data *data =
		container_of(args, काष्ठा nfs4_layoutcommit_data, args);
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, NFS_FH(args->inode), &hdr);
	encode_layoutcommit(xdr, data->args.inode, args, &hdr);
	encode_getfattr(xdr, args->biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LAYOUTRETURN request
 */
अटल व्योम nfs4_xdr_enc_layoutवापस(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs4_layoutवापस_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, NFS_FH(args->inode), &hdr);
	encode_layoutवापस(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode SECINFO_NO_NAME request
 */
अटल व्योम nfs4_xdr_enc_secinfo_no_name(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_secinfo_no_name_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putrootfh(xdr, &hdr);
	encode_secinfo_no_name(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 *  Encode TEST_STATEID request
 */
अटल व्योम nfs4_xdr_enc_test_stateid(काष्ठा rpc_rqst *req,
				      काष्ठा xdr_stream *xdr,
				      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_test_stateid_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_test_stateid(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 *  Encode FREE_STATEID request
 */
अटल व्योम nfs4_xdr_enc_मुक्त_stateid(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs41_मुक्त_stateid_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_मुक्त_stateid(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल पूर्णांक decode_opaque_अंतरभूत(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक *len, अक्षर **string)
अणु
	sमाप_प्रकार ret = xdr_stream_decode_opaque_अंतरभूत(xdr, (व्योम **)string,
			NFS4_OPAQUE_LIMIT);
	अगर (unlikely(ret < 0))
		वापस -EIO;
	*len = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_compound_hdr(काष्ठा xdr_stream *xdr, काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	hdr->status = be32_to_cpup(p++);
	hdr->taglen = be32_to_cpup(p);

	p = xdr_अंतरभूत_decode(xdr, hdr->taglen + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	hdr->tag = (अक्षर *)p;
	p += XDR_QUADLEN(hdr->taglen);
	hdr->nops = be32_to_cpup(p);
	अगर (unlikely(hdr->nops < 1))
		वापस nfs4_stat_to_त्रुटि_सं(hdr->status);
	वापस 0;
पूर्ण

अटल bool __decode_op_hdr(काष्ठा xdr_stream *xdr, क्रमागत nfs_opnum4 expected,
		पूर्णांक *nfs_retval)
अणु
	__be32 *p;
	uपूर्णांक32_t opnum;
	पूर्णांक32_t nfserr;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		जाओ out_overflow;
	opnum = be32_to_cpup(p++);
	अगर (unlikely(opnum != expected))
		जाओ out_bad_operation;
	अगर (unlikely(*p != cpu_to_be32(NFS_OK)))
		जाओ out_status;
	*nfs_retval = 0;
	वापस true;
out_status:
	nfserr = be32_to_cpup(p);
	trace_nfs4_xdr_status(xdr, opnum, nfserr);
	*nfs_retval = nfs4_stat_to_त्रुटि_सं(nfserr);
	वापस true;
out_bad_operation:
	trace_nfs4_xdr_bad_operation(xdr, opnum, expected);
	*nfs_retval = -EREMOTEIO;
	वापस false;
out_overflow:
	*nfs_retval = -EIO;
	वापस false;
पूर्ण

अटल पूर्णांक decode_op_hdr(काष्ठा xdr_stream *xdr, क्रमागत nfs_opnum4 expected)
अणु
	पूर्णांक retval;

	__decode_op_hdr(xdr, expected, &retval);
	वापस retval;
पूर्ण

/* Dummy routine */
अटल पूर्णांक decode_ace(काष्ठा xdr_stream *xdr, व्योम *ace)
अणु
	__be32 *p;
	अचिन्हित पूर्णांक म_माप;
	अक्षर *str;

	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(!p))
		वापस -EIO;
	वापस decode_opaque_अंतरभूत(xdr, &म_माप, &str);
पूर्ण

अटल sमाप_प्रकार
decode_biपंचांगap4(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, माप_प्रकार sz)
अणु
	sमाप_प्रकार ret;

	ret = xdr_stream_decode_uपूर्णांक32_array(xdr, biपंचांगap, sz);
	अगर (likely(ret >= 0))
		वापस ret;
	अगर (ret != -EMSGSIZE)
		वापस -EIO;
	वापस sz;
पूर्ण

अटल पूर्णांक decode_attr_biपंचांगap(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap)
अणु
	sमाप_प्रकार ret;
	ret = decode_biपंचांगap4(xdr, biपंचांगap, 3);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक decode_attr_length(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *attrlen, अचिन्हित पूर्णांक *savep)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	*attrlen = be32_to_cpup(p);
	*savep = xdr_stream_pos(xdr);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_supported(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *biपंचांगask)
अणु
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_SUPPORTED_ATTRS)) अणु
		पूर्णांक ret;
		ret = decode_attr_biपंचांगap(xdr, biपंचांगask);
		अगर (unlikely(ret < 0))
			वापस ret;
		biपंचांगap[0] &= ~FATTR4_WORD0_SUPPORTED_ATTRS;
	पूर्ण अन्यथा
		biपंचांगask[0] = biपंचांगask[1] = biपंचांगask[2] = 0;
	dprपूर्णांकk("%s: bitmask=%08x:%08x:%08x\n", __func__,
		biपंचांगask[0], biपंचांगask[1], biपंचांगask[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_type(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *type)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*type = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_TYPE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_TYPE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*type = be32_to_cpup(p);
		अगर (*type < NF4REG || *type > NF4NAMEDATTR) अणु
			dprपूर्णांकk("%s: bad type %d\n", __func__, *type);
			वापस -EIO;
		पूर्ण
		biपंचांगap[0] &= ~FATTR4_WORD0_TYPE;
		ret = NFS_ATTR_FATTR_TYPE;
	पूर्ण
	dprपूर्णांकk("%s: type=0%o\n", __func__, nfs_type2fmt[*type]);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_fh_expire_type(काष्ठा xdr_stream *xdr,
				      uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *type)
अणु
	__be32 *p;

	*type = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_FH_EXPIRE_TYPE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_FH_EXPIRE_TYPE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*type = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_FH_EXPIRE_TYPE;
	पूर्ण
	dprपूर्णांकk("%s: expire type=0x%x\n", __func__, *type);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_change(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *change)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*change = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_CHANGE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_CHANGE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, change);
		biपंचांगap[0] &= ~FATTR4_WORD0_CHANGE;
		ret = NFS_ATTR_FATTR_CHANGE;
	पूर्ण
	dprपूर्णांकk("%s: change attribute=%Lu\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)*change);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_size(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *size)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*size = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_SIZE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_SIZE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, size);
		biपंचांगap[0] &= ~FATTR4_WORD0_SIZE;
		ret = NFS_ATTR_FATTR_SIZE;
	पूर्ण
	dprपूर्णांकk("%s: file size=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*size);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_link_support(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_LINK_SUPPORT - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_LINK_SUPPORT)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_LINK_SUPPORT;
	पूर्ण
	dprपूर्णांकk("%s: link support=%s\n", __func__, *res == 0 ? "false" : "true");
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_symlink_support(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_SYMLINK_SUPPORT - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_SYMLINK_SUPPORT)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_SYMLINK_SUPPORT;
	पूर्ण
	dprपूर्णांकk("%s: symlink support=%s\n", __func__, *res == 0 ? "false" : "true");
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_fsid(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा nfs_fsid *fsid)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	fsid->major = 0;
	fsid->minor = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_FSID - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_FSID)) अणु
		p = xdr_अंतरभूत_decode(xdr, 16);
		अगर (unlikely(!p))
			वापस -EIO;
		p = xdr_decode_hyper(p, &fsid->major);
		xdr_decode_hyper(p, &fsid->minor);
		biपंचांगap[0] &= ~FATTR4_WORD0_FSID;
		ret = NFS_ATTR_FATTR_FSID;
	पूर्ण
	dprपूर्णांकk("%s: fsid=(0x%Lx/0x%Lx)\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)fsid->major,
			(अचिन्हित दीर्घ दीर्घ)fsid->minor);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_lease_समय(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;

	*res = 60;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_LEASE_TIME - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_LEASE_TIME)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_LEASE_TIME;
	पूर्ण
	dprपूर्णांकk("%s: lease time=%u\n", __func__, (अचिन्हित पूर्णांक)*res);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_error(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, पूर्णांक32_t *res)
अणु
	__be32 *p;

	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_RDATTR_ERROR - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_RDATTR_ERROR)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		biपंचांगap[0] &= ~FATTR4_WORD0_RDATTR_ERROR;
		*res = -be32_to_cpup(p);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_exclcreat_supported(काष्ठा xdr_stream *xdr,
				 uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *biपंचांगask)
अणु
	अगर (likely(biपंचांगap[2] & FATTR4_WORD2_SUPPATTR_EXCLCREAT)) अणु
		पूर्णांक ret;
		ret = decode_attr_biपंचांगap(xdr, biपंचांगask);
		अगर (unlikely(ret < 0))
			वापस ret;
		biपंचांगap[2] &= ~FATTR4_WORD2_SUPPATTR_EXCLCREAT;
	पूर्ण अन्यथा
		biपंचांगask[0] = biपंचांगask[1] = biपंचांगask[2] = 0;
	dprपूर्णांकk("%s: bitmask=%08x:%08x:%08x\n", __func__,
		biपंचांगask[0], biपंचांगask[1], biपंचांगask[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_filehandle(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा nfs_fh *fh)
अणु
	__be32 *p;
	u32 len;

	अगर (fh != शून्य)
		स_रखो(fh, 0, माप(*fh));

	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_खाताHANDLE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_खाताHANDLE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		len = be32_to_cpup(p);
		अगर (len > NFS4_FHSIZE || len == 0) अणु
			trace_nfs4_xdr_bad_filehandle(xdr, OP_READसूची,
						      NFS4ERR_BADHANDLE);
			वापस -EREMOTEIO;
		पूर्ण
		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EIO;
		अगर (fh != शून्य) अणु
			स_नकल(fh->data, p, len);
			fh->size = len;
		पूर्ण
		biपंचांगap[0] &= ~FATTR4_WORD0_खाताHANDLE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_aclsupport(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_ACLSUPPORT - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_ACLSUPPORT)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_ACLSUPPORT;
	पूर्ण
	dprपूर्णांकk("%s: ACLs supported=%u\n", __func__, (अचिन्हित पूर्णांक)*res);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_fileid(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *fileid)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*fileid = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_खाताID - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_खाताID)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, fileid);
		biपंचांगap[0] &= ~FATTR4_WORD0_खाताID;
		ret = NFS_ATTR_FATTR_खाताID;
	पूर्ण
	dprपूर्णांकk("%s: fileid=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*fileid);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_mounted_on_fileid(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *fileid)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*fileid = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_MOUNTED_ON_खाताID - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_MOUNTED_ON_खाताID)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, fileid);
		biपंचांगap[1] &= ~FATTR4_WORD1_MOUNTED_ON_खाताID;
		ret = NFS_ATTR_FATTR_MOUNTED_ON_खाताID;
	पूर्ण
	dprपूर्णांकk("%s: fileid=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*fileid);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_files_avail(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_खाताS_AVAIL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_खाताS_AVAIL)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[0] &= ~FATTR4_WORD0_खाताS_AVAIL;
	पूर्ण
	dprपूर्णांकk("%s: files avail=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_files_मुक्त(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_खाताS_FREE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_खाताS_FREE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[0] &= ~FATTR4_WORD0_खाताS_FREE;
	पूर्ण
	dprपूर्णांकk("%s: files free=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_files_total(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_खाताS_TOTAL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_खाताS_TOTAL)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[0] &= ~FATTR4_WORD0_खाताS_TOTAL;
	पूर्ण
	dprपूर्णांकk("%s: files total=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_pathname(काष्ठा xdr_stream *xdr, काष्ठा nfs4_pathname *path)
अणु
	u32 n;
	__be32 *p;
	पूर्णांक status = 0;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	n = be32_to_cpup(p);
	अगर (n == 0)
		जाओ root_path;
	dprपूर्णांकk("pathname4: ");
	अगर (n > NFS4_PATHNAME_MAXCOMPONENTS) अणु
		dprपूर्णांकk("cannot parse %d components in path\n", n);
		जाओ out_eio;
	पूर्ण
	क्रम (path->ncomponents = 0; path->ncomponents < n; path->ncomponents++) अणु
		काष्ठा nfs4_string *component = &path->components[path->ncomponents];
		status = decode_opaque_अंतरभूत(xdr, &component->len, &component->data);
		अगर (unlikely(status != 0))
			जाओ out_eio;
		अगरdebug (XDR)
			pr_cont("%s%.*s ",
				(path->ncomponents != n ? "/ " : ""),
				component->len, component->data);
	पूर्ण
out:
	वापस status;
root_path:
/* a root pathname is sent as a zero component4 */
	path->ncomponents = 1;
	path->components[0].len=0;
	path->components[0].data=शून्य;
	dprपूर्णांकk("pathname4: /\n");
	जाओ out;
out_eio:
	dprपूर्णांकk(" status %d", status);
	status = -EIO;
	जाओ out;
पूर्ण

अटल पूर्णांक decode_attr_fs_locations(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा nfs4_fs_locations *res)
अणु
	पूर्णांक n;
	__be32 *p;
	पूर्णांक status = -EIO;

	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_FS_LOCATIONS -1U)))
		जाओ out;
	status = 0;
	अगर (unlikely(!(biपंचांगap[0] & FATTR4_WORD0_FS_LOCATIONS)))
		जाओ out;
	biपंचांगap[0] &= ~FATTR4_WORD0_FS_LOCATIONS;
	status = -EIO;
	/* Ignore borken servers that वापस unrequested attrs */
	अगर (unlikely(res == शून्य))
		जाओ out;
	dprपूर्णांकk("%s: fsroot:\n", __func__);
	status = decode_pathname(xdr, &res->fs_path);
	अगर (unlikely(status != 0))
		जाओ out;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		जाओ out_eio;
	n = be32_to_cpup(p);
	अगर (n <= 0)
		जाओ out_eio;
	क्रम (res->nlocations = 0; res->nlocations < n; res->nlocations++) अणु
		u32 m;
		काष्ठा nfs4_fs_location *loc;

		अगर (res->nlocations == NFS4_FS_LOCATIONS_MAXENTRIES)
			अवरोध;
		loc = &res->locations[res->nlocations];
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			जाओ out_eio;
		m = be32_to_cpup(p);

		dprपूर्णांकk("%s: servers:\n", __func__);
		क्रम (loc->nservers = 0; loc->nservers < m; loc->nservers++) अणु
			काष्ठा nfs4_string *server;

			अगर (loc->nservers == NFS4_FS_LOCATION_MAXSERVERS) अणु
				अचिन्हित पूर्णांक i;
				dprपूर्णांकk("%s: using first %u of %u servers "
					"returned for location %u\n",
						__func__,
						NFS4_FS_LOCATION_MAXSERVERS,
						m, res->nlocations);
				क्रम (i = loc->nservers; i < m; i++) अणु
					अचिन्हित पूर्णांक len;
					अक्षर *data;
					status = decode_opaque_अंतरभूत(xdr, &len, &data);
					अगर (unlikely(status != 0))
						जाओ out_eio;
				पूर्ण
				अवरोध;
			पूर्ण
			server = &loc->servers[loc->nservers];
			status = decode_opaque_अंतरभूत(xdr, &server->len, &server->data);
			अगर (unlikely(status != 0))
				जाओ out_eio;
			dprपूर्णांकk("%s ", server->data);
		पूर्ण
		status = decode_pathname(xdr, &loc->rootpath);
		अगर (unlikely(status != 0))
			जाओ out_eio;
	पूर्ण
	अगर (res->nlocations != 0)
		status = NFS_ATTR_FATTR_V4_LOCATIONS;
out:
	dprपूर्णांकk("%s: fs_locations done, error = %d\n", __func__, status);
	वापस status;
out_eio:
	status = -EIO;
	जाओ out;
पूर्ण

अटल पूर्णांक decode_attr_maxfilesize(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_MAXखाताSIZE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_MAXखाताSIZE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[0] &= ~FATTR4_WORD0_MAXखाताSIZE;
	पूर्ण
	dprपूर्णांकk("%s: maxfilesize=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_maxlink(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *maxlink)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*maxlink = 1;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_MAXLINK - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_MAXLINK)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*maxlink = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_MAXLINK;
	पूर्ण
	dprपूर्णांकk("%s: maxlink=%u\n", __func__, *maxlink);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_maxname(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *maxname)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*maxname = 1024;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_MAXNAME - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_MAXNAME)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*maxname = be32_to_cpup(p);
		biपंचांगap[0] &= ~FATTR4_WORD0_MAXNAME;
	पूर्ण
	dprपूर्णांकk("%s: maxname=%u\n", __func__, *maxname);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_maxपढ़ो(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 1024;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_MAXREAD - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_MAXREAD)) अणु
		uपूर्णांक64_t maxपढ़ो;
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, &maxपढ़ो);
		अगर (maxपढ़ो > 0x7FFFFFFF)
			maxपढ़ो = 0x7FFFFFFF;
		*res = (uपूर्णांक32_t)maxपढ़ो;
		biपंचांगap[0] &= ~FATTR4_WORD0_MAXREAD;
	पूर्ण
	dprपूर्णांकk("%s: maxread=%lu\n", __func__, (अचिन्हित दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_maxग_लिखो(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 1024;
	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_MAXWRITE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_MAXWRITE)) अणु
		uपूर्णांक64_t maxग_लिखो;
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, &maxग_लिखो);
		अगर (maxग_लिखो > 0x7FFFFFFF)
			maxग_लिखो = 0x7FFFFFFF;
		*res = (uपूर्णांक32_t)maxग_लिखो;
		biपंचांगap[0] &= ~FATTR4_WORD0_MAXWRITE;
	पूर्ण
	dprपूर्णांकk("%s: maxwrite=%lu\n", __func__, (अचिन्हित दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_mode(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, umode_t *mode)
अणु
	uपूर्णांक32_t पंचांगp;
	__be32 *p;
	पूर्णांक ret = 0;

	*mode = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_MODE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_MODE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		पंचांगp = be32_to_cpup(p);
		*mode = पंचांगp & ~S_IFMT;
		biपंचांगap[1] &= ~FATTR4_WORD1_MODE;
		ret = NFS_ATTR_FATTR_MODE;
	पूर्ण
	dprपूर्णांकk("%s: file mode=0%o\n", __func__, (अचिन्हित पूर्णांक)*mode);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_nlink(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक32_t *nlink)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*nlink = 1;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_NUMLINKS - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_NUMLINKS)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*nlink = be32_to_cpup(p);
		biपंचांगap[1] &= ~FATTR4_WORD1_NUMLINKS;
		ret = NFS_ATTR_FATTR_NLINK;
	पूर्ण
	dprपूर्णांकk("%s: nlink=%u\n", __func__, (अचिन्हित पूर्णांक)*nlink);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार decode_nfs4_string(काष्ठा xdr_stream *xdr,
		काष्ठा nfs4_string *name, gfp_t gfp_flags)
अणु
	sमाप_प्रकार ret;

	ret = xdr_stream_decode_string_dup(xdr, &name->data,
			XDR_MAX_NETOBJ, gfp_flags);
	name->len = 0;
	अगर (ret > 0)
		name->len = ret;
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_owner(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
		स्थिर काष्ठा nfs_server *server, kuid_t *uid,
		काष्ठा nfs4_string *owner_name)
अणु
	sमाप_प्रकार len;
	अक्षर *p;

	*uid = make_kuid(&init_user_ns, -2);
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_OWNER - 1U)))
		वापस -EIO;
	अगर (!(biपंचांगap[1] & FATTR4_WORD1_OWNER))
		वापस 0;
	biपंचांगap[1] &= ~FATTR4_WORD1_OWNER;

	अगर (owner_name != शून्य) अणु
		len = decode_nfs4_string(xdr, owner_name, GFP_NOIO);
		अगर (len <= 0)
			जाओ out;
		dprपूर्णांकk("%s: name=%s\n", __func__, owner_name->data);
		वापस NFS_ATTR_FATTR_OWNER_NAME;
	पूर्ण अन्यथा अणु
		len = xdr_stream_decode_opaque_अंतरभूत(xdr, (व्योम **)&p,
				XDR_MAX_NETOBJ);
		अगर (len <= 0 || nfs_map_name_to_uid(server, p, len, uid) != 0)
			जाओ out;
		dprपूर्णांकk("%s: uid=%d\n", __func__, (पूर्णांक)from_kuid(&init_user_ns, *uid));
		वापस NFS_ATTR_FATTR_OWNER;
	पूर्ण
out:
	अगर (len == -EBADMSG)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_group(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
		स्थिर काष्ठा nfs_server *server, kgid_t *gid,
		काष्ठा nfs4_string *group_name)
अणु
	sमाप_प्रकार len;
	अक्षर *p;

	*gid = make_kgid(&init_user_ns, -2);
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_OWNER_GROUP - 1U)))
		वापस -EIO;
	अगर (!(biपंचांगap[1] & FATTR4_WORD1_OWNER_GROUP))
		वापस 0;
	biपंचांगap[1] &= ~FATTR4_WORD1_OWNER_GROUP;

	अगर (group_name != शून्य) अणु
		len = decode_nfs4_string(xdr, group_name, GFP_NOIO);
		अगर (len <= 0)
			जाओ out;
		dprपूर्णांकk("%s: name=%s\n", __func__, group_name->data);
		वापस NFS_ATTR_FATTR_GROUP_NAME;
	पूर्ण अन्यथा अणु
		len = xdr_stream_decode_opaque_अंतरभूत(xdr, (व्योम **)&p,
				XDR_MAX_NETOBJ);
		अगर (len <= 0 || nfs_map_group_to_gid(server, p, len, gid) != 0)
			जाओ out;
		dprपूर्णांकk("%s: gid=%d\n", __func__, (पूर्णांक)from_kgid(&init_user_ns, *gid));
		वापस NFS_ATTR_FATTR_GROUP;
	पूर्ण
out:
	अगर (len == -EBADMSG)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_rdev(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, dev_t *rdev)
अणु
	uपूर्णांक32_t major = 0, minor = 0;
	__be32 *p;
	पूर्णांक ret = 0;

	*rdev = MKDEV(0,0);
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_RAWDEV - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_RAWDEV)) अणु
		dev_t पंचांगp;

		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		major = be32_to_cpup(p++);
		minor = be32_to_cpup(p);
		पंचांगp = MKDEV(major, minor);
		अगर (MAJOR(पंचांगp) == major && MINOR(पंचांगp) == minor)
			*rdev = पंचांगp;
		biपंचांगap[1] &= ~ FATTR4_WORD1_RAWDEV;
		ret = NFS_ATTR_FATTR_RDEV;
	पूर्ण
	dprपूर्णांकk("%s: rdev=(0x%x:0x%x)\n", __func__, major, minor);
	वापस ret;
पूर्ण

अटल पूर्णांक decode_attr_space_avail(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_SPACE_AVAIL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_SPACE_AVAIL)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[1] &= ~FATTR4_WORD1_SPACE_AVAIL;
	पूर्ण
	dprपूर्णांकk("%s: space avail=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_space_मुक्त(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_SPACE_FREE - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_SPACE_FREE)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[1] &= ~FATTR4_WORD1_SPACE_FREE;
	पूर्ण
	dprपूर्णांकk("%s: space free=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_space_total(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;

	*res = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_SPACE_TOTAL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_SPACE_TOTAL)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
		biपंचांगap[1] &= ~FATTR4_WORD1_SPACE_TOTAL;
	पूर्ण
	dprपूर्णांकk("%s: space total=%Lu\n", __func__, (अचिन्हित दीर्घ दीर्घ)*res);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_space_used(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t *used)
अणु
	__be32 *p;
	पूर्णांक ret = 0;

	*used = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_SPACE_USED - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_SPACE_USED)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, used);
		biपंचांगap[1] &= ~FATTR4_WORD1_SPACE_USED;
		ret = NFS_ATTR_FATTR_SPACE_USED;
	पूर्ण
	dprपूर्णांकk("%s: space used=%Lu\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)*used);
	वापस ret;
पूर्ण

अटल __be32 *
xdr_decode_nfsसमय4(__be32 *p, काष्ठा बारpec64 *t)
अणु
	__u64 sec;

	p = xdr_decode_hyper(p, &sec);
	t-> tv_sec = sec;
	t->tv_nsec = be32_to_cpup(p++);
	वापस p;
पूर्ण

अटल पूर्णांक decode_attr_समय(काष्ठा xdr_stream *xdr, काष्ठा बारpec64 *समय)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, nfsसमय4_maxsz << 2);
	अगर (unlikely(!p))
		वापस -EIO;
	xdr_decode_nfsसमय4(p, समय);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_समय_access(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा बारpec64 *समय)
अणु
	पूर्णांक status = 0;

	समय->tv_sec = 0;
	समय->tv_nsec = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_TIME_ACCESS - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_TIME_ACCESS)) अणु
		status = decode_attr_समय(xdr, समय);
		अगर (status == 0)
			status = NFS_ATTR_FATTR_ATIME;
		biपंचांगap[1] &= ~FATTR4_WORD1_TIME_ACCESS;
	पूर्ण
	dprपूर्णांकk("%s: atime=%lld\n", __func__, समय->tv_sec);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_समय_metadata(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा बारpec64 *समय)
अणु
	पूर्णांक status = 0;

	समय->tv_sec = 0;
	समय->tv_nsec = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_TIME_METADATA - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_TIME_METADATA)) अणु
		status = decode_attr_समय(xdr, समय);
		अगर (status == 0)
			status = NFS_ATTR_FATTR_CTIME;
		biपंचांगap[1] &= ~FATTR4_WORD1_TIME_METADATA;
	पूर्ण
	dprपूर्णांकk("%s: ctime=%lld\n", __func__, समय->tv_sec);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_समय_delta(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
				  काष्ठा बारpec64 *समय)
अणु
	पूर्णांक status = 0;

	समय->tv_sec = 0;
	समय->tv_nsec = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_TIME_DELTA - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_TIME_DELTA)) अणु
		status = decode_attr_समय(xdr, समय);
		biपंचांगap[1] &= ~FATTR4_WORD1_TIME_DELTA;
	पूर्ण
	dprपूर्णांकk("%s: time_delta=%lld %ld\n", __func__, समय->tv_sec,
		समय->tv_nsec);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_security_label(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
					काष्ठा nfs4_label *label)
अणु
	uपूर्णांक32_t pi = 0;
	uपूर्णांक32_t lfs = 0;
	__u32 len;
	__be32 *p;
	पूर्णांक status = 0;

	अगर (unlikely(biपंचांगap[2] & (FATTR4_WORD2_SECURITY_LABEL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[2] & FATTR4_WORD2_SECURITY_LABEL)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		lfs = be32_to_cpup(p++);
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		pi = be32_to_cpup(p++);
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		len = be32_to_cpup(p++);
		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EIO;
		अगर (len < NFS4_MAXLABELLEN) अणु
			अगर (label) अणु
				अगर (label->len) अणु
					अगर (label->len < len)
						वापस -दुस्फल;
					स_नकल(label->label, p, len);
				पूर्ण
				label->len = len;
				label->pi = pi;
				label->lfs = lfs;
				status = NFS_ATTR_FATTR_V4_SECURITY_LABEL;
			पूर्ण
			biपंचांगap[2] &= ~FATTR4_WORD2_SECURITY_LABEL;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING "%s: label too long (%u)!\n",
					__func__, len);
	पूर्ण
	अगर (label && label->label)
		dprपूर्णांकk("%s: label=%s, len=%d, PI=%d, LFS=%d\n", __func__,
			(अक्षर *)label->label, label->len, label->pi, label->lfs);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_समय_modअगरy(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap, काष्ठा बारpec64 *समय)
अणु
	पूर्णांक status = 0;

	समय->tv_sec = 0;
	समय->tv_nsec = 0;
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_TIME_MODIFY - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[1] & FATTR4_WORD1_TIME_MODIFY)) अणु
		status = decode_attr_समय(xdr, समय);
		अगर (status == 0)
			status = NFS_ATTR_FATTR_MTIME;
		biपंचांगap[1] &= ~FATTR4_WORD1_TIME_MODIFY;
	पूर्ण
	dprपूर्णांकk("%s: mtime=%lld\n", __func__, समय->tv_sec);
	वापस status;
पूर्ण

अटल पूर्णांक decode_attr_xattrsupport(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
				    uपूर्णांक32_t *res)
अणु
	__be32 *p;

	*res = 0;
	अगर (unlikely(biपंचांगap[2] & (FATTR4_WORD2_XATTR_SUPPORT - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[2] & FATTR4_WORD2_XATTR_SUPPORT)) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[2] &= ~FATTR4_WORD2_XATTR_SUPPORT;
	पूर्ण
	dprपूर्णांकk("%s: XATTR support=%s\n", __func__,
		*res == 0 ? "false" : "true");
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_attr_len(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक savep, uपूर्णांक32_t attrlen)
अणु
	अचिन्हित पूर्णांक attrwords = XDR_QUADLEN(attrlen);
	अचिन्हित पूर्णांक nwords = (xdr_stream_pos(xdr) - savep) >> 2;

	अगर (unlikely(attrwords != nwords)) अणु
		dprपूर्णांकk("%s: server returned incorrect attribute length: "
			"%u %c %u\n",
				__func__,
				attrwords << 2,
				(attrwords < nwords) ? '<' : '>',
				nwords << 2);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_change_info(काष्ठा xdr_stream *xdr, काष्ठा nfs4_change_info *cinfo)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 20);
	अगर (unlikely(!p))
		वापस -EIO;
	cinfo->atomic = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &cinfo->beक्रमe);
	xdr_decode_hyper(p, &cinfo->after);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_access(काष्ठा xdr_stream *xdr, u32 *supported, u32 *access)
अणु
	__be32 *p;
	uपूर्णांक32_t supp, acc;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_ACCESS);
	अगर (status)
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	supp = be32_to_cpup(p++);
	acc = be32_to_cpup(p);
	*supported = supp;
	*access = acc;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_opaque_fixed(काष्ठा xdr_stream *xdr, व्योम *buf, माप_प्रकार len)
अणु
	sमाप_प्रकार ret = xdr_stream_decode_opaque_fixed(xdr, buf, len);
	अगर (unlikely(ret < 0))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	वापस decode_opaque_fixed(xdr, stateid, NFS4_STATEID_SIZE);
पूर्ण

अटल पूर्णांक decode_खोलो_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_OPEN_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल पूर्णांक decode_lock_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_LOCK_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल पूर्णांक decode_delegation_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_DELEGATION_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल पूर्णांक decode_invalid_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	nfs4_stateid dummy;

	nfs4_stateid_copy(stateid, &invalid_stateid);
	वापस decode_stateid(xdr, &dummy);
पूर्ण

अटल पूर्णांक decode_बंद(काष्ठा xdr_stream *xdr, काष्ठा nfs_बंदres *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_CLOSE);
	अगर (status != -EIO)
		nfs_increment_खोलो_seqid(status, res->seqid);
	अगर (!status)
		status = decode_invalid_stateid(xdr, &res->stateid);
	वापस status;
पूर्ण

अटल पूर्णांक decode_verअगरier(काष्ठा xdr_stream *xdr, व्योम *verअगरier)
अणु
	वापस decode_opaque_fixed(xdr, verअगरier, NFS4_VERIFIER_SIZE);
पूर्ण

अटल पूर्णांक decode_ग_लिखो_verअगरier(काष्ठा xdr_stream *xdr, काष्ठा nfs_ग_लिखो_verअगरier *verअगरier)
अणु
	वापस decode_opaque_fixed(xdr, verअगरier->data, NFS4_VERIFIER_SIZE);
पूर्ण

अटल पूर्णांक decode_commit(काष्ठा xdr_stream *xdr, काष्ठा nfs_commitres *res)
अणु
	काष्ठा nfs_ग_लिखोverf *verf = res->verf;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_COMMIT);
	अगर (!status)
		status = decode_ग_लिखो_verअगरier(xdr, &verf->verअगरier);
	अगर (!status)
		verf->committed = NFS_खाता_SYNC;
	वापस status;
पूर्ण

अटल पूर्णांक decode_create(काष्ठा xdr_stream *xdr, काष्ठा nfs4_change_info *cinfo)
अणु
	__be32 *p;
	uपूर्णांक32_t bmlen;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_CREATE);
	अगर (status)
		वापस status;
	अगर ((status = decode_change_info(xdr, cinfo)))
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	bmlen = be32_to_cpup(p);
	p = xdr_अंतरभूत_decode(xdr, bmlen << 2);
	अगर (likely(p))
		वापस 0;
	वापस -EIO;
पूर्ण

अटल पूर्णांक decode_server_caps(काष्ठा xdr_stream *xdr, काष्ठा nfs4_server_caps_res *res)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen, biपंचांगap[3] = अणु0पूर्ण;
	पूर्णांक status;

	अगर ((status = decode_op_hdr(xdr, OP_GETATTR)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_biपंचांगap(xdr, biपंचांगap)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_length(xdr, &attrlen, &savep)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_supported(xdr, biपंचांगap, res->attr_biपंचांगask)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_fh_expire_type(xdr, biपंचांगap,
						 &res->fh_expire_type)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_link_support(xdr, biपंचांगap, &res->has_links)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_symlink_support(xdr, biपंचांगap, &res->has_symlinks)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_aclsupport(xdr, biपंचांगap, &res->acl_biपंचांगask)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_exclcreat_supported(xdr, biपंचांगap,
				res->exclcreat_biपंचांगask)) != 0)
		जाओ xdr_error;
	status = verअगरy_attr_len(xdr, savep, attrlen);
xdr_error:
	dprपूर्णांकk("%s: xdr returned %d!\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_statfs(काष्ठा xdr_stream *xdr, काष्ठा nfs_fsstat *fsstat)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen, biपंचांगap[3] = अणु0पूर्ण;
	पूर्णांक status;

	अगर ((status = decode_op_hdr(xdr, OP_GETATTR)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_biपंचांगap(xdr, biपंचांगap)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_length(xdr, &attrlen, &savep)) != 0)
		जाओ xdr_error;

	अगर ((status = decode_attr_files_avail(xdr, biपंचांगap, &fsstat->afiles)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_files_मुक्त(xdr, biपंचांगap, &fsstat->ffiles)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_files_total(xdr, biपंचांगap, &fsstat->tfiles)) != 0)
		जाओ xdr_error;

	status = -EIO;
	अगर (unlikely(biपंचांगap[0]))
		जाओ xdr_error;

	अगर ((status = decode_attr_space_avail(xdr, biपंचांगap, &fsstat->abytes)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_space_मुक्त(xdr, biपंचांगap, &fsstat->fbytes)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_space_total(xdr, biपंचांगap, &fsstat->tbytes)) != 0)
		जाओ xdr_error;

	status = verअगरy_attr_len(xdr, savep, attrlen);
xdr_error:
	dprपूर्णांकk("%s: xdr returned %d!\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_pathconf(काष्ठा xdr_stream *xdr, काष्ठा nfs_pathconf *pathconf)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen, biपंचांगap[3] = अणु0पूर्ण;
	पूर्णांक status;

	अगर ((status = decode_op_hdr(xdr, OP_GETATTR)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_biपंचांगap(xdr, biपंचांगap)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_length(xdr, &attrlen, &savep)) != 0)
		जाओ xdr_error;

	अगर ((status = decode_attr_maxlink(xdr, biपंचांगap, &pathconf->max_link)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_maxname(xdr, biपंचांगap, &pathconf->max_namelen)) != 0)
		जाओ xdr_error;

	status = verअगरy_attr_len(xdr, savep, attrlen);
xdr_error:
	dprपूर्णांकk("%s: xdr returned %d!\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_threshold_hपूर्णांक(काष्ठा xdr_stream *xdr,
				  uपूर्णांक32_t *biपंचांगap,
				  uपूर्णांक64_t *res,
				  uपूर्णांक32_t hपूर्णांक_bit)
अणु
	__be32 *p;

	*res = 0;
	अगर (likely(biपंचांगap[0] & hपूर्णांक_bit)) अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
		xdr_decode_hyper(p, res);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_first_threshold_item4(काष्ठा xdr_stream *xdr,
					काष्ठा nfs4_threshold *res)
अणु
	__be32 *p;
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t biपंचांगap[3] = अणु0,पूर्ण, attrlen;
	पूर्णांक status;

	/* layout type */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	res->l_type = be32_to_cpup(p);

	/* thi_hपूर्णांकset biपंचांगap */
	status = decode_attr_biपंचांगap(xdr, biपंचांगap);
	अगर (status < 0)
		जाओ xdr_error;

	/* thi_hपूर्णांकlist length */
	status = decode_attr_length(xdr, &attrlen, &savep);
	अगर (status < 0)
		जाओ xdr_error;
	/* thi_hपूर्णांकlist */
	status = decode_threshold_hपूर्णांक(xdr, biपंचांगap, &res->rd_sz, THRESHOLD_RD);
	अगर (status < 0)
		जाओ xdr_error;
	status = decode_threshold_hपूर्णांक(xdr, biपंचांगap, &res->wr_sz, THRESHOLD_WR);
	अगर (status < 0)
		जाओ xdr_error;
	status = decode_threshold_hपूर्णांक(xdr, biपंचांगap, &res->rd_io_sz,
				       THRESHOLD_RD_IO);
	अगर (status < 0)
		जाओ xdr_error;
	status = decode_threshold_hपूर्णांक(xdr, biपंचांगap, &res->wr_io_sz,
				       THRESHOLD_WR_IO);
	अगर (status < 0)
		जाओ xdr_error;

	status = verअगरy_attr_len(xdr, savep, attrlen);
	res->bm = biपंचांगap[0];

	dprपूर्णांकk("%s bm=0x%x rd_sz=%llu wr_sz=%llu rd_io=%llu wr_io=%llu\n",
		 __func__, res->bm, res->rd_sz, res->wr_sz, res->rd_io_sz,
		res->wr_io_sz);
xdr_error:
	dprपूर्णांकk("%s ret=%d!\n", __func__, status);
	वापस status;
पूर्ण

/*
 * Thresholds on pNFS direct I/O vrs MDS I/O
 */
अटल पूर्णांक decode_attr_mdsthreshold(काष्ठा xdr_stream *xdr,
				    uपूर्णांक32_t *biपंचांगap,
				    काष्ठा nfs4_threshold *res)
अणु
	__be32 *p;
	पूर्णांक status = 0;
	uपूर्णांक32_t num;

	अगर (unlikely(biपंचांगap[2] & (FATTR4_WORD2_MDSTHRESHOLD - 1U)))
		वापस -EIO;
	अगर (biपंचांगap[2] & FATTR4_WORD2_MDSTHRESHOLD) अणु
		/* Did the server वापस an unrequested attribute? */
		अगर (unlikely(res == शून्य))
			वापस -EREMOTEIO;
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		num = be32_to_cpup(p);
		अगर (num == 0)
			वापस 0;
		अगर (num > 1)
			prपूर्णांकk(KERN_INFO "%s: Warning: Multiple pNFS layout "
				"drivers per filesystem not supported\n",
				__func__);

		status = decode_first_threshold_item4(xdr, res);
		biपंचांगap[2] &= ~FATTR4_WORD2_MDSTHRESHOLD;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक decode_getfattr_attrs(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
		काष्ठा nfs_fattr *fattr, काष्ठा nfs_fh *fh,
		काष्ठा nfs4_fs_locations *fs_loc, काष्ठा nfs4_label *label,
		स्थिर काष्ठा nfs_server *server)
अणु
	पूर्णांक status;
	umode_t भ_शेषe = 0;
	uपूर्णांक32_t type;
	पूर्णांक32_t err;

	status = decode_attr_type(xdr, biपंचांगap, &type);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->mode = 0;
	अगर (status != 0) अणु
		fattr->mode |= nfs_type2fmt[type];
		fattr->valid |= status;
	पूर्ण

	status = decode_attr_change(xdr, biपंचांगap, &fattr->change_attr);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_size(xdr, biपंचांगap, &fattr->size);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_fsid(xdr, biपंचांगap, &fattr->fsid);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	err = 0;
	status = decode_attr_error(xdr, biपंचांगap, &err);
	अगर (status < 0)
		जाओ xdr_error;

	status = decode_attr_filehandle(xdr, biपंचांगap, fh);
	अगर (status < 0)
		जाओ xdr_error;

	status = decode_attr_fileid(xdr, biपंचांगap, &fattr->fileid);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_fs_locations(xdr, biपंचांगap, fs_loc);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = -EIO;
	अगर (unlikely(biपंचांगap[0]))
		जाओ xdr_error;

	status = decode_attr_mode(xdr, biपंचांगap, &भ_शेषe);
	अगर (status < 0)
		जाओ xdr_error;
	अगर (status != 0) अणु
		fattr->mode |= भ_शेषe;
		fattr->valid |= status;
	पूर्ण

	status = decode_attr_nlink(xdr, biपंचांगap, &fattr->nlink);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_owner(xdr, biपंचांगap, server, &fattr->uid, fattr->owner_name);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_group(xdr, biपंचांगap, server, &fattr->gid, fattr->group_name);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_rdev(xdr, biपंचांगap, &fattr->rdev);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_space_used(xdr, biपंचांगap, &fattr->du.nfs3.used);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_समय_access(xdr, biपंचांगap, &fattr->aसमय);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_समय_metadata(xdr, biपंचांगap, &fattr->स_समय);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_समय_modअगरy(xdr, biपंचांगap, &fattr->mसमय);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = decode_attr_mounted_on_fileid(xdr, biपंचांगap, &fattr->mounted_on_fileid);
	अगर (status < 0)
		जाओ xdr_error;
	fattr->valid |= status;

	status = -EIO;
	अगर (unlikely(biपंचांगap[1]))
		जाओ xdr_error;

	status = decode_attr_mdsthreshold(xdr, biपंचांगap, fattr->mdsthreshold);
	अगर (status < 0)
		जाओ xdr_error;

	अगर (label) अणु
		status = decode_attr_security_label(xdr, biपंचांगap, label);
		अगर (status < 0)
			जाओ xdr_error;
		fattr->valid |= status;
	पूर्ण

xdr_error:
	dprपूर्णांकk("%s: xdr returned %d\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_getfattr_generic(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा nfs_fh *fh, काष्ठा nfs4_fs_locations *fs_loc,
		काष्ठा nfs4_label *label, स्थिर काष्ठा nfs_server *server)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen,
		 biपंचांगap[3] = अणु0पूर्ण;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_GETATTR);
	अगर (status < 0)
		जाओ xdr_error;

	status = decode_attr_biपंचांगap(xdr, biपंचांगap);
	अगर (status < 0)
		जाओ xdr_error;

	status = decode_attr_length(xdr, &attrlen, &savep);
	अगर (status < 0)
		जाओ xdr_error;

	status = decode_getfattr_attrs(xdr, biपंचांगap, fattr, fh, fs_loc,
					label, server);
	अगर (status < 0)
		जाओ xdr_error;

	status = verअगरy_attr_len(xdr, savep, attrlen);
xdr_error:
	dprपूर्णांकk("%s: xdr returned %d\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_getfattr_label(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_label *label, स्थिर काष्ठा nfs_server *server)
अणु
	वापस decode_getfattr_generic(xdr, fattr, शून्य, शून्य, label, server);
पूर्ण

अटल पूर्णांक decode_getfattr(काष्ठा xdr_stream *xdr, काष्ठा nfs_fattr *fattr,
		स्थिर काष्ठा nfs_server *server)
अणु
	वापस decode_getfattr_generic(xdr, fattr, शून्य, शून्य, शून्य, server);
पूर्ण

/*
 * Decode potentially multiple layout types.
 */
अटल पूर्णांक decode_pnfs_layout_types(काष्ठा xdr_stream *xdr,
				    काष्ठा nfs_fsinfo *fsinfo)
अणु
	__be32 *p;
	uपूर्णांक32_t i;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	fsinfo->nlayouttypes = be32_to_cpup(p);

	/* pNFS is not supported by the underlying file प्रणाली */
	अगर (fsinfo->nlayouttypes == 0)
		वापस 0;

	/* Decode and set first layout type, move xdr->p past unused types */
	p = xdr_अंतरभूत_decode(xdr, fsinfo->nlayouttypes * 4);
	अगर (unlikely(!p))
		वापस -EIO;

	/* If we get too many, then just cap it at the max */
	अगर (fsinfo->nlayouttypes > NFS_MAX_LAYOUT_TYPES) अणु
		prपूर्णांकk(KERN_INFO "NFS: %s: Warning: Too many (%u) pNFS layout types\n",
			__func__, fsinfo->nlayouttypes);
		fsinfo->nlayouttypes = NFS_MAX_LAYOUT_TYPES;
	पूर्ण

	क्रम(i = 0; i < fsinfo->nlayouttypes; ++i)
		fsinfo->layouttype[i] = be32_to_cpup(p++);
	वापस 0;
पूर्ण

/*
 * The type of file प्रणाली exported.
 * Note we must ensure that layouttype is set in any non-error हाल.
 */
अटल पूर्णांक decode_attr_pnfstype(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
				काष्ठा nfs_fsinfo *fsinfo)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk("%s: bitmap is %x\n", __func__, biपंचांगap[1]);
	अगर (unlikely(biपंचांगap[1] & (FATTR4_WORD1_FS_LAYOUT_TYPES - 1U)))
		वापस -EIO;
	अगर (biपंचांगap[1] & FATTR4_WORD1_FS_LAYOUT_TYPES) अणु
		status = decode_pnfs_layout_types(xdr, fsinfo);
		biपंचांगap[1] &= ~FATTR4_WORD1_FS_LAYOUT_TYPES;
	पूर्ण
	वापस status;
पूर्ण

/*
 * The prefered block size क्रम layout directed io
 */
अटल पूर्णांक decode_attr_layout_blksize(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
				      uपूर्णांक32_t *res)
अणु
	__be32 *p;

	dprपूर्णांकk("%s: bitmap is %x\n", __func__, biपंचांगap[2]);
	*res = 0;
	अगर (biपंचांगap[2] & FATTR4_WORD2_LAYOUT_BLKSIZE) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[2] &= ~FATTR4_WORD2_LAYOUT_BLKSIZE;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The granularity of a CLONE operation.
 */
अटल पूर्णांक decode_attr_clone_blksize(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap,
				     uपूर्णांक32_t *res)
अणु
	__be32 *p;

	dprपूर्णांकk("%s: bitmap is %x\n", __func__, biपंचांगap[2]);
	*res = 0;
	अगर (biपंचांगap[2] & FATTR4_WORD2_CLONE_BLKSIZE) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		*res = be32_to_cpup(p);
		biपंचांगap[2] &= ~FATTR4_WORD2_CLONE_BLKSIZE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_attr_change_attr_type(काष्ठा xdr_stream *xdr,
					uपूर्णांक32_t *biपंचांगap,
					क्रमागत nfs4_change_attr_type *res)
अणु
	u32 पंचांगp = NFS4_CHANGE_TYPE_IS_UNDEFINED;

	dprपूर्णांकk("%s: bitmap is %x\n", __func__, biपंचांगap[2]);
	अगर (biपंचांगap[2] & FATTR4_WORD2_CHANGE_ATTR_TYPE) अणु
		अगर (xdr_stream_decode_u32(xdr, &पंचांगp))
			वापस -EIO;
		biपंचांगap[2] &= ~FATTR4_WORD2_CHANGE_ATTR_TYPE;
	पूर्ण

	चयन(पंचांगp) अणु
	हाल NFS4_CHANGE_TYPE_IS_MONOTONIC_INCR:
	हाल NFS4_CHANGE_TYPE_IS_VERSION_COUNTER:
	हाल NFS4_CHANGE_TYPE_IS_VERSION_COUNTER_NOPNFS:
	हाल NFS4_CHANGE_TYPE_IS_TIME_METADATA:
		*res = पंचांगp;
		अवरोध;
	शेष:
		*res = NFS4_CHANGE_TYPE_IS_UNDEFINED;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_fsinfo(काष्ठा xdr_stream *xdr, काष्ठा nfs_fsinfo *fsinfo)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen, biपंचांगap[3];
	पूर्णांक status;

	अगर ((status = decode_op_hdr(xdr, OP_GETATTR)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_biपंचांगap(xdr, biपंचांगap)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_length(xdr, &attrlen, &savep)) != 0)
		जाओ xdr_error;

	fsinfo->rपंचांगult = fsinfo->wपंचांगult = 512;	/* ??? */

	अगर ((status = decode_attr_lease_समय(xdr, biपंचांगap, &fsinfo->lease_समय)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_maxfilesize(xdr, biपंचांगap, &fsinfo->maxfilesize)) != 0)
		जाओ xdr_error;
	अगर ((status = decode_attr_maxपढ़ो(xdr, biपंचांगap, &fsinfo->rपंचांगax)) != 0)
		जाओ xdr_error;
	fsinfo->rtpref = fsinfo->dtpref = fsinfo->rपंचांगax;
	अगर ((status = decode_attr_maxग_लिखो(xdr, biपंचांगap, &fsinfo->wपंचांगax)) != 0)
		जाओ xdr_error;
	fsinfo->wtpref = fsinfo->wपंचांगax;

	status = -EIO;
	अगर (unlikely(biपंचांगap[0]))
		जाओ xdr_error;

	status = decode_attr_समय_delta(xdr, biपंचांगap, &fsinfo->समय_delta);
	अगर (status != 0)
		जाओ xdr_error;
	status = decode_attr_pnfstype(xdr, biपंचांगap, fsinfo);
	अगर (status != 0)
		जाओ xdr_error;

	status = -EIO;
	अगर (unlikely(biपंचांगap[1]))
		जाओ xdr_error;

	status = decode_attr_layout_blksize(xdr, biपंचांगap, &fsinfo->blksize);
	अगर (status)
		जाओ xdr_error;
	status = decode_attr_clone_blksize(xdr, biपंचांगap, &fsinfo->clone_blksize);
	अगर (status)
		जाओ xdr_error;

	status = decode_attr_change_attr_type(xdr, biपंचांगap,
					      &fsinfo->change_attr_type);
	अगर (status)
		जाओ xdr_error;

	status = decode_attr_xattrsupport(xdr, biपंचांगap,
					  &fsinfo->xattr_support);
	अगर (status)
		जाओ xdr_error;

	status = verअगरy_attr_len(xdr, savep, attrlen);
xdr_error:
	dprपूर्णांकk("%s: xdr returned %d!\n", __func__, -status);
	वापस status;
पूर्ण

अटल पूर्णांक decode_getfh(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	__be32 *p;
	uपूर्णांक32_t len;
	पूर्णांक status;

	/* Zero handle first to allow comparisons */
	स_रखो(fh, 0, माप(*fh));

	status = decode_op_hdr(xdr, OP_GETFH);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	len = be32_to_cpup(p);
	अगर (len > NFS4_FHSIZE || len == 0) अणु
		trace_nfs4_xdr_bad_filehandle(xdr, OP_GETFH, NFS4ERR_BADHANDLE);
		वापस -EREMOTEIO;
	पूर्ण
	fh->size = len;
	p = xdr_अंतरभूत_decode(xdr, len);
	अगर (unlikely(!p))
		वापस -EIO;
	स_नकल(fh->data, p, len);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_link(काष्ठा xdr_stream *xdr, काष्ठा nfs4_change_info *cinfo)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_LINK);
	अगर (status)
		वापस status;
	वापस decode_change_info(xdr, cinfo);
पूर्ण

/*
 * We create the owner, so we know a proper owner.id length is 4.
 */
अटल पूर्णांक decode_lock_denied (काष्ठा xdr_stream *xdr, काष्ठा file_lock *fl)
अणु
	uपूर्णांक64_t offset, length, clientid;
	__be32 *p;
	uपूर्णांक32_t namelen, type;

	p = xdr_अंतरभूत_decode(xdr, 32); /* पढ़ो 32 bytes */
	अगर (unlikely(!p))
		वापस -EIO;
	p = xdr_decode_hyper(p, &offset); /* पढ़ो 2 8-byte दीर्घ words */
	p = xdr_decode_hyper(p, &length);
	type = be32_to_cpup(p++); /* 4 byte पढ़ो */
	अगर (fl != शून्य) अणु /* manipulate file lock */
		fl->fl_start = (loff_t)offset;
		fl->fl_end = fl->fl_start + (loff_t)length - 1;
		अगर (length == ~(uपूर्णांक64_t)0)
			fl->fl_end = OFFSET_MAX;
		fl->fl_type = F_WRLCK;
		अगर (type & 1)
			fl->fl_type = F_RDLCK;
		fl->fl_pid = 0;
	पूर्ण
	p = xdr_decode_hyper(p, &clientid); /* पढ़ो 8 bytes */
	namelen = be32_to_cpup(p); /* पढ़ो 4 bytes */  /* have पढ़ो all 32 bytes now */
	p = xdr_अंतरभूत_decode(xdr, namelen); /* variable size field */
	अगर (likely(!p))
		वापस -EIO;
	वापस -NFS4ERR_DENIED;
पूर्ण

अटल पूर्णांक decode_lock(काष्ठा xdr_stream *xdr, काष्ठा nfs_lock_res *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_LOCK);
	अगर (status == -EIO)
		जाओ out;
	अगर (status == 0) अणु
		status = decode_lock_stateid(xdr, &res->stateid);
		अगर (unlikely(status))
			जाओ out;
	पूर्ण अन्यथा अगर (status == -NFS4ERR_DENIED)
		status = decode_lock_denied(xdr, शून्य);
	अगर (res->खोलो_seqid != शून्य)
		nfs_increment_खोलो_seqid(status, res->खोलो_seqid);
	nfs_increment_lock_seqid(status, res->lock_seqid);
out:
	वापस status;
पूर्ण

अटल पूर्णांक decode_lockt(काष्ठा xdr_stream *xdr, काष्ठा nfs_lockt_res *res)
अणु
	पूर्णांक status;
	status = decode_op_hdr(xdr, OP_LOCKT);
	अगर (status == -NFS4ERR_DENIED)
		वापस decode_lock_denied(xdr, res->denied);
	वापस status;
पूर्ण

अटल पूर्णांक decode_locku(काष्ठा xdr_stream *xdr, काष्ठा nfs_locku_res *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_LOCKU);
	अगर (status != -EIO)
		nfs_increment_lock_seqid(status, res->seqid);
	अगर (status == 0)
		status = decode_lock_stateid(xdr, &res->stateid);
	वापस status;
पूर्ण

अटल पूर्णांक decode_release_lockowner(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_RELEASE_LOCKOWNER);
पूर्ण

अटल पूर्णांक decode_lookup(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_LOOKUP);
पूर्ण

अटल पूर्णांक decode_lookupp(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_LOOKUPP);
पूर्ण

/* This is too sick! */
अटल पूर्णांक decode_space_limit(काष्ठा xdr_stream *xdr,
		अचिन्हित दीर्घ *pagemod_limit)
अणु
	__be32 *p;
	uपूर्णांक32_t limit_type, nblocks, blocksize;
	u64 maxsize = 0;

	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(!p))
		वापस -EIO;
	limit_type = be32_to_cpup(p++);
	चयन (limit_type) अणु
	हाल NFS4_LIMIT_SIZE:
		xdr_decode_hyper(p, &maxsize);
		अवरोध;
	हाल NFS4_LIMIT_BLOCKS:
		nblocks = be32_to_cpup(p++);
		blocksize = be32_to_cpup(p);
		maxsize = (uपूर्णांक64_t)nblocks * (uपूर्णांक64_t)blocksize;
	पूर्ण
	maxsize >>= PAGE_SHIFT;
	*pagemod_limit = min_t(u64, maxsize, अच_दीर्घ_उच्च);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_rw_delegation(काष्ठा xdr_stream *xdr,
		uपूर्णांक32_t delegation_type,
		काष्ठा nfs_खोलोres *res)
अणु
	__be32 *p;
	पूर्णांक status;

	status = decode_delegation_stateid(xdr, &res->delegation);
	अगर (unlikely(status))
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	res->करो_recall = be32_to_cpup(p);

	चयन (delegation_type) अणु
	हाल NFS4_OPEN_DELEGATE_READ:
		res->delegation_type = FMODE_READ;
		अवरोध;
	हाल NFS4_OPEN_DELEGATE_WRITE:
		res->delegation_type = FMODE_WRITE|FMODE_READ;
		अगर (decode_space_limit(xdr, &res->pagemod_limit) < 0)
				वापस -EIO;
	पूर्ण
	वापस decode_ace(xdr, शून्य);
पूर्ण

अटल पूर्णांक decode_no_delegation(काष्ठा xdr_stream *xdr, काष्ठा nfs_खोलोres *res)
अणु
	__be32 *p;
	uपूर्णांक32_t why_no_delegation;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	why_no_delegation = be32_to_cpup(p);
	चयन (why_no_delegation) अणु
		हाल WND4_CONTENTION:
		हाल WND4_RESOURCE:
			xdr_अंतरभूत_decode(xdr, 4);
			/* Ignore क्रम now */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_delegation(काष्ठा xdr_stream *xdr, काष्ठा nfs_खोलोres *res)
अणु
	__be32 *p;
	uपूर्णांक32_t delegation_type;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	delegation_type = be32_to_cpup(p);
	res->delegation_type = 0;
	चयन (delegation_type) अणु
	हाल NFS4_OPEN_DELEGATE_NONE:
		वापस 0;
	हाल NFS4_OPEN_DELEGATE_READ:
	हाल NFS4_OPEN_DELEGATE_WRITE:
		वापस decode_rw_delegation(xdr, delegation_type, res);
	हाल NFS4_OPEN_DELEGATE_NONE_EXT:
		वापस decode_no_delegation(xdr, res);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक decode_खोलो(काष्ठा xdr_stream *xdr, काष्ठा nfs_खोलोres *res)
अणु
	__be32 *p;
	uपूर्णांक32_t savewords, bmlen, i;
	पूर्णांक status;

	अगर (!__decode_op_hdr(xdr, OP_OPEN, &status))
		वापस status;
	nfs_increment_खोलो_seqid(status, res->seqid);
	अगर (status)
		वापस status;
	status = decode_खोलो_stateid(xdr, &res->stateid);
	अगर (unlikely(status))
		वापस status;

	decode_change_info(xdr, &res->cinfo);

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	res->rflags = be32_to_cpup(p++);
	bmlen = be32_to_cpup(p);
	अगर (bmlen > 10)
		जाओ xdr_error;

	p = xdr_अंतरभूत_decode(xdr, bmlen << 2);
	अगर (unlikely(!p))
		वापस -EIO;
	savewords = min_t(uपूर्णांक32_t, bmlen, NFS4_BITMAP_SIZE);
	क्रम (i = 0; i < savewords; ++i)
		res->attrset[i] = be32_to_cpup(p++);
	क्रम (; i < NFS4_BITMAP_SIZE; i++)
		res->attrset[i] = 0;

	वापस decode_delegation(xdr, res);
xdr_error:
	dprपूर्णांकk("%s: Bitmap too large! Length = %u\n", __func__, bmlen);
	वापस -EIO;
पूर्ण

अटल पूर्णांक decode_खोलो_confirm(काष्ठा xdr_stream *xdr, काष्ठा nfs_खोलो_confirmres *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_OPEN_CONFIRM);
	अगर (status != -EIO)
		nfs_increment_खोलो_seqid(status, res->seqid);
	अगर (!status)
		status = decode_खोलो_stateid(xdr, &res->stateid);
	वापस status;
पूर्ण

अटल पूर्णांक decode_खोलो_करोwngrade(काष्ठा xdr_stream *xdr, काष्ठा nfs_बंदres *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_OPEN_DOWNGRADE);
	अगर (status != -EIO)
		nfs_increment_खोलो_seqid(status, res->seqid);
	अगर (!status)
		status = decode_खोलो_stateid(xdr, &res->stateid);
	वापस status;
पूर्ण

अटल पूर्णांक decode_putfh(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_PUTFH);
पूर्ण

अटल पूर्णांक decode_putrootfh(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_PUTROOTFH);
पूर्ण

अटल पूर्णांक decode_पढ़ो(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req,
		       काष्ठा nfs_pgio_res *res)
अणु
	__be32 *p;
	uपूर्णांक32_t count, eof, recvd;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_READ);
	अगर (status)
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	eof = be32_to_cpup(p++);
	count = be32_to_cpup(p);
	recvd = xdr_पढ़ो_pages(xdr, count);
	अगर (count > recvd) अणु
		dprपूर्णांकk("NFS: server cheating in read reply: "
				"count %u > recvd %u\n", count, recvd);
		count = recvd;
		eof = 0;
	पूर्ण
	res->eof = eof;
	res->count = count;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_सूची_पढ़ो(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req, काष्ठा nfs4_सूची_पढ़ो_res *सूची_पढ़ो)
अणु
	पूर्णांक		status;
	__be32		verf[2];

	status = decode_op_hdr(xdr, OP_READसूची);
	अगर (!status)
		status = decode_verअगरier(xdr, सूची_पढ़ो->verअगरier.data);
	अगर (unlikely(status))
		वापस status;
	स_नकल(verf, सूची_पढ़ो->verअगरier.data, माप(verf));
	dprपूर्णांकk("%s: verifier = %08x:%08x\n",
			__func__, verf[0], verf[1]);
	वापस xdr_पढ़ो_pages(xdr, xdr->buf->page_len);
पूर्ण

अटल पूर्णांक decode_पढ़ोlink(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req)
अणु
	काष्ठा xdr_buf *rcvbuf = &req->rq_rcv_buf;
	u32 len, recvd;
	__be32 *p;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_READLINK);
	अगर (status)
		वापस status;

	/* Convert length of symlink */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	len = be32_to_cpup(p);
	अगर (len >= rcvbuf->page_len || len <= 0) अणु
		dprपूर्णांकk("nfs: server returned giant symlink!\n");
		वापस -ENAMETOOLONG;
	पूर्ण
	recvd = xdr_पढ़ो_pages(xdr, len);
	अगर (recvd < len) अणु
		dprपूर्णांकk("NFS: server cheating in readlink reply: "
				"count %u > recvd %u\n", len, recvd);
		वापस -EIO;
	पूर्ण
	/*
	 * The XDR encode routine has set things up so that
	 * the link text will be copied directly पूर्णांकo the
	 * buffer.  We just have to करो overflow-checking,
	 * and null-terminate the text (the VFS expects
	 * null-termination).
	 */
	xdr_terminate_string(rcvbuf, len);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_हटाओ(काष्ठा xdr_stream *xdr, काष्ठा nfs4_change_info *cinfo)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_REMOVE);
	अगर (status)
		जाओ out;
	status = decode_change_info(xdr, cinfo);
out:
	वापस status;
पूर्ण

अटल पूर्णांक decode_नाम(काष्ठा xdr_stream *xdr, काष्ठा nfs4_change_info *old_cinfo,
	      काष्ठा nfs4_change_info *new_cinfo)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_RENAME);
	अगर (status)
		जाओ out;
	अगर ((status = decode_change_info(xdr, old_cinfo)))
		जाओ out;
	status = decode_change_info(xdr, new_cinfo);
out:
	वापस status;
पूर्ण

अटल पूर्णांक decode_renew(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_RENEW);
पूर्ण

अटल पूर्णांक
decode_restorefh(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_RESTOREFH);
पूर्ण

अटल पूर्णांक decode_getacl(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req,
			 काष्ठा nfs_getaclres *res)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t attrlen,
		 biपंचांगap[3] = अणु0पूर्ण;
	पूर्णांक status;

	res->acl_len = 0;
	अगर ((status = decode_op_hdr(xdr, OP_GETATTR)) != 0)
		जाओ out;

	xdr_enter_page(xdr, xdr->buf->page_len);

	अगर ((status = decode_attr_biपंचांगap(xdr, biपंचांगap)) != 0)
		जाओ out;
	अगर ((status = decode_attr_length(xdr, &attrlen, &savep)) != 0)
		जाओ out;

	अगर (unlikely(biपंचांगap[0] & (FATTR4_WORD0_ACL - 1U)))
		वापस -EIO;
	अगर (likely(biपंचांगap[0] & FATTR4_WORD0_ACL)) अणु

		/* The biपंचांगap (xdr len + biपंचांगaps) and the attr xdr len words
		 * are stored with the acl data to handle the problem of
		 * variable length biपंचांगaps.*/
		res->acl_data_offset = xdr_page_pos(xdr);
		res->acl_len = attrlen;

		/* Check क्रम receive buffer overflow */
		अगर (res->acl_len > xdr_stream_reमुख्यing(xdr) ||
		    res->acl_len + res->acl_data_offset > xdr->buf->page_len) अणु
			res->acl_flags |= NFS4_ACL_TRUNC;
			dprपूर्णांकk("NFS: acl reply: attrlen %u > page_len %zu\n",
				attrlen, xdr_stream_reमुख्यing(xdr));
		पूर्ण
	पूर्ण अन्यथा
		status = -EOPNOTSUPP;

out:
	वापस status;
पूर्ण

अटल पूर्णांक
decode_savefh(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_SAVEFH);
पूर्ण

अटल पूर्णांक decode_setattr(काष्ठा xdr_stream *xdr)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_SETATTR);
	अगर (status)
		वापस status;
	अगर (decode_biपंचांगap4(xdr, शून्य, 0) >= 0)
		वापस 0;
	वापस -EIO;
पूर्ण

अटल पूर्णांक decode_setclientid(काष्ठा xdr_stream *xdr, काष्ठा nfs4_setclientid_res *res)
अणु
	__be32 *p;
	uपूर्णांक32_t opnum;
	पूर्णांक32_t nfserr;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	opnum = be32_to_cpup(p++);
	अगर (opnum != OP_SETCLIENTID) अणु
		dprपूर्णांकk("nfs: decode_setclientid: Server returned operation"
			" %d\n", opnum);
		वापस -EIO;
	पूर्ण
	nfserr = be32_to_cpup(p);
	अगर (nfserr == NFS_OK) अणु
		p = xdr_अंतरभूत_decode(xdr, 8 + NFS4_VERIFIER_SIZE);
		अगर (unlikely(!p))
			वापस -EIO;
		p = xdr_decode_hyper(p, &res->clientid);
		स_नकल(res->confirm.data, p, NFS4_VERIFIER_SIZE);
	पूर्ण अन्यथा अगर (nfserr == NFSERR_CLID_INUSE) अणु
		uपूर्णांक32_t len;

		/* skip netid string */
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		len = be32_to_cpup(p);
		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EIO;

		/* skip uaddr string */
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		len = be32_to_cpup(p);
		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EIO;
		वापस -NFSERR_CLID_INUSE;
	पूर्ण अन्यथा
		वापस nfs4_stat_to_त्रुटि_सं(nfserr);

	वापस 0;
पूर्ण

अटल पूर्णांक decode_setclientid_confirm(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_SETCLIENTID_CONFIRM);
पूर्ण

अटल पूर्णांक decode_ग_लिखो(काष्ठा xdr_stream *xdr, काष्ठा nfs_pgio_res *res)
अणु
	__be32 *p;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_WRITE);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	res->count = be32_to_cpup(p++);
	res->verf->committed = be32_to_cpup(p++);
	वापस decode_ग_लिखो_verअगरier(xdr, &res->verf->verअगरier);
पूर्ण

अटल पूर्णांक decode_delegवापस(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_DELEGRETURN);
पूर्ण

अटल पूर्णांक decode_secinfo_gss(काष्ठा xdr_stream *xdr,
			      काष्ठा nfs4_secinfo4 *flavor)
अणु
	u32 oid_len;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	oid_len = be32_to_cpup(p);
	अगर (oid_len > GSS_OID_MAX_LEN)
		वापस -EINVAL;

	p = xdr_अंतरभूत_decode(xdr, oid_len);
	अगर (unlikely(!p))
		वापस -EIO;
	स_नकल(flavor->flavor_info.oid.data, p, oid_len);
	flavor->flavor_info.oid.len = oid_len;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	flavor->flavor_info.qop = be32_to_cpup(p++);
	flavor->flavor_info.service = be32_to_cpup(p);

	वापस 0;
पूर्ण

अटल पूर्णांक decode_secinfo_common(काष्ठा xdr_stream *xdr, काष्ठा nfs4_secinfo_res *res)
अणु
	काष्ठा nfs4_secinfo4 *sec_flavor;
	अचिन्हित पूर्णांक i, num_flavors;
	पूर्णांक status;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;

	res->flavors->num_flavors = 0;
	num_flavors = be32_to_cpup(p);

	क्रम (i = 0; i < num_flavors; i++) अणु
		sec_flavor = &res->flavors->flavors[i];
		अगर ((अक्षर *)&sec_flavor[1] - (अक्षर *)res->flavors > PAGE_SIZE)
			अवरोध;

		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;
		sec_flavor->flavor = be32_to_cpup(p);

		अगर (sec_flavor->flavor == RPC_AUTH_GSS) अणु
			status = decode_secinfo_gss(xdr, sec_flavor);
			अगर (status)
				जाओ out;
		पूर्ण
		res->flavors->num_flavors++;
	पूर्ण

	status = 0;
out:
	वापस status;
पूर्ण

अटल पूर्णांक decode_secinfo(काष्ठा xdr_stream *xdr, काष्ठा nfs4_secinfo_res *res)
अणु
	पूर्णांक status = decode_op_hdr(xdr, OP_SECINFO);
	अगर (status)
		वापस status;
	वापस decode_secinfo_common(xdr, res);
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
अटल पूर्णांक decode_secinfo_no_name(काष्ठा xdr_stream *xdr, काष्ठा nfs4_secinfo_res *res)
अणु
	पूर्णांक status = decode_op_hdr(xdr, OP_SECINFO_NO_NAME);
	अगर (status)
		वापस status;
	वापस decode_secinfo_common(xdr, res);
पूर्ण

अटल पूर्णांक decode_op_map(काष्ठा xdr_stream *xdr, काष्ठा nfs4_op_map *op_map)
अणु
	__be32 *p;
	uपूर्णांक32_t biपंचांगap_words;
	अचिन्हित पूर्णांक i;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (!p)
		वापस -EIO;
	biपंचांगap_words = be32_to_cpup(p++);
	अगर (biपंचांगap_words > NFS4_OP_MAP_NUM_WORDS)
		वापस -EIO;
	p = xdr_अंतरभूत_decode(xdr, 4 * biपंचांगap_words);
	क्रम (i = 0; i < biपंचांगap_words; i++)
		op_map->u.words[i] = be32_to_cpup(p++);

	वापस 0;
पूर्ण

अटल पूर्णांक decode_exchange_id(काष्ठा xdr_stream *xdr,
			      काष्ठा nfs41_exchange_id_res *res)
अणु
	__be32 *p;
	uपूर्णांक32_t dummy;
	अक्षर *dummy_str;
	पूर्णांक status;
	uपूर्णांक32_t impl_id_count;

	status = decode_op_hdr(xdr, OP_EXCHANGE_ID);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	xdr_decode_hyper(p, &res->clientid);
	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(!p))
		वापस -EIO;
	res->seqid = be32_to_cpup(p++);
	res->flags = be32_to_cpup(p++);

	res->state_protect.how = be32_to_cpup(p);
	चयन (res->state_protect.how) अणु
	हाल SP4_NONE:
		अवरोध;
	हाल SP4_MACH_CRED:
		status = decode_op_map(xdr, &res->state_protect.enक्रमce);
		अगर (status)
			वापस status;
		status = decode_op_map(xdr, &res->state_protect.allow);
		अगर (status)
			वापस status;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण

	/* server_owner4.so_minor_id */
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	p = xdr_decode_hyper(p, &res->server_owner->minor_id);

	/* server_owner4.so_major_id */
	status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
	अगर (unlikely(status))
		वापस status;
	स_नकल(res->server_owner->major_id, dummy_str, dummy);
	res->server_owner->major_id_sz = dummy;

	/* server_scope4 */
	status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
	अगर (unlikely(status))
		वापस status;
	स_नकल(res->server_scope->server_scope, dummy_str, dummy);
	res->server_scope->server_scope_sz = dummy;

	/* Implementation Id */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	impl_id_count = be32_to_cpup(p++);

	अगर (impl_id_count) अणु
		/* nii_करोमुख्य */
		status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
		अगर (unlikely(status))
			वापस status;
		स_नकल(res->impl_id->करोमुख्य, dummy_str, dummy);

		/* nii_name */
		status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
		अगर (unlikely(status))
			वापस status;
		स_नकल(res->impl_id->name, dummy_str, dummy);

		/* nii_date */
		p = xdr_अंतरभूत_decode(xdr, 12);
		अगर (unlikely(!p))
			वापस -EIO;
		p = xdr_decode_hyper(p, &res->impl_id->date.seconds);
		res->impl_id->date.nseconds = be32_to_cpup(p);

		/* अगर there's more than one entry, ignore the rest */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_chan_attrs(काष्ठा xdr_stream *xdr,
			     काष्ठा nfs4_channel_attrs *attrs)
अणु
	__be32 *p;
	u32 nr_attrs, val;

	p = xdr_अंतरभूत_decode(xdr, 28);
	अगर (unlikely(!p))
		वापस -EIO;
	val = be32_to_cpup(p++);	/* headerpadsz */
	अगर (val)
		वापस -EINVAL;		/* no support क्रम header padding yet */
	attrs->max_rqst_sz = be32_to_cpup(p++);
	attrs->max_resp_sz = be32_to_cpup(p++);
	attrs->max_resp_sz_cached = be32_to_cpup(p++);
	attrs->max_ops = be32_to_cpup(p++);
	attrs->max_reqs = be32_to_cpup(p++);
	nr_attrs = be32_to_cpup(p);
	अगर (unlikely(nr_attrs > 1)) अणु
		prपूर्णांकk(KERN_WARNING "NFS: %s: Invalid rdma channel attrs "
			"count %u\n", __func__, nr_attrs);
		वापस -EINVAL;
	पूर्ण
	अगर (nr_attrs == 1) अणु
		p = xdr_अंतरभूत_decode(xdr, 4); /* skip rdma_attrs */
		अगर (unlikely(!p))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_sessionid(काष्ठा xdr_stream *xdr, काष्ठा nfs4_sessionid *sid)
अणु
	वापस decode_opaque_fixed(xdr, sid->data, NFS4_MAX_SESSIONID_LEN);
पूर्ण

अटल पूर्णांक decode_bind_conn_to_session(काष्ठा xdr_stream *xdr,
				काष्ठा nfs41_bind_conn_to_session_res *res)
अणु
	__be32 *p;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_BIND_CONN_TO_SESSION);
	अगर (!status)
		status = decode_sessionid(xdr, &res->sessionid);
	अगर (unlikely(status))
		वापस status;

	/* dir flags, rdma mode bool */
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;

	res->dir = be32_to_cpup(p++);
	अगर (res->dir == 0 || res->dir > NFS4_CDFS4_BOTH)
		वापस -EIO;
	अगर (be32_to_cpup(p) == 0)
		res->use_conn_in_rdma_mode = false;
	अन्यथा
		res->use_conn_in_rdma_mode = true;

	वापस 0;
पूर्ण

अटल पूर्णांक decode_create_session(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs41_create_session_res *res)
अणु
	__be32 *p;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_CREATE_SESSION);
	अगर (!status)
		status = decode_sessionid(xdr, &res->sessionid);
	अगर (unlikely(status))
		वापस status;

	/* seqid, flags */
	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	res->seqid = be32_to_cpup(p++);
	res->flags = be32_to_cpup(p);

	/* Channel attributes */
	status = decode_chan_attrs(xdr, &res->fc_attrs);
	अगर (!status)
		status = decode_chan_attrs(xdr, &res->bc_attrs);
	वापस status;
पूर्ण

अटल पूर्णांक decode_destroy_session(काष्ठा xdr_stream *xdr, व्योम *dummy)
अणु
	वापस decode_op_hdr(xdr, OP_DESTROY_SESSION);
पूर्ण

अटल पूर्णांक decode_destroy_clientid(काष्ठा xdr_stream *xdr, व्योम *dummy)
अणु
	वापस decode_op_hdr(xdr, OP_DESTROY_CLIENTID);
पूर्ण

अटल पूर्णांक decode_reclaim_complete(काष्ठा xdr_stream *xdr, व्योम *dummy)
अणु
	वापस decode_op_hdr(xdr, OP_RECLAIM_COMPLETE);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल पूर्णांक decode_sequence(काष्ठा xdr_stream *xdr,
			   काष्ठा nfs4_sequence_res *res,
			   काष्ठा rpc_rqst *rqstp)
अणु
#अगर defined(CONFIG_NFS_V4_1)
	काष्ठा nfs4_session *session;
	काष्ठा nfs4_sessionid id;
	u32 dummy;
	पूर्णांक status;
	__be32 *p;

	अगर (res->sr_slot == शून्य)
		वापस 0;
	अगर (!res->sr_slot->table->session)
		वापस 0;

	status = decode_op_hdr(xdr, OP_SEQUENCE);
	अगर (!status)
		status = decode_sessionid(xdr, &id);
	अगर (unlikely(status))
		जाओ out_err;

	/*
	 * If the server वापसs dअगरferent values क्रम sessionID, slotID or
	 * sequence number, the server is looney tunes.
	 */
	status = -EREMOTEIO;
	session = res->sr_slot->table->session;

	अगर (स_भेद(id.data, session->sess_id.data,
		   NFS4_MAX_SESSIONID_LEN)) अणु
		dprपूर्णांकk("%s Invalid session id\n", __func__);
		जाओ out_err;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 20);
	अगर (unlikely(!p))
		जाओ out_overflow;

	/* seqid */
	dummy = be32_to_cpup(p++);
	अगर (dummy != res->sr_slot->seq_nr) अणु
		dprपूर्णांकk("%s Invalid sequence number\n", __func__);
		जाओ out_err;
	पूर्ण
	/* slot id */
	dummy = be32_to_cpup(p++);
	अगर (dummy != res->sr_slot->slot_nr) अणु
		dprपूर्णांकk("%s Invalid slot id\n", __func__);
		जाओ out_err;
	पूर्ण
	/* highest slot id */
	res->sr_highest_slotid = be32_to_cpup(p++);
	/* target highest slot id */
	res->sr_target_highest_slotid = be32_to_cpup(p++);
	/* result flags */
	res->sr_status_flags = be32_to_cpup(p);
	status = 0;
out_err:
	res->sr_status = status;
	वापस status;
out_overflow:
	status = -EIO;
	जाओ out_err;
#अन्यथा  /* CONFIG_NFS_V4_1 */
	वापस 0;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
अटल पूर्णांक decode_layout_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_LAYOUT_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल पूर्णांक decode_getdeviceinfo(काष्ठा xdr_stream *xdr,
				काष्ठा nfs4_getdeviceinfo_res *res)
अणु
	काष्ठा pnfs_device *pdev = res->pdev;
	__be32 *p;
	uपूर्णांक32_t len, type;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_GETDEVICEINFO);
	अगर (status) अणु
		अगर (status == -ETOOSMALL) अणु
			p = xdr_अंतरभूत_decode(xdr, 4);
			अगर (unlikely(!p))
				वापस -EIO;
			pdev->mincount = be32_to_cpup(p);
			dprपूर्णांकk("%s: Min count too small. mincnt = %u\n",
				__func__, pdev->mincount);
		पूर्ण
		वापस status;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;
	type = be32_to_cpup(p++);
	अगर (type != pdev->layout_type) अणु
		dprपूर्णांकk("%s: layout mismatch req: %u pdev: %u\n",
			__func__, pdev->layout_type, type);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Get the length of the opaque device_addr4. xdr_पढ़ो_pages places
	 * the opaque device_addr4 in the xdr_buf->pages (pnfs_device->pages)
	 * and places the reमुख्यing xdr data in xdr_buf->tail
	 */
	pdev->mincount = be32_to_cpup(p);
	अगर (xdr_पढ़ो_pages(xdr, pdev->mincount) != pdev->mincount)
		वापस -EIO;

	/* Parse notअगरication biपंचांगap, verअगरying that it is zero. */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	len = be32_to_cpup(p);
	अगर (len) अणु
		uपूर्णांक32_t i;

		p = xdr_अंतरभूत_decode(xdr, 4 * len);
		अगर (unlikely(!p))
			वापस -EIO;

		res->notअगरication = be32_to_cpup(p++);
		क्रम (i = 1; i < len; i++) अणु
			अगर (be32_to_cpup(p++)) अणु
				dprपूर्णांकk("%s: unsupported notification\n",
					__func__);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_layoutget(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req,
			    काष्ठा nfs4_layoutget_res *res)
अणु
	__be32 *p;
	पूर्णांक status;
	u32 layout_count;
	u32 recvd;

	status = decode_op_hdr(xdr, OP_LAYOUTGET);
	अगर (status)
		जाओ out;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		जाओ out_overflow;
	res->वापस_on_बंद = be32_to_cpup(p);
	decode_layout_stateid(xdr, &res->stateid);
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		जाओ out_overflow;
	layout_count = be32_to_cpup(p);
	अगर (!layout_count) अणु
		dprपूर्णांकk("%s: server responded with empty layout array\n",
			__func__);
		status = -EINVAL;
		जाओ out;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 28);
	अगर (unlikely(!p))
		जाओ out_overflow;
	p = xdr_decode_hyper(p, &res->range.offset);
	p = xdr_decode_hyper(p, &res->range.length);
	res->range.iomode = be32_to_cpup(p++);
	res->type = be32_to_cpup(p++);
	res->layoutp->len = be32_to_cpup(p);

	dprपूर्णांकk("%s roff:%lu rlen:%lu riomode:%d, lo_type:0x%x, lo.len:%d\n",
		__func__,
		(अचिन्हित दीर्घ)res->range.offset,
		(अचिन्हित दीर्घ)res->range.length,
		res->range.iomode,
		res->type,
		res->layoutp->len);

	recvd = xdr_पढ़ो_pages(xdr, res->layoutp->len);
	अगर (res->layoutp->len > recvd) अणु
		dprपूर्णांकk("NFS: server cheating in layoutget reply: "
				"layout len %u > recvd %u\n",
				res->layoutp->len, recvd);
		status = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (layout_count > 1) अणु
		/* We only handle a length one array at the moment.  Any
		 * further entries are just ignored.  Note that this means
		 * the client may see a response that is less than the
		 * minimum it requested.
		 */
		dprपूर्णांकk("%s: server responded with %d layouts, dropping tail\n",
			__func__, layout_count);
	पूर्ण

out:
	res->status = status;
	वापस status;
out_overflow:
	status = -EIO;
	जाओ out;
पूर्ण

अटल पूर्णांक decode_layoutवापस(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs4_layoutवापस_res *res)
अणु
	__be32 *p;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_LAYOUTRETURN);
	अगर (status)
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	res->lrs_present = be32_to_cpup(p);
	अगर (res->lrs_present)
		status = decode_layout_stateid(xdr, &res->stateid);
	अन्यथा
		nfs4_stateid_copy(&res->stateid, &invalid_stateid);
	वापस status;
पूर्ण

अटल पूर्णांक decode_layoutcommit(काष्ठा xdr_stream *xdr,
			       काष्ठा rpc_rqst *req,
			       काष्ठा nfs4_layoutcommit_res *res)
अणु
	__be32 *p;
	__u32 sizechanged;
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_LAYOUTCOMMIT);
	res->status = status;
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	sizechanged = be32_to_cpup(p);

	अगर (sizechanged) अणु
		/* throw away new size */
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_test_stateid(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs41_test_stateid_res *res)
अणु
	__be32 *p;
	पूर्णांक status;
	पूर्णांक num_res;

	status = decode_op_hdr(xdr, OP_TEST_STATEID);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	num_res = be32_to_cpup(p++);
	अगर (num_res != 1)
		वापस -EIO;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	res->status = be32_to_cpup(p++);

	वापस status;
पूर्ण

अटल पूर्णांक decode_मुक्त_stateid(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs41_मुक्त_stateid_res *res)
अणु
	res->status = decode_op_hdr(xdr, OP_FREE_STATEID);
	वापस res->status;
पूर्ण
#अन्यथा
अटल अंतरभूत
पूर्णांक decode_layoutवापस(काष्ठा xdr_stream *xdr,
			       काष्ठा nfs4_layoutवापस_res *res)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक decode_layoutget(काष्ठा xdr_stream *xdr, काष्ठा rpc_rqst *req,
			    काष्ठा nfs4_layoutget_res *res)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

/*
 * END OF "GENERIC" DECODE ROUTINES.
 */

/*
 * Decode OPEN_DOWNGRADE response
 */
अटल पूर्णांक nfs4_xdr_dec_खोलो_करोwngrade(काष्ठा rpc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr,
				       व्योम *data)
अणु
	काष्ठा nfs_बंदres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	अगर (res->lr_res) अणु
		status = decode_layoutवापस(xdr, res->lr_res);
		res->lr_ret = status;
		अगर (status)
			जाओ out;
	पूर्ण
	status = decode_खोलो_करोwngrade(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode ACCESS response
 */
अटल पूर्णांक nfs4_xdr_dec_access(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs4_accessres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status != 0)
		जाओ out;
	status = decode_access(xdr, &res->supported, &res->access);
	अगर (status != 0)
		जाओ out;
	अगर (res->fattr)
		decode_getfattr(xdr, res->fattr, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode LOOKUP response
 */
अटल पूर्णांक nfs4_xdr_dec_lookup(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs4_lookup_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_lookup(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, res->fh);
	अगर (status)
		जाओ out;
	status = decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode LOOKUPP response
 */
अटल पूर्णांक nfs4_xdr_dec_lookupp(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		व्योम *data)
अणु
	काष्ठा nfs4_lookupp_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_lookupp(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, res->fh);
	अगर (status)
		जाओ out;
	status = decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode LOOKUP_ROOT response
 */
अटल पूर्णांक nfs4_xdr_dec_lookup_root(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs4_lookup_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putrootfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, res->fh);
	अगर (status == 0)
		status = decode_getfattr_label(xdr, res->fattr,
						res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode REMOVE response
 */
अटल पूर्णांक nfs4_xdr_dec_हटाओ(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs_हटाओres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_हटाओ(xdr, &res->cinfo);
out:
	वापस status;
पूर्ण

/*
 * Decode RENAME response
 */
अटल पूर्णांक nfs4_xdr_dec_नाम(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs_नामres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_savefh(xdr);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_नाम(xdr, &res->old_cinfo, &res->new_cinfo);
out:
	वापस status;
पूर्ण

/*
 * Decode LINK response
 */
अटल पूर्णांक nfs4_xdr_dec_link(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs4_link_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_savefh(xdr);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_link(xdr, &res->cinfo);
	अगर (status)
		जाओ out;
	/*
	 * Note order: OP_LINK leaves the directory as the current
	 *             filehandle.
	 */
	status = decode_restorefh(xdr);
	अगर (status)
		जाओ out;
	decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode CREATE response
 */
अटल पूर्णांक nfs4_xdr_dec_create(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs4_create_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_create(xdr, &res->dir_cinfo);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, res->fh);
	अगर (status)
		जाओ out;
	decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode SYMLINK response
 */
अटल पूर्णांक nfs4_xdr_dec_symlink(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
				व्योम *res)
अणु
	वापस nfs4_xdr_dec_create(rqstp, xdr, res);
पूर्ण

/*
 * Decode GETATTR response
 */
अटल पूर्णांक nfs4_xdr_dec_getattr(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nfs4_getattr_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Encode an SETACL request
 */
अटल व्योम nfs4_xdr_enc_setacl(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_setaclargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_setacl(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Decode SETACL response
 */
अटल पूर्णांक
nfs4_xdr_dec_setacl(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		    व्योम *data)
अणु
	काष्ठा nfs_setaclres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_setattr(xdr);
out:
	वापस status;
पूर्ण

/*
 * Decode GETACL response
 */
अटल पूर्णांक
nfs4_xdr_dec_getacl(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		    व्योम *data)
अणु
	काष्ठा nfs_getaclres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	अगर (res->acl_scratch != शून्य)
		xdr_set_scratch_page(xdr, res->acl_scratch);
	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_getacl(xdr, rqstp, res);

out:
	वापस status;
पूर्ण

/*
 * Decode CLOSE response
 */
अटल पूर्णांक nfs4_xdr_dec_बंद(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			      व्योम *data)
अणु
	काष्ठा nfs_बंदres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	अगर (res->lr_res) अणु
		status = decode_layoutवापस(xdr, res->lr_res);
		res->lr_ret = status;
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (res->fattr != शून्य) अणु
		status = decode_getfattr(xdr, res->fattr, res->server);
		अगर (status != 0)
			जाओ out;
	पूर्ण
	status = decode_बंद(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode OPEN response
 */
अटल पूर्णांक nfs4_xdr_dec_खोलो(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs_खोलोres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_खोलो(xdr, res);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, &res->fh);
	अगर (status)
		जाओ out;
	अगर (res->access_request)
		decode_access(xdr, &res->access_supported, &res->access_result);
	decode_getfattr_label(xdr, res->f_attr, res->f_label, res->server);
	अगर (res->lg_res)
		decode_layoutget(xdr, rqstp, res->lg_res);
out:
	वापस status;
पूर्ण

/*
 * Decode OPEN_CONFIRM response
 */
अटल पूर्णांक nfs4_xdr_dec_खोलो_confirm(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs_खोलो_confirmres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_खोलो_confirm(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode OPEN response
 */
अटल पूर्णांक nfs4_xdr_dec_खोलो_noattr(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs_खोलोres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_खोलो(xdr, res);
	अगर (status)
		जाओ out;
	अगर (res->access_request)
		decode_access(xdr, &res->access_supported, &res->access_result);
	decode_getfattr(xdr, res->f_attr, res->server);
	अगर (res->lg_res)
		decode_layoutget(xdr, rqstp, res->lg_res);
out:
	वापस status;
पूर्ण

/*
 * Decode SETATTR response
 */
अटल पूर्णांक nfs4_xdr_dec_setattr(काष्ठा rpc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nfs_setattrres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_setattr(xdr);
	अगर (status)
		जाओ out;
	decode_getfattr_label(xdr, res->fattr, res->label, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode LOCK response
 */
अटल पूर्णांक nfs4_xdr_dec_lock(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs_lock_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_lock(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LOCKT response
 */
अटल पूर्णांक nfs4_xdr_dec_lockt(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			      व्योम *data)
अणु
	काष्ठा nfs_lockt_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_lockt(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LOCKU response
 */
अटल पूर्णांक nfs4_xdr_dec_locku(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			      व्योम *data)
अणु
	काष्ठा nfs_locku_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_locku(xdr, res);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_release_lockowner(काष्ठा rpc_rqst *rqstp,
					  काष्ठा xdr_stream *xdr, व्योम *dummy)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_release_lockowner(xdr);
	वापस status;
पूर्ण

/*
 * Decode READLINK response
 */
अटल पूर्णांक nfs4_xdr_dec_पढ़ोlink(काष्ठा rpc_rqst *rqstp,
				 काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs4_पढ़ोlink_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_पढ़ोlink(xdr, rqstp);
out:
	वापस status;
पूर्ण

/*
 * Decode READसूची response
 */
अटल पूर्णांक nfs4_xdr_dec_सूची_पढ़ो(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nfs4_सूची_पढ़ो_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_सूची_पढ़ो(xdr, rqstp, res);
out:
	वापस status;
पूर्ण

/*
 * Decode Read response
 */
अटल पूर्णांक nfs4_xdr_dec_पढ़ो(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs_pgio_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	res->op_status = hdr.status;
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_पढ़ो(xdr, rqstp, res);
	अगर (!status)
		status = res->count;
out:
	वापस status;
पूर्ण

/*
 * Decode WRITE response
 */
अटल पूर्णांक nfs4_xdr_dec_ग_लिखो(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			      व्योम *data)
अणु
	काष्ठा nfs_pgio_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	res->op_status = hdr.status;
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_ग_लिखो(xdr, res);
	अगर (status)
		जाओ out;
	अगर (res->fattr)
		decode_getfattr(xdr, res->fattr, res->server);
	अगर (!status)
		status = res->count;
out:
	वापस status;
पूर्ण

/*
 * Decode COMMIT response
 */
अटल पूर्णांक nfs4_xdr_dec_commit(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs_commitres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	res->op_status = hdr.status;
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_commit(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode FSINFO response
 */
अटल पूर्णांक nfs4_xdr_dec_fsinfo(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs4_fsinfo_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, &res->seq_res, req);
	अगर (!status)
		status = decode_putfh(xdr);
	अगर (!status)
		status = decode_fsinfo(xdr, res->fsinfo);
	वापस status;
पूर्ण

/*
 * Decode PATHCONF response
 */
अटल पूर्णांक nfs4_xdr_dec_pathconf(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs4_pathconf_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, &res->seq_res, req);
	अगर (!status)
		status = decode_putfh(xdr);
	अगर (!status)
		status = decode_pathconf(xdr, res->pathconf);
	वापस status;
पूर्ण

/*
 * Decode STATFS response
 */
अटल पूर्णांक nfs4_xdr_dec_statfs(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			       व्योम *data)
अणु
	काष्ठा nfs4_statfs_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, &res->seq_res, req);
	अगर (!status)
		status = decode_putfh(xdr);
	अगर (!status)
		status = decode_statfs(xdr, res->fsstat);
	वापस status;
पूर्ण

/*
 * Decode GETATTR_BITMAP response
 */
अटल पूर्णांक nfs4_xdr_dec_server_caps(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs4_server_caps_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, req);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_server_caps(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode RENEW response
 */
अटल पूर्णांक nfs4_xdr_dec_renew(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			      व्योम *__unused)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_renew(xdr);
	वापस status;
पूर्ण

/*
 * Decode SETCLIENTID response
 */
अटल पूर्णांक nfs4_xdr_dec_setclientid(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs4_setclientid_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_setclientid(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode SETCLIENTID_CONFIRM response
 */
अटल पूर्णांक nfs4_xdr_dec_setclientid_confirm(काष्ठा rpc_rqst *req,
					    काष्ठा xdr_stream *xdr,
					    व्योम *data)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_setclientid_confirm(xdr);
	वापस status;
पूर्ण

/*
 * Decode DELEGRETURN response
 */
अटल पूर्णांक nfs4_xdr_dec_delegवापस(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs4_delegवापसres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status != 0)
		जाओ out;
	अगर (res->lr_res) अणु
		status = decode_layoutवापस(xdr, res->lr_res);
		res->lr_ret = status;
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (res->fattr) अणु
		status = decode_getfattr(xdr, res->fattr, res->server);
		अगर (status != 0)
			जाओ out;
	पूर्ण
	status = decode_delegवापस(xdr);
out:
	वापस status;
पूर्ण

/*
 * Decode FS_LOCATIONS response
 */
अटल पूर्णांक nfs4_xdr_dec_fs_locations(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs4_fs_locations_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, req);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	अगर (res->migration) अणु
		xdr_enter_page(xdr, PAGE_SIZE);
		status = decode_getfattr_generic(xdr,
					&res->fs_locations->fattr,
					 शून्य, res->fs_locations,
					 शून्य, res->fs_locations->server);
		अगर (status)
			जाओ out;
		अगर (res->renew)
			status = decode_renew(xdr);
	पूर्ण अन्यथा अणु
		status = decode_lookup(xdr);
		अगर (status)
			जाओ out;
		xdr_enter_page(xdr, PAGE_SIZE);
		status = decode_getfattr_generic(xdr,
					&res->fs_locations->fattr,
					 शून्य, res->fs_locations,
					 शून्य, res->fs_locations->server);
	पूर्ण
out:
	वापस status;
पूर्ण

/*
 * Decode SECINFO response
 */
अटल पूर्णांक nfs4_xdr_dec_secinfo(काष्ठा rpc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nfs4_secinfo_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_secinfo(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode FSID_PRESENT response
 */
अटल पूर्णांक nfs4_xdr_dec_fsid_present(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs4_fsid_present_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfh(xdr, res->fh);
	अगर (status)
		जाओ out;
	अगर (res->renew)
		status = decode_renew(xdr);
out:
	वापस status;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
/*
 * Decode BIND_CONN_TO_SESSION response
 */
अटल पूर्णांक nfs4_xdr_dec_bind_conn_to_session(काष्ठा rpc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_bind_conn_to_session(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode EXCHANGE_ID response
 */
अटल पूर्णांक nfs4_xdr_dec_exchange_id(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_exchange_id(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode CREATE_SESSION response
 */
अटल पूर्णांक nfs4_xdr_dec_create_session(काष्ठा rpc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr,
				       व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_create_session(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode DESTROY_SESSION response
 */
अटल पूर्णांक nfs4_xdr_dec_destroy_session(काष्ठा rpc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_destroy_session(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode DESTROY_CLIENTID response
 */
अटल पूर्णांक nfs4_xdr_dec_destroy_clientid(काष्ठा rpc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_destroy_clientid(xdr, res);
	वापस status;
पूर्ण

/*
 * Decode SEQUENCE response
 */
अटल पूर्णांक nfs4_xdr_dec_sequence(काष्ठा rpc_rqst *rqstp,
				 काष्ठा xdr_stream *xdr,
				 व्योम *res)
अणु
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, res, rqstp);
	वापस status;
पूर्ण

#पूर्ण_अगर

/*
 * Decode GET_LEASE_TIME response
 */
अटल पूर्णांक nfs4_xdr_dec_get_lease_समय(काष्ठा rpc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr,
				       व्योम *data)
अणु
	काष्ठा nfs4_get_lease_समय_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, &res->lr_seq_res, rqstp);
	अगर (!status)
		status = decode_putrootfh(xdr);
	अगर (!status)
		status = decode_fsinfo(xdr, res->lr_fsinfo);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1

/*
 * Decode RECLAIM_COMPLETE response
 */
अटल पूर्णांक nfs4_xdr_dec_reclaim_complete(काष्ठा rpc_rqst *rqstp,
					 काष्ठा xdr_stream *xdr,
					 व्योम *data)
अणु
	काष्ठा nfs41_reclaim_complete_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (!status)
		status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (!status)
		status = decode_reclaim_complete(xdr, शून्य);
	वापस status;
पूर्ण

/*
 * Decode GETDEVINFO response
 */
अटल पूर्णांक nfs4_xdr_dec_getdeviceinfo(काष्ठा rpc_rqst *rqstp,
				      काष्ठा xdr_stream *xdr,
				      व्योम *data)
अणु
	काष्ठा nfs4_getdeviceinfo_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status != 0)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status != 0)
		जाओ out;
	status = decode_getdeviceinfo(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LAYOUTGET response
 */
अटल पूर्णांक nfs4_xdr_dec_layoutget(काष्ठा rpc_rqst *rqstp,
				  काष्ठा xdr_stream *xdr,
				  व्योम *data)
अणु
	काष्ठा nfs4_layoutget_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_layoutget(xdr, rqstp, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LAYOUTRETURN response
 */
अटल पूर्णांक nfs4_xdr_dec_layoutवापस(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs4_layoutवापस_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_layoutवापस(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LAYOUTCOMMIT response
 */
अटल पूर्णांक nfs4_xdr_dec_layoutcommit(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs4_layoutcommit_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_layoutcommit(xdr, rqstp, res);
	अगर (status)
		जाओ out;
	decode_getfattr(xdr, res->fattr, res->server);
out:
	वापस status;
पूर्ण

/*
 * Decode SECINFO_NO_NAME response
 */
अटल पूर्णांक nfs4_xdr_dec_secinfo_no_name(काष्ठा rpc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *data)
अणु
	काष्ठा nfs4_secinfo_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putrootfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_secinfo_no_name(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode TEST_STATEID response
 */
अटल पूर्णांक nfs4_xdr_dec_test_stateid(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs41_test_stateid_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_test_stateid(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode FREE_STATEID response
 */
अटल पूर्णांक nfs4_xdr_dec_मुक्त_stateid(काष्ठा rpc_rqst *rqstp,
				     काष्ठा xdr_stream *xdr,
				     व्योम *data)
अणु
	काष्ठा nfs41_मुक्त_stateid_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_मुक्त_stateid(xdr, res);
out:
	वापस status;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

/**
 * nfs4_decode_dirent - Decode a single NFSv4 directory entry stored in
 *                      the local page cache.
 * @xdr: XDR stream where entry resides
 * @entry: buffer to fill in with entry data
 * @plus: boolean indicating whether this should be a सूची_पढ़ोplus entry
 *
 * Returns zero अगर successful, otherwise a negative त्रुटि_सं value is
 * वापसed.
 *
 * This function is not invoked during READसूची reply decoding, but
 * rather whenever an application invokes the getdents(2) प्रणाली call
 * on a directory alपढ़ोy in our cache.
 */
पूर्णांक nfs4_decode_dirent(काष्ठा xdr_stream *xdr, काष्ठा nfs_entry *entry,
		       bool plus)
अणु
	अचिन्हित पूर्णांक savep;
	uपूर्णांक32_t biपंचांगap[3] = अणु0पूर्ण;
	uपूर्णांक32_t len;
	uपूर्णांक64_t new_cookie;
	__be32 *p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	अगर (*p == xdr_zero) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EAGAIN;
		अगर (*p == xdr_zero)
			वापस -EAGAIN;
		entry->eof = 1;
		वापस -EBADCOOKIE;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	p = xdr_decode_hyper(p, &new_cookie);
	entry->len = be32_to_cpup(p);

	p = xdr_अंतरभूत_decode(xdr, entry->len);
	अगर (unlikely(!p))
		वापस -EAGAIN;
	entry->name = (स्थिर अक्षर *) p;

	/*
	 * In हाल the server करोesn't वापस an inode number,
	 * we fake one here.  (We करोn't use inode number 0,
	 * since glibc seems to choke on it...)
	 */
	entry->ino = 1;
	entry->fattr->valid = 0;

	अगर (decode_attr_biपंचांगap(xdr, biपंचांगap) < 0)
		वापस -EAGAIN;

	अगर (decode_attr_length(xdr, &len, &savep) < 0)
		वापस -EAGAIN;

	अगर (decode_getfattr_attrs(xdr, biपंचांगap, entry->fattr, entry->fh,
			शून्य, entry->label, entry->server) < 0)
		वापस -EAGAIN;
	अगर (entry->fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID)
		entry->ino = entry->fattr->mounted_on_fileid;
	अन्यथा अगर (entry->fattr->valid & NFS_ATTR_FATTR_खाताID)
		entry->ino = entry->fattr->fileid;

	entry->d_type = DT_UNKNOWN;
	अगर (entry->fattr->valid & NFS_ATTR_FATTR_TYPE)
		entry->d_type = nfs_umode_to_dtype(entry->fattr->mode);

	entry->prev_cookie = entry->cookie;
	entry->cookie = new_cookie;

	वापस 0;
पूर्ण

/*
 * We need to translate between nfs status वापस values and
 * the local त्रुटि_सं values which may not be the same.
 */
अटल काष्ठा अणु
	पूर्णांक stat;
	पूर्णांक त्रुटि_सं;
पूर्ण nfs_errtbl[] = अणु
	अणु NFS4_OK,		0		पूर्ण,
	अणु NFS4ERR_PERM,		-EPERM		पूर्ण,
	अणु NFS4ERR_NOENT,	-ENOENT		पूर्ण,
	अणु NFS4ERR_IO,		-त्रुटि_सं_NFSERR_IOपूर्ण,
	अणु NFS4ERR_NXIO,		-ENXIO		पूर्ण,
	अणु NFS4ERR_ACCESS,	-EACCES		पूर्ण,
	अणु NFS4ERR_EXIST,	-EEXIST		पूर्ण,
	अणु NFS4ERR_XDEV,		-EXDEV		पूर्ण,
	अणु NFS4ERR_NOTसूची,	-ENOTसूची	पूर्ण,
	अणु NFS4ERR_ISसूची,	-EISसूची		पूर्ण,
	अणु NFS4ERR_INVAL,	-EINVAL		पूर्ण,
	अणु NFS4ERR_FBIG,		-EFBIG		पूर्ण,
	अणु NFS4ERR_NOSPC,	-ENOSPC		पूर्ण,
	अणु NFS4ERR_ROFS,		-EROFS		पूर्ण,
	अणु NFS4ERR_MLINK,	-EMLINK		पूर्ण,
	अणु NFS4ERR_NAMETOOLONG,	-ENAMETOOLONG	पूर्ण,
	अणु NFS4ERR_NOTEMPTY,	-ENOTEMPTY	पूर्ण,
	अणु NFS4ERR_DQUOT,	-EDQUOT		पूर्ण,
	अणु NFS4ERR_STALE,	-ESTALE		पूर्ण,
	अणु NFS4ERR_BADHANDLE,	-EBADHANDLE	पूर्ण,
	अणु NFS4ERR_BAD_COOKIE,	-EBADCOOKIE	पूर्ण,
	अणु NFS4ERR_NOTSUPP,	-ENOTSUPP	पूर्ण,
	अणु NFS4ERR_TOOSMALL,	-ETOOSMALL	पूर्ण,
	अणु NFS4ERR_SERVERFAULT,	-EREMOTEIO	पूर्ण,
	अणु NFS4ERR_BADTYPE,	-EBADTYPE	पूर्ण,
	अणु NFS4ERR_LOCKED,	-EAGAIN		पूर्ण,
	अणु NFS4ERR_SYMLINK,	-ELOOP		पूर्ण,
	अणु NFS4ERR_OP_ILLEGAL,	-EOPNOTSUPP	पूर्ण,
	अणु NFS4ERR_DEADLOCK,	-EDEADLK	पूर्ण,
	अणु NFS4ERR_NOXATTR,	-ENODATA	पूर्ण,
	अणु NFS4ERR_XATTR2BIG,	-E2BIG		पूर्ण,
	अणु -1,			-EIO		पूर्ण
पूर्ण;

/*
 * Convert an NFS error code to a local one.
 * This one is used joपूर्णांकly by NFSv2 and NFSv3.
 */
अटल पूर्णांक
nfs4_stat_to_त्रुटि_सं(पूर्णांक stat)
अणु
	पूर्णांक i;
	क्रम (i = 0; nfs_errtbl[i].stat != -1; i++) अणु
		अगर (nfs_errtbl[i].stat == stat)
			वापस nfs_errtbl[i].त्रुटि_सं;
	पूर्ण
	अगर (stat <= 10000 || stat > 10100) अणु
		/* The server is looney tunes. */
		वापस -EREMOTEIO;
	पूर्ण
	/* If we cannot translate the error, the recovery routines should
	 * handle it.
	 * Note: reमुख्यing NFSv4 error codes have values > 10000, so should
	 * not conflict with native Linux error codes.
	 */
	वापस -stat;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_2
#समावेश "nfs42xdr.c"
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

#घोषणा PROC(proc, argtype, restype)				\
[NFSPROC4_CLNT_##proc] = अणु					\
	.p_proc   = NFSPROC4_COMPOUND,				\
	.p_encode = nfs4_xdr_##argtype,				\
	.p_decode = nfs4_xdr_##restype,				\
	.p_arglen = NFS4_##argtype##_sz,			\
	.p_replen = NFS4_##restype##_sz,			\
	.p_statidx = NFSPROC4_CLNT_##proc,			\
	.p_name   = #proc,					\
पूर्ण

#घोषणा STUB(proc)		\
[NFSPROC4_CLNT_##proc] = अणु	\
	.p_name = #proc,	\
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
#घोषणा PROC41(proc, argtype, restype)				\
	PROC(proc, argtype, restype)
#अन्यथा
#घोषणा PROC41(proc, argtype, restype)				\
	STUB(proc)
#पूर्ण_अगर

#अगर defined(CONFIG_NFS_V4_2)
#घोषणा PROC42(proc, argtype, restype)				\
	PROC(proc, argtype, restype)
#अन्यथा
#घोषणा PROC42(proc, argtype, restype)				\
	STUB(proc)
#पूर्ण_अगर

स्थिर काष्ठा rpc_procinfo nfs4_procedures[] = अणु
	PROC(READ,		enc_पढ़ो,		dec_पढ़ो),
	PROC(WRITE,		enc_ग_लिखो,		dec_ग_लिखो),
	PROC(COMMIT,		enc_commit,		dec_commit),
	PROC(OPEN,		enc_खोलो,		dec_खोलो),
	PROC(OPEN_CONFIRM,	enc_खोलो_confirm,	dec_खोलो_confirm),
	PROC(OPEN_NOATTR,	enc_खोलो_noattr,	dec_खोलो_noattr),
	PROC(OPEN_DOWNGRADE,	enc_खोलो_करोwngrade,	dec_खोलो_करोwngrade),
	PROC(CLOSE,		enc_बंद,		dec_बंद),
	PROC(SETATTR,		enc_setattr,		dec_setattr),
	PROC(FSINFO,		enc_fsinfo,		dec_fsinfo),
	PROC(RENEW,		enc_renew,		dec_renew),
	PROC(SETCLIENTID,	enc_setclientid,	dec_setclientid),
	PROC(SETCLIENTID_CONFIRM, enc_setclientid_confirm, dec_setclientid_confirm),
	PROC(LOCK,		enc_lock,		dec_lock),
	PROC(LOCKT,		enc_lockt,		dec_lockt),
	PROC(LOCKU,		enc_locku,		dec_locku),
	PROC(ACCESS,		enc_access,		dec_access),
	PROC(GETATTR,		enc_getattr,		dec_getattr),
	PROC(LOOKUP,		enc_lookup,		dec_lookup),
	PROC(LOOKUP_ROOT,	enc_lookup_root,	dec_lookup_root),
	PROC(REMOVE,		enc_हटाओ,		dec_हटाओ),
	PROC(RENAME,		enc_नाम,		dec_नाम),
	PROC(LINK,		enc_link,		dec_link),
	PROC(SYMLINK,		enc_symlink,		dec_symlink),
	PROC(CREATE,		enc_create,		dec_create),
	PROC(PATHCONF,		enc_pathconf,		dec_pathconf),
	PROC(STATFS,		enc_statfs,		dec_statfs),
	PROC(READLINK,		enc_पढ़ोlink,		dec_पढ़ोlink),
	PROC(READसूची,		enc_सूची_पढ़ो,		dec_सूची_पढ़ो),
	PROC(SERVER_CAPS,	enc_server_caps,	dec_server_caps),
	PROC(DELEGRETURN,	enc_delegवापस,	dec_delegवापस),
	PROC(GETACL,		enc_getacl,		dec_getacl),
	PROC(SETACL,		enc_setacl,		dec_setacl),
	PROC(FS_LOCATIONS,	enc_fs_locations,	dec_fs_locations),
	PROC(RELEASE_LOCKOWNER,	enc_release_lockowner,	dec_release_lockowner),
	PROC(SECINFO,		enc_secinfo,		dec_secinfo),
	PROC(FSID_PRESENT,	enc_fsid_present,	dec_fsid_present),
	PROC41(EXCHANGE_ID,	enc_exchange_id,	dec_exchange_id),
	PROC41(CREATE_SESSION,	enc_create_session,	dec_create_session),
	PROC41(DESTROY_SESSION,	enc_destroy_session,	dec_destroy_session),
	PROC41(SEQUENCE,	enc_sequence,		dec_sequence),
	PROC(GET_LEASE_TIME,	enc_get_lease_समय,	dec_get_lease_समय),
	PROC41(RECLAIM_COMPLETE,enc_reclaim_complete,	dec_reclaim_complete),
	PROC41(GETDEVICEINFO,	enc_getdeviceinfo,	dec_getdeviceinfo),
	PROC41(LAYOUTGET,	enc_layoutget,		dec_layoutget),
	PROC41(LAYOUTCOMMIT,	enc_layoutcommit,	dec_layoutcommit),
	PROC41(LAYOUTRETURN,	enc_layoutवापस,	dec_layoutवापस),
	PROC41(SECINFO_NO_NAME,	enc_secinfo_no_name,	dec_secinfo_no_name),
	PROC41(TEST_STATEID,	enc_test_stateid,	dec_test_stateid),
	PROC41(FREE_STATEID,	enc_मुक्त_stateid,	dec_मुक्त_stateid),
	STUB(GETDEVICELIST),
	PROC41(BIND_CONN_TO_SESSION,
			enc_bind_conn_to_session, dec_bind_conn_to_session),
	PROC41(DESTROY_CLIENTID,enc_destroy_clientid,	dec_destroy_clientid),
	PROC42(SEEK,		enc_seek,		dec_seek),
	PROC42(ALLOCATE,	enc_allocate,		dec_allocate),
	PROC42(DEALLOCATE,	enc_deallocate,		dec_deallocate),
	PROC42(LAYOUTSTATS,	enc_layoutstats,	dec_layoutstats),
	PROC42(CLONE,		enc_clone,		dec_clone),
	PROC42(COPY,		enc_copy,		dec_copy),
	PROC42(OFFLOAD_CANCEL,	enc_offload_cancel,	dec_offload_cancel),
	PROC42(COPY_NOTIFY,	enc_copy_notअगरy,	dec_copy_notअगरy),
	PROC(LOOKUPP,		enc_lookupp,		dec_lookupp),
	PROC42(LAYOUTERROR,	enc_layouterror,	dec_layouterror),
	PROC42(GETXATTR,	enc_getxattr,		dec_getxattr),
	PROC42(SETXATTR,	enc_setxattr,		dec_setxattr),
	PROC42(LISTXATTRS,	enc_listxattrs,		dec_listxattrs),
	PROC42(REMOVEXATTR,	enc_हटाओxattr,	dec_हटाओxattr),
	PROC42(READ_PLUS,	enc_पढ़ो_plus,		dec_पढ़ो_plus),
पूर्ण;

अटल अचिन्हित पूर्णांक nfs_version4_counts[ARRAY_SIZE(nfs4_procedures)];
स्थिर काष्ठा rpc_version nfs_version4 = अणु
	.number			= 4,
	.nrprocs		= ARRAY_SIZE(nfs4_procedures),
	.procs			= nfs4_procedures,
	.counts			= nfs_version4_counts,
पूर्ण;
