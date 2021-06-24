<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mISDNinfineon.c
 *		Support क्रम cards based on following Infineon ISDN chipsets
 *		- ISAC + HSCX
 *		- IPAC and IPAC-X
 *		- ISAC-SX + HSCX
 *
 * Supported cards:
 *		- Dialogic Diva 2.0
 *		- Dialogic Diva 2.0U
 *		- Dialogic Diva 2.01
 *		- Dialogic Diva 2.02
 *		- Sedlbauer Speedwin
 *		- HST Saphir3
 *		- Develo (क्रमmer ELSA) Microlink PCI (Quickstep 1000)
 *		- Develo (क्रमmer ELSA) Quickstep 3000
 *		- Berkom Scitel BRIX Quadro
 *		- Dr.Neuhaus (Sagem) Niccy
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/slab.h>
#समावेश "ipac.h"

#घोषणा INFINEON_REV	"1.0"

अटल पूर्णांक inf_cnt;
अटल u32 debug;
अटल u32 irqloops = 4;

क्रमागत inf_types अणु
	INF_NONE,
	INF_DIVA20,
	INF_DIVA20U,
	INF_DIVA201,
	INF_DIVA202,
	INF_SPEEDWIN,
	INF_SAPHIR3,
	INF_QS1000,
	INF_QS3000,
	INF_NICCY,
	INF_SCT_1,
	INF_SCT_2,
	INF_SCT_3,
	INF_SCT_4,
	INF_GAZEL_R685,
	INF_GAZEL_R753
पूर्ण;

क्रमागत addr_mode अणु
	AM_NONE = 0,
	AM_IO,
	AM_MEMIO,
	AM_IND_IO,
पूर्ण;

काष्ठा inf_cinfo अणु
	क्रमागत inf_types	typ;
	स्थिर अक्षर	*full;
	स्थिर अक्षर	*name;
	क्रमागत addr_mode	cfg_mode;
	क्रमागत addr_mode	addr_mode;
	u8		cfg_bar;
	u8		addr_bar;
	व्योम		*irqfunc;
पूर्ण;

काष्ठा _ioaddr अणु
	क्रमागत addr_mode	mode;
	जोड़ अणु
		व्योम __iomem	*p;
		काष्ठा _ioport	io;
	पूर्ण a;
पूर्ण;

काष्ठा _iohandle अणु
	क्रमागत addr_mode	mode;
	resource_माप_प्रकार	size;
	resource_माप_प्रकार	start;
	व्योम __iomem	*p;
पूर्ण;

काष्ठा inf_hw अणु
	काष्ठा list_head	list;
	काष्ठा pci_dev		*pdev;
	स्थिर काष्ठा inf_cinfo	*ci;
	अक्षर			name[MISDN_MAX_IDLEN];
	u32			irq;
	u32			irqcnt;
	काष्ठा _iohandle	cfg;
	काष्ठा _iohandle	addr;
	काष्ठा _ioaddr		isac;
	काष्ठा _ioaddr		hscx;
	spinlock_t		lock;	/* HW access lock */
	काष्ठा ipac_hw		ipac;
	काष्ठा inf_hw		*sc[3];	/* slave cards */
पूर्ण;


#घोषणा PCI_SUBVENDOR_HST_SAPHIR3       0x52
#घोषणा PCI_SUBVENDOR_SEDLBAUER_PCI     0x53
#घोषणा PCI_SUB_ID_SEDLBAUER            0x01

अटल काष्ठा pci_device_id infineon_ids[] = अणु
	अणु PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA20), INF_DIVA20 पूर्ण,
	अणु PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA20_U), INF_DIVA20U पूर्ण,
	अणु PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA201), INF_DIVA201 पूर्ण,
	अणु PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA202), INF_DIVA202 पूर्ण,
	अणु PCI_VENDOR_ID_TIGERJET, PCI_DEVICE_ID_TIGERJET_100,
	  PCI_SUBVENDOR_SEDLBAUER_PCI, PCI_SUB_ID_SEDLBAUER, 0, 0,
	  INF_SPEEDWIN पूर्ण,
	अणु PCI_VENDOR_ID_TIGERJET, PCI_DEVICE_ID_TIGERJET_100,
	  PCI_SUBVENDOR_HST_SAPHIR3, PCI_SUB_ID_SEDLBAUER, 0, 0, INF_SAPHIR3 पूर्ण,
	अणु PCI_VDEVICE(ELSA, PCI_DEVICE_ID_ELSA_MICROLINK), INF_QS1000 पूर्ण,
	अणु PCI_VDEVICE(ELSA, PCI_DEVICE_ID_ELSA_QS3000), INF_QS3000 पूर्ण,
	अणु PCI_VDEVICE(SATSAGEM, PCI_DEVICE_ID_SATSAGEM_NICCY), INF_NICCY पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
	  PCI_VENDOR_ID_BERKOM, PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO, 0, 0,
	  INF_SCT_1 पूर्ण,
	अणु PCI_VDEVICE(PLX, PCI_DEVICE_ID_PLX_R685), INF_GAZEL_R685 पूर्ण,
	अणु PCI_VDEVICE(PLX, PCI_DEVICE_ID_PLX_R753), INF_GAZEL_R753 पूर्ण,
	अणु PCI_VDEVICE(PLX, PCI_DEVICE_ID_PLX_DJINN_ITOO), INF_GAZEL_R753 पूर्ण,
	अणु PCI_VDEVICE(PLX, PCI_DEVICE_ID_PLX_OLITEC), INF_GAZEL_R753 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, infineon_ids);

