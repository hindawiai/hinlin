<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_EXPORTFS_H
#घोषणा LINUX_EXPORTFS_H 1

#समावेश <linux/types.h>

काष्ठा dentry;
काष्ठा iattr;
काष्ठा inode;
काष्ठा iomap;
काष्ठा super_block;
काष्ठा vfsmount;

/* limit the handle size to NFSv4 handle size now */
#घोषणा MAX_HANDLE_SZ 128

/*
 * The fileid_type identअगरies how the file within the fileप्रणाली is encoded.
 * In theory this is मुक्तly set and parsed by the fileप्रणाली, but we try to
 * stick to conventions so we can share some generic code and करोn't confuse
 * snअगरfers like ethereal/wireshark.
 *
 * The fileप्रणाली must not use the value '0' or '0xff'.
 */
क्रमागत fid_type अणु
	/*
	 * The root, or export poपूर्णांक, of the fileप्रणाली.
	 * (Never actually passed करोwn to the fileप्रणाली.
	 */
	खाताID_ROOT = 0,

	/*
	 * 32bit inode number, 32 bit generation number.
	 */
	खाताID_INO32_GEN = 1,

	/*
	 * 32bit inode number, 32 bit generation number,
	 * 32 bit parent directory inode number.
	 */
	खाताID_INO32_GEN_PARENT = 2,

	/*
	 * 64 bit object ID, 64 bit root object ID,
	 * 32 bit generation number.
	 */
	खाताID_BTRFS_WITHOUT_PARENT = 0x4d,

	/*
	 * 64 bit object ID, 64 bit root object ID,
	 * 32 bit generation number,
	 * 64 bit parent object ID, 32 bit parent generation.
	 */
	खाताID_BTRFS_WITH_PARENT = 0x4e,

	/*
	 * 64 bit object ID, 64 bit root object ID,
	 * 32 bit generation number,
	 * 64 bit parent object ID, 32 bit parent generation,
	 * 64 bit parent root object ID.
	 */
	खाताID_BTRFS_WITH_PARENT_ROOT = 0x4f,

	/*
	 * 32 bit block number, 16 bit partition reference,
	 * 16 bit unused, 32 bit generation number.
	 */
	खाताID_UDF_WITHOUT_PARENT = 0x51,

	/*
	 * 32 bit block number, 16 bit partition reference,
	 * 16 bit unused, 32 bit generation number,
	 * 32 bit parent block number, 32 bit parent generation number
	 */
	खाताID_UDF_WITH_PARENT = 0x52,

	/*
	 * 64 bit checkpoपूर्णांक number, 64 bit inode number,
	 * 32 bit generation number.
	 */
	खाताID_NILFS_WITHOUT_PARENT = 0x61,

	/*
	 * 64 bit checkpoपूर्णांक number, 64 bit inode number,
	 * 32 bit generation number, 32 bit parent generation.
	 * 64 bit parent inode number.
	 */
	खाताID_NILFS_WITH_PARENT = 0x62,

	/*
	 * 32 bit generation number, 40 bit i_pos.
	 */
	खाताID_FAT_WITHOUT_PARENT = 0x71,

	/*
	 * 32 bit generation number, 40 bit i_pos,
	 * 32 bit parent generation number, 40 bit parent i_pos
	 */
	खाताID_FAT_WITH_PARENT = 0x72,

	/*
	 * 128 bit child FID (काष्ठा lu_fid)
	 * 128 bit parent FID (काष्ठा lu_fid)
	 */
	खाताID_LUSTRE = 0x97,

	/*
	 * 64 bit unique kernfs id
	 */
	खाताID_KERNFS = 0xfe,

	/*
	 * Fileप्रणालीs must not use 0xff file ID.
	 */
	खाताID_INVALID = 0xff,
पूर्ण;

