<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_ORION5X_MPP_H
#घोषणा __ARCH_ORION5X_MPP_H

#घोषणा MPP(_num, _sel, _in, _out, _F5181l, _F5182, _F5281) ( \
	/* MPP number */		((_num) & 0xff) | \
	/* MPP select value */		(((_sel) & 0xf) << 8) | \
	/* may be input संकेत */	((!!(_in)) << 12) | \
	/* may be output संकेत */	((!!(_out)) << 13) | \
	/* available on F5181l */	((!!(_F5181l)) << 14) | \
	/* available on F5182 */	((!!(_F5182)) << 15) | \
	/* available on F5281 */	((!!(_F5281)) << 16))

				/* num sel  i  o  5181 5182 5281 */

#घोषणा MPP_F5181_MASK		MPP(0,  0x0, 0, 0, 1,   0,   0)
#घोषणा MPP_F5182_MASK		MPP(0,  0x0, 0, 0, 0,   1,   0)
#घोषणा MPP_F5281_MASK		MPP(0,  0x0, 0, 0, 0,   0,   1)

#घोषणा MPP0_UNUSED	        MPP(0,  0x3, 0, 0, 1,   1,   1)
#घोषणा MPP0_GPIO		MPP(0,  0x3, 1, 1, 1,   1,   1)
#घोषणा MPP0_PCIE_RST_OUTn	MPP(0,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP0_PCI_ARB            MPP(0,  0x2, 0, 0, 1,   1,   1)

#घोषणा MPP1_UNUSED		MPP(1,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP1_GPIO		MPP(1,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP1_PCI_ARB            MPP(1,  0x2, 0, 0, 1,   1,   1)

#घोषणा MPP2_UNUSED		MPP(2,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP2_GPIO		MPP(2,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP2_PCI_ARB            MPP(2,  0x2, 0, 0, 1,   1,   1)
#घोषणा MPP2_PCI_PMEn           MPP(2,  0x3, 0, 0, 1,   1,   1)

#घोषणा MPP3_UNUSED		MPP(3,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP3_GPIO		MPP(3,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP3_PCI_ARB            MPP(3,  0x2, 0, 0, 1,   1,   1)

#घोषणा MPP4_UNUSED		MPP(4,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP4_GPIO		MPP(4,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP4_PCI_ARB            MPP(4,  0x2, 0, 0, 1,   1,   1)
#घोषणा MPP4_न_अंकD               MPP(4,  0x4, 0, 0, 0,   1,   1)
#घोषणा MPP4_SATA_LED           MPP(4,  0x5, 0, 0, 0,   1,   0)

#घोषणा MPP5_UNUSED		MPP(5,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP5_GPIO		MPP(5,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP5_PCI_ARB            MPP(5,  0x2, 0, 0, 1,   1,   1)
#घोषणा MPP5_न_अंकD               MPP(5,  0x4, 0, 0, 0,   1,   1)
#घोषणा MPP5_SATA_LED           MPP(5,  0x5, 0, 0, 0,   1,   0)

#घोषणा MPP6_UNUSED		MPP(6,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP6_GPIO		MPP(6,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP6_PCI_ARB            MPP(6,  0x2, 0, 0, 1,   1,   1)
#घोषणा MPP6_न_अंकD               MPP(6,  0x4, 0, 0, 0,   1,   1)
#घोषणा MPP6_PCI_CLK            MPP(6,  0x5, 0, 0, 1,   0,   0)
#घोषणा MPP6_SATA_LED           MPP(6,  0x5, 0, 0, 0,   1,   0)

#घोषणा MPP7_UNUSED		MPP(7,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP7_GPIO		MPP(7,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP7_PCI_ARB            MPP(7,  0x2, 0, 0, 1,   1,   1)
#घोषणा MPP7_न_अंकD               MPP(7,  0x4, 0, 0, 0,   1,   1)
#घोषणा MPP7_PCI_CLK            MPP(7,  0x5, 0, 0, 1,   0,   0)
#घोषणा MPP7_SATA_LED           MPP(7,  0x5, 0, 0, 0,   1,   0)

