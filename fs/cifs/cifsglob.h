<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsglob.h
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Jeremy Allison (jra@samba.org)
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
 */
#अगर_अघोषित _CIFS_GLOB_H
#घोषणा _CIFS_GLOB_H

#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/mempool.h>
#समावेश <linux/workqueue.h>
#समावेश "cifs_fs_sb.h"
#समावेश "cifsacl.h"
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/scatterlist.h>
#समावेश <uapi/linux/cअगरs/cअगरs_mount.h>
#समावेश "smb2pdu.h"

#घोषणा CIFS_MAGIC_NUMBER 0xFF534D42      /* the first four bytes of SMB PDUs */

#घोषणा SMB_PATH_MAX 260
#घोषणा CIFS_PORT 445
#घोषणा RFC1001_PORT 139

/*
 * The sizes of various पूर्णांकernal tables and strings
 */
#घोषणा MAX_UID_INFO 16
#घोषणा MAX_SES_INFO 2
#घोषणा MAX_TCON_INFO 4

#घोषणा MAX_TREE_SIZE (2 + CIFS_NI_MAXHOST + 1 + CIFS_MAX_SHARE_LEN + 1)

#घोषणा CIFS_MIN_RCV_POOL 4

#घोषणा MAX_REOPEN_ATT	5 /* these many maximum attempts to reखोलो a file */
/*
 * शेष attribute cache समयout (jअगरfies)
 */
#घोषणा CIFS_DEF_ACTIMEO (1 * HZ)

/*
 * max attribute cache समयout (jअगरfies) - 2^30
 */
#घोषणा CIFS_MAX_ACTIMEO (1 << 30)

/*
 * Max persistent and resilient handle समयout (milliseconds).
 * Winकरोws durable max was 960000 (16 minutes)
 */
#घोषणा SMB3_MAX_HANDLE_TIMEOUT 960000

/*
 * MAX_REQ is the maximum number of requests that WE will send
 * on one socket concurrently.
 */
#घोषणा CIFS_MAX_REQ 32767

#घोषणा RFC1001_NAME_LEN 15
#घोषणा RFC1001_NAME_LEN_WITH_शून्य (RFC1001_NAME_LEN + 1)

/* maximum length of ip addr as a string (including ipv6 and sctp) */
#घोषणा SERVER_NAME_LENGTH 80
#घोषणा SERVER_NAME_LEN_WITH_शून्य     (SERVER_NAME_LENGTH + 1)

/* echo पूर्णांकerval in seconds */
#घोषणा SMB_ECHO_INTERVAL_MIN 1
#घोषणा SMB_ECHO_INTERVAL_MAX 600
#घोषणा SMB_ECHO_INTERVAL_DEFAULT 60

/* maximum number of PDUs in one compound */
#घोषणा MAX_COMPOUND 5

/*
 * Default number of credits to keep available क्रम SMB3.
 * This value is chosen somewhat arbitrarily. The Winकरोws client
 * शेषs to 128 credits, the Winकरोws server allows clients up to
 * 512 credits (or 8K क्रम later versions), and the NetApp server
 * करोes not limit clients at all.  Choose a high enough शेष value
 * such that the client shouldn't limit perक्रमmance, but allow mount
 * to override (until you approach 64K, where we limit credits to 65000
 * to reduce possibility of seeing more server credit overflow bugs.
 */
#घोषणा SMB2_MAX_CREDITS_AVAILABLE 32000

#समावेश "cifspdu.h"

#अगर_अघोषित XATTR_DOS_ATTRIB
#घोषणा XATTR_DOS_ATTRIB "user.DOSATTRIB"
#पूर्ण_अगर

/*
 * CIFS vfs client Status inक्रमmation (based on what we know.)
 */

/* associated with each tcp and smb session */
क्रमागत statusEnum अणु
	CअगरsNew = 0,
	CअगरsGood,
	CअगरsExiting,
	CअगरsNeedReconnect,
	CअगरsNeedNegotiate
पूर्ण;

क्रमागत securityEnum अणु
	Unspecअगरied = 0,	/* not specअगरied */
	LANMAN,			/* Legacy LANMAN auth */
	NTLM,			/* Legacy NTLM012 auth with NTLM hash */
	NTLMv2,			/* Legacy NTLM auth with NTLMv2 hash */
	RawNTLMSSP,		/* NTLMSSP without SPNEGO, NTLMv2 hash */
	Kerberos,		/* Kerberos via SPNEGO */
पूर्ण;

काष्ठा session_key अणु
	अचिन्हित पूर्णांक len;
	अक्षर *response;
पूर्ण;

/* crypto security descriptor definition */
काष्ठा sdesc अणु
	काष्ठा shash_desc shash;
	अक्षर ctx[];
पूर्ण;

/* crypto hashing related काष्ठाure/fields, not specअगरic to a sec mech */
काष्ठा cअगरs_secmech अणु
	काष्ठा crypto_shash *hmacmd5; /* hmac-md5 hash function */
	काष्ठा crypto_shash *md5; /* md5 hash function */
	काष्ठा crypto_shash *hmacsha256; /* hmac-sha256 hash function */
	काष्ठा crypto_shash *cmacaes; /* block-cipher based MAC function */
	काष्ठा crypto_shash *sha512; /* sha512 hash function */
	काष्ठा sdesc *sdeschmacmd5;  /* ctxt to generate ntlmv2 hash, CR1 */
	काष्ठा sdesc *sdescmd5; /* ctxt to generate cअगरs/smb signature */
	काष्ठा sdesc *sdeschmacsha256;  /* ctxt to generate smb2 signature */
	काष्ठा sdesc *sdesccmacaes;  /* ctxt to generate smb3 signature */
	काष्ठा sdesc *sdescsha512; /* ctxt to generate smb3.11 signing key */
	काष्ठा crypto_aead *ccmaesencrypt; /* smb3 encryption aead */
	काष्ठा crypto_aead *ccmaesdecrypt; /* smb3 decryption aead */
पूर्ण;

/* per smb session काष्ठाure/fields */
काष्ठा ntlmssp_auth अणु
	bool sesskey_per_smbsess; /* whether session key is per smb session */
	__u32 client_flags; /* sent by client in type 1 ntlmsssp exchange */
	__u32 server_flags; /* sent by server in type 2 ntlmssp exchange */
	अचिन्हित अक्षर ciphertext[CIFS_CPHTXT_SIZE]; /* sent to server */
	अक्षर cryptkey[CIFS_CRYPTO_KEY_SIZE]; /* used by ntlmssp */
पूर्ण;

काष्ठा cअगरs_cred अणु
	पूर्णांक uid;
	पूर्णांक gid;
	पूर्णांक mode;
	पूर्णांक cecount;
	काष्ठा cअगरs_sid osid;
	काष्ठा cअगरs_sid gsid;
	काष्ठा cअगरs_ntace *ntaces;
	काष्ठा cअगरs_ace *aces;
पूर्ण;

/*
 *****************************************************************
 * Except the CIFS PDUs themselves all the
 * globally पूर्णांकeresting काष्ठाs should go here
 *****************************************************************
 */

/*
 * A smb_rqst represents a complete request to be issued to a server. It's
 * क्रमmed by a kvec array, followed by an array of pages. Page data is assumed
 * to start at the beginning of the first page.
 */
काष्ठा smb_rqst अणु
	काष्ठा kvec	*rq_iov;	/* array of kvecs */
	अचिन्हित पूर्णांक	rq_nvec;	/* number of kvecs in array */
	काष्ठा page	**rq_pages;	/* poपूर्णांकer to array of page ptrs */
	अचिन्हित पूर्णांक	rq_offset;	/* the offset to the 1st page */
	अचिन्हित पूर्णांक	rq_npages;	/* number pages in array */
	अचिन्हित पूर्णांक	rq_pagesz;	/* page size to use */
	अचिन्हित पूर्णांक	rq_tailsz;	/* length of last page */
पूर्ण;

काष्ठा mid_q_entry;
काष्ठा TCP_Server_Info;
काष्ठा cअगरsFileInfo;
काष्ठा cअगरs_ses;
काष्ठा cअगरs_tcon;
काष्ठा dfs_info3_param;
काष्ठा cअगरs_fattr;
काष्ठा smb3_fs_context;
काष्ठा cअगरs_fid;
काष्ठा cअगरs_पढ़ोdata;
काष्ठा cअगरs_ग_लिखोdata;
काष्ठा cअगरs_io_parms;
काष्ठा cअगरs_search_info;
काष्ठा cअगरsInodeInfo;
काष्ठा cअगरs_खोलो_parms;
काष्ठा cअगरs_credits;

