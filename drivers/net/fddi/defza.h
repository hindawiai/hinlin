<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*	FDDI network adapter driver क्रम DEC FDDIcontroller 700/700-C devices.
 *
 *	Copyright (c) 2018  Maciej W. Rozycki
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 *	References:
 *
 *	Dave Sawyer & Phil Weeks & Frank Itkowsky,
 *	"DEC FDDIcontroller 700 Port Specification",
 *	Revision 1.1, Digital Equipment Corporation
 */

#समावेश <linux/compiler.h>
#समावेश <linux/अगर_fddi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>

/* IOmem रेजिस्टर offsets. */
#घोषणा FZA_REG_BASE		0x100000	/* रेजिस्टर base address */
#घोषणा FZA_REG_RESET		0x100200	/* reset, r/w */
#घोषणा FZA_REG_INT_EVENT	0x100400	/* पूर्णांकerrupt event, r/w1c */
#घोषणा FZA_REG_STATUS		0x100402	/* status, r/o */
#घोषणा FZA_REG_INT_MASK	0x100404	/* पूर्णांकerrupt mask, r/w */
#घोषणा FZA_REG_CONTROL_A	0x100500	/* control A, r/w1s */
#घोषणा FZA_REG_CONTROL_B	0x100502	/* control B, r/w */

/* Reset रेजिस्टर स्थिरants.  Bits 1:0 are r/w, others are fixed at 0. */
#घोषणा FZA_RESET_DLU	0x0002	/* OR with INIT to blast flash memory */
#घोषणा FZA_RESET_INIT	0x0001	/* चयन पूर्णांकo the reset state */
#घोषणा FZA_RESET_CLR	0x0000	/* run self-test and वापस to work */

/* Interrupt event रेजिस्टर स्थिरants.  All bits are r/w1c. */
#घोषणा FZA_EVENT_DLU_DONE	0x0800	/* flash memory ग_लिखो complete */
#घोषणा FZA_EVENT_FLUSH_TX	0x0400	/* transmit ring flush request */
#घोषणा FZA_EVENT_PM_PARITY_ERR	0x0200	/* onboard packet memory parity err */
#घोषणा FZA_EVENT_HB_PARITY_ERR	0x0100	/* host bus parity error */
#घोषणा FZA_EVENT_NXM_ERR	0x0080	/* non-existent memory access error;
					 * also उठाओd क्रम unaligned and
					 * unsupported partial-word accesses
					 */
#घोषणा FZA_EVENT_LINK_ST_CHG	0x0040	/* link status change */
#घोषणा FZA_EVENT_STATE_CHG	0x0020	/* adapter state change */
#घोषणा FZA_EVENT_UNS_POLL	0x0010	/* unsolicited event service request */
#घोषणा FZA_EVENT_CMD_DONE	0x0008	/* command करोne ack */
#घोषणा FZA_EVENT_SMT_TX_POLL	0x0004	/* SMT frame transmit request */
#घोषणा FZA_EVENT_RX_POLL	0x0002	/* receive request (packet avail.) */
#घोषणा FZA_EVENT_TX_DONE	0x0001	/* RMC transmit करोne ack */

/* Status रेजिस्टर स्थिरants.  All bits are r/o. */
#घोषणा FZA_STATUS_DLU_SHIFT	0xc	/* करोwn line upgrade status bits */
#घोषणा FZA_STATUS_DLU_MASK	0x03
#घोषणा FZA_STATUS_LINK_SHIFT	0xb	/* link status bits */
#घोषणा FZA_STATUS_LINK_MASK	0x01
#घोषणा FZA_STATUS_STATE_SHIFT	0x8	/* adapter state bits */
#घोषणा FZA_STATUS_STATE_MASK	0x07
#घोषणा FZA_STATUS_HALT_SHIFT	0x0	/* halt reason bits */
#घोषणा FZA_STATUS_HALT_MASK	0xff
#घोषणा FZA_STATUS_TEST_SHIFT	0x0	/* test failure bits */
#घोषणा FZA_STATUS_TEST_MASK	0xff

#घोषणा FZA_STATUS_GET_DLU(x)	(((x) >> FZA_STATUS_DLU_SHIFT) &	\
				 FZA_STATUS_DLU_MASK)
#घोषणा FZA_STATUS_GET_LINK(x)	(((x) >> FZA_STATUS_LINK_SHIFT) &	\
				 FZA_STATUS_LINK_MASK)
#घोषणा FZA_STATUS_GET_STATE(x)	(((x) >> FZA_STATUS_STATE_SHIFT) &	\
				 FZA_STATUS_STATE_MASK)
#घोषणा FZA_STATUS_GET_HALT(x)	(((x) >> FZA_STATUS_HALT_SHIFT) &	\
				 FZA_STATUS_HALT_MASK)
#घोषणा FZA_STATUS_GET_TEST(x)	(((x) >> FZA_STATUS_TEST_SHIFT) &	\
				 FZA_STATUS_TEST_MASK)

#घोषणा FZA_DLU_FAILURE		0x0	/* DLU catastrophic error; brain dead */
#घोषणा FZA_DLU_ERROR		0x1	/* DLU error; old firmware पूर्णांकact */
#घोषणा FZA_DLU_SUCCESS		0x2	/* DLU OK; new firmware loaded */

#घोषणा FZA_LINK_OFF		0x0	/* link unavailable */
#घोषणा FZA_LINK_ON		0x1	/* link available */

#घोषणा FZA_STATE_RESET		0x0	/* resetting */
#घोषणा FZA_STATE_UNINITIALIZED	0x1	/* after a reset */
#घोषणा FZA_STATE_INITIALIZED	0x2	/* initialized */
#घोषणा FZA_STATE_RUNNING	0x3	/* running (link active) */
#घोषणा FZA_STATE_MAINTEन_अंकCE	0x4	/* running (link looped back) */
#घोषणा FZA_STATE_HALTED	0x5	/* halted (error condition) */

