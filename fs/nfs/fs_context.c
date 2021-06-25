<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/fs_context.c
 *
 * Copyright (C) 1992 Rick Sladkey
 * Conversion to new mount api Copyright (C) David Howells
 *
 * NFS mount handling.
 *
 * Split from fs/nfs/super.c by David Howells <dhowells@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश "nfs.h"
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_MOUNT

#अगर IS_ENABLED(CONFIG_NFS_V3)
#घोषणा NFS_DEFAULT_VERSION 3
#अन्यथा
#घोषणा NFS_DEFAULT_VERSION 2
#पूर्ण_अगर

#घोषणा NFS_MAX_CONNECTIONS 16

क्रमागत nfs_param अणु
	Opt_ac,
	Opt_acdirmax,
	Opt_acdirmin,
	Opt_acl,
	Opt_acregmax,
	Opt_acregmin,
	Opt_aस_समयo,
	Opt_addr,
	Opt_bg,
	Opt_bsize,
	Opt_clientaddr,
	Opt_cto,
	Opt_fg,
	Opt_fscache,
	Opt_fscache_flag,
	Opt_hard,
	Opt_पूर्णांकr,
	Opt_local_lock,
	Opt_lock,
	Opt_lookupcache,
	Opt_migration,
	Opt_minorversion,
	Opt_mountaddr,
	Opt_mounthost,
	Opt_mountport,
	Opt_mountproto,
	Opt_mountvers,
	Opt_namelen,
	Opt_nconnect,
	Opt_port,
	Opt_posix,
	Opt_proto,
	Opt_rdirplus,
	Opt_rdma,
	Opt_resvport,
	Opt_retrans,
	Opt_retry,
	Opt_rsize,
	Opt_sec,
	Opt_sharecache,
	Opt_sloppy,
	Opt_soft,
	Opt_softerr,
	Opt_softreval,
	Opt_source,
	Opt_tcp,
	Opt_समयo,
	Opt_udp,
	Opt_v,
	Opt_vers,
	Opt_wsize,
	Opt_ग_लिखो,
पूर्ण;

क्रमागत अणु
	Opt_local_lock_all,
	Opt_local_lock_flock,
	Opt_local_lock_none,
	Opt_local_lock_posix,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_param_क्रमागतs_local_lock[] = अणु
	अणु "all",		Opt_local_lock_all पूर्ण,
	अणु "flock",	Opt_local_lock_flock पूर्ण,
	अणु "posix",	Opt_local_lock_posix पूर्ण,
	अणु "none",		Opt_local_lock_none पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	Opt_lookupcache_all,
	Opt_lookupcache_none,
	Opt_lookupcache_positive,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_param_क्रमागतs_lookupcache[] = अणु
	अणु "all",		Opt_lookupcache_all पूर्ण,
	अणु "none",		Opt_lookupcache_none पूर्ण,
	अणु "pos",		Opt_lookupcache_positive पूर्ण,
	अणु "positive",		Opt_lookupcache_positive पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	Opt_ग_लिखो_lazy,
	Opt_ग_लिखो_eager,
	Opt_ग_लिखो_रुको,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_param_क्रमागतs_ग_लिखो[] = अणु
	अणु "lazy",		Opt_ग_लिखो_lazy पूर्ण,
	अणु "eager",		Opt_ग_लिखो_eager पूर्ण,
	अणु "wait",		Opt_ग_लिखो_रुको पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec nfs_fs_parameters[] = अणु
	fsparam_flag_no("ac",		Opt_ac),
	fsparam_u32   ("acdirmax",	Opt_acdirmax),
	fsparam_u32   ("acdirmin",	Opt_acdirmin),
	fsparam_flag_no("acl",		Opt_acl),
	fsparam_u32   ("acregmax",	Opt_acregmax),
	fsparam_u32   ("acregmin",	Opt_acregmin),
	fsparam_u32   ("actimeo",	Opt_aस_समयo),
	fsparam_string("addr",		Opt_addr),
	fsparam_flag  ("bg",		Opt_bg),
	fsparam_u32   ("bsize",		Opt_bsize),
	fsparam_string("clientaddr",	Opt_clientaddr),
	fsparam_flag_no("cto",		Opt_cto),
	fsparam_flag  ("fg",		Opt_fg),
	fsparam_flag_no("fsc",		Opt_fscache_flag),
	fsparam_string("fsc",		Opt_fscache),
	fsparam_flag  ("hard",		Opt_hard),
	__fsparam(शून्य, "intr",		Opt_पूर्णांकr,
		  fs_param_neg_with_no|fs_param_deprecated, शून्य),
	fsparam_क्रमागत  ("local_lock",	Opt_local_lock, nfs_param_क्रमागतs_local_lock),
	fsparam_flag_no("lock",		Opt_lock),
	fsparam_क्रमागत  ("lookupcache",	Opt_lookupcache, nfs_param_क्रमागतs_lookupcache),
	fsparam_flag_no("migration",	Opt_migration),
	fsparam_u32   ("minorversion",	Opt_minorversion),
	fsparam_string("mountaddr",	Opt_mountaddr),
	fsparam_string("mounthost",	Opt_mounthost),
	fsparam_u32   ("mountport",	Opt_mountport),
	fsparam_string("mountproto",	Opt_mountproto),
	fsparam_u32   ("mountvers",	Opt_mountvers),
	fsparam_u32   ("namlen",	Opt_namelen),
	fsparam_u32   ("nconnect",	Opt_nconnect),
	fsparam_string("nfsvers",	Opt_vers),
	fsparam_u32   ("port",		Opt_port),
	fsparam_flag_no("posix",	Opt_posix),
	fsparam_string("proto",		Opt_proto),
	fsparam_flag_no("rdirplus",	Opt_rdirplus),
	fsparam_flag  ("rdma",		Opt_rdma),
	fsparam_flag_no("resvport",	Opt_resvport),
	fsparam_u32   ("retrans",	Opt_retrans),
	fsparam_string("retry",		Opt_retry),
	fsparam_u32   ("rsize",		Opt_rsize),
	fsparam_string("sec",		Opt_sec),
	fsparam_flag_no("sharecache",	Opt_sharecache),
	fsparam_flag  ("sloppy",	Opt_sloppy),
	fsparam_flag  ("soft",		Opt_soft),
	fsparam_flag  ("softerr",	Opt_softerr),
	fsparam_flag  ("softreval",	Opt_softreval),
	fsparam_string("source",	Opt_source),
	fsparam_flag  ("tcp",		Opt_tcp),
	fsparam_u32   ("timeo",		Opt_समयo),
	fsparam_flag  ("udp",		Opt_udp),
	fsparam_flag  ("v2",		Opt_v),
	fsparam_flag  ("v3",		Opt_v),
	fsparam_flag  ("v4",		Opt_v),
	fsparam_flag  ("v4.0",		Opt_v),
	fsparam_flag  ("v4.1",		Opt_v),
	fsparam_flag  ("v4.2",		Opt_v),
	fsparam_string("vers",		Opt_vers),
	fsparam_क्रमागत  ("write",		Opt_ग_लिखो, nfs_param_क्रमागतs_ग_लिखो),
	fsparam_u32   ("wsize",		Opt_wsize),
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	Opt_vers_2,
	Opt_vers_3,
	Opt_vers_4,
	Opt_vers_4_0,
	Opt_vers_4_1,
	Opt_vers_4_2,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_vers_tokens[] = अणु
	अणु "2",		Opt_vers_2 पूर्ण,
	अणु "3",		Opt_vers_3 पूर्ण,
	अणु "4",		Opt_vers_4 पूर्ण,
	अणु "4.0",	Opt_vers_4_0 पूर्ण,
	अणु "4.1",	Opt_vers_4_1 पूर्ण,
	अणु "4.2",	Opt_vers_4_2 पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	Opt_xprt_rdma,
	Opt_xprt_rdma6,
	Opt_xprt_tcp,
	Opt_xprt_tcp6,
	Opt_xprt_udp,
	Opt_xprt_udp6,
	nr__Opt_xprt
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_xprt_protocol_tokens[] = अणु
	अणु "rdma",	Opt_xprt_rdma पूर्ण,
	अणु "rdma6",	Opt_xprt_rdma6 पूर्ण,
	अणु "tcp",	Opt_xprt_tcp पूर्ण,
	अणु "tcp6",	Opt_xprt_tcp6 पूर्ण,
	अणु "udp",	Opt_xprt_udp पूर्ण,
	अणु "udp6",	Opt_xprt_udp6 पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	Opt_sec_krb5,
	Opt_sec_krb5i,
	Opt_sec_krb5p,
	Opt_sec_lkey,
	Opt_sec_lkeyi,
	Opt_sec_lkeyp,
	Opt_sec_none,
	Opt_sec_spkm,
	Opt_sec_spkmi,
	Opt_sec_spkmp,
	Opt_sec_sys,
	nr__Opt_sec
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table nfs_secflavor_tokens[] = अणु
	अणु "krb5",	Opt_sec_krb5 पूर्ण,
	अणु "krb5i",	Opt_sec_krb5i पूर्ण,
	अणु "krb5p",	Opt_sec_krb5p पूर्ण,
	अणु "lkey",	Opt_sec_lkey पूर्ण,
	अणु "lkeyi",	Opt_sec_lkeyi पूर्ण,
	अणु "lkeyp",	Opt_sec_lkeyp पूर्ण,
	अणु "none",	Opt_sec_none पूर्ण,
	अणु "null",	Opt_sec_none पूर्ण,
	अणु "spkm3",	Opt_sec_spkm पूर्ण,
	अणु "spkm3i",	Opt_sec_spkmi पूर्ण,
	अणु "spkm3p",	Opt_sec_spkmp पूर्ण,
	अणु "sys",	Opt_sec_sys पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Sanity-check a server address provided by the mount command.
 *
 * Address family must be initialized, and address must not be
 * the ANY address क्रम that family.
 */
