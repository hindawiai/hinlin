<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश <linux/delay.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/pci.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <scsi/scsi_tcq.h>

#घोषणा MASK(n)			((1ULL<<(n))-1)
#घोषणा MN_WIN(addr) (((addr & 0x1fc0000) >> 1) | \
	((addr >> 25) & 0x3ff))
#घोषणा OCM_WIN(addr) (((addr & 0x1ff0000) >> 1) | \
	((addr >> 25) & 0x3ff))
#घोषणा MS_WIN(addr) (addr & 0x0ffc0000)
#घोषणा QLA82XX_PCI_MN_2M   (0)
#घोषणा QLA82XX_PCI_MS_2M   (0x80000)
#घोषणा QLA82XX_PCI_OCM0_2M (0xc0000)
#घोषणा VALID_OCM_ADDR(addr) (((addr) & 0x3f800) != 0x3f800)
#घोषणा GET_MEM_OFFS_2M(addr) (addr & MASK(18))
#घोषणा BLOCK_PROTECT_BITS 0x0F

/* CRB winकरोw related */
#घोषणा CRB_BLK(off)	((off >> 20) & 0x3f)
#घोषणा CRB_SUBBLK(off)	((off >> 16) & 0xf)
#घोषणा CRB_WINDOW_2M	(0x130060)
#घोषणा QLA82XX_PCI_CAMQM_2M_END	(0x04800800UL)
#घोषणा CRB_HI(off)	((qla82xx_crb_hub_agt[CRB_BLK(off)] << 20) | \
			((off) & 0xf0000))
#घोषणा QLA82XX_PCI_CAMQM_2M_BASE	(0x000ff800UL)
#घोषणा CRB_INसूचीECT_2M	(0x1e0000UL)

#घोषणा MAX_CRB_XFORM 60
अटल अचिन्हित दीर्घ crb_addr_xक्रमm[MAX_CRB_XFORM];
अटल पूर्णांक qla82xx_crb_table_initialized;

#घोषणा qla82xx_crb_addr_transक्रमm(name) \
	(crb_addr_xक्रमm[QLA82XX_HW_PX_MAP_CRB_##name] = \
	QLA82XX_HW_CRB_HUB_AGT_ADR_##name << 20)

स्थिर पूर्णांक MD_MIU_TEST_AGT_RDDATA[] = अणु
	0x410000A8, 0x410000AC,
	0x410000B8, 0x410000BC
पूर्ण;

अटल व्योम qla82xx_crb_addr_transक्रमm_setup(व्योम)
अणु
	qla82xx_crb_addr_transक्रमm(XDMA);
	qla82xx_crb_addr_transक्रमm(TIMR);
	qla82xx_crb_addr_transक्रमm(SRE);
	qla82xx_crb_addr_transक्रमm(SQN3);
	qla82xx_crb_addr_transक्रमm(SQN2);
	qla82xx_crb_addr_transक्रमm(SQN1);
	qla82xx_crb_addr_transक्रमm(SQN0);
	qla82xx_crb_addr_transक्रमm(SQS3);
	qla82xx_crb_addr_transक्रमm(SQS2);
	qla82xx_crb_addr_transक्रमm(SQS1);
	qla82xx_crb_addr_transक्रमm(SQS0);
	qla82xx_crb_addr_transक्रमm(RPMX7);
	qla82xx_crb_addr_transक्रमm(RPMX6);
	qla82xx_crb_addr_transक्रमm(RPMX5);
	qla82xx_crb_addr_transक्रमm(RPMX4);
	qla82xx_crb_addr_transक्रमm(RPMX3);
	qla82xx_crb_addr_transक्रमm(RPMX2);
	qla82xx_crb_addr_transक्रमm(RPMX1);
	qla82xx_crb_addr_transक्रमm(RPMX0);
	qla82xx_crb_addr_transक्रमm(ROMUSB);
	qla82xx_crb_addr_transक्रमm(SN);
	qla82xx_crb_addr_transक्रमm(QMN);
	qla82xx_crb_addr_transक्रमm(QMS);
	qla82xx_crb_addr_transक्रमm(PGNI);
	qla82xx_crb_addr_transक्रमm(PGND);
	qla82xx_crb_addr_transक्रमm(PGN3);
	qla82xx_crb_addr_transक्रमm(PGN2);
	qla82xx_crb_addr_transक्रमm(PGN1);
	qla82xx_crb_addr_transक्रमm(PGN0);
	qla82xx_crb_addr_transक्रमm(PGSI);
	qla82xx_crb_addr_transक्रमm(PGSD);
	qla82xx_crb_addr_transक्रमm(PGS3);
	qla82xx_crb_addr_transक्रमm(PGS2);
	qla82xx_crb_addr_transक्रमm(PGS1);
	qla82xx_crb_addr_transक्रमm(PGS0);
	qla82xx_crb_addr_transक्रमm(PS);
	qla82xx_crb_addr_transक्रमm(PH);
	qla82xx_crb_addr_transक्रमm(NIU);
	qla82xx_crb_addr_transक्रमm(I2Q);
	qla82xx_crb_addr_transक्रमm(EG);
	qla82xx_crb_addr_transक्रमm(MN);
	qla82xx_crb_addr_transक्रमm(MS);
	qla82xx_crb_addr_transक्रमm(CAS2);
	qla82xx_crb_addr_transक्रमm(CAS1);
	qla82xx_crb_addr_transक्रमm(CAS0);
	qla82xx_crb_addr_transक्रमm(CAM);
	qla82xx_crb_addr_transक्रमm(C2C1);
	qla82xx_crb_addr_transक्रमm(C2C0);
	qla82xx_crb_addr_transक्रमm(SMB);
	qla82xx_crb_addr_transक्रमm(OCM0);
	/*
	 * Used only in P3 just define it क्रम P2 also.
	 */
	qla82xx_crb_addr_transक्रमm(I2C0);

	qla82xx_crb_table_initialized = 1;
पूर्ण

अटल काष्ठा crb_128M_2M_block_map crb_128M_2M_map[64] = अणु
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0100000, 0x0102000, 0x120000पूर्ण,
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
	अणु0, 0x0000000, 0x0000000, 0x000000पूर्ण पूर्ण पूर्ण ,
	अणुअणुअणु1, 0x0200000, 0x0210000, 0x180000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0400000, 0x0401000, 0x169000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0500000, 0x0510000, 0x140000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0600000, 0x0610000, 0x1c0000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0700000, 0x0704000, 0x1b8000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0800000, 0x0802000, 0x170000पूर्ण,
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
	अणुअणुअणु1, 0x0900000, 0x0902000, 0x174000पूर्ण,
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
	अणुअणुअणु0, 0x0a00000, 0x0a02000, 0x178000पूर्ण,
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
	अणुअणुअणु0, 0x0b00000, 0x0b02000, 0x17c000पूर्ण,
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
	अणुअणुअणु1, 0x0c00000, 0x0c04000, 0x1d4000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0d00000, 0x0d04000, 0x1a4000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0e00000, 0x0e04000, 0x1a0000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x0f00000, 0x0f01000, 0x164000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0x1000000, 0x1004000, 0x1a8000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1100000, 0x1101000, 0x160000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1200000, 0x1201000, 0x161000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1300000, 0x1301000, 0x162000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1400000, 0x1401000, 0x163000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1500000, 0x1501000, 0x165000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1600000, 0x1601000, 0x166000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0,         0,         0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1d00000, 0x1d10000, 0x190000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1e00000, 0x1e01000, 0x16a000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x1f00000, 0x1f10000, 0x150000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2100000, 0x2102000, 0x120000पूर्ण,
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
	अणुअणुअणु1, 0x2200000, 0x2204000, 0x1b0000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2800000, 0x2804000, 0x1a4000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2900000, 0x2901000, 0x16b000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2a00000, 0x2a00400, 0x1ac400पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2b00000, 0x2b00400, 0x1ac800पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2c00000, 0x2c00400, 0x1acc00पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2d00000, 0x2d00400, 0x1ad000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2e00000, 0x2e00400, 0x1ad400पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x2f00000, 0x2f00400, 0x1ad800पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3000000, 0x3000400, 0x1adc00पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0, 0x3100000, 0x3104000, 0x1a8000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3200000, 0x3204000, 0x1d4000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3300000, 0x3304000, 0x1a0000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3500000, 0x3500400, 0x1ac000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3600000, 0x3600400, 0x1ae000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3700000, 0x3700400, 0x1ae400पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3800000, 0x3804000, 0x1d0000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3900000, 0x3904000, 0x1b4000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3a00000, 0x3a04000, 0x1d8000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु0पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3d00000, 0x3d04000, 0x1dc000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3e00000, 0x3e01000, 0x167000पूर्ण पूर्ण पूर्ण,
	अणुअणुअणु1, 0x3f00000, 0x3f01000, 0x168000पूर्ण पूर्ण पूर्ण
पूर्ण;

/*
 * top 12 bits of crb पूर्णांकernal address (hub, agent)
 */
अटल अचिन्हित qla82xx_crb_hub_agt[64] = अणु
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
अटल अक्षर *q_dev_state[] = अणु
	 "Unknown",
	"Cold",
	"Initializing",
	"Ready",
	"Need Reset",
	"Need Quiescent",
	"Failed",
	"Quiescent",
पूर्ण;

अक्षर *qdev_state(uपूर्णांक32_t dev_state)
अणु
	वापस q_dev_state[dev_state];
पूर्ण

/*
 * In: 'off_in' is offset from CRB space in 128M pci map
 * Out: 'off_out' is 2M pci map addr
 * side effect: lock crb winकरोw
 */
अटल व्योम
qla82xx_pci_set_crbwinकरोw_2M(काष्ठा qla_hw_data *ha, uदीर्घ off_in,
			     व्योम __iomem **off_out)
अणु
	u32 win_पढ़ो;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ha->crb_win = CRB_HI(off_in);
	ग_लिखोl(ha->crb_win, CRB_WINDOW_2M + ha->nx_pcibase);

	/* Read back value to make sure ग_लिखो has gone through beक्रमe trying
	 * to use it.
	 */
	win_पढ़ो = rd_reg_dword(CRB_WINDOW_2M + ha->nx_pcibase);
	अगर (win_पढ़ो != ha->crb_win) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb000,
		    "%s: Written crbwin (0x%x) "
		    "!= Read crbwin (0x%x), off=0x%lx.\n",
		    __func__, ha->crb_win, win_पढ़ो, off_in);
	पूर्ण
	*off_out = (off_in & MASK(16)) + CRB_INसूचीECT_2M + ha->nx_pcibase;
पूर्ण

अटल पूर्णांक
qla82xx_pci_get_crb_addr_2M(काष्ठा qla_hw_data *ha, uदीर्घ off_in,
			    व्योम __iomem **off_out)
अणु
	काष्ठा crb_128M_2M_sub_block_map *m;

	अगर (off_in >= QLA82XX_CRB_MAX)
		वापस -1;

	अगर (off_in >= QLA82XX_PCI_CAMQM && off_in < QLA82XX_PCI_CAMQM_2M_END) अणु
		*off_out = (off_in - QLA82XX_PCI_CAMQM) +
		    QLA82XX_PCI_CAMQM_2M_BASE + ha->nx_pcibase;
		वापस 0;
	पूर्ण

	अगर (off_in < QLA82XX_PCI_CRBSPACE)
		वापस -1;

	off_in -= QLA82XX_PCI_CRBSPACE;

	/* Try direct map */
	m = &crb_128M_2M_map[CRB_BLK(off_in)].sub_block[CRB_SUBBLK(off_in)];

	अगर (m->valid && (m->start_128M <= off_in) && (m->end_128M > off_in)) अणु
		*off_out = off_in + m->start_2M - m->start_128M + ha->nx_pcibase;
		वापस 0;
	पूर्ण
	/* Not in direct map, use crb winकरोw */
	*off_out = (व्योम __iomem *)off_in;
	वापस 1;
पूर्ण

#घोषणा CRB_WIN_LOCK_TIMEOUT 100000000
अटल पूर्णांक qla82xx_crb_win_lock(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक करोne = 0, समयout = 0;

	जबतक (!करोne) अणु
		/* acquire semaphore3 from PCI HW block */
		करोne = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (समयout >= CRB_WIN_LOCK_TIMEOUT)
			वापस -1;
		समयout++;
	पूर्ण
	qla82xx_wr_32(ha, QLA82XX_CRB_WIN_LOCK_ID, ha->portnum);
	वापस 0;
पूर्ण

पूर्णांक
qla82xx_wr_32(काष्ठा qla_hw_data *ha, uदीर्घ off_in, u32 data)
अणु
	व्योम __iomem *off;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rv;

	rv = qla82xx_pci_get_crb_addr_2M(ha, off_in, &off);

	BUG_ON(rv == -1);

	अगर (rv == 1) अणु
#अगर_अघोषित __CHECKER__
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
#पूर्ण_अगर
		qla82xx_crb_win_lock(ha);
		qla82xx_pci_set_crbwinकरोw_2M(ha, off_in, &off);
	पूर्ण

	ग_लिखोl(data, (व्योम __iomem *)off);

	अगर (rv == 1) अणु
		qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_UNLOCK));
#अगर_अघोषित __CHECKER__
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
qla82xx_rd_32(काष्ठा qla_hw_data *ha, uदीर्घ off_in)
अणु
	व्योम __iomem *off;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rv;
	u32 data;

	rv = qla82xx_pci_get_crb_addr_2M(ha, off_in, &off);

	BUG_ON(rv == -1);

	अगर (rv == 1) अणु
#अगर_अघोषित __CHECKER__
		ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
#पूर्ण_अगर
		qla82xx_crb_win_lock(ha);
		qla82xx_pci_set_crbwinकरोw_2M(ha, off_in, &off);
	पूर्ण
	data = rd_reg_dword(off);

	अगर (rv == 1) अणु
		qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_UNLOCK));
#अगर_अघोषित __CHECKER__
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
#पूर्ण_अगर
	पूर्ण
	वापस data;
पूर्ण

/*
 * Context: task, might sleep
 */
पूर्णांक qla82xx_idc_lock(काष्ठा qla_hw_data *ha)
अणु
	स्थिर पूर्णांक delay_ms = 100, समयout_ms = 2000;
	पूर्णांक करोne, total = 0;

	might_sleep();

	जबतक (true) अणु
		/* acquire semaphore5 from PCI HW block */
		करोne = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM5_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (WARN_ON_ONCE(total >= समयout_ms))
			वापस -1;

		total += delay_ms;
		msleep(delay_ms);
	पूर्ण

	वापस 0;
पूर्ण

व्योम qla82xx_idc_unlock(काष्ठा qla_hw_data *ha)
अणु
	qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM5_UNLOCK));
पूर्ण

/*
 * check memory access boundary.
 * used by test agent. support ddr access only क्रम now
 */
अटल अचिन्हित दीर्घ
qla82xx_pci_mem_bound_check(काष्ठा qla_hw_data *ha,
	अचिन्हित दीर्घ दीर्घ addr, पूर्णांक size)
अणु
	अगर (!addr_in_range(addr, QLA82XX_ADDR_DDR_NET,
		QLA82XX_ADDR_DDR_NET_MAX) ||
		!addr_in_range(addr + size - 1, QLA82XX_ADDR_DDR_NET,
		QLA82XX_ADDR_DDR_NET_MAX) ||
		((size != 1) && (size != 2) && (size != 4) && (size != 8)))
			वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक qla82xx_pci_set_winकरोw_warning_count;

