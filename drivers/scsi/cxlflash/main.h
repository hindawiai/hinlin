<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#अगर_अघोषित _CXLFLASH_MAIN_H
#घोषणा _CXLFLASH_MAIN_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>

#समावेश "backend.h"

#घोषणा CXLFLASH_NAME		"cxlflash"
#घोषणा CXLFLASH_ADAPTER_NAME	"IBM POWER CXL Flash Adapter"
#घोषणा CXLFLASH_MAX_ADAPTERS	32

#घोषणा PCI_DEVICE_ID_IBM_CORSA		0x04F0
#घोषणा PCI_DEVICE_ID_IBM_FLASH_GT	0x0600
#घोषणा PCI_DEVICE_ID_IBM_BRIARD	0x0624

/* Since there is only one target, make it 0 */
#घोषणा CXLFLASH_TARGET		0
#घोषणा CXLFLASH_MAX_CDB_LEN	16

/* Really only one target per bus since the Texan is directly attached */
#घोषणा CXLFLASH_MAX_NUM_TARGETS_PER_BUS	1
#घोषणा CXLFLASH_MAX_NUM_LUNS_PER_TARGET	65536

#घोषणा CXLFLASH_PCI_ERROR_RECOVERY_TIMEOUT	(120 * HZ)

/* FC defines */
#घोषणा FC_MTIP_CMDCONFIG 0x010
#घोषणा FC_MTIP_STATUS 0x018
#घोषणा FC_MAX_NUM_LUNS 0x080 /* Max LUNs host can provision क्रम port */
#घोषणा FC_CUR_NUM_LUNS 0x088 /* Cur number LUNs provisioned क्रम port */
#घोषणा FC_MAX_CAP_PORT 0x090 /* Max capacity all LUNs क्रम port (4K blocks) */
#घोषणा FC_CUR_CAP_PORT 0x098 /* Cur capacity all LUNs क्रम port (4K blocks) */

#घोषणा FC_PNAME 0x300
#घोषणा FC_CONFIG 0x320
#घोषणा FC_CONFIG2 0x328
#घोषणा FC_STATUS 0x330
#घोषणा FC_ERROR 0x380
#घोषणा FC_ERRCAP 0x388
#घोषणा FC_ERRMSK 0x390
#घोषणा FC_CNT_CRCERR 0x538
#घोषणा FC_CRC_THRESH 0x580

#घोषणा FC_MTIP_CMDCONFIG_ONLINE	0x20ULL
#घोषणा FC_MTIP_CMDCONFIG_OFFLINE	0x40ULL

#घोषणा FC_MTIP_STATUS_MASK		0x30ULL
#घोषणा FC_MTIP_STATUS_ONLINE		0x20ULL
#घोषणा FC_MTIP_STATUS_OFFLINE		0x10ULL

/* TIMEOUT and RETRY definitions */

/* AFU command समयout values */
#घोषणा MC_AFU_SYNC_TIMEOUT	5	/* 5 secs */
#घोषणा MC_LUN_PROV_TIMEOUT	5	/* 5 secs */
#घोषणा MC_AFU_DEBUG_TIMEOUT	5	/* 5 secs */

/* AFU command room retry limit */
#घोषणा MC_ROOM_RETRY_CNT	10

/* FC CRC clear periodic समयr */
#घोषणा MC_CRC_THRESH 100	/* threshold in 5 mins */

#घोषणा FC_PORT_STATUS_RETRY_CNT 100	/* 100 100ms retries = 10 seconds */
#घोषणा FC_PORT_STATUS_RETRY_INTERVAL_US 100000	/* microseconds */

/* VPD defines */
#घोषणा CXLFLASH_VPD_LEN	256
#घोषणा WWPN_LEN	16
#घोषणा WWPN_BUF_LEN	(WWPN_LEN + 1)

क्रमागत unकरो_level अणु
	UNDO_NOOP = 0,
	FREE_IRQ,
	UNMAP_ONE,
	UNMAP_TWO,
	UNMAP_THREE
पूर्ण;

काष्ठा dev_dependent_vals अणु
	u64 max_sectors;
	u64 flags;
#घोषणा CXLFLASH_NOTIFY_SHUTDOWN	0x0000000000000001ULL
#घोषणा CXLFLASH_WWPN_VPD_REQUIRED	0x0000000000000002ULL
#घोषणा CXLFLASH_OCXL_DEV		0x0000000000000004ULL
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा cxlflash_backend_ops *
cxlflash_assign_ops(काष्ठा dev_dependent_vals *ddv)
अणु
	स्थिर काष्ठा cxlflash_backend_ops *ops = शून्य;

#अगर_घोषित CONFIG_OCXL_BASE
	अगर (ddv->flags & CXLFLASH_OCXL_DEV)
		ops = &cxlflash_ocxl_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CXL_BASE
	अगर (!(ddv->flags & CXLFLASH_OCXL_DEV))
		ops = &cxlflash_cxl_ops;
#पूर्ण_अगर

	वापस ops;
पूर्ण

काष्ठा asyc_पूर्णांकr_info अणु
	u64 status;
	अक्षर *desc;
	u8 port;
	u8 action;
#घोषणा CLR_FC_ERROR	0x01
#घोषणा LINK_RESET	0x02
#घोषणा SCAN_HOST	0x04
पूर्ण;

#पूर्ण_अगर /* _CXLFLASH_MAIN_H */