अटल पूर्णांक nfs_verअगरy_server_address(काष्ठा sockaddr *addr)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET: अणु
		काष्ठा sockaddr_in *sa = (काष्ठा sockaddr_in *)addr;
		वापस sa->sin_addr.s_addr != htonl(INADDR_ANY);
	पूर्ण
	हाल AF_INET6: अणु
		काष्ठा in6_addr *sa = &((काष्ठा sockaddr_in6 *)addr)->sin6_addr;
		वापस !ipv6_addr_any(sa);
	पूर्ण
	पूर्ण

	dfprपूर्णांकk(MOUNT, "NFS: Invalid IP address specified\n");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NFS_DISABLE_UDP_SUPPORT
अटल bool nfs_server_transport_udp_invalid(स्थिर काष्ठा nfs_fs_context *ctx)
अणु
	वापस true;
पूर्ण
#अन्यथा
अटल bool nfs_server_transport_udp_invalid(स्थिर काष्ठा nfs_fs_context *ctx)
अणु
	अगर (ctx->version == 4)
		वापस true;
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Sanity check the NFS transport protocol.
 */
अटल पूर्णांक nfs_validate_transport_protocol(काष्ठा fs_context *fc,
					   काष्ठा nfs_fs_context *ctx)
अणु
	चयन (ctx->nfs_server.protocol) अणु
	हाल XPRT_TRANSPORT_UDP:
		अगर (nfs_server_transport_udp_invalid(ctx))
			जाओ out_invalid_transport_udp;
		अवरोध;
	हाल XPRT_TRANSPORT_TCP:
	हाल XPRT_TRANSPORT_RDMA:
		अवरोध;
	शेष:
		ctx->nfs_server.protocol = XPRT_TRANSPORT_TCP;
	पूर्ण
	वापस 0;
out_invalid_transport_udp:
	वापस nfs_invalf(fc, "NFS: Unsupported transport protocol udp");
पूर्ण

/*
 * For text based NFSv2/v3 mounts, the mount protocol transport शेष
 * settings should depend upon the specअगरied NFS transport.
 */
अटल व्योम nfs_set_mount_transport_protocol(काष्ठा nfs_fs_context *ctx)
अणु
	अगर (ctx->mount_server.protocol == XPRT_TRANSPORT_UDP ||
	    ctx->mount_server.protocol == XPRT_TRANSPORT_TCP)
			वापस;
	चयन (ctx->nfs_server.protocol) अणु
	हाल XPRT_TRANSPORT_UDP:
		ctx->mount_server.protocol = XPRT_TRANSPORT_UDP;
		अवरोध;
	हाल XPRT_TRANSPORT_TCP:
	हाल XPRT_TRANSPORT_RDMA:
		ctx->mount_server.protocol = XPRT_TRANSPORT_TCP;
	पूर्ण
पूर्ण

/*
 * Add 'flavor' to 'auth_info' अगर not alपढ़ोy present.
 * Returns true अगर 'flavor' ends up in the list, false otherwise
 */
अटल पूर्णांक nfs_auth_info_add(काष्ठा fs_context *fc,
			     काष्ठा nfs_auth_info *auth_info,
			     rpc_authflavor_t flavor)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक max_flavor_len = ARRAY_SIZE(auth_info->flavors);

	/* make sure this flavor isn't alपढ़ोy in the list */
	क्रम (i = 0; i < auth_info->flavor_len; i++) अणु
		अगर (flavor == auth_info->flavors[i])
			वापस 0;
	पूर्ण

	अगर (auth_info->flavor_len + 1 >= max_flavor_len)
		वापस nfs_invalf(fc, "NFS: too many sec= flavors");

	auth_info->flavors[auth_info->flavor_len++] = flavor;
	वापस 0;
पूर्ण

/*
 * Parse the value of the 'sec=' option.
 */
