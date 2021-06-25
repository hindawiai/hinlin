<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
 * Copyright (c) 2016 Krzysztof Blaszkowski
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Veritas fileप्रणाली driver - lookup and other directory related code.
 */
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>

#समावेश "vxfs.h"
#समावेश "vxfs_dir.h"
#समावेश "vxfs_inode.h"
#समावेश "vxfs_extern.h"

/*
 * Number of VxFS blocks per page.
 */
#घोषणा VXFS_BLOCK_PER_PAGE(sbp)  ((PAGE_SIZE / (sbp)->s_blocksize))


अटल काष्ठा dentry *	vxfs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
अटल पूर्णांक		vxfs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

स्थिर काष्ठा inode_operations vxfs_dir_inode_ops = अणु
	.lookup =		vxfs_lookup,
पूर्ण;

स्थिर काष्ठा file_operations vxfs_dir_operations = अणु
	.llseek =		generic_file_llseek,
	.पढ़ो =			generic_पढ़ो_dir,
	.iterate_shared =	vxfs_सूची_पढ़ो,
पूर्ण;


/**
 * vxfs_find_entry - find a mathing directory entry क्रम a dentry
 * @ip:		directory inode
 * @dp:		dentry क्रम which we want to find a direct
 * @ppp:	माला_लो filled with the page the वापस value sits in
 *
 * Description:
 *   vxfs_find_entry finds a &काष्ठा vxfs_direct क्रम the VFS directory
 *   cache entry @dp.  @ppp will be filled with the page the वापस
 *   value resides in.
 *
 * Returns:
 *   The wanted direct on success, अन्यथा a शून्य poपूर्णांकer.
 */
अटल काष्ठा vxfs_direct *
vxfs_find_entry(काष्ठा inode *ip, काष्ठा dentry *dp, काष्ठा page **ppp)
अणु
	u_दीर्घ bsize = ip->i_sb->s_blocksize;
	स्थिर अक्षर *name = dp->d_name.name;
	पूर्णांक namelen = dp->d_name.len;
	loff_t limit = VXFS_सूचीROUND(ip->i_size);
	काष्ठा vxfs_direct *de_निकास = शून्य;
	loff_t pos = 0;
	काष्ठा vxfs_sb_info *sbi = VXFS_SBI(ip->i_sb);

	जबतक (pos < limit) अणु
		काष्ठा page *pp;
		अक्षर *kaddr;
		पूर्णांक pg_ofs = pos & ~PAGE_MASK;

		pp = vxfs_get_page(ip->i_mapping, pos >> PAGE_SHIFT);
		अगर (IS_ERR(pp))
			वापस शून्य;
		kaddr = (अक्षर *)page_address(pp);

		जबतक (pg_ofs < PAGE_SIZE && pos < limit) अणु
			काष्ठा vxfs_direct *de;

			अगर ((pos & (bsize - 1)) < 4) अणु
				काष्ठा vxfs_dirblk *dbp =
					(काष्ठा vxfs_dirblk *)
					 (kaddr + (pos & ~PAGE_MASK));
				पूर्णांक overhead = VXFS_सूचीBLKOV(sbi, dbp);

				pos += overhead;
				pg_ofs += overhead;
			पूर्ण
			de = (काष्ठा vxfs_direct *)(kaddr + pg_ofs);

			अगर (!de->d_reclen) अणु
				pos += bsize - 1;
				pos &= ~(bsize - 1);
				अवरोध;
			पूर्ण

			pg_ofs += fs16_to_cpu(sbi, de->d_reclen);
			pos += fs16_to_cpu(sbi, de->d_reclen);
			अगर (!de->d_ino)
				जारी;

			अगर (namelen != fs16_to_cpu(sbi, de->d_namelen))
				जारी;
			अगर (!स_भेद(name, de->d_name, namelen)) अणु
				*ppp = pp;
				de_निकास = de;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!de_निकास)
			vxfs_put_page(pp);
		अन्यथा
			अवरोध;
	पूर्ण

	वापस de_निकास;
पूर्ण

/**
 * vxfs_inode_by_name - find inode number क्रम dentry
 * @dip:	directory to search in
 * @dp:		dentry we search क्रम
 *
 * Description:
 *   vxfs_inode_by_name finds out the inode number of
 *   the path component described by @dp in @dip.
 *
 * Returns:
 *   The wanted inode number on success, अन्यथा Zero.
 */
