<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2006  NEC Corporation
 *
 * Created by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा JFFS2_XATTR_IS_CORRUPTED	1

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/mtd/mtd.h>
#समावेश "nodelist.h"
/* -------- xdatum related functions ----------------
 * xattr_datum_hashkey(xprefix, xname, xvalue, xsize)
 *   is used to calcurate xdatum hashkey. The reminder of hashkey पूर्णांकo XATTRINDEX_HASHSIZE is
 *   the index of the xattr name/value pair cache (c->xattrindex).
 * is_xattr_datum_unchecked(c, xd)
 *   वापसs 1, अगर xdatum contains any unchecked raw nodes. अगर all raw nodes are not
 *   unchecked, it वापसs 0.
 * unload_xattr_datum(c, xd)
 *   is used to release xattr name/value pair and detach from c->xattrindex.
 * reclaim_xattr_datum(c)
 *   is used to reclaim xattr name/value pairs on the xattr name/value pair cache when
 *   memory usage by cache is over c->xdatum_mem_threshold. Currently, this threshold
 *   is hard coded as 32KiB.
 * करो_verअगरy_xattr_datum(c, xd)
 *   is used to load the xdatum inक्रमmations without name/value pair from the medium.
 *   It's necessary once, because those inक्रमmations are not collected during mounting
 *   process when EBS is enabled.
 *   0 will be वापसed, अगर success. An negative वापस value means recoverable error, and
 *   positive वापस value means unrecoverable error. Thus, caller must हटाओ this xdatum
 *   and xref when it वापसed positive value.
 * करो_load_xattr_datum(c, xd)
 *   is used to load name/value pair from the medium.
 *   The meanings of वापस value is same as करो_verअगरy_xattr_datum().
 * load_xattr_datum(c, xd)
 *   is used to be as a wrapper of करो_verअगरy_xattr_datum() and करो_load_xattr_datum().
 *   If xd need to call करो_verअगरy_xattr_datum() at first, it's called beक्रमe calling
 *   करो_load_xattr_datum(). The meanings of वापस value is same as करो_verअगरy_xattr_datum().
 * save_xattr_datum(c, xd)
 *   is used to ग_लिखो xdatum to medium. xd->version will be incremented.
 * create_xattr_datum(c, xprefix, xname, xvalue, xsize)
 *   is used to create new xdatum and ग_लिखो to medium.
 * unrefer_xattr_datum(c, xd)
 *   is used to delete a xdatum. When nobody refers this xdatum, JFFS2_XFLAGS_DEAD
 *   is set on xd->flags and chained xattr_dead_list or release it immediately.
 *   In the first हाल, the garbage collector release it later.
 * -------------------------------------------------- */
अटल uपूर्णांक32_t xattr_datum_hashkey(पूर्णांक xprefix, स्थिर अक्षर *xname, स्थिर अक्षर *xvalue, पूर्णांक xsize)
अणु
	पूर्णांक name_len = म_माप(xname);

	वापस crc32(xprefix, xname, name_len) ^ crc32(xprefix, xvalue, xsize);
पूर्ण

अटल पूर्णांक is_xattr_datum_unchecked(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	काष्ठा jffs2_raw_node_ref *raw;
	पूर्णांक rc = 0;

	spin_lock(&c->erase_completion_lock);
	क्रम (raw=xd->node; raw != (व्योम *)xd; raw=raw->next_in_ino) अणु
		अगर (ref_flags(raw) == REF_UNCHECKED) अणु
			rc = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&c->erase_completion_lock);
	वापस rc;
पूर्ण

अटल व्योम unload_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	D1(dbg_xattr("%s: xid=%u, version=%u\n", __func__, xd->xid, xd->version));
	अगर (xd->xname) अणु
		c->xdatum_mem_usage -= (xd->name_len + 1 + xd->value_len);
		kमुक्त(xd->xname);
	पूर्ण

	list_del_init(&xd->xindex);
	xd->hashkey = 0;
	xd->xname = शून्य;
	xd->xvalue = शून्य;
पूर्ण

अटल व्योम reclaim_xattr_datum(काष्ठा jffs2_sb_info *c)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_xattr_datum *xd, *_xd;
	uपूर्णांक32_t target, beक्रमe;
	अटल पूर्णांक index = 0;
	पूर्णांक count;

	अगर (c->xdatum_mem_threshold > c->xdatum_mem_usage)
		वापस;

	beक्रमe = c->xdatum_mem_usage;
	target = c->xdatum_mem_usage * 4 / 5; /* 20% reduction */
	क्रम (count = 0; count < XATTRINDEX_HASHSIZE; count++) अणु
		list_क्रम_each_entry_safe(xd, _xd, &c->xattrindex[index], xindex) अणु
			अगर (xd->flags & JFFS2_XFLAGS_HOT) अणु
				xd->flags &= ~JFFS2_XFLAGS_HOT;
			पूर्ण अन्यथा अगर (!(xd->flags & JFFS2_XFLAGS_BIND)) अणु
				unload_xattr_datum(c, xd);
			पूर्ण
			अगर (c->xdatum_mem_usage <= target)
				जाओ out;
		पूर्ण
		index = (index+1) % XATTRINDEX_HASHSIZE;
	पूर्ण
 out:
	JFFS2_NOTICE("xdatum_mem_usage from %u byte to %u byte (%u byte reclaimed)\n",
		     beक्रमe, c->xdatum_mem_usage, beक्रमe - c->xdatum_mem_usage);
पूर्ण

