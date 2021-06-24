<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 Power Management Unit (PMU) driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Harald Welte <laक्रमge@खोलोmoko.org>
 * 	   Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/mbc.h>

पूर्णांक pcf50633_रेजिस्टर_irq(काष्ठा pcf50633 *pcf, पूर्णांक irq,
			व्योम (*handler) (पूर्णांक, व्योम *), व्योम *data)
अणु
	अगर (irq < 0 || irq >= PCF50633_NUM_IRQ || !handler)
		वापस -EINVAL;

	अगर (WARN_ON(pcf->irq_handler[irq].handler))
		वापस -EBUSY;

	mutex_lock(&pcf->lock);
	pcf->irq_handler[irq].handler = handler;
	pcf->irq_handler[irq].data = data;
	mutex_unlock(&pcf->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_रेजिस्टर_irq);

पूर्णांक pcf50633_मुक्त_irq(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	अगर (irq < 0 || irq >= PCF50633_NUM_IRQ)
		वापस -EINVAL;

	mutex_lock(&pcf->lock);
	pcf->irq_handler[irq].handler = शून्य;
	mutex_unlock(&pcf->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_मुक्त_irq);

अटल पूर्णांक __pcf50633_irq_mask_set(काष्ठा pcf50633 *pcf, पूर्णांक irq, u8 mask)
अणु
	u8 reg, bit;
	पूर्णांक idx;

	idx = irq >> 3;
	reg = PCF50633_REG_INT1M + idx;
	bit = 1 << (irq & 0x07);

	pcf50633_reg_set_bit_mask(pcf, reg, bit, mask ? bit : 0);

	mutex_lock(&pcf->lock);

	अगर (mask)
		pcf->mask_regs[idx] |= bit;
	अन्यथा
		pcf->mask_regs[idx] &= ~bit;

	mutex_unlock(&pcf->lock);

	वापस 0;
पूर्ण

पूर्णांक pcf50633_irq_mask(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	dev_dbg(pcf->dev, "Masking IRQ %d\n", irq);

	वापस __pcf50633_irq_mask_set(pcf, irq, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_irq_mask);

पूर्णांक pcf50633_irq_unmask(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	dev_dbg(pcf->dev, "Unmasking IRQ %d\n", irq);

	वापस __pcf50633_irq_mask_set(pcf, irq, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_irq_unmask);

पूर्णांक pcf50633_irq_mask_get(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	u8 reg, bits;

	reg =  irq >> 3;
	bits = 1 << (irq & 0x07);

	वापस pcf->mask_regs[reg] & bits;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_irq_mask_get);

अटल व्योम pcf50633_irq_call_handler(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	अगर (pcf->irq_handler[irq].handler)
		pcf->irq_handler[irq].handler(irq, pcf->irq_handler[irq].data);
पूर्ण

/* Maximum amount of समय ONKEY is held beक्रमe emergency action is taken */
#घोषणा PCF50633_ONKEY1S_TIMEOUT 8

अटल irqवापस_t pcf50633_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf50633 *pcf = data;
	पूर्णांक ret, i, j;
	u8 pcf_पूर्णांक[5], chgstat;

	/* Read the 5 INT regs in one transaction */
	ret = pcf50633_पढ़ो_block(pcf, PCF50633_REG_INT1,
						ARRAY_SIZE(pcf_पूर्णांक), pcf_पूर्णांक);
	अगर (ret != ARRAY_SIZE(pcf_पूर्णांक)) अणु
		dev_err(pcf->dev, "Error reading INT registers\n");

		/*
		 * If this करोesn't ACK the interrupt to the chip, we'll be
		 * called once again as we're level triggered.
		 */
		जाओ out;
	पूर्ण

	/* defeat 8s death from lowsys on A5 */
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_OOCSHDWN,  0x04);

	/* We immediately पढ़ो the usb and adapter status. We thus make sure
	 * only of USBINS/USBREM IRQ handlers are called */
	अगर (pcf_पूर्णांक[0] & (PCF50633_INT1_USBINS | PCF50633_INT1_USBREM)) अणु
		chgstat = pcf50633_reg_पढ़ो(pcf, PCF50633_REG_MBCS2);
		अगर (chgstat & (0x3 << 4))
			pcf_पूर्णांक[0] &= ~PCF50633_INT1_USBREM;
		अन्यथा
			pcf_पूर्णांक[0] &= ~PCF50633_INT1_USBINS;
	पूर्ण

	/* Make sure only one of ADPINS or ADPREM is set */
	अगर (pcf_पूर्णांक[0] & (PCF50633_INT1_ADPINS | PCF50633_INT1_ADPREM)) अणु
		chgstat = pcf50633_reg_पढ़ो(pcf, PCF50633_REG_MBCS2);
		अगर (chgstat & (0x3 << 4))
			pcf_पूर्णांक[0] &= ~PCF50633_INT1_ADPREM;
		अन्यथा
			pcf_पूर्णांक[0] &= ~PCF50633_INT1_ADPINS;
	पूर्ण

	dev_dbg(pcf->dev, "INT1=0x%02x INT2=0x%02x INT3=0x%02x "
			"INT4=0x%02x INT5=0x%02x\n", pcf_पूर्णांक[0],
			pcf_पूर्णांक[1], pcf_पूर्णांक[2], pcf_पूर्णांक[3], pcf_पूर्णांक[4]);

	/* Some revisions of the chip करोn't have a 8s standby mode on
	 * ONKEY1S press. We try to manually करो it in such हालs. */
	अगर ((pcf_पूर्णांक[0] & PCF50633_INT1_SECOND) && pcf->onkey1s_held) अणु
		dev_info(pcf->dev, "ONKEY1S held for %d secs\n",
							pcf->onkey1s_held);
		अगर (pcf->onkey1s_held++ == PCF50633_ONKEY1S_TIMEOUT)
			अगर (pcf->pdata->क्रमce_shutकरोwn)
				pcf->pdata->क्रमce_shutकरोwn(pcf);
	पूर्ण

	अगर (pcf_पूर्णांक[2] & PCF50633_INT3_ONKEY1S) अणु
		dev_info(pcf->dev, "ONKEY1S held\n");
		pcf->onkey1s_held = 1 ;

		/* Unmask IRQ_SECOND */
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_INT1M,
						PCF50633_INT1_SECOND);

		/* Unmask IRQ_ONKEYR */
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_INT2M,
						PCF50633_INT2_ONKEYR);
	पूर्ण

	अगर ((pcf_पूर्णांक[1] & PCF50633_INT2_ONKEYR) && pcf->onkey1s_held) अणु
		pcf->onkey1s_held = 0;

		/* Mask SECOND and ONKEYR पूर्णांकerrupts */
		अगर (pcf->mask_regs[0] & PCF50633_INT1_SECOND)
			pcf50633_reg_set_bit_mask(pcf,
					PCF50633_REG_INT1M,
					PCF50633_INT1_SECOND,
					PCF50633_INT1_SECOND);

		अगर (pcf->mask_regs[1] & PCF50633_INT2_ONKEYR)
			pcf50633_reg_set_bit_mask(pcf,
					PCF50633_REG_INT2M,
					PCF50633_INT2_ONKEYR,
					PCF50633_INT2_ONKEYR);
	पूर्ण

	/* Have we just resumed ? */
	अगर (pcf->is_suspended) अणु
		pcf->is_suspended = 0;

		/* Set the resume reason filtering out non resumers */
		क्रम (i = 0; i < ARRAY_SIZE(pcf_पूर्णांक); i++)
			pcf->resume_reason[i] = pcf_पूर्णांक[i] &
						pcf->pdata->resumers[i];

		/* Make sure we करोn't pass on any ONKEY events to
		 * userspace now */
		pcf_पूर्णांक[1] &= ~(PCF50633_INT2_ONKEYR | PCF50633_INT2_ONKEYF);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pcf_पूर्णांक); i++) अणु
		/* Unset masked पूर्णांकerrupts */
		pcf_पूर्णांक[i] &= ~pcf->mask_regs[i];

		क्रम (j = 0; j < 8 ; j++)
			अगर (pcf_पूर्णांक[i] & (1 << j))
				pcf50633_irq_call_handler(pcf, (i * 8) + j);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM

पूर्णांक pcf50633_irq_suspend(काष्ठा pcf50633 *pcf)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u8 res[5];


	/* Make sure our पूर्णांकerrupt handlers are not called
	 * henceक्रमth */
	disable_irq(pcf->irq);

	/* Save the masks */
	ret = pcf50633_पढ़ो_block(pcf, PCF50633_REG_INT1M,
				ARRAY_SIZE(pcf->suspend_irq_masks),
					pcf->suspend_irq_masks);
	अगर (ret < 0) अणु
		dev_err(pcf->dev, "error saving irq masks\n");
		जाओ out;
	पूर्ण

	/* Write wakeup irq masks */
	क्रम (i = 0; i < ARRAY_SIZE(res); i++)
		res[i] = ~pcf->pdata->resumers[i];

	ret = pcf50633_ग_लिखो_block(pcf, PCF50633_REG_INT1M,
					ARRAY_SIZE(res), &res[0]);
	अगर (ret < 0) अणु
		dev_err(pcf->dev, "error writing wakeup irq masks\n");
		जाओ out;
	पूर्ण

	pcf->is_suspended = 1;

out:
	वापस ret;
पूर्ण

पूर्णांक pcf50633_irq_resume(काष्ठा pcf50633 *pcf)
अणु
	पूर्णांक ret;

	/* Write the saved mask रेजिस्टरs */
	ret = pcf50633_ग_लिखो_block(pcf, PCF50633_REG_INT1M,
				ARRAY_SIZE(pcf->suspend_irq_masks),
					pcf->suspend_irq_masks);
	अगर (ret < 0)
		dev_err(pcf->dev, "Error restoring saved suspend masks\n");

	enable_irq(pcf->irq);

	वापस ret;
पूर्ण

#पूर्ण_अगर

पूर्णांक pcf50633_irq_init(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	पूर्णांक ret;

	pcf->irq = irq;

	/* Enable all पूर्णांकerrupts except RTC SECOND */
	pcf->mask_regs[0] = 0x80;
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_INT1M, pcf->mask_regs[0]);
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_INT2M, 0x00);
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_INT3M, 0x00);
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_INT4M, 0x00);
	pcf50633_reg_ग_लिखो(pcf, PCF50633_REG_INT5M, 0x00);

	ret = request_thपढ़ोed_irq(irq, शून्य, pcf50633_irq,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"pcf50633", pcf);

	अगर (ret)
		dev_err(pcf->dev, "Failed to request IRQ %d\n", ret);

	अगर (enable_irq_wake(irq) < 0)
		dev_err(pcf->dev, "IRQ %u cannot be enabled as wake-up source"
			"in this hardware revision", irq);

	वापस ret;
पूर्ण

व्योम pcf50633_irq_मुक्त(काष्ठा pcf50633 *pcf)
अणु
	मुक्त_irq(pcf->irq, pcf);
पूर्ण
