<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * Hardware core part
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/info.h>
#समावेश <sound/vx_core.h>
#समावेश "vx_cmd.h"

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Common routines for Digigram VX drivers");
MODULE_LICENSE("GPL");


/*
 * vx_check_reg_bit - रुको क्रम the specअगरied bit is set/reset on a रेजिस्टर
 * @reg: रेजिस्टर to check
 * @mask: bit mask
 * @bit: resultant bit to be checked
 * @समय: समय-out of loop in msec
 *
 * वापसs zero अगर a bit matches, or a negative error code.
 */
पूर्णांक snd_vx_check_reg_bit(काष्ठा vx_core *chip, पूर्णांक reg, पूर्णांक mask, पूर्णांक bit, पूर्णांक समय)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + (समय * HZ + 999) / 1000;
	अटल स्थिर अक्षर * स्थिर reg_names[VX_REG_MAX] = अणु
		"ICR", "CVR", "ISR", "IVR", "RXH", "RXM", "RXL",
		"DMA", "CDSP", "RFREQ", "RUER/V2", "DATA", "MEMIRQ",
		"ACQ", "BIT0", "BIT1", "MIC0", "MIC1", "MIC2",
		"MIC3", "INTCSR", "CNTRL", "GPIOC",
		"LOFREQ", "HIFREQ", "CSUER", "RUER"
	पूर्ण;

	करो अणु
		अगर ((snd_vx_inb(chip, reg) & mask) == bit)
			वापस 0;
		//msleep(10);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	snd_prपूर्णांकd(KERN_DEBUG "vx_check_reg_bit: timeout, reg=%s, mask=0x%x, val=0x%x\n", reg_names[reg], mask, snd_vx_inb(chip, reg));
	वापस -EIO;
पूर्ण

EXPORT_SYMBOL(snd_vx_check_reg_bit);

/*
 * vx_send_irq_dsp - set command irq bit
 * @num: the requested IRQ type, IRQ_XXX
 *
 * this triggers the specअगरied IRQ request
 * वापसs 0 अगर successful, or a negative error code.
 * 
 */
अटल पूर्णांक vx_send_irq_dsp(काष्ठा vx_core *chip, पूर्णांक num)
अणु
	पूर्णांक nirq;

	/* रुको क्रम Hc = 0 */
	अगर (snd_vx_check_reg_bit(chip, VX_CVR, CVR_HC, 0, 200) < 0)
		वापस -EIO;

	nirq = num;
	अगर (vx_has_new_dsp(chip))
		nirq += VXP_IRQ_OFFSET;
	vx_outb(chip, CVR, (nirq >> 1) | CVR_HC);
	वापस 0;
पूर्ण


/*
 * vx_reset_chk - reset CHK bit on ISR
 *
 * वापसs 0 अगर successful, or a negative error code.
 */
अटल पूर्णांक vx_reset_chk(काष्ठा vx_core *chip)
अणु
	/* Reset irq CHK */
	अगर (vx_send_irq_dsp(chip, IRQ_RESET_CHK) < 0)
		वापस -EIO;
	/* Wait until CHK = 0 */
	अगर (vx_check_isr(chip, ISR_CHK, 0, 200) < 0)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * vx_transfer_end - terminate message transfer
 * @cmd: IRQ message to send (IRQ_MESS_XXX_END)
 *
 * वापसs 0 अगर successful, or a negative error code.
 * the error code can be VX-specअगरic, retrieved via vx_get_error().
 * NB: call with mutex held!
 */
