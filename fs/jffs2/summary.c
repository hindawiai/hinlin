<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2004  Ferenc Havasi <havasi@inf.u-szeged.hu>,
 *		     Zoltan Sogor <weth@inf.u-szeged.hu>,
 *		     Patrik Kluba <pajko@halom.u-szeged.hu>,
 *		     University of Szeged, Hungary
 *	       2006  KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/compiler.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "nodelist.h"
#समावेश "debug.h"

पूर्णांक jffs2_sum_init(काष्ठा jffs2_sb_info *c)
अणु
	uपूर्णांक32_t sum_size = min_t(uपूर्णांक32_t, c->sector_size, MAX_SUMMARY_SIZE);

	c->summary = kzalloc(माप(काष्ठा jffs2_summary), GFP_KERNEL);

	अगर (!c->summary) अणु
		JFFS2_WARNING("Can't allocate memory for summary information!\n");
		वापस -ENOMEM;
	पूर्ण

	c->summary->sum_buf = kदो_स्मृति(sum_size, GFP_KERNEL);

	अगर (!c->summary->sum_buf) अणु
		JFFS2_WARNING("Can't allocate buffer for writing out summary information!\n");
		kमुक्त(c->summary);
		वापस -ENOMEM;
	पूर्ण

	dbg_summary("returned successfully\n");

	वापस 0;
पूर्ण

व्योम jffs2_sum_निकास(काष्ठा jffs2_sb_info *c)
अणु
	dbg_summary("called\n");

	jffs2_sum_disable_collecting(c->summary);

	kमुक्त(c->summary->sum_buf);
	c->summary->sum_buf = शून्य;

	kमुक्त(c->summary);
	c->summary = शून्य;
पूर्ण

अटल पूर्णांक jffs2_sum_add_mem(काष्ठा jffs2_summary *s, जोड़ jffs2_sum_mem *item)
अणु
	अगर (!s->sum_list_head)
		s->sum_list_head = (जोड़ jffs2_sum_mem *) item;
	अगर (s->sum_list_tail)
		s->sum_list_tail->u.next = (जोड़ jffs2_sum_mem *) item;
	s->sum_list_tail = (जोड़ jffs2_sum_mem *) item;

	चयन (je16_to_cpu(item->u.nodetype)) अणु
		हाल JFFS2_NODETYPE_INODE:
			s->sum_size += JFFS2_SUMMARY_INODE_SIZE;
			s->sum_num++;
			dbg_summary("inode (%u) added to summary\n",
						je32_to_cpu(item->i.inode));
			अवरोध;
		हाल JFFS2_NODETYPE_सूचीENT:
			s->sum_size += JFFS2_SUMMARY_सूचीENT_SIZE(item->d.nsize);
			s->sum_num++;
			dbg_summary("dirent (%u) added to summary\n",
						je32_to_cpu(item->d.ino));
			अवरोध;
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
		हाल JFFS2_NODETYPE_XATTR:
			s->sum_size += JFFS2_SUMMARY_XATTR_SIZE;
			s->sum_num++;
			dbg_summary("xattr (xid=%u, version=%u) added to summary\n",
				    je32_to_cpu(item->x.xid), je32_to_cpu(item->x.version));
			अवरोध;
		हाल JFFS2_NODETYPE_XREF:
			s->sum_size += JFFS2_SUMMARY_XREF_SIZE;
			s->sum_num++;
			dbg_summary("xref added to summary\n");
			अवरोध;
#पूर्ण_अगर
		शेष:
			JFFS2_WARNING("UNKNOWN node type %u\n",
					    je16_to_cpu(item->u.nodetype));
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/* The following 3 functions are called from scan.c to collect summary info क्रम not बंदd jeb */

पूर्णांक jffs2_sum_add_padding_mem(काष्ठा jffs2_summary *s, uपूर्णांक32_t size)
अणु
	dbg_summary("called with %u\n", size);
	s->sum_padded += size;
	वापस 0;
पूर्ण

पूर्णांक jffs2_sum_add_inode_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_inode *ri,
				uपूर्णांक32_t ofs)
