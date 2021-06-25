<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/समय.स
 *
 * Marvell Orion SoC समय handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_TIME_H
#घोषणा __PLAT_TIME_H

व्योम orion_समय_set_base(व्योम __iomem *समयr_base);

व्योम orion_समय_init(व्योम __iomem *bridge_base, u32 bridge_समयr1_clr_mask,
		     अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक tclk);


#पूर्ण_अगर
