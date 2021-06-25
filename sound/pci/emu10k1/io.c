<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम control of EMU10K1 chips
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश "p17v.h"

अचिन्हित पूर्णांक snd_emu10k1_ptr_पढ़ो(काष्ठा snd_emu10k1 * emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक regptr, val;
	अचिन्हित पूर्णांक mask;

	mask = emu->audigy ? A_PTR_ADDRESS_MASK : PTR_ADDRESS_MASK;
	regptr = ((reg << 16) & mask) | (chn & PTR_CHANNELNUM_MASK);

	अगर (reg & 0xff000000) अणु
		अचिन्हित अक्षर size, offset;
		
		size = (reg >> 24) & 0x3f;
		offset = (reg >> 16) & 0x1f;
		mask = ((1 << size) - 1) << offset;
		
		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		val = inl(emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		
		वापस (val & mask) >> offset;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		val = inl(emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		वापस val;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_ptr_पढ़ो);

व्योम snd_emu10k1_ptr_ग_लिखो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक regptr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mask;

	अगर (snd_BUG_ON(!emu))
		वापस;
	mask = emu->audigy ? A_PTR_ADDRESS_MASK : PTR_ADDRESS_MASK;
	regptr = ((reg << 16) & mask) | (chn & PTR_CHANNELNUM_MASK);

	अगर (reg & 0xff000000) अणु
		अचिन्हित अक्षर size, offset;

		size = (reg >> 24) & 0x3f;
		offset = (reg >> 16) & 0x1f;
		mask = ((1 << size) - 1) << offset;
		data = (data << offset) & mask;

		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		data |= inl(emu->port + DATA) & ~mask;
		outl(data, emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);		
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		outl(regptr, emu->port + PTR);
		outl(data, emu->port + DATA);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_ptr_ग_लिखो);

अचिन्हित पूर्णांक snd_emu10k1_ptr20_पढ़ो(काष्ठा snd_emu10k1 * emu, 
					  अचिन्हित पूर्णांक reg, 
					  अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक regptr, val;
  
	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + 0x20 + PTR);
	val = inl(emu->port + 0x20 + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

व्योम snd_emu10k1_ptr20_ग_लिखो(काष्ठा snd_emu10k1 *emu, 
				   अचिन्हित पूर्णांक reg, 
				   अचिन्हित पूर्णांक chn, 
				   अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक regptr;
	अचिन्हित दीर्घ flags;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + 0x20 + PTR);
	outl(data, emu->port + 0x20 + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

पूर्णांक snd_emu10k1_spi_ग_लिखो(काष्ठा snd_emu10k1 * emu,
				   अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक reset, set;
	अचिन्हित पूर्णांक reg, पंचांगp;
	पूर्णांक n, result;
	पूर्णांक err = 0;

	/* This function is not re-entrant, so protect against it. */
	spin_lock(&emu->spi_lock);
	अगर (emu->card_capabilities->ca0108_chip)
		reg = 0x3c; /* PTR20, reg 0x3c */
	अन्यथा अणु
		/* For other chip types the SPI रेजिस्टर
		 * is currently unknown. */
		err = 1;
		जाओ spi_ग_लिखो_निकास;
	पूर्ण
	अगर (data > 0xffff) अणु
		/* Only 16bit values allowed */
		err = 1;
		जाओ spi_ग_लिखो_निकास;
	पूर्ण

	पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, reg, 0);
	reset = (पंचांगp & ~0x3ffff) | 0x20000; /* Set xxx20000 */
	set = reset | 0x10000; /* Set xxx1xxxx */
	snd_emu10k1_ptr20_ग_लिखो(emu, reg, 0, reset | data);
	पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, reg, 0); /* ग_लिखो post */
	snd_emu10k1_ptr20_ग_लिखो(emu, reg, 0, set | data);
	result = 1;
	/* Wait क्रम status bit to वापस to 0 */
	क्रम (n = 0; n < 100; n++) अणु
		udelay(10);
		पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, reg, 0);
		अगर (!(पंचांगp & 0x10000)) अणु
			result = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (result) अणु
		/* Timed out */
		err = 1;
		जाओ spi_ग_लिखो_निकास;
	पूर्ण
	snd_emu10k1_ptr20_ग_लिखो(emu, reg, 0, reset | data);
	पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, reg, 0); /* Write post */
	err = 0;
spi_ग_लिखो_निकास:
	spin_unlock(&emu->spi_lock);
	वापस err;
पूर्ण