काष्ठा smb_version_operations अणु
	पूर्णांक (*send_cancel)(काष्ठा TCP_Server_Info *, काष्ठा smb_rqst *,
			   काष्ठा mid_q_entry *);
	bool (*compare_fids)(काष्ठा cअगरsFileInfo *, काष्ठा cअगरsFileInfo *);
	/* setup request: allocate mid, sign message */
	काष्ठा mid_q_entry *(*setup_request)(काष्ठा cअगरs_ses *,
					     काष्ठा TCP_Server_Info *,
					     काष्ठा smb_rqst *);
	/* setup async request: allocate mid, sign message */
	काष्ठा mid_q_entry *(*setup_async_request)(काष्ठा TCP_Server_Info *,
						काष्ठा smb_rqst *);
	/* check response: verअगरy signature, map error */
	पूर्णांक (*check_receive)(काष्ठा mid_q_entry *, काष्ठा TCP_Server_Info *,
			     bool);
	व्योम (*add_credits)(काष्ठा TCP_Server_Info *server,
			    स्थिर काष्ठा cअगरs_credits *credits,
			    स्थिर पूर्णांक optype);
	व्योम (*set_credits)(काष्ठा TCP_Server_Info *, स्थिर पूर्णांक);
	पूर्णांक * (*get_credits_field)(काष्ठा TCP_Server_Info *, स्थिर पूर्णांक);
	अचिन्हित पूर्णांक (*get_credits)(काष्ठा mid_q_entry *);
	__u64 (*get_next_mid)(काष्ठा TCP_Server_Info *);
	व्योम (*revert_current_mid)(काष्ठा TCP_Server_Info *server,
				   स्थिर अचिन्हित पूर्णांक val);
	/* data offset from पढ़ो response message */
	अचिन्हित पूर्णांक (*पढ़ो_data_offset)(अक्षर *);
	/*
	 * Data length from पढ़ो response message
	 * When in_reमुख्यing is true, the वापसed data length is in
	 * message field DataReमुख्यing क्रम out-of-band data पढ़ो (e.g through
	 * Memory Registration RDMA ग_लिखो in SMBD).
	 * Otherwise, the वापसed data length is in message field DataLength.
	 */
	अचिन्हित पूर्णांक (*पढ़ो_data_length)(अक्षर *, bool in_reमुख्यing);
	/* map smb to linux error */
	पूर्णांक (*map_error)(अक्षर *, bool);
	/* find mid corresponding to the response message */
	काष्ठा mid_q_entry * (*find_mid)(काष्ठा TCP_Server_Info *, अक्षर *);
	व्योम (*dump_detail)(व्योम *buf, काष्ठा TCP_Server_Info *ptcp_info);
	व्योम (*clear_stats)(काष्ठा cअगरs_tcon *);
	व्योम (*prपूर्णांक_stats)(काष्ठा seq_file *m, काष्ठा cअगरs_tcon *);
	व्योम (*dump_share_caps)(काष्ठा seq_file *, काष्ठा cअगरs_tcon *);
	/* verअगरy the message */
	पूर्णांक (*check_message)(अक्षर *, अचिन्हित पूर्णांक, काष्ठा TCP_Server_Info *);
	bool (*is_oplock_अवरोध)(अक्षर *, काष्ठा TCP_Server_Info *);
	पूर्णांक (*handle_cancelled_mid)(काष्ठा mid_q_entry *, काष्ठा TCP_Server_Info *);
	व्योम (*करोwngrade_oplock)(काष्ठा TCP_Server_Info *server,
				 काष्ठा cअगरsInodeInfo *cinode, __u32 oplock,
				 अचिन्हित पूर्णांक epoch, bool *purge_cache);
	/* process transaction2 response */
	bool (*check_trans2)(काष्ठा mid_q_entry *, काष्ठा TCP_Server_Info *,
			     अक्षर *, पूर्णांक);
	/* check अगर we need to negotiate */
	bool (*need_neg)(काष्ठा TCP_Server_Info *);
	/* negotiate to the server */
	पूर्णांक (*negotiate)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_ses *);
	/* set negotiated ग_लिखो size */
	अचिन्हित पूर्णांक (*negotiate_wsize)(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx);
	/* set negotiated पढ़ो size */
	अचिन्हित पूर्णांक (*negotiate_rsize)(काष्ठा cअगरs_tcon *tcon, काष्ठा smb3_fs_context *ctx);
	/* setup smb sessionn */
	पूर्णांक (*sess_setup)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_ses *,
			  स्थिर काष्ठा nls_table *);
	/* बंद smb session */
	पूर्णांक (*logoff)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_ses *);
	/* connect to a server share */
	पूर्णांक (*tree_connect)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_ses *, स्थिर अक्षर *,
			    काष्ठा cअगरs_tcon *, स्थिर काष्ठा nls_table *);
	/* बंद tree connecion */
	पूर्णांक (*tree_disconnect)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *);
	/* get DFS referrals */
	पूर्णांक (*get_dfs_refer)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_ses *,
			     स्थिर अक्षर *, काष्ठा dfs_info3_param **,
			     अचिन्हित पूर्णांक *, स्थिर काष्ठा nls_table *, पूर्णांक);
	/* inक्रमmational QFS call */
	व्योम (*qfs_tcon)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			 काष्ठा cअगरs_sb_info *);
	/* check अगर a path is accessible or not */
	पूर्णांक (*is_path_accessible)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
				  काष्ठा cअगरs_sb_info *, स्थिर अक्षर *);
	/* query path data from the server */
	पूर्णांक (*query_path_info)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			       काष्ठा cअगरs_sb_info *, स्थिर अक्षर *,
			       खाता_ALL_INFO *, bool *, bool *);
	/* query file data from the server */
	पूर्णांक (*query_file_info)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			       काष्ठा cअगरs_fid *, खाता_ALL_INFO *);
	/* query reparse tag from srv to determine which type of special file */
	पूर्णांक (*query_reparse_tag)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
				काष्ठा cअगरs_sb_info *cअगरs_sb, स्थिर अक्षर *path,
				__u32 *reparse_tag);
	/* get server index number */
	पूर्णांक (*get_srv_inum)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			    काष्ठा cअगरs_sb_info *, स्थिर अक्षर *,
			    u64 *uniqueid, खाता_ALL_INFO *);
	/* set size by path */
	पूर्णांक (*set_path_size)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			     स्थिर अक्षर *, __u64, काष्ठा cअगरs_sb_info *, bool);
	/* set size by file handle */
	पूर्णांक (*set_file_size)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			     काष्ठा cअगरsFileInfo *, __u64, bool);
	/* set attributes */
	पूर्णांक (*set_file_info)(काष्ठा inode *, स्थिर अक्षर *, खाता_BASIC_INFO *,
			     स्थिर अचिन्हित पूर्णांक);
	पूर्णांक (*set_compression)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			       काष्ठा cअगरsFileInfo *);
	/* check अगर we can send an echo or nor */
	bool (*can_echo)(काष्ठा TCP_Server_Info *);
	/* send echo request */
	पूर्णांक (*echo)(काष्ठा TCP_Server_Info *);
	/* create directory */
	पूर्णांक (*posix_सूची_गढ़ो)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode,
			umode_t mode, काष्ठा cअगरs_tcon *tcon,
			स्थिर अक्षर *full_path,
			काष्ठा cअगरs_sb_info *cअगरs_sb);
	पूर्णांक (*सूची_गढ़ो)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा inode *inode, umode_t mode,
		     काष्ठा cअगरs_tcon *tcon, स्थिर अक्षर *name,
		     काष्ठा cअगरs_sb_info *sb);
	/* set info on created directory */
	व्योम (*सूची_गढ़ो_setinfo)(काष्ठा inode *, स्थिर अक्षर *,
			      काष्ठा cअगरs_sb_info *, काष्ठा cअगरs_tcon *,
			      स्थिर अचिन्हित पूर्णांक);
	/* हटाओ directory */
	पूर्णांक (*सूची_हटाओ)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, स्थिर अक्षर *,
		     काष्ठा cअगरs_sb_info *);
	/* unlink file */
	पूर्णांक (*unlink)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, स्थिर अक्षर *,
		      काष्ठा cअगरs_sb_info *);
	/* खोलो, नाम and delete file */
	पूर्णांक (*नाम_pending_delete)(स्थिर अक्षर *, काष्ठा dentry *,
				     स्थिर अचिन्हित पूर्णांक);
	/* send नाम request */
	पूर्णांक (*नाम)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, स्थिर अक्षर *,
		      स्थिर अक्षर *, काष्ठा cअगरs_sb_info *);
	/* send create hardlink request */
	पूर्णांक (*create_hardlink)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			       स्थिर अक्षर *, स्थिर अक्षर *,
			       काष्ठा cअगरs_sb_info *);
	/* query symlink target */
	पूर्णांक (*query_symlink)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			     काष्ठा cअगरs_sb_info *, स्थिर अक्षर *,
			     अक्षर **, bool);
	/* खोलो a file क्रम non-posix mounts */
	पूर्णांक (*खोलो)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_खोलो_parms *,
		    __u32 *, खाता_ALL_INFO *);
	/* set fid protocol-specअगरic info */
	व्योम (*set_fid)(काष्ठा cअगरsFileInfo *, काष्ठा cअगरs_fid *, __u32);
	/* बंद a file */
	व्योम (*बंद)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
		      काष्ठा cअगरs_fid *);
	/* बंद a file, वापसing file attributes and बारtamps */
	व्योम (*बंद_getattr)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
		      काष्ठा cअगरsFileInfo *pfile_info);
	/* send a flush request to the server */
	पूर्णांक (*flush)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, काष्ठा cअगरs_fid *);
	/* async पढ़ो from the server */
	पूर्णांक (*async_पढ़ोv)(काष्ठा cअगरs_पढ़ोdata *);
	/* async ग_लिखो to the server */
	पूर्णांक (*async_ग_लिखोv)(काष्ठा cअगरs_ग_लिखोdata *,
			    व्योम (*release)(काष्ठा kref *));
	/* sync पढ़ो from the server */
	पूर्णांक (*sync_पढ़ो)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_fid *,
			 काष्ठा cअगरs_io_parms *, अचिन्हित पूर्णांक *, अक्षर **,
			 पूर्णांक *);
	/* sync ग_लिखो to the server */
	पूर्णांक (*sync_ग_लिखो)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_fid *,
			  काष्ठा cअगरs_io_parms *, अचिन्हित पूर्णांक *, काष्ठा kvec *,
			  अचिन्हित दीर्घ);
	/* खोलो dir, start सूची_पढ़ो */
	पूर्णांक (*query_dir_first)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			       स्थिर अक्षर *, काष्ठा cअगरs_sb_info *,
			       काष्ठा cअगरs_fid *, __u16,
			       काष्ठा cअगरs_search_info *);
	/* जारी सूची_पढ़ो */
	पूर्णांक (*query_dir_next)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			      काष्ठा cअगरs_fid *,
			      __u16, काष्ठा cअगरs_search_info *srch_inf);
	/* बंद dir */
	पूर्णांक (*बंद_dir)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			 काष्ठा cअगरs_fid *);
	/* calculate a size of SMB message */
	अचिन्हित पूर्णांक (*calc_smb_size)(व्योम *buf, काष्ठा TCP_Server_Info *ptcpi);
	/* check क्रम STATUS_PENDING and process the response अगर yes */
	bool (*is_status_pending)(अक्षर *buf, काष्ठा TCP_Server_Info *server);
	/* check क्रम STATUS_NETWORK_SESSION_EXPIRED */
	bool (*is_session_expired)(अक्षर *);
	/* send oplock अवरोध response */
	पूर्णांक (*oplock_response)(काष्ठा cअगरs_tcon *, काष्ठा cअगरs_fid *,
			       काष्ठा cअगरsInodeInfo *);
	/* query remote fileप्रणाली */
	पूर्णांक (*queryfs)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
		       काष्ठा cअगरs_sb_info *, काष्ठा kstatfs *);
	/* send mandatory brlock to the server */
	पूर्णांक (*mand_lock)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरsFileInfo *, __u64,
			 __u64, __u32, पूर्णांक, पूर्णांक, bool);
	/* unlock range of mandatory locks */
	पूर्णांक (*mand_unlock_range)(काष्ठा cअगरsFileInfo *, काष्ठा file_lock *,
				 स्थिर अचिन्हित पूर्णांक);
	/* push brlocks from the cache to the server */
	पूर्णांक (*push_mand_locks)(काष्ठा cअगरsFileInfo *);
	/* get lease key of the inode */
	व्योम (*get_lease_key)(काष्ठा inode *, काष्ठा cअगरs_fid *);
	/* set lease key of the inode */
	व्योम (*set_lease_key)(काष्ठा inode *, काष्ठा cअगरs_fid *);
	/* generate new lease key */
	व्योम (*new_lease_key)(काष्ठा cअगरs_fid *);
	पूर्णांक (*generate_signingkey)(काष्ठा cअगरs_ses *);
	पूर्णांक (*calc_signature)(काष्ठा smb_rqst *, काष्ठा TCP_Server_Info *,
				bool allocate_crypto);
	पूर्णांक (*set_पूर्णांकegrity)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *tcon,
			     काष्ठा cअगरsFileInfo *src_file);
	पूर्णांक (*क्रमागत_snapshots)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_tcon *tcon,
			     काष्ठा cअगरsFileInfo *src_file, व्योम __user *);
	पूर्णांक (*notअगरy)(स्थिर अचिन्हित पूर्णांक xid, काष्ठा file *pfile,
			     व्योम __user *pbuf);
	पूर्णांक (*query_mf_symlink)(अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
				काष्ठा cअगरs_sb_info *, स्थिर अचिन्हित अक्षर *,
				अक्षर *, अचिन्हित पूर्णांक *);
	पूर्णांक (*create_mf_symlink)(अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
				 काष्ठा cअगरs_sb_info *, स्थिर अचिन्हित अक्षर *,
				 अक्षर *, अचिन्हित पूर्णांक *);
	/* अगर we can करो cache पढ़ो operations */
	bool (*is_पढ़ो_op)(__u32);
	/* set oplock level क्रम the inode */
	व्योम (*set_oplock_level)(काष्ठा cअगरsInodeInfo *, __u32, अचिन्हित पूर्णांक,
				 bool *);
	/* create lease context buffer क्रम CREATE request */
	अक्षर * (*create_lease_buf)(u8 *lease_key, u8 oplock);
	/* parse lease context buffer and वापस oplock/epoch info */
	__u8 (*parse_lease_buf)(व्योम *buf, अचिन्हित पूर्णांक *epoch, अक्षर *lkey);
	sमाप_प्रकार (*copychunk_range)(स्थिर अचिन्हित पूर्णांक,
			काष्ठा cअगरsFileInfo *src_file,
			काष्ठा cअगरsFileInfo *target_file,
			u64 src_off, u64 len, u64 dest_off);
	पूर्णांक (*duplicate_extents)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरsFileInfo *src,
			काष्ठा cअगरsFileInfo *target_file, u64 src_off, u64 len,
			u64 dest_off);
	पूर्णांक (*validate_negotiate)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *);
	sमाप_प्रकार (*query_all_EAs)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *,
			स्थिर अचिन्हित अक्षर *, स्थिर अचिन्हित अक्षर *, अक्षर *,
			माप_प्रकार, काष्ठा cअगरs_sb_info *);
	पूर्णांक (*set_EA)(स्थिर अचिन्हित पूर्णांक, काष्ठा cअगरs_tcon *, स्थिर अक्षर *,
			स्थिर अक्षर *, स्थिर व्योम *, स्थिर __u16,
			स्थिर काष्ठा nls_table *, काष्ठा cअगरs_sb_info *);
	काष्ठा cअगरs_ntsd * (*get_acl)(काष्ठा cअगरs_sb_info *, काष्ठा inode *,
			स्थिर अक्षर *, u32 *, u32);
	काष्ठा cअगरs_ntsd * (*get_acl_by_fid)(काष्ठा cअगरs_sb_info *,
			स्थिर काष्ठा cअगरs_fid *, u32 *, u32);
	पूर्णांक (*set_acl)(काष्ठा cअगरs_ntsd *, __u32, काष्ठा inode *, स्थिर अक्षर *,
			पूर्णांक);
	/* ग_लिखोpages retry size */
	अचिन्हित पूर्णांक (*wp_retry_size)(काष्ठा inode *);
	/* get mtu credits */
	पूर्णांक (*रुको_mtu_credits)(काष्ठा TCP_Server_Info *, अचिन्हित पूर्णांक,
				अचिन्हित पूर्णांक *, काष्ठा cअगरs_credits *);
	/* adjust previously taken mtu credits to request size */
	पूर्णांक (*adjust_credits)(काष्ठा TCP_Server_Info *server,
			      काष्ठा cअगरs_credits *credits,
			      स्थिर अचिन्हित पूर्णांक payload_size);
	/* check अगर we need to issue बंद_सूची */
	bool (*dir_needs_बंद)(काष्ठा cअगरsFileInfo *);
	दीर्घ (*fallocate)(काष्ठा file *, काष्ठा cअगरs_tcon *, पूर्णांक, loff_t,
			  loff_t);
	/* init transक्रमm request - used क्रम encryption क्रम now */
	पूर्णांक (*init_transक्रमm_rq)(काष्ठा TCP_Server_Info *, पूर्णांक num_rqst,
				 काष्ठा smb_rqst *, काष्ठा smb_rqst *);
	पूर्णांक (*is_transक्रमm_hdr)(व्योम *buf);
	पूर्णांक (*receive_transक्रमm)(काष्ठा TCP_Server_Info *,
				 काष्ठा mid_q_entry **, अक्षर **, पूर्णांक *);
	क्रमागत securityEnum (*select_sectype)(काष्ठा TCP_Server_Info *,
			    क्रमागत securityEnum);
	पूर्णांक (*next_header)(अक्षर *);
	/* ioctl passthrough क्रम query_info */
	पूर्णांक (*ioctl_query_info)(स्थिर अचिन्हित पूर्णांक xid,
				काष्ठा cअगरs_tcon *tcon,
				काष्ठा cअगरs_sb_info *cअगरs_sb,
				__le16 *path, पूर्णांक is_dir,
				अचिन्हित दीर्घ p);
	/* make unix special files (block, अक्षर, fअगरo, socket) */
	पूर्णांक (*make_node)(अचिन्हित पूर्णांक xid,
			 काष्ठा inode *inode,
			 काष्ठा dentry *dentry,
			 काष्ठा cअगरs_tcon *tcon,
			 स्थिर अक्षर *full_path,
			 umode_t mode,
			 dev_t device_number);
	/* version specअगरic fiemap implementation */
	पूर्णांक (*fiemap)(काष्ठा cअगरs_tcon *tcon, काष्ठा cअगरsFileInfo *,
		      काष्ठा fiemap_extent_info *, u64, u64);
	/* version specअगरic llseek implementation */
	loff_t (*llseek)(काष्ठा file *, काष्ठा cअगरs_tcon *, loff_t, पूर्णांक);
	/* Check क्रम STATUS_IO_TIMEOUT */
	bool (*is_status_io_समयout)(अक्षर *buf);
	/* Check क्रम STATUS_NETWORK_NAME_DELETED */
	व्योम (*is_network_name_deleted)(अक्षर *buf, काष्ठा TCP_Server_Info *srv);
