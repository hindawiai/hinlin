<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Srinidhi Kasagar <srinidhi.kasagar@stericsson.com>
 * Author: Rabin Vincent <rabin.vincent@stericsson.com>
 * Author: Mattias Wallin <mattias.wallin@stericsson.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/*
 * Interrupt रेजिस्टर offsets
 * Bank : 0x0E
 */
#घोषणा AB8500_IT_SOURCE1_REG		0x00
#घोषणा AB8500_IT_SOURCE2_REG		0x01
#घोषणा AB8500_IT_SOURCE3_REG		0x02
#घोषणा AB8500_IT_SOURCE4_REG		0x03
#घोषणा AB8500_IT_SOURCE5_REG		0x04
#घोषणा AB8500_IT_SOURCE6_REG		0x05
#घोषणा AB8500_IT_SOURCE7_REG		0x06
#घोषणा AB8500_IT_SOURCE8_REG		0x07
#घोषणा AB9540_IT_SOURCE13_REG		0x0C
#घोषणा AB8500_IT_SOURCE19_REG		0x12
#घोषणा AB8500_IT_SOURCE20_REG		0x13
#घोषणा AB8500_IT_SOURCE21_REG		0x14
#घोषणा AB8500_IT_SOURCE22_REG		0x15
#घोषणा AB8500_IT_SOURCE23_REG		0x16
#घोषणा AB8500_IT_SOURCE24_REG		0x17

/*
 * latch रेजिस्टरs
 */
#घोषणा AB8500_IT_LATCH1_REG		0x20
#घोषणा AB8500_IT_LATCH2_REG		0x21
#घोषणा AB8500_IT_LATCH3_REG		0x22
#घोषणा AB8500_IT_LATCH4_REG		0x23
#घोषणा AB8500_IT_LATCH5_REG		0x24
#घोषणा AB8500_IT_LATCH6_REG		0x25
#घोषणा AB8500_IT_LATCH7_REG		0x26
#घोषणा AB8500_IT_LATCH8_REG		0x27
#घोषणा AB8500_IT_LATCH9_REG		0x28
#घोषणा AB8500_IT_LATCH10_REG		0x29
#घोषणा AB8500_IT_LATCH12_REG		0x2B
#घोषणा AB9540_IT_LATCH13_REG		0x2C
#घोषणा AB8500_IT_LATCH19_REG		0x32
#घोषणा AB8500_IT_LATCH20_REG		0x33
#घोषणा AB8500_IT_LATCH21_REG		0x34
#घोषणा AB8500_IT_LATCH22_REG		0x35
#घोषणा AB8500_IT_LATCH23_REG		0x36
#घोषणा AB8500_IT_LATCH24_REG		0x37

/*
 * mask रेजिस्टरs
 */

#घोषणा AB8500_IT_MASK1_REG		0x40
#घोषणा AB8500_IT_MASK2_REG		0x41
#घोषणा AB8500_IT_MASK3_REG		0x42
#घोषणा AB8500_IT_MASK4_REG		0x43
#घोषणा AB8500_IT_MASK5_REG		0x44
#घोषणा AB8500_IT_MASK6_REG		0x45
#घोषणा AB8500_IT_MASK7_REG		0x46
#घोषणा AB8500_IT_MASK8_REG		0x47
#घोषणा AB8500_IT_MASK9_REG		0x48
#घोषणा AB8500_IT_MASK10_REG		0x49
#घोषणा AB8500_IT_MASK11_REG		0x4A
#घोषणा AB8500_IT_MASK12_REG		0x4B
#घोषणा AB8500_IT_MASK13_REG		0x4C
#घोषणा AB8500_IT_MASK14_REG		0x4D
#घोषणा AB8500_IT_MASK15_REG		0x4E
#घोषणा AB8500_IT_MASK16_REG		0x4F
#घोषणा AB8500_IT_MASK17_REG		0x50
#घोषणा AB8500_IT_MASK18_REG		0x51
#घोषणा AB8500_IT_MASK19_REG		0x52
#घोषणा AB8500_IT_MASK20_REG		0x53
#घोषणा AB8500_IT_MASK21_REG		0x54
#घोषणा AB8500_IT_MASK22_REG		0x55
#घोषणा AB8500_IT_MASK23_REG		0x56
#घोषणा AB8500_IT_MASK24_REG		0x57
#घोषणा AB8500_IT_MASK25_REG		0x58

/*
 * latch hierarchy रेजिस्टरs
 */
#घोषणा AB8500_IT_LATCHHIER1_REG	0x60
#घोषणा AB8500_IT_LATCHHIER2_REG	0x61
#घोषणा AB8500_IT_LATCHHIER3_REG	0x62
#घोषणा AB8540_IT_LATCHHIER4_REG	0x63

#घोषणा AB8500_IT_LATCHHIER_NUM		3
#घोषणा AB8540_IT_LATCHHIER_NUM		4

#घोषणा AB8500_REV_REG			0x80
#घोषणा AB8500_IC_NAME_REG		0x82
#घोषणा AB8500_SWITCH_OFF_STATUS	0x00

#घोषणा AB8500_TURN_ON_STATUS		0x00
#घोषणा AB8505_TURN_ON_STATUS_2		0x04

#घोषणा AB8500_CH_USBCH_STAT1_REG	0x02
#घोषणा VBUS_DET_DBNC100		0x02
#घोषणा VBUS_DET_DBNC1			0x01

अटल DEFINE_SPINLOCK(on_stat_lock);
अटल u8 turn_on_stat_mask = 0xFF;
अटल u8 turn_on_stat_set;

#घोषणा AB9540_MODEM_CTRL2_REG			0x23
#घोषणा AB9540_MODEM_CTRL2_SWDBBRSTN_BIT	BIT(2)

