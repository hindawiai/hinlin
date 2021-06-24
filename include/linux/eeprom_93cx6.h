<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2006 rt2x00 SourceForge Project
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: eeprom_93cx6
	Abstract: EEPROM पढ़ोer dataकाष्ठाures क्रम 93cx6 chipsets.
	Supported chipsets: 93c46, 93c56 and 93c66.
 */

/*
 * EEPROM operation defines.
 */
#घोषणा PCI_EEPROM_WIDTH_93C46	6
#घोषणा PCI_EEPROM_WIDTH_93C56	8
#घोषणा PCI_EEPROM_WIDTH_93C66	8
#घोषणा PCI_EEPROM_WIDTH_93C86	8
#घोषणा PCI_EEPROM_WIDTH_OPCODE	3
#घोषणा PCI_EEPROM_WRITE_OPCODE	0x05
#घोषणा PCI_EEPROM_ERASE_OPCODE 0x07
#घोषणा PCI_EEPROM_READ_OPCODE	0x06
#घोषणा PCI_EEPROM_EWDS_OPCODE	0x10
#घोषणा PCI_EEPROM_EWEN_OPCODE	0x13

/**
 * काष्ठा eeprom_93cx6 - control काष्ठाure क्रम setting the commands
 * क्रम पढ़ोing the eeprom data.
 * @data: निजी poपूर्णांकer क्रम the driver.
 * @रेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom): handler to
 * पढ़ो the eeprom रेजिस्टर, this function should set all reg_* fields.
 * @रेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom): handler to
 * ग_लिखो to the eeprom रेजिस्टर by using all reg_* fields.
 * @width: eeprom width, should be one of the PCI_EEPROM_WIDTH_* defines
 * @drive_data: Set अगर we're driving the data line.
 * @reg_data_in: रेजिस्टर field to indicate data input
 * @reg_data_out: रेजिस्टर field to indicate data output
 * @reg_data_घड़ी: रेजिस्टर field to set the data घड़ी
 * @reg_chip_select: रेजिस्टर field to set the chip select
 *
 * This काष्ठाure is used क्रम the communication between the driver
 * and the eeprom_93cx6 handlers क्रम पढ़ोing the eeprom.
 */
काष्ठा eeprom_93cx6 अणु
	व्योम *data;

	व्योम (*रेजिस्टर_पढ़ो)(काष्ठा eeprom_93cx6 *eeprom);
	व्योम (*रेजिस्टर_ग_लिखो)(काष्ठा eeprom_93cx6 *eeprom);

	पूर्णांक width;

	अक्षर drive_data;
	अक्षर reg_data_in;
	अक्षर reg_data_out;
	अक्षर reg_data_घड़ी;
	अक्षर reg_chip_select;
पूर्ण;

बाह्य व्योम eeprom_93cx6_पढ़ो(काष्ठा eeprom_93cx6 *eeprom,
	स्थिर u8 word, u16 *data);
बाह्य व्योम eeprom_93cx6_multiपढ़ो(काष्ठा eeprom_93cx6 *eeprom,
	स्थिर u8 word, __le16 *data, स्थिर u16 words);
बाह्य व्योम eeprom_93cx6_पढ़ोb(काष्ठा eeprom_93cx6 *eeprom,
	स्थिर u8 byte, u8 *data);
बाह्य व्योम eeprom_93cx6_multiपढ़ोb(काष्ठा eeprom_93cx6 *eeprom,
	स्थिर u8 byte, u8 *data, स्थिर u16 bytes);

बाह्य व्योम eeprom_93cx6_wren(काष्ठा eeprom_93cx6 *eeprom, bool enable);

बाह्य व्योम eeprom_93cx6_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom,
			       u8 addr, u16 data);