#घोषणा MPP8_UNUSED		MPP(8,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP8_GPIO		MPP(8,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP8_GIGE               MPP(8,  0x1, 0, 0, 1,   1,   1)

#घोषणा MPP9_UNUSED		MPP(9,  0x0, 0, 0, 1,   1,   1)
#घोषणा MPP9_GPIO		MPP(9,  0x0, 1, 1, 1,   1,   1)
#घोषणा MPP9_GIGE               MPP(9,  0x1, 0, 0, 1,   1,   1)

#घोषणा MPP10_UNUSED		MPP(10, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP10_GPIO		MPP(10, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP10_GIGE              MPP(10, 0x1, 0, 0, 1,   1,   1)

#घोषणा MPP11_UNUSED		MPP(11, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP11_GPIO		MPP(11, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP11_GIGE              MPP(11, 0x1, 0, 0, 1,   1,   1)

#घोषणा MPP12_UNUSED		MPP(12, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP12_GPIO		MPP(12, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP12_GIGE              MPP(12, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP12_न_अंकD              MPP(12, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP12_SATA_LED          MPP(12, 0x5, 0, 0, 0,   1,   0)

#घोषणा MPP13_UNUSED		MPP(13, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP13_GPIO		MPP(13, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP13_GIGE              MPP(13, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP13_न_अंकD              MPP(13, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP13_SATA_LED          MPP(13, 0x5, 0, 0, 0,   1,   0)

#घोषणा MPP14_UNUSED		MPP(14, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP14_GPIO		MPP(14, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP14_GIGE              MPP(14, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP14_न_अंकD              MPP(14, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP14_SATA_LED          MPP(14, 0x5, 0, 0, 0,   1,   0)

#घोषणा MPP15_UNUSED		MPP(15, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP15_GPIO		MPP(15, 0x0, 1, 1, 1,   1,   1)
#घोषणा MPP15_GIGE              MPP(15, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP15_न_अंकD              MPP(15, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP15_SATA_LED          MPP(15, 0x5, 0, 0, 0,   1,   0)

#घोषणा MPP16_UNUSED		MPP(16, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP16_GPIO		MPP(16, 0x5, 1, 1, 0,   1,   0)
#घोषणा MPP16_GIGE              MPP(16, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP16_न_अंकD              MPP(16, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP16_UART              MPP(16, 0x0, 0, 0, 0,   1,   1)

#घोषणा MPP17_UNUSED		MPP(17, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP17_GPIO		MPP(17, 0x5, 1, 1, 0,   1,   0)
#घोषणा MPP17_GIGE              MPP(17, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP17_न_अंकD              MPP(17, 0x4, 0, 0, 0,   1,   1)
#घोषणा MPP17_UART              MPP(17, 0x0, 0, 0, 0,   1,   1)

#घोषणा MPP18_UNUSED		MPP(18, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP18_GPIO		MPP(18, 0x5, 1, 1, 0,   1,   0)
#घोषणा MPP18_GIGE              MPP(18, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP18_UART              MPP(18, 0x0, 0, 0, 0,   1,   1)

#घोषणा MPP19_UNUSED		MPP(19, 0x0, 0, 0, 1,   1,   1)
#घोषणा MPP19_GPIO		MPP(19, 0x5, 1, 1, 0,   1,   0)
#घोषणा MPP19_GIGE              MPP(19, 0x1, 0, 0, 1,   1,   1)
#घोषणा MPP19_UART              MPP(19, 0x0, 0, 0, 0,   1,   1)

#घोषणा MPP_MAX			19

व्योम orion5x_mpp_conf(अचिन्हित पूर्णांक *mpp_list);

#पूर्ण_अगर
