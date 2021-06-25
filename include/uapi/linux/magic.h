<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_MAGIC_H__
#घोषणा __LINUX_MAGIC_H__

#घोषणा ADFS_SUPER_MAGIC	0xadf5
#घोषणा AFFS_SUPER_MAGIC	0xadff
#घोषणा AFS_SUPER_MAGIC                0x5346414F
#घोषणा AUTOFS_SUPER_MAGIC	0x0187
#घोषणा CODA_SUPER_MAGIC	0x73757245
#घोषणा CRAMFS_MAGIC		0x28cd3d45	/* some अक्रमom number */
#घोषणा CRAMFS_MAGIC_WEND	0x453dcd28	/* magic number with the wrong endianess */
#घोषणा DEBUGFS_MAGIC          0x64626720
#घोषणा SECURITYFS_MAGIC	0x73636673
#घोषणा SELINUX_MAGIC		0xf97cff8c
#घोषणा SMACK_MAGIC		0x43415d53	/* "SMAC" */
#घोषणा RAMFS_MAGIC		0x858458f6	/* some अक्रमom number */
#घोषणा TMPFS_MAGIC		0x01021994
#घोषणा HUGETLBFS_MAGIC 	0x958458f6	/* some अक्रमom number */
#घोषणा SQUASHFS_MAGIC		0x73717368
#घोषणा ECRYPTFS_SUPER_MAGIC	0xf15f
#घोषणा EFS_SUPER_MAGIC		0x414A53
#घोषणा EROFS_SUPER_MAGIC_V1	0xE0F5E1E2
#घोषणा EXT2_SUPER_MAGIC	0xEF53
#घोषणा EXT3_SUPER_MAGIC	0xEF53
#घोषणा XENFS_SUPER_MAGIC	0xabba1974
#घोषणा EXT4_SUPER_MAGIC	0xEF53
#घोषणा BTRFS_SUPER_MAGIC	0x9123683E
#घोषणा NILFS_SUPER_MAGIC	0x3434
#घोषणा F2FS_SUPER_MAGIC	0xF2F52010
#घोषणा HPFS_SUPER_MAGIC	0xf995e849
#घोषणा ISOFS_SUPER_MAGIC	0x9660
#घोषणा JFFS2_SUPER_MAGIC	0x72b6
#घोषणा XFS_SUPER_MAGIC		0x58465342	/* "XFSB" */
#घोषणा PSTOREFS_MAGIC		0x6165676C
#घोषणा EFIVARFS_MAGIC		0xde5e81e4
#घोषणा HOSTFS_SUPER_MAGIC	0x00c0ffee
#घोषणा OVERLAYFS_SUPER_MAGIC	0x794c7630

#घोषणा MINIX_SUPER_MAGIC	0x137F		/* minix v1 fs, 14 अक्षर names */
#घोषणा MINIX_SUPER_MAGIC2	0x138F		/* minix v1 fs, 30 अक्षर names */
#घोषणा MINIX2_SUPER_MAGIC	0x2468		/* minix v2 fs, 14 अक्षर names */
#घोषणा MINIX2_SUPER_MAGIC2	0x2478		/* minix v2 fs, 30 अक्षर names */
#घोषणा MINIX3_SUPER_MAGIC	0x4d5a		/* minix v3 fs, 60 अक्षर names */

#घोषणा MSDOS_SUPER_MAGIC	0x4d44		/* MD */
#घोषणा NCP_SUPER_MAGIC		0x564c		/* Guess, what 0x564c is :-) */
#घोषणा NFS_SUPER_MAGIC		0x6969
#घोषणा OCFS2_SUPER_MAGIC	0x7461636f
#घोषणा OPENPROM_SUPER_MAGIC	0x9fa1
#घोषणा QNX4_SUPER_MAGIC	0x002f		/* qnx4 fs detection */
#घोषणा QNX6_SUPER_MAGIC	0x68191122	/* qnx6 fs detection */
#घोषणा AFS_FS_MAGIC		0x6B414653

#घोषणा REISERFS_SUPER_MAGIC	0x52654973	/* used by gcc */
					/* used by file प्रणाली utilities that
	                                   look at the superblock, etc.  */
#घोषणा REISERFS_SUPER_MAGIC_STRING	"ReIsErFs"
#घोषणा REISER2FS_SUPER_MAGIC_STRING	"ReIsEr2Fs"
#घोषणा REISER2FS_JR_SUPER_MAGIC_STRING	"ReIsEr3Fs"

#घोषणा SMB_SUPER_MAGIC		0x517B
#घोषणा CGROUP_SUPER_MAGIC	0x27e0eb
#घोषणा CGROUP2_SUPER_MAGIC	0x63677270

#घोषणा RDTGROUP_SUPER_MAGIC	0x7655821

#घोषणा STACK_END_MAGIC		0x57AC6E9D

#घोषणा TRACEFS_MAGIC          0x74726163

#घोषणा V9FS_MAGIC		0x01021997

#घोषणा BDEVFS_MAGIC            0x62646576
#घोषणा DAXFS_MAGIC             0x64646178
#घोषणा BINFMTFS_MAGIC          0x42494e4d
#घोषणा DEVPTS_SUPER_MAGIC	0x1cd1
#घोषणा BINDERFS_SUPER_MAGIC	0x6c6f6f70
#घोषणा FUTEXFS_SUPER_MAGIC	0xBAD1DEA
#घोषणा PIPEFS_MAGIC            0x50495045
#घोषणा PROC_SUPER_MAGIC	0x9fa0
#घोषणा SOCKFS_MAGIC		0x534F434B
#घोषणा SYSFS_MAGIC		0x62656572
#घोषणा USBDEVICE_SUPER_MAGIC	0x9fa2
#घोषणा MTD_INODE_FS_MAGIC      0x11307854
#घोषणा ANON_INODE_FS_MAGIC	0x09041934
#घोषणा BTRFS_TEST_MAGIC	0x73727279
#घोषणा NSFS_MAGIC		0x6e736673
#घोषणा BPF_FS_MAGIC		0xcafe4a11
#घोषणा AAFS_MAGIC		0x5a3c69f0
#घोषणा ZONEFS_MAGIC		0x5a4f4653

/* Since UDF 2.01 is ISO 13346 based... */
#घोषणा UDF_SUPER_MAGIC		0x15013346
#घोषणा BALLOON_KVM_MAGIC	0x13661366
#घोषणा ZSMALLOC_MAGIC		0x58295829
#घोषणा DMA_BUF_MAGIC		0x444d4142	/* "DMAB" */
#घोषणा DEVMEM_MAGIC		0x454d444d	/* "DMEM" */
#घोषणा Z3FOLD_MAGIC		0x33
#घोषणा PPC_CMM_MAGIC		0xc7571590

#पूर्ण_अगर /* __LINUX_MAGIC_H__ */
