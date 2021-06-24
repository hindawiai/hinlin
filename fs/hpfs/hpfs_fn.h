<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/hpfs/hpfs_fn.h
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  function headers
 */

//#घोषणा DBG
//#घोषणा DEBUG_LOCKS
#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/blkdev.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "hpfs.h"

#घोषणा EIOERROR  EIO
#घोषणा EFSERROR  EUCLEAN

#घोषणा ANODE_ALLOC_FWD	512
#घोषणा FNODE_ALLOC_FWD	0
#घोषणा ALLOC_FWD_MIN	16
#घोषणा ALLOC_FWD_MAX	128
#घोषणा ALLOC_M		1
#घोषणा FNODE_RD_AHEAD	16
#घोषणा ANODE_RD_AHEAD	0
#घोषणा DNODE_RD_AHEAD	72
#घोषणा COUNT_RD_AHEAD	62

#घोषणा FREE_DNODES_ADD	58
#घोषणा FREE_DNODES_DEL	29

#घोषणा CHKCOND(x,y) अगर (!(x)) prपूर्णांकk y

काष्ठा hpfs_inode_info अणु
	loff_t mmu_निजी;
	ino_t i_parent_dir;	/* (directories) gives fnode of parent dir */
	अचिन्हित i_dno;		/* (directories) root dnode */
	अचिन्हित i_dpos;	/* (directories) temp क्रम सूची_पढ़ो */
	अचिन्हित i_dsubdno;	/* (directories) temp क्रम सूची_पढ़ो */
	अचिन्हित i_file_sec;	/* (files) minimalist cache of alloc info */
	अचिन्हित i_disk_sec;	/* (files) minimalist cache of alloc info */
	अचिन्हित i_n_secs;	/* (files) minimalist cache of alloc info */
	अचिन्हित i_ea_size;	/* size of extended attributes */
	अचिन्हित i_ea_mode : 1;	/* file's permission is stored in ea */
	अचिन्हित i_ea_uid : 1;	/* file's uid is stored in ea */
	अचिन्हित i_ea_gid : 1;	/* file's gid is stored in ea */
	अचिन्हित i_dirty : 1;
	loff_t **i_rddir_off;
	काष्ठा inode vfs_inode;
पूर्ण;

काष्ठा hpfs_sb_info अणु
	काष्ठा mutex hpfs_mutex;	/* global hpfs lock */
	ino_t sb_root;			/* inode number of root dir */
	अचिन्हित sb_fs_size;		/* file प्रणाली size, sectors */
	अचिन्हित sb_biपंचांगaps;		/* sector number of biपंचांगap list */
	अचिन्हित sb_dirband_start;	/* directory band start sector */
	अचिन्हित sb_dirband_size;	/* directory band size, dnodes */
	अचिन्हित sb_dmap;		/* sector number of dnode bit map */
	अचिन्हित sb_n_मुक्त;		/* मुक्त blocks क्रम statfs, or -1 */
	अचिन्हित sb_n_मुक्त_dnodes;	/* मुक्त dnodes क्रम statfs, or -1 */
	kuid_t sb_uid;			/* uid from mount options */
	kgid_t sb_gid;			/* gid from mount options */
	umode_t sb_mode;		/* mode from mount options */
	अचिन्हित sb_eas : 2;		/* eas: 0-ignore, 1-ro, 2-rw */
	अचिन्हित sb_err : 2;		/* on errs: 0-cont, 1-ro, 2-panic */
	अचिन्हित sb_chk : 2;		/* checks: 0-no, 1-normal, 2-strict */
	अचिन्हित sb_lowerहाल : 1;	/* करोwnहाल filenames hackery */
	अचिन्हित sb_was_error : 1;	/* there was an error, set dirty flag */
	अचिन्हित sb_chkdsk : 2;		/* chkdsk: 0-no, 1-on errs, 2-allways */
	अचिन्हित अक्षर *sb_cp_table;	/* code page tables: */
					/* 	128 bytes uppercasing table & */
					/*	128 bytes lowercasing table */
	__le32 *sb_bmp_dir;		/* मुख्य biपंचांगap directory */
	अचिन्हित sb_c_biपंचांगap;		/* current biपंचांगap */
	अचिन्हित sb_max_fwd_alloc;	/* max क्रमwad allocation */
	पूर्णांक sb_बारhअगरt;
	काष्ठा rcu_head rcu;

	अचिन्हित n_hotfixes;
	secno hotfix_from[256];
	secno hotfix_to[256];
