<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/ratelimit.h>
#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_inline.h"

#समावेश <linux/io-64-nonatomic-lo-hi.h>

#घोषणा TIMEOUT_100_MS	100
#घोषणा MASK(n)		DMA_BIT_MASK(n)
#घोषणा MN_WIN(addr)	(((addr & 0x1fc0000) >> 1) | ((addr >> 25) & 0x3ff))
#घोषणा OCM_WIN(addr)	(((addr & 0x1ff0000) >> 1) | ((addr >> 25) & 0x3ff))
#घोषणा MS_WIN(addr)	(addr & 0x0ffc0000)
#घोषणा QLA82XX_PCI_MN_2M	(0)
#घोषणा QLA82XX_PCI_MS_2M	(0x80000)
#घोषणा QLA82XX_PCI_OCM0_2M	(0xc0000)
#घोषणा VALID_OCM_ADDR(addr)	(((addr) & 0x3f800) != 0x3f800)
#घोषणा GET_MEM_OFFS_2M(addr)	(addr & MASK(18))

/* CRB winकरोw related */
#घोषणा CRB_BLK(off)	((off >> 20) & 0x3f)
#घोषणा CRB_SUBBLK(off)	((off >> 16) & 0xf)
#घोषणा CRB_WINDOW_2M	(0x130060)
#घोषणा CRB_HI(off)	((qla4_82xx_crb_hub_agt[CRB_BLK(off)] << 20) | \
			((off) & 0xf0000))
#घोषणा QLA82XX_PCI_CAMQM_2M_END	(0x04800800UL)
#घोषणा QLA82XX_PCI_CAMQM_2M_BASE	(0x000ff800UL)
#घोषणा CRB_INसूचीECT_2M			(0x1e0000UL)

अटल अंतरभूत व्योम __iomem *
qla4_8xxx_pci_base_offsetfset(काष्ठा scsi_qla_host *ha, अचिन्हित दीर्घ off)
अणु
	अगर ((off < ha->first_page_group_end) &&
	    (off >= ha->first_page_group_start))
		वापस (व्योम __iomem *)(ha->nx_pcibase + off);

	वापस शून्य;
पूर्ण

अटल स्थिर पूर्णांक MD_MIU_TEST_AGT_RDDATA[] = अणु 0x410000A8,
				0x410000AC, 0x410000B8, 0x410000BC पूर्ण;
#घोषणा MAX_CRB_XFORM 60
अटल अचिन्हित दीर्घ crb_addr_xक्रमm[MAX_CRB_XFORM];
अटल पूर्णांक qla4_8xxx_crb_table_initialized;

#घोषणा qla4_8xxx_crb_addr_transक्रमm(name) \
	(crb_addr_xक्रमm[QLA82XX_HW_PX_MAP_CRB_##name] = \
	 QLA82XX_HW_CRB_HUB_AGT_ADR_##name << 20)
अटल व्योम
qla4_82xx_crb_addr_transक्रमm_setup(व्योम)
अणु
	qla4_8xxx_crb_addr_transक्रमm(XDMA);
	qla4_8xxx_crb_addr_transक्रमm(TIMR);
	qla4_8xxx_crb_addr_transक्रमm(SRE);
	qla4_8xxx_crb_addr_transक्रमm(SQN3);
	qla4_8xxx_crb_addr_transक्रमm(SQN2);
	qla4_8xxx_crb_addr_transक्रमm(SQN1);
	qla4_8xxx_crb_addr_transक्रमm(SQN0);
	qla4_8xxx_crb_addr_transक्रमm(SQS3);
	qla4_8xxx_crb_addr_transक्रमm(SQS2);
	qla4_8xxx_crb_addr_transक्रमm(SQS1);
	qla4_8xxx_crb_addr_transक्रमm(SQS0);
	qla4_8xxx_crb_addr_transक्रमm(RPMX7);
	qla4_8xxx_crb_addr_transक्रमm(RPMX6);
	qla4_8xxx_crb_addr_transक्रमm(RPMX5);
	qla4_8xxx_crb_addr_transक्रमm(RPMX4);
	qla4_8xxx_crb_addr_transक्रमm(RPMX3);
	qla4_8xxx_crb_addr_transक्रमm(RPMX2);
	qla4_8xxx_crb_addr_transक्रमm(RPMX1);
	qla4_8xxx_crb_addr_transक्रमm(RPMX0);
	qla4_8xxx_crb_addr_transक्रमm(ROMUSB);
	qla4_8xxx_crb_addr_transक्रमm(SN);
	qla4_8xxx_crb_addr_transक्रमm(QMN);
	qla4_8xxx_crb_addr_transक्रमm(QMS);
	qla4_8xxx_crb_addr_transक्रमm(PGNI);
	qla4_8xxx_crb_addr_transक्रमm(PGND);
	qla4_8xxx_crb_addr_transक्रमm(PGN3);
	qla4_8xxx_crb_addr_transक्रमm(PGN2);
	qla4_8xxx_crb_addr_transक्रमm(PGN1);
	qla4_8xxx_crb_addr_transक्रमm(PGN0);
	qla4_8xxx_crb_addr_transक्रमm(PGSI);
	qla4_8xxx_crb_addr_transक्रमm(PGSD);
	qla4_8xxx_crb_addr_transक्रमm(PGS3);
	qla4_8xxx_crb_addr_transक्रमm(PGS2);
	qla4_8xxx_crb_addr_transक्रमm(PGS1);
	qla4_8xxx_crb_addr_transक्रमm(PGS0);
	qla4_8xxx_crb_addr_transक्रमm(PS);
	qla4_8xxx_crb_addr_transक्रमm(PH);
	qla4_8xxx_crb_addr_transक्रमm(NIU);
	qla4_8xxx_crb_addr_transक्रमm(I2Q);
	qla4_8xxx_crb_addr_transक्रमm(EG);
	qla4_8xxx_crb_addr_transक्रमm(MN);
	qla4_8xxx_crb_addr_transक्रमm(MS);
	qla4_8xxx_crb_addr_transक्रमm(CAS2);
	qla4_8xxx_crb_addr_transक्रमm(CAS1);
	qla4_8xxx_crb_addr_transक्रमm(CAS0);
	qla4_8xxx_crb_addr_transक्रमm(CAM);
	qla4_8xxx_crb_addr_transक्रमm(C2C1);
	qla4_8xxx_crb_addr_transक्रमm(C2C0);
	qla4_8xxx_crb_addr_transक्रमm(SMB);
	qla4_8xxx_crb_addr_transक्रमm(OCM0);
	qla4_8xxx_crb_addr_transक्रमm(I2C0);

	qla4_8xxx_crb_table_initialized = 1;
पूर्ण

अटल काष्ठा crb_128M_2M_block_map crb_128M_2M_map[64] = अणु
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
	अणुअणुअणु1, 0x3d00000, 0x3d04000, 0x1dc000पूर्ण पूर्ण पूर्ण,/* 61: LPC */
	अणुअणुअणु1, 0x3e00000, 0x3e01000, 0x167000पूर्ण पूर्ण पूर्ण,/* 62: P2NC */
	अणुअणुअणु1, 0x3f00000, 0x3f01000, 0x168000पूर्ण पूर्ण पूर्ण	/* 63: P2NR0 */
पूर्ण;

/*
 * top 12 bits of crb पूर्णांकernal address (hub, agent)
 */
अटल अचिन्हित qla4_82xx_crb_hub_agt[64] = अणु
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PS,
	QLA82XX_HW_CRB_HUB_AGT_ADR_MN,
	QLA82XX_HW_CRB_HUB_AGT_ADR_MS,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SRE,
	QLA82XX_HW_CRB_HUB_AGT_ADR_NIU,
	QLA82XX_HW_CRB_HUB_AGT_ADR_QMN,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SQN0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SQN1,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SQN2,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SQN3,
	QLA82XX_HW_CRB_HUB_AGT_ADR_I2Q,
	QLA82XX_HW_CRB_HUB_AGT_ADR_TIMR,
	QLA82XX_HW_CRB_HUB_AGT_ADR_ROMUSB,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGN4,
	QLA82XX_HW_CRB_HUB_AGT_ADR_XDMA,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGN0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGN1,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGN2,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGN3,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGND,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGNI,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGS0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGS1,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGS2,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGS3,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGSI,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SN,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_EG,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PS,
	QLA82XX_HW_CRB_HUB_AGT_ADR_CAM,
	0,
	0,
	0,
	0,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_TIMR,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX1,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX2,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX3,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX4,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX5,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX6,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX7,
	QLA82XX_HW_CRB_HUB_AGT_ADR_XDMA,
	QLA82XX_HW_CRB_HUB_AGT_ADR_I2Q,
	QLA82XX_HW_CRB_HUB_AGT_ADR_ROMUSB,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX8,
	QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX9,
	QLA82XX_HW_CRB_HUB_AGT_ADR_OCM0,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_SMB,
	QLA82XX_HW_CRB_HUB_AGT_ADR_I2C0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_I2C1,
	0,
	QLA82XX_HW_CRB_HUB_AGT_ADR_PGNC,
	0,
पूर्ण;

/* Device states */
अटल अक्षर *qdev_state[] = अणु
	"Unknown",
	"Cold",
	"Initializing",
	"Ready",
	"Need Reset",
	"Need Quiescent",
	"Failed",
	"Quiescent",
पूर्ण;

/*
 * In: 'off' is offset from CRB space in 128M pci map
 * Out: 'off' is 2M pci map addr
 * side effect: lock crb winकरोw
 */
अटल व्योम
qla4_82xx_pci_set_crbwinकरोw_2M(काष्ठा scsi_qla_host *ha, uदीर्घ *off)
अणु
	u32 win_पढ़ो;

	ha->crb_win = CRB_HI(*off);
	ग_लिखोl(ha->crb_win,
		(व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));

	/* Read back value to make sure ग_लिखो has gone through beक्रमe trying
	* to use it. */
	win_पढ़ो = पढ़ोl((व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));
	अगर (win_पढ़ो != ha->crb_win) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "%s: Written crbwin (0x%x) != Read crbwin (0x%x),"
		    " off=0x%lx\n", __func__, ha->crb_win, win_पढ़ो, *off));
	पूर्ण
	*off = (*off & MASK(16)) + CRB_INसूचीECT_2M + ha->nx_pcibase;
पूर्ण

#घोषणा CRB_WIN_LOCK_TIMEOUT 100000000

/*
 * Context: atomic
 */
अटल पूर्णांक qla4_82xx_crb_win_lock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक करोne = 0, समयout = 0;

	जबतक (!करोne) अणु
		/* acquire semaphore3 from PCI HW block */
		करोne = qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (समयout >= CRB_WIN_LOCK_TIMEOUT)
			वापस -1;

		समयout++;
		udelay(10);
	पूर्ण
	qla4_82xx_wr_32(ha, QLA82XX_CRB_WIN_LOCK_ID, ha->func_num);
	वापस 0;
पूर्ण

व्योम qla4_82xx_crb_win_unlock(काष्ठा scsi_qla_host *ha)
अणु
	qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_UNLOCK));
पूर्ण

व्योम
qla4_82xx_wr_32(काष्ठा scsi_qla_host *ha, uदीर्घ off, u32 data)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rv;

	rv = qla4_82xx_pci_get_crb_addr_2M(ha, &off);

	BUG_ON(rv == -1);

	अगर (rv == 1) अणु
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
		qla4_82xx_crb_win_lock(ha);
		qla4_82xx_pci_set_crbwinकरोw_2M(ha, &off);
	पूर्ण

	ग_लिखोl(data, (व्योम __iomem *)off);

	अगर (rv == 1) अणु
		qla4_82xx_crb_win_unlock(ha);
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	पूर्ण
पूर्ण

uपूर्णांक32_t qla4_82xx_rd_32(काष्ठा scsi_qla_host *ha, uदीर्घ off)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rv;
	u32 data;

	rv = qla4_82xx_pci_get_crb_addr_2M(ha, &off);

	BUG_ON(rv == -1);

	अगर (rv == 1) अणु
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
		qla4_82xx_crb_win_lock(ha);
		qla4_82xx_pci_set_crbwinकरोw_2M(ha, &off);
	पूर्ण
	data = पढ़ोl((व्योम __iomem *)off);

	अगर (rv == 1) अणु
		qla4_82xx_crb_win_unlock(ha);
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	पूर्ण
	वापस data;
पूर्ण

/* Minidump related functions */
पूर्णांक qla4_82xx_md_rd_32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t off, uपूर्णांक32_t *data)
अणु
	uपूर्णांक32_t win_पढ़ो, off_value;
	पूर्णांक rval = QLA_SUCCESS;

	off_value  = off & 0xFFFF0000;
	ग_लिखोl(off_value, (व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));

	/*
	 * Read back value to make sure ग_लिखो has gone through beक्रमe trying
	 * to use it.
	 */
	win_पढ़ो = पढ़ोl((व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));
	अगर (win_पढ़ो != off_value) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Written (0x%x) != Read (0x%x), off=0x%x\n",
				  __func__, off_value, win_पढ़ो, off));
		rval = QLA_ERROR;
	पूर्ण अन्यथा अणु
		off_value  = off & 0x0000FFFF;
		*data = पढ़ोl((व्योम __iomem *)(off_value + CRB_INसूचीECT_2M +
					       ha->nx_pcibase));
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक qla4_82xx_md_wr_32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t off, uपूर्णांक32_t data)
अणु
	uपूर्णांक32_t win_पढ़ो, off_value;
	पूर्णांक rval = QLA_SUCCESS;

	off_value  = off & 0xFFFF0000;
	ग_लिखोl(off_value, (व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));

	/* Read back value to make sure ग_लिखो has gone through beक्रमe trying
	 * to use it.
	 */
	win_पढ़ो = पढ़ोl((व्योम __iomem *)(CRB_WINDOW_2M + ha->nx_pcibase));
	अगर (win_पढ़ो != off_value) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Written (0x%x) != Read (0x%x), off=0x%x\n",
				  __func__, off_value, win_पढ़ो, off));
		rval = QLA_ERROR;
	पूर्ण अन्यथा अणु
		off_value  = off & 0x0000FFFF;
		ग_लिखोl(data, (व्योम __iomem *)(off_value + CRB_INसूचीECT_2M +
					      ha->nx_pcibase));
	पूर्ण
	वापस rval;
पूर्ण

#घोषणा IDC_LOCK_TIMEOUT 100000000

/**
 * qla4_82xx_idc_lock - hw_lock
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * General purpose lock used to synchronize access to
 * CRB_DEV_STATE, CRB_DEV_REF_COUNT, etc.
 *
 * Context: task, can sleep
 **/
पूर्णांक qla4_82xx_idc_lock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक करोne = 0, समयout = 0;

	might_sleep();

	जबतक (!करोne) अणु
		/* acquire semaphore5 from PCI HW block */
		करोne = qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM5_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (समयout >= IDC_LOCK_TIMEOUT)
			वापस -1;

		समयout++;
		msleep(100);
	पूर्ण
	वापस 0;
पूर्ण

व्योम qla4_82xx_idc_unlock(काष्ठा scsi_qla_host *ha)
अणु
	qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM5_UNLOCK));
पूर्ण

पूर्णांक
qla4_82xx_pci_get_crb_addr_2M(काष्ठा scsi_qla_host *ha, uदीर्घ *off)
अणु
	काष्ठा crb_128M_2M_sub_block_map *m;

	अगर (*off >= QLA82XX_CRB_MAX)
		वापस -1;

	अगर (*off >= QLA82XX_PCI_CAMQM && (*off < QLA82XX_PCI_CAMQM_2M_END)) अणु
		*off = (*off - QLA82XX_PCI_CAMQM) +
		    QLA82XX_PCI_CAMQM_2M_BASE + ha->nx_pcibase;
		वापस 0;
	पूर्ण

	अगर (*off < QLA82XX_PCI_CRBSPACE)
		वापस -1;

	*off -= QLA82XX_PCI_CRBSPACE;
	/*
	 * Try direct map
	 */

	m = &crb_128M_2M_map[CRB_BLK(*off)].sub_block[CRB_SUBBLK(*off)];

	अगर (m->valid && (m->start_128M <= *off) && (m->end_128M > *off)) अणु
		*off = *off + m->start_2M - m->start_128M + ha->nx_pcibase;
		वापस 0;
	पूर्ण

	/*
	 * Not in direct map, use crb winकरोw
	 */
	वापस 1;
पूर्ण

/*
* check memory access boundary.
* used by test agent. support ddr access only क्रम now
*/
अटल अचिन्हित दीर्घ
qla4_82xx_pci_mem_bound_check(काष्ठा scsi_qla_host *ha,
		अचिन्हित दीर्घ दीर्घ addr, पूर्णांक size)
अणु
	अगर (!QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
	    QLA8XXX_ADDR_DDR_NET_MAX) ||
	    !QLA8XXX_ADDR_IN_RANGE(addr + size - 1,
	    QLA8XXX_ADDR_DDR_NET, QLA8XXX_ADDR_DDR_NET_MAX) ||
	    ((size != 1) && (size != 2) && (size != 4) && (size != 8))) अणु
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक qla4_82xx_pci_set_winकरोw_warning_count;