अटल पूर्णांक vx_transfer_end(काष्ठा vx_core *chip, पूर्णांक cmd)
अणु
	पूर्णांक err;

	अगर ((err = vx_reset_chk(chip)) < 0)
		वापस err;

	/* irq MESS_READ/WRITE_END */
	अगर ((err = vx_send_irq_dsp(chip, cmd)) < 0)
		वापस err;

	/* Wait CHK = 1 */
	अगर ((err = vx_रुको_isr_bit(chip, ISR_CHK)) < 0)
		वापस err;

	/* If error, Read RX */
	अगर ((err = vx_inb(chip, ISR)) & ISR_ERR) अणु
		अगर ((err = vx_रुको_क्रम_rx_full(chip)) < 0) अणु
			snd_prपूर्णांकd(KERN_DEBUG "transfer_end: error in rx_full\n");
			वापस err;
		पूर्ण
		err = vx_inb(chip, RXH) << 16;
		err |= vx_inb(chip, RXM) << 8;
		err |= vx_inb(chip, RXL);
		snd_prपूर्णांकd(KERN_DEBUG "transfer_end: error = 0x%x\n", err);
		वापस -(VX_ERR_MASK | err);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * vx_पढ़ो_status - वापस the status rmh
 * @rmh: rmh record to store the status
 *
 * वापसs 0 अगर successful, or a negative error code.
 * the error code can be VX-specअगरic, retrieved via vx_get_error().
 * NB: call with mutex held!
 */
अटल पूर्णांक vx_पढ़ो_status(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh)
अणु
	पूर्णांक i, err, val, size;

	/* no पढ़ो necessary? */
	अगर (rmh->DspStat == RMH_SSIZE_FIXED && rmh->LgStat == 0)
		वापस 0;

	/* Wait क्रम RX full (with समयout protection)
	 * The first word of status is in RX
	 */
	err = vx_रुको_क्रम_rx_full(chip);
	अगर (err < 0)
		वापस err;

	/* Read RX */
	val = vx_inb(chip, RXH) << 16;
	val |= vx_inb(chip, RXM) << 8;
	val |= vx_inb(chip, RXL);

	/* If status given by DSP, let's decode its size */
	चयन (rmh->DspStat) अणु
	हाल RMH_SSIZE_ARG:
		size = val & 0xff;
		rmh->Stat[0] = val & 0xffff00;
		rmh->LgStat = size + 1;
		अवरोध;
	हाल RMH_SSIZE_MASK:
		/* Let's count the arg numbers from a mask */
		rmh->Stat[0] = val;
		size = 0;
		जबतक (val) अणु
			अगर (val & 0x01)
				size++;
			val >>= 1;
		पूर्ण
		rmh->LgStat = size + 1;
		अवरोध;
	शेष:
		/* अन्यथा retrieve the status length given by the driver */
		size = rmh->LgStat;
		rmh->Stat[0] = val;  /* Val is the status 1st word */
		size--;              /* hence adjust reमुख्यing length */
		अवरोध;
        पूर्ण

	अगर (size < 1)
		वापस 0;
	अगर (snd_BUG_ON(size >= SIZE_MAX_STATUS))
		वापस -EINVAL;

	क्रम (i = 1; i <= size; i++) अणु
		/* trigger an irq MESS_WRITE_NEXT */
		err = vx_send_irq_dsp(chip, IRQ_MESS_WRITE_NEXT);
		अगर (err < 0)
			वापस err;
		/* Wait क्रम RX full (with समयout protection) */
		err = vx_रुको_क्रम_rx_full(chip);
		अगर (err < 0)
			वापस err;
		rmh->Stat[i] = vx_inb(chip, RXH) << 16;
		rmh->Stat[i] |= vx_inb(chip, RXM) <<  8;
		rmh->Stat[i] |= vx_inb(chip, RXL);
	पूर्ण

	वापस vx_transfer_end(chip, IRQ_MESS_WRITE_END);
पूर्ण


#घोषणा MASK_MORE_THAN_1_WORD_COMMAND   0x00008000
#घोषणा MASK_1_WORD_COMMAND             0x00ff7fff

/*
 * vx_send_msg_nolock - send a DSP message and पढ़ो back the status
 * @rmh: the rmh record to send and receive
 *
 * वापसs 0 अगर successful, or a negative error code.
 * the error code can be VX-specअगरic, retrieved via vx_get_error().
 * 
 * this function करोesn't call mutex lock at all.
 */
पूर्णांक vx_send_msg_nolock(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh)
अणु
	पूर्णांक i, err;
	
	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

	अगर ((err = vx_reset_chk(chip)) < 0) अणु
		snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: vx_reset_chk error\n");
		वापस err;
	पूर्ण

