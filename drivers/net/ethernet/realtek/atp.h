<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Linux header file क्रम the ATP pocket ethernet adapter. */
/* v1.09 8/9/2000 becker@scyld.com. */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/types.h>

/* The header prepended to received packets. */
काष्ठा rx_header अणु
	uलघु pad;		/* Pad. */
	uलघु rx_count;
	uलघु rx_status;	/* Unknown bit assignments :-<.  */
	uलघु cur_addr;	/* Apparently the current buffer address(?) */
पूर्ण;

#घोषणा PAR_DATA	0
#घोषणा PAR_STATUS	1
#घोषणा PAR_CONTROL 2

#घोषणा Ctrl_LNibRead	0x08	/* LP_PSELECP */
#घोषणा Ctrl_HNibRead	0
#घोषणा Ctrl_LNibWrite	0x08	/* LP_PSELECP */
#घोषणा Ctrl_HNibWrite	0
#घोषणा Ctrl_SelData	0x04	/* LP_PINITP */
#घोषणा Ctrl_IRQEN	0x10	/* LP_PINTEN */

#घोषणा EOW	0xE0
#घोषणा EOC	0xE0
#घोषणा WrAddr	0x40	/* Set address of EPLC पढ़ो, ग_लिखो रेजिस्टर. */
#घोषणा RdAddr	0xC0
#घोषणा HNib	0x10

क्रमागत page0_regs अणु
	/* The first six रेजिस्टरs hold
	 * the ethernet physical station address.
	 */
	PAR0 = 0, PAR1 = 1, PAR2 = 2, PAR3 = 3, PAR4 = 4, PAR5 = 5,
	TxCNT0 = 6, TxCNT1 = 7,		/* The transmit byte count. */
	TxSTAT = 8, RxSTAT = 9,		/* Tx and Rx status. */
	ISR = 10, IMR = 11,		/* Interrupt status and mask. */
	CMR1 = 12,			/* Command रेजिस्टर 1. */
	CMR2 = 13,			/* Command रेजिस्टर 2. */
	MODSEL = 14,		/* Mode select रेजिस्टर. */
	MAR = 14,			/* Memory address रेजिस्टर (?). */
	CMR2_h = 0x1d,
पूर्ण;

क्रमागत eepage_regs अणु
	PROM_CMD = 6,
	PROM_DATA = 7	/* Note that PROM_CMD is in the "high" bits. */
पूर्ण;

#घोषणा ISR_TxOK	0x01
#घोषणा ISR_RxOK	0x04
#घोषणा ISR_TxErr	0x02
#घोषणा ISRh_RxErr	0x11	/* ISR, high nibble */

#घोषणा CMR1h_MUX	0x08	/* Select prपूर्णांकer multiplexor on 8012. */
#घोषणा CMR1h_RESET	0x04	/* Reset. */
#घोषणा CMR1h_RxENABLE	0x02	/* Rx unit enable.  */
#घोषणा CMR1h_TxENABLE	0x01	/* Tx unit enable.  */
#घोषणा CMR1h_TxRxOFF	0x00
#घोषणा CMR1_ReXmit	0x08	/* Trigger a retransmit. */
#घोषणा CMR1_Xmit	0x04	/* Trigger a transmit. */
#घोषणा	CMR1_IRQ	0x02	/* Interrupt active. */
#घोषणा	CMR1_BufEnb	0x01	/* Enable the buffer(?). */
#घोषणा	CMR1_NextPkt	0x01	/* Enable the buffer(?). */

#घोषणा CMR2_शून्य	8
#घोषणा CMR2_IRQOUT	9
#घोषणा CMR2_RAMTEST	10
#घोषणा CMR2_EEPROM	12	/* Set to page 1, क्रम पढ़ोing the EEPROM. */

#घोषणा CMR2h_OFF	0	/* No accept mode. */
#घोषणा CMR2h_Physical	1	/* Accept a physical address match only. */
#घोषणा CMR2h_Normal	2	/* Accept physical and broadcast address. */
#घोषणा CMR2h_PROMISC	3	/* Promiscuous mode. */

