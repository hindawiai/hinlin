<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Filename: core.c
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/genhd.h>
#समावेश <linux/idr.h>

#समावेश "rsxx_priv.h"
#समावेश "rsxx_cfg.h"

#घोषणा NO_LEGACY 0
#घोषणा SYNC_START_TIMEOUT (10 * 60) /* 10 minutes */

MODULE_DESCRIPTION("IBM Flash Adapter 900GB Full Height Device Driver");
MODULE_AUTHOR("Joshua Morris/Philip Kelleher, IBM");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

अटल अचिन्हित पूर्णांक क्रमce_legacy = NO_LEGACY;
module_param(क्रमce_legacy, uपूर्णांक, 0444);
MODULE_PARM_DESC(क्रमce_legacy, "Force the use of legacy type PCI interrupts");

अटल अचिन्हित पूर्णांक sync_start = 1;
module_param(sync_start, uपूर्णांक, 0444);
MODULE_PARM_DESC(sync_start, "On by Default: Driver load will not complete "
			     "until the card startup has completed.");

अटल DEFINE_IDA(rsxx_disk_ida);

/* --------------------Debugfs Setup ------------------- */

अटल पूर्णांक rsxx_attr_pci_regs_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा rsxx_cardinfo *card = m->निजी;

	seq_म_लिखो(m, "HWID		0x%08x\n",
					ioपढ़ो32(card->regmap + HWID));
	seq_म_लिखो(m, "SCRATCH		0x%08x\n",
					ioपढ़ो32(card->regmap + SCRATCH));
	seq_म_लिखो(m, "IER		0x%08x\n",
					ioपढ़ो32(card->regmap + IER));
	seq_म_लिखो(m, "IPR		0x%08x\n",
					ioपढ़ो32(card->regmap + IPR));
	seq_म_लिखो(m, "CREG_CMD		0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_CMD));
	seq_म_लिखो(m, "CREG_ADD		0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_ADD));
	seq_म_लिखो(m, "CREG_CNT		0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_CNT));
	seq_म_लिखो(m, "CREG_STAT	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_STAT));
	seq_म_लिखो(m, "CREG_DATA0	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA0));
	seq_म_लिखो(m, "CREG_DATA1	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA1));
	seq_म_लिखो(m, "CREG_DATA2	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA2));
	seq_म_लिखो(m, "CREG_DATA3	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA3));
	seq_म_लिखो(m, "CREG_DATA4	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA4));
	seq_म_लिखो(m, "CREG_DATA5	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA5));
	seq_म_लिखो(m, "CREG_DATA6	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA6));
	seq_म_लिखो(m, "CREG_DATA7	0x%08x\n",
					ioपढ़ो32(card->regmap + CREG_DATA7));
	seq_म_लिखो(m, "INTR_COAL	0x%08x\n",
					ioपढ़ो32(card->regmap + INTR_COAL));
	seq_म_लिखो(m, "HW_ERROR		0x%08x\n",
					ioपढ़ो32(card->regmap + HW_ERROR));
	seq_म_लिखो(m, "DEBUG0		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG0));
	seq_म_लिखो(m, "DEBUG1		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG1));
	seq_म_लिखो(m, "DEBUG2		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG2));
	seq_म_लिखो(m, "DEBUG3		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG3));
	seq_म_लिखो(m, "DEBUG4		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG4));
	seq_म_लिखो(m, "DEBUG5		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG5));
	seq_म_लिखो(m, "DEBUG6		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG6));
	seq_म_लिखो(m, "DEBUG7		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_DEBUG7));
	seq_म_लिखो(m, "RECONFIG		0x%08x\n",
					ioपढ़ो32(card->regmap + PCI_RECONFIG));

	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_attr_stats_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा rsxx_cardinfo *card = m->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		seq_म_लिखो(m, "Ctrl %d CRC Errors	= %d\n",
				i, card->ctrl[i].stats.crc_errors);
		seq_म_लिखो(m, "Ctrl %d Hard Errors	= %d\n",
				i, card->ctrl[i].stats.hard_errors);
		seq_म_लिखो(m, "Ctrl %d Soft Errors	= %d\n",
				i, card->ctrl[i].stats.soft_errors);
		seq_म_लिखो(m, "Ctrl %d Writes Issued	= %d\n",
				i, card->ctrl[i].stats.ग_लिखोs_issued);
		seq_म_लिखो(m, "Ctrl %d Writes Failed	= %d\n",
				i, card->ctrl[i].stats.ग_लिखोs_failed);
		seq_म_लिखो(m, "Ctrl %d Reads Issued	= %d\n",
				i, card->ctrl[i].stats.पढ़ोs_issued);
		seq_म_लिखो(m, "Ctrl %d Reads Failed	= %d\n",
				i, card->ctrl[i].stats.पढ़ोs_failed);
		seq_म_लिखो(m, "Ctrl %d Reads Retried	= %d\n",
				i, card->ctrl[i].stats.पढ़ोs_retried);
		seq_म_लिखो(m, "Ctrl %d Discards Issued	= %d\n",
				i, card->ctrl[i].stats.discards_issued);
		seq_म_लिखो(m, "Ctrl %d Discards Failed	= %d\n",
				i, card->ctrl[i].stats.discards_failed);
		seq_म_लिखो(m, "Ctrl %d DMA SW Errors	= %d\n",
				i, card->ctrl[i].stats.dma_sw_err);
		seq_म_लिखो(m, "Ctrl %d DMA HW Faults	= %d\n",
				i, card->ctrl[i].stats.dma_hw_fault);
		seq_म_लिखो(m, "Ctrl %d DMAs Cancelled	= %d\n",
				i, card->ctrl[i].stats.dma_cancelled);
		seq_म_लिखो(m, "Ctrl %d SW Queue Depth	= %d\n",
				i, card->ctrl[i].stats.sw_q_depth);
		seq_म_लिखो(m, "Ctrl %d HW Queue Depth	= %d\n",
			i, atomic_पढ़ो(&card->ctrl[i].stats.hw_q_depth));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_attr_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsxx_attr_stats_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक rsxx_attr_pci_regs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsxx_attr_pci_regs_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार rsxx_cram_पढ़ो(काष्ठा file *fp, अक्षर __user *ubuf,
			      माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा rsxx_cardinfo *card = file_inode(fp)->i_निजी;
	अक्षर *buf;
	पूर्णांक st;

	buf = kzalloc(cnt, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	st = rsxx_creg_पढ़ो(card, CREG_ADD_CRAM + (u32)*ppos, cnt, buf, 1);
	अगर (!st) अणु
		अगर (copy_to_user(ubuf, buf, cnt))
			st = -EFAULT;
	पूर्ण
	kमुक्त(buf);
	अगर (st)
		वापस st;
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार rsxx_cram_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा rsxx_cardinfo *card = file_inode(fp)->i_निजी;
	अक्षर *buf;
	sमाप_प्रकार st;

	buf = memdup_user(ubuf, cnt);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	st = rsxx_creg_ग_लिखो(card, CREG_ADD_CRAM + (u32)*ppos, cnt, buf, 1);
	kमुक्त(buf);
	अगर (st)
		वापस st;
	*ppos += cnt;
	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_cram_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rsxx_cram_पढ़ो,
	.ग_लिखो		= rsxx_cram_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_stats_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rsxx_attr_stats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_pci_regs_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rsxx_attr_pci_regs_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम rsxx_debugfs_dev_new(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा dentry *debugfs_stats;
	काष्ठा dentry *debugfs_pci_regs;
	काष्ठा dentry *debugfs_cram;

	card->debugfs_dir = debugfs_create_dir(card->gendisk->disk_name, शून्य);
	अगर (IS_ERR_OR_शून्य(card->debugfs_dir))
		जाओ failed_debugfs_dir;

	debugfs_stats = debugfs_create_file("stats", 0444,
					    card->debugfs_dir, card,
					    &debugfs_stats_fops);
	अगर (IS_ERR_OR_शून्य(debugfs_stats))
		जाओ failed_debugfs_stats;

	debugfs_pci_regs = debugfs_create_file("pci_regs", 0444,
					       card->debugfs_dir, card,
					       &debugfs_pci_regs_fops);
	अगर (IS_ERR_OR_शून्य(debugfs_pci_regs))
		जाओ failed_debugfs_pci_regs;

	debugfs_cram = debugfs_create_file("cram", 0644,
					   card->debugfs_dir, card,
					   &debugfs_cram_fops);
	अगर (IS_ERR_OR_शून्य(debugfs_cram))
		जाओ failed_debugfs_cram;

	वापस;
failed_debugfs_cram:
	debugfs_हटाओ(debugfs_pci_regs);
failed_debugfs_pci_regs:
	debugfs_हटाओ(debugfs_stats);
failed_debugfs_stats:
	debugfs_हटाओ(card->debugfs_dir);
failed_debugfs_dir:
	card->debugfs_dir = शून्य;
पूर्ण

/*----------------- Interrupt Control & Handling -------------------*/

अटल व्योम rsxx_mask_पूर्णांकerrupts(काष्ठा rsxx_cardinfo *card)
अणु
	card->isr_mask = 0;
	card->ier_mask = 0;
पूर्ण

अटल व्योम __enable_पूर्णांकr(अचिन्हित पूर्णांक *mask, अचिन्हित पूर्णांक पूर्णांकr)
अणु
	*mask |= पूर्णांकr;
पूर्ण

अटल व्योम __disable_पूर्णांकr(अचिन्हित पूर्णांक *mask, अचिन्हित पूर्णांक पूर्णांकr)
अणु
	*mask &= ~पूर्णांकr;
पूर्ण

/*
 * NOTE: Disabling the IER will disable the hardware पूर्णांकerrupt.
 * Disabling the ISR will disable the software handling of the ISR bit.
 *
 * Enable/Disable पूर्णांकerrupt functions assume the card->irq_lock
 * is held by the caller.
 */
व्योम rsxx_enable_ier(काष्ठा rsxx_cardinfo *card, अचिन्हित पूर्णांक पूर्णांकr)
अणु
	अगर (unlikely(card->halt) ||
	    unlikely(card->eeh_state))
		वापस;

	__enable_पूर्णांकr(&card->ier_mask, पूर्णांकr);
	ioग_लिखो32(card->ier_mask, card->regmap + IER);
पूर्ण

व्योम rsxx_disable_ier(काष्ठा rsxx_cardinfo *card, अचिन्हित पूर्णांक पूर्णांकr)
अणु
	अगर (unlikely(card->eeh_state))
		वापस;

	__disable_पूर्णांकr(&card->ier_mask, पूर्णांकr);
	ioग_लिखो32(card->ier_mask, card->regmap + IER);
पूर्ण

व्योम rsxx_enable_ier_and_isr(काष्ठा rsxx_cardinfo *card,
				 अचिन्हित पूर्णांक पूर्णांकr)
अणु
	अगर (unlikely(card->halt) ||
	    unlikely(card->eeh_state))
		वापस;

	__enable_पूर्णांकr(&card->isr_mask, पूर्णांकr);
	__enable_पूर्णांकr(&card->ier_mask, पूर्णांकr);
	ioग_लिखो32(card->ier_mask, card->regmap + IER);
पूर्ण
व्योम rsxx_disable_ier_and_isr(काष्ठा rsxx_cardinfo *card,
				  अचिन्हित पूर्णांक पूर्णांकr)
अणु
	अगर (unlikely(card->eeh_state))
		वापस;

	__disable_पूर्णांकr(&card->isr_mask, पूर्णांकr);
	__disable_पूर्णांकr(&card->ier_mask, पूर्णांकr);
	ioग_लिखो32(card->ier_mask, card->regmap + IER);
पूर्ण

अटल irqवापस_t rsxx_isr(पूर्णांक irq, व्योम *pdata)
अणु
	काष्ठा rsxx_cardinfo *card = pdata;
	अचिन्हित पूर्णांक isr;
	पूर्णांक handled = 0;
	पूर्णांक reपढ़ो_isr;
	पूर्णांक i;

	spin_lock(&card->irq_lock);

	करो अणु
		reपढ़ो_isr = 0;

		अगर (unlikely(card->eeh_state))
			अवरोध;

		isr = ioपढ़ो32(card->regmap + ISR);
		अगर (isr == 0xffffffff) अणु
			/*
			 * A few प्रणालीs seem to have an पूर्णांकermittent issue
			 * where PCI पढ़ोs वापस all Fs, but retrying the पढ़ो
			 * a little later will वापस as expected.
			 */
			dev_info(CARD_TO_DEV(card),
				"ISR = 0xFFFFFFFF, retrying later\n");
			अवरोध;
		पूर्ण

		isr &= card->isr_mask;
		अगर (!isr)
			अवरोध;

		क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
			अगर (isr & CR_INTR_DMA(i)) अणु
				अगर (card->ier_mask & CR_INTR_DMA(i)) अणु
					rsxx_disable_ier(card, CR_INTR_DMA(i));
					reपढ़ो_isr = 1;
				पूर्ण
				queue_work(card->ctrl[i].करोne_wq,
					   &card->ctrl[i].dma_करोne_work);
				handled++;
			पूर्ण
		पूर्ण

		अगर (isr & CR_INTR_CREG) अणु
			queue_work(card->creg_ctrl.creg_wq,
				   &card->creg_ctrl.करोne_work);
			handled++;
		पूर्ण

		अगर (isr & CR_INTR_EVENT) अणु
			queue_work(card->event_wq, &card->event_work);
			rsxx_disable_ier_and_isr(card, CR_INTR_EVENT);
			handled++;
		पूर्ण
	पूर्ण जबतक (reपढ़ो_isr);

	spin_unlock(&card->irq_lock);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/*----------------- Card Event Handler -------------------*/
अटल स्थिर अक्षर *rsxx_card_state_to_str(अचिन्हित पूर्णांक state)
अणु
	अटल स्थिर अक्षर * स्थिर state_strings[] = अणु
		"Unknown", "Shutdown", "Starting", "Formatting",
		"Uninitialized", "Good", "Shutting Down",
		"Fault", "Read Only Fault", "dStroying"
	पूर्ण;

	वापस state_strings[ffs(state)];
पूर्ण

अटल व्योम card_state_change(काष्ठा rsxx_cardinfo *card,
			      अचिन्हित पूर्णांक new_state)
अणु
	पूर्णांक st;

	dev_info(CARD_TO_DEV(card),
		"card state change detected.(%s -> %s)\n",
		rsxx_card_state_to_str(card->state),
		rsxx_card_state_to_str(new_state));

	card->state = new_state;

	/* Don't attach DMA पूर्णांकerfaces अगर the card has an invalid config */
	अगर (!card->config_valid)
		वापस;

	चयन (new_state) अणु
	हाल CARD_STATE_RD_ONLY_FAULT:
		dev_crit(CARD_TO_DEV(card),
			"Hardware has entered read-only mode!\n");
		/*
		 * Fall through so the DMA devices can be attached and
		 * the user can attempt to pull off their data.
		 */
		fallthrough;
	हाल CARD_STATE_GOOD:
		st = rsxx_get_card_size8(card, &card->size8);
		अगर (st)
			dev_err(CARD_TO_DEV(card),
				"Failed attaching DMA devices\n");

		अगर (card->config_valid)
			set_capacity(card->gendisk, card->size8 >> 9);
		अवरोध;

	हाल CARD_STATE_FAULT:
		dev_crit(CARD_TO_DEV(card),
			"Hardware Fault reported!\n");
		fallthrough;

	/* Everything अन्यथा, detach DMA पूर्णांकerface अगर it's attached. */
	हाल CARD_STATE_SHUTDOWN:
	हाल CARD_STATE_STARTING:
	हाल CARD_STATE_FORMATTING:
	हाल CARD_STATE_UNINITIALIZED:
	हाल CARD_STATE_SHUTTING_DOWN:
	/*
	 * dStroy is a term coined by marketing to represent the low level
	 * secure erase.
	 */
	हाल CARD_STATE_DSTROYING:
		set_capacity(card->gendisk, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम card_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rsxx_cardinfo *card;
	अचिन्हित पूर्णांक state;
	अचिन्हित दीर्घ flags;
	पूर्णांक st;

	card = container_of(work, काष्ठा rsxx_cardinfo, event_work);

	अगर (unlikely(card->halt))
		वापस;

	/*
	 * Enable the पूर्णांकerrupt now to aव्योम any weird race conditions where a
	 * state change might occur जबतक rsxx_get_card_state() is
	 * processing a वापसed creg cmd.
	 */
	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_enable_ier_and_isr(card, CR_INTR_EVENT);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	st = rsxx_get_card_state(card, &state);
	अगर (st) अणु
		dev_info(CARD_TO_DEV(card),
			"Failed reading state after event.\n");
		वापस;
	पूर्ण

	अगर (card->state != state)
		card_state_change(card, state);

	अगर (card->creg_ctrl.creg_stats.stat & CREG_STAT_LOG_PENDING)
		rsxx_पढ़ो_hw_log(card);
पूर्ण

/*----------------- Card Operations -------------------*/
अटल पूर्णांक card_shutकरोwn(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित पूर्णांक state;
	चिन्हित दीर्घ start;
	स्थिर पूर्णांक समयout = msecs_to_jअगरfies(120000);
	पूर्णांक st;

	/* We can't issue a shutकरोwn अगर the card is in a transition state */
	start = jअगरfies;
	करो अणु
		st = rsxx_get_card_state(card, &state);
		अगर (st)
			वापस st;
	पूर्ण जबतक (state == CARD_STATE_STARTING &&
		 (jअगरfies - start < समयout));

	अगर (state == CARD_STATE_STARTING)
		वापस -ETIMEDOUT;

	/* Only issue a shutकरोwn अगर we need to */
	अगर ((state != CARD_STATE_SHUTTING_DOWN) &&
	    (state != CARD_STATE_SHUTDOWN)) अणु
		st = rsxx_issue_card_cmd(card, CARD_CMD_SHUTDOWN);
		अगर (st)
			वापस st;
	पूर्ण

	start = jअगरfies;
	करो अणु
		st = rsxx_get_card_state(card, &state);
		अगर (st)
			वापस st;
	पूर्ण जबतक (state != CARD_STATE_SHUTDOWN &&
		 (jअगरfies - start < समयout));

	अगर (state != CARD_STATE_SHUTDOWN)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_eeh_frozen(काष्ठा pci_dev *dev)
अणु
	काष्ठा rsxx_cardinfo *card = pci_get_drvdata(dev);
	पूर्णांक i;
	पूर्णांक st;

	dev_warn(&dev->dev, "IBM Flash Adapter PCI: preparing for slot reset.\n");

	card->eeh_state = 1;
	rsxx_mask_पूर्णांकerrupts(card);

	/*
	 * We need to guarantee that the ग_लिखो क्रम eeh_state and masking
	 * पूर्णांकerrupts करोes not become reordered. This will prevent a possible
	 * race condition with the EEH code.
	 */
	wmb();

	pci_disable_device(dev);

	st = rsxx_eeh_save_issued_dmas(card);
	अगर (st)
		वापस st;

	rsxx_eeh_save_issued_creg(card);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		अगर (card->ctrl[i].status.buf)
			dma_मुक्त_coherent(&card->dev->dev,
					  STATUS_BUFFER_SIZE8,
					  card->ctrl[i].status.buf,
					  card->ctrl[i].status.dma_addr);
		अगर (card->ctrl[i].cmd.buf)
			dma_मुक्त_coherent(&card->dev->dev,
					  COMMAND_BUFFER_SIZE8,
					  card->ctrl[i].cmd.buf,
					  card->ctrl[i].cmd.dma_addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rsxx_eeh_failure(काष्ठा pci_dev *dev)
अणु
	काष्ठा rsxx_cardinfo *card = pci_get_drvdata(dev);
	पूर्णांक i;
	पूर्णांक cnt = 0;

	dev_err(&dev->dev, "IBM Flash Adapter PCI: disabling failed card.\n");

	card->eeh_state = 1;
	card->halt = 1;

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		spin_lock_bh(&card->ctrl[i].queue_lock);
		cnt = rsxx_cleanup_dma_queue(&card->ctrl[i],
					     &card->ctrl[i].queue,
					     COMPLETE_DMA);
		spin_unlock_bh(&card->ctrl[i].queue_lock);

		cnt += rsxx_dma_cancel(&card->ctrl[i]);

		अगर (cnt)
			dev_info(CARD_TO_DEV(card),
				"Freed %d queued DMAs on channel %d\n",
				cnt, card->ctrl[i].id);
	पूर्ण
पूर्ण

अटल पूर्णांक rsxx_eeh_fअगरo_flush_poll(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक iter = 0;

	/* We need to रुको क्रम the hardware to reset */
	जबतक (iter++ < 10) अणु
		status = ioपढ़ो32(card->regmap + PCI_RECONFIG);

		अगर (status & RSXX_FLUSH_BUSY) अणु
			ssleep(1);
			जारी;
		पूर्ण

		अगर (status & RSXX_FLUSH_TIMEOUT)
			dev_warn(CARD_TO_DEV(card), "HW: flash controller timeout\n");
		वापस 0;
	पूर्ण

	/* Hardware failed resetting itself. */
	वापस -1;
पूर्ण

अटल pci_ers_result_t rsxx_error_detected(काष्ठा pci_dev *dev,
					    pci_channel_state_t error)
अणु
	पूर्णांक st;

	अगर (dev->revision < RSXX_EEH_SUPPORT)
		वापस PCI_ERS_RESULT_NONE;

	अगर (error == pci_channel_io_perm_failure) अणु
		rsxx_eeh_failure(dev);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	st = rsxx_eeh_frozen(dev);
	अगर (st) अणु
		dev_err(&dev->dev, "Slot reset setup failed\n");
		rsxx_eeh_failure(dev);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t rsxx_slot_reset(काष्ठा pci_dev *dev)
अणु
	काष्ठा rsxx_cardinfo *card = pci_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक st;

	dev_warn(&dev->dev,
		"IBM Flash Adapter PCI: recovering from slot reset.\n");

	st = pci_enable_device(dev);
	अगर (st)
		जाओ failed_hw_setup;

	pci_set_master(dev);

	st = rsxx_eeh_fअगरo_flush_poll(card);
	अगर (st)
		जाओ failed_hw_setup;

	rsxx_dma_queue_reset(card);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		st = rsxx_hw_buffers_init(dev, &card->ctrl[i]);
		अगर (st)
			जाओ failed_hw_buffers_init;
	पूर्ण

	अगर (card->config_valid)
		rsxx_dma_configure(card);

	/* Clears the ISR रेजिस्टर from spurious पूर्णांकerrupts */
	st = ioपढ़ो32(card->regmap + ISR);

	card->eeh_state = 0;

	spin_lock_irqsave(&card->irq_lock, flags);
	अगर (card->n_tarमाला_लो & RSXX_MAX_TARGETS)
		rsxx_enable_ier_and_isr(card, CR_INTR_ALL_G);
	अन्यथा
		rsxx_enable_ier_and_isr(card, CR_INTR_ALL_C);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	rsxx_kick_creg_queue(card);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		spin_lock(&card->ctrl[i].queue_lock);
		अगर (list_empty(&card->ctrl[i].queue)) अणु
			spin_unlock(&card->ctrl[i].queue_lock);
			जारी;
		पूर्ण
		spin_unlock(&card->ctrl[i].queue_lock);

		queue_work(card->ctrl[i].issue_wq,
				&card->ctrl[i].issue_dma_work);
	पूर्ण

	dev_info(&dev->dev, "IBM Flash Adapter PCI: recovery complete.\n");

	वापस PCI_ERS_RESULT_RECOVERED;

failed_hw_buffers_init:
	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		अगर (card->ctrl[i].status.buf)
			dma_मुक्त_coherent(&card->dev->dev,
					  STATUS_BUFFER_SIZE8,
					  card->ctrl[i].status.buf,
					  card->ctrl[i].status.dma_addr);
		अगर (card->ctrl[i].cmd.buf)
			dma_मुक्त_coherent(&card->dev->dev,
					  COMMAND_BUFFER_SIZE8,
					  card->ctrl[i].cmd.buf,
					  card->ctrl[i].cmd.dma_addr);
	पूर्ण
failed_hw_setup:
	rsxx_eeh_failure(dev);
	वापस PCI_ERS_RESULT_DISCONNECT;

पूर्ण

/*----------------- Driver Initialization & Setup -------------------*/
/* Returns:   0 अगर the driver is compatible with the device
	     -1 अगर the driver is NOT compatible with the device */
अटल पूर्णांक rsxx_compatibility_check(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित अक्षर pci_rev;

	pci_पढ़ो_config_byte(card->dev, PCI_REVISION_ID, &pci_rev);

	अगर (pci_rev > RS70_PCI_REV_SUPPORTED)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_pci_probe(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा rsxx_cardinfo *card;
	पूर्णांक st;
	अचिन्हित पूर्णांक sync_समयout;

	dev_info(&dev->dev, "PCI-Flash SSD discovered\n");

	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->dev = dev;
	pci_set_drvdata(dev, card);

	st = ida_alloc(&rsxx_disk_ida, GFP_KERNEL);
	अगर (st < 0)
		जाओ failed_ida_get;
	card->disk_id = st;

	st = pci_enable_device(dev);
	अगर (st)
		जाओ failed_enable;

	pci_set_master(dev);

	st = dma_set_mask(&dev->dev, DMA_BIT_MASK(64));
	अगर (st) अणु
		dev_err(CARD_TO_DEV(card),
			"No usable DMA configuration,aborting\n");
		जाओ failed_dma_mask;
	पूर्ण

	st = pci_request_regions(dev, DRIVER_NAME);
	अगर (st) अणु
		dev_err(CARD_TO_DEV(card),
			"Failed to request memory region\n");
		जाओ failed_request_regions;
	पूर्ण

	अगर (pci_resource_len(dev, 0) == 0) अणु
		dev_err(CARD_TO_DEV(card), "BAR0 has length 0!\n");
		st = -ENOMEM;
		जाओ failed_iomap;
	पूर्ण

	card->regmap = pci_iomap(dev, 0, 0);
	अगर (!card->regmap) अणु
		dev_err(CARD_TO_DEV(card), "Failed to map BAR0\n");
		st = -ENOMEM;
		जाओ failed_iomap;
	पूर्ण

	spin_lock_init(&card->irq_lock);
	card->halt = 0;
	card->eeh_state = 0;

	spin_lock_irq(&card->irq_lock);
	rsxx_disable_ier_and_isr(card, CR_INTR_ALL);
	spin_unlock_irq(&card->irq_lock);

	अगर (!क्रमce_legacy) अणु
		st = pci_enable_msi(dev);
		अगर (st)
			dev_warn(CARD_TO_DEV(card),
				"Failed to enable MSI\n");
	पूर्ण

	st = request_irq(dev->irq, rsxx_isr, IRQF_SHARED,
			 DRIVER_NAME, card);
	अगर (st) अणु
		dev_err(CARD_TO_DEV(card),
			"Failed requesting IRQ%d\n", dev->irq);
		जाओ failed_irq;
	पूर्ण

	/************* Setup Processor Command Interface *************/
	st = rsxx_creg_setup(card);
	अगर (st) अणु
		dev_err(CARD_TO_DEV(card), "Failed to setup creg interface.\n");
		जाओ failed_creg_setup;
	पूर्ण

	spin_lock_irq(&card->irq_lock);
	rsxx_enable_ier_and_isr(card, CR_INTR_CREG);
	spin_unlock_irq(&card->irq_lock);

	st = rsxx_compatibility_check(card);
	अगर (st) अणु
		dev_warn(CARD_TO_DEV(card),
			"Incompatible driver detected. Please update the driver.\n");
		st = -EINVAL;
		जाओ failed_compatiblity_check;
	पूर्ण

	/************* Load Card Config *************/
	st = rsxx_load_config(card);
	अगर (st)
		dev_err(CARD_TO_DEV(card),
			"Failed loading card config\n");

	/************* Setup DMA Engine *************/
	st = rsxx_get_num_tarमाला_लो(card, &card->n_tarमाला_लो);
	अगर (st)
		dev_info(CARD_TO_DEV(card),
			"Failed reading the number of DMA targets\n");

	card->ctrl = kसुस्मृति(card->n_tarमाला_लो, माप(*card->ctrl),
			     GFP_KERNEL);
	अगर (!card->ctrl) अणु
		st = -ENOMEM;
		जाओ failed_dma_setup;
	पूर्ण

	st = rsxx_dma_setup(card);
	अगर (st) अणु
		dev_info(CARD_TO_DEV(card),
			"Failed to setup DMA engine\n");
		जाओ failed_dma_setup;
	पूर्ण

	/************* Setup Card Event Handler *************/
	card->event_wq = create_singlethपढ़ो_workqueue(DRIVER_NAME"_event");
	अगर (!card->event_wq) अणु
		dev_err(CARD_TO_DEV(card), "Failed card event setup.\n");
		st = -ENOMEM;
		जाओ failed_event_handler;
	पूर्ण

	INIT_WORK(&card->event_work, card_event_handler);

	st = rsxx_setup_dev(card);
	अगर (st)
		जाओ failed_create_dev;

	rsxx_get_card_state(card, &card->state);

	dev_info(CARD_TO_DEV(card),
		"card state: %s\n",
		rsxx_card_state_to_str(card->state));

	/*
	 * Now that the DMA Engine and devices have been setup,
	 * we can enable the event पूर्णांकerrupt(it kicks off actions in
	 * those layers so we couldn't enable it right away.)
	 */
	spin_lock_irq(&card->irq_lock);
	rsxx_enable_ier_and_isr(card, CR_INTR_EVENT);
	spin_unlock_irq(&card->irq_lock);

	अगर (card->state == CARD_STATE_SHUTDOWN) अणु
		st = rsxx_issue_card_cmd(card, CARD_CMD_STARTUP);
		अगर (st)
			dev_crit(CARD_TO_DEV(card),
				"Failed issuing card startup\n");
		अगर (sync_start) अणु
			sync_समयout = SYNC_START_TIMEOUT;

			dev_info(CARD_TO_DEV(card),
				 "Waiting for card to startup\n");

			करो अणु
				ssleep(1);
				sync_समयout--;

				rsxx_get_card_state(card, &card->state);
			पूर्ण जबतक (sync_समयout &&
				(card->state == CARD_STATE_STARTING));

			अगर (card->state == CARD_STATE_STARTING) अणु
				dev_warn(CARD_TO_DEV(card),
					 "Card startup timed out\n");
				card->size8 = 0;
			पूर्ण अन्यथा अणु
				dev_info(CARD_TO_DEV(card),
					"card state: %s\n",
					rsxx_card_state_to_str(card->state));
				st = rsxx_get_card_size8(card, &card->size8);
				अगर (st)
					card->size8 = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (card->state == CARD_STATE_GOOD ||
		   card->state == CARD_STATE_RD_ONLY_FAULT) अणु
		st = rsxx_get_card_size8(card, &card->size8);
		अगर (st)
			card->size8 = 0;
	पूर्ण

	rsxx_attach_dev(card);

	/************* Setup Debugfs *************/
	rsxx_debugfs_dev_new(card);

	वापस 0;

failed_create_dev:
	destroy_workqueue(card->event_wq);
	card->event_wq = शून्य;
failed_event_handler:
	rsxx_dma_destroy(card);
failed_dma_setup:
failed_compatiblity_check:
	destroy_workqueue(card->creg_ctrl.creg_wq);
	card->creg_ctrl.creg_wq = शून्य;
failed_creg_setup:
	spin_lock_irq(&card->irq_lock);
	rsxx_disable_ier_and_isr(card, CR_INTR_ALL);
	spin_unlock_irq(&card->irq_lock);
	मुक्त_irq(dev->irq, card);
	अगर (!क्रमce_legacy)
		pci_disable_msi(dev);
failed_irq:
	pci_iounmap(dev, card->regmap);
failed_iomap:
	pci_release_regions(dev);
failed_request_regions:
failed_dma_mask:
	pci_disable_device(dev);
failed_enable:
	ida_मुक्त(&rsxx_disk_ida, card->disk_id);
failed_ida_get:
	kमुक्त(card);

	वापस st;
पूर्ण

अटल व्योम rsxx_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा rsxx_cardinfo *card = pci_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक st;
	पूर्णांक i;

	अगर (!card)
		वापस;

	dev_info(CARD_TO_DEV(card),
		"Removing PCI-Flash SSD.\n");

	rsxx_detach_dev(card);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_disable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	पूर्ण

	st = card_shutकरोwn(card);
	अगर (st)
		dev_crit(CARD_TO_DEV(card), "Shutdown failed!\n");

	/* Sync outstanding event handlers. */
	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_disable_ier_and_isr(card, CR_INTR_EVENT);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	cancel_work_sync(&card->event_work);

	destroy_workqueue(card->event_wq);
	rsxx_destroy_dev(card);
	rsxx_dma_destroy(card);
	destroy_workqueue(card->creg_ctrl.creg_wq);

	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_disable_ier_and_isr(card, CR_INTR_ALL);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	/* Prevent work_काष्ठाs from re-queuing themselves. */
	card->halt = 1;

	debugfs_हटाओ_recursive(card->debugfs_dir);

	मुक्त_irq(dev->irq, card);

	अगर (!क्रमce_legacy)
		pci_disable_msi(dev);

	rsxx_creg_destroy(card);

	pci_iounmap(dev, card->regmap);

	pci_disable_device(dev);
	pci_release_regions(dev);

	ida_मुक्त(&rsxx_disk_ida, card->disk_id);
	kमुक्त(card);
पूर्ण

अटल पूर्णांक rsxx_pci_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	/* We करोn't support suspend at this समय. */
	वापस -ENOSYS;
पूर्ण

अटल व्योम rsxx_pci_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा rsxx_cardinfo *card = pci_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!card)
		वापस;

	dev_info(CARD_TO_DEV(card), "Shutting down PCI-Flash SSD.\n");

	rsxx_detach_dev(card);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_disable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	पूर्ण

	card_shutकरोwn(card);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers rsxx_err_handler = अणु
	.error_detected = rsxx_error_detected,
	.slot_reset     = rsxx_slot_reset,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id rsxx_pci_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_FS70_FLASH)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_FS80_FLASH)पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, rsxx_pci_ids);

अटल काष्ठा pci_driver rsxx_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= rsxx_pci_ids,
	.probe		= rsxx_pci_probe,
	.हटाओ		= rsxx_pci_हटाओ,
	.suspend	= rsxx_pci_suspend,
	.shutकरोwn	= rsxx_pci_shutकरोwn,
	.err_handler    = &rsxx_err_handler,
पूर्ण;

अटल पूर्णांक __init rsxx_core_init(व्योम)
अणु
	पूर्णांक st;

	st = rsxx_dev_init();
	अगर (st)
		वापस st;

	st = rsxx_dma_init();
	अगर (st)
		जाओ dma_init_failed;

	st = rsxx_creg_init();
	अगर (st)
		जाओ creg_init_failed;

	वापस pci_रेजिस्टर_driver(&rsxx_pci_driver);

creg_init_failed:
	rsxx_dma_cleanup();
dma_init_failed:
	rsxx_dev_cleanup();

	वापस st;
पूर्ण

अटल व्योम __निकास rsxx_core_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rsxx_pci_driver);
	rsxx_creg_cleanup();
	rsxx_dma_cleanup();
	rsxx_dev_cleanup();
पूर्ण

module_init(rsxx_core_init);
module_निकास(rsxx_core_cleanup);
