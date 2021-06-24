<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Module: eeprom_93xx46
 * platक्रमm description क्रम 93xx46 EEPROMs.
 */
#समावेश <linux/gpio/consumer.h>

काष्ठा eeprom_93xx46_platक्रमm_data अणु
	अचिन्हित अक्षर	flags;
#घोषणा EE_ADDR8	0x01		/*  8 bit addr. cfg */
#घोषणा EE_ADDR16	0x02		/* 16 bit addr. cfg */
#घोषणा EE_READONLY	0x08		/* क्रमbid writing */

	अचिन्हित पूर्णांक	quirks;
/* Single word पढ़ो transfers only; no sequential पढ़ो. */
#घोषणा EEPROM_93XX46_QUIRK_SINGLE_WORD_READ		(1 << 0)
/* Inकाष्ठाions such as EWEN are (addrlen + 2) in length. */
#घोषणा EEPROM_93XX46_QUIRK_INSTRUCTION_LENGTH		(1 << 1)
/* Add extra cycle after address during a पढ़ो */
#घोषणा EEPROM_93XX46_QUIRK_EXTRA_READ_CYCLE		BIT(2)

	/*
	 * optional hooks to control additional logic
	 * beक्रमe and after spi transfer.
	 */
	व्योम (*prepare)(व्योम *);
	व्योम (*finish)(व्योम *);
	काष्ठा gpio_desc *select;
पूर्ण;
