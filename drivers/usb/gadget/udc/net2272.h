<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PLX NET2272 high/full speed USB device controller
 *
 * Copyright (C) 2005-2006 PLX Technology, Inc.
 * Copyright (C) 2006-2011 Analog Devices, Inc.
 */

#अगर_अघोषित __NET2272_H__
#घोषणा __NET2272_H__

/* Main Registers */
#घोषणा REGADDRPTR			0x00
#घोषणा REGDATA				0x01
#घोषणा IRQSTAT0			0x02
#घोषणा 	ENDPOINT_0_INTERRUPT			0
#घोषणा 	ENDPOINT_A_INTERRUPT			1
#घोषणा 	ENDPOINT_B_INTERRUPT			2
#घोषणा 	ENDPOINT_C_INTERRUPT			3
#घोषणा 	VIRTUALIZED_ENDPOINT_INTERRUPT		4
#घोषणा 	SETUP_PACKET_INTERRUPT			5
#घोषणा 	DMA_DONE_INTERRUPT			6
#घोषणा 	SOF_INTERRUPT				7
#घोषणा IRQSTAT1			0x03
#घोषणा 	CONTROL_STATUS_INTERRUPT		1
#घोषणा 	VBUS_INTERRUPT				2
#घोषणा 	SUSPEND_REQUEST_INTERRUPT		3
#घोषणा 	SUSPEND_REQUEST_CHANGE_INTERRUPT	4
#घोषणा 	RESUME_INTERRUPT			5
#घोषणा 	ROOT_PORT_RESET_INTERRUPT		6
#घोषणा 	RESET_STATUS				7
#घोषणा PAGESEL				0x04
#घोषणा DMAREQ				0x1c
#घोषणा 	DMA_ENDPOINT_SELECT			0
#घोषणा 	DREQ_POLARITY				1
#घोषणा 	DACK_POLARITY				2
#घोषणा 	EOT_POLARITY				3
#घोषणा 	DMA_CONTROL_DACK			4
#घोषणा 	DMA_REQUEST_ENABLE			5
#घोषणा 	DMA_REQUEST				6
#घोषणा 	DMA_BUFFER_VALID			7
#घोषणा SCRATCH				0x1d
#घोषणा IRQENB0				0x20
#घोषणा 	ENDPOINT_0_INTERRUPT_ENABLE		0
#घोषणा 	ENDPOINT_A_INTERRUPT_ENABLE		1
#घोषणा 	ENDPOINT_B_INTERRUPT_ENABLE		2
#घोषणा 	ENDPOINT_C_INTERRUPT_ENABLE		3
#घोषणा 	VIRTUALIZED_ENDPOINT_INTERRUPT_ENABLE	4
#घोषणा 	SETUP_PACKET_INTERRUPT_ENABLE		5
#घोषणा 	DMA_DONE_INTERRUPT_ENABLE		6
#घोषणा 	SOF_INTERRUPT_ENABLE			7
#घोषणा IRQENB1				0x21
#घोषणा 	VBUS_INTERRUPT_ENABLE			2
#घोषणा 	SUSPEND_REQUEST_INTERRUPT_ENABLE	3
#घोषणा 	SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE	4
#घोषणा 	RESUME_INTERRUPT_ENABLE			5
#घोषणा 	ROOT_PORT_RESET_INTERRUPT_ENABLE	6
#घोषणा LOCCTL				0x22
#घोषणा 	DATA_WIDTH				0
#घोषणा 	LOCAL_CLOCK_OUTPUT			1
#घोषणा 		LOCAL_CLOCK_OUTPUT_OFF			0
#घोषणा 		LOCAL_CLOCK_OUTPUT_3_75MHZ		1
#घोषणा 		LOCAL_CLOCK_OUTPUT_7_5MHZ		2
#घोषणा 		LOCAL_CLOCK_OUTPUT_15MHZ		3
#घोषणा 		LOCAL_CLOCK_OUTPUT_30MHZ		4
#घोषणा 		LOCAL_CLOCK_OUTPUT_60MHZ		5
#घोषणा 	DMA_SPLIT_BUS_MODE			4
#घोषणा 	BYTE_SWAP				5
#घोषणा 	BUFFER_CONFIGURATION			6
#घोषणा 		BUFFER_CONFIGURATION_EPA512_EPB512	0
#घोषणा 		BUFFER_CONFIGURATION_EPA1024_EPB512	1
#घोषणा 		BUFFER_CONFIGURATION_EPA1024_EPB1024	2
#घोषणा 		BUFFER_CONFIGURATION_EPA1024DB		3
#घोषणा CHIPREV_LEGACY			0x23
#घोषणा 		NET2270_LEGACY_REV			0x40
#घोषणा LOCCTL1				0x24
#घोषणा 	DMA_MODE				0
#घोषणा 		SLOW_DREQ				0
#घोषणा 		FAST_DREQ				1
#घोषणा 		BURST_MODE				2
#घोषणा 	DMA_DACK_ENABLE				2
#घोषणा CHIPREV_2272			0x25
#घोषणा 		CHIPREV_NET2272_R1			0x10
#घोषणा 		CHIPREV_NET2272_R1A			0x11
/* USB Registers */
#घोषणा USBCTL0				0x18
#घोषणा 	IO_WAKEUP_ENABLE			1
#घोषणा 	USB_DETECT_ENABLE			3
#घोषणा 	USB_ROOT_PORT_WAKEUP_ENABLE		5
#घोषणा USBCTL1				0x19
#घोषणा 	VBUS_PIN				0
#घोषणा 		USB_FULL_SPEED				1
#घोषणा 		USB_HIGH_SPEED				2
#घोषणा 	GENERATE_RESUME				3
#घोषणा 	VIRTUAL_ENDPOINT_ENABLE			4
#घोषणा FRAME0				0x1a
#घोषणा FRAME1				0x1b
#घोषणा OURADDR				0x30
#घोषणा 	FORCE_IMMEDIATE				7
#घोषणा USBDIAG				0x31
#घोषणा 	FORCE_TRANSMIT_CRC_ERROR		0
#घोषणा 	PREVENT_TRANSMIT_BIT_STUFF		1
#घोषणा 	FORCE_RECEIVE_ERROR			2
#घोषणा 	FAST_TIMES				4
#घोषणा USBTEST				0x32
#घोषणा 	TEST_MODE_SELECT			0
#घोषणा 		NORMAL_OPERATION			0
#घोषणा XCVRDIAG			0x33
#घोषणा 	FORCE_FULL_SPEED			2
#घोषणा 	FORCE_HIGH_SPEED			3
#घोषणा 	OPMODE					4
#घोषणा 		NORMAL_OPERATION			0
#घोषणा 		NON_DRIVING				1
#घोषणा 		DISABLE_BITSTUFF_AND_NRZI_ENCODE	2
#घोषणा 	LINESTATE				6
#घोषणा 		SE0_STATE				0
#घोषणा 		J_STATE					1
#घोषणा 		K_STATE					2
#घोषणा 		SE1_STATE				3
#घोषणा VIRTOUT0			0x34
#घोषणा VIRTOUT1			0x35
#घोषणा VIRTIN0				0x36
#घोषणा VIRTIN1				0x37
#घोषणा SETUP0				0x40
#घोषणा SETUP1				0x41
#घोषणा SETUP2				0x42
#घोषणा SETUP3				0x43
#घोषणा SETUP4				0x44
#घोषणा SETUP5				0x45
#घोषणा SETUP6				0x46
#घोषणा SETUP7				0x47
/* Endpoपूर्णांक Registers (Paged via PAGESEL) */
#घोषणा EP_DATA				0x05
#घोषणा EP_STAT0			0x06
#घोषणा 	DATA_IN_TOKEN_INTERRUPT			0
#घोषणा 	DATA_OUT_TOKEN_INTERRUPT		1
#घोषणा 	DATA_PACKET_TRANSMITTED_INTERRUPT	2
#घोषणा 	DATA_PACKET_RECEIVED_INTERRUPT		3
#घोषणा 	SHORT_PACKET_TRANSFERRED_INTERRUPT	4
#घोषणा 	NAK_OUT_PACKETS				5
#घोषणा 	BUFFER_EMPTY				6
#घोषणा 	BUFFER_FULL				7
#घोषणा EP_STAT1			0x07
#घोषणा 	TIMEOUT					0
#घोषणा 	USB_OUT_ACK_SENT			1
#घोषणा 	USB_OUT_NAK_SENT			2
#घोषणा 	USB_IN_ACK_RCVD				3
#घोषणा 	USB_IN_NAK_SENT				4
#घोषणा 	USB_STALL_SENT				5
#घोषणा 	LOCAL_OUT_ZLP				6
#घोषणा 	BUFFER_FLUSH				7
#घोषणा EP_TRANSFER0			0x08
#घोषणा EP_TRANSFER1			0x09
#घोषणा EP_TRANSFER2			0x0a
#घोषणा EP_IRQENB			0x0b
#घोषणा 	DATA_IN_TOKEN_INTERRUPT_ENABLE		0
#घोषणा 	DATA_OUT_TOKEN_INTERRUPT_ENABLE		1
#घोषणा 	DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE	2
#घोषणा 	DATA_PACKET_RECEIVED_INTERRUPT_ENABLE	3
#घोषणा 	SHORT_PACKET_TRANSFERRED_INTERRUPT_ENABLE	4
#घोषणा EP_AVAIL0			0x0c
#घोषणा EP_AVAIL1			0x0d
#घोषणा EP_RSPCLR			0x0e
#घोषणा EP_RSPSET			0x0f
#घोषणा 	ENDPOINT_HALT				0
#घोषणा 	ENDPOINT_TOGGLE				1
#घोषणा 	NAK_OUT_PACKETS_MODE			2
#घोषणा 	CONTROL_STATUS_PHASE_HANDSHAKE		3
#घोषणा 	INTERRUPT_MODE				4
#घोषणा 	AUTOVALIDATE				5
#घोषणा 	HIDE_STATUS_PHASE			6
#घोषणा 	ALT_NAK_OUT_PACKETS			7
#घोषणा EP_MAXPKT0			0x28
#घोषणा EP_MAXPKT1			0x29
#घोषणा 	ADDITIONAL_TRANSACTION_OPPORTUNITIES	3
#घोषणा 		NONE_ADDITIONAL_TRANSACTION		0
#घोषणा 		ONE_ADDITIONAL_TRANSACTION		1
#घोषणा 		TWO_ADDITIONAL_TRANSACTION		2
#घोषणा EP_CFG				0x2a
#घोषणा 	ENDPOINT_NUMBER				0
#घोषणा 	ENDPOINT_सूचीECTION			4
#घोषणा 	ENDPOINT_TYPE				5
#घोषणा 	ENDPOINT_ENABLE				7
#घोषणा EP_HBW				0x2b
#घोषणा 	HIGH_BANDWIDTH_OUT_TRANSACTION_PID	0
#घोषणा 		DATA0_PID				0
#घोषणा 		DATA1_PID				1
#घोषणा 		DATA2_PID				2
#घोषणा 		MDATA_PID				3
#घोषणा EP_BUFF_STATES			0x2c
#घोषणा 	BUFFER_A_STATE				0
#घोषणा 	BUFFER_B_STATE				2
#घोषणा 		BUFF_FREE				0
#घोषणा 		BUFF_VALID				1
#घोषणा 		BUFF_LCL				2
#घोषणा 		BUFF_USB				3