अणु
	काष्ठा jffs2_sum_inode_mem *temp = kदो_स्मृति(माप(काष्ठा jffs2_sum_inode_mem), GFP_KERNEL);

	अगर (!temp)
		वापस -ENOMEM;

	temp->nodetype = ri->nodetype;
	temp->inode = ri->ino;
	temp->version = ri->version;
	temp->offset = cpu_to_je32(ofs); /* relative offset from the beginning of the jeb */
	temp->totlen = ri->totlen;
	temp->next = शून्य;

	वापस jffs2_sum_add_mem(s, (जोड़ jffs2_sum_mem *)temp);
पूर्ण

पूर्णांक jffs2_sum_add_dirent_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_dirent *rd,
				uपूर्णांक32_t ofs)
अणु
	काष्ठा jffs2_sum_dirent_mem *temp =
		kदो_स्मृति(माप(काष्ठा jffs2_sum_dirent_mem) + rd->nsize, GFP_KERNEL);

	अगर (!temp)
		वापस -ENOMEM;

	temp->nodetype = rd->nodetype;
	temp->totlen = rd->totlen;
	temp->offset = cpu_to_je32(ofs);	/* relative from the beginning of the jeb */
	temp->pino = rd->pino;
	temp->version = rd->version;
	temp->ino = rd->ino;
	temp->nsize = rd->nsize;
	temp->type = rd->type;
	temp->next = शून्य;

	स_नकल(temp->name, rd->name, rd->nsize);

	वापस jffs2_sum_add_mem(s, (जोड़ jffs2_sum_mem *)temp);
पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
पूर्णांक jffs2_sum_add_xattr_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_xattr *rx, uपूर्णांक32_t ofs)
अणु
	काष्ठा jffs2_sum_xattr_mem *temp;

	temp = kदो_स्मृति(माप(काष्ठा jffs2_sum_xattr_mem), GFP_KERNEL);
	अगर (!temp)
		वापस -ENOMEM;

	temp->nodetype = rx->nodetype;
	temp->xid = rx->xid;
	temp->version = rx->version;
	temp->offset = cpu_to_je32(ofs);
	temp->totlen = rx->totlen;
	temp->next = शून्य;

	वापस jffs2_sum_add_mem(s, (जोड़ jffs2_sum_mem *)temp);
पूर्ण

पूर्णांक jffs2_sum_add_xref_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_xref *rr, uपूर्णांक32_t ofs)
अणु
	काष्ठा jffs2_sum_xref_mem *temp;

	temp = kदो_स्मृति(माप(काष्ठा jffs2_sum_xref_mem), GFP_KERNEL);
	अगर (!temp)
		वापस -ENOMEM;

	temp->nodetype = rr->nodetype;
	temp->offset = cpu_to_je32(ofs);
	temp->next = शून्य;

	वापस jffs2_sum_add_mem(s, (जोड़ jffs2_sum_mem *)temp);
पूर्ण
#पूर्ण_अगर
/* Cleanup every collected summary inक्रमmation */

अटल व्योम jffs2_sum_clean_collected(काष्ठा jffs2_summary *s)
अणु
	जोड़ jffs2_sum_mem *temp;

	अगर (!s->sum_list_head) अणु
		dbg_summary("already empty\n");
	पूर्ण
	जबतक (s->sum_list_head) अणु
		temp = s->sum_list_head;
		s->sum_list_head = s->sum_list_head->u.next;
		kमुक्त(temp);
	पूर्ण
	s->sum_list_tail = शून्य;
	s->sum_padded = 0;
	s->sum_num = 0;
पूर्ण

व्योम jffs2_sum_reset_collected(काष्ठा jffs2_summary *s)
अणु
	dbg_summary("called\n");
	jffs2_sum_clean_collected(s);
	s->sum_size = 0;
पूर्ण

व्योम jffs2_sum_disable_collecting(काष्ठा jffs2_summary *s)
अणु
	dbg_summary("called\n");
	jffs2_sum_clean_collected(s);
	s->sum_size = JFFS2_SUMMARY_NOSUM_SIZE;
पूर्ण

पूर्णांक jffs2_sum_is_disabled(काष्ठा jffs2_summary *s)
अणु
	वापस (s->sum_size == JFFS2_SUMMARY_NOSUM_SIZE);
पूर्ण

/* Move the collected summary inक्रमmation पूर्णांकo sb (called from scan.c) */

