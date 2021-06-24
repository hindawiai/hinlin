<शैली गुरु>
/*
 * o2micro.h 1.13 1999/10/25 20:03:34
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License. 
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in which
 * हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#अगर_अघोषित _LINUX_O2MICRO_H
#घोषणा _LINUX_O2MICRO_H

/* Additional PCI configuration रेजिस्टरs */

#घोषणा O2_MUX_CONTROL		0x90	/* 32 bit */
#घोषणा  O2_MUX_RING_OUT	0x0000000f
#घोषणा  O2_MUX_SKTB_ACTV	0x000000f0
#घोषणा  O2_MUX_SCTA_ACTV_ENA	0x00000100
#घोषणा  O2_MUX_SCTB_ACTV_ENA	0x00000200
#घोषणा  O2_MUX_SER_IRQ_ROUTE	0x0000e000
#घोषणा  O2_MUX_SER_PCI		0x00010000

#घोषणा  O2_MUX_SKTA_TURBO	0x000c0000	/* क्रम 6833, 6860 */
#घोषणा  O2_MUX_SKTB_TURBO	0x00300000
#घोषणा  O2_MUX_AUX_VCC_3V	0x00400000
#घोषणा  O2_MUX_PCI_VCC_5V	0x00800000
#घोषणा  O2_MUX_PME_MUX		0x0f000000

/* Additional ExCA रेजिस्टरs */

#घोषणा O2_MODE_A		0x38
#घोषणा O2_MODE_A_2		0x26	/* क्रम 6833B, 6860C */
#घोषणा  O2_MODE_A_CD_PULSE	0x04
#घोषणा  O2_MODE_A_SUSP_EDGE	0x08
#घोषणा  O2_MODE_A_HOST_SUSP	0x10
#घोषणा  O2_MODE_A_PWR_MASK	0x60
#घोषणा  O2_MODE_A_QUIET	0x80

#घोषणा O2_MODE_B		0x39
#घोषणा O2_MODE_B_2		0x2e	/* क्रम 6833B, 6860C */
#घोषणा  O2_MODE_B_IDENT	0x03
#घोषणा  O2_MODE_B_ID_BSTEP	0x00
#घोषणा  O2_MODE_B_ID_CSTEP	0x01
#घोषणा  O2_MODE_B_ID_O2	0x02
#घोषणा  O2_MODE_B_VS1		0x04
#घोषणा  O2_MODE_B_VS2		0x08
#घोषणा  O2_MODE_B_IRQ15_RI	0x80

#घोषणा O2_MODE_C		0x3a
#घोषणा  O2_MODE_C_DREQ_MASK	0x03
#घोषणा  O2_MODE_C_DREQ_INPACK	0x01
#घोषणा  O2_MODE_C_DREQ_WP	0x02
#घोषणा  O2_MODE_C_DREQ_BVD2	0x03
#घोषणा  O2_MODE_C_ZVIDEO	0x08
#घोषणा  O2_MODE_C_IREQ_SEL	0x30
#घोषणा  O2_MODE_C_MGMT_SEL	0xc0

#घोषणा O2_MODE_D		0x3b
#घोषणा  O2_MODE_D_IRQ_MODE	0x03
#घोषणा  O2_MODE_D_PCI_CLKRUN	0x04
#घोषणा  O2_MODE_D_CB_CLKRUN	0x08
#घोषणा  O2_MODE_D_SKT_ACTV	0x20
#घोषणा  O2_MODE_D_PCI_FIFO	0x40	/* क्रम OZ6729, OZ6730 */
#घोषणा  O2_MODE_D_W97_IRQ	0x40
#घोषणा  O2_MODE_D_ISA_IRQ	0x80

#घोषणा O2_MHPG_DMA		0x3c
#घोषणा  O2_MHPG_CHANNEL	0x07
#घोषणा  O2_MHPG_CINT_ENA	0x08
#घोषणा  O2_MHPG_CSC_ENA	0x10

#घोषणा O2_FIFO_ENA		0x3d
#घोषणा  O2_FIFO_ZVIDEO_3	0x08
#घोषणा  O2_FIFO_PCI_FIFO	0x10
#घोषणा  O2_FIFO_POSTWR		0x40
#घोषणा  O2_FIFO_BUFFER		0x80

