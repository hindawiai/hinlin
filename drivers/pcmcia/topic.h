<शैली गुरु>
/*
 * topic.h 1.8 1999/08/28 04:01:47
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
 * topic.h $Release$ 1999/08/28 04:01:47
 */

#अगर_अघोषित _LINUX_TOPIC_H
#घोषणा _LINUX_TOPIC_H

/* Register definitions क्रम Toshiba ToPIC95/97/100 controllers */

#घोषणा TOPIC_SOCKET_CONTROL		0x0090	/* 32 bit */
#घोषणा  TOPIC_SCR_IRQSEL		0x00000001

#घोषणा TOPIC_SLOT_CONTROL		0x00a0	/* 8 bit */
#घोषणा  TOPIC_SLOT_SLOTON		0x80
#घोषणा  TOPIC_SLOT_SLOTEN		0x40
#घोषणा  TOPIC_SLOT_ID_LOCK		0x20
#घोषणा  TOPIC_SLOT_ID_WP		0x10
#घोषणा  TOPIC_SLOT_PORT_MASK		0x0c
#घोषणा  TOPIC_SLOT_PORT_SHIFT		2
#घोषणा  TOPIC_SLOT_OFS_MASK		0x03

#घोषणा TOPIC_CARD_CONTROL		0x00a1	/* 8 bit */
#घोषणा  TOPIC_CCR_INTB			0x20
#घोषणा  TOPIC_CCR_INTA			0x10
#घोषणा  TOPIC_CCR_CLOCK		0x0c
#घोषणा  TOPIC_CCR_PCICLK		0x0c
#घोषणा  TOPIC_CCR_PCICLK_2		0x08
#घोषणा  TOPIC_CCR_CCLK			0x04

#घोषणा TOPIC97_INT_CONTROL		0x00a1	/* 8 bit */
#घोषणा  TOPIC97_ICR_INTB		0x20
#घोषणा  TOPIC97_ICR_INTA		0x10
#घोषणा  TOPIC97_ICR_STSIRQNP		0x04
#घोषणा  TOPIC97_ICR_IRQNP		0x02
#घोषणा  TOPIC97_ICR_IRQSEL		0x01

#घोषणा TOPIC_CARD_DETECT		0x00a3	/* 8 bit */
#घोषणा  TOPIC_CDR_MODE_PC32		0x80
#घोषणा  TOPIC_CDR_VS1			0x04
#घोषणा  TOPIC_CDR_VS2			0x02
#घोषणा  TOPIC_CDR_SW_DETECT		0x01

#घोषणा TOPIC_REGISTER_CONTROL		0x00a4	/* 32 bit */
#घोषणा  TOPIC_RCR_RESUME_RESET		0x80000000
#घोषणा  TOPIC_RCR_REMOVE_RESET		0x40000000
#घोषणा  TOPIC97_RCR_CLKRUN_ENA		0x20000000
#घोषणा  TOPIC97_RCR_TESTMODE		0x10000000
#घोषणा  TOPIC97_RCR_IOPLUP		0x08000000
#घोषणा  TOPIC_RCR_BUFOFF_PWROFF	0x02000000
#घोषणा  TOPIC_RCR_BUFOFF_SIGOFF	0x01000000
#घोषणा  TOPIC97_RCR_CB_DEV_MASK	0x0000f800
#घोषणा  TOPIC97_RCR_CB_DEV_SHIFT	11
#घोषणा  TOPIC97_RCR_RI_DISABLE		0x00000004
#घोषणा  TOPIC97_RCR_CAUDIO_OFF		0x00000002
#घोषणा  TOPIC_RCR_CAUDIO_INVERT	0x00000001

#घोषणा TOPIC97_MISC1			0x00ad  /* 8bit */
#घोषणा  TOPIC97_MISC1_CLOCKRUN_ENABLE	0x80
#घोषणा  TOPIC97_MISC1_CLOCKRUN_MODE	0x40
#घोषणा  TOPIC97_MISC1_DETECT_REQ_ENA	0x10
#घोषणा  TOPIC97_MISC1_SCK_CLEAR_DIS	0x04
#घोषणा  TOPIC97_MISC1_R2_LOW_ENABLE	0x10

