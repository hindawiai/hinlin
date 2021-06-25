<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/slab.h>
#समावेश "netxen_nic.h"
#समावेश "netxen_nic_hw.h"

#समावेश <net/ip.h>

#घोषणा MASK(n) ((1ULL<<(n))-1)
#घोषणा MN_WIN(addr) (((addr & 0x1fc0000) >> 1) | ((addr >> 25) & 0x3ff))
#घोषणा OCM_WIN(addr) (((addr & 0x1ff0000) >> 1) | ((addr >> 25) & 0x3ff))
#घोषणा MS_WIN(addr) (addr & 0x0ffc0000)

#घोषणा GET_MEM_OFFS_2M(addr) (addr & MASK(18))

#घोषणा CRB_BLK(off)	((off >> 20) & 0x3f)
#घोषणा CRB_SUBBLK(off)	((off >> 16) & 0xf)
#घोषणा CRB_WINDOW_2M	(0x130060)
#घोषणा CRB_HI(off)	((crb_hub_agt[CRB_BLK(off)] << 20) | ((off) & 0xf0000))
#घोषणा CRB_INसूचीECT_2M	(0x1e0000UL)

अटल व्योम netxen_nic_io_ग_लिखो_128M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr, u32 data);
अटल u32 netxen_nic_io_पढ़ो_128M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr);

#घोषणा PCI_OFFSET_FIRST_RANGE(adapter, off)    \
	((adapter)->ahw.pci_base0 + (off))
#घोषणा PCI_OFFSET_SECOND_RANGE(adapter, off)   \
	((adapter)->ahw.pci_base1 + (off) - SECOND_PAGE_GROUP_START)
#घोषणा PCI_OFFSET_THIRD_RANGE(adapter, off)    \
	((adapter)->ahw.pci_base2 + (off) - THIRD_PAGE_GROUP_START)

अटल व्योम __iomem *pci_base_offset(काष्ठा netxen_adapter *adapter,
					    अचिन्हित दीर्घ off)
अणु
	अगर (ADDR_IN_RANGE(off, FIRST_PAGE_GROUP_START, FIRST_PAGE_GROUP_END))
		वापस PCI_OFFSET_FIRST_RANGE(adapter, off);

	अगर (ADDR_IN_RANGE(off, SECOND_PAGE_GROUP_START, SECOND_PAGE_GROUP_END))
		वापस PCI_OFFSET_SECOND_RANGE(adapter, off);

	अगर (ADDR_IN_RANGE(off, THIRD_PAGE_GROUP_START, THIRD_PAGE_GROUP_END))
		वापस PCI_OFFSET_THIRD_RANGE(adapter, off);

	वापस शून्य;
पूर्ण

अटल crb_128M_2M_block_map_t
crb_128M_2M_map[64] __cacheline_aligned_in_smp = अणु
    अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,		/* 0: PCI */
    अणुअणुअणु1, 0x0100000, 0x0102000, 0x120000पूर्ण,	/* 1: PCIE */
	  अणु1, 0x0110000, 0x0120000, 0x130000पूर्ण,
	  अणु1, 0x0120000, 0x0122000, 0x124000पूर्ण,
	  अणु1, 0x0130000, 0x0132000, 0x126000पूर्ण,
	  अणु1, 0x0140000, 0x0142000, 0x128000पूर्ण,
	  अणु1, 0x0150000, 0x0152000, 0x12a000पूर्ण,
	  अणु1, 0x0160000, 0x0170000, 0x110000पूर्ण,
	  अणु1, 0x0170000, 0x0172000, 0x12e000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु1, 0x01e0000, 0x01e0800, 0x122000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0200000, 0x0210000, 0x180000पूर्ण पूर्ण पूर्ण,/* 2: MN */
    अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	    /* 3: */
    अणुअणुअणु1, 0x0400000, 0x0401000, 0x169000पूर्ण पूर्ण पूर्ण,/* 4: P2NR1 */
    अणुअणुअणु1, 0x0500000, 0x0510000, 0x140000पूर्ण पूर्ण पूर्ण,/* 5: SRE   */
    अणुअणुअणु1, 0x0600000, 0x0610000, 0x1c0000पूर्ण पूर्ण पूर्ण,/* 6: NIU   */
    अणुअणुअणु1, 0x0700000, 0x0704000, 0x1b8000पूर्ण पूर्ण पूर्ण,/* 7: QM    */
    अणुअणुअणु1, 0x0800000, 0x0802000, 0x170000पूर्ण,  /* 8: SQM0  */
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु1, 0x08f0000, 0x08f2000, 0x172000पूर्ण पूर्ण पूर्ण,
    अणुअणुअणु1, 0x0900000, 0x0902000, 0x174000पूर्ण,	/* 9: SQM1*/
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु1, 0x09f0000, 0x09f2000, 0x176000पूर्ण पूर्ण पूर्ण,
    अणुअणुअणु0, 0x0a00000, 0x0a02000, 0x178000पूर्ण,	/* 10: SQM2*/
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु1, 0x0af0000, 0x0af2000, 0x17a000पूर्ण पूर्ण पूर्ण,
    अणुअणुअणु0, 0x0b00000, 0x0b02000, 0x17c000पूर्ण,	/* 11: SQM3*/
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
      अणु1, 0x0bf0000, 0x0bf2000, 0x17e000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0c00000, 0x0c04000, 0x1d4000पूर्ण पूर्ण पूर्ण,/* 12: I2Q */
	अणुअणुअणु1, 0x0d00000, 0x0d04000, 0x1a4000पूर्ण पूर्ण पूर्ण,/* 13: TMR */
	अणुअणुअणु1, 0x0e00000, 0x0e04000, 0x1a0000पूर्ण पूर्ण पूर्ण,/* 14: ROMUSB */
	अणुअणुअणु1, 0x0f00000, 0x0f01000, 0x164000पूर्ण पूर्ण पूर्ण,/* 15: PEG4 */
	अणुअणुअणु0, 0x1000000, 0x1004000, 0x1a8000पूर्ण पूर्ण पूर्ण,/* 16: XDMA */
	अणुअणुअणु1, 0x1100000, 0x1101000, 0x160000पूर्ण पूर्ण पूर्ण,/* 17: PEG0 */
	अणुअणुअणु1, 0x1200000, 0x1201000, 0x161000पूर्ण पूर्ण पूर्ण,/* 18: PEG1 */
	अणुअणुअणु1, 0x1300000, 0x1301000, 0x162000पूर्ण पूर्ण पूर्ण,/* 19: PEG2 */
	अणुअणुअणु1, 0x1400000, 0x1401000, 0x163000पूर्ण पूर्ण पूर्ण,/* 20: PEG3 */
	अणुअणुअणु1, 0x1500000, 0x1501000, 0x165000पूर्ण पूर्ण पूर्ण,/* 21: P2ND */
	अणुअणुअणु1, 0x1600000, 0x1601000, 0x166000पूर्ण पूर्ण पूर्ण,/* 22: P2NI */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 23: */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 24: */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 25: */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 26: */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 27: */
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,	/* 28: */
	अणुअणुअणु1, 0x1d00000, 0x1d10000, 0x190000पूर्ण पूर्ण पूर्ण,/* 29: MS */
    अणुअणुअणु1, 0x1e00000, 0x1e01000, 0x16a000पूर्ण पूर्ण पूर्ण,/* 30: P2NR2 */
    अणुअणुअणु1, 0x1f00000, 0x1f10000, 0x150000पूर्ण पूर्ण पूर्ण,/* 31: EPG */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 32: PCI */
	अणुअणुअणु1, 0x2100000, 0x2102000, 0x120000पूर्ण,	/* 33: PCIE */
	  अणु1, 0x2110000, 0x2120000, 0x130000पूर्ण,
	  अणु1, 0x2120000, 0x2122000, 0x124000पूर्ण,
	  अणु1, 0x2130000, 0x2132000, 0x126000पूर्ण,
	  अणु1, 0x2140000, 0x2142000, 0x128000पूर्ण,
	  अणु1, 0x2150000, 0x2152000, 0x12a000पूर्ण,
	  अणु1, 0x2160000, 0x2170000, 0x110000पूर्ण,
	  अणु1, 0x2170000, 0x2172000, 0x12e000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण,
	  अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2200000, 0x2204000, 0x1b0000पूर्ण पूर्ण पूर्ण,/* 34: CAM */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 35: */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 36: */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 37: */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 38: */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 39: */
	अणुअणुअणु1, 0x2800000, 0x2804000, 0x1a4000पूर्ण पूर्ण पूर्ण,/* 40: TMR */
	अणुअणुअणु1, 0x2900000, 0x2901000, 0x16b000पूर्ण पूर्ण पूर्ण,/* 41: P2NR3 */
	अणुअणुअणु1, 0x2a00000, 0x2a00400, 0x1ac400पूर्ण पूर्ण पूर्ण,/* 42: RPMX1 */
	अणुअणुअणु1, 0x2b00000, 0x2b00400, 0x1ac800पूर्ण पूर्ण पूर्ण,/* 43: RPMX2 */
	अणुअणुअणु1, 0x2c00000, 0x2c00400, 0x1acc00पूर्ण पूर्ण पूर्ण,/* 44: RPMX3 */
	अणुअणुअणु1, 0x2d00000, 0x2d00400, 0x1ad000पूर्ण पूर्ण पूर्ण,/* 45: RPMX4 */
	अणुअणुअणु1, 0x2e00000, 0x2e00400, 0x1ad400पूर्ण पूर्ण पूर्ण,/* 46: RPMX5 */
	अणुअणुअणु1, 0x2f00000, 0x2f00400, 0x1ad800पूर्ण पूर्ण पूर्ण,/* 47: RPMX6 */
	अणुअणुअणु1, 0x3000000, 0x3000400, 0x1adc00पूर्ण पूर्ण पूर्ण,/* 48: RPMX7 */
	अणुअणुअणु0, 0x3100000, 0x3104000, 0x1a8000पूर्ण पूर्ण पूर्ण,/* 49: XDMA */
	अणुअणुअणु1, 0x3200000, 0x3204000, 0x1d4000पूर्ण पूर्ण पूर्ण,/* 50: I2Q */
	अणुअणुअणु1, 0x3300000, 0x3304000, 0x1a0000पूर्ण पूर्ण पूर्ण,/* 51: ROMUSB */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 52: */
	अणुअणुअणु1, 0x3500000, 0x3500400, 0x1ac000पूर्ण पूर्ण पूर्ण,/* 53: RPMX0 */
	अणुअणुअणु1, 0x3600000, 0x3600400, 0x1ae000पूर्ण पूर्ण पूर्ण,/* 54: RPMX8 */
	अणुअणुअणु1, 0x3700000, 0x3700400, 0x1ae400पूर्ण पूर्ण पूर्ण,/* 55: RPMX9 */
	अणुअणुअणु1, 0x3800000, 0x3804000, 0x1d0000पूर्ण पूर्ण पूर्ण,/* 56: OCM0 */
	अणुअणुअणु1, 0x3900000, 0x3904000, 0x1b4000पूर्ण पूर्ण पूर्ण,/* 57: CRYPTO */
	अणुअणुअणु1, 0x3a00000, 0x3a04000, 0x1d8000पूर्ण पूर्ण पूर्ण,/* 58: SMB */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 59: I2C0 */
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,				/* 60: I2C1 */
	अणुअणुअणु1, 0x3d00000, 0x3d04000, 0x1d8000पूर्ण पूर्ण पूर्ण,/* 61: LPC */
	अणुअणुअणु1, 0x3e00000, 0x3e01000, 0x167000पूर्ण पूर्ण पूर्ण,/* 62: P2NC */
	अणुअणुअणु1, 0x3f00000, 0x3f01000, 0x168000पूर्ण पूर्ण पूर्ण	/* 63: P2NR0 */