/*---------------------------------------------------------------------------*/

#घोषणा PCI_DEVICE_ID_RDK1	0x9054

/* PCI-RDK EPLD Registers */
#घोषणा RDK_EPLD_IO_REGISTER1		0x00000000
#घोषणा 	RDK_EPLD_USB_RESET				0
#घोषणा 	RDK_EPLD_USB_POWERDOWN				1
#घोषणा 	RDK_EPLD_USB_WAKEUP				2
#घोषणा 	RDK_EPLD_USB_EOT				3
#घोषणा 	RDK_EPLD_DPPULL					4
#घोषणा RDK_EPLD_IO_REGISTER2		0x00000004
#घोषणा 	RDK_EPLD_BUSWIDTH				0
#घोषणा 	RDK_EPLD_USER					2
#घोषणा 	RDK_EPLD_RESET_INTERRUPT_ENABLE			3
#घोषणा 	RDK_EPLD_DMA_TIMEOUT_ENABLE			4
#घोषणा RDK_EPLD_STATUS_REGISTER	0x00000008
#घोषणा 	RDK_EPLD_USB_LRESET				0
#घोषणा RDK_EPLD_REVISION_REGISTER	0x0000000c

/* PCI-RDK PLX 9054 Registers */
#घोषणा INTCSR				0x68
#घोषणा 	PCI_INTERRUPT_ENABLE				8
#घोषणा 	LOCAL_INTERRUPT_INPUT_ENABLE			11
#घोषणा 	LOCAL_INPUT_INTERRUPT_ACTIVE			15
#घोषणा 	LOCAL_DMA_CHANNEL_0_INTERRUPT_ENABLE		18
#घोषणा 	LOCAL_DMA_CHANNEL_1_INTERRUPT_ENABLE		19
#घोषणा 	DMA_CHANNEL_0_INTERRUPT_ACTIVE			21
#घोषणा 	DMA_CHANNEL_1_INTERRUPT_ACTIVE			22
#घोषणा CNTRL				0x6C
#घोषणा 	RELOAD_CONFIGURATION_REGISTERS			29
#घोषणा 	PCI_ADAPTER_SOFTWARE_RESET			30
#घोषणा DMAMODE0			0x80
#घोषणा 	LOCAL_BUS_WIDTH					0
#घोषणा 	INTERNAL_WAIT_STATES				2
#घोषणा 	TA_READY_INPUT_ENABLE				6
#घोषणा 	LOCAL_BURST_ENABLE				8
#घोषणा 	SCATTER_GATHER_MODE				9
#घोषणा 	DONE_INTERRUPT_ENABLE				10
#घोषणा 	LOCAL_ADDRESSING_MODE				11
#घोषणा 	DEMAND_MODE					12
#घोषणा 	DMA_EOT_ENABLE					14
#घोषणा 	FAST_SLOW_TERMINATE_MODE_SELECT			15
#घोषणा 	DMA_CHANNEL_INTERRUPT_SELECT			17
#घोषणा DMAPADR0			0x84
#घोषणा DMALADR0			0x88
#घोषणा DMASIZ0				0x8c
#घोषणा DMADPR0				0x90
#घोषणा 	DESCRIPTOR_LOCATION				0
#घोषणा 	END_OF_CHAIN					1
#घोषणा 	INTERRUPT_AFTER_TERMINAL_COUNT			2
#घोषणा 	सूचीECTION_OF_TRANSFER				3
#घोषणा DMACSR0				0xa8
#घोषणा 	CHANNEL_ENABLE					0
#घोषणा 	CHANNEL_START					1
#घोषणा 	CHANNEL_ABORT					2
#घोषणा 	CHANNEL_CLEAR_INTERRUPT				3
#घोषणा 	CHANNEL_DONE					4
#घोषणा DMATHR				0xb0
#घोषणा LBRD1				0xf8
#घोषणा 	MEMORY_SPACE_LOCAL_BUS_WIDTH			0
#घोषणा 	W8_BIT						0
#घोषणा 	W16_BIT						1

