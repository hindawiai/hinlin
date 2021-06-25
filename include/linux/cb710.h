<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  cb710/cb710.h
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#अगर_अघोषित LINUX_CB710_DRIVER_H
#घोषणा LINUX_CB710_DRIVER_H

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mmc/host.h>

काष्ठा cb710_slot;

प्रकार पूर्णांक (*cb710_irq_handler_t)(काष्ठा cb710_slot *);

/* per-भव-slot काष्ठाure */
काष्ठा cb710_slot अणु
	काष्ठा platक्रमm_device	pdev;
	व्योम __iomem		*iobase;
	cb710_irq_handler_t	irq_handler;
पूर्ण;

/* per-device काष्ठाure */
काष्ठा cb710_chip अणु
	काष्ठा pci_dev		*pdev;
	व्योम __iomem		*iobase;
	अचिन्हित		platक्रमm_id;
#अगर_घोषित CONFIG_CB710_DEBUG_ASSUMPTIONS
	atomic_t		slot_refs_count;
#पूर्ण_अगर
	अचिन्हित		slot_mask;
	अचिन्हित		slots;
	spinlock_t		irq_lock;
	काष्ठा cb710_slot	slot[];
पूर्ण;

/* NOTE: cb710_chip.slots is modअगरied only during device init/निकास and
 * they are all serialized wrt themselves */

/* cb710_chip.slot_mask values */
#घोषणा CB710_SLOT_MMC		1
#घोषणा CB710_SLOT_MS		2
#घोषणा CB710_SLOT_SM		4

/* slot port accessors - so the logic is more clear in the code */
#घोषणा CB710_PORT_ACCESSORS(t) \
अटल अंतरभूत व्योम cb710_ग_लिखो_port_##t(काष्ठा cb710_slot *slot,	\
	अचिन्हित port, u##t value)					\
अणु									\
	ioग_लिखो##t(value, slot->iobase + port);				\
पूर्ण									\
									\
अटल अंतरभूत u##t cb710_पढ़ो_port_##t(काष्ठा cb710_slot *slot,		\
	अचिन्हित port)							\
अणु									\
	वापस ioपढ़ो##t(slot->iobase + port);				\
पूर्ण									\
									\
अटल अंतरभूत व्योम cb710_modअगरy_port_##t(काष्ठा cb710_slot *slot,	\
	अचिन्हित port, u##t set, u##t clear)				\
अणु									\
	ioग_लिखो##t(							\
		(ioपढ़ो##t(slot->iobase + port) & ~clear)|set,		\
		slot->iobase + port);					\
पूर्ण

CB710_PORT_ACCESSORS(8)
CB710_PORT_ACCESSORS(16)
CB710_PORT_ACCESSORS(32)

व्योम cb710_pci_update_config_reg(काष्ठा pci_dev *pdev,
	पूर्णांक reg, uपूर्णांक32_t and, uपूर्णांक32_t xor);
व्योम cb710_set_irq_handler(काष्ठा cb710_slot *slot,
	cb710_irq_handler_t handler);

/* some device काष्ठा walking */

अटल अंतरभूत काष्ठा cb710_slot *cb710_pdev_to_slot(
	काष्ठा platक्रमm_device *pdev)
अणु
	वापस container_of(pdev, काष्ठा cb710_slot, pdev);
पूर्ण

अटल अंतरभूत काष्ठा cb710_chip *cb710_slot_to_chip(काष्ठा cb710_slot *slot)
अणु
	वापस dev_get_drvdata(slot->pdev.dev.parent);
पूर्ण

अटल अंतरभूत काष्ठा device *cb710_slot_dev(काष्ठा cb710_slot *slot)
अणु
	वापस &slot->pdev.dev;
पूर्ण

अटल अंतरभूत काष्ठा device *cb710_chip_dev(काष्ठा cb710_chip *chip)
अणु
	वापस &chip->pdev->dev;
पूर्ण

/* debugging aids */

