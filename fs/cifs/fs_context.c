<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) 2020, Microsoft Corporation.
 *
 *   Author(s): Steve French <stfrench@microsoft.com>
 *              David Howells <dhowells@redhat.com>
 */

/*
#समावेश <linux/module.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/magic.h>
#समावेश <linux/security.h>
#समावेश <net/net_namespace.h>
*/

#समावेश <linux/प्रकार.स>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/parser.h>
#समावेश <linux/utsname.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश "ntlmssp.h"
#समावेश "nterr.h"
#समावेश "rfc1002pdu.h"
#समावेश "fs_context.h"

अटल स्थिर match_table_t cअगरs_smb_version_tokens = अणु
	अणु Smb_1, SMB1_VERSION_STRING पूर्ण,
	अणु Smb_20, SMB20_VERSION_STRINGपूर्ण,
	अणु Smb_21, SMB21_VERSION_STRING पूर्ण,
	अणु Smb_30, SMB30_VERSION_STRING पूर्ण,
	अणु Smb_302, SMB302_VERSION_STRING पूर्ण,
	अणु Smb_302, ALT_SMB302_VERSION_STRING पूर्ण,
	अणु Smb_311, SMB311_VERSION_STRING पूर्ण,
	अणु Smb_311, ALT_SMB311_VERSION_STRING पूर्ण,
	अणु Smb_3any, SMB3ANY_VERSION_STRING पूर्ण,
	अणु Smb_शेष, SMBDEFAULT_VERSION_STRING पूर्ण,
	अणु Smb_version_err, शून्य पूर्ण
पूर्ण;

अटल स्थिर match_table_t cअगरs_secflavor_tokens = अणु
	अणु Opt_sec_krb5, "krb5" पूर्ण,
	अणु Opt_sec_krb5i, "krb5i" पूर्ण,
	अणु Opt_sec_krb5p, "krb5p" पूर्ण,
	अणु Opt_sec_ntlmsspi, "ntlmsspi" पूर्ण,
	अणु Opt_sec_ntlmssp, "ntlmssp" पूर्ण,
	अणु Opt_ntlm, "ntlm" पूर्ण,
	अणु Opt_sec_ntlmi, "ntlmi" पूर्ण,
	अणु Opt_sec_ntlmv2, "nontlm" पूर्ण,
	अणु Opt_sec_ntlmv2, "ntlmv2" पूर्ण,
	अणु Opt_sec_ntlmv2i, "ntlmv2i" पूर्ण,
	अणु Opt_sec_lanman, "lanman" पूर्ण,
	अणु Opt_sec_none, "none" पूर्ण,

	अणु Opt_sec_err, शून्य पूर्ण
पूर्ण;

स्थिर काष्ठा fs_parameter_spec smb3_fs_parameters[] = अणु
	/* Mount options that take no arguments */
	fsparam_flag_no("user_xattr", Opt_user_xattr),
	fsparam_flag_no("forceuid", Opt_क्रमceuid),
	fsparam_flag_no("multichannel", Opt_multichannel),
	fsparam_flag_no("forcegid", Opt_क्रमcegid),
	fsparam_flag("noblocksend", Opt_noblocksend),
	fsparam_flag("noautotune", Opt_noस्वतःtune),
	fsparam_flag("nolease", Opt_nolease),
	fsparam_flag_no("hard", Opt_hard),
	fsparam_flag_no("soft", Opt_soft),
	fsparam_flag_no("perm", Opt_perm),
	fsparam_flag("nodelete", Opt_nodelete),
	fsparam_flag_no("mapposix", Opt_mapposix),
	fsparam_flag("mapchars", Opt_mapअक्षरs),
	fsparam_flag("nomapchars", Opt_nomapअक्षरs),
	fsparam_flag_no("sfu", Opt_sfu),
	fsparam_flag("nodfs", Opt_nodfs),
	fsparam_flag_no("posixpaths", Opt_posixpaths),
	fsparam_flag_no("unix", Opt_unix),
	fsparam_flag_no("linux", Opt_unix),
	fsparam_flag_no("posix", Opt_unix),
	fsparam_flag("nocase", Opt_noहाल),
	fsparam_flag("ignorecase", Opt_noहाल),
	fsparam_flag_no("brl", Opt_brl),
	fsparam_flag_no("handlecache", Opt_handlecache),
	fsparam_flag("forcemandatorylock", Opt_क्रमcemandatorylock),
	fsparam_flag("forcemand", Opt_क्रमcemandatorylock),
	fsparam_flag("setuidfromacl", Opt_setuidfromacl),
	fsparam_flag("idsfromsid", Opt_setuidfromacl),
	fsparam_flag_no("setuids", Opt_setuids),
	fsparam_flag_no("dynperm", Opt_dynperm),
	fsparam_flag_no("intr", Opt_पूर्णांकr),
	fsparam_flag_no("strictsync", Opt_strictsync),
	fsparam_flag_no("serverino", Opt_serverino),
	fsparam_flag("rwpidforward", Opt_rwpidक्रमward),
	fsparam_flag("cifsacl", Opt_cअगरsacl),
	fsparam_flag_no("acl", Opt_acl),
	fsparam_flag("locallease", Opt_locallease),
	fsparam_flag("sign", Opt_sign),
	fsparam_flag("ignore_signature", Opt_ignore_signature),
	fsparam_flag("signloosely", Opt_ignore_signature),
	fsparam_flag("seal", Opt_seal),
	fsparam_flag("noac", Opt_noac),
	fsparam_flag("fsc", Opt_fsc),
	fsparam_flag("mfsymlinks", Opt_mfsymlinks),
	fsparam_flag("multiuser", Opt_multiuser),
	fsparam_flag("sloppy", Opt_sloppy),
	fsparam_flag("nosharesock", Opt_nosharesock),
	fsparam_flag_no("persistenthandles", Opt_persistent),
	fsparam_flag_no("resilienthandles", Opt_resilient),
	fsparam_flag("domainauto", Opt_करोमुख्यस्वतः),
	fsparam_flag("rdma", Opt_rdma),
	fsparam_flag("modesid", Opt_modesid),
	fsparam_flag("modefromsid", Opt_modesid),
	fsparam_flag("rootfs", Opt_rootfs),
	fsparam_flag("compress", Opt_compress),
	fsparam_flag("witness", Opt_witness),

	/* Mount options which take numeric value */
	fsparam_u32("backupuid", Opt_backupuid),
	fsparam_u32("backupgid", Opt_backupgid),
	fsparam_u32("uid", Opt_uid),
	fsparam_u32("cruid", Opt_cruid),
	fsparam_u32("gid", Opt_gid),
	fsparam_u32("file_mode", Opt_file_mode),
	fsparam_u32("dirmode", Opt_dirmode),
	fsparam_u32("dir_mode", Opt_dirmode),
	fsparam_u32("port", Opt_port),
	fsparam_u32("min_enc_offload", Opt_min_enc_offload),
	fsparam_u32("esize", Opt_min_enc_offload),
	fsparam_u32("bsize", Opt_blocksize),
	fsparam_u32("rasize", Opt_rasize),
	fsparam_u32("rsize", Opt_rsize),
	fsparam_u32("wsize", Opt_wsize),
	fsparam_u32("actimeo", Opt_aस_समयo),
	fsparam_u32("acdirmax", Opt_acdirmax),
	fsparam_u32("acregmax", Opt_acregmax),
	fsparam_u32("echo_interval", Opt_echo_पूर्णांकerval),
	fsparam_u32("max_credits", Opt_max_credits),
	fsparam_u32("handletimeout", Opt_handleसमयout),
	fsparam_u32("snapshot", Opt_snapshot),
	fsparam_u32("max_channels", Opt_max_channels),

	/* Mount options which take string value */
	fsparam_string("source", Opt_source),
	fsparam_string("user", Opt_user),
	fsparam_string("username", Opt_user),
	fsparam_string("pass", Opt_pass),
	fsparam_string("password", Opt_pass),
	fsparam_string("ip", Opt_ip),
	fsparam_string("addr", Opt_ip),
	fsparam_string("domain", Opt_करोमुख्य),
	fsparam_string("dom", Opt_करोमुख्य),
	fsparam_string("srcaddr", Opt_srcaddr),
	fsparam_string("iocharset", Opt_ioअक्षरset),
	fsparam_string("netbiosname", Opt_netbiosname),
	fsparam_string("servern", Opt_servern),
	fsparam_string("ver", Opt_ver),
	fsparam_string("vers", Opt_vers),
	fsparam_string("sec", Opt_sec),
	fsparam_string("cache", Opt_cache),

	/* Arguments that should be ignored */
	fsparam_flag("guest", Opt_ignore),
	fsparam_flag("noatime", Opt_ignore),
	fsparam_flag("relatime", Opt_ignore),
	fsparam_flag("_netdev", Opt_ignore),
	fsparam_flag_no("suid", Opt_ignore),
	fsparam_flag_no("exec", Opt_ignore),
	fsparam_flag_no("dev", Opt_ignore),
	fsparam_flag_no("mand", Opt_ignore),
	fsparam_flag_no("auto", Opt_ignore),
	fsparam_string("cred", Opt_ignore),
	fsparam_string("credentials", Opt_ignore),
	/*
	 * UNC and prefixpath is now extracted from Opt_source
	 * in the new mount API so we can just ignore them going क्रमward.
	 */
	fsparam_string("unc", Opt_ignore),
	fsparam_string("prefixpath", Opt_ignore),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
