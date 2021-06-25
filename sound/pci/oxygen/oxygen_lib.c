<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver - मुख्य driver module
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/pcm.h>
#समावेश "oxygen.h"
#समावेश "cm9780.h"

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("C-Media CMI8788 helper library");
MODULE_LICENSE("GPL v2");

#घोषणा DRIVER "oxygen"

अटल अंतरभूत पूर्णांक oxygen_uart_input_पढ़ोy(काष्ठा oxygen *chip)
अणु
	वापस !(oxygen_पढ़ो8(chip, OXYGEN_MPU401 + 1) & MPU401_RX_EMPTY);
पूर्ण

अटल व्योम oxygen_पढ़ो_uart(काष्ठा oxygen *chip)
अणु
	अगर (unlikely(!oxygen_uart_input_पढ़ोy(chip))) अणु
		/* no data, but पढ़ो it anyway to clear the पूर्णांकerrupt */
		oxygen_पढ़ो8(chip, OXYGEN_MPU401);
		वापस;
	पूर्ण
	करो अणु
		u8 data = oxygen_पढ़ो8(chip, OXYGEN_MPU401);
		अगर (data == MPU401_ACK)
			जारी;
		अगर (chip->uart_input_count >= ARRAY_SIZE(chip->uart_input))
			chip->uart_input_count = 0;
		chip->uart_input[chip->uart_input_count++] = data;
	पूर्ण जबतक (oxygen_uart_input_पढ़ोy(chip));
	अगर (chip->model.uart_input)
		chip->model.uart_input(chip);
पूर्ण

अटल irqवापस_t oxygen_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा oxygen *chip = dev_id;
	अचिन्हित पूर्णांक status, clear, elapsed_streams, i;

	status = oxygen_पढ़ो16(chip, OXYGEN_INTERRUPT_STATUS);
	अगर (!status)
		वापस IRQ_NONE;

	spin_lock(&chip->reg_lock);

	clear = status & (OXYGEN_CHANNEL_A |
			  OXYGEN_CHANNEL_B |
			  OXYGEN_CHANNEL_C |
			  OXYGEN_CHANNEL_SPDIF |
			  OXYGEN_CHANNEL_MULTICH |
			  OXYGEN_CHANNEL_AC97 |
			  OXYGEN_INT_SPDIF_IN_DETECT |
			  OXYGEN_INT_GPIO |
			  OXYGEN_INT_AC97);
	अगर (clear) अणु
		अगर (clear & OXYGEN_INT_SPDIF_IN_DETECT)
			chip->पूर्णांकerrupt_mask &= ~OXYGEN_INT_SPDIF_IN_DETECT;
		oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK,
			       chip->पूर्णांकerrupt_mask & ~clear);
		oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK,
			       chip->पूर्णांकerrupt_mask);
	पूर्ण

	elapsed_streams = status & chip->pcm_running;

	spin_unlock(&chip->reg_lock);

	क्रम (i = 0; i < PCM_COUNT; ++i)
		अगर ((elapsed_streams & (1 << i)) && chip->streams[i])
			snd_pcm_period_elapsed(chip->streams[i]);

	अगर (status & OXYGEN_INT_SPDIF_IN_DETECT) अणु
		spin_lock(&chip->reg_lock);
		i = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL);
		अगर (i & (OXYGEN_SPDIF_SENSE_INT | OXYGEN_SPDIF_LOCK_INT |
			 OXYGEN_SPDIF_RATE_INT)) अणु
			/* ग_लिखो the पूर्णांकerrupt bit(s) to clear */
			oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL, i);
			schedule_work(&chip->spdअगर_input_bits_work);
		पूर्ण
		spin_unlock(&chip->reg_lock);
	पूर्ण

	अगर (status & OXYGEN_INT_GPIO)
		schedule_work(&chip->gpio_work);

	अगर (status & OXYGEN_INT_MIDI) अणु
		अगर (chip->midi)
			snd_mpu401_uart_पूर्णांकerrupt(0, chip->midi->निजी_data);
		अन्यथा
			oxygen_पढ़ो_uart(chip);
	पूर्ण

	अगर (status & OXYGEN_INT_AC97)
		wake_up(&chip->ac97_रुकोqueue);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम oxygen_spdअगर_input_bits_changed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा oxygen *chip = container_of(work, काष्ठा oxygen,
					   spdअगर_input_bits_work);
	u32 reg;

	/*
	 * This function माला_लो called when there is new activity on the SPDIF
	 * input, or when we lose lock on the input संकेत, or when the rate
	 * changes.
	 */
	msleep(1);
	spin_lock_irq(&chip->reg_lock);
	reg = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL);
	अगर ((reg & (OXYGEN_SPDIF_SENSE_STATUS |
		    OXYGEN_SPDIF_LOCK_STATUS))
	    == OXYGEN_SPDIF_SENSE_STATUS) अणु
		/*
		 * If we detect activity on the SPDIF input but cannot lock to
		 * a संकेत, the घड़ी bit is likely to be wrong.
		 */
		reg ^= OXYGEN_SPDIF_IN_CLOCK_MASK;
		oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL, reg);
		spin_unlock_irq(&chip->reg_lock);
		msleep(1);
		spin_lock_irq(&chip->reg_lock);
		reg = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL);
		अगर ((reg & (OXYGEN_SPDIF_SENSE_STATUS |
			    OXYGEN_SPDIF_LOCK_STATUS))
		    == OXYGEN_SPDIF_SENSE_STATUS) अणु
			/* nothing detected with either घड़ी; give up */
			अगर ((reg & OXYGEN_SPDIF_IN_CLOCK_MASK)
			    == OXYGEN_SPDIF_IN_CLOCK_192) अणु
				/*
				 * Reset घड़ी to <= 96 kHz because this is
				 * more likely to be received next समय.
				 */
				reg &= ~OXYGEN_SPDIF_IN_CLOCK_MASK;
				reg |= OXYGEN_SPDIF_IN_CLOCK_96;
				oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL, reg);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);

	अगर (chip->controls[CONTROL_SPDIF_INPUT_BITS]) अणु
		spin_lock_irq(&chip->reg_lock);
		chip->पूर्णांकerrupt_mask |= OXYGEN_INT_SPDIF_IN_DETECT;
		oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK,
			       chip->पूर्णांकerrupt_mask);
		spin_unlock_irq(&chip->reg_lock);

		/*
		 * We करोn't actually know that any channel status bits have
		 * changed, but let's send a notअगरication just to be sure.
		 */
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->controls[CONTROL_SPDIF_INPUT_BITS]->id);
	पूर्ण
