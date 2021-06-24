<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt5677-spi.h  --  RT5677 ALSA SoC audio codec driver
 *
 * Copyright 2013 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __RT5677_SPI_H__
#घोषणा __RT5677_SPI_H__

#अगर IS_ENABLED(CONFIG_SND_SOC_RT5677_SPI)
पूर्णांक rt5677_spi_पढ़ो(u32 addr, व्योम *rxbuf, माप_प्रकार len);
पूर्णांक rt5677_spi_ग_लिखो(u32 addr, स्थिर व्योम *txbuf, माप_प्रकार len);
पूर्णांक rt5677_spi_ग_लिखो_firmware(u32 addr, स्थिर काष्ठा firmware *fw);
व्योम rt5677_spi_hotword_detected(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक rt5677_spi_पढ़ो(u32 addr, व्योम *rxbuf, माप_प्रकार len)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक rt5677_spi_ग_लिखो(u32 addr, स्थिर व्योम *txbuf, माप_प्रकार len)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक rt5677_spi_ग_लिखो_firmware(u32 addr, स्थिर काष्ठा firmware *fw)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम rt5677_spi_hotword_detected(व्योम)अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __RT5677_SPI_H__ */
