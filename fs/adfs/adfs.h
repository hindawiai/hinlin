<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/adfs_fs.h>

/* Internal data काष्ठाures क्रम ADFS */

#घोषणा ADFS_FREE_FRAG		 0
#घोषणा ADFS_BAD_FRAG		 1
#घोषणा ADFS_ROOT_FRAG		 2

#घोषणा ADFS_खाताTYPE_NONE	((u16)~0)

/* RISC OS 12-bit filetype is stored in load_address[19:8] */
अटल अंतरभूत u16 adfs_filetype(u32 loadaddr)
अणु
	वापस (loadaddr & 0xfff00000) == 0xfff00000 ?
	       (loadaddr >> 8) & 0xfff : ADFS_खाताTYPE_NONE;
पूर्ण

#घोषणा ADFS_NDA_OWNER_READ	(1 << 0)
#घोषणा ADFS_NDA_OWNER_WRITE	(1 << 1)
#घोषणा ADFS_NDA_LOCKED		(1 << 2)
#घोषणा ADFS_NDA_सूचीECTORY	(1 << 3)
#घोषणा ADFS_NDA_EXECUTE	(1 << 4)
#घोषणा ADFS_NDA_PUBLIC_READ	(1 << 5)
#घोषणा ADFS_NDA_PUBLIC_WRITE	(1 << 6)

/*
 * adfs file प्रणाली inode data in memory
 */
काष्ठा adfs_inode_info अणु
	loff_t		mmu_निजी;
	__u32		parent_id;	/* parent indirect disc address	*/
	__u32		indaddr;	/* object indirect disc address	*/
	__u32		loadaddr;	/* RISC OS load address		*/
	__u32		execaddr;	/* RISC OS exec address		*/
	अचिन्हित पूर्णांक	attr;		/* RISC OS permissions		*/
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा adfs_inode_info *ADFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा adfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत bool adfs_inode_is_stamped(काष्ठा inode *inode)
अणु
	वापस (ADFS_I(inode)->loadaddr & 0xfff00000) == 0xfff00000;
पूर्ण

/*
 * Forward-declare this
 */
काष्ठा adfs_discmap;
काष्ठा adfs_dir_ops;

/*
 * ADFS file प्रणाली superblock data in memory
 */
काष्ठा adfs_sb_info अणु
	जोड़ अणु काष्ठा अणु
		काष्ठा adfs_discmap *s_map;	/* bh list containing map */
		स्थिर काष्ठा adfs_dir_ops *s_dir; /* directory operations */
		पूर्ण;
		काष्ठा rcu_head rcu;	/* used only at shutकरोwn समय	 */
	पूर्ण;
	kuid_t		s_uid;		/* owner uid */
	kgid_t		s_gid;		/* owner gid */
	umode_t		s_owner_mask;	/* ADFS owner perm -> unix perm */
	umode_t		s_other_mask;	/* ADFS other perm -> unix perm	*/
	पूर्णांक		s_ftsuffix;	/* ,xyz hex filetype suffix option */

	__u32		s_ids_per_zone;	/* max. no ids in one zone */
	__u32		s_idlen;	/* length of ID in map */
	__u32		s_map_size;	/* sector size of a map	*/
	चिन्हित पूर्णांक	s_map2blk;	/* shअगरt left by this क्रम map->sector*/
	अचिन्हित पूर्णांक	s_log2sharesize;/* log2 share size */
	अचिन्हित पूर्णांक	s_namelen;	/* maximum number of अक्षरacters in name	 */
पूर्ण;

अटल अंतरभूत काष्ठा adfs_sb_info *ADFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * Directory handling
 */
काष्ठा adfs_dir अणु
	काष्ठा super_block	*sb;

	पूर्णांक			nr_buffers;
	काष्ठा buffer_head	*bh[4];
	काष्ठा buffer_head	**bhs;

	अचिन्हित पूर्णांक		pos;
	__u32			parent_id;

	जोड़ अणु
		काष्ठा adfs_dirheader	*dirhead;
		काष्ठा adfs_bigdirheader *bighead;
	पूर्ण;
	जोड़ अणु
		काष्ठा adfs_newdirtail	*newtail;
		काष्ठा adfs_bigdirtail	*bigtail;
	पूर्ण;
पूर्ण;

/*
 * This is the overall maximum name length
 */
#घोषणा ADFS_MAX_NAME_LEN	(256 + 4) /* +4 क्रम ,xyz hex filetype suffix */
काष्ठा object_info अणु
	__u32		parent_id;		/* parent object id	*/
	__u32		indaddr;		/* indirect disc addr	*/
	__u32		loadaddr;		/* load address		*/
	__u32		execaddr;		/* execution address	*/
	__u32		size;			/* size			*/
	__u8		attr;			/* RISC OS attributes	*/
	अचिन्हित पूर्णांक	name_len;		/* name length		*/
	अक्षर		name[ADFS_MAX_NAME_LEN];/* file name		*/
पूर्ण;