/*
 * Map पूर्णांकerrupt numbers to the LATCH and MASK रेजिस्टर offsets, Interrupt
 * numbers are indexed पूर्णांकo this array with (num / 8). The पूर्णांकerupts are
 * defined in linux/mfd/ab8500.h
 *
 * This is one off from the रेजिस्टर names, i.e. AB8500_IT_MASK1_REG is at
 * offset 0.
 */
/* AB8500 support */
अटल स्थिर पूर्णांक ab8500_irq_regoffset[AB8500_NUM_IRQ_REGS] = अणु
	0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 18, 19, 20, 21,
पूर्ण;

/* AB9540 / AB8505 support */
अटल स्थिर पूर्णांक ab9540_irq_regoffset[AB9540_NUM_IRQ_REGS] = अणु
	0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 18, 19, 20, 21, 12, 13, 24, 5, 22, 23
पूर्ण;

/* AB8540 support */
अटल स्थिर पूर्णांक ab8540_irq_regoffset[AB8540_NUM_IRQ_REGS] = अणु
	0, 1, 2, 3, 4, -1, -1, -1, -1, 11, 18, 19, 20, 21, 12, 13, 24, 5, 22,
	23, 25, 26, 27, 28, 29, 30, 31,
पूर्ण;

अटल स्थिर अक्षर ab8500_version_str[][7] = अणु
	[AB8500_VERSION_AB8500] = "AB8500",
	[AB8500_VERSION_AB8505] = "AB8505",
	[AB8500_VERSION_AB9540] = "AB9540",
	[AB8500_VERSION_AB8540] = "AB8540",
पूर्ण;

अटल पूर्णांक ab8500_prcmu_ग_लिखो(काष्ठा ab8500 *ab8500, u16 addr, u8 data)
अणु
	पूर्णांक ret;

	ret = prcmu_abb_ग_लिखो((u8)(addr >> 8), (u8)(addr & 0xFF), &data, 1);
	अगर (ret < 0)
		dev_err(ab8500->dev, "prcmu i2c error %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_prcmu_ग_लिखो_masked(काष्ठा ab8500 *ab8500, u16 addr, u8 mask,
	u8 data)
अणु
	पूर्णांक ret;

	ret = prcmu_abb_ग_लिखो_masked((u8)(addr >> 8), (u8)(addr & 0xFF), &data,
		&mask, 1);
	अगर (ret < 0)
		dev_err(ab8500->dev, "prcmu i2c error %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_prcmu_पढ़ो(काष्ठा ab8500 *ab8500, u16 addr)
अणु
	पूर्णांक ret;
	u8 data;

	ret = prcmu_abb_पढ़ो((u8)(addr >> 8), (u8)(addr & 0xFF), &data, 1);
	अगर (ret < 0) अणु
		dev_err(ab8500->dev, "prcmu i2c error %d\n", ret);
		वापस ret;
	पूर्ण
	वापस (पूर्णांक)data;
पूर्ण

अटल पूर्णांक ab8500_get_chip_id(काष्ठा device *dev)
अणु
	काष्ठा ab8500 *ab8500;

	अगर (!dev)
		वापस -EINVAL;
	ab8500 = dev_get_drvdata(dev->parent);
	वापस ab8500 ? (पूर्णांक)ab8500->chip_id : -EINVAL;
पूर्ण

अटल पूर्णांक set_रेजिस्टर_पूर्णांकerruptible(काष्ठा ab8500 *ab8500, u8 bank,
	u8 reg, u8 data)
अणु
	पूर्णांक ret;
	/*
	 * Put the u8 bank and u8 रेजिस्टर together पूर्णांकo a an u16.
	 * The bank on higher 8 bits and रेजिस्टर in lower 8 bits.
	 */
	u16 addr = ((u16)bank) << 8 | reg;

	dev_vdbg(ab8500->dev, "wr: addr %#x <= %#x\n", addr, data);

	mutex_lock(&ab8500->lock);

	ret = ab8500->ग_लिखो(ab8500, addr, data);
	अगर (ret < 0)
		dev_err(ab8500->dev, "failed to write reg %#x: %d\n",
			addr, ret);
	mutex_unlock(&ab8500->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_set_रेजिस्टर(काष्ठा device *dev, u8 bank,
	u8 reg, u8 value)
अणु
	पूर्णांक ret;
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(dev->parent);

	atomic_inc(&ab8500->transfer_ongoing);
	ret = set_रेजिस्टर_पूर्णांकerruptible(ab8500, bank, reg, value);
	atomic_dec(&ab8500->transfer_ongoing);
	वापस ret;
पूर्ण

अटल पूर्णांक get_रेजिस्टर_पूर्णांकerruptible(काष्ठा ab8500 *ab8500, u8 bank,
	u8 reg, u8 *value)
अणु
	पूर्णांक ret;
	u16 addr = ((u16)bank) << 8 | reg;

	mutex_lock(&ab8500->lock);

	ret = ab8500->पढ़ो(ab8500, addr);
	अगर (ret < 0)
		dev_err(ab8500->dev, "failed to read reg %#x: %d\n",
			addr, ret);
	अन्यथा
		*value = ret;

	mutex_unlock(&ab8500->lock);
	dev_vdbg(ab8500->dev, "rd: addr %#x => data %#x\n", addr, ret);

	वापस (ret < 0) ? ret : 0;
पूर्ण

अटल पूर्णांक ab8500_get_रेजिस्टर(काष्ठा device *dev, u8 bank,
	u8 reg, u8 *value)
अणु
	पूर्णांक ret;
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(dev->parent);

	atomic_inc(&ab8500->transfer_ongoing);
	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, bank, reg, value);
	atomic_dec(&ab8500->transfer_ongoing);
	वापस ret;
पूर्ण

अटल पूर्णांक mask_and_set_रेजिस्टर_पूर्णांकerruptible(काष्ठा ab8500 *ab8500, u8 bank,
	u8 reg, u8 biपंचांगask, u8 bitvalues)
अणु
	पूर्णांक ret;
	u16 addr = ((u16)bank) << 8 | reg;

	mutex_lock(&ab8500->lock);

	अगर (ab8500->ग_लिखो_masked == शून्य) अणु
		u8 data;

		ret = ab8500->पढ़ो(ab8500, addr);
		अगर (ret < 0) अणु
			dev_err(ab8500->dev, "failed to read reg %#x: %d\n",
				addr, ret);
			जाओ out;
		पूर्ण

		data = (u8)ret;
		data = (~biपंचांगask & data) | (biपंचांगask & bitvalues);

		ret = ab8500->ग_लिखो(ab8500, addr, data);
		अगर (ret < 0)
			dev_err(ab8500->dev, "failed to write reg %#x: %d\n",
				addr, ret);

		dev_vdbg(ab8500->dev, "mask: addr %#x => data %#x\n", addr,
			data);
		जाओ out;
	पूर्ण
	ret = ab8500->ग_लिखो_masked(ab8500, addr, biपंचांगask, bitvalues);
	अगर (ret < 0)
		dev_err(ab8500->dev, "failed to modify reg %#x: %d\n", addr,
			ret);
out:
	mutex_unlock(&ab8500->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_mask_and_set_रेजिस्टर(काष्ठा device *dev,
	u8 bank, u8 reg, u8 biपंचांगask, u8 bitvalues)
अणु
	पूर्णांक ret;
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(dev->parent);

	atomic_inc(&ab8500->transfer_ongoing);
	ret = mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab8500, bank, reg,
						 biपंचांगask, bitvalues);
	atomic_dec(&ab8500->transfer_ongoing);
	वापस ret;
पूर्ण

अटल काष्ठा abx500_ops ab8500_ops = अणु
	.get_chip_id = ab8500_get_chip_id,
	.get_रेजिस्टर = ab8500_get_रेजिस्टर,
	.set_रेजिस्टर = ab8500_set_रेजिस्टर,
	.get_रेजिस्टर_page = शून्य,
	.set_रेजिस्टर_page = शून्य,
	.mask_and_set_रेजिस्टर = ab8500_mask_and_set_रेजिस्टर,
	.event_रेजिस्टरs_startup_state_get = शून्य,
	.startup_irq_enabled = शून्य,
	.dump_all_banks = ab8500_dump_all_banks,
पूर्ण;

अटल व्योम ab8500_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा ab8500 *ab8500 = irq_data_get_irq_chip_data(data);

	mutex_lock(&ab8500->irq_lock);
	atomic_inc(&ab8500->transfer_ongoing);
पूर्ण

अटल व्योम ab8500_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा ab8500 *ab8500 = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < ab8500->mask_size; i++) अणु
		u8 old = ab8500->oldmask[i];
		u8 new = ab8500->mask[i];
		पूर्णांक reg;

		अगर (new == old)
			जारी;

		/*
		 * Interrupt रेजिस्टर 12 करोesn't exist prior to AB8500 version
		 * 2.0
		 */
		अगर (ab8500->irq_reg_offset[i] == 11 &&
			is_ab8500_1p1_or_earlier(ab8500))
			जारी;

		अगर (ab8500->irq_reg_offset[i] < 0)
			जारी;

		ab8500->oldmask[i] = new;

		reg = AB8500_IT_MASK1_REG + ab8500->irq_reg_offset[i];
		set_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_INTERRUPT, reg, new);
	पूर्ण
	atomic_dec(&ab8500->transfer_ongoing);
	mutex_unlock(&ab8500->irq_lock);