पूर्ण

अटल व्योम oxygen_gpio_changed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा oxygen *chip = container_of(work, काष्ठा oxygen, gpio_work);

	अगर (chip->model.gpio_changed)
		chip->model.gpio_changed(chip);
पूर्ण

अटल व्योम oxygen_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा oxygen *chip = entry->निजी_data;
	पूर्णांक i, j;

	चयन (oxygen_पढ़ो8(chip, OXYGEN_REVISION) & OXYGEN_PACKAGE_ID_MASK) अणु
	हाल OXYGEN_PACKAGE_ID_8786: i = '6'; अवरोध;
	हाल OXYGEN_PACKAGE_ID_8787: i = '7'; अवरोध;
	हाल OXYGEN_PACKAGE_ID_8788: i = '8'; अवरोध;
	शेष:                     i = '?'; अवरोध;
	पूर्ण
	snd_iम_लिखो(buffer, "CMI878%c:\n", i);
	क्रम (i = 0; i < OXYGEN_IO_SIZE; i += 0x10) अणु
		snd_iम_लिखो(buffer, "%02x:", i);
		क्रम (j = 0; j < 0x10; ++j)
			snd_iम_लिखो(buffer, " %02x", oxygen_पढ़ो8(chip, i + j));
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&chip->mutex) < 0)
		वापस;
	अगर (chip->has_ac97_0) अणु
		snd_iम_लिखो(buffer, "\nAC97:\n");
		क्रम (i = 0; i < 0x80; i += 0x10) अणु
			snd_iम_लिखो(buffer, "%02x:", i);
			क्रम (j = 0; j < 0x10; j += 2)
				snd_iम_लिखो(buffer, " %04x",
					    oxygen_पढ़ो_ac97(chip, 0, i + j));
			snd_iम_लिखो(buffer, "\n");
		पूर्ण
	पूर्ण
	अगर (chip->has_ac97_1) अणु
		snd_iम_लिखो(buffer, "\nAC97 2:\n");
		क्रम (i = 0; i < 0x80; i += 0x10) अणु
			snd_iम_लिखो(buffer, "%02x:", i);
			क्रम (j = 0; j < 0x10; j += 2)
				snd_iम_लिखो(buffer, " %04x",
					    oxygen_पढ़ो_ac97(chip, 1, i + j));
			snd_iम_लिखो(buffer, "\n");
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mutex);
	अगर (chip->model.dump_रेजिस्टरs)
		chip->model.dump_रेजिस्टरs(chip, buffer);