#अगर 0
	prपूर्णांकk(KERN_DEBUG "rmh: cmd = 0x%06x, length = %d, stype = %d\n",
	       rmh->Cmd[0], rmh->LgCmd, rmh->DspStat);
	अगर (rmh->LgCmd > 1) अणु
		prपूर्णांकk(KERN_DEBUG "  ");
		क्रम (i = 1; i < rmh->LgCmd; i++)
			prपूर्णांकk(KERN_CONT "0x%06x ", rmh->Cmd[i]);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
#पूर्ण_अगर
	/* Check bit M is set according to length of the command */
	अगर (rmh->LgCmd > 1)
		rmh->Cmd[0] |= MASK_MORE_THAN_1_WORD_COMMAND;
	अन्यथा
		rmh->Cmd[0] &= MASK_1_WORD_COMMAND;

	/* Wait क्रम TX empty */
	अगर ((err = vx_रुको_isr_bit(chip, ISR_TX_EMPTY)) < 0) अणु
		snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: wait tx empty error\n");
		वापस err;
	पूर्ण

	/* Write Cmd[0] */
	vx_outb(chip, TXH, (rmh->Cmd[0] >> 16) & 0xff);
	vx_outb(chip, TXM, (rmh->Cmd[0] >> 8) & 0xff);
	vx_outb(chip, TXL, rmh->Cmd[0] & 0xff);

	/* Trigger irq MESSAGE */
	अगर ((err = vx_send_irq_dsp(chip, IRQ_MESSAGE)) < 0) अणु
		snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: send IRQ_MESSAGE error\n");
		वापस err;
	पूर्ण

	/* Wait क्रम CHK = 1 */
	अगर ((err = vx_रुको_isr_bit(chip, ISR_CHK)) < 0)
		वापस err;

	/* If error, get error value from RX */
	अगर (vx_inb(chip, ISR) & ISR_ERR) अणु
		अगर ((err = vx_रुको_क्रम_rx_full(chip)) < 0) अणु
			snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: rx_full read error\n");
			वापस err;
		पूर्ण
		err = vx_inb(chip, RXH) << 16;
		err |= vx_inb(chip, RXM) << 8;
		err |= vx_inb(chip, RXL);
		snd_prपूर्णांकd(KERN_DEBUG "msg got error = 0x%x at cmd[0]\n", err);
		err = -(VX_ERR_MASK | err);
		वापस err;
	पूर्ण

	/* Send the other words */
	अगर (rmh->LgCmd > 1) अणु
		क्रम (i = 1; i < rmh->LgCmd; i++) अणु
			/* Wait क्रम TX पढ़ोy */
			अगर ((err = vx_रुको_isr_bit(chip, ISR_TX_READY)) < 0) अणु
				snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: tx_ready error\n");
				वापस err;
			पूर्ण

			/* Write Cmd[i] */
			vx_outb(chip, TXH, (rmh->Cmd[i] >> 16) & 0xff);
			vx_outb(chip, TXM, (rmh->Cmd[i] >> 8) & 0xff);
			vx_outb(chip, TXL, rmh->Cmd[i] & 0xff);

			/* Trigger irq MESS_READ_NEXT */
			अगर ((err = vx_send_irq_dsp(chip, IRQ_MESS_READ_NEXT)) < 0) अणु
				snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: IRQ_READ_NEXT error\n");
				वापस err;
			पूर्ण
		पूर्ण
		/* Wait क्रम TX empty */
		अगर ((err = vx_रुको_isr_bit(chip, ISR_TX_READY)) < 0) अणु
			snd_prपूर्णांकd(KERN_DEBUG "vx_send_msg: TX_READY error\n");
			वापस err;
		पूर्ण
		/* End of transfer */
		err = vx_transfer_end(chip, IRQ_MESS_READ_END);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस vx_पढ़ो_status(chip, rmh);
पूर्ण


/*
 * vx_send_msg - send a DSP message with mutex
 * @rmh: the rmh record to send and receive
 *
 * वापसs 0 अगर successful, or a negative error code.
 * see vx_send_msg_nolock().
 */
