<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/nfs/super.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  nfs superblock handling functions
 *
 *  Modularised by Alan Cox <alan@lxorguk.ukuu.org.uk>, जबतक hacking some
 *  experimental NFS changes. Modularisation taken straight from SYS5 fs.
 *
 *  Change to nfs_पढ़ो_super() to permit NFS mounts to multi-homed hosts.
 *  J.S.Peatfield@damtp.cam.ac.uk
 *
 *  Split from inode.c by David Howells <dhowells@redhat.com>
 *
 * - superblocks are indexed on server only - all inodes, dentries, etc. associated with a
 *   particular server are held in the same superblock
 * - NFS superblocks can have several effective roots to the dentry tree
 * - directory type roots are spliced पूर्णांकo the tree when a path from one root reaches the root
 *   of another (see nfs_lookup())
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/sunrpc/xprtsock.h>
#समावेश <linux/sunrpc/xprtrdma.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/vfs.h>
#समावेश <linux/inet.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <net/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/magic.h>
#समावेश <linux/parser.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/rcupdate.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/nfs_ssc.h>

#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "iostat.h"
#समावेश "internal.h"
#समावेश "fscache.h"
#समावेश "nfs4session.h"
#समावेश "pnfs.h"
#समावेश "nfs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

स्थिर काष्ठा super_operations nfs_sops = अणु
	.alloc_inode	= nfs_alloc_inode,
	.मुक्त_inode	= nfs_मुक्त_inode,
	.ग_लिखो_inode	= nfs_ग_लिखो_inode,
	.drop_inode	= nfs_drop_inode,
	.statfs		= nfs_statfs,
	.evict_inode	= nfs_evict_inode,
	.umount_begin	= nfs_umount_begin,
	.show_options	= nfs_show_options,
	.show_devname	= nfs_show_devname,
	.show_path	= nfs_show_path,
	.show_stats	= nfs_show_stats,
पूर्ण;
EXPORT_SYMBOL_GPL(nfs_sops);

#अगर_घोषित CONFIG_NFS_V4_2
अटल स्थिर काष्ठा nfs_ssc_client_ops nfs_ssc_clnt_ops_tbl = अणु
	.sco_sb_deactive = nfs_sb_deactive,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल पूर्णांक __init रेजिस्टर_nfs4_fs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&nfs4_fs_type);
पूर्ण

अटल व्योम unरेजिस्टर_nfs4_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&nfs4_fs_type);
पूर्ण
#अन्यथा
अटल पूर्णांक __init रेजिस्टर_nfs4_fs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_nfs4_fs(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NFS_V4_2
अटल व्योम nfs_ssc_रेजिस्टर_ops(व्योम)
अणु
	nfs_ssc_रेजिस्टर(&nfs_ssc_clnt_ops_tbl);
पूर्ण

अटल व्योम nfs_ssc_unरेजिस्टर_ops(व्योम)
अणु
	nfs_ssc_unरेजिस्टर(&nfs_ssc_clnt_ops_tbl);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

अटल काष्ठा shrinker acl_shrinker = अणु
	.count_objects	= nfs_access_cache_count,
	.scan_objects	= nfs_access_cache_scan,
	.seeks		= DEFAULT_SEEKS,
पूर्ण;

/*
 * Register the NFS fileप्रणालीs
 */
पूर्णांक __init रेजिस्टर_nfs_fs(व्योम)
अणु
	पूर्णांक ret;

        ret = रेजिस्टर_fileप्रणाली(&nfs_fs_type);
	अगर (ret < 0)
		जाओ error_0;

	ret = रेजिस्टर_nfs4_fs();
	अगर (ret < 0)
		जाओ error_1;

	ret = nfs_रेजिस्टर_sysctl();
	अगर (ret < 0)
		जाओ error_2;
	ret = रेजिस्टर_shrinker(&acl_shrinker);
	अगर (ret < 0)
		जाओ error_3;
#अगर_घोषित CONFIG_NFS_V4_2
	nfs_ssc_रेजिस्टर_ops();
#पूर्ण_अगर
	वापस 0;
error_3:
	nfs_unरेजिस्टर_sysctl();
error_2:
	unरेजिस्टर_nfs4_fs();
error_1:
	unरेजिस्टर_fileप्रणाली(&nfs_fs_type);
error_0:
	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर the NFS fileप्रणालीs
 */
व्योम __निकास unरेजिस्टर_nfs_fs(व्योम)
अणु
	unरेजिस्टर_shrinker(&acl_shrinker);
	nfs_unरेजिस्टर_sysctl();
	unरेजिस्टर_nfs4_fs();
#अगर_घोषित CONFIG_NFS_V4_2
	nfs_ssc_unरेजिस्टर_ops();
#पूर्ण_अगर
	unरेजिस्टर_fileप्रणाली(&nfs_fs_type);
पूर्ण

bool nfs_sb_active(काष्ठा super_block *sb)
अणु
	काष्ठा nfs_server *server = NFS_SB(sb);

	अगर (!atomic_inc_not_zero(&sb->s_active))
		वापस false;
	अगर (atomic_inc_वापस(&server->active) != 1)
		atomic_dec(&sb->s_active);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_sb_active);

व्योम nfs_sb_deactive(काष्ठा super_block *sb)
अणु
	काष्ठा nfs_server *server = NFS_SB(sb);

	अगर (atomic_dec_and_test(&server->active))
		deactivate_super(sb);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_sb_deactive);

अटल पूर्णांक __nfs_list_क्रम_each_server(काष्ठा list_head *head,
		पूर्णांक (*fn)(काष्ठा nfs_server *, व्योम *),
		व्योम *data)
अणु
	काष्ठा nfs_server *server, *last = शून्य;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, head, client_link) अणु
		अगर (!(server->super && nfs_sb_active(server->super)))
			जारी;
		rcu_पढ़ो_unlock();
		अगर (last)
			nfs_sb_deactive(last->super);
		last = server;
		ret = fn(server, data);
		अगर (ret)
			जाओ out;
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	अगर (last)
		nfs_sb_deactive(last->super);
	वापस ret;
पूर्ण

पूर्णांक nfs_client_क्रम_each_server(काष्ठा nfs_client *clp,
		पूर्णांक (*fn)(काष्ठा nfs_server *, व्योम *),
		व्योम *data)
अणु
	वापस __nfs_list_क्रम_each_server(&clp->cl_superblocks, fn, data);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_client_क्रम_each_server);

/*
 * Deliver file प्रणाली statistics to userspace
 */