अटल पूर्णांक करो_verअगरy_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_eraseblock *jeb;
	काष्ठा jffs2_raw_node_ref *raw;
	काष्ठा jffs2_raw_xattr rx;
	माप_प्रकार पढ़ोlen;
	uपूर्णांक32_t crc, offset, totlen;
	पूर्णांक rc;

	spin_lock(&c->erase_completion_lock);
	offset = ref_offset(xd->node);
	अगर (ref_flags(xd->node) == REF_PRISTINE)
		जाओ complete;
	spin_unlock(&c->erase_completion_lock);

	rc = jffs2_flash_पढ़ो(c, offset, माप(rx), &पढ़ोlen, (अक्षर *)&rx);
	अगर (rc || पढ़ोlen != माप(rx)) अणु
		JFFS2_WARNING("jffs2_flash_read()=%d, req=%zu, read=%zu at %#08x\n",
			      rc, माप(rx), पढ़ोlen, offset);
		वापस rc ? rc : -EIO;
	पूर्ण
	crc = crc32(0, &rx, माप(rx) - 4);
	अगर (crc != je32_to_cpu(rx.node_crc)) अणु
		JFFS2_ERROR("node CRC failed at %#08x, read=%#08x, calc=%#08x\n",
			    offset, je32_to_cpu(rx.hdr_crc), crc);
		xd->flags |= JFFS2_XFLAGS_INVALID;
		वापस JFFS2_XATTR_IS_CORRUPTED;
	पूर्ण
	totlen = PAD(माप(rx) + rx.name_len + 1 + je16_to_cpu(rx.value_len));
	अगर (je16_to_cpu(rx.magic) != JFFS2_MAGIC_BITMASK
	    || je16_to_cpu(rx.nodetype) != JFFS2_NODETYPE_XATTR
	    || je32_to_cpu(rx.totlen) != totlen
	    || je32_to_cpu(rx.xid) != xd->xid
	    || je32_to_cpu(rx.version) != xd->version) अणु
		JFFS2_ERROR("inconsistent xdatum at %#08x, magic=%#04x/%#04x, "
			    "nodetype=%#04x/%#04x, totlen=%u/%u, xid=%u/%u, version=%u/%u\n",
			    offset, je16_to_cpu(rx.magic), JFFS2_MAGIC_BITMASK,
			    je16_to_cpu(rx.nodetype), JFFS2_NODETYPE_XATTR,
			    je32_to_cpu(rx.totlen), totlen,
			    je32_to_cpu(rx.xid), xd->xid,
			    je32_to_cpu(rx.version), xd->version);
		xd->flags |= JFFS2_XFLAGS_INVALID;
		वापस JFFS2_XATTR_IS_CORRUPTED;
	पूर्ण
	xd->xprefix = rx.xprefix;
	xd->name_len = rx.name_len;
	xd->value_len = je16_to_cpu(rx.value_len);
	xd->data_crc = je32_to_cpu(rx.data_crc);

	spin_lock(&c->erase_completion_lock);
 complete:
	क्रम (raw=xd->node; raw != (व्योम *)xd; raw=raw->next_in_ino) अणु
		jeb = &c->blocks[ref_offset(raw) / c->sector_size];
		totlen = PAD(ref_totlen(c, jeb, raw));
		अगर (ref_flags(raw) == REF_UNCHECKED) अणु
			c->unchecked_size -= totlen; c->used_size += totlen;
			jeb->unchecked_size -= totlen; jeb->used_size += totlen;
		पूर्ण
		raw->flash_offset = ref_offset(raw) | ((xd->node==raw) ? REF_PRISTINE : REF_NORMAL);
	पूर्ण
	spin_unlock(&c->erase_completion_lock);

	/* unchecked xdatum is chained with c->xattr_unchecked */
	list_del_init(&xd->xindex);

	dbg_xattr("success on verifying xdatum (xid=%u, version=%u)\n",
		  xd->xid, xd->version);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_load_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	अक्षर *data;
	माप_प्रकार पढ़ोlen;
	uपूर्णांक32_t crc, length;
	पूर्णांक i, ret, retry = 0;

	BUG_ON(ref_flags(xd->node) != REF_PRISTINE);
	BUG_ON(!list_empty(&xd->xindex));
 retry:
	length = xd->name_len + 1 + xd->value_len;
	data = kदो_स्मृति(length, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = jffs2_flash_पढ़ो(c, ref_offset(xd->node)+माप(काष्ठा jffs2_raw_xattr),
			       length, &पढ़ोlen, data);

	अगर (ret || length!=पढ़ोlen) अणु
		JFFS2_WARNING("jffs2_flash_read() returned %d, request=%d, readlen=%zu, at %#08x\n",
			      ret, length, पढ़ोlen, ref_offset(xd->node));
		kमुक्त(data);
		वापस ret ? ret : -EIO;
	पूर्ण

	data[xd->name_len] = '\0';
	crc = crc32(0, data, length);
	अगर (crc != xd->data_crc) अणु
		JFFS2_WARNING("node CRC failed (JFFS2_NODETYPE_XATTR)"
			      " at %#08x, read: 0x%08x calculated: 0x%08x\n",
			      ref_offset(xd->node), xd->data_crc, crc);
		kमुक्त(data);
		xd->flags |= JFFS2_XFLAGS_INVALID;
		वापस JFFS2_XATTR_IS_CORRUPTED;
	पूर्ण

	xd->flags |= JFFS2_XFLAGS_HOT;
	xd->xname = data;
	xd->xvalue = data + xd->name_len+1;

	c->xdatum_mem_usage += length;

	xd->hashkey = xattr_datum_hashkey(xd->xprefix, xd->xname, xd->xvalue, xd->value_len);
	i = xd->hashkey % XATTRINDEX_HASHSIZE;
	list_add(&xd->xindex, &c->xattrindex[i]);
	अगर (!retry) अणु
		retry = 1;
		reclaim_xattr_datum(c);
		अगर (!xd->xname)
			जाओ retry;
	पूर्ण

	dbg_xattr("success on loading xdatum (xid=%u, xprefix=%u, xname='%s')\n",
		  xd->xid, xd->xprefix, xd->xname);

	वापस 0;
पूर्ण

अटल पूर्णांक load_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem);
	 * rc < 0 : recoverable error, try again
	 * rc = 0 : success
	 * rc > 0 : Unrecoverable error, this node should be deleted.
	 */
	पूर्णांक rc = 0;

	BUG_ON(xd->flags & JFFS2_XFLAGS_DEAD);
	अगर (xd->xname)
		वापस 0;
	अगर (xd->flags & JFFS2_XFLAGS_INVALID)
		वापस JFFS2_XATTR_IS_CORRUPTED;
	अगर (unlikely(is_xattr_datum_unchecked(c, xd)))
		rc = करो_verअगरy_xattr_datum(c, xd);
	अगर (!rc)
		rc = करो_load_xattr_datum(c, xd);
	वापस rc;
पूर्ण

अटल पूर्णांक save_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_raw_xattr rx;
	काष्ठा kvec vecs[2];
	माप_प्रकार length;
	पूर्णांक rc, totlen;
	uपूर्णांक32_t phys_ofs = ग_लिखो_ofs(c);

	BUG_ON(!xd->xname);
	BUG_ON(xd->flags & (JFFS2_XFLAGS_DEAD|JFFS2_XFLAGS_INVALID));

	vecs[0].iov_base = &rx;
	vecs[0].iov_len = माप(rx);
	vecs[1].iov_base = xd->xname;
	vecs[1].iov_len = xd->name_len + 1 + xd->value_len;
	totlen = vecs[0].iov_len + vecs[1].iov_len;

	/* Setup raw-xattr */
	स_रखो(&rx, 0, माप(rx));
	rx.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rx.nodetype = cpu_to_je16(JFFS2_NODETYPE_XATTR);
	rx.totlen = cpu_to_je32(PAD(totlen));
	rx.hdr_crc = cpu_to_je32(crc32(0, &rx, माप(काष्ठा jffs2_unknown_node) - 4));

	rx.xid = cpu_to_je32(xd->xid);
	rx.version = cpu_to_je32(++xd->version);
	rx.xprefix = xd->xprefix;
	rx.name_len = xd->name_len;
	rx.value_len = cpu_to_je16(xd->value_len);
	rx.data_crc = cpu_to_je32(crc32(0, vecs[1].iov_base, vecs[1].iov_len));
	rx.node_crc = cpu_to_je32(crc32(0, &rx, माप(काष्ठा jffs2_raw_xattr) - 4));

	rc = jffs2_flash_ग_लिखोv(c, vecs, 2, phys_ofs, &length, 0);
	अगर (rc || totlen != length) अणु
		JFFS2_WARNING("jffs2_flash_writev()=%d, req=%u, wrote=%zu, at %#08x\n",
			      rc, totlen, length, phys_ofs);
		rc = rc ? rc : -EIO;
		अगर (length)
			jffs2_add_physical_node_ref(c, phys_ofs | REF_OBSOLETE, PAD(totlen), शून्य);

		वापस rc;
	पूर्ण
	/* success */
	jffs2_add_physical_node_ref(c, phys_ofs | REF_PRISTINE, PAD(totlen), (व्योम *)xd);

	dbg_xattr("success on saving xdatum (xid=%u, version=%u, xprefix=%u, xname='%s')\n",
		  xd->xid, xd->version, xd->xprefix, xd->xname);

	वापस 0;
