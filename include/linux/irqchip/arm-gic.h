<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  include/linux/irqchip/arm-gic.h
 *
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 */
#अगर_अघोषित __LINUX_IRQCHIP_ARM_GIC_H
#घोषणा __LINUX_IRQCHIP_ARM_GIC_H

#घोषणा GIC_CPU_CTRL			0x00
#घोषणा GIC_CPU_PRIMASK			0x04
#घोषणा GIC_CPU_BINPOINT		0x08
#घोषणा GIC_CPU_INTACK			0x0c
#घोषणा GIC_CPU_EOI			0x10
#घोषणा GIC_CPU_RUNNINGPRI		0x14
#घोषणा GIC_CPU_HIGHPRI			0x18
#घोषणा GIC_CPU_ALIAS_BINPOINT		0x1c
#घोषणा GIC_CPU_ACTIVEPRIO		0xd0
#घोषणा GIC_CPU_IDENT			0xfc
#घोषणा GIC_CPU_DEACTIVATE		0x1000

#घोषणा GICC_ENABLE			0x1
#घोषणा GICC_INT_PRI_THRESHOLD		0xf0

#घोषणा GIC_CPU_CTRL_EnableGrp0_SHIFT	0
#घोषणा GIC_CPU_CTRL_EnableGrp0		(1 << GIC_CPU_CTRL_EnableGrp0_SHIFT)
#घोषणा GIC_CPU_CTRL_EnableGrp1_SHIFT	1
#घोषणा GIC_CPU_CTRL_EnableGrp1		(1 << GIC_CPU_CTRL_EnableGrp1_SHIFT)
#घोषणा GIC_CPU_CTRL_AckCtl_SHIFT	2
#घोषणा GIC_CPU_CTRL_AckCtl		(1 << GIC_CPU_CTRL_AckCtl_SHIFT)
#घोषणा GIC_CPU_CTRL_FIQEn_SHIFT	3
#घोषणा GIC_CPU_CTRL_FIQEn		(1 << GIC_CPU_CTRL_FIQEn_SHIFT)
#घोषणा GIC_CPU_CTRL_CBPR_SHIFT		4
#घोषणा GIC_CPU_CTRL_CBPR		(1 << GIC_CPU_CTRL_CBPR_SHIFT)
#घोषणा GIC_CPU_CTRL_EOImodeNS_SHIFT	9
#घोषणा GIC_CPU_CTRL_EOImodeNS		(1 << GIC_CPU_CTRL_EOImodeNS_SHIFT)

#घोषणा GICC_IAR_INT_ID_MASK		0x3ff
#घोषणा GICC_INT_SPURIOUS		1023
#घोषणा GICC_DIS_BYPASS_MASK		0x1e0

#घोषणा GIC_DIST_CTRL			0x000
#घोषणा GIC_DIST_CTR			0x004
#घोषणा GIC_DIST_IIDR			0x008
#घोषणा GIC_DIST_IGROUP			0x080
#घोषणा GIC_DIST_ENABLE_SET		0x100
#घोषणा GIC_DIST_ENABLE_CLEAR		0x180
#घोषणा GIC_DIST_PENDING_SET		0x200
#घोषणा GIC_DIST_PENDING_CLEAR		0x280
#घोषणा GIC_DIST_ACTIVE_SET		0x300
#घोषणा GIC_DIST_ACTIVE_CLEAR		0x380
#घोषणा GIC_DIST_PRI			0x400
#घोषणा GIC_DIST_TARGET			0x800
#घोषणा GIC_DIST_CONFIG			0xc00
#घोषणा GIC_DIST_SOFTINT		0xf00
#घोषणा GIC_DIST_SGI_PENDING_CLEAR	0xf10
#घोषणा GIC_DIST_SGI_PENDING_SET	0xf20

#घोषणा GICD_ENABLE			0x1
#घोषणा GICD_DISABLE			0x0
#घोषणा GICD_INT_ACTLOW_LVLTRIG		0x0
#घोषणा GICD_INT_EN_CLR_X32		0xffffffff
#घोषणा GICD_INT_EN_SET_SGI		0x0000ffff
#घोषणा GICD_INT_EN_CLR_PPI		0xffff0000

#घोषणा GICD_IIDR_IMPLEMENTER_SHIFT	0
#घोषणा GICD_IIDR_IMPLEMENTER_MASK	(0xfff << GICD_IIDR_IMPLEMENTER_SHIFT)
#घोषणा GICD_IIDR_REVISION_SHIFT	12
#घोषणा GICD_IIDR_REVISION_MASK		(0xf << GICD_IIDR_REVISION_SHIFT)
#घोषणा GICD_IIDR_VARIANT_SHIFT		16
#घोषणा GICD_IIDR_VARIANT_MASK		(0xf << GICD_IIDR_VARIANT_SHIFT)
#घोषणा GICD_IIDR_PRODUCT_ID_SHIFT	24
#घोषणा GICD_IIDR_PRODUCT_ID_MASK	(0xff << GICD_IIDR_PRODUCT_ID_SHIFT)


#घोषणा GICH_HCR			0x0
#घोषणा GICH_VTR			0x4
#घोषणा GICH_VMCR			0x8
#घोषणा GICH_MISR			0x10
#घोषणा GICH_EISR0 			0x20
#घोषणा GICH_EISR1 			0x24
#घोषणा GICH_ELRSR0 			0x30
#घोषणा GICH_ELRSR1 			0x34
#घोषणा GICH_APR			0xf0
#घोषणा GICH_LR0			0x100

