<शैली गुरु>
/*
 * PCI Register definitions क्रम the MIPS System Controller.
 *
 * Copyright (C) 2004 MIPS Technologies, Inc.  All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित __ASM_MIPS_BOARDS_MSC01_IC_H
#घोषणा __ASM_MIPS_BOARDS_MSC01_IC_H

/*****************************************************************************
 * Register offset addresses
 *****************************************************************************/

#घोषणा MSC01_IC_RST_OFS     0x00008	/* Software reset	       */
#घोषणा MSC01_IC_ENAL_OFS    0x00100	/* Int_in enable mask 31:0     */
#घोषणा MSC01_IC_ENAH_OFS    0x00108	/* Int_in enable mask 63:32    */
#घोषणा MSC01_IC_DISL_OFS    0x00120	/* Int_in disable mask 31:0    */
#घोषणा MSC01_IC_DISH_OFS    0x00128	/* Int_in disable mask 63:32   */
#घोषणा MSC01_IC_ISBL_OFS    0x00140	/* Raw पूर्णांक_in 31:0	       */
#घोषणा MSC01_IC_ISBH_OFS    0x00148	/* Raw पूर्णांक_in 63:32	       */
#घोषणा MSC01_IC_ISAL_OFS    0x00160	/* Masked पूर्णांक_in 31:0	       */
#घोषणा MSC01_IC_ISAH_OFS    0x00168	/* Masked पूर्णांक_in 63:32	       */
#घोषणा MSC01_IC_LVL_OFS     0x00180	/* Disable priority पूर्णांक_out    */
#घोषणा MSC01_IC_RAMW_OFS    0x00180	/* Shaकरोw set RAM (EI)	       */
#घोषणा MSC01_IC_OSB_OFS     0x00188	/* Raw पूर्णांक_out		       */
#घोषणा MSC01_IC_OSA_OFS     0x00190	/* Masked पूर्णांक_out	       */
#घोषणा MSC01_IC_GENA_OFS    0x00198	/* Global HW पूर्णांक enable	       */
#घोषणा MSC01_IC_BASE_OFS    0x001a0	/* Base address of IC_VEC      */
#घोषणा MSC01_IC_VEC_OFS     0x001b0	/* Active पूर्णांक's vector address */
#घोषणा MSC01_IC_EOI_OFS     0x001c0	/* Enable lower level पूर्णांकs     */
#घोषणा MSC01_IC_CFG_OFS     0x001c8	/* Configuration रेजिस्टर      */
#घोषणा MSC01_IC_TRLD_OFS    0x001d0	/* Interval समयr reload val   */
#घोषणा MSC01_IC_TVAL_OFS    0x001e0	/* Interval समयr current val  */
#घोषणा MSC01_IC_TCFG_OFS    0x001f0	/* Interval समयr config       */
#घोषणा MSC01_IC_SUP_OFS     0x00200	/* Set up पूर्णांक_in line 0	       */
#घोषणा MSC01_IC_ENA_OFS     0x00800	/* Int_in enable mask 63:0     */
#घोषणा MSC01_IC_DIS_OFS     0x00820	/* Int_in disable mask 63:0    */
#घोषणा MSC01_IC_ISB_OFS     0x00840	/* Raw पूर्णांक_in 63:0	       */
#घोषणा MSC01_IC_ISA_OFS     0x00860	/* Masked पूर्णांक_in 63:0	       */

/*****************************************************************************
 * Register field encodings
 *****************************************************************************/