पूर्ण

अटल काष्ठा jffs2_xattr_datum *create_xattr_datum(काष्ठा jffs2_sb_info *c,
						    पूर्णांक xprefix, स्थिर अक्षर *xname,
						    स्थिर अक्षर *xvalue, पूर्णांक xsize)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_xattr_datum *xd;
	uपूर्णांक32_t hashkey, name_len;
	अक्षर *data;
	पूर्णांक i, rc;

	/* Search xattr_datum has same xname/xvalue by index */
	hashkey = xattr_datum_hashkey(xprefix, xname, xvalue, xsize);
	i = hashkey % XATTRINDEX_HASHSIZE;
	list_क्रम_each_entry(xd, &c->xattrindex[i], xindex) अणु
		अगर (xd->hashkey==hashkey
		    && xd->xprefix==xprefix
		    && xd->value_len==xsize
		    && !म_भेद(xd->xname, xname)
		    && !स_भेद(xd->xvalue, xvalue, xsize)) अणु
			atomic_inc(&xd->refcnt);
			वापस xd;
		पूर्ण
	पूर्ण

	/* Not found, Create NEW XATTR-Cache */
	name_len = म_माप(xname);

	xd = jffs2_alloc_xattr_datum();
	अगर (!xd)
		वापस ERR_PTR(-ENOMEM);

	data = kदो_स्मृति(name_len + 1 + xsize, GFP_KERNEL);
	अगर (!data) अणु
		jffs2_मुक्त_xattr_datum(xd);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	म_नकल(data, xname);
	स_नकल(data + name_len + 1, xvalue, xsize);

	atomic_set(&xd->refcnt, 1);
	xd->xid = ++c->highest_xid;
	xd->flags |= JFFS2_XFLAGS_HOT;
	xd->xprefix = xprefix;

	xd->hashkey = hashkey;
	xd->xname = data;
	xd->xvalue = data + name_len + 1;
	xd->name_len = name_len;
	xd->value_len = xsize;
	xd->data_crc = crc32(0, data, xd->name_len + 1 + xd->value_len);

	rc = save_xattr_datum(c, xd);
	अगर (rc) अणु
		kमुक्त(xd->xname);
		jffs2_मुक्त_xattr_datum(xd);
		वापस ERR_PTR(rc);
	पूर्ण

	/* Insert Hash Index */
	i = hashkey % XATTRINDEX_HASHSIZE;
	list_add(&xd->xindex, &c->xattrindex[i]);

	c->xdatum_mem_usage += (xd->name_len + 1 + xd->value_len);
	reclaim_xattr_datum(c);

	वापस xd;
पूर्ण

अटल व्योम unrefer_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	अगर (atomic_dec_and_lock(&xd->refcnt, &c->erase_completion_lock)) अणु
		unload_xattr_datum(c, xd);
		xd->flags |= JFFS2_XFLAGS_DEAD;
		अगर (xd->node == (व्योम *)xd) अणु
			BUG_ON(!(xd->flags & JFFS2_XFLAGS_INVALID));
			jffs2_मुक्त_xattr_datum(xd);
		पूर्ण अन्यथा अणु
			list_add(&xd->xindex, &c->xattr_dead_list);
		पूर्ण
		spin_unlock(&c->erase_completion_lock);

		dbg_xattr("xdatum(xid=%u, version=%u) was removed.\n",
			  xd->xid, xd->version);
	पूर्ण
पूर्ण

/* -------- xref related functions ------------------
 * verअगरy_xattr_ref(c, ref)
 *   is used to load xref inक्रमmation from medium. Because summary data करोes not
 *   contain xid/ino, it's necessary to verअगरy once जबतक mounting process.
 * save_xattr_ref(c, ref)
 *   is used to ग_लिखो xref to medium. If delete marker is marked, it ग_लिखो
 *   a delete marker of xref पूर्णांकo medium.
 * create_xattr_ref(c, ic, xd)
 *   is used to create a new xref and ग_लिखो to medium.
 * delete_xattr_ref(c, ref)
 *   is used to delete jffs2_xattr_ref. It marks xref XREF_DELETE_MARKER,
 *   and allows GC to reclaim those physical nodes.
 * jffs2_xattr_delete_inode(c, ic)
 *   is called to हटाओ xrefs related to obsolete inode when inode is unlinked.
 * jffs2_xattr_मुक्त_inode(c, ic)
 *   is called to release xattr related objects when unmounting. 
 * check_xattr_ref_inode(c, ic)
 *   is used to confirm inode करोes not have duplicate xattr name/value pair.
 * jffs2_xattr_करो_crccheck_inode(c, ic)
 *   is used to क्रमce xattr data पूर्णांकegrity check during the initial gc scan.
 * -------------------------------------------------- */
