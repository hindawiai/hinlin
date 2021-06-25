<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver - helper functions
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/mpu401.h>
#समावेश "oxygen.h"

u8 oxygen_पढ़ो8(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg)
अणु
	वापस inb(chip->addr + reg);
पूर्ण
EXPORT_SYMBOL(oxygen_पढ़ो8);

u16 oxygen_पढ़ो16(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg)
अणु
	वापस inw(chip->addr + reg);
पूर्ण
EXPORT_SYMBOL(oxygen_पढ़ो16);

u32 oxygen_पढ़ो32(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg)
अणु
	वापस inl(chip->addr + reg);
पूर्ण
EXPORT_SYMBOL(oxygen_पढ़ो32);

व्योम oxygen_ग_लिखो8(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u8 value)
अणु
	outb(value, chip->addr + reg);
	chip->saved_रेजिस्टरs._8[reg] = value;
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो8);

व्योम oxygen_ग_लिखो16(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u16 value)
अणु
	outw(value, chip->addr + reg);
	chip->saved_रेजिस्टरs._16[reg / 2] = cpu_to_le16(value);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो16);

व्योम oxygen_ग_लिखो32(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u32 value)
अणु
	outl(value, chip->addr + reg);
	chip->saved_रेजिस्टरs._32[reg / 4] = cpu_to_le32(value);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो32);

व्योम oxygen_ग_लिखो8_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			  u8 value, u8 mask)
अणु
	u8 पंचांगp = inb(chip->addr + reg);
	पंचांगp &= ~mask;
	पंचांगp |= value & mask;
	outb(पंचांगp, chip->addr + reg);
	chip->saved_रेजिस्टरs._8[reg] = पंचांगp;
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो8_masked);

व्योम oxygen_ग_लिखो16_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			   u16 value, u16 mask)
अणु
	u16 पंचांगp = inw(chip->addr + reg);
	पंचांगp &= ~mask;
	पंचांगp |= value & mask;
	outw(पंचांगp, chip->addr + reg);
	chip->saved_रेजिस्टरs._16[reg / 2] = cpu_to_le16(पंचांगp);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो16_masked);

व्योम oxygen_ग_लिखो32_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			   u32 value, u32 mask)
अणु
	u32 पंचांगp = inl(chip->addr + reg);
	पंचांगp &= ~mask;
	पंचांगp |= value & mask;
	outl(पंचांगp, chip->addr + reg);
	chip->saved_रेजिस्टरs._32[reg / 4] = cpu_to_le32(पंचांगp);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो32_masked);

अटल पूर्णांक oxygen_ac97_रुको(काष्ठा oxygen *chip, अचिन्हित पूर्णांक mask)
अणु
	u8 status = 0;

	/*
	 * Reading the status रेजिस्टर also clears the bits, so we have to save
	 * the पढ़ो bits in status.
	 */
	रुको_event_समयout(chip->ac97_रुकोqueue,
			   (अणु status |= oxygen_पढ़ो8(chip, OXYGEN_AC97_INTERRUPT_STATUS);
			      status & mask; पूर्ण),
			   msecs_to_jअगरfies(1) + 1);
	/*
	 * Check even after a समयout because this function should not require
	 * the AC'97 पूर्णांकerrupt to be enabled.
	 */
	status |= oxygen_पढ़ो8(chip, OXYGEN_AC97_INTERRUPT_STATUS);
	वापस status & mask ? 0 : -EIO;
पूर्ण

/*
 * About 10% of AC'97 रेजिस्टर पढ़ोs or ग_लिखोs fail to complete, but even those
 * where the controller indicates completion aren't guaranteed to have actually
 * happened.
 *
 * It's hard to assign blame to either the controller or the codec because both
 * were made by C-Media ...
 */

व्योम oxygen_ग_लिखो_ac97(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
		       अचिन्हित पूर्णांक index, u16 data)
अणु
	अचिन्हित पूर्णांक count, succeeded;
	u32 reg;

	reg = data;
	reg |= index << OXYGEN_AC97_REG_ADDR_SHIFT;
	reg |= OXYGEN_AC97_REG_सूची_WRITE;
	reg |= codec << OXYGEN_AC97_REG_CODEC_SHIFT;
	succeeded = 0;
	क्रम (count = 5; count > 0; --count) अणु
		udelay(5);
		oxygen_ग_लिखो32(chip, OXYGEN_AC97_REGS, reg);
		/* require two "completed" ग_लिखोs, just to be sure */
		अगर (oxygen_ac97_रुको(chip, OXYGEN_AC97_INT_WRITE_DONE) >= 0 &&
		    ++succeeded >= 2) अणु
			chip->saved_ac97_रेजिस्टरs[codec][index / 2] = data;
			वापस;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev, "AC'97 write timeout\n");
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो_ac97);

u16 oxygen_पढ़ो_ac97(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
		     अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक last_पढ़ो = अच_पूर्णांक_उच्च;
	u32 reg;

	reg = index << OXYGEN_AC97_REG_ADDR_SHIFT;
	reg |= OXYGEN_AC97_REG_सूची_READ;
	reg |= codec << OXYGEN_AC97_REG_CODEC_SHIFT;
	क्रम (count = 5; count > 0; --count) अणु
		udelay(5);
		oxygen_ग_लिखो32(chip, OXYGEN_AC97_REGS, reg);
		udelay(10);
		अगर (oxygen_ac97_रुको(chip, OXYGEN_AC97_INT_READ_DONE) >= 0) अणु
			u16 value = oxygen_पढ़ो16(chip, OXYGEN_AC97_REGS);
			/* we require two consecutive पढ़ोs of the same value */
			अगर (value == last_पढ़ो)
				वापस value;
			last_पढ़ो = value;
			/*
			 * Invert the रेजिस्टर value bits to make sure that two
			 * consecutive unsuccessful पढ़ोs करो not वापस the same
			 * value.
			 */
			reg ^= 0xffff;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev, "AC'97 read timeout on codec %u\n", codec);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(oxygen_पढ़ो_ac97);