#घोषणा FZA_HALT_UNKNOWN	0x00	/* unknown reason */
#घोषणा FZA_HALT_HOST		0x01	/* host-directed HALT */
#घोषणा FZA_HALT_HB_PARITY	0x02	/* host bus parity error */
#घोषणा FZA_HALT_NXM		0x03	/* adapter non-existent memory ref. */
#घोषणा FZA_HALT_SW		0x04	/* adapter software fault */
#घोषणा FZA_HALT_HW		0x05	/* adapter hardware fault */
#घोषणा FZA_HALT_PC_TRACE	0x06	/* PC Trace path test */
#घोषणा FZA_HALT_DLSW		0x07	/* data link software fault */
#घोषणा FZA_HALT_DLHW		0x08	/* data link hardware fault */

#घोषणा FZA_TEST_FATAL		0x00	/* self-test catastrophic failure */
#घोषणा FZA_TEST_68K		0x01	/* 68000 CPU */
#घोषणा FZA_TEST_SRAM_BWADDR	0x02	/* SRAM byte/word address */
#घोषणा FZA_TEST_SRAM_DBUS	0x03	/* SRAM data bus */
#घोषणा FZA_TEST_SRAM_STUCK1	0x04	/* SRAM stuck-at range 1 */
#घोषणा FZA_TEST_SRAM_STUCK2	0x05	/* SRAM stuck-at range 2 */
#घोषणा FZA_TEST_SRAM_COUPL1	0x06	/* SRAM coupling range 1 */
#घोषणा FZA_TEST_SRAM_COUPL2	0x07	/* SRAM coupling */
#घोषणा FZA_TEST_FLASH_CRC	0x08	/* Flash CRC */
#घोषणा FZA_TEST_ROM		0x09	/* option ROM */
#घोषणा FZA_TEST_PHY_CSR	0x0a	/* PHY CSR */
#घोषणा FZA_TEST_MAC_BIST	0x0b	/* MAC BiST */
#घोषणा FZA_TEST_MAC_CSR	0x0c	/* MAC CSR */
#घोषणा FZA_TEST_MAC_ADDR_UNIQ	0x0d	/* MAC unique address */
#घोषणा FZA_TEST_ELM_BIST	0x0e	/* ELM BiST */
#घोषणा FZA_TEST_ELM_CSR	0x0f	/* ELM CSR */
#घोषणा FZA_TEST_ELM_ADDR_UNIQ	0x10	/* ELM unique address */
#घोषणा FZA_TEST_CAM		0x11	/* CAM */
#घोषणा FZA_TEST_NIROM		0x12	/* NI ROM checksum */
#घोषणा FZA_TEST_SC_LOOP	0x13	/* SC loopback packet */
#घोषणा FZA_TEST_LM_LOOP	0x14	/* LM loopback packet */
#घोषणा FZA_TEST_EB_LOOP	0x15	/* EB loopback packet */
#घोषणा FZA_TEST_SC_LOOP_BYPS	0x16	/* SC bypass loopback packet */
#घोषणा FZA_TEST_LM_LOOP_LOCAL	0x17	/* LM local loopback packet */
#घोषणा FZA_TEST_EB_LOOP_LOCAL	0x18	/* EB local loopback packet */
#घोषणा FZA_TEST_CDC_LOOP	0x19	/* CDC loopback packet */
#घोषणा FZA_TEST_FIBER_LOOP	0x1A	/* FIBER loopback packet */
#घोषणा FZA_TEST_CAM_MATCH_LOOP	0x1B	/* CAM match packet loopback */
#घोषणा FZA_TEST_68K_IRQ_STUCK	0x1C	/* 68000 पूर्णांकerrupt line stuck-at */
#घोषणा FZA_TEST_IRQ_PRESENT	0x1D	/* पूर्णांकerrupt present रेजिस्टर */
#घोषणा FZA_TEST_RMC_BIST	0x1E	/* RMC BiST */
#घोषणा FZA_TEST_RMC_CSR	0x1F	/* RMC CSR */
#घोषणा FZA_TEST_RMC_ADDR_UNIQ	0x20	/* RMC unique address */
#घोषणा FZA_TEST_PM_DPATH	0x21	/* packet memory data path */
#घोषणा FZA_TEST_PM_ADDR	0x22	/* packet memory address */
#घोषणा FZA_TEST_RES_23		0x23	/* reserved */
#घोषणा FZA_TEST_PM_DESC	0x24	/* packet memory descriptor */
#घोषणा FZA_TEST_PM_OWN		0x25	/* packet memory own bit */
#घोषणा FZA_TEST_PM_PARITY	0x26	/* packet memory parity */
#घोषणा FZA_TEST_PM_BSWAP	0x27	/* packet memory byte swap */
#घोषणा FZA_TEST_PM_WSWAP	0x28	/* packet memory word swap */
#घोषणा FZA_TEST_PM_REF		0x29	/* packet memory refresh */
#घोषणा FZA_TEST_PM_CSR		0x2A	/* PM CSR */
#घोषणा FZA_TEST_PORT_STATUS	0x2B	/* port status रेजिस्टर */
#घोषणा FZA_TEST_HOST_IRQMASK	0x2C	/* host पूर्णांकerrupt mask */
#घोषणा FZA_TEST_TIMER_IRQ1	0x2D	/* RTOS समयr */
#घोषणा FZA_TEST_FORCE_IRQ1	0x2E	/* क्रमce RTOS IRQ1 */
#घोषणा FZA_TEST_TIMER_IRQ5	0x2F	/* IRQ5 backoff समयr */
#घोषणा FZA_TEST_FORCE_IRQ5	0x30	/* क्रमce IRQ5 */
#घोषणा FZA_TEST_RES_31		0x31	/* reserved */
#घोषणा FZA_TEST_IC_PRIO	0x32	/* पूर्णांकerrupt controller priority */
#घोषणा FZA_TEST_PM_FULL	0x33	/* full packet memory */
#घोषणा FZA_TEST_PMI_DMA	0x34	/* PMI DMA */