#घोषणा O2_MODE_E		0x3e
#घोषणा  O2_MODE_E_MHPG_DMA	0x01
#घोषणा  O2_MODE_E_SPKR_OUT	0x02
#घोषणा  O2_MODE_E_LED_OUT	0x08
#घोषणा  O2_MODE_E_SKTA_ACTV	0x10

#घोषणा O2_RESERVED1		0x94
#घोषणा O2_RESERVED2		0xD4
#घोषणा O2_RES_READ_PREFETCH	0x02
#घोषणा O2_RES_WRITE_BURST	0x08

अटल पूर्णांक o2micro_override(काष्ठा yenta_socket *socket)
अणु
	/*
	 * 'reserved' रेजिस्टर at 0x94/D4. allows setting पढ़ो prefetch and ग_लिखो
	 * bursting. पढ़ो prefetching क्रम example makes the RME Hammerfall DSP
	 * working. क्रम some bridges it is at 0x94, क्रम others at 0xD4. it's
	 * ok to ग_लिखो to both रेजिस्टरs on all O2 bridges.
	 * from Eric Still, 02Micro.
	 */
	u8 a, b;
	bool use_speedup;

	अगर (PCI_FUNC(socket->dev->devfn) == 0) अणु
		a = config_पढ़ोb(socket, O2_RESERVED1);
		b = config_पढ़ोb(socket, O2_RESERVED2);
		dev_dbg(&socket->dev->dev, "O2: 0x94/0xD4: %02x/%02x\n", a, b);

		चयन (socket->dev->device) अणु
		/*
		 * older bridges have problems with both पढ़ो prefetch and ग_लिखो
		 * bursting depending on the combination of the chipset, bridge
		 * and the cardbus card. so disable them to be on the safe side.
		 */
		हाल PCI_DEVICE_ID_O2_6729:
		हाल PCI_DEVICE_ID_O2_6730:
		हाल PCI_DEVICE_ID_O2_6812:
		हाल PCI_DEVICE_ID_O2_6832:
		हाल PCI_DEVICE_ID_O2_6836:
		हाल PCI_DEVICE_ID_O2_6933:
			use_speedup = false;
			अवरोध;
		शेष:
			use_speedup = true;
			अवरोध;
		पूर्ण

		/* the user may override our decision */
		अगर (strहालcmp(o2_speedup, "on") == 0)
			use_speedup = true;
		अन्यथा अगर (strहालcmp(o2_speedup, "off") == 0)
			use_speedup = false;
		अन्यथा अगर (strहालcmp(o2_speedup, "default") != 0)
			dev_warn(&socket->dev->dev,
				"O2: Unknown parameter, using 'default'");

		अगर (use_speedup) अणु
			dev_info(&socket->dev->dev,
				"O2: enabling read prefetch/write burst. If you experience problems or performance issues, use the yenta_socket parameter 'o2_speedup=off'\n");
			config_ग_लिखोb(socket, O2_RESERVED1,
				      a | O2_RES_READ_PREFETCH | O2_RES_WRITE_BURST);
			config_ग_लिखोb(socket, O2_RESERVED2,
				      b | O2_RES_READ_PREFETCH | O2_RES_WRITE_BURST);
		पूर्ण अन्यथा अणु
			dev_info(&socket->dev->dev,
				"O2: disabling read prefetch/write burst. If you experience problems or performance issues, use the yenta_socket parameter 'o2_speedup=on'\n");
			config_ग_लिखोb(socket, O2_RESERVED1,
				      a & ~(O2_RES_READ_PREFETCH | O2_RES_WRITE_BURST));
			config_ग_लिखोb(socket, O2_RESERVED2,
				      b & ~(O2_RES_READ_PREFETCH | O2_RES_WRITE_BURST));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम o2micro_restore_state(काष्ठा yenta_socket *socket)
अणु
	/*
	 * as दीर्घ as पढ़ो prefetch is the only thing in
	 * o2micro_override, it's safe to call it from here
	 */
	o2micro_override(socket);
पूर्ण

#पूर्ण_अगर /* _LINUX_O2MICRO_H */