अटल अचिन्हित दीर्घ
qla4_82xx_pci_set_winकरोw(काष्ठा scsi_qla_host *ha, अचिन्हित दीर्घ दीर्घ addr)
अणु
	पूर्णांक winकरोw;
	u32 win_पढ़ो;

	अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
	    QLA8XXX_ADDR_DDR_NET_MAX)) अणु
		/* DDR network side */
		winकरोw = MN_WIN(addr);
		ha->ddr_mn_winकरोw = winकरोw;
		qla4_82xx_wr_32(ha, ha->mn_win_crb |
		    QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla4_82xx_rd_32(ha, ha->mn_win_crb |
		    QLA82XX_PCI_CRBSPACE);
		अगर ((win_पढ़ो << 17) != winकरोw) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
			"%s: Written MNwin (0x%x) != Read MNwin (0x%x)\n",
			__func__, winकरोw, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_DDR_NET;
	पूर्ण अन्यथा अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_OCM0,
				QLA8XXX_ADDR_OCM0_MAX)) अणु
		अचिन्हित पूर्णांक temp1;
		/* अगर bits 19:18&17:11 are on */
		अगर ((addr & 0x00ff800) == 0xff800) अणु
			prपूर्णांकk("%s: QM access not handled.\n", __func__);
			addr = -1UL;
		पूर्ण

		winकरोw = OCM_WIN(addr);
		ha->ddr_mn_winकरोw = winकरोw;
		qla4_82xx_wr_32(ha, ha->mn_win_crb |
		    QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla4_82xx_rd_32(ha, ha->mn_win_crb |
		    QLA82XX_PCI_CRBSPACE);
		temp1 = ((winकरोw & 0x1FF) << 7) |
		    ((winकरोw & 0x0FFFE0000) >> 17);
		अगर (win_पढ़ो != temp1) अणु
			prपूर्णांकk("%s: Written OCMwin (0x%x) != Read"
			    " OCMwin (0x%x)\n", __func__, temp1, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_OCM0_2M;

	पूर्ण अन्यथा अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_QDR_NET,
				QLA82XX_P3_ADDR_QDR_NET_MAX)) अणु
		/* QDR network side */
		winकरोw = MS_WIN(addr);
		ha->qdr_sn_winकरोw = winकरोw;
		qla4_82xx_wr_32(ha, ha->ms_win_crb |
		    QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla4_82xx_rd_32(ha,
		     ha->ms_win_crb | QLA82XX_PCI_CRBSPACE);
		अगर (win_पढ़ो != winकरोw) अणु
			prपूर्णांकk("%s: Written MSwin (0x%x) != Read "
			    "MSwin (0x%x)\n", __func__, winकरोw, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_QDR_NET;

	पूर्ण अन्यथा अणु
		/*
		 * peg gdb frequently accesses memory that करोesn't exist,
		 * this limits the chit chat so debugging isn't slowed करोwn.
		 */
		अगर ((qla4_82xx_pci_set_winकरोw_warning_count++ < 8) ||
		    (qla4_82xx_pci_set_winकरोw_warning_count%64 == 0)) अणु
			prपूर्णांकk("%s: Warning:%s Unknown address range!\n",
			    __func__, DRIVER_NAME);
		पूर्ण
		addr = -1UL;
	पूर्ण
	वापस addr;
पूर्ण

/* check अगर address is in the same winकरोws as the previous access */
अटल पूर्णांक qla4_82xx_pci_is_same_winकरोw(काष्ठा scsi_qla_host *ha,
		अचिन्हित दीर्घ दीर्घ addr)
अणु
	पूर्णांक winकरोw;
	अचिन्हित दीर्घ दीर्घ qdr_max;

	qdr_max = QLA82XX_P3_ADDR_QDR_NET_MAX;

	अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
	    QLA8XXX_ADDR_DDR_NET_MAX)) अणु
		/* DDR network side */
		BUG();	/* MN access can not come here */
	पूर्ण अन्यथा अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_OCM0,
	     QLA8XXX_ADDR_OCM0_MAX)) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_OCM1,
	     QLA8XXX_ADDR_OCM1_MAX)) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_QDR_NET,
	    qdr_max)) अणु
		/* QDR network side */
		winकरोw = ((addr - QLA8XXX_ADDR_QDR_NET) >> 22) & 0x3f;
		अगर (ha->qdr_sn_winकरोw == winकरोw)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qla4_82xx_pci_mem_पढ़ो_direct(काष्ठा scsi_qla_host *ha,
		u64 off, व्योम *data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;
	पूर्णांक ret = 0;
	u64 start;
	व्योम __iomem *mem_ptr = शून्य;
	अचिन्हित दीर्घ mem_base;
	अचिन्हित दीर्घ mem_page;

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/*
	 * If attempting to access unknown address or straddle hw winकरोws,
	 * करो not access.
	 */
	start = qla4_82xx_pci_set_winकरोw(ha, off);
	अगर ((start == -1UL) ||
	    (qla4_82xx_pci_is_same_winकरोw(ha, off + size - 1) == 0)) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		prपूर्णांकk(KERN_ERR"%s out of bound pci memory access. "
				"offset is 0x%llx\n", DRIVER_NAME, off);
		वापस -1;
	पूर्ण

	addr = qla4_8xxx_pci_base_offsetfset(ha, start);
	अगर (!addr) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		mem_base = pci_resource_start(ha->pdev, 0);
		mem_page = start & PAGE_MASK;
		/* Map two pages whenever user tries to access addresses in two
		   consecutive pages.
		 */
		अगर (mem_page != ((start + size - 1) & PAGE_MASK))
			mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE * 2);
		अन्यथा
			mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE);

		अगर (mem_ptr == शून्य) अणु
			*(u8 *)data = 0;
			वापस -1;
		पूर्ण
		addr = mem_ptr;
		addr += start & (PAGE_SIZE - 1);
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
	पूर्ण

	चयन (size) अणु
	हाल 1:
		*(u8  *)data = पढ़ोb(addr);
		अवरोध;
	हाल 2:
		*(u16 *)data = पढ़ोw(addr);
		अवरोध;
	हाल 4:
		*(u32 *)data = पढ़ोl(addr);
		अवरोध;
	हाल 8:
		*(u64 *)data = पढ़ोq(addr);
		अवरोध;
	शेष:
		ret = -1;
		अवरोध;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);

	अगर (mem_ptr)
		iounmap(mem_ptr);
	वापस ret;
पूर्ण

अटल पूर्णांक
qla4_82xx_pci_mem_ग_लिखो_direct(काष्ठा scsi_qla_host *ha, u64 off,
		व्योम *data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;
	पूर्णांक ret = 0;
	u64 start;
	व्योम __iomem *mem_ptr = शून्य;
	अचिन्हित दीर्घ mem_base;
	अचिन्हित दीर्घ mem_page;

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/*
	 * If attempting to access unknown address or straddle hw winकरोws,
	 * करो not access.
	 */
	start = qla4_82xx_pci_set_winकरोw(ha, off);
	अगर ((start == -1UL) ||
	    (qla4_82xx_pci_is_same_winकरोw(ha, off + size - 1) == 0)) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		prपूर्णांकk(KERN_ERR"%s out of bound pci memory access. "
				"offset is 0x%llx\n", DRIVER_NAME, off);
		वापस -1;
	पूर्ण

	addr = qla4_8xxx_pci_base_offsetfset(ha, start);
	अगर (!addr) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		mem_base = pci_resource_start(ha->pdev, 0);
		mem_page = start & PAGE_MASK;
		/* Map two pages whenever user tries to access addresses in two
		   consecutive pages.
		 */
		अगर (mem_page != ((start + size - 1) & PAGE_MASK))
			mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE*2);
		अन्यथा
			mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE);
		अगर (mem_ptr == शून्य)
			वापस -1;

		addr = mem_ptr;
		addr += start & (PAGE_SIZE - 1);
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
	पूर्ण

	चयन (size) अणु
	हाल 1:
		ग_लिखोb(*(u8 *)data, addr);
		अवरोध;
	हाल 2:
		ग_लिखोw(*(u16 *)data, addr);
		अवरोध;
	हाल 4:
		ग_लिखोl(*(u32 *)data, addr);
		अवरोध;
	हाल 8:
		ग_लिखोq(*(u64 *)data, addr);
		अवरोध;
	शेष:
		ret = -1;
		अवरोध;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	अगर (mem_ptr)
		iounmap(mem_ptr);
	वापस ret;
पूर्ण

#घोषणा MTU_FUDGE_FACTOR 100

अटल अचिन्हित दीर्घ
qla4_82xx_decode_crb_addr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ base_addr, offset, pci_base;

	अगर (!qla4_8xxx_crb_table_initialized)
		qla4_82xx_crb_addr_transक्रमm_setup();

	pci_base = ADDR_ERROR;
	base_addr = addr & 0xfff00000;
	offset = addr & 0x000fffff;

	क्रम (i = 0; i < MAX_CRB_XFORM; i++) अणु
		अगर (crb_addr_xक्रमm[i] == base_addr) अणु
			pci_base = i << 20;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pci_base == ADDR_ERROR)
		वापस pci_base;
	अन्यथा
		वापस pci_base + offset;
पूर्ण

अटल दीर्घ rom_max_समयout = 100;
अटल दीर्घ qla4_82xx_rom_lock_समयout = 100;

/*
 * Context: task, can_sleep
 */
अटल पूर्णांक
qla4_82xx_rom_lock(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक करोne = 0, समयout = 0;

	might_sleep();

	जबतक (!करोne) अणु
		/* acquire semaphore2 from PCI HW block */
		करोne = qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (समयout >= qla4_82xx_rom_lock_समयout)
			वापस -1;

		समयout++;
		msleep(20);
	पूर्ण
	qla4_82xx_wr_32(ha, QLA82XX_ROM_LOCK_ID, ROM_LOCK_DRIVER);
	वापस 0;
पूर्ण

अटल व्योम
qla4_82xx_rom_unlock(काष्ठा scsi_qla_host *ha)
अणु
	qla4_82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_UNLOCK));
पूर्ण

अटल पूर्णांक
qla4_82xx_रुको_rom_करोne(काष्ठा scsi_qla_host *ha)
अणु
	दीर्घ समयout = 0;
	दीर्घ करोne = 0 ;

	जबतक (करोne == 0) अणु
		करोne = qla4_82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_STATUS);
		करोne &= 2;
		समयout++;
		अगर (समयout >= rom_max_समयout) अणु
			prपूर्णांकk("%s: Timeout reached  waiting for rom done",
					DRIVER_NAME);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qla4_82xx_करो_rom_fast_पढ़ो(काष्ठा scsi_qla_host *ha, पूर्णांक addr, पूर्णांक *valp)
अणु
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ADDRESS, addr);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 3);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	अगर (qla4_82xx_रुको_rom_करोne(ha)) अणु
		prपूर्णांकk("%s: Error waiting for rom done\n", DRIVER_NAME);
		वापस -1;
	पूर्ण
	/* reset abyte_cnt and dummy_byte_cnt */
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	udelay(10);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);

	*valp = qla4_82xx_rd_32(ha, QLA82XX_ROMUSB_ROM_RDATA);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla4_82xx_rom_fast_पढ़ो(काष्ठा scsi_qla_host *ha, पूर्णांक addr, पूर्णांक *valp)
अणु
	पूर्णांक ret, loops = 0;

	जबतक ((qla4_82xx_rom_lock(ha) != 0) && (loops < 50000)) अणु
		udelay(100);
		loops++;
	पूर्ण
	अगर (loops >= 50000) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: qla4_82xx_rom_lock failed\n",
			   DRIVER_NAME);
		वापस -1;
	पूर्ण
	ret = qla4_82xx_करो_rom_fast_पढ़ो(ha, addr, valp);
	qla4_82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

/*
 * This routine करोes CRB initialize sequence
 * to put the ISP पूर्णांकo operational state
 */
अटल पूर्णांक
qla4_82xx_pinit_from_rom(काष्ठा scsi_qla_host *ha, पूर्णांक verbose)
अणु
	पूर्णांक addr, val;
	पूर्णांक i ;
	काष्ठा crb_addr_pair *buf;
	अचिन्हित दीर्घ off;
	अचिन्हित offset, n;

	काष्ठा crb_addr_pair अणु
		दीर्घ addr;
		दीर्घ data;
	पूर्ण;

	/* Halt all the inभागiual PEGs and other blocks of the ISP */
	qla4_82xx_rom_lock(ha);

	/* disable all I2Q */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x10, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x14, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x18, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x1c, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x20, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x24, 0x0);

	/* disable all niu पूर्णांकerrupts */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x40, 0xff);
	/* disable xge rx/tx */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x70000, 0x00);
	/* disable xg1 rx/tx */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x80000, 0x00);
	/* disable sideband mac */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x90000, 0x00);
	/* disable ap0 mac */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xa0000, 0x00);
	/* disable ap1 mac */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xb0000, 0x00);

	/* halt sre */
	val = qla4_82xx_rd_32(ha, QLA82XX_CRB_SRE + 0x1000);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_SRE + 0x1000, val & (~(0x1)));

	/* halt epg */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_EPG + 0x1300, 0x1);

	/* halt समयrs */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x0, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x8, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x10, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x18, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x100, 0x0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x200, 0x0);

	/* halt pegs */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x3c, 1);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1 + 0x3c, 1);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2 + 0x3c, 1);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3 + 0x3c, 1);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_4 + 0x3c, 1);
	msleep(5);

	/* big hammer */
	अगर (test_bit(DPC_RESET_HA, &ha->dpc_flags))
		/* करोn't reset CAM block on reset */
		qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xfeffffff);
	अन्यथा
		qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xffffffff);

	qla4_82xx_rom_unlock(ha);

	/* Read the signature value from the flash.
	 * Offset 0: Contain signature (0xcafecafe)
	 * Offset 4: Offset and number of addr/value pairs
	 * that present in CRB initialize sequence
	 */
	अगर (qla4_82xx_rom_fast_पढ़ो(ha, 0, &n) != 0 || n != 0xcafecafeUL ||
	    qla4_82xx_rom_fast_पढ़ो(ha, 4, &n) != 0) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			"[ERROR] Reading crb_init area: n: %08x\n", n);
		वापस -1;
	पूर्ण

	/* Offset in flash = lower 16 bits
	 * Number of enteries = upper 16 bits
	 */
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	/* number of addr/value pair should not exceed 1024 enteries */
	अगर (n  >= 1024) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "%s: %s:n=0x%x [ERROR] Card flash not initialized.\n",
		    DRIVER_NAME, __func__, n);
		वापस -1;
	पूर्ण

	ql4_prपूर्णांकk(KERN_INFO, ha,
		"%s: %d CRB init values found in ROM.\n", DRIVER_NAME, n);

	buf = kदो_स्मृति_array(n, माप(काष्ठा crb_addr_pair), GFP_KERNEL);
	अगर (buf == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "%s: [ERROR] Unable to malloc memory.\n", DRIVER_NAME);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		अगर (qla4_82xx_rom_fast_पढ़ो(ha, 8*i + 4*offset, &val) != 0 ||
		    qla4_82xx_rom_fast_पढ़ो(ha, 8*i + 4*offset + 4, &addr) !=
		    0) अणु
			kमुक्त(buf);
			वापस -1;
		पूर्ण

		buf[i].addr = addr;
		buf[i].data = val;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		/* Translate पूर्णांकernal CRB initialization
		 * address to PCI bus address
		 */
		off = qla4_82xx_decode_crb_addr((अचिन्हित दीर्घ)buf[i].addr) +
		    QLA82XX_PCI_CRBSPACE;
		/* Not all CRB  addr/value pair to be written,
		 * some of them are skipped
		 */

		/* skip अगर LS bit is set*/
		अगर (off & 0x1) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
			    "Skip CRB init replay for offset = 0x%lx\n", off));
			जारी;
		पूर्ण

		/* skipping cold reboot MAGIC */
		अगर (off == QLA82XX_CAM_RAM(0x1fc))
			जारी;

		/* करो not reset PCI */
		अगर (off == (ROMUSB_GLB + 0xbc))
			जारी;

		/* skip core घड़ी, so that firmware can increase the घड़ी */
		अगर (off == (ROMUSB_GLB + 0xc8))
			जारी;

		/* skip the function enable रेजिस्टर */
		अगर (off == QLA82XX_PCIE_REG(PCIE_SETUP_FUNCTION))
			जारी;

		अगर (off == QLA82XX_PCIE_REG(PCIE_SETUP_FUNCTION2))
			जारी;

		अगर ((off & 0x0ff00000) == QLA82XX_CRB_SMB)
			जारी;

		अगर ((off & 0x0ff00000) == QLA82XX_CRB_DDR_NET)
			जारी;

		अगर (off == ADDR_ERROR) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
			    "%s: [ERROR] Unknown addr: 0x%08lx\n",
			    DRIVER_NAME, buf[i].addr);
			जारी;
		पूर्ण

		qla4_82xx_wr_32(ha, off, buf[i].data);

		/* ISP requires much bigger delay to settle करोwn,
		 * अन्यथा crb_winकरोw वापसs 0xffffffff
		 */
		अगर (off == QLA82XX_ROMUSB_GLB_SW_RESET)
			msleep(1000);

		/* ISP requires millisec delay between
		 * successive CRB रेजिस्टर updation
		 */
		msleep(1);
	पूर्ण

	kमुक्त(buf);

	/* Resetting the data and inकाष्ठाion cache */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0xec, 0x1e);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0x4c, 8);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_I+0x4c, 8);

	/* Clear all protocol processing engines */
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0x8, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0xc, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0x8, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0xc, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0x8, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0xc, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0x8, 0);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0xc, 0);

	वापस 0;
पूर्ण