cअगरs_parse_security_flavors(काष्ठा fs_context *fc, अक्षर *value, काष्ठा smb3_fs_context *ctx)
अणु

	substring_t args[MAX_OPT_ARGS];

	/*
	 * With mount options, the last one should win. Reset any existing
	 * settings back to शेष.
	 */
	ctx->sectype = Unspecअगरied;
	ctx->sign = false;

	चयन (match_token(value, cअगरs_secflavor_tokens, args)) अणु
	हाल Opt_sec_krb5p:
		cअगरs_errorf(fc, "sec=krb5p is not supported!\n");
		वापस 1;
	हाल Opt_sec_krb5i:
		ctx->sign = true;
		fallthrough;
	हाल Opt_sec_krb5:
		ctx->sectype = Kerberos;
		अवरोध;
	हाल Opt_sec_ntlmsspi:
		ctx->sign = true;
		fallthrough;
	हाल Opt_sec_ntlmssp:
		ctx->sectype = RawNTLMSSP;
		अवरोध;
	हाल Opt_sec_ntlmi:
		ctx->sign = true;
		fallthrough;
	हाल Opt_ntlm:
		ctx->sectype = NTLM;
		अवरोध;
	हाल Opt_sec_ntlmv2i:
		ctx->sign = true;
		fallthrough;
	हाल Opt_sec_ntlmv2:
		ctx->sectype = NTLMv2;
		अवरोध;
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
	हाल Opt_sec_lanman:
		ctx->sectype = LANMAN;
		अवरोध;
#पूर्ण_अगर
	हाल Opt_sec_none:
		ctx->nullauth = 1;
		अवरोध;
	शेष:
		cअगरs_errorf(fc, "bad security option: %s\n", value);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर match_table_t cअगरs_cacheflavor_tokens = अणु
	अणु Opt_cache_loose, "loose" पूर्ण,
	अणु Opt_cache_strict, "strict" पूर्ण,
	अणु Opt_cache_none, "none" पूर्ण,
	अणु Opt_cache_ro, "ro" पूर्ण,
	अणु Opt_cache_rw, "singleclient" पूर्ण,
	अणु Opt_cache_err, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक
cअगरs_parse_cache_flavor(काष्ठा fs_context *fc, अक्षर *value, काष्ठा smb3_fs_context *ctx)
अणु
	substring_t args[MAX_OPT_ARGS];

	चयन (match_token(value, cअगरs_cacheflavor_tokens, args)) अणु
	हाल Opt_cache_loose:
		ctx->direct_io = false;
		ctx->strict_io = false;
		ctx->cache_ro = false;
		ctx->cache_rw = false;
		अवरोध;
	हाल Opt_cache_strict:
		ctx->direct_io = false;
		ctx->strict_io = true;
		ctx->cache_ro = false;
		ctx->cache_rw = false;
		अवरोध;
	हाल Opt_cache_none:
		ctx->direct_io = true;
		ctx->strict_io = false;
		ctx->cache_ro = false;
		ctx->cache_rw = false;
		अवरोध;
	हाल Opt_cache_ro:
		ctx->direct_io = false;
		ctx->strict_io = false;
		ctx->cache_ro = true;
		ctx->cache_rw = false;
		अवरोध;
	हाल Opt_cache_rw:
		ctx->direct_io = false;
		ctx->strict_io = false;
		ctx->cache_ro = false;
		ctx->cache_rw = true;
		अवरोध;
	शेष:
		cअगरs_errorf(fc, "bad cache= option: %s\n", value);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा DUP_CTX_STR(field)						\
करो अणु									\
	अगर (ctx->field) अणु						\
		new_ctx->field = kstrdup(ctx->field, GFP_ATOMIC);	\
		अगर (new_ctx->field == शून्य) अणु				\
			smb3_cleanup_fs_context_contents(new_ctx);	\
			वापस -ENOMEM;					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

पूर्णांक
smb3_fs_context_dup(काष्ठा smb3_fs_context *new_ctx, काष्ठा smb3_fs_context *ctx)
अणु
	स_नकल(new_ctx, ctx, माप(*ctx));
	new_ctx->prepath = शून्य;
	new_ctx->mount_options = शून्य;
	new_ctx->nodename = शून्य;
	new_ctx->username = शून्य;
	new_ctx->password = शून्य;
	new_ctx->करोमुख्यname = शून्य;
	new_ctx->UNC = शून्य;
	new_ctx->source = शून्य;
	new_ctx->ioअक्षरset = शून्य;

	/*
	 * Make sure to stay in sync with smb3_cleanup_fs_context_contents()
	 */
	DUP_CTX_STR(prepath);
	DUP_CTX_STR(mount_options);
	DUP_CTX_STR(username);
	DUP_CTX_STR(password);
	DUP_CTX_STR(UNC);
	DUP_CTX_STR(source);
	DUP_CTX_STR(करोमुख्यname);
	DUP_CTX_STR(nodename);
	DUP_CTX_STR(ioअक्षरset);

	वापस 0;
पूर्ण

अटल पूर्णांक
cअगरs_parse_smb_version(काष्ठा fs_context *fc, अक्षर *value, काष्ठा smb3_fs_context *ctx, bool is_smb3)
अणु
	substring_t args[MAX_OPT_ARGS];

	चयन (match_token(value, cअगरs_smb_version_tokens, args)) अणु