पूर्णांक nfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा nfs_server *server = NFS_SB(dentry->d_sb);
	अचिन्हित अक्षर blockbits;
	अचिन्हित दीर्घ blockres;
	काष्ठा nfs_fh *fh = NFS_FH(d_inode(dentry));
	काष्ठा nfs_fsstat res;
	पूर्णांक error = -ENOMEM;

	res.fattr = nfs_alloc_fattr();
	अगर (res.fattr == शून्य)
		जाओ out_err;

	error = server->nfs_client->rpc_ops->statfs(server, fh, &res);
	अगर (unlikely(error == -ESTALE)) अणु
		काष्ठा dentry *pd_dentry;

		pd_dentry = dget_parent(dentry);
		nfs_zap_caches(d_inode(pd_dentry));
		dput(pd_dentry);
	पूर्ण
	nfs_मुक्त_fattr(res.fattr);
	अगर (error < 0)
		जाओ out_err;

	buf->f_type = NFS_SUPER_MAGIC;

	/*
	 * Current versions of glibc करो not correctly handle the
	 * हाल where f_frsize != f_bsize.  Eventually we want to
	 * report the value of wपंचांगult in this field.
	 */
	buf->f_frsize = dentry->d_sb->s_blocksize;

	/*
	 * On most *nix प्रणालीs, f_blocks, f_bमुक्त, and f_bavail
	 * are reported in units of f_frsize.  Linux hasn't had
	 * an f_frsize field in its statfs काष्ठा until recently,
	 * thus historically Linux's sys_statfs reports these
	 * fields in units of f_bsize.
	 */
	buf->f_bsize = dentry->d_sb->s_blocksize;
	blockbits = dentry->d_sb->s_blocksize_bits;
	blockres = (1 << blockbits) - 1;
	buf->f_blocks = (res.tbytes + blockres) >> blockbits;
	buf->f_bमुक्त = (res.fbytes + blockres) >> blockbits;
	buf->f_bavail = (res.abytes + blockres) >> blockbits;

	buf->f_files = res.tfiles;
	buf->f_fमुक्त = res.afiles;

	buf->f_namelen = server->namelen;

	वापस 0;

 out_err:
	dprपूर्णांकk("%s: statfs error = %d\n", __func__, -error);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_statfs);

/*
 * Map the security flavour number to a name
 */
अटल स्थिर अक्षर *nfs_pseuकरोflavour_to_name(rpc_authflavor_t flavour)
अणु
	अटल स्थिर काष्ठा अणु
		rpc_authflavor_t flavour;
		स्थिर अक्षर *str;
	पूर्ण sec_flavours[NFS_AUTH_INFO_MAX_FLAVORS] = अणु
		/* update NFS_AUTH_INFO_MAX_FLAVORS when this list changes! */
		अणु RPC_AUTH_शून्य, "null" पूर्ण,
		अणु RPC_AUTH_UNIX, "sys" पूर्ण,
		अणु RPC_AUTH_GSS_KRB5, "krb5" पूर्ण,
		अणु RPC_AUTH_GSS_KRB5I, "krb5i" पूर्ण,
		अणु RPC_AUTH_GSS_KRB5P, "krb5p" पूर्ण,
		अणु RPC_AUTH_GSS_LKEY, "lkey" पूर्ण,
		अणु RPC_AUTH_GSS_LKEYI, "lkeyi" पूर्ण,
		अणु RPC_AUTH_GSS_LKEYP, "lkeyp" पूर्ण,
		अणु RPC_AUTH_GSS_SPKM, "spkm" पूर्ण,
		अणु RPC_AUTH_GSS_SPKMI, "spkmi" पूर्ण,
		अणु RPC_AUTH_GSS_SPKMP, "spkmp" पूर्ण,
		अणु अच_पूर्णांक_उच्च, "unknown" पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; sec_flavours[i].flavour != अच_पूर्णांक_उच्च; i++) अणु
		अगर (sec_flavours[i].flavour == flavour)
			अवरोध;
	पूर्ण
	वापस sec_flavours[i].str;
पूर्ण

अटल व्योम nfs_show_mountd_netid(काष्ठा seq_file *m, काष्ठा nfs_server *nfss,
				  पूर्णांक showशेषs)
अणु
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *) &nfss->mountd_address;
	अक्षर *proto = शून्य;

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		चयन (nfss->mountd_protocol) अणु
		हाल IPPROTO_UDP:
			proto = RPCBIND_NETID_UDP;
			अवरोध;
		हाल IPPROTO_TCP:
			proto = RPCBIND_NETID_TCP;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AF_INET6:
		चयन (nfss->mountd_protocol) अणु
		हाल IPPROTO_UDP:
			proto = RPCBIND_NETID_UDP6;
			अवरोध;
		हाल IPPROTO_TCP:
			proto = RPCBIND_NETID_TCP6;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (proto || showशेषs)
		seq_म_लिखो(m, ",mountproto=%s", proto ?: "auto");
पूर्ण

अटल व्योम nfs_show_mountd_options(काष्ठा seq_file *m, काष्ठा nfs_server *nfss,
				    पूर्णांक showशेषs)
अणु
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&nfss->mountd_address;

	अगर (nfss->flags & NFS_MOUNT_LEGACY_INTERFACE)
		वापस;

	चयन (sap->sa_family) अणु
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;
		seq_म_लिखो(m, ",mountaddr=%pI4", &sin->sin_addr.s_addr);
		अवरोध;
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
		seq_म_लिखो(m, ",mountaddr=%pI6c", &sin6->sin6_addr);
		अवरोध;
	पूर्ण
	शेष:
		अगर (showशेषs)
			seq_माला_दो(m, ",mountaddr=unspecified");
	पूर्ण

	अगर (nfss->mountd_version || showशेषs)
		seq_म_लिखो(m, ",mountvers=%u", nfss->mountd_version);
	अगर ((nfss->mountd_port &&
		nfss->mountd_port != (अचिन्हित लघु)NFS_UNSPEC_PORT) ||
		showशेषs)
		seq_म_लिखो(m, ",mountport=%u", nfss->mountd_port);

	nfs_show_mountd_netid(m, nfss, showशेषs);
पूर्ण

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल व्योम nfs_show_nfsv4_options(काष्ठा seq_file *m, काष्ठा nfs_server *nfss,
				    पूर्णांक showशेषs)
अणु
	काष्ठा nfs_client *clp = nfss->nfs_client;

	seq_म_लिखो(m, ",clientaddr=%s", clp->cl_ipaddr);
पूर्ण
#अन्यथा
अटल व्योम nfs_show_nfsv4_options(काष्ठा seq_file *m, काष्ठा nfs_server *nfss,
				    पूर्णांक showशेषs)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम nfs_show_nfs_version(काष्ठा seq_file *m,
		अचिन्हित पूर्णांक version,
		अचिन्हित पूर्णांक minorversion)
अणु
	seq_म_लिखो(m, ",vers=%u", version);
	अगर (version == 4)
		seq_म_लिखो(m, ".%u", minorversion);
पूर्ण

/*
 * Describe the mount options in क्रमce on this server representation
 */
अटल व्योम nfs_show_mount_options(काष्ठा seq_file *m, काष्ठा nfs_server *nfss,
				   पूर्णांक showशेषs)
