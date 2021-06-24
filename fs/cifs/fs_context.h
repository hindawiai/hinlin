<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) 2020, Microsoft Corporation.
 *
 *   Author(s): Steve French <stfrench@microsoft.com>
 *              David Howells <dhowells@redhat.com>
 */

#अगर_अघोषित _FS_CONTEXT_H
#घोषणा _FS_CONTEXT_H

#समावेश "cifsglob.h"
#समावेश <linux/parser.h>
#समावेश <linux/fs_parser.h>

/* Log errors in fs_context (new mount api) but also in dmesg (old style) */
#घोषणा cअगरs_errorf(fc, fmt, ...)			\
	करो अणु						\
		errorf(fc, fmt, ## __VA_ARGS__);	\
		cअगरs_dbg(VFS, fmt, ## __VA_ARGS__);	\
	पूर्ण जबतक (0)

क्रमागत smb_version अणु
	Smb_1 = 1,
	Smb_20,
	Smb_21,
	Smb_30,
	Smb_302,
	Smb_311,
	Smb_3any,
	Smb_शेष,
	Smb_version_err
पूर्ण;

क्रमागत अणु
	Opt_cache_loose,
	Opt_cache_strict,
	Opt_cache_none,
	Opt_cache_ro,
	Opt_cache_rw,
	Opt_cache_err
पूर्ण;

क्रमागत cअगरs_sec_param अणु
	Opt_sec_krb5,
	Opt_sec_krb5i,
	Opt_sec_krb5p,
	Opt_sec_ntlmsspi,
	Opt_sec_ntlmssp,
	Opt_ntlm,
	Opt_sec_ntlmi,
	Opt_sec_ntlmv2,
	Opt_sec_ntlmv2i,
	Opt_sec_lanman,
	Opt_sec_none,

	Opt_sec_err
पूर्ण;

क्रमागत cअगरs_param अणु
	/* Mount options that take no arguments */
	Opt_user_xattr,
	Opt_क्रमceuid,
	Opt_क्रमcegid,
	Opt_noblocksend,
	Opt_noस्वतःtune,
	Opt_nolease,
	Opt_hard,
	Opt_soft,
	Opt_perm,
	Opt_nodelete,
	Opt_mapposix,
	Opt_mapअक्षरs,
	Opt_nomapअक्षरs,
	Opt_sfu,
	Opt_nodfs,
	Opt_posixpaths,
	Opt_unix,
	Opt_noहाल,
	Opt_brl,
	Opt_handlecache,
	Opt_क्रमcemandatorylock,
	Opt_setuidfromacl,
	Opt_setuids,
	Opt_dynperm,
	Opt_पूर्णांकr,
	Opt_strictsync,
	Opt_serverino,
	Opt_rwpidक्रमward,
	Opt_cअगरsacl,
	Opt_acl,
	Opt_locallease,
	Opt_sign,
	Opt_ignore_signature,
	Opt_seal,
	Opt_noac,
	Opt_fsc,
	Opt_mfsymlinks,
	Opt_multiuser,
	Opt_sloppy,
	Opt_nosharesock,
	Opt_persistent,
	Opt_resilient,
	Opt_करोमुख्यस्वतः,
	Opt_rdma,
	Opt_modesid,
	Opt_rootfs,
	Opt_multichannel,
	Opt_compress,
	Opt_witness,

	/* Mount options which take numeric value */
	Opt_backupuid,
	Opt_backupgid,
	Opt_uid,
	Opt_cruid,
	Opt_gid,
	Opt_port,
	Opt_file_mode,
	Opt_dirmode,
	Opt_min_enc_offload,
	Opt_blocksize,
	Opt_rasize,
	Opt_rsize,
	Opt_wsize,
	Opt_aस_समयo,
	Opt_acdirmax,
	Opt_acregmax,
	Opt_echo_पूर्णांकerval,
	Opt_max_credits,
	Opt_snapshot,
	Opt_max_channels,
	Opt_handleसमयout,

	/* Mount options which take string value */
	Opt_source,
	Opt_user,
	Opt_pass,
	Opt_ip,
	Opt_करोमुख्य,
	Opt_srcaddr,
	Opt_ioअक्षरset,
	Opt_netbiosname,
	Opt_servern,
	Opt_ver,
	Opt_vers,
	Opt_sec,
	Opt_cache,

	/* Mount options to be ignored */
	Opt_ignore,

	Opt_err
पूर्ण;

काष्ठा smb3_fs_context अणु
	bool uid_specअगरied;
	bool gid_specअगरied;
	bool sloppy;
	bool got_ip;
	bool got_version;
	bool got_rsize;
	bool got_wsize;
	bool got_bsize;
	अचिन्हित लघु port;

	अक्षर *username;
	अक्षर *password;
	अक्षर *करोमुख्यname;
	अक्षर *source;
	अक्षर *UNC;
	अक्षर *nodename;
	अक्षर *ioअक्षरset;  /* local code page क्रम mapping to and from Unicode */
	अक्षर source_rfc1001_name[RFC1001_NAME_LEN_WITH_शून्य]; /* clnt nb name */
	अक्षर target_rfc1001_name[RFC1001_NAME_LEN_WITH_शून्य]; /* srvr nb name */
	kuid_t cred_uid;
	kuid_t linux_uid;
	kgid_t linux_gid;
	kuid_t backupuid;
	kgid_t backupgid;
	umode_t file_mode;
	umode_t dir_mode;
	क्रमागत securityEnum sectype; /* sectype requested via mnt opts */
	bool sign; /* was signing requested via mnt opts? */
	bool ignore_signature:1;
	bool retry:1;
	bool पूर्णांकr:1;
	bool setuids:1;
	bool setuidfromacl:1;
	bool override_uid:1;
	bool override_gid:1;
	bool dynperm:1;
	bool noperm:1;
	bool nodelete:1;
	bool mode_ace:1;
	bool no_psx_acl:1; /* set अगर posix acl support should be disabled */
	bool cअगरs_acl:1;
	bool backupuid_specअगरied; /* mount option  backupuid  is specअगरied */
	bool backupgid_specअगरied; /* mount option  backupgid  is specअगरied */
	bool no_xattr:1;   /* set अगर xattr (EA) support should be disabled*/
	bool server_ino:1; /* use inode numbers from server ie UniqueId */
	bool direct_io:1;
	bool strict_io:1; /* strict cache behavior */
	bool cache_ro:1;
	bool cache_rw:1;
	bool remap:1;      /* set to remap seven reserved अक्षरs in filenames */
	bool sfu_remap:1;  /* remap seven reserved अक्षरs ala SFU */
	bool posix_paths:1; /* unset to not ask क्रम posix pathnames. */
	bool no_linux_ext:1;
	bool linux_ext:1;
	bool sfu_emul:1;
	bool nullauth:1;   /* attempt to authenticate with null user */
	bool noहाल:1;     /* request हाल insensitive filenames */
	bool nobrl:1;      /* disable sending byte range locks to srv */
	bool nohandlecache:1; /* disable caching dir handles अगर srvr probs */
	bool mand_lock:1;  /* send mandatory not posix byte range lock reqs */
	bool seal:1;       /* request transport encryption on share */
	bool nodfs:1;      /* Do not request DFS, even अगर available */
	bool local_lease:1; /* check leases only on local प्रणाली, not remote */
	bool noblocksnd:1;
	bool noस्वतःtune:1;
	bool nostrictsync:1; /* करो not क्रमce expensive SMBflush on every sync */
	bool no_lease:1;     /* disable requesting leases */
	bool fsc:1;	/* enable fscache */
	bool mfsymlinks:1; /* use Minshall+French Symlinks */
	bool multiuser:1;
	bool rwpidक्रमward:1; /* pid क्रमward क्रम पढ़ो/ग_लिखो operations */
	bool nosharesock:1;
	bool persistent:1;
	bool nopersistent:1;
	bool resilient:1; /* noresilient not required since not क्रमed क्रम CA */
	bool करोमुख्यस्वतः:1;
	bool rdma:1;
	bool multichannel:1;
	bool use_client_guid:1;
	/* reuse existing guid क्रम multichannel */
	u8 client_guid[SMB2_CLIENT_GUID_SIZE];
	अचिन्हित पूर्णांक bsize;
	अचिन्हित पूर्णांक rasize;
	अचिन्हित पूर्णांक rsize;
	अचिन्हित पूर्णांक wsize;
	अचिन्हित पूर्णांक min_offload;
	bool sockopt_tcp_nodelay:1;
	/* attribute cache समयmout क्रम files and directories in jअगरfies */
	अचिन्हित दीर्घ acregmax;
	अचिन्हित दीर्घ acdirmax;
	काष्ठा smb_version_operations *ops;
	काष्ठा smb_version_values *vals;
	अक्षर *prepath;
	काष्ठा sockaddr_storage dstaddr; /* destination address */
	काष्ठा sockaddr_storage srcaddr; /* allow binding to a local IP */
	काष्ठा nls_table *local_nls; /* This is a copy of the poपूर्णांकer in cअगरs_sb */
	अचिन्हित पूर्णांक echo_पूर्णांकerval; /* echo पूर्णांकerval in secs */
	__u64 snapshot_समय; /* needed क्रम समयwarp tokens */
	__u32 handle_समयout; /* persistent and durable handle समयout in ms */
	अचिन्हित पूर्णांक max_credits; /* smb3 max_credits 10 < credits < 60000 */
	अचिन्हित पूर्णांक max_channels;
	__u16 compression; /* compression algorithm 0xFFFF शेष 0=disabled */
	bool rootfs:1; /* अगर it's a SMB root file प्रणाली */
	bool witness:1; /* use witness protocol */

	अक्षर *mount_options;
पूर्ण;

बाह्य स्थिर काष्ठा fs_parameter_spec smb3_fs_parameters[];

बाह्य पूर्णांक smb3_init_fs_context(काष्ठा fs_context *fc);
बाह्य व्योम smb3_cleanup_fs_context_contents(काष्ठा smb3_fs_context *ctx);
बाह्य व्योम smb3_cleanup_fs_context(काष्ठा smb3_fs_context *ctx);

अटल अंतरभूत काष्ठा smb3_fs_context *smb3_fc2context(स्थिर काष्ठा fs_context *fc)
अणु
	वापस fc->fs_निजी;
पूर्ण

बाह्य पूर्णांक smb3_fs_context_dup(काष्ठा smb3_fs_context *new_ctx, काष्ठा smb3_fs_context *ctx);
बाह्य व्योम smb3_update_mnt_flags(काष्ठा cअगरs_sb_info *cअगरs_sb);

#पूर्ण_अगर