#अगर_घोषित CONFIG_CIFS_ALLOW_INSECURE_LEGACY
	हाल Smb_1:
		अगर (disable_legacy_dialects) अणु
			cअगरs_errorf(fc, "mount with legacy dialect disabled\n");
			वापस 1;
		पूर्ण
		अगर (is_smb3) अणु
			cअगरs_errorf(fc, "vers=1.0 (cifs) not permitted when mounting with smb3\n");
			वापस 1;
		पूर्ण
		cअगरs_errorf(fc, "Use of the less secure dialect vers=1.0 is not recommended unless required for access to very old servers\n");
		ctx->ops = &smb1_operations;
		ctx->vals = &smb1_values;
		अवरोध;
	हाल Smb_20:
		अगर (disable_legacy_dialects) अणु
			cअगरs_errorf(fc, "mount with legacy dialect disabled\n");
			वापस 1;
		पूर्ण
		अगर (is_smb3) अणु
			cअगरs_errorf(fc, "vers=2.0 not permitted when mounting with smb3\n");
			वापस 1;
		पूर्ण
		ctx->ops = &smb20_operations;
		ctx->vals = &smb20_values;
		अवरोध;
#अन्यथा
	हाल Smb_1:
		cअगरs_errorf(fc, "vers=1.0 (cifs) mount not permitted when legacy dialects disabled\n");
		वापस 1;
	हाल Smb_20:
		cअगरs_errorf(fc, "vers=2.0 mount not permitted when legacy dialects disabled\n");
		वापस 1;
#पूर्ण_अगर /* CIFS_ALLOW_INSECURE_LEGACY */
	हाल Smb_21:
		ctx->ops = &smb21_operations;
		ctx->vals = &smb21_values;
		अवरोध;
	हाल Smb_30:
		ctx->ops = &smb30_operations;
		ctx->vals = &smb30_values;
		अवरोध;
	हाल Smb_302:
		ctx->ops = &smb30_operations; /* currently identical with 3.0 */
		ctx->vals = &smb302_values;
		अवरोध;
	हाल Smb_311:
		ctx->ops = &smb311_operations;
		ctx->vals = &smb311_values;
		अवरोध;
	हाल Smb_3any:
		ctx->ops = &smb30_operations; /* currently identical with 3.0 */
		ctx->vals = &smb3any_values;
		अवरोध;
	हाल Smb_शेष:
		ctx->ops = &smb30_operations;
		ctx->vals = &smbशेष_values;
		अवरोध;
	शेष:
		cअगरs_errorf(fc, "Unknown vers= option specified: %s\n", value);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक smb3_parse_opt(स्थिर अक्षर *options, स्थिर अक्षर *key, अक्षर **val)
अणु
	पूर्णांक rc = -ENOENT;
	अक्षर *opts, *orig, *p;

	orig = opts = kstrdup(options, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	जबतक ((p = strsep(&opts, ","))) अणु
		अक्षर *nval;

		अगर (!*p)
			जारी;
		अगर (strnहालcmp(p, key, म_माप(key)))
			जारी;
		nval = म_अक्षर(p, '=');
		अगर (nval) अणु
			अगर (nval == p)
				जारी;
			*nval++ = 0;
			*val = kstrdup(nval, GFP_KERNEL);
			rc = !*val ? -ENOMEM : 0;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(orig);
	वापस rc;
पूर्ण

/*
 * Parse a devname पूर्णांकo substrings and populate the ctx->UNC and ctx->prepath
 * fields with the result. Returns 0 on success and an error otherwise
 * (e.g. ENOMEM or EINVAL)
 */
पूर्णांक
smb3_parse_devname(स्थिर अक्षर *devname, काष्ठा smb3_fs_context *ctx)
अणु
	अक्षर *pos;
	स्थिर अक्षर *delims = "/\\";
	माप_प्रकार len;

	अगर (unlikely(!devname || !*devname)) अणु
		cअगरs_dbg(VFS, "Device name not specified\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure we have a valid UNC द्विगुन delimiter prefix */
	len = म_अखोज(devname, delims);
	अगर (len != 2)
		वापस -EINVAL;

	/* find delimiter between host and shaनाम */
	pos = strpbrk(devname + 2, delims);
	अगर (!pos)
		वापस -EINVAL;

	/* skip past delimiter */
	++pos;

	/* now go until next delimiter or end of string */
	len = म_खोज(pos, delims);

	/* move "pos" up to delimiter or शून्य */
	pos += len;
	kमुक्त(ctx->UNC);
	ctx->UNC = kstrndup(devname, pos - devname, GFP_KERNEL);
	अगर (!ctx->UNC)
		वापस -ENOMEM;

	convert_delimiter(ctx->UNC, '\\');

	/* skip any delimiter */
	अगर (*pos == '/' || *pos == '\\')
		pos++;

	kमुक्त(ctx->prepath);
	ctx->prepath = शून्य;

	/* If pos is शून्य then no prepath */
	अगर (!*pos)
		वापस 0;

	ctx->prepath = kstrdup(pos, GFP_KERNEL);
	अगर (!ctx->prepath)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम smb3_fs_context_मुक्त(काष्ठा fs_context *fc);
अटल पूर्णांक smb3_fs_context_parse_param(काष्ठा fs_context *fc,
				       काष्ठा fs_parameter *param);
अटल पूर्णांक smb3_fs_context_parse_monolithic(काष्ठा fs_context *fc,
					    व्योम *data);
अटल पूर्णांक smb3_get_tree(काष्ठा fs_context *fc);
अटल पूर्णांक smb3_reconfigure(काष्ठा fs_context *fc);

अटल स्थिर काष्ठा fs_context_operations smb3_fs_context_ops = अणु
	.मुक्त			= smb3_fs_context_मुक्त,
	.parse_param		= smb3_fs_context_parse_param,
	.parse_monolithic	= smb3_fs_context_parse_monolithic,
	.get_tree		= smb3_get_tree,
	.reconfigure		= smb3_reconfigure,
पूर्ण;

/*
 * Parse a monolithic block of data from sys_mount().
 * smb3_fs_context_parse_monolithic - Parse key[=val][,key[=val]]* mount data
 * @ctx: The superblock configuration to fill in.
 * @data: The data to parse
 *
 * Parse a blob of data that's in key[=val][,key[=val]]* क्रमm.  This can be
 * called from the ->monolithic_mount_data() fs_context operation.
 *
 * Returns 0 on success or the error वापसed by the ->parse_option() fs_context
 * operation on failure.
 */
अटल पूर्णांक smb3_fs_context_parse_monolithic(काष्ठा fs_context *fc,
					   व्योम *data)
अणु
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);
	अक्षर *options = data, *key;
	पूर्णांक ret = 0;

	अगर (!options)
		वापस 0;

	ctx->mount_options = kstrdup(data, GFP_KERNEL);
	अगर (ctx->mount_options == शून्य)
		वापस -ENOMEM;

	ret = security_sb_eat_lsm_opts(options, &fc->security);
	अगर (ret)
		वापस ret;

	/* BB Need to add support क्रम sep= here TBD */
	जबतक ((key = strsep(&options, ",")) != शून्य) अणु
		माप_प्रकार len;
		अक्षर *value;

		अगर (*key == 0)
			अवरोध;

		/* Check अगर following अक्षरacter is the deliminator If yes,
		 * we have encountered a द्विगुन deliminator reset the शून्य
		 * अक्षरacter to the deliminator
		 */
		जबतक (options && options[0] == ',') अणु
			len = म_माप(key);
			म_नकल(key + len, options);
			options = म_अक्षर(options, ',');
			अगर (options)
				*options++ = 0;
		पूर्ण


		len = 0;
		value = म_अक्षर(key, '=');
		अगर (value) अणु
			अगर (value == key)
				जारी;
			*value++ = 0;
			len = म_माप(value);
		पूर्ण

		ret = vfs_parse_fs_string(fc, key, value, len);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Validate the preparsed inक्रमmation in the config.
 */
अटल पूर्णांक smb3_fs_context_validate(काष्ठा fs_context *fc)
अणु
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);

	अगर (ctx->rdma && ctx->vals->protocol_id < SMB30_PROT_ID) अणु
		cअगरs_errorf(fc, "SMB Direct requires Version >=3.0\n");
		वापस -EOPNOTSUPP;
	पूर्ण