पूर्ण;

/* Four 512-byte buffers and the 2k block obtained by concatenating them */

काष्ठा quad_buffer_head अणु
	काष्ठा buffer_head *bh[4];
	व्योम *data;
पूर्ण;

/* The b-tree करोwn poपूर्णांकer from a dir entry */

अटल अंतरभूत dnode_secno de_करोwn_poपूर्णांकer (काष्ठा hpfs_dirent *de)
अणु
  CHKCOND(de->करोwn,("HPFS: de_down_pointer: !de->down\n"));
  वापस le32_to_cpu(*(__le32 *) ((व्योम *) de + le16_to_cpu(de->length) - 4));
पूर्ण

/* The first dir entry in a dnode */

अटल अंतरभूत काष्ठा hpfs_dirent *dnode_first_de (काष्ठा dnode *dnode)
अणु
  वापस (व्योम *) dnode->dirent;
पूर्ण

/* The end+1 of the dir entries */

अटल अंतरभूत काष्ठा hpfs_dirent *dnode_end_de (काष्ठा dnode *dnode)
अणु
  CHKCOND(le32_to_cpu(dnode->first_मुक्त)>=0x14 && le32_to_cpu(dnode->first_मुक्त)<=0xa00,("HPFS: dnode_end_de: dnode->first_free = %x\n",(अचिन्हित)le32_to_cpu(dnode->first_मुक्त)));
  वापस (व्योम *) dnode + le32_to_cpu(dnode->first_मुक्त);
पूर्ण

/* The dir entry after dir entry de */

अटल अंतरभूत काष्ठा hpfs_dirent *de_next_de (काष्ठा hpfs_dirent *de)
अणु
  CHKCOND(le16_to_cpu(de->length)>=0x20 && le16_to_cpu(de->length)<0x800,("HPFS: de_next_de: de->length = %x\n",(अचिन्हित)le16_to_cpu(de->length)));
  वापस (व्योम *) de + le16_to_cpu(de->length);
पूर्ण

अटल अंतरभूत काष्ठा extended_attribute *fnode_ea(काष्ठा fnode *fnode)
अणु
	वापस (काष्ठा extended_attribute *)((अक्षर *)fnode + le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s));
पूर्ण

अटल अंतरभूत काष्ठा extended_attribute *fnode_end_ea(काष्ठा fnode *fnode)
अणु
	वापस (काष्ठा extended_attribute *)((अक्षर *)fnode + le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s));
पूर्ण

अटल अचिन्हित ea_valuelen(काष्ठा extended_attribute *ea)
अणु
	वापस ea->valuelen_lo + 256 * ea->valuelen_hi;
पूर्ण

अटल अंतरभूत काष्ठा extended_attribute *next_ea(काष्ठा extended_attribute *ea)
अणु
	वापस (काष्ठा extended_attribute *)((अक्षर *)ea + 5 + ea->namelen + ea_valuelen(ea));
पूर्ण

अटल अंतरभूत secno ea_sec(काष्ठा extended_attribute *ea)
अणु
	वापस le32_to_cpu(get_unaligned((__le32 *)((अक्षर *)ea + 9 + ea->namelen)));
पूर्ण

अटल अंतरभूत secno ea_len(काष्ठा extended_attribute *ea)
अणु
	वापस le32_to_cpu(get_unaligned((__le32 *)((अक्षर *)ea + 5 + ea->namelen)));
पूर्ण

अटल अंतरभूत अक्षर *ea_data(काष्ठा extended_attribute *ea)
अणु
	वापस (अक्षर *)((अक्षर *)ea + 5 + ea->namelen);
पूर्ण

अटल अंतरभूत अचिन्हित de_size(पूर्णांक namelen, secno करोwn_ptr)
अणु
	वापस ((0x1f + namelen + 3) & ~3) + (करोwn_ptr ? 4 : 0);
