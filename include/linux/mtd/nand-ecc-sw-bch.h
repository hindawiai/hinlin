<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2011 Ivan Djelic <ivan.djelic@parrot.com>
 *
 * This file is the header क्रम the न_अंकD BCH ECC implementation.
 */

#अगर_अघोषित __MTD_न_अंकD_ECC_SW_BCH_H__
#घोषणा __MTD_न_अंकD_ECC_SW_BCH_H__

#समावेश <linux/mtd/nand.h>
#समावेश <linux/bch.h>

/**
 * काष्ठा nand_ecc_sw_bch_conf - निजी software BCH ECC engine काष्ठाure
 * @req_ctx: Save request context and tweak the original request to fit the
 *           engine needs
 * @code_size: Number of bytes needed to store a code (one code per step)
 * @calc_buf: Buffer to use when calculating ECC bytes
 * @code_buf: Buffer to use when पढ़ोing (raw) ECC bytes from the chip
 * @bch: BCH control काष्ठाure
 * @errloc: error location array
 * @eccmask: XOR ecc mask, allows erased pages to be decoded as valid
 */
काष्ठा nand_ecc_sw_bch_conf अणु
	काष्ठा nand_ecc_req_tweak_ctx req_ctx;
	अचिन्हित पूर्णांक code_size;
	u8 *calc_buf;
	u8 *code_buf;
	काष्ठा bch_control *bch;
	अचिन्हित पूर्णांक *errloc;
	अचिन्हित अक्षर *eccmask;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_BCH)

पूर्णांक nand_ecc_sw_bch_calculate(काष्ठा nand_device *nand,
			      स्थिर अचिन्हित अक्षर *buf, अचिन्हित अक्षर *code);
पूर्णांक nand_ecc_sw_bch_correct(काष्ठा nand_device *nand, अचिन्हित अक्षर *buf,
			    अचिन्हित अक्षर *पढ़ो_ecc, अचिन्हित अक्षर *calc_ecc);
पूर्णांक nand_ecc_sw_bch_init_ctx(काष्ठा nand_device *nand);
व्योम nand_ecc_sw_bch_cleanup_ctx(काष्ठा nand_device *nand);
काष्ठा nand_ecc_engine *nand_ecc_sw_bch_get_engine(व्योम);

#अन्यथा /* !CONFIG_MTD_न_अंकD_ECC_SW_BCH */

अटल अंतरभूत पूर्णांक nand_ecc_sw_bch_calculate(काष्ठा nand_device *nand,
					    स्थिर अचिन्हित अक्षर *buf,
					    अचिन्हित अक्षर *code)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nand_ecc_sw_bch_correct(काष्ठा nand_device *nand,
					  अचिन्हित अक्षर *buf,
					  अचिन्हित अक्षर *पढ़ो_ecc,
					  अचिन्हित अक्षर *calc_ecc)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nand_ecc_sw_bch_init_ctx(काष्ठा nand_device *nand)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम nand_ecc_sw_bch_cleanup_ctx(काष्ठा nand_device *nand) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_ECC_SW_BCH */

#पूर्ण_अगर /* __MTD_न_अंकD_ECC_SW_BCH_H__ */
