<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NFS पूर्णांकernal definitions
 */

#समावेश "nfs4_fs.h"
#समावेश <linux/fs_context.h>
#समावेश <linux/security.h>
#समावेश <linux/crc32.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/रुको_bit.h>

#घोषणा NFS_SB_MASK (SB_RDONLY|SB_NOSUID|SB_NODEV|SB_NOEXEC|SB_SYNCHRONOUS)

बाह्य स्थिर काष्ठा export_operations nfs_export_ops;

काष्ठा nfs_string;
काष्ठा nfs_pageio_descriptor;

अटल अंतरभूत व्योम nfs_attr_check_mountpoपूर्णांक(काष्ठा super_block *parent, काष्ठा nfs_fattr *fattr)
अणु
	अगर (!nfs_fsid_equal(&NFS_SB(parent)->fsid, &fattr->fsid))
		fattr->valid |= NFS_ATTR_FATTR_MOUNTPOINT;
पूर्ण

अटल अंतरभूत पूर्णांक nfs_attr_use_mounted_on_fileid(काष्ठा nfs_fattr *fattr)
अणु
	अगर (((fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID) == 0) ||
	    (((fattr->valid & NFS_ATTR_FATTR_MOUNTPOINT) == 0) &&
	     ((fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) == 0)))
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत bool nfs_lookup_is_soft_revalidate(स्थिर काष्ठा dentry *dentry)
अणु
	अगर (!(NFS_SB(dentry->d_sb)->flags & NFS_MOUNT_SOFTREVAL))
		वापस false;
	अगर (!d_is_positive(dentry) || !NFS_FH(d_inode(dentry))->size)
		वापस false;
	वापस true;
पूर्ण

/*
 * Note: RFC 1813 करोesn't limit the number of auth flavors that
 * a server can वापस, so make something up.
 */
#घोषणा NFS_MAX_SECFLAVORS	(12)

/*
 * Value used अगर the user did not specअगरy a port value.
 */
#घोषणा NFS_UNSPEC_PORT		(-1)

#घोषणा NFS_UNSPEC_RETRANS	(अच_पूर्णांक_उच्च)
#घोषणा NFS_UNSPEC_TIMEO	(अच_पूर्णांक_उच्च)

काष्ठा nfs_client_initdata अणु
	अचिन्हित दीर्घ init_flags;
	स्थिर अक्षर *hostname;			/* Hostname of the server */
	स्थिर काष्ठा sockaddr *addr;		/* Address of the server */
	स्थिर अक्षर *nodename;			/* Hostname of the client */
	स्थिर अक्षर *ip_addr;			/* IP address of the client */
	माप_प्रकार addrlen;
	काष्ठा nfs_subversion *nfs_mod;
	पूर्णांक proto;
	u32 minorversion;
	अचिन्हित पूर्णांक nconnect;
	काष्ठा net *net;
	स्थिर काष्ठा rpc_समयout *समयparms;
	स्थिर काष्ठा cred *cred;
पूर्ण;

/*
 * In-kernel mount arguments
 */
काष्ठा nfs_fs_context अणु
	bool			पूर्णांकernal;
	bool			skip_reconfig_option_check;
	bool			need_mount;
	bool			sloppy;
	अचिन्हित पूर्णांक		flags;		/* NFSअणु,4पूर्ण_MOUNT_* flags */
	अचिन्हित पूर्णांक		rsize, wsize;
	अचिन्हित पूर्णांक		समयo, retrans;
	अचिन्हित पूर्णांक		acregmin, acregmax;
	अचिन्हित पूर्णांक		acdirmin, acdirmax;
	अचिन्हित पूर्णांक		namlen;
	अचिन्हित पूर्णांक		options;
	अचिन्हित पूर्णांक		bsize;
	काष्ठा nfs_auth_info	auth_info;
	rpc_authflavor_t	selected_flavor;
	अक्षर			*client_address;
	अचिन्हित पूर्णांक		version;
	अचिन्हित पूर्णांक		minorversion;
	अक्षर			*fscache_uniq;
	अचिन्हित लघु		protofamily;
	अचिन्हित लघु		mountfamily;
	bool			has_sec_mnt_opts;

	काष्ठा अणु
		जोड़ अणु
			काष्ठा sockaddr	address;
			काष्ठा sockaddr_storage	_address;
		पूर्ण;
		माप_प्रकार			addrlen;
		अक्षर			*hostname;
		u32			version;
		पूर्णांक			port;
		अचिन्हित लघु		protocol;
	पूर्ण mount_server;

	काष्ठा अणु
		जोड़ अणु
			काष्ठा sockaddr	address;
			काष्ठा sockaddr_storage	_address;
		पूर्ण;
		माप_प्रकार			addrlen;
		अक्षर			*hostname;
		अक्षर			*export_path;
		पूर्णांक			port;
		अचिन्हित लघु		protocol;
		अचिन्हित लघु		nconnect;
		अचिन्हित लघु		export_path_len;
	पूर्ण nfs_server;

	काष्ठा nfs_fh		*mntfh;
	काष्ठा nfs_server	*server;
	काष्ठा nfs_subversion	*nfs_mod;

	/* Inक्रमmation क्रम a cloned mount. */
	काष्ठा nfs_clone_mount अणु
		काष्ठा super_block	*sb;
		काष्ठा dentry		*dentry;
		काष्ठा nfs_fattr	*fattr;
		अचिन्हित पूर्णांक		inherited_bsize;
	पूर्ण clone_data;
