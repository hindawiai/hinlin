<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NFS exporting and validation.
 *
 * We मुख्यtain a list of clients, each of which has a list of
 * exports. To export an fs to a given client, you first have
 * to create the client entry with NFSCTL_ADDCLIENT, which
 * creates a client control block and adds it to the hash
 * table. Then, you call NFSCTL_EXPORT क्रम each fs.
 *
 *
 * Copyright (C) 1995, 1996 Olaf Kirch, <okir@monad.swb.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/module.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/sunrpc/svc_xprt.h>

#समावेश "nfsd.h"
#समावेश "nfsfh.h"
#समावेश "netns.h"
#समावेश "pnfs.h"
#समावेश "filecache.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_EXPORT

/*
 * We have two caches.
 * One maps client+vfsmnt+dentry to export options - the export map
 * The other maps client+filehandle-fragment to export options. - the expkey map
 *
 * The export options are actually stored in the first map, and the
 * second map contains a reference to the entry in the first map.
 */

#घोषणा	EXPKEY_HASHBITS		8
#घोषणा	EXPKEY_HASHMAX		(1 << EXPKEY_HASHBITS)
#घोषणा	EXPKEY_HASHMASK		(EXPKEY_HASHMAX -1)

अटल व्योम expkey_put(काष्ठा kref *ref)
अणु
	काष्ठा svc_expkey *key = container_of(ref, काष्ठा svc_expkey, h.ref);

	अगर (test_bit(CACHE_VALID, &key->h.flags) &&
	    !test_bit(CACHE_NEGATIVE, &key->h.flags))
		path_put(&key->ek_path);
	auth_करोमुख्य_put(key->ek_client);
	kमुक्त_rcu(key, ek_rcu);
पूर्ण

अटल पूर्णांक expkey_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall(cd, h);
पूर्ण

अटल व्योम expkey_request(काष्ठा cache_detail *cd,
			   काष्ठा cache_head *h,
			   अक्षर **bpp, पूर्णांक *blen)
अणु
	/* client fsidtype \षfsid */
	काष्ठा svc_expkey *ek = container_of(h, काष्ठा svc_expkey, h);
	अक्षर type[5];

	qword_add(bpp, blen, ek->ek_client->name);
	snम_लिखो(type, 5, "%d", ek->ek_fsidtype);
	qword_add(bpp, blen, type);
	qword_addhex(bpp, blen, (अक्षर*)ek->ek_fsid, key_len(ek->ek_fsidtype));
	(*bpp)[-1] = '\n';
पूर्ण

अटल काष्ठा svc_expkey *svc_expkey_update(काष्ठा cache_detail *cd, काष्ठा svc_expkey *new,
					    काष्ठा svc_expkey *old);
अटल काष्ठा svc_expkey *svc_expkey_lookup(काष्ठा cache_detail *cd, काष्ठा svc_expkey *);

अटल पूर्णांक expkey_parse(काष्ठा cache_detail *cd, अक्षर *mesg, पूर्णांक mlen)
अणु
	/* client fsidtype fsid expiry [path] */
	अक्षर *buf;
	पूर्णांक len;
	काष्ठा auth_करोमुख्य *करोm = शून्य;
	पूर्णांक err;
	पूर्णांक fsidtype;
	अक्षर *ep;
	काष्ठा svc_expkey key;
	काष्ठा svc_expkey *ek = शून्य;

	अगर (mesg[mlen - 1] != '\n')
		वापस -EINVAL;
	mesg[mlen-1] = 0;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!buf)
		जाओ out;

	err = -EINVAL;
	अगर ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		जाओ out;

	err = -ENOENT;
	करोm = auth_करोमुख्य_find(buf);
	अगर (!करोm)
		जाओ out;
	dprपूर्णांकk("found domain %s\n", buf);

	err = -EINVAL;
	अगर ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		जाओ out;
	fsidtype = simple_म_से_अदीर्घ(buf, &ep, 10);
	अगर (*ep)
		जाओ out;
	dprपूर्णांकk("found fsidtype %d\n", fsidtype);
	अगर (key_len(fsidtype)==0) /* invalid type */
		जाओ out;
	अगर ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		जाओ out;
	dprपूर्णांकk("found fsid length %d\n", len);
	अगर (len != key_len(fsidtype))
		जाओ out;

	/* OK, we seem to have a valid key */
	key.h.flags = 0;
	key.h.expiry_समय = get_expiry(&mesg);
	अगर (key.h.expiry_समय == 0)
		जाओ out;

	key.ek_client = करोm;	
	key.ek_fsidtype = fsidtype;
	स_नकल(key.ek_fsid, buf, len);

	ek = svc_expkey_lookup(cd, &key);
	err = -ENOMEM;
	अगर (!ek)
		जाओ out;

	/* now we want a pathname, or empty meaning NEGATIVE  */
	err = -EINVAL;
	len = qword_get(&mesg, buf, PAGE_SIZE);
	अगर (len < 0)
		जाओ out;
	dprपूर्णांकk("Path seems to be <%s>\n", buf);
	err = 0;
	अगर (len == 0) अणु
		set_bit(CACHE_NEGATIVE, &key.h.flags);
		ek = svc_expkey_update(cd, &key, ek);
		अगर (ek)
			trace_nfsd_expkey_update(ek, शून्य);
		अन्यथा
			err = -ENOMEM;
	पूर्ण अन्यथा अणु
		err = kern_path(buf, 0, &key.ek_path);
		अगर (err)
			जाओ out;

		dprपूर्णांकk("Found the path %s\n", buf);

		ek = svc_expkey_update(cd, &key, ek);
		अगर (ek)
			trace_nfsd_expkey_update(ek, buf);
		अन्यथा
			err = -ENOMEM;
		path_put(&key.ek_path);
	पूर्ण
	cache_flush();
 out:
	अगर (ek)
		cache_put(&ek->h, cd);
	अगर (करोm)
		auth_करोमुख्य_put(करोm);
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक expkey_show(काष्ठा seq_file *m,
		       काष्ठा cache_detail *cd,
		       काष्ठा cache_head *h)
