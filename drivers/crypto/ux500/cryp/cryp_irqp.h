<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 */

#अगर_अघोषित __CRYP_IRQP_H_
#घोषणा __CRYP_IRQP_H_

#समावेश "cryp_irq.h"

/*
 *
 * CRYP Registers - Offset mapping
 *     +-----------------+
 * 00h | CRYP_CR         |  Configuration रेजिस्टर
 *     +-----------------+
 * 04h | CRYP_SR         |  Status रेजिस्टर
 *     +-----------------+
 * 08h | CRYP_DIN        |  Data In रेजिस्टर
 *     +-----------------+
 * 0ch | CRYP_DOUT       |  Data out रेजिस्टर
 *     +-----------------+
 * 10h | CRYP_DMACR      |  DMA control रेजिस्टर
 *     +-----------------+
 * 14h | CRYP_IMSC       |  IMSC
 *     +-----------------+
 * 18h | CRYP_RIS        |  Raw पूर्णांकerrupt status
 *     +-----------------+
 * 1ch | CRYP_MIS        |  Masked पूर्णांकerrupt status.
 *     +-----------------+
 *       Key रेजिस्टरs
 *       IVR रेजिस्टरs
 *       Peripheral
 *       Cell IDs
 *
 *       Refer data काष्ठाure क्रम other रेजिस्टर map
 */

/**
 * काष्ठा cryp_रेजिस्टर
 * @cr			- Configuration रेजिस्टर
 * @status		- Status रेजिस्टर
 * @din			- Data input रेजिस्टर
 * @din_size		- Data input size रेजिस्टर
 * @करोut		- Data output रेजिस्टर
 * @करोut_size		- Data output size रेजिस्टर
 * @dmacr		- Dma control रेजिस्टर
 * @imsc		- Interrupt mask set/clear रेजिस्टर
 * @ris			- Raw पूर्णांकerrupt status
 * @mis			- Masked पूर्णांकerrupt statu रेजिस्टर
 * @key_1_l		- Key रेजिस्टर 1 L
 * @key_1_r		- Key रेजिस्टर 1 R
 * @key_2_l		- Key रेजिस्टर 2 L
 * @key_2_r		- Key रेजिस्टर 2 R
 * @key_3_l		- Key रेजिस्टर 3 L
 * @key_3_r		- Key रेजिस्टर 3 R
 * @key_4_l		- Key रेजिस्टर 4 L
 * @key_4_r		- Key रेजिस्टर 4 R
 * @init_vect_0_l	- init vector 0 L
 * @init_vect_0_r	- init vector 0 R
 * @init_vect_1_l	- init vector 1 L
 * @init_vect_1_r	- init vector 1 R
 * @cryp_unused1	- unused रेजिस्टरs
 * @itcr		- Integration test control रेजिस्टर
 * @itip		- Integration test input रेजिस्टर
 * @itop		- Integration test output रेजिस्टर
 * @cryp_unused2	- unused रेजिस्टरs
 * @periphId0		- FE0 CRYP Peripheral Identication Register
 * @periphId1		- FE4
 * @periphId2		- FE8
 * @periphId3		- FEC
 * @pcellId0		- FF0  CRYP PCell Identication Register
 * @pcellId1		- FF4
 * @pcellId2		- FF8
 * @pcellId3		- FFC
 */
काष्ठा cryp_रेजिस्टर अणु
	u32 cr;			/* Configuration रेजिस्टर   */
	u32 sr;			/* Status रेजिस्टर          */
	u32 din;		/* Data input रेजिस्टर      */
	u32 din_size;		/* Data input size रेजिस्टर */
	u32 करोut;		/* Data output रेजिस्टर     */
	u32 करोut_size;		/* Data output size रेजिस्टर */
	u32 dmacr;		/* Dma control रेजिस्टर     */
	u32 imsc;		/* Interrupt mask set/clear रेजिस्टर */
	u32 ris;		/* Raw पूर्णांकerrupt status             */
	u32 mis;		/* Masked पूर्णांकerrupt statu रेजिस्टर  */

	u32 key_1_l;		/*Key रेजिस्टर 1 L */
	u32 key_1_r;		/*Key रेजिस्टर 1 R */
	u32 key_2_l;		/*Key रेजिस्टर 2 L */
	u32 key_2_r;		/*Key रेजिस्टर 2 R */
	u32 key_3_l;		/*Key रेजिस्टर 3 L */
	u32 key_3_r;		/*Key रेजिस्टर 3 R */
	u32 key_4_l;		/*Key रेजिस्टर 4 L */
	u32 key_4_r;		/*Key रेजिस्टर 4 R */

	u32 init_vect_0_l;	/*init vector 0 L */
	u32 init_vect_0_r;	/*init vector 0 R */
	u32 init_vect_1_l;	/*init vector 1 L */
	u32 init_vect_1_r;	/*init vector 1 R */

	u32 cryp_unused1[(0x80 - 0x58) / माप(u32)];	/* unused रेजिस्टरs */
	u32 itcr;		/*Integration test control रेजिस्टर */
	u32 itip;		/*Integration test input रेजिस्टर */
	u32 itop;		/*Integration test output रेजिस्टर */
	u32 cryp_unused2[(0xFE0 - 0x8C) / माप(u32)];	/* unused रेजिस्टरs */

	u32 periphId0;		/* FE0  CRYP Peripheral Identication Register */
	u32 periphId1;		/* FE4 */
	u32 periphId2;		/* FE8 */
	u32 periphId3;		/* FEC */

	u32 pcellId0;		/* FF0  CRYP PCell Identication Register */
	u32 pcellId1;		/* FF4 */
	u32 pcellId2;		/* FF8 */
	u32 pcellId3;		/* FFC */
पूर्ण;

#पूर्ण_अगर
