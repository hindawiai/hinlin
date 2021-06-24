<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2015, Intel Corporation.
 */

#अगर_अघोषित __NVDIMM_PFN_H
#घोषणा __NVDIMM_PFN_H

#समावेश <linux/types.h>
#समावेश <linux/mmzone.h>

#घोषणा PFN_SIG_LEN 16
#घोषणा PFN_SIG "NVDIMM_PFN_INFO\0"
#घोषणा DAX_SIG "NVDIMM_DAX_INFO\0"

काष्ठा nd_pfn_sb अणु
	u8 signature[PFN_SIG_LEN];
	u8 uuid[16];
	u8 parent_uuid[16];
	__le32 flags;
	__le16 version_major;
	__le16 version_minor;
	__le64 dataoff; /* relative to namespace_base + start_pad */
	__le64 npfns;
	__le32 mode;
	/* minor-version-1 additions क्रम section alignment */
	/**
	 * @start_pad: Deprecated attribute to pad start-misaligned namespaces
	 *
	 * start_pad is deprecated because the original definition did
	 * not comprehend that dataoff is relative to the base address
	 * of the namespace not the start_pad adjusted base. The result
	 * is that the dax path is broken, but the block-I/O path is
	 * not. The kernel will no दीर्घer create namespaces using start
	 * padding, but it still supports block-I/O क्रम legacy
	 * configurations मुख्यly to allow a backup, reconfigure the
	 * namespace, and restore flow to repair dax operation.
	 */
	__le32 start_pad;
	__le32 end_trunc;
	/* minor-version-2 record the base alignment of the mapping */
	__le32 align;
	/* minor-version-3 guarantee the padding and flags are zero */
	/* minor-version-4 record the page size and काष्ठा page size */
	__le32 page_size;
	__le16 page_काष्ठा_size;
	u8 padding[3994];
	__le64 checksum;
पूर्ण;

#पूर्ण_अगर /* __NVDIMM_PFN_H */
