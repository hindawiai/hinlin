<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel MAX 10 Board Management Controller chip.
 *
 * Copyright (C) 2018-2020 Intel Corporation, Inc.
 */
#अगर_अघोषित __MFD_INTEL_M10_BMC_H
#घोषणा __MFD_INTEL_M10_BMC_H

#समावेश <linux/regmap.h>

#घोषणा M10BMC_LEGACY_BUILD_VER		0x300468
#घोषणा M10BMC_SYS_BASE			0x300800
#घोषणा M10BMC_SYS_END			0x300fff
#घोषणा M10BMC_FLASH_BASE		0x10000000
#घोषणा M10BMC_FLASH_END		0x1fffffff
#घोषणा M10BMC_MEM_END			M10BMC_FLASH_END

#घोषणा M10BMC_STAGING_BASE		0x18000000
#घोषणा M10BMC_STAGING_SIZE		0x3800000

/* Register offset of प्रणाली रेजिस्टरs */
#घोषणा NIOS2_FW_VERSION		0x0
#घोषणा M10BMC_MAC_LOW			0x10
#घोषणा M10BMC_MAC_BYTE4		GENMASK(7, 0)
#घोषणा M10BMC_MAC_BYTE3		GENMASK(15, 8)
#घोषणा M10BMC_MAC_BYTE2		GENMASK(23, 16)
#घोषणा M10BMC_MAC_BYTE1		GENMASK(31, 24)
#घोषणा M10BMC_MAC_HIGH			0x14
#घोषणा M10BMC_MAC_BYTE6		GENMASK(7, 0)
#घोषणा M10BMC_MAC_BYTE5		GENMASK(15, 8)
#घोषणा M10BMC_MAC_COUNT		GENMASK(23, 16)
#घोषणा M10BMC_TEST_REG			0x3c
#घोषणा M10BMC_BUILD_VER		0x68
#घोषणा M10BMC_VER_MAJOR_MSK		GENMASK(23, 16)
#घोषणा M10BMC_VER_PCB_INFO_MSK		GENMASK(31, 24)
#घोषणा M10BMC_VER_LEGACY_INVALID	0xffffffff

/* Secure update करोorbell रेजिस्टर, in प्रणाली रेजिस्टर region */
#घोषणा M10BMC_DOORBELL			0x400

/* Authorization Result रेजिस्टर, in प्रणाली रेजिस्टर region */
#घोषणा M10BMC_AUTH_RESULT		0x404

/* Doorbell रेजिस्टर fields */
#घोषणा DRBL_RSU_REQUEST		BIT(0)
#घोषणा DRBL_RSU_PROGRESS		GENMASK(7, 4)
#घोषणा DRBL_HOST_STATUS		GENMASK(11, 8)
#घोषणा DRBL_RSU_STATUS			GENMASK(23, 16)
#घोषणा DRBL_PKVL_EEPROM_LOAD_SEC	BIT(24)
#घोषणा DRBL_PKVL1_POLL_EN		BIT(25)
#घोषणा DRBL_PKVL2_POLL_EN		BIT(26)
#घोषणा DRBL_CONFIG_SEL			BIT(28)
#घोषणा DRBL_REBOOT_REQ			BIT(29)
#घोषणा DRBL_REBOOT_DISABLED		BIT(30)

/* Progress states */
#घोषणा RSU_PROG_IDLE			0x0
#घोषणा RSU_PROG_PREPARE		0x1
#घोषणा RSU_PROG_READY			0x3
#घोषणा RSU_PROG_AUTHENTICATING		0x4
#घोषणा RSU_PROG_COPYING		0x5
#घोषणा RSU_PROG_UPDATE_CANCEL		0x6
#घोषणा RSU_PROG_PROGRAM_KEY_HASH	0x7
#घोषणा RSU_PROG_RSU_DONE		0x8
#घोषणा RSU_PROG_PKVL_PROM_DONE		0x9