अणु
	अटल स्थिर काष्ठा proc_nfs_info अणु
		पूर्णांक flag;
		स्थिर अक्षर *str;
		स्थिर अक्षर *nostr;
	पूर्ण nfs_info[] = अणु
		अणु NFS_MOUNT_SOFT, ",soft", "" पूर्ण,
		अणु NFS_MOUNT_SOFTERR, ",softerr", "" पूर्ण,
		अणु NFS_MOUNT_SOFTREVAL, ",softreval", "" पूर्ण,
		अणु NFS_MOUNT_POSIX, ",posix", "" पूर्ण,
		अणु NFS_MOUNT_NOCTO, ",nocto", "" पूर्ण,
		अणु NFS_MOUNT_NOAC, ",noac", "" पूर्ण,
		अणु NFS_MOUNT_NONLM, ",nolock", "" पूर्ण,
		अणु NFS_MOUNT_NOACL, ",noacl", "" पूर्ण,
		अणु NFS_MOUNT_NORसूचीPLUS, ",nordirplus", "" पूर्ण,
		अणु NFS_MOUNT_UNSHARED, ",nosharecache", "" पूर्ण,
		अणु NFS_MOUNT_NORESVPORT, ",noresvport", "" पूर्ण,
		अणु 0, शून्य, शून्य पूर्ण
	पूर्ण;
	स्थिर काष्ठा proc_nfs_info *nfs_infop;
	काष्ठा nfs_client *clp = nfss->nfs_client;
	u32 version = clp->rpc_ops->version;
	पूर्णांक local_flock, local_fcntl;

	nfs_show_nfs_version(m, version, clp->cl_minorversion);
	seq_म_लिखो(m, ",rsize=%u", nfss->rsize);
	seq_म_लिखो(m, ",wsize=%u", nfss->wsize);
	अगर (nfss->bsize != 0)
		seq_म_लिखो(m, ",bsize=%u", nfss->bsize);
	seq_म_लिखो(m, ",namlen=%u", nfss->namelen);
	अगर (nfss->acregmin != NFS_DEF_ACREGMIN*HZ || showशेषs)
		seq_म_लिखो(m, ",acregmin=%u", nfss->acregmin/HZ);
	अगर (nfss->acregmax != NFS_DEF_ACREGMAX*HZ || showशेषs)
		seq_म_लिखो(m, ",acregmax=%u", nfss->acregmax/HZ);
	अगर (nfss->acdirmin != NFS_DEF_ACसूचीMIN*HZ || showशेषs)
		seq_म_लिखो(m, ",acdirmin=%u", nfss->acdirmin/HZ);
	अगर (nfss->acdirmax != NFS_DEF_ACसूचीMAX*HZ || showशेषs)
		seq_म_लिखो(m, ",acdirmax=%u", nfss->acdirmax/HZ);
	अगर (!(nfss->flags & (NFS_MOUNT_SOFT|NFS_MOUNT_SOFTERR)))
			seq_माला_दो(m, ",hard");
	क्रम (nfs_infop = nfs_info; nfs_infop->flag; nfs_infop++) अणु
		अगर (nfss->flags & nfs_infop->flag)
			seq_माला_दो(m, nfs_infop->str);
		अन्यथा
			seq_माला_दो(m, nfs_infop->nostr);
	पूर्ण
	rcu_पढ़ो_lock();
	seq_म_लिखो(m, ",proto=%s",
		   rpc_peeraddr2str(nfss->client, RPC_DISPLAY_NETID));
	rcu_पढ़ो_unlock();
	अगर (clp->cl_nconnect > 0)
		seq_म_लिखो(m, ",nconnect=%u", clp->cl_nconnect);
	अगर (version == 4) अणु
		अगर (nfss->port != NFS_PORT)
			seq_म_लिखो(m, ",port=%u", nfss->port);
	पूर्ण अन्यथा
		अगर (nfss->port)
			seq_म_लिखो(m, ",port=%u", nfss->port);

	seq_म_लिखो(m, ",timeo=%lu", 10U * nfss->client->cl_समयout->to_initval / HZ);
	seq_म_लिखो(m, ",retrans=%u", nfss->client->cl_समयout->to_retries);
	seq_म_लिखो(m, ",sec=%s", nfs_pseuकरोflavour_to_name(nfss->client->cl_auth->au_flavor));

	अगर (version != 4)
		nfs_show_mountd_options(m, nfss, showशेषs);
	अन्यथा
		nfs_show_nfsv4_options(m, nfss, showशेषs);

	अगर (nfss->options & NFS_OPTION_FSCACHE)
		seq_माला_दो(m, ",fsc");

	अगर (nfss->options & NFS_OPTION_MIGRATION)
		seq_माला_दो(m, ",migration");

	अगर (nfss->flags & NFS_MOUNT_LOOKUP_CACHE_NONEG) अणु
		अगर (nfss->flags & NFS_MOUNT_LOOKUP_CACHE_NONE)
			seq_माला_दो(m, ",lookupcache=none");
		अन्यथा
			seq_माला_दो(m, ",lookupcache=pos");
	पूर्ण

	local_flock = nfss->flags & NFS_MOUNT_LOCAL_FLOCK;
	local_fcntl = nfss->flags & NFS_MOUNT_LOCAL_FCNTL;

	अगर (!local_flock && !local_fcntl)
		seq_माला_दो(m, ",local_lock=none");
	अन्यथा अगर (local_flock && local_fcntl)
		seq_माला_दो(m, ",local_lock=all");
	अन्यथा अगर (local_flock)
		seq_माला_दो(m, ",local_lock=flock");
	अन्यथा
		seq_माला_दो(m, ",local_lock=posix");

	अगर (nfss->flags & NFS_MOUNT_WRITE_EAGER) अणु
		अगर (nfss->flags & NFS_MOUNT_WRITE_WAIT)
			seq_माला_दो(m, ",write=wait");
		अन्यथा
			seq_माला_दो(m, ",write=eager");
	पूर्ण
पूर्ण

/*
 * Describe the mount options on this VFS mountpoपूर्णांक
 */
