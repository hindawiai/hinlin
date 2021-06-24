<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Syscall पूर्णांकerface to knfsd.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs_context.h>

#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/sunrpc/gss_krb5_enctypes.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/module.h>
#समावेश <linux/fsnotअगरy.h>

#समावेश "idmap.h"
#समावेश "nfsd.h"
#समावेश "cache.h"
#समावेश "state.h"
#समावेश "netns.h"
#समावेश "pnfs.h"

/*
 *	We have a single directory with several nodes in it.
 */
क्रमागत अणु
	NFSD_Root = 1,
	NFSD_List,
	NFSD_Export_Stats,
	NFSD_Export_features,
	NFSD_Fh,
	NFSD_FO_UnlockIP,
	NFSD_FO_UnlockFS,
	NFSD_Thपढ़ोs,
	NFSD_Pool_Thपढ़ोs,
	NFSD_Pool_Stats,
	NFSD_Reply_Cache_Stats,
	NFSD_Versions,
	NFSD_Ports,
	NFSD_MaxBlkSize,
	NFSD_MaxConnections,
	NFSD_SupportedEnctypes,
	/*
	 * The below MUST come last.  Otherwise we leave a hole in nfsd_files[]
	 * with !CONFIG_NFSD_V4 and simple_fill_super() goes oops
	 */
#अगर_घोषित CONFIG_NFSD_V4
	NFSD_Leaseसमय,
	NFSD_Graceसमय,
	NFSD_RecoveryDir,
	NFSD_V4EndGrace,
#पूर्ण_अगर
	NFSD_MaxReserved
पूर्ण;

/*
 * ग_लिखो() क्रम these nodes.
 */