पूर्ण;

/*
 * top 12 bits of crb पूर्णांकernal address (hub, agent)
 */
अटल अचिन्हित crb_hub_agt[64] =
अणु
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PS,
	NETXEN_HW_CRB_HUB_AGT_ADR_MN,
	NETXEN_HW_CRB_HUB_AGT_ADR_MS,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_SRE,
	NETXEN_HW_CRB_HUB_AGT_ADR_NIU,
	NETXEN_HW_CRB_HUB_AGT_ADR_QMN,
	NETXEN_HW_CRB_HUB_AGT_ADR_SQN0,
	NETXEN_HW_CRB_HUB_AGT_ADR_SQN1,
	NETXEN_HW_CRB_HUB_AGT_ADR_SQN2,
	NETXEN_HW_CRB_HUB_AGT_ADR_SQN3,
	NETXEN_HW_CRB_HUB_AGT_ADR_I2Q,
	NETXEN_HW_CRB_HUB_AGT_ADR_TIMR,
	NETXEN_HW_CRB_HUB_AGT_ADR_ROMUSB,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGN4,
	NETXEN_HW_CRB_HUB_AGT_ADR_XDMA,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGN0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGN1,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGN2,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGN3,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGND,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGNI,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGS0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGS1,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGS2,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGS3,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGSI,
	NETXEN_HW_CRB_HUB_AGT_ADR_SN,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_EG,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PS,
	NETXEN_HW_CRB_HUB_AGT_ADR_CAM,
	0,
	0,
	0,
	0,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_TIMR,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX1,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX2,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX3,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX4,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX5,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX6,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX7,
	NETXEN_HW_CRB_HUB_AGT_ADR_XDMA,
	NETXEN_HW_CRB_HUB_AGT_ADR_I2Q,
	NETXEN_HW_CRB_HUB_AGT_ADR_ROMUSB,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX0,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX8,
	NETXEN_HW_CRB_HUB_AGT_ADR_RPMX9,
	NETXEN_HW_CRB_HUB_AGT_ADR_OCM0,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_SMB,
	NETXEN_HW_CRB_HUB_AGT_ADR_I2C0,
	NETXEN_HW_CRB_HUB_AGT_ADR_I2C1,
	0,
	NETXEN_HW_CRB_HUB_AGT_ADR_PGNC,
	0,
पूर्ण;

/*  PCI Winकरोwing क्रम DDR regions.  */

#घोषणा NETXEN_WINDOW_ONE 	0x2000000 /*CRB Winकरोw: bit 25 of CRB address */

#घोषणा NETXEN_PCIE_SEM_TIMEOUT	10000

अटल पूर्णांक netxen_nic_set_mtu_xgb(काष्ठा netxen_adapter *adapter, पूर्णांक new_mtu);

पूर्णांक
netxen_pcie_sem_lock(काष्ठा netxen_adapter *adapter, पूर्णांक sem, u32 id_reg)
अणु
	पूर्णांक करोne = 0, समयout = 0;

	जबतक (!करोne) अणु
		करोne = NXRD32(adapter, NETXEN_PCIE_REG(PCIE_SEM_LOCK(sem)));
		अगर (करोne == 1)
			अवरोध;
		अगर (++समयout >= NETXEN_PCIE_SEM_TIMEOUT)
			वापस -EIO;
		msleep(1);
	पूर्ण

	अगर (id_reg)
		NXWR32(adapter, id_reg, adapter->portnum);

	वापस 0;
पूर्ण

व्योम
netxen_pcie_sem_unlock(काष्ठा netxen_adapter *adapter, पूर्णांक sem)
अणु
	NXRD32(adapter, NETXEN_PCIE_REG(PCIE_SEM_UNLOCK(sem)));
पूर्ण

अटल पूर्णांक netxen_niu_xg_init_port(काष्ठा netxen_adapter *adapter, पूर्णांक port)
अणु
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_1+(0x10000*port), 0x1447);
		NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0+(0x10000*port), 0x5);
	पूर्ण

	वापस 0;
पूर्ण

/* Disable an XG पूर्णांकerface */
अटल पूर्णांक netxen_niu_disable_xg_port(काष्ठा netxen_adapter *adapter)
अणु
	__u32 mac_cfg;
	u32 port = adapter->physical_port;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		वापस 0;

	अगर (port >= NETXEN_NIU_MAX_XG_PORTS)
		वापस -EINVAL;

	mac_cfg = 0;
	अगर (NXWR32(adapter,
			NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg))
		वापस -EIO;
	वापस 0;
पूर्ण

#घोषणा NETXEN_UNICAST_ADDR(port, index) \
	(NETXEN_UNICAST_ADDR_BASE+(port*32)+(index*8))
#घोषणा NETXEN_MCAST_ADDR(port, index) \
	(NETXEN_MULTICAST_ADDR_BASE+(port*0x80)+(index*8))
#घोषणा MAC_HI(addr) \
	((addr[2] << 16) | (addr[1] << 8) | (addr[0]))
#घोषणा MAC_LO(addr) \
	((addr[5] << 16) | (addr[4] << 8) | (addr[3]))

अटल पूर्णांक netxen_p2_nic_set_promisc(काष्ठा netxen_adapter *adapter, u32 mode)
अणु
	u32 mac_cfg;
	u32 cnt = 0;
	__u32 reg = 0x0200;
	u32 port = adapter->physical_port;
	u16 board_type = adapter->ahw.board_type;

	अगर (port >= NETXEN_NIU_MAX_XG_PORTS)
		वापस -EINVAL;

	mac_cfg = NXRD32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port));
	mac_cfg &= ~0x4;
	NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg);

	अगर ((board_type == NETXEN_BRDTYPE_P2_SB31_10G_IMEZ) ||
			(board_type == NETXEN_BRDTYPE_P2_SB31_10G_HMEZ))
		reg = (0x20 << port);

	NXWR32(adapter, NETXEN_NIU_FRAME_COUNT_SELECT, reg);

	mdelay(10);

	जबतक (NXRD32(adapter, NETXEN_NIU_FRAME_COUNT) && ++cnt < 20)
		mdelay(10);

	अगर (cnt < 20) अणु

		reg = NXRD32(adapter,
			NETXEN_NIU_XGE_CONFIG_1 + (0x10000 * port));

		अगर (mode == NETXEN_NIU_PROMISC_MODE)
			reg = (reg | 0x2000UL);
		अन्यथा
			reg = (reg & ~0x2000UL);

		अगर (mode == NETXEN_NIU_ALLMULTI_MODE)
			reg = (reg | 0x1000UL);
		अन्यथा
			reg = (reg & ~0x1000UL);

		NXWR32(adapter,
			NETXEN_NIU_XGE_CONFIG_1 + (0x10000 * port), reg);
	पूर्ण

	mac_cfg |= 0x4;
	NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक netxen_p2_nic_set_mac_addr(काष्ठा netxen_adapter *adapter, u8 *addr)
अणु
	u32 mac_hi, mac_lo;
	u32 reg_hi, reg_lo;

	u8 phy = adapter->physical_port;

	अगर (phy >= NETXEN_NIU_MAX_XG_PORTS)
		वापस -EINVAL;

	mac_lo = ((u32)addr[0] << 16) | ((u32)addr[1] << 24);
	mac_hi = addr[2] | ((u32)addr[3] << 8) |
		((u32)addr[4] << 16) | ((u32)addr[5] << 24);

	reg_lo = NETXEN_NIU_XGE_STATION_ADDR_0_1 + (0x10000 * phy);
	reg_hi = NETXEN_NIU_XGE_STATION_ADDR_0_HI + (0x10000 * phy);

	/* ग_लिखो twice to flush */
	अगर (NXWR32(adapter, reg_lo, mac_lo) || NXWR32(adapter, reg_hi, mac_hi))
		वापस -EIO;
	अगर (NXWR32(adapter, reg_lo, mac_lo) || NXWR32(adapter, reg_hi, mac_hi))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_enable_mcast_filter(काष्ठा netxen_adapter *adapter)
अणु
	u32	val = 0;
	u16 port = adapter->physical_port;
	u8 *addr = adapter->mac_addr;

	अगर (adapter->mc_enabled)
		वापस 0;

	val = NXRD32(adapter, NETXEN_MAC_ADDR_CNTL_REG);
	val |= (1UL << (28+port));
	NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);

	/* add broadcast addr to filter */
	val = 0xffffff;
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0), val);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0)+4, val);

	/* add station addr to filter */
	val = MAC_HI(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1), val);
	val = MAC_LO(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1)+4, val);

	adapter->mc_enabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_disable_mcast_filter(काष्ठा netxen_adapter *adapter)
अणु
	u32	val = 0;
	u16 port = adapter->physical_port;
	u8 *addr = adapter->mac_addr;

	अगर (!adapter->mc_enabled)
		वापस 0;

	val = NXRD32(adapter, NETXEN_MAC_ADDR_CNTL_REG);
	val &= ~(1UL << (28+port));
	NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);

	val = MAC_HI(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0), val);
	val = MAC_LO(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0)+4, val);

	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1), 0);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1)+4, 0);

	adapter->mc_enabled = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_set_mcast_addr(काष्ठा netxen_adapter *adapter,
		पूर्णांक index, u8 *addr)
अणु
	u32 hi = 0, lo = 0;
	u16 port = adapter->physical_port;

	lo = MAC_LO(addr);
	hi = MAC_HI(addr);

	NXWR32(adapter, NETXEN_MCAST_ADDR(port, index), hi);
	NXWR32(adapter, NETXEN_MCAST_ADDR(port, index)+4, lo);

	वापस 0;
पूर्ण

अटल व्योम netxen_p2_nic_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	u8 null_addr[ETH_ALEN];
	पूर्णांक i;

	eth_zero_addr(null_addr);

	अगर (netdev->flags & IFF_PROMISC) अणु

		adapter->set_promisc(adapter,
				NETXEN_NIU_PROMISC_MODE);

		/* Full promiscuous mode */
		netxen_nic_disable_mcast_filter(adapter);

		वापस;
	पूर्ण

	अगर (netdev_mc_empty(netdev)) अणु
		adapter->set_promisc(adapter,
				NETXEN_NIU_NON_PROMISC_MODE);
		netxen_nic_disable_mcast_filter(adapter);
		वापस;
	पूर्ण

	adapter->set_promisc(adapter, NETXEN_NIU_ALLMULTI_MODE);
	अगर (netdev->flags & IFF_ALLMULTI ||
			netdev_mc_count(netdev) > adapter->max_mc_count) अणु
		netxen_nic_disable_mcast_filter(adapter);
		वापस;
	पूर्ण

	netxen_nic_enable_mcast_filter(adapter);

	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev)
		netxen_nic_set_mcast_addr(adapter, i++, ha->addr);

	/* Clear out reमुख्यing addresses */
	जबतक (i < adapter->max_mc_count)
		netxen_nic_set_mcast_addr(adapter, i++, null_addr);
पूर्ण

अटल पूर्णांक
netxen_send_cmd_descs(काष्ठा netxen_adapter *adapter,
		काष्ठा cmd_desc_type0 *cmd_desc_arr, पूर्णांक nr_desc)