/**
 * qla4_8xxx_ms_mem_ग_लिखो_128b - Writes data to MS/off-chip memory
 * @ha: Poपूर्णांकer to adapter काष्ठाure
 * @addr: Flash address to ग_लिखो to
 * @data: Data to be written
 * @count: word_count to be written
 *
 * Return: On success वापस QLA_SUCCESS
 *         On error वापस QLA_ERROR
 **/
पूर्णांक qla4_8xxx_ms_mem_ग_लिखो_128b(काष्ठा scsi_qla_host *ha, uपूर्णांक64_t addr,
				uपूर्णांक32_t *data, uपूर्णांक32_t count)
अणु
	पूर्णांक i, j;
	uपूर्णांक32_t agt_ctrl;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret_val = QLA_SUCCESS;

	/* Only 128-bit aligned access */
	अगर (addr & 0xF) अणु
		ret_val = QLA_ERROR;
		जाओ निकास_ms_mem_ग_लिखो;
	पूर्ण

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/* Write address */
	ret_val = ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_ADDR_HI, 0);
	अगर (ret_val == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: write to AGT_ADDR_HI failed\n",
			   __func__);
		जाओ निकास_ms_mem_ग_लिखो_unlock;
	पूर्ण

	क्रम (i = 0; i < count; i++, addr += 16) अणु
		अगर (!((QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_QDR_NET,
					     QLA8XXX_ADDR_QDR_NET_MAX)) ||
		      (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
					     QLA8XXX_ADDR_DDR_NET_MAX)))) अणु
			ret_val = QLA_ERROR;
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		ret_val = ha->isp_ops->wr_reg_indirect(ha,
						       MD_MIU_TEST_AGT_ADDR_LO,
						       addr);
		/* Write data */
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_LO,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_HI,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_ULO,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_UHI,
						*data++);
		अगर (ret_val == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: write to AGT_WRDATA failed\n",
				   __func__);
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		/* Check ग_लिखो status */
		ret_val = ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_CTRL,
						       MIU_TA_CTL_WRITE_ENABLE);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
							MD_MIU_TEST_AGT_CTRL,
							MIU_TA_CTL_WRITE_START);
		अगर (ret_val == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: write to AGT_CTRL failed\n",
				   __func__);
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			ret_val = ha->isp_ops->rd_reg_indirect(ha,
							MD_MIU_TEST_AGT_CTRL,
							&agt_ctrl);
			अगर (ret_val == QLA_ERROR) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed to read MD_MIU_TEST_AGT_CTRL\n",
					   __func__);
				जाओ निकास_ms_mem_ग_लिखो_unlock;
			पूर्ण
			अगर ((agt_ctrl & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		/* Status check failed */
		अगर (j >= MAX_CTL_CHECK) अणु
			prपूर्णांकk_ratelimited(KERN_ERR "%s: MS memory write failed!\n",
					   __func__);
			ret_val = QLA_ERROR;
			जाओ निकास_ms_mem_ग_लिखो_unlock;
		पूर्ण
	पूर्ण

निकास_ms_mem_ग_लिखो_unlock:
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);

निकास_ms_mem_ग_लिखो:
	वापस ret_val;
पूर्ण

अटल पूर्णांक
qla4_82xx_load_from_flash(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t image_start)
अणु
	पूर्णांक  i, rval = 0;
	दीर्घ size = 0;
	दीर्घ flashaddr, memaddr;
	u64 data;
	u32 high, low;

	flashaddr = memaddr = ha->hw.flt_region_bootload;
	size = (image_start - flashaddr) / 8;

	DEBUG2(prपूर्णांकk("scsi%ld: %s: bootldr=0x%lx, fw_image=0x%x\n",
	    ha->host_no, __func__, flashaddr, image_start));

	क्रम (i = 0; i < size; i++) अणु
		अगर ((qla4_82xx_rom_fast_पढ़ो(ha, flashaddr, (पूर्णांक *)&low)) ||
		    (qla4_82xx_rom_fast_पढ़ो(ha, flashaddr + 4,
		    (पूर्णांक *)&high))) अणु
			rval = -1;
			जाओ निकास_load_from_flash;
		पूर्ण
		data = ((u64)high << 32) | low ;
		rval = qla4_82xx_pci_mem_ग_लिखो_2M(ha, memaddr, &data, 8);
		अगर (rval)
			जाओ निकास_load_from_flash;

		flashaddr += 8;
		memaddr   += 8;

		अगर (i % 0x1000 == 0)
			msleep(1);

	पूर्ण

	udelay(100);

	पढ़ो_lock(&ha->hw_lock);
	qla4_82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x18, 0x1020);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0x80001e);
	पढ़ो_unlock(&ha->hw_lock);

निकास_load_from_flash:
	वापस rval;
पूर्ण

अटल पूर्णांक qla4_82xx_load_fw(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t image_start)
अणु
	u32 rst;

	qla4_82xx_wr_32(ha, CRB_CMDPEG_STATE, 0);
	अगर (qla4_82xx_pinit_from_rom(ha, 0) != QLA_SUCCESS) अणु
		prपूर्णांकk(KERN_WARNING "%s: Error during CRB Initialization\n",
		    __func__);
		वापस QLA_ERROR;
	पूर्ण

	udelay(500);

	/* at this poपूर्णांक, QM is in reset. This could be a problem अगर there are
	 * incoming d* transition queue messages. QM/PCIE could wedge.
	 * To get around this, QM is brought out of reset.
	 */

	rst = qla4_82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET);
	/* unreset qm */
	rst &= ~(1 << 28);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, rst);

	अगर (qla4_82xx_load_from_flash(ha, image_start)) अणु
		prपूर्णांकk("%s: Error trying to load fw from flash!\n", __func__);
		वापस QLA_ERROR;
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla4_82xx_pci_mem_पढ़ो_2M(काष्ठा scsi_qla_host *ha,
		u64 off, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक i, j = 0, k, start, end, loop, sz[2], off0[2];
	पूर्णांक shअगरt_amount;
	uपूर्णांक32_t temp;
	uपूर्णांक64_t off8, val, mem_crb, word[2] = अणु0, 0पूर्ण;

	/*
	 * If not MN, go check क्रम MS or invalid.
	 */

	अगर (off >= QLA8XXX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	अन्यथा अणु
		mem_crb = QLA82XX_CRB_DDR_NET;
		अगर (qla4_82xx_pci_mem_bound_check(ha, off, size) == 0)
			वापस qla4_82xx_pci_mem_पढ़ो_direct(ha,
					off, data, size);
	पूर्ण


	off8 = off & 0xfffffff0;
	off0[0] = off & 0xf;
	sz[0] = (size < (16 - off0[0])) ? size : (16 - off0[0]);
	shअगरt_amount = 4;

	loop = ((off0[0] + size - 1) >> shअगरt_amount) + 1;
	off0[1] = 0;
	sz[1] = size - sz[0];

	क्रम (i = 0; i < loop; i++) अणु
		temp = off8 + (i << shअगरt_amount);
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_HI, temp);
		temp = MIU_TA_CTL_ENABLE;
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_START_ENABLE;
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			temp = qla4_82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			अगर ((temp & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			prपूर्णांकk_ratelimited(KERN_ERR
					   "%s: failed to read through agent\n",
					   __func__);
			अवरोध;
		पूर्ण

		start = off0[i] >> 2;
		end   = (off0[i] + sz[i] - 1) >> 2;
		क्रम (k = start; k <= end; k++) अणु
			temp = qla4_82xx_rd_32(ha,
				mem_crb + MIU_TEST_AGT_RDDATA(k));
			word[i] |= ((uपूर्णांक64_t)temp << (32 * (k & 1)));
		पूर्ण
	पूर्ण

	अगर (j >= MAX_CTL_CHECK)
		वापस -1;

	अगर ((off0[0] & 7) == 0) अणु
		val = word[0];
	पूर्ण अन्यथा अणु
		val = ((word[0] >> (off0[0] * 8)) & (~(~0ULL << (sz[0] * 8)))) |
		((word[1] & (~(~0ULL << (sz[1] * 8)))) << (sz[0] * 8));
	पूर्ण

	चयन (size) अणु
	हाल 1:
		*(uपूर्णांक8_t  *)data = val;
		अवरोध;
	हाल 2:
		*(uपूर्णांक16_t *)data = val;
		अवरोध;
	हाल 4:
		*(uपूर्णांक32_t *)data = val;
		अवरोध;
	हाल 8:
		*(uपूर्णांक64_t *)data = val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
qla4_82xx_pci_mem_ग_लिखो_2M(काष्ठा scsi_qla_host *ha,
		u64 off, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक i, j, ret = 0, loop, sz[2], off0;
	पूर्णांक scale, shअगरt_amount, startword;
	uपूर्णांक32_t temp;
	uपूर्णांक64_t off8, mem_crb, पंचांगpw, word[2] = अणु0, 0पूर्ण;

	/*
	 * If not MN, go check क्रम MS or invalid.
	 */
	अगर (off >= QLA8XXX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	अन्यथा अणु
		mem_crb = QLA82XX_CRB_DDR_NET;
		अगर (qla4_82xx_pci_mem_bound_check(ha, off, size) == 0)
			वापस qla4_82xx_pci_mem_ग_लिखो_direct(ha,
					off, data, size);
	पूर्ण

	off0 = off & 0x7;
	sz[0] = (size < (8 - off0)) ? size : (8 - off0);
	sz[1] = size - sz[0];

	off8 = off & 0xfffffff0;
	loop = (((off & 0xf) + size - 1) >> 4) + 1;
	shअगरt_amount = 4;
	scale = 2;
	startword = (off & 0xf)/8;

	क्रम (i = 0; i < loop; i++) अणु
		अगर (qla4_82xx_pci_mem_पढ़ो_2M(ha, off8 +
		    (i << shअगरt_amount), &word[i * scale], 8))
			वापस -1;
	पूर्ण

	चयन (size) अणु
	हाल 1:
		पंचांगpw = *((uपूर्णांक8_t *)data);
		अवरोध;
	हाल 2:
		पंचांगpw = *((uपूर्णांक16_t *)data);
		अवरोध;
	हाल 4:
		पंचांगpw = *((uपूर्णांक32_t *)data);
		अवरोध;
	हाल 8:
	शेष:
		पंचांगpw = *((uपूर्णांक64_t *)data);
		अवरोध;
	पूर्ण

	अगर (sz[0] == 8)
		word[startword] = पंचांगpw;
	अन्यथा अणु
		word[startword] &=
		    ~((~(~0ULL << (sz[0] * 8))) << (off0 * 8));
		word[startword] |= पंचांगpw << (off0 * 8);
	पूर्ण

	अगर (sz[1] != 0) अणु
		word[startword+1] &= ~(~0ULL << (sz[1] * 8));
		word[startword+1] |= पंचांगpw >> (sz[0] * 8);
	पूर्ण

	क्रम (i = 0; i < loop; i++) अणु
		temp = off8 + (i << shअगरt_amount);
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_HI, temp);
		temp = word[i * scale] & 0xffffffff;
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_LO, temp);
		temp = (word[i * scale] >> 32) & 0xffffffff;
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_HI, temp);
		temp = word[i*scale + 1] & 0xffffffff;
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_WRDATA_UPPER_LO,
		    temp);
		temp = (word[i*scale + 1] >> 32) & 0xffffffff;
		qla4_82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_WRDATA_UPPER_HI,
		    temp);

		temp = MIU_TA_CTL_WRITE_ENABLE;
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_WRITE_START;
		qla4_82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_CTRL, temp);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			temp = qla4_82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			अगर ((temp & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			अगर (prपूर्णांकk_ratelimit())
				ql4_prपूर्णांकk(KERN_ERR, ha,
					   "%s: failed to read through agent\n",
					   __func__);
			ret = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qla4_82xx_cmdpeg_पढ़ोy(काष्ठा scsi_qla_host *ha, पूर्णांक pegtune_val)
अणु
	u32 val = 0;
	पूर्णांक retries = 60;

	अगर (!pegtune_val) अणु
		करो अणु
			val = qla4_82xx_rd_32(ha, CRB_CMDPEG_STATE);
			अगर ((val == PHAN_INITIALIZE_COMPLETE) ||
			    (val == PHAN_INITIALIZE_ACK))
				वापस 0;
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(500);

		पूर्ण जबतक (--retries);

		अगर (!retries) अणु
			pegtune_val = qla4_82xx_rd_32(ha,
				QLA82XX_ROMUSB_GLB_PEGTUNE_DONE);
			prपूर्णांकk(KERN_WARNING "%s: init failed, "
				"pegtune_val = %x\n", __func__, pegtune_val);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qla4_82xx_rcvpeg_पढ़ोy(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t state = 0;
	पूर्णांक loops = 0;

	/* Winकरोw 1 call */
	पढ़ो_lock(&ha->hw_lock);
	state = qla4_82xx_rd_32(ha, CRB_RCVPEG_STATE);
	पढ़ो_unlock(&ha->hw_lock);

	जबतक ((state != PHAN_PEG_RCV_INITIALIZED) && (loops < 30000)) अणु
		udelay(100);
		/* Winकरोw 1 call */
		पढ़ो_lock(&ha->hw_lock);
		state = qla4_82xx_rd_32(ha, CRB_RCVPEG_STATE);
		पढ़ो_unlock(&ha->hw_lock);

		loops++;
	पूर्ण

	अगर (loops >= 30000) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "Receive Peg initialization not complete: 0x%x.\n", state));
		वापस QLA_ERROR;
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

व्योम
qla4_8xxx_set_drv_active(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		drv_active |= (1 << ha->func_num);
	अन्यथा
		drv_active |= (1 << (ha->func_num * 4));

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s(%ld): drv_active: 0x%08x\n",
		   __func__, ha->host_no, drv_active);
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_ACTIVE, drv_active);
पूर्ण

व्योम
qla4_8xxx_clear_drv_active(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		drv_active &= ~(1 << (ha->func_num));
	अन्यथा
		drv_active &= ~(1 << (ha->func_num * 4));

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s(%ld): drv_active: 0x%08x\n",
		   __func__, ha->host_no, drv_active);
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_ACTIVE, drv_active);
पूर्ण

अंतरभूत पूर्णांक qla4_8xxx_need_reset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_state, drv_active;
	पूर्णांक rval;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
	drv_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		rval = drv_state & (1 << ha->func_num);
	अन्यथा
		rval = drv_state & (1 << (ha->func_num * 4));

	अगर ((test_bit(AF_EEH_BUSY, &ha->flags)) && drv_active)
		rval = 1;

	वापस rval;
पूर्ण

व्योम qla4_8xxx_set_rst_पढ़ोy(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_state;

	drv_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		drv_state |= (1 << ha->func_num);
	अन्यथा
		drv_state |= (1 << (ha->func_num * 4));

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s(%ld): drv_state: 0x%08x\n",
		   __func__, ha->host_no, drv_state);
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_STATE, drv_state);
पूर्ण

व्योम qla4_8xxx_clear_rst_पढ़ोy(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_state;

	drv_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		drv_state &= ~(1 << ha->func_num);
	अन्यथा
		drv_state &= ~(1 << (ha->func_num * 4));

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s(%ld): drv_state: 0x%08x\n",
		   __func__, ha->host_no, drv_state);
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_STATE, drv_state);
पूर्ण

अटल अंतरभूत व्योम
qla4_8xxx_set_qsnt_पढ़ोy(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t qsnt_state;

	qsnt_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);

	/*
	 * For ISP8324 and ISP8042, drv_active रेजिस्टर has 1 bit per function,
	 * shअगरt 1 by func_num to set a bit क्रम the function.
	 * For ISP8022, drv_active has 4 bits per function.
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha))
		qsnt_state |= (1 << ha->func_num);
	अन्यथा
		qsnt_state |= (2 << (ha->func_num * 4));

	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_STATE, qsnt_state);
पूर्ण


अटल पूर्णांक
qla4_82xx_start_firmware(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t image_start)
अणु
	uपूर्णांक16_t lnk;

	/* scrub dma mask expansion रेजिस्टर */
	qla4_82xx_wr_32(ha, CRB_DMA_SHIFT, 0x55555555);

	/* Overग_लिखो stale initialization रेजिस्टर values */
	qla4_82xx_wr_32(ha, CRB_CMDPEG_STATE, 0);
	qla4_82xx_wr_32(ha, CRB_RCVPEG_STATE, 0);
	qla4_82xx_wr_32(ha, QLA82XX_PEG_HALT_STATUS1, 0);
	qla4_82xx_wr_32(ha, QLA82XX_PEG_HALT_STATUS2, 0);

	अगर (qla4_82xx_load_fw(ha, image_start) != QLA_SUCCESS) अणु
		prपूर्णांकk("%s: Error trying to start fw!\n", __func__);
		वापस QLA_ERROR;
	पूर्ण

	/* Handshake with the card beक्रमe we रेजिस्टर the devices. */
	अगर (qla4_82xx_cmdpeg_पढ़ोy(ha, 0) != QLA_SUCCESS) अणु
		prपूर्णांकk("%s: Error during card handshake!\n", __func__);
		वापस QLA_ERROR;
	पूर्ण

	/* Negotiated Link width */
	pcie_capability_पढ़ो_word(ha->pdev, PCI_EXP_LNKSTA, &lnk);
	ha->link_width = (lnk >> 4) & 0x3f;

	/* Synchronize with Receive peg */
	वापस qla4_82xx_rcvpeg_पढ़ोy(ha);
पूर्ण

