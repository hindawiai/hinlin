<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा PRISM2_PLX

/* Host AP driver's support क्रम PC Cards on PCI adapters using PLX9052 is
 * based on:
 * - Host AP driver patch from james@madingley.org
 * - linux-wlan-ng driver, Copyright (C) AbsoluteValue Systems, Inc.
 */


#समावेश <linux/module.h>
#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>

#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

#समावेश "hostap_wlan.h"


अटल अक्षर *dev_info = "hostap_plx";


MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Support for Intersil Prism2-based 802.11 wireless LAN "
		   "cards (PLX).");
MODULE_LICENSE("GPL");


अटल पूर्णांक ignore_cis;
module_param(ignore_cis, पूर्णांक, 0444);
MODULE_PARM_DESC(ignore_cis, "Do not verify manfid information in CIS");


/* काष्ठा local_info::hw_priv */
काष्ठा hostap_plx_priv अणु
	व्योम __iomem *attr_mem;
	अचिन्हित पूर्णांक cor_offset;
पूर्ण;


#घोषणा PLX_MIN_ATTR_LEN 512	/* at least 2 x 256 is needed क्रम CIS */
#घोषणा COR_SRESET       0x80
#घोषणा COR_LEVLREQ      0x40
#घोषणा COR_ENABLE_FUNC  0x01
/* PCI Configuration Registers */
#घोषणा PLX_PCIIPR       0x3d   /* PCI Interrupt Pin */
/* Local Configuration Registers */
#घोषणा PLX_INTCSR       0x4c   /* Interrupt Control/Status Register */
#घोषणा PLX_INTCSR_PCI_INTEN BIT(6) /* PCI Interrupt Enable */
#घोषणा PLX_CNTRL        0x50
#घोषणा PLX_CNTRL_SERIAL_EEPROM_PRESENT BIT(28)


#घोषणा PLXDEV(venकरोr,dev,str) अणु venकरोr, dev, PCI_ANY_ID, PCI_ANY_ID पूर्ण

अटल स्थिर काष्ठा pci_device_id prism2_plx_id_table[] = अणु
	PLXDEV(0x10b7, 0x7770, "3Com AirConnect PCI 777A"),
	PLXDEV(0x111a, 0x1023, "Siemens SpeedStream SS1023"),
	PLXDEV(0x126c, 0x8030, "Nortel emobility"),
	PLXDEV(0x1562, 0x0001, "Symbol LA-4123"),
	PLXDEV(0x1385, 0x4100, "Netgear MA301"),
	PLXDEV(0x15e8, 0x0130, "National Datacomm NCP130 (PLX9052)"),
	PLXDEV(0x15e8, 0x0131, "National Datacomm NCP130 (TMD7160)"),
	PLXDEV(0x1638, 0x1100, "Eumitcom WL11000"),
	PLXDEV(0x16ab, 0x1100, "Global Sun Tech GL24110P"),
	PLXDEV(0x16ab, 0x1101, "Global Sun Tech GL24110P (?)"),
	PLXDEV(0x16ab, 0x1102, "Linksys WPC11 with WDT11"),
	PLXDEV(0x16ab, 0x1103, "Longshine 8031"),
	PLXDEV(0x16ec, 0x3685, "US Robotics USR2415"),
	PLXDEV(0xec80, 0xec00, "Belkin F5D6000"),
	अणु 0 पूर्ण
पूर्ण;


/* Array of known Prism2/2.5 PC Card manufactured ids. If your card's manfid
 * is not listed here, you will need to add it here to get the driver
 * initialized. */
अटल काष्ठा prism2_plx_manfid अणु
	u16 manfid1, manfid2;
पूर्ण prism2_plx_known_manfids[] = अणु
	अणु 0x000b, 0x7110 पूर्ण /* D-Link DWL-650 Rev. P1 */,
	अणु 0x000b, 0x7300 पूर्ण /* Philips 802.11b WLAN PCMCIA */,
	अणु 0x0101, 0x0777 पूर्ण /* 3Com AirConnect PCI 777A */,
	अणु 0x0126, 0x8000 पूर्ण /* Proxim RangeLAN */,
	अणु 0x0138, 0x0002 पूर्ण /* Compaq WL100 */,
	अणु 0x0156, 0x0002 पूर्ण /* Intersil Prism II Ref. Design (and others) */,
	अणु 0x026f, 0x030b पूर्ण /* Buffalo WLI-CF-S11G */,
	अणु 0x0274, 0x1612 पूर्ण /* Linksys WPC11 Ver 2.5 */,
	अणु 0x0274, 0x1613 पूर्ण /* Linksys WPC11 Ver 3 */,
	अणु 0x028a, 0x0002 पूर्ण /* D-Link DRC-650 */,
	अणु 0x0250, 0x0002 पूर्ण /* Samsung SWL2000-N */,
	अणु 0xc250, 0x0002 पूर्ण /* EMTAC A2424i */,
	अणु 0xd601, 0x0002 पूर्ण /* Z-Com XI300 */,
	अणु 0xd601, 0x0005 पूर्ण /* Zcomax XI-325H 200mW */,
	अणु 0, 0पूर्ण
