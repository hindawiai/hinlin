<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mediated भव PCI serial host device driver
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 *
 * Sample driver that creates mdev device that simulates serial port over PCI
 * card.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdev.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uuid.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/file.h>
#समावेश <linux/mdev.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial.h>
#समावेश <uapi/linux/serial_reg.h>
#समावेश <linux/eventfd.h>
/*
 * #घोषणाs
 */

#घोषणा VERSION_STRING  "0.1"
#घोषणा DRIVER_AUTHOR   "NVIDIA Corporation"

#घोषणा MTTY_CLASS_NAME "mtty"

#घोषणा MTTY_NAME       "mtty"

#घोषणा MTTY_STRING_LEN		16

#घोषणा MTTY_CONFIG_SPACE_SIZE  0xff
#घोषणा MTTY_IO_BAR_SIZE        0x8
#घोषणा MTTY_MMIO_BAR_SIZE      0x100000

#घोषणा STORE_LE16(addr, val)   (*(u16 *)addr = val)
#घोषणा STORE_LE32(addr, val)   (*(u32 *)addr = val)

#घोषणा MAX_FIFO_SIZE   16

#घोषणा CIRCULAR_BUF_INC_IDX(idx)    (idx = (idx + 1) & (MAX_FIFO_SIZE - 1))

#घोषणा MTTY_VFIO_PCI_OFFSET_SHIFT   40

#घोषणा MTTY_VFIO_PCI_OFFSET_TO_INDEX(off)   (off >> MTTY_VFIO_PCI_OFFSET_SHIFT)
#घोषणा MTTY_VFIO_PCI_INDEX_TO_OFFSET(index) \
				((u64)(index) << MTTY_VFIO_PCI_OFFSET_SHIFT)
#घोषणा MTTY_VFIO_PCI_OFFSET_MASK    \
				(((u64)(1) << MTTY_VFIO_PCI_OFFSET_SHIFT) - 1)
#घोषणा MAX_MTTYS	24

/*
 * Global Structures
 */

अटल काष्ठा mtty_dev अणु
	dev_t		vd_devt;
	काष्ठा class	*vd_class;
	काष्ठा cdev	vd_cdev;
	काष्ठा idr	vd_idr;
	काष्ठा device	dev;
पूर्ण mtty_dev;

काष्ठा mdev_region_info अणु
	u64 start;
	u64 phys_start;
	u32 size;
	u64 vfio_offset;
पूर्ण;

#अगर defined(DEBUG_REGS)
अटल स्थिर अक्षर *wr_reg[] = अणु
	"TX",
	"IER",
	"FCR",
	"LCR",
	"MCR",
	"LSR",
	"MSR",
	"SCR"
पूर्ण;

अटल स्थिर अक्षर *rd_reg[] = अणु
	"RX",
	"IER",
	"IIR",
	"LCR",
	"MCR",
	"LSR",
	"MSR",
	"SCR"
पूर्ण;
#पूर्ण_अगर

/* loop back buffer */
काष्ठा rxtx अणु
	u8 fअगरo[MAX_FIFO_SIZE];
	u8 head, tail;
	u8 count;
पूर्ण;

काष्ठा serial_port अणु
	u8 uart_reg[8];         /* 8 रेजिस्टरs */
	काष्ठा rxtx rxtx;       /* loop back buffer */
	bool dlab;
	bool overrun;
	u16 भागisor;
	u8 fcr;                 /* FIFO control रेजिस्टर */
	u8 max_fअगरo_size;
	u8 पूर्णांकr_trigger_level;  /* पूर्णांकerrupt trigger level */
पूर्ण;

/* State of each mdev device */
काष्ठा mdev_state अणु
	पूर्णांक irq_fd;
	काष्ठा eventfd_ctx *पूर्णांकx_evtfd;
	काष्ठा eventfd_ctx *msi_evtfd;
	पूर्णांक irq_index;
	u8 *vconfig;
	काष्ठा mutex ops_lock;
	काष्ठा mdev_device *mdev;
	काष्ठा mdev_region_info region_info[VFIO_PCI_NUM_REGIONS];
	u32 bar_mask[VFIO_PCI_NUM_REGIONS];
	काष्ठा list_head next;
	काष्ठा serial_port s[2];
	काष्ठा mutex rxtx_lock;
	काष्ठा vfio_device_info dev_info;
	पूर्णांक nr_ports;
पूर्ण;

अटल काष्ठा mutex mdev_list_lock;
अटल काष्ठा list_head mdev_devices_list;

अटल स्थिर काष्ठा file_operations vd_fops = अणु
	.owner          = THIS_MODULE,
पूर्ण;

/* function prototypes */

अटल पूर्णांक mtty_trigger_पूर्णांकerrupt(काष्ठा mdev_state *mdev_state);

/* Helper functions */

