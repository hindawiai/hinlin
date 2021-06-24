<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/uuid.h>
#समावेश <linux/fs.h>
#समावेश "ovl_entry.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "overlayfs: " fmt

क्रमागत ovl_path_type अणु
	__OVL_PATH_UPPER	= (1 << 0),
	__OVL_PATH_MERGE	= (1 << 1),
	__OVL_PATH_ORIGIN	= (1 << 2),
पूर्ण;

#घोषणा OVL_TYPE_UPPER(type)	((type) & __OVL_PATH_UPPER)
#घोषणा OVL_TYPE_MERGE(type)	((type) & __OVL_PATH_MERGE)
#घोषणा OVL_TYPE_ORIGIN(type)	((type) & __OVL_PATH_ORIGIN)

#घोषणा OVL_XATTR_NAMESPACE "overlay."
#घोषणा OVL_XATTR_TRUSTED_PREFIX XATTR_TRUSTED_PREFIX OVL_XATTR_NAMESPACE
#घोषणा OVL_XATTR_USER_PREFIX XATTR_USER_PREFIX OVL_XATTR_NAMESPACE

क्रमागत ovl_xattr अणु
	OVL_XATTR_OPAQUE,
	OVL_XATTR_REसूचीECT,
	OVL_XATTR_ORIGIN,
	OVL_XATTR_IMPURE,
	OVL_XATTR_NLINK,
	OVL_XATTR_UPPER,
	OVL_XATTR_METACOPY,
पूर्ण;

क्रमागत ovl_inode_flag अणु
	/* Pure upper dir that may contain non pure upper entries */
	OVL_IMPURE,
	/* Non-merge dir that may contain whiteout entries */
	OVL_WHITEOUTS,
	OVL_INDEX,
	OVL_UPPERDATA,
	/* Inode number will reमुख्य स्थिरant over copy up. */
	OVL_CONST_INO,
पूर्ण;

क्रमागत ovl_entry_flag अणु
	OVL_E_UPPER_ALIAS,
	OVL_E_OPAQUE,
	OVL_E_CONNECTED,
पूर्ण;

क्रमागत अणु
	OVL_XINO_OFF,
	OVL_XINO_AUTO,
	OVL_XINO_ON,
पूर्ण;

/*
 * The tuple (fh,uuid) is a universal unique identअगरier क्रम a copy up origin,
 * where:
 * origin.fh	- exported file handle of the lower file
 * origin.uuid	- uuid of the lower fileप्रणाली
 */
#घोषणा OVL_FH_VERSION	0
#घोषणा OVL_FH_MAGIC	0xfb

/* CPU byte order required क्रम fid decoding:  */
#घोषणा OVL_FH_FLAG_BIG_ENDIAN	(1 << 0)
#घोषणा OVL_FH_FLAG_ANY_ENDIAN	(1 << 1)
/* Is the real inode encoded in fid an upper inode? */
#घोषणा OVL_FH_FLAG_PATH_UPPER	(1 << 2)

#घोषणा OVL_FH_FLAG_ALL (OVL_FH_FLAG_BIG_ENDIAN | OVL_FH_FLAG_ANY_ENDIAN | \
			 OVL_FH_FLAG_PATH_UPPER)

#अगर defined(__LITTLE_ENDIAN)
#घोषणा OVL_FH_FLAG_CPU_ENDIAN 0
#या_अगर defined(__BIG_ENDIAN)
#घोषणा OVL_FH_FLAG_CPU_ENDIAN OVL_FH_FLAG_BIG_ENDIAN
#अन्यथा
#त्रुटि Endianness not defined
#पूर्ण_अगर

/* The type used to be वापसed by overlay exportfs क्रम misaligned fid */
#घोषणा OVL_खाताID_V0	0xfb
/* The type वापसed by overlay exportfs क्रम 32bit aligned fid */
#घोषणा OVL_खाताID_V1	0xf8