/* Special OR'ing of INTCSR bits */
#घोषणा LOCAL_INTERRUPT_TEST \
	((1 << LOCAL_INPUT_INTERRUPT_ACTIVE) | \
	 (1 << LOCAL_INTERRUPT_INPUT_ENABLE))

#घोषणा DMA_CHANNEL_0_TEST \
	((1 << DMA_CHANNEL_0_INTERRUPT_ACTIVE) | \
	 (1 << LOCAL_DMA_CHANNEL_0_INTERRUPT_ENABLE))

#घोषणा DMA_CHANNEL_1_TEST \
	((1 << DMA_CHANNEL_1_INTERRUPT_ACTIVE) | \
	 (1 << LOCAL_DMA_CHANNEL_1_INTERRUPT_ENABLE))

/* EPLD Registers */
#घोषणा RDK_EPLD_IO_REGISTER1			0x00000000
#घोषणा 	RDK_EPLD_USB_RESET			0
#घोषणा 	RDK_EPLD_USB_POWERDOWN			1
#घोषणा 	RDK_EPLD_USB_WAKEUP			2
#घोषणा 	RDK_EPLD_USB_EOT			3
#घोषणा 	RDK_EPLD_DPPULL				4
#घोषणा RDK_EPLD_IO_REGISTER2			0x00000004
#घोषणा 	RDK_EPLD_BUSWIDTH			0
#घोषणा 	RDK_EPLD_USER				2
#घोषणा 	RDK_EPLD_RESET_INTERRUPT_ENABLE		3
#घोषणा 	RDK_EPLD_DMA_TIMEOUT_ENABLE		4
#घोषणा RDK_EPLD_STATUS_REGISTER		0x00000008
#घोषणा RDK_EPLD_USB_LRESET				0
#घोषणा RDK_EPLD_REVISION_REGISTER		0x0000000c