अटल अचिन्हित दीर्घ
qla82xx_pci_set_winकरोw(काष्ठा qla_hw_data *ha, अचिन्हित दीर्घ दीर्घ addr)
अणु
	पूर्णांक winकरोw;
	u32 win_पढ़ो;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	अगर (addr_in_range(addr, QLA82XX_ADDR_DDR_NET,
		QLA82XX_ADDR_DDR_NET_MAX)) अणु
		/* DDR network side */
		winकरोw = MN_WIN(addr);
		ha->ddr_mn_winकरोw = winकरोw;
		qla82xx_wr_32(ha,
			ha->mn_win_crb | QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla82xx_rd_32(ha,
			ha->mn_win_crb | QLA82XX_PCI_CRBSPACE);
		अगर ((win_पढ़ो << 17) != winकरोw) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb003,
			    "%s: Written MNwin (0x%x) != Read MNwin (0x%x).\n",
			    __func__, winकरोw, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_DDR_NET;
	पूर्ण अन्यथा अगर (addr_in_range(addr, QLA82XX_ADDR_OCM0,
		QLA82XX_ADDR_OCM0_MAX)) अणु
		अचिन्हित पूर्णांक temp1;

		अगर ((addr & 0x00ff800) == 0xff800) अणु
			ql_log(ql_log_warn, vha, 0xb004,
			    "%s: QM access not handled.\n", __func__);
			addr = -1UL;
		पूर्ण
		winकरोw = OCM_WIN(addr);
		ha->ddr_mn_winकरोw = winकरोw;
		qla82xx_wr_32(ha,
			ha->mn_win_crb | QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla82xx_rd_32(ha,
			ha->mn_win_crb | QLA82XX_PCI_CRBSPACE);
		temp1 = ((winकरोw & 0x1FF) << 7) |
		    ((winकरोw & 0x0FFFE0000) >> 17);
		अगर (win_पढ़ो != temp1) अणु
			ql_log(ql_log_warn, vha, 0xb005,
			    "%s: Written OCMwin (0x%x) != Read OCMwin (0x%x).\n",
			    __func__, temp1, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_OCM0_2M;

	पूर्ण अन्यथा अगर (addr_in_range(addr, QLA82XX_ADDR_QDR_NET,
		QLA82XX_P3_ADDR_QDR_NET_MAX)) अणु
		/* QDR network side */
		winकरोw = MS_WIN(addr);
		ha->qdr_sn_winकरोw = winकरोw;
		qla82xx_wr_32(ha,
			ha->ms_win_crb | QLA82XX_PCI_CRBSPACE, winकरोw);
		win_पढ़ो = qla82xx_rd_32(ha,
			ha->ms_win_crb | QLA82XX_PCI_CRBSPACE);
		अगर (win_पढ़ो != winकरोw) अणु
			ql_log(ql_log_warn, vha, 0xb006,
			    "%s: Written MSwin (0x%x) != Read MSwin (0x%x).\n",
			    __func__, winकरोw, win_पढ़ो);
		पूर्ण
		addr = GET_MEM_OFFS_2M(addr) + QLA82XX_PCI_QDR_NET;
	पूर्ण अन्यथा अणु
		/*
		 * peg gdb frequently accesses memory that करोesn't exist,
		 * this limits the chit chat so debugging isn't slowed करोwn.
		 */
		अगर ((qla82xx_pci_set_winकरोw_warning_count++ < 8) ||
		    (qla82xx_pci_set_winकरोw_warning_count%64 == 0)) अणु
			ql_log(ql_log_warn, vha, 0xb007,
			    "%s: Warning:%s Unknown address range!.\n",
			    __func__, QLA2XXX_DRIVER_NAME);
		पूर्ण
		addr = -1UL;
	पूर्ण
	वापस addr;
पूर्ण

/* check अगर address is in the same winकरोws as the previous access */
अटल पूर्णांक qla82xx_pci_is_same_winकरोw(काष्ठा qla_hw_data *ha,
	अचिन्हित दीर्घ दीर्घ addr)
अणु
	पूर्णांक			winकरोw;
	अचिन्हित दीर्घ दीर्घ	qdr_max;

	qdr_max = QLA82XX_P3_ADDR_QDR_NET_MAX;

	/* DDR network side */
	अगर (addr_in_range(addr, QLA82XX_ADDR_DDR_NET,
		QLA82XX_ADDR_DDR_NET_MAX))
		BUG();
	अन्यथा अगर (addr_in_range(addr, QLA82XX_ADDR_OCM0,
		QLA82XX_ADDR_OCM0_MAX))
		वापस 1;
	अन्यथा अगर (addr_in_range(addr, QLA82XX_ADDR_OCM1,
		QLA82XX_ADDR_OCM1_MAX))
		वापस 1;
	अन्यथा अगर (addr_in_range(addr, QLA82XX_ADDR_QDR_NET, qdr_max)) अणु
		/* QDR network side */
		winकरोw = ((addr - QLA82XX_ADDR_QDR_NET) >> 22) & 0x3f;
		अगर (ha->qdr_sn_winकरोw == winकरोw)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qla82xx_pci_mem_पढ़ो_direct(काष्ठा qla_hw_data *ha,
	u64 off, व्योम *data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ   flags;
	व्योम __iomem *addr = शून्य;
	पूर्णांक             ret = 0;
	u64             start;
	uपूर्णांक8_t __iomem  *mem_ptr = शून्य;
	अचिन्हित दीर्घ   mem_base;
	अचिन्हित दीर्घ   mem_page;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/*
	 * If attempting to access unknown address or straddle hw winकरोws,
	 * करो not access.
	 */
	start = qla82xx_pci_set_winकरोw(ha, off);
	अगर ((start == -1UL) ||
		(qla82xx_pci_is_same_winकरोw(ha, off + size - 1) == 0)) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		ql_log(ql_log_fatal, vha, 0xb008,
		    "%s out of bound pci memory "
		    "access, offset is 0x%llx.\n",
		    QLA2XXX_DRIVER_NAME, off);
		वापस -1;
	पूर्ण

	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	mem_base = pci_resource_start(ha->pdev, 0);
	mem_page = start & PAGE_MASK;
	/* Map two pages whenever user tries to access addresses in two
	* consecutive pages.
	*/
	अगर (mem_page != ((start + size - 1) & PAGE_MASK))
		mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE * 2);
	अन्यथा
		mem_ptr = ioremap(mem_base + mem_page, PAGE_SIZE);
	अगर (mem_ptr == शून्य) अणु
		*(u8  *)data = 0;
		वापस -1;
	पूर्ण
	addr = mem_ptr;
	addr += start & (PAGE_SIZE - 1);
	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

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
qla82xx_pci_mem_ग_लिखो_direct(काष्ठा qla_hw_data *ha,
	u64 off, व्योम *data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ   flags;
	व्योम  __iomem *addr = शून्य;
	पूर्णांक             ret = 0;
	u64             start;
	uपूर्णांक8_t __iomem *mem_ptr = शून्य;
	अचिन्हित दीर्घ   mem_base;
	अचिन्हित दीर्घ   mem_page;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);

	/*
	 * If attempting to access unknown address or straddle hw winकरोws,
	 * करो not access.
	 */
	start = qla82xx_pci_set_winकरोw(ha, off);
	अगर ((start == -1UL) ||
		(qla82xx_pci_is_same_winकरोw(ha, off + size - 1) == 0)) अणु
		ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
		ql_log(ql_log_fatal, vha, 0xb009,
		    "%s out of bound memory "
		    "access, offset is 0x%llx.\n",
		    QLA2XXX_DRIVER_NAME, off);
		वापस -1;
	पूर्ण

	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	mem_base = pci_resource_start(ha->pdev, 0);
	mem_page = start & PAGE_MASK;
	/* Map two pages whenever user tries to access addresses in two
	 * consecutive pages.
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

	चयन (size) अणु
	हाल 1:
		ग_लिखोb(*(u8  *)data, addr);
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
qla82xx_decode_crb_addr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ base_addr, offset, pci_base;

	अगर (!qla82xx_crb_table_initialized)
		qla82xx_crb_addr_transक्रमm_setup();

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
	वापस pci_base + offset;
पूर्ण

अटल दीर्घ rom_max_समयout = 100;
अटल दीर्घ qla82xx_rom_lock_समयout = 100;

अटल पूर्णांक
qla82xx_rom_lock(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक करोne = 0, समयout = 0;
	uपूर्णांक32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक (!करोne) अणु
		/* acquire semaphore2 from PCI HW block */
		करोne = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_LOCK));
		अगर (करोne == 1)
			अवरोध;
		अगर (समयout >= qla82xx_rom_lock_समयout) अणु
			lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
			ql_dbg(ql_dbg_p3p, vha, 0xb157,
			    "%s: Simultaneous flash access by following ports, active port = %d: accessing port = %d",
			    __func__, ha->portnum, lock_owner);
			वापस -1;
		पूर्ण
		समयout++;
	पूर्ण
	qla82xx_wr_32(ha, QLA82XX_ROM_LOCK_ID, ha->portnum);
	वापस 0;
पूर्ण

अटल व्योम
qla82xx_rom_unlock(काष्ठा qla_hw_data *ha)
अणु
	qla82xx_wr_32(ha, QLA82XX_ROM_LOCK_ID, 0xffffffff);
	qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_UNLOCK));
पूर्ण

अटल पूर्णांक
qla82xx_रुको_rom_busy(काष्ठा qla_hw_data *ha)
अणु
	दीर्घ समयout = 0;
	दीर्घ करोne = 0 ;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक (करोne == 0) अणु
		करोne = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_STATUS);
		करोne &= 4;
		समयout++;
		अगर (समयout >= rom_max_समयout) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb00a,
			    "%s: Timeout reached waiting for rom busy.\n",
			    QLA2XXX_DRIVER_NAME);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_रुको_rom_करोne(काष्ठा qla_hw_data *ha)
अणु
	दीर्घ समयout = 0;
	दीर्घ करोne = 0 ;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक (करोne == 0) अणु
		करोne = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_STATUS);
		करोne &= 2;
		समयout++;
		अगर (समयout >= rom_max_समयout) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb00b,
			    "%s: Timeout reached waiting for rom done.\n",
			    QLA2XXX_DRIVER_NAME);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_md_rw_32(काष्ठा qla_hw_data *ha, uपूर्णांक32_t off, u32 data, uपूर्णांक8_t flag)
अणु
	uपूर्णांक32_t  off_value, rval = 0;

	wrt_reg_dword(CRB_WINDOW_2M + ha->nx_pcibase, off & 0xFFFF0000);

	/* Read back value to make sure ग_लिखो has gone through */
	rd_reg_dword(CRB_WINDOW_2M + ha->nx_pcibase);
	off_value  = (off & 0x0000FFFF);

	अगर (flag)
		wrt_reg_dword(off_value + CRB_INसूचीECT_2M + ha->nx_pcibase,
			      data);
	अन्यथा
		rval = rd_reg_dword(off_value + CRB_INसूचीECT_2M +
				    ha->nx_pcibase);

	वापस rval;
पूर्ण

अटल पूर्णांक
qla82xx_करो_rom_fast_पढ़ो(काष्ठा qla_hw_data *ha, पूर्णांक addr, पूर्णांक *valp)
अणु
	/* Dword पढ़ोs to flash. */
	qla82xx_md_rw_32(ha, MD_सूचीECT_ROM_WINDOW, (addr & 0xFFFF0000), 1);
	*valp = qla82xx_md_rw_32(ha, MD_सूचीECT_ROM_READ_BASE +
	    (addr & 0x0000FFFF), 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_rom_fast_पढ़ो(काष्ठा qla_hw_data *ha, पूर्णांक addr, पूर्णांक *valp)
अणु
	पूर्णांक ret, loops = 0;
	uपूर्णांक32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक ((qla82xx_rom_lock(ha) != 0) && (loops < 50000)) अणु
		udelay(100);
		schedule();
		loops++;
	पूर्ण
	अगर (loops >= 50000) अणु
		lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
		ql_log(ql_log_fatal, vha, 0x00b9,
		    "Failed to acquire SEM2 lock, Lock Owner %u.\n",
		    lock_owner);
		वापस -1;
	पूर्ण
	ret = qla82xx_करो_rom_fast_पढ़ो(ha, addr, valp);
	qla82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

अटल पूर्णांक
qla82xx_पढ़ो_status_reg(काष्ठा qla_hw_data *ha, uपूर्णांक32_t *val)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_RDSR);
	qla82xx_रुको_rom_busy(ha);
	अगर (qla82xx_रुको_rom_करोne(ha)) अणु
		ql_log(ql_log_warn, vha, 0xb00c,
		    "Error waiting for rom done.\n");
		वापस -1;
	पूर्ण
	*val = qla82xx_rd_32(ha, QLA82XX_ROMUSB_ROM_RDATA);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_flash_रुको_ग_लिखो_finish(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t val = 0;
	पूर्णांक i, ret;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);
	क्रम (i = 0; i < 50000; i++) अणु
		ret = qla82xx_पढ़ो_status_reg(ha, &val);
		अगर (ret < 0 || (val & 1) == 0)
			वापस ret;
		udelay(10);
		cond_resched();
	पूर्ण
	ql_log(ql_log_warn, vha, 0xb00d,
	       "Timeout reached waiting for write finish.\n");
	वापस -1;
पूर्ण

अटल पूर्णांक
qla82xx_flash_set_ग_लिखो_enable(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t val;

	qla82xx_रुको_rom_busy(ha);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_WREN);
	qla82xx_रुको_rom_busy(ha);
	अगर (qla82xx_रुको_rom_करोne(ha))
		वापस -1;
	अगर (qla82xx_पढ़ो_status_reg(ha, &val) != 0)
		वापस -1;
	अगर ((val & 2) != 2)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_ग_लिखो_status_reg(काष्ठा qla_hw_data *ha, uपूर्णांक32_t val)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	अगर (qla82xx_flash_set_ग_लिखो_enable(ha))
		वापस -1;
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_WDATA, val);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, 0x1);
	अगर (qla82xx_रुको_rom_करोne(ha)) अणु
		ql_log(ql_log_warn, vha, 0xb00e,
		    "Error waiting for rom done.\n");
		वापस -1;
	पूर्ण
	वापस qla82xx_flash_रुको_ग_लिखो_finish(ha);
पूर्ण

अटल पूर्णांक
qla82xx_ग_लिखो_disable_flash(काष्ठा qla_hw_data *ha)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_WRDI);
	अगर (qla82xx_रुको_rom_करोne(ha)) अणु
		ql_log(ql_log_warn, vha, 0xb00f,
		    "Error waiting for rom done.\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
ql82xx_rom_lock_d(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक loops = 0;
	uपूर्णांक32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	जबतक ((qla82xx_rom_lock(ha) != 0) && (loops < 50000)) अणु
		udelay(100);
		cond_resched();
		loops++;
	पूर्ण
	अगर (loops >= 50000) अणु
		lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
		ql_log(ql_log_warn, vha, 0xb010,
		    "ROM lock failed, Lock Owner %u.\n", lock_owner);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_ग_लिखो_flash_dword(काष्ठा qla_hw_data *ha, uपूर्णांक32_t flashaddr,
	uपूर्णांक32_t data)
अणु
	पूर्णांक ret = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	अगर (ret < 0) अणु
		ql_log(ql_log_warn, vha, 0xb011,
		    "ROM lock failed.\n");
		वापस ret;
	पूर्ण

	ret = qla82xx_flash_set_ग_लिखो_enable(ha);
	अगर (ret < 0)
		जाओ करोne_ग_लिखो;

	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_WDATA, data);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ADDRESS, flashaddr);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 3);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_PP);
	qla82xx_रुको_rom_busy(ha);
	अगर (qla82xx_रुको_rom_करोne(ha)) अणु
		ql_log(ql_log_warn, vha, 0xb012,
		    "Error waiting for rom done.\n");
		ret = -1;
		जाओ करोne_ग_लिखो;
	पूर्ण

	ret = qla82xx_flash_रुको_ग_लिखो_finish(ha);

करोne_ग_लिखो:
	qla82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

/* This routine करोes CRB initialize sequence
 *  to put the ISP पूर्णांकo operational state
 */
