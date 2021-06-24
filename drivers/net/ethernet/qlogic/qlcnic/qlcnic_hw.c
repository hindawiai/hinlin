<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <linux/bitops.h>

#समावेश "qlcnic.h"
#समावेश "qlcnic_hdr.h"

#घोषणा MASK(n) ((1ULL<<(n))-1)
#घोषणा OCM_WIN_P3P(addr) (addr & 0xffc0000)

#घोषणा GET_MEM_OFFS_2M(addr) (addr & MASK(18))

#घोषणा CRB_BLK(off)	((off >> 20) & 0x3f)
#घोषणा CRB_SUBBLK(off)	((off >> 16) & 0xf)
#घोषणा CRB_WINDOW_2M	(0x130060)
#घोषणा CRB_HI(off)	((crb_hub_agt[CRB_BLK(off)] << 20) | ((off) & 0xf0000))
#घोषणा CRB_INसूचीECT_2M	(0x1e0000UL)

काष्ठा qlcnic_ms_reg_ctrl अणु
	u32 ocm_winकरोw;
	u32 control;
	u32 hi;
	u32 low;
	u32 rd[4];
	u32 wd[4];
	u64 off;
पूर्ण;

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) | (((u64) पढ़ोl(addr + 4)) << 32LL);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(((u32) (val)), (addr));
	ग_लिखोl(((u32) (val >> 32)), (addr + 4));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा crb_128M_2M_block_map
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
अटल स्थिर अचिन्हित crb_hub_agt[64] = अणु
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PS,
	QLCNIC_HW_CRB_HUB_AGT_ADR_MN,
	QLCNIC_HW_CRB_HUB_AGT_ADR_MS,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SRE,
	QLCNIC_HW_CRB_HUB_AGT_ADR_NIU,
	QLCNIC_HW_CRB_HUB_AGT_ADR_QMN,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SQN0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SQN1,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SQN2,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SQN3,
	QLCNIC_HW_CRB_HUB_AGT_ADR_I2Q,
	QLCNIC_HW_CRB_HUB_AGT_ADR_TIMR,
	QLCNIC_HW_CRB_HUB_AGT_ADR_ROMUSB,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGN4,
	QLCNIC_HW_CRB_HUB_AGT_ADR_XDMA,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGN0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGN1,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGN2,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGN3,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGND,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGNI,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGS0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGS1,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGS2,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGS3,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGSI,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SN,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_EG,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PS,
	QLCNIC_HW_CRB_HUB_AGT_ADR_CAM,
	0,
	0,
	0,
	0,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_TIMR,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX1,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX2,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX3,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX4,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX5,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX6,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX7,
	QLCNIC_HW_CRB_HUB_AGT_ADR_XDMA,
	QLCNIC_HW_CRB_HUB_AGT_ADR_I2Q,
	QLCNIC_HW_CRB_HUB_AGT_ADR_ROMUSB,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX8,
	QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX9,
	QLCNIC_HW_CRB_HUB_AGT_ADR_OCM0,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_SMB,
	QLCNIC_HW_CRB_HUB_AGT_ADR_I2C0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_I2C1,
	0,
	QLCNIC_HW_CRB_HUB_AGT_ADR_PGNC,
	0,
पूर्ण;

/*  PCI Winकरोwing क्रम DDR regions.  */

#घोषणा QLCNIC_PCIE_SEM_TIMEOUT	10000

अटल व्योम qlcnic_पढ़ो_winकरोw_reg(u32 addr, व्योम __iomem *bar0, u32 *data)
अणु
	u32 dest;
	व्योम __iomem *val;

	dest = addr & 0xFFFF0000;
	val = bar0 + QLCNIC_FW_DUMP_REG1;
	ग_लिखोl(dest, val);
	पढ़ोl(val);
	val = bar0 + QLCNIC_FW_DUMP_REG2 + LSW(addr);
	*data = पढ़ोl(val);
पूर्ण

अटल व्योम qlcnic_ग_लिखो_winकरोw_reg(u32 addr, व्योम __iomem *bar0, u32 data)
अणु
	u32 dest;
	व्योम __iomem *val;

	dest = addr & 0xFFFF0000;
	val = bar0 + QLCNIC_FW_DUMP_REG1;
	ग_लिखोl(dest, val);
	पढ़ोl(val);
	val = bar0 + QLCNIC_FW_DUMP_REG2 + LSW(addr);
	ग_लिखोl(data, val);
	पढ़ोl(val);
पूर्ण

पूर्णांक
qlcnic_pcie_sem_lock(काष्ठा qlcnic_adapter *adapter, पूर्णांक sem, u32 id_reg)
अणु
	पूर्णांक समयout = 0, err = 0, करोne = 0;

	जबतक (!करोne) अणु
		करोne = QLCRD32(adapter, QLCNIC_PCIE_REG(PCIE_SEM_LOCK(sem)),
			       &err);
		अगर (करोne == 1)
			अवरोध;
		अगर (++समयout >= QLCNIC_PCIE_SEM_TIMEOUT) अणु
			अगर (id_reg) अणु
				करोne = QLCRD32(adapter, id_reg, &err);
				अगर (करोne != -1)
					dev_err(&adapter->pdev->dev,
						"Failed to acquire sem=%d lock held by=%d\n",
						sem, करोne);
				अन्यथा
					dev_err(&adapter->pdev->dev,
						"Failed to acquire sem=%d lock",
						sem);
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev,
					"Failed to acquire sem=%d lock", sem);
			पूर्ण
			वापस -EIO;
		पूर्ण
		udelay(1200);
	पूर्ण

	अगर (id_reg)
		QLCWR32(adapter, id_reg, adapter->portnum);

	वापस 0;
पूर्ण

व्योम
qlcnic_pcie_sem_unlock(काष्ठा qlcnic_adapter *adapter, पूर्णांक sem)
अणु
	पूर्णांक err = 0;

	QLCRD32(adapter, QLCNIC_PCIE_REG(PCIE_SEM_UNLOCK(sem)), &err);
पूर्ण

पूर्णांक qlcnic_ind_rd(काष्ठा qlcnic_adapter *adapter, u32 addr)
अणु
	पूर्णांक err = 0;
	u32 data;

	अगर (qlcnic_82xx_check(adapter))
		qlcnic_पढ़ो_winकरोw_reg(addr, adapter->ahw->pci_base0, &data);
	अन्यथा अणु
		data = QLCRD32(adapter, addr, &err);
		अगर (err == -EIO)
			वापस err;
	पूर्ण
	वापस data;