#घोषणा MSC01_IC_RST_RST_SHF	  0
#घोषणा MSC01_IC_RST_RST_MSK	  0x00000001
#घोषणा MSC01_IC_RST_RST_BIT	  MSC01_IC_RST_RST_MSK
#घोषणा MSC01_IC_LVL_LVL_SHF	  0
#घोषणा MSC01_IC_LVL_LVL_MSK	  0x000000ff
#घोषणा MSC01_IC_LVL_SPUR_SHF	  16
#घोषणा MSC01_IC_LVL_SPUR_MSK	  0x00010000
#घोषणा MSC01_IC_LVL_SPUR_BIT	  MSC01_IC_LVL_SPUR_MSK
#घोषणा MSC01_IC_RAMW_RIPL_SHF	  0
#घोषणा MSC01_IC_RAMW_RIPL_MSK	  0x0000003f
#घोषणा MSC01_IC_RAMW_DATA_SHF	  6
#घोषणा MSC01_IC_RAMW_DATA_MSK	  0x00000fc0
#घोषणा MSC01_IC_RAMW_ADDR_SHF	  25
#घोषणा MSC01_IC_RAMW_ADDR_MSK	  0x7e000000
#घोषणा MSC01_IC_RAMW_READ_SHF	  31
#घोषणा MSC01_IC_RAMW_READ_MSK	  0x80000000
#घोषणा MSC01_IC_RAMW_READ_BIT	  MSC01_IC_RAMW_READ_MSK
#घोषणा MSC01_IC_OSB_OSB_SHF	  0
#घोषणा MSC01_IC_OSB_OSB_MSK	  0x000000ff
#घोषणा MSC01_IC_OSA_OSA_SHF	  0
#घोषणा MSC01_IC_OSA_OSA_MSK	  0x000000ff
#घोषणा MSC01_IC_GENA_GENA_SHF	  0
#घोषणा MSC01_IC_GENA_GENA_MSK	  0x00000001
#घोषणा MSC01_IC_GENA_GENA_BIT	  MSC01_IC_GENA_GENA_MSK
#घोषणा MSC01_IC_CFG_DIS_SHF	  0
#घोषणा MSC01_IC_CFG_DIS_MSK	  0x00000001
#घोषणा MSC01_IC_CFG_DIS_BIT	  MSC01_IC_CFG_DIS_MSK
#घोषणा MSC01_IC_CFG_SHFT_SHF	  8
#घोषणा MSC01_IC_CFG_SHFT_MSK	  0x00000f00
#घोषणा MSC01_IC_TCFG_ENA_SHF	  0
#घोषणा MSC01_IC_TCFG_ENA_MSK	  0x00000001
#घोषणा MSC01_IC_TCFG_ENA_BIT	  MSC01_IC_TCFG_ENA_MSK
#घोषणा MSC01_IC_TCFG_INT_SHF	  8
#घोषणा MSC01_IC_TCFG_INT_MSK	  0x00000100
#घोषणा MSC01_IC_TCFG_INT_BIT	  MSC01_IC_TCFG_INT_MSK
#घोषणा MSC01_IC_TCFG_EDGE_SHF	  16
#घोषणा MSC01_IC_TCFG_EDGE_MSK	  0x00010000
#घोषणा MSC01_IC_TCFG_EDGE_BIT	  MSC01_IC_TCFG_EDGE_MSK
#घोषणा MSC01_IC_SUP_PRI_SHF	  0
#घोषणा MSC01_IC_SUP_PRI_MSK	  0x00000007
#घोषणा MSC01_IC_SUP_EDGE_SHF	  8
#घोषणा MSC01_IC_SUP_EDGE_MSK	  0x00000100
#घोषणा MSC01_IC_SUP_EDGE_BIT	  MSC01_IC_SUP_EDGE_MSK
#घोषणा MSC01_IC_SUP_STEP	  8

/*
 * MIPS System controller पूर्णांकerrupt रेजिस्टर base.
 *
 */

/*****************************************************************************
 * Absolute रेजिस्टर addresses
 *****************************************************************************/