अणु
	u32 i, producer;
	काष्ठा netxen_cmd_buffer *pbuf;
	काष्ठा nx_host_tx_ring *tx_ring;

	i = 0;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस -EIO;

	tx_ring = adapter->tx_ring;
	__netअगर_tx_lock_bh(tx_ring->txq);

	producer = tx_ring->producer;

	अगर (nr_desc >= netxen_tx_avail(tx_ring)) अणु
		netअगर_tx_stop_queue(tx_ring->txq);
		smp_mb();
		अगर (netxen_tx_avail(tx_ring) > nr_desc) अणु
			अगर (netxen_tx_avail(tx_ring) > TX_STOP_THRESH)
				netअगर_tx_wake_queue(tx_ring->txq);
		पूर्ण अन्यथा अणु
			__netअगर_tx_unlock_bh(tx_ring->txq);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	करो अणु
		pbuf = &tx_ring->cmd_buf_arr[producer];
		pbuf->skb = शून्य;
		pbuf->frag_count = 0;

		स_नकल(&tx_ring->desc_head[producer],
			&cmd_desc_arr[i], माप(काष्ठा cmd_desc_type0));

		producer = get_next_index(producer, tx_ring->num_desc);
		i++;

	पूर्ण जबतक (i != nr_desc);

	tx_ring->producer = producer;

	netxen_nic_update_cmd_producer(adapter, tx_ring);

	__netअगर_tx_unlock_bh(tx_ring->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक
nx_p3_sre_macaddr_change(काष्ठा netxen_adapter *adapter, u8 *addr, अचिन्हित op)
अणु
	nx_nic_req_t req;
	nx_mac_req_t *mac_req;
	u64 word;

	स_रखो(&req, 0, माप(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_NIC_REQUEST << 23);

	word = NX_MAC_EVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	mac_req = (nx_mac_req_t *)&req.words[0];
	mac_req->op = op;
	स_नकल(mac_req->mac_addr, addr, ETH_ALEN);

	वापस netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
पूर्ण

अटल पूर्णांक nx_p3_nic_add_mac(काष्ठा netxen_adapter *adapter,
		स्थिर u8 *addr, काष्ठा list_head *del_list)
अणु
	काष्ठा list_head *head;
	nx_mac_list_t *cur;

	/* look up अगर alपढ़ोy exists */
	list_क्रम_each(head, del_list) अणु
		cur = list_entry(head, nx_mac_list_t, list);

		अगर (ether_addr_equal(addr, cur->mac_addr)) अणु
			list_move_tail(head, &adapter->mac_list);
			वापस 0;
		पूर्ण
	पूर्ण

	cur = kzalloc(माप(nx_mac_list_t), GFP_ATOMIC);
	अगर (cur == शून्य)
		वापस -ENOMEM;

	स_नकल(cur->mac_addr, addr, ETH_ALEN);
	list_add_tail(&cur->list, &adapter->mac_list);
	वापस nx_p3_sre_macaddr_change(adapter,
				cur->mac_addr, NETXEN_MAC_ADD);
पूर्ण

अटल व्योम netxen_p3_nic_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	u32 mode = VPORT_MISS_MODE_DROP;
	LIST_HEAD(del_list);
	काष्ठा list_head *head;
	nx_mac_list_t *cur;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस;

	list_splice_tail_init(&adapter->mac_list, &del_list);

	nx_p3_nic_add_mac(adapter, adapter->mac_addr, &del_list);
	nx_p3_nic_add_mac(adapter, bcast_addr, &del_list);

	अगर (netdev->flags & IFF_PROMISC) अणु
		mode = VPORT_MISS_MODE_ACCEPT_ALL;
		जाओ send_fw_cmd;
	पूर्ण

	अगर ((netdev->flags & IFF_ALLMULTI) ||
			(netdev_mc_count(netdev) > adapter->max_mc_count)) अणु
		mode = VPORT_MISS_MODE_ACCEPT_MULTI;
		जाओ send_fw_cmd;
	पूर्ण

	अगर (!netdev_mc_empty(netdev)) अणु
		netdev_क्रम_each_mc_addr(ha, netdev)
			nx_p3_nic_add_mac(adapter, ha->addr, &del_list);
	पूर्ण

send_fw_cmd:
	adapter->set_promisc(adapter, mode);
	head = &del_list;
	जबतक (!list_empty(head)) अणु
		cur = list_entry(head->next, nx_mac_list_t, list);

		nx_p3_sre_macaddr_change(adapter,
				cur->mac_addr, NETXEN_MAC_DEL);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

अटल पूर्णांक netxen_p3_nic_set_promisc(काष्ठा netxen_adapter *adapter, u32 mode)
अणु
	nx_nic_req_t req;
	u64 word;

	स_रखो(&req, 0, माप(nx_nic_req_t));

	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_PROXY_SET_VPORT_MISS_MODE |
			((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(mode);

	वापस netxen_send_cmd_descs(adapter,
				(काष्ठा cmd_desc_type0 *)&req, 1);
पूर्ण

व्योम netxen_p3_मुक्त_mac_list(काष्ठा netxen_adapter *adapter)
अणु
	nx_mac_list_t *cur;
	काष्ठा list_head *head = &adapter->mac_list;

	जबतक (!list_empty(head)) अणु
		cur = list_entry(head->next, nx_mac_list_t, list);
		nx_p3_sre_macaddr_change(adapter,
				cur->mac_addr, NETXEN_MAC_DEL);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

अटल पूर्णांक netxen_p3_nic_set_mac_addr(काष्ठा netxen_adapter *adapter, u8 *addr)
अणु
	/* assuming caller has alपढ़ोy copied new addr to netdev */
	netxen_p3_nic_set_multi(adapter->netdev);
	वापस 0;
पूर्ण

#घोषणा	NETXEN_CONFIG_INTR_COALESCE	3

/*
 * Send the पूर्णांकerrupt coalescing parameter set by ethtool to the card.
 */
पूर्णांक netxen_config_पूर्णांकr_coalesce(काष्ठा netxen_adapter *adapter)
अणु
	nx_nic_req_t req;
	u64 word[6];
	पूर्णांक rv, i;

	स_रखो(&req, 0, माप(nx_nic_req_t));
	स_रखो(word, 0, माप(word));

	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word[0] = NETXEN_CONFIG_INTR_COALESCE | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word[0]);

	स_नकल(&word[0], &adapter->coal, माप(adapter->coal));
	क्रम (i = 0; i < 6; i++)
		req.words[i] = cpu_to_le64(word[i]);

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "ERROR. Could not send "
			"interrupt coalescing parameters\n");
	पूर्ण

	वापस rv;
पूर्ण

पूर्णांक netxen_config_hw_lro(काष्ठा netxen_adapter *adapter, पूर्णांक enable)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक rv = 0;

	अगर (!test_bit(__NX_FW_ATTACHED, &adapter->state))
		वापस 0;

	स_रखो(&req, 0, माप(nx_nic_req_t));

	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_CONFIG_HW_LRO | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(enable);

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "ERROR. Could not send "
			"configure hw lro request\n");
	पूर्ण

	वापस rv;
पूर्ण

पूर्णांक netxen_config_bridged_mode(काष्ठा netxen_adapter *adapter, पूर्णांक enable)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक rv = 0;

	अगर (!!(adapter->flags & NETXEN_NIC_BRIDGE_ENABLED) == enable)
		वापस rv;

	स_रखो(&req, 0, माप(nx_nic_req_t));

	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_CONFIG_BRIDGING |
		((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(enable);

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "ERROR. Could not send "
				"configure bridge mode request\n");
	पूर्ण

	adapter->flags ^= NETXEN_NIC_BRIDGE_ENABLED;

	वापस rv;
पूर्ण


#घोषणा RSS_HASHTYPE_IP_TCP	0x3

पूर्णांक netxen_config_rss(काष्ठा netxen_adapter *adapter, पूर्णांक enable)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक i, rv;

	अटल स्थिर u64 key[] = अणु
		0xbeac01fa6a42b73bULL, 0x8030f20c77cb2da3ULL,
		0xae7b30b4d0ca2bcbULL, 0x43a38fb04167253dULL,
		0x255b0ec26d5a56daULL
	पूर्ण;


	स_रखो(&req, 0, माप(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_CONFIG_RSS | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	/*
	 * RSS request:
	 * bits 3-0: hash_method
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enable
	 *        9: use indirection table
	 *    47-10: reserved
	 *    63-48: indirection table mask
	 */
	word =  ((u64)(RSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u64)(RSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u64)(enable & 0x1) << 8) |
		((0x7ULL) << 48);
	req.words[0] = cpu_to_le64(word);
	क्रम (i = 0; i < ARRAY_SIZE(key); i++)
		req.words[i+1] = cpu_to_le64(key[i]);


	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: could not configure RSS\n",
				adapter->netdev->name);
	पूर्ण

	वापस rv;
पूर्ण

पूर्णांक netxen_config_ipaddr(काष्ठा netxen_adapter *adapter, __be32 ip, पूर्णांक cmd)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक rv;

	स_रखो(&req, 0, माप(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_CONFIG_IPADDR | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(cmd);
	स_नकल(&req.words[1], &ip, माप(u32));

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: could not notify %s IP 0x%x request\n",
				adapter->netdev->name,
				(cmd == NX_IP_UP) ? "Add" : "Remove", ip);
	पूर्ण
	वापस rv;
पूर्ण

पूर्णांक netxen_linkevent_request(काष्ठा netxen_adapter *adapter, पूर्णांक enable)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक rv;

	स_रखो(&req, 0, माप(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_GET_LINKEVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);
	req.words[0] = cpu_to_le64(enable | (enable << 8));

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: could not configure link notification\n",
				adapter->netdev->name);
	पूर्ण

	वापस rv;
पूर्ण

पूर्णांक netxen_send_lro_cleanup(काष्ठा netxen_adapter *adapter)
अणु
	nx_nic_req_t req;
	u64 word;
	पूर्णांक rv;

	अगर (!test_bit(__NX_FW_ATTACHED, &adapter->state))
		वापस 0;

	स_रखो(&req, 0, माप(nx_nic_req_t));
	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_LRO_REQUEST |
		((u64)adapter->portnum << 16) |
		((u64)NX_NIC_LRO_REQUEST_CLEANUP << 56) ;

	req.req_hdr = cpu_to_le64(word);

	rv = netxen_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: could not cleanup lro flows\n",
				adapter->netdev->name);
	पूर्ण
	वापस rv;
पूर्ण

/*
 * netxen_nic_change_mtu - Change the Maximum Transfer Unit
 * @वापसs 0 on success, negative on failure
 */

#घोषणा MTU_FUDGE_FACTOR	100

पूर्णांक netxen_nic_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	अगर (adapter->set_mtu)
		rc = adapter->set_mtu(adapter, mtu);

	अगर (!rc)
		netdev->mtu = mtu;

	वापस rc;
पूर्ण

अटल पूर्णांक netxen_get_flash_block(काष्ठा netxen_adapter *adapter, पूर्णांक base,
				  पूर्णांक size, __le32 * buf)
अणु
	पूर्णांक i, v, addr;
	__le32 *ptr32;
	पूर्णांक ret;

	addr = base;
	ptr32 = buf;
	क्रम (i = 0; i < size / माप(u32); i++) अणु
		ret = netxen_rom_fast_पढ़ो(adapter, addr, &v);
		अगर (ret)
			वापस ret;

		*ptr32 = cpu_to_le32(v);
		ptr32++;
		addr += माप(u32);
	पूर्ण
	अगर ((अक्षर *)buf + size > (अक्षर *)ptr32) अणु
		__le32 local;
		ret = netxen_rom_fast_पढ़ो(adapter, addr, &v);
		अगर (ret)
			वापस ret;
		local = cpu_to_le32(v);
		स_नकल(ptr32, &local, (अक्षर *)buf + size - (अक्षर *)ptr32);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक netxen_get_flash_mac_addr(काष्ठा netxen_adapter *adapter, u64 *mac)
अणु
	__le32 *pmac = (__le32 *) mac;
	u32 offset;

	offset = NX_FW_MAC_ADDR_OFFSET + (adapter->portnum * माप(u64));

	अगर (netxen_get_flash_block(adapter, offset, माप(u64), pmac) == -1)
		वापस -1;

	अगर (*mac == ~0ULL) अणु

		offset = NX_OLD_MAC_ADDR_OFFSET +
			(adapter->portnum * माप(u64));

		अगर (netxen_get_flash_block(adapter,
					offset, माप(u64), pmac) == -1)
			वापस -1;

		अगर (*mac == ~0ULL)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक netxen_p3_get_mac_addr(काष्ठा netxen_adapter *adapter, u64 *mac)
अणु
	uपूर्णांक32_t crbaddr, mac_hi, mac_lo;
	पूर्णांक pci_func = adapter->ahw.pci_func;

	crbaddr = CRB_MAC_BLOCK_START +
		(4 * ((pci_func/2) * 3)) + (4 * (pci_func & 1));

	mac_lo = NXRD32(adapter, crbaddr);
	mac_hi = NXRD32(adapter, crbaddr+4);

	अगर (pci_func & 1)
		*mac = le64_to_cpu((mac_lo >> 16) | ((u64)mac_hi << 16));
	अन्यथा
		*mac = le64_to_cpu((u64)mac_lo | ((u64)mac_hi << 32));

	वापस 0;
पूर्ण

/*
 * Changes the CRB winकरोw to the specअगरied winकरोw.
 */
अटल व्योम
netxen_nic_pci_set_crbwinकरोw_128M(काष्ठा netxen_adapter *adapter,
		u32 winकरोw)
अणु
	व्योम __iomem *offset;
	पूर्णांक count = 10;
	u8 func = adapter->ahw.pci_func;

	अगर (adapter->ahw.crb_win == winकरोw)
		वापस;

	offset = PCI_OFFSET_SECOND_RANGE(adapter,
			NETXEN_PCIX_PH_REG(PCIE_CRB_WINDOW_REG(func)));

	ग_लिखोl(winकरोw, offset);
	करो अणु
		अगर (winकरोw == पढ़ोl(offset))
			अवरोध;

		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&adapter->pdev->dev,
					"failed to set CRB window to %d\n",
					(winकरोw == NETXEN_WINDOW_ONE));
		udelay(1);

	पूर्ण जबतक (--count > 0);

	अगर (count > 0)
		adapter->ahw.crb_win = winकरोw;
पूर्ण

/*
 * Returns < 0 अगर off is not valid,
 *	 1 अगर winकरोw access is needed. 'off' is set to offset from
 *	   CRB space in 128M pci map
 *	 0 अगर no winकरोw access is needed. 'off' is set to 2M addr
 * In: 'off' is offset from base in 128M pci map
 */
अटल पूर्णांक
netxen_nic_pci_get_crb_addr_2M(काष्ठा netxen_adapter *adapter,
		uदीर्घ off, व्योम __iomem **addr)
अणु
	crb_128M_2M_sub_block_map_t *m;


	अगर ((off >= NETXEN_CRB_MAX) || (off < NETXEN_PCI_CRBSPACE))
		वापस -EINVAL;

	off -= NETXEN_PCI_CRBSPACE;

	/*
	 * Try direct map
	 */
	m = &crb_128M_2M_map[CRB_BLK(off)].sub_block[CRB_SUBBLK(off)];

	अगर (m->valid && (m->start_128M <= off) && (m->end_128M > off)) अणु
		*addr = adapter->ahw.pci_base0 + m->start_2M +
			(off - m->start_128M);
		वापस 0;
	पूर्ण

	/*
	 * Not in direct map, use crb winकरोw
	 */
	*addr = adapter->ahw.pci_base0 + CRB_INसूचीECT_2M +
		(off & MASK(16));
	वापस 1;
पूर्ण

/*
 * In: 'off' is offset from CRB space in 128M pci map
 * Out: 'off' is 2M pci map addr
 * side effect: lock crb winकरोw
 */
अटल व्योम
netxen_nic_pci_set_crbwinकरोw_2M(काष्ठा netxen_adapter *adapter, uदीर्घ off)
अणु
	u32 winकरोw;
	व्योम __iomem *addr = adapter->ahw.pci_base0 + CRB_WINDOW_2M;

	off -= NETXEN_PCI_CRBSPACE;

	winकरोw = CRB_HI(off);

	ग_लिखोl(winकरोw, addr);
	अगर (पढ़ोl(addr) != winकरोw) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&adapter->pdev->dev,
				"failed to set CRB window to %d off 0x%lx\n",
				winकरोw, off);
	पूर्ण
पूर्ण

अटल व्योम __iomem *
netxen_nic_map_indirect_address_128M(काष्ठा netxen_adapter *adapter,
		uदीर्घ win_off, व्योम __iomem **mem_ptr)
अणु
	uदीर्घ off = win_off;
	व्योम __iomem *addr;
	resource_माप_प्रकार mem_base;

	अगर (ADDR_IN_WINDOW1(win_off))
		off = NETXEN_CRB_NORMAL(win_off);

	addr = pci_base_offset(adapter, off);
	अगर (addr)
		वापस addr;

	अगर (adapter->ahw.pci_len0 == 0)
		off -= NETXEN_PCI_CRBSPACE;

	mem_base = pci_resource_start(adapter->pdev, 0);
	*mem_ptr = ioremap(mem_base + (off & PAGE_MASK), PAGE_SIZE);
	अगर (*mem_ptr)
		addr = *mem_ptr + (off & (PAGE_SIZE - 1));

	वापस addr;
पूर्ण

अटल पूर्णांक
netxen_nic_hw_ग_लिखो_wx_128M(काष्ठा netxen_adapter *adapter, uदीर्घ off, u32 data)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr, *mem_ptr = शून्य;

	addr = netxen_nic_map_indirect_address_128M(adapter, off, &mem_ptr);
	अगर (!addr)
		वापस -EIO;

	अगर (ADDR_IN_WINDOW1(off)) अणु /* Winकरोw 1 */
		netxen_nic_io_ग_लिखो_128M(adapter, addr, data);
	पूर्ण अन्यथा अणु        /* Winकरोw 0 */
		ग_लिखो_lock_irqsave(&adapter->ahw.crb_lock, flags);
		netxen_nic_pci_set_crbwinकरोw_128M(adapter, 0);
		ग_लिखोl(data, addr);
		netxen_nic_pci_set_crbwinकरोw_128M(adapter,
				NETXEN_WINDOW_ONE);
		ग_लिखो_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
	पूर्ण

	अगर (mem_ptr)
		iounmap(mem_ptr);

	वापस 0;
पूर्ण

अटल u32
netxen_nic_hw_पढ़ो_wx_128M(काष्ठा netxen_adapter *adapter, uदीर्घ off)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr, *mem_ptr = शून्य;
	u32 data;

	addr = netxen_nic_map_indirect_address_128M(adapter, off, &mem_ptr);
	अगर (!addr)
		वापस -EIO;

	अगर (ADDR_IN_WINDOW1(off)) अणु /* Winकरोw 1 */
		data = netxen_nic_io_पढ़ो_128M(adapter, addr);
	पूर्ण अन्यथा अणु        /* Winकरोw 0 */
		ग_लिखो_lock_irqsave(&adapter->ahw.crb_lock, flags);
		netxen_nic_pci_set_crbwinकरोw_128M(adapter, 0);
		data = पढ़ोl(addr);
		netxen_nic_pci_set_crbwinकरोw_128M(adapter,
				NETXEN_WINDOW_ONE);
		ग_लिखो_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
	पूर्ण

	अगर (mem_ptr)
		iounmap(mem_ptr);

	वापस data;
पूर्ण

अटल पूर्णांक
netxen_nic_hw_ग_लिखो_wx_2M(काष्ठा netxen_adapter *adapter, uदीर्घ off, u32 data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;
	व्योम __iomem *addr = शून्य;

	rv = netxen_nic_pci_get_crb_addr_2M(adapter, off, &addr);

	अगर (rv == 0) अणु
		ग_लिखोl(data, addr);
		वापस 0;
	पूर्ण

	अगर (rv > 0) अणु
		/* indirect access */
		ग_लिखो_lock_irqsave(&adapter->ahw.crb_lock, flags);
		crb_win_lock(adapter);
		netxen_nic_pci_set_crbwinकरोw_2M(adapter, off);
		ग_लिखोl(data, addr);
		crb_win_unlock(adapter);
		ग_लिखो_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
		वापस 0;
	पूर्ण

	dev_err(&adapter->pdev->dev,
			"%s: invalid offset: 0x%016lx\n", __func__, off);
	dump_stack();
	वापस -EIO;
पूर्ण

अटल u32
netxen_nic_hw_पढ़ो_wx_2M(काष्ठा netxen_adapter *adapter, uदीर्घ off)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;
	u32 data;
	व्योम __iomem *addr = शून्य;

	rv = netxen_nic_pci_get_crb_addr_2M(adapter, off, &addr);

	अगर (rv == 0)
		वापस पढ़ोl(addr);

	अगर (rv > 0) अणु
		/* indirect access */
		ग_लिखो_lock_irqsave(&adapter->ahw.crb_lock, flags);
		crb_win_lock(adapter);
		netxen_nic_pci_set_crbwinकरोw_2M(adapter, off);
		data = पढ़ोl(addr);
		crb_win_unlock(adapter);
		ग_लिखो_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
		वापस data;
	पूर्ण

	dev_err(&adapter->pdev->dev,
			"%s: invalid offset: 0x%016lx\n", __func__, off);
	dump_stack();
	वापस -1;
पूर्ण

/* winकरोw 1 रेजिस्टरs only */
अटल व्योम netxen_nic_io_ग_लिखो_128M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr, u32 data)
अणु
	पढ़ो_lock(&adapter->ahw.crb_lock);
	ग_लिखोl(data, addr);
	पढ़ो_unlock(&adapter->ahw.crb_lock);
पूर्ण

अटल u32 netxen_nic_io_पढ़ो_128M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr)
अणु
	u32 val;

	पढ़ो_lock(&adapter->ahw.crb_lock);
	val = पढ़ोl(addr);
	पढ़ो_unlock(&adapter->ahw.crb_lock);

	वापस val;