/* An अंतरभूत function used below: it dअगरfers from inb() by explicitly
 * वापस an अचिन्हित अक्षर, saving a truncation.
 */
अटल अंतरभूत अचिन्हित अक्षर inbyte(अचिन्हित लघु port)
अणु
	अचिन्हित अक्षर _v;

	__यंत्र__ __अस्थिर__ ("inb %w1,%b0" : "=a" (_v) : "d" (port));
	वापस _v;
पूर्ण

/* Read रेजिस्टर OFFSET.
 * This command should always be terminated with पढ़ो_end().
 */
अटल अंतरभूत अचिन्हित अक्षर पढ़ो_nibble(लघु port, अचिन्हित अक्षर offset)
अणु
	अचिन्हित अक्षर retval;

	outb(EOC+offset, port + PAR_DATA);
	outb(RdAddr+offset, port + PAR_DATA);
	inbyte(port + PAR_STATUS);	/* Settling समय delay */
	retval = inbyte(port + PAR_STATUS);
	outb(EOC+offset, port + PAR_DATA);

	वापस retval;
पूर्ण

/* Functions क्रम bulk data पढ़ो.  The पूर्णांकerrupt line is always disabled. */
/* Get a byte using पढ़ो mode 0, पढ़ोing data from the control lines. */
अटल अंतरभूत अचिन्हित अक्षर पढ़ो_byte_mode0(लघु ioaddr)
अणु
	अचिन्हित अक्षर low_nib;

	outb(Ctrl_LNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);
	low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
	outb(Ctrl_HNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);	/* Settling समय delay -- needed!  */
	inbyte(ioaddr + PAR_STATUS);	/* Settling समय delay -- needed!  */
	वापस low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
पूर्ण

/* The same as पढ़ो_byte_mode0(), but करोes multiple inb()s क्रम stability. */
अटल अंतरभूत अचिन्हित अक्षर पढ़ो_byte_mode2(लघु ioaddr)
अणु
	अचिन्हित अक्षर low_nib;

	outb(Ctrl_LNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);
	low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
	outb(Ctrl_HNibRead, ioaddr + PAR_CONTROL);
	inbyte(ioaddr + PAR_STATUS);	/* Settling समय delay -- needed!  */
	वापस low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
पूर्ण

/* Read a byte through the data रेजिस्टर. */
अटल अंतरभूत अचिन्हित अक्षर पढ़ो_byte_mode4(लघु ioaddr)
अणु
	अचिन्हित अक्षर low_nib;

	outb(RdAddr | MAR, ioaddr + PAR_DATA);
	low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
	outb(RdAddr | HNib | MAR, ioaddr + PAR_DATA);
	वापस low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
पूर्ण

/* Read a byte through the data रेजिस्टर, द्विगुन पढ़ोing to allow settling. */
अटल अंतरभूत अचिन्हित अक्षर पढ़ो_byte_mode6(लघु ioaddr)
अणु
	अचिन्हित अक्षर low_nib;

	outb(RdAddr | MAR, ioaddr + PAR_DATA);
	inbyte(ioaddr + PAR_STATUS);
	low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
	outb(RdAddr | HNib | MAR, ioaddr + PAR_DATA);
	inbyte(ioaddr + PAR_STATUS);
	वापस low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_reg(लघु port, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर outval;

	outb(EOC | reg, port + PAR_DATA);
	outval = WrAddr | reg;
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);	/* Double ग_लिखो क्रम PS/2. */

	outval &= 0xf0;
	outval |= value;
	outb(outval, port + PAR_DATA);
	outval &= 0x1f;
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);

	outb(EOC | outval, port + PAR_DATA);
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_reg_high(लघु port, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर outval = EOC | HNib | reg;

	outb(outval, port + PAR_DATA);
	outval &= WrAddr | HNib | 0x0f;
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);	/* Double ग_लिखो क्रम PS/2. */

	outval = WrAddr | HNib | value;
	outb(outval, port + PAR_DATA);
	outval &= HNib | 0x0f;		/* HNib | value */
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);

	outb(EOC | HNib | outval, port + PAR_DATA);
