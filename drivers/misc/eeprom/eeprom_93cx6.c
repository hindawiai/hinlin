<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004 - 2006 rt2x00 SourceForge Project
 * <http://rt2x00.serialmonkey.com>
 *
 * Module: eeprom_93cx6
 * Abstract: EEPROM पढ़ोer routines क्रम 93cx6 chipsets.
 * Supported chipsets: 93c46 & 93c66.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/eeprom_93cx6.h>

MODULE_AUTHOR("http://rt2x00.serialmonkey.com");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("EEPROM 93cx6 chip driver");
MODULE_LICENSE("GPL");

अटल अंतरभूत व्योम eeprom_93cx6_pulse_high(काष्ठा eeprom_93cx6 *eeprom)
अणु
	eeprom->reg_data_घड़ी = 1;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);

	/*
	 * Add a लघु delay क्रम the pulse to work.
	 * According to the specअगरications the "maximum minimum"
	 * समय should be 450ns.
	 */
	ndelay(450);
पूर्ण

अटल अंतरभूत व्योम eeprom_93cx6_pulse_low(काष्ठा eeprom_93cx6 *eeprom)
अणु
	eeprom->reg_data_घड़ी = 0;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);

	/*
	 * Add a लघु delay क्रम the pulse to work.
	 * According to the specअगरications the "maximum minimum"
	 * समय should be 450ns.
	 */
	ndelay(450);
पूर्ण

अटल व्योम eeprom_93cx6_startup(काष्ठा eeprom_93cx6 *eeprom)
अणु
	/*
	 * Clear all flags, and enable chip select.
	 */
	eeprom->रेजिस्टर_पढ़ो(eeprom);
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->reg_data_घड़ी = 0;
	eeprom->reg_chip_select = 1;
	eeprom->drive_data = 1;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);

	/*
	 * kick a pulse.
	 */
	eeprom_93cx6_pulse_high(eeprom);
	eeprom_93cx6_pulse_low(eeprom);
पूर्ण

अटल व्योम eeprom_93cx6_cleanup(काष्ठा eeprom_93cx6 *eeprom)
अणु
	/*
	 * Clear chip_select and data_in flags.
	 */
	eeprom->रेजिस्टर_पढ़ो(eeprom);
	eeprom->reg_data_in = 0;
	eeprom->reg_chip_select = 0;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);

	/*
	 * kick a pulse.
	 */
	eeprom_93cx6_pulse_high(eeprom);
	eeprom_93cx6_pulse_low(eeprom);
पूर्ण

अटल व्योम eeprom_93cx6_ग_लिखो_bits(काष्ठा eeprom_93cx6 *eeprom,
	स्थिर u16 data, स्थिर u16 count)
अणु
	अचिन्हित पूर्णांक i;

	eeprom->रेजिस्टर_पढ़ो(eeprom);

	/*
	 * Clear data flags.
	 */
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->drive_data = 1;

	/*
	 * Start writing all bits.
	 */
	क्रम (i = count; i > 0; i--) अणु
		/*
		 * Check अगर this bit needs to be set.
		 */
		eeprom->reg_data_in = !!(data & (1 << (i - 1)));

		/*
		 * Write the bit to the eeprom रेजिस्टर.
		 */
		eeprom->रेजिस्टर_ग_लिखो(eeprom);

		/*
		 * Kick a pulse.
		 */
		eeprom_93cx6_pulse_high(eeprom);
		eeprom_93cx6_pulse_low(eeprom);
	पूर्ण

	eeprom->reg_data_in = 0;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);
पूर्ण

अटल व्योम eeprom_93cx6_पढ़ो_bits(काष्ठा eeprom_93cx6 *eeprom,
	u16 *data, स्थिर u16 count)
