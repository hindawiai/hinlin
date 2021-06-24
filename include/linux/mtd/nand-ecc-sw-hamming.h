<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2000-2010 Steven J. Hill <sjhill@realitydiluted.com>
 *			    David Woodhouse <dwmw2@infradead.org>
 *			    Thomas Gleixner <tglx@linutronix.de>
 *
 * This file is the header क्रम the न_अंकD Hamming ECC implementation.
 */

#अगर_अघोषित __MTD_न_अंकD_ECC_SW_HAMMING_H__
#घोषणा __MTD_न_अंकD_ECC_SW_HAMMING_H__

#समावेश <linux/mtd/nand.h>

/**
 * काष्ठा nand_ecc_sw_hamming_conf - निजी software Hamming ECC engine काष्ठाure
 * @req_ctx: Save request context and tweak the original request to fit the
 *           engine needs
 * @code_size: Number of bytes needed to store a code (one code per step)
 * @calc_buf: Buffer to use when calculating ECC bytes
 * @code_buf: Buffer to use when पढ़ोing (raw) ECC bytes from the chip
 * @sm_order: Smart Media special ordering
 */
काष्ठा nand_ecc_sw_hamming_conf अणु
	काष्ठा nand_ecc_req_tweak_ctx req_ctx;
	अचिन्हित पूर्णांक code_size;
	u8 *calc_buf;
	u8 *code_buf;
	अचिन्हित पूर्णांक sm_order;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING)

पूर्णांक nand_ecc_sw_hamming_init_ctx(काष्ठा nand_device *nand);
व्योम nand_ecc_sw_hamming_cleanup_ctx(काष्ठा nand_device *nand);
पूर्णांक ecc_sw_hamming_calculate(स्थिर अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक step_size,
			     अचिन्हित अक्षर *code, bool sm_order);
पूर्णांक nand_ecc_sw_hamming_calculate(काष्ठा nand_device *nand,
				  स्थिर अचिन्हित अक्षर *buf,
				  अचिन्हित अक्षर *code);
पूर्णांक ecc_sw_hamming_correct(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *पढ़ो_ecc,
			   अचिन्हित अक्षर *calc_ecc, अचिन्हित पूर्णांक step_size,
			   bool sm_order);
पूर्णांक nand_ecc_sw_hamming_correct(काष्ठा nand_device *nand, अचिन्हित अक्षर *buf,
				अचिन्हित अक्षर *पढ़ो_ecc,
				अचिन्हित अक्षर *calc_ecc);

#अन्यथा /* !CONFIG_MTD_न_अंकD_ECC_SW_HAMMING */

अटल अंतरभूत पूर्णांक nand_ecc_sw_hamming_init_ctx(काष्ठा nand_device *nand)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम nand_ecc_sw_hamming_cleanup_ctx(काष्ठा nand_device *nand) अणुपूर्ण

अटल अंतरभूत पूर्णांक ecc_sw_hamming_calculate(स्थिर अचिन्हित अक्षर *buf,
					   अचिन्हित पूर्णांक step_size,
					   अचिन्हित अक्षर *code, bool sm_order)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nand_ecc_sw_hamming_calculate(काष्ठा nand_device *nand,
						स्थिर अचिन्हित अक्षर *buf,
						अचिन्हित अक्षर *code)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ecc_sw_hamming_correct(अचिन्हित अक्षर *buf,
					 अचिन्हित अक्षर *पढ़ो_ecc,
					 अचिन्हित अक्षर *calc_ecc,
					 अचिन्हित पूर्णांक step_size, bool sm_order)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nand_ecc_sw_hamming_correct(काष्ठा nand_device *nand,
					      अचिन्हित अक्षर *buf,
					      अचिन्हित अक्षर *पढ़ो_ecc,
					      अचिन्हित अक्षर *calc_ecc)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_ECC_SW_HAMMING */

#पूर्ण_अगर /* __MTD_न_अंकD_ECC_SW_HAMMING_H__ */