व्योम jffs2_sum_move_collected(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_summary *s)
अणु
	dbg_summary("oldsize=0x%x oldnum=%u => newsize=0x%x newnum=%u\n",
				c->summary->sum_size, c->summary->sum_num,
				s->sum_size, s->sum_num);

	c->summary->sum_size = s->sum_size;
	c->summary->sum_num = s->sum_num;
	c->summary->sum_padded = s->sum_padded;
	c->summary->sum_list_head = s->sum_list_head;
	c->summary->sum_list_tail = s->sum_list_tail;

	s->sum_list_head = s->sum_list_tail = शून्य;
पूर्ण

/* Called from wbuf.c to collect ग_लिखोd node info */

पूर्णांक jffs2_sum_add_kvec(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *invecs,
				अचिन्हित दीर्घ count, uपूर्णांक32_t ofs)
अणु
	जोड़ jffs2_node_जोड़ *node;
	काष्ठा jffs2_eraseblock *jeb;

	अगर (c->summary->sum_size == JFFS2_SUMMARY_NOSUM_SIZE) अणु
		dbg_summary("Summary is disabled for this jeb! Skipping summary info!\n");
		वापस 0;
	पूर्ण

	node = invecs[0].iov_base;
	jeb = &c->blocks[ofs / c->sector_size];
	ofs -= jeb->offset;

	चयन (je16_to_cpu(node->u.nodetype)) अणु
		हाल JFFS2_NODETYPE_INODE: अणु
			काष्ठा jffs2_sum_inode_mem *temp =
				kदो_स्मृति(माप(काष्ठा jffs2_sum_inode_mem), GFP_KERNEL);

			अगर (!temp)
				जाओ no_mem;

			temp->nodetype = node->i.nodetype;
			temp->inode = node->i.ino;
			temp->version = node->i.version;
			temp->offset = cpu_to_je32(ofs);
			temp->totlen = node->i.totlen;
			temp->next = शून्य;

			वापस jffs2_sum_add_mem(c->summary, (जोड़ jffs2_sum_mem *)temp);
		पूर्ण

		हाल JFFS2_NODETYPE_सूचीENT: अणु
			काष्ठा jffs2_sum_dirent_mem *temp =
				kदो_स्मृति(माप(काष्ठा jffs2_sum_dirent_mem) + node->d.nsize, GFP_KERNEL);

			अगर (!temp)
				जाओ no_mem;

			temp->nodetype = node->d.nodetype;
			temp->totlen = node->d.totlen;
			temp->offset = cpu_to_je32(ofs);
			temp->pino = node->d.pino;
			temp->version = node->d.version;
			temp->ino = node->d.ino;
			temp->nsize = node->d.nsize;
			temp->type = node->d.type;
			temp->next = शून्य;

			चयन (count) अणु
				हाल 1:
					स_नकल(temp->name,node->d.name,node->d.nsize);
					अवरोध;

				हाल 2:
					स_नकल(temp->name,invecs[1].iov_base,node->d.nsize);
					अवरोध;

				शेष:
					BUG();	/* impossible count value */
					अवरोध;
			पूर्ण

			वापस jffs2_sum_add_mem(c->summary, (जोड़ jffs2_sum_mem *)temp);
		पूर्ण
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
		हाल JFFS2_NODETYPE_XATTR: अणु
			काष्ठा jffs2_sum_xattr_mem *temp;
			temp = kदो_स्मृति(माप(काष्ठा jffs2_sum_xattr_mem), GFP_KERNEL);
			अगर (!temp)
				जाओ no_mem;

			temp->nodetype = node->x.nodetype;
			temp->xid = node->x.xid;
			temp->version = node->x.version;
			temp->totlen = node->x.totlen;
			temp->offset = cpu_to_je32(ofs);
			temp->next = शून्य;

			वापस jffs2_sum_add_mem(c->summary, (जोड़ jffs2_sum_mem *)temp);
		पूर्ण
		हाल JFFS2_NODETYPE_XREF: अणु
			काष्ठा jffs2_sum_xref_mem *temp;
			temp = kदो_स्मृति(माप(काष्ठा jffs2_sum_xref_mem), GFP_KERNEL);
			अगर (!temp)
				जाओ no_mem;
			temp->nodetype = node->r.nodetype;
			temp->offset = cpu_to_je32(ofs);
			temp->next = शून्य;

			वापस jffs2_sum_add_mem(c->summary, (जोड़ jffs2_sum_mem *)temp);
		पूर्ण