पूर्णांक nfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा nfs_server *nfss = NFS_SB(root->d_sb);

	nfs_show_mount_options(m, nfss, 0);

	rcu_पढ़ो_lock();
	seq_म_लिखो(m, ",addr=%s",
			rpc_peeraddr2str(nfss->nfs_client->cl_rpcclient,
							RPC_DISPLAY_ADDR));
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_show_options);

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल व्योम show_lease(काष्ठा seq_file *m, काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	अचिन्हित दीर्घ expire;

	seq_म_लिखो(m, ",lease_time=%ld", clp->cl_lease_समय / HZ);
	expire = clp->cl_last_renewal + clp->cl_lease_समय;
	seq_म_लिखो(m, ",lease_expired=%ld",
		   समय_after(expire, jअगरfies) ?  0 : (jअगरfies - expire) / HZ);
पूर्ण
#अगर_घोषित CONFIG_NFS_V4_1
अटल व्योम show_sessions(काष्ठा seq_file *m, काष्ठा nfs_server *server)
अणु
	अगर (nfs4_has_session(server->nfs_client))
		seq_माला_दो(m, ",sessions");
पूर्ण
#अन्यथा
अटल व्योम show_sessions(काष्ठा seq_file *m, काष्ठा nfs_server *server) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_NFS_V4_1
अटल व्योम show_pnfs(काष्ठा seq_file *m, काष्ठा nfs_server *server)
अणु
	seq_म_लिखो(m, ",pnfs=");
	अगर (server->pnfs_curr_ld)
		seq_म_लिखो(m, "%s", server->pnfs_curr_ld->name);
	अन्यथा
		seq_म_लिखो(m, "not configured");
पूर्ण

अटल व्योम show_implementation_id(काष्ठा seq_file *m, काष्ठा nfs_server *nfss)
अणु
	अगर (nfss->nfs_client && nfss->nfs_client->cl_implid) अणु
		काष्ठा nfs41_impl_id *impl_id = nfss->nfs_client->cl_implid;
		seq_म_लिखो(m, "\n\timpl_id:\tname='%s',domain='%s',"
			   "date='%llu,%u'",
			   impl_id->name, impl_id->करोमुख्य,
			   impl_id->date.seconds, impl_id->date.nseconds);
	पूर्ण
पूर्ण
#अन्यथा
#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल व्योम show_pnfs(काष्ठा seq_file *m, काष्ठा nfs_server *server)
अणु
पूर्ण
#पूर्ण_अगर
अटल व्योम show_implementation_id(काष्ठा seq_file *m, काष्ठा nfs_server *nfss)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक nfs_show_devname(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	अक्षर *page = (अक्षर *) __get_मुक्त_page(GFP_KERNEL);
	अक्षर *devname, *dummy;
	पूर्णांक err = 0;
	अगर (!page)
		वापस -ENOMEM;
	devname = nfs_path(&dummy, root, page, PAGE_SIZE, 0);
	अगर (IS_ERR(devname))
		err = PTR_ERR(devname);
	अन्यथा
		seq_escape(m, devname, " \t\n\\");
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_show_devname);

पूर्णांक nfs_show_path(काष्ठा seq_file *m, काष्ठा dentry *dentry)
अणु
	seq_माला_दो(m, "/");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_show_path);

/*
 * Present statistical inक्रमmation क्रम this VFS mountpoपूर्णांक
 */
पूर्णांक nfs_show_stats(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	पूर्णांक i, cpu;
	काष्ठा nfs_server *nfss = NFS_SB(root->d_sb);
	काष्ठा rpc_auth *auth = nfss->client->cl_auth;
	काष्ठा nfs_iostats totals = अणु पूर्ण;

	seq_म_लिखो(m, "statvers=%s", NFS_IOSTAT_VERS);

	/*
	 * Display all mount option settings
	 */
	seq_माला_दो(m, "\n\topts:\t");
	seq_माला_दो(m, sb_rकरोnly(root->d_sb) ? "ro" : "rw");
	seq_माला_दो(m, root->d_sb->s_flags & SB_SYNCHRONOUS ? ",sync" : "");
	seq_माला_दो(m, root->d_sb->s_flags & SB_NOATIME ? ",noatime" : "");
	seq_माला_दो(m, root->d_sb->s_flags & SB_NOसूचीATIME ? ",nodiratime" : "");
	nfs_show_mount_options(m, nfss, 1);

	seq_म_लिखो(m, "\n\tage:\t%lu", (jअगरfies - nfss->mount_समय) / HZ);

	show_implementation_id(m, nfss);

	seq_माला_दो(m, "\n\tcaps:\t");
	seq_म_लिखो(m, "caps=0x%x", nfss->caps);
	seq_म_लिखो(m, ",wtmult=%u", nfss->wपंचांगult);
	seq_म_लिखो(m, ",dtsize=%u", nfss->dtsize);
	seq_म_लिखो(m, ",bsize=%u", nfss->bsize);
	seq_म_लिखो(m, ",namlen=%u", nfss->namelen);

#अगर IS_ENABLED(CONFIG_NFS_V4)
	अगर (nfss->nfs_client->rpc_ops->version == 4) अणु
		seq_माला_दो(m, "\n\tnfsv4:\t");
		seq_म_लिखो(m, "bm0=0x%x", nfss->attr_biपंचांगask[0]);
		seq_म_लिखो(m, ",bm1=0x%x", nfss->attr_biपंचांगask[1]);
		seq_म_लिखो(m, ",bm2=0x%x", nfss->attr_biपंचांगask[2]);
		seq_म_लिखो(m, ",acl=0x%x", nfss->acl_biपंचांगask);
		show_sessions(m, nfss);
		show_pnfs(m, nfss);
		show_lease(m, nfss);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Display security flavor in effect क्रम this mount
	 */
	seq_म_लिखो(m, "\n\tsec:\tflavor=%u", auth->au_ops->au_flavor);
	अगर (auth->au_flavor)
		seq_म_लिखो(m, ",pseudoflavor=%u", auth->au_flavor);

	/*
	 * Display superblock I/O counters
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा nfs_iostats *stats;

		preempt_disable();
		stats = per_cpu_ptr(nfss->io_stats, cpu);

		क्रम (i = 0; i < __NFSIOS_COUNTSMAX; i++)
			totals.events[i] += stats->events[i];
		क्रम (i = 0; i < __NFSIOS_BYTESMAX; i++)
			totals.bytes[i] += stats->bytes[i];
#अगर_घोषित CONFIG_NFS_FSCACHE
		क्रम (i = 0; i < __NFSIOS_FSCACHEMAX; i++)
			totals.fscache[i] += stats->fscache[i];
#पूर्ण_अगर

		preempt_enable();
	पूर्ण

	seq_माला_दो(m, "\n\tevents:\t");
	क्रम (i = 0; i < __NFSIOS_COUNTSMAX; i++)
		seq_म_लिखो(m, "%lu ", totals.events[i]);
	seq_माला_दो(m, "\n\tbytes:\t");
	क्रम (i = 0; i < __NFSIOS_BYTESMAX; i++)
		seq_म_लिखो(m, "%Lu ", totals.bytes[i]);
#अगर_घोषित CONFIG_NFS_FSCACHE
	अगर (nfss->options & NFS_OPTION_FSCACHE) अणु
		seq_माला_दो(m, "\n\tfsc:\t");
		क्रम (i = 0; i < __NFSIOS_FSCACHEMAX; i++)
			seq_म_लिखो(m, "%Lu ", totals.fscache[i]);
	पूर्ण
#पूर्ण_अगर
	seq_अ_दो(m, '\n');

	rpc_clnt_show_stats(m, nfss->client);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_show_stats);

/*
 * Begin unmount by attempting to हटाओ all स्वतःmounted mountpoपूर्णांकs we added
 * in response to xdev traversals and referrals
 */
व्योम nfs_umount_begin(काष्ठा super_block *sb)
अणु
	काष्ठा nfs_server *server;
	काष्ठा rpc_clnt *rpc;

	server = NFS_SB(sb);
	/* -EIO all pending I/O */
	rpc = server->client_acl;
	अगर (!IS_ERR(rpc))
		rpc_समाप्तall_tasks(rpc);
	rpc = server->client;
	अगर (!IS_ERR(rpc))
		rpc_समाप्तall_tasks(rpc);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_umount_begin);

