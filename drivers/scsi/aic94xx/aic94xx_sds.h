<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver hardware पूर्णांकerface header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Gilbert Wu <gilbert_wu@adaptec.com>
 */
#अगर_अघोषित _AIC94XX_SDS_H_
#घोषणा _AIC94XX_SDS_H_

क्रमागत अणु
	FLASH_METHOD_UNKNOWN,
	FLASH_METHOD_A,
	FLASH_METHOD_B
पूर्ण;

#घोषणा FLASH_MANUF_ID_AMD              0x01
#घोषणा FLASH_MANUF_ID_ST               0x20
#घोषणा FLASH_MANUF_ID_FUJITSU          0x04
#घोषणा FLASH_MANUF_ID_MACRONIX         0xC2
#घोषणा FLASH_MANUF_ID_INTEL            0x89
#घोषणा FLASH_MANUF_ID_UNKNOWN          0xFF

#घोषणा FLASH_DEV_ID_AM29LV008BT        0x3E
#घोषणा FLASH_DEV_ID_AM29LV800DT        0xDA
#घोषणा FLASH_DEV_ID_STM29W800DT        0xD7
#घोषणा FLASH_DEV_ID_STM29LV640         0xDE
#घोषणा FLASH_DEV_ID_STM29008           0xEA
#घोषणा FLASH_DEV_ID_MBM29LV800TE       0xDA
#घोषणा FLASH_DEV_ID_MBM29DL800TA       0x4A
#घोषणा FLASH_DEV_ID_MBM29LV008TA       0x3E
#घोषणा FLASH_DEV_ID_AM29LV640MT        0x7E
#घोषणा FLASH_DEV_ID_AM29F800B          0xD6
#घोषणा FLASH_DEV_ID_MX29LV800BT        0xDA
#घोषणा FLASH_DEV_ID_MX29LV008CT        0xDA
#घोषणा FLASH_DEV_ID_I28LV00TAT         0x3E
#घोषणा FLASH_DEV_ID_UNKNOWN            0xFF

/* status bit mask values */
#घोषणा FLASH_STATUS_BIT_MASK_DQ6       0x40
#घोषणा FLASH_STATUS_BIT_MASK_DQ5       0x20
#घोषणा FLASH_STATUS_BIT_MASK_DQ2       0x04

/* minimum value in micro seconds needed क्रम checking status */
#घोषणा FLASH_STATUS_ERASE_DELAY_COUNT  50
#घोषणा FLASH_STATUS_WRITE_DELAY_COUNT  25

#घोषणा FLASH_SECTOR_SIZE               0x010000
#घोषणा FLASH_SECTOR_SIZE_MASK          0xffff0000

#घोषणा FLASH_OK                        0x000000
#घोषणा FAIL_OPEN_BIOS_खाता             0x000100
#घोषणा FAIL_CHECK_PCI_ID               0x000200
#घोषणा FAIL_CHECK_SUM                  0x000300
#घोषणा FAIL_UNKNOWN                    0x000400
#घोषणा FAIL_VERIFY                     0x000500
#घोषणा FAIL_RESET_FLASH                0x000600
#घोषणा FAIL_FIND_FLASH_ID              0x000700
#घोषणा FAIL_ERASE_FLASH                0x000800
#घोषणा FAIL_WRITE_FLASH                0x000900
#घोषणा FAIL_खाता_SIZE                  0x000a00
#घोषणा FAIL_PARAMETERS                 0x000b00
#घोषणा FAIL_OUT_MEMORY                 0x000c00
#घोषणा FLASH_IN_PROGRESS               0x001000

काष्ठा controller_id अणु
	u32 venकरोr;     /* PCI Venकरोr ID */
	u32 device;     /* PCI Device ID */
	u32 sub_venकरोr; /* PCI Subvenकरोr ID */
	u32 sub_device; /* PCI Subdevice ID */
पूर्ण;

काष्ठा image_info अणु
	u32 ImageId;       /* Identअगरies the image */
	u32 ImageOffset;   /* Offset the beginning of the file */
	u32 ImageLength;   /* length of the image */
	u32 ImageChecksum; /* Image checksum */
	u32 ImageVersion;  /* Version of the image, could be build number */
पूर्ण;

काष्ठा bios_file_header अणु
	u8 signature[32]; /* Signature/Cookie to identअगरy the file */
	u32 checksum;	  /*Entire file checksum with this field zero */
	u32 antiकरोte;	  /* Entire file checksum with this field 0xFFFFFFFF */
	काष्ठा controller_id contrl_id; /*PCI id to identअगरy the controller */
	u32 filelen;      /*Length of the entire file*/
	u32 chunk_num;	  /*The chunk/part number क्रम multiple Image files */
	u32 total_chunks; /*Total number of chunks/parts in the image file */
	u32 num_images;   /* Number of images in the file */
	u32 build_num;    /* Build number of this image */
	काष्ठा image_info image_header;
पूर्ण;

पूर्णांक asd_verअगरy_flash_seg(काष्ठा asd_ha_काष्ठा *asd_ha,
		स्थिर व्योम *src, u32 dest_offset, u32 bytes_to_verअगरy);
पूर्णांक asd_ग_लिखो_flash_seg(काष्ठा asd_ha_काष्ठा *asd_ha,
		स्थिर व्योम *src, u32 dest_offset, u32 bytes_to_ग_लिखो);
पूर्णांक asd_chk_ग_लिखो_status(काष्ठा asd_ha_काष्ठा *asd_ha,
		u32 sector_addr, u8 erase_flag);
पूर्णांक asd_check_flash_type(काष्ठा asd_ha_काष्ठा *asd_ha);
पूर्णांक asd_erase_nv_sector(काष्ठा asd_ha_काष्ठा *asd_ha,
		u32 flash_addr, u32 size);
#पूर्ण_अगर