#पूर्ण_अगर
		हाल JFFS2_NODETYPE_PADDING:
			dbg_summary("node PADDING\n");
			c->summary->sum_padded += je32_to_cpu(node->u.totlen);
			अवरोध;

		हाल JFFS2_NODETYPE_CLEANMARKER:
			dbg_summary("node CLEANMARKER\n");
			अवरोध;

		हाल JFFS2_NODETYPE_SUMMARY:
			dbg_summary("node SUMMARY\n");
			अवरोध;

		शेष:
			/* If you implement a new node type you should also implement
			   summary support क्रम it or disable summary.
			*/
			BUG();
			अवरोध;
	पूर्ण

	वापस 0;

no_mem:
	JFFS2_WARNING("MEMORY ALLOCATION ERROR!");
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा jffs2_raw_node_ref *sum_link_node_ref(काष्ठा jffs2_sb_info *c,
						    काष्ठा jffs2_eraseblock *jeb,
						    uपूर्णांक32_t ofs, uपूर्णांक32_t len,
						    काष्ठा jffs2_inode_cache *ic)
अणु
	/* If there was a gap, mark it dirty */
	अगर ((ofs & ~3) > c->sector_size - jeb->मुक्त_size) अणु
		/* Ew. Summary करोesn't actually tell us explicitly about dirty space */
		jffs2_scan_dirty_space(c, jeb, (ofs & ~3) - (c->sector_size - jeb->मुक्त_size));
	पूर्ण

	वापस jffs2_link_node_ref(c, jeb, jeb->offset + ofs, len, ic);
पूर्ण

/* Process the stored summary inक्रमmation - helper function क्रम jffs2_sum_scan_sumnode() */