#घोषणा MSC01_IC_RST	 (MSC01_IC_REG_BASE + MSC01_IC_RST_OFS)
#घोषणा MSC01_IC_ENAL	 (MSC01_IC_REG_BASE + MSC01_IC_ENAL_OFS)
#घोषणा MSC01_IC_ENAH	 (MSC01_IC_REG_BASE + MSC01_IC_ENAH_OFS)
#घोषणा MSC01_IC_DISL	 (MSC01_IC_REG_BASE + MSC01_IC_DISL_OFS)
#घोषणा MSC01_IC_DISH	 (MSC01_IC_REG_BASE + MSC01_IC_DISH_OFS)
#घोषणा MSC01_IC_ISBL	 (MSC01_IC_REG_BASE + MSC01_IC_ISBL_OFS)
#घोषणा MSC01_IC_ISBH	 (MSC01_IC_REG_BASE + MSC01_IC_ISBH_OFS)
#घोषणा MSC01_IC_ISAL	 (MSC01_IC_REG_BASE + MSC01_IC_ISAL_OFS)
#घोषणा MSC01_IC_ISAH	 (MSC01_IC_REG_BASE + MSC01_IC_ISAH_OFS)
#घोषणा MSC01_IC_LVL	 (MSC01_IC_REG_BASE + MSC01_IC_LVL_OFS)
#घोषणा MSC01_IC_RAMW	 (MSC01_IC_REG_BASE + MSC01_IC_RAMW_OFS)
#घोषणा MSC01_IC_OSB	 (MSC01_IC_REG_BASE + MSC01_IC_OSB_OFS)
#घोषणा MSC01_IC_OSA	 (MSC01_IC_REG_BASE + MSC01_IC_OSA_OFS)
#घोषणा MSC01_IC_GENA	 (MSC01_IC_REG_BASE + MSC01_IC_GENA_OFS)
#घोषणा MSC01_IC_BASE	 (MSC01_IC_REG_BASE + MSC01_IC_BASE_OFS)
#घोषणा MSC01_IC_VEC	 (MSC01_IC_REG_BASE + MSC01_IC_VEC_OFS)
#घोषणा MSC01_IC_EOI	 (MSC01_IC_REG_BASE + MSC01_IC_EOI_OFS)
#घोषणा MSC01_IC_CFG	 (MSC01_IC_REG_BASE + MSC01_IC_CFG_OFS)
#घोषणा MSC01_IC_TRLD	 (MSC01_IC_REG_BASE + MSC01_IC_TRLD_OFS)
#घोषणा MSC01_IC_TVAL	 (MSC01_IC_REG_BASE + MSC01_IC_TVAL_OFS)
#घोषणा MSC01_IC_TCFG	 (MSC01_IC_REG_BASE + MSC01_IC_TCFG_OFS)
#घोषणा MSC01_IC_SUP	 (MSC01_IC_REG_BASE + MSC01_IC_SUP_OFS)
#घोषणा MSC01_IC_ENA	 (MSC01_IC_REG_BASE + MSC01_IC_ENA_OFS)
#घोषणा MSC01_IC_DIS	 (MSC01_IC_REG_BASE + MSC01_IC_DIS_OFS)
#घोषणा MSC01_IC_ISB	 (MSC01_IC_REG_BASE + MSC01_IC_ISB_OFS)
#घोषणा MSC01_IC_ISA	 (MSC01_IC_REG_BASE + MSC01_IC_ISA_OFS)

/*
 * Soc-it पूर्णांकerrupts are configurable.
 * Every board describes its IRQ mapping with this table.
 */
प्रकार काष्ठा msc_irqmap अणु
	पूर्णांक	im_irq;
	पूर्णांक	im_type;
	पूर्णांक	im_lvl;
पूर्ण msc_irqmap_t;

/* im_type */
#घोषणा MSC01_IRQ_LEVEL		0
#घोषणा MSC01_IRQ_EDGE		1

बाह्य व्योम __init init_msc_irqs(अचिन्हित दीर्घ icubase, अचिन्हित पूर्णांक base, msc_irqmap_t *imp, पूर्णांक nirq);
बाह्य व्योम ll_msc_irq(व्योम);

#पूर्ण_अगर /* __ASM_MIPS_BOARDS_MSC01_IC_H */