पूर्ण

अटल अंतरभूत व्योम copy_de(काष्ठा hpfs_dirent *dst, काष्ठा hpfs_dirent *src)
अणु
	पूर्णांक a;
	पूर्णांक n;
	अगर (!dst || !src) वापस;
	a = dst->करोwn;
	n = dst->not_8x3;
	स_नकल((अक्षर *)dst + 2, (अक्षर *)src + 2, 28);
	dst->करोwn = a;
	dst->not_8x3 = n;
पूर्ण

अटल अंतरभूत अचिन्हित tstbits(__le32 *bmp, अचिन्हित b, अचिन्हित n)
अणु
	पूर्णांक i;
	अगर ((b >= 0x4000) || (b + n - 1 >= 0x4000)) वापस n;
	अगर (!((le32_to_cpu(bmp[(b & 0x3fff) >> 5]) >> (b & 0x1f)) & 1)) वापस 1;
	क्रम (i = 1; i < n; i++)
		अगर (!((le32_to_cpu(bmp[((b+i) & 0x3fff) >> 5]) >> ((b+i) & 0x1f)) & 1))
			वापस i + 1;
	वापस 0;
पूर्ण

/* alloc.c */

पूर्णांक hpfs_chk_sectors(काष्ठा super_block *, secno, पूर्णांक, अक्षर *);
secno hpfs_alloc_sector(काष्ठा super_block *, secno, अचिन्हित, पूर्णांक);
पूर्णांक hpfs_alloc_अगर_possible(काष्ठा super_block *, secno);
व्योम hpfs_मुक्त_sectors(काष्ठा super_block *, secno, अचिन्हित);
पूर्णांक hpfs_check_मुक्त_dnodes(काष्ठा super_block *, पूर्णांक);
व्योम hpfs_मुक्त_dnode(काष्ठा super_block *, secno);
काष्ठा dnode *hpfs_alloc_dnode(काष्ठा super_block *, secno, dnode_secno *, काष्ठा quad_buffer_head *);
काष्ठा fnode *hpfs_alloc_fnode(काष्ठा super_block *, secno, fnode_secno *, काष्ठा buffer_head **);
काष्ठा anode *hpfs_alloc_anode(काष्ठा super_block *, secno, anode_secno *, काष्ठा buffer_head **);
पूर्णांक hpfs_trim_fs(काष्ठा super_block *, u64, u64, u64, अचिन्हित *);

/* anode.c */

secno hpfs_bplus_lookup(काष्ठा super_block *, काष्ठा inode *, काष्ठा bplus_header *, अचिन्हित, काष्ठा buffer_head *);
secno hpfs_add_sector_to_btree(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित);
व्योम hpfs_हटाओ_btree(काष्ठा super_block *, काष्ठा bplus_header *);
पूर्णांक hpfs_ea_पढ़ो(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित, अचिन्हित, अक्षर *);
पूर्णांक hpfs_ea_ग_लिखो(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित, अचिन्हित, स्थिर अक्षर *);
व्योम hpfs_ea_हटाओ(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित);
व्योम hpfs_truncate_btree(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित);
व्योम hpfs_हटाओ_fnode(काष्ठा super_block *, fnode_secno fno);

/* buffer.c */

secno hpfs_search_hotfix_map(काष्ठा super_block *s, secno sec);
अचिन्हित hpfs_search_hotfix_map_क्रम_range(काष्ठा super_block *s, secno sec, अचिन्हित n);
व्योम hpfs_prefetch_sectors(काष्ठा super_block *, अचिन्हित, पूर्णांक);
व्योम *hpfs_map_sector(काष्ठा super_block *, अचिन्हित, काष्ठा buffer_head **, पूर्णांक);
व्योम *hpfs_get_sector(काष्ठा super_block *, अचिन्हित, काष्ठा buffer_head **);
व्योम *hpfs_map_4sectors(काष्ठा super_block *, अचिन्हित, काष्ठा quad_buffer_head *, पूर्णांक);
व्योम *hpfs_get_4sectors(काष्ठा super_block *, अचिन्हित, काष्ठा quad_buffer_head *);
व्योम hpfs_brअन्यथा4(काष्ठा quad_buffer_head *);
व्योम hpfs_mark_4buffers_dirty(काष्ठा quad_buffer_head *);