/* On-disk क्रमmat क्रम "origin" file handle */
काष्ठा ovl_fb अणु
	u8 version;	/* 0 */
	u8 magic;	/* 0xfb */
	u8 len;		/* size of this header + size of fid */
	u8 flags;	/* OVL_FH_FLAG_* */
	u8 type;	/* fid_type of fid */
	uuid_t uuid;	/* uuid of fileप्रणाली */
	u32 fid[];	/* file identअगरier should be 32bit aligned in-memory */
पूर्ण __packed;

/* In-memory and on-wire क्रमmat क्रम overlay file handle */
काष्ठा ovl_fh अणु
	u8 padding[3];	/* make sure fb.fid is 32bit aligned */
	जोड़ अणु
		काष्ठा ovl_fb fb;
		u8 buf[0];
	पूर्ण;
पूर्ण __packed;

#घोषणा OVL_FH_WIRE_OFFSET	दुरत्व(काष्ठा ovl_fh, fb)
#घोषणा OVL_FH_LEN(fh)		(OVL_FH_WIRE_OFFSET + (fh)->fb.len)
#घोषणा OVL_FH_FID_OFFSET	(OVL_FH_WIRE_OFFSET + \
				 दुरत्व(काष्ठा ovl_fb, fid))

बाह्य स्थिर अक्षर *स्थिर ovl_xattr_table[][2];
अटल अंतरभूत स्थिर अक्षर *ovl_xattr(काष्ठा ovl_fs *ofs, क्रमागत ovl_xattr ox)
अणु
	वापस ovl_xattr_table[ox][ofs->config.userxattr];
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक err = vfs_सूची_हटाओ(&init_user_ns, dir, dentry);

	pr_debug("rmdir(%pd2) = %i\n", dentry, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक err = vfs_unlink(&init_user_ns, dir, dentry, शून्य);

	pr_debug("unlink(%pd2) = %i\n", dentry, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			      काष्ठा dentry *new_dentry)
अणु
	पूर्णांक err = vfs_link(old_dentry, &init_user_ns, dir, new_dentry, शून्य);

	pr_debug("link(%pd2, %pd2) = %i\n", old_dentry, new_dentry, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_create(काष्ठा inode *dir, काष्ठा dentry *dentry,
				umode_t mode)
अणु
	पूर्णांक err = vfs_create(&init_user_ns, dir, dentry, mode, true);

	pr_debug("create(%pd2, 0%o) = %i\n", dentry, mode, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t mode)
अणु
	पूर्णांक err = vfs_सूची_गढ़ो(&init_user_ns, dir, dentry, mode);
	pr_debug("mkdir(%pd2, 0%o) = %i\n", dentry, mode, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t mode, dev_t dev)
अणु
	पूर्णांक err = vfs_mknod(&init_user_ns, dir, dentry, mode, dev);

	pr_debug("mknod(%pd2, 0%o, 0%o) = %i\n", dentry, mode, dev, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 स्थिर अक्षर *oldname)
अणु
	पूर्णांक err = vfs_symlink(&init_user_ns, dir, dentry, oldname);

	pr_debug("symlink(\"%s\", %pd2) = %i\n", oldname, dentry, err);
	वापस err;
पूर्ण

अटल अंतरभूत sमाप_प्रकार ovl_करो_getxattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
				      क्रमागत ovl_xattr ox, व्योम *value,
				      माप_प्रकार size)
अणु
	स्थिर अक्षर *name = ovl_xattr(ofs, ox);
	पूर्णांक err = vfs_getxattr(&init_user_ns, dentry, name, value, size);
	पूर्णांक len = (value && err > 0) ? err : 0;

	pr_debug("getxattr(%pd2, \"%s\", \"%*pE\", %zu, 0) = %i\n",
		 dentry, name, min(len, 48), value, size, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_setxattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
				  क्रमागत ovl_xattr ox, स्थिर व्योम *value,
				  माप_प्रकार size)
अणु
	स्थिर अक्षर *name = ovl_xattr(ofs, ox);
	पूर्णांक err = vfs_setxattr(&init_user_ns, dentry, name, value, size, 0);
	pr_debug("setxattr(%pd2, \"%s\", \"%*pE\", %zu, 0) = %i\n",
		 dentry, name, min((पूर्णांक)size, 48), value, size, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_हटाओxattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
				     क्रमागत ovl_xattr ox)
अणु
	स्थिर अक्षर *name = ovl_xattr(ofs, ox);
	पूर्णांक err = vfs_हटाओxattr(&init_user_ns, dentry, name);
	pr_debug("removexattr(%pd2, \"%s\") = %i\n", dentry, name, err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_नाम(काष्ठा inode *olddir, काष्ठा dentry *olddentry,
				काष्ठा inode *newdir, काष्ठा dentry *newdentry,
				अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा नामdata rd = अणु
		.old_mnt_userns	= &init_user_ns,
		.old_dir 	= olddir,
		.old_dentry 	= olddentry,
		.new_mnt_userns	= &init_user_ns,
		.new_dir 	= newdir,
		.new_dentry 	= newdentry,
		.flags 		= flags,
	पूर्ण;

	pr_debug("rename(%pd2, %pd2, 0x%x)\n", olddentry, newdentry, flags);
	err = vfs_नाम(&rd);
	अगर (err) अणु
		pr_debug("...rename(%pd2, %pd2, ...) = %i\n",
			 olddentry, newdentry, err);
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_करो_whiteout(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक err = vfs_whiteout(&init_user_ns, dir, dentry);
	pr_debug("whiteout(%pd2) = %i\n", dentry, err);
	वापस err;
पूर्ण

अटल अंतरभूत काष्ठा dentry *ovl_करो_क्षणिक_ख(काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा dentry *ret = vfs_क्षणिक_ख(&init_user_ns, dentry, mode, 0);
	पूर्णांक err = PTR_ERR_OR_ZERO(ret);

	pr_debug("tmpfile(%pd2, 0%o) = %i\n", dentry, mode, err);
	वापस ret;
पूर्ण

अटल अंतरभूत bool ovl_खोलो_flags_need_copy_up(पूर्णांक flags)
अणु
	अगर (!flags)
		वापस false;

	वापस ((OPEN_FMODE(flags) & FMODE_WRITE) || (flags & O_TRUNC));
पूर्ण

/* util.c */
पूर्णांक ovl_want_ग_लिखो(काष्ठा dentry *dentry);
व्योम ovl_drop_ग_लिखो(काष्ठा dentry *dentry);
काष्ठा dentry *ovl_workdir(काष्ठा dentry *dentry);
स्थिर काष्ठा cred *ovl_override_creds(काष्ठा super_block *sb);
पूर्णांक ovl_can_decode_fh(काष्ठा super_block *sb);
काष्ठा dentry *ovl_indexdir(काष्ठा super_block *sb);
bool ovl_index_all(काष्ठा super_block *sb);
bool ovl_verअगरy_lower(काष्ठा super_block *sb);
काष्ठा ovl_entry *ovl_alloc_entry(अचिन्हित पूर्णांक numlower);
bool ovl_dentry_remote(काष्ठा dentry *dentry);
व्योम ovl_dentry_update_reval(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry,
			     अचिन्हित पूर्णांक mask);
bool ovl_dentry_weird(काष्ठा dentry *dentry);
क्रमागत ovl_path_type ovl_path_type(काष्ठा dentry *dentry);
व्योम ovl_path_upper(काष्ठा dentry *dentry, काष्ठा path *path);
व्योम ovl_path_lower(काष्ठा dentry *dentry, काष्ठा path *path);
व्योम ovl_path_lowerdata(काष्ठा dentry *dentry, काष्ठा path *path);
क्रमागत ovl_path_type ovl_path_real(काष्ठा dentry *dentry, काष्ठा path *path);
काष्ठा dentry *ovl_dentry_upper(काष्ठा dentry *dentry);
काष्ठा dentry *ovl_dentry_lower(काष्ठा dentry *dentry);
काष्ठा dentry *ovl_dentry_lowerdata(काष्ठा dentry *dentry);
स्थिर काष्ठा ovl_layer *ovl_layer_lower(काष्ठा dentry *dentry);
काष्ठा dentry *ovl_dentry_real(काष्ठा dentry *dentry);
काष्ठा dentry *ovl_i_dentry_upper(काष्ठा inode *inode);
काष्ठा inode *ovl_inode_upper(काष्ठा inode *inode);
काष्ठा inode *ovl_inode_lower(काष्ठा inode *inode);
काष्ठा inode *ovl_inode_lowerdata(काष्ठा inode *inode);
काष्ठा inode *ovl_inode_real(काष्ठा inode *inode);
काष्ठा inode *ovl_inode_realdata(काष्ठा inode *inode);
काष्ठा ovl_dir_cache *ovl_dir_cache(काष्ठा inode *inode);
व्योम ovl_set_dir_cache(काष्ठा inode *inode, काष्ठा ovl_dir_cache *cache);
व्योम ovl_dentry_set_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry);
व्योम ovl_dentry_clear_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry);
bool ovl_dentry_test_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry);
bool ovl_dentry_is_opaque(काष्ठा dentry *dentry);
bool ovl_dentry_is_whiteout(काष्ठा dentry *dentry);
व्योम ovl_dentry_set_opaque(काष्ठा dentry *dentry);
bool ovl_dentry_has_upper_alias(काष्ठा dentry *dentry);
व्योम ovl_dentry_set_upper_alias(काष्ठा dentry *dentry);
bool ovl_dentry_needs_data_copy_up(काष्ठा dentry *dentry, पूर्णांक flags);
bool ovl_dentry_needs_data_copy_up_locked(काष्ठा dentry *dentry, पूर्णांक flags);
bool ovl_has_upperdata(काष्ठा inode *inode);
व्योम ovl_set_upperdata(काष्ठा inode *inode);
bool ovl_redirect_dir(काष्ठा super_block *sb);
स्थिर अक्षर *ovl_dentry_get_redirect(काष्ठा dentry *dentry);
व्योम ovl_dentry_set_redirect(काष्ठा dentry *dentry, स्थिर अक्षर *redirect);
व्योम ovl_inode_update(काष्ठा inode *inode, काष्ठा dentry *upperdentry);
व्योम ovl_dir_modअगरied(काष्ठा dentry *dentry, bool impurity);
u64 ovl_dentry_version_get(काष्ठा dentry *dentry);
bool ovl_is_whiteout(काष्ठा dentry *dentry);
काष्ठा file *ovl_path_खोलो(काष्ठा path *path, पूर्णांक flags);
पूर्णांक ovl_copy_up_start(काष्ठा dentry *dentry, पूर्णांक flags);
व्योम ovl_copy_up_end(काष्ठा dentry *dentry);
bool ovl_alपढ़ोy_copied_up(काष्ठा dentry *dentry, पूर्णांक flags);
bool ovl_check_origin_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry);
bool ovl_check_dir_xattr(काष्ठा super_block *sb, काष्ठा dentry *dentry,
			 क्रमागत ovl_xattr ox);
पूर्णांक ovl_check_setxattr(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry,
		       क्रमागत ovl_xattr ox, स्थिर व्योम *value, माप_प्रकार size,
		       पूर्णांक xerr);
पूर्णांक ovl_set_impure(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry);
bool ovl_inuse_trylock(काष्ठा dentry *dentry);
व्योम ovl_inuse_unlock(काष्ठा dentry *dentry);
bool ovl_is_inuse(काष्ठा dentry *dentry);
bool ovl_need_index(काष्ठा dentry *dentry);
पूर्णांक ovl_nlink_start(काष्ठा dentry *dentry);
व्योम ovl_nlink_end(काष्ठा dentry *dentry);
पूर्णांक ovl_lock_नाम_workdir(काष्ठा dentry *workdir, काष्ठा dentry *upperdir);
पूर्णांक ovl_check_metacopy_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry);
bool ovl_is_metacopy_dentry(काष्ठा dentry *dentry);
अक्षर *ovl_get_redirect_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
			     पूर्णांक padding);
