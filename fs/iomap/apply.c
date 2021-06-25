<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Red Hat, Inc.
 * Copyright (c) 2016-2018 Christoph Hellwig.
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश "trace.h"

/*
 * Execute a iomap ग_लिखो on a segment of the mapping that spans a
 * contiguous range of pages that have identical block mapping state.
 *
 * This aव्योमs the need to map pages inभागidually, करो inभागidual allocations
 * क्रम each page and most importantly aव्योम the need क्रम fileप्रणाली specअगरic
 * locking per page. Instead, all the operations are amortised over the entire
 * range of pages. It is assumed that the fileप्रणालीs will lock whatever
 * resources they require in the iomap_begin call, and release them in the
 * iomap_end call.
 */
loff_t
iomap_apply(काष्ठा inode *inode, loff_t pos, loff_t length, अचिन्हित flags,
		स्थिर काष्ठा iomap_ops *ops, व्योम *data, iomap_actor_t actor)
अणु
	काष्ठा iomap iomap = अणु .type = IOMAP_HOLE पूर्ण;
	काष्ठा iomap srcmap = अणु .type = IOMAP_HOLE पूर्ण;
	loff_t written = 0, ret;
	u64 end;

	trace_iomap_apply(inode, pos, length, flags, ops, actor, _RET_IP_);

	/*
	 * Need to map a range from start position क्रम length bytes. This can
	 * span multiple pages - it is only guaranteed to वापस a range of a
	 * single type of pages (e.g. all पूर्णांकo a hole, all mapped or all
	 * unwritten). Failure at this poपूर्णांक has nothing to unकरो.
	 *
	 * If allocation is required क्रम this range, reserve the space now so
	 * that the allocation is guaranteed to succeed later on. Once we copy
	 * the data पूर्णांकo the page cache pages, then we cannot fail otherwise we
	 * expose transient stale data. If the reserve fails, we can safely
	 * back out at this poपूर्णांक as there is nothing to unकरो.
	 */
	ret = ops->iomap_begin(inode, pos, length, flags, &iomap, &srcmap);
	अगर (ret)
		वापस ret;
	अगर (WARN_ON(iomap.offset > pos)) अणु
		written = -EIO;
		जाओ out;
	पूर्ण
	अगर (WARN_ON(iomap.length == 0)) अणु
		written = -EIO;
		जाओ out;
	पूर्ण

	trace_iomap_apply_dsपंचांगap(inode, &iomap);
	अगर (srcmap.type != IOMAP_HOLE)
		trace_iomap_apply_srcmap(inode, &srcmap);

	/*
	 * Cut करोwn the length to the one actually provided by the fileप्रणाली,
	 * as it might not be able to give us the whole size that we requested.
	 */
	end = iomap.offset + iomap.length;
	अगर (srcmap.type != IOMAP_HOLE)
		end = min(end, srcmap.offset + srcmap.length);
	अगर (pos + length > end)
		length = end - pos;

	/*
	 * Now that we have guaranteed that the space allocation will succeed,
	 * we can करो the copy-in page by page without having to worry about
	 * failures exposing transient data.
	 *
	 * To support COW operations, we पढ़ो in data क्रम partially blocks from
	 * the srcmap अगर the file प्रणाली filled it in.  In that हाल we the
	 * length needs to be limited to the earlier of the ends of the iomaps.
	 * If the file प्रणाली did not provide a srcmap we pass in the normal
	 * iomap पूर्णांकo the actors so that they करोn't need to have special
	 * handling क्रम the two हालs.
	 */
	written = actor(inode, pos, length, data, &iomap,
			srcmap.type != IOMAP_HOLE ? &srcmap : &iomap);

out:
	/*
	 * Now the data has been copied, commit the range we've copied.  This
	 * should not fail unless the fileप्रणाली has had a fatal error.
	 */
	अगर (ops->iomap_end) अणु
		ret = ops->iomap_end(inode, pos, length,
				     written > 0 ? written : 0,
				     flags, &iomap);
	पूर्ण

	वापस written ? written : ret;
पूर्ण