अटल sमाप_प्रकार ग_लिखो_filehandle(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_unlock_ip(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_unlock_fs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_thपढ़ोs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_pool_thपढ़ोs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_versions(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_ports(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_maxblksize(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_maxconn(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
#अगर_घोषित CONFIG_NFSD_V4
अटल sमाप_प्रकार ग_लिखो_leaseसमय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_graceसमय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_recoverydir(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ग_लिखो_v4_end_grace(काष्ठा file *file, अक्षर *buf, माप_प्रकार size);
#पूर्ण_अगर

अटल sमाप_प्रकार (*स्थिर ग_लिखो_op[])(काष्ठा file *, अक्षर *, माप_प्रकार) = अणु
	[NFSD_Fh] = ग_लिखो_filehandle,
	[NFSD_FO_UnlockIP] = ग_लिखो_unlock_ip,
	[NFSD_FO_UnlockFS] = ग_लिखो_unlock_fs,
	[NFSD_Thपढ़ोs] = ग_लिखो_thपढ़ोs,
	[NFSD_Pool_Thपढ़ोs] = ग_लिखो_pool_thपढ़ोs,
	[NFSD_Versions] = ग_लिखो_versions,
	[NFSD_Ports] = ग_लिखो_ports,
	[NFSD_MaxBlkSize] = ग_लिखो_maxblksize,
	[NFSD_MaxConnections] = ग_लिखो_maxconn,
#अगर_घोषित CONFIG_NFSD_V4
	[NFSD_Leaseसमय] = ग_लिखो_leaseसमय,
	[NFSD_Graceसमय] = ग_लिखो_graceसमय,
	[NFSD_RecoveryDir] = ग_लिखो_recoverydir,
	[NFSD_V4EndGrace] = ग_लिखो_v4_end_grace,
#पूर्ण_अगर
पूर्ण;

अटल sमाप_प्रकार nfsctl_transaction_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार size, loff_t *pos)
अणु
	ino_t ino =  file_inode(file)->i_ino;
	अक्षर *data;
	sमाप_प्रकार rv;

	अगर (ino >= ARRAY_SIZE(ग_लिखो_op) || !ग_लिखो_op[ino])
		वापस -EINVAL;

	data = simple_transaction_get(file, buf, size);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rv =  ग_लिखो_op[ino](file, data, size);
	अगर (rv >= 0) अणु
		simple_transaction_set(file, rv);
		rv = size;
	पूर्ण
	वापस rv;
पूर्ण

अटल sमाप_प्रकार nfsctl_transaction_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size, loff_t *pos)
अणु
	अगर (! file->निजी_data) अणु
		/* An attempt to पढ़ो a transaction file without writing
		 * causes a 0-byte ग_लिखो so that the file can वापस
		 * state inक्रमmation
		 */
		sमाप_प्रकार rv = nfsctl_transaction_ग_लिखो(file, buf, 0, pos);
		अगर (rv < 0)
			वापस rv;
	पूर्ण
	वापस simple_transaction_पढ़ो(file, buf, size, pos);
पूर्ण

अटल स्थिर काष्ठा file_operations transaction_ops = अणु
	.ग_लिखो		= nfsctl_transaction_ग_लिखो,
	.पढ़ो		= nfsctl_transaction_पढ़ो,
	.release	= simple_transaction_release,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक exports_net_खोलो(काष्ठा net *net, काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा seq_file *seq;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	err = seq_खोलो(file, &nfs_exports_op);
	अगर (err)
		वापस err;

	seq = file->निजी_data;
	seq->निजी = nn->svc_export_cache;
	वापस 0;
पूर्ण

अटल पूर्णांक exports_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस exports_net_खोलो(current->nsproxy->net_ns, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops exports_proc_ops = अणु
	.proc_खोलो	= exports_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल पूर्णांक exports_nfsd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस exports_net_खोलो(inode->i_sb->s_fs_info, file);
पूर्ण

अटल स्थिर काष्ठा file_operations exports_nfsd_operations = अणु
	.खोलो		= exports_nfsd_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल पूर्णांक export_features_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "0x%x 0x%x\n", NFSEXP_ALLFLAGS, NFSEXP_SECINFO_FLAGS);
	वापस 0;
पूर्ण

अटल पूर्णांक export_features_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, export_features_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations export_features_operations = अणु
	.खोलो		= export_features_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#अगर defined(CONFIG_SUNRPC_GSS) || defined(CONFIG_SUNRPC_GSS_MODULE)
अटल पूर्णांक supported_enctypes_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, KRB5_SUPPORTED_ENCTYPES);
	वापस 0;
पूर्ण

अटल पूर्णांक supported_enctypes_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, supported_enctypes_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations supported_enctypes_ops = अणु
	.खोलो		= supported_enctypes_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SUNRPC_GSS or CONFIG_SUNRPC_GSS_MODULE */

अटल स्थिर काष्ठा file_operations pool_stats_operations = अणु
	.खोलो		= nfsd_pool_stats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= nfsd_pool_stats_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations reply_cache_stats_operations = अणु
	.खोलो		= nfsd_reply_cache_stats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

/*----------------------------------------------------------------------------*/
/*
 * payload - ग_लिखो methods
 */

अटल अंतरभूत काष्ठा net *netns(काष्ठा file *file)
अणु
	वापस file_inode(file)->i_sb->s_fs_info;
पूर्ण

/*
 * ग_लिखो_unlock_ip - Release all locks used by a client
 *
 * Experimental.
 *
 * Input:
 *			buf:	'\n'-terminated C string containing a
 *				presentation क्रमmat IP address
 *			size:	length of C string in @buf
 * Output:
 *	On success:	वापसs zero अगर all specअगरied locks were released;
 *			वापसs one अगर one or more locks were not released
 *	On error:	वापस code is negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_unlock_ip(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sockaddr_storage address;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&address;
	माप_प्रकार salen = माप(address);
	अक्षर *fo_path;
	काष्ठा net *net = netns(file);

	/* sanity check */
	अगर (size == 0)
		वापस -EINVAL;

	अगर (buf[size-1] != '\n')
		वापस -EINVAL;

	fo_path = buf;
	अगर (qword_get(&buf, fo_path, size) < 0)
		वापस -EINVAL;

	अगर (rpc_pton(net, fo_path, size, sap, salen) == 0)
		वापस -EINVAL;

	वापस nlmsvc_unlock_all_by_ip(sap);
पूर्ण

/*
 * ग_लिखो_unlock_fs - Release all locks on a local file प्रणाली
 *
 * Experimental.
 *
 * Input:
 *			buf:	'\n'-terminated C string containing the
 *				असलolute pathname of a local file प्रणाली
 *			size:	length of C string in @buf
 * Output:
 *	On success:	वापसs zero अगर all specअगरied locks were released;
 *			वापसs one अगर one or more locks were not released
 *	On error:	वापस code is negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_unlock_fs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा path path;
	अक्षर *fo_path;
	पूर्णांक error;

	/* sanity check */
	अगर (size == 0)
		वापस -EINVAL;

	अगर (buf[size-1] != '\n')
		वापस -EINVAL;

	fo_path = buf;
	अगर (qword_get(&buf, fo_path, size) < 0)
		वापस -EINVAL;

	error = kern_path(fo_path, 0, &path);
	अगर (error)
		वापस error;

	/*
	 * XXX: Needs better sanity checking.  Otherwise we could end up
	 * releasing locks on the wrong file प्रणाली.
	 *
	 * For example:
	 * 1.  Does the path refer to a directory?
	 * 2.  Is that directory a mount poपूर्णांक, or
	 * 3.  Is that directory the root of an exported file प्रणाली?
	 */
	error = nlmsvc_unlock_all_by_sb(path.dentry->d_sb);

	path_put(&path);
	वापस error;
पूर्ण

/*
 * ग_लिखो_filehandle - Get a variable-length NFS file handle by path
 *
 * On input, the buffer contains a '\n'-terminated C string comprised of
 * three alphanumeric words separated by whitespace.  The string may
 * contain escape sequences.
 *
 * Input:
 *			buf:
 *				करोमुख्य:		client करोमुख्य name
 *				path:		export pathname
 *				maxsize:	numeric maximum size of
 *						@buf
 *			size:	length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C
 *			string containing a ASCII hex text version
 *			of the NFS file handle;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_filehandle(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर *dname, *path;
	पूर्णांक maxsize;
	अक्षर *mesg = buf;
	पूर्णांक len;
	काष्ठा auth_करोमुख्य *करोm;
	काष्ठा knfsd_fh fh;

	अगर (size == 0)
		वापस -EINVAL;

	अगर (buf[size-1] != '\n')
		वापस -EINVAL;
	buf[size-1] = 0;

	dname = mesg;
	len = qword_get(&mesg, dname, size);
	अगर (len <= 0)
		वापस -EINVAL;
	
	path = dname+len+1;
	len = qword_get(&mesg, path, size);
	अगर (len <= 0)
		वापस -EINVAL;

	len = get_पूर्णांक(&mesg, &maxsize);
	अगर (len)
		वापस len;

	अगर (maxsize < NFS_FHSIZE)
		वापस -EINVAL;
	maxsize = min(maxsize, NFS3_FHSIZE);

	अगर (qword_get(&mesg, mesg, size)>0)
		वापस -EINVAL;

	/* we have all the words, they are in buf.. */
	करोm = unix_करोमुख्य_find(dname);
	अगर (!करोm)
		वापस -ENOMEM;

	len = exp_rootfh(netns(file), करोm, path, &fh,  maxsize);
	auth_करोमुख्य_put(करोm);
	अगर (len)
		वापस len;
	
	mesg = buf;
	len = SIMPLE_TRANSACTION_LIMIT;
	qword_addhex(&mesg, &len, (अक्षर*)&fh.fh_base, fh.fh_size);
	mesg[-1] = '\n';
	वापस mesg - buf;	
पूर्ण

/*
 * ग_लिखो_thपढ़ोs - Start NFSD, or report the current number of running thपढ़ोs
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C
 *			string numeric value representing the number of
 *			running NFSD thपढ़ोs;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero
 *
 * OR
 *
 * Input:
 *			buf:		C string containing an अचिन्हित
 *					पूर्णांकeger value representing the
 *					number of NFSD thपढ़ोs to start
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	NFS service is started;
 *			passed-in buffer filled with '\n'-terminated C
 *			string numeric value representing the number of
 *			running NFSD thपढ़ोs;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_thपढ़ोs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर *mesg = buf;
	पूर्णांक rv;
	काष्ठा net *net = netns(file);

	अगर (size > 0) अणु
		पूर्णांक newthपढ़ोs;
		rv = get_पूर्णांक(&mesg, &newthपढ़ोs);
		अगर (rv)
			वापस rv;
		अगर (newthपढ़ोs < 0)
			वापस -EINVAL;
		rv = nfsd_svc(newthपढ़ोs, net, file->f_cred);
		अगर (rv < 0)
			वापस rv;
	पूर्ण अन्यथा
		rv = nfsd_nrthपढ़ोs(net);

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%d\n", rv);
पूर्ण

/*
 * ग_लिखो_pool_thपढ़ोs - Set or report the current number of thपढ़ोs per pool
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 *
 * OR
 *
 * Input:
 * 			buf:		C string containing whitespace-
 * 					separated अचिन्हित पूर्णांकeger values
 *					representing the number of NFSD
 *					thपढ़ोs to start in each pool
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C
 *			string containing पूर्णांकeger values representing the
 *			number of NFSD thपढ़ोs in each pool;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_pool_thपढ़ोs(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	/* अगर size > 0, look क्रम an array of number of thपढ़ोs per node
	 * and apply them  then ग_लिखो out number of thपढ़ोs per node as reply
	 */
	अक्षर *mesg = buf;
	पूर्णांक i;
	पूर्णांक rv;
	पूर्णांक len;
	पूर्णांक npools;
	पूर्णांक *nthपढ़ोs;
	काष्ठा net *net = netns(file);

	mutex_lock(&nfsd_mutex);
	npools = nfsd_nrpools(net);
	अगर (npools == 0) अणु
		/*
		 * NFS is shut करोwn.  The admin can start it by
		 * writing to the thपढ़ोs file but NOT the pool_thपढ़ोs
		 * file, sorry.  Report zero thपढ़ोs.
		 */
		mutex_unlock(&nfsd_mutex);
		म_नकल(buf, "0\n");
		वापस म_माप(buf);
	पूर्ण

	nthपढ़ोs = kसुस्मृति(npools, माप(पूर्णांक), GFP_KERNEL);
	rv = -ENOMEM;
	अगर (nthपढ़ोs == शून्य)
		जाओ out_मुक्त;

	अगर (size > 0) अणु
		क्रम (i = 0; i < npools; i++) अणु
			rv = get_पूर्णांक(&mesg, &nthपढ़ोs[i]);
			अगर (rv == -ENOENT)
				अवरोध;		/* fewer numbers than pools */
			अगर (rv)
				जाओ out_मुक्त;	/* syntax error */
			rv = -EINVAL;
			अगर (nthपढ़ोs[i] < 0)
				जाओ out_मुक्त;
		पूर्ण
		rv = nfsd_set_nrthपढ़ोs(i, nthपढ़ोs, net);
		अगर (rv)
			जाओ out_मुक्त;
	पूर्ण

	rv = nfsd_get_nrthपढ़ोs(npools, nthपढ़ोs, net);
	अगर (rv)
		जाओ out_मुक्त;

	mesg = buf;
	size = SIMPLE_TRANSACTION_LIMIT;
	क्रम (i = 0; i < npools && size > 0; i++) अणु
		snम_लिखो(mesg, size, "%d%c", nthपढ़ोs[i], (i == npools-1 ? '\n' : ' '));
		len = म_माप(mesg);
		size -= len;
		mesg += len;
	पूर्ण
	rv = mesg - buf;
out_मुक्त:
	kमुक्त(nthपढ़ोs);
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार
nfsd_prपूर्णांक_version_support(काष्ठा nfsd_net *nn, अक्षर *buf, पूर्णांक reमुख्यing,
		स्थिर अक्षर *sep, अचिन्हित vers, पूर्णांक minor)
अणु
	स्थिर अक्षर *क्रमmat = minor < 0 ? "%s%c%u" : "%s%c%u.%u";
	bool supported = !!nfsd_vers(nn, vers, NFSD_TEST);

	अगर (vers == 4 && minor >= 0 &&
	    !nfsd_minorversion(nn, minor, NFSD_TEST))
		supported = false;
	अगर (minor == 0 && supported)
		/*
		 * special हाल क्रम backward compatability.
		 * +4.0 is never reported, it is implied by
		 * +4, unless -4.0 is present.
		 */
		वापस 0;
	वापस snम_लिखो(buf, reमुख्यing, क्रमmat, sep,
			supported ? '+' : '-', vers, minor);
पूर्ण

अटल sमाप_प्रकार __ग_लिखो_versions(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर *mesg = buf;
	अक्षर *vers, *minorp, sign;
	पूर्णांक len, num, reमुख्यing;
	sमाप_प्रकार tlen = 0;
	अक्षर *sep;
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);

	अगर (size>0) अणु
		अगर (nn->nfsd_serv)
			/* Cannot change versions without updating
			 * nn->nfsd_serv->sv_xdrsize, and पुनः_स्मृतिing
			 * rq_argp and rq_resp
			 */
			वापस -EBUSY;
		अगर (buf[size-1] != '\n')
			वापस -EINVAL;
		buf[size-1] = 0;

		vers = mesg;
		len = qword_get(&mesg, vers, size);
		अगर (len <= 0) वापस -EINVAL;
		करो अणु
			क्रमागत vers_op cmd;
			अचिन्हित minor;
			sign = *vers;
			अगर (sign == '+' || sign == '-')
				num = simple_म_से_दीर्घ((vers+1), &minorp, 0);
			अन्यथा
				num = simple_म_से_दीर्घ(vers, &minorp, 0);
			अगर (*minorp == '.') अणु
				अगर (num != 4)
					वापस -EINVAL;
				अगर (kstrtouपूर्णांक(minorp+1, 0, &minor) < 0)
					वापस -EINVAL;
			पूर्ण

			cmd = sign == '-' ? NFSD_CLEAR : NFSD_SET;
			चयन(num) अणु
			हाल 2:
			हाल 3:
				nfsd_vers(nn, num, cmd);
				अवरोध;
			हाल 4:
				अगर (*minorp == '.') अणु
					अगर (nfsd_minorversion(nn, minor, cmd) < 0)
						वापस -EINVAL;
				पूर्ण अन्यथा अगर ((cmd == NFSD_SET) != nfsd_vers(nn, num, NFSD_TEST)) अणु
					/*
					 * Either we have +4 and no minors are enabled,
					 * or we have -4 and at least one minor is enabled.
					 * In either हाल, propagate 'cmd' to all minors.
					 */
					minor = 0;
					जबतक (nfsd_minorversion(nn, minor, cmd) >= 0)
						minor++;
				पूर्ण
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			vers += len + 1;
		पूर्ण जबतक ((len = qword_get(&mesg, vers, size)) > 0);
		/* If all get turned off, turn them back on, as
		 * having no versions is BAD
		 */
		nfsd_reset_versions(nn);
	पूर्ण

	/* Now ग_लिखो current state पूर्णांकo reply buffer */
	len = 0;
	sep = "";
	reमुख्यing = SIMPLE_TRANSACTION_LIMIT;
	क्रम (num=2 ; num <= 4 ; num++) अणु
		पूर्णांक minor;
		अगर (!nfsd_vers(nn, num, NFSD_AVAIL))
			जारी;

		minor = -1;
		करो अणु
			len = nfsd_prपूर्णांक_version_support(nn, buf, reमुख्यing,
					sep, num, minor);
			अगर (len >= reमुख्यing)
				जाओ out;
			reमुख्यing -= len;
			buf += len;
			tlen += len;
			minor++;
			अगर (len)
				sep = " ";
		पूर्ण जबतक (num == 4 && minor <= NFSD_SUPPORTED_MINOR_VERSION);
	पूर्ण
out:
	len = snम_लिखो(buf, reमुख्यing, "\n");
	अगर (len >= reमुख्यing)
		वापस -EINVAL;
	वापस tlen + len;
पूर्ण

/*
 * ग_लिखो_versions - Set or report the available NFS protocol versions
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C
 *			string containing positive or negative पूर्णांकeger
 *			values representing the current status of each
 *			protocol version;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 *
 * OR
 *
 * Input:
 * 			buf:		C string containing whitespace-
 * 					separated positive or negative
 * 					पूर्णांकeger values representing NFS
 * 					protocol versions to enable ("+n")
 * 					or disable ("-n")
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	status of zero or more protocol versions has
 *			been updated; passed-in buffer filled with
 *			'\n'-terminated C string containing positive
 *			or negative पूर्णांकeger values representing the
 *			current status of each protocol version;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_versions(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार rv;

	mutex_lock(&nfsd_mutex);
	rv = __ग_लिखो_versions(file, buf, size);
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण

/*
 * Zero-length ग_लिखो.  Return a list of NFSD's current listener
 * transports.
 */
अटल sमाप_प्रकार __ग_लिखो_ports_names(अक्षर *buf, काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (nn->nfsd_serv == शून्य)
		वापस 0;
	वापस svc_xprt_names(nn->nfsd_serv, buf, SIMPLE_TRANSACTION_LIMIT);
पूर्ण

/*
 * A single 'fd' number was written, in which हाल it must be क्रम
 * a socket of a supported family/protocol, and we use it as an
 * nfsd listener.
 */
अटल sमाप_प्रकार __ग_लिखो_ports_addfd(अक्षर *buf, काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	अक्षर *mesg = buf;
	पूर्णांक fd, err;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	err = get_पूर्णांक(&mesg, &fd);
	अगर (err != 0 || fd < 0)
		वापस -EINVAL;

	अगर (svc_alien_sock(net, fd)) अणु
		prपूर्णांकk(KERN_ERR "%s: socket net is different to NFSd's one\n", __func__);
		वापस -EINVAL;
	पूर्ण

	err = nfsd_create_serv(net);
	अगर (err != 0)
		वापस err;

	err = svc_addsock(nn->nfsd_serv, fd, buf, SIMPLE_TRANSACTION_LIMIT, cred);
	अगर (err < 0) अणु
		nfsd_destroy(net);
		वापस err;
	पूर्ण

	/* Decrease the count, but करोn't shut करोwn the service */
	nn->nfsd_serv->sv_nrthपढ़ोs--;
	वापस err;
पूर्ण

/*
 * A transport listener is added by writing it's transport name and
 * a port number.
 */
अटल sमाप_प्रकार __ग_लिखो_ports_addxprt(अक्षर *buf, काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	अक्षर transport[16];
	काष्ठा svc_xprt *xprt;
	पूर्णांक port, err;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (माला_पूछो(buf, "%15s %5u", transport, &port) != 2)
		वापस -EINVAL;

	अगर (port < 1 || port > अच_लघु_उच्च)
		वापस -EINVAL;

	err = nfsd_create_serv(net);
	अगर (err != 0)
		वापस err;

	err = svc_create_xprt(nn->nfsd_serv, transport, net,
				PF_INET, port, SVC_SOCK_ANONYMOUS, cred);
	अगर (err < 0)
		जाओ out_err;

	err = svc_create_xprt(nn->nfsd_serv, transport, net,
				PF_INET6, port, SVC_SOCK_ANONYMOUS, cred);
	अगर (err < 0 && err != -EAFNOSUPPORT)
		जाओ out_बंद;

	/* Decrease the count, but करोn't shut करोwn the service */
	nn->nfsd_serv->sv_nrthपढ़ोs--;
	वापस 0;
out_बंद:
	xprt = svc_find_xprt(nn->nfsd_serv, transport, net, PF_INET, port);
	अगर (xprt != शून्य) अणु
		svc_बंद_xprt(xprt);
		svc_xprt_put(xprt);
	पूर्ण
out_err:
	nfsd_destroy(net);
	वापस err;
पूर्ण

अटल sमाप_प्रकार __ग_लिखो_ports(काष्ठा file *file, अक्षर *buf, माप_प्रकार size,
			     काष्ठा net *net)
अणु
	अगर (size == 0)
		वापस __ग_लिखो_ports_names(buf, net);

	अगर (है_अंक(buf[0]))
		वापस __ग_लिखो_ports_addfd(buf, net, file->f_cred);

	अगर (है_अक्षर(buf[0]))
		वापस __ग_लिखो_ports_addxprt(buf, net, file->f_cred);

	वापस -EINVAL;
पूर्ण

/*
 * ग_लिखो_ports - Pass a socket file descriptor or transport name to listen on
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 * Output:
 *	On success:	passed-in buffer filled with a '\n'-terminated C
 *			string containing a whitespace-separated list of
 *			named NFSD listeners;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 *
 * OR
 *
 * Input:
 *			buf:		C string containing an अचिन्हित
 *					पूर्णांकeger value representing a bound
 *					but unconnected socket that is to be
 *					used as an NFSD listener; listen(3)
 *					must be called क्रम a SOCK_STREAM
 *					socket, otherwise it is ignored
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	NFS service is started;
 *			passed-in buffer filled with a '\n'-terminated C
 *			string containing a unique alphanumeric name of
 *			the listener;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is a negative त्रुटि_सं value
 *
 * OR
 *
 * Input:
 *			buf:		C string containing a transport
 *					name and an अचिन्हित पूर्णांकeger value
 *					representing the port to listen on,
 *					separated by whitespace
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	वापसs zero; NFS service is started
 *	On error:	वापस code is a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_ports(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार rv;

	mutex_lock(&nfsd_mutex);
	rv = __ग_लिखो_ports(file, buf, size, netns(file));
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण


पूर्णांक nfsd_max_blksize;

/*
 * ग_लिखो_maxblksize - Set or report the current NFS blksize
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 *
 * OR
 *
 * Input:
 * 			buf:		C string containing an अचिन्हित
 * 					पूर्णांकeger value representing the new
 * 					NFS blksize
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C string
 *			containing numeric value of the current NFS blksize
 *			setting;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_maxblksize(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर *mesg = buf;
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);

	अगर (size > 0) अणु
		पूर्णांक bsize;
		पूर्णांक rv = get_पूर्णांक(&mesg, &bsize);
		अगर (rv)
			वापस rv;
		/* क्रमce bsize पूर्णांकo allowed range and
		 * required alignment.
		 */
		bsize = max_t(पूर्णांक, bsize, 1024);
		bsize = min_t(पूर्णांक, bsize, NFSSVC_MAXBLKSIZE);
		bsize &= ~(1024-1);
		mutex_lock(&nfsd_mutex);
		अगर (nn->nfsd_serv) अणु
			mutex_unlock(&nfsd_mutex);
			वापस -EBUSY;
		पूर्ण
		nfsd_max_blksize = bsize;
		mutex_unlock(&nfsd_mutex);
	पूर्ण

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%d\n",
							nfsd_max_blksize);
पूर्ण

/*
 * ग_लिखो_maxconn - Set or report the current max number of connections
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 * OR
 *
 * Input:
 * 			buf:		C string containing an अचिन्हित
 * 					पूर्णांकeger value representing the new
 * 					number of max connections
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C string
 *			containing numeric value of max_connections setting
 *			क्रम this net namespace;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_maxconn(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर *mesg = buf;
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);
	अचिन्हित पूर्णांक maxconn = nn->max_connections;

	अगर (size > 0) अणु
		पूर्णांक rv = get_uपूर्णांक(&mesg, &maxconn);

		अगर (rv)
			वापस rv;
		nn->max_connections = maxconn;
	पूर्ण

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%u\n", maxconn);
पूर्ण

#अगर_घोषित CONFIG_NFSD_V4
अटल sमाप_प्रकार __nfsd4_ग_लिखो_समय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size,
				  समय64_t *समय, काष्ठा nfsd_net *nn)
अणु
	अक्षर *mesg = buf;
	पूर्णांक rv, i;

	अगर (size > 0) अणु
		अगर (nn->nfsd_serv)
			वापस -EBUSY;
		rv = get_पूर्णांक(&mesg, &i);
		अगर (rv)
			वापस rv;
		/*
		 * Some sanity checking.  We करोn't have a reason क्रम
		 * these particular numbers, but problems with the
		 * extremes are:
		 *	- Too लघु: the briefest network outage may
		 *	  cause clients to lose all their locks.  Also,
		 *	  the frequent polling may be wasteful.
		 *	- Too दीर्घ: करो you really want reboot recovery
		 *	  to take more than an hour?  Or to make other
		 *	  clients रुको an hour beक्रमe being able to
		 *	  revoke a dead client's locks?
		 */
		अगर (i < 10 || i > 3600)
			वापस -EINVAL;
		*समय = i;
	पूर्ण

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%lld\n", *समय);
पूर्ण

अटल sमाप_प्रकार nfsd4_ग_लिखो_समय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size,
				समय64_t *समय, काष्ठा nfsd_net *nn)
अणु
	sमाप_प्रकार rv;

	mutex_lock(&nfsd_mutex);
	rv = __nfsd4_ग_लिखो_समय(file, buf, size, समय, nn);
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण

/*
 * ग_लिखो_leaseसमय - Set or report the current NFSv4 lease समय
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 *
 * OR
 *
 * Input:
 *			buf:		C string containing an अचिन्हित
 *					पूर्णांकeger value representing the new
 *					NFSv4 lease expiry समय
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C
 *			string containing अचिन्हित पूर्णांकeger value of the
 *			current lease expiry समय;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_leaseसमय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);
	वापस nfsd4_ग_लिखो_समय(file, buf, size, &nn->nfsd4_lease, nn);
पूर्ण

/*
 * ग_लिखो_graceसमय - Set or report current NFSv4 grace period समय
 *
 * As above, but sets the समय of the NFSv4 grace period.
 *
 * Note this should never be set to less than the *previous*
 * lease-period समय, but we करोn't try to enक्रमce this.  (In the common
 * हाल (a new boot), we करोn't know what the previous lease समय was
 * anyway.)
 */
अटल sमाप_प्रकार ग_लिखो_graceसमय(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);
	वापस nfsd4_ग_लिखो_समय(file, buf, size, &nn->nfsd4_grace, nn);
पूर्ण

अटल sमाप_प्रकार __ग_लिखो_recoverydir(काष्ठा file *file, अक्षर *buf, माप_प्रकार size,
				   काष्ठा nfsd_net *nn)
अणु
	अक्षर *mesg = buf;
	अक्षर *recdir;
	पूर्णांक len, status;

	अगर (size > 0) अणु
		अगर (nn->nfsd_serv)
			वापस -EBUSY;
		अगर (size > PATH_MAX || buf[size-1] != '\n')
			वापस -EINVAL;
		buf[size-1] = 0;

		recdir = mesg;
		len = qword_get(&mesg, recdir, size);
		अगर (len <= 0)
			वापस -EINVAL;

		status = nfs4_reset_recoverydir(recdir);
		अगर (status)
			वापस status;
	पूर्ण

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%s\n",
							nfs4_recoverydir());
पूर्ण

/*
 * ग_लिखो_recoverydir - Set or report the pathname of the recovery directory
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 *
 * OR
 *
 * Input:
 *			buf:		C string containing the pathname
 *					of the directory on a local file
 *					प्रणाली containing permanent NFSv4
 *					recovery data
 *			size:		non-zero length of C string in @buf
 * Output:
 *	On success:	passed-in buffer filled with '\n'-terminated C string
 *			containing the current recovery pathname setting;
 *			वापस code is the size in bytes of the string
 *	On error:	वापस code is zero or a negative त्रुटि_सं value
 */
अटल sमाप_प्रकार ग_लिखो_recoverydir(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार rv;
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);

	mutex_lock(&nfsd_mutex);
	rv = __ग_लिखो_recoverydir(file, buf, size, nn);
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण

/*
 * ग_लिखो_v4_end_grace - release grace period क्रम nfsd's v4.x lock manager
 *
 * Input:
 *			buf:		ignored
 *			size:		zero
 * OR
 *
 * Input:
 * 			buf:		any value
 *			size:		non-zero length of C string in @buf
 * Output:
 *			passed-in buffer filled with "Y" or "N" with a newline
 *			and शून्य-terminated C string. This indicates whether
 *			the grace period has ended in the current net
 *			namespace. Return code is the size in bytes of the
 *			string. Writing a string that starts with 'Y', 'y', or
 *			'1' to the file will end the grace period for nfsd's v4
 *			lock manager.
 */
अटल sमाप_प्रकार ग_लिखो_v4_end_grace(काष्ठा file *file, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nfsd_net *nn = net_generic(netns(file), nfsd_net_id);

	अगर (size > 0) अणु
		चयन(buf[0]) अणु
		हाल 'Y':
		हाल 'y':
		हाल '1':
			अगर (!nn->nfsd_serv)
				वापस -EBUSY;
			nfsd4_end_grace(nn);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस scnम_लिखो(buf, SIMPLE_TRANSACTION_LIMIT, "%c\n",
			 nn->grace_ended ? 'Y' : 'N');
पूर्ण

#पूर्ण_अगर

/*----------------------------------------------------------------------------*/
/*
 *	populating the fileप्रणाली.
 */

/* Basically copying rpc_get_inode. */
अटल काष्ठा inode *nfsd_get_inode(काष्ठा super_block *sb, umode_t mode)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (!inode)
		वापस शून्य;
	/* Following advice from simple_fill_super करोcumentation: */
	inode->i_ino = iunique(sb, NFSD_MaxReserved);
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	चयन (mode & S_IFMT) अणु
	हाल S_IFसूची:
		inode->i_fop = &simple_dir_operations;
		inode->i_op = &simple_dir_inode_operations;
		inc_nlink(inode);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस inode;
पूर्ण

अटल पूर्णांक __nfsd_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode, काष्ठा nfsdfs_client *ncl)
अणु
	काष्ठा inode *inode;

	inode = nfsd_get_inode(dir->i_sb, mode);
	अगर (!inode)
		वापस -ENOMEM;
	अगर (ncl) अणु
		inode->i_निजी = ncl;
		kref_get(&ncl->cl_ref);
	पूर्ण
	d_add(dentry, inode);
	inc_nlink(dir);
	fsnotअगरy_सूची_गढ़ो(dir, dentry);
	वापस 0;
पूर्ण

अटल काष्ठा dentry *nfsd_सूची_गढ़ो(काष्ठा dentry *parent, काष्ठा nfsdfs_client *ncl, अक्षर *name)
अणु
	काष्ठा inode *dir = parent->d_inode;
	काष्ठा dentry *dentry;
	पूर्णांक ret = -ENOMEM;

	inode_lock(dir);
	dentry = d_alloc_name(parent, name);
	अगर (!dentry)
		जाओ out_err;
	ret = __nfsd_सूची_गढ़ो(d_inode(parent), dentry, S_IFसूची | 0600, ncl);
	अगर (ret)
		जाओ out_err;
out:
	inode_unlock(dir);
	वापस dentry;
out_err:
	dput(dentry);
	dentry = ERR_PTR(ret);
	जाओ out;
पूर्ण

अटल व्योम clear_ncl(काष्ठा inode *inode)
अणु
	काष्ठा nfsdfs_client *ncl = inode->i_निजी;

	inode->i_निजी = शून्य;
	kref_put(&ncl->cl_ref, ncl->cl_release);
पूर्ण

अटल काष्ठा nfsdfs_client *__get_nfsdfs_client(काष्ठा inode *inode)
अणु
	काष्ठा nfsdfs_client *nc = inode->i_निजी;

	अगर (nc)
		kref_get(&nc->cl_ref);
	वापस nc;
पूर्ण

काष्ठा nfsdfs_client *get_nfsdfs_client(काष्ठा inode *inode)
अणु
	काष्ठा nfsdfs_client *nc;

	inode_lock_shared(inode);
	nc = __get_nfsdfs_client(inode);
	inode_unlock_shared(inode);
	वापस nc;
पूर्ण
/* from __rpc_unlink */
अटल व्योम nfsdfs_हटाओ_file(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;

	clear_ncl(d_inode(dentry));
	dget(dentry);
	ret = simple_unlink(dir, dentry);
	d_delete(dentry);
	dput(dentry);
	WARN_ON_ONCE(ret);
पूर्ण

अटल व्योम nfsdfs_हटाओ_files(काष्ठा dentry *root)
अणु
	काष्ठा dentry *dentry, *पंचांगp;

	list_क्रम_each_entry_safe(dentry, पंचांगp, &root->d_subdirs, d_child) अणु
		अगर (!simple_positive(dentry)) अणु
			WARN_ON_ONCE(1); /* I think this can't happen? */
			जारी;
		पूर्ण
		nfsdfs_हटाओ_file(d_inode(root), dentry);
	पूर्ण
पूर्ण

/* XXX: cut'n'paste from simple_fill_super; figure out अगर we could share
 * code instead. */
अटल  पूर्णांक nfsdfs_create_files(काष्ठा dentry *root,
				स्थिर काष्ठा tree_descr *files,
				काष्ठा dentry **fdentries)
अणु
	काष्ठा inode *dir = d_inode(root);
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;
	पूर्णांक i;

	inode_lock(dir);
	क्रम (i = 0; files->name && files->name[0]; i++, files++) अणु
		dentry = d_alloc_name(root, files->name);
		अगर (!dentry)
			जाओ out;
		inode = nfsd_get_inode(d_inode(root)->i_sb,
					S_IFREG | files->mode);
		अगर (!inode) अणु
			dput(dentry);
			जाओ out;
		पूर्ण
		inode->i_fop = files->ops;
		inode->i_निजी = __get_nfsdfs_client(dir);
		d_add(dentry, inode);
		fsnotअगरy_create(dir, dentry);
		अगर (fdentries)
			fdentries[i] = dentry;
	पूर्ण
	inode_unlock(dir);
	वापस 0;
out:
	nfsdfs_हटाओ_files(root);
	inode_unlock(dir);
	वापस -ENOMEM;
पूर्ण

/* on success, वापसs positive number unique to that client. */
काष्ठा dentry *nfsd_client_सूची_गढ़ो(काष्ठा nfsd_net *nn,
				 काष्ठा nfsdfs_client *ncl, u32 id,
				 स्थिर काष्ठा tree_descr *files,
				 काष्ठा dentry **fdentries)
अणु
	काष्ठा dentry *dentry;
	अक्षर name[11];
	पूर्णांक ret;

	प्र_लिखो(name, "%u", id);

	dentry = nfsd_सूची_गढ़ो(nn->nfsd_client_dir, ncl, name);
	अगर (IS_ERR(dentry)) /* XXX: tossing errors? */
		वापस शून्य;
	ret = nfsdfs_create_files(dentry, files, fdentries);
	अगर (ret) अणु
		nfsd_client_सूची_हटाओ(dentry);
		वापस शून्य;
	पूर्ण
	वापस dentry;
पूर्ण

/* Taken from __rpc_सूची_हटाओ: */
व्योम nfsd_client_सूची_हटाओ(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक ret;

	inode_lock(dir);
	nfsdfs_हटाओ_files(dentry);
	clear_ncl(inode);
	dget(dentry);
	ret = simple_सूची_हटाओ(dir, dentry);
	WARN_ON_ONCE(ret);
	fsnotअगरy_सूची_हटाओ(dir, dentry);
	d_delete(dentry);
	dput(dentry);
	inode_unlock(dir);
पूर्ण

अटल पूर्णांक nfsd_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा nfsd_net *nn = net_generic(current->nsproxy->net_ns,
							nfsd_net_id);
	काष्ठा dentry *dentry;
	पूर्णांक ret;

	अटल स्थिर काष्ठा tree_descr nfsd_files[] = अणु
		[NFSD_List] = अणु"exports", &exports_nfsd_operations, S_IRUGOपूर्ण,
		/* Per-export io stats use same ops as exports file */
		[NFSD_Export_Stats] = अणु"export_stats", &exports_nfsd_operations, S_IRUGOपूर्ण,
		[NFSD_Export_features] = अणु"export_features",
					&export_features_operations, S_IRUGOपूर्ण,
		[NFSD_FO_UnlockIP] = अणु"unlock_ip",
					&transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_FO_UnlockFS] = अणु"unlock_filesystem",
					&transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Fh] = अणु"filehandle", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Thपढ़ोs] = अणु"threads", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Pool_Thपढ़ोs] = अणु"pool_threads", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Pool_Stats] = अणु"pool_stats", &pool_stats_operations, S_IRUGOपूर्ण,
		[NFSD_Reply_Cache_Stats] = अणु"reply_cache_stats", &reply_cache_stats_operations, S_IRUGOपूर्ण,
		[NFSD_Versions] = अणु"versions", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Ports] = अणु"portlist", &transaction_ops, S_IWUSR|S_IRUGOपूर्ण,
		[NFSD_MaxBlkSize] = अणु"max_block_size", &transaction_ops, S_IWUSR|S_IRUGOपूर्ण,
		[NFSD_MaxConnections] = अणु"max_connections", &transaction_ops, S_IWUSR|S_IRUGOपूर्ण,
#अगर defined(CONFIG_SUNRPC_GSS) || defined(CONFIG_SUNRPC_GSS_MODULE)
		[NFSD_SupportedEnctypes] = अणु"supported_krb5_enctypes", &supported_enctypes_ops, S_IRUGOपूर्ण,
#पूर्ण_अगर /* CONFIG_SUNRPC_GSS or CONFIG_SUNRPC_GSS_MODULE */
#अगर_घोषित CONFIG_NFSD_V4
		[NFSD_Leaseसमय] = अणु"nfsv4leasetime", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_Graceसमय] = अणु"nfsv4gracetime", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_RecoveryDir] = अणु"nfsv4recoverydir", &transaction_ops, S_IWUSR|S_IRUSRपूर्ण,
		[NFSD_V4EndGrace] = अणु"v4_end_grace", &transaction_ops, S_IWUSR|S_IRUGOपूर्ण,