#घोषणा EPLD_IO_CONTROL_REGISTER		0x400
#घोषणा 	NET2272_RESET				0
#घोषणा 	BUSWIDTH				1
#घोषणा 	MPX_MODE				3
#घोषणा 	USER					4
#घोषणा 	DMA_TIMEOUT_ENABLE			5
#घोषणा 	DMA_CTL_DACK				6
#घोषणा 	EPLD_DMA_ENABLE				7
#घोषणा EPLD_DMA_CONTROL_REGISTER		0x800
#घोषणा 	SPLIT_DMA_MODE				0
#घोषणा 	SPLIT_DMA_सूचीECTION			1
#घोषणा 	SPLIT_DMA_ENABLE			2
#घोषणा 	SPLIT_DMA_INTERRUPT_ENABLE		3
#घोषणा 	SPLIT_DMA_INTERRUPT			4
#घोषणा 	EPLD_DMA_MODE				5
#घोषणा 	EPLD_DMA_CONTROLLER_ENABLE		7
#घोषणा SPLIT_DMA_ADDRESS_LOW			0xc00
#घोषणा SPLIT_DMA_ADDRESS_HIGH			0x1000
#घोषणा SPLIT_DMA_BYTE_COUNT_LOW		0x1400
#घोषणा SPLIT_DMA_BYTE_COUNT_HIGH		0x1800
#घोषणा EPLD_REVISION_REGISTER			0x1c00
#घोषणा SPLIT_DMA_RAM				0x4000
#घोषणा DMA_RAM_SIZE				0x1000