पूर्णांक ovl_sync_status(काष्ठा ovl_fs *ofs);

अटल अंतरभूत व्योम ovl_set_flag(अचिन्हित दीर्घ flag, काष्ठा inode *inode)
अणु
	set_bit(flag, &OVL_I(inode)->flags);
पूर्ण

अटल अंतरभूत व्योम ovl_clear_flag(अचिन्हित दीर्घ flag, काष्ठा inode *inode)
अणु
	clear_bit(flag, &OVL_I(inode)->flags);
पूर्ण

अटल अंतरभूत bool ovl_test_flag(अचिन्हित दीर्घ flag, काष्ठा inode *inode)
अणु
	वापस test_bit(flag, &OVL_I(inode)->flags);
पूर्ण

अटल अंतरभूत bool ovl_is_impuredir(काष्ठा super_block *sb,
				    काष्ठा dentry *dentry)
अणु
	वापस ovl_check_dir_xattr(sb, dentry, OVL_XATTR_IMPURE);
पूर्ण

/*
 * With xino=स्वतः, we करो best efक्रमt to keep all inodes on same st_dev and
 * d_ino consistent with st_ino.
 * With xino=on, we करो the same efक्रमt but we warn अगर we failed.
 */
अटल अंतरभूत bool ovl_xino_warn(काष्ठा super_block *sb)
अणु
	वापस OVL_FS(sb)->config.xino == OVL_XINO_ON;
