<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित _BNXT_NVM_DEFS_H_
#घोषणा _BNXT_NVM_DEFS_H_

क्रमागत bnxt_nvm_directory_type अणु
	BNX_सूची_TYPE_UNUSED = 0,
	BNX_सूची_TYPE_PKG_LOG = 1,
	BNX_सूची_TYPE_UPDATE = 2,
	BNX_सूची_TYPE_CHIMP_PATCH = 3,
	BNX_सूची_TYPE_BOOTCODE = 4,
	BNX_सूची_TYPE_VPD = 5,
	BNX_सूची_TYPE_EXP_ROM_MBA = 6,
	BNX_सूची_TYPE_AVS = 7,
	BNX_सूची_TYPE_PCIE = 8,
	BNX_सूची_TYPE_PORT_MACRO = 9,
	BNX_सूची_TYPE_APE_FW = 10,
	BNX_सूची_TYPE_APE_PATCH = 11,
	BNX_सूची_TYPE_KONG_FW = 12,
	BNX_सूची_TYPE_KONG_PATCH = 13,
	BNX_सूची_TYPE_BONO_FW = 14,
	BNX_सूची_TYPE_BONO_PATCH = 15,
	BNX_सूची_TYPE_TANG_FW = 16,
	BNX_सूची_TYPE_TANG_PATCH = 17,
	BNX_सूची_TYPE_BOOTCODE_2 = 18,
	BNX_सूची_TYPE_CCM = 19,
	BNX_सूची_TYPE_PCI_CFG = 20,
	BNX_सूची_TYPE_TSCF_UCODE = 21,
	BNX_सूची_TYPE_ISCSI_BOOT = 22,
	BNX_सूची_TYPE_ISCSI_BOOT_IPV6 = 24,
	BNX_सूची_TYPE_ISCSI_BOOT_IPV4N6 = 25,
	BNX_सूची_TYPE_ISCSI_BOOT_CFG6 = 26,
	BNX_सूची_TYPE_EXT_PHY = 27,
	BNX_सूची_TYPE_SHARED_CFG = 40,
	BNX_सूची_TYPE_PORT_CFG = 41,
	BNX_सूची_TYPE_FUNC_CFG = 42,
	BNX_सूची_TYPE_MGMT_CFG = 48,
	BNX_सूची_TYPE_MGMT_DATA = 49,
	BNX_सूची_TYPE_MGMT_WEB_DATA = 50,
	BNX_सूची_TYPE_MGMT_WEB_META = 51,
	BNX_सूची_TYPE_MGMT_EVENT_LOG = 52,
	BNX_सूची_TYPE_MGMT_AUDIT_LOG = 53
पूर्ण;

#घोषणा BNX_सूची_ORDINAL_FIRST			0

#घोषणा BNX_सूची_EXT_NONE			0
#घोषणा BNX_सूची_EXT_INACTIVE			(1 << 0)
#घोषणा BNX_सूची_EXT_UPDATE			(1 << 1)

#घोषणा BNX_सूची_ATTR_NONE			0
#घोषणा BNX_सूची_ATTR_NO_CHKSUM			(1 << 0)
#घोषणा BNX_सूची_ATTR_PROP_STREAM		(1 << 1)

क्रमागत bnxnvm_pkglog_field_index अणु
	BNX_PKG_LOG_FIELD_IDX_INSTALLED_TIMESTAMP	= 0,
	BNX_PKG_LOG_FIELD_IDX_PKG_DESCRIPTION		= 1,
	BNX_PKG_LOG_FIELD_IDX_PKG_VERSION		= 2,
	BNX_PKG_LOG_FIELD_IDX_PKG_TIMESTAMP		= 3,
	BNX_PKG_LOG_FIELD_IDX_PKG_CHECKSUM		= 4,
	BNX_PKG_LOG_FIELD_IDX_INSTALLED_ITEMS		= 5,
	BNX_PKG_LOG_FIELD_IDX_INSTALLED_MASK		= 6
पूर्ण;

#पूर्ण_अगर				/* Don't add anything after this line */
