<शैली गुरु>
/*
 * include/linux/platक्रमm_data/media/si4713.h
 *
 * Board related data definitions क्रम Si4713 i2c device driver.
 *
 * Copyright (c) 2009 Nokia Corporation
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@nokia.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#अगर_अघोषित SI4713_H
#घोषणा SI4713_H

/* The SI4713 I2C sensor chip has a fixed slave address of 0xc6 or 0x22. */
#घोषणा SI4713_I2C_ADDR_BUSEN_HIGH	0x63
#घोषणा SI4713_I2C_ADDR_BUSEN_LOW	0x11

/*
 * Platक्रमm dependent definition
 */
काष्ठा si4713_platक्रमm_data अणु
	bool is_platक्रमm_device;
पूर्ण;

/*
 * Structure to query क्रम Received Noise Level (RNL).
 */
काष्ठा si4713_rnl अणु
	__u32 index;		/* modulator index */
	__u32 frequency;	/* frequency to perक्रमm rnl measurement */
	__s32 rnl;		/* result of measurement in dBuV */
	__u32 reserved[4];	/* drivers and apps must init this to 0 */
पूर्ण;

/*
 * This is the ioctl number to query क्रम rnl. Users must pass a
 * काष्ठा si4713_rnl poपूर्णांकer specअगरying desired frequency in 'frequency' field
 * following driver capabilities (i.e V4L2_TUNER_CAP_LOW).
 * Driver must वापस measured value in the same काष्ठाure, filling 'rnl' field.
 */
#घोषणा SI4713_IOC_MEASURE_RNL	_IOWR('V', BASE_VIDIOC_PRIVATE + 0, \
						काष्ठा si4713_rnl)

#पूर्ण_अगर /* अगरndef SI4713_H*/