/* dentry.c */

बाह्य स्थिर काष्ठा dentry_operations hpfs_dentry_operations;

/* dir.c */

काष्ठा dentry *hpfs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
बाह्य स्थिर काष्ठा file_operations hpfs_dir_ops;

/* dnode.c */

पूर्णांक hpfs_add_pos(काष्ठा inode *, loff_t *);
व्योम hpfs_del_pos(काष्ठा inode *, loff_t *);
काष्ठा hpfs_dirent *hpfs_add_de(काष्ठा super_block *, काष्ठा dnode *,
				स्थिर अचिन्हित अक्षर *, अचिन्हित, secno);
पूर्णांक hpfs_add_dirent(काष्ठा inode *, स्थिर अचिन्हित अक्षर *, अचिन्हित,
		    काष्ठा hpfs_dirent *);
पूर्णांक hpfs_हटाओ_dirent(काष्ठा inode *, dnode_secno, काष्ठा hpfs_dirent *, काष्ठा quad_buffer_head *, पूर्णांक);
व्योम hpfs_count_dnodes(काष्ठा super_block *, dnode_secno, पूर्णांक *, पूर्णांक *, पूर्णांक *);
dnode_secno hpfs_de_as_करोwn_as_possible(काष्ठा super_block *, dnode_secno dno);
काष्ठा hpfs_dirent *map_pos_dirent(काष्ठा inode *, loff_t *, काष्ठा quad_buffer_head *);
काष्ठा hpfs_dirent *map_dirent(काष्ठा inode *, dnode_secno,
			       स्थिर अचिन्हित अक्षर *, अचिन्हित, dnode_secno *,
			       काष्ठा quad_buffer_head *);
व्योम hpfs_हटाओ_dtree(काष्ठा super_block *, dnode_secno);
काष्ठा hpfs_dirent *map_fnode_dirent(काष्ठा super_block *, fnode_secno, काष्ठा fnode *, काष्ठा quad_buffer_head *);

/* ea.c */

व्योम hpfs_ea_ext_हटाओ(काष्ठा super_block *, secno, पूर्णांक, अचिन्हित);
पूर्णांक hpfs_पढ़ो_ea(काष्ठा super_block *, काष्ठा fnode *, अक्षर *, अक्षर *, पूर्णांक);
अक्षर *hpfs_get_ea(काष्ठा super_block *, काष्ठा fnode *, अक्षर *, पूर्णांक *);
व्योम hpfs_set_ea(काष्ठा inode *, काष्ठा fnode *, स्थिर अक्षर *,
		 स्थिर अक्षर *, पूर्णांक);

/* file.c */

पूर्णांक hpfs_file_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
व्योम hpfs_truncate(काष्ठा inode *);
बाह्य स्थिर काष्ठा file_operations hpfs_file_ops;
बाह्य स्थिर काष्ठा inode_operations hpfs_file_iops;
बाह्य स्थिर काष्ठा address_space_operations hpfs_aops;

/* inode.c */

व्योम hpfs_init_inode(काष्ठा inode *);
व्योम hpfs_पढ़ो_inode(काष्ठा inode *);
व्योम hpfs_ग_लिखो_inode(काष्ठा inode *);
व्योम hpfs_ग_लिखो_inode_nolock(काष्ठा inode *);
पूर्णांक hpfs_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
व्योम hpfs_ग_लिखो_अगर_changed(काष्ठा inode *);
व्योम hpfs_evict_inode(काष्ठा inode *);

/* map.c */