व्योम oxygen_ग_लिखो_ac97_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
			      अचिन्हित पूर्णांक index, u16 data, u16 mask)
अणु
	u16 value = oxygen_पढ़ो_ac97(chip, codec, index);
	value &= ~mask;
	value |= data & mask;
	oxygen_ग_लिखो_ac97(chip, codec, index, value);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो_ac97_masked);

अटल पूर्णांक oxygen_रुको_spi(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक count;

	/*
	 * Higher समयout to be sure: 200 us;
	 * actual transaction should not need more than 40 us.
	 */
	क्रम (count = 50; count > 0; count--) अणु
		udelay(4);
		अगर ((oxygen_पढ़ो8(chip, OXYGEN_SPI_CONTROL) &
						OXYGEN_SPI_BUSY) == 0)
			वापस 0;
	पूर्ण
	dev_err(chip->card->dev, "oxygen: SPI wait timeout\n");
	वापस -EIO;
पूर्ण

पूर्णांक oxygen_ग_लिखो_spi(काष्ठा oxygen *chip, u8 control, अचिन्हित पूर्णांक data)
अणु
	/*
	 * We need to रुको AFTER initiating the SPI transaction,
	 * otherwise पढ़ो operations will not work.
	 */
	oxygen_ग_लिखो8(chip, OXYGEN_SPI_DATA1, data);
	oxygen_ग_लिखो8(chip, OXYGEN_SPI_DATA2, data >> 8);
	अगर (control & OXYGEN_SPI_DATA_LENGTH_3)
		oxygen_ग_लिखो8(chip, OXYGEN_SPI_DATA3, data >> 16);
	oxygen_ग_लिखो8(chip, OXYGEN_SPI_CONTROL, control);
	वापस oxygen_रुको_spi(chip);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो_spi);

व्योम oxygen_ग_लिखो_i2c(काष्ठा oxygen *chip, u8 device, u8 map, u8 data)
अणु
	/* should not need more than about 300 us */
	msleep(1);

	oxygen_ग_लिखो8(chip, OXYGEN_2WIRE_MAP, map);
	oxygen_ग_लिखो8(chip, OXYGEN_2WIRE_DATA, data);
	oxygen_ग_लिखो8(chip, OXYGEN_2WIRE_CONTROL,
		      device | OXYGEN_2WIRE_सूची_WRITE);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो_i2c);

अटल व्योम _ग_लिखो_uart(काष्ठा oxygen *chip, अचिन्हित पूर्णांक port, u8 data)
अणु
	अगर (oxygen_पढ़ो8(chip, OXYGEN_MPU401 + 1) & MPU401_TX_FULL)
		msleep(1);
	oxygen_ग_लिखो8(chip, OXYGEN_MPU401 + port, data);
पूर्ण

व्योम oxygen_reset_uart(काष्ठा oxygen *chip)
अणु
	_ग_लिखो_uart(chip, 1, MPU401_RESET);
	msleep(1); /* रुको क्रम ACK */
	_ग_लिखो_uart(chip, 1, MPU401_ENTER_UART);
पूर्ण
EXPORT_SYMBOL(oxygen_reset_uart);

व्योम oxygen_ग_लिखो_uart(काष्ठा oxygen *chip, u8 data)
अणु
	_ग_लिखो_uart(chip, 0, data);
पूर्ण
EXPORT_SYMBOL(oxygen_ग_लिखो_uart);

u16 oxygen_पढ़ो_eeprom(काष्ठा oxygen *chip, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक समयout;

	oxygen_ग_लिखो8(chip, OXYGEN_EEPROM_CONTROL,
		      index | OXYGEN_EEPROM_सूची_READ);
	क्रम (समयout = 0; समयout < 100; ++समयout) अणु
		udelay(1);
		अगर (!(oxygen_पढ़ो8(chip, OXYGEN_EEPROM_STATUS)
		      & OXYGEN_EEPROM_BUSY))
			अवरोध;
	पूर्ण
	वापस oxygen_पढ़ो16(chip, OXYGEN_EEPROM_DATA);
पूर्ण

व्योम oxygen_ग_लिखो_eeprom(काष्ठा oxygen *chip, अचिन्हित पूर्णांक index, u16 value)
अणु
	अचिन्हित पूर्णांक समयout;

	oxygen_ग_लिखो16(chip, OXYGEN_EEPROM_DATA, value);
	oxygen_ग_लिखो8(chip, OXYGEN_EEPROM_CONTROL,
		      index | OXYGEN_EEPROM_सूची_WRITE);
	क्रम (समयout = 0; समयout < 10; ++समयout) अणु
		msleep(1);
		अगर (!(oxygen_पढ़ो8(chip, OXYGEN_EEPROM_STATUS)
		      & OXYGEN_EEPROM_BUSY))
			वापस;
	पूर्ण
	dev_err(chip->card->dev, "EEPROM write timeout\n");
पूर्ण