अणु
	काष्ठा svc_expkey *ek ;
	पूर्णांक i;

	अगर (h ==शून्य) अणु
		seq_माला_दो(m, "#domain fsidtype fsid [path]\n");
		वापस 0;
	पूर्ण
	ek = container_of(h, काष्ठा svc_expkey, h);
	seq_म_लिखो(m, "%s %d 0x", ek->ek_client->name,
		   ek->ek_fsidtype);
	क्रम (i=0; i < key_len(ek->ek_fsidtype)/4; i++)
		seq_म_लिखो(m, "%08x", ek->ek_fsid[i]);
	अगर (test_bit(CACHE_VALID, &h->flags) && 
	    !test_bit(CACHE_NEGATIVE, &h->flags)) अणु
		seq_म_लिखो(m, " ");
		seq_path(m, &ek->ek_path, "\\ \t\n");
	पूर्ण
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक expkey_match (काष्ठा cache_head *a, काष्ठा cache_head *b)
अणु
	काष्ठा svc_expkey *orig = container_of(a, काष्ठा svc_expkey, h);
	काष्ठा svc_expkey *new = container_of(b, काष्ठा svc_expkey, h);

	अगर (orig->ek_fsidtype != new->ek_fsidtype ||
	    orig->ek_client != new->ek_client ||
	    स_भेद(orig->ek_fsid, new->ek_fsid, key_len(orig->ek_fsidtype)) != 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम expkey_init(काष्ठा cache_head *cnew,
				   काष्ठा cache_head *citem)
अणु
	काष्ठा svc_expkey *new = container_of(cnew, काष्ठा svc_expkey, h);
	काष्ठा svc_expkey *item = container_of(citem, काष्ठा svc_expkey, h);

	kref_get(&item->ek_client->ref);
	new->ek_client = item->ek_client;
	new->ek_fsidtype = item->ek_fsidtype;

	स_नकल(new->ek_fsid, item->ek_fsid, माप(new->ek_fsid));
पूर्ण

अटल अंतरभूत व्योम expkey_update(काष्ठा cache_head *cnew,
				   काष्ठा cache_head *citem)
अणु
	काष्ठा svc_expkey *new = container_of(cnew, काष्ठा svc_expkey, h);
	काष्ठा svc_expkey *item = container_of(citem, काष्ठा svc_expkey, h);

	new->ek_path = item->ek_path;
	path_get(&item->ek_path);
पूर्ण

अटल काष्ठा cache_head *expkey_alloc(व्योम)
अणु
	काष्ठा svc_expkey *i = kदो_स्मृति(माप(*i), GFP_KERNEL);
	अगर (i)
		वापस &i->h;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम expkey_flush(व्योम)
अणु
	/*
	 * Take the nfsd_mutex here to ensure that the file cache is not
	 * destroyed जबतक we're in the middle of flushing.
	 */
	mutex_lock(&nfsd_mutex);
	nfsd_file_cache_purge(current->nsproxy->net_ns);
	mutex_unlock(&nfsd_mutex);
पूर्ण

अटल स्थिर काष्ठा cache_detail svc_expkey_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= EXPKEY_HASHMAX,
	.name		= "nfsd.fh",
	.cache_put	= expkey_put,
	.cache_upcall	= expkey_upcall,
	.cache_request	= expkey_request,
	.cache_parse	= expkey_parse,
	.cache_show	= expkey_show,
	.match		= expkey_match,
	.init		= expkey_init,
	.update       	= expkey_update,
	.alloc		= expkey_alloc,
	.flush		= expkey_flush,
पूर्ण;

अटल पूर्णांक
svc_expkey_hash(काष्ठा svc_expkey *item)
अणु
	पूर्णांक hash = item->ek_fsidtype;
	अक्षर * cp = (अक्षर*)item->ek_fsid;
	पूर्णांक len = key_len(item->ek_fsidtype);

	hash ^= hash_mem(cp, len, EXPKEY_HASHBITS);
	hash ^= hash_ptr(item->ek_client, EXPKEY_HASHBITS);
	hash &= EXPKEY_HASHMASK;
	वापस hash;
पूर्ण

अटल काष्ठा svc_expkey *
svc_expkey_lookup(काष्ठा cache_detail *cd, काष्ठा svc_expkey *item)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = svc_expkey_hash(item);

	ch = sunrpc_cache_lookup_rcu(cd, &item->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा svc_expkey, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा svc_expkey *
svc_expkey_update(काष्ठा cache_detail *cd, काष्ठा svc_expkey *new,
		  काष्ठा svc_expkey *old)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = svc_expkey_hash(new);

	ch = sunrpc_cache_update(cd, &new->h, &old->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा svc_expkey, h);
	अन्यथा
		वापस शून्य;
पूर्ण


#घोषणा	EXPORT_HASHBITS		8
#घोषणा	EXPORT_HASHMAX		(1<< EXPORT_HASHBITS)

अटल व्योम nfsd4_fslocs_मुक्त(काष्ठा nfsd4_fs_locations *fsloc)
अणु
	काष्ठा nfsd4_fs_location *locations = fsloc->locations;
	पूर्णांक i;

	अगर (!locations)
		वापस;

	क्रम (i = 0; i < fsloc->locations_count; i++) अणु
		kमुक्त(locations[i].path);
		kमुक्त(locations[i].hosts);
	पूर्ण

	kमुक्त(locations);
	fsloc->locations = शून्य;
पूर्ण

अटल पूर्णांक export_stats_init(काष्ठा export_stats *stats)
अणु
	stats->start_समय = kसमय_get_seconds();
	वापस nfsd_percpu_counters_init(stats->counter, EXP_STATS_COUNTERS_NUM);
पूर्ण

अटल व्योम export_stats_reset(काष्ठा export_stats *stats)
अणु
	nfsd_percpu_counters_reset(stats->counter, EXP_STATS_COUNTERS_NUM);
पूर्ण

अटल व्योम export_stats_destroy(काष्ठा export_stats *stats)
अणु
	nfsd_percpu_counters_destroy(stats->counter, EXP_STATS_COUNTERS_NUM);
पूर्ण

अटल व्योम svc_export_put(काष्ठा kref *ref)
अणु
	काष्ठा svc_export *exp = container_of(ref, काष्ठा svc_export, h.ref);
	path_put(&exp->ex_path);
	auth_करोमुख्य_put(exp->ex_client);
	nfsd4_fslocs_मुक्त(&exp->ex_fslocs);
	export_stats_destroy(&exp->ex_stats);
	kमुक्त(exp->ex_uuid);
	kमुक्त_rcu(exp, ex_rcu);
पूर्ण

अटल पूर्णांक svc_export_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall(cd, h);
पूर्ण

अटल व्योम svc_export_request(काष्ठा cache_detail *cd,
			       काष्ठा cache_head *h,
			       अक्षर **bpp, पूर्णांक *blen)
अणु
	/*  client path */
	काष्ठा svc_export *exp = container_of(h, काष्ठा svc_export, h);
	अक्षर *pth;

	qword_add(bpp, blen, exp->ex_client->name);
	pth = d_path(&exp->ex_path, *bpp, *blen);
	अगर (IS_ERR(pth)) अणु
		/* is this correct? */
		(*bpp)[0] = '\n';
		वापस;
	पूर्ण
	qword_add(bpp, blen, pth);
	(*bpp)[-1] = '\n';
पूर्ण

अटल काष्ठा svc_export *svc_export_update(काष्ठा svc_export *new,
					    काष्ठा svc_export *old);
अटल काष्ठा svc_export *svc_export_lookup(काष्ठा svc_export *);

अटल पूर्णांक check_export(काष्ठा path *path, पूर्णांक *flags, अचिन्हित अक्षर *uuid)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);

	/*
	 * We currently export only dirs, regular files, and (क्रम v4
	 * pseuकरोroot) symlinks.
	 */
	अगर (!S_ISसूची(inode->i_mode) &&
	    !S_ISLNK(inode->i_mode) &&
	    !S_ISREG(inode->i_mode))
		वापस -ENOTसूची;

	/*
	 * Mountd should never pass करोwn a ग_लिखोable V4ROOT export, but,
	 * just to make sure:
	 */
	अगर (*flags & NFSEXP_V4ROOT)
		*flags |= NFSEXP_READONLY;

	/* There are two requirements on a fileप्रणाली to be exportable.
	 * 1:  We must be able to identअगरy the fileप्रणाली from a number.
	 *       either a device number (so FS_REQUIRES_DEV needed)
	 *       or an FSID number (so NFSEXP_FSID or ->uuid is needed).
	 * 2:  We must be able to find an inode from a filehandle.
	 *       This means that s_export_op must be set.
	 * 3: We must not currently be on an idmapped mount.
	 */
	अगर (!(inode->i_sb->s_type->fs_flags & FS_REQUIRES_DEV) &&
	    !(*flags & NFSEXP_FSID) &&
	    uuid == शून्य) अणु
		dprपूर्णांकk("exp_export: export of non-dev fs without fsid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!inode->i_sb->s_export_op ||
	    !inode->i_sb->s_export_op->fh_to_dentry) अणु
		dprपूर्णांकk("exp_export: export of invalid fs type.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mnt_user_ns(path->mnt) != &init_user_ns) अणु
		dprपूर्णांकk("exp_export: export of idmapped mounts not yet supported.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (inode->i_sb->s_export_op->flags & EXPORT_OP_NOSUBTREECHK &&
	    !(*flags & NFSEXP_NOSUBTREECHECK)) अणु
		dprपूर्णांकk("%s: %s does not support subtree checking!\n",
			__func__, inode->i_sb->s_type->name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;

पूर्ण

#अगर_घोषित CONFIG_NFSD_V4

अटल पूर्णांक
fsloc_parse(अक्षर **mesg, अक्षर *buf, काष्ठा nfsd4_fs_locations *fsloc)
अणु
	पूर्णांक len;
	पूर्णांक migrated, i, err;

	/* more than one fsloc */
	अगर (fsloc->locations)
		वापस -EINVAL;

	/* listsize */
	err = get_uपूर्णांक(mesg, &fsloc->locations_count);
	अगर (err)
		वापस err;
	अगर (fsloc->locations_count > MAX_FS_LOCATIONS)
		वापस -EINVAL;
	अगर (fsloc->locations_count == 0)
		वापस 0;

	fsloc->locations = kसुस्मृति(fsloc->locations_count,
				   माप(काष्ठा nfsd4_fs_location),
				   GFP_KERNEL);
	अगर (!fsloc->locations)
		वापस -ENOMEM;
	क्रम (i=0; i < fsloc->locations_count; i++) अणु
		/* colon separated host list */
		err = -EINVAL;
		len = qword_get(mesg, buf, PAGE_SIZE);
		अगर (len <= 0)
			जाओ out_मुक्त_all;
		err = -ENOMEM;
		fsloc->locations[i].hosts = kstrdup(buf, GFP_KERNEL);
		अगर (!fsloc->locations[i].hosts)
			जाओ out_मुक्त_all;
		err = -EINVAL;
		/* slash separated path component list */
		len = qword_get(mesg, buf, PAGE_SIZE);
		अगर (len <= 0)
			जाओ out_मुक्त_all;
		err = -ENOMEM;
		fsloc->locations[i].path = kstrdup(buf, GFP_KERNEL);
		अगर (!fsloc->locations[i].path)
			जाओ out_मुक्त_all;
	पूर्ण
	/* migrated */
	err = get_पूर्णांक(mesg, &migrated);
	अगर (err)
		जाओ out_मुक्त_all;
	err = -EINVAL;
	अगर (migrated < 0 || migrated > 1)
		जाओ out_मुक्त_all;
	fsloc->migrated = migrated;
	वापस 0;
out_मुक्त_all:
	nfsd4_fslocs_मुक्त(fsloc);
	वापस err;
पूर्ण

अटल पूर्णांक secinfo_parse(अक्षर **mesg, अक्षर *buf, काष्ठा svc_export *exp)
अणु
	काष्ठा exp_flavor_info *f;
	u32 listsize;
	पूर्णांक err;

	/* more than one secinfo */
	अगर (exp->ex_nflavors)
		वापस -EINVAL;

	err = get_uपूर्णांक(mesg, &listsize);
	अगर (err)
		वापस err;
	अगर (listsize > MAX_SECINFO_LIST)
		वापस -EINVAL;

	क्रम (f = exp->ex_flavors; f < exp->ex_flavors + listsize; f++) अणु
		err = get_uपूर्णांक(mesg, &f->pseuकरोflavor);
		अगर (err)
			वापस err;
		/*
		 * XXX: It would be nice to also check whether this
		 * pseuकरोflavor is supported, so we can discover the
		 * problem at export समय instead of when a client fails
		 * to authenticate.
		 */
		err = get_uपूर्णांक(mesg, &f->flags);
		अगर (err)
			वापस err;
		/* Only some flags are allowed to dअगरfer between flavors: */
		अगर (~NFSEXP_SECINFO_FLAGS & (f->flags ^ exp->ex_flags))
			वापस -EINVAL;
	पूर्ण
	exp->ex_nflavors = listsize;
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_NFSD_V4 */
अटल अंतरभूत पूर्णांक
fsloc_parse(अक्षर **mesg, अक्षर *buf, काष्ठा nfsd4_fs_locations *fsloc)अणुवापस 0;पूर्ण
अटल अंतरभूत पूर्णांक
secinfo_parse(अक्षर **mesg, अक्षर *buf, काष्ठा svc_export *exp) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
nfsd_uuid_parse(अक्षर **mesg, अक्षर *buf, अचिन्हित अक्षर **puuid)
अणु
	पूर्णांक len;

	/* more than one uuid */
	अगर (*puuid)
		वापस -EINVAL;

	/* expect a 16 byte uuid encoded as \षXXXX... */
	len = qword_get(mesg, buf, PAGE_SIZE);
	अगर (len != EX_UUID_LEN)
		वापस -EINVAL;

	*puuid = kmemdup(buf, EX_UUID_LEN, GFP_KERNEL);
	अगर (*puuid == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक svc_export_parse(काष्ठा cache_detail *cd, अक्षर *mesg, पूर्णांक mlen)
अणु
	/* client path expiry [flags anonuid anongid fsid] */
	अक्षर *buf;
	पूर्णांक len;
	पूर्णांक err;
	काष्ठा auth_करोमुख्य *करोm = शून्य;
	काष्ठा svc_export exp = अणुपूर्ण, *expp;
	पूर्णांक an_पूर्णांक;

	अगर (mesg[mlen-1] != '\n')
		वापस -EINVAL;
	mesg[mlen-1] = 0;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* client */
	err = -EINVAL;
	len = qword_get(&mesg, buf, PAGE_SIZE);
	अगर (len <= 0)
		जाओ out;

	err = -ENOENT;
	करोm = auth_करोमुख्य_find(buf);
	अगर (!करोm)
		जाओ out;

	/* path */
	err = -EINVAL;
	अगर ((len = qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		जाओ out1;

	err = kern_path(buf, 0, &exp.ex_path);
	अगर (err)
		जाओ out1;

	exp.ex_client = करोm;
	exp.cd = cd;
	exp.ex_devid_map = शून्य;

	/* expiry */
	err = -EINVAL;
	exp.h.expiry_समय = get_expiry(&mesg);
	अगर (exp.h.expiry_समय == 0)
		जाओ out3;

	/* flags */
	err = get_पूर्णांक(&mesg, &an_पूर्णांक);
	अगर (err == -ENOENT) अणु
		err = 0;
		set_bit(CACHE_NEGATIVE, &exp.h.flags);
	पूर्ण अन्यथा अणु
		अगर (err || an_पूर्णांक < 0)
			जाओ out3;
		exp.ex_flags= an_पूर्णांक;
	
		/* anon uid */
		err = get_पूर्णांक(&mesg, &an_पूर्णांक);
		अगर (err)
			जाओ out3;
		exp.ex_anon_uid= make_kuid(current_user_ns(), an_पूर्णांक);

		/* anon gid */
		err = get_पूर्णांक(&mesg, &an_पूर्णांक);
		अगर (err)
			जाओ out3;
		exp.ex_anon_gid= make_kgid(current_user_ns(), an_पूर्णांक);

		/* fsid */
		err = get_पूर्णांक(&mesg, &an_पूर्णांक);
		अगर (err)
			जाओ out3;
		exp.ex_fsid = an_पूर्णांक;

		जबतक ((len = qword_get(&mesg, buf, PAGE_SIZE)) > 0) अणु
			अगर (म_भेद(buf, "fsloc") == 0)
				err = fsloc_parse(&mesg, buf, &exp.ex_fslocs);
			अन्यथा अगर (म_भेद(buf, "uuid") == 0)
				err = nfsd_uuid_parse(&mesg, buf, &exp.ex_uuid);
			अन्यथा अगर (म_भेद(buf, "secinfo") == 0)
				err = secinfo_parse(&mesg, buf, &exp);
			अन्यथा
				/* quietly ignore unknown words and anything
				 * following. Newer user-space can try to set
				 * new values, then see what the result was.
				 */
				अवरोध;
			अगर (err)
				जाओ out4;
		पूर्ण

		err = check_export(&exp.ex_path, &exp.ex_flags, exp.ex_uuid);
		अगर (err)
			जाओ out4;
		/*
		 * No poपूर्णांक caching this अगर it would immediately expire.
		 * Also, this protects exportfs's dummy export from the
		 * anon_uid/anon_gid checks:
		 */
		अगर (exp.h.expiry_समय < seconds_since_boot())
			जाओ out4;
		/*
		 * For some reason exportfs has been passing करोwn an
		 * invalid (-1) uid & gid on the "dummy" export which it
		 * uses to test export support.  To make sure exportfs
		 * sees errors from check_export we thereक्रमe need to
		 * delay these checks till after check_export:
		 */
		err = -EINVAL;
		अगर (!uid_valid(exp.ex_anon_uid))
			जाओ out4;
		अगर (!gid_valid(exp.ex_anon_gid))
			जाओ out4;
		err = 0;

		nfsd4_setup_layout_type(&exp);
	पूर्ण

	expp = svc_export_lookup(&exp);
	अगर (!expp) अणु
		err = -ENOMEM;
		जाओ out4;
	पूर्ण
	expp = svc_export_update(&exp, expp);
	अगर (expp) अणु
		trace_nfsd_export_update(expp);
		cache_flush();
		exp_put(expp);
	पूर्ण अन्यथा
		err = -ENOMEM;
out4:
	nfsd4_fslocs_मुक्त(&exp.ex_fslocs);
	kमुक्त(exp.ex_uuid);
out3:
	path_put(&exp.ex_path);
out1:
	auth_करोमुख्य_put(करोm);
out:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल व्योम exp_flags(काष्ठा seq_file *m, पूर्णांक flag, पूर्णांक fsid,
		kuid_t anonu, kgid_t anong, काष्ठा nfsd4_fs_locations *fslocs);
अटल व्योम show_secinfo(काष्ठा seq_file *m, काष्ठा svc_export *exp);

अटल पूर्णांक is_export_stats_file(काष्ठा seq_file *m)
अणु
	/*
	 * The export_stats file uses the same ops as the exports file.
	 * We use the file's name to determine the reported info per export.
	 * There is no नाम in nsfdfs, so d_name.name is stable.
	 */
	वापस !म_भेद(m->file->f_path.dentry->d_name.name, "export_stats");
पूर्ण

अटल पूर्णांक svc_export_show(काष्ठा seq_file *m,
			   काष्ठा cache_detail *cd,
			   काष्ठा cache_head *h)
अणु
	काष्ठा svc_export *exp;
	bool export_stats = is_export_stats_file(m);

	अगर (h == शून्य) अणु
		अगर (export_stats)
			seq_माला_दो(m, "#path domain start-time\n#\tstats\n");
		अन्यथा
			seq_माला_दो(m, "#path domain(flags)\n");
		वापस 0;
	पूर्ण
	exp = container_of(h, काष्ठा svc_export, h);
	seq_path(m, &exp->ex_path, " \t\n\\");
	seq_अ_दो(m, '\t');
	seq_escape(m, exp->ex_client->name, " \t\n\\");
	अगर (export_stats) अणु
		seq_म_लिखो(m, "\t%lld\n", exp->ex_stats.start_समय);
		seq_म_लिखो(m, "\tfh_stale: %lld\n",
			   percpu_counter_sum_positive(&exp->ex_stats.counter[EXP_STATS_FH_STALE]));
		seq_म_लिखो(m, "\tio_read: %lld\n",
			   percpu_counter_sum_positive(&exp->ex_stats.counter[EXP_STATS_IO_READ]));
		seq_म_लिखो(m, "\tio_write: %lld\n",
			   percpu_counter_sum_positive(&exp->ex_stats.counter[EXP_STATS_IO_WRITE]));
		seq_अ_दो(m, '\n');
		वापस 0;
	पूर्ण
	seq_अ_दो(m, '(');
	अगर (test_bit(CACHE_VALID, &h->flags) &&
	    !test_bit(CACHE_NEGATIVE, &h->flags)) अणु
		exp_flags(m, exp->ex_flags, exp->ex_fsid,
			  exp->ex_anon_uid, exp->ex_anon_gid, &exp->ex_fslocs);
		अगर (exp->ex_uuid) अणु
			पूर्णांक i;
			seq_माला_दो(m, ",uuid=");
			क्रम (i = 0; i < EX_UUID_LEN; i++) अणु
				अगर ((i&3) == 0 && i)
					seq_अ_दो(m, ':');
				seq_म_लिखो(m, "%02x", exp->ex_uuid[i]);
			पूर्ण
		पूर्ण
		show_secinfo(m, exp);
	पूर्ण
	seq_माला_दो(m, ")\n");
	वापस 0;
पूर्ण
अटल पूर्णांक svc_export_match(काष्ठा cache_head *a, काष्ठा cache_head *b)
अणु
	काष्ठा svc_export *orig = container_of(a, काष्ठा svc_export, h);
	काष्ठा svc_export *new = container_of(b, काष्ठा svc_export, h);
	वापस orig->ex_client == new->ex_client &&
		path_equal(&orig->ex_path, &new->ex_path);
पूर्ण

अटल व्योम svc_export_init(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा svc_export *new = container_of(cnew, काष्ठा svc_export, h);
	काष्ठा svc_export *item = container_of(citem, काष्ठा svc_export, h);

	kref_get(&item->ex_client->ref);
	new->ex_client = item->ex_client;
	new->ex_path = item->ex_path;
	path_get(&item->ex_path);
	new->ex_fslocs.locations = शून्य;
	new->ex_fslocs.locations_count = 0;
	new->ex_fslocs.migrated = 0;
	new->ex_layout_types = 0;
	new->ex_uuid = शून्य;
	new->cd = item->cd;
	export_stats_reset(&new->ex_stats);
पूर्ण

अटल व्योम export_update(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा svc_export *new = container_of(cnew, काष्ठा svc_export, h);
	काष्ठा svc_export *item = container_of(citem, काष्ठा svc_export, h);
	पूर्णांक i;

	new->ex_flags = item->ex_flags;
	new->ex_anon_uid = item->ex_anon_uid;
	new->ex_anon_gid = item->ex_anon_gid;
	new->ex_fsid = item->ex_fsid;
	new->ex_devid_map = item->ex_devid_map;
	item->ex_devid_map = शून्य;
	new->ex_uuid = item->ex_uuid;
	item->ex_uuid = शून्य;
	new->ex_fslocs.locations = item->ex_fslocs.locations;
	item->ex_fslocs.locations = शून्य;
	new->ex_fslocs.locations_count = item->ex_fslocs.locations_count;
	item->ex_fslocs.locations_count = 0;
	new->ex_fslocs.migrated = item->ex_fslocs.migrated;
	item->ex_fslocs.migrated = 0;
	new->ex_layout_types = item->ex_layout_types;
	new->ex_nflavors = item->ex_nflavors;
	क्रम (i = 0; i < MAX_SECINFO_LIST; i++) अणु
		new->ex_flavors[i] = item->ex_flavors[i];
	पूर्ण
पूर्ण

अटल काष्ठा cache_head *svc_export_alloc(व्योम)
अणु
	काष्ठा svc_export *i = kदो_स्मृति(माप(*i), GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	अगर (export_stats_init(&i->ex_stats)) अणु
		kमुक्त(i);
		वापस शून्य;
	पूर्ण

	वापस &i->h;
पूर्ण

अटल स्थिर काष्ठा cache_detail svc_export_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= EXPORT_HASHMAX,
	.name		= "nfsd.export",
	.cache_put	= svc_export_put,
	.cache_upcall	= svc_export_upcall,
	.cache_request	= svc_export_request,
	.cache_parse	= svc_export_parse,
	.cache_show	= svc_export_show,
	.match		= svc_export_match,
	.init		= svc_export_init,
	.update		= export_update,
	.alloc		= svc_export_alloc,
पूर्ण;

अटल पूर्णांक
svc_export_hash(काष्ठा svc_export *exp)
अणु
	पूर्णांक hash;

	hash = hash_ptr(exp->ex_client, EXPORT_HASHBITS);
	hash ^= hash_ptr(exp->ex_path.dentry, EXPORT_HASHBITS);
	hash ^= hash_ptr(exp->ex_path.mnt, EXPORT_HASHBITS);
	वापस hash;
पूर्ण

अटल काष्ठा svc_export *
svc_export_lookup(काष्ठा svc_export *exp)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = svc_export_hash(exp);

	ch = sunrpc_cache_lookup_rcu(exp->cd, &exp->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा svc_export, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा svc_export *
svc_export_update(काष्ठा svc_export *new, काष्ठा svc_export *old)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = svc_export_hash(old);

	ch = sunrpc_cache_update(old->cd, &new->h, &old->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा svc_export, h);
	अन्यथा
		वापस शून्य;
पूर्ण


अटल काष्ठा svc_expkey *
exp_find_key(काष्ठा cache_detail *cd, काष्ठा auth_करोमुख्य *clp, पूर्णांक fsid_type,
	     u32 *fsidv, काष्ठा cache_req *reqp)
अणु
	काष्ठा svc_expkey key, *ek;
	पूर्णांक err;
	
	अगर (!clp)
		वापस ERR_PTR(-ENOENT);

	key.ek_client = clp;
	key.ek_fsidtype = fsid_type;
	स_नकल(key.ek_fsid, fsidv, key_len(fsid_type));

	ek = svc_expkey_lookup(cd, &key);
	अगर (ek == शून्य)
		वापस ERR_PTR(-ENOMEM);
	err = cache_check(cd, &ek->h, reqp);
	अगर (err) अणु
		trace_nfsd_exp_find_key(&key, err);
		वापस ERR_PTR(err);
	पूर्ण
	वापस ek;
पूर्ण

अटल काष्ठा svc_export *
exp_get_by_name(काष्ठा cache_detail *cd, काष्ठा auth_करोमुख्य *clp,
		स्थिर काष्ठा path *path, काष्ठा cache_req *reqp)
अणु
	काष्ठा svc_export *exp, key;
	पूर्णांक err;

	अगर (!clp)
		वापस ERR_PTR(-ENOENT);

	key.ex_client = clp;
	key.ex_path = *path;
	key.cd = cd;

	exp = svc_export_lookup(&key);
	अगर (exp == शून्य)
		वापस ERR_PTR(-ENOMEM);
	err = cache_check(cd, &exp->h, reqp);
	अगर (err) अणु
		trace_nfsd_exp_get_by_name(&key, err);
		वापस ERR_PTR(err);
	पूर्ण
	वापस exp;
पूर्ण

/*
 * Find the export entry क्रम a given dentry.
 */
अटल काष्ठा svc_export *
exp_parent(काष्ठा cache_detail *cd, काष्ठा auth_करोमुख्य *clp, काष्ठा path *path)
अणु
	काष्ठा dentry *saved = dget(path->dentry);
	काष्ठा svc_export *exp = exp_get_by_name(cd, clp, path, शून्य);

	जबतक (PTR_ERR(exp) == -ENOENT && !IS_ROOT(path->dentry)) अणु
		काष्ठा dentry *parent = dget_parent(path->dentry);
		dput(path->dentry);
		path->dentry = parent;
		exp = exp_get_by_name(cd, clp, path, शून्य);
	पूर्ण
	dput(path->dentry);
	path->dentry = saved;
	वापस exp;
पूर्ण



/*
 * Obtain the root fh on behalf of a client.
 * This could be करोne in user space, but I feel that it adds some safety
 * since its harder to fool a kernel module than a user space program.
 */
पूर्णांक
exp_rootfh(काष्ठा net *net, काष्ठा auth_करोमुख्य *clp, अक्षर *name,
	   काष्ठा knfsd_fh *f, पूर्णांक maxsize)
अणु
	काष्ठा svc_export	*exp;
	काष्ठा path		path;
	काष्ठा inode		*inode;
	काष्ठा svc_fh		fh;
	पूर्णांक			err;
	काष्ठा nfsd_net		*nn = net_generic(net, nfsd_net_id);
	काष्ठा cache_detail	*cd = nn->svc_export_cache;

	err = -EPERM;
	/* NB: we probably ought to check that it's NUL-terminated */
	अगर (kern_path(name, 0, &path)) अणु
		prपूर्णांकk("nfsd: exp_rootfh path not found %s", name);
		वापस err;
	पूर्ण
	inode = d_inode(path.dentry);

	dprपूर्णांकk("nfsd: exp_rootfh(%s [%p] %s:%s/%ld)\n",
		 name, path.dentry, clp->name,
		 inode->i_sb->s_id, inode->i_ino);
	exp = exp_parent(cd, clp, &path);
	अगर (IS_ERR(exp)) अणु
		err = PTR_ERR(exp);
		जाओ out;
	पूर्ण

	/*
	 * fh must be initialized beक्रमe calling fh_compose
	 */
	fh_init(&fh, maxsize);
	अगर (fh_compose(&fh, exp, path.dentry, शून्य))
		err = -EINVAL;
	अन्यथा
		err = 0;
	स_नकल(f, &fh.fh_handle, माप(काष्ठा knfsd_fh));
	fh_put(&fh);
	exp_put(exp);
out:
	path_put(&path);
	वापस err;
पूर्ण

अटल काष्ठा svc_export *exp_find(काष्ठा cache_detail *cd,
				   काष्ठा auth_करोमुख्य *clp, पूर्णांक fsid_type,
				   u32 *fsidv, काष्ठा cache_req *reqp)
अणु
	काष्ठा svc_export *exp;
	काष्ठा nfsd_net *nn = net_generic(cd->net, nfsd_net_id);
	काष्ठा svc_expkey *ek = exp_find_key(nn->svc_expkey_cache, clp, fsid_type, fsidv, reqp);
	अगर (IS_ERR(ek))
		वापस ERR_CAST(ek);

	exp = exp_get_by_name(cd, clp, &ek->ek_path, reqp);
	cache_put(&ek->h, nn->svc_expkey_cache);

	अगर (IS_ERR(exp))
		वापस ERR_CAST(exp);
	वापस exp;
पूर्ण

__be32 check_nfsd_access(काष्ठा svc_export *exp, काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा exp_flavor_info *f;
	काष्ठा exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;

	/* legacy gss-only clients are always OK: */
	अगर (exp->ex_client == rqstp->rq_gssclient)
		वापस 0;
	/* ip-address based client; check sec= export option: */
	क्रम (f = exp->ex_flavors; f < end; f++) अणु
		अगर (f->pseuकरोflavor == rqstp->rq_cred.cr_flavor)
			वापस 0;
	पूर्ण
	/* शेषs in असलence of sec= options: */
	अगर (exp->ex_nflavors == 0) अणु
		अगर (rqstp->rq_cred.cr_flavor == RPC_AUTH_शून्य ||
		    rqstp->rq_cred.cr_flavor == RPC_AUTH_UNIX)
			वापस 0;
	पूर्ण

	/* If the compound op contains a spo_must_allowed op,
	 * it will be sent with पूर्णांकegrity/protection which
	 * will have to be expressly allowed on mounts that
	 * करोn't support it
	 */

	अगर (nfsd4_spo_must_allow(rqstp))
		वापस 0;

	वापस rqstp->rq_vers < 4 ? nfserr_acces : nfserr_wrongsec;
पूर्ण

/*
 * Uses rq_client and rq_gssclient to find an export; uses rq_client (an
 * auth_unix client) अगर it's available and has secinfo inक्रमmation;
 * otherwise, will try to use rq_gssclient.
 *
 * Called from functions that handle requests; functions that करो work on
 * behalf of mountd are passed a single client name to use, and should
 * use exp_get_by_name() or exp_find().
 */
काष्ठा svc_export *
rqst_exp_get_by_name(काष्ठा svc_rqst *rqstp, काष्ठा path *path)
अणु
	काष्ठा svc_export *gssexp, *exp = ERR_PTR(-ENOENT);
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा cache_detail *cd = nn->svc_export_cache;

	अगर (rqstp->rq_client == शून्य)
		जाओ gss;

	/* First try the auth_unix client: */
	exp = exp_get_by_name(cd, rqstp->rq_client, path, &rqstp->rq_chandle);
	अगर (PTR_ERR(exp) == -ENOENT)
		जाओ gss;
	अगर (IS_ERR(exp))
		वापस exp;
	/* If it has secinfo, assume there are no gss/... clients */
	अगर (exp->ex_nflavors > 0)
		वापस exp;
gss:
	/* Otherwise, try falling back on gss client */
	अगर (rqstp->rq_gssclient == शून्य)
		वापस exp;
	gssexp = exp_get_by_name(cd, rqstp->rq_gssclient, path, &rqstp->rq_chandle);
	अगर (PTR_ERR(gssexp) == -ENOENT)
		वापस exp;
	अगर (!IS_ERR(exp))
		exp_put(exp);
	वापस gssexp;
पूर्ण

काष्ठा svc_export *
rqst_exp_find(काष्ठा svc_rqst *rqstp, पूर्णांक fsid_type, u32 *fsidv)
अणु
	काष्ठा svc_export *gssexp, *exp = ERR_PTR(-ENOENT);
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा cache_detail *cd = nn->svc_export_cache;

	अगर (rqstp->rq_client == शून्य)
		जाओ gss;

	/* First try the auth_unix client: */
	exp = exp_find(cd, rqstp->rq_client, fsid_type,
		       fsidv, &rqstp->rq_chandle);
	अगर (PTR_ERR(exp) == -ENOENT)
		जाओ gss;
	अगर (IS_ERR(exp))
		वापस exp;
	/* If it has secinfo, assume there are no gss/... clients */
	अगर (exp->ex_nflavors > 0)
		वापस exp;
gss:
	/* Otherwise, try falling back on gss client */
	अगर (rqstp->rq_gssclient == शून्य)
		वापस exp;
	gssexp = exp_find(cd, rqstp->rq_gssclient, fsid_type, fsidv,
						&rqstp->rq_chandle);
	अगर (PTR_ERR(gssexp) == -ENOENT)
		वापस exp;
	अगर (!IS_ERR(exp))
		exp_put(exp);
	वापस gssexp;
पूर्ण

काष्ठा svc_export *
rqst_exp_parent(काष्ठा svc_rqst *rqstp, काष्ठा path *path)
अणु
	काष्ठा dentry *saved = dget(path->dentry);
	काष्ठा svc_export *exp = rqst_exp_get_by_name(rqstp, path);

	जबतक (PTR_ERR(exp) == -ENOENT && !IS_ROOT(path->dentry)) अणु
		काष्ठा dentry *parent = dget_parent(path->dentry);
		dput(path->dentry);
		path->dentry = parent;
		exp = rqst_exp_get_by_name(rqstp, path);
	पूर्ण
	dput(path->dentry);
	path->dentry = saved;
	वापस exp;
पूर्ण

काष्ठा svc_export *rqst_find_fsidzero_export(काष्ठा svc_rqst *rqstp)
अणु
	u32 fsidv[2];

	mk_fsid(FSID_NUM, fsidv, 0, 0, 0, शून्य);

	वापस rqst_exp_find(rqstp, FSID_NUM, fsidv);
पूर्ण

/*
 * Called when we need the filehandle क्रम the root of the pseuकरोfs,
 * क्रम a given NFSv4 client.   The root is defined to be the
 * export poपूर्णांक with fsid==0
 */
__be32
exp_pseuकरोroot(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp)
अणु
	काष्ठा svc_export *exp;
	__be32 rv;

	exp = rqst_find_fsidzero_export(rqstp);
	अगर (IS_ERR(exp))
		वापस nfsत्रुटि_सं(PTR_ERR(exp));
	rv = fh_compose(fhp, exp, exp->ex_path.dentry, शून्य);
	exp_put(exp);
	वापस rv;
पूर्ण

अटल काष्ठा flags अणु
	पूर्णांक flag;
	अक्षर *name[2];
पूर्ण expflags[] = अणु
	अणु NFSEXP_READONLY, अणु"ro", "rw"पूर्णपूर्ण,
	अणु NFSEXP_INSECURE_PORT, अणु"insecure", ""पूर्णपूर्ण,
	अणु NFSEXP_ROOTSQUASH, अणु"root_squash", "no_root_squash"पूर्णपूर्ण,
	अणु NFSEXP_ALLSQUASH, अणु"all_squash", ""पूर्णपूर्ण,
	अणु NFSEXP_ASYNC, अणु"async", "sync"पूर्णपूर्ण,
	अणु NFSEXP_GATHERED_WRITES, अणु"wdelay", "no_wdelay"पूर्णपूर्ण,
	अणु NFSEXP_NOREADसूचीPLUS, अणु"nordirplus", ""पूर्णपूर्ण,
	अणु NFSEXP_NOHIDE, अणु"nohide", ""पूर्णपूर्ण,
	अणु NFSEXP_CROSSMOUNT, अणु"crossmnt", ""पूर्णपूर्ण,
	अणु NFSEXP_NOSUBTREECHECK, अणु"no_subtree_check", ""पूर्णपूर्ण,
	अणु NFSEXP_NOAUTHNLM, अणु"insecure_locks", ""पूर्णपूर्ण,
	अणु NFSEXP_V4ROOT, अणु"v4root", ""पूर्णपूर्ण,
	अणु NFSEXP_PNFS, अणु"pnfs", ""पूर्णपूर्ण,
	अणु NFSEXP_SECURITY_LABEL, अणु"security_label", ""पूर्णपूर्ण,
	अणु 0, अणु"", ""पूर्णपूर्ण
पूर्ण;

अटल व्योम show_expflags(काष्ठा seq_file *m, पूर्णांक flags, पूर्णांक mask)
अणु
	काष्ठा flags *flg;
	पूर्णांक state, first = 0;

	क्रम (flg = expflags; flg->flag; flg++) अणु
		अगर (flg->flag & ~mask)
			जारी;
		state = (flg->flag & flags) ? 0 : 1;
		अगर (*flg->name[state])
			seq_म_लिखो(m, "%s%s", first++?",":"", flg->name[state]);
	पूर्ण
पूर्ण

अटल व्योम show_secinfo_flags(काष्ठा seq_file *m, पूर्णांक flags)
अणु
	seq_म_लिखो(m, ",");
	show_expflags(m, flags, NFSEXP_SECINFO_FLAGS);
पूर्ण

अटल bool secinfo_flags_equal(पूर्णांक f, पूर्णांक g)
अणु
	f &= NFSEXP_SECINFO_FLAGS;
	g &= NFSEXP_SECINFO_FLAGS;
	वापस f == g;
पूर्ण

अटल पूर्णांक show_secinfo_run(काष्ठा seq_file *m, काष्ठा exp_flavor_info **fp, काष्ठा exp_flavor_info *end)
अणु
	पूर्णांक flags;

	flags = (*fp)->flags;
	seq_म_लिखो(m, ",sec=%d", (*fp)->pseuकरोflavor);
	(*fp)++;
	जबतक (*fp != end && secinfo_flags_equal(flags, (*fp)->flags)) अणु
		seq_म_लिखो(m, ":%d", (*fp)->pseuकरोflavor);
		(*fp)++;
	पूर्ण
	वापस flags;
पूर्ण

अटल व्योम show_secinfo(काष्ठा seq_file *m, काष्ठा svc_export *exp)
अणु
	काष्ठा exp_flavor_info *f;
	काष्ठा exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;
	पूर्णांक flags;

	अगर (exp->ex_nflavors == 0)
		वापस;
	f = exp->ex_flavors;
	flags = show_secinfo_run(m, &f, end);
	अगर (!secinfo_flags_equal(flags, exp->ex_flags))
		show_secinfo_flags(m, flags);
	जबतक (f != end) अणु
		flags = show_secinfo_run(m, &f, end);
		show_secinfo_flags(m, flags);
	पूर्ण
पूर्ण

अटल व्योम exp_flags(काष्ठा seq_file *m, पूर्णांक flag, पूर्णांक fsid,
		kuid_t anonu, kgid_t anong, काष्ठा nfsd4_fs_locations *fsloc)
अणु
	काष्ठा user_namespace *userns = m->file->f_cred->user_ns;

	show_expflags(m, flag, NFSEXP_ALLFLAGS);
	अगर (flag & NFSEXP_FSID)
		seq_म_लिखो(m, ",fsid=%d", fsid);
	अगर (!uid_eq(anonu, make_kuid(userns, (uid_t)-2)) &&
	    !uid_eq(anonu, make_kuid(userns, 0x10000-2)))
		seq_म_लिखो(m, ",anonuid=%u", from_kuid_munged(userns, anonu));
	अगर (!gid_eq(anong, make_kgid(userns, (gid_t)-2)) &&
	    !gid_eq(anong, make_kgid(userns, 0x10000-2)))
		seq_म_लिखो(m, ",anongid=%u", from_kgid_munged(userns, anong));
	अगर (fsloc && fsloc->locations_count > 0) अणु
		अक्षर *loctype = (fsloc->migrated) ? "refer" : "replicas";
		पूर्णांक i;

		seq_म_लिखो(m, ",%s=", loctype);
		seq_escape(m, fsloc->locations[0].path, ",;@ \t\n\\");
		seq_अ_दो(m, '@');
		seq_escape(m, fsloc->locations[0].hosts, ",;@ \t\n\\");
		क्रम (i = 1; i < fsloc->locations_count; i++) अणु
			seq_अ_दो(m, ';');
			seq_escape(m, fsloc->locations[i].path, ",;@ \t\n\\");
			seq_अ_दो(m, '@');
			seq_escape(m, fsloc->locations[i].hosts, ",;@ \t\n\\");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक e_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा cache_head *cp = p;
	काष्ठा svc_export *exp = container_of(cp, काष्ठा svc_export, h);
	काष्ठा cache_detail *cd = m->निजी;
	bool export_stats = is_export_stats_file(m);

	अगर (p == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "# Version 1.1\n");
		अगर (export_stats)
			seq_माला_दो(m, "# Path Client Start-time\n#\tStats\n");
		अन्यथा
			seq_माला_दो(m, "# Path Client(Flags) # IPs\n");
		वापस 0;
	पूर्ण

	exp_get(exp);
	अगर (cache_check(cd, &exp->h, शून्य))
		वापस 0;
	exp_put(exp);
	वापस svc_export_show(m, cd, cp);
पूर्ण

स्थिर काष्ठा seq_operations nfs_exports_op = अणु
	.start	= cache_seq_start_rcu,
	.next	= cache_seq_next_rcu,
	.stop	= cache_seq_stop_rcu,
	.show	= e_show,
पूर्ण;

/*
 * Initialize the exports module.
 */
पूर्णांक
nfsd_export_init(काष्ठा net *net)
अणु
	पूर्णांक rv;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprपूर्णांकk("nfsd: initializing export module (net: %x).\n", net->ns.inum);

	nn->svc_export_cache = cache_create_net(&svc_export_cache_ढाँचा, net);
	अगर (IS_ERR(nn->svc_export_cache))
		वापस PTR_ERR(nn->svc_export_cache);
	rv = cache_रेजिस्टर_net(nn->svc_export_cache, net);
	अगर (rv)
		जाओ destroy_export_cache;

	nn->svc_expkey_cache = cache_create_net(&svc_expkey_cache_ढाँचा, net);
	अगर (IS_ERR(nn->svc_expkey_cache)) अणु
		rv = PTR_ERR(nn->svc_expkey_cache);
		जाओ unरेजिस्टर_export_cache;
	पूर्ण
	rv = cache_रेजिस्टर_net(nn->svc_expkey_cache, net);
	अगर (rv)
		जाओ destroy_expkey_cache;
	वापस 0;

destroy_expkey_cache:
	cache_destroy_net(nn->svc_expkey_cache, net);
unरेजिस्टर_export_cache:
	cache_unरेजिस्टर_net(nn->svc_export_cache, net);
destroy_export_cache:
	cache_destroy_net(nn->svc_export_cache, net);
	वापस rv;
पूर्ण

/*
 * Flush exports table - called when last nfsd thपढ़ो is समाप्तed
 */
व्योम
nfsd_export_flush(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	cache_purge(nn->svc_expkey_cache);
	cache_purge(nn->svc_export_cache);
पूर्ण

/*
 * Shutकरोwn the exports module.
 */
व्योम
nfsd_export_shutकरोwn(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprपूर्णांकk("nfsd: shutting down export module (net: %x).\n", net->ns.inum);

	cache_unरेजिस्टर_net(nn->svc_expkey_cache, net);
	cache_unरेजिस्टर_net(nn->svc_export_cache, net);
	cache_destroy_net(nn->svc_expkey_cache, net);
	cache_destroy_net(nn->svc_export_cache, net);
	svcauth_unix_purge(net);

	dprपूर्णांकk("nfsd: export shutdown complete (net: %x).\n", net->ns.inum);
पूर्ण