/*
 * Return true अगर 'match' is in auth_info or auth_info is empty.
 * Return false otherwise.
 */
bool nfs_auth_info_match(स्थिर काष्ठा nfs_auth_info *auth_info,
			 rpc_authflavor_t match)
अणु
	पूर्णांक i;

	अगर (!auth_info->flavor_len)
		वापस true;

	क्रम (i = 0; i < auth_info->flavor_len; i++) अणु
		अगर (auth_info->flavors[i] == match)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_auth_info_match);

/*
 * Ensure that a specअगरied authtype in ctx->auth_info is supported by
 * the server. Returns 0 and sets ctx->selected_flavor अगर it's ok, and
 * -EACCES अगर not.
 */
अटल पूर्णांक nfs_verअगरy_authflavors(काष्ठा nfs_fs_context *ctx,
				  rpc_authflavor_t *server_authlist,
				  अचिन्हित पूर्णांक count)
अणु
	rpc_authflavor_t flavor = RPC_AUTH_MAXFLAVOR;
	bool found_auth_null = false;
	अचिन्हित पूर्णांक i;

	/*
	 * If the sec= mount option is used, the specअगरied flavor or AUTH_शून्य
	 * must be in the list वापसed by the server.
	 *
	 * AUTH_शून्य has a special meaning when it's in the server list - it
	 * means that the server will ignore the rpc creds, so any flavor
	 * can be used but still use the sec= that was specअगरied.
	 *
	 * Note also that the MNT procedure in MNTv1 करोes not वापस a list
	 * of supported security flavors. In this हाल, nfs_mount() fabricates
	 * a security flavor list containing just AUTH_शून्य.
	 */
	क्रम (i = 0; i < count; i++) अणु
		flavor = server_authlist[i];

		अगर (nfs_auth_info_match(&ctx->auth_info, flavor))
			जाओ out;

		अगर (flavor == RPC_AUTH_शून्य)
			found_auth_null = true;
	पूर्ण

	अगर (found_auth_null) अणु
		flavor = ctx->auth_info.flavors[0];
		जाओ out;
	पूर्ण

	dfprपूर्णांकk(MOUNT,
		 "NFS: specified auth flavors not supported by server\n");
	वापस -EACCES;

out:
	ctx->selected_flavor = flavor;
	dfprपूर्णांकk(MOUNT, "NFS: using auth flavor %u\n", ctx->selected_flavor);
	वापस 0;
पूर्ण

/*
 * Use the remote server's MOUNT service to request the NFS file handle
 * corresponding to the provided path.
 */
अटल पूर्णांक nfs_request_mount(काष्ठा fs_context *fc,
			     काष्ठा nfs_fh *root_fh,
			     rpc_authflavor_t *server_authlist,
			     अचिन्हित पूर्णांक *server_authlist_len)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_mount_request request = अणु
		.sap		= (काष्ठा sockaddr *)
						&ctx->mount_server.address,
		.dirpath	= ctx->nfs_server.export_path,
		.protocol	= ctx->mount_server.protocol,
		.fh		= root_fh,
		.noresvport	= ctx->flags & NFS_MOUNT_NORESVPORT,
		.auth_flav_len	= server_authlist_len,
		.auth_flavs	= server_authlist,
		.net		= fc->net_ns,
	पूर्ण;
	पूर्णांक status;

	अगर (ctx->mount_server.version == 0) अणु
		चयन (ctx->version) अणु
			शेष:
				ctx->mount_server.version = NFS_MNT3_VERSION;
				अवरोध;
			हाल 2:
				ctx->mount_server.version = NFS_MNT_VERSION;
		पूर्ण
	पूर्ण
	request.version = ctx->mount_server.version;

	अगर (ctx->mount_server.hostname)
		request.hostname = ctx->mount_server.hostname;
	अन्यथा
		request.hostname = ctx->nfs_server.hostname;

	/*
	 * Conकाष्ठा the mount server's address.
	 */
	अगर (ctx->mount_server.address.sa_family == AF_UNSPEC) अणु
		स_नकल(request.sap, &ctx->nfs_server.address,
		       ctx->nfs_server.addrlen);
		ctx->mount_server.addrlen = ctx->nfs_server.addrlen;
	पूर्ण
	request.salen = ctx->mount_server.addrlen;
	nfs_set_port(request.sap, &ctx->mount_server.port, 0);

	/*
	 * Now ask the mount server to map our export path
	 * to a file handle.
	 */
	status = nfs_mount(&request, ctx->समयo, ctx->retrans);
	अगर (status != 0) अणु
		dfprपूर्णांकk(MOUNT, "NFS: unable to mount server %s, error %d\n",
				request.hostname, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nfs_server *nfs_try_mount_request(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	पूर्णांक status;
	अचिन्हित पूर्णांक i;
	bool tried_auth_unix = false;
	bool auth_null_in_list = false;
	काष्ठा nfs_server *server = ERR_PTR(-EACCES);
	rpc_authflavor_t authlist[NFS_MAX_SECFLAVORS];
	अचिन्हित पूर्णांक authlist_len = ARRAY_SIZE(authlist);

	status = nfs_request_mount(fc, ctx->mntfh, authlist, &authlist_len);
	अगर (status)
		वापस ERR_PTR(status);

	/*
	 * Was a sec= authflavor specअगरied in the options? First, verअगरy
	 * whether the server supports it, and then just try to use it अगर so.
	 */
	अगर (ctx->auth_info.flavor_len > 0) अणु
		status = nfs_verअगरy_authflavors(ctx, authlist, authlist_len);
		dfprपूर्णांकk(MOUNT, "NFS: using auth flavor %u\n",
			 ctx->selected_flavor);
		अगर (status)
			वापस ERR_PTR(status);
		वापस ctx->nfs_mod->rpc_ops->create_server(fc);
	पूर्ण

	/*
	 * No sec= option was provided. RFC 2623, section 2.7 suggests we
	 * SHOULD prefer the flavor listed first. However, some servers list
	 * AUTH_शून्य first. Aव्योम ever choosing AUTH_शून्य.
	 */
	क्रम (i = 0; i < authlist_len; ++i) अणु
		rpc_authflavor_t flavor;
		काष्ठा rpcsec_gss_info info;

		flavor = authlist[i];
		चयन (flavor) अणु
		हाल RPC_AUTH_UNIX:
			tried_auth_unix = true;
			अवरोध;
		हाल RPC_AUTH_शून्य:
			auth_null_in_list = true;
			जारी;
		शेष:
			अगर (rpcauth_get_gssinfo(flavor, &info) != 0)
				जारी;
			अवरोध;
		पूर्ण
		dfprपूर्णांकk(MOUNT, "NFS: attempting to use auth flavor %u\n", flavor);
		ctx->selected_flavor = flavor;
		server = ctx->nfs_mod->rpc_ops->create_server(fc);
		अगर (!IS_ERR(server))
			वापस server;
	पूर्ण

	/*
	 * Nothing we tried so far worked. At this poपूर्णांक, give up अगर we've
	 * alपढ़ोy tried AUTH_UNIX or अगर the server's list doesn't contain
	 * AUTH_शून्य
	 */
	अगर (tried_auth_unix || !auth_null_in_list)
		वापस server;

	/* Last chance! Try AUTH_UNIX */
	dfprपूर्णांकk(MOUNT, "NFS: attempting to use auth flavor %u\n", RPC_AUTH_UNIX);
	ctx->selected_flavor = RPC_AUTH_UNIX;
	वापस ctx->nfs_mod->rpc_ops->create_server(fc);
पूर्ण

पूर्णांक nfs_try_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);

	अगर (ctx->need_mount)
		ctx->server = nfs_try_mount_request(fc);
	अन्यथा
		ctx->server = ctx->nfs_mod->rpc_ops->create_server(fc);

	वापस nfs_get_tree_common(fc);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_try_get_tree);