पूर्णांक vx_send_msg(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh)
अणु
	पूर्णांक err;

	mutex_lock(&chip->lock);
	err = vx_send_msg_nolock(chip, rmh);
	mutex_unlock(&chip->lock);
	वापस err;
पूर्ण


/*
 * vx_send_rih_nolock - send an RIH to xilinx
 * @cmd: the command to send
 *
 * वापसs 0 अगर successful, or a negative error code.
 * the error code can be VX-specअगरic, retrieved via vx_get_error().
 *
 * this function करोesn't call mutex at all.
 *
 * unlike RMH, no command is sent to DSP.
 */
पूर्णांक vx_send_rih_nolock(काष्ठा vx_core *chip, पूर्णांक cmd)
अणु
	पूर्णांक err;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

#अगर 0
	prपूर्णांकk(KERN_DEBUG "send_rih: cmd = 0x%x\n", cmd);
#पूर्ण_अगर
	अगर ((err = vx_reset_chk(chip)) < 0)
		वापस err;
	/* send the IRQ */
	अगर ((err = vx_send_irq_dsp(chip, cmd)) < 0)
		वापस err;
	/* Wait CHK = 1 */
	अगर ((err = vx_रुको_isr_bit(chip, ISR_CHK)) < 0)
		वापस err;
	/* If error, पढ़ो RX */
	अगर (vx_inb(chip, ISR) & ISR_ERR) अणु
		अगर ((err = vx_रुको_क्रम_rx_full(chip)) < 0)
			वापस err;
		err = vx_inb(chip, RXH) << 16;
		err |= vx_inb(chip, RXM) << 8;
		err |= vx_inb(chip, RXL);
		वापस -(VX_ERR_MASK | err);
	पूर्ण
	वापस 0;
पूर्ण


/*
 * vx_send_rih - send an RIH with mutex
 * @cmd: the command to send
 *
 * see vx_send_rih_nolock().
 */
पूर्णांक vx_send_rih(काष्ठा vx_core *chip, पूर्णांक cmd)
अणु
	पूर्णांक err;

	mutex_lock(&chip->lock);
	err = vx_send_rih_nolock(chip, cmd);
	mutex_unlock(&chip->lock);
	वापस err;
पूर्ण

#घोषणा END_OF_RESET_WAIT_TIME		500	/* us */

/**
 * snd_vx_load_boot_image - boot up the xilinx पूर्णांकerface
 * @chip: VX core instance
 * @boot: the boot record to load
 */
पूर्णांक snd_vx_load_boot_image(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *boot)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक no_fillup = vx_has_new_dsp(chip);

	/* check the length of boot image */
	अगर (boot->size <= 0)
		वापस -EINVAL;
	अगर (boot->size % 3)
		वापस -EINVAL;
#अगर 0
	अणु
		/* more strict check */
		अचिन्हित पूर्णांक c = ((u32)boot->data[0] << 16) | ((u32)boot->data[1] << 8) | boot->data[2];
		अगर (boot->size != (c + 2) * 3)
			वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	/* reset dsp */
	vx_reset_dsp(chip);
	
	udelay(END_OF_RESET_WAIT_TIME); /* another रुको? */

	/* करोwnload boot strap */
	क्रम (i = 0; i < 0x600; i += 3) अणु
		अगर (i >= boot->size) अणु
			अगर (no_fillup)
				अवरोध;
			अगर (vx_रुको_isr_bit(chip, ISR_TX_EMPTY) < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "dsp boot failed at %d\n", i);
				वापस -EIO;
			पूर्ण
			vx_outb(chip, TXH, 0);
			vx_outb(chip, TXM, 0);
			vx_outb(chip, TXL, 0);
		पूर्ण अन्यथा अणु
			स्थिर अचिन्हित अक्षर *image = boot->data + i;
			अगर (vx_रुको_isr_bit(chip, ISR_TX_EMPTY) < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "dsp boot failed at %d\n", i);
				वापस -EIO;
			पूर्ण
			vx_outb(chip, TXH, image[0]);
			vx_outb(chip, TXM, image[1]);
			vx_outb(chip, TXL, image[2]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_vx_load_boot_image);

