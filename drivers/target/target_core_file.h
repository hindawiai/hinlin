<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_खाता_H
#घोषणा TARGET_CORE_खाता_H

#समावेश <target/target_core_base.h>

#घोषणा FD_VERSION		"4.0"

#घोषणा FD_MAX_DEV_NAME		256
#घोषणा FD_MAX_DEV_PROT_NAME	FD_MAX_DEV_NAME + 16
#घोषणा FD_DEVICE_QUEUE_DEPTH	32
#घोषणा FD_MAX_DEVICE_QUEUE_DEPTH 128
#घोषणा FD_BLOCKSIZE		512
/*
 * Limited by the number of iovecs (2048) per vfs_[ग_लिखोv,पढ़ोv] call
 */
#घोषणा FD_MAX_BYTES		8388608

#घोषणा RRF_EMULATE_CDB		0x01
#घोषणा RRF_GOT_LBA		0x02

#घोषणा FBDF_HAS_PATH		0x01
#घोषणा FBDF_HAS_SIZE		0x02
#घोषणा FDBD_HAS_BUFFERED_IO_WCE 0x04
#घोषणा FDBD_HAS_ASYNC_IO	 0x08
#घोषणा FDBD_FORMAT_UNIT_SIZE	2048

काष्ठा fd_dev अणु
	काष्ठा se_device dev;

	u32		fbd_flags;
	अचिन्हित अक्षर	fd_dev_name[FD_MAX_DEV_NAME];
	/* Unique Ramdisk Device ID in Ramdisk HBA */
	u32		fd_dev_id;
	/* Number of SG tables in sg_table_array */
	u32		fd_table_count;
	u32		fd_queue_depth;
	u32		fd_block_size;
	अचिन्हित दीर्घ दीर्घ fd_dev_size;
	काष्ठा file	*fd_file;
	काष्ठा file	*fd_prot_file;
	/* खाताIO HBA device is connected to */
	काष्ठा fd_host *fd_host;
पूर्ण ____cacheline_aligned;

काष्ठा fd_host अणु
	u32		fd_host_dev_id_count;
	/* Unique खाताIO Host ID */
	u32		fd_host_id;
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर /* TARGET_CORE_खाता_H */