/* The ADC करोes not support i2c पढ़ो, so only ग_लिखो is implemented */
पूर्णांक snd_emu10k1_i2c_ग_लिखो(काष्ठा snd_emu10k1 *emu,
				u32 reg,
				u32 value)
अणु
	u32 पंचांगp;
	पूर्णांक समयout = 0;
	पूर्णांक status;
	पूर्णांक retry;
	पूर्णांक err = 0;

	अगर ((reg > 0x7f) || (value > 0x1ff)) अणु
		dev_err(emu->card->dev, "i2c_write: invalid values.\n");
		वापस -EINVAL;
	पूर्ण

	/* This function is not re-entrant, so protect against it. */
	spin_lock(&emu->i2c_lock);

	पंचांगp = reg << 25 | value << 16;

	/* This controls the I2C connected to the WM8775 ADC Codec */
	snd_emu10k1_ptr20_ग_लिखो(emu, P17V_I2C_1, 0, पंचांगp);
	पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, P17V_I2C_1, 0); /* ग_लिखो post */

	क्रम (retry = 0; retry < 10; retry++) अणु
		/* Send the data to i2c */
		पंचांगp = 0;
		पंचांगp = पंचांगp | (I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD);
		snd_emu10k1_ptr20_ग_लिखो(emu, P17V_I2C_ADDR, 0, पंचांगp);

		/* Wait till the transaction ends */
		जबतक (1) अणु
			mdelay(1);
			status = snd_emu10k1_ptr20_पढ़ो(emu, P17V_I2C_ADDR, 0);
			समयout++;
			अगर ((status & I2C_A_ADC_START) == 0)
				अवरोध;

			अगर (समयout > 1000) अणु
				dev_warn(emu->card->dev,
					   "emu10k1:I2C:timeout status=0x%x\n",
					   status);
				अवरोध;
			पूर्ण
		पूर्ण
		//Read back and see अगर the transaction is successful
		अगर ((status & I2C_A_ADC_ABORT) == 0)
			अवरोध;
	पूर्ण

	अगर (retry == 10) अणु
		dev_err(emu->card->dev, "Writing to ADC failed!\n");
		dev_err(emu->card->dev, "status=0x%x, reg=%d, value=%d\n",
			status, reg, value);
		/* dump_stack(); */
		err = -EINVAL;
	पूर्ण
    
	spin_unlock(&emu->i2c_lock);
	वापस err;
पूर्ण

