<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * VFIO Region definitions क्रम ZPCI devices
 *
 * Copyright IBM Corp. 2020
 *
 * Author(s): Pierre Morel <pmorel@linux.ibm.com>
 *            Matthew Rosato <mjrosato@linux.ibm.com>
 */

#अगर_अघोषित _VFIO_ZDEV_H_
#घोषणा _VFIO_ZDEV_H_

#समावेश <linux/types.h>
#समावेश <linux/vfपन.स>

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_BASE - Base PCI Function inक्रमmation
 *
 * This capability provides a set of descriptive inक्रमmation about the
 * associated PCI function.
 */
काष्ठा vfio_device_info_cap_zpci_base अणु
	काष्ठा vfio_info_cap_header header;
	__u64 start_dma;	/* Start of available DMA addresses */
	__u64 end_dma;		/* End of available DMA addresses */
	__u16 pchid;		/* Physical Channel ID */
	__u16 vfn;		/* Virtual function number */
	__u16 fmb_length;	/* Measurement Block Length (in bytes) */
	__u8 pft;		/* PCI Function Type */
	__u8 gid;		/* PCI function group ID */
पूर्ण;

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_GROUP - Base PCI Function Group inक्रमmation
 *
 * This capability provides a set of descriptive inक्रमmation about the group of
 * PCI functions that the associated device beदीर्घs to.
 */
काष्ठा vfio_device_info_cap_zpci_group अणु
	काष्ठा vfio_info_cap_header header;
	__u64 dयंत्र;		/* DMA Address space mask */
	__u64 msi_addr;		/* MSI address */
	__u64 flags;
#घोषणा VFIO_DEVICE_INFO_ZPCI_FLAG_REFRESH 1 /* Program-specअगरied TLB refresh */
	__u16 mui;		/* Measurement Block Update Interval */
	__u16 noi;		/* Maximum number of MSIs */
	__u16 maxstbl;		/* Maximum Store Block Length */
	__u8 version;		/* Supported PCI Version */
पूर्ण;

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_UTIL - Utility String
 *
 * This capability provides the utility string क्रम the associated device, which
 * is a device identअगरier string made up of EBCDID अक्षरacters.  'size' specअगरies
 * the length of 'util_str'.
 */
काष्ठा vfio_device_info_cap_zpci_util अणु
	काष्ठा vfio_info_cap_header header;
	__u32 size;
	__u8 util_str[];
पूर्ण;

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_PFIP - PCI Function Path
 *
 * This capability provides the PCI function path string, which is an identअगरier
 * that describes the पूर्णांकernal hardware path of the device. 'size' specअगरies
 * the length of 'pfip'.
 */
काष्ठा vfio_device_info_cap_zpci_pfip अणु
	काष्ठा vfio_info_cap_header header;
	__u32 size;
	__u8 pfip[];
पूर्ण;

#पूर्ण_अगर