पूर्णांक qla4_82xx_try_start_fw(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval;

	/*
	 * FW Load priority:
	 * 1) Operational firmware residing in flash.
	 * 2) Fail
	 */

	ql4_prपूर्णांकk(KERN_INFO, ha,
	    "FW: Retrieving flash offsets from FLT/FDT ...\n");
	rval = qla4_8xxx_get_flash_info(ha);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	ql4_prपूर्णांकk(KERN_INFO, ha,
	    "FW: Attempting to load firmware from flash...\n");
	rval = qla4_82xx_start_firmware(ha, ha->hw.flt_region_fw);

	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "FW: Load firmware from flash"
		    " FAILED...\n");
		वापस rval;
	पूर्ण

	वापस rval;
पूर्ण

व्योम qla4_82xx_rom_lock_recovery(काष्ठा scsi_qla_host *ha)
अणु
	अगर (qla4_82xx_rom_lock(ha)) अणु
		/* Someone अन्यथा is holding the lock. */
		dev_info(&ha->pdev->dev, "Resetting rom_lock\n");
	पूर्ण

	/*
	 * Either we got the lock, or someone
	 * अन्यथा died जबतक holding it.
	 * In either हाल, unlock.
	 */
	qla4_82xx_rom_unlock(ha);
पूर्ण

अटल uपूर्णांक32_t ql4_84xx_poll_रुको_क्रम_पढ़ोy(काष्ठा scsi_qla_host *ha,
					     uपूर्णांक32_t addr1, uपूर्णांक32_t mask)
अणु
	अचिन्हित दीर्घ समयout;
	uपूर्णांक32_t rval = QLA_SUCCESS;
	uपूर्णांक32_t temp;

	समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT_100_MS);
	करो अणु
		ha->isp_ops->rd_reg_indirect(ha, addr1, &temp);
		अगर ((temp & mask) != 0)
			अवरोध;

		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "Error in processing rdmdio entry\n");
			वापस QLA_ERROR;
		पूर्ण
	पूर्ण जबतक (1);

	वापस rval;
पूर्ण

अटल uपूर्णांक32_t ql4_84xx_ipmdio_rd_reg(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr1,
				uपूर्णांक32_t addr3, uपूर्णांक32_t mask, uपूर्णांक32_t addr,
				uपूर्णांक32_t *data_ptr)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t temp;
	uपूर्णांक32_t data;

	rval = ql4_84xx_poll_रुको_क्रम_पढ़ोy(ha, addr1, mask);
	अगर (rval)
		जाओ निकास_ipmdio_rd_reg;

	temp = (0x40000000 | addr);
	ha->isp_ops->wr_reg_indirect(ha, addr1, temp);

	rval = ql4_84xx_poll_रुको_क्रम_पढ़ोy(ha, addr1, mask);
	अगर (rval)
		जाओ निकास_ipmdio_rd_reg;

	ha->isp_ops->rd_reg_indirect(ha, addr3, &data);
	*data_ptr = data;

निकास_ipmdio_rd_reg:
	वापस rval;
पूर्ण


अटल uपूर्णांक32_t ql4_84xx_poll_रुको_ipmdio_bus_idle(काष्ठा scsi_qla_host *ha,
						    uपूर्णांक32_t addr1,
						    uपूर्णांक32_t addr2,
						    uपूर्णांक32_t addr3,
						    uपूर्णांक32_t mask)
अणु
	अचिन्हित दीर्घ समयout;
	uपूर्णांक32_t temp;
	uपूर्णांक32_t rval = QLA_SUCCESS;

	समयout = jअगरfies + msecs_to_jअगरfies(TIMEOUT_100_MS);
	करो अणु
		ql4_84xx_ipmdio_rd_reg(ha, addr1, addr3, mask, addr2, &temp);
		अगर ((temp & 0x1) != 1)
			अवरोध;
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "Error in processing mdiobus idle\n");
			वापस QLA_ERROR;
		पूर्ण
	पूर्ण जबतक (1);

	वापस rval;
पूर्ण

अटल पूर्णांक ql4_84xx_ipmdio_wr_reg(काष्ठा scsi_qla_host *ha,
				  uपूर्णांक32_t addr1, uपूर्णांक32_t addr3,
				  uपूर्णांक32_t mask, uपूर्णांक32_t addr,
				  uपूर्णांक32_t value)
अणु
	पूर्णांक rval = QLA_SUCCESS;

	rval = ql4_84xx_poll_रुको_क्रम_पढ़ोy(ha, addr1, mask);
	अगर (rval)
		जाओ निकास_ipmdio_wr_reg;

	ha->isp_ops->wr_reg_indirect(ha, addr3, value);
	ha->isp_ops->wr_reg_indirect(ha, addr1, addr);

	rval = ql4_84xx_poll_रुको_क्रम_पढ़ोy(ha, addr1, mask);
	अगर (rval)
		जाओ निकास_ipmdio_wr_reg;

निकास_ipmdio_wr_reg:
	वापस rval;
पूर्ण

अटल व्योम qla4_8xxx_minidump_process_rdcrb(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla8xxx_minidump_entry_crb *crb_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	crb_hdr = (काष्ठा qla8xxx_minidump_entry_crb *)entry_hdr;
	r_addr = crb_hdr->addr;
	r_stride = crb_hdr->crb_strd.addr_stride;
	loop_cnt = crb_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		ha->isp_ops->rd_reg_indirect(ha, r_addr, &r_value);
		*data_ptr++ = cpu_to_le32(r_addr);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल पूर्णांक qla4_83xx_check_dma_engine_state(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uपूर्णांक64_t dma_base_addr = 0;
	काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *पंचांगplt_hdr = शून्य;

	पंचांगplt_hdr = (काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *)
							ha->fw_dump_पंचांगplt_hdr;
	dma_eng_num =
		पंचांगplt_hdr->saved_state_array[QLA83XX_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = QLA83XX_PEX_DMA_BASE_ADDRESS +
				(dma_eng_num * QLA83XX_PEX_DMA_NUM_OFFSET);

	/* Read the pex-dma's command-status-and-control रेजिस्टर. */
	rval = ha->isp_ops->rd_reg_indirect(ha,
			(dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL),
			&cmd_sts_and_cntrl);

	अगर (rval)
		वापस QLA_ERROR;

	/* Check अगर requested pex-dma engine is available. */
	अगर (cmd_sts_and_cntrl & BIT_31)
		वापस QLA_SUCCESS;
	अन्यथा
		वापस QLA_ERROR;
पूर्ण

अटल पूर्णांक qla4_83xx_start_pex_dma(काष्ठा scsi_qla_host *ha,
			   काष्ठा qla4_83xx_minidump_entry_rdmem_pex_dma *m_hdr)
अणु
	पूर्णांक rval = QLA_SUCCESS, रुको = 0;
	uपूर्णांक32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uपूर्णांक64_t dma_base_addr = 0;
	काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *पंचांगplt_hdr = शून्य;

	पंचांगplt_hdr = (काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *)
							ha->fw_dump_पंचांगplt_hdr;
	dma_eng_num =
		पंचांगplt_hdr->saved_state_array[QLA83XX_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = QLA83XX_PEX_DMA_BASE_ADDRESS +
				(dma_eng_num * QLA83XX_PEX_DMA_NUM_OFFSET);

	rval = ha->isp_ops->wr_reg_indirect(ha,
				dma_base_addr + QLA83XX_PEX_DMA_CMD_ADDR_LOW,
				m_hdr->desc_card_addr);
	अगर (rval)
		जाओ error_निकास;

	rval = ha->isp_ops->wr_reg_indirect(ha,
			      dma_base_addr + QLA83XX_PEX_DMA_CMD_ADDR_HIGH, 0);
	अगर (rval)
		जाओ error_निकास;

	rval = ha->isp_ops->wr_reg_indirect(ha,
			      dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL,
			      m_hdr->start_dma_cmd);
	अगर (rval)
		जाओ error_निकास;

	/* Wait क्रम dma operation to complete. */
	क्रम (रुको = 0; रुको < QLA83XX_PEX_DMA_MAX_WAIT; रुको++) अणु
		rval = ha->isp_ops->rd_reg_indirect(ha,
			    (dma_base_addr + QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL),
			    &cmd_sts_and_cntrl);
		अगर (rval)
			जाओ error_निकास;

		अगर ((cmd_sts_and_cntrl & BIT_1) == 0)
			अवरोध;
		अन्यथा
			udelay(10);
	पूर्ण

	/* Wait a max of 100 ms, otherwise fallback to rdmem entry पढ़ो */
	अगर (रुको >= QLA83XX_PEX_DMA_MAX_WAIT) अणु
		rval = QLA_ERROR;
		जाओ error_निकास;
	पूर्ण

error_निकास:
	वापस rval;
पूर्ण

अटल पूर्णांक qla4_8xxx_minidump_pex_dma_पढ़ो(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla4_83xx_minidump_entry_rdmem_pex_dma *m_hdr = शून्य;
	uपूर्णांक32_t size, पढ़ो_size;
	uपूर्णांक8_t *data_ptr = (uपूर्णांक8_t *)*d_ptr;
	व्योम *rdmem_buffer = शून्य;
	dma_addr_t rdmem_dma;
	काष्ठा qla4_83xx_pex_dma_descriptor dma_desc;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));

	rval = qla4_83xx_check_dma_engine_state(ha);
	अगर (rval != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: DMA engine not available. Fallback to rdmem-read.\n",
				  __func__));
		वापस QLA_ERROR;
	पूर्ण

	m_hdr = (काष्ठा qla4_83xx_minidump_entry_rdmem_pex_dma *)entry_hdr;
	rdmem_buffer = dma_alloc_coherent(&ha->pdev->dev,
					  QLA83XX_PEX_DMA_READ_SIZE,
					  &rdmem_dma, GFP_KERNEL);
	अगर (!rdmem_buffer) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Unable to allocate rdmem dma buffer\n",
				  __func__));
		वापस QLA_ERROR;
	पूर्ण

	/* Prepare pex-dma descriptor to be written to MS memory. */
	/* dma-desc-cmd layout:
	 *              0-3: dma-desc-cmd 0-3
	 *              4-7: pcid function number
	 *              8-15: dma-desc-cmd 8-15
	 */
	dma_desc.cmd.dma_desc_cmd = (m_hdr->dma_desc_cmd & 0xff0f);
	dma_desc.cmd.dma_desc_cmd |= ((PCI_FUNC(ha->pdev->devfn) & 0xf) << 0x4);
	dma_desc.dma_bus_addr = rdmem_dma;

	size = 0;
	पढ़ो_size = 0;
	/*
	 * Perक्रमm rdmem operation using pex-dma.
	 * Prepare dma in chunks of QLA83XX_PEX_DMA_READ_SIZE.
	 */
	जबतक (पढ़ो_size < m_hdr->पढ़ो_data_size) अणु
		अगर (m_hdr->पढ़ो_data_size - पढ़ो_size >=
		    QLA83XX_PEX_DMA_READ_SIZE)
			size = QLA83XX_PEX_DMA_READ_SIZE;
		अन्यथा अणु
			size = (m_hdr->पढ़ो_data_size - पढ़ो_size);

			अगर (rdmem_buffer)
				dma_मुक्त_coherent(&ha->pdev->dev,
						  QLA83XX_PEX_DMA_READ_SIZE,
						  rdmem_buffer, rdmem_dma);

			rdmem_buffer = dma_alloc_coherent(&ha->pdev->dev, size,
							  &rdmem_dma,
							  GFP_KERNEL);
			अगर (!rdmem_buffer) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "%s: Unable to allocate rdmem dma buffer\n",
						  __func__));
				वापस QLA_ERROR;
			पूर्ण
			dma_desc.dma_bus_addr = rdmem_dma;
		पूर्ण

		dma_desc.src_addr = m_hdr->पढ़ो_addr + पढ़ो_size;
		dma_desc.cmd.पढ़ो_data_size = size;

		/* Prepare: Write pex-dma descriptor to MS memory. */
		rval = qla4_8xxx_ms_mem_ग_लिखो_128b(ha,
			      (uपूर्णांक64_t)m_hdr->desc_card_addr,
			      (uपूर्णांक32_t *)&dma_desc,
			      (माप(काष्ठा qla4_83xx_pex_dma_descriptor)/16));
		अगर (rval != QLA_SUCCESS) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s: Error writing rdmem-dma-init to MS !!!\n",
				   __func__);
			जाओ error_निकास;
		पूर्ण

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Dma-desc: Instruct for rdmem dma (size 0x%x).\n",
				  __func__, size));
		/* Execute: Start pex-dma operation. */
		rval = qla4_83xx_start_pex_dma(ha, m_hdr);
		अगर (rval != QLA_SUCCESS) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi(%ld): start-pex-dma failed rval=0x%x\n",
					  ha->host_no, rval));
			जाओ error_निकास;
		पूर्ण

		स_नकल(data_ptr, rdmem_buffer, size);
		data_ptr += size;
		पढ़ो_size += size;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Leaving fn: %s\n", __func__));

	*d_ptr = (uपूर्णांक32_t *)data_ptr;

error_निकास:
	अगर (rdmem_buffer)
		dma_मुक्त_coherent(&ha->pdev->dev, size, rdmem_buffer,
				  rdmem_dma);

	वापस rval;
पूर्ण

अटल पूर्णांक qla4_8xxx_minidump_process_l2tag(काष्ठा scsi_qla_host *ha,
				 काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				 uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	अचिन्हित दीर्घ p_रुको, w_समय, p_mask;
	uपूर्णांक32_t c_value_w, c_value_r;
	काष्ठा qla8xxx_minidump_entry_cache *cache_hdr;
	पूर्णांक rval = QLA_ERROR;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	cache_hdr = (काष्ठा qla8xxx_minidump_entry_cache *)entry_hdr;

	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->पढ़ो_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.ग_लिखो_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->पढ़ो_ctrl.पढ़ो_addr_cnt;
	p_रुको = cache_hdr->cache_ctrl.poll_रुको;
	p_mask = cache_hdr->cache_ctrl.poll_mask;

	क्रम (i = 0; i < loop_count; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, t_r_addr, t_value);

		अगर (c_value_w)
			ha->isp_ops->wr_reg_indirect(ha, c_addr, c_value_w);

		अगर (p_mask) अणु
			w_समय = jअगरfies + p_रुको;
			करो अणु
				ha->isp_ops->rd_reg_indirect(ha, c_addr,
							     &c_value_r);
				अगर ((c_value_r & p_mask) == 0) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, w_समय)) अणु
					/* capturing dump failed */
					वापस rval;
				पूर्ण
			पूर्ण जबतक (1);
		पूर्ण

		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			ha->isp_ops->rd_reg_indirect(ha, addr, &r_value);
			*data_ptr++ = cpu_to_le32(r_value);
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण

		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक qla4_8xxx_minidump_process_control(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr)