अटल पूर्णांक nfs_parse_security_flavors(काष्ठा fs_context *fc,
				      काष्ठा fs_parameter *param)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	rpc_authflavor_t pseuकरोflavor;
	अक्षर *string = param->string, *p;
	पूर्णांक ret;

	dfprपूर्णांकk(MOUNT, "NFS: parsing %s=%s option\n", param->key, param->string);

	जबतक ((p = strsep(&string, ":")) != शून्य) अणु
		अगर (!*p)
			जारी;
		चयन (lookup_स्थिरant(nfs_secflavor_tokens, p, -1)) अणु
		हाल Opt_sec_none:
			pseuकरोflavor = RPC_AUTH_शून्य;
			अवरोध;
		हाल Opt_sec_sys:
			pseuकरोflavor = RPC_AUTH_UNIX;
			अवरोध;
		हाल Opt_sec_krb5:
			pseuकरोflavor = RPC_AUTH_GSS_KRB5;
			अवरोध;
		हाल Opt_sec_krb5i:
			pseuकरोflavor = RPC_AUTH_GSS_KRB5I;
			अवरोध;
		हाल Opt_sec_krb5p:
			pseuकरोflavor = RPC_AUTH_GSS_KRB5P;
			अवरोध;
		हाल Opt_sec_lkey:
			pseuकरोflavor = RPC_AUTH_GSS_LKEY;
			अवरोध;
		हाल Opt_sec_lkeyi:
			pseuकरोflavor = RPC_AUTH_GSS_LKEYI;
			अवरोध;
		हाल Opt_sec_lkeyp:
			pseuकरोflavor = RPC_AUTH_GSS_LKEYP;
			अवरोध;
		हाल Opt_sec_spkm:
			pseuकरोflavor = RPC_AUTH_GSS_SPKM;
			अवरोध;
		हाल Opt_sec_spkmi:
			pseuकरोflavor = RPC_AUTH_GSS_SPKMI;
			अवरोध;
		हाल Opt_sec_spkmp:
			pseuकरोflavor = RPC_AUTH_GSS_SPKMP;
			अवरोध;
		शेष:
			वापस nfs_invalf(fc, "NFS: sec=%s option not recognized", p);
		पूर्ण

		ret = nfs_auth_info_add(fc, &ctx->auth_info, pseuकरोflavor);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfs_parse_version_string(काष्ठा fs_context *fc,
				    स्थिर अक्षर *string)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);

	ctx->flags &= ~NFS_MOUNT_VER3;
	चयन (lookup_स्थिरant(nfs_vers_tokens, string, -1)) अणु
	हाल Opt_vers_2:
		ctx->version = 2;
		अवरोध;
	हाल Opt_vers_3:
		ctx->flags |= NFS_MOUNT_VER3;
		ctx->version = 3;
		अवरोध;
	हाल Opt_vers_4:
		/* Backward compatibility option. In future,
		 * the mount program should always supply
		 * a NFSv4 minor version number.
		 */
		ctx->version = 4;
		अवरोध;
	हाल Opt_vers_4_0:
		ctx->version = 4;
		ctx->minorversion = 0;
		अवरोध;
	हाल Opt_vers_4_1:
		ctx->version = 4;
		ctx->minorversion = 1;
		अवरोध;
	हाल Opt_vers_4_2:
		ctx->version = 4;
		ctx->minorversion = 2;
		अवरोध;
	शेष:
		वापस nfs_invalf(fc, "NFS: Unsupported NFS version");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Parse a single mount parameter.
 */
