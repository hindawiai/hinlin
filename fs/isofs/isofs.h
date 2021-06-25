<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/iso_fs.h>
#समावेश <यंत्र/unaligned.h>

क्रमागत isofs_file_क्रमmat अणु
	isofs_file_normal = 0,
	isofs_file_sparse = 1,
	isofs_file_compressed = 2,
पूर्ण;
	
/*
 * iso fs inode data in memory
 */
काष्ठा iso_inode_info अणु
	अचिन्हित दीर्घ i_iget5_block;
	अचिन्हित दीर्घ i_iget5_offset;
	अचिन्हित पूर्णांक i_first_extent;
	अचिन्हित अक्षर i_file_क्रमmat;
	अचिन्हित अक्षर i_क्रमmat_parm[3];
	अचिन्हित दीर्घ i_next_section_block;
	अचिन्हित दीर्घ i_next_section_offset;
	off_t i_section_size;
	काष्ठा inode vfs_inode;
पूर्ण;

/*
 * iso9660 super-block data in memory
 */
काष्ठा isofs_sb_info अणु
	अचिन्हित दीर्घ s_ninodes;
	अचिन्हित दीर्घ s_nzones;
	अचिन्हित दीर्घ s_firstdatazone;
	अचिन्हित दीर्घ s_log_zone_size;
	अचिन्हित दीर्घ s_max_size;
	
	पूर्णांक           s_rock_offset; /* offset of SUSP fields within SU area */
	s32           s_sbsector;
	अचिन्हित अक्षर s_joliet_level;
	अचिन्हित अक्षर s_mapping;
	अचिन्हित अक्षर s_check;
	अचिन्हित अक्षर s_session;
	अचिन्हित पूर्णांक  s_high_sierra:1;
	अचिन्हित पूर्णांक  s_rock:2;
	अचिन्हित पूर्णांक  s_utf8:1;
	अचिन्हित पूर्णांक  s_cruft:1; /* Broken disks with high byte of length
				  * containing junk */
	अचिन्हित पूर्णांक  s_nocompress:1;
	अचिन्हित पूर्णांक  s_hide:1;
	अचिन्हित पूर्णांक  s_showassoc:1;
	अचिन्हित पूर्णांक  s_overriderockperm:1;
	अचिन्हित पूर्णांक  s_uid_set:1;
	अचिन्हित पूर्णांक  s_gid_set:1;

	umode_t s_भ_शेषe;
	umode_t s_dmode;
	kgid_t s_gid;
	kuid_t s_uid;
	काष्ठा nls_table *s_nls_ioअक्षरset; /* Native language support table */
पूर्ण;

#घोषणा ISOFS_INVALID_MODE ((umode_t) -1)

अटल अंतरभूत काष्ठा isofs_sb_info *ISOFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा iso_inode_info *ISOFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा iso_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत पूर्णांक isonum_711(u8 *p)
अणु
	वापस *p;
पूर्ण
अटल अंतरभूत पूर्णांक isonum_712(s8 *p)
अणु
	वापस *p;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_721(u8 *p)
अणु
	वापस get_unaligned_le16(p);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_722(u8 *p)
अणु
	वापस get_unaligned_be16(p);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_723(u8 *p)
अणु
	/* Ignore bigendian datum due to broken mastering programs */
	वापस get_unaligned_le16(p);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_731(u8 *p)
अणु
	वापस get_unaligned_le32(p);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_732(u8 *p)
अणु
	वापस get_unaligned_be32(p);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक isonum_733(u8 *p)
अणु
	/* Ignore bigendian datum due to broken mastering programs */
	वापस get_unaligned_le32(p);
पूर्ण
बाह्य पूर्णांक iso_date(u8 *, पूर्णांक);

काष्ठा inode;		/* To make gcc happy */

बाह्य पूर्णांक parse_rock_ridge_inode(काष्ठा iso_directory_record *, काष्ठा inode *, पूर्णांक relocated);
बाह्य पूर्णांक get_rock_ridge_filename(काष्ठा iso_directory_record *, अक्षर *, काष्ठा inode *);
बाह्य पूर्णांक isofs_name_translate(काष्ठा iso_directory_record *, अक्षर *, काष्ठा inode *);

