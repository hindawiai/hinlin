<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_T10_PI_H
#घोषणा _LINUX_T10_PI_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>

/*
 * A T10 PI-capable target device can be क्रमmatted with dअगरferent
 * protection schemes.	Currently 0 through 3 are defined:
 *
 * Type 0 is regular (unरक्षित) I/O
 *
 * Type 1 defines the contents of the guard and reference tags
 *
 * Type 2 defines the contents of the guard and reference tags and
 * uses 32-byte commands to seed the latter
 *
 * Type 3 defines the contents of the guard tag only
 */
क्रमागत t10_dअगर_type अणु
	T10_PI_TYPE0_PROTECTION = 0x0,
	T10_PI_TYPE1_PROTECTION = 0x1,
	T10_PI_TYPE2_PROTECTION = 0x2,
	T10_PI_TYPE3_PROTECTION = 0x3,
पूर्ण;

/*
 * T10 Protection Inक्रमmation tuple.
 */
काष्ठा t10_pi_tuple अणु
	__be16 guard_tag;	/* Checksum */
	__be16 app_tag;		/* Opaque storage */
	__be32 ref_tag;		/* Target LBA or indirect LBA */
पूर्ण;

#घोषणा T10_PI_APP_ESCAPE cpu_to_be16(0xffff)
#घोषणा T10_PI_REF_ESCAPE cpu_to_be32(0xffffffff)

अटल अंतरभूत u32 t10_pi_ref_tag(काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक shअगरt = ilog2(queue_logical_block_size(rq->q));

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	अगर (rq->q->पूर्णांकegrity.पूर्णांकerval_exp)
		shअगरt = rq->q->पूर्णांकegrity.पूर्णांकerval_exp;
#पूर्ण_अगर
	वापस blk_rq_pos(rq) >> (shअगरt - SECTOR_SHIFT) & 0xffffffff;
पूर्ण

बाह्य स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type1_crc;
बाह्य स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type1_ip;
बाह्य स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type3_crc;
बाह्य स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type3_ip;

#पूर्ण_अगर