पूर्ण

अटल व्योम oxygen_proc_init(काष्ठा oxygen *chip)
अणु
	snd_card_ro_proc_new(chip->card, "oxygen", chip, oxygen_proc_पढ़ो);
पूर्ण

अटल स्थिर काष्ठा pci_device_id *
oxygen_search_pci_id(काष्ठा oxygen *chip, स्थिर काष्ठा pci_device_id ids[])
अणु
	u16 subdevice;

	/*
	 * Make sure the EEPROM pins are available, i.e., not used क्रम SPI.
	 * (This function is called beक्रमe we initialize or use SPI.)
	 */
	oxygen_clear_bits8(chip, OXYGEN_FUNCTION,
			   OXYGEN_FUNCTION_ENABLE_SPI_4_5);
	/*
	 * Read the subप्रणाली device ID directly from the EEPROM, because the
	 * chip didn't अगर the first EEPROM word was overwritten.
	 */
	subdevice = oxygen_पढ़ो_eeprom(chip, 2);
	/* use शेष ID अगर EEPROM is missing */
	अगर (subdevice == 0xffff && oxygen_पढ़ो_eeprom(chip, 1) == 0xffff)
		subdevice = 0x8788;
	/*
	 * We use only the subप्रणाली device ID क्रम searching because it is
	 * unique even without the subप्रणाली venकरोr ID, which may have been
	 * overwritten in the EEPROM.
	 */
	क्रम (; ids->venकरोr; ++ids)
		अगर (ids->subdevice == subdevice &&
		    ids->driver_data != BROKEN_EEPROM_DRIVER_DATA)
			वापस ids;
	वापस शून्य;
पूर्ण

अटल व्योम oxygen_restore_eeprom(काष्ठा oxygen *chip,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	u16 eeprom_id;

	eeprom_id = oxygen_पढ़ो_eeprom(chip, 0);
	अगर (eeprom_id != OXYGEN_EEPROM_ID &&
	    (eeprom_id != 0xffff || id->subdevice != 0x8788)) अणु
		/*
		 * This function माला_लो called only when a known card model has
		 * been detected, i.e., we know there is a valid subप्रणाली
		 * product ID at index 2 in the EEPROM.  Thereक्रमe, we have
		 * been able to deduce the correct subप्रणाली venकरोr ID, and
		 * this is enough inक्रमmation to restore the original EEPROM
		 * contents.
		 */
		oxygen_ग_लिखो_eeprom(chip, 1, id->subvenकरोr);
		oxygen_ग_लिखो_eeprom(chip, 0, OXYGEN_EEPROM_ID);

		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_WRITE_PCI_SUBID);
		pci_ग_लिखो_config_word(chip->pci, PCI_SUBSYSTEM_VENDOR_ID,
				      id->subvenकरोr);
		pci_ग_लिखो_config_word(chip->pci, PCI_SUBSYSTEM_ID,
				      id->subdevice);
		oxygen_clear_bits8(chip, OXYGEN_MISC,
				   OXYGEN_MISC_WRITE_PCI_SUBID);

		dev_info(chip->card->dev, "EEPROM ID restored\n");
	पूर्ण
पूर्ण

