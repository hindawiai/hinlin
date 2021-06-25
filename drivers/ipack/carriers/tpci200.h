<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**
 * tpci200.h
 *
 * driver क्रम the carrier TEWS TPCI-200
 *
 * Copyright (C) 2009-2012 CERN (www.cern.ch)
 * Author: Nicolas Serafini, EIC2 SA
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#अगर_अघोषित _TPCI200_H_
#घोषणा _TPCI200_H_

#समावेश <linux/सीमा.स>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/swab.h>
#समावेश <linux/पन.स>
#समावेश <linux/ipack.h>

#घोषणा TPCI200_NB_SLOT               0x4
#घोषणा TPCI200_NB_BAR                0x6

#घोषणा TPCI200_VENDOR_ID             0x1498
#घोषणा TPCI200_DEVICE_ID             0x30C8
#घोषणा TPCI200_SUBVENDOR_ID          0x1498
#घोषणा TPCI200_SUBDEVICE_ID          0x300A

#घोषणा TPCI200_CFG_MEM_BAR           0
#घोषणा TPCI200_IP_INTERFACE_BAR      2
#घोषणा TPCI200_IO_ID_INT_SPACES_BAR  3
#घोषणा TPCI200_MEM16_SPACE_BAR       4
#घोषणा TPCI200_MEM8_SPACE_BAR        5

काष्ठा tpci200_regs अणु
	__le16	revision;
	/* ग_लिखोs to control should occur with the mutex held to protect
	 * पढ़ो-modअगरy-ग_लिखो operations */
	__le16  control[4];
	__le16	reset;
	__le16	status;
	u8	reserved[242];
पूर्ण __packed;

#घोषणा TPCI200_IFACE_SIZE            0x100

#घोषणा TPCI200_IO_SPACE_OFF          0x0000
#घोषणा TPCI200_IO_SPACE_INTERVAL     0x0100
#घोषणा TPCI200_IO_SPACE_SIZE         0x0080
#घोषणा TPCI200_ID_SPACE_OFF          0x0080
#घोषणा TPCI200_ID_SPACE_INTERVAL     0x0100
#घोषणा TPCI200_ID_SPACE_SIZE         0x0040
#घोषणा TPCI200_INT_SPACE_OFF         0x00C0
#घोषणा TPCI200_INT_SPACE_INTERVAL    0x0100
#घोषणा TPCI200_INT_SPACE_SIZE        0x0040
#घोषणा TPCI200_IOIDINT_SIZE          0x0400

#घोषणा TPCI200_MEM8_SPACE_INTERVAL   0x00400000
#घोषणा TPCI200_MEM8_SPACE_SIZE       0x00400000
#घोषणा TPCI200_MEM16_SPACE_INTERVAL  0x00800000
#घोषणा TPCI200_MEM16_SPACE_SIZE      0x00800000

/* control field in tpci200_regs */
#घोषणा TPCI200_INT0_EN               0x0040
#घोषणा TPCI200_INT1_EN               0x0080
#घोषणा TPCI200_INT0_EDGE             0x0010
#घोषणा TPCI200_INT1_EDGE             0x0020
#घोषणा TPCI200_ERR_INT_EN            0x0008
#घोषणा TPCI200_TIME_INT_EN           0x0004
#घोषणा TPCI200_RECOVER_EN            0x0002
#घोषणा TPCI200_CLK32                 0x0001

/* reset field in tpci200_regs */
#घोषणा TPCI200_A_RESET               0x0001
#घोषणा TPCI200_B_RESET               0x0002
#घोषणा TPCI200_C_RESET               0x0004
#घोषणा TPCI200_D_RESET               0x0008

/* status field in tpci200_regs */
#घोषणा TPCI200_A_TIMEOUT             0x1000
#घोषणा TPCI200_B_TIMEOUT             0x2000
#घोषणा TPCI200_C_TIMEOUT             0x4000
#घोषणा TPCI200_D_TIMEOUT             0x8000

#घोषणा TPCI200_A_ERROR               0x0100
#घोषणा TPCI200_B_ERROR               0x0200
#घोषणा TPCI200_C_ERROR               0x0400
#घोषणा TPCI200_D_ERROR               0x0800

#घोषणा TPCI200_A_INT0                0x0001
#घोषणा TPCI200_A_INT1                0x0002
#घोषणा TPCI200_B_INT0                0x0004
#घोषणा TPCI200_B_INT1                0x0008
#घोषणा TPCI200_C_INT0                0x0010
#घोषणा TPCI200_C_INT1                0x0020
#घोषणा TPCI200_D_INT0                0x0040
#घोषणा TPCI200_D_INT1                0x0080

#घोषणा TPCI200_SLOT_INT_MASK         0x00FF

/* PCI Configuration रेजिस्टरs. The PCI bridge is a PLX Technology PCI9030. */
#घोषणा LAS1_DESC		      0x2C
#घोषणा LAS2_DESC		      0x30

/* Bits in the LAS?_DESC रेजिस्टरs */
#घोषणा LAS_BIT_BIGENDIAN	      24

#घोषणा VME_IOID_SPACE  "IOID"
#घोषणा VME_MEM_SPACE  "MEM"

/**
 * काष्ठा slot_irq - slot IRQ definition.
 * @vector	Vector number
 * @handler	Handler called when IRQ arrives
 * @arg		Handler argument
 *
 */
काष्ठा slot_irq अणु
	काष्ठा ipack_device *holder;
	पूर्णांक		vector;
	irqवापस_t	(*handler)(व्योम *);
	व्योम		*arg;
पूर्ण;

/**
 * काष्ठा tpci200_slot - data specअगरic to the tpci200 slot.
 * @slot_id	Slot identअगरication gived to बाह्यal पूर्णांकerface
 * @irq		Slot IRQ infos
 * @io_phys	IO physical base address रेजिस्टर of the slot
 * @id_phys	ID physical base address रेजिस्टर of the slot
 * @पूर्णांक_phys	INT physical base address रेजिस्टर of the slot
 * @mem_phys	MEM physical base address रेजिस्टर of the slot
 *
 */
काष्ठा tpci200_slot अणु
	काष्ठा slot_irq	    *irq;
पूर्ण;

/**
 * काष्ठा tpci200_infos - inक्रमmations specअगरic of the TPCI200 tpci200.
 * @pci_dev		PCI device
 * @पूर्णांकerface_regs	Poपूर्णांकer to IP पूर्णांकerface space (Bar 2)
 * @ioidपूर्णांक_space	Poपूर्णांकer to IP ID, IO and INT space (Bar 3)
 * @mem8_space		Poपूर्णांकer to MEM space (Bar 4)
 *
 */
काष्ठा tpci200_infos अणु
	काष्ठा pci_dev			*pdev;
	काष्ठा pci_device_id		*id_table;
	काष्ठा tpci200_regs __iomem	*पूर्णांकerface_regs;
	व्योम __iomem			*cfg_regs;
	काष्ठा ipack_bus_device		*ipack_bus;
पूर्ण;
काष्ठा tpci200_board अणु
	अचिन्हित पूर्णांक		number;
	काष्ठा mutex		mutex;
	spinlock_t		regs_lock;
	काष्ठा tpci200_slot	*slots;
	काष्ठा tpci200_infos	*info;
	phys_addr_t             mod_mem[IPACK_SPACE_COUNT];
पूर्ण;

#पूर्ण_अगर /* _TPCI200_H_ */
