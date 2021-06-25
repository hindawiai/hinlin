<शैली गुरु>
/*
 * Definitions क्रम TX4937/TX4938 SPI
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#अगर_अघोषित __ASM_TXX9_SPI_H
#घोषणा __ASM_TXX9_SPI_H

#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_SPI
पूर्णांक spi_eeprom_रेजिस्टर(पूर्णांक busid, पूर्णांक chipid, पूर्णांक size);
पूर्णांक spi_eeprom_पढ़ो(पूर्णांक busid, पूर्णांक chipid,
		    पूर्णांक address, अचिन्हित अक्षर *buf, पूर्णांक len);
#अन्यथा
अटल अंतरभूत पूर्णांक spi_eeprom_रेजिस्टर(पूर्णांक busid, पूर्णांक chipid, पूर्णांक size)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक spi_eeprom_पढ़ो(पूर्णांक busid, पूर्णांक chipid,
				  पूर्णांक address, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_TXX9_SPI_H */
