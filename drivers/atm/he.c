<शैली गुरु>
/*

  he.c

  ForeRunnerHE ATM Adapter driver क्रम ATM on Linux
  Copyright (C) 1999-2001  Naval Research Laboratory

  This library is मुक्त software; you can redistribute it and/or
  modअगरy it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License क्रम more details.

  You should have received a copy of the GNU Lesser General Public
  License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*

  he.c

  ForeRunnerHE ATM Adapter driver क्रम ATM on Linux
  Copyright (C) 1999-2001  Naval Research Laboratory

  Permission to use, copy, modअगरy and distribute this software and its
  करोcumentation is hereby granted, provided that both the copyright
  notice and this permission notice appear in all copies of the software,
  derivative works or modअगरied versions, and any portions thereof, and
  that both notices appear in supporting करोcumentation.

  NRL ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION AND
  DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER
  RESULTING FROM THE USE OF THIS SOFTWARE.

  This driver was written using the "Programmer's Reference Manual क्रम
  ForeRunnerHE(पंचांग)", MANU0361-01 - Rev. A, 08/21/98.

  AUTHORS:
	chas williams <chas@cmf.nrl.navy.mil>
	eric kinzie <ekinzie@cmf.nrl.navy.mil>

  NOTES:
	4096 supported 'connections'
	group 0 is used क्रम all traffic
	पूर्णांकerrupt queue 0 is used क्रम all पूर्णांकerrupts
	aal0 support (based on work from ulrich.u.muller@nokia.com)

 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/sonet.h>

#अघोषित USE_SCATTERGATHER
#अघोषित USE_CHECKSUM_HW			/* still confused about this */
/* #अघोषित HE_DEBUG */

#समावेश "he.h"
#समावेश "suni.h"
#समावेश <linux/aपंचांग_he.h>

#घोषणा hprपूर्णांकk(fmt,args...)	prपूर्णांकk(KERN_ERR DEV_LABEL "%d: " fmt, he_dev->number , ##args)

#अगर_घोषित HE_DEBUG
#घोषणा HPRINTK(fmt,args...)	prपूर्णांकk(KERN_DEBUG DEV_LABEL "%d: " fmt, he_dev->number , ##args)
#अन्यथा /* !HE_DEBUG */
#घोषणा HPRINTK(fmt,args...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* HE_DEBUG */

/* declarations */

अटल पूर्णांक he_खोलो(काष्ठा aपंचांग_vcc *vcc);
अटल व्योम he_बंद(काष्ठा aपंचांग_vcc *vcc);
अटल पूर्णांक he_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल पूर्णांक he_ioctl(काष्ठा aपंचांग_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
अटल irqवापस_t he_irq_handler(पूर्णांक irq, व्योम *dev_id);
अटल व्योम he_tasklet(अचिन्हित दीर्घ data);
अटल पूर्णांक he_proc_पढ़ो(काष्ठा aपंचांग_dev *dev,loff_t *pos,अक्षर *page);
अटल पूर्णांक he_start(काष्ठा aपंचांग_dev *dev);
अटल व्योम he_stop(काष्ठा he_dev *dev);
अटल व्योम he_phy_put(काष्ठा aपंचांग_dev *, अचिन्हित अक्षर, अचिन्हित दीर्घ);
अटल अचिन्हित अक्षर he_phy_get(काष्ठा aपंचांग_dev *, अचिन्हित दीर्घ);

अटल u8 पढ़ो_prom_byte(काष्ठा he_dev *he_dev, पूर्णांक addr);

/* globals */

अटल काष्ठा he_dev *he_devs;
अटल bool disable64;
अटल लघु nvpibits = -1;
अटल लघु nvcibits = -1;
अटल लघु rx_skb_reserve = 16;
अटल bool irq_coalesce = true;
अटल bool sdh;

/* Read from EEPROM = 0000 0011b */
अटल अचिन्हित पूर्णांक पढ़ोtab[] = अणु
	CS_HIGH | CLK_HIGH,
	CS_LOW | CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW,
	CLK_HIGH,               /* 0 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH,     /* 1 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH      /* 1 */
पूर्ण;     
 
/* Clock to पढ़ो from/ग_लिखो to the EEPROM */
अटल अचिन्हित पूर्णांक घड़ीtab[] = अणु
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW
पूर्ण;     

अटल स्थिर काष्ठा aपंचांगdev_ops he_ops =
अणु
	.खोलो =		he_खोलो,
	.बंद =	he_बंद,	
	.ioctl =	he_ioctl,	
	.send =		he_send,
	.phy_put =	he_phy_put,
	.phy_get =	he_phy_get,
	.proc_पढ़ो =	he_proc_पढ़ो,
	.owner =	THIS_MODULE
पूर्ण;

#घोषणा he_ग_लिखोl(dev, val, reg)	करो अणु ग_लिखोl(val, (dev)->membase + (reg)); wmb(); पूर्ण जबतक (0)
#घोषणा he_पढ़ोl(dev, reg)		पढ़ोl((dev)->membase + (reg))

/* section 2.12 connection memory access */

अटल __अंतरभूत__ व्योम
he_ग_लिखोl_पूर्णांकernal(काष्ठा he_dev *he_dev, अचिन्हित val, अचिन्हित addr,
								अचिन्हित flags)
अणु
	he_ग_लिखोl(he_dev, val, CON_DAT);
	(व्योम) he_पढ़ोl(he_dev, CON_DAT);		/* flush posted ग_लिखोs */
	he_ग_लिखोl(he_dev, flags | CON_CTL_WRITE | CON_CTL_ADDR(addr), CON_CTL);
	जबतक (he_पढ़ोl(he_dev, CON_CTL) & CON_CTL_BUSY);
पूर्ण

#घोषणा he_ग_लिखोl_rcm(dev, val, reg) 				\
			he_ग_लिखोl_पूर्णांकernal(dev, val, reg, CON_CTL_RCM)

#घोषणा he_ग_लिखोl_tcm(dev, val, reg) 				\
			he_ग_लिखोl_पूर्णांकernal(dev, val, reg, CON_CTL_TCM)

#घोषणा he_ग_लिखोl_mbox(dev, val, reg) 				\
			he_ग_लिखोl_पूर्णांकernal(dev, val, reg, CON_CTL_MBOX)

अटल अचिन्हित
he_पढ़ोl_पूर्णांकernal(काष्ठा he_dev *he_dev, अचिन्हित addr, अचिन्हित flags)
अणु
	he_ग_लिखोl(he_dev, flags | CON_CTL_READ | CON_CTL_ADDR(addr), CON_CTL);
	जबतक (he_पढ़ोl(he_dev, CON_CTL) & CON_CTL_BUSY);
	वापस he_पढ़ोl(he_dev, CON_DAT);
पूर्ण

#घोषणा he_पढ़ोl_rcm(dev, reg) \
			he_पढ़ोl_पूर्णांकernal(dev, reg, CON_CTL_RCM)

#घोषणा he_पढ़ोl_tcm(dev, reg) \
			he_पढ़ोl_पूर्णांकernal(dev, reg, CON_CTL_TCM)

#घोषणा he_पढ़ोl_mbox(dev, reg) \
			he_पढ़ोl_पूर्णांकernal(dev, reg, CON_CTL_MBOX)


/* figure 2.2 connection id */

#घोषणा he_mkcid(dev, vpi, vci)		(((vpi << (dev)->vcibits) | vci) & 0x1fff)

/* 2.5.1 per connection transmit state रेजिस्टरs */

#घोषणा he_ग_लिखोl_tsr0(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 0)
#घोषणा he_पढ़ोl_tsr0(dev, cid) \
		he_पढ़ोl_tcm(dev, CONFIG_TSRA | (cid << 3) | 0)

#घोषणा he_ग_लिखोl_tsr1(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 1)

#घोषणा he_ग_लिखोl_tsr2(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 2)

#घोषणा he_ग_लिखोl_tsr3(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 3)

#घोषणा he_ग_लिखोl_tsr4(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 4)

	/* from page 2-20
	 *
	 * NOTE While the transmit connection is active, bits 23 through 0
	 *      of this रेजिस्टर must not be written by the host.  Byte
	 *      enables should be used during normal operation when writing
	 *      the most signअगरicant byte.
	 */

#घोषणा he_ग_लिखोl_tsr4_upper(dev, val, cid) \
		he_ग_लिखोl_पूर्णांकernal(dev, val, CONFIG_TSRA | (cid << 3) | 4, \
							CON_CTL_TCM \
							| CON_BYTE_DISABLE_2 \
							| CON_BYTE_DISABLE_1 \
							| CON_BYTE_DISABLE_0)

#घोषणा he_पढ़ोl_tsr4(dev, cid) \
		he_पढ़ोl_tcm(dev, CONFIG_TSRA | (cid << 3) | 4)

#घोषणा he_ग_लिखोl_tsr5(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 5)

#घोषणा he_ग_लिखोl_tsr6(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 6)

#घोषणा he_ग_लिखोl_tsr7(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRA | (cid << 3) | 7)


#घोषणा he_ग_लिखोl_tsr8(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRB | (cid << 2) | 0)

#घोषणा he_ग_लिखोl_tsr9(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRB | (cid << 2) | 1)

#घोषणा he_ग_लिखोl_tsr10(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRB | (cid << 2) | 2)

#घोषणा he_ग_लिखोl_tsr11(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRB | (cid << 2) | 3)


#घोषणा he_ग_लिखोl_tsr12(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRC | (cid << 1) | 0)

#घोषणा he_ग_लिखोl_tsr13(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRC | (cid << 1) | 1)


#घोषणा he_ग_लिखोl_tsr14(dev, val, cid) \
		he_ग_लिखोl_tcm(dev, val, CONFIG_TSRD | cid)

#घोषणा he_ग_लिखोl_tsr14_upper(dev, val, cid) \
		he_ग_लिखोl_पूर्णांकernal(dev, val, CONFIG_TSRD | cid, \
							CON_CTL_TCM \
							| CON_BYTE_DISABLE_2 \
							| CON_BYTE_DISABLE_1 \
							| CON_BYTE_DISABLE_0)

/* 2.7.1 per connection receive state रेजिस्टरs */

#घोषणा he_ग_लिखोl_rsr0(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 0)
#घोषणा he_पढ़ोl_rsr0(dev, cid) \
		he_पढ़ोl_rcm(dev, 0x00000 | (cid << 3) | 0)

#घोषणा he_ग_लिखोl_rsr1(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 1)

#घोषणा he_ग_लिखोl_rsr2(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 2)

#घोषणा he_ग_लिखोl_rsr3(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 3)

#घोषणा he_ग_लिखोl_rsr4(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 4)

#घोषणा he_ग_लिखोl_rsr5(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 5)

#घोषणा he_ग_लिखोl_rsr6(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 6)

#घोषणा he_ग_लिखोl_rsr7(dev, val, cid) \
		he_ग_लिखोl_rcm(dev, val, 0x00000 | (cid << 3) | 7)

अटल __अंतरभूत__ काष्ठा aपंचांग_vcc*
__find_vcc(काष्ठा he_dev *he_dev, अचिन्हित cid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sock *s;
	लघु vpi;
	पूर्णांक vci;

	vpi = cid >> he_dev->vcibits;
	vci = cid & ((1 << he_dev->vcibits) - 1);
	head = &vcc_hash[vci & (VCC_HTABLE_SIZE -1)];

	sk_क्रम_each(s, head) अणु
		vcc = aपंचांग_sk(s);
		अगर (vcc->dev == he_dev->aपंचांग_dev &&
		    vcc->vci == vci && vcc->vpi == vpi &&
		    vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
				वापस vcc;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक he_init_one(काष्ठा pci_dev *pci_dev,
		       स्थिर काष्ठा pci_device_id *pci_ent)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev = शून्य;
	काष्ठा he_dev *he_dev = शून्य;
	पूर्णांक err = 0;

	prपूर्णांकk(KERN_INFO "ATM he driver\n");

	अगर (pci_enable_device(pci_dev))
		वापस -EIO;
	अगर (dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32)) != 0) अणु
		prपूर्णांकk(KERN_WARNING "he: no suitable dma available\n");
		err = -EIO;
		जाओ init_one_failure;
	पूर्ण

	aपंचांग_dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, &pci_dev->dev, &he_ops, -1, शून्य);
	अगर (!aपंचांग_dev) अणु
		err = -ENODEV;
		जाओ init_one_failure;
	पूर्ण
	pci_set_drvdata(pci_dev, aपंचांग_dev);

	he_dev = kzalloc(माप(काष्ठा he_dev),
							GFP_KERNEL);
	अगर (!he_dev) अणु
		err = -ENOMEM;
		जाओ init_one_failure;
	पूर्ण
	he_dev->pci_dev = pci_dev;
	he_dev->aपंचांग_dev = aपंचांग_dev;
	he_dev->aपंचांग_dev->dev_data = he_dev;
	aपंचांग_dev->dev_data = he_dev;
	he_dev->number = aपंचांग_dev->number;
	tasklet_init(&he_dev->tasklet, he_tasklet, (अचिन्हित दीर्घ) he_dev);
	spin_lock_init(&he_dev->global_lock);

	अगर (he_start(aपंचांग_dev)) अणु
		he_stop(he_dev);
		err = -ENODEV;
		जाओ init_one_failure;
	पूर्ण
	he_dev->next = शून्य;
	अगर (he_devs)
		he_dev->next = he_devs;
	he_devs = he_dev;
	वापस 0;

init_one_failure:
	अगर (aपंचांग_dev)
		aपंचांग_dev_deरेजिस्टर(aपंचांग_dev);
	kमुक्त(he_dev);
	pci_disable_device(pci_dev);
	वापस err;
पूर्ण

अटल व्योम he_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	काष्ठा he_dev *he_dev;

	aपंचांग_dev = pci_get_drvdata(pci_dev);
	he_dev = HE_DEV(aपंचांग_dev);

	/* need to हटाओ from he_devs */

	he_stop(he_dev);
	aपंचांग_dev_deरेजिस्टर(aपंचांग_dev);
	kमुक्त(he_dev);

	pci_disable_device(pci_dev);
पूर्ण


अटल अचिन्हित
rate_to_aपंचांगf(अचिन्हित rate)		/* cps to aपंचांग क्रमum क्रमmat */
अणु
#घोषणा NONZERO (1 << 14)

	अचिन्हित exp = 0;

	अगर (rate == 0)
		वापस 0;

	rate <<= 9;
	जबतक (rate > 0x3ff) अणु
		++exp;
		rate >>= 1;
	पूर्ण

	वापस (NONZERO | (exp << 9) | (rate & 0x1ff));
पूर्ण

