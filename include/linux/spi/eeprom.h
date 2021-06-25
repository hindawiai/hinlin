<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPI_EEPROM_H
#घोषणा __LINUX_SPI_EEPROM_H

#समावेश <linux/memory.h>

/*
 * Put one of these काष्ठाures in platक्रमm_data क्रम SPI EEPROMS handled
 * by the "at25" driver.  On SPI, most EEPROMS understand the same core
 * command set.  If you need to support EEPROMs that करोn't yet fit, add
 * flags to support those protocol options.  These values all come from
 * the chip datasheets.
 */
काष्ठा spi_eeprom अणु
	u32		byte_len;
	अक्षर		name[10];
	u32		page_size;		/* क्रम ग_लिखोs */
	u16		flags;
#घोषणा	EE_ADDR1	0x0001			/*  8 bit addrs */
#घोषणा	EE_ADDR2	0x0002			/* 16 bit addrs */
#घोषणा	EE_ADDR3	0x0004			/* 24 bit addrs */
#घोषणा	EE_READONLY	0x0008			/* disallow ग_लिखोs */

	/*
	 * Certain EEPROMS have a size that is larger than the number of address
	 * bytes would allow (e.g. like M95040 from ST that has 512 Byte size
	 * but uses only one address byte (A0 to A7) क्रम addressing.) For
	 * the extra address bit (A8, A16 or A24) bit 3 of the inकाष्ठाion byte
	 * is used. This inकाष्ठाion bit is normally defined as करोn't care क्रम
	 * other AT25 like chips.
	 */
#घोषणा EE_INSTR_BIT3_IS_ADDR	0x0010

	व्योम *context;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SPI_EEPROM_H */