/*
 * vx_test_irq_src - query the source of पूर्णांकerrupts
 *
 * called from irq handler only
 */
अटल पूर्णांक vx_test_irq_src(काष्ठा vx_core *chip, अचिन्हित पूर्णांक *ret)
अणु
	पूर्णांक err;

	vx_init_rmh(&chip->irq_rmh, CMD_TEST_IT);
	mutex_lock(&chip->lock);
	err = vx_send_msg_nolock(chip, &chip->irq_rmh);
	अगर (err < 0)
		*ret = 0;
	अन्यथा
		*ret = chip->irq_rmh.Stat[0];
	mutex_unlock(&chip->lock);
	वापस err;
पूर्ण


/*
 * snd_vx_thपढ़ोed_irq_handler - thपढ़ोed irq handler
 */
irqवापस_t snd_vx_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा vx_core *chip = dev;
	अचिन्हित पूर्णांक events;
		
	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस IRQ_HANDLED;

	अगर (vx_test_irq_src(chip, &events) < 0)
		वापस IRQ_HANDLED;
    
#अगर 0
	अगर (events & 0x000800)
		prपूर्णांकk(KERN_ERR "DSP Stream underrun ! IRQ events = 0x%x\n", events);
#पूर्ण_अगर
	// prपूर्णांकk(KERN_DEBUG "IRQ events = 0x%x\n", events);

	/* We must prevent any application using this DSP
	 * and block any further request until the application
	 * either unरेजिस्टरs or reloads the DSP
	 */
	अगर (events & FATAL_DSP_ERROR) अणु
		snd_prपूर्णांकk(KERN_ERR "vx_core: fatal DSP error!!\n");
		वापस IRQ_HANDLED;
	पूर्ण

	/* The start on समय code conditions are filled (ie the समय code
	 * received by the board is equal to one of those given to it).
	 */
	अगर (events & TIME_CODE_EVENT_PENDING) अणु
		; /* so far, nothing to करो yet */
	पूर्ण

	/* The frequency has changed on the board (UER mode). */
	अगर (events & FREQUENCY_CHANGE_EVENT_PENDING)
		vx_change_frequency(chip);

	/* update the pcm streams */
	vx_pcm_update_पूर्णांकr(chip, events);
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(snd_vx_thपढ़ोed_irq_handler);

/**
 * snd_vx_irq_handler - पूर्णांकerrupt handler
 * @irq: irq number
 * @dev: VX core instance
 */
irqवापस_t snd_vx_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा vx_core *chip = dev;

	अगर (! (chip->chip_status & VX_STAT_CHIP_INIT) ||
	    (chip->chip_status & VX_STAT_IS_STALE))
		वापस IRQ_NONE;
	अगर (! vx_test_and_ack(chip))
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_NONE;
पूर्ण

EXPORT_SYMBOL(snd_vx_irq_handler);

/*
 */
अटल व्योम vx_reset_board(काष्ठा vx_core *chip, पूर्णांक cold_reset)
अणु
	अगर (snd_BUG_ON(!chip->ops->reset_board))
		वापस;

	/* current source, later sync'ed with target */
	chip->audio_source = VX_AUDIO_SRC_LINE;
	अगर (cold_reset) अणु
		chip->audio_source_target = chip->audio_source;
		chip->घड़ी_source = INTERNAL_QUARTZ;
		chip->घड़ी_mode = VX_CLOCK_MODE_AUTO;
		chip->freq = 48000;
		chip->uer_detected = VX_UER_MODE_NOT_PRESENT;
		chip->uer_bits = SNDRV_PCM_DEFAULT_CON_SPDIF;
	पूर्ण

	chip->ops->reset_board(chip, cold_reset);

	vx_reset_codec(chip, cold_reset);

	vx_set_पूर्णांकernal_घड़ी(chip, chip->freq);

	/* Reset the DSP */
	vx_reset_dsp(chip);

	अगर (vx_is_pcmcia(chip)) अणु
		/* Acknowledge any pending IRQ and reset the MEMIRQ flag. */
		vx_test_and_ack(chip);
		vx_validate_irq(chip, 1);
	पूर्ण

	/* init CBits */
	vx_set_iec958_status(chip, chip->uer_bits);