काष्ठा fid अणु
	जोड़ अणु
		काष्ठा अणु
			u32 ino;
			u32 gen;
			u32 parent_ino;
			u32 parent_gen;
		पूर्ण i32;
 		काष्ठा अणु
 			u32 block;
 			u16 partref;
 			u16 parent_partref;
 			u32 generation;
 			u32 parent_block;
 			u32 parent_generation;
 		पूर्ण udf;
		__u32 raw[0];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा export_operations - क्रम nfsd to communicate with file प्रणालीs
 * @encode_fh:      encode a file handle fragment from a dentry
 * @fh_to_dentry:   find the implied object and get a dentry क्रम it
 * @fh_to_parent:   find the implied object's parent and get a dentry क्रम it
 * @get_name:       find the name क्रम a given inode in a given directory
 * @get_parent:     find the parent of a given directory
 * @commit_metadata: commit metadata changes to stable storage
 *
 * See Documentation/fileप्रणालीs/nfs/exporting.rst क्रम details on how to use
 * this पूर्णांकerface correctly.
 *
 * encode_fh:
 *    @encode_fh should store in the file handle fragment @fh (using at most
 *    @max_len bytes) inक्रमmation that can be used by @decode_fh to recover the
 *    file referred to by the &काष्ठा dentry @de.  If the @connectable flag is
 *    set, the encode_fh() should store sufficient inक्रमmation so that a good
 *    attempt can be made to find not only the file but also it's place in the
 *    fileप्रणाली.   This typically means storing a reference to de->d_parent in
 *    the filehandle fragment.  encode_fh() should वापस the fileid_type on
 *    success and on error वापसs 255 (अगर the space needed to encode fh is
 *    greater than @max_len*4 bytes). On error @max_len contains the minimum
 *    size(in 4 byte unit) needed to encode the file handle.
 *
 * fh_to_dentry:
 *    @fh_to_dentry is given a &काष्ठा super_block (@sb) and a file handle
 *    fragment (@fh, @fh_len). It should वापस a &काष्ठा dentry which refers
 *    to the same file that the file handle fragment refers to.  If it cannot,
 *    it should वापस a %शून्य poपूर्णांकer अगर the file cannot be found, or an
 *    %ERR_PTR error code of %ENOMEM अगर a memory allocation failure occurred.
 *    Any other error code is treated like %शून्य, and will cause an %ESTALE error
 *    क्रम callers of exportfs_decode_fh().
 *    Any suitable dentry can be वापसed including, अगर necessary, a new dentry
 *    created with d_alloc_root.  The caller can then find any other extant
 *    dentries by following the d_alias links.
 *
 * fh_to_parent:
 *    Same as @fh_to_dentry, except that it वापसs a poपूर्णांकer to the parent
 *    dentry अगर it was encoded पूर्णांकo the filehandle fragment by @encode_fh.
 *
 * get_name:
 *    @get_name should find a name क्रम the given @child in the given @parent
 *    directory.  The name should be stored in the @name (with the
 *    understanding that it is alपढ़ोy poपूर्णांकing to a %NAME_MAX+1 sized
 *    buffer.   get_name() should वापस %0 on success, a negative error code
 *    or error.  @get_name will be called without @parent->i_mutex held.
 *
 * get_parent:
 *    @get_parent should find the parent directory क्रम the given @child which
 *    is also a directory.  In the event that it cannot be found, or storage
 *    space cannot be allocated, a %ERR_PTR should be वापसed.
 *
 * commit_metadata:
 *    @commit_metadata should commit metadata changes to stable storage.
 *
 * Locking rules:
 *    get_parent is called with child->d_inode->i_mutex करोwn
 *    get_name is not (which is possibly inconsistent)
 */

काष्ठा export_operations अणु
	पूर्णांक (*encode_fh)(काष्ठा inode *inode, __u32 *fh, पूर्णांक *max_len,
			काष्ठा inode *parent);
	काष्ठा dentry * (*fh_to_dentry)(काष्ठा super_block *sb, काष्ठा fid *fid,
			पूर्णांक fh_len, पूर्णांक fh_type);
	काष्ठा dentry * (*fh_to_parent)(काष्ठा super_block *sb, काष्ठा fid *fid,
			पूर्णांक fh_len, पूर्णांक fh_type);
	पूर्णांक (*get_name)(काष्ठा dentry *parent, अक्षर *name,
			काष्ठा dentry *child);
	काष्ठा dentry * (*get_parent)(काष्ठा dentry *child);
	पूर्णांक (*commit_metadata)(काष्ठा inode *inode);

	पूर्णांक (*get_uuid)(काष्ठा super_block *sb, u8 *buf, u32 *len, u64 *offset);
	पूर्णांक (*map_blocks)(काष्ठा inode *inode, loff_t offset,
			  u64 len, काष्ठा iomap *iomap,
			  bool ग_लिखो, u32 *device_generation);
	पूर्णांक (*commit_blocks)(काष्ठा inode *inode, काष्ठा iomap *iomaps,
			     पूर्णांक nr_iomaps, काष्ठा iattr *iattr);
	u64 (*fetch_iversion)(काष्ठा inode *);
#घोषणा	EXPORT_OP_NOWCC			(0x1) /* करोn't collect v3 wcc data */
#घोषणा	EXPORT_OP_NOSUBTREECHK		(0x2) /* no subtree checking */
#घोषणा	EXPORT_OP_CLOSE_BEFORE_UNLINK	(0x4) /* बंद files beक्रमe unlink */
#घोषणा EXPORT_OP_REMOTE_FS		(0x8) /* Fileप्रणाली is remote */
#घोषणा EXPORT_OP_NOATOMIC_ATTR		(0x10) /* Fileप्रणाली cannot supply
						  atomic attribute updates
						*/
	अचिन्हित दीर्घ	flags;
पूर्ण;

बाह्य पूर्णांक exportfs_encode_inode_fh(काष्ठा inode *inode, काष्ठा fid *fid,
				    पूर्णांक *max_len, काष्ठा inode *parent);
बाह्य पूर्णांक exportfs_encode_fh(काष्ठा dentry *dentry, काष्ठा fid *fid,
	पूर्णांक *max_len, पूर्णांक connectable);
बाह्य काष्ठा dentry *exportfs_decode_fh_raw(काष्ठा vfsmount *mnt,
					     काष्ठा fid *fid, पूर्णांक fh_len,
					     पूर्णांक fileid_type,
					     पूर्णांक (*acceptable)(व्योम *, काष्ठा dentry *),
					     व्योम *context);
बाह्य काष्ठा dentry *exportfs_decode_fh(काष्ठा vfsmount *mnt, काष्ठा fid *fid,
	पूर्णांक fh_len, पूर्णांक fileid_type, पूर्णांक (*acceptable)(व्योम *, काष्ठा dentry *),
	व्योम *context);

/*
 * Generic helpers क्रम fileप्रणालीs.
 */
बाह्य काष्ठा dentry *generic_fh_to_dentry(काष्ठा super_block *sb,
	काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type,
	काष्ठा inode *(*get_inode) (काष्ठा super_block *sb, u64 ino, u32 gen));
बाह्य काष्ठा dentry *generic_fh_to_parent(काष्ठा super_block *sb,
	काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type,
	काष्ठा inode *(*get_inode) (काष्ठा super_block *sb, u64 ino, u32 gen));

#पूर्ण_अगर /* LINUX_EXPORTFS_H */