पूर्ण

अटल व्योम ab8500_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा ab8500 *ab8500 = irq_data_get_irq_chip_data(data);
	पूर्णांक offset = data->hwirq;
	पूर्णांक index = offset / 8;
	पूर्णांक mask = 1 << (offset % 8);

	ab8500->mask[index] |= mask;

	/* The AB8500 GPIOs have two पूर्णांकerrupts each (rising & falling). */
	अगर (offset >= AB8500_INT_GPIO6R && offset <= AB8500_INT_GPIO41R)
		ab8500->mask[index + 2] |= mask;
	अगर (offset >= AB9540_INT_GPIO50R && offset <= AB9540_INT_GPIO54R)
		ab8500->mask[index + 1] |= mask;
	अगर (offset == AB8540_INT_GPIO43R || offset == AB8540_INT_GPIO44R)
		/* Here the falling IRQ is one bit lower */
		ab8500->mask[index] |= (mask << 1);
पूर्ण

अटल व्योम ab8500_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा ab8500 *ab8500 = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक type = irqd_get_trigger_type(data);
	पूर्णांक offset = data->hwirq;
	पूर्णांक index = offset / 8;
	पूर्णांक mask = 1 << (offset % 8);

	अगर (type & IRQ_TYPE_EDGE_RISING)
		ab8500->mask[index] &= ~mask;

	/* The AB8500 GPIOs have two पूर्णांकerrupts each (rising & falling). */
	अगर (type & IRQ_TYPE_EDGE_FALLING) अणु
		अगर (offset >= AB8500_INT_GPIO6R && offset <= AB8500_INT_GPIO41R)
			ab8500->mask[index + 2] &= ~mask;
		अन्यथा अगर (offset >= AB9540_INT_GPIO50R &&
			 offset <= AB9540_INT_GPIO54R)
			ab8500->mask[index + 1] &= ~mask;
		अन्यथा अगर (offset == AB8540_INT_GPIO43R ||
			 offset == AB8540_INT_GPIO44R)
			/* Here the falling IRQ is one bit lower */
			ab8500->mask[index] &= ~(mask << 1);
		अन्यथा
			ab8500->mask[index] &= ~mask;
	पूर्ण अन्यथा अणु
		/* Satisfies the हाल where type is not set. */
		ab8500->mask[index] &= ~mask;
	पूर्ण
