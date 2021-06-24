<शैली गुरु>
/*
 * ricoh.h 1.9 1999/10/25 20:03:34
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

#अगर_अघोषित _LINUX_RICOH_H
#घोषणा _LINUX_RICOH_H


#घोषणा RF5C_MODE_CTL		0x1f	/* Mode control */
#घोषणा RF5C_PWR_CTL		0x2f	/* Mixed voltage control */
#घोषणा RF5C_CHIP_ID		0x3a	/* Chip identअगरication */
#घोषणा RF5C_MODE_CTL_3		0x3b	/* Mode control 3 */

/* I/O winकरोw address offset */
#घोषणा RF5C_IO_OFF(w)		(0x36+((w)<<1))

/* Flags क्रम RF5C_MODE_CTL */
#घोषणा RF5C_MODE_ATA		0x01	/* ATA mode */
#घोषणा RF5C_MODE_LED_ENA	0x02	/* IRQ 12 is LED */
#घोषणा RF5C_MODE_CA21		0x04
#घोषणा RF5C_MODE_CA22		0x08
#घोषणा RF5C_MODE_CA23		0x10
#घोषणा RF5C_MODE_CA24		0x20
#घोषणा RF5C_MODE_CA25		0x40
#घोषणा RF5C_MODE_3STATE_BIT7	0x80

/* Flags क्रम RF5C_PWR_CTL */
#घोषणा RF5C_PWR_VCC_3V		0x01
#घोषणा RF5C_PWR_IREQ_HIGH	0x02
#घोषणा RF5C_PWR_INPACK_ENA	0x04
#घोषणा RF5C_PWR_5V_DET		0x08
#घोषणा RF5C_PWR_TC_SEL		0x10	/* Terminal Count: irq 11 or 15 */
#घोषणा RF5C_PWR_DREQ_LOW	0x20
#घोषणा RF5C_PWR_DREQ_OFF	0x00	/* DREQ steering control */
#घोषणा RF5C_PWR_DREQ_INPACK	0x40
#घोषणा RF5C_PWR_DREQ_SPKR	0x80
#घोषणा RF5C_PWR_DREQ_IOIS16	0xc0

/* Values क्रम RF5C_CHIP_ID */
#घोषणा RF5C_CHIP_RF5C296	0x32
#घोषणा RF5C_CHIP_RF5C396	0xb2

/* Flags क्रम RF5C_MODE_CTL_3 */
#घोषणा RF5C_MCTL3_DISABLE	0x01	/* Disable PCMCIA पूर्णांकerface */
#घोषणा RF5C_MCTL3_DMA_ENA	0x02

/* Register definitions क्रम Ricoh PCI-to-CardBus bridges */

/* Extra bits in CB_BRIDGE_CONTROL */
#घोषणा RL5C46X_BCR_3E0_ENA		0x0800
#घोषणा RL5C46X_BCR_3E2_ENA		0x1000

/* Bridge Configuration Register */
#घोषणा RL5C4XX_CONFIG			0x80	/* 16 bit */
#घोषणा  RL5C4XX_CONFIG_IO_1_MODE	0x0200
#घोषणा  RL5C4XX_CONFIG_IO_0_MODE	0x0100
#घोषणा  RL5C4XX_CONFIG_PREFETCH	0x0001

/* Misc Control Register */
#घोषणा RL5C4XX_MISC			0x0082	/* 16 bit */
#घोषणा  RL5C4XX_MISC_HW_SUSPEND_ENA	0x0002
#घोषणा  RL5C4XX_MISC_VCCEN_POL		0x0100
#घोषणा  RL5C4XX_MISC_VPPEN_POL		0x0200
#घोषणा  RL5C46X_MISC_SUSPEND		0x0001
#घोषणा  RL5C46X_MISC_PWR_SAVE_2	0x0004
#घोषणा  RL5C46X_MISC_IFACE_BUSY	0x0008
#घोषणा  RL5C46X_MISC_B_LOCK		0x0010
#घोषणा  RL5C46X_MISC_A_LOCK		0x0020
#घोषणा  RL5C46X_MISC_PCI_LOCK		0x0040
#घोषणा  RL5C47X_MISC_IFACE_BUSY	0x0004
#घोषणा  RL5C47X_MISC_PCI_INT_MASK	0x0018
#घोषणा  RL5C47X_MISC_PCI_INT_DIS	0x0020
#घोषणा  RL5C47X_MISC_SUBSYS_WR		0x0040
#घोषणा  RL5C47X_MISC_SRIRQ_ENA		0x0080
#घोषणा  RL5C47X_MISC_5V_DISABLE	0x0400
#घोषणा  RL5C47X_MISC_LED_POL		0x0800

/* 16-bit Interface Control Register */
#घोषणा RL5C4XX_16BIT_CTL		0x0084	/* 16 bit */
#घोषणा  RL5C4XX_16CTL_IO_TIMING	0x0100
#घोषणा  RL5C4XX_16CTL_MEM_TIMING	0x0200
#घोषणा  RL5C46X_16CTL_LEVEL_1		0x0010
#घोषणा  RL5C46X_16CTL_LEVEL_2		0x0020

/* 16-bit IO and memory timing रेजिस्टरs */
#घोषणा RL5C4XX_16BIT_IO_0		0x0088	/* 16 bit */
#घोषणा RL5C4XX_16BIT_MEM_0		0x008a	/* 16 bit */
#घोषणा  RL5C4XX_SETUP_MASK		0x0007
#घोषणा  RL5C4XX_SETUP_SHIFT		0
#घोषणा  RL5C4XX_CMD_MASK		0x01f0
#घोषणा  RL5C4XX_CMD_SHIFT		4
#घोषणा  RL5C4XX_HOLD_MASK		0x1c00
#घोषणा  RL5C4XX_HOLD_SHIFT		10
#घोषणा  RL5C4XX_MISC_CONTROL           0x2F /* 8 bit */
#घोषणा  RL5C4XX_ZV_ENABLE              0x08