पूर्ण;

काष्ठा smb_version_values अणु
	अक्षर		*version_string;
	__u16		protocol_id;
	__u32		req_capabilities;
	__u32		large_lock_type;
	__u32		exclusive_lock_type;
	__u32		shared_lock_type;
	__u32		unlock_lock_type;
	माप_प्रकार		header_preamble_size;
	माप_प्रकार		header_size;
	माप_प्रकार		max_header_size;
	माप_प्रकार		पढ़ो_rsp_size;
	__le16		lock_cmd;
	अचिन्हित पूर्णांक	cap_unix;
	अचिन्हित पूर्णांक	cap_nt_find;
	अचिन्हित पूर्णांक	cap_large_files;
	__u16		signing_enabled;
	__u16		signing_required;
	माप_प्रकार		create_lease_size;
पूर्ण;

#घोषणा HEADER_SIZE(server) (server->vals->header_size)
#घोषणा MAX_HEADER_SIZE(server) (server->vals->max_header_size)

/**
 * CIFS superblock mount flags (mnt_cअगरs_flags) to consider when
 * trying to reuse existing superblock क्रम a new mount
 */
#घोषणा CIFS_MOUNT_MASK (CIFS_MOUNT_NO_PERM | CIFS_MOUNT_SET_UID | \
			 CIFS_MOUNT_SERVER_INUM | CIFS_MOUNT_सूचीECT_IO | \
			 CIFS_MOUNT_NO_XATTR | CIFS_MOUNT_MAP_SPECIAL_CHR | \
			 CIFS_MOUNT_MAP_SFM_CHR | \
			 CIFS_MOUNT_UNX_EMUL | CIFS_MOUNT_NO_BRL | \
			 CIFS_MOUNT_CIFS_ACL | CIFS_MOUNT_OVERR_UID | \
			 CIFS_MOUNT_OVERR_GID | CIFS_MOUNT_DYNPERM | \
			 CIFS_MOUNT_NOPOSIXBRL | CIFS_MOUNT_NOSSYNC | \
			 CIFS_MOUNT_FSCACHE | CIFS_MOUNT_MF_SYMLINKS | \
			 CIFS_MOUNT_MULTIUSER | CIFS_MOUNT_STRICT_IO | \
			 CIFS_MOUNT_CIFS_BACKUPUID | CIFS_MOUNT_CIFS_BACKUPGID | \
			 CIFS_MOUNT_UID_FROM_ACL | CIFS_MOUNT_NO_HANDLE_CACHE | \
			 CIFS_MOUNT_NO_DFS | CIFS_MOUNT_MODE_FROM_SID | \
			 CIFS_MOUNT_RO_CACHE | CIFS_MOUNT_RW_CACHE)

/**
 * Generic VFS superblock mount flags (s_flags) to consider when
 * trying to reuse existing superblock क्रम a new mount
 */
#घोषणा CIFS_MS_MASK (SB_RDONLY | SB_MANDLOCK | SB_NOEXEC | SB_NOSUID | \
		      SB_NODEV | SB_SYNCHRONOUS)

काष्ठा cअगरs_mnt_data अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा smb3_fs_context *ctx;
	पूर्णांक flags;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
get_rfc1002_length(व्योम *buf)
अणु
	वापस be32_to_cpu(*((__be32 *)buf)) & 0xffffff;
पूर्ण

अटल अंतरभूत व्योम
inc_rfc1001_len(व्योम *buf, पूर्णांक count)
अणु
	be32_add_cpu((__be32 *)buf, count);
पूर्ण

काष्ठा TCP_Server_Info अणु
	काष्ठा list_head tcp_ses_list;
	काष्ठा list_head smb_ses_list;
	__u64 conn_id; /* connection identअगरier (useful क्रम debugging) */
	पूर्णांक srv_count; /* reference counter */
	/* 15 अक्षरacter server name + 0x20 16th byte indicating type = srv */
	अक्षर server_RFC1001_name[RFC1001_NAME_LEN_WITH_शून्य];
	काष्ठा smb_version_operations	*ops;
	काष्ठा smb_version_values	*vals;
	क्रमागत statusEnum tcpStatus; /* what we think the status is */
	अक्षर *hostname; /* hostname portion of UNC string */
	काष्ठा socket *ssocket;
	काष्ठा sockaddr_storage dstaddr;
	काष्ठा sockaddr_storage srcaddr; /* locally bind to this IP */
#अगर_घोषित CONFIG_NET_NS
	काष्ठा net *net;
#पूर्ण_अगर
	रुको_queue_head_t response_q;
	रुको_queue_head_t request_q; /* अगर more than maxmpx to srvr must block*/
	काष्ठा list_head pending_mid_q;
	bool noblocksnd;		/* use blocking sendmsg */
	bool noस्वतःtune;		/* करो not स्वतःtune send buf sizes */
	bool tcp_nodelay;
	अचिन्हित पूर्णांक credits;  /* send no more requests at once */
	अचिन्हित पूर्णांक max_credits; /* can override large 32000 शेष at mnt */
	अचिन्हित पूर्णांक in_flight;  /* number of requests on the wire to server */
	अचिन्हित पूर्णांक max_in_flight; /* max number of requests that were on wire */
	spinlock_t req_lock;  /* protect the two values above */
	काष्ठा mutex srv_mutex;
	काष्ठा task_काष्ठा *tsk;
	अक्षर server_GUID[16];
	__u16 sec_mode;
	bool sign; /* is signing enabled on this connection? */
	bool ignore_signature:1; /* skip validation of signatures in SMB2/3 rsp */
	bool session_estab; /* mark when very first sess is established */
	पूर्णांक echo_credits;  /* echo reserved slots */
	पूर्णांक oplock_credits;  /* oplock अवरोध reserved slots */
	bool echoes:1; /* enable echoes */
	__u8 client_guid[SMB2_CLIENT_GUID_SIZE]; /* Client GUID */
	u16 dialect; /* dialect index that server chose */
	bool oplocks:1; /* enable oplocks */
	अचिन्हित पूर्णांक maxReq;	/* Clients should submit no more */
	/* than maxReq distinct unanswered SMBs to the server when using  */
	/* multiplexed पढ़ोs or ग_लिखोs (क्रम SMB1/CIFS only, not SMB2/SMB3) */
	अचिन्हित पूर्णांक maxBuf;	/* maxBuf specअगरies the maximum */
	/* message size the server can send or receive क्रम non-raw SMBs */
	/* maxBuf is वापसed by SMB NegotiateProtocol so maxBuf is only 0 */
	/* when socket is setup (and during reconnect) beक्रमe NegProt sent */
	अचिन्हित पूर्णांक max_rw;	/* maxRw specअगरies the maximum */
	/* message size the server can send or receive क्रम */
	/* SMB_COM_WRITE_RAW or SMB_COM_READ_RAW. */
	अचिन्हित पूर्णांक capabilities; /* selective disabling of caps by smb sess */
	पूर्णांक समयAdj;  /* Adjust क्रम dअगरference in server समय zone in sec */
	__u64 CurrentMid;         /* multiplex id - rotating counter */
	अक्षर cryptkey[CIFS_CRYPTO_KEY_SIZE]; /* used by ntlm, ntlmv2 etc */
	/* 16th byte of RFC1001 workstation name is always null */
	अक्षर workstation_RFC1001_name[RFC1001_NAME_LEN_WITH_शून्य];
	__u32 sequence_number; /* क्रम signing, रक्षित by srv_mutex */
	__u32 reconnect_instance; /* incremented on each reconnect */
	काष्ठा session_key session_key;
	अचिन्हित दीर्घ lstrp; /* when we got last response from this server */
	काष्ठा cअगरs_secmech secmech; /* crypto sec mech functs, descriptors */