अटल पूर्णांक nfs_fs_context_parse_param(काष्ठा fs_context *fc,
				      काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	अचिन्हित लघु protofamily, mountfamily;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret, opt;

	dfprपूर्णांकk(MOUNT, "NFS:   parsing nfs mount option '%s'\n", param->key);

	opt = fs_parse(fc, nfs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस ctx->sloppy ? 1 : opt;

	अगर (fc->security)
		ctx->has_sec_mnt_opts = 1;

	चयन (opt) अणु
	हाल Opt_source:
		अगर (fc->source)
			वापस nfs_invalf(fc, "NFS: Multiple sources not supported");
		fc->source = param->string;
		param->string = शून्य;
		अवरोध;

		/*
		 * boolean options:  foo/nofoo
		 */
	हाल Opt_soft:
		ctx->flags |= NFS_MOUNT_SOFT;
		ctx->flags &= ~NFS_MOUNT_SOFTERR;
		अवरोध;
	हाल Opt_softerr:
		ctx->flags |= NFS_MOUNT_SOFTERR | NFS_MOUNT_SOFTREVAL;
		ctx->flags &= ~NFS_MOUNT_SOFT;
		अवरोध;
	हाल Opt_hard:
		ctx->flags &= ~(NFS_MOUNT_SOFT |
				NFS_MOUNT_SOFTERR |
				NFS_MOUNT_SOFTREVAL);
		अवरोध;
	हाल Opt_softreval:
		अगर (result.negated)
			ctx->flags &= ~NFS_MOUNT_SOFTREVAL;
		अन्यथा
			ctx->flags &= NFS_MOUNT_SOFTREVAL;
		अवरोध;
	हाल Opt_posix:
		अगर (result.negated)
			ctx->flags &= ~NFS_MOUNT_POSIX;
		अन्यथा
			ctx->flags |= NFS_MOUNT_POSIX;
		अवरोध;
	हाल Opt_cto:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_NOCTO;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_NOCTO;
		अवरोध;
	हाल Opt_ac:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_NOAC;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_NOAC;
		अवरोध;
	हाल Opt_lock:
		अगर (result.negated) अणु
			ctx->flags |= NFS_MOUNT_NONLM;
			ctx->flags |= (NFS_MOUNT_LOCAL_FLOCK | NFS_MOUNT_LOCAL_FCNTL);
		पूर्ण अन्यथा अणु
			ctx->flags &= ~NFS_MOUNT_NONLM;
			ctx->flags &= ~(NFS_MOUNT_LOCAL_FLOCK | NFS_MOUNT_LOCAL_FCNTL);
		पूर्ण
		अवरोध;
	हाल Opt_udp:
		ctx->flags &= ~NFS_MOUNT_TCP;
		ctx->nfs_server.protocol = XPRT_TRANSPORT_UDP;
		अवरोध;
	हाल Opt_tcp:
	हाल Opt_rdma:
		ctx->flags |= NFS_MOUNT_TCP; /* क्रम side protocols */
		ret = xprt_find_transport_ident(param->key);
		अगर (ret < 0)
			जाओ out_bad_transport;
		ctx->nfs_server.protocol = ret;
		अवरोध;
	हाल Opt_acl:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_NOACL;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_NOACL;
		अवरोध;
	हाल Opt_rdirplus:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_NORसूचीPLUS;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_NORसूचीPLUS;
		अवरोध;
	हाल Opt_sharecache:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_UNSHARED;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_UNSHARED;
		अवरोध;
	हाल Opt_resvport:
		अगर (result.negated)
			ctx->flags |= NFS_MOUNT_NORESVPORT;
		अन्यथा
			ctx->flags &= ~NFS_MOUNT_NORESVPORT;
		अवरोध;
	हाल Opt_fscache_flag:
		अगर (result.negated)
			ctx->options &= ~NFS_OPTION_FSCACHE;
		अन्यथा
			ctx->options |= NFS_OPTION_FSCACHE;
		kमुक्त(ctx->fscache_uniq);
		ctx->fscache_uniq = शून्य;
		अवरोध;
	हाल Opt_fscache:
		ctx->options |= NFS_OPTION_FSCACHE;
		kमुक्त(ctx->fscache_uniq);
		ctx->fscache_uniq = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_migration:
		अगर (result.negated)
			ctx->options &= ~NFS_OPTION_MIGRATION;
		अन्यथा
			ctx->options |= NFS_OPTION_MIGRATION;
		अवरोध;

		/*
		 * options that take numeric values
		 */
	हाल Opt_port:
		अगर (result.uपूर्णांक_32 > अच_लघु_उच्च)
			जाओ out_of_bounds;
		ctx->nfs_server.port = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_rsize:
		ctx->rsize = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_wsize:
		ctx->wsize = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_bsize:
		ctx->bsize = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_समयo:
		अगर (result.uपूर्णांक_32 < 1 || result.uपूर्णांक_32 > पूर्णांक_उच्च)
			जाओ out_of_bounds;
		ctx->समयo = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_retrans:
		अगर (result.uपूर्णांक_32 > पूर्णांक_उच्च)
			जाओ out_of_bounds;
		ctx->retrans = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_acregmin:
		ctx->acregmin = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_acregmax:
		ctx->acregmax = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_acdirmin:
		ctx->acdirmin = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_acdirmax:
		ctx->acdirmax = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_aस_समयo:
		ctx->acregmin = result.uपूर्णांक_32;
		ctx->acregmax = result.uपूर्णांक_32;
		ctx->acdirmin = result.uपूर्णांक_32;
		ctx->acdirmax = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_namelen:
		ctx->namlen = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_mountport:
		अगर (result.uपूर्णांक_32 > अच_लघु_उच्च)
			जाओ out_of_bounds;
		ctx->mount_server.port = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_mountvers:
		अगर (result.uपूर्णांक_32 < NFS_MNT_VERSION ||
		    result.uपूर्णांक_32 > NFS_MNT3_VERSION)
			जाओ out_of_bounds;
		ctx->mount_server.version = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_minorversion:
		अगर (result.uपूर्णांक_32 > NFS4_MAX_MINOR_VERSION)
			जाओ out_of_bounds;
		ctx->minorversion = result.uपूर्णांक_32;
		अवरोध;

		/*
		 * options that take text values
		 */
	हाल Opt_v:
		ret = nfs_parse_version_string(fc, param->key + 1);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल Opt_vers:
		ret = nfs_parse_version_string(fc, param->string);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल Opt_sec:
		ret = nfs_parse_security_flavors(fc, param);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल Opt_proto:
		protofamily = AF_INET;
		चयन (lookup_स्थिरant(nfs_xprt_protocol_tokens, param->string, -1)) अणु
		हाल Opt_xprt_udp6:
			protofamily = AF_INET6;
			fallthrough;
		हाल Opt_xprt_udp:
			ctx->flags &= ~NFS_MOUNT_TCP;
			ctx->nfs_server.protocol = XPRT_TRANSPORT_UDP;
			अवरोध;
		हाल Opt_xprt_tcp6:
			protofamily = AF_INET6;
			fallthrough;
		हाल Opt_xprt_tcp:
			ctx->flags |= NFS_MOUNT_TCP;
			ctx->nfs_server.protocol = XPRT_TRANSPORT_TCP;
			अवरोध;
		हाल Opt_xprt_rdma6:
			protofamily = AF_INET6;
			fallthrough;
		हाल Opt_xprt_rdma:
			/* vector side protocols to TCP */
			ctx->flags |= NFS_MOUNT_TCP;
			ret = xprt_find_transport_ident(param->string);
			अगर (ret < 0)
				जाओ out_bad_transport;
			ctx->nfs_server.protocol = ret;
			अवरोध;
		शेष:
			जाओ out_bad_transport;
		पूर्ण

		ctx->protofamily = protofamily;
		अवरोध;

	हाल Opt_mountproto:
		mountfamily = AF_INET;
		चयन (lookup_स्थिरant(nfs_xprt_protocol_tokens, param->string, -1)) अणु
		हाल Opt_xprt_udp6:
			mountfamily = AF_INET6;
			fallthrough;
		हाल Opt_xprt_udp:
			ctx->mount_server.protocol = XPRT_TRANSPORT_UDP;
			अवरोध;
		हाल Opt_xprt_tcp6:
			mountfamily = AF_INET6;
			fallthrough;
		हाल Opt_xprt_tcp:
			ctx->mount_server.protocol = XPRT_TRANSPORT_TCP;
			अवरोध;
		हाल Opt_xprt_rdma: /* not used क्रम side protocols */
		शेष:
			जाओ out_bad_transport;
		पूर्ण
		ctx->mountfamily = mountfamily;
		अवरोध;

	हाल Opt_addr:
		len = rpc_pton(fc->net_ns, param->string, param->size,
			       &ctx->nfs_server.address,
			       माप(ctx->nfs_server._address));
		अगर (len == 0)
			जाओ out_invalid_address;
		ctx->nfs_server.addrlen = len;
		अवरोध;
	हाल Opt_clientaddr:
		kमुक्त(ctx->client_address);
		ctx->client_address = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_mounthost:
		kमुक्त(ctx->mount_server.hostname);
		ctx->mount_server.hostname = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_mountaddr:
		len = rpc_pton(fc->net_ns, param->string, param->size,
			       &ctx->mount_server.address,
			       माप(ctx->mount_server._address));
		अगर (len == 0)
			जाओ out_invalid_address;
		ctx->mount_server.addrlen = len;
		अवरोध;
	हाल Opt_nconnect:
		अगर (result.uपूर्णांक_32 < 1 || result.uपूर्णांक_32 > NFS_MAX_CONNECTIONS)
			जाओ out_of_bounds;
		ctx->nfs_server.nconnect = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_lookupcache:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_lookupcache_all:
			ctx->flags &= ~(NFS_MOUNT_LOOKUP_CACHE_NONEG|NFS_MOUNT_LOOKUP_CACHE_NONE);
			अवरोध;
		हाल Opt_lookupcache_positive:
			ctx->flags &= ~NFS_MOUNT_LOOKUP_CACHE_NONE;
			ctx->flags |= NFS_MOUNT_LOOKUP_CACHE_NONEG;
			अवरोध;
		हाल Opt_lookupcache_none:
			ctx->flags |= NFS_MOUNT_LOOKUP_CACHE_NONEG|NFS_MOUNT_LOOKUP_CACHE_NONE;
			अवरोध;
		शेष:
			जाओ out_invalid_value;
		पूर्ण
		अवरोध;
	हाल Opt_local_lock:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_local_lock_all:
			ctx->flags |= (NFS_MOUNT_LOCAL_FLOCK |
				       NFS_MOUNT_LOCAL_FCNTL);
			अवरोध;
		हाल Opt_local_lock_flock:
			ctx->flags |= NFS_MOUNT_LOCAL_FLOCK;
			अवरोध;
		हाल Opt_local_lock_posix:
			ctx->flags |= NFS_MOUNT_LOCAL_FCNTL;
			अवरोध;
		हाल Opt_local_lock_none:
			ctx->flags &= ~(NFS_MOUNT_LOCAL_FLOCK |
					NFS_MOUNT_LOCAL_FCNTL);
			अवरोध;
		शेष:
			जाओ out_invalid_value;
		पूर्ण
		अवरोध;
	हाल Opt_ग_लिखो:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_ग_लिखो_lazy:
			ctx->flags &=
				~(NFS_MOUNT_WRITE_EAGER | NFS_MOUNT_WRITE_WAIT);
			अवरोध;
		हाल Opt_ग_लिखो_eager:
			ctx->flags |= NFS_MOUNT_WRITE_EAGER;
			ctx->flags &= ~NFS_MOUNT_WRITE_WAIT;
			अवरोध;
		हाल Opt_ग_लिखो_रुको:
			ctx->flags |=
				NFS_MOUNT_WRITE_EAGER | NFS_MOUNT_WRITE_WAIT;
			अवरोध;
		शेष:
			जाओ out_invalid_value;
		पूर्ण
		अवरोध;

		/*
		 * Special options
		 */
	हाल Opt_sloppy:
		ctx->sloppy = true;
		dfprपूर्णांकk(MOUNT, "NFS:   relaxing parsing rules\n");
		अवरोध;
	पूर्ण

	वापस 0;

out_invalid_value:
	वापस nfs_invalf(fc, "NFS: Bad mount option value specified");
out_invalid_address:
	वापस nfs_invalf(fc, "NFS: Bad IP address specified");
out_of_bounds:
	वापस nfs_invalf(fc, "NFS: Value for '%s' out of range", param->key);
out_bad_transport:
	वापस nfs_invalf(fc, "NFS: Unrecognized transport protocol");
पूर्ण

/*
 * Split fc->source पूर्णांकo "hostname:export_path".
 *
 * The lefपंचांगost colon demarks the split between the server's hostname
 * and the export path.  If the hostname starts with a left square
 * bracket, then it may contain colons.
 *
 * Note: caller मुक्तs hostname and export path, even on error.
 */
अटल पूर्णांक nfs_parse_source(काष्ठा fs_context *fc,
			    माप_प्रकार maxnamlen, माप_प्रकार maxpathlen)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	स्थिर अक्षर *dev_name = fc->source;
	माप_प्रकार len;
	स्थिर अक्षर *end;

	अगर (unlikely(!dev_name || !*dev_name)) अणु
		dfprपूर्णांकk(MOUNT, "NFS: device name not specified\n");
		वापस -EINVAL;
	पूर्ण

	/* Is the host name रक्षित with square brakcets? */
	अगर (*dev_name == '[') अणु
		end = म_अक्षर(++dev_name, ']');
		अगर (end == शून्य || end[1] != ':')
			जाओ out_bad_devname;

		len = end - dev_name;
		end++;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *comma;

		end = म_अक्षर(dev_name, ':');
		अगर (end == शून्य)
			जाओ out_bad_devname;
		len = end - dev_name;

		/* समाप्त possible hostname list: not supported */
		comma = स_प्रथम(dev_name, ',', len);
		अगर (comma)
			len = comma - dev_name;
	पूर्ण

	अगर (len > maxnamlen)
		जाओ out_hostname;

	kमुक्त(ctx->nfs_server.hostname);

	/* N.B. caller will मुक्त nfs_server.hostname in all हालs */
	ctx->nfs_server.hostname = kmemdup_nul(dev_name, len, GFP_KERNEL);
	अगर (!ctx->nfs_server.hostname)
		जाओ out_nomem;
	len = म_माप(++end);
	अगर (len > maxpathlen)
		जाओ out_path;
	ctx->nfs_server.export_path = kmemdup_nul(end, len, GFP_KERNEL);
	अगर (!ctx->nfs_server.export_path)
		जाओ out_nomem;

	dfprपूर्णांकk(MOUNT, "NFS: MNTPATH: '%s'\n", ctx->nfs_server.export_path);
	वापस 0;

out_bad_devname:
	वापस nfs_invalf(fc, "NFS: device name not in host:path format");
out_nomem:
	nfs_errorf(fc, "NFS: not enough memory to parse device name");
	वापस -ENOMEM;
out_hostname:
	nfs_errorf(fc, "NFS: server hostname too long");
	वापस -ENAMETOOLONG;
out_path:
	nfs_errorf(fc, "NFS: export pathname too long");
	वापस -ENAMETOOLONG;
पूर्ण

अटल अंतरभूत bool is_remount_fc(काष्ठा fs_context *fc)
अणु
	वापस fc->root != शून्य;
पूर्ण

/*
 * Parse monolithic NFS2/NFS3 mount data
 * - fills in the mount root filehandle
 *
 * For option strings, user space handles the following behaviors:
 *
 * + DNS: mapping server host name to IP address ("addr=" option)
 *
 * + failure mode: how to behave अगर a mount request can't be handled
 *   immediately ("fg/bg" option)
 *
 * + retry: how often to retry a mount request ("retry=" option)
 *
 * + अवरोधing back: trying proto=udp after proto=tcp, v2 after v3,
 *   mountproto=tcp after mountproto=udp, and so on
 */
अटल पूर्णांक nfs23_parse_monolithic(काष्ठा fs_context *fc,
				  काष्ठा nfs_mount_data *data)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_fh *mntfh = ctx->mntfh;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&ctx->nfs_server.address;
	पूर्णांक extra_flags = NFS_MOUNT_LEGACY_INTERFACE;
	पूर्णांक ret;

	अगर (data == शून्य)
		जाओ out_no_data;

	ctx->version = NFS_DEFAULT_VERSION;
	चयन (data->version) अणु
	हाल 1:
		data->namlen = 0;
		fallthrough;
	हाल 2:
		data->bsize = 0;
		fallthrough;
	हाल 3:
		अगर (data->flags & NFS_MOUNT_VER3)
			जाओ out_no_v3;
		data->root.size = NFS2_FHSIZE;
		स_नकल(data->root.data, data->old_root.data, NFS2_FHSIZE);
		/* Turn off security negotiation */
		extra_flags |= NFS_MOUNT_SECFLAVOUR;
		fallthrough;
	हाल 4:
		अगर (data->flags & NFS_MOUNT_SECFLAVOUR)
			जाओ out_no_sec;
		fallthrough;
	हाल 5:
		स_रखो(data->context, 0, माप(data->context));
		fallthrough;
	हाल 6:
		अगर (data->flags & NFS_MOUNT_VER3) अणु
			अगर (data->root.size > NFS3_FHSIZE || data->root.size == 0)
				जाओ out_invalid_fh;
			mntfh->size = data->root.size;
			ctx->version = 3;
		पूर्ण अन्यथा अणु
			mntfh->size = NFS2_FHSIZE;
			ctx->version = 2;
		पूर्ण


		स_नकल(mntfh->data, data->root.data, mntfh->size);
		अगर (mntfh->size < माप(mntfh->data))
			स_रखो(mntfh->data + mntfh->size, 0,
			       माप(mntfh->data) - mntfh->size);

		/*
		 * क्रम proto == XPRT_TRANSPORT_UDP, which is what uses
		 * to_exponential, implying shअगरt: limit the shअगरt value
		 * to BITS_PER_LONG (majorसमयo is अचिन्हित दीर्घ)
		 */
		अगर (!(data->flags & NFS_MOUNT_TCP)) /* this will be UDP */
			अगर (data->retrans >= 64) /* shअगरt value is too large */
				जाओ out_invalid_data;

		/*
		 * Translate to nfs_fs_context, which nfs_fill_super
		 * can deal with.
		 */
		ctx->flags	= data->flags & NFS_MOUNT_FLAGMASK;
		ctx->flags	|= extra_flags;
		ctx->rsize	= data->rsize;
		ctx->wsize	= data->wsize;
		ctx->समयo	= data->समयo;
		ctx->retrans	= data->retrans;
		ctx->acregmin	= data->acregmin;
		ctx->acregmax	= data->acregmax;
		ctx->acdirmin	= data->acdirmin;
		ctx->acdirmax	= data->acdirmax;
		ctx->need_mount	= false;

		स_नकल(sap, &data->addr, माप(data->addr));
		ctx->nfs_server.addrlen = माप(data->addr);
		ctx->nfs_server.port = ntohs(data->addr.sin_port);
		अगर (sap->sa_family != AF_INET ||
		    !nfs_verअगरy_server_address(sap))
			जाओ out_no_address;

		अगर (!(data->flags & NFS_MOUNT_TCP))
			ctx->nfs_server.protocol = XPRT_TRANSPORT_UDP;
		/* N.B. caller will मुक्त nfs_server.hostname in all हालs */
		ctx->nfs_server.hostname = kstrdup(data->hostname, GFP_KERNEL);
		अगर (!ctx->nfs_server.hostname)
			जाओ out_nomem;

		ctx->namlen		= data->namlen;
		ctx->bsize		= data->bsize;

		अगर (data->flags & NFS_MOUNT_SECFLAVOUR)
			ctx->selected_flavor = data->pseuकरोflavor;
		अन्यथा
			ctx->selected_flavor = RPC_AUTH_UNIX;

		अगर (!(data->flags & NFS_MOUNT_NONLM))
			ctx->flags &= ~(NFS_MOUNT_LOCAL_FLOCK|
					 NFS_MOUNT_LOCAL_FCNTL);
		अन्यथा
			ctx->flags |= (NFS_MOUNT_LOCAL_FLOCK|
					NFS_MOUNT_LOCAL_FCNTL);

		/*
		 * The legacy version 6 binary mount data from userspace has a
		 * field used only to transport selinux inक्रमmation पूर्णांकo the
		 * kernel.  To जारी to support that functionality we
		 * have a touch of selinux knowledge here in the NFS code. The
		 * userspace code converted context=blah to just blah so we are
		 * converting back to the full string selinux understands.
		 */
		अगर (data->context[0])अणु
#अगर_घोषित CONFIG_SECURITY_SELINUX
			पूर्णांक ret;

			data->context[NFS_MAX_CONTEXT_LEN] = '\0';
			ret = vfs_parse_fs_string(fc, "context",
						  data->context, म_माप(data->context));
			अगर (ret < 0)
				वापस ret;
#अन्यथा
			वापस -EINVAL;
#पूर्ण_अगर
		पूर्ण

		अवरोध;
	शेष:
		जाओ generic;
	पूर्ण

	ret = nfs_validate_transport_protocol(fc, ctx);
	अगर (ret)
		वापस ret;

	ctx->skip_reconfig_option_check = true;
	वापस 0;

generic:
	वापस generic_parse_monolithic(fc, data);

out_no_data:
	अगर (is_remount_fc(fc)) अणु
		ctx->skip_reconfig_option_check = true;
		वापस 0;
	पूर्ण
	वापस nfs_invalf(fc, "NFS: mount program didn't pass any mount data");

out_no_v3:
	वापस nfs_invalf(fc, "NFS: nfs_mount_data version does not support v3");

out_no_sec:
	वापस nfs_invalf(fc, "NFS: nfs_mount_data version supports only AUTH_SYS");

out_nomem:
	dfprपूर्णांकk(MOUNT, "NFS: not enough memory to handle mount options");
	वापस -ENOMEM;

out_no_address:
	वापस nfs_invalf(fc, "NFS: mount program didn't pass remote address");

out_invalid_fh:
	वापस nfs_invalf(fc, "NFS: invalid root filehandle");

out_invalid_data:
	वापस nfs_invalf(fc, "NFS: invalid binary mount data");
पूर्ण

#अगर IS_ENABLED(CONFIG_NFS_V4)
काष्ठा compat_nfs_string अणु
	compat_uपूर्णांक_t len;
	compat_uptr_t data;
पूर्ण;

अटल अंतरभूत व्योम compat_nfs_string(काष्ठा nfs_string *dst,
				     काष्ठा compat_nfs_string *src)
अणु
	dst->data = compat_ptr(src->data);
	dst->len = src->len;
पूर्ण

काष्ठा compat_nfs4_mount_data_v1 अणु
	compat_पूर्णांक_t version;
	compat_पूर्णांक_t flags;
	compat_पूर्णांक_t rsize;
	compat_पूर्णांक_t wsize;
	compat_पूर्णांक_t समयo;
	compat_पूर्णांक_t retrans;
	compat_पूर्णांक_t acregmin;
	compat_पूर्णांक_t acregmax;
	compat_पूर्णांक_t acdirmin;
	compat_पूर्णांक_t acdirmax;
	काष्ठा compat_nfs_string client_addr;
	काष्ठा compat_nfs_string mnt_path;
	काष्ठा compat_nfs_string hostname;
	compat_uपूर्णांक_t host_addrlen;
	compat_uptr_t host_addr;
	compat_पूर्णांक_t proto;
	compat_पूर्णांक_t auth_flavourlen;
	compat_uptr_t auth_flavours;
पूर्ण;

अटल व्योम nfs4_compat_mount_data_conv(काष्ठा nfs4_mount_data *data)
अणु
	काष्ठा compat_nfs4_mount_data_v1 *compat =
			(काष्ठा compat_nfs4_mount_data_v1 *)data;

	/* copy the fields backwards */
	data->auth_flavours = compat_ptr(compat->auth_flavours);
	data->auth_flavourlen = compat->auth_flavourlen;
	data->proto = compat->proto;
	data->host_addr = compat_ptr(compat->host_addr);
	data->host_addrlen = compat->host_addrlen;
	compat_nfs_string(&data->hostname, &compat->hostname);
	compat_nfs_string(&data->mnt_path, &compat->mnt_path);
	compat_nfs_string(&data->client_addr, &compat->client_addr);
	data->acdirmax = compat->acdirmax;
	data->acdirmin = compat->acdirmin;
	data->acregmax = compat->acregmax;
	data->acregmin = compat->acregmin;
	data->retrans = compat->retrans;
	data->समयo = compat->समयo;
	data->wsize = compat->wsize;
	data->rsize = compat->rsize;
	data->flags = compat->flags;
	data->version = compat->version;
पूर्ण

/*
 * Validate NFSv4 mount options
 */
अटल पूर्णांक nfs4_parse_monolithic(काष्ठा fs_context *fc,
				 काष्ठा nfs4_mount_data *data)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&ctx->nfs_server.address;
	पूर्णांक ret;
	अक्षर *c;

	अगर (!data) अणु
		अगर (is_remount_fc(fc))
			जाओ करोne;
		वापस nfs_invalf(fc,
			"NFS4: mount program didn't pass any mount data");
	पूर्ण

	ctx->version = 4;

	अगर (data->version != 1)
		वापस generic_parse_monolithic(fc, data);

	अगर (in_compat_syscall())
		nfs4_compat_mount_data_conv(data);

	अगर (data->host_addrlen > माप(ctx->nfs_server.address))
		जाओ out_no_address;
	अगर (data->host_addrlen == 0)
		जाओ out_no_address;
	ctx->nfs_server.addrlen = data->host_addrlen;
	अगर (copy_from_user(sap, data->host_addr, data->host_addrlen))
		वापस -EFAULT;
	अगर (!nfs_verअगरy_server_address(sap))
		जाओ out_no_address;
	ctx->nfs_server.port = ntohs(((काष्ठा sockaddr_in *)sap)->sin_port);

	अगर (data->auth_flavourlen) अणु
		rpc_authflavor_t pseuकरोflavor;

		अगर (data->auth_flavourlen > 1)
			जाओ out_inval_auth;
		अगर (copy_from_user(&pseuकरोflavor, data->auth_flavours,
				   माप(pseuकरोflavor)))
			वापस -EFAULT;
		ctx->selected_flavor = pseuकरोflavor;
	पूर्ण अन्यथा अणु
		ctx->selected_flavor = RPC_AUTH_UNIX;
	पूर्ण

	c = strndup_user(data->hostname.data, NFS4_MAXNAMLEN);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	ctx->nfs_server.hostname = c;

	c = strndup_user(data->mnt_path.data, NFS4_MAXPATHLEN);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	ctx->nfs_server.export_path = c;
	dfprपूर्णांकk(MOUNT, "NFS: MNTPATH: '%s'\n", c);

	c = strndup_user(data->client_addr.data, 16);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);
	ctx->client_address = c;

	/*
	 * Translate to nfs_fs_context, which nfs_fill_super
	 * can deal with.
	 */

	ctx->flags	= data->flags & NFS4_MOUNT_FLAGMASK;
	ctx->rsize	= data->rsize;
	ctx->wsize	= data->wsize;
	ctx->समयo	= data->समयo;
	ctx->retrans	= data->retrans;
	ctx->acregmin	= data->acregmin;
	ctx->acregmax	= data->acregmax;
	ctx->acdirmin	= data->acdirmin;
	ctx->acdirmax	= data->acdirmax;
	ctx->nfs_server.protocol = data->proto;
	ret = nfs_validate_transport_protocol(fc, ctx);
	अगर (ret)
		वापस ret;
करोne:
	ctx->skip_reconfig_option_check = true;
	वापस 0;

out_inval_auth:
	वापस nfs_invalf(fc, "NFS4: Invalid number of RPC auth flavours %d",
		      data->auth_flavourlen);

out_no_address:
	वापस nfs_invalf(fc, "NFS4: mount program didn't pass remote address");
पूर्ण
#पूर्ण_अगर

/*
 * Parse a monolithic block of data from sys_mount().
 */
अटल पूर्णांक nfs_fs_context_parse_monolithic(काष्ठा fs_context *fc,
					   व्योम *data)
अणु
	अगर (fc->fs_type == &nfs_fs_type)
		वापस nfs23_parse_monolithic(fc, data);

#अगर IS_ENABLED(CONFIG_NFS_V4)
	अगर (fc->fs_type == &nfs4_fs_type)
		वापस nfs4_parse_monolithic(fc, data);
#पूर्ण_अगर

	वापस nfs_invalf(fc, "NFS: Unsupported monolithic data version");
पूर्ण

/*
 * Validate the preparsed inक्रमmation in the config.
 */
अटल पूर्णांक nfs_fs_context_validate(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_subversion *nfs_mod;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&ctx->nfs_server.address;
	पूर्णांक max_namelen = PAGE_SIZE;
	पूर्णांक max_pathlen = NFS_MAXPATHLEN;
	पूर्णांक port = 0;
	पूर्णांक ret;

	अगर (!fc->source)
		जाओ out_no_device_name;

	/* Check क्रम sanity first. */
	अगर (ctx->minorversion && ctx->version != 4)
		जाओ out_minorversion_mismatch;

	अगर (ctx->options & NFS_OPTION_MIGRATION &&
	    (ctx->version != 4 || ctx->minorversion != 0))
		जाओ out_migration_misuse;

	/* Verअगरy that any proto=/mountproto= options match the address
	 * families in the addr=/mountaddr= options.
	 */
	अगर (ctx->protofamily != AF_UNSPEC &&
	    ctx->protofamily != ctx->nfs_server.address.sa_family)
		जाओ out_proto_mismatch;

	अगर (ctx->mountfamily != AF_UNSPEC) अणु
		अगर (ctx->mount_server.addrlen) अणु
			अगर (ctx->mountfamily != ctx->mount_server.address.sa_family)
				जाओ out_mountproto_mismatch;
		पूर्ण अन्यथा अणु
			अगर (ctx->mountfamily != ctx->nfs_server.address.sa_family)
				जाओ out_mountproto_mismatch;
		पूर्ण
	पूर्ण

	अगर (!nfs_verअगरy_server_address(sap))
		जाओ out_no_address;

	ret = nfs_validate_transport_protocol(fc, ctx);
	अगर (ret)
		वापस ret;

	अगर (ctx->version == 4) अणु
		अगर (IS_ENABLED(CONFIG_NFS_V4)) अणु
			अगर (ctx->nfs_server.protocol == XPRT_TRANSPORT_RDMA)
				port = NFS_RDMA_PORT;
			अन्यथा
				port = NFS_PORT;
			max_namelen = NFS4_MAXNAMLEN;
			max_pathlen = NFS4_MAXPATHLEN;
			ctx->flags &= ~(NFS_MOUNT_NONLM | NFS_MOUNT_NOACL |
					NFS_MOUNT_VER3 | NFS_MOUNT_LOCAL_FLOCK |
					NFS_MOUNT_LOCAL_FCNTL);
		पूर्ण अन्यथा अणु
			जाओ out_v4_not_compiled;
		पूर्ण
	पूर्ण अन्यथा अणु
		nfs_set_mount_transport_protocol(ctx);
		अगर (ctx->nfs_server.protocol == XPRT_TRANSPORT_RDMA)
			port = NFS_RDMA_PORT;
	पूर्ण

	nfs_set_port(sap, &ctx->nfs_server.port, port);

	ret = nfs_parse_source(fc, max_namelen, max_pathlen);
	अगर (ret < 0)
		वापस ret;

	/* Load the NFS protocol module अगर we haven't करोne so yet */
	अगर (!ctx->nfs_mod) अणु
		nfs_mod = get_nfs_version(ctx->version);
		अगर (IS_ERR(nfs_mod)) अणु
			ret = PTR_ERR(nfs_mod);
			जाओ out_version_unavailable;
		पूर्ण
		ctx->nfs_mod = nfs_mod;
	पूर्ण

	/* Ensure the fileप्रणाली context has the correct fs_type */
	अगर (fc->fs_type != ctx->nfs_mod->nfs_fs) अणु
		module_put(fc->fs_type->owner);
		__module_get(ctx->nfs_mod->nfs_fs->owner);
		fc->fs_type = ctx->nfs_mod->nfs_fs;
	पूर्ण
	वापस 0;

out_no_device_name:
	वापस nfs_invalf(fc, "NFS: Device name not specified");
out_v4_not_compiled:
	nfs_errorf(fc, "NFS: NFSv4 is not compiled into kernel");
	वापस -EPROTONOSUPPORT;
out_no_address:
	वापस nfs_invalf(fc, "NFS: mount program didn't pass remote address");
out_mountproto_mismatch:
	वापस nfs_invalf(fc, "NFS: Mount server address does not match mountproto= option");
out_proto_mismatch:
	वापस nfs_invalf(fc, "NFS: Server address does not match proto= option");
out_minorversion_mismatch:
	वापस nfs_invalf(fc, "NFS: Mount option vers=%u does not support minorversion=%u",
			  ctx->version, ctx->minorversion);
out_migration_misuse:
	वापस nfs_invalf(fc, "NFS: 'Migration' not supported for this NFS version");
out_version_unavailable:
	nfs_errorf(fc, "NFS: Version unavailable");
	वापस ret;
पूर्ण

/*
 * Create an NFS superblock by the appropriate method.
 */
अटल पूर्णांक nfs_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	पूर्णांक err = nfs_fs_context_validate(fc);

	अगर (err)
		वापस err;
	अगर (!ctx->पूर्णांकernal)
		वापस ctx->nfs_mod->rpc_ops->try_get_tree(fc);
	अन्यथा
		वापस nfs_get_tree_common(fc);
पूर्ण

/*
 * Handle duplication of a configuration.  The caller copied *src पूर्णांकo *sc, but
 * it can't deal with resource poपूर्णांकers in the fileप्रणाली context, so we have
 * to करो that.  We need to clear poपूर्णांकers, copy data or get extra refs as
 * appropriate.
 */
अटल पूर्णांक nfs_fs_context_dup(काष्ठा fs_context *fc, काष्ठा fs_context *src_fc)
अणु
	काष्ठा nfs_fs_context *src = nfs_fc2context(src_fc), *ctx;

	ctx = kmemdup(src, माप(काष्ठा nfs_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->mntfh = nfs_alloc_fhandle();
	अगर (!ctx->mntfh) अणु
		kमुक्त(ctx);
		वापस -ENOMEM;
	पूर्ण
	nfs_copy_fh(ctx->mntfh, src->mntfh);

	__module_get(ctx->nfs_mod->owner);
	ctx->client_address		= शून्य;
	ctx->mount_server.hostname	= शून्य;
	ctx->nfs_server.export_path	= शून्य;
	ctx->nfs_server.hostname	= शून्य;
	ctx->fscache_uniq		= शून्य;
	ctx->clone_data.fattr		= शून्य;
	fc->fs_निजी = ctx;
	वापस 0;
पूर्ण

अटल व्योम nfs_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);

	अगर (ctx) अणु
		अगर (ctx->server)
			nfs_मुक्त_server(ctx->server);
		अगर (ctx->nfs_mod)
			put_nfs_version(ctx->nfs_mod);
		kमुक्त(ctx->client_address);
		kमुक्त(ctx->mount_server.hostname);
		kमुक्त(ctx->nfs_server.export_path);
		kमुक्त(ctx->nfs_server.hostname);
		kमुक्त(ctx->fscache_uniq);
		nfs_मुक्त_fhandle(ctx->mntfh);
		nfs_मुक्त_fattr(ctx->clone_data.fattr);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fs_context_operations nfs_fs_context_ops = अणु
	.मुक्त			= nfs_fs_context_मुक्त,
	.dup			= nfs_fs_context_dup,
	.parse_param		= nfs_fs_context_parse_param,
	.parse_monolithic	= nfs_fs_context_parse_monolithic,
	.get_tree		= nfs_get_tree,
	.reconfigure		= nfs_reconfigure,
पूर्ण;

/*
 * Prepare superblock configuration.  We use the namespaces attached to the
 * context.  This may be the current process's namespaces, or it may be a
 * container's namespaces.
 */
अटल पूर्णांक nfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा nfs_fs_context), GFP_KERNEL);
	अगर (unlikely(!ctx))
		वापस -ENOMEM;

	ctx->mntfh = nfs_alloc_fhandle();
	अगर (unlikely(!ctx->mntfh)) अणु
		kमुक्त(ctx);
		वापस -ENOMEM;
	पूर्ण

	ctx->protofamily	= AF_UNSPEC;
	ctx->mountfamily	= AF_UNSPEC;
	ctx->mount_server.port	= NFS_UNSPEC_PORT;

	अगर (fc->root) अणु
		/* reconfigure, start with the current config */
		काष्ठा nfs_server *nfss = fc->root->d_sb->s_fs_info;
		काष्ठा net *net = nfss->nfs_client->cl_net;

		ctx->flags		= nfss->flags;
		ctx->rsize		= nfss->rsize;
		ctx->wsize		= nfss->wsize;
		ctx->retrans		= nfss->client->cl_समयout->to_retries;
		ctx->selected_flavor	= nfss->client->cl_auth->au_flavor;
		ctx->acregmin		= nfss->acregmin / HZ;
		ctx->acregmax		= nfss->acregmax / HZ;
		ctx->acdirmin		= nfss->acdirmin / HZ;
		ctx->acdirmax		= nfss->acdirmax / HZ;
		ctx->समयo		= 10U * nfss->client->cl_समयout->to_initval / HZ;
		ctx->nfs_server.port	= nfss->port;
		ctx->nfs_server.addrlen	= nfss->nfs_client->cl_addrlen;
		ctx->version		= nfss->nfs_client->rpc_ops->version;
		ctx->minorversion	= nfss->nfs_client->cl_minorversion;

		स_नकल(&ctx->nfs_server.address, &nfss->nfs_client->cl_addr,
			ctx->nfs_server.addrlen);

		अगर (fc->net_ns != net) अणु
			put_net(fc->net_ns);
			fc->net_ns = get_net(net);
		पूर्ण

		ctx->nfs_mod = nfss->nfs_client->cl_nfs_mod;
		__module_get(ctx->nfs_mod->owner);
	पूर्ण अन्यथा अणु
		/* शेषs */
		ctx->समयo		= NFS_UNSPEC_TIMEO;
		ctx->retrans		= NFS_UNSPEC_RETRANS;
		ctx->acregmin		= NFS_DEF_ACREGMIN;
		ctx->acregmax		= NFS_DEF_ACREGMAX;
		ctx->acdirmin		= NFS_DEF_ACसूचीMIN;
		ctx->acdirmax		= NFS_DEF_ACसूचीMAX;
		ctx->nfs_server.port	= NFS_UNSPEC_PORT;
		ctx->nfs_server.protocol = XPRT_TRANSPORT_TCP;
		ctx->selected_flavor	= RPC_AUTH_MAXFLAVOR;
		ctx->minorversion	= 0;
		ctx->need_mount		= true;

		fc->s_अगरlags		|= SB_I_STABLE_WRITES;
	पूर्ण
	fc->fs_निजी = ctx;
	fc->ops = &nfs_fs_context_ops;
	वापस 0;
पूर्ण

काष्ठा file_प्रणाली_type nfs_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "nfs",
	.init_fs_context	= nfs_init_fs_context,
	.parameters		= nfs_fs_parameters,
	.समाप्त_sb		= nfs_समाप्त_super,
	.fs_flags		= FS_RENAME_DOES_D_MOVE|FS_BINARY_MOUNTDATA,
पूर्ण;
MODULE_ALIAS_FS("nfs");
EXPORT_SYMBOL_GPL(nfs_fs_type);

#अगर IS_ENABLED(CONFIG_NFS_V4)
काष्ठा file_प्रणाली_type nfs4_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "nfs4",
	.init_fs_context	= nfs_init_fs_context,
	.parameters		= nfs_fs_parameters,
	.समाप्त_sb		= nfs_समाप्त_super,
	.fs_flags		= FS_RENAME_DOES_D_MOVE|FS_BINARY_MOUNTDATA,
पूर्ण;
MODULE_ALIAS_FS("nfs4");
MODULE_ALIAS("nfs4");
EXPORT_SYMBOL_GPL(nfs4_fs_type);
#पूर्ण_अगर /* CONFIG_NFS_V4 */