अटल पूर्णांक verअगरy_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref)
अणु
	काष्ठा jffs2_eraseblock *jeb;
	काष्ठा jffs2_raw_node_ref *raw;
	काष्ठा jffs2_raw_xref rr;
	माप_प्रकार पढ़ोlen;
	uपूर्णांक32_t crc, offset, totlen;
	पूर्णांक rc;

	spin_lock(&c->erase_completion_lock);
	अगर (ref_flags(ref->node) != REF_UNCHECKED)
		जाओ complete;
	offset = ref_offset(ref->node);
	spin_unlock(&c->erase_completion_lock);

	rc = jffs2_flash_पढ़ो(c, offset, माप(rr), &पढ़ोlen, (अक्षर *)&rr);
	अगर (rc || माप(rr) != पढ़ोlen) अणु
		JFFS2_WARNING("jffs2_flash_read()=%d, req=%zu, read=%zu, at %#08x\n",
			      rc, माप(rr), पढ़ोlen, offset);
		वापस rc ? rc : -EIO;
	पूर्ण
	/* obsolete node */
	crc = crc32(0, &rr, माप(rr) - 4);
	अगर (crc != je32_to_cpu(rr.node_crc)) अणु
		JFFS2_ERROR("node CRC failed at %#08x, read=%#08x, calc=%#08x\n",
			    offset, je32_to_cpu(rr.node_crc), crc);
		वापस JFFS2_XATTR_IS_CORRUPTED;
	पूर्ण
	अगर (je16_to_cpu(rr.magic) != JFFS2_MAGIC_BITMASK
	    || je16_to_cpu(rr.nodetype) != JFFS2_NODETYPE_XREF
	    || je32_to_cpu(rr.totlen) != PAD(माप(rr))) अणु
		JFFS2_ERROR("inconsistent xref at %#08x, magic=%#04x/%#04x, "
			    "nodetype=%#04x/%#04x, totlen=%u/%zu\n",
			    offset, je16_to_cpu(rr.magic), JFFS2_MAGIC_BITMASK,
			    je16_to_cpu(rr.nodetype), JFFS2_NODETYPE_XREF,
			    je32_to_cpu(rr.totlen), PAD(माप(rr)));
		वापस JFFS2_XATTR_IS_CORRUPTED;
	पूर्ण
	ref->ino = je32_to_cpu(rr.ino);
	ref->xid = je32_to_cpu(rr.xid);
	ref->xseqno = je32_to_cpu(rr.xseqno);
	अगर (ref->xseqno > c->highest_xseqno)
		c->highest_xseqno = (ref->xseqno & ~XREF_DELETE_MARKER);

	spin_lock(&c->erase_completion_lock);
 complete:
	क्रम (raw=ref->node; raw != (व्योम *)ref; raw=raw->next_in_ino) अणु
		jeb = &c->blocks[ref_offset(raw) / c->sector_size];
		totlen = PAD(ref_totlen(c, jeb, raw));
		अगर (ref_flags(raw) == REF_UNCHECKED) अणु
			c->unchecked_size -= totlen; c->used_size += totlen;
			jeb->unchecked_size -= totlen; jeb->used_size += totlen;
		पूर्ण
		raw->flash_offset = ref_offset(raw) | ((ref->node==raw) ? REF_PRISTINE : REF_NORMAL);
	पूर्ण
	spin_unlock(&c->erase_completion_lock);

	dbg_xattr("success on verifying xref (ino=%u, xid=%u) at %#08x\n",
		  ref->ino, ref->xid, ref_offset(ref->node));
	वापस 0;
पूर्ण

अटल पूर्णांक save_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_raw_xref rr;
	माप_प्रकार length;
	uपूर्णांक32_t xseqno, phys_ofs = ग_लिखो_ofs(c);
	पूर्णांक ret;

	rr.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rr.nodetype = cpu_to_je16(JFFS2_NODETYPE_XREF);
	rr.totlen = cpu_to_je32(PAD(माप(rr)));
	rr.hdr_crc = cpu_to_je32(crc32(0, &rr, माप(काष्ठा jffs2_unknown_node) - 4));

	xseqno = (c->highest_xseqno += 2);
	अगर (is_xattr_ref_dead(ref)) अणु
		xseqno |= XREF_DELETE_MARKER;
		rr.ino = cpu_to_je32(ref->ino);
		rr.xid = cpu_to_je32(ref->xid);
	पूर्ण अन्यथा अणु
		rr.ino = cpu_to_je32(ref->ic->ino);
		rr.xid = cpu_to_je32(ref->xd->xid);
	पूर्ण
	rr.xseqno = cpu_to_je32(xseqno);
	rr.node_crc = cpu_to_je32(crc32(0, &rr, माप(rr) - 4));

	ret = jffs2_flash_ग_लिखो(c, phys_ofs, माप(rr), &length, (अक्षर *)&rr);
	अगर (ret || माप(rr) != length) अणु
		JFFS2_WARNING("jffs2_flash_write() returned %d, request=%zu, retlen=%zu, at %#08x\n",
			      ret, माप(rr), length, phys_ofs);
		ret = ret ? ret : -EIO;
		अगर (length)
			jffs2_add_physical_node_ref(c, phys_ofs | REF_OBSOLETE, PAD(माप(rr)), शून्य);

		वापस ret;
	पूर्ण
	/* success */
	ref->xseqno = xseqno;
	jffs2_add_physical_node_ref(c, phys_ofs | REF_PRISTINE, PAD(माप(rr)), (व्योम *)ref);

	dbg_xattr("success on saving xref (ino=%u, xid=%u)\n", ref->ic->ino, ref->xd->xid);

	वापस 0;
पूर्ण

अटल काष्ठा jffs2_xattr_ref *create_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic,
						काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_xattr_ref *ref;
	पूर्णांक ret;

	ref = jffs2_alloc_xattr_ref();
	अगर (!ref)
		वापस ERR_PTR(-ENOMEM);
	ref->ic = ic;
	ref->xd = xd;

	ret = save_xattr_ref(c, ref);
	अगर (ret) अणु
		jffs2_मुक्त_xattr_ref(ref);
		वापस ERR_PTR(ret);
	पूर्ण

	/* Chain to inode */
	ref->next = ic->xref;
	ic->xref = ref;

	वापस ref; /* success */
पूर्ण

अटल व्योम delete_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref)
अणु
	/* must be called under करोwn_ग_लिखो(xattr_sem) */
	काष्ठा jffs2_xattr_datum *xd;

	xd = ref->xd;
	ref->xseqno |= XREF_DELETE_MARKER;
	ref->ino = ref->ic->ino;
	ref->xid = ref->xd->xid;
	spin_lock(&c->erase_completion_lock);
	ref->next = c->xref_dead_list;
	c->xref_dead_list = ref;
	spin_unlock(&c->erase_completion_lock);

	dbg_xattr("xref(ino=%u, xid=%u, xseqno=%u) was removed.\n",
		  ref->ino, ref->xid, ref->xseqno);

	unrefer_xattr_datum(c, xd);
पूर्ण

व्योम jffs2_xattr_delete_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic)
अणु
	/* It's called from jffs2_evict_inode() on inode removing.
	   When an inode with XATTR is हटाओd, those XATTRs must be हटाओd. */
	काष्ठा jffs2_xattr_ref *ref, *_ref;

	अगर (!ic || ic->pino_nlink > 0)
		वापस;

	करोwn_ग_लिखो(&c->xattr_sem);
	क्रम (ref = ic->xref; ref; ref = _ref) अणु
		_ref = ref->next;
		delete_xattr_ref(c, ref);
	पूर्ण
	ic->xref = शून्य;
	up_ग_लिखो(&c->xattr_sem);
पूर्ण

व्योम jffs2_xattr_मुक्त_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic)
अणु
	/* It's called from jffs2_मुक्त_ino_caches() until unmounting FS. */
	काष्ठा jffs2_xattr_datum *xd;
	काष्ठा jffs2_xattr_ref *ref, *_ref;

	करोwn_ग_लिखो(&c->xattr_sem);
	क्रम (ref = ic->xref; ref; ref = _ref) अणु
		_ref = ref->next;
		xd = ref->xd;
		अगर (atomic_dec_and_test(&xd->refcnt)) अणु
			unload_xattr_datum(c, xd);
			jffs2_मुक्त_xattr_datum(xd);
		पूर्ण
		jffs2_मुक्त_xattr_ref(ref);
	पूर्ण
	ic->xref = शून्य;
	up_ग_लिखो(&c->xattr_sem);
पूर्ण

