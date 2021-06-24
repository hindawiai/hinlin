<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IA64_MSI_DEF_H
#घोषणा _IA64_MSI_DEF_H

/*
 * Shअगरts क्रम APIC-based data
 */

#घोषणा     MSI_DATA_VECTOR_SHIFT	0
#घोषणा	    MSI_DATA_VECTOR(v)		(((u8)v) << MSI_DATA_VECTOR_SHIFT)
#घोषणा     MSI_DATA_VECTOR_MASK	0xffffff00

#घोषणा     MSI_DATA_DELIVERY_MODE_SHIFT	8
#घोषणा     MSI_DATA_DELIVERY_FIXED	(0 << MSI_DATA_DELIVERY_MODE_SHIFT)
#घोषणा     MSI_DATA_DELIVERY_LOWPRI	(1 << MSI_DATA_DELIVERY_MODE_SHIFT)

#घोषणा     MSI_DATA_LEVEL_SHIFT	14
#घोषणा     MSI_DATA_LEVEL_DEASSERT	(0 << MSI_DATA_LEVEL_SHIFT)
#घोषणा     MSI_DATA_LEVEL_ASSERT	(1 << MSI_DATA_LEVEL_SHIFT)

#घोषणा     MSI_DATA_TRIGGER_SHIFT	15
#घोषणा     MSI_DATA_TRIGGER_EDGE	(0 << MSI_DATA_TRIGGER_SHIFT)
#घोषणा     MSI_DATA_TRIGGER_LEVEL	(1 << MSI_DATA_TRIGGER_SHIFT)

/*
 * Shअगरt/mask fields क्रम APIC-based bus address
 */

#घोषणा     MSI_ADDR_DEST_ID_SHIFT	4
#घोषणा     MSI_ADDR_HEADER		0xfee00000

#घोषणा     MSI_ADDR_DEST_ID_MASK	0xfff0000f
#घोषणा     MSI_ADDR_DEST_ID_CPU(cpu)	((cpu) << MSI_ADDR_DEST_ID_SHIFT)

#घोषणा     MSI_ADDR_DEST_MODE_SHIFT	2
#घोषणा     MSI_ADDR_DEST_MODE_PHYS	(0 << MSI_ADDR_DEST_MODE_SHIFT)
#घोषणा	    MSI_ADDR_DEST_MODE_LOGIC	(1 << MSI_ADDR_DEST_MODE_SHIFT)

#घोषणा     MSI_ADDR_REसूचीECTION_SHIFT	3
#घोषणा     MSI_ADDR_REसूचीECTION_CPU	(0 << MSI_ADDR_REसूचीECTION_SHIFT)
#घोषणा     MSI_ADDR_REसूचीECTION_LOWPRI	(1 << MSI_ADDR_REसूचीECTION_SHIFT)

#पूर्ण_अगर/* _IA64_MSI_DEF_H */