काष्ठा adfs_dir_ops अणु
	पूर्णांक	(*पढ़ो)(काष्ठा super_block *sb, अचिन्हित पूर्णांक indaddr,
			अचिन्हित पूर्णांक size, काष्ठा adfs_dir *dir);
	पूर्णांक	(*iterate)(काष्ठा adfs_dir *dir, काष्ठा dir_context *ctx);
	पूर्णांक	(*setpos)(काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक fpos);
	पूर्णांक	(*getnext)(काष्ठा adfs_dir *dir, काष्ठा object_info *obj);
	पूर्णांक	(*update)(काष्ठा adfs_dir *dir, काष्ठा object_info *obj);
	पूर्णांक	(*create)(काष्ठा adfs_dir *dir, काष्ठा object_info *obj);
	पूर्णांक	(*हटाओ)(काष्ठा adfs_dir *dir, काष्ठा object_info *obj);
	पूर्णांक	(*commit)(काष्ठा adfs_dir *dir);
पूर्ण;

काष्ठा adfs_discmap अणु
	काष्ठा buffer_head	*dm_bh;
	__u32			dm_startblk;
	अचिन्हित पूर्णांक		dm_startbit;
	अचिन्हित पूर्णांक		dm_endbit;
पूर्ण;

/* Inode stuff */
काष्ठा inode *adfs_iget(काष्ठा super_block *sb, काष्ठा object_info *obj);
पूर्णांक adfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
पूर्णांक adfs_notअगरy_change(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *attr);

/* map.c */
पूर्णांक adfs_map_lookup(काष्ठा super_block *sb, u32 frag_id, अचिन्हित पूर्णांक offset);
व्योम adfs_map_statfs(काष्ठा super_block *sb, काष्ठा kstatfs *buf);
काष्ठा adfs_discmap *adfs_पढ़ो_map(काष्ठा super_block *sb, काष्ठा adfs_discrecord *dr);
व्योम adfs_मुक्त_map(काष्ठा super_block *sb);

/* Misc */
__म_लिखो(3, 4)
व्योम __adfs_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		  स्थिर अक्षर *fmt, ...);
#घोषणा adfs_error(sb, fmt...) __adfs_error(sb, __func__, fmt)
व्योम adfs_msg(काष्ठा super_block *sb, स्थिर अक्षर *pfx, स्थिर अक्षर *fmt, ...);

/* super.c */

/*
 * Inodes and file operations
 */

/* dir_*.c */
बाह्य स्थिर काष्ठा inode_operations adfs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations adfs_dir_operations;
बाह्य स्थिर काष्ठा dentry_operations adfs_dentry_operations;
बाह्य स्थिर काष्ठा adfs_dir_ops adfs_f_dir_ops;
बाह्य स्थिर काष्ठा adfs_dir_ops adfs_fplus_dir_ops;

पूर्णांक adfs_dir_copyfrom(व्योम *dst, काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक offset,
		      माप_प्रकार len);
पूर्णांक adfs_dir_copyto(काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक offset, स्थिर व्योम *src,
		    माप_प्रकार len);
व्योम adfs_dir_rअन्यथा(काष्ठा adfs_dir *dir);
पूर्णांक adfs_dir_पढ़ो_buffers(काष्ठा super_block *sb, u32 indaddr,
			  अचिन्हित पूर्णांक size, काष्ठा adfs_dir *dir);
व्योम adfs_object_fixup(काष्ठा adfs_dir *dir, काष्ठा object_info *obj);
बाह्य पूर्णांक adfs_dir_update(काष्ठा super_block *sb, काष्ठा object_info *obj,
			   पूर्णांक रुको);

/* file.c */
बाह्य स्थिर काष्ठा inode_operations adfs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations adfs_file_operations;

अटल अंतरभूत __u32 चिन्हित_asl(__u32 val, चिन्हित पूर्णांक shअगरt)
अणु
	अगर (shअगरt >= 0)
		val <<= shअगरt;
	अन्यथा
		val >>= -shअगरt;
	वापस val;
पूर्ण

/*
 * Calculate the address of a block in an object given the block offset
 * and the object identity.
 *
 * The root directory ID should always be looked up in the map [3.4]
 */
अटल अंतरभूत पूर्णांक __adfs_block_map(काष्ठा super_block *sb, u32 indaddr,
				   अचिन्हित पूर्णांक block)
अणु
	अगर (indaddr & 255) अणु
		अचिन्हित पूर्णांक off;

		off = (indaddr & 255) - 1;
		block += off << ADFS_SB(sb)->s_log2sharesize;
	पूर्ण

	वापस adfs_map_lookup(sb, indaddr >> 8, block);
पूर्ण

/* Return the disc record from the map */
अटल अंतरभूत
काष्ठा adfs_discrecord *adfs_map_discrecord(काष्ठा adfs_discmap *dm)
अणु
	वापस (व्योम *)(dm[0].dm_bh->b_data + 4);
पूर्ण

अटल अंतरभूत u64 adfs_disc_size(स्थिर काष्ठा adfs_discrecord *dr)
अणु
	वापस (u64)le32_to_cpu(dr->disc_size_high) << 32 |
		    le32_to_cpu(dr->disc_size);
पूर्ण