पूर्ण

अटल पूर्णांक ab8500_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ab8500_irq_chip = अणु
	.name			= "ab8500",
	.irq_bus_lock		= ab8500_irq_lock,
	.irq_bus_sync_unlock	= ab8500_irq_sync_unlock,
	.irq_mask		= ab8500_irq_mask,
	.irq_disable		= ab8500_irq_mask,
	.irq_unmask		= ab8500_irq_unmask,
	.irq_set_type		= ab8500_irq_set_type,
पूर्ण;

अटल व्योम update_latch_offset(u8 *offset, पूर्णांक i)
अणु
	/* Fix inconsistent ITFromLatch25 bit mapping... */
	अगर (unlikely(*offset == 17))
		*offset = 24;
	/* Fix inconsistent ab8540 bit mapping... */
	अगर (unlikely(*offset == 16))
		*offset = 25;
	अगर ((i == 3) && (*offset >= 24))
		*offset += 2;
पूर्ण

अटल पूर्णांक ab8500_handle_hierarchical_line(काष्ठा ab8500 *ab8500,
					पूर्णांक latch_offset, u8 latch_val)
अणु
	पूर्णांक पूर्णांक_bit, line, i;

	क्रम (i = 0; i < ab8500->mask_size; i++)
		अगर (ab8500->irq_reg_offset[i] == latch_offset)
			अवरोध;

	अगर (i >= ab8500->mask_size) अणु
		dev_err(ab8500->dev, "Register offset 0x%2x not declared\n",
				latch_offset);
		वापस -ENXIO;
	पूर्ण

	/* ignore masked out पूर्णांकerrupts */
	latch_val &= ~ab8500->mask[i];

	जबतक (latch_val) अणु
		पूर्णांक_bit = __ffs(latch_val);
		line = (i << 3) + पूर्णांक_bit;
		latch_val &= ~(1 << पूर्णांक_bit);

		/*
		 * This handles the falling edge hwirqs from the GPIO
		 * lines. Route them back to the line रेजिस्टरed क्रम the
		 * rising IRQ, as this is merely a flag क्रम the same IRQ
		 * in linux terms.
		 */
		अगर (line >= AB8500_INT_GPIO6F && line <= AB8500_INT_GPIO41F)
			line -= 16;
		अगर (line >= AB9540_INT_GPIO50F && line <= AB9540_INT_GPIO54F)
			line -= 8;
		अगर (line == AB8540_INT_GPIO43F || line == AB8540_INT_GPIO44F)
			line += 1;

		handle_nested_irq(irq_create_mapping(ab8500->करोमुख्य, line));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_handle_hierarchical_latch(काष्ठा ab8500 *ab8500,
					पूर्णांक hier_offset, u8 hier_val)
अणु
	पूर्णांक latch_bit, status;
	u8 latch_offset, latch_val;

	करो अणु
		latch_bit = __ffs(hier_val);
		latch_offset = (hier_offset << 3) + latch_bit;

		update_latch_offset(&latch_offset, hier_offset);

		status = get_रेजिस्टर_पूर्णांकerruptible(ab8500,
				AB8500_INTERRUPT,
				AB8500_IT_LATCH1_REG + latch_offset,
				&latch_val);
		अगर (status < 0 || latch_val == 0)
			जाओ discard;

		status = ab8500_handle_hierarchical_line(ab8500,
				latch_offset, latch_val);
		अगर (status < 0)
			वापस status;
discard:
		hier_val &= ~(1 << latch_bit);
	पूर्ण जबतक (hier_val);

	वापस 0;
पूर्ण

अटल irqवापस_t ab8500_hierarchical_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ab8500 *ab8500 = dev;
	u8 i;

	dev_vdbg(ab8500->dev, "interrupt\n");

	/*  Hierarchical पूर्णांकerrupt version */
	क्रम (i = 0; i < (ab8500->it_latchhier_num); i++) अणु
		पूर्णांक status;
		u8 hier_val;

		status = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_INTERRUPT,
			AB8500_IT_LATCHHIER1_REG + i, &hier_val);
		अगर (status < 0 || hier_val == 0)
			जारी;

		status = ab8500_handle_hierarchical_latch(ab8500, i, hier_val);
		अगर (status < 0)
			अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ab8500_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hwirq)
