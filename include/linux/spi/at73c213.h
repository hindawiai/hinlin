<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Board-specअगरic data used to set up AT73c213 audio DAC driver.
 */

#अगर_अघोषित __LINUX_SPI_AT73C213_H
#घोषणा __LINUX_SPI_AT73C213_H

/**
 * at73c213_board_info - how the बाह्यal DAC is wired to the device.
 *
 * @ssc_id: SSC platक्रमm_driver id the DAC shall use to stream the audio.
 * @dac_clk: the बाह्यal घड़ी used to provide master घड़ी to the DAC.
 * @लघुname: a लघु discription क्रम the DAC, seen by userspace tools.
 *
 * This काष्ठा contains the configuration of the hardware connection to the
 * बाह्यal DAC. The DAC needs a master घड़ी and a I2S audio stream. It also
 * provides a name which is used to identअगरy it in userspace tools.
 */
काष्ठा at73c213_board_info अणु
	पूर्णांक		ssc_id;
	काष्ठा clk	*dac_clk;
	अक्षर		लघुname[32];
पूर्ण;

#पूर्ण_अगर /* __LINUX_SPI_AT73C213_H */