पूर्ण


/*
 * proc पूर्णांकerface
 */

अटल व्योम vx_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा vx_core *chip = entry->निजी_data;
	अटल स्थिर अक्षर * स्थिर audio_src_vxp[] = अणु "Line", "Mic", "Digital" पूर्ण;
	अटल स्थिर अक्षर * स्थिर audio_src_vx2[] = अणु "Analog", "Analog", "Digital" पूर्ण;
	अटल स्थिर अक्षर * स्थिर घड़ी_mode[] = अणु "Auto", "Internal", "External" पूर्ण;
	अटल स्थिर अक्षर * स्थिर घड़ी_src[] = अणु "Internal", "External" पूर्ण;
	अटल स्थिर अक्षर * स्थिर uer_type[] = अणु "Consumer", "Professional", "Not Present" पूर्ण;
	
	snd_iम_लिखो(buffer, "%s\n", chip->card->दीर्घname);
	snd_iम_लिखो(buffer, "Xilinx Firmware: %s\n",
		    (chip->chip_status & VX_STAT_XILINX_LOADED) ? "Loaded" : "No");
	snd_iम_लिखो(buffer, "Device Initialized: %s\n",
		    (chip->chip_status & VX_STAT_DEVICE_INIT) ? "Yes" : "No");
	snd_iम_लिखो(buffer, "DSP audio info:");
	अगर (chip->audio_info & VX_AUDIO_INFO_REAL_TIME)
		snd_iम_लिखो(buffer, " realtime");
	अगर (chip->audio_info & VX_AUDIO_INFO_OFFLINE)
		snd_iम_लिखो(buffer, " offline");
	अगर (chip->audio_info & VX_AUDIO_INFO_MPEG1)
		snd_iम_लिखो(buffer, " mpeg1");
	अगर (chip->audio_info & VX_AUDIO_INFO_MPEG2)
		snd_iम_लिखो(buffer, " mpeg2");
	अगर (chip->audio_info & VX_AUDIO_INFO_LINEAR_8)
		snd_iम_लिखो(buffer, " linear8");
	अगर (chip->audio_info & VX_AUDIO_INFO_LINEAR_16)
		snd_iम_लिखो(buffer, " linear16");
	अगर (chip->audio_info & VX_AUDIO_INFO_LINEAR_24)
		snd_iम_लिखो(buffer, " linear24");
	snd_iम_लिखो(buffer, "\n");
	snd_iम_लिखो(buffer, "Input Source: %s\n", vx_is_pcmcia(chip) ?
		    audio_src_vxp[chip->audio_source] :
		    audio_src_vx2[chip->audio_source]);
	snd_iम_लिखो(buffer, "Clock Mode: %s\n", घड़ी_mode[chip->घड़ी_mode]);
	snd_iम_लिखो(buffer, "Clock Source: %s\n", घड़ी_src[chip->घड़ी_source]);
	snd_iम_लिखो(buffer, "Frequency: %d\n", chip->freq);
	snd_iम_लिखो(buffer, "Detected Frequency: %d\n", chip->freq_detected);
	snd_iम_लिखो(buffer, "Detected UER type: %s\n", uer_type[chip->uer_detected]);
	snd_iम_लिखो(buffer, "Min/Max/Cur IBL: %d/%d/%d (granularity=%d)\n",
		    chip->ibl.min_size, chip->ibl.max_size, chip->ibl.size,
		    chip->ibl.granularity);
पूर्ण

अटल व्योम vx_proc_init(काष्ठा vx_core *chip)
अणु
	snd_card_ro_proc_new(chip->card, "vx-status", chip, vx_proc_पढ़ो);
पूर्ण


/**
 * snd_vx_dsp_boot - load the DSP boot
 * @chip: VX core instance
 * @boot: firmware data
 */