पूर्ण

/* Write a byte out using nibble mode.  The low nibble is written first. */
अटल अंतरभूत व्योम
ग_लिखो_reg_byte(लघु port, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर outval;

	outb(EOC | reg, port + PAR_DATA); /* Reset the address रेजिस्टर. */
	outval = WrAddr | reg;
	outb(outval, port + PAR_DATA);
	outb(outval, port + PAR_DATA);	/* Double ग_लिखो क्रम PS/2. */

	outb((outval & 0xf0) | (value & 0x0f), port + PAR_DATA);
	outb(value & 0x0f, port + PAR_DATA);
	value >>= 4;
	outb(value, port + PAR_DATA);
	outb(0x10 | value, port + PAR_DATA);
	outb(0x10 | value, port + PAR_DATA);

	outb(EOC  | value, port + PAR_DATA); /* Reset the address रेजिस्टर. */
पूर्ण

/* Bulk data ग_लिखोs to the packet buffer.  The पूर्णांकerrupt line reमुख्यs enabled.
 * The first, faster method uses only the dataport (data modes 0, 2 & 4).
 * The second (backup) method uses data and control regs (modes 1, 3 & 5).
 * It should only be needed when there is skew between the inभागidual data
 * lines.
 */
अटल अंतरभूत व्योम ग_लिखो_byte_mode0(लघु ioaddr, अचिन्हित अक्षर value)
अणु
	outb(value & 0x0f, ioaddr + PAR_DATA);
	outb((value>>4) | 0x10, ioaddr + PAR_DATA);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_byte_mode1(लघु ioaddr, अचिन्हित अक्षर value)
अणु
	outb(value & 0x0f, ioaddr + PAR_DATA);
	outb(Ctrl_IRQEN | Ctrl_LNibWrite, ioaddr + PAR_CONTROL);
	outb((value>>4) | 0x10, ioaddr + PAR_DATA);
	outb(Ctrl_IRQEN | Ctrl_HNibWrite, ioaddr + PAR_CONTROL);
पूर्ण

/* Write 16bit VALUE to the packet buffer: the same as above just द्विगुनd. */
अटल अंतरभूत व्योम ग_लिखो_word_mode0(लघु ioaddr, अचिन्हित लघु value)
अणु
	outb(value & 0x0f, ioaddr + PAR_DATA);
	value >>= 4;
	outb((value & 0x0f) | 0x10, ioaddr + PAR_DATA);
	value >>= 4;
	outb(value & 0x0f, ioaddr + PAR_DATA);
	value >>= 4;
	outb((value & 0x0f) | 0x10, ioaddr + PAR_DATA);
पूर्ण

/*  EEPROM_Ctrl bits. */
#घोषणा EE_SHIFT_CLK	0x04	/* EEPROM shअगरt घड़ी. */
#घोषणा EE_CS		0x02	/* EEPROM chip select. */
#घोषणा EE_CLK_HIGH	0x12
#घोषणा EE_CLK_LOW	0x16
#घोषणा EE_DATA_WRITE	0x01	/* EEPROM chip data in. */
#घोषणा EE_DATA_READ	0x08	/* EEPROM chip data out. */

/* Delay between EEPROM घड़ी transitions. */
#घोषणा eeprom_delay(ticks) \
करो अणु पूर्णांक _i = 40; जबतक (--_i > 0) अणु __SLOW_DOWN_IO; पूर्ण पूर्ण जबतक (0)

/* The EEPROM commands include the alway-set leading bit. */
#घोषणा EE_WRITE_CMD(offset)	(((5 << 6) + (offset)) << 17)
#घोषणा EE_READ(offset)		(((6 << 6) + (offset)) << 17)
#घोषणा EE_ERASE(offset)	(((7 << 6) + (offset)) << 17)
#घोषणा EE_CMD_SIZE	27	/* The command+address+data size. */
