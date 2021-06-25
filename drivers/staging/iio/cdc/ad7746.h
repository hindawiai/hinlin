<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AD7746 capacitive sensor driver supporting AD7745, AD7746 and AD7747
 *
 * Copyright 2011 Analog Devices Inc.
 */

#अगर_अघोषित IIO_CDC_AD7746_H_
#घोषणा IIO_CDC_AD7746_H_

/*
 * TODO: काष्ठा ad7746_platक्रमm_data needs to go पूर्णांकo include/linux/iio
 */

#घोषणा AD7466_EXCLVL_0		0 /* +-VDD/8 */
#घोषणा AD7466_EXCLVL_1		1 /* +-VDD/4 */
#घोषणा AD7466_EXCLVL_2		2 /* +-VDD * 3/8 */
#घोषणा AD7466_EXCLVL_3		3 /* +-VDD/2 */

काष्ठा ad7746_platक्रमm_data अणु
	अचिन्हित अक्षर exclvl;	/*Excitation Voltage Level */
	bool exca_en;		/* enables EXCA pin as the excitation output */
	bool exca_inv_en;	/* enables /EXCA pin as the excitation output */
	bool excb_en;		/* enables EXCB pin as the excitation output */
	bool excb_inv_en;	/* enables /EXCB pin as the excitation output */
पूर्ण;

#पूर्ण_अगर /* IIO_CDC_AD7746_H_ */