#घोषणा GICH_HCR_EN			(1 << 0)
#घोषणा GICH_HCR_UIE			(1 << 1)
#घोषणा GICH_HCR_NPIE			(1 << 3)

#घोषणा GICH_LR_VIRTUALID		(0x3ff << 0)
#घोषणा GICH_LR_PHYSID_CPUID_SHIFT	(10)
#घोषणा GICH_LR_PHYSID_CPUID		(0x3ff << GICH_LR_PHYSID_CPUID_SHIFT)
#घोषणा GICH_LR_PRIORITY_SHIFT		23
#घोषणा GICH_LR_STATE			(3 << 28)
#घोषणा GICH_LR_PENDING_BIT		(1 << 28)
#घोषणा GICH_LR_ACTIVE_BIT		(1 << 29)
#घोषणा GICH_LR_EOI			(1 << 19)
#घोषणा GICH_LR_GROUP1			(1 << 30)
#घोषणा GICH_LR_HW			(1 << 31)

#घोषणा GICH_VMCR_ENABLE_GRP0_SHIFT	0
#घोषणा GICH_VMCR_ENABLE_GRP0_MASK	(1 << GICH_VMCR_ENABLE_GRP0_SHIFT)
#घोषणा GICH_VMCR_ENABLE_GRP1_SHIFT	1
#घोषणा GICH_VMCR_ENABLE_GRP1_MASK	(1 << GICH_VMCR_ENABLE_GRP1_SHIFT)
#घोषणा GICH_VMCR_ACK_CTL_SHIFT		2
#घोषणा GICH_VMCR_ACK_CTL_MASK		(1 << GICH_VMCR_ACK_CTL_SHIFT)
#घोषणा GICH_VMCR_FIQ_EN_SHIFT		3
#घोषणा GICH_VMCR_FIQ_EN_MASK		(1 << GICH_VMCR_FIQ_EN_SHIFT)
#घोषणा GICH_VMCR_CBPR_SHIFT		4
#घोषणा GICH_VMCR_CBPR_MASK		(1 << GICH_VMCR_CBPR_SHIFT)
#घोषणा GICH_VMCR_EOI_MODE_SHIFT	9
#घोषणा GICH_VMCR_EOI_MODE_MASK		(1 << GICH_VMCR_EOI_MODE_SHIFT)

#घोषणा GICH_VMCR_PRIMASK_SHIFT		27
#घोषणा GICH_VMCR_PRIMASK_MASK		(0x1f << GICH_VMCR_PRIMASK_SHIFT)
#घोषणा GICH_VMCR_BINPOINT_SHIFT	21
#घोषणा GICH_VMCR_BINPOINT_MASK		(0x7 << GICH_VMCR_BINPOINT_SHIFT)
#घोषणा GICH_VMCR_ALIAS_BINPOINT_SHIFT	18
#घोषणा GICH_VMCR_ALIAS_BINPOINT_MASK	(0x7 << GICH_VMCR_ALIAS_BINPOINT_SHIFT)

#घोषणा GICH_MISR_EOI			(1 << 0)
#घोषणा GICH_MISR_U			(1 << 1)

#घोषणा GICV_PMR_PRIORITY_SHIFT		3
#घोषणा GICV_PMR_PRIORITY_MASK		(0x1f << GICV_PMR_PRIORITY_SHIFT)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/irqकरोमुख्य.h>

काष्ठा device_node;
काष्ठा gic_chip_data;

व्योम gic_cascade_irq(अचिन्हित पूर्णांक gic_nr, अचिन्हित पूर्णांक irq);
पूर्णांक gic_cpu_अगर_करोwn(अचिन्हित पूर्णांक gic_nr);
व्योम gic_cpu_save(काष्ठा gic_chip_data *gic);
व्योम gic_cpu_restore(काष्ठा gic_chip_data *gic);
व्योम gic_dist_save(काष्ठा gic_chip_data *gic);
व्योम gic_dist_restore(काष्ठा gic_chip_data *gic);

/*
 * Subdrivers that need some preparatory work can initialize their
 * chips and call this to रेजिस्टर their GICs.
 */
पूर्णांक gic_of_init(काष्ठा device_node *node, काष्ठा device_node *parent);

/*
 * Initialises and रेजिस्टरs a non-root or child GIC chip. Memory क्रम
 * the gic_chip_data काष्ठाure is dynamically allocated.
 */
पूर्णांक gic_of_init_child(काष्ठा device *dev, काष्ठा gic_chip_data **gic, पूर्णांक irq);

/*
 * Legacy platक्रमms not converted to DT yet must use this to init
 * their GIC
 */
व्योम gic_init(व्योम __iomem *dist , व्योम __iomem *cpu);

व्योम gic_send_sgi(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक irq);
पूर्णांक gic_get_cpu_id(अचिन्हित पूर्णांक cpu);
व्योम gic_migrate_target(अचिन्हित पूर्णांक new_cpu_id);
अचिन्हित दीर्घ gic_get_sgir_physaddr(व्योम);

#पूर्ण_अगर /* __ASSEMBLY */
#पूर्ण_अगर
