<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (c) 2015 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

/* This file contains the definitions क्रम the boot loader
 * क्रम the Qualcomm "Sparrow" 60 Gigabit wireless solution.
 */
#अगर_अघोषित BOOT_LOADER_EXPORT_H_
#घोषणा BOOT_LOADER_EXPORT_H_

काष्ठा bl_dedicated_रेजिस्टरs_v1 अणु
	__le32	boot_loader_पढ़ोy;		/* 0x880A3C driver will poll
						 * this Dword until BL will
						 * set it to 1 (initial value
						 * should be 0)
						 */
	__le32	boot_loader_काष्ठा_version;	/* 0x880A40 BL काष्ठा ver. */
	__le16	rf_type;			/* 0x880A44 connected RF ID */
	__le16	rf_status;			/* 0x880A46 RF status,
						 * 0 is OK अन्यथा error
						 */
	__le32	baseband_type;			/* 0x880A48 board type ID */
	u8	mac_address[6];			/* 0x880A4c BL mac address */
	u8	bl_version_major;		/* 0x880A52 BL ver. major */
	u8	bl_version_minor;		/* 0x880A53 BL ver. minor */
	__le16	bl_version_subminor;		/* 0x880A54 BL ver. subminor */
	__le16	bl_version_build;		/* 0x880A56 BL ver. build */
	/* valid only क्रम version 2 and above */
	__le32  bl_निश्चित_code;         /* 0x880A58 BL Assert code */
	__le32  bl_निश्चित_blink;        /* 0x880A5C BL Assert Branch */
	__le32  bl_shutकरोwn_handshake;  /* 0x880A60 BL cleaner shutकरोwn */
	__le32  bl_reserved[21];        /* 0x880A64 - 0x880AB4 */
	__le32  bl_magic_number;        /* 0x880AB8 BL Magic number */
पूर्ण __packed;

/* the following काष्ठा is the version 0 काष्ठा */

काष्ठा bl_dedicated_रेजिस्टरs_v0 अणु
	__le32	boot_loader_पढ़ोy;		/* 0x880A3C driver will poll
						 * this Dword until BL will
						 * set it to 1 (initial value
						 * should be 0)
						 */
#घोषणा BL_READY (1)	/* पढ़ोy indication */
	__le32	boot_loader_काष्ठा_version;	/* 0x880A40 BL काष्ठा ver. */
	__le32	rf_type;			/* 0x880A44 connected RF ID */
	__le32	baseband_type;			/* 0x880A48 board type ID */
	u8	mac_address[6];			/* 0x880A4c BL mac address */
पूर्ण __packed;

/* bits क्रम bl_shutकरोwn_handshake */
#घोषणा BL_SHUTDOWN_HS_GRTD		BIT(0)
#घोषणा BL_SHUTDOWN_HS_RTD		BIT(1)
#घोषणा BL_SHUTDOWN_HS_PROT_VER(x) WIL_GET_BITS(x, 28, 31)

#पूर्ण_अगर /* BOOT_LOADER_EXPORT_H_ */