अटल पूर्णांक jffs2_sum_process_sum_data(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				काष्ठा jffs2_raw_summary *summary, uपूर्णांक32_t *pseuकरो_अक्रमom)
अणु
	काष्ठा jffs2_inode_cache *ic;
	काष्ठा jffs2_full_dirent *fd;
	व्योम *sp;
	पूर्णांक i, ino;
	पूर्णांक err;

	sp = summary->sum;

	क्रम (i=0; i<je32_to_cpu(summary->sum_num); i++) अणु
		dbg_summary("processing summary index %d\n", i);

		cond_resched();

		/* Make sure there's a spare ref क्रम dirty space */
		err = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 2);
		अगर (err)
			वापस err;

		चयन (je16_to_cpu(((काष्ठा jffs2_sum_unknown_flash *)sp)->nodetype)) अणु
			हाल JFFS2_NODETYPE_INODE: अणु
				काष्ठा jffs2_sum_inode_flash *spi;
				spi = sp;

				ino = je32_to_cpu(spi->inode);

				dbg_summary("Inode at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spi->offset),
					    jeb->offset + je32_to_cpu(spi->offset) + je32_to_cpu(spi->totlen));

				ic = jffs2_scan_make_ino_cache(c, ino);
				अगर (!ic) अणु
					JFFS2_NOTICE("scan_make_ino_cache failed\n");
					वापस -ENOMEM;
				पूर्ण

				sum_link_node_ref(c, jeb, je32_to_cpu(spi->offset) | REF_UNCHECKED,
						  PAD(je32_to_cpu(spi->totlen)), ic);

				*pseuकरो_अक्रमom += je32_to_cpu(spi->version);

				sp += JFFS2_SUMMARY_INODE_SIZE;

				अवरोध;
			पूर्ण

			हाल JFFS2_NODETYPE_सूचीENT: अणु
				काष्ठा jffs2_sum_dirent_flash *spd;
				पूर्णांक checkedlen;
				spd = sp;

				dbg_summary("Dirent at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spd->offset),
					    jeb->offset + je32_to_cpu(spd->offset) + je32_to_cpu(spd->totlen));


				/* This should never happen, but https://dev.laptop.org/ticket/4184 */
				checkedlen = strnlen(spd->name, spd->nsize);
				अगर (!checkedlen) अणु
					pr_err("Dirent at %08x has zero at start of name. Aborting mount.\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset));
					वापस -EIO;
				पूर्ण
				अगर (checkedlen < spd->nsize) अणु
					pr_err("Dirent at %08x has zeroes in name. Truncating to %d chars\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset),
					       checkedlen);
				पूर्ण


				fd = jffs2_alloc_full_dirent(checkedlen+1);
				अगर (!fd)
					वापस -ENOMEM;

				स_नकल(&fd->name, spd->name, checkedlen);
				fd->name[checkedlen] = 0;

				ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(spd->pino));
				अगर (!ic) अणु
					jffs2_मुक्त_full_dirent(fd);
					वापस -ENOMEM;
				पूर्ण

				fd->raw = sum_link_node_ref(c, jeb,  je32_to_cpu(spd->offset) | REF_UNCHECKED,
							    PAD(je32_to_cpu(spd->totlen)), ic);

				fd->next = शून्य;
				fd->version = je32_to_cpu(spd->version);
				fd->ino = je32_to_cpu(spd->ino);
				fd->nhash = full_name_hash(शून्य, fd->name, checkedlen);
				fd->type = spd->type;

				jffs2_add_fd_to_list(c, fd, &ic->scan_dents);

				*pseuकरो_अक्रमom += je32_to_cpu(spd->version);

				sp += JFFS2_SUMMARY_सूचीENT_SIZE(spd->nsize);

				अवरोध;
			पूर्ण
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
			हाल JFFS2_NODETYPE_XATTR: अणु
				काष्ठा jffs2_xattr_datum *xd;
				काष्ठा jffs2_sum_xattr_flash *spx;

				spx = (काष्ठा jffs2_sum_xattr_flash *)sp;
				dbg_summary("xattr at %#08x-%#08x (xid=%u, version=%u)\n", 
					    jeb->offset + je32_to_cpu(spx->offset),
					    jeb->offset + je32_to_cpu(spx->offset) + je32_to_cpu(spx->totlen),
					    je32_to_cpu(spx->xid), je32_to_cpu(spx->version));

				xd = jffs2_setup_xattr_datum(c, je32_to_cpu(spx->xid),
								je32_to_cpu(spx->version));
				अगर (IS_ERR(xd))
					वापस PTR_ERR(xd);
				अगर (xd->version > je32_to_cpu(spx->version)) अणु
					/* node is not the newest one */
					काष्ठा jffs2_raw_node_ref *raw
						= sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
								    PAD(je32_to_cpu(spx->totlen)), शून्य);
					raw->next_in_ino = xd->node->next_in_ino;
					xd->node->next_in_ino = raw;
				पूर्ण अन्यथा अणु
					xd->version = je32_to_cpu(spx->version);
					sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
							  PAD(je32_to_cpu(spx->totlen)), (व्योम *)xd);
				पूर्ण
				*pseuकरो_अक्रमom += je32_to_cpu(spx->xid);
				sp += JFFS2_SUMMARY_XATTR_SIZE;

				अवरोध;
			पूर्ण
			हाल JFFS2_NODETYPE_XREF: अणु
				काष्ठा jffs2_xattr_ref *ref;
				काष्ठा jffs2_sum_xref_flash *spr;

				spr = (काष्ठा jffs2_sum_xref_flash *)sp;
				dbg_summary("xref at %#08x-%#08x\n",
					    jeb->offset + je32_to_cpu(spr->offset),
					    jeb->offset + je32_to_cpu(spr->offset) + 
					    (uपूर्णांक32_t)PAD(माप(काष्ठा jffs2_raw_xref)));

				ref = jffs2_alloc_xattr_ref();
				अगर (!ref) अणु
					JFFS2_NOTICE("allocation of xattr_datum failed\n");
					वापस -ENOMEM;
				पूर्ण
				ref->next = c->xref_temp;
				c->xref_temp = ref;

				sum_link_node_ref(c, jeb, je32_to_cpu(spr->offset) | REF_UNCHECKED,
						  PAD(माप(काष्ठा jffs2_raw_xref)), (व्योम *)ref);

				*pseuकरो_अक्रमom += ref->node->flash_offset;
				sp += JFFS2_SUMMARY_XREF_SIZE;

				अवरोध;
			पूर्ण
#पूर्ण_अगर
			शेष : अणु
				uपूर्णांक16_t nodetype = je16_to_cpu(((काष्ठा jffs2_sum_unknown_flash *)sp)->nodetype);
				JFFS2_WARNING("Unsupported node type %x found in summary! Exiting...\n", nodetype);
				अगर ((nodetype & JFFS2_COMPAT_MASK) == JFFS2_FEATURE_INCOMPAT)
					वापस -EIO;

				/* For compatible node types, just fall back to the full scan */
				c->wasted_size -= jeb->wasted_size;
				c->मुक्त_size += c->sector_size - jeb->मुक्त_size;
				c->used_size -= jeb->used_size;
				c->dirty_size -= jeb->dirty_size;
				jeb->wasted_size = jeb->used_size = jeb->dirty_size = 0;
				jeb->मुक्त_size = c->sector_size;

				jffs2_मुक्त_jeb_node_refs(c, jeb);
				वापस -ENOTRECOVERABLE;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Process the summary node - called from jffs2_scan_eraseblock() */
