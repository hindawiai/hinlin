<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम LG2160 - ATSC/MH
 *
 *    Copyright (C) 2010 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _LG2160_H_
#घोषणा _LG2160_H_

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

क्रमागत lg_chip_type अणु
	LG2160 = 0,
	LG2161 = 1,
पूर्ण;

#घोषणा LG2161_1019 LG2161
#घोषणा LG2161_1040 LG2161

क्रमागत lg2160_spi_घड़ी अणु
	LG2160_SPI_3_125_MHZ = 0,
	LG2160_SPI_6_25_MHZ = 1,
	LG2160_SPI_12_5_MHZ = 2,
पूर्ण;

#अगर 0
क्रमागत lg2161_oअगर अणु
	LG2161_OIF_EBI2_SLA  = 1,
	LG2161_OIF_SDIO_SLA  = 2,
	LG2161_OIF_SPI_SLA   = 3,
	LG2161_OIF_SPI_MAS   = 4,
	LG2161_OIF_SERIAL_TS = 7,
पूर्ण;
#पूर्ण_अगर

काष्ठा lg2160_config अणु
	u8 i2c_addr;

	/* user defined IF frequency in KHz */
	u16 अगर_khz;

	/* disable i2c repeater - 0:repeater enabled 1:repeater disabled */
	अचिन्हित पूर्णांक deny_i2c_rptr:1;

	/* spectral inversion - 0:disabled 1:enabled */
	अचिन्हित पूर्णांक spectral_inversion:1;

	अचिन्हित पूर्णांक output_अगर;
	क्रमागत lg2160_spi_घड़ी spi_घड़ी;
	क्रमागत lg_chip_type lg_chip;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LG2160)
बाह्य
काष्ठा dvb_frontend *lg2160_attach(स्थिर काष्ठा lg2160_config *config,
				     काष्ठा i2c_adapter *i2c_adap);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *lg2160_attach(स्थिर काष्ठा lg2160_config *config,
				     काष्ठा i2c_adapter *i2c_adap)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LG2160 */

#पूर्ण_अगर /* _LG2160_H_ */