अटल व्योम he_init_rx_lbfp0(काष्ठा he_dev *he_dev)
अणु
	अचिन्हित i, lbm_offset, lbufd_index, lbuf_addr, lbuf_count;
	अचिन्हित lbufs_per_row = he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अचिन्हित lbuf_bufsize = he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD;
	अचिन्हित row_offset = he_dev->r0_startrow * he_dev->bytes_per_row;
	
	lbufd_index = 0;
	lbm_offset = he_पढ़ोl(he_dev, RCMLBM_BA);

	he_ग_लिखोl(he_dev, lbufd_index, RLBF0_H);

	क्रम (i = 0, lbuf_count = 0; i < he_dev->r0_numbuffs; ++i) अणु
		lbufd_index += 2;
		lbuf_addr = (row_offset + (lbuf_count * lbuf_bufsize)) / 32;

		he_ग_लिखोl_rcm(he_dev, lbuf_addr, lbm_offset);
		he_ग_लिखोl_rcm(he_dev, lbufd_index, lbm_offset + 1);

		अगर (++lbuf_count == lbufs_per_row) अणु
			lbuf_count = 0;
			row_offset += he_dev->bytes_per_row;
		पूर्ण
		lbm_offset += 4;
	पूर्ण
		
	he_ग_लिखोl(he_dev, lbufd_index - 2, RLBF0_T);
	he_ग_लिखोl(he_dev, he_dev->r0_numbuffs, RLBF0_C);
पूर्ण

अटल व्योम he_init_rx_lbfp1(काष्ठा he_dev *he_dev)
अणु
	अचिन्हित i, lbm_offset, lbufd_index, lbuf_addr, lbuf_count;
	अचिन्हित lbufs_per_row = he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अचिन्हित lbuf_bufsize = he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD;
	अचिन्हित row_offset = he_dev->r1_startrow * he_dev->bytes_per_row;
	
	lbufd_index = 1;
	lbm_offset = he_पढ़ोl(he_dev, RCMLBM_BA) + (2 * lbufd_index);

	he_ग_लिखोl(he_dev, lbufd_index, RLBF1_H);

	क्रम (i = 0, lbuf_count = 0; i < he_dev->r1_numbuffs; ++i) अणु
		lbufd_index += 2;
		lbuf_addr = (row_offset + (lbuf_count * lbuf_bufsize)) / 32;

		he_ग_लिखोl_rcm(he_dev, lbuf_addr, lbm_offset);
		he_ग_लिखोl_rcm(he_dev, lbufd_index, lbm_offset + 1);

		अगर (++lbuf_count == lbufs_per_row) अणु
			lbuf_count = 0;
			row_offset += he_dev->bytes_per_row;
		पूर्ण
		lbm_offset += 4;
	पूर्ण
		
	he_ग_लिखोl(he_dev, lbufd_index - 2, RLBF1_T);
	he_ग_लिखोl(he_dev, he_dev->r1_numbuffs, RLBF1_C);
पूर्ण

अटल व्योम he_init_tx_lbfp(काष्ठा he_dev *he_dev)
अणु
	अचिन्हित i, lbm_offset, lbufd_index, lbuf_addr, lbuf_count;
	अचिन्हित lbufs_per_row = he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अचिन्हित lbuf_bufsize = he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD;
	अचिन्हित row_offset = he_dev->tx_startrow * he_dev->bytes_per_row;
	
	lbufd_index = he_dev->r0_numbuffs + he_dev->r1_numbuffs;
	lbm_offset = he_पढ़ोl(he_dev, RCMLBM_BA) + (2 * lbufd_index);

	he_ग_लिखोl(he_dev, lbufd_index, TLBF_H);

	क्रम (i = 0, lbuf_count = 0; i < he_dev->tx_numbuffs; ++i) अणु
		lbufd_index += 1;
		lbuf_addr = (row_offset + (lbuf_count * lbuf_bufsize)) / 32;

		he_ग_लिखोl_rcm(he_dev, lbuf_addr, lbm_offset);
		he_ग_लिखोl_rcm(he_dev, lbufd_index, lbm_offset + 1);

		अगर (++lbuf_count == lbufs_per_row) अणु
			lbuf_count = 0;
			row_offset += he_dev->bytes_per_row;
		पूर्ण
		lbm_offset += 2;
	पूर्ण
		
	he_ग_लिखोl(he_dev, lbufd_index - 1, TLBF_T);
पूर्ण

अटल पूर्णांक he_init_tpdrq(काष्ठा he_dev *he_dev)
अणु
	he_dev->tpdrq_base = dma_alloc_coherent(&he_dev->pci_dev->dev,
						CONFIG_TPDRQ_SIZE * माप(काष्ठा he_tpdrq),
						&he_dev->tpdrq_phys,
						GFP_KERNEL);
	अगर (he_dev->tpdrq_base == शून्य) अणु
		hprपूर्णांकk("failed to alloc tpdrq\n");
		वापस -ENOMEM;
	पूर्ण

	he_dev->tpdrq_tail = he_dev->tpdrq_base;
	he_dev->tpdrq_head = he_dev->tpdrq_base;

	he_ग_लिखोl(he_dev, he_dev->tpdrq_phys, TPDRQ_B_H);
	he_ग_लिखोl(he_dev, 0, TPDRQ_T);	
	he_ग_लिखोl(he_dev, CONFIG_TPDRQ_SIZE - 1, TPDRQ_S);

	वापस 0;
पूर्ण

अटल व्योम he_init_cs_block(काष्ठा he_dev *he_dev)
अणु
	अचिन्हित घड़ी, rate, delta;
	पूर्णांक reg;

	/* 5.1.7 cs block initialization */

	क्रम (reg = 0; reg < 0x20; ++reg)
		he_ग_लिखोl_mbox(he_dev, 0x0, CS_STTIM0 + reg);

	/* rate grid समयr reload values */

	घड़ी = he_is622(he_dev) ? 66667000 : 50000000;
	rate = he_dev->aपंचांग_dev->link_rate;
	delta = rate / 16 / 2;

	क्रम (reg = 0; reg < 0x10; ++reg) अणु
		/* 2.4 पूर्णांकernal transmit function
		 *
	 	 * we initialize the first row in the rate grid.
		 * values are period (in घड़ी cycles) of समयr
		 */
		अचिन्हित period = घड़ी / rate;

		he_ग_लिखोl_mbox(he_dev, period, CS_TGRLD0 + reg);
		rate -= delta;
	पूर्ण

	अगर (he_is622(he_dev)) अणु
		/* table 5.2 (4 cells per lbuf) */
		he_ग_लिखोl_mbox(he_dev, 0x000800fa, CS_ERTHR0);
		he_ग_लिखोl_mbox(he_dev, 0x000c33cb, CS_ERTHR1);
		he_ग_लिखोl_mbox(he_dev, 0x0010101b, CS_ERTHR2);
		he_ग_लिखोl_mbox(he_dev, 0x00181dac, CS_ERTHR3);
		he_ग_लिखोl_mbox(he_dev, 0x00280600, CS_ERTHR4);

		/* table 5.3, 5.4, 5.5, 5.6, 5.7 */
		he_ग_लिखोl_mbox(he_dev, 0x023de8b3, CS_ERCTL0);
		he_ग_लिखोl_mbox(he_dev, 0x1801, CS_ERCTL1);
		he_ग_लिखोl_mbox(he_dev, 0x68b3, CS_ERCTL2);
		he_ग_लिखोl_mbox(he_dev, 0x1280, CS_ERSTAT0);
		he_ग_लिखोl_mbox(he_dev, 0x68b3, CS_ERSTAT1);
		he_ग_लिखोl_mbox(he_dev, 0x14585, CS_RTFWR);

		he_ग_लिखोl_mbox(he_dev, 0x4680, CS_RTATR);

		/* table 5.8 */
		he_ग_लिखोl_mbox(he_dev, 0x00159ece, CS_TFBSET);
		he_ग_लिखोl_mbox(he_dev, 0x68b3, CS_WCRMAX);
		he_ग_लिखोl_mbox(he_dev, 0x5eb3, CS_WCRMIN);
		he_ग_लिखोl_mbox(he_dev, 0xe8b3, CS_WCRINC);
		he_ग_लिखोl_mbox(he_dev, 0xdeb3, CS_WCRDEC);
		he_ग_लिखोl_mbox(he_dev, 0x68b3, CS_WCRCEIL);

		/* table 5.9 */
		he_ग_लिखोl_mbox(he_dev, 0x5, CS_OTPPER);
		he_ग_लिखोl_mbox(he_dev, 0x14, CS_OTWPER);
	पूर्ण अन्यथा अणु
		/* table 5.1 (4 cells per lbuf) */
		he_ग_लिखोl_mbox(he_dev, 0x000400ea, CS_ERTHR0);
		he_ग_लिखोl_mbox(he_dev, 0x00063388, CS_ERTHR1);
		he_ग_लिखोl_mbox(he_dev, 0x00081018, CS_ERTHR2);
		he_ग_लिखोl_mbox(he_dev, 0x000c1dac, CS_ERTHR3);
		he_ग_लिखोl_mbox(he_dev, 0x0014051a, CS_ERTHR4);

		/* table 5.3, 5.4, 5.5, 5.6, 5.7 */
		he_ग_लिखोl_mbox(he_dev, 0x0235e4b1, CS_ERCTL0);
		he_ग_लिखोl_mbox(he_dev, 0x4701, CS_ERCTL1);
		he_ग_लिखोl_mbox(he_dev, 0x64b1, CS_ERCTL2);
		he_ग_लिखोl_mbox(he_dev, 0x1280, CS_ERSTAT0);
		he_ग_लिखोl_mbox(he_dev, 0x64b1, CS_ERSTAT1);
		he_ग_लिखोl_mbox(he_dev, 0xf424, CS_RTFWR);

		he_ग_लिखोl_mbox(he_dev, 0x4680, CS_RTATR);

		/* table 5.8 */
		he_ग_लिखोl_mbox(he_dev, 0x000563b7, CS_TFBSET);
		he_ग_लिखोl_mbox(he_dev, 0x64b1, CS_WCRMAX);
		he_ग_लिखोl_mbox(he_dev, 0x5ab1, CS_WCRMIN);
		he_ग_लिखोl_mbox(he_dev, 0xe4b1, CS_WCRINC);
		he_ग_लिखोl_mbox(he_dev, 0xdab1, CS_WCRDEC);
		he_ग_लिखोl_mbox(he_dev, 0x64b1, CS_WCRCEIL);

		/* table 5.9 */
		he_ग_लिखोl_mbox(he_dev, 0x6, CS_OTPPER);
		he_ग_लिखोl_mbox(he_dev, 0x1e, CS_OTWPER);
	पूर्ण

	he_ग_लिखोl_mbox(he_dev, 0x8, CS_OTTLIM);

	क्रम (reg = 0; reg < 0x8; ++reg)
		he_ग_लिखोl_mbox(he_dev, 0x0, CS_HGRRT0 + reg);

पूर्ण

अटल पूर्णांक he_init_cs_block_rcm(काष्ठा he_dev *he_dev)
अणु
	अचिन्हित (*rategrid)[16][16];
	अचिन्हित rate, delta;
	पूर्णांक i, j, reg;

	अचिन्हित rate_aपंचांगf, exp, man;
	अचिन्हित दीर्घ दीर्घ rate_cps;
	पूर्णांक mult, buf, buf_limit = 4;

	rategrid = kदो_स्मृति( माप(अचिन्हित) * 16 * 16, GFP_KERNEL);
	अगर (!rategrid)
		वापस -ENOMEM;

	/* initialize rate grid group table */

	क्रम (reg = 0x0; reg < 0xff; ++reg)
		he_ग_लिखोl_rcm(he_dev, 0x0, CONFIG_RCMABR + reg);

	/* initialize rate controller groups */

	क्रम (reg = 0x100; reg < 0x1ff; ++reg)
		he_ग_लिखोl_rcm(he_dev, 0x0, CONFIG_RCMABR + reg);
	
	/* initialize tNrm lookup table */

	/* the manual makes reference to a routine in a sample driver
	   क्रम proper configuration; क्रमtunately, we only need this
	   in order to support abr connection */
	
	/* initialize rate to group table */

	rate = he_dev->aपंचांग_dev->link_rate;
	delta = rate / 32;

	/*
	 * 2.4 transmit पूर्णांकernal functions
	 * 
	 * we स्थिरruct a copy of the rate grid used by the scheduler
	 * in order to स्थिरruct the rate to group table below
	 */

	क्रम (j = 0; j < 16; j++) अणु
		(*rategrid)[0][j] = rate;
		rate -= delta;
	पूर्ण

	क्रम (i = 1; i < 16; i++)
		क्रम (j = 0; j < 16; j++)
			अगर (i > 14)
				(*rategrid)[i][j] = (*rategrid)[i - 1][j] / 4;
			अन्यथा
				(*rategrid)[i][j] = (*rategrid)[i - 1][j] / 2;

	/*
	 * 2.4 transmit पूर्णांकernal function
	 *
	 * this table maps the upper 5 bits of exponent and mantissa
	 * of the aपंचांग क्रमum representation of the rate पूर्णांकo an index
	 * on rate grid  
	 */

	rate_aपंचांगf = 0;
	जबतक (rate_aपंचांगf < 0x400) अणु
		man = (rate_aपंचांगf & 0x1f) << 4;
		exp = rate_aपंचांगf >> 5;

		/* 
			instead of '/ 512', use '>> 9' to prevent a call
			to भागdu3 on x86 platक्रमms
		*/
		rate_cps = (अचिन्हित दीर्घ दीर्घ) (1UL << exp) * (man + 512) >> 9;

		अगर (rate_cps < 10)
			rate_cps = 10;	/* 2.2.1 minimum payload rate is 10 cps */

		क्रम (i = 255; i > 0; i--)
			अगर ((*rategrid)[i/16][i%16] >= rate_cps)
				अवरोध;	 /* pick nearest rate instead? */

		/*
		 * each table entry is 16 bits: (rate grid index (8 bits)
		 * and a buffer limit (8 bits)
		 * there are two table entries in each 32-bit रेजिस्टर
		 */

#अगर_घोषित notdef
		buf = rate_cps * he_dev->tx_numbuffs /
				(he_dev->aपंचांग_dev->link_rate * 2);
#अन्यथा
		/* this is pretty, but aव्योमs _भागdu3 and is mostly correct */
		mult = he_dev->aपंचांग_dev->link_rate / ATM_OC3_PCR;
		अगर (rate_cps > (272ULL * mult))
			buf = 4;
		अन्यथा अगर (rate_cps > (204ULL * mult))
			buf = 3;
		अन्यथा अगर (rate_cps > (136ULL * mult))
			buf = 2;
		अन्यथा अगर (rate_cps > (68ULL * mult))
			buf = 1;
		अन्यथा
			buf = 0;
#पूर्ण_अगर
		अगर (buf > buf_limit)
			buf = buf_limit;
		reg = (reg << 16) | ((i << 8) | buf);

#घोषणा RTGTBL_OFFSET 0x400
	  
		अगर (rate_aपंचांगf & 0x1)
			he_ग_लिखोl_rcm(he_dev, reg,
				CONFIG_RCMABR + RTGTBL_OFFSET + (rate_aपंचांगf >> 1));

		++rate_aपंचांगf;
	पूर्ण

	kमुक्त(rategrid);
	वापस 0;
पूर्ण