/* Interrupt mask रेजिस्टर स्थिरants.  All bits are r/w. */
#घोषणा FZA_MASK_RESERVED	0xf000	/* unused */
#घोषणा FZA_MASK_DLU_DONE	0x0800	/* flash memory ग_लिखो complete */
#घोषणा FZA_MASK_FLUSH_TX	0x0400	/* transmit ring flush request */
#घोषणा FZA_MASK_PM_PARITY_ERR	0x0200	/* onboard packet memory parity error
					 */
#घोषणा FZA_MASK_HB_PARITY_ERR	0x0100	/* host bus parity error */
#घोषणा FZA_MASK_NXM_ERR	0x0080	/* adapter non-existent memory
					 * reference
					 */
#घोषणा FZA_MASK_LINK_ST_CHG	0x0040	/* link status change */
#घोषणा FZA_MASK_STATE_CHG	0x0020	/* adapter state change */
#घोषणा FZA_MASK_UNS_POLL	0x0010	/* unsolicited event service request */
#घोषणा FZA_MASK_CMD_DONE	0x0008	/* command ring entry processed */
#घोषणा FZA_MASK_SMT_TX_POLL	0x0004	/* SMT frame transmit request */
#घोषणा FZA_MASK_RCV_POLL	0x0002	/* receive request (packet available)
					 */
#घोषणा FZA_MASK_TX_DONE	0x0001	/* RMC transmit करोne acknowledge */

/* Which पूर्णांकerrupts to receive: 0/1 is mask/unmask. */
#घोषणा FZA_MASK_NONE		0x0000
#घोषणा FZA_MASK_NORMAL							\
		((~(FZA_MASK_RESERVED | FZA_MASK_DLU_DONE |		\
		    FZA_MASK_PM_PARITY_ERR | FZA_MASK_HB_PARITY_ERR |	\
		    FZA_MASK_NXM_ERR)) & 0xffff)

/* Control A रेजिस्टर स्थिरants. */
#घोषणा FZA_CONTROL_A_HB_PARITY_ERR	0x8000	/* host bus parity error */
#घोषणा FZA_CONTROL_A_NXM_ERR		0x4000	/* adapter non-existent memory
						 * reference
						 */
#घोषणा FZA_CONTROL_A_SMT_RX_OVFL	0x0040	/* SMT receive overflow */
#घोषणा FZA_CONTROL_A_FLUSH_DONE	0x0020	/* flush tx request complete */
#घोषणा FZA_CONTROL_A_SHUT		0x0010	/* turn the पूर्णांकerface off */
#घोषणा FZA_CONTROL_A_HALT		0x0008	/* halt the controller */
#घोषणा FZA_CONTROL_A_CMD_POLL		0x0004	/* command ring poll */
#घोषणा FZA_CONTROL_A_SMT_RX_POLL	0x0002	/* SMT receive ring poll */
#घोषणा FZA_CONTROL_A_TX_POLL		0x0001	/* transmit poll */

/* Control B रेजिस्टर स्थिरants.  All bits are r/w.
 *
 * Possible values:
 *	0x0000 after booting पूर्णांकo REX,
 *	0x0003 after issuing `boot #/mop'.
 */
#घोषणा FZA_CONTROL_B_CONSOLE	0x0002	/* OR with DRIVER क्रम console
					 * (TC firmware) mode
					 */
#घोषणा FZA_CONTROL_B_DRIVER	0x0001	/* driver mode */
#घोषणा FZA_CONTROL_B_IDLE	0x0000	/* no driver installed */

#घोषणा FZA_RESET_PAD							\
		(FZA_REG_RESET - FZA_REG_BASE)
#घोषणा FZA_INT_EVENT_PAD						\
		(FZA_REG_INT_EVENT - FZA_REG_RESET - माप(u16))
#घोषणा FZA_CONTROL_A_PAD						\
		(FZA_REG_CONTROL_A - FZA_REG_INT_MASK - माप(u16))

/* Layout of रेजिस्टरs. */
काष्ठा fza_regs अणु
	u8  pad0[FZA_RESET_PAD];
	u16 reset;				/* reset रेजिस्टर */
	u8  pad1[FZA_INT_EVENT_PAD];
	u16 पूर्णांक_event;				/* पूर्णांकerrupt event रेजिस्टर */
	u16 status;				/* status रेजिस्टर */
	u16 पूर्णांक_mask;				/* पूर्णांकerrupt mask रेजिस्टर */
	u8  pad2[FZA_CONTROL_A_PAD];
	u16 control_a;				/* control A रेजिस्टर */
	u16 control_b;				/* control B रेजिस्टर */
पूर्ण;

/* Command descriptor ring entry. */
काष्ठा fza_ring_cmd अणु
	u32 cmd_own;		/* bit 31: ownership, bits [30:0]: command */
	u32 stat;		/* command status */
	u32 buffer;		/* address of the buffer in the FZA space */
	u32 pad0;
पूर्ण;

#घोषणा FZA_RING_CMD		0x200400	/* command ring address */
#घोषणा FZA_RING_CMD_SIZE	0x40		/* command descriptor ring
						 * size
						 */
/* Command स्थिरants. */
#घोषणा FZA_RING_CMD_MASK	0x7fffffff
#घोषणा FZA_RING_CMD_NOP	0x00000000	/* nop */
#घोषणा FZA_RING_CMD_INIT	0x00000001	/* initialize */
#घोषणा FZA_RING_CMD_MODCAM	0x00000002	/* modअगरy CAM */
#घोषणा FZA_RING_CMD_PARAM	0x00000003	/* set प्रणाली parameters */
#घोषणा FZA_RING_CMD_MODPROM	0x00000004	/* modअगरy promiscuous mode */
#घोषणा FZA_RING_CMD_SETCHAR	0x00000005	/* set link अक्षरacteristics */
#घोषणा FZA_RING_CMD_RDCNTR	0x00000006	/* पढ़ो counters */
#घोषणा FZA_RING_CMD_STATUS	0x00000007	/* get link status */
#घोषणा FZA_RING_CMD_RDCAM	0x00000008	/* पढ़ो CAM */