पूर्ण;

#घोषणा nfs_errorf(fc, fmt, ...) ((fc)->log.log ?		\
	errorf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dprपूर्णांकk(fmt "\n", ## __VA_ARGS__); पूर्ण))

#घोषणा nfs_ख_त्रुटिf(fc, fac, fmt, ...) ((fc)->log.log ?		\
	errorf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dfprपूर्णांकk(fac, fmt "\n", ## __VA_ARGS__); पूर्ण))

#घोषणा nfs_invalf(fc, fmt, ...) ((fc)->log.log ?		\
	invalf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dprपूर्णांकk(fmt "\n", ## __VA_ARGS__);  -EINVAL; पूर्ण))

#घोषणा nfs_finvalf(fc, fac, fmt, ...) ((fc)->log.log ?		\
	invalf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dfprपूर्णांकk(fac, fmt "\n", ## __VA_ARGS__);  -EINVAL; पूर्ण))

#घोषणा nfs_warnf(fc, fmt, ...) ((fc)->log.log ?		\
	warnf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dprपूर्णांकk(fmt "\n", ## __VA_ARGS__); पूर्ण))

#घोषणा nfs_fwarnf(fc, fac, fmt, ...) ((fc)->log.log ?		\
	warnf(fc, fmt, ## __VA_ARGS__) :			\
	(अणु dfprपूर्णांकk(fac, fmt "\n", ## __VA_ARGS__); पूर्ण))

अटल अंतरभूत काष्ठा nfs_fs_context *nfs_fc2context(स्थिर काष्ठा fs_context *fc)
अणु
	वापस fc->fs_निजी;
पूर्ण

/* mount_clnt.c */
काष्ठा nfs_mount_request अणु
	काष्ठा sockaddr		*sap;
	माप_प्रकार			salen;
	अक्षर			*hostname;
	अक्षर			*dirpath;
	u32			version;
	अचिन्हित लघु		protocol;
	काष्ठा nfs_fh		*fh;
	पूर्णांक			noresvport;
	अचिन्हित पूर्णांक		*auth_flav_len;
	rpc_authflavor_t	*auth_flavs;
	काष्ठा net		*net;
पूर्ण;

बाह्य पूर्णांक nfs_mount(काष्ठा nfs_mount_request *info, पूर्णांक समयo, पूर्णांक retrans);
बाह्य व्योम nfs_umount(स्थिर काष्ठा nfs_mount_request *info);

/* client.c */
बाह्य स्थिर काष्ठा rpc_program nfs_program;
बाह्य व्योम nfs_clients_init(काष्ठा net *net);
बाह्य व्योम nfs_clients_निकास(काष्ठा net *net);
बाह्य काष्ठा nfs_client *nfs_alloc_client(स्थिर काष्ठा nfs_client_initdata *);
पूर्णांक nfs_create_rpc_client(काष्ठा nfs_client *, स्थिर काष्ठा nfs_client_initdata *, rpc_authflavor_t);
काष्ठा nfs_client *nfs_get_client(स्थिर काष्ठा nfs_client_initdata *);
पूर्णांक nfs_probe_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *, काष्ठा nfs_fattr *);
व्योम nfs_server_insert_lists(काष्ठा nfs_server *);
व्योम nfs_server_हटाओ_lists(काष्ठा nfs_server *);
व्योम nfs_init_समयout_values(काष्ठा rpc_समयout *to, पूर्णांक proto, पूर्णांक समयo, पूर्णांक retrans);
पूर्णांक nfs_init_server_rpcclient(काष्ठा nfs_server *, स्थिर काष्ठा rpc_समयout *t,
		rpc_authflavor_t);
काष्ठा nfs_server *nfs_alloc_server(व्योम);
व्योम nfs_server_copy_userdata(काष्ठा nfs_server *, काष्ठा nfs_server *);

बाह्य व्योम nfs_put_client(काष्ठा nfs_client *);
बाह्य व्योम nfs_मुक्त_client(काष्ठा nfs_client *);
बाह्य काष्ठा nfs_client *nfs4_find_client_ident(काष्ठा net *, पूर्णांक);
बाह्य काष्ठा nfs_client *
nfs4_find_client_sessionid(काष्ठा net *, स्थिर काष्ठा sockaddr *,
				काष्ठा nfs4_sessionid *, u32);
बाह्य काष्ठा nfs_server *nfs_create_server(काष्ठा fs_context *);
बाह्य काष्ठा nfs_server *nfs4_create_server(काष्ठा fs_context *);
बाह्य काष्ठा nfs_server *nfs4_create_referral_server(काष्ठा fs_context *);
बाह्य पूर्णांक nfs4_update_server(काष्ठा nfs_server *server, स्थिर अक्षर *hostname,
					काष्ठा sockaddr *sap, माप_प्रकार salen,
					काष्ठा net *net);
बाह्य व्योम nfs_मुक्त_server(काष्ठा nfs_server *server);
बाह्य काष्ठा nfs_server *nfs_clone_server(काष्ठा nfs_server *,
					   काष्ठा nfs_fh *,
					   काष्ठा nfs_fattr *,
					   rpc_authflavor_t);
बाह्य bool nfs_client_init_is_complete(स्थिर काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs_client_init_status(स्थिर काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs_रुको_client_init_complete(स्थिर काष्ठा nfs_client *clp);
बाह्य व्योम nfs_mark_client_पढ़ोy(काष्ठा nfs_client *clp, पूर्णांक state);
बाह्य काष्ठा nfs_client *nfs4_set_ds_client(काष्ठा nfs_server *mds_srv,
					     स्थिर काष्ठा sockaddr *ds_addr,
					     पूर्णांक ds_addrlen, पूर्णांक ds_proto,
					     अचिन्हित पूर्णांक ds_समयo,
					     अचिन्हित पूर्णांक ds_retrans,
					     u32 minor_version);
बाह्य काष्ठा rpc_clnt *nfs4_find_or_create_ds_client(काष्ठा nfs_client *,
						काष्ठा inode *);
बाह्य काष्ठा nfs_client *nfs3_set_ds_client(काष्ठा nfs_server *mds_srv,
			स्थिर काष्ठा sockaddr *ds_addr, पूर्णांक ds_addrlen,
			पूर्णांक ds_proto, अचिन्हित पूर्णांक ds_समयo,
			अचिन्हित पूर्णांक ds_retrans);
#अगर_घोषित CONFIG_PROC_FS
बाह्य पूर्णांक __init nfs_fs_proc_init(व्योम);
बाह्य व्योम nfs_fs_proc_निकास(व्योम);
बाह्य पूर्णांक nfs_fs_proc_net_init(काष्ठा net *net);
बाह्य व्योम nfs_fs_proc_net_निकास(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक nfs_fs_proc_net_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nfs_fs_proc_net_निकास(काष्ठा net *net)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक nfs_fs_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nfs_fs_proc_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/* callback_xdr.c */
बाह्य स्थिर काष्ठा svc_version nfs4_callback_version1;
बाह्य स्थिर काष्ठा svc_version nfs4_callback_version4;

/* fs_context.c */
बाह्य काष्ठा file_प्रणाली_type nfs_fs_type;

/* pagelist.c */
बाह्य पूर्णांक __init nfs_init_nfspagecache(व्योम);
बाह्य व्योम nfs_destroy_nfspagecache(व्योम);
बाह्य पूर्णांक __init nfs_init_पढ़ोpagecache(व्योम);
बाह्य व्योम nfs_destroy_पढ़ोpagecache(व्योम);
बाह्य पूर्णांक __init nfs_init_ग_लिखोpagecache(व्योम);
बाह्य व्योम nfs_destroy_ग_लिखोpagecache(व्योम);

बाह्य पूर्णांक __init nfs_init_directcache(व्योम);
बाह्य व्योम nfs_destroy_directcache(व्योम);
बाह्य व्योम nfs_pgheader_init(काष्ठा nfs_pageio_descriptor *desc,
			      काष्ठा nfs_pgio_header *hdr,
			      व्योम (*release)(काष्ठा nfs_pgio_header *hdr));
व्योम nfs_set_pgio_error(काष्ठा nfs_pgio_header *hdr, पूर्णांक error, loff_t pos);
पूर्णांक nfs_iocounter_रुको(काष्ठा nfs_lock_context *l_ctx);

बाह्य स्थिर काष्ठा nfs_pageio_ops nfs_pgio_rw_ops;
काष्ठा nfs_pgio_header *nfs_pgio_header_alloc(स्थिर काष्ठा nfs_rw_ops *);
व्योम nfs_pgio_header_मुक्त(काष्ठा nfs_pgio_header *);
पूर्णांक nfs_generic_pgio(काष्ठा nfs_pageio_descriptor *, काष्ठा nfs_pgio_header *);
पूर्णांक nfs_initiate_pgio(काष्ठा rpc_clnt *clnt, काष्ठा nfs_pgio_header *hdr,
		      स्थिर काष्ठा cred *cred, स्थिर काष्ठा nfs_rpc_ops *rpc_ops,
		      स्थिर काष्ठा rpc_call_ops *call_ops, पूर्णांक how, पूर्णांक flags);
व्योम nfs_मुक्त_request(काष्ठा nfs_page *req);
काष्ठा nfs_pgio_mirror *
nfs_pgio_current_mirror(काष्ठा nfs_pageio_descriptor *desc);

अटल अंतरभूत bool nfs_match_खोलो_context(स्थिर काष्ठा nfs_खोलो_context *ctx1,
		स्थिर काष्ठा nfs_खोलो_context *ctx2)
अणु
	वापस cred_fscmp(ctx1->cred, ctx2->cred) == 0 && ctx1->state == ctx2->state;
पूर्ण

/* nfs2xdr.c */
बाह्य स्थिर काष्ठा rpc_procinfo nfs_procedures[];
बाह्य पूर्णांक nfs2_decode_dirent(काष्ठा xdr_stream *,
				काष्ठा nfs_entry *, bool);

/* nfs3xdr.c */
बाह्य स्थिर काष्ठा rpc_procinfo nfs3_procedures[];
बाह्य पूर्णांक nfs3_decode_dirent(काष्ठा xdr_stream *,
				काष्ठा nfs_entry *, bool);

/* nfs4xdr.c */
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य पूर्णांक nfs4_decode_dirent(काष्ठा xdr_stream *,
				काष्ठा nfs_entry *, bool);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFS_V4_1
बाह्य स्थिर u32 nfs41_maxपढ़ो_overhead;
बाह्य स्थिर u32 nfs41_maxग_लिखो_overhead;
बाह्य स्थिर u32 nfs41_maxgetdevinfo_overhead;
#पूर्ण_अगर

/* nfs4proc.c */
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य स्थिर काष्ठा rpc_procinfo nfs4_procedures[];
#पूर्ण_अगर

#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
बाह्य काष्ठा nfs4_label *nfs4_label_alloc(काष्ठा nfs_server *server, gfp_t flags);
अटल अंतरभूत काष्ठा nfs4_label *
nfs4_label_copy(काष्ठा nfs4_label *dst, काष्ठा nfs4_label *src)
अणु
	अगर (!dst || !src)
		वापस शून्य;

	अगर (src->len > NFS4_MAXLABELLEN)
		वापस शून्य;

	dst->lfs = src->lfs;
	dst->pi = src->pi;
	dst->len = src->len;
	स_नकल(dst->label, src->label, src->len);

	वापस dst;
पूर्ण
अटल अंतरभूत व्योम nfs4_label_मुक्त(काष्ठा nfs4_label *label)
अणु
	अगर (label) अणु
		kमुक्त(label->label);
		kमुक्त(label);
	पूर्ण
	वापस;
पूर्ण

अटल अंतरभूत व्योम nfs_zap_label_cache_locked(काष्ठा nfs_inode *nfsi)
अणु
	अगर (nfs_server_capable(&nfsi->vfs_inode, NFS_CAP_SECURITY_LABEL))
		nfsi->cache_validity |= NFS_INO_INVALID_LABEL;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा nfs4_label *nfs4_label_alloc(काष्ठा nfs_server *server, gfp_t flags) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम nfs4_label_मुक्त(व्योम *label) अणुपूर्ण
अटल अंतरभूत व्योम nfs_zap_label_cache_locked(काष्ठा nfs_inode *nfsi)
अणु
पूर्ण
अटल अंतरभूत काष्ठा nfs4_label *
nfs4_label_copy(काष्ठा nfs4_label *dst, काष्ठा nfs4_label *src)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_SECURITY_LABEL */

/* proc.c */
व्योम nfs_बंद_context(काष्ठा nfs_खोलो_context *ctx, पूर्णांक is_sync);
बाह्य काष्ठा nfs_client *nfs_init_client(काष्ठा nfs_client *clp,
			   स्थिर काष्ठा nfs_client_initdata *);

/* dir.c */
बाह्य व्योम nfs_advise_use_सूची_पढ़ोplus(काष्ठा inode *dir);
बाह्य व्योम nfs_क्रमce_use_सूची_पढ़ोplus(काष्ठा inode *dir);
बाह्य अचिन्हित दीर्घ nfs_access_cache_count(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc);
बाह्य अचिन्हित दीर्घ nfs_access_cache_scan(काष्ठा shrinker *shrink,
					   काष्ठा shrink_control *sc);
काष्ठा dentry *nfs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
पूर्णांक nfs_create(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
	       umode_t, bool);
पूर्णांक nfs_सूची_गढ़ो(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
	      umode_t);
पूर्णांक nfs_सूची_हटाओ(काष्ठा inode *, काष्ठा dentry *);
पूर्णांक nfs_unlink(काष्ठा inode *, काष्ठा dentry *);
पूर्णांक nfs_symlink(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
		स्थिर अक्षर *);
पूर्णांक nfs_link(काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *);
पूर्णांक nfs_mknod(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *, umode_t,
	      dev_t);
पूर्णांक nfs_नाम(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
	       काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);

/* file.c */
पूर्णांक nfs_file_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync);
loff_t nfs_file_llseek(काष्ठा file *, loff_t, पूर्णांक);
sमाप_प्रकार nfs_file_पढ़ो(काष्ठा kiocb *, काष्ठा iov_iter *);
पूर्णांक nfs_file_mmap(काष्ठा file *, काष्ठा vm_area_काष्ठा *);
sमाप_प्रकार nfs_file_ग_लिखो(काष्ठा kiocb *, काष्ठा iov_iter *);
पूर्णांक nfs_file_release(काष्ठा inode *, काष्ठा file *);
पूर्णांक nfs_lock(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
पूर्णांक nfs_flock(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
पूर्णांक nfs_check_flags(पूर्णांक);

/* inode.c */
बाह्य काष्ठा workqueue_काष्ठा *nfsiod_workqueue;
बाह्य काष्ठा inode *nfs_alloc_inode(काष्ठा super_block *sb);
बाह्य व्योम nfs_मुक्त_inode(काष्ठा inode *);
बाह्य पूर्णांक nfs_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक nfs_drop_inode(काष्ठा inode *);
बाह्य व्योम nfs_clear_inode(काष्ठा inode *);
बाह्य व्योम nfs_evict_inode(काष्ठा inode *);
बाह्य व्योम nfs_zap_acl_cache(काष्ठा inode *inode);
बाह्य व्योम nfs_set_cache_invalid(काष्ठा inode *inode, अचिन्हित दीर्घ flags);
बाह्य bool nfs_check_cache_invalid(काष्ठा inode *, अचिन्हित दीर्घ);
बाह्य पूर्णांक nfs_रुको_bit_समाप्तable(काष्ठा रुको_bit_key *key, पूर्णांक mode);
बाह्य पूर्णांक nfs_रुको_atomic_समाप्तable(atomic_t *p, अचिन्हित पूर्णांक mode);

/* super.c */
बाह्य स्थिर काष्ठा super_operations nfs_sops;
bool nfs_auth_info_match(स्थिर काष्ठा nfs_auth_info *, rpc_authflavor_t);
पूर्णांक nfs_try_get_tree(काष्ठा fs_context *);
पूर्णांक nfs_get_tree_common(काष्ठा fs_context *);
व्योम nfs_समाप्त_super(काष्ठा super_block *);

बाह्य काष्ठा rpc_stat nfs_rpcstat;

बाह्य पूर्णांक __init रेजिस्टर_nfs_fs(व्योम);
बाह्य व्योम __निकास unरेजिस्टर_nfs_fs(व्योम);
बाह्य bool nfs_sb_active(काष्ठा super_block *sb);
बाह्य व्योम nfs_sb_deactive(काष्ठा super_block *sb);
बाह्य पूर्णांक nfs_client_क्रम_each_server(काष्ठा nfs_client *clp,
				      पूर्णांक (*fn)(काष्ठा nfs_server *, व्योम *),
				      व्योम *data);
/* io.c */
बाह्य व्योम nfs_start_io_पढ़ो(काष्ठा inode *inode);
बाह्य व्योम nfs_end_io_पढ़ो(काष्ठा inode *inode);
बाह्य व्योम nfs_start_io_ग_लिखो(काष्ठा inode *inode);
बाह्य व्योम nfs_end_io_ग_लिखो(काष्ठा inode *inode);
बाह्य व्योम nfs_start_io_direct(काष्ठा inode *inode);
बाह्य व्योम nfs_end_io_direct(काष्ठा inode *inode);

अटल अंतरभूत bool nfs_file_io_is_buffered(काष्ठा nfs_inode *nfsi)
अणु
	वापस test_bit(NFS_INO_OसूचीECT, &nfsi->flags) == 0;
पूर्ण

/* namespace.c */
#घोषणा NFS_PATH_CANONICAL 1
बाह्य अक्षर *nfs_path(अक्षर **p, काष्ठा dentry *dentry,
		      अक्षर *buffer, sमाप_प्रकार buflen, अचिन्हित flags);
बाह्य काष्ठा vfsmount *nfs_d_स्वतःmount(काष्ठा path *path);
पूर्णांक nfs_submount(काष्ठा fs_context *, काष्ठा nfs_server *);
पूर्णांक nfs_करो_submount(काष्ठा fs_context *);

/* getroot.c */
बाह्य पूर्णांक nfs_get_root(काष्ठा super_block *s, काष्ठा fs_context *fc);
#अगर IS_ENABLED(CONFIG_NFS_V4)
बाह्य पूर्णांक nfs4_get_rootfh(काष्ठा nfs_server *server, काष्ठा nfs_fh *mntfh, bool);
#पूर्ण_अगर

काष्ठा nfs_pgio_completion_ops;
/* पढ़ो.c */
बाह्य व्योम nfs_pageio_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
			काष्ठा inode *inode, bool क्रमce_mds,
			स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops);
बाह्य व्योम nfs_पढ़ो_prepare(काष्ठा rpc_task *task, व्योम *calldata);
बाह्य व्योम nfs_pageio_reset_पढ़ो_mds(काष्ठा nfs_pageio_descriptor *pgio);

/* super.c */
व्योम nfs_umount_begin(काष्ठा super_block *);
पूर्णांक  nfs_statfs(काष्ठा dentry *, काष्ठा kstatfs *);
पूर्णांक  nfs_show_options(काष्ठा seq_file *, काष्ठा dentry *);
पूर्णांक  nfs_show_devname(काष्ठा seq_file *, काष्ठा dentry *);
पूर्णांक  nfs_show_path(काष्ठा seq_file *, काष्ठा dentry *);
पूर्णांक  nfs_show_stats(काष्ठा seq_file *, काष्ठा dentry *);
पूर्णांक  nfs_reconfigure(काष्ठा fs_context *);

/* ग_लिखो.c */
बाह्य व्योम nfs_pageio_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			काष्ठा inode *inode, पूर्णांक ioflags, bool क्रमce_mds,
			स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops);
बाह्य व्योम nfs_pageio_reset_ग_लिखो_mds(काष्ठा nfs_pageio_descriptor *pgio);
बाह्य व्योम nfs_commit_मुक्त(काष्ठा nfs_commit_data *p);
बाह्य व्योम nfs_ग_लिखो_prepare(काष्ठा rpc_task *task, व्योम *calldata);
बाह्य व्योम nfs_commit_prepare(काष्ठा rpc_task *task, व्योम *calldata);
बाह्य पूर्णांक nfs_initiate_commit(काष्ठा rpc_clnt *clnt,
			       काष्ठा nfs_commit_data *data,
			       स्थिर काष्ठा nfs_rpc_ops *nfs_ops,
			       स्थिर काष्ठा rpc_call_ops *call_ops,
			       पूर्णांक how, पूर्णांक flags);
बाह्य व्योम nfs_init_commit(काष्ठा nfs_commit_data *data,
			    काष्ठा list_head *head,
			    काष्ठा pnfs_layout_segment *lseg,
			    काष्ठा nfs_commit_info *cinfo);
पूर्णांक nfs_scan_commit_list(काष्ठा list_head *src, काष्ठा list_head *dst,
			 काष्ठा nfs_commit_info *cinfo, पूर्णांक max);
अचिन्हित दीर्घ nfs_reqs_to_commit(काष्ठा nfs_commit_info *);
पूर्णांक nfs_scan_commit(काष्ठा inode *inode, काष्ठा list_head *dst,
		    काष्ठा nfs_commit_info *cinfo);
व्योम nfs_mark_request_commit(काष्ठा nfs_page *req,
			     काष्ठा pnfs_layout_segment *lseg,
			     काष्ठा nfs_commit_info *cinfo,
			     u32 ds_commit_idx);
पूर्णांक nfs_ग_लिखो_need_commit(काष्ठा nfs_pgio_header *);
व्योम nfs_ग_लिखोback_update_inode(काष्ठा nfs_pgio_header *hdr);
पूर्णांक nfs_generic_commit_list(काष्ठा inode *inode, काष्ठा list_head *head,
			    पूर्णांक how, काष्ठा nfs_commit_info *cinfo);
व्योम nfs_retry_commit(काष्ठा list_head *page_list,
		      काष्ठा pnfs_layout_segment *lseg,
		      काष्ठा nfs_commit_info *cinfo,
		      u32 ds_commit_idx);
व्योम nfs_commitdata_release(काष्ठा nfs_commit_data *data);
व्योम nfs_request_add_commit_list(काष्ठा nfs_page *req,
				 काष्ठा nfs_commit_info *cinfo);
व्योम nfs_request_add_commit_list_locked(काष्ठा nfs_page *req,
		काष्ठा list_head *dst,
		काष्ठा nfs_commit_info *cinfo);
व्योम nfs_request_हटाओ_commit_list(काष्ठा nfs_page *req,
				    काष्ठा nfs_commit_info *cinfo);
व्योम nfs_init_cinfo(काष्ठा nfs_commit_info *cinfo,
		    काष्ठा inode *inode,
		    काष्ठा nfs_direct_req *dreq);
पूर्णांक nfs_key_समयout_notअगरy(काष्ठा file *filp, काष्ठा inode *inode);
bool nfs_ctx_key_to_expire(काष्ठा nfs_खोलो_context *ctx, काष्ठा inode *inode);
व्योम nfs_pageio_stop_mirroring(काष्ठा nfs_pageio_descriptor *pgio);

पूर्णांक nfs_filemap_ग_लिखो_and_रुको_range(काष्ठा address_space *mapping,
		loff_t lstart, loff_t lend);

#अगर_घोषित CONFIG_NFS_V4_1
अटल अंतरभूत व्योम
pnfs_bucket_clear_pnfs_ds_commit_verअगरiers(काष्ठा pnfs_commit_bucket *buckets,
		अचिन्हित पूर्णांक nbuckets)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nbuckets; i++)
		buckets[i].direct_verf.committed = NFS_INVALID_STABLE_HOW;
पूर्ण
अटल अंतरभूत
व्योम nfs_clear_pnfs_ds_commit_verअगरiers(काष्ठा pnfs_ds_commit_info *cinfo)
अणु
	काष्ठा pnfs_commit_array *array;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(array, &cinfo->commits, cinfo_list)
		pnfs_bucket_clear_pnfs_ds_commit_verअगरiers(array->buckets,
				array->nbuckets);
	rcu_पढ़ो_unlock();
पूर्ण
#अन्यथा
अटल अंतरभूत
व्योम nfs_clear_pnfs_ds_commit_verअगरiers(काष्ठा pnfs_ds_commit_info *cinfo)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIGRATION
बाह्य पूर्णांक nfs_migrate_page(काष्ठा address_space *,
		काष्ठा page *, काष्ठा page *, क्रमागत migrate_mode);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
nfs_ग_लिखो_verअगरier_cmp(स्थिर काष्ठा nfs_ग_लिखो_verअगरier *v1,
		स्थिर काष्ठा nfs_ग_लिखो_verअगरier *v2)
अणु
	वापस स_भेद(v1->data, v2->data, माप(v1->data));
पूर्ण

अटल अंतरभूत bool
nfs_ग_लिखो_match_verf(स्थिर काष्ठा nfs_ग_लिखोverf *verf,
		काष्ठा nfs_page *req)
अणु
	वापस verf->committed > NFS_UNSTABLE &&
		!nfs_ग_लिखो_verअगरier_cmp(&req->wb_verf, &verf->verअगरier);
पूर्ण

/* unlink.c */
बाह्य काष्ठा rpc_task *
nfs_async_नाम(काष्ठा inode *old_dir, काष्ठा inode *new_dir,
		 काष्ठा dentry *old_dentry, काष्ठा dentry *new_dentry,
		 व्योम (*complete)(काष्ठा rpc_task *, काष्ठा nfs_नामdata *));
बाह्य पूर्णांक nfs_sillyनाम(काष्ठा inode *dir, काष्ठा dentry *dentry);

/* direct.c */
व्योम nfs_init_cinfo_from_dreq(काष्ठा nfs_commit_info *cinfo,
			      काष्ठा nfs_direct_req *dreq);
बाह्य sमाप_प्रकार nfs_dreq_bytes_left(काष्ठा nfs_direct_req *dreq);

/* nfs4proc.c */
बाह्य काष्ठा nfs_client *nfs4_init_client(काष्ठा nfs_client *clp,
			    स्थिर काष्ठा nfs_client_initdata *);
बाह्य पूर्णांक nfs40_walk_client_list(काष्ठा nfs_client *clp,
				काष्ठा nfs_client **result,
				स्थिर काष्ठा cred *cred);
बाह्य पूर्णांक nfs41_walk_client_list(काष्ठा nfs_client *clp,
				काष्ठा nfs_client **result,
				स्थिर काष्ठा cred *cred);
बाह्य व्योम nfs4_test_session_trunk(काष्ठा rpc_clnt *clnt,
				काष्ठा rpc_xprt *xprt,
				व्योम *data);

अटल अंतरभूत काष्ठा inode *nfs_igrab_and_active(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	अगर (sb && nfs_sb_active(sb)) अणु
		अगर (igrab(inode))
			वापस inode;
		nfs_sb_deactive(sb);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम nfs_iput_and_deactive(काष्ठा inode *inode)
अणु
	अगर (inode != शून्य) अणु
		काष्ठा super_block *sb = inode->i_sb;

		iput(inode);
		nfs_sb_deactive(sb);
	पूर्ण
पूर्ण

/*
 * Determine the device name as a string
 */
अटल अंतरभूत अक्षर *nfs_devname(काष्ठा dentry *dentry,
				अक्षर *buffer, sमाप_प्रकार buflen)
अणु
	अक्षर *dummy;
	वापस nfs_path(&dummy, dentry, buffer, buflen, NFS_PATH_CANONICAL);
पूर्ण

/*
 * Determine the actual block size (and log2 thereof)
 */
अटल अंतरभूत
अचिन्हित दीर्घ nfs_block_bits(अचिन्हित दीर्घ bsize, अचिन्हित अक्षर *nrbitsp)
अणु
	/* make sure blocksize is a घातer of two */
	अगर ((bsize & (bsize - 1)) || nrbitsp) अणु
		अचिन्हित अक्षर	nrbits;

		क्रम (nrbits = 31; nrbits && !(bsize & (1 << nrbits)); nrbits--)
			;
		bsize = 1 << nrbits;
		अगर (nrbitsp)
			*nrbitsp = nrbits;
	पूर्ण

	वापस bsize;
पूर्ण

/*
 * Calculate the number of 512byte blocks used.
 */
अटल अंतरभूत blkcnt_t nfs_calc_block_size(u64 tsize)
अणु
	blkcnt_t used = (tsize + 511) >> 9;
	वापस (used > अच_दीर्घ_उच्च) ? अच_दीर्घ_उच्च : used;
पूर्ण

/*
 * Compute and set NFS server blocksize
 */
अटल अंतरभूत
अचिन्हित दीर्घ nfs_block_size(अचिन्हित दीर्घ bsize, अचिन्हित अक्षर *nrbitsp)
अणु
	अगर (bsize < NFS_MIN_खाता_IO_SIZE)
		bsize = NFS_DEF_खाता_IO_SIZE;
	अन्यथा अगर (bsize >= NFS_MAX_खाता_IO_SIZE)
		bsize = NFS_MAX_खाता_IO_SIZE;

	वापस nfs_block_bits(bsize, nrbitsp);
पूर्ण

/*
 * Determine the maximum file size क्रम a superblock
 */
अटल अंतरभूत
व्योम nfs_super_set_maxbytes(काष्ठा super_block *sb, __u64 maxfilesize)
अणु
	sb->s_maxbytes = (loff_t)maxfilesize;
	अगर (sb->s_maxbytes > MAX_LFS_खाताSIZE || sb->s_maxbytes <= 0)
		sb->s_maxbytes = MAX_LFS_खाताSIZE;
पूर्ण

/*
 * Record the page as unstable (an extra ग_लिखोback period) and mark its
 * inode as dirty.
 */
अटल अंतरभूत
व्योम nfs_mark_page_unstable(काष्ठा page *page, काष्ठा nfs_commit_info *cinfo)
अणु
	अगर (!cinfo->dreq) अणु
		काष्ठा inode *inode = page_file_mapping(page)->host;

		/* This page is really still in ग_लिखो-back - just that the
		 * ग_लिखोback is happening on the server now.
		 */
		inc_node_page_state(page, NR_WRITEBACK);
		inc_wb_stat(&inode_to_bdi(inode)->wb, WB_WRITEBACK);
		__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);
	पूर्ण
पूर्ण

/*
 * Determine the number of bytes of data the page contains
 */
अटल अंतरभूत
अचिन्हित पूर्णांक nfs_page_length(काष्ठा page *page)
अणु
	loff_t i_size = i_size_पढ़ो(page_file_mapping(page)->host);

	अगर (i_size > 0) अणु
		pgoff_t index = page_index(page);
		pgoff_t end_index = (i_size - 1) >> PAGE_SHIFT;
		अगर (index < end_index)
			वापस PAGE_SIZE;
		अगर (index == end_index)
			वापस ((i_size - 1) & ~PAGE_MASK) + 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Convert a umode to a dirent->d_type
 */
अटल अंतरभूत
अचिन्हित अक्षर nfs_umode_to_dtype(umode_t mode)
अणु
	वापस (mode >> 12) & 15;
पूर्ण

/*
 * Determine the number of pages in an array of length 'len' and
 * with a base offset of 'base'
 */
अटल अंतरभूत
अचिन्हित पूर्णांक nfs_page_array_len(अचिन्हित पूर्णांक base, माप_प्रकार len)
अणु
	वापस ((अचिन्हित दीर्घ)len + (अचिन्हित दीर्घ)base +
		PAGE_SIZE - 1) >> PAGE_SHIFT;
पूर्ण

/*
 * Convert a काष्ठा बारpec64 पूर्णांकo a 64-bit change attribute
 *
 * This करोes approximately the same thing as बारpec64_to_ns(),
 * but क्रम calculation efficiency, we multiply the seconds by
 * 1024*1024*1024.
 */
अटल अंतरभूत
u64 nfs_बारpec_to_change_attr(स्थिर काष्ठा बारpec64 *ts)
अणु
	वापस ((u64)ts->tv_sec << 30) + ts->tv_nsec;
पूर्ण

#अगर_घोषित CONFIG_CRC32
/**
 * nfs_fhandle_hash - calculate the crc32 hash क्रम the filehandle
 * @fh - poपूर्णांकer to filehandle
 *
 * वापसs a crc32 hash क्रम the filehandle that is compatible with
 * the one displayed by "wireshark".
 */
अटल अंतरभूत u32 nfs_fhandle_hash(स्थिर काष्ठा nfs_fh *fh)
अणु
	वापस ~crc32_le(0xFFFFFFFF, &fh->data[0], fh->size);
पूर्ण
अटल अंतरभूत u32 nfs_stateid_hash(स्थिर nfs4_stateid *stateid)
अणु
	वापस ~crc32_le(0xFFFFFFFF, &stateid->other[0],
				NFS4_STATEID_OTHER_SIZE);
पूर्ण
#अन्यथा
अटल अंतरभूत u32 nfs_fhandle_hash(स्थिर काष्ठा nfs_fh *fh)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u32 nfs_stateid_hash(nfs4_stateid *stateid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool nfs_error_is_fatal(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -ERESTARTSYS:
	हाल -EINTR:
	हाल -EACCES:
	हाल -EDQUOT:
	हाल -EFBIG:
	हाल -EIO:
	हाल -ENOSPC:
	हाल -EROFS:
	हाल -ESTALE:
	हाल -E2BIG:
	हाल -ENOMEM:
	हाल -ETIMEDOUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool nfs_error_is_fatal_on_server(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल 0:
	हाल -ERESTARTSYS:
	हाल -EINTR:
		वापस false;
	पूर्ण
	वापस nfs_error_is_fatal(err);
पूर्ण

/*
 * Select between a शेष port value and a user-specअगरied port value.
 * If a zero value is set, then स्वतःbind will be used.
 */
अटल अंतरभूत व्योम nfs_set_port(काष्ठा sockaddr *sap, पूर्णांक *port,
				स्थिर अचिन्हित लघु शेष_port)
अणु
	अगर (*port == NFS_UNSPEC_PORT)
		*port = शेष_port;

	rpc_set_port(sap, *port);
पूर्ण