अटल व्योम configure_pcie_bridge(काष्ठा pci_dev *pci)
अणु
	क्रमागत अणु PEX811X, PI7C9X110, XIO2001 पूर्ण;
	अटल स्थिर काष्ठा pci_device_id bridge_ids[] = अणु
		अणु PCI_VDEVICE(PLX, 0x8111), .driver_data = PEX811X पूर्ण,
		अणु PCI_VDEVICE(PLX, 0x8112), .driver_data = PEX811X पूर्ण,
		अणु PCI_DEVICE(0x12d8, 0xe110), .driver_data = PI7C9X110 पूर्ण,
		अणु PCI_VDEVICE(TI, 0x8240), .driver_data = XIO2001 पूर्ण,
		अणु पूर्ण
	पूर्ण;
	काष्ठा pci_dev *bridge;
	स्थिर काष्ठा pci_device_id *id;
	u32 पंचांगp;

	अगर (!pci->bus || !pci->bus->self)
		वापस;
	bridge = pci->bus->self;

	id = pci_match_id(bridge_ids, bridge);
	अगर (!id)
		वापस;

	चयन (id->driver_data) अणु
	हाल PEX811X:	/* PLX PEX8111/PEX8112 PCIe/PCI bridge */
		pci_पढ़ो_config_dword(bridge, 0x48, &पंचांगp);
		पंचांगp |= 1;	/* enable blind prefetching */
		पंचांगp |= 1 << 11;	/* enable beacon generation */
		pci_ग_लिखो_config_dword(bridge, 0x48, पंचांगp);

		pci_ग_लिखो_config_dword(bridge, 0x84, 0x0c);
		pci_पढ़ो_config_dword(bridge, 0x88, &पंचांगp);
		पंचांगp &= ~(7 << 27);
		पंचांगp |= 2 << 27;	/* set prefetch size to 128 bytes */
		pci_ग_लिखो_config_dword(bridge, 0x88, पंचांगp);
		अवरोध;

	हाल PI7C9X110:	/* Pericom PI7C9X110 PCIe/PCI bridge */
		pci_पढ़ो_config_dword(bridge, 0x40, &पंचांगp);
		पंचांगp |= 1;	/* park the PCI arbiter to the sound chip */
		pci_ग_लिखो_config_dword(bridge, 0x40, पंचांगp);
		अवरोध;

	हाल XIO2001: /* Texas Instruments XIO2001 PCIe/PCI bridge */
		pci_पढ़ो_config_dword(bridge, 0xe8, &पंचांगp);
		पंचांगp &= ~0xf;	/* request length limit: 64 bytes */
		पंचांगp &= ~(0xf << 8);
		पंचांगp |= 1 << 8;	/* request count limit: one buffer */
		pci_ग_लिखो_config_dword(bridge, 0xe8, पंचांगp);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम oxygen_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;

	chip->dac_routing = 1;
	क्रम (i = 0; i < 8; ++i)
		chip->dac_volume[i] = chip->model.dac_volume_min;
	chip->dac_mute = 1;
	chip->spdअगर_playback_enable = 0;
	chip->spdअगर_bits = OXYGEN_SPDIF_C | OXYGEN_SPDIF_ORIGINAL |
		(IEC958_AES1_CON_PCM_CODER << OXYGEN_SPDIF_CATEGORY_SHIFT);
	chip->spdअगर_pcm_bits = chip->spdअगर_bits;

	अगर (!(oxygen_पढ़ो8(chip, OXYGEN_REVISION) & OXYGEN_REVISION_2))
		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_PCI_MEM_W_1_CLOCK);

	i = oxygen_पढ़ो16(chip, OXYGEN_AC97_CONTROL);
	chip->has_ac97_0 = (i & OXYGEN_AC97_CODEC_0) != 0;
	chip->has_ac97_1 = (i & OXYGEN_AC97_CODEC_1) != 0;

	oxygen_ग_लिखो8_masked(chip, OXYGEN_FUNCTION,
			     OXYGEN_FUNCTION_RESET_CODEC |
			     chip->model.function_flags,
			     OXYGEN_FUNCTION_RESET_CODEC |
			     OXYGEN_FUNCTION_2WIRE_SPI_MASK |
			     OXYGEN_FUNCTION_ENABLE_SPI_4_5);
	oxygen_ग_लिखो8(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_ग_लिखो8(chip, OXYGEN_DMA_PAUSE, 0);
	oxygen_ग_लिखो8(chip, OXYGEN_PLAY_CHANNELS,
		      OXYGEN_PLAY_CHANNELS_2 |
		      OXYGEN_DMA_A_BURST_8 |
		      OXYGEN_DMA_MULTICH_BURST_8);
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, 0);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_MISC,
			     chip->model.misc_flags,
			     OXYGEN_MISC_WRITE_PCI_SUBID |
			     OXYGEN_MISC_REC_C_FROM_SPDIF |
			     OXYGEN_MISC_REC_B_FROM_AC97 |
			     OXYGEN_MISC_REC_A_FROM_MULTICH |
			     OXYGEN_MISC_MIDI);
	oxygen_ग_लिखो8(chip, OXYGEN_REC_FORMAT,
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_A_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_B_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_C_SHIFT));
	oxygen_ग_लिखो8(chip, OXYGEN_PLAY_FORMAT,
		      (OXYGEN_FORMAT_16 << OXYGEN_SPDIF_FORMAT_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_MULTICH_FORMAT_SHIFT));
	oxygen_ग_लिखो8(chip, OXYGEN_REC_CHANNELS, OXYGEN_REC_CHANNELS_2_2_2);
	oxygen_ग_लिखो16(chip, OXYGEN_I2S_MULTICH_FORMAT,
		       OXYGEN_RATE_48000 |
		       chip->model.dac_i2s_क्रमmat |
		       OXYGEN_I2S_MCLK(chip->model.dac_mclks) |
		       OXYGEN_I2S_BITS_16 |
		       OXYGEN_I2S_MASTER |
		       OXYGEN_I2S_BCLK_64);
	अगर (chip->model.device_config & CAPTURE_0_FROM_I2S_1)
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_A_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_क्रमmat |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	अन्यथा
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_A_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	अगर (chip->model.device_config & (CAPTURE_0_FROM_I2S_2 |
					 CAPTURE_2_FROM_I2S_2))
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_B_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_क्रमmat |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	अन्यथा
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_B_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	अगर (chip->model.device_config & CAPTURE_3_FROM_I2S_3)
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_C_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_क्रमmat |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	अन्यथा
		oxygen_ग_लिखो16(chip, OXYGEN_I2S_C_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE |
			    OXYGEN_SPDIF_LOOPBACK);
	अगर (chip->model.device_config & CAPTURE_1_FROM_SPDIF)
		oxygen_ग_लिखो32_masked(chip, OXYGEN_SPDIF_CONTROL,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_LOCK_MASK |
				      OXYGEN_SPDIF_RATE_MASK |
				      OXYGEN_SPDIF_LOCK_PAR |
				      OXYGEN_SPDIF_IN_CLOCK_96,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_LOCK_MASK |
				      OXYGEN_SPDIF_RATE_MASK |
				      OXYGEN_SPDIF_SENSE_PAR |
				      OXYGEN_SPDIF_LOCK_PAR |
				      OXYGEN_SPDIF_IN_CLOCK_MASK);
	अन्यथा
		oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
				    OXYGEN_SPDIF_SENSE_MASK |
				    OXYGEN_SPDIF_LOCK_MASK |
				    OXYGEN_SPDIF_RATE_MASK);
	oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_OUTPUT_BITS, chip->spdअगर_bits);
	oxygen_ग_लिखो16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_STANDARD);
	oxygen_clear_bits8(chip, OXYGEN_MPU401_CONTROL, OXYGEN_MPU401_LOOPBACK);
	oxygen_ग_लिखो8(chip, OXYGEN_GPI_INTERRUPT_MASK, 0);
	oxygen_ग_लिखो16(chip, OXYGEN_GPIO_INTERRUPT_MASK, 0);
	oxygen_ग_लिखो16(chip, OXYGEN_PLAY_ROUTING,
		       OXYGEN_PLAY_MULTICH_I2S_DAC |
		       OXYGEN_PLAY_SPDIF_SPDIF |
		       (0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		       (1 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		       (2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		       (3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT));
	oxygen_ग_लिखो8(chip, OXYGEN_REC_ROUTING,
		      OXYGEN_REC_A_ROUTE_I2S_ADC_1 |
		      OXYGEN_REC_B_ROUTE_I2S_ADC_2 |
		      OXYGEN_REC_C_ROUTE_SPDIF);
	oxygen_ग_लिखो8(chip, OXYGEN_ADC_MONITOR, 0);
	oxygen_ग_लिखो8(chip, OXYGEN_A_MONITOR_ROUTING,
		      (0 << OXYGEN_A_MONITOR_ROUTE_0_SHIFT) |
		      (1 << OXYGEN_A_MONITOR_ROUTE_1_SHIFT) |
		      (2 << OXYGEN_A_MONITOR_ROUTE_2_SHIFT) |
		      (3 << OXYGEN_A_MONITOR_ROUTE_3_SHIFT));

	अगर (chip->has_ac97_0 | chip->has_ac97_1)
		oxygen_ग_लिखो8(chip, OXYGEN_AC97_INTERRUPT_MASK,
			      OXYGEN_AC97_INT_READ_DONE |
			      OXYGEN_AC97_INT_WRITE_DONE);
	अन्यथा
		oxygen_ग_लिखो8(chip, OXYGEN_AC97_INTERRUPT_MASK, 0);
	oxygen_ग_लिखो32(chip, OXYGEN_AC97_OUT_CONFIG, 0);
	oxygen_ग_लिखो32(chip, OXYGEN_AC97_IN_CONFIG, 0);
	अगर (!(chip->has_ac97_0 | chip->has_ac97_1))
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTROL,
				  OXYGEN_AC97_CLOCK_DISABLE);
	अगर (!chip->has_ac97_0) अणु
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTROL,
				  OXYGEN_AC97_NO_CODEC_0);
	पूर्ण अन्यथा अणु
		oxygen_ग_लिखो_ac97(chip, 0, AC97_RESET, 0);
		msleep(1);
		oxygen_ac97_set_bits(chip, 0, CM9780_GPIO_SETUP,
				     CM9780_GPIO0IO | CM9780_GPIO1IO);
		oxygen_ac97_set_bits(chip, 0, CM9780_MIXER,
				     CM9780_BSTSEL | CM9780_STRO_MIC |
				     CM9780_MIX2FR | CM9780_PCBSW);
		oxygen_ac97_set_bits(chip, 0, CM9780_JACK,
				     CM9780_RSOE | CM9780_CBOE |
				     CM9780_SSOE | CM9780_FROE |
				     CM9780_MIC2MIC | CM9780_LI2LI);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_MASTER, 0x0000);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_PC_BEEP, 0x8000);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_MIC, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_LINE, 0x0808);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_CD, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_VIDEO, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_AUX, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_REC_GAIN, 0x8000);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_CENTER_LFE_MASTER, 0x8080);
		oxygen_ग_लिखो_ac97(chip, 0, AC97_SURROUND_MASTER, 0x8080);
		oxygen_ac97_clear_bits(chip, 0, CM9780_GPIO_STATUS,
				       CM9780_GPO0);
		/* घातer करोwn unused ADCs and DACs */
		oxygen_ac97_set_bits(chip, 0, AC97_POWERDOWN,
				     AC97_PD_PR0 | AC97_PD_PR1);
		oxygen_ac97_set_bits(chip, 0, AC97_EXTENDED_STATUS,
				     AC97_EA_PRI | AC97_EA_PRJ | AC97_EA_PRK);
	पूर्ण
	अगर (chip->has_ac97_1) अणु
		oxygen_set_bits32(chip, OXYGEN_AC97_OUT_CONFIG,
				  OXYGEN_AC97_CODEC1_SLOT3 |
				  OXYGEN_AC97_CODEC1_SLOT4);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_RESET, 0);
		msleep(1);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_MASTER, 0x0000);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_HEADPHONE, 0x8000);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_PC_BEEP, 0x8000);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_MIC, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_LINE, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_CD, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_VIDEO, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_AUX, 0x8808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_PCM, 0x0808);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_REC_SEL, 0x0000);
		oxygen_ग_लिखो_ac97(chip, 1, AC97_REC_GAIN, 0x0000);
		oxygen_ac97_set_bits(chip, 1, 0x6a, 0x0040);
	पूर्ण
