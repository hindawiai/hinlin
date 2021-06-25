<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/jffs2.h>
#समावेश "nodelist.h"

/* These are initialised to शून्य in the kernel startup code.
   If you're porting to other operating प्रणालीs, beware */
अटल काष्ठा kmem_cache *full_dnode_slab;
अटल काष्ठा kmem_cache *raw_dirent_slab;
अटल काष्ठा kmem_cache *raw_inode_slab;
अटल काष्ठा kmem_cache *पंचांगp_dnode_info_slab;
अटल काष्ठा kmem_cache *raw_node_ref_slab;
अटल काष्ठा kmem_cache *node_frag_slab;
अटल काष्ठा kmem_cache *inode_cache_slab;
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
अटल काष्ठा kmem_cache *xattr_datum_cache;
अटल काष्ठा kmem_cache *xattr_ref_cache;
#पूर्ण_अगर

पूर्णांक __init jffs2_create_slab_caches(व्योम)
अणु
	full_dnode_slab = kmem_cache_create("jffs2_full_dnode",
					    माप(काष्ठा jffs2_full_dnode),
					    0, 0, शून्य);
	अगर (!full_dnode_slab)
		जाओ err;

	raw_dirent_slab = kmem_cache_create("jffs2_raw_dirent",
					    माप(काष्ठा jffs2_raw_dirent),
					    0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!raw_dirent_slab)
		जाओ err;

	raw_inode_slab = kmem_cache_create("jffs2_raw_inode",
					   माप(काष्ठा jffs2_raw_inode),
					   0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!raw_inode_slab)
		जाओ err;

	पंचांगp_dnode_info_slab = kmem_cache_create("jffs2_tmp_dnode",
						माप(काष्ठा jffs2_पंचांगp_dnode_info),
						0, 0, शून्य);
	अगर (!पंचांगp_dnode_info_slab)
		जाओ err;

	raw_node_ref_slab = kmem_cache_create("jffs2_refblock",
					      माप(काष्ठा jffs2_raw_node_ref) * (REFS_PER_BLOCK + 1),
					      0, 0, शून्य);
	अगर (!raw_node_ref_slab)
		जाओ err;

	node_frag_slab = kmem_cache_create("jffs2_node_frag",
					   माप(काष्ठा jffs2_node_frag),
					   0, 0, शून्य);
	अगर (!node_frag_slab)
		जाओ err;

	inode_cache_slab = kmem_cache_create("jffs2_inode_cache",
					     माप(काष्ठा jffs2_inode_cache),
					     0, 0, शून्य);
	अगर (!inode_cache_slab)
		जाओ err;

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
	xattr_datum_cache = kmem_cache_create("jffs2_xattr_datum",
					     माप(काष्ठा jffs2_xattr_datum),
					     0, 0, शून्य);
	अगर (!xattr_datum_cache)
		जाओ err;

	xattr_ref_cache = kmem_cache_create("jffs2_xattr_ref",
					   माप(काष्ठा jffs2_xattr_ref),
					   0, 0, शून्य);
	अगर (!xattr_ref_cache)
		जाओ err;
#पूर्ण_अगर

	वापस 0;
 err:
	jffs2_destroy_slab_caches();
	वापस -ENOMEM;
पूर्ण

व्योम jffs2_destroy_slab_caches(व्योम)
अणु
	kmem_cache_destroy(full_dnode_slab);
	kmem_cache_destroy(raw_dirent_slab);
	kmem_cache_destroy(raw_inode_slab);
	kmem_cache_destroy(पंचांगp_dnode_info_slab);
	kmem_cache_destroy(raw_node_ref_slab);
	kmem_cache_destroy(node_frag_slab);
	kmem_cache_destroy(inode_cache_slab);
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
	kmem_cache_destroy(xattr_datum_cache);
	kmem_cache_destroy(xattr_ref_cache);
#पूर्ण_अगर
पूर्ण