पूर्णांक get_joliet_filename(काष्ठा iso_directory_record *, अचिन्हित अक्षर *, काष्ठा inode *);
पूर्णांक get_acorn_filename(काष्ठा iso_directory_record *, अक्षर *, काष्ठा inode *);

बाह्य काष्ठा dentry *isofs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक flags);
बाह्य काष्ठा buffer_head *isofs_bपढ़ो(काष्ठा inode *, sector_t);
बाह्य पूर्णांक isofs_get_blocks(काष्ठा inode *, sector_t, काष्ठा buffer_head **, अचिन्हित दीर्घ);

काष्ठा inode *__isofs_iget(काष्ठा super_block *sb,
			   अचिन्हित दीर्घ block,
			   अचिन्हित दीर्घ offset,
			   पूर्णांक relocated);

अटल अंतरभूत काष्ठा inode *isofs_iget(काष्ठा super_block *sb,
				       अचिन्हित दीर्घ block,
				       अचिन्हित दीर्घ offset)
अणु
	वापस __isofs_iget(sb, block, offset, 0);
पूर्ण

अटल अंतरभूत काष्ठा inode *isofs_iget_reloc(काष्ठा super_block *sb,
					     अचिन्हित दीर्घ block,
					     अचिन्हित दीर्घ offset)
अणु
	वापस __isofs_iget(sb, block, offset, 1);
पूर्ण

/* Because the inode number is no दीर्घer relevant to finding the
 * underlying meta-data क्रम an inode, we are मुक्त to choose a more
 * convenient 32-bit number as the inode number.  The inode numbering
 * scheme was recommended by Sergey Vlasov and Eric Lammerts. */
अटल अंतरभूत अचिन्हित दीर्घ isofs_get_ino(अचिन्हित दीर्घ block,
					  अचिन्हित दीर्घ offset,
					  अचिन्हित दीर्घ bufbits)
अणु
	वापस (block << (bufbits - 5)) | (offset >> 5);
पूर्ण

/* Every directory can have many redundant directory entries scattered
 * throughout the directory tree.  First there is the directory entry
 * with the name of the directory stored in the parent directory.
 * Then, there is the "." directory entry stored in the directory
 * itself.  Finally, there are possibly many ".." directory entries
 * stored in all the subdirectories.
 *
 * In order क्रम the NFS get_parent() method to work and क्रम the
 * general consistency of the dcache, we need to make sure the
 * "i_iget5_block" and "i_iget5_offset" all poपूर्णांक to exactly one of
 * the many redundant entries क्रम each directory.  We normalize the
 * block and offset by always making them poपूर्णांक to the "."  directory.
 *
 * Notice that we करो not use the entry क्रम the directory with the name
 * that is located in the parent directory.  Even though choosing this
 * first directory is more natural, it is much easier to find the "."
 * entry in the NFS get_parent() method because it is implicitly
 * encoded in the "extent + ext_attr_length" fields of _all_ the
 * redundant entries क्रम the directory.  Thus, it can always be
 * reached regardless of which directory entry you have in hand.
 *
 * This works because the "." entry is simply the first directory
 * record when you start पढ़ोing the file that holds all the directory
 * records, and this file starts at "extent + ext_attr_length" blocks.
 * Because the "." entry is always the first entry listed in the
 * directories file, the normalized "offset" value is always 0.
 *
 * You should pass the directory entry in "de".  On वापस, "block"
 * and "offset" will hold normalized values.  Only directories are
 * affected making it safe to call even क्रम non-directory file
 * types. */
अटल अंतरभूत व्योम
isofs_normalize_block_and_offset(काष्ठा iso_directory_record* de,
				 अचिन्हित दीर्घ *block,
				 अचिन्हित दीर्घ *offset)
अणु
	/* Only directories are normalized. */
	अगर (de->flags[0] & 2) अणु
		*offset = 0;
		*block = (अचिन्हित दीर्घ)isonum_733(de->extent)
			+ (अचिन्हित दीर्घ)isonum_711(de->ext_attr_length);
	पूर्ण
पूर्ण

बाह्य स्थिर काष्ठा inode_operations isofs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations isofs_dir_operations;
बाह्य स्थिर काष्ठा address_space_operations isofs_symlink_aops;
बाह्य स्थिर काष्ठा export_operations isofs_export_ops;
