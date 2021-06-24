<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-nvram.c: NVRAM and serial EEPROM handling.
 *
 * Copyright (C) 2003 Ladislav Michl (ladis@linux-mips.org)
 */
#समावेश <linux/export.h>

#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

/* Control opcode क्रम serial eeprom  */
#घोषणा EEPROM_READ	0xc000	/* serial memory पढ़ो */
#घोषणा EEPROM_WEN	0x9800	/* ग_लिखो enable beक्रमe prog modes */
#घोषणा EEPROM_WRITE	0xa000	/* serial memory ग_लिखो */
#घोषणा EEPROM_WRALL	0x8800	/* ग_लिखो all रेजिस्टरs */
#घोषणा EEPROM_WDS	0x8000	/* disable all programming */
#घोषणा EEPROM_PRREAD	0xc000	/* पढ़ो protect रेजिस्टर */
#घोषणा EEPROM_PREN	0x9800	/* enable protect रेजिस्टर mode */
#घोषणा EEPROM_PRCLEAR	0xffff	/* clear protect रेजिस्टर */
#घोषणा EEPROM_PRWRITE	0xa000	/* ग_लिखो protect रेजिस्टर */
#घोषणा EEPROM_PRDS	0x8000	/* disable protect रेजिस्टर, क्रमever */

#घोषणा EEPROM_EPROT	0x01	/* Protect रेजिस्टर enable */
#घोषणा EEPROM_CSEL	0x02	/* Chip select */
#घोषणा EEPROM_ECLK	0x04	/* EEPROM घड़ी */
#घोषणा EEPROM_DATO	0x08	/* Data out */
#घोषणा EEPROM_DATI	0x10	/* Data in */

/* We need to use these functions early... */
#घोषणा delay() (अणु						\
	पूर्णांक x;							\
	क्रम (x=0; x<100000; x++) __यंत्र__ __अस्थिर__(""); पूर्ण)

#घोषणा eeprom_cs_on(ptr) (अणु	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) & ~EEPROM_DATO, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) & ~EEPROM_ECLK, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) & ~EEPROM_EPROT, ptr);	\
	delay();						\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) | EEPROM_CSEL, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) | EEPROM_ECLK, ptr); पूर्ण)


#घोषणा eeprom_cs_off(ptr) (अणु	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) & ~EEPROM_ECLK, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) & ~EEPROM_CSEL, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) | EEPROM_EPROT, ptr);	\
	__raw_ग_लिखोl(__raw_पढ़ोl(ptr) | EEPROM_ECLK, ptr); पूर्ण)

#घोषणा BITS_IN_COMMAND 11
/*
 * घड़ी in the nvram command and the रेजिस्टर number. For the
 * national semiconductor nv ram chip the op code is 3 bits and
 * the address is 6/8 bits.
 */
अटल अंतरभूत व्योम eeprom_cmd(अचिन्हित पूर्णांक *ctrl, अचिन्हित cmd, अचिन्हित reg)
अणु
	अचिन्हित लघु ser_cmd;
	पूर्णांक i;

	ser_cmd = cmd | (reg << (16 - BITS_IN_COMMAND));
	क्रम (i = 0; i < BITS_IN_COMMAND; i++) अणु
		अगर (ser_cmd & (1<<15))	/* अगर high order bit set */
			__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) | EEPROM_DATO, ctrl);
		अन्यथा
			__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) & ~EEPROM_DATO, ctrl);
		__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) & ~EEPROM_ECLK, ctrl);
		delay();
		__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) | EEPROM_ECLK, ctrl);
		delay();
		ser_cmd <<= 1;
	पूर्ण
	/* see data sheet timing diagram */
	__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) & ~EEPROM_DATO, ctrl);
पूर्ण

अचिन्हित लघु ip22_eeprom_पढ़ो(अचिन्हित पूर्णांक *ctrl, पूर्णांक reg)
अणु
	अचिन्हित लघु res = 0;
	पूर्णांक i;

	__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) & ~EEPROM_EPROT, ctrl);
	eeprom_cs_on(ctrl);
	eeprom_cmd(ctrl, EEPROM_READ, reg);

	/* घड़ी the data ouf of serial mem */
	क्रम (i = 0; i < 16; i++) अणु
		__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) & ~EEPROM_ECLK, ctrl);
		delay();
		__raw_ग_लिखोl(__raw_पढ़ोl(ctrl) | EEPROM_ECLK, ctrl);
		delay();
		res <<= 1;
		अगर (__raw_पढ़ोl(ctrl) & EEPROM_DATI)
			res |= 1;
	पूर्ण

	eeprom_cs_off(ctrl);

	वापस res;
पूर्ण

EXPORT_SYMBOL(ip22_eeprom_पढ़ो);

/*
 * Read specअगरied रेजिस्टर from मुख्य NVRAM
 */
अचिन्हित लघु ip22_nvram_पढ़ो(पूर्णांक reg)
अणु
	अगर (ip22_is_fullhouse())
		/* IP22 (Indigo2 aka FullHouse) stores env variables पूर्णांकo
		 * 93CS56 Microwire Bus EEPROM 2048 Bit (128x16) */
		वापस ip22_eeprom_पढ़ो(&hpc3c0->eeprom, reg);
	अन्यथा अणु
		अचिन्हित लघु पंचांगp;
		/* IP24 (Indy aka Guiness) uses DS1386 8K version */
		reg <<= 1;
		पंचांगp = hpc3c0->bbram[reg++] & 0xff;
		वापस (पंचांगp << 8) | (hpc3c0->bbram[reg] & 0xff);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(ip22_nvram_पढ़ो);
