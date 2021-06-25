<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_ENET_FEC_H
#घोषणा FS_ENET_FEC_H

#घोषणा FEC_MAX_MULTICAST_ADDRS	64

/* Interrupt events/masks.
*/
#घोषणा FEC_ENET_HBERR	0x80000000U	/* Heartbeat error          */
#घोषणा FEC_ENET_BABR	0x40000000U	/* Babbling receiver        */
#घोषणा FEC_ENET_BABT	0x20000000U	/* Babbling transmitter     */
#घोषणा FEC_ENET_GRA	0x10000000U	/* Graceful stop complete   */
#घोषणा FEC_ENET_TXF	0x08000000U	/* Full frame transmitted   */
#घोषणा FEC_ENET_TXB	0x04000000U	/* A buffer was transmitted */
#घोषणा FEC_ENET_RXF	0x02000000U	/* Full frame received      */
#घोषणा FEC_ENET_RXB	0x01000000U	/* A buffer was received    */
#घोषणा FEC_ENET_MII	0x00800000U	/* MII पूर्णांकerrupt            */
#घोषणा FEC_ENET_EBERR	0x00400000U	/* SDMA bus error           */

#घोषणा FEC_ECNTRL_PINMUX	0x00000004
#घोषणा FEC_ECNTRL_ETHER_EN	0x00000002
#घोषणा FEC_ECNTRL_RESET	0x00000001

/* RMII mode enabled only when MII_MODE bit is set too. */
#घोषणा FEC_RCNTRL_RMII_MODE	(0x00000100 | \
				 FEC_RCNTRL_MII_MODE | FEC_RCNTRL_FCE)
#घोषणा FEC_RCNTRL_FCE		0x00000020
#घोषणा FEC_RCNTRL_BC_REJ	0x00000010
#घोषणा FEC_RCNTRL_PROM		0x00000008
#घोषणा FEC_RCNTRL_MII_MODE	0x00000004
#घोषणा FEC_RCNTRL_DRT		0x00000002
#घोषणा FEC_RCNTRL_LOOP		0x00000001

#घोषणा FEC_TCNTRL_FDEN		0x00000004
#घोषणा FEC_TCNTRL_HBC		0x00000002
#घोषणा FEC_TCNTRL_GTS		0x00000001

/*
 * Delay to रुको क्रम FEC reset command to complete (in us)
 */
#घोषणा FEC_RESET_DELAY		50
#पूर्ण_अगर
