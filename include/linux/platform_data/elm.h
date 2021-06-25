<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * BCH Error Location Module
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित __ELM_H
#घोषणा __ELM_H

क्रमागत bch_ecc अणु
	BCH4_ECC = 0,
	BCH8_ECC,
	BCH16_ECC,
पूर्ण;

/* ELM support 8 error syndrome process */
#घोषणा ERROR_VECTOR_MAX		8

/**
 * काष्ठा elm_errorvec - error vector क्रम elm
 * @error_reported:		set true क्रम vectors error is reported
 * @error_uncorrectable:	number of uncorrectable errors
 * @error_count:		number of correctable errors in the sector
 * @error_loc:			buffer क्रम error location
 *
 */
काष्ठा elm_errorvec अणु
	bool error_reported;
	bool error_uncorrectable;
	पूर्णांक error_count;
	पूर्णांक error_loc[16];
पूर्ण;

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_OMAP_BCH)
व्योम elm_decode_bch_error_page(काष्ठा device *dev, u8 *ecc_calc,
		काष्ठा elm_errorvec *err_vec);
पूर्णांक elm_config(काष्ठा device *dev, क्रमागत bch_ecc bch_type,
	पूर्णांक ecc_steps, पूर्णांक ecc_step_size, पूर्णांक ecc_syndrome_size);
#अन्यथा
अटल अंतरभूत व्योम
elm_decode_bch_error_page(काष्ठा device *dev, u8 *ecc_calc,
			  काष्ठा elm_errorvec *err_vec)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक elm_config(काष्ठा device *dev, क्रमागत bch_ecc bch_type,
			     पूर्णांक ecc_steps, पूर्णांक ecc_step_size,
			     पूर्णांक ecc_syndrome_size)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_OMAP_BCH */

#पूर्ण_अगर /* __ELM_H */