पूर्णांक snd_vx_dsp_boot(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *boot)
अणु
	पूर्णांक err;
	पूर्णांक cold_reset = !(chip->chip_status & VX_STAT_DEVICE_INIT);

	vx_reset_board(chip, cold_reset);
	vx_validate_irq(chip, 0);

	अगर ((err = snd_vx_load_boot_image(chip, boot)) < 0)
		वापस err;
	msleep(10);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_vx_dsp_boot);

/**
 * snd_vx_dsp_load - load the DSP image
 * @chip: VX core instance
 * @dsp: firmware data
 */
पूर्णांक snd_vx_dsp_load(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *dsp)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	अचिन्हित पूर्णांक csum = 0;
	स्थिर अचिन्हित अक्षर *image, *cptr;

	अगर (dsp->size % 3)
		वापस -EINVAL;

	vx_toggle_dac_mute(chip, 1);

	/* Transfert data buffer from PC to DSP */
	क्रम (i = 0; i < dsp->size; i += 3) अणु
		image = dsp->data + i;
		/* Wait DSP पढ़ोy क्रम a new पढ़ो */
		अगर ((err = vx_रुको_isr_bit(chip, ISR_TX_EMPTY)) < 0) अणु
			prपूर्णांकk(KERN_ERR
			       "dsp loading error at position %d\n", i);
			वापस err;
		पूर्ण
		cptr = image;
		csum ^= *cptr;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXH, *cptr++);
		csum ^= *cptr;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXM, *cptr++);
		csum ^= *cptr;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXL, *cptr++);
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "checksum = 0x%08x\n", csum);

	msleep(200);

	अगर ((err = vx_रुको_isr_bit(chip, ISR_CHK)) < 0)
		वापस err;

	vx_toggle_dac_mute(chip, 0);

	vx_test_and_ack(chip);
	vx_validate_irq(chip, 1);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_vx_dsp_load);

#अगर_घोषित CONFIG_PM
/*
 * suspend
 */
पूर्णांक snd_vx_suspend(काष्ठा vx_core *chip)
अणु
	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D3hot);
	chip->chip_status |= VX_STAT_IN_SUSPEND;

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_vx_suspend);

/*
 * resume
 */
पूर्णांक snd_vx_resume(काष्ठा vx_core *chip)
अणु
	पूर्णांक i, err;

	chip->chip_status &= ~VX_STAT_CHIP_INIT;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (! chip->firmware[i])
			जारी;
		err = chip->ops->load_dsp(chip, i, chip->firmware[i]);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "vx: firmware resume error at DSP %d\n", i);
			वापस -EIO;
		पूर्ण
	पूर्ण

	chip->chip_status |= VX_STAT_CHIP_INIT;
	chip->chip_status &= ~VX_STAT_IN_SUSPEND;

	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_vx_resume);
#पूर्ण_अगर

/**
 * snd_vx_create - स्थिरructor क्रम काष्ठा vx_core
 * @card: card instance
 * @hw: hardware specअगरic record
 * @ops: VX ops poपूर्णांकer
 * @extra_size: extra byte size to allocate appending to chip
 *
 * this function allocates the instance and prepare क्रम the hardware
 * initialization.
 *
 * वापस the instance poपूर्णांकer अगर successful, शून्य in error.
 */
काष्ठा vx_core *snd_vx_create(काष्ठा snd_card *card,
			      स्थिर काष्ठा snd_vx_hardware *hw,
			      स्थिर काष्ठा snd_vx_ops *ops,
			      पूर्णांक extra_size)
अणु
	काष्ठा vx_core *chip;

	अगर (snd_BUG_ON(!card || !hw || !ops))
		वापस शून्य;

	chip = kzalloc(माप(*chip) + extra_size, GFP_KERNEL);
	अगर (! chip)
		वापस शून्य;
	mutex_init(&chip->lock);
	chip->irq = -1;
	chip->hw = hw;
	chip->type = hw->type;
	chip->ops = ops;
	mutex_init(&chip->mixer_mutex);

	chip->card = card;
	card->निजी_data = chip;
	म_नकल(card->driver, hw->name);
	प्र_लिखो(card->लघुname, "Digigram %s", hw->name);

	vx_proc_init(chip);

	वापस chip;
पूर्ण

EXPORT_SYMBOL(snd_vx_create);