पूर्ण

पूर्णांक qlcnic_ind_wr(काष्ठा qlcnic_adapter *adapter, u32 addr, u32 data)
अणु
	पूर्णांक ret = 0;

	अगर (qlcnic_82xx_check(adapter))
		qlcnic_ग_लिखो_winकरोw_reg(addr, adapter->ahw->pci_base0, data);
	अन्यथा
		ret = qlcnic_83xx_wrt_reg_indirect(adapter, addr, data);

	वापस ret;
पूर्ण

अटल पूर्णांक
qlcnic_send_cmd_descs(काष्ठा qlcnic_adapter *adapter,
		काष्ठा cmd_desc_type0 *cmd_desc_arr, पूर्णांक nr_desc)
अणु
	u32 i, producer;
	काष्ठा qlcnic_cmd_buffer *pbuf;
	काष्ठा cmd_desc_type0 *cmd_desc;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	i = 0;

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस -EIO;

	tx_ring = &adapter->tx_ring[0];
	__netअगर_tx_lock_bh(tx_ring->txq);

	producer = tx_ring->producer;

	अगर (nr_desc >= qlcnic_tx_avail(tx_ring)) अणु
		netअगर_tx_stop_queue(tx_ring->txq);
		smp_mb();
		अगर (qlcnic_tx_avail(tx_ring) > nr_desc) अणु
			अगर (qlcnic_tx_avail(tx_ring) > TX_STOP_THRESH)
				netअगर_tx_wake_queue(tx_ring->txq);
		पूर्ण अन्यथा अणु
			adapter->stats.xmit_off++;
			__netअगर_tx_unlock_bh(tx_ring->txq);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	करो अणु
		cmd_desc = &cmd_desc_arr[i];

		pbuf = &tx_ring->cmd_buf_arr[producer];
		pbuf->skb = शून्य;
		pbuf->frag_count = 0;

		स_नकल(&tx_ring->desc_head[producer],
		       cmd_desc, माप(काष्ठा cmd_desc_type0));

		producer = get_next_index(producer, tx_ring->num_desc);
		i++;

	पूर्ण जबतक (i != nr_desc);

	tx_ring->producer = producer;

	qlcnic_update_cmd_producer(tx_ring);

	__netअगर_tx_unlock_bh(tx_ring->txq);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_sre_macaddr_change(काष्ठा qlcnic_adapter *adapter, u8 *addr,
				   u16 vlan_id, u8 op)
अणु
	काष्ठा qlcnic_nic_req req;
	काष्ठा qlcnic_mac_req *mac_req;
	काष्ठा qlcnic_vlan_req *vlan_req;
	u64 word;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_REQUEST << 23);

	word = QLCNIC_MAC_EVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	mac_req = (काष्ठा qlcnic_mac_req *)&req.words[0];
	mac_req->op = op;
	स_नकल(mac_req->mac_addr, addr, ETH_ALEN);

	vlan_req = (काष्ठा qlcnic_vlan_req *)&req.words[1];
	vlan_req->vlan_id = cpu_to_le16(vlan_id);

	वापस qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
पूर्ण

पूर्णांक qlcnic_nic_del_mac(काष्ठा qlcnic_adapter *adapter, स्थिर u8 *addr)
अणु
	काष्ठा qlcnic_mac_vlan_list *cur;
	काष्ठा list_head *head;
	पूर्णांक err = -EINVAL;

	/* Delete MAC from the existing list */
	list_क्रम_each(head, &adapter->mac_list) अणु
		cur = list_entry(head, काष्ठा qlcnic_mac_vlan_list, list);
		अगर (ether_addr_equal(addr, cur->mac_addr)) अणु
			err = qlcnic_sre_macaddr_change(adapter, cur->mac_addr,
							0, QLCNIC_MAC_DEL);
			अगर (err)
				वापस err;
			list_del(&cur->list);
			kमुक्त(cur);
			वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक qlcnic_nic_add_mac(काष्ठा qlcnic_adapter *adapter, स्थिर u8 *addr, u16 vlan,
		       क्रमागत qlcnic_mac_type mac_type)
अणु
	काष्ठा qlcnic_mac_vlan_list *cur;
	काष्ठा list_head *head;

	/* look up अगर alपढ़ोy exists */
	list_क्रम_each(head, &adapter->mac_list) अणु
		cur = list_entry(head, काष्ठा qlcnic_mac_vlan_list, list);
		अगर (ether_addr_equal(addr, cur->mac_addr) &&
		    cur->vlan_id == vlan)
			वापस 0;
	पूर्ण

	cur = kzalloc(माप(*cur), GFP_ATOMIC);
	अगर (cur == शून्य)
		वापस -ENOMEM;

	स_नकल(cur->mac_addr, addr, ETH_ALEN);

	अगर (qlcnic_sre_macaddr_change(adapter,
				cur->mac_addr, vlan, QLCNIC_MAC_ADD)) अणु
		kमुक्त(cur);
		वापस -EIO;
	पूर्ण

	cur->vlan_id = vlan;
	cur->mac_type = mac_type;

	list_add_tail(&cur->list, &adapter->mac_list);
	वापस 0;
पूर्ण