#घोषणा NFS_REMOUNT_CMP_FLAGMASK ~(NFS_MOUNT_INTR \
		| NFS_MOUNT_SECURE \
		| NFS_MOUNT_TCP \
		| NFS_MOUNT_VER3 \
		| NFS_MOUNT_KERBEROS \
		| NFS_MOUNT_NONLM \
		| NFS_MOUNT_BROKEN_SUID \
		| NFS_MOUNT_STRICTLOCK \
		| NFS_MOUNT_LEGACY_INTERFACE)

#घोषणा NFS_MOUNT_CMP_FLAGMASK (NFS_REMOUNT_CMP_FLAGMASK & \
		~(NFS_MOUNT_UNSHARED | NFS_MOUNT_NORESVPORT))

अटल पूर्णांक
nfs_compare_remount_data(काष्ठा nfs_server *nfss,
			 काष्ठा nfs_fs_context *ctx)
अणु
	अगर ((ctx->flags ^ nfss->flags) & NFS_REMOUNT_CMP_FLAGMASK ||
	    ctx->rsize != nfss->rsize ||
	    ctx->wsize != nfss->wsize ||
	    ctx->version != nfss->nfs_client->rpc_ops->version ||
	    ctx->minorversion != nfss->nfs_client->cl_minorversion ||
	    ctx->retrans != nfss->client->cl_समयout->to_retries ||
	    !nfs_auth_info_match(&ctx->auth_info, nfss->client->cl_auth->au_flavor) ||
	    ctx->acregmin != nfss->acregmin / HZ ||
	    ctx->acregmax != nfss->acregmax / HZ ||
	    ctx->acdirmin != nfss->acdirmin / HZ ||
	    ctx->acdirmax != nfss->acdirmax / HZ ||
	    ctx->समयo != (10U * nfss->client->cl_समयout->to_initval / HZ) ||
	    (ctx->options & NFS_OPTION_FSCACHE) != (nfss->options & NFS_OPTION_FSCACHE) ||
	    ctx->nfs_server.port != nfss->port ||
	    ctx->nfs_server.addrlen != nfss->nfs_client->cl_addrlen ||
	    !rpc_cmp_addr((काष्ठा sockaddr *)&ctx->nfs_server.address,
			  (काष्ठा sockaddr *)&nfss->nfs_client->cl_addr))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक nfs_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा super_block *sb = fc->root->d_sb;
	काष्ठा nfs_server *nfss = sb->s_fs_info;

	sync_fileप्रणाली(sb);

	/*
	 * Userspace mount programs that send binary options generally send
	 * them populated with शेष values. We have no way to know which
	 * ones were explicitly specअगरied. Fall back to legacy behavior and
	 * just वापस success.
	 */
	अगर (ctx->skip_reconfig_option_check)
		वापस 0;

	/*
	 * noac is a special हाल. It implies -o sync, but that's not
	 * necessarily reflected in the mtab options. reconfigure_super
	 * will clear SB_SYNCHRONOUS अगर -o sync wasn't specअगरied in the
	 * remount options, so we have to explicitly reset it.
	 */
	अगर (ctx->flags & NFS_MOUNT_NOAC) अणु
		fc->sb_flags |= SB_SYNCHRONOUS;
		fc->sb_flags_mask |= SB_SYNCHRONOUS;
	पूर्ण

	/* compare new mount options with old ones */
	वापस nfs_compare_remount_data(nfss, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_reconfigure);

/*
 * Finish setting up an NFS superblock
 */
अटल व्योम nfs_fill_super(काष्ठा super_block *sb, काष्ठा nfs_fs_context *ctx)
अणु
	काष्ठा nfs_server *server = NFS_SB(sb);

	sb->s_blocksize_bits = 0;
	sb->s_blocksize = 0;
	sb->s_xattr = server->nfs_client->cl_nfs_mod->xattr;
	sb->s_op = server->nfs_client->cl_nfs_mod->sops;
	अगर (ctx->bsize)
		sb->s_blocksize = nfs_block_size(ctx->bsize, &sb->s_blocksize_bits);

	अगर (server->nfs_client->rpc_ops->version != 2) अणु
		/* The VFS shouldn't apply the umask to mode bits. We will करो
		 * so ourselves when necessary.
		 */
		sb->s_flags |= SB_POSIXACL;
		sb->s_समय_gran = 1;
		sb->s_export_op = &nfs_export_ops;
	पूर्ण अन्यथा
		sb->s_समय_gran = 1000;

	अगर (server->nfs_client->rpc_ops->version != 4) अणु
		sb->s_समय_min = 0;
		sb->s_समय_max = U32_MAX;
	पूर्ण अन्यथा अणु
		sb->s_समय_min = S64_MIN;
		sb->s_समय_max = S64_MAX;
	पूर्ण

	sb->s_magic = NFS_SUPER_MAGIC;

	/* We probably want something more inक्रमmative here */
	snम_लिखो(sb->s_id, माप(sb->s_id),
		 "%u:%u", MAJOR(sb->s_dev), MINOR(sb->s_dev));

	अगर (sb->s_blocksize == 0)
		sb->s_blocksize = nfs_block_bits(server->wsize,
						 &sb->s_blocksize_bits);

	nfs_super_set_maxbytes(sb, server->maxfilesize);
	server->has_sec_mnt_opts = ctx->has_sec_mnt_opts;
