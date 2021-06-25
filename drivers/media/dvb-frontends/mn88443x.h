<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Socionext MN88443x series demodulator driver क्रम ISDB-S/ISDB-T.
 *
 * Copyright (c) 2018 Socionext Inc.
 */

#अगर_अघोषित MN88443X_H
#घोषणा MN88443X_H

#समावेश <media/dvb_frontend.h>

/* ISDB-T IF frequency */
#घोषणा सूचीECT_IF_57MHZ    57000000
#घोषणा सूचीECT_IF_44MHZ    44000000
#घोषणा LOW_IF_4MHZ        4000000

काष्ठा mn88443x_config अणु
	काष्ठा clk *mclk;
	u32 अगर_freq;
	काष्ठा gpio_desc *reset_gpio;

	/* Everything after that is वापसed by the driver. */
	काष्ठा dvb_frontend **fe;
पूर्ण;

#पूर्ण_अगर /* MN88443X_H */
