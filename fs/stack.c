<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_stack.h>

/* करोes _NOT_ require i_mutex to be held.
 *
 * This function cannot be अंतरभूतd since i_size_अणुपढ़ो,ग_लिखोपूर्ण is rather
 * heavy-weight on 32-bit प्रणालीs
 */
व्योम fsstack_copy_inode_size(काष्ठा inode *dst, काष्ठा inode *src)
अणु
	loff_t i_size;
	blkcnt_t i_blocks;

	/*
	 * i_size_पढ़ो() includes its own seqlocking and protection from
	 * preemption (see include/linux/fs.h): we need nothing extra क्रम
	 * that here, and prefer to aव्योम nesting locks than attempt to keep
	 * i_size and i_blocks in sync together.
	 */
	i_size = i_size_पढ़ो(src);

	/*
	 * But on 32-bit, we ought to make an efक्रमt to keep the two halves of
	 * i_blocks in sync despite SMP or PREEMPTION - though stat's
	 * generic_fillattr() करोesn't bother, and we won't be applying quotas
	 * (where i_blocks करोes become important) at the upper level.
	 *
	 * We करोn't actually know what locking is used at the lower level;
	 * but अगर it's a fileप्रणाली that supports quotas, it will be using
	 * i_lock as in inode_add_bytes().
	 */
	अगर (माप(i_blocks) > माप(दीर्घ))
		spin_lock(&src->i_lock);
	i_blocks = src->i_blocks;
	अगर (माप(i_blocks) > माप(दीर्घ))
		spin_unlock(&src->i_lock);

	/*
	 * If CONFIG_SMP or CONFIG_PREEMPTION on 32-bit, it's vital क्रम
	 * fsstack_copy_inode_size() to hold some lock around
	 * i_size_ग_लिखो(), otherwise i_size_पढ़ो() may spin क्रमever (see
	 * include/linux/fs.h).  We करोn't necessarily hold i_mutex when this
	 * is called, so take i_lock क्रम that हाल.
	 *
	 * And अगर on 32-bit, जारी our efक्रमt to keep the two halves of
	 * i_blocks in sync despite SMP or PREEMPTION: use i_lock क्रम that हाल
	 * too, and करो both at once by combining the tests.
	 *
	 * There is none of this locking overhead in the 64-bit हाल.
	 */
	अगर (माप(i_size) > माप(दीर्घ) || माप(i_blocks) > माप(दीर्घ))
		spin_lock(&dst->i_lock);
	i_size_ग_लिखो(dst, i_size);
	dst->i_blocks = i_blocks;
	अगर (माप(i_size) > माप(दीर्घ) || माप(i_blocks) > माप(दीर्घ))
		spin_unlock(&dst->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(fsstack_copy_inode_size);

/* copy all attributes */
व्योम fsstack_copy_attr_all(काष्ठा inode *dest, स्थिर काष्ठा inode *src)
अणु
	dest->i_mode = src->i_mode;
	dest->i_uid = src->i_uid;
	dest->i_gid = src->i_gid;
	dest->i_rdev = src->i_rdev;
	dest->i_aसमय = src->i_aसमय;
	dest->i_mसमय = src->i_mसमय;
	dest->i_स_समय = src->i_स_समय;
	dest->i_blkbits = src->i_blkbits;
	dest->i_flags = src->i_flags;
	set_nlink(dest, src->i_nlink);
पूर्ण
EXPORT_SYMBOL_GPL(fsstack_copy_attr_all);