पूर्णांक snd_emu1010_fpga_ग_लिखो(काष्ठा snd_emu10k1 * emu, u32 reg, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	अगर (reg > 0x3f)
		वापस 1;
	reg += 0x40; /* 0x40 upwards are रेजिस्टरs. */
	अगर (value > 0x3f) /* 0 to 0x3f are values */
		वापस 1;
	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(reg, emu->port + A_IOCFG);
	udelay(10);
	outl(reg | 0x80, emu->port + A_IOCFG);  /* High bit घड़ीs the value पूर्णांकo the fpga. */
	udelay(10);
	outl(value, emu->port + A_IOCFG);
	udelay(10);
	outl(value | 0x80 , emu->port + A_IOCFG);  /* High bit घड़ीs the value पूर्णांकo the fpga. */
	spin_unlock_irqrestore(&emu->emu_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक snd_emu1010_fpga_पढ़ो(काष्ठा snd_emu10k1 * emu, u32 reg, u32 *value)
अणु
	अचिन्हित दीर्घ flags;
	अगर (reg > 0x3f)
		वापस 1;
	reg += 0x40; /* 0x40 upwards are रेजिस्टरs. */
	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(reg, emu->port + A_IOCFG);
	udelay(10);
	outl(reg | 0x80, emu->port + A_IOCFG);  /* High bit घड़ीs the value पूर्णांकo the fpga. */
	udelay(10);
	*value = ((inl(emu->port + A_IOCFG) >> 8) & 0x7f);
	spin_unlock_irqrestore(&emu->emu_lock, flags);

	वापस 0;
पूर्ण

/* Each Destination has one and only one Source,
 * but one Source can feed any number of Destinations simultaneously.
 */
पूर्णांक snd_emu1010_fpga_link_dst_src_ग_लिखो(काष्ठा snd_emu10k1 * emu, u32 dst, u32 src)
अणु
	snd_emu1010_fpga_ग_लिखो(emu, 0x00, ((dst >> 8) & 0x3f) );
	snd_emu1010_fpga_ग_लिखो(emu, 0x01, (dst & 0x3f) );
	snd_emu1010_fpga_ग_लिखो(emu, 0x02, ((src >> 8) & 0x3f) );
	snd_emu1010_fpga_ग_लिखो(emu, 0x03, (src & 0x3f) );

	वापस 0;
पूर्ण

व्योम snd_emu10k1_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	enable = inl(emu->port + INTE) | पूर्णांकrenb;
	outl(enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	enable = inl(emu->port + INTE) & ~पूर्णांकrenb;
	outl(enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(CLIEH << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val |= 1 << (voicक्रमागत - 32);
	पूर्ण अन्यथा अणु
		outl(CLIEL << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val |= 1 << voicक्रमागत;
	पूर्ण
	outl(val, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(CLIEH << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val &= ~(1 << (voicक्रमागत - 32));
	पूर्ण अन्यथा अणु
		outl(CLIEL << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val &= ~(1 << voicक्रमागत);
	पूर्ण
	outl(val, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_पूर्णांकr_ack(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(CLIPH << 16, emu->port + PTR);
		voicक्रमागत = 1 << (voicक्रमागत - 32);
	पूर्ण अन्यथा अणु
		outl(CLIPL << 16, emu->port + PTR);
		voicक्रमागत = 1 << voicक्रमागत;
	पूर्ण
	outl(voicक्रमागत, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(HLIEH << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val |= 1 << (voicक्रमागत - 32);
	पूर्ण अन्यथा अणु
		outl(HLIEL << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val |= 1 << voicक्रमागत;
	पूर्ण
	outl(val, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(HLIEH << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val &= ~(1 << (voicक्रमागत - 32));
	पूर्ण अन्यथा अणु
		outl(HLIEL << 16, emu->port + PTR);
		val = inl(emu->port + DATA);
		val &= ~(1 << voicक्रमागत);
	पूर्ण
	outl(val, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_ack(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(HLIPH << 16, emu->port + PTR);
		voicक्रमागत = 1 << (voicक्रमागत - 32);
	पूर्ण अन्यथा अणु
		outl(HLIPL << 16, emu->port + PTR);
		voicक्रमागत = 1 << voicक्रमागत;
	पूर्ण
	outl(voicक्रमागत, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_set_loop_stop(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sol;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(SOLEH << 16, emu->port + PTR);
		sol = inl(emu->port + DATA);
		sol |= 1 << (voicक्रमागत - 32);
	पूर्ण अन्यथा अणु
		outl(SOLEL << 16, emu->port + PTR);
		sol = inl(emu->port + DATA);
		sol |= 1 << voicक्रमागत;
	पूर्ण
	outl(sol, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_voice_clear_loop_stop(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sol;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice पूर्णांकerrupt */
	अगर (voicक्रमागत >= 32) अणु
		outl(SOLEH << 16, emu->port + PTR);
		sol = inl(emu->port + DATA);
		sol &= ~(1 << (voicक्रमागत - 32));
	पूर्ण अन्यथा अणु
		outl(SOLEL << 16, emu->port + PTR);
		sol = inl(emu->port + DATA);
		sol &= ~(1 << voicक्रमागत);
	पूर्ण
	outl(sol, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

व्योम snd_emu10k1_रुको(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक रुको)
अणु
	अस्थिर अचिन्हित count;
	अचिन्हित पूर्णांक newसमय = 0, curसमय;

	curसमय = inl(emu->port + WC) >> 6;
	जबतक (रुको-- > 0) अणु
		count = 0;
		जबतक (count++ < 16384) अणु
			newसमय = inl(emu->port + WC) >> 6;
			अगर (newसमय != curसमय)
				अवरोध;
		पूर्ण
		अगर (count > 16384)
			अवरोध;
		curसमय = newसमय;
	पूर्ण
पूर्ण

अचिन्हित लघु snd_emu10k1_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा snd_emu10k1 *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	val = inw(emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

व्योम snd_emu10k1_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	काष्ठा snd_emu10k1 *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	outw(data, emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

/*
 *  convert rate to pitch
 */

अचिन्हित पूर्णांक snd_emu10k1_rate_to_pitch(अचिन्हित पूर्णांक rate)
अणु
	अटल स्थिर u32 logMagTable[128] = अणु
		0x00000, 0x02dfc, 0x05b9e, 0x088e6, 0x0b5d6, 0x0e26f, 0x10eb3, 0x13aa2,
		0x1663f, 0x1918a, 0x1bc84, 0x1e72e, 0x2118b, 0x23b9a, 0x2655d, 0x28ed5,
		0x2b803, 0x2e0e8, 0x30985, 0x331db, 0x359eb, 0x381b6, 0x3a93d, 0x3d081,
		0x3f782, 0x41e42, 0x444c1, 0x46b01, 0x49101, 0x4b6c4, 0x4dc49, 0x50191,
		0x5269e, 0x54b6f, 0x57006, 0x59463, 0x5b888, 0x5dc74, 0x60029, 0x623a7,
		0x646ee, 0x66a00, 0x68cdd, 0x6af86, 0x6d1fa, 0x6f43c, 0x7164b, 0x73829,
		0x759d4, 0x77b4f, 0x79c9a, 0x7bdb5, 0x7dea1, 0x7ff5e, 0x81fed, 0x8404e,
		0x86082, 0x88089, 0x8a064, 0x8c014, 0x8df98, 0x8fef1, 0x91e20, 0x93d26,
		0x95c01, 0x97ab4, 0x9993e, 0x9b79f, 0x9d5d9, 0x9f3ec, 0xa11d8, 0xa2f9d,
		0xa4d3c, 0xa6ab5, 0xa8808, 0xaa537, 0xac241, 0xadf26, 0xafbe7, 0xb1885,
		0xb3500, 0xb5157, 0xb6d8c, 0xb899f, 0xba58f, 0xbc15e, 0xbdd0c, 0xbf899,
		0xc1404, 0xc2f50, 0xc4a7b, 0xc6587, 0xc8073, 0xc9b3f, 0xcb5ed, 0xcd07c,
		0xceaec, 0xd053f, 0xd1f73, 0xd398a, 0xd5384, 0xd6d60, 0xd8720, 0xda0c3,
		0xdba4a, 0xdd3b4, 0xded03, 0xe0636, 0xe1f4e, 0xe384a, 0xe512c, 0xe69f3,
		0xe829f, 0xe9b31, 0xeb3a9, 0xecc08, 0xee44c, 0xefc78, 0xf148a, 0xf2c83,
		0xf4463, 0xf5c2a, 0xf73da, 0xf8b71, 0xfa2f0, 0xfba57, 0xfd1a7, 0xfe8df
	पूर्ण;
	अटल स्थिर अक्षर logSlopeTable[128] = अणु
		0x5c, 0x5c, 0x5b, 0x5a, 0x5a, 0x59, 0x58, 0x58,
		0x57, 0x56, 0x56, 0x55, 0x55, 0x54, 0x53, 0x53,
		0x52, 0x52, 0x51, 0x51, 0x50, 0x50, 0x4f, 0x4f,
		0x4e, 0x4d, 0x4d, 0x4d, 0x4c, 0x4c, 0x4b, 0x4b,
		0x4a, 0x4a, 0x49, 0x49, 0x48, 0x48, 0x47, 0x47,
		0x47, 0x46, 0x46, 0x45, 0x45, 0x45, 0x44, 0x44,
		0x43, 0x43, 0x43, 0x42, 0x42, 0x42, 0x41, 0x41,
		0x41, 0x40, 0x40, 0x40, 0x3f, 0x3f, 0x3f, 0x3e,
		0x3e, 0x3e, 0x3d, 0x3d, 0x3d, 0x3c, 0x3c, 0x3c,
		0x3b, 0x3b, 0x3b, 0x3b, 0x3a, 0x3a, 0x3a, 0x39,
		0x39, 0x39, 0x39, 0x38, 0x38, 0x38, 0x38, 0x37,
		0x37, 0x37, 0x37, 0x36, 0x36, 0x36, 0x36, 0x35,
		0x35, 0x35, 0x35, 0x34, 0x34, 0x34, 0x34, 0x34,
		0x33, 0x33, 0x33, 0x33, 0x32, 0x32, 0x32, 0x32,
		0x32, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30,
		0x30, 0x30, 0x30, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f
	पूर्ण;
	पूर्णांक i;

	अगर (rate == 0)
		वापस 0;	/* Bail out अगर no leading "1" */
	rate *= 11185;		/* Scale 48000 to 0x20002380 */
	क्रम (i = 31; i > 0; i--) अणु
		अगर (rate & 0x80000000) अणु	/* Detect leading "1" */
			वापस (((अचिन्हित पूर्णांक) (i - 15) << 20) +
			       logMagTable[0x7f & (rate >> 24)] +
					(0x7f & (rate >> 17)) *
					logSlopeTable[0x7f & (rate >> 24)]);
		पूर्ण
		rate <<= 1;
	पूर्ण

	वापस 0;		/* Should never reach this poपूर्णांक */
पूर्ण