#घोषणा TOPIC97_MISC2			0x00ae  /* 8 bit */
#घोषणा  TOPIC97_MISC2_SPWRCLK_MASK	0x70
#घोषणा  TOPIC97_MISC2_SPWRMOD		0x08
#घोषणा  TOPIC97_MISC2_SPWR_ENABLE	0x04
#घोषणा  TOPIC97_MISC2_ZV_MODE		0x02
#घोषणा  TOPIC97_MISC2_ZV_ENABLE	0x01

#घोषणा TOPIC97_ZOOM_VIDEO_CONTROL	0x009c  /* 8 bit */
#घोषणा  TOPIC97_ZV_CONTROL_ENABLE	0x01

#घोषणा TOPIC97_AUDIO_VIDEO_SWITCH	0x003c  /* 8 bit */
#घोषणा  TOPIC97_AVS_AUDIO_CONTROL	0x02
#घोषणा  TOPIC97_AVS_VIDEO_CONTROL	0x01

#घोषणा TOPIC_EXCA_IF_CONTROL		0x3e	/* 8 bit */
#घोषणा TOPIC_EXCA_IFC_33V_ENA		0x01

#घोषणा TOPIC_PCI_CFG_PPBCN		0x3e	/* 16-bit */
#घोषणा TOPIC_PCI_CFG_PPBCN_WBEN	0x0400

अटल व्योम topic97_zoom_video(काष्ठा pcmcia_socket *sock, पूर्णांक onoff)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	u8 reg_zv, reg;

	reg_zv = config_पढ़ोb(socket, TOPIC97_ZOOM_VIDEO_CONTROL);
	अगर (onoff) अणु
		reg_zv |= TOPIC97_ZV_CONTROL_ENABLE;
		config_ग_लिखोb(socket, TOPIC97_ZOOM_VIDEO_CONTROL, reg_zv);

		reg = config_पढ़ोb(socket, TOPIC97_AUDIO_VIDEO_SWITCH);
		reg |= TOPIC97_AVS_AUDIO_CONTROL | TOPIC97_AVS_VIDEO_CONTROL;
		config_ग_लिखोb(socket, TOPIC97_AUDIO_VIDEO_SWITCH, reg);
	पूर्ण अन्यथा अणु
		reg_zv &= ~TOPIC97_ZV_CONTROL_ENABLE;
		config_ग_लिखोb(socket, TOPIC97_ZOOM_VIDEO_CONTROL, reg_zv);

		reg = config_पढ़ोb(socket, TOPIC97_AUDIO_VIDEO_SWITCH);
		reg &= ~(TOPIC97_AVS_AUDIO_CONTROL | TOPIC97_AVS_VIDEO_CONTROL);
		config_ग_लिखोb(socket, TOPIC97_AUDIO_VIDEO_SWITCH, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक topic97_override(काष्ठा yenta_socket *socket)
अणु
	/* ToPIC97/100 support ZV */
	socket->socket.zoom_video = topic97_zoom_video;
	वापस 0;
पूर्ण


अटल पूर्णांक topic95_override(काष्ठा yenta_socket *socket)
अणु
	u8 fctrl;
	u16 ppbcn;

	/* enable 3.3V support क्रम 16bit cards */
	fctrl = exca_पढ़ोb(socket, TOPIC_EXCA_IF_CONTROL);
	exca_ग_लिखोb(socket, TOPIC_EXCA_IF_CONTROL, fctrl | TOPIC_EXCA_IFC_33V_ENA);

	/* tell yenta to use exca रेजिस्टरs to घातer 16bit cards */
	socket->flags |= YENTA_16BIT_POWER_EXCA | YENTA_16BIT_POWER_DF;

	/* Disable ग_लिखो buffers to prevent lockups under load with numerous
	   Cardbus cards, observed on Tecra 500CDT and reported अन्यथाwhere on the
	   net.  This is not a घातer-on शेष according to the datasheet
	   but some BIOSes seem to set it. */
	अगर (pci_पढ़ो_config_word(socket->dev, TOPIC_PCI_CFG_PPBCN, &ppbcn) == 0
	    && socket->dev->revision <= 7
	    && (ppbcn & TOPIC_PCI_CFG_PPBCN_WBEN)) अणु
		ppbcn &= ~TOPIC_PCI_CFG_PPBCN_WBEN;
		pci_ग_लिखो_config_word(socket->dev, TOPIC_PCI_CFG_PPBCN, ppbcn);
		dev_info(&socket->dev->dev, "Disabled ToPIC95 Cardbus write buffers.\n");
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* _LINUX_TOPIC_H */