अटल पूर्णांक he_init_group(काष्ठा he_dev *he_dev, पूर्णांक group)
अणु
	काष्ठा he_buff *heb, *next;
	dma_addr_t mapping;
	पूर्णांक i;

	he_ग_लिखोl(he_dev, 0x0, G0_RBPS_S + (group * 32));
	he_ग_लिखोl(he_dev, 0x0, G0_RBPS_T + (group * 32));
	he_ग_लिखोl(he_dev, 0x0, G0_RBPS_QI + (group * 32));
	he_ग_लिखोl(he_dev, RBP_THRESH(0x1) | RBP_QSIZE(0x0),
		  G0_RBPS_BS + (group * 32));

	/* biपंचांगap table */
	he_dev->rbpl_table = kदो_स्मृति_array(BITS_TO_LONGS(RBPL_TABLE_SIZE),
					   माप(*he_dev->rbpl_table),
					   GFP_KERNEL);
	अगर (!he_dev->rbpl_table) अणु
		hprपूर्णांकk("unable to allocate rbpl bitmap table\n");
		वापस -ENOMEM;
	पूर्ण
	biपंचांगap_zero(he_dev->rbpl_table, RBPL_TABLE_SIZE);

	/* rbpl_virt 64-bit poपूर्णांकers */
	he_dev->rbpl_virt = kदो_स्मृति_array(RBPL_TABLE_SIZE,
					  माप(*he_dev->rbpl_virt),
					  GFP_KERNEL);
	अगर (!he_dev->rbpl_virt) अणु
		hprपूर्णांकk("unable to allocate rbpl virt table\n");
		जाओ out_मुक्त_rbpl_table;
	पूर्ण

	/* large buffer pool */
	he_dev->rbpl_pool = dma_pool_create("rbpl", &he_dev->pci_dev->dev,
					    CONFIG_RBPL_बफ_मानE, 64, 0);
	अगर (he_dev->rbpl_pool == शून्य) अणु
		hprपूर्णांकk("unable to create rbpl pool\n");
		जाओ out_मुक्त_rbpl_virt;
	पूर्ण

	he_dev->rbpl_base = dma_alloc_coherent(&he_dev->pci_dev->dev,
					       CONFIG_RBPL_SIZE * माप(काष्ठा he_rbp),
					       &he_dev->rbpl_phys, GFP_KERNEL);
	अगर (he_dev->rbpl_base == शून्य) अणु
		hprपूर्णांकk("failed to alloc rbpl_base\n");
		जाओ out_destroy_rbpl_pool;
	पूर्ण

	INIT_LIST_HEAD(&he_dev->rbpl_outstanding);

	क्रम (i = 0; i < CONFIG_RBPL_SIZE; ++i) अणु

		heb = dma_pool_alloc(he_dev->rbpl_pool, GFP_KERNEL, &mapping);
		अगर (!heb)
			जाओ out_मुक्त_rbpl;
		heb->mapping = mapping;
		list_add(&heb->entry, &he_dev->rbpl_outstanding);

		set_bit(i, he_dev->rbpl_table);
		he_dev->rbpl_virt[i] = heb;
		he_dev->rbpl_hपूर्णांक = i + 1;
		he_dev->rbpl_base[i].idx =  i << RBP_IDX_OFFSET;
		he_dev->rbpl_base[i].phys = mapping + दुरत्व(काष्ठा he_buff, data);
	पूर्ण
	he_dev->rbpl_tail = &he_dev->rbpl_base[CONFIG_RBPL_SIZE - 1];

	he_ग_लिखोl(he_dev, he_dev->rbpl_phys, G0_RBPL_S + (group * 32));
	he_ग_लिखोl(he_dev, RBPL_MASK(he_dev->rbpl_tail),
						G0_RBPL_T + (group * 32));
	he_ग_लिखोl(he_dev, (CONFIG_RBPL_बफ_मानE - माप(काष्ठा he_buff))/4,
						G0_RBPL_BS + (group * 32));
	he_ग_लिखोl(he_dev,
			RBP_THRESH(CONFIG_RBPL_THRESH) |
			RBP_QSIZE(CONFIG_RBPL_SIZE - 1) |
			RBP_INT_ENB,
						G0_RBPL_QI + (group * 32));

	/* rx buffer पढ़ोy queue */

	he_dev->rbrq_base = dma_alloc_coherent(&he_dev->pci_dev->dev,
					       CONFIG_RBRQ_SIZE * माप(काष्ठा he_rbrq),
					       &he_dev->rbrq_phys, GFP_KERNEL);
	अगर (he_dev->rbrq_base == शून्य) अणु
		hprपूर्णांकk("failed to allocate rbrq\n");
		जाओ out_मुक्त_rbpl;
	पूर्ण

	he_dev->rbrq_head = he_dev->rbrq_base;
	he_ग_लिखोl(he_dev, he_dev->rbrq_phys, G0_RBRQ_ST + (group * 16));
	he_ग_लिखोl(he_dev, 0, G0_RBRQ_H + (group * 16));
	he_ग_लिखोl(he_dev,
		RBRQ_THRESH(CONFIG_RBRQ_THRESH) | RBRQ_SIZE(CONFIG_RBRQ_SIZE - 1),
						G0_RBRQ_Q + (group * 16));
	अगर (irq_coalesce) अणु
		hprपूर्णांकk("coalescing interrupts\n");
		he_ग_लिखोl(he_dev, RBRQ_TIME(768) | RBRQ_COUNT(7),
						G0_RBRQ_I + (group * 16));
	पूर्ण अन्यथा
		he_ग_लिखोl(he_dev, RBRQ_TIME(0) | RBRQ_COUNT(1),
						G0_RBRQ_I + (group * 16));

	/* tx buffer पढ़ोy queue */

	he_dev->tbrq_base = dma_alloc_coherent(&he_dev->pci_dev->dev,
					       CONFIG_TBRQ_SIZE * माप(काष्ठा he_tbrq),
					       &he_dev->tbrq_phys, GFP_KERNEL);
	अगर (he_dev->tbrq_base == शून्य) अणु
		hprपूर्णांकk("failed to allocate tbrq\n");
		जाओ out_मुक्त_rbpq_base;
	पूर्ण

	he_dev->tbrq_head = he_dev->tbrq_base;

	he_ग_लिखोl(he_dev, he_dev->tbrq_phys, G0_TBRQ_B_T + (group * 16));
	he_ग_लिखोl(he_dev, 0, G0_TBRQ_H + (group * 16));
	he_ग_लिखोl(he_dev, CONFIG_TBRQ_SIZE - 1, G0_TBRQ_S + (group * 16));
	he_ग_लिखोl(he_dev, CONFIG_TBRQ_THRESH, G0_TBRQ_THRESH + (group * 16));

	वापस 0;

out_मुक्त_rbpq_base:
	dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_RBRQ_SIZE *
			  माप(काष्ठा he_rbrq), he_dev->rbrq_base,
			  he_dev->rbrq_phys);
out_मुक्त_rbpl:
	list_क्रम_each_entry_safe(heb, next, &he_dev->rbpl_outstanding, entry)
		dma_pool_मुक्त(he_dev->rbpl_pool, heb, heb->mapping);

	dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_RBPL_SIZE *
			  माप(काष्ठा he_rbp), he_dev->rbpl_base,
			  he_dev->rbpl_phys);
out_destroy_rbpl_pool:
	dma_pool_destroy(he_dev->rbpl_pool);
out_मुक्त_rbpl_virt:
	kमुक्त(he_dev->rbpl_virt);
out_मुक्त_rbpl_table:
	kमुक्त(he_dev->rbpl_table);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक he_init_irq(काष्ठा he_dev *he_dev)
अणु
	पूर्णांक i;

	/* 2.9.3.5  tail offset क्रम each पूर्णांकerrupt queue is located after the
		    end of the पूर्णांकerrupt queue */

	he_dev->irq_base = dma_alloc_coherent(&he_dev->pci_dev->dev,
					      (CONFIG_IRQ_SIZE + 1) * माप(काष्ठा he_irq),
					      &he_dev->irq_phys, GFP_KERNEL);
	अगर (he_dev->irq_base == शून्य) अणु
		hprपूर्णांकk("failed to allocate irq\n");
		वापस -ENOMEM;
	पूर्ण
	he_dev->irq_tailoffset = (अचिन्हित *)
					&he_dev->irq_base[CONFIG_IRQ_SIZE];
	*he_dev->irq_tailoffset = 0;
	he_dev->irq_head = he_dev->irq_base;
	he_dev->irq_tail = he_dev->irq_base;

	क्रम (i = 0; i < CONFIG_IRQ_SIZE; ++i)
		he_dev->irq_base[i].isw = ITYPE_INVALID;

	he_ग_लिखोl(he_dev, he_dev->irq_phys, IRQ0_BASE);
	he_ग_लिखोl(he_dev,
		IRQ_SIZE(CONFIG_IRQ_SIZE) | IRQ_THRESH(CONFIG_IRQ_THRESH),
								IRQ0_HEAD);
	he_ग_लिखोl(he_dev, IRQ_INT_A | IRQ_TYPE_LINE, IRQ0_CNTL);
	he_ग_लिखोl(he_dev, 0x0, IRQ0_DATA);

	he_ग_लिखोl(he_dev, 0x0, IRQ1_BASE);
	he_ग_लिखोl(he_dev, 0x0, IRQ1_HEAD);
	he_ग_लिखोl(he_dev, 0x0, IRQ1_CNTL);
	he_ग_लिखोl(he_dev, 0x0, IRQ1_DATA);

	he_ग_लिखोl(he_dev, 0x0, IRQ2_BASE);
	he_ग_लिखोl(he_dev, 0x0, IRQ2_HEAD);
	he_ग_लिखोl(he_dev, 0x0, IRQ2_CNTL);
	he_ग_लिखोl(he_dev, 0x0, IRQ2_DATA);

	he_ग_लिखोl(he_dev, 0x0, IRQ3_BASE);
	he_ग_लिखोl(he_dev, 0x0, IRQ3_HEAD);
	he_ग_लिखोl(he_dev, 0x0, IRQ3_CNTL);
	he_ग_लिखोl(he_dev, 0x0, IRQ3_DATA);

	/* 2.9.3.2 पूर्णांकerrupt queue mapping रेजिस्टरs */

	he_ग_लिखोl(he_dev, 0x0, GRP_10_MAP);
	he_ग_लिखोl(he_dev, 0x0, GRP_32_MAP);
	he_ग_लिखोl(he_dev, 0x0, GRP_54_MAP);
	he_ग_लिखोl(he_dev, 0x0, GRP_76_MAP);

	अगर (request_irq(he_dev->pci_dev->irq,
			he_irq_handler, IRQF_SHARED, DEV_LABEL, he_dev)) अणु
		hprपूर्णांकk("irq %d already in use\n", he_dev->pci_dev->irq);
		वापस -EINVAL;
	पूर्ण   

	he_dev->irq = he_dev->pci_dev->irq;

	वापस 0;
पूर्ण

अटल पूर्णांक he_start(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा he_dev *he_dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ membase;

	u16 command;
	u32 gen_cntl_0, host_cntl, lb_swap;
	u8 cache_size, समयr;
	
	अचिन्हित err;
	अचिन्हित पूर्णांक status, reg;
	पूर्णांक i, group;

	he_dev = HE_DEV(dev);
	pci_dev = he_dev->pci_dev;

	membase = pci_resource_start(pci_dev, 0);
	HPRINTK("membase = 0x%lx  irq = %d.\n", membase, pci_dev->irq);

	/*
	 * pci bus controller initialization 
	 */

	/* 4.3 pci bus controller-specअगरic initialization */
	अगर (pci_पढ़ो_config_dword(pci_dev, GEN_CNTL_0, &gen_cntl_0) != 0) अणु
		hprपूर्णांकk("can't read GEN_CNTL_0\n");
		वापस -EINVAL;
	पूर्ण
	gen_cntl_0 |= (MRL_ENB | MRM_ENB | IGNORE_TIMEOUT);
	अगर (pci_ग_लिखो_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0) != 0) अणु
		hprपूर्णांकk("can't write GEN_CNTL_0.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pci_पढ़ो_config_word(pci_dev, PCI_COMMAND, &command) != 0) अणु
		hprपूर्णांकk("can't read PCI_COMMAND.\n");
		वापस -EINVAL;
	पूर्ण

	command |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE);
	अगर (pci_ग_लिखो_config_word(pci_dev, PCI_COMMAND, command) != 0) अणु
		hprपूर्णांकk("can't enable memory.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pci_पढ़ो_config_byte(pci_dev, PCI_CACHE_LINE_SIZE, &cache_size)) अणु
		hprपूर्णांकk("can't read cache line size?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cache_size < 16) अणु
		cache_size = 16;
		अगर (pci_ग_लिखो_config_byte(pci_dev, PCI_CACHE_LINE_SIZE, cache_size))
			hprपूर्णांकk("can't set cache line size to %d\n", cache_size);
	पूर्ण

	अगर (pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER, &समयr)) अणु
		hprपूर्णांकk("can't read latency timer?\n");
		वापस -EINVAL;
	पूर्ण

	/* from table 3.9
	 *
	 * LAT_TIMER = 1 + AVG_LAT + BURST_SIZE/BUS_SIZE
	 * 
	 * AVG_LAT: The average first data पढ़ो/ग_लिखो latency [maximum 16 घड़ी cycles]
	 * BURST_SIZE: 1536 bytes (पढ़ो) क्रम 622, 768 bytes (पढ़ो) क्रम 155 [192 घड़ी cycles]
	 *
	 */ 
#घोषणा LAT_TIMER 209
	अगर (समयr < LAT_TIMER) अणु
		HPRINTK("latency timer was %d, setting to %d\n", समयr, LAT_TIMER);
		समयr = LAT_TIMER;
		अगर (pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, समयr))
			hprपूर्णांकk("can't set latency timer to %d\n", समयr);
	पूर्ण

	अगर (!(he_dev->membase = ioremap(membase, HE_REGMAP_SIZE))) अणु
		hprपूर्णांकk("can't set up page mapping\n");
		वापस -EINVAL;
	पूर्ण

	/* 4.4 card reset */
	he_ग_लिखोl(he_dev, 0x0, RESET_CNTL);
	he_ग_लिखोl(he_dev, 0xff, RESET_CNTL);

	msleep(16);	/* 16 ms */
	status = he_पढ़ोl(he_dev, RESET_CNTL);
	अगर ((status & BOARD_RST_STATUS) == 0) अणु
		hprपूर्णांकk("reset failed\n");
		वापस -EINVAL;
	पूर्ण

	/* 4.5 set bus width */
	host_cntl = he_पढ़ोl(he_dev, HOST_CNTL);
	अगर (host_cntl & PCI_BUS_SIZE64)
		gen_cntl_0 |= ENBL_64;
	अन्यथा
		gen_cntl_0 &= ~ENBL_64;

	अगर (disable64 == 1) अणु
		hprपूर्णांकk("disabling 64-bit pci bus transfers\n");
		gen_cntl_0 &= ~ENBL_64;
	पूर्ण

	अगर (gen_cntl_0 & ENBL_64)
		hprपूर्णांकk("64-bit transfers enabled\n");

	pci_ग_लिखो_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0);

	/* 4.7 पढ़ो prom contents */
	क्रम (i = 0; i < PROD_ID_LEN; ++i)
		he_dev->prod_id[i] = पढ़ो_prom_byte(he_dev, PROD_ID + i);

	he_dev->media = पढ़ो_prom_byte(he_dev, MEDIA);

	क्रम (i = 0; i < 6; ++i)
		dev->esi[i] = पढ़ो_prom_byte(he_dev, MAC_ADDR + i);

	hprपूर्णांकk("%s%s, %pM\n", he_dev->prod_id,
		he_dev->media & 0x40 ? "SM" : "MM", dev->esi);
	he_dev->aपंचांग_dev->link_rate = he_is622(he_dev) ?
						ATM_OC12_PCR : ATM_OC3_PCR;

	/* 4.6 set host endianess */
	lb_swap = he_पढ़ोl(he_dev, LB_SWAP);
	अगर (he_is622(he_dev))
		lb_swap &= ~XFER_SIZE;		/* 4 cells */
	अन्यथा
		lb_swap |= XFER_SIZE;		/* 8 cells */
