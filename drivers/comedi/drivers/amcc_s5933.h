<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Stuff क्रम AMCC S5933 PCI Controller
 *
 * Author: Michal Dobes <करोbes@tesnet.cz>
 *
 * Inspirated from general-purpose AMCC S5933 PCI Matchmaker driver
 * made by Andrea Cisternino  <acister@pcape1.pi.infn.it>
 * and as result of espionage from MITE code made by David A. Schleef.
 * Thanks to AMCC क्रम their on-line करोcumentation and bus master DMA
 * example.
 */

#अगर_अघोषित _AMCC_S5933_H_
#घोषणा _AMCC_S5933_H_

/****************************************************************************/
/* AMCC Operation Register Offsets - PCI                                    */
/****************************************************************************/

#घोषणा AMCC_OP_REG_OMB1         0x00
#घोषणा AMCC_OP_REG_OMB2         0x04
#घोषणा AMCC_OP_REG_OMB3         0x08
#घोषणा AMCC_OP_REG_OMB4         0x0c
#घोषणा AMCC_OP_REG_IMB1         0x10
#घोषणा AMCC_OP_REG_IMB2         0x14
#घोषणा AMCC_OP_REG_IMB3         0x18
#घोषणा AMCC_OP_REG_IMB4         0x1c
#घोषणा AMCC_OP_REG_FIFO         0x20
#घोषणा AMCC_OP_REG_MWAR         0x24
#घोषणा AMCC_OP_REG_MWTC         0x28
#घोषणा AMCC_OP_REG_MRAR         0x2c
#घोषणा AMCC_OP_REG_MRTC         0x30
#घोषणा AMCC_OP_REG_MBEF         0x34
#घोषणा AMCC_OP_REG_INTCSR       0x38
#घोषणा  AMCC_OP_REG_INTCSR_SRC  (AMCC_OP_REG_INTCSR + 2)	/* INT source */
#घोषणा  AMCC_OP_REG_INTCSR_FEC  (AMCC_OP_REG_INTCSR + 3)	/* FIFO ctrl */
#घोषणा AMCC_OP_REG_MCSR         0x3c
#घोषणा  AMCC_OP_REG_MCSR_NVDATA (AMCC_OP_REG_MCSR + 2)	/* Data in byte 2 */
#घोषणा  AMCC_OP_REG_MCSR_NVCMD  (AMCC_OP_REG_MCSR + 3)	/* Command in byte 3 */

#घोषणा AMCC_FIFO_DEPTH_DWORD	8
#घोषणा AMCC_FIFO_DEPTH_BYTES	(8 * माप(u32))

/****************************************************************************/
/* AMCC - PCI Interrupt Control/Status Register                            */
/****************************************************************************/
#घोषणा INTCSR_OUTBOX_BYTE(x)	((x) & 0x3)
#घोषणा INTCSR_OUTBOX_SELECT(x)	(((x) & 0x3) << 2)
#घोषणा INTCSR_OUTBOX_EMPTY_INT	0x10	/*  enable outbox empty पूर्णांकerrupt */
#घोषणा INTCSR_INBOX_BYTE(x)	(((x) & 0x3) << 8)
#घोषणा INTCSR_INBOX_SELECT(x)	(((x) & 0x3) << 10)
#घोषणा INTCSR_INBOX_FULL_INT	0x1000	/*  enable inbox full पूर्णांकerrupt */
/* पढ़ो, or ग_लिखो clear inbox full पूर्णांकerrupt */
#घोषणा INTCSR_INBOX_INTR_STATUS	0x20000
/* पढ़ो only, पूर्णांकerrupt निश्चितed */
#घोषणा INTCSR_INTR_ASSERTED	0x800000

/****************************************************************************/
/* AMCC - PCI non-अस्थिर ram command रेजिस्टर (byte 3 of AMCC_OP_REG_MCSR) */
/****************************************************************************/
#घोषणा MCSR_NV_LOAD_LOW_ADDR	0x0
#घोषणा MCSR_NV_LOAD_HIGH_ADDR	0x20
#घोषणा MCSR_NV_WRITE	0x40
#घोषणा MCSR_NV_READ	0x60
#घोषणा MCSR_NV_MASK	0x60
#घोषणा MCSR_NV_ENABLE	0x80
#घोषणा MCSR_NV_BUSY	MCSR_NV_ENABLE

/****************************************************************************/
/* AMCC Operation Registers Size - PCI                                      */
/****************************************************************************/

#घोषणा AMCC_OP_REG_SIZE	 64	/* in bytes */

/****************************************************************************/
/* AMCC Operation Register Offsets - Add-on                                 */
/****************************************************************************/