अटल व्योम dump_buffer(u8 *buf, uपूर्णांक32_t count)
अणु
#अगर defined(DEBUG)
	पूर्णांक i;

	pr_info("Buffer:\n");
	क्रम (i = 0; i < count; i++) अणु
		pr_info("%2x ", *(buf + i));
		अगर ((i + 1) % 16 == 0)
			pr_info("\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम mtty_create_config_space(काष्ठा mdev_state *mdev_state)
अणु
	/* PCI dev ID */
	STORE_LE32((u32 *) &mdev_state->vconfig[0x0], 0x32534348);

	/* Control: I/O+, Mem-, BusMaster- */
	STORE_LE16((u16 *) &mdev_state->vconfig[0x4], 0x0001);

	/* Status: capabilities list असलent */
	STORE_LE16((u16 *) &mdev_state->vconfig[0x6], 0x0200);

	/* Rev ID */
	mdev_state->vconfig[0x8] =  0x10;

	/* programming पूर्णांकerface class : 16550-compatible serial controller */
	mdev_state->vconfig[0x9] =  0x02;

	/* Sub class : 00 */
	mdev_state->vconfig[0xa] =  0x00;

	/* Base class : Simple Communication controllers */
	mdev_state->vconfig[0xb] =  0x07;

	/* base address रेजिस्टरs */
	/* BAR0: IO space */
	STORE_LE32((u32 *) &mdev_state->vconfig[0x10], 0x000001);
	mdev_state->bar_mask[0] = ~(MTTY_IO_BAR_SIZE) + 1;

	अगर (mdev_state->nr_ports == 2) अणु
		/* BAR1: IO space */
		STORE_LE32((u32 *) &mdev_state->vconfig[0x14], 0x000001);
		mdev_state->bar_mask[1] = ~(MTTY_IO_BAR_SIZE) + 1;
	पूर्ण

	/* Subप्रणाली ID */
	STORE_LE32((u32 *) &mdev_state->vconfig[0x2c], 0x32534348);

	mdev_state->vconfig[0x34] =  0x00;   /* Cap Ptr */
	mdev_state->vconfig[0x3d] =  0x01;   /* पूर्णांकerrupt pin (INTA#) */

	/* Venकरोr specअगरic data */
	mdev_state->vconfig[0x40] =  0x23;
	mdev_state->vconfig[0x43] =  0x80;
	mdev_state->vconfig[0x44] =  0x23;
	mdev_state->vconfig[0x48] =  0x23;
	mdev_state->vconfig[0x4c] =  0x23;

	mdev_state->vconfig[0x60] =  0x50;
	mdev_state->vconfig[0x61] =  0x43;
	mdev_state->vconfig[0x62] =  0x49;
	mdev_state->vconfig[0x63] =  0x20;
	mdev_state->vconfig[0x64] =  0x53;
	mdev_state->vconfig[0x65] =  0x65;
	mdev_state->vconfig[0x66] =  0x72;
	mdev_state->vconfig[0x67] =  0x69;
	mdev_state->vconfig[0x68] =  0x61;
	mdev_state->vconfig[0x69] =  0x6c;
	mdev_state->vconfig[0x6a] =  0x2f;
	mdev_state->vconfig[0x6b] =  0x55;
	mdev_state->vconfig[0x6c] =  0x41;
	mdev_state->vconfig[0x6d] =  0x52;
	mdev_state->vconfig[0x6e] =  0x54;
पूर्ण

अटल व्योम handle_pci_cfg_ग_लिखो(काष्ठा mdev_state *mdev_state, u16 offset,
				 u8 *buf, u32 count)
अणु
	u32 cfg_addr, bar_mask, bar_index = 0;

	चयन (offset) अणु
	हाल 0x04: /* device control */
	हाल 0x06: /* device status */
		/* करो nothing */
		अवरोध;
	हाल 0x3c:  /* पूर्णांकerrupt line */
		mdev_state->vconfig[0x3c] = buf[0];
		अवरोध;
	हाल 0x3d:
		/*
		 * Interrupt Pin is hardwired to INTA.
		 * This field is ग_लिखो रक्षित by hardware
		 */
		अवरोध;
	हाल 0x10:  /* BAR0 */
	हाल 0x14:  /* BAR1 */
		अगर (offset == 0x10)
			bar_index = 0;
		अन्यथा अगर (offset == 0x14)
			bar_index = 1;

		अगर ((mdev_state->nr_ports == 1) && (bar_index == 1)) अणु
			STORE_LE32(&mdev_state->vconfig[offset], 0);
			अवरोध;
		पूर्ण

		cfg_addr = *(u32 *)buf;
		pr_info("BAR%d addr 0x%x\n", bar_index, cfg_addr);

		अगर (cfg_addr == 0xffffffff) अणु
			bar_mask = mdev_state->bar_mask[bar_index];
			cfg_addr = (cfg_addr & bar_mask);
		पूर्ण

		cfg_addr |= (mdev_state->vconfig[offset] & 0x3ul);
		STORE_LE32(&mdev_state->vconfig[offset], cfg_addr);
		अवरोध;
	हाल 0x18:  /* BAR2 */
	हाल 0x1c:  /* BAR3 */
	हाल 0x20:  /* BAR4 */
		STORE_LE32(&mdev_state->vconfig[offset], 0);
		अवरोध;
	शेष:
		pr_info("PCI config write @0x%x of %d bytes not handled\n",
			offset, count);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_bar_ग_लिखो(अचिन्हित पूर्णांक index, काष्ठा mdev_state *mdev_state,
				u16 offset, u8 *buf, u32 count)
अणु
	u8 data = *buf;

	/* Handle data written by guest */
	चयन (offset) अणु
	हाल UART_TX:
		/* अगर DLAB set, data is LSB of भागisor */
		अगर (mdev_state->s[index].dlab) अणु
			mdev_state->s[index].भागisor |= data;
			अवरोध;
		पूर्ण

		mutex_lock(&mdev_state->rxtx_lock);

		/* save in TX buffer */
		अगर (mdev_state->s[index].rxtx.count <
				mdev_state->s[index].max_fअगरo_size) अणु
			mdev_state->s[index].rxtx.fअगरo[
					mdev_state->s[index].rxtx.head] = data;
			mdev_state->s[index].rxtx.count++;
			CIRCULAR_BUF_INC_IDX(mdev_state->s[index].rxtx.head);
			mdev_state->s[index].overrun = false;

			/*
			 * Trigger पूर्णांकerrupt अगर receive data पूर्णांकerrupt is
			 * enabled and fअगरo reached trigger level
			 */
			अगर ((mdev_state->s[index].uart_reg[UART_IER] &
						UART_IER_RDI) &&
			   (mdev_state->s[index].rxtx.count ==
				    mdev_state->s[index].पूर्णांकr_trigger_level)) अणु
				/* trigger पूर्णांकerrupt */
#अगर defined(DEBUG_INTR)
				pr_err("Serial port %d: Fifo level trigger\n",
					index);
#पूर्ण_अगर
				mtty_trigger_पूर्णांकerrupt(mdev_state);
			पूर्ण
		पूर्ण अन्यथा अणु
#अगर defined(DEBUG_INTR)
			pr_err("Serial port %d: Buffer Overflow\n", index);
#पूर्ण_अगर
			mdev_state->s[index].overrun = true;

			/*
			 * Trigger पूर्णांकerrupt अगर receiver line status पूर्णांकerrupt
			 * is enabled
			 */
			अगर (mdev_state->s[index].uart_reg[UART_IER] &
								UART_IER_RLSI)
				mtty_trigger_पूर्णांकerrupt(mdev_state);
		पूर्ण
		mutex_unlock(&mdev_state->rxtx_lock);
		अवरोध;

	हाल UART_IER:
		/* अगर DLAB set, data is MSB of भागisor */
		अगर (mdev_state->s[index].dlab)
			mdev_state->s[index].भागisor |= (u16)data << 8;
		अन्यथा अणु
			mdev_state->s[index].uart_reg[offset] = data;
			mutex_lock(&mdev_state->rxtx_lock);
			अगर ((data & UART_IER_THRI) &&
			    (mdev_state->s[index].rxtx.head ==
					mdev_state->s[index].rxtx.tail)) अणु
#अगर defined(DEBUG_INTR)
				pr_err("Serial port %d: IER_THRI write\n",
					index);
#पूर्ण_अगर
				mtty_trigger_पूर्णांकerrupt(mdev_state);
			पूर्ण

			mutex_unlock(&mdev_state->rxtx_lock);
		पूर्ण

		अवरोध;

	हाल UART_FCR:
		mdev_state->s[index].fcr = data;

		mutex_lock(&mdev_state->rxtx_lock);
		अगर (data & (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT)) अणु
			/* clear loop back FIFO */
			mdev_state->s[index].rxtx.count = 0;
			mdev_state->s[index].rxtx.head = 0;
			mdev_state->s[index].rxtx.tail = 0;
		पूर्ण
		mutex_unlock(&mdev_state->rxtx_lock);

		चयन (data & UART_FCR_TRIGGER_MASK) अणु
		हाल UART_FCR_TRIGGER_1:
			mdev_state->s[index].पूर्णांकr_trigger_level = 1;
			अवरोध;

		हाल UART_FCR_TRIGGER_4:
			mdev_state->s[index].पूर्णांकr_trigger_level = 4;
			अवरोध;

		हाल UART_FCR_TRIGGER_8:
			mdev_state->s[index].पूर्णांकr_trigger_level = 8;
			अवरोध;

		हाल UART_FCR_TRIGGER_14:
			mdev_state->s[index].पूर्णांकr_trigger_level = 14;
			अवरोध;
		पूर्ण

		/*
		 * Set trigger level to 1 otherwise or  implement समयr with
		 * समयout of 4 अक्षरacters and on expiring that समयr set
		 * Recevice data समयout in IIR रेजिस्टर
		 */
		mdev_state->s[index].पूर्णांकr_trigger_level = 1;
		अगर (data & UART_FCR_ENABLE_FIFO)
			mdev_state->s[index].max_fअगरo_size = MAX_FIFO_SIZE;
		अन्यथा अणु
			mdev_state->s[index].max_fअगरo_size = 1;
			mdev_state->s[index].पूर्णांकr_trigger_level = 1;
		पूर्ण

		अवरोध;

	हाल UART_LCR:
		अगर (data & UART_LCR_DLAB) अणु
			mdev_state->s[index].dlab = true;
			mdev_state->s[index].भागisor = 0;
		पूर्ण अन्यथा
			mdev_state->s[index].dlab = false;

		mdev_state->s[index].uart_reg[offset] = data;
		अवरोध;

	हाल UART_MCR:
		mdev_state->s[index].uart_reg[offset] = data;

		अगर ((mdev_state->s[index].uart_reg[UART_IER] & UART_IER_MSI) &&
				(data & UART_MCR_OUT2)) अणु
#अगर defined(DEBUG_INTR)
			pr_err("Serial port %d: MCR_OUT2 write\n", index);
#पूर्ण_अगर
			mtty_trigger_पूर्णांकerrupt(mdev_state);
		पूर्ण

		अगर ((mdev_state->s[index].uart_reg[UART_IER] & UART_IER_MSI) &&
				(data & (UART_MCR_RTS | UART_MCR_DTR))) अणु
#अगर defined(DEBUG_INTR)
			pr_err("Serial port %d: MCR RTS/DTR write\n", index);
#पूर्ण_अगर
			mtty_trigger_पूर्णांकerrupt(mdev_state);
		पूर्ण
		अवरोध;

	हाल UART_LSR:
	हाल UART_MSR:
		/* करो nothing */
		अवरोध;

	हाल UART_SCR:
		mdev_state->s[index].uart_reg[offset] = data;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_bar_पढ़ो(अचिन्हित पूर्णांक index, काष्ठा mdev_state *mdev_state,
			    u16 offset, u8 *buf, u32 count)
अणु
	/* Handle पढ़ो requests by guest */
	चयन (offset) अणु
	हाल UART_RX:
		/* अगर DLAB set, data is LSB of भागisor */
		अगर (mdev_state->s[index].dlab) अणु
			*buf  = (u8)mdev_state->s[index].भागisor;
			अवरोध;
		पूर्ण

		mutex_lock(&mdev_state->rxtx_lock);
		/* वापस data in tx buffer */
		अगर (mdev_state->s[index].rxtx.head !=
				 mdev_state->s[index].rxtx.tail) अणु
			*buf = mdev_state->s[index].rxtx.fअगरo[
						mdev_state->s[index].rxtx.tail];
			mdev_state->s[index].rxtx.count--;
			CIRCULAR_BUF_INC_IDX(mdev_state->s[index].rxtx.tail);
		पूर्ण

		अगर (mdev_state->s[index].rxtx.head ==
				mdev_state->s[index].rxtx.tail) अणु
		/*
		 *  Trigger पूर्णांकerrupt अगर tx buffer empty पूर्णांकerrupt is
		 *  enabled and fअगरo is empty
		 */
#अगर defined(DEBUG_INTR)
			pr_err("Serial port %d: Buffer Empty\n", index);
#पूर्ण_अगर
			अगर (mdev_state->s[index].uart_reg[UART_IER] &
							 UART_IER_THRI)
				mtty_trigger_पूर्णांकerrupt(mdev_state);
		पूर्ण
		mutex_unlock(&mdev_state->rxtx_lock);

		अवरोध;

	हाल UART_IER:
		अगर (mdev_state->s[index].dlab) अणु
			*buf = (u8)(mdev_state->s[index].भागisor >> 8);
			अवरोध;
		पूर्ण
		*buf = mdev_state->s[index].uart_reg[offset] & 0x0f;
		अवरोध;

	हाल UART_IIR:
	अणु
		u8 ier = mdev_state->s[index].uart_reg[UART_IER];
		*buf = 0;

		mutex_lock(&mdev_state->rxtx_lock);
		/* Interrupt priority 1: Parity, overrun, framing or अवरोध */
		अगर ((ier & UART_IER_RLSI) && mdev_state->s[index].overrun)
			*buf |= UART_IIR_RLSI;

		/* Interrupt priority 2: Fअगरo trigger level reached */
		अगर ((ier & UART_IER_RDI) &&
		    (mdev_state->s[index].rxtx.count >=
		      mdev_state->s[index].पूर्णांकr_trigger_level))
			*buf |= UART_IIR_RDI;

		/* Interrupt priotiry 3: transmitter holding रेजिस्टर empty */
		अगर ((ier & UART_IER_THRI) &&
		    (mdev_state->s[index].rxtx.head ==
				mdev_state->s[index].rxtx.tail))
			*buf |= UART_IIR_THRI;

		/* Interrupt priotiry 4: Modem status: CTS, DSR, RI or DCD  */
		अगर ((ier & UART_IER_MSI) &&
		    (mdev_state->s[index].uart_reg[UART_MCR] &
				 (UART_MCR_RTS | UART_MCR_DTR)))
			*buf |= UART_IIR_MSI;

		/* bit0: 0=> पूर्णांकerrupt pending, 1=> no पूर्णांकerrupt is pending */
		अगर (*buf == 0)
			*buf = UART_IIR_NO_INT;

		/* set bit 6 & 7 to be 16550 compatible */
		*buf |= 0xC0;
		mutex_unlock(&mdev_state->rxtx_lock);
	पूर्ण
	अवरोध;

	हाल UART_LCR:
	हाल UART_MCR:
		*buf = mdev_state->s[index].uart_reg[offset];
		अवरोध;

	हाल UART_LSR:
	अणु
		u8 lsr = 0;

		mutex_lock(&mdev_state->rxtx_lock);
		/* atleast one अक्षर in FIFO */
		अगर (mdev_state->s[index].rxtx.head !=
				 mdev_state->s[index].rxtx.tail)
			lsr |= UART_LSR_DR;

		/* अगर FIFO overrun */
		अगर (mdev_state->s[index].overrun)
			lsr |= UART_LSR_OE;

		/* transmit FIFO empty and tramsitter empty */
		अगर (mdev_state->s[index].rxtx.head ==
				 mdev_state->s[index].rxtx.tail)
			lsr |= UART_LSR_TEMT | UART_LSR_THRE;

		mutex_unlock(&mdev_state->rxtx_lock);
		*buf = lsr;
		अवरोध;
	पूर्ण
	हाल UART_MSR:
		*buf = UART_MSR_DSR | UART_MSR_DDSR | UART_MSR_DCD;

		mutex_lock(&mdev_state->rxtx_lock);
		/* अगर AFE is 1 and FIFO have space, set CTS bit */
		अगर (mdev_state->s[index].uart_reg[UART_MCR] &
						 UART_MCR_AFE) अणु
			अगर (mdev_state->s[index].rxtx.count <
					mdev_state->s[index].max_fअगरo_size)
				*buf |= UART_MSR_CTS | UART_MSR_DCTS;
		पूर्ण अन्यथा
			*buf |= UART_MSR_CTS | UART_MSR_DCTS;
		mutex_unlock(&mdev_state->rxtx_lock);

		अवरोध;

	हाल UART_SCR:
		*buf = mdev_state->s[index].uart_reg[offset];
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mdev_पढ़ो_base(काष्ठा mdev_state *mdev_state)
अणु
	पूर्णांक index, pos;
	u32 start_lo, start_hi;
	u32 mem_type;

	pos = PCI_BASE_ADDRESS_0;

	क्रम (index = 0; index <= VFIO_PCI_BAR5_REGION_INDEX; index++) अणु

		अगर (!mdev_state->region_info[index].size)
			जारी;

		start_lo = (*(u32 *)(mdev_state->vconfig + pos)) &
			PCI_BASE_ADDRESS_MEM_MASK;
		mem_type = (*(u32 *)(mdev_state->vconfig + pos)) &
			PCI_BASE_ADDRESS_MEM_TYPE_MASK;

		चयन (mem_type) अणु
		हाल PCI_BASE_ADDRESS_MEM_TYPE_64:
			start_hi = (*(u32 *)(mdev_state->vconfig + pos + 4));
			pos += 4;
			अवरोध;
		हाल PCI_BASE_ADDRESS_MEM_TYPE_32:
		हाल PCI_BASE_ADDRESS_MEM_TYPE_1M:
			/* 1M mem BAR treated as 32-bit BAR */
		शेष:
			/* mem unknown type treated as 32-bit BAR */
			start_hi = 0;
			अवरोध;
		पूर्ण
		pos += 4;
		mdev_state->region_info[index].start = ((u64)start_hi << 32) |
							start_lo;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mdev_access(काष्ठा mdev_device *mdev, u8 *buf, माप_प्रकार count,
			   loff_t pos, bool is_ग_लिखो)
अणु
	काष्ठा mdev_state *mdev_state;
	अचिन्हित पूर्णांक index;
	loff_t offset;
	पूर्णांक ret = 0;

	अगर (!mdev || !buf)
		वापस -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state) अणु
		pr_err("%s mdev_state not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mdev_state->ops_lock);

	index = MTTY_VFIO_PCI_OFFSET_TO_INDEX(pos);
	offset = pos & MTTY_VFIO_PCI_OFFSET_MASK;
	चयन (index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:

#अगर defined(DEBUG)
		pr_info("%s: PCI config space %s at offset 0x%llx\n",
			 __func__, is_ग_लिखो ? "write" : "read", offset);
#पूर्ण_अगर
		अगर (is_ग_लिखो) अणु
			dump_buffer(buf, count);
			handle_pci_cfg_ग_लिखो(mdev_state, offset, buf, count);
		पूर्ण अन्यथा अणु
			स_नकल(buf, (mdev_state->vconfig + offset), count);
			dump_buffer(buf, count);
		पूर्ण

		अवरोध;

	हाल VFIO_PCI_BAR0_REGION_INDEX ... VFIO_PCI_BAR5_REGION_INDEX:
		अगर (!mdev_state->region_info[index].start)
			mdev_पढ़ो_base(mdev_state);

		अगर (is_ग_लिखो) अणु
			dump_buffer(buf, count);

#अगर defined(DEBUG_REGS)
			pr_info("%s: BAR%d  WR @0x%llx %s val:0x%02x dlab:%d\n",
				__func__, index, offset, wr_reg[offset],
				*buf, mdev_state->s[index].dlab);
#पूर्ण_अगर
			handle_bar_ग_लिखो(index, mdev_state, offset, buf, count);
		पूर्ण अन्यथा अणु
			handle_bar_पढ़ो(index, mdev_state, offset, buf, count);
			dump_buffer(buf, count);

#अगर defined(DEBUG_REGS)
			pr_info("%s: BAR%d  RD @0x%llx %s val:0x%02x dlab:%d\n",
				__func__, index, offset, rd_reg[offset],
				*buf, mdev_state->s[index].dlab);
#पूर्ण_अगर
		पूर्ण
		अवरोध;

	शेष:
		ret = -1;
		जाओ accessfailed;
	पूर्ण

	ret = count;


accessfailed:
	mutex_unlock(&mdev_state->ops_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mtty_create(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state;
	पूर्णांक nr_ports = mdev_get_type_group_id(mdev) + 1;

	mdev_state = kzalloc(माप(काष्ठा mdev_state), GFP_KERNEL);
	अगर (mdev_state == शून्य)
		वापस -ENOMEM;

	mdev_state->nr_ports = nr_ports;
	mdev_state->irq_index = -1;
	mdev_state->s[0].max_fअगरo_size = MAX_FIFO_SIZE;
	mdev_state->s[1].max_fअगरo_size = MAX_FIFO_SIZE;
	mutex_init(&mdev_state->rxtx_lock);
	mdev_state->vconfig = kzalloc(MTTY_CONFIG_SPACE_SIZE, GFP_KERNEL);

	अगर (mdev_state->vconfig == शून्य) अणु
		kमुक्त(mdev_state);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&mdev_state->ops_lock);
	mdev_state->mdev = mdev;
	mdev_set_drvdata(mdev, mdev_state);

	mtty_create_config_space(mdev_state);

	mutex_lock(&mdev_list_lock);
	list_add(&mdev_state->next, &mdev_devices_list);
	mutex_unlock(&mdev_list_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mtty_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mds, *पंचांगp_mds;
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&mdev_list_lock);
	list_क्रम_each_entry_safe(mds, पंचांगp_mds, &mdev_devices_list, next) अणु
		अगर (mdev_state == mds) अणु
			list_del(&mdev_state->next);
			mdev_set_drvdata(mdev, शून्य);
			kमुक्त(mdev_state->vconfig);
			kमुक्त(mdev_state);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mdev_list_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mtty_reset(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state;

	अगर (!mdev)
		वापस -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -EINVAL;

	pr_info("%s: called\n", __func__);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mtty_पढ़ो(काष्ठा mdev_device *mdev, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			ret =  mdev_access(mdev, (u8 *)&val, माप(val),
					   *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			ret = mdev_access(mdev, (u8 *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			ret = mdev_access(mdev, (u8 *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;

पढ़ो_err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार mtty_ग_लिखो(काष्ठा mdev_device *mdev, स्थिर अक्षर __user *buf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (u8 *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (u8 *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (u8 *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 1;
		पूर्ण
		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
ग_लिखो_err:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक mtty_set_irqs(काष्ठा mdev_device *mdev, uपूर्णांक32_t flags,
			 अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start,
			 अचिन्हित पूर्णांक count, व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा mdev_state *mdev_state;

	अगर (!mdev)
		वापस -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -EINVAL;

	mutex_lock(&mdev_state->ops_lock);
	चयन (index) अणु
	हाल VFIO_PCI_INTX_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
		अणु
			अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
				pr_info("%s: disable INTx\n", __func__);
				अगर (mdev_state->पूर्णांकx_evtfd)
					eventfd_ctx_put(mdev_state->पूर्णांकx_evtfd);
				अवरोध;
			पूर्ण

			अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
				पूर्णांक fd = *(पूर्णांक *)data;

				अगर (fd > 0) अणु
					काष्ठा eventfd_ctx *evt;

					evt = eventfd_ctx_fdget(fd);
					अगर (IS_ERR(evt)) अणु
						ret = PTR_ERR(evt);
						अवरोध;
					पूर्ण
					mdev_state->पूर्णांकx_evtfd = evt;
					mdev_state->irq_fd = fd;
					mdev_state->irq_index = index;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल VFIO_PCI_MSI_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			अगर (flags & VFIO_IRQ_SET_DATA_NONE) अणु
				अगर (mdev_state->msi_evtfd)
					eventfd_ctx_put(mdev_state->msi_evtfd);
				pr_info("%s: disable MSI\n", __func__);
				mdev_state->irq_index = VFIO_PCI_INTX_IRQ_INDEX;
				अवरोध;
			पूर्ण
			अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
				पूर्णांक fd = *(पूर्णांक *)data;
				काष्ठा eventfd_ctx *evt;

				अगर (fd <= 0)
					अवरोध;

				अगर (mdev_state->msi_evtfd)
					अवरोध;

				evt = eventfd_ctx_fdget(fd);
				अगर (IS_ERR(evt)) अणु
					ret = PTR_ERR(evt);
					अवरोध;
				पूर्ण
				mdev_state->msi_evtfd = evt;
				mdev_state->irq_fd = fd;
				mdev_state->irq_index = index;
			पूर्ण
			अवरोध;
	पूर्ण
	अवरोध;
	हाल VFIO_PCI_MSIX_IRQ_INDEX:
		pr_info("%s: MSIX_IRQ\n", __func__);
		अवरोध;
	हाल VFIO_PCI_ERR_IRQ_INDEX:
		pr_info("%s: ERR_IRQ\n", __func__);
		अवरोध;
	हाल VFIO_PCI_REQ_IRQ_INDEX:
		pr_info("%s: REQ_IRQ\n", __func__);
		अवरोध;
	पूर्ण

	mutex_unlock(&mdev_state->ops_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mtty_trigger_पूर्णांकerrupt(काष्ठा mdev_state *mdev_state)
अणु
	पूर्णांक ret = -1;

	अगर ((mdev_state->irq_index == VFIO_PCI_MSI_IRQ_INDEX) &&
	    (!mdev_state->msi_evtfd))
		वापस -EINVAL;
	अन्यथा अगर ((mdev_state->irq_index == VFIO_PCI_INTX_IRQ_INDEX) &&
		 (!mdev_state->पूर्णांकx_evtfd)) अणु
		pr_info("%s: Intr eventfd not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (mdev_state->irq_index == VFIO_PCI_MSI_IRQ_INDEX)
		ret = eventfd_संकेत(mdev_state->msi_evtfd, 1);
	अन्यथा
		ret = eventfd_संकेत(mdev_state->पूर्णांकx_evtfd, 1);

#अगर defined(DEBUG_INTR)
	pr_info("Intx triggered\n");
#पूर्ण_अगर
	अगर (ret != 1)
		pr_err("%s: eventfd signal failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mtty_get_region_info(काष्ठा mdev_device *mdev,
			 काष्ठा vfio_region_info *region_info,
			 u16 *cap_type_id, व्योम **cap_type)
अणु
	अचिन्हित पूर्णांक size = 0;
	काष्ठा mdev_state *mdev_state;
	u32 bar_index;

	अगर (!mdev)
		वापस -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -EINVAL;

	bar_index = region_info->index;
	अगर (bar_index >= VFIO_PCI_NUM_REGIONS)
		वापस -EINVAL;

	mutex_lock(&mdev_state->ops_lock);

	चयन (bar_index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:
		size = MTTY_CONFIG_SPACE_SIZE;
		अवरोध;
	हाल VFIO_PCI_BAR0_REGION_INDEX:
		size = MTTY_IO_BAR_SIZE;
		अवरोध;
	हाल VFIO_PCI_BAR1_REGION_INDEX:
		अगर (mdev_state->nr_ports == 2)
			size = MTTY_IO_BAR_SIZE;
		अवरोध;
	शेष:
		size = 0;
		अवरोध;
	पूर्ण

	mdev_state->region_info[bar_index].size = size;
	mdev_state->region_info[bar_index].vfio_offset =
		MTTY_VFIO_PCI_INDEX_TO_OFFSET(bar_index);

	region_info->size = size;
	region_info->offset = MTTY_VFIO_PCI_INDEX_TO_OFFSET(bar_index);
	region_info->flags = VFIO_REGION_INFO_FLAG_READ |
		VFIO_REGION_INFO_FLAG_WRITE;
	mutex_unlock(&mdev_state->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mtty_get_irq_info(काष्ठा mdev_device *mdev,
			     काष्ठा vfio_irq_info *irq_info)
अणु
	चयन (irq_info->index) अणु
	हाल VFIO_PCI_INTX_IRQ_INDEX:
	हाल VFIO_PCI_MSI_IRQ_INDEX:
	हाल VFIO_PCI_REQ_IRQ_INDEX:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_info->flags = VFIO_IRQ_INFO_EVENTFD;
	irq_info->count = 1;

	अगर (irq_info->index == VFIO_PCI_INTX_IRQ_INDEX)
		irq_info->flags |= (VFIO_IRQ_INFO_MASKABLE |
				VFIO_IRQ_INFO_AUTOMASKED);
	अन्यथा
		irq_info->flags |= VFIO_IRQ_INFO_NORESIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक mtty_get_device_info(काष्ठा mdev_device *mdev,
			 काष्ठा vfio_device_info *dev_info)
अणु
	dev_info->flags = VFIO_DEVICE_FLAGS_PCI;
	dev_info->num_regions = VFIO_PCI_NUM_REGIONS;
	dev_info->num_irqs = VFIO_PCI_NUM_IRQS;

	वापस 0;
पूर्ण

अटल दीर्घ mtty_ioctl(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ minsz;
	काष्ठा mdev_state *mdev_state;

	अगर (!mdev)
		वापस -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
	अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = mtty_get_device_info(mdev, &info);
		अगर (ret)
			वापस ret;

		स_नकल(&mdev_state->dev_info, &info, माप(info));

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_REGION_INFO:
	अणु
		काष्ठा vfio_region_info info;
		u16 cap_type_id = 0;
		व्योम *cap_type = शून्य;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = mtty_get_region_info(mdev, &info, &cap_type_id,
					   &cap_type);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_GET_IRQ_INFO:
	अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर ((info.argsz < minsz) ||
		    (info.index >= mdev_state->dev_info.num_irqs))
			वापस -EINVAL;

		ret = mtty_get_irq_info(mdev, &info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_SET_IRQS:
	अणु
		काष्ठा vfio_irq_set hdr;
		u8 *data = शून्य, *ptr = शून्य;
		माप_प्रकार data_size = 0;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		ret = vfio_set_irqs_validate_and_prepare(&hdr,
						mdev_state->dev_info.num_irqs,
						VFIO_PCI_NUM_IRQS,
						&data_size);
		अगर (ret)
			वापस ret;

		अगर (data_size) अणु
			ptr = data = memdup_user((व्योम __user *)(arg + minsz),
						 data_size);
			अगर (IS_ERR(data))
				वापस PTR_ERR(data);
		पूर्ण

		ret = mtty_set_irqs(mdev, hdr.flags, hdr.index, hdr.start,
				    hdr.count, data);

		kमुक्त(ptr);
		वापस ret;
	पूर्ण
	हाल VFIO_DEVICE_RESET:
		वापस mtty_reset(mdev);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक mtty_खोलो(काष्ठा mdev_device *mdev)
अणु
	pr_info("%s\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम mtty_बंद(काष्ठा mdev_device *mdev)
अणु
	pr_info("%s\n", __func__);
पूर्ण

अटल sमाप_प्रकार
sample_mtty_dev_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "This is phy device\n");
पूर्ण

अटल DEVICE_ATTR_RO(sample_mtty_dev);

अटल काष्ठा attribute *mtty_dev_attrs[] = अणु
	&dev_attr_sample_mtty_dev.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mtty_dev_group = अणु
	.name  = "mtty_dev",
	.attrs = mtty_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mtty_dev_groups[] = अणु
	&mtty_dev_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार
sample_mdev_dev_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	अगर (mdev_from_dev(dev))
		वापस प्र_लिखो(buf, "This is MDEV %s\n", dev_name(dev));

	वापस प्र_लिखो(buf, "\n");
पूर्ण

अटल DEVICE_ATTR_RO(sample_mdev_dev);

अटल काष्ठा attribute *mdev_dev_attrs[] = अणु
	&dev_attr_sample_mdev_dev.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mdev_dev_group = अणु
	.name  = "vendor",
	.attrs = mdev_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mdev_dev_groups[] = अणु
	&mdev_dev_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	अटल स्थिर अक्षर *name_str[2] = अणु "Single port serial",
					   "Dual port serial" पूर्ण;

	वापस sysfs_emit(buf, "%s\n",
			  name_str[mtype_get_type_group_id(mtype)]);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(name);

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा mdev_state *mds;
	अचिन्हित पूर्णांक ports = mtype_get_type_group_id(mtype) + 1;
	पूर्णांक used = 0;

	list_क्रम_each_entry(mds, &mdev_devices_list, next)
		used += mds->nr_ports;

	वापस प्र_लिखो(buf, "%d\n", (MAX_MTTYS - used)/ports);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(available_instances);

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_PCI_STRING);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(device_api);

अटल काष्ठा attribute *mdev_types_attrs[] = अणु
	&mdev_type_attr_name.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_available_instances.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group1 = अणु
	.name  = "1",
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group2 = अणु
	.name  = "2",
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group *mdev_type_groups[] = अणु
	&mdev_type_group1,
	&mdev_type_group2,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा mdev_parent_ops mdev_fops = अणु
	.owner                  = THIS_MODULE,
	.dev_attr_groups        = mtty_dev_groups,
	.mdev_attr_groups       = mdev_dev_groups,
	.supported_type_groups  = mdev_type_groups,
	.create                 = mtty_create,
	.हटाओ			= mtty_हटाओ,
	.खोलो                   = mtty_खोलो,
	.release                = mtty_बंद,
	.पढ़ो                   = mtty_पढ़ो,
	.ग_लिखो                  = mtty_ग_लिखो,
	.ioctl		        = mtty_ioctl,
पूर्ण;

अटल व्योम mtty_device_release(काष्ठा device *dev)
अणु
	dev_dbg(dev, "mtty: released\n");
पूर्ण

अटल पूर्णांक __init mtty_dev_init(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("mtty_dev: %s\n", __func__);

	स_रखो(&mtty_dev, 0, माप(mtty_dev));

	idr_init(&mtty_dev.vd_idr);

	ret = alloc_chrdev_region(&mtty_dev.vd_devt, 0, MINORMASK + 1,
				  MTTY_NAME);

	अगर (ret < 0) अणु
		pr_err("Error: failed to register mtty_dev, err:%d\n", ret);
		वापस ret;
	पूर्ण

	cdev_init(&mtty_dev.vd_cdev, &vd_fops);
	cdev_add(&mtty_dev.vd_cdev, mtty_dev.vd_devt, MINORMASK + 1);

	pr_info("major_number:%d\n", MAJOR(mtty_dev.vd_devt));

	mtty_dev.vd_class = class_create(THIS_MODULE, MTTY_CLASS_NAME);

	अगर (IS_ERR(mtty_dev.vd_class)) अणु
		pr_err("Error: failed to register mtty_dev class\n");
		ret = PTR_ERR(mtty_dev.vd_class);
		जाओ failed1;
	पूर्ण

	mtty_dev.dev.class = mtty_dev.vd_class;
	mtty_dev.dev.release = mtty_device_release;
	dev_set_name(&mtty_dev.dev, "%s", MTTY_NAME);

	ret = device_रेजिस्टर(&mtty_dev.dev);
	अगर (ret)
		जाओ failed2;

	ret = mdev_रेजिस्टर_device(&mtty_dev.dev, &mdev_fops);
	अगर (ret)
		जाओ failed3;

	mutex_init(&mdev_list_lock);
	INIT_LIST_HEAD(&mdev_devices_list);

	जाओ all_करोne;

failed3:

	device_unरेजिस्टर(&mtty_dev.dev);
failed2:
	class_destroy(mtty_dev.vd_class);

failed1:
	cdev_del(&mtty_dev.vd_cdev);
	unरेजिस्टर_chrdev_region(mtty_dev.vd_devt, MINORMASK + 1);

all_करोne:
	वापस ret;
पूर्ण

अटल व्योम __निकास mtty_dev_निकास(व्योम)
अणु
	mtty_dev.dev.bus = शून्य;
	mdev_unरेजिस्टर_device(&mtty_dev.dev);

	device_unरेजिस्टर(&mtty_dev.dev);
	idr_destroy(&mtty_dev.vd_idr);
	cdev_del(&mtty_dev.vd_cdev);
	unरेजिस्टर_chrdev_region(mtty_dev.vd_devt, MINORMASK + 1);
	class_destroy(mtty_dev.vd_class);
	mtty_dev.vd_class = शून्य;
	pr_info("mtty_dev: Unloaded!\n");
पूर्ण

module_init(mtty_dev_init)
module_निकास(mtty_dev_निकास)

MODULE_LICENSE("GPL v2");
MODULE_INFO(supported, "Test driver that simulate serial port over PCI");
MODULE_VERSION(VERSION_STRING);
MODULE_AUTHOR(DRIVER_AUTHOR);