अटल ino_t
vxfs_inode_by_name(काष्ठा inode *dip, काष्ठा dentry *dp)
अणु
	काष्ठा vxfs_direct		*de;
	काष्ठा page			*pp;
	ino_t				ino = 0;

	de = vxfs_find_entry(dip, dp, &pp);
	अगर (de) अणु
		ino = fs32_to_cpu(VXFS_SBI(dip->i_sb), de->d_ino);
		kunmap(pp);
		put_page(pp);
	पूर्ण
	
	वापस (ino);
पूर्ण

/**
 * vxfs_lookup - lookup pathname component
 * @dip:	dir in which we lookup
 * @dp:		dentry we lookup
 * @flags:	lookup flags
 *
 * Description:
 *   vxfs_lookup tries to lookup the pathname component described
 *   by @dp in @dip.
 *
 * Returns:
 *   A शून्य-poपूर्णांकer on success, अन्यथा a negative error code encoded
 *   in the वापस poपूर्णांकer.
 */
अटल काष्ठा dentry *
vxfs_lookup(काष्ठा inode *dip, काष्ठा dentry *dp, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode		*ip = शून्य;
	ino_t			ino;
			 
	अगर (dp->d_name.len > VXFS_NAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);
				 
	ino = vxfs_inode_by_name(dip, dp);
	अगर (ino)
		ip = vxfs_iget(dip->i_sb, ino);
	वापस d_splice_alias(ip, dp);
पूर्ण

/**
 * vxfs_सूची_पढ़ो - पढ़ो a directory
 * @fp:		the directory to पढ़ो
 * @retp:	वापस buffer
 * @filler:	filldir callback
 *
 * Description:
 *   vxfs_सूची_पढ़ो fills @retp with directory entries from @fp
 *   using the VFS supplied callback @filler.
 *
 * Returns:
 *   Zero.
 */
अटल पूर्णांक
vxfs_सूची_पढ़ो(काष्ठा file *fp, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode		*ip = file_inode(fp);
	काष्ठा super_block	*sbp = ip->i_sb;
	u_दीर्घ			bsize = sbp->s_blocksize;
	loff_t			pos, limit;
	काष्ठा vxfs_sb_info	*sbi = VXFS_SBI(sbp);

	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit_करोt(fp, ctx))
			जाओ out;
		ctx->pos++;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (!dir_emit(ctx, "..", 2, VXFS_INO(ip)->vii_करोtकरोt, DT_सूची))
			जाओ out;
		ctx->pos++;
	पूर्ण

	limit = VXFS_सूचीROUND(ip->i_size);
	अगर (ctx->pos > limit)
		जाओ out;

	pos = ctx->pos & ~3L;

	जबतक (pos < limit) अणु
		काष्ठा page *pp;
		अक्षर *kaddr;
		पूर्णांक pg_ofs = pos & ~PAGE_MASK;
		पूर्णांक rc = 0;

		pp = vxfs_get_page(ip->i_mapping, pos >> PAGE_SHIFT);
		अगर (IS_ERR(pp))
			वापस -ENOMEM;

		kaddr = (अक्षर *)page_address(pp);

		जबतक (pg_ofs < PAGE_SIZE && pos < limit) अणु
			काष्ठा vxfs_direct *de;

			अगर ((pos & (bsize - 1)) < 4) अणु
				काष्ठा vxfs_dirblk *dbp =
					(काष्ठा vxfs_dirblk *)
					 (kaddr + (pos & ~PAGE_MASK));
				पूर्णांक overhead = VXFS_सूचीBLKOV(sbi, dbp);

				pos += overhead;
				pg_ofs += overhead;
			पूर्ण
			de = (काष्ठा vxfs_direct *)(kaddr + pg_ofs);

			अगर (!de->d_reclen) अणु
				pos += bsize - 1;
				pos &= ~(bsize - 1);
				अवरोध;
			पूर्ण

			pg_ofs += fs16_to_cpu(sbi, de->d_reclen);
			pos += fs16_to_cpu(sbi, de->d_reclen);
			अगर (!de->d_ino)
				जारी;

			rc = dir_emit(ctx, de->d_name,
					fs16_to_cpu(sbi, de->d_namelen),
					fs32_to_cpu(sbi, de->d_ino),
					DT_UNKNOWN);
			अगर (!rc) अणु
				/* the dir entry was not पढ़ो, fix pos. */
				pos -= fs16_to_cpu(sbi, de->d_reclen);
				अवरोध;
			पूर्ण
		पूर्ण
		vxfs_put_page(pp);
		अगर (!rc)
			अवरोध;
	पूर्ण

	ctx->pos = pos | 2;

out:
	वापस 0;
पूर्ण