पूर्ण

अटल व्योम oxygen_shutकरोwn(काष्ठा oxygen *chip)
अणु
	spin_lock_irq(&chip->reg_lock);
	chip->पूर्णांकerrupt_mask = 0;
	chip->pcm_running = 0;
	oxygen_ग_लिखो16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, 0);
	spin_unlock_irq(&chip->reg_lock);
पूर्ण

अटल व्योम oxygen_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा oxygen *chip = card->निजी_data;

	oxygen_shutकरोwn(chip);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	flush_work(&chip->spdअगर_input_bits_work);
	flush_work(&chip->gpio_work);
	chip->model.cleanup(chip);
	kमुक्त(chip->model_data);
	mutex_destroy(&chip->mutex);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
पूर्ण

पूर्णांक oxygen_pci_probe(काष्ठा pci_dev *pci, पूर्णांक index, अक्षर *id,
		     काष्ठा module *owner,
		     स्थिर काष्ठा pci_device_id *ids,
		     पूर्णांक (*get_model)(काष्ठा oxygen *chip,
				      स्थिर काष्ठा pci_device_id *id
				     )
		    )
अणु
	काष्ठा snd_card *card;
	काष्ठा oxygen *chip;
	स्थिर काष्ठा pci_device_id *pci_id;
	पूर्णांक err;

	err = snd_card_new(&pci->dev, index, id, owner,
			   माप(*chip), &card);
	अगर (err < 0)
		वापस err;

	chip = card->निजी_data;
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	spin_lock_init(&chip->reg_lock);
	mutex_init(&chip->mutex);
	INIT_WORK(&chip->spdअगर_input_bits_work,
		  oxygen_spdअगर_input_bits_changed);
	INIT_WORK(&chip->gpio_work, oxygen_gpio_changed);
	init_रुकोqueue_head(&chip->ac97_रुकोqueue);

	err = pci_enable_device(pci);
	अगर (err < 0)
		जाओ err_card;

	err = pci_request_regions(pci, DRIVER);
	अगर (err < 0) अणु
		dev_err(card->dev, "cannot reserve PCI resources\n");
		जाओ err_pci_enable;
	पूर्ण

	अगर (!(pci_resource_flags(pci, 0) & IORESOURCE_IO) ||
	    pci_resource_len(pci, 0) < OXYGEN_IO_SIZE) अणु
		dev_err(card->dev, "invalid PCI I/O range\n");
		err = -ENXIO;
		जाओ err_pci_regions;
	पूर्ण
	chip->addr = pci_resource_start(pci, 0);

	pci_id = oxygen_search_pci_id(chip, ids);
	अगर (!pci_id) अणु
		err = -ENODEV;
		जाओ err_pci_regions;
	पूर्ण
	oxygen_restore_eeprom(chip, pci_id);
	err = get_model(chip, pci_id);
	अगर (err < 0)
		जाओ err_pci_regions;

	अगर (chip->model.model_data_size) अणु
		chip->model_data = kzalloc(chip->model.model_data_size,
					   GFP_KERNEL);
		अगर (!chip->model_data) अणु
			err = -ENOMEM;
			जाओ err_pci_regions;
		पूर्ण
	पूर्ण

	pci_set_master(pci);
	card->निजी_मुक्त = oxygen_card_मुक्त;

	configure_pcie_bridge(pci);
	oxygen_init(chip);
	chip->model.init(chip);

	err = request_irq(pci->irq, oxygen_पूर्णांकerrupt, IRQF_SHARED,
			  KBUILD_MODNAME, chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "cannot grab interrupt %d\n", pci->irq);
		जाओ err_card;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	म_नकल(card->driver, chip->model.chip);
	म_नकल(card->लघुname, chip->model.लघुname);
	प्र_लिखो(card->दीर्घname, "%s at %#lx, irq %i",
		chip->model.दीर्घname, chip->addr, chip->irq);
	म_नकल(card->mixername, chip->model.chip);
	snd_component_add(card, chip->model.chip);

	err = oxygen_pcm_init(chip);
	अगर (err < 0)
		जाओ err_card;

	err = oxygen_mixer_init(chip);
	अगर (err < 0)
		जाओ err_card;

	अगर (chip->model.device_config & (MIDI_OUTPUT | MIDI_INPUT)) अणु
		अचिन्हित पूर्णांक info_flags =
				MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK;
		अगर (chip->model.device_config & MIDI_OUTPUT)
			info_flags |= MPU401_INFO_OUTPUT;
		अगर (chip->model.device_config & MIDI_INPUT)
			info_flags |= MPU401_INFO_INPUT;
		err = snd_mpu401_uart_new(card, 0, MPU401_HW_CMIPCI,
					  chip->addr + OXYGEN_MPU401,
					  info_flags, -1, &chip->midi);
		अगर (err < 0)
			जाओ err_card;
	पूर्ण

	oxygen_proc_init(chip);

	spin_lock_irq(&chip->reg_lock);
	अगर (chip->model.device_config & CAPTURE_1_FROM_SPDIF)
		chip->पूर्णांकerrupt_mask |= OXYGEN_INT_SPDIF_IN_DETECT;
	अगर (chip->has_ac97_0 | chip->has_ac97_1)
		chip->पूर्णांकerrupt_mask |= OXYGEN_INT_AC97;
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, chip->पूर्णांकerrupt_mask);
	spin_unlock_irq(&chip->reg_lock);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ err_card;

	pci_set_drvdata(pci, card);
	वापस 0;