पूर्ण;


#अगर_घोषित PRISM2_IO_DEBUG

अटल अंतरभूत व्योम hfa384x_outb_debug(काष्ठा net_device *dev, पूर्णांक a, u8 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_OUTB, a, v);
	outb(v, dev->base_addr + a);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

अटल अंतरभूत u8 hfa384x_inb_debug(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;
	u8 v;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	v = inb(dev->base_addr + a);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INB, a, v);
	spin_unlock_irqrestore(&local->lock, flags);
	वापस v;
पूर्ण

अटल अंतरभूत व्योम hfa384x_outw_debug(काष्ठा net_device *dev, पूर्णांक a, u16 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_OUTW, a, v);
	outw(v, dev->base_addr + a);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

अटल अंतरभूत u16 hfa384x_inw_debug(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;
	u16 v;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	v = inw(dev->base_addr + a);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INW, a, v);
	spin_unlock_irqrestore(&local->lock, flags);
	वापस v;
पूर्ण

अटल अंतरभूत व्योम hfa384x_outsw_debug(काष्ठा net_device *dev, पूर्णांक a,
				       u8 *buf, पूर्णांक wc)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_OUTSW, a, wc);
	outsw(dev->base_addr + a, buf, wc);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

अटल अंतरभूत व्योम hfa384x_insw_debug(काष्ठा net_device *dev, पूर्णांक a,
				      u8 *buf, पूर्णांक wc)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INSW, a, wc);
	insw(dev->base_addr + a, buf, wc);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

#घोषणा HFA384X_OUTB(v,a) hfa384x_outb_debug(dev, (a), (v))
#घोषणा HFA384X_INB(a) hfa384x_inb_debug(dev, (a))
#घोषणा HFA384X_OUTW(v,a) hfa384x_outw_debug(dev, (a), (v))
#घोषणा HFA384X_INW(a) hfa384x_inw_debug(dev, (a))
#घोषणा HFA384X_OUTSW(a, buf, wc) hfa384x_outsw_debug(dev, (a), (buf), (wc))
#घोषणा HFA384X_INSW(a, buf, wc) hfa384x_insw_debug(dev, (a), (buf), (wc))

#अन्यथा /* PRISM2_IO_DEBUG */

#घोषणा HFA384X_OUTB(v,a) outb((v), dev->base_addr + (a))
#घोषणा HFA384X_INB(a) inb(dev->base_addr + (a))
#घोषणा HFA384X_OUTW(v,a) outw((v), dev->base_addr + (a))
#घोषणा HFA384X_INW(a) inw(dev->base_addr + (a))
#घोषणा HFA384X_INSW(a, buf, wc) insw(dev->base_addr + (a), buf, wc)
#घोषणा HFA384X_OUTSW(a, buf, wc) outsw(dev->base_addr + (a), buf, wc)

#पूर्ण_अगर /* PRISM2_IO_DEBUG */


अटल पूर्णांक hfa384x_from_bap(काष्ठा net_device *dev, u16 bap, व्योम *buf,
			    पूर्णांक len)
अणु
	u16 d_off;
	u16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (u16 *) buf;

	अगर (len / 2)
		HFA384X_INSW(d_off, buf, len / 2);
	pos += len / 2;

	अगर (len & 1)
		*((अक्षर *) pos) = HFA384X_INB(d_off);

	वापस 0;
पूर्ण


अटल पूर्णांक hfa384x_to_bap(काष्ठा net_device *dev, u16 bap, व्योम *buf, पूर्णांक len)
अणु
	u16 d_off;
	u16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (u16 *) buf;

	अगर (len / 2)
		HFA384X_OUTSW(d_off, buf, len / 2);
	pos += len / 2;

	अगर (len & 1)
		HFA384X_OUTB(*((अक्षर *) pos), d_off);

	वापस 0;
पूर्ण


/* FIX: This might change at some poपूर्णांक.. */
#समावेश "hostap_hw.c"