अणु
	काष्ठा ab8500 *ab8500 = d->host_data;

	अगर (!ab8500)
		वापस -EINVAL;

	irq_set_chip_data(virq, ab8500);
	irq_set_chip_and_handler(virq, &ab8500_irq_chip,
				handle_simple_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ab8500_irq_ops = अणु
	.map    = ab8500_irq_map,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक ab8500_irq_init(काष्ठा ab8500 *ab8500, काष्ठा device_node *np)
अणु
	पूर्णांक num_irqs;

	अगर (is_ab8540(ab8500))
		num_irqs = AB8540_NR_IRQS;
	अन्यथा अगर (is_ab9540(ab8500))
		num_irqs = AB9540_NR_IRQS;
	अन्यथा अगर (is_ab8505(ab8500))
		num_irqs = AB8505_NR_IRQS;
	अन्यथा
		num_irqs = AB8500_NR_IRQS;

	/* If ->irq_base is zero this will give a linear mapping */
	ab8500->करोमुख्य = irq_करोमुख्य_add_simple(ab8500->dev->of_node,
					       num_irqs, 0,
					       &ab8500_irq_ops, ab8500);

	अगर (!ab8500->करोमुख्य) अणु
		dev_err(ab8500->dev, "Failed to create irqdomain\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ab8500_suspend(काष्ठा ab8500 *ab8500)
अणु
	अगर (atomic_पढ़ो(&ab8500->transfer_ongoing))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mfd_cell ab8500_bm_devs[] = अणु
	MFD_CELL_OF("ab8500-charger", शून्य, शून्य, 0, 0,
		    "stericsson,ab8500-charger"),
	MFD_CELL_OF("ab8500-btemp", शून्य, शून्य, 0, 0,
		    "stericsson,ab8500-btemp"),
	MFD_CELL_OF("ab8500-fg", शून्य, शून्य, 0, 0,
		    "stericsson,ab8500-fg"),
	MFD_CELL_OF("ab8500-chargalg", शून्य, शून्य, 0, 0,
		    "stericsson,ab8500-chargalg"),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ab8500_devs[] = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	MFD_CELL_OF("ab8500-debug",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-debug"),
#पूर्ण_अगर
	MFD_CELL_OF("ab8500-sysctrl",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-sysctrl"),
	MFD_CELL_OF("ab8500-ext-regulator",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-ext-regulator"),
	MFD_CELL_OF("ab8500-regulator",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-regulator"),
	MFD_CELL_OF("ab8500-clk",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-clk"),
	MFD_CELL_OF("ab8500-gpadc",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-gpadc"),
	MFD_CELL_OF("ab8500-rtc",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-rtc"),
	MFD_CELL_OF("ab8500-acc-det",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-acc-det"),
	MFD_CELL_OF("ab8500-poweron-key",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-poweron-key"),
	MFD_CELL_OF("ab8500-pwm",
		    शून्य, शून्य, 0, 1, "stericsson,ab8500-pwm"),
	MFD_CELL_OF("ab8500-pwm",
		    शून्य, शून्य, 0, 2, "stericsson,ab8500-pwm"),
	MFD_CELL_OF("ab8500-pwm",
		    शून्य, शून्य, 0, 3, "stericsson,ab8500-pwm"),
	MFD_CELL_OF("ab8500-denc",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-denc"),
	MFD_CELL_OF("pinctrl-ab8500",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-gpio"),
	MFD_CELL_OF("abx500-temp",
		    शून्य, शून्य, 0, 0, "stericsson,abx500-temp"),
	MFD_CELL_OF("ab8500-usb",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-usb"),
	MFD_CELL_OF("ab8500-codec",
		    शून्य, शून्य, 0, 0, "stericsson,ab8500-codec"),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ab9540_devs[] = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	अणु
		.name = "ab8500-debug",
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "ab8500-sysctrl",
	पूर्ण,
	अणु
		.name = "ab8500-ext-regulator",
	पूर्ण,
	अणु
		.name = "ab8500-regulator",
	पूर्ण,
	अणु
		.name = "abx500-clk",
		.of_compatible = "stericsson,abx500-clk",
	पूर्ण,
	अणु
		.name = "ab8500-gpadc",
		.of_compatible = "stericsson,ab8500-gpadc",
	पूर्ण,
	अणु
		.name = "ab8500-rtc",
	पूर्ण,
	अणु
		.name = "ab8500-acc-det",
	पूर्ण,
	अणु
		.name = "ab8500-poweron-key",
	पूर्ण,
	अणु
		.name = "ab8500-pwm",
		.id = 1,
	पूर्ण,
	अणु
		.name = "abx500-temp",
	पूर्ण,
	अणु
		.name = "pinctrl-ab9540",
		.of_compatible = "stericsson,ab9540-gpio",
	पूर्ण,
	अणु
		.name = "ab9540-usb",
	पूर्ण,
	अणु
		.name = "ab9540-codec",
	पूर्ण,
	अणु
		.name = "ab-iddet",
	पूर्ण,
पूर्ण;

/* Device list क्रम ab8505  */
अटल स्थिर काष्ठा mfd_cell ab8505_devs[] = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	अणु
		.name = "ab8500-debug",
		.of_compatible = "stericsson,ab8500-debug",
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "ab8500-sysctrl",
		.of_compatible = "stericsson,ab8500-sysctrl",
	पूर्ण,
	अणु
		.name = "ab8500-regulator",
		.of_compatible = "stericsson,ab8505-regulator",
	पूर्ण,
	अणु
		.name = "abx500-clk",
		.of_compatible = "stericsson,ab8500-clk",
	पूर्ण,
	अणु
		.name = "ab8500-gpadc",
		.of_compatible = "stericsson,ab8500-gpadc",
	पूर्ण,
	अणु
		.name = "ab8500-rtc",
		.of_compatible = "stericsson,ab8500-rtc",
	पूर्ण,
	अणु
		.name = "ab8500-acc-det",
		.of_compatible = "stericsson,ab8500-acc-det",
	पूर्ण,
	अणु
		.name = "ab8500-poweron-key",
		.of_compatible = "stericsson,ab8500-poweron-key",
	पूर्ण,
	अणु
		.name = "ab8500-pwm",
		.of_compatible = "stericsson,ab8500-pwm",
		.id = 1,
	पूर्ण,
	अणु
		.name = "pinctrl-ab8505",
		.of_compatible = "stericsson,ab8505-gpio",
	पूर्ण,
	अणु
		.name = "ab8500-usb",
		.of_compatible = "stericsson,ab8500-usb",
	पूर्ण,
	अणु
		.name = "ab8500-codec",
		.of_compatible = "stericsson,ab8500-codec",
	पूर्ण,
	अणु
		.name = "ab-iddet",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ab8540_devs[] = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	अणु
		.name = "ab8500-debug",
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "ab8500-sysctrl",
	पूर्ण,
	अणु
		.name = "ab8500-ext-regulator",
	पूर्ण,
	अणु
		.name = "ab8500-regulator",
	पूर्ण,
	अणु
		.name = "abx500-clk",
		.of_compatible = "stericsson,abx500-clk",
	पूर्ण,
	अणु
		.name = "ab8500-gpadc",
		.of_compatible = "stericsson,ab8500-gpadc",
	पूर्ण,
	अणु
		.name = "ab8500-acc-det",
	पूर्ण,
	अणु
		.name = "ab8500-poweron-key",
	पूर्ण,
	अणु
		.name = "ab8500-pwm",
		.id = 1,
	पूर्ण,
	अणु
		.name = "abx500-temp",
	पूर्ण,
	अणु
		.name = "pinctrl-ab8540",
	पूर्ण,
	अणु
		.name = "ab8540-usb",
	पूर्ण,
	अणु
		.name = "ab8540-codec",
	पूर्ण,
	अणु
		.name = "ab-iddet",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ab8540_cut1_devs[] = अणु
	अणु
		.name = "ab8500-rtc",
		.of_compatible = "stericsson,ab8500-rtc",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ab8540_cut2_devs[] = अणु
	अणु
		.name = "ab8540-rtc",
		.of_compatible = "stericsson,ab8540-rtc",
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार show_chip_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", ab8500 ? ab8500->chip_id : -EINVAL);
पूर्ण

/*
 * ab8500 has चयनed off due to (SWITCH_OFF_STATUS):
 * 0x01 Swoff bit programming
 * 0x02 Thermal protection activation
 * 0x04 Vbat lower then BattOk falling threshold
 * 0x08 Watchकरोg expired
 * 0x10 Non presence of 32kHz घड़ी
 * 0x20 Battery level lower than घातer on reset threshold
 * 0x40 Power on key 1 pressed दीर्घer than 10 seconds
 * 0x80 DB8500 thermal shutकरोwn
 */
अटल sमाप_प्रकार show_चयन_off_status(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 value;
	काष्ठा ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);
	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_RTC,
		AB8500_SWITCH_OFF_STATUS, &value);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%#x\n", value);
पूर्ण

/* use mask and set to override the रेजिस्टर turn_on_stat value */
व्योम ab8500_override_turn_on_stat(u8 mask, u8 set)
अणु
	spin_lock(&on_stat_lock);
	turn_on_stat_mask = mask;
	turn_on_stat_set = set;
	spin_unlock(&on_stat_lock);
पूर्ण

/*
 * ab8500 has turned on due to (TURN_ON_STATUS):
 * 0x01 PORnVbat
 * 0x02 PonKey1dbF
 * 0x04 PonKey2dbF
 * 0x08 RTCAlarm
 * 0x10 MainChDet
 * 0x20 VbusDet
 * 0x40 UsbIDDetect
 * 0x80 Reserved
 */
अटल sमाप_प्रकार show_turn_on_status(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 value;
	काष्ठा ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);
	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_SYS_CTRL1_BLOCK,
		AB8500_TURN_ON_STATUS, &value);
	अगर (ret < 0)
		वापस ret;

	/*
	 * In L9540, turn_on_status रेजिस्टर is not updated correctly अगर
	 * the device is rebooted with AC/USB अक्षरger connected. Due to
	 * this, the device boots android instead of entering पूर्णांकo अक्षरge
	 * only mode. Read the AC/USB status रेजिस्टर to detect the अक्षरger
	 * presence and update the turn on status manually.
	 */
	अगर (is_ab9540(ab8500)) अणु
		spin_lock(&on_stat_lock);
		value = (value & turn_on_stat_mask) | turn_on_stat_set;
		spin_unlock(&on_stat_lock);
	पूर्ण

	वापस प्र_लिखो(buf, "%#x\n", value);
पूर्ण

अटल sमाप_प्रकार show_turn_on_status_2(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 value;
	काष्ठा ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);
	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_SYS_CTRL1_BLOCK,
		AB8505_TURN_ON_STATUS_2, &value);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%#x\n", (value & 0x1));
पूर्ण

अटल sमाप_प्रकार show_ab9540_dbbrstn(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ab8500 *ab8500;
	पूर्णांक ret;
	u8 value;

	ab8500 = dev_get_drvdata(dev);

	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_REGU_CTRL2,
		AB9540_MODEM_CTRL2_REG, &value);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n",
			(value & AB9540_MODEM_CTRL2_SWDBBRSTN_BIT) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार store_ab9540_dbbrstn(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ab8500 *ab8500;
	पूर्णांक ret = count;
	पूर्णांक err;
	u8 bitvalues;

	ab8500 = dev_get_drvdata(dev);

	अगर (count > 0) अणु
		चयन (buf[0]) अणु
		हाल '0':
			bitvalues = 0;
			अवरोध;
		हाल '1':
			bitvalues = AB9540_MODEM_CTRL2_SWDBBRSTN_BIT;
			अवरोध;
		शेष:
			जाओ निकास;
		पूर्ण

		err = mask_and_set_रेजिस्टर_पूर्णांकerruptible(ab8500,
			AB8500_REGU_CTRL2, AB9540_MODEM_CTRL2_REG,
			AB9540_MODEM_CTRL2_SWDBBRSTN_BIT, bitvalues);
		अगर (err)
			dev_info(ab8500->dev,
				"Failed to set DBBRSTN %c, err %#x\n",
				buf[0], err);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(chip_id, S_IRUGO, show_chip_id, शून्य);
अटल DEVICE_ATTR(चयन_off_status, S_IRUGO, show_चयन_off_status, शून्य);
अटल DEVICE_ATTR(turn_on_status, S_IRUGO, show_turn_on_status, शून्य);
अटल DEVICE_ATTR(turn_on_status_2, S_IRUGO, show_turn_on_status_2, शून्य);
अटल DEVICE_ATTR(dbbrstn, S_IRUGO | S_IWUSR,
			show_ab9540_dbbrstn, store_ab9540_dbbrstn);

अटल काष्ठा attribute *ab8500_sysfs_entries[] = अणु
	&dev_attr_chip_id.attr,
	&dev_attr_चयन_off_status.attr,
	&dev_attr_turn_on_status.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ab8505_sysfs_entries[] = अणु
	&dev_attr_turn_on_status_2.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ab9540_sysfs_entries[] = अणु
	&dev_attr_chip_id.attr,
	&dev_attr_चयन_off_status.attr,
	&dev_attr_turn_on_status.attr,
	&dev_attr_dbbrstn.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ab8500_attr_group = अणु
	.attrs	= ab8500_sysfs_entries,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ab8505_attr_group = अणु
	.attrs	= ab8505_sysfs_entries,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ab9540_attr_group = अणु
	.attrs	= ab9540_sysfs_entries,
पूर्ण;

अटल पूर्णांक ab8500_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर अक्षर * स्थिर चयन_off_status[] = अणु
		"Swoff bit programming",
		"Thermal protection activation",
		"Vbat lower then BattOk falling threshold",
		"Watchdog expired",
		"Non presence of 32kHz clock",
		"Battery level lower than power on reset threshold",
		"Power on key 1 pressed longer than 10 seconds",
		"DB8500 thermal shutdown"पूर्ण;
	अटल स्थिर अक्षर * स्थिर turn_on_status[] = अणु
		"Battery rising (Vbat)",
		"Power On Key 1 dbF",
		"Power On Key 2 dbF",
		"RTC Alarm",
		"Main Charger Detect",
		"Vbus Detect (USB)",
		"USB ID Detect",
		"UART Factory Mode Detect"पूर्ण;
	स्थिर काष्ठा platक्रमm_device_id *platid = platक्रमm_get_device_id(pdev);
	क्रमागत ab8500_version version = AB8500_VERSION_UNDEFINED;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ab8500 *ab8500;
	काष्ठा resource *resource;
	पूर्णांक ret;
	पूर्णांक i;
	u8 value;

	ab8500 = devm_kzalloc(&pdev->dev, माप(*ab8500), GFP_KERNEL);
	अगर (!ab8500)
		वापस -ENOMEM;

	ab8500->dev = &pdev->dev;

	resource = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!resource) अणु
		dev_err(&pdev->dev, "no IRQ resource\n");
		वापस -ENODEV;
	पूर्ण

	ab8500->irq = resource->start;

	ab8500->पढ़ो = ab8500_prcmu_पढ़ो;
	ab8500->ग_लिखो = ab8500_prcmu_ग_लिखो;
	ab8500->ग_लिखो_masked = ab8500_prcmu_ग_लिखो_masked;

	mutex_init(&ab8500->lock);
	mutex_init(&ab8500->irq_lock);
	atomic_set(&ab8500->transfer_ongoing, 0);

	platक्रमm_set_drvdata(pdev, ab8500);

	अगर (platid)
		version = platid->driver_data;

	अगर (version != AB8500_VERSION_UNDEFINED)
		ab8500->version = version;
	अन्यथा अणु
		ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_MISC,
			AB8500_IC_NAME_REG, &value);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "could not probe HW\n");
			वापस ret;
		पूर्ण

		ab8500->version = value;
	पूर्ण

	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_MISC,
		AB8500_REV_REG, &value);
	अगर (ret < 0)
		वापस ret;

	ab8500->chip_id = value;

	dev_info(ab8500->dev, "detected chip, %s rev. %1x.%1x\n",
			ab8500_version_str[ab8500->version],
			ab8500->chip_id >> 4,
			ab8500->chip_id & 0x0F);

	/* Configure AB8540 */
	अगर (is_ab8540(ab8500)) अणु
		ab8500->mask_size = AB8540_NUM_IRQ_REGS;
		ab8500->irq_reg_offset = ab8540_irq_regoffset;
		ab8500->it_latchhier_num = AB8540_IT_LATCHHIER_NUM;
	पूर्ण /* Configure AB8500 or AB9540 IRQ */
	अन्यथा अगर (is_ab9540(ab8500) || is_ab8505(ab8500)) अणु
		ab8500->mask_size = AB9540_NUM_IRQ_REGS;
		ab8500->irq_reg_offset = ab9540_irq_regoffset;
		ab8500->it_latchhier_num = AB8500_IT_LATCHHIER_NUM;
	पूर्ण अन्यथा अणु
		ab8500->mask_size = AB8500_NUM_IRQ_REGS;
		ab8500->irq_reg_offset = ab8500_irq_regoffset;
		ab8500->it_latchhier_num = AB8500_IT_LATCHHIER_NUM;
	पूर्ण
	ab8500->mask = devm_kzalloc(&pdev->dev, ab8500->mask_size,
				    GFP_KERNEL);
	अगर (!ab8500->mask)
		वापस -ENOMEM;
	ab8500->oldmask = devm_kzalloc(&pdev->dev, ab8500->mask_size,
				       GFP_KERNEL);
	अगर (!ab8500->oldmask)
		वापस -ENOMEM;

	/*
	 * ab8500 has चयनed off due to (SWITCH_OFF_STATUS):
	 * 0x01 Swoff bit programming
	 * 0x02 Thermal protection activation
	 * 0x04 Vbat lower then BattOk falling threshold
	 * 0x08 Watchकरोg expired
	 * 0x10 Non presence of 32kHz घड़ी
	 * 0x20 Battery level lower than घातer on reset threshold
	 * 0x40 Power on key 1 pressed दीर्घer than 10 seconds
	 * 0x80 DB8500 thermal shutकरोwn
	 */

	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_RTC,
		AB8500_SWITCH_OFF_STATUS, &value);
	अगर (ret < 0)
		वापस ret;
	dev_info(ab8500->dev, "switch off cause(s) (%#x): ", value);

	अगर (value) अणु
		क्रम (i = 0; i < ARRAY_SIZE(चयन_off_status); i++) अणु
			अगर (value & 1)
				pr_cont(" \"%s\"", चयन_off_status[i]);
			value = value >> 1;

		पूर्ण
		pr_cont("\n");
	पूर्ण अन्यथा अणु
		pr_cont(" None\n");
	पूर्ण
	ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_SYS_CTRL1_BLOCK,
		AB8500_TURN_ON_STATUS, &value);
	अगर (ret < 0)
		वापस ret;
	dev_info(ab8500->dev, "turn on reason(s) (%#x): ", value);

	अगर (value) अणु
		क्रम (i = 0; i < ARRAY_SIZE(turn_on_status); i++) अणु
			अगर (value & 1)
				pr_cont("\"%s\" ", turn_on_status[i]);
			value = value >> 1;
		पूर्ण
		pr_cont("\n");
	पूर्ण अन्यथा अणु
		pr_cont("None\n");
	पूर्ण

	अगर (is_ab9540(ab8500)) अणु
		ret = get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_CHARGER,
			AB8500_CH_USBCH_STAT1_REG, &value);
		अगर (ret < 0)
			वापस ret;
		अगर ((value & VBUS_DET_DBNC1) && (value & VBUS_DET_DBNC100))
			ab8500_override_turn_on_stat(~AB8500_POW_KEY_1_ON,
						     AB8500_VBUS_DET);
	पूर्ण

	/* Clear and mask all पूर्णांकerrupts */
	क्रम (i = 0; i < ab8500->mask_size; i++) अणु
		/*
		 * Interrupt रेजिस्टर 12 करोesn't exist prior to AB8500 version
		 * 2.0
		 */
		अगर (ab8500->irq_reg_offset[i] == 11 &&
				is_ab8500_1p1_or_earlier(ab8500))
			जारी;

		अगर (ab8500->irq_reg_offset[i] < 0)
			जारी;

		get_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_INTERRUPT,
			AB8500_IT_LATCH1_REG + ab8500->irq_reg_offset[i],
			&value);
		set_रेजिस्टर_पूर्णांकerruptible(ab8500, AB8500_INTERRUPT,
			AB8500_IT_MASK1_REG + ab8500->irq_reg_offset[i], 0xff);
	पूर्ण

	ret = abx500_रेजिस्टर_ops(ab8500->dev, &ab8500_ops);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ab8500->mask_size; i++)
		ab8500->mask[i] = ab8500->oldmask[i] = 0xff;

	ret = ab8500_irq_init(ab8500, np);
	अगर (ret)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, ab8500->irq, शून्य,
			ab8500_hierarchical_irq,
			IRQF_ONESHOT | IRQF_NO_SUSPEND,
			"ab8500", ab8500);
	अगर (ret)
		वापस ret;

	अगर (is_ab9540(ab8500))
		ret = mfd_add_devices(ab8500->dev, 0, ab9540_devs,
				ARRAY_SIZE(ab9540_devs), शून्य,
				0, ab8500->करोमुख्य);
	अन्यथा अगर (is_ab8540(ab8500)) अणु
		ret = mfd_add_devices(ab8500->dev, 0, ab8540_devs,
			      ARRAY_SIZE(ab8540_devs), शून्य,
			      0, ab8500->करोमुख्य);
		अगर (ret)
			वापस ret;

		अगर (is_ab8540_1p2_or_earlier(ab8500))
			ret = mfd_add_devices(ab8500->dev, 0, ab8540_cut1_devs,
			      ARRAY_SIZE(ab8540_cut1_devs), शून्य,
			      0, ab8500->करोमुख्य);
		अन्यथा /* ab8540 >= cut2 */
			ret = mfd_add_devices(ab8500->dev, 0, ab8540_cut2_devs,
			      ARRAY_SIZE(ab8540_cut2_devs), शून्य,
			      0, ab8500->करोमुख्य);
	पूर्ण अन्यथा अगर (is_ab8505(ab8500))
		ret = mfd_add_devices(ab8500->dev, 0, ab8505_devs,
			      ARRAY_SIZE(ab8505_devs), शून्य,
			      0, ab8500->करोमुख्य);
	अन्यथा
		ret = mfd_add_devices(ab8500->dev, 0, ab8500_devs,
				ARRAY_SIZE(ab8500_devs), शून्य,
				0, ab8500->करोमुख्य);
	अगर (ret)
		वापस ret;

	/* Add battery management devices */
	ret = mfd_add_devices(ab8500->dev, 0, ab8500_bm_devs,
			      ARRAY_SIZE(ab8500_bm_devs), शून्य,
			      0, ab8500->करोमुख्य);
	अगर (ret)
		dev_err(ab8500->dev, "error adding bm devices\n");

	अगर (((is_ab8505(ab8500) || is_ab9540(ab8500)) &&
			ab8500->chip_id >= AB8500_CUT2P0) || is_ab8540(ab8500))
		ret = sysfs_create_group(&ab8500->dev->kobj,
					&ab9540_attr_group);
	अन्यथा
		ret = sysfs_create_group(&ab8500->dev->kobj,
					&ab8500_attr_group);

	अगर ((is_ab8505(ab8500) || is_ab9540(ab8500)) &&
			ab8500->chip_id >= AB8500_CUT2P0)
		ret = sysfs_create_group(&ab8500->dev->kobj,
					 &ab8505_attr_group);

	अगर (ret)
		dev_err(ab8500->dev, "error creating sysfs entries\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ab8500_id[] = अणु
	अणु "ab8500-core", AB8500_VERSION_AB8500 पूर्ण,
	अणु "ab8505-core", AB8500_VERSION_AB8505 पूर्ण,
	अणु "ab9540-i2c", AB8500_VERSION_AB9540 पूर्ण,
	अणु "ab8540-i2c", AB8500_VERSION_AB8540 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_core_driver = अणु
	.driver = अणु
		.name = "ab8500-core",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= ab8500_probe,
	.id_table = ab8500_id,
पूर्ण;

अटल पूर्णांक __init ab8500_core_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_core_driver);
पूर्ण
core_initcall(ab8500_core_init);