/* Command status स्थिरants. */
#घोषणा FZA_RING_STAT_SUCCESS	0x00000000

/* Unsolicited event descriptor ring entry. */
काष्ठा fza_ring_uns अणु
	u32 own;		/* bit 31: ownership, bits [30:0]: reserved */
	u32 id;			/* event ID */
	u32 buffer;		/* address of the buffer in the FZA space */
	u32 pad0;		/* reserved */
पूर्ण;

#घोषणा FZA_RING_UNS		0x200800	/* unsolicited ring address */
#घोषणा FZA_RING_UNS_SIZE	0x40		/* unsolicited descriptor ring
						 * size
						 */
/* Unsolicited event स्थिरants. */
#घोषणा FZA_RING_UNS_UND	0x00000000	/* undefined event ID */
#घोषणा FZA_RING_UNS_INIT_IN	0x00000001	/* ring init initiated */
#घोषणा FZA_RING_UNS_INIT_RX	0x00000002	/* ring init received */
#घोषणा FZA_RING_UNS_BEAC_IN	0x00000003	/* ring beaconing initiated */
#घोषणा FZA_RING_UNS_DUP_ADDR	0x00000004	/* duplicate address detected */
#घोषणा FZA_RING_UNS_DUP_TOK	0x00000005	/* duplicate token detected */
#घोषणा FZA_RING_UNS_PURG_ERR	0x00000006	/* ring purger error */
#घोषणा FZA_RING_UNS_STRIP_ERR	0x00000007	/* bridge strip error */
#घोषणा FZA_RING_UNS_OP_OSC	0x00000008	/* ring op oscillation */
#घोषणा FZA_RING_UNS_BEAC_RX	0x00000009	/* directed beacon received */
#घोषणा FZA_RING_UNS_PCT_IN	0x0000000a	/* PC trace initiated */
#घोषणा FZA_RING_UNS_PCT_RX	0x0000000b	/* PC trace received */
#घोषणा FZA_RING_UNS_TX_UNDER	0x0000000c	/* transmit underrun */
#घोषणा FZA_RING_UNS_TX_FAIL	0x0000000d	/* transmit failure */
#घोषणा FZA_RING_UNS_RX_OVER	0x0000000e	/* receive overrun */

/* RMC (Ring Memory Control) transmit descriptor ring entry. */
काष्ठा fza_ring_rmc_tx अणु
	u32 rmc;		/* RMC inक्रमmation */
	u32 avl;		/* available क्रम host (unused by RMC) */
	u32 own;		/* bit 31: ownership, bits [30:0]: reserved */
	u32 pad0;		/* reserved */
पूर्ण;

#घोषणा FZA_TX_BUFFER_ADDR(x)	(0x200000 | (((x) & 0xffff) << 5))
#घोषणा FZA_TX_BUFFER_SIZE	512
काष्ठा fza_buffer_tx अणु
	u32 data[FZA_TX_BUFFER_SIZE / माप(u32)];
पूर्ण;

/* Transmit ring RMC स्थिरants. */
#घोषणा FZA_RING_TX_SOP		0x80000000	/* start of packet */
#घोषणा FZA_RING_TX_EOP		0x40000000	/* end of packet */
#घोषणा FZA_RING_TX_DTP		0x20000000	/* discard this packet */
#घोषणा FZA_RING_TX_VBC		0x10000000	/* valid buffer byte count */
#घोषणा FZA_RING_TX_DCC_MASK	0x0f000000	/* DMA completion code */
#घोषणा FZA_RING_TX_DCC_SUCCESS	0x01000000	/* transmit succeeded */
#घोषणा FZA_RING_TX_DCC_DTP_SOP	0x02000000	/* DTP set at SOP */
#घोषणा FZA_RING_TX_DCC_DTP	0x04000000	/* DTP set within packet */
#घोषणा FZA_RING_TX_DCC_ABORT	0x05000000	/* MAC-requested पात */
#घोषणा FZA_RING_TX_DCC_PARITY	0x06000000	/* xmit data parity error */
#घोषणा FZA_RING_TX_DCC_UNDRRUN	0x07000000	/* transmit underrun */
#घोषणा FZA_RING_TX_XPO_MASK	0x003fe000	/* transmit packet offset */

/* Host receive descriptor ring entry. */
काष्ठा fza_ring_hst_rx अणु
	u32 buf0_own;		/* bit 31: ownership, bits [30:23]: unused,
				 * bits [22:0]: right-shअगरted address of the
				 * buffer in प्रणाली memory (low buffer)
				 */
	u32 buffer1;		/* bits [31:23]: unused,
				 * bits [22:0]: right-shअगरted address of the
				 * buffer in प्रणाली memory (high buffer)
				 */
	u32 rmc;		/* RMC inक्रमmation */
	u32 pad0;
पूर्ण;

#घोषणा FZA_RX_BUFFER_SIZE	(4096 + 512)	/* buffer length */