#घोषणा AMCC_OP_REG_AIMB1         0x00
#घोषणा AMCC_OP_REG_AIMB2         0x04
#घोषणा AMCC_OP_REG_AIMB3         0x08
#घोषणा AMCC_OP_REG_AIMB4         0x0c
#घोषणा AMCC_OP_REG_AOMB1         0x10
#घोषणा AMCC_OP_REG_AOMB2         0x14
#घोषणा AMCC_OP_REG_AOMB3         0x18
#घोषणा AMCC_OP_REG_AOMB4         0x1c
#घोषणा AMCC_OP_REG_AFIFO         0x20
#घोषणा AMCC_OP_REG_AMWAR         0x24
#घोषणा AMCC_OP_REG_APTA          0x28
#घोषणा AMCC_OP_REG_APTD          0x2c
#घोषणा AMCC_OP_REG_AMRAR         0x30
#घोषणा AMCC_OP_REG_AMBEF         0x34
#घोषणा AMCC_OP_REG_AINT          0x38
#घोषणा AMCC_OP_REG_AGCSTS        0x3c
#घोषणा AMCC_OP_REG_AMWTC         0x58
#घोषणा AMCC_OP_REG_AMRTC         0x5c

/****************************************************************************/
/* AMCC - Add-on General Control/Status Register                            */
/****************************************************************************/

#घोषणा AGCSTS_CONTROL_MASK	0xfffff000
#घोषणा  AGCSTS_NV_ACC_MASK	0xe0000000
#घोषणा  AGCSTS_RESET_MASK	0x0e000000
#घोषणा  AGCSTS_NV_DA_MASK	0x00ff0000
#घोषणा  AGCSTS_BIST_MASK	0x0000f000
#घोषणा AGCSTS_STATUS_MASK	0x000000ff
#घोषणा  AGCSTS_TCZERO_MASK	0x000000c0
#घोषणा  AGCSTS_FIFO_ST_MASK	0x0000003f

#घोषणा AGCSTS_TC_ENABLE	0x10000000

#घोषणा AGCSTS_RESET_MBFLAGS	0x08000000
#घोषणा AGCSTS_RESET_P2A_FIFO	0x04000000
#घोषणा AGCSTS_RESET_A2P_FIFO	0x02000000
#घोषणा AGCSTS_RESET_FIFOS	(AGCSTS_RESET_A2P_FIFO | AGCSTS_RESET_P2A_FIFO)

#घोषणा AGCSTS_A2P_TCOUNT	0x00000080
#घोषणा AGCSTS_P2A_TCOUNT	0x00000040

#घोषणा AGCSTS_FS_P2A_EMPTY	0x00000020
#घोषणा AGCSTS_FS_P2A_HALF	0x00000010
#घोषणा AGCSTS_FS_P2A_FULL	0x00000008

#घोषणा AGCSTS_FS_A2P_EMPTY	0x00000004
#घोषणा AGCSTS_FS_A2P_HALF	0x00000002
#घोषणा AGCSTS_FS_A2P_FULL	0x00000001

/****************************************************************************/
/* AMCC - Add-on Interrupt Control/Status Register                            */
/****************************************************************************/

#घोषणा AINT_INT_MASK		0x00ff0000
#घोषणा AINT_SEL_MASK		0x0000ffff
#घोषणा  AINT_IS_ENSEL_MASK	0x00001f1f

#घोषणा AINT_INT_ASSERTED	0x00800000
#घोषणा AINT_BM_ERROR		0x00200000
#घोषणा AINT_BIST_INT		0x00100000

#घोषणा AINT_RT_COMPLETE	0x00080000
#घोषणा AINT_WT_COMPLETE	0x00040000

#घोषणा AINT_OUT_MB_INT		0x00020000
#घोषणा AINT_IN_MB_INT		0x00010000

#घोषणा AINT_READ_COMPL		0x00008000
#घोषणा AINT_WRITE_COMPL	0x00004000

#घोषणा AINT_OMB_ENABLE		0x00001000
#घोषणा AINT_OMB_SELECT		0x00000c00
#घोषणा AINT_OMB_BYTE		0x00000300

#घोषणा AINT_IMB_ENABLE		0x00000010
#घोषणा AINT_IMB_SELECT		0x0000000c
#घोषणा AINT_IMB_BYTE		0x00000003

/* these are bits from various dअगरferent रेजिस्टरs, needs cleanup XXX */
/* Enable Bus Mastering */
#घोषणा EN_A2P_TRANSFERS	0x00000400
/* FIFO Flag Reset */
#घोषणा RESET_A2P_FLAGS		0x04000000L
/* FIFO Relative Priority */
#घोषणा A2P_HI_PRIORITY		0x00000100L
/* Identअगरy Interrupt Sources */
#घोषणा ANY_S593X_INT		0x00800000L
#घोषणा READ_TC_INT		0x00080000L
#घोषणा WRITE_TC_INT		0x00040000L
#घोषणा IN_MB_INT		0x00020000L
#घोषणा MASTER_ABORT_INT	0x00100000L
#घोषणा TARGET_ABORT_INT	0x00200000L
#घोषणा BUS_MASTER_INT		0x00200000L

#पूर्ण_अगर
