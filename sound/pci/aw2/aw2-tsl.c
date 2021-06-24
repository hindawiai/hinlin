<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*****************************************************************************
 *
 * Copyright (C) 2008 Cedric Bregardis <cedric.bregardis@मुक्त.fr> and
 * Jean-Christian Hassler <jhassler@मुक्त.fr>
 * Copyright 1998 Emagic Soft- und Hardware GmbH
 * Copyright 2002 Martijn Sipkema
 *
 * This file is part of the Audiowerk2 ALSA driver
 *
 *****************************************************************************/

#घोषणा TSL_WS0		(1UL << 31)
#घोषणा	TSL_WS1		(1UL << 30)
#घोषणा	TSL_WS2		(1UL << 29)
#घोषणा TSL_WS3		(1UL << 28)
#घोषणा TSL_WS4		(1UL << 27)
#घोषणा	TSL_DIS_A1	(1UL << 24)
#घोषणा TSL_SDW_A1	(1UL << 23)
#घोषणा TSL_SIB_A1	(1UL << 22)
#घोषणा TSL_SF_A1	(1UL << 21)
#घोषणा	TSL_LF_A1	(1UL << 20)
#घोषणा TSL_BSEL_A1	(1UL << 17)
#घोषणा TSL_DOD_A1	(1UL << 15)
#घोषणा TSL_LOW_A1	(1UL << 14)
#घोषणा TSL_DIS_A2	(1UL << 11)
#घोषणा TSL_SDW_A2	(1UL << 10)
#घोषणा TSL_SIB_A2	(1UL << 9)
#घोषणा TSL_SF_A2	(1UL << 8)
#घोषणा TSL_LF_A2	(1UL << 7)
#घोषणा TSL_BSEL_A2	(1UL << 4)
#घोषणा TSL_DOD_A2	(1UL << 2)
#घोषणा TSL_LOW_A2	(1UL << 1)
#घोषणा TSL_EOS		(1UL << 0)

    /* Audiowerk8 hardware setup: */
    /*      WS0, SD4, TSL1  - Analog/ digital in */
    /*      WS1, SD0, TSL1  - Analog out #1, digital out */
    /*      WS2, SD2, TSL1  - Analog out #2 */
    /*      WS3, SD1, TSL2  - Analog out #3 */
    /*      WS4, SD3, TSL2  - Analog out #4 */

    /* Audiowerk8 timing: */
    /*      Timeslot:     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | ... */

    /*      A1_INPUT: */
    /*      SD4:          <_ADC-L_>-------<_ADC-R_>-------< */
    /*      WS0:          _______________/---------------\_ */

    /*      A1_OUTPUT: */
    /*      SD0:          <_1-L___>-------<_1-R___>-------< */
    /*      WS1:          _______________/---------------\_ */
    /*      SD2:          >-------<_2-L___>-------<_2-R___> */
    /*      WS2:          -------\_______________/--------- */

    /*      A2_OUTPUT: */
    /*      SD1:          <_3-L___>-------<_3-R___>-------< */
    /*      WS3:          _______________/---------------\_ */
    /*      SD3:          >-------<_4-L___>-------<_4-R___> */
    /*      WS4:          -------\_______________/--------- */

अटल स्थिर पूर्णांक tsl1[8] = अणु
	1 * TSL_SDW_A1 | 3 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1 | TSL_LF_A1,

	1 * TSL_SDW_A1 | 2 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1,

	0 * TSL_SDW_A1 | 3 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1,

	0 * TSL_SDW_A1 | 2 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1,

	1 * TSL_SDW_A1 | 1 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1 | TSL_WS1 | TSL_WS0,

	1 * TSL_SDW_A1 | 0 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1 | TSL_WS1 | TSL_WS0,

	0 * TSL_SDW_A1 | 1 * TSL_BSEL_A1 |
	0 * TSL_DIS_A1 | 0 * TSL_DOD_A1 | TSL_WS1 | TSL_WS0,

	0 * TSL_SDW_A1 | 0 * TSL_BSEL_A1 | 0 * TSL_DIS_A1 |
	0 * TSL_DOD_A1 | TSL_WS1 | TSL_WS0 | TSL_SF_A1 | TSL_EOS,
पूर्ण;

अटल स्थिर पूर्णांक tsl2[8] = अणु
	0 * TSL_SDW_A2 | 3 * TSL_BSEL_A2 | 2 * TSL_DOD_A2 | TSL_LF_A2,
	0 * TSL_SDW_A2 | 2 * TSL_BSEL_A2 | 2 * TSL_DOD_A2,
	0 * TSL_SDW_A2 | 3 * TSL_BSEL_A2 | 2 * TSL_DOD_A2,
	0 * TSL_SDW_A2 | 2 * TSL_BSEL_A2 | 2 * TSL_DOD_A2,
	0 * TSL_SDW_A2 | 1 * TSL_BSEL_A2 | 2 * TSL_DOD_A2 | TSL_WS2,
	0 * TSL_SDW_A2 | 0 * TSL_BSEL_A2 | 2 * TSL_DOD_A2 | TSL_WS2,
	0 * TSL_SDW_A2 | 1 * TSL_BSEL_A2 | 2 * TSL_DOD_A2 | TSL_WS2,
	0 * TSL_SDW_A2 | 0 * TSL_BSEL_A2 | 2 * TSL_DOD_A2 | TSL_WS2 | TSL_EOS
पूर्ण;