__le32 *hpfs_map_dnode_biपंचांगap(काष्ठा super_block *, काष्ठा quad_buffer_head *);
__le32 *hpfs_map_biपंचांगap(काष्ठा super_block *, अचिन्हित, काष्ठा quad_buffer_head *, अक्षर *);
व्योम hpfs_prefetch_biपंचांगap(काष्ठा super_block *, अचिन्हित);
अचिन्हित अक्षर *hpfs_load_code_page(काष्ठा super_block *, secno);
__le32 *hpfs_load_biपंचांगap_directory(काष्ठा super_block *, secno bmp);
व्योम hpfs_load_hotfix_map(काष्ठा super_block *s, काष्ठा hpfs_spare_block *spareblock);
काष्ठा fnode *hpfs_map_fnode(काष्ठा super_block *s, ino_t, काष्ठा buffer_head **);
काष्ठा anode *hpfs_map_anode(काष्ठा super_block *s, anode_secno, काष्ठा buffer_head **);
काष्ठा dnode *hpfs_map_dnode(काष्ठा super_block *s, dnode_secno, काष्ठा quad_buffer_head *);
dnode_secno hpfs_fnode_dno(काष्ठा super_block *s, ino_t ino);

/* name.c */

अचिन्हित अक्षर hpfs_upहाल(अचिन्हित अक्षर *, अचिन्हित अक्षर);
पूर्णांक hpfs_chk_name(स्थिर अचिन्हित अक्षर *, अचिन्हित *);
अचिन्हित अक्षर *hpfs_translate_name(काष्ठा super_block *, अचिन्हित अक्षर *, अचिन्हित, पूर्णांक, पूर्णांक);
पूर्णांक hpfs_compare_names(काष्ठा super_block *, स्थिर अचिन्हित अक्षर *, अचिन्हित,
		       स्थिर अचिन्हित अक्षर *, अचिन्हित, पूर्णांक);
पूर्णांक hpfs_is_name_दीर्घ(स्थिर अचिन्हित अक्षर *, अचिन्हित);
व्योम hpfs_adjust_length(स्थिर अचिन्हित अक्षर *, अचिन्हित *);

/* namei.c */

बाह्य स्थिर काष्ठा inode_operations hpfs_dir_iops;
बाह्य स्थिर काष्ठा address_space_operations hpfs_symlink_aops;

अटल अंतरभूत काष्ठा hpfs_inode_info *hpfs_i(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा hpfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा hpfs_sb_info *hpfs_sb(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/* super.c */

__म_लिखो(2, 3)
व्योम hpfs_error(काष्ठा super_block *, स्थिर अक्षर *, ...);
पूर्णांक hpfs_stop_cycles(काष्ठा super_block *, पूर्णांक, पूर्णांक *, पूर्णांक *, अक्षर *);
अचिन्हित hpfs_get_मुक्त_dnodes(काष्ठा super_block *);
दीर्घ hpfs_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg);

/*
 * local समय (HPFS) to GMT (Unix)
 */

अटल अंतरभूत समय64_t local_to_gmt(काष्ठा super_block *s, समय64_t t)
अणु
	बाह्य काष्ठा समयzone sys_tz;
	वापस t + sys_tz.tz_minuteswest * 60 + hpfs_sb(s)->sb_बारhअगरt;
पूर्ण

अटल अंतरभूत समय32_t gmt_to_local(काष्ठा super_block *s, समय64_t t)
अणु
	बाह्य काष्ठा समयzone sys_tz;
	वापस t - sys_tz.tz_minuteswest * 60 - hpfs_sb(s)->sb_बारhअगरt;
पूर्ण

अटल अंतरभूत समय32_t local_get_seconds(काष्ठा super_block *s)
अणु
	वापस gmt_to_local(s, kसमय_get_real_seconds());
पूर्ण

/*
 * Locking:
 *
 * hpfs_lock() locks the whole fileप्रणाली. It must be taken
 * on any method called by the VFS.
 *
 * We करोn't करो any per-file locking anymore, it is hard to
 * review and HPFS is not perक्रमmance-sensitive anyway.
 */
अटल अंतरभूत व्योम hpfs_lock(काष्ठा super_block *s)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	mutex_lock(&sbi->hpfs_mutex);
पूर्ण

अटल अंतरभूत व्योम hpfs_unlock(काष्ठा super_block *s)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	mutex_unlock(&sbi->hpfs_mutex);
पूर्ण

अटल अंतरभूत व्योम hpfs_lock_निश्चित(काष्ठा super_block *s)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	WARN_ON(!mutex_is_locked(&sbi->hpfs_mutex));
पूर्ण
