<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  sata_promise.h - Promise SATA common definitions and अंतरभूत funcs
 *
 *  Copyright 2003-2004 Red Hat, Inc.
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 */

#अगर_अघोषित __SATA_PROMISE_H__
#घोषणा __SATA_PROMISE_H__

#समावेश <linux/ata.h>

क्रमागत pdc_packet_bits अणु
	PDC_PKT_READ		= (1 << 2),
	PDC_PKT_NODATA		= (1 << 3),

	PDC_PKT_SIZEMASK	= (1 << 7) | (1 << 6) | (1 << 5),
	PDC_PKT_CLEAR_BSY	= (1 << 4),
	PDC_PKT_WAIT_DRDY	= (1 << 3) | (1 << 4),
	PDC_LAST_REG		= (1 << 3),

	PDC_REG_DEVCTL		= (1 << 3) | (1 << 2) | (1 << 1),
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक pdc_pkt_header(काष्ठा ata_taskfile *tf,
					  dma_addr_t sg_table,
					  अचिन्हित पूर्णांक devno, u8 *buf)
अणु
	u8 dev_reg;
	__le32 *buf32 = (__le32 *) buf;

	/* set control bits (byte 0), zero delay seq id (byte 3),
	 * and seq id (byte 2)
	 */
	चयन (tf->protocol) अणु
	हाल ATA_PROT_DMA:
		अगर (!(tf->flags & ATA_TFLAG_WRITE))
			buf32[0] = cpu_to_le32(PDC_PKT_READ);
		अन्यथा
			buf32[0] = 0;
		अवरोध;

	हाल ATA_PROT_NODATA:
		buf32[0] = cpu_to_le32(PDC_PKT_NODATA);
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण

	buf32[1] = cpu_to_le32(sg_table);	/* S/G table addr */
	buf32[2] = 0;				/* no next-packet */

	अगर (devno == 0)
		dev_reg = ATA_DEVICE_OBS;
	अन्यथा
		dev_reg = ATA_DEVICE_OBS | ATA_DEV1;

	/* select device */
	buf[12] = (1 << 5) | PDC_PKT_CLEAR_BSY | ATA_REG_DEVICE;
	buf[13] = dev_reg;

	/* device control रेजिस्टर */
	buf[14] = (1 << 5) | PDC_REG_DEVCTL;
	buf[15] = tf->ctl;

	वापस 16; 	/* offset of next byte */
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pdc_pkt_footer(काष्ठा ata_taskfile *tf, u8 *buf,
				  अचिन्हित पूर्णांक i)
अणु
	अगर (tf->flags & ATA_TFLAG_DEVICE) अणु
		buf[i++] = (1 << 5) | ATA_REG_DEVICE;
		buf[i++] = tf->device;
	पूर्ण

	/* and finally the command itself; also includes end-of-pkt marker */
	buf[i++] = (1 << 5) | PDC_LAST_REG | ATA_REG_CMD;
	buf[i++] = tf->command;

	वापस i;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pdc_prep_lba28(काष्ठा ata_taskfile *tf, u8 *buf, अचिन्हित पूर्णांक i)
अणु
	/* the "(1 << 5)" should be पढ़ो "(count << 5)" */

	/* ATA command block रेजिस्टरs */
	buf[i++] = (1 << 5) | ATA_REG_FEATURE;
	buf[i++] = tf->feature;

	buf[i++] = (1 << 5) | ATA_REG_NSECT;
	buf[i++] = tf->nsect;

	buf[i++] = (1 << 5) | ATA_REG_LBAL;
	buf[i++] = tf->lbal;

	buf[i++] = (1 << 5) | ATA_REG_LBAM;
	buf[i++] = tf->lbam;

	buf[i++] = (1 << 5) | ATA_REG_LBAH;
	buf[i++] = tf->lbah;

	वापस i;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pdc_prep_lba48(काष्ठा ata_taskfile *tf, u8 *buf, अचिन्हित पूर्णांक i)
अणु
	/* the "(2 << 5)" should be पढ़ो "(count << 5)" */

	/* ATA command block रेजिस्टरs */
	buf[i++] = (2 << 5) | ATA_REG_FEATURE;
	buf[i++] = tf->hob_feature;
	buf[i++] = tf->feature;

	buf[i++] = (2 << 5) | ATA_REG_NSECT;
	buf[i++] = tf->hob_nsect;
	buf[i++] = tf->nsect;

	buf[i++] = (2 << 5) | ATA_REG_LBAL;
	buf[i++] = tf->hob_lbal;
	buf[i++] = tf->lbal;

	buf[i++] = (2 << 5) | ATA_REG_LBAM;
	buf[i++] = tf->hob_lbam;
	buf[i++] = tf->lbam;

	buf[i++] = (2 << 5) | ATA_REG_LBAH;
	buf[i++] = tf->hob_lbah;
	buf[i++] = tf->lbah;

	वापस i;
पूर्ण


#पूर्ण_अगर /* __SATA_PROMISE_H__ */
