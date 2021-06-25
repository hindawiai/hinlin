<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __YENTA_H
#घोषणा __YENTA_H

#समावेश <यंत्र/पन.स>

#घोषणा CB_SOCKET_EVENT		0x00
#घोषणा    CB_CSTSEVENT		0x00000001	/* Card status event */
#घोषणा    CB_CD1EVENT		0x00000002	/* Card detect 1 change event */
#घोषणा    CB_CD2EVENT		0x00000004	/* Card detect 2 change event */
#घोषणा    CB_PWREVENT		0x00000008	/* PWRCYCLE change event */

#घोषणा CB_SOCKET_MASK		0x04
#घोषणा    CB_CSTSMASK		0x00000001	/* Card status mask */
#घोषणा    CB_CDMASK		0x00000006	/* Card detect 1&2 mask */
#घोषणा    CB_PWRMASK		0x00000008	/* PWRCYCLE change mask */

#घोषणा CB_SOCKET_STATE		0x08
#घोषणा    CB_CARDSTS		0x00000001	/* CSTSCHG status */
#घोषणा    CB_CDETECT1		0x00000002	/* Card detect status 1 */
#घोषणा    CB_CDETECT2		0x00000004	/* Card detect status 2 */
#घोषणा    CB_PWRCYCLE		0x00000008	/* Socket घातered */
#घोषणा    CB_16BITCARD		0x00000010	/* 16-bit card detected */
#घोषणा    CB_CBCARD		0x00000020	/* CardBus card detected */
#घोषणा    CB_IREQCINT		0x00000040	/* READY(xIRQ)/xCINT high */
#घोषणा    CB_NOTACARD		0x00000080	/* Unrecognizable PC card detected */
#घोषणा    CB_DATALOST		0x00000100	/* Potential data loss due to card removal */
#घोषणा    CB_BADVCCREQ		0x00000200	/* Invalid Vcc request by host software */
#घोषणा    CB_5VCARD		0x00000400	/* Card Vcc at 5.0 volts? */
#घोषणा    CB_3VCARD		0x00000800	/* Card Vcc at 3.3 volts? */
#घोषणा    CB_XVCARD		0x00001000	/* Card Vcc at X.X volts? */
#घोषणा    CB_YVCARD		0x00002000	/* Card Vcc at Y.Y volts? */
#घोषणा    CB_5VSOCKET		0x10000000	/* Socket Vcc at 5.0 volts? */
#घोषणा    CB_3VSOCKET		0x20000000	/* Socket Vcc at 3.3 volts? */
#घोषणा    CB_XVSOCKET		0x40000000	/* Socket Vcc at X.X volts? */
#घोषणा    CB_YVSOCKET		0x80000000	/* Socket Vcc at Y.Y volts? */

#घोषणा CB_SOCKET_FORCE		0x0C
#घोषणा    CB_FCARDSTS		0x00000001	/* Force CSTSCHG */
#घोषणा    CB_FCDETECT1		0x00000002	/* Force CD1EVENT */
#घोषणा    CB_FCDETECT2		0x00000004	/* Force CD2EVENT */
#घोषणा    CB_FPWRCYCLE		0x00000008	/* Force PWREVENT */
#घोषणा    CB_F16BITCARD	0x00000010	/* Force 16-bit PCMCIA card */
#घोषणा    CB_FCBCARD		0x00000020	/* Force CardBus line */
#घोषणा    CB_FNOTACARD		0x00000080	/* Force NOTACARD */
#घोषणा    CB_FDATALOST		0x00000100	/* Force data lost */
#घोषणा    CB_FBADVCCREQ	0x00000200	/* Force bad Vcc request */
#घोषणा    CB_F5VCARD		0x00000400	/* Force 5.0 volt card */
#घोषणा    CB_F3VCARD		0x00000800	/* Force 3.3 volt card */
#घोषणा    CB_FXVCARD		0x00001000	/* Force X.X volt card */
#घोषणा    CB_FYVCARD		0x00002000	/* Force Y.Y volt card */
#घोषणा    CB_CVSTEST		0x00004000	/* Card VS test */