पूर्ण

/* All layers on same fs? */
अटल अंतरभूत bool ovl_same_fs(काष्ठा super_block *sb)
अणु
	वापस OVL_FS(sb)->xino_mode == 0;
पूर्ण

/* All overlay inodes have same st_dev? */
अटल अंतरभूत bool ovl_same_dev(काष्ठा super_block *sb)
अणु
	वापस OVL_FS(sb)->xino_mode >= 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ovl_xino_bits(काष्ठा super_block *sb)
अणु
	वापस ovl_same_dev(sb) ? OVL_FS(sb)->xino_mode : 0;
पूर्ण

अटल अंतरभूत व्योम ovl_inode_lock(काष्ठा inode *inode)
अणु
	mutex_lock(&OVL_I(inode)->lock);
पूर्ण

अटल अंतरभूत पूर्णांक ovl_inode_lock_पूर्णांकerruptible(काष्ठा inode *inode)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&OVL_I(inode)->lock);
पूर्ण

अटल अंतरभूत व्योम ovl_inode_unlock(काष्ठा inode *inode)
अणु
	mutex_unlock(&OVL_I(inode)->lock);
पूर्ण


/* namei.c */
पूर्णांक ovl_check_fb_len(काष्ठा ovl_fb *fb, पूर्णांक fb_len);