पूर्ण

अटल पूर्णांक nfs_compare_mount_options(स्थिर काष्ठा super_block *s, स्थिर काष्ठा nfs_server *b,
				     स्थिर काष्ठा fs_context *fc)
अणु
	स्थिर काष्ठा nfs_server *a = s->s_fs_info;
	स्थिर काष्ठा rpc_clnt *clnt_a = a->client;
	स्थिर काष्ठा rpc_clnt *clnt_b = b->client;

	अगर ((s->s_flags & NFS_SB_MASK) != (fc->sb_flags & NFS_SB_MASK))
		जाओ Ebusy;
	अगर (a->nfs_client != b->nfs_client)
		जाओ Ebusy;
	अगर ((a->flags ^ b->flags) & NFS_MOUNT_CMP_FLAGMASK)
		जाओ Ebusy;
	अगर (a->wsize != b->wsize)
		जाओ Ebusy;
	अगर (a->rsize != b->rsize)
		जाओ Ebusy;
	अगर (a->acregmin != b->acregmin)
		जाओ Ebusy;
	अगर (a->acregmax != b->acregmax)
		जाओ Ebusy;
	अगर (a->acdirmin != b->acdirmin)
		जाओ Ebusy;
	अगर (a->acdirmax != b->acdirmax)
		जाओ Ebusy;
	अगर (clnt_a->cl_auth->au_flavor != clnt_b->cl_auth->au_flavor)
		जाओ Ebusy;
	वापस 1;
Ebusy:
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_set_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_server *server = fc->s_fs_info;
	पूर्णांक ret;

	s->s_d_op = server->nfs_client->rpc_ops->dentry_ops;
	ret = set_anon_super(s, server);
	अगर (ret == 0)
		server->s_dev = s->s_dev;
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_compare_super_address(काष्ठा nfs_server *server1,
				     काष्ठा nfs_server *server2)
अणु
	काष्ठा sockaddr *sap1, *sap2;
	काष्ठा rpc_xprt *xprt1 = server1->client->cl_xprt;
	काष्ठा rpc_xprt *xprt2 = server2->client->cl_xprt;

	अगर (!net_eq(xprt1->xprt_net, xprt2->xprt_net))
		वापस 0;

	sap1 = (काष्ठा sockaddr *)&server1->nfs_client->cl_addr;
	sap2 = (काष्ठा sockaddr *)&server2->nfs_client->cl_addr;

	अगर (sap1->sa_family != sap2->sa_family)
		वापस 0;

	चयन (sap1->sa_family) अणु
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *sin1 = (काष्ठा sockaddr_in *)sap1;
		काष्ठा sockaddr_in *sin2 = (काष्ठा sockaddr_in *)sap2;
		अगर (sin1->sin_addr.s_addr != sin2->sin_addr.s_addr)
			वापस 0;
		अगर (sin1->sin_port != sin2->sin_port)
			वापस 0;
		अवरोध;
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा sockaddr_in6 *sin1 = (काष्ठा sockaddr_in6 *)sap1;
		काष्ठा sockaddr_in6 *sin2 = (काष्ठा sockaddr_in6 *)sap2;
		अगर (!ipv6_addr_equal(&sin1->sin6_addr, &sin2->sin6_addr))
			वापस 0;
		अगर (sin1->sin6_port != sin2->sin6_port)
			वापस 0;
		अवरोध;
	पूर्ण
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक nfs_compare_userns(स्थिर काष्ठा nfs_server *old,
		स्थिर काष्ठा nfs_server *new)
अणु
	स्थिर काष्ठा user_namespace *oldns = &init_user_ns;
	स्थिर काष्ठा user_namespace *newns = &init_user_ns;

	अगर (old->client && old->client->cl_cred)
		oldns = old->client->cl_cred->user_ns;
	अगर (new->client && new->client->cl_cred)
		newns = new->client->cl_cred->user_ns;
	अगर (oldns != newns)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक nfs_compare_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_server *server = fc->s_fs_info, *old = NFS_SB(sb);

	अगर (!nfs_compare_super_address(old, server))
		वापस 0;
	/* Note: NFS_MOUNT_UNSHARED == NFS4_MOUNT_UNSHARED */
	अगर (old->flags & NFS_MOUNT_UNSHARED)
		वापस 0;
	अगर (स_भेद(&old->fsid, &server->fsid, माप(old->fsid)) != 0)
		वापस 0;
	अगर (!nfs_compare_userns(old, server))
		वापस 0;
	अगर ((old->has_sec_mnt_opts || fc->security) &&
			security_sb_mnt_opts_compat(sb, fc->security))
		वापस 0;
	वापस nfs_compare_mount_options(sb, server, fc);
पूर्ण

#अगर_घोषित CONFIG_NFS_FSCACHE
अटल व्योम nfs_get_cache_cookie(काष्ठा super_block *sb,
				 काष्ठा nfs_fs_context *ctx)
अणु
	काष्ठा nfs_server *nfss = NFS_SB(sb);
	अक्षर *uniq = शून्य;
	पूर्णांक ulen = 0;

	nfss->fscache_key = शून्य;
	nfss->fscache = शून्य;

	अगर (!ctx)
		वापस;

	अगर (ctx->clone_data.sb) अणु
		काष्ठा nfs_server *mnt_s = NFS_SB(ctx->clone_data.sb);
		अगर (!(mnt_s->options & NFS_OPTION_FSCACHE))
			वापस;
		अगर (mnt_s->fscache_key) अणु
			uniq = mnt_s->fscache_key->key.uniquअगरier;
			ulen = mnt_s->fscache_key->key.uniq_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(ctx->options & NFS_OPTION_FSCACHE))
			वापस;
		अगर (ctx->fscache_uniq) अणु
			uniq = ctx->fscache_uniq;
			ulen = म_माप(ctx->fscache_uniq);
		पूर्ण
	पूर्ण

	nfs_fscache_get_super_cookie(sb, uniq, ulen);