#घोषणा	CIFS_NEGFLAVOR_LANMAN	0	/* wct == 13, LANMAN */
#घोषणा	CIFS_NEGFLAVOR_UNENCAP	1	/* wct == 17, but no ext_sec */
#घोषणा	CIFS_NEGFLAVOR_EXTENDED	2	/* wct == 17, ext_sec bit set */
	अक्षर	negflavor;	/* NEGOTIATE response flavor */
	/* extended security flavors that server supports */
	bool	sec_ntlmssp;		/* supports NTLMSSP */
	bool	sec_kerberosu2u;	/* supports U2U Kerberos */
	bool	sec_kerberos;		/* supports plain Kerberos */
	bool	sec_mskerberos;		/* supports legacy MS Kerberos */
	bool	large_buf;		/* is current buffer large? */
	/* use SMBD connection instead of socket */
	bool	rdma;
	/* poपूर्णांक to the SMBD connection अगर RDMA is used instead of socket */
	काष्ठा smbd_connection *smbd_conn;
	काष्ठा delayed_work	echo; /* echo ping workqueue job */
	अक्षर	*smallbuf;	/* poपूर्णांकer to current "small" buffer */
	अक्षर	*bigbuf;	/* poपूर्णांकer to current "big" buffer */
	/* Total size of this PDU. Only valid from cअगरs_demultiplex_thपढ़ो */
	अचिन्हित पूर्णांक pdu_size;
	अचिन्हित पूर्णांक total_पढ़ो; /* total amount of data पढ़ो in this pass */
	atomic_t in_send; /* requests trying to send */
	atomic_t num_रुकोers;   /* blocked रुकोing to get in sendrecv */
#अगर_घोषित CONFIG_CIFS_FSCACHE
	काष्ठा fscache_cookie   *fscache; /* client index cache cookie */
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_STATS2
	atomic_t num_cmds[NUMBER_OF_SMB2_COMMANDS]; /* total requests by cmd */
	atomic_t smb2slowcmd[NUMBER_OF_SMB2_COMMANDS]; /* count resps > 1 sec */
	__u64 समय_per_cmd[NUMBER_OF_SMB2_COMMANDS]; /* total समय per cmd */
	__u32 slowest_cmd[NUMBER_OF_SMB2_COMMANDS];
	__u32 fastest_cmd[NUMBER_OF_SMB2_COMMANDS];
#पूर्ण_अगर /* STATS2 */
	अचिन्हित पूर्णांक	max_पढ़ो;
	अचिन्हित पूर्णांक	max_ग_लिखो;
	अचिन्हित पूर्णांक	min_offload;
	__le16	compress_algorithm;
	__le16	cipher_type;
	 /* save initital negprot hash */
	__u8	preauth_sha_hash[SMB2_PREAUTH_HASH_SIZE];
	bool	posix_ext_supported;
	काष्ठा delayed_work reconnect; /* reconnect workqueue job */
	काष्ठा mutex reconnect_mutex; /* prevent simultaneous reconnects */
	अचिन्हित दीर्घ echo_पूर्णांकerval;

	/*
	 * Number of tarमाला_लो available क्रम reconnect. The more tarमाला_लो
	 * the more tasks have to रुको to let the demultiplex thपढ़ो
	 * reconnect.
	 */
	पूर्णांक nr_tarमाला_लो;
	bool noblockcnt; /* use non-blocking connect() */
	bool is_channel; /* अगर a session channel */
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
	bool use_swn_dstaddr;
	काष्ठा sockaddr_storage swn_dstaddr;
#पूर्ण_अगर
पूर्ण;

काष्ठा cअगरs_credits अणु
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक instance;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
in_flight(काष्ठा TCP_Server_Info *server)
अणु
	अचिन्हित पूर्णांक num;
	spin_lock(&server->req_lock);
	num = server->in_flight;
	spin_unlock(&server->req_lock);
	वापस num;
पूर्ण

अटल अंतरभूत bool
has_credits(काष्ठा TCP_Server_Info *server, पूर्णांक *credits, पूर्णांक num_credits)
अणु
	पूर्णांक num;
	spin_lock(&server->req_lock);
	num = *credits;
	spin_unlock(&server->req_lock);
	वापस num >= num_credits;
पूर्ण

अटल अंतरभूत व्योम
add_credits(काष्ठा TCP_Server_Info *server, स्थिर काष्ठा cअगरs_credits *credits,
	    स्थिर पूर्णांक optype)
अणु
	server->ops->add_credits(server, credits, optype);
पूर्ण

अटल अंतरभूत व्योम
add_credits_and_wake_अगर(काष्ठा TCP_Server_Info *server,
			स्थिर काष्ठा cअगरs_credits *credits, स्थिर पूर्णांक optype)
अणु
	अगर (credits->value) अणु
		server->ops->add_credits(server, credits, optype);
		wake_up(&server->request_q);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
set_credits(काष्ठा TCP_Server_Info *server, स्थिर पूर्णांक val)
अणु
	server->ops->set_credits(server, val);
पूर्ण

अटल अंतरभूत पूर्णांक
adjust_credits(काष्ठा TCP_Server_Info *server, काष्ठा cअगरs_credits *credits,
	       स्थिर अचिन्हित पूर्णांक payload_size)
अणु
	वापस server->ops->adjust_credits ?
		server->ops->adjust_credits(server, credits, payload_size) : 0;
पूर्ण

अटल अंतरभूत __le64
get_next_mid64(काष्ठा TCP_Server_Info *server)
अणु
	वापस cpu_to_le64(server->ops->get_next_mid(server));
पूर्ण

अटल अंतरभूत __le16
get_next_mid(काष्ठा TCP_Server_Info *server)
अणु
	__u16 mid = server->ops->get_next_mid(server);
	/*
	 * The value in the SMB header should be little endian क्रम easy
	 * on-the-wire decoding.
	 */
	वापस cpu_to_le16(mid);
पूर्ण

अटल अंतरभूत व्योम
revert_current_mid(काष्ठा TCP_Server_Info *server, स्थिर अचिन्हित पूर्णांक val)
अणु
	अगर (server->ops->revert_current_mid)
		server->ops->revert_current_mid(server, val);
पूर्ण

अटल अंतरभूत व्योम
revert_current_mid_from_hdr(काष्ठा TCP_Server_Info *server,
			    स्थिर काष्ठा smb2_sync_hdr *shdr)
अणु
	अचिन्हित पूर्णांक num = le16_to_cpu(shdr->CreditCharge);

	वापस revert_current_mid(server, num > 0 ? num : 1);
पूर्ण

अटल अंतरभूत __u16
get_mid(स्थिर काष्ठा smb_hdr *smb)
अणु
	वापस le16_to_cpu(smb->Mid);
पूर्ण

अटल अंतरभूत bool
compare_mid(__u16 mid, स्थिर काष्ठा smb_hdr *smb)
अणु
	वापस mid == le16_to_cpu(smb->Mid);
पूर्ण

/*
 * When the server supports very large पढ़ोs and ग_लिखोs via POSIX extensions,
 * we can allow up to 2^24-1, minus the size of a READ/WRITE_AND_X header, not
 * including the RFC1001 length.
 *
 * Note that this might make क्रम "interesting" allocation problems during
 * ग_लिखोback however as we have to allocate an array of poपूर्णांकers क्रम the
 * pages. A 16M ग_लिखो means ~32kb page array with PAGE_SIZE == 4096.
 *
 * For पढ़ोs, there is a similar problem as we need to allocate an array
 * of kvecs to handle the receive, though that should only need to be करोne
 * once.
 */
#घोषणा CIFS_MAX_WSIZE ((1<<24) - 1 - माप(WRITE_REQ) + 4)
#घोषणा CIFS_MAX_RSIZE ((1<<24) - माप(READ_RSP) + 4)

/*
 * When the server करोesn't allow large posix ग_लिखोs, only allow a rsize/wsize
 * of 2^17-1 minus the size of the call header. That allows क्रम a पढ़ो or
 * ग_लिखो up to the maximum size described by RFC1002.
 */
#घोषणा CIFS_MAX_RFC1002_WSIZE ((1<<17) - 1 - माप(WRITE_REQ) + 4)
#घोषणा CIFS_MAX_RFC1002_RSIZE ((1<<17) - 1 - माप(READ_RSP) + 4)

/*
 * The शेष wsize is 1M. find_get_pages seems to वापस a maximum of 256
 * pages in a single call. With PAGE_SIZE == 4k, this means we can fill
 * a single wsize request with a single call.
 */
#घोषणा CIFS_DEFAULT_IOSIZE (1024 * 1024)
#घोषणा SMB3_DEFAULT_IOSIZE (4 * 1024 * 1024)

/*
 * Winकरोws only supports a max of 60kb पढ़ोs and 65535 byte ग_लिखोs. Default to
 * those values when posix extensions aren't in क्रमce. In actuality here, we
 * use 65536 to allow क्रम a ग_लिखो that is a multiple of 4k. Most servers seem
 * to be ok with the extra byte even though Winकरोws करोesn't send ग_लिखोs that
 * are that large.
 *
 * Citation:
 *
 * https://blogs.msdn.com/b/खोलोspecअगरication/archive/2009/04/10/smb-maximum-transmit-buffer-size-and-perक्रमmance-tuning.aspx
 */
#घोषणा CIFS_DEFAULT_NON_POSIX_RSIZE (60 * 1024)
#घोषणा CIFS_DEFAULT_NON_POSIX_WSIZE (65536)

/*
 * Macros to allow the TCP_Server_Info->net field and related code to drop out
 * when CONFIG_NET_NS isn't set.
 */

#अगर_घोषित CONFIG_NET_NS

अटल अंतरभूत काष्ठा net *cअगरs_net_ns(काष्ठा TCP_Server_Info *srv)
अणु
	वापस srv->net;
पूर्ण

अटल अंतरभूत व्योम cअगरs_set_net_ns(काष्ठा TCP_Server_Info *srv, काष्ठा net *net)
अणु
	srv->net = net;
पूर्ण

#अन्यथा

अटल अंतरभूत काष्ठा net *cअगरs_net_ns(काष्ठा TCP_Server_Info *srv)
अणु
	वापस &init_net;
पूर्ण

अटल अंतरभूत व्योम cअगरs_set_net_ns(काष्ठा TCP_Server_Info *srv, काष्ठा net *net)
अणु
पूर्ण

#पूर्ण_अगर

काष्ठा cअगरs_server_अगरace अणु
	माप_प्रकार speed;
	अचिन्हित पूर्णांक rdma_capable : 1;
	अचिन्हित पूर्णांक rss_capable : 1;
	काष्ठा sockaddr_storage sockaddr;
पूर्ण;

काष्ठा cअगरs_chan अणु
	काष्ठा TCP_Server_Info *server;
	__u8 signkey[SMB3_SIGN_KEY_SIZE];
पूर्ण;

/*
 * Session काष्ठाure.  One of these क्रम each uid session with a particular host
 */
काष्ठा cअगरs_ses अणु
	काष्ठा list_head smb_ses_list;
	काष्ठा list_head tcon_list;
	काष्ठा cअगरs_tcon *tcon_ipc;
	काष्ठा mutex session_mutex;
	काष्ठा TCP_Server_Info *server;	/* poपूर्णांकer to server info */
	पूर्णांक ses_count;		/* reference counter */
	क्रमागत statusEnum status;
	अचिन्हित overrideSecFlg;  /* अगर non-zero override global sec flags */
	अक्षर *serverOS;		/* name of operating प्रणाली underlying server */
	अक्षर *serverNOS;	/* name of network operating प्रणाली of server */
	अक्षर *serverDoमुख्य;	/* security realm of server */
	__u64 Suid;		/* remote smb uid  */
	kuid_t linux_uid;	/* overriding owner of files on the mount */
	kuid_t cred_uid;	/* owner of credentials */
	अचिन्हित पूर्णांक capabilities;
	अक्षर ip_addr[INET6_ADDRSTRLEN + 1]; /* Max ipv6 (or v4) addr string len */
	अक्षर *user_name;	/* must not be null except during init of sess
				   and after mount option parsing we fill it */
	अक्षर *करोमुख्यName;
	अक्षर *password;
	काष्ठा session_key auth_key;
	काष्ठा ntlmssp_auth *ntlmssp; /* ciphertext, flags, server challenge */
	क्रमागत securityEnum sectype; /* what security flavor was specअगरied? */
	bool sign;		/* is signing required? */
	bool need_reconnect:1; /* connection reset, uid now invalid */
	bool करोमुख्यAuto:1;
	bool binding:1; /* are we binding the session? */
	__u16 session_flags;
	__u8 smb3signingkey[SMB3_SIGN_KEY_SIZE];
	__u8 smb3encryptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8 smb3decryptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8 preauth_sha_hash[SMB2_PREAUTH_HASH_SIZE];

	__u8 binding_preauth_sha_hash[SMB2_PREAUTH_HASH_SIZE];

	/*
	 * Network पूर्णांकerfaces available on the server this session is
	 * connected to.
	 *
	 * Other channels can be खोलोed by connecting and binding this
	 * session to पूर्णांकerfaces from this list.
	 *
	 * अगरace_lock should be taken when accessing any of these fields
	 */
	spinlock_t अगरace_lock;
	काष्ठा cअगरs_server_अगरace *अगरace_list;
	माप_प्रकार अगरace_count;
	अचिन्हित दीर्घ अगरace_last_update; /* jअगरfies */

