<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPI_DS1305_H
#घोषणा __LINUX_SPI_DS1305_H

/*
 * One-समय configuration क्रम ds1305 and ds1306 RTC chips.
 *
 * Put a poपूर्णांकer to this in spi_board_info.platक्रमm_data अगर you want to
 * be sure that Linux (re)initializes this as needed ... after losing
 * backup घातer, and potentially on the first boot.
 */
काष्ठा ds1305_platक्रमm_data अणु

	/* Trickle अक्षरge configuration:  it's OK to leave out the MAGIC
	 * biपंचांगask; mask in either DS1 or DS2, and then one of 2K/4k/8K.
	 */
#घोषणा DS1305_TRICKLE_MAGIC	0xa0
#घोषणा DS1305_TRICKLE_DS2	0x08	/* two diodes */
#घोषणा DS1305_TRICKLE_DS1	0x04	/* one diode */
#घोषणा DS1305_TRICKLE_2K	0x01	/* 2 KOhm resistance */
#घोषणा DS1305_TRICKLE_4K	0x02	/* 4 KOhm resistance */
#घोषणा DS1305_TRICKLE_8K	0x03	/* 8 KOhm resistance */
	u8	trickle;

	/* set only on ds1306 parts */
	bool	is_ds1306;

	/* ds1306 only:  enable 1 Hz output */
	bool	en_1hz;

	/* REVISIT:  the driver currently expects nINT0 to be wired
	 * as the alarm IRQ.  ALM1 may also need to be set up ...
	 */
पूर्ण;

#पूर्ण_अगर /* __LINUX_SPI_DS1305_H */
