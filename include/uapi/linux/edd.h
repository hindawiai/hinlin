<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * linux/include/linux/edd.h
 *  Copyright (C) 2002, 2003, 2004 Dell Inc.
 *  by Matt Domsch <Matt_Domsch@dell.com>
 *
 * काष्ठाures and definitions क्रम the पूर्णांक 13h, ax=अणु41,48पूर्णh
 * BIOS Enhanced Disk Drive Services
 * This is based on the T13 group करोcument D1572 Revision 0 (August 14 2002)
 * available at http://www.t13.org/करोcs2002/d1572r0.pdf.  It is
 * very similar to D1484 Revision 3 http://www.t13.org/करोcs2002/d1484r3.pdf
 *
 * In a nutshell, arch/अणुi386,x86_64पूर्ण/boot/setup.S populates a scratch
 * table in the boot_params that contains a list of BIOS-क्रमागतerated
 * boot devices.
 * In arch/अणुi386,x86_64पूर्ण/kernel/setup.c, this inक्रमmation is
 * transferred पूर्णांकo the edd काष्ठाure, and in drivers/firmware/edd.c, that
 * inक्रमmation is used to identअगरy BIOS boot disk.  The code in setup.S
 * is very sensitive to the size of these काष्ठाures.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License v2.0 as published by
 * the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */
#अगर_अघोषित _UAPI_LINUX_EDD_H
#घोषणा _UAPI_LINUX_EDD_H

#समावेश <linux/types.h>

#घोषणा EDDNR 0x1e9		/* addr of number of edd_info काष्ठाs at EDDBUF
				   in boot_params - treat this as 1 byte  */
#घोषणा EDDBUF	0xd00		/* addr of edd_info काष्ठाs in boot_params */
#घोषणा EDDMAXNR 6		/* number of edd_info काष्ठाs starting at EDDBUF  */
#घोषणा EDDEXTSIZE 8		/* change these अगर you muck with the काष्ठाures */
#घोषणा EDDPARMSIZE 74
#घोषणा CHECKEXTENSIONSPRESENT 0x41
#घोषणा GETDEVICEPARAMETERS 0x48
#घोषणा LEGACYGETDEVICEPARAMETERS 0x08
#घोषणा EDDMAGIC1 0x55AA
#घोषणा EDDMAGIC2 0xAA55


#घोषणा READ_SECTORS 0x02         /* पूर्णांक13 AH=0x02 is READ_SECTORS command */
#घोषणा EDD_MBR_SIG_OFFSET 0x1B8  /* offset of signature in the MBR */
#घोषणा EDD_MBR_SIG_BUF    0x290  /* addr in boot params */
#घोषणा EDD_MBR_SIG_MAX 16        /* max number of signatures to store */
#घोषणा EDD_MBR_SIG_NR_BUF 0x1ea  /* addr of number of MBR signtaures at EDD_MBR_SIG_BUF
				     in boot_params - treat this as 1 byte  */

#अगर_अघोषित __ASSEMBLY__

#घोषणा EDD_EXT_FIXED_DISK_ACCESS           (1 << 0)
#घोषणा EDD_EXT_DEVICE_LOCKING_AND_EJECTING (1 << 1)
#घोषणा EDD_EXT_ENHANCED_DISK_DRIVE_SUPPORT (1 << 2)
#घोषणा EDD_EXT_64BIT_EXTENSIONS            (1 << 3)

#घोषणा EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT (1 << 0)
#घोषणा EDD_INFO_GEOMETRY_VALID                (1 << 1)
#घोषणा EDD_INFO_REMOVABLE                     (1 << 2)
#घोषणा EDD_INFO_WRITE_VERIFY                  (1 << 3)
#घोषणा EDD_INFO_MEDIA_CHANGE_NOTIFICATION     (1 << 4)
#घोषणा EDD_INFO_LOCKABLE                      (1 << 5)
#घोषणा EDD_INFO_NO_MEDIA_PRESENT              (1 << 6)
#घोषणा EDD_INFO_USE_INT13_FN50                (1 << 7)

काष्ठा edd_device_params अणु
	__u16 length;
	__u16 info_flags;
	__u32 num_शेष_cylinders;
	__u32 num_शेष_heads;
	__u32 sectors_per_track;
	__u64 number_of_sectors;
	__u16 bytes_per_sector;
	__u32 dpte_ptr;		/* 0xFFFFFFFF क्रम our purposes */
	__u16 key;		/* = 0xBEDD */
	__u8 device_path_info_length;	/* = 44 */
	__u8 reserved2;
	__u16 reserved3;
	__u8 host_bus_type[4];
	__u8 पूर्णांकerface_type[8];
	जोड़ अणु
		काष्ठा अणु
			__u16 base_address;
			__u16 reserved1;
			__u32 reserved2;
		पूर्ण __attribute__ ((packed)) isa;
		काष्ठा अणु
			__u8 bus;
			__u8 slot;
			__u8 function;
			__u8 channel;
			__u32 reserved;
		पूर्ण __attribute__ ((packed)) pci;
		/* pcix is same as pci */
		काष्ठा अणु
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) ibnd;
		काष्ठा अणु
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) xprs;
		काष्ठा अणु
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) htpt;
		काष्ठा अणु
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) unknown;
	पूर्ण पूर्णांकerface_path;
	जोड़ अणु
		काष्ठा अणु
			__u8 device;
			__u8 reserved1;
			__u16 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		पूर्ण __attribute__ ((packed)) ata;
		काष्ठा अणु
			__u8 device;
			__u8 lun;
			__u8 reserved1;
			__u8 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		पूर्ण __attribute__ ((packed)) atapi;
		काष्ठा अणु
			__u16 id;
			__u64 lun;
			__u16 reserved1;
			__u32 reserved2;
		पूर्ण __attribute__ ((packed)) scsi;
		काष्ठा अणु
			__u64 serial_number;
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) usb;
		काष्ठा अणु
			__u64 eui;
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) i1394;
		काष्ठा अणु
			__u64 wwid;
			__u64 lun;
		पूर्ण __attribute__ ((packed)) fibre;
		काष्ठा अणु
			__u64 identity_tag;
			__u64 reserved;
		पूर्ण __attribute__ ((packed)) i2o;
		काष्ठा अणु
			__u32 array_number;
			__u32 reserved1;
			__u64 reserved2;
		पूर्ण __attribute__ ((packed)) raid;
		काष्ठा अणु
			__u8 device;
			__u8 reserved1;
			__u16 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		पूर्ण __attribute__ ((packed)) sata;
		काष्ठा अणु
			__u64 reserved1;
			__u64 reserved2;
		पूर्ण __attribute__ ((packed)) unknown;
	पूर्ण device_path;
	__u8 reserved4;
	__u8 checksum;
पूर्ण __attribute__ ((packed));

काष्ठा edd_info अणु
	__u8 device;
	__u8 version;
	__u16 पूर्णांकerface_support;
	__u16 legacy_max_cylinder;
	__u8 legacy_max_head;
	__u8 legacy_sectors_per_track;
	काष्ठा edd_device_params params;
पूर्ण __attribute__ ((packed));

काष्ठा edd अणु
	अचिन्हित पूर्णांक mbr_signature[EDD_MBR_SIG_MAX];
	काष्ठा edd_info edd_info[EDDMAXNR];
	अचिन्हित अक्षर mbr_signature_nr;
	अचिन्हित अक्षर edd_info_nr;
पूर्ण;

#पूर्ण_अगर				/*!__ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_LINUX_EDD_H */
