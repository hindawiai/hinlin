<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_UDF_SB_H
#घोषणा __LINUX_UDF_SB_H

#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश <linux/magic.h>

#घोषणा UDF_MAX_READ_VERSION		0x0250
#घोषणा UDF_MAX_WRITE_VERSION		0x0201

#घोषणा UDF_FLAG_USE_EXTENDED_FE	0
#घोषणा UDF_VERS_USE_EXTENDED_FE	0x0200
#घोषणा UDF_FLAG_USE_STREAMS		1
#घोषणा UDF_VERS_USE_STREAMS		0x0200
#घोषणा UDF_FLAG_USE_SHORT_AD		2
#घोषणा UDF_FLAG_USE_AD_IN_ICB		3
#घोषणा UDF_FLAG_USE_खाता_CTIME_EA	4
#घोषणा UDF_FLAG_STRICT			5
#घोषणा UDF_FLAG_UNDELETE		6
#घोषणा UDF_FLAG_UNHIDE			7
#घोषणा UDF_FLAG_VARCONV		8
#घोषणा UDF_FLAG_NLS_MAP		9
#घोषणा UDF_FLAG_UTF8			10
#घोषणा UDF_FLAG_UID_FORGET     11    /* save -1 क्रम uid to disk */
#घोषणा UDF_FLAG_GID_FORGET     12
#घोषणा UDF_FLAG_UID_SET	13
#घोषणा UDF_FLAG_GID_SET	14
#घोषणा UDF_FLAG_SESSION_SET	15
#घोषणा UDF_FLAG_LASTBLOCK_SET	16
#घोषणा UDF_FLAG_BLOCKSIZE_SET	17
#घोषणा UDF_FLAG_INCONSISTENT	18
#घोषणा UDF_FLAG_RW_INCOMPAT	19	/* Set when we find RW incompatible
					 * feature */

#घोषणा UDF_PART_FLAG_UNALLOC_BITMAP	0x0001
#घोषणा UDF_PART_FLAG_UNALLOC_TABLE	0x0002
#घोषणा UDF_PART_FLAG_READ_ONLY		0x0010
#घोषणा UDF_PART_FLAG_WRITE_ONCE	0x0020
#घोषणा UDF_PART_FLAG_REWRITABLE	0x0040
#घोषणा UDF_PART_FLAG_OVERWRITABLE	0x0080

#घोषणा UDF_MAX_BLOCK_LOADED	8

#घोषणा UDF_TYPE1_MAP15			0x1511U
#घोषणा UDF_VIRTUAL_MAP15		0x1512U
#घोषणा UDF_VIRTUAL_MAP20		0x2012U
#घोषणा UDF_SPARABLE_MAP15		0x1522U
#घोषणा UDF_METADATA_MAP25		0x2511U

#घोषणा UDF_INVALID_MODE		((umode_t)-1)

#घोषणा MF_DUPLICATE_MD		0x01
#घोषणा MF_MIRROR_FE_LOADED	0x02

काष्ठा udf_meta_data अणु
	__u32	s_meta_file_loc;
	__u32	s_mirror_file_loc;
	__u32	s_biपंचांगap_file_loc;
	__u32	s_alloc_unit_size;
	__u16	s_align_unit_size;
	/*
	 * Partition Reference Number of the associated physical / sparable
	 * partition
	 */
	__u16   s_phys_partition_ref;
	पूर्णांक	s_flags;
	काष्ठा inode *s_metadata_fe;
	काष्ठा inode *s_mirror_fe;
	काष्ठा inode *s_biपंचांगap_fe;
पूर्ण;

काष्ठा udf_sparing_data अणु
	__u16	s_packet_len;
	काष्ठा buffer_head *s_spar_map[4];
पूर्ण;

काष्ठा udf_भव_data अणु
	__u32	s_num_entries;
	__u16	s_start_offset;
पूर्ण;

काष्ठा udf_biपंचांगap अणु
	__u32			s_extPosition;
	पूर्णांक			s_nr_groups;
	काष्ठा buffer_head	*s_block_biपंचांगap[];
पूर्ण;

काष्ठा udf_part_map अणु
	जोड़ अणु
		काष्ठा udf_biपंचांगap	*s_biपंचांगap;
		काष्ठा inode		*s_table;
	पूर्ण s_uspace;
	__u32	s_partition_root;
	__u32	s_partition_len;
	__u16	s_partition_type;
	__u16	s_partition_num;
	जोड़ अणु
		काष्ठा udf_sparing_data s_sparing;
		काष्ठा udf_भव_data s_भव;
		काष्ठा udf_meta_data s_metadata;
	पूर्ण s_type_specअगरic;
	__u32	(*s_partition_func)(काष्ठा super_block *, __u32, __u16, __u32);
	__u16	s_volumeseqnum;
	__u16	s_partition_flags;
पूर्ण;

#आशय pack()

काष्ठा udf_sb_info अणु
	काष्ठा udf_part_map	*s_parपंचांगaps;
	__u8			s_volume_ident[32];

	/* Overall info */
	__u16			s_partitions;
	__u16			s_partition;

	/* Sector headers */
	__s32			s_session;
	__u32			s_anchor;
	__u32			s_last_block;

	काष्ठा buffer_head	*s_lvid_bh;

	/* Default permissions */
	umode_t			s_umask;
	kgid_t			s_gid;
	kuid_t			s_uid;
	umode_t			s_भ_शेषe;
	umode_t			s_dmode;
	/* Lock protecting consistency of above permission settings */
	rwlock_t		s_cred_lock;

	/* Root Info */
	काष्ठा बारpec64	s_record_समय;

	/* Fileset Info */
	__u16			s_serial_number;

	/* highest UDF revision we have recorded to this media */
	__u16			s_udfrev;

	/* Miscellaneous flags */
	अचिन्हित दीर्घ		s_flags;

	/* Encoding info */
	काष्ठा nls_table	*s_nls_map;

	/* VAT inode */
	काष्ठा inode		*s_vat_inode;

	काष्ठा mutex		s_alloc_mutex;
	/* Protected by s_alloc_mutex */
	अचिन्हित पूर्णांक		s_lvid_dirty;
पूर्ण;

अटल अंतरभूत काष्ठा udf_sb_info *UDF_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

काष्ठा logicalVolIntegrityDescImpUse *udf_sb_lvidiu(काष्ठा super_block *sb);

पूर्णांक udf_compute_nr_groups(काष्ठा super_block *sb, u32 partition);

अटल अंतरभूत पूर्णांक UDF_QUERY_FLAG(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	वापस test_bit(flag, &UDF_SB(sb)->s_flags);
पूर्ण

अटल अंतरभूत व्योम UDF_SET_FLAG(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	set_bit(flag, &UDF_SB(sb)->s_flags);
पूर्ण

अटल अंतरभूत व्योम UDF_CLEAR_FLAG(काष्ठा super_block *sb, पूर्णांक flag)
अणु
	clear_bit(flag, &UDF_SB(sb)->s_flags);
पूर्ण

#पूर्ण_अगर /* __LINUX_UDF_SB_H */