#अगर_घोषित CONFIG_CB710_DEBUG
व्योम cb710_dump_regs(काष्ठा cb710_chip *chip, अचिन्हित dump);
#अन्यथा
#घोषणा cb710_dump_regs(c, d) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा CB710_DUMP_REGS_MMC	0x0F
#घोषणा CB710_DUMP_REGS_MS	0x30
#घोषणा CB710_DUMP_REGS_SM	0xC0
#घोषणा CB710_DUMP_REGS_ALL	0xFF
#घोषणा CB710_DUMP_REGS_MASK	0xFF

#घोषणा CB710_DUMP_ACCESS_8	0x100
#घोषणा CB710_DUMP_ACCESS_16	0x200
#घोषणा CB710_DUMP_ACCESS_32	0x400
#घोषणा CB710_DUMP_ACCESS_ALL	0x700
#घोषणा CB710_DUMP_ACCESS_MASK	0x700

#पूर्ण_अगर /* LINUX_CB710_DRIVER_H */
/*
 *  cb710/sgbuf2.h
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#अगर_अघोषित LINUX_CB710_SG_H
#घोषणा LINUX_CB710_SG_H

#समावेश <linux/highस्मृति.स>
#समावेश <linux/scatterlist.h>

/*
 * 32-bit PIO mapping sg iterator
 *
 * Hides scatterlist access issues - fragment boundaries, alignment, page
 * mapping - क्रम drivers using 32-bit-word-at-a-समय-PIO (ie. PCI devices
 * without DMA support).
 *
 * Best-हाल पढ़ोing (transfer from device):
 *   sg_miter_start(, SG_MITER_TO_SG);
 *   cb710_sg_dwiter_ग_लिखो_from_io();
 *   sg_miter_stop();
 *
 * Best-हाल writing (transfer to device):
 *   sg_miter_start(, SG_MITER_FROM_SG);
 *   cb710_sg_dwiter_पढ़ो_to_io();
 *   sg_miter_stop();
 */

uपूर्णांक32_t cb710_sg_dwiter_पढ़ो_next_block(काष्ठा sg_mapping_iter *miter);
व्योम cb710_sg_dwiter_ग_लिखो_next_block(काष्ठा sg_mapping_iter *miter, uपूर्णांक32_t data);

/**
 * cb710_sg_dwiter_ग_लिखो_from_io - transfer data to mapped buffer from 32-bit IO port
 * @miter: sg mapping iter
 * @port: PIO port - IO or MMIO address
 * @count: number of 32-bit words to transfer
 *
 * Description:
 *   Reads @count 32-bit words from रेजिस्टर @port and stores it in
 *   buffer iterated by @miter.  Data that would overflow the buffer
 *   is silently ignored.  Iterator is advanced by 4*@count bytes
 *   or to the buffer's end whichever is बंदr.
 *
 * Context:
 *   IRQ disabled अगर the SG_MITER_ATOMIC is set.  Don't care otherwise.
 */
अटल अंतरभूत व्योम cb710_sg_dwiter_ग_लिखो_from_io(काष्ठा sg_mapping_iter *miter,
	व्योम __iomem *port, माप_प्रकार count)
अणु
	जबतक (count-- > 0)
		cb710_sg_dwiter_ग_लिखो_next_block(miter, ioपढ़ो32(port));
पूर्ण

/**
 * cb710_sg_dwiter_पढ़ो_to_io - transfer data to 32-bit IO port from mapped buffer
 * @miter: sg mapping iter
 * @port: PIO port - IO or MMIO address
 * @count: number of 32-bit words to transfer
 *
 * Description:
 *   Writes @count 32-bit words to रेजिस्टर @port from buffer iterated
 *   through @miter.  If buffer ends beक्रमe @count words are written
 *   missing data is replaced by zeroes. @miter is advanced by 4*@count
 *   bytes or to the buffer's end whichever is बंदr.
 *
 * Context:
 *   IRQ disabled अगर the SG_MITER_ATOMIC is set.  Don't care otherwise.
 */
अटल अंतरभूत व्योम cb710_sg_dwiter_पढ़ो_to_io(काष्ठा sg_mapping_iter *miter,
	व्योम __iomem *port, माप_प्रकार count)
अणु
	जबतक (count-- > 0)
		ioग_लिखो32(cb710_sg_dwiter_पढ़ो_next_block(miter), port);
पूर्ण

#पूर्ण_अगर /* LINUX_CB710_SG_H */
