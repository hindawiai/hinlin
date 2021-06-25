<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * speedfax.c	low level stuff क्रम Sedlbauer Speedfax+ cards
 *		based on the ISAR DSP
 *		Thanks to Sedlbauer AG क्रम inक्रमmations and HW
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/firmware.h>
#समावेश "ipac.h"
#समावेश "isar.h"

#घोषणा SPEEDFAX_REV	"2.0"

#घोषणा PCI_SUBVENDOR_SPEEDFAX_PYRAMID	0x51
#घोषणा PCI_SUBVENDOR_SPEEDFAX_PCI	0x54
#घोषणा PCI_SUB_ID_SEDLBAUER		0x01

#घोषणा SFAX_PCI_ADDR		0xc8
#घोषणा SFAX_PCI_ISAC		0xd0
#घोषणा SFAX_PCI_ISAR		0xe0

/* TIGER 100 Registers */

#घोषणा TIGER_RESET_ADDR	0x00
#घोषणा TIGER_EXTERN_RESET_ON	0x01
#घोषणा TIGER_EXTERN_RESET_OFF	0x00
#घोषणा TIGER_AUX_CTRL		0x02
#घोषणा TIGER_AUX_DATA		0x03
#घोषणा TIGER_AUX_IRQMASK	0x05
#घोषणा TIGER_AUX_STATUS	0x07

/* Tiger AUX BITs */
#घोषणा SFAX_AUX_IOMASK		0xdd	/* 1 and 5 are inमाला_दो */
#घोषणा SFAX_ISAR_RESET_BIT_OFF 0x00
#घोषणा SFAX_ISAR_RESET_BIT_ON	0x01
#घोषणा SFAX_TIGER_IRQ_BIT	0x02
#घोषणा SFAX_LED1_BIT		0x08
#घोषणा SFAX_LED2_BIT		0x10

#घोषणा SFAX_PCI_RESET_ON	(SFAX_ISAR_RESET_BIT_ON)
#घोषणा SFAX_PCI_RESET_OFF	(SFAX_LED1_BIT | SFAX_LED2_BIT)

अटल पूर्णांक sfax_cnt;
अटल u32 debug;
अटल u32 irqloops = 4;

काष्ठा sfax_hw अणु
	काष्ठा list_head	list;
	काष्ठा pci_dev		*pdev;
	अक्षर			name[MISDN_MAX_IDLEN];
	u32			irq;
	u32			irqcnt;
	u32			cfg;
	काष्ठा _ioport		p_isac;
	काष्ठा _ioport		p_isar;
	u8			aux_data;
	spinlock_t		lock;	/* HW access lock */
	काष्ठा isac_hw		isac;
	काष्ठा isar_hw		isar;
पूर्ण;

अटल LIST_HEAD(Cards);
अटल DEFINE_RWLOCK(card_lock); /* protect Cards */

अटल व्योम
_set_debug(काष्ठा sfax_hw *card)
अणु
	card->isac.dch.debug = debug;
	card->isar.ch[0].bch.debug = debug;
	card->isar.ch[1].bch.debug = debug;
पूर्ण

अटल पूर्णांक
set_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	काष्ठा sfax_hw *card;

	ret = param_set_uपूर्णांक(val, kp);
	अगर (!ret) अणु
		पढ़ो_lock(&card_lock);
		list_क्रम_each_entry(card, &Cards, list)
			_set_debug(card);
		पढ़ो_unlock(&card_lock);
	पूर्ण
	वापस ret;
पूर्ण

