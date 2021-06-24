<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/nfs/dir.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  nfs directory handling functions
 *
 * 10 Apr 1996	Added silly नाम क्रम unlink	--okir
 * 28 Sep 1996	Improved directory cache --okir
 * 23 Aug 1997  Claus Heine claus@momo.math.rwth-aachen.de 
 *              Re-implemented silly नाम क्रम unlink, newly implemented
 *              silly नाम क्रम nfs_नाम() following the suggestions
 *              of Olaf Kirch (okir) found in this file.
 *              Following Linus comments on my original hack, this version
 *              depends only on the dcache stuff and करोesn't touch the inode
 *              layer (iput() and मित्रs).
 *  6 Jun 1999	Cache सूची_पढ़ो lookups in the page cache. -DaveM
 */

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/swap.h>
#समावेश <linux/sched.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/xattr.h>

#समावेश "delegation.h"
#समावेश "iostat.h"
#समावेश "internal.h"
#समावेश "fscache.h"

#समावेश "nfstrace.h"

/* #घोषणा NFS_DEBUG_VERBOSE 1 */

अटल पूर्णांक nfs_सूची_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक nfs_बंद_सूची(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक nfs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
अटल पूर्णांक nfs_fsync_dir(काष्ठा file *, loff_t, loff_t, पूर्णांक);
अटल loff_t nfs_llseek_dir(काष्ठा file *, loff_t, पूर्णांक);
अटल व्योम nfs_सूची_पढ़ो_clear_array(काष्ठा page*);

स्थिर काष्ठा file_operations nfs_dir_operations = अणु
	.llseek		= nfs_llseek_dir,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= nfs_सूची_पढ़ो,
	.खोलो		= nfs_सूची_खोलो,
	.release	= nfs_बंद_सूची,
	.fsync		= nfs_fsync_dir,
पूर्ण;

स्थिर काष्ठा address_space_operations nfs_dir_aops = अणु
	.मुक्तpage = nfs_सूची_पढ़ो_clear_array,
पूर्ण;

अटल काष्ठा nfs_खोलो_dir_context *alloc_nfs_खोलो_dir_context(काष्ठा inode *dir)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(dir);
	काष्ठा nfs_खोलो_dir_context *ctx;
	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (ctx != शून्य) अणु
		ctx->duped = 0;
		ctx->attr_gencount = nfsi->attr_gencount;
		ctx->dir_cookie = 0;
		ctx->dup_cookie = 0;
		spin_lock(&dir->i_lock);
		अगर (list_empty(&nfsi->खोलो_files) &&
		    (nfsi->cache_validity & NFS_INO_DATA_INVAL_DEFER))
			nfs_set_cache_invalid(dir,
					      NFS_INO_INVALID_DATA |
						      NFS_INO_REVAL_FORCED);
		list_add(&ctx->list, &nfsi->खोलो_files);
		spin_unlock(&dir->i_lock);
		वापस ctx;
	पूर्ण
	वापस  ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम put_nfs_खोलो_dir_context(काष्ठा inode *dir, काष्ठा nfs_खोलो_dir_context *ctx)
अणु
	spin_lock(&dir->i_lock);
	list_del(&ctx->list);
	spin_unlock(&dir->i_lock);
	kमुक्त(ctx);
पूर्ण

/*
 * Open file
 */
अटल पूर्णांक
nfs_सूची_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक res = 0;
	काष्ठा nfs_खोलो_dir_context *ctx;

	dfprपूर्णांकk(खाता, "NFS: open dir(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);

	ctx = alloc_nfs_खोलो_dir_context(inode);
	अगर (IS_ERR(ctx)) अणु
		res = PTR_ERR(ctx);
		जाओ out;
	पूर्ण
	filp->निजी_data = ctx;
out:
	वापस res;
पूर्ण

अटल पूर्णांक
nfs_बंद_सूची(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	put_nfs_खोलो_dir_context(file_inode(filp), filp->निजी_data);
	वापस 0;
पूर्ण

काष्ठा nfs_cache_array_entry अणु
	u64 cookie;
	u64 ino;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक name_len;
	अचिन्हित अक्षर d_type;
पूर्ण;

काष्ठा nfs_cache_array अणु
	u64 last_cookie;
	अचिन्हित पूर्णांक size;
	अचिन्हित अक्षर page_full : 1,
		      page_is_eof : 1,
		      cookies_are_ordered : 1;
	काष्ठा nfs_cache_array_entry array[];
पूर्ण;

काष्ठा nfs_सूची_पढ़ो_descriptor अणु
	काष्ठा file	*file;
	काष्ठा page	*page;
	काष्ठा dir_context *ctx;
	pgoff_t		page_index;
	u64		dir_cookie;
	u64		last_cookie;
	u64		dup_cookie;
	loff_t		current_index;
	loff_t		prev_index;

	__be32		verf[NFS_सूची_VERIFIER_SIZE];
	अचिन्हित दीर्घ	dir_verअगरier;
	अचिन्हित दीर्घ	बारtamp;
	अचिन्हित दीर्घ	gencount;
	अचिन्हित दीर्घ	attr_gencount;
	अचिन्हित पूर्णांक	cache_entry_index;
	चिन्हित अक्षर duped;
	bool plus;
	bool eof;
पूर्ण;

अटल व्योम nfs_सूची_पढ़ो_array_init(काष्ठा nfs_cache_array *array)
अणु
	स_रखो(array, 0, माप(काष्ठा nfs_cache_array));
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_page_init_array(काष्ठा page *page, u64 last_cookie)
अणु
	काष्ठा nfs_cache_array *array;

	array = kmap_atomic(page);
	nfs_सूची_पढ़ो_array_init(array);
	array->last_cookie = last_cookie;
	array->cookies_are_ordered = 1;
	kunmap_atomic(array);
पूर्ण

/*
 * we are मुक्तing strings created by nfs_add_to_सूची_पढ़ो_array()
 */
अटल
व्योम nfs_सूची_पढ़ो_clear_array(काष्ठा page *page)
अणु
	काष्ठा nfs_cache_array *array;
	पूर्णांक i;

	array = kmap_atomic(page);
	क्रम (i = 0; i < array->size; i++)
		kमुक्त(array->array[i].name);
	nfs_सूची_पढ़ो_array_init(array);
	kunmap_atomic(array);
पूर्ण

अटल काष्ठा page *
nfs_सूची_पढ़ो_page_array_alloc(u64 last_cookie, gfp_t gfp_flags)
अणु
	काष्ठा page *page = alloc_page(gfp_flags);
	अगर (page)
		nfs_सूची_पढ़ो_page_init_array(page, last_cookie);
	वापस page;
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_page_array_मुक्त(काष्ठा page *page)
अणु
	अगर (page) अणु
		nfs_सूची_पढ़ो_clear_array(page);
		put_page(page);
	पूर्ण
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_array_set_eof(काष्ठा nfs_cache_array *array)
अणु
	array->page_is_eof = 1;
	array->page_full = 1;
पूर्ण

अटल bool nfs_सूची_पढ़ो_array_is_full(काष्ठा nfs_cache_array *array)
अणु
	वापस array->page_full;
पूर्ण

/*
 * the caller is responsible क्रम मुक्तing qstr.name
 * when called by nfs_सूची_पढ़ो_add_to_array, the strings will be मुक्तd in
 * nfs_clear_सूची_पढ़ो_array()
 */
अटल स्थिर अक्षर *nfs_सूची_पढ़ो_copy_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक len)
अणु
	स्थिर अक्षर *ret = kmemdup_nul(name, len, GFP_KERNEL);

	/*
	 * Aव्योम a kmemleak false positive. The poपूर्णांकer to the name is stored
	 * in a page cache page which kmemleak करोes not scan.
	 */
	अगर (ret != शून्य)
		kmemleak_not_leak(ret);
	वापस ret;
पूर्ण

/*
 * Check that the next array entry lies entirely within the page bounds
 */
अटल पूर्णांक nfs_सूची_पढ़ो_array_can_expand(काष्ठा nfs_cache_array *array)
अणु
	काष्ठा nfs_cache_array_entry *cache_entry;

	अगर (array->page_full)
		वापस -ENOSPC;
	cache_entry = &array->array[array->size + 1];
	अगर ((अक्षर *)cache_entry - (अक्षर *)array > PAGE_SIZE) अणु
		array->page_full = 1;
		वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक nfs_सूची_पढ़ो_add_to_array(काष्ठा nfs_entry *entry, काष्ठा page *page)
अणु
	काष्ठा nfs_cache_array *array;
	काष्ठा nfs_cache_array_entry *cache_entry;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	name = nfs_सूची_पढ़ो_copy_name(entry->name, entry->len);
	अगर (!name)
		वापस -ENOMEM;

	array = kmap_atomic(page);
	ret = nfs_सूची_पढ़ो_array_can_expand(array);
	अगर (ret) अणु
		kमुक्त(name);
		जाओ out;
	पूर्ण

	cache_entry = &array->array[array->size];
	cache_entry->cookie = entry->prev_cookie;
	cache_entry->ino = entry->ino;
	cache_entry->d_type = entry->d_type;
	cache_entry->name_len = entry->len;
	cache_entry->name = name;
	array->last_cookie = entry->cookie;
	अगर (array->last_cookie <= cache_entry->cookie)
		array->cookies_are_ordered = 0;
	array->size++;
	अगर (entry->eof != 0)
		nfs_सूची_पढ़ो_array_set_eof(array);
out:
	kunmap_atomic(array);
	वापस ret;
पूर्ण

अटल काष्ठा page *nfs_सूची_पढ़ो_page_get_locked(काष्ठा address_space *mapping,
						pgoff_t index, u64 last_cookie)
अणु
	काष्ठा page *page;

	page = grab_cache_page(mapping, index);
	अगर (page && !PageUptodate(page)) अणु
		nfs_सूची_पढ़ो_page_init_array(page, last_cookie);
		अगर (invalidate_inode_pages2_range(mapping, index + 1, -1) < 0)
			nfs_zap_mapping(mapping->host, mapping);
		SetPageUptodate(page);
	पूर्ण

	वापस page;
पूर्ण

अटल u64 nfs_सूची_पढ़ो_page_last_cookie(काष्ठा page *page)
अणु
	काष्ठा nfs_cache_array *array;
	u64 ret;

	array = kmap_atomic(page);
	ret = array->last_cookie;
	kunmap_atomic(array);
	वापस ret;
पूर्ण

अटल bool nfs_सूची_पढ़ो_page_needs_filling(काष्ठा page *page)
अणु
	काष्ठा nfs_cache_array *array;
	bool ret;

	array = kmap_atomic(page);
	ret = !nfs_सूची_पढ़ो_array_is_full(array);
	kunmap_atomic(array);
	वापस ret;
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_page_set_eof(काष्ठा page *page)
अणु
	काष्ठा nfs_cache_array *array;

	array = kmap_atomic(page);
	nfs_सूची_पढ़ो_array_set_eof(array);
	kunmap_atomic(array);
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_page_unlock_and_put(काष्ठा page *page)
अणु
	unlock_page(page);
	put_page(page);
पूर्ण

अटल काष्ठा page *nfs_सूची_पढ़ो_page_get_next(काष्ठा address_space *mapping,
					      pgoff_t index, u64 cookie)
अणु
	काष्ठा page *page;

	page = nfs_सूची_पढ़ो_page_get_locked(mapping, index, cookie);
	अगर (page) अणु
		अगर (nfs_सूची_पढ़ो_page_last_cookie(page) == cookie)
			वापस page;
		nfs_सूची_पढ़ो_page_unlock_and_put(page);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक is_32bit_api(व्योम)
अणु
#अगर_घोषित CONFIG_COMPAT
	वापस in_compat_syscall();
#अन्यथा
	वापस (BITS_PER_LONG == 32);
#पूर्ण_अगर
पूर्ण

अटल
bool nfs_सूची_पढ़ो_use_cookie(स्थिर काष्ठा file *filp)
अणु
	अगर ((filp->f_mode & FMODE_32BITHASH) ||
	    (!(filp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक nfs_सूची_पढ़ो_search_क्रम_pos(काष्ठा nfs_cache_array *array,
				      काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	loff_t dअगरf = desc->ctx->pos - desc->current_index;
	अचिन्हित पूर्णांक index;

	अगर (dअगरf < 0)
		जाओ out_eof;
	अगर (dअगरf >= array->size) अणु
		अगर (array->page_is_eof)
			जाओ out_eof;
		वापस -EAGAIN;
	पूर्ण

	index = (अचिन्हित पूर्णांक)dअगरf;
	desc->dir_cookie = array->array[index].cookie;
	desc->cache_entry_index = index;
	वापस 0;
out_eof:
	desc->eof = true;
	वापस -EBADCOOKIE;
पूर्ण

अटल bool
nfs_सूची_पढ़ो_inode_mapping_valid(काष्ठा nfs_inode *nfsi)
अणु
	अगर (nfsi->cache_validity & (NFS_INO_INVALID_ATTR|NFS_INO_INVALID_DATA))
		वापस false;
	smp_rmb();
	वापस !test_bit(NFS_INO_INVALIDATING, &nfsi->flags);
पूर्ण

अटल bool nfs_सूची_पढ़ो_array_cookie_in_range(काष्ठा nfs_cache_array *array,
					      u64 cookie)
अणु
	अगर (!array->cookies_are_ordered)
		वापस true;
	/* Optimisation क्रम monotonically increasing cookies */
	अगर (cookie >= array->last_cookie)
		वापस false;
	अगर (array->size && cookie < array->array[0].cookie)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक nfs_सूची_पढ़ो_search_क्रम_cookie(काष्ठा nfs_cache_array *array,
					 काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	पूर्णांक i;
	loff_t new_pos;
	पूर्णांक status = -EAGAIN;

	अगर (!nfs_सूची_पढ़ो_array_cookie_in_range(array, desc->dir_cookie))
		जाओ check_eof;

	क्रम (i = 0; i < array->size; i++) अणु
		अगर (array->array[i].cookie == desc->dir_cookie) अणु
			काष्ठा nfs_inode *nfsi = NFS_I(file_inode(desc->file));

			new_pos = desc->current_index + i;
			अगर (desc->attr_gencount != nfsi->attr_gencount ||
			    !nfs_सूची_पढ़ो_inode_mapping_valid(nfsi)) अणु
				desc->duped = 0;
				desc->attr_gencount = nfsi->attr_gencount;
			पूर्ण अन्यथा अगर (new_pos < desc->prev_index) अणु
				अगर (desc->duped > 0
				    && desc->dup_cookie == desc->dir_cookie) अणु
					अगर (prपूर्णांकk_ratelimit()) अणु
						pr_notice("NFS: directory %pD2 contains a readdir loop."
								"Please contact your server vendor.  "
								"The file: %s has duplicate cookie %llu\n",
								desc->file, array->array[i].name, desc->dir_cookie);
					पूर्ण
					status = -ELOOP;
					जाओ out;
				पूर्ण
				desc->dup_cookie = desc->dir_cookie;
				desc->duped = -1;
			पूर्ण
			अगर (nfs_सूची_पढ़ो_use_cookie(desc->file))
				desc->ctx->pos = desc->dir_cookie;
			अन्यथा
				desc->ctx->pos = new_pos;
			desc->prev_index = new_pos;
			desc->cache_entry_index = i;
			वापस 0;
		पूर्ण
	पूर्ण
check_eof:
	अगर (array->page_is_eof) अणु
		status = -EBADCOOKIE;
		अगर (desc->dir_cookie == array->last_cookie)
			desc->eof = true;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs_सूची_पढ़ो_search_array(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	काष्ठा nfs_cache_array *array;
	पूर्णांक status;

	array = kmap_atomic(desc->page);

	अगर (desc->dir_cookie == 0)
		status = nfs_सूची_पढ़ो_search_क्रम_pos(array, desc);
	अन्यथा
		status = nfs_सूची_पढ़ो_search_क्रम_cookie(array, desc);

	अगर (status == -EAGAIN) अणु
		desc->last_cookie = array->last_cookie;
		desc->current_index += array->size;
		desc->page_index++;
	पूर्ण
	kunmap_atomic(array);
	वापस status;
पूर्ण

/* Fill a page with xdr inक्रमmation beक्रमe transferring to the cache page */
अटल पूर्णांक nfs_सूची_पढ़ो_xdr_filler(काष्ठा nfs_सूची_पढ़ो_descriptor *desc,
				  __be32 *verf, u64 cookie,
				  काष्ठा page **pages, माप_प्रकार bufsize,
				  __be32 *verf_res)
अणु
	काष्ठा inode *inode = file_inode(desc->file);
	काष्ठा nfs_सूची_पढ़ो_arg arg = अणु
		.dentry = file_dentry(desc->file),
		.cred = desc->file->f_cred,
		.verf = verf,
		.cookie = cookie,
		.pages = pages,
		.page_len = bufsize,
		.plus = desc->plus,
	पूर्ण;
	काष्ठा nfs_सूची_पढ़ो_res res = अणु
		.verf = verf_res,
	पूर्ण;
	अचिन्हित दीर्घ	बारtamp, gencount;
	पूर्णांक		error;

 again:
	बारtamp = jअगरfies;
	gencount = nfs_inc_attr_generation_counter();
	desc->dir_verअगरier = nfs_save_change_attribute(inode);
	error = NFS_PROTO(inode)->सूची_पढ़ो(&arg, &res);
	अगर (error < 0) अणु
		/* We requested READसूचीPLUS, but the server करोesn't grok it */
		अगर (error == -ENOTSUPP && desc->plus) अणु
			NFS_SERVER(inode)->caps &= ~NFS_CAP_READसूचीPLUS;
			clear_bit(NFS_INO_ADVISE_RDPLUS, &NFS_I(inode)->flags);
			desc->plus = arg.plus = false;
			जाओ again;
		पूर्ण
		जाओ error;
	पूर्ण
	desc->बारtamp = बारtamp;
	desc->gencount = gencount;
error:
	वापस error;
पूर्ण

अटल पूर्णांक xdr_decode(काष्ठा nfs_सूची_पढ़ो_descriptor *desc,
		      काष्ठा nfs_entry *entry, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा inode *inode = file_inode(desc->file);
	पूर्णांक error;

	error = NFS_PROTO(inode)->decode_dirent(xdr, entry, desc->plus);
	अगर (error)
		वापस error;
	entry->fattr->समय_start = desc->बारtamp;
	entry->fattr->gencount = desc->gencount;
	वापस 0;
पूर्ण

/* Match file and dirent using either filehandle or fileid
 * Note: caller is responsible क्रम checking the fsid
 */
अटल
पूर्णांक nfs_same_file(काष्ठा dentry *dentry, काष्ठा nfs_entry *entry)
अणु
	काष्ठा inode *inode;
	काष्ठा nfs_inode *nfsi;

	अगर (d_really_is_negative(dentry))
		वापस 0;

	inode = d_inode(dentry);
	अगर (is_bad_inode(inode) || NFS_STALE(inode))
		वापस 0;

	nfsi = NFS_I(inode);
	अगर (entry->fattr->fileid != nfsi->fileid)
		वापस 0;
	अगर (entry->fh->size && nfs_compare_fh(entry->fh, &nfsi->fh) != 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल
bool nfs_use_सूची_पढ़ोplus(काष्ठा inode *dir, काष्ठा dir_context *ctx)
अणु
	अगर (!nfs_server_capable(dir, NFS_CAP_READसूचीPLUS))
		वापस false;
	अगर (test_and_clear_bit(NFS_INO_ADVISE_RDPLUS, &NFS_I(dir)->flags))
		वापस true;
	अगर (ctx->pos == 0)
		वापस true;
	वापस false;
पूर्ण

/*
 * This function is called by the lookup and getattr code to request the
 * use of सूची_पढ़ोplus to accelerate any future lookups in the same
 * directory.
 */
व्योम nfs_advise_use_सूची_पढ़ोplus(काष्ठा inode *dir)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(dir);

	अगर (nfs_server_capable(dir, NFS_CAP_READसूचीPLUS) &&
	    !list_empty(&nfsi->खोलो_files))
		set_bit(NFS_INO_ADVISE_RDPLUS, &nfsi->flags);
पूर्ण

/*
 * This function is मुख्यly क्रम use by nfs_getattr().
 *
 * If this is an 'ls -l', we want to क्रमce use of सूची_पढ़ोplus.
 * Do this by checking अगर there is an active file descriptor
 * and calling nfs_advise_use_सूची_पढ़ोplus, then क्रमcing a
 * cache flush.
 */
व्योम nfs_क्रमce_use_सूची_पढ़ोplus(काष्ठा inode *dir)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(dir);

	अगर (nfs_server_capable(dir, NFS_CAP_READसूचीPLUS) &&
	    !list_empty(&nfsi->खोलो_files)) अणु
		set_bit(NFS_INO_ADVISE_RDPLUS, &nfsi->flags);
		invalidate_mapping_pages(dir->i_mapping,
			nfsi->page_index + 1, -1);
	पूर्ण
पूर्ण

अटल
व्योम nfs_prime_dcache(काष्ठा dentry *parent, काष्ठा nfs_entry *entry,
		अचिन्हित दीर्घ dir_verअगरier)
अणु
	काष्ठा qstr filename = QSTR_INIT(entry->name, entry->len);
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	काष्ठा dentry *dentry;
	काष्ठा dentry *alias;
	काष्ठा inode *inode;
	पूर्णांक status;

	अगर (!(entry->fattr->valid & NFS_ATTR_FATTR_खाताID))
		वापस;
	अगर (!(entry->fattr->valid & NFS_ATTR_FATTR_FSID))
		वापस;
	अगर (filename.len == 0)
		वापस;
	/* Validate that the name करोesn't contain any illegal '\0' */
	अगर (strnlen(filename.name, filename.len) != filename.len)
		वापस;
	/* ...or '/' */
	अगर (strnchr(filename.name, filename.len, '/'))
		वापस;
	अगर (filename.name[0] == '.') अणु
		अगर (filename.len == 1)
			वापस;
		अगर (filename.len == 2 && filename.name[1] == '.')
			वापस;
	पूर्ण
	filename.hash = full_name_hash(parent, filename.name, filename.len);

	dentry = d_lookup(parent, &filename);
again:
	अगर (!dentry) अणु
		dentry = d_alloc_parallel(parent, &filename, &wq);
		अगर (IS_ERR(dentry))
			वापस;
	पूर्ण
	अगर (!d_in_lookup(dentry)) अणु
		/* Is there a mountpoपूर्णांक here? If so, just निकास */
		अगर (!nfs_fsid_equal(&NFS_SB(dentry->d_sb)->fsid,
					&entry->fattr->fsid))
			जाओ out;
		अगर (nfs_same_file(dentry, entry)) अणु
			अगर (!entry->fh->size)
				जाओ out;
			nfs_set_verअगरier(dentry, dir_verअगरier);
			status = nfs_refresh_inode(d_inode(dentry), entry->fattr);
			अगर (!status)
				nfs_setsecurity(d_inode(dentry), entry->fattr, entry->label);
			जाओ out;
		पूर्ण अन्यथा अणु
			d_invalidate(dentry);
			dput(dentry);
			dentry = शून्य;
			जाओ again;
		पूर्ण
	पूर्ण
	अगर (!entry->fh->size) अणु
		d_lookup_करोne(dentry);
		जाओ out;
	पूर्ण

	inode = nfs_fhget(dentry->d_sb, entry->fh, entry->fattr, entry->label);
	alias = d_splice_alias(inode, dentry);
	d_lookup_करोne(dentry);
	अगर (alias) अणु
		अगर (IS_ERR(alias))
			जाओ out;
		dput(dentry);
		dentry = alias;
	पूर्ण
	nfs_set_verअगरier(dentry, dir_verअगरier);
out:
	dput(dentry);
पूर्ण

/* Perक्रमm conversion from xdr to cache array */
अटल पूर्णांक nfs_सूची_पढ़ो_page_filler(काष्ठा nfs_सूची_पढ़ो_descriptor *desc,
				   काष्ठा nfs_entry *entry,
				   काष्ठा page **xdr_pages,
				   अचिन्हित पूर्णांक buflen,
				   काष्ठा page **arrays,
				   माप_प्रकार narrays)
अणु
	काष्ठा address_space *mapping = desc->file->f_mapping;
	काष्ठा xdr_stream stream;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch, *new, *page = *arrays;
	पूर्णांक status;

	scratch = alloc_page(GFP_KERNEL);
	अगर (scratch == शून्य)
		वापस -ENOMEM;

	xdr_init_decode_pages(&stream, &buf, xdr_pages, buflen);
	xdr_set_scratch_page(&stream, scratch);

	करो अणु
		अगर (entry->label)
			entry->label->len = NFS4_MAXLABELLEN;

		status = xdr_decode(desc, entry, &stream);
		अगर (status != 0)
			अवरोध;

		अगर (desc->plus)
			nfs_prime_dcache(file_dentry(desc->file), entry,
					desc->dir_verअगरier);

		status = nfs_सूची_पढ़ो_add_to_array(entry, page);
		अगर (status != -ENOSPC)
			जारी;

		अगर (page->mapping != mapping) अणु
			अगर (!--narrays)
				अवरोध;
			new = nfs_सूची_पढ़ो_page_array_alloc(entry->prev_cookie,
							   GFP_KERNEL);
			अगर (!new)
				अवरोध;
			arrays++;
			*arrays = page = new;
		पूर्ण अन्यथा अणु
			new = nfs_सूची_पढ़ो_page_get_next(mapping,
							page->index + 1,
							entry->prev_cookie);
			अगर (!new)
				अवरोध;
			अगर (page != *arrays)
				nfs_सूची_पढ़ो_page_unlock_and_put(page);
			page = new;
		पूर्ण
		status = nfs_सूची_पढ़ो_add_to_array(entry, page);
	पूर्ण जबतक (!status && !entry->eof);

	चयन (status) अणु
	हाल -EBADCOOKIE:
		अगर (entry->eof) अणु
			nfs_सूची_पढ़ो_page_set_eof(page);
			status = 0;
		पूर्ण
		अवरोध;
	हाल -ENOSPC:
	हाल -EAGAIN:
		status = 0;
		अवरोध;
	पूर्ण

	अगर (page != *arrays)
		nfs_सूची_पढ़ो_page_unlock_and_put(page);

	put_page(scratch);
	वापस status;
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_मुक्त_pages(काष्ठा page **pages, माप_प्रकार npages)
अणु
	जबतक (npages--)
		put_page(pages[npages]);
	kमुक्त(pages);
पूर्ण

/*
 * nfs_सूची_पढ़ो_alloc_pages() will allocate pages that must be मुक्तd with a call
 * to nfs_सूची_पढ़ो_मुक्त_pages()
 */
अटल काष्ठा page **nfs_सूची_पढ़ो_alloc_pages(माप_प्रकार npages)
अणु
	काष्ठा page **pages;
	माप_प्रकार i;

	pages = kदो_स्मृति_array(npages, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस शून्य;
	क्रम (i = 0; i < npages; i++) अणु
		काष्ठा page *page = alloc_page(GFP_KERNEL);
		अगर (page == शून्य)
			जाओ out_मुक्तpages;
		pages[i] = page;
	पूर्ण
	वापस pages;

out_मुक्तpages:
	nfs_सूची_पढ़ो_मुक्त_pages(pages, i);
	वापस शून्य;
पूर्ण

अटल पूर्णांक nfs_सूची_पढ़ो_xdr_to_array(काष्ठा nfs_सूची_पढ़ो_descriptor *desc,
				    __be32 *verf_arg, __be32 *verf_res,
				    काष्ठा page **arrays, माप_प्रकार narrays)
अणु
	काष्ठा page **pages;
	काष्ठा page *page = *arrays;
	काष्ठा nfs_entry *entry;
	माप_प्रकार array_size;
	काष्ठा inode *inode = file_inode(desc->file);
	माप_प्रकार dtsize = NFS_SERVER(inode)->dtsize;
	पूर्णांक status = -ENOMEM;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;
	entry->cookie = nfs_सूची_पढ़ो_page_last_cookie(page);
	entry->fh = nfs_alloc_fhandle();
	entry->fattr = nfs_alloc_fattr();
	entry->server = NFS_SERVER(inode);
	अगर (entry->fh == शून्य || entry->fattr == शून्य)
		जाओ out;

	entry->label = nfs4_label_alloc(NFS_SERVER(inode), GFP_NOWAIT);
	अगर (IS_ERR(entry->label)) अणु
		status = PTR_ERR(entry->label);
		जाओ out;
	पूर्ण

	array_size = (dtsize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	pages = nfs_सूची_पढ़ो_alloc_pages(array_size);
	अगर (!pages)
		जाओ out_release_label;

	करो अणु
		अचिन्हित पूर्णांक pglen;
		status = nfs_सूची_पढ़ो_xdr_filler(desc, verf_arg, entry->cookie,
						pages, dtsize,
						verf_res);
		अगर (status < 0)
			अवरोध;

		pglen = status;
		अगर (pglen == 0) अणु
			nfs_सूची_पढ़ो_page_set_eof(page);
			अवरोध;
		पूर्ण

		verf_arg = verf_res;

		status = nfs_सूची_पढ़ो_page_filler(desc, entry, pages, pglen,
						 arrays, narrays);
	पूर्ण जबतक (!status && nfs_सूची_पढ़ो_page_needs_filling(page));

	nfs_सूची_पढ़ो_मुक्त_pages(pages, array_size);
out_release_label:
	nfs4_label_मुक्त(entry->label);
out:
	nfs_मुक्त_fattr(entry->fattr);
	nfs_मुक्त_fhandle(entry->fh);
	kमुक्त(entry);
	वापस status;
पूर्ण

अटल व्योम nfs_सूची_पढ़ो_page_put(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	put_page(desc->page);
	desc->page = शून्य;
पूर्ण

अटल व्योम
nfs_सूची_पढ़ो_page_unlock_and_put_cached(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	unlock_page(desc->page);
	nfs_सूची_पढ़ो_page_put(desc);
पूर्ण

अटल काष्ठा page *
nfs_सूची_पढ़ो_page_get_cached(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	वापस nfs_सूची_पढ़ो_page_get_locked(desc->file->f_mapping,
					   desc->page_index,
					   desc->last_cookie);
पूर्ण

/*
 * Returns 0 अगर desc->dir_cookie was found on page desc->page_index
 * and locks the page to prevent removal from the page cache.
 */
अटल पूर्णांक find_and_lock_cache_page(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	काष्ठा inode *inode = file_inode(desc->file);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	__be32 verf[NFS_सूची_VERIFIER_SIZE];
	पूर्णांक res;

	desc->page = nfs_सूची_पढ़ो_page_get_cached(desc);
	अगर (!desc->page)
		वापस -ENOMEM;
	अगर (nfs_सूची_पढ़ो_page_needs_filling(desc->page)) अणु
		res = nfs_सूची_पढ़ो_xdr_to_array(desc, nfsi->cookieverf, verf,
					       &desc->page, 1);
		अगर (res < 0) अणु
			nfs_सूची_पढ़ो_page_unlock_and_put_cached(desc);
			अगर (res == -EBADCOOKIE || res == -ENOTSYNC) अणु
				invalidate_inode_pages2(desc->file->f_mapping);
				desc->page_index = 0;
				वापस -EAGAIN;
			पूर्ण
			वापस res;
		पूर्ण
		/*
		 * Set the cookie verअगरier अगर the page cache was empty
		 */
		अगर (desc->page_index == 0)
			स_नकल(nfsi->cookieverf, verf,
			       माप(nfsi->cookieverf));
	पूर्ण
	res = nfs_सूची_पढ़ो_search_array(desc);
	अगर (res == 0) अणु
		nfsi->page_index = desc->page_index;
		वापस 0;
	पूर्ण
	nfs_सूची_पढ़ो_page_unlock_and_put_cached(desc);
	वापस res;
पूर्ण

अटल bool nfs_सूची_पढ़ो_करोnt_search_cache(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	काष्ठा address_space *mapping = desc->file->f_mapping;
	काष्ठा inode *dir = file_inode(desc->file);
	अचिन्हित पूर्णांक dtsize = NFS_SERVER(dir)->dtsize;
	loff_t size = i_size_पढ़ो(dir);

	/*
	 * Default to uncached सूची_पढ़ो अगर the page cache is empty, and
	 * we're looking क्रम a non-zero cookie in a large directory.
	 */
	वापस desc->dir_cookie != 0 && mapping->nrpages == 0 && size > dtsize;
पूर्ण

/* Search क्रम desc->dir_cookie from the beginning of the page cache */
अटल पूर्णांक सूची_पढ़ो_search_pagecache(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	पूर्णांक res;

	अगर (nfs_सूची_पढ़ो_करोnt_search_cache(desc))
		वापस -EBADCOOKIE;

	करो अणु
		अगर (desc->page_index == 0) अणु
			desc->current_index = 0;
			desc->prev_index = 0;
			desc->last_cookie = 0;
		पूर्ण
		res = find_and_lock_cache_page(desc);
	पूर्ण जबतक (res == -EAGAIN);
	वापस res;
पूर्ण

/*
 * Once we've found the start of the dirent within a page: fill 'er up...
 */
अटल व्योम nfs_करो_filldir(काष्ठा nfs_सूची_पढ़ो_descriptor *desc,
			   स्थिर __be32 *verf)
अणु
	काष्ठा file	*file = desc->file;
	काष्ठा nfs_cache_array *array;
	अचिन्हित पूर्णांक i = 0;

	array = kmap(desc->page);
	क्रम (i = desc->cache_entry_index; i < array->size; i++) अणु
		काष्ठा nfs_cache_array_entry *ent;

		ent = &array->array[i];
		अगर (!dir_emit(desc->ctx, ent->name, ent->name_len,
		    nfs_compat_user_ino64(ent->ino), ent->d_type)) अणु
			desc->eof = true;
			अवरोध;
		पूर्ण
		स_नकल(desc->verf, verf, माप(desc->verf));
		अगर (i < (array->size-1))
			desc->dir_cookie = array->array[i+1].cookie;
		अन्यथा
			desc->dir_cookie = array->last_cookie;
		अगर (nfs_सूची_पढ़ो_use_cookie(file))
			desc->ctx->pos = desc->dir_cookie;
		अन्यथा
			desc->ctx->pos++;
		अगर (desc->duped != 0)
			desc->duped = 1;
	पूर्ण
	अगर (array->page_is_eof)
		desc->eof = true;

	kunmap(desc->page);
	dfprपूर्णांकk(सूचीCACHE, "NFS: nfs_do_filldir() filling ended @ cookie %llu\n",
			(अचिन्हित दीर्घ दीर्घ)desc->dir_cookie);
पूर्ण

/*
 * If we cannot find a cookie in our cache, we suspect that this is
 * because it poपूर्णांकs to a deleted file, so we ask the server to वापस
 * whatever it thinks is the next entry. We then feed this to filldir.
 * If all goes well, we should then be able to find our way round the
 * cache on the next call to सूची_पढ़ो_search_pagecache();
 *
 * NOTE: we cannot add the anonymous page to the pagecache because
 *	 the data it contains might not be page aligned. Besides,
 *	 we should alपढ़ोy have a complete representation of the
 *	 directory in the page cache by the समय we get here.
 */
अटल पूर्णांक uncached_सूची_पढ़ो(काष्ठा nfs_सूची_पढ़ो_descriptor *desc)
अणु
	काष्ठा page	**arrays;
	माप_प्रकार		i, sz = 512;
	__be32		verf[NFS_सूची_VERIFIER_SIZE];
	पूर्णांक		status = -ENOMEM;

	dfprपूर्णांकk(सूचीCACHE, "NFS: uncached_readdir() searching for cookie %llu\n",
			(अचिन्हित दीर्घ दीर्घ)desc->dir_cookie);

	arrays = kसुस्मृति(sz, माप(*arrays), GFP_KERNEL);
	अगर (!arrays)
		जाओ out;
	arrays[0] = nfs_सूची_पढ़ो_page_array_alloc(desc->dir_cookie, GFP_KERNEL);
	अगर (!arrays[0])
		जाओ out;

	desc->page_index = 0;
	desc->last_cookie = desc->dir_cookie;
	desc->duped = 0;

	status = nfs_सूची_पढ़ो_xdr_to_array(desc, desc->verf, verf, arrays, sz);

	क्रम (i = 0; !desc->eof && i < sz && arrays[i]; i++) अणु
		desc->page = arrays[i];
		nfs_करो_filldir(desc, verf);
	पूर्ण
	desc->page = शून्य;


	क्रम (i = 0; i < sz && arrays[i]; i++)
		nfs_सूची_पढ़ो_page_array_मुक्त(arrays[i]);
out:
	kमुक्त(arrays);
	dfprपूर्णांकk(सूचीCACHE, "NFS: %s: returns %d\n", __func__, status);
	वापस status;
पूर्ण

/* The file offset position represents the dirent entry number.  A
   last cookie cache takes care of the common हाल of पढ़ोing the
   whole directory.
 */
अटल पूर्णांक nfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा dentry	*dentry = file_dentry(file);
	काष्ठा inode	*inode = d_inode(dentry);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_खोलो_dir_context *dir_ctx = file->निजी_data;
	काष्ठा nfs_सूची_पढ़ो_descriptor *desc;
	पूर्णांक res;

	dfprपूर्णांकk(खाता, "NFS: readdir(%pD2) starting at cookie %llu\n",
			file, (दीर्घ दीर्घ)ctx->pos);
	nfs_inc_stats(inode, NFSIOS_VFSGETDENTS);

	/*
	 * ctx->pos poपूर्णांकs to the dirent entry number.
	 * *desc->dir_cookie has the cookie क्रम the next entry. We have
	 * to either find the entry with the appropriate number or
	 * revalidate the cookie.
	 */
	अगर (ctx->pos == 0 || nfs_attribute_cache_expired(inode)) अणु
		res = nfs_revalidate_mapping(inode, file->f_mapping);
		अगर (res < 0)
			जाओ out;
	पूर्ण

	res = -ENOMEM;
	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		जाओ out;
	desc->file = file;
	desc->ctx = ctx;
	desc->plus = nfs_use_सूची_पढ़ोplus(inode, ctx);

	spin_lock(&file->f_lock);
	desc->dir_cookie = dir_ctx->dir_cookie;
	desc->dup_cookie = dir_ctx->dup_cookie;
	desc->duped = dir_ctx->duped;
	desc->attr_gencount = dir_ctx->attr_gencount;
	स_नकल(desc->verf, dir_ctx->verf, माप(desc->verf));
	spin_unlock(&file->f_lock);

	करो अणु
		res = सूची_पढ़ो_search_pagecache(desc);

		अगर (res == -EBADCOOKIE) अणु
			res = 0;
			/* This means either end of directory */
			अगर (desc->dir_cookie && !desc->eof) अणु
				/* Or that the server has 'lost' a cookie */
				res = uncached_सूची_पढ़ो(desc);
				अगर (res == 0)
					जारी;
				अगर (res == -EBADCOOKIE || res == -ENOTSYNC)
					res = 0;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (res == -ETOOSMALL && desc->plus) अणु
			clear_bit(NFS_INO_ADVISE_RDPLUS, &nfsi->flags);
			nfs_zap_caches(inode);
			desc->page_index = 0;
			desc->plus = false;
			desc->eof = false;
			जारी;
		पूर्ण
		अगर (res < 0)
			अवरोध;

		nfs_करो_filldir(desc, nfsi->cookieverf);
		nfs_सूची_पढ़ो_page_unlock_and_put_cached(desc);
	पूर्ण जबतक (!desc->eof);

	spin_lock(&file->f_lock);
	dir_ctx->dir_cookie = desc->dir_cookie;
	dir_ctx->dup_cookie = desc->dup_cookie;
	dir_ctx->duped = desc->duped;
	dir_ctx->attr_gencount = desc->attr_gencount;
	स_नकल(dir_ctx->verf, desc->verf, माप(dir_ctx->verf));
	spin_unlock(&file->f_lock);

	kमुक्त(desc);

out:
	dfprपूर्णांकk(खाता, "NFS: readdir(%pD2) returns %d\n", file, res);
	वापस res;
पूर्ण

अटल loff_t nfs_llseek_dir(काष्ठा file *filp, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा nfs_खोलो_dir_context *dir_ctx = filp->निजी_data;

	dfprपूर्णांकk(खाता, "NFS: llseek dir(%pD2, %lld, %d)\n",
			filp, offset, whence);

	चयन (whence) अणु
	शेष:
		वापस -EINVAL;
	हाल शुरू_से:
		अगर (offset < 0)
			वापस -EINVAL;
		spin_lock(&filp->f_lock);
		अवरोध;
	हाल प्रस्तुत_से:
		अगर (offset == 0)
			वापस filp->f_pos;
		spin_lock(&filp->f_lock);
		offset += filp->f_pos;
		अगर (offset < 0) अणु
			spin_unlock(&filp->f_lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (offset != filp->f_pos) अणु
		filp->f_pos = offset;
		अगर (nfs_सूची_पढ़ो_use_cookie(filp))
			dir_ctx->dir_cookie = offset;
		अन्यथा
			dir_ctx->dir_cookie = 0;
		अगर (offset == 0)
			स_रखो(dir_ctx->verf, 0, माप(dir_ctx->verf));
		dir_ctx->duped = 0;
	पूर्ण
	spin_unlock(&filp->f_lock);
	वापस offset;
पूर्ण

/*
 * All directory operations under NFS are synchronous, so fsync()
 * is a dummy operation.
 */
अटल पूर्णांक nfs_fsync_dir(काष्ठा file *filp, loff_t start, loff_t end,
			 पूर्णांक datasync)
अणु
	dfprपूर्णांकk(खाता, "NFS: fsync dir(%pD2) datasync %d\n", filp, datasync);

	nfs_inc_stats(file_inode(filp), NFSIOS_VFSFSYNC);
	वापस 0;
पूर्ण

/**
 * nfs_क्रमce_lookup_revalidate - Mark the directory as having changed
 * @dir: poपूर्णांकer to directory inode
 *
 * This क्रमces the revalidation code in nfs_lookup_revalidate() to करो a
 * full lookup on all child dentries of 'dir' whenever a change occurs
 * on the server that might have invalidated our dcache.
 *
 * Note that we reserve bit '0' as a tag to let us know when a dentry
 * was revalidated जबतक holding a delegation on its inode.
 *
 * The caller should be holding dir->i_lock
 */
व्योम nfs_क्रमce_lookup_revalidate(काष्ठा inode *dir)
अणु
	NFS_I(dir)->cache_change_attribute += 2;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_क्रमce_lookup_revalidate);

/**
 * nfs_verअगरy_change_attribute - Detects NFS remote directory changes
 * @dir: poपूर्णांकer to parent directory inode
 * @verf: previously saved change attribute
 *
 * Return "false" अगर the verअगरiers करोesn't match the change attribute.
 * This would usually indicate that the directory contents have changed on
 * the server, and that any dentries need revalidating.
 */
अटल bool nfs_verअगरy_change_attribute(काष्ठा inode *dir, अचिन्हित दीर्घ verf)
अणु
	वापस (verf & ~1UL) == nfs_save_change_attribute(dir);
पूर्ण

अटल व्योम nfs_set_verअगरier_delegated(अचिन्हित दीर्घ *verf)
अणु
	*verf |= 1UL;
पूर्ण

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल व्योम nfs_unset_verअगरier_delegated(अचिन्हित दीर्घ *verf)
अणु
	*verf &= ~1UL;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_NFS_V4) */

अटल bool nfs_test_verअगरier_delegated(अचिन्हित दीर्घ verf)
अणु
	वापस verf & 1;
पूर्ण

अटल bool nfs_verअगरier_is_delegated(काष्ठा dentry *dentry)
अणु
	वापस nfs_test_verअगरier_delegated(dentry->d_समय);
पूर्ण

अटल व्योम nfs_set_verअगरier_locked(काष्ठा dentry *dentry, अचिन्हित दीर्घ verf)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (!nfs_verअगरier_is_delegated(dentry) &&
	    !nfs_verअगरy_change_attribute(d_inode(dentry->d_parent), verf))
		जाओ out;
	अगर (inode && NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		nfs_set_verअगरier_delegated(&verf);
out:
	dentry->d_समय = verf;
पूर्ण

/**
 * nfs_set_verअगरier - save a parent directory verअगरier in the dentry
 * @dentry: poपूर्णांकer to dentry
 * @verf: verअगरier to save
 *
 * Saves the parent directory verअगरier in @dentry. If the inode has
 * a delegation, we also tag the dentry as having been revalidated
 * जबतक holding a delegation so that we know we करोn't have to
 * look it up again after a directory change.
 */
व्योम nfs_set_verअगरier(काष्ठा dentry *dentry, अचिन्हित दीर्घ verf)
अणु

	spin_lock(&dentry->d_lock);
	nfs_set_verअगरier_locked(dentry, verf);
	spin_unlock(&dentry->d_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_set_verअगरier);

#अगर IS_ENABLED(CONFIG_NFS_V4)
/**
 * nfs_clear_verअगरier_delegated - clear the dir verअगरier delegation tag
 * @inode: poपूर्णांकer to inode
 *
 * Iterates through the dentries in the inode alias list and clears
 * the tag used to indicate that the dentry has been revalidated
 * जबतक holding a delegation.
 * This function is पूर्णांकended क्रम use when the delegation is being
 * वापसed or revoked.
 */
व्योम nfs_clear_verअगरier_delegated(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias;

	अगर (!inode)
		वापस;
	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&alias->d_lock);
		nfs_unset_verअगरier_delegated(&alias->d_समय);
		spin_unlock(&alias->d_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_clear_verअगरier_delegated);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_NFS_V4) */

/*
 * A check क्रम whether or not the parent directory has changed.
 * In the हाल it has, we assume that the dentries are untrustworthy
 * and may need to be looked up again.
 * If rcu_walk prevents us from perक्रमming a full check, वापस 0.
 */
अटल पूर्णांक nfs_check_verअगरier(काष्ठा inode *dir, काष्ठा dentry *dentry,
			      पूर्णांक rcu_walk)
अणु
	अगर (IS_ROOT(dentry))
		वापस 1;
	अगर (NFS_SERVER(dir)->flags & NFS_MOUNT_LOOKUP_CACHE_NONE)
		वापस 0;
	अगर (!nfs_verअगरy_change_attribute(dir, dentry->d_समय))
		वापस 0;
	/* Revalidate nfsi->cache_change_attribute beक्रमe we declare a match */
	अगर (nfs_mapping_need_revalidate_inode(dir)) अणु
		अगर (rcu_walk)
			वापस 0;
		अगर (__nfs_revalidate_inode(NFS_SERVER(dir), dir) < 0)
			वापस 0;
	पूर्ण
	अगर (!nfs_verअगरy_change_attribute(dir, dentry->d_समय))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Use पूर्णांकent inक्रमmation to check whether or not we're going to करो
 * an O_EXCL create using this path component.
 */
अटल पूर्णांक nfs_is_exclusive_create(काष्ठा inode *dir, अचिन्हित पूर्णांक flags)
अणु
	अगर (NFS_PROTO(dir)->version == 2)
		वापस 0;
	वापस flags & LOOKUP_EXCL;
पूर्ण

/*
 * Inode and filehandle revalidation क्रम lookups.
 *
 * We क्रमce revalidation in the हालs where the VFS sets LOOKUP_REVAL,
 * or अगर the पूर्णांकent inक्रमmation indicates that we're about to खोलो this
 * particular file and the "nocto" mount flag is not set.
 *
 */
अटल
पूर्णांक nfs_lookup_verअगरy_inode(काष्ठा inode *inode, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	पूर्णांक ret;

	अगर (IS_AUTOMOUNT(inode))
		वापस 0;

	अगर (flags & LOOKUP_OPEN) अणु
		चयन (inode->i_mode & S_IFMT) अणु
		हाल S_IFREG:
			/* A NFSv4 OPEN will revalidate later */
			अगर (server->caps & NFS_CAP_ATOMIC_OPEN)
				जाओ out;
			fallthrough;
		हाल S_IFसूची:
			अगर (server->flags & NFS_MOUNT_NOCTO)
				अवरोध;
			/* NFS बंद-to-खोलो cache consistency validation */
			जाओ out_क्रमce;
		पूर्ण
	पूर्ण

	/* VFS wants an on-the-wire revalidation */
	अगर (flags & LOOKUP_REVAL)
		जाओ out_क्रमce;
out:
	वापस (inode->i_nlink == 0) ? -ESTALE : 0;
out_क्रमce:
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;
	ret = __nfs_revalidate_inode(server, inode);
	अगर (ret != 0)
		वापस ret;
	जाओ out;
पूर्ण

अटल व्योम nfs_mark_dir_क्रम_revalidate(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	nfs_set_cache_invalid(inode, NFS_INO_REVAL_PAGECACHE);
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * We judge how दीर्घ we want to trust negative
 * dentries by looking at the parent inode mसमय.
 *
 * If parent mसमय has changed, we revalidate, अन्यथा we रुको क्रम a
 * period corresponding to the parent's attribute cache समयout value.
 *
 * If LOOKUP_RCU prevents us from perक्रमming a full check, वापस 1
 * suggesting a reval is needed.
 *
 * Note that when creating a new file, or looking up a नाम target,
 * then it shouldn't be necessary to revalidate a negative dentry.
 */
अटल अंतरभूत
पूर्णांक nfs_neg_need_reval(काष्ठा inode *dir, काष्ठा dentry *dentry,
		       अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		वापस 0;
	अगर (NFS_SERVER(dir)->flags & NFS_MOUNT_LOOKUP_CACHE_NONEG)
		वापस 1;
	वापस !nfs_check_verअगरier(dir, dentry, flags & LOOKUP_RCU);
पूर्ण

अटल पूर्णांक
nfs_lookup_revalidate_करोne(काष्ठा inode *dir, काष्ठा dentry *dentry,
			   काष्ठा inode *inode, पूर्णांक error)
अणु
	चयन (error) अणु
	हाल 1:
		dfprपूर्णांकk(LOOKUPCACHE, "NFS: %s(%pd2) is valid\n",
			__func__, dentry);
		वापस 1;
	हाल 0:
		/*
		 * We can't d_drop the root of a disconnected tree:
		 * its d_hash is on the s_anon list and d_drop() would hide
		 * it from shrink_dcache_क्रम_unmount(), leading to busy
		 * inodes on unmount and further oopses.
		 */
		अगर (inode && IS_ROOT(dentry))
			वापस 1;
		dfprपूर्णांकk(LOOKUPCACHE, "NFS: %s(%pd2) is invalid\n",
				__func__, dentry);
		वापस 0;
	पूर्ण
	dfprपूर्णांकk(LOOKUPCACHE, "NFS: %s(%pd2) lookup returned error %d\n",
				__func__, dentry, error);
	वापस error;
पूर्ण

अटल पूर्णांक
nfs_lookup_revalidate_negative(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret = 1;
	अगर (nfs_neg_need_reval(dir, dentry, flags)) अणु
		अगर (flags & LOOKUP_RCU)
			वापस -ECHILD;
		ret = 0;
	पूर्ण
	वापस nfs_lookup_revalidate_करोne(dir, dentry, शून्य, ret);
पूर्ण

अटल पूर्णांक
nfs_lookup_revalidate_delegated(काष्ठा inode *dir, काष्ठा dentry *dentry,
				काष्ठा inode *inode)
अणु
	nfs_set_verअगरier(dentry, nfs_save_change_attribute(dir));
	वापस nfs_lookup_revalidate_करोne(dir, dentry, inode, 1);
पूर्ण

अटल पूर्णांक
nfs_lookup_revalidate_dentry(काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा inode *inode)
अणु
	काष्ठा nfs_fh *fhandle;
	काष्ठा nfs_fattr *fattr;
	काष्ठा nfs4_label *label;
	अचिन्हित दीर्घ dir_verअगरier;
	पूर्णांक ret;

	ret = -ENOMEM;
	fhandle = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	label = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	अगर (fhandle == शून्य || fattr == शून्य || IS_ERR(label))
		जाओ out;

	dir_verअगरier = nfs_save_change_attribute(dir);
	ret = NFS_PROTO(dir)->lookup(dir, dentry, fhandle, fattr, label);
	अगर (ret < 0) अणु
		चयन (ret) अणु
		हाल -ESTALE:
		हाल -ENOENT:
			ret = 0;
			अवरोध;
		हाल -ETIMEDOUT:
			अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_SOFTREVAL)
				ret = 1;
		पूर्ण
		जाओ out;
	पूर्ण
	ret = 0;
	अगर (nfs_compare_fh(NFS_FH(inode), fhandle))
		जाओ out;
	अगर (nfs_refresh_inode(inode, fattr) < 0)
		जाओ out;

	nfs_setsecurity(inode, fattr, label);
	nfs_set_verअगरier(dentry, dir_verअगरier);

	/* set a सूची_पढ़ोplus hपूर्णांक that we had a cache miss */
	nfs_क्रमce_use_सूची_पढ़ोplus(dir);
	ret = 1;
out:
	nfs_मुक्त_fattr(fattr);
	nfs_मुक्त_fhandle(fhandle);
	nfs4_label_मुक्त(label);

	/*
	 * If the lookup failed despite the dentry change attribute being
	 * a match, then we should revalidate the directory cache.
	 */
	अगर (!ret && nfs_verअगरy_change_attribute(dir, dentry->d_समय))
		nfs_mark_dir_क्रम_revalidate(dir);
	वापस nfs_lookup_revalidate_करोne(dir, dentry, inode, ret);
पूर्ण

/*
 * This is called every समय the dcache has a lookup hit,
 * and we should check whether we can really trust that
 * lookup.
 *
 * NOTE! The hit can be a negative hit too, करोn't assume
 * we have an inode!
 *
 * If the parent directory is seen to have changed, we throw out the
 * cached dentry and करो a new lookup.
 */
अटल पूर्णांक
nfs_करो_lookup_revalidate(काष्ठा inode *dir, काष्ठा dentry *dentry,
			 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	पूर्णांक error;

	nfs_inc_stats(dir, NFSIOS_DENTRYREVALIDATE);
	inode = d_inode(dentry);

	अगर (!inode)
		वापस nfs_lookup_revalidate_negative(dir, dentry, flags);

	अगर (is_bad_inode(inode)) अणु
		dfprपूर्णांकk(LOOKUPCACHE, "%s: %pd2 has dud inode\n",
				__func__, dentry);
		जाओ out_bad;
	पूर्ण

	अगर (nfs_verअगरier_is_delegated(dentry))
		वापस nfs_lookup_revalidate_delegated(dir, dentry, inode);

	/* Force a full look up अगरf the parent directory has changed */
	अगर (!(flags & (LOOKUP_EXCL | LOOKUP_REVAL)) &&
	    nfs_check_verअगरier(dir, dentry, flags & LOOKUP_RCU)) अणु
		error = nfs_lookup_verअगरy_inode(inode, flags);
		अगर (error) अणु
			अगर (error == -ESTALE)
				nfs_mark_dir_क्रम_revalidate(dir);
			जाओ out_bad;
		पूर्ण
		nfs_advise_use_सूची_पढ़ोplus(dir);
		जाओ out_valid;
	पूर्ण

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	अगर (NFS_STALE(inode))
		जाओ out_bad;

	trace_nfs_lookup_revalidate_enter(dir, dentry, flags);
	error = nfs_lookup_revalidate_dentry(dir, dentry, inode);
	trace_nfs_lookup_revalidate_निकास(dir, dentry, flags, error);
	वापस error;
out_valid:
	वापस nfs_lookup_revalidate_करोne(dir, dentry, inode, 1);
out_bad:
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;
	वापस nfs_lookup_revalidate_करोne(dir, dentry, inode, 0);
पूर्ण

अटल पूर्णांक
__nfs_lookup_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags,
			पूर्णांक (*reval)(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक))
अणु
	काष्ठा dentry *parent;
	काष्ठा inode *dir;
	पूर्णांक ret;

	अगर (flags & LOOKUP_RCU) अणु
		parent = READ_ONCE(dentry->d_parent);
		dir = d_inode_rcu(parent);
		अगर (!dir)
			वापस -ECHILD;
		ret = reval(dir, dentry, flags);
		अगर (parent != READ_ONCE(dentry->d_parent))
			वापस -ECHILD;
	पूर्ण अन्यथा अणु
		parent = dget_parent(dentry);
		ret = reval(d_inode(parent), dentry, flags);
		dput(parent);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_lookup_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस __nfs_lookup_revalidate(dentry, flags, nfs_करो_lookup_revalidate);
पूर्ण

/*
 * A weaker क्रमm of d_revalidate क्रम revalidating just the d_inode(dentry)
 * when we करोn't really care about the dentry name. This is called when a
 * pathwalk ends on a dentry that was not found via a normal lookup in the
 * parent dir (e.g.: ".", "..", procfs symlinks or mountpoपूर्णांक traversals).
 *
 * In this situation, we just want to verअगरy that the inode itself is OK
 * since the dentry might have changed on the server.
 */
अटल पूर्णांक nfs_weak_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error = 0;

	/*
	 * I believe we can only get a negative dentry here in the हाल of a
	 * procfs-style symlink. Just assume it's correct क्रम now, but we may
	 * eventually need to करो something more here.
	 */
	अगर (!inode) अणु
		dfprपूर्णांकk(LOOKUPCACHE, "%s: %pd2 has negative inode\n",
				__func__, dentry);
		वापस 1;
	पूर्ण

	अगर (is_bad_inode(inode)) अणु
		dfprपूर्णांकk(LOOKUPCACHE, "%s: %pd2 has dud inode\n",
				__func__, dentry);
		वापस 0;
	पूर्ण

	error = nfs_lookup_verअगरy_inode(inode, flags);
	dfprपूर्णांकk(LOOKUPCACHE, "NFS: %s: inode %lu is %s\n",
			__func__, inode->i_ino, error ? "invalid" : "valid");
	वापस !error;
पूर्ण

/*
 * This is called from dput() when d_count is going to 0.
 */
अटल पूर्णांक nfs_dentry_delete(स्थिर काष्ठा dentry *dentry)
अणु
	dfprपूर्णांकk(VFS, "NFS: dentry_delete(%pd2, %x)\n",
		dentry, dentry->d_flags);

	/* Unhash any dentry with a stale inode */
	अगर (d_really_is_positive(dentry) && NFS_STALE(d_inode(dentry)))
		वापस 1;

	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED) अणु
		/* Unhash it, so that ->d_iput() would be called */
		वापस 1;
	पूर्ण
	अगर (!(dentry->d_sb->s_flags & SB_ACTIVE)) अणु
		/* Unhash it, so that ancestors of समाप्तed async unlink
		 * files will be cleaned up during umount */
		वापस 1;
	पूर्ण
	वापस 0;

पूर्ण

/* Ensure that we revalidate inode->i_nlink */
अटल व्योम nfs_drop_nlink(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	/* drop the inode अगर we're reasonably sure this is the last link */
	अगर (inode->i_nlink > 0)
		drop_nlink(inode);
	NFS_I(inode)->attr_gencount = nfs_inc_attr_generation_counter();
	nfs_set_cache_invalid(
		inode, NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_CTIME |
			       NFS_INO_INVALID_NLINK);
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * Called when the dentry loses inode.
 * We use it to clean up silly-नामd files.
 */
अटल व्योम nfs_dentry_iput(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अगर (S_ISसूची(inode->i_mode))
		/* drop any सूची_पढ़ो cache as it could easily be old */
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);

	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED) अणु
		nfs_complete_unlink(dentry, inode);
		nfs_drop_nlink(inode);
	पूर्ण
	iput(inode);
पूर्ण

अटल व्योम nfs_d_release(काष्ठा dentry *dentry)
अणु
	/* मुक्त cached devname value, अगर it survived that far */
	अगर (unlikely(dentry->d_fsdata)) अणु
		अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
			WARN_ON(1);
		अन्यथा
			kमुक्त(dentry->d_fsdata);
	पूर्ण
पूर्ण

स्थिर काष्ठा dentry_operations nfs_dentry_operations = अणु
	.d_revalidate	= nfs_lookup_revalidate,
	.d_weak_revalidate	= nfs_weak_revalidate,
	.d_delete	= nfs_dentry_delete,
	.d_iput		= nfs_dentry_iput,
	.d_स्वतःmount	= nfs_d_स्वतःmount,
	.d_release	= nfs_d_release,
पूर्ण;
EXPORT_SYMBOL_GPL(nfs_dentry_operations);

काष्ठा dentry *nfs_lookup(काष्ठा inode *dir, काष्ठा dentry * dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *res;
	काष्ठा inode *inode = शून्य;
	काष्ठा nfs_fh *fhandle = शून्य;
	काष्ठा nfs_fattr *fattr = शून्य;
	काष्ठा nfs4_label *label = शून्य;
	अचिन्हित दीर्घ dir_verअगरier;
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: lookup(%pd2)\n", dentry);
	nfs_inc_stats(dir, NFSIOS_VFSLOOKUP);

	अगर (unlikely(dentry->d_name.len > NFS_SERVER(dir)->namelen))
		वापस ERR_PTR(-ENAMETOOLONG);

	/*
	 * If we're करोing an exclusive create, optimize away the lookup
	 * but करोn't hash the dentry.
	 */
	अगर (nfs_is_exclusive_create(dir, flags) || flags & LOOKUP_RENAME_TARGET)
		वापस शून्य;

	res = ERR_PTR(-ENOMEM);
	fhandle = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	अगर (fhandle == शून्य || fattr == शून्य)
		जाओ out;

	label = nfs4_label_alloc(NFS_SERVER(dir), GFP_NOWAIT);
	अगर (IS_ERR(label))
		जाओ out;

	dir_verअगरier = nfs_save_change_attribute(dir);
	trace_nfs_lookup_enter(dir, dentry, flags);
	error = NFS_PROTO(dir)->lookup(dir, dentry, fhandle, fattr, label);
	अगर (error == -ENOENT)
		जाओ no_entry;
	अगर (error < 0) अणु
		res = ERR_PTR(error);
		जाओ out_label;
	पूर्ण
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr, label);
	res = ERR_CAST(inode);
	अगर (IS_ERR(res))
		जाओ out_label;

	/* Notअगरy सूची_पढ़ो to use READसूचीPLUS */
	nfs_क्रमce_use_सूची_पढ़ोplus(dir);

no_entry:
	res = d_splice_alias(inode, dentry);
	अगर (res != शून्य) अणु
		अगर (IS_ERR(res))
			जाओ out_label;
		dentry = res;
	पूर्ण
	nfs_set_verअगरier(dentry, dir_verअगरier);
out_label:
	trace_nfs_lookup_निकास(dir, dentry, flags, error);
	nfs4_label_मुक्त(label);
out:
	nfs_मुक्त_fattr(fattr);
	nfs_मुक्त_fhandle(fhandle);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_lookup);

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल पूर्णांक nfs4_lookup_revalidate(काष्ठा dentry *, अचिन्हित पूर्णांक);

स्थिर काष्ठा dentry_operations nfs4_dentry_operations = अणु
	.d_revalidate	= nfs4_lookup_revalidate,
	.d_weak_revalidate	= nfs_weak_revalidate,
	.d_delete	= nfs_dentry_delete,
	.d_iput		= nfs_dentry_iput,
	.d_स्वतःmount	= nfs_d_स्वतःmount,
	.d_release	= nfs_d_release,
पूर्ण;
EXPORT_SYMBOL_GPL(nfs4_dentry_operations);

अटल भ_शेषe_t flags_to_mode(पूर्णांक flags)
अणु
	भ_शेषe_t res = (__क्रमce भ_शेषe_t)flags & FMODE_EXEC;
	अगर ((flags & O_ACCMODE) != O_WRONLY)
		res |= FMODE_READ;
	अगर ((flags & O_ACCMODE) != O_RDONLY)
		res |= FMODE_WRITE;
	वापस res;
पूर्ण

अटल काष्ठा nfs_खोलो_context *create_nfs_खोलो_context(काष्ठा dentry *dentry, पूर्णांक खोलो_flags, काष्ठा file *filp)
अणु
	वापस alloc_nfs_खोलो_context(dentry, flags_to_mode(खोलो_flags), filp);
पूर्ण

अटल पूर्णांक करो_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	nfs_fscache_खोलो_file(inode, filp);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_finish_खोलो(काष्ठा nfs_खोलो_context *ctx,
			   काष्ठा dentry *dentry,
			   काष्ठा file *file, अचिन्हित खोलो_flags)
अणु
	पूर्णांक err;

	err = finish_खोलो(file, dentry, करो_खोलो);
	अगर (err)
		जाओ out;
	अगर (S_ISREG(file->f_path.dentry->d_inode->i_mode))
		nfs_file_set_खोलो_context(file, ctx);
	अन्यथा
		err = -EOPENSTALE;
out:
	वापस err;
पूर्ण

पूर्णांक nfs_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		    काष्ठा file *file, अचिन्हित खोलो_flags,
		    umode_t mode)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा dentry *res;
	काष्ठा iattr attr = अणु .ia_valid = ATTR_OPEN पूर्ण;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक lookup_flags = 0;
	bool चयनed = false;
	पूर्णांक created = 0;
	पूर्णांक err;

	/* Expect a negative dentry */
	BUG_ON(d_inode(dentry));

	dfprपूर्णांकk(VFS, "NFS: atomic_open(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	err = nfs_check_flags(खोलो_flags);
	अगर (err)
		वापस err;

	/* NFS only supports OPEN on regular files */
	अगर ((खोलो_flags & O_सूचीECTORY)) अणु
		अगर (!d_in_lookup(dentry)) अणु
			/*
			 * Hashed negative dentry with O_सूचीECTORY: dentry was
			 * revalidated and is fine, no need to perक्रमm lookup
			 * again
			 */
			वापस -ENOENT;
		पूर्ण
		lookup_flags = LOOKUP_OPEN|LOOKUP_सूचीECTORY;
		जाओ no_खोलो;
	पूर्ण

	अगर (dentry->d_name.len > NFS_SERVER(dir)->namelen)
		वापस -ENAMETOOLONG;

	अगर (खोलो_flags & O_CREAT) अणु
		काष्ठा nfs_server *server = NFS_SERVER(dir);

		अगर (!(server->attr_biपंचांगask[2] & FATTR4_WORD2_MODE_UMASK))
			mode &= ~current_umask();

		attr.ia_valid |= ATTR_MODE;
		attr.ia_mode = mode;
	पूर्ण
	अगर (खोलो_flags & O_TRUNC) अणु
		attr.ia_valid |= ATTR_SIZE;
		attr.ia_size = 0;
	पूर्ण

	अगर (!(खोलो_flags & O_CREAT) && !d_in_lookup(dentry)) अणु
		d_drop(dentry);
		चयनed = true;
		dentry = d_alloc_parallel(dentry->d_parent,
					  &dentry->d_name, &wq);
		अगर (IS_ERR(dentry))
			वापस PTR_ERR(dentry);
		अगर (unlikely(!d_in_lookup(dentry)))
			वापस finish_no_खोलो(file, dentry);
	पूर्ण

	ctx = create_nfs_खोलो_context(dentry, खोलो_flags, file);
	err = PTR_ERR(ctx);
	अगर (IS_ERR(ctx))
		जाओ out;

	trace_nfs_atomic_खोलो_enter(dir, ctx, खोलो_flags);
	inode = NFS_PROTO(dir)->खोलो_context(dir, ctx, खोलो_flags, &attr, &created);
	अगर (created)
		file->f_mode |= FMODE_CREATED;
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		trace_nfs_atomic_खोलो_निकास(dir, ctx, खोलो_flags, err);
		put_nfs_खोलो_context(ctx);
		d_drop(dentry);
		चयन (err) अणु
		हाल -ENOENT:
			d_splice_alias(शून्य, dentry);
			nfs_set_verअगरier(dentry, nfs_save_change_attribute(dir));
			अवरोध;
		हाल -EISसूची:
		हाल -ENOTसूची:
			जाओ no_खोलो;
		हाल -ELOOP:
			अगर (!(खोलो_flags & O_NOFOLLOW))
				जाओ no_खोलो;
			अवरोध;
			/* हाल -EINVAL: */
		शेष:
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	err = nfs_finish_खोलो(ctx, ctx->dentry, file, खोलो_flags);
	trace_nfs_atomic_खोलो_निकास(dir, ctx, खोलो_flags, err);
	put_nfs_खोलो_context(ctx);
out:
	अगर (unlikely(चयनed)) अणु
		d_lookup_करोne(dentry);
		dput(dentry);
	पूर्ण
	वापस err;

no_खोलो:
	res = nfs_lookup(dir, dentry, lookup_flags);
	अगर (चयनed) अणु
		d_lookup_करोne(dentry);
		अगर (!res)
			res = dentry;
		अन्यथा
			dput(dentry);
	पूर्ण
	अगर (IS_ERR(res))
		वापस PTR_ERR(res);
	वापस finish_no_खोलो(file, res);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_atomic_खोलो);

अटल पूर्णांक
nfs4_करो_lookup_revalidate(काष्ठा inode *dir, काष्ठा dentry *dentry,
			  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;

	अगर (!(flags & LOOKUP_OPEN) || (flags & LOOKUP_सूचीECTORY))
		जाओ full_reval;
	अगर (d_mountpoपूर्णांक(dentry))
		जाओ full_reval;

	inode = d_inode(dentry);

	/* We can't create new files in nfs_खोलो_revalidate(), so we
	 * optimize away revalidation of negative dentries.
	 */
	अगर (inode == शून्य)
		जाओ full_reval;

	अगर (nfs_verअगरier_is_delegated(dentry))
		वापस nfs_lookup_revalidate_delegated(dir, dentry, inode);

	/* NFS only supports OPEN on regular files */
	अगर (!S_ISREG(inode->i_mode))
		जाओ full_reval;

	/* We cannot करो exclusive creation on a positive dentry */
	अगर (flags & (LOOKUP_EXCL | LOOKUP_REVAL))
		जाओ reval_dentry;

	/* Check अगर the directory changed */
	अगर (!nfs_check_verअगरier(dir, dentry, flags & LOOKUP_RCU))
		जाओ reval_dentry;

	/* Let f_op->खोलो() actually खोलो (and revalidate) the file */
	वापस 1;
reval_dentry:
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;
	वापस nfs_lookup_revalidate_dentry(dir, dentry, inode);

full_reval:
	वापस nfs_करो_lookup_revalidate(dir, dentry, flags);
पूर्ण

अटल पूर्णांक nfs4_lookup_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस __nfs_lookup_revalidate(dentry, flags,
			nfs4_करो_lookup_revalidate);
पूर्ण

#पूर्ण_अगर /* CONFIG_NFSV4 */

काष्ठा dentry *
nfs_add_or_obtain(काष्ठा dentry *dentry, काष्ठा nfs_fh *fhandle,
				काष्ठा nfs_fattr *fattr,
				काष्ठा nfs4_label *label)
अणु
	काष्ठा dentry *parent = dget_parent(dentry);
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा inode *inode;
	काष्ठा dentry *d;
	पूर्णांक error;

	d_drop(dentry);

	अगर (fhandle->size == 0) अणु
		error = NFS_PROTO(dir)->lookup(dir, dentry, fhandle, fattr, शून्य);
		अगर (error)
			जाओ out_error;
	पूर्ण
	nfs_set_verअगरier(dentry, nfs_save_change_attribute(dir));
	अगर (!(fattr->valid & NFS_ATTR_FATTR)) अणु
		काष्ठा nfs_server *server = NFS_SB(dentry->d_sb);
		error = server->nfs_client->rpc_ops->getattr(server, fhandle,
				fattr, शून्य, शून्य);
		अगर (error < 0)
			जाओ out_error;
	पूर्ण
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr, label);
	d = d_splice_alias(inode, dentry);
out:
	dput(parent);
	वापस d;
out_error:
	d = ERR_PTR(error);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_add_or_obtain);

/*
 * Code common to create, सूची_गढ़ो, and mknod.
 */
पूर्णांक nfs_instantiate(काष्ठा dentry *dentry, काष्ठा nfs_fh *fhandle,
				काष्ठा nfs_fattr *fattr,
				काष्ठा nfs4_label *label)
अणु
	काष्ठा dentry *d;

	d = nfs_add_or_obtain(dentry, fhandle, fattr, label);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	/* Callers करोn't care */
	dput(d);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_instantiate);

/*
 * Following a failed create operation, we drop the dentry rather
 * than retain a negative dentry. This aव्योमs a problem in the event
 * that the operation succeeded on the server, but an error in the
 * reply path made it appear to have failed.
 */
पूर्णांक nfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा iattr attr;
	पूर्णांक खोलो_flags = excl ? O_CREAT | O_EXCL : O_CREAT;
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: create(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_mode = mode;
	attr.ia_valid = ATTR_MODE;

	trace_nfs_create_enter(dir, dentry, खोलो_flags);
	error = NFS_PROTO(dir)->create(dir, dentry, &attr, खोलो_flags);
	trace_nfs_create_निकास(dir, dentry, खोलो_flags, error);
	अगर (error != 0)
		जाओ out_err;
	वापस 0;
out_err:
	d_drop(dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_create);

/*
 * See comments क्रम nfs_proc_create regarding failed operations.
 */
पूर्णांक
nfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	  काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा iattr attr;
	पूर्णांक status;

	dfprपूर्णांकk(VFS, "NFS: mknod(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_mode = mode;
	attr.ia_valid = ATTR_MODE;

	trace_nfs_mknod_enter(dir, dentry);
	status = NFS_PROTO(dir)->mknod(dir, dentry, &attr, rdev);
	trace_nfs_mknod_निकास(dir, dentry, status);
	अगर (status != 0)
		जाओ out_err;
	वापस 0;
out_err:
	d_drop(dentry);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_mknod);

/*
 * See comments क्रम nfs_proc_create regarding failed operations.
 */
पूर्णांक nfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा iattr attr;
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: mkdir(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_valid = ATTR_MODE;
	attr.ia_mode = mode | S_IFसूची;

	trace_nfs_सूची_गढ़ो_enter(dir, dentry);
	error = NFS_PROTO(dir)->सूची_गढ़ो(dir, dentry, &attr);
	trace_nfs_सूची_गढ़ो_निकास(dir, dentry, error);
	अगर (error != 0)
		जाओ out_err;
	वापस 0;
out_err:
	d_drop(dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_सूची_गढ़ो);

अटल व्योम nfs_dentry_handle_enoent(काष्ठा dentry *dentry)
अणु
	अगर (simple_positive(dentry))
		d_delete(dentry);
पूर्ण

पूर्णांक nfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: rmdir(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	trace_nfs_सूची_हटाओ_enter(dir, dentry);
	अगर (d_really_is_positive(dentry)) अणु
		करोwn_ग_लिखो(&NFS_I(d_inode(dentry))->सूची_हटाओ_sem);
		error = NFS_PROTO(dir)->सूची_हटाओ(dir, &dentry->d_name);
		/* Ensure the VFS deletes this inode */
		चयन (error) अणु
		हाल 0:
			clear_nlink(d_inode(dentry));
			अवरोध;
		हाल -ENOENT:
			nfs_dentry_handle_enoent(dentry);
		पूर्ण
		up_ग_लिखो(&NFS_I(d_inode(dentry))->सूची_हटाओ_sem);
	पूर्ण अन्यथा
		error = NFS_PROTO(dir)->सूची_हटाओ(dir, &dentry->d_name);
	trace_nfs_सूची_हटाओ_निकास(dir, dentry, error);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_सूची_हटाओ);

/*
 * Remove a file after making sure there are no pending ग_लिखोs,
 * and after checking that the file has only one user. 
 *
 * We invalidate the attribute cache and मुक्त the inode prior to the operation
 * to aव्योम possible races अगर the server reuses the inode.
 */
अटल पूर्णांक nfs_safe_हटाओ(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error = -EBUSY;
		
	dfprपूर्णांकk(VFS, "NFS: safe_remove(%pd2)\n", dentry);

	/* If the dentry was sillyनामd, we simply call d_delete() */
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED) अणु
		error = 0;
		जाओ out;
	पूर्ण

	trace_nfs_हटाओ_enter(dir, dentry);
	अगर (inode != शून्य) अणु
		error = NFS_PROTO(dir)->हटाओ(dir, dentry);
		अगर (error == 0)
			nfs_drop_nlink(inode);
	पूर्ण अन्यथा
		error = NFS_PROTO(dir)->हटाओ(dir, dentry);
	अगर (error == -ENOENT)
		nfs_dentry_handle_enoent(dentry);
	trace_nfs_हटाओ_निकास(dir, dentry, error);
out:
	वापस error;
पूर्ण

/*  We करो silly नाम. In हाल sillyनाम() वापसs -EBUSY, the inode
 *  beदीर्घs to an active ".nfs..." file and we वापस -EBUSY.
 *
 *  If sillyनाम() वापसs 0, we करो nothing, otherwise we unlink.
 */
पूर्णांक nfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक error;
	पूर्णांक need_rehash = 0;

	dfprपूर्णांकk(VFS, "NFS: unlink(%s/%lu, %pd)\n", dir->i_sb->s_id,
		dir->i_ino, dentry);

	trace_nfs_unlink_enter(dir, dentry);
	spin_lock(&dentry->d_lock);
	अगर (d_count(dentry) > 1) अणु
		spin_unlock(&dentry->d_lock);
		/* Start asynchronous ग_लिखोout of the inode */
		ग_लिखो_inode_now(d_inode(dentry), 0);
		error = nfs_sillyनाम(dir, dentry);
		जाओ out;
	पूर्ण
	अगर (!d_unhashed(dentry)) अणु
		__d_drop(dentry);
		need_rehash = 1;
	पूर्ण
	spin_unlock(&dentry->d_lock);
	error = nfs_safe_हटाओ(dentry);
	अगर (!error || error == -ENOENT) अणु
		nfs_set_verअगरier(dentry, nfs_save_change_attribute(dir));
	पूर्ण अन्यथा अगर (need_rehash)
		d_rehash(dentry);
out:
	trace_nfs_unlink_निकास(dir, dentry, error);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_unlink);

/*
 * To create a symbolic link, most file प्रणालीs instantiate a new inode,
 * add a page to it containing the path, then ग_लिखो it out to the disk
 * using prepare_ग_लिखो/commit_ग_लिखो.
 *
 * Unक्रमtunately the NFS client can't create the in-core inode first
 * because it needs a file handle to create an in-core inode (see
 * fs/nfs/inode.c:nfs_fhget).  We only have a file handle *after* the
 * symlink request has completed on the server.
 *
 * So instead we allocate a raw page, copy the symname पूर्णांकo it, then करो
 * the SYMLINK request with the page as the buffer.  If it succeeds, we
 * now have a new file handle and can instantiate an in-core NFS inode
 * and move the raw page पूर्णांकo its mapping.
 */
पूर्णांक nfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा page *page;
	अक्षर *kaddr;
	काष्ठा iattr attr;
	अचिन्हित पूर्णांक pathlen = म_माप(symname);
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: symlink(%s/%lu, %pd, %s)\n", dir->i_sb->s_id,
		dir->i_ino, dentry, symname);

	अगर (pathlen > PAGE_SIZE)
		वापस -ENAMETOOLONG;

	attr.ia_mode = S_IFLNK | S_IRWXUGO;
	attr.ia_valid = ATTR_MODE;

	page = alloc_page(GFP_USER);
	अगर (!page)
		वापस -ENOMEM;

	kaddr = page_address(page);
	स_नकल(kaddr, symname, pathlen);
	अगर (pathlen < PAGE_SIZE)
		स_रखो(kaddr + pathlen, 0, PAGE_SIZE - pathlen);

	trace_nfs_symlink_enter(dir, dentry);
	error = NFS_PROTO(dir)->symlink(dir, dentry, page, pathlen, &attr);
	trace_nfs_symlink_निकास(dir, dentry, error);
	अगर (error != 0) अणु
		dfprपूर्णांकk(VFS, "NFS: symlink(%s/%lu, %pd, %s) error %d\n",
			dir->i_sb->s_id, dir->i_ino,
			dentry, symname, error);
		d_drop(dentry);
		__मुक्त_page(page);
		वापस error;
	पूर्ण

	/*
	 * No big deal अगर we can't add this page to the page cache here.
	 * READLINK will get the missing page from the server अगर needed.
	 */
	अगर (!add_to_page_cache_lru(page, d_inode(dentry)->i_mapping, 0,
							GFP_KERNEL)) अणु
		SetPageUptodate(page);
		unlock_page(page);
		/*
		 * add_to_page_cache_lru() grअसल an extra page refcount.
		 * Drop it here to aव्योम leaking this page later.
		 */
		put_page(page);
	पूर्ण अन्यथा
		__मुक्त_page(page);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_symlink);

पूर्णांक
nfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक error;

	dfprपूर्णांकk(VFS, "NFS: link(%pd2 -> %pd2)\n",
		old_dentry, dentry);

	trace_nfs_link_enter(inode, dir, dentry);
	d_drop(dentry);
	error = NFS_PROTO(dir)->link(inode, dir, &dentry->d_name);
	अगर (error == 0) अणु
		ihold(inode);
		d_add(dentry, inode);
	पूर्ण
	trace_nfs_link_निकास(inode, dir, dentry, error);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_link);

/*
 * RENAME
 * FIXME: Some nfsds, like the Linux user space nfsd, may generate a
 * dअगरferent file handle क्रम the same inode after a नाम (e.g. when
 * moving to a dअगरferent directory). A fail-safe method to करो so would
 * be to look up old_dir/old_name, create a link to new_dir/new_name and
 * नाम the old file using the sillyनाम stuff. This way, the original
 * file in old_dir will go away when the last process iput()s the inode.
 *
 * FIXED.
 * 
 * It actually works quite well. One needs to have the possibility क्रम
 * at least one ".nfs..." file in each directory the file ever माला_लो
 * moved or linked to which happens स्वतःmagically with the new
 * implementation that only depends on the dcache stuff instead of
 * using the inode layer
 *
 * Unक्रमtunately, things are a little more complicated than indicated
 * above. For a cross-directory move, we want to make sure we can get
 * rid of the old inode after the operation.  This means there must be
 * no pending ग_लिखोs (अगर it's a file), and the use count must be 1.
 * If these conditions are met, we can drop the dentries beक्रमe करोing
 * the नाम.
 */
पूर्णांक nfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
	       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
	       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा dentry *dentry = शून्य, *rehash = शून्य;
	काष्ठा rpc_task *task;
	पूर्णांक error = -EBUSY;

	अगर (flags)
		वापस -EINVAL;

	dfprपूर्णांकk(VFS, "NFS: rename(%pd2 -> %pd2, ct=%d)\n",
		 old_dentry, new_dentry,
		 d_count(new_dentry));

	trace_nfs_नाम_enter(old_dir, old_dentry, new_dir, new_dentry);
	/*
	 * For non-directories, check whether the target is busy and अगर so,
	 * make a copy of the dentry and then करो a silly-नाम. If the
	 * silly-नाम succeeds, the copied dentry is hashed and becomes
	 * the new target.
	 */
	अगर (new_inode && !S_ISसूची(new_inode->i_mode)) अणु
		/*
		 * To prevent any new references to the target during the
		 * नाम, we unhash the dentry in advance.
		 */
		अगर (!d_unhashed(new_dentry)) अणु
			d_drop(new_dentry);
			rehash = new_dentry;
		पूर्ण

		अगर (d_count(new_dentry) > 2) अणु
			पूर्णांक err;

			/* copy the target dentry's name */
			dentry = d_alloc(new_dentry->d_parent,
					 &new_dentry->d_name);
			अगर (!dentry)
				जाओ out;

			/* silly-नाम the existing target ... */
			err = nfs_sillyनाम(new_dir, new_dentry);
			अगर (err)
				जाओ out;

			new_dentry = dentry;
			rehash = शून्य;
			new_inode = शून्य;
		पूर्ण
	पूर्ण

	task = nfs_async_नाम(old_dir, new_dir, old_dentry, new_dentry, शून्य);
	अगर (IS_ERR(task)) अणु
		error = PTR_ERR(task);
		जाओ out;
	पूर्ण

	error = rpc_रुको_क्रम_completion_task(task);
	अगर (error != 0) अणु
		((काष्ठा nfs_नामdata *)task->tk_calldata)->cancelled = 1;
		/* Paired with the atomic_dec_and_test() barrier in rpc_करो_put_task() */
		smp_wmb();
	पूर्ण अन्यथा
		error = task->tk_status;
	rpc_put_task(task);
	/* Ensure the inode attributes are revalidated */
	अगर (error == 0) अणु
		spin_lock(&old_inode->i_lock);
		NFS_I(old_inode)->attr_gencount = nfs_inc_attr_generation_counter();
		nfs_set_cache_invalid(old_inode, NFS_INO_INVALID_CHANGE |
							 NFS_INO_INVALID_CTIME |
							 NFS_INO_REVAL_FORCED);
		spin_unlock(&old_inode->i_lock);
	पूर्ण
out:
	अगर (rehash)
		d_rehash(rehash);
	trace_nfs_नाम_निकास(old_dir, old_dentry,
			new_dir, new_dentry, error);
	अगर (!error) अणु
		अगर (new_inode != शून्य)
			nfs_drop_nlink(new_inode);
		/*
		 * The d_move() should be here instead of in an async RPC completion
		 * handler because we need the proper locks to move the dentry.  If
		 * we're पूर्णांकerrupted by a संकेत, the async RPC completion handler
		 * should mark the directories क्रम revalidation.
		 */
		d_move(old_dentry, new_dentry);
		nfs_set_verअगरier(old_dentry,
					nfs_save_change_attribute(new_dir));
	पूर्ण अन्यथा अगर (error == -ENOENT)
		nfs_dentry_handle_enoent(old_dentry);

	/* new dentry created? */
	अगर (dentry)
		dput(dentry);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_नाम);

अटल DEFINE_SPINLOCK(nfs_access_lru_lock);
अटल LIST_HEAD(nfs_access_lru_list);
अटल atomic_दीर्घ_t nfs_access_nr_entries;

अटल अचिन्हित दीर्घ nfs_access_max_cachesize = 4*1024*1024;
module_param(nfs_access_max_cachesize, uदीर्घ, 0644);
MODULE_PARM_DESC(nfs_access_max_cachesize, "NFS access maximum total cache length");

अटल व्योम nfs_access_मुक्त_entry(काष्ठा nfs_access_entry *entry)
अणु
	put_cred(entry->cred);
	kमुक्त_rcu(entry, rcu_head);
	smp_mb__beक्रमe_atomic();
	atomic_दीर्घ_dec(&nfs_access_nr_entries);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम nfs_access_मुक्त_list(काष्ठा list_head *head)
अणु
	काष्ठा nfs_access_entry *cache;

	जबतक (!list_empty(head)) अणु
		cache = list_entry(head->next, काष्ठा nfs_access_entry, lru);
		list_del(&cache->lru);
		nfs_access_मुक्त_entry(cache);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ
nfs_करो_access_cache_scan(अचिन्हित पूर्णांक nr_to_scan)
अणु
	LIST_HEAD(head);
	काष्ठा nfs_inode *nfsi, *next;
	काष्ठा nfs_access_entry *cache;
	दीर्घ मुक्तd = 0;

	spin_lock(&nfs_access_lru_lock);
	list_क्रम_each_entry_safe(nfsi, next, &nfs_access_lru_list, access_cache_inode_lru) अणु
		काष्ठा inode *inode;

		अगर (nr_to_scan-- == 0)
			अवरोध;
		inode = &nfsi->vfs_inode;
		spin_lock(&inode->i_lock);
		अगर (list_empty(&nfsi->access_cache_entry_lru))
			जाओ हटाओ_lru_entry;
		cache = list_entry(nfsi->access_cache_entry_lru.next,
				काष्ठा nfs_access_entry, lru);
		list_move(&cache->lru, &head);
		rb_erase(&cache->rb_node, &nfsi->access_cache);
		मुक्तd++;
		अगर (!list_empty(&nfsi->access_cache_entry_lru))
			list_move_tail(&nfsi->access_cache_inode_lru,
					&nfs_access_lru_list);
		अन्यथा अणु
हटाओ_lru_entry:
			list_del_init(&nfsi->access_cache_inode_lru);
			smp_mb__beक्रमe_atomic();
			clear_bit(NFS_INO_ACL_LRU_SET, &nfsi->flags);
			smp_mb__after_atomic();
		पूर्ण
		spin_unlock(&inode->i_lock);
	पूर्ण
	spin_unlock(&nfs_access_lru_lock);
	nfs_access_मुक्त_list(&head);
	वापस मुक्तd;
पूर्ण

अचिन्हित दीर्घ
nfs_access_cache_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	पूर्णांक nr_to_scan = sc->nr_to_scan;
	gfp_t gfp_mask = sc->gfp_mask;

	अगर ((gfp_mask & GFP_KERNEL) != GFP_KERNEL)
		वापस SHRINK_STOP;
	वापस nfs_करो_access_cache_scan(nr_to_scan);
पूर्ण


अचिन्हित दीर्घ
nfs_access_cache_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	वापस vfs_pressure_ratio(atomic_दीर्घ_पढ़ो(&nfs_access_nr_entries));
पूर्ण

अटल व्योम
nfs_access_cache_enक्रमce_limit(व्योम)
अणु
	दीर्घ nr_entries = atomic_दीर्घ_पढ़ो(&nfs_access_nr_entries);
	अचिन्हित दीर्घ dअगरf;
	अचिन्हित पूर्णांक nr_to_scan;

	अगर (nr_entries < 0 || nr_entries <= nfs_access_max_cachesize)
		वापस;
	nr_to_scan = 100;
	dअगरf = nr_entries - nfs_access_max_cachesize;
	अगर (dअगरf < nr_to_scan)
		nr_to_scan = dअगरf;
	nfs_करो_access_cache_scan(nr_to_scan);
पूर्ण

अटल व्योम __nfs_access_zap_cache(काष्ठा nfs_inode *nfsi, काष्ठा list_head *head)
अणु
	काष्ठा rb_root *root_node = &nfsi->access_cache;
	काष्ठा rb_node *n;
	काष्ठा nfs_access_entry *entry;

	/* Unhook entries from the cache */
	जबतक ((n = rb_first(root_node)) != शून्य) अणु
		entry = rb_entry(n, काष्ठा nfs_access_entry, rb_node);
		rb_erase(n, root_node);
		list_move(&entry->lru, head);
	पूर्ण
	nfsi->cache_validity &= ~NFS_INO_INVALID_ACCESS;
पूर्ण

व्योम nfs_access_zap_cache(काष्ठा inode *inode)
अणु
	LIST_HEAD(head);

	अगर (test_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags) == 0)
		वापस;
	/* Remove from global LRU init */
	spin_lock(&nfs_access_lru_lock);
	अगर (test_and_clear_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags))
		list_del_init(&NFS_I(inode)->access_cache_inode_lru);

	spin_lock(&inode->i_lock);
	__nfs_access_zap_cache(NFS_I(inode), &head);
	spin_unlock(&inode->i_lock);
	spin_unlock(&nfs_access_lru_lock);
	nfs_access_मुक्त_list(&head);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_access_zap_cache);

अटल काष्ठा nfs_access_entry *nfs_access_search_rbtree(काष्ठा inode *inode, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rb_node *n = NFS_I(inode)->access_cache.rb_node;

	जबतक (n != शून्य) अणु
		काष्ठा nfs_access_entry *entry =
			rb_entry(n, काष्ठा nfs_access_entry, rb_node);
		पूर्णांक cmp = cred_fscmp(cred, entry->cred);

		अगर (cmp < 0)
			n = n->rb_left;
		अन्यथा अगर (cmp > 0)
			n = n->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक nfs_access_get_cached_locked(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, काष्ठा nfs_access_entry *res, bool may_block)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_access_entry *cache;
	bool retry = true;
	पूर्णांक err;

	spin_lock(&inode->i_lock);
	क्रम(;;) अणु
		अगर (nfsi->cache_validity & NFS_INO_INVALID_ACCESS)
			जाओ out_zap;
		cache = nfs_access_search_rbtree(inode, cred);
		err = -ENOENT;
		अगर (cache == शून्य)
			जाओ out;
		/* Found an entry, is our attribute cache valid? */
		अगर (!nfs_check_cache_invalid(inode, NFS_INO_INVALID_ACCESS))
			अवरोध;
		अगर (!retry)
			अवरोध;
		err = -ECHILD;
		अगर (!may_block)
			जाओ out;
		spin_unlock(&inode->i_lock);
		err = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
		अगर (err)
			वापस err;
		spin_lock(&inode->i_lock);
		retry = false;
	पूर्ण
	res->cred = cache->cred;
	res->mask = cache->mask;
	list_move_tail(&cache->lru, &nfsi->access_cache_entry_lru);
	err = 0;
out:
	spin_unlock(&inode->i_lock);
	वापस err;
out_zap:
	spin_unlock(&inode->i_lock);
	nfs_access_zap_cache(inode);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक nfs_access_get_cached_rcu(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, काष्ठा nfs_access_entry *res)
अणु
	/* Only check the most recently वापसed cache entry,
	 * but करो it without locking.
	 */
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_access_entry *cache;
	पूर्णांक err = -ECHILD;
	काष्ठा list_head *lh;

	rcu_पढ़ो_lock();
	अगर (nfsi->cache_validity & NFS_INO_INVALID_ACCESS)
		जाओ out;
	lh = rcu_dereference(list_tail_rcu(&nfsi->access_cache_entry_lru));
	cache = list_entry(lh, काष्ठा nfs_access_entry, lru);
	अगर (lh == &nfsi->access_cache_entry_lru ||
	    cred_fscmp(cred, cache->cred) != 0)
		cache = शून्य;
	अगर (cache == शून्य)
		जाओ out;
	अगर (nfs_check_cache_invalid(inode, NFS_INO_INVALID_ACCESS))
		जाओ out;
	res->cred = cache->cred;
	res->mask = cache->mask;
	err = 0;
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

पूर्णांक nfs_access_get_cached(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, काष्ठा
nfs_access_entry *res, bool may_block)
अणु
	पूर्णांक status;

	status = nfs_access_get_cached_rcu(inode, cred, res);
	अगर (status != 0)
		status = nfs_access_get_cached_locked(inode, cred, res,
		    may_block);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_access_get_cached);

अटल व्योम nfs_access_add_rbtree(काष्ठा inode *inode, काष्ठा nfs_access_entry *set)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा rb_root *root_node = &nfsi->access_cache;
	काष्ठा rb_node **p = &root_node->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा nfs_access_entry *entry;
	पूर्णांक cmp;

	spin_lock(&inode->i_lock);
	जबतक (*p != शून्य) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा nfs_access_entry, rb_node);
		cmp = cred_fscmp(set->cred, entry->cred);

		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &parent->rb_right;
		अन्यथा
			जाओ found;
	पूर्ण
	rb_link_node(&set->rb_node, parent, p);
	rb_insert_color(&set->rb_node, root_node);
	list_add_tail(&set->lru, &nfsi->access_cache_entry_lru);
	spin_unlock(&inode->i_lock);
	वापस;
found:
	rb_replace_node(parent, &set->rb_node, root_node);
	list_add_tail(&set->lru, &nfsi->access_cache_entry_lru);
	list_del(&entry->lru);
	spin_unlock(&inode->i_lock);
	nfs_access_मुक्त_entry(entry);
पूर्ण

व्योम nfs_access_add_cache(काष्ठा inode *inode, काष्ठा nfs_access_entry *set)
अणु
	काष्ठा nfs_access_entry *cache = kदो_स्मृति(माप(*cache), GFP_KERNEL);
	अगर (cache == शून्य)
		वापस;
	RB_CLEAR_NODE(&cache->rb_node);
	cache->cred = get_cred(set->cred);
	cache->mask = set->mask;

	/* The above field assignments must be visible
	 * beक्रमe this item appears on the lru.  We cannot easily
	 * use rcu_assign_poपूर्णांकer, so just क्रमce the memory barrier.
	 */
	smp_wmb();
	nfs_access_add_rbtree(inode, cache);

	/* Update accounting */
	smp_mb__beक्रमe_atomic();
	atomic_दीर्घ_inc(&nfs_access_nr_entries);
	smp_mb__after_atomic();

	/* Add inode to global LRU list */
	अगर (!test_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags)) अणु
		spin_lock(&nfs_access_lru_lock);
		अगर (!test_and_set_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags))
			list_add_tail(&NFS_I(inode)->access_cache_inode_lru,
					&nfs_access_lru_list);
		spin_unlock(&nfs_access_lru_lock);
	पूर्ण
	nfs_access_cache_enक्रमce_limit();
पूर्ण
EXPORT_SYMBOL_GPL(nfs_access_add_cache);

#घोषणा NFS_MAY_READ (NFS_ACCESS_READ)
#घोषणा NFS_MAY_WRITE (NFS_ACCESS_MODIFY | \
		NFS_ACCESS_EXTEND | \
		NFS_ACCESS_DELETE)
#घोषणा NFS_खाता_MAY_WRITE (NFS_ACCESS_MODIFY | \
		NFS_ACCESS_EXTEND)
#घोषणा NFS_सूची_MAY_WRITE NFS_MAY_WRITE
#घोषणा NFS_MAY_LOOKUP (NFS_ACCESS_LOOKUP)
#घोषणा NFS_MAY_EXECUTE (NFS_ACCESS_EXECUTE)
अटल पूर्णांक
nfs_access_calc_mask(u32 access_result, umode_t umode)
अणु
	पूर्णांक mask = 0;

	अगर (access_result & NFS_MAY_READ)
		mask |= MAY_READ;
	अगर (S_ISसूची(umode)) अणु
		अगर ((access_result & NFS_सूची_MAY_WRITE) == NFS_सूची_MAY_WRITE)
			mask |= MAY_WRITE;
		अगर ((access_result & NFS_MAY_LOOKUP) == NFS_MAY_LOOKUP)
			mask |= MAY_EXEC;
	पूर्ण अन्यथा अगर (S_ISREG(umode)) अणु
		अगर ((access_result & NFS_खाता_MAY_WRITE) == NFS_खाता_MAY_WRITE)
			mask |= MAY_WRITE;
		अगर ((access_result & NFS_MAY_EXECUTE) == NFS_MAY_EXECUTE)
			mask |= MAY_EXEC;
	पूर्ण अन्यथा अगर (access_result & NFS_MAY_WRITE)
			mask |= MAY_WRITE;
	वापस mask;
पूर्ण

व्योम nfs_access_set_mask(काष्ठा nfs_access_entry *entry, u32 access_result)
अणु
	entry->mask = access_result;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_access_set_mask);

अटल पूर्णांक nfs_करो_access(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, पूर्णांक mask)
अणु
	काष्ठा nfs_access_entry cache;
	bool may_block = (mask & MAY_NOT_BLOCK) == 0;
	पूर्णांक cache_mask = -1;
	पूर्णांक status;

	trace_nfs_access_enter(inode);

	status = nfs_access_get_cached(inode, cred, &cache, may_block);
	अगर (status == 0)
		जाओ out_cached;

	status = -ECHILD;
	अगर (!may_block)
		जाओ out;

	/*
	 * Determine which access bits we want to ask क्रम...
	 */
	cache.mask = NFS_ACCESS_READ | NFS_ACCESS_MODIFY | NFS_ACCESS_EXTEND;
	अगर (nfs_server_capable(inode, NFS_CAP_XATTR)) अणु
		cache.mask |= NFS_ACCESS_XAREAD | NFS_ACCESS_XAWRITE |
		    NFS_ACCESS_XALIST;
	पूर्ण
	अगर (S_ISसूची(inode->i_mode))
		cache.mask |= NFS_ACCESS_DELETE | NFS_ACCESS_LOOKUP;
	अन्यथा
		cache.mask |= NFS_ACCESS_EXECUTE;
	cache.cred = cred;
	status = NFS_PROTO(inode)->access(inode, &cache);
	अगर (status != 0) अणु
		अगर (status == -ESTALE) अणु
			अगर (!S_ISसूची(inode->i_mode))
				nfs_set_inode_stale(inode);
			अन्यथा
				nfs_zap_caches(inode);
		पूर्ण
		जाओ out;
	पूर्ण
	nfs_access_add_cache(inode, &cache);
out_cached:
	cache_mask = nfs_access_calc_mask(cache.mask, inode->i_mode);
	अगर ((mask & ~cache_mask & (MAY_READ | MAY_WRITE | MAY_EXEC)) != 0)
		status = -EACCES;
out:
	trace_nfs_access_निकास(inode, mask, cache_mask, status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs_खोलो_permission_mask(पूर्णांक खोलोflags)
अणु
	पूर्णांक mask = 0;

	अगर (खोलोflags & __FMODE_EXEC) अणु
		/* ONLY check exec rights */
		mask = MAY_EXEC;
	पूर्ण अन्यथा अणु
		अगर ((खोलोflags & O_ACCMODE) != O_WRONLY)
			mask |= MAY_READ;
		अगर ((खोलोflags & O_ACCMODE) != O_RDONLY)
			mask |= MAY_WRITE;
	पूर्ण

	वापस mask;
पूर्ण

पूर्णांक nfs_may_खोलो(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, पूर्णांक खोलोflags)
अणु
	वापस nfs_करो_access(inode, cred, nfs_खोलो_permission_mask(खोलोflags));
पूर्ण
EXPORT_SYMBOL_GPL(nfs_may_खोलो);

अटल पूर्णांक nfs_execute_ok(काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	पूर्णांक ret = 0;

	अगर (S_ISसूची(inode->i_mode))
		वापस 0;
	अगर (nfs_check_cache_invalid(inode, NFS_INO_INVALID_MODE)) अणु
		अगर (mask & MAY_NOT_BLOCK)
			वापस -ECHILD;
		ret = __nfs_revalidate_inode(server, inode);
	पूर्ण
	अगर (ret == 0 && !execute_ok(inode))
		ret = -EACCES;
	वापस ret;
पूर्ण

पूर्णांक nfs_permission(काष्ठा user_namespace *mnt_userns,
		   काष्ठा inode *inode,
		   पूर्णांक mask)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक res = 0;

	nfs_inc_stats(inode, NFSIOS_VFSACCESS);

	अगर ((mask & (MAY_READ | MAY_WRITE | MAY_EXEC)) == 0)
		जाओ out;
	/* Is this sys_access() ? */
	अगर (mask & (MAY_ACCESS | MAY_CHसूची))
		जाओ क्रमce_lookup;

	चयन (inode->i_mode & S_IFMT) अणु
		हाल S_IFLNK:
			जाओ out;
		हाल S_IFREG:
			अगर ((mask & MAY_OPEN) &&
			   nfs_server_capable(inode, NFS_CAP_ATOMIC_OPEN))
				वापस 0;
			अवरोध;
		हाल S_IFसूची:
			/*
			 * Optimize away all ग_लिखो operations, since the server
			 * will check permissions when we perक्रमm the op.
			 */
			अगर ((mask & MAY_WRITE) && !(mask & MAY_READ))
				जाओ out;
	पूर्ण

क्रमce_lookup:
	अगर (!NFS_PROTO(inode)->access)
		जाओ out_notsup;

	res = nfs_करो_access(inode, cred, mask);
out:
	अगर (!res && (mask & MAY_EXEC))
		res = nfs_execute_ok(inode, mask);

	dfprपूर्णांकk(VFS, "NFS: permission(%s/%lu), mask=0x%x, res=%d\n",
		inode->i_sb->s_id, inode->i_ino, mask, res);
	वापस res;
out_notsup:
	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	res = nfs_revalidate_inode(inode, NFS_INO_INVALID_MODE |
						  NFS_INO_INVALID_OTHER);
	अगर (res == 0)
		res = generic_permission(&init_user_ns, inode, mask);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_permission);