err_pci_regions:
	pci_release_regions(pci);
err_pci_enable:
	pci_disable_device(pci);
err_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण
EXPORT_SYMBOL(oxygen_pci_probe);

व्योम oxygen_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण
EXPORT_SYMBOL(oxygen_pci_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक oxygen_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा oxygen *chip = card->निजी_data;
	अचिन्हित पूर्णांक saved_पूर्णांकerrupt_mask;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	अगर (chip->model.suspend)
		chip->model.suspend(chip);

	spin_lock_irq(&chip->reg_lock);
	saved_पूर्णांकerrupt_mask = chip->पूर्णांकerrupt_mask;
	chip->पूर्णांकerrupt_mask = 0;
	oxygen_ग_लिखो16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, 0);
	spin_unlock_irq(&chip->reg_lock);

	flush_work(&chip->spdअगर_input_bits_work);
	flush_work(&chip->gpio_work);
	chip->पूर्णांकerrupt_mask = saved_पूर्णांकerrupt_mask;
	वापस 0;
पूर्ण

अटल स्थिर u32 रेजिस्टरs_to_restore[OXYGEN_IO_SIZE / 32] = अणु
	0xffffffff, 0x00ff077f, 0x00011d08, 0x007f00ff,
	0x00300000, 0x00000fe4, 0x0ff7001f, 0x00000000