/*---------------------------------------------------------------------------*/

#घोषणा PCI_DEVICE_ID_RDK2	0x3272

/* PCI-RDK version 2 रेजिस्टरs */

/* Main Control Registers */

#घोषणा RDK2_IRQENB			0x00
#घोषणा RDK2_IRQSTAT			0x04
#घोषणा 	PB7				23
#घोषणा 	PB6				22
#घोषणा 	PB5				21
#घोषणा 	PB4				20
#घोषणा 	PB3				19
#घोषणा 	PB2				18
#घोषणा 	PB1				17
#घोषणा 	PB0				16
#घोषणा 	GP3				23
#घोषणा 	GP2				23
#घोषणा 	GP1				23
#घोषणा 	GP0				23
#घोषणा 	DMA_RETRY_ABORT			6
#घोषणा 	DMA_PAUSE_DONE			5
#घोषणा 	DMA_ABORT_DONE			4
#घोषणा 	DMA_OUT_FIFO_TRANSFER_DONE	3
#घोषणा 	DMA_LOCAL_DONE			2
#घोषणा 	DMA_PCI_DONE			1
#घोषणा 	NET2272_PCI_IRQ			0

#घोषणा RDK2_LOCCTLRDK			0x08
#घोषणा 	CHIP_RESET			3
#घोषणा 	SPLIT_DMA			2
#घोषणा 	MULTIPLEX_MODE			1
#घोषणा 	BUS_WIDTH			0

#घोषणा RDK2_GPIOCTL			0x10
#घोषणा 	GP3_OUT_ENABLE					7
#घोषणा 	GP2_OUT_ENABLE					6
#घोषणा 	GP1_OUT_ENABLE					5
#घोषणा 	GP0_OUT_ENABLE					4
#घोषणा 	GP3_DATA					3
#घोषणा 	GP2_DATA					2
#घोषणा 	GP1_DATA					1
#घोषणा 	GP0_DATA					0

#घोषणा RDK2_LEDSW			0x14
#घोषणा 	LED3				27
#घोषणा 	LED2				26
#घोषणा 	LED1				25
#घोषणा 	LED0				24
#घोषणा 	PBUTTON				16
#घोषणा 	DIPSW				0

#घोषणा RDK2_DIAG			0x18
#घोषणा 	RDK2_FAST_TIMES				2
#घोषणा 	FORCE_PCI_SERR				1
#घोषणा 	FORCE_PCI_INT				0
#घोषणा RDK2_FPGAREV			0x1C

