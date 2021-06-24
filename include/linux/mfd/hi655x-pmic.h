<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Device driver क्रम regulators in hi655x IC
 *
 * Copyright (c) 2016 Hisilicon.
 *
 * Authors:
 * Chen Feng <puck.chen@hisilicon.com>
 * Fei  Wang <w.f@huawei.com>
 */

#अगर_अघोषित __HI655X_PMIC_H
#घोषणा __HI655X_PMIC_H

/* Hi655x रेजिस्टरs are mapped to memory bus in 4 bytes stride */
#घोषणा HI655X_STRIDE                   4
#घोषणा HI655X_BUS_ADDR(x)              ((x) << 2)

#घोषणा HI655X_BITS                     8

#घोषणा HI655X_NR_IRQ                   32

#घोषणा HI655X_IRQ_STAT_BASE            (0x003 << 2)
#घोषणा HI655X_IRQ_MASK_BASE            (0x007 << 2)
#घोषणा HI655X_ANA_IRQM_BASE            (0x1b5 << 2)
#घोषणा HI655X_IRQ_ARRAY                4
#घोषणा HI655X_IRQ_MASK                 0xFF
#घोषणा HI655X_IRQ_CLR                  0xFF
#घोषणा HI655X_VER_REG                  0x00

#घोषणा PMU_VER_START                   0x10
#घोषणा PMU_VER_END                     0x38

#घोषणा RESERVE_INT                     7
#घोषणा PWRON_D20R_INT                  6
#घोषणा PWRON_D20F_INT                  5
#घोषणा PWRON_D4SR_INT                  4
#घोषणा VSYS_6P0_D200UR_INT             3
#घोषणा VSYS_UV_D3R_INT                 2
#घोषणा VSYS_2P5_R_INT                  1
#घोषणा OTMP_D1R_INT                    0

#घोषणा RESERVE_INT_MASK                BIT(RESERVE_INT)
#घोषणा PWRON_D20R_INT_MASK             BIT(PWRON_D20R_INT)
#घोषणा PWRON_D20F_INT_MASK             BIT(PWRON_D20F_INT)
#घोषणा PWRON_D4SR_INT_MASK             BIT(PWRON_D4SR_INT)
#घोषणा VSYS_6P0_D200UR_INT_MASK        BIT(VSYS_6P0_D200UR_INT)
#घोषणा VSYS_UV_D3R_INT_MASK            BIT(VSYS_UV_D3R_INT)
#घोषणा VSYS_2P5_R_INT_MASK             BIT(VSYS_2P5_R_INT)
#घोषणा OTMP_D1R_INT_MASK               BIT(OTMP_D1R_INT)

काष्ठा hi655x_pmic अणु
	काष्ठा resource *res;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	पूर्णांक gpio;
	अचिन्हित पूर्णांक ver;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

#पूर्ण_अगर