/* Misc Control 3 Register */
#घोषणा RL5C4XX_MISC3			0x00A2 /* 16 bit */
#घोषणा  RL5C47X_MISC3_CB_CLKRUN_DIS	BIT(1)

#अगर_घोषित __YENTA_H

#घोषणा rl_misc(socket)		((socket)->निजी[0])
#घोषणा rl_ctl(socket)		((socket)->निजी[1])
#घोषणा rl_io(socket)		((socket)->निजी[2])
#घोषणा rl_mem(socket)		((socket)->निजी[3])
#घोषणा rl_config(socket)	((socket)->निजी[4])

अटल व्योम ricoh_zoom_video(काष्ठा pcmcia_socket *sock, पूर्णांक onoff)
अणु
        u8 reg;
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);

        reg = config_पढ़ोb(socket, RL5C4XX_MISC_CONTROL);
        अगर (onoff)
                /* Zoom zoom, we will all go together, zoom zoom, zoom zoom */
                reg |=  RL5C4XX_ZV_ENABLE;
        अन्यथा
                reg &= ~RL5C4XX_ZV_ENABLE;
	
        config_ग_लिखोb(socket, RL5C4XX_MISC_CONTROL, reg);
पूर्ण

अटल व्योम ricoh_set_zv(काष्ठा yenta_socket *socket)
अणु
        अगर(socket->dev->venकरोr == PCI_VENDOR_ID_RICOH)
        अणु
                चयन(socket->dev->device)
                अणु
                        /* There may be more .. */
		हाल  PCI_DEVICE_ID_RICOH_RL5C478:
			socket->socket.zoom_video = ricoh_zoom_video;
			अवरोध;  
                पूर्ण
        पूर्ण
पूर्ण

अटल व्योम ricoh_set_clkrun(काष्ठा yenta_socket *socket, bool quiet)
अणु
	u16 misc3;

	/*
	 * RL5C475II likely has this setting, too, however no datasheet
	 * is खुलाly available क्रम this chip
	 */
	अगर (socket->dev->device != PCI_DEVICE_ID_RICOH_RL5C476 &&
	    socket->dev->device != PCI_DEVICE_ID_RICOH_RL5C478)
		वापस;

	अगर (socket->dev->revision < 0x80)
		वापस;

	misc3 = config_पढ़ोw(socket, RL5C4XX_MISC3);
	अगर (misc3 & RL5C47X_MISC3_CB_CLKRUN_DIS) अणु
		अगर (!quiet)
			dev_dbg(&socket->dev->dev,
				"CLKRUN feature already disabled\n");
	पूर्ण अन्यथा अगर (disable_clkrun) अणु
		अगर (!quiet)
			dev_info(&socket->dev->dev,
				 "Disabling CLKRUN feature\n");
		misc3 |= RL5C47X_MISC3_CB_CLKRUN_DIS;
		config_ग_लिखोw(socket, RL5C4XX_MISC3, misc3);
	पूर्ण
पूर्ण

अटल व्योम ricoh_save_state(काष्ठा yenta_socket *socket)
अणु
	rl_misc(socket) = config_पढ़ोw(socket, RL5C4XX_MISC);
	rl_ctl(socket) = config_पढ़ोw(socket, RL5C4XX_16BIT_CTL);
	rl_io(socket) = config_पढ़ोw(socket, RL5C4XX_16BIT_IO_0);
	rl_mem(socket) = config_पढ़ोw(socket, RL5C4XX_16BIT_MEM_0);
	rl_config(socket) = config_पढ़ोw(socket, RL5C4XX_CONFIG);
पूर्ण

अटल व्योम ricoh_restore_state(काष्ठा yenta_socket *socket)
अणु
	config_ग_लिखोw(socket, RL5C4XX_MISC, rl_misc(socket));
	config_ग_लिखोw(socket, RL5C4XX_16BIT_CTL, rl_ctl(socket));
	config_ग_लिखोw(socket, RL5C4XX_16BIT_IO_0, rl_io(socket));
	config_ग_लिखोw(socket, RL5C4XX_16BIT_MEM_0, rl_mem(socket));
	config_ग_लिखोw(socket, RL5C4XX_CONFIG, rl_config(socket));
	ricoh_set_clkrun(socket, true);
पूर्ण


/*
 * Magic Ricoh initialization code..
 */
अटल पूर्णांक ricoh_override(काष्ठा yenta_socket *socket)
अणु
	u16 config, ctl;

	config = config_पढ़ोw(socket, RL5C4XX_CONFIG);

	/* Set the शेष timings, करोn't trust the original values */
	ctl = RL5C4XX_16CTL_IO_TIMING | RL5C4XX_16CTL_MEM_TIMING;

	अगर(socket->dev->device < PCI_DEVICE_ID_RICOH_RL5C475) अणु
		ctl |= RL5C46X_16CTL_LEVEL_1 | RL5C46X_16CTL_LEVEL_2;
	पूर्ण अन्यथा अणु
		config |= RL5C4XX_CONFIG_PREFETCH;
	पूर्ण

	config_ग_लिखोw(socket, RL5C4XX_16BIT_CTL, ctl);
	config_ग_लिखोw(socket, RL5C4XX_CONFIG, config);

	ricoh_set_zv(socket);
	ricoh_set_clkrun(socket, false);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_CARDBUS */

#पूर्ण_अगर /* _LINUX_RICOH_H */