अटल अंतरभूत पूर्णांक ovl_check_fh_len(काष्ठा ovl_fh *fh, पूर्णांक fh_len)
अणु
	अगर (fh_len < माप(काष्ठा ovl_fh))
		वापस -EINVAL;

	वापस ovl_check_fb_len(&fh->fb, fh_len - OVL_FH_WIRE_OFFSET);
पूर्ण

काष्ठा dentry *ovl_decode_real_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh,
				  काष्ठा vfsmount *mnt, bool connected);
पूर्णांक ovl_check_origin_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh, bool connected,
			काष्ठा dentry *upperdentry, काष्ठा ovl_path **stackp);
पूर्णांक ovl_verअगरy_set_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
		      क्रमागत ovl_xattr ox, काष्ठा dentry *real, bool is_upper,
		      bool set);
काष्ठा dentry *ovl_index_upper(काष्ठा ovl_fs *ofs, काष्ठा dentry *index);
पूर्णांक ovl_verअगरy_index(काष्ठा ovl_fs *ofs, काष्ठा dentry *index);
पूर्णांक ovl_get_index_name(काष्ठा ovl_fs *ofs, काष्ठा dentry *origin,
		       काष्ठा qstr *name);
काष्ठा dentry *ovl_get_index_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh);
काष्ठा dentry *ovl_lookup_index(काष्ठा ovl_fs *ofs, काष्ठा dentry *upper,
				काष्ठा dentry *origin, bool verअगरy);