अणु
	काष्ठा qla8xxx_minidump_entry_crb *crb_entry;
	uपूर्णांक32_t पढ़ो_value, opcode, poll_समय, addr, index, rval = QLA_SUCCESS;
	uपूर्णांक32_t crb_addr;
	अचिन्हित दीर्घ wसमय;
	काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *पंचांगplt_hdr;
	पूर्णांक i;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	पंचांगplt_hdr = (काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *)
						ha->fw_dump_पंचांगplt_hdr;
	crb_entry = (काष्ठा qla8xxx_minidump_entry_crb *)entry_hdr;

	crb_addr = crb_entry->addr;
	क्रम (i = 0; i < crb_entry->op_count; i++) अणु
		opcode = crb_entry->crb_ctrl.opcode;
		अगर (opcode & QLA8XXX_DBG_OPCODE_WR) अणु
			ha->isp_ops->wr_reg_indirect(ha, crb_addr,
						     crb_entry->value_1);
			opcode &= ~QLA8XXX_DBG_OPCODE_WR;
		पूर्ण
		अगर (opcode & QLA8XXX_DBG_OPCODE_RW) अणु
			ha->isp_ops->rd_reg_indirect(ha, crb_addr, &पढ़ो_value);
			ha->isp_ops->wr_reg_indirect(ha, crb_addr, पढ़ो_value);
			opcode &= ~QLA8XXX_DBG_OPCODE_RW;
		पूर्ण
		अगर (opcode & QLA8XXX_DBG_OPCODE_AND) अणु
			ha->isp_ops->rd_reg_indirect(ha, crb_addr, &पढ़ो_value);
			पढ़ो_value &= crb_entry->value_2;
			opcode &= ~QLA8XXX_DBG_OPCODE_AND;
			अगर (opcode & QLA8XXX_DBG_OPCODE_OR) अणु
				पढ़ो_value |= crb_entry->value_3;
				opcode &= ~QLA8XXX_DBG_OPCODE_OR;
			पूर्ण
			ha->isp_ops->wr_reg_indirect(ha, crb_addr, पढ़ो_value);
		पूर्ण
		अगर (opcode & QLA8XXX_DBG_OPCODE_OR) अणु
			ha->isp_ops->rd_reg_indirect(ha, crb_addr, &पढ़ो_value);
			पढ़ो_value |= crb_entry->value_3;
			ha->isp_ops->wr_reg_indirect(ha, crb_addr, पढ़ो_value);
			opcode &= ~QLA8XXX_DBG_OPCODE_OR;
		पूर्ण
		अगर (opcode & QLA8XXX_DBG_OPCODE_POLL) अणु
			poll_समय = crb_entry->crb_strd.poll_समयout;
			wसमय = jअगरfies + poll_समय;
			ha->isp_ops->rd_reg_indirect(ha, crb_addr, &पढ़ो_value);

			करो अणु
				अगर ((पढ़ो_value & crb_entry->value_2) ==
				    crb_entry->value_1) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, wसमय)) अणु
					/* capturing dump failed */
					rval = QLA_ERROR;
					अवरोध;
				पूर्ण अन्यथा अणु
					ha->isp_ops->rd_reg_indirect(ha,
							crb_addr, &पढ़ो_value);
				पूर्ण
			पूर्ण जबतक (1);
			opcode &= ~QLA8XXX_DBG_OPCODE_POLL;
		पूर्ण

		अगर (opcode & QLA8XXX_DBG_OPCODE_RDSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				addr = crb_addr;
			पूर्ण

			ha->isp_ops->rd_reg_indirect(ha, addr, &पढ़ो_value);
			index = crb_entry->crb_ctrl.state_index_v;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
			opcode &= ~QLA8XXX_DBG_OPCODE_RDSTATE;
		पूर्ण

		अगर (opcode & QLA8XXX_DBG_OPCODE_WRSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				addr = crb_addr;
			पूर्ण

			अगर (crb_entry->crb_ctrl.state_index_v) अणु
				index = crb_entry->crb_ctrl.state_index_v;
				पढ़ो_value =
					पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा अणु
				पढ़ो_value = crb_entry->value_1;
			पूर्ण

			ha->isp_ops->wr_reg_indirect(ha, addr, पढ़ो_value);
			opcode &= ~QLA8XXX_DBG_OPCODE_WRSTATE;
		पूर्ण

		अगर (opcode & QLA8XXX_DBG_OPCODE_MDSTATE) अणु
			index = crb_entry->crb_ctrl.state_index_v;
			पढ़ो_value = पंचांगplt_hdr->saved_state_array[index];
			पढ़ो_value <<= crb_entry->crb_ctrl.shl;
			पढ़ो_value >>= crb_entry->crb_ctrl.shr;
			अगर (crb_entry->value_2)
				पढ़ो_value &= crb_entry->value_2;
			पढ़ो_value |= crb_entry->value_3;
			पढ़ो_value += crb_entry->value_1;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
			opcode &= ~QLA8XXX_DBG_OPCODE_MDSTATE;
		पूर्ण
		crb_addr += crb_entry->crb_strd.addr_stride;
	पूर्ण
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Leaving fn: %s\n", __func__));
	वापस rval;
पूर्ण

अटल व्योम qla4_8xxx_minidump_process_rकरोcm(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla8xxx_minidump_entry_rकरोcm *ocm_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	ocm_hdr = (काष्ठा qla8xxx_minidump_entry_rकरोcm *)entry_hdr;
	r_addr = ocm_hdr->पढ़ो_addr;
	r_stride = ocm_hdr->पढ़ो_addr_stride;
	loop_cnt = ocm_hdr->op_count;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "[%s]: r_addr: 0x%x, r_stride: 0x%x, loop_cnt: 0x%x\n",
			  __func__, r_addr, r_stride, loop_cnt));

	क्रम (i = 0; i < loop_cnt; i++) अणु
		r_value = पढ़ोl((व्योम __iomem *)(r_addr + ha->nx_pcibase));
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	पूर्ण
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Leaving fn: %s datacount: 0x%lx\n",
		__func__, (दीर्घ अचिन्हित पूर्णांक) (loop_cnt * माप(uपूर्णांक32_t))));
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम qla4_8xxx_minidump_process_rdmux(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, s_stride, s_addr, s_value, loop_cnt, i, r_value;
	काष्ठा qla8xxx_minidump_entry_mux *mux_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	mux_hdr = (काष्ठा qla8xxx_minidump_entry_mux *)entry_hdr;
	r_addr = mux_hdr->पढ़ो_addr;
	s_addr = mux_hdr->select_addr;
	s_stride = mux_hdr->select_value_stride;
	s_value = mux_hdr->select_value;
	loop_cnt = mux_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, s_addr, s_value);
		ha->isp_ops->rd_reg_indirect(ha, r_addr, &r_value);
		*data_ptr++ = cpu_to_le32(s_value);
		*data_ptr++ = cpu_to_le32(r_value);
		s_value += s_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम qla4_8xxx_minidump_process_l1cache(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	uपूर्णांक32_t c_value_w;
	काष्ठा qla8xxx_minidump_entry_cache *cache_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	cache_hdr = (काष्ठा qla8xxx_minidump_entry_cache *)entry_hdr;
	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->पढ़ो_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.ग_लिखो_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->पढ़ो_ctrl.पढ़ो_addr_cnt;

	क्रम (i = 0; i < loop_count; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, t_r_addr, t_value);
		ha->isp_ops->wr_reg_indirect(ha, c_addr, c_value_w);
		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			ha->isp_ops->rd_reg_indirect(ha, addr, &r_value);
			*data_ptr++ = cpu_to_le32(r_value);
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम qla4_8xxx_minidump_process_queue(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t s_addr, r_addr;
	uपूर्णांक32_t r_stride, r_value, r_cnt, qid = 0;
	uपूर्णांक32_t i, k, loop_cnt;
	काष्ठा qla8xxx_minidump_entry_queue *q_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	q_hdr = (काष्ठा qla8xxx_minidump_entry_queue *)entry_hdr;
	s_addr = q_hdr->select_addr;
	r_cnt = q_hdr->rd_strd.पढ़ो_addr_cnt;
	r_stride = q_hdr->rd_strd.पढ़ो_addr_stride;
	loop_cnt = q_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, s_addr, qid);
		r_addr = q_hdr->पढ़ो_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			ha->isp_ops->rd_reg_indirect(ha, r_addr, &r_value);
			*data_ptr++ = cpu_to_le32(r_value);
			r_addr += r_stride;
		पूर्ण
		qid += q_hdr->q_strd.queue_id_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

#घोषणा MD_सूचीECT_ROM_WINDOW		0x42110030
#घोषणा MD_सूचीECT_ROM_READ_BASE		0x42150000

अटल व्योम qla4_82xx_minidump_process_rdrom(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_value;
	uपूर्णांक32_t i, loop_cnt;
	काष्ठा qla8xxx_minidump_entry_rdrom *rom_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	rom_hdr = (काष्ठा qla8xxx_minidump_entry_rdrom *)entry_hdr;
	r_addr = rom_hdr->पढ़ो_addr;
	loop_cnt = rom_hdr->पढ़ो_data_size/माप(uपूर्णांक32_t);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "[%s]: flash_addr: 0x%x, read_data_size: 0x%x\n",
			   __func__, r_addr, loop_cnt));

	क्रम (i = 0; i < loop_cnt; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, MD_सूचीECT_ROM_WINDOW,
					     (r_addr & 0xFFFF0000));
		ha->isp_ops->rd_reg_indirect(ha,
				MD_सूचीECT_ROM_READ_BASE + (r_addr & 0x0000FFFF),
				&r_value);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += माप(uपूर्णांक32_t);
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

#घोषणा MD_MIU_TEST_AGT_CTRL		0x41000090
#घोषणा MD_MIU_TEST_AGT_ADDR_LO		0x41000094
#घोषणा MD_MIU_TEST_AGT_ADDR_HI		0x41000098

अटल पूर्णांक __qla4_8xxx_minidump_process_rdmem(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, r_value, r_data;
	uपूर्णांक32_t i, j, loop_cnt;
	काष्ठा qla8xxx_minidump_entry_rdmem *m_hdr;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	m_hdr = (काष्ठा qla8xxx_minidump_entry_rdmem *)entry_hdr;
	r_addr = m_hdr->पढ़ो_addr;
	loop_cnt = m_hdr->पढ़ो_data_size/16;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "[%s]: Read addr: 0x%x, read_data_size: 0x%x\n",
			  __func__, r_addr, m_hdr->पढ़ो_data_size));

	अगर (r_addr & 0xf) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "[%s]: Read addr 0x%x not 16 bytes aligned\n",
				  __func__, r_addr));
		वापस QLA_ERROR;
	पूर्ण

	अगर (m_hdr->पढ़ो_data_size % 16) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "[%s]: Read data[0x%x] not multiple of 16 bytes\n",
				  __func__, m_hdr->पढ़ो_data_size));
		वापस QLA_ERROR;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "[%s]: rdmem_addr: 0x%x, read_data_size: 0x%x, loop_cnt: 0x%x\n",
			  __func__, r_addr, m_hdr->पढ़ो_data_size, loop_cnt));

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
	क्रम (i = 0; i < loop_cnt; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_ADDR_LO,
					     r_addr);
		r_value = 0;
		ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_ADDR_HI,
					     r_value);
		r_value = MIU_TA_CTL_ENABLE;
		ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_CTRL, r_value);
		r_value = MIU_TA_CTL_START_ENABLE;
		ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_CTRL, r_value);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			ha->isp_ops->rd_reg_indirect(ha, MD_MIU_TEST_AGT_CTRL,
						     &r_value);
			अगर ((r_value & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			prपूर्णांकk_ratelimited(KERN_ERR
					   "%s: failed to read through agent\n",
					    __func__);
			ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
			वापस QLA_SUCCESS;
		पूर्ण

		क्रम (j = 0; j < 4; j++) अणु
			ha->isp_ops->rd_reg_indirect(ha,
						     MD_MIU_TEST_AGT_RDDATA[j],
						     &r_data);
			*data_ptr++ = cpu_to_le32(r_data);
		पूर्ण

		r_addr += 16;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Leaving fn: %s datacount: 0x%x\n",
			  __func__, (loop_cnt * 16)));

	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक qla4_8xxx_minidump_process_rdmem(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t *data_ptr = *d_ptr;
	पूर्णांक rval = QLA_SUCCESS;

	rval = qla4_8xxx_minidump_pex_dma_पढ़ो(ha, entry_hdr, &data_ptr);
	अगर (rval != QLA_SUCCESS)
		rval = __qla4_8xxx_minidump_process_rdmem(ha, entry_hdr,
							  &data_ptr);
	*d_ptr = data_ptr;
	वापस rval;
पूर्ण

अटल व्योम qla4_8xxx_mark_entry_skipped(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				पूर्णांक index)
अणु
	entry_hdr->d_ctrl.driver_flags |= QLA8XXX_DBG_SKIPPED_FLAG;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "scsi(%ld): Skipping entry[%d]: ETYPE[0x%x]-ELEVEL[0x%x]\n",
			  ha->host_no, index, entry_hdr->entry_type,
			  entry_hdr->d_ctrl.entry_capture_mask));
	/* If driver encounters a new entry type that it cannot process,
	 * it should just skip the entry and adjust the total buffer size by
	 * from subtracting the skipped bytes from it
	 */
	ha->fw_dump_skip_size += entry_hdr->entry_capture_size;
पूर्ण

/* ISP83xx functions to process new minidump entries... */
अटल uपूर्णांक32_t qla83xx_minidump_process_pollrd(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t r_addr, s_addr, s_value, r_value, poll_रुको, poll_mask;
	uपूर्णांक16_t s_stride, i;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	uपूर्णांक32_t rval = QLA_SUCCESS;
	काष्ठा qla83xx_minidump_entry_pollrd *pollrd_hdr;

	pollrd_hdr = (काष्ठा qla83xx_minidump_entry_pollrd *)entry_hdr;
	s_addr = le32_to_cpu(pollrd_hdr->select_addr);
	r_addr = le32_to_cpu(pollrd_hdr->पढ़ो_addr);
	s_value = le32_to_cpu(pollrd_hdr->select_value);
	s_stride = le32_to_cpu(pollrd_hdr->select_value_stride);

	poll_रुको = le32_to_cpu(pollrd_hdr->poll_रुको);
	poll_mask = le32_to_cpu(pollrd_hdr->poll_mask);

	क्रम (i = 0; i < le32_to_cpu(pollrd_hdr->op_count); i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, s_addr, s_value);
		poll_रुको = le32_to_cpu(pollrd_hdr->poll_रुको);
		जबतक (1) अणु
			ha->isp_ops->rd_reg_indirect(ha, s_addr, &r_value);

			अगर ((r_value & poll_mask) != 0) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				msleep(1);
				अगर (--poll_रुको == 0) अणु
					ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT\n",
						   __func__);
					rval = QLA_ERROR;
					जाओ निकास_process_pollrd;
				पूर्ण
			पूर्ण
		पूर्ण
		ha->isp_ops->rd_reg_indirect(ha, r_addr, &r_value);
		*data_ptr++ = cpu_to_le32(s_value);
		*data_ptr++ = cpu_to_le32(r_value);
		s_value += s_stride;
	पूर्ण

	*d_ptr = data_ptr;

निकास_process_pollrd:
	वापस rval;
पूर्ण

अटल uपूर्णांक32_t qla4_84xx_minidump_process_rddfe(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	पूर्णांक loop_cnt;
	uपूर्णांक32_t addr1, addr2, value, data, temp, wrval;
	uपूर्णांक8_t stride, stride2;
	uपूर्णांक16_t count;
	uपूर्णांक32_t poll, mask, modअगरy_mask;
	uपूर्णांक32_t रुको_count = 0;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	काष्ठा qla8044_minidump_entry_rddfe *rddfe;
	uपूर्णांक32_t rval = QLA_SUCCESS;

	rddfe = (काष्ठा qla8044_minidump_entry_rddfe *)entry_hdr;
	addr1 = le32_to_cpu(rddfe->addr_1);
	value = le32_to_cpu(rddfe->value);
	stride = le32_to_cpu(rddfe->stride);
	stride2 = le32_to_cpu(rddfe->stride2);
	count = le32_to_cpu(rddfe->count);

	poll = le32_to_cpu(rddfe->poll);
	mask = le32_to_cpu(rddfe->mask);
	modअगरy_mask = le32_to_cpu(rddfe->modअगरy_mask);

	addr2 = addr1 + stride;

	क्रम (loop_cnt = 0x0; loop_cnt < count; loop_cnt++) अणु
		ha->isp_ops->wr_reg_indirect(ha, addr1, (0x40000000 | value));

		रुको_count = 0;
		जबतक (रुको_count < poll) अणु
			ha->isp_ops->rd_reg_indirect(ha, addr1, &temp);
			अगर ((temp & mask) != 0)
				अवरोध;
			रुको_count++;
		पूर्ण

		अगर (रुको_count == poll) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT\n", __func__);
			rval = QLA_ERROR;
			जाओ निकास_process_rddfe;
		पूर्ण अन्यथा अणु
			ha->isp_ops->rd_reg_indirect(ha, addr2, &temp);
			temp = temp & modअगरy_mask;
			temp = (temp | ((loop_cnt << 16) | loop_cnt));
			wrval = ((temp << 16) | temp);

			ha->isp_ops->wr_reg_indirect(ha, addr2, wrval);
			ha->isp_ops->wr_reg_indirect(ha, addr1, value);

			रुको_count = 0;
			जबतक (रुको_count < poll) अणु
				ha->isp_ops->rd_reg_indirect(ha, addr1, &temp);
				अगर ((temp & mask) != 0)
					अवरोध;
				रुको_count++;
			पूर्ण
			अगर (रुको_count == poll) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT\n",
					   __func__);
				rval = QLA_ERROR;
				जाओ निकास_process_rddfe;
			पूर्ण

			ha->isp_ops->wr_reg_indirect(ha, addr1,
						     ((0x40000000 | value) +
						     stride2));
			रुको_count = 0;
			जबतक (रुको_count < poll) अणु
				ha->isp_ops->rd_reg_indirect(ha, addr1, &temp);
				अगर ((temp & mask) != 0)
					अवरोध;
				रुको_count++;
			पूर्ण

			अगर (रुको_count == poll) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT\n",
					   __func__);
				rval = QLA_ERROR;
				जाओ निकास_process_rddfe;
			पूर्ण

			ha->isp_ops->rd_reg_indirect(ha, addr2, &data);

			*data_ptr++ = cpu_to_le32(wrval);
			*data_ptr++ = cpu_to_le32(data);
		पूर्ण
	पूर्ण

	*d_ptr = data_ptr;
निकास_process_rddfe:
	वापस rval;
पूर्ण

अटल uपूर्णांक32_t qla4_84xx_minidump_process_rdmdio(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t addr1, addr2, value1, value2, data, selval;
	uपूर्णांक8_t stride1, stride2;
	uपूर्णांक32_t addr3, addr4, addr5, addr6, addr7;
	uपूर्णांक16_t count, loop_cnt;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	काष्ठा qla8044_minidump_entry_rdmdio *rdmdio;

	rdmdio = (काष्ठा qla8044_minidump_entry_rdmdio *)entry_hdr;
	addr1 = le32_to_cpu(rdmdio->addr_1);
	addr2 = le32_to_cpu(rdmdio->addr_2);
	value1 = le32_to_cpu(rdmdio->value_1);
	stride1 = le32_to_cpu(rdmdio->stride_1);
	stride2 = le32_to_cpu(rdmdio->stride_2);
	count = le32_to_cpu(rdmdio->count);

	mask = le32_to_cpu(rdmdio->mask);
	value2 = le32_to_cpu(rdmdio->value_2);

	addr3 = addr1 + stride1;

	क्रम (loop_cnt = 0; loop_cnt < count; loop_cnt++) अणु
		rval = ql4_84xx_poll_रुको_ipmdio_bus_idle(ha, addr1, addr2,
							 addr3, mask);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		addr4 = addr2 - stride1;
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask, addr4,
					     value2);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		addr5 = addr2 - (2 * stride1);
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask, addr5,
					     value1);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		addr6 = addr2 - (3 * stride1);
		rval = ql4_84xx_ipmdio_wr_reg(ha, addr1, addr3, mask,
					     addr6, 0x2);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		rval = ql4_84xx_poll_रुको_ipmdio_bus_idle(ha, addr1, addr2,
							 addr3, mask);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		addr7 = addr2 - (4 * stride1);
		rval = ql4_84xx_ipmdio_rd_reg(ha, addr1, addr3,
						      mask, addr7, &data);
		अगर (rval)
			जाओ निकास_process_rdmdio;

		selval = (value2 << 18) | (value1 << 2) | 2;

		stride2 = le32_to_cpu(rdmdio->stride_2);
		*data_ptr++ = cpu_to_le32(selval);
		*data_ptr++ = cpu_to_le32(data);

		value1 = value1 + stride2;
		*d_ptr = data_ptr;
	पूर्ण