#घोषणा CIFS_MAX_CHANNELS 16
	काष्ठा cअगरs_chan chans[CIFS_MAX_CHANNELS];
	काष्ठा cअगरs_chan *binding_chan;
	माप_प्रकार chan_count;
	माप_प्रकार chan_max;
	atomic_t chan_seq; /* round robin state */
पूर्ण;

/*
 * When binding a new channel, we need to access the channel which isn't fully
 * established yet.
 */

अटल अंतरभूत
काष्ठा cअगरs_chan *cअगरs_ses_binding_channel(काष्ठा cअगरs_ses *ses)
अणु
	अगर (ses->binding)
		वापस ses->binding_chan;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Returns the server poपूर्णांकer of the session. When binding a new
 * channel this वापसs the last channel which isn't fully established
 * yet.
 *
 * This function should be use क्रम negprot/sess.setup codepaths. For
 * the other requests see cअगरs_pick_channel().
 */
अटल अंतरभूत
काष्ठा TCP_Server_Info *cअगरs_ses_server(काष्ठा cअगरs_ses *ses)
अणु
	अगर (ses->binding)
		वापस ses->binding_chan->server;
	अन्यथा
		वापस ses->server;
पूर्ण

अटल अंतरभूत bool
cap_unix(काष्ठा cअगरs_ses *ses)
अणु
	वापस ses->server->vals->cap_unix & ses->capabilities;
पूर्ण

काष्ठा cached_fid अणु
	bool is_valid:1;	/* Do we have a useable root fid */
	bool file_all_info_is_valid:1;
	bool has_lease:1;
	अचिन्हित दीर्घ समय; /* jअगरfies of when lease was taken */
	काष्ठा kref refcount;
	काष्ठा cअगरs_fid *fid;
	काष्ठा mutex fid_mutex;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा dentry *dentry;
	काष्ठा work_काष्ठा lease_अवरोध;
	काष्ठा smb2_file_all_info file_all_info;
पूर्ण;

/*
 * there is one of these क्रम each connection to a resource on a particular
 * session
 */
काष्ठा cअगरs_tcon अणु
	काष्ठा list_head tcon_list;
	पूर्णांक tc_count;
	काष्ठा list_head rlist; /* reconnect list */
	atomic_t num_local_खोलोs;  /* num of all खोलोs including disconnected */
	atomic_t num_remote_खोलोs; /* num of all network खोलोs on server */
	काष्ठा list_head खोलोFileList;
	spinlock_t खोलो_file_lock; /* protects list above */
	काष्ठा cअगरs_ses *ses;	/* poपूर्णांकer to session associated with */
	अक्षर treeName[MAX_TREE_SIZE + 1]; /* UNC name of resource in ASCII */
	अक्षर *nativeFileSystem;
	अक्षर *password;		/* क्रम share-level security */
	__u32 tid;		/* The 4 byte tree id */
	__u16 Flags;		/* optional support bits */
	क्रमागत statusEnum tidStatus;
	atomic_t num_smbs_sent;
	जोड़ अणु
		काष्ठा अणु
			atomic_t num_ग_लिखोs;
			atomic_t num_पढ़ोs;
			atomic_t num_flushes;
			atomic_t num_oplock_brks;
			atomic_t num_खोलोs;
			atomic_t num_बंदs;
			atomic_t num_deletes;
			atomic_t num_सूची_गढ़ोs;
			atomic_t num_posixखोलोs;
			atomic_t num_posixसूची_गढ़ोs;
			atomic_t num_सूची_हटाओs;
			atomic_t num_नामs;
			atomic_t num_t2नामs;
			atomic_t num_ffirst;
			atomic_t num_fnext;
			atomic_t num_ख_बंद;
			atomic_t num_hardlinks;
			atomic_t num_symlinks;
			atomic_t num_locks;
			atomic_t num_acl_get;
			atomic_t num_acl_set;
		पूर्ण cअगरs_stats;
		काष्ठा अणु
			atomic_t smb2_com_sent[NUMBER_OF_SMB2_COMMANDS];
			atomic_t smb2_com_failed[NUMBER_OF_SMB2_COMMANDS];
		पूर्ण smb2_stats;
	पूर्ण stats;
	__u64    bytes_पढ़ो;
	__u64    bytes_written;
	spinlock_t stat_lock;  /* protects the two fields above */
	खाता_SYSTEM_DEVICE_INFO fsDevInfo;
	खाता_SYSTEM_ATTRIBUTE_INFO fsAttrInfo; /* ok अगर fs name truncated */
	खाता_SYSTEM_UNIX_INFO fsUnixInfo;
	bool ipc:1;   /* set अगर connection to IPC$ share (always also pipe) */
	bool pipe:1;  /* set अगर connection to pipe share */
	bool prपूर्णांक:1; /* set अगर connection to prपूर्णांकer share */
	bool retry:1;
	bool noहाल:1;
	bool nohandlecache:1; /* अगर strange server resource prob can turn off */
	bool nodelete:1;
	bool seal:1;      /* transport encryption क्रम this mounted share */
	bool unix_ext:1;  /* अगर false disable Linux extensions to CIFS protocol
				क्रम this mount even अगर server would support */
	bool posix_extensions; /* अगर true SMB3.11 posix extensions enabled */
	bool local_lease:1; /* check leases (only) on local प्रणाली not remote */
	bool broken_posix_खोलो; /* e.g. Samba server versions < 3.3.2, 3.2.9 */
	bool broken_sparse_sup; /* अगर server or share करोes not support sparse */
	bool need_reconnect:1; /* connection reset, tid now invalid */
	bool need_reखोलो_files:1; /* need to reखोलो tcon file handles */
	bool use_resilient:1; /* use resilient instead of durable handles */
	bool use_persistent:1; /* use persistent instead of durable handles */
	bool no_lease:1;    /* Do not request leases on files or directories */
	bool use_witness:1; /* use witness protocol */
	__le32 capabilities;
	__u32 share_flags;
	__u32 maximal_access;
	__u32 vol_serial_number;
	__le64 vol_create_समय;
	__u64 snapshot_समय; /* क्रम समयwarp tokens - बारtamp of snapshot */
	__u32 handle_समयout; /* persistent and durable handle समयout in ms */
	__u32 ss_flags;		/* sector size flags */
	__u32 perf_sector_size; /* best sector size क्रम perf */
	__u32 max_chunks;
	__u32 max_bytes_chunk;
	__u32 max_bytes_copy;
#अगर_घोषित CONFIG_CIFS_FSCACHE
	u64 resource_id;		/* server resource id */
	काष्ठा fscache_cookie *fscache;	/* cookie क्रम share */
#पूर्ण_अगर
	काष्ठा list_head pending_खोलोs;	/* list of incomplete खोलोs */
	काष्ठा cached_fid crfid; /* Cached root fid */
	/* BB add field क्रम back poपूर्णांकer to sb काष्ठा(s)? */
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	अक्षर *dfs_path;
	पूर्णांक remap:2;
	काष्ठा list_head ulist; /* cache update list */
#पूर्ण_अगर
पूर्ण;

/*
 * This is a refcounted and बारtamped container क्रम a tcon poपूर्णांकer. The
 * container holds a tcon reference. It is considered safe to मुक्त one of
 * these when the tl_count goes to 0. The tl_समय is the समय of the last
 * "get" on the container.
 */
काष्ठा tcon_link अणु
	काष्ठा rb_node		tl_rbnode;
	kuid_t			tl_uid;
	अचिन्हित दीर्घ		tl_flags;
#घोषणा TCON_LINK_MASTER	0
#घोषणा TCON_LINK_PENDING	1
#घोषणा TCON_LINK_IN_TREE	2
	अचिन्हित दीर्घ		tl_समय;
	atomic_t		tl_count;
	काष्ठा cअगरs_tcon	*tl_tcon;
पूर्ण;

बाह्य काष्ठा tcon_link *cअगरs_sb_tlink(काष्ठा cअगरs_sb_info *cअगरs_sb);
बाह्य व्योम smb3_मुक्त_compound_rqst(पूर्णांक num_rqst, काष्ठा smb_rqst *rqst);

अटल अंतरभूत काष्ठा cअगरs_tcon *
tlink_tcon(काष्ठा tcon_link *tlink)
अणु
	वापस tlink->tl_tcon;
पूर्ण