अणु
	अचिन्हित पूर्णांक i;
	u16 buf = 0;

	eeprom->रेजिस्टर_पढ़ो(eeprom);

	/*
	 * Clear data flags.
	 */
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->drive_data = 0;

	/*
	 * Start पढ़ोing all bits.
	 */
	क्रम (i = count; i > 0; i--) अणु
		eeprom_93cx6_pulse_high(eeprom);

		eeprom->रेजिस्टर_पढ़ो(eeprom);

		/*
		 * Clear data_in flag.
		 */
		eeprom->reg_data_in = 0;

		/*
		 * Read अगर the bit has been set.
		 */
		अगर (eeprom->reg_data_out)
			buf |= (1 << (i - 1));

		eeprom_93cx6_pulse_low(eeprom);
	पूर्ण

	*data = buf;
पूर्ण

/**
 * eeprom_93cx6_पढ़ो - Read a word from eeprom
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @word: Word index from where we should start पढ़ोing
 * @data: target poपूर्णांकer where the inक्रमmation will have to be stored
 *
 * This function will पढ़ो the eeprom data as host-endian word
 * पूर्णांकo the given data poपूर्णांकer.
 */
व्योम eeprom_93cx6_पढ़ो(काष्ठा eeprom_93cx6 *eeprom, स्थिर u8 word,
	u16 *data)
अणु
	u16 command;

	/*
	 * Initialize the eeprom रेजिस्टर
	 */
	eeprom_93cx6_startup(eeprom);

	/*
	 * Select the पढ़ो opcode and the word to be पढ़ो.
	 */
	command = (PCI_EEPROM_READ_OPCODE << eeprom->width) | word;
	eeprom_93cx6_ग_लिखो_bits(eeprom, command,
		PCI_EEPROM_WIDTH_OPCODE + eeprom->width);

	/*
	 * Read the requested 16 bits.
	 */
	eeprom_93cx6_पढ़ो_bits(eeprom, data, 16);

	/*
	 * Cleanup eeprom रेजिस्टर.
	 */
	eeprom_93cx6_cleanup(eeprom);
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_पढ़ो);

/**
 * eeprom_93cx6_multiपढ़ो - Read multiple words from eeprom
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @word: Word index from where we should start पढ़ोing
 * @data: target poपूर्णांकer where the inक्रमmation will have to be stored
 * @words: Number of words that should be पढ़ो.
 *
 * This function will पढ़ो all requested words from the eeprom,
 * this is करोne by calling eeprom_93cx6_पढ़ो() multiple बार.
 * But with the additional change that जबतक the eeprom_93cx6_पढ़ो
 * will वापस host ordered bytes, this method will वापस little
 * endian words.
 */
व्योम eeprom_93cx6_multiपढ़ो(काष्ठा eeprom_93cx6 *eeprom, स्थिर u8 word,
	__le16 *data, स्थिर u16 words)
अणु
	अचिन्हित पूर्णांक i;
	u16 पंचांगp;

	क्रम (i = 0; i < words; i++) अणु
		पंचांगp = 0;
		eeprom_93cx6_पढ़ो(eeprom, word + i, &पंचांगp);
		data[i] = cpu_to_le16(पंचांगp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_multiपढ़ो);

/**
 * eeprom_93cx6_पढ़ोb - Read a byte from eeprom
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @byte: Byte index from where we should start पढ़ोing
 * @data: target poपूर्णांकer where the inक्रमmation will have to be stored
 *
 * This function will पढ़ो a byte of the eeprom data
 * पूर्णांकo the given data poपूर्णांकer.
 */
व्योम eeprom_93cx6_पढ़ोb(काष्ठा eeprom_93cx6 *eeprom, स्थिर u8 byte,
	u8 *data)
अणु
	u16 command;
	u16 पंचांगp;

	/*
	 * Initialize the eeprom रेजिस्टर
	 */
	eeprom_93cx6_startup(eeprom);

	/*
	 * Select the पढ़ो opcode and the byte to be पढ़ो.
	 */
	command = (PCI_EEPROM_READ_OPCODE << (eeprom->width + 1)) | byte;
	eeprom_93cx6_ग_लिखो_bits(eeprom, command,
		PCI_EEPROM_WIDTH_OPCODE + eeprom->width + 1);

	/*
	 * Read the requested 8 bits.
	 */
	eeprom_93cx6_पढ़ो_bits(eeprom, &पंचांगp, 8);
	*data = पंचांगp & 0xff;

	/*
	 * Cleanup eeprom रेजिस्टर.
	 */
	eeprom_93cx6_cleanup(eeprom);
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_पढ़ोb);