#अगर_अघोषित CONFIG_KEYS
	/* Muliuser mounts require CONFIG_KEYS support */
	अगर (ctx->multiuser) अणु
		cअगरs_errorf(fc, "Multiuser mounts require kernels with CONFIG_KEYS enabled\n");
		वापस -1;
	पूर्ण
#पूर्ण_अगर

	अगर (ctx->got_version == false)
		pr_warn_once("No dialect specified on mount. Default has changed to a more secure dialect, SMB2.1 or later (e.g. SMB3.1.1), from CIFS (SMB1). To use the less secure SMB1 dialect to access old servers which do not support SMB3.1.1 (or even SMB3 or SMB2.1) specify vers=1.0 on mount.\n");


	अगर (!ctx->UNC) अणु
		cअगरs_errorf(fc, "CIFS mount error: No usable UNC path provided in device string!\n");
		वापस -1;
	पूर्ण

	/* make sure UNC has a share name */
	अगर (म_माप(ctx->UNC) < 3 || !म_अक्षर(ctx->UNC + 3, '\\')) अणु
		cअगरs_errorf(fc, "Malformed UNC. Unable to find share name.\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!ctx->got_ip) अणु
		पूर्णांक len;
		स्थिर अक्षर *slash;

		/* No ip= option specअगरied? Try to get it from UNC */
		/* Use the address part of the UNC. */
		slash = म_अक्षर(&ctx->UNC[2], '\\');
		len = slash - &ctx->UNC[2];
		अगर (!cअगरs_convert_address((काष्ठा sockaddr *)&ctx->dstaddr,
					  &ctx->UNC[2], len)) अणु
			pr_err("Unable to determine destination address\n");
			वापस -EHOSTUNREACH;
		पूर्ण
	पूर्ण

	/* set the port that we got earlier */
	cअगरs_set_port((काष्ठा sockaddr *)&ctx->dstaddr, ctx->port);

	अगर (ctx->override_uid && !ctx->uid_specअगरied) अणु
		ctx->override_uid = 0;
		pr_notice("ignoring forceuid mount option specified with no uid= option\n");
	पूर्ण

	अगर (ctx->override_gid && !ctx->gid_specअगरied) अणु
		ctx->override_gid = 0;
		pr_notice("ignoring forcegid mount option specified with no gid= option\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb3_get_tree_common(काष्ठा fs_context *fc)
अणु
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);
	काष्ठा dentry *root;
	पूर्णांक rc = 0;

	root = cअगरs_smb3_करो_mount(fc->fs_type, 0, ctx);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	fc->root = root;

	वापस rc;
पूर्ण

/*
 * Create an SMB3 superblock from the parameters passed.
 */
अटल पूर्णांक smb3_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक err = smb3_fs_context_validate(fc);

	अगर (err)
		वापस err;
	वापस smb3_get_tree_common(fc);
पूर्ण

अटल व्योम smb3_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);

	smb3_cleanup_fs_context(ctx);
पूर्ण

/*
 * Compare the old and new proposed context during reconfigure
 * and check अगर the changes are compatible.
 */
अटल पूर्णांक smb3_verअगरy_reconfigure_ctx(काष्ठा fs_context *fc,
				       काष्ठा smb3_fs_context *new_ctx,
				       काष्ठा smb3_fs_context *old_ctx)