पूर्णांक ovl_path_next(पूर्णांक idx, काष्ठा dentry *dentry, काष्ठा path *path);
काष्ठा dentry *ovl_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			  अचिन्हित पूर्णांक flags);
bool ovl_lower_positive(काष्ठा dentry *dentry);

अटल अंतरभूत पूर्णांक ovl_verअगरy_origin(काष्ठा ovl_fs *ofs, काष्ठा dentry *upper,
				    काष्ठा dentry *origin, bool set)
अणु
	वापस ovl_verअगरy_set_fh(ofs, upper, OVL_XATTR_ORIGIN, origin,
				 false, set);
पूर्ण

अटल अंतरभूत पूर्णांक ovl_verअगरy_upper(काष्ठा ovl_fs *ofs, काष्ठा dentry *index,
				   काष्ठा dentry *upper, bool set)
अणु
	वापस ovl_verअगरy_set_fh(ofs, index, OVL_XATTR_UPPER, upper, true, set);
पूर्ण

/* सूची_पढ़ो.c */
बाह्य स्थिर काष्ठा file_operations ovl_dir_operations;
काष्ठा file *ovl_dir_real_file(स्थिर काष्ठा file *file, bool want_upper);
पूर्णांक ovl_check_empty_dir(काष्ठा dentry *dentry, काष्ठा list_head *list);
व्योम ovl_cleanup_whiteouts(काष्ठा dentry *upper, काष्ठा list_head *list);
व्योम ovl_cache_मुक्त(काष्ठा list_head *list);
व्योम ovl_dir_cache_मुक्त(काष्ठा inode *inode);
पूर्णांक ovl_check_d_type_supported(काष्ठा path *realpath);
पूर्णांक ovl_workdir_cleanup(काष्ठा inode *dir, काष्ठा vfsmount *mnt,
			काष्ठा dentry *dentry, पूर्णांक level);
पूर्णांक ovl_indexdir_cleanup(काष्ठा ovl_fs *ofs);

/*
 * Can we iterate real dir directly?
 *
 * Non-merge dir may contain whiteouts from a समय it was a merge upper, beक्रमe
 * lower dir was हटाओd under it and possibly beक्रमe it was rotated from upper
 * to lower layer.
 */
अटल अंतरभूत bool ovl_dir_is_real(काष्ठा dentry *dir)
अणु
	वापस !ovl_test_flag(OVL_WHITEOUTS, d_inode(dir));
पूर्ण

/* inode.c */
पूर्णांक ovl_set_nlink_upper(काष्ठा dentry *dentry);
पूर्णांक ovl_set_nlink_lower(काष्ठा dentry *dentry);
अचिन्हित पूर्णांक ovl_get_nlink(काष्ठा ovl_fs *ofs, काष्ठा dentry *lowerdentry,
			   काष्ठा dentry *upperdentry,
			   अचिन्हित पूर्णांक fallback);
पूर्णांक ovl_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *attr);
पूर्णांक ovl_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags);
पूर्णांक ovl_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		   पूर्णांक mask);
पूर्णांक ovl_xattr_set(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
		  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक ovl_xattr_get(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
		  व्योम *value, माप_प्रकार size);
sमाप_प्रकार ovl_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size);
काष्ठा posix_acl *ovl_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक ovl_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *ts, पूर्णांक flags);
bool ovl_is_निजी_xattr(काष्ठा super_block *sb, स्थिर अक्षर *name);

काष्ठा ovl_inode_params अणु
	काष्ठा inode *newinode;
	काष्ठा dentry *upperdentry;
	काष्ठा ovl_path *lowerpath;
	bool index;
	अचिन्हित पूर्णांक numlower;
	अक्षर *redirect;
	काष्ठा dentry *lowerdata;