/**
 * eeprom_93cx6_multiपढ़ोb - Read multiple bytes from eeprom
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @byte: Index from where we should start पढ़ोing
 * @data: target poपूर्णांकer where the inक्रमmation will have to be stored
 * @bytes: Number of bytes that should be पढ़ो.
 *
 * This function will पढ़ो all requested bytes from the eeprom,
 * this is करोne by calling eeprom_93cx6_पढ़ोb() multiple बार.
 */
व्योम eeprom_93cx6_multiपढ़ोb(काष्ठा eeprom_93cx6 *eeprom, स्थिर u8 byte,
	u8 *data, स्थिर u16 bytes)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < bytes; i++)
		eeprom_93cx6_पढ़ोb(eeprom, byte + i, &data[i]);
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_multiपढ़ोb);

/**
 * eeprom_93cx6_wren - set the ग_लिखो enable state
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @enable: true to enable ग_लिखोs, otherwise disable ग_लिखोs
 *
 * Set the EEPROM ग_लिखो enable state to either allow or deny
 * ग_लिखोs depending on the @enable value.
 */
व्योम eeprom_93cx6_wren(काष्ठा eeprom_93cx6 *eeprom, bool enable)
अणु
	u16 command;

	/* start the command */
	eeprom_93cx6_startup(eeprom);

	/* create command to enable/disable */

	command = enable ? PCI_EEPROM_EWEN_OPCODE : PCI_EEPROM_EWDS_OPCODE;
	command <<= (eeprom->width - 2);

	eeprom_93cx6_ग_लिखो_bits(eeprom, command,
				PCI_EEPROM_WIDTH_OPCODE + eeprom->width);

	eeprom_93cx6_cleanup(eeprom);
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_wren);

/**
 * eeprom_93cx6_ग_लिखो - ग_लिखो data to the EEPROM
 * @eeprom: Poपूर्णांकer to eeprom काष्ठाure
 * @addr: Address to ग_लिखो data to.
 * @data: The data to ग_लिखो to address @addr.
 *
 * Write the @data to the specअगरied @addr in the EEPROM and
 * रुकोing क्रम the device to finish writing.
 *
 * Note, since we करो not expect large number of ग_लिखो operations
 * we delay in between parts of the operation to aव्योम using excessive
 * amounts of CPU समय busy रुकोing.
 */
व्योम eeprom_93cx6_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom, u8 addr, u16 data)
अणु
	पूर्णांक समयout = 100;
	u16 command;

	/* start the command */
	eeprom_93cx6_startup(eeprom);

	command = PCI_EEPROM_WRITE_OPCODE << eeprom->width;
	command |= addr;

	/* send ग_लिखो command */
	eeprom_93cx6_ग_लिखो_bits(eeprom, command,
				PCI_EEPROM_WIDTH_OPCODE + eeprom->width);

	/* send data */
	eeprom_93cx6_ग_लिखो_bits(eeprom, data, 16);

	/* get पढ़ोy to check क्रम busy */
	eeprom->drive_data = 0;
	eeprom->reg_chip_select = 1;
	eeprom->रेजिस्टर_ग_लिखो(eeprom);

	/* रुको at-least 250ns to get DO to be the busy संकेत */
	usleep_range(1000, 2000);

	/* रुको क्रम DO to go high to signअगरy finish */

	जबतक (true) अणु
		eeprom->रेजिस्टर_पढ़ो(eeprom);

		अगर (eeprom->reg_data_out)
			अवरोध;

		usleep_range(1000, 2000);

		अगर (--समयout <= 0) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	eeprom_93cx6_cleanup(eeprom);
पूर्ण
EXPORT_SYMBOL_GPL(eeprom_93cx6_ग_लिखो);