पूर्णांक jffs2_sum_scan_sumnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
			   काष्ठा jffs2_raw_summary *summary, uपूर्णांक32_t sumsize,
			   uपूर्णांक32_t *pseuकरो_अक्रमom)
अणु
	काष्ठा jffs2_unknown_node crcnode;
	पूर्णांक ret, ofs;
	uपूर्णांक32_t crc;

	ofs = c->sector_size - sumsize;

	dbg_summary("summary found for 0x%08x at 0x%08x (0x%x bytes)\n",
		    jeb->offset, jeb->offset + ofs, sumsize);

	/* OK, now check क्रम node validity and CRC */
	crcnode.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	crcnode.nodetype = cpu_to_je16(JFFS2_NODETYPE_SUMMARY);
	crcnode.totlen = summary->totlen;
	crc = crc32(0, &crcnode, माप(crcnode)-4);

	अगर (je32_to_cpu(summary->hdr_crc) != crc) अणु
		dbg_summary("Summary node header is corrupt (bad CRC or "
				"no summary at all)\n");
		जाओ crc_err;
	पूर्ण

	अगर (je32_to_cpu(summary->totlen) != sumsize) अणु
		dbg_summary("Summary node is corrupt (wrong erasesize?)\n");
		जाओ crc_err;
	पूर्ण

	crc = crc32(0, summary, माप(काष्ठा jffs2_raw_summary)-8);

	अगर (je32_to_cpu(summary->node_crc) != crc) अणु
		dbg_summary("Summary node is corrupt (bad CRC)\n");
		जाओ crc_err;
	पूर्ण

	crc = crc32(0, summary->sum, sumsize - माप(काष्ठा jffs2_raw_summary));

	अगर (je32_to_cpu(summary->sum_crc) != crc) अणु
		dbg_summary("Summary node data is corrupt (bad CRC)\n");
		जाओ crc_err;
	पूर्ण

	अगर ( je32_to_cpu(summary->cln_mkr) ) अणु

		dbg_summary("Summary : CLEANMARKER node \n");

		ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1);
		अगर (ret)
			वापस ret;

		अगर (je32_to_cpu(summary->cln_mkr) != c->cleanmarker_size) अणु
			dbg_summary("CLEANMARKER node has totlen 0x%x != normal 0x%x\n",
				je32_to_cpu(summary->cln_mkr), c->cleanmarker_size);
			अगर ((ret = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(summary->cln_mkr)))))
				वापस ret;
		पूर्ण अन्यथा अगर (jeb->first_node) अणु
			dbg_summary("CLEANMARKER node not first node in block "
					"(0x%08x)\n", jeb->offset);
			अगर ((ret = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(summary->cln_mkr)))))
				वापस ret;
		पूर्ण अन्यथा अणु
			jffs2_link_node_ref(c, jeb, jeb->offset | REF_NORMAL,
					    je32_to_cpu(summary->cln_mkr), शून्य);
		पूर्ण
	पूर्ण

	ret = jffs2_sum_process_sum_data(c, jeb, summary, pseuकरो_अक्रमom);
	/* -ENOTRECOVERABLE isn't a fatal error -- it means we should करो a full
	   scan of this eraseblock. So वापस zero */
	अगर (ret == -ENOTRECOVERABLE)
		वापस 0;
	अगर (ret)
		वापस ret;		/* real error */

	/* क्रम PARANOIA_CHECK */
	ret = jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 2);
	अगर (ret)
		वापस ret;

	sum_link_node_ref(c, jeb, ofs | REF_NORMAL, sumsize, शून्य);

	अगर (unlikely(jeb->मुक्त_size)) अणु
		JFFS2_WARNING("Free size 0x%x bytes in eraseblock @0x%08x with summary?\n",
			      jeb->मुक्त_size, jeb->offset);
		jeb->wasted_size += jeb->मुक्त_size;
		c->wasted_size += jeb->मुक्त_size;
		c->मुक्त_size -= jeb->मुक्त_size;
		jeb->मुक्त_size = 0;
	पूर्ण

	वापस jffs2_scan_classअगरy_jeb(c, jeb);