अणु
	अगर (new_ctx->posix_paths != old_ctx->posix_paths) अणु
		cअगरs_errorf(fc, "can not change posixpaths during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->sectype != old_ctx->sectype) अणु
		cअगरs_errorf(fc, "can not change sec during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->multiuser != old_ctx->multiuser) अणु
		cअगरs_errorf(fc, "can not change multiuser during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->UNC &&
	    (!old_ctx->UNC || म_भेद(new_ctx->UNC, old_ctx->UNC))) अणु
		cअगरs_errorf(fc, "can not change UNC during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->username &&
	    (!old_ctx->username || म_भेद(new_ctx->username, old_ctx->username))) अणु
		cअगरs_errorf(fc, "can not change username during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->password &&
	    (!old_ctx->password || म_भेद(new_ctx->password, old_ctx->password))) अणु
		cअगरs_errorf(fc, "can not change password during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->करोमुख्यname &&
	    (!old_ctx->करोमुख्यname || म_भेद(new_ctx->करोमुख्यname, old_ctx->करोमुख्यname))) अणु
		cअगरs_errorf(fc, "can not change domainname during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->nodename &&
	    (!old_ctx->nodename || म_भेद(new_ctx->nodename, old_ctx->nodename))) अणु
		cअगरs_errorf(fc, "can not change nodename during remount\n");
		वापस -EINVAL;
	पूर्ण
	अगर (new_ctx->ioअक्षरset &&
	    (!old_ctx->ioअक्षरset || म_भेद(new_ctx->ioअक्षरset, old_ctx->ioअक्षरset))) अणु
		cअगरs_errorf(fc, "can not change iocharset during remount\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा STEAL_STRING(cअगरs_sb, ctx, field)				\
करो अणु									\
	kमुक्त(ctx->field);						\
	ctx->field = cअगरs_sb->ctx->field;				\
	cअगरs_sb->ctx->field = शून्य;					\
पूर्ण जबतक (0)

अटल पूर्णांक smb3_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);
	काष्ठा dentry *root = fc->root;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(root->d_sb);
	पूर्णांक rc;

	rc = smb3_verअगरy_reconfigure_ctx(fc, ctx, cअगरs_sb->ctx);
	अगर (rc)
		वापस rc;

	/*
	 * We can not change UNC/username/password/करोमुख्यname/nodename/ioअक्षरset
	 * during reconnect so ignore what we have in the new context and
	 * just use what we alपढ़ोy have in cअगरs_sb->ctx.
	 */
	STEAL_STRING(cअगरs_sb, ctx, UNC);
	STEAL_STRING(cअगरs_sb, ctx, source);
	STEAL_STRING(cअगरs_sb, ctx, username);
	STEAL_STRING(cअगरs_sb, ctx, password);
	STEAL_STRING(cअगरs_sb, ctx, करोमुख्यname);
	STEAL_STRING(cअगरs_sb, ctx, nodename);
	STEAL_STRING(cअगरs_sb, ctx, ioअक्षरset);

	/* अगर rsize or wsize not passed in on remount, use previous values */
	अगर (ctx->rsize == 0)
		ctx->rsize = cअगरs_sb->ctx->rsize;
	अगर (ctx->wsize == 0)
		ctx->wsize = cअगरs_sb->ctx->wsize;


	smb3_cleanup_fs_context_contents(cअगरs_sb->ctx);
	rc = smb3_fs_context_dup(cअगरs_sb->ctx, ctx);
	smb3_update_mnt_flags(cअगरs_sb);

	वापस rc;
पूर्ण

अटल पूर्णांक smb3_fs_context_parse_param(काष्ठा fs_context *fc,
				      काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा smb3_fs_context *ctx = smb3_fc2context(fc);
	पूर्णांक i, opt;
	bool is_smb3 = !म_भेद(fc->fs_type->name, "smb3");
	bool skip_parsing = false;

	cअगरs_dbg(FYI, "CIFS: parsing cifs mount option '%s'\n", param->key);

	/*
	 * fs_parse can not handle string options with an empty value so
	 * we will need special handling of them.
	 */
	अगर (param->type == fs_value_is_string && param->string[0] == 0) अणु
		अगर (!म_भेद("pass", param->key) || !म_भेद("password", param->key)) अणु
			skip_parsing = true;
			opt = Opt_pass;
		पूर्ण अन्यथा अगर (!म_भेद("user", param->key) || !म_भेद("username", param->key)) अणु
			skip_parsing = true;
			opt = Opt_user;
		पूर्ण
	पूर्ण

	अगर (!skip_parsing) अणु
		opt = fs_parse(fc, smb3_fs_parameters, param, &result);
		अगर (opt < 0)
			वापस ctx->sloppy ? 1 : opt;
	पूर्ण

	चयन (opt) अणु
	हाल Opt_compress:
		ctx->compression = UNKNOWN_TYPE;
		cअगरs_dbg(VFS,
			"SMB3 compression support is experimental\n");
		अवरोध;
	हाल Opt_nodfs:
		ctx->nodfs = 1;
		अवरोध;
	हाल Opt_hard:
		अगर (result.negated)
			ctx->retry = 0;
		अन्यथा
			ctx->retry = 1;
		अवरोध;
	हाल Opt_soft:
		अगर (result.negated)
			ctx->retry = 1;
		अन्यथा
			ctx->retry = 0;
		अवरोध;
	हाल Opt_mapposix:
		अगर (result.negated)
			ctx->remap = false;
		अन्यथा अणु
			ctx->remap = true;
			ctx->sfu_remap = false; /* disable SFU mapping */
		पूर्ण
		अवरोध;
	हाल Opt_user_xattr:
		अगर (result.negated)
			ctx->no_xattr = 1;
		अन्यथा
			ctx->no_xattr = 0;
		अवरोध;
	हाल Opt_क्रमceuid:
		अगर (result.negated)
			ctx->override_uid = 0;
		अन्यथा
			ctx->override_uid = 1;
		अवरोध;
	हाल Opt_क्रमcegid:
		अगर (result.negated)
			ctx->override_gid = 0;
		अन्यथा
			ctx->override_gid = 1;
		अवरोध;
	हाल Opt_perm:
		अगर (result.negated)
			ctx->noperm = 1;
		अन्यथा
			ctx->noperm = 0;
		अवरोध;
	हाल Opt_dynperm:
		अगर (result.negated)
			ctx->dynperm = 0;
		अन्यथा
			ctx->dynperm = 1;
		अवरोध;
	हाल Opt_sfu:
		अगर (result.negated)
			ctx->sfu_emul = 0;
		अन्यथा
			ctx->sfu_emul = 1;
		अवरोध;
	हाल Opt_noblocksend:
		ctx->noblocksnd = 1;
		अवरोध;
	हाल Opt_noस्वतःtune:
		ctx->noस्वतःtune = 1;
		अवरोध;
	हाल Opt_nolease:
		ctx->no_lease = 1;
		अवरोध;
	हाल Opt_nodelete:
		ctx->nodelete = 1;
		अवरोध;
	हाल Opt_multichannel:
		अगर (result.negated) अणु
			ctx->multichannel = false;
			ctx->max_channels = 1;
		पूर्ण अन्यथा अणु
			ctx->multichannel = true;
			/* अगर number of channels not specअगरied, शेष to 2 */
			अगर (ctx->max_channels < 2)
				ctx->max_channels = 2;
		पूर्ण
		अवरोध;
	हाल Opt_uid:
		ctx->linux_uid.val = result.uपूर्णांक_32;
		ctx->uid_specअगरied = true;
		अवरोध;
	हाल Opt_cruid:
		ctx->cred_uid.val = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_backupgid:
		ctx->backupgid.val = result.uपूर्णांक_32;
		ctx->backupgid_specअगरied = true;
		अवरोध;
	हाल Opt_gid:
		ctx->linux_gid.val = result.uपूर्णांक_32;
		ctx->gid_specअगरied = true;
		अवरोध;
	हाल Opt_port:
		ctx->port = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_file_mode:
		ctx->file_mode = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_dirmode:
		ctx->dir_mode = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_min_enc_offload:
		ctx->min_offload = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_blocksize:
		/*
		 * inode blocksize realistically should never need to be
		 * less than 16K or greater than 16M and शेष is 1MB.
		 * Note that small inode block sizes (e.g. 64K) can lead
		 * to very poor perक्रमmance of common tools like cp and scp
		 */
		अगर ((result.uपूर्णांक_32 < CIFS_MAX_MSGSIZE) ||
		   (result.uपूर्णांक_32 > (4 * SMB3_DEFAULT_IOSIZE))) अणु
			cअगरs_errorf(fc, "%s: Invalid blocksize\n",
				__func__);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->bsize = result.uपूर्णांक_32;
		ctx->got_bsize = true;
		अवरोध;
	हाल Opt_rasize:
		/*
		 * पढ़ोahead size realistically should never need to be
		 * less than 1M (CIFS_DEFAULT_IOSIZE) or greater than 32M
		 * (perhaps an exception should be considered in the
		 * क्रम the हाल of a large number of channels
		 * when multichannel is negotiated) since that would lead
		 * to plenty of parallel I/O in flight to the server.
		 * Note that smaller पढ़ो ahead sizes would
		 * hurt perक्रमmance of common tools like cp and scp
		 * which often trigger sequential i/o with पढ़ो ahead
		 */
		अगर ((result.uपूर्णांक_32 > (8 * SMB3_DEFAULT_IOSIZE)) ||
		    (result.uपूर्णांक_32 < CIFS_DEFAULT_IOSIZE)) अणु
			cअगरs_errorf(fc, "%s: Invalid rasize %d vs. %d\n",
				__func__, result.uपूर्णांक_32, SMB3_DEFAULT_IOSIZE);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->rasize = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_rsize:
		ctx->rsize = result.uपूर्णांक_32;
		ctx->got_rsize = true;
		अवरोध;
	हाल Opt_wsize:
		ctx->wsize = result.uपूर्णांक_32;
		ctx->got_wsize = true;
		अवरोध;
	हाल Opt_acregmax:
		ctx->acregmax = HZ * result.uपूर्णांक_32;
		अगर (ctx->acregmax > CIFS_MAX_ACTIMEO) अणु
			cअगरs_errorf(fc, "acregmax too large\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_acdirmax:
		ctx->acdirmax = HZ * result.uपूर्णांक_32;
		अगर (ctx->acdirmax > CIFS_MAX_ACTIMEO) अणु
			cअगरs_errorf(fc, "acdirmax too large\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_aस_समयo:
		अगर (HZ * result.uपूर्णांक_32 > CIFS_MAX_ACTIMEO) अणु
			cअगरs_errorf(fc, "timeout too large\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अगर ((ctx->acdirmax != CIFS_DEF_ACTIMEO) ||
		    (ctx->acregmax != CIFS_DEF_ACTIMEO)) अणु
			cअगरs_errorf(fc, "actimeo ignored since acregmax or acdirmax specified\n");
			अवरोध;
		पूर्ण
		ctx->acdirmax = ctx->acregmax = HZ * result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_echo_पूर्णांकerval:
		ctx->echo_पूर्णांकerval = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_snapshot:
		ctx->snapshot_समय = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_max_credits:
		अगर (result.uपूर्णांक_32 < 20 || result.uपूर्णांक_32 > 60000) अणु
			cअगरs_errorf(fc, "%s: Invalid max_credits value\n",
				 __func__);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->max_credits = result.uपूर्णांक_32;
		अवरोध;
	हाल Opt_max_channels:
		अगर (result.uपूर्णांक_32 < 1 || result.uपूर्णांक_32 > CIFS_MAX_CHANNELS) अणु
			cअगरs_errorf(fc, "%s: Invalid max_channels value, needs to be 1-%d\n",
				 __func__, CIFS_MAX_CHANNELS);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->max_channels = result.uपूर्णांक_32;
		/* If more than one channel requested ... they want multichan */
		अगर (result.uपूर्णांक_32 > 1)
			ctx->multichannel = true;
		अवरोध;
	हाल Opt_handleसमयout:
		ctx->handle_समयout = result.uपूर्णांक_32;
		अगर (ctx->handle_समयout > SMB3_MAX_HANDLE_TIMEOUT) अणु
			cअगरs_errorf(fc, "Invalid handle cache timeout, longer than 16 minutes\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_source:
		kमुक्त(ctx->UNC);
		ctx->UNC = शून्य;
		चयन (smb3_parse_devname(param->string, ctx)) अणु
		हाल 0:
			अवरोध;
		हाल -ENOMEM:
			cअगरs_errorf(fc, "Unable to allocate memory for devname\n");
			जाओ cअगरs_parse_mount_err;
		हाल -EINVAL:
			cअगरs_errorf(fc, "Malformed UNC in devname\n");
			जाओ cअगरs_parse_mount_err;
		शेष:
			cअगरs_errorf(fc, "Unknown error parsing devname\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->source = kstrdup(param->string, GFP_KERNEL);
		अगर (ctx->source == शून्य) अणु
			cअगरs_errorf(fc, "OOM when copying UNC string\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		fc->source = kstrdup(param->string, GFP_KERNEL);
		अगर (fc->source == शून्य) अणु
			cअगरs_errorf(fc, "OOM when copying UNC string\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_user:
		kमुक्त(ctx->username);
		ctx->username = शून्य;
		अगर (म_माप(param->string) == 0) अणु
			/* null user, ie. anonymous authentication */
			ctx->nullauth = 1;
			अवरोध;
		पूर्ण

		अगर (strnlen(param->string, CIFS_MAX_USERNAME_LEN) >
		    CIFS_MAX_USERNAME_LEN) अणु
			pr_warn("username too long\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->username = kstrdup(param->string, GFP_KERNEL);
		अगर (ctx->username == शून्य) अणु
			cअगरs_errorf(fc, "OOM when copying username string\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_pass:
		kमुक्त(ctx->password);
		ctx->password = शून्य;
		अगर (म_माप(param->string) == 0)
			अवरोध;

		ctx->password = kstrdup(param->string, GFP_KERNEL);
		अगर (ctx->password == शून्य) अणु
			cअगरs_errorf(fc, "OOM when copying password string\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_ip:
		अगर (म_माप(param->string) == 0) अणु
			ctx->got_ip = false;
			अवरोध;
		पूर्ण
		अगर (!cअगरs_convert_address((काष्ठा sockaddr *)&ctx->dstaddr,
					  param->string,
					  म_माप(param->string))) अणु
			pr_err("bad ip= option (%s)\n", param->string);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		ctx->got_ip = true;
		अवरोध;
	हाल Opt_करोमुख्य:
		अगर (strnlen(param->string, CIFS_MAX_DOMAINNAME_LEN)
				== CIFS_MAX_DOMAINNAME_LEN) अणु
			pr_warn("domain name too long\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण

		kमुक्त(ctx->करोमुख्यname);
		ctx->करोमुख्यname = kstrdup(param->string, GFP_KERNEL);
		अगर (ctx->करोमुख्यname == शून्य) अणु
			cअगरs_errorf(fc, "OOM when copying domainname string\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		cअगरs_dbg(FYI, "Domain name set\n");
		अवरोध;
	हाल Opt_srcaddr:
		अगर (!cअगरs_convert_address(
				(काष्ठा sockaddr *)&ctx->srcaddr,
				param->string, म_माप(param->string))) अणु
			pr_warn("Could not parse srcaddr: %s\n",
				param->string);
			जाओ cअगरs_parse_mount_err;
		पूर्ण
		अवरोध;
	हाल Opt_ioअक्षरset:
		अगर (strnlen(param->string, 1024) >= 65) अणु
			pr_warn("iocharset name too long\n");
			जाओ cअगरs_parse_mount_err;
		पूर्ण

		अगर (strnहालcmp(param->string, "default", 7) != 0) अणु
			kमुक्त(ctx->ioअक्षरset);
			ctx->ioअक्षरset = kstrdup(param->string, GFP_KERNEL);
			अगर (ctx->ioअक्षरset == शून्य) अणु
				cअगरs_errorf(fc, "OOM when copying iocharset string\n");
				जाओ cअगरs_parse_mount_err;
			पूर्ण
		पूर्ण
		/* अगर ioअक्षरset not set then load_nls_शेष
		 * is used by caller
		 */
		cअगरs_dbg(FYI, "iocharset set to %s\n", ctx->ioअक्षरset);
		अवरोध;
	हाल Opt_netbiosname:
		स_रखो(ctx->source_rfc1001_name, 0x20,
			RFC1001_NAME_LEN);
		/*
		 * FIXME: are there हालs in which a comma can
		 * be valid in workstation netbios name (and
		 * need special handling)?
		 */
		क्रम (i = 0; i < RFC1001_NAME_LEN; i++) अणु
			/* करोn't uहाल netbiosname क्रम user */
			अगर (param->string[i] == 0)
				अवरोध;
			ctx->source_rfc1001_name[i] = param->string[i];
		पूर्ण
		/* The string has 16th byte zero still from
		 * set at top of the function
		 */
		अगर (i == RFC1001_NAME_LEN && param->string[i] != 0)
			pr_warn("netbiosname longer than 15 truncated\n");
		अवरोध;
	हाल Opt_servern:
		/* last byte, type, is 0x20 क्रम servr type */
		स_रखो(ctx->target_rfc1001_name, 0x20,
			RFC1001_NAME_LEN_WITH_शून्य);
		/*
		 * BB are there हालs in which a comma can be valid in this
		 * workstation netbios name (and need special handling)?
		 */

		/* user or mount helper must upperहाल the netbios name */
		क्रम (i = 0; i < 15; i++) अणु
			अगर (param->string[i] == 0)
				अवरोध;
			ctx->target_rfc1001_name[i] = param->string[i];
		पूर्ण

		/* The string has 16th byte zero still from set at top of function */
		अगर (i == RFC1001_NAME_LEN && param->string[i] != 0)
			pr_warn("server netbiosname longer than 15 truncated\n");
		अवरोध;
	हाल Opt_ver:
		/* version of mount userspace tools, not dialect */
		/* If पूर्णांकerface changes in mount.cअगरs bump to new ver */
		अगर (strnहालcmp(param->string, "1", 1) == 0) अणु
			अगर (म_माप(param->string) > 1) अणु
				pr_warn("Bad mount helper ver=%s. Did you want SMB1 (CIFS) dialect and mean to type vers=1.0 instead?\n",
					param->string);
				जाओ cअगरs_parse_mount_err;
			पूर्ण
			/* This is the शेष */
			अवरोध;
		पूर्ण
		/* For all other value, error */
		pr_warn("Invalid mount helper version specified\n");
		जाओ cअगरs_parse_mount_err;
	हाल Opt_vers:
		/* protocol version (dialect) */
		अगर (cअगरs_parse_smb_version(fc, param->string, ctx, is_smb3) != 0)
			जाओ cअगरs_parse_mount_err;
		ctx->got_version = true;
		अवरोध;
	हाल Opt_sec:
		अगर (cअगरs_parse_security_flavors(fc, param->string, ctx) != 0)
			जाओ cअगरs_parse_mount_err;
		अवरोध;
	हाल Opt_cache:
		अगर (cअगरs_parse_cache_flavor(fc, param->string, ctx) != 0)
			जाओ cअगरs_parse_mount_err;
		अवरोध;
	हाल Opt_witness:
#अगर_अघोषित CONFIG_CIFS_SWN_UPCALL
		cअगरs_errorf(fc, "Witness support needs CONFIG_CIFS_SWN_UPCALL config option\n");
			जाओ cअगरs_parse_mount_err;
#पूर्ण_अगर
		ctx->witness = true;
		pr_warn_once("Witness protocol support is experimental\n");
		अवरोध;
	हाल Opt_rootfs:
#अगर_अघोषित CONFIG_CIFS_ROOT
		cअगरs_dbg(VFS, "rootfs support requires CONFIG_CIFS_ROOT config option\n");
		जाओ cअगरs_parse_mount_err;
#पूर्ण_अगर
		ctx->rootfs = true;
		अवरोध;
	हाल Opt_posixpaths:
		अगर (result.negated)
			ctx->posix_paths = 0;
		अन्यथा
			ctx->posix_paths = 1;
		अवरोध;
	हाल Opt_unix:
		अगर (result.negated)
			ctx->linux_ext = 0;
		अन्यथा
			ctx->no_linux_ext = 1;
		अवरोध;
	हाल Opt_noहाल:
		ctx->noहाल = 1;
		अवरोध;
	हाल Opt_brl:
		अगर (result.negated) अणु
			/*
			 * turn off mandatory locking in mode
			 * अगर remote locking is turned off since the
			 * local vfs will करो advisory
			 */
			अगर (ctx->file_mode ==
				(S_IALLUGO & ~(S_ISUID | S_IXGRP)))
				ctx->file_mode = S_IALLUGO;
			ctx->nobrl =  1;
		पूर्ण अन्यथा
			ctx->nobrl =  0;
		अवरोध;
	हाल Opt_handlecache:
		अगर (result.negated)
			ctx->nohandlecache = 1;
		अन्यथा
			ctx->nohandlecache = 0;
		अवरोध;
	हाल Opt_क्रमcemandatorylock:
		ctx->mand_lock = 1;
		अवरोध;
	हाल Opt_setuids:
		ctx->setuids = result.negated;
		अवरोध;
	हाल Opt_पूर्णांकr:
		ctx->पूर्णांकr = !result.negated;
		अवरोध;
	हाल Opt_setuidfromacl:
		ctx->setuidfromacl = 1;
		अवरोध;
	हाल Opt_strictsync:
		ctx->nostrictsync = result.negated;
		अवरोध;
	हाल Opt_serverino:
		ctx->server_ino = !result.negated;
		अवरोध;
	हाल Opt_rwpidक्रमward:
		ctx->rwpidक्रमward = 1;
		अवरोध;
	हाल Opt_modesid:
		ctx->mode_ace = 1;
		अवरोध;
	हाल Opt_cअगरsacl:
		ctx->cअगरs_acl = !result.negated;
		अवरोध;
	हाल Opt_acl:
		ctx->no_psx_acl = result.negated;
		अवरोध;
	हाल Opt_locallease:
		ctx->local_lease = 1;
		अवरोध;
	हाल Opt_sign:
		ctx->sign = true;
		अवरोध;
	हाल Opt_ignore_signature:
		ctx->sign = true;
		ctx->ignore_signature = true;
		अवरोध;
	हाल Opt_seal:
		/* we करो not करो the following in secFlags because seal
		 * is a per tree connection (mount) not a per socket
		 * or per-smb connection option in the protocol
		 * vol->secFlg |= CIFSSEC_MUST_SEAL;
		 */
		ctx->seal = 1;
		अवरोध;
	हाल Opt_noac:
		pr_warn("Mount option noac not supported. Instead set /proc/fs/cifs/LookupCacheEnabled to 0\n");
		अवरोध;
	हाल Opt_fsc:
#अगर_अघोषित CONFIG_CIFS_FSCACHE
		cअगरs_errorf(fc, "FS-Cache support needs CONFIG_CIFS_FSCACHE kernel config option set\n");
		जाओ cअगरs_parse_mount_err;
#पूर्ण_अगर
		ctx->fsc = true;
		अवरोध;
	हाल Opt_mfsymlinks:
		ctx->mfsymlinks = true;
		अवरोध;
	हाल Opt_multiuser:
		ctx->multiuser = true;
		अवरोध;
	हाल Opt_sloppy:
		ctx->sloppy = true;
		अवरोध;
	हाल Opt_nosharesock:
		ctx->nosharesock = true;
		अवरोध;
	हाल Opt_persistent:
		अगर (result.negated) अणु
			ctx->nopersistent = true;
			अगर (ctx->persistent) अणु
				cअगरs_errorf(fc, "persistenthandles mount options conflict\n");
				जाओ cअगरs_parse_mount_err;
			पूर्ण
		पूर्ण अन्यथा अणु
			ctx->persistent = true;
			अगर ((ctx->nopersistent) || (ctx->resilient)) अणु
				cअगरs_errorf(fc, "persistenthandles mount options conflict\n");
				जाओ cअगरs_parse_mount_err;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल Opt_resilient:
		अगर (result.negated) अणु
			ctx->resilient = false; /* alपढ़ोy the शेष */
		पूर्ण अन्यथा अणु
			ctx->resilient = true;
			अगर (ctx->persistent) अणु
				cअगरs_errorf(fc, "persistenthandles mount options conflict\n");
				जाओ cअगरs_parse_mount_err;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल Opt_करोमुख्यस्वतः:
		ctx->करोमुख्यस्वतः = true;
		अवरोध;
	हाल Opt_rdma:
		ctx->rdma = true;
		अवरोध;
	पूर्ण
	/* हाल Opt_ignore: - is ignored as expected ... */

	वापस 0;

 cअगरs_parse_mount_err:
	वापस -EINVAL;
पूर्ण

पूर्णांक smb3_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा smb3_fs_context *ctx;
	अक्षर *nodename = utsname()->nodename;
	पूर्णांक i;

	ctx = kzalloc(माप(काष्ठा smb3_fs_context), GFP_KERNEL);
	अगर (unlikely(!ctx))
		वापस -ENOMEM;

	/*
	 * करोes not have to be perfect mapping since field is
	 * inक्रमmational, only used क्रम servers that करो not support
	 * port 445 and it can be overridden at mount समय
	 */
	स_रखो(ctx->source_rfc1001_name, 0x20, RFC1001_NAME_LEN);
	क्रम (i = 0; i < strnlen(nodename, RFC1001_NAME_LEN); i++)
		ctx->source_rfc1001_name[i] = बड़े(nodename[i]);

	ctx->source_rfc1001_name[RFC1001_NAME_LEN] = 0;
	/*
	 * null target name indicates to use *SMBSERVR शेष called name
	 *  अगर we end up sending RFC1001 session initialize
	 */
	ctx->target_rfc1001_name[0] = 0;
	ctx->cred_uid = current_uid();
	ctx->linux_uid = current_uid();
	ctx->linux_gid = current_gid();
	/* By शेष 4MB पढ़ो ahead size, 1MB block size */
	ctx->bsize = CIFS_DEFAULT_IOSIZE; /* can improve cp perक्रमmance signअगरicantly */
	ctx->rasize = 0; /* 0 = use शेष (ie negotiated rsize) क्रम पढ़ो ahead pages */

	/*
	 * शेष to SFM style remapping of seven reserved अक्षरacters
	 * unless user overrides it or we negotiate CIFS POSIX where
	 * it is unnecessary.  Can not simultaneously use more than one mapping
	 * since then सूची_पढ़ो could list files that खोलो could not खोलो
	 */
	ctx->remap = true;

	/* शेष to only allowing ग_लिखो access to owner of the mount */
	ctx->dir_mode = ctx->file_mode = S_IRUGO | S_IXUGO | S_IWUSR;

	/* ctx->retry शेष is 0 (i.e. "soft" limited retry not hard retry) */
	/* शेष is always to request posix paths. */
	ctx->posix_paths = 1;
	/* शेष to using server inode numbers where available */
	ctx->server_ino = 1;

	/* शेष is to use strict cअगरs caching semantics */
	ctx->strict_io = true;

	ctx->acregmax = CIFS_DEF_ACTIMEO;
	ctx->acdirmax = CIFS_DEF_ACTIMEO;

	/* Most clients set समयout to 0, allows server to use its शेष */
	ctx->handle_समयout = 0; /* See MS-SMB2 spec section 2.2.14.2.12 */

	/* offer SMB2.1 and later (SMB3 etc). Secure and widely accepted */
	ctx->ops = &smb30_operations;
	ctx->vals = &smbशेष_values;

	ctx->echo_पूर्णांकerval = SMB_ECHO_INTERVAL_DEFAULT;

	/* शेष to no multichannel (single server connection) */
	ctx->multichannel = false;
	ctx->max_channels = 1;

	ctx->backupuid_specअगरied = false; /* no backup पूर्णांकent क्रम a user */
	ctx->backupgid_specअगरied = false; /* no backup पूर्णांकent क्रम a group */

/*
 *	लघु पूर्णांक override_uid = -1;
 *	लघु पूर्णांक override_gid = -1;
 *	अक्षर *nodename = strdup(utsname()->nodename);
 *	काष्ठा sockaddr *dstaddr = (काष्ठा sockaddr *)&vol->dstaddr;
 */

	fc->fs_निजी = ctx;
	fc->ops = &smb3_fs_context_ops;
	वापस 0;
पूर्ण

व्योम
smb3_cleanup_fs_context_contents(काष्ठा smb3_fs_context *ctx)
अणु
	अगर (ctx == शून्य)
		वापस;

	/*
	 * Make sure this stays in sync with smb3_fs_context_dup()
	 */
	kमुक्त(ctx->mount_options);
	ctx->mount_options = शून्य;
	kमुक्त(ctx->username);
	ctx->username = शून्य;
	kमुक्त_sensitive(ctx->password);
	ctx->password = शून्य;
	kमुक्त(ctx->UNC);
	ctx->UNC = शून्य;
	kमुक्त(ctx->source);
	ctx->source = शून्य;
	kमुक्त(ctx->करोमुख्यname);
	ctx->करोमुख्यname = शून्य;
	kमुक्त(ctx->nodename);
	ctx->nodename = शून्य;
	kमुक्त(ctx->ioअक्षरset);
	ctx->ioअक्षरset = शून्य;
	kमुक्त(ctx->prepath);
	ctx->prepath = शून्य;
पूर्ण

व्योम
smb3_cleanup_fs_context(काष्ठा smb3_fs_context *ctx)
अणु
	अगर (!ctx)
		वापस;
	smb3_cleanup_fs_context_contents(ctx);
	kमुक्त(ctx);
पूर्ण

व्योम smb3_update_mnt_flags(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	काष्ठा smb3_fs_context *ctx = cअगरs_sb->ctx;

	अगर (ctx->nodfs)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NO_DFS;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NO_DFS;

	अगर (ctx->noperm)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NO_PERM;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NO_PERM;

	अगर (ctx->setuids)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_SET_UID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_SET_UID;

	अगर (ctx->setuidfromacl)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_UID_FROM_ACL;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_UID_FROM_ACL;

	अगर (ctx->server_ino)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_SERVER_INUM;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_SERVER_INUM;

	अगर (ctx->remap)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_MAP_SFM_CHR;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_MAP_SFM_CHR;

	अगर (ctx->sfu_remap)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_MAP_SPECIAL_CHR;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_MAP_SPECIAL_CHR;

	अगर (ctx->no_xattr)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NO_XATTR;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NO_XATTR;

	अगर (ctx->sfu_emul)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_UNX_EMUL;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_UNX_EMUL;

	अगर (ctx->nobrl)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NO_BRL;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NO_BRL;

	अगर (ctx->nohandlecache)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NO_HANDLE_CACHE;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NO_HANDLE_CACHE;

	अगर (ctx->nostrictsync)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NOSSYNC;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NOSSYNC;

	अगर (ctx->mand_lock)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_NOPOSIXBRL;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_NOPOSIXBRL;

	अगर (ctx->rwpidक्रमward)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_RWPIDFORWARD;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_RWPIDFORWARD;

	अगर (ctx->mode_ace)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_MODE_FROM_SID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_MODE_FROM_SID;

	अगर (ctx->cअगरs_acl)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_CIFS_ACL;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_CIFS_ACL;

	अगर (ctx->backupuid_specअगरied)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_CIFS_BACKUPUID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_CIFS_BACKUPUID;

	अगर (ctx->backupgid_specअगरied)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_CIFS_BACKUPGID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_CIFS_BACKUPGID;

	अगर (ctx->override_uid)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_OVERR_UID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_OVERR_UID;

	अगर (ctx->override_gid)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_OVERR_GID;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_OVERR_GID;

	अगर (ctx->dynperm)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_DYNPERM;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_DYNPERM;

	अगर (ctx->fsc)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_FSCACHE;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_FSCACHE;

	अगर (ctx->multiuser)
		cअगरs_sb->mnt_cअगरs_flags |= (CIFS_MOUNT_MULTIUSER |
					    CIFS_MOUNT_NO_PERM);
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_MULTIUSER;


	अगर (ctx->strict_io)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_STRICT_IO;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_STRICT_IO;

	अगर (ctx->direct_io)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_सूचीECT_IO;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_सूचीECT_IO;

	अगर (ctx->mfsymlinks)
		cअगरs_sb->mnt_cअगरs_flags |= CIFS_MOUNT_MF_SYMLINKS;
	अन्यथा
		cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_MF_SYMLINKS;
	अगर (ctx->mfsymlinks) अणु
		अगर (ctx->sfu_emul) अणु
			/*
			 * Our SFU ("Services for Unix" emulation करोes not allow
			 * creating symlinks but करोes allow पढ़ोing existing SFU
			 * symlinks (it करोes allow both creating and पढ़ोing SFU
			 * style mknod and FIFOs though). When "mfsymlinks" and
			 * "sfu" are both enabled at the same समय, it allows
			 * पढ़ोing both types of symlinks, but will only create
			 * them with mfsymlinks क्रमmat. This allows better
			 * Apple compatibility (probably better क्रम Samba too)
			 * जबतक still recognizing old Winकरोws style symlinks.
			 */
			cअगरs_dbg(VFS, "mount options mfsymlinks and sfu both enabled\n");
		पूर्ण
	पूर्ण
	cअगरs_sb->mnt_cअगरs_flags &= ~CIFS_MOUNT_SHUTDOWN;

	वापस;
पूर्ण