अटल अंतरभूत काष्ठा tcon_link *
cअगरs_sb_master_tlink(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	वापस cअगरs_sb->master_tlink;
पूर्ण

बाह्य व्योम cअगरs_put_tlink(काष्ठा tcon_link *tlink);

अटल अंतरभूत काष्ठा tcon_link *
cअगरs_get_tlink(काष्ठा tcon_link *tlink)
अणु
	अगर (tlink && !IS_ERR(tlink))
		atomic_inc(&tlink->tl_count);
	वापस tlink;
पूर्ण

/* This function is always expected to succeed */
बाह्य काष्ठा cअगरs_tcon *cअगरs_sb_master_tcon(काष्ठा cअगरs_sb_info *cअगरs_sb);

#घोषणा CIFS_OPLOCK_NO_CHANGE 0xfe

काष्ठा cअगरs_pending_खोलो अणु
	काष्ठा list_head olist;
	काष्ठा tcon_link *tlink;
	__u8 lease_key[16];
	__u32 oplock;
पूर्ण;

काष्ठा cअगरs_deferred_बंद अणु
	काष्ठा list_head dlist;
	काष्ठा tcon_link *tlink;
	__u16  netfid;
	__u64  persistent_fid;
	__u64  अस्थिर_fid;
पूर्ण;

/*
 * This info hangs off the cअगरsFileInfo काष्ठाure, poपूर्णांकed to by llist.
 * This is used to track byte stream locks on the file
 */
काष्ठा cअगरsLockInfo अणु
	काष्ठा list_head llist;	/* poपूर्णांकer to next cअगरsLockInfo */
	काष्ठा list_head blist; /* poपूर्णांकer to locks blocked on this */
	रुको_queue_head_t block_q;
	__u64 offset;
	__u64 length;
	__u32 pid;
	__u16 type;
	__u16 flags;
पूर्ण;

/*
 * One of these क्रम each खोलो instance of a file
 */
काष्ठा cअगरs_search_info अणु
	loff_t index_of_last_entry;
	__u16 entries_in_buffer;
	__u16 info_level;
	__u32 resume_key;
	अक्षर *ntwrk_buf_start;
	अक्षर *srch_entries_start;
	अक्षर *last_entry;
	स्थिर अक्षर *presume_name;
	अचिन्हित पूर्णांक resume_name_len;
	bool endOfSearch:1;
	bool emptyDir:1;
	bool unicode:1;
	bool smallBuf:1; /* so we know which buf_release function to call */
पूर्ण;

#घोषणा ACL_NO_MODE	((umode_t)(-1))
काष्ठा cअगरs_खोलो_parms अणु
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	पूर्णांक disposition;
	पूर्णांक desired_access;
	पूर्णांक create_options;
	स्थिर अक्षर *path;
	काष्ठा cअगरs_fid *fid;
	umode_t mode;
	bool reconnect:1;
पूर्ण;

काष्ठा cअगरs_fid अणु
	__u16 netfid;
	__u64 persistent_fid;	/* persist file id क्रम smb2 */
	__u64 अस्थिर_fid;	/* अस्थिर file id क्रम smb2 */
	__u8 lease_key[SMB2_LEASE_KEY_SIZE];	/* lease key क्रम smb2 */
	__u8 create_guid[16];
	__u32 access;
	काष्ठा cअगरs_pending_खोलो *pending_खोलो;
	अचिन्हित पूर्णांक epoch;
#अगर_घोषित CONFIG_CIFS_DEBUG2
	__u64 mid;
#पूर्ण_अगर /* CIFS_DEBUG2 */
	bool purge_cache;
पूर्ण;

काष्ठा cअगरs_fid_locks अणु
	काष्ठा list_head llist;
	काष्ठा cअगरsFileInfo *cfile;	/* fid that owns locks */
	काष्ठा list_head locks;		/* locks held by fid above */
पूर्ण;

काष्ठा cअगरsFileInfo अणु
	/* following two lists are रक्षित by tcon->खोलो_file_lock */
	काष्ठा list_head tlist;	/* poपूर्णांकer to next fid owned by tcon */
	काष्ठा list_head flist;	/* next fid (file instance) क्रम this inode */
	/* lock list below रक्षित by cअगरsi->lock_sem */
	काष्ठा cअगरs_fid_locks *llist;	/* brlocks held by this fid */
	kuid_t uid;		/* allows finding which FileInfo काष्ठाure */
	__u32 pid;		/* process id who खोलोed file */
	काष्ठा cअगरs_fid fid;	/* file id from remote */
	काष्ठा list_head rlist; /* reconnect list */
	/* BB add lock scope info here अगर needed */ ;
	/* lock scope id (0 अगर none) */
	काष्ठा dentry *dentry;
	काष्ठा tcon_link *tlink;
	अचिन्हित पूर्णांक f_flags;
	bool invalidHandle:1;	/* file बंदd via session abend */
	bool swapfile:1;
	bool oplock_अवरोध_cancelled:1;
	अचिन्हित पूर्णांक oplock_epoch; /* epoch from the lease अवरोध */
	__u32 oplock_level; /* oplock/lease level from the lease अवरोध */
	पूर्णांक count;
	spinlock_t file_info_lock; /* protects four flag/count fields above */
	काष्ठा mutex fh_mutex; /* prevents reखोलो race after dead ses*/
	काष्ठा cअगरs_search_info srch_inf;
	काष्ठा work_काष्ठा oplock_अवरोध; /* work क्रम oplock अवरोधs */
	काष्ठा work_काष्ठा put; /* work क्रम the final part of _put */
	काष्ठा delayed_work deferred;
	bool deferred_बंद_scheduled; /* Flag to indicate बंद is scheduled */
पूर्ण;

काष्ठा cअगरs_io_parms अणु
	__u16 netfid;
	__u64 persistent_fid;	/* persist file id क्रम smb2 */
	__u64 अस्थिर_fid;	/* अस्थिर file id क्रम smb2 */
	__u32 pid;
	__u64 offset;
	अचिन्हित पूर्णांक length;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा TCP_Server_Info *server;
पूर्ण;

काष्ठा cअगरs_aio_ctx अणु
	काष्ठा kref		refcount;
	काष्ठा list_head	list;
	काष्ठा mutex		aio_mutex;
	काष्ठा completion	करोne;
	काष्ठा iov_iter		iter;
	काष्ठा kiocb		*iocb;
	काष्ठा cअगरsFileInfo	*cfile;
	काष्ठा bio_vec		*bv;
	loff_t			pos;
	अचिन्हित पूर्णांक		npages;
	sमाप_प्रकार			rc;
	अचिन्हित पूर्णांक		len;
	अचिन्हित पूर्णांक		total_len;
	bool			should_dirty;
	/*
	 * Indicates अगर this aio_ctx is क्रम direct_io,
	 * If yes, iter is a copy of the user passed iov_iter
	 */
	bool			direct_io;
पूर्ण;

/* asynchronous पढ़ो support */
काष्ठा cअगरs_पढ़ोdata अणु
	काष्ठा kref			refcount;
	काष्ठा list_head		list;
	काष्ठा completion		करोne;
	काष्ठा cअगरsFileInfo		*cfile;
	काष्ठा address_space		*mapping;
	काष्ठा cअगरs_aio_ctx		*ctx;
	__u64				offset;
	अचिन्हित पूर्णांक			bytes;
	अचिन्हित पूर्णांक			got_bytes;
	pid_t				pid;
	पूर्णांक				result;
	काष्ठा work_काष्ठा		work;
	पूर्णांक (*पढ़ो_पूर्णांकo_pages)(काष्ठा TCP_Server_Info *server,
				काष्ठा cअगरs_पढ़ोdata *rdata,
				अचिन्हित पूर्णांक len);
	पूर्णांक (*copy_पूर्णांकo_pages)(काष्ठा TCP_Server_Info *server,
				काष्ठा cअगरs_पढ़ोdata *rdata,
				काष्ठा iov_iter *iter);
	काष्ठा kvec			iov[2];
	काष्ठा TCP_Server_Info		*server;
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	काष्ठा smbd_mr			*mr;
#पूर्ण_अगर
	अचिन्हित पूर्णांक			pagesz;
	अचिन्हित पूर्णांक			page_offset;
	अचिन्हित पूर्णांक			tailsz;
	काष्ठा cअगरs_credits		credits;
	अचिन्हित पूर्णांक			nr_pages;
	काष्ठा page			**pages;
पूर्ण;

/* asynchronous ग_लिखो support */
काष्ठा cअगरs_ग_लिखोdata अणु
	काष्ठा kref			refcount;
	काष्ठा list_head		list;
	काष्ठा completion		करोne;
	क्रमागत ग_लिखोback_sync_modes	sync_mode;
	काष्ठा work_काष्ठा		work;
	काष्ठा cअगरsFileInfo		*cfile;
	काष्ठा cअगरs_aio_ctx		*ctx;
	__u64				offset;
	pid_t				pid;
	अचिन्हित पूर्णांक			bytes;
	पूर्णांक				result;
	काष्ठा TCP_Server_Info		*server;
#अगर_घोषित CONFIG_CIFS_SMB_सूचीECT
	काष्ठा smbd_mr			*mr;
#पूर्ण_अगर
	अचिन्हित पूर्णांक			pagesz;
	अचिन्हित पूर्णांक			page_offset;
	अचिन्हित पूर्णांक			tailsz;
	काष्ठा cअगरs_credits		credits;
	अचिन्हित पूर्णांक			nr_pages;
	काष्ठा page			**pages;
पूर्ण;

/*
 * Take a reference on the file निजी data. Must be called with
 * cfile->file_info_lock held.
 */
अटल अंतरभूत व्योम
cअगरsFileInfo_get_locked(काष्ठा cअगरsFileInfo *cअगरs_file)
अणु
	++cअगरs_file->count;
पूर्ण

काष्ठा cअगरsFileInfo *cअगरsFileInfo_get(काष्ठा cअगरsFileInfo *cअगरs_file);
व्योम _cअगरsFileInfo_put(काष्ठा cअगरsFileInfo *cअगरs_file, bool रुको_oplock_hdlr,
		       bool offload);
व्योम cअगरsFileInfo_put(काष्ठा cअगरsFileInfo *cअगरs_file);

#घोषणा CIFS_CACHE_READ_FLG	1
#घोषणा CIFS_CACHE_HANDLE_FLG	2
#घोषणा CIFS_CACHE_RH_FLG	(CIFS_CACHE_READ_FLG | CIFS_CACHE_HANDLE_FLG)
#घोषणा CIFS_CACHE_WRITE_FLG	4
#घोषणा CIFS_CACHE_RW_FLG	(CIFS_CACHE_READ_FLG | CIFS_CACHE_WRITE_FLG)
#घोषणा CIFS_CACHE_RHW_FLG	(CIFS_CACHE_RW_FLG | CIFS_CACHE_HANDLE_FLG)

#घोषणा CIFS_CACHE_READ(cinode) ((cinode->oplock & CIFS_CACHE_READ_FLG) || (CIFS_SB(cinode->vfs_inode.i_sb)->mnt_cअगरs_flags & CIFS_MOUNT_RO_CACHE))
#घोषणा CIFS_CACHE_HANDLE(cinode) (cinode->oplock & CIFS_CACHE_HANDLE_FLG)
#घोषणा CIFS_CACHE_WRITE(cinode) ((cinode->oplock & CIFS_CACHE_WRITE_FLG) || (CIFS_SB(cinode->vfs_inode.i_sb)->mnt_cअगरs_flags & CIFS_MOUNT_RW_CACHE))

/*
 * One of these क्रम each file inode
 */

काष्ठा cअगरsInodeInfo अणु
	bool can_cache_brlcks;
	काष्ठा list_head llist;	/* locks helb by this inode */
	/*
	 * NOTE: Some code paths call करोwn_पढ़ो(lock_sem) twice, so
	 * we must always use cअगरs_करोwn_ग_लिखो() instead of करोwn_ग_लिखो()
	 * क्रम this semaphore to aव्योम deadlocks.
	 */
	काष्ठा rw_semaphore lock_sem;	/* protect the fields above */
	/* BB add in lists क्रम dirty pages i.e. ग_लिखो caching info क्रम oplock */
	काष्ठा list_head खोलोFileList;
	spinlock_t	खोलो_file_lock;	/* protects खोलोFileList */
	__u32 cअगरsAttrs; /* e.g. DOS archive bit, sparse, compressed, प्रणाली */
	अचिन्हित पूर्णांक oplock;		/* oplock/lease level we have */
	अचिन्हित पूर्णांक epoch;		/* used to track lease state changes */
#घोषणा CIFS_INODE_PENDING_OPLOCK_BREAK   (0) /* oplock अवरोध in progress */
#घोषणा CIFS_INODE_PENDING_WRITERS	  (1) /* Writes in progress */
#घोषणा CIFS_INODE_FLAG_UNUSED		  (2) /* Unused flag */
#घोषणा CIFS_INO_DELETE_PENDING		  (3) /* delete pending on server */
#घोषणा CIFS_INO_INVALID_MAPPING	  (4) /* pagecache is invalid */
#घोषणा CIFS_INO_LOCK			  (5) /* lock bit क्रम synchronization */
#घोषणा CIFS_INO_MODIFIED_ATTR            (6) /* Indicate change in mसमय/स_समय */
	अचिन्हित दीर्घ flags;
	spinlock_t ग_लिखोrs_lock;
	अचिन्हित पूर्णांक ग_लिखोrs;		/* Number of ग_लिखोrs on this inode */
	अचिन्हित दीर्घ समय;		/* jअगरfies of last update of inode */
	u64  server_eof;		/* current file size on server -- रक्षित by i_lock */
	u64  uniqueid;			/* server inode number */
	u64  createसमय;		/* creation समय on server */
	__u8 lease_key[SMB2_LEASE_KEY_SIZE];	/* lease key क्रम this inode */
#अगर_घोषित CONFIG_CIFS_FSCACHE
	काष्ठा fscache_cookie *fscache;
#पूर्ण_अगर
	काष्ठा inode vfs_inode;
	काष्ठा list_head deferred_बंदs; /* list of deferred बंदs */
	spinlock_t deferred_lock; /* protection on deferred list */
	bool lease_granted; /* Flag to indicate whether lease or oplock is granted. */
पूर्ण;

अटल अंतरभूत काष्ठा cअगरsInodeInfo *
CIFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा cअगरsInodeInfo, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा cअगरs_sb_info *
CIFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा cअगरs_sb_info *
CIFS_खाता_SB(काष्ठा file *file)
अणु
	वापस CIFS_SB(file_inode(file)->i_sb);
पूर्ण

अटल अंतरभूत अक्षर CIFS_सूची_SEP(स्थिर काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_POSIX_PATHS)
		वापस '/';
	अन्यथा
		वापस '\\';
पूर्ण

अटल अंतरभूत व्योम
convert_delimiter(अक्षर *path, अक्षर delim)
अणु
	अक्षर old_delim, *pos;

	अगर (delim == '/')
		old_delim = '\\';
	अन्यथा
		old_delim = '/';

	pos = path;
	जबतक ((pos = म_अक्षर(pos, old_delim)))
		*pos = delim;
पूर्ण

#घोषणा cअगरs_stats_inc atomic_inc

अटल अंतरभूत व्योम cअगरs_stats_bytes_written(काष्ठा cअगरs_tcon *tcon,
					    अचिन्हित पूर्णांक bytes)
अणु
	अगर (bytes) अणु
		spin_lock(&tcon->stat_lock);
		tcon->bytes_written += bytes;
		spin_unlock(&tcon->stat_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cअगरs_stats_bytes_पढ़ो(काष्ठा cअगरs_tcon *tcon,
					 अचिन्हित पूर्णांक bytes)
अणु
	spin_lock(&tcon->stat_lock);
	tcon->bytes_पढ़ो += bytes;
	spin_unlock(&tcon->stat_lock);
पूर्ण


/*
 * This is the prototype क्रम the mid receive function. This function is क्रम
 * receiving the rest of the SMB frame, starting with the WordCount (which is
 * just after the MID in काष्ठा smb_hdr). Note:
 *
 * - This will be called by cअगरsd, with no locks held.
 * - The mid will still be on the pending_mid_q.
 * - mid->resp_buf will poपूर्णांक to the current buffer.
 *
 * Returns zero on a successful receive, or an error. The receive state in
 * the TCP_Server_Info will also be updated.
 */
प्रकार पूर्णांक (mid_receive_t)(काष्ठा TCP_Server_Info *server,
			    काष्ठा mid_q_entry *mid);

/*
 * This is the prototype क्रम the mid callback function. This is called once the
 * mid has been received off of the socket. When creating one, take special
 * care to aव्योम deadlocks. Things to bear in mind:
 *
 * - it will be called by cअगरsd, with no locks held
 * - the mid will be हटाओd from any lists
 */
प्रकार व्योम (mid_callback_t)(काष्ठा mid_q_entry *mid);

/*
 * This is the protopyte क्रम mid handle function. This is called once the mid
 * has been recognized after decryption of the message.
 */
प्रकार पूर्णांक (mid_handle_t)(काष्ठा TCP_Server_Info *server,
			    काष्ठा mid_q_entry *mid);

/* one of these क्रम every pending CIFS request to the server */
काष्ठा mid_q_entry अणु
	काष्ठा list_head qhead;	/* mids रुकोing on reply from this server */
	काष्ठा kref refcount;
	काष्ठा TCP_Server_Info *server;	/* server corresponding to this mid */
	__u64 mid;		/* multiplex id */
	__u16 credits;		/* number of credits consumed by this mid */
	__u16 credits_received;	/* number of credits from the response */
	__u32 pid;		/* process id */
	__u32 sequence_number;  /* क्रम CIFS signing */
	अचिन्हित दीर्घ when_alloc;  /* when mid was created */
#अगर_घोषित CONFIG_CIFS_STATS2
	अचिन्हित दीर्घ when_sent; /* समय when smb send finished */
	अचिन्हित दीर्घ when_received; /* when demux complete (taken off wire) */
#पूर्ण_अगर
	mid_receive_t *receive; /* call receive callback */
	mid_callback_t *callback; /* call completion callback */
	mid_handle_t *handle; /* call handle mid callback */
	व्योम *callback_data;	  /* general purpose poपूर्णांकer क्रम callback */
	काष्ठा task_काष्ठा *creator;
	व्योम *resp_buf;		/* poपूर्णांकer to received SMB header */
	अचिन्हित पूर्णांक resp_buf_size;
	पूर्णांक mid_state;	/* wish this were क्रमागत but can not pass to रुको_event */
	अचिन्हित पूर्णांक mid_flags;
	__le16 command;		/* smb command code */
	अचिन्हित पूर्णांक optype;	/* operation type */
	bool large_buf:1;	/* अगर valid response, is poपूर्णांकer to large buf */
	bool multiRsp:1;	/* multiple trans2 responses क्रम one request  */
	bool multiEnd:1;	/* both received */
	bool decrypted:1;	/* decrypted entry */
पूर्ण;

काष्ठा बंद_cancelled_खोलो अणु
	काष्ठा cअगरs_fid         fid;
	काष्ठा cअगरs_tcon        *tcon;
	काष्ठा work_काष्ठा      work;
	__u64 mid;
	__u16 cmd;
पूर्ण;

/*	Make code in transport.c a little cleaner by moving
	update of optional stats पूर्णांकo function below */
अटल अंतरभूत व्योम cअगरs_in_send_inc(काष्ठा TCP_Server_Info *server)
अणु
	atomic_inc(&server->in_send);
पूर्ण

अटल अंतरभूत व्योम cअगरs_in_send_dec(काष्ठा TCP_Server_Info *server)
अणु
	atomic_dec(&server->in_send);
पूर्ण

अटल अंतरभूत व्योम cअगरs_num_रुकोers_inc(काष्ठा TCP_Server_Info *server)
अणु
	atomic_inc(&server->num_रुकोers);
पूर्ण

अटल अंतरभूत व्योम cअगरs_num_रुकोers_dec(काष्ठा TCP_Server_Info *server)
अणु
	atomic_dec(&server->num_रुकोers);
पूर्ण

#अगर_घोषित CONFIG_CIFS_STATS2
अटल अंतरभूत व्योम cअगरs_save_when_sent(काष्ठा mid_q_entry *mid)
अणु
	mid->when_sent = jअगरfies;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cअगरs_save_when_sent(काष्ठा mid_q_entry *mid)
अणु
पूर्ण
#पूर्ण_अगर

/* क्रम pending dnotअगरy requests */
काष्ठा dir_notअगरy_req अणु
	काष्ठा list_head lhead;
	__le16 Pid;
	__le16 PidHigh;
	__u16 Mid;
	__u16 Tid;
	__u16 Uid;
	__u16 netfid;
	__u32 filter; /* CompletionFilter (क्रम multishot) */
	पूर्णांक multishot;
	काष्ठा file *pfile;
पूर्ण;

काष्ठा dfs_info3_param अणु
	पूर्णांक flags; /* DFSREF_REFERRAL_SERVER, DFSREF_STORAGE_SERVER*/
	पूर्णांक path_consumed;
	पूर्णांक server_type;
	पूर्णांक ref_flag;
	अक्षर *path_name;
	अक्षर *node_name;
	पूर्णांक ttl;
पूर्ण;

/*
 * common काष्ठा क्रम holding inode info when searching क्रम or updating an
 * inode with new info
 */

#घोषणा CIFS_FATTR_DFS_REFERRAL		0x1
#घोषणा CIFS_FATTR_DELETE_PENDING	0x2
#घोषणा CIFS_FATTR_NEED_REVAL		0x4
#घोषणा CIFS_FATTR_INO_COLLISION	0x8
#घोषणा CIFS_FATTR_UNKNOWN_NLINK	0x10
#घोषणा CIFS_FATTR_FAKE_ROOT_INO	0x20

काष्ठा cअगरs_fattr अणु
	u32		cf_flags;
	u32		cf_cअगरsattrs;
	u64		cf_uniqueid;
	u64		cf_eof;
	u64		cf_bytes;
	u64		cf_createसमय;
	kuid_t		cf_uid;
	kgid_t		cf_gid;
	umode_t		cf_mode;
	dev_t		cf_rdev;
	अचिन्हित पूर्णांक	cf_nlink;
	अचिन्हित पूर्णांक	cf_dtype;
	काष्ठा बारpec64 cf_aसमय;
	काष्ठा बारpec64 cf_mसमय;
	काष्ठा बारpec64 cf_स_समय;
	u32             cf_cअगरstag;
पूर्ण;

अटल अंतरभूत व्योम मुक्त_dfs_info_param(काष्ठा dfs_info3_param *param)
अणु
	अगर (param) अणु
		kमुक्त(param->path_name);
		kमुक्त(param->node_name);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम मुक्त_dfs_info_array(काष्ठा dfs_info3_param *param,
				       पूर्णांक number_of_items)
अणु
	पूर्णांक i;
	अगर ((number_of_items == 0) || (param == शून्य))
		वापस;
	क्रम (i = 0; i < number_of_items; i++) अणु
		kमुक्त(param[i].path_name);
		kमुक्त(param[i].node_name);
	पूर्ण
	kमुक्त(param);
पूर्ण

अटल अंतरभूत bool is_पूर्णांकerrupt_error(पूर्णांक error)
अणु
	चयन (error) अणु
	हाल -EINTR:
	हाल -ERESTARTSYS:
	हाल -ERESTARTNOHAND:
	हाल -ERESTARTNOINTR:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool is_retryable_error(पूर्णांक error)
अणु
	अगर (is_पूर्णांकerrupt_error(error) || error == -EAGAIN)
		वापस true;
	वापस false;
पूर्ण


/* cअगरs_get_writable_file() flags */
#घोषणा FIND_WR_ANY         0
#घोषणा FIND_WR_FSUID_ONLY  1
#घोषणा FIND_WR_WITH_DELETE 2

#घोषणा   MID_FREE 0
#घोषणा   MID_REQUEST_ALLOCATED 1
#घोषणा   MID_REQUEST_SUBMITTED 2
#घोषणा   MID_RESPONSE_RECEIVED 4
#घोषणा   MID_RETRY_NEEDED      8 /* session बंदd जबतक this request out */
#घोषणा   MID_RESPONSE_MALFORMED 0x10
#घोषणा   MID_SHUTDOWN		 0x20

/* Flags */
#घोषणा   MID_WAIT_CANCELLED	 1 /* Cancelled जबतक रुकोing क्रम response */
#घोषणा   MID_DELETED            2 /* Mid has been dequeued/deleted */

/* Types of response buffer वापसed from SendReceive2 */
#घोषणा   CIFS_NO_BUFFER        0    /* Response buffer not वापसed */
#घोषणा   CIFS_SMALL_BUFFER     1
#घोषणा   CIFS_LARGE_BUFFER     2
#घोषणा   CIFS_IOVEC            4    /* array of response buffers */

/* Type of Request to SendReceive2 */
#घोषणा   CIFS_BLOCKING_OP      1    /* operation can block */
#घोषणा   CIFS_NON_BLOCKING     2    /* करो not block रुकोing क्रम credits */
#घोषणा   CIFS_TIMEOUT_MASK 0x003    /* only one of above set in req */
#घोषणा   CIFS_LOG_ERROR    0x010    /* log NT STATUS अगर non-zero */
#घोषणा   CIFS_LARGE_BUF_OP 0x020    /* large request buffer */
#घोषणा   CIFS_NO_RSP_BUF   0x040    /* no response buffer required */

/* Type of request operation */
#घोषणा   CIFS_ECHO_OP            0x080  /* echo request */
#घोषणा   CIFS_OBREAK_OP          0x0100 /* oplock अवरोध request */
#घोषणा   CIFS_NEG_OP             0x0200 /* negotiate request */
#घोषणा   CIFS_CP_CREATE_CLOSE_OP 0x0400 /* compound create+बंद request */
/* Lower biपंचांगask values are reserved by others below. */
#घोषणा   CIFS_SESS_OP            0x2000 /* session setup request */
#घोषणा   CIFS_OP_MASK            0x2780 /* mask request type */

#घोषणा   CIFS_HAS_CREDITS        0x0400 /* alपढ़ोy has credits */
#घोषणा   CIFS_TRANSFORM_REQ      0x0800 /* transक्रमm request beक्रमe sending */
#घोषणा   CIFS_NO_SRV_RSP         0x1000 /* there is no server response */

/* Security Flags: indicate type of session setup needed */
#घोषणा   CIFSSEC_MAY_SIGN	0x00001
#घोषणा   CIFSSEC_MAY_NTLM	0x00002
#घोषणा   CIFSSEC_MAY_NTLMV2	0x00004
#घोषणा   CIFSSEC_MAY_KRB5	0x00008
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
#घोषणा   CIFSSEC_MAY_LANMAN	0x00010
#घोषणा   CIFSSEC_MAY_PLNTXT	0x00020
#अन्यथा
#घोषणा   CIFSSEC_MAY_LANMAN    0
#घोषणा   CIFSSEC_MAY_PLNTXT    0
#पूर्ण_अगर /* weak passwords */
#घोषणा   CIFSSEC_MAY_SEAL	0x00040 /* not supported yet */
#घोषणा   CIFSSEC_MAY_NTLMSSP	0x00080 /* raw ntlmssp with ntlmv2 */

#घोषणा   CIFSSEC_MUST_SIGN	0x01001
/* note that only one of the following can be set so the
result of setting MUST flags more than once will be to
require use of the stronger protocol */
#घोषणा   CIFSSEC_MUST_NTLM	0x02002
#घोषणा   CIFSSEC_MUST_NTLMV2	0x04004
#घोषणा   CIFSSEC_MUST_KRB5	0x08008
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
#घोषणा   CIFSSEC_MUST_LANMAN	0x10010
#घोषणा   CIFSSEC_MUST_PLNTXT	0x20020
#अगर_घोषित CONFIG_CIFS_UPCALL
#घोषणा   CIFSSEC_MASK          0xBF0BF /* allows weak security but also krb5 */
#अन्यथा
#घोषणा   CIFSSEC_MASK          0xB70B7 /* current flags supported अगर weak */
#पूर्ण_अगर /* UPCALL */
#अन्यथा /* करो not allow weak pw hash */
#घोषणा   CIFSSEC_MUST_LANMAN	0
#घोषणा   CIFSSEC_MUST_PLNTXT	0
#अगर_घोषित CONFIG_CIFS_UPCALL
#घोषणा   CIFSSEC_MASK          0x8F08F /* flags supported अगर no weak allowed */
#अन्यथा
#घोषणा	  CIFSSEC_MASK          0x87087 /* flags supported अगर no weak allowed */
#पूर्ण_अगर /* UPCALL */
#पूर्ण_अगर /* WEAK_PW_HASH */
#घोषणा   CIFSSEC_MUST_SEAL	0x40040 /* not supported yet */
#घोषणा   CIFSSEC_MUST_NTLMSSP	0x80080 /* raw ntlmssp with ntlmv2 */

#घोषणा   CIFSSEC_DEF (CIFSSEC_MAY_SIGN | CIFSSEC_MAY_NTLMV2 | CIFSSEC_MAY_NTLMSSP)
#घोषणा   CIFSSEC_MAX (CIFSSEC_MUST_SIGN | CIFSSEC_MUST_NTLMV2)
#घोषणा   CIFSSEC_AUTH_MASK (CIFSSEC_MAY_NTLM | CIFSSEC_MAY_NTLMV2 | CIFSSEC_MAY_LANMAN | CIFSSEC_MAY_PLNTXT | CIFSSEC_MAY_KRB5 | CIFSSEC_MAY_NTLMSSP)
/*
 *****************************************************************
 * All स्थिरants go here
 *****************************************************************
 */

#घोषणा UID_HASH (16)

/*
 * Note that ONE module should define _DECLARE_GLOBALS_HERE to cause the
 * following to be declared.
 */

/****************************************************************************
 *  Locking notes.  All updates to global variables and lists should be
 *                  रक्षित by spinlocks or semaphores.
 *
 *  Spinlocks
 *  ---------
 *  GlobalMid_Lock protects:
 *	list operations on pending_mid_q and oplockQ
 *      updates to XID counters, multiplex id  and SMB sequence numbers
 *      list operations on global DnotअगरyReqList
 *  tcp_ses_lock protects:
 *	list operations on tcp and SMB session lists
 *  tcon->खोलो_file_lock protects the list of खोलो files hanging off the tcon
 *  inode->खोलो_file_lock protects the खोलोFileList hanging off the inode
 *  cfile->file_info_lock protects counters and fields in cअगरs file काष्ठा
 *  f_owner.lock protects certain per file काष्ठा operations
 *  mapping->page_lock protects certain per page operations
 *
 *  Note that the cअगरs_tcon.खोलो_file_lock should be taken beक्रमe
 *  not after the cअगरsInodeInfo.खोलो_file_lock
 *
 *  Semaphores
 *  ----------
 *  cअगरsInodeInfo->lock_sem protects:
 *	the list of locks held by the inode
 *
 ****************************************************************************/

#अगर_घोषित DECLARE_GLOBALS_HERE
#घोषणा GLOBAL_EXTERN
#अन्यथा
#घोषणा GLOBAL_EXTERN बाह्य
#पूर्ण_अगर

/*
 * the list of TCP_Server_Info काष्ठाures, ie each of the sockets
 * connecting our client to a distinct server (ip address), is
 * chained together by cअगरs_tcp_ses_list. The list of all our SMB
 * sessions (and from that the tree connections) can be found
 * by iterating over cअगरs_tcp_ses_list
 */
GLOBAL_EXTERN काष्ठा list_head		cअगरs_tcp_ses_list;

/*
 * This lock protects the cअगरs_tcp_ses_list, the list of smb sessions per
 * tcp session, and the list of tcon's per smb session. It also protects
 * the reference counters क्रम the server, smb session, and tcon. It also
 * protects some fields in the TCP_Server_Info काष्ठा such as dstaddr. Finally,
 * changes to the tcon->tidStatus should be करोne जबतक holding this lock.
 * generally the locks should be taken in order tcp_ses_lock beक्रमe
 * tcon->खोलो_file_lock and that beक्रमe file->file_info_lock since the
 * काष्ठाure order is cअगरs_socket-->cअगरs_ses-->cअगरs_tcon-->cअगरs_file
 */
GLOBAL_EXTERN spinlock_t		cअगरs_tcp_ses_lock;

/*
 * Global transaction id (XID) inक्रमmation
 */
GLOBAL_EXTERN अचिन्हित पूर्णांक GlobalCurrentXid;	/* रक्षित by GlobalMid_Sem */
GLOBAL_EXTERN अचिन्हित पूर्णांक GlobalTotalActiveXid; /* prot by GlobalMid_Sem */
GLOBAL_EXTERN अचिन्हित पूर्णांक GlobalMaxActiveXid;	/* prot by GlobalMid_Sem */
GLOBAL_EXTERN spinlock_t GlobalMid_Lock;  /* protects above & list operations */
					  /* on midQ entries */
/*
 *  Global counters, updated atomically
 */
GLOBAL_EXTERN atomic_t sesInfoAllocCount;
GLOBAL_EXTERN atomic_t tconInfoAllocCount;
GLOBAL_EXTERN atomic_t tcpSesNextId;
GLOBAL_EXTERN atomic_t tcpSesAllocCount;
GLOBAL_EXTERN atomic_t tcpSesReconnectCount;
GLOBAL_EXTERN atomic_t tconInfoReconnectCount;

/* Various Debug counters */
GLOBAL_EXTERN atomic_t bufAllocCount;    /* current number allocated  */
#अगर_घोषित CONFIG_CIFS_STATS2
GLOBAL_EXTERN atomic_t totBufAllocCount; /* total allocated over all समय */
GLOBAL_EXTERN atomic_t totSmBufAllocCount;
बाह्य अचिन्हित पूर्णांक slow_rsp_threshold; /* number of secs beक्रमe logging */
#पूर्ण_अगर
GLOBAL_EXTERN atomic_t smBufAllocCount;
GLOBAL_EXTERN atomic_t midCount;

/* Misc globals */
बाह्य bool enable_oplocks; /* enable or disable oplocks */
बाह्य bool lookupCacheEnabled;
बाह्य अचिन्हित पूर्णांक global_secflags;	/* अगर on, session setup sent
				with more secure ntlmssp2 challenge/resp */
बाह्य अचिन्हित पूर्णांक sign_CIFS_PDUs;  /* enable smb packet signing */
बाह्य bool enable_gcm_256; /* allow optional negotiate of strongest signing (aes-gcm-256) */
बाह्य bool require_gcm_256; /* require use of strongest signing (aes-gcm-256) */
बाह्य bool linuxExtEnabled;/*enable Linux/Unix CIFS extensions*/
बाह्य अचिन्हित पूर्णांक CIFSMaxBufSize;  /* max size not including hdr */
बाह्य अचिन्हित पूर्णांक cअगरs_min_rcv;    /* min size of big ntwrk buf pool */
बाह्य अचिन्हित पूर्णांक cअगरs_min_small;  /* min size of small buf pool */
बाह्य अचिन्हित पूर्णांक cअगरs_max_pending; /* MAX requests at once to server*/
बाह्य bool disable_legacy_dialects;  /* क्रमbid vers=1.0 and vers=2.0 mounts */

व्योम cअगरs_oplock_अवरोध(काष्ठा work_काष्ठा *work);
व्योम cअगरs_queue_oplock_अवरोध(काष्ठा cअगरsFileInfo *cfile);
व्योम smb2_deferred_work_बंद(काष्ठा work_काष्ठा *work);

बाह्य स्थिर काष्ठा slow_work_ops cअगरs_oplock_अवरोध_ops;
बाह्य काष्ठा workqueue_काष्ठा *cअगरsiod_wq;
बाह्य काष्ठा workqueue_काष्ठा *decrypt_wq;
बाह्य काष्ठा workqueue_काष्ठा *fileinfo_put_wq;
बाह्य काष्ठा workqueue_काष्ठा *cअगरsoplockd_wq;
बाह्य काष्ठा workqueue_काष्ठा *deferredबंद_wq;
बाह्य __u32 cअगरs_lock_secret;

बाह्य mempool_t *cअगरs_mid_poolp;

/* Operations क्रम dअगरferent SMB versions */
#घोषणा SMB1_VERSION_STRING	"1.0"
बाह्य काष्ठा smb_version_operations smb1_operations;
बाह्य काष्ठा smb_version_values smb1_values;
#घोषणा SMB20_VERSION_STRING	"2.0"
बाह्य काष्ठा smb_version_operations smb20_operations;
बाह्य काष्ठा smb_version_values smb20_values;
#घोषणा SMB21_VERSION_STRING	"2.1"
बाह्य काष्ठा smb_version_operations smb21_operations;
बाह्य काष्ठा smb_version_values smb21_values;
#घोषणा SMBDEFAULT_VERSION_STRING "default"
बाह्य काष्ठा smb_version_values smbशेष_values;
#घोषणा SMB3ANY_VERSION_STRING "3"
बाह्य काष्ठा smb_version_values smb3any_values;
#घोषणा SMB30_VERSION_STRING	"3.0"
बाह्य काष्ठा smb_version_operations smb30_operations;
बाह्य काष्ठा smb_version_values smb30_values;
#घोषणा SMB302_VERSION_STRING	"3.02"
#घोषणा ALT_SMB302_VERSION_STRING "3.0.2"
/*बाह्य काष्ठा smb_version_operations smb302_operations;*/ /* not needed yet */
बाह्य काष्ठा smb_version_values smb302_values;
#घोषणा SMB311_VERSION_STRING	"3.1.1"
#घोषणा ALT_SMB311_VERSION_STRING "3.11"
बाह्य काष्ठा smb_version_operations smb311_operations;
बाह्य काष्ठा smb_version_values smb311_values;

अटल अंतरभूत अक्षर *get_security_type_str(क्रमागत securityEnum sectype)
अणु
	चयन (sectype) अणु
	हाल RawNTLMSSP:
		वापस "RawNTLMSSP";
	हाल Kerberos:
		वापस "Kerberos";
	हाल NTLMv2:
		वापस "NTLMv2";
	हाल NTLM:
		वापस "NTLM";
	हाल LANMAN:
		वापस "LANMAN";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_smb1_server(काष्ठा TCP_Server_Info *server)
अणु
	वापस म_भेद(server->vals->version_string, SMB1_VERSION_STRING) == 0;
पूर्ण

अटल अंतरभूत bool is_tcon_dfs(काष्ठा cअगरs_tcon *tcon)
अणु
	/*
	 * For SMB1, see MS-CIFS 2.4.55 SMB_COM_TREE_CONNECT_ANDX (0x75) and MS-CIFS 3.3.4.4 DFS
	 * Subप्रणाली Notअगरies That a Share Is a DFS Share.
	 *
	 * For SMB2+, see MS-SMB2 2.2.10 SMB2 TREE_CONNECT Response and MS-SMB2 3.3.4.14 Server
	 * Application Updates a Share.
	 */
	अगर (!tcon || !tcon->ses || !tcon->ses->server)
		वापस false;
	वापस is_smb1_server(tcon->ses->server) ? tcon->Flags & SMB_SHARE_IS_IN_DFS :
		tcon->share_flags & (SHI1005_FLAGS_DFS | SHI1005_FLAGS_DFS_ROOT);
पूर्ण

#पूर्ण_अगर	/* _CIFS_GLOB_H */