/* Dma Control रेजिस्टरs */
#घोषणा RDK2_DMACTL			0x80
#घोषणा 	ADDR_HOLD				24
#घोषणा 	RETRY_COUNT				16	/* 23:16 */
#घोषणा 	FIFO_THRESHOLD				11	/* 15:11 */
#घोषणा 	MEM_WRITE_INVALIDATE			10
#घोषणा 	READ_MULTIPLE				9
#घोषणा 	READ_LINE				8
#घोषणा 	RDK2_DMA_MODE				6	/* 7:6 */
#घोषणा 	CONTROL_DACK				5
#घोषणा 	EOT_ENABLE				4
#घोषणा 	EOT_POLARITY				3
#घोषणा 	DACK_POLARITY				2
#घोषणा 	DREQ_POLARITY				1
#घोषणा 	DMA_ENABLE				0

#घोषणा RDK2_DMASTAT			0x84
#घोषणा 	GATHER_COUNT				12	/* 14:12 */
#घोषणा 	FIFO_COUNT				6	/* 11:6 */
#घोषणा 	FIFO_FLUSH				5
#घोषणा 	FIFO_TRANSFER				4
#घोषणा 	PAUSE_DONE				3
#घोषणा 	ABORT_DONE				2
#घोषणा 	DMA_ABORT				1
#घोषणा 	DMA_START				0

#घोषणा RDK2_DMAPCICOUNT		0x88
#घोषणा 	DMA_सूचीECTION				31
#घोषणा 	DMA_PCI_BYTE_COUNT			0	/* 0:23 */

#घोषणा RDK2_DMALOCCOUNT		0x8C	/* 0:23 dma local byte count */

#घोषणा RDK2_DMAADDR			0x90	/* 2:31 PCI bus starting address */

/*---------------------------------------------------------------------------*/

#घोषणा REG_INDEXED_THRESHOLD	(1 << 5)

/* DRIVER DATA STRUCTURES and UTILITIES */
काष्ठा net2272_ep अणु
	काष्ठा usb_ep ep;
	काष्ठा net2272 *dev;
	अचिन्हित दीर्घ irqs;

	/* analogous to a host-side qh */
	काष्ठा list_head queue;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	अचिन्हित num:8,
	         fअगरo_size:12,
	         stopped:1,
	         wedged:1,
	         is_in:1,
	         is_iso:1,
	         dma:1,
	         not_empty:1;
पूर्ण;

काष्ठा net2272 अणु
	/* each device provides one gadget, several endpoपूर्णांकs */
	काष्ठा usb_gadget gadget;
	काष्ठा device *dev;
	अचिन्हित लघु dev_id;

	spinlock_t lock;
	काष्ठा net2272_ep ep[4];
	काष्ठा usb_gadget_driver *driver;
	अचिन्हित protocol_stall:1,
	         softconnect:1,
	         wakeup:1,
		 added:1,
	         dma_eot_polarity:1,
	         dma_dack_polarity:1,
	         dma_dreq_polarity:1,
	         dma_busy:1;
	u16 chiprev;
	u8 pagesel;

	अचिन्हित पूर्णांक irq;
	अचिन्हित लघु fअगरo_mode;

	अचिन्हित पूर्णांक base_shअगरt;
	u16 __iomem *base_addr;
	जोड़ अणु
#अगर_घोषित CONFIG_USB_PCI
		काष्ठा अणु
			व्योम __iomem *plx9054_base_addr;
			व्योम __iomem *epld_base_addr;
		पूर्ण rdk1;
		काष्ठा अणु
			/* Bar0, Bar1 is base_addr both mem-mapped */
			व्योम __iomem *fpga_base_addr;
		पूर्ण rdk2;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