/* Receive ring RMC स्थिरants. */
#घोषणा FZA_RING_RX_SOP		0x80000000	/* start of packet */
#घोषणा FZA_RING_RX_EOP		0x40000000	/* end of packet */
#घोषणा FZA_RING_RX_FSC_MASK	0x38000000	/* # of frame status bits */
#घोषणा FZA_RING_RX_FSB_MASK	0x07c00000	/* frame status bits */
#घोषणा FZA_RING_RX_FSB_ERR	0x04000000	/* error detected */
#घोषणा FZA_RING_RX_FSB_ADDR	0x02000000	/* address recognized */
#घोषणा FZA_RING_RX_FSB_COP	0x01000000	/* frame copied */
#घोषणा FZA_RING_RX_FSB_F0	0x00800000	/* first additional flag */
#घोषणा FZA_RING_RX_FSB_F1	0x00400000	/* second additional flag */
#घोषणा FZA_RING_RX_BAD		0x00200000	/* bad packet */
#घोषणा FZA_RING_RX_CRC		0x00100000	/* CRC error */
#घोषणा FZA_RING_RX_RRR_MASK	0x000e0000	/* MAC receive status bits */
#घोषणा FZA_RING_RX_RRR_OK	0x00000000	/* receive OK */
#घोषणा FZA_RING_RX_RRR_SADDR	0x00020000	/* source address matched */
#घोषणा FZA_RING_RX_RRR_DADDR	0x00040000	/* dest address not matched */
#घोषणा FZA_RING_RX_RRR_ABORT	0x00060000	/* RMC पात */
#घोषणा FZA_RING_RX_RRR_LENGTH	0x00080000	/* invalid length */
#घोषणा FZA_RING_RX_RRR_FRAG	0x000a0000	/* fragment */
#घोषणा FZA_RING_RX_RRR_FORMAT	0x000c0000	/* क्रमmat error */
#घोषणा FZA_RING_RX_RRR_RESET	0x000e0000	/* MAC reset */
#घोषणा FZA_RING_RX_DA_MASK	0x00018000	/* daddr match status bits */
#घोषणा FZA_RING_RX_DA_NONE	0x00000000	/* no match */
#घोषणा FZA_RING_RX_DA_PROM	0x00008000	/* promiscuous match */
#घोषणा FZA_RING_RX_DA_CAM	0x00010000	/* CAM entry match */
#घोषणा FZA_RING_RX_DA_LOCAL	0x00018000	/* link addr or LLC bcast */
#घोषणा FZA_RING_RX_SA_MASK	0x00006000	/* saddr match status bits */
#घोषणा FZA_RING_RX_SA_NONE	0x00000000	/* no match */
#घोषणा FZA_RING_RX_SA_ALIAS	0x00002000	/* alias address match */
#घोषणा FZA_RING_RX_SA_CAM	0x00004000	/* CAM entry match */
#घोषणा FZA_RING_RX_SA_LOCAL	0x00006000	/* link address match */

/* SMT (Station Management) transmit/receive descriptor ring entry. */
काष्ठा fza_ring_smt अणु
	u32 own;		/* bit 31: ownership, bits [30:0]: unused */
	u32 rmc;		/* RMC inक्रमmation */
	u32 buffer;		/* address of the buffer */
	u32 pad0;		/* reserved */
पूर्ण;

/* Ownership स्थिरants.
 *
 * Only an owner is permitted to process a given ring entry.
 * RMC transmit ring meanings are reversed.
 */
#घोषणा FZA_RING_OWN_MASK	0x80000000
#घोषणा FZA_RING_OWN_FZA	0x00000000	/* permit FZA, क्रमbid host */
#घोषणा FZA_RING_OWN_HOST	0x80000000	/* permit host, क्रमbid FZA */
#घोषणा FZA_RING_TX_OWN_RMC	0x80000000	/* permit RMC, क्रमbid host */
#घोषणा FZA_RING_TX_OWN_HOST	0x00000000	/* permit host, क्रमbid RMC */

/* RMC स्थिरants. */
#घोषणा FZA_RING_PBC_MASK	0x00001fff	/* frame length */

/* Layout of counter buffers. */

काष्ठा fza_counter अणु
	u32 msw;
	u32 lsw;
पूर्ण;

काष्ठा fza_counters अणु
	काष्ठा fza_counter sys_buf;	/* प्रणाली buffer unavailable */
	काष्ठा fza_counter tx_under;	/* transmit underruns */
	काष्ठा fza_counter tx_fail;	/* transmit failures */
	काष्ठा fza_counter rx_over;	/* receive data overruns */
	काष्ठा fza_counter frame_cnt;	/* frame count */
	काष्ठा fza_counter error_cnt;	/* error count */
	काष्ठा fza_counter lost_cnt;	/* lost count */
	काष्ठा fza_counter rinit_in;	/* ring initialization initiated */
	काष्ठा fza_counter rinit_rx;	/* ring initialization received */
	काष्ठा fza_counter beac_in;	/* ring beacon initiated */
	काष्ठा fza_counter dup_addr;	/* duplicate address test failures */
	काष्ठा fza_counter dup_tok;	/* duplicate token detected */
	काष्ठा fza_counter purg_err;	/* ring purge errors */
	काष्ठा fza_counter strip_err;	/* bridge strip errors */
	काष्ठा fza_counter pct_in;	/* traces initiated */
	काष्ठा fza_counter pct_rx;	/* traces received */
	काष्ठा fza_counter lem_rej;	/* LEM rejects */
	काष्ठा fza_counter tne_rej;	/* TNE expiry rejects */
	काष्ठा fza_counter lem_event;	/* LEM events */
	काष्ठा fza_counter lct_rej;	/* LCT rejects */
	काष्ठा fza_counter conn_cmpl;	/* connections completed */
	काष्ठा fza_counter el_buf;	/* elasticity buffer errors */
पूर्ण;

/* Layout of command buffers. */

/* INIT command buffer.
 *
 * Values of शेष link parameters given are as obtained from a
 * DEFZA-AA rev. C03 board.  The board counts समय in units of 80ns.
 */
