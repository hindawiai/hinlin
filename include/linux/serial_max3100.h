<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Copyright (C) 2007 Christian Pellegrin
 */


#अगर_अघोषित _LINUX_SERIAL_MAX3100_H
#घोषणा _LINUX_SERIAL_MAX3100_H 1


/**
 * काष्ठा plat_max3100 - MAX3100 SPI UART platक्रमm data
 * @loopback:            क्रमce MAX3100 in loopback
 * @crystal:             1 क्रम 3.6864 Mhz, 0 क्रम 1.8432
 * @max3100_hw_suspend:  MAX3100 has a shutकरोwn pin. This is a hook
 *                       called on suspend and resume to activate it.
 * @poll_समय:           poll समय क्रम CTS संकेत in ms, 0 disables (so no hw
 *                       flow ctrl is possible but you have less CPU usage)
 *
 * You should use this काष्ठाure in your machine description to specअगरy
 * how the MAX3100 is connected. Example:
 *
 * अटल काष्ठा plat_max3100 max3100_plat_data = अणु
 *  .loopback = 0,
 *  .crystal = 0,
 *  .poll_समय = 100,
 * पूर्ण;
 *
 * अटल काष्ठा spi_board_info spi_board_info[] = अणु
 * अणु
 *  .modalias	= "max3100",
 *  .platक्रमm_data	= &max3100_plat_data,
 *  .irq		= IRQ_EINT12,
 *  .max_speed_hz	= 5*1000*1000,
 *  .chip_select	= 0,
 * पूर्ण,
 * पूर्ण;
 *
 **/
काष्ठा plat_max3100 अणु
	पूर्णांक loopback;
	पूर्णांक crystal;
	व्योम (*max3100_hw_suspend) (पूर्णांक suspend);
	पूर्णांक poll_समय;
पूर्ण;

#पूर्ण_अगर