अटल पूर्णांक check_xattr_ref_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic)
अणु
	/* success of check_xattr_ref_inode() means that inode (ic) करोse not have
	 * duplicate name/value pairs. If duplicate name/value pair would be found,
	 * one will be हटाओd.
	 */
	काष्ठा jffs2_xattr_ref *ref, *cmp, **pref, **pcmp;
	पूर्णांक rc = 0;

	अगर (likely(ic->flags & INO_FLAGS_XATTR_CHECKED))
		वापस 0;
	करोwn_ग_लिखो(&c->xattr_sem);
 retry:
	rc = 0;
	क्रम (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) अणु
		अगर (!ref->xd->xname) अणु
			rc = load_xattr_datum(c, ref->xd);
			अगर (unlikely(rc > 0)) अणु
				*pref = ref->next;
				delete_xattr_ref(c, ref);
				जाओ retry;
			पूर्ण अन्यथा अगर (unlikely(rc < 0))
				जाओ out;
		पूर्ण
		क्रम (cmp=ref->next, pcmp=&ref->next; cmp; pcmp=&cmp->next, cmp=cmp->next) अणु
			अगर (!cmp->xd->xname) अणु
				ref->xd->flags |= JFFS2_XFLAGS_BIND;
				rc = load_xattr_datum(c, cmp->xd);
				ref->xd->flags &= ~JFFS2_XFLAGS_BIND;
				अगर (unlikely(rc > 0)) अणु
					*pcmp = cmp->next;
					delete_xattr_ref(c, cmp);
					जाओ retry;
				पूर्ण अन्यथा अगर (unlikely(rc < 0))
					जाओ out;
			पूर्ण
			अगर (ref->xd->xprefix == cmp->xd->xprefix
			    && !म_भेद(ref->xd->xname, cmp->xd->xname)) अणु
				अगर (ref->xseqno > cmp->xseqno) अणु
					*pcmp = cmp->next;
					delete_xattr_ref(c, cmp);
				पूर्ण अन्यथा अणु
					*pref = ref->next;
					delete_xattr_ref(c, ref);
				पूर्ण
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण
	ic->flags |= INO_FLAGS_XATTR_CHECKED;
 out:
	up_ग_लिखो(&c->xattr_sem);

	वापस rc;
पूर्ण

व्योम jffs2_xattr_करो_crccheck_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic)
अणु
	check_xattr_ref_inode(c, ic);
पूर्ण

/* -------- xattr subप्रणाली functions ---------------
 * jffs2_init_xattr_subप्रणाली(c)
 *   is used to initialize semaphore and list_head, and some variables.
 * jffs2_find_xattr_datum(c, xid)
 *   is used to lookup xdatum जबतक scanning process.
 * jffs2_clear_xattr_subप्रणाली(c)
 *   is used to release any xattr related objects.
 * jffs2_build_xattr_subप्रणाली(c)
 *   is used to associate xdatum and xref जबतक super block building process.
 * jffs2_setup_xattr_datum(c, xid, version)
 *   is used to insert xdatum जबतक scanning process.
 * -------------------------------------------------- */
व्योम jffs2_init_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c)
अणु
	पूर्णांक i;

	क्रम (i=0; i < XATTRINDEX_HASHSIZE; i++)
		INIT_LIST_HEAD(&c->xattrindex[i]);
	INIT_LIST_HEAD(&c->xattr_unchecked);
	INIT_LIST_HEAD(&c->xattr_dead_list);
	c->xref_dead_list = शून्य;
	c->xref_temp = शून्य;

	init_rwsem(&c->xattr_sem);
	c->highest_xid = 0;
	c->highest_xseqno = 0;
	c->xdatum_mem_usage = 0;
	c->xdatum_mem_threshold = 32 * 1024;	/* Default 32KB */
पूर्ण

अटल काष्ठा jffs2_xattr_datum *jffs2_find_xattr_datum(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t xid)
अणु
	काष्ठा jffs2_xattr_datum *xd;
	पूर्णांक i = xid % XATTRINDEX_HASHSIZE;

	/* It's only used in scanning/building process. */
	BUG_ON(!(c->flags & (JFFS2_SB_FLAG_SCANNING|JFFS2_SB_FLAG_BUILDING)));

	list_क्रम_each_entry(xd, &c->xattrindex[i], xindex) अणु
		अगर (xd->xid==xid)
			वापस xd;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम jffs2_clear_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_xattr_datum *xd, *_xd;
	काष्ठा jffs2_xattr_ref *ref, *_ref;
	पूर्णांक i;

	क्रम (ref=c->xref_temp; ref; ref = _ref) अणु
		_ref = ref->next;
		jffs2_मुक्त_xattr_ref(ref);
	पूर्ण

	क्रम (ref=c->xref_dead_list; ref; ref = _ref) अणु
		_ref = ref->next;
		jffs2_मुक्त_xattr_ref(ref);
	पूर्ण

	क्रम (i=0; i < XATTRINDEX_HASHSIZE; i++) अणु
		list_क्रम_each_entry_safe(xd, _xd, &c->xattrindex[i], xindex) अणु
			list_del(&xd->xindex);
			kमुक्त(xd->xname);
			jffs2_मुक्त_xattr_datum(xd);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(xd, _xd, &c->xattr_dead_list, xindex) अणु
		list_del(&xd->xindex);
		jffs2_मुक्त_xattr_datum(xd);
	पूर्ण
	list_क्रम_each_entry_safe(xd, _xd, &c->xattr_unchecked, xindex) अणु
		list_del(&xd->xindex);
		jffs2_मुक्त_xattr_datum(xd);
	पूर्ण
पूर्ण