पूर्ण;
अटल स्थिर u32 ac97_रेजिस्टरs_to_restore[2][0x40 / 32] = अणु
	अणु 0x18284fa2, 0x03060000 पूर्ण,
	अणु 0x00007fa6, 0x00200000 पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक is_bit_set(स्थिर u32 *biपंचांगap, अचिन्हित पूर्णांक bit)
अणु
	वापस biपंचांगap[bit / 32] & (1 << (bit & 31));
पूर्ण

अटल व्योम oxygen_restore_ac97(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec)
अणु
	अचिन्हित पूर्णांक i;

	oxygen_ग_लिखो_ac97(chip, codec, AC97_RESET, 0);
	msleep(1);
	क्रम (i = 1; i < 0x40; ++i)
		अगर (is_bit_set(ac97_रेजिस्टरs_to_restore[codec], i))
			oxygen_ग_लिखो_ac97(chip, codec, i * 2,
					  chip->saved_ac97_रेजिस्टरs[codec][i]);
पूर्ण

अटल पूर्णांक oxygen_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा oxygen *chip = card->निजी_data;
	अचिन्हित पूर्णांक i;

	oxygen_ग_लिखो16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, 0);
	क्रम (i = 0; i < OXYGEN_IO_SIZE; ++i)
		अगर (is_bit_set(रेजिस्टरs_to_restore, i))
			oxygen_ग_लिखो8(chip, i, chip->saved_रेजिस्टरs._8[i]);
	अगर (chip->has_ac97_0)
		oxygen_restore_ac97(chip, 0);
	अगर (chip->has_ac97_1)
		oxygen_restore_ac97(chip, 1);

	अगर (chip->model.resume)
		chip->model.resume(chip);

	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, chip->पूर्णांकerrupt_mask);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(oxygen_pci_pm, oxygen_pci_suspend, oxygen_pci_resume);
EXPORT_SYMBOL(oxygen_pci_pm);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

व्योम oxygen_pci_shutकरोwn(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा oxygen *chip = card->निजी_data;

	oxygen_shutकरोwn(chip);
	chip->model.cleanup(chip);
पूर्ण
EXPORT_SYMBOL(oxygen_pci_shutकरोwn);