व्योम qlcnic_flush_mcast_mac(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mac_vlan_list *cur;
	काष्ठा list_head *head, *पंचांगp;

	list_क्रम_each_safe(head, पंचांगp, &adapter->mac_list) अणु
		cur = list_entry(head, काष्ठा qlcnic_mac_vlan_list, list);
		अगर (cur->mac_type != QLCNIC_MULTICAST_MAC)
			जारी;

		qlcnic_sre_macaddr_change(adapter, cur->mac_addr,
					  cur->vlan_id, QLCNIC_MAC_DEL);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

अटल व्योम __qlcnic_set_multi(काष्ठा net_device *netdev, u16 vlan)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा netdev_hw_addr *ha;
	अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	u32 mode = VPORT_MISS_MODE_DROP;

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस;

	qlcnic_nic_add_mac(adapter, adapter->mac_addr, vlan,
			   QLCNIC_UNICAST_MAC);
	qlcnic_nic_add_mac(adapter, bcast_addr, vlan, QLCNIC_BROADCAST_MAC);

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (!(adapter->flags & QLCNIC_PROMISC_DISABLED))
			mode = VPORT_MISS_MODE_ACCEPT_ALL;
	पूर्ण अन्यथा अगर ((netdev->flags & IFF_ALLMULTI) ||
		   (netdev_mc_count(netdev) > ahw->max_mc_count)) अणु
		mode = VPORT_MISS_MODE_ACCEPT_MULTI;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(netdev)) अणु
		qlcnic_flush_mcast_mac(adapter);
		netdev_क्रम_each_mc_addr(ha, netdev)
			qlcnic_nic_add_mac(adapter, ha->addr, vlan,
					   QLCNIC_MULTICAST_MAC);
	पूर्ण

	/* configure unicast MAC address, अगर there is not sufficient space
	 * to store all the unicast addresses then enable promiscuous mode
	 */
	अगर (netdev_uc_count(netdev) > ahw->max_uc_count) अणु
		mode = VPORT_MISS_MODE_ACCEPT_ALL;
	पूर्ण अन्यथा अगर (!netdev_uc_empty(netdev)) अणु
		netdev_क्रम_each_uc_addr(ha, netdev)
			qlcnic_nic_add_mac(adapter, ha->addr, vlan,
					   QLCNIC_UNICAST_MAC);
	पूर्ण

	अगर (mode == VPORT_MISS_MODE_ACCEPT_ALL &&
	    !adapter->fdb_mac_learn) अणु
		qlcnic_alloc_lb_filters_mem(adapter);
		adapter->drv_mac_learn = 1;
		अगर (adapter->flags & QLCNIC_ESWITCH_ENABLED)
			adapter->rx_mac_learn = true;
	पूर्ण अन्यथा अणु
		adapter->drv_mac_learn = 0;
		adapter->rx_mac_learn = false;
	पूर्ण

	qlcnic_nic_set_promisc(adapter, mode);
पूर्ण