#अगर_घोषित __BIG_ENDIAN
	lb_swap |= DESC_WR_SWAP | INTR_SWAP | BIG_ENDIAN_HOST;
#अन्यथा
	lb_swap &= ~(DESC_WR_SWAP | INTR_SWAP | BIG_ENDIAN_HOST |
			DATA_WR_SWAP | DATA_RD_SWAP | DESC_RD_SWAP);
#पूर्ण_अगर /* __BIG_ENDIAN */
	he_ग_लिखोl(he_dev, lb_swap, LB_SWAP);

	/* 4.8 sdram controller initialization */
	he_ग_लिखोl(he_dev, he_is622(he_dev) ? LB_64_ENB : 0x0, SDRAM_CTL);

	/* 4.9 initialize rnum value */
	lb_swap |= SWAP_RNUM_MAX(0xf);
	he_ग_लिखोl(he_dev, lb_swap, LB_SWAP);

	/* 4.10 initialize the पूर्णांकerrupt queues */
	अगर ((err = he_init_irq(he_dev)) != 0)
		वापस err;

	/* 4.11 enable pci bus controller state machines */
	host_cntl |= (OUTFF_ENB | CMDFF_ENB |
				QUICK_RD_RETRY | QUICK_WR_RETRY | PERR_INT_ENB);
	he_ग_लिखोl(he_dev, host_cntl, HOST_CNTL);

	gen_cntl_0 |= INT_PROC_ENBL|INIT_ENB;
	pci_ग_लिखो_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0);

	/*
	 * aपंचांग network controller initialization
	 */

	/* 5.1.1 generic configuration state */

	/*
	 *		local (cell) buffer memory map
	 *                    
	 *             HE155                          HE622
	 *                                                      
	 *        0 ____________1023 bytes  0 _______________________2047 bytes
	 *         |            |            |                   |   |
	 *         |  utility   |            |        rx0        |   |
	 *        5|____________|         255|___________________| u |
	 *        6|            |         256|                   | t |
	 *         |            |            |                   | i |
	 *         |    rx0     |     row    |        tx         | l |
	 *         |            |            |                   | i |
	 *         |            |         767|___________________| t |
	 *      517|____________|         768|                   | y |
	 * row  518|            |            |        rx1        |   |
	 *         |            |        1023|___________________|___|
	 *         |            |
	 *         |    tx      |
	 *         |            |
	 *         |            |
	 *     1535|____________|
	 *     1536|            |
	 *         |    rx1     |
	 *     2047|____________|
	 *
	 */

	/* total 4096 connections */
	he_dev->vcibits = CONFIG_DEFAULT_VCIBITS;
	he_dev->vpibits = CONFIG_DEFAULT_VPIBITS;

	अगर (nvpibits != -1 && nvcibits != -1 && nvpibits+nvcibits != HE_MAXCIDBITS) अणु
		hprपूर्णांकk("nvpibits + nvcibits != %d\n", HE_MAXCIDBITS);
		वापस -ENODEV;
	पूर्ण

	अगर (nvpibits != -1) अणु
		he_dev->vpibits = nvpibits;
		he_dev->vcibits = HE_MAXCIDBITS - nvpibits;
	पूर्ण

	अगर (nvcibits != -1) अणु
		he_dev->vcibits = nvcibits;
		he_dev->vpibits = HE_MAXCIDBITS - nvcibits;
	पूर्ण


	अगर (he_is622(he_dev)) अणु
		he_dev->cells_per_row = 40;
		he_dev->bytes_per_row = 2048;
		he_dev->r0_numrows = 256;
		he_dev->tx_numrows = 512;
		he_dev->r1_numrows = 256;
		he_dev->r0_startrow = 0;
		he_dev->tx_startrow = 256;
		he_dev->r1_startrow = 768;
	पूर्ण अन्यथा अणु
		he_dev->cells_per_row = 20;
		he_dev->bytes_per_row = 1024;
		he_dev->r0_numrows = 512;
		he_dev->tx_numrows = 1018;
		he_dev->r1_numrows = 512;
		he_dev->r0_startrow = 6;
		he_dev->tx_startrow = 518;
		he_dev->r1_startrow = 1536;
	पूर्ण

	he_dev->cells_per_lbuf = 4;
	he_dev->buffer_limit = 4;
	he_dev->r0_numbuffs = he_dev->r0_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अगर (he_dev->r0_numbuffs > 2560)
		he_dev->r0_numbuffs = 2560;

	he_dev->r1_numbuffs = he_dev->r1_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अगर (he_dev->r1_numbuffs > 2560)
		he_dev->r1_numbuffs = 2560;

	he_dev->tx_numbuffs = he_dev->tx_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	अगर (he_dev->tx_numbuffs > 5120)
		he_dev->tx_numbuffs = 5120;

	/* 5.1.2 configure hardware dependent रेजिस्टरs */

	he_ग_लिखोl(he_dev, 
		SLICE_X(0x2) | ARB_RNUM_MAX(0xf) | TH_PRTY(0x3) |
		RH_PRTY(0x3) | TL_PRTY(0x2) | RL_PRTY(0x1) |
		(he_is622(he_dev) ? BUS_MULTI(0x28) : BUS_MULTI(0x46)) |
		(he_is622(he_dev) ? NET_PREF(0x50) : NET_PREF(0x8c)),
								LBARB);

	he_ग_लिखोl(he_dev, BANK_ON |
		(he_is622(he_dev) ? (REF_RATE(0x384) | WIDE_DATA) : REF_RATE(0x150)),
								SDRAMCON);

	he_ग_लिखोl(he_dev,
		(he_is622(he_dev) ? RM_BANK_WAIT(1) : RM_BANK_WAIT(0)) |
						RM_RW_WAIT(1), RCMCONFIG);
	he_ग_लिखोl(he_dev,
		(he_is622(he_dev) ? TM_BANK_WAIT(2) : TM_BANK_WAIT(1)) |
						TM_RW_WAIT(1), TCMCONFIG);

	he_ग_लिखोl(he_dev, he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD, LB_CONFIG);

	he_ग_लिखोl(he_dev, 
		(he_is622(he_dev) ? UT_RD_DELAY(8) : UT_RD_DELAY(0)) |
		(he_is622(he_dev) ? RC_UT_MODE(0) : RC_UT_MODE(1)) |
		RX_VALVP(he_dev->vpibits) |
		RX_VALVC(he_dev->vcibits),			 RC_CONFIG);

	he_ग_लिखोl(he_dev, DRF_THRESH(0x20) |
		(he_is622(he_dev) ? TX_UT_MODE(0) : TX_UT_MODE(1)) |
		TX_VCI_MASK(he_dev->vcibits) |
		LBFREE_CNT(he_dev->tx_numbuffs), 		TX_CONFIG);

	he_ग_लिखोl(he_dev, 0x0, TXAAL5_PROTO);

	he_ग_लिखोl(he_dev, PHY_INT_ENB |
		(he_is622(he_dev) ? PTMR_PRE(67 - 1) : PTMR_PRE(50 - 1)),
								RH_CONFIG);

	/* 5.1.3 initialize connection memory */

	क्रम (i = 0; i < TCM_MEM_SIZE; ++i)
		he_ग_लिखोl_tcm(he_dev, 0, i);

	क्रम (i = 0; i < RCM_MEM_SIZE; ++i)
		he_ग_लिखोl_rcm(he_dev, 0, i);

	/*
	 *	transmit connection memory map
	 *
	 *                  tx memory
	 *          0x0 ___________________
	 *             |                   |
	 *             |                   |
	 *             |       TSRa        |
	 *             |                   |
	 *             |                   |
	 *       0x8000|___________________|
	 *             |                   |
	 *             |       TSRb        |
	 *       0xc000|___________________|
	 *             |                   |
	 *             |       TSRc        |
	 *       0xe000|___________________|
	 *             |       TSRd        |
	 *       0xf000|___________________|
	 *             |       पंचांगABR       |
	 *      0x10000|___________________|
	 *             |                   |
	 *             |       पंचांगTPD       |
	 *             |___________________|
	 *             |                   |
	 *                      ....
	 *      0x1ffff|___________________|
	 *
	 *
	 */

	he_ग_लिखोl(he_dev, CONFIG_TSRB, TSRB_BA);
	he_ग_लिखोl(he_dev, CONFIG_TSRC, TSRC_BA);
	he_ग_लिखोl(he_dev, CONFIG_TSRD, TSRD_BA);
	he_ग_लिखोl(he_dev, CONFIG_TMABR, TMABR_BA);
	he_ग_लिखोl(he_dev, CONFIG_TPDBA, TPD_BA);


	/*
	 *	receive connection memory map
	 *
	 *          0x0 ___________________
	 *             |                   |
	 *             |                   |
	 *             |       RSRa        |
	 *             |                   |
	 *             |                   |
	 *       0x8000|___________________|
	 *             |                   |
	 *             |             rx0/1 |
	 *             |       LBM         |   link lists of local
	 *             |             tx    |   buffer memory 
	 *             |                   |
	 *       0xd000|___________________|
	 *             |                   |
	 *             |      rmABR        |
	 *       0xe000|___________________|
	 *             |                   |
	 *             |       RSRb        |
	 *             |___________________|
	 *             |                   |
	 *                      ....
	 *       0xffff|___________________|
	 */

	he_ग_लिखोl(he_dev, 0x08000, RCMLBM_BA);
	he_ग_लिखोl(he_dev, 0x0e000, RCMRSRB_BA);
	he_ग_लिखोl(he_dev, 0x0d800, RCMABR_BA);

	/* 5.1.4 initialize local buffer मुक्त pools linked lists */

	he_init_rx_lbfp0(he_dev);
	he_init_rx_lbfp1(he_dev);

	he_ग_लिखोl(he_dev, 0x0, RLBC_H);
	he_ग_लिखोl(he_dev, 0x0, RLBC_T);
	he_ग_लिखोl(he_dev, 0x0, RLBC_H2);

	he_ग_लिखोl(he_dev, 512, RXTHRSH);	/* 10% of r0+r1 buffers */
	he_ग_लिखोl(he_dev, 256, LITHRSH); 	/* 5% of r0+r1 buffers */

	he_init_tx_lbfp(he_dev);

	he_ग_लिखोl(he_dev, he_is622(he_dev) ? 0x104780 : 0x800, UBUFF_BA);

	/* 5.1.5 initialize पूर्णांकermediate receive queues */

	अगर (he_is622(he_dev)) अणु
		he_ग_लिखोl(he_dev, 0x000f, G0_INMQ_S);
		he_ग_लिखोl(he_dev, 0x200f, G0_INMQ_L);

		he_ग_लिखोl(he_dev, 0x001f, G1_INMQ_S);
		he_ग_लिखोl(he_dev, 0x201f, G1_INMQ_L);

		he_ग_लिखोl(he_dev, 0x002f, G2_INMQ_S);
		he_ग_लिखोl(he_dev, 0x202f, G2_INMQ_L);

		he_ग_लिखोl(he_dev, 0x003f, G3_INMQ_S);
		he_ग_लिखोl(he_dev, 0x203f, G3_INMQ_L);

		he_ग_लिखोl(he_dev, 0x004f, G4_INMQ_S);
		he_ग_लिखोl(he_dev, 0x204f, G4_INMQ_L);

		he_ग_लिखोl(he_dev, 0x005f, G5_INMQ_S);
		he_ग_लिखोl(he_dev, 0x205f, G5_INMQ_L);

		he_ग_लिखोl(he_dev, 0x006f, G6_INMQ_S);
		he_ग_लिखोl(he_dev, 0x206f, G6_INMQ_L);

		he_ग_लिखोl(he_dev, 0x007f, G7_INMQ_S);
		he_ग_लिखोl(he_dev, 0x207f, G7_INMQ_L);
	पूर्ण अन्यथा अणु
		he_ग_लिखोl(he_dev, 0x0000, G0_INMQ_S);
		he_ग_लिखोl(he_dev, 0x0008, G0_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0001, G1_INMQ_S);
		he_ग_लिखोl(he_dev, 0x0009, G1_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0002, G2_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000a, G2_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0003, G3_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000b, G3_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0004, G4_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000c, G4_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0005, G5_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000d, G5_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0006, G6_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000e, G6_INMQ_L);

		he_ग_लिखोl(he_dev, 0x0007, G7_INMQ_S);
		he_ग_लिखोl(he_dev, 0x000f, G7_INMQ_L);
	पूर्ण

	/* 5.1.6 application tunable parameters */

	he_ग_लिखोl(he_dev, 0x0, MCC);
	he_ग_लिखोl(he_dev, 0x0, OEC);
	he_ग_लिखोl(he_dev, 0x0, DCC);
	he_ग_लिखोl(he_dev, 0x0, CEC);
	
	/* 5.1.7 cs block initialization */

	he_init_cs_block(he_dev);

	/* 5.1.8 cs block connection memory initialization */
	
	अगर (he_init_cs_block_rcm(he_dev) < 0)
		वापस -ENOMEM;

	/* 5.1.10 initialize host काष्ठाures */

	he_init_tpdrq(he_dev);

	he_dev->tpd_pool = dma_pool_create("tpd", &he_dev->pci_dev->dev,
					   माप(काष्ठा he_tpd), TPD_ALIGNMENT, 0);
	अगर (he_dev->tpd_pool == शून्य) अणु
		hprपूर्णांकk("unable to create tpd dma_pool\n");
		वापस -ENOMEM;         
	पूर्ण

	INIT_LIST_HEAD(&he_dev->outstanding_tpds);

	अगर (he_init_group(he_dev, 0) != 0)
		वापस -ENOMEM;

	क्रम (group = 1; group < HE_NUM_GROUPS; ++group) अणु
		he_ग_लिखोl(he_dev, 0x0, G0_RBPS_S + (group * 32));
		he_ग_लिखोl(he_dev, 0x0, G0_RBPS_T + (group * 32));
		he_ग_लिखोl(he_dev, 0x0, G0_RBPS_QI + (group * 32));
		he_ग_लिखोl(he_dev, RBP_THRESH(0x1) | RBP_QSIZE(0x0),
						G0_RBPS_BS + (group * 32));

		he_ग_लिखोl(he_dev, 0x0, G0_RBPL_S + (group * 32));
		he_ग_लिखोl(he_dev, 0x0, G0_RBPL_T + (group * 32));
		he_ग_लिखोl(he_dev, RBP_THRESH(0x1) | RBP_QSIZE(0x0),
						G0_RBPL_QI + (group * 32));
		he_ग_लिखोl(he_dev, 0x0, G0_RBPL_BS + (group * 32));

		he_ग_लिखोl(he_dev, 0x0, G0_RBRQ_ST + (group * 16));
		he_ग_लिखोl(he_dev, 0x0, G0_RBRQ_H + (group * 16));
		he_ग_लिखोl(he_dev, RBRQ_THRESH(0x1) | RBRQ_SIZE(0x0),
						G0_RBRQ_Q + (group * 16));
		he_ग_लिखोl(he_dev, 0x0, G0_RBRQ_I + (group * 16));

		he_ग_लिखोl(he_dev, 0x0, G0_TBRQ_B_T + (group * 16));
		he_ग_लिखोl(he_dev, 0x0, G0_TBRQ_H + (group * 16));
		he_ग_लिखोl(he_dev, TBRQ_THRESH(0x1),
						G0_TBRQ_THRESH + (group * 16));
		he_ग_लिखोl(he_dev, 0x0, G0_TBRQ_S + (group * 16));
	पूर्ण

	/* host status page */

	he_dev->hsp = dma_alloc_coherent(&he_dev->pci_dev->dev,
					 माप(काष्ठा he_hsp),
					 &he_dev->hsp_phys, GFP_KERNEL);
	अगर (he_dev->hsp == शून्य) अणु
		hprपूर्णांकk("failed to allocate host status page\n");
		वापस -ENOMEM;
	पूर्ण
	he_ग_लिखोl(he_dev, he_dev->hsp_phys, HSP_BA);

	/* initialize framer */