पूर्ण

अटल व्योम netxen_nic_io_ग_लिखो_2M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr, u32 data)
अणु
	ग_लिखोl(data, addr);
पूर्ण

अटल u32 netxen_nic_io_पढ़ो_2M(काष्ठा netxen_adapter *adapter,
		व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण

व्योम __iomem *
netxen_get_ioaddr(काष्ठा netxen_adapter *adapter, u32 offset)
अणु
	व्योम __iomem *addr = शून्य;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		अगर ((offset < NETXEN_CRB_PCIX_HOST2) &&
				(offset > NETXEN_CRB_PCIX_HOST))
			addr = PCI_OFFSET_SECOND_RANGE(adapter, offset);
		अन्यथा
			addr = NETXEN_CRB_NORMALIZE(adapter, offset);
	पूर्ण अन्यथा अणु
		WARN_ON(netxen_nic_pci_get_crb_addr_2M(adapter,
					offset, &addr));
	पूर्ण

	वापस addr;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_set_winकरोw_128M(काष्ठा netxen_adapter *adapter,
		u64 addr, u32 *start)
अणु
	अगर (ADDR_IN_RANGE(addr, NETXEN_ADDR_OCM0, NETXEN_ADDR_OCM0_MAX)) अणु
		*start = (addr - NETXEN_ADDR_OCM0  + NETXEN_PCI_OCM0);
		वापस 0;
	पूर्ण अन्यथा अगर (ADDR_IN_RANGE(addr,
				NETXEN_ADDR_OCM1, NETXEN_ADDR_OCM1_MAX)) अणु
		*start = (addr - NETXEN_ADDR_OCM1 + NETXEN_PCI_OCM1);
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_set_winकरोw_2M(काष्ठा netxen_adapter *adapter,
		u64 addr, u32 *start)
अणु
	u32 winकरोw;

	winकरोw = OCM_WIN(addr);

	ग_लिखोl(winकरोw, adapter->ahw.ocm_win_crb);
	/* पढ़ो back to flush */
	पढ़ोl(adapter->ahw.ocm_win_crb);

	adapter->ahw.ocm_win = winकरोw;
	*start = NETXEN_PCI_OCM0_2M + GET_MEM_OFFS_2M(addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_mem_access_direct(काष्ठा netxen_adapter *adapter, u64 off,
		u64 *data, पूर्णांक op)
अणु
	व्योम __iomem *addr, *mem_ptr = शून्य;
	resource_माप_प्रकार mem_base;
	पूर्णांक ret;
	u32 start;

	spin_lock(&adapter->ahw.mem_lock);

	ret = adapter->pci_set_winकरोw(adapter, off, &start);
	अगर (ret != 0)
		जाओ unlock;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		addr = adapter->ahw.pci_base0 + start;
	पूर्ण अन्यथा अणु
		addr = pci_base_offset(adapter, start);
		अगर (addr)
			जाओ noremap;

		mem_base = pci_resource_start(adapter->pdev, 0) +
					(start & PAGE_MASK);
		mem_ptr = ioremap(mem_base, PAGE_SIZE);
		अगर (mem_ptr == शून्य) अणु
			ret = -EIO;
			जाओ unlock;
		पूर्ण

		addr = mem_ptr + (start & (PAGE_SIZE-1));
	पूर्ण
noremap:
	अगर (op == 0)	/* पढ़ो */
		*data = पढ़ोq(addr);
	अन्यथा		/* ग_लिखो */
		ग_लिखोq(*data, addr);

unlock:
	spin_unlock(&adapter->ahw.mem_lock);

	अगर (mem_ptr)
		iounmap(mem_ptr);
	वापस ret;
पूर्ण

व्योम
netxen_pci_camqm_पढ़ो_2M(काष्ठा netxen_adapter *adapter, u64 off, u64 *data)
अणु
	व्योम __iomem *addr = adapter->ahw.pci_base0 +
		NETXEN_PCI_CAMQM_2M_BASE + (off - NETXEN_PCI_CAMQM);

	spin_lock(&adapter->ahw.mem_lock);
	*data = पढ़ोq(addr);
	spin_unlock(&adapter->ahw.mem_lock);
पूर्ण

व्योम
netxen_pci_camqm_ग_लिखो_2M(काष्ठा netxen_adapter *adapter, u64 off, u64 data)
अणु
	व्योम __iomem *addr = adapter->ahw.pci_base0 +
		NETXEN_PCI_CAMQM_2M_BASE + (off - NETXEN_PCI_CAMQM);

	spin_lock(&adapter->ahw.mem_lock);
	ग_लिखोq(data, addr);
	spin_unlock(&adapter->ahw.mem_lock);
पूर्ण

#घोषणा MAX_CTL_CHECK   1000

अटल पूर्णांक
netxen_nic_pci_mem_ग_लिखो_128M(काष्ठा netxen_adapter *adapter,
		u64 off, u64 data)
अणु
	पूर्णांक j, ret;
	u32 temp, off_lo, off_hi, addr_hi, data_hi, data_lo;
	व्योम __iomem *mem_crb;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;

	/* P2 has dअगरferent SIU and MIU test agent base addr */
	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_QDR_NET,
				NETXEN_ADDR_QDR_NET_MAX_P2)) अणु
		mem_crb = pci_base_offset(adapter,
				NETXEN_CRB_QDR_NET+SIU_TEST_AGT_BASE);
		addr_hi = SIU_TEST_AGT_ADDR_HI;
		data_lo = SIU_TEST_AGT_WRDATA_LO;
		data_hi = SIU_TEST_AGT_WRDATA_HI;
		off_lo = off & SIU_TEST_AGT_ADDR_MASK;
		off_hi = SIU_TEST_AGT_UPPER_ADDR(off);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_DDR_NET, NETXEN_ADDR_DDR_NET_MAX)) अणु
		mem_crb = pci_base_offset(adapter,
				NETXEN_CRB_DDR_NET+MIU_TEST_AGT_BASE);
		addr_hi = MIU_TEST_AGT_ADDR_HI;
		data_lo = MIU_TEST_AGT_WRDATA_LO;
		data_hi = MIU_TEST_AGT_WRDATA_HI;
		off_lo = off & MIU_TEST_AGT_ADDR_MASK;
		off_hi = 0;
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_OCM0, NETXEN_ADDR_OCM0_MAX) ||
		ADDR_IN_RANGE(off, NETXEN_ADDR_OCM1, NETXEN_ADDR_OCM1_MAX)) अणु
		अगर (adapter->ahw.pci_len0 != 0) अणु
			वापस netxen_nic_pci_mem_access_direct(adapter,
					off, &data, 1);
		पूर्ण
	पूर्ण

	वापस -EIO;