पूर्ण
#अन्यथा
अटल व्योम nfs_get_cache_cookie(काष्ठा super_block *sb,
				 काष्ठा nfs_fs_context *ctx)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक nfs_get_tree_common(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा super_block *s;
	पूर्णांक (*compare_super)(काष्ठा super_block *, काष्ठा fs_context *) = nfs_compare_super;
	काष्ठा nfs_server *server = ctx->server;
	पूर्णांक error;

	ctx->server = शून्य;
	अगर (IS_ERR(server))
		वापस PTR_ERR(server);

	अगर (server->flags & NFS_MOUNT_UNSHARED)
		compare_super = शून्य;

	/* -o noac implies -o sync */
	अगर (server->flags & NFS_MOUNT_NOAC)
		fc->sb_flags |= SB_SYNCHRONOUS;

	अगर (ctx->clone_data.sb)
		अगर (ctx->clone_data.sb->s_flags & SB_SYNCHRONOUS)
			fc->sb_flags |= SB_SYNCHRONOUS;

	अगर (server->caps & NFS_CAP_SECURITY_LABEL)
		fc->lsm_flags |= SECURITY_LSM_NATIVE_LABELS;

	/* Get a superblock - note that we may end up sharing one that alपढ़ोy exists */
	fc->s_fs_info = server;
	s = sget_fc(fc, compare_super, nfs_set_super);
	fc->s_fs_info = शून्य;
	अगर (IS_ERR(s)) अणु
		error = PTR_ERR(s);
		nfs_errorf(fc, "NFS: Couldn't get superblock");
		जाओ out_err_nosb;
	पूर्ण

	अगर (s->s_fs_info != server) अणु
		nfs_मुक्त_server(server);
		server = शून्य;
	पूर्ण अन्यथा अणु
		error = super_setup_bdi_name(s, "%u:%u", MAJOR(server->s_dev),
					     MINOR(server->s_dev));
		अगर (error)
			जाओ error_splat_super;
		s->s_bdi->io_pages = server->rpages;
		server->super = s;
	पूर्ण

	अगर (!s->s_root) अणु
		अचिन्हित bsize = ctx->clone_data.inherited_bsize;
		/* initial superblock/root creation */
		nfs_fill_super(s, ctx);
		अगर (bsize) अणु
			s->s_blocksize_bits = bsize;
			s->s_blocksize = 1U << bsize;
		पूर्ण
		nfs_get_cache_cookie(s, ctx);
	पूर्ण

	error = nfs_get_root(s, fc);
	अगर (error < 0) अणु
		nfs_errorf(fc, "NFS: Couldn't get root dentry");
		जाओ error_splat_super;
	पूर्ण

	s->s_flags |= SB_ACTIVE;
	error = 0;

out:
	वापस error;

out_err_nosb:
	nfs_मुक्त_server(server);
	जाओ out;
error_splat_super:
	deactivate_locked_super(s);
	जाओ out;
पूर्ण

/*
 * Destroy an NFS2/3 superblock
 */
व्योम nfs_समाप्त_super(काष्ठा super_block *s)
अणु
	काष्ठा nfs_server *server = NFS_SB(s);
	dev_t dev = s->s_dev;

	generic_shutकरोwn_super(s);

	nfs_fscache_release_super_cookie(s);

	nfs_मुक्त_server(server);
	मुक्त_anon_bdev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_समाप्त_super);

#अगर IS_ENABLED(CONFIG_NFS_V4)

/*
 * NFS v4 module parameters need to stay in the
 * NFS client क्रम backwards compatibility
 */
अचिन्हित पूर्णांक nfs_callback_set_tcpport;
अचिन्हित लघु nfs_callback_nr_thपढ़ोs;
/* Default cache समयout is 10 minutes */
अचिन्हित पूर्णांक nfs_idmap_cache_समयout = 600;
/* Turn off NFSv4 uid/gid mapping when using AUTH_SYS */
bool nfs4_disable_idmapping = true;
अचिन्हित लघु max_session_slots = NFS4_DEF_SLOT_TABLE_SIZE;
अचिन्हित लघु max_session_cb_slots = NFS4_DEF_CB_SLOT_TABLE_SIZE;
अचिन्हित लघु send_implementation_id = 1;
अक्षर nfs4_client_id_uniquअगरier[NFS4_CLIENT_ID_UNIQ_LEN] = "";
bool recover_lost_locks = false;

EXPORT_SYMBOL_GPL(nfs_callback_nr_thपढ़ोs);
EXPORT_SYMBOL_GPL(nfs_callback_set_tcpport);
EXPORT_SYMBOL_GPL(nfs_idmap_cache_समयout);
EXPORT_SYMBOL_GPL(nfs4_disable_idmapping);
EXPORT_SYMBOL_GPL(max_session_slots);
EXPORT_SYMBOL_GPL(max_session_cb_slots);
EXPORT_SYMBOL_GPL(send_implementation_id);
EXPORT_SYMBOL_GPL(nfs4_client_id_uniquअगरier);
EXPORT_SYMBOL_GPL(recover_lost_locks);

#घोषणा NFS_CALLBACK_MAXPORTNR (65535U)

अटल पूर्णांक param_set_portnr(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ num;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;
	ret = kम_से_अदीर्घ(val, 0, &num);
	अगर (ret || num > NFS_CALLBACK_MAXPORTNR)
		वापस -EINVAL;
	*((अचिन्हित पूर्णांक *)kp->arg) = num;
	वापस 0;
पूर्ण
अटल स्थिर काष्ठा kernel_param_ops param_ops_portnr = अणु
	.set = param_set_portnr,
	.get = param_get_uपूर्णांक,
पूर्ण;
#घोषणा param_check_portnr(name, p) __param_check(name, p, अचिन्हित पूर्णांक)

module_param_named(callback_tcpport, nfs_callback_set_tcpport, portnr, 0644);
module_param_named(callback_nr_thपढ़ोs, nfs_callback_nr_thपढ़ोs, uलघु, 0644);
MODULE_PARM_DESC(callback_nr_thपढ़ोs, "Number of threads that will be "
		"assigned to the NFSv4 callback channels.");
module_param(nfs_idmap_cache_समयout, पूर्णांक, 0644);
module_param(nfs4_disable_idmapping, bool, 0644);
module_param_string(nfs4_unique_id, nfs4_client_id_uniquअगरier,
			NFS4_CLIENT_ID_UNIQ_LEN, 0600);
MODULE_PARM_DESC(nfs4_disable_idmapping,
		"Turn off NFSv4 idmapping when using 'sec=sys'");
module_param(max_session_slots, uलघु, 0644);
MODULE_PARM_DESC(max_session_slots, "Maximum number of outstanding NFSv4.1 "
		"requests the client will negotiate");
module_param(max_session_cb_slots, uलघु, 0644);
MODULE_PARM_DESC(max_session_cb_slots, "Maximum number of parallel NFSv4.1 "
		"callbacks the client will process for a given server");
module_param(send_implementation_id, uलघु, 0644);
MODULE_PARM_DESC(send_implementation_id,
		"Send implementation ID with NFSv4.1 exchange_id");
MODULE_PARM_DESC(nfs4_unique_id, "nfs_client_id4 uniquifier string");

module_param(recover_lost_locks, bool, 0644);
MODULE_PARM_DESC(recover_lost_locks,
		 "If the server reports that a lock might be lost, "
		 "try to recover it risking data corruption.");


#पूर्ण_अगर /* CONFIG_NFS_V4 */
