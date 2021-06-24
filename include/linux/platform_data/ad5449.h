<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD5415, AD5426, AD5429, AD5432, AD5439, AD5443, AD5449 Digital to Analog
 * Converter driver.
 *
 * Copyright 2012 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_AD5449_H__
#घोषणा __LINUX_PLATFORM_DATA_AD5449_H__

/**
 * क्रमागत ad5449_sकरो_mode - AD5449 SDO pin configuration
 * @AD5449_SDO_DRIVE_FULL: Drive the SDO pin with full strength.
 * @AD5449_SDO_DRIVE_WEAK: Drive the SDO pin with not full strength.
 * @AD5449_SDO_OPEN_DRAIN: Operate the SDO pin in खोलो-drain mode.
 * @AD5449_SDO_DISABLED: Disable the SDO pin, in this mode it is not possible to
 *			पढ़ो back from the device.
 */
क्रमागत ad5449_sकरो_mode अणु
	AD5449_SDO_DRIVE_FULL = 0x0,
	AD5449_SDO_DRIVE_WEAK = 0x1,
	AD5449_SDO_OPEN_DRAIN = 0x2,
	AD5449_SDO_DISABLED = 0x3,
पूर्ण;

/**
 * काष्ठा ad5449_platक्रमm_data - Platक्रमm data क्रम the ad5449 DAC driver
 * @sकरो_mode: SDO pin mode
 * @hardware_clear_to_midscale: Whether निश्चितing the hardware CLR pin sets the
 *			outमाला_दो to midscale (true) or to zero scale(false).
 */
काष्ठा ad5449_platक्रमm_data अणु
	क्रमागत ad5449_sकरो_mode sकरो_mode;
	bool hardware_clear_to_midscale;
पूर्ण;

#पूर्ण_अगर
