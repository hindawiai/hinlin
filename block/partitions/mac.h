<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  fs/partitions/mac.h
 */

#घोषणा MAC_PARTITION_MAGIC	0x504d

/* type field value क्रम A/UX or other Unix partitions */
#घोषणा APPLE_AUX_TYPE	"Apple_UNIX_SVR2"

काष्ठा mac_partition अणु
	__be16	signature;	/* expected to be MAC_PARTITION_MAGIC */
	__be16	res1;
	__be32	map_count;	/* # blocks in partition map */
	__be32	start_block;	/* असलolute starting block # of partition */
	__be32	block_count;	/* number of blocks in partition */
	अक्षर	name[32];	/* partition name */
	अक्षर	type[32];	/* string type description */
	__be32	data_start;	/* rel block # of first data block */
	__be32	data_count;	/* number of data blocks */
	__be32	status;		/* partition status bits */
	__be32	boot_start;
	__be32	boot_size;
	__be32	boot_load;
	__be32	boot_load2;
	__be32	boot_entry;
	__be32	boot_entry2;
	__be32	boot_cksum;
	अक्षर	processor[16];	/* identअगरies ISA of boot */
	/* there is more stuff after this that we करोn't need */
पूर्ण;

#घोषणा MAC_STATUS_BOOTABLE	8	/* partition is bootable */

#घोषणा MAC_DRIVER_MAGIC	0x4552

/* Driver descriptor काष्ठाure, in block 0 */
काष्ठा mac_driver_desc अणु
	__be16	signature;	/* expected to be MAC_DRIVER_MAGIC */
	__be16	block_size;
	__be32	block_count;
    /* ... more stuff */
पूर्ण;