#घोषणा XREF_TMPHASH_SIZE	(128)
व्योम jffs2_build_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_xattr_ref *ref, *_ref;
	काष्ठा jffs2_xattr_ref *xref_पंचांगphash[XREF_TMPHASH_SIZE];
	काष्ठा jffs2_xattr_datum *xd, *_xd;
	काष्ठा jffs2_inode_cache *ic;
	काष्ठा jffs2_raw_node_ref *raw;
	पूर्णांक i, xdatum_count = 0, xdatum_unchecked_count = 0, xref_count = 0;
	पूर्णांक xdatum_orphan_count = 0, xref_orphan_count = 0, xref_dead_count = 0;

	BUG_ON(!(c->flags & JFFS2_SB_FLAG_BUILDING));

	/* Phase.1 : Merge same xref */
	क्रम (i=0; i < XREF_TMPHASH_SIZE; i++)
		xref_पंचांगphash[i] = शून्य;
	क्रम (ref=c->xref_temp; ref; ref=_ref) अणु
		काष्ठा jffs2_xattr_ref *पंचांगp;

		_ref = ref->next;
		अगर (ref_flags(ref->node) != REF_PRISTINE) अणु
			अगर (verअगरy_xattr_ref(c, ref)) अणु
				BUG_ON(ref->node->next_in_ino != (व्योम *)ref);
				ref->node->next_in_ino = शून्य;
				jffs2_mark_node_obsolete(c, ref->node);
				jffs2_मुक्त_xattr_ref(ref);
				जारी;
			पूर्ण
		पूर्ण

		i = (ref->ino ^ ref->xid) % XREF_TMPHASH_SIZE;
		क्रम (पंचांगp=xref_पंचांगphash[i]; पंचांगp; पंचांगp=पंचांगp->next) अणु
			अगर (पंचांगp->ino == ref->ino && पंचांगp->xid == ref->xid)
				अवरोध;
		पूर्ण
		अगर (पंचांगp) अणु
			raw = ref->node;
			अगर (ref->xseqno > पंचांगp->xseqno) अणु
				पंचांगp->xseqno = ref->xseqno;
				raw->next_in_ino = पंचांगp->node;
				पंचांगp->node = raw;
			पूर्ण अन्यथा अणु
				raw->next_in_ino = पंचांगp->node->next_in_ino;
				पंचांगp->node->next_in_ino = raw;
			पूर्ण
			jffs2_मुक्त_xattr_ref(ref);
			जारी;
		पूर्ण अन्यथा अणु
			ref->next = xref_पंचांगphash[i];
			xref_पंचांगphash[i] = ref;
		पूर्ण
	पूर्ण
	c->xref_temp = शून्य;

	/* Phase.2 : Bind xref with inode_cache and xattr_datum */
	क्रम (i=0; i < XREF_TMPHASH_SIZE; i++) अणु
		क्रम (ref=xref_पंचांगphash[i]; ref; ref=_ref) अणु
			xref_count++;
			_ref = ref->next;
			अगर (is_xattr_ref_dead(ref)) अणु
				ref->next = c->xref_dead_list;
				c->xref_dead_list = ref;
				xref_dead_count++;
				जारी;
			पूर्ण
			/* At this poपूर्णांक, ref->xid and ref->ino contain XID and inode number.
			   ref->xd and ref->ic are not valid yet. */
			xd = jffs2_find_xattr_datum(c, ref->xid);
			ic = jffs2_get_ino_cache(c, ref->ino);
			अगर (!xd || !ic || !ic->pino_nlink) अणु
				dbg_xattr("xref(ino=%u, xid=%u, xseqno=%u) is orphan.\n",
					  ref->ino, ref->xid, ref->xseqno);
				ref->xseqno |= XREF_DELETE_MARKER;
				ref->next = c->xref_dead_list;
				c->xref_dead_list = ref;
				xref_orphan_count++;
				जारी;
			पूर्ण
			ref->xd = xd;
			ref->ic = ic;
			atomic_inc(&xd->refcnt);
			ref->next = ic->xref;
			ic->xref = ref;
		पूर्ण
	पूर्ण

	/* Phase.3 : Link unchecked xdatum to xattr_unchecked list */
	क्रम (i=0; i < XATTRINDEX_HASHSIZE; i++) अणु
		list_क्रम_each_entry_safe(xd, _xd, &c->xattrindex[i], xindex) अणु
			xdatum_count++;
			list_del_init(&xd->xindex);
			अगर (!atomic_पढ़ो(&xd->refcnt)) अणु
				dbg_xattr("xdatum(xid=%u, version=%u) is orphan.\n",
					  xd->xid, xd->version);
				xd->flags |= JFFS2_XFLAGS_DEAD;
				list_add(&xd->xindex, &c->xattr_unchecked);
				xdatum_orphan_count++;
				जारी;
			पूर्ण
			अगर (is_xattr_datum_unchecked(c, xd)) अणु
				dbg_xattr("unchecked xdatum(xid=%u, version=%u)\n",
					  xd->xid, xd->version);
				list_add(&xd->xindex, &c->xattr_unchecked);
				xdatum_unchecked_count++;
			पूर्ण
		पूर्ण
	पूर्ण
	/* build complete */
	JFFS2_NOTICE("complete building xattr subsystem, %u of xdatum"
		     " (%u unchecked, %u orphan) and "
		     "%u of xref (%u dead, %u orphan) found.\n",
		     xdatum_count, xdatum_unchecked_count, xdatum_orphan_count,
		     xref_count, xref_dead_count, xref_orphan_count);
पूर्ण

काष्ठा jffs2_xattr_datum *jffs2_setup_xattr_datum(काष्ठा jffs2_sb_info *c,
						  uपूर्णांक32_t xid, uपूर्णांक32_t version)
अणु
	काष्ठा jffs2_xattr_datum *xd;

	xd = jffs2_find_xattr_datum(c, xid);
	अगर (!xd) अणु
		xd = jffs2_alloc_xattr_datum();
		अगर (!xd)
			वापस ERR_PTR(-ENOMEM);
		xd->xid = xid;
		xd->version = version;
		अगर (xd->xid > c->highest_xid)
			c->highest_xid = xd->xid;
		list_add_tail(&xd->xindex, &c->xattrindex[xid % XATTRINDEX_HASHSIZE]);
	पूर्ण
	वापस xd;
पूर्ण

/* -------- xattr subप्रणाली functions ---------------
 * xprefix_to_handler(xprefix)
 *   is used to translate xprefix पूर्णांकo xattr_handler.
 * jffs2_listxattr(dentry, buffer, size)
 *   is an implementation of listxattr handler on jffs2.
 * करो_jffs2_getxattr(inode, xprefix, xname, buffer, size)
 *   is an implementation of getxattr handler on jffs2.
 * करो_jffs2_setxattr(inode, xprefix, xname, buffer, size, flags)
 *   is an implementation of setxattr handler on jffs2.
 * -------------------------------------------------- */
स्थिर काष्ठा xattr_handler *jffs2_xattr_handlers[] = अणु
	&jffs2_user_xattr_handler,
#अगर_घोषित CONFIG_JFFS2_FS_SECURITY
	&jffs2_security_xattr_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&jffs2_trusted_xattr_handler,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *xprefix_to_handler(पूर्णांक xprefix) अणु
	स्थिर काष्ठा xattr_handler *ret;

	चयन (xprefix) अणु
	हाल JFFS2_XPREFIX_USER:
		ret = &jffs2_user_xattr_handler;
		अवरोध;
#अगर_घोषित CONFIG_JFFS2_FS_SECURITY
	हाल JFFS2_XPREFIX_SECURITY:
		ret = &jffs2_security_xattr_handler;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_FS_POSIX_ACL
	हाल JFFS2_XPREFIX_ACL_ACCESS:
		ret = &posix_acl_access_xattr_handler;
		अवरोध;
	हाल JFFS2_XPREFIX_ACL_DEFAULT:
		ret = &posix_acl_शेष_xattr_handler;
		अवरोध;
#पूर्ण_अगर
	हाल JFFS2_XPREFIX_TRUSTED:
		ret = &jffs2_trusted_xattr_handler;
		अवरोध;
	शेष:
		ret = शून्य;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