काष्ठा fza_cmd_init अणु
	u32 tx_mode;			/* transmit mode */
	u32 hst_rx_size;		/* host receive ring entries */

	काष्ठा fza_counters counters;	/* counters */

	u8 rmc_rev[4];			/* RMC revision */
	u8 rom_rev[4];			/* ROM revision */
	u8 fw_rev[4];			/* firmware revision */

	u32 mop_type;			/* MOP device type */

	u32 hst_rx;			/* base of host rx descriptor ring */
	u32 rmc_tx;			/* base of RMC tx descriptor ring */
	u32 rmc_tx_size;		/* size of RMC tx descriptor ring */
	u32 smt_tx;			/* base of SMT tx descriptor ring */
	u32 smt_tx_size;		/* size of SMT tx descriptor ring */
	u32 smt_rx;			/* base of SMT rx descriptor ring */
	u32 smt_rx_size;		/* size of SMT rx descriptor ring */

	u32 hw_addr[2];			/* link address */

	u32 def_t_req;			/* शेष Requested TTRT (T_REQ) --
					 * C03: 100000 [80ns]
					 */
	u32 def_tvx;			/* शेष Valid Transmission Time
					 * (TVX) -- C03: 32768 [80ns]
					 */
	u32 def_t_max;			/* शेष Maximum TTRT (T_MAX) --
					 * C03: 2162688 [80ns]
					 */
	u32 lem_threshold;		/* शेष LEM threshold -- C03: 8 */
	u32 def_station_id[2];		/* शेष station ID */

	u32 pmd_type_alt;		/* alternative PMD type code */

	u32 smt_ver;			/* SMT version */

	u32 rtoken_समयout;		/* शेष restricted token समयout
					 * -- C03: 12500000 [80ns]
					 */
	u32 ring_purger;		/* शेष ring purger enable --
					 * C03: 1
					 */

	u32 smt_ver_max;		/* max SMT version ID */
	u32 smt_ver_min;		/* min SMT version ID */
	u32 pmd_type;			/* PMD type code */
पूर्ण;

/* INIT command PMD type codes. */
#घोषणा FZA_PMD_TYPE_MMF	  0	/* Multimode fiber */
#घोषणा FZA_PMD_TYPE_TW		101	/* ThinWire */
#घोषणा FZA_PMD_TYPE_STP	102	/* STP */

/* MODCAM/RDCAM command buffer. */
#घोषणा FZA_CMD_CAM_SIZE	64		/* CAM address entry count */
काष्ठा fza_cmd_cam अणु
	u32 hw_addr[FZA_CMD_CAM_SIZE][2];	/* CAM address entries */
पूर्ण;

/* PARAM command buffer.
 *
 * Permitted ranges given are as defined by the spec and obtained from a
 * DEFZA-AA rev. C03 board, respectively.  The rtoken_समयout field is
 * erroneously पूर्णांकerpreted in units of ms.
 */
काष्ठा fza_cmd_param अणु
	u32 loop_mode;			/* loopback mode */
	u32 t_max;			/* Maximum TTRT (T_MAX)
					 * def: ??? [80ns]
					 * C03: [t_req+1,4294967295] [80ns]
					 */
	u32 t_req;			/* Requested TTRT (T_REQ)
					 * def: [50000,2097151] [80ns]
					 * C03: [50001,t_max-1] [80ns]
					 */
	u32 tvx;			/* Valid Transmission Time (TVX)
					 * def: [29375,65280] [80ns]
					 * C03: [29376,65279] [80ns]
					 */
	u32 lem_threshold;		/* LEM threshold */
	u32 station_id[2];		/* station ID */
	u32 rtoken_समयout;		/* restricted token समयout
					 * def: [0,125000000] [80ns]
					 * C03: [0,9999] [ms]
					 */
	u32 ring_purger;		/* ring purger enable: 0|1 */
पूर्ण;

/* Loopback modes क्रम the PARAM command. */
#घोषणा FZA_LOOP_NORMAL		0
#घोषणा FZA_LOOP_INTERN		1
#घोषणा FZA_LOOP_EXTERN		2

/* MODPROM command buffer. */
काष्ठा fza_cmd_modprom अणु
	u32 llc_prom;			/* LLC promiscuous enable */
	u32 smt_prom;			/* SMT promiscuous enable */
	u32 llc_multi;			/* LLC multicast promiscuous enable */
	u32 llc_bcast;			/* LLC broadcast promiscuous enable */
पूर्ण;

/* SETCHAR command buffer.
 *
 * Permitted ranges are as क्रम the PARAM command.
 */
काष्ठा fza_cmd_setअक्षर अणु
	u32 t_max;			/* Maximum TTRT (T_MAX) */
	u32 t_req;			/* Requested TTRT (T_REQ) */
	u32 tvx;			/* Valid Transmission Time (TVX) */
	u32 lem_threshold;		/* LEM threshold */
	u32 rtoken_समयout;		/* restricted token समयout */
	u32 ring_purger;		/* ring purger enable */
पूर्ण;

/* RDCNTR command buffer. */
काष्ठा fza_cmd_rdcntr अणु
	काष्ठा fza_counters counters;	/* counters */
पूर्ण;

/* STATUS command buffer. */
काष्ठा fza_cmd_status अणु
	u32 led_state;			/* LED state */
	u32 rmt_state;			/* ring management state */
	u32 link_state;			/* link state */
	u32 dup_addr;			/* duplicate address flag */
	u32 ring_purger;		/* ring purger state */
	u32 t_neg;			/* negotiated TTRT [80ns] */
	u32 una[2];			/* upstream neighbour address */
	u32 una_समयout;		/* UNA समयd out */
	u32 strip_mode;			/* frame strip mode */
	u32 yield_mode;			/* claim token yield mode */
	u32 phy_state;			/* PHY state */
	u32 neigh_phy;			/* neighbour PHY type */
	u32 reject;			/* reject reason */
	u32 phy_lee;			/* PHY link error estimate [-log10] */
	u32 una_old[2];			/* old upstream neighbour address */
	u32 rmt_mac;			/* remote MAC indicated */
	u32 ring_err;			/* ring error reason */
	u32 beac_rx[2];			/* sender of last directed beacon */
	u32 un_dup_addr;		/* upstream neighbr dup address flag */
	u32 dna[2];			/* करोwnstream neighbour address */
	u32 dna_old[2];			/* old करोwnstream neighbour address */
पूर्ण;

