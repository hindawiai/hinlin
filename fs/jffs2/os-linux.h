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

#अगर_अघोषित __JFFS2_OS_LINUX_H__
#घोषणा __JFFS2_OS_LINUX_H__

/* JFFS2 uses Linux mode bits natively -- no need क्रम conversion */
#घोषणा os_to_jffs2_mode(x) (x)
#घोषणा jffs2_to_os_mode(x) (x)

काष्ठा kstatfs;
काष्ठा kvec;

#घोषणा JFFS2_INODE_INFO(i) (container_of(i, काष्ठा jffs2_inode_info, vfs_inode))
#घोषणा OFNI_EDONI_2SFFJ(f)  (&(f)->vfs_inode)
#घोषणा JFFS2_SB_INFO(sb) (sb->s_fs_info)
#घोषणा OFNI_BS_2SFFJ(c)  ((काष्ठा super_block *)c->os_priv)


#घोषणा JFFS2_F_I_SIZE(f) (OFNI_EDONI_2SFFJ(f)->i_size)
#घोषणा JFFS2_F_I_MODE(f) (OFNI_EDONI_2SFFJ(f)->i_mode)
#घोषणा JFFS2_F_I_UID(f) (i_uid_पढ़ो(OFNI_EDONI_2SFFJ(f)))
#घोषणा JFFS2_F_I_GID(f) (i_gid_पढ़ो(OFNI_EDONI_2SFFJ(f)))
#घोषणा JFFS2_F_I_RDEV(f) (OFNI_EDONI_2SFFJ(f)->i_rdev)

#घोषणा JFFS2_CLAMP_TIME(t) ((uपूर्णांक32_t)clamp_t(समय64_t, (t), 0, U32_MAX))
#घोषणा ITIME(sec) ((काष्ठा बारpec64)अणुsec, 0पूर्ण)
#घोषणा JFFS2_NOW() JFFS2_CLAMP_TIME(kसमय_get_real_seconds())
#घोषणा I_SEC(tv) JFFS2_CLAMP_TIME((tv).tv_sec)
#घोषणा JFFS2_F_I_CTIME(f) I_SEC(OFNI_EDONI_2SFFJ(f)->i_स_समय)
#घोषणा JFFS2_F_I_MTIME(f) I_SEC(OFNI_EDONI_2SFFJ(f)->i_mसमय)
#घोषणा JFFS2_F_I_ATIME(f) I_SEC(OFNI_EDONI_2SFFJ(f)->i_aसमय)
#घोषणा sleep_on_spinunlock(wq, s)				\
	करो अणु							\
		DECLARE_WAITQUEUE(__रुको, current);		\
		add_रुको_queue((wq), &__रुको);			\
		set_current_state(TASK_UNINTERRUPTIBLE);	\
		spin_unlock(s);					\
		schedule();					\
		हटाओ_रुको_queue((wq), &__रुको);		\
	पूर्ण जबतक(0)

अटल अंतरभूत व्योम jffs2_init_inode_info(काष्ठा jffs2_inode_info *f)
अणु
	f->highest_version = 0;
	f->fragtree = RB_ROOT;
	f->metadata = शून्य;
	f->dents = शून्य;
	f->target = शून्य;
	f->flags = 0;
	f->usercompr = 0;
पूर्ण


#घोषणा jffs2_is_पढ़ोonly(c) (OFNI_BS_2SFFJ(c)->s_flags & SB_RDONLY)

#घोषणा SECTOR_ADDR(x) ( (((अचिन्हित दीर्घ)(x) / c->sector_size) * c->sector_size) )
#अगर_अघोषित CONFIG_JFFS2_FS_WRITEBUFFER


#अगर_घोषित CONFIG_JFFS2_SUMMARY
#घोषणा jffs2_can_mark_obsolete(c) (0)
#अन्यथा
#घोषणा jffs2_can_mark_obsolete(c) (1)
#पूर्ण_अगर

#घोषणा jffs2_is_ग_लिखोbuffered(c) (0)
#घोषणा jffs2_cleanmarker_oob(c) (0)
#घोषणा jffs2_ग_लिखो_nand_cleanmarker(c,jeb) (-EIO)

