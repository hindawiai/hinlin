<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * AD9832 SPI DDS driver
 *
 * Copyright 2011 Analog Devices Inc.
 */
#अगर_अघोषित IIO_DDS_AD9832_H_
#घोषणा IIO_DDS_AD9832_H_

/*
 * TODO: काष्ठा ad9832_platक्रमm_data needs to go पूर्णांकo include/linux/iio
 */

/**
 * काष्ठा ad9832_platक्रमm_data - platक्रमm specअगरic inक्रमmation
 * @mclk:		master घड़ी in Hz
 * @freq0:		घातer up freq0 tuning word in Hz
 * @freq1:		घातer up freq1 tuning word in Hz
 * @phase0:		घातer up phase0 value [0..4095] correlates with 0..2PI
 * @phase1:		घातer up phase1 value [0..4095] correlates with 0..2PI
 * @phase2:		घातer up phase2 value [0..4095] correlates with 0..2PI
 * @phase3:		घातer up phase3 value [0..4095] correlates with 0..2PI
 */

काष्ठा ad9832_platक्रमm_data अणु
	अचिन्हित दीर्घ		freq0;
	अचिन्हित दीर्घ		freq1;
	अचिन्हित लघु		phase0;
	अचिन्हित लघु		phase1;
	अचिन्हित लघु		phase2;
	अचिन्हित लघु		phase3;
पूर्ण;

#पूर्ण_अगर /* IIO_DDS_AD9832_H_ */
