<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2018 Christoph Hellwig.
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/fiemap.h>

काष्ठा fiemap_ctx अणु
	काष्ठा fiemap_extent_info *fi;
	काष्ठा iomap prev;
पूर्ण;

अटल पूर्णांक iomap_to_fiemap(काष्ठा fiemap_extent_info *fi,
		काष्ठा iomap *iomap, u32 flags)
अणु
	चयन (iomap->type) अणु
	हाल IOMAP_HOLE:
		/* skip holes */
		वापस 0;
	हाल IOMAP_DELALLOC:
		flags |= FIEMAP_EXTENT_DELALLOC | FIEMAP_EXTENT_UNKNOWN;
		अवरोध;
	हाल IOMAP_MAPPED:
		अवरोध;
	हाल IOMAP_UNWRITTEN:
		flags |= FIEMAP_EXTENT_UNWRITTEN;
		अवरोध;
	हाल IOMAP_INLINE:
		flags |= FIEMAP_EXTENT_DATA_INLINE;
		अवरोध;
	पूर्ण

	अगर (iomap->flags & IOMAP_F_MERGED)
		flags |= FIEMAP_EXTENT_MERGED;
	अगर (iomap->flags & IOMAP_F_SHARED)
		flags |= FIEMAP_EXTENT_SHARED;

	वापस fiemap_fill_next_extent(fi, iomap->offset,
			iomap->addr != IOMAP_शून्य_ADDR ? iomap->addr : 0,
			iomap->length, flags);
पूर्ण

अटल loff_t
iomap_fiemap_actor(काष्ठा inode *inode, loff_t pos, loff_t length, व्योम *data,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा fiemap_ctx *ctx = data;
	loff_t ret = length;

	अगर (iomap->type == IOMAP_HOLE)
		वापस length;

	ret = iomap_to_fiemap(ctx->fi, &ctx->prev, 0);
	ctx->prev = *iomap;
	चयन (ret) अणु
	हाल 0:		/* success */
		वापस length;
	हाल 1:		/* extent array full */
		वापस 0;
	शेष:
		वापस ret;
	पूर्ण
पूर्ण

पूर्णांक iomap_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fi,
		u64 start, u64 len, स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा fiemap_ctx ctx;
	loff_t ret;

	स_रखो(&ctx, 0, माप(ctx));
	ctx.fi = fi;
	ctx.prev.type = IOMAP_HOLE;

	ret = fiemap_prep(inode, fi, start, &len, 0);
	अगर (ret)
		वापस ret;

	जबतक (len > 0) अणु
		ret = iomap_apply(inode, start, len, IOMAP_REPORT, ops, &ctx,
				iomap_fiemap_actor);
		/* inode with no (attribute) mapping will give ENOENT */
		अगर (ret == -ENOENT)
			अवरोध;
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)
			अवरोध;

		start += ret;
		len -= ret;
	पूर्ण

	अगर (ctx.prev.type != IOMAP_HOLE) अणु
		ret = iomap_to_fiemap(fi, &ctx.prev, FIEMAP_EXTENT_LAST);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_fiemap);

अटल loff_t
iomap_bmap_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	sector_t *bno = data, addr;

	अगर (iomap->type == IOMAP_MAPPED) अणु
		addr = (pos - iomap->offset + iomap->addr) >> inode->i_blkbits;
		*bno = addr;
	पूर्ण
	वापस 0;
पूर्ण

/* legacy ->bmap पूर्णांकerface.  0 is the error वापस (!) */
sector_t
iomap_bmap(काष्ठा address_space *mapping, sector_t bno,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा inode *inode = mapping->host;
	loff_t pos = bno << inode->i_blkbits;
	अचिन्हित blocksize = i_blocksize(inode);
	पूर्णांक ret;

	अगर (filemap_ग_लिखो_and_रुको(mapping))
		वापस 0;

	bno = 0;
	ret = iomap_apply(inode, pos, blocksize, 0, ops, &bno,
			  iomap_bmap_actor);
	अगर (ret)
		वापस 0;
	वापस bno;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_bmap);