/* Device and error states */
#घोषणा RSU_STAT_NORMAL			0x0
#घोषणा RSU_STAT_TIMEOUT		0x1
#घोषणा RSU_STAT_AUTH_FAIL		0x2
#घोषणा RSU_STAT_COPY_FAIL		0x3
#घोषणा RSU_STAT_FATAL			0x4
#घोषणा RSU_STAT_PKVL_REJECT		0x5
#घोषणा RSU_STAT_NON_INC		0x6
#घोषणा RSU_STAT_ERASE_FAIL		0x7
#घोषणा RSU_STAT_WEAROUT		0x8
#घोषणा RSU_STAT_NIOS_OK		0x80
#घोषणा RSU_STAT_USER_OK		0x81
#घोषणा RSU_STAT_FACTORY_OK		0x82
#घोषणा RSU_STAT_USER_FAIL		0x83
#घोषणा RSU_STAT_FACTORY_FAIL		0x84
#घोषणा RSU_STAT_NIOS_FLASH_ERR		0x85
#घोषणा RSU_STAT_FPGA_FLASH_ERR		0x86

#घोषणा HOST_STATUS_IDLE		0x0
#घोषणा HOST_STATUS_WRITE_DONE		0x1
#घोषणा HOST_STATUS_ABORT_RSU		0x2

#घोषणा rsu_prog(करोorbell)	FIELD_GET(DRBL_RSU_PROGRESS, करोorbell)
#घोषणा rsu_stat(करोorbell)	FIELD_GET(DRBL_RSU_STATUS, करोorbell)

/* पूर्णांकerval 100ms and समयout 5s */
#घोषणा NIOS_HANDSHAKE_INTERVAL_US	(100 * 1000)
#घोषणा NIOS_HANDSHAKE_TIMEOUT_US	(5 * 1000 * 1000)

/* RSU PREP Timeout (2 minutes) to erase flash staging area */
#घोषणा RSU_PREP_INTERVAL_MS		100
#घोषणा RSU_PREP_TIMEOUT_MS		(2 * 60 * 1000)

/* RSU Complete Timeout (40 minutes) क्रम full flash update */
#घोषणा RSU_COMPLETE_INTERVAL_MS	1000
#घोषणा RSU_COMPLETE_TIMEOUT_MS		(40 * 60 * 1000)

/* Addresses क्रम security related data in FLASH */
#घोषणा BMC_REH_ADDR	0x17ffc004
#घोषणा BMC_PROG_ADDR	0x17ffc000
#घोषणा BMC_PROG_MAGIC	0x5746

#घोषणा SR_REH_ADDR	0x17ffd004
#घोषणा SR_PROG_ADDR	0x17ffd000
#घोषणा SR_PROG_MAGIC	0x5253

#घोषणा PR_REH_ADDR	0x17ffe004
#घोषणा PR_PROG_ADDR	0x17ffe000
#घोषणा PR_PROG_MAGIC	0x5250

/* Address of 4KB inverted bit vector containing staging area FLASH count */
#घोषणा STAGING_FLASH_COUNT	0x17ffb000

/**
 * काष्ठा पूर्णांकel_m10bmc - Intel MAX 10 BMC parent driver data काष्ठाure
 * @dev: this device
 * @regmap: the regmap used to access रेजिस्टरs by m10bmc itself
 */
काष्ठा पूर्णांकel_m10bmc अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * रेजिस्टर access helper functions.
 *
 * m10bmc_raw_पढ़ो - पढ़ो m10bmc रेजिस्टर per addr
 * m10bmc_sys_पढ़ो - पढ़ो m10bmc प्रणाली रेजिस्टर per offset
 */
अटल अंतरभूत पूर्णांक
m10bmc_raw_पढ़ो(काष्ठा पूर्णांकel_m10bmc *m10bmc, अचिन्हित पूर्णांक addr,
		अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(m10bmc->regmap, addr, val);
	अगर (ret)
		dev_err(m10bmc->dev, "fail to read raw reg %x: %d\n",
			addr, ret);

	वापस ret;
पूर्ण

/*
 * The base of the प्रणाली रेजिस्टरs could be configured by HW developers, and
 * in HW SPEC, the base is not added to the addresses of the प्रणाली रेजिस्टरs.
 *
 * This macro helps to simplअगरy the accessing of the प्रणाली रेजिस्टरs. And अगर
 * the base is reconfigured in HW, SW developers could simply change the
 * M10BMC_SYS_BASE accordingly.
 */
#घोषणा m10bmc_sys_पढ़ो(m10bmc, offset, val) \
	m10bmc_raw_पढ़ो(m10bmc, M10BMC_SYS_BASE + (offset), val)

#पूर्ण_अगर /* __MFD_INTEL_M10_BMC_H */