crc_err:
	JFFS2_WARNING("Summary node crc error, skipping summary information.\n");

	वापस 0;
पूर्ण

/* Write summary data to flash - helper function क्रम jffs2_sum_ग_लिखो_sumnode() */

अटल पूर्णांक jffs2_sum_ग_लिखो_data(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
				uपूर्णांक32_t infosize, uपूर्णांक32_t datasize, पूर्णांक padsize)
अणु
	काष्ठा jffs2_raw_summary isum;
	जोड़ jffs2_sum_mem *temp;
	काष्ठा jffs2_sum_marker *sm;
	काष्ठा kvec vecs[2];
	uपूर्णांक32_t sum_ofs;
	व्योम *wpage;
	पूर्णांक ret;
	माप_प्रकार retlen;

	अगर (padsize + datasize > MAX_SUMMARY_SIZE) अणु
		/* It won't fit in the buffer. Abort summary क्रम this jeb */
		jffs2_sum_disable_collecting(c->summary);

		JFFS2_WARNING("Summary too big (%d data, %d pad) in eraseblock at %08x\n",
			      datasize, padsize, jeb->offset);
		/* Non-fatal */
		वापस 0;
	पूर्ण
	/* Is there enough space क्रम summary? */
	अगर (padsize < 0) अणु
		/* करोn't try to ग_लिखो out summary क्रम this jeb */
		jffs2_sum_disable_collecting(c->summary);

		JFFS2_WARNING("Not enough space for summary, padsize = %d\n",
			      padsize);
		/* Non-fatal */
		वापस 0;
	पूर्ण

	स_रखो(c->summary->sum_buf, 0xff, datasize);
	स_रखो(&isum, 0, माप(isum));

	isum.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	isum.nodetype = cpu_to_je16(JFFS2_NODETYPE_SUMMARY);
	isum.totlen = cpu_to_je32(infosize);
	isum.hdr_crc = cpu_to_je32(crc32(0, &isum, माप(काष्ठा jffs2_unknown_node) - 4));
	isum.padded = cpu_to_je32(c->summary->sum_padded);
	isum.cln_mkr = cpu_to_je32(c->cleanmarker_size);
	isum.sum_num = cpu_to_je32(c->summary->sum_num);
	wpage = c->summary->sum_buf;

	जबतक (c->summary->sum_num) अणु
		temp = c->summary->sum_list_head;

		चयन (je16_to_cpu(temp->u.nodetype)) अणु
			हाल JFFS2_NODETYPE_INODE: अणु
				काष्ठा jffs2_sum_inode_flash *sino_ptr = wpage;

				sino_ptr->nodetype = temp->i.nodetype;
				sino_ptr->inode = temp->i.inode;
				sino_ptr->version = temp->i.version;
				sino_ptr->offset = temp->i.offset;
				sino_ptr->totlen = temp->i.totlen;

				wpage += JFFS2_SUMMARY_INODE_SIZE;

				अवरोध;
			पूर्ण

			हाल JFFS2_NODETYPE_सूचीENT: अणु
				काष्ठा jffs2_sum_dirent_flash *sdrnt_ptr = wpage;

				sdrnt_ptr->nodetype = temp->d.nodetype;
				sdrnt_ptr->totlen = temp->d.totlen;
				sdrnt_ptr->offset = temp->d.offset;
				sdrnt_ptr->pino = temp->d.pino;
				sdrnt_ptr->version = temp->d.version;
				sdrnt_ptr->ino = temp->d.ino;
				sdrnt_ptr->nsize = temp->d.nsize;
				sdrnt_ptr->type = temp->d.type;

				स_नकल(sdrnt_ptr->name, temp->d.name,
							temp->d.nsize);

				wpage += JFFS2_SUMMARY_सूचीENT_SIZE(temp->d.nsize);

				अवरोध;
			पूर्ण
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
			हाल JFFS2_NODETYPE_XATTR: अणु
				काष्ठा jffs2_sum_xattr_flash *sxattr_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxattr_ptr->nodetype = temp->x.nodetype;
				sxattr_ptr->xid = temp->x.xid;
				sxattr_ptr->version = temp->x.version;
				sxattr_ptr->offset = temp->x.offset;
				sxattr_ptr->totlen = temp->x.totlen;

				wpage += JFFS2_SUMMARY_XATTR_SIZE;
				अवरोध;
			पूर्ण
			हाल JFFS2_NODETYPE_XREF: अणु
				काष्ठा jffs2_sum_xref_flash *sxref_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxref_ptr->nodetype = temp->r.nodetype;
				sxref_ptr->offset = temp->r.offset;

				wpage += JFFS2_SUMMARY_XREF_SIZE;
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			शेष : अणु
				अगर ((je16_to_cpu(temp->u.nodetype) & JFFS2_COMPAT_MASK)
				    == JFFS2_FEATURE_RWCOMPAT_COPY) अणु
					dbg_summary("Writing unknown RWCOMPAT_COPY node type %x\n",
						    je16_to_cpu(temp->u.nodetype));
					jffs2_sum_disable_collecting(c->summary);
					/* The above call हटाओs the list, nothing more to करो */
					जाओ bail_rwcompat;
				पूर्ण अन्यथा अणु
					BUG();	/* unknown node in summary inक्रमmation */
				पूर्ण
			पूर्ण
		पूर्ण

		c->summary->sum_list_head = temp->u.next;
		kमुक्त(temp);

		c->summary->sum_num--;
	पूर्ण
 bail_rwcompat:

	jffs2_sum_reset_collected(c->summary);

	wpage += padsize;

	sm = wpage;
	sm->offset = cpu_to_je32(c->sector_size - jeb->मुक्त_size);
	sm->magic = cpu_to_je32(JFFS2_SUM_MAGIC);

	isum.sum_crc = cpu_to_je32(crc32(0, c->summary->sum_buf, datasize));
	isum.node_crc = cpu_to_je32(crc32(0, &isum, माप(isum) - 8));

	vecs[0].iov_base = &isum;
	vecs[0].iov_len = माप(isum);
	vecs[1].iov_base = c->summary->sum_buf;
	vecs[1].iov_len = datasize;

	sum_ofs = jeb->offset + c->sector_size - jeb->मुक्त_size;

	dbg_summary("writing out data to flash to pos : 0x%08x\n", sum_ofs);

	ret = jffs2_flash_ग_लिखोv(c, vecs, 2, sum_ofs, &retlen, 0);

	अगर (ret || (retlen != infosize)) अणु

		JFFS2_WARNING("Write of %u bytes at 0x%08x failed. returned %d, retlen %zd\n",
			      infosize, sum_ofs, ret, retlen);

		अगर (retlen) अणु
			/* Waste reमुख्यing space */
			spin_lock(&c->erase_completion_lock);
			jffs2_link_node_ref(c, jeb, sum_ofs | REF_OBSOLETE, infosize, शून्य);
			spin_unlock(&c->erase_completion_lock);
		पूर्ण

		c->summary->sum_size = JFFS2_SUMMARY_NOSUM_SIZE;

		वापस 0;
	पूर्ण

	spin_lock(&c->erase_completion_lock);
	jffs2_link_node_ref(c, jeb, sum_ofs | REF_NORMAL, infosize, शून्य);
	spin_unlock(&c->erase_completion_lock);

	वापस 0;
पूर्ण

/* Write out summary inक्रमmation - called from jffs2_करो_reserve_space */

पूर्णांक jffs2_sum_ग_लिखो_sumnode(काष्ठा jffs2_sb_info *c)
	__must_hold(&c->erase_completion_block)
अणु
	पूर्णांक datasize, infosize, padsize;
	काष्ठा jffs2_eraseblock *jeb;
	पूर्णांक ret = 0;

	dbg_summary("called\n");

	spin_unlock(&c->erase_completion_lock);

	jeb = c->nextblock;
	jffs2_pपुनः_स्मृति_raw_node_refs(c, jeb, 1);

	अगर (!c->summary->sum_num || !c->summary->sum_list_head) अणु
		JFFS2_WARNING("Empty summary info!!!\n");
		BUG();
	पूर्ण

	datasize = c->summary->sum_size + माप(काष्ठा jffs2_sum_marker);
	infosize = माप(काष्ठा jffs2_raw_summary) + datasize;
	padsize = jeb->मुक्त_size - infosize;
	infosize += padsize;
	datasize += padsize;

	ret = jffs2_sum_ग_लिखो_data(c, jeb, infosize, datasize, padsize);
	spin_lock(&c->erase_completion_lock);
	वापस ret;
पूर्ण