/* Common command buffer. */
जोड़ fza_cmd_buf अणु
	काष्ठा fza_cmd_init init;
	काष्ठा fza_cmd_cam cam;
	काष्ठा fza_cmd_param param;
	काष्ठा fza_cmd_modprom modprom;
	काष्ठा fza_cmd_setअक्षर setअक्षर;
	काष्ठा fza_cmd_rdcntr rdcntr;
	काष्ठा fza_cmd_status status;
पूर्ण;

/* MAC (Media Access Controller) chip packet request header स्थिरants. */

/* Packet request header byte #0. */
#घोषणा FZA_PRH0_FMT_TYPE_MASK	0xc0	/* type of packet, always zero */
#घोषणा FZA_PRH0_TOK_TYPE_MASK	0x30	/* type of token required
					 * to send this frame
					 */
#घोषणा FZA_PRH0_TKN_TYPE_ANY	0x30	/* use either token type */
#घोषणा FZA_PRH0_TKN_TYPE_UNR	0x20	/* use an unrestricted token */
#घोषणा FZA_PRH0_TKN_TYPE_RST	0x10	/* use a restricted token */
#घोषणा FZA_PRH0_TKN_TYPE_IMM	0x00	/* send immediately, no token required
					 */
#घोषणा FZA_PRH0_FRAME_MASK	0x08	/* type of frame to send */
#घोषणा FZA_PRH0_FRAME_SYNC	0x08	/* send a synchronous frame */
#घोषणा FZA_PRH0_FRAME_ASYNC	0x00	/* send an asynchronous frame */
#घोषणा FZA_PRH0_MODE_MASK	0x04	/* send mode */
#घोषणा FZA_PRH0_MODE_IMMED	0x04	/* an immediate mode, send regardless
					 * of the ring operational state
					 */
#घोषणा FZA_PRH0_MODE_NORMAL	0x00	/* a normal mode, send only अगर ring
					 * operational
					 */
#घोषणा FZA_PRH0_SF_MASK	0x02	/* send frame first */
#घोषणा FZA_PRH0_SF_FIRST	0x02	/* send this frame first
					 * with this token capture
					 */
#घोषणा FZA_PRH0_SF_NORMAL	0x00	/* treat this frame normally */
#घोषणा FZA_PRH0_BCN_MASK	0x01	/* beacon frame */
#घोषणा FZA_PRH0_BCN_BEACON	0x01	/* send the frame only
					 * अगर in the beacon state
					 */
#घोषणा FZA_PRH0_BCN_DATA	0x01	/* send the frame only
					 * अगर in the data state
					 */
/* Packet request header byte #1. */
					/* bit 7 always zero */
#घोषणा FZA_PRH1_SL_MASK	0x40	/* send frame last */
#घोषणा FZA_PRH1_SL_LAST	0x40	/* send this frame last, releasing
					 * the token afterwards
					 */
#घोषणा FZA_PRH1_SL_NORMAL	0x00	/* treat this frame normally */
#घोषणा FZA_PRH1_CRC_MASK	0x20	/* CRC append */
#घोषणा FZA_PRH1_CRC_NORMAL	0x20	/* calculate the CRC and append it
					 * as the FCS field to the frame
					 */
#घोषणा FZA_PRH1_CRC_SKIP	0x00	/* leave the frame as is */
#घोषणा FZA_PRH1_TKN_SEND_MASK	0x18	/* type of token to send after the
					 * frame अगर this is the last frame
					 */
#घोषणा FZA_PRH1_TKN_SEND_ORIG	0x18	/* send a token of the same type as the
					 * originally captured one
					 */
#घोषणा FZA_PRH1_TKN_SEND_RST	0x10	/* send a restricted token */
#घोषणा FZA_PRH1_TKN_SEND_UNR	0x08	/* send an unrestricted token */
#घोषणा FZA_PRH1_TKN_SEND_NONE	0x00	/* send no token */
#घोषणा FZA_PRH1_EXTRA_FS_MASK	0x07	/* send extra frame status indicators
					 */
#घोषणा FZA_PRH1_EXTRA_FS_ST	0x07	/* TR RR ST II */
#घोषणा FZA_PRH1_EXTRA_FS_SS	0x06	/* TR RR SS II */
#घोषणा FZA_PRH1_EXTRA_FS_SR	0x05	/* TR RR SR II */
#घोषणा FZA_PRH1_EXTRA_FS_NONE1	0x04	/* TR RR II II */
#घोषणा FZA_PRH1_EXTRA_FS_RT	0x03	/* TR RR RT II */
#घोषणा FZA_PRH1_EXTRA_FS_RS	0x02	/* TR RR RS II */
#घोषणा FZA_PRH1_EXTRA_FS_RR	0x01	/* TR RR RR II */
#घोषणा FZA_PRH1_EXTRA_FS_NONE	0x00	/* TR RR II II */
/* Packet request header byte #2. */
#घोषणा FZA_PRH2_NORMAL		0x00	/* always zero */

/* PRH used क्रम LLC frames. */
#घोषणा FZA_PRH0_LLC		(FZA_PRH0_TKN_TYPE_UNR)
#घोषणा FZA_PRH1_LLC		(FZA_PRH1_CRC_NORMAL | FZA_PRH1_TKN_SEND_UNR)
#घोषणा FZA_PRH2_LLC		(FZA_PRH2_NORMAL)

/* PRH used क्रम SMT frames. */
#घोषणा FZA_PRH0_SMT		(FZA_PRH0_TKN_TYPE_UNR)
#घोषणा FZA_PRH1_SMT		(FZA_PRH1_CRC_NORMAL | FZA_PRH1_TKN_SEND_UNR)
#घोषणा FZA_PRH2_SMT		(FZA_PRH2_NORMAL)