#घोषणा CB_SOCKET_CONTROL	0x10
#घोषणा  CB_SC_VPP_MASK		0x00000007
#घोषणा   CB_SC_VPP_OFF		0x00000000
#घोषणा   CB_SC_VPP_12V		0x00000001
#घोषणा   CB_SC_VPP_5V		0x00000002
#घोषणा   CB_SC_VPP_3V		0x00000003
#घोषणा   CB_SC_VPP_XV		0x00000004
#घोषणा   CB_SC_VPP_YV		0x00000005
#घोषणा  CB_SC_VCC_MASK		0x00000070
#घोषणा   CB_SC_VCC_OFF		0x00000000
#घोषणा   CB_SC_VCC_5V		0x00000020
#घोषणा   CB_SC_VCC_3V		0x00000030
#घोषणा   CB_SC_VCC_XV		0x00000040
#घोषणा   CB_SC_VCC_YV		0x00000050
#घोषणा  CB_SC_CCLK_STOP	0x00000080

#घोषणा CB_SOCKET_POWER		0x20
#घोषणा    CB_SKTACCES		0x02000000	/* A PC card access has occurred (clear on पढ़ो) */
#घोषणा    CB_SKTMODE		0x01000000	/* Clock frequency has changed (clear on पढ़ो) */
#घोषणा    CB_CLKCTRLEN		0x00010000	/* Clock control enabled (RW) */
#घोषणा    CB_CLKCTRL		0x00000001	/* Stop(0) or slow(1) CB घड़ी (RW) */

/*
 * Cardbus configuration space
 */
#घोषणा CB_BRIDGE_BASE(m)	(0x1c + 8*(m))
#घोषणा CB_BRIDGE_LIMIT(m)	(0x20 + 8*(m))
#घोषणा CB_BRIDGE_CONTROL	0x3e
#घोषणा   CB_BRIDGE_CPERREN	0x00000001
#घोषणा   CB_BRIDGE_CSERREN	0x00000002
#घोषणा   CB_BRIDGE_ISAEN	0x00000004
#घोषणा   CB_BRIDGE_VGAEN	0x00000008
#घोषणा   CB_BRIDGE_MABTMODE	0x00000020
#घोषणा   CB_BRIDGE_CRST	0x00000040
#घोषणा   CB_BRIDGE_INTR	0x00000080
#घोषणा   CB_BRIDGE_PREFETCH0	0x00000100
#घोषणा   CB_BRIDGE_PREFETCH1	0x00000200
#घोषणा   CB_BRIDGE_POSTEN	0x00000400
#घोषणा CB_LEGACY_MODE_BASE	0x44

/*
 * ExCA area extensions in Yenta
 */
#घोषणा CB_MEM_PAGE(map)	(0x40 + (map))


/* control how 16bit cards are घातered */
#घोषणा YENTA_16BIT_POWER_EXCA	0x00000001
#घोषणा YENTA_16BIT_POWER_DF	0x00000002


काष्ठा yenta_socket;

काष्ठा cardbus_type अणु
	पूर्णांक	(*override)(काष्ठा yenta_socket *);
	व्योम	(*save_state)(काष्ठा yenta_socket *);
	व्योम	(*restore_state)(काष्ठा yenta_socket *);
	पूर्णांक	(*sock_init)(काष्ठा yenta_socket *);
पूर्ण;

काष्ठा yenta_socket अणु
	काष्ठा pci_dev *dev;
	पूर्णांक cb_irq, io_irq;
	व्योम __iomem *base;
	काष्ठा समयr_list poll_समयr;

	काष्ठा pcmcia_socket socket;
	काष्ठा cardbus_type *type;

	u32 flags;

	/* क्रम PCI पूर्णांकerrupt probing */
	अचिन्हित पूर्णांक probe_status;

	/* A few words of निजी data क्रम special stuff of overrides... */
	अचिन्हित पूर्णांक निजी[8];

	/* PCI saved state */
	u32 saved_state[2];
पूर्ण;


#पूर्ण_अगर