अटल व्योम prism2_plx_cor_sreset(local_info_t *local)
अणु
	अचिन्हित अक्षर corsave;
	काष्ठा hostap_plx_priv *hw_priv = local->hw_priv;

	prपूर्णांकk(KERN_DEBUG "%s: Doing reset via direct COR access.\n",
	       dev_info);

	/* Set sreset bit of COR and clear it after hold समय */

	अगर (hw_priv->attr_mem == शून्य) अणु
		/* TMD7160 - COR at card's first I/O addr */
		corsave = inb(hw_priv->cor_offset);
		outb(corsave | COR_SRESET, hw_priv->cor_offset);
		mdelay(2);
		outb(corsave & ~COR_SRESET, hw_priv->cor_offset);
		mdelay(2);
	पूर्ण अन्यथा अणु
		/* PLX9052 */
		corsave = पढ़ोb(hw_priv->attr_mem + hw_priv->cor_offset);
		ग_लिखोb(corsave | COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(2);
		ग_लिखोb(corsave & ~COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(2);
	पूर्ण
पूर्ण


अटल व्योम prism2_plx_genesis_reset(local_info_t *local, पूर्णांक hcr)
अणु
	अचिन्हित अक्षर corsave;
	काष्ठा hostap_plx_priv *hw_priv = local->hw_priv;

	अगर (hw_priv->attr_mem == शून्य) अणु
		/* TMD7160 - COR at card's first I/O addr */
		corsave = inb(hw_priv->cor_offset);
		outb(corsave | COR_SRESET, hw_priv->cor_offset);
		mdelay(10);
		outb(hcr, hw_priv->cor_offset + 2);
		mdelay(10);
		outb(corsave & ~COR_SRESET, hw_priv->cor_offset);
		mdelay(10);
	पूर्ण अन्यथा अणु
		/* PLX9052 */
		corsave = पढ़ोb(hw_priv->attr_mem + hw_priv->cor_offset);
		ग_लिखोb(corsave | COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(10);
		ग_लिखोb(hcr, hw_priv->attr_mem + hw_priv->cor_offset + 2);
		mdelay(10);
		ग_लिखोb(corsave & ~COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(10);
	पूर्ण
पूर्ण


अटल काष्ठा prism2_helper_functions prism2_plx_funcs =
अणु
	.card_present	= शून्य,
	.cor_sreset	= prism2_plx_cor_sreset,
	.genesis_reset	= prism2_plx_genesis_reset,
	.hw_type	= HOSTAP_HW_PLX,
पूर्ण;


अटल पूर्णांक prism2_plx_check_cis(व्योम __iomem *attr_mem, पूर्णांक attr_len,
				अचिन्हित पूर्णांक *cor_offset,
				अचिन्हित पूर्णांक *cor_index)
अणु
#घोषणा CISTPL_CONFIG 0x1A
#घोषणा CISTPL_MANFID 0x20
#घोषणा CISTPL_END 0xFF
#घोषणा CIS_MAX_LEN 256
	u8 *cis;
	पूर्णांक i, pos;
	अचिन्हित पूर्णांक rmsz, rasz, manfid1, manfid2;
	काष्ठा prism2_plx_manfid *manfid;

	cis = kदो_स्मृति(CIS_MAX_LEN, GFP_KERNEL);
	अगर (cis == शून्य)
		वापस -ENOMEM;

	/* पढ़ो CIS; it is in even offsets in the beginning of attr_mem */
	क्रम (i = 0; i < CIS_MAX_LEN; i++)
		cis[i] = पढ़ोb(attr_mem + 2 * i);
	prपूर्णांकk(KERN_DEBUG "%s: CIS: %6ph ...\n", dev_info, cis);

	/* set reasonable शेषs क्रम Prism2 cards just in हाल CIS parsing
	 * fails */
	*cor_offset = 0x3e0;
	*cor_index = 0x01;
	manfid1 = manfid2 = 0;

	pos = 0;
	जबतक (pos < CIS_MAX_LEN - 1 && cis[pos] != CISTPL_END) अणु
		अगर (pos + 2 + cis[pos + 1] > CIS_MAX_LEN)
			जाओ cis_error;

		चयन (cis[pos]) अणु
		हाल CISTPL_CONFIG:
			अगर (cis[pos + 1] < 2)
				जाओ cis_error;
			rmsz = (cis[pos + 2] & 0x3c) >> 2;
			rasz = cis[pos + 2] & 0x03;
			अगर (4 + rasz + rmsz > cis[pos + 1])
				जाओ cis_error;
			*cor_index = cis[pos + 3] & 0x3F;
			*cor_offset = 0;
			क्रम (i = 0; i <= rasz; i++)
				*cor_offset += cis[pos + 4 + i] << (8 * i);
			prपूर्णांकk(KERN_DEBUG "%s: cor_index=0x%x "
			       "cor_offset=0x%x\n", dev_info,
			       *cor_index, *cor_offset);
			अगर (*cor_offset > attr_len) अणु
				prपूर्णांकk(KERN_ERR "%s: COR offset not within "
				       "attr_mem\n", dev_info);
				kमुक्त(cis);
				वापस -1;
			पूर्ण
			अवरोध;

		हाल CISTPL_MANFID:
			अगर (cis[pos + 1] < 4)
				जाओ cis_error;
			manfid1 = cis[pos + 2] + (cis[pos + 3] << 8);
			manfid2 = cis[pos + 4] + (cis[pos + 5] << 8);
			prपूर्णांकk(KERN_DEBUG "%s: manfid=0x%04x, 0x%04x\n",
			       dev_info, manfid1, manfid2);
			अवरोध;
		पूर्ण

		pos += cis[pos + 1] + 2;
	पूर्ण

	अगर (pos >= CIS_MAX_LEN || cis[pos] != CISTPL_END)
		जाओ cis_error;

	क्रम (manfid = prism2_plx_known_manfids; manfid->manfid1 != 0; manfid++)
		अगर (manfid1 == manfid->manfid1 && manfid2 == manfid->manfid2) अणु
			kमुक्त(cis);
			वापस 0;
		पूर्ण

	prपूर्णांकk(KERN_INFO "%s: unknown manfid 0x%04x, 0x%04x - assuming this is"
	       " not supported card\n", dev_info, manfid1, manfid2);
	जाओ fail;

 cis_error:
	prपूर्णांकk(KERN_WARNING "%s: invalid CIS data\n", dev_info);

 fail:
	kमुक्त(cis);
	अगर (ignore_cis) अणु
		prपूर्णांकk(KERN_INFO "%s: ignore_cis parameter set - ignoring "
		       "errors during CIS verification\n", dev_info);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण


अटल पूर्णांक prism2_plx_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित पूर्णांक pccard_ioaddr, plx_ioaddr;
	अचिन्हित दीर्घ pccard_attr_mem;
	अचिन्हित पूर्णांक pccard_attr_len;
	व्योम __iomem *attr_mem = शून्य;
	अचिन्हित पूर्णांक cor_offset = 0, cor_index = 0;
	u32 reg;
	local_info_t *local = शून्य;
	काष्ठा net_device *dev = शून्य;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	अटल पूर्णांक cards_found /* = 0 */;
	पूर्णांक irq_रेजिस्टरed = 0;
	पूर्णांक पंचांगd7160;
	काष्ठा hostap_plx_priv *hw_priv;

	hw_priv = kzalloc(माप(*hw_priv), GFP_KERNEL);
	अगर (hw_priv == शून्य)
		वापस -ENOMEM;

	अगर (pci_enable_device(pdev))
		जाओ err_out_मुक्त;

	/* National Datacomm NCP130 based on TMD7160, not PLX9052. */
	पंचांगd7160 = (pdev->venकरोr == 0x15e8) && (pdev->device == 0x0131);

	plx_ioaddr = pci_resource_start(pdev, 1);
	pccard_ioaddr = pci_resource_start(pdev, पंचांगd7160 ? 2 : 3);

	अगर (पंचांगd7160) अणु
		/* TMD7160 */
		attr_mem = शून्य; /* no access to PC Card attribute memory */

		prपूर्णांकk(KERN_INFO "TMD7160 PCI/PCMCIA adapter: io=0x%x, "
		       "irq=%d, pccard_io=0x%x\n",
		       plx_ioaddr, pdev->irq, pccard_ioaddr);

		cor_offset = plx_ioaddr;
		cor_index = 0x04;

		outb(cor_index | COR_LEVLREQ | COR_ENABLE_FUNC, plx_ioaddr);
		mdelay(1);
		reg = inb(plx_ioaddr);
		अगर (reg != (cor_index | COR_LEVLREQ | COR_ENABLE_FUNC)) अणु
			prपूर्णांकk(KERN_ERR "%s: Error setting COR (expected="
			       "0x%02x, was=0x%02x)\n", dev_info,
			       cor_index | COR_LEVLREQ | COR_ENABLE_FUNC, reg);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* PLX9052 */
		pccard_attr_mem = pci_resource_start(pdev, 2);
		pccard_attr_len = pci_resource_len(pdev, 2);
		अगर (pccard_attr_len < PLX_MIN_ATTR_LEN)
			जाओ fail;


		attr_mem = ioremap(pccard_attr_mem, pccard_attr_len);
		अगर (attr_mem == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%s: cannot remap attr_mem\n",
			       dev_info);
			जाओ fail;
		पूर्ण

		prपूर्णांकk(KERN_INFO "PLX9052 PCI/PCMCIA adapter: "
		       "mem=0x%lx, plx_io=0x%x, irq=%d, pccard_io=0x%x\n",
		       pccard_attr_mem, plx_ioaddr, pdev->irq, pccard_ioaddr);

		अगर (prism2_plx_check_cis(attr_mem, pccard_attr_len,
					 &cor_offset, &cor_index)) अणु
			prपूर्णांकk(KERN_INFO "Unknown PC Card CIS - not a "
			       "Prism2/2.5 card?\n");
			जाओ fail;
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "Prism2/2.5 PC Card detected in PLX9052 "
		       "adapter\n");

		/* Write COR to enable PC Card */
		ग_लिखोb(cor_index | COR_LEVLREQ | COR_ENABLE_FUNC,
		       attr_mem + cor_offset);

		/* Enable PCI पूर्णांकerrupts अगर they are not alपढ़ोy enabled */
		reg = inl(plx_ioaddr + PLX_INTCSR);
		prपूर्णांकk(KERN_DEBUG "PLX_INTCSR=0x%x\n", reg);
		अगर (!(reg & PLX_INTCSR_PCI_INTEN)) अणु
			outl(reg | PLX_INTCSR_PCI_INTEN,
			     plx_ioaddr + PLX_INTCSR);
			अगर (!(inl(plx_ioaddr + PLX_INTCSR) &
			      PLX_INTCSR_PCI_INTEN)) अणु
				prपूर्णांकk(KERN_WARNING "%s: Could not enable "
				       "Local Interrupts\n", dev_info);
				जाओ fail;
			पूर्ण
		पूर्ण

		reg = inl(plx_ioaddr + PLX_CNTRL);
		prपूर्णांकk(KERN_DEBUG "PLX_CNTRL=0x%x (Serial EEPROM "
		       "present=%d)\n",
		       reg, (reg & PLX_CNTRL_SERIAL_EEPROM_PRESENT) != 0);
		/* should set PLX_PCIIPR to 0x01 (INTA#) अगर Serial EEPROM is
		 * not present; but are there really such cards in use(?) */
	पूर्ण

	dev = prism2_init_local_data(&prism2_plx_funcs, cards_found,
				     &pdev->dev);
	अगर (dev == शून्य)
		जाओ fail;
	अगरace = netdev_priv(dev);
	local = अगरace->local;
	local->hw_priv = hw_priv;
	cards_found++;

	dev->irq = pdev->irq;
	dev->base_addr = pccard_ioaddr;
	hw_priv->attr_mem = attr_mem;
	hw_priv->cor_offset = cor_offset;

	pci_set_drvdata(pdev, dev);

	अगर (request_irq(dev->irq, prism2_पूर्णांकerrupt, IRQF_SHARED, dev->name,
			dev)) अणु
		prपूर्णांकk(KERN_WARNING "%s: request_irq failed\n", dev->name);
		जाओ fail;
	पूर्ण अन्यथा
		irq_रेजिस्टरed = 1;

	अगर (prism2_hw_config(dev, 1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hardware initialization failed\n",
		       dev_info);
		जाओ fail;
	पूर्ण

	वापस hostap_hw_पढ़ोy(dev);

 fail:
	अगर (irq_रेजिस्टरed && dev)
		मुक्त_irq(dev->irq, dev);

	अगर (attr_mem)
		iounmap(attr_mem);

	pci_disable_device(pdev);
	prism2_मुक्त_local_data(dev);

 err_out_मुक्त:
	kमुक्त(hw_priv);

	वापस -ENODEV;
पूर्ण


अटल व्योम prism2_plx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_plx_priv *hw_priv;

	dev = pci_get_drvdata(pdev);
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;

	/* Reset the hardware, and ensure पूर्णांकerrupts are disabled. */
	prism2_plx_cor_sreset(अगरace->local);
	hfa384x_disable_पूर्णांकerrupts(dev);

	अगर (hw_priv->attr_mem)
		iounmap(hw_priv->attr_mem);
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);

	prism2_मुक्त_local_data(dev);
	kमुक्त(hw_priv);
	pci_disable_device(pdev);
पूर्ण


MODULE_DEVICE_TABLE(pci, prism2_plx_id_table);

अटल काष्ठा pci_driver prism2_plx_driver = अणु
	.name		= "hostap_plx",
	.id_table	= prism2_plx_id_table,
	.probe		= prism2_plx_probe,
	.हटाओ		= prism2_plx_हटाओ,
पूर्ण;

module_pci_driver(prism2_plx_driver);