correct:
	spin_lock(&adapter->ahw.mem_lock);
	netxen_nic_pci_set_crbwinकरोw_128M(adapter, 0);

	ग_लिखोl(off_lo, (mem_crb + MIU_TEST_AGT_ADDR_LO));
	ग_लिखोl(off_hi, (mem_crb + addr_hi));
	ग_लिखोl(data & 0xffffffff, (mem_crb + data_lo));
	ग_लिखोl((data >> 32) & 0xffffffff, (mem_crb + data_hi));
	ग_लिखोl((TA_CTL_ENABLE | TA_CTL_WRITE), (mem_crb + TEST_AGT_CTRL));
	ग_लिखोl((TA_CTL_START | TA_CTL_ENABLE | TA_CTL_WRITE),
			(mem_crb + TEST_AGT_CTRL));

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = पढ़ोl((mem_crb + TEST_AGT_CTRL));
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&adapter->pdev->dev,
					"failed to write through agent\n");
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	netxen_nic_pci_set_crbwinकरोw_128M(adapter, NETXEN_WINDOW_ONE);
	spin_unlock(&adapter->ahw.mem_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_mem_पढ़ो_128M(काष्ठा netxen_adapter *adapter,
		u64 off, u64 *data)
अणु
	पूर्णांक j, ret;
	u32 temp, off_lo, off_hi, addr_hi, data_hi, data_lo;
	u64 val;
	व्योम __iomem *mem_crb;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;

	/* P2 has dअगरferent SIU and MIU test agent base addr */
	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_QDR_NET,
				NETXEN_ADDR_QDR_NET_MAX_P2)) अणु
		mem_crb = pci_base_offset(adapter,
				NETXEN_CRB_QDR_NET+SIU_TEST_AGT_BASE);
		addr_hi = SIU_TEST_AGT_ADDR_HI;
		data_lo = SIU_TEST_AGT_RDDATA_LO;
		data_hi = SIU_TEST_AGT_RDDATA_HI;
		off_lo = off & SIU_TEST_AGT_ADDR_MASK;
		off_hi = SIU_TEST_AGT_UPPER_ADDR(off);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_DDR_NET, NETXEN_ADDR_DDR_NET_MAX)) अणु
		mem_crb = pci_base_offset(adapter,
				NETXEN_CRB_DDR_NET+MIU_TEST_AGT_BASE);
		addr_hi = MIU_TEST_AGT_ADDR_HI;
		data_lo = MIU_TEST_AGT_RDDATA_LO;
		data_hi = MIU_TEST_AGT_RDDATA_HI;
		off_lo = off & MIU_TEST_AGT_ADDR_MASK;
		off_hi = 0;
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_OCM0, NETXEN_ADDR_OCM0_MAX) ||
		ADDR_IN_RANGE(off, NETXEN_ADDR_OCM1, NETXEN_ADDR_OCM1_MAX)) अणु
		अगर (adapter->ahw.pci_len0 != 0) अणु
			वापस netxen_nic_pci_mem_access_direct(adapter,
					off, data, 0);
		पूर्ण
	पूर्ण

	वापस -EIO;

correct:
	spin_lock(&adapter->ahw.mem_lock);
	netxen_nic_pci_set_crbwinकरोw_128M(adapter, 0);

	ग_लिखोl(off_lo, (mem_crb + MIU_TEST_AGT_ADDR_LO));
	ग_लिखोl(off_hi, (mem_crb + addr_hi));
	ग_लिखोl(TA_CTL_ENABLE, (mem_crb + TEST_AGT_CTRL));
	ग_लिखोl((TA_CTL_START|TA_CTL_ENABLE), (mem_crb + TEST_AGT_CTRL));

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = पढ़ोl(mem_crb + TEST_AGT_CTRL);
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
		ret = -EIO;
	पूर्ण अन्यथा अणु

		temp = पढ़ोl(mem_crb + data_hi);
		val = ((u64)temp << 32);
		val |= पढ़ोl(mem_crb + data_lo);
		*data = val;
		ret = 0;
	पूर्ण

	netxen_nic_pci_set_crbwinकरोw_128M(adapter, NETXEN_WINDOW_ONE);
	spin_unlock(&adapter->ahw.mem_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_mem_ग_लिखो_2M(काष्ठा netxen_adapter *adapter,
		u64 off, u64 data)
अणु
	पूर्णांक j, ret;
	u32 temp, off8;
	व्योम __iomem *mem_crb;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;

	/* P3 onward, test agent base क्रम MIU and SIU is same */
	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_QDR_NET,
				NETXEN_ADDR_QDR_NET_MAX_P3)) अणु
		mem_crb = netxen_get_ioaddr(adapter,
				NETXEN_CRB_QDR_NET+MIU_TEST_AGT_BASE);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_DDR_NET, NETXEN_ADDR_DDR_NET_MAX)) अणु
		mem_crb = netxen_get_ioaddr(adapter,
				NETXEN_CRB_DDR_NET+MIU_TEST_AGT_BASE);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_OCM0, NETXEN_ADDR_OCM0_MAX))
		वापस netxen_nic_pci_mem_access_direct(adapter, off, &data, 1);

	वापस -EIO;

