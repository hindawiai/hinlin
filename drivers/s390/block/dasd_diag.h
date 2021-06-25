<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Based on.......: linux/drivers/s390/block/mdisk.h
 * ...............: by Harपंचांगunt Penner <hpenner@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2000
 *
 */

#घोषणा MDSK_WRITE_REQ 0x01
#घोषणा MDSK_READ_REQ  0x02

#घोषणा INIT_BIO	0x00
#घोषणा RW_BIO		0x01
#घोषणा TERM_BIO	0x02

#घोषणा DEV_CLASS_FBA	0x01
#घोषणा DEV_CLASS_ECKD	0x04

#घोषणा DASD_DIAG_CODE_31BIT		0x03
#घोषणा DASD_DIAG_CODE_64BIT		0x07

#घोषणा DASD_DIAG_RWFLAG_ASYNC		0x02
#घोषणा DASD_DIAG_RWFLAG_NOCACHE	0x01

#घोषणा DASD_DIAG_FLAGA_FORMAT_64BIT	0x80

काष्ठा dasd_diag_अक्षरacteristics अणु
	u16 dev_nr;
	u16 rdc_len;
	u8 vdev_class;
	u8 vdev_type;
	u8 vdev_status;
	u8 vdev_flags;
	u8 rdev_class;
	u8 rdev_type;
	u8 rdev_model;
	u8 rdev_features;
पूर्ण __attribute__ ((packed, aligned(4)));

#घोषणा DASD_DIAG_FLAGA_DEFAULT		DASD_DIAG_FLAGA_FORMAT_64BIT

प्रकार u64 blocknum_t;
प्रकार s64 sblocknum_t;

काष्ठा dasd_diag_bio अणु
	u8 type;
	u8 status;
	u8 spare1[2];
	u32 alet;
	blocknum_t block_number;
	व्योम *buffer;
पूर्ण __attribute__ ((packed, aligned(8)));

काष्ठा dasd_diag_init_io अणु
	u16 dev_nr;
	u8 flaga;
	u8 spare1[21];
	u32 block_size;
	u8 spare2[4];
	blocknum_t offset;
	sblocknum_t start_block;
	blocknum_t end_block;
	u8  spare3[8];
पूर्ण __attribute__ ((packed, aligned(8)));

काष्ठा dasd_diag_rw_io अणु
	u16 dev_nr;
	u8  flaga;
	u8  spare1[21];
	u8  key;
	u8  flags;
	u8  spare2[2];
	u32 block_count;
	u32 alet;
	u8  spare3[4];
	u64 पूर्णांकerrupt_params;
	काष्ठा dasd_diag_bio *bio_list;
	u8  spare4[8];
पूर्ण __attribute__ ((packed, aligned(8)));