sमाप_प्रकार jffs2_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_inode_cache *ic = f->inocache;
	काष्ठा jffs2_xattr_ref *ref, **pref;
	काष्ठा jffs2_xattr_datum *xd;
	स्थिर काष्ठा xattr_handler *xhandle;
	स्थिर अक्षर *prefix;
	sमाप_प्रकार prefix_len, len, rc;
	पूर्णांक retry = 0;

	rc = check_xattr_ref_inode(c, ic);
	अगर (unlikely(rc))
		वापस rc;

	करोwn_पढ़ो(&c->xattr_sem);
 retry:
	len = 0;
	क्रम (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) अणु
		BUG_ON(ref->ic != ic);
		xd = ref->xd;
		अगर (!xd->xname) अणु
			/* xdatum is unchached */
			अगर (!retry) अणु
				retry = 1;
				up_पढ़ो(&c->xattr_sem);
				करोwn_ग_लिखो(&c->xattr_sem);
				जाओ retry;
			पूर्ण अन्यथा अणु
				rc = load_xattr_datum(c, xd);
				अगर (unlikely(rc > 0)) अणु
					*pref = ref->next;
					delete_xattr_ref(c, ref);
					जाओ retry;
				पूर्ण अन्यथा अगर (unlikely(rc < 0))
					जाओ out;
			पूर्ण
		पूर्ण
		xhandle = xprefix_to_handler(xd->xprefix);
		अगर (!xhandle || (xhandle->list && !xhandle->list(dentry)))
			जारी;
		prefix = xhandle->prefix ?: xhandle->name;
		prefix_len = म_माप(prefix);
		rc = prefix_len + xd->name_len + 1;

		अगर (buffer) अणु
			अगर (rc > size - len) अणु
				rc = -दुस्फल;
				जाओ out;
			पूर्ण
			स_नकल(buffer, prefix, prefix_len);
			buffer += prefix_len;
			स_नकल(buffer, xd->xname, xd->name_len);
			buffer += xd->name_len;
			*buffer++ = 0;
		पूर्ण
		len += rc;
	पूर्ण
	rc = len;
 out:
	अगर (!retry) अणु
		up_पढ़ो(&c->xattr_sem);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&c->xattr_sem);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक करो_jffs2_getxattr(काष्ठा inode *inode, पूर्णांक xprefix, स्थिर अक्षर *xname,
		      अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_inode_cache *ic = f->inocache;
	काष्ठा jffs2_xattr_datum *xd;
	काष्ठा jffs2_xattr_ref *ref, **pref;
	पूर्णांक rc, retry = 0;

	rc = check_xattr_ref_inode(c, ic);
	अगर (unlikely(rc))
		वापस rc;

	करोwn_पढ़ो(&c->xattr_sem);
 retry:
	क्रम (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) अणु
		BUG_ON(ref->ic!=ic);

		xd = ref->xd;
		अगर (xd->xprefix != xprefix)
			जारी;
		अगर (!xd->xname) अणु
			/* xdatum is unchached */
			अगर (!retry) अणु
				retry = 1;
				up_पढ़ो(&c->xattr_sem);
				करोwn_ग_लिखो(&c->xattr_sem);
				जाओ retry;
			पूर्ण अन्यथा अणु
				rc = load_xattr_datum(c, xd);
				अगर (unlikely(rc > 0)) अणु
					*pref = ref->next;
					delete_xattr_ref(c, ref);
					जाओ retry;
				पूर्ण अन्यथा अगर (unlikely(rc < 0)) अणु
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!म_भेद(xname, xd->xname)) अणु
			rc = xd->value_len;
			अगर (buffer) अणु
				अगर (size < rc) अणु
					rc = -दुस्फल;
				पूर्ण अन्यथा अणु
					स_नकल(buffer, xd->xvalue, rc);
				पूर्ण
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
	rc = -ENODATA;
 out:
	अगर (!retry) अणु
		up_पढ़ो(&c->xattr_sem);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&c->xattr_sem);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक करो_jffs2_setxattr(काष्ठा inode *inode, पूर्णांक xprefix, स्थिर अक्षर *xname,
		      स्थिर अक्षर *buffer, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_inode_cache *ic = f->inocache;
	काष्ठा jffs2_xattr_datum *xd;
	काष्ठा jffs2_xattr_ref *ref, *newref, **pref;
	uपूर्णांक32_t length, request;
	पूर्णांक rc;

	rc = check_xattr_ref_inode(c, ic);
	अगर (unlikely(rc))
		वापस rc;

	request = PAD(माप(काष्ठा jffs2_raw_xattr) + म_माप(xname) + 1 + size);
	rc = jffs2_reserve_space(c, request, &length,
				 ALLOC_NORMAL, JFFS2_SUMMARY_XATTR_SIZE);
	अगर (rc) अणु
		JFFS2_WARNING("jffs2_reserve_space()=%d, request=%u\n", rc, request);
		वापस rc;
	पूर्ण

	/* Find existing xattr */
	करोwn_ग_लिखो(&c->xattr_sem);
 retry:
	क्रम (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) अणु
		xd = ref->xd;
		अगर (xd->xprefix != xprefix)
			जारी;
		अगर (!xd->xname) अणु
			rc = load_xattr_datum(c, xd);
			अगर (unlikely(rc > 0)) अणु
				*pref = ref->next;
				delete_xattr_ref(c, ref);
				जाओ retry;
			पूर्ण अन्यथा अगर (unlikely(rc < 0))
				जाओ out;
		पूर्ण
		अगर (!म_भेद(xd->xname, xname)) अणु
			अगर (flags & XATTR_CREATE) अणु
				rc = -EEXIST;
				जाओ out;
			पूर्ण
			अगर (!buffer) अणु
				ref->ino = ic->ino;
				ref->xid = xd->xid;
				ref->xseqno |= XREF_DELETE_MARKER;
				rc = save_xattr_ref(c, ref);
				अगर (!rc) अणु
					*pref = ref->next;
					spin_lock(&c->erase_completion_lock);
					ref->next = c->xref_dead_list;
					c->xref_dead_list = ref;
					spin_unlock(&c->erase_completion_lock);
					unrefer_xattr_datum(c, xd);
				पूर्ण अन्यथा अणु
					ref->ic = ic;
					ref->xd = xd;
					ref->xseqno &= ~XREF_DELETE_MARKER;
				पूर्ण
				जाओ out;
			पूर्ण
			जाओ found;
		पूर्ण
	पूर्ण
	/* not found */
	अगर (flags & XATTR_REPLACE) अणु
		rc = -ENODATA;
		जाओ out;
	पूर्ण
	अगर (!buffer) अणु
		rc = -ENODATA;
		जाओ out;
	पूर्ण
 found:
	xd = create_xattr_datum(c, xprefix, xname, buffer, size);
	अगर (IS_ERR(xd)) अणु
		rc = PTR_ERR(xd);
		जाओ out;
	पूर्ण
	up_ग_लिखो(&c->xattr_sem);
	jffs2_complete_reservation(c);

	/* create xattr_ref */
	request = PAD(माप(काष्ठा jffs2_raw_xref));
	rc = jffs2_reserve_space(c, request, &length,
				 ALLOC_NORMAL, JFFS2_SUMMARY_XREF_SIZE);
	करोwn_ग_लिखो(&c->xattr_sem);
	अगर (rc) अणु
		JFFS2_WARNING("jffs2_reserve_space()=%d, request=%u\n", rc, request);
		unrefer_xattr_datum(c, xd);
		up_ग_लिखो(&c->xattr_sem);
		वापस rc;
	पूर्ण
	अगर (ref)
		*pref = ref->next;
	newref = create_xattr_ref(c, ic, xd);
	अगर (IS_ERR(newref)) अणु
		अगर (ref) अणु
			ref->next = ic->xref;
			ic->xref = ref;
		पूर्ण
		rc = PTR_ERR(newref);
		unrefer_xattr_datum(c, xd);
	पूर्ण अन्यथा अगर (ref) अणु
		delete_xattr_ref(c, ref);
	पूर्ण
 out:
	up_ग_लिखो(&c->xattr_sem);
	jffs2_complete_reservation(c);
	वापस rc;
पूर्ण

/* -------- garbage collector functions -------------
 * jffs2_garbage_collect_xattr_datum(c, xd, raw)
 *   is used to move xdatum पूर्णांकo new node.
 * jffs2_garbage_collect_xattr_ref(c, ref, raw)
 *   is used to move xref पूर्णांकo new node.
 * jffs2_verअगरy_xattr(c)
 *   is used to call करो_verअगरy_xattr_datum() beक्रमe garbage collecting.
 * jffs2_release_xattr_datum(c, xd)
 *   is used to release an in-memory object of xdatum.
 * jffs2_release_xattr_ref(c, ref)
 *   is used to release an in-memory object of xref.
 * -------------------------------------------------- */
पूर्णांक jffs2_garbage_collect_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd,
				      काष्ठा jffs2_raw_node_ref *raw)