correct:
	off8 = off & 0xfffffff8;

	spin_lock(&adapter->ahw.mem_lock);

	ग_लिखोl(off8, (mem_crb + MIU_TEST_AGT_ADDR_LO));
	ग_लिखोl(0, (mem_crb + MIU_TEST_AGT_ADDR_HI));

	ग_लिखोl(data & 0xffffffff,
			mem_crb + MIU_TEST_AGT_WRDATA_LO);
	ग_लिखोl((data >> 32) & 0xffffffff,
			mem_crb + MIU_TEST_AGT_WRDATA_HI);

	ग_लिखोl((TA_CTL_ENABLE | TA_CTL_WRITE), (mem_crb + TEST_AGT_CTRL));
	ग_लिखोl((TA_CTL_START | TA_CTL_ENABLE | TA_CTL_WRITE),
			(mem_crb + TEST_AGT_CTRL));

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = पढ़ोl(mem_crb + TEST_AGT_CTRL);
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&adapter->pdev->dev,
					"failed to write through agent\n");
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	spin_unlock(&adapter->ahw.mem_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
netxen_nic_pci_mem_पढ़ो_2M(काष्ठा netxen_adapter *adapter,
		u64 off, u64 *data)
अणु
	पूर्णांक j, ret;
	u32 temp, off8;
	u64 val;
	व्योम __iomem *mem_crb;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;

	/* P3 onward, test agent base क्रम MIU and SIU is same */
	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_QDR_NET,
				NETXEN_ADDR_QDR_NET_MAX_P3)) अणु
		mem_crb = netxen_get_ioaddr(adapter,
				NETXEN_CRB_QDR_NET+MIU_TEST_AGT_BASE);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_DDR_NET, NETXEN_ADDR_DDR_NET_MAX)) अणु
		mem_crb = netxen_get_ioaddr(adapter,
				NETXEN_CRB_DDR_NET+MIU_TEST_AGT_BASE);
		जाओ correct;
	पूर्ण

	अगर (ADDR_IN_RANGE(off, NETXEN_ADDR_OCM0, NETXEN_ADDR_OCM0_MAX)) अणु
		वापस netxen_nic_pci_mem_access_direct(adapter,
				off, data, 0);
	पूर्ण

	वापस -EIO;

correct:
	off8 = off & 0xfffffff8;

	spin_lock(&adapter->ahw.mem_lock);

	ग_लिखोl(off8, (mem_crb + MIU_TEST_AGT_ADDR_LO));
	ग_लिखोl(0, (mem_crb + MIU_TEST_AGT_ADDR_HI));
	ग_लिखोl(TA_CTL_ENABLE, (mem_crb + TEST_AGT_CTRL));
	ग_लिखोl((TA_CTL_START | TA_CTL_ENABLE), (mem_crb + TEST_AGT_CTRL));

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = पढ़ोl(mem_crb + TEST_AGT_CTRL);
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
		ret = -EIO;
	पूर्ण अन्यथा अणु
		val = (u64)(पढ़ोl(mem_crb + MIU_TEST_AGT_RDDATA_HI)) << 32;
		val |= पढ़ोl(mem_crb + MIU_TEST_AGT_RDDATA_LO);
		*data = val;
		ret = 0;
	पूर्ण

	spin_unlock(&adapter->ahw.mem_lock);

	वापस ret;
पूर्ण

व्योम
netxen_setup_hwops(काष्ठा netxen_adapter *adapter)
अणु
	adapter->init_port = netxen_niu_xg_init_port;
	adapter->stop_port = netxen_niu_disable_xg_port;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		adapter->crb_पढ़ो = netxen_nic_hw_पढ़ो_wx_128M,
		adapter->crb_ग_लिखो = netxen_nic_hw_ग_लिखो_wx_128M,
		adapter->pci_set_winकरोw = netxen_nic_pci_set_winकरोw_128M,
		adapter->pci_mem_पढ़ो = netxen_nic_pci_mem_पढ़ो_128M,
		adapter->pci_mem_ग_लिखो = netxen_nic_pci_mem_ग_लिखो_128M,
		adapter->io_पढ़ो = netxen_nic_io_पढ़ो_128M,
		adapter->io_ग_लिखो = netxen_nic_io_ग_लिखो_128M,

		adapter->macaddr_set = netxen_p2_nic_set_mac_addr;
		adapter->set_multi = netxen_p2_nic_set_multi;
		adapter->set_mtu = netxen_nic_set_mtu_xgb;
		adapter->set_promisc = netxen_p2_nic_set_promisc;

	पूर्ण अन्यथा अणु
		adapter->crb_पढ़ो = netxen_nic_hw_पढ़ो_wx_2M,
		adapter->crb_ग_लिखो = netxen_nic_hw_ग_लिखो_wx_2M,
		adapter->pci_set_winकरोw = netxen_nic_pci_set_winकरोw_2M,
		adapter->pci_mem_पढ़ो = netxen_nic_pci_mem_पढ़ो_2M,
		adapter->pci_mem_ग_लिखो = netxen_nic_pci_mem_ग_लिखो_2M,
		adapter->io_पढ़ो = netxen_nic_io_पढ़ो_2M,
		adapter->io_ग_लिखो = netxen_nic_io_ग_लिखो_2M,

		adapter->set_mtu = nx_fw_cmd_set_mtu;
		adapter->set_promisc = netxen_p3_nic_set_promisc;
		adapter->macaddr_set = netxen_p3_nic_set_mac_addr;
		adapter->set_multi = netxen_p3_nic_set_multi;

		adapter->phy_पढ़ो = nx_fw_cmd_query_phy;
		adapter->phy_ग_लिखो = nx_fw_cmd_set_phy;
	पूर्ण
पूर्ण

पूर्णांक netxen_nic_get_board_info(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक offset, board_type, magic;
	काष्ठा pci_dev *pdev = adapter->pdev;

	offset = NX_FW_MAGIC_OFFSET;
	अगर (netxen_rom_fast_पढ़ो(adapter, offset, &magic))
		वापस -EIO;

	अगर (magic != NETXEN_BDINFO_MAGIC) अणु
		dev_err(&pdev->dev, "invalid board config, magic=%08x\n",
			magic);
		वापस -EIO;
	पूर्ण

	offset = NX_BRDTYPE_OFFSET;
	अगर (netxen_rom_fast_पढ़ो(adapter, offset, &board_type))
		वापस -EIO;

	अगर (board_type == NETXEN_BRDTYPE_P3_4_GB_MM) अणु
		u32 gpio = NXRD32(adapter, NETXEN_ROMUSB_GLB_PAD_GPIO_I);
		अगर ((gpio & 0x8000) == 0)
			board_type = NETXEN_BRDTYPE_P3_10G_TP;
	पूर्ण

	adapter->ahw.board_type = board_type;

	चयन (board_type) अणु
	हाल NETXEN_BRDTYPE_P2_SB35_4G:
		adapter->ahw.port_type = NETXEN_NIC_GBE;
		अवरोध;
	हाल NETXEN_BRDTYPE_P2_SB31_10G:
	हाल NETXEN_BRDTYPE_P2_SB31_10G_IMEZ:
	हाल NETXEN_BRDTYPE_P2_SB31_10G_HMEZ:
	हाल NETXEN_BRDTYPE_P2_SB31_10G_CX4:
	हाल NETXEN_BRDTYPE_P3_HMEZ:
	हाल NETXEN_BRDTYPE_P3_XG_LOM:
	हाल NETXEN_BRDTYPE_P3_10G_CX4:
	हाल NETXEN_BRDTYPE_P3_10G_CX4_LP:
	हाल NETXEN_BRDTYPE_P3_IMEZ:
	हाल NETXEN_BRDTYPE_P3_10G_SFP_PLUS:
	हाल NETXEN_BRDTYPE_P3_10G_SFP_CT:
	हाल NETXEN_BRDTYPE_P3_10G_SFP_QT:
	हाल NETXEN_BRDTYPE_P3_10G_XFP:
	हाल NETXEN_BRDTYPE_P3_10000_BASE_T:
		adapter->ahw.port_type = NETXEN_NIC_XGBE;
		अवरोध;
	हाल NETXEN_BRDTYPE_P1_BD:
	हाल NETXEN_BRDTYPE_P1_SB:
	हाल NETXEN_BRDTYPE_P1_SMAX:
	हाल NETXEN_BRDTYPE_P1_SOCK:
	हाल NETXEN_BRDTYPE_P3_REF_QG:
	हाल NETXEN_BRDTYPE_P3_4_GB:
	हाल NETXEN_BRDTYPE_P3_4_GB_MM:
		adapter->ahw.port_type = NETXEN_NIC_GBE;
		अवरोध;
	हाल NETXEN_BRDTYPE_P3_10G_TP:
		adapter->ahw.port_type = (adapter->portnum < 2) ?
			NETXEN_NIC_XGBE : NETXEN_NIC_GBE;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unknown board type %x\n", board_type);
		adapter->ahw.port_type = NETXEN_NIC_XGBE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* NIU access sections */
अटल पूर्णांक netxen_nic_set_mtu_xgb(काष्ठा netxen_adapter *adapter, पूर्णांक new_mtu)
अणु
	new_mtu += MTU_FUDGE_FACTOR;
	अगर (adapter->physical_port == 0)
		NXWR32(adapter, NETXEN_NIU_XGE_MAX_FRAME_SIZE, new_mtu);
	अन्यथा
		NXWR32(adapter, NETXEN_NIU_XG1_MAX_FRAME_SIZE, new_mtu);
	वापस 0;
पूर्ण

व्योम netxen_nic_set_link_parameters(काष्ठा netxen_adapter *adapter)
अणु
	__u32 status;
	__u32 स्वतःneg;
	__u32 port_mode;

	अगर (!netअगर_carrier_ok(adapter->netdev)) अणु
		adapter->link_speed   = 0;
		adapter->link_duplex  = -1;
		adapter->link_स्वतःneg = AUTONEG_ENABLE;
		वापस;
	पूर्ण

	अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		port_mode = NXRD32(adapter, NETXEN_PORT_MODE_ADDR);
		अगर (port_mode == NETXEN_PORT_MODE_802_3_AP) अणु
			adapter->link_speed   = SPEED_1000;
			adapter->link_duplex  = DUPLEX_FULL;
			adapter->link_स्वतःneg = AUTONEG_DISABLE;
			वापस;
		पूर्ण

		अगर (adapter->phy_पढ़ो &&
		    adapter->phy_पढ़ो(adapter,
				      NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_STATUS,
				      &status) == 0) अणु
			अगर (netxen_get_phy_link(status)) अणु
				चयन (netxen_get_phy_speed(status)) अणु
				हाल 0:
					adapter->link_speed = SPEED_10;
					अवरोध;
				हाल 1:
					adapter->link_speed = SPEED_100;
					अवरोध;
				हाल 2:
					adapter->link_speed = SPEED_1000;
					अवरोध;
				शेष:
					adapter->link_speed = 0;
					अवरोध;
				पूर्ण
				चयन (netxen_get_phy_duplex(status)) अणु
				हाल 0:
					adapter->link_duplex = DUPLEX_HALF;
					अवरोध;
				हाल 1:
					adapter->link_duplex = DUPLEX_FULL;
					अवरोध;
				शेष:
					adapter->link_duplex = -1;
					अवरोध;
				पूर्ण
				अगर (adapter->phy_पढ़ो &&
				    adapter->phy_पढ़ो(adapter,
						      NETXEN_NIU_GB_MII_MGMT_ADDR_AUTONEG,
						      &स्वतःneg) == 0)
					adapter->link_स्वतःneg = स्वतःneg;
			पूर्ण अन्यथा
				जाओ link_करोwn;
		पूर्ण अन्यथा अणु
		      link_करोwn:
			adapter->link_speed = 0;
			adapter->link_duplex = -1;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
netxen_nic_wol_supported(काष्ठा netxen_adapter *adapter)
अणु
	u32 wol_cfg;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 0;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG_NV);
	अगर (wol_cfg & (1UL << adapter->portnum)) अणु
		wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG);
		अगर (wol_cfg & (1 << adapter->portnum))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 netxen_md_cntrl(काष्ठा netxen_adapter *adapter,
			काष्ठा netxen_minidump_ढाँचा_hdr *ढाँचा_hdr,
			काष्ठा netxen_minidump_entry_crb *crtEntry)
