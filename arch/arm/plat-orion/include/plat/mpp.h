<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/mpp.h
 *
 * Marvell Orion SoC MPP handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_MPP_H
#घोषणा __PLAT_MPP_H

#घोषणा MPP_NUM(x)	((x) & 0xff)
#घोषणा MPP_SEL(x)	(((x) >> 8) & 0xf)

/* This is the generic MPP macro, without any variant inक्रमmation.
   Each machine architecture is expected to extend this with further
   bit fields indicating which MPP configurations are valid क्रम a
   specअगरic variant. */

#घोषणा GENERIC_MPP(_num, _sel, _in, _out) ( \
	/* MPP number */		((_num) & 0xff) | \
	/* MPP select value */		(((_sel) & 0xf) << 8) | \
	/* may be input संकेत */	((!!(_in)) << 12) | \
	/* may be output संकेत */	((!!(_out)) << 13))

#घोषणा MPP_INPUT_MASK		GENERIC_MPP(0, 0x0, 1, 0)
#घोषणा MPP_OUTPUT_MASK		GENERIC_MPP(0, 0x0, 0, 1)

व्योम __init orion_mpp_conf(अचिन्हित पूर्णांक *mpp_list, अचिन्हित पूर्णांक variant_mask,
			   अचिन्हित पूर्णांक mpp_max, व्योम __iomem *dev_bus);

#पूर्ण_अगर