#घोषणा jffs2_flash_ग_लिखो(c, ofs, len, retlen, buf) jffs2_flash_direct_ग_लिखो(c, ofs, len, retlen, buf)
#घोषणा jffs2_flash_पढ़ो(c, ofs, len, retlen, buf) (mtd_पढ़ो((c)->mtd, ofs, len, retlen, buf))
#घोषणा jffs2_flush_wbuf_pad(c) (अणु करोअणुपूर्ण जबतक(0); (व्योम)(c), 0; पूर्ण)
#घोषणा jffs2_flush_wbuf_gc(c, i) (अणु करोअणुपूर्ण जबतक(0); (व्योम)(c), (व्योम) i, 0; पूर्ण)
#घोषणा jffs2_ग_लिखो_nand_badblock(c,jeb,bad_offset) (1)
#घोषणा jffs2_nand_flash_setup(c) (0)
#घोषणा jffs2_nand_flash_cleanup(c) करो अणुपूर्ण जबतक(0)
#घोषणा jffs2_wbuf_dirty(c) (0)
#घोषणा jffs2_flash_ग_लिखोv(a,b,c,d,e,f) jffs2_flash_direct_ग_लिखोv(a,b,c,d,e)
#घोषणा jffs2_wbuf_समयout शून्य
#घोषणा jffs2_wbuf_process शून्य
#घोषणा jffs2_dataflash(c) (0)
#घोषणा jffs2_dataflash_setup(c) (0)
#घोषणा jffs2_dataflash_cleanup(c) करो अणुपूर्ण जबतक (0)
#घोषणा jffs2_nor_wbuf_flash(c) (0)
#घोषणा jffs2_nor_wbuf_flash_setup(c) (0)
#घोषणा jffs2_nor_wbuf_flash_cleanup(c) करो अणुपूर्ण जबतक (0)
#घोषणा jffs2_ubivol(c) (0)
#घोषणा jffs2_ubivol_setup(c) (0)
#घोषणा jffs2_ubivol_cleanup(c) करो अणुपूर्ण जबतक (0)
#घोषणा jffs2_dirty_trigger(c) करो अणुपूर्ण जबतक (0)

#अन्यथा /* न_अंकD and/or ECC'd NOR support present */

#घोषणा jffs2_is_ग_लिखोbuffered(c) (c->wbuf != शून्य)

#अगर_घोषित CONFIG_JFFS2_SUMMARY
#घोषणा jffs2_can_mark_obsolete(c) (0)
#अन्यथा
#घोषणा jffs2_can_mark_obsolete(c) (c->mtd->flags & (MTD_BIT_WRITEABLE))
#पूर्ण_अगर

#घोषणा jffs2_cleanmarker_oob(c) (c->mtd->type == MTD_न_अंकDFLASH)

#घोषणा jffs2_wbuf_dirty(c) (!!(c)->wbuf_len)

