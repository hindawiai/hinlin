<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Platक्रमm header क्रम Texas Instruments TLV320DAC33 codec driver
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Copyright:   (C) 2009 Nokia Corporation
 */

#अगर_अघोषित __TLV320DAC33_PLAT_H
#घोषणा __TLV320DAC33_PLAT_H

काष्ठा tlv320dac33_platक्रमm_data अणु
	पूर्णांक घातer_gpio;
	पूर्णांक mode1_latency; /* latency caused by the i2c ग_लिखोs in us */
	पूर्णांक स्वतः_fअगरo_config; /* FIFO config based on the period size */
	पूर्णांक keep_bclk;	/* Keep the BCLK running in FIFO modes */
	u8 burst_bclkभाग;
पूर्ण;

#पूर्ण_अगर /* __TLV320DAC33_PLAT_H */