अटल पूर्णांक
qla82xx_pinit_from_rom(scsi_qla_host_t *vha)
अणु
	पूर्णांक addr, val;
	पूर्णांक i ;
	काष्ठा crb_addr_pair *buf;
	अचिन्हित दीर्घ off;
	अचिन्हित offset, n;
	काष्ठा qla_hw_data *ha = vha->hw;

	काष्ठा crb_addr_pair अणु
		दीर्घ addr;
		दीर्घ data;
	पूर्ण;

	/* Halt all the inभागidual PEGs and other blocks of the ISP */
	qla82xx_rom_lock(ha);

	/* disable all I2Q */
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x10, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x14, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x18, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x1c, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x20, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x24, 0x0);

	/* disable all niu पूर्णांकerrupts */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x40, 0xff);
	/* disable xge rx/tx */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x70000, 0x00);
	/* disable xg1 rx/tx */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x80000, 0x00);
	/* disable sideband mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x90000, 0x00);
	/* disable ap0 mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xa0000, 0x00);
	/* disable ap1 mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xb0000, 0x00);

	/* halt sre */
	val = qla82xx_rd_32(ha, QLA82XX_CRB_SRE + 0x1000);
	qla82xx_wr_32(ha, QLA82XX_CRB_SRE + 0x1000, val & (~(0x1)));

	/* halt epg */
	qla82xx_wr_32(ha, QLA82XX_CRB_EPG + 0x1300, 0x1);

	/* halt समयrs */
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x0, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x8, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x10, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x18, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x100, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x200, 0x0);

	/* halt pegs */
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_4 + 0x3c, 1);
	msleep(20);

	/* big hammer */
	अगर (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
		/* करोn't reset CAM block on reset */
		qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xfeffffff);
	अन्यथा
		qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xffffffff);
	qla82xx_rom_unlock(ha);

	/* Read the signature value from the flash.
	 * Offset 0: Contain signature (0xcafecafe)
	 * Offset 4: Offset and number of addr/value pairs
	 * that present in CRB initialize sequence
	 */
	n = 0;
	अगर (qla82xx_rom_fast_पढ़ो(ha, 0, &n) != 0 || n != 0xcafecafeUL ||
	    qla82xx_rom_fast_पढ़ो(ha, 4, &n) != 0) अणु
		ql_log(ql_log_fatal, vha, 0x006e,
		    "Error Reading crb_init area: n: %08x.\n", n);
		वापस -1;
	पूर्ण

	/* Offset in flash = lower 16 bits
	 * Number of entries = upper 16 bits
	 */
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	/* number of addr/value pair should not exceed 1024 entries */
	अगर (n  >= 1024) अणु
		ql_log(ql_log_fatal, vha, 0x0071,
		    "Card flash not initialized:n=0x%x.\n", n);
		वापस -1;
	पूर्ण

	ql_log(ql_log_info, vha, 0x0072,
	    "%d CRB init values found in ROM.\n", n);

	buf = kदो_स्मृति_array(n, माप(काष्ठा crb_addr_pair), GFP_KERNEL);
	अगर (buf == शून्य) अणु
		ql_log(ql_log_fatal, vha, 0x010c,
		    "Unable to allocate memory.\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		अगर (qla82xx_rom_fast_पढ़ो(ha, 8*i + 4*offset, &val) != 0 ||
		    qla82xx_rom_fast_पढ़ो(ha, 8*i + 4*offset + 4, &addr) != 0) अणु
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
		off = qla82xx_decode_crb_addr((अचिन्हित दीर्घ)buf[i].addr) +
		    QLA82XX_PCI_CRBSPACE;
		/* Not all CRB  addr/value pair to be written,
		 * some of them are skipped
		 */

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
			ql_log(ql_log_fatal, vha, 0x0116,
			    "Unknown addr: 0x%08lx.\n", buf[i].addr);
			जारी;
		पूर्ण

		qla82xx_wr_32(ha, off, buf[i].data);

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
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0xec, 0x1e);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0x4c, 8);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_I+0x4c, 8);

	/* Clear all protocol processing engines */
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0xc, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_pci_mem_ग_लिखो_2M(काष्ठा qla_hw_data *ha,
		u64 off, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक i, j, ret = 0, loop, sz[2], off0;
	पूर्णांक scale, shअगरt_amount, startword;
	uपूर्णांक32_t temp;
	uपूर्णांक64_t off8, mem_crb, पंचांगpw, word[2] = अणु0, 0पूर्ण;

	/*
	 * If not MN, go check क्रम MS or invalid.
	 */
	अगर (off >= QLA82XX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	अन्यथा अणु
		mem_crb = QLA82XX_CRB_DDR_NET;
		अगर (qla82xx_pci_mem_bound_check(ha, off, size) == 0)
			वापस qla82xx_pci_mem_ग_लिखो_direct(ha,
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
		अगर (qla82xx_pci_mem_पढ़ो_2M(ha, off8 +
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

	अगर (sz[0] == 8) अणु
		word[startword] = पंचांगpw;
	पूर्ण अन्यथा अणु
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
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_ADDR_HI, temp);
		temp = word[i * scale] & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_LO, temp);
		temp = (word[i * scale] >> 32) & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb+MIU_TEST_AGT_WRDATA_HI, temp);
		temp = word[i*scale + 1] & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb +
		    MIU_TEST_AGT_WRDATA_UPPER_LO, temp);
		temp = (word[i*scale + 1] >> 32) & 0xffffffff;
		qla82xx_wr_32(ha, mem_crb +
		    MIU_TEST_AGT_WRDATA_UPPER_HI, temp);

		temp = MIU_TA_CTL_ENABLE | MIU_TA_CTL_WRITE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_START | MIU_TA_CTL_ENABLE | MIU_TA_CTL_WRITE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			temp = qla82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			अगर ((temp & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			अगर (prपूर्णांकk_ratelimit())
				dev_err(&ha->pdev->dev,
				    "failed to write through agent.\n");
			ret = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qla82xx_fw_load_from_flash(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक  i;
	दीर्घ size = 0;
	दीर्घ flashaddr = ha->flt_region_bootload << 2;
	दीर्घ memaddr = BOOTLD_START;
	u64 data;
	u32 high, low;

	size = (IMAGE_START - BOOTLD_START) / 8;

	क्रम (i = 0; i < size; i++) अणु
		अगर ((qla82xx_rom_fast_पढ़ो(ha, flashaddr, (पूर्णांक *)&low)) ||
		    (qla82xx_rom_fast_पढ़ो(ha, flashaddr + 4, (पूर्णांक *)&high))) अणु
			वापस -1;
		पूर्ण
		data = ((u64)high << 32) | low ;
		qla82xx_pci_mem_ग_लिखो_2M(ha, memaddr, &data, 8);
		flashaddr += 8;
		memaddr += 8;

		अगर (i % 0x1000 == 0)
			msleep(1);
	पूर्ण
	udelay(100);
	पढ़ो_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x18, 0x1020);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0x80001e);
	पढ़ो_unlock(&ha->hw_lock);
	वापस 0;
पूर्ण

पूर्णांक
qla82xx_pci_mem_पढ़ो_2M(काष्ठा qla_hw_data *ha,
		u64 off, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक i, j = 0, k, start, end, loop, sz[2], off0[2];
	पूर्णांक	      shअगरt_amount;
	uपूर्णांक32_t      temp;
	uपूर्णांक64_t      off8, val, mem_crb, word[2] = अणु0, 0पूर्ण;

	/*
	 * If not MN, go check क्रम MS or invalid.
	 */

	अगर (off >= QLA82XX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	अन्यथा अणु
		mem_crb = QLA82XX_CRB_DDR_NET;
		अगर (qla82xx_pci_mem_bound_check(ha, off, size) == 0)
			वापस qla82xx_pci_mem_पढ़ो_direct(ha,
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
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_HI, temp);
		temp = MIU_TA_CTL_ENABLE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_START | MIU_TA_CTL_ENABLE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			temp = qla82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			अगर ((temp & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			अगर (prपूर्णांकk_ratelimit())
				dev_err(&ha->pdev->dev,
				    "failed to read through agent.\n");
			अवरोध;
		पूर्ण

		start = off0[i] >> 2;
		end   = (off0[i] + sz[i] - 1) >> 2;
		क्रम (k = start; k <= end; k++) अणु
			temp = qla82xx_rd_32(ha,
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


अटल काष्ठा qla82xx_uri_table_desc *
qla82xx_get_table_desc(स्थिर u8 *unirom, पूर्णांक section)
अणु
	uपूर्णांक32_t i;
	काष्ठा qla82xx_uri_table_desc *directory =
		(काष्ठा qla82xx_uri_table_desc *)&unirom[0];
	uपूर्णांक32_t offset;
	uपूर्णांक32_t tab_type;
	uपूर्णांक32_t entries = le32_to_cpu(directory->num_entries);

	क्रम (i = 0; i < entries; i++) अणु
		offset = le32_to_cpu(directory->findex) +
		    (i * le32_to_cpu(directory->entry_size));
		tab_type = get_unaligned_le32((u32 *)&unirom[offset] + 8);

		अगर (tab_type == section)
			वापस (काष्ठा qla82xx_uri_table_desc *)&unirom[offset];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा qla82xx_uri_data_desc *
qla82xx_get_data_desc(काष्ठा qla_hw_data *ha,
	u32 section, u32 idx_offset)
अणु
	स्थिर u8 *unirom = ha->hablob->fw->data;
	पूर्णांक idx = get_unaligned_le32((u32 *)&unirom[ha->file_prd_off] +
				     idx_offset);
	काष्ठा qla82xx_uri_table_desc *tab_desc = शून्य;
	uपूर्णांक32_t offset;

	tab_desc = qla82xx_get_table_desc(unirom, section);
	अगर (!tab_desc)
		वापस शून्य;

	offset = le32_to_cpu(tab_desc->findex) +
	    (le32_to_cpu(tab_desc->entry_size) * idx);

	वापस (काष्ठा qla82xx_uri_data_desc *)&unirom[offset];
पूर्ण

अटल u8 *
qla82xx_get_bootld_offset(काष्ठा qla_hw_data *ha)
अणु
	u32 offset = BOOTLD_START;
	काष्ठा qla82xx_uri_data_desc *uri_desc = शून्य;

	अगर (ha->fw_type == QLA82XX_UNIFIED_ROMIMAGE) अणु
		uri_desc = qla82xx_get_data_desc(ha,
		    QLA82XX_URI_सूची_SECT_BOOTLD, QLA82XX_URI_BOOTLD_IDX_OFF);
		अगर (uri_desc)
			offset = le32_to_cpu(uri_desc->findex);
	पूर्ण

	वापस (u8 *)&ha->hablob->fw->data[offset];
पूर्ण

अटल u32 qla82xx_get_fw_size(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा qla82xx_uri_data_desc *uri_desc = शून्य;

	अगर (ha->fw_type == QLA82XX_UNIFIED_ROMIMAGE) अणु
		uri_desc =  qla82xx_get_data_desc(ha, QLA82XX_URI_सूची_SECT_FW,
		    QLA82XX_URI_FIRMWARE_IDX_OFF);
		अगर (uri_desc)
			वापस le32_to_cpu(uri_desc->size);
	पूर्ण

	वापस get_unaligned_le32(&ha->hablob->fw->data[FW_SIZE_OFFSET]);
पूर्ण

अटल u8 *
qla82xx_get_fw_offs(काष्ठा qla_hw_data *ha)
अणु
	u32 offset = IMAGE_START;
	काष्ठा qla82xx_uri_data_desc *uri_desc = शून्य;

	अगर (ha->fw_type == QLA82XX_UNIFIED_ROMIMAGE) अणु
		uri_desc = qla82xx_get_data_desc(ha, QLA82XX_URI_सूची_SECT_FW,
			QLA82XX_URI_FIRMWARE_IDX_OFF);
		अगर (uri_desc)
			offset = le32_to_cpu(uri_desc->findex);
	पूर्ण

	वापस (u8 *)&ha->hablob->fw->data[offset];
पूर्ण

/* PCI related functions */
पूर्णांक qla82xx_pci_region_offset(काष्ठा pci_dev *pdev, पूर्णांक region)
अणु
	अचिन्हित दीर्घ val = 0;
	u32 control;

	चयन (region) अणु
	हाल 0:
		val = 0;
		अवरोध;
	हाल 1:
		pci_पढ़ो_config_dword(pdev, QLA82XX_PCI_REG_MSIX_TBL, &control);
		val = control + QLA82XX_MSIX_TBL_SPACE;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण


पूर्णांक
qla82xx_iospace_config(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t len = 0;

	अगर (pci_request_regions(ha->pdev, QLA2XXX_DRIVER_NAME)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x000c,
		    "Failed to reserver selected regions.\n");
		जाओ iospace_error_निकास;
	पूर्ण

	/* Use MMIO operations क्रम all accesses. */
	अगर (!(pci_resource_flags(ha->pdev, 0) & IORESOURCE_MEM)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x000d,
		    "Region #0 not an MMIO resource, aborting.\n");
		जाओ iospace_error_निकास;
	पूर्ण

	len = pci_resource_len(ha->pdev, 0);
	ha->nx_pcibase = ioremap(pci_resource_start(ha->pdev, 0), len);
	अगर (!ha->nx_pcibase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x000e,
		    "Cannot remap pcibase MMIO, aborting.\n");
		जाओ iospace_error_निकास;
	पूर्ण

	/* Mapping of IO base poपूर्णांकer */
	अगर (IS_QLA8044(ha)) अणु
		ha->iobase = ha->nx_pcibase;
	पूर्ण अन्यथा अगर (IS_QLA82XX(ha)) अणु
		ha->iobase = ha->nx_pcibase + 0xbc000 + (ha->pdev->devfn << 11);
	पूर्ण

	अगर (!ql2xdbwr) अणु
		ha->nxdb_wr_ptr = ioremap((pci_resource_start(ha->pdev, 4) +
		    (ha->pdev->devfn << 12)), 4);
		अगर (!ha->nxdb_wr_ptr) अणु
			ql_log_pci(ql_log_fatal, ha->pdev, 0x000f,
			    "Cannot remap MMIO, aborting.\n");
			जाओ iospace_error_निकास;
		पूर्ण

		/* Mapping of IO base poपूर्णांकer,
		 * करोor bell पढ़ो and ग_लिखो poपूर्णांकer
		 */
		ha->nxdb_rd_ptr = ha->nx_pcibase + (512 * 1024) +
		    (ha->pdev->devfn * 8);
	पूर्ण अन्यथा अणु
		ha->nxdb_wr_ptr = (व्योम __iomem *)(ha->pdev->devfn == 6 ?
			QLA82XX_CAMRAM_DB1 :
			QLA82XX_CAMRAM_DB2);
	पूर्ण

	ha->max_req_queues = ha->max_rsp_queues = 1;
	ha->msix_count = ha->max_rsp_queues + 1;
	ql_dbg_pci(ql_dbg_multiq, ha->pdev, 0xc006,
	    "nx_pci_base=%p iobase=%p "
	    "max_req_queues=%d msix_count=%d.\n",
	    ha->nx_pcibase, ha->iobase,
	    ha->max_req_queues, ha->msix_count);
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0010,
	    "nx_pci_base=%p iobase=%p "
	    "max_req_queues=%d msix_count=%d.\n",
	    ha->nx_pcibase, ha->iobase,
	    ha->max_req_queues, ha->msix_count);
	वापस 0;

iospace_error_निकास:
	वापस -ENOMEM;
पूर्ण

/* GS related functions */

/* Initialization related functions */

/**
 * qla82xx_pci_config() - Setup ISP82xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
*/
पूर्णांक
qla82xx_pci_config(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक ret;

	pci_set_master(ha->pdev);
	ret = pci_set_mwi(ha->pdev);
	ha->chip_revision = ha->pdev->revision;
	ql_dbg(ql_dbg_init, vha, 0x0043,
	    "Chip revision:%d; pci_set_mwi() returned %d.\n",
	    ha->chip_revision, ret);
	वापस 0;
पूर्ण

/**
 * qla82xx_reset_chip() - Setup ISP82xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla82xx_reset_chip(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	ha->isp_ops->disable_पूर्णांकrs(ha);

	वापस QLA_SUCCESS;
पूर्ण

व्योम qla82xx_config_rings(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_82xx __iomem *reg = &ha->iobase->isp82;
	काष्ठा init_cb_81xx *icb;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];

	/* Setup ring parameters in initialization control block. */
	icb = (काष्ठा init_cb_81xx *)ha->init_cb;
	icb->request_q_outpoपूर्णांकer = cpu_to_le16(0);
	icb->response_q_inpoपूर्णांकer = cpu_to_le16(0);
	icb->request_q_length = cpu_to_le16(req->length);
	icb->response_q_length = cpu_to_le16(rsp->length);
	put_unaligned_le64(req->dma, &icb->request_q_address);
	put_unaligned_le64(rsp->dma, &icb->response_q_address);

	wrt_reg_dword(&reg->req_q_out[0], 0);
	wrt_reg_dword(&reg->rsp_q_in[0], 0);
	wrt_reg_dword(&reg->rsp_q_out[0], 0);
पूर्ण

अटल पूर्णांक
qla82xx_fw_load_from_blob(काष्ठा qla_hw_data *ha)
अणु
	u64 *ptr64;
	u32 i, flashaddr, size;
	__le64 data;

	size = (IMAGE_START - BOOTLD_START) / 8;

	ptr64 = (u64 *)qla82xx_get_bootld_offset(ha);
	flashaddr = BOOTLD_START;

	क्रम (i = 0; i < size; i++) अणु
		data = cpu_to_le64(ptr64[i]);
		अगर (qla82xx_pci_mem_ग_लिखो_2M(ha, flashaddr, &data, 8))
			वापस -EIO;
		flashaddr += 8;
	पूर्ण

	flashaddr = FLASH_ADDR_START;
	size = qla82xx_get_fw_size(ha) / 8;
	ptr64 = (u64 *)qla82xx_get_fw_offs(ha);

	क्रम (i = 0; i < size; i++) अणु
		data = cpu_to_le64(ptr64[i]);

		अगर (qla82xx_pci_mem_ग_लिखो_2M(ha, flashaddr, &data, 8))
			वापस -EIO;
		flashaddr += 8;
	पूर्ण
	udelay(100);

	/* Write a magic value to CAMRAM रेजिस्टर
	 * at a specअगरied offset to indicate
	 * that all data is written and
	 * पढ़ोy क्रम firmware to initialize.
	 */
	qla82xx_wr_32(ha, QLA82XX_CAM_RAM(0x1fc), QLA82XX_BDINFO_MAGIC);

	पढ़ो_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x18, 0x1020);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0x80001e);
	पढ़ो_unlock(&ha->hw_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_set_product_offset(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा qla82xx_uri_table_desc *ptab_desc = शून्य;
	स्थिर uपूर्णांक8_t *unirom = ha->hablob->fw->data;
	uपूर्णांक32_t i;
	uपूर्णांक32_t entries;
	uपूर्णांक32_t flags, file_chiprev, offset;
	uपूर्णांक8_t chiprev = ha->chip_revision;
	/* Hardcoding mn_present flag क्रम P3P */
	पूर्णांक mn_present = 0;
	uपूर्णांक32_t flagbit;

	ptab_desc = qla82xx_get_table_desc(unirom,
		 QLA82XX_URI_सूची_SECT_PRODUCT_TBL);
	अगर (!ptab_desc)
		वापस -1;

	entries = le32_to_cpu(ptab_desc->num_entries);

	क्रम (i = 0; i < entries; i++) अणु
		offset = le32_to_cpu(ptab_desc->findex) +
			(i * le32_to_cpu(ptab_desc->entry_size));
		flags = le32_to_cpu(*((__le32 *)&unirom[offset] +
			QLA82XX_URI_FLAGS_OFF));
		file_chiprev = le32_to_cpu(*((__le32 *)&unirom[offset] +
			QLA82XX_URI_CHIP_REV_OFF));

		flagbit = mn_present ? 1 : 2;

		अगर ((chiprev == file_chiprev) && ((1ULL << flagbit) & flags)) अणु
			ha->file_prd_off = offset;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक
qla82xx_validate_firmware_blob(scsi_qla_host_t *vha, uपूर्णांक8_t fw_type)
अणु
	uपूर्णांक32_t val;
	uपूर्णांक32_t min_size;
	काष्ठा qla_hw_data *ha = vha->hw;
	स्थिर काष्ठा firmware *fw = ha->hablob->fw;

	ha->fw_type = fw_type;

	अगर (fw_type == QLA82XX_UNIFIED_ROMIMAGE) अणु
		अगर (qla82xx_set_product_offset(ha))
			वापस -EINVAL;

		min_size = QLA82XX_URI_FW_MIN_SIZE;
	पूर्ण अन्यथा अणु
		val = get_unaligned_le32(&fw->data[QLA82XX_FW_MAGIC_OFFSET]);
		अगर (val != QLA82XX_BDINFO_MAGIC)
			वापस -EINVAL;

		min_size = QLA82XX_FW_MIN_SIZE;
	पूर्ण

	अगर (fw->size < min_size)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक
qla82xx_check_cmdpeg_state(काष्ठा qla_hw_data *ha)
अणु
	u32 val = 0;
	पूर्णांक retries = 60;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	करो अणु
		पढ़ो_lock(&ha->hw_lock);
		val = qla82xx_rd_32(ha, CRB_CMDPEG_STATE);
		पढ़ो_unlock(&ha->hw_lock);

		चयन (val) अणु
		हाल PHAN_INITIALIZE_COMPLETE:
		हाल PHAN_INITIALIZE_ACK:
			वापस QLA_SUCCESS;
		हाल PHAN_INITIALIZE_FAILED:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ql_log(ql_log_info, vha, 0x00a8,
		    "CRB_CMDPEG_STATE: 0x%x and retries:0x%x.\n",
		    val, retries);

		msleep(500);

	पूर्ण जबतक (--retries);

	ql_log(ql_log_fatal, vha, 0x00a9,
	    "Cmd Peg initialization failed: 0x%x.\n", val);

	val = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_PEGTUNE_DONE);
	पढ़ो_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, CRB_CMDPEG_STATE, PHAN_INITIALIZE_FAILED);
	पढ़ो_unlock(&ha->hw_lock);
	वापस QLA_FUNCTION_FAILED;
पूर्ण

अटल पूर्णांक
qla82xx_check_rcvpeg_state(काष्ठा qla_hw_data *ha)
अणु
	u32 val = 0;
	पूर्णांक retries = 60;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	करो अणु
		पढ़ो_lock(&ha->hw_lock);
		val = qla82xx_rd_32(ha, CRB_RCVPEG_STATE);
		पढ़ो_unlock(&ha->hw_lock);

		चयन (val) अणु
		हाल PHAN_INITIALIZE_COMPLETE:
		हाल PHAN_INITIALIZE_ACK:
			वापस QLA_SUCCESS;
		हाल PHAN_INITIALIZE_FAILED:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ql_log(ql_log_info, vha, 0x00ab,
		    "CRB_RCVPEG_STATE: 0x%x and retries: 0x%x.\n",
		    val, retries);

		msleep(500);

	पूर्ण जबतक (--retries);

	ql_log(ql_log_fatal, vha, 0x00ac,
	    "Rcv Peg initialization failed: 0x%x.\n", val);
	पढ़ो_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, CRB_RCVPEG_STATE, PHAN_INITIALIZE_FAILED);
	पढ़ो_unlock(&ha->hw_lock);
	वापस QLA_FUNCTION_FAILED;
पूर्ण

/* ISR related functions */
अटल काष्ठा qla82xx_legacy_पूर्णांकr_set legacy_पूर्णांकr[] =
	QLA82XX_LEGACY_INTR_CONFIG;

/*
 * qla82xx_mbx_completion() - Process mailbox command completions.
 * @ha: SCSI driver HA context
 * @mb0: Mailbox0 रेजिस्टर
 */
व्योम
qla82xx_mbx_completion(scsi_qla_host_t *vha, uपूर्णांक16_t mb0)
अणु
	uपूर्णांक16_t	cnt;
	__le16 __iomem *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_82xx __iomem *reg = &ha->iobase->isp82;

	wptr = &reg->mailbox_out[1];

	/* Load वापस mailbox रेजिस्टरs. */
	ha->flags.mbox_पूर्णांक = 1;
	ha->mailbox_out[0] = mb0;

	क्रम (cnt = 1; cnt < ha->mbx_count; cnt++) अणु
		ha->mailbox_out[cnt] = rd_reg_word(wptr);
		wptr++;
	पूर्ण

	अगर (!ha->mcp)
		ql_dbg(ql_dbg_async, vha, 0x5053,
		    "MBX pointer ERROR.\n");
पूर्ण

/**
 * qla82xx_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISP23xx and ISP63xx.
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qla82xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_82xx __iomem *reg;
	पूर्णांक status = 0, status1 = 0;
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक32_t	stat = 0;
	uपूर्णांक16_t	mb[8];

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0xb053,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = rsp->hw;

	अगर (!ha->flags.msi_enabled) अणु
		status = qla82xx_rd_32(ha, ISR_INT_VECTOR);
		अगर (!(status & ha->nx_legacy_पूर्णांकr.पूर्णांक_vec_bit))
			वापस IRQ_NONE;

		status1 = qla82xx_rd_32(ha, ISR_INT_STATE_REG);
		अगर (!ISR_IS_LEGACY_INTR_TRIGGERED(status1))
			वापस IRQ_NONE;
	पूर्ण

	/* clear the पूर्णांकerrupt */
	qla82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_status_reg, 0xffffffff);

	/* पढ़ो twice to ensure ग_लिखो is flushed */
	qla82xx_rd_32(ha, ISR_INT_VECTOR);
	qla82xx_rd_32(ha, ISR_INT_VECTOR);

	reg = &ha->iobase->isp82;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	क्रम (iter = 1; iter--; ) अणु

		अगर (rd_reg_dword(&reg->host_पूर्णांक)) अणु
			stat = rd_reg_dword(&reg->host_status);

			चयन (stat & 0xff) अणु
			हाल 0x1:
			हाल 0x2:
			हाल 0x10:
			हाल 0x11:
				qla82xx_mbx_completion(vha, MSW(stat));
				status |= MBX_INTERRUPT;
				अवरोध;
			हाल 0x12:
				mb[0] = MSW(stat);
				mb[1] = rd_reg_word(&reg->mailbox_out[1]);
				mb[2] = rd_reg_word(&reg->mailbox_out[2]);
				mb[3] = rd_reg_word(&reg->mailbox_out[3]);
				qla2x00_async_event(vha, rsp, mb);
				अवरोध;
			हाल 0x13:
				qla24xx_process_response_queue(vha, rsp);
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_async, vha, 0x5054,
				    "Unrecognized interrupt type (%d).\n",
				    stat & 0xff);
				अवरोध;
			पूर्ण
		पूर्ण
		wrt_reg_dword(&reg->host_पूर्णांक, 0);
	पूर्ण

	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (!ha->flags.msi_enabled)
		qla82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0xfbff);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla82xx_msix_शेष(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_82xx __iomem *reg;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t stat = 0;
	uपूर्णांक32_t host_पूर्णांक = 0;
	uपूर्णांक16_t mb[8];

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		prपूर्णांकk(KERN_INFO
			"%s(): NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = rsp->hw;

	reg = &ha->iobase->isp82;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	करो अणु
		host_पूर्णांक = rd_reg_dword(&reg->host_पूर्णांक);
		अगर (qla2x00_check_reg32_क्रम_disconnect(vha, host_पूर्णांक))
			अवरोध;
		अगर (host_पूर्णांक) अणु
			stat = rd_reg_dword(&reg->host_status);

			चयन (stat & 0xff) अणु
			हाल 0x1:
			हाल 0x2:
			हाल 0x10:
			हाल 0x11:
				qla82xx_mbx_completion(vha, MSW(stat));
				status |= MBX_INTERRUPT;
				अवरोध;
			हाल 0x12:
				mb[0] = MSW(stat);
				mb[1] = rd_reg_word(&reg->mailbox_out[1]);
				mb[2] = rd_reg_word(&reg->mailbox_out[2]);
				mb[3] = rd_reg_word(&reg->mailbox_out[3]);
				qla2x00_async_event(vha, rsp, mb);
				अवरोध;
			हाल 0x13:
				qla24xx_process_response_queue(vha, rsp);
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_async, vha, 0x5041,
				    "Unrecognized interrupt type (%d).\n",
				    stat & 0xff);
				अवरोध;
			पूर्ण
		पूर्ण
		wrt_reg_dword(&reg->host_पूर्णांक, 0);
	पूर्ण जबतक (0);

	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla82xx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_82xx __iomem *reg;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t host_पूर्णांक = 0;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		prपूर्णांकk(KERN_INFO
			"%s(): NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	ha = rsp->hw;
	reg = &ha->iobase->isp82;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	host_पूर्णांक = rd_reg_dword(&reg->host_पूर्णांक);
	अगर (qla2x00_check_reg32_क्रम_disconnect(vha, host_पूर्णांक))
		जाओ out;
	qla24xx_process_response_queue(vha, rsp);
	wrt_reg_dword(&reg->host_पूर्णांक, 0);
out:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

व्योम
qla82xx_poll(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_82xx __iomem *reg;
	पूर्णांक status = 0;
	uपूर्णांक32_t stat;
	uपूर्णांक32_t host_पूर्णांक = 0;
	uपूर्णांक16_t mb[8];
	अचिन्हित दीर्घ flags;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		prपूर्णांकk(KERN_INFO
			"%s(): NULL response queue pointer.\n", __func__);
		वापस;
	पूर्ण
	ha = rsp->hw;

	reg = &ha->iobase->isp82;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);

	host_पूर्णांक = rd_reg_dword(&reg->host_पूर्णांक);
	अगर (qla2x00_check_reg32_क्रम_disconnect(vha, host_पूर्णांक))
		जाओ out;
	अगर (host_पूर्णांक) अणु
		stat = rd_reg_dword(&reg->host_status);
		चयन (stat & 0xff) अणु
		हाल 0x1:
		हाल 0x2:
		हाल 0x10:
		हाल 0x11:
			qla82xx_mbx_completion(vha, MSW(stat));
			status |= MBX_INTERRUPT;
			अवरोध;
		हाल 0x12:
			mb[0] = MSW(stat);
			mb[1] = rd_reg_word(&reg->mailbox_out[1]);
			mb[2] = rd_reg_word(&reg->mailbox_out[2]);
			mb[3] = rd_reg_word(&reg->mailbox_out[3]);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		हाल 0x13:
			qla24xx_process_response_queue(vha, rsp);
			अवरोध;
		शेष:
			ql_dbg(ql_dbg_p3p, vha, 0xb013,
			    "Unrecognized interrupt type (%d).\n",
			    stat * 0xff);
			अवरोध;
		पूर्ण
		wrt_reg_dword(&reg->host_पूर्णांक, 0);
	पूर्ण
out:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

व्योम
qla82xx_enable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla82xx_mbx_पूर्णांकr_enable(vha);
	spin_lock_irq(&ha->hardware_lock);
	अगर (IS_QLA8044(ha))
		qla8044_wr_reg(ha, LEG_INTR_MASK_OFFSET, 0);
	अन्यथा
		qla82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0xfbff);
	spin_unlock_irq(&ha->hardware_lock);
	ha->पूर्णांकerrupts_on = 1;
पूर्ण

व्योम
qla82xx_disable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	अगर (ha->पूर्णांकerrupts_on)
		qla82xx_mbx_पूर्णांकr_disable(vha);

	spin_lock_irq(&ha->hardware_lock);
	अगर (IS_QLA8044(ha))
		qla8044_wr_reg(ha, LEG_INTR_MASK_OFFSET, 1);
	अन्यथा
		qla82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0x0400);
	spin_unlock_irq(&ha->hardware_lock);
	ha->पूर्णांकerrupts_on = 0;
पूर्ण

व्योम qla82xx_init_flags(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा qla82xx_legacy_पूर्णांकr_set *nx_legacy_पूर्णांकr;

	/* ISP 8021 initializations */
	rwlock_init(&ha->hw_lock);
	ha->qdr_sn_winकरोw = -1;
	ha->ddr_mn_winकरोw = -1;
	ha->curr_winकरोw = 255;
	ha->portnum = PCI_FUNC(ha->pdev->devfn);
	nx_legacy_पूर्णांकr = &legacy_पूर्णांकr[ha->portnum];
	ha->nx_legacy_पूर्णांकr.पूर्णांक_vec_bit = nx_legacy_पूर्णांकr->पूर्णांक_vec_bit;
	ha->nx_legacy_पूर्णांकr.tgt_status_reg = nx_legacy_पूर्णांकr->tgt_status_reg;
	ha->nx_legacy_पूर्णांकr.tgt_mask_reg = nx_legacy_पूर्णांकr->tgt_mask_reg;
	ha->nx_legacy_पूर्णांकr.pci_पूर्णांक_reg = nx_legacy_पूर्णांकr->pci_पूर्णांक_reg;
पूर्ण

अटल अंतरभूत व्योम
qla82xx_set_idc_version(scsi_qla_host_t *vha)
अणु
	पूर्णांक idc_ver;
	uपूर्णांक32_t drv_active;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	अगर (drv_active == (QLA82XX_DRV_ACTIVE << (ha->portnum * 4))) अणु
		qla82xx_wr_32(ha, QLA82XX_CRB_DRV_IDC_VERSION,
		    QLA82XX_IDC_VERSION);
		ql_log(ql_log_info, vha, 0xb082,
		    "IDC version updated to %d\n", QLA82XX_IDC_VERSION);
	पूर्ण अन्यथा अणु
		idc_ver = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_IDC_VERSION);
		अगर (idc_ver != QLA82XX_IDC_VERSION)
			ql_log(ql_log_info, vha, 0xb083,
			    "qla2xxx driver IDC version %d is not compatible "
			    "with IDC version %d of the other drivers\n",
			    QLA82XX_IDC_VERSION, idc_ver);
	पूर्ण
पूर्ण

अंतरभूत व्योम
qla82xx_set_drv_active(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t drv_active;
	काष्ठा qla_hw_data *ha = vha->hw;

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);

	/* If reset value is all FF's, initialize DRV_ACTIVE */
	अगर (drv_active == 0xffffffff) अणु
		qla82xx_wr_32(ha, QLA82XX_CRB_DRV_ACTIVE,
			QLA82XX_DRV_NOT_ACTIVE);
		drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	पूर्ण
	drv_active |= (QLA82XX_DRV_ACTIVE << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_ACTIVE, drv_active);
पूर्ण

अंतरभूत व्योम
qla82xx_clear_drv_active(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t drv_active;

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	drv_active &= ~(QLA82XX_DRV_ACTIVE << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_ACTIVE, drv_active);
पूर्ण

अटल अंतरभूत पूर्णांक
qla82xx_need_reset(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t drv_state;
	पूर्णांक rval;

	अगर (ha->flags.nic_core_reset_owner)
		वापस 1;
	अन्यथा अणु
		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		rval = drv_state & (QLA82XX_DRVST_RST_RDY << (ha->portnum * 4));
		वापस rval;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla82xx_set_rst_पढ़ोy(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t drv_state;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);

	/* If reset value is all FF's, initialize DRV_STATE */
	अगर (drv_state == 0xffffffff) अणु
		qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, QLA82XX_DRVST_NOT_RDY);
		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	पूर्ण
	drv_state |= (QLA82XX_DRVST_RST_RDY << (ha->portnum * 4));
	ql_dbg(ql_dbg_init, vha, 0x00bb,
	    "drv_state = 0x%08x.\n", drv_state);
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, drv_state);
पूर्ण

अटल अंतरभूत व्योम
qla82xx_clear_rst_पढ़ोy(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t drv_state;

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_state &= ~(QLA82XX_DRVST_RST_RDY << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, drv_state);
पूर्ण

अटल अंतरभूत व्योम
qla82xx_set_qsnt_पढ़ोy(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक32_t qsnt_state;

	qsnt_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	qsnt_state |= (QLA82XX_DRVST_QSNT_RDY << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, qsnt_state);
पूर्ण

व्योम
qla82xx_clear_qsnt_पढ़ोy(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t qsnt_state;

	qsnt_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	qsnt_state &= ~(QLA82XX_DRVST_QSNT_RDY << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, qsnt_state);
पूर्ण

अटल पूर्णांक
qla82xx_load_fw(scsi_qla_host_t *vha)
अणु
	पूर्णांक rst;
	काष्ठा fw_blob *blob;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (qla82xx_pinit_from_rom(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0x009f,
		    "Error during CRB initialization.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण
	udelay(500);

	/* Bring QM and CAMRAM out of reset */
	rst = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET);
	rst &= ~((1 << 28) | (1 << 24));
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, rst);

	/*
	 * FW Load priority:
	 * 1) Operational firmware residing in flash.
	 * 2) Firmware via request-firmware पूर्णांकerface (.bin file).
	 */
	अगर (ql2xfwloadbin == 2)
		जाओ try_blob_fw;

	ql_log(ql_log_info, vha, 0x00a0,
	    "Attempting to load firmware from flash.\n");

	अगर (qla82xx_fw_load_from_flash(ha) == QLA_SUCCESS) अणु
		ql_log(ql_log_info, vha, 0x00a1,
		    "Firmware loaded successfully from flash.\n");
		वापस QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		ql_log(ql_log_warn, vha, 0x0108,
		    "Firmware load from flash failed.\n");
	पूर्ण

try_blob_fw:
	ql_log(ql_log_info, vha, 0x00a2,
	    "Attempting to load firmware from blob.\n");

	/* Load firmware blob. */
	blob = ha->hablob = qla2x00_request_firmware(vha);
	अगर (!blob) अणु
		ql_log(ql_log_fatal, vha, 0x00a3,
		    "Firmware image not present.\n");
		जाओ fw_load_failed;
	पूर्ण

	/* Validating firmware blob */
	अगर (qla82xx_validate_firmware_blob(vha,
		QLA82XX_FLASH_ROMIMAGE)) अणु
		/* Fallback to URI क्रमmat */
		अगर (qla82xx_validate_firmware_blob(vha,
			QLA82XX_UNIFIED_ROMIMAGE)) अणु
			ql_log(ql_log_fatal, vha, 0x00a4,
			    "No valid firmware image found.\n");
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	अगर (qla82xx_fw_load_from_blob(ha) == QLA_SUCCESS) अणु
		ql_log(ql_log_info, vha, 0x00a5,
		    "Firmware loaded successfully from binary blob.\n");
		वापस QLA_SUCCESS;
	पूर्ण

	ql_log(ql_log_fatal, vha, 0x00a6,
	       "Firmware load failed for binary blob.\n");
	blob->fw = शून्य;
	blob = शून्य;

fw_load_failed:
	वापस QLA_FUNCTION_FAILED;
पूर्ण

पूर्णांक
qla82xx_start_firmware(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t      lnk;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* scrub dma mask expansion रेजिस्टर */
	qla82xx_wr_32(ha, CRB_DMA_SHIFT, QLA82XX_DMA_SHIFT_VALUE);

	/* Put both the PEG CMD and RCV PEG to शेष state
	 * of 0 beक्रमe resetting the hardware
	 */
	qla82xx_wr_32(ha, CRB_CMDPEG_STATE, 0);
	qla82xx_wr_32(ha, CRB_RCVPEG_STATE, 0);

	/* Overग_लिखो stale initialization रेजिस्टर values */
	qla82xx_wr_32(ha, QLA82XX_PEG_HALT_STATUS1, 0);
	qla82xx_wr_32(ha, QLA82XX_PEG_HALT_STATUS2, 0);

	अगर (qla82xx_load_fw(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0x00a7,
		    "Error trying to start fw.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Handshake with the card beक्रमe we रेजिस्टर the devices. */
	अगर (qla82xx_check_cmdpeg_state(ha) != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0x00aa,
		    "Error during card handshake.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Negotiated Link width */
	pcie_capability_पढ़ो_word(ha->pdev, PCI_EXP_LNKSTA, &lnk);
	ha->link_width = (lnk >> 4) & 0x3f;

	/* Synchronize with Receive peg */
	वापस qla82xx_check_rcvpeg_state(ha);
पूर्ण

अटल __le32 *
qla82xx_पढ़ो_flash_data(scsi_qla_host_t *vha, __le32 *dwptr, uपूर्णांक32_t faddr,
	uपूर्णांक32_t length)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t val;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Dword पढ़ोs to flash. */
	क्रम (i = 0; i < length/4; i++, faddr += 4) अणु
		अगर (qla82xx_rom_fast_पढ़ो(ha, faddr, &val)) अणु
			ql_log(ql_log_warn, vha, 0x0106,
			    "Do ROM fast read failed.\n");
			जाओ करोne_पढ़ो;
		पूर्ण
		dwptr[i] = cpu_to_le32(val);
	पूर्ण
करोne_पढ़ो:
	वापस dwptr;
पूर्ण

अटल पूर्णांक
qla82xx_unprotect_flash(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t val;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	अगर (ret < 0) अणु
		ql_log(ql_log_warn, vha, 0xb014,
		    "ROM Lock failed.\n");
		वापस ret;
	पूर्ण

	ret = qla82xx_पढ़ो_status_reg(ha, &val);
	अगर (ret < 0)
		जाओ करोne_unprotect;

	val &= ~(BLOCK_PROTECT_BITS << 2);
	ret = qla82xx_ग_लिखो_status_reg(ha, val);
	अगर (ret < 0) अणु
		val |= (BLOCK_PROTECT_BITS << 2);
		qla82xx_ग_लिखो_status_reg(ha, val);
	पूर्ण

	अगर (qla82xx_ग_लिखो_disable_flash(ha) != 0)
		ql_log(ql_log_warn, vha, 0xb015,
		    "Write disable failed.\n");

करोne_unprotect:
	qla82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

अटल पूर्णांक
qla82xx_protect_flash(काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t val;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	अगर (ret < 0) अणु
		ql_log(ql_log_warn, vha, 0xb016,
		    "ROM Lock failed.\n");
		वापस ret;
	पूर्ण

	ret = qla82xx_पढ़ो_status_reg(ha, &val);
	अगर (ret < 0)
		जाओ करोne_protect;

	val |= (BLOCK_PROTECT_BITS << 2);
	/* LOCK all sectors */
	ret = qla82xx_ग_लिखो_status_reg(ha, val);
	अगर (ret < 0)
		ql_log(ql_log_warn, vha, 0xb017,
		    "Write status register failed.\n");

	अगर (qla82xx_ग_लिखो_disable_flash(ha) != 0)
		ql_log(ql_log_warn, vha, 0xb018,
		    "Write disable failed.\n");
करोne_protect:
	qla82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

अटल पूर्णांक
qla82xx_erase_sector(काष्ठा qla_hw_data *ha, पूर्णांक addr)
अणु
	पूर्णांक ret = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	अगर (ret < 0) अणु
		ql_log(ql_log_warn, vha, 0xb019,
		    "ROM Lock failed.\n");
		वापस ret;
	पूर्ण

	qla82xx_flash_set_ग_लिखो_enable(ha);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ADDRESS, addr);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 3);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_SE);

	अगर (qla82xx_रुको_rom_करोne(ha)) अणु
		ql_log(ql_log_warn, vha, 0xb01a,
		    "Error waiting for rom done.\n");
		ret = -1;
		जाओ करोne;
	पूर्ण
	ret = qla82xx_flash_रुको_ग_लिखो_finish(ha);
करोne:
	qla82xx_rom_unlock(ha);
	वापस ret;
पूर्ण

/*
 * Address and length are byte address
 */
व्योम *
qla82xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
	uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	scsi_block_requests(vha->host);
	qla82xx_पढ़ो_flash_data(vha, buf, offset, length);
	scsi_unblock_requests(vha->host);
	वापस buf;
पूर्ण

अटल पूर्णांक
qla82xx_ग_लिखो_flash_data(काष्ठा scsi_qla_host *vha, __le32 *dwptr,
	uपूर्णांक32_t faddr, uपूर्णांक32_t dwords)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t liter;
	uपूर्णांक32_t rest_addr;
	dma_addr_t optrom_dma;
	व्योम *optrom = शून्य;
	पूर्णांक page_mode = 0;
	काष्ठा qla_hw_data *ha = vha->hw;

	ret = -1;

	/* Prepare burst-capable ग_लिखो on supported ISPs. */
	अगर (page_mode && !(faddr & 0xfff) &&
	    dwords > OPTROM_BURST_DWORDS) अणु
		optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
		    &optrom_dma, GFP_KERNEL);
		अगर (!optrom) अणु
			ql_log(ql_log_warn, vha, 0xb01b,
			    "Unable to allocate memory "
			    "for optrom burst write (%x KB).\n",
			    OPTROM_BURST_SIZE / 1024);
		पूर्ण
	पूर्ण

	rest_addr = ha->fdt_block_size - 1;

	ret = qla82xx_unprotect_flash(ha);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0xb01c,
		    "Unable to unprotect flash for update.\n");
		जाओ ग_लिखो_करोne;
	पूर्ण

	क्रम (liter = 0; liter < dwords; liter++, faddr += 4, dwptr++) अणु
		/* Are we at the beginning of a sector? */
		अगर ((faddr & rest_addr) == 0) अणु

			ret = qla82xx_erase_sector(ha, faddr);
			अगर (ret) अणु
				ql_log(ql_log_warn, vha, 0xb01d,
				    "Unable to erase sector: address=%x.\n",
				    faddr);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Go with burst-ग_लिखो. */
		अगर (optrom && (liter + OPTROM_BURST_DWORDS) <= dwords) अणु
			/* Copy data to DMA'ble buffer. */
			स_नकल(optrom, dwptr, OPTROM_BURST_SIZE);

			ret = qla2x00_load_ram(vha, optrom_dma,
			    (ha->flash_data_off | faddr),
			    OPTROM_BURST_DWORDS);
			अगर (ret != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0xb01e,
				    "Unable to burst-write optrom segment "
				    "(%x/%x/%llx).\n", ret,
				    (ha->flash_data_off | faddr),
				    (अचिन्हित दीर्घ दीर्घ)optrom_dma);
				ql_log(ql_log_warn, vha, 0xb01f,
				    "Reverting to slow-write.\n");

				dma_मुक्त_coherent(&ha->pdev->dev,
				    OPTROM_BURST_SIZE, optrom, optrom_dma);
				optrom = शून्य;
			पूर्ण अन्यथा अणु
				liter += OPTROM_BURST_DWORDS - 1;
				faddr += OPTROM_BURST_DWORDS - 1;
				dwptr += OPTROM_BURST_DWORDS - 1;
				जारी;
			पूर्ण
		पूर्ण

		ret = qla82xx_ग_लिखो_flash_dword(ha, faddr,
						le32_to_cpu(*dwptr));
		अगर (ret) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb020,
			    "Unable to program flash address=%x data=%x.\n",
			    faddr, *dwptr);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = qla82xx_protect_flash(ha);
	अगर (ret)
		ql_log(ql_log_warn, vha, 0xb021,
		    "Unable to protect flash after update.\n");
ग_लिखो_करोne:
	अगर (optrom)
		dma_मुक्त_coherent(&ha->pdev->dev,
		    OPTROM_BURST_SIZE, optrom, optrom_dma);
	वापस ret;
पूर्ण

पूर्णांक
qla82xx_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *vha, व्योम *buf,
	uपूर्णांक32_t offset, uपूर्णांक32_t length)
अणु
	पूर्णांक rval;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	rval = qla82xx_ग_लिखो_flash_data(vha, buf, offset, length >> 2);
	scsi_unblock_requests(vha->host);

	/* Convert वापस ISP82xx to generic */
	अगर (rval)
		rval = QLA_FUNCTION_FAILED;
	अन्यथा
		rval = QLA_SUCCESS;
	वापस rval;
पूर्ण

व्योम
qla82xx_start_iocbs(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	uपूर्णांक32_t dbval;

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	dbval = 0x04 | (ha->portnum << 5);

	dbval = dbval | (req->id << 8) | (req->ring_index << 16);
	अगर (ql2xdbwr)
		qla82xx_wr_32(ha, (अचिन्हित दीर्घ)ha->nxdb_wr_ptr, dbval);
	अन्यथा अणु
		wrt_reg_dword(ha->nxdb_wr_ptr, dbval);
		wmb();
		जबतक (rd_reg_dword(ha->nxdb_rd_ptr) != dbval) अणु
			wrt_reg_dword(ha->nxdb_wr_ptr, dbval);
			wmb();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
qla82xx_rom_lock_recovery(काष्ठा qla_hw_data *ha)
अणु
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक32_t lock_owner = 0;

	अगर (qla82xx_rom_lock(ha)) अणु
		lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
		/* Someone अन्यथा is holding the lock. */
		ql_log(ql_log_info, vha, 0xb022,
		    "Resetting rom_lock, Lock Owner %u.\n", lock_owner);
	पूर्ण
	/*
	 * Either we got the lock, or someone
	 * अन्यथा died जबतक holding it.
	 * In either हाल, unlock.
	 */
	qla82xx_rom_unlock(ha);
पूर्ण

/*
 * qla82xx_device_bootstrap
 *    Initialize device, set DEV_READY, start fw
 *
 * Note:
 *      IDC lock must be held upon entry
 *
 * Return:
 *    Success : 0
 *    Failed  : 1
 */
अटल पूर्णांक
qla82xx_device_bootstrap(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	पूर्णांक i;
	uपूर्णांक32_t old_count, count;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक need_reset = 0;

	need_reset = qla82xx_need_reset(ha);

	अगर (need_reset) अणु
		/* We are trying to perक्रमm a recovery here. */
		अगर (ha->flags.isp82xx_fw_hung)
			qla82xx_rom_lock_recovery(ha);
	पूर्ण अन्यथा  अणु
		old_count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);
		क्रम (i = 0; i < 10; i++) अणु
			msleep(200);
			count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);
			अगर (count != old_count) अणु
				rval = QLA_SUCCESS;
				जाओ dev_पढ़ोy;
			पूर्ण
		पूर्ण
		qla82xx_rom_lock_recovery(ha);
	पूर्ण

	/* set to DEV_INITIALIZING */
	ql_log(ql_log_info, vha, 0x009e,
	    "HW State: INITIALIZING.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_INITIALIZING);

	qla82xx_idc_unlock(ha);
	rval = qla82xx_start_firmware(vha);
	qla82xx_idc_lock(ha);

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_fatal, vha, 0x00ad,
		    "HW State: FAILED.\n");
		qla82xx_clear_drv_active(ha);
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_FAILED);
		वापस rval;
	पूर्ण

dev_पढ़ोy:
	ql_log(ql_log_info, vha, 0x00ae,
	    "HW State: READY.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_READY);

	वापस QLA_SUCCESS;
पूर्ण

/*
* qla82xx_need_qsnt_handler
*    Code to start quiescence sequence
*
* Note:
*      IDC lock must be held upon entry
*
* Return: व्योम
*/

अटल व्योम
qla82xx_need_qsnt_handler(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t dev_state, drv_state, drv_active;
	अचिन्हित दीर्घ reset_समयout;

	अगर (vha->flags.online) अणु
		/*Block any further I/O and रुको क्रम pending cmnds to complete*/
		qla2x00_quiesce_io(vha);
	पूर्ण

	/* Set the quiescence पढ़ोy bit */
	qla82xx_set_qsnt_पढ़ोy(ha);

	/*रुको क्रम 30 secs क्रम other functions to ack */
	reset_समयout = jअगरfies + (30 * HZ);

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	/* Its 2 that is written when qsnt is acked, moving one bit */
	drv_active = drv_active << 0x01;

	जबतक (drv_state != drv_active) अणु

		अगर (समय_after_eq(jअगरfies, reset_समयout)) अणु
			/* quiescence समयout, other functions didn't ack
			 * changing the state to DEV_READY
			 */
			ql_log(ql_log_info, vha, 0xb023,
			    "%s : QUIESCENT TIMEOUT DRV_ACTIVE:%d "
			    "DRV_STATE:%d.\n", QLA2XXX_DRIVER_NAME,
			    drv_active, drv_state);
			qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
			    QLA8XXX_DEV_READY);
			ql_log(ql_log_info, vha, 0xb025,
			    "HW State: DEV_READY.\n");
			qla82xx_idc_unlock(ha);
			qla2x00_perक्रमm_loop_resync(vha);
			qla82xx_idc_lock(ha);

			qla82xx_clear_qsnt_पढ़ोy(vha);
			वापस;
		पूर्ण

		qla82xx_idc_unlock(ha);
		msleep(1000);
		qla82xx_idc_lock(ha);

		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
		drv_active = drv_active << 0x01;
	पूर्ण
	dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	/* everyone acked so set the state to DEV_QUIESCENCE */
	अगर (dev_state == QLA8XXX_DEV_NEED_QUIESCENT) अणु
		ql_log(ql_log_info, vha, 0xb026,
		    "HW State: DEV_QUIESCENT.\n");
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_QUIESCENT);
	पूर्ण
पूर्ण

/*
* qla82xx_रुको_क्रम_state_change
*    Wait क्रम device state to change from given current state
*
* Note:
*     IDC lock must not be held upon entry
*
* Return:
*    Changed device state.
*/
uपूर्णांक32_t
qla82xx_रुको_क्रम_state_change(scsi_qla_host_t *vha, uपूर्णांक32_t curr_state)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t dev_state;

	करो अणु
		msleep(1000);
		qla82xx_idc_lock(ha);
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
		qla82xx_idc_unlock(ha);
	पूर्ण जबतक (dev_state == curr_state);

	वापस dev_state;
पूर्ण

व्योम
qla8xxx_dev_failed_handler(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Disable the board */
	ql_log(ql_log_fatal, vha, 0x00b8,
	    "Disabling the board.\n");

	अगर (IS_QLA82XX(ha)) अणु
		qla82xx_clear_drv_active(ha);
		qla82xx_idc_unlock(ha);
	पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
		qla8044_clear_drv_active(ha);
		qla8044_idc_unlock(ha);
	पूर्ण

	/* Set DEV_FAILED flag to disable समयr */
	vha->device_flags |= DFLG_DEV_FAILED;
	qla2x00_पात_all_cmds(vha, DID_NO_CONNECT << 16);
	qla2x00_mark_all_devices_lost(vha);
	vha->flags.online = 0;
	vha->flags.init_करोne = 0;
पूर्ण

/*
 * qla82xx_need_reset_handler
 *    Code to start reset sequence
 *
 * Note:
 *      IDC lock must be held upon entry
 *
 * Return:
 *    Success : 0
 *    Failed  : 1
 */
अटल व्योम
qla82xx_need_reset_handler(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t dev_state, drv_state, drv_active;
	uपूर्णांक32_t active_mask = 0;
	अचिन्हित दीर्घ reset_समयout;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];

	अगर (vha->flags.online) अणु
		qla82xx_idc_unlock(ha);
		qla2x00_पात_isp_cleanup(vha);
		ha->isp_ops->get_flash_version(vha, req->ring);
		ha->isp_ops->nvram_config(vha);
		qla82xx_idc_lock(ha);
	पूर्ण

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	अगर (!ha->flags.nic_core_reset_owner) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb028,
		    "reset_acknowledged by 0x%x\n", ha->portnum);
		qla82xx_set_rst_पढ़ोy(ha);
	पूर्ण अन्यथा अणु
		active_mask = ~(QLA82XX_DRV_ACTIVE << (ha->portnum * 4));
		drv_active &= active_mask;
		ql_dbg(ql_dbg_p3p, vha, 0xb029,
		    "active_mask: 0x%08x\n", active_mask);
	पूर्ण

	/* रुको क्रम 10 seconds क्रम reset ack from all functions */
	reset_समयout = jअगरfies + (ha->fcoe_reset_समयout * HZ);

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);

	ql_dbg(ql_dbg_p3p, vha, 0xb02a,
	    "drv_state: 0x%08x, drv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    drv_state, drv_active, dev_state, active_mask);

	जबतक (drv_state != drv_active &&
	    dev_state != QLA8XXX_DEV_INITIALIZING) अणु
		अगर (समय_after_eq(jअगरfies, reset_समयout)) अणु
			ql_log(ql_log_warn, vha, 0x00b5,
			    "Reset timeout.\n");
			अवरोध;
		पूर्ण
		qla82xx_idc_unlock(ha);
		msleep(1000);
		qla82xx_idc_lock(ha);
		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
		अगर (ha->flags.nic_core_reset_owner)
			drv_active &= active_mask;
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	पूर्ण

	ql_dbg(ql_dbg_p3p, vha, 0xb02b,
	    "drv_state: 0x%08x, drv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    drv_state, drv_active, dev_state, active_mask);

	ql_log(ql_log_info, vha, 0x00b6,
	    "Device state is 0x%x = %s.\n",
	    dev_state,
	    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");

	/* Force to DEV_COLD unless someone अन्यथा is starting a reset */
	अगर (dev_state != QLA8XXX_DEV_INITIALIZING &&
	    dev_state != QLA8XXX_DEV_COLD) अणु
		ql_log(ql_log_info, vha, 0x00b7,
		    "HW State: COLD/RE-INIT.\n");
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_COLD);
		qla82xx_set_rst_पढ़ोy(ha);
		अगर (ql2xmdenable) अणु
			अगर (qla82xx_md_collect(vha))
				ql_log(ql_log_warn, vha, 0xb02c,
				    "Minidump not collected.\n");
		पूर्ण अन्यथा
			ql_log(ql_log_warn, vha, 0xb04f,
			    "Minidump disabled.\n");
	पूर्ण
पूर्ण

पूर्णांक
qla82xx_check_md_needed(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t fw_major_version, fw_minor_version, fw_subminor_version;
	पूर्णांक rval = QLA_SUCCESS;

	fw_major_version = ha->fw_major_version;
	fw_minor_version = ha->fw_minor_version;
	fw_subminor_version = ha->fw_subminor_version;

	rval = qla2x00_get_fw_version(vha);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	अगर (ql2xmdenable) अणु
		अगर (!ha->fw_dumped) अणु
			अगर ((fw_major_version != ha->fw_major_version ||
			    fw_minor_version != ha->fw_minor_version ||
			    fw_subminor_version != ha->fw_subminor_version) ||
			    (ha->prev_minidump_failed)) अणु
				ql_dbg(ql_dbg_p3p, vha, 0xb02d,
				    "Firmware version differs Previous version: %d:%d:%d - New version: %d:%d:%d, prev_minidump_failed: %d.\n",
				    fw_major_version, fw_minor_version,
				    fw_subminor_version,
				    ha->fw_major_version,
				    ha->fw_minor_version,
				    ha->fw_subminor_version,
				    ha->prev_minidump_failed);
				/* Release MiniDump resources */
				qla82xx_md_मुक्त(vha);
				/* ALlocate MiniDump resources */
				qla82xx_md_prep(vha);
			पूर्ण
		पूर्ण अन्यथा
			ql_log(ql_log_info, vha, 0xb02e,
			    "Firmware dump available to retrieve\n");
	पूर्ण
	वापस rval;
पूर्ण


अटल पूर्णांक
qla82xx_check_fw_alive(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t fw_heartbeat_counter;
	पूर्णांक status = 0;

	fw_heartbeat_counter = qla82xx_rd_32(vha->hw,
		QLA82XX_PEG_ALIVE_COUNTER);
	/* all 0xff, assume AER/EEH in progress, ignore */
	अगर (fw_heartbeat_counter == 0xffffffff) अणु
		ql_dbg(ql_dbg_समयr, vha, 0x6003,
		    "FW heartbeat counter is 0xffffffff, "
		    "returning status=%d.\n", status);
		वापस status;
	पूर्ण
	अगर (vha->fw_heartbeat_counter == fw_heartbeat_counter) अणु
		vha->seconds_since_last_heartbeat++;
		/* FW not alive after 2 seconds */
		अगर (vha->seconds_since_last_heartbeat == 2) अणु
			vha->seconds_since_last_heartbeat = 0;
			status = 1;
		पूर्ण
	पूर्ण अन्यथा
		vha->seconds_since_last_heartbeat = 0;
	vha->fw_heartbeat_counter = fw_heartbeat_counter;
	अगर (status)
		ql_dbg(ql_dbg_समयr, vha, 0x6004,
		    "Returning status=%d.\n", status);
	वापस status;
पूर्ण

/*
 * qla82xx_device_state_handler
 *	Main state handler
 *
 * Note:
 *      IDC lock must be held upon entry
 *
 * Return:
 *    Success : 0
 *    Failed  : 1
 */
पूर्णांक
qla82xx_device_state_handler(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t dev_state;
	uपूर्णांक32_t old_dev_state;
	पूर्णांक rval = QLA_SUCCESS;
	अचिन्हित दीर्घ dev_init_समयout;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक loopcount = 0;

	qla82xx_idc_lock(ha);
	अगर (!vha->flags.init_करोne) अणु
		qla82xx_set_drv_active(vha);
		qla82xx_set_idc_version(vha);
	पूर्ण

	dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	old_dev_state = dev_state;
	ql_log(ql_log_info, vha, 0x009b,
	    "Device state is 0x%x = %s.\n",
	    dev_state,
	    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");

	/* रुको क्रम 30 seconds क्रम device to go पढ़ोy */
	dev_init_समयout = jअगरfies + (ha->fcoe_dev_init_समयout * HZ);

	जबतक (1) अणु

		अगर (समय_after_eq(jअगरfies, dev_init_समयout)) अणु
			ql_log(ql_log_fatal, vha, 0x009c,
			    "Device init failed.\n");
			rval = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
		अगर (old_dev_state != dev_state) अणु
			loopcount = 0;
			old_dev_state = dev_state;
		पूर्ण
		अगर (loopcount < 5) अणु
			ql_log(ql_log_info, vha, 0x009d,
			    "Device state is 0x%x = %s.\n",
			    dev_state,
			    dev_state < MAX_STATES ? qdev_state(dev_state) :
			    "Unknown");
		पूर्ण

		चयन (dev_state) अणु
		हाल QLA8XXX_DEV_READY:
			ha->flags.nic_core_reset_owner = 0;
			जाओ rel_lock;
		हाल QLA8XXX_DEV_COLD:
			rval = qla82xx_device_bootstrap(vha);
			अवरोध;
		हाल QLA8XXX_DEV_INITIALIZING:
			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_RESET:
			अगर (!ql2xकरोntresethba)
				qla82xx_need_reset_handler(vha);
			अन्यथा अणु
				qla82xx_idc_unlock(ha);
				msleep(1000);
				qla82xx_idc_lock(ha);
			पूर्ण
			dev_init_समयout = jअगरfies +
			    (ha->fcoe_dev_init_समयout * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_NEED_QUIESCENT:
			qla82xx_need_qsnt_handler(vha);
			/* Reset समयout value after quiescence handler */
			dev_init_समयout = jअगरfies + (ha->fcoe_dev_init_समयout
							 * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_QUIESCENT:
			/* Owner will निकास and other will रुको क्रम the state
			 * to get changed
			 */
			अगर (ha->flags.quiesce_owner)
				जाओ rel_lock;

			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);

			/* Reset समयout value after quiescence handler */
			dev_init_समयout = jअगरfies + (ha->fcoe_dev_init_समयout
							 * HZ);
			अवरोध;
		हाल QLA8XXX_DEV_FAILED:
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			जाओ निकास;
		शेष:
			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);
		पूर्ण
		loopcount++;
	पूर्ण
rel_lock:
	qla82xx_idc_unlock(ha);
निकास:
	वापस rval;
पूर्ण

अटल पूर्णांक qla82xx_check_temp(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t temp, temp_state, temp_val;
	काष्ठा qla_hw_data *ha = vha->hw;

	temp = qla82xx_rd_32(ha, CRB_TEMP_STATE);
	temp_state = qla82xx_get_temp_state(temp);
	temp_val = qla82xx_get_temp_val(temp);

	अगर (temp_state == QLA82XX_TEMP_PANIC) अणु
		ql_log(ql_log_warn, vha, 0x600e,
		    "Device temperature %d degrees C exceeds "
		    " maximum allowed. Hardware has been shut down.\n",
		    temp_val);
		वापस 1;
	पूर्ण अन्यथा अगर (temp_state == QLA82XX_TEMP_WARN) अणु
		ql_log(ql_log_warn, vha, 0x600f,
		    "Device temperature %d degrees C exceeds "
		    "operating range. Immediate action needed.\n",
		    temp_val);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qla82xx_पढ़ो_temperature(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t temp;

	temp = qla82xx_rd_32(vha->hw, CRB_TEMP_STATE);
	वापस qla82xx_get_temp_val(temp);
पूर्ण

व्योम qla82xx_clear_pending_mbx(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (ha->flags.mbox_busy) अणु
		ha->flags.mbox_पूर्णांक = 1;
		ha->flags.mbox_busy = 0;
		ql_log(ql_log_warn, vha, 0x6010,
		    "Doing premature completion of mbx command.\n");
		अगर (test_and_clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags))
			complete(&ha->mbx_पूर्णांकr_comp);
	पूर्ण
पूर्ण

व्योम qla82xx_watchकरोg(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t dev_state, halt_status;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* करोn't poll अगर reset is going on */
	अगर (!ha->flags.nic_core_reset_hdlr_active) अणु
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
		अगर (qla82xx_check_temp(vha)) अणु
			set_bit(ISP_UNRECOVERABLE, &vha->dpc_flags);
			ha->flags.isp82xx_fw_hung = 1;
			qla82xx_clear_pending_mbx(vha);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_RESET &&
		    !test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags)) अणु
			ql_log(ql_log_warn, vha, 0x6001,
			    "Adapter reset needed.\n");
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_QUIESCENT &&
			!test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags)) अणु
			ql_log(ql_log_warn, vha, 0x6002,
			    "Quiescent needed.\n");
			set_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_FAILED &&
			!test_bit(ISP_UNRECOVERABLE, &vha->dpc_flags) &&
			vha->flags.online == 1) अणु
			ql_log(ql_log_warn, vha, 0xb055,
			    "Adapter state is failed. Offlining.\n");
			set_bit(ISP_UNRECOVERABLE, &vha->dpc_flags);
			ha->flags.isp82xx_fw_hung = 1;
			qla82xx_clear_pending_mbx(vha);
		पूर्ण अन्यथा अणु
			अगर (qla82xx_check_fw_alive(vha)) अणु
				ql_dbg(ql_dbg_समयr, vha, 0x6011,
				    "disabling pause transmit on port 0 & 1.\n");
				qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x98,
				    CRB_NIU_XG_PAUSE_CTL_P0|CRB_NIU_XG_PAUSE_CTL_P1);
				halt_status = qla82xx_rd_32(ha,
				    QLA82XX_PEG_HALT_STATUS1);
				ql_log(ql_log_info, vha, 0x6005,
				    "dumping hw/fw registers:.\n "
				    " PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,.\n "
				    " PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,.\n "
				    " PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,.\n "
				    " PEG_NET_4_PC: 0x%x.\n", halt_status,
				    qla82xx_rd_32(ha, QLA82XX_PEG_HALT_STATUS2),
				    qla82xx_rd_32(ha,
					    QLA82XX_CRB_PEG_NET_0 + 0x3c),
				    qla82xx_rd_32(ha,
					    QLA82XX_CRB_PEG_NET_1 + 0x3c),
				    qla82xx_rd_32(ha,
					    QLA82XX_CRB_PEG_NET_2 + 0x3c),
				    qla82xx_rd_32(ha,
					    QLA82XX_CRB_PEG_NET_3 + 0x3c),
				    qla82xx_rd_32(ha,
					    QLA82XX_CRB_PEG_NET_4 + 0x3c));
				अगर (((halt_status & 0x1fffff00) >> 8) == 0x67)
					ql_log(ql_log_warn, vha, 0xb052,
					    "Firmware aborted with "
					    "error code 0x00006700. Device is "
					    "being reset.\n");
				अगर (halt_status & HALT_STATUS_UNRECOVERABLE) अणु
					set_bit(ISP_UNRECOVERABLE,
					    &vha->dpc_flags);
				पूर्ण अन्यथा अणु
					ql_log(ql_log_info, vha, 0x6006,
					    "Detect abort  needed.\n");
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				पूर्ण
				ha->flags.isp82xx_fw_hung = 1;
				ql_log(ql_log_warn, vha, 0x6007, "Firmware hung.\n");
				qla82xx_clear_pending_mbx(vha);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक qla82xx_load_risc(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr)
अणु
	पूर्णांक rval = -1;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA82XX(ha))
		rval = qla82xx_device_state_handler(vha);
	अन्यथा अगर (IS_QLA8044(ha)) अणु
		qla8044_idc_lock(ha);
		/* Decide the reset ownership */
		qla83xx_reset_ownership(vha);
		qla8044_idc_unlock(ha);
		rval = qla8044_device_state_handler(vha);
	पूर्ण
	वापस rval;
पूर्ण

व्योम
qla82xx_set_reset_owner(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t dev_state = 0;

	अगर (IS_QLA82XX(ha))
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	अन्यथा अगर (IS_QLA8044(ha))
		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

	अगर (dev_state == QLA8XXX_DEV_READY) अणु
		ql_log(ql_log_info, vha, 0xb02f,
		    "HW State: NEED RESET\n");
		अगर (IS_QLA82XX(ha)) अणु
			qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
			    QLA8XXX_DEV_NEED_RESET);
			ha->flags.nic_core_reset_owner = 1;
			ql_dbg(ql_dbg_p3p, vha, 0xb030,
			    "reset_owner is 0x%x\n", ha->portnum);
		पूर्ण अन्यथा अगर (IS_QLA8044(ha))
			qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
			    QLA8XXX_DEV_NEED_RESET);
	पूर्ण अन्यथा
		ql_log(ql_log_info, vha, 0xb031,
		    "Device state is 0x%x = %s.\n",
		    dev_state,
		    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");
पूर्ण

/*
 *  qla82xx_पात_isp
 *      Resets ISP and पातs all outstanding commands.
 *
 * Input:
 *      ha           = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक
qla82xx_पात_isp(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = -1;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_log(ql_log_warn, vha, 0x8024,
		    "Device in failed state, exiting.\n");
		वापस QLA_SUCCESS;
	पूर्ण
	ha->flags.nic_core_reset_hdlr_active = 1;

	qla82xx_idc_lock(ha);
	qla82xx_set_reset_owner(vha);
	qla82xx_idc_unlock(ha);

	अगर (IS_QLA82XX(ha))
		rval = qla82xx_device_state_handler(vha);
	अन्यथा अगर (IS_QLA8044(ha)) अणु
		qla8044_idc_lock(ha);
		/* Decide the reset ownership */
		qla83xx_reset_ownership(vha);
		qla8044_idc_unlock(ha);
		rval = qla8044_device_state_handler(vha);
	पूर्ण

	qla82xx_idc_lock(ha);
	qla82xx_clear_rst_पढ़ोy(ha);
	qla82xx_idc_unlock(ha);

	अगर (rval == QLA_SUCCESS) अणु
		ha->flags.isp82xx_fw_hung = 0;
		ha->flags.nic_core_reset_hdlr_active = 0;
		qla82xx_restart_isp(vha);
	पूर्ण

	अगर (rval) अणु
		vha->flags.online = 1;
		अगर (test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु
			अगर (ha->isp_पात_cnt == 0) अणु
				ql_log(ql_log_warn, vha, 0x8027,
				    "ISP error recover failed - board "
				    "disabled.\n");
				/*
				 * The next call disables the board
				 * completely.
				 */
				ha->isp_ops->reset_adapter(vha);
				vha->flags.online = 0;
				clear_bit(ISP_ABORT_RETRY,
				    &vha->dpc_flags);
				rval = QLA_SUCCESS;
			पूर्ण अन्यथा अणु /* schedule another ISP पात */
				ha->isp_पात_cnt--;
				ql_log(ql_log_warn, vha, 0x8036,
				    "ISP abort - retry remaining %d.\n",
				    ha->isp_पात_cnt);
				rval = QLA_FUNCTION_FAILED;
			पूर्ण
		पूर्ण अन्यथा अणु
			ha->isp_पात_cnt = MAX_RETRIES_OF_ISP_ABORT;
			ql_dbg(ql_dbg_taskm, vha, 0x8029,
			    "ISP error recovery - retrying (%d) more times.\n",
			    ha->isp_पात_cnt);
			set_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण
	वापस rval;
पूर्ण

/*
 *  qla82xx_fcoe_ctx_reset
 *      Perक्रमm a quick reset and पातs all outstanding commands.
 *      This will only perक्रमm an FCoE context reset and aव्योमs a full blown
 *      chip reset.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *      is_reset_path = flag क्रम identअगरying the reset path.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक qla82xx_fcoe_ctx_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (vha->flags.online) अणु
		/* Abort all outstanding commands, so as to be requeued later */
		qla2x00_पात_isp_cleanup(vha);
	पूर्ण

	/* Stop currently executing firmware.
	 * This will destroy existing FCoE context at the F/W end.
	 */
	qla2x00_try_to_stop_firmware(vha);

	/* Restart. Creates a new FCoE context on INIT_FIRMWARE. */
	rval = qla82xx_restart_isp(vha);

	वापस rval;
पूर्ण

/*
 * qla2x00_रुको_क्रम_fcoe_ctx_reset
 *    Wait till the FCoE context is reset.
 *
 * Note:
 *    Does context चयनing here.
 *    Release SPIN_LOCK (अगर any) beक्रमe calling this routine.
 *
 * Return:
 *    Success (fcoe_ctx reset is करोne) : 0
 *    Failed  (fcoe_ctx reset not completed within max loop timout ) : 1
 */
पूर्णांक qla2x00_रुको_क्रम_fcoe_ctx_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक status = QLA_FUNCTION_FAILED;
	अचिन्हित दीर्घ रुको_reset;

	रुको_reset = jअगरfies + (MAX_LOOP_TIMEOUT * HZ);
	जबतक ((test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags) ||
	    test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
	    && समय_beक्रमe(jअगरfies, रुको_reset)) अणु

		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(HZ);

		अगर (!test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags) &&
		    !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) अणु
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण
	ql_dbg(ql_dbg_p3p, vha, 0xb027,
	       "%s: status=%d.\n", __func__, status);

	वापस status;
पूर्ण

व्योम
qla82xx_chip_reset_cleanup(scsi_qla_host_t *vha)
अणु
	पूर्णांक i, fw_state = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Check अगर 82XX firmware is alive or not
	 * We may have arrived here from NEED_RESET
	 * detection only
	 */
	अगर (!ha->flags.isp82xx_fw_hung) अणु
		क्रम (i = 0; i < 2; i++) अणु
			msleep(1000);
			अगर (IS_QLA82XX(ha))
				fw_state = qla82xx_check_fw_alive(vha);
			अन्यथा अगर (IS_QLA8044(ha))
				fw_state = qla8044_check_fw_alive(vha);
			अगर (fw_state) अणु
				ha->flags.isp82xx_fw_hung = 1;
				qla82xx_clear_pending_mbx(vha);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	ql_dbg(ql_dbg_init, vha, 0x00b0,
	    "Entered %s fw_hung=%d.\n",
	    __func__, ha->flags.isp82xx_fw_hung);

	/* Abort all commands gracefully अगर fw NOT hung */
	अगर (!ha->flags.isp82xx_fw_hung) अणु
		पूर्णांक cnt, que;
		srb_t *sp;
		काष्ठा req_que *req;

		spin_lock_irqsave(&ha->hardware_lock, flags);
		क्रम (que = 0; que < ha->max_req_queues; que++) अणु
			req = ha->req_q_map[que];
			अगर (!req)
				जारी;
			क्रम (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) अणु
				sp = req->outstanding_cmds[cnt];
				अगर (sp) अणु
					अगर ((!sp->u.scmd.crc_ctx ||
					    (sp->flags &
						SRB_FCP_CMND_DMA_VALID)) &&
						!ha->flags.isp82xx_fw_hung) अणु
						spin_unlock_irqrestore(
						    &ha->hardware_lock, flags);
						अगर (ha->isp_ops->पात_command(sp)) अणु
							ql_log(ql_log_info, vha,
							    0x00b1,
							    "mbx abort failed.\n");
						पूर्ण अन्यथा अणु
							ql_log(ql_log_info, vha,
							    0x00b2,
							    "mbx abort success.\n");
						पूर्ण
						spin_lock_irqsave(&ha->hardware_lock, flags);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		/* Wait क्रम pending cmds (physical and भव) to complete */
		अगर (qla2x00_eh_रुको_क्रम_pending_commands(vha, 0, 0,
		    WAIT_HOST) == QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_init, vha, 0x00b3,
			    "Done wait for "
			    "pending commands.\n");
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(true);
		पूर्ण
	पूर्ण
पूर्ण

/* Minidump related functions */
अटल पूर्णांक
qla82xx_minidump_process_control(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla82xx_md_entry_crb *crb_entry;
	uपूर्णांक32_t पढ़ो_value, opcode, poll_समय;
	uपूर्णांक32_t addr, index, crb_addr;
	अचिन्हित दीर्घ wसमय;
	काष्ठा qla82xx_md_ढाँचा_hdr *पंचांगplt_hdr;
	uपूर्णांक32_t rval = QLA_SUCCESS;
	पूर्णांक i;

	पंचांगplt_hdr = (काष्ठा qla82xx_md_ढाँचा_hdr *)ha->md_पंचांगplt_hdr;
	crb_entry = (काष्ठा qla82xx_md_entry_crb *)entry_hdr;
	crb_addr = crb_entry->addr;

	क्रम (i = 0; i < crb_entry->op_count; i++) अणु
		opcode = crb_entry->crb_ctrl.opcode;
		अगर (opcode & QLA82XX_DBG_OPCODE_WR) अणु
			qla82xx_md_rw_32(ha, crb_addr,
			    crb_entry->value_1, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_WR;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_RW) अणु
			पढ़ो_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			qla82xx_md_rw_32(ha, crb_addr, पढ़ो_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_RW;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_AND) अणु
			पढ़ो_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			पढ़ो_value &= crb_entry->value_2;
			opcode &= ~QLA82XX_DBG_OPCODE_AND;
			अगर (opcode & QLA82XX_DBG_OPCODE_OR) अणु
				पढ़ो_value |= crb_entry->value_3;
				opcode &= ~QLA82XX_DBG_OPCODE_OR;
			पूर्ण
			qla82xx_md_rw_32(ha, crb_addr, पढ़ो_value, 1);
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_OR) अणु
			पढ़ो_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			पढ़ो_value |= crb_entry->value_3;
			qla82xx_md_rw_32(ha, crb_addr, पढ़ो_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_OR;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_POLL) अणु
			poll_समय = crb_entry->crb_strd.poll_समयout;
			wसमय = jअगरfies + poll_समय;
			पढ़ो_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);

			करो अणु
				अगर ((पढ़ो_value & crb_entry->value_2)
				    == crb_entry->value_1)
					अवरोध;
				अन्यथा अगर (समय_after_eq(jअगरfies, wसमय)) अणु
					/* capturing dump failed */
					rval = QLA_FUNCTION_FAILED;
					अवरोध;
				पूर्ण अन्यथा
					पढ़ो_value = qla82xx_md_rw_32(ha,
					    crb_addr, 0, 0);
			पूर्ण जबतक (1);
			opcode &= ~QLA82XX_DBG_OPCODE_POLL;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_RDSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा
				addr = crb_addr;

			पढ़ो_value = qla82xx_md_rw_32(ha, addr, 0, 0);
			index = crb_entry->crb_ctrl.state_index_v;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
			opcode &= ~QLA82XX_DBG_OPCODE_RDSTATE;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_WRSTATE) अणु
			अगर (crb_entry->crb_strd.state_index_a) अणु
				index = crb_entry->crb_strd.state_index_a;
				addr = पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा
				addr = crb_addr;

			अगर (crb_entry->crb_ctrl.state_index_v) अणु
				index = crb_entry->crb_ctrl.state_index_v;
				पढ़ो_value =
				    पंचांगplt_hdr->saved_state_array[index];
			पूर्ण अन्यथा
				पढ़ो_value = crb_entry->value_1;

			qla82xx_md_rw_32(ha, addr, पढ़ो_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_WRSTATE;
		पूर्ण

		अगर (opcode & QLA82XX_DBG_OPCODE_MDSTATE) अणु
			index = crb_entry->crb_ctrl.state_index_v;
			पढ़ो_value = पंचांगplt_hdr->saved_state_array[index];
			पढ़ो_value <<= crb_entry->crb_ctrl.shl;
			पढ़ो_value >>= crb_entry->crb_ctrl.shr;
			अगर (crb_entry->value_2)
				पढ़ो_value &= crb_entry->value_2;
			पढ़ो_value |= crb_entry->value_3;
			पढ़ो_value += crb_entry->value_1;
			पंचांगplt_hdr->saved_state_array[index] = पढ़ो_value;
			opcode &= ~QLA82XX_DBG_OPCODE_MDSTATE;
		पूर्ण
		crb_addr += crb_entry->crb_strd.addr_stride;
	पूर्ण
	वापस rval;
पूर्ण

अटल व्योम
qla82xx_minidump_process_rकरोcm(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla82xx_md_entry_rकरोcm *ocm_hdr;
	__le32 *data_ptr = *d_ptr;

	ocm_hdr = (काष्ठा qla82xx_md_entry_rकरोcm *)entry_hdr;
	r_addr = ocm_hdr->पढ़ो_addr;
	r_stride = ocm_hdr->पढ़ो_addr_stride;
	loop_cnt = ocm_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		r_value = rd_reg_dword(r_addr + ha->nx_pcibase);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla82xx_minidump_process_rdmux(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t r_addr, s_stride, s_addr, s_value, loop_cnt, i, r_value;
	काष्ठा qla82xx_md_entry_mux *mux_hdr;
	__le32 *data_ptr = *d_ptr;

	mux_hdr = (काष्ठा qla82xx_md_entry_mux *)entry_hdr;
	r_addr = mux_hdr->पढ़ो_addr;
	s_addr = mux_hdr->select_addr;
	s_stride = mux_hdr->select_value_stride;
	s_value = mux_hdr->select_value;
	loop_cnt = mux_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla82xx_md_rw_32(ha, s_addr, s_value, 1);
		r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
		*data_ptr++ = cpu_to_le32(s_value);
		*data_ptr++ = cpu_to_le32(r_value);
		s_value += s_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla82xx_minidump_process_rdcrb(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t r_addr, r_stride, loop_cnt, i, r_value;
	काष्ठा qla82xx_md_entry_crb *crb_hdr;
	__le32 *data_ptr = *d_ptr;

	crb_hdr = (काष्ठा qla82xx_md_entry_crb *)entry_hdr;
	r_addr = crb_hdr->addr;
	r_stride = crb_hdr->crb_strd.addr_stride;
	loop_cnt = crb_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
		*data_ptr++ = cpu_to_le32(r_addr);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल पूर्णांक
qla82xx_minidump_process_l2tag(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	अचिन्हित दीर्घ p_रुको, w_समय, p_mask;
	uपूर्णांक32_t c_value_w, c_value_r;
	काष्ठा qla82xx_md_entry_cache *cache_hdr;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	__le32 *data_ptr = *d_ptr;

	cache_hdr = (काष्ठा qla82xx_md_entry_cache *)entry_hdr;
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
		qla82xx_md_rw_32(ha, t_r_addr, t_value, 1);
		अगर (c_value_w)
			qla82xx_md_rw_32(ha, c_addr, c_value_w, 1);

		अगर (p_mask) अणु
			w_समय = jअगरfies + p_रुको;
			करो अणु
				c_value_r = qla82xx_md_rw_32(ha, c_addr, 0, 0);
				अगर ((c_value_r & p_mask) == 0)
					अवरोध;
				अन्यथा अगर (समय_after_eq(jअगरfies, w_समय)) अणु
					/* capturing dump failed */
					ql_dbg(ql_dbg_p3p, vha, 0xb032,
					    "c_value_r: 0x%x, poll_mask: 0x%lx, "
					    "w_time: 0x%lx\n",
					    c_value_r, p_mask, w_समय);
					वापस rval;
				पूर्ण
			पूर्ण जबतक (1);
		पूर्ण

		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			r_value = qla82xx_md_rw_32(ha, addr, 0, 0);
			*data_ptr++ = cpu_to_le32(r_value);
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम
qla82xx_minidump_process_l1cache(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t addr, r_addr, c_addr, t_r_addr;
	uपूर्णांक32_t i, k, loop_count, t_value, r_cnt, r_value;
	uपूर्णांक32_t c_value_w;
	काष्ठा qla82xx_md_entry_cache *cache_hdr;
	__le32 *data_ptr = *d_ptr;

	cache_hdr = (काष्ठा qla82xx_md_entry_cache *)entry_hdr;
	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->पढ़ो_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.ग_लिखो_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->पढ़ो_ctrl.पढ़ो_addr_cnt;

	क्रम (i = 0; i < loop_count; i++) अणु
		qla82xx_md_rw_32(ha, t_r_addr, t_value, 1);
		qla82xx_md_rw_32(ha, c_addr, c_value_w, 1);
		addr = r_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			r_value = qla82xx_md_rw_32(ha, addr, 0, 0);
			*data_ptr++ = cpu_to_le32(r_value);
			addr += cache_hdr->पढ़ो_ctrl.पढ़ो_addr_stride;
		पूर्ण
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla82xx_minidump_process_queue(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t s_addr, r_addr;
	uपूर्णांक32_t r_stride, r_value, r_cnt, qid = 0;
	uपूर्णांक32_t i, k, loop_cnt;
	काष्ठा qla82xx_md_entry_queue *q_hdr;
	__le32 *data_ptr = *d_ptr;

	q_hdr = (काष्ठा qla82xx_md_entry_queue *)entry_hdr;
	s_addr = q_hdr->select_addr;
	r_cnt = q_hdr->rd_strd.पढ़ो_addr_cnt;
	r_stride = q_hdr->rd_strd.पढ़ो_addr_stride;
	loop_cnt = q_hdr->op_count;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla82xx_md_rw_32(ha, s_addr, qid, 1);
		r_addr = q_hdr->पढ़ो_addr;
		क्रम (k = 0; k < r_cnt; k++) अणु
			r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
			*data_ptr++ = cpu_to_le32(r_value);
			r_addr += r_stride;
		पूर्ण
		qid += q_hdr->q_strd.queue_id_stride;
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल व्योम
qla82xx_minidump_process_rdrom(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t r_addr, r_value;
	uपूर्णांक32_t i, loop_cnt;
	काष्ठा qla82xx_md_entry_rdrom *rom_hdr;
	__le32 *data_ptr = *d_ptr;

	rom_hdr = (काष्ठा qla82xx_md_entry_rdrom *)entry_hdr;
	r_addr = rom_hdr->पढ़ो_addr;
	loop_cnt = rom_hdr->पढ़ो_data_size/माप(uपूर्णांक32_t);

	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla82xx_md_rw_32(ha, MD_सूचीECT_ROM_WINDOW,
		    (r_addr & 0xFFFF0000), 1);
		r_value = qla82xx_md_rw_32(ha,
		    MD_सूचीECT_ROM_READ_BASE +
		    (r_addr & 0x0000FFFF), 0, 0);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += माप(uपूर्णांक32_t);
	पूर्ण
	*d_ptr = data_ptr;
पूर्ण

अटल पूर्णांक
qla82xx_minidump_process_rdmem(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, __le32 **d_ptr)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t r_addr, r_value, r_data;
	uपूर्णांक32_t i, j, loop_cnt;
	काष्ठा qla82xx_md_entry_rdmem *m_hdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	__le32 *data_ptr = *d_ptr;

	m_hdr = (काष्ठा qla82xx_md_entry_rdmem *)entry_hdr;
	r_addr = m_hdr->पढ़ो_addr;
	loop_cnt = m_hdr->पढ़ो_data_size/16;

	अगर (r_addr & 0xf) अणु
		ql_log(ql_log_warn, vha, 0xb033,
		    "Read addr 0x%x not 16 bytes aligned\n", r_addr);
		वापस rval;
	पूर्ण

	अगर (m_hdr->पढ़ो_data_size % 16) अणु
		ql_log(ql_log_warn, vha, 0xb034,
		    "Read data[0x%x] not multiple of 16 bytes\n",
		    m_hdr->पढ़ो_data_size);
		वापस rval;
	पूर्ण

	ql_dbg(ql_dbg_p3p, vha, 0xb035,
	    "[%s]: rdmem_addr: 0x%x, read_data_size: 0x%x, loop_cnt: 0x%x\n",
	    __func__, r_addr, m_hdr->पढ़ो_data_size, loop_cnt);

	ग_लिखो_lock_irqsave(&ha->hw_lock, flags);
	क्रम (i = 0; i < loop_cnt; i++) अणु
		qla82xx_md_rw_32(ha, MD_MIU_TEST_AGT_ADDR_LO, r_addr, 1);
		r_value = 0;
		qla82xx_md_rw_32(ha, MD_MIU_TEST_AGT_ADDR_HI, r_value, 1);
		r_value = MIU_TA_CTL_ENABLE;
		qla82xx_md_rw_32(ha, MD_MIU_TEST_AGT_CTRL, r_value, 1);
		r_value = MIU_TA_CTL_START | MIU_TA_CTL_ENABLE;
		qla82xx_md_rw_32(ha, MD_MIU_TEST_AGT_CTRL, r_value, 1);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			r_value = qla82xx_md_rw_32(ha,
			    MD_MIU_TEST_AGT_CTRL, 0, 0);
			अगर ((r_value & MIU_TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		अगर (j >= MAX_CTL_CHECK) अणु
			prपूर्णांकk_ratelimited(KERN_ERR
			    "failed to read through agent\n");
			ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
			वापस rval;
		पूर्ण

		क्रम (j = 0; j < 4; j++) अणु
			r_data = qla82xx_md_rw_32(ha,
			    MD_MIU_TEST_AGT_RDDATA[j], 0, 0);
			*data_ptr++ = cpu_to_le32(r_data);
		पूर्ण
		r_addr += 16;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ha->hw_lock, flags);
	*d_ptr = data_ptr;
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla82xx_validate_ढाँचा_chksum(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक64_t chksum = 0;
	uपूर्णांक32_t *d_ptr = (uपूर्णांक32_t *)ha->md_पंचांगplt_hdr;
	पूर्णांक count = ha->md_ढाँचा_size/माप(uपूर्णांक32_t);

	जबतक (count-- > 0)
		chksum += *d_ptr++;
	जबतक (chksum >> 32)
		chksum = (chksum & 0xFFFFFFFF) + (chksum >> 32);
	वापस ~chksum;
पूर्ण

अटल व्योम
qla82xx_mark_entry_skipped(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, पूर्णांक index)
अणु
	entry_hdr->d_ctrl.driver_flags |= QLA82XX_DBG_SKIPPED_FLAG;
	ql_dbg(ql_dbg_p3p, vha, 0xb036,
	    "Skipping entry[%d]: "
	    "ETYPE[0x%x]-ELEVEL[0x%x]\n",
	    index, entry_hdr->entry_type,
	    entry_hdr->d_ctrl.entry_capture_mask);
पूर्ण

पूर्णांक
qla82xx_md_collect(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक no_entry_hdr = 0;
	qla82xx_md_entry_hdr_t *entry_hdr;
	काष्ठा qla82xx_md_ढाँचा_hdr *पंचांगplt_hdr;
	__le32 *data_ptr;
	uपूर्णांक32_t total_data_size = 0, f_capture_mask, data_collected = 0;
	पूर्णांक i = 0, rval = QLA_FUNCTION_FAILED;

	पंचांगplt_hdr = (काष्ठा qla82xx_md_ढाँचा_hdr *)ha->md_पंचांगplt_hdr;
	data_ptr = ha->md_dump;

	अगर (ha->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xb037,
		    "Firmware has been previously dumped (%p) "
		    "-- ignoring request.\n", ha->fw_dump);
		जाओ md_failed;
	पूर्ण

	ha->fw_dumped = false;

	अगर (!ha->md_पंचांगplt_hdr || !ha->md_dump) अणु
		ql_log(ql_log_warn, vha, 0xb038,
		    "Memory not allocated for minidump capture\n");
		जाओ md_failed;
	पूर्ण

	अगर (ha->flags.isp82xx_no_md_cap) अणु
		ql_log(ql_log_warn, vha, 0xb054,
		    "Forced reset from application, "
		    "ignore minidump capture\n");
		ha->flags.isp82xx_no_md_cap = 0;
		जाओ md_failed;
	पूर्ण

	अगर (qla82xx_validate_ढाँचा_chksum(vha)) अणु
		ql_log(ql_log_info, vha, 0xb039,
		    "Template checksum validation error\n");
		जाओ md_failed;
	पूर्ण

	no_entry_hdr = पंचांगplt_hdr->num_of_entries;
	ql_dbg(ql_dbg_p3p, vha, 0xb03a,
	    "No of entry headers in Template: 0x%x\n", no_entry_hdr);

	ql_dbg(ql_dbg_p3p, vha, 0xb03b,
	    "Capture Mask obtained: 0x%x\n", पंचांगplt_hdr->capture_debug_level);

	f_capture_mask = पंचांगplt_hdr->capture_debug_level & 0xFF;

	/* Validate whether required debug level is set */
	अगर ((f_capture_mask & 0x3) != 0x3) अणु
		ql_log(ql_log_warn, vha, 0xb03c,
		    "Minimum required capture mask[0x%x] level not set\n",
		    f_capture_mask);
		जाओ md_failed;
	पूर्ण
	पंचांगplt_hdr->driver_capture_mask = ql2xmdcapmask;

	पंचांगplt_hdr->driver_info[0] = vha->host_no;
	पंचांगplt_hdr->driver_info[1] = (QLA_DRIVER_MAJOR_VER << 24) |
	    (QLA_DRIVER_MINOR_VER << 16) | (QLA_DRIVER_PATCH_VER << 8) |
	    QLA_DRIVER_BETA_VER;

	total_data_size = ha->md_dump_size;

	ql_dbg(ql_dbg_p3p, vha, 0xb03d,
	    "Total minidump data_size 0x%x to be captured\n", total_data_size);

	/* Check whether ढाँचा obtained is valid */
	अगर (पंचांगplt_hdr->entry_type != QLA82XX_TLHDR) अणु
		ql_log(ql_log_warn, vha, 0xb04e,
		    "Bad template header entry type: 0x%x obtained\n",
		    पंचांगplt_hdr->entry_type);
		जाओ md_failed;
	पूर्ण

	entry_hdr = (qla82xx_md_entry_hdr_t *)
	    (((uपूर्णांक8_t *)ha->md_पंचांगplt_hdr) + पंचांगplt_hdr->first_entry_offset);

	/* Walk through the entry headers */
	क्रम (i = 0; i < no_entry_hdr; i++) अणु

		अगर (data_collected > total_data_size) अणु
			ql_log(ql_log_warn, vha, 0xb03e,
			    "More MiniDump data collected: [0x%x]\n",
			    data_collected);
			जाओ md_failed;
		पूर्ण

		अगर (!(entry_hdr->d_ctrl.entry_capture_mask &
		    ql2xmdcapmask)) अणु
			entry_hdr->d_ctrl.driver_flags |=
			    QLA82XX_DBG_SKIPPED_FLAG;
			ql_dbg(ql_dbg_p3p, vha, 0xb03f,
			    "Skipping entry[%d]: "
			    "ETYPE[0x%x]-ELEVEL[0x%x]\n",
			    i, entry_hdr->entry_type,
			    entry_hdr->d_ctrl.entry_capture_mask);
			जाओ skip_nxt_entry;
		पूर्ण

		ql_dbg(ql_dbg_p3p, vha, 0xb040,
		    "[%s]: data ptr[%d]: %p, entry_hdr: %p\n"
		    "entry_type: 0x%x, capture_mask: 0x%x\n",
		    __func__, i, data_ptr, entry_hdr,
		    entry_hdr->entry_type,
		    entry_hdr->d_ctrl.entry_capture_mask);

		ql_dbg(ql_dbg_p3p, vha, 0xb041,
		    "Data collected: [0x%x], Dump size left:[0x%x]\n",
		    data_collected, (ha->md_dump_size - data_collected));

		/* Decode the entry type and take
		 * required action to capture debug data */
		चयन (entry_hdr->entry_type) अणु
		हाल QLA82XX_RDEND:
			qla82xx_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		हाल QLA82XX_CNTRL:
			rval = qla82xx_minidump_process_control(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla82xx_mark_entry_skipped(vha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA82XX_RDCRB:
			qla82xx_minidump_process_rdcrb(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDMEM:
			rval = qla82xx_minidump_process_rdmem(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla82xx_mark_entry_skipped(vha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA82XX_BOARD:
		हाल QLA82XX_RDROM:
			qla82xx_minidump_process_rdrom(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_L2DTG:
		हाल QLA82XX_L2ITG:
		हाल QLA82XX_L2DAT:
		हाल QLA82XX_L2INS:
			rval = qla82xx_minidump_process_l2tag(vha,
			    entry_hdr, &data_ptr);
			अगर (rval != QLA_SUCCESS) अणु
				qla82xx_mark_entry_skipped(vha, entry_hdr, i);
				जाओ md_failed;
			पूर्ण
			अवरोध;
		हाल QLA82XX_L1DAT:
		हाल QLA82XX_L1INS:
			qla82xx_minidump_process_l1cache(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDOCM:
			qla82xx_minidump_process_rकरोcm(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDMUX:
			qla82xx_minidump_process_rdmux(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_QUEUE:
			qla82xx_minidump_process_queue(vha,
			    entry_hdr, &data_ptr);
			अवरोध;
		हाल QLA82XX_RDNOP:
		शेष:
			qla82xx_mark_entry_skipped(vha, entry_hdr, i);
			अवरोध;
		पूर्ण

		ql_dbg(ql_dbg_p3p, vha, 0xb042,
		    "[%s]: data ptr[%d]: %p\n", __func__, i, data_ptr);

		data_collected = (uपूर्णांक8_t *)data_ptr -
		    (uपूर्णांक8_t *)ha->md_dump;
skip_nxt_entry:
		entry_hdr = (qla82xx_md_entry_hdr_t *)
		    (((uपूर्णांक8_t *)entry_hdr) + entry_hdr->entry_size);
	पूर्ण

	अगर (data_collected != total_data_size) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb043,
		    "MiniDump data mismatch: Data collected: [0x%x],"
		    "total_data_size:[0x%x]\n",
		    data_collected, total_data_size);
		जाओ md_failed;
	पूर्ण

	ql_log(ql_log_info, vha, 0xb044,
	    "Firmware dump saved to temp buffer (%ld/%p %ld/%p).\n",
	    vha->host_no, ha->md_पंचांगplt_hdr, vha->host_no, ha->md_dump);
	ha->fw_dumped = true;
	qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);

md_failed:
	वापस rval;
पूर्ण

पूर्णांक
qla82xx_md_alloc(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक i, k;
	काष्ठा qla82xx_md_ढाँचा_hdr *पंचांगplt_hdr;

	पंचांगplt_hdr = (काष्ठा qla82xx_md_ढाँचा_hdr *)ha->md_पंचांगplt_hdr;

	अगर (ql2xmdcapmask < 0x3 || ql2xmdcapmask > 0x7F) अणु
		ql2xmdcapmask = पंचांगplt_hdr->capture_debug_level & 0xFF;
		ql_log(ql_log_info, vha, 0xb045,
		    "Forcing driver capture mask to firmware default capture mask: 0x%x.\n",
		    ql2xmdcapmask);
	पूर्ण

	क्रम (i = 0x2, k = 1; (i & QLA82XX_DEFAULT_CAP_MASK); i <<= 1, k++) अणु
		अगर (i & ql2xmdcapmask)
			ha->md_dump_size += पंचांगplt_hdr->capture_size_array[k];
	पूर्ण

	अगर (ha->md_dump) अणु
		ql_log(ql_log_warn, vha, 0xb046,
		    "Firmware dump previously allocated.\n");
		वापस 1;
	पूर्ण

	ha->md_dump = vदो_स्मृति(ha->md_dump_size);
	अगर (ha->md_dump == शून्य) अणु
		ql_log(ql_log_warn, vha, 0xb047,
		    "Unable to allocate memory for Minidump size "
		    "(0x%x).\n", ha->md_dump_size);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
qla82xx_md_मुक्त(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Release the ढाँचा header allocated */
	अगर (ha->md_पंचांगplt_hdr) अणु
		ql_log(ql_log_info, vha, 0xb048,
		    "Free MiniDump template: %p, size (%d KB)\n",
		    ha->md_पंचांगplt_hdr, ha->md_ढाँचा_size / 1024);
		dma_मुक्त_coherent(&ha->pdev->dev, ha->md_ढाँचा_size,
		    ha->md_पंचांगplt_hdr, ha->md_पंचांगplt_hdr_dma);
		ha->md_पंचांगplt_hdr = शून्य;
	पूर्ण

	/* Release the ढाँचा data buffer allocated */
	अगर (ha->md_dump) अणु
		ql_log(ql_log_info, vha, 0xb049,
		    "Free MiniDump memory: %p, size (%d KB)\n",
		    ha->md_dump, ha->md_dump_size / 1024);
		vमुक्त(ha->md_dump);
		ha->md_dump_size = 0;
		ha->md_dump = शून्य;
	पूर्ण
पूर्ण

व्योम
qla82xx_md_prep(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;

	/* Get Minidump ढाँचा size */
	rval = qla82xx_md_get_ढाँचा_size(vha);
	अगर (rval == QLA_SUCCESS) अणु
		ql_log(ql_log_info, vha, 0xb04a,
		    "MiniDump Template size obtained (%d KB)\n",
		    ha->md_ढाँचा_size / 1024);

		/* Get Minidump ढाँचा */
		अगर (IS_QLA8044(ha))
			rval = qla8044_md_get_ढाँचा(vha);
		अन्यथा
			rval = qla82xx_md_get_ढाँचा(vha);

		अगर (rval == QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb04b,
			    "MiniDump Template obtained\n");

			/* Allocate memory क्रम minidump */
			rval = qla82xx_md_alloc(vha);
			अगर (rval == QLA_SUCCESS)
				ql_log(ql_log_info, vha, 0xb04c,
				    "MiniDump memory allocated (%d KB)\n",
				    ha->md_dump_size / 1024);
			अन्यथा अणु
				ql_log(ql_log_info, vha, 0xb04d,
				    "Free MiniDump template: %p, size: (%d KB)\n",
				    ha->md_पंचांगplt_hdr,
				    ha->md_ढाँचा_size / 1024);
				dma_मुक्त_coherent(&ha->pdev->dev,
				    ha->md_ढाँचा_size,
				    ha->md_पंचांगplt_hdr, ha->md_पंचांगplt_hdr_dma);
				ha->md_पंचांगplt_hdr = शून्य;
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
qla82xx_beacon_on(काष्ठा scsi_qla_host *vha)
अणु

	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla82xx_idc_lock(ha);
	rval = qla82xx_mbx_beacon_ctl(vha, 1);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0xb050,
		    "mbx set led config failed in %s\n", __func__);
		जाओ निकास;
	पूर्ण
	ha->beacon_blink_led = 1;
निकास:
	qla82xx_idc_unlock(ha);
	वापस rval;
पूर्ण

पूर्णांक
qla82xx_beacon_off(काष्ठा scsi_qla_host *vha)
अणु

	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla82xx_idc_lock(ha);
	rval = qla82xx_mbx_beacon_ctl(vha, 0);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0xb051,
		    "mbx set led config failed in %s\n", __func__);
		जाओ निकास;
	पूर्ण
	ha->beacon_blink_led = 0;
निकास:
	qla82xx_idc_unlock(ha);
	वापस rval;
पूर्ण

व्योम
qla82xx_fw_dump(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->allow_cna_fw_dump)
		वापस;

	scsi_block_requests(vha->host);
	ha->flags.isp82xx_no_md_cap = 1;
	qla82xx_idc_lock(ha);
	qla82xx_set_reset_owner(vha);
	qla82xx_idc_unlock(ha);
	qla2x00_रुको_क्रम_chip_reset(vha);
	scsi_unblock_requests(vha->host);
पूर्ण