पूर्ण;
व्योम ovl_inode_init(काष्ठा inode *inode, काष्ठा ovl_inode_params *oip,
		    अचिन्हित दीर्घ ino, पूर्णांक fsid);
काष्ठा inode *ovl_new_inode(काष्ठा super_block *sb, umode_t mode, dev_t rdev);
काष्ठा inode *ovl_lookup_inode(काष्ठा super_block *sb, काष्ठा dentry *real,
			       bool is_upper);
bool ovl_lookup_trap_inode(काष्ठा super_block *sb, काष्ठा dentry *dir);
काष्ठा inode *ovl_get_trap_inode(काष्ठा super_block *sb, काष्ठा dentry *dir);
काष्ठा inode *ovl_get_inode(काष्ठा super_block *sb,
			    काष्ठा ovl_inode_params *oip);
अटल अंतरभूत व्योम ovl_copyattr(काष्ठा inode *from, काष्ठा inode *to)
अणु
	to->i_uid = from->i_uid;
	to->i_gid = from->i_gid;
	to->i_mode = from->i_mode;
	to->i_aसमय = from->i_aसमय;
	to->i_mसमय = from->i_mसमय;
	to->i_स_समय = from->i_स_समय;
	i_size_ग_लिखो(to, i_size_पढ़ो(from));
पूर्ण

अटल अंतरभूत व्योम ovl_copyflags(काष्ठा inode *from, काष्ठा inode *to)
अणु
	अचिन्हित पूर्णांक mask = S_SYNC | S_IMMUTABLE | S_APPEND | S_NOATIME;

	inode_set_flags(to, from->i_flags & mask, mask);
पूर्ण

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations ovl_dir_inode_operations;
पूर्णांक ovl_cleanup_and_whiteout(काष्ठा ovl_fs *ofs, काष्ठा inode *dir,
			     काष्ठा dentry *dentry);
काष्ठा ovl_cattr अणु
	dev_t rdev;
	umode_t mode;
	स्थिर अक्षर *link;
	काष्ठा dentry *hardlink;
पूर्ण;

#घोषणा OVL_CATTR(m) (&(काष्ठा ovl_cattr) अणु .mode = (m) पूर्ण)

काष्ठा dentry *ovl_create_real(काष्ठा inode *dir, काष्ठा dentry *newdentry,
			       काष्ठा ovl_cattr *attr);
पूर्णांक ovl_cleanup(काष्ठा inode *dir, काष्ठा dentry *dentry);
काष्ठा dentry *ovl_lookup_temp(काष्ठा dentry *workdir);
काष्ठा dentry *ovl_create_temp(काष्ठा dentry *workdir, काष्ठा ovl_cattr *attr);

/* file.c */
बाह्य स्थिर काष्ठा file_operations ovl_file_operations;
पूर्णांक __init ovl_aio_request_cache_init(व्योम);
व्योम ovl_aio_request_cache_destroy(व्योम);
पूर्णांक ovl_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक ovl_fileattr_set(काष्ठा user_namespace *mnt_userns,
		     काष्ठा dentry *dentry, काष्ठा fileattr *fa);

/* copy_up.c */
पूर्णांक ovl_copy_up(काष्ठा dentry *dentry);
पूर्णांक ovl_copy_up_with_data(काष्ठा dentry *dentry);
पूर्णांक ovl_maybe_copy_up(काष्ठा dentry *dentry, पूर्णांक flags);
पूर्णांक ovl_copy_xattr(काष्ठा super_block *sb, काष्ठा dentry *old,
		   काष्ठा dentry *new);
पूर्णांक ovl_set_attr(काष्ठा dentry *upper, काष्ठा kstat *stat);
काष्ठा ovl_fh *ovl_encode_real_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *real,
				  bool is_upper);
पूर्णांक ovl_set_origin(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
		   काष्ठा dentry *lower, काष्ठा dentry *upper);

/* export.c */
बाह्य स्थिर काष्ठा export_operations ovl_export_operations;