MODULE_AUTHOR("Karsten Keil");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(SPEEDFAX_REV);
MODULE_FIRMWARE("isdn/ISAR.BIN");
module_param_call(debug, set_debug, param_get_uपूर्णांक, &debug, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Speedfax debug mask");
module_param(irqloops, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(irqloops, "Speedfax maximal irqloops (default 4)");

IOFUNC_IND(ISAC, sfax_hw, p_isac)
IOFUNC_IND(ISAR, sfax_hw, p_isar)

अटल irqवापस_t
speedfax_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा sfax_hw	*sf = dev_id;
	u8 val;
	पूर्णांक cnt = irqloops;

	spin_lock(&sf->lock);
	val = inb(sf->cfg + TIGER_AUX_STATUS);
	अगर (val & SFAX_TIGER_IRQ_BIT) अणु /* क्रम us or shared ? */
		spin_unlock(&sf->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	sf->irqcnt++;
	val = ReadISAR_IND(sf, ISAR_IRQBIT);
Start_ISAR:
	अगर (val & ISAR_IRQSTA)
		mISDNisar_irq(&sf->isar);
	val = ReadISAC_IND(sf, ISAC_ISTA);
	अगर (val)
		mISDNisac_irq(&sf->isac, val);
	val = ReadISAR_IND(sf, ISAR_IRQBIT);
	अगर ((val & ISAR_IRQSTA) && cnt--)
		जाओ Start_ISAR;
	अगर (cnt < irqloops)
		pr_debug("%s: %d irqloops cpu%d\n", sf->name,
			 irqloops - cnt, smp_processor_id());
	अगर (irqloops && !cnt)
		pr_notice("%s: %d IRQ LOOP cpu%d\n", sf->name,
			  irqloops, smp_processor_id());
	spin_unlock(&sf->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
enable_hwirq(काष्ठा sfax_hw *sf)
अणु
	WriteISAC_IND(sf, ISAC_MASK, 0);
	WriteISAR_IND(sf, ISAR_IRQBIT, ISAR_IRQMSK);
	outb(SFAX_TIGER_IRQ_BIT, sf->cfg + TIGER_AUX_IRQMASK);
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा sfax_hw *sf)
अणु
	WriteISAC_IND(sf, ISAC_MASK, 0xFF);
	WriteISAR_IND(sf, ISAR_IRQBIT, 0);
	outb(0, sf->cfg + TIGER_AUX_IRQMASK);
पूर्ण

अटल व्योम
reset_speedfax(काष्ठा sfax_hw *sf)
अणु

	pr_debug("%s: resetting card\n", sf->name);
	outb(TIGER_EXTERN_RESET_ON, sf->cfg + TIGER_RESET_ADDR);
	outb(SFAX_PCI_RESET_ON, sf->cfg + TIGER_AUX_DATA);
	mdelay(1);
	outb(TIGER_EXTERN_RESET_OFF, sf->cfg + TIGER_RESET_ADDR);
	sf->aux_data = SFAX_PCI_RESET_OFF;
	outb(sf->aux_data, sf->cfg + TIGER_AUX_DATA);
	mdelay(1);
पूर्ण

अटल पूर्णांक
sfax_ctrl(काष्ठा sfax_hw  *sf, u32 cmd, u_दीर्घ arg)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल HW_RESET_REQ:
		reset_speedfax(sf);
		अवरोध;
	हाल HW_ACTIVATE_IND:
		अगर (arg & 1)
			sf->aux_data &= ~SFAX_LED1_BIT;
		अगर (arg & 2)
			sf->aux_data &= ~SFAX_LED2_BIT;
		outb(sf->aux_data, sf->cfg + TIGER_AUX_DATA);
		अवरोध;
	हाल HW_DEACT_IND:
		अगर (arg & 1)
			sf->aux_data |= SFAX_LED1_BIT;
		अगर (arg & 2)
			sf->aux_data |= SFAX_LED2_BIT;
		outb(sf->aux_data, sf->cfg + TIGER_AUX_DATA);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown command %x %lx\n",
			sf->name, __func__, cmd, arg);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा sfax_hw  *sf, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक	ret = 0;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP | MISDN_CTRL_L1_TIMER3;
		अवरोध;
	हाल MISDN_CTRL_LOOP:
		/* cq->channel: 0 disable, 1 B1 loop 2 B2 loop, 3 both */
		अगर (cq->channel < 0 || cq->channel > 3) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = sf->isac.ctrl(&sf->isac, HW_TESTLOOP, cq->channel);
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = sf->isac.ctrl(&sf->isac, HW_TIMER3_VALUE, cq->p1);
		अवरोध;
	शेष:
		pr_info("%s: unknown Op %x\n", sf->name, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
sfax_dctrl(काष्ठा mISDNchannel *ch, u32 cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा sfax_hw		*sf = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	pr_debug("%s: cmd:%x %p\n", sf->name, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर (rq->protocol == ISDN_P_TE_S0)
			err = sf->isac.खोलो(&sf->isac, rq);
		अन्यथा
			err = sf->isar.खोलो(&sf->isar, rq);
		अगर (err)
			अवरोध;
		अगर (!try_module_get(THIS_MODULE))
			pr_info("%s: cannot get module\n", sf->name);
		अवरोध;
	हाल CLOSE_CHANNEL:
		pr_debug("%s: dev(%d) close from %p\n", sf->name,
			 dch->dev.id, __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(sf, arg);
		अवरोध;
	शेष:
		pr_debug("%s: unknown command %x\n", sf->name, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
init_card(काष्ठा sfax_hw *sf)
अणु
	पूर्णांक	ret, cnt = 3;
	u_दीर्घ	flags;

	ret = request_irq(sf->irq, speedfax_irq, IRQF_SHARED, sf->name, sf);
	अगर (ret) अणु
		pr_info("%s: couldn't get interrupt %d\n", sf->name, sf->irq);
		वापस ret;
	पूर्ण
	जबतक (cnt--) अणु
		spin_lock_irqsave(&sf->lock, flags);
		ret = sf->isac.init(&sf->isac);
		अगर (ret) अणु
			spin_unlock_irqrestore(&sf->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				sf->name, ret);
			अवरोध;
		पूर्ण
		enable_hwirq(sf);
		/* RESET Receiver and Transmitter */
		WriteISAC_IND(sf, ISAC_CMDR, 0x41);
		spin_unlock_irqrestore(&sf->lock, flags);
		msleep_पूर्णांकerruptible(10);
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", sf->name,
				  sf->irq, sf->irqcnt);
		अगर (!sf->irqcnt) अणु
			pr_info("%s: IRQ(%d) got no requests during init %d\n",
				sf->name, sf->irq, 3 - cnt);
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	मुक्त_irq(sf->irq, sf);
	वापस -EIO;
पूर्ण


अटल पूर्णांक
setup_speedfax(काष्ठा sfax_hw *sf)
अणु
	u_दीर्घ flags;

	अगर (!request_region(sf->cfg, 256, sf->name)) अणु
		pr_info("mISDN: %s config port %x-%x already in use\n",
			sf->name, sf->cfg, sf->cfg + 255);
		वापस -EIO;
	पूर्ण
	outb(0xff, sf->cfg);
	outb(0, sf->cfg);
	outb(0xdd, sf->cfg + TIGER_AUX_CTRL);
	outb(0, sf->cfg + TIGER_AUX_IRQMASK);

	sf->isac.type = IPAC_TYPE_ISAC;
	sf->p_isac.ale = sf->cfg + SFAX_PCI_ADDR;
	sf->p_isac.port = sf->cfg + SFAX_PCI_ISAC;
	sf->p_isar.ale = sf->cfg + SFAX_PCI_ADDR;
	sf->p_isar.port = sf->cfg + SFAX_PCI_ISAR;
	ASSIGN_FUNC(IND, ISAC, sf->isac);
	ASSIGN_FUNC(IND, ISAR, sf->isar);
	spin_lock_irqsave(&sf->lock, flags);
	reset_speedfax(sf);
	disable_hwirq(sf);
	spin_unlock_irqrestore(&sf->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम
release_card(काष्ठा sfax_hw *card) अणु
	u_दीर्घ	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	card->isac.release(&card->isac);
	मुक्त_irq(card->irq, card);
	card->isar.release(&card->isar);
	mISDN_unरेजिस्टर_device(&card->isac.dch.dev);
	release_region(card->cfg, 256);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, शून्य);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	kमुक्त(card);
	sfax_cnt--;
पूर्ण

अटल पूर्णांक
setup_instance(काष्ठा sfax_hw *card)
अणु
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक i, err;
	u_दीर्घ flags;

	snम_लिखो(card->name, MISDN_MAX_IDLEN - 1, "Speedfax.%d", sfax_cnt + 1);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	_set_debug(card);
	spin_lock_init(&card->lock);
	card->isac.hwlock = &card->lock;
	card->isar.hwlock = &card->lock;
	card->isar.ctrl = (व्योम *)&sfax_ctrl;
	card->isac.name = card->name;
	card->isar.name = card->name;
	card->isar.owner = THIS_MODULE;

	err = request_firmware(&firmware, "isdn/ISAR.BIN", &card->pdev->dev);
	अगर (err < 0) अणु
		pr_info("%s: firmware request failed %d\n",
			card->name, err);
		जाओ error_fw;
	पूर्ण
	अगर (debug & DEBUG_HW)
		pr_notice("%s: got firmware %zu bytes\n",
			  card->name, firmware->size);

	mISDNisac_init(&card->isac, card);

	card->isac.dch.dev.D.ctrl = sfax_dctrl;
	card->isac.dch.dev.Bprotocols =
		mISDNisar_init(&card->isar, card);
	क्रम (i = 0; i < 2; i++) अणु
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		list_add(&card->isar.ch[i].bch.ch.list,
			 &card->isac.dch.dev.bchannels);
	पूर्ण

	err = setup_speedfax(card);
	अगर (err)
		जाओ error_setup;
	err = card->isar.init(&card->isar);
	अगर (err)
		जाओ error;
	err = mISDN_रेजिस्टर_device(&card->isac.dch.dev,
				    &card->pdev->dev, card->name);
	अगर (err)
		जाओ error;
	err = init_card(card);
	अगर (err)
		जाओ error_init;
	err = card->isar.firmware(&card->isar, firmware->data, firmware->size);
	अगर (!err)  अणु
		release_firmware(firmware);
		sfax_cnt++;
		pr_notice("SpeedFax %d cards installed\n", sfax_cnt);
		वापस 0;
	पूर्ण
	disable_hwirq(card);
	मुक्त_irq(card->irq, card);
error_init:
	mISDN_unरेजिस्टर_device(&card->isac.dch.dev);
error:
	release_region(card->cfg, 256);
error_setup:
	card->isac.release(&card->isac);
	card->isar.release(&card->isar);
	release_firmware(firmware);
error_fw:
	pci_disable_device(card->pdev);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	kमुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक
sfaxpci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा sfax_hw *card = kzalloc(माप(काष्ठा sfax_hw), GFP_KERNEL);

	अगर (!card) अणु
		pr_info("No memory for Speedfax+ PCI\n");
		वापस err;
	पूर्ण
	card->pdev = pdev;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण

	pr_notice("mISDN: Speedfax found adapter %s at %s\n",
		  (अक्षर *)ent->driver_data, pci_name(pdev));

	card->cfg = pci_resource_start(pdev, 0);
	card->irq = pdev->irq;
	pci_set_drvdata(pdev, card);
	err = setup_instance(card);
	अगर (err)
		pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम
sfax_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sfax_hw	*card = pci_get_drvdata(pdev);

	अगर (card)
		release_card(card);
	अन्यथा
		pr_debug("%s: drvdata already removed\n", __func__);
पूर्ण

अटल काष्ठा pci_device_id sfaxpci_ids[] = अणु
	अणु PCI_VENDOR_ID_TIGERJET, PCI_DEVICE_ID_TIGERJET_100,
	  PCI_SUBVENDOR_SPEEDFAX_PYRAMID, PCI_SUB_ID_SEDLBAUER,
	  0, 0, (अचिन्हित दीर्घ) "Pyramid Speedfax + PCI"
	पूर्ण,
	अणु PCI_VENDOR_ID_TIGERJET, PCI_DEVICE_ID_TIGERJET_100,
	  PCI_SUBVENDOR_SPEEDFAX_PCI, PCI_SUB_ID_SEDLBAUER,
	  0, 0, (अचिन्हित दीर्घ) "Sedlbauer Speedfax + PCI"
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sfaxpci_ids);

अटल काष्ठा pci_driver sfaxpci_driver = अणु
	.name = "speedfax+ pci",
	.probe = sfaxpci_probe,
	.हटाओ = sfax_हटाओ_pci,
	.id_table = sfaxpci_ids,
पूर्ण;

अटल पूर्णांक __init
Speedfax_init(व्योम)
अणु
	पूर्णांक err;

	pr_notice("Sedlbauer Speedfax+ Driver Rev. %s\n",
		  SPEEDFAX_REV);
	err = pci_रेजिस्टर_driver(&sfaxpci_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास
Speedfax_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sfaxpci_driver);
पूर्ण

module_init(Speedfax_init);
module_निकास(Speedfax_cleanup);