/* PCI पूर्णांकerface specअगरic defines */
/* Diva 2.0/2.0U */
#घोषणा DIVA_HSCX_PORT		0x00
#घोषणा DIVA_HSCX_ALE		0x04
#घोषणा DIVA_ISAC_PORT		0x08
#घोषणा DIVA_ISAC_ALE		0x0C
#घोषणा DIVA_PCI_CTRL           0x10

/* DIVA_PCI_CTRL bits */
#घोषणा DIVA_IRQ_BIT		0x01
#घोषणा DIVA_RESET_BIT		0x08
#घोषणा DIVA_EEPROM_CLK		0x40
#घोषणा DIVA_LED_A		0x10
#घोषणा DIVA_LED_B		0x20
#घोषणा DIVA_IRQ_CLR		0x80

/* Diva 2.01/2.02 */
/* Siemens PITA */
#घोषणा PITA_ICR_REG		0x00
#घोषणा PITA_INT0_STATUS	0x02

#घोषणा PITA_MISC_REG		0x1c
#घोषणा PITA_PARA_SOFTRESET	0x01000000
#घोषणा PITA_SER_SOFTRESET	0x02000000
#घोषणा PITA_PARA_MPX_MODE	0x04000000
#घोषणा PITA_INT0_ENABLE	0x00020000

/* TIGER 100 Registers */
#घोषणा TIGER_RESET_ADDR	0x00
#घोषणा TIGER_EXTERN_RESET	0x01
#घोषणा TIGER_AUX_CTRL		0x02
#घोषणा TIGER_AUX_DATA		0x03
#घोषणा TIGER_AUX_IRQMASK	0x05
#घोषणा TIGER_AUX_STATUS	0x07

/* Tiger AUX BITs */
#घोषणा TIGER_IOMASK		0xdd	/* 1 and 5 are inमाला_दो */
#घोषणा TIGER_IRQ_BIT		0x02

#घोषणा TIGER_IPAC_ALE		0xC0
#घोषणा TIGER_IPAC_PORT		0xC8

/* ELSA (now Develo) PCI cards */
#घोषणा ELSA_IRQ_ADDR		0x4c
#घोषणा ELSA_IRQ_MASK		0x04
#घोषणा QS1000_IRQ_OFF		0x01
#घोषणा QS3000_IRQ_OFF		0x03
#घोषणा QS1000_IRQ_ON		0x41
#घोषणा QS3000_IRQ_ON		0x43

/* Dr Neuhaus/Sagem Niccy */
#घोषणा NICCY_ISAC_PORT		0x00
#घोषणा NICCY_HSCX_PORT		0x01
#घोषणा NICCY_ISAC_ALE		0x02
#घोषणा NICCY_HSCX_ALE		0x03

#घोषणा NICCY_IRQ_CTRL_REG	0x38
#घोषणा NICCY_IRQ_ENABLE	0x001f00
#घोषणा NICCY_IRQ_DISABLE	0xff0000
#घोषणा NICCY_IRQ_BIT		0x800000


/* Scitel PLX */
#घोषणा SCT_PLX_IRQ_ADDR	0x4c
#घोषणा SCT_PLX_RESET_ADDR	0x50
#घोषणा SCT_PLX_IRQ_ENABLE	0x41
#घोषणा SCT_PLX_RESET_BIT	0x04

/* Gazel */
#घोषणा	GAZEL_IPAC_DATA_PORT	0x04
/* Gazel PLX */
#घोषणा GAZEL_CNTRL		0x50
#घोषणा GAZEL_RESET		0x04
#घोषणा GAZEL_RESET_9050	0x40000000
#घोषणा GAZEL_INCSR		0x4C
#घोषणा GAZEL_ISAC_EN		0x08
#घोषणा GAZEL_INT_ISAC		0x20
#घोषणा GAZEL_HSCX_EN		0x01
#घोषणा GAZEL_INT_HSCX		0x04
#घोषणा GAZEL_PCI_EN		0x40
#घोषणा GAZEL_IPAC_EN		0x03


अटल LIST_HEAD(Cards);
अटल DEFINE_RWLOCK(card_lock); /* protect Cards */