#अगर ((FZA_RING_RX_SIZE) < 2) || ((FZA_RING_RX_SIZE) > 256)
# error FZA_RING_RX_SIZE has to be from 2 up to 256
#पूर्ण_अगर
#अगर ((FZA_RING_TX_MODE) != 0) && ((FZA_RING_TX_MODE) != 1)
# error FZA_RING_TX_MODE has to be either 0 or 1
#पूर्ण_अगर

#घोषणा FZA_RING_TX_SIZE (512 << (FZA_RING_TX_MODE))

काष्ठा fza_निजी अणु
	काष्ठा device *bdev;		/* poपूर्णांकer to the bus device */
	स्थिर अक्षर *name;		/* prपूर्णांकable device name */
	व्योम __iomem *mmio;		/* MMIO ioremap cookie */
	काष्ठा fza_regs __iomem *regs;	/* poपूर्णांकer to FZA रेजिस्टरs */

	काष्ठा sk_buff *rx_skbuff[FZA_RING_RX_SIZE];
					/* all skbs asचिन्हित to the host
					 * receive descriptors
					 */
	dma_addr_t rx_dma[FZA_RING_RX_SIZE];
					/* their corresponding DMA addresses */

	काष्ठा fza_ring_cmd __iomem *ring_cmd;
					/* poपूर्णांकer to the command descriptor
					 * ring
					 */
	पूर्णांक ring_cmd_index;		/* index to the command descriptor ring
					 * क्रम the next command
					 */
	काष्ठा fza_ring_uns __iomem *ring_uns;
					/* poपूर्णांकer to the unsolicited
					 * descriptor ring
					 */
	पूर्णांक ring_uns_index;		/* index to the unsolicited descriptor
					 * ring क्रम the next event
					 */

	काष्ठा fza_ring_rmc_tx __iomem *ring_rmc_tx;
					/* poपूर्णांकer to the RMC transmit
					 * descriptor ring (obtained from the
					 * INIT command)
					 */
	पूर्णांक ring_rmc_tx_size;		/* number of entries in the RMC
					 * transmit descriptor ring (obtained
					 * from the INIT command)
					 */
	पूर्णांक ring_rmc_tx_index;		/* index to the RMC transmit descriptor
					 * ring क्रम the next transmission
					 */
	पूर्णांक ring_rmc_txd_index;		/* index to the RMC transmit descriptor
					 * ring क्रम the next transmit करोne
					 * acknowledge
					 */

	काष्ठा fza_ring_hst_rx __iomem *ring_hst_rx;
					/* poपूर्णांकer to the host receive
					 * descriptor ring (obtained from the
					 * INIT command)
					 */
	पूर्णांक ring_hst_rx_size;		/* number of entries in the host
					 * receive descriptor ring (set by the
					 * INIT command)
					 */
	पूर्णांक ring_hst_rx_index;		/* index to the host receive descriptor
					 * ring क्रम the next transmission
					 */

	काष्ठा fza_ring_smt __iomem *ring_smt_tx;
					/* poपूर्णांकer to the SMT transmit
					 * descriptor ring (obtained from the
					 * INIT command)
					 */
	पूर्णांक ring_smt_tx_size;		/* number of entries in the SMT
					 * transmit descriptor ring (obtained
					 * from the INIT command)
					 */
	पूर्णांक ring_smt_tx_index;		/* index to the SMT transmit descriptor
					 * ring क्रम the next transmission
					 */

	काष्ठा fza_ring_smt __iomem *ring_smt_rx;
					/* poपूर्णांकer to the SMT transmit
					 * descriptor ring (obtained from the
					 * INIT command)
					 */
	पूर्णांक ring_smt_rx_size;		/* number of entries in the SMT
					 * receive descriptor ring (obtained
					 * from the INIT command)
					 */
	पूर्णांक ring_smt_rx_index;		/* index to the SMT receive descriptor
					 * ring क्रम the next transmission
					 */

	काष्ठा fza_buffer_tx __iomem *buffer_tx;
					/* poपूर्णांकer to the RMC transmit buffers
					 */

	uपूर्णांक state;			/* adapter expected state */

	spinlock_t lock;		/* क्रम device & निजी data access */
	uपूर्णांक पूर्णांक_mask;			/* पूर्णांकerrupt source selector */

	पूर्णांक cmd_करोne_flag;		/* command completion trigger */
	रुको_queue_head_t cmd_करोne_रुको;

	पूर्णांक state_chg_flag;		/* state change trigger */
	रुको_queue_head_t state_chg_रुको;

	काष्ठा समयr_list reset_समयr;	/* RESET समय-out trigger */
	पूर्णांक समयr_state;		/* RESET trigger state */

	पूर्णांक queue_active;		/* whether to enable queueing */

	काष्ठा net_device_stats stats;

	uपूर्णांक irq_count_flush_tx;	/* transmit flush irqs */
	uपूर्णांक irq_count_uns_poll;	/* unsolicited event irqs */
	uपूर्णांक irq_count_smt_tx_poll;	/* SMT transmit irqs */
	uपूर्णांक irq_count_rx_poll;		/* host receive irqs */
	uपूर्णांक irq_count_tx_करोne;		/* transmit करोne irqs */
	uपूर्णांक irq_count_cmd_करोne;	/* command करोne irqs */
	uपूर्णांक irq_count_state_chg;	/* state change irqs */
	uपूर्णांक irq_count_link_st_chg;	/* link status change irqs */

	uपूर्णांक t_max;			/* T_MAX */
	uपूर्णांक t_req;			/* T_REQ */
	uपूर्णांक tvx;			/* TVX */
	uपूर्णांक lem_threshold;		/* LEM threshold */
	uपूर्णांक station_id[2];		/* station ID */
	uपूर्णांक rtoken_समयout;		/* restricted token समयout */
	uपूर्णांक ring_purger;		/* ring purger enable flag */
पूर्ण;

काष्ठा fza_fddihdr अणु
	u8 pa[2];			/* preamble */
	u8 sd;				/* starting delimiter */
	काष्ठा fddihdr hdr;
पूर्ण __packed;