व्योम qlcnic_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस;

	अगर (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_vf_set_multi(netdev);
	अन्यथा
		__qlcnic_set_multi(netdev, 0);
पूर्ण

पूर्णांक qlcnic_82xx_nic_set_promisc(काष्ठा qlcnic_adapter *adapter, u32 mode)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_SET_MAC_RECEIVE_MODE |
			((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(mode);

	वापस qlcnic_send_cmd_descs(adapter,
				(काष्ठा cmd_desc_type0 *)&req, 1);
पूर्ण

व्योम qlcnic_82xx_मुक्त_mac_list(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा list_head *head = &adapter->mac_list;
	काष्ठा qlcnic_mac_vlan_list *cur;

	जबतक (!list_empty(head)) अणु
		cur = list_entry(head->next, काष्ठा qlcnic_mac_vlan_list, list);
		qlcnic_sre_macaddr_change(adapter,
				cur->mac_addr, 0, QLCNIC_MAC_DEL);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

व्योम qlcnic_prune_lb_filters(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_filter *पंचांगp_fil;
	काष्ठा hlist_node *n;
	काष्ठा hlist_head *head;
	पूर्णांक i;
	अचिन्हित दीर्घ expires;
	u8 cmd;

	क्रम (i = 0; i < adapter->fhash.fbucket_size; i++) अणु
		head = &(adapter->fhash.fhead[i]);
		hlist_क्रम_each_entry_safe(पंचांगp_fil, n, head, fnode) अणु
			cmd =  पंचांगp_fil->vlan_id ? QLCNIC_MAC_VLAN_DEL :
						  QLCNIC_MAC_DEL;
			expires = पंचांगp_fil->fसमय + QLCNIC_FILTER_AGE * HZ;
			अगर (समय_beक्रमe(expires, jअगरfies)) अणु
				qlcnic_sre_macaddr_change(adapter,
							  पंचांगp_fil->faddr,
							  पंचांगp_fil->vlan_id,
							  cmd);
				spin_lock_bh(&adapter->mac_learn_lock);
				adapter->fhash.fnum--;
				hlist_del(&पंचांगp_fil->fnode);
				spin_unlock_bh(&adapter->mac_learn_lock);
				kमुक्त(पंचांगp_fil);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < adapter->rx_fhash.fbucket_size; i++) अणु
		head = &(adapter->rx_fhash.fhead[i]);

		hlist_क्रम_each_entry_safe(पंचांगp_fil, n, head, fnode)
		अणु
			expires = पंचांगp_fil->fसमय + QLCNIC_FILTER_AGE * HZ;
			अगर (समय_beक्रमe(expires, jअगरfies)) अणु
				spin_lock_bh(&adapter->rx_mac_learn_lock);
				adapter->rx_fhash.fnum--;
				hlist_del(&पंचांगp_fil->fnode);
				spin_unlock_bh(&adapter->rx_mac_learn_lock);
				kमुक्त(पंचांगp_fil);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_delete_lb_filters(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_filter *पंचांगp_fil;
	काष्ठा hlist_node *n;
	काष्ठा hlist_head *head;
	पूर्णांक i;
	u8 cmd;

	क्रम (i = 0; i < adapter->fhash.fbucket_size; i++) अणु
		head = &(adapter->fhash.fhead[i]);
		hlist_क्रम_each_entry_safe(पंचांगp_fil, n, head, fnode) अणु
			cmd =  पंचांगp_fil->vlan_id ? QLCNIC_MAC_VLAN_DEL :
						  QLCNIC_MAC_DEL;
			qlcnic_sre_macaddr_change(adapter,
						  पंचांगp_fil->faddr,
						  पंचांगp_fil->vlan_id,
						  cmd);
			spin_lock_bh(&adapter->mac_learn_lock);
			adapter->fhash.fnum--;
			hlist_del(&पंचांगp_fil->fnode);
			spin_unlock_bh(&adapter->mac_learn_lock);
			kमुक्त(पंचांगp_fil);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_set_fw_loopback(काष्ठा qlcnic_adapter *adapter, u8 flag)
अणु
	काष्ठा qlcnic_nic_req req;
	पूर्णांक rv;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);
	req.req_hdr = cpu_to_le64(QLCNIC_H2C_OPCODE_CONFIG_LOOPBACK |
		((u64) adapter->portnum << 16) | ((u64) 0x1 << 32));

	req.words[0] = cpu_to_le64(flag);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->pdev->dev, "%sting loopback mode failed\n",
				flag ? "Set" : "Reset");
	वापस rv;
पूर्ण

पूर्णांक qlcnic_82xx_set_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	अगर (qlcnic_set_fw_loopback(adapter, mode))
		वापस -EIO;

	अगर (qlcnic_nic_set_promisc(adapter,
				   VPORT_MISS_MODE_ACCEPT_ALL)) अणु
		qlcnic_set_fw_loopback(adapter, 0);
		वापस -EIO;
	पूर्ण

	msleep(1000);
	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_clear_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	mode = VPORT_MISS_MODE_DROP;
	qlcnic_set_fw_loopback(adapter, 0);

	अगर (netdev->flags & IFF_PROMISC)
		mode = VPORT_MISS_MODE_ACCEPT_ALL;
	अन्यथा अगर (netdev->flags & IFF_ALLMULTI)
		mode = VPORT_MISS_MODE_ACCEPT_MULTI;

	qlcnic_nic_set_promisc(adapter, mode);
	msleep(1000);
	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_पढ़ो_phys_port_id(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 mac[ETH_ALEN];
	पूर्णांक ret;

	ret = qlcnic_get_mac_address(adapter, mac,
				     adapter->ahw->physical_port);
	अगर (ret)
		वापस ret;

	स_नकल(adapter->ahw->phys_port_id, mac, ETH_ALEN);
	adapter->flags |= QLCNIC_HAS_PHYS_PORT_ID;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_set_rx_coalesce(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_nic_req req;
	पूर्णांक rv;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	req.req_hdr = cpu_to_le64(QLCNIC_CONFIG_INTR_COALESCE |
		((u64) adapter->portnum << 16));

	req.words[0] = cpu_to_le64(((u64) adapter->ahw->coal.flag) << 32);
	req.words[2] = cpu_to_le64(adapter->ahw->coal.rx_packets |
			((u64) adapter->ahw->coal.rx_समय_us) << 16);
	req.words[5] = cpu_to_le64(adapter->ahw->coal.समयr_out |
			((u64) adapter->ahw->coal.type) << 32 |
			((u64) adapter->ahw->coal.sts_ring_mask) << 40);
	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
			"Could not send interrupt coalescing parameters\n");

	वापस rv;
पूर्ण

/* Send the पूर्णांकerrupt coalescing parameter set by ethtool to the card. */
पूर्णांक qlcnic_82xx_config_पूर्णांकr_coalesce(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce *coal = &adapter->ahw->coal;
	पूर्णांक rv;

	coal->flag = QLCNIC_INTR_DEFAULT;
	coal->rx_समय_us = ethcoal->rx_coalesce_usecs;
	coal->rx_packets = ethcoal->rx_max_coalesced_frames;

	rv = qlcnic_82xx_set_rx_coalesce(adapter);

	अगर (rv)
		netdev_err(adapter->netdev,
			   "Failed to set Rx coalescing parameters\n");

	वापस rv;
पूर्ण

#घोषणा QLCNIC_ENABLE_IPV4_LRO		BIT_0
#घोषणा QLCNIC_ENABLE_IPV6_LRO		(BIT_1 | BIT_9)

पूर्णांक qlcnic_82xx_config_hw_lro(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;
	पूर्णांक rv;

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस 0;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_HW_LRO | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	word = 0;
	अगर (enable) अणु
		word = QLCNIC_ENABLE_IPV4_LRO;
		अगर (adapter->ahw->extra_capability[0] &
		    QLCNIC_FW_CAP2_HW_LRO_IPV6)
			word |= QLCNIC_ENABLE_IPV6_LRO;
	पूर्ण

	req.words[0] = cpu_to_le64(word);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
			"Could not send configure hw lro request\n");

	वापस rv;
पूर्ण

पूर्णांक qlcnic_config_bridged_mode(काष्ठा qlcnic_adapter *adapter, u32 enable)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;
	पूर्णांक rv;

	अगर (!!(adapter->flags & QLCNIC_BRIDGE_ENABLED) == enable)
		वापस 0;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_BRIDGING |
		((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(enable);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
			"Could not send configure bridge mode request\n");

	adapter->flags ^= QLCNIC_BRIDGE_ENABLED;

	वापस rv;
पूर्ण


#घोषणा QLCNIC_RSS_HASHTYPE_IP_TCP	0x3
#घोषणा QLCNIC_ENABLE_TYPE_C_RSS	BIT_10
#घोषणा QLCNIC_RSS_FEATURE_FLAG	(1ULL << 63)
#घोषणा QLCNIC_RSS_IND_TABLE_MASK	0x7ULL

पूर्णांक qlcnic_82xx_config_rss(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;
	पूर्णांक i, rv;

	अटल स्थिर u64 key[] = अणु
		0xbeac01fa6a42b73bULL, 0x8030f20c77cb2da3ULL,
		0xae7b30b4d0ca2bcbULL, 0x43a38fb04167253dULL,
		0x255b0ec26d5a56daULL
	पूर्ण;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_RSS | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	/*
	 * RSS request:
	 * bits 3-0: hash_method
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enable
	 *        9: use indirection table
	 *       10: type-c rss
	 *	 11: udp rss
	 *    47-12: reserved
	 *    62-48: indirection table mask
	 *	 63: feature flag
	 */
	word =  ((u64)(QLCNIC_RSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u64)(QLCNIC_RSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u64)(enable & 0x1) << 8) |
		((u64)QLCNIC_RSS_IND_TABLE_MASK << 48) |
		(u64)QLCNIC_ENABLE_TYPE_C_RSS |
		(u64)QLCNIC_RSS_FEATURE_FLAG;

	req.words[0] = cpu_to_le64(word);
	क्रम (i = 0; i < 5; i++)
		req.words[i+1] = cpu_to_le64(key[i]);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev, "could not configure RSS\n");

	वापस rv;
पूर्ण

व्योम qlcnic_82xx_config_ipaddr(काष्ठा qlcnic_adapter *adapter,
			       __be32 ip, पूर्णांक cmd)
अणु
	काष्ठा qlcnic_nic_req req;
	काष्ठा qlcnic_ipaddr *ipa;
	u64 word;
	पूर्णांक rv;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_IPADDR | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(cmd);
	ipa = (काष्ठा qlcnic_ipaddr *)&req.words[1];
	ipa->ipv4 = ip;

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
				"could not notify %s IP 0x%x request\n",
				(cmd == QLCNIC_IP_UP) ? "Add" : "Remove", ip);
पूर्ण

पूर्णांक qlcnic_82xx_linkevent_request(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;
	पूर्णांक rv;
	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_GET_LINKEVENT | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);
	req.words[0] = cpu_to_le64(enable | (enable << 8));
	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
				"could not configure link notification\n");

	वापस rv;
पूर्ण

अटल पूर्णांक qlcnic_send_lro_cleanup(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_nic_req req;
	u64 word;
	पूर्णांक rv;

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस 0;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_LRO_REQUEST |
		((u64)adapter->portnum << 16) |
		((u64)QLCNIC_LRO_REQUEST_CLEANUP << 56) ;

	req.req_hdr = cpu_to_le64(word);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv != 0)
		dev_err(&adapter->netdev->dev,
				 "could not cleanup lro flows\n");

	वापस rv;
पूर्ण

/*
 * qlcnic_change_mtu - Change the Maximum Transfer Unit
 * @वापसs 0 on success, negative on failure
 */

पूर्णांक qlcnic_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	rc = qlcnic_fw_cmd_set_mtu(adapter, mtu);

	अगर (!rc)
		netdev->mtu = mtu;

	वापस rc;
पूर्ण

अटल netdev_features_t qlcnic_process_flags(काष्ठा qlcnic_adapter *adapter,
					      netdev_features_t features)
अणु
	u32 offload_flags = adapter->offload_flags;

	अगर (offload_flags & BIT_0) अणु
		features |= NETIF_F_RXCSUM | NETIF_F_IP_CSUM |
			    NETIF_F_IPV6_CSUM;
		adapter->rx_csum = 1;
		अगर (QLCNIC_IS_TSO_CAPABLE(adapter)) अणु
			अगर (!(offload_flags & BIT_1))
				features &= ~NETIF_F_TSO;
			अन्यथा
				features |= NETIF_F_TSO;

			अगर (!(offload_flags & BIT_2))
				features &= ~NETIF_F_TSO6;
			अन्यथा
				features |= NETIF_F_TSO6;
		पूर्ण
	पूर्ण अन्यथा अणु
		features &= ~(NETIF_F_RXCSUM |
			      NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM);

		अगर (QLCNIC_IS_TSO_CAPABLE(adapter))
			features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
		adapter->rx_csum = 0;
	पूर्ण

	वापस features;
पूर्ण

netdev_features_t qlcnic_fix_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed;

	अगर (qlcnic_82xx_check(adapter) &&
	    (adapter->flags & QLCNIC_ESWITCH_ENABLED)) अणु
		अगर (adapter->flags & QLCNIC_APP_CHANGED_FLAGS) अणु
			features = qlcnic_process_flags(adapter, features);
		पूर्ण अन्यथा अणु
			changed = features ^ netdev->features;
			features ^= changed & (NETIF_F_RXCSUM |
					       NETIF_F_IP_CSUM |
					       NETIF_F_IPV6_CSUM |
					       NETIF_F_TSO |
					       NETIF_F_TSO6);
		पूर्ण
	पूर्ण

	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	वापस features;
पूर्ण


पूर्णांक qlcnic_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = netdev->features ^ features;
	पूर्णांक hw_lro = (features & NETIF_F_LRO) ? QLCNIC_LRO_ENABLED : 0;

	अगर (!(changed & NETIF_F_LRO))
		वापस 0;

	netdev->features ^= NETIF_F_LRO;

	अगर (qlcnic_config_hw_lro(adapter, hw_lro))
		वापस -EIO;

	अगर (!hw_lro && qlcnic_82xx_check(adapter)) अणु
		अगर (qlcnic_send_lro_cleanup(adapter))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Changes the CRB winकरोw to the specअगरied winकरोw.
 */
 /* Returns < 0 अगर off is not valid,
 *	 1 अगर winकरोw access is needed. 'off' is set to offset from
 *	   CRB space in 128M pci map
 *	 0 अगर no winकरोw access is needed. 'off' is set to 2M addr
 * In: 'off' is offset from base in 128M pci map
 */
अटल पूर्णांक qlcnic_pci_get_crb_addr_2M(काष्ठा qlcnic_hardware_context *ahw,
				      uदीर्घ off, व्योम __iomem **addr)
अणु
	स्थिर काष्ठा crb_128M_2M_sub_block_map *m;

	अगर ((off >= QLCNIC_CRB_MAX) || (off < QLCNIC_PCI_CRBSPACE))
		वापस -EINVAL;

	off -= QLCNIC_PCI_CRBSPACE;

	/*
	 * Try direct map
	 */
	m = &crb_128M_2M_map[CRB_BLK(off)].sub_block[CRB_SUBBLK(off)];

	अगर (m->valid && (m->start_128M <= off) && (m->end_128M > off)) अणु
		*addr = ahw->pci_base0 + m->start_2M +
			(off - m->start_128M);
		वापस 0;
	पूर्ण

	/*
	 * Not in direct map, use crb winकरोw
	 */
	*addr = ahw->pci_base0 + CRB_INसूचीECT_2M + (off & MASK(16));
	वापस 1;
पूर्ण

/*
 * In: 'off' is offset from CRB space in 128M pci map
 * Out: 'off' is 2M pci map addr
 * side effect: lock crb winकरोw
 */
अटल पूर्णांक
qlcnic_pci_set_crbwinकरोw_2M(काष्ठा qlcnic_adapter *adapter, uदीर्घ off)
अणु
	u32 winकरोw;
	व्योम __iomem *addr = adapter->ahw->pci_base0 + CRB_WINDOW_2M;

	off -= QLCNIC_PCI_CRBSPACE;

	winकरोw = CRB_HI(off);
	अगर (winकरोw == 0) अणु
		dev_err(&adapter->pdev->dev, "Invalid offset 0x%lx\n", off);
		वापस -EIO;
	पूर्ण

	ग_लिखोl(winकरोw, addr);
	अगर (पढ़ोl(addr) != winकरोw) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(&adapter->pdev->dev,
				"failed to set CRB window to %d off 0x%lx\n",
				winकरोw, off);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_hw_ग_लिखो_wx_2M(काष्ठा qlcnic_adapter *adapter, uदीर्घ off,
			       u32 data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;
	व्योम __iomem *addr = शून्य;

	rv = qlcnic_pci_get_crb_addr_2M(adapter->ahw, off, &addr);

	अगर (rv == 0) अणु
		ग_लिखोl(data, addr);
		वापस 0;
	पूर्ण

	अगर (rv > 0) अणु
		/* indirect access */
		ग_लिखो_lock_irqsave(&adapter->ahw->crb_lock, flags);
		crb_win_lock(adapter);
		rv = qlcnic_pci_set_crbwinकरोw_2M(adapter, off);
		अगर (!rv)
			ग_लिखोl(data, addr);
		crb_win_unlock(adapter);
		ग_लिखो_unlock_irqrestore(&adapter->ahw->crb_lock, flags);
		वापस rv;
	पूर्ण

	dev_err(&adapter->pdev->dev,
			"%s: invalid offset: 0x%016lx\n", __func__, off);
	dump_stack();
	वापस -EIO;
पूर्ण

पूर्णांक qlcnic_82xx_hw_पढ़ो_wx_2M(काष्ठा qlcnic_adapter *adapter, uदीर्घ off,
			      पूर्णांक *err)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;
	u32 data = -1;
	व्योम __iomem *addr = शून्य;

	rv = qlcnic_pci_get_crb_addr_2M(adapter->ahw, off, &addr);

	अगर (rv == 0)
		वापस पढ़ोl(addr);

	अगर (rv > 0) अणु
		/* indirect access */
		ग_लिखो_lock_irqsave(&adapter->ahw->crb_lock, flags);
		crb_win_lock(adapter);
		अगर (!qlcnic_pci_set_crbwinकरोw_2M(adapter, off))
			data = पढ़ोl(addr);
		crb_win_unlock(adapter);
		ग_लिखो_unlock_irqrestore(&adapter->ahw->crb_lock, flags);
		वापस data;
	पूर्ण

	dev_err(&adapter->pdev->dev,
			"%s: invalid offset: 0x%016lx\n", __func__, off);
	dump_stack();
	वापस -1;
पूर्ण

व्योम __iomem *qlcnic_get_ioaddr(काष्ठा qlcnic_hardware_context *ahw,
				u32 offset)
अणु
	व्योम __iomem *addr = शून्य;

	WARN_ON(qlcnic_pci_get_crb_addr_2M(ahw, offset, &addr));

	वापस addr;
पूर्ण

अटल पूर्णांक qlcnic_pci_mem_access_direct(काष्ठा qlcnic_adapter *adapter,
					u32 winकरोw, u64 off, u64 *data, पूर्णांक op)
अणु
	व्योम __iomem *addr;
	u32 start;

	mutex_lock(&adapter->ahw->mem_lock);

	ग_लिखोl(winकरोw, adapter->ahw->ocm_win_crb);
	/* पढ़ो back to flush */
	पढ़ोl(adapter->ahw->ocm_win_crb);
	start = QLCNIC_PCI_OCM0_2M + off;

	addr = adapter->ahw->pci_base0 + start;

	अगर (op == 0)	/* पढ़ो */
		*data = पढ़ोq(addr);
	अन्यथा		/* ग_लिखो */
		ग_लिखोq(*data, addr);

	/* Set winकरोw to 0 */
	ग_लिखोl(0, adapter->ahw->ocm_win_crb);
	पढ़ोl(adapter->ahw->ocm_win_crb);

	mutex_unlock(&adapter->ahw->mem_lock);
	वापस 0;
पूर्ण

अटल व्योम
qlcnic_pci_camqm_पढ़ो_2M(काष्ठा qlcnic_adapter *adapter, u64 off, u64 *data)
अणु
	व्योम __iomem *addr = adapter->ahw->pci_base0 +
		QLCNIC_PCI_CAMQM_2M_BASE + (off - QLCNIC_PCI_CAMQM);

	mutex_lock(&adapter->ahw->mem_lock);
	*data = पढ़ोq(addr);
	mutex_unlock(&adapter->ahw->mem_lock);
पूर्ण

अटल व्योम
qlcnic_pci_camqm_ग_लिखो_2M(काष्ठा qlcnic_adapter *adapter, u64 off, u64 data)
अणु
	व्योम __iomem *addr = adapter->ahw->pci_base0 +
		QLCNIC_PCI_CAMQM_2M_BASE + (off - QLCNIC_PCI_CAMQM);

	mutex_lock(&adapter->ahw->mem_lock);
	ग_लिखोq(data, addr);
	mutex_unlock(&adapter->ahw->mem_lock);
पूर्ण



/* Set MS memory control data क्रम dअगरferent adapters */
अटल व्योम qlcnic_set_ms_controls(काष्ठा qlcnic_adapter *adapter, u64 off,
				   काष्ठा qlcnic_ms_reg_ctrl *ms)
अणु
	ms->control = QLCNIC_MS_CTRL;
	ms->low = QLCNIC_MS_ADDR_LO;
	ms->hi = QLCNIC_MS_ADDR_HI;
	अगर (off & 0xf) अणु
		ms->wd[0] = QLCNIC_MS_WRTDATA_LO;
		ms->rd[0] = QLCNIC_MS_RDDATA_LO;
		ms->wd[1] = QLCNIC_MS_WRTDATA_HI;
		ms->rd[1] = QLCNIC_MS_RDDATA_HI;
		ms->wd[2] = QLCNIC_MS_WRTDATA_ULO;
		ms->wd[3] = QLCNIC_MS_WRTDATA_UHI;
		ms->rd[2] = QLCNIC_MS_RDDATA_ULO;
		ms->rd[3] = QLCNIC_MS_RDDATA_UHI;
	पूर्ण अन्यथा अणु
		ms->wd[0] = QLCNIC_MS_WRTDATA_ULO;
		ms->rd[0] = QLCNIC_MS_RDDATA_ULO;
		ms->wd[1] = QLCNIC_MS_WRTDATA_UHI;
		ms->rd[1] = QLCNIC_MS_RDDATA_UHI;
		ms->wd[2] = QLCNIC_MS_WRTDATA_LO;
		ms->wd[3] = QLCNIC_MS_WRTDATA_HI;
		ms->rd[2] = QLCNIC_MS_RDDATA_LO;
		ms->rd[3] = QLCNIC_MS_RDDATA_HI;
	पूर्ण

	ms->ocm_winकरोw = OCM_WIN_P3P(off);
	ms->off = GET_MEM_OFFS_2M(off);
पूर्ण

पूर्णांक qlcnic_pci_mem_ग_लिखो_2M(काष्ठा qlcnic_adapter *adapter, u64 off, u64 data)
अणु
	पूर्णांक j, ret = 0;
	u32 temp, off8;
	काष्ठा qlcnic_ms_reg_ctrl ms;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;

	स_रखो(&ms, 0, माप(काष्ठा qlcnic_ms_reg_ctrl));
	अगर (!(ADDR_IN_RANGE(off, QLCNIC_ADDR_QDR_NET,
			    QLCNIC_ADDR_QDR_NET_MAX) ||
	      ADDR_IN_RANGE(off, QLCNIC_ADDR_DDR_NET,
			    QLCNIC_ADDR_DDR_NET_MAX)))
		वापस -EIO;

	qlcnic_set_ms_controls(adapter, off, &ms);

	अगर (ADDR_IN_RANGE(off, QLCNIC_ADDR_OCM0, QLCNIC_ADDR_OCM0_MAX))
		वापस qlcnic_pci_mem_access_direct(adapter, ms.ocm_winकरोw,
						    ms.off, &data, 1);

	off8 = off & ~0xf;

	mutex_lock(&adapter->ahw->mem_lock);

	qlcnic_ind_wr(adapter, ms.low, off8);
	qlcnic_ind_wr(adapter, ms.hi, 0);

	qlcnic_ind_wr(adapter, ms.control, TA_CTL_ENABLE);
	qlcnic_ind_wr(adapter, ms.control, QLCNIC_TA_START_ENABLE);

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = qlcnic_ind_rd(adapter, ms.control);
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* This is the modअगरy part of पढ़ो-modअगरy-ग_लिखो */
	qlcnic_ind_wr(adapter, ms.wd[0], qlcnic_ind_rd(adapter, ms.rd[0]));
	qlcnic_ind_wr(adapter, ms.wd[1], qlcnic_ind_rd(adapter, ms.rd[1]));
	/* This is the ग_लिखो part of पढ़ो-modअगरy-ग_लिखो */
	qlcnic_ind_wr(adapter, ms.wd[2], data & 0xffffffff);
	qlcnic_ind_wr(adapter, ms.wd[3], (data >> 32) & 0xffffffff);

	qlcnic_ind_wr(adapter, ms.control, QLCNIC_TA_WRITE_ENABLE);
	qlcnic_ind_wr(adapter, ms.control, QLCNIC_TA_WRITE_START);

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = qlcnic_ind_rd(adapter, ms.control);
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

करोne:
	mutex_unlock(&adapter->ahw->mem_lock);

	वापस ret;
पूर्ण

पूर्णांक qlcnic_pci_mem_पढ़ो_2M(काष्ठा qlcnic_adapter *adapter, u64 off, u64 *data)
अणु
	पूर्णांक j, ret;
	u32 temp, off8;
	u64 val;
	काष्ठा qlcnic_ms_reg_ctrl ms;

	/* Only 64-bit aligned access */
	अगर (off & 7)
		वापस -EIO;
	अगर (!(ADDR_IN_RANGE(off, QLCNIC_ADDR_QDR_NET,
			    QLCNIC_ADDR_QDR_NET_MAX) ||
	      ADDR_IN_RANGE(off, QLCNIC_ADDR_DDR_NET,
			    QLCNIC_ADDR_DDR_NET_MAX)))
		वापस -EIO;

	स_रखो(&ms, 0, माप(काष्ठा qlcnic_ms_reg_ctrl));
	qlcnic_set_ms_controls(adapter, off, &ms);

	अगर (ADDR_IN_RANGE(off, QLCNIC_ADDR_OCM0, QLCNIC_ADDR_OCM0_MAX))
		वापस qlcnic_pci_mem_access_direct(adapter, ms.ocm_winकरोw,
						    ms.off, data, 0);

	mutex_lock(&adapter->ahw->mem_lock);

	off8 = off & ~0xf;

	qlcnic_ind_wr(adapter, ms.low, off8);
	qlcnic_ind_wr(adapter, ms.hi, 0);

	qlcnic_ind_wr(adapter, ms.control, TA_CTL_ENABLE);
	qlcnic_ind_wr(adapter, ms.control, QLCNIC_TA_START_ENABLE);

	क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
		temp = qlcnic_ind_rd(adapter, ms.control);
		अगर ((temp & TA_CTL_BUSY) == 0)
			अवरोध;
	पूर्ण

	अगर (j >= MAX_CTL_CHECK) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
		ret = -EIO;
	पूर्ण अन्यथा अणु

		temp = qlcnic_ind_rd(adapter, ms.rd[3]);
		val = (u64)temp << 32;
		val |= qlcnic_ind_rd(adapter, ms.rd[2]);
		*data = val;
		ret = 0;
	पूर्ण

	mutex_unlock(&adapter->ahw->mem_lock);

	वापस ret;
पूर्ण

पूर्णांक qlcnic_82xx_get_board_info(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक offset, board_type, magic, err = 0;
	काष्ठा pci_dev *pdev = adapter->pdev;

	offset = QLCNIC_FW_MAGIC_OFFSET;
	अगर (qlcnic_rom_fast_पढ़ो(adapter, offset, &magic))
		वापस -EIO;

	अगर (magic != QLCNIC_BDINFO_MAGIC) अणु
		dev_err(&pdev->dev, "invalid board config, magic=%08x\n",
			magic);
		वापस -EIO;
	पूर्ण

	offset = QLCNIC_BRDTYPE_OFFSET;
	अगर (qlcnic_rom_fast_पढ़ो(adapter, offset, &board_type))
		वापस -EIO;

	adapter->ahw->board_type = board_type;

	अगर (board_type == QLCNIC_BRDTYPE_P3P_4_GB_MM) अणु
		u32 gpio = QLCRD32(adapter, QLCNIC_ROMUSB_GLB_PAD_GPIO_I, &err);
		अगर (err == -EIO)
			वापस err;
		अगर ((gpio & 0x8000) == 0)
			board_type = QLCNIC_BRDTYPE_P3P_10G_TP;
	पूर्ण

	चयन (board_type) अणु
	हाल QLCNIC_BRDTYPE_P3P_HMEZ:
	हाल QLCNIC_BRDTYPE_P3P_XG_LOM:
	हाल QLCNIC_BRDTYPE_P3P_10G_CX4:
	हाल QLCNIC_BRDTYPE_P3P_10G_CX4_LP:
	हाल QLCNIC_BRDTYPE_P3P_IMEZ:
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS:
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_CT:
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_QT:
	हाल QLCNIC_BRDTYPE_P3P_10G_XFP:
	हाल QLCNIC_BRDTYPE_P3P_10000_BASE_T:
		adapter->ahw->port_type = QLCNIC_XGBE;
		अवरोध;
	हाल QLCNIC_BRDTYPE_P3P_REF_QG:
	हाल QLCNIC_BRDTYPE_P3P_4_GB:
	हाल QLCNIC_BRDTYPE_P3P_4_GB_MM:
		adapter->ahw->port_type = QLCNIC_GBE;
		अवरोध;
	हाल QLCNIC_BRDTYPE_P3P_10G_TP:
		adapter->ahw->port_type = (adapter->portnum < 2) ?
			QLCNIC_XGBE : QLCNIC_GBE;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unknown board type %x\n", board_type);
		adapter->ahw->port_type = QLCNIC_XGBE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_wol_supported(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 wol_cfg;
	पूर्णांक err = 0;

	wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG_NV, &err);
	अगर (wol_cfg & (1UL << adapter->portnum)) अणु
		wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG, &err);
		अगर (err == -EIO)
			वापस err;
		अगर (wol_cfg & (1 << adapter->portnum))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_config_led(काष्ठा qlcnic_adapter *adapter, u32 state, u32 rate)
अणु
	काष्ठा qlcnic_nic_req   req;
	पूर्णांक rv;
	u64 word;

	स_रखो(&req, 0, माप(काष्ठा qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_LED | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(((u64)rate << 32) | adapter->portnum);
	req.words[1] = cpu_to_le64(state);

	rv = qlcnic_send_cmd_descs(adapter, (काष्ठा cmd_desc_type0 *)&req, 1);
	अगर (rv)
		dev_err(&adapter->pdev->dev, "LED configuration failed.\n");

	वापस rv;
पूर्ण

व्योम qlcnic_82xx_get_beacon_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	u8 beacon_state;
	पूर्णांक err = 0;

	अगर (ahw->extra_capability[0] & QLCNIC_FW_CAPABILITY_2_BEACON) अणु
		err = qlcnic_alloc_mbx_args(&cmd, adapter,
					    QLCNIC_CMD_GET_LED_STATUS);
		अगर (!err) अणु
			err = qlcnic_issue_cmd(adapter, &cmd);
			अगर (err) अणु
				netdev_err(adapter->netdev,
					   "Failed to get current beacon state, err=%d\n",
					   err);
			पूर्ण अन्यथा अणु
				beacon_state = cmd.rsp.arg[1];
				अगर (beacon_state == QLCNIC_BEACON_DISABLE)
					ahw->beacon_state = QLCNIC_BEACON_OFF;
				अन्यथा अगर (beacon_state == QLCNIC_BEACON_EANBLE)
					ahw->beacon_state = QLCNIC_BEACON_ON;
			पूर्ण
		पूर्ण
		qlcnic_मुक्त_mbx_args(&cmd);
	पूर्ण

	वापस;
पूर्ण

व्योम qlcnic_82xx_get_func_no(काष्ठा qlcnic_adapter *adapter)
अणु
	व्योम __iomem *msix_base_addr;
	u32 func;
	u32 msix_base;

	pci_पढ़ो_config_dword(adapter->pdev, QLCNIC_MSIX_TABLE_OFFSET, &func);
	msix_base_addr = adapter->ahw->pci_base0 + QLCNIC_MSIX_BASE;
	msix_base = पढ़ोl(msix_base_addr);
	func = (func - msix_base) / QLCNIC_MSIX_TBL_PGSIZE;
	adapter->ahw->pci_func = func;
पूर्ण

व्योम qlcnic_82xx_पढ़ो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
			  loff_t offset, माप_प्रकार size)
अणु
	पूर्णांक err = 0;
	u32 data;
	u64 qmdata;

	अगर (ADDR_IN_RANGE(offset, QLCNIC_PCI_CAMQM, QLCNIC_PCI_CAMQM_END)) अणु
		qlcnic_pci_camqm_पढ़ो_2M(adapter, offset, &qmdata);
		स_नकल(buf, &qmdata, size);
	पूर्ण अन्यथा अणु
		data = QLCRD32(adapter, offset, &err);
		स_नकल(buf, &data, size);
	पूर्ण
पूर्ण

व्योम qlcnic_82xx_ग_लिखो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
			   loff_t offset, माप_प्रकार size)
अणु
	u32 data;
	u64 qmdata;

	अगर (ADDR_IN_RANGE(offset, QLCNIC_PCI_CAMQM, QLCNIC_PCI_CAMQM_END)) अणु
		स_नकल(&qmdata, buf, size);
		qlcnic_pci_camqm_ग_लिखो_2M(adapter, offset, qmdata);
	पूर्ण अन्यथा अणु
		स_नकल(&data, buf, size);
		QLCWR32(adapter, offset, data);
	पूर्ण
पूर्ण

पूर्णांक qlcnic_82xx_api_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस qlcnic_pcie_sem_lock(adapter, 5, 0);
पूर्ण

व्योम qlcnic_82xx_api_unlock(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_pcie_sem_unlock(adapter, 5);
पूर्ण

पूर्णांक qlcnic_82xx_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);

	qlcnic_cancel_idc_work(adapter);

	अगर (netअगर_running(netdev))
		qlcnic_करोwn(adapter, netdev);

	qlcnic_clr_all_drv_state(adapter, 0);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	अगर (qlcnic_wol_supported(adapter))
		device_wakeup_enable(&pdev->dev);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_resume(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	err = qlcnic_start_firmware(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev, "failed to start firmware\n");
		वापस err;
	पूर्ण

	अगर (netअगर_running(netdev)) अणु
		err = qlcnic_up(adapter, netdev);
		अगर (!err)
			qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण

	netअगर_device_attach(netdev);
	qlcnic_schedule_work(adapter, qlcnic_fw_poll_work, FW_POLL_DELAY);
	वापस err;
पूर्ण
