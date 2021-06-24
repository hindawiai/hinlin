<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2019 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/module.h>

#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/समय.स>
#समावेश <linux/mii.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bpf.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/cache.h>
#समावेश <linux/log2.h>
#समावेश <linux/aer.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/cpu_rmap.h>
#समावेश <linux/cpumask.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <net/page_pool.h>

#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_ulp.h"
#समावेश "bnxt_sriov.h"
#समावेश "bnxt_ethtool.h"
#समावेश "bnxt_dcb.h"
#समावेश "bnxt_xdp.h"
#समावेश "bnxt_vfr.h"
#समावेश "bnxt_tc.h"
#समावेश "bnxt_devlink.h"
#समावेश "bnxt_debugfs.h"

#घोषणा BNXT_TX_TIMEOUT		(5 * HZ)
#घोषणा BNXT_DEF_MSG_ENABLE	(NETIF_MSG_DRV | NETIF_MSG_HW)

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Broadcom BCM573xx network driver");

#घोषणा BNXT_RX_OFFSET (NET_SKB_PAD + NET_IP_ALIGN)
#घोषणा BNXT_RX_DMA_OFFSET NET_SKB_PAD
#घोषणा BNXT_RX_COPY_THRESH 256

#घोषणा BNXT_TX_PUSH_THRESH 164

क्रमागत board_idx अणु
	BCM57301,
	BCM57302,
	BCM57304,
	BCM57417_NPAR,
	BCM58700,
	BCM57311,
	BCM57312,
	BCM57402,
	BCM57404,
	BCM57406,
	BCM57402_NPAR,
	BCM57407,
	BCM57412,
	BCM57414,
	BCM57416,
	BCM57417,
	BCM57412_NPAR,
	BCM57314,
	BCM57417_SFP,
	BCM57416_SFP,
	BCM57404_NPAR,
	BCM57406_NPAR,
	BCM57407_SFP,
	BCM57407_NPAR,
	BCM57414_NPAR,
	BCM57416_NPAR,
	BCM57452,
	BCM57454,
	BCM5745x_NPAR,
	BCM57508,
	BCM57504,
	BCM57502,
	BCM57508_NPAR,
	BCM57504_NPAR,
	BCM57502_NPAR,
	BCM58802,
	BCM58804,
	BCM58808,
	NETXTREME_E_VF,
	NETXTREME_C_VF,
	NETXTREME_S_VF,
	NETXTREME_C_VF_HV,
	NETXTREME_E_VF_HV,
	NETXTREME_E_P5_VF,
	NETXTREME_E_P5_VF_HV,
पूर्ण;

/* indexed by क्रमागत above */
अटल स्थिर काष्ठा अणु
	अक्षर *name;
पूर्ण board_info[] = अणु
	[BCM57301] = अणु "Broadcom BCM57301 NetXtreme-C 10Gb Ethernet" पूर्ण,
	[BCM57302] = अणु "Broadcom BCM57302 NetXtreme-C 10Gb/25Gb Ethernet" पूर्ण,
	[BCM57304] = अणु "Broadcom BCM57304 NetXtreme-C 10Gb/25Gb/40Gb/50Gb Ethernet" पूर्ण,
	[BCM57417_NPAR] = अणु "Broadcom BCM57417 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM58700] = अणु "Broadcom BCM58700 Nitro 1Gb/2.5Gb/10Gb Ethernet" पूर्ण,
	[BCM57311] = अणु "Broadcom BCM57311 NetXtreme-C 10Gb Ethernet" पूर्ण,
	[BCM57312] = अणु "Broadcom BCM57312 NetXtreme-C 10Gb/25Gb Ethernet" पूर्ण,
	[BCM57402] = अणु "Broadcom BCM57402 NetXtreme-E 10Gb Ethernet" पूर्ण,
	[BCM57404] = अणु "Broadcom BCM57404 NetXtreme-E 10Gb/25Gb Ethernet" पूर्ण,
	[BCM57406] = अणु "Broadcom BCM57406 NetXtreme-E 10GBase-T Ethernet" पूर्ण,
	[BCM57402_NPAR] = अणु "Broadcom BCM57402 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57407] = अणु "Broadcom BCM57407 NetXtreme-E 10GBase-T Ethernet" पूर्ण,
	[BCM57412] = अणु "Broadcom BCM57412 NetXtreme-E 10Gb Ethernet" पूर्ण,
	[BCM57414] = अणु "Broadcom BCM57414 NetXtreme-E 10Gb/25Gb Ethernet" पूर्ण,
	[BCM57416] = अणु "Broadcom BCM57416 NetXtreme-E 10GBase-T Ethernet" पूर्ण,
	[BCM57417] = अणु "Broadcom BCM57417 NetXtreme-E 10GBase-T Ethernet" पूर्ण,
	[BCM57412_NPAR] = अणु "Broadcom BCM57412 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57314] = अणु "Broadcom BCM57314 NetXtreme-C 10Gb/25Gb/40Gb/50Gb Ethernet" पूर्ण,
	[BCM57417_SFP] = अणु "Broadcom BCM57417 NetXtreme-E 10Gb/25Gb Ethernet" पूर्ण,
	[BCM57416_SFP] = अणु "Broadcom BCM57416 NetXtreme-E 10Gb Ethernet" पूर्ण,
	[BCM57404_NPAR] = अणु "Broadcom BCM57404 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57406_NPAR] = अणु "Broadcom BCM57406 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57407_SFP] = अणु "Broadcom BCM57407 NetXtreme-E 25Gb Ethernet" पूर्ण,
	[BCM57407_NPAR] = अणु "Broadcom BCM57407 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57414_NPAR] = अणु "Broadcom BCM57414 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57416_NPAR] = अणु "Broadcom BCM57416 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57452] = अणु "Broadcom BCM57452 NetXtreme-E 10Gb/25Gb/40Gb/50Gb Ethernet" पूर्ण,
	[BCM57454] = अणु "Broadcom BCM57454 NetXtreme-E 10Gb/25Gb/40Gb/50Gb/100Gb Ethernet" पूर्ण,
	[BCM5745x_NPAR] = अणु "Broadcom BCM5745x NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57508] = अणु "Broadcom BCM57508 NetXtreme-E 10Gb/25Gb/50Gb/100Gb/200Gb Ethernet" पूर्ण,
	[BCM57504] = अणु "Broadcom BCM57504 NetXtreme-E 10Gb/25Gb/50Gb/100Gb/200Gb Ethernet" पूर्ण,
	[BCM57502] = अणु "Broadcom BCM57502 NetXtreme-E 10Gb/25Gb/50Gb Ethernet" पूर्ण,
	[BCM57508_NPAR] = अणु "Broadcom BCM57508 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57504_NPAR] = अणु "Broadcom BCM57504 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM57502_NPAR] = अणु "Broadcom BCM57502 NetXtreme-E Ethernet Partition" पूर्ण,
	[BCM58802] = अणु "Broadcom BCM58802 NetXtreme-S 10Gb/25Gb/40Gb/50Gb Ethernet" पूर्ण,
	[BCM58804] = अणु "Broadcom BCM58804 NetXtreme-S 10Gb/25Gb/40Gb/50Gb/100Gb Ethernet" पूर्ण,
	[BCM58808] = अणु "Broadcom BCM58808 NetXtreme-S 10Gb/25Gb/40Gb/50Gb/100Gb Ethernet" पूर्ण,
	[NETXTREME_E_VF] = अणु "Broadcom NetXtreme-E Ethernet Virtual Function" पूर्ण,
	[NETXTREME_C_VF] = अणु "Broadcom NetXtreme-C Ethernet Virtual Function" पूर्ण,
	[NETXTREME_S_VF] = अणु "Broadcom NetXtreme-S Ethernet Virtual Function" पूर्ण,
	[NETXTREME_C_VF_HV] = अणु "Broadcom NetXtreme-C Virtual Function for Hyper-V" पूर्ण,
	[NETXTREME_E_VF_HV] = अणु "Broadcom NetXtreme-E Virtual Function for Hyper-V" पूर्ण,
	[NETXTREME_E_P5_VF] = अणु "Broadcom BCM5750X NetXtreme-E Ethernet Virtual Function" पूर्ण,
	[NETXTREME_E_P5_VF_HV] = अणु "Broadcom BCM5750X NetXtreme-E Virtual Function for Hyper-V" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id bnxt_pci_tbl[] = अणु
	अणु PCI_VDEVICE(BROADCOM, 0x1604), .driver_data = BCM5745x_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1605), .driver_data = BCM5745x_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1614), .driver_data = BCM57454 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c0), .driver_data = BCM57417_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c8), .driver_data = BCM57301 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c9), .driver_data = BCM57302 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ca), .driver_data = BCM57304 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16cc), .driver_data = BCM57417_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16cd), .driver_data = BCM58700 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ce), .driver_data = BCM57311 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16cf), .driver_data = BCM57312 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d0), .driver_data = BCM57402 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d1), .driver_data = BCM57404 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d2), .driver_data = BCM57406 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d4), .driver_data = BCM57402_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d5), .driver_data = BCM57407 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d6), .driver_data = BCM57412 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d7), .driver_data = BCM57414 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d8), .driver_data = BCM57416 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d9), .driver_data = BCM57417 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16de), .driver_data = BCM57412_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16df), .driver_data = BCM57314 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e2), .driver_data = BCM57417_SFP पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e3), .driver_data = BCM57416_SFP पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e7), .driver_data = BCM57404_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e8), .driver_data = BCM57406_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e9), .driver_data = BCM57407_SFP पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ea), .driver_data = BCM57407_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16eb), .driver_data = BCM57412_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ec), .driver_data = BCM57414_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ed), .driver_data = BCM57414_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ee), .driver_data = BCM57416_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16ef), .driver_data = BCM57416_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16f0), .driver_data = BCM58808 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16f1), .driver_data = BCM57452 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1750), .driver_data = BCM57508 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1751), .driver_data = BCM57504 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1752), .driver_data = BCM57502 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1800), .driver_data = BCM57508_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1801), .driver_data = BCM57504_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1802), .driver_data = BCM57502_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1803), .driver_data = BCM57508_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1804), .driver_data = BCM57504_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1805), .driver_data = BCM57502_NPAR पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0xd802), .driver_data = BCM58802 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0xd804), .driver_data = BCM58804 पूर्ण,
#अगर_घोषित CONFIG_BNXT_SRIOV
	अणु PCI_VDEVICE(BROADCOM, 0x1606), .driver_data = NETXTREME_E_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1607), .driver_data = NETXTREME_E_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1608), .driver_data = NETXTREME_E_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1609), .driver_data = NETXTREME_E_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16bd), .driver_data = NETXTREME_E_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c1), .driver_data = NETXTREME_E_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c2), .driver_data = NETXTREME_C_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c3), .driver_data = NETXTREME_C_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c4), .driver_data = NETXTREME_E_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16c5), .driver_data = NETXTREME_E_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16cb), .driver_data = NETXTREME_C_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16d3), .driver_data = NETXTREME_E_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16dc), .driver_data = NETXTREME_E_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e1), .driver_data = NETXTREME_C_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e5), .driver_data = NETXTREME_C_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x16e6), .driver_data = NETXTREME_C_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1806), .driver_data = NETXTREME_E_P5_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1807), .driver_data = NETXTREME_E_P5_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1808), .driver_data = NETXTREME_E_P5_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0x1809), .driver_data = NETXTREME_E_P5_VF_HV पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, 0xd800), .driver_data = NETXTREME_S_VF पूर्ण,
#पूर्ण_अगर
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, bnxt_pci_tbl);

अटल स्थिर u16 bnxt_vf_req_snअगर[] = अणु
	HWRM_FUNC_CFG,
	HWRM_FUNC_VF_CFG,
	HWRM_PORT_PHY_QCFG,
	HWRM_CFA_L2_FILTER_ALLOC,
पूर्ण;

अटल स्थिर u16 bnxt_async_events_arr[] = अणु
	ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE,
	ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CHANGE,
	ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD,
	ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED,
	ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE,
	ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE,
	ASYNC_EVENT_CMPL_EVENT_ID_PORT_PHY_CFG_CHANGE,
	ASYNC_EVENT_CMPL_EVENT_ID_RESET_NOTIFY,
	ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY,
	ASYNC_EVENT_CMPL_EVENT_ID_DEBUG_NOTIFICATION,
	ASYNC_EVENT_CMPL_EVENT_ID_RING_MONITOR_MSG,
	ASYNC_EVENT_CMPL_EVENT_ID_ECHO_REQUEST,
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *bnxt_pf_wq;

अटल bool bnxt_vf_pciid(क्रमागत board_idx idx)
अणु
	वापस (idx == NETXTREME_C_VF || idx == NETXTREME_E_VF ||
		idx == NETXTREME_S_VF || idx == NETXTREME_C_VF_HV ||
		idx == NETXTREME_E_VF_HV || idx == NETXTREME_E_P5_VF ||
		idx == NETXTREME_E_P5_VF_HV);
पूर्ण

#घोषणा DB_CP_REARM_FLAGS	(DB_KEY_CP | DB_IDX_VALID)
#घोषणा DB_CP_FLAGS		(DB_KEY_CP | DB_IDX_VALID | DB_IRQ_DIS)
#घोषणा DB_CP_IRQ_DIS_FLAGS	(DB_KEY_CP | DB_IRQ_DIS)

#घोषणा BNXT_CP_DB_IRQ_DIS(db)						\
		ग_लिखोl(DB_CP_IRQ_DIS_FLAGS, db)

#घोषणा BNXT_DB_CQ(db, idx)						\
	ग_लिखोl(DB_CP_FLAGS | RING_CMP(idx), (db)->करोorbell)

#घोषणा BNXT_DB_NQ_P5(db, idx)						\
	ग_लिखोq((db)->db_key64 | DBR_TYPE_NQ | RING_CMP(idx), (db)->करोorbell)

#घोषणा BNXT_DB_CQ_ARM(db, idx)						\
	ग_लिखोl(DB_CP_REARM_FLAGS | RING_CMP(idx), (db)->करोorbell)

#घोषणा BNXT_DB_NQ_ARM_P5(db, idx)					\
	ग_लिखोq((db)->db_key64 | DBR_TYPE_NQ_ARM | RING_CMP(idx), (db)->करोorbell)

अटल व्योम bnxt_db_nq(काष्ठा bnxt *bp, काष्ठा bnxt_db_info *db, u32 idx)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		BNXT_DB_NQ_P5(db, idx);
	अन्यथा
		BNXT_DB_CQ(db, idx);
पूर्ण

अटल व्योम bnxt_db_nq_arm(काष्ठा bnxt *bp, काष्ठा bnxt_db_info *db, u32 idx)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		BNXT_DB_NQ_ARM_P5(db, idx);
	अन्यथा
		BNXT_DB_CQ_ARM(db, idx);
पूर्ण

अटल व्योम bnxt_db_cq(काष्ठा bnxt *bp, काष्ठा bnxt_db_info *db, u32 idx)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		ग_लिखोq(db->db_key64 | DBR_TYPE_CQ_ARMALL | RING_CMP(idx),
		       db->करोorbell);
	अन्यथा
		BNXT_DB_CQ(db, idx);
पूर्ण

स्थिर u16 bnxt_lhपूर्णांक_arr[] = अणु
	TX_BD_FLAGS_LHINT_512_AND_SMALLER,
	TX_BD_FLAGS_LHINT_512_TO_1023,
	TX_BD_FLAGS_LHINT_1024_TO_2047,
	TX_BD_FLAGS_LHINT_1024_TO_2047,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
	TX_BD_FLAGS_LHINT_2048_AND_LARGER,
पूर्ण;

अटल u16 bnxt_xmit_get_cfa_action(काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *md_dst = skb_metadata_dst(skb);

	अगर (!md_dst || md_dst->type != METADATA_HW_PORT_MUX)
		वापस 0;

	वापस md_dst->u.port_info.port_id;
पूर्ण

अटल netdev_tx_t bnxt_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा tx_bd *txbd;
	काष्ठा tx_bd_ext *txbd1;
	काष्ठा netdev_queue *txq;
	पूर्णांक i;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक length, pad = 0;
	u32 len, मुक्त_size, vlan_tag_flags, cfa_action, flags;
	u16 prod, last_frag;
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा bnxt_tx_ring_info *txr;
	काष्ठा bnxt_sw_tx_bd *tx_buf;
	__le32 lflags = 0;

	i = skb_get_queue_mapping(skb);
	अगर (unlikely(i >= bp->tx_nr_rings)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	txq = netdev_get_tx_queue(dev, i);
	txr = &bp->tx_ring[bp->tx_ring_map[i]];
	prod = txr->tx_prod;

	मुक्त_size = bnxt_tx_avail(bp, txr);
	अगर (unlikely(मुक्त_size < skb_shinfo(skb)->nr_frags + 2)) अणु
		netअगर_tx_stop_queue(txq);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	length = skb->len;
	len = skb_headlen(skb);
	last_frag = skb_shinfo(skb)->nr_frags;

	txbd = &txr->tx_desc_ring[TX_RING(prod)][TX_IDX(prod)];

	txbd->tx_bd_opaque = prod;

	tx_buf = &txr->tx_buf_ring[prod];
	tx_buf->skb = skb;
	tx_buf->nr_frags = last_frag;

	vlan_tag_flags = 0;
	cfa_action = bnxt_xmit_get_cfa_action(skb);
	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_tag_flags = TX_BD_CFA_META_KEY_VLAN |
				 skb_vlan_tag_get(skb);
		/* Currently supports 8021Q, 8021AD vlan offloads
		 * QINQ1, QINQ2, QINQ3 vlan headers are deprecated
		 */
		अगर (skb->vlan_proto == htons(ETH_P_8021Q))
			vlan_tag_flags |= 1 << TX_BD_CFA_META_TPID_SHIFT;
	पूर्ण

	अगर (unlikely(skb->no_fcs)) अणु
		lflags |= cpu_to_le32(TX_BD_FLAGS_NO_CRC);
		जाओ normal_tx;
	पूर्ण

	अगर (मुक्त_size == bp->tx_ring_size && length <= bp->tx_push_thresh) अणु
		काष्ठा tx_push_buffer *tx_push_buf = txr->tx_push;
		काष्ठा tx_push_bd *tx_push = &tx_push_buf->push_bd;
		काष्ठा tx_bd_ext *tx_push1 = &tx_push->txbd2;
		व्योम __iomem *db = txr->tx_db.करोorbell;
		व्योम *pdata = tx_push_buf->data;
		u64 *end;
		पूर्णांक j, push_len;

		/* Set COAL_NOW to be पढ़ोy quickly क्रम the next push */
		tx_push->tx_bd_len_flags_type =
			cpu_to_le32((length << TX_BD_LEN_SHIFT) |
					TX_BD_TYPE_LONG_TX_BD |
					TX_BD_FLAGS_LHINT_512_AND_SMALLER |
					TX_BD_FLAGS_COAL_NOW |
					TX_BD_FLAGS_PACKET_END |
					(2 << TX_BD_FLAGS_BD_CNT_SHIFT));

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			tx_push1->tx_bd_hsize_lflags =
					cpu_to_le32(TX_BD_FLAGS_TCP_UDP_CHKSUM);
		अन्यथा
			tx_push1->tx_bd_hsize_lflags = 0;

		tx_push1->tx_bd_cfa_meta = cpu_to_le32(vlan_tag_flags);
		tx_push1->tx_bd_cfa_action =
			cpu_to_le32(cfa_action << TX_BD_CFA_ACTION_SHIFT);

		end = pdata + length;
		end = PTR_ALIGN(end, 8) - 1;
		*end = 0;

		skb_copy_from_linear_data(skb, pdata, len);
		pdata += len;
		क्रम (j = 0; j < last_frag; j++) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[j];
			व्योम *fptr;

			fptr = skb_frag_address_safe(frag);
			अगर (!fptr)
				जाओ normal_tx;

			स_नकल(pdata, fptr, skb_frag_size(frag));
			pdata += skb_frag_size(frag);
		पूर्ण

		txbd->tx_bd_len_flags_type = tx_push->tx_bd_len_flags_type;
		txbd->tx_bd_haddr = txr->data_mapping;
		prod = NEXT_TX(prod);
		txbd = &txr->tx_desc_ring[TX_RING(prod)][TX_IDX(prod)];
		स_नकल(txbd, tx_push1, माप(*txbd));
		prod = NEXT_TX(prod);
		tx_push->करोorbell =
			cpu_to_le32(DB_KEY_TX_PUSH | DB_LONG_TX_PUSH | prod);
		txr->tx_prod = prod;

		tx_buf->is_push = 1;
		netdev_tx_sent_queue(txq, skb->len);
		wmb();	/* Sync is_push and byte queue beक्रमe pushing data */

		push_len = (length + माप(*tx_push) + 7) / 8;
		अगर (push_len > 16) अणु
			__ioग_लिखो64_copy(db, tx_push_buf, 16);
			__ioग_लिखो32_copy(db + 4, tx_push_buf + 1,
					 (push_len - 16) << 1);
		पूर्ण अन्यथा अणु
			__ioग_लिखो64_copy(db, tx_push_buf, push_len);
		पूर्ण

		जाओ tx_करोne;
	पूर्ण

normal_tx:
	अगर (length < BNXT_MIN_PKT_SIZE) अणु
		pad = BNXT_MIN_PKT_SIZE - length;
		अगर (skb_pad(skb, pad)) अणु
			/* SKB alपढ़ोy मुक्तd. */
			tx_buf->skb = शून्य;
			वापस NETDEV_TX_OK;
		पूर्ण
		length = BNXT_MIN_PKT_SIZE;
	पूर्ण

	mapping = dma_map_single(&pdev->dev, skb->data, len, DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(&pdev->dev, mapping))) अणु
		dev_kमुक्त_skb_any(skb);
		tx_buf->skb = शून्य;
		वापस NETDEV_TX_OK;
	पूर्ण

	dma_unmap_addr_set(tx_buf, mapping, mapping);
	flags = (len << TX_BD_LEN_SHIFT) | TX_BD_TYPE_LONG_TX_BD |
		((last_frag + 2) << TX_BD_FLAGS_BD_CNT_SHIFT);

	txbd->tx_bd_haddr = cpu_to_le64(mapping);

	prod = NEXT_TX(prod);
	txbd1 = (काष्ठा tx_bd_ext *)
		&txr->tx_desc_ring[TX_RING(prod)][TX_IDX(prod)];

	txbd1->tx_bd_hsize_lflags = lflags;
	अगर (skb_is_gso(skb)) अणु
		u32 hdr_len;

		अगर (skb->encapsulation)
			hdr_len = skb_inner_network_offset(skb) +
				skb_inner_network_header_len(skb) +
				inner_tcp_hdrlen(skb);
		अन्यथा
			hdr_len = skb_transport_offset(skb) +
				tcp_hdrlen(skb);

		txbd1->tx_bd_hsize_lflags |= cpu_to_le32(TX_BD_FLAGS_LSO |
					TX_BD_FLAGS_T_IPID |
					(hdr_len << (TX_BD_HSIZE_SHIFT - 1)));
		length = skb_shinfo(skb)->gso_size;
		txbd1->tx_bd_mss = cpu_to_le32(length);
		length += hdr_len;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		txbd1->tx_bd_hsize_lflags |=
			cpu_to_le32(TX_BD_FLAGS_TCP_UDP_CHKSUM);
		txbd1->tx_bd_mss = 0;
	पूर्ण

	length >>= 9;
	अगर (unlikely(length >= ARRAY_SIZE(bnxt_lhपूर्णांक_arr))) अणु
		dev_warn_ratelimited(&pdev->dev, "Dropped oversize %d bytes TX packet.\n",
				     skb->len);
		i = 0;
		जाओ tx_dma_error;
	पूर्ण
	flags |= bnxt_lhपूर्णांक_arr[length];
	txbd->tx_bd_len_flags_type = cpu_to_le32(flags);

	txbd1->tx_bd_cfa_meta = cpu_to_le32(vlan_tag_flags);
	txbd1->tx_bd_cfa_action =
			cpu_to_le32(cfa_action << TX_BD_CFA_ACTION_SHIFT);
	क्रम (i = 0; i < last_frag; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		prod = NEXT_TX(prod);
		txbd = &txr->tx_desc_ring[TX_RING(prod)][TX_IDX(prod)];

		len = skb_frag_size(frag);
		mapping = skb_frag_dma_map(&pdev->dev, frag, 0, len,
					   DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(&pdev->dev, mapping)))
			जाओ tx_dma_error;

		tx_buf = &txr->tx_buf_ring[prod];
		dma_unmap_addr_set(tx_buf, mapping, mapping);

		txbd->tx_bd_haddr = cpu_to_le64(mapping);

		flags = len << TX_BD_LEN_SHIFT;
		txbd->tx_bd_len_flags_type = cpu_to_le32(flags);
	पूर्ण

	flags &= ~TX_BD_LEN;
	txbd->tx_bd_len_flags_type =
		cpu_to_le32(((len + pad) << TX_BD_LEN_SHIFT) | flags |
			    TX_BD_FLAGS_PACKET_END);

	netdev_tx_sent_queue(txq, skb->len);

	/* Sync BD data beक्रमe updating करोorbell */
	wmb();

	prod = NEXT_TX(prod);
	txr->tx_prod = prod;

	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(txq))
		bnxt_db_ग_लिखो(bp, &txr->tx_db, prod);

tx_करोne:

	अगर (unlikely(bnxt_tx_avail(bp, txr) <= MAX_SKB_FRAGS + 1)) अणु
		अगर (netdev_xmit_more() && !tx_buf->is_push)
			bnxt_db_ग_लिखो(bp, &txr->tx_db, prod);

		netअगर_tx_stop_queue(txq);

		/* netअगर_tx_stop_queue() must be करोne beक्रमe checking
		 * tx index in bnxt_tx_avail() below, because in
		 * bnxt_tx_पूर्णांक(), we update tx index beक्रमe checking क्रम
		 * netअगर_tx_queue_stopped().
		 */
		smp_mb();
		अगर (bnxt_tx_avail(bp, txr) > bp->tx_wake_thresh)
			netअगर_tx_wake_queue(txq);
	पूर्ण
	वापस NETDEV_TX_OK;

tx_dma_error:
	last_frag = i;

	/* start back at beginning and unmap skb */
	prod = txr->tx_prod;
	tx_buf = &txr->tx_buf_ring[prod];
	tx_buf->skb = शून्य;
	dma_unmap_single(&pdev->dev, dma_unmap_addr(tx_buf, mapping),
			 skb_headlen(skb), PCI_DMA_TODEVICE);
	prod = NEXT_TX(prod);

	/* unmap reमुख्यing mapped pages */
	क्रम (i = 0; i < last_frag; i++) अणु
		prod = NEXT_TX(prod);
		tx_buf = &txr->tx_buf_ring[prod];
		dma_unmap_page(&pdev->dev, dma_unmap_addr(tx_buf, mapping),
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       PCI_DMA_TODEVICE);
	पूर्ण

	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम bnxt_tx_पूर्णांक(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi, पूर्णांक nr_pkts)
अणु
	काष्ठा bnxt_tx_ring_info *txr = bnapi->tx_ring;
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(bp->dev, txr->txq_index);
	u16 cons = txr->tx_cons;
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक i;
	अचिन्हित पूर्णांक tx_bytes = 0;

	क्रम (i = 0; i < nr_pkts; i++) अणु
		काष्ठा bnxt_sw_tx_bd *tx_buf;
		काष्ठा sk_buff *skb;
		पूर्णांक j, last;

		tx_buf = &txr->tx_buf_ring[cons];
		cons = NEXT_TX(cons);
		skb = tx_buf->skb;
		tx_buf->skb = शून्य;

		अगर (tx_buf->is_push) अणु
			tx_buf->is_push = 0;
			जाओ next_tx_पूर्णांक;
		पूर्ण

		dma_unmap_single(&pdev->dev, dma_unmap_addr(tx_buf, mapping),
				 skb_headlen(skb), PCI_DMA_TODEVICE);
		last = tx_buf->nr_frags;

		क्रम (j = 0; j < last; j++) अणु
			cons = NEXT_TX(cons);
			tx_buf = &txr->tx_buf_ring[cons];
			dma_unmap_page(
				&pdev->dev,
				dma_unmap_addr(tx_buf, mapping),
				skb_frag_size(&skb_shinfo(skb)->frags[j]),
				PCI_DMA_TODEVICE);
		पूर्ण

next_tx_पूर्णांक:
		cons = NEXT_TX(cons);

		tx_bytes += skb->len;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	netdev_tx_completed_queue(txq, nr_pkts, tx_bytes);
	txr->tx_cons = cons;

	/* Need to make the tx_cons update visible to bnxt_start_xmit()
	 * beक्रमe checking क्रम netअगर_tx_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that bnxt_start_xmit()
	 * will miss it and cause the queue to be stopped क्रमever.
	 */
	smp_mb();

	अगर (unlikely(netअगर_tx_queue_stopped(txq)) &&
	    (bnxt_tx_avail(bp, txr) > bp->tx_wake_thresh)) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_tx_queue_stopped(txq) &&
		    bnxt_tx_avail(bp, txr) > bp->tx_wake_thresh &&
		    txr->dev_state != BNXT_DEV_STATE_CLOSING)
			netअगर_tx_wake_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल काष्ठा page *__bnxt_alloc_rx_page(काष्ठा bnxt *bp, dma_addr_t *mapping,
					 काष्ठा bnxt_rx_ring_info *rxr,
					 gfp_t gfp)
अणु
	काष्ठा device *dev = &bp->pdev->dev;
	काष्ठा page *page;

	page = page_pool_dev_alloc_pages(rxr->page_pool);
	अगर (!page)
		वापस शून्य;

	*mapping = dma_map_page_attrs(dev, page, 0, PAGE_SIZE, bp->rx_dir,
				      DMA_ATTR_WEAK_ORDERING);
	अगर (dma_mapping_error(dev, *mapping)) अणु
		page_pool_recycle_direct(rxr->page_pool, page);
		वापस शून्य;
	पूर्ण
	*mapping += bp->rx_dma_offset;
	वापस page;
पूर्ण

अटल अंतरभूत u8 *__bnxt_alloc_rx_data(काष्ठा bnxt *bp, dma_addr_t *mapping,
				       gfp_t gfp)
अणु
	u8 *data;
	काष्ठा pci_dev *pdev = bp->pdev;

	data = kदो_स्मृति(bp->rx_buf_size, gfp);
	अगर (!data)
		वापस शून्य;

	*mapping = dma_map_single_attrs(&pdev->dev, data + bp->rx_dma_offset,
					bp->rx_buf_use_size, bp->rx_dir,
					DMA_ATTR_WEAK_ORDERING);

	अगर (dma_mapping_error(&pdev->dev, *mapping)) अणु
		kमुक्त(data);
		data = शून्य;
	पूर्ण
	वापस data;
पूर्ण

पूर्णांक bnxt_alloc_rx_data(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr,
		       u16 prod, gfp_t gfp)
अणु
	काष्ठा rx_bd *rxbd = &rxr->rx_desc_ring[RX_RING(prod)][RX_IDX(prod)];
	काष्ठा bnxt_sw_rx_bd *rx_buf = &rxr->rx_buf_ring[prod];
	dma_addr_t mapping;

	अगर (BNXT_RX_PAGE_MODE(bp)) अणु
		काष्ठा page *page =
			__bnxt_alloc_rx_page(bp, &mapping, rxr, gfp);

		अगर (!page)
			वापस -ENOMEM;

		rx_buf->data = page;
		rx_buf->data_ptr = page_address(page) + bp->rx_offset;
	पूर्ण अन्यथा अणु
		u8 *data = __bnxt_alloc_rx_data(bp, &mapping, gfp);

		अगर (!data)
			वापस -ENOMEM;

		rx_buf->data = data;
		rx_buf->data_ptr = data + bp->rx_offset;
	पूर्ण
	rx_buf->mapping = mapping;

	rxbd->rx_bd_haddr = cpu_to_le64(mapping);
	वापस 0;
पूर्ण

व्योम bnxt_reuse_rx_data(काष्ठा bnxt_rx_ring_info *rxr, u16 cons, व्योम *data)
अणु
	u16 prod = rxr->rx_prod;
	काष्ठा bnxt_sw_rx_bd *cons_rx_buf, *prod_rx_buf;
	काष्ठा rx_bd *cons_bd, *prod_bd;

	prod_rx_buf = &rxr->rx_buf_ring[prod];
	cons_rx_buf = &rxr->rx_buf_ring[cons];

	prod_rx_buf->data = data;
	prod_rx_buf->data_ptr = cons_rx_buf->data_ptr;

	prod_rx_buf->mapping = cons_rx_buf->mapping;

	prod_bd = &rxr->rx_desc_ring[RX_RING(prod)][RX_IDX(prod)];
	cons_bd = &rxr->rx_desc_ring[RX_RING(cons)][RX_IDX(cons)];

	prod_bd->rx_bd_haddr = cons_bd->rx_bd_haddr;
पूर्ण

अटल अंतरभूत u16 bnxt_find_next_agg_idx(काष्ठा bnxt_rx_ring_info *rxr, u16 idx)
अणु
	u16 next, max = rxr->rx_agg_bmap_size;

	next = find_next_zero_bit(rxr->rx_agg_bmap, max, idx);
	अगर (next >= max)
		next = find_first_zero_bit(rxr->rx_agg_bmap, max);
	वापस next;
पूर्ण

अटल अंतरभूत पूर्णांक bnxt_alloc_rx_page(काष्ठा bnxt *bp,
				     काष्ठा bnxt_rx_ring_info *rxr,
				     u16 prod, gfp_t gfp)
अणु
	काष्ठा rx_bd *rxbd =
		&rxr->rx_agg_desc_ring[RX_RING(prod)][RX_IDX(prod)];
	काष्ठा bnxt_sw_rx_agg_bd *rx_agg_buf;
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा page *page;
	dma_addr_t mapping;
	u16 sw_prod = rxr->rx_sw_agg_prod;
	अचिन्हित पूर्णांक offset = 0;

	अगर (PAGE_SIZE > BNXT_RX_PAGE_SIZE) अणु
		page = rxr->rx_page;
		अगर (!page) अणु
			page = alloc_page(gfp);
			अगर (!page)
				वापस -ENOMEM;
			rxr->rx_page = page;
			rxr->rx_page_offset = 0;
		पूर्ण
		offset = rxr->rx_page_offset;
		rxr->rx_page_offset += BNXT_RX_PAGE_SIZE;
		अगर (rxr->rx_page_offset == PAGE_SIZE)
			rxr->rx_page = शून्य;
		अन्यथा
			get_page(page);
	पूर्ण अन्यथा अणु
		page = alloc_page(gfp);
		अगर (!page)
			वापस -ENOMEM;
	पूर्ण

	mapping = dma_map_page_attrs(&pdev->dev, page, offset,
				     BNXT_RX_PAGE_SIZE, PCI_DMA_FROMDEVICE,
				     DMA_ATTR_WEAK_ORDERING);
	अगर (dma_mapping_error(&pdev->dev, mapping)) अणु
		__मुक्त_page(page);
		वापस -EIO;
	पूर्ण

	अगर (unlikely(test_bit(sw_prod, rxr->rx_agg_bmap)))
		sw_prod = bnxt_find_next_agg_idx(rxr, sw_prod);

	__set_bit(sw_prod, rxr->rx_agg_bmap);
	rx_agg_buf = &rxr->rx_agg_ring[sw_prod];
	rxr->rx_sw_agg_prod = NEXT_RX_AGG(sw_prod);

	rx_agg_buf->page = page;
	rx_agg_buf->offset = offset;
	rx_agg_buf->mapping = mapping;
	rxbd->rx_bd_haddr = cpu_to_le64(mapping);
	rxbd->rx_bd_opaque = sw_prod;
	वापस 0;
पूर्ण

अटल काष्ठा rx_agg_cmp *bnxt_get_agg(काष्ठा bnxt *bp,
				       काष्ठा bnxt_cp_ring_info *cpr,
				       u16 cp_cons, u16 curr)
अणु
	काष्ठा rx_agg_cmp *agg;

	cp_cons = RING_CMP(ADV_RAW_CMP(cp_cons, curr));
	agg = (काष्ठा rx_agg_cmp *)
		&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];
	वापस agg;
पूर्ण

अटल काष्ठा rx_agg_cmp *bnxt_get_tpa_agg_p5(काष्ठा bnxt *bp,
					      काष्ठा bnxt_rx_ring_info *rxr,
					      u16 agg_id, u16 curr)
अणु
	काष्ठा bnxt_tpa_info *tpa_info = &rxr->rx_tpa[agg_id];

	वापस &tpa_info->agg_arr[curr];
पूर्ण

अटल व्योम bnxt_reuse_rx_agg_bufs(काष्ठा bnxt_cp_ring_info *cpr, u16 idx,
				   u16 start, u32 agg_bufs, bool tpa)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u16 prod = rxr->rx_agg_prod;
	u16 sw_prod = rxr->rx_sw_agg_prod;
	bool p5_tpa = false;
	u32 i;

	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) && tpa)
		p5_tpa = true;

	क्रम (i = 0; i < agg_bufs; i++) अणु
		u16 cons;
		काष्ठा rx_agg_cmp *agg;
		काष्ठा bnxt_sw_rx_agg_bd *cons_rx_buf, *prod_rx_buf;
		काष्ठा rx_bd *prod_bd;
		काष्ठा page *page;

		अगर (p5_tpa)
			agg = bnxt_get_tpa_agg_p5(bp, rxr, idx, start + i);
		अन्यथा
			agg = bnxt_get_agg(bp, cpr, idx, start + i);
		cons = agg->rx_agg_cmp_opaque;
		__clear_bit(cons, rxr->rx_agg_bmap);

		अगर (unlikely(test_bit(sw_prod, rxr->rx_agg_bmap)))
			sw_prod = bnxt_find_next_agg_idx(rxr, sw_prod);

		__set_bit(sw_prod, rxr->rx_agg_bmap);
		prod_rx_buf = &rxr->rx_agg_ring[sw_prod];
		cons_rx_buf = &rxr->rx_agg_ring[cons];

		/* It is possible क्रम sw_prod to be equal to cons, so
		 * set cons_rx_buf->page to शून्य first.
		 */
		page = cons_rx_buf->page;
		cons_rx_buf->page = शून्य;
		prod_rx_buf->page = page;
		prod_rx_buf->offset = cons_rx_buf->offset;

		prod_rx_buf->mapping = cons_rx_buf->mapping;

		prod_bd = &rxr->rx_agg_desc_ring[RX_RING(prod)][RX_IDX(prod)];

		prod_bd->rx_bd_haddr = cpu_to_le64(cons_rx_buf->mapping);
		prod_bd->rx_bd_opaque = sw_prod;

		prod = NEXT_RX_AGG(prod);
		sw_prod = NEXT_RX_AGG(sw_prod);
	पूर्ण
	rxr->rx_agg_prod = prod;
	rxr->rx_sw_agg_prod = sw_prod;
पूर्ण

अटल काष्ठा sk_buff *bnxt_rx_page_skb(काष्ठा bnxt *bp,
					काष्ठा bnxt_rx_ring_info *rxr,
					u16 cons, व्योम *data, u8 *data_ptr,
					dma_addr_t dma_addr,
					अचिन्हित पूर्णांक offset_and_len)
अणु
	अचिन्हित पूर्णांक payload = offset_and_len >> 16;
	अचिन्हित पूर्णांक len = offset_and_len & 0xffff;
	skb_frag_t *frag;
	काष्ठा page *page = data;
	u16 prod = rxr->rx_prod;
	काष्ठा sk_buff *skb;
	पूर्णांक off, err;

	err = bnxt_alloc_rx_data(bp, rxr, prod, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		bnxt_reuse_rx_data(rxr, cons, data);
		वापस शून्य;
	पूर्ण
	dma_addr -= bp->rx_dma_offset;
	dma_unmap_page_attrs(&bp->pdev->dev, dma_addr, PAGE_SIZE, bp->rx_dir,
			     DMA_ATTR_WEAK_ORDERING);
	page_pool_release_page(rxr->page_pool, page);

	अगर (unlikely(!payload))
		payload = eth_get_headlen(bp->dev, data_ptr, len);

	skb = napi_alloc_skb(&rxr->bnapi->napi, payload);
	अगर (!skb) अणु
		__मुक्त_page(page);
		वापस शून्य;
	पूर्ण

	off = (व्योम *)data_ptr - page_address(page);
	skb_add_rx_frag(skb, 0, page, off, len, PAGE_SIZE);
	स_नकल(skb->data - NET_IP_ALIGN, data_ptr - NET_IP_ALIGN,
	       payload + NET_IP_ALIGN);

	frag = &skb_shinfo(skb)->frags[0];
	skb_frag_size_sub(frag, payload);
	skb_frag_off_add(frag, payload);
	skb->data_len -= payload;
	skb->tail += payload;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *bnxt_rx_skb(काष्ठा bnxt *bp,
				   काष्ठा bnxt_rx_ring_info *rxr, u16 cons,
				   व्योम *data, u8 *data_ptr,
				   dma_addr_t dma_addr,
				   अचिन्हित पूर्णांक offset_and_len)
अणु
	u16 prod = rxr->rx_prod;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	err = bnxt_alloc_rx_data(bp, rxr, prod, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		bnxt_reuse_rx_data(rxr, cons, data);
		वापस शून्य;
	पूर्ण

	skb = build_skb(data, 0);
	dma_unmap_single_attrs(&bp->pdev->dev, dma_addr, bp->rx_buf_use_size,
			       bp->rx_dir, DMA_ATTR_WEAK_ORDERING);
	अगर (!skb) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, bp->rx_offset);
	skb_put(skb, offset_and_len & 0xffff);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *bnxt_rx_pages(काष्ठा bnxt *bp,
				     काष्ठा bnxt_cp_ring_info *cpr,
				     काष्ठा sk_buff *skb, u16 idx,
				     u32 agg_bufs, bool tpa)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u16 prod = rxr->rx_agg_prod;
	bool p5_tpa = false;
	u32 i;

	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) && tpa)
		p5_tpa = true;

	क्रम (i = 0; i < agg_bufs; i++) अणु
		u16 cons, frag_len;
		काष्ठा rx_agg_cmp *agg;
		काष्ठा bnxt_sw_rx_agg_bd *cons_rx_buf;
		काष्ठा page *page;
		dma_addr_t mapping;

		अगर (p5_tpa)
			agg = bnxt_get_tpa_agg_p5(bp, rxr, idx, i);
		अन्यथा
			agg = bnxt_get_agg(bp, cpr, idx, i);
		cons = agg->rx_agg_cmp_opaque;
		frag_len = (le32_to_cpu(agg->rx_agg_cmp_len_flags_type) &
			    RX_AGG_CMP_LEN) >> RX_AGG_CMP_LEN_SHIFT;

		cons_rx_buf = &rxr->rx_agg_ring[cons];
		skb_fill_page_desc(skb, i, cons_rx_buf->page,
				   cons_rx_buf->offset, frag_len);
		__clear_bit(cons, rxr->rx_agg_bmap);

		/* It is possible क्रम bnxt_alloc_rx_page() to allocate
		 * a sw_prod index that equals the cons index, so we
		 * need to clear the cons entry now.
		 */
		mapping = cons_rx_buf->mapping;
		page = cons_rx_buf->page;
		cons_rx_buf->page = शून्य;

		अगर (bnxt_alloc_rx_page(bp, rxr, prod, GFP_ATOMIC) != 0) अणु
			काष्ठा skb_shared_info *shinfo;
			अचिन्हित पूर्णांक nr_frags;

			shinfo = skb_shinfo(skb);
			nr_frags = --shinfo->nr_frags;
			__skb_frag_set_page(&shinfo->frags[nr_frags], शून्य);

			dev_kमुक्त_skb(skb);

			cons_rx_buf->page = page;

			/* Update prod since possibly some pages have been
			 * allocated alपढ़ोy.
			 */
			rxr->rx_agg_prod = prod;
			bnxt_reuse_rx_agg_bufs(cpr, idx, i, agg_bufs - i, tpa);
			वापस शून्य;
		पूर्ण

		dma_unmap_page_attrs(&pdev->dev, mapping, BNXT_RX_PAGE_SIZE,
				     PCI_DMA_FROMDEVICE,
				     DMA_ATTR_WEAK_ORDERING);

		skb->data_len += frag_len;
		skb->len += frag_len;
		skb->truesize += PAGE_SIZE;

		prod = NEXT_RX_AGG(prod);
	पूर्ण
	rxr->rx_agg_prod = prod;
	वापस skb;
पूर्ण

अटल पूर्णांक bnxt_agg_bufs_valid(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			       u8 agg_bufs, u32 *raw_cons)
अणु
	u16 last;
	काष्ठा rx_agg_cmp *agg;

	*raw_cons = ADV_RAW_CMP(*raw_cons, agg_bufs);
	last = RING_CMP(*raw_cons);
	agg = (काष्ठा rx_agg_cmp *)
		&cpr->cp_desc_ring[CP_RING(last)][CP_IDX(last)];
	वापस RX_AGG_CMP_VALID(agg, *raw_cons);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *bnxt_copy_skb(काष्ठा bnxt_napi *bnapi, u8 *data,
					    अचिन्हित पूर्णांक len,
					    dma_addr_t mapping)
अणु
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा sk_buff *skb;

	skb = napi_alloc_skb(&bnapi->napi, len);
	अगर (!skb)
		वापस शून्य;

	dma_sync_single_क्रम_cpu(&pdev->dev, mapping, bp->rx_copy_thresh,
				bp->rx_dir);

	स_नकल(skb->data - NET_IP_ALIGN, data - NET_IP_ALIGN,
	       len + NET_IP_ALIGN);

	dma_sync_single_क्रम_device(&pdev->dev, mapping, bp->rx_copy_thresh,
				   bp->rx_dir);

	skb_put(skb, len);
	वापस skb;
पूर्ण

अटल पूर्णांक bnxt_discard_rx(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			   u32 *raw_cons, व्योम *cmp)
अणु
	काष्ठा rx_cmp *rxcmp = cmp;
	u32 पंचांगp_raw_cons = *raw_cons;
	u8 cmp_type, agg_bufs = 0;

	cmp_type = RX_CMP_TYPE(rxcmp);

	अगर (cmp_type == CMP_TYPE_RX_L2_CMP) अणु
		agg_bufs = (le32_to_cpu(rxcmp->rx_cmp_misc_v1) &
			    RX_CMP_AGG_BUFS) >>
			   RX_CMP_AGG_BUFS_SHIFT;
	पूर्ण अन्यथा अगर (cmp_type == CMP_TYPE_RX_L2_TPA_END_CMP) अणु
		काष्ठा rx_tpa_end_cmp *tpa_end = cmp;

		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			वापस 0;

		agg_bufs = TPA_END_AGG_BUFS(tpa_end);
	पूर्ण

	अगर (agg_bufs) अणु
		अगर (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, &पंचांगp_raw_cons))
			वापस -EBUSY;
	पूर्ण
	*raw_cons = पंचांगp_raw_cons;
	वापस 0;
पूर्ण

अटल व्योम bnxt_queue_fw_reset_work(काष्ठा bnxt *bp, अचिन्हित दीर्घ delay)
अणु
	अगर (!(test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)))
		वापस;

	अगर (BNXT_PF(bp))
		queue_delayed_work(bnxt_pf_wq, &bp->fw_reset_task, delay);
	अन्यथा
		schedule_delayed_work(&bp->fw_reset_task, delay);
पूर्ण

अटल व्योम bnxt_queue_sp_work(काष्ठा bnxt *bp)
अणु
	अगर (BNXT_PF(bp))
		queue_work(bnxt_pf_wq, &bp->sp_task);
	अन्यथा
		schedule_work(&bp->sp_task);
पूर्ण

अटल व्योम bnxt_sched_reset(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr)
अणु
	अगर (!rxr->bnapi->in_reset) अणु
		rxr->bnapi->in_reset = true;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			set_bit(BNXT_RESET_TASK_SP_EVENT, &bp->sp_event);
		अन्यथा
			set_bit(BNXT_RST_RING_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण
	rxr->rx_next_cons = 0xffff;
पूर्ण

अटल u16 bnxt_alloc_agg_idx(काष्ठा bnxt_rx_ring_info *rxr, u16 agg_id)
अणु
	काष्ठा bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;
	u16 idx = agg_id & MAX_TPA_P5_MASK;

	अगर (test_bit(idx, map->agg_idx_bmap))
		idx = find_first_zero_bit(map->agg_idx_bmap,
					  BNXT_AGG_IDX_BMAP_SIZE);
	__set_bit(idx, map->agg_idx_bmap);
	map->agg_id_tbl[agg_id] = idx;
	वापस idx;
पूर्ण

अटल व्योम bnxt_मुक्त_agg_idx(काष्ठा bnxt_rx_ring_info *rxr, u16 idx)
अणु
	काष्ठा bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;

	__clear_bit(idx, map->agg_idx_bmap);
पूर्ण

अटल u16 bnxt_lookup_agg_idx(काष्ठा bnxt_rx_ring_info *rxr, u16 agg_id)
अणु
	काष्ठा bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;

	वापस map->agg_id_tbl[agg_id];
पूर्ण

अटल व्योम bnxt_tpa_start(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr,
			   काष्ठा rx_tpa_start_cmp *tpa_start,
			   काष्ठा rx_tpa_start_cmp_ext *tpa_start1)
अणु
	काष्ठा bnxt_sw_rx_bd *cons_rx_buf, *prod_rx_buf;
	काष्ठा bnxt_tpa_info *tpa_info;
	u16 cons, prod, agg_id;
	काष्ठा rx_bd *prod_bd;
	dma_addr_t mapping;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		agg_id = TPA_START_AGG_ID_P5(tpa_start);
		agg_id = bnxt_alloc_agg_idx(rxr, agg_id);
	पूर्ण अन्यथा अणु
		agg_id = TPA_START_AGG_ID(tpa_start);
	पूर्ण
	cons = tpa_start->rx_tpa_start_cmp_opaque;
	prod = rxr->rx_prod;
	cons_rx_buf = &rxr->rx_buf_ring[cons];
	prod_rx_buf = &rxr->rx_buf_ring[prod];
	tpa_info = &rxr->rx_tpa[agg_id];

	अगर (unlikely(cons != rxr->rx_next_cons ||
		     TPA_START_ERROR(tpa_start))) अणु
		netdev_warn(bp->dev, "TPA cons %x, expected cons %x, error code %x\n",
			    cons, rxr->rx_next_cons,
			    TPA_START_ERROR_CODE(tpa_start1));
		bnxt_sched_reset(bp, rxr);
		वापस;
	पूर्ण
	/* Store cfa_code in tpa_info to use in tpa_end
	 * completion processing.
	 */
	tpa_info->cfa_code = TPA_START_CFA_CODE(tpa_start1);
	prod_rx_buf->data = tpa_info->data;
	prod_rx_buf->data_ptr = tpa_info->data_ptr;

	mapping = tpa_info->mapping;
	prod_rx_buf->mapping = mapping;

	prod_bd = &rxr->rx_desc_ring[RX_RING(prod)][RX_IDX(prod)];

	prod_bd->rx_bd_haddr = cpu_to_le64(mapping);

	tpa_info->data = cons_rx_buf->data;
	tpa_info->data_ptr = cons_rx_buf->data_ptr;
	cons_rx_buf->data = शून्य;
	tpa_info->mapping = cons_rx_buf->mapping;

	tpa_info->len =
		le32_to_cpu(tpa_start->rx_tpa_start_cmp_len_flags_type) >>
				RX_TPA_START_CMP_LEN_SHIFT;
	अगर (likely(TPA_START_HASH_VALID(tpa_start))) अणु
		u32 hash_type = TPA_START_HASH_TYPE(tpa_start);

		tpa_info->hash_type = PKT_HASH_TYPE_L4;
		tpa_info->gso_type = SKB_GSO_TCPV4;
		/* RSS profiles 1 and 3 with extract code 0 क्रम inner 4-tuple */
		अगर (hash_type == 3 || TPA_START_IS_IPV6(tpa_start1))
			tpa_info->gso_type = SKB_GSO_TCPV6;
		tpa_info->rss_hash =
			le32_to_cpu(tpa_start->rx_tpa_start_cmp_rss_hash);
	पूर्ण अन्यथा अणु
		tpa_info->hash_type = PKT_HASH_TYPE_NONE;
		tpa_info->gso_type = 0;
		netअगर_warn(bp, rx_err, bp->dev, "TPA packet without valid hash\n");
	पूर्ण
	tpa_info->flags2 = le32_to_cpu(tpa_start1->rx_tpa_start_cmp_flags2);
	tpa_info->metadata = le32_to_cpu(tpa_start1->rx_tpa_start_cmp_metadata);
	tpa_info->hdr_info = le32_to_cpu(tpa_start1->rx_tpa_start_cmp_hdr_info);
	tpa_info->agg_count = 0;

	rxr->rx_prod = NEXT_RX(prod);
	cons = NEXT_RX(cons);
	rxr->rx_next_cons = NEXT_RX(cons);
	cons_rx_buf = &rxr->rx_buf_ring[cons];

	bnxt_reuse_rx_data(rxr, cons, cons_rx_buf->data);
	rxr->rx_prod = NEXT_RX(rxr->rx_prod);
	cons_rx_buf->data = शून्य;
पूर्ण

अटल व्योम bnxt_पात_tpa(काष्ठा bnxt_cp_ring_info *cpr, u16 idx, u32 agg_bufs)
अणु
	अगर (agg_bufs)
		bnxt_reuse_rx_agg_bufs(cpr, idx, 0, agg_bufs, true);
पूर्ण

#अगर_घोषित CONFIG_INET
अटल व्योम bnxt_gro_tunnel(काष्ठा sk_buff *skb, __be16 ip_proto)
अणु
	काष्ठा udphdr *uh = शून्य;

	अगर (ip_proto == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

		अगर (iph->protocol == IPPROTO_UDP)
			uh = (काष्ठा udphdr *)(iph + 1);
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *)skb->data;

		अगर (iph->nexthdr == IPPROTO_UDP)
			uh = (काष्ठा udphdr *)(iph + 1);
	पूर्ण
	अगर (uh) अणु
		अगर (uh->check)
			skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
		अन्यथा
			skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा sk_buff *bnxt_gro_func_5731x(काष्ठा bnxt_tpa_info *tpa_info,
					   पूर्णांक payload_off, पूर्णांक tcp_ts,
					   काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	काष्ठा tcphdr *th;
	पूर्णांक len, nw_off;
	u16 outer_ip_off, inner_ip_off, inner_mac_off;
	u32 hdr_info = tpa_info->hdr_info;
	bool loopback = false;

	inner_ip_off = BNXT_TPA_INNER_L3_OFF(hdr_info);
	inner_mac_off = BNXT_TPA_INNER_L2_OFF(hdr_info);
	outer_ip_off = BNXT_TPA_OUTER_L3_OFF(hdr_info);

	/* If the packet is an पूर्णांकernal loopback packet, the offsets will
	 * have an extra 4 bytes.
	 */
	अगर (inner_mac_off == 4) अणु
		loopback = true;
	पूर्ण अन्यथा अगर (inner_mac_off > 4) अणु
		__be16 proto = *((__be16 *)(skb->data + inner_ip_off -
					    ETH_HLEN - 2));

		/* We only support inner iPv4/ipv6.  If we करोn't see the
		 * correct protocol ID, it must be a loopback packet where
		 * the offsets are off by 4.
		 */
		अगर (proto != htons(ETH_P_IP) && proto != htons(ETH_P_IPV6))
			loopback = true;
	पूर्ण
	अगर (loopback) अणु
		/* पूर्णांकernal loopback packet, subtract all offsets by 4 */
		inner_ip_off -= 4;
		inner_mac_off -= 4;
		outer_ip_off -= 4;
	पूर्ण

	nw_off = inner_ip_off - ETH_HLEN;
	skb_set_network_header(skb, nw_off);
	अगर (tpa_info->flags2 & RX_TPA_START_CMP_FLAGS2_IP_TYPE) अणु
		काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

		skb_set_transport_header(skb, nw_off + माप(काष्ठा ipv6hdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v6_check(len, &iph->saddr, &iph->daddr, 0);
	पूर्ण अन्यथा अणु
		काष्ठा iphdr *iph = ip_hdr(skb);

		skb_set_transport_header(skb, nw_off + माप(काष्ठा iphdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v4_check(len, iph->saddr, iph->daddr, 0);
	पूर्ण

	अगर (inner_mac_off) अणु /* tunnel */
		__be16 proto = *((__be16 *)(skb->data + outer_ip_off -
					    ETH_HLEN - 2));

		bnxt_gro_tunnel(skb, proto);
	पूर्ण
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *bnxt_gro_func_5750x(काष्ठा bnxt_tpa_info *tpa_info,
					   पूर्णांक payload_off, पूर्णांक tcp_ts,
					   काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	u16 outer_ip_off, inner_ip_off, inner_mac_off;
	u32 hdr_info = tpa_info->hdr_info;
	पूर्णांक iphdr_len, nw_off;

	inner_ip_off = BNXT_TPA_INNER_L3_OFF(hdr_info);
	inner_mac_off = BNXT_TPA_INNER_L2_OFF(hdr_info);
	outer_ip_off = BNXT_TPA_OUTER_L3_OFF(hdr_info);

	nw_off = inner_ip_off - ETH_HLEN;
	skb_set_network_header(skb, nw_off);
	iphdr_len = (tpa_info->flags2 & RX_TPA_START_CMP_FLAGS2_IP_TYPE) ?
		     माप(काष्ठा ipv6hdr) : माप(काष्ठा iphdr);
	skb_set_transport_header(skb, nw_off + iphdr_len);

	अगर (inner_mac_off) अणु /* tunnel */
		__be16 proto = *((__be16 *)(skb->data + outer_ip_off -
					    ETH_HLEN - 2));

		bnxt_gro_tunnel(skb, proto);
	पूर्ण
#पूर्ण_अगर
	वापस skb;
पूर्ण

#घोषणा BNXT_IPV4_HDR_SIZE	(माप(काष्ठा iphdr) + माप(काष्ठा tcphdr))
#घोषणा BNXT_IPV6_HDR_SIZE	(माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr))

अटल काष्ठा sk_buff *bnxt_gro_func_5730x(काष्ठा bnxt_tpa_info *tpa_info,
					   पूर्णांक payload_off, पूर्णांक tcp_ts,
					   काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	काष्ठा tcphdr *th;
	पूर्णांक len, nw_off, tcp_opt_len = 0;

	अगर (tcp_ts)
		tcp_opt_len = 12;

	अगर (tpa_info->gso_type == SKB_GSO_TCPV4) अणु
		काष्ठा iphdr *iph;

		nw_off = payload_off - BNXT_IPV4_HDR_SIZE - tcp_opt_len -
			 ETH_HLEN;
		skb_set_network_header(skb, nw_off);
		iph = ip_hdr(skb);
		skb_set_transport_header(skb, nw_off + माप(काष्ठा iphdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v4_check(len, iph->saddr, iph->daddr, 0);
	पूर्ण अन्यथा अगर (tpa_info->gso_type == SKB_GSO_TCPV6) अणु
		काष्ठा ipv6hdr *iph;

		nw_off = payload_off - BNXT_IPV6_HDR_SIZE - tcp_opt_len -
			 ETH_HLEN;
		skb_set_network_header(skb, nw_off);
		iph = ipv6_hdr(skb);
		skb_set_transport_header(skb, nw_off + माप(काष्ठा ipv6hdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v6_check(len, &iph->saddr, &iph->daddr, 0);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	अगर (nw_off) /* tunnel */
		bnxt_gro_tunnel(skb, skb->protocol);
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *bnxt_gro_skb(काष्ठा bnxt *bp,
					   काष्ठा bnxt_tpa_info *tpa_info,
					   काष्ठा rx_tpa_end_cmp *tpa_end,
					   काष्ठा rx_tpa_end_cmp_ext *tpa_end1,
					   काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	पूर्णांक payload_off;
	u16 segs;

	segs = TPA_END_TPA_SEGS(tpa_end);
	अगर (segs == 1)
		वापस skb;

	NAPI_GRO_CB(skb)->count = segs;
	skb_shinfo(skb)->gso_size =
		le32_to_cpu(tpa_end1->rx_tpa_end_cmp_seg_len);
	skb_shinfo(skb)->gso_type = tpa_info->gso_type;
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		payload_off = TPA_END_PAYLOAD_OFF_P5(tpa_end1);
	अन्यथा
		payload_off = TPA_END_PAYLOAD_OFF(tpa_end);
	skb = bp->gro_func(tpa_info, payload_off, TPA_END_GRO_TS(tpa_end), skb);
	अगर (likely(skb))
		tcp_gro_complete(skb);
#पूर्ण_अगर
	वापस skb;
पूर्ण

/* Given the cfa_code of a received packet determine which
 * netdev (vf-rep or PF) the packet is destined to.
 */
अटल काष्ठा net_device *bnxt_get_pkt_dev(काष्ठा bnxt *bp, u16 cfa_code)
अणु
	काष्ठा net_device *dev = bnxt_get_vf_rep(bp, cfa_code);

	/* अगर vf-rep dev is शून्य, the must beदीर्घs to the PF */
	वापस dev ? dev : bp->dev;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *bnxt_tpa_end(काष्ठा bnxt *bp,
					   काष्ठा bnxt_cp_ring_info *cpr,
					   u32 *raw_cons,
					   काष्ठा rx_tpa_end_cmp *tpa_end,
					   काष्ठा rx_tpa_end_cmp_ext *tpa_end1,
					   u8 *event)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u8 *data_ptr, agg_bufs;
	अचिन्हित पूर्णांक len;
	काष्ठा bnxt_tpa_info *tpa_info;
	dma_addr_t mapping;
	काष्ठा sk_buff *skb;
	u16 idx = 0, agg_id;
	व्योम *data;
	bool gro;

	अगर (unlikely(bnapi->in_reset)) अणु
		पूर्णांक rc = bnxt_discard_rx(bp, cpr, raw_cons, tpa_end);

		अगर (rc < 0)
			वापस ERR_PTR(-EBUSY);
		वापस शून्य;
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		agg_id = TPA_END_AGG_ID_P5(tpa_end);
		agg_id = bnxt_lookup_agg_idx(rxr, agg_id);
		agg_bufs = TPA_END_AGG_BUFS_P5(tpa_end1);
		tpa_info = &rxr->rx_tpa[agg_id];
		अगर (unlikely(agg_bufs != tpa_info->agg_count)) अणु
			netdev_warn(bp->dev, "TPA end agg_buf %d != expected agg_bufs %d\n",
				    agg_bufs, tpa_info->agg_count);
			agg_bufs = tpa_info->agg_count;
		पूर्ण
		tpa_info->agg_count = 0;
		*event |= BNXT_AGG_EVENT;
		bnxt_मुक्त_agg_idx(rxr, agg_id);
		idx = agg_id;
		gro = !!(bp->flags & BNXT_FLAG_GRO);
	पूर्ण अन्यथा अणु
		agg_id = TPA_END_AGG_ID(tpa_end);
		agg_bufs = TPA_END_AGG_BUFS(tpa_end);
		tpa_info = &rxr->rx_tpa[agg_id];
		idx = RING_CMP(*raw_cons);
		अगर (agg_bufs) अणु
			अगर (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, raw_cons))
				वापस ERR_PTR(-EBUSY);

			*event |= BNXT_AGG_EVENT;
			idx = NEXT_CMP(idx);
		पूर्ण
		gro = !!TPA_END_GRO(tpa_end);
	पूर्ण
	data = tpa_info->data;
	data_ptr = tpa_info->data_ptr;
	prefetch(data_ptr);
	len = tpa_info->len;
	mapping = tpa_info->mapping;

	अगर (unlikely(agg_bufs > MAX_SKB_FRAGS || TPA_END_ERRORS(tpa_end1))) अणु
		bnxt_पात_tpa(cpr, idx, agg_bufs);
		अगर (agg_bufs > MAX_SKB_FRAGS)
			netdev_warn(bp->dev, "TPA frags %d exceeded MAX_SKB_FRAGS %d\n",
				    agg_bufs, (पूर्णांक)MAX_SKB_FRAGS);
		वापस शून्य;
	पूर्ण

	अगर (len <= bp->rx_copy_thresh) अणु
		skb = bnxt_copy_skb(bnapi, data_ptr, len, mapping);
		अगर (!skb) अणु
			bnxt_पात_tpa(cpr, idx, agg_bufs);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 *new_data;
		dma_addr_t new_mapping;

		new_data = __bnxt_alloc_rx_data(bp, &new_mapping, GFP_ATOMIC);
		अगर (!new_data) अणु
			bnxt_पात_tpa(cpr, idx, agg_bufs);
			वापस शून्य;
		पूर्ण

		tpa_info->data = new_data;
		tpa_info->data_ptr = new_data + bp->rx_offset;
		tpa_info->mapping = new_mapping;

		skb = build_skb(data, 0);
		dma_unmap_single_attrs(&bp->pdev->dev, mapping,
				       bp->rx_buf_use_size, bp->rx_dir,
				       DMA_ATTR_WEAK_ORDERING);

		अगर (!skb) अणु
			kमुक्त(data);
			bnxt_पात_tpa(cpr, idx, agg_bufs);
			वापस शून्य;
		पूर्ण
		skb_reserve(skb, bp->rx_offset);
		skb_put(skb, len);
	पूर्ण

	अगर (agg_bufs) अणु
		skb = bnxt_rx_pages(bp, cpr, skb, idx, agg_bufs, true);
		अगर (!skb) अणु
			/* Page reuse alपढ़ोy handled by bnxt_rx_pages(). */
			वापस शून्य;
		पूर्ण
	पूर्ण

	skb->protocol =
		eth_type_trans(skb, bnxt_get_pkt_dev(bp, tpa_info->cfa_code));

	अगर (tpa_info->hash_type != PKT_HASH_TYPE_NONE)
		skb_set_hash(skb, tpa_info->rss_hash, tpa_info->hash_type);

	अगर ((tpa_info->flags2 & RX_CMP_FLAGS2_META_FORMAT_VLAN) &&
	    (skb->dev->features & BNXT_HW_FEATURE_VLAN_ALL_RX)) अणु
		u16 vlan_proto = tpa_info->metadata >>
			RX_CMP_FLAGS2_METADATA_TPID_SFT;
		u16 vtag = tpa_info->metadata & RX_CMP_FLAGS2_METADATA_TCI_MASK;

		__vlan_hwaccel_put_tag(skb, htons(vlan_proto), vtag);
	पूर्ण

	skb_checksum_none_निश्चित(skb);
	अगर (likely(tpa_info->flags2 & RX_TPA_START_CMP_FLAGS2_L4_CS_CALC)) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->csum_level =
			(tpa_info->flags2 & RX_CMP_FLAGS2_T_L4_CS_CALC) >> 3;
	पूर्ण

	अगर (gro)
		skb = bnxt_gro_skb(bp, tpa_info, tpa_end, tpa_end1, skb);

	वापस skb;
पूर्ण

अटल व्योम bnxt_tpa_agg(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr,
			 काष्ठा rx_agg_cmp *rx_agg)
अणु
	u16 agg_id = TPA_AGG_AGG_ID(rx_agg);
	काष्ठा bnxt_tpa_info *tpa_info;

	agg_id = bnxt_lookup_agg_idx(rxr, agg_id);
	tpa_info = &rxr->rx_tpa[agg_id];
	BUG_ON(tpa_info->agg_count >= MAX_SKB_FRAGS);
	tpa_info->agg_arr[tpa_info->agg_count++] = *rx_agg;
पूर्ण

अटल व्योम bnxt_deliver_skb(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi,
			     काष्ठा sk_buff *skb)
अणु
	अगर (skb->dev != bp->dev) अणु
		/* this packet beदीर्घs to a vf-rep */
		bnxt_vf_rep_rx(bp, skb);
		वापस;
	पूर्ण
	skb_record_rx_queue(skb, bnapi->index);
	napi_gro_receive(&bnapi->napi, skb);
पूर्ण

/* वापसs the following:
 * 1       - 1 packet successfully received
 * 0       - successful TPA_START, packet not completed yet
 * -EBUSY  - completion ring करोes not have all the agg buffers yet
 * -ENOMEM - packet पातed due to out of memory
 * -EIO    - packet पातed due to hw error indicated in BD
 */
अटल पूर्णांक bnxt_rx_pkt(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
		       u32 *raw_cons, u8 *event)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	काष्ठा net_device *dev = bp->dev;
	काष्ठा rx_cmp *rxcmp;
	काष्ठा rx_cmp_ext *rxcmp1;
	u32 पंचांगp_raw_cons = *raw_cons;
	u16 cfa_code, cons, prod, cp_cons = RING_CMP(पंचांगp_raw_cons);
	काष्ठा bnxt_sw_rx_bd *rx_buf;
	अचिन्हित पूर्णांक len;
	u8 *data_ptr, agg_bufs, cmp_type;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	व्योम *data;
	पूर्णांक rc = 0;
	u32 misc;

	rxcmp = (काष्ठा rx_cmp *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	cmp_type = RX_CMP_TYPE(rxcmp);

	अगर (cmp_type == CMP_TYPE_RX_TPA_AGG_CMP) अणु
		bnxt_tpa_agg(bp, rxr, (काष्ठा rx_agg_cmp *)rxcmp);
		जाओ next_rx_no_prod_no_len;
	पूर्ण

	पंचांगp_raw_cons = NEXT_RAW_CMP(पंचांगp_raw_cons);
	cp_cons = RING_CMP(पंचांगp_raw_cons);
	rxcmp1 = (काष्ठा rx_cmp_ext *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	अगर (!RX_CMP_VALID(rxcmp1, पंचांगp_raw_cons))
		वापस -EBUSY;

	prod = rxr->rx_prod;

	अगर (cmp_type == CMP_TYPE_RX_L2_TPA_START_CMP) अणु
		bnxt_tpa_start(bp, rxr, (काष्ठा rx_tpa_start_cmp *)rxcmp,
			       (काष्ठा rx_tpa_start_cmp_ext *)rxcmp1);

		*event |= BNXT_RX_EVENT;
		जाओ next_rx_no_prod_no_len;

	पूर्ण अन्यथा अगर (cmp_type == CMP_TYPE_RX_L2_TPA_END_CMP) अणु
		skb = bnxt_tpa_end(bp, cpr, &पंचांगp_raw_cons,
				   (काष्ठा rx_tpa_end_cmp *)rxcmp,
				   (काष्ठा rx_tpa_end_cmp_ext *)rxcmp1, event);

		अगर (IS_ERR(skb))
			वापस -EBUSY;

		rc = -ENOMEM;
		अगर (likely(skb)) अणु
			bnxt_deliver_skb(bp, bnapi, skb);
			rc = 1;
		पूर्ण
		*event |= BNXT_RX_EVENT;
		जाओ next_rx_no_prod_no_len;
	पूर्ण

	cons = rxcmp->rx_cmp_opaque;
	अगर (unlikely(cons != rxr->rx_next_cons)) अणु
		पूर्णांक rc1 = bnxt_discard_rx(bp, cpr, &पंचांगp_raw_cons, rxcmp);

		/* 0xffff is क्रमced error, करोn't prपूर्णांक it */
		अगर (rxr->rx_next_cons != 0xffff)
			netdev_warn(bp->dev, "RX cons %x != expected cons %x\n",
				    cons, rxr->rx_next_cons);
		bnxt_sched_reset(bp, rxr);
		अगर (rc1)
			वापस rc1;
		जाओ next_rx_no_prod_no_len;
	पूर्ण
	rx_buf = &rxr->rx_buf_ring[cons];
	data = rx_buf->data;
	data_ptr = rx_buf->data_ptr;
	prefetch(data_ptr);

	misc = le32_to_cpu(rxcmp->rx_cmp_misc_v1);
	agg_bufs = (misc & RX_CMP_AGG_BUFS) >> RX_CMP_AGG_BUFS_SHIFT;

	अगर (agg_bufs) अणु
		अगर (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, &पंचांगp_raw_cons))
			वापस -EBUSY;

		cp_cons = NEXT_CMP(cp_cons);
		*event |= BNXT_AGG_EVENT;
	पूर्ण
	*event |= BNXT_RX_EVENT;

	rx_buf->data = शून्य;
	अगर (rxcmp1->rx_cmp_cfa_code_errors_v2 & RX_CMP_L2_ERRORS) अणु
		u32 rx_err = le32_to_cpu(rxcmp1->rx_cmp_cfa_code_errors_v2);

		bnxt_reuse_rx_data(rxr, cons, data);
		अगर (agg_bufs)
			bnxt_reuse_rx_agg_bufs(cpr, cp_cons, 0, agg_bufs,
					       false);

		rc = -EIO;
		अगर (rx_err & RX_CMPL_ERRORS_BUFFER_ERROR_MASK) अणु
			bnapi->cp_ring.sw_stats.rx.rx_buf_errors++;
			अगर (!(bp->flags & BNXT_FLAG_CHIP_P5) &&
			    !(bp->fw_cap & BNXT_FW_CAP_RING_MONITOR)) अणु
				netdev_warn_once(bp->dev, "RX buffer error %x\n",
						 rx_err);
				bnxt_sched_reset(bp, rxr);
			पूर्ण
		पूर्ण
		जाओ next_rx_no_len;
	पूर्ण

	len = le32_to_cpu(rxcmp->rx_cmp_len_flags_type) >> RX_CMP_LEN_SHIFT;
	dma_addr = rx_buf->mapping;

	अगर (bnxt_rx_xdp(bp, rxr, cons, data, &data_ptr, &len, event)) अणु
		rc = 1;
		जाओ next_rx;
	पूर्ण

	अगर (len <= bp->rx_copy_thresh) अणु
		skb = bnxt_copy_skb(bnapi, data_ptr, len, dma_addr);
		bnxt_reuse_rx_data(rxr, cons, data);
		अगर (!skb) अणु
			अगर (agg_bufs)
				bnxt_reuse_rx_agg_bufs(cpr, cp_cons, 0,
						       agg_bufs, false);
			rc = -ENOMEM;
			जाओ next_rx;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 payload;

		अगर (rx_buf->data_ptr == data_ptr)
			payload = misc & RX_CMP_PAYLOAD_OFFSET;
		अन्यथा
			payload = 0;
		skb = bp->rx_skb_func(bp, rxr, cons, data, data_ptr, dma_addr,
				      payload | len);
		अगर (!skb) अणु
			rc = -ENOMEM;
			जाओ next_rx;
		पूर्ण
	पूर्ण

	अगर (agg_bufs) अणु
		skb = bnxt_rx_pages(bp, cpr, skb, cp_cons, agg_bufs, false);
		अगर (!skb) अणु
			rc = -ENOMEM;
			जाओ next_rx;
		पूर्ण
	पूर्ण

	अगर (RX_CMP_HASH_VALID(rxcmp)) अणु
		u32 hash_type = RX_CMP_HASH_TYPE(rxcmp);
		क्रमागत pkt_hash_types type = PKT_HASH_TYPE_L4;

		/* RSS profiles 1 and 3 with extract code 0 क्रम inner 4-tuple */
		अगर (hash_type != 1 && hash_type != 3)
			type = PKT_HASH_TYPE_L3;
		skb_set_hash(skb, le32_to_cpu(rxcmp->rx_cmp_rss_hash), type);
	पूर्ण

	cfa_code = RX_CMP_CFA_CODE(rxcmp1);
	skb->protocol = eth_type_trans(skb, bnxt_get_pkt_dev(bp, cfa_code));

	अगर ((rxcmp1->rx_cmp_flags2 &
	     cpu_to_le32(RX_CMP_FLAGS2_META_FORMAT_VLAN)) &&
	    (skb->dev->features & BNXT_HW_FEATURE_VLAN_ALL_RX)) अणु
		u32 meta_data = le32_to_cpu(rxcmp1->rx_cmp_meta_data);
		u16 vtag = meta_data & RX_CMP_FLAGS2_METADATA_TCI_MASK;
		u16 vlan_proto = meta_data >> RX_CMP_FLAGS2_METADATA_TPID_SFT;

		__vlan_hwaccel_put_tag(skb, htons(vlan_proto), vtag);
	पूर्ण

	skb_checksum_none_निश्चित(skb);
	अगर (RX_CMP_L4_CS_OK(rxcmp1)) अणु
		अगर (dev->features & NETIF_F_RXCSUM) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum_level = RX_CMP_ENCAP(rxcmp1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rxcmp1->rx_cmp_cfa_code_errors_v2 & RX_CMP_L4_CS_ERR_BITS) अणु
			अगर (dev->features & NETIF_F_RXCSUM)
				bnapi->cp_ring.sw_stats.rx.rx_l4_csum_errors++;
		पूर्ण
	पूर्ण

	bnxt_deliver_skb(bp, bnapi, skb);
	rc = 1;

next_rx:
	cpr->rx_packets += 1;
	cpr->rx_bytes += len;

next_rx_no_len:
	rxr->rx_prod = NEXT_RX(prod);
	rxr->rx_next_cons = NEXT_RX(cons);

next_rx_no_prod_no_len:
	*raw_cons = पंचांगp_raw_cons;

	वापस rc;
पूर्ण

/* In netpoll mode, अगर we are using a combined completion ring, we need to
 * discard the rx packets and recycle the buffers.
 */
अटल पूर्णांक bnxt_क्रमce_rx_discard(काष्ठा bnxt *bp,
				 काष्ठा bnxt_cp_ring_info *cpr,
				 u32 *raw_cons, u8 *event)
अणु
	u32 पंचांगp_raw_cons = *raw_cons;
	काष्ठा rx_cmp_ext *rxcmp1;
	काष्ठा rx_cmp *rxcmp;
	u16 cp_cons;
	u8 cmp_type;

	cp_cons = RING_CMP(पंचांगp_raw_cons);
	rxcmp = (काष्ठा rx_cmp *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	पंचांगp_raw_cons = NEXT_RAW_CMP(पंचांगp_raw_cons);
	cp_cons = RING_CMP(पंचांगp_raw_cons);
	rxcmp1 = (काष्ठा rx_cmp_ext *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	अगर (!RX_CMP_VALID(rxcmp1, पंचांगp_raw_cons))
		वापस -EBUSY;

	cmp_type = RX_CMP_TYPE(rxcmp);
	अगर (cmp_type == CMP_TYPE_RX_L2_CMP) अणु
		rxcmp1->rx_cmp_cfa_code_errors_v2 |=
			cpu_to_le32(RX_CMPL_ERRORS_CRC_ERROR);
	पूर्ण अन्यथा अगर (cmp_type == CMP_TYPE_RX_L2_TPA_END_CMP) अणु
		काष्ठा rx_tpa_end_cmp_ext *tpa_end1;

		tpa_end1 = (काष्ठा rx_tpa_end_cmp_ext *)rxcmp1;
		tpa_end1->rx_tpa_end_cmp_errors_v2 |=
			cpu_to_le32(RX_TPA_END_CMP_ERRORS);
	पूर्ण
	वापस bnxt_rx_pkt(bp, cpr, raw_cons, event);
पूर्ण

u32 bnxt_fw_health_पढ़ोl(काष्ठा bnxt *bp, पूर्णांक reg_idx)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg = fw_health->regs[reg_idx];
	u32 reg_type, reg_off, val = 0;

	reg_type = BNXT_FW_HEALTH_REG_TYPE(reg);
	reg_off = BNXT_FW_HEALTH_REG_OFF(reg);
	चयन (reg_type) अणु
	हाल BNXT_FW_HEALTH_REG_TYPE_CFG:
		pci_पढ़ो_config_dword(bp->pdev, reg_off, &val);
		अवरोध;
	हाल BNXT_FW_HEALTH_REG_TYPE_GRC:
		reg_off = fw_health->mapped_regs[reg_idx];
		fallthrough;
	हाल BNXT_FW_HEALTH_REG_TYPE_BAR0:
		val = पढ़ोl(bp->bar0 + reg_off);
		अवरोध;
	हाल BNXT_FW_HEALTH_REG_TYPE_BAR1:
		val = पढ़ोl(bp->bar1 + reg_off);
		अवरोध;
	पूर्ण
	अगर (reg_idx == BNXT_FW_RESET_INPROG_REG)
		val &= fw_health->fw_reset_inprog_reg_mask;
	वापस val;
पूर्ण

अटल u16 bnxt_agg_ring_id_to_grp_idx(काष्ठा bnxt *bp, u16 ring_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		u16 grp_idx = bp->rx_ring[i].bnapi->index;
		काष्ठा bnxt_ring_grp_info *grp_info;

		grp_info = &bp->grp_info[grp_idx];
		अगर (grp_info->agg_fw_ring_id == ring_id)
			वापस grp_idx;
	पूर्ण
	वापस INVALID_HW_RING_ID;
पूर्ण

#घोषणा BNXT_GET_EVENT_PORT(data)	\
	((data) &			\
	 ASYNC_EVENT_CMPL_PORT_CONN_NOT_ALLOWED_EVENT_DATA1_PORT_ID_MASK)

#घोषणा BNXT_EVENT_RING_TYPE(data2)	\
	((data2) &			\
	 ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_MASK)

#घोषणा BNXT_EVENT_RING_TYPE_RX(data2)	\
	(BNXT_EVENT_RING_TYPE(data2) ==	\
	 ASYNC_EVENT_CMPL_RING_MONITOR_MSG_EVENT_DATA2_DISABLE_RING_TYPE_RX)

अटल पूर्णांक bnxt_async_event_process(काष्ठा bnxt *bp,
				    काष्ठा hwrm_async_event_cmpl *cmpl)
अणु
	u16 event_id = le16_to_cpu(cmpl->event_id);
	u32 data1 = le32_to_cpu(cmpl->event_data1);
	u32 data2 = le32_to_cpu(cmpl->event_data2);

	/* TODO CHIMP_FW: Define event id's क्रम link change, error etc */
	चयन (event_id) अणु
	हाल ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE: अणु
		काष्ठा bnxt_link_info *link_info = &bp->link_info;

		अगर (BNXT_VF(bp))
			जाओ async_event_process_निकास;

		/* prपूर्णांक unsupported speed warning in क्रमced speed mode only */
		अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED) &&
		    (data1 & 0x20000)) अणु
			u16 fw_speed = link_info->क्रमce_link_speed;
			u32 speed = bnxt_fw_to_ethtool_speed(fw_speed);

			अगर (speed != SPEED_UNKNOWN)
				netdev_warn(bp->dev, "Link speed %d no longer supported\n",
					    speed);
		पूर्ण
		set_bit(BNXT_LINK_SPEED_CHNG_SP_EVENT, &bp->sp_event);
	पूर्ण
		fallthrough;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CHANGE:
	हाल ASYNC_EVENT_CMPL_EVENT_ID_PORT_PHY_CFG_CHANGE:
		set_bit(BNXT_LINK_CFG_CHANGE_SP_EVENT, &bp->sp_event);
		fallthrough;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE:
		set_bit(BNXT_LINK_CHNG_SP_EVENT, &bp->sp_event);
		अवरोध;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD:
		set_bit(BNXT_HWRM_PF_UNLOAD_SP_EVENT, &bp->sp_event);
		अवरोध;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED: अणु
		u16 port_id = BNXT_GET_EVENT_PORT(data1);

		अगर (BNXT_VF(bp))
			अवरोध;

		अगर (bp->pf.port_id != port_id)
			अवरोध;

		set_bit(BNXT_HWRM_PORT_MODULE_SP_EVENT, &bp->sp_event);
		अवरोध;
	पूर्ण
	हाल ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE:
		अगर (BNXT_PF(bp))
			जाओ async_event_process_निकास;
		set_bit(BNXT_RESET_TASK_SILENT_SP_EVENT, &bp->sp_event);
		अवरोध;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_RESET_NOTIFY: अणु
		अक्षर *fatal_str = "non-fatal";

		अगर (!bp->fw_health)
			जाओ async_event_process_निकास;

		bp->fw_reset_बारtamp = jअगरfies;
		bp->fw_reset_min_dsecs = cmpl->बारtamp_lo;
		अगर (!bp->fw_reset_min_dsecs)
			bp->fw_reset_min_dsecs = BNXT_DFLT_FW_RST_MIN_DSECS;
		bp->fw_reset_max_dsecs = le16_to_cpu(cmpl->बारtamp_hi);
		अगर (!bp->fw_reset_max_dsecs)
			bp->fw_reset_max_dsecs = BNXT_DFLT_FW_RST_MAX_DSECS;
		अगर (EVENT_DATA1_RESET_NOTIFY_FATAL(data1)) अणु
			fatal_str = "fatal";
			set_bit(BNXT_STATE_FW_FATAL_COND, &bp->state);
		पूर्ण
		netअगर_warn(bp, hw, bp->dev,
			   "Firmware %s reset event, data1: 0x%x, data2: 0x%x, min wait %u ms, max wait %u ms\n",
			   fatal_str, data1, data2,
			   bp->fw_reset_min_dsecs * 100,
			   bp->fw_reset_max_dsecs * 100);
		set_bit(BNXT_FW_RESET_NOTIFY_SP_EVENT, &bp->sp_event);
		अवरोध;
	पूर्ण
	हाल ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY: अणु
		काष्ठा bnxt_fw_health *fw_health = bp->fw_health;

		अगर (!fw_health)
			जाओ async_event_process_निकास;

		fw_health->enabled = EVENT_DATA1_RECOVERY_ENABLED(data1);
		fw_health->master = EVENT_DATA1_RECOVERY_MASTER_FUNC(data1);
		अगर (!fw_health->enabled) अणु
			netअगर_info(bp, drv, bp->dev,
				   "Error recovery info: error recovery[0]\n");
			अवरोध;
		पूर्ण
		fw_health->पंचांगr_multiplier =
			DIV_ROUND_UP(fw_health->polling_dsecs * HZ,
				     bp->current_पूर्णांकerval * 10);
		fw_health->पंचांगr_counter = fw_health->पंचांगr_multiplier;
		fw_health->last_fw_heartbeat =
			bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEARTBEAT_REG);
		fw_health->last_fw_reset_cnt =
			bnxt_fw_health_पढ़ोl(bp, BNXT_FW_RESET_CNT_REG);
		netअगर_info(bp, drv, bp->dev,
			   "Error recovery info: error recovery[1], master[%d], reset count[%u], health status: 0x%x\n",
			   fw_health->master, fw_health->last_fw_reset_cnt,
			   bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG));
		जाओ async_event_process_निकास;
	पूर्ण
	हाल ASYNC_EVENT_CMPL_EVENT_ID_DEBUG_NOTIFICATION:
		netअगर_notice(bp, hw, bp->dev,
			     "Received firmware debug notification, data1: 0x%x, data2: 0x%x\n",
			     data1, data2);
		जाओ async_event_process_निकास;
	हाल ASYNC_EVENT_CMPL_EVENT_ID_RING_MONITOR_MSG: अणु
		काष्ठा bnxt_rx_ring_info *rxr;
		u16 grp_idx;

		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			जाओ async_event_process_निकास;

		netdev_warn(bp->dev, "Ring monitor event, ring type %lu id 0x%x\n",
			    BNXT_EVENT_RING_TYPE(data2), data1);
		अगर (!BNXT_EVENT_RING_TYPE_RX(data2))
			जाओ async_event_process_निकास;

		grp_idx = bnxt_agg_ring_id_to_grp_idx(bp, data1);
		अगर (grp_idx == INVALID_HW_RING_ID) अणु
			netdev_warn(bp->dev, "Unknown RX agg ring id 0x%x\n",
				    data1);
			जाओ async_event_process_निकास;
		पूर्ण
		rxr = bp->bnapi[grp_idx]->rx_ring;
		bnxt_sched_reset(bp, rxr);
		जाओ async_event_process_निकास;
	पूर्ण
	हाल ASYNC_EVENT_CMPL_EVENT_ID_ECHO_REQUEST: अणु
		काष्ठा bnxt_fw_health *fw_health = bp->fw_health;

		netअगर_notice(bp, hw, bp->dev,
			     "Received firmware echo request, data1: 0x%x, data2: 0x%x\n",
			     data1, data2);
		अगर (fw_health) अणु
			fw_health->echo_req_data1 = data1;
			fw_health->echo_req_data2 = data2;
			set_bit(BNXT_FW_ECHO_REQUEST_SP_EVENT, &bp->sp_event);
			अवरोध;
		पूर्ण
		जाओ async_event_process_निकास;
	पूर्ण
	शेष:
		जाओ async_event_process_निकास;
	पूर्ण
	bnxt_queue_sp_work(bp);
async_event_process_निकास:
	bnxt_ulp_async_events(bp, cmpl);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_handler(काष्ठा bnxt *bp, काष्ठा tx_cmp *txcmp)
अणु
	u16 cmpl_type = TX_CMP_TYPE(txcmp), vf_id, seq_id;
	काष्ठा hwrm_cmpl *h_cmpl = (काष्ठा hwrm_cmpl *)txcmp;
	काष्ठा hwrm_fwd_req_cmpl *fwd_req_cmpl =
				(काष्ठा hwrm_fwd_req_cmpl *)txcmp;

	चयन (cmpl_type) अणु
	हाल CMPL_BASE_TYPE_HWRM_DONE:
		seq_id = le16_to_cpu(h_cmpl->sequence_id);
		अगर (seq_id == bp->hwrm_पूर्णांकr_seq_id)
			bp->hwrm_पूर्णांकr_seq_id = (u16)~bp->hwrm_पूर्णांकr_seq_id;
		अन्यथा
			netdev_err(bp->dev, "Invalid hwrm seq id %d\n", seq_id);
		अवरोध;

	हाल CMPL_BASE_TYPE_HWRM_FWD_REQ:
		vf_id = le16_to_cpu(fwd_req_cmpl->source_id);

		अगर ((vf_id < bp->pf.first_vf_id) ||
		    (vf_id >= bp->pf.first_vf_id + bp->pf.active_vfs)) अणु
			netdev_err(bp->dev, "Msg contains invalid VF id %x\n",
				   vf_id);
			वापस -EINVAL;
		पूर्ण

		set_bit(vf_id - bp->pf.first_vf_id, bp->pf.vf_event_bmap);
		set_bit(BNXT_HWRM_EXEC_FWD_REQ_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
		अवरोध;

	हाल CMPL_BASE_TYPE_HWRM_ASYNC_EVENT:
		bnxt_async_event_process(bp,
					 (काष्ठा hwrm_async_event_cmpl *)txcmp);

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t bnxt_msix(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnxt_napi *bnapi = dev_instance;
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	u32 cons = RING_CMP(cpr->cp_raw_cons);

	cpr->event_ctr++;
	prefetch(&cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)]);
	napi_schedule(&bnapi->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत पूर्णांक bnxt_has_work(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr)
अणु
	u32 raw_cons = cpr->cp_raw_cons;
	u16 cons = RING_CMP(raw_cons);
	काष्ठा tx_cmp *txcmp;

	txcmp = &cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)];

	वापस TX_CMP_VALID(txcmp, raw_cons);
पूर्ण

अटल irqवापस_t bnxt_पूर्णांकa(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnxt_napi *bnapi = dev_instance;
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	u32 cons = RING_CMP(cpr->cp_raw_cons);
	u32 पूर्णांक_status;

	prefetch(&cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)]);

	अगर (!bnxt_has_work(bp, cpr)) अणु
		पूर्णांक_status = पढ़ोl(bp->bar0 + BNXT_CAG_REG_LEGACY_INT_STATUS);
		/* वापस अगर erroneous पूर्णांकerrupt */
		अगर (!(पूर्णांक_status & (0x10000 << cpr->cp_ring_काष्ठा.fw_ring_id)))
			वापस IRQ_NONE;
	पूर्ण

	/* disable ring IRQ */
	BNXT_CP_DB_IRQ_DIS(cpr->cp_db.करोorbell);

	/* Return here अगर पूर्णांकerrupt is shared and is disabled. */
	अगर (unlikely(atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0))
		वापस IRQ_HANDLED;

	napi_schedule(&bnapi->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __bnxt_poll_work(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			    पूर्णांक budget)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	u32 raw_cons = cpr->cp_raw_cons;
	u32 cons;
	पूर्णांक tx_pkts = 0;
	पूर्णांक rx_pkts = 0;
	u8 event = 0;
	काष्ठा tx_cmp *txcmp;

	cpr->has_more_work = 0;
	cpr->had_work_करोne = 1;
	जबतक (1) अणु
		पूर्णांक rc;

		cons = RING_CMP(raw_cons);
		txcmp = &cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)];

		अगर (!TX_CMP_VALID(txcmp, raw_cons))
			अवरोध;

		/* The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();
		अगर (TX_CMP_TYPE(txcmp) == CMP_TYPE_TX_L2_CMP) अणु
			tx_pkts++;
			/* वापस full budget so NAPI will complete. */
			अगर (unlikely(tx_pkts > bp->tx_wake_thresh)) अणु
				rx_pkts = budget;
				raw_cons = NEXT_RAW_CMP(raw_cons);
				अगर (budget)
					cpr->has_more_work = 1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((TX_CMP_TYPE(txcmp) & 0x30) == 0x10) अणु
			अगर (likely(budget))
				rc = bnxt_rx_pkt(bp, cpr, &raw_cons, &event);
			अन्यथा
				rc = bnxt_क्रमce_rx_discard(bp, cpr, &raw_cons,
							   &event);
			अगर (likely(rc >= 0))
				rx_pkts += rc;
			/* Increment rx_pkts when rc is -ENOMEM to count towards
			 * the NAPI budget.  Otherwise, we may potentially loop
			 * here क्रमever अगर we consistently cannot allocate
			 * buffers.
			 */
			अन्यथा अगर (rc == -ENOMEM && budget)
				rx_pkts++;
			अन्यथा अगर (rc == -EBUSY)	/* partial completion */
				अवरोध;
		पूर्ण अन्यथा अगर (unlikely((TX_CMP_TYPE(txcmp) ==
				     CMPL_BASE_TYPE_HWRM_DONE) ||
				    (TX_CMP_TYPE(txcmp) ==
				     CMPL_BASE_TYPE_HWRM_FWD_REQ) ||
				    (TX_CMP_TYPE(txcmp) ==
				     CMPL_BASE_TYPE_HWRM_ASYNC_EVENT))) अणु
			bnxt_hwrm_handler(bp, txcmp);
		पूर्ण
		raw_cons = NEXT_RAW_CMP(raw_cons);

		अगर (rx_pkts && rx_pkts == budget) अणु
			cpr->has_more_work = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (event & BNXT_REसूचीECT_EVENT)
		xdp_करो_flush_map();

	अगर (event & BNXT_TX_EVENT) अणु
		काष्ठा bnxt_tx_ring_info *txr = bnapi->tx_ring;
		u16 prod = txr->tx_prod;

		/* Sync BD data beक्रमe updating करोorbell */
		wmb();

		bnxt_db_ग_लिखो_relaxed(bp, &txr->tx_db, prod);
	पूर्ण

	cpr->cp_raw_cons = raw_cons;
	bnapi->tx_pkts += tx_pkts;
	bnapi->events |= event;
	वापस rx_pkts;
पूर्ण

अटल व्योम __bnxt_poll_work_करोne(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi)
अणु
	अगर (bnapi->tx_pkts) अणु
		bnapi->tx_पूर्णांक(bp, bnapi, bnapi->tx_pkts);
		bnapi->tx_pkts = 0;
	पूर्ण

	अगर ((bnapi->events & BNXT_RX_EVENT) && !(bnapi->in_reset)) अणु
		काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;

		अगर (bnapi->events & BNXT_AGG_EVENT)
			bnxt_db_ग_लिखो(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);
		bnxt_db_ग_लिखो(bp, &rxr->rx_db, rxr->rx_prod);
	पूर्ण
	bnapi->events = 0;
पूर्ण

अटल पूर्णांक bnxt_poll_work(काष्ठा bnxt *bp, काष्ठा bnxt_cp_ring_info *cpr,
			  पूर्णांक budget)
अणु
	काष्ठा bnxt_napi *bnapi = cpr->bnapi;
	पूर्णांक rx_pkts;

	rx_pkts = __bnxt_poll_work(bp, cpr, budget);

	/* ACK completion ring beक्रमe मुक्तing tx ring and producing new
	 * buffers in rx/agg rings to prevent overflowing the completion
	 * ring.
	 */
	bnxt_db_cq(bp, &cpr->cp_db, cpr->cp_raw_cons);

	__bnxt_poll_work_करोne(bp, bnapi);
	वापस rx_pkts;
पूर्ण

अटल पूर्णांक bnxt_poll_nitroa0(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnxt_napi *bnapi = container_of(napi, काष्ठा bnxt_napi, napi);
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	काष्ठा tx_cmp *txcmp;
	काष्ठा rx_cmp_ext *rxcmp1;
	u32 cp_cons, पंचांगp_raw_cons;
	u32 raw_cons = cpr->cp_raw_cons;
	u32 rx_pkts = 0;
	u8 event = 0;

	जबतक (1) अणु
		पूर्णांक rc;

		cp_cons = RING_CMP(raw_cons);
		txcmp = &cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

		अगर (!TX_CMP_VALID(txcmp, raw_cons))
			अवरोध;

		अगर ((TX_CMP_TYPE(txcmp) & 0x30) == 0x10) अणु
			पंचांगp_raw_cons = NEXT_RAW_CMP(raw_cons);
			cp_cons = RING_CMP(पंचांगp_raw_cons);
			rxcmp1 = (काष्ठा rx_cmp_ext *)
			  &cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

			अगर (!RX_CMP_VALID(rxcmp1, पंचांगp_raw_cons))
				अवरोध;

			/* क्रमce an error to recycle the buffer */
			rxcmp1->rx_cmp_cfa_code_errors_v2 |=
				cpu_to_le32(RX_CMPL_ERRORS_CRC_ERROR);

			rc = bnxt_rx_pkt(bp, cpr, &raw_cons, &event);
			अगर (likely(rc == -EIO) && budget)
				rx_pkts++;
			अन्यथा अगर (rc == -EBUSY)	/* partial completion */
				अवरोध;
		पूर्ण अन्यथा अगर (unlikely(TX_CMP_TYPE(txcmp) ==
				    CMPL_BASE_TYPE_HWRM_DONE)) अणु
			bnxt_hwrm_handler(bp, txcmp);
		पूर्ण अन्यथा अणु
			netdev_err(bp->dev,
				   "Invalid completion received on special ring\n");
		पूर्ण
		raw_cons = NEXT_RAW_CMP(raw_cons);

		अगर (rx_pkts == budget)
			अवरोध;
	पूर्ण

	cpr->cp_raw_cons = raw_cons;
	BNXT_DB_CQ(&cpr->cp_db, cpr->cp_raw_cons);
	bnxt_db_ग_लिखो(bp, &rxr->rx_db, rxr->rx_prod);

	अगर (event & BNXT_AGG_EVENT)
		bnxt_db_ग_लिखो(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);

	अगर (!bnxt_has_work(bp, cpr) && rx_pkts < budget) अणु
		napi_complete_करोne(napi, rx_pkts);
		BNXT_DB_CQ_ARM(&cpr->cp_db, cpr->cp_raw_cons);
	पूर्ण
	वापस rx_pkts;
पूर्ण

अटल पूर्णांक bnxt_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnxt_napi *bnapi = container_of(napi, काष्ठा bnxt_napi, napi);
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	पूर्णांक work_करोne = 0;

	अगर (unlikely(test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण
	जबतक (1) अणु
		work_करोne += bnxt_poll_work(bp, cpr, budget - work_करोne);

		अगर (work_करोne >= budget) अणु
			अगर (!budget)
				BNXT_DB_CQ_ARM(&cpr->cp_db, cpr->cp_raw_cons);
			अवरोध;
		पूर्ण

		अगर (!bnxt_has_work(bp, cpr)) अणु
			अगर (napi_complete_करोne(napi, work_करोne))
				BNXT_DB_CQ_ARM(&cpr->cp_db, cpr->cp_raw_cons);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_DIM) अणु
		काष्ठा dim_sample dim_sample = अणुपूर्ण;

		dim_update_sample(cpr->event_ctr,
				  cpr->rx_packets,
				  cpr->rx_bytes,
				  &dim_sample);
		net_dim(&cpr->dim, dim_sample);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल पूर्णांक __bnxt_poll_cqs(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi, पूर्णांक budget)
अणु
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	पूर्णांक i, work_करोne = 0;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[i];

		अगर (cpr2) अणु
			work_करोne += __bnxt_poll_work(bp, cpr2,
						      budget - work_करोne);
			cpr->has_more_work |= cpr2->has_more_work;
		पूर्ण
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम __bnxt_poll_cqs_करोne(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi,
				 u64 dbr_type)
अणु
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[i];
		काष्ठा bnxt_db_info *db;

		अगर (cpr2 && cpr2->had_work_करोne) अणु
			db = &cpr2->cp_db;
			ग_लिखोq(db->db_key64 | dbr_type |
			       RING_CMP(cpr2->cp_raw_cons), db->करोorbell);
			cpr2->had_work_करोne = 0;
		पूर्ण
	पूर्ण
	__bnxt_poll_work_करोne(bp, bnapi);
पूर्ण

अटल पूर्णांक bnxt_poll_p5(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnxt_napi *bnapi = container_of(napi, काष्ठा bnxt_napi, napi);
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	u32 raw_cons = cpr->cp_raw_cons;
	काष्ठा bnxt *bp = bnapi->bp;
	काष्ठा nqe_cn *nqcmp;
	पूर्णांक work_करोne = 0;
	u32 cons;

	अगर (unlikely(test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण
	अगर (cpr->has_more_work) अणु
		cpr->has_more_work = 0;
		work_करोne = __bnxt_poll_cqs(bp, bnapi, budget);
	पूर्ण
	जबतक (1) अणु
		cons = RING_CMP(raw_cons);
		nqcmp = &cpr->nq_desc_ring[CP_RING(cons)][CP_IDX(cons)];

		अगर (!NQ_CMP_VALID(nqcmp, raw_cons)) अणु
			अगर (cpr->has_more_work)
				अवरोध;

			__bnxt_poll_cqs_करोne(bp, bnapi, DBR_TYPE_CQ_ARMALL);
			cpr->cp_raw_cons = raw_cons;
			अगर (napi_complete_करोne(napi, work_करोne))
				BNXT_DB_NQ_ARM_P5(&cpr->cp_db,
						  cpr->cp_raw_cons);
			वापस work_करोne;
		पूर्ण

		/* The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();

		अगर (nqcmp->type == cpu_to_le16(NQ_CN_TYPE_CQ_NOTIFICATION)) अणु
			u32 idx = le32_to_cpu(nqcmp->cq_handle_low);
			काष्ठा bnxt_cp_ring_info *cpr2;

			cpr2 = cpr->cp_ring_arr[idx];
			work_करोne += __bnxt_poll_work(bp, cpr2,
						      budget - work_करोne);
			cpr->has_more_work |= cpr2->has_more_work;
		पूर्ण अन्यथा अणु
			bnxt_hwrm_handler(bp, (काष्ठा tx_cmp *)nqcmp);
		पूर्ण
		raw_cons = NEXT_RAW_CMP(raw_cons);
	पूर्ण
	__bnxt_poll_cqs_करोne(bp, bnapi, DBR_TYPE_CQ);
	अगर (raw_cons != cpr->cp_raw_cons) अणु
		cpr->cp_raw_cons = raw_cons;
		BNXT_DB_NQ_P5(&cpr->cp_db, raw_cons);
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल व्योम bnxt_मुक्त_tx_skbs(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, max_idx;
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (!bp->tx_ring)
		वापस;

	max_idx = bp->tx_nr_pages * TX_DESC_CNT;
	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		पूर्णांक j;

		क्रम (j = 0; j < max_idx;) अणु
			काष्ठा bnxt_sw_tx_bd *tx_buf = &txr->tx_buf_ring[j];
			काष्ठा sk_buff *skb;
			पूर्णांक k, last;

			अगर (i < bp->tx_nr_rings_xdp &&
			    tx_buf->action == XDP_REसूचीECT) अणु
				dma_unmap_single(&pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					dma_unmap_len(tx_buf, len),
					PCI_DMA_TODEVICE);
				xdp_वापस_frame(tx_buf->xdpf);
				tx_buf->action = 0;
				tx_buf->xdpf = शून्य;
				j++;
				जारी;
			पूर्ण

			skb = tx_buf->skb;
			अगर (!skb) अणु
				j++;
				जारी;
			पूर्ण

			tx_buf->skb = शून्य;

			अगर (tx_buf->is_push) अणु
				dev_kमुक्त_skb(skb);
				j += 2;
				जारी;
			पूर्ण

			dma_unmap_single(&pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 skb_headlen(skb),
					 PCI_DMA_TODEVICE);

			last = tx_buf->nr_frags;
			j += 2;
			क्रम (k = 0; k < last; k++, j++) अणु
				पूर्णांक ring_idx = j & bp->tx_ring_mask;
				skb_frag_t *frag = &skb_shinfo(skb)->frags[k];

				tx_buf = &txr->tx_buf_ring[ring_idx];
				dma_unmap_page(
					&pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					skb_frag_size(frag), PCI_DMA_TODEVICE);
			पूर्ण
			dev_kमुक्त_skb(skb);
		पूर्ण
		netdev_tx_reset_queue(netdev_get_tx_queue(bp->dev, i));
	पूर्ण
पूर्ण

अटल व्योम bnxt_मुक्त_one_rx_ring_skbs(काष्ठा bnxt *bp, पूर्णांक ring_nr)
अणु
	काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[ring_nr];
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा bnxt_tpa_idx_map *map;
	पूर्णांक i, max_idx, max_agg_idx;

	max_idx = bp->rx_nr_pages * RX_DESC_CNT;
	max_agg_idx = bp->rx_agg_nr_pages * RX_DESC_CNT;
	अगर (!rxr->rx_tpa)
		जाओ skip_rx_tpa_मुक्त;

	क्रम (i = 0; i < bp->max_tpa; i++) अणु
		काष्ठा bnxt_tpa_info *tpa_info = &rxr->rx_tpa[i];
		u8 *data = tpa_info->data;

		अगर (!data)
			जारी;

		dma_unmap_single_attrs(&pdev->dev, tpa_info->mapping,
				       bp->rx_buf_use_size, bp->rx_dir,
				       DMA_ATTR_WEAK_ORDERING);

		tpa_info->data = शून्य;

		kमुक्त(data);
	पूर्ण

skip_rx_tpa_मुक्त:
	क्रम (i = 0; i < max_idx; i++) अणु
		काष्ठा bnxt_sw_rx_bd *rx_buf = &rxr->rx_buf_ring[i];
		dma_addr_t mapping = rx_buf->mapping;
		व्योम *data = rx_buf->data;

		अगर (!data)
			जारी;

		rx_buf->data = शून्य;
		अगर (BNXT_RX_PAGE_MODE(bp)) अणु
			mapping -= bp->rx_dma_offset;
			dma_unmap_page_attrs(&pdev->dev, mapping, PAGE_SIZE,
					     bp->rx_dir,
					     DMA_ATTR_WEAK_ORDERING);
			page_pool_recycle_direct(rxr->page_pool, data);
		पूर्ण अन्यथा अणु
			dma_unmap_single_attrs(&pdev->dev, mapping,
					       bp->rx_buf_use_size, bp->rx_dir,
					       DMA_ATTR_WEAK_ORDERING);
			kमुक्त(data);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < max_agg_idx; i++) अणु
		काष्ठा bnxt_sw_rx_agg_bd *rx_agg_buf = &rxr->rx_agg_ring[i];
		काष्ठा page *page = rx_agg_buf->page;

		अगर (!page)
			जारी;

		dma_unmap_page_attrs(&pdev->dev, rx_agg_buf->mapping,
				     BNXT_RX_PAGE_SIZE, PCI_DMA_FROMDEVICE,
				     DMA_ATTR_WEAK_ORDERING);

		rx_agg_buf->page = शून्य;
		__clear_bit(i, rxr->rx_agg_bmap);

		__मुक्त_page(page);
	पूर्ण
	अगर (rxr->rx_page) अणु
		__मुक्त_page(rxr->rx_page);
		rxr->rx_page = शून्य;
	पूर्ण
	map = rxr->rx_tpa_idx_map;
	अगर (map)
		स_रखो(map->agg_idx_bmap, 0, माप(map->agg_idx_bmap));
पूर्ण

अटल व्योम bnxt_मुक्त_rx_skbs(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->rx_ring)
		वापस;

	क्रम (i = 0; i < bp->rx_nr_rings; i++)
		bnxt_मुक्त_one_rx_ring_skbs(bp, i);
पूर्ण

अटल व्योम bnxt_मुक्त_skbs(काष्ठा bnxt *bp)
अणु
	bnxt_मुक्त_tx_skbs(bp);
	bnxt_मुक्त_rx_skbs(bp);
पूर्ण

अटल व्योम bnxt_init_ctx_mem(काष्ठा bnxt_mem_init *mem_init, व्योम *p, पूर्णांक len)
अणु
	u8 init_val = mem_init->init_val;
	u16 offset = mem_init->offset;
	u8 *p2 = p;
	पूर्णांक i;

	अगर (!init_val)
		वापस;
	अगर (offset == BNXT_MEM_INVALID_OFFSET) अणु
		स_रखो(p, init_val, len);
		वापस;
	पूर्ण
	क्रम (i = 0; i < len; i += mem_init->size)
		*(p2 + i + offset) = init_val;
पूर्ण

अटल व्योम bnxt_मुक्त_ring(काष्ठा bnxt *bp, काष्ठा bnxt_ring_mem_info *rmem)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < rmem->nr_pages; i++) अणु
		अगर (!rmem->pg_arr[i])
			जारी;

		dma_मुक्त_coherent(&pdev->dev, rmem->page_size,
				  rmem->pg_arr[i], rmem->dma_arr[i]);

		rmem->pg_arr[i] = शून्य;
	पूर्ण
	अगर (rmem->pg_tbl) अणु
		माप_प्रकार pg_tbl_size = rmem->nr_pages * 8;

		अगर (rmem->flags & BNXT_RMEM_USE_FULL_PAGE_FLAG)
			pg_tbl_size = rmem->page_size;
		dma_मुक्त_coherent(&pdev->dev, pg_tbl_size,
				  rmem->pg_tbl, rmem->pg_tbl_map);
		rmem->pg_tbl = शून्य;
	पूर्ण
	अगर (rmem->vmem_size && *rmem->vmem) अणु
		vमुक्त(*rmem->vmem);
		*rmem->vmem = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_ring(काष्ठा bnxt *bp, काष्ठा bnxt_ring_mem_info *rmem)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	u64 valid_bit = 0;
	पूर्णांक i;

	अगर (rmem->flags & (BNXT_RMEM_VALID_PTE_FLAG | BNXT_RMEM_RING_PTE_FLAG))
		valid_bit = PTU_PTE_VALID;
	अगर ((rmem->nr_pages > 1 || rmem->depth > 0) && !rmem->pg_tbl) अणु
		माप_प्रकार pg_tbl_size = rmem->nr_pages * 8;

		अगर (rmem->flags & BNXT_RMEM_USE_FULL_PAGE_FLAG)
			pg_tbl_size = rmem->page_size;
		rmem->pg_tbl = dma_alloc_coherent(&pdev->dev, pg_tbl_size,
						  &rmem->pg_tbl_map,
						  GFP_KERNEL);
		अगर (!rmem->pg_tbl)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < rmem->nr_pages; i++) अणु
		u64 extra_bits = valid_bit;

		rmem->pg_arr[i] = dma_alloc_coherent(&pdev->dev,
						     rmem->page_size,
						     &rmem->dma_arr[i],
						     GFP_KERNEL);
		अगर (!rmem->pg_arr[i])
			वापस -ENOMEM;

		अगर (rmem->mem_init)
			bnxt_init_ctx_mem(rmem->mem_init, rmem->pg_arr[i],
					  rmem->page_size);
		अगर (rmem->nr_pages > 1 || rmem->depth > 0) अणु
			अगर (i == rmem->nr_pages - 2 &&
			    (rmem->flags & BNXT_RMEM_RING_PTE_FLAG))
				extra_bits |= PTU_PTE_NEXT_TO_LAST;
			अन्यथा अगर (i == rmem->nr_pages - 1 &&
				 (rmem->flags & BNXT_RMEM_RING_PTE_FLAG))
				extra_bits |= PTU_PTE_LAST;
			rmem->pg_tbl[i] =
				cpu_to_le64(rmem->dma_arr[i] | extra_bits);
		पूर्ण
	पूर्ण

	अगर (rmem->vmem_size) अणु
		*rmem->vmem = vzalloc(rmem->vmem_size);
		अगर (!(*rmem->vmem))
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_tpa_info(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];

		kमुक्त(rxr->rx_tpa_idx_map);
		rxr->rx_tpa_idx_map = शून्य;
		अगर (rxr->rx_tpa) अणु
			kमुक्त(rxr->rx_tpa[0].agg_arr);
			rxr->rx_tpa[0].agg_arr = शून्य;
		पूर्ण
		kमुक्त(rxr->rx_tpa);
		rxr->rx_tpa = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_tpa_info(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, j, total_aggs = 0;

	bp->max_tpa = MAX_TPA;
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		अगर (!bp->max_tpa_v2)
			वापस 0;
		bp->max_tpa = max_t(u16, bp->max_tpa_v2, MAX_TPA_P5);
		total_aggs = bp->max_tpa * MAX_SKB_FRAGS;
	पूर्ण

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा rx_agg_cmp *agg;

		rxr->rx_tpa = kसुस्मृति(bp->max_tpa, माप(काष्ठा bnxt_tpa_info),
				      GFP_KERNEL);
		अगर (!rxr->rx_tpa)
			वापस -ENOMEM;

		अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
			जारी;
		agg = kसुस्मृति(total_aggs, माप(*agg), GFP_KERNEL);
		rxr->rx_tpa[0].agg_arr = agg;
		अगर (!agg)
			वापस -ENOMEM;
		क्रम (j = 1; j < bp->max_tpa; j++)
			rxr->rx_tpa[j].agg_arr = agg + j * MAX_SKB_FRAGS;
		rxr->rx_tpa_idx_map = kzalloc(माप(*rxr->rx_tpa_idx_map),
					      GFP_KERNEL);
		अगर (!rxr->rx_tpa_idx_map)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_rx_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->rx_ring)
		वापस;

	bnxt_मुक्त_tpa_info(bp);
	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring;

		अगर (rxr->xdp_prog)
			bpf_prog_put(rxr->xdp_prog);

		अगर (xdp_rxq_info_is_reg(&rxr->xdp_rxq))
			xdp_rxq_info_unreg(&rxr->xdp_rxq);

		page_pool_destroy(rxr->page_pool);
		rxr->page_pool = शून्य;

		kमुक्त(rxr->rx_agg_bmap);
		rxr->rx_agg_bmap = शून्य;

		ring = &rxr->rx_ring_काष्ठा;
		bnxt_मुक्त_ring(bp, &ring->ring_mem);

		ring = &rxr->rx_agg_ring_काष्ठा;
		bnxt_मुक्त_ring(bp, &ring->ring_mem);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_rx_page_pool(काष्ठा bnxt *bp,
				   काष्ठा bnxt_rx_ring_info *rxr)
अणु
	काष्ठा page_pool_params pp = अणु 0 पूर्ण;

	pp.pool_size = bp->rx_ring_size;
	pp.nid = dev_to_node(&bp->pdev->dev);
	pp.dev = &bp->pdev->dev;
	pp.dma_dir = DMA_BIसूचीECTIONAL;

	rxr->page_pool = page_pool_create(&pp);
	अगर (IS_ERR(rxr->page_pool)) अणु
		पूर्णांक err = PTR_ERR(rxr->page_pool);

		rxr->page_pool = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_alloc_rx_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, rc = 0, agg_rings = 0;

	अगर (!bp->rx_ring)
		वापस -ENOMEM;

	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		agg_rings = 1;

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring;

		ring = &rxr->rx_ring_काष्ठा;

		rc = bnxt_alloc_rx_page_pool(bp, rxr);
		अगर (rc)
			वापस rc;

		rc = xdp_rxq_info_reg(&rxr->xdp_rxq, bp->dev, i, 0);
		अगर (rc < 0)
			वापस rc;

		rc = xdp_rxq_info_reg_mem_model(&rxr->xdp_rxq,
						MEM_TYPE_PAGE_POOL,
						rxr->page_pool);
		अगर (rc) अणु
			xdp_rxq_info_unreg(&rxr->xdp_rxq);
			वापस rc;
		पूर्ण

		rc = bnxt_alloc_ring(bp, &ring->ring_mem);
		अगर (rc)
			वापस rc;

		ring->grp_idx = i;
		अगर (agg_rings) अणु
			u16 mem_size;

			ring = &rxr->rx_agg_ring_काष्ठा;
			rc = bnxt_alloc_ring(bp, &ring->ring_mem);
			अगर (rc)
				वापस rc;

			ring->grp_idx = i;
			rxr->rx_agg_bmap_size = bp->rx_agg_ring_mask + 1;
			mem_size = rxr->rx_agg_bmap_size / 8;
			rxr->rx_agg_bmap = kzalloc(mem_size, GFP_KERNEL);
			अगर (!rxr->rx_agg_bmap)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_TPA)
		rc = bnxt_alloc_tpa_info(bp);
	वापस rc;
पूर्ण

अटल व्योम bnxt_मुक्त_tx_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (!bp->tx_ring)
		वापस;

	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring;

		अगर (txr->tx_push) अणु
			dma_मुक्त_coherent(&pdev->dev, bp->tx_push_size,
					  txr->tx_push, txr->tx_push_mapping);
			txr->tx_push = शून्य;
		पूर्ण

		ring = &txr->tx_ring_काष्ठा;

		bnxt_मुक्त_ring(bp, &ring->ring_mem);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_tx_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, j, rc;
	काष्ठा pci_dev *pdev = bp->pdev;

	bp->tx_push_size = 0;
	अगर (bp->tx_push_thresh) अणु
		पूर्णांक push_size;

		push_size  = L1_CACHE_ALIGN(माप(काष्ठा tx_push_bd) +
					bp->tx_push_thresh);

		अगर (push_size > 256) अणु
			push_size = 0;
			bp->tx_push_thresh = 0;
		पूर्ण

		bp->tx_push_size = push_size;
	पूर्ण

	क्रम (i = 0, j = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring;
		u8 qidx;

		ring = &txr->tx_ring_काष्ठा;

		rc = bnxt_alloc_ring(bp, &ring->ring_mem);
		अगर (rc)
			वापस rc;

		ring->grp_idx = txr->bnapi->index;
		अगर (bp->tx_push_size) अणु
			dma_addr_t mapping;

			/* One pre-allocated DMA buffer to backup
			 * TX push operation
			 */
			txr->tx_push = dma_alloc_coherent(&pdev->dev,
						bp->tx_push_size,
						&txr->tx_push_mapping,
						GFP_KERNEL);

			अगर (!txr->tx_push)
				वापस -ENOMEM;

			mapping = txr->tx_push_mapping +
				माप(काष्ठा tx_push_bd);
			txr->data_mapping = cpu_to_le64(mapping);
		पूर्ण
		qidx = bp->tc_to_qidx[j];
		ring->queue_id = bp->q_info[qidx].queue_id;
		अगर (i < bp->tx_nr_rings_xdp)
			जारी;
		अगर (i % bp->tx_nr_rings_per_tc == (bp->tx_nr_rings_per_tc - 1))
			j++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_cp_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		काष्ठा bnxt_ring_काष्ठा *ring;
		पूर्णांक j;

		अगर (!bnapi)
			जारी;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_काष्ठा;

		bnxt_मुक्त_ring(bp, &ring->ring_mem);

		क्रम (j = 0; j < 2; j++) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];

			अगर (cpr2) अणु
				ring = &cpr2->cp_ring_काष्ठा;
				bnxt_मुक्त_ring(bp, &ring->ring_mem);
				kमुक्त(cpr2);
				cpr->cp_ring_arr[j] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा bnxt_cp_ring_info *bnxt_alloc_cp_sub_ring(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_ring_mem_info *rmem;
	काष्ठा bnxt_ring_काष्ठा *ring;
	काष्ठा bnxt_cp_ring_info *cpr;
	पूर्णांक rc;

	cpr = kzalloc(माप(*cpr), GFP_KERNEL);
	अगर (!cpr)
		वापस शून्य;

	ring = &cpr->cp_ring_काष्ठा;
	rmem = &ring->ring_mem;
	rmem->nr_pages = bp->cp_nr_pages;
	rmem->page_size = HW_CMPD_RING_SIZE;
	rmem->pg_arr = (व्योम **)cpr->cp_desc_ring;
	rmem->dma_arr = cpr->cp_desc_mapping;
	rmem->flags = BNXT_RMEM_RING_PTE_FLAG;
	rc = bnxt_alloc_ring(bp, rmem);
	अगर (rc) अणु
		bnxt_मुक्त_ring(bp, rmem);
		kमुक्त(cpr);
		cpr = शून्य;
	पूर्ण
	वापस cpr;
पूर्ण

अटल पूर्णांक bnxt_alloc_cp_rings(काष्ठा bnxt *bp)
अणु
	bool sh = !!(bp->flags & BNXT_FLAG_SHARED_RINGS);
	पूर्णांक i, rc, ulp_base_vec, ulp_msix;

	ulp_msix = bnxt_get_ulp_msix_num(bp);
	ulp_base_vec = bnxt_get_ulp_msix_base(bp);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		काष्ठा bnxt_ring_काष्ठा *ring;

		अगर (!bnapi)
			जारी;

		cpr = &bnapi->cp_ring;
		cpr->bnapi = bnapi;
		ring = &cpr->cp_ring_काष्ठा;

		rc = bnxt_alloc_ring(bp, &ring->ring_mem);
		अगर (rc)
			वापस rc;

		अगर (ulp_msix && i >= ulp_base_vec)
			ring->map_idx = i + ulp_msix;
		अन्यथा
			ring->map_idx = i;

		अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
			जारी;

		अगर (i < bp->rx_nr_rings) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 =
				bnxt_alloc_cp_sub_ring(bp);

			cpr->cp_ring_arr[BNXT_RX_HDL] = cpr2;
			अगर (!cpr2)
				वापस -ENOMEM;
			cpr2->bnapi = bnapi;
		पूर्ण
		अगर ((sh && i < bp->tx_nr_rings) ||
		    (!sh && i >= bp->rx_nr_rings)) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 =
				bnxt_alloc_cp_sub_ring(bp);

			cpr->cp_ring_arr[BNXT_TX_HDL] = cpr2;
			अगर (!cpr2)
				वापस -ENOMEM;
			cpr2->bnapi = bnapi;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_init_ring_काष्ठा(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_ring_mem_info *rmem;
		काष्ठा bnxt_cp_ring_info *cpr;
		काष्ठा bnxt_rx_ring_info *rxr;
		काष्ठा bnxt_tx_ring_info *txr;
		काष्ठा bnxt_ring_काष्ठा *ring;

		अगर (!bnapi)
			जारी;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_काष्ठा;
		rmem = &ring->ring_mem;
		rmem->nr_pages = bp->cp_nr_pages;
		rmem->page_size = HW_CMPD_RING_SIZE;
		rmem->pg_arr = (व्योम **)cpr->cp_desc_ring;
		rmem->dma_arr = cpr->cp_desc_mapping;
		rmem->vmem_size = 0;

		rxr = bnapi->rx_ring;
		अगर (!rxr)
			जाओ skip_rx;

		ring = &rxr->rx_ring_काष्ठा;
		rmem = &ring->ring_mem;
		rmem->nr_pages = bp->rx_nr_pages;
		rmem->page_size = HW_RXBD_RING_SIZE;
		rmem->pg_arr = (व्योम **)rxr->rx_desc_ring;
		rmem->dma_arr = rxr->rx_desc_mapping;
		rmem->vmem_size = SW_RXBD_RING_SIZE * bp->rx_nr_pages;
		rmem->vmem = (व्योम **)&rxr->rx_buf_ring;

		ring = &rxr->rx_agg_ring_काष्ठा;
		rmem = &ring->ring_mem;
		rmem->nr_pages = bp->rx_agg_nr_pages;
		rmem->page_size = HW_RXBD_RING_SIZE;
		rmem->pg_arr = (व्योम **)rxr->rx_agg_desc_ring;
		rmem->dma_arr = rxr->rx_agg_desc_mapping;
		rmem->vmem_size = SW_RXBD_AGG_RING_SIZE * bp->rx_agg_nr_pages;
		rmem->vmem = (व्योम **)&rxr->rx_agg_ring;

skip_rx:
		txr = bnapi->tx_ring;
		अगर (!txr)
			जारी;

		ring = &txr->tx_ring_काष्ठा;
		rmem = &ring->ring_mem;
		rmem->nr_pages = bp->tx_nr_pages;
		rmem->page_size = HW_RXBD_RING_SIZE;
		rmem->pg_arr = (व्योम **)txr->tx_desc_ring;
		rmem->dma_arr = txr->tx_desc_mapping;
		rmem->vmem_size = SW_TXBD_RING_SIZE * bp->tx_nr_pages;
		rmem->vmem = (व्योम **)&txr->tx_buf_ring;
	पूर्ण
पूर्ण

अटल व्योम bnxt_init_rxbd_pages(काष्ठा bnxt_ring_काष्ठा *ring, u32 type)
अणु
	पूर्णांक i;
	u32 prod;
	काष्ठा rx_bd **rx_buf_ring;

	rx_buf_ring = (काष्ठा rx_bd **)ring->ring_mem.pg_arr;
	क्रम (i = 0, prod = 0; i < ring->ring_mem.nr_pages; i++) अणु
		पूर्णांक j;
		काष्ठा rx_bd *rxbd;

		rxbd = rx_buf_ring[i];
		अगर (!rxbd)
			जारी;

		क्रम (j = 0; j < RX_DESC_CNT; j++, rxbd++, prod++) अणु
			rxbd->rx_bd_len_flags_type = cpu_to_le32(type);
			rxbd->rx_bd_opaque = prod;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_one_rx_ring(काष्ठा bnxt *bp, पूर्णांक ring_nr)
अणु
	काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[ring_nr];
	काष्ठा net_device *dev = bp->dev;
	u32 prod;
	पूर्णांक i;

	prod = rxr->rx_prod;
	क्रम (i = 0; i < bp->rx_ring_size; i++) अणु
		अगर (bnxt_alloc_rx_data(bp, rxr, prod, GFP_KERNEL)) अणु
			netdev_warn(dev, "init'ed rx ring %d with %d/%d skbs only\n",
				    ring_nr, i, bp->rx_ring_size);
			अवरोध;
		पूर्ण
		prod = NEXT_RX(prod);
	पूर्ण
	rxr->rx_prod = prod;

	अगर (!(bp->flags & BNXT_FLAG_AGG_RINGS))
		वापस 0;

	prod = rxr->rx_agg_prod;
	क्रम (i = 0; i < bp->rx_agg_ring_size; i++) अणु
		अगर (bnxt_alloc_rx_page(bp, rxr, prod, GFP_KERNEL)) अणु
			netdev_warn(dev, "init'ed rx ring %d with %d/%d pages only\n",
				    ring_nr, i, bp->rx_ring_size);
			अवरोध;
		पूर्ण
		prod = NEXT_RX_AGG(prod);
	पूर्ण
	rxr->rx_agg_prod = prod;

	अगर (rxr->rx_tpa) अणु
		dma_addr_t mapping;
		u8 *data;

		क्रम (i = 0; i < bp->max_tpa; i++) अणु
			data = __bnxt_alloc_rx_data(bp, &mapping, GFP_KERNEL);
			अगर (!data)
				वापस -ENOMEM;

			rxr->rx_tpa[i].data = data;
			rxr->rx_tpa[i].data_ptr = data + bp->rx_offset;
			rxr->rx_tpa[i].mapping = mapping;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_init_one_rx_ring(काष्ठा bnxt *bp, पूर्णांक ring_nr)
अणु
	काष्ठा bnxt_rx_ring_info *rxr;
	काष्ठा bnxt_ring_काष्ठा *ring;
	u32 type;

	type = (bp->rx_buf_use_size << RX_BD_LEN_SHIFT) |
		RX_BD_TYPE_RX_PACKET_BD | RX_BD_FLAGS_EOP;

	अगर (NET_IP_ALIGN == 2)
		type |= RX_BD_FLAGS_SOP;

	rxr = &bp->rx_ring[ring_nr];
	ring = &rxr->rx_ring_काष्ठा;
	bnxt_init_rxbd_pages(ring, type);

	अगर (BNXT_RX_PAGE_MODE(bp) && bp->xdp_prog) अणु
		bpf_prog_add(bp->xdp_prog, 1);
		rxr->xdp_prog = bp->xdp_prog;
	पूर्ण
	ring->fw_ring_id = INVALID_HW_RING_ID;

	ring = &rxr->rx_agg_ring_काष्ठा;
	ring->fw_ring_id = INVALID_HW_RING_ID;

	अगर ((bp->flags & BNXT_FLAG_AGG_RINGS)) अणु
		type = ((u32)BNXT_RX_PAGE_SIZE << RX_BD_LEN_SHIFT) |
			RX_BD_TYPE_RX_AGG_BD | RX_BD_FLAGS_SOP;

		bnxt_init_rxbd_pages(ring, type);
	पूर्ण

	वापस bnxt_alloc_one_rx_ring(bp, ring_nr);
पूर्ण

अटल व्योम bnxt_init_cp_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;
		काष्ठा bnxt_ring_काष्ठा *ring = &cpr->cp_ring_काष्ठा;

		ring->fw_ring_id = INVALID_HW_RING_ID;
		cpr->rx_ring_coal.coal_ticks = bp->rx_coal.coal_ticks;
		cpr->rx_ring_coal.coal_bufs = bp->rx_coal.coal_bufs;
		क्रम (j = 0; j < 2; j++) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];

			अगर (!cpr2)
				जारी;

			ring = &cpr2->cp_ring_काष्ठा;
			ring->fw_ring_id = INVALID_HW_RING_ID;
			cpr2->rx_ring_coal.coal_ticks = bp->rx_coal.coal_ticks;
			cpr2->rx_ring_coal.coal_bufs = bp->rx_coal.coal_bufs;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_init_rx_rings(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, rc = 0;

	अगर (BNXT_RX_PAGE_MODE(bp)) अणु
		bp->rx_offset = NET_IP_ALIGN + XDP_PACKET_HEADROOM;
		bp->rx_dma_offset = XDP_PACKET_HEADROOM;
	पूर्ण अन्यथा अणु
		bp->rx_offset = BNXT_RX_OFFSET;
		bp->rx_dma_offset = BNXT_RX_DMA_OFFSET;
	पूर्ण

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		rc = bnxt_init_one_rx_ring(bp, i);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_init_tx_rings(काष्ठा bnxt *bp)
अणु
	u16 i;

	bp->tx_wake_thresh = max_t(पूर्णांक, bp->tx_ring_size / 2,
				   MAX_SKB_FRAGS + 1);

	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring = &txr->tx_ring_काष्ठा;

		ring->fw_ring_id = INVALID_HW_RING_ID;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_ring_grps(काष्ठा bnxt *bp)
अणु
	kमुक्त(bp->grp_info);
	bp->grp_info = शून्य;
पूर्ण

अटल पूर्णांक bnxt_init_ring_grps(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	पूर्णांक i;

	अगर (irq_re_init) अणु
		bp->grp_info = kसुस्मृति(bp->cp_nr_rings,
				       माप(काष्ठा bnxt_ring_grp_info),
				       GFP_KERNEL);
		अगर (!bp->grp_info)
			वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		अगर (irq_re_init)
			bp->grp_info[i].fw_stats_ctx = INVALID_HW_RING_ID;
		bp->grp_info[i].fw_grp_id = INVALID_HW_RING_ID;
		bp->grp_info[i].rx_fw_ring_id = INVALID_HW_RING_ID;
		bp->grp_info[i].agg_fw_ring_id = INVALID_HW_RING_ID;
		bp->grp_info[i].cp_fw_ring_id = INVALID_HW_RING_ID;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_vnics(काष्ठा bnxt *bp)
अणु
	kमुक्त(bp->vnic_info);
	bp->vnic_info = शून्य;
	bp->nr_vnics = 0;
पूर्ण

अटल पूर्णांक bnxt_alloc_vnics(काष्ठा bnxt *bp)
अणु
	पूर्णांक num_vnics = 1;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर ((bp->flags & (BNXT_FLAG_RFS | BNXT_FLAG_CHIP_P5)) == BNXT_FLAG_RFS)
		num_vnics += bp->rx_nr_rings;
#पूर्ण_अगर

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		num_vnics++;

	bp->vnic_info = kसुस्मृति(num_vnics, माप(काष्ठा bnxt_vnic_info),
				GFP_KERNEL);
	अगर (!bp->vnic_info)
		वापस -ENOMEM;

	bp->nr_vnics = num_vnics;
	वापस 0;
पूर्ण

अटल व्योम bnxt_init_vnics(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->nr_vnics; i++) अणु
		काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[i];
		पूर्णांक j;

		vnic->fw_vnic_id = INVALID_HW_RING_ID;
		क्रम (j = 0; j < BNXT_MAX_CTX_PER_VNIC; j++)
			vnic->fw_rss_cos_lb_ctx[j] = INVALID_HW_RING_ID;

		vnic->fw_l2_ctx_id = INVALID_HW_RING_ID;

		अगर (bp->vnic_info[i].rss_hash_key) अणु
			अगर (i == 0)
				pअक्रमom_bytes(vnic->rss_hash_key,
					      HW_HASH_KEY_SIZE);
			अन्यथा
				स_नकल(vnic->rss_hash_key,
				       bp->vnic_info[0].rss_hash_key,
				       HW_HASH_KEY_SIZE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_calc_nr_ring_pages(u32 ring_size, पूर्णांक desc_per_pg)
अणु
	पूर्णांक pages;

	pages = ring_size / desc_per_pg;

	अगर (!pages)
		वापस 1;

	pages++;

	जबतक (pages & (pages - 1))
		pages++;

	वापस pages;
पूर्ण

व्योम bnxt_set_tpa_flags(काष्ठा bnxt *bp)
अणु
	bp->flags &= ~BNXT_FLAG_TPA;
	अगर (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		वापस;
	अगर (bp->dev->features & NETIF_F_LRO)
		bp->flags |= BNXT_FLAG_LRO;
	अन्यथा अगर (bp->dev->features & NETIF_F_GRO_HW)
		bp->flags |= BNXT_FLAG_GRO;
पूर्ण

/* bp->rx_ring_size, bp->tx_ring_size, dev->mtu, BNXT_FLAG_अणुG|Lपूर्णRO flags must
 * be set on entry.
 */
व्योम bnxt_set_ring_params(काष्ठा bnxt *bp)
अणु
	u32 ring_size, rx_size, rx_space, max_rx_cmpl;
	u32 agg_factor = 0, agg_ring_size = 0;

	/* 8 क्रम CRC and VLAN */
	rx_size = SKB_DATA_ALIGN(bp->dev->mtu + ETH_HLEN + NET_IP_ALIGN + 8);

	rx_space = rx_size + NET_SKB_PAD +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	bp->rx_copy_thresh = BNXT_RX_COPY_THRESH;
	ring_size = bp->rx_ring_size;
	bp->rx_agg_ring_size = 0;
	bp->rx_agg_nr_pages = 0;

	अगर (bp->flags & BNXT_FLAG_TPA)
		agg_factor = min_t(u32, 4, 65536 / BNXT_RX_PAGE_SIZE);

	bp->flags &= ~BNXT_FLAG_JUMBO;
	अगर (rx_space > PAGE_SIZE && !(bp->flags & BNXT_FLAG_NO_AGG_RINGS)) अणु
		u32 jumbo_factor;

		bp->flags |= BNXT_FLAG_JUMBO;
		jumbo_factor = PAGE_ALIGN(bp->dev->mtu - 40) >> PAGE_SHIFT;
		अगर (jumbo_factor > agg_factor)
			agg_factor = jumbo_factor;
	पूर्ण
	agg_ring_size = ring_size * agg_factor;

	अगर (agg_ring_size) अणु
		bp->rx_agg_nr_pages = bnxt_calc_nr_ring_pages(agg_ring_size,
							RX_DESC_CNT);
		अगर (bp->rx_agg_nr_pages > MAX_RX_AGG_PAGES) अणु
			u32 पंचांगp = agg_ring_size;

			bp->rx_agg_nr_pages = MAX_RX_AGG_PAGES;
			agg_ring_size = MAX_RX_AGG_PAGES * RX_DESC_CNT - 1;
			netdev_warn(bp->dev, "rx agg ring size %d reduced to %d.\n",
				    पंचांगp, agg_ring_size);
		पूर्ण
		bp->rx_agg_ring_size = agg_ring_size;
		bp->rx_agg_ring_mask = (bp->rx_agg_nr_pages * RX_DESC_CNT) - 1;
		rx_size = SKB_DATA_ALIGN(BNXT_RX_COPY_THRESH + NET_IP_ALIGN);
		rx_space = rx_size + NET_SKB_PAD +
			SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	पूर्ण

	bp->rx_buf_use_size = rx_size;
	bp->rx_buf_size = rx_space;

	bp->rx_nr_pages = bnxt_calc_nr_ring_pages(ring_size, RX_DESC_CNT);
	bp->rx_ring_mask = (bp->rx_nr_pages * RX_DESC_CNT) - 1;

	ring_size = bp->tx_ring_size;
	bp->tx_nr_pages = bnxt_calc_nr_ring_pages(ring_size, TX_DESC_CNT);
	bp->tx_ring_mask = (bp->tx_nr_pages * TX_DESC_CNT) - 1;

	max_rx_cmpl = bp->rx_ring_size;
	/* MAX TPA needs to be added because TPA_START completions are
	 * immediately recycled, so the TPA completions are not bound by
	 * the RX ring size.
	 */
	अगर (bp->flags & BNXT_FLAG_TPA)
		max_rx_cmpl += bp->max_tpa;
	/* RX and TPA completions are 32-byte, all others are 16-byte */
	ring_size = max_rx_cmpl * 2 + agg_ring_size + bp->tx_ring_size;
	bp->cp_ring_size = ring_size;

	bp->cp_nr_pages = bnxt_calc_nr_ring_pages(ring_size, CP_DESC_CNT);
	अगर (bp->cp_nr_pages > MAX_CP_PAGES) अणु
		bp->cp_nr_pages = MAX_CP_PAGES;
		bp->cp_ring_size = MAX_CP_PAGES * CP_DESC_CNT - 1;
		netdev_warn(bp->dev, "completion ring size %d reduced to %d.\n",
			    ring_size, bp->cp_ring_size);
	पूर्ण
	bp->cp_bit = bp->cp_nr_pages * CP_DESC_CNT;
	bp->cp_ring_mask = bp->cp_bit - 1;
पूर्ण

/* Changing allocation mode of RX rings.
 * TODO: Update when extending xdp_rxq_info to support allocation modes.
 */
पूर्णांक bnxt_set_rx_skb_mode(काष्ठा bnxt *bp, bool page_mode)
अणु
	अगर (page_mode) अणु
		अगर (bp->dev->mtu > BNXT_MAX_PAGE_MODE_MTU)
			वापस -EOPNOTSUPP;
		bp->dev->max_mtu =
			min_t(u16, bp->max_mtu, BNXT_MAX_PAGE_MODE_MTU);
		bp->flags &= ~BNXT_FLAG_AGG_RINGS;
		bp->flags |= BNXT_FLAG_NO_AGG_RINGS | BNXT_FLAG_RX_PAGE_MODE;
		bp->rx_dir = DMA_BIसूचीECTIONAL;
		bp->rx_skb_func = bnxt_rx_page_skb;
		/* Disable LRO or GRO_HW */
		netdev_update_features(bp->dev);
	पूर्ण अन्यथा अणु
		bp->dev->max_mtu = bp->max_mtu;
		bp->flags &= ~BNXT_FLAG_RX_PAGE_MODE;
		bp->rx_dir = DMA_FROM_DEVICE;
		bp->rx_skb_func = bnxt_rx_skb;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_vnic_attributes(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	काष्ठा bnxt_vnic_info *vnic;
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (!bp->vnic_info)
		वापस;

	क्रम (i = 0; i < bp->nr_vnics; i++) अणु
		vnic = &bp->vnic_info[i];

		kमुक्त(vnic->fw_grp_ids);
		vnic->fw_grp_ids = शून्य;

		kमुक्त(vnic->uc_list);
		vnic->uc_list = शून्य;

		अगर (vnic->mc_list) अणु
			dma_मुक्त_coherent(&pdev->dev, vnic->mc_list_size,
					  vnic->mc_list, vnic->mc_list_mapping);
			vnic->mc_list = शून्य;
		पूर्ण

		अगर (vnic->rss_table) अणु
			dma_मुक्त_coherent(&pdev->dev, vnic->rss_table_size,
					  vnic->rss_table,
					  vnic->rss_table_dma_addr);
			vnic->rss_table = शून्य;
		पूर्ण

		vnic->rss_hash_key = शून्य;
		vnic->flags = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_vnic_attributes(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, rc = 0, size;
	काष्ठा bnxt_vnic_info *vnic;
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक max_rings;

	क्रम (i = 0; i < bp->nr_vnics; i++) अणु
		vnic = &bp->vnic_info[i];

		अगर (vnic->flags & BNXT_VNIC_UCAST_FLAG) अणु
			पूर्णांक mem_size = (BNXT_MAX_UC_ADDRS - 1) * ETH_ALEN;

			अगर (mem_size > 0) अणु
				vnic->uc_list = kदो_स्मृति(mem_size, GFP_KERNEL);
				अगर (!vnic->uc_list) अणु
					rc = -ENOMEM;
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (vnic->flags & BNXT_VNIC_MCAST_FLAG) अणु
			vnic->mc_list_size = BNXT_MAX_MC_ADDRS * ETH_ALEN;
			vnic->mc_list =
				dma_alloc_coherent(&pdev->dev,
						   vnic->mc_list_size,
						   &vnic->mc_list_mapping,
						   GFP_KERNEL);
			अगर (!vnic->mc_list) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			जाओ vnic_skip_grps;

		अगर (vnic->flags & BNXT_VNIC_RSS_FLAG)
			max_rings = bp->rx_nr_rings;
		अन्यथा
			max_rings = 1;

		vnic->fw_grp_ids = kसुस्मृति(max_rings, माप(u16), GFP_KERNEL);
		अगर (!vnic->fw_grp_ids) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
vnic_skip_grps:
		अगर ((bp->flags & BNXT_FLAG_NEW_RSS_CAP) &&
		    !(vnic->flags & BNXT_VNIC_RSS_FLAG))
			जारी;

		/* Allocate rss table and hash key */
		size = L1_CACHE_ALIGN(HW_HASH_INDEX_SIZE * माप(u16));
		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			size = L1_CACHE_ALIGN(BNXT_MAX_RSS_TABLE_SIZE_P5);

		vnic->rss_table_size = size + HW_HASH_KEY_SIZE;
		vnic->rss_table = dma_alloc_coherent(&pdev->dev,
						     vnic->rss_table_size,
						     &vnic->rss_table_dma_addr,
						     GFP_KERNEL);
		अगर (!vnic->rss_table) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		vnic->rss_hash_key = ((व्योम *)vnic->rss_table) + size;
		vnic->rss_hash_key_dma_addr = vnic->rss_table_dma_addr + size;
	पूर्ण
	वापस 0;

out:
	वापस rc;
पूर्ण

अटल व्योम bnxt_मुक्त_hwrm_resources(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (bp->hwrm_cmd_resp_addr) अणु
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, bp->hwrm_cmd_resp_addr,
				  bp->hwrm_cmd_resp_dma_addr);
		bp->hwrm_cmd_resp_addr = शून्य;
	पूर्ण

	अगर (bp->hwrm_cmd_kong_resp_addr) अणु
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE,
				  bp->hwrm_cmd_kong_resp_addr,
				  bp->hwrm_cmd_kong_resp_dma_addr);
		bp->hwrm_cmd_kong_resp_addr = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_kong_hwrm_resources(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (bp->hwrm_cmd_kong_resp_addr)
		वापस 0;

	bp->hwrm_cmd_kong_resp_addr =
		dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
				   &bp->hwrm_cmd_kong_resp_dma_addr,
				   GFP_KERNEL);
	अगर (!bp->hwrm_cmd_kong_resp_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_alloc_hwrm_resources(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;

	bp->hwrm_cmd_resp_addr = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
						   &bp->hwrm_cmd_resp_dma_addr,
						   GFP_KERNEL);
	अगर (!bp->hwrm_cmd_resp_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_hwrm_लघु_cmd_req(काष्ठा bnxt *bp)
अणु
	अगर (bp->hwrm_लघु_cmd_req_addr) अणु
		काष्ठा pci_dev *pdev = bp->pdev;

		dma_मुक्त_coherent(&pdev->dev, bp->hwrm_max_ext_req_len,
				  bp->hwrm_लघु_cmd_req_addr,
				  bp->hwrm_लघु_cmd_req_dma_addr);
		bp->hwrm_लघु_cmd_req_addr = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_hwrm_लघु_cmd_req(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;

	अगर (bp->hwrm_लघु_cmd_req_addr)
		वापस 0;

	bp->hwrm_लघु_cmd_req_addr =
		dma_alloc_coherent(&pdev->dev, bp->hwrm_max_ext_req_len,
				   &bp->hwrm_लघु_cmd_req_dma_addr,
				   GFP_KERNEL);
	अगर (!bp->hwrm_लघु_cmd_req_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_stats_mem(काष्ठा bnxt *bp, काष्ठा bnxt_stats_mem *stats)
अणु
	kमुक्त(stats->hw_masks);
	stats->hw_masks = शून्य;
	kमुक्त(stats->sw_stats);
	stats->sw_stats = शून्य;
	अगर (stats->hw_stats) अणु
		dma_मुक्त_coherent(&bp->pdev->dev, stats->len, stats->hw_stats,
				  stats->hw_stats_map);
		stats->hw_stats = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_stats_mem(काष्ठा bnxt *bp, काष्ठा bnxt_stats_mem *stats,
				bool alloc_masks)
अणु
	stats->hw_stats = dma_alloc_coherent(&bp->pdev->dev, stats->len,
					     &stats->hw_stats_map, GFP_KERNEL);
	अगर (!stats->hw_stats)
		वापस -ENOMEM;

	stats->sw_stats = kzalloc(stats->len, GFP_KERNEL);
	अगर (!stats->sw_stats)
		जाओ stats_mem_err;

	अगर (alloc_masks) अणु
		stats->hw_masks = kzalloc(stats->len, GFP_KERNEL);
		अगर (!stats->hw_masks)
			जाओ stats_mem_err;
	पूर्ण
	वापस 0;

stats_mem_err:
	bnxt_मुक्त_stats_mem(bp, stats);
	वापस -ENOMEM;
पूर्ण

अटल व्योम bnxt_fill_masks(u64 *mask_arr, u64 mask, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		mask_arr[i] = mask;
पूर्ण

अटल व्योम bnxt_copy_hw_masks(u64 *mask_arr, __le64 *hw_mask_arr, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		mask_arr[i] = le64_to_cpu(hw_mask_arr[i]);
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_qstat_ext(काष्ठा bnxt *bp,
				    काष्ठा bnxt_stats_mem *stats)
अणु
	काष्ठा hwrm_func_qstats_ext_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_qstats_ext_input req = अणु0पूर्ण;
	__le64 *hw_masks;
	पूर्णांक rc;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED) ||
	    !(bp->flags & BNXT_FLAG_CHIP_P5))
		वापस -EOPNOTSUPP;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QSTATS_EXT, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.flags = FUNC_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ qstat_निकास;

	hw_masks = &resp->rx_ucast_pkts;
	bnxt_copy_hw_masks(stats->hw_masks, hw_masks, stats->len / 8);

qstat_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_qstats(काष्ठा bnxt *bp, u8 flags);
अटल पूर्णांक bnxt_hwrm_port_qstats_ext(काष्ठा bnxt *bp, u8 flags);

अटल व्योम bnxt_init_stats(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_napi *bnapi = bp->bnapi[0];
	काष्ठा bnxt_cp_ring_info *cpr;
	काष्ठा bnxt_stats_mem *stats;
	__le64 *rx_stats, *tx_stats;
	पूर्णांक rc, rx_count, tx_count;
	u64 *rx_masks, *tx_masks;
	u64 mask;
	u8 flags;

	cpr = &bnapi->cp_ring;
	stats = &cpr->stats;
	rc = bnxt_hwrm_func_qstat_ext(bp, stats);
	अगर (rc) अणु
		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			mask = (1ULL << 48) - 1;
		अन्यथा
			mask = -1ULL;
		bnxt_fill_masks(stats->hw_masks, mask, stats->len / 8);
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_PORT_STATS) अणु
		stats = &bp->port_stats;
		rx_stats = stats->hw_stats;
		rx_masks = stats->hw_masks;
		rx_count = माप(काष्ठा rx_port_stats) / 8;
		tx_stats = rx_stats + BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;
		tx_masks = rx_masks + BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;
		tx_count = माप(काष्ठा tx_port_stats) / 8;

		flags = PORT_QSTATS_REQ_FLAGS_COUNTER_MASK;
		rc = bnxt_hwrm_port_qstats(bp, flags);
		अगर (rc) अणु
			mask = (1ULL << 40) - 1;

			bnxt_fill_masks(rx_masks, mask, rx_count);
			bnxt_fill_masks(tx_masks, mask, tx_count);
		पूर्ण अन्यथा अणु
			bnxt_copy_hw_masks(rx_masks, rx_stats, rx_count);
			bnxt_copy_hw_masks(tx_masks, tx_stats, tx_count);
			bnxt_hwrm_port_qstats(bp, 0);
		पूर्ण
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_PORT_STATS_EXT) अणु
		stats = &bp->rx_port_stats_ext;
		rx_stats = stats->hw_stats;
		rx_masks = stats->hw_masks;
		rx_count = माप(काष्ठा rx_port_stats_ext) / 8;
		stats = &bp->tx_port_stats_ext;
		tx_stats = stats->hw_stats;
		tx_masks = stats->hw_masks;
		tx_count = माप(काष्ठा tx_port_stats_ext) / 8;

		flags = PORT_QSTATS_EXT_REQ_FLAGS_COUNTER_MASK;
		rc = bnxt_hwrm_port_qstats_ext(bp, flags);
		अगर (rc) अणु
			mask = (1ULL << 40) - 1;

			bnxt_fill_masks(rx_masks, mask, rx_count);
			अगर (tx_stats)
				bnxt_fill_masks(tx_masks, mask, tx_count);
		पूर्ण अन्यथा अणु
			bnxt_copy_hw_masks(rx_masks, rx_stats, rx_count);
			अगर (tx_stats)
				bnxt_copy_hw_masks(tx_masks, tx_stats,
						   tx_count);
			bnxt_hwrm_port_qstats_ext(bp, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_मुक्त_port_stats(काष्ठा bnxt *bp)
अणु
	bp->flags &= ~BNXT_FLAG_PORT_STATS;
	bp->flags &= ~BNXT_FLAG_PORT_STATS_EXT;

	bnxt_मुक्त_stats_mem(bp, &bp->port_stats);
	bnxt_मुक्त_stats_mem(bp, &bp->rx_port_stats_ext);
	bnxt_मुक्त_stats_mem(bp, &bp->tx_port_stats_ext);
पूर्ण

अटल व्योम bnxt_मुक्त_ring_stats(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		bnxt_मुक्त_stats_mem(bp, &cpr->stats);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_stats(काष्ठा bnxt *bp)
अणु
	u32 size, i;
	पूर्णांक rc;

	size = bp->hw_ring_stats_size;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		cpr->stats.len = size;
		rc = bnxt_alloc_stats_mem(bp, &cpr->stats, !i);
		अगर (rc)
			वापस rc;

		cpr->hw_stats_ctx_id = INVALID_STATS_CTX_ID;
	पूर्ण

	अगर (BNXT_VF(bp) || bp->chip_num == CHIP_NUM_58700)
		वापस 0;

	अगर (bp->port_stats.hw_stats)
		जाओ alloc_ext_stats;

	bp->port_stats.len = BNXT_PORT_STATS_SIZE;
	rc = bnxt_alloc_stats_mem(bp, &bp->port_stats, true);
	अगर (rc)
		वापस rc;

	bp->flags |= BNXT_FLAG_PORT_STATS;

alloc_ext_stats:
	/* Display extended statistics only अगर FW supports it */
	अगर (bp->hwrm_spec_code < 0x10804 || bp->hwrm_spec_code == 0x10900)
		अगर (!(bp->fw_cap & BNXT_FW_CAP_EXT_STATS_SUPPORTED))
			वापस 0;

	अगर (bp->rx_port_stats_ext.hw_stats)
		जाओ alloc_tx_ext_stats;

	bp->rx_port_stats_ext.len = माप(काष्ठा rx_port_stats_ext);
	rc = bnxt_alloc_stats_mem(bp, &bp->rx_port_stats_ext, true);
	/* Extended stats are optional */
	अगर (rc)
		वापस 0;

alloc_tx_ext_stats:
	अगर (bp->tx_port_stats_ext.hw_stats)
		वापस 0;

	अगर (bp->hwrm_spec_code >= 0x10902 ||
	    (bp->fw_cap & BNXT_FW_CAP_EXT_STATS_SUPPORTED)) अणु
		bp->tx_port_stats_ext.len = माप(काष्ठा tx_port_stats_ext);
		rc = bnxt_alloc_stats_mem(bp, &bp->tx_port_stats_ext, true);
		/* Extended stats are optional */
		अगर (rc)
			वापस 0;
	पूर्ण
	bp->flags |= BNXT_FLAG_PORT_STATS_EXT;
	वापस 0;
पूर्ण

अटल व्योम bnxt_clear_ring_indices(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		काष्ठा bnxt_rx_ring_info *rxr;
		काष्ठा bnxt_tx_ring_info *txr;

		अगर (!bnapi)
			जारी;

		cpr = &bnapi->cp_ring;
		cpr->cp_raw_cons = 0;

		txr = bnapi->tx_ring;
		अगर (txr) अणु
			txr->tx_prod = 0;
			txr->tx_cons = 0;
		पूर्ण

		rxr = bnapi->rx_ring;
		अगर (rxr) अणु
			rxr->rx_prod = 0;
			rxr->rx_agg_prod = 0;
			rxr->rx_sw_agg_prod = 0;
			rxr->rx_next_cons = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_मुक्त_ntp_fltrs(काष्ठा bnxt *bp, bool irq_reinit)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	पूर्णांक i;

	/* Under rtnl_lock and all our NAPIs have been disabled.  It's
	 * safe to delete the hash table.
	 */
	क्रम (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) अणु
		काष्ठा hlist_head *head;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा bnxt_ntuple_filter *fltr;

		head = &bp->ntp_fltr_hash_tbl[i];
		hlist_क्रम_each_entry_safe(fltr, पंचांगp, head, hash) अणु
			hlist_del(&fltr->hash);
			kमुक्त(fltr);
		पूर्ण
	पूर्ण
	अगर (irq_reinit) अणु
		kमुक्त(bp->ntp_fltr_bmap);
		bp->ntp_fltr_bmap = शून्य;
	पूर्ण
	bp->ntp_fltr_count = 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bnxt_alloc_ntp_fltrs(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	पूर्णांक i, rc = 0;

	अगर (!(bp->flags & BNXT_FLAG_RFS))
		वापस 0;

	क्रम (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&bp->ntp_fltr_hash_tbl[i]);

	bp->ntp_fltr_count = 0;
	bp->ntp_fltr_bmap = kसुस्मृति(BITS_TO_LONGS(BNXT_NTP_FLTR_MAX_FLTR),
				    माप(दीर्घ),
				    GFP_KERNEL);

	अगर (!bp->ntp_fltr_bmap)
		rc = -ENOMEM;

	वापस rc;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम bnxt_मुक्त_mem(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	bnxt_मुक्त_vnic_attributes(bp);
	bnxt_मुक्त_tx_rings(bp);
	bnxt_मुक्त_rx_rings(bp);
	bnxt_मुक्त_cp_rings(bp);
	bnxt_मुक्त_ntp_fltrs(bp, irq_re_init);
	अगर (irq_re_init) अणु
		bnxt_मुक्त_ring_stats(bp);
		अगर (!(bp->phy_flags & BNXT_PHY_FL_PORT_STATS_NO_RESET) ||
		    test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
			bnxt_मुक्त_port_stats(bp);
		bnxt_मुक्त_ring_grps(bp);
		bnxt_मुक्त_vnics(bp);
		kमुक्त(bp->tx_ring_map);
		bp->tx_ring_map = शून्य;
		kमुक्त(bp->tx_ring);
		bp->tx_ring = शून्य;
		kमुक्त(bp->rx_ring);
		bp->rx_ring = शून्य;
		kमुक्त(bp->bnapi);
		bp->bnapi = शून्य;
	पूर्ण अन्यथा अणु
		bnxt_clear_ring_indices(bp);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_mem(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	पूर्णांक i, j, rc, size, arr_size;
	व्योम *bnapi;

	अगर (irq_re_init) अणु
		/* Allocate bnapi mem poपूर्णांकer array and mem block क्रम
		 * all queues
		 */
		arr_size = L1_CACHE_ALIGN(माप(काष्ठा bnxt_napi *) *
				bp->cp_nr_rings);
		size = L1_CACHE_ALIGN(माप(काष्ठा bnxt_napi));
		bnapi = kzalloc(arr_size + size * bp->cp_nr_rings, GFP_KERNEL);
		अगर (!bnapi)
			वापस -ENOMEM;

		bp->bnapi = bnapi;
		bnapi += arr_size;
		क्रम (i = 0; i < bp->cp_nr_rings; i++, bnapi += size) अणु
			bp->bnapi[i] = bnapi;
			bp->bnapi[i]->index = i;
			bp->bnapi[i]->bp = bp;
			अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
				काष्ठा bnxt_cp_ring_info *cpr =
					&bp->bnapi[i]->cp_ring;

				cpr->cp_ring_काष्ठा.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			पूर्ण
		पूर्ण

		bp->rx_ring = kसुस्मृति(bp->rx_nr_rings,
				      माप(काष्ठा bnxt_rx_ring_info),
				      GFP_KERNEL);
		अगर (!bp->rx_ring)
			वापस -ENOMEM;

		क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
			काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];

			अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
				rxr->rx_ring_काष्ठा.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
				rxr->rx_agg_ring_काष्ठा.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			पूर्ण
			rxr->bnapi = bp->bnapi[i];
			bp->bnapi[i]->rx_ring = &bp->rx_ring[i];
		पूर्ण

		bp->tx_ring = kसुस्मृति(bp->tx_nr_rings,
				      माप(काष्ठा bnxt_tx_ring_info),
				      GFP_KERNEL);
		अगर (!bp->tx_ring)
			वापस -ENOMEM;

		bp->tx_ring_map = kसुस्मृति(bp->tx_nr_rings, माप(u16),
					  GFP_KERNEL);

		अगर (!bp->tx_ring_map)
			वापस -ENOMEM;

		अगर (bp->flags & BNXT_FLAG_SHARED_RINGS)
			j = 0;
		अन्यथा
			j = bp->rx_nr_rings;

		क्रम (i = 0; i < bp->tx_nr_rings; i++, j++) अणु
			काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];

			अगर (bp->flags & BNXT_FLAG_CHIP_P5)
				txr->tx_ring_काष्ठा.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			txr->bnapi = bp->bnapi[j];
			bp->bnapi[j]->tx_ring = txr;
			bp->tx_ring_map[i] = bp->tx_nr_rings_xdp + i;
			अगर (i >= bp->tx_nr_rings_xdp) अणु
				txr->txq_index = i - bp->tx_nr_rings_xdp;
				bp->bnapi[j]->tx_पूर्णांक = bnxt_tx_पूर्णांक;
			पूर्ण अन्यथा अणु
				bp->bnapi[j]->flags |= BNXT_NAPI_FLAG_XDP;
				bp->bnapi[j]->tx_पूर्णांक = bnxt_tx_पूर्णांक_xdp;
			पूर्ण
		पूर्ण

		rc = bnxt_alloc_stats(bp);
		अगर (rc)
			जाओ alloc_mem_err;
		bnxt_init_stats(bp);

		rc = bnxt_alloc_ntp_fltrs(bp);
		अगर (rc)
			जाओ alloc_mem_err;

		rc = bnxt_alloc_vnics(bp);
		अगर (rc)
			जाओ alloc_mem_err;
	पूर्ण

	bnxt_init_ring_काष्ठा(bp);

	rc = bnxt_alloc_rx_rings(bp);
	अगर (rc)
		जाओ alloc_mem_err;

	rc = bnxt_alloc_tx_rings(bp);
	अगर (rc)
		जाओ alloc_mem_err;

	rc = bnxt_alloc_cp_rings(bp);
	अगर (rc)
		जाओ alloc_mem_err;

	bp->vnic_info[0].flags |= BNXT_VNIC_RSS_FLAG | BNXT_VNIC_MCAST_FLAG |
				  BNXT_VNIC_UCAST_FLAG;
	rc = bnxt_alloc_vnic_attributes(bp);
	अगर (rc)
		जाओ alloc_mem_err;
	वापस 0;

alloc_mem_err:
	bnxt_मुक्त_mem(bp, true);
	वापस rc;
पूर्ण

अटल व्योम bnxt_disable_पूर्णांक(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		काष्ठा bnxt_ring_काष्ठा *ring = &cpr->cp_ring_काष्ठा;

		अगर (ring->fw_ring_id != INVALID_HW_RING_ID)
			bnxt_db_nq(bp, &cpr->cp_db, cpr->cp_raw_cons);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_cp_num_to_irq_num(काष्ठा bnxt *bp, पूर्णांक n)
अणु
	काष्ठा bnxt_napi *bnapi = bp->bnapi[n];
	काष्ठा bnxt_cp_ring_info *cpr;

	cpr = &bnapi->cp_ring;
	वापस cpr->cp_ring_काष्ठा.map_idx;
पूर्ण

अटल व्योम bnxt_disable_पूर्णांक_sync(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->irq_tbl)
		वापस;

	atomic_inc(&bp->पूर्णांकr_sem);

	bnxt_disable_पूर्णांक(bp);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		पूर्णांक map_idx = bnxt_cp_num_to_irq_num(bp, i);

		synchronize_irq(bp->irq_tbl[map_idx].vector);
	पूर्ण
पूर्ण

अटल व्योम bnxt_enable_पूर्णांक(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	atomic_set(&bp->पूर्णांकr_sem, 0);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		bnxt_db_nq_arm(bp, &cpr->cp_db, cpr->cp_raw_cons);
	पूर्ण
पूर्ण

व्योम bnxt_hwrm_cmd_hdr_init(काष्ठा bnxt *bp, व्योम *request, u16 req_type,
			    u16 cmpl_ring, u16 target_id)
अणु
	काष्ठा input *req = request;

	req->req_type = cpu_to_le16(req_type);
	req->cmpl_ring = cpu_to_le16(cmpl_ring);
	req->target_id = cpu_to_le16(target_id);
	अगर (bnxt_kong_hwrm_message(bp, req))
		req->resp_addr = cpu_to_le64(bp->hwrm_cmd_kong_resp_dma_addr);
	अन्यथा
		req->resp_addr = cpu_to_le64(bp->hwrm_cmd_resp_dma_addr);
पूर्ण

अटल पूर्णांक bnxt_hwrm_to_मानक_त्रुटि(u32 hwrm_err)
अणु
	चयन (hwrm_err) अणु
	हाल HWRM_ERR_CODE_SUCCESS:
		वापस 0;
	हाल HWRM_ERR_CODE_RESOURCE_LOCKED:
		वापस -EROFS;
	हाल HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED:
		वापस -EACCES;
	हाल HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR:
		वापस -ENOSPC;
	हाल HWRM_ERR_CODE_INVALID_PARAMS:
	हाल HWRM_ERR_CODE_INVALID_FLAGS:
	हाल HWRM_ERR_CODE_INVALID_ENABLES:
	हाल HWRM_ERR_CODE_UNSUPPORTED_TLV:
	हाल HWRM_ERR_CODE_UNSUPPORTED_OPTION_ERR:
		वापस -EINVAL;
	हाल HWRM_ERR_CODE_NO_BUFFER:
		वापस -ENOMEM;
	हाल HWRM_ERR_CODE_HOT_RESET_PROGRESS:
	हाल HWRM_ERR_CODE_BUSY:
		वापस -EAGAIN;
	हाल HWRM_ERR_CODE_CMD_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_hwrm_करो_send_msg(काष्ठा bnxt *bp, व्योम *msg, u32 msg_len,
				 पूर्णांक समयout, bool silent)
अणु
	पूर्णांक i, पूर्णांकr_process, rc, पंचांगo_count;
	काष्ठा input *req = msg;
	u32 *data = msg;
	u8 *valid;
	u16 cp_ring_id, len = 0;
	काष्ठा hwrm_err_output *resp = bp->hwrm_cmd_resp_addr;
	u16 max_req_len = BNXT_HWRM_MAX_REQ_LEN;
	काष्ठा hwrm_लघु_input लघु_input = अणु0पूर्ण;
	u32 करोorbell_offset = BNXT_GRCPF_REG_CHIMP_COMM_TRIGGER;
	u32 bar_offset = BNXT_GRCPF_REG_CHIMP_COMM;
	u16 dst = BNXT_HWRM_CHNL_CHIMP;

	अगर (BNXT_NO_FW_ACCESS(bp) &&
	    le16_to_cpu(req->req_type) != HWRM_FUNC_RESET)
		वापस -EBUSY;

	अगर (msg_len > BNXT_HWRM_MAX_REQ_LEN) अणु
		अगर (msg_len > bp->hwrm_max_ext_req_len ||
		    !bp->hwrm_लघु_cmd_req_addr)
			वापस -EINVAL;
	पूर्ण

	अगर (bnxt_hwrm_kong_chnl(bp, req)) अणु
		dst = BNXT_HWRM_CHNL_KONG;
		bar_offset = BNXT_GRCPF_REG_KONG_COMM;
		करोorbell_offset = BNXT_GRCPF_REG_KONG_COMM_TRIGGER;
		resp = bp->hwrm_cmd_kong_resp_addr;
	पूर्ण

	स_रखो(resp, 0, PAGE_SIZE);
	cp_ring_id = le16_to_cpu(req->cmpl_ring);
	पूर्णांकr_process = (cp_ring_id == INVALID_HW_RING_ID) ? 0 : 1;

	req->seq_id = cpu_to_le16(bnxt_get_hwrm_seq_id(bp, dst));
	/* currently supports only one outstanding message */
	अगर (पूर्णांकr_process)
		bp->hwrm_पूर्णांकr_seq_id = le16_to_cpu(req->seq_id);

	अगर ((bp->fw_cap & BNXT_FW_CAP_SHORT_CMD) ||
	    msg_len > BNXT_HWRM_MAX_REQ_LEN) अणु
		व्योम *लघु_cmd_req = bp->hwrm_लघु_cmd_req_addr;
		u16 max_msg_len;

		/* Set boundary क्रम maximum extended request length क्रम लघु
		 * cmd क्रमmat. If passed up from device use the max supported
		 * पूर्णांकernal req length.
		 */
		max_msg_len = bp->hwrm_max_ext_req_len;

		स_नकल(लघु_cmd_req, req, msg_len);
		अगर (msg_len < max_msg_len)
			स_रखो(लघु_cmd_req + msg_len, 0,
			       max_msg_len - msg_len);

		लघु_input.req_type = req->req_type;
		लघु_input.signature =
				cpu_to_le16(SHORT_REQ_SIGNATURE_SHORT_CMD);
		लघु_input.size = cpu_to_le16(msg_len);
		लघु_input.req_addr =
			cpu_to_le64(bp->hwrm_लघु_cmd_req_dma_addr);

		data = (u32 *)&लघु_input;
		msg_len = माप(लघु_input);

		/* Sync memory ग_लिखो beक्रमe updating करोorbell */
		wmb();

		max_req_len = BNXT_HWRM_SHORT_REQ_LEN;
	पूर्ण

	/* Write request msg to hwrm channel */
	__ioग_लिखो32_copy(bp->bar0 + bar_offset, data, msg_len / 4);

	क्रम (i = msg_len; i < max_req_len; i += 4)
		ग_लिखोl(0, bp->bar0 + bar_offset + i);

	/* Ring channel करोorbell */
	ग_लिखोl(1, bp->bar0 + करोorbell_offset);

	अगर (!pci_is_enabled(bp->pdev))
		वापस -ENODEV;

	अगर (!समयout)
		समयout = DFLT_HWRM_CMD_TIMEOUT;
	/* Limit समयout to an upper limit */
	समयout = min(समयout, HWRM_CMD_MAX_TIMEOUT);
	/* convert समयout to usec */
	समयout *= 1000;

	i = 0;
	/* Short समयout क्रम the first few iterations:
	 * number of loops = number of loops क्रम लघु समयout +
	 * number of loops क्रम standard समयout.
	 */
	पंचांगo_count = HWRM_SHORT_TIMEOUT_COUNTER;
	समयout = समयout - HWRM_SHORT_MIN_TIMEOUT * HWRM_SHORT_TIMEOUT_COUNTER;
	पंचांगo_count += DIV_ROUND_UP(समयout, HWRM_MIN_TIMEOUT);

	अगर (पूर्णांकr_process) अणु
		u16 seq_id = bp->hwrm_पूर्णांकr_seq_id;

		/* Wait until hwrm response cmpl पूर्णांकerrupt is processed */
		जबतक (bp->hwrm_पूर्णांकr_seq_id != (u16)~seq_id &&
		       i++ < पंचांगo_count) अणु
			/* Abort the रुको क्रम completion अगर the FW health
			 * check has failed.
			 */
			अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
				वापस -EBUSY;
			/* on first few passes, just barely sleep */
			अगर (i < HWRM_SHORT_TIMEOUT_COUNTER) अणु
				usleep_range(HWRM_SHORT_MIN_TIMEOUT,
					     HWRM_SHORT_MAX_TIMEOUT);
			पूर्ण अन्यथा अणु
				अगर (HWRM_WAIT_MUST_ABORT(bp, req))
					अवरोध;
				usleep_range(HWRM_MIN_TIMEOUT,
					     HWRM_MAX_TIMEOUT);
			पूर्ण
		पूर्ण

		अगर (bp->hwrm_पूर्णांकr_seq_id != (u16)~seq_id) अणु
			अगर (!silent)
				netdev_err(bp->dev, "Resp cmpl intr err msg: 0x%x\n",
					   le16_to_cpu(req->req_type));
			वापस -EBUSY;
		पूर्ण
		len = le16_to_cpu(resp->resp_len);
		valid = ((u8 *)resp) + len - 1;
	पूर्ण अन्यथा अणु
		पूर्णांक j;

		/* Check अगर response len is updated */
		क्रम (i = 0; i < पंचांगo_count; i++) अणु
			/* Abort the रुको क्रम completion अगर the FW health
			 * check has failed.
			 */
			अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
				वापस -EBUSY;
			len = le16_to_cpu(resp->resp_len);
			अगर (len)
				अवरोध;
			/* on first few passes, just barely sleep */
			अगर (i < HWRM_SHORT_TIMEOUT_COUNTER) अणु
				usleep_range(HWRM_SHORT_MIN_TIMEOUT,
					     HWRM_SHORT_MAX_TIMEOUT);
			पूर्ण अन्यथा अणु
				अगर (HWRM_WAIT_MUST_ABORT(bp, req))
					जाओ समयout_पात;
				usleep_range(HWRM_MIN_TIMEOUT,
					     HWRM_MAX_TIMEOUT);
			पूर्ण
		पूर्ण

		अगर (i >= पंचांगo_count) अणु
समयout_पात:
			अगर (!silent)
				netdev_err(bp->dev, "Error (timeout: %d) msg {0x%x 0x%x} len:%d\n",
					   HWRM_TOTAL_TIMEOUT(i),
					   le16_to_cpu(req->req_type),
					   le16_to_cpu(req->seq_id), len);
			वापस -EBUSY;
		पूर्ण

		/* Last byte of resp contains valid bit */
		valid = ((u8 *)resp) + len - 1;
		क्रम (j = 0; j < HWRM_VALID_BIT_DELAY_USEC; j++) अणु
			/* make sure we पढ़ो from updated DMA memory */
			dma_rmb();
			अगर (*valid)
				अवरोध;
			usleep_range(1, 5);
		पूर्ण

		अगर (j >= HWRM_VALID_BIT_DELAY_USEC) अणु
			अगर (!silent)
				netdev_err(bp->dev, "Error (timeout: %d) msg {0x%x 0x%x} len:%d v:%d\n",
					   HWRM_TOTAL_TIMEOUT(i),
					   le16_to_cpu(req->req_type),
					   le16_to_cpu(req->seq_id), len,
					   *valid);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Zero valid bit क्रम compatibility.  Valid bit in an older spec
	 * may become a new field in a newer spec.  We must make sure that
	 * a new field not implemented by old spec will पढ़ो zero.
	 */
	*valid = 0;
	rc = le16_to_cpu(resp->error_code);
	अगर (rc && !silent)
		netdev_err(bp->dev, "hwrm req_type 0x%x seq id 0x%x error 0x%x\n",
			   le16_to_cpu(resp->req_type),
			   le16_to_cpu(resp->seq_id), rc);
	वापस bnxt_hwrm_to_मानक_त्रुटि(rc);
पूर्ण

पूर्णांक _hwrm_send_message(काष्ठा bnxt *bp, व्योम *msg, u32 msg_len, पूर्णांक समयout)
अणु
	वापस bnxt_hwrm_करो_send_msg(bp, msg, msg_len, समयout, false);
पूर्ण

पूर्णांक _hwrm_send_message_silent(काष्ठा bnxt *bp, व्योम *msg, u32 msg_len,
			      पूर्णांक समयout)
अणु
	वापस bnxt_hwrm_करो_send_msg(bp, msg, msg_len, समयout, true);
पूर्ण

पूर्णांक hwrm_send_message(काष्ठा bnxt *bp, व्योम *msg, u32 msg_len, पूर्णांक समयout)
अणु
	पूर्णांक rc;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, msg, msg_len, समयout);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

पूर्णांक hwrm_send_message_silent(काष्ठा bnxt *bp, व्योम *msg, u32 msg_len,
			     पूर्णांक समयout)
अणु
	पूर्णांक rc;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = bnxt_hwrm_करो_send_msg(bp, msg, msg_len, समयout, true);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

पूर्णांक bnxt_hwrm_func_drv_rgtr(काष्ठा bnxt *bp, अचिन्हित दीर्घ *bmap, पूर्णांक bmap_size,
			    bool async_only)
अणु
	काष्ठा hwrm_func_drv_rgtr_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_drv_rgtr_input req = अणु0पूर्ण;
	DECLARE_BITMAP(async_events_bmap, 256);
	u32 *events = (u32 *)async_events_bmap;
	u32 flags;
	पूर्णांक rc, i;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_DRV_RGTR, -1, -1);

	req.enables =
		cpu_to_le32(FUNC_DRV_RGTR_REQ_ENABLES_OS_TYPE |
			    FUNC_DRV_RGTR_REQ_ENABLES_VER |
			    FUNC_DRV_RGTR_REQ_ENABLES_ASYNC_EVENT_FWD);

	req.os_type = cpu_to_le16(FUNC_DRV_RGTR_REQ_OS_TYPE_LINUX);
	flags = FUNC_DRV_RGTR_REQ_FLAGS_16BIT_VER_MODE;
	अगर (bp->fw_cap & BNXT_FW_CAP_HOT_RESET)
		flags |= FUNC_DRV_RGTR_REQ_FLAGS_HOT_RESET_SUPPORT;
	अगर (bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY)
		flags |= FUNC_DRV_RGTR_REQ_FLAGS_ERROR_RECOVERY_SUPPORT |
			 FUNC_DRV_RGTR_REQ_FLAGS_MASTER_SUPPORT;
	req.flags = cpu_to_le32(flags);
	req.ver_maj_8b = DRV_VER_MAJ;
	req.ver_min_8b = DRV_VER_MIN;
	req.ver_upd_8b = DRV_VER_UPD;
	req.ver_maj = cpu_to_le16(DRV_VER_MAJ);
	req.ver_min = cpu_to_le16(DRV_VER_MIN);
	req.ver_upd = cpu_to_le16(DRV_VER_UPD);

	अगर (BNXT_PF(bp)) अणु
		u32 data[8];
		पूर्णांक i;

		स_रखो(data, 0, माप(data));
		क्रम (i = 0; i < ARRAY_SIZE(bnxt_vf_req_snअगर); i++) अणु
			u16 cmd = bnxt_vf_req_snअगर[i];
			अचिन्हित पूर्णांक bit, idx;

			idx = cmd / 32;
			bit = cmd % 32;
			data[idx] |= 1 << bit;
		पूर्ण

		क्रम (i = 0; i < 8; i++)
			req.vf_req_fwd[i] = cpu_to_le32(data[i]);

		req.enables |=
			cpu_to_le32(FUNC_DRV_RGTR_REQ_ENABLES_VF_REQ_FWD);
	पूर्ण

	अगर (bp->fw_cap & BNXT_FW_CAP_OVS_64BIT_HANDLE)
		req.flags |= cpu_to_le32(
			FUNC_DRV_RGTR_REQ_FLAGS_FLOW_HANDLE_64BIT_MODE);

	स_रखो(async_events_bmap, 0, माप(async_events_bmap));
	क्रम (i = 0; i < ARRAY_SIZE(bnxt_async_events_arr); i++) अणु
		u16 event_id = bnxt_async_events_arr[i];

		अगर (event_id == ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY &&
		    !(bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY))
			जारी;
		__set_bit(bnxt_async_events_arr[i], async_events_bmap);
	पूर्ण
	अगर (bmap && bmap_size) अणु
		क्रम (i = 0; i < bmap_size; i++) अणु
			अगर (test_bit(i, bmap))
				__set_bit(i, async_events_bmap);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 8; i++)
		req.async_event_fwd[i] |= cpu_to_le32(events[i]);

	अगर (async_only)
		req.enables =
			cpu_to_le32(FUNC_DRV_RGTR_REQ_ENABLES_ASYNC_EVENT_FWD);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		set_bit(BNXT_STATE_DRV_REGISTERED, &bp->state);
		अगर (resp->flags &
		    cpu_to_le32(FUNC_DRV_RGTR_RESP_FLAGS_IF_CHANGE_SUPPORTED))
			bp->fw_cap |= BNXT_FW_CAP_IF_CHANGE;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_drv_unrgtr(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_drv_unrgtr_input req = अणु0पूर्ण;

	अगर (!test_and_clear_bit(BNXT_STATE_DRV_REGISTERED, &bp->state))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_DRV_UNRGTR, -1, -1);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_tunnel_dst_port_मुक्त(काष्ठा bnxt *bp, u8 tunnel_type)
अणु
	u32 rc = 0;
	काष्ठा hwrm_tunnel_dst_port_मुक्त_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_TUNNEL_DST_PORT_FREE, -1, -1);
	req.tunnel_type = tunnel_type;

	चयन (tunnel_type) अणु
	हाल TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN:
		req.tunnel_dst_port_id = cpu_to_le16(bp->vxlan_fw_dst_port_id);
		bp->vxlan_fw_dst_port_id = INVALID_HW_RING_ID;
		अवरोध;
	हाल TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE:
		req.tunnel_dst_port_id = cpu_to_le16(bp->nge_fw_dst_port_id);
		bp->nge_fw_dst_port_id = INVALID_HW_RING_ID;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_err(bp->dev, "hwrm_tunnel_dst_port_free failed. rc:%d\n",
			   rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_tunnel_dst_port_alloc(काष्ठा bnxt *bp, __be16 port,
					   u8 tunnel_type)
अणु
	u32 rc = 0;
	काष्ठा hwrm_tunnel_dst_port_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_tunnel_dst_port_alloc_output *resp = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_TUNNEL_DST_PORT_ALLOC, -1, -1);

	req.tunnel_type = tunnel_type;
	req.tunnel_dst_port_val = port;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm_tunnel_dst_port_alloc failed. rc:%d\n",
			   rc);
		जाओ err_out;
	पूर्ण

	चयन (tunnel_type) अणु
	हाल TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_VXLAN:
		bp->vxlan_fw_dst_port_id =
			le16_to_cpu(resp->tunnel_dst_port_id);
		अवरोध;
	हाल TUNNEL_DST_PORT_ALLOC_REQ_TUNNEL_TYPE_GENEVE:
		bp->nge_fw_dst_port_id = le16_to_cpu(resp->tunnel_dst_port_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

err_out:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_cfa_l2_set_rx_mask(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	काष्ठा hwrm_cfa_l2_set_rx_mask_input req = अणु0पूर्ण;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_L2_SET_RX_MASK, -1, -1);
	req.vnic_id = cpu_to_le32(vnic->fw_vnic_id);

	req.num_mc_entries = cpu_to_le32(vnic->mc_list_count);
	req.mc_tbl_addr = cpu_to_le64(vnic->mc_list_mapping);
	req.mask = cpu_to_le32(vnic->rx_mask);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल पूर्णांक bnxt_hwrm_cfa_ntuple_filter_मुक्त(काष्ठा bnxt *bp,
					    काष्ठा bnxt_ntuple_filter *fltr)
अणु
	काष्ठा hwrm_cfa_ntuple_filter_मुक्त_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_NTUPLE_FILTER_FREE, -1, -1);
	req.ntuple_filter_id = fltr->filter_id;
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

#घोषणा BNXT_NTP_FLTR_FLAGS					\
	(CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_L2_FILTER_ID |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_ETHERTYPE |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_MACADDR |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_IPADDR_TYPE |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR_MASK |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR_MASK |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_IP_PROTOCOL |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_PORT |		\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_SRC_PORT_MASK |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_PORT |		\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_PORT_MASK |	\
	 CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_DST_ID)

#घोषणा BNXT_NTP_TUNNEL_FLTR_FLAG				\
		CFA_NTUPLE_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE

अटल पूर्णांक bnxt_hwrm_cfa_ntuple_filter_alloc(काष्ठा bnxt *bp,
					     काष्ठा bnxt_ntuple_filter *fltr)
अणु
	काष्ठा hwrm_cfa_ntuple_filter_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_cfa_ntuple_filter_alloc_output *resp;
	काष्ठा flow_keys *keys = &fltr->fkeys;
	काष्ठा bnxt_vnic_info *vnic;
	u32 flags = 0;
	पूर्णांक rc = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_NTUPLE_FILTER_ALLOC, -1, -1);
	req.l2_filter_id = bp->vnic_info[0].fw_l2_filter_id[fltr->l2_fltr_idx];

	अगर (bp->fw_cap & BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX_V2) अणु
		flags = CFA_NTUPLE_FILTER_ALLOC_REQ_FLAGS_DEST_RFS_RING_IDX;
		req.dst_id = cpu_to_le16(fltr->rxq);
	पूर्ण अन्यथा अणु
		vnic = &bp->vnic_info[fltr->rxq + 1];
		req.dst_id = cpu_to_le16(vnic->fw_vnic_id);
	पूर्ण
	req.flags = cpu_to_le32(flags);
	req.enables = cpu_to_le32(BNXT_NTP_FLTR_FLAGS);

	req.ethertype = htons(ETH_P_IP);
	स_नकल(req.src_macaddr, fltr->src_mac_addr, ETH_ALEN);
	req.ip_addr_type = CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV4;
	req.ip_protocol = keys->basic.ip_proto;

	अगर (keys->basic.n_proto == htons(ETH_P_IPV6)) अणु
		पूर्णांक i;

		req.ethertype = htons(ETH_P_IPV6);
		req.ip_addr_type =
			CFA_NTUPLE_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV6;
		*(काष्ठा in6_addr *)&req.src_ipaddr[0] =
			keys->addrs.v6addrs.src;
		*(काष्ठा in6_addr *)&req.dst_ipaddr[0] =
			keys->addrs.v6addrs.dst;
		क्रम (i = 0; i < 4; i++) अणु
			req.src_ipaddr_mask[i] = cpu_to_be32(0xffffffff);
			req.dst_ipaddr_mask[i] = cpu_to_be32(0xffffffff);
		पूर्ण
	पूर्ण अन्यथा अणु
		req.src_ipaddr[0] = keys->addrs.v4addrs.src;
		req.src_ipaddr_mask[0] = cpu_to_be32(0xffffffff);
		req.dst_ipaddr[0] = keys->addrs.v4addrs.dst;
		req.dst_ipaddr_mask[0] = cpu_to_be32(0xffffffff);
	पूर्ण
	अगर (keys->control.flags & FLOW_DIS_ENCAPSULATION) अणु
		req.enables |= cpu_to_le32(BNXT_NTP_TUNNEL_FLTR_FLAG);
		req.tunnel_type =
			CFA_NTUPLE_FILTER_ALLOC_REQ_TUNNEL_TYPE_ANYTUNNEL;
	पूर्ण

	req.src_port = keys->ports.src;
	req.src_port_mask = cpu_to_be16(0xffff);
	req.dst_port = keys->ports.dst;
	req.dst_port_mask = cpu_to_be16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		resp = bnxt_get_hwrm_resp_addr(bp, &req);
		fltr->filter_id = resp->ntuple_filter_id;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bnxt_hwrm_set_vnic_filter(काष्ठा bnxt *bp, u16 vnic_id, u16 idx,
				     u8 *mac_addr)
अणु
	u32 rc = 0;
	काष्ठा hwrm_cfa_l2_filter_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_cfa_l2_filter_alloc_output *resp = bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_L2_FILTER_ALLOC, -1, -1);
	req.flags = cpu_to_le32(CFA_L2_FILTER_ALLOC_REQ_FLAGS_PATH_RX);
	अगर (!BNXT_CHIP_TYPE_NITRO_A0(bp))
		req.flags |=
			cpu_to_le32(CFA_L2_FILTER_ALLOC_REQ_FLAGS_OUTERMOST);
	req.dst_id = cpu_to_le16(bp->vnic_info[vnic_id].fw_vnic_id);
	req.enables =
		cpu_to_le32(CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_ADDR |
			    CFA_L2_FILTER_ALLOC_REQ_ENABLES_DST_ID |
			    CFA_L2_FILTER_ALLOC_REQ_ENABLES_L2_ADDR_MASK);
	स_नकल(req.l2_addr, mac_addr, ETH_ALEN);
	req.l2_addr_mask[0] = 0xff;
	req.l2_addr_mask[1] = 0xff;
	req.l2_addr_mask[2] = 0xff;
	req.l2_addr_mask[3] = 0xff;
	req.l2_addr_mask[4] = 0xff;
	req.l2_addr_mask[5] = 0xff;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		bp->vnic_info[vnic_id].fw_l2_filter_id[idx] =
							resp->l2_filter_id;
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_clear_vnic_filter(काष्ठा bnxt *bp)
अणु
	u16 i, j, num_of_vnics = 1; /* only vnic 0 supported */
	पूर्णांक rc = 0;

	/* Any associated ntuple filters will also be cleared by firmware. */
	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < num_of_vnics; i++) अणु
		काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[i];

		क्रम (j = 0; j < vnic->uc_filter_count; j++) अणु
			काष्ठा hwrm_cfa_l2_filter_मुक्त_input req = अणु0पूर्ण;

			bnxt_hwrm_cmd_hdr_init(bp, &req,
					       HWRM_CFA_L2_FILTER_FREE, -1, -1);

			req.l2_filter_id = vnic->fw_l2_filter_id[j];

			rc = _hwrm_send_message(bp, &req, माप(req),
						HWRM_CMD_TIMEOUT);
		पूर्ण
		vnic->uc_filter_count = 0;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_set_tpa(काष्ठा bnxt *bp, u16 vnic_id, u32 tpa_flags)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	u16 max_aggs = VNIC_TPA_CFG_REQ_MAX_AGGS_MAX;
	काष्ठा hwrm_vnic_tpa_cfg_input req = अणु0पूर्ण;

	अगर (vnic->fw_vnic_id == INVALID_HW_RING_ID)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_TPA_CFG, -1, -1);

	अगर (tpa_flags) अणु
		u16 mss = bp->dev->mtu - 40;
		u32 nsegs, n, segs = 0, flags;

		flags = VNIC_TPA_CFG_REQ_FLAGS_TPA |
			VNIC_TPA_CFG_REQ_FLAGS_ENCAP_TPA |
			VNIC_TPA_CFG_REQ_FLAGS_RSC_WND_UPDATE |
			VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_ECN |
			VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_SAME_GRE_SEQ;
		अगर (tpa_flags & BNXT_FLAG_GRO)
			flags |= VNIC_TPA_CFG_REQ_FLAGS_GRO;

		req.flags = cpu_to_le32(flags);

		req.enables =
			cpu_to_le32(VNIC_TPA_CFG_REQ_ENABLES_MAX_AGG_SEGS |
				    VNIC_TPA_CFG_REQ_ENABLES_MAX_AGGS |
				    VNIC_TPA_CFG_REQ_ENABLES_MIN_AGG_LEN);

		/* Number of segs are log2 units, and first packet is not
		 * included as part of this units.
		 */
		अगर (mss <= BNXT_RX_PAGE_SIZE) अणु
			n = BNXT_RX_PAGE_SIZE / mss;
			nsegs = (MAX_SKB_FRAGS - 1) * n;
		पूर्ण अन्यथा अणु
			n = mss / BNXT_RX_PAGE_SIZE;
			अगर (mss & (BNXT_RX_PAGE_SIZE - 1))
				n++;
			nsegs = (MAX_SKB_FRAGS - n) / n;
		पूर्ण

		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			segs = MAX_TPA_SEGS_P5;
			max_aggs = bp->max_tpa;
		पूर्ण अन्यथा अणु
			segs = ilog2(nsegs);
		पूर्ण
		req.max_agg_segs = cpu_to_le16(segs);
		req.max_aggs = cpu_to_le16(max_aggs);

		req.min_agg_len = cpu_to_le32(512);
	पूर्ण
	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल u16 bnxt_cp_ring_from_grp(काष्ठा bnxt *bp, काष्ठा bnxt_ring_काष्ठा *ring)
अणु
	काष्ठा bnxt_ring_grp_info *grp_info;

	grp_info = &bp->grp_info[ring->grp_idx];
	वापस grp_info->cp_fw_ring_id;
पूर्ण

अटल u16 bnxt_cp_ring_क्रम_rx(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		काष्ठा bnxt_napi *bnapi = rxr->bnapi;
		काष्ठा bnxt_cp_ring_info *cpr;

		cpr = bnapi->cp_ring.cp_ring_arr[BNXT_RX_HDL];
		वापस cpr->cp_ring_काष्ठा.fw_ring_id;
	पूर्ण अन्यथा अणु
		वापस bnxt_cp_ring_from_grp(bp, &rxr->rx_ring_काष्ठा);
	पूर्ण
पूर्ण

अटल u16 bnxt_cp_ring_क्रम_tx(काष्ठा bnxt *bp, काष्ठा bnxt_tx_ring_info *txr)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		काष्ठा bnxt_napi *bnapi = txr->bnapi;
		काष्ठा bnxt_cp_ring_info *cpr;

		cpr = bnapi->cp_ring.cp_ring_arr[BNXT_TX_HDL];
		वापस cpr->cp_ring_काष्ठा.fw_ring_id;
	पूर्ण अन्यथा अणु
		वापस bnxt_cp_ring_from_grp(bp, &txr->tx_ring_काष्ठा);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_alloc_rss_indir_tbl(काष्ठा bnxt *bp)
अणु
	पूर्णांक entries;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		entries = BNXT_MAX_RSS_TABLE_ENTRIES_P5;
	अन्यथा
		entries = HW_HASH_INDEX_SIZE;

	bp->rss_indir_tbl_entries = entries;
	bp->rss_indir_tbl = kदो_स्मृति_array(entries, माप(*bp->rss_indir_tbl),
					  GFP_KERNEL);
	अगर (!bp->rss_indir_tbl)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम bnxt_set_dflt_rss_indir_tbl(काष्ठा bnxt *bp)
अणु
	u16 max_rings, max_entries, pad, i;

	अगर (!bp->rx_nr_rings)
		वापस;

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		max_rings = bp->rx_nr_rings - 1;
	अन्यथा
		max_rings = bp->rx_nr_rings;

	max_entries = bnxt_get_rxfh_indir_size(bp->dev);

	क्रम (i = 0; i < max_entries; i++)
		bp->rss_indir_tbl[i] = ethtool_rxfh_indir_शेष(i, max_rings);

	pad = bp->rss_indir_tbl_entries - max_entries;
	अगर (pad)
		स_रखो(&bp->rss_indir_tbl[i], 0, pad * माप(u16));
पूर्ण

अटल u16 bnxt_get_max_rss_ring(काष्ठा bnxt *bp)
अणु
	u16 i, tbl_size, max_ring = 0;

	अगर (!bp->rss_indir_tbl)
		वापस 0;

	tbl_size = bnxt_get_rxfh_indir_size(bp->dev);
	क्रम (i = 0; i < tbl_size; i++)
		max_ring = max(max_ring, bp->rss_indir_tbl[i]);
	वापस max_ring;
पूर्ण

पूर्णांक bnxt_get_nr_rss_ctxs(काष्ठा bnxt *bp, पूर्णांक rx_rings)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस DIV_ROUND_UP(rx_rings, BNXT_RSS_TABLE_ENTRIES_P5);
	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		वापस 2;
	वापस 1;
पूर्ण

अटल व्योम __bnxt_fill_hw_rss_tbl(काष्ठा bnxt *bp, काष्ठा bnxt_vnic_info *vnic)
अणु
	bool no_rss = !(vnic->flags & BNXT_VNIC_RSS_FLAG);
	u16 i, j;

	/* Fill the RSS indirection table with ring group ids */
	क्रम (i = 0, j = 0; i < HW_HASH_INDEX_SIZE; i++) अणु
		अगर (!no_rss)
			j = bp->rss_indir_tbl[i];
		vnic->rss_table[i] = cpu_to_le16(vnic->fw_grp_ids[j]);
	पूर्ण
पूर्ण

अटल व्योम __bnxt_fill_hw_rss_tbl_p5(काष्ठा bnxt *bp,
				      काष्ठा bnxt_vnic_info *vnic)
अणु
	__le16 *ring_tbl = vnic->rss_table;
	काष्ठा bnxt_rx_ring_info *rxr;
	u16 tbl_size, i;

	tbl_size = bnxt_get_rxfh_indir_size(bp->dev);

	क्रम (i = 0; i < tbl_size; i++) अणु
		u16 ring_id, j;

		j = bp->rss_indir_tbl[i];
		rxr = &bp->rx_ring[j];

		ring_id = rxr->rx_ring_काष्ठा.fw_ring_id;
		*ring_tbl++ = cpu_to_le16(ring_id);
		ring_id = bnxt_cp_ring_क्रम_rx(bp, rxr);
		*ring_tbl++ = cpu_to_le16(ring_id);
	पूर्ण
पूर्ण

अटल व्योम bnxt_fill_hw_rss_tbl(काष्ठा bnxt *bp, काष्ठा bnxt_vnic_info *vnic)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		__bnxt_fill_hw_rss_tbl_p5(bp, vnic);
	अन्यथा
		__bnxt_fill_hw_rss_tbl(bp, vnic);
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_set_rss(काष्ठा bnxt *bp, u16 vnic_id, bool set_rss)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	काष्ठा hwrm_vnic_rss_cfg_input req = अणु0पूर्ण;

	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) ||
	    vnic->fw_rss_cos_lb_ctx[0] == INVALID_HW_RING_ID)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_CFG, -1, -1);
	अगर (set_rss) अणु
		bnxt_fill_hw_rss_tbl(bp, vnic);
		req.hash_type = cpu_to_le32(bp->rss_hash_cfg);
		req.hash_mode_flags = VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT;
		req.ring_grp_tbl_addr = cpu_to_le64(vnic->rss_table_dma_addr);
		req.hash_key_tbl_addr =
			cpu_to_le64(vnic->rss_hash_key_dma_addr);
	पूर्ण
	req.rss_ctx_idx = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[0]);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_set_rss_p5(काष्ठा bnxt *bp, u16 vnic_id, bool set_rss)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	काष्ठा hwrm_vnic_rss_cfg_input req = अणु0पूर्ण;
	dma_addr_t ring_tbl_map;
	u32 i, nr_ctxs;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_CFG, -1, -1);
	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);
	अगर (!set_rss) अणु
		hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		वापस 0;
	पूर्ण
	bnxt_fill_hw_rss_tbl(bp, vnic);
	req.hash_type = cpu_to_le32(bp->rss_hash_cfg);
	req.hash_mode_flags = VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT;
	req.hash_key_tbl_addr = cpu_to_le64(vnic->rss_hash_key_dma_addr);
	ring_tbl_map = vnic->rss_table_dma_addr;
	nr_ctxs = bnxt_get_nr_rss_ctxs(bp, bp->rx_nr_rings);
	क्रम (i = 0; i < nr_ctxs; ring_tbl_map += BNXT_RSS_TABLE_SIZE_P5, i++) अणु
		पूर्णांक rc;

		req.ring_grp_tbl_addr = cpu_to_le64(ring_tbl_map);
		req.ring_table_pair_index = i;
		req.rss_ctx_idx = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[i]);
		rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_set_hds(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	काष्ठा hwrm_vnic_plcmodes_cfg_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_PLCMODES_CFG, -1, -1);
	req.flags = cpu_to_le32(VNIC_PLCMODES_CFG_REQ_FLAGS_JUMBO_PLACEMENT |
				VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV4 |
				VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV6);
	req.enables =
		cpu_to_le32(VNIC_PLCMODES_CFG_REQ_ENABLES_JUMBO_THRESH_VALID |
			    VNIC_PLCMODES_CFG_REQ_ENABLES_HDS_THRESHOLD_VALID);
	/* thresholds not implemented in firmware yet */
	req.jumbo_thresh = cpu_to_le16(bp->rx_copy_thresh);
	req.hds_threshold = cpu_to_le16(bp->rx_copy_thresh);
	req.vnic_id = cpu_to_le32(vnic->fw_vnic_id);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल व्योम bnxt_hwrm_vnic_ctx_मुक्त_one(काष्ठा bnxt *bp, u16 vnic_id,
					u16 ctx_idx)
अणु
	काष्ठा hwrm_vnic_rss_cos_lb_ctx_मुक्त_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_COS_LB_CTX_FREE, -1, -1);
	req.rss_cos_lb_ctx_id =
		cpu_to_le16(bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[ctx_idx]);

	hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[ctx_idx] = INVALID_HW_RING_ID;
पूर्ण

अटल व्योम bnxt_hwrm_vnic_ctx_मुक्त(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < bp->nr_vnics; i++) अणु
		काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[i];

		क्रम (j = 0; j < BNXT_MAX_CTX_PER_VNIC; j++) अणु
			अगर (vnic->fw_rss_cos_lb_ctx[j] != INVALID_HW_RING_ID)
				bnxt_hwrm_vnic_ctx_मुक्त_one(bp, i, j);
		पूर्ण
	पूर्ण
	bp->rsscos_nr_ctxs = 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_ctx_alloc(काष्ठा bnxt *bp, u16 vnic_id, u16 ctx_idx)
अणु
	पूर्णांक rc;
	काष्ठा hwrm_vnic_rss_cos_lb_ctx_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_vnic_rss_cos_lb_ctx_alloc_output *resp =
						bp->hwrm_cmd_resp_addr;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_COS_LB_CTX_ALLOC, -1,
			       -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		bp->vnic_info[vnic_id].fw_rss_cos_lb_ctx[ctx_idx] =
			le16_to_cpu(resp->rss_cos_lb_ctx_id);
	mutex_unlock(&bp->hwrm_cmd_lock);

	वापस rc;
पूर्ण

अटल u32 bnxt_get_roce_vnic_mode(काष्ठा bnxt *bp)
अणु
	अगर (bp->flags & BNXT_FLAG_ROCE_MIRROR_CAP)
		वापस VNIC_CFG_REQ_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_MODE;
	वापस VNIC_CFG_REQ_FLAGS_ROCE_DUAL_VNIC_MODE;
पूर्ण

पूर्णांक bnxt_hwrm_vnic_cfg(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	अचिन्हित पूर्णांक ring = 0, grp_idx;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	काष्ठा hwrm_vnic_cfg_input req = अणु0पूर्ण;
	u16 def_vlan = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_CFG, -1, -1);

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[0];

		req.शेष_rx_ring_id =
			cpu_to_le16(rxr->rx_ring_काष्ठा.fw_ring_id);
		req.शेष_cmpl_ring_id =
			cpu_to_le16(bnxt_cp_ring_क्रम_rx(bp, rxr));
		req.enables =
			cpu_to_le32(VNIC_CFG_REQ_ENABLES_DEFAULT_RX_RING_ID |
				    VNIC_CFG_REQ_ENABLES_DEFAULT_CMPL_RING_ID);
		जाओ vnic_mru;
	पूर्ण
	req.enables = cpu_to_le32(VNIC_CFG_REQ_ENABLES_DFLT_RING_GRP);
	/* Only RSS support क्रम now TBD: COS & LB */
	अगर (vnic->fw_rss_cos_lb_ctx[0] != INVALID_HW_RING_ID) अणु
		req.rss_rule = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[0]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_RSS_RULE |
					   VNIC_CFG_REQ_ENABLES_MRU);
	पूर्ण अन्यथा अगर (vnic->flags & BNXT_VNIC_RFS_NEW_RSS_FLAG) अणु
		req.rss_rule =
			cpu_to_le16(bp->vnic_info[0].fw_rss_cos_lb_ctx[0]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_RSS_RULE |
					   VNIC_CFG_REQ_ENABLES_MRU);
		req.flags |= cpu_to_le32(VNIC_CFG_REQ_FLAGS_RSS_DFLT_CR_MODE);
	पूर्ण अन्यथा अणु
		req.rss_rule = cpu_to_le16(0xffff);
	पूर्ण

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp) &&
	    (vnic->fw_rss_cos_lb_ctx[0] != INVALID_HW_RING_ID)) अणु
		req.cos_rule = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[1]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_COS_RULE);
	पूर्ण अन्यथा अणु
		req.cos_rule = cpu_to_le16(0xffff);
	पूर्ण

	अगर (vnic->flags & BNXT_VNIC_RSS_FLAG)
		ring = 0;
	अन्यथा अगर (vnic->flags & BNXT_VNIC_RFS_FLAG)
		ring = vnic_id - 1;
	अन्यथा अगर ((vnic_id == 1) && BNXT_CHIP_TYPE_NITRO_A0(bp))
		ring = bp->rx_nr_rings - 1;

	grp_idx = bp->rx_ring[ring].bnapi->index;
	req.dflt_ring_grp = cpu_to_le16(bp->grp_info[grp_idx].fw_grp_id);
	req.lb_rule = cpu_to_le16(0xffff);
vnic_mru:
	req.mru = cpu_to_le16(bp->dev->mtu + ETH_HLEN + VLAN_HLEN);

	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);
#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (BNXT_VF(bp))
		def_vlan = bp->vf.vlan;
#पूर्ण_अगर
	अगर ((bp->flags & BNXT_FLAG_STRIP_VLAN) || def_vlan)
		req.flags |= cpu_to_le32(VNIC_CFG_REQ_FLAGS_VLAN_STRIP_MODE);
	अगर (!vnic_id && bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP))
		req.flags |= cpu_to_le32(bnxt_get_roce_vnic_mode(bp));

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल व्योम bnxt_hwrm_vnic_मुक्त_one(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	अगर (bp->vnic_info[vnic_id].fw_vnic_id != INVALID_HW_RING_ID) अणु
		काष्ठा hwrm_vnic_मुक्त_input req = अणु0पूर्ण;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_FREE, -1, -1);
		req.vnic_id =
			cpu_to_le32(bp->vnic_info[vnic_id].fw_vnic_id);

		hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		bp->vnic_info[vnic_id].fw_vnic_id = INVALID_HW_RING_ID;
	पूर्ण
पूर्ण

अटल व्योम bnxt_hwrm_vnic_मुक्त(काष्ठा bnxt *bp)
अणु
	u16 i;

	क्रम (i = 0; i < bp->nr_vnics; i++)
		bnxt_hwrm_vnic_मुक्त_one(bp, i);
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_alloc(काष्ठा bnxt *bp, u16 vnic_id,
				अचिन्हित पूर्णांक start_rx_ring_idx,
				अचिन्हित पूर्णांक nr_rings)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक i, j, grp_idx, end_idx = start_rx_ring_idx + nr_rings;
	काष्ठा hwrm_vnic_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_vnic_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		जाओ vnic_no_ring_grps;

	/* map ring groups to this vnic */
	क्रम (i = start_rx_ring_idx, j = 0; i < end_idx; i++, j++) अणु
		grp_idx = bp->rx_ring[i].bnapi->index;
		अगर (bp->grp_info[grp_idx].fw_grp_id == INVALID_HW_RING_ID) अणु
			netdev_err(bp->dev, "Not enough ring groups avail:%x req:%x\n",
				   j, nr_rings);
			अवरोध;
		पूर्ण
		vnic->fw_grp_ids[j] = bp->grp_info[grp_idx].fw_grp_id;
	पूर्ण

vnic_no_ring_grps:
	क्रम (i = 0; i < BNXT_MAX_CTX_PER_VNIC; i++)
		vnic->fw_rss_cos_lb_ctx[i] = INVALID_HW_RING_ID;
	अगर (vnic_id == 0)
		req.flags = cpu_to_le32(VNIC_ALLOC_REQ_FLAGS_DEFAULT);

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_ALLOC, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		vnic->fw_vnic_id = le32_to_cpu(resp->vnic_id);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_vnic_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_vnic_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_vnic_qcaps_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bp->hw_ring_stats_size = माप(काष्ठा ctx_hw_stats);
	bp->flags &= ~(BNXT_FLAG_NEW_RSS_CAP | BNXT_FLAG_ROCE_MIRROR_CAP);
	अगर (bp->hwrm_spec_code < 0x10600)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		u32 flags = le32_to_cpu(resp->flags);

		अगर (!(bp->flags & BNXT_FLAG_CHIP_P5) &&
		    (flags & VNIC_QCAPS_RESP_FLAGS_RSS_DFLT_CR_CAP))
			bp->flags |= BNXT_FLAG_NEW_RSS_CAP;
		अगर (flags &
		    VNIC_QCAPS_RESP_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_CAP)
			bp->flags |= BNXT_FLAG_ROCE_MIRROR_CAP;

		/* Older P5 fw beक्रमe EXT_HW_STATS support did not set
		 * VLAN_STRIP_CAP properly.
		 */
		अगर ((flags & VNIC_QCAPS_RESP_FLAGS_VLAN_STRIP_CAP) ||
		    (BNXT_CHIP_P5_THOR(bp) &&
		     !(bp->fw_cap & BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED)))
			bp->fw_cap |= BNXT_FW_CAP_VLAN_RX_STRIP;
		bp->max_tpa_v2 = le16_to_cpu(resp->max_aggs_supported);
		अगर (bp->max_tpa_v2) अणु
			अगर (BNXT_CHIP_P5_THOR(bp))
				bp->hw_ring_stats_size = BNXT_RING_STATS_SIZE_P5;
			अन्यथा
				bp->hw_ring_stats_size = BNXT_RING_STATS_SIZE_P5_SR2;
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_ring_grp_alloc(काष्ठा bnxt *bp)
अणु
	u16 i;
	u32 rc = 0;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस 0;

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा hwrm_ring_grp_alloc_input req = अणु0पूर्ण;
		काष्ठा hwrm_ring_grp_alloc_output *resp =
					bp->hwrm_cmd_resp_addr;
		अचिन्हित पूर्णांक grp_idx = bp->rx_ring[i].bnapi->index;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_GRP_ALLOC, -1, -1);

		req.cr = cpu_to_le16(bp->grp_info[grp_idx].cp_fw_ring_id);
		req.rr = cpu_to_le16(bp->grp_info[grp_idx].rx_fw_ring_id);
		req.ar = cpu_to_le16(bp->grp_info[grp_idx].agg_fw_ring_id);
		req.sc = cpu_to_le16(bp->grp_info[grp_idx].fw_stats_ctx);

		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;

		bp->grp_info[grp_idx].fw_grp_id =
			le32_to_cpu(resp->ring_group_id);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_hwrm_ring_grp_मुक्त(काष्ठा bnxt *bp)
अणु
	u16 i;
	काष्ठा hwrm_ring_grp_मुक्त_input req = अणु0पूर्ण;

	अगर (!bp->grp_info || (bp->flags & BNXT_FLAG_CHIP_P5))
		वापस;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_GRP_FREE, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		अगर (bp->grp_info[i].fw_grp_id == INVALID_HW_RING_ID)
			जारी;
		req.ring_group_id =
			cpu_to_le32(bp->grp_info[i].fw_grp_id);

		_hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		bp->grp_info[i].fw_grp_id = INVALID_HW_RING_ID;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
पूर्ण

अटल पूर्णांक hwrm_ring_alloc_send_msg(काष्ठा bnxt *bp,
				    काष्ठा bnxt_ring_काष्ठा *ring,
				    u32 ring_type, u32 map_index)
अणु
	पूर्णांक rc = 0, err = 0;
	काष्ठा hwrm_ring_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_ring_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_ring_mem_info *rmem = &ring->ring_mem;
	काष्ठा bnxt_ring_grp_info *grp_info;
	u16 ring_id;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_ALLOC, -1, -1);

	req.enables = 0;
	अगर (rmem->nr_pages > 1) अणु
		req.page_tbl_addr = cpu_to_le64(rmem->pg_tbl_map);
		/* Page size is in log2 units */
		req.page_size = BNXT_PAGE_SHIFT;
		req.page_tbl_depth = 1;
	पूर्ण अन्यथा अणु
		req.page_tbl_addr =  cpu_to_le64(rmem->dma_arr[0]);
	पूर्ण
	req.fbo = 0;
	/* Association of ring index with करोorbell index and MSIX number */
	req.logical_id = cpu_to_le16(map_index);

	चयन (ring_type) अणु
	हाल HWRM_RING_ALLOC_TX: अणु
		काष्ठा bnxt_tx_ring_info *txr;

		txr = container_of(ring, काष्ठा bnxt_tx_ring_info,
				   tx_ring_काष्ठा);
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_TX;
		/* Association of transmit ring with completion ring */
		grp_info = &bp->grp_info[ring->grp_idx];
		req.cmpl_ring_id = cpu_to_le16(bnxt_cp_ring_क्रम_tx(bp, txr));
		req.length = cpu_to_le32(bp->tx_ring_mask + 1);
		req.stat_ctx_id = cpu_to_le32(grp_info->fw_stats_ctx);
		req.queue_id = cpu_to_le16(ring->queue_id);
		अवरोध;
	पूर्ण
	हाल HWRM_RING_ALLOC_RX:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_RX;
		req.length = cpu_to_le32(bp->rx_ring_mask + 1);
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			u16 flags = 0;

			/* Association of rx ring with stats context */
			grp_info = &bp->grp_info[ring->grp_idx];
			req.rx_buf_size = cpu_to_le16(bp->rx_buf_use_size);
			req.stat_ctx_id = cpu_to_le32(grp_info->fw_stats_ctx);
			req.enables |= cpu_to_le32(
				RING_ALLOC_REQ_ENABLES_RX_BUF_SIZE_VALID);
			अगर (NET_IP_ALIGN == 2)
				flags = RING_ALLOC_REQ_FLAGS_RX_SOP_PAD;
			req.flags = cpu_to_le16(flags);
		पूर्ण
		अवरोध;
	हाल HWRM_RING_ALLOC_AGG:
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			req.ring_type = RING_ALLOC_REQ_RING_TYPE_RX_AGG;
			/* Association of agg ring with rx ring */
			grp_info = &bp->grp_info[ring->grp_idx];
			req.rx_ring_id = cpu_to_le16(grp_info->rx_fw_ring_id);
			req.rx_buf_size = cpu_to_le16(BNXT_RX_PAGE_SIZE);
			req.stat_ctx_id = cpu_to_le32(grp_info->fw_stats_ctx);
			req.enables |= cpu_to_le32(
				RING_ALLOC_REQ_ENABLES_RX_RING_ID_VALID |
				RING_ALLOC_REQ_ENABLES_RX_BUF_SIZE_VALID);
		पूर्ण अन्यथा अणु
			req.ring_type = RING_ALLOC_REQ_RING_TYPE_RX;
		पूर्ण
		req.length = cpu_to_le32(bp->rx_agg_ring_mask + 1);
		अवरोध;
	हाल HWRM_RING_ALLOC_CMPL:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_L2_CMPL;
		req.length = cpu_to_le32(bp->cp_ring_mask + 1);
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			/* Association of cp ring with nq */
			grp_info = &bp->grp_info[map_index];
			req.nq_ring_id = cpu_to_le16(grp_info->cp_fw_ring_id);
			req.cq_handle = cpu_to_le64(ring->handle);
			req.enables |= cpu_to_le32(
				RING_ALLOC_REQ_ENABLES_NQ_RING_ID_VALID);
		पूर्ण अन्यथा अगर (bp->flags & BNXT_FLAG_USING_MSIX) अणु
			req.पूर्णांक_mode = RING_ALLOC_REQ_INT_MODE_MSIX;
		पूर्ण
		अवरोध;
	हाल HWRM_RING_ALLOC_NQ:
		req.ring_type = RING_ALLOC_REQ_RING_TYPE_NQ;
		req.length = cpu_to_le32(bp->cp_ring_mask + 1);
		अगर (bp->flags & BNXT_FLAG_USING_MSIX)
			req.पूर्णांक_mode = RING_ALLOC_REQ_INT_MODE_MSIX;
		अवरोध;
	शेष:
		netdev_err(bp->dev, "hwrm alloc invalid ring type %d\n",
			   ring_type);
		वापस -1;
	पूर्ण

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	err = le16_to_cpu(resp->error_code);
	ring_id = le16_to_cpu(resp->ring_id);
	mutex_unlock(&bp->hwrm_cmd_lock);

	अगर (rc || err) अणु
		netdev_err(bp->dev, "hwrm_ring_alloc type %d failed. rc:%x err:%x\n",
			   ring_type, rc, err);
		वापस -EIO;
	पूर्ण
	ring->fw_ring_id = ring_id;
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_set_async_event_cr(काष्ठा bnxt *bp, पूर्णांक idx)
अणु
	पूर्णांक rc;

	अगर (BNXT_PF(bp)) अणु
		काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
		req.fid = cpu_to_le16(0xffff);
		req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = cpu_to_le16(idx);
		rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	पूर्ण अन्यथा अणु
		काष्ठा hwrm_func_vf_cfg_input req = अणु0पूर्ण;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_CFG, -1, -1);
		req.enables =
			cpu_to_le32(FUNC_VF_CFG_REQ_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = cpu_to_le16(idx);
		rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_set_db(काष्ठा bnxt *bp, काष्ठा bnxt_db_info *db, u32 ring_type,
			u32 map_idx, u32 xid)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		अगर (BNXT_PF(bp))
			db->करोorbell = bp->bar1 + DB_PF_OFFSET_P5;
		अन्यथा
			db->करोorbell = bp->bar1 + DB_VF_OFFSET_P5;
		चयन (ring_type) अणु
		हाल HWRM_RING_ALLOC_TX:
			db->db_key64 = DBR_PATH_L2 | DBR_TYPE_SQ;
			अवरोध;
		हाल HWRM_RING_ALLOC_RX:
		हाल HWRM_RING_ALLOC_AGG:
			db->db_key64 = DBR_PATH_L2 | DBR_TYPE_SRQ;
			अवरोध;
		हाल HWRM_RING_ALLOC_CMPL:
			db->db_key64 = DBR_PATH_L2;
			अवरोध;
		हाल HWRM_RING_ALLOC_NQ:
			db->db_key64 = DBR_PATH_L2;
			अवरोध;
		पूर्ण
		db->db_key64 |= (u64)xid << DBR_XID_SFT;
	पूर्ण अन्यथा अणु
		db->करोorbell = bp->bar1 + map_idx * 0x80;
		चयन (ring_type) अणु
		हाल HWRM_RING_ALLOC_TX:
			db->db_key32 = DB_KEY_TX;
			अवरोध;
		हाल HWRM_RING_ALLOC_RX:
		हाल HWRM_RING_ALLOC_AGG:
			db->db_key32 = DB_KEY_RX;
			अवरोध;
		हाल HWRM_RING_ALLOC_CMPL:
			db->db_key32 = DB_KEY_CP;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_hwrm_ring_alloc(काष्ठा bnxt *bp)
अणु
	bool agg_rings = !!(bp->flags & BNXT_FLAG_AGG_RINGS);
	पूर्णांक i, rc = 0;
	u32 type;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		type = HWRM_RING_ALLOC_NQ;
	अन्यथा
		type = HWRM_RING_ALLOC_CMPL;
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		काष्ठा bnxt_ring_काष्ठा *ring = &cpr->cp_ring_काष्ठा;
		u32 map_idx = ring->map_idx;
		अचिन्हित पूर्णांक vector;

		vector = bp->irq_tbl[map_idx].vector;
		disable_irq_nosync(vector);
		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		अगर (rc) अणु
			enable_irq(vector);
			जाओ err_out;
		पूर्ण
		bnxt_set_db(bp, &cpr->cp_db, type, map_idx, ring->fw_ring_id);
		bnxt_db_nq(bp, &cpr->cp_db, cpr->cp_raw_cons);
		enable_irq(vector);
		bp->grp_info[i].cp_fw_ring_id = ring->fw_ring_id;

		अगर (!i) अणु
			rc = bnxt_hwrm_set_async_event_cr(bp, ring->fw_ring_id);
			अगर (rc)
				netdev_warn(bp->dev, "Failed to set async event completion ring.\n");
		पूर्ण
	पूर्ण

	type = HWRM_RING_ALLOC_TX;
	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring;
		u32 map_idx;

		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			काष्ठा bnxt_napi *bnapi = txr->bnapi;
			काष्ठा bnxt_cp_ring_info *cpr, *cpr2;
			u32 type2 = HWRM_RING_ALLOC_CMPL;

			cpr = &bnapi->cp_ring;
			cpr2 = cpr->cp_ring_arr[BNXT_TX_HDL];
			ring = &cpr2->cp_ring_काष्ठा;
			ring->handle = BNXT_TX_HDL;
			map_idx = bnapi->index;
			rc = hwrm_ring_alloc_send_msg(bp, ring, type2, map_idx);
			अगर (rc)
				जाओ err_out;
			bnxt_set_db(bp, &cpr2->cp_db, type2, map_idx,
				    ring->fw_ring_id);
			bnxt_db_cq(bp, &cpr2->cp_db, cpr2->cp_raw_cons);
		पूर्ण
		ring = &txr->tx_ring_काष्ठा;
		map_idx = i;
		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		अगर (rc)
			जाओ err_out;
		bnxt_set_db(bp, &txr->tx_db, type, map_idx, ring->fw_ring_id);
	पूर्ण

	type = HWRM_RING_ALLOC_RX;
	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring = &rxr->rx_ring_काष्ठा;
		काष्ठा bnxt_napi *bnapi = rxr->bnapi;
		u32 map_idx = bnapi->index;

		rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
		अगर (rc)
			जाओ err_out;
		bnxt_set_db(bp, &rxr->rx_db, type, map_idx, ring->fw_ring_id);
		/* If we have agg rings, post agg buffers first. */
		अगर (!agg_rings)
			bnxt_db_ग_लिखो(bp, &rxr->rx_db, rxr->rx_prod);
		bp->grp_info[map_idx].rx_fw_ring_id = ring->fw_ring_id;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
			u32 type2 = HWRM_RING_ALLOC_CMPL;
			काष्ठा bnxt_cp_ring_info *cpr2;

			cpr2 = cpr->cp_ring_arr[BNXT_RX_HDL];
			ring = &cpr2->cp_ring_काष्ठा;
			ring->handle = BNXT_RX_HDL;
			rc = hwrm_ring_alloc_send_msg(bp, ring, type2, map_idx);
			अगर (rc)
				जाओ err_out;
			bnxt_set_db(bp, &cpr2->cp_db, type2, map_idx,
				    ring->fw_ring_id);
			bnxt_db_cq(bp, &cpr2->cp_db, cpr2->cp_raw_cons);
		पूर्ण
	पूर्ण

	अगर (agg_rings) अणु
		type = HWRM_RING_ALLOC_AGG;
		क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
			काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
			काष्ठा bnxt_ring_काष्ठा *ring =
						&rxr->rx_agg_ring_काष्ठा;
			u32 grp_idx = ring->grp_idx;
			u32 map_idx = grp_idx + bp->rx_nr_rings;

			rc = hwrm_ring_alloc_send_msg(bp, ring, type, map_idx);
			अगर (rc)
				जाओ err_out;

			bnxt_set_db(bp, &rxr->rx_agg_db, type, map_idx,
				    ring->fw_ring_id);
			bnxt_db_ग_लिखो(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);
			bnxt_db_ग_लिखो(bp, &rxr->rx_db, rxr->rx_prod);
			bp->grp_info[grp_idx].agg_fw_ring_id = ring->fw_ring_id;
		पूर्ण
	पूर्ण
err_out:
	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_ring_मुक्त_send_msg(काष्ठा bnxt *bp,
				   काष्ठा bnxt_ring_काष्ठा *ring,
				   u32 ring_type, पूर्णांक cmpl_ring_id)
अणु
	पूर्णांक rc;
	काष्ठा hwrm_ring_मुक्त_input req = अणु0पूर्ण;
	काष्ठा hwrm_ring_मुक्त_output *resp = bp->hwrm_cmd_resp_addr;
	u16 error_code;

	अगर (BNXT_NO_FW_ACCESS(bp))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_FREE, cmpl_ring_id, -1);
	req.ring_type = ring_type;
	req.ring_id = cpu_to_le16(ring->fw_ring_id);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	error_code = le16_to_cpu(resp->error_code);
	mutex_unlock(&bp->hwrm_cmd_lock);

	अगर (rc || error_code) अणु
		netdev_err(bp->dev, "hwrm_ring_free type %d failed. rc:%x err:%x\n",
			   ring_type, rc, error_code);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_hwrm_ring_मुक्त(काष्ठा bnxt *bp, bool बंद_path)
अणु
	u32 type;
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		काष्ठा bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring = &txr->tx_ring_काष्ठा;

		अगर (ring->fw_ring_id != INVALID_HW_RING_ID) अणु
			u32 cmpl_ring_id = bnxt_cp_ring_क्रम_tx(bp, txr);

			hwrm_ring_मुक्त_send_msg(bp, ring,
						RING_FREE_REQ_RING_TYPE_TX,
						बंद_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring = &rxr->rx_ring_काष्ठा;
		u32 grp_idx = rxr->bnapi->index;

		अगर (ring->fw_ring_id != INVALID_HW_RING_ID) अणु
			u32 cmpl_ring_id = bnxt_cp_ring_क्रम_rx(bp, rxr);

			hwrm_ring_मुक्त_send_msg(bp, ring,
						RING_FREE_REQ_RING_TYPE_RX,
						बंद_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[grp_idx].rx_fw_ring_id =
				INVALID_HW_RING_ID;
		पूर्ण
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		type = RING_FREE_REQ_RING_TYPE_RX_AGG;
	अन्यथा
		type = RING_FREE_REQ_RING_TYPE_RX;
	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_ring_काष्ठा *ring = &rxr->rx_agg_ring_काष्ठा;
		u32 grp_idx = rxr->bnapi->index;

		अगर (ring->fw_ring_id != INVALID_HW_RING_ID) अणु
			u32 cmpl_ring_id = bnxt_cp_ring_क्रम_rx(bp, rxr);

			hwrm_ring_मुक्त_send_msg(bp, ring, type,
						बंद_path ? cmpl_ring_id :
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[grp_idx].agg_fw_ring_id =
				INVALID_HW_RING_ID;
		पूर्ण
	पूर्ण

	/* The completion rings are about to be मुक्तd.  After that the
	 * IRQ करोorbell will not work anymore.  So we need to disable
	 * IRQ here.
	 */
	bnxt_disable_पूर्णांक_sync(bp);

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		type = RING_FREE_REQ_RING_TYPE_NQ;
	अन्यथा
		type = RING_FREE_REQ_RING_TYPE_L2_CMPL;
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		काष्ठा bnxt_ring_काष्ठा *ring;
		पूर्णांक j;

		क्रम (j = 0; j < 2; j++) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];

			अगर (cpr2) अणु
				ring = &cpr2->cp_ring_काष्ठा;
				अगर (ring->fw_ring_id == INVALID_HW_RING_ID)
					जारी;
				hwrm_ring_मुक्त_send_msg(bp, ring,
					RING_FREE_REQ_RING_TYPE_L2_CMPL,
					INVALID_HW_RING_ID);
				ring->fw_ring_id = INVALID_HW_RING_ID;
			पूर्ण
		पूर्ण
		ring = &cpr->cp_ring_काष्ठा;
		अगर (ring->fw_ring_id != INVALID_HW_RING_ID) अणु
			hwrm_ring_मुक्त_send_msg(bp, ring, type,
						INVALID_HW_RING_ID);
			ring->fw_ring_id = INVALID_HW_RING_ID;
			bp->grp_info[i].cp_fw_ring_id = INVALID_HW_RING_ID;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_trim_rings(काष्ठा bnxt *bp, पूर्णांक *rx, पूर्णांक *tx, पूर्णांक max,
			   bool shared);

अटल पूर्णांक bnxt_hwrm_get_rings(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	काष्ठा hwrm_func_qcfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10601)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण

	hw_resc->resv_tx_rings = le16_to_cpu(resp->alloc_tx_rings);
	अगर (BNXT_NEW_RM(bp)) अणु
		u16 cp, stats;

		hw_resc->resv_rx_rings = le16_to_cpu(resp->alloc_rx_rings);
		hw_resc->resv_hw_ring_grps =
			le32_to_cpu(resp->alloc_hw_ring_grps);
		hw_resc->resv_vnics = le16_to_cpu(resp->alloc_vnics);
		cp = le16_to_cpu(resp->alloc_cmpl_rings);
		stats = le16_to_cpu(resp->alloc_stat_ctx);
		hw_resc->resv_irqs = cp;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			पूर्णांक rx = hw_resc->resv_rx_rings;
			पूर्णांक tx = hw_resc->resv_tx_rings;

			अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
				rx >>= 1;
			अगर (cp < (rx + tx)) अणु
				bnxt_trim_rings(bp, &rx, &tx, cp, false);
				अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
					rx <<= 1;
				hw_resc->resv_rx_rings = rx;
				hw_resc->resv_tx_rings = tx;
			पूर्ण
			hw_resc->resv_irqs = le16_to_cpu(resp->alloc_msix);
			hw_resc->resv_hw_ring_grps = rx;
		पूर्ण
		hw_resc->resv_cp_rings = cp;
		hw_resc->resv_stat_ctxs = stats;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस 0;
पूर्ण

/* Caller must hold bp->hwrm_cmd_lock */
पूर्णांक __bnxt_hwrm_get_tx_rings(काष्ठा bnxt *bp, u16 fid, पूर्णांक *tx_rings)
अणु
	काष्ठा hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_qcfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10601)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(fid);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		*tx_rings = le16_to_cpu(resp->alloc_tx_rings);

	वापस rc;
पूर्ण

अटल bool bnxt_rfs_supported(काष्ठा bnxt *bp);

अटल व्योम
__bnxt_hwrm_reserve_pf_rings(काष्ठा bnxt *bp, काष्ठा hwrm_func_cfg_input *req,
			     पूर्णांक tx_rings, पूर्णांक rx_rings, पूर्णांक ring_grps,
			     पूर्णांक cp_rings, पूर्णांक stats, पूर्णांक vnics)
अणु
	u32 enables = 0;

	bnxt_hwrm_cmd_hdr_init(bp, req, HWRM_FUNC_CFG, -1, -1);
	req->fid = cpu_to_le16(0xffff);
	enables |= tx_rings ? FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS : 0;
	req->num_tx_rings = cpu_to_le16(tx_rings);
	अगर (BNXT_NEW_RM(bp)) अणु
		enables |= rx_rings ? FUNC_CFG_REQ_ENABLES_NUM_RX_RINGS : 0;
		enables |= stats ? FUNC_CFG_REQ_ENABLES_NUM_STAT_CTXS : 0;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			enables |= cp_rings ? FUNC_CFG_REQ_ENABLES_NUM_MSIX : 0;
			enables |= tx_rings + ring_grps ?
				   FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
			enables |= rx_rings ?
				FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS : 0;
		पूर्ण अन्यथा अणु
			enables |= cp_rings ?
				   FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
			enables |= ring_grps ?
				   FUNC_CFG_REQ_ENABLES_NUM_HW_RING_GRPS |
				   FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS : 0;
		पूर्ण
		enables |= vnics ? FUNC_CFG_REQ_ENABLES_NUM_VNICS : 0;

		req->num_rx_rings = cpu_to_le16(rx_rings);
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			req->num_cmpl_rings = cpu_to_le16(tx_rings + ring_grps);
			req->num_msix = cpu_to_le16(cp_rings);
			req->num_rsscos_ctxs =
				cpu_to_le16(DIV_ROUND_UP(ring_grps, 64));
		पूर्ण अन्यथा अणु
			req->num_cmpl_rings = cpu_to_le16(cp_rings);
			req->num_hw_ring_grps = cpu_to_le16(ring_grps);
			req->num_rsscos_ctxs = cpu_to_le16(1);
			अगर (!(bp->flags & BNXT_FLAG_NEW_RSS_CAP) &&
			    bnxt_rfs_supported(bp))
				req->num_rsscos_ctxs =
					cpu_to_le16(ring_grps + 1);
		पूर्ण
		req->num_stat_ctxs = cpu_to_le16(stats);
		req->num_vnics = cpu_to_le16(vnics);
	पूर्ण
	req->enables = cpu_to_le32(enables);
पूर्ण

अटल व्योम
__bnxt_hwrm_reserve_vf_rings(काष्ठा bnxt *bp,
			     काष्ठा hwrm_func_vf_cfg_input *req, पूर्णांक tx_rings,
			     पूर्णांक rx_rings, पूर्णांक ring_grps, पूर्णांक cp_rings,
			     पूर्णांक stats, पूर्णांक vnics)
अणु
	u32 enables = 0;

	bnxt_hwrm_cmd_hdr_init(bp, req, HWRM_FUNC_VF_CFG, -1, -1);
	enables |= tx_rings ? FUNC_VF_CFG_REQ_ENABLES_NUM_TX_RINGS : 0;
	enables |= rx_rings ? FUNC_VF_CFG_REQ_ENABLES_NUM_RX_RINGS |
			      FUNC_VF_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS : 0;
	enables |= stats ? FUNC_VF_CFG_REQ_ENABLES_NUM_STAT_CTXS : 0;
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		enables |= tx_rings + ring_grps ?
			   FUNC_VF_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
	पूर्ण अन्यथा अणु
		enables |= cp_rings ?
			   FUNC_VF_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
		enables |= ring_grps ?
			   FUNC_VF_CFG_REQ_ENABLES_NUM_HW_RING_GRPS : 0;
	पूर्ण
	enables |= vnics ? FUNC_VF_CFG_REQ_ENABLES_NUM_VNICS : 0;
	enables |= FUNC_VF_CFG_REQ_ENABLES_NUM_L2_CTXS;

	req->num_l2_ctxs = cpu_to_le16(BNXT_VF_MAX_L2_CTX);
	req->num_tx_rings = cpu_to_le16(tx_rings);
	req->num_rx_rings = cpu_to_le16(rx_rings);
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		req->num_cmpl_rings = cpu_to_le16(tx_rings + ring_grps);
		req->num_rsscos_ctxs = cpu_to_le16(DIV_ROUND_UP(ring_grps, 64));
	पूर्ण अन्यथा अणु
		req->num_cmpl_rings = cpu_to_le16(cp_rings);
		req->num_hw_ring_grps = cpu_to_le16(ring_grps);
		req->num_rsscos_ctxs = cpu_to_le16(BNXT_VF_MAX_RSS_CTX);
	पूर्ण
	req->num_stat_ctxs = cpu_to_le16(stats);
	req->num_vnics = cpu_to_le16(vnics);

	req->enables = cpu_to_le32(enables);
पूर्ण

अटल पूर्णांक
bnxt_hwrm_reserve_pf_rings(काष्ठा bnxt *bp, पूर्णांक tx_rings, पूर्णांक rx_rings,
			   पूर्णांक ring_grps, पूर्णांक cp_rings, पूर्णांक stats, पूर्णांक vnics)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	__bnxt_hwrm_reserve_pf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	अगर (!req.enables)
		वापस 0;

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		वापस rc;

	अगर (bp->hwrm_spec_code < 0x10601)
		bp->hw_resc.resv_tx_rings = tx_rings;

	वापस bnxt_hwrm_get_rings(bp);
पूर्ण

अटल पूर्णांक
bnxt_hwrm_reserve_vf_rings(काष्ठा bnxt *bp, पूर्णांक tx_rings, पूर्णांक rx_rings,
			   पूर्णांक ring_grps, पूर्णांक cp_rings, पूर्णांक stats, पूर्णांक vnics)
अणु
	काष्ठा hwrm_func_vf_cfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (!BNXT_NEW_RM(bp)) अणु
		bp->hw_resc.resv_tx_rings = tx_rings;
		वापस 0;
	पूर्ण

	__bnxt_hwrm_reserve_vf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		वापस rc;

	वापस bnxt_hwrm_get_rings(bp);
पूर्ण

अटल पूर्णांक bnxt_hwrm_reserve_rings(काष्ठा bnxt *bp, पूर्णांक tx, पूर्णांक rx, पूर्णांक grp,
				   पूर्णांक cp, पूर्णांक stat, पूर्णांक vnic)
अणु
	अगर (BNXT_PF(bp))
		वापस bnxt_hwrm_reserve_pf_rings(bp, tx, rx, grp, cp, stat,
						  vnic);
	अन्यथा
		वापस bnxt_hwrm_reserve_vf_rings(bp, tx, rx, grp, cp, stat,
						  vnic);
पूर्ण

पूर्णांक bnxt_nq_rings_in_use(काष्ठा bnxt *bp)
अणु
	पूर्णांक cp = bp->cp_nr_rings;
	पूर्णांक ulp_msix, ulp_base;

	ulp_msix = bnxt_get_ulp_msix_num(bp);
	अगर (ulp_msix) अणु
		ulp_base = bnxt_get_ulp_msix_base(bp);
		cp += ulp_msix;
		अगर ((ulp_base + ulp_msix) > cp)
			cp = ulp_base + ulp_msix;
	पूर्ण
	वापस cp;
पूर्ण

अटल पूर्णांक bnxt_cp_rings_in_use(काष्ठा bnxt *bp)
अणु
	पूर्णांक cp;

	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		वापस bnxt_nq_rings_in_use(bp);

	cp = bp->tx_nr_rings + bp->rx_nr_rings;
	वापस cp;
पूर्ण

अटल पूर्णांक bnxt_get_func_stat_ctxs(काष्ठा bnxt *bp)
अणु
	पूर्णांक ulp_stat = bnxt_get_ulp_stat_ctxs(bp);
	पूर्णांक cp = bp->cp_nr_rings;

	अगर (!ulp_stat)
		वापस cp;

	अगर (bnxt_nq_rings_in_use(bp) > cp + bnxt_get_ulp_msix_num(bp))
		वापस bnxt_get_ulp_msix_base(bp) + ulp_stat;

	वापस cp + ulp_stat;
पूर्ण

/* Check अगर a शेष RSS map needs to be setup.  This function is only
 * used on older firmware that करोes not require reserving RX rings.
 */
अटल व्योम bnxt_check_rss_tbl_no_rmgr(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;

	/* The RSS map is valid क्रम RX rings set to resv_rx_rings */
	अगर (hw_resc->resv_rx_rings != bp->rx_nr_rings) अणु
		hw_resc->resv_rx_rings = bp->rx_nr_rings;
		अगर (!netअगर_is_rxfh_configured(bp->dev))
			bnxt_set_dflt_rss_indir_tbl(bp);
	पूर्ण
पूर्ण

अटल bool bnxt_need_reserve_rings(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक cp = bnxt_cp_rings_in_use(bp);
	पूर्णांक nq = bnxt_nq_rings_in_use(bp);
	पूर्णांक rx = bp->rx_nr_rings, stat;
	पूर्णांक vnic = 1, grp = rx;

	अगर (hw_resc->resv_tx_rings != bp->tx_nr_rings &&
	    bp->hwrm_spec_code >= 0x10601)
		वापस true;

	/* Old firmware करोes not need RX ring reservations but we still
	 * need to setup a शेष RSS map when needed.  With new firmware
	 * we go through RX ring reservations first and then set up the
	 * RSS map क्रम the successfully reserved RX rings when needed.
	 */
	अगर (!BNXT_NEW_RM(bp)) अणु
		bnxt_check_rss_tbl_no_rmgr(bp);
		वापस false;
	पूर्ण
	अगर ((bp->flags & BNXT_FLAG_RFS) && !(bp->flags & BNXT_FLAG_CHIP_P5))
		vnic = rx + 1;
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx <<= 1;
	stat = bnxt_get_func_stat_ctxs(bp);
	अगर (hw_resc->resv_rx_rings != rx || hw_resc->resv_cp_rings != cp ||
	    hw_resc->resv_vnics != vnic || hw_resc->resv_stat_ctxs != stat ||
	    (hw_resc->resv_hw_ring_grps != grp &&
	     !(bp->flags & BNXT_FLAG_CHIP_P5)))
		वापस true;
	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) && BNXT_PF(bp) &&
	    hw_resc->resv_irqs != nq)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक __bnxt_reserve_rings(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक cp = bnxt_nq_rings_in_use(bp);
	पूर्णांक tx = bp->tx_nr_rings;
	पूर्णांक rx = bp->rx_nr_rings;
	पूर्णांक grp, rx_rings, rc;
	पूर्णांक vnic = 1, stat;
	bool sh = false;

	अगर (!bnxt_need_reserve_rings(bp))
		वापस 0;

	अगर (bp->flags & BNXT_FLAG_SHARED_RINGS)
		sh = true;
	अगर ((bp->flags & BNXT_FLAG_RFS) && !(bp->flags & BNXT_FLAG_CHIP_P5))
		vnic = rx + 1;
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx <<= 1;
	grp = bp->rx_nr_rings;
	stat = bnxt_get_func_stat_ctxs(bp);

	rc = bnxt_hwrm_reserve_rings(bp, tx, rx, grp, cp, stat, vnic);
	अगर (rc)
		वापस rc;

	tx = hw_resc->resv_tx_rings;
	अगर (BNXT_NEW_RM(bp)) अणु
		rx = hw_resc->resv_rx_rings;
		cp = hw_resc->resv_irqs;
		grp = hw_resc->resv_hw_ring_grps;
		vnic = hw_resc->resv_vnics;
		stat = hw_resc->resv_stat_ctxs;
	पूर्ण

	rx_rings = rx;
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS) अणु
		अगर (rx >= 2) अणु
			rx_rings = rx >> 1;
		पूर्ण अन्यथा अणु
			अगर (netअगर_running(bp->dev))
				वापस -ENOMEM;

			bp->flags &= ~BNXT_FLAG_AGG_RINGS;
			bp->flags |= BNXT_FLAG_NO_AGG_RINGS;
			bp->dev->hw_features &= ~NETIF_F_LRO;
			bp->dev->features &= ~NETIF_F_LRO;
			bnxt_set_ring_params(bp);
		पूर्ण
	पूर्ण
	rx_rings = min_t(पूर्णांक, rx_rings, grp);
	cp = min_t(पूर्णांक, cp, bp->cp_nr_rings);
	अगर (stat > bnxt_get_ulp_stat_ctxs(bp))
		stat -= bnxt_get_ulp_stat_ctxs(bp);
	cp = min_t(पूर्णांक, cp, stat);
	rc = bnxt_trim_rings(bp, &rx_rings, &tx, cp, sh);
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx = rx_rings << 1;
	cp = sh ? max_t(पूर्णांक, tx, rx_rings) : tx + rx_rings;
	bp->tx_nr_rings = tx;

	/* If we cannot reserve all the RX rings, reset the RSS map only
	 * अगर असलolutely necessary
	 */
	अगर (rx_rings != bp->rx_nr_rings) अणु
		netdev_warn(bp->dev, "Able to reserve only %d out of %d requested RX rings\n",
			    rx_rings, bp->rx_nr_rings);
		अगर ((bp->dev->priv_flags & IFF_RXFH_CONFIGURED) &&
		    (bnxt_get_nr_rss_ctxs(bp, bp->rx_nr_rings) !=
		     bnxt_get_nr_rss_ctxs(bp, rx_rings) ||
		     bnxt_get_max_rss_ring(bp) >= rx_rings)) अणु
			netdev_warn(bp->dev, "RSS table entries reverting to default\n");
			bp->dev->priv_flags &= ~IFF_RXFH_CONFIGURED;
		पूर्ण
	पूर्ण
	bp->rx_nr_rings = rx_rings;
	bp->cp_nr_rings = cp;

	अगर (!tx || !rx || !cp || !grp || !vnic || !stat)
		वापस -ENOMEM;

	अगर (!netअगर_is_rxfh_configured(bp->dev))
		bnxt_set_dflt_rss_indir_tbl(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_check_vf_rings(काष्ठा bnxt *bp, पूर्णांक tx_rings, पूर्णांक rx_rings,
				    पूर्णांक ring_grps, पूर्णांक cp_rings, पूर्णांक stats,
				    पूर्णांक vnics)
अणु
	काष्ठा hwrm_func_vf_cfg_input req = अणु0पूर्ण;
	u32 flags;

	अगर (!BNXT_NEW_RM(bp))
		वापस 0;

	__bnxt_hwrm_reserve_vf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	flags = FUNC_VF_CFG_REQ_FLAGS_TX_ASSETS_TEST |
		FUNC_VF_CFG_REQ_FLAGS_RX_ASSETS_TEST |
		FUNC_VF_CFG_REQ_FLAGS_CMPL_ASSETS_TEST |
		FUNC_VF_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST |
		FUNC_VF_CFG_REQ_FLAGS_VNIC_ASSETS_TEST |
		FUNC_VF_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST;
	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		flags |= FUNC_VF_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST;

	req.flags = cpu_to_le32(flags);
	वापस hwrm_send_message_silent(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_check_pf_rings(काष्ठा bnxt *bp, पूर्णांक tx_rings, पूर्णांक rx_rings,
				    पूर्णांक ring_grps, पूर्णांक cp_rings, पूर्णांक stats,
				    पूर्णांक vnics)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	u32 flags;

	__bnxt_hwrm_reserve_pf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	flags = FUNC_CFG_REQ_FLAGS_TX_ASSETS_TEST;
	अगर (BNXT_NEW_RM(bp)) अणु
		flags |= FUNC_CFG_REQ_FLAGS_RX_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_CMPL_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_VNIC_ASSETS_TEST;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			flags |= FUNC_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST |
				 FUNC_CFG_REQ_FLAGS_NQ_ASSETS_TEST;
		अन्यथा
			flags |= FUNC_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST;
	पूर्ण

	req.flags = cpu_to_le32(flags);
	वापस hwrm_send_message_silent(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_check_rings(काष्ठा bnxt *bp, पूर्णांक tx_rings, पूर्णांक rx_rings,
				 पूर्णांक ring_grps, पूर्णांक cp_rings, पूर्णांक stats,
				 पूर्णांक vnics)
अणु
	अगर (bp->hwrm_spec_code < 0x10801)
		वापस 0;

	अगर (BNXT_PF(bp))
		वापस bnxt_hwrm_check_pf_rings(bp, tx_rings, rx_rings,
						ring_grps, cp_rings, stats,
						vnics);

	वापस bnxt_hwrm_check_vf_rings(bp, tx_rings, rx_rings, ring_grps,
					cp_rings, stats, vnics);
पूर्ण

अटल व्योम bnxt_hwrm_coal_params_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_ring_aggपूर्णांक_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_coal_cap *coal_cap = &bp->coal_cap;
	काष्ठा hwrm_ring_aggपूर्णांक_qcaps_input req = अणु0पूर्ण;
	पूर्णांक rc;

	coal_cap->cmpl_params = BNXT_LEGACY_COAL_CMPL_PARAMS;
	coal_cap->num_cmpl_dma_aggr_max = 63;
	coal_cap->num_cmpl_dma_aggr_during_पूर्णांक_max = 63;
	coal_cap->cmpl_aggr_dma_पंचांगr_max = 65535;
	coal_cap->cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max = 65535;
	coal_cap->पूर्णांक_lat_पंचांगr_min_max = 65535;
	coal_cap->पूर्णांक_lat_पंचांगr_max_max = 65535;
	coal_cap->num_cmpl_aggr_पूर्णांक_max = 65535;
	coal_cap->समयr_units = 80;

	अगर (bp->hwrm_spec_code < 0x10902)
		वापस;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_AGGINT_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		coal_cap->cmpl_params = le32_to_cpu(resp->cmpl_params);
		coal_cap->nq_params = le32_to_cpu(resp->nq_params);
		coal_cap->num_cmpl_dma_aggr_max =
			le16_to_cpu(resp->num_cmpl_dma_aggr_max);
		coal_cap->num_cmpl_dma_aggr_during_पूर्णांक_max =
			le16_to_cpu(resp->num_cmpl_dma_aggr_during_पूर्णांक_max);
		coal_cap->cmpl_aggr_dma_पंचांगr_max =
			le16_to_cpu(resp->cmpl_aggr_dma_पंचांगr_max);
		coal_cap->cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max =
			le16_to_cpu(resp->cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max);
		coal_cap->पूर्णांक_lat_पंचांगr_min_max =
			le16_to_cpu(resp->पूर्णांक_lat_पंचांगr_min_max);
		coal_cap->पूर्णांक_lat_पंचांगr_max_max =
			le16_to_cpu(resp->पूर्णांक_lat_पंचांगr_max_max);
		coal_cap->num_cmpl_aggr_पूर्णांक_max =
			le16_to_cpu(resp->num_cmpl_aggr_पूर्णांक_max);
		coal_cap->समयr_units = le16_to_cpu(resp->समयr_units);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
पूर्ण

अटल u16 bnxt_usec_to_coal_पंचांगr(काष्ठा bnxt *bp, u16 usec)
अणु
	काष्ठा bnxt_coal_cap *coal_cap = &bp->coal_cap;

	वापस usec * 1000 / coal_cap->समयr_units;
पूर्ण

अटल व्योम bnxt_hwrm_set_coal_params(काष्ठा bnxt *bp,
	काष्ठा bnxt_coal *hw_coal,
	काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input *req)
अणु
	काष्ठा bnxt_coal_cap *coal_cap = &bp->coal_cap;
	u32 cmpl_params = coal_cap->cmpl_params;
	u16 val, पंचांगr, max, flags = 0;

	max = hw_coal->bufs_per_record * 128;
	अगर (hw_coal->budget)
		max = hw_coal->bufs_per_record * hw_coal->budget;
	max = min_t(u16, max, coal_cap->num_cmpl_aggr_पूर्णांक_max);

	val = clamp_t(u16, hw_coal->coal_bufs, 1, max);
	req->num_cmpl_aggr_पूर्णांक = cpu_to_le16(val);

	val = min_t(u16, val, coal_cap->num_cmpl_dma_aggr_max);
	req->num_cmpl_dma_aggr = cpu_to_le16(val);

	val = clamp_t(u16, hw_coal->coal_bufs_irq, 1,
		      coal_cap->num_cmpl_dma_aggr_during_पूर्णांक_max);
	req->num_cmpl_dma_aggr_during_पूर्णांक = cpu_to_le16(val);

	पंचांगr = bnxt_usec_to_coal_पंचांगr(bp, hw_coal->coal_ticks);
	पंचांगr = clamp_t(u16, पंचांगr, 1, coal_cap->पूर्णांक_lat_पंचांगr_max_max);
	req->पूर्णांक_lat_पंचांगr_max = cpu_to_le16(पंचांगr);

	/* min समयr set to 1/2 of पूर्णांकerrupt समयr */
	अगर (cmpl_params & RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_INT_LAT_TMR_MIN) अणु
		val = पंचांगr / 2;
		val = clamp_t(u16, val, 1, coal_cap->पूर्णांक_lat_पंचांगr_min_max);
		req->पूर्णांक_lat_पंचांगr_min = cpu_to_le16(val);
		req->enables |= cpu_to_le16(BNXT_COAL_CMPL_MIN_TMR_ENABLE);
	पूर्ण

	/* buf समयr set to 1/4 of पूर्णांकerrupt समयr */
	val = clamp_t(u16, पंचांगr / 4, 1, coal_cap->cmpl_aggr_dma_पंचांगr_max);
	req->cmpl_aggr_dma_पंचांगr = cpu_to_le16(val);

	अगर (cmpl_params &
	    RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_NUM_CMPL_DMA_AGGR_DURING_INT) अणु
		पंचांगr = bnxt_usec_to_coal_पंचांगr(bp, hw_coal->coal_ticks_irq);
		val = clamp_t(u16, पंचांगr, 1,
			      coal_cap->cmpl_aggr_dma_पंचांगr_during_पूर्णांक_max);
		req->cmpl_aggr_dma_पंचांगr_during_पूर्णांक = cpu_to_le16(val);
		req->enables |=
			cpu_to_le16(BNXT_COAL_CMPL_AGGR_TMR_DURING_INT_ENABLE);
	पूर्ण

	अगर (cmpl_params & RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_TIMER_RESET)
		flags |= RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_TIMER_RESET;
	अगर ((cmpl_params & RING_AGGINT_QCAPS_RESP_CMPL_PARAMS_RING_IDLE) &&
	    hw_coal->idle_thresh && hw_coal->coal_ticks < hw_coal->idle_thresh)
		flags |= RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_RING_IDLE;
	req->flags = cpu_to_le16(flags);
	req->enables |= cpu_to_le16(BNXT_COAL_CMPL_ENABLES);
पूर्ण

/* Caller holds bp->hwrm_cmd_lock */
अटल पूर्णांक __bnxt_hwrm_set_coal_nq(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi,
				   काष्ठा bnxt_coal *hw_coal)
अणु
	काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input req = अणु0पूर्ण;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	काष्ठा bnxt_coal_cap *coal_cap = &bp->coal_cap;
	u32 nq_params = coal_cap->nq_params;
	u16 पंचांगr;

	अगर (!(nq_params & RING_AGGINT_QCAPS_RESP_NQ_PARAMS_INT_LAT_TMR_MIN))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS,
			       -1, -1);
	req.ring_id = cpu_to_le16(cpr->cp_ring_काष्ठा.fw_ring_id);
	req.flags =
		cpu_to_le16(RING_CMPL_RING_CFG_AGGINT_PARAMS_REQ_FLAGS_IS_NQ);

	पंचांगr = bnxt_usec_to_coal_पंचांगr(bp, hw_coal->coal_ticks) / 2;
	पंचांगr = clamp_t(u16, पंचांगr, 1, coal_cap->पूर्णांक_lat_पंचांगr_min_max);
	req.पूर्णांक_lat_पंचांगr_min = cpu_to_le16(पंचांगr);
	req.enables |= cpu_to_le16(BNXT_COAL_CMPL_MIN_TMR_ENABLE);
	वापस _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

पूर्णांक bnxt_hwrm_set_ring_coal(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi)
अणु
	काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input req_rx = अणु0पूर्ण;
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	काष्ठा bnxt_coal coal;

	/* Tick values in micro seconds.
	 * 1 coal_buf x bufs_per_record = 1 completion record.
	 */
	स_नकल(&coal, &bp->rx_coal, माप(काष्ठा bnxt_coal));

	coal.coal_ticks = cpr->rx_ring_coal.coal_ticks;
	coal.coal_bufs = cpr->rx_ring_coal.coal_bufs;

	अगर (!bnapi->rx_ring)
		वापस -ENODEV;

	bnxt_hwrm_cmd_hdr_init(bp, &req_rx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);

	bnxt_hwrm_set_coal_params(bp, &coal, &req_rx);

	req_rx.ring_id = cpu_to_le16(bnxt_cp_ring_क्रम_rx(bp, bnapi->rx_ring));

	वापस hwrm_send_message(bp, &req_rx, माप(req_rx),
				 HWRM_CMD_TIMEOUT);
पूर्ण

पूर्णांक bnxt_hwrm_set_coal(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा hwrm_ring_cmpl_ring_cfg_aggपूर्णांक_params_input req_rx = अणु0पूर्ण,
							   req_tx = अणु0पूर्ण, *req;

	bnxt_hwrm_cmd_hdr_init(bp, &req_rx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);
	bnxt_hwrm_cmd_hdr_init(bp, &req_tx,
			       HWRM_RING_CMPL_RING_CFG_AGGINT_PARAMS, -1, -1);

	bnxt_hwrm_set_coal_params(bp, &bp->rx_coal, &req_rx);
	bnxt_hwrm_set_coal_params(bp, &bp->tx_coal, &req_tx);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_coal *hw_coal;
		u16 ring_id;

		req = &req_rx;
		अगर (!bnapi->rx_ring) अणु
			ring_id = bnxt_cp_ring_क्रम_tx(bp, bnapi->tx_ring);
			req = &req_tx;
		पूर्ण अन्यथा अणु
			ring_id = bnxt_cp_ring_क्रम_rx(bp, bnapi->rx_ring);
		पूर्ण
		req->ring_id = cpu_to_le16(ring_id);

		rc = _hwrm_send_message(bp, req, माप(*req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;

		अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
			जारी;

		अगर (bnapi->rx_ring && bnapi->tx_ring) अणु
			req = &req_tx;
			ring_id = bnxt_cp_ring_क्रम_tx(bp, bnapi->tx_ring);
			req->ring_id = cpu_to_le16(ring_id);
			rc = _hwrm_send_message(bp, req, माप(*req),
						HWRM_CMD_TIMEOUT);
			अगर (rc)
				अवरोध;
		पूर्ण
		अगर (bnapi->rx_ring)
			hw_coal = &bp->rx_coal;
		अन्यथा
			hw_coal = &bp->tx_coal;
		__bnxt_hwrm_set_coal_nq(bp, bnapi, hw_coal);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_hwrm_stat_ctx_मुक्त(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_stat_ctx_clr_stats_input req0 = अणु0पूर्ण;
	काष्ठा hwrm_stat_ctx_मुक्त_input req = अणु0पूर्ण;
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		वापस;

	bnxt_hwrm_cmd_hdr_init(bp, &req0, HWRM_STAT_CTX_CLR_STATS, -1, -1);
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_STAT_CTX_FREE, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		अगर (cpr->hw_stats_ctx_id != INVALID_STATS_CTX_ID) अणु
			req.stat_ctx_id = cpu_to_le32(cpr->hw_stats_ctx_id);
			अगर (BNXT_FW_MAJ(bp) <= 20) अणु
				req0.stat_ctx_id = req.stat_ctx_id;
				_hwrm_send_message(bp, &req0, माप(req0),
						   HWRM_CMD_TIMEOUT);
			पूर्ण
			_hwrm_send_message(bp, &req, माप(req),
					   HWRM_CMD_TIMEOUT);

			cpr->hw_stats_ctx_id = INVALID_STATS_CTX_ID;
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
पूर्ण

अटल पूर्णांक bnxt_hwrm_stat_ctx_alloc(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0, i;
	काष्ठा hwrm_stat_ctx_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_stat_ctx_alloc_output *resp = bp->hwrm_cmd_resp_addr;

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_STAT_CTX_ALLOC, -1, -1);

	req.stats_dma_length = cpu_to_le16(bp->hw_ring_stats_size);
	req.update_period_ms = cpu_to_le32(bp->stats_coal_ticks / 1000);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		req.stats_dma_addr = cpu_to_le64(cpr->stats.hw_stats_map);

		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;

		cpr->hw_stats_ctx_id = le32_to_cpu(resp->stat_ctx_id);

		bp->grp_info[i].fw_stats_ctx = cpr->hw_stats_ctx_id;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_qcfg(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_qcfg_input req = अणु0पूर्ण;
	काष्ठा hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	u32 min_db_offset = 0;
	u16 flags;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ func_qcfg_निकास;

#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (BNXT_VF(bp)) अणु
		काष्ठा bnxt_vf_info *vf = &bp->vf;

		vf->vlan = le16_to_cpu(resp->vlan) & VLAN_VID_MASK;
	पूर्ण अन्यथा अणु
		bp->pf.रेजिस्टरed_vfs = le16_to_cpu(resp->रेजिस्टरed_vfs);
	पूर्ण
#पूर्ण_अगर
	flags = le16_to_cpu(resp->flags);
	अगर (flags & (FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED |
		     FUNC_QCFG_RESP_FLAGS_FW_LLDP_AGENT_ENABLED)) अणु
		bp->fw_cap |= BNXT_FW_CAP_LLDP_AGENT;
		अगर (flags & FUNC_QCFG_RESP_FLAGS_FW_DCBX_AGENT_ENABLED)
			bp->fw_cap |= BNXT_FW_CAP_DCBX_AGENT;
	पूर्ण
	अगर (BNXT_PF(bp) && (flags & FUNC_QCFG_RESP_FLAGS_MULTI_HOST))
		bp->flags |= BNXT_FLAG_MULTI_HOST;
	अगर (flags & FUNC_QCFG_RESP_FLAGS_RING_MONITOR_ENABLED)
		bp->fw_cap |= BNXT_FW_CAP_RING_MONITOR;

	चयन (resp->port_partition_type) अणु
	हाल FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_0:
	हाल FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR1_5:
	हाल FUNC_QCFG_RESP_PORT_PARTITION_TYPE_NPAR2_0:
		bp->port_partition_type = resp->port_partition_type;
		अवरोध;
	पूर्ण
	अगर (bp->hwrm_spec_code < 0x10707 ||
	    resp->evb_mode == FUNC_QCFG_RESP_EVB_MODE_VEB)
		bp->br_mode = BRIDGE_MODE_VEB;
	अन्यथा अगर (resp->evb_mode == FUNC_QCFG_RESP_EVB_MODE_VEPA)
		bp->br_mode = BRIDGE_MODE_VEPA;
	अन्यथा
		bp->br_mode = BRIDGE_MODE_UNDEF;

	bp->max_mtu = le16_to_cpu(resp->max_mtu_configured);
	अगर (!bp->max_mtu)
		bp->max_mtu = BNXT_MAX_MTU;

	अगर (bp->db_size)
		जाओ func_qcfg_निकास;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		अगर (BNXT_PF(bp))
			min_db_offset = DB_PF_OFFSET_P5;
		अन्यथा
			min_db_offset = DB_VF_OFFSET_P5;
	पूर्ण
	bp->db_size = PAGE_ALIGN(le16_to_cpu(resp->l2_करोorbell_bar_size_kb) *
				 1024);
	अगर (!bp->db_size || bp->db_size > pci_resource_len(bp->pdev, 2) ||
	    bp->db_size <= min_db_offset)
		bp->db_size = pci_resource_len(bp->pdev, 2);

func_qcfg_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_init_ctx_initializer(काष्ठा bnxt_ctx_mem_info *ctx,
			काष्ठा hwrm_func_backing_store_qcaps_output *resp)
अणु
	काष्ठा bnxt_mem_init *mem_init;
	u16 init_mask;
	u8 init_val;
	u8 *offset;
	पूर्णांक i;

	init_val = resp->ctx_kind_initializer;
	init_mask = le16_to_cpu(resp->ctx_init_mask);
	offset = &resp->qp_init_offset;
	mem_init = &ctx->mem_init[BNXT_CTX_MEM_INIT_QP];
	क्रम (i = 0; i < BNXT_CTX_MEM_INIT_MAX; i++, mem_init++, offset++) अणु
		mem_init->init_val = init_val;
		mem_init->offset = BNXT_MEM_INVALID_OFFSET;
		अगर (!init_mask)
			जारी;
		अगर (i == BNXT_CTX_MEM_INIT_STAT)
			offset = &resp->stat_init_offset;
		अगर (init_mask & (1 << i))
			mem_init->offset = *offset * 4;
		अन्यथा
			mem_init->init_val = 0;
	पूर्ण
	ctx->mem_init[BNXT_CTX_MEM_INIT_QP].size = ctx->qp_entry_size;
	ctx->mem_init[BNXT_CTX_MEM_INIT_SRQ].size = ctx->srq_entry_size;
	ctx->mem_init[BNXT_CTX_MEM_INIT_CQ].size = ctx->cq_entry_size;
	ctx->mem_init[BNXT_CTX_MEM_INIT_VNIC].size = ctx->vnic_entry_size;
	ctx->mem_init[BNXT_CTX_MEM_INIT_STAT].size = ctx->stat_entry_size;
	ctx->mem_init[BNXT_CTX_MEM_INIT_MRAV].size = ctx->mrav_entry_size;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_backing_store_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_backing_store_qcaps_input req = अणु0पूर्ण;
	काष्ठा hwrm_func_backing_store_qcaps_output *resp =
		bp->hwrm_cmd_resp_addr;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10902 || BNXT_VF(bp) || bp->ctx)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_BACKING_STORE_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		काष्ठा bnxt_ctx_pg_info *ctx_pg;
		काष्ठा bnxt_ctx_mem_info *ctx;
		पूर्णांक i, tqm_rings;

		ctx = kzalloc(माप(*ctx), GFP_KERNEL);
		अगर (!ctx) अणु
			rc = -ENOMEM;
			जाओ ctx_err;
		पूर्ण
		ctx->qp_max_entries = le32_to_cpu(resp->qp_max_entries);
		ctx->qp_min_qp1_entries = le16_to_cpu(resp->qp_min_qp1_entries);
		ctx->qp_max_l2_entries = le16_to_cpu(resp->qp_max_l2_entries);
		ctx->qp_entry_size = le16_to_cpu(resp->qp_entry_size);
		ctx->srq_max_l2_entries = le16_to_cpu(resp->srq_max_l2_entries);
		ctx->srq_max_entries = le32_to_cpu(resp->srq_max_entries);
		ctx->srq_entry_size = le16_to_cpu(resp->srq_entry_size);
		ctx->cq_max_l2_entries = le16_to_cpu(resp->cq_max_l2_entries);
		ctx->cq_max_entries = le32_to_cpu(resp->cq_max_entries);
		ctx->cq_entry_size = le16_to_cpu(resp->cq_entry_size);
		ctx->vnic_max_vnic_entries =
			le16_to_cpu(resp->vnic_max_vnic_entries);
		ctx->vnic_max_ring_table_entries =
			le16_to_cpu(resp->vnic_max_ring_table_entries);
		ctx->vnic_entry_size = le16_to_cpu(resp->vnic_entry_size);
		ctx->stat_max_entries = le32_to_cpu(resp->stat_max_entries);
		ctx->stat_entry_size = le16_to_cpu(resp->stat_entry_size);
		ctx->tqm_entry_size = le16_to_cpu(resp->tqm_entry_size);
		ctx->tqm_min_entries_per_ring =
			le32_to_cpu(resp->tqm_min_entries_per_ring);
		ctx->tqm_max_entries_per_ring =
			le32_to_cpu(resp->tqm_max_entries_per_ring);
		ctx->tqm_entries_multiple = resp->tqm_entries_multiple;
		अगर (!ctx->tqm_entries_multiple)
			ctx->tqm_entries_multiple = 1;
		ctx->mrav_max_entries = le32_to_cpu(resp->mrav_max_entries);
		ctx->mrav_entry_size = le16_to_cpu(resp->mrav_entry_size);
		ctx->mrav_num_entries_units =
			le16_to_cpu(resp->mrav_num_entries_units);
		ctx->tim_entry_size = le16_to_cpu(resp->tim_entry_size);
		ctx->tim_max_entries = le32_to_cpu(resp->tim_max_entries);

		bnxt_init_ctx_initializer(ctx, resp);

		ctx->tqm_fp_rings_count = resp->tqm_fp_rings_count;
		अगर (!ctx->tqm_fp_rings_count)
			ctx->tqm_fp_rings_count = bp->max_q;
		अन्यथा अगर (ctx->tqm_fp_rings_count > BNXT_MAX_TQM_FP_RINGS)
			ctx->tqm_fp_rings_count = BNXT_MAX_TQM_FP_RINGS;

		tqm_rings = ctx->tqm_fp_rings_count + BNXT_MAX_TQM_SP_RINGS;
		ctx_pg = kसुस्मृति(tqm_rings, माप(*ctx_pg), GFP_KERNEL);
		अगर (!ctx_pg) अणु
			kमुक्त(ctx);
			rc = -ENOMEM;
			जाओ ctx_err;
		पूर्ण
		क्रम (i = 0; i < tqm_rings; i++, ctx_pg++)
			ctx->tqm_mem[i] = ctx_pg;
		bp->ctx = ctx;
	पूर्ण अन्यथा अणु
		rc = 0;
	पूर्ण
ctx_err:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_hwrm_set_pg_attr(काष्ठा bnxt_ring_mem_info *rmem, u8 *pg_attr,
				  __le64 *pg_dir)
अणु
	अगर (!rmem->nr_pages)
		वापस;

	BNXT_SET_CTX_PAGE_ATTR(*pg_attr);
	अगर (rmem->depth >= 1) अणु
		अगर (rmem->depth == 2)
			*pg_attr |= 2;
		अन्यथा
			*pg_attr |= 1;
		*pg_dir = cpu_to_le64(rmem->pg_tbl_map);
	पूर्ण अन्यथा अणु
		*pg_dir = cpu_to_le64(rmem->dma_arr[0]);
	पूर्ण
पूर्ण

#घोषणा FUNC_BACKING_STORE_CFG_REQ_DFLT_ENABLES			\
	(FUNC_BACKING_STORE_CFG_REQ_ENABLES_QP |		\
	 FUNC_BACKING_STORE_CFG_REQ_ENABLES_SRQ |		\
	 FUNC_BACKING_STORE_CFG_REQ_ENABLES_CQ |		\
	 FUNC_BACKING_STORE_CFG_REQ_ENABLES_VNIC |		\
	 FUNC_BACKING_STORE_CFG_REQ_ENABLES_STAT)

अटल पूर्णांक bnxt_hwrm_func_backing_store_cfg(काष्ठा bnxt *bp, u32 enables)
अणु
	काष्ठा hwrm_func_backing_store_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_ctx_mem_info *ctx = bp->ctx;
	काष्ठा bnxt_ctx_pg_info *ctx_pg;
	u32 req_len = माप(req);
	__le32 *num_entries;
	__le64 *pg_dir;
	u32 flags = 0;
	u8 *pg_attr;
	u32 ena;
	पूर्णांक i;

	अगर (!ctx)
		वापस 0;

	अगर (req_len > bp->hwrm_max_ext_req_len)
		req_len = BNXT_BACKING_STORE_CFG_LEGACY_LEN;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_BACKING_STORE_CFG, -1, -1);
	req.enables = cpu_to_le32(enables);

	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_QP) अणु
		ctx_pg = &ctx->qp_mem;
		req.qp_num_entries = cpu_to_le32(ctx_pg->entries);
		req.qp_num_qp1_entries = cpu_to_le16(ctx->qp_min_qp1_entries);
		req.qp_num_l2_entries = cpu_to_le16(ctx->qp_max_l2_entries);
		req.qp_entry_size = cpu_to_le16(ctx->qp_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.qpc_pg_size_qpc_lvl,
				      &req.qpc_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_SRQ) अणु
		ctx_pg = &ctx->srq_mem;
		req.srq_num_entries = cpu_to_le32(ctx_pg->entries);
		req.srq_num_l2_entries = cpu_to_le16(ctx->srq_max_l2_entries);
		req.srq_entry_size = cpu_to_le16(ctx->srq_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.srq_pg_size_srq_lvl,
				      &req.srq_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_CQ) अणु
		ctx_pg = &ctx->cq_mem;
		req.cq_num_entries = cpu_to_le32(ctx_pg->entries);
		req.cq_num_l2_entries = cpu_to_le16(ctx->cq_max_l2_entries);
		req.cq_entry_size = cpu_to_le16(ctx->cq_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem, &req.cq_pg_size_cq_lvl,
				      &req.cq_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_VNIC) अणु
		ctx_pg = &ctx->vnic_mem;
		req.vnic_num_vnic_entries =
			cpu_to_le16(ctx->vnic_max_vnic_entries);
		req.vnic_num_ring_table_entries =
			cpu_to_le16(ctx->vnic_max_ring_table_entries);
		req.vnic_entry_size = cpu_to_le16(ctx->vnic_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.vnic_pg_size_vnic_lvl,
				      &req.vnic_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_STAT) अणु
		ctx_pg = &ctx->stat_mem;
		req.stat_num_entries = cpu_to_le32(ctx->stat_max_entries);
		req.stat_entry_size = cpu_to_le16(ctx->stat_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.stat_pg_size_stat_lvl,
				      &req.stat_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_MRAV) अणु
		ctx_pg = &ctx->mrav_mem;
		req.mrav_num_entries = cpu_to_le32(ctx_pg->entries);
		अगर (ctx->mrav_num_entries_units)
			flags |=
			FUNC_BACKING_STORE_CFG_REQ_FLAGS_MRAV_RESERVATION_SPLIT;
		req.mrav_entry_size = cpu_to_le16(ctx->mrav_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.mrav_pg_size_mrav_lvl,
				      &req.mrav_page_dir);
	पूर्ण
	अगर (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_TIM) अणु
		ctx_pg = &ctx->tim_mem;
		req.tim_num_entries = cpu_to_le32(ctx_pg->entries);
		req.tim_entry_size = cpu_to_le16(ctx->tim_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.tim_pg_माप_प्रकारim_lvl,
				      &req.tim_page_dir);
	पूर्ण
	क्रम (i = 0, num_entries = &req.tqm_sp_num_entries,
	     pg_attr = &req.tqm_sp_pg_माप_प्रकारqm_sp_lvl,
	     pg_dir = &req.tqm_sp_page_dir,
	     ena = FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_SP;
	     i < BNXT_MAX_TQM_RINGS;
	     i++, num_entries++, pg_attr++, pg_dir++, ena <<= 1) अणु
		अगर (!(enables & ena))
			जारी;

		req.tqm_entry_size = cpu_to_le16(ctx->tqm_entry_size);
		ctx_pg = ctx->tqm_mem[i];
		*num_entries = cpu_to_le32(ctx_pg->entries);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem, pg_attr, pg_dir);
	पूर्ण
	req.flags = cpu_to_le32(flags);
	वापस hwrm_send_message(bp, &req, req_len, HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_alloc_ctx_mem_blk(काष्ठा bnxt *bp,
				  काष्ठा bnxt_ctx_pg_info *ctx_pg)
अणु
	काष्ठा bnxt_ring_mem_info *rmem = &ctx_pg->ring_mem;

	rmem->page_size = BNXT_PAGE_SIZE;
	rmem->pg_arr = ctx_pg->ctx_pg_arr;
	rmem->dma_arr = ctx_pg->ctx_dma_arr;
	rmem->flags = BNXT_RMEM_VALID_PTE_FLAG;
	अगर (rmem->depth >= 1)
		rmem->flags |= BNXT_RMEM_USE_FULL_PAGE_FLAG;
	वापस bnxt_alloc_ring(bp, rmem);
पूर्ण

अटल पूर्णांक bnxt_alloc_ctx_pg_tbls(काष्ठा bnxt *bp,
				  काष्ठा bnxt_ctx_pg_info *ctx_pg, u32 mem_size,
				  u8 depth, काष्ठा bnxt_mem_init *mem_init)
अणु
	काष्ठा bnxt_ring_mem_info *rmem = &ctx_pg->ring_mem;
	पूर्णांक rc;

	अगर (!mem_size)
		वापस -EINVAL;

	ctx_pg->nr_pages = DIV_ROUND_UP(mem_size, BNXT_PAGE_SIZE);
	अगर (ctx_pg->nr_pages > MAX_CTX_TOTAL_PAGES) अणु
		ctx_pg->nr_pages = 0;
		वापस -EINVAL;
	पूर्ण
	अगर (ctx_pg->nr_pages > MAX_CTX_PAGES || depth > 1) अणु
		पूर्णांक nr_tbls, i;

		rmem->depth = 2;
		ctx_pg->ctx_pg_tbl = kसुस्मृति(MAX_CTX_PAGES, माप(ctx_pg),
					     GFP_KERNEL);
		अगर (!ctx_pg->ctx_pg_tbl)
			वापस -ENOMEM;
		nr_tbls = DIV_ROUND_UP(ctx_pg->nr_pages, MAX_CTX_PAGES);
		rmem->nr_pages = nr_tbls;
		rc = bnxt_alloc_ctx_mem_blk(bp, ctx_pg);
		अगर (rc)
			वापस rc;
		क्रम (i = 0; i < nr_tbls; i++) अणु
			काष्ठा bnxt_ctx_pg_info *pg_tbl;

			pg_tbl = kzalloc(माप(*pg_tbl), GFP_KERNEL);
			अगर (!pg_tbl)
				वापस -ENOMEM;
			ctx_pg->ctx_pg_tbl[i] = pg_tbl;
			rmem = &pg_tbl->ring_mem;
			rmem->pg_tbl = ctx_pg->ctx_pg_arr[i];
			rmem->pg_tbl_map = ctx_pg->ctx_dma_arr[i];
			rmem->depth = 1;
			rmem->nr_pages = MAX_CTX_PAGES;
			rmem->mem_init = mem_init;
			अगर (i == (nr_tbls - 1)) अणु
				पूर्णांक rem = ctx_pg->nr_pages % MAX_CTX_PAGES;

				अगर (rem)
					rmem->nr_pages = rem;
			पूर्ण
			rc = bnxt_alloc_ctx_mem_blk(bp, pg_tbl);
			अगर (rc)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rmem->nr_pages = DIV_ROUND_UP(mem_size, BNXT_PAGE_SIZE);
		अगर (rmem->nr_pages > 1 || depth)
			rmem->depth = 1;
		rmem->mem_init = mem_init;
		rc = bnxt_alloc_ctx_mem_blk(bp, ctx_pg);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_मुक्त_ctx_pg_tbls(काष्ठा bnxt *bp,
				  काष्ठा bnxt_ctx_pg_info *ctx_pg)
अणु
	काष्ठा bnxt_ring_mem_info *rmem = &ctx_pg->ring_mem;

	अगर (rmem->depth > 1 || ctx_pg->nr_pages > MAX_CTX_PAGES ||
	    ctx_pg->ctx_pg_tbl) अणु
		पूर्णांक i, nr_tbls = rmem->nr_pages;

		क्रम (i = 0; i < nr_tbls; i++) अणु
			काष्ठा bnxt_ctx_pg_info *pg_tbl;
			काष्ठा bnxt_ring_mem_info *rmem2;

			pg_tbl = ctx_pg->ctx_pg_tbl[i];
			अगर (!pg_tbl)
				जारी;
			rmem2 = &pg_tbl->ring_mem;
			bnxt_मुक्त_ring(bp, rmem2);
			ctx_pg->ctx_pg_arr[i] = शून्य;
			kमुक्त(pg_tbl);
			ctx_pg->ctx_pg_tbl[i] = शून्य;
		पूर्ण
		kमुक्त(ctx_pg->ctx_pg_tbl);
		ctx_pg->ctx_pg_tbl = शून्य;
	पूर्ण
	bnxt_मुक्त_ring(bp, rmem);
	ctx_pg->nr_pages = 0;
पूर्ण

अटल व्योम bnxt_मुक्त_ctx_mem(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_ctx_mem_info *ctx = bp->ctx;
	पूर्णांक i;

	अगर (!ctx)
		वापस;

	अगर (ctx->tqm_mem[0]) अणु
		क्रम (i = 0; i < ctx->tqm_fp_rings_count + 1; i++)
			bnxt_मुक्त_ctx_pg_tbls(bp, ctx->tqm_mem[i]);
		kमुक्त(ctx->tqm_mem[0]);
		ctx->tqm_mem[0] = शून्य;
	पूर्ण

	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->tim_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->mrav_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->stat_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->vnic_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->cq_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->srq_mem);
	bnxt_मुक्त_ctx_pg_tbls(bp, &ctx->qp_mem);
	ctx->flags &= ~BNXT_CTX_FLAG_INITED;
पूर्ण

अटल पूर्णांक bnxt_alloc_ctx_mem(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_ctx_pg_info *ctx_pg;
	काष्ठा bnxt_ctx_mem_info *ctx;
	काष्ठा bnxt_mem_init *init;
	u32 mem_size, ena, entries;
	u32 entries_sp, min;
	u32 num_mr, num_ah;
	u32 extra_srqs = 0;
	u32 extra_qps = 0;
	u8 pg_lvl = 1;
	पूर्णांक i, rc;

	rc = bnxt_hwrm_func_backing_store_qcaps(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "Failed querying context mem capability, rc = %d.\n",
			   rc);
		वापस rc;
	पूर्ण
	ctx = bp->ctx;
	अगर (!ctx || (ctx->flags & BNXT_CTX_FLAG_INITED))
		वापस 0;

	अगर ((bp->flags & BNXT_FLAG_ROCE_CAP) && !is_kdump_kernel()) अणु
		pg_lvl = 2;
		extra_qps = 65536;
		extra_srqs = 8192;
	पूर्ण

	ctx_pg = &ctx->qp_mem;
	ctx_pg->entries = ctx->qp_min_qp1_entries + ctx->qp_max_l2_entries +
			  extra_qps;
	अगर (ctx->qp_entry_size) अणु
		mem_size = ctx->qp_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_QP];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, pg_lvl, init);
		अगर (rc)
			वापस rc;
	पूर्ण

	ctx_pg = &ctx->srq_mem;
	ctx_pg->entries = ctx->srq_max_l2_entries + extra_srqs;
	अगर (ctx->srq_entry_size) अणु
		mem_size = ctx->srq_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_SRQ];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, pg_lvl, init);
		अगर (rc)
			वापस rc;
	पूर्ण

	ctx_pg = &ctx->cq_mem;
	ctx_pg->entries = ctx->cq_max_l2_entries + extra_qps * 2;
	अगर (ctx->cq_entry_size) अणु
		mem_size = ctx->cq_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_CQ];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, pg_lvl, init);
		अगर (rc)
			वापस rc;
	पूर्ण

	ctx_pg = &ctx->vnic_mem;
	ctx_pg->entries = ctx->vnic_max_vnic_entries +
			  ctx->vnic_max_ring_table_entries;
	अगर (ctx->vnic_entry_size) अणु
		mem_size = ctx->vnic_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_VNIC];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, 1, init);
		अगर (rc)
			वापस rc;
	पूर्ण

	ctx_pg = &ctx->stat_mem;
	ctx_pg->entries = ctx->stat_max_entries;
	अगर (ctx->stat_entry_size) अणु
		mem_size = ctx->stat_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_STAT];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, 1, init);
		अगर (rc)
			वापस rc;
	पूर्ण

	ena = 0;
	अगर (!(bp->flags & BNXT_FLAG_ROCE_CAP))
		जाओ skip_rdma;

	ctx_pg = &ctx->mrav_mem;
	/* 128K extra is needed to accommodate अटल AH context
	 * allocation by f/w.
	 */
	num_mr = 1024 * 256;
	num_ah = 1024 * 128;
	ctx_pg->entries = num_mr + num_ah;
	अगर (ctx->mrav_entry_size) अणु
		mem_size = ctx->mrav_entry_size * ctx_pg->entries;
		init = &ctx->mem_init[BNXT_CTX_MEM_INIT_MRAV];
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, 2, init);
		अगर (rc)
			वापस rc;
	पूर्ण
	ena = FUNC_BACKING_STORE_CFG_REQ_ENABLES_MRAV;
	अगर (ctx->mrav_num_entries_units)
		ctx_pg->entries =
			((num_mr / ctx->mrav_num_entries_units) << 16) |
			 (num_ah / ctx->mrav_num_entries_units);

	ctx_pg = &ctx->tim_mem;
	ctx_pg->entries = ctx->qp_mem.entries;
	अगर (ctx->tim_entry_size) अणु
		mem_size = ctx->tim_entry_size * ctx_pg->entries;
		rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, 1, शून्य);
		अगर (rc)
			वापस rc;
	पूर्ण
	ena |= FUNC_BACKING_STORE_CFG_REQ_ENABLES_TIM;

skip_rdma:
	min = ctx->tqm_min_entries_per_ring;
	entries_sp = ctx->vnic_max_vnic_entries + ctx->qp_max_l2_entries +
		     2 * (extra_qps + ctx->qp_min_qp1_entries) + min;
	entries_sp = roundup(entries_sp, ctx->tqm_entries_multiple);
	entries = ctx->qp_max_l2_entries + 2 * (extra_qps + ctx->qp_min_qp1_entries);
	entries = roundup(entries, ctx->tqm_entries_multiple);
	entries = clamp_t(u32, entries, min, ctx->tqm_max_entries_per_ring);
	क्रम (i = 0; i < ctx->tqm_fp_rings_count + 1; i++) अणु
		ctx_pg = ctx->tqm_mem[i];
		ctx_pg->entries = i ? entries : entries_sp;
		अगर (ctx->tqm_entry_size) अणु
			mem_size = ctx->tqm_entry_size * ctx_pg->entries;
			rc = bnxt_alloc_ctx_pg_tbls(bp, ctx_pg, mem_size, 1,
						    शून्य);
			अगर (rc)
				वापस rc;
		पूर्ण
		ena |= FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_SP << i;
	पूर्ण
	ena |= FUNC_BACKING_STORE_CFG_REQ_DFLT_ENABLES;
	rc = bnxt_hwrm_func_backing_store_cfg(bp, ena);
	अगर (rc) अणु
		netdev_err(bp->dev, "Failed configuring context mem, rc = %d.\n",
			   rc);
		वापस rc;
	पूर्ण
	ctx->flags |= BNXT_CTX_FLAG_INITED;
	वापस 0;
पूर्ण

पूर्णांक bnxt_hwrm_func_resc_qcaps(काष्ठा bnxt *bp, bool all)
अणु
	काष्ठा hwrm_func_resource_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_resource_qcaps_input req = अणु0पूर्ण;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_RESOURCE_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, माप(req),
				       HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ hwrm_func_resc_qcaps_निकास;

	hw_resc->max_tx_sch_inमाला_दो = le16_to_cpu(resp->max_tx_scheduler_inमाला_दो);
	अगर (!all)
		जाओ hwrm_func_resc_qcaps_निकास;

	hw_resc->min_rsscos_ctxs = le16_to_cpu(resp->min_rsscos_ctx);
	hw_resc->max_rsscos_ctxs = le16_to_cpu(resp->max_rsscos_ctx);
	hw_resc->min_cp_rings = le16_to_cpu(resp->min_cmpl_rings);
	hw_resc->max_cp_rings = le16_to_cpu(resp->max_cmpl_rings);
	hw_resc->min_tx_rings = le16_to_cpu(resp->min_tx_rings);
	hw_resc->max_tx_rings = le16_to_cpu(resp->max_tx_rings);
	hw_resc->min_rx_rings = le16_to_cpu(resp->min_rx_rings);
	hw_resc->max_rx_rings = le16_to_cpu(resp->max_rx_rings);
	hw_resc->min_hw_ring_grps = le16_to_cpu(resp->min_hw_ring_grps);
	hw_resc->max_hw_ring_grps = le16_to_cpu(resp->max_hw_ring_grps);
	hw_resc->min_l2_ctxs = le16_to_cpu(resp->min_l2_ctxs);
	hw_resc->max_l2_ctxs = le16_to_cpu(resp->max_l2_ctxs);
	hw_resc->min_vnics = le16_to_cpu(resp->min_vnics);
	hw_resc->max_vnics = le16_to_cpu(resp->max_vnics);
	hw_resc->min_stat_ctxs = le16_to_cpu(resp->min_stat_ctx);
	hw_resc->max_stat_ctxs = le16_to_cpu(resp->max_stat_ctx);

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		u16 max_msix = le16_to_cpu(resp->max_msix);

		hw_resc->max_nqs = max_msix;
		hw_resc->max_hw_ring_grps = hw_resc->max_rx_rings;
	पूर्ण

	अगर (BNXT_PF(bp)) अणु
		काष्ठा bnxt_pf_info *pf = &bp->pf;

		pf->vf_resv_strategy =
			le16_to_cpu(resp->vf_reservation_strategy);
		अगर (pf->vf_resv_strategy > BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC)
			pf->vf_resv_strategy = BNXT_VF_RESV_STRATEGY_MAXIMAL;
	पूर्ण
hwrm_func_resc_qcaps_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक __bnxt_hwrm_func_qcaps(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_func_qcaps_input req = अणु0पूर्ण;
	काष्ठा hwrm_func_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	u32 flags, flags_ext;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ hwrm_func_qcaps_निकास;

	flags = le32_to_cpu(resp->flags);
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_ROCE_V1_SUPPORTED)
		bp->flags |= BNXT_FLAG_ROCEV1_CAP;
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_ROCE_V2_SUPPORTED)
		bp->flags |= BNXT_FLAG_ROCEV2_CAP;
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_PCIE_STATS_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_PCIE_STATS_SUPPORTED;
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_HOT_RESET_CAPABLE)
		bp->fw_cap |= BNXT_FW_CAP_HOT_RESET;
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_EXT_STATS_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_EXT_STATS_SUPPORTED;
	अगर (flags &  FUNC_QCAPS_RESP_FLAGS_ERROR_RECOVERY_CAPABLE)
		bp->fw_cap |= BNXT_FW_CAP_ERROR_RECOVERY;
	अगर (flags & FUNC_QCAPS_RESP_FLAGS_ERR_RECOVER_RELOAD)
		bp->fw_cap |= BNXT_FW_CAP_ERR_RECOVER_RELOAD;
	अगर (!(flags & FUNC_QCAPS_RESP_FLAGS_VLAN_ACCELERATION_TX_DISABLED))
		bp->fw_cap |= BNXT_FW_CAP_VLAN_TX_INSERT;

	flags_ext = le32_to_cpu(resp->flags_ext);
	अगर (flags_ext & FUNC_QCAPS_RESP_FLAGS_EXT_EXT_HW_STATS_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED;

	bp->tx_push_thresh = 0;
	अगर ((flags & FUNC_QCAPS_RESP_FLAGS_PUSH_MODE_SUPPORTED) &&
	    BNXT_FW_MAJ(bp) > 217)
		bp->tx_push_thresh = BNXT_TX_PUSH_THRESH;

	hw_resc->max_rsscos_ctxs = le16_to_cpu(resp->max_rsscos_ctx);
	hw_resc->max_cp_rings = le16_to_cpu(resp->max_cmpl_rings);
	hw_resc->max_tx_rings = le16_to_cpu(resp->max_tx_rings);
	hw_resc->max_rx_rings = le16_to_cpu(resp->max_rx_rings);
	hw_resc->max_hw_ring_grps = le32_to_cpu(resp->max_hw_ring_grps);
	अगर (!hw_resc->max_hw_ring_grps)
		hw_resc->max_hw_ring_grps = hw_resc->max_tx_rings;
	hw_resc->max_l2_ctxs = le16_to_cpu(resp->max_l2_ctxs);
	hw_resc->max_vnics = le16_to_cpu(resp->max_vnics);
	hw_resc->max_stat_ctxs = le16_to_cpu(resp->max_stat_ctx);

	अगर (BNXT_PF(bp)) अणु
		काष्ठा bnxt_pf_info *pf = &bp->pf;

		pf->fw_fid = le16_to_cpu(resp->fid);
		pf->port_id = le16_to_cpu(resp->port_id);
		स_नकल(pf->mac_addr, resp->mac_address, ETH_ALEN);
		pf->first_vf_id = le16_to_cpu(resp->first_vf_id);
		pf->max_vfs = le16_to_cpu(resp->max_vfs);
		pf->max_encap_records = le32_to_cpu(resp->max_encap_records);
		pf->max_decap_records = le32_to_cpu(resp->max_decap_records);
		pf->max_tx_em_flows = le32_to_cpu(resp->max_tx_em_flows);
		pf->max_tx_wm_flows = le32_to_cpu(resp->max_tx_wm_flows);
		pf->max_rx_em_flows = le32_to_cpu(resp->max_rx_em_flows);
		pf->max_rx_wm_flows = le32_to_cpu(resp->max_rx_wm_flows);
		bp->flags &= ~BNXT_FLAG_WOL_CAP;
		अगर (flags & FUNC_QCAPS_RESP_FLAGS_WOL_MAGICPKT_SUPPORTED)
			bp->flags |= BNXT_FLAG_WOL_CAP;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
		काष्ठा bnxt_vf_info *vf = &bp->vf;

		vf->fw_fid = le16_to_cpu(resp->fid);
		स_नकल(vf->mac_addr, resp->mac_address, ETH_ALEN);
#पूर्ण_अगर
	पूर्ण

hwrm_func_qcaps_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_qportcfg(काष्ठा bnxt *bp);

अटल पूर्णांक bnxt_hwrm_func_qcaps(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	rc = __bnxt_hwrm_func_qcaps(bp);
	अगर (rc)
		वापस rc;
	rc = bnxt_hwrm_queue_qportcfg(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm query qportcfg failure rc: %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (bp->hwrm_spec_code >= 0x10803) अणु
		rc = bnxt_alloc_ctx_mem(bp);
		अगर (rc)
			वापस rc;
		rc = bnxt_hwrm_func_resc_qcaps(bp, true);
		अगर (!rc)
			bp->fw_cap |= BNXT_FW_CAP_NEW_RM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_cfa_adv_flow_mgnt_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_cfa_adv_flow_mgnt_qcaps_input req = अणु0पूर्ण;
	काष्ठा hwrm_cfa_adv_flow_mgnt_qcaps_output *resp;
	पूर्णांक rc = 0;
	u32 flags;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_CFA_ADV_FLOW))
		वापस 0;

	resp = bp->hwrm_cmd_resp_addr;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_ADV_FLOW_MGNT_QCAPS, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ hwrm_cfa_adv_qcaps_निकास;

	flags = le32_to_cpu(resp->flags);
	अगर (flags &
	    CFA_ADV_FLOW_MGNT_QCAPS_RESP_FLAGS_RFS_RING_TBL_IDX_V2_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX_V2;

hwrm_cfa_adv_qcaps_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक __bnxt_alloc_fw_health(काष्ठा bnxt *bp)
अणु
	अगर (bp->fw_health)
		वापस 0;

	bp->fw_health = kzalloc(माप(*bp->fw_health), GFP_KERNEL);
	अगर (!bp->fw_health)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_alloc_fw_health(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_HOT_RESET) &&
	    !(bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY))
		वापस 0;

	rc = __bnxt_alloc_fw_health(bp);
	अगर (rc) अणु
		bp->fw_cap &= ~BNXT_FW_CAP_HOT_RESET;
		bp->fw_cap &= ~BNXT_FW_CAP_ERROR_RECOVERY;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __bnxt_map_fw_health_reg(काष्ठा bnxt *bp, u32 reg)
अणु
	ग_लिखोl(reg & BNXT_GRC_BASE_MASK, bp->bar0 +
					 BNXT_GRCPF_REG_WINDOW_BASE_OUT +
					 BNXT_FW_HEALTH_WIN_MAP_OFF);
पूर्ण

bool bnxt_is_fw_healthy(काष्ठा bnxt *bp)
अणु
	अगर (bp->fw_health && bp->fw_health->status_reliable) अणु
		u32 fw_status;

		fw_status = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG);
		अगर (fw_status && !BNXT_FW_IS_HEALTHY(fw_status))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम bnxt_inv_fw_health_reg(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg_type;

	अगर (!fw_health || !fw_health->status_reliable)
		वापस;

	reg_type = BNXT_FW_HEALTH_REG_TYPE(fw_health->regs[BNXT_FW_HEALTH_REG]);
	अगर (reg_type == BNXT_FW_HEALTH_REG_TYPE_GRC)
		fw_health->status_reliable = false;
पूर्ण

अटल व्योम bnxt_try_map_fw_health_reg(काष्ठा bnxt *bp)
अणु
	व्योम __iomem *hs;
	u32 status_loc;
	u32 reg_type;
	u32 sig;

	अगर (bp->fw_health)
		bp->fw_health->status_reliable = false;

	__bnxt_map_fw_health_reg(bp, HCOMM_STATUS_STRUCT_LOC);
	hs = bp->bar0 + BNXT_FW_HEALTH_WIN_OFF(HCOMM_STATUS_STRUCT_LOC);

	sig = पढ़ोl(hs + दुरत्व(काष्ठा hcomm_status, sig_ver));
	अगर ((sig & HCOMM_STATUS_SIGNATURE_MASK) != HCOMM_STATUS_SIGNATURE_VAL) अणु
		अगर (!bp->chip_num) अणु
			__bnxt_map_fw_health_reg(bp, BNXT_GRC_REG_BASE);
			bp->chip_num = पढ़ोl(bp->bar0 +
					     BNXT_FW_HEALTH_WIN_BASE +
					     BNXT_GRC_REG_CHIP_NUM);
		पूर्ण
		अगर (!BNXT_CHIP_P5(bp))
			वापस;

		status_loc = BNXT_GRC_REG_STATUS_P5 |
			     BNXT_FW_HEALTH_REG_TYPE_BAR0;
	पूर्ण अन्यथा अणु
		status_loc = पढ़ोl(hs + दुरत्व(काष्ठा hcomm_status,
						 fw_status_loc));
	पूर्ण

	अगर (__bnxt_alloc_fw_health(bp)) अणु
		netdev_warn(bp->dev, "no memory for firmware status checks\n");
		वापस;
	पूर्ण

	bp->fw_health->regs[BNXT_FW_HEALTH_REG] = status_loc;
	reg_type = BNXT_FW_HEALTH_REG_TYPE(status_loc);
	अगर (reg_type == BNXT_FW_HEALTH_REG_TYPE_GRC) अणु
		__bnxt_map_fw_health_reg(bp, status_loc);
		bp->fw_health->mapped_regs[BNXT_FW_HEALTH_REG] =
			BNXT_FW_HEALTH_WIN_OFF(status_loc);
	पूर्ण

	bp->fw_health->status_reliable = true;
पूर्ण

अटल पूर्णांक bnxt_map_fw_health_regs(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg_base = 0xffffffff;
	पूर्णांक i;

	bp->fw_health->status_reliable = false;
	/* Only pre-map the monitoring GRC रेजिस्टरs using winकरोw 3 */
	क्रम (i = 0; i < 4; i++) अणु
		u32 reg = fw_health->regs[i];

		अगर (BNXT_FW_HEALTH_REG_TYPE(reg) != BNXT_FW_HEALTH_REG_TYPE_GRC)
			जारी;
		अगर (reg_base == 0xffffffff)
			reg_base = reg & BNXT_GRC_BASE_MASK;
		अगर ((reg & BNXT_GRC_BASE_MASK) != reg_base)
			वापस -दुस्फल;
		fw_health->mapped_regs[i] = BNXT_FW_HEALTH_WIN_OFF(reg);
	पूर्ण
	bp->fw_health->status_reliable = true;
	अगर (reg_base == 0xffffffff)
		वापस 0;

	__bnxt_map_fw_health_reg(bp, reg_base);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_error_recovery_qcfg(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_error_recovery_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	काष्ठा hwrm_error_recovery_qcfg_input req = अणु0पूर्ण;
	पूर्णांक rc, i;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_ERROR_RECOVERY_QCFG, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ err_recovery_out;
	fw_health->flags = le32_to_cpu(resp->flags);
	अगर ((fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU) &&
	    !(bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL)) अणु
		rc = -EINVAL;
		जाओ err_recovery_out;
	पूर्ण
	fw_health->polling_dsecs = le32_to_cpu(resp->driver_polling_freq);
	fw_health->master_func_रुको_dsecs =
		le32_to_cpu(resp->master_func_रुको_period);
	fw_health->normal_func_रुको_dsecs =
		le32_to_cpu(resp->normal_func_रुको_period);
	fw_health->post_reset_रुको_dsecs =
		le32_to_cpu(resp->master_func_रुको_period_after_reset);
	fw_health->post_reset_max_रुको_dsecs =
		le32_to_cpu(resp->max_bailout_समय_after_reset);
	fw_health->regs[BNXT_FW_HEALTH_REG] =
		le32_to_cpu(resp->fw_health_status_reg);
	fw_health->regs[BNXT_FW_HEARTBEAT_REG] =
		le32_to_cpu(resp->fw_heartbeat_reg);
	fw_health->regs[BNXT_FW_RESET_CNT_REG] =
		le32_to_cpu(resp->fw_reset_cnt_reg);
	fw_health->regs[BNXT_FW_RESET_INPROG_REG] =
		le32_to_cpu(resp->reset_inprogress_reg);
	fw_health->fw_reset_inprog_reg_mask =
		le32_to_cpu(resp->reset_inprogress_reg_mask);
	fw_health->fw_reset_seq_cnt = resp->reg_array_cnt;
	अगर (fw_health->fw_reset_seq_cnt >= 16) अणु
		rc = -EINVAL;
		जाओ err_recovery_out;
	पूर्ण
	क्रम (i = 0; i < fw_health->fw_reset_seq_cnt; i++) अणु
		fw_health->fw_reset_seq_regs[i] =
			le32_to_cpu(resp->reset_reg[i]);
		fw_health->fw_reset_seq_vals[i] =
			le32_to_cpu(resp->reset_reg_val[i]);
		fw_health->fw_reset_seq_delay_msec[i] =
			resp->delay_after_reset[i];
	पूर्ण
err_recovery_out:
	mutex_unlock(&bp->hwrm_cmd_lock);
	अगर (!rc)
		rc = bnxt_map_fw_health_regs(bp);
	अगर (rc)
		bp->fw_cap &= ~BNXT_FW_CAP_ERROR_RECOVERY;
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_reset(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_reset_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_RESET, -1, -1);
	req.enables = 0;

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_RESET_TIMEOUT);
पूर्ण

अटल व्योम bnxt_nvm_cfg_ver_get(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_nvm_get_dev_info_output nvm_info;

	अगर (!bnxt_hwrm_nvm_get_dev_info(bp, &nvm_info))
		snम_लिखो(bp->nvm_cfg_ver, FW_VER_STR_LEN, "%d.%d.%d",
			 nvm_info.nvm_cfg_ver_maj, nvm_info.nvm_cfg_ver_min,
			 nvm_info.nvm_cfg_ver_upd);
पूर्ण

अटल पूर्णांक bnxt_hwrm_queue_qportcfg(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_queue_qportcfg_input req = अणु0पूर्ण;
	काष्ठा hwrm_queue_qportcfg_output *resp = bp->hwrm_cmd_resp_addr;
	u8 i, j, *qptr;
	bool no_rdma;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_QUEUE_QPORTCFG, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ qportcfg_निकास;

	अगर (!resp->max_configurable_queues) अणु
		rc = -EINVAL;
		जाओ qportcfg_निकास;
	पूर्ण
	bp->max_tc = resp->max_configurable_queues;
	bp->max_lltc = resp->max_configurable_lossless_queues;
	अगर (bp->max_tc > BNXT_MAX_QUEUE)
		bp->max_tc = BNXT_MAX_QUEUE;

	no_rdma = !(bp->flags & BNXT_FLAG_ROCE_CAP);
	qptr = &resp->queue_id0;
	क्रम (i = 0, j = 0; i < bp->max_tc; i++) अणु
		bp->q_info[j].queue_id = *qptr;
		bp->q_ids[i] = *qptr++;
		bp->q_info[j].queue_profile = *qptr++;
		bp->tc_to_qidx[j] = j;
		अगर (!BNXT_CNPQ(bp->q_info[j].queue_profile) ||
		    (no_rdma && BNXT_PF(bp)))
			j++;
	पूर्ण
	bp->max_q = bp->max_tc;
	bp->max_tc = max_t(u8, j, 1);

	अगर (resp->queue_cfg_info & QUEUE_QPORTCFG_RESP_QUEUE_CFG_INFO_ASYM_CFG)
		bp->max_tc = 1;

	अगर (bp->max_lltc > bp->max_tc)
		bp->max_lltc = bp->max_tc;

qportcfg_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक __bnxt_hwrm_ver_get(काष्ठा bnxt *bp, bool silent)
अणु
	काष्ठा hwrm_ver_get_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VER_GET, -1, -1);
	req.hwrm_पूर्णांकf_maj = HWRM_VERSION_MAJOR;
	req.hwrm_पूर्णांकf_min = HWRM_VERSION_MINOR;
	req.hwrm_पूर्णांकf_upd = HWRM_VERSION_UPDATE;

	rc = bnxt_hwrm_करो_send_msg(bp, &req, माप(req), HWRM_CMD_TIMEOUT,
				   silent);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_ver_get(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_ver_get_output *resp = bp->hwrm_cmd_resp_addr;
	u16 fw_maj, fw_min, fw_bld, fw_rsv;
	u32 dev_caps_cfg, hwrm_ver;
	पूर्णांक rc, len;

	bp->hwrm_max_req_len = HWRM_MAX_REQ_LEN;
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = __bnxt_hwrm_ver_get(bp, false);
	अगर (rc)
		जाओ hwrm_ver_get_निकास;

	स_नकल(&bp->ver_resp, resp, माप(काष्ठा hwrm_ver_get_output));

	bp->hwrm_spec_code = resp->hwrm_पूर्णांकf_maj_8b << 16 |
			     resp->hwrm_पूर्णांकf_min_8b << 8 |
			     resp->hwrm_पूर्णांकf_upd_8b;
	अगर (resp->hwrm_पूर्णांकf_maj_8b < 1) अणु
		netdev_warn(bp->dev, "HWRM interface %d.%d.%d is older than 1.0.0.\n",
			    resp->hwrm_पूर्णांकf_maj_8b, resp->hwrm_पूर्णांकf_min_8b,
			    resp->hwrm_पूर्णांकf_upd_8b);
		netdev_warn(bp->dev, "Please update firmware with HWRM interface 1.0.0 or newer.\n");
	पूर्ण

	hwrm_ver = HWRM_VERSION_MAJOR << 16 | HWRM_VERSION_MINOR << 8 |
			HWRM_VERSION_UPDATE;

	अगर (bp->hwrm_spec_code > hwrm_ver)
		snम_लिखो(bp->hwrm_ver_supp, FW_VER_STR_LEN, "%d.%d.%d",
			 HWRM_VERSION_MAJOR, HWRM_VERSION_MINOR,
			 HWRM_VERSION_UPDATE);
	अन्यथा
		snम_लिखो(bp->hwrm_ver_supp, FW_VER_STR_LEN, "%d.%d.%d",
			 resp->hwrm_पूर्णांकf_maj_8b, resp->hwrm_पूर्णांकf_min_8b,
			 resp->hwrm_पूर्णांकf_upd_8b);

	fw_maj = le16_to_cpu(resp->hwrm_fw_major);
	अगर (bp->hwrm_spec_code > 0x10803 && fw_maj) अणु
		fw_min = le16_to_cpu(resp->hwrm_fw_minor);
		fw_bld = le16_to_cpu(resp->hwrm_fw_build);
		fw_rsv = le16_to_cpu(resp->hwrm_fw_patch);
		len = FW_VER_STR_LEN;
	पूर्ण अन्यथा अणु
		fw_maj = resp->hwrm_fw_maj_8b;
		fw_min = resp->hwrm_fw_min_8b;
		fw_bld = resp->hwrm_fw_bld_8b;
		fw_rsv = resp->hwrm_fw_rsvd_8b;
		len = BC_HWRM_STR_LEN;
	पूर्ण
	bp->fw_ver_code = BNXT_FW_VER_CODE(fw_maj, fw_min, fw_bld, fw_rsv);
	snम_लिखो(bp->fw_ver_str, len, "%d.%d.%d.%d", fw_maj, fw_min, fw_bld,
		 fw_rsv);

	अगर (म_माप(resp->active_pkg_name)) अणु
		पूर्णांक fw_ver_len = म_माप(bp->fw_ver_str);

		snम_लिखो(bp->fw_ver_str + fw_ver_len,
			 FW_VER_STR_LEN - fw_ver_len - 1, "/pkg %s",
			 resp->active_pkg_name);
		bp->fw_cap |= BNXT_FW_CAP_PKG_VER;
	पूर्ण

	bp->hwrm_cmd_समयout = le16_to_cpu(resp->def_req_समयout);
	अगर (!bp->hwrm_cmd_समयout)
		bp->hwrm_cmd_समयout = DFLT_HWRM_CMD_TIMEOUT;

	अगर (resp->hwrm_पूर्णांकf_maj_8b >= 1) अणु
		bp->hwrm_max_req_len = le16_to_cpu(resp->max_req_win_len);
		bp->hwrm_max_ext_req_len = le16_to_cpu(resp->max_ext_req_len);
	पूर्ण
	अगर (bp->hwrm_max_ext_req_len < HWRM_MAX_REQ_LEN)
		bp->hwrm_max_ext_req_len = HWRM_MAX_REQ_LEN;

	bp->chip_num = le16_to_cpu(resp->chip_num);
	bp->chip_rev = resp->chip_rev;
	अगर (bp->chip_num == CHIP_NUM_58700 && !resp->chip_rev &&
	    !resp->chip_metal)
		bp->flags |= BNXT_FLAG_CHIP_NITRO_A0;

	dev_caps_cfg = le32_to_cpu(resp->dev_caps_cfg);
	अगर ((dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_SUPPORTED) &&
	    (dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_SHORT_CMD_REQUIRED))
		bp->fw_cap |= BNXT_FW_CAP_SHORT_CMD;

	अगर (dev_caps_cfg & VER_GET_RESP_DEV_CAPS_CFG_KONG_MB_CHNL_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_KONG_MB_CHNL;

	अगर (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_FLOW_HANDLE_64BIT_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_OVS_64BIT_HANDLE;

	अगर (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_TRUSTED_VF_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_TRUSTED_VF;

	अगर (dev_caps_cfg &
	    VER_GET_RESP_DEV_CAPS_CFG_CFA_ADV_FLOW_MGNT_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_CFA_ADV_FLOW;

hwrm_ver_get_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

पूर्णांक bnxt_hwrm_fw_set_समय(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_fw_set_समय_input req = अणु0पूर्ण;
	काष्ठा पंचांग पंचांग;
	समय64_t now = kसमय_get_real_seconds();

	अगर ((BNXT_VF(bp) && bp->hwrm_spec_code < 0x10901) ||
	    bp->hwrm_spec_code < 0x10400)
		वापस -EOPNOTSUPP;

	समय64_to_पंचांग(now, 0, &पंचांग);
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_SET_TIME, -1, -1);
	req.year = cpu_to_le16(1900 + पंचांग.पंचांग_year);
	req.month = 1 + पंचांग.पंचांग_mon;
	req.day = पंचांग.पंचांग_mday;
	req.hour = पंचांग.पंचांग_hour;
	req.minute = पंचांग.पंचांग_min;
	req.second = पंचांग.पंचांग_sec;
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल व्योम bnxt_add_one_ctr(u64 hw, u64 *sw, u64 mask)
अणु
	u64 sw_पंचांगp;

	hw &= mask;
	sw_पंचांगp = (*sw & ~mask) | hw;
	अगर (hw < (*sw & mask))
		sw_पंचांगp += mask + 1;
	WRITE_ONCE(*sw, sw_पंचांगp);
पूर्ण

अटल व्योम __bnxt_accumulate_stats(__le64 *hw_stats, u64 *sw_stats, u64 *masks,
				    पूर्णांक count, bool ignore_zero)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		u64 hw = le64_to_cpu(READ_ONCE(hw_stats[i]));

		अगर (ignore_zero && !hw)
			जारी;

		अगर (masks[i] == -1ULL)
			sw_stats[i] = hw;
		अन्यथा
			bnxt_add_one_ctr(hw, &sw_stats[i], masks[i]);
	पूर्ण
पूर्ण

अटल व्योम bnxt_accumulate_stats(काष्ठा bnxt_stats_mem *stats)
अणु
	अगर (!stats->hw_stats)
		वापस;

	__bnxt_accumulate_stats(stats->hw_stats, stats->sw_stats,
				stats->hw_masks, stats->len / 8, false);
पूर्ण

अटल व्योम bnxt_accumulate_all_stats(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_stats_mem *ring0_stats;
	bool ignore_zero = false;
	पूर्णांक i;

	/* Chip bug.  Counter पूर्णांकermittently becomes 0. */
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		ignore_zero = true;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		काष्ठा bnxt_stats_mem *stats;

		cpr = &bnapi->cp_ring;
		stats = &cpr->stats;
		अगर (!i)
			ring0_stats = stats;
		__bnxt_accumulate_stats(stats->hw_stats, stats->sw_stats,
					ring0_stats->hw_masks,
					ring0_stats->len / 8, ignore_zero);
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_PORT_STATS) अणु
		काष्ठा bnxt_stats_mem *stats = &bp->port_stats;
		__le64 *hw_stats = stats->hw_stats;
		u64 *sw_stats = stats->sw_stats;
		u64 *masks = stats->hw_masks;
		पूर्णांक cnt;

		cnt = माप(काष्ठा rx_port_stats) / 8;
		__bnxt_accumulate_stats(hw_stats, sw_stats, masks, cnt, false);

		hw_stats += BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;
		sw_stats += BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;
		masks += BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;
		cnt = माप(काष्ठा tx_port_stats) / 8;
		__bnxt_accumulate_stats(hw_stats, sw_stats, masks, cnt, false);
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_PORT_STATS_EXT) अणु
		bnxt_accumulate_stats(&bp->rx_port_stats_ext);
		bnxt_accumulate_stats(&bp->tx_port_stats_ext);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_qstats(काष्ठा bnxt *bp, u8 flags)
अणु
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	काष्ठा hwrm_port_qstats_input req = अणु0पूर्ण;

	अगर (!(bp->flags & BNXT_FLAG_PORT_STATS))
		वापस 0;

	अगर (flags && !(bp->fw_cap & BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED))
		वापस -EOPNOTSUPP;

	req.flags = flags;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_QSTATS, -1, -1);
	req.port_id = cpu_to_le16(pf->port_id);
	req.tx_stat_host_addr = cpu_to_le64(bp->port_stats.hw_stats_map +
					    BNXT_TX_PORT_STATS_BYTE_OFFSET);
	req.rx_stat_host_addr = cpu_to_le64(bp->port_stats.hw_stats_map);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_qstats_ext(काष्ठा bnxt *bp, u8 flags)
अणु
	काष्ठा hwrm_port_qstats_ext_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_queue_pri2cos_qcfg_input req2 = अणु0पूर्ण;
	काष्ठा hwrm_port_qstats_ext_input req = अणु0पूर्ण;
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	u32 tx_stat_size;
	पूर्णांक rc;

	अगर (!(bp->flags & BNXT_FLAG_PORT_STATS_EXT))
		वापस 0;

	अगर (flags && !(bp->fw_cap & BNXT_FW_CAP_EXT_HW_STATS_SUPPORTED))
		वापस -EOPNOTSUPP;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_QSTATS_EXT, -1, -1);
	req.flags = flags;
	req.port_id = cpu_to_le16(pf->port_id);
	req.rx_stat_size = cpu_to_le16(माप(काष्ठा rx_port_stats_ext));
	req.rx_stat_host_addr = cpu_to_le64(bp->rx_port_stats_ext.hw_stats_map);
	tx_stat_size = bp->tx_port_stats_ext.hw_stats ?
		       माप(काष्ठा tx_port_stats_ext) : 0;
	req.tx_stat_size = cpu_to_le16(tx_stat_size);
	req.tx_stat_host_addr = cpu_to_le64(bp->tx_port_stats_ext.hw_stats_map);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		bp->fw_rx_stats_ext_size = le16_to_cpu(resp->rx_stat_size) / 8;
		bp->fw_tx_stats_ext_size = tx_stat_size ?
			le16_to_cpu(resp->tx_stat_size) / 8 : 0;
	पूर्ण अन्यथा अणु
		bp->fw_rx_stats_ext_size = 0;
		bp->fw_tx_stats_ext_size = 0;
	पूर्ण
	अगर (flags)
		जाओ qstats_करोne;

	अगर (bp->fw_tx_stats_ext_size <=
	    दुरत्व(काष्ठा tx_port_stats_ext, pfc_pri0_tx_duration_us) / 8) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		bp->pri2cos_valid = 0;
		वापस rc;
	पूर्ण

	bnxt_hwrm_cmd_hdr_init(bp, &req2, HWRM_QUEUE_PRI2COS_QCFG, -1, -1);
	req2.flags = cpu_to_le32(QUEUE_PRI2COS_QCFG_REQ_FLAGS_IVLAN);

	rc = _hwrm_send_message(bp, &req2, माप(req2), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		काष्ठा hwrm_queue_pri2cos_qcfg_output *resp2;
		u8 *pri2cos;
		पूर्णांक i, j;

		resp2 = bp->hwrm_cmd_resp_addr;
		pri2cos = &resp2->pri0_cos_queue_id;
		क्रम (i = 0; i < 8; i++) अणु
			u8 queue_id = pri2cos[i];
			u8 queue_idx;

			/* Per port queue IDs start from 0, 10, 20, etc */
			queue_idx = queue_id % 10;
			अगर (queue_idx > BNXT_MAX_QUEUE) अणु
				bp->pri2cos_valid = false;
				जाओ qstats_करोne;
			पूर्ण
			क्रम (j = 0; j < bp->max_q; j++) अणु
				अगर (bp->q_ids[j] == queue_id)
					bp->pri2cos_idx[i] = queue_idx;
			पूर्ण
		पूर्ण
		bp->pri2cos_valid = 1;
	पूर्ण
qstats_करोne:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_hwrm_मुक्त_tunnel_ports(काष्ठा bnxt *bp)
अणु
	अगर (bp->vxlan_fw_dst_port_id != INVALID_HW_RING_ID)
		bnxt_hwrm_tunnel_dst_port_मुक्त(
			bp, TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN);
	अगर (bp->nge_fw_dst_port_id != INVALID_HW_RING_ID)
		bnxt_hwrm_tunnel_dst_port_मुक्त(
			bp, TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE);
पूर्ण

अटल पूर्णांक bnxt_set_tpa(काष्ठा bnxt *bp, bool set_tpa)
अणु
	पूर्णांक rc, i;
	u32 tpa_flags = 0;

	अगर (set_tpa)
		tpa_flags = bp->flags & BNXT_FLAG_TPA;
	अन्यथा अगर (BNXT_NO_FW_ACCESS(bp))
		वापस 0;
	क्रम (i = 0; i < bp->nr_vnics; i++) अणु
		rc = bnxt_hwrm_vnic_set_tpa(bp, i, tpa_flags);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic set tpa failure rc for vnic %d: %x\n",
				   i, rc);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_hwrm_clear_vnic_rss(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->nr_vnics; i++)
		bnxt_hwrm_vnic_set_rss(bp, i, false);
पूर्ण

अटल व्योम bnxt_clear_vnic(काष्ठा bnxt *bp)
अणु
	अगर (!bp->vnic_info)
		वापस;

	bnxt_hwrm_clear_vnic_filter(bp);
	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5)) अणु
		/* clear all RSS setting beक्रमe मुक्त vnic ctx */
		bnxt_hwrm_clear_vnic_rss(bp);
		bnxt_hwrm_vnic_ctx_मुक्त(bp);
	पूर्ण
	/* beक्रमe मुक्त the vnic, unकरो the vnic tpa settings */
	अगर (bp->flags & BNXT_FLAG_TPA)
		bnxt_set_tpa(bp, false);
	bnxt_hwrm_vnic_मुक्त(bp);
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		bnxt_hwrm_vnic_ctx_मुक्त(bp);
पूर्ण

अटल व्योम bnxt_hwrm_resource_मुक्त(काष्ठा bnxt *bp, bool बंद_path,
				    bool irq_re_init)
अणु
	bnxt_clear_vnic(bp);
	bnxt_hwrm_ring_मुक्त(bp, बंद_path);
	bnxt_hwrm_ring_grp_मुक्त(bp);
	अगर (irq_re_init) अणु
		bnxt_hwrm_stat_ctx_मुक्त(bp);
		bnxt_hwrm_मुक्त_tunnel_ports(bp);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_hwrm_set_br_mode(काष्ठा bnxt *bp, u16 br_mode)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_EVB_MODE);
	अगर (br_mode == BRIDGE_MODE_VEB)
		req.evb_mode = FUNC_CFG_REQ_EVB_MODE_VEB;
	अन्यथा अगर (br_mode == BRIDGE_MODE_VEPA)
		req.evb_mode = FUNC_CFG_REQ_EVB_MODE_VEPA;
	अन्यथा
		वापस -EINVAL;
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_set_cache_line_size(काष्ठा bnxt *bp, पूर्णांक size)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;

	अगर (BNXT_VF(bp) || bp->hwrm_spec_code < 0x10803)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_CACHE_LINESIZE);
	req.options = FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_64;
	अगर (size == 128)
		req.options = FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_128;

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक __bnxt_setup_vnic(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	पूर्णांक rc;

	अगर (vnic->flags & BNXT_VNIC_RFS_NEW_RSS_FLAG)
		जाओ skip_rss_ctx;

	/* allocate context क्रम vnic */
	rc = bnxt_hwrm_vnic_ctx_alloc(bp, vnic_id, 0);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic %d alloc failure rc: %x\n",
			   vnic_id, rc);
		जाओ vnic_setup_err;
	पूर्ण
	bp->rsscos_nr_ctxs++;

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp)) अणु
		rc = bnxt_hwrm_vnic_ctx_alloc(bp, vnic_id, 1);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic %d cos ctx alloc failure rc: %x\n",
				   vnic_id, rc);
			जाओ vnic_setup_err;
		पूर्ण
		bp->rsscos_nr_ctxs++;
	पूर्ण

skip_rss_ctx:
	/* configure शेष vnic, ring grp */
	rc = bnxt_hwrm_vnic_cfg(bp, vnic_id);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic %d cfg failure rc: %x\n",
			   vnic_id, rc);
		जाओ vnic_setup_err;
	पूर्ण

	/* Enable RSS hashing on vnic */
	rc = bnxt_hwrm_vnic_set_rss(bp, vnic_id, true);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic %d set rss failure rc: %x\n",
			   vnic_id, rc);
		जाओ vnic_setup_err;
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_AGG_RINGS) अणु
		rc = bnxt_hwrm_vnic_set_hds(bp, vnic_id);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic %d set hds failure rc: %x\n",
				   vnic_id, rc);
		पूर्ण
	पूर्ण

vnic_setup_err:
	वापस rc;
पूर्ण

अटल पूर्णांक __bnxt_setup_vnic_p5(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	पूर्णांक rc, i, nr_ctxs;

	nr_ctxs = bnxt_get_nr_rss_ctxs(bp, bp->rx_nr_rings);
	क्रम (i = 0; i < nr_ctxs; i++) अणु
		rc = bnxt_hwrm_vnic_ctx_alloc(bp, vnic_id, i);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic %d ctx %d alloc failure rc: %x\n",
				   vnic_id, i, rc);
			अवरोध;
		पूर्ण
		bp->rsscos_nr_ctxs++;
	पूर्ण
	अगर (i < nr_ctxs)
		वापस -ENOMEM;

	rc = bnxt_hwrm_vnic_set_rss_p5(bp, vnic_id, true);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic %d set rss failure rc: %d\n",
			   vnic_id, rc);
		वापस rc;
	पूर्ण
	rc = bnxt_hwrm_vnic_cfg(bp, vnic_id);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic %d cfg failure rc: %x\n",
			   vnic_id, rc);
		वापस rc;
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS) अणु
		rc = bnxt_hwrm_vnic_set_hds(bp, vnic_id);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic %d set hds failure rc: %x\n",
				   vnic_id, rc);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_setup_vnic(काष्ठा bnxt *bp, u16 vnic_id)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस __bnxt_setup_vnic_p5(bp, vnic_id);
	अन्यथा
		वापस __bnxt_setup_vnic(bp, vnic_id);
पूर्ण

अटल पूर्णांक bnxt_alloc_rfs_vnics(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	पूर्णांक i, rc = 0;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस 0;

	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_vnic_info *vnic;
		u16 vnic_id = i + 1;
		u16 ring_id = i;

		अगर (vnic_id >= bp->nr_vnics)
			अवरोध;

		vnic = &bp->vnic_info[vnic_id];
		vnic->flags |= BNXT_VNIC_RFS_FLAG;
		अगर (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
			vnic->flags |= BNXT_VNIC_RFS_NEW_RSS_FLAG;
		rc = bnxt_hwrm_vnic_alloc(bp, vnic_id, ring_id, 1);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm vnic %d alloc failure rc: %x\n",
				   vnic_id, rc);
			अवरोध;
		पूर्ण
		rc = bnxt_setup_vnic(bp, vnic_id);
		अगर (rc)
			अवरोध;
	पूर्ण
	वापस rc;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* Allow PF, trusted VFs and VFs with शेष VLAN to be in promiscuous mode */
अटल bool bnxt_promisc_ok(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (BNXT_VF(bp) && !bp->vf.vlan && !bnxt_is_trusted_vf(bp, &bp->vf))
		वापस false;
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल पूर्णांक bnxt_setup_nitroa0_vnic(काष्ठा bnxt *bp)
अणु
	अचिन्हित पूर्णांक rc = 0;

	rc = bnxt_hwrm_vnic_alloc(bp, 1, bp->rx_nr_rings - 1, 1);
	अगर (rc) अणु
		netdev_err(bp->dev, "Cannot allocate special vnic for NS2 A0: %x\n",
			   rc);
		वापस rc;
	पूर्ण

	rc = bnxt_hwrm_vnic_cfg(bp, 1);
	अगर (rc) अणु
		netdev_err(bp->dev, "Cannot allocate special vnic for NS2 A0: %x\n",
			   rc);
		वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_cfg_rx_mode(काष्ठा bnxt *);
अटल bool bnxt_mc_list_updated(काष्ठा bnxt *, u32 *);

अटल पूर्णांक bnxt_init_chip(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[0];
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक rx_nr_rings = bp->rx_nr_rings;

	अगर (irq_re_init) अणु
		rc = bnxt_hwrm_stat_ctx_alloc(bp);
		अगर (rc) अणु
			netdev_err(bp->dev, "hwrm stat ctx alloc failure rc: %x\n",
				   rc);
			जाओ err_out;
		पूर्ण
	पूर्ण

	rc = bnxt_hwrm_ring_alloc(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm ring alloc failure rc: %x\n", rc);
		जाओ err_out;
	पूर्ण

	rc = bnxt_hwrm_ring_grp_alloc(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm_ring_grp alloc failure: %x\n", rc);
		जाओ err_out;
	पूर्ण

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
		rx_nr_rings--;

	/* शेष vnic 0 */
	rc = bnxt_hwrm_vnic_alloc(bp, 0, 0, rx_nr_rings);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm vnic alloc failure rc: %x\n", rc);
		जाओ err_out;
	पूर्ण

	rc = bnxt_setup_vnic(bp, 0);
	अगर (rc)
		जाओ err_out;

	अगर (bp->flags & BNXT_FLAG_RFS) अणु
		rc = bnxt_alloc_rfs_vnics(bp);
		अगर (rc)
			जाओ err_out;
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_TPA) अणु
		rc = bnxt_set_tpa(bp, true);
		अगर (rc)
			जाओ err_out;
	पूर्ण

	अगर (BNXT_VF(bp))
		bnxt_update_vf_mac(bp);

	/* Filter क्रम शेष vnic 0 */
	rc = bnxt_hwrm_set_vnic_filter(bp, 0, 0, bp->dev->dev_addr);
	अगर (rc) अणु
		netdev_err(bp->dev, "HWRM vnic filter failure rc: %x\n", rc);
		जाओ err_out;
	पूर्ण
	vnic->uc_filter_count = 1;

	vnic->rx_mask = 0;
	अगर (bp->dev->flags & IFF_BROADCAST)
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_BCAST;

	अगर (bp->dev->flags & IFF_PROMISC)
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;

	अगर (bp->dev->flags & IFF_ALLMULTI) अणु
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
		vnic->mc_list_count = 0;
	पूर्ण अन्यथा अणु
		u32 mask = 0;

		bnxt_mc_list_updated(bp, &mask);
		vnic->rx_mask |= mask;
	पूर्ण

	rc = bnxt_cfg_rx_mode(bp);
	अगर (rc)
		जाओ err_out;

	rc = bnxt_hwrm_set_coal(bp);
	अगर (rc)
		netdev_warn(bp->dev, "HWRM set coalescing failure rc: %x\n",
				rc);

	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp)) अणु
		rc = bnxt_setup_nitroa0_vnic(bp);
		अगर (rc)
			netdev_err(bp->dev, "Special vnic setup failure for NS2 A0 rc: %x\n",
				   rc);
	पूर्ण

	अगर (BNXT_VF(bp)) अणु
		bnxt_hwrm_func_qcfg(bp);
		netdev_update_features(bp->dev);
	पूर्ण

	वापस 0;

err_out:
	bnxt_hwrm_resource_मुक्त(bp, 0, true);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_shutकरोwn_nic(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	bnxt_hwrm_resource_मुक्त(bp, 1, irq_re_init);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_init_nic(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	bnxt_init_cp_rings(bp);
	bnxt_init_rx_rings(bp);
	bnxt_init_tx_rings(bp);
	bnxt_init_ring_grps(bp, irq_re_init);
	bnxt_init_vnics(bp);

	वापस bnxt_init_chip(bp, irq_re_init);
पूर्ण

अटल पूर्णांक bnxt_set_real_num_queues(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;
	काष्ठा net_device *dev = bp->dev;

	rc = netअगर_set_real_num_tx_queues(dev, bp->tx_nr_rings -
					  bp->tx_nr_rings_xdp);
	अगर (rc)
		वापस rc;

	rc = netअगर_set_real_num_rx_queues(dev, bp->rx_nr_rings);
	अगर (rc)
		वापस rc;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (bp->flags & BNXT_FLAG_RFS)
		dev->rx_cpu_rmap = alloc_irq_cpu_rmap(bp->rx_nr_rings);
#पूर्ण_अगर

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_trim_rings(काष्ठा bnxt *bp, पूर्णांक *rx, पूर्णांक *tx, पूर्णांक max,
			   bool shared)
अणु
	पूर्णांक _rx = *rx, _tx = *tx;

	अगर (shared) अणु
		*rx = min_t(पूर्णांक, _rx, max);
		*tx = min_t(पूर्णांक, _tx, max);
	पूर्ण अन्यथा अणु
		अगर (max < 2)
			वापस -ENOMEM;

		जबतक (_rx + _tx > max) अणु
			अगर (_rx > _tx && _rx > 1)
				_rx--;
			अन्यथा अगर (_tx > 1)
				_tx--;
		पूर्ण
		*rx = _rx;
		*tx = _tx;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_setup_msix(काष्ठा bnxt *bp)
अणु
	स्थिर पूर्णांक len = माप(bp->irq_tbl[0].name);
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक tcs, i;

	tcs = netdev_get_num_tc(dev);
	अगर (tcs) अणु
		पूर्णांक i, off, count;

		क्रम (i = 0; i < tcs; i++) अणु
			count = bp->tx_nr_rings_per_tc;
			off = i * count;
			netdev_set_tc_queue(dev, i, count, off);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		पूर्णांक map_idx = bnxt_cp_num_to_irq_num(bp, i);
		अक्षर *attr;

		अगर (bp->flags & BNXT_FLAG_SHARED_RINGS)
			attr = "TxRx";
		अन्यथा अगर (i < bp->rx_nr_rings)
			attr = "rx";
		अन्यथा
			attr = "tx";

		snम_लिखो(bp->irq_tbl[map_idx].name, len, "%s-%s-%d", dev->name,
			 attr, i);
		bp->irq_tbl[map_idx].handler = bnxt_msix;
	पूर्ण
पूर्ण

अटल व्योम bnxt_setup_पूर्णांकa(काष्ठा bnxt *bp)
अणु
	स्थिर पूर्णांक len = माप(bp->irq_tbl[0].name);

	अगर (netdev_get_num_tc(bp->dev))
		netdev_reset_tc(bp->dev);

	snम_लिखो(bp->irq_tbl[0].name, len, "%s-%s-%d", bp->dev->name, "TxRx",
		 0);
	bp->irq_tbl[0].handler = bnxt_पूर्णांकa;
पूर्ण

अटल पूर्णांक bnxt_init_पूर्णांक_mode(काष्ठा bnxt *bp);

अटल पूर्णांक bnxt_setup_पूर्णांक_mode(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	अगर (!bp->irq_tbl) अणु
		rc = bnxt_init_पूर्णांक_mode(bp);
		अगर (rc || !bp->irq_tbl)
			वापस rc ?: -ENODEV;
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_USING_MSIX)
		bnxt_setup_msix(bp);
	अन्यथा
		bnxt_setup_पूर्णांकa(bp);

	rc = bnxt_set_real_num_queues(bp);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल अचिन्हित पूर्णांक bnxt_get_max_func_rss_ctxs(काष्ठा bnxt *bp)
अणु
	वापस bp->hw_resc.max_rsscos_ctxs;
पूर्ण

अटल अचिन्हित पूर्णांक bnxt_get_max_func_vnics(काष्ठा bnxt *bp)
अणु
	वापस bp->hw_resc.max_vnics;
पूर्ण
#पूर्ण_अगर

अचिन्हित पूर्णांक bnxt_get_max_func_stat_ctxs(काष्ठा bnxt *bp)
अणु
	वापस bp->hw_resc.max_stat_ctxs;
पूर्ण

अचिन्हित पूर्णांक bnxt_get_max_func_cp_rings(काष्ठा bnxt *bp)
अणु
	वापस bp->hw_resc.max_cp_rings;
पूर्ण

अटल अचिन्हित पूर्णांक bnxt_get_max_func_cp_rings_क्रम_en(काष्ठा bnxt *bp)
अणु
	अचिन्हित पूर्णांक cp = bp->hw_resc.max_cp_rings;

	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		cp -= bnxt_get_ulp_msix_num(bp);

	वापस cp;
पूर्ण

अटल अचिन्हित पूर्णांक bnxt_get_max_func_irqs(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस min_t(अचिन्हित पूर्णांक, hw_resc->max_irqs, hw_resc->max_nqs);

	वापस min_t(अचिन्हित पूर्णांक, hw_resc->max_irqs, hw_resc->max_cp_rings);
पूर्ण

अटल व्योम bnxt_set_max_func_irqs(काष्ठा bnxt *bp, अचिन्हित पूर्णांक max_irqs)
अणु
	bp->hw_resc.max_irqs = max_irqs;
पूर्ण

अचिन्हित पूर्णांक bnxt_get_avail_cp_rings_क्रम_en(काष्ठा bnxt *bp)
अणु
	अचिन्हित पूर्णांक cp;

	cp = bnxt_get_max_func_cp_rings_क्रम_en(bp);
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस cp - bp->rx_nr_rings - bp->tx_nr_rings;
	अन्यथा
		वापस cp - bp->cp_nr_rings;
पूर्ण

अचिन्हित पूर्णांक bnxt_get_avail_stat_ctxs_क्रम_en(काष्ठा bnxt *bp)
अणु
	वापस bnxt_get_max_func_stat_ctxs(bp) - bnxt_get_func_stat_ctxs(bp);
पूर्ण

पूर्णांक bnxt_get_avail_msix(काष्ठा bnxt *bp, पूर्णांक num)
अणु
	पूर्णांक max_cp = bnxt_get_max_func_cp_rings(bp);
	पूर्णांक max_irq = bnxt_get_max_func_irqs(bp);
	पूर्णांक total_req = bp->cp_nr_rings + num;
	पूर्णांक max_idx, avail_msix;

	max_idx = bp->total_irqs;
	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		max_idx = min_t(पूर्णांक, bp->total_irqs, max_cp);
	avail_msix = max_idx - bp->cp_nr_rings;
	अगर (!BNXT_NEW_RM(bp) || avail_msix >= num)
		वापस avail_msix;

	अगर (max_irq < total_req) अणु
		num = max_irq - bp->cp_nr_rings;
		अगर (num <= 0)
			वापस 0;
	पूर्ण
	वापस num;
पूर्ण

अटल पूर्णांक bnxt_get_num_msix(काष्ठा bnxt *bp)
अणु
	अगर (!BNXT_NEW_RM(bp))
		वापस bnxt_get_max_func_irqs(bp);

	वापस bnxt_nq_rings_in_use(bp);
पूर्ण

अटल पूर्णांक bnxt_init_msix(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, total_vecs, max, rc = 0, min = 1, ulp_msix;
	काष्ठा msix_entry *msix_ent;

	total_vecs = bnxt_get_num_msix(bp);
	max = bnxt_get_max_func_irqs(bp);
	अगर (total_vecs > max)
		total_vecs = max;

	अगर (!total_vecs)
		वापस 0;

	msix_ent = kसुस्मृति(total_vecs, माप(काष्ठा msix_entry), GFP_KERNEL);
	अगर (!msix_ent)
		वापस -ENOMEM;

	क्रम (i = 0; i < total_vecs; i++) अणु
		msix_ent[i].entry = i;
		msix_ent[i].vector = 0;
	पूर्ण

	अगर (!(bp->flags & BNXT_FLAG_SHARED_RINGS))
		min = 2;

	total_vecs = pci_enable_msix_range(bp->pdev, msix_ent, min, total_vecs);
	ulp_msix = bnxt_get_ulp_msix_num(bp);
	अगर (total_vecs < 0 || total_vecs < ulp_msix) अणु
		rc = -ENODEV;
		जाओ msix_setup_निकास;
	पूर्ण

	bp->irq_tbl = kसुस्मृति(total_vecs, माप(काष्ठा bnxt_irq), GFP_KERNEL);
	अगर (bp->irq_tbl) अणु
		क्रम (i = 0; i < total_vecs; i++)
			bp->irq_tbl[i].vector = msix_ent[i].vector;

		bp->total_irqs = total_vecs;
		/* Trim rings based upon num of vectors allocated */
		rc = bnxt_trim_rings(bp, &bp->rx_nr_rings, &bp->tx_nr_rings,
				     total_vecs - ulp_msix, min == 1);
		अगर (rc)
			जाओ msix_setup_निकास;

		bp->cp_nr_rings = (min == 1) ?
				  max_t(पूर्णांक, bp->tx_nr_rings, bp->rx_nr_rings) :
				  bp->tx_nr_rings + bp->rx_nr_rings;

	पूर्ण अन्यथा अणु
		rc = -ENOMEM;
		जाओ msix_setup_निकास;
	पूर्ण
	bp->flags |= BNXT_FLAG_USING_MSIX;
	kमुक्त(msix_ent);
	वापस 0;

msix_setup_निकास:
	netdev_err(bp->dev, "bnxt_init_msix err: %x\n", rc);
	kमुक्त(bp->irq_tbl);
	bp->irq_tbl = शून्य;
	pci_disable_msix(bp->pdev);
	kमुक्त(msix_ent);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_init_पूर्णांकa(काष्ठा bnxt *bp)
अणु
	bp->irq_tbl = kzalloc(माप(काष्ठा bnxt_irq), GFP_KERNEL);
	अगर (!bp->irq_tbl)
		वापस -ENOMEM;

	bp->total_irqs = 1;
	bp->rx_nr_rings = 1;
	bp->tx_nr_rings = 1;
	bp->cp_nr_rings = 1;
	bp->flags |= BNXT_FLAG_SHARED_RINGS;
	bp->irq_tbl[0].vector = bp->pdev->irq;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_init_पूर्णांक_mode(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = -ENODEV;

	अगर (bp->flags & BNXT_FLAG_MSIX_CAP)
		rc = bnxt_init_msix(bp);

	अगर (!(bp->flags & BNXT_FLAG_USING_MSIX) && BNXT_PF(bp)) अणु
		/* fallback to INTA */
		rc = bnxt_init_पूर्णांकa(bp);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_clear_पूर्णांक_mode(काष्ठा bnxt *bp)
अणु
	अगर (bp->flags & BNXT_FLAG_USING_MSIX)
		pci_disable_msix(bp->pdev);

	kमुक्त(bp->irq_tbl);
	bp->irq_tbl = शून्य;
	bp->flags &= ~BNXT_FLAG_USING_MSIX;
पूर्ण

पूर्णांक bnxt_reserve_rings(काष्ठा bnxt *bp, bool irq_re_init)
अणु
	पूर्णांक tcs = netdev_get_num_tc(bp->dev);
	bool irq_cleared = false;
	पूर्णांक rc;

	अगर (!bnxt_need_reserve_rings(bp))
		वापस 0;

	अगर (irq_re_init && BNXT_NEW_RM(bp) &&
	    bnxt_get_num_msix(bp) != bp->total_irqs) अणु
		bnxt_ulp_irq_stop(bp);
		bnxt_clear_पूर्णांक_mode(bp);
		irq_cleared = true;
	पूर्ण
	rc = __bnxt_reserve_rings(bp);
	अगर (irq_cleared) अणु
		अगर (!rc)
			rc = bnxt_init_पूर्णांक_mode(bp);
		bnxt_ulp_irq_restart(bp, rc);
	पूर्ण
	अगर (rc) अणु
		netdev_err(bp->dev, "ring reservation/IRQ init failure rc: %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (tcs && (bp->tx_nr_rings_per_tc * tcs != bp->tx_nr_rings)) अणु
		netdev_err(bp->dev, "tx ring reservation failure\n");
		netdev_reset_tc(bp->dev);
		bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_मुक्त_irq(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_irq *irq;
	पूर्णांक i;

#अगर_घोषित CONFIG_RFS_ACCEL
	मुक्त_irq_cpu_rmap(bp->dev->rx_cpu_rmap);
	bp->dev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर
	अगर (!bp->irq_tbl || !bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		पूर्णांक map_idx = bnxt_cp_num_to_irq_num(bp, i);

		irq = &bp->irq_tbl[map_idx];
		अगर (irq->requested) अणु
			अगर (irq->have_cpumask) अणु
				irq_set_affinity_hपूर्णांक(irq->vector, शून्य);
				मुक्त_cpumask_var(irq->cpu_mask);
				irq->have_cpumask = 0;
			पूर्ण
			मुक्त_irq(irq->vector, bp->bnapi[i]);
		पूर्ण

		irq->requested = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_request_irq(काष्ठा bnxt *bp)
अणु
	पूर्णांक i, j, rc = 0;
	अचिन्हित दीर्घ flags = 0;
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा cpu_rmap *rmap;
#पूर्ण_अगर

	rc = bnxt_setup_पूर्णांक_mode(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "bnxt_setup_int_mode err: %x\n",
			   rc);
		वापस rc;
	पूर्ण
#अगर_घोषित CONFIG_RFS_ACCEL
	rmap = bp->dev->rx_cpu_rmap;
#पूर्ण_अगर
	अगर (!(bp->flags & BNXT_FLAG_USING_MSIX))
		flags = IRQF_SHARED;

	क्रम (i = 0, j = 0; i < bp->cp_nr_rings; i++) अणु
		पूर्णांक map_idx = bnxt_cp_num_to_irq_num(bp, i);
		काष्ठा bnxt_irq *irq = &bp->irq_tbl[map_idx];

#अगर_घोषित CONFIG_RFS_ACCEL
		अगर (rmap && bp->bnapi[i]->rx_ring) अणु
			rc = irq_cpu_rmap_add(rmap, irq->vector);
			अगर (rc)
				netdev_warn(bp->dev, "failed adding irq rmap for ring %d\n",
					    j);
			j++;
		पूर्ण
#पूर्ण_अगर
		rc = request_irq(irq->vector, irq->handler, flags, irq->name,
				 bp->bnapi[i]);
		अगर (rc)
			अवरोध;

		irq->requested = 1;

		अगर (zalloc_cpumask_var(&irq->cpu_mask, GFP_KERNEL)) अणु
			पूर्णांक numa_node = dev_to_node(&bp->pdev->dev);

			irq->have_cpumask = 1;
			cpumask_set_cpu(cpumask_local_spपढ़ो(i, numa_node),
					irq->cpu_mask);
			rc = irq_set_affinity_hपूर्णांक(irq->vector, irq->cpu_mask);
			अगर (rc) अणु
				netdev_warn(bp->dev,
					    "Set affinity failed, IRQ = %d\n",
					    irq->vector);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnxt_del_napi(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi)
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];

		__netअगर_napi_del(&bnapi->napi);
	पूर्ण
	/* We called __netअगर_napi_del(), we need
	 * to respect an RCU grace period beक्रमe मुक्तing napi काष्ठाures.
	 */
	synchronize_net();
पूर्ण

अटल व्योम bnxt_init_napi(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक cp_nr_rings = bp->cp_nr_rings;
	काष्ठा bnxt_napi *bnapi;

	अगर (bp->flags & BNXT_FLAG_USING_MSIX) अणु
		पूर्णांक (*poll_fn)(काष्ठा napi_काष्ठा *, पूर्णांक) = bnxt_poll;

		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			poll_fn = bnxt_poll_p5;
		अन्यथा अगर (BNXT_CHIP_TYPE_NITRO_A0(bp))
			cp_nr_rings--;
		क्रम (i = 0; i < cp_nr_rings; i++) अणु
			bnapi = bp->bnapi[i];
			netअगर_napi_add(bp->dev, &bnapi->napi, poll_fn, 64);
		पूर्ण
		अगर (BNXT_CHIP_TYPE_NITRO_A0(bp)) अणु
			bnapi = bp->bnapi[cp_nr_rings];
			netअगर_napi_add(bp->dev, &bnapi->napi,
				       bnxt_poll_nitroa0, 64);
		पूर्ण
	पूर्ण अन्यथा अणु
		bnapi = bp->bnapi[0];
		netअगर_napi_add(bp->dev, &bnapi->napi, bnxt_poll, 64);
	पूर्ण
पूर्ण

अटल व्योम bnxt_disable_napi(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!bp->bnapi ||
	    test_and_set_bit(BNXT_STATE_NAPI_DISABLED, &bp->state))
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;

		अगर (bp->bnapi[i]->rx_ring)
			cancel_work_sync(&cpr->dim.work);

		napi_disable(&bp->bnapi[i]->napi);
	पूर्ण
पूर्ण

अटल व्योम bnxt_enable_napi(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	clear_bit(BNXT_STATE_NAPI_DISABLED, &bp->state);
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;

		cpr = &bnapi->cp_ring;
		अगर (bnapi->in_reset)
			cpr->sw_stats.rx.rx_resets++;
		bnapi->in_reset = false;

		अगर (bnapi->rx_ring) अणु
			INIT_WORK(&cpr->dim.work, bnxt_dim_work);
			cpr->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
		पूर्ण
		napi_enable(&bnapi->napi);
	पूर्ण
पूर्ण

व्योम bnxt_tx_disable(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	काष्ठा bnxt_tx_ring_info *txr;

	अगर (bp->tx_ring) अणु
		क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
			txr = &bp->tx_ring[i];
			txr->dev_state = BNXT_DEV_STATE_CLOSING;
		पूर्ण
	पूर्ण
	/* Drop carrier first to prevent TX समयout */
	netअगर_carrier_off(bp->dev);
	/* Stop all TX queues */
	netअगर_tx_disable(bp->dev);
पूर्ण

व्योम bnxt_tx_enable(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	काष्ठा bnxt_tx_ring_info *txr;

	क्रम (i = 0; i < bp->tx_nr_rings; i++) अणु
		txr = &bp->tx_ring[i];
		txr->dev_state = 0;
	पूर्ण
	netअगर_tx_wake_all_queues(bp->dev);
	अगर (bp->link_info.link_up)
		netअगर_carrier_on(bp->dev);
पूर्ण

अटल अक्षर *bnxt_report_fec(काष्ठा bnxt_link_info *link_info)
अणु
	u8 active_fec = link_info->active_fec_sig_mode &
			PORT_PHY_QCFG_RESP_ACTIVE_FEC_MASK;

	चयन (active_fec) अणु
	शेष:
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_NONE_ACTIVE:
		वापस "None";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE74_ACTIVE:
		वापस "Clause 74 BaseR";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_CLAUSE91_ACTIVE:
		वापस "Clause 91 RS(528,514)";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_1XN_ACTIVE:
		वापस "Clause 91 RS544_1XN";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS544_IEEE_ACTIVE:
		वापस "Clause 91 RS(544,514)";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_1XN_ACTIVE:
		वापस "Clause 91 RS272_1XN";
	हाल PORT_PHY_QCFG_RESP_ACTIVE_FEC_FEC_RS272_IEEE_ACTIVE:
		वापस "Clause 91 RS(272,257)";
	पूर्ण
पूर्ण

अटल व्योम bnxt_report_link(काष्ठा bnxt *bp)
अणु
	अगर (bp->link_info.link_up) अणु
		स्थिर अक्षर *संकेत = "";
		स्थिर अक्षर *flow_ctrl;
		स्थिर अक्षर *duplex;
		u32 speed;
		u16 fec;

		netअगर_carrier_on(bp->dev);
		speed = bnxt_fw_to_ethtool_speed(bp->link_info.link_speed);
		अगर (speed == SPEED_UNKNOWN) अणु
			netdev_info(bp->dev, "NIC Link is Up, speed unknown\n");
			वापस;
		पूर्ण
		अगर (bp->link_info.duplex == BNXT_LINK_DUPLEX_FULL)
			duplex = "full";
		अन्यथा
			duplex = "half";
		अगर (bp->link_info.छोड़ो == BNXT_LINK_PAUSE_BOTH)
			flow_ctrl = "ON - receive & transmit";
		अन्यथा अगर (bp->link_info.छोड़ो == BNXT_LINK_PAUSE_TX)
			flow_ctrl = "ON - transmit";
		अन्यथा अगर (bp->link_info.छोड़ो == BNXT_LINK_PAUSE_RX)
			flow_ctrl = "ON - receive";
		अन्यथा
			flow_ctrl = "none";
		अगर (bp->link_info.phy_qcfg_resp.option_flags &
		    PORT_PHY_QCFG_RESP_OPTION_FLAGS_SIGNAL_MODE_KNOWN) अणु
			u8 sig_mode = bp->link_info.active_fec_sig_mode &
				      PORT_PHY_QCFG_RESP_SIGNAL_MODE_MASK;
			चयन (sig_mode) अणु
			हाल PORT_PHY_QCFG_RESP_SIGNAL_MODE_NRZ:
				संकेत = "(NRZ) ";
				अवरोध;
			हाल PORT_PHY_QCFG_RESP_SIGNAL_MODE_PAM4:
				संकेत = "(PAM4) ";
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		netdev_info(bp->dev, "NIC Link is Up, %u Mbps %s%s duplex, Flow control: %s\n",
			    speed, संकेत, duplex, flow_ctrl);
		अगर (bp->phy_flags & BNXT_PHY_FL_EEE_CAP)
			netdev_info(bp->dev, "EEE is %s\n",
				    bp->eee.eee_active ? "active" :
							 "not active");
		fec = bp->link_info.fec_cfg;
		अगर (!(fec & PORT_PHY_QCFG_RESP_FEC_CFG_FEC_NONE_SUPPORTED))
			netdev_info(bp->dev, "FEC autoneg %s encoding: %s\n",
				    (fec & BNXT_FEC_AUTONEG) ? "on" : "off",
				    bnxt_report_fec(&bp->link_info));
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(bp->dev);
		netdev_err(bp->dev, "NIC Link is Down\n");
	पूर्ण
पूर्ण

अटल bool bnxt_phy_qcaps_no_speed(काष्ठा hwrm_port_phy_qcaps_output *resp)
अणु
	अगर (!resp->supported_speeds_स्वतः_mode &&
	    !resp->supported_speeds_क्रमce_mode &&
	    !resp->supported_pam4_speeds_स्वतः_mode &&
	    !resp->supported_pam4_speeds_क्रमce_mode)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक bnxt_hwrm_phy_qcaps(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_port_phy_qcaps_input req = अणु0पूर्ण;
	काष्ठा hwrm_port_phy_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (bp->hwrm_spec_code < 0x10201)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_QCAPS, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		जाओ hwrm_phy_qcaps_निकास;

	bp->phy_flags = resp->flags;
	अगर (resp->flags & PORT_PHY_QCAPS_RESP_FLAGS_EEE_SUPPORTED) अणु
		काष्ठा ethtool_eee *eee = &bp->eee;
		u16 fw_speeds = le16_to_cpu(resp->supported_speeds_eee_mode);

		eee->supported = _bnxt_fw_to_ethtool_adv_spds(fw_speeds, 0);
		bp->lpi_पंचांगr_lo = le32_to_cpu(resp->tx_lpi_समयr_low) &
				 PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_LOW_MASK;
		bp->lpi_पंचांगr_hi = le32_to_cpu(resp->valid_tx_lpi_समयr_high) &
				 PORT_PHY_QCAPS_RESP_TX_LPI_TIMER_HIGH_MASK;
	पूर्ण

	अगर (bp->hwrm_spec_code >= 0x10a01) अणु
		अगर (bnxt_phy_qcaps_no_speed(resp)) अणु
			link_info->phy_state = BNXT_PHY_STATE_DISABLED;
			netdev_warn(bp->dev, "Ethernet link disabled\n");
		पूर्ण अन्यथा अगर (link_info->phy_state == BNXT_PHY_STATE_DISABLED) अणु
			link_info->phy_state = BNXT_PHY_STATE_ENABLED;
			netdev_info(bp->dev, "Ethernet link enabled\n");
			/* Phy re-enabled, reprobe the speeds */
			link_info->support_स्वतः_speeds = 0;
			link_info->support_pam4_स्वतः_speeds = 0;
		पूर्ण
	पूर्ण
	अगर (resp->supported_speeds_स्वतः_mode)
		link_info->support_स्वतः_speeds =
			le16_to_cpu(resp->supported_speeds_स्वतः_mode);
	अगर (resp->supported_pam4_speeds_स्वतः_mode)
		link_info->support_pam4_स्वतः_speeds =
			le16_to_cpu(resp->supported_pam4_speeds_स्वतः_mode);

	bp->port_count = resp->port_cnt;

hwrm_phy_qcaps_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल bool bnxt_support_dropped(u16 advertising, u16 supported)
अणु
	u16 dअगरf = advertising ^ supported;

	वापस ((supported | dअगरf) != supported);
पूर्ण

पूर्णांक bnxt_update_link(काष्ठा bnxt *bp, bool chng_link_state)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	काष्ठा hwrm_port_phy_qcfg_input req = अणु0पूर्ण;
	काष्ठा hwrm_port_phy_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	u8 link_up = link_info->link_up;
	bool support_changed = false;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_QCFG, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण

	स_नकल(&link_info->phy_qcfg_resp, resp, माप(*resp));
	link_info->phy_link_status = resp->link;
	link_info->duplex = resp->duplex_cfg;
	अगर (bp->hwrm_spec_code >= 0x10800)
		link_info->duplex = resp->duplex_state;
	link_info->छोड़ो = resp->छोड़ो;
	link_info->स्वतः_mode = resp->स्वतः_mode;
	link_info->स्वतः_छोड़ो_setting = resp->स्वतः_छोड़ो;
	link_info->lp_छोड़ो = resp->link_partner_adv_छोड़ो;
	link_info->क्रमce_छोड़ो_setting = resp->क्रमce_छोड़ो;
	link_info->duplex_setting = resp->duplex_cfg;
	अगर (link_info->phy_link_status == BNXT_LINK_LINK)
		link_info->link_speed = le16_to_cpu(resp->link_speed);
	अन्यथा
		link_info->link_speed = 0;
	link_info->क्रमce_link_speed = le16_to_cpu(resp->क्रमce_link_speed);
	link_info->क्रमce_pam4_link_speed =
		le16_to_cpu(resp->क्रमce_pam4_link_speed);
	link_info->support_speeds = le16_to_cpu(resp->support_speeds);
	link_info->support_pam4_speeds = le16_to_cpu(resp->support_pam4_speeds);
	link_info->स्वतः_link_speeds = le16_to_cpu(resp->स्वतः_link_speed_mask);
	link_info->स्वतः_pam4_link_speeds =
		le16_to_cpu(resp->स्वतः_pam4_link_speed_mask);
	link_info->lp_स्वतः_link_speeds =
		le16_to_cpu(resp->link_partner_adv_speeds);
	link_info->lp_स्वतः_pam4_link_speeds =
		resp->link_partner_pam4_adv_speeds;
	link_info->preemphasis = le32_to_cpu(resp->preemphasis);
	link_info->phy_ver[0] = resp->phy_maj;
	link_info->phy_ver[1] = resp->phy_min;
	link_info->phy_ver[2] = resp->phy_bld;
	link_info->media_type = resp->media_type;
	link_info->phy_type = resp->phy_type;
	link_info->transceiver = resp->xcvr_pkg_type;
	link_info->phy_addr = resp->eee_config_phy_addr &
			      PORT_PHY_QCFG_RESP_PHY_ADDR_MASK;
	link_info->module_status = resp->module_status;

	अगर (bp->phy_flags & BNXT_PHY_FL_EEE_CAP) अणु
		काष्ठा ethtool_eee *eee = &bp->eee;
		u16 fw_speeds;

		eee->eee_active = 0;
		अगर (resp->eee_config_phy_addr &
		    PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_ACTIVE) अणु
			eee->eee_active = 1;
			fw_speeds = le16_to_cpu(
				resp->link_partner_adv_eee_link_speed_mask);
			eee->lp_advertised =
				_bnxt_fw_to_ethtool_adv_spds(fw_speeds, 0);
		पूर्ण

		/* Pull initial EEE config */
		अगर (!chng_link_state) अणु
			अगर (resp->eee_config_phy_addr &
			    PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_ENABLED)
				eee->eee_enabled = 1;

			fw_speeds = le16_to_cpu(resp->adv_eee_link_speed_mask);
			eee->advertised =
				_bnxt_fw_to_ethtool_adv_spds(fw_speeds, 0);

			अगर (resp->eee_config_phy_addr &
			    PORT_PHY_QCFG_RESP_EEE_CONFIG_EEE_TX_LPI) अणु
				__le32 पंचांगr;

				eee->tx_lpi_enabled = 1;
				पंचांगr = resp->xcvr_identअगरier_type_tx_lpi_समयr;
				eee->tx_lpi_समयr = le32_to_cpu(पंचांगr) &
					PORT_PHY_QCFG_RESP_TX_LPI_TIMER_MASK;
			पूर्ण
		पूर्ण
	पूर्ण

	link_info->fec_cfg = PORT_PHY_QCFG_RESP_FEC_CFG_FEC_NONE_SUPPORTED;
	अगर (bp->hwrm_spec_code >= 0x10504) अणु
		link_info->fec_cfg = le16_to_cpu(resp->fec_cfg);
		link_info->active_fec_sig_mode = resp->active_fec_संकेत_mode;
	पूर्ण
	/* TODO: need to add more logic to report VF link */
	अगर (chng_link_state) अणु
		अगर (link_info->phy_link_status == BNXT_LINK_LINK)
			link_info->link_up = 1;
		अन्यथा
			link_info->link_up = 0;
		अगर (link_up != link_info->link_up)
			bnxt_report_link(bp);
	पूर्ण अन्यथा अणु
		/* alwasy link करोwn अगर not require to update link state */
		link_info->link_up = 0;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	अगर (!BNXT_PHY_CFG_ABLE(bp))
		वापस 0;

	/* Check अगर any advertised speeds are no दीर्घer supported. The caller
	 * holds the link_lock mutex, so we can modअगरy link_info settings.
	 */
	अगर (bnxt_support_dropped(link_info->advertising,
				 link_info->support_स्वतः_speeds)) अणु
		link_info->advertising = link_info->support_स्वतः_speeds;
		support_changed = true;
	पूर्ण
	अगर (bnxt_support_dropped(link_info->advertising_pam4,
				 link_info->support_pam4_स्वतः_speeds)) अणु
		link_info->advertising_pam4 = link_info->support_pam4_स्वतः_speeds;
		support_changed = true;
	पूर्ण
	अगर (support_changed && (link_info->स्वतःneg & BNXT_AUTONEG_SPEED))
		bnxt_hwrm_set_link_setting(bp, true, false);
	वापस 0;
पूर्ण

अटल व्योम bnxt_get_port_module_status(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_link_info *link_info = &bp->link_info;
	काष्ठा hwrm_port_phy_qcfg_output *resp = &link_info->phy_qcfg_resp;
	u8 module_status;

	अगर (bnxt_update_link(bp, true))
		वापस;

	module_status = link_info->module_status;
	चयन (module_status) अणु
	हाल PORT_PHY_QCFG_RESP_MODULE_STATUS_DISABLETX:
	हाल PORT_PHY_QCFG_RESP_MODULE_STATUS_PWRDOWN:
	हाल PORT_PHY_QCFG_RESP_MODULE_STATUS_WARNINGMSG:
		netdev_warn(bp->dev, "Unqualified SFP+ module detected on port %d\n",
			    bp->pf.port_id);
		अगर (bp->hwrm_spec_code >= 0x10201) अणु
			netdev_warn(bp->dev, "Module part number %s\n",
				    resp->phy_venकरोr_partnumber);
		पूर्ण
		अगर (module_status == PORT_PHY_QCFG_RESP_MODULE_STATUS_DISABLETX)
			netdev_warn(bp->dev, "TX is disabled\n");
		अगर (module_status == PORT_PHY_QCFG_RESP_MODULE_STATUS_PWRDOWN)
			netdev_warn(bp->dev, "SFP+ module is shutdown\n");
	पूर्ण
पूर्ण

अटल व्योम
bnxt_hwrm_set_छोड़ो_common(काष्ठा bnxt *bp, काष्ठा hwrm_port_phy_cfg_input *req)
अणु
	अगर (bp->link_info.स्वतःneg & BNXT_AUTONEG_FLOW_CTRL) अणु
		अगर (bp->hwrm_spec_code >= 0x10201)
			req->स्वतः_छोड़ो =
				PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE;
		अगर (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_RX)
			req->स्वतः_छोड़ो |= PORT_PHY_CFG_REQ_AUTO_PAUSE_RX;
		अगर (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_TX)
			req->स्वतः_छोड़ो |= PORT_PHY_CFG_REQ_AUTO_PAUSE_TX;
		req->enables |=
			cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE);
	पूर्ण अन्यथा अणु
		अगर (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_RX)
			req->क्रमce_छोड़ो |= PORT_PHY_CFG_REQ_FORCE_PAUSE_RX;
		अगर (bp->link_info.req_flow_ctrl & BNXT_LINK_PAUSE_TX)
			req->क्रमce_छोड़ो |= PORT_PHY_CFG_REQ_FORCE_PAUSE_TX;
		req->enables |=
			cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_FORCE_PAUSE);
		अगर (bp->hwrm_spec_code >= 0x10201) अणु
			req->स्वतः_छोड़ो = req->क्रमce_छोड़ो;
			req->enables |= cpu_to_le32(
				PORT_PHY_CFG_REQ_ENABLES_AUTO_PAUSE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_hwrm_set_link_common(काष्ठा bnxt *bp, काष्ठा hwrm_port_phy_cfg_input *req)
अणु
	अगर (bp->link_info.स्वतःneg & BNXT_AUTONEG_SPEED) अणु
		req->स्वतः_mode |= PORT_PHY_CFG_REQ_AUTO_MODE_SPEED_MASK;
		अगर (bp->link_info.advertising) अणु
			req->enables |= cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_LINK_SPEED_MASK);
			req->स्वतः_link_speed_mask = cpu_to_le16(bp->link_info.advertising);
		पूर्ण
		अगर (bp->link_info.advertising_pam4) अणु
			req->enables |=
				cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_PAM4_LINK_SPEED_MASK);
			req->स्वतः_link_pam4_speed_mask =
				cpu_to_le16(bp->link_info.advertising_pam4);
		पूर्ण
		req->enables |= cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_AUTO_MODE);
		req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_RESTART_AUTONEG);
	पूर्ण अन्यथा अणु
		req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_FORCE);
		अगर (bp->link_info.req_संकेत_mode == BNXT_SIG_MODE_PAM4) अणु
			req->क्रमce_pam4_link_speed = cpu_to_le16(bp->link_info.req_link_speed);
			req->enables |= cpu_to_le32(PORT_PHY_CFG_REQ_ENABLES_FORCE_PAM4_LINK_SPEED);
		पूर्ण अन्यथा अणु
			req->क्रमce_link_speed = cpu_to_le16(bp->link_info.req_link_speed);
		पूर्ण
	पूर्ण

	/* tell chimp that the setting takes effect immediately */
	req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_RESET_PHY);
पूर्ण

पूर्णांक bnxt_hwrm_set_छोड़ो(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_port_phy_cfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	bnxt_hwrm_set_छोड़ो_common(bp, &req);

	अगर ((bp->link_info.स्वतःneg & BNXT_AUTONEG_FLOW_CTRL) ||
	    bp->link_info.क्रमce_link_chng)
		bnxt_hwrm_set_link_common(bp, &req);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc && !(bp->link_info.स्वतःneg & BNXT_AUTONEG_FLOW_CTRL)) अणु
		/* since changing of छोड़ो setting करोesn't trigger any link
		 * change event, the driver needs to update the current छोड़ो
		 * result upon successfully वापस of the phy_cfg command
		 */
		bp->link_info.छोड़ो =
		bp->link_info.क्रमce_छोड़ो_setting = bp->link_info.req_flow_ctrl;
		bp->link_info.स्वतः_छोड़ो_setting = 0;
		अगर (!bp->link_info.क्रमce_link_chng)
			bnxt_report_link(bp);
	पूर्ण
	bp->link_info.क्रमce_link_chng = false;
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_hwrm_set_eee(काष्ठा bnxt *bp,
			      काष्ठा hwrm_port_phy_cfg_input *req)
अणु
	काष्ठा ethtool_eee *eee = &bp->eee;

	अगर (eee->eee_enabled) अणु
		u16 eee_speeds;
		u32 flags = PORT_PHY_CFG_REQ_FLAGS_EEE_ENABLE;

		अगर (eee->tx_lpi_enabled)
			flags |= PORT_PHY_CFG_REQ_FLAGS_EEE_TX_LPI_ENABLE;
		अन्यथा
			flags |= PORT_PHY_CFG_REQ_FLAGS_EEE_TX_LPI_DISABLE;

		req->flags |= cpu_to_le32(flags);
		eee_speeds = bnxt_get_fw_स्वतः_link_speeds(eee->advertised);
		req->eee_link_speed_mask = cpu_to_le16(eee_speeds);
		req->tx_lpi_समयr = cpu_to_le32(eee->tx_lpi_समयr);
	पूर्ण अन्यथा अणु
		req->flags |= cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_EEE_DISABLE);
	पूर्ण
पूर्ण

पूर्णांक bnxt_hwrm_set_link_setting(काष्ठा bnxt *bp, bool set_छोड़ो, bool set_eee)
अणु
	काष्ठा hwrm_port_phy_cfg_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	अगर (set_छोड़ो)
		bnxt_hwrm_set_छोड़ो_common(bp, &req);

	bnxt_hwrm_set_link_common(bp, &req);

	अगर (set_eee)
		bnxt_hwrm_set_eee(bp, &req);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_hwrm_shutकरोwn_link(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_port_phy_cfg_input req = अणु0पूर्ण;

	अगर (!BNXT_SINGLE_PF(bp))
		वापस 0;

	अगर (pci_num_vf(bp->pdev) &&
	    !(bp->phy_flags & BNXT_PHY_FL_FW_MANAGED_LKDN))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_CFG, -1, -1);
	req.flags = cpu_to_le32(PORT_PHY_CFG_REQ_FLAGS_FORCE_LINK_DWN);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक bnxt_fw_init_one(काष्ठा bnxt *bp);

अटल पूर्णांक bnxt_fw_reset_via_optee(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_TEE_BNXT_FW
	पूर्णांक rc = tee_bnxt_fw_load();

	अगर (rc)
		netdev_err(bp->dev, "Failed FW reset via OP-TEE, rc=%d\n", rc);

	वापस rc;
#अन्यथा
	netdev_err(bp->dev, "OP-TEE not supported\n");
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bnxt_try_recover_fw(काष्ठा bnxt *bp)
अणु
	अगर (bp->fw_health && bp->fw_health->status_reliable) अणु
		पूर्णांक retry = 0, rc;
		u32 sts;

		mutex_lock(&bp->hwrm_cmd_lock);
		करो अणु
			sts = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG);
			rc = __bnxt_hwrm_ver_get(bp, true);
			अगर (!BNXT_FW_IS_BOOTING(sts) &&
			    !BNXT_FW_IS_RECOVERING(sts))
				अवरोध;
			retry++;
		पूर्ण जबतक (rc == -EBUSY && retry < BNXT_FW_RETRY);
		mutex_unlock(&bp->hwrm_cmd_lock);

		अगर (!BNXT_FW_IS_HEALTHY(sts)) अणु
			netdev_err(bp->dev,
				   "Firmware not responding, status: 0x%x\n",
				   sts);
			rc = -ENODEV;
		पूर्ण
		अगर (sts & FW_STATUS_REG_CRASHED_NO_MASTER) अणु
			netdev_warn(bp->dev, "Firmware recover via OP-TEE requested\n");
			वापस bnxt_fw_reset_via_optee(bp);
		पूर्ण
		वापस rc;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक bnxt_hwrm_अगर_change(काष्ठा bnxt *bp, bool up)
अणु
	काष्ठा hwrm_func_drv_अगर_change_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_drv_अगर_change_input req = अणु0पूर्ण;
	bool fw_reset = !bp->irq_tbl;
	bool resc_reinit = false;
	पूर्णांक rc, retry = 0;
	u32 flags = 0;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_IF_CHANGE))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_DRV_IF_CHANGE, -1, -1);
	अगर (up)
		req.flags = cpu_to_le32(FUNC_DRV_IF_CHANGE_REQ_FLAGS_UP);
	mutex_lock(&bp->hwrm_cmd_lock);
	जबतक (retry < BNXT_FW_IF_RETRY) अणु
		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc != -EAGAIN)
			अवरोध;

		msleep(50);
		retry++;
	पूर्ण
	अगर (!rc)
		flags = le32_to_cpu(resp->flags);
	mutex_unlock(&bp->hwrm_cmd_lock);

	अगर (rc == -EAGAIN)
		वापस rc;
	अगर (rc && up) अणु
		rc = bnxt_try_recover_fw(bp);
		fw_reset = true;
	पूर्ण
	अगर (rc)
		वापस rc;

	अगर (!up) अणु
		bnxt_inv_fw_health_reg(bp);
		वापस 0;
	पूर्ण

	अगर (flags & FUNC_DRV_IF_CHANGE_RESP_FLAGS_RESC_CHANGE)
		resc_reinit = true;
	अगर (flags & FUNC_DRV_IF_CHANGE_RESP_FLAGS_HOT_FW_RESET_DONE)
		fw_reset = true;
	अन्यथा अगर (bp->fw_health && !bp->fw_health->status_reliable)
		bnxt_try_map_fw_health_reg(bp);

	अगर (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state) && !fw_reset) अणु
		netdev_err(bp->dev, "RESET_DONE not set during FW reset.\n");
		set_bit(BNXT_STATE_ABORT_ERR, &bp->state);
		वापस -ENODEV;
	पूर्ण
	अगर (resc_reinit || fw_reset) अणु
		अगर (fw_reset) अणु
			set_bit(BNXT_STATE_FW_RESET_DET, &bp->state);
			अगर (!test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
				bnxt_ulp_stop(bp);
			bnxt_मुक्त_ctx_mem(bp);
			kमुक्त(bp->ctx);
			bp->ctx = शून्य;
			bnxt_dcb_मुक्त(bp);
			rc = bnxt_fw_init_one(bp);
			अगर (rc) अणु
				clear_bit(BNXT_STATE_FW_RESET_DET, &bp->state);
				set_bit(BNXT_STATE_ABORT_ERR, &bp->state);
				वापस rc;
			पूर्ण
			bnxt_clear_पूर्णांक_mode(bp);
			rc = bnxt_init_पूर्णांक_mode(bp);
			अगर (rc) अणु
				clear_bit(BNXT_STATE_FW_RESET_DET, &bp->state);
				netdev_err(bp->dev, "init int mode failed\n");
				वापस rc;
			पूर्ण
		पूर्ण
		अगर (BNXT_NEW_RM(bp)) अणु
			काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;

			rc = bnxt_hwrm_func_resc_qcaps(bp, true);
			अगर (rc)
				netdev_err(bp->dev, "resc_qcaps failed\n");

			hw_resc->resv_cp_rings = 0;
			hw_resc->resv_stat_ctxs = 0;
			hw_resc->resv_irqs = 0;
			hw_resc->resv_tx_rings = 0;
			hw_resc->resv_rx_rings = 0;
			hw_resc->resv_hw_ring_grps = 0;
			hw_resc->resv_vnics = 0;
			अगर (!fw_reset) अणु
				bp->tx_nr_rings = 0;
				bp->rx_nr_rings = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_led_qcaps(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_port_led_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_port_led_qcaps_input req = अणु0पूर्ण;
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	पूर्णांक rc;

	bp->num_leds = 0;
	अगर (BNXT_VF(bp) || bp->hwrm_spec_code < 0x10601)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_LED_QCAPS, -1, -1);
	req.port_id = cpu_to_le16(pf->port_id);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण
	अगर (resp->num_leds > 0 && resp->num_leds < BNXT_MAX_LED) अणु
		पूर्णांक i;

		bp->num_leds = resp->num_leds;
		स_नकल(bp->leds, &resp->led0_id, माप(bp->leds[0]) *
						 bp->num_leds);
		क्रम (i = 0; i < bp->num_leds; i++) अणु
			काष्ठा bnxt_led_info *led = &bp->leds[i];
			__le16 caps = led->led_state_caps;

			अगर (!led->led_group_id ||
			    !BNXT_LED_ALT_BLINK_CAP(caps)) अणु
				bp->num_leds = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस 0;
पूर्ण

पूर्णांक bnxt_hwrm_alloc_wol_fltr(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_wol_filter_alloc_input req = अणु0पूर्ण;
	काष्ठा hwrm_wol_filter_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_WOL_FILTER_ALLOC, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.wol_type = WOL_FILTER_ALLOC_REQ_WOL_TYPE_MAGICPKT;
	req.enables = cpu_to_le32(WOL_FILTER_ALLOC_REQ_ENABLES_MAC_ADDRESS);
	स_नकल(req.mac_address, bp->dev->dev_addr, ETH_ALEN);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		bp->wol_filter_id = resp->wol_filter_id;
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

पूर्णांक bnxt_hwrm_मुक्त_wol_fltr(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_wol_filter_मुक्त_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_WOL_FILTER_FREE, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.enables = cpu_to_le32(WOL_FILTER_FREE_REQ_ENABLES_WOL_FILTER_ID);
	req.wol_filter_id = bp->wol_filter_id;
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल u16 bnxt_hwrm_get_wol_fltrs(काष्ठा bnxt *bp, u16 handle)
अणु
	काष्ठा hwrm_wol_filter_qcfg_input req = अणु0पूर्ण;
	काष्ठा hwrm_wol_filter_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	u16 next_handle = 0;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_WOL_FILTER_QCFG, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.handle = cpu_to_le16(handle);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		next_handle = le16_to_cpu(resp->next_handle);
		अगर (next_handle != 0) अणु
			अगर (resp->wol_type ==
			    WOL_FILTER_ALLOC_REQ_WOL_TYPE_MAGICPKT) अणु
				bp->wol = 1;
				bp->wol_filter_id = resp->wol_filter_id;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस next_handle;
पूर्ण

अटल व्योम bnxt_get_wol_settings(काष्ठा bnxt *bp)
अणु
	u16 handle = 0;

	bp->wol = 0;
	अगर (!BNXT_PF(bp) || !(bp->flags & BNXT_FLAG_WOL_CAP))
		वापस;

	करो अणु
		handle = bnxt_hwrm_get_wol_fltrs(bp, handle);
	पूर्ण जबतक (handle && handle != 0xffff);
पूर्ण

#अगर_घोषित CONFIG_BNXT_HWMON
अटल sमाप_प्रकार bnxt_show_temp(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा hwrm_temp_monitor_query_input req = अणु0पूर्ण;
	काष्ठा hwrm_temp_monitor_query_output *resp;
	काष्ठा bnxt *bp = dev_get_drvdata(dev);
	u32 len = 0;
	पूर्णांक rc;

	resp = bp->hwrm_cmd_resp_addr;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_TEMP_MONITOR_QUERY, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		len = प्र_लिखो(buf, "%u\n", resp->temp * 1000); /* display millidegree */
	mutex_unlock(&bp->hwrm_cmd_lock);
	अगर (rc)
		वापस rc;
	वापस len;
पूर्ण
अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, bnxt_show_temp, शून्य, 0);

अटल काष्ठा attribute *bnxt_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(bnxt);

अटल व्योम bnxt_hwmon_बंद(काष्ठा bnxt *bp)
अणु
	अगर (bp->hwmon_dev) अणु
		hwmon_device_unरेजिस्टर(bp->hwmon_dev);
		bp->hwmon_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम bnxt_hwmon_खोलो(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_temp_monitor_query_input req = अणु0पूर्ण;
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_TEMP_MONITOR_QUERY, -1, -1);
	rc = hwrm_send_message_silent(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc == -EACCES || rc == -EOPNOTSUPP) अणु
		bnxt_hwmon_बंद(bp);
		वापस;
	पूर्ण

	अगर (bp->hwmon_dev)
		वापस;

	bp->hwmon_dev = hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
							  DRV_MODULE_NAME, bp,
							  bnxt_groups);
	अगर (IS_ERR(bp->hwmon_dev)) अणु
		bp->hwmon_dev = शून्य;
		dev_warn(&pdev->dev, "Cannot register hwmon device\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम bnxt_hwmon_बंद(काष्ठा bnxt *bp)
अणु
पूर्ण

अटल व्योम bnxt_hwmon_खोलो(काष्ठा bnxt *bp)
अणु
पूर्ण
#पूर्ण_अगर

अटल bool bnxt_eee_config_ok(काष्ठा bnxt *bp)
अणु
	काष्ठा ethtool_eee *eee = &bp->eee;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (!(bp->phy_flags & BNXT_PHY_FL_EEE_CAP))
		वापस true;

	अगर (eee->eee_enabled) अणु
		u32 advertising =
			_bnxt_fw_to_ethtool_adv_spds(link_info->advertising, 0);

		अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED)) अणु
			eee->eee_enabled = 0;
			वापस false;
		पूर्ण
		अगर (eee->advertised & ~advertising) अणु
			eee->advertised = advertising & eee->supported;
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक bnxt_update_phy_setting(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;
	bool update_link = false;
	bool update_छोड़ो = false;
	bool update_eee = false;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	rc = bnxt_update_link(bp, true);
	अगर (rc) अणु
		netdev_err(bp->dev, "failed to update link (rc: %x)\n",
			   rc);
		वापस rc;
	पूर्ण
	अगर (!BNXT_SINGLE_PF(bp))
		वापस 0;

	अगर ((link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL) &&
	    (link_info->स्वतः_छोड़ो_setting & BNXT_LINK_PAUSE_BOTH) !=
	    link_info->req_flow_ctrl)
		update_छोड़ो = true;
	अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL) &&
	    link_info->क्रमce_छोड़ो_setting != link_info->req_flow_ctrl)
		update_छोड़ो = true;
	अगर (!(link_info->स्वतःneg & BNXT_AUTONEG_SPEED)) अणु
		अगर (BNXT_AUTO_MODE(link_info->स्वतः_mode))
			update_link = true;
		अगर (link_info->req_संकेत_mode == BNXT_SIG_MODE_NRZ &&
		    link_info->req_link_speed != link_info->क्रमce_link_speed)
			update_link = true;
		अन्यथा अगर (link_info->req_संकेत_mode == BNXT_SIG_MODE_PAM4 &&
			 link_info->req_link_speed != link_info->क्रमce_pam4_link_speed)
			update_link = true;
		अगर (link_info->req_duplex != link_info->duplex_setting)
			update_link = true;
	पूर्ण अन्यथा अणु
		अगर (link_info->स्वतः_mode == BNXT_LINK_AUTO_NONE)
			update_link = true;
		अगर (link_info->advertising != link_info->स्वतः_link_speeds ||
		    link_info->advertising_pam4 != link_info->स्वतः_pam4_link_speeds)
			update_link = true;
	पूर्ण

	/* The last बंद may have shutकरोwn the link, so need to call
	 * PHY_CFG to bring it back up.
	 */
	अगर (!bp->link_info.link_up)
		update_link = true;

	अगर (!bnxt_eee_config_ok(bp))
		update_eee = true;

	अगर (update_link)
		rc = bnxt_hwrm_set_link_setting(bp, update_छोड़ो, update_eee);
	अन्यथा अगर (update_छोड़ो)
		rc = bnxt_hwrm_set_छोड़ो(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "failed to update phy setting (rc: %x)\n",
			   rc);
		वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

/* Common routine to pre-map certain रेजिस्टर block to dअगरferent GRC winकरोw.
 * A PF has 16 4K winकरोws and a VF has 4 4K winकरोws. However, only 15 winकरोws
 * in PF and 3 winकरोws in VF that can be customized to map in dअगरferent
 * रेजिस्टर blocks.
 */
अटल व्योम bnxt_preset_reg_win(काष्ठा bnxt *bp)
अणु
	अगर (BNXT_PF(bp)) अणु
		/* CAG रेजिस्टरs map to GRC winकरोw #4 */
		ग_लिखोl(BNXT_CAG_REG_BASE,
		       bp->bar0 + BNXT_GRCPF_REG_WINDOW_BASE_OUT + 12);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_init_dflt_ring_mode(काष्ठा bnxt *bp);

अटल पूर्णांक bnxt_reinit_after_पात(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	अगर (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
		वापस -EBUSY;

	अगर (bp->dev->reg_state == NETREG_UNREGISTERED)
		वापस -ENODEV;

	rc = bnxt_fw_init_one(bp);
	अगर (!rc) अणु
		bnxt_clear_पूर्णांक_mode(bp);
		rc = bnxt_init_पूर्णांक_mode(bp);
		अगर (!rc) अणु
			clear_bit(BNXT_STATE_ABORT_ERR, &bp->state);
			set_bit(BNXT_STATE_FW_RESET_DET, &bp->state);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक __bnxt_खोलो_nic(काष्ठा bnxt *bp, bool irq_re_init, bool link_re_init)
अणु
	पूर्णांक rc = 0;

	bnxt_preset_reg_win(bp);
	netअगर_carrier_off(bp->dev);
	अगर (irq_re_init) अणु
		/* Reserve rings now अगर none were reserved at driver probe. */
		rc = bnxt_init_dflt_ring_mode(bp);
		अगर (rc) अणु
			netdev_err(bp->dev, "Failed to reserve default rings at open\n");
			वापस rc;
		पूर्ण
	पूर्ण
	rc = bnxt_reserve_rings(bp, irq_re_init);
	अगर (rc)
		वापस rc;
	अगर ((bp->flags & BNXT_FLAG_RFS) &&
	    !(bp->flags & BNXT_FLAG_USING_MSIX)) अणु
		/* disable RFS अगर falling back to INTA */
		bp->dev->hw_features &= ~NETIF_F_NTUPLE;
		bp->flags &= ~BNXT_FLAG_RFS;
	पूर्ण

	rc = bnxt_alloc_mem(bp, irq_re_init);
	अगर (rc) अणु
		netdev_err(bp->dev, "bnxt_alloc_mem err: %x\n", rc);
		जाओ खोलो_err_मुक्त_mem;
	पूर्ण

	अगर (irq_re_init) अणु
		bnxt_init_napi(bp);
		rc = bnxt_request_irq(bp);
		अगर (rc) अणु
			netdev_err(bp->dev, "bnxt_request_irq err: %x\n", rc);
			जाओ खोलो_err_irq;
		पूर्ण
	पूर्ण

	rc = bnxt_init_nic(bp, irq_re_init);
	अगर (rc) अणु
		netdev_err(bp->dev, "bnxt_init_nic err: %x\n", rc);
		जाओ खोलो_err_irq;
	पूर्ण

	bnxt_enable_napi(bp);
	bnxt_debug_dev_init(bp);

	अगर (link_re_init) अणु
		mutex_lock(&bp->link_lock);
		rc = bnxt_update_phy_setting(bp);
		mutex_unlock(&bp->link_lock);
		अगर (rc) अणु
			netdev_warn(bp->dev, "failed to update phy settings\n");
			अगर (BNXT_SINGLE_PF(bp)) अणु
				bp->link_info.phy_retry = true;
				bp->link_info.phy_retry_expires =
					jअगरfies + 5 * HZ;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (irq_re_init)
		udp_tunnel_nic_reset_ntf(bp->dev);

	set_bit(BNXT_STATE_OPEN, &bp->state);
	bnxt_enable_पूर्णांक(bp);
	/* Enable TX queues */
	bnxt_tx_enable(bp);
	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
	/* Poll link status and check क्रम SFP+ module status */
	bnxt_get_port_module_status(bp);

	/* VF-reps may need to be re-खोलोed after the PF is re-खोलोed */
	अगर (BNXT_PF(bp))
		bnxt_vf_reps_खोलो(bp);
	वापस 0;

खोलो_err_irq:
	bnxt_del_napi(bp);

खोलो_err_मुक्त_mem:
	bnxt_मुक्त_skbs(bp);
	bnxt_मुक्त_irq(bp);
	bnxt_मुक्त_mem(bp, true);
	वापस rc;
पूर्ण

/* rtnl_lock held */
पूर्णांक bnxt_खोलो_nic(काष्ठा bnxt *bp, bool irq_re_init, bool link_re_init)
अणु
	पूर्णांक rc = 0;

	अगर (test_bit(BNXT_STATE_ABORT_ERR, &bp->state))
		rc = -EIO;
	अगर (!rc)
		rc = __bnxt_खोलो_nic(bp, irq_re_init, link_re_init);
	अगर (rc) अणु
		netdev_err(bp->dev, "nic open fail (rc: %x)\n", rc);
		dev_बंद(bp->dev);
	पूर्ण
	वापस rc;
पूर्ण

/* rtnl_lock held, खोलो the NIC half way by allocating all resources, but
 * NAPI, IRQ, and TX are not enabled.  This is मुख्यly used क्रम offline
 * self tests.
 */
पूर्णांक bnxt_half_खोलो_nic(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0;

	rc = bnxt_alloc_mem(bp, false);
	अगर (rc) अणु
		netdev_err(bp->dev, "bnxt_alloc_mem err: %x\n", rc);
		जाओ half_खोलो_err;
	पूर्ण
	rc = bnxt_init_nic(bp, false);
	अगर (rc) अणु
		netdev_err(bp->dev, "bnxt_init_nic err: %x\n", rc);
		जाओ half_खोलो_err;
	पूर्ण
	वापस 0;

half_खोलो_err:
	bnxt_मुक्त_skbs(bp);
	bnxt_मुक्त_mem(bp, false);
	dev_बंद(bp->dev);
	वापस rc;
पूर्ण

/* rtnl_lock held, this call can only be made after a previous successful
 * call to bnxt_half_खोलो_nic().
 */
व्योम bnxt_half_बंद_nic(काष्ठा bnxt *bp)
अणु
	bnxt_hwrm_resource_मुक्त(bp, false, false);
	bnxt_मुक्त_skbs(bp);
	bnxt_मुक्त_mem(bp, false);
पूर्ण

अटल व्योम bnxt_reenable_sriov(काष्ठा bnxt *bp)
अणु
	अगर (BNXT_PF(bp)) अणु
		काष्ठा bnxt_pf_info *pf = &bp->pf;
		पूर्णांक n = pf->active_vfs;

		अगर (n)
			bnxt_cfg_hw_sriov(bp, &n, true);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (test_bit(BNXT_STATE_ABORT_ERR, &bp->state)) अणु
		rc = bnxt_reinit_after_पात(bp);
		अगर (rc) अणु
			अगर (rc == -EBUSY)
				netdev_err(bp->dev, "A previous firmware reset has not completed, aborting\n");
			अन्यथा
				netdev_err(bp->dev, "Failed to reinitialize after aborted firmware reset\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	rc = bnxt_hwrm_अगर_change(bp, true);
	अगर (rc)
		वापस rc;
	rc = __bnxt_खोलो_nic(bp, true, true);
	अगर (rc) अणु
		bnxt_hwrm_अगर_change(bp, false);
	पूर्ण अन्यथा अणु
		अगर (test_and_clear_bit(BNXT_STATE_FW_RESET_DET, &bp->state)) अणु
			अगर (!test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) अणु
				bnxt_ulp_start(bp, 0);
				bnxt_reenable_sriov(bp);
			पूर्ण
		पूर्ण
		bnxt_hwmon_खोलो(bp);
	पूर्ण

	वापस rc;
पूर्ण

अटल bool bnxt_drv_busy(काष्ठा bnxt *bp)
अणु
	वापस (test_bit(BNXT_STATE_IN_SP_TASK, &bp->state) ||
		test_bit(BNXT_STATE_READ_STATS, &bp->state));
पूर्ण

अटल व्योम bnxt_get_ring_stats(काष्ठा bnxt *bp,
				काष्ठा rtnl_link_stats64 *stats);

अटल व्योम __bnxt_बंद_nic(काष्ठा bnxt *bp, bool irq_re_init,
			     bool link_re_init)
अणु
	/* Close the VF-reps beक्रमe closing PF */
	अगर (BNXT_PF(bp))
		bnxt_vf_reps_बंद(bp);

	/* Change device state to aव्योम TX queue wake up's */
	bnxt_tx_disable(bp);

	clear_bit(BNXT_STATE_OPEN, &bp->state);
	smp_mb__after_atomic();
	जबतक (bnxt_drv_busy(bp))
		msleep(20);

	/* Flush rings and and disable पूर्णांकerrupts */
	bnxt_shutकरोwn_nic(bp, irq_re_init);

	/* TODO CHIMP_FW: Link/PHY related cleanup अगर (link_re_init) */

	bnxt_debug_dev_निकास(bp);
	bnxt_disable_napi(bp);
	del_समयr_sync(&bp->समयr);
	bnxt_मुक्त_skbs(bp);

	/* Save ring stats beक्रमe shutकरोwn */
	अगर (bp->bnapi && irq_re_init)
		bnxt_get_ring_stats(bp, &bp->net_stats_prev);
	अगर (irq_re_init) अणु
		bnxt_मुक्त_irq(bp);
		bnxt_del_napi(bp);
	पूर्ण
	bnxt_मुक्त_mem(bp, irq_re_init);
पूर्ण

पूर्णांक bnxt_बंद_nic(काष्ठा bnxt *bp, bool irq_re_init, bool link_re_init)
अणु
	पूर्णांक rc = 0;

	अगर (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) अणु
		/* If we get here, it means firmware reset is in progress
		 * जबतक we are trying to बंद.  We can safely proceed with
		 * the बंद because we are holding rtnl_lock().  Some firmware
		 * messages may fail as we proceed to बंद.  We set the
		 * ABORT_ERR flag here so that the FW reset thपढ़ो will later
		 * पात when it माला_लो the rtnl_lock() and sees the flag.
		 */
		netdev_warn(bp->dev, "FW reset in progress during close, FW reset will be aborted\n");
		set_bit(BNXT_STATE_ABORT_ERR, &bp->state);
	पूर्ण

#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (bp->sriov_cfg) अणु
		rc = रुको_event_पूर्णांकerruptible_समयout(bp->sriov_cfg_रुको,
						      !bp->sriov_cfg,
						      BNXT_SRIOV_CFG_WAIT_TMO);
		अगर (rc)
			netdev_warn(bp->dev, "timeout waiting for SRIOV config operation to complete!\n");
	पूर्ण
#पूर्ण_अगर
	__bnxt_बंद_nic(bp, irq_re_init, link_re_init);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	bnxt_hwmon_बंद(bp);
	bnxt_बंद_nic(bp, true, true);
	bnxt_hwrm_shutकरोwn_link(bp);
	bnxt_hwrm_अगर_change(bp, false);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_phy_पढ़ो(काष्ठा bnxt *bp, u16 phy_addr, u16 reg,
				   u16 *val)
अणु
	काष्ठा hwrm_port_phy_mdio_पढ़ो_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_port_phy_mdio_पढ़ो_input req = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10a00)
		वापस -EOPNOTSUPP;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_MDIO_READ, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.phy_addr = phy_addr;
	req.reg_addr = cpu_to_le16(reg & 0x1f);
	अगर (mdio_phy_id_is_c45(phy_addr)) अणु
		req.cl45_mdio = 1;
		req.phy_addr = mdio_phy_id_prtad(phy_addr);
		req.dev_addr = mdio_phy_id_devad(phy_addr);
		req.reg_addr = cpu_to_le16(reg);
	पूर्ण

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		*val = le16_to_cpu(resp->reg_data);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_port_phy_ग_लिखो(काष्ठा bnxt *bp, u16 phy_addr, u16 reg,
				    u16 val)
अणु
	काष्ठा hwrm_port_phy_mdio_ग_लिखो_input req = अणु0पूर्ण;

	अगर (bp->hwrm_spec_code < 0x10a00)
		वापस -EOPNOTSUPP;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_MDIO_WRITE, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.phy_addr = phy_addr;
	req.reg_addr = cpu_to_le16(reg & 0x1f);
	अगर (mdio_phy_id_is_c45(phy_addr)) अणु
		req.cl45_mdio = 1;
		req.phy_addr = mdio_phy_id_prtad(phy_addr);
		req.dev_addr = mdio_phy_id_devad(phy_addr);
		req.reg_addr = cpu_to_le16(reg);
	पूर्ण
	req.reg_data = cpu_to_le16(val);

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

/* rtnl_lock held */
अटल पूर्णांक bnxt_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *mdio = अगर_mii(अगरr);
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		mdio->phy_id = bp->link_info.phy_addr;

		fallthrough;
	हाल SIOCGMIIREG: अणु
		u16 mii_regval = 0;

		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		rc = bnxt_hwrm_port_phy_पढ़ो(bp, mdio->phy_id, mdio->reg_num,
					     &mii_regval);
		mdio->val_out = mii_regval;
		वापस rc;
	पूर्ण

	हाल SIOCSMIIREG:
		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		वापस bnxt_hwrm_port_phy_ग_लिखो(bp, mdio->phy_id, mdio->reg_num,
						mdio->val_in);

	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम bnxt_get_ring_stats(काष्ठा bnxt *bp,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		u64 *sw = cpr->stats.sw_stats;

		stats->rx_packets += BNXT_GET_RING_STATS64(sw, rx_ucast_pkts);
		stats->rx_packets += BNXT_GET_RING_STATS64(sw, rx_mcast_pkts);
		stats->rx_packets += BNXT_GET_RING_STATS64(sw, rx_bcast_pkts);

		stats->tx_packets += BNXT_GET_RING_STATS64(sw, tx_ucast_pkts);
		stats->tx_packets += BNXT_GET_RING_STATS64(sw, tx_mcast_pkts);
		stats->tx_packets += BNXT_GET_RING_STATS64(sw, tx_bcast_pkts);

		stats->rx_bytes += BNXT_GET_RING_STATS64(sw, rx_ucast_bytes);
		stats->rx_bytes += BNXT_GET_RING_STATS64(sw, rx_mcast_bytes);
		stats->rx_bytes += BNXT_GET_RING_STATS64(sw, rx_bcast_bytes);

		stats->tx_bytes += BNXT_GET_RING_STATS64(sw, tx_ucast_bytes);
		stats->tx_bytes += BNXT_GET_RING_STATS64(sw, tx_mcast_bytes);
		stats->tx_bytes += BNXT_GET_RING_STATS64(sw, tx_bcast_bytes);

		stats->rx_missed_errors +=
			BNXT_GET_RING_STATS64(sw, rx_discard_pkts);

		stats->multicast += BNXT_GET_RING_STATS64(sw, rx_mcast_pkts);

		stats->tx_dropped += BNXT_GET_RING_STATS64(sw, tx_error_pkts);
	पूर्ण
पूर्ण

अटल व्योम bnxt_add_prev_stats(काष्ठा bnxt *bp,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा rtnl_link_stats64 *prev_stats = &bp->net_stats_prev;

	stats->rx_packets += prev_stats->rx_packets;
	stats->tx_packets += prev_stats->tx_packets;
	stats->rx_bytes += prev_stats->rx_bytes;
	stats->tx_bytes += prev_stats->tx_bytes;
	stats->rx_missed_errors += prev_stats->rx_missed_errors;
	stats->multicast += prev_stats->multicast;
	stats->tx_dropped += prev_stats->tx_dropped;
पूर्ण

अटल व्योम
bnxt_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	set_bit(BNXT_STATE_READ_STATS, &bp->state);
	/* Make sure bnxt_बंद_nic() sees that we are पढ़ोing stats beक्रमe
	 * we check the BNXT_STATE_OPEN flag.
	 */
	smp_mb__after_atomic();
	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state)) अणु
		clear_bit(BNXT_STATE_READ_STATS, &bp->state);
		*stats = bp->net_stats_prev;
		वापस;
	पूर्ण

	bnxt_get_ring_stats(bp, stats);
	bnxt_add_prev_stats(bp, stats);

	अगर (bp->flags & BNXT_FLAG_PORT_STATS) अणु
		u64 *rx = bp->port_stats.sw_stats;
		u64 *tx = bp->port_stats.sw_stats +
			  BNXT_TX_PORT_STATS_BYTE_OFFSET / 8;

		stats->rx_crc_errors =
			BNXT_GET_RX_PORT_STATS64(rx, rx_fcs_err_frames);
		stats->rx_frame_errors =
			BNXT_GET_RX_PORT_STATS64(rx, rx_align_err_frames);
		stats->rx_length_errors =
			BNXT_GET_RX_PORT_STATS64(rx, rx_undrsz_frames) +
			BNXT_GET_RX_PORT_STATS64(rx, rx_ovrsz_frames) +
			BNXT_GET_RX_PORT_STATS64(rx, rx_runt_frames);
		stats->rx_errors =
			BNXT_GET_RX_PORT_STATS64(rx, rx_false_carrier_frames) +
			BNXT_GET_RX_PORT_STATS64(rx, rx_jbr_frames);
		stats->collisions =
			BNXT_GET_TX_PORT_STATS64(tx, tx_total_collisions);
		stats->tx_fअगरo_errors =
			BNXT_GET_TX_PORT_STATS64(tx, tx_fअगरo_underruns);
		stats->tx_errors = BNXT_GET_TX_PORT_STATS64(tx, tx_err);
	पूर्ण
	clear_bit(BNXT_STATE_READ_STATS, &bp->state);
पूर्ण

अटल bool bnxt_mc_list_updated(काष्ठा bnxt *bp, u32 *rx_mask)
अणु
	काष्ठा net_device *dev = bp->dev;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[0];
	काष्ठा netdev_hw_addr *ha;
	u8 *haddr;
	पूर्णांक mc_count = 0;
	bool update = false;
	पूर्णांक off = 0;

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (mc_count >= BNXT_MAX_MC_ADDRS) अणु
			*rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
			vnic->mc_list_count = 0;
			वापस false;
		पूर्ण
		haddr = ha->addr;
		अगर (!ether_addr_equal(haddr, vnic->mc_list + off)) अणु
			स_नकल(vnic->mc_list + off, haddr, ETH_ALEN);
			update = true;
		पूर्ण
		off += ETH_ALEN;
		mc_count++;
	पूर्ण
	अगर (mc_count)
		*rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_MCAST;

	अगर (mc_count != vnic->mc_list_count) अणु
		vnic->mc_list_count = mc_count;
		update = true;
	पूर्ण
	वापस update;
पूर्ण

अटल bool bnxt_uc_list_updated(काष्ठा bnxt *bp)
अणु
	काष्ठा net_device *dev = bp->dev;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[0];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक off = 0;

	अगर (netdev_uc_count(dev) != (vnic->uc_filter_count - 1))
		वापस true;

	netdev_क्रम_each_uc_addr(ha, dev) अणु
		अगर (!ether_addr_equal(ha->addr, vnic->uc_list + off))
			वापस true;

		off += ETH_ALEN;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम bnxt_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vnic_info *vnic;
	bool mc_update = false;
	bool uc_update;
	u32 mask;

	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state))
		वापस;

	vnic = &bp->vnic_info[0];
	mask = vnic->rx_mask;
	mask &= ~(CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS |
		  CFA_L2_SET_RX_MASK_REQ_MASK_MCAST |
		  CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST |
		  CFA_L2_SET_RX_MASK_REQ_MASK_BCAST);

	अगर (dev->flags & IFF_PROMISC)
		mask |= CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;

	uc_update = bnxt_uc_list_updated(bp);

	अगर (dev->flags & IFF_BROADCAST)
		mask |= CFA_L2_SET_RX_MASK_REQ_MASK_BCAST;
	अगर (dev->flags & IFF_ALLMULTI) अणु
		mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
		vnic->mc_list_count = 0;
	पूर्ण अन्यथा अणु
		mc_update = bnxt_mc_list_updated(bp, &mask);
	पूर्ण

	अगर (mask != vnic->rx_mask || uc_update || mc_update) अणु
		vnic->rx_mask = mask;

		set_bit(BNXT_RX_MASK_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_cfg_rx_mode(काष्ठा bnxt *bp)
अणु
	काष्ठा net_device *dev = bp->dev;
	काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[0];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i, off = 0, rc;
	bool uc_update;

	netअगर_addr_lock_bh(dev);
	uc_update = bnxt_uc_list_updated(bp);
	netअगर_addr_unlock_bh(dev);

	अगर (!uc_update)
		जाओ skip_uc;

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 1; i < vnic->uc_filter_count; i++) अणु
		काष्ठा hwrm_cfa_l2_filter_मुक्त_input req = अणु0पूर्ण;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_L2_FILTER_FREE, -1,
				       -1);

		req.l2_filter_id = vnic->fw_l2_filter_id[i];

		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	vnic->uc_filter_count = 1;

	netअगर_addr_lock_bh(dev);
	अगर (netdev_uc_count(dev) > (BNXT_MAX_UC_ADDRS - 1)) अणु
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_uc_addr(ha, dev) अणु
			स_नकल(vnic->uc_list + off, ha->addr, ETH_ALEN);
			off += ETH_ALEN;
			vnic->uc_filter_count++;
		पूर्ण
	पूर्ण
	netअगर_addr_unlock_bh(dev);

	क्रम (i = 1, off = 0; i < vnic->uc_filter_count; i++, off += ETH_ALEN) अणु
		rc = bnxt_hwrm_set_vnic_filter(bp, 0, i, vnic->uc_list + off);
		अगर (rc) अणु
			netdev_err(bp->dev, "HWRM vnic filter failure rc: %x\n",
				   rc);
			vnic->uc_filter_count = i;
			वापस rc;
		पूर्ण
	पूर्ण

skip_uc:
	अगर ((vnic->rx_mask & CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS) &&
	    !bnxt_promisc_ok(bp))
		vnic->rx_mask &= ~CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;
	rc = bnxt_hwrm_cfa_l2_set_rx_mask(bp, 0);
	अगर (rc && vnic->mc_list_count) अणु
		netdev_info(bp->dev, "Failed setting MC filters rc: %d, turning on ALL_MCAST mode\n",
			    rc);
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
		vnic->mc_list_count = 0;
		rc = bnxt_hwrm_cfa_l2_set_rx_mask(bp, 0);
	पूर्ण
	अगर (rc)
		netdev_err(bp->dev, "HWRM cfa l2 rx mask failure rc: %d\n",
			   rc);

	वापस rc;
पूर्ण

अटल bool bnxt_can_reserve_rings(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (BNXT_NEW_RM(bp) && BNXT_VF(bp)) अणु
		काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;

		/* No minimum rings were provisioned by the PF.  Don't
		 * reserve rings by शेष when device is करोwn.
		 */
		अगर (hw_resc->min_tx_rings || hw_resc->resv_tx_rings)
			वापस true;

		अगर (!netअगर_running(bp->dev))
			वापस false;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

/* If the chip and firmware supports RFS */
अटल bool bnxt_rfs_supported(काष्ठा bnxt *bp)
अणु
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		अगर (bp->fw_cap & BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX_V2)
			वापस true;
		वापस false;
	पूर्ण
	अगर (BNXT_PF(bp) && !BNXT_CHIP_TYPE_NITRO_A0(bp))
		वापस true;
	अगर (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
		वापस true;
	वापस false;
पूर्ण

/* If runसमय conditions support RFS */
अटल bool bnxt_rfs_capable(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	पूर्णांक vnics, max_vnics, max_rss_ctxs;

	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		वापस bnxt_rfs_supported(bp);
	अगर (!(bp->flags & BNXT_FLAG_MSIX_CAP) || !bnxt_can_reserve_rings(bp))
		वापस false;

	vnics = 1 + bp->rx_nr_rings;
	max_vnics = bnxt_get_max_func_vnics(bp);
	max_rss_ctxs = bnxt_get_max_func_rss_ctxs(bp);

	/* RSS contexts not a limiting factor */
	अगर (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
		max_rss_ctxs = max_vnics;
	अगर (vnics > max_vnics || vnics > max_rss_ctxs) अणु
		अगर (bp->rx_nr_rings > 1)
			netdev_warn(bp->dev,
				    "Not enough resources to support NTUPLE filters, enough resources for up to %d rx rings\n",
				    min(max_rss_ctxs - 1, max_vnics - 1));
		वापस false;
	पूर्ण

	अगर (!BNXT_NEW_RM(bp))
		वापस true;

	अगर (vnics == bp->hw_resc.resv_vnics)
		वापस true;

	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, 0, vnics);
	अगर (vnics <= bp->hw_resc.resv_vnics)
		वापस true;

	netdev_warn(bp->dev, "Unable to reserve resources to support NTUPLE filters.\n");
	bnxt_hwrm_reserve_rings(bp, 0, 0, 0, 0, 0, 1);
	वापस false;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल netdev_features_t bnxt_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	netdev_features_t vlan_features;

	अगर ((features & NETIF_F_NTUPLE) && !bnxt_rfs_capable(bp))
		features &= ~NETIF_F_NTUPLE;

	अगर (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);

	अगर (!(features & NETIF_F_GRO))
		features &= ~NETIF_F_GRO_HW;

	अगर (features & NETIF_F_GRO_HW)
		features &= ~NETIF_F_LRO;

	/* Both CTAG and STAG VLAN accelaration on the RX side have to be
	 * turned on or off together.
	 */
	vlan_features = features & BNXT_HW_FEATURE_VLAN_ALL_RX;
	अगर (vlan_features != BNXT_HW_FEATURE_VLAN_ALL_RX) अणु
		अगर (dev->features & BNXT_HW_FEATURE_VLAN_ALL_RX)
			features &= ~BNXT_HW_FEATURE_VLAN_ALL_RX;
		अन्यथा अगर (vlan_features)
			features |= BNXT_HW_FEATURE_VLAN_ALL_RX;
	पूर्ण
#अगर_घोषित CONFIG_BNXT_SRIOV
	अगर (BNXT_VF(bp) && bp->vf.vlan)
		features &= ~BNXT_HW_FEATURE_VLAN_ALL_RX;
#पूर्ण_अगर
	वापस features;
पूर्ण

अटल पूर्णांक bnxt_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u32 flags = bp->flags;
	u32 changes;
	पूर्णांक rc = 0;
	bool re_init = false;
	bool update_tpa = false;

	flags &= ~BNXT_FLAG_ALL_CONFIG_FEATS;
	अगर (features & NETIF_F_GRO_HW)
		flags |= BNXT_FLAG_GRO;
	अन्यथा अगर (features & NETIF_F_LRO)
		flags |= BNXT_FLAG_LRO;

	अगर (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		flags &= ~BNXT_FLAG_TPA;

	अगर (features & BNXT_HW_FEATURE_VLAN_ALL_RX)
		flags |= BNXT_FLAG_STRIP_VLAN;

	अगर (features & NETIF_F_NTUPLE)
		flags |= BNXT_FLAG_RFS;

	changes = flags ^ bp->flags;
	अगर (changes & BNXT_FLAG_TPA) अणु
		update_tpa = true;
		अगर ((bp->flags & BNXT_FLAG_TPA) == 0 ||
		    (flags & BNXT_FLAG_TPA) == 0 ||
		    (bp->flags & BNXT_FLAG_CHIP_P5))
			re_init = true;
	पूर्ण

	अगर (changes & ~BNXT_FLAG_TPA)
		re_init = true;

	अगर (flags != bp->flags) अणु
		u32 old_flags = bp->flags;

		अगर (!test_bit(BNXT_STATE_OPEN, &bp->state)) अणु
			bp->flags = flags;
			अगर (update_tpa)
				bnxt_set_ring_params(bp);
			वापस rc;
		पूर्ण

		अगर (re_init) अणु
			bnxt_बंद_nic(bp, false, false);
			bp->flags = flags;
			अगर (update_tpa)
				bnxt_set_ring_params(bp);

			वापस bnxt_खोलो_nic(bp, false, false);
		पूर्ण
		अगर (update_tpa) अणु
			bp->flags = flags;
			rc = bnxt_set_tpa(bp,
					  (flags & BNXT_FLAG_TPA) ?
					  true : false);
			अगर (rc)
				bp->flags = old_flags;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल bool bnxt_exthdr_check(काष्ठा bnxt *bp, काष्ठा sk_buff *skb, पूर्णांक nw_off,
			      u8 **nextp)
अणु
	काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)(skb->data + nw_off);
	पूर्णांक hdr_count = 0;
	u8 *nexthdr;
	पूर्णांक start;

	/* Check that there are at most 2 IPv6 extension headers, no
	 * fragment header, and each is <= 64 bytes.
	 */
	start = nw_off + माप(*ip6h);
	nexthdr = &ip6h->nexthdr;
	जबतक (ipv6_ext_hdr(*nexthdr)) अणु
		काष्ठा ipv6_opt_hdr *hp;
		पूर्णांक hdrlen;

		अगर (hdr_count >= 3 || *nexthdr == NEXTHDR_NONE ||
		    *nexthdr == NEXTHDR_FRAGMENT)
			वापस false;
		hp = __skb_header_poपूर्णांकer(शून्य, start, माप(*hp), skb->data,
					  skb_headlen(skb), शून्य);
		अगर (!hp)
			वापस false;
		अगर (*nexthdr == NEXTHDR_AUTH)
			hdrlen = ipv6_authlen(hp);
		अन्यथा
			hdrlen = ipv6_optlen(hp);

		अगर (hdrlen > 64)
			वापस false;
		nexthdr = &hp->nexthdr;
		start += hdrlen;
		hdr_count++;
	पूर्ण
	अगर (nextp) अणु
		/* Caller will check inner protocol */
		अगर (skb->encapsulation) अणु
			*nextp = nexthdr;
			वापस true;
		पूर्ण
		*nextp = शून्य;
	पूर्ण
	/* Only support TCP/UDP क्रम non-tunneled ipv6 and inner ipv6 */
	वापस *nexthdr == IPPROTO_TCP || *nexthdr == IPPROTO_UDP;
पूर्ण

/* For UDP, we can only handle 1 Vxlan port and 1 Geneve port. */
अटल bool bnxt_udp_tunl_check(काष्ठा bnxt *bp, काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh = udp_hdr(skb);
	__be16 udp_port = uh->dest;

	अगर (udp_port != bp->vxlan_port && udp_port != bp->nge_port)
		वापस false;
	अगर (skb->inner_protocol_type == ENCAP_TYPE_ETHER) अणु
		काष्ठा ethhdr *eh = inner_eth_hdr(skb);

		चयन (eh->h_proto) अणु
		हाल htons(ETH_P_IP):
			वापस true;
		हाल htons(ETH_P_IPV6):
			वापस bnxt_exthdr_check(bp, skb,
						 skb_inner_network_offset(skb),
						 शून्य);
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool bnxt_tunl_check(काष्ठा bnxt *bp, काष्ठा sk_buff *skb, u8 l4_proto)
अणु
	चयन (l4_proto) अणु
	हाल IPPROTO_UDP:
		वापस bnxt_udp_tunl_check(bp, skb);
	हाल IPPROTO_IPIP:
		वापस true;
	हाल IPPROTO_GRE: अणु
		चयन (skb->inner_protocol) अणु
		शेष:
			वापस false;
		हाल htons(ETH_P_IP):
			वापस true;
		हाल htons(ETH_P_IPV6):
			fallthrough;
		पूर्ण
	पूर्ण
	हाल IPPROTO_IPV6:
		/* Check ext headers of inner ipv6 */
		वापस bnxt_exthdr_check(bp, skb, skb_inner_network_offset(skb),
					 शून्य);
	पूर्ण
	वापस false;
पूर्ण

अटल netdev_features_t bnxt_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	u8 *l4_proto;

	features = vlan_features_check(skb, features);
	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		अगर (!skb->encapsulation)
			वापस features;
		l4_proto = &ip_hdr(skb)->protocol;
		अगर (bnxt_tunl_check(bp, skb, *l4_proto))
			वापस features;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (!bnxt_exthdr_check(bp, skb, skb_network_offset(skb),
				       &l4_proto))
			अवरोध;
		अगर (!l4_proto || bnxt_tunl_check(bp, skb, *l4_proto))
			वापस features;
		अवरोध;
	पूर्ण
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

पूर्णांक bnxt_dbg_hwrm_rd_reg(काष्ठा bnxt *bp, u32 reg_off, u16 num_words,
			 u32 *reg_buf)
अणु
	काष्ठा hwrm_dbg_पढ़ो_direct_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_dbg_पढ़ो_direct_input req = अणु0पूर्ण;
	__le32 *dbg_reg_buf;
	dma_addr_t mapping;
	पूर्णांक rc, i;

	dbg_reg_buf = dma_alloc_coherent(&bp->pdev->dev, num_words * 4,
					 &mapping, GFP_KERNEL);
	अगर (!dbg_reg_buf)
		वापस -ENOMEM;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_READ_सूचीECT, -1, -1);
	req.host_dest_addr = cpu_to_le64(mapping);
	req.पढ़ो_addr = cpu_to_le32(reg_off + CHIMP_REG_VIEW_ADDR);
	req.पढ़ो_len32 = cpu_to_le32(num_words);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc || resp->error_code) अणु
		rc = -EIO;
		जाओ dbg_rd_reg_निकास;
	पूर्ण
	क्रम (i = 0; i < num_words; i++)
		reg_buf[i] = le32_to_cpu(dbg_reg_buf[i]);

dbg_rd_reg_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	dma_मुक्त_coherent(&bp->pdev->dev, num_words * 4, dbg_reg_buf, mapping);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_dbg_hwrm_ring_info_get(काष्ठा bnxt *bp, u8 ring_type,
				       u32 ring_id, u32 *prod, u32 *cons)
अणु
	काष्ठा hwrm_dbg_ring_info_get_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_dbg_ring_info_get_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_RING_INFO_GET, -1, -1);
	req.ring_type = ring_type;
	req.fw_ring_id = cpu_to_le32(ring_id);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		*prod = le32_to_cpu(resp->producer_index);
		*cons = le32_to_cpu(resp->consumer_index);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_dump_tx_sw_state(काष्ठा bnxt_napi *bnapi)
अणु
	काष्ठा bnxt_tx_ring_info *txr = bnapi->tx_ring;
	पूर्णांक i = bnapi->index;

	अगर (!txr)
		वापस;

	netdev_info(bnapi->bp->dev, "[%d]: tx{fw_ring: %d prod: %x cons: %x}\n",
		    i, txr->tx_ring_काष्ठा.fw_ring_id, txr->tx_prod,
		    txr->tx_cons);
पूर्ण

अटल व्योम bnxt_dump_rx_sw_state(काष्ठा bnxt_napi *bnapi)
अणु
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	पूर्णांक i = bnapi->index;

	अगर (!rxr)
		वापस;

	netdev_info(bnapi->bp->dev, "[%d]: rx{fw_ring: %d prod: %x} rx_agg{fw_ring: %d agg_prod: %x sw_agg_prod: %x}\n",
		    i, rxr->rx_ring_काष्ठा.fw_ring_id, rxr->rx_prod,
		    rxr->rx_agg_ring_काष्ठा.fw_ring_id, rxr->rx_agg_prod,
		    rxr->rx_sw_agg_prod);
पूर्ण

अटल व्योम bnxt_dump_cp_sw_state(काष्ठा bnxt_napi *bnapi)
अणु
	काष्ठा bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	पूर्णांक i = bnapi->index;

	netdev_info(bnapi->bp->dev, "[%d]: cp{fw_ring: %d raw_cons: %x}\n",
		    i, cpr->cp_ring_काष्ठा.fw_ring_id, cpr->cp_raw_cons);
पूर्ण

अटल व्योम bnxt_dbg_dump_states(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;
	काष्ठा bnxt_napi *bnapi;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		bnapi = bp->bnapi[i];
		अगर (netअगर_msg_drv(bp)) अणु
			bnxt_dump_tx_sw_state(bnapi);
			bnxt_dump_rx_sw_state(bnapi);
			bnxt_dump_cp_sw_state(bnapi);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_hwrm_rx_ring_reset(काष्ठा bnxt *bp, पूर्णांक ring_nr)
अणु
	काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[ring_nr];
	काष्ठा hwrm_ring_reset_input req = अणु0पूर्ण;
	काष्ठा bnxt_napi *bnapi = rxr->bnapi;
	काष्ठा bnxt_cp_ring_info *cpr;
	u16 cp_ring_id;

	cpr = &bnapi->cp_ring;
	cp_ring_id = cpr->cp_ring_काष्ठा.fw_ring_id;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_RESET, cp_ring_id, -1);
	req.ring_type = RING_RESET_REQ_RING_TYPE_RX_RING_GRP;
	req.ring_id = cpu_to_le16(bp->grp_info[bnapi->index].fw_grp_id);
	वापस hwrm_send_message_silent(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
पूर्ण

अटल व्योम bnxt_reset_task(काष्ठा bnxt *bp, bool silent)
अणु
	अगर (!silent)
		bnxt_dbg_dump_states(bp);
	अगर (netअगर_running(bp->dev)) अणु
		पूर्णांक rc;

		अगर (silent) अणु
			bnxt_बंद_nic(bp, false, false);
			bnxt_खोलो_nic(bp, false, false);
		पूर्ण अन्यथा अणु
			bnxt_ulp_stop(bp);
			bnxt_बंद_nic(bp, true, false);
			rc = bnxt_खोलो_nic(bp, true, false);
			bnxt_ulp_start(bp, rc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	netdev_err(bp->dev,  "TX timeout detected, starting reset task!\n");
	set_bit(BNXT_RESET_TASK_SP_EVENT, &bp->sp_event);
	bnxt_queue_sp_work(bp);
पूर्ण

अटल व्योम bnxt_fw_health_check(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 val;

	अगर (!fw_health->enabled || test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
		वापस;

	अगर (fw_health->पंचांगr_counter) अणु
		fw_health->पंचांगr_counter--;
		वापस;
	पूर्ण

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEARTBEAT_REG);
	अगर (val == fw_health->last_fw_heartbeat)
		जाओ fw_reset;

	fw_health->last_fw_heartbeat = val;

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_RESET_CNT_REG);
	अगर (val != fw_health->last_fw_reset_cnt)
		जाओ fw_reset;

	fw_health->पंचांगr_counter = fw_health->पंचांगr_multiplier;
	वापस;

fw_reset:
	set_bit(BNXT_FW_EXCEPTION_SP_EVENT, &bp->sp_event);
	bnxt_queue_sp_work(bp);
पूर्ण

अटल व्योम bnxt_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bnxt *bp = from_समयr(bp, t, समयr);
	काष्ठा net_device *dev = bp->dev;

	अगर (!netअगर_running(dev) || !test_bit(BNXT_STATE_OPEN, &bp->state))
		वापस;

	अगर (atomic_पढ़ो(&bp->पूर्णांकr_sem) != 0)
		जाओ bnxt_restart_समयr;

	अगर (bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY)
		bnxt_fw_health_check(bp);

	अगर (bp->link_info.link_up && bp->stats_coal_ticks) अणु
		set_bit(BNXT_PERIODIC_STATS_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण

	अगर (bnxt_tc_flower_enabled(bp)) अणु
		set_bit(BNXT_FLOW_STATS_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर ((bp->flags & BNXT_FLAG_RFS) && bp->ntp_fltr_count) अणु
		set_bit(BNXT_RX_NTP_FLTR_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण
#पूर्ण_अगर /*CONFIG_RFS_ACCEL*/

	अगर (bp->link_info.phy_retry) अणु
		अगर (समय_after(jअगरfies, bp->link_info.phy_retry_expires)) अणु
			bp->link_info.phy_retry = false;
			netdev_warn(bp->dev, "failed to update phy settings after maximum retries.\n");
		पूर्ण अन्यथा अणु
			set_bit(BNXT_UPDATE_PHY_SP_EVENT, &bp->sp_event);
			bnxt_queue_sp_work(bp);
		पूर्ण
	पूर्ण

	अगर ((bp->flags & BNXT_FLAG_CHIP_P5) && !bp->chip_rev &&
	    netअगर_carrier_ok(dev)) अणु
		set_bit(BNXT_RING_COAL_NOW_SP_EVENT, &bp->sp_event);
		bnxt_queue_sp_work(bp);
	पूर्ण
bnxt_restart_समयr:
	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
पूर्ण

अटल व्योम bnxt_rtnl_lock_sp(काष्ठा bnxt *bp)
अणु
	/* We are called from bnxt_sp_task which has BNXT_STATE_IN_SP_TASK
	 * set.  If the device is being बंदd, bnxt_बंद() may be holding
	 * rtnl() and रुकोing क्रम BNXT_STATE_IN_SP_TASK to clear.  So we
	 * must clear BNXT_STATE_IN_SP_TASK beक्रमe holding rtnl().
	 */
	clear_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
	rtnl_lock();
पूर्ण

अटल व्योम bnxt_rtnl_unlock_sp(काष्ठा bnxt *bp)
अणु
	set_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
	rtnl_unlock();
पूर्ण

/* Only called from bnxt_sp_task() */
अटल व्योम bnxt_reset(काष्ठा bnxt *bp, bool silent)
अणु
	bnxt_rtnl_lock_sp(bp);
	अगर (test_bit(BNXT_STATE_OPEN, &bp->state))
		bnxt_reset_task(bp, silent);
	bnxt_rtnl_unlock_sp(bp);
पूर्ण

/* Only called from bnxt_sp_task() */
अटल व्योम bnxt_rx_ring_reset(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	bnxt_rtnl_lock_sp(bp);
	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state)) अणु
		bnxt_rtnl_unlock_sp(bp);
		वापस;
	पूर्ण
	/* Disable and flush TPA beक्रमe resetting the RX ring */
	अगर (bp->flags & BNXT_FLAG_TPA)
		bnxt_set_tpa(bp, false);
	क्रम (i = 0; i < bp->rx_nr_rings; i++) अणु
		काष्ठा bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		पूर्णांक rc;

		अगर (!rxr->bnapi->in_reset)
			जारी;

		rc = bnxt_hwrm_rx_ring_reset(bp, i);
		अगर (rc) अणु
			अगर (rc == -EINVAL || rc == -EOPNOTSUPP)
				netdev_info_once(bp->dev, "RX ring reset not supported by firmware, falling back to global reset\n");
			अन्यथा
				netdev_warn(bp->dev, "RX ring reset failed, rc = %d, falling back to global reset\n",
					    rc);
			bnxt_reset_task(bp, true);
			अवरोध;
		पूर्ण
		bnxt_मुक्त_one_rx_ring_skbs(bp, i);
		rxr->rx_prod = 0;
		rxr->rx_agg_prod = 0;
		rxr->rx_sw_agg_prod = 0;
		rxr->rx_next_cons = 0;
		rxr->bnapi->in_reset = false;
		bnxt_alloc_one_rx_ring(bp, i);
		cpr = &rxr->bnapi->cp_ring;
		cpr->sw_stats.rx.rx_resets++;
		अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
			bnxt_db_ग_लिखो(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);
		bnxt_db_ग_लिखो(bp, &rxr->rx_db, rxr->rx_prod);
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_TPA)
		bnxt_set_tpa(bp, true);
	bnxt_rtnl_unlock_sp(bp);
पूर्ण

अटल व्योम bnxt_fw_reset_बंद(काष्ठा bnxt *bp)
अणु
	bnxt_ulp_stop(bp);
	/* When firmware is in fatal state, quiesce device and disable
	 * bus master to prevent any potential bad DMAs beक्रमe मुक्तing
	 * kernel memory.
	 */
	अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state)) अणु
		u16 val = 0;

		pci_पढ़ो_config_word(bp->pdev, PCI_SUBSYSTEM_ID, &val);
		अगर (val == 0xffff)
			bp->fw_reset_min_dsecs = 0;
		bnxt_tx_disable(bp);
		bnxt_disable_napi(bp);
		bnxt_disable_पूर्णांक_sync(bp);
		bnxt_मुक्त_irq(bp);
		bnxt_clear_पूर्णांक_mode(bp);
		pci_disable_device(bp->pdev);
	पूर्ण
	__bnxt_बंद_nic(bp, true, false);
	bnxt_vf_reps_मुक्त(bp);
	bnxt_clear_पूर्णांक_mode(bp);
	bnxt_hwrm_func_drv_unrgtr(bp);
	अगर (pci_is_enabled(bp->pdev))
		pci_disable_device(bp->pdev);
	bnxt_मुक्त_ctx_mem(bp);
	kमुक्त(bp->ctx);
	bp->ctx = शून्य;
पूर्ण

अटल bool is_bnxt_fw_ok(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	bool no_heartbeat = false, has_reset = false;
	u32 val;

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEARTBEAT_REG);
	अगर (val == fw_health->last_fw_heartbeat)
		no_heartbeat = true;

	val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_RESET_CNT_REG);
	अगर (val != fw_health->last_fw_reset_cnt)
		has_reset = true;

	अगर (!no_heartbeat && has_reset)
		वापस true;

	वापस false;
पूर्ण

/* rtnl_lock is acquired beक्रमe calling this function */
अटल व्योम bnxt_क्रमce_fw_reset(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 रुको_dsecs;

	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state) ||
	    test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
		वापस;

	set_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
	bnxt_fw_reset_बंद(bp);
	रुको_dsecs = fw_health->master_func_रुको_dsecs;
	अगर (fw_health->master) अणु
		अगर (fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU)
			रुको_dsecs = 0;
		bp->fw_reset_state = BNXT_FW_RESET_STATE_RESET_FW;
	पूर्ण अन्यथा अणु
		bp->fw_reset_बारtamp = jअगरfies + रुको_dsecs * HZ / 10;
		रुको_dsecs = fw_health->normal_func_रुको_dsecs;
		bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
	पूर्ण

	bp->fw_reset_min_dsecs = fw_health->post_reset_रुको_dsecs;
	bp->fw_reset_max_dsecs = fw_health->post_reset_max_रुको_dsecs;
	bnxt_queue_fw_reset_work(bp, रुको_dsecs * HZ / 10);
पूर्ण

व्योम bnxt_fw_exception(काष्ठा bnxt *bp)
अणु
	netdev_warn(bp->dev, "Detected firmware fatal condition, initiating reset\n");
	set_bit(BNXT_STATE_FW_FATAL_COND, &bp->state);
	bnxt_rtnl_lock_sp(bp);
	bnxt_क्रमce_fw_reset(bp);
	bnxt_rtnl_unlock_sp(bp);
पूर्ण

/* Returns the number of रेजिस्टरed VFs, or 1 अगर VF configuration is pending, or
 * < 0 on error.
 */
अटल पूर्णांक bnxt_get_रेजिस्टरed_vfs(काष्ठा bnxt *bp)
अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
	पूर्णांक rc;

	अगर (!BNXT_PF(bp))
		वापस 0;

	rc = bnxt_hwrm_func_qcfg(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "func_qcfg cmd failed, rc = %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (bp->pf.रेजिस्टरed_vfs)
		वापस bp->pf.रेजिस्टरed_vfs;
	अगर (bp->sriov_cfg)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम bnxt_fw_reset(काष्ठा bnxt *bp)
अणु
	bnxt_rtnl_lock_sp(bp);
	अगर (test_bit(BNXT_STATE_OPEN, &bp->state) &&
	    !test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) अणु
		पूर्णांक n = 0, पंचांगo;

		set_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
		अगर (bp->pf.active_vfs &&
		    !test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
			n = bnxt_get_रेजिस्टरed_vfs(bp);
		अगर (n < 0) अणु
			netdev_err(bp->dev, "Firmware reset aborted, rc = %d\n",
				   n);
			clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
			dev_बंद(bp->dev);
			जाओ fw_reset_निकास;
		पूर्ण अन्यथा अगर (n > 0) अणु
			u16 vf_पंचांगo_dsecs = n * 10;

			अगर (bp->fw_reset_max_dsecs < vf_पंचांगo_dsecs)
				bp->fw_reset_max_dsecs = vf_पंचांगo_dsecs;
			bp->fw_reset_state =
				BNXT_FW_RESET_STATE_POLL_VF;
			bnxt_queue_fw_reset_work(bp, HZ / 10);
			जाओ fw_reset_निकास;
		पूर्ण
		bnxt_fw_reset_बंद(bp);
		अगर (bp->fw_cap & BNXT_FW_CAP_ERR_RECOVER_RELOAD) अणु
			bp->fw_reset_state = BNXT_FW_RESET_STATE_POLL_FW_DOWN;
			पंचांगo = HZ / 10;
		पूर्ण अन्यथा अणु
			bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
			पंचांगo = bp->fw_reset_min_dsecs * HZ / 10;
		पूर्ण
		bnxt_queue_fw_reset_work(bp, पंचांगo);
	पूर्ण
fw_reset_निकास:
	bnxt_rtnl_unlock_sp(bp);
पूर्ण

अटल व्योम bnxt_chk_missed_irq(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		वापस;

	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_napi *bnapi = bp->bnapi[i];
		काष्ठा bnxt_cp_ring_info *cpr;
		u32 fw_ring_id;
		पूर्णांक j;

		अगर (!bnapi)
			जारी;

		cpr = &bnapi->cp_ring;
		क्रम (j = 0; j < 2; j++) अणु
			काष्ठा bnxt_cp_ring_info *cpr2 = cpr->cp_ring_arr[j];
			u32 val[2];

			अगर (!cpr2 || cpr2->has_more_work ||
			    !bnxt_has_work(bp, cpr2))
				जारी;

			अगर (cpr2->cp_raw_cons != cpr2->last_cp_raw_cons) अणु
				cpr2->last_cp_raw_cons = cpr2->cp_raw_cons;
				जारी;
			पूर्ण
			fw_ring_id = cpr2->cp_ring_काष्ठा.fw_ring_id;
			bnxt_dbg_hwrm_ring_info_get(bp,
				DBG_RING_INFO_GET_REQ_RING_TYPE_L2_CMPL,
				fw_ring_id, &val[0], &val[1]);
			cpr->sw_stats.cmn.missed_irqs++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_cfg_ntp_filters(काष्ठा bnxt *);

अटल व्योम bnxt_init_ethtool_link_settings(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	अगर (BNXT_AUTO_MODE(link_info->स्वतः_mode)) अणु
		link_info->स्वतःneg = BNXT_AUTONEG_SPEED;
		अगर (bp->hwrm_spec_code >= 0x10201) अणु
			अगर (link_info->स्वतः_छोड़ो_setting &
			    PORT_PHY_CFG_REQ_AUTO_PAUSE_AUTONEG_PAUSE)
				link_info->स्वतःneg |= BNXT_AUTONEG_FLOW_CTRL;
		पूर्ण अन्यथा अणु
			link_info->स्वतःneg |= BNXT_AUTONEG_FLOW_CTRL;
		पूर्ण
		link_info->advertising = link_info->स्वतः_link_speeds;
		link_info->advertising_pam4 = link_info->स्वतः_pam4_link_speeds;
	पूर्ण अन्यथा अणु
		link_info->req_link_speed = link_info->क्रमce_link_speed;
		link_info->req_संकेत_mode = BNXT_SIG_MODE_NRZ;
		अगर (link_info->क्रमce_pam4_link_speed) अणु
			link_info->req_link_speed =
				link_info->क्रमce_pam4_link_speed;
			link_info->req_संकेत_mode = BNXT_SIG_MODE_PAM4;
		पूर्ण
		link_info->req_duplex = link_info->duplex_setting;
	पूर्ण
	अगर (link_info->स्वतःneg & BNXT_AUTONEG_FLOW_CTRL)
		link_info->req_flow_ctrl =
			link_info->स्वतः_छोड़ो_setting & BNXT_LINK_PAUSE_BOTH;
	अन्यथा
		link_info->req_flow_ctrl = link_info->क्रमce_छोड़ो_setting;
पूर्ण

अटल व्योम bnxt_fw_echo_reply(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	काष्ठा hwrm_func_echo_response_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_ECHO_RESPONSE, -1, -1);
	req.event_data1 = cpu_to_le32(fw_health->echo_req_data1);
	req.event_data2 = cpu_to_le32(fw_health->echo_req_data2);
	hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

अटल व्योम bnxt_sp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnxt *bp = container_of(work, काष्ठा bnxt, sp_task);

	set_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
	smp_mb__after_atomic();
	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state)) अणु
		clear_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(BNXT_RX_MASK_SP_EVENT, &bp->sp_event))
		bnxt_cfg_rx_mode(bp);

	अगर (test_and_clear_bit(BNXT_RX_NTP_FLTR_SP_EVENT, &bp->sp_event))
		bnxt_cfg_ntp_filters(bp);
	अगर (test_and_clear_bit(BNXT_HWRM_EXEC_FWD_REQ_SP_EVENT, &bp->sp_event))
		bnxt_hwrm_exec_fwd_req(bp);
	अगर (test_and_clear_bit(BNXT_PERIODIC_STATS_SP_EVENT, &bp->sp_event)) अणु
		bnxt_hwrm_port_qstats(bp, 0);
		bnxt_hwrm_port_qstats_ext(bp, 0);
		bnxt_accumulate_all_stats(bp);
	पूर्ण

	अगर (test_and_clear_bit(BNXT_LINK_CHNG_SP_EVENT, &bp->sp_event)) अणु
		पूर्णांक rc;

		mutex_lock(&bp->link_lock);
		अगर (test_and_clear_bit(BNXT_LINK_SPEED_CHNG_SP_EVENT,
				       &bp->sp_event))
			bnxt_hwrm_phy_qcaps(bp);

		rc = bnxt_update_link(bp, true);
		अगर (rc)
			netdev_err(bp->dev, "SP task can't update link (rc: %x)\n",
				   rc);

		अगर (test_and_clear_bit(BNXT_LINK_CFG_CHANGE_SP_EVENT,
				       &bp->sp_event))
			bnxt_init_ethtool_link_settings(bp);
		mutex_unlock(&bp->link_lock);
	पूर्ण
	अगर (test_and_clear_bit(BNXT_UPDATE_PHY_SP_EVENT, &bp->sp_event)) अणु
		पूर्णांक rc;

		mutex_lock(&bp->link_lock);
		rc = bnxt_update_phy_setting(bp);
		mutex_unlock(&bp->link_lock);
		अगर (rc) अणु
			netdev_warn(bp->dev, "update phy settings retry failed\n");
		पूर्ण अन्यथा अणु
			bp->link_info.phy_retry = false;
			netdev_info(bp->dev, "update phy settings retry succeeded\n");
		पूर्ण
	पूर्ण
	अगर (test_and_clear_bit(BNXT_HWRM_PORT_MODULE_SP_EVENT, &bp->sp_event)) अणु
		mutex_lock(&bp->link_lock);
		bnxt_get_port_module_status(bp);
		mutex_unlock(&bp->link_lock);
	पूर्ण

	अगर (test_and_clear_bit(BNXT_FLOW_STATS_SP_EVENT, &bp->sp_event))
		bnxt_tc_flow_stats_work(bp);

	अगर (test_and_clear_bit(BNXT_RING_COAL_NOW_SP_EVENT, &bp->sp_event))
		bnxt_chk_missed_irq(bp);

	अगर (test_and_clear_bit(BNXT_FW_ECHO_REQUEST_SP_EVENT, &bp->sp_event))
		bnxt_fw_echo_reply(bp);

	/* These functions below will clear BNXT_STATE_IN_SP_TASK.  They
	 * must be the last functions to be called beक्रमe निकासing.
	 */
	अगर (test_and_clear_bit(BNXT_RESET_TASK_SP_EVENT, &bp->sp_event))
		bnxt_reset(bp, false);

	अगर (test_and_clear_bit(BNXT_RESET_TASK_SILENT_SP_EVENT, &bp->sp_event))
		bnxt_reset(bp, true);

	अगर (test_and_clear_bit(BNXT_RST_RING_SP_EVENT, &bp->sp_event))
		bnxt_rx_ring_reset(bp);

	अगर (test_and_clear_bit(BNXT_FW_RESET_NOTIFY_SP_EVENT, &bp->sp_event))
		bnxt_devlink_health_report(bp, BNXT_FW_RESET_NOTIFY_SP_EVENT);

	अगर (test_and_clear_bit(BNXT_FW_EXCEPTION_SP_EVENT, &bp->sp_event)) अणु
		अगर (!is_bnxt_fw_ok(bp))
			bnxt_devlink_health_report(bp,
						   BNXT_FW_EXCEPTION_SP_EVENT);
	पूर्ण

	smp_mb__beक्रमe_atomic();
	clear_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
पूर्ण

/* Under rtnl_lock */
पूर्णांक bnxt_check_rings(काष्ठा bnxt *bp, पूर्णांक tx, पूर्णांक rx, bool sh, पूर्णांक tcs,
		     पूर्णांक tx_xdp)
अणु
	पूर्णांक max_rx, max_tx, tx_sets = 1;
	पूर्णांक tx_rings_needed, stats;
	पूर्णांक rx_rings = rx;
	पूर्णांक cp, vnics, rc;

	अगर (tcs)
		tx_sets = tcs;

	rc = bnxt_get_max_rings(bp, &max_rx, &max_tx, sh);
	अगर (rc)
		वापस rc;

	अगर (max_rx < rx)
		वापस -ENOMEM;

	tx_rings_needed = tx * tx_sets + tx_xdp;
	अगर (max_tx < tx_rings_needed)
		वापस -ENOMEM;

	vnics = 1;
	अगर ((bp->flags & (BNXT_FLAG_RFS | BNXT_FLAG_CHIP_P5)) == BNXT_FLAG_RFS)
		vnics += rx_rings;

	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx_rings <<= 1;
	cp = sh ? max_t(पूर्णांक, tx_rings_needed, rx) : tx_rings_needed + rx;
	stats = cp;
	अगर (BNXT_NEW_RM(bp)) अणु
		cp += bnxt_get_ulp_msix_num(bp);
		stats += bnxt_get_ulp_stat_ctxs(bp);
	पूर्ण
	वापस bnxt_hwrm_check_rings(bp, tx_rings_needed, rx_rings, rx, cp,
				     stats, vnics);
पूर्ण

अटल व्योम bnxt_unmap_bars(काष्ठा bnxt *bp, काष्ठा pci_dev *pdev)
अणु
	अगर (bp->bar2) अणु
		pci_iounmap(pdev, bp->bar2);
		bp->bar2 = शून्य;
	पूर्ण

	अगर (bp->bar1) अणु
		pci_iounmap(pdev, bp->bar1);
		bp->bar1 = शून्य;
	पूर्ण

	अगर (bp->bar0) अणु
		pci_iounmap(pdev, bp->bar0);
		bp->bar0 = शून्य;
	पूर्ण
पूर्ण

अटल व्योम bnxt_cleanup_pci(काष्ठा bnxt *bp)
अणु
	bnxt_unmap_bars(bp, bp->pdev);
	pci_release_regions(bp->pdev);
	अगर (pci_is_enabled(bp->pdev))
		pci_disable_device(bp->pdev);
पूर्ण

अटल व्योम bnxt_init_dflt_coal(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_coal *coal;

	/* Tick values in micro seconds.
	 * 1 coal_buf x bufs_per_record = 1 completion record.
	 */
	coal = &bp->rx_coal;
	coal->coal_ticks = 10;
	coal->coal_bufs = 30;
	coal->coal_ticks_irq = 1;
	coal->coal_bufs_irq = 2;
	coal->idle_thresh = 50;
	coal->bufs_per_record = 2;
	coal->budget = 64;		/* NAPI budget */

	coal = &bp->tx_coal;
	coal->coal_ticks = 28;
	coal->coal_bufs = 30;
	coal->coal_ticks_irq = 2;
	coal->coal_bufs_irq = 2;
	coal->bufs_per_record = 1;

	bp->stats_coal_ticks = BNXT_DEF_STATS_COAL_TICKS;
पूर्ण

अटल पूर्णांक bnxt_fw_init_one_p1(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	bp->fw_cap = 0;
	rc = bnxt_hwrm_ver_get(bp);
	bnxt_try_map_fw_health_reg(bp);
	अगर (rc) अणु
		rc = bnxt_try_recover_fw(bp);
		अगर (rc)
			वापस rc;
		rc = bnxt_hwrm_ver_get(bp);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL) अणु
		rc = bnxt_alloc_kong_hwrm_resources(bp);
		अगर (rc)
			bp->fw_cap &= ~BNXT_FW_CAP_KONG_MB_CHNL;
	पूर्ण

	अगर ((bp->fw_cap & BNXT_FW_CAP_SHORT_CMD) ||
	    bp->hwrm_max_ext_req_len > BNXT_HWRM_MAX_REQ_LEN) अणु
		rc = bnxt_alloc_hwrm_लघु_cmd_req(bp);
		अगर (rc)
			वापस rc;
	पूर्ण
	bnxt_nvm_cfg_ver_get(bp);

	rc = bnxt_hwrm_func_reset(bp);
	अगर (rc)
		वापस -ENODEV;

	bnxt_hwrm_fw_set_समय(bp);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_fw_init_one_p2(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	/* Get the MAX capabilities क्रम this function */
	rc = bnxt_hwrm_func_qcaps(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "hwrm query capability failure rc: %x\n",
			   rc);
		वापस -ENODEV;
	पूर्ण

	rc = bnxt_hwrm_cfa_adv_flow_mgnt_qcaps(bp);
	अगर (rc)
		netdev_warn(bp->dev, "hwrm query adv flow mgnt failure rc: %d\n",
			    rc);

	अगर (bnxt_alloc_fw_health(bp)) अणु
		netdev_warn(bp->dev, "no memory for firmware error recovery\n");
	पूर्ण अन्यथा अणु
		rc = bnxt_hwrm_error_recovery_qcfg(bp);
		अगर (rc)
			netdev_warn(bp->dev, "hwrm query error recovery failure rc: %d\n",
				    rc);
	पूर्ण

	rc = bnxt_hwrm_func_drv_rgtr(bp, शून्य, 0, false);
	अगर (rc)
		वापस -ENODEV;

	bnxt_hwrm_func_qcfg(bp);
	bnxt_hwrm_vnic_qcaps(bp);
	bnxt_hwrm_port_led_qcaps(bp);
	bnxt_ethtool_init(bp);
	bnxt_dcb_init(bp);
	वापस 0;
पूर्ण

अटल व्योम bnxt_set_dflt_rss_hash_type(काष्ठा bnxt *bp)
अणु
	bp->flags &= ~BNXT_FLAG_UDP_RSS_CAP;
	bp->rss_hash_cfg = VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
	अगर (BNXT_CHIP_P4_PLUS(bp) && bp->hwrm_spec_code >= 0x10501) अणु
		bp->flags |= BNXT_FLAG_UDP_RSS_CAP;
		bp->rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4 |
				    VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
	पूर्ण
पूर्ण

अटल व्योम bnxt_set_dflt_rfs(काष्ठा bnxt *bp)
अणु
	काष्ठा net_device *dev = bp->dev;

	dev->hw_features &= ~NETIF_F_NTUPLE;
	dev->features &= ~NETIF_F_NTUPLE;
	bp->flags &= ~BNXT_FLAG_RFS;
	अगर (bnxt_rfs_supported(bp)) अणु
		dev->hw_features |= NETIF_F_NTUPLE;
		अगर (bnxt_rfs_capable(bp)) अणु
			bp->flags |= BNXT_FLAG_RFS;
			dev->features |= NETIF_F_NTUPLE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_fw_init_one_p3(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;

	bnxt_set_dflt_rss_hash_type(bp);
	bnxt_set_dflt_rfs(bp);

	bnxt_get_wol_settings(bp);
	अगर (bp->flags & BNXT_FLAG_WOL_CAP)
		device_set_wakeup_enable(&pdev->dev, bp->wol);
	अन्यथा
		device_set_wakeup_capable(&pdev->dev, false);

	bnxt_hwrm_set_cache_line_size(bp, cache_line_size());
	bnxt_hwrm_coal_params_qcaps(bp);
पूर्ण

अटल पूर्णांक bnxt_probe_phy(काष्ठा bnxt *bp, bool fw_dflt);

अटल पूर्णांक bnxt_fw_init_one(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	rc = bnxt_fw_init_one_p1(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "Firmware init phase 1 failed\n");
		वापस rc;
	पूर्ण
	rc = bnxt_fw_init_one_p2(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "Firmware init phase 2 failed\n");
		वापस rc;
	पूर्ण
	rc = bnxt_probe_phy(bp, false);
	अगर (rc)
		वापस rc;
	rc = bnxt_approve_mac(bp, bp->dev->dev_addr, false);
	अगर (rc)
		वापस rc;

	/* In हाल fw capabilities have changed, destroy the unneeded
	 * reporters and create newly capable ones.
	 */
	bnxt_dl_fw_reporters_destroy(bp, false);
	bnxt_dl_fw_reporters_create(bp);
	bnxt_fw_init_one_p3(bp);
	वापस 0;
पूर्ण

अटल व्योम bnxt_fw_reset_ग_लिखोl(काष्ठा bnxt *bp, पूर्णांक reg_idx)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	u32 reg = fw_health->fw_reset_seq_regs[reg_idx];
	u32 val = fw_health->fw_reset_seq_vals[reg_idx];
	u32 reg_type, reg_off, delay_msecs;

	delay_msecs = fw_health->fw_reset_seq_delay_msec[reg_idx];
	reg_type = BNXT_FW_HEALTH_REG_TYPE(reg);
	reg_off = BNXT_FW_HEALTH_REG_OFF(reg);
	चयन (reg_type) अणु
	हाल BNXT_FW_HEALTH_REG_TYPE_CFG:
		pci_ग_लिखो_config_dword(bp->pdev, reg_off, val);
		अवरोध;
	हाल BNXT_FW_HEALTH_REG_TYPE_GRC:
		ग_लिखोl(reg_off & BNXT_GRC_BASE_MASK,
		       bp->bar0 + BNXT_GRCPF_REG_WINDOW_BASE_OUT + 4);
		reg_off = (reg_off & BNXT_GRC_OFFSET_MASK) + 0x2000;
		fallthrough;
	हाल BNXT_FW_HEALTH_REG_TYPE_BAR0:
		ग_लिखोl(val, bp->bar0 + reg_off);
		अवरोध;
	हाल BNXT_FW_HEALTH_REG_TYPE_BAR1:
		ग_लिखोl(val, bp->bar1 + reg_off);
		अवरोध;
	पूर्ण
	अगर (delay_msecs) अणु
		pci_पढ़ो_config_dword(bp->pdev, 0, &val);
		msleep(delay_msecs);
	पूर्ण
पूर्ण

अटल व्योम bnxt_reset_all(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_fw_health *fw_health = bp->fw_health;
	पूर्णांक i, rc;

	अगर (bp->fw_cap & BNXT_FW_CAP_ERR_RECOVER_RELOAD) अणु
		bnxt_fw_reset_via_optee(bp);
		bp->fw_reset_बारtamp = jअगरfies;
		वापस;
	पूर्ण

	अगर (fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_HOST) अणु
		क्रम (i = 0; i < fw_health->fw_reset_seq_cnt; i++)
			bnxt_fw_reset_ग_लिखोl(bp, i);
	पूर्ण अन्यथा अगर (fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU) अणु
		काष्ठा hwrm_fw_reset_input req = अणु0पूर्ण;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_RESET, -1, -1);
		req.resp_addr = cpu_to_le64(bp->hwrm_cmd_kong_resp_dma_addr);
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP;
		req.selfrst_status = FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP;
		req.flags = FW_RESET_REQ_FLAGS_RESET_GRACEFUL;
		rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
		अगर (rc != -ENODEV)
			netdev_warn(bp->dev, "Unable to reset FW rc=%d\n", rc);
	पूर्ण
	bp->fw_reset_बारtamp = jअगरfies;
पूर्ण

अटल bool bnxt_fw_reset_समयout(काष्ठा bnxt *bp)
अणु
	वापस समय_after(jअगरfies, bp->fw_reset_बारtamp +
			  (bp->fw_reset_max_dsecs * HZ / 10));
पूर्ण

अटल व्योम bnxt_fw_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnxt *bp = container_of(work, काष्ठा bnxt, fw_reset_task.work);
	पूर्णांक rc;

	अगर (!test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) अणु
		netdev_err(bp->dev, "bnxt_fw_reset_task() called when not in fw reset mode!\n");
		वापस;
	पूर्ण

	चयन (bp->fw_reset_state) अणु
	हाल BNXT_FW_RESET_STATE_POLL_VF: अणु
		पूर्णांक n = bnxt_get_रेजिस्टरed_vfs(bp);
		पूर्णांक पंचांगo;

		अगर (n < 0) अणु
			netdev_err(bp->dev, "Firmware reset aborted, subsequent func_qcfg cmd failed, rc = %d, %d msecs since reset timestamp\n",
				   n, jअगरfies_to_msecs(jअगरfies -
				   bp->fw_reset_बारtamp));
			जाओ fw_reset_पात;
		पूर्ण अन्यथा अगर (n > 0) अणु
			अगर (bnxt_fw_reset_समयout(bp)) अणु
				clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
				bp->fw_reset_state = 0;
				netdev_err(bp->dev, "Firmware reset aborted, bnxt_get_registered_vfs() returns %d\n",
					   n);
				वापस;
			पूर्ण
			bnxt_queue_fw_reset_work(bp, HZ / 10);
			वापस;
		पूर्ण
		bp->fw_reset_बारtamp = jअगरfies;
		rtnl_lock();
		bnxt_fw_reset_बंद(bp);
		अगर (bp->fw_cap & BNXT_FW_CAP_ERR_RECOVER_RELOAD) अणु
			bp->fw_reset_state = BNXT_FW_RESET_STATE_POLL_FW_DOWN;
			पंचांगo = HZ / 10;
		पूर्ण अन्यथा अणु
			bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
			पंचांगo = bp->fw_reset_min_dsecs * HZ / 10;
		पूर्ण
		rtnl_unlock();
		bnxt_queue_fw_reset_work(bp, पंचांगo);
		वापस;
	पूर्ण
	हाल BNXT_FW_RESET_STATE_POLL_FW_DOWN: अणु
		u32 val;

		val = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG);
		अगर (!(val & BNXT_FW_STATUS_SHUTDOWN) &&
		    !bnxt_fw_reset_समयout(bp)) अणु
			bnxt_queue_fw_reset_work(bp, HZ / 5);
			वापस;
		पूर्ण

		अगर (!bp->fw_health->master) अणु
			u32 रुको_dsecs = bp->fw_health->normal_func_रुको_dsecs;

			bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
			bnxt_queue_fw_reset_work(bp, रुको_dsecs * HZ / 10);
			वापस;
		पूर्ण
		bp->fw_reset_state = BNXT_FW_RESET_STATE_RESET_FW;
	पूर्ण
		fallthrough;
	हाल BNXT_FW_RESET_STATE_RESET_FW:
		bnxt_reset_all(bp);
		bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
		bnxt_queue_fw_reset_work(bp, bp->fw_reset_min_dsecs * HZ / 10);
		वापस;
	हाल BNXT_FW_RESET_STATE_ENABLE_DEV:
		bnxt_inv_fw_health_reg(bp);
		अगर (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state) &&
		    !bp->fw_reset_min_dsecs) अणु
			u16 val;

			pci_पढ़ो_config_word(bp->pdev, PCI_SUBSYSTEM_ID, &val);
			अगर (val == 0xffff) अणु
				अगर (bnxt_fw_reset_समयout(bp)) अणु
					netdev_err(bp->dev, "Firmware reset aborted, PCI config space invalid\n");
					जाओ fw_reset_पात;
				पूर्ण
				bnxt_queue_fw_reset_work(bp, HZ / 1000);
				वापस;
			पूर्ण
		पूर्ण
		clear_bit(BNXT_STATE_FW_FATAL_COND, &bp->state);
		अगर (pci_enable_device(bp->pdev)) अणु
			netdev_err(bp->dev, "Cannot re-enable PCI device\n");
			जाओ fw_reset_पात;
		पूर्ण
		pci_set_master(bp->pdev);
		bp->fw_reset_state = BNXT_FW_RESET_STATE_POLL_FW;
		fallthrough;
	हाल BNXT_FW_RESET_STATE_POLL_FW:
		bp->hwrm_cmd_समयout = SHORT_HWRM_CMD_TIMEOUT;
		rc = __bnxt_hwrm_ver_get(bp, true);
		अगर (rc) अणु
			अगर (bnxt_fw_reset_समयout(bp)) अणु
				netdev_err(bp->dev, "Firmware reset aborted\n");
				जाओ fw_reset_पात_status;
			पूर्ण
			bnxt_queue_fw_reset_work(bp, HZ / 5);
			वापस;
		पूर्ण
		bp->hwrm_cmd_समयout = DFLT_HWRM_CMD_TIMEOUT;
		bp->fw_reset_state = BNXT_FW_RESET_STATE_OPENING;
		fallthrough;
	हाल BNXT_FW_RESET_STATE_OPENING:
		जबतक (!rtnl_trylock()) अणु
			bnxt_queue_fw_reset_work(bp, HZ / 10);
			वापस;
		पूर्ण
		rc = bnxt_खोलो(bp->dev);
		अगर (rc) अणु
			netdev_err(bp->dev, "bnxt_open_nic() failed\n");
			clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
			dev_बंद(bp->dev);
		पूर्ण

		bp->fw_reset_state = 0;
		/* Make sure fw_reset_state is 0 beक्रमe clearing the flag */
		smp_mb__beक्रमe_atomic();
		clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
		bnxt_ulp_start(bp, rc);
		अगर (!rc)
			bnxt_reenable_sriov(bp);
		bnxt_vf_reps_alloc(bp);
		bnxt_vf_reps_खोलो(bp);
		bnxt_dl_health_recovery_करोne(bp);
		bnxt_dl_health_status_update(bp, true);
		rtnl_unlock();
		अवरोध;
	पूर्ण
	वापस;

fw_reset_पात_status:
	अगर (bp->fw_health->status_reliable ||
	    (bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY)) अणु
		u32 sts = bnxt_fw_health_पढ़ोl(bp, BNXT_FW_HEALTH_REG);

		netdev_err(bp->dev, "fw_health_status 0x%x\n", sts);
	पूर्ण
fw_reset_पात:
	clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
	अगर (bp->fw_reset_state != BNXT_FW_RESET_STATE_POLL_VF)
		bnxt_dl_health_status_update(bp, false);
	bp->fw_reset_state = 0;
	rtnl_lock();
	dev_बंद(bp->dev);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक bnxt_init_board(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	पूर्णांक rc;
	काष्ठा bnxt *bp = netdev_priv(dev);

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* enable device (incl. PCI PM wakeup), and bus-mastering */
	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		जाओ init_err;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev,
			"Cannot find PCI device base address, aborting\n");
		rc = -ENODEV;
		जाओ init_err_disable;
	पूर्ण

	rc = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		जाओ init_err_disable;
	पूर्ण

	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64)) != 0 &&
	    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)) != 0) अणु
		dev_err(&pdev->dev, "System does not support DMA, aborting\n");
		rc = -EIO;
		जाओ init_err_release;
	पूर्ण

	pci_set_master(pdev);

	bp->dev = dev;
	bp->pdev = pdev;

	/* Doorbell BAR bp->bar1 is mapped after bnxt_fw_init_one_p2()
	 * determines the BAR size.
	 */
	bp->bar0 = pci_ioremap_bar(pdev, 0);
	अगर (!bp->bar0) अणु
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		rc = -ENOMEM;
		जाओ init_err_release;
	पूर्ण

	bp->bar2 = pci_ioremap_bar(pdev, 4);
	अगर (!bp->bar2) अणु
		dev_err(&pdev->dev, "Cannot map bar4 registers, aborting\n");
		rc = -ENOMEM;
		जाओ init_err_release;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);

	INIT_WORK(&bp->sp_task, bnxt_sp_task);
	INIT_DELAYED_WORK(&bp->fw_reset_task, bnxt_fw_reset_task);

	spin_lock_init(&bp->ntp_fltr_lock);
#अगर BITS_PER_LONG == 32
	spin_lock_init(&bp->db_lock);
#पूर्ण_अगर

	bp->rx_ring_size = BNXT_DEFAULT_RX_RING_SIZE;
	bp->tx_ring_size = BNXT_DEFAULT_TX_RING_SIZE;

	bnxt_init_dflt_coal(bp);

	समयr_setup(&bp->समयr, bnxt_समयr, 0);
	bp->current_पूर्णांकerval = BNXT_TIMER_INTERVAL;

	bp->vxlan_fw_dst_port_id = INVALID_HW_RING_ID;
	bp->nge_fw_dst_port_id = INVALID_HW_RING_ID;

	clear_bit(BNXT_STATE_OPEN, &bp->state);
	वापस 0;

init_err_release:
	bnxt_unmap_bars(bp, pdev);
	pci_release_regions(pdev);

init_err_disable:
	pci_disable_device(pdev);

init_err:
	वापस rc;
पूर्ण

/* rtnl_lock held */
अटल पूर्णांक bnxt_change_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(addr->sa_data, dev->dev_addr))
		वापस 0;

	rc = bnxt_approve_mac(bp, addr->sa_data, true);
	अगर (rc)
		वापस rc;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	अगर (netअगर_running(dev)) अणु
		bnxt_बंद_nic(bp, false, false);
		rc = bnxt_खोलो_nic(bp, false, false);
	पूर्ण

	वापस rc;
पूर्ण

/* rtnl_lock held */
अटल पूर्णांक bnxt_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (netअगर_running(dev))
		bnxt_बंद_nic(bp, true, false);

	dev->mtu = new_mtu;
	bnxt_set_ring_params(bp);

	अगर (netअगर_running(dev))
		वापस bnxt_खोलो_nic(bp, true, false);

	वापस 0;
पूर्ण

पूर्णांक bnxt_setup_mq_tc(काष्ठा net_device *dev, u8 tc)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	bool sh = false;
	पूर्णांक rc;

	अगर (tc > bp->max_tc) अणु
		netdev_err(dev, "Too many traffic classes requested: %d. Max supported is %d.\n",
			   tc, bp->max_tc);
		वापस -EINVAL;
	पूर्ण

	अगर (netdev_get_num_tc(dev) == tc)
		वापस 0;

	अगर (bp->flags & BNXT_FLAG_SHARED_RINGS)
		sh = true;

	rc = bnxt_check_rings(bp, bp->tx_nr_rings_per_tc, bp->rx_nr_rings,
			      sh, tc, bp->tx_nr_rings_xdp);
	अगर (rc)
		वापस rc;

	/* Needs to बंद the device and करो hw resource re-allocations */
	अगर (netअगर_running(bp->dev))
		bnxt_बंद_nic(bp, true, false);

	अगर (tc) अणु
		bp->tx_nr_rings = bp->tx_nr_rings_per_tc * tc;
		netdev_set_num_tc(dev, tc);
	पूर्ण अन्यथा अणु
		bp->tx_nr_rings = bp->tx_nr_rings_per_tc;
		netdev_reset_tc(dev);
	पूर्ण
	bp->tx_nr_rings += bp->tx_nr_rings_xdp;
	bp->cp_nr_rings = sh ? max_t(पूर्णांक, bp->tx_nr_rings, bp->rx_nr_rings) :
			       bp->tx_nr_rings + bp->rx_nr_rings;

	अगर (netअगर_running(bp->dev))
		वापस bnxt_खोलो_nic(bp, true, false);

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				  व्योम *cb_priv)
अणु
	काष्ठा bnxt *bp = cb_priv;

	अगर (!bnxt_tc_flower_enabled(bp) ||
	    !tc_cls_can_offload_and_chain0(bp->dev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस bnxt_tc_setup_flower(bp, bp->pf.fw_fid, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

LIST_HEAD(bnxt_block_cb_list);

अटल पूर्णांक bnxt_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			 व्योम *type_data)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &bnxt_block_cb_list,
						  bnxt_setup_tc_block_cb,
						  bp, bp, true);
	हाल TC_SETUP_QDISC_MQPRIO: अणु
		काष्ठा tc_mqprio_qopt *mqprio = type_data;

		mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

		वापस bnxt_setup_mq_tc(dev, mqprio->num_tc);
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल bool bnxt_fltr_match(काष्ठा bnxt_ntuple_filter *f1,
			    काष्ठा bnxt_ntuple_filter *f2)
अणु
	काष्ठा flow_keys *keys1 = &f1->fkeys;
	काष्ठा flow_keys *keys2 = &f2->fkeys;

	अगर (keys1->basic.n_proto != keys2->basic.n_proto ||
	    keys1->basic.ip_proto != keys2->basic.ip_proto)
		वापस false;

	अगर (keys1->basic.n_proto == htons(ETH_P_IP)) अणु
		अगर (keys1->addrs.v4addrs.src != keys2->addrs.v4addrs.src ||
		    keys1->addrs.v4addrs.dst != keys2->addrs.v4addrs.dst)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (स_भेद(&keys1->addrs.v6addrs.src, &keys2->addrs.v6addrs.src,
			   माप(keys1->addrs.v6addrs.src)) ||
		    स_भेद(&keys1->addrs.v6addrs.dst, &keys2->addrs.v6addrs.dst,
			   माप(keys1->addrs.v6addrs.dst)))
			वापस false;
	पूर्ण

	अगर (keys1->ports.ports == keys2->ports.ports &&
	    keys1->control.flags == keys2->control.flags &&
	    ether_addr_equal(f1->src_mac_addr, f2->src_mac_addr) &&
	    ether_addr_equal(f1->dst_mac_addr, f2->dst_mac_addr))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bnxt_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
			      u16 rxq_index, u32 flow_id)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_ntuple_filter *fltr, *new_fltr;
	काष्ठा flow_keys *fkeys;
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb_mac_header(skb);
	पूर्णांक rc = 0, idx, bit_id, l2_idx = 0;
	काष्ठा hlist_head *head;
	u32 flags;

	अगर (!ether_addr_equal(dev->dev_addr, eth->h_dest)) अणु
		काष्ठा bnxt_vnic_info *vnic = &bp->vnic_info[0];
		पूर्णांक off = 0, j;

		netअगर_addr_lock_bh(dev);
		क्रम (j = 0; j < vnic->uc_filter_count; j++, off += ETH_ALEN) अणु
			अगर (ether_addr_equal(eth->h_dest,
					     vnic->uc_list + off)) अणु
				l2_idx = j + 1;
				अवरोध;
			पूर्ण
		पूर्ण
		netअगर_addr_unlock_bh(dev);
		अगर (!l2_idx)
			वापस -EINVAL;
	पूर्ण
	new_fltr = kzalloc(माप(*new_fltr), GFP_ATOMIC);
	अगर (!new_fltr)
		वापस -ENOMEM;

	fkeys = &new_fltr->fkeys;
	अगर (!skb_flow_dissect_flow_keys(skb, fkeys, 0)) अणु
		rc = -EPROTONOSUPPORT;
		जाओ err_मुक्त;
	पूर्ण

	अगर ((fkeys->basic.n_proto != htons(ETH_P_IP) &&
	     fkeys->basic.n_proto != htons(ETH_P_IPV6)) ||
	    ((fkeys->basic.ip_proto != IPPROTO_TCP) &&
	     (fkeys->basic.ip_proto != IPPROTO_UDP))) अणु
		rc = -EPROTONOSUPPORT;
		जाओ err_मुक्त;
	पूर्ण
	अगर (fkeys->basic.n_proto == htons(ETH_P_IPV6) &&
	    bp->hwrm_spec_code < 0x10601) अणु
		rc = -EPROTONOSUPPORT;
		जाओ err_मुक्त;
	पूर्ण
	flags = fkeys->control.flags;
	अगर (((flags & FLOW_DIS_ENCAPSULATION) &&
	     bp->hwrm_spec_code < 0x10601) || (flags & FLOW_DIS_IS_FRAGMENT)) अणु
		rc = -EPROTONOSUPPORT;
		जाओ err_मुक्त;
	पूर्ण

	स_नकल(new_fltr->dst_mac_addr, eth->h_dest, ETH_ALEN);
	स_नकल(new_fltr->src_mac_addr, eth->h_source, ETH_ALEN);

	idx = skb_get_hash_raw(skb) & BNXT_NTP_FLTR_HASH_MASK;
	head = &bp->ntp_fltr_hash_tbl[idx];
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(fltr, head, hash) अणु
		अगर (bnxt_fltr_match(fltr, new_fltr)) अणु
			rcu_पढ़ो_unlock();
			rc = 0;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	spin_lock_bh(&bp->ntp_fltr_lock);
	bit_id = biपंचांगap_find_मुक्त_region(bp->ntp_fltr_bmap,
					 BNXT_NTP_FLTR_MAX_FLTR, 0);
	अगर (bit_id < 0) अणु
		spin_unlock_bh(&bp->ntp_fltr_lock);
		rc = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	new_fltr->sw_id = (u16)bit_id;
	new_fltr->flow_id = flow_id;
	new_fltr->l2_fltr_idx = l2_idx;
	new_fltr->rxq = rxq_index;
	hlist_add_head_rcu(&new_fltr->hash, head);
	bp->ntp_fltr_count++;
	spin_unlock_bh(&bp->ntp_fltr_lock);

	set_bit(BNXT_RX_NTP_FLTR_SP_EVENT, &bp->sp_event);
	bnxt_queue_sp_work(bp);

	वापस new_fltr->sw_id;

err_मुक्त:
	kमुक्त(new_fltr);
	वापस rc;
पूर्ण

अटल व्योम bnxt_cfg_ntp_filters(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) अणु
		काष्ठा hlist_head *head;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा bnxt_ntuple_filter *fltr;
		पूर्णांक rc;

		head = &bp->ntp_fltr_hash_tbl[i];
		hlist_क्रम_each_entry_safe(fltr, पंचांगp, head, hash) अणु
			bool del = false;

			अगर (test_bit(BNXT_FLTR_VALID, &fltr->state)) अणु
				अगर (rps_may_expire_flow(bp->dev, fltr->rxq,
							fltr->flow_id,
							fltr->sw_id)) अणु
					bnxt_hwrm_cfa_ntuple_filter_मुक्त(bp,
									 fltr);
					del = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				rc = bnxt_hwrm_cfa_ntuple_filter_alloc(bp,
								       fltr);
				अगर (rc)
					del = true;
				अन्यथा
					set_bit(BNXT_FLTR_VALID, &fltr->state);
			पूर्ण

			अगर (del) अणु
				spin_lock_bh(&bp->ntp_fltr_lock);
				hlist_del_rcu(&fltr->hash);
				bp->ntp_fltr_count--;
				spin_unlock_bh(&bp->ntp_fltr_lock);
				synchronize_rcu();
				clear_bit(fltr->sw_id, bp->ntp_fltr_bmap);
				kमुक्त(fltr);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (test_and_clear_bit(BNXT_HWRM_PF_UNLOAD_SP_EVENT, &bp->sp_event))
		netdev_info(bp->dev, "Receive PF driver unload event!\n");
पूर्ण

#अन्यथा

अटल व्योम bnxt_cfg_ntp_filters(काष्ठा bnxt *bp)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

अटल पूर्णांक bnxt_udp_tunnel_sync(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा bnxt *bp = netdev_priv(netdev);
	काष्ठा udp_tunnel_info ti;
	अचिन्हित पूर्णांक cmd;

	udp_tunnel_nic_get_port(netdev, table, 0, &ti);
	अगर (ti.type == UDP_TUNNEL_TYPE_VXLAN) अणु
		bp->vxlan_port = ti.port;
		cmd = TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN;
	पूर्ण अन्यथा अणु
		bp->nge_port = ti.port;
		cmd = TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE;
	पूर्ण

	अगर (ti.port)
		वापस bnxt_hwrm_tunnel_dst_port_alloc(bp, ti.port, cmd);

	वापस bnxt_hwrm_tunnel_dst_port_मुक्त(bp, cmd);
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info bnxt_udp_tunnels = अणु
	.sync_table	= bnxt_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
			  UDP_TUNNEL_NIC_INFO_OPEN_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bnxt_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
			       काष्ठा net_device *dev, u32 filter_mask,
			       पूर्णांक nlflags)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev, bp->br_mode, 0, 0,
				       nlflags, filter_mask, शून्य);
पूर्ण

अटल पूर्णांक bnxt_bridge_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
			       u16 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा nlattr *attr, *br_spec;
	पूर्णांक rem, rc = 0;

	अगर (bp->hwrm_spec_code < 0x10708 || !BNXT_SINGLE_PF(bp))
		वापस -EOPNOTSUPP;

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!br_spec)
		वापस -EINVAL;

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		u16 mode;

		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;

		अगर (nla_len(attr) < माप(mode))
			वापस -EINVAL;

		mode = nla_get_u16(attr);
		अगर (mode == bp->br_mode)
			अवरोध;

		rc = bnxt_hwrm_set_br_mode(bp, mode);
		अगर (!rc)
			bp->br_mode = mode;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक bnxt_get_port_parent_id(काष्ठा net_device *dev,
			    काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस -EOPNOTSUPP;

	/* The PF and it's VF-reps only support the चयनdev framework */
	अगर (!BNXT_PF(bp) || !(bp->flags & BNXT_FLAG_DSN_VALID))
		वापस -EOPNOTSUPP;

	ppid->id_len = माप(bp->dsn);
	स_नकल(ppid->id, bp->dsn, ppid->id_len);

	वापस 0;
पूर्ण

अटल काष्ठा devlink_port *bnxt_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);

	वापस &bp->dl_port;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bnxt_netdev_ops = अणु
	.nकरो_खोलो		= bnxt_खोलो,
	.nकरो_start_xmit		= bnxt_start_xmit,
	.nकरो_stop		= bnxt_बंद,
	.nकरो_get_stats64	= bnxt_get_stats64,
	.nकरो_set_rx_mode	= bnxt_set_rx_mode,
	.nकरो_करो_ioctl		= bnxt_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= bnxt_change_mac_addr,
	.nकरो_change_mtu		= bnxt_change_mtu,
	.nकरो_fix_features	= bnxt_fix_features,
	.nकरो_set_features	= bnxt_set_features,
	.nकरो_features_check	= bnxt_features_check,
	.nकरो_tx_समयout		= bnxt_tx_समयout,
#अगर_घोषित CONFIG_BNXT_SRIOV
	.nकरो_get_vf_config	= bnxt_get_vf_config,
	.nकरो_set_vf_mac		= bnxt_set_vf_mac,
	.nकरो_set_vf_vlan	= bnxt_set_vf_vlan,
	.nकरो_set_vf_rate	= bnxt_set_vf_bw,
	.nकरो_set_vf_link_state	= bnxt_set_vf_link_state,
	.nकरो_set_vf_spoofchk	= bnxt_set_vf_spoofchk,
	.nकरो_set_vf_trust	= bnxt_set_vf_trust,
#पूर्ण_अगर
	.nकरो_setup_tc           = bnxt_setup_tc,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= bnxt_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_bpf		= bnxt_xdp,
	.nकरो_xdp_xmit		= bnxt_xdp_xmit,
	.nकरो_bridge_getlink	= bnxt_bridge_getlink,
	.nकरो_bridge_setlink	= bnxt_bridge_setlink,
	.nकरो_get_devlink_port	= bnxt_get_devlink_port,
पूर्ण;

अटल व्योम bnxt_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (BNXT_PF(bp))
		bnxt_sriov_disable(bp);

	अगर (BNXT_PF(bp))
		devlink_port_type_clear(&bp->dl_port);
	pci_disable_pcie_error_reporting(pdev);
	unरेजिस्टर_netdev(dev);
	clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
	/* Flush any pending tasks */
	cancel_work_sync(&bp->sp_task);
	cancel_delayed_work_sync(&bp->fw_reset_task);
	bp->sp_event = 0;

	bnxt_dl_fw_reporters_destroy(bp, true);
	bnxt_dl_unरेजिस्टर(bp);
	bnxt_shutकरोwn_tc(bp);

	bnxt_clear_पूर्णांक_mode(bp);
	bnxt_hwrm_func_drv_unrgtr(bp);
	bnxt_मुक्त_hwrm_resources(bp);
	bnxt_मुक्त_hwrm_लघु_cmd_req(bp);
	bnxt_ethtool_मुक्त(bp);
	bnxt_dcb_मुक्त(bp);
	kमुक्त(bp->edev);
	bp->edev = शून्य;
	kमुक्त(bp->fw_health);
	bp->fw_health = शून्य;
	bnxt_cleanup_pci(bp);
	bnxt_मुक्त_ctx_mem(bp);
	kमुक्त(bp->ctx);
	bp->ctx = शून्य;
	kमुक्त(bp->rss_indir_tbl);
	bp->rss_indir_tbl = शून्य;
	bnxt_मुक्त_port_stats(bp);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक bnxt_probe_phy(काष्ठा bnxt *bp, bool fw_dflt)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnxt_link_info *link_info = &bp->link_info;

	bp->phy_flags = 0;
	rc = bnxt_hwrm_phy_qcaps(bp);
	अगर (rc) अणु
		netdev_err(bp->dev, "Probe phy can't get phy capabilities (rc: %x)\n",
			   rc);
		वापस rc;
	पूर्ण
	अगर (bp->phy_flags & BNXT_PHY_FL_NO_FCS)
		bp->dev->priv_flags |= IFF_SUPP_NOFCS;
	अन्यथा
		bp->dev->priv_flags &= ~IFF_SUPP_NOFCS;
	अगर (!fw_dflt)
		वापस 0;

	rc = bnxt_update_link(bp, false);
	अगर (rc) अणु
		netdev_err(bp->dev, "Probe phy can't update link (rc: %x)\n",
			   rc);
		वापस rc;
	पूर्ण

	/* Older firmware करोes not have supported_स्वतः_speeds, so assume
	 * that all supported speeds can be स्वतःnegotiated.
	 */
	अगर (link_info->स्वतः_link_speeds && !link_info->support_स्वतः_speeds)
		link_info->support_स्वतः_speeds = link_info->support_speeds;

	bnxt_init_ethtool_link_settings(bp);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_get_max_irq(काष्ठा pci_dev *pdev)
अणु
	u16 ctrl;

	अगर (!pdev->msix_cap)
		वापस 1;

	pci_पढ़ो_config_word(pdev, pdev->msix_cap + PCI_MSIX_FLAGS, &ctrl);
	वापस (ctrl & PCI_MSIX_FLAGS_QSIZE) + 1;
पूर्ण

अटल व्योम _bnxt_get_max_rings(काष्ठा bnxt *bp, पूर्णांक *max_rx, पूर्णांक *max_tx,
				पूर्णांक *max_cp)
अणु
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक max_ring_grps = 0, max_irq;

	*max_tx = hw_resc->max_tx_rings;
	*max_rx = hw_resc->max_rx_rings;
	*max_cp = bnxt_get_max_func_cp_rings_क्रम_en(bp);
	max_irq = min_t(पूर्णांक, bnxt_get_max_func_irqs(bp) -
			bnxt_get_ulp_msix_num(bp),
			hw_resc->max_stat_ctxs - bnxt_get_ulp_stat_ctxs(bp));
	अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
		*max_cp = min_t(पूर्णांक, *max_cp, max_irq);
	max_ring_grps = hw_resc->max_hw_ring_grps;
	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp) && BNXT_PF(bp)) अणु
		*max_cp -= 1;
		*max_rx -= 2;
	पूर्ण
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		*max_rx >>= 1;
	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		bnxt_trim_rings(bp, max_rx, max_tx, *max_cp, false);
		/* On P5 chips, max_cp output param should be available NQs */
		*max_cp = max_irq;
	पूर्ण
	*max_rx = min_t(पूर्णांक, *max_rx, max_ring_grps);
पूर्ण

पूर्णांक bnxt_get_max_rings(काष्ठा bnxt *bp, पूर्णांक *max_rx, पूर्णांक *max_tx, bool shared)
अणु
	पूर्णांक rx, tx, cp;

	_bnxt_get_max_rings(bp, &rx, &tx, &cp);
	*max_rx = rx;
	*max_tx = tx;
	अगर (!rx || !tx || !cp)
		वापस -ENOMEM;

	वापस bnxt_trim_rings(bp, max_rx, max_tx, cp, shared);
पूर्ण

अटल पूर्णांक bnxt_get_dflt_rings(काष्ठा bnxt *bp, पूर्णांक *max_rx, पूर्णांक *max_tx,
			       bool shared)
अणु
	पूर्णांक rc;

	rc = bnxt_get_max_rings(bp, max_rx, max_tx, shared);
	अगर (rc && (bp->flags & BNXT_FLAG_AGG_RINGS)) अणु
		/* Not enough rings, try disabling agg rings. */
		bp->flags &= ~BNXT_FLAG_AGG_RINGS;
		rc = bnxt_get_max_rings(bp, max_rx, max_tx, shared);
		अगर (rc) अणु
			/* set BNXT_FLAG_AGG_RINGS back क्रम consistency */
			bp->flags |= BNXT_FLAG_AGG_RINGS;
			वापस rc;
		पूर्ण
		bp->flags |= BNXT_FLAG_NO_AGG_RINGS;
		bp->dev->hw_features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);
		bp->dev->features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);
		bnxt_set_ring_params(bp);
	पूर्ण

	अगर (bp->flags & BNXT_FLAG_ROCE_CAP) अणु
		पूर्णांक max_cp, max_stat, max_irq;

		/* Reserve minimum resources क्रम RoCE */
		max_cp = bnxt_get_max_func_cp_rings(bp);
		max_stat = bnxt_get_max_func_stat_ctxs(bp);
		max_irq = bnxt_get_max_func_irqs(bp);
		अगर (max_cp <= BNXT_MIN_ROCE_CP_RINGS ||
		    max_irq <= BNXT_MIN_ROCE_CP_RINGS ||
		    max_stat <= BNXT_MIN_ROCE_STAT_CTXS)
			वापस 0;

		max_cp -= BNXT_MIN_ROCE_CP_RINGS;
		max_irq -= BNXT_MIN_ROCE_CP_RINGS;
		max_stat -= BNXT_MIN_ROCE_STAT_CTXS;
		max_cp = min_t(पूर्णांक, max_cp, max_irq);
		max_cp = min_t(पूर्णांक, max_cp, max_stat);
		rc = bnxt_trim_rings(bp, max_rx, max_tx, max_cp, shared);
		अगर (rc)
			rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/* In initial शेष shared ring setting, each shared ring must have a
 * RX/TX ring pair.
 */
अटल व्योम bnxt_trim_dflt_sh_rings(काष्ठा bnxt *bp)
अणु
	bp->cp_nr_rings = min_t(पूर्णांक, bp->tx_nr_rings_per_tc, bp->rx_nr_rings);
	bp->rx_nr_rings = bp->cp_nr_rings;
	bp->tx_nr_rings_per_tc = bp->cp_nr_rings;
	bp->tx_nr_rings = bp->tx_nr_rings_per_tc;
पूर्ण

अटल पूर्णांक bnxt_set_dflt_rings(काष्ठा bnxt *bp, bool sh)
अणु
	पूर्णांक dflt_rings, max_rx_rings, max_tx_rings, rc;

	अगर (!bnxt_can_reserve_rings(bp))
		वापस 0;

	अगर (sh)
		bp->flags |= BNXT_FLAG_SHARED_RINGS;
	dflt_rings = is_kdump_kernel() ? 1 : netअगर_get_num_शेष_rss_queues();
	/* Reduce शेष rings on multi-port cards so that total शेष
	 * rings करो not exceed CPU count.
	 */
	अगर (bp->port_count > 1) अणु
		पूर्णांक max_rings =
			max_t(पूर्णांक, num_online_cpus() / bp->port_count, 1);

		dflt_rings = min_t(पूर्णांक, dflt_rings, max_rings);
	पूर्ण
	rc = bnxt_get_dflt_rings(bp, &max_rx_rings, &max_tx_rings, sh);
	अगर (rc)
		वापस rc;
	bp->rx_nr_rings = min_t(पूर्णांक, dflt_rings, max_rx_rings);
	bp->tx_nr_rings_per_tc = min_t(पूर्णांक, dflt_rings, max_tx_rings);
	अगर (sh)
		bnxt_trim_dflt_sh_rings(bp);
	अन्यथा
		bp->cp_nr_rings = bp->tx_nr_rings_per_tc + bp->rx_nr_rings;
	bp->tx_nr_rings = bp->tx_nr_rings_per_tc;

	rc = __bnxt_reserve_rings(bp);
	अगर (rc)
		netdev_warn(bp->dev, "Unable to reserve tx rings\n");
	bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
	अगर (sh)
		bnxt_trim_dflt_sh_rings(bp);

	/* Rings may have been trimmed, re-reserve the trimmed rings. */
	अगर (bnxt_need_reserve_rings(bp)) अणु
		rc = __bnxt_reserve_rings(bp);
		अगर (rc)
			netdev_warn(bp->dev, "2nd rings reservation failed.\n");
		bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
	पूर्ण
	अगर (BNXT_CHIP_TYPE_NITRO_A0(bp)) अणु
		bp->rx_nr_rings++;
		bp->cp_nr_rings++;
	पूर्ण
	अगर (rc) अणु
		bp->tx_nr_rings = 0;
		bp->rx_nr_rings = 0;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_init_dflt_ring_mode(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	अगर (bp->tx_nr_rings)
		वापस 0;

	bnxt_ulp_irq_stop(bp);
	bnxt_clear_पूर्णांक_mode(bp);
	rc = bnxt_set_dflt_rings(bp, true);
	अगर (rc) अणु
		netdev_err(bp->dev, "Not enough rings available.\n");
		जाओ init_dflt_ring_err;
	पूर्ण
	rc = bnxt_init_पूर्णांक_mode(bp);
	अगर (rc)
		जाओ init_dflt_ring_err;

	bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
	अगर (bnxt_rfs_supported(bp) && bnxt_rfs_capable(bp)) अणु
		bp->flags |= BNXT_FLAG_RFS;
		bp->dev->features |= NETIF_F_NTUPLE;
	पूर्ण
init_dflt_ring_err:
	bnxt_ulp_irq_restart(bp, rc);
	वापस rc;
पूर्ण

पूर्णांक bnxt_restore_pf_fw_resources(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc;

	ASSERT_RTNL();
	bnxt_hwrm_func_qcaps(bp);

	अगर (netअगर_running(bp->dev))
		__bnxt_बंद_nic(bp, true, false);

	bnxt_ulp_irq_stop(bp);
	bnxt_clear_पूर्णांक_mode(bp);
	rc = bnxt_init_पूर्णांक_mode(bp);
	bnxt_ulp_irq_restart(bp, rc);

	अगर (netअगर_running(bp->dev)) अणु
		अगर (rc)
			dev_बंद(bp->dev);
		अन्यथा
			rc = bnxt_खोलो_nic(bp, true, false);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_init_mac_addr(काष्ठा bnxt *bp)
अणु
	पूर्णांक rc = 0;

	अगर (BNXT_PF(bp)) अणु
		स_नकल(bp->dev->dev_addr, bp->pf.mac_addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_BNXT_SRIOV
		काष्ठा bnxt_vf_info *vf = &bp->vf;
		bool strict_approval = true;

		अगर (is_valid_ether_addr(vf->mac_addr)) अणु
			/* overग_लिखो netdev dev_addr with admin VF MAC */
			स_नकल(bp->dev->dev_addr, vf->mac_addr, ETH_ALEN);
			/* Older PF driver or firmware may not approve this
			 * correctly.
			 */
			strict_approval = false;
		पूर्ण अन्यथा अणु
			eth_hw_addr_अक्रमom(bp->dev);
		पूर्ण
		rc = bnxt_approve_mac(bp, bp->dev->dev_addr, strict_approval);
#पूर्ण_अगर
	पूर्ण
	वापस rc;
पूर्ण

#घोषणा BNXT_VPD_LEN	512
अटल व्योम bnxt_vpd_पढ़ो_info(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक i, len, pos, ro_size, size;
	sमाप_प्रकार vpd_size;
	u8 *vpd_data;

	vpd_data = kदो_स्मृति(BNXT_VPD_LEN, GFP_KERNEL);
	अगर (!vpd_data)
		वापस;

	vpd_size = pci_पढ़ो_vpd(pdev, 0, BNXT_VPD_LEN, vpd_data);
	अगर (vpd_size <= 0) अणु
		netdev_err(bp->dev, "Unable to read VPD\n");
		जाओ निकास;
	पूर्ण

	i = pci_vpd_find_tag(vpd_data, vpd_size, PCI_VPD_LRDT_RO_DATA);
	अगर (i < 0) अणु
		netdev_err(bp->dev, "VPD READ-Only not found\n");
		जाओ निकास;
	पूर्ण

	ro_size = pci_vpd_lrdt_size(&vpd_data[i]);
	i += PCI_VPD_LRDT_TAG_SIZE;
	अगर (i + ro_size > vpd_size)
		जाओ निकास;

	pos = pci_vpd_find_info_keyword(vpd_data, i, ro_size,
					PCI_VPD_RO_KEYWORD_PARTNO);
	अगर (pos < 0)
		जाओ पढ़ो_sn;

	len = pci_vpd_info_field_size(&vpd_data[pos]);
	pos += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (len + pos > vpd_size)
		जाओ पढ़ो_sn;

	size = min(len, BNXT_VPD_FLD_LEN - 1);
	स_नकल(bp->board_partno, &vpd_data[pos], size);

पढ़ो_sn:
	pos = pci_vpd_find_info_keyword(vpd_data, i, ro_size,
					PCI_VPD_RO_KEYWORD_SERIALNO);
	अगर (pos < 0)
		जाओ निकास;

	len = pci_vpd_info_field_size(&vpd_data[pos]);
	pos += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (len + pos > vpd_size)
		जाओ निकास;

	size = min(len, BNXT_VPD_FLD_LEN - 1);
	स_नकल(bp->board_serialno, &vpd_data[pos], size);
निकास:
	kमुक्त(vpd_data);
पूर्ण

अटल पूर्णांक bnxt_pcie_dsn_get(काष्ठा bnxt *bp, u8 dsn[])
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	u64 qword;

	qword = pci_get_dsn(pdev);
	अगर (!qword) अणु
		netdev_info(bp->dev, "Unable to read adapter's DSN\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	put_unaligned_le64(qword, dsn);

	bp->flags |= BNXT_FLAG_DSN_VALID;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_map_db_bar(काष्ठा bnxt *bp)
अणु
	अगर (!bp->db_size)
		वापस -ENODEV;
	bp->bar1 = pci_iomap(bp->pdev, 2, bp->db_size);
	अगर (!bp->bar1)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा bnxt *bp;
	पूर्णांक rc, max_irqs;

	अगर (pci_is_bridge(pdev))
		वापस -ENODEV;

	/* Clear any pending DMA transactions from crash kernel
	 * जबतक loading driver in capture kernel.
	 */
	अगर (is_kdump_kernel()) अणु
		pci_clear_master(pdev);
		pcie_flr(pdev);
	पूर्ण

	max_irqs = bnxt_get_max_irq(pdev);
	dev = alloc_etherdev_mq(माप(*bp), max_irqs);
	अगर (!dev)
		वापस -ENOMEM;

	bp = netdev_priv(dev);
	bp->msg_enable = BNXT_DEF_MSG_ENABLE;
	bnxt_set_max_func_irqs(bp, max_irqs);

	अगर (bnxt_vf_pciid(ent->driver_data))
		bp->flags |= BNXT_FLAG_VF;

	अगर (pdev->msix_cap)
		bp->flags |= BNXT_FLAG_MSIX_CAP;

	rc = bnxt_init_board(pdev, dev);
	अगर (rc < 0)
		जाओ init_err_मुक्त;

	dev->netdev_ops = &bnxt_netdev_ops;
	dev->watchकरोg_समयo = BNXT_TX_TIMEOUT;
	dev->ethtool_ops = &bnxt_ethtool_ops;
	pci_set_drvdata(pdev, dev);

	rc = bnxt_alloc_hwrm_resources(bp);
	अगर (rc)
		जाओ init_err_pci_clean;

	mutex_init(&bp->hwrm_cmd_lock);
	mutex_init(&bp->link_lock);

	rc = bnxt_fw_init_one_p1(bp);
	अगर (rc)
		जाओ init_err_pci_clean;

	अगर (BNXT_PF(bp))
		bnxt_vpd_पढ़ो_info(bp);

	अगर (BNXT_CHIP_P5(bp)) अणु
		bp->flags |= BNXT_FLAG_CHIP_P5;
		अगर (BNXT_CHIP_SR2(bp))
			bp->flags |= BNXT_FLAG_CHIP_SR2;
	पूर्ण

	rc = bnxt_alloc_rss_indir_tbl(bp);
	अगर (rc)
		जाओ init_err_pci_clean;

	rc = bnxt_fw_init_one_p2(bp);
	अगर (rc)
		जाओ init_err_pci_clean;

	rc = bnxt_map_db_bar(bp);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot map doorbell BAR rc = %d, aborting\n",
			rc);
		जाओ init_err_pci_clean;
	पूर्ण

	dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SG |
			   NETIF_F_TSO | NETIF_F_TSO6 |
			   NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_GRE |
			   NETIF_F_GSO_IPXIP4 |
			   NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_GSO_GRE_CSUM |
			   NETIF_F_GSO_PARTIAL | NETIF_F_RXHASH |
			   NETIF_F_RXCSUM | NETIF_F_GRO;

	अगर (BNXT_SUPPORTS_TPA(bp))
		dev->hw_features |= NETIF_F_LRO;

	dev->hw_enc_features =
			NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SG |
			NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_GRE |
			NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_GSO_GRE_CSUM |
			NETIF_F_GSO_IPXIP4 | NETIF_F_GSO_PARTIAL;
	dev->udp_tunnel_nic_info = &bnxt_udp_tunnels;

	dev->gso_partial_features = NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_GRE_CSUM;
	dev->vlan_features = dev->hw_features | NETIF_F_HIGHDMA;
	अगर (bp->fw_cap & BNXT_FW_CAP_VLAN_RX_STRIP)
		dev->hw_features |= BNXT_HW_FEATURE_VLAN_ALL_RX;
	अगर (bp->fw_cap & BNXT_FW_CAP_VLAN_TX_INSERT)
		dev->hw_features |= BNXT_HW_FEATURE_VLAN_ALL_TX;
	अगर (BNXT_SUPPORTS_TPA(bp))
		dev->hw_features |= NETIF_F_GRO_HW;
	dev->features |= dev->hw_features | NETIF_F_HIGHDMA;
	अगर (dev->features & NETIF_F_GRO_HW)
		dev->features &= ~NETIF_F_LRO;
	dev->priv_flags |= IFF_UNICAST_FLT;

#अगर_घोषित CONFIG_BNXT_SRIOV
	init_रुकोqueue_head(&bp->sriov_cfg_रुको);
	mutex_init(&bp->sriov_lock);
#पूर्ण_अगर
	अगर (BNXT_SUPPORTS_TPA(bp)) अणु
		bp->gro_func = bnxt_gro_func_5730x;
		अगर (BNXT_CHIP_P4(bp))
			bp->gro_func = bnxt_gro_func_5731x;
		अन्यथा अगर (BNXT_CHIP_P5(bp))
			bp->gro_func = bnxt_gro_func_5750x;
	पूर्ण
	अगर (!BNXT_CHIP_P4_PLUS(bp))
		bp->flags |= BNXT_FLAG_DOUBLE_DB;

	rc = bnxt_init_mac_addr(bp);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Unable to initialize mac address.\n");
		rc = -EADDRNOTAVAIL;
		जाओ init_err_pci_clean;
	पूर्ण

	अगर (BNXT_PF(bp)) अणु
		/* Read the adapter's DSN to use as the eचयन चयन_id */
		rc = bnxt_pcie_dsn_get(bp, bp->dsn);
	पूर्ण

	/* MTU range: 60 - FW defined max */
	dev->min_mtu = ETH_ZLEN;
	dev->max_mtu = bp->max_mtu;

	rc = bnxt_probe_phy(bp, true);
	अगर (rc)
		जाओ init_err_pci_clean;

	bnxt_set_rx_skb_mode(bp, false);
	bnxt_set_tpa_flags(bp);
	bnxt_set_ring_params(bp);
	rc = bnxt_set_dflt_rings(bp, true);
	अगर (rc) अणु
		netdev_err(bp->dev, "Not enough rings available.\n");
		rc = -ENOMEM;
		जाओ init_err_pci_clean;
	पूर्ण

	bnxt_fw_init_one_p3(bp);

	अगर (dev->hw_features & BNXT_HW_FEATURE_VLAN_ALL_RX)
		bp->flags |= BNXT_FLAG_STRIP_VLAN;

	rc = bnxt_init_पूर्णांक_mode(bp);
	अगर (rc)
		जाओ init_err_pci_clean;

	/* No TC has been set yet and rings may have been trimmed due to
	 * limited MSIX, so we re-initialize the TX rings per TC.
	 */
	bp->tx_nr_rings_per_tc = bp->tx_nr_rings;

	अगर (BNXT_PF(bp)) अणु
		अगर (!bnxt_pf_wq) अणु
			bnxt_pf_wq =
				create_singlethपढ़ो_workqueue("bnxt_pf_wq");
			अगर (!bnxt_pf_wq) अणु
				dev_err(&pdev->dev, "Unable to create workqueue.\n");
				rc = -ENOMEM;
				जाओ init_err_pci_clean;
			पूर्ण
		पूर्ण
		rc = bnxt_init_tc(bp);
		अगर (rc)
			netdev_err(dev, "Failed to initialize TC flower offload, err = %d.\n",
				   rc);
	पूर्ण

	bnxt_inv_fw_health_reg(bp);
	bnxt_dl_रेजिस्टर(bp);

	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		जाओ init_err_cleanup;

	अगर (BNXT_PF(bp))
		devlink_port_type_eth_set(&bp->dl_port, bp->dev);
	bnxt_dl_fw_reporters_create(bp);

	netdev_info(dev, "%s found at mem %lx, node addr %pM\n",
		    board_info[ent->driver_data].name,
		    (दीर्घ)pci_resource_start(pdev, 0), dev->dev_addr);
	pcie_prपूर्णांक_link_status(pdev);

	pci_save_state(pdev);
	वापस 0;

init_err_cleanup:
	bnxt_dl_unरेजिस्टर(bp);
	bnxt_shutकरोwn_tc(bp);
	bnxt_clear_पूर्णांक_mode(bp);

init_err_pci_clean:
	bnxt_hwrm_func_drv_unrgtr(bp);
	bnxt_मुक्त_hwrm_लघु_cmd_req(bp);
	bnxt_मुक्त_hwrm_resources(bp);
	bnxt_ethtool_मुक्त(bp);
	kमुक्त(bp->fw_health);
	bp->fw_health = शून्य;
	bnxt_cleanup_pci(bp);
	bnxt_मुक्त_ctx_mem(bp);
	kमुक्त(bp->ctx);
	bp->ctx = शून्य;
	kमुक्त(bp->rss_indir_tbl);
	bp->rss_indir_tbl = शून्य;

init_err_मुक्त:
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण

अटल व्योम bnxt_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp;

	अगर (!dev)
		वापस;

	rtnl_lock();
	bp = netdev_priv(dev);
	अगर (!bp)
		जाओ shutकरोwn_निकास;

	अगर (netअगर_running(dev))
		dev_बंद(dev);

	bnxt_ulp_shutकरोwn(bp);
	bnxt_clear_पूर्णांक_mode(bp);
	pci_disable_device(pdev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, bp->wol);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण

shutकरोwn_निकास:
	rtnl_unlock();
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bnxt_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	rtnl_lock();
	bnxt_ulp_stop(bp);
	अगर (netअगर_running(dev)) अणु
		netअगर_device_detach(dev);
		rc = bnxt_बंद(dev);
	पूर्ण
	bnxt_hwrm_func_drv_unrgtr(bp);
	pci_disable_device(bp->pdev);
	bnxt_मुक्त_ctx_mem(bp);
	kमुक्त(bp->ctx);
	bp->ctx = शून्य;
	rtnl_unlock();
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	rtnl_lock();
	rc = pci_enable_device(bp->pdev);
	अगर (rc) अणु
		netdev_err(dev, "Cannot re-enable PCI device during resume, err = %d\n",
			   rc);
		जाओ resume_निकास;
	पूर्ण
	pci_set_master(bp->pdev);
	अगर (bnxt_hwrm_ver_get(bp)) अणु
		rc = -ENODEV;
		जाओ resume_निकास;
	पूर्ण
	rc = bnxt_hwrm_func_reset(bp);
	अगर (rc) अणु
		rc = -EBUSY;
		जाओ resume_निकास;
	पूर्ण

	rc = bnxt_hwrm_func_qcaps(bp);
	अगर (rc)
		जाओ resume_निकास;

	अगर (bnxt_hwrm_func_drv_rgtr(bp, शून्य, 0, false)) अणु
		rc = -ENODEV;
		जाओ resume_निकास;
	पूर्ण

	bnxt_get_wol_settings(bp);
	अगर (netअगर_running(dev)) अणु
		rc = bnxt_खोलो(dev);
		अगर (!rc)
			netअगर_device_attach(dev);
	पूर्ण

resume_निकास:
	bnxt_ulp_start(bp, rc);
	अगर (!rc)
		bnxt_reenable_sriov(bp);
	rtnl_unlock();
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bnxt_pm_ops, bnxt_suspend, bnxt_resume);
#घोषणा BNXT_PM_OPS (&bnxt_pm_ops)

#अन्यथा

#घोषणा BNXT_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/**
 * bnxt_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t bnxt_io_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp = netdev_priv(netdev);

	netdev_info(netdev, "PCI I/O error detected\n");

	rtnl_lock();
	netअगर_device_detach(netdev);

	bnxt_ulp_stop(bp);

	अगर (state == pci_channel_io_perm_failure) अणु
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (state == pci_channel_io_frozen)
		set_bit(BNXT_STATE_PCI_CHANNEL_IO_FROZEN, &bp->state);

	अगर (netअगर_running(netdev))
		bnxt_बंद(netdev);

	pci_disable_device(pdev);
	bnxt_मुक्त_ctx_mem(bp);
	kमुक्त(bp->ctx);
	bp->ctx = शून्य;
	rtnl_unlock();

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * bnxt_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 * At this poपूर्णांक, the card has exprienced a hard reset,
 * followed by fixups by BIOS, and has its config space
 * set up identically to what it was at cold boot.
 */
अटल pci_ers_result_t bnxt_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t result = PCI_ERS_RESULT_DISCONNECT;
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp = netdev_priv(netdev);
	पूर्णांक err = 0, off;

	netdev_info(bp->dev, "PCI Slot Reset\n");

	rtnl_lock();

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		/* Upon fatal error, our device पूर्णांकernal logic that latches to
		 * BAR value is getting reset and will restore only upon
		 * rewritting the BARs.
		 *
		 * As pci_restore_state() करोes not re-ग_लिखो the BARs अगर the
		 * value is same as saved value earlier, driver needs to
		 * ग_लिखो the BARs to 0 to क्रमce restore, in हाल of fatal error.
		 */
		अगर (test_and_clear_bit(BNXT_STATE_PCI_CHANNEL_IO_FROZEN,
				       &bp->state)) अणु
			क्रम (off = PCI_BASE_ADDRESS_0;
			     off <= PCI_BASE_ADDRESS_5; off += 4)
				pci_ग_लिखो_config_dword(bp->pdev, off, 0);
		पूर्ण
		pci_restore_state(pdev);
		pci_save_state(pdev);

		err = bnxt_hwrm_func_reset(bp);
		अगर (!err)
			result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	rtnl_unlock();

	वापस result;
पूर्ण

/**
 * bnxt_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells
 * us that its OK to resume normal operation.
 */
अटल व्योम bnxt_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp = netdev_priv(netdev);
	पूर्णांक err;

	netdev_info(bp->dev, "PCI Slot Resume\n");
	rtnl_lock();

	err = bnxt_hwrm_func_qcaps(bp);
	अगर (!err && netअगर_running(netdev))
		err = bnxt_खोलो(netdev);

	bnxt_ulp_start(bp, err);
	अगर (!err) अणु
		bnxt_reenable_sriov(bp);
		netअगर_device_attach(netdev);
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers bnxt_err_handler = अणु
	.error_detected	= bnxt_io_error_detected,
	.slot_reset	= bnxt_io_slot_reset,
	.resume		= bnxt_io_resume
पूर्ण;

अटल काष्ठा pci_driver bnxt_pci_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= bnxt_pci_tbl,
	.probe		= bnxt_init_one,
	.हटाओ		= bnxt_हटाओ_one,
	.shutकरोwn	= bnxt_shutकरोwn,
	.driver.pm	= BNXT_PM_OPS,
	.err_handler	= &bnxt_err_handler,
#अगर defined(CONFIG_BNXT_SRIOV)
	.sriov_configure = bnxt_sriov_configure,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init bnxt_init(व्योम)
अणु
	bnxt_debug_init();
	वापस pci_रेजिस्टर_driver(&bnxt_pci_driver);
पूर्ण

अटल व्योम __निकास bnxt_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bnxt_pci_driver);
	अगर (bnxt_pf_wq)
		destroy_workqueue(bnxt_pf_wq);
	bnxt_debug_निकास();
पूर्ण

module_init(bnxt_init);
module_निकास(bnxt_निकास);