अणु
	पूर्णांक loop_cnt, i, rv = 0, समयout_flag;
	u32 op_count, stride;
	u32 opcode, पढ़ो_value, addr;
	अचिन्हित दीर्घ समयout, समयout_jअगरfies;
	addr = crtEntry->addr;
	op_count = crtEntry->op_count;
	stride = crtEntry->addr_stride;

	क्रम (loop_cnt = 0; loop_cnt < op_count; loop_cnt++) अणु
		क्रम (i = 0; i < माप(crtEntry->opcode) * 8; i++) अणु
			opcode = (crtEntry->opcode & (0x1 << i));
			अगर (opcode) अणु
				चयन (opcode) अणु
				हाल NX_DUMP_WCRB:
					NX_WR_DUMP_REG(addr,
						adapter->ahw.pci_base0,
							crtEntry->value_1);
					अवरोध;
				हाल NX_DUMP_RWCRB:
					NX_RD_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								&पढ़ो_value);
					NX_WR_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								पढ़ो_value);
					अवरोध;
				हाल NX_DUMP_ANDCRB:
					NX_RD_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								&पढ़ो_value);
					पढ़ो_value &= crtEntry->value_2;
					NX_WR_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								पढ़ो_value);
					अवरोध;
				हाल NX_DUMP_ORCRB:
					NX_RD_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								&पढ़ो_value);
					पढ़ो_value |= crtEntry->value_3;
					NX_WR_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								पढ़ो_value);
					अवरोध;
				हाल NX_DUMP_POLLCRB:
					समयout = crtEntry->poll_समयout;
					NX_RD_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								&पढ़ो_value);
					समयout_jअगरfies =
					msecs_to_jअगरfies(समयout) + jअगरfies;
					क्रम (समयout_flag = 0;
						!समयout_flag
					&& ((पढ़ो_value & crtEntry->value_2)
					!= crtEntry->value_1);) अणु
						अगर (समय_after(jअगरfies,
							समयout_jअगरfies))
							समयout_flag = 1;
					NX_RD_DUMP_REG(addr,
							adapter->ahw.pci_base0,
								&पढ़ो_value);
					पूर्ण

					अगर (समयout_flag) अणु
						dev_err(&adapter->pdev->dev, "%s : "
							"Timeout in poll_crb control operation.\n"
								, __func__);
						वापस -1;
					पूर्ण
					अवरोध;
				हाल NX_DUMP_RD_SAVE:
					/* Decide which address to use */
					अगर (crtEntry->state_index_a)
						addr =
						ढाँचा_hdr->saved_state_array
						[crtEntry->state_index_a];
					NX_RD_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								&पढ़ो_value);
					ढाँचा_hdr->saved_state_array
					[crtEntry->state_index_v]
						= पढ़ो_value;
					अवरोध;
				हाल NX_DUMP_WRT_SAVED:
					/* Decide which value to use */
					अगर (crtEntry->state_index_v)
						पढ़ो_value =
						ढाँचा_hdr->saved_state_array
						[crtEntry->state_index_v];
					अन्यथा
						पढ़ो_value = crtEntry->value_1;

					/* Decide which address to use */
					अगर (crtEntry->state_index_a)
						addr =
						ढाँचा_hdr->saved_state_array
						[crtEntry->state_index_a];

					NX_WR_DUMP_REG(addr,
						adapter->ahw.pci_base0,
								पढ़ो_value);
					अवरोध;
				हाल NX_DUMP_MOD_SAVE_ST:
					पढ़ो_value =
					ढाँचा_hdr->saved_state_array
						[crtEntry->state_index_v];
					पढ़ो_value <<= crtEntry->shl;
					पढ़ो_value >>= crtEntry->shr;
					अगर (crtEntry->value_2)
						पढ़ो_value &=
						crtEntry->value_2;
					पढ़ो_value |= crtEntry->value_3;
					पढ़ो_value += crtEntry->value_1;
					/* Write value back to state area.*/
					ढाँचा_hdr->saved_state_array
						[crtEntry->state_index_v]
							= पढ़ो_value;
					अवरोध;
				शेष:
					rv = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		addr = addr + stride;
	पूर्ण
	वापस rv;
पूर्ण

/* Read memory or MN */
अटल u32
netxen_md_rdmem(काष्ठा netxen_adapter *adapter,
		काष्ठा netxen_minidump_entry_rdmem
			*memEntry, u64 *data_buff)
अणु
	u64 addr, value = 0;
	पूर्णांक i = 0, loop_cnt;

	addr = (u64)memEntry->पढ़ो_addr;
	loop_cnt = memEntry->पढ़ो_data_size;    /* This is size in bytes */
	loop_cnt /= माप(value);

	क्रम (i = 0; i < loop_cnt; i++) अणु
		अगर (netxen_nic_pci_mem_पढ़ो_2M(adapter, addr, &value))
			जाओ out;
		*data_buff++ = value;
		addr += माप(value);
	पूर्ण
out:
	वापस i * माप(value);
पूर्ण

/* Read CRB operation */
अटल u32 netxen_md_rd_crb(काष्ठा netxen_adapter *adapter,
			काष्ठा netxen_minidump_entry_crb
				*crbEntry, u32 *data_buff)
अणु
	पूर्णांक loop_cnt;
	u32 op_count, addr, stride, value;

	addr = crbEntry->addr;
	op_count = crbEntry->op_count;
	stride = crbEntry->addr_stride;

	क्रम (loop_cnt = 0; loop_cnt < op_count; loop_cnt++) अणु
		NX_RD_DUMP_REG(addr, adapter->ahw.pci_base0, &value);
		*data_buff++ = addr;
		*data_buff++ = value;
		addr = addr + stride;
	पूर्ण
	वापस loop_cnt * (2 * माप(u32));
पूर्ण

/* Read ROM */
अटल u32
netxen_md_rdrom(काष्ठा netxen_adapter *adapter,
			काष्ठा netxen_minidump_entry_rdrom
				*romEntry, __le32 *data_buff)
अणु
	पूर्णांक i, count = 0;
	u32 size, lck_val;
	u32 val;
	u32 fl_addr, waddr, raddr;
	fl_addr = romEntry->पढ़ो_addr;
	size = romEntry->पढ़ो_data_size/4;
lock_try:
	lck_val = पढ़ोl((व्योम __iomem *)(adapter->ahw.pci_base0 +
							NX_FLASH_SEM2_LK));
	अगर (!lck_val && count < MAX_CTL_CHECK) अणु
		msleep(20);
		count++;
		जाओ lock_try;
	पूर्ण
	ग_लिखोl(adapter->ahw.pci_func, (व्योम __iomem *)(adapter->ahw.pci_base0 +
							NX_FLASH_LOCK_ID));
	क्रम (i = 0; i < size; i++) अणु
		waddr = fl_addr & 0xFFFF0000;
		NX_WR_DUMP_REG(FLASH_ROM_WINDOW, adapter->ahw.pci_base0, waddr);
		raddr = FLASH_ROM_DATA + (fl_addr & 0x0000FFFF);
		NX_RD_DUMP_REG(raddr, adapter->ahw.pci_base0, &val);
		*data_buff++ = cpu_to_le32(val);
		fl_addr += माप(val);
	पूर्ण
	पढ़ोl((व्योम __iomem *)(adapter->ahw.pci_base0 + NX_FLASH_SEM2_ULK));
	वापस romEntry->पढ़ो_data_size;
पूर्ण

/* Handle L2 Cache */
अटल u32
netxen_md_L2Cache(काष्ठा netxen_adapter *adapter,
				काष्ठा netxen_minidump_entry_cache
					*cacheEntry, u32 *data_buff)
अणु
	पूर्णांक loop_cnt, i, k, समयout_flag = 0;
	u32 addr, पढ़ो_addr, पढ़ो_value, cntrl_addr, tag_reg_addr;
	u32 tag_value, पढ़ो_cnt;
	u8 cntl_value_w, cntl_value_r;
	अचिन्हित दीर्घ समयout, समयout_jअगरfies;

	loop_cnt = cacheEntry->op_count;
	पढ़ो_addr = cacheEntry->पढ़ो_addr;
	cntrl_addr = cacheEntry->control_addr;
	cntl_value_w = (u32) cacheEntry->ग_लिखो_value;
	tag_reg_addr = cacheEntry->tag_reg_addr;
	tag_value = cacheEntry->init_tag_value;
	पढ़ो_cnt = cacheEntry->पढ़ो_addr_cnt;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		NX_WR_DUMP_REG(tag_reg_addr, adapter->ahw.pci_base0, tag_value);
		अगर (cntl_value_w)
			NX_WR_DUMP_REG(cntrl_addr, adapter->ahw.pci_base0,
					(u32)cntl_value_w);
		अगर (cacheEntry->poll_mask) अणु
			समयout = cacheEntry->poll_रुको;
			NX_RD_DUMP_REG(cntrl_addr, adapter->ahw.pci_base0,
							&cntl_value_r);
			समयout_jअगरfies = msecs_to_jअगरfies(समयout) + jअगरfies;
			क्रम (समयout_flag = 0; !समयout_flag &&
			((cntl_value_r & cacheEntry->poll_mask) != 0);) अणु
				अगर (समय_after(jअगरfies, समयout_jअगरfies))
					समयout_flag = 1;
				NX_RD_DUMP_REG(cntrl_addr,
					adapter->ahw.pci_base0,
							&cntl_value_r);
			पूर्ण
			अगर (समयout_flag) अणु
				dev_err(&adapter->pdev->dev,
						"Timeout in processing L2 Tag poll.\n");
				वापस -1;
			पूर्ण
		पूर्ण
		addr = पढ़ो_addr;
		क्रम (k = 0; k < पढ़ो_cnt; k++) अणु
			NX_RD_DUMP_REG(addr, adapter->ahw.pci_base0,
					&पढ़ो_value);
			*data_buff++ = पढ़ो_value;
			addr += cacheEntry->पढ़ो_addr_stride;
		पूर्ण
		tag_value += cacheEntry->tag_value_stride;
	पूर्ण
	वापस पढ़ो_cnt * loop_cnt * माप(पढ़ो_value);
पूर्ण


/* Handle L1 Cache */
अटल u32 netxen_md_L1Cache(काष्ठा netxen_adapter *adapter,
				काष्ठा netxen_minidump_entry_cache
					*cacheEntry, u32 *data_buff)