#पूर्ण_अगर
		/* last one */ अणु""पूर्ण
	पूर्ण;

	ret = simple_fill_super(sb, 0x6e667364, nfsd_files);
	अगर (ret)
		वापस ret;
	dentry = nfsd_सूची_गढ़ो(sb->s_root, शून्य, "clients");
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	nn->nfsd_client_dir = dentry;
	वापस 0;
पूर्ण

अटल पूर्णांक nfsd_fs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_keyed(fc, nfsd_fill_super, get_net(fc->net_ns));
पूर्ण

अटल व्योम nfsd_fs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	अगर (fc->s_fs_info)
		put_net(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations nfsd_fs_context_ops = अणु
	.मुक्त		= nfsd_fs_मुक्त_fc,
	.get_tree	= nfsd_fs_get_tree,
पूर्ण;

अटल पूर्णांक nfsd_init_fs_context(काष्ठा fs_context *fc)
अणु
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(fc->net_ns->user_ns);
	fc->ops = &nfsd_fs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम nfsd_umount(काष्ठा super_block *sb)
अणु
	काष्ठा net *net = sb->s_fs_info;

	nfsd_shutकरोwn_thपढ़ोs(net);

	समाप्त_litter_super(sb);
	put_net(net);
पूर्ण

अटल काष्ठा file_प्रणाली_type nfsd_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "nfsd",
	.init_fs_context = nfsd_init_fs_context,
	.समाप्त_sb	= nfsd_umount,
पूर्ण;
MODULE_ALIAS_FS("nfsd");

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक create_proc_exports_entry(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	entry = proc_सूची_गढ़ो("fs/nfs", शून्य);
	अगर (!entry)
		वापस -ENOMEM;
	entry = proc_create("exports", 0, entry, &exports_proc_ops);
	अगर (!entry) अणु
		हटाओ_proc_entry("fs/nfs", शून्य);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_PROC_FS */
अटल पूर्णांक create_proc_exports_entry(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अचिन्हित पूर्णांक nfsd_net_id;

अटल __net_init पूर्णांक nfsd_init_net(काष्ठा net *net)
अणु
	पूर्णांक retval;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	retval = nfsd_export_init(net);
	अगर (retval)
		जाओ out_export_error;
	retval = nfsd_idmap_init(net);
	अगर (retval)
		जाओ out_idmap_error;
	nn->nfsd_versions = शून्य;
	nn->nfsd4_minorversions = शून्य;
	retval = nfsd_reply_cache_init(nn);
	अगर (retval)
		जाओ out_drc_error;
	nn->nfsd4_lease = 90;	/* शेष lease समय */
	nn->nfsd4_grace = 90;
	nn->somebody_reclaimed = false;
	nn->track_reclaim_completes = false;
	nn->clverअगरier_counter = pअक्रमom_u32();
	nn->clientid_base = pअक्रमom_u32();
	nn->clientid_counter = nn->clientid_base + 1;
	nn->s2s_cp_cl_id = nn->clientid_counter++;

	atomic_set(&nn->ntf_refcnt, 0);
	init_रुकोqueue_head(&nn->ntf_wq);
	seqlock_init(&nn->boot_lock);

	वापस 0;

out_drc_error:
	nfsd_idmap_shutकरोwn(net);
out_idmap_error:
	nfsd_export_shutकरोwn(net);
out_export_error:
	वापस retval;
पूर्ण

अटल __net_निकास व्योम nfsd_निकास_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfsd_reply_cache_shutकरोwn(nn);
	nfsd_idmap_shutकरोwn(net);
	nfsd_export_shutकरोwn(net);
	nfsd_netns_मुक्त_versions(net_generic(net, nfsd_net_id));
पूर्ण

अटल काष्ठा pernet_operations nfsd_net_ops = अणु
	.init = nfsd_init_net,
	.निकास = nfsd_निकास_net,
	.id   = &nfsd_net_id,
	.size = माप(काष्ठा nfsd_net),
पूर्ण;

अटल पूर्णांक __init init_nfsd(व्योम)
अणु
	पूर्णांक retval;
	prपूर्णांकk(KERN_INFO "Installing knfsd (copyright (C) 1996 okir@monad.swb.de).\n");

	retval = रेजिस्टर_cld_notअगरier();
	अगर (retval)
		वापस retval;
	retval = nfsd4_init_sद_असल();
	अगर (retval)
		जाओ out_unरेजिस्टर_notअगरier;
	retval = nfsd4_init_pnfs();
	अगर (retval)
		जाओ out_मुक्त_sद_असल;
	retval = nfsd_stat_init();	/* Statistics */
	अगर (retval)
		जाओ out_मुक्त_pnfs;
	retval = nfsd_drc_slab_create();
	अगर (retval)
		जाओ out_मुक्त_stat;
	nfsd_lockd_init();	/* lockd->nfsd callbacks */
	retval = create_proc_exports_entry();
	अगर (retval)
		जाओ out_मुक्त_lockd;
	retval = रेजिस्टर_fileप्रणाली(&nfsd_fs_type);
	अगर (retval)
		जाओ out_मुक्त_exports;
	retval = रेजिस्टर_pernet_subsys(&nfsd_net_ops);
	अगर (retval < 0)
		जाओ out_मुक्त_all;
	वापस 0;
out_मुक्त_all:
	unरेजिस्टर_pernet_subsys(&nfsd_net_ops);
out_मुक्त_exports:
	हटाओ_proc_entry("fs/nfs/exports", शून्य);
	हटाओ_proc_entry("fs/nfs", शून्य);
out_मुक्त_lockd:
	nfsd_lockd_shutकरोwn();
	nfsd_drc_slab_मुक्त();
out_मुक्त_stat:
	nfsd_stat_shutकरोwn();
out_मुक्त_pnfs:
	nfsd4_निकास_pnfs();
out_मुक्त_sद_असल:
	nfsd4_मुक्त_sद_असल();
out_unरेजिस्टर_notअगरier:
	unरेजिस्टर_cld_notअगरier();
	वापस retval;
पूर्ण

अटल व्योम __निकास निकास_nfsd(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&nfsd_net_ops);
	nfsd_drc_slab_मुक्त();
	हटाओ_proc_entry("fs/nfs/exports", शून्य);
	हटाओ_proc_entry("fs/nfs", शून्य);
	nfsd_stat_shutकरोwn();
	nfsd_lockd_shutकरोwn();
	nfsd4_मुक्त_sद_असल();
	nfsd4_निकास_pnfs();
	unरेजिस्टर_fileप्रणाली(&nfsd_fs_type);
	unरेजिस्टर_cld_notअगरier();
पूर्ण

MODULE_AUTHOR("Olaf Kirch <okir@monad.swb.de>");
MODULE_LICENSE("GPL");
module_init(init_nfsd)
module_निकास(निकास_nfsd)