काष्ठा jffs2_full_dirent *jffs2_alloc_full_dirent(पूर्णांक namesize)
अणु
	काष्ठा jffs2_full_dirent *ret;
	ret = kदो_स्मृति(माप(काष्ठा jffs2_full_dirent) + namesize, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_full_dirent(काष्ठा jffs2_full_dirent *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kमुक्त(x);
पूर्ण

काष्ठा jffs2_full_dnode *jffs2_alloc_full_dnode(व्योम)
अणु
	काष्ठा jffs2_full_dnode *ret;
	ret = kmem_cache_alloc(full_dnode_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_full_dnode(काष्ठा jffs2_full_dnode *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(full_dnode_slab, x);
पूर्ण

काष्ठा jffs2_raw_dirent *jffs2_alloc_raw_dirent(व्योम)
अणु
	काष्ठा jffs2_raw_dirent *ret;
	ret = kmem_cache_alloc(raw_dirent_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_raw_dirent(काष्ठा jffs2_raw_dirent *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(raw_dirent_slab, x);
पूर्ण

काष्ठा jffs2_raw_inode *jffs2_alloc_raw_inode(व्योम)
अणु
	काष्ठा jffs2_raw_inode *ret;
	ret = kmem_cache_alloc(raw_inode_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_raw_inode(काष्ठा jffs2_raw_inode *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(raw_inode_slab, x);
पूर्ण

काष्ठा jffs2_पंचांगp_dnode_info *jffs2_alloc_पंचांगp_dnode_info(व्योम)
अणु
	काष्ठा jffs2_पंचांगp_dnode_info *ret;
	ret = kmem_cache_alloc(पंचांगp_dnode_info_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n",
		ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_पंचांगp_dnode_info(काष्ठा jffs2_पंचांगp_dnode_info *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(पंचांगp_dnode_info_slab, x);
पूर्ण

अटल काष्ठा jffs2_raw_node_ref *jffs2_alloc_refblock(व्योम)
अणु
	काष्ठा jffs2_raw_node_ref *ret;

	ret = kmem_cache_alloc(raw_node_ref_slab, GFP_KERNEL);
	अगर (ret) अणु
		पूर्णांक i = 0;
		क्रम (i=0; i < REFS_PER_BLOCK; i++) अणु
			ret[i].flash_offset = REF_EMPTY_NODE;
			ret[i].next_in_ino = शून्य;
		पूर्ण
		ret[i].flash_offset = REF_LINK_NODE;
		ret[i].next_in_ino = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक jffs2_pपुनः_स्मृति_raw_node_refs(काष्ठा jffs2_sb_info *c,
				 काष्ठा jffs2_eraseblock *jeb, पूर्णांक nr)
अणु
	काष्ठा jffs2_raw_node_ref **p, *ref;
	पूर्णांक i = nr;

	dbg_meदो_स्मृति("%d\n", nr);

	p = &jeb->last_node;
	ref = *p;

	dbg_meदो_स्मृति("Reserving %d refs for block @0x%08x\n", nr, jeb->offset);

	/* If jeb->last_node is really a valid node then skip over it */
	अगर (ref && ref->flash_offset != REF_EMPTY_NODE)
		ref++;

	जबतक (i) अणु
		अगर (!ref) अणु
			dbg_meदो_स्मृति("Allocating new refblock linked from %p\n", p);
			ref = *p = jffs2_alloc_refblock();
			अगर (!ref)
				वापस -ENOMEM;
		पूर्ण
		अगर (ref->flash_offset == REF_LINK_NODE) अणु
			p = &ref->next_in_ino;
			ref = *p;
			जारी;
		पूर्ण
		i--;
		ref++;
	पूर्ण
	jeb->allocated_refs = nr;

	dbg_meदो_स्मृति("Reserved %d refs for block @0x%08x, last_node is %p (%08x,%p)\n",
		  nr, jeb->offset, jeb->last_node, jeb->last_node->flash_offset,
		  jeb->last_node->next_in_ino);

	वापस 0;
पूर्ण

व्योम jffs2_मुक्त_refblock(काष्ठा jffs2_raw_node_ref *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(raw_node_ref_slab, x);
पूर्ण

काष्ठा jffs2_node_frag *jffs2_alloc_node_frag(व्योम)
अणु
	काष्ठा jffs2_node_frag *ret;
	ret = kmem_cache_alloc(node_frag_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_node_frag(काष्ठा jffs2_node_frag *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(node_frag_slab, x);
पूर्ण

काष्ठा jffs2_inode_cache *jffs2_alloc_inode_cache(व्योम)
अणु
	काष्ठा jffs2_inode_cache *ret;
	ret = kmem_cache_alloc(inode_cache_slab, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ret);
	वापस ret;
पूर्ण

व्योम jffs2_मुक्त_inode_cache(काष्ठा jffs2_inode_cache *x)
अणु
	dbg_meदो_स्मृति("%p\n", x);
	kmem_cache_मुक्त(inode_cache_slab, x);
पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
काष्ठा jffs2_xattr_datum *jffs2_alloc_xattr_datum(व्योम)
अणु
	काष्ठा jffs2_xattr_datum *xd;
	xd = kmem_cache_zalloc(xattr_datum_cache, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", xd);
	अगर (!xd)
		वापस शून्य;

	xd->class = RAWNODE_CLASS_XATTR_DATUM;
	xd->node = (व्योम *)xd;
	INIT_LIST_HEAD(&xd->xindex);
	वापस xd;
पूर्ण

व्योम jffs2_मुक्त_xattr_datum(काष्ठा jffs2_xattr_datum *xd)
अणु
	dbg_meदो_स्मृति("%p\n", xd);
	kmem_cache_मुक्त(xattr_datum_cache, xd);
पूर्ण

काष्ठा jffs2_xattr_ref *jffs2_alloc_xattr_ref(व्योम)
अणु
	काष्ठा jffs2_xattr_ref *ref;
	ref = kmem_cache_zalloc(xattr_ref_cache, GFP_KERNEL);
	dbg_meदो_स्मृति("%p\n", ref);
	अगर (!ref)
		वापस शून्य;

	ref->class = RAWNODE_CLASS_XATTR_REF;
	ref->node = (व्योम *)ref;
	वापस ref;
पूर्ण

व्योम jffs2_मुक्त_xattr_ref(काष्ठा jffs2_xattr_ref *ref)
अणु
	dbg_meदो_स्मृति("%p\n", ref);
	kmem_cache_मुक्त(xattr_ref_cache, ref);
पूर्ण
#पूर्ण_अगर