निकास_process_rdmdio:
	वापस rval;
पूर्ण

अटल uपूर्णांक32_t qla4_84xx_minidump_process_pollwr(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t addr1, addr2, value1, value2, poll, r_value;
	काष्ठा qla8044_minidump_entry_pollwr *pollwr_hdr;
	uपूर्णांक32_t रुको_count = 0;
	uपूर्णांक32_t rval = QLA_SUCCESS;

	pollwr_hdr = (काष्ठा qla8044_minidump_entry_pollwr *)entry_hdr;
	addr1 = le32_to_cpu(pollwr_hdr->addr_1);
	addr2 = le32_to_cpu(pollwr_hdr->addr_2);
	value1 = le32_to_cpu(pollwr_hdr->value_1);
	value2 = le32_to_cpu(pollwr_hdr->value_2);

	poll = le32_to_cpu(pollwr_hdr->poll);

	जबतक (रुको_count < poll) अणु
		ha->isp_ops->rd_reg_indirect(ha, addr1, &r_value);

		अगर ((r_value & poll) != 0)
			अवरोध;

		रुको_count++;
	पूर्ण

	अगर (रुको_count == poll) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT\n", __func__);
		rval = QLA_ERROR;
		जाओ निकास_process_pollwr;
	पूर्ण

	ha->isp_ops->wr_reg_indirect(ha, addr2, value2);
	ha->isp_ops->wr_reg_indirect(ha, addr1, value1);

	रुको_count = 0;
	जबतक (रुको_count < poll) अणु
		ha->isp_ops->rd_reg_indirect(ha, addr1, &r_value);

		अगर ((r_value & poll) != 0)
			अवरोध;
		रुको_count++;
	पूर्ण

निकास_process_pollwr:
	वापस rval;
पूर्ण

अटल व्योम qla83xx_minidump_process_rdmux2(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t sel_val1, sel_val2, t_sel_val, data, i;
	uपूर्णांक32_t sel_addr1, sel_addr2, sel_val_mask, पढ़ो_addr;
	काष्ठा qla83xx_minidump_entry_rdmux2 *rdmux2_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	rdmux2_hdr = (काष्ठा qla83xx_minidump_entry_rdmux2 *)entry_hdr;
	sel_val1 = le32_to_cpu(rdmux2_hdr->select_value_1);
	sel_val2 = le32_to_cpu(rdmux2_hdr->select_value_2);
	sel_addr1 = le32_to_cpu(rdmux2_hdr->select_addr_1);
	sel_addr2 = le32_to_cpu(rdmux2_hdr->select_addr_2);
	sel_val_mask = le32_to_cpu(rdmux2_hdr->select_value_mask);
	पढ़ो_addr = le32_to_cpu(rdmux2_hdr->पढ़ो_addr);

	क्रम (i = 0; i < rdmux2_hdr->op_count; i++) अणु
		ha->isp_ops->wr_reg_indirect(ha, sel_addr1, sel_val1);
		t_sel_val = sel_val1 & sel_val_mask;
		*data_ptr++ = cpu_to_le32(t_sel_val);

		ha->isp_ops->wr_reg_indirect(ha, sel_addr2, t_sel_val);
		ha->isp_ops->rd_reg_indirect(ha, पढ़ो_addr, &data);

		*data_ptr++ = cpu_to_le32(data);

		ha->isp_ops->wr_reg_indirect(ha, sel_addr1, sel_val2);
		t_sel_val = sel_val2 & sel_val_mask;
		*data_ptr++ = cpu_to_le32(t_sel_val);

		ha->isp_ops->wr_reg_indirect(ha, sel_addr2, t_sel_val);
		ha->isp_ops->rd_reg_indirect(ha, पढ़ो_addr, &data);

		*data_ptr++ = cpu_to_le32(data);

		sel_val1 += rdmux2_hdr->select_value_stride;
		sel_val2 += rdmux2_hdr->select_value_stride;
	पूर्ण

	*d_ptr = data_ptr;
पूर्ण

अटल uपूर्णांक32_t qla83xx_minidump_process_pollrdmwr(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t poll_रुको, poll_mask, r_value, data;
	uपूर्णांक32_t addr_1, addr_2, value_1, value_2;
	uपूर्णांक32_t *data_ptr = *d_ptr;
	uपूर्णांक32_t rval = QLA_SUCCESS;
	काष्ठा qla83xx_minidump_entry_pollrdmwr *poll_hdr;

	poll_hdr = (काष्ठा qla83xx_minidump_entry_pollrdmwr *)entry_hdr;
	addr_1 = le32_to_cpu(poll_hdr->addr_1);
	addr_2 = le32_to_cpu(poll_hdr->addr_2);
	value_1 = le32_to_cpu(poll_hdr->value_1);
	value_2 = le32_to_cpu(poll_hdr->value_2);
	poll_mask = le32_to_cpu(poll_hdr->poll_mask);

	ha->isp_ops->wr_reg_indirect(ha, addr_1, value_1);

	poll_रुको = le32_to_cpu(poll_hdr->poll_रुको);
	जबतक (1) अणु
		ha->isp_ops->rd_reg_indirect(ha, addr_1, &r_value);

		अगर ((r_value & poll_mask) != 0) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			msleep(1);
			अगर (--poll_रुको == 0) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT_1\n",
					   __func__);
				rval = QLA_ERROR;
				जाओ निकास_process_pollrdmwr;
			पूर्ण
		पूर्ण
	पूर्ण

	ha->isp_ops->rd_reg_indirect(ha, addr_2, &data);
	data &= le32_to_cpu(poll_hdr->modअगरy_mask);
	ha->isp_ops->wr_reg_indirect(ha, addr_2, data);
	ha->isp_ops->wr_reg_indirect(ha, addr_1, value_2);

	poll_रुको = le32_to_cpu(poll_hdr->poll_रुको);
	जबतक (1) अणु
		ha->isp_ops->rd_reg_indirect(ha, addr_1, &r_value);

		अगर ((r_value & poll_mask) != 0) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			msleep(1);
			अगर (--poll_रुको == 0) अणु
				ql4_prपूर्णांकk(KERN_ERR, ha, "%s: TIMEOUT_2\n",
					   __func__);
				rval = QLA_ERROR;
				जाओ निकास_process_pollrdmwr;
			पूर्ण
		पूर्ण
	पूर्ण

	*data_ptr++ = cpu_to_le32(addr_2);
	*data_ptr++ = cpu_to_le32(data);
	*d_ptr = data_ptr;

निकास_process_pollrdmwr:
	वापस rval;
पूर्ण

अटल uपूर्णांक32_t qla4_83xx_minidump_process_rdrom(काष्ठा scsi_qla_host *ha,
				काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr,
				uपूर्णांक32_t **d_ptr)
अणु
	uपूर्णांक32_t fl_addr, u32_count, rval;
	काष्ठा qla8xxx_minidump_entry_rdrom *rom_hdr;
	uपूर्णांक32_t *data_ptr = *d_ptr;

	rom_hdr = (काष्ठा qla8xxx_minidump_entry_rdrom *)entry_hdr;
	fl_addr = le32_to_cpu(rom_hdr->पढ़ो_addr);
	u32_count = le32_to_cpu(rom_hdr->पढ़ो_data_size)/माप(uपूर्णांक32_t);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "[%s]: fl_addr: 0x%x, count: 0x%x\n",
			  __func__, fl_addr, u32_count));

	rval = qla4_83xx_lockless_flash_पढ़ो_u32(ha, fl_addr,
						 (u8 *)(data_ptr), u32_count);

	अगर (rval == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Flash Read Error,Count=%d\n",
			   __func__, u32_count);
		जाओ निकास_process_rdrom;
	पूर्ण

	data_ptr += u32_count;
	*d_ptr = data_ptr;

निकास_process_rdrom:
	वापस rval;
पूर्ण

/**
 * qla4_8xxx_collect_md_data - Retrieve firmware minidump data.
 * @ha: poपूर्णांकer to adapter काष्ठाure
 **/
अटल पूर्णांक qla4_8xxx_collect_md_data(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक num_entry_hdr = 0;
	काष्ठा qla8xxx_minidump_entry_hdr *entry_hdr;
	काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *पंचांगplt_hdr;
	uपूर्णांक32_t *data_ptr;
	uपूर्णांक32_t data_collected = 0;
	पूर्णांक i, rval = QLA_ERROR;
	uपूर्णांक64_t now;
	uपूर्णांक32_t बारtamp;

	ha->fw_dump_skip_size = 0;
	अगर (!ha->fw_dump) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s(%ld) No buffer to dump\n",
			   __func__, ha->host_no);
		वापस rval;
	पूर्ण

	पंचांगplt_hdr = (काष्ठा qla4_8xxx_minidump_ढाँचा_hdr *)
						ha->fw_dump_पंचांगplt_hdr;
	data_ptr = (uपूर्णांक32_t *)((uपूर्णांक8_t *)ha->fw_dump +
						ha->fw_dump_पंचांगplt_size);
	data_collected += ha->fw_dump_पंचांगplt_size;

	num_entry_hdr = पंचांगplt_hdr->num_of_entries;
	ql4_prपूर्णांकk(KERN_INFO, ha, "[%s]: starting data ptr: %p\n",
		   __func__, data_ptr);
	ql4_prपूर्णांकk(KERN_INFO, ha,
		   "[%s]: no of entry headers in Template: 0x%x\n",
		   __func__, num_entry_hdr);
	ql4_prपूर्णांकk(KERN_INFO, ha, "[%s]: Capture Mask obtained: 0x%x\n",
		   __func__, ha->fw_dump_capture_mask);
	ql4_prपूर्णांकk(KERN_INFO, ha, "[%s]: Total_data_size 0x%x, %d obtained\n",
		   __func__, ha->fw_dump_size, ha->fw_dump_size);

	/* Update current बारtamp beक्रमe taking dump */
	now = get_jअगरfies_64();
	बारtamp = (u32)(jअगरfies_to_msecs(now) / 1000);
	पंचांगplt_hdr->driver_बारtamp = बारtamp;

	entry_hdr = (काष्ठा qla8xxx_minidump_entry_hdr *)
					(((uपूर्णांक8_t *)ha->fw_dump_पंचांगplt_hdr) +
					 पंचांगplt_hdr->first_entry_offset);

	अगर (is_qla8032(ha) || is_qla8042(ha))
		पंचांगplt_hdr->saved_state_array[QLA83XX_SS_OCM_WNDREG_INDEX] =
					पंचांगplt_hdr->ocm_winकरोw_reg[ha->func_num];

	/* Walk through the entry headers - validate/perक्रमm required action */
	क्रम (i = 0; i < num_entry_hdr; i++) अणु
		अगर (data_collected > ha->fw_dump_size) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "Data collected: [0x%x], Total Dump size: [0x%x]\n",
				   data_collected, ha->fw_dump_size);
			वापस rval;
		पूर्ण

		अगर (!(entry_hdr->d_ctrl.entry_capture_mask &
		      ha->fw_dump_capture_mask)) अणु
			entry_hdr->d_ctrl.driver_flags |=
						QLA8XXX_DBG_SKIPPED_FLAG;
			जाओ skip_nxt_entry;
		पूर्ण

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Data collected: [0x%x], Dump size left:[0x%x]\n",
				  data_collected,
				  (ha->fw_dump_size - data_collected)));

		/* Decode the entry type and take required action to capture
		 * debug data
		 */
		चयन (entry_hdr->entry_type) अणु
		हाल QLA8XXX_RDEND:
			qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA8XXX_CNTRL:
			rval = qla4_8xxx_minidump_process_control(ha,
								  entry_hdr);
			अगर (rval != QLA_SUCCESS) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA8XXX_RDCRB:
			qla4_8xxx_minidump_process_rdcrb(ha, entry_hdr,
							 &data_ptr);
			अवरोध;
		हाल QLA8XXX_RDMEM:
			rval = qla4_8xxx_minidump_process_rdmem(ha, entry_hdr,
								&data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA8XXX_BOARD:
		हाल QLA8XXX_RDROM:
			अगर (is_qla8022(ha)) अणु
				qla4_82xx_minidump_process_rdrom(ha, entry_hdr,
								 &data_ptr);
			पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				rval = qla4_83xx_minidump_process_rdrom(ha,
								    entry_hdr,
								    &data_ptr);
				अगर (rval != QLA_SUCCESS)
					qla4_8xxx_mark_entry_skipped(ha,
								     entry_hdr,
								     i);
			पूर्ण
			अवरोध;
		हाल QLA8XXX_L2DTG:
		हाल QLA8XXX_L2ITG:
		हाल QLA8XXX_L2DAT:
		हाल QLA8XXX_L2INS:
			rval = qla4_8xxx_minidump_process_l2tag(ha, entry_hdr,
								&data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA8XXX_L1DTG:
		हाल QLA8XXX_L1ITG:
		हाल QLA8XXX_L1DAT:
		हाल QLA8XXX_L1INS:
			qla4_8xxx_minidump_process_l1cache(ha, entry_hdr,
							   &data_ptr);
			अवरोध;
		हाल QLA8XXX_RDOCM:
			qla4_8xxx_minidump_process_rकरोcm(ha, entry_hdr,
							 &data_ptr);
			अवरोध;
		हाल QLA8XXX_RDMUX:
			qla4_8xxx_minidump_process_rdmux(ha, entry_hdr,
							 &data_ptr);
			अवरोध;
		हाल QLA8XXX_QUEUE:
			qla4_8xxx_minidump_process_queue(ha, entry_hdr,
							 &data_ptr);
			अवरोध;
		हाल QLA83XX_POLLRD:
			अगर (is_qla8022(ha)) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				अवरोध;
			पूर्ण
			rval = qla83xx_minidump_process_pollrd(ha, entry_hdr,
							       &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA83XX_RDMUX2:
			अगर (is_qla8022(ha)) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				अवरोध;
			पूर्ण
			qla83xx_minidump_process_rdmux2(ha, entry_hdr,
							&data_ptr);
			अवरोध;
		हाल QLA83XX_POLLRDMWR:
			अगर (is_qla8022(ha)) अणु
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
				अवरोध;
			पूर्ण
			rval = qla83xx_minidump_process_pollrdmwr(ha, entry_hdr,
								  &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_RDDFE:
			rval = qla4_84xx_minidump_process_rddfe(ha, entry_hdr,
								&data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_RDMDIO:
			rval = qla4_84xx_minidump_process_rdmdio(ha, entry_hdr,
								 &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA8044_POLLWR:
			rval = qla4_84xx_minidump_process_pollwr(ha, entry_hdr,
								 &data_ptr);
			अगर (rval != QLA_SUCCESS)
				qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		हाल QLA8XXX_RDNOP:
		शेष:
			qla4_8xxx_mark_entry_skipped(ha, entry_hdr, i);
			अवरोध;
		पूर्ण

		data_collected = (uपूर्णांक8_t *)data_ptr - (uपूर्णांक8_t *)ha->fw_dump;
skip_nxt_entry:
		/*  next entry in the ढाँचा */
		entry_hdr = (काष्ठा qla8xxx_minidump_entry_hdr *)
				(((uपूर्णांक8_t *)entry_hdr) +
				 entry_hdr->entry_size);
	पूर्ण

	अगर ((data_collected + ha->fw_dump_skip_size) != ha->fw_dump_size) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "Dump data mismatch: Data collected: [0x%x], total_data_size:[0x%x]\n",
			   data_collected, ha->fw_dump_size);
		rval = QLA_ERROR;
		जाओ md_failed;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Leaving fn: %s Last entry: 0x%x\n",
			  __func__, i));
md_failed:
	वापस rval;
पूर्ण

/**
 * qla4_8xxx_uevent_emit - Send uevent when the firmware dump is पढ़ोy.
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @code: uevent code to act upon
 **/
अटल व्योम qla4_8xxx_uevent_emit(काष्ठा scsi_qla_host *ha, u32 code)
अणु
	अक्षर event_string[40];
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;

	चयन (code) अणु
	हाल QL4_UEVENT_CODE_FW_DUMP:
		snम_लिखो(event_string, माप(event_string), "FW_DUMP=%lu",
			 ha->host_no);
		अवरोध;
	शेष:
		/*करो nothing*/
		अवरोध;
	पूर्ण

	kobject_uevent_env(&(&ha->pdev->dev)->kobj, KOBJ_CHANGE, envp);
पूर्ण

व्योम qla4_8xxx_get_minidump(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ql4xenablemd && test_bit(AF_FW_RECOVERY, &ha->flags) &&
	    !test_bit(AF_82XX_FW_DUMPED, &ha->flags)) अणु
		अगर (!qla4_8xxx_collect_md_data(ha)) अणु
			qla4_8xxx_uevent_emit(ha, QL4_UEVENT_CODE_FW_DUMP);
			set_bit(AF_82XX_FW_DUMPED, &ha->flags);
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Unable to collect minidump\n",
				   __func__);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * qla4_8xxx_device_bootstrap - Initialize device, set DEV_READY, start fw
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Note: IDC lock must be held upon entry
 **/
पूर्णांक qla4_8xxx_device_bootstrap(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval = QLA_ERROR;
	पूर्णांक i;
	uपूर्णांक32_t old_count, count;
	पूर्णांक need_reset = 0;

	need_reset = ha->isp_ops->need_reset(ha);

	अगर (need_reset) अणु
		/* We are trying to perक्रमm a recovery here. */
		अगर (test_bit(AF_FW_RECOVERY, &ha->flags))
			ha->isp_ops->rom_lock_recovery(ha);
	पूर्ण अन्यथा  अणु
		old_count = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_ALIVE_COUNTER);
		क्रम (i = 0; i < 10; i++) अणु
			msleep(200);
			count = qla4_8xxx_rd_direct(ha,
						    QLA8XXX_PEG_ALIVE_COUNTER);
			अगर (count != old_count) अणु
				rval = QLA_SUCCESS;
				जाओ dev_पढ़ोy;
			पूर्ण
		पूर्ण
		ha->isp_ops->rom_lock_recovery(ha);
	पूर्ण

	/* set to DEV_INITIALIZING */
	ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: INITIALIZING\n");
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
			    QLA8XXX_DEV_INITIALIZING);

	ha->isp_ops->idc_unlock(ha);

	अगर (is_qla8022(ha))
		qla4_8xxx_get_minidump(ha);

	rval = ha->isp_ops->restart_firmware(ha);
	ha->isp_ops->idc_lock(ha);

	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: FAILED\n");
		qla4_8xxx_clear_drv_active(ha);
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
				    QLA8XXX_DEV_FAILED);
		वापस rval;
	पूर्ण