/* wbuf.c */
पूर्णांक jffs2_flash_ग_लिखोv(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *vecs, अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen, uपूर्णांक32_t ino);
पूर्णांक jffs2_flash_ग_लिखो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf);
पूर्णांक jffs2_flash_पढ़ो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf);
पूर्णांक jffs2_check_oob_empty(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,पूर्णांक mode);
पूर्णांक jffs2_check_nand_cleanmarker(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
पूर्णांक jffs2_ग_लिखो_nand_cleanmarker(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
पूर्णांक jffs2_ग_लिखो_nand_badblock(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t bad_offset);
व्योम jffs2_wbuf_समयout(अचिन्हित दीर्घ data);
व्योम jffs2_wbuf_process(व्योम *data);
पूर्णांक jffs2_flush_wbuf_gc(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino);
पूर्णांक jffs2_flush_wbuf_pad(काष्ठा jffs2_sb_info *c);
पूर्णांक jffs2_nand_flash_setup(काष्ठा jffs2_sb_info *c);
व्योम jffs2_nand_flash_cleanup(काष्ठा jffs2_sb_info *c);

#घोषणा jffs2_dataflash(c) (c->mtd->type == MTD_DATAFLASH)
पूर्णांक jffs2_dataflash_setup(काष्ठा jffs2_sb_info *c);
व्योम jffs2_dataflash_cleanup(काष्ठा jffs2_sb_info *c);
#घोषणा jffs2_ubivol(c) (c->mtd->type == MTD_UBIVOLUME)
पूर्णांक jffs2_ubivol_setup(काष्ठा jffs2_sb_info *c);
व्योम jffs2_ubivol_cleanup(काष्ठा jffs2_sb_info *c);

#घोषणा jffs2_nor_wbuf_flash(c) (c->mtd->type == MTD_NORFLASH && ! (c->mtd->flags & MTD_BIT_WRITEABLE))
पूर्णांक jffs2_nor_wbuf_flash_setup(काष्ठा jffs2_sb_info *c);
व्योम jffs2_nor_wbuf_flash_cleanup(काष्ठा jffs2_sb_info *c);
व्योम jffs2_dirty_trigger(काष्ठा jffs2_sb_info *c);

#पूर्ण_अगर /* WRITEBUFFER */

/* background.c */
पूर्णांक jffs2_start_garbage_collect_thपढ़ो(काष्ठा jffs2_sb_info *c);
व्योम jffs2_stop_garbage_collect_thपढ़ो(काष्ठा jffs2_sb_info *c);
व्योम jffs2_garbage_collect_trigger(काष्ठा jffs2_sb_info *c);

/* dir.c */
बाह्य स्थिर काष्ठा file_operations jffs2_dir_operations;
बाह्य स्थिर काष्ठा inode_operations jffs2_dir_inode_operations;

/* file.c */
बाह्य स्थिर काष्ठा file_operations jffs2_file_operations;
बाह्य स्थिर काष्ठा inode_operations jffs2_file_inode_operations;
बाह्य स्थिर काष्ठा address_space_operations jffs2_file_address_operations;
पूर्णांक jffs2_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
पूर्णांक jffs2_करो_पढ़ोpage_unlock(व्योम *data, काष्ठा page *pg);

/* ioctl.c */
दीर्घ jffs2_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/* symlink.c */
बाह्य स्थिर काष्ठा inode_operations jffs2_symlink_inode_operations;

/* fs.c */
पूर्णांक jffs2_setattr (काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
पूर्णांक jffs2_करो_setattr (काष्ठा inode *, काष्ठा iattr *);
काष्ठा inode *jffs2_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
व्योम jffs2_evict_inode (काष्ठा inode *);
व्योम jffs2_dirty_inode(काष्ठा inode *inode, पूर्णांक flags);
काष्ठा inode *jffs2_new_inode (काष्ठा inode *dir_i, umode_t mode,
			       काष्ठा jffs2_raw_inode *ri);
पूर्णांक jffs2_statfs (काष्ठा dentry *, काष्ठा kstatfs *);
पूर्णांक jffs2_करो_remount_fs(काष्ठा super_block *sb, काष्ठा fs_context *fc);
पूर्णांक jffs2_करो_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc);
व्योम jffs2_gc_release_inode(काष्ठा jffs2_sb_info *c,
			    काष्ठा jffs2_inode_info *f);
काष्ठा jffs2_inode_info *jffs2_gc_fetch_inode(काष्ठा jffs2_sb_info *c,
					      पूर्णांक inum, पूर्णांक unlinked);

अचिन्हित अक्षर *jffs2_gc_fetch_page(काष्ठा jffs2_sb_info *c,
				   काष्ठा jffs2_inode_info *f,
				   अचिन्हित दीर्घ offset,
				   अचिन्हित दीर्घ *priv);
व्योम jffs2_flash_cleanup(काष्ठा jffs2_sb_info *c);


/* ग_लिखोv.c */
पूर्णांक jffs2_flash_direct_ग_लिखोv(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *vecs,
		       अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen);
पूर्णांक jffs2_flash_direct_ग_लिखो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len,
			माप_प्रकार *retlen, स्थिर u_अक्षर *buf);

#पूर्ण_अगर /* __JFFS2_OS_LINUX_H__ */


