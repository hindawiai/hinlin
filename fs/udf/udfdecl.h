<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UDF_DECL_H
#घोषणा __UDF_DECL_H

#घोषणा pr_fmt(fmt) "UDF-fs: " fmt

#समावेश "ecma_167.h"
#समावेश "osta_udf.h"

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/udf_fs_i.h>

#समावेश "udf_sb.h"
#समावेश "udfend.h"
#समावेश "udf_i.h"

#घोषणा UDF_DEFAULT_PREALLOC_BLOCKS	8

बाह्य __म_लिखो(3, 4) व्योम _udf_err(काष्ठा super_block *sb,
		स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...);
#घोषणा udf_err(sb, fmt, ...)					\
	_udf_err(sb, __func__, fmt, ##__VA_ARGS__)

बाह्य __म_लिखो(3, 4) व्योम _udf_warn(काष्ठा super_block *sb,
		स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...);
#घोषणा udf_warn(sb, fmt, ...)					\
	_udf_warn(sb, __func__, fmt, ##__VA_ARGS__)

#घोषणा udf_info(fmt, ...)					\
	pr_info("INFO " fmt, ##__VA_ARGS__)

#घोषणा udf_debug(fmt, ...)					\
	pr_debug("%s:%d:%s: " fmt, __खाता__, __LINE__, __func__, ##__VA_ARGS__)

#घोषणा udf_fixed_to_variable(x) ( ( ( (x) >> 5 ) * 39 ) + ( (x) & 0x0000001F ) )
#घोषणा udf_variable_to_fixed(x) ( ( ( (x) / 39 ) << 5 ) + ( (x) % 39 ) )

#घोषणा UDF_EXTENT_LENGTH_MASK	0x3FFFFFFF
#घोषणा UDF_EXTENT_FLAG_MASK	0xC0000000

#घोषणा UDF_INVALID_ID ((uपूर्णांक32_t)-1)

#घोषणा UDF_NAME_PAD		4
#घोषणा UDF_NAME_LEN		254
#घोषणा UDF_NAME_LEN_CS0	255

अटल अंतरभूत माप_प्रकार udf_file_entry_alloc_offset(काष्ठा inode *inode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	अगर (iinfo->i_use)
		वापस माप(काष्ठा unallocSpaceEntry);
	अन्यथा अगर (iinfo->i_efe)
		वापस माप(काष्ठा extendedFileEntry) + iinfo->i_lenEAttr;
	अन्यथा
		वापस माप(काष्ठा fileEntry) + iinfo->i_lenEAttr;
पूर्ण

अटल अंतरभूत माप_प्रकार udf_ext0_offset(काष्ठा inode *inode)
अणु
	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		वापस udf_file_entry_alloc_offset(inode);
	अन्यथा
		वापस 0;
पूर्ण

/* computes tag checksum */
u8 udf_tag_checksum(स्थिर काष्ठा tag *t);

प्रकार uपूर्णांक32_t udf_pblk_t;

काष्ठा dentry;
काष्ठा inode;
काष्ठा task_काष्ठा;
काष्ठा buffer_head;
काष्ठा super_block;

बाह्य स्थिर काष्ठा export_operations udf_export_ops;
बाह्य स्थिर काष्ठा inode_operations udf_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations udf_dir_operations;
बाह्य स्थिर काष्ठा inode_operations udf_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations udf_file_operations;
बाह्य स्थिर काष्ठा inode_operations udf_symlink_inode_operations;
बाह्य स्थिर काष्ठा address_space_operations udf_aops;
बाह्य स्थिर काष्ठा address_space_operations udf_adinicb_aops;
बाह्य स्थिर काष्ठा address_space_operations udf_symlink_aops;

काष्ठा udf_fileident_bh अणु
	काष्ठा buffer_head *sbh;
	काष्ठा buffer_head *ebh;
	पूर्णांक soffset;
	पूर्णांक eoffset;
पूर्ण;

काष्ठा udf_vds_record अणु
	uपूर्णांक32_t block;
	uपूर्णांक32_t volDescSeqNum;
पूर्ण;

काष्ठा generic_desc अणु
	काष्ठा tag	descTag;
	__le32		volDescSeqNum;
पूर्ण;


/* super.c */

अटल अंतरभूत व्योम udf_updated_lvid(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *bh = UDF_SB(sb)->s_lvid_bh;

	BUG_ON(!bh);
	WARN_ON_ONCE(((काष्ठा logicalVolIntegrityDesc *)
		     bh->b_data)->पूर्णांकegrityType !=
		     cpu_to_le32(LVID_INTEGRITY_TYPE_OPEN));
	UDF_SB(sb)->s_lvid_dirty = 1;
पूर्ण
बाह्य u64 lvid_get_unique_id(काष्ठा super_block *sb);
काष्ठा inode *udf_find_metadata_inode_efe(काष्ठा super_block *sb,
					u32 meta_file_loc, u32 partition_num);

/* namei.c */
बाह्य पूर्णांक udf_ग_लिखो_fi(काष्ठा inode *inode, काष्ठा fileIdentDesc *,
			काष्ठा fileIdentDesc *, काष्ठा udf_fileident_bh *,
			uपूर्णांक8_t *, uपूर्णांक8_t *);
अटल अंतरभूत अचिन्हित पूर्णांक udf_dir_entry_len(काष्ठा fileIdentDesc *cfi)
अणु
	वापस ALIGN(माप(काष्ठा fileIdentDesc) +
		le16_to_cpu(cfi->lengthOfImpUse) + cfi->lengthFileIdent,
		UDF_NAME_PAD);
पूर्ण

/* file.c */
बाह्य दीर्घ udf_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
/* inode.c */
बाह्य काष्ठा inode *__udf_iget(काष्ठा super_block *, काष्ठा kernel_lb_addr *,
				bool hidden_inode);
अटल अंतरभूत काष्ठा inode *udf_iget_special(काष्ठा super_block *sb,
					     काष्ठा kernel_lb_addr *ino)
अणु
	वापस __udf_iget(sb, ino, true);
पूर्ण
अटल अंतरभूत काष्ठा inode *udf_iget(काष्ठा super_block *sb,
				     काष्ठा kernel_lb_addr *ino)
अणु
	वापस __udf_iget(sb, ino, false);
पूर्ण
बाह्य पूर्णांक udf_expand_file_adinicb(काष्ठा inode *);
बाह्य काष्ठा buffer_head *udf_expand_dir_adinicb(काष्ठा inode *inode,
						  udf_pblk_t *block, पूर्णांक *err);
बाह्य काष्ठा buffer_head *udf_bपढ़ो(काष्ठा inode *inode, udf_pblk_t block,
				      पूर्णांक create, पूर्णांक *err);
बाह्य पूर्णांक udf_setsize(काष्ठा inode *, loff_t);
बाह्य व्योम udf_evict_inode(काष्ठा inode *);
बाह्य पूर्णांक udf_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *wbc);
बाह्य udf_pblk_t udf_block_map(काष्ठा inode *inode, sector_t block);
बाह्य पूर्णांक8_t inode_bmap(काष्ठा inode *, sector_t, काष्ठा extent_position *,
			 काष्ठा kernel_lb_addr *, uपूर्णांक32_t *, sector_t *);
बाह्य पूर्णांक udf_setup_indirect_aext(काष्ठा inode *inode, udf_pblk_t block,
				   काष्ठा extent_position *epos);
बाह्य पूर्णांक __udf_add_aext(काष्ठा inode *inode, काष्ठा extent_position *epos,
			  काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t elen, पूर्णांक inc);
बाह्य पूर्णांक udf_add_aext(काष्ठा inode *, काष्ठा extent_position *,
			काष्ठा kernel_lb_addr *, uपूर्णांक32_t, पूर्णांक);
बाह्य व्योम udf_ग_लिखो_aext(काष्ठा inode *, काष्ठा extent_position *,
			   काष्ठा kernel_lb_addr *, uपूर्णांक32_t, पूर्णांक);
बाह्य पूर्णांक8_t udf_delete_aext(काष्ठा inode *, काष्ठा extent_position);
बाह्य पूर्णांक8_t udf_next_aext(काष्ठा inode *, काष्ठा extent_position *,
			    काष्ठा kernel_lb_addr *, uपूर्णांक32_t *, पूर्णांक);
बाह्य पूर्णांक8_t udf_current_aext(काष्ठा inode *, काष्ठा extent_position *,
			       काष्ठा kernel_lb_addr *, uपूर्णांक32_t *, पूर्णांक);
बाह्य व्योम udf_update_extra_perms(काष्ठा inode *inode, umode_t mode);

/* misc.c */
बाह्य काष्ठा buffer_head *udf_tgetblk(काष्ठा super_block *sb,
					udf_pblk_t block);
बाह्य काष्ठा buffer_head *udf_tपढ़ो(काष्ठा super_block *sb, udf_pblk_t block);
बाह्य काष्ठा genericFormat *udf_add_extendedattr(काष्ठा inode *, uपूर्णांक32_t,
						  uपूर्णांक32_t, uपूर्णांक8_t);
बाह्य काष्ठा genericFormat *udf_get_extendedattr(काष्ठा inode *, uपूर्णांक32_t,
						  uपूर्णांक8_t);
बाह्य काष्ठा buffer_head *udf_पढ़ो_tagged(काष्ठा super_block *, uपूर्णांक32_t,
					   uपूर्णांक32_t, uपूर्णांक16_t *);
बाह्य काष्ठा buffer_head *udf_पढ़ो_ptagged(काष्ठा super_block *,
					    काष्ठा kernel_lb_addr *, uपूर्णांक32_t,
					    uपूर्णांक16_t *);
बाह्य व्योम udf_update_tag(अक्षर *, पूर्णांक);
बाह्य व्योम udf_new_tag(अक्षर *, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक32_t, पूर्णांक);

/* lowlevel.c */
बाह्य अचिन्हित पूर्णांक udf_get_last_session(काष्ठा super_block *);
बाह्य अचिन्हित दीर्घ udf_get_last_block(काष्ठा super_block *);

/* partition.c */
बाह्य uपूर्णांक32_t udf_get_pblock(काष्ठा super_block *, uपूर्णांक32_t, uपूर्णांक16_t,
			       uपूर्णांक32_t);
बाह्य uपूर्णांक32_t udf_get_pblock_virt15(काष्ठा super_block *, uपूर्णांक32_t, uपूर्णांक16_t,
				      uपूर्णांक32_t);
बाह्य uपूर्णांक32_t udf_get_pblock_virt20(काष्ठा super_block *, uपूर्णांक32_t, uपूर्णांक16_t,
				      uपूर्णांक32_t);
बाह्य uपूर्णांक32_t udf_get_pblock_spar15(काष्ठा super_block *, uपूर्णांक32_t, uपूर्णांक16_t,
				      uपूर्णांक32_t);
बाह्य uपूर्णांक32_t udf_get_pblock_meta25(काष्ठा super_block *, uपूर्णांक32_t, uपूर्णांक16_t,
					  uपूर्णांक32_t);
बाह्य पूर्णांक udf_relocate_blocks(काष्ठा super_block *, दीर्घ, दीर्घ *);

अटल अंतरभूत uपूर्णांक32_t
udf_get_lb_pblock(काष्ठा super_block *sb, काष्ठा kernel_lb_addr *loc,
		  uपूर्णांक32_t offset)
अणु
	वापस udf_get_pblock(sb, loc->logicalBlockNum,
			loc->partitionReferenceNum, offset);
पूर्ण

/* unicode.c */
बाह्य पूर्णांक udf_get_filename(काष्ठा super_block *, स्थिर uपूर्णांक8_t *, पूर्णांक,
			    uपूर्णांक8_t *, पूर्णांक);
बाह्य पूर्णांक udf_put_filename(काष्ठा super_block *, स्थिर uपूर्णांक8_t *, पूर्णांक,
			    uपूर्णांक8_t *, पूर्णांक);
बाह्य पूर्णांक udf_dstrCS0toChar(काष्ठा super_block *, uपूर्णांक8_t *, पूर्णांक,
			     स्थिर uपूर्णांक8_t *, पूर्णांक);

/* ialloc.c */
बाह्य व्योम udf_मुक्त_inode(काष्ठा inode *);
बाह्य काष्ठा inode *udf_new_inode(काष्ठा inode *, umode_t);

/* truncate.c */
बाह्य व्योम udf_truncate_tail_extent(काष्ठा inode *);
बाह्य व्योम udf_discard_pपुनः_स्मृति(काष्ठा inode *);
बाह्य पूर्णांक udf_truncate_extents(काष्ठा inode *);

/* balloc.c */
बाह्य व्योम udf_मुक्त_blocks(काष्ठा super_block *, काष्ठा inode *,
			    काष्ठा kernel_lb_addr *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक udf_pपुनः_स्मृति_blocks(काष्ठा super_block *, काष्ठा inode *, uपूर्णांक16_t,
			       uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य udf_pblk_t udf_new_block(काष्ठा super_block *sb, काष्ठा inode *inode,
				 uपूर्णांक16_t partition, uपूर्णांक32_t goal, पूर्णांक *err);

/* directory.c */
बाह्य काष्ठा fileIdentDesc *udf_fileident_पढ़ो(काष्ठा inode *, loff_t *,
						काष्ठा udf_fileident_bh *,
						काष्ठा fileIdentDesc *,
						काष्ठा extent_position *,
						काष्ठा kernel_lb_addr *, uपूर्णांक32_t *,
						sector_t *);
बाह्य काष्ठा fileIdentDesc *udf_get_fileident(व्योम *buffer, पूर्णांक bufsize,
					       पूर्णांक *offset);
बाह्य काष्ठा दीर्घ_ad *udf_get_fileदीर्घad(uपूर्णांक8_t *, पूर्णांक, uपूर्णांक32_t *, पूर्णांक);
बाह्य काष्ठा लघु_ad *udf_get_fileलघुad(uपूर्णांक8_t *, पूर्णांक, uपूर्णांक32_t *, पूर्णांक);

/* udfसमय.c */
बाह्य व्योम udf_disk_stamp_to_समय(काष्ठा बारpec64 *dest,
						काष्ठा बारtamp src);
बाह्य व्योम udf_समय_प्रकारo_disk_stamp(काष्ठा बारtamp *dest, काष्ठा बारpec64 src);

#पूर्ण_अगर				/* __UDF_DECL_H */