अणु
	पूर्णांक i, k, loop_cnt;
	u32 addr, पढ़ो_addr, पढ़ो_value, cntrl_addr, tag_reg_addr;
	u32 tag_value, पढ़ो_cnt;
	u8 cntl_value_w;

	loop_cnt = cacheEntry->op_count;
	पढ़ो_addr = cacheEntry->पढ़ो_addr;
	cntrl_addr = cacheEntry->control_addr;
	cntl_value_w = (u32) cacheEntry->ग_लिखो_value;
	tag_reg_addr = cacheEntry->tag_reg_addr;
	tag_value = cacheEntry->init_tag_value;
	पढ़ो_cnt = cacheEntry->पढ़ो_addr_cnt;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		NX_WR_DUMP_REG(tag_reg_addr, adapter->ahw.pci_base0, tag_value);
		NX_WR_DUMP_REG(cntrl_addr, adapter->ahw.pci_base0,
						(u32) cntl_value_w);
		addr = पढ़ो_addr;
		क्रम (k = 0; k < पढ़ो_cnt; k++) अणु
			NX_RD_DUMP_REG(addr,
				adapter->ahw.pci_base0,
						&पढ़ो_value);
			*data_buff++ = पढ़ो_value;
			addr += cacheEntry->पढ़ो_addr_stride;
		पूर्ण
		tag_value += cacheEntry->tag_value_stride;
	पूर्ण
	वापस पढ़ो_cnt * loop_cnt * माप(पढ़ो_value);
पूर्ण

/* Reading OCM memory */
अटल u32
netxen_md_rकरोcm(काष्ठा netxen_adapter *adapter,
				काष्ठा netxen_minidump_entry_rकरोcm
					*ocmEntry, u32 *data_buff)
अणु
	पूर्णांक i, loop_cnt;
	u32 value;
	व्योम __iomem *addr;
	addr = (ocmEntry->पढ़ो_addr + adapter->ahw.pci_base0);
	loop_cnt = ocmEntry->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		value = पढ़ोl(addr);
		*data_buff++ = value;
		addr += ocmEntry->पढ़ो_addr_stride;
	पूर्ण
	वापस i * माप(u32);
पूर्ण

/* Read MUX data */
अटल u32
netxen_md_rdmux(काष्ठा netxen_adapter *adapter, काष्ठा netxen_minidump_entry_mux
					*muxEntry, u32 *data_buff)
अणु
	पूर्णांक loop_cnt = 0;
	u32 पढ़ो_addr, पढ़ो_value, select_addr, sel_value;

	पढ़ो_addr = muxEntry->पढ़ो_addr;
	sel_value = muxEntry->select_value;
	select_addr = muxEntry->select_addr;

	क्रम (loop_cnt = 0; loop_cnt < muxEntry->op_count; loop_cnt++) अणु
		NX_WR_DUMP_REG(select_addr, adapter->ahw.pci_base0, sel_value);
		NX_RD_DUMP_REG(पढ़ो_addr, adapter->ahw.pci_base0, &पढ़ो_value);
		*data_buff++ = sel_value;
		*data_buff++ = पढ़ो_value;
		sel_value += muxEntry->select_value_stride;
	पूर्ण
	वापस loop_cnt * (2 * माप(u32));
पूर्ण

/* Handling Queue State Reads */
अटल u32
netxen_md_rdqueue(काष्ठा netxen_adapter *adapter,
				काष्ठा netxen_minidump_entry_queue
					*queueEntry, u32 *data_buff)
अणु
	पूर्णांक loop_cnt, k;
	u32 queue_id, पढ़ो_addr, पढ़ो_value, पढ़ो_stride, select_addr, पढ़ो_cnt;

	पढ़ो_cnt = queueEntry->पढ़ो_addr_cnt;
	पढ़ो_stride = queueEntry->पढ़ो_addr_stride;
	select_addr = queueEntry->select_addr;

	क्रम (loop_cnt = 0, queue_id = 0; loop_cnt < queueEntry->op_count;
				 loop_cnt++) अणु
		NX_WR_DUMP_REG(select_addr, adapter->ahw.pci_base0, queue_id);
		पढ़ो_addr = queueEntry->पढ़ो_addr;
		क्रम (k = 0; k < पढ़ो_cnt; k++) अणु
			NX_RD_DUMP_REG(पढ़ो_addr, adapter->ahw.pci_base0,
							&पढ़ो_value);
			*data_buff++ = पढ़ो_value;
			पढ़ो_addr += पढ़ो_stride;
		पूर्ण
		queue_id += queueEntry->queue_id_stride;
	पूर्ण
	वापस loop_cnt * (पढ़ो_cnt * माप(पढ़ो_value));
पूर्ण


/*
* We catch an error where driver करोes not पढ़ो
* as much data as we expect from the entry.
*/

अटल पूर्णांक netxen_md_entry_err_chk(काष्ठा netxen_adapter *adapter,
				काष्ठा netxen_minidump_entry *entry, पूर्णांक esize)
अणु
	अगर (esize < 0) अणु
		entry->hdr.driver_flags |= NX_DUMP_SKIP;
		वापस esize;
	पूर्ण
	अगर (esize != entry->hdr.entry_capture_size) अणु
		entry->hdr.entry_capture_size = esize;
		entry->hdr.driver_flags |= NX_DUMP_SIZE_ERR;
		dev_info(&adapter->pdev->dev,
			"Invalidate dump, Type:%d\tMask:%d\tSize:%dCap_size:%d\n",
			entry->hdr.entry_type, entry->hdr.entry_capture_mask,
			esize, entry->hdr.entry_capture_size);
		dev_info(&adapter->pdev->dev, "Aborting further dump capture\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netxen_parse_md_ढाँचा(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक num_of_entries, buff_level, e_cnt, esize;
	पूर्णांक rv = 0, sane_start = 0, sane_end = 0;
	अक्षर *dbuff;
	व्योम *ढाँचा_buff = adapter->mdump.md_ढाँचा;
	अक्षर *dump_buff = adapter->mdump.md_capture_buff;
	पूर्णांक capture_mask = adapter->mdump.md_capture_mask;
	काष्ठा netxen_minidump_ढाँचा_hdr *ढाँचा_hdr;
	काष्ठा netxen_minidump_entry *entry;

	अगर ((capture_mask & 0x3) != 0x3) अणु
		dev_err(&adapter->pdev->dev, "Capture mask %02x below minimum needed "
			"for valid firmware dump\n", capture_mask);
		वापस -EINVAL;
	पूर्ण
	ढाँचा_hdr = (काष्ठा netxen_minidump_ढाँचा_hdr *) ढाँचा_buff;
	num_of_entries = ढाँचा_hdr->num_of_entries;
	entry = (काष्ठा netxen_minidump_entry *) ((अक्षर *) ढाँचा_buff +
				ढाँचा_hdr->first_entry_offset);
	स_नकल(dump_buff, ढाँचा_buff, adapter->mdump.md_ढाँचा_size);
	dump_buff = dump_buff + adapter->mdump.md_ढाँचा_size;

	अगर (ढाँचा_hdr->entry_type == TLHDR)
		sane_start = 1;

	क्रम (e_cnt = 0, buff_level = 0; e_cnt < num_of_entries; e_cnt++) अणु
		अगर (!(entry->hdr.entry_capture_mask & capture_mask)) अणु
			entry->hdr.driver_flags |= NX_DUMP_SKIP;
			entry = (काष्ठा netxen_minidump_entry *)
				((अक्षर *) entry + entry->hdr.entry_size);
			जारी;
		पूर्ण
		चयन (entry->hdr.entry_type) अणु
		हाल RDNOP:
			entry->hdr.driver_flags |= NX_DUMP_SKIP;
			अवरोध;
		हाल RDEND:
			entry->hdr.driver_flags |= NX_DUMP_SKIP;
			sane_end += 1;
			अवरोध;
		हाल CNTRL:
			rv = netxen_md_cntrl(adapter,
				ढाँचा_hdr, (व्योम *)entry);
			अगर (rv)
				entry->hdr.driver_flags |= NX_DUMP_SKIP;
			अवरोध;
		हाल RDCRB:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rd_crb(adapter,
					(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल RDMN:
		हाल RDMEM:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rdmem(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल BOARD:
		हाल RDROM:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rdrom(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल L2ITG:
		हाल L2DTG:
		हाल L2DAT:
		हाल L2INS:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_L2Cache(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल L1DAT:
		हाल L1INS:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_L1Cache(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल RDOCM:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rकरोcm(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल RDMUX:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rdmux(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		हाल QUEUE:
			dbuff = dump_buff + buff_level;
			esize = netxen_md_rdqueue(adapter,
				(व्योम *) entry, (व्योम *) dbuff);
			rv = netxen_md_entry_err_chk
				(adapter, entry, esize);
			अगर (rv  < 0)
				अवरोध;
			buff_level += esize;
			अवरोध;
		शेष:
			entry->hdr.driver_flags |= NX_DUMP_SKIP;
			अवरोध;
		पूर्ण
		/* Next entry in the ढाँचा */
		entry = (काष्ठा netxen_minidump_entry *)
			((अक्षर *) entry + entry->hdr.entry_size);
	पूर्ण
	अगर (!sane_start || sane_end > 1) अणु
		dev_err(&adapter->pdev->dev,
				"Firmware minidump template configuration error.\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_collect_minidump(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक ret = 0;
	काष्ठा netxen_minidump_ढाँचा_hdr *hdr;
	hdr = (काष्ठा netxen_minidump_ढाँचा_hdr *)
				adapter->mdump.md_ढाँचा;
	hdr->driver_capture_mask = adapter->mdump.md_capture_mask;
	hdr->driver_बारtamp = kसमय_get_seconds();
	hdr->driver_info_word2 = adapter->fw_version;
	hdr->driver_info_word3 = NXRD32(adapter, CRB_DRIVER_VERSION);
	ret = netxen_parse_md_ढाँचा(adapter);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण


व्योम
netxen_dump_fw(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_minidump_ढाँचा_hdr *hdr;
	पूर्णांक i, k, data_size = 0;
	u32 capture_mask;
	hdr = (काष्ठा netxen_minidump_ढाँचा_hdr *)
				adapter->mdump.md_ढाँचा;
	capture_mask = adapter->mdump.md_capture_mask;

	क्रम (i = 0x2, k = 1; (i & NX_DUMP_MASK_MAX); i <<= 1, k++) अणु
		अगर (i & capture_mask)
			data_size += hdr->capture_size_array[k];
	पूर्ण
	अगर (!data_size) अणु
		dev_err(&adapter->pdev->dev,
				"Invalid cap sizes for capture_mask=0x%x\n",
			adapter->mdump.md_capture_mask);
		वापस;
	पूर्ण
	adapter->mdump.md_capture_size = data_size;
	adapter->mdump.md_dump_size = adapter->mdump.md_ढाँचा_size +
					adapter->mdump.md_capture_size;
	अगर (!adapter->mdump.md_capture_buff) अणु
		adapter->mdump.md_capture_buff =
				vzalloc(adapter->mdump.md_dump_size);
		अगर (!adapter->mdump.md_capture_buff)
			वापस;

		अगर (netxen_collect_minidump(adapter)) अणु
			adapter->mdump.has_valid_dump = 0;
			adapter->mdump.md_dump_size = 0;
			vमुक्त(adapter->mdump.md_capture_buff);
			adapter->mdump.md_capture_buff = शून्य;
			dev_err(&adapter->pdev->dev,
				"Error in collecting firmware minidump.\n");
		पूर्ण अन्यथा अणु
			adapter->mdump.md_बारtamp = jअगरfies;
			adapter->mdump.has_valid_dump = 1;
			adapter->fw_mdump_rdy = 1;
			dev_info(&adapter->pdev->dev, "%s Successfully "
				"collected fw dump.\n", adapter->netdev->name);
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_info(&adapter->pdev->dev,
					"Cannot overwrite previously collected "
							"firmware minidump.\n");
		adapter->fw_mdump_rdy = 1;
		वापस;
	पूर्ण
पूर्ण