#अगर_घोषित CONFIG_ATM_HE_USE_SUNI
	अगर (he_isMM(he_dev))
		suni_init(he_dev->aपंचांग_dev);
	अगर (he_dev->aपंचांग_dev->phy && he_dev->aपंचांग_dev->phy->start)
		he_dev->aपंचांग_dev->phy->start(he_dev->aपंचांग_dev);
#पूर्ण_अगर /* CONFIG_ATM_HE_USE_SUNI */

	अगर (sdh) अणु
		/* this really should be in suni.c but क्रम now... */
		पूर्णांक val;

		val = he_phy_get(he_dev->aपंचांग_dev, SUNI_TPOP_APM);
		val = (val & ~SUNI_TPOP_APM_S) | (SUNI_TPOP_S_SDH << SUNI_TPOP_APM_S_SHIFT);
		he_phy_put(he_dev->aपंचांग_dev, val, SUNI_TPOP_APM);
		he_phy_put(he_dev->aपंचांग_dev, SUNI_TACP_IUCHP_CLP, SUNI_TACP_IUCHP);
	पूर्ण

	/* 5.1.12 enable transmit and receive */

	reg = he_पढ़ोl_mbox(he_dev, CS_ERCTL0);
	reg |= TX_ENABLE|ER_ENABLE;
	he_ग_लिखोl_mbox(he_dev, reg, CS_ERCTL0);

	reg = he_पढ़ोl(he_dev, RC_CONFIG);
	reg |= RX_ENABLE;
	he_ग_लिखोl(he_dev, reg, RC_CONFIG);

	क्रम (i = 0; i < HE_NUM_CS_STPER; ++i) अणु
		he_dev->cs_stper[i].inuse = 0;
		he_dev->cs_stper[i].pcr = -1;
	पूर्ण
	he_dev->total_bw = 0;


	/* aपंचांग linux initialization */

	he_dev->aपंचांग_dev->ci_range.vpi_bits = he_dev->vpibits;
	he_dev->aपंचांग_dev->ci_range.vci_bits = he_dev->vcibits;

	he_dev->irq_peak = 0;
	he_dev->rbrq_peak = 0;
	he_dev->rbpl_peak = 0;
	he_dev->tbrq_peak = 0;

	HPRINTK("hell bent for leather!\n");

	वापस 0;
पूर्ण

अटल व्योम
he_stop(काष्ठा he_dev *he_dev)
अणु
	काष्ठा he_buff *heb, *next;
	काष्ठा pci_dev *pci_dev;
	u32 gen_cntl_0, reg;
	u16 command;

	pci_dev = he_dev->pci_dev;

	/* disable पूर्णांकerrupts */

	अगर (he_dev->membase) अणु
		pci_पढ़ो_config_dword(pci_dev, GEN_CNTL_0, &gen_cntl_0);
		gen_cntl_0 &= ~(INT_PROC_ENBL | INIT_ENB);
		pci_ग_लिखो_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0);

		tasklet_disable(&he_dev->tasklet);

		/* disable recv and transmit */

		reg = he_पढ़ोl_mbox(he_dev, CS_ERCTL0);
		reg &= ~(TX_ENABLE|ER_ENABLE);
		he_ग_लिखोl_mbox(he_dev, reg, CS_ERCTL0);

		reg = he_पढ़ोl(he_dev, RC_CONFIG);
		reg &= ~(RX_ENABLE);
		he_ग_लिखोl(he_dev, reg, RC_CONFIG);
	पूर्ण

#अगर_घोषित CONFIG_ATM_HE_USE_SUNI
	अगर (he_dev->aपंचांग_dev->phy && he_dev->aपंचांग_dev->phy->stop)
		he_dev->aपंचांग_dev->phy->stop(he_dev->aपंचांग_dev);
