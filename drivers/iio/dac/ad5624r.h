<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD5624R SPI DAC driver
 *
 * Copyright 2010-2011 Analog Devices Inc.
 */
#अगर_अघोषित SPI_AD5624R_H_
#घोषणा SPI_AD5624R_H_

#घोषणा AD5624R_DAC_CHANNELS			4

#घोषणा AD5624R_ADDR_DAC0			0x0
#घोषणा AD5624R_ADDR_DAC1			0x1
#घोषणा AD5624R_ADDR_DAC2			0x2
#घोषणा AD5624R_ADDR_DAC3			0x3
#घोषणा AD5624R_ADDR_ALL_DAC			0x7

#घोषणा AD5624R_CMD_WRITE_INPUT_N		0x0
#घोषणा AD5624R_CMD_UPDATE_DAC_N		0x1
#घोषणा AD5624R_CMD_WRITE_INPUT_N_UPDATE_ALL	0x2
#घोषणा AD5624R_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#घोषणा AD5624R_CMD_POWERDOWN_DAC		0x4
#घोषणा AD5624R_CMD_RESET			0x5
#घोषणा AD5624R_CMD_LDAC_SETUP			0x6
#घोषणा AD5624R_CMD_INTERNAL_REFER_SETUP	0x7

#घोषणा AD5624R_LDAC_PWRDN_NONE			0x0
#घोषणा AD5624R_LDAC_PWRDN_1K			0x1
#घोषणा AD5624R_LDAC_PWRDN_100K			0x2
#घोषणा AD5624R_LDAC_PWRDN_3STATE		0x3

/**
 * काष्ठा ad5624r_chip_info - chip specअगरic inक्रमmation
 * @channels:		channel spec क्रम the DAC
 * @पूर्णांक_vref_mv:	AD5620/40/60: the पूर्णांकernal reference voltage
 */

काष्ठा ad5624r_chip_info अणु
	स्थिर काष्ठा iio_chan_spec	*channels;
	u16				पूर्णांक_vref_mv;
पूर्ण;

/**
 * काष्ठा ad5446_state - driver instance specअगरic data
 * @indio_dev:		the industrial I/O device
 * @us:			spi_device
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @pwr_करोwn_mask	घातer करोwn mask
 * @pwr_करोwn_mode	current घातer करोwn mode
 */

काष्ठा ad5624r_state अणु
	काष्ठा spi_device		*us;
	स्थिर काष्ठा ad5624r_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	अचिन्हित लघु			vref_mv;
	अचिन्हित			pwr_करोwn_mask;
	अचिन्हित			pwr_करोwn_mode;
पूर्ण;

/**
 * ad5624r_supported_device_ids:
 * The AD5624/44/64 parts are available in dअगरferent
 * fixed पूर्णांकernal reference voltage options.
 */

क्रमागत ad5624r_supported_device_ids अणु
	ID_AD5624R3,
	ID_AD5644R3,
	ID_AD5664R3,
	ID_AD5624R5,
	ID_AD5644R5,
	ID_AD5664R5,
पूर्ण;

#पूर्ण_अगर /* SPI_AD5624R_H_ */