अटल व्योम __iomem *
net2272_reg_addr(काष्ठा net2272 *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस dev->base_addr + (reg << dev->base_shअगरt);
पूर्ण

अटल व्योम
net2272_ग_लिखो(काष्ठा net2272 *dev, अचिन्हित पूर्णांक reg, u8 value)
अणु
	अगर (reg >= REG_INDEXED_THRESHOLD) अणु
		/*
		 * Indexed रेजिस्टर; use REGADDRPTR/REGDATA
		 *  - Save and restore REGADDRPTR. This prevents REGADDRPTR from
		 *    changes between other code sections, but it is समय consuming.
		 *  - Perक्रमmance tips: either करो not save and restore REGADDRPTR (अगर it
		 *    is safe) or करो save/restore operations only in critical sections.
		u8 पंचांगp = पढ़ोb(dev->base_addr + REGADDRPTR);
		 */
		ग_लिखोb((u8)reg, net2272_reg_addr(dev, REGADDRPTR));
		ग_लिखोb(value, net2272_reg_addr(dev, REGDATA));
		/* ग_लिखोb(पंचांगp, net2272_reg_addr(dev, REGADDRPTR)); */
	पूर्ण अन्यथा
		ग_लिखोb(value, net2272_reg_addr(dev, reg));
पूर्ण

अटल u8
net2272_पढ़ो(काष्ठा net2272 *dev, अचिन्हित पूर्णांक reg)
अणु
	u8 ret;

	अगर (reg >= REG_INDEXED_THRESHOLD) अणु
		/*
		 * Indexed रेजिस्टर; use REGADDRPTR/REGDATA
		 *  - Save and restore REGADDRPTR. This prevents REGADDRPTR from
		 *    changes between other code sections, but it is समय consuming.
		 *  - Perक्रमmance tips: either करो not save and restore REGADDRPTR (अगर it
		 *    is safe) or करो save/restore operations only in critical sections.
		u8 पंचांगp = पढ़ोb(dev->base_addr + REGADDRPTR);
		 */
		ग_लिखोb((u8)reg, net2272_reg_addr(dev, REGADDRPTR));
		ret = पढ़ोb(net2272_reg_addr(dev, REGDATA));
		/* ग_लिखोb(पंचांगp, net2272_reg_addr(dev, REGADDRPTR)); */
	पूर्ण अन्यथा
		ret = पढ़ोb(net2272_reg_addr(dev, reg));

	वापस ret;
पूर्ण

अटल व्योम
net2272_ep_ग_लिखो(काष्ठा net2272_ep *ep, अचिन्हित पूर्णांक reg, u8 value)
अणु
	काष्ठा net2272 *dev = ep->dev;

	अगर (dev->pagesel != ep->num) अणु
		net2272_ग_लिखो(dev, PAGESEL, ep->num);
		dev->pagesel = ep->num;
	पूर्ण
	net2272_ग_लिखो(dev, reg, value);
पूर्ण

अटल u8
net2272_ep_पढ़ो(काष्ठा net2272_ep *ep, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा net2272 *dev = ep->dev;

	अगर (dev->pagesel != ep->num) अणु
		net2272_ग_लिखो(dev, PAGESEL, ep->num);
		dev->pagesel = ep->num;
	पूर्ण
	वापस net2272_पढ़ो(dev, reg);
पूर्ण

अटल व्योम allow_status(काष्ठा net2272_ep *ep)
अणु
	/* ep0 only */
	net2272_ep_ग_लिखो(ep, EP_RSPCLR,
		(1 << CONTROL_STATUS_PHASE_HANDSHAKE) |
		(1 << ALT_NAK_OUT_PACKETS) |
		(1 << NAK_OUT_PACKETS_MODE));
	ep->stopped = 1;
पूर्ण

अटल व्योम set_halt(काष्ठा net2272_ep *ep)
अणु
	/* ep0 and bulk/पूर्णांकr endpoपूर्णांकs */
	net2272_ep_ग_लिखो(ep, EP_RSPCLR, 1 << CONTROL_STATUS_PHASE_HANDSHAKE);
	net2272_ep_ग_लिखो(ep, EP_RSPSET, 1 << ENDPOINT_HALT);
पूर्ण

अटल व्योम clear_halt(काष्ठा net2272_ep *ep)
अणु
	/* ep0 and bulk/पूर्णांकr endpoपूर्णांकs */
	net2272_ep_ग_लिखो(ep, EP_RSPCLR,
		(1 << ENDPOINT_HALT) | (1 << ENDPOINT_TOGGLE));
पूर्ण

/* count (<= 4) bytes in the next fअगरo ग_लिखो will be valid */
अटल व्योम set_fअगरo_bytecount(काष्ठा net2272_ep *ep, अचिन्हित count)
अणु
	/* net2272_ep_ग_लिखो will truncate to u8 क्रम us */
	net2272_ep_ग_लिखो(ep, EP_TRANSFER2, count >> 16);
	net2272_ep_ग_लिखो(ep, EP_TRANSFER1, count >> 8);
	net2272_ep_ग_लिखो(ep, EP_TRANSFER0, count);
पूर्ण

काष्ठा net2272_request अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;
	अचिन्हित mapped:1,
	         valid:1;
पूर्ण;

#पूर्ण_अगर