#पूर्ण_अगर /* CONFIG_ATM_HE_USE_SUNI */

	अगर (he_dev->irq)
		मुक्त_irq(he_dev->irq, he_dev);

	अगर (he_dev->irq_base)
		dma_मुक्त_coherent(&he_dev->pci_dev->dev, (CONFIG_IRQ_SIZE + 1)
				  * माप(काष्ठा he_irq), he_dev->irq_base, he_dev->irq_phys);

	अगर (he_dev->hsp)
		dma_मुक्त_coherent(&he_dev->pci_dev->dev, माप(काष्ठा he_hsp),
				  he_dev->hsp, he_dev->hsp_phys);

	अगर (he_dev->rbpl_base) अणु
		list_क्रम_each_entry_safe(heb, next, &he_dev->rbpl_outstanding, entry)
			dma_pool_मुक्त(he_dev->rbpl_pool, heb, heb->mapping);

		dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_RBPL_SIZE
				  * माप(काष्ठा he_rbp), he_dev->rbpl_base, he_dev->rbpl_phys);
	पूर्ण

	kमुक्त(he_dev->rbpl_virt);
	kमुक्त(he_dev->rbpl_table);
	dma_pool_destroy(he_dev->rbpl_pool);

	अगर (he_dev->rbrq_base)
		dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_RBRQ_SIZE * माप(काष्ठा he_rbrq),
				  he_dev->rbrq_base, he_dev->rbrq_phys);

	अगर (he_dev->tbrq_base)
		dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_TBRQ_SIZE * माप(काष्ठा he_tbrq),
				  he_dev->tbrq_base, he_dev->tbrq_phys);

	अगर (he_dev->tpdrq_base)
		dma_मुक्त_coherent(&he_dev->pci_dev->dev, CONFIG_TBRQ_SIZE * माप(काष्ठा he_tbrq),
				  he_dev->tpdrq_base, he_dev->tpdrq_phys);

	dma_pool_destroy(he_dev->tpd_pool);

	अगर (he_dev->pci_dev) अणु
		pci_पढ़ो_config_word(he_dev->pci_dev, PCI_COMMAND, &command);
		command &= ~(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
		pci_ग_लिखो_config_word(he_dev->pci_dev, PCI_COMMAND, command);
	पूर्ण
	
	अगर (he_dev->membase)
		iounmap(he_dev->membase);
पूर्ण

अटल काष्ठा he_tpd *
__alloc_tpd(काष्ठा he_dev *he_dev)
अणु
	काष्ठा he_tpd *tpd;
	dma_addr_t mapping;

	tpd = dma_pool_alloc(he_dev->tpd_pool, GFP_ATOMIC, &mapping);
	अगर (tpd == शून्य)
		वापस शून्य;
			
	tpd->status = TPD_ADDR(mapping);
	tpd->reserved = 0; 
	tpd->iovec[0].addr = 0; tpd->iovec[0].len = 0;
	tpd->iovec[1].addr = 0; tpd->iovec[1].len = 0;
	tpd->iovec[2].addr = 0; tpd->iovec[2].len = 0;

	वापस tpd;
पूर्ण

#घोषणा AAL5_LEN(buf,len) 						\
			((((अचिन्हित अक्षर *)(buf))[(len)-6] << 8) |	\
				(((अचिन्हित अक्षर *)(buf))[(len)-5]))

/* 2.10.1.2 receive
 *
 * aal5 packets can optionally वापस the tcp checksum in the lower
 * 16 bits of the crc (RSR0_TCP_CKSUM)
 */

#घोषणा TCP_CKSUM(buf,len) 						\
			((((अचिन्हित अक्षर *)(buf))[(len)-2] << 8) |	\
				(((अचिन्हित अक्षर *)(buf))[(len-1)]))

अटल पूर्णांक
he_service_rbrq(काष्ठा he_dev *he_dev, पूर्णांक group)
अणु
	काष्ठा he_rbrq *rbrq_tail = (काष्ठा he_rbrq *)
				((अचिन्हित दीर्घ)he_dev->rbrq_base |
					he_dev->hsp->group[group].rbrq_tail);
	अचिन्हित cid, lastcid = -1;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांग_vcc *vcc = शून्य;
	काष्ठा he_vcc *he_vcc;
	काष्ठा he_buff *heb, *next;
	पूर्णांक i;
	पूर्णांक pdus_assembled = 0;
	पूर्णांक updated = 0;

	पढ़ो_lock(&vcc_sklist_lock);
	जबतक (he_dev->rbrq_head != rbrq_tail) अणु
		++updated;

		HPRINTK("%p rbrq%d 0x%x len=%d cid=0x%x %s%s%s%s%s%s\n",
			he_dev->rbrq_head, group,
			RBRQ_ADDR(he_dev->rbrq_head),
			RBRQ_BUFLEN(he_dev->rbrq_head),
			RBRQ_CID(he_dev->rbrq_head),
			RBRQ_CRC_ERR(he_dev->rbrq_head) ? " CRC_ERR" : "",
			RBRQ_LEN_ERR(he_dev->rbrq_head) ? " LEN_ERR" : "",
			RBRQ_END_PDU(he_dev->rbrq_head) ? " END_PDU" : "",
			RBRQ_AAL5_PROT(he_dev->rbrq_head) ? " AAL5_PROT" : "",
			RBRQ_CON_CLOSED(he_dev->rbrq_head) ? " CON_CLOSED" : "",
			RBRQ_HBUF_ERR(he_dev->rbrq_head) ? " HBUF_ERR" : "");

		i = RBRQ_ADDR(he_dev->rbrq_head) >> RBP_IDX_OFFSET;
		heb = he_dev->rbpl_virt[i];

		cid = RBRQ_CID(he_dev->rbrq_head);
		अगर (cid != lastcid)
			vcc = __find_vcc(he_dev, cid);
		lastcid = cid;

		अगर (vcc == शून्य || (he_vcc = HE_VCC(vcc)) == शून्य) अणु
			hprपूर्णांकk("vcc/he_vcc == NULL  (cid 0x%x)\n", cid);
			अगर (!RBRQ_HBUF_ERR(he_dev->rbrq_head)) अणु
				clear_bit(i, he_dev->rbpl_table);
				list_del(&heb->entry);
				dma_pool_मुक्त(he_dev->rbpl_pool, heb, heb->mapping);
			पूर्ण
					
			जाओ next_rbrq_entry;
		पूर्ण

		अगर (RBRQ_HBUF_ERR(he_dev->rbrq_head)) अणु
			hprपूर्णांकk("HBUF_ERR!  (cid 0x%x)\n", cid);
			atomic_inc(&vcc->stats->rx_drop);
			जाओ वापस_host_buffers;
		पूर्ण

		heb->len = RBRQ_BUFLEN(he_dev->rbrq_head) * 4;
		clear_bit(i, he_dev->rbpl_table);
		list_move_tail(&heb->entry, &he_vcc->buffers);
		he_vcc->pdu_len += heb->len;

		अगर (RBRQ_CON_CLOSED(he_dev->rbrq_head)) अणु
			lastcid = -1;
			HPRINTK("wake_up rx_waitq  (cid 0x%x)\n", cid);
			wake_up(&he_vcc->rx_रुकोq);
			जाओ वापस_host_buffers;
		पूर्ण

		अगर (!RBRQ_END_PDU(he_dev->rbrq_head))
			जाओ next_rbrq_entry;

		अगर (RBRQ_LEN_ERR(he_dev->rbrq_head)
				|| RBRQ_CRC_ERR(he_dev->rbrq_head)) अणु
			HPRINTK("%s%s (%d.%d)\n",
				RBRQ_CRC_ERR(he_dev->rbrq_head)
							? "CRC_ERR " : "",
				RBRQ_LEN_ERR(he_dev->rbrq_head)
							? "LEN_ERR" : "",
							vcc->vpi, vcc->vci);
			atomic_inc(&vcc->stats->rx_err);
			जाओ वापस_host_buffers;
		पूर्ण

		skb = aपंचांग_alloc_अक्षरge(vcc, he_vcc->pdu_len + rx_skb_reserve,
							GFP_ATOMIC);
		अगर (!skb) अणु
			HPRINTK("charge failed (%d.%d)\n", vcc->vpi, vcc->vci);
			जाओ वापस_host_buffers;
		पूर्ण

		अगर (rx_skb_reserve > 0)
			skb_reserve(skb, rx_skb_reserve);

		__net_बारtamp(skb);

		list_क्रम_each_entry(heb, &he_vcc->buffers, entry)
			skb_put_data(skb, &heb->data, heb->len);

		चयन (vcc->qos.aal) अणु
			हाल ATM_AAL0:
				/* 2.10.1.5 raw cell receive */
				skb->len = ATM_AAL0_SDU;
				skb_set_tail_poपूर्णांकer(skb, skb->len);
				अवरोध;
			हाल ATM_AAL5:
				/* 2.10.1.2 aal5 receive */

				skb->len = AAL5_LEN(skb->data, he_vcc->pdu_len);
				skb_set_tail_poपूर्णांकer(skb, skb->len);
#अगर_घोषित USE_CHECKSUM_HW
				अगर (vcc->vpi == 0 && vcc->vci >= ATM_NOT_RSV_VCI) अणु
					skb->ip_summed = CHECKSUM_COMPLETE;
					skb->csum = TCP_CKSUM(skb->data,
							he_vcc->pdu_len);
				पूर्ण
#पूर्ण_अगर
				अवरोध;
		पूर्ण

#अगर_घोषित should_never_happen
		अगर (skb->len > vcc->qos.rxtp.max_sdu)
			hprपूर्णांकk("pdu_len (%d) > vcc->qos.rxtp.max_sdu (%d)!  cid 0x%x\n", skb->len, vcc->qos.rxtp.max_sdu, cid);
#पूर्ण_अगर

#अगर_घोषित notdef
		ATM_SKB(skb)->vcc = vcc;
#पूर्ण_अगर
		spin_unlock(&he_dev->global_lock);
		vcc->push(vcc, skb);
		spin_lock(&he_dev->global_lock);

		atomic_inc(&vcc->stats->rx);

वापस_host_buffers:
		++pdus_assembled;

		list_क्रम_each_entry_safe(heb, next, &he_vcc->buffers, entry)
			dma_pool_मुक्त(he_dev->rbpl_pool, heb, heb->mapping);
		INIT_LIST_HEAD(&he_vcc->buffers);
		he_vcc->pdu_len = 0;

next_rbrq_entry:
		he_dev->rbrq_head = (काष्ठा he_rbrq *)
				((अचिन्हित दीर्घ) he_dev->rbrq_base |
					RBRQ_MASK(he_dev->rbrq_head + 1));

	पूर्ण
	पढ़ो_unlock(&vcc_sklist_lock);

	अगर (updated) अणु
		अगर (updated > he_dev->rbrq_peak)
			he_dev->rbrq_peak = updated;

		he_ग_लिखोl(he_dev, RBRQ_MASK(he_dev->rbrq_head),
						G0_RBRQ_H + (group * 16));
	पूर्ण

	वापस pdus_assembled;
पूर्ण

अटल व्योम
he_service_tbrq(काष्ठा he_dev *he_dev, पूर्णांक group)
अणु
	काष्ठा he_tbrq *tbrq_tail = (काष्ठा he_tbrq *)
				((अचिन्हित दीर्घ)he_dev->tbrq_base |
					he_dev->hsp->group[group].tbrq_tail);
	काष्ठा he_tpd *tpd;
	पूर्णांक slot, updated = 0;
	काष्ठा he_tpd *__tpd;

	/* 2.1.6 transmit buffer वापस queue */

	जबतक (he_dev->tbrq_head != tbrq_tail) अणु
		++updated;

		HPRINTK("tbrq%d 0x%x%s%s\n",
			group,
			TBRQ_TPD(he_dev->tbrq_head), 
			TBRQ_EOS(he_dev->tbrq_head) ? " EOS" : "",
			TBRQ_MULTIPLE(he_dev->tbrq_head) ? " MULTIPLE" : "");
		tpd = शून्य;
		list_क्रम_each_entry(__tpd, &he_dev->outstanding_tpds, entry) अणु
			अगर (TPD_ADDR(__tpd->status) == TBRQ_TPD(he_dev->tbrq_head)) अणु
				tpd = __tpd;
				list_del(&__tpd->entry);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (tpd == शून्य) अणु
			hprपूर्णांकk("unable to locate tpd for dma buffer %x\n",
						TBRQ_TPD(he_dev->tbrq_head));
			जाओ next_tbrq_entry;
		पूर्ण

		अगर (TBRQ_EOS(he_dev->tbrq_head)) अणु
			HPRINTK("wake_up(tx_waitq) cid 0x%x\n",
				he_mkcid(he_dev, tpd->vcc->vpi, tpd->vcc->vci));
			अगर (tpd->vcc)
				wake_up(&HE_VCC(tpd->vcc)->tx_रुकोq);

			जाओ next_tbrq_entry;
		पूर्ण

		क्रम (slot = 0; slot < TPD_MAXIOV; ++slot) अणु
			अगर (tpd->iovec[slot].addr)
				dma_unmap_single(&he_dev->pci_dev->dev,
					tpd->iovec[slot].addr,
					tpd->iovec[slot].len & TPD_LEN_MASK,
							DMA_TO_DEVICE);
			अगर (tpd->iovec[slot].len & TPD_LST)
				अवरोध;
				
		पूर्ण

		अगर (tpd->skb) अणु	/* && !TBRQ_MULTIPLE(he_dev->tbrq_head) */
			अगर (tpd->vcc && tpd->vcc->pop)
				tpd->vcc->pop(tpd->vcc, tpd->skb);
			अन्यथा
				dev_kमुक्त_skb_any(tpd->skb);
		पूर्ण

next_tbrq_entry:
		अगर (tpd)
			dma_pool_मुक्त(he_dev->tpd_pool, tpd, TPD_ADDR(tpd->status));
		he_dev->tbrq_head = (काष्ठा he_tbrq *)
				((अचिन्हित दीर्घ) he_dev->tbrq_base |
					TBRQ_MASK(he_dev->tbrq_head + 1));
	पूर्ण

	अगर (updated) अणु
		अगर (updated > he_dev->tbrq_peak)
			he_dev->tbrq_peak = updated;

		he_ग_लिखोl(he_dev, TBRQ_MASK(he_dev->tbrq_head),
						G0_TBRQ_H + (group * 16));
	पूर्ण
पूर्ण

अटल व्योम
he_service_rbpl(काष्ठा he_dev *he_dev, पूर्णांक group)
अणु
	काष्ठा he_rbp *new_tail;
	काष्ठा he_rbp *rbpl_head;
	काष्ठा he_buff *heb;
	dma_addr_t mapping;
	पूर्णांक i;
	पूर्णांक moved = 0;

	rbpl_head = (काष्ठा he_rbp *) ((अचिन्हित दीर्घ)he_dev->rbpl_base |
					RBPL_MASK(he_पढ़ोl(he_dev, G0_RBPL_S)));

	क्रम (;;) अणु
		new_tail = (काष्ठा he_rbp *) ((अचिन्हित दीर्घ)he_dev->rbpl_base |
						RBPL_MASK(he_dev->rbpl_tail+1));

		/* table 3.42 -- rbpl_tail should never be set to rbpl_head */
		अगर (new_tail == rbpl_head)
			अवरोध;

		i = find_next_zero_bit(he_dev->rbpl_table, RBPL_TABLE_SIZE, he_dev->rbpl_hपूर्णांक);
		अगर (i > (RBPL_TABLE_SIZE - 1)) अणु
			i = find_first_zero_bit(he_dev->rbpl_table, RBPL_TABLE_SIZE);
			अगर (i > (RBPL_TABLE_SIZE - 1))
				अवरोध;
		पूर्ण
		he_dev->rbpl_hपूर्णांक = i + 1;

		heb = dma_pool_alloc(he_dev->rbpl_pool, GFP_ATOMIC, &mapping);
		अगर (!heb)
			अवरोध;
		heb->mapping = mapping;
		list_add(&heb->entry, &he_dev->rbpl_outstanding);
		he_dev->rbpl_virt[i] = heb;
		set_bit(i, he_dev->rbpl_table);
		new_tail->idx = i << RBP_IDX_OFFSET;
		new_tail->phys = mapping + दुरत्व(काष्ठा he_buff, data);

		he_dev->rbpl_tail = new_tail;
		++moved;
	पूर्ण 

	अगर (moved)
		he_ग_लिखोl(he_dev, RBPL_MASK(he_dev->rbpl_tail), G0_RBPL_T);
पूर्ण

अटल व्योम
he_tasklet(अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = (काष्ठा he_dev *) data;
	पूर्णांक group, type;
	पूर्णांक updated = 0;

	HPRINTK("tasklet (0x%lx)\n", data);
	spin_lock_irqsave(&he_dev->global_lock, flags);

	जबतक (he_dev->irq_head != he_dev->irq_tail) अणु
		++updated;

		type = ITYPE_TYPE(he_dev->irq_head->isw);
		group = ITYPE_GROUP(he_dev->irq_head->isw);

		चयन (type) अणु
			हाल ITYPE_RBRQ_THRESH:
				HPRINTK("rbrq%d threshold\n", group);
				fallthrough;
			हाल ITYPE_RBRQ_TIMER:
				अगर (he_service_rbrq(he_dev, group))
					he_service_rbpl(he_dev, group);
				अवरोध;
			हाल ITYPE_TBRQ_THRESH:
				HPRINTK("tbrq%d threshold\n", group);
				fallthrough;
			हाल ITYPE_TPD_COMPLETE:
				he_service_tbrq(he_dev, group);
				अवरोध;
			हाल ITYPE_RBPL_THRESH:
				he_service_rbpl(he_dev, group);
				अवरोध;
			हाल ITYPE_RBPS_THRESH:
				/* shouldn't happen unless small buffers enabled */
				अवरोध;
			हाल ITYPE_PHY:
				HPRINTK("phy interrupt\n");
#अगर_घोषित CONFIG_ATM_HE_USE_SUNI
				spin_unlock_irqrestore(&he_dev->global_lock, flags);
				अगर (he_dev->aपंचांग_dev->phy && he_dev->aपंचांग_dev->phy->पूर्णांकerrupt)
					he_dev->aपंचांग_dev->phy->पूर्णांकerrupt(he_dev->aपंचांग_dev);
				spin_lock_irqsave(&he_dev->global_lock, flags);
#पूर्ण_अगर
				अवरोध;
			हाल ITYPE_OTHER:
				चयन (type|group) अणु
					हाल ITYPE_PARITY:
						hprपूर्णांकk("parity error\n");
						अवरोध;
					हाल ITYPE_ABORT:
						hprपूर्णांकk("abort 0x%x\n", he_पढ़ोl(he_dev, ABORT_ADDR));
						अवरोध;
				पूर्ण
				अवरोध;
			हाल ITYPE_TYPE(ITYPE_INVALID):
				/* see 8.1.1 -- check all queues */

				HPRINTK("isw not updated 0x%x\n", he_dev->irq_head->isw);

				he_service_rbrq(he_dev, 0);
				he_service_rbpl(he_dev, 0);
				he_service_tbrq(he_dev, 0);
				अवरोध;
			शेष:
				hprपूर्णांकk("bad isw 0x%x?\n", he_dev->irq_head->isw);
		पूर्ण

		he_dev->irq_head->isw = ITYPE_INVALID;

		he_dev->irq_head = (काष्ठा he_irq *) NEXT_ENTRY(he_dev->irq_base, he_dev->irq_head, IRQ_MASK);
	पूर्ण

	अगर (updated) अणु
		अगर (updated > he_dev->irq_peak)
			he_dev->irq_peak = updated;

		he_ग_लिखोl(he_dev,
			IRQ_SIZE(CONFIG_IRQ_SIZE) |
			IRQ_THRESH(CONFIG_IRQ_THRESH) |
			IRQ_TAIL(he_dev->irq_tail), IRQ0_HEAD);
		(व्योम) he_पढ़ोl(he_dev, INT_FIFO); /* 8.1.2 controller errata; flush posted ग_लिखोs */
	पूर्ण
	spin_unlock_irqrestore(&he_dev->global_lock, flags);
पूर्ण

अटल irqवापस_t
he_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = (काष्ठा he_dev * )dev_id;
	पूर्णांक handled = 0;

	अगर (he_dev == शून्य)
		वापस IRQ_NONE;

	spin_lock_irqsave(&he_dev->global_lock, flags);

	he_dev->irq_tail = (काष्ठा he_irq *) (((अचिन्हित दीर्घ)he_dev->irq_base) |
						(*he_dev->irq_tailoffset << 2));

	अगर (he_dev->irq_tail == he_dev->irq_head) अणु
		HPRINTK("tailoffset not updated?\n");
		he_dev->irq_tail = (काष्ठा he_irq *) ((अचिन्हित दीर्घ)he_dev->irq_base |
			((he_पढ़ोl(he_dev, IRQ0_BASE) & IRQ_MASK) << 2));
		(व्योम) he_पढ़ोl(he_dev, INT_FIFO);	/* 8.1.2 controller errata */
	पूर्ण

#अगर_घोषित DEBUG
	अगर (he_dev->irq_head == he_dev->irq_tail /* && !IRQ_PENDING */)
		hprपूर्णांकk("spurious (or shared) interrupt?\n");
#पूर्ण_अगर

	अगर (he_dev->irq_head != he_dev->irq_tail) अणु
		handled = 1;
		tasklet_schedule(&he_dev->tasklet);
		he_ग_लिखोl(he_dev, INT_CLEAR_A, INT_FIFO);	/* clear पूर्णांकerrupt */
		(व्योम) he_पढ़ोl(he_dev, INT_FIFO);		/* flush posted ग_लिखोs */
	पूर्ण
	spin_unlock_irqrestore(&he_dev->global_lock, flags);
	वापस IRQ_RETVAL(handled);

पूर्ण

अटल __अंतरभूत__ व्योम
__enqueue_tpd(काष्ठा he_dev *he_dev, काष्ठा he_tpd *tpd, अचिन्हित cid)
अणु
	काष्ठा he_tpdrq *new_tail;

	HPRINTK("tpdrq %p cid 0x%x -> tpdrq_tail %p\n",
					tpd, cid, he_dev->tpdrq_tail);

	/* new_tail = he_dev->tpdrq_tail; */
	new_tail = (काष्ठा he_tpdrq *) ((अचिन्हित दीर्घ) he_dev->tpdrq_base |
					TPDRQ_MASK(he_dev->tpdrq_tail+1));

	/*
	 * check to see अगर we are about to set the tail == head
	 * अगर true, update the head poपूर्णांकer from the adapter
	 * to see अगर this is really the हाल (पढ़ोing the queue
	 * head क्रम every enqueue would be unnecessarily slow)
	 */

	अगर (new_tail == he_dev->tpdrq_head) अणु
		he_dev->tpdrq_head = (काष्ठा he_tpdrq *)
			(((अचिन्हित दीर्घ)he_dev->tpdrq_base) |
				TPDRQ_MASK(he_पढ़ोl(he_dev, TPDRQ_B_H)));

		अगर (new_tail == he_dev->tpdrq_head) अणु
			पूर्णांक slot;

			hprपूर्णांकk("tpdrq full (cid 0x%x)\n", cid);
			/*
			 * FIXME
			 * push tpd onto a transmit backlog queue
			 * after service_tbrq, service the backlog
			 * क्रम now, we just drop the pdu
			 */
			क्रम (slot = 0; slot < TPD_MAXIOV; ++slot) अणु
				अगर (tpd->iovec[slot].addr)
					dma_unmap_single(&he_dev->pci_dev->dev,
						tpd->iovec[slot].addr,
						tpd->iovec[slot].len & TPD_LEN_MASK,
								DMA_TO_DEVICE);
			पूर्ण
			अगर (tpd->skb) अणु
				अगर (tpd->vcc->pop)
					tpd->vcc->pop(tpd->vcc, tpd->skb);
				अन्यथा
					dev_kमुक्त_skb_any(tpd->skb);
				atomic_inc(&tpd->vcc->stats->tx_err);
			पूर्ण
			dma_pool_मुक्त(he_dev->tpd_pool, tpd, TPD_ADDR(tpd->status));
			वापस;
		पूर्ण
	पूर्ण

	/* 2.1.5 transmit packet descriptor पढ़ोy queue */
	list_add_tail(&tpd->entry, &he_dev->outstanding_tpds);
	he_dev->tpdrq_tail->tpd = TPD_ADDR(tpd->status);
	he_dev->tpdrq_tail->cid = cid;
	wmb();

	he_dev->tpdrq_tail = new_tail;

	he_ग_लिखोl(he_dev, TPDRQ_MASK(he_dev->tpdrq_tail), TPDRQ_T);
	(व्योम) he_पढ़ोl(he_dev, TPDRQ_T);		/* flush posted ग_लिखोs */
पूर्ण

अटल पूर्णांक
he_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(vcc->dev);
	काष्ठा he_vcc *he_vcc;
	पूर्णांक err = 0;
	अचिन्हित cid, rsr0, rsr1, rsr4, tsr0, tsr0_aal, tsr4, period, reg, घड़ी;
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;

	अगर (vci == ATM_VCI_UNSPEC || vpi == ATM_VPI_UNSPEC)
		वापस 0;

	HPRINTK("open vcc %p %d.%d\n", vcc, vpi, vci);

	set_bit(ATM_VF_ADDR, &vcc->flags);

	cid = he_mkcid(he_dev, vpi, vci);

	he_vcc = kदो_स्मृति(माप(काष्ठा he_vcc), GFP_ATOMIC);
	अगर (he_vcc == शून्य) अणु
		hprपूर्णांकk("unable to allocate he_vcc during open\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&he_vcc->buffers);
	he_vcc->pdu_len = 0;
	he_vcc->rc_index = -1;

	init_रुकोqueue_head(&he_vcc->rx_रुकोq);
	init_रुकोqueue_head(&he_vcc->tx_रुकोq);

	vcc->dev_data = he_vcc;

	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
		पूर्णांक pcr_goal;

		pcr_goal = aपंचांग_pcr_goal(&vcc->qos.txtp);
		अगर (pcr_goal == 0)
			pcr_goal = he_dev->aपंचांग_dev->link_rate;
		अगर (pcr_goal < 0)	/* means round करोwn, technically */
			pcr_goal = -pcr_goal;

		HPRINTK("open tx cid 0x%x pcr_goal %d\n", cid, pcr_goal);

		चयन (vcc->qos.aal) अणु
			हाल ATM_AAL5:
				tsr0_aal = TSR0_AAL5;
				tsr4 = TSR4_AAL5;
				अवरोध;
			हाल ATM_AAL0:
				tsr0_aal = TSR0_AAL0_SDU;
				tsr4 = TSR4_AAL0_SDU;
				अवरोध;
			शेष:
				err = -EINVAL;
				जाओ खोलो_failed;
		पूर्ण

		spin_lock_irqsave(&he_dev->global_lock, flags);
		tsr0 = he_पढ़ोl_tsr0(he_dev, cid);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		अगर (TSR0_CONN_STATE(tsr0) != 0) अणु
			hprपूर्णांकk("cid 0x%x not idle (tsr0 = 0x%x)\n", cid, tsr0);
			err = -EBUSY;
			जाओ खोलो_failed;
		पूर्ण

		चयन (vcc->qos.txtp.traffic_class) अणु
			हाल ATM_UBR:
				/* 2.3.3.1 खोलो connection ubr */

				tsr0 = TSR0_UBR | TSR0_GROUP(0) | tsr0_aal |
					TSR0_USE_WMIN | TSR0_UPDATE_GER;
				अवरोध;

			हाल ATM_CBR:
				/* 2.3.3.2 खोलो connection cbr */

				/* 8.2.3 cbr scheduler wrap problem -- limit to 90% total link rate */
				अगर ((he_dev->total_bw + pcr_goal)
					> (he_dev->aपंचांग_dev->link_rate * 9 / 10))
				अणु
					err = -EBUSY;
					जाओ खोलो_failed;
				पूर्ण

				spin_lock_irqsave(&he_dev->global_lock, flags);			/* also protects he_dev->cs_stper[] */

				/* find an unused cs_stper रेजिस्टर */
				क्रम (reg = 0; reg < HE_NUM_CS_STPER; ++reg)
					अगर (he_dev->cs_stper[reg].inuse == 0 || 
					    he_dev->cs_stper[reg].pcr == pcr_goal)
							अवरोध;

				अगर (reg == HE_NUM_CS_STPER) अणु
					err = -EBUSY;
					spin_unlock_irqrestore(&he_dev->global_lock, flags);
					जाओ खोलो_failed;
				पूर्ण

				he_dev->total_bw += pcr_goal;

				he_vcc->rc_index = reg;
				++he_dev->cs_stper[reg].inuse;
				he_dev->cs_stper[reg].pcr = pcr_goal;

				घड़ी = he_is622(he_dev) ? 66667000 : 50000000;
				period = घड़ी / pcr_goal;
				
				HPRINTK("rc_index = %d period = %d\n",
								reg, period);

				he_ग_लिखोl_mbox(he_dev, rate_to_aपंचांगf(period/2),
							CS_STPER0 + reg);
				spin_unlock_irqrestore(&he_dev->global_lock, flags);

				tsr0 = TSR0_CBR | TSR0_GROUP(0) | tsr0_aal |
							TSR0_RC_INDEX(reg);

				अवरोध;
			शेष:
				err = -EINVAL;
				जाओ खोलो_failed;
		पूर्ण

		spin_lock_irqsave(&he_dev->global_lock, flags);

		he_ग_लिखोl_tsr0(he_dev, tsr0, cid);
		he_ग_लिखोl_tsr4(he_dev, tsr4 | 1, cid);
		he_ग_लिखोl_tsr1(he_dev, TSR1_MCR(rate_to_aपंचांगf(0)) |
					TSR1_PCR(rate_to_aपंचांगf(pcr_goal)), cid);
		he_ग_लिखोl_tsr2(he_dev, TSR2_ACR(rate_to_aपंचांगf(pcr_goal)), cid);
		he_ग_लिखोl_tsr9(he_dev, TSR9_OPEN_CONN, cid);

		he_ग_लिखोl_tsr3(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr5(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr6(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr7(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr8(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr10(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr11(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr12(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr13(he_dev, 0x0, cid);
		he_ग_लिखोl_tsr14(he_dev, 0x0, cid);
		(व्योम) he_पढ़ोl_tsr0(he_dev, cid);		/* flush posted ग_लिखोs */
		spin_unlock_irqrestore(&he_dev->global_lock, flags);
	पूर्ण

	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
		अचिन्हित aal;

		HPRINTK("open rx cid 0x%x (rx_waitq %p)\n", cid,
		 				&HE_VCC(vcc)->rx_रुकोq);

		चयन (vcc->qos.aal) अणु
			हाल ATM_AAL5:
				aal = RSR0_AAL5;
				अवरोध;
			हाल ATM_AAL0:
				aal = RSR0_RAWCELL;
				अवरोध;
			शेष:
				err = -EINVAL;
				जाओ खोलो_failed;
		पूर्ण

		spin_lock_irqsave(&he_dev->global_lock, flags);

		rsr0 = he_पढ़ोl_rsr0(he_dev, cid);
		अगर (rsr0 & RSR0_OPEN_CONN) अणु
			spin_unlock_irqrestore(&he_dev->global_lock, flags);

			hprपूर्णांकk("cid 0x%x not idle (rsr0 = 0x%x)\n", cid, rsr0);
			err = -EBUSY;
			जाओ खोलो_failed;
		पूर्ण

		rsr1 = RSR1_GROUP(0) | RSR1_RBPL_ONLY;
		rsr4 = RSR4_GROUP(0) | RSR4_RBPL_ONLY;
		rsr0 = vcc->qos.rxtp.traffic_class == ATM_UBR ? 
				(RSR0_EPD_ENABLE|RSR0_PPD_ENABLE) : 0;

#अगर_घोषित USE_CHECKSUM_HW
		अगर (vpi == 0 && vci >= ATM_NOT_RSV_VCI)
			rsr0 |= RSR0_TCP_CKSUM;
#पूर्ण_अगर

		he_ग_लिखोl_rsr4(he_dev, rsr4, cid);
		he_ग_लिखोl_rsr1(he_dev, rsr1, cid);
		/* 5.1.11 last parameter initialized should be
			  the खोलो/बंदd indication in rsr0 */
		he_ग_लिखोl_rsr0(he_dev,
			rsr0 | RSR0_START_PDU | RSR0_OPEN_CONN | aal, cid);
		(व्योम) he_पढ़ोl_rsr0(he_dev, cid);		/* flush posted ग_लिखोs */

		spin_unlock_irqrestore(&he_dev->global_lock, flags);
	पूर्ण

खोलो_failed:

	अगर (err) अणु
		kमुक्त(he_vcc);
		clear_bit(ATM_VF_ADDR, &vcc->flags);
	पूर्ण
	अन्यथा
		set_bit(ATM_VF_READY, &vcc->flags);

	वापस err;
पूर्ण

अटल व्योम
he_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	अचिन्हित दीर्घ flags;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा he_dev *he_dev = HE_DEV(vcc->dev);
	काष्ठा he_tpd *tpd;
	अचिन्हित cid;
	काष्ठा he_vcc *he_vcc = HE_VCC(vcc);
#घोषणा MAX_RETRY 30
	पूर्णांक retry = 0, sleep = 1, tx_inuse;

	HPRINTK("close vcc %p %d.%d\n", vcc, vcc->vpi, vcc->vci);

	clear_bit(ATM_VF_READY, &vcc->flags);
	cid = he_mkcid(he_dev, vcc->vpi, vcc->vci);

	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
		पूर्णांक समयout;

		HPRINTK("close rx cid 0x%x\n", cid);

		/* 2.7.2.2 बंद receive operation */

		/* रुको क्रम previous बंद (अगर any) to finish */

		spin_lock_irqsave(&he_dev->global_lock, flags);
		जबतक (he_पढ़ोl(he_dev, RCC_STAT) & RCC_BUSY) अणु
			HPRINTK("close cid 0x%x RCC_BUSY\n", cid);
			udelay(250);
		पूर्ण

		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&he_vcc->rx_रुकोq, &रुको);

		he_ग_लिखोl_rsr0(he_dev, RSR0_CLOSE_CONN, cid);
		(व्योम) he_पढ़ोl_rsr0(he_dev, cid);		/* flush posted ग_लिखोs */
		he_ग_लिखोl_mbox(he_dev, cid, RXCON_CLOSE);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		समयout = schedule_समयout(30*HZ);

		हटाओ_रुको_queue(&he_vcc->rx_रुकोq, &रुको);
		set_current_state(TASK_RUNNING);

		अगर (समयout == 0)
			hprपूर्णांकk("close rx timeout cid 0x%x\n", cid);

		HPRINTK("close rx cid 0x%x complete\n", cid);

	पूर्ण

	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
		अस्थिर अचिन्हित tsr4, tsr0;
		पूर्णांक समयout;

		HPRINTK("close tx cid 0x%x\n", cid);
		
		/* 2.1.2
		 *
		 * ... the host must first stop queueing packets to the TPDRQ
		 * on the connection to be बंदd, then रुको क्रम all outstanding
		 * packets to be transmitted and their buffers वापसed to the
		 * TBRQ. When the last packet on the connection arrives in the
		 * TBRQ, the host issues the बंद command to the adapter.
		 */

		जबतक (((tx_inuse = refcount_पढ़ो(&sk_aपंचांग(vcc)->sk_wmem_alloc)) > 1) &&
		       (retry < MAX_RETRY)) अणु
			msleep(sleep);
			अगर (sleep < 250)
				sleep = sleep * 2;

			++retry;
		पूर्ण

		अगर (tx_inuse > 1)
			hprपूर्णांकk("close tx cid 0x%x tx_inuse = %d\n", cid, tx_inuse);

		/* 2.3.1.1 generic बंद operations with flush */

		spin_lock_irqsave(&he_dev->global_lock, flags);
		he_ग_लिखोl_tsr4_upper(he_dev, TSR4_FLUSH_CONN, cid);
					/* also clears TSR4_SESSION_ENDED */

		चयन (vcc->qos.txtp.traffic_class) अणु
			हाल ATM_UBR:
				he_ग_लिखोl_tsr1(he_dev, 
					TSR1_MCR(rate_to_aपंचांगf(200000))
					| TSR1_PCR(0), cid);
				अवरोध;
			हाल ATM_CBR:
				he_ग_लिखोl_tsr14_upper(he_dev, TSR14_DELETE, cid);
				अवरोध;
		पूर्ण
		(व्योम) he_पढ़ोl_tsr4(he_dev, cid);		/* flush posted ग_लिखोs */

		tpd = __alloc_tpd(he_dev);
		अगर (tpd == शून्य) अणु
			hprपूर्णांकk("close tx he_alloc_tpd failed cid 0x%x\n", cid);
			जाओ बंद_tx_incomplete;
		पूर्ण
		tpd->status |= TPD_EOS | TPD_INT;
		tpd->skb = शून्य;
		tpd->vcc = vcc;
		wmb();

		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&he_vcc->tx_रुकोq, &रुको);
		__enqueue_tpd(he_dev, tpd, cid);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		समयout = schedule_समयout(30*HZ);

		हटाओ_रुको_queue(&he_vcc->tx_रुकोq, &रुको);
		set_current_state(TASK_RUNNING);

		spin_lock_irqsave(&he_dev->global_lock, flags);

		अगर (समयout == 0) अणु
			hprपूर्णांकk("close tx timeout cid 0x%x\n", cid);
			जाओ बंद_tx_incomplete;
		पूर्ण

		जबतक (!((tsr4 = he_पढ़ोl_tsr4(he_dev, cid)) & TSR4_SESSION_ENDED)) अणु
			HPRINTK("close tx cid 0x%x !TSR4_SESSION_ENDED (tsr4 = 0x%x)\n", cid, tsr4);
			udelay(250);
		पूर्ण

		जबतक (TSR0_CONN_STATE(tsr0 = he_पढ़ोl_tsr0(he_dev, cid)) != 0) अणु
			HPRINTK("close tx cid 0x%x TSR0_CONN_STATE != 0 (tsr0 = 0x%x)\n", cid, tsr0);
			udelay(250);
		पूर्ण

बंद_tx_incomplete:

		अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
			पूर्णांक reg = he_vcc->rc_index;

			HPRINTK("cs_stper reg = %d\n", reg);

			अगर (he_dev->cs_stper[reg].inuse == 0)
				hprपूर्णांकk("cs_stper[%d].inuse = 0!\n", reg);
			अन्यथा
				--he_dev->cs_stper[reg].inuse;

			he_dev->total_bw -= he_dev->cs_stper[reg].pcr;
		पूर्ण
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		HPRINTK("close tx cid 0x%x complete\n", cid);
	पूर्ण

	kमुक्त(he_vcc);

	clear_bit(ATM_VF_ADDR, &vcc->flags);
पूर्ण

अटल पूर्णांक
he_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(vcc->dev);
	अचिन्हित cid = he_mkcid(he_dev, vcc->vpi, vcc->vci);
	काष्ठा he_tpd *tpd;
#अगर_घोषित USE_SCATTERGATHER
	पूर्णांक i, slot = 0;
#पूर्ण_अगर

#घोषणा HE_TPD_बफ_मानE 0xffff

	HPRINTK("send %d.%d\n", vcc->vpi, vcc->vci);

	अगर ((skb->len > HE_TPD_बफ_मानE) ||
	    ((vcc->qos.aal == ATM_AAL0) && (skb->len != ATM_AAL0_SDU))) अणु
		hprपूर्णांकk("buffer too large (or small) -- %d bytes\n", skb->len );
		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
		atomic_inc(&vcc->stats->tx_err);
		वापस -EINVAL;
	पूर्ण

#अगर_अघोषित USE_SCATTERGATHER
	अगर (skb_shinfo(skb)->nr_frags) अणु
		hprपूर्णांकk("no scatter/gather support\n");
		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
		atomic_inc(&vcc->stats->tx_err);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	spin_lock_irqsave(&he_dev->global_lock, flags);

	tpd = __alloc_tpd(he_dev);
	अगर (tpd == शून्य) अणु
		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
		atomic_inc(&vcc->stats->tx_err);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);
		वापस -ENOMEM;
	पूर्ण

	अगर (vcc->qos.aal == ATM_AAL5)
		tpd->status |= TPD_CELLTYPE(TPD_USERCELL);
	अन्यथा अणु
		अक्षर *pti_clp = (व्योम *) (skb->data + 3);
		पूर्णांक clp, pti;

		pti = (*pti_clp & ATM_HDR_PTI_MASK) >> ATM_HDR_PTI_SHIFT; 
		clp = (*pti_clp & ATM_HDR_CLP);
		tpd->status |= TPD_CELLTYPE(pti);
		अगर (clp)
			tpd->status |= TPD_CLP;

		skb_pull(skb, ATM_AAL0_SDU - ATM_CELL_PAYLOAD);
	पूर्ण

#अगर_घोषित USE_SCATTERGATHER
	tpd->iovec[slot].addr = dma_map_single(&he_dev->pci_dev->dev, skb->data,
				skb_headlen(skb), DMA_TO_DEVICE);
	tpd->iovec[slot].len = skb_headlen(skb);
	++slot;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		अगर (slot == TPD_MAXIOV) अणु	/* queue tpd; start new tpd */
			tpd->vcc = vcc;
			tpd->skb = शून्य;	/* not the last fragment
						   so करोnt ->push() yet */
			wmb();

			__enqueue_tpd(he_dev, tpd, cid);
			tpd = __alloc_tpd(he_dev);
			अगर (tpd == शून्य) अणु
				अगर (vcc->pop)
					vcc->pop(vcc, skb);
				अन्यथा
					dev_kमुक्त_skb_any(skb);
				atomic_inc(&vcc->stats->tx_err);
				spin_unlock_irqrestore(&he_dev->global_lock, flags);
				वापस -ENOMEM;
			पूर्ण
			tpd->status |= TPD_USERCELL;
			slot = 0;
		पूर्ण

		tpd->iovec[slot].addr = skb_frag_dma_map(&he_dev->pci_dev->dev,
				frag, 0, skb_frag_size(frag), DMA_TO_DEVICE);
		tpd->iovec[slot].len = skb_frag_size(frag);
		++slot;

	पूर्ण

	tpd->iovec[slot - 1].len |= TPD_LST;
#अन्यथा
	tpd->address0 = dma_map_single(&he_dev->pci_dev->dev, skb->data, skb->len, DMA_TO_DEVICE);
	tpd->length0 = skb->len | TPD_LST;
#पूर्ण_अगर
	tpd->status |= TPD_INT;

	tpd->vcc = vcc;
	tpd->skb = skb;
	wmb();
	ATM_SKB(skb)->vcc = vcc;

	__enqueue_tpd(he_dev, tpd, cid);
	spin_unlock_irqrestore(&he_dev->global_lock, flags);

	atomic_inc(&vcc->stats->tx);

	वापस 0;
पूर्ण

अटल पूर्णांक
he_ioctl(काष्ठा aपंचांग_dev *aपंचांग_dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(aपंचांग_dev);
	काष्ठा he_ioctl_reg reg;
	पूर्णांक err = 0;

	चयन (cmd) अणु
		हाल HE_GET_REG:
			अगर (!capable(CAP_NET_ADMIN))
				वापस -EPERM;

			अगर (copy_from_user(&reg, arg,
					   माप(काष्ठा he_ioctl_reg)))
				वापस -EFAULT;

			spin_lock_irqsave(&he_dev->global_lock, flags);
			चयन (reg.type) अणु
				हाल HE_REGTYPE_PCI:
					अगर (reg.addr >= HE_REGMAP_SIZE) अणु
						err = -EINVAL;
						अवरोध;
					पूर्ण

					reg.val = he_पढ़ोl(he_dev, reg.addr);
					अवरोध;
				हाल HE_REGTYPE_RCM:
					reg.val =
						he_पढ़ोl_rcm(he_dev, reg.addr);
					अवरोध;
				हाल HE_REGTYPE_TCM:
					reg.val =
						he_पढ़ोl_tcm(he_dev, reg.addr);
					अवरोध;
				हाल HE_REGTYPE_MBOX:
					reg.val =
						he_पढ़ोl_mbox(he_dev, reg.addr);
					अवरोध;
				शेष:
					err = -EINVAL;
					अवरोध;
			पूर्ण
			spin_unlock_irqrestore(&he_dev->global_lock, flags);
			अगर (err == 0)
				अगर (copy_to_user(arg, &reg,
							माप(काष्ठा he_ioctl_reg)))
					वापस -EFAULT;
			अवरोध;
		शेष:
#अगर_घोषित CONFIG_ATM_HE_USE_SUNI
			अगर (aपंचांग_dev->phy && aपंचांग_dev->phy->ioctl)
				err = aपंचांग_dev->phy->ioctl(aपंचांग_dev, cmd, arg);
#अन्यथा /* CONFIG_ATM_HE_USE_SUNI */
			err = -EINVAL;
#पूर्ण_अगर /* CONFIG_ATM_HE_USE_SUNI */
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
he_phy_put(काष्ठा aपंचांग_dev *aपंचांग_dev, अचिन्हित अक्षर val, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(aपंचांग_dev);

	HPRINTK("phy_put(val 0x%x, addr 0x%lx)\n", val, addr);

	spin_lock_irqsave(&he_dev->global_lock, flags);
	he_ग_लिखोl(he_dev, val, FRAMER + (addr*4));
	(व्योम) he_पढ़ोl(he_dev, FRAMER + (addr*4));		/* flush posted ग_लिखोs */
	spin_unlock_irqrestore(&he_dev->global_lock, flags);
पूर्ण
 
	
अटल अचिन्हित अक्षर
he_phy_get(काष्ठा aपंचांग_dev *aपंचांग_dev, अचिन्हित दीर्घ addr)
अणु 
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(aपंचांग_dev);
	अचिन्हित reg;

	spin_lock_irqsave(&he_dev->global_lock, flags);
	reg = he_पढ़ोl(he_dev, FRAMER + (addr*4));
	spin_unlock_irqrestore(&he_dev->global_lock, flags);

	HPRINTK("phy_get(addr 0x%lx) =0x%x\n", addr, reg);
	वापस reg;
पूर्ण

अटल पूर्णांक
he_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t *pos, अक्षर *page)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा he_dev *he_dev = HE_DEV(dev);
	पूर्णांक left, i;
#अगर_घोषित notdef
	काष्ठा he_rbrq *rbrq_tail;
	काष्ठा he_tpdrq *tpdrq_head;
	पूर्णांक rbpl_head, rbpl_tail;
#पूर्ण_अगर
	अटल दीर्घ mcc = 0, oec = 0, dcc = 0, cec = 0;


	left = *pos;
	अगर (!left--)
		वापस प्र_लिखो(page, "ATM he driver\n");

	अगर (!left--)
		वापस प्र_लिखो(page, "%s%s\n\n",
			he_dev->prod_id, he_dev->media & 0x40 ? "SM" : "MM");

	अगर (!left--)
		वापस प्र_लिखो(page, "Mismatched Cells  VPI/VCI Not Open  Dropped Cells  RCM Dropped Cells\n");

	spin_lock_irqsave(&he_dev->global_lock, flags);
	mcc += he_पढ़ोl(he_dev, MCC);
	oec += he_पढ़ोl(he_dev, OEC);
	dcc += he_पढ़ोl(he_dev, DCC);
	cec += he_पढ़ोl(he_dev, CEC);
	spin_unlock_irqrestore(&he_dev->global_lock, flags);

	अगर (!left--)
		वापस प्र_लिखो(page, "%16ld  %16ld  %13ld  %17ld\n\n", 
							mcc, oec, dcc, cec);

	अगर (!left--)
		वापस प्र_लिखो(page, "irq_size = %d  inuse = ?  peak = %d\n",
				CONFIG_IRQ_SIZE, he_dev->irq_peak);

	अगर (!left--)
		वापस प्र_लिखो(page, "tpdrq_size = %d  inuse = ?\n",
						CONFIG_TPDRQ_SIZE);

	अगर (!left--)
		वापस प्र_लिखो(page, "rbrq_size = %d  inuse = ?  peak = %d\n",
				CONFIG_RBRQ_SIZE, he_dev->rbrq_peak);

	अगर (!left--)
		वापस प्र_लिखो(page, "tbrq_size = %d  peak = %d\n",
					CONFIG_TBRQ_SIZE, he_dev->tbrq_peak);


#अगर_घोषित notdef
	rbpl_head = RBPL_MASK(he_पढ़ोl(he_dev, G0_RBPL_S));
	rbpl_tail = RBPL_MASK(he_पढ़ोl(he_dev, G0_RBPL_T));

	inuse = rbpl_head - rbpl_tail;
	अगर (inuse < 0)
		inuse += CONFIG_RBPL_SIZE * माप(काष्ठा he_rbp);
	inuse /= माप(काष्ठा he_rbp);

	अगर (!left--)
		वापस प्र_लिखो(page, "rbpl_size = %d  inuse = %d\n\n",
						CONFIG_RBPL_SIZE, inuse);
#पूर्ण_अगर

	अगर (!left--)
		वापस प्र_लिखो(page, "rate controller periods (cbr)\n                 pcr  #vc\n");

	क्रम (i = 0; i < HE_NUM_CS_STPER; ++i)
		अगर (!left--)
			वापस प्र_लिखो(page, "cs_stper%-2d  %8ld  %3d\n", i,
						he_dev->cs_stper[i].pcr,
						he_dev->cs_stper[i].inuse);

	अगर (!left--)
		वापस प्र_लिखो(page, "total bw (cbr): %d  (limit %d)\n",
			he_dev->total_bw, he_dev->aपंचांग_dev->link_rate * 10 / 9);

	वापस 0;
पूर्ण

/* eeprom routines  -- see 4.7 */

अटल u8 पढ़ो_prom_byte(काष्ठा he_dev *he_dev, पूर्णांक addr)
अणु
	u32 val = 0, पंचांगp_पढ़ो = 0;
	पूर्णांक i, j = 0;
	u8 byte_पढ़ो = 0;

	val = पढ़ोl(he_dev->membase + HOST_CNTL);
	val &= 0xFFFFE0FF;
       
	/* Turn on ग_लिखो enable */
	val |= 0x800;
	he_ग_लिखोl(he_dev, val, HOST_CNTL);
       
	/* Send READ inकाष्ठाion */
	क्रम (i = 0; i < ARRAY_SIZE(पढ़ोtab); i++) अणु
		he_ग_लिखोl(he_dev, val | पढ़ोtab[i], HOST_CNTL);
		udelay(EEPROM_DELAY);
	पूर्ण
       
	/* Next, we need to send the byte address to पढ़ो from */
	क्रम (i = 7; i >= 0; i--) अणु
		he_ग_लिखोl(he_dev, val | घड़ीtab[j++] | (((addr >> i) & 1) << 9), HOST_CNTL);
		udelay(EEPROM_DELAY);
		he_ग_लिखोl(he_dev, val | घड़ीtab[j++] | (((addr >> i) & 1) << 9), HOST_CNTL);
		udelay(EEPROM_DELAY);
	पूर्ण
       
	j = 0;

	val &= 0xFFFFF7FF;      /* Turn off ग_लिखो enable */
	he_ग_लिखोl(he_dev, val, HOST_CNTL);
       
	/* Now, we can पढ़ो data from the EEPROM by घड़ीing it in */
	क्रम (i = 7; i >= 0; i--) अणु
		he_ग_लिखोl(he_dev, val | घड़ीtab[j++], HOST_CNTL);
		udelay(EEPROM_DELAY);
		पंचांगp_पढ़ो = he_पढ़ोl(he_dev, HOST_CNTL);
		byte_पढ़ो |= (अचिन्हित अक्षर)
			   ((पंचांगp_पढ़ो & ID_DOUT) >> ID_DOFFSET << i);
		he_ग_लिखोl(he_dev, val | घड़ीtab[j++], HOST_CNTL);
		udelay(EEPROM_DELAY);
	पूर्ण
       
	he_ग_लिखोl(he_dev, val | ID_CS, HOST_CNTL);
	udelay(EEPROM_DELAY);

	वापस byte_पढ़ो;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chas williams <chas@cmf.nrl.navy.mil>");
MODULE_DESCRIPTION("ForeRunnerHE ATM Adapter driver");
module_param(disable64, bool, 0);
MODULE_PARM_DESC(disable64, "disable 64-bit pci bus transfers");
module_param(nvpibits, लघु, 0);
MODULE_PARM_DESC(nvpibits, "numbers of bits for vpi (default 0)");
module_param(nvcibits, लघु, 0);
MODULE_PARM_DESC(nvcibits, "numbers of bits for vci (default 12)");
module_param(rx_skb_reserve, लघु, 0);
MODULE_PARM_DESC(rx_skb_reserve, "padding for receive skb (default 16)");
module_param(irq_coalesce, bool, 0);
MODULE_PARM_DESC(irq_coalesce, "use interrupt coalescing (default 1)");
module_param(sdh, bool, 0);
MODULE_PARM_DESC(sdh, "use SDH framing (default 0)");

अटल स्थिर काष्ठा pci_device_id he_pci_tbl[] = अणु
	अणु PCI_VDEVICE(FORE, PCI_DEVICE_ID_FORE_HE), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, he_pci_tbl);

अटल काष्ठा pci_driver he_driver = अणु
	.name =		"he",
	.probe =	he_init_one,
	.हटाओ =	he_हटाओ_one,
	.id_table =	he_pci_tbl,
पूर्ण;

module_pci_driver(he_driver);
