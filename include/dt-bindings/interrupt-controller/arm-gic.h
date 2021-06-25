<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * This header provides स्थिरants क्रम the ARM GIC.
 */

#अगर_अघोषित _DT_BINDINGS_INTERRUPT_CONTROLLER_ARM_GIC_H
#घोषणा _DT_BINDINGS_INTERRUPT_CONTROLLER_ARM_GIC_H

#समावेश <dt-bindings/पूर्णांकerrupt-controller/irq.h>

/* पूर्णांकerrupt specअगरier cell 0 */

#घोषणा GIC_SPI 0
#घोषणा GIC_PPI 1

/*
 * Interrupt specअगरier cell 2.
 * The flags in irq.h are valid, plus those below.
 */
#घोषणा GIC_CPU_MASK_RAW(x) ((x) << 8)
#घोषणा GIC_CPU_MASK_SIMPLE(num) GIC_CPU_MASK_RAW((1 << (num)) - 1)

#पूर्ण_अगर