dev_पढ़ोy:
	ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: READY\n");
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE, QLA8XXX_DEV_READY);

	वापस rval;
पूर्ण

/**
 * qla4_82xx_need_reset_handler - Code to start reset sequence
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Note: IDC lock must be held upon entry
 **/
अटल व्योम
qla4_82xx_need_reset_handler(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t dev_state, drv_state, drv_active;
	uपूर्णांक32_t active_mask = 0xFFFFFFFF;
	अचिन्हित दीर्घ reset_समयout;

	ql4_prपूर्णांकk(KERN_INFO, ha,
		"Performing ISP error recovery\n");

	अगर (test_and_clear_bit(AF_ONLINE, &ha->flags)) अणु
		qla4_82xx_idc_unlock(ha);
		ha->isp_ops->disable_पूर्णांकrs(ha);
		qla4_82xx_idc_lock(ha);
	पूर्ण

	अगर (!test_bit(AF_8XXX_RST_OWNER, &ha->flags)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s(%ld): reset acknowledged\n",
				  __func__, ha->host_no));
		qla4_8xxx_set_rst_पढ़ोy(ha);
	पूर्ण अन्यथा अणु
		active_mask = (~(1 << (ha->func_num * 4)));
	पूर्ण

	/* रुको क्रम 10 seconds क्रम reset ack from all functions */
	reset_समयout = jअगरfies + (ha->nx_reset_समयout * HZ);

	drv_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_active = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);

	ql4_prपूर्णांकk(KERN_INFO, ha,
		"%s(%ld): drv_state = 0x%x, drv_active = 0x%x\n",
		__func__, ha->host_no, drv_state, drv_active);

	जबतक (drv_state != (drv_active & active_mask)) अणु
		अगर (समय_after_eq(jअगरfies, reset_समयout)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s: RESET TIMEOUT! drv_state: 0x%08x, drv_active: 0x%08x\n",
				   DRIVER_NAME, drv_state, drv_active);
			अवरोध;
		पूर्ण

		/*
		 * When reset_owner बार out, check which functions
		 * acked/did not ack
		 */
		अगर (test_bit(AF_8XXX_RST_OWNER, &ha->flags)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s(%ld): drv_state = 0x%x, drv_active = 0x%x\n",
				   __func__, ha->host_no, drv_state,
				   drv_active);
		पूर्ण
		qla4_82xx_idc_unlock(ha);
		msleep(1000);
		qla4_82xx_idc_lock(ha);

		drv_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		drv_active = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	पूर्ण

	/* Clear RESET OWNER as we are not going to use it any further */
	clear_bit(AF_8XXX_RST_OWNER, &ha->flags);

	dev_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	ql4_prपूर्णांकk(KERN_INFO, ha, "Device state is 0x%x = %s\n", dev_state,
		   dev_state < MAX_STATES ? qdev_state[dev_state] : "Unknown");

	/* Force to DEV_COLD unless someone अन्यथा is starting a reset */
	अगर (dev_state != QLA8XXX_DEV_INITIALIZING) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: COLD/RE-INIT\n");
		qla4_82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_COLD);
		qla4_8xxx_set_rst_पढ़ोy(ha);
	पूर्ण
पूर्ण

/**
 * qla4_8xxx_need_qsnt_handler - Code to start qsnt
 * @ha: poपूर्णांकer to adapter काष्ठाure
 **/
व्योम
qla4_8xxx_need_qsnt_handler(काष्ठा scsi_qla_host *ha)
अणु
	ha->isp_ops->idc_lock(ha);
	qla4_8xxx_set_qsnt_पढ़ोy(ha);
	ha->isp_ops->idc_unlock(ha);
पूर्ण

अटल व्योम qla4_82xx_set_idc_ver(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक idc_ver;
	uपूर्णांक32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
	अगर (drv_active == (1 << (ha->func_num * 4))) अणु
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION,
				    QLA82XX_IDC_VERSION);
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: IDC version updated to %d\n", __func__,
			   QLA82XX_IDC_VERSION);
	पूर्ण अन्यथा अणु
		idc_ver = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION);
		अगर (QLA82XX_IDC_VERSION != idc_ver) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s: qla4xxx driver IDC version %d is not compatible with IDC version %d of other drivers!\n",
				   __func__, QLA82XX_IDC_VERSION, idc_ver);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qla4_83xx_set_idc_ver(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक idc_ver;
	uपूर्णांक32_t drv_active;
	पूर्णांक rval = QLA_SUCCESS;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
	अगर (drv_active == (1 << ha->func_num)) अणु
		idc_ver = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION);
		idc_ver &= (~0xFF);
		idc_ver |= QLA83XX_IDC_VER_MAJ_VALUE;
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION, idc_ver);
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: IDC version updated to %d\n", __func__,
			   idc_ver);
	पूर्ण अन्यथा अणु
		idc_ver = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_IDC_VERSION);
		idc_ver &= 0xFF;
		अगर (QLA83XX_IDC_VER_MAJ_VALUE != idc_ver) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "%s: qla4xxx driver IDC version %d is not compatible with IDC version %d of other drivers!\n",
				   __func__, QLA83XX_IDC_VER_MAJ_VALUE,
				   idc_ver);
			rval = QLA_ERROR;
			जाओ निकास_set_idc_ver;
		पूर्ण
	पूर्ण

	/* Update IDC_MINOR_VERSION */
	idc_ver = qla4_83xx_rd_reg(ha, QLA83XX_CRB_IDC_VER_MINOR);
	idc_ver &= ~(0x03 << (ha->func_num * 2));
	idc_ver |= (QLA83XX_IDC_VER_MIN_VALUE << (ha->func_num * 2));
	qla4_83xx_wr_reg(ha, QLA83XX_CRB_IDC_VER_MINOR, idc_ver);

निकास_set_idc_ver:
	वापस rval;
पूर्ण

पूर्णांक qla4_8xxx_update_idc_reg(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t drv_active;
	पूर्णांक rval = QLA_SUCCESS;

	अगर (test_bit(AF_INIT_DONE, &ha->flags))
		जाओ निकास_update_idc_reg;

	ha->isp_ops->idc_lock(ha);
	qla4_8xxx_set_drv_active(ha);

	/*
	 * If we are the first driver to load and
	 * ql4xकरोntresethba is not set, clear IDC_CTRL BIT0.
	 */
	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
		अगर ((drv_active == (1 << ha->func_num)) && !ql4xकरोntresethba)
			qla4_83xx_clear_idc_करोntreset(ha);
	पूर्ण

	अगर (is_qla8022(ha)) अणु
		qla4_82xx_set_idc_ver(ha);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		rval = qla4_83xx_set_idc_ver(ha);
		अगर (rval == QLA_ERROR)
			qla4_8xxx_clear_drv_active(ha);
	पूर्ण

	ha->isp_ops->idc_unlock(ha);

निकास_update_idc_reg:
	वापस rval;
पूर्ण

/**
 * qla4_8xxx_device_state_handler - Adapter state machine
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * Note: IDC lock must be UNLOCKED upon entry
 **/
पूर्णांक qla4_8xxx_device_state_handler(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t dev_state;
	पूर्णांक rval = QLA_SUCCESS;
	अचिन्हित दीर्घ dev_init_समयout;

	rval = qla4_8xxx_update_idc_reg(ha);
	अगर (rval == QLA_ERROR)
		जाओ निकास_state_handler;

	dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Device state is 0x%x = %s\n",
			  dev_state, dev_state < MAX_STATES ?
			  qdev_state[dev_state] : "Unknown"));

	/* रुको क्रम 30 seconds क्रम device to go पढ़ोy */
	dev_init_समयout = jअगरfies + (ha->nx_dev_init_समयout * HZ);

	ha->isp_ops->idc_lock(ha);
	जबतक (1) अणु

		अगर (समय_after_eq(jअगरfies, dev_init_समयout)) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
				   "%s: Device Init Failed 0x%x = %s\n",
				   DRIVER_NAME,
				   dev_state, dev_state < MAX_STATES ?
				   qdev_state[dev_state] : "Unknown");
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
		पूर्ण

		dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
		ql4_prपूर्णांकk(KERN_INFO, ha, "Device state is 0x%x = %s\n",
			   dev_state, dev_state < MAX_STATES ?
			   qdev_state[dev_state] : "Unknown");

		/* NOTE: Make sure idc unlocked upon निकास of चयन statement */
		चयन (dev_state) अणु
		हाल QLA8XXX_DEV_READY:
			जाओ निकास;
		हाल QLA8XXX_DEV_COLD:
			rval = qla4_8xxx_device_bootstrap(ha);
			जाओ निकास;
		हाल QLA8XXX_DEV_INITIALIZING:
			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_RESET:
			/*
			 * For ISP8324 and ISP8042, अगर NEED_RESET is set by any
			 * driver, it should be honored, irrespective of
			 * IDC_CTRL DONTRESET_BIT0
			 */
			अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				qla4_83xx_need_reset_handler(ha);
			पूर्ण अन्यथा अगर (is_qla8022(ha)) अणु
				अगर (!ql4xकरोntresethba) अणु
					qla4_82xx_need_reset_handler(ha);
					/* Update समयout value after need
					 * reset handler */
					dev_init_समयout = jअगरfies +
						(ha->nx_dev_init_समयout * HZ);
				पूर्ण अन्यथा अणु
					ha->isp_ops->idc_unlock(ha);
					msleep(1000);
					ha->isp_ops->idc_lock(ha);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल QLA8XXX_DEV_NEED_QUIESCENT:
			/* idc locked/unlocked in handler */
			qla4_8xxx_need_qsnt_handler(ha);
			अवरोध;
		हाल QLA8XXX_DEV_QUIESCENT:
			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);
			अवरोध;
		हाल QLA8XXX_DEV_FAILED:
			ha->isp_ops->idc_unlock(ha);
			qla4xxx_dead_adapter_cleanup(ha);
			rval = QLA_ERROR;
			ha->isp_ops->idc_lock(ha);
			जाओ निकास;
		शेष:
			ha->isp_ops->idc_unlock(ha);
			qla4xxx_dead_adapter_cleanup(ha);
			rval = QLA_ERROR;
			ha->isp_ops->idc_lock(ha);
			जाओ निकास;
		पूर्ण
	पूर्ण
निकास:
	ha->isp_ops->idc_unlock(ha);
निकास_state_handler:
	वापस rval;
पूर्ण

पूर्णांक qla4_8xxx_load_risc(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक retval;

	/* clear the पूर्णांकerrupt */
	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ग_लिखोl(0, &ha->qla4_83xx_reg->risc_पूर्णांकr);
		पढ़ोl(&ha->qla4_83xx_reg->risc_पूर्णांकr);
	पूर्ण अन्यथा अगर (is_qla8022(ha)) अणु
		ग_लिखोl(0, &ha->qla4_82xx_reg->host_पूर्णांक);
		पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक);
	पूर्ण

	retval = qla4_8xxx_device_state_handler(ha);

	/* Initialize request and response queues. */
	अगर (retval == QLA_SUCCESS)
		qla4xxx_init_rings(ha);

	अगर (retval == QLA_SUCCESS && !test_bit(AF_IRQ_ATTACHED, &ha->flags))
		retval = qla4xxx_request_irqs(ha);

	वापस retval;
पूर्ण

/*****************************************************************************/
/* Flash Manipulation Routines                                               */
/*****************************************************************************/

#घोषणा OPTROM_BURST_SIZE       0x1000
#घोषणा OPTROM_BURST_DWORDS     (OPTROM_BURST_SIZE / 4)

#घोषणा FARX_DATA_FLAG	BIT_31
#घोषणा FARX_ACCESS_FLASH_CONF	0x7FFD0000
#घोषणा FARX_ACCESS_FLASH_DATA	0x7FF00000

अटल अंतरभूत uपूर्णांक32_t
flash_conf_addr(काष्ठा ql82xx_hw_data *hw, uपूर्णांक32_t faddr)
अणु
	वापस hw->flash_conf_off | faddr;
पूर्ण

अटल uपूर्णांक32_t *
qla4_82xx_पढ़ो_flash_data(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *dwptr,
    uपूर्णांक32_t faddr, uपूर्णांक32_t length)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t val;
	पूर्णांक loops = 0;
	जबतक ((qla4_82xx_rom_lock(ha) != 0) && (loops < 50000)) अणु
		udelay(100);
		cond_resched();
		loops++;
	पूर्ण
	अगर (loops >= 50000) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "ROM lock failed\n");
		वापस dwptr;
	पूर्ण

	/* Dword पढ़ोs to flash. */
	क्रम (i = 0; i < length/4; i++, faddr += 4) अणु
		अगर (qla4_82xx_करो_rom_fast_पढ़ो(ha, faddr, &val)) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
			    "Do ROM fast read failed\n");
			जाओ करोne_पढ़ो;
		पूर्ण
		dwptr[i] = __स्थिरant_cpu_to_le32(val);
	पूर्ण

करोne_पढ़ो:
	qla4_82xx_rom_unlock(ha);
	वापस dwptr;
पूर्ण

/*
 * Address and length are byte address
 */
अटल uपूर्णांक8_t *
qla4_82xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *ha, uपूर्णांक8_t *buf,
		uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	qla4_82xx_पढ़ो_flash_data(ha, (uपूर्णांक32_t *)buf, offset, length);
	वापस buf;
पूर्ण

अटल पूर्णांक
qla4_8xxx_find_flt_start(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *start)
अणु
	स्थिर अक्षर *loc, *locations[] = अणु "DEF", "PCI" पूर्ण;

	/*
	 * FLT-location काष्ठाure resides after the last PCI region.
	 */

	/* Begin with sane शेषs. */
	loc = locations[0];
	*start = FA_FLASH_LAYOUT_ADDR_82;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "FLTL[%s] = 0x%x.\n", loc, *start));
	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम
qla4_8xxx_get_flt_info(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t flt_addr)
अणु
	स्थिर अक्षर *loc, *locations[] = अणु "DEF", "FLT" पूर्ण;
	uपूर्णांक16_t *wptr;
	uपूर्णांक16_t cnt, chksum;
	uपूर्णांक32_t start, status;
	काष्ठा qla_flt_header *flt;
	काष्ठा qla_flt_region *region;
	काष्ठा ql82xx_hw_data *hw = &ha->hw;

	hw->flt_region_flt = flt_addr;
	wptr = (uपूर्णांक16_t *)ha->request_ring;
	flt = (काष्ठा qla_flt_header *)ha->request_ring;
	region = (काष्ठा qla_flt_region *)&flt[1];

	अगर (is_qla8022(ha)) अणु
		qla4_82xx_पढ़ो_optrom_data(ha, (uपूर्णांक8_t *)ha->request_ring,
					   flt_addr << 2, OPTROM_BURST_SIZE);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		status = qla4_83xx_flash_पढ़ो_u32(ha, flt_addr << 2,
						  (uपूर्णांक8_t *)ha->request_ring,
						  0x400);
		अगर (status != QLA_SUCCESS)
			जाओ no_flash_data;
	पूर्ण

	अगर (*wptr == __स्थिरant_cpu_to_le16(0xffff))
		जाओ no_flash_data;
	अगर (flt->version != __स्थिरant_cpu_to_le16(1)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Unsupported FLT detected: "
			"version=0x%x length=0x%x checksum=0x%x.\n",
			le16_to_cpu(flt->version), le16_to_cpu(flt->length),
			le16_to_cpu(flt->checksum)));
		जाओ no_flash_data;
	पूर्ण

	cnt = (माप(काष्ठा qla_flt_header) + le16_to_cpu(flt->length)) >> 1;
	क्रम (chksum = 0; cnt; cnt--)
		chksum += le16_to_cpu(*wptr++);
	अगर (chksum) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Inconsistent FLT detected: "
			"version=0x%x length=0x%x checksum=0x%x.\n",
			le16_to_cpu(flt->version), le16_to_cpu(flt->length),
			chksum));
		जाओ no_flash_data;
	पूर्ण

	loc = locations[1];
	cnt = le16_to_cpu(flt->length) / माप(काष्ठा qla_flt_region);
	क्रम ( ; cnt; cnt--, region++) अणु
		/* Store addresses as DWORD offsets. */
		start = le32_to_cpu(region->start) >> 2;

		DEBUG3(ql4_prपूर्णांकk(KERN_DEBUG, ha, "FLT[%02x]: start=0x%x "
		    "end=0x%x size=0x%x.\n", le32_to_cpu(region->code), start,
		    le32_to_cpu(region->end) >> 2, le32_to_cpu(region->size)));

		चयन (le32_to_cpu(region->code) & 0xff) अणु
		हाल FLT_REG_FDT:
			hw->flt_region_fdt = start;
			अवरोध;
		हाल FLT_REG_BOOT_CODE_82:
			hw->flt_region_boot = start;
			अवरोध;
		हाल FLT_REG_FW_82:
		हाल FLT_REG_FW_82_1:
			hw->flt_region_fw = start;
			अवरोध;
		हाल FLT_REG_BOOTLOAD_82:
			hw->flt_region_bootload = start;
			अवरोध;
		हाल FLT_REG_ISCSI_PARAM:
			hw->flt_iscsi_param =  start;
			अवरोध;
		हाल FLT_REG_ISCSI_CHAP:
			hw->flt_region_chap =  start;
			hw->flt_chap_size =  le32_to_cpu(region->size);
			अवरोध;
		हाल FLT_REG_ISCSI_DDB:
			hw->flt_region_ddb =  start;
			hw->flt_ddb_size =  le32_to_cpu(region->size);
			अवरोध;
		पूर्ण
	पूर्ण
	जाओ करोne;

no_flash_data:
	/* Use hardcoded शेषs. */
	loc = locations[0];

	hw->flt_region_fdt      = FA_FLASH_DESCR_ADDR_82;
	hw->flt_region_boot     = FA_BOOT_CODE_ADDR_82;
	hw->flt_region_bootload = FA_BOOT_LOAD_ADDR_82;
	hw->flt_region_fw       = FA_RISC_CODE_ADDR_82;
	hw->flt_region_chap	= FA_FLASH_ISCSI_CHAP >> 2;
	hw->flt_chap_size	= FA_FLASH_CHAP_SIZE;
	hw->flt_region_ddb	= FA_FLASH_ISCSI_DDB >> 2;
	hw->flt_ddb_size	= FA_FLASH_DDB_SIZE;

करोne:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "FLT[%s]: flt=0x%x fdt=0x%x boot=0x%x bootload=0x%x fw=0x%x chap=0x%x chap_size=0x%x ddb=0x%x  ddb_size=0x%x\n",
			  loc, hw->flt_region_flt, hw->flt_region_fdt,
			  hw->flt_region_boot, hw->flt_region_bootload,
			  hw->flt_region_fw, hw->flt_region_chap,
			  hw->flt_chap_size, hw->flt_region_ddb,
			  hw->flt_ddb_size));
पूर्ण

अटल व्योम
qla4_82xx_get_fdt_info(काष्ठा scsi_qla_host *ha)
अणु
#घोषणा FLASH_BLK_SIZE_4K       0x1000
#घोषणा FLASH_BLK_SIZE_32K      0x8000
#घोषणा FLASH_BLK_SIZE_64K      0x10000
	स्थिर अक्षर *loc, *locations[] = अणु "MID", "FDT" पूर्ण;
	uपूर्णांक16_t cnt, chksum;
	uपूर्णांक16_t *wptr;
	काष्ठा qla_fdt_layout *fdt;
	uपूर्णांक16_t mid = 0;
	uपूर्णांक16_t fid = 0;
	काष्ठा ql82xx_hw_data *hw = &ha->hw;

	hw->flash_conf_off = FARX_ACCESS_FLASH_CONF;
	hw->flash_data_off = FARX_ACCESS_FLASH_DATA;

	wptr = (uपूर्णांक16_t *)ha->request_ring;
	fdt = (काष्ठा qla_fdt_layout *)ha->request_ring;
	qla4_82xx_पढ़ो_optrom_data(ha, (uपूर्णांक8_t *)ha->request_ring,
	    hw->flt_region_fdt << 2, OPTROM_BURST_SIZE);

	अगर (*wptr == __स्थिरant_cpu_to_le16(0xffff))
		जाओ no_flash_data;

	अगर (fdt->sig[0] != 'Q' || fdt->sig[1] != 'L' || fdt->sig[2] != 'I' ||
	    fdt->sig[3] != 'D')
		जाओ no_flash_data;

	क्रम (cnt = 0, chksum = 0; cnt < माप(काष्ठा qla_fdt_layout) >> 1;
	    cnt++)
		chksum += le16_to_cpu(*wptr++);

	अगर (chksum) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Inconsistent FDT detected: "
		    "checksum=0x%x id=%c version=0x%x.\n", chksum, fdt->sig[0],
		    le16_to_cpu(fdt->version)));
		जाओ no_flash_data;
	पूर्ण

	loc = locations[1];
	mid = le16_to_cpu(fdt->man_id);
	fid = le16_to_cpu(fdt->id);
	hw->fdt_wrt_disable = fdt->wrt_disable_bits;
	hw->fdt_erase_cmd = flash_conf_addr(hw, 0x0300 | fdt->erase_cmd);
	hw->fdt_block_size = le32_to_cpu(fdt->block_size);

	अगर (fdt->unprotect_sec_cmd) अणु
		hw->fdt_unprotect_sec_cmd = flash_conf_addr(hw, 0x0300 |
		    fdt->unprotect_sec_cmd);
		hw->fdt_protect_sec_cmd = fdt->protect_sec_cmd ?
		    flash_conf_addr(hw, 0x0300 | fdt->protect_sec_cmd) :
		    flash_conf_addr(hw, 0x0336);
	पूर्ण
	जाओ करोne;

no_flash_data:
	loc = locations[0];
	hw->fdt_block_size = FLASH_BLK_SIZE_64K;
करोne:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "FDT[%s]: (0x%x/0x%x) erase=0x%x "
		"pro=%x upro=%x wrtd=0x%x blk=0x%x.\n", loc, mid, fid,
		hw->fdt_erase_cmd, hw->fdt_protect_sec_cmd,
		hw->fdt_unprotect_sec_cmd, hw->fdt_wrt_disable,
		hw->fdt_block_size));
पूर्ण

अटल व्योम
qla4_82xx_get_idc_param(काष्ठा scsi_qla_host *ha)
अणु
#घोषणा QLA82XX_IDC_PARAM_ADDR      0x003e885c
	uपूर्णांक32_t *wptr;

	अगर (!is_qla8022(ha))
		वापस;
	wptr = (uपूर्णांक32_t *)ha->request_ring;
	qla4_82xx_पढ़ो_optrom_data(ha, (uपूर्णांक8_t *)ha->request_ring,
			QLA82XX_IDC_PARAM_ADDR , 8);

	अगर (*wptr == __स्थिरant_cpu_to_le32(0xffffffff)) अणु
		ha->nx_dev_init_समयout = ROM_DEV_INIT_TIMEOUT;
		ha->nx_reset_समयout = ROM_DRV_RESET_ACK_TIMEOUT;
	पूर्ण अन्यथा अणु
		ha->nx_dev_init_समयout = le32_to_cpu(*wptr++);
		ha->nx_reset_समयout = le32_to_cpu(*wptr);
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_DEBUG, ha,
		"ha->nx_dev_init_timeout = %d\n", ha->nx_dev_init_समयout));
	DEBUG2(ql4_prपूर्णांकk(KERN_DEBUG, ha,
		"ha->nx_reset_timeout = %d\n", ha->nx_reset_समयout));
	वापस;
पूर्ण

व्योम qla4_82xx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			      पूर्णांक in_count)
अणु
	पूर्णांक i;

	/* Load all mailbox रेजिस्टरs, except mailbox 0. */
	क्रम (i = 1; i < in_count; i++)
		ग_लिखोl(mbx_cmd[i], &ha->qla4_82xx_reg->mailbox_in[i]);

	/* Wakeup firmware  */
	ग_लिखोl(mbx_cmd[0], &ha->qla4_82xx_reg->mailbox_in[0]);
	पढ़ोl(&ha->qla4_82xx_reg->mailbox_in[0]);
	ग_लिखोl(HINT_MBX_INT_PENDING, &ha->qla4_82xx_reg->hपूर्णांक);
	पढ़ोl(&ha->qla4_82xx_reg->hपूर्णांक);
पूर्ण

व्योम qla4_82xx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक out_count)
अणु
	पूर्णांक पूर्णांकr_status;

	पूर्णांकr_status = पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक);
	अगर (पूर्णांकr_status & ISRX_82XX_RISC_INT) अणु
		ha->mbox_status_count = out_count;
		पूर्णांकr_status = पढ़ोl(&ha->qla4_82xx_reg->host_status);
		ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);

		अगर (test_bit(AF_INTERRUPTS_ON, &ha->flags) &&
		    (!ha->pdev->msi_enabled && !ha->pdev->msix_enabled))
			qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg,
					0xfbff);
	पूर्ण
पूर्ण

पूर्णांक
qla4_8xxx_get_flash_info(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t flt_addr;

	ret = qla4_8xxx_find_flt_start(ha, &flt_addr);
	अगर (ret != QLA_SUCCESS)
		वापस ret;

	qla4_8xxx_get_flt_info(ha, flt_addr);
	अगर (is_qla8022(ha)) अणु
		qla4_82xx_get_fdt_info(ha);
		qla4_82xx_get_idc_param(ha);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		qla4_83xx_get_idc_param(ha);
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4_8xxx_stop_firmware - stops firmware on specअगरied adapter instance
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * Remarks:
 * For iSCSI, throws away all I/O and AENs पूर्णांकo bit bucket, so they will
 * not be available after successful वापस.  Driver must cleanup potential
 * outstanding I/O's after calling this funcion.
 **/
पूर्णांक
qla4_8xxx_stop_firmware(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_STOP_FW;
	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1,
	    &mbox_cmd[0], &mbox_sts[0]);

	DEBUG2(prपूर्णांकk("scsi%ld: %s: status = %d\n", ha->host_no,
	    __func__, status));
	वापस status;
पूर्ण

/**
 * qla4_82xx_isp_reset - Resets ISP and पातs all outstanding commands.
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक
qla4_82xx_isp_reset(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t dev_state;

	qla4_82xx_idc_lock(ha);
	dev_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);

	अगर (dev_state == QLA8XXX_DEV_READY) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: NEED RESET\n");
		qla4_82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
		    QLA8XXX_DEV_NEED_RESET);
		set_bit(AF_8XXX_RST_OWNER, &ha->flags);
	पूर्ण अन्यथा
		ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: DEVICE INITIALIZING\n");

	qla4_82xx_idc_unlock(ha);

	rval = qla4_8xxx_device_state_handler(ha);

	qla4_82xx_idc_lock(ha);
	qla4_8xxx_clear_rst_पढ़ोy(ha);
	qla4_82xx_idc_unlock(ha);

	अगर (rval == QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "Clearing AF_RECOVERY in qla4_82xx_isp_reset\n");
		clear_bit(AF_FW_RECOVERY, &ha->flags);
	पूर्ण

	वापस rval;
पूर्ण

/**
 * qla4_8xxx_get_sys_info - get adapter MAC address(es) and serial number
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 **/
पूर्णांक qla4_8xxx_get_sys_info(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा mbx_sys_info *sys_info;
	dma_addr_t sys_info_dma;
	पूर्णांक status = QLA_ERROR;

	sys_info = dma_alloc_coherent(&ha->pdev->dev, माप(*sys_info),
				      &sys_info_dma, GFP_KERNEL);
	अगर (sys_info == शून्य) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Unable to allocate dma buffer.\n",
		    ha->host_no, __func__));
		वापस status;
	पूर्ण

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_SYS_INFO;
	mbox_cmd[1] = LSDW(sys_info_dma);
	mbox_cmd[2] = MSDW(sys_info_dma);
	mbox_cmd[4] = माप(*sys_info);

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 6, &mbox_cmd[0],
	    &mbox_sts[0]) != QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: GET_SYS_INFO failed\n",
		    ha->host_no, __func__));
		जाओ निकास_validate_mac82;
	पूर्ण

	/* Make sure we receive the minimum required data to cache पूर्णांकernally */
	अगर (((is_qla8032(ha) || is_qla8042(ha)) ? mbox_sts[3] : mbox_sts[4]) <
	    दुरत्व(काष्ठा mbx_sys_info, reserved)) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: GET_SYS_INFO data receive"
		    " error (%x)\n", ha->host_no, __func__, mbox_sts[4]));
		जाओ निकास_validate_mac82;
	पूर्ण

	/* Save M.A.C. address & serial_number */
	ha->port_num = sys_info->port_num;
	स_नकल(ha->my_mac, &sys_info->mac_addr[0],
	    min(माप(ha->my_mac), माप(sys_info->mac_addr)));
	स_नकल(ha->serial_number, &sys_info->serial_number,
	    min(माप(ha->serial_number), माप(sys_info->serial_number)));
	स_नकल(ha->model_name, &sys_info->board_id_str,
	       min(माप(ha->model_name), माप(sys_info->board_id_str)));
	ha->phy_port_cnt = sys_info->phys_port_cnt;
	ha->phy_port_num = sys_info->port_num;
	ha->iscsi_pci_func_cnt = sys_info->iscsi_pci_func_cnt;

	DEBUG2(prपूर्णांकk("scsi%ld: %s: mac %pM serial %s\n",
	    ha->host_no, __func__, ha->my_mac, ha->serial_number));

	status = QLA_SUCCESS;

निकास_validate_mac82:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(*sys_info), sys_info,
			  sys_info_dma);
	वापस status;
पूर्ण

/* Interrupt handling helpers. */

पूर्णांक qla4_8xxx_पूर्णांकr_enable(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s\n", __func__));

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	mbox_cmd[0] = MBOX_CMD_ENABLE_INTRS;
	mbox_cmd[1] = INTR_ENABLE;
	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
		&mbox_sts[0]) != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "%s: MBOX_CMD_ENABLE_INTRS failed (0x%04x)\n",
		    __func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक qla4_8xxx_पूर्णांकr_disable(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s\n", __func__));

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	mbox_cmd[0] = MBOX_CMD_ENABLE_INTRS;
	mbox_cmd[1] = INTR_DISABLE;
	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
	    &mbox_sts[0]) != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			"%s: MBOX_CMD_ENABLE_INTRS failed (0x%04x)\n",
			__func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

व्योम
qla4_82xx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	qla4_8xxx_पूर्णांकr_enable(ha);

	spin_lock_irq(&ha->hardware_lock);
	/* BIT 10 - reset */
	qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0xfbff);
	spin_unlock_irq(&ha->hardware_lock);
	set_bit(AF_INTERRUPTS_ON, &ha->flags);
पूर्ण

व्योम
qla4_82xx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (test_and_clear_bit(AF_INTERRUPTS_ON, &ha->flags))
		qla4_8xxx_पूर्णांकr_disable(ha);

	spin_lock_irq(&ha->hardware_lock);
	/* BIT 10 - set */
	qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0x0400);
	spin_unlock_irq(&ha->hardware_lock);
पूर्ण

पूर्णांक
qla4_8xxx_enable_msix(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(ha->pdev, QLA_MSIX_ENTRIES,
			QLA_MSIX_ENTRIES, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "MSI-X: Failed to enable support -- %d/%d\n",
		    QLA_MSIX_ENTRIES, ret);
		वापस ret;
	पूर्ण

	ret = request_irq(pci_irq_vector(ha->pdev, 0),
			qla4_8xxx_शेष_पूर्णांकr_handler, 0, "qla4xxx (default)",
			ha);
	अगर (ret)
		जाओ out_मुक्त_vectors;

	ret = request_irq(pci_irq_vector(ha->pdev, 1),
			qla4_8xxx_msix_rsp_q, 0, "qla4xxx (rsp_q)", ha);
	अगर (ret)
		जाओ out_मुक्त_शेष_irq;

	वापस 0;

out_मुक्त_शेष_irq:
	मुक्त_irq(pci_irq_vector(ha->pdev, 0), ha);
out_मुक्त_vectors:
	pci_मुक्त_irq_vectors(ha->pdev);
	वापस ret;
पूर्ण

पूर्णांक qla4_8xxx_check_init_adapter_retry(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status = QLA_SUCCESS;

	/* Dont retry adapter initialization अगर IRQ allocation failed */
	अगर (!test_bit(AF_IRQ_ATTACHED, &ha->flags)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: Skipping retry of adapter initialization as IRQs are not attached\n",
			   __func__);
		status = QLA_ERROR;
		जाओ निकास_init_adapter_failure;
	पूर्ण

	/* Since पूर्णांकerrupts are रेजिस्टरed in start_firmware क्रम
	 * 8xxx, release them here अगर initialize_adapter fails
	 * and retry adapter initialization */
	qla4xxx_मुक्त_irqs(ha);

निकास_init_adapter_failure:
	वापस status;
पूर्ण