अणु
	uपूर्णांक32_t totlen, length, old_ofs;
	पूर्णांक rc = 0;

	करोwn_ग_लिखो(&c->xattr_sem);
	अगर (xd->node != raw)
		जाओ out;
	अगर (xd->flags & (JFFS2_XFLAGS_DEAD|JFFS2_XFLAGS_INVALID))
		जाओ out;

	rc = load_xattr_datum(c, xd);
	अगर (unlikely(rc)) अणु
		rc = (rc > 0) ? 0 : rc;
		जाओ out;
	पूर्ण
	old_ofs = ref_offset(xd->node);
	totlen = PAD(माप(काष्ठा jffs2_raw_xattr)
			+ xd->name_len + 1 + xd->value_len);
	rc = jffs2_reserve_space_gc(c, totlen, &length, JFFS2_SUMMARY_XATTR_SIZE);
	अगर (rc) अणु
		JFFS2_WARNING("jffs2_reserve_space_gc()=%d, request=%u\n", rc, totlen);
		जाओ out;
	पूर्ण
	rc = save_xattr_datum(c, xd);
	अगर (!rc)
		dbg_xattr("xdatum (xid=%u, version=%u) GC'ed from %#08x to %08x\n",
			  xd->xid, xd->version, old_ofs, ref_offset(xd->node));
 out:
	अगर (!rc)
		jffs2_mark_node_obsolete(c, raw);
	up_ग_लिखो(&c->xattr_sem);
	वापस rc;
पूर्ण

पूर्णांक jffs2_garbage_collect_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref,
				    काष्ठा jffs2_raw_node_ref *raw)
अणु
	uपूर्णांक32_t totlen, length, old_ofs;
	पूर्णांक rc = 0;

	करोwn_ग_लिखो(&c->xattr_sem);
	BUG_ON(!ref->node);

	अगर (ref->node != raw)
		जाओ out;
	अगर (is_xattr_ref_dead(ref) && (raw->next_in_ino == (व्योम *)ref))
		जाओ out;

	old_ofs = ref_offset(ref->node);
	totlen = ref_totlen(c, c->gcblock, ref->node);

	rc = jffs2_reserve_space_gc(c, totlen, &length, JFFS2_SUMMARY_XREF_SIZE);
	अगर (rc) अणु
		JFFS2_WARNING("%s: jffs2_reserve_space_gc() = %d, request = %u\n",
			      __func__, rc, totlen);
		जाओ out;
	पूर्ण
	rc = save_xattr_ref(c, ref);
	अगर (!rc)
		dbg_xattr("xref (ino=%u, xid=%u) GC'ed from %#08x to %08x\n",
			  ref->ic->ino, ref->xd->xid, old_ofs, ref_offset(ref->node));
 out:
	अगर (!rc)
		jffs2_mark_node_obsolete(c, raw);
	up_ग_लिखो(&c->xattr_sem);
	वापस rc;
पूर्ण

पूर्णांक jffs2_verअगरy_xattr(काष्ठा jffs2_sb_info *c)
अणु
	काष्ठा jffs2_xattr_datum *xd, *_xd;
	काष्ठा jffs2_eraseblock *jeb;
	काष्ठा jffs2_raw_node_ref *raw;
	uपूर्णांक32_t totlen;
	पूर्णांक rc;

	करोwn_ग_लिखो(&c->xattr_sem);
	list_क्रम_each_entry_safe(xd, _xd, &c->xattr_unchecked, xindex) अणु
		rc = करो_verअगरy_xattr_datum(c, xd);
		अगर (rc < 0)
			जारी;
		list_del_init(&xd->xindex);
		spin_lock(&c->erase_completion_lock);
		क्रम (raw=xd->node; raw != (व्योम *)xd; raw=raw->next_in_ino) अणु
			अगर (ref_flags(raw) != REF_UNCHECKED)
				जारी;
			jeb = &c->blocks[ref_offset(raw) / c->sector_size];
			totlen = PAD(ref_totlen(c, jeb, raw));
			c->unchecked_size -= totlen; c->used_size += totlen;
			jeb->unchecked_size -= totlen; jeb->used_size += totlen;
			raw->flash_offset = ref_offset(raw)
				| ((xd->node == (व्योम *)raw) ? REF_PRISTINE : REF_NORMAL);
		पूर्ण
		अगर (xd->flags & JFFS2_XFLAGS_DEAD)
			list_add(&xd->xindex, &c->xattr_dead_list);
		spin_unlock(&c->erase_completion_lock);
	पूर्ण
	up_ग_लिखो(&c->xattr_sem);
	वापस list_empty(&c->xattr_unchecked) ? 1 : 0;
पूर्ण

व्योम jffs2_release_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd)
अणु
	/* must be called under spin_lock(&c->erase_completion_lock) */
	अगर (atomic_पढ़ो(&xd->refcnt) || xd->node != (व्योम *)xd)
		वापस;

	list_del(&xd->xindex);
	jffs2_मुक्त_xattr_datum(xd);
पूर्ण

व्योम jffs2_release_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref)
अणु
	/* must be called under spin_lock(&c->erase_completion_lock) */
	काष्ठा jffs2_xattr_ref *पंचांगp, **pपंचांगp;

	अगर (ref->node != (व्योम *)ref)
		वापस;

	क्रम (पंचांगp=c->xref_dead_list, pपंचांगp=&c->xref_dead_list; पंचांगp; pपंचांगp=&पंचांगp->next, पंचांगp=पंचांगp->next) अणु
		अगर (ref == पंचांगp) अणु
			*pपंचांगp = पंचांगp->next;
			अवरोध;
		पूर्ण
	पूर्ण
	jffs2_मुक्त_xattr_ref(ref);
पूर्ण