अटल व्योम
_set_debug(काष्ठा inf_hw *card)
अणु
	card->ipac.isac.dch.debug = debug;
	card->ipac.hscx[0].bch.debug = debug;
	card->ipac.hscx[1].bch.debug = debug;
पूर्ण

अटल पूर्णांक
set_debug(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	काष्ठा inf_hw *card;

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
MODULE_VERSION(INFINEON_REV);
module_param_call(debug, set_debug, param_get_uपूर्णांक, &debug, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "infineon debug mask");
module_param(irqloops, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(irqloops, "infineon maximal irqloops (default 4)");

/* Interface functions */

IOFUNC_IO(ISAC, inf_hw, isac.a.io)
IOFUNC_IO(IPAC, inf_hw, hscx.a.io)
IOFUNC_IND(ISAC, inf_hw, isac.a.io)
IOFUNC_IND(IPAC, inf_hw, hscx.a.io)
IOFUNC_MEMIO(ISAC, inf_hw, u32, isac.a.p)
IOFUNC_MEMIO(IPAC, inf_hw, u32, hscx.a.p)

अटल irqवापस_t
भागa_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = inb((u32)hw->cfg.start + DIVA_PCI_CTRL);
	अगर (!(val & DIVA_IRQ_BIT)) अणु /* क्रम us or shared ? */
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
भागa20x_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = पढ़ोb(hw->cfg.p);
	अगर (!(val & PITA_INT0_STATUS)) अणु /* क्रम us or shared ? */
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	ग_लिखोb(PITA_INT0_STATUS, hw->cfg.p); /* ACK PITA INT0 */
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
tiger_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = inb((u32)hw->cfg.start + TIGER_AUX_STATUS);
	अगर (val & TIGER_IRQ_BIT) अणु /* क्रम us or shared ? */
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
elsa_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = inb((u32)hw->cfg.start + ELSA_IRQ_ADDR);
	अगर (!(val & ELSA_IRQ_MASK)) अणु
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
niccy_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u32 val;

	spin_lock(&hw->lock);
	val = inl((u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
	अगर (!(val & NICCY_IRQ_BIT)) अणु /* क्रम us or shared ? */
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	outl(val, (u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
gazel_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	irqवापस_t ret;

	spin_lock(&hw->lock);
	ret = mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस ret;
पूर्ण

अटल irqवापस_t
ipac_irq(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = hw->ipac.पढ़ो_reg(hw, IPAC_ISTA);
	अगर (!(val & 0x3f)) अणु
		spin_unlock(&hw->lock);
		वापस IRQ_NONE; /* shared */
	पूर्ण
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
enable_hwirq(काष्ठा inf_hw *hw)
अणु
	u16 w;
	u32 val;

	चयन (hw->ci->typ) अणु
	हाल INF_DIVA201:
	हाल INF_DIVA202:
		ग_लिखोl(PITA_INT0_ENABLE, hw->cfg.p);
		अवरोध;
	हाल INF_SPEEDWIN:
	हाल INF_SAPHIR3:
		outb(TIGER_IRQ_BIT, (u32)hw->cfg.start + TIGER_AUX_IRQMASK);
		अवरोध;
	हाल INF_QS1000:
		outb(QS1000_IRQ_ON, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		अवरोध;
	हाल INF_QS3000:
		outb(QS3000_IRQ_ON, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		अवरोध;
	हाल INF_NICCY:
		val = inl((u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		val |= NICCY_IRQ_ENABLE;
		outl(val, (u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		अवरोध;
	हाल INF_SCT_1:
		w = inw((u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		w |= SCT_PLX_IRQ_ENABLE;
		outw(w, (u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		अवरोध;
	हाल INF_GAZEL_R685:
		outb(GAZEL_ISAC_EN + GAZEL_HSCX_EN + GAZEL_PCI_EN,
		     (u32)hw->cfg.start + GAZEL_INCSR);
		अवरोध;
	हाल INF_GAZEL_R753:
		outb(GAZEL_IPAC_EN + GAZEL_PCI_EN,
		     (u32)hw->cfg.start + GAZEL_INCSR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा inf_hw *hw)
अणु
	u16 w;
	u32 val;

	चयन (hw->ci->typ) अणु
	हाल INF_DIVA201:
	हाल INF_DIVA202:
		ग_लिखोl(0, hw->cfg.p);
		अवरोध;
	हाल INF_SPEEDWIN:
	हाल INF_SAPHIR3:
		outb(0, (u32)hw->cfg.start + TIGER_AUX_IRQMASK);
		अवरोध;
	हाल INF_QS1000:
		outb(QS1000_IRQ_OFF, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		अवरोध;
	हाल INF_QS3000:
		outb(QS3000_IRQ_OFF, (u32)hw->cfg.start + ELSA_IRQ_ADDR);
		अवरोध;
	हाल INF_NICCY:
		val = inl((u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		val &= NICCY_IRQ_DISABLE;
		outl(val, (u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
		अवरोध;
	हाल INF_SCT_1:
		w = inw((u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		w &= (~SCT_PLX_IRQ_ENABLE);
		outw(w, (u32)hw->cfg.start + SCT_PLX_IRQ_ADDR);
		अवरोध;
	हाल INF_GAZEL_R685:
	हाल INF_GAZEL_R753:
		outb(0, (u32)hw->cfg.start + GAZEL_INCSR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ipac_chip_reset(काष्ठा inf_hw *hw)
अणु
	hw->ipac.ग_लिखो_reg(hw, IPAC_POTA2, 0x20);
	mdelay(5);
	hw->ipac.ग_लिखो_reg(hw, IPAC_POTA2, 0x00);
	mdelay(5);
	hw->ipac.ग_लिखो_reg(hw, IPAC_CONF, hw->ipac.conf);
	hw->ipac.ग_लिखो_reg(hw, IPAC_MASK, 0xc0);
पूर्ण

अटल व्योम
reset_inf(काष्ठा inf_hw *hw)
अणु
	u16 w;
	u32 val;

	अगर (debug & DEBUG_HW)
		pr_notice("%s: resetting card\n", hw->name);
	चयन (hw->ci->typ) अणु
	हाल INF_DIVA20:
	हाल INF_DIVA20U:
		outb(0, (u32)hw->cfg.start + DIVA_PCI_CTRL);
		mdelay(10);
		outb(DIVA_RESET_BIT, (u32)hw->cfg.start + DIVA_PCI_CTRL);
		mdelay(10);
		/* Workaround PCI9060 */
		outb(9, (u32)hw->cfg.start + 0x69);
		outb(DIVA_RESET_BIT | DIVA_LED_A,
		     (u32)hw->cfg.start + DIVA_PCI_CTRL);
		अवरोध;
	हाल INF_DIVA201:
		ग_लिखोl(PITA_PARA_SOFTRESET | PITA_PARA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(1);
		ग_लिखोl(PITA_PARA_MPX_MODE, hw->cfg.p + PITA_MISC_REG);
		mdelay(10);
		अवरोध;
	हाल INF_DIVA202:
		ग_लिखोl(PITA_PARA_SOFTRESET | PITA_PARA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(1);
		ग_लिखोl(PITA_PARA_MPX_MODE | PITA_SER_SOFTRESET,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(10);
		अवरोध;
	हाल INF_SPEEDWIN:
	हाल INF_SAPHIR3:
		ipac_chip_reset(hw);
		hw->ipac.ग_लिखो_reg(hw, IPAC_ACFG, 0xff);
		hw->ipac.ग_लिखो_reg(hw, IPAC_AOE, 0x00);
		hw->ipac.ग_लिखो_reg(hw, IPAC_PCFG, 0x12);
		अवरोध;
	हाल INF_QS1000:
	हाल INF_QS3000:
		ipac_chip_reset(hw);
		hw->ipac.ग_लिखो_reg(hw, IPAC_ACFG, 0x00);
		hw->ipac.ग_लिखो_reg(hw, IPAC_AOE, 0x3c);
		hw->ipac.ग_लिखो_reg(hw, IPAC_ATX, 0xff);
		अवरोध;
	हाल INF_NICCY:
		अवरोध;
	हाल INF_SCT_1:
		w = inw((u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		w &= (~SCT_PLX_RESET_BIT);
		outw(w, (u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		mdelay(10);
		w = inw((u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		w |= SCT_PLX_RESET_BIT;
		outw(w, (u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		mdelay(10);
		अवरोध;
	हाल INF_GAZEL_R685:
		val = inl((u32)hw->cfg.start + GAZEL_CNTRL);
		val |= (GAZEL_RESET_9050 + GAZEL_RESET);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		val &= ~(GAZEL_RESET_9050 + GAZEL_RESET);
		mdelay(4);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		mdelay(10);
		hw->ipac.isac.adf2 = 0x87;
		hw->ipac.hscx[0].slot = 0x1f;
		hw->ipac.hscx[1].slot = 0x23;
		अवरोध;
	हाल INF_GAZEL_R753:
		val = inl((u32)hw->cfg.start + GAZEL_CNTRL);
		val |= (GAZEL_RESET_9050 + GAZEL_RESET);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		val &= ~(GAZEL_RESET_9050 + GAZEL_RESET);
		mdelay(4);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		mdelay(10);
		ipac_chip_reset(hw);
		hw->ipac.ग_लिखो_reg(hw, IPAC_ACFG, 0xff);
		hw->ipac.ग_लिखो_reg(hw, IPAC_AOE, 0x00);
		hw->ipac.conf = 0x01; /* IOM off */
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	enable_hwirq(hw);
पूर्ण

अटल पूर्णांक
inf_ctrl(काष्ठा inf_hw *hw, u32 cmd, u_दीर्घ arg)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल HW_RESET_REQ:
		reset_inf(hw);
		अवरोध;
	शेष:
		pr_info("%s: %s unknown command %x %lx\n",
			hw->name, __func__, cmd, arg);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
init_irq(काष्ठा inf_hw *hw)
अणु
	पूर्णांक	ret, cnt = 3;
	u_दीर्घ	flags;

	अगर (!hw->ci->irqfunc)
		वापस -EINVAL;
	ret = request_irq(hw->irq, hw->ci->irqfunc, IRQF_SHARED, hw->name, hw);
	अगर (ret) अणु
		pr_info("%s: couldn't get interrupt %d\n", hw->name, hw->irq);
		वापस ret;
	पूर्ण
	जबतक (cnt--) अणु
		spin_lock_irqsave(&hw->lock, flags);
		reset_inf(hw);
		ret = hw->ipac.init(&hw->ipac);
		अगर (ret) अणु
			spin_unlock_irqrestore(&hw->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				hw->name, ret);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&hw->lock, flags);
		msleep_पूर्णांकerruptible(10);
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", hw->name,
				  hw->irq, hw->irqcnt);
		अगर (!hw->irqcnt) अणु
			pr_info("%s: IRQ(%d) got no requests during init %d\n",
				hw->name, hw->irq, 3 - cnt);
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	मुक्त_irq(hw->irq, hw);
	वापस -EIO;
पूर्ण

अटल व्योम
release_io(काष्ठा inf_hw *hw)
अणु
	अगर (hw->cfg.mode) अणु
		अगर (hw->cfg.mode == AM_MEMIO) अणु
			release_mem_region(hw->cfg.start, hw->cfg.size);
			अगर (hw->cfg.p)
				iounmap(hw->cfg.p);
		पूर्ण अन्यथा
			release_region(hw->cfg.start, hw->cfg.size);
		hw->cfg.mode = AM_NONE;
	पूर्ण
	अगर (hw->addr.mode) अणु
		अगर (hw->addr.mode == AM_MEMIO) अणु
			release_mem_region(hw->addr.start, hw->addr.size);
			अगर (hw->addr.p)
				iounmap(hw->addr.p);
		पूर्ण अन्यथा
			release_region(hw->addr.start, hw->addr.size);
		hw->addr.mode = AM_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक
setup_io(काष्ठा inf_hw *hw)
अणु
	पूर्णांक err = 0;

	अगर (hw->ci->cfg_mode) अणु
		hw->cfg.start = pci_resource_start(hw->pdev, hw->ci->cfg_bar);
		hw->cfg.size = pci_resource_len(hw->pdev, hw->ci->cfg_bar);
		अगर (hw->ci->cfg_mode == AM_MEMIO) अणु
			अगर (!request_mem_region(hw->cfg.start, hw->cfg.size,
						hw->name))
				err = -EBUSY;
		पूर्ण अन्यथा अणु
			अगर (!request_region(hw->cfg.start, hw->cfg.size,
					    hw->name))
				err = -EBUSY;
		पूर्ण
		अगर (err) अणु
			pr_info("mISDN: %s config port %lx (%lu bytes)"
				"already in use\n", hw->name,
				(uदीर्घ)hw->cfg.start, (uदीर्घ)hw->cfg.size);
			वापस err;
		पूर्ण
		hw->cfg.mode = hw->ci->cfg_mode;
		अगर (hw->ci->cfg_mode == AM_MEMIO) अणु
			hw->cfg.p = ioremap(hw->cfg.start, hw->cfg.size);
			अगर (!hw->cfg.p)
				वापस -ENOMEM;
		पूर्ण
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IO cfg %lx (%lu bytes) mode%d\n",
				  hw->name, (uदीर्घ)hw->cfg.start,
				  (uदीर्घ)hw->cfg.size, hw->ci->cfg_mode);

	पूर्ण
	अगर (hw->ci->addr_mode) अणु
		hw->addr.start = pci_resource_start(hw->pdev, hw->ci->addr_bar);
		hw->addr.size = pci_resource_len(hw->pdev, hw->ci->addr_bar);
		अगर (hw->ci->addr_mode == AM_MEMIO) अणु
			अगर (!request_mem_region(hw->addr.start, hw->addr.size,
						hw->name))
				err = -EBUSY;
		पूर्ण अन्यथा अणु
			अगर (!request_region(hw->addr.start, hw->addr.size,
					    hw->name))
				err = -EBUSY;
		पूर्ण
		अगर (err) अणु
			pr_info("mISDN: %s address port %lx (%lu bytes)"
				"already in use\n", hw->name,
				(uदीर्घ)hw->addr.start, (uदीर्घ)hw->addr.size);
			वापस err;
		पूर्ण
		hw->addr.mode = hw->ci->addr_mode;
		अगर (hw->ci->addr_mode == AM_MEMIO) अणु
			hw->addr.p = ioremap(hw->addr.start, hw->addr.size);
			अगर (!hw->addr.p)
				वापस -ENOMEM;
		पूर्ण
		अगर (debug & DEBUG_HW)
			pr_notice("%s: IO addr %lx (%lu bytes) mode%d\n",
				  hw->name, (uदीर्घ)hw->addr.start,
				  (uदीर्घ)hw->addr.size, hw->ci->addr_mode);

	पूर्ण

	चयन (hw->ci->typ) अणु
	हाल INF_DIVA20:
	हाल INF_DIVA20U:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->isac.mode = hw->cfg.mode;
		hw->isac.a.io.ale = (u32)hw->cfg.start + DIVA_ISAC_ALE;
		hw->isac.a.io.port = (u32)hw->cfg.start + DIVA_ISAC_PORT;
		hw->hscx.mode = hw->cfg.mode;
		hw->hscx.a.io.ale = (u32)hw->cfg.start + DIVA_HSCX_ALE;
		hw->hscx.a.io.port = (u32)hw->cfg.start + DIVA_HSCX_PORT;
		अवरोध;
	हाल INF_DIVA201:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addr.mode;
		hw->isac.a.p = hw->addr.p;
		hw->hscx.mode = hw->addr.mode;
		hw->hscx.a.p = hw->addr.p;
		अवरोध;
	हाल INF_DIVA202:
		hw->ipac.type = IPAC_TYPE_IPACX;
		hw->isac.mode = hw->addr.mode;
		hw->isac.a.p = hw->addr.p;
		hw->hscx.mode = hw->addr.mode;
		hw->hscx.a.p = hw->addr.p;
		अवरोध;
	हाल INF_SPEEDWIN:
	हाल INF_SAPHIR3:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->cfg.mode;
		hw->isac.a.io.ale = (u32)hw->cfg.start + TIGER_IPAC_ALE;
		hw->isac.a.io.port = (u32)hw->cfg.start + TIGER_IPAC_PORT;
		hw->hscx.mode = hw->cfg.mode;
		hw->hscx.a.io.ale = (u32)hw->cfg.start + TIGER_IPAC_ALE;
		hw->hscx.a.io.port = (u32)hw->cfg.start + TIGER_IPAC_PORT;
		outb(0xff, (uदीर्घ)hw->cfg.start);
		mdelay(1);
		outb(0x00, (uदीर्घ)hw->cfg.start);
		mdelay(1);
		outb(TIGER_IOMASK, (uदीर्घ)hw->cfg.start + TIGER_AUX_CTRL);
		अवरोध;
	हाल INF_QS1000:
	हाल INF_QS3000:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.ale = (u32)hw->addr.start;
		hw->isac.a.io.port = (u32)hw->addr.start + 1;
		hw->isac.mode = hw->addr.mode;
		hw->hscx.a.io.ale = (u32)hw->addr.start;
		hw->hscx.a.io.port = (u32)hw->addr.start + 1;
		hw->hscx.mode = hw->addr.mode;
		अवरोध;
	हाल INF_NICCY:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->isac.mode = hw->addr.mode;
		hw->isac.a.io.ale = (u32)hw->addr.start + NICCY_ISAC_ALE;
		hw->isac.a.io.port = (u32)hw->addr.start + NICCY_ISAC_PORT;
		hw->hscx.mode = hw->addr.mode;
		hw->hscx.a.io.ale = (u32)hw->addr.start + NICCY_HSCX_ALE;
		hw->hscx.a.io.port = (u32)hw->addr.start + NICCY_HSCX_PORT;
		अवरोध;
	हाल INF_SCT_1:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.ale = (u32)hw->addr.start;
		hw->isac.a.io.port = hw->isac.a.io.ale + 4;
		hw->isac.mode = hw->addr.mode;
		hw->hscx.a.io.ale = hw->isac.a.io.ale;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		hw->hscx.mode = hw->addr.mode;
		अवरोध;
	हाल INF_SCT_2:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.ale = (u32)hw->addr.start + 0x08;
		hw->isac.a.io.port = hw->isac.a.io.ale + 4;
		hw->isac.mode = hw->addr.mode;
		hw->hscx.a.io.ale = hw->isac.a.io.ale;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		hw->hscx.mode = hw->addr.mode;
		अवरोध;
	हाल INF_SCT_3:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.ale = (u32)hw->addr.start + 0x10;
		hw->isac.a.io.port = hw->isac.a.io.ale + 4;
		hw->isac.mode = hw->addr.mode;
		hw->hscx.a.io.ale = hw->isac.a.io.ale;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		hw->hscx.mode = hw->addr.mode;
		अवरोध;
	हाल INF_SCT_4:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.ale = (u32)hw->addr.start + 0x20;
		hw->isac.a.io.port = hw->isac.a.io.ale + 4;
		hw->isac.mode = hw->addr.mode;
		hw->hscx.a.io.ale = hw->isac.a.io.ale;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		hw->hscx.mode = hw->addr.mode;
		अवरोध;
	हाल INF_GAZEL_R685:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addr.mode;
		hw->isac.a.io.port = (u32)hw->addr.start;
		hw->hscx.mode = hw->addr.mode;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		अवरोध;
	हाल INF_GAZEL_R753:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addr.mode;
		hw->isac.a.io.ale = (u32)hw->addr.start;
		hw->isac.a.io.port = (u32)hw->addr.start + GAZEL_IPAC_DATA_PORT;
		hw->hscx.mode = hw->addr.mode;
		hw->hscx.a.io.ale = hw->isac.a.io.ale;
		hw->hscx.a.io.port = hw->isac.a.io.port;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	चयन (hw->isac.mode) अणु
	हाल AM_MEMIO:
		ASSIGN_FUNC_IPAC(MIO, hw->ipac);
		अवरोध;
	हाल AM_IND_IO:
		ASSIGN_FUNC_IPAC(IND, hw->ipac);
		अवरोध;
	हाल AM_IO:
		ASSIGN_FUNC_IPAC(IO, hw->ipac);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
release_card(काष्ठा inf_hw *card) अणु
	uदीर्घ	flags;
	पूर्णांक	i;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	card->ipac.isac.release(&card->ipac.isac);
	मुक्त_irq(card->irq, card);
	mISDN_unरेजिस्टर_device(&card->ipac.isac.dch.dev);
	release_io(card);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	चयन (card->ci->typ) अणु
	हाल INF_SCT_2:
	हाल INF_SCT_3:
	हाल INF_SCT_4:
		अवरोध;
	हाल INF_SCT_1:
		क्रम (i = 0; i < 3; i++) अणु
			अगर (card->sc[i])
				release_card(card->sc[i]);
			card->sc[i] = शून्य;
		पूर्ण
		fallthrough;
	शेष:
		pci_disable_device(card->pdev);
		pci_set_drvdata(card->pdev, शून्य);
		अवरोध;
	पूर्ण
	kमुक्त(card);
	inf_cnt--;
पूर्ण

अटल पूर्णांक
setup_instance(काष्ठा inf_hw *card)
अणु
	पूर्णांक err;
	uदीर्घ flags;

	snम_लिखो(card->name, MISDN_MAX_IDLEN - 1, "%s.%d", card->ci->name,
		 inf_cnt + 1);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);

	_set_debug(card);
	card->ipac.isac.name = card->name;
	card->ipac.name = card->name;
	card->ipac.owner = THIS_MODULE;
	spin_lock_init(&card->lock);
	card->ipac.isac.hwlock = &card->lock;
	card->ipac.hwlock = &card->lock;
	card->ipac.ctrl = (व्योम *)&inf_ctrl;

	err = setup_io(card);
	अगर (err)
		जाओ error_setup;

	card->ipac.isac.dch.dev.Bprotocols =
		mISDNipac_init(&card->ipac, card);

	अगर (card->ipac.isac.dch.dev.Bprotocols == 0)
		जाओ error_setup;

	err = mISDN_रेजिस्टर_device(&card->ipac.isac.dch.dev,
				    &card->pdev->dev, card->name);
	अगर (err)
		जाओ error;

	err = init_irq(card);
	अगर (!err)  अणु
		inf_cnt++;
		pr_notice("Infineon %d cards installed\n", inf_cnt);
		वापस 0;
	पूर्ण
	mISDN_unरेजिस्टर_device(&card->ipac.isac.dch.dev);
error:
	card->ipac.release(&card->ipac);
error_setup:
	release_io(card);
	ग_लिखो_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	ग_लिखो_unlock_irqrestore(&card_lock, flags);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा inf_cinfo inf_card_info[] = अणु
	अणु
		INF_DIVA20,
		"Dialogic Diva 2.0",
		"diva20",
		AM_IND_IO, AM_NONE, 2, 0,
		&भागa_irq
	पूर्ण,
	अणु
		INF_DIVA20U,
		"Dialogic Diva 2.0U",
		"diva20U",
		AM_IND_IO, AM_NONE, 2, 0,
		&भागa_irq
	पूर्ण,
	अणु
		INF_DIVA201,
		"Dialogic Diva 2.01",
		"diva201",
		AM_MEMIO, AM_MEMIO, 0, 1,
		&भागa20x_irq
	पूर्ण,
	अणु
		INF_DIVA202,
		"Dialogic Diva 2.02",
		"diva202",
		AM_MEMIO, AM_MEMIO, 0, 1,
		&भागa20x_irq
	पूर्ण,
	अणु
		INF_SPEEDWIN,
		"Sedlbauer SpeedWin PCI",
		"speedwin",
		AM_IND_IO, AM_NONE, 0, 0,
		&tiger_irq
	पूर्ण,
	अणु
		INF_SAPHIR3,
		"HST Saphir 3",
		"saphir",
		AM_IND_IO, AM_NONE, 0, 0,
		&tiger_irq
	पूर्ण,
	अणु
		INF_QS1000,
		"Develo Microlink PCI",
		"qs1000",
		AM_IO, AM_IND_IO, 1, 3,
		&elsa_irq
	पूर्ण,
	अणु
		INF_QS3000,
		"Develo QuickStep 3000",
		"qs3000",
		AM_IO, AM_IND_IO, 1, 3,
		&elsa_irq
	पूर्ण,
	अणु
		INF_NICCY,
		"Sagem NICCY",
		"niccy",
		AM_IO, AM_IND_IO, 0, 1,
		&niccy_irq
	पूर्ण,
	अणु
		INF_SCT_1,
		"SciTel Quadro",
		"p1_scitel",
		AM_IO, AM_IND_IO, 1, 5,
		&ipac_irq
	पूर्ण,
	अणु
		INF_SCT_2,
		"SciTel Quadro",
		"p2_scitel",
		AM_NONE, AM_IND_IO, 0, 4,
		&ipac_irq
	पूर्ण,
	अणु
		INF_SCT_3,
		"SciTel Quadro",
		"p3_scitel",
		AM_NONE, AM_IND_IO, 0, 3,
		&ipac_irq
	पूर्ण,
	अणु
		INF_SCT_4,
		"SciTel Quadro",
		"p4_scitel",
		AM_NONE, AM_IND_IO, 0, 2,
		&ipac_irq
	पूर्ण,
	अणु
		INF_GAZEL_R685,
		"Gazel R685",
		"gazel685",
		AM_IO, AM_IO, 1, 2,
		&gazel_irq
	पूर्ण,
	अणु
		INF_GAZEL_R753,
		"Gazel R753",
		"gazel753",
		AM_IO, AM_IND_IO, 1, 2,
		&ipac_irq
	पूर्ण,
	अणु
		INF_NONE,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा inf_cinfo *
get_card_info(क्रमागत inf_types typ)
अणु
	स्थिर काष्ठा inf_cinfo *ci = inf_card_info;

	जबतक (ci->typ != INF_NONE) अणु
		अगर (ci->typ == typ)
			वापस ci;
		ci++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
inf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा inf_hw *card;

	card = kzalloc(माप(काष्ठा inf_hw), GFP_KERNEL);
	अगर (!card) अणु
		pr_info("No memory for Infineon ISDN card\n");
		वापस err;
	पूर्ण
	card->pdev = pdev;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण
	card->ci = get_card_info(ent->driver_data);
	अगर (!card->ci) अणु
		pr_info("mISDN: do not have information about adapter at %s\n",
			pci_name(pdev));
		kमुक्त(card);
		pci_disable_device(pdev);
		वापस -EINVAL;
	पूर्ण अन्यथा
		pr_notice("mISDN: found adapter %s at %s\n",
			  card->ci->full, pci_name(pdev));

	card->irq = pdev->irq;
	pci_set_drvdata(pdev, card);
	err = setup_instance(card);
	अगर (err) अणु
		pci_disable_device(pdev);
		kमुक्त(card);
		pci_set_drvdata(pdev, शून्य);
	पूर्ण अन्यथा अगर (ent->driver_data == INF_SCT_1) अणु
		पूर्णांक i;
		काष्ठा inf_hw *sc;

		क्रम (i = 1; i < 4; i++) अणु
			sc = kzalloc(माप(काष्ठा inf_hw), GFP_KERNEL);
			अगर (!sc) अणु
				release_card(card);
				pci_disable_device(pdev);
				वापस -ENOMEM;
			पूर्ण
			sc->irq = card->irq;
			sc->pdev = card->pdev;
			sc->ci = card->ci + i;
			err = setup_instance(sc);
			अगर (err) अणु
				pci_disable_device(pdev);
				kमुक्त(sc);
				release_card(card);
				अवरोध;
			पूर्ण अन्यथा
				card->sc[i - 1] = sc;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
inf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा inf_hw	*card = pci_get_drvdata(pdev);

	अगर (card)
		release_card(card);
	अन्यथा
		pr_debug("%s: drvdata already removed\n", __func__);
पूर्ण

अटल काष्ठा pci_driver infineon_driver = अणु
	.name = "ISDN Infineon pci",
	.probe = inf_probe,
	.हटाओ = inf_हटाओ,
	.id_table = infineon_ids,
पूर्ण;

अटल पूर्णांक __init
infineon_init(व्योम)
अणु
	पूर्णांक err;

	pr_notice("Infineon ISDN Driver Rev. %s\n", INFINEON_REV);
	err = pci_रेजिस्टर_driver(&infineon_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास
infineon_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&infineon_driver);
पूर्ण

module_init(infineon_init);
module_निकास(infineon_cleanup);
