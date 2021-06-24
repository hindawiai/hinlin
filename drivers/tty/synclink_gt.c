<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Device driver क्रम Microgate SyncLink GT serial adapters.
 *
 * written by Paul Fulghum क्रम Microgate Corporation
 * paulkf@microgate.com
 *
 * Microgate and SyncLink are trademarks of Microgate Corporation
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * DEBUG OUTPUT DEFINITIONS
 *
 * uncomment lines below to enable specअगरic types of debug output
 *
 * DBGINFO   inक्रमmation - most verbose output
 * DBGERR    serious errors
 * DBGBH     bottom half service routine debugging
 * DBGISR    पूर्णांकerrupt service routine debugging
 * DBGDATA   output receive and transmit data
 * DBGTBUF   output transmit DMA buffers and रेजिस्टरs
 * DBGRBUF   output receive DMA buffers and रेजिस्टरs
 */

#घोषणा DBGINFO(fmt) अगर (debug_level >= DEBUG_LEVEL_INFO) prपूर्णांकk fmt
#घोषणा DBGERR(fmt) अगर (debug_level >= DEBUG_LEVEL_ERROR) prपूर्णांकk fmt
#घोषणा DBGBH(fmt) अगर (debug_level >= DEBUG_LEVEL_BH) prपूर्णांकk fmt
#घोषणा DBGISR(fmt) अगर (debug_level >= DEBUG_LEVEL_ISR) prपूर्णांकk fmt
#घोषणा DBGDATA(info, buf, size, label) अगर (debug_level >= DEBUG_LEVEL_DATA) trace_block((info), (buf), (size), (label))
/*#घोषणा DBGTBUF(info) dump_tbufs(info)*/
/*#घोषणा DBGRBUF(info) dump_rbufs(info)*/


#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/termios.h>
#समावेश <linux/bitops.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/synclink.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>

#अगर defined(CONFIG_HDLC) || (defined(CONFIG_HDLC_MODULE) && defined(CONFIG_SYNCLINK_GT_MODULE))
#घोषणा SYNCLINK_GENERIC_HDLC 1
#अन्यथा
#घोषणा SYNCLINK_GENERIC_HDLC 0
#पूर्ण_अगर

/*
 * module identअगरication
 */
अटल अक्षर *driver_name     = "SyncLink GT";
अटल अक्षर *slgt_driver_name = "synclink_gt";
अटल अक्षर *tty_dev_prefix  = "ttySLG";
MODULE_LICENSE("GPL");
#घोषणा MGSL_MAGIC 0x5401
#घोषणा MAX_DEVICES 32

अटल स्थिर काष्ठा pci_device_id pci_table[] = अणु
	अणुPCI_VENDOR_ID_MICROGATE, SYNCLINK_GT_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPCI_VENDOR_ID_MICROGATE, SYNCLINK_GT2_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPCI_VENDOR_ID_MICROGATE, SYNCLINK_GT4_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPCI_VENDOR_ID_MICROGATE, SYNCLINK_AC_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु0,पूर्ण, /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_table);

अटल पूर्णांक  init_one(काष्ठा pci_dev *dev,स्थिर काष्ठा pci_device_id *ent);
अटल व्योम हटाओ_one(काष्ठा pci_dev *dev);
अटल काष्ठा pci_driver pci_driver = अणु
	.name		= "synclink_gt",
	.id_table	= pci_table,
	.probe		= init_one,
	.हटाओ		= हटाओ_one,
पूर्ण;

अटल bool pci_रेजिस्टरed;

/*
 * module configuration and status
 */
अटल काष्ठा slgt_info *slgt_device_list;
अटल पूर्णांक slgt_device_count;

अटल पूर्णांक ttymajor;
अटल पूर्णांक debug_level;
अटल पूर्णांक maxframe[MAX_DEVICES];

module_param(ttymajor, पूर्णांक, 0);
module_param(debug_level, पूर्णांक, 0);
module_param_array(maxframe, पूर्णांक, शून्य, 0);

MODULE_PARM_DESC(ttymajor, "TTY major device number override: 0=auto assigned");
MODULE_PARM_DESC(debug_level, "Debug syslog output: 0=disabled, 1 to 5=increasing detail");
MODULE_PARM_DESC(maxframe, "Maximum frame size used by device (4096 to 65535)");

/*
 * tty support and callbacks
 */
अटल काष्ठा tty_driver *serial_driver;

अटल व्योम रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);
अटल व्योम flush_buffer(काष्ठा tty_काष्ठा *tty);
अटल व्योम tx_release(काष्ठा tty_काष्ठा *tty);

/*
 * generic HDLC support
 */
#घोषणा dev_to_port(D) (dev_to_hdlc(D)->priv)


/*
 * device specअगरic काष्ठाures, macros and functions
 */

#घोषणा SLGT_MAX_PORTS 4
#घोषणा SLGT_REG_SIZE  256

/*
 * conditional रुको facility
 */
काष्ठा cond_रुको अणु
	काष्ठा cond_रुको *next;
	रुको_queue_head_t q;
	रुको_queue_entry_t रुको;
	अचिन्हित पूर्णांक data;
पूर्ण;
अटल व्योम flush_cond_रुको(काष्ठा cond_रुको **head);

/*
 * DMA buffer descriptor and access macros
 */
काष्ठा slgt_desc
अणु
	__le16 count;
	__le16 status;
	__le32 pbuf;  /* physical address of data buffer */
	__le32 next;  /* physical address of next descriptor */

	/* driver book keeping */
	अक्षर *buf;          /* भव  address of data buffer */
    	अचिन्हित पूर्णांक pdesc; /* physical address of this descriptor */
	dma_addr_t buf_dma_addr;
	अचिन्हित लघु buf_count;
पूर्ण;

#घोषणा set_desc_buffer(a,b) (a).pbuf = cpu_to_le32((अचिन्हित पूर्णांक)(b))
#घोषणा set_desc_next(a,b) (a).next   = cpu_to_le32((अचिन्हित पूर्णांक)(b))
#घोषणा set_desc_count(a,b)(a).count  = cpu_to_le16((अचिन्हित लघु)(b))
#घोषणा set_desc_eof(a,b)  (a).status = cpu_to_le16((b) ? (le16_to_cpu((a).status) | BIT0) : (le16_to_cpu((a).status) & ~BIT0))
#घोषणा set_desc_status(a, b) (a).status = cpu_to_le16((अचिन्हित लघु)(b))
#घोषणा desc_count(a)      (le16_to_cpu((a).count))
#घोषणा desc_status(a)     (le16_to_cpu((a).status))
#घोषणा desc_complete(a)   (le16_to_cpu((a).status) & BIT15)
#घोषणा desc_eof(a)        (le16_to_cpu((a).status) & BIT2)
#घोषणा desc_crc_error(a)  (le16_to_cpu((a).status) & BIT1)
#घोषणा desc_पात(a)      (le16_to_cpu((a).status) & BIT0)
#घोषणा desc_residue(a)    ((le16_to_cpu((a).status) & 0x38) >> 3)

काष्ठा _input_संकेत_events अणु
	पूर्णांक ri_up;
	पूर्णांक ri_करोwn;
	पूर्णांक dsr_up;
	पूर्णांक dsr_करोwn;
	पूर्णांक dcd_up;
	पूर्णांक dcd_करोwn;
	पूर्णांक cts_up;
	पूर्णांक cts_करोwn;
पूर्ण;

/*
 * device instance data काष्ठाure
 */
काष्ठा slgt_info अणु
	व्योम *अगर_ptr;		/* General purpose poपूर्णांकer (used by SPPP) */
	काष्ठा tty_port port;

	काष्ठा slgt_info *next_device;	/* device list link */

	पूर्णांक magic;

	अक्षर device_name[25];
	काष्ठा pci_dev *pdev;

	पूर्णांक port_count;  /* count of ports on adapter */
	पूर्णांक adapter_num; /* adapter instance number */
	पूर्णांक port_num;    /* port instance number */

	/* array of poपूर्णांकers to port contexts on this adapter */
	काष्ठा slgt_info *port_array[SLGT_MAX_PORTS];

	पूर्णांक			line;		/* tty line instance number */

	काष्ठा mgsl_icount	icount;

	पूर्णांक			समयout;
	पूर्णांक			x_अक्षर;		/* xon/xoff अक्षरacter */
	अचिन्हित पूर्णांक		पढ़ो_status_mask;
	अचिन्हित पूर्णांक 		ignore_status_mask;

	रुको_queue_head_t	status_event_रुको_q;
	रुको_queue_head_t	event_रुको_q;
	काष्ठा समयr_list	tx_समयr;
	काष्ठा समयr_list	rx_समयr;

	अचिन्हित पूर्णांक            gpio_present;
	काष्ठा cond_रुको        *gpio_रुको_q;

	spinlock_t lock;	/* spinlock क्रम synchronizing with ISR */

	काष्ठा work_काष्ठा task;
	u32 pending_bh;
	bool bh_requested;
	bool bh_running;

	पूर्णांक isr_overflow;
	bool irq_requested;	/* true अगर IRQ requested */
	bool irq_occurred;	/* क्रम diagnostics use */

	/* device configuration */

	अचिन्हित पूर्णांक bus_type;
	अचिन्हित पूर्णांक irq_level;
	अचिन्हित दीर्घ irq_flags;

	अचिन्हित अक्षर __iomem * reg_addr;  /* memory mapped रेजिस्टरs address */
	u32 phys_reg_addr;
	bool reg_addr_requested;

	MGSL_PARAMS params;       /* communications parameters */
	u32 idle_mode;
	u32 max_frame_size;       /* as set by device config */

	अचिन्हित पूर्णांक rbuf_fill_level;
	अचिन्हित पूर्णांक rx_pio;
	अचिन्हित पूर्णांक अगर_mode;
	अचिन्हित पूर्णांक base_घड़ी;
	अचिन्हित पूर्णांक xsync;
	अचिन्हित पूर्णांक xctrl;

	/* device status */

	bool rx_enabled;
	bool rx_restart;

	bool tx_enabled;
	bool tx_active;

	अचिन्हित अक्षर संकेतs;    /* serial संकेत states */
	पूर्णांक init_error;  /* initialization error */

	अचिन्हित अक्षर *tx_buf;
	पूर्णांक tx_count;

	अक्षर *flag_buf;
	bool drop_rts_on_tx_करोne;
	काष्ठा	_input_संकेत_events	input_संकेत_events;

	पूर्णांक dcd_chkcount;	/* check counts to prevent */
	पूर्णांक cts_chkcount;	/* too many IRQs अगर a संकेत */
	पूर्णांक dsr_chkcount;	/* is भग्नing */
	पूर्णांक ri_chkcount;

	अक्षर *bufs;		/* भव address of DMA buffer lists */
	dma_addr_t bufs_dma_addr; /* physical address of buffer descriptors */

	अचिन्हित पूर्णांक rbuf_count;
	काष्ठा slgt_desc *rbufs;
	अचिन्हित पूर्णांक rbuf_current;
	अचिन्हित पूर्णांक rbuf_index;
	अचिन्हित पूर्णांक rbuf_fill_index;
	अचिन्हित लघु rbuf_fill_count;

	अचिन्हित पूर्णांक tbuf_count;
	काष्ठा slgt_desc *tbufs;
	अचिन्हित पूर्णांक tbuf_current;
	अचिन्हित पूर्णांक tbuf_start;

	अचिन्हित अक्षर *पंचांगp_rbuf;
	अचिन्हित पूर्णांक पंचांगp_rbuf_count;

	/* SPPP/Cisco HDLC device parts */

	पूर्णांक netcount;
	spinlock_t netlock;
#अगर SYNCLINK_GENERIC_HDLC
	काष्ठा net_device *netdev;
#पूर्ण_अगर

पूर्ण;

अटल MGSL_PARAMS शेष_params = अणु
	.mode            = MGSL_MODE_HDLC,
	.loopback        = 0,
	.flags           = HDLC_FLAG_UNDERRUN_ABORT15,
	.encoding        = HDLC_ENCODING_NRZI_SPACE,
	.घड़ी_speed     = 0,
	.addr_filter     = 0xff,
	.crc_type        = HDLC_CRC_16_CCITT,
	.preamble_length = HDLC_PREAMBLE_LENGTH_8BITS,
	.preamble        = HDLC_PREAMBLE_PATTERN_NONE,
	.data_rate       = 9600,
	.data_bits       = 8,
	.stop_bits       = 1,
	.parity          = ASYNC_PARITY_NONE
पूर्ण;


#घोषणा BH_RECEIVE  1
#घोषणा BH_TRANSMIT 2
#घोषणा BH_STATUS   4
#घोषणा IO_PIN_SHUTDOWN_LIMIT 100

#घोषणा DMAबफ_मानE 256
#घोषणा DESC_LIST_SIZE 4096

#घोषणा MASK_PARITY  BIT1
#घोषणा MASK_FRAMING BIT0
#घोषणा MASK_BREAK   BIT14
#घोषणा MASK_OVERRUN BIT4

#घोषणा GSR   0x00 /* global status */
#घोषणा JCR   0x04 /* JTAG control */
#घोषणा IODR  0x08 /* GPIO direction */
#घोषणा IOER  0x0c /* GPIO पूर्णांकerrupt enable */
#घोषणा IOVR  0x10 /* GPIO value */
#घोषणा IOSR  0x14 /* GPIO पूर्णांकerrupt status */
#घोषणा TDR   0x80 /* tx data */
#घोषणा RDR   0x80 /* rx data */
#घोषणा TCR   0x82 /* tx control */
#घोषणा TIR   0x84 /* tx idle */
#घोषणा TPR   0x85 /* tx preamble */
#घोषणा RCR   0x86 /* rx control */
#घोषणा VCR   0x88 /* V.24 control */
#घोषणा CCR   0x89 /* घड़ी control */
#घोषणा BDR   0x8a /* baud भागisor */
#घोषणा SCR   0x8c /* serial control */
#घोषणा SSR   0x8e /* serial status */
#घोषणा RDCSR 0x90 /* rx DMA control/status */
#घोषणा TDCSR 0x94 /* tx DMA control/status */
#घोषणा RDDAR 0x98 /* rx DMA descriptor address */
#घोषणा TDDAR 0x9c /* tx DMA descriptor address */
#घोषणा XSR   0x40 /* extended sync pattern */
#घोषणा XCR   0x44 /* extended control */

#घोषणा RXIDLE      BIT14
#घोषणा RXBREAK     BIT14
#घोषणा IRQ_TXDATA  BIT13
#घोषणा IRQ_TXIDLE  BIT12
#घोषणा IRQ_TXUNDER BIT11 /* HDLC */
#घोषणा IRQ_RXDATA  BIT10
#घोषणा IRQ_RXIDLE  BIT9  /* HDLC */
#घोषणा IRQ_RXBREAK BIT9  /* async */
#घोषणा IRQ_RXOVER  BIT8
#घोषणा IRQ_DSR     BIT7
#घोषणा IRQ_CTS     BIT6
#घोषणा IRQ_DCD     BIT5
#घोषणा IRQ_RI      BIT4
#घोषणा IRQ_ALL     0x3ff0
#घोषणा IRQ_MASTER  BIT0

#घोषणा slgt_irq_on(info, mask) \
	wr_reg16((info), SCR, (अचिन्हित लघु)(rd_reg16((info), SCR) | (mask)))
#घोषणा slgt_irq_off(info, mask) \
	wr_reg16((info), SCR, (अचिन्हित लघु)(rd_reg16((info), SCR) & ~(mask)))

अटल __u8  rd_reg8(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr);
अटल व्योम  wr_reg8(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u8 value);
अटल __u16 rd_reg16(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr);
अटल व्योम  wr_reg16(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u16 value);
अटल __u32 rd_reg32(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr);
अटल व्योम  wr_reg32(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u32 value);

अटल व्योम  msc_set_vcr(काष्ठा slgt_info *info);

अटल पूर्णांक  startup(काष्ठा slgt_info *info);
अटल पूर्णांक  block_til_पढ़ोy(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp,काष्ठा slgt_info *info);
अटल व्योम shutकरोwn(काष्ठा slgt_info *info);
अटल व्योम program_hw(काष्ठा slgt_info *info);
अटल व्योम change_params(काष्ठा slgt_info *info);

अटल पूर्णांक  adapter_test(काष्ठा slgt_info *info);

अटल व्योम reset_port(काष्ठा slgt_info *info);
अटल व्योम async_mode(काष्ठा slgt_info *info);
अटल व्योम sync_mode(काष्ठा slgt_info *info);

अटल व्योम rx_stop(काष्ठा slgt_info *info);
अटल व्योम rx_start(काष्ठा slgt_info *info);
अटल व्योम reset_rbufs(काष्ठा slgt_info *info);
अटल व्योम मुक्त_rbufs(काष्ठा slgt_info *info, अचिन्हित पूर्णांक first, अचिन्हित पूर्णांक last);
अटल bool rx_get_frame(काष्ठा slgt_info *info);
अटल bool rx_get_buf(काष्ठा slgt_info *info);

अटल व्योम tx_start(काष्ठा slgt_info *info);
अटल व्योम tx_stop(काष्ठा slgt_info *info);
अटल व्योम tx_set_idle(काष्ठा slgt_info *info);
अटल अचिन्हित पूर्णांक tbuf_bytes(काष्ठा slgt_info *info);
अटल व्योम reset_tbufs(काष्ठा slgt_info *info);
अटल व्योम tdma_reset(काष्ठा slgt_info *info);
अटल bool tx_load(काष्ठा slgt_info *info, स्थिर अक्षर *buf, अचिन्हित पूर्णांक count);

अटल व्योम get_संकेतs(काष्ठा slgt_info *info);
अटल व्योम set_संकेतs(काष्ठा slgt_info *info);
अटल व्योम set_rate(काष्ठा slgt_info *info, u32 data_rate);

अटल व्योम bh_transmit(काष्ठा slgt_info *info);
अटल व्योम isr_txeom(काष्ठा slgt_info *info, अचिन्हित लघु status);

अटल व्योम tx_समयout(काष्ठा समयr_list *t);
अटल व्योम rx_समयout(काष्ठा समयr_list *t);

/*
 * ioctl handlers
 */
अटल पूर्णांक  get_stats(काष्ठा slgt_info *info, काष्ठा mgsl_icount __user *user_icount);
अटल पूर्णांक  get_params(काष्ठा slgt_info *info, MGSL_PARAMS __user *params);
अटल पूर्णांक  set_params(काष्ठा slgt_info *info, MGSL_PARAMS __user *params);
अटल पूर्णांक  get_txidle(काष्ठा slgt_info *info, पूर्णांक __user *idle_mode);
अटल पूर्णांक  set_txidle(काष्ठा slgt_info *info, पूर्णांक idle_mode);
अटल पूर्णांक  tx_enable(काष्ठा slgt_info *info, पूर्णांक enable);
अटल पूर्णांक  tx_पात(काष्ठा slgt_info *info);
अटल पूर्णांक  rx_enable(काष्ठा slgt_info *info, पूर्णांक enable);
अटल पूर्णांक  modem_input_रुको(काष्ठा slgt_info *info,पूर्णांक arg);
अटल पूर्णांक  रुको_mgsl_event(काष्ठा slgt_info *info, पूर्णांक __user *mask_ptr);
अटल पूर्णांक  get_पूर्णांकerface(काष्ठा slgt_info *info, पूर्णांक __user *अगर_mode);
अटल पूर्णांक  set_पूर्णांकerface(काष्ठा slgt_info *info, पूर्णांक अगर_mode);
अटल पूर्णांक  set_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *gpio);
अटल पूर्णांक  get_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *gpio);
अटल पूर्णांक  रुको_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *gpio);
अटल पूर्णांक  get_xsync(काष्ठा slgt_info *info, पूर्णांक __user *अगर_mode);
अटल पूर्णांक  set_xsync(काष्ठा slgt_info *info, पूर्णांक अगर_mode);
अटल पूर्णांक  get_xctrl(काष्ठा slgt_info *info, पूर्णांक __user *अगर_mode);
अटल पूर्णांक  set_xctrl(काष्ठा slgt_info *info, पूर्णांक अगर_mode);

/*
 * driver functions
 */
अटल व्योम release_resources(काष्ठा slgt_info *info);

/*
 * DEBUG OUTPUT CODE
 */
#अगर_अघोषित DBGINFO
#घोषणा DBGINFO(fmt)
#पूर्ण_अगर
#अगर_अघोषित DBGERR
#घोषणा DBGERR(fmt)
#पूर्ण_अगर
#अगर_अघोषित DBGBH
#घोषणा DBGBH(fmt)
#पूर्ण_अगर
#अगर_अघोषित DBGISR
#घोषणा DBGISR(fmt)
#पूर्ण_अगर

#अगर_घोषित DBGDATA
अटल व्योम trace_block(काष्ठा slgt_info *info, स्थिर अक्षर *data, पूर्णांक count, स्थिर अक्षर *label)
अणु
	पूर्णांक i;
	पूर्णांक linecount;
	prपूर्णांकk("%s %s data:\n",info->device_name, label);
	जबतक(count) अणु
		linecount = (count > 16) ? 16 : count;
		क्रम(i=0; i < linecount; i++)
			prपूर्णांकk("%02X ",(अचिन्हित अक्षर)data[i]);
		क्रम(;i<17;i++)
			prपूर्णांकk("   ");
		क्रम(i=0;i<linecount;i++) अणु
			अगर (data[i]>=040 && data[i]<=0176)
				prपूर्णांकk("%c",data[i]);
			अन्यथा
				prपूर्णांकk(".");
		पूर्ण
		prपूर्णांकk("\n");
		data  += linecount;
		count -= linecount;
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा DBGDATA(info, buf, size, label)
#पूर्ण_अगर

#अगर_घोषित DBGTBUF
अटल व्योम dump_tbufs(काष्ठा slgt_info *info)
अणु
	पूर्णांक i;
	prपूर्णांकk("tbuf_current=%d\n", info->tbuf_current);
	क्रम (i=0 ; i < info->tbuf_count ; i++) अणु
		prपूर्णांकk("%d: count=%04X status=%04X\n",
			i, le16_to_cpu(info->tbufs[i].count), le16_to_cpu(info->tbufs[i].status));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा DBGTBUF(info)
#पूर्ण_अगर

#अगर_घोषित DBGRBUF
अटल व्योम dump_rbufs(काष्ठा slgt_info *info)
अणु
	पूर्णांक i;
	prपूर्णांकk("rbuf_current=%d\n", info->rbuf_current);
	क्रम (i=0 ; i < info->rbuf_count ; i++) अणु
		prपूर्णांकk("%d: count=%04X status=%04X\n",
			i, le16_to_cpu(info->rbufs[i].count), le16_to_cpu(info->rbufs[i].status));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा DBGRBUF(info)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sanity_check(काष्ठा slgt_info *info, अक्षर *devname, स्थिर अक्षर *name)
अणु
#अगर_घोषित SANITY_CHECK
	अगर (!info) अणु
		prपूर्णांकk("null struct slgt_info for (%s) in %s\n", devname, name);
		वापस 1;
	पूर्ण
	अगर (info->magic != MGSL_MAGIC) अणु
		prपूर्णांकk("bad magic number struct slgt_info (%s) in %s\n", devname, name);
		वापस 1;
	पूर्ण
#अन्यथा
	अगर (!info)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * line discipline callback wrappers
 *
 * The wrappers मुख्यtain line discipline references
 * जबतक calling पूर्णांकo the line discipline.
 *
 * ldisc_receive_buf  - pass receive data to line discipline
 */
अटल व्योम ldisc_receive_buf(काष्ठा tty_काष्ठा *tty,
			      स्थिर __u8 *data, अक्षर *flags, पूर्णांक count)
अणु
	काष्ठा tty_ldisc *ld;
	अगर (!tty)
		वापस;
	ld = tty_ldisc_ref(tty);
	अगर (ld) अणु
		अगर (ld->ops->receive_buf)
			ld->ops->receive_buf(tty, data, flags, count);
		tty_ldisc_deref(ld);
	पूर्ण
पूर्ण

/* tty callbacks */

अटल पूर्णांक खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा slgt_info *info;
	पूर्णांक retval, line;
	अचिन्हित दीर्घ flags;

	line = tty->index;
	अगर (line >= slgt_device_count) अणु
		DBGERR(("%s: open with invalid line #%d.\n", driver_name, line));
		वापस -ENODEV;
	पूर्ण

	info = slgt_device_list;
	जबतक(info && info->line != line)
		info = info->next_device;
	अगर (sanity_check(info, tty->name, "open"))
		वापस -ENODEV;
	अगर (info->init_error) अणु
		DBGERR(("%s init error=%d\n", info->device_name, info->init_error));
		वापस -ENODEV;
	पूर्ण

	tty->driver_data = info;
	info->port.tty = tty;

	DBGINFO(("%s open, old ref count = %d\n", info->device_name, info->port.count));

	mutex_lock(&info->port.mutex);

	spin_lock_irqsave(&info->netlock, flags);
	अगर (info->netcount) अणु
		retval = -EBUSY;
		spin_unlock_irqrestore(&info->netlock, flags);
		mutex_unlock(&info->port.mutex);
		जाओ cleanup;
	पूर्ण
	info->port.count++;
	spin_unlock_irqrestore(&info->netlock, flags);

	अगर (info->port.count == 1) अणु
		/* 1st खोलो on this device, init hardware */
		retval = startup(info);
		अगर (retval < 0) अणु
			mutex_unlock(&info->port.mutex);
			जाओ cleanup;
		पूर्ण
	पूर्ण
	mutex_unlock(&info->port.mutex);
	retval = block_til_पढ़ोy(tty, filp, info);
	अगर (retval) अणु
		DBGINFO(("%s block_til_ready rc=%d\n", info->device_name, retval));
		जाओ cleanup;
	पूर्ण

	retval = 0;

cleanup:
	अगर (retval) अणु
		अगर (tty->count == 1)
			info->port.tty = शून्य; /* tty layer will release tty काष्ठा */
		अगर(info->port.count)
			info->port.count--;
	पूर्ण

	DBGINFO(("%s open rc=%d\n", info->device_name, retval));
	वापस retval;
पूर्ण

अटल व्योम बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा slgt_info *info = tty->driver_data;

	अगर (sanity_check(info, tty->name, "close"))
		वापस;
	DBGINFO(("%s close entry, count=%d\n", info->device_name, info->port.count));

	अगर (tty_port_बंद_start(&info->port, tty, filp) == 0)
		जाओ cleanup;

	mutex_lock(&info->port.mutex);
	अगर (tty_port_initialized(&info->port))
 		रुको_until_sent(tty, info->समयout);
	flush_buffer(tty);
	tty_ldisc_flush(tty);

	shutकरोwn(info);
	mutex_unlock(&info->port.mutex);

	tty_port_बंद_end(&info->port, tty);
	info->port.tty = शून्य;
cleanup:
	DBGINFO(("%s close exit, count=%d\n", tty->driver->name, info->port.count));
पूर्ण

अटल व्योम hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "hangup"))
		वापस;
	DBGINFO(("%s hangup\n", info->device_name));

	flush_buffer(tty);

	mutex_lock(&info->port.mutex);
	shutकरोwn(info);

	spin_lock_irqsave(&info->port.lock, flags);
	info->port.count = 0;
	info->port.tty = शून्य;
	spin_unlock_irqrestore(&info->port.lock, flags);
	tty_port_set_active(&info->port, 0);
	mutex_unlock(&info->port.mutex);

	wake_up_पूर्णांकerruptible(&info->port.खोलो_रुको);
पूर्ण

अटल व्योम set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old_termios)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s set_termios\n", tty->driver->name));

	change_params(info);

	/* Handle transition to B0 status */
	अगर ((old_termios->c_cflag & CBAUD) && !C_BAUD(tty)) अणु
		info->संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
		spin_lock_irqsave(&info->lock,flags);
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण

	/* Handle transition away from B0 status */
	अगर (!(old_termios->c_cflag & CBAUD) && C_BAUD(tty)) अणु
		info->संकेतs |= SerialSignal_DTR;
		अगर (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->संकेतs |= SerialSignal_RTS;
		spin_lock_irqsave(&info->lock,flags);
	 	set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण

	/* Handle turning off CRTSCTS */
	अगर ((old_termios->c_cflag & CRTSCTS) && !C_CRTSCTS(tty)) अणु
		tty->hw_stopped = 0;
		tx_release(tty);
	पूर्ण
पूर्ण

अटल व्योम update_tx_समयr(काष्ठा slgt_info *info)
अणु
	/*
	 * use worst हाल speed of 1200bps to calculate transmit समयout
	 * based on data in buffers (tbuf_bytes) and FIFO (128 bytes)
	 */
	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		पूर्णांक समयout  = (tbuf_bytes(info) * 7) + 1000;
		mod_समयr(&info->tx_समयr, jअगरfies + msecs_to_jअगरfies(समयout));
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखो(काष्ठा tty_काष्ठा *tty,
		 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक ret = 0;
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "write"))
		वापस -EIO;

	DBGINFO(("%s write count=%d\n", info->device_name, count));

	अगर (!info->tx_buf || (count > info->max_frame_size))
		वापस -EIO;

	अगर (!count || tty->stopped || tty->hw_stopped)
		वापस 0;

	spin_lock_irqsave(&info->lock, flags);

	अगर (info->tx_count) अणु
		/* send accumulated data from send_अक्षर() */
		अगर (!tx_load(info, info->tx_buf, info->tx_count))
			जाओ cleanup;
		info->tx_count = 0;
	पूर्ण

	अगर (tx_load(info, buf, count))
		ret = count;

cleanup:
	spin_unlock_irqrestore(&info->lock, flags);
	DBGINFO(("%s write rc=%d\n", info->device_name, ret));
	वापस ret;
पूर्ण

अटल पूर्णांक put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (sanity_check(info, tty->name, "put_char"))
		वापस 0;
	DBGINFO(("%s put_char(%d)\n", info->device_name, ch));
	अगर (!info->tx_buf)
		वापस 0;
	spin_lock_irqsave(&info->lock,flags);
	अगर (info->tx_count < info->max_frame_size) अणु
		info->tx_buf[info->tx_count++] = ch;
		ret = 1;
	पूर्ण
	spin_unlock_irqrestore(&info->lock,flags);
	वापस ret;
पूर्ण

अटल व्योम send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "send_xchar"))
		वापस;
	DBGINFO(("%s send_xchar(%d)\n", info->device_name, ch));
	info->x_अक्षर = ch;
	अगर (ch) अणु
		spin_lock_irqsave(&info->lock,flags);
		अगर (!info->tx_enabled)
		 	tx_start(info);
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण
पूर्ण

अटल व्योम रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ orig_jअगरfies, अक्षर_समय;

	अगर (!info )
		वापस;
	अगर (sanity_check(info, tty->name, "wait_until_sent"))
		वापस;
	DBGINFO(("%s wait_until_sent entry\n", info->device_name));
	अगर (!tty_port_initialized(&info->port))
		जाओ निकास;

	orig_jअगरfies = jअगरfies;

	/* Set check पूर्णांकerval to 1/5 of estimated समय to
	 * send a अक्षरacter, and make it at least 1. The check
	 * पूर्णांकerval should also be less than the समयout.
	 * Note: use tight timings here to satisfy the NIST-PCTS.
	 */

	अगर (info->params.data_rate) अणु
	       	अक्षर_समय = info->समयout/(32 * 5);
		अगर (!अक्षर_समय)
			अक्षर_समय++;
	पूर्ण अन्यथा
		अक्षर_समय = 1;

	अगर (समयout)
		अक्षर_समय = min_t(अचिन्हित दीर्घ, अक्षर_समय, समयout);

	जबतक (info->tx_active) अणु
		msleep_पूर्णांकerruptible(jअगरfies_to_msecs(अक्षर_समय));
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (समयout && समय_after(jअगरfies, orig_jअगरfies + समयout))
			अवरोध;
	पूर्ण
निकास:
	DBGINFO(("%s wait_until_sent exit\n", info->device_name));
पूर्ण

अटल पूर्णांक ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	पूर्णांक ret;

	अगर (sanity_check(info, tty->name, "write_room"))
		वापस 0;
	ret = (info->tx_active) ? 0 : HDLC_MAX_FRAME_SIZE;
	DBGINFO(("%s write_room=%d\n", info->device_name, ret));
	वापस ret;
पूर्ण

अटल व्योम flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "flush_chars"))
		वापस;
	DBGINFO(("%s flush_chars entry tx_count=%d\n", info->device_name, info->tx_count));

	अगर (info->tx_count <= 0 || tty->stopped ||
	    tty->hw_stopped || !info->tx_buf)
		वापस;

	DBGINFO(("%s flush_chars start transmit\n", info->device_name));

	spin_lock_irqsave(&info->lock,flags);
	अगर (info->tx_count && tx_load(info, info->tx_buf, info->tx_count))
		info->tx_count = 0;
	spin_unlock_irqrestore(&info->lock,flags);
पूर्ण

अटल व्योम flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "flush_buffer"))
		वापस;
	DBGINFO(("%s flush_buffer\n", info->device_name));

	spin_lock_irqsave(&info->lock, flags);
	info->tx_count = 0;
	spin_unlock_irqrestore(&info->lock, flags);

	tty_wakeup(tty);
पूर्ण

/*
 * throttle (stop) transmitter
 */
अटल व्योम tx_hold(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "tx_hold"))
		वापस;
	DBGINFO(("%s tx_hold\n", info->device_name));
	spin_lock_irqsave(&info->lock,flags);
	अगर (info->tx_enabled && info->params.mode == MGSL_MODE_ASYNC)
	 	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);
पूर्ण

/*
 * release (start) transmitter
 */
अटल व्योम tx_release(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "tx_release"))
		वापस;
	DBGINFO(("%s tx_release\n", info->device_name));
	spin_lock_irqsave(&info->lock, flags);
	अगर (info->tx_count && tx_load(info, info->tx_buf, info->tx_count))
		info->tx_count = 0;
	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

/*
 * Service an IOCTL request
 *
 * Arguments
 *
 * 	tty	poपूर्णांकer to tty instance data
 * 	cmd	IOCTL command code
 * 	arg	command argument/context
 *
 * Return 0 अगर success, otherwise error code
 */
अटल पूर्णांक ioctl(काष्ठा tty_काष्ठा *tty,
		 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक ret;

	अगर (sanity_check(info, tty->name, "ioctl"))
		वापस -ENODEV;
	DBGINFO(("%s ioctl() cmd=%08X\n", info->device_name, cmd));

	अगर (cmd != TIOCMIWAIT) अणु
		अगर (tty_io_error(tty))
		    वापस -EIO;
	पूर्ण

	चयन (cmd) अणु
	हाल MGSL_IOCWAITEVENT:
		वापस रुको_mgsl_event(info, argp);
	हाल TIOCMIWAIT:
		वापस modem_input_रुको(info,(पूर्णांक)arg);
	हाल MGSL_IOCSGPIO:
		वापस set_gpio(info, argp);
	हाल MGSL_IOCGGPIO:
		वापस get_gpio(info, argp);
	हाल MGSL_IOCWAITGPIO:
		वापस रुको_gpio(info, argp);
	हाल MGSL_IOCGXSYNC:
		वापस get_xsync(info, argp);
	हाल MGSL_IOCSXSYNC:
		वापस set_xsync(info, (पूर्णांक)arg);
	हाल MGSL_IOCGXCTRL:
		वापस get_xctrl(info, argp);
	हाल MGSL_IOCSXCTRL:
		वापस set_xctrl(info, (पूर्णांक)arg);
	पूर्ण
	mutex_lock(&info->port.mutex);
	चयन (cmd) अणु
	हाल MGSL_IOCGPARAMS:
		ret = get_params(info, argp);
		अवरोध;
	हाल MGSL_IOCSPARAMS:
		ret = set_params(info, argp);
		अवरोध;
	हाल MGSL_IOCGTXIDLE:
		ret = get_txidle(info, argp);
		अवरोध;
	हाल MGSL_IOCSTXIDLE:
		ret = set_txidle(info, (पूर्णांक)arg);
		अवरोध;
	हाल MGSL_IOCTXENABLE:
		ret = tx_enable(info, (पूर्णांक)arg);
		अवरोध;
	हाल MGSL_IOCRXENABLE:
		ret = rx_enable(info, (पूर्णांक)arg);
		अवरोध;
	हाल MGSL_IOCTXABORT:
		ret = tx_पात(info);
		अवरोध;
	हाल MGSL_IOCGSTATS:
		ret = get_stats(info, argp);
		अवरोध;
	हाल MGSL_IOCGIF:
		ret = get_पूर्णांकerface(info, argp);
		अवरोध;
	हाल MGSL_IOCSIF:
		ret = set_पूर्णांकerface(info,(पूर्णांक)arg);
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
	पूर्ण
	mutex_unlock(&info->port.mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक get_icount(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount)

अणु
	काष्ठा slgt_info *info = tty->driver_data;
	काष्ठा mgsl_icount cnow;	/* kernel counter temps */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock,flags);
	cnow = info->icount;
	spin_unlock_irqrestore(&info->lock,flags);

	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	icount->rx = cnow.rx;
	icount->tx = cnow.tx;
	icount->frame = cnow.frame;
	icount->overrun = cnow.overrun;
	icount->parity = cnow.parity;
	icount->brk = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	वापस 0;
पूर्ण

/*
 * support क्रम 32 bit ioctl calls on 64 bit प्रणालीs
 */
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ get_params32(काष्ठा slgt_info *info, काष्ठा MGSL_PARAMS32 __user *user_params)
अणु
	काष्ठा MGSL_PARAMS32 पंचांगp_params;

	DBGINFO(("%s get_params32\n", info->device_name));
	स_रखो(&पंचांगp_params, 0, माप(पंचांगp_params));
	पंचांगp_params.mode            = (compat_uदीर्घ_t)info->params.mode;
	पंचांगp_params.loopback        = info->params.loopback;
	पंचांगp_params.flags           = info->params.flags;
	पंचांगp_params.encoding        = info->params.encoding;
	पंचांगp_params.घड़ी_speed     = (compat_uदीर्घ_t)info->params.घड़ी_speed;
	पंचांगp_params.addr_filter     = info->params.addr_filter;
	पंचांगp_params.crc_type        = info->params.crc_type;
	पंचांगp_params.preamble_length = info->params.preamble_length;
	पंचांगp_params.preamble        = info->params.preamble;
	पंचांगp_params.data_rate       = (compat_uदीर्घ_t)info->params.data_rate;
	पंचांगp_params.data_bits       = info->params.data_bits;
	पंचांगp_params.stop_bits       = info->params.stop_bits;
	पंचांगp_params.parity          = info->params.parity;
	अगर (copy_to_user(user_params, &पंचांगp_params, माप(काष्ठा MGSL_PARAMS32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ set_params32(काष्ठा slgt_info *info, काष्ठा MGSL_PARAMS32 __user *new_params)
अणु
	काष्ठा MGSL_PARAMS32 पंचांगp_params;

	DBGINFO(("%s set_params32\n", info->device_name));
	अगर (copy_from_user(&पंचांगp_params, new_params, माप(काष्ठा MGSL_PARAMS32)))
		वापस -EFAULT;

	spin_lock(&info->lock);
	अगर (पंचांगp_params.mode == MGSL_MODE_BASE_CLOCK) अणु
		info->base_घड़ी = पंचांगp_params.घड़ी_speed;
	पूर्ण अन्यथा अणु
		info->params.mode            = पंचांगp_params.mode;
		info->params.loopback        = पंचांगp_params.loopback;
		info->params.flags           = पंचांगp_params.flags;
		info->params.encoding        = पंचांगp_params.encoding;
		info->params.घड़ी_speed     = पंचांगp_params.घड़ी_speed;
		info->params.addr_filter     = पंचांगp_params.addr_filter;
		info->params.crc_type        = पंचांगp_params.crc_type;
		info->params.preamble_length = पंचांगp_params.preamble_length;
		info->params.preamble        = पंचांगp_params.preamble;
		info->params.data_rate       = पंचांगp_params.data_rate;
		info->params.data_bits       = पंचांगp_params.data_bits;
		info->params.stop_bits       = पंचांगp_params.stop_bits;
		info->params.parity          = पंचांगp_params.parity;
	पूर्ण
	spin_unlock(&info->lock);

	program_hw(info);

	वापस 0;
पूर्ण

अटल दीर्घ slgt_compat_ioctl(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	पूर्णांक rc;

	अगर (sanity_check(info, tty->name, "compat_ioctl"))
		वापस -ENODEV;
	DBGINFO(("%s compat_ioctl() cmd=%08X\n", info->device_name, cmd));

	चयन (cmd) अणु
	हाल MGSL_IOCSPARAMS32:
		rc = set_params32(info, compat_ptr(arg));
		अवरोध;

	हाल MGSL_IOCGPARAMS32:
		rc = get_params32(info, compat_ptr(arg));
		अवरोध;

	हाल MGSL_IOCGPARAMS:
	हाल MGSL_IOCSPARAMS:
	हाल MGSL_IOCGTXIDLE:
	हाल MGSL_IOCGSTATS:
	हाल MGSL_IOCWAITEVENT:
	हाल MGSL_IOCGIF:
	हाल MGSL_IOCSGPIO:
	हाल MGSL_IOCGGPIO:
	हाल MGSL_IOCWAITGPIO:
	हाल MGSL_IOCGXSYNC:
	हाल MGSL_IOCGXCTRL:
		rc = ioctl(tty, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
		अवरोध;
	शेष:
		rc = ioctl(tty, cmd, arg);
	पूर्ण
	DBGINFO(("%s compat_ioctl() cmd=%08X rc=%d\n", info->device_name, cmd, rc));
	वापस rc;
पूर्ण
#अन्यथा
#घोषणा slgt_compat_ioctl शून्य
#पूर्ण_अगर /* अगरdef CONFIG_COMPAT */

/*
 * proc fs support
 */
अटल अंतरभूत व्योम line_info(काष्ठा seq_file *m, काष्ठा slgt_info *info)
अणु
	अक्षर stat_buf[30];
	अचिन्हित दीर्घ flags;

	seq_म_लिखो(m, "%s: IO=%08X IRQ=%d MaxFrameSize=%u\n",
		      info->device_name, info->phys_reg_addr,
		      info->irq_level, info->max_frame_size);

	/* output current serial संकेत states */
	spin_lock_irqsave(&info->lock,flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock,flags);

	stat_buf[0] = 0;
	stat_buf[1] = 0;
	अगर (info->संकेतs & SerialSignal_RTS)
		म_जोड़ो(stat_buf, "|RTS");
	अगर (info->संकेतs & SerialSignal_CTS)
		म_जोड़ो(stat_buf, "|CTS");
	अगर (info->संकेतs & SerialSignal_DTR)
		म_जोड़ो(stat_buf, "|DTR");
	अगर (info->संकेतs & SerialSignal_DSR)
		म_जोड़ो(stat_buf, "|DSR");
	अगर (info->संकेतs & SerialSignal_DCD)
		म_जोड़ो(stat_buf, "|CD");
	अगर (info->संकेतs & SerialSignal_RI)
		म_जोड़ो(stat_buf, "|RI");

	अगर (info->params.mode != MGSL_MODE_ASYNC) अणु
		seq_म_लिखो(m, "\tHDLC txok:%d rxok:%d",
			       info->icount.txok, info->icount.rxok);
		अगर (info->icount.txunder)
			seq_म_लिखो(m, " txunder:%d", info->icount.txunder);
		अगर (info->icount.txपात)
			seq_म_लिखो(m, " txabort:%d", info->icount.txपात);
		अगर (info->icount.rxलघु)
			seq_म_लिखो(m, " rxshort:%d", info->icount.rxलघु);
		अगर (info->icount.rxदीर्घ)
			seq_म_लिखो(m, " rxlong:%d", info->icount.rxदीर्घ);
		अगर (info->icount.rxover)
			seq_म_लिखो(m, " rxover:%d", info->icount.rxover);
		अगर (info->icount.rxcrc)
			seq_म_लिखो(m, " rxcrc:%d", info->icount.rxcrc);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "\tASYNC tx:%d rx:%d",
			       info->icount.tx, info->icount.rx);
		अगर (info->icount.frame)
			seq_म_लिखो(m, " fe:%d", info->icount.frame);
		अगर (info->icount.parity)
			seq_म_लिखो(m, " pe:%d", info->icount.parity);
		अगर (info->icount.brk)
			seq_म_लिखो(m, " brk:%d", info->icount.brk);
		अगर (info->icount.overrun)
			seq_म_लिखो(m, " oe:%d", info->icount.overrun);
	पूर्ण

	/* Append serial संकेत status to end */
	seq_म_लिखो(m, " %s\n", stat_buf+1);

	seq_म_लिखो(m, "\ttxactive=%d bh_req=%d bh_run=%d pending_bh=%x\n",
		       info->tx_active,info->bh_requested,info->bh_running,
		       info->pending_bh);
पूर्ण

/* Called to prपूर्णांक inक्रमmation about devices
 */
अटल पूर्णांक synclink_gt_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा slgt_info *info;

	seq_माला_दो(m, "synclink_gt driver\n");

	info = slgt_device_list;
	जबतक( info ) अणु
		line_info(m, info);
		info = info->next_device;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * वापस count of bytes in transmit buffer
 */
अटल पूर्णांक अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	पूर्णांक count;
	अगर (sanity_check(info, tty->name, "chars_in_buffer"))
		वापस 0;
	count = tbuf_bytes(info);
	DBGINFO(("%s chars_in_buffer()=%d\n", info->device_name, count));
	वापस count;
पूर्ण

/*
 * संकेत remote device to throttle send data (our receive data)
 */
अटल व्योम throttle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "throttle"))
		वापस;
	DBGINFO(("%s throttle\n", info->device_name));
	अगर (I_IXOFF(tty))
		send_xअक्षर(tty, STOP_CHAR(tty));
	अगर (C_CRTSCTS(tty)) अणु
		spin_lock_irqsave(&info->lock,flags);
		info->संकेतs &= ~SerialSignal_RTS;
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण
पूर्ण

/*
 * संकेत remote device to stop throttling send data (our receive data)
 */
अटल व्योम unthrottle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "unthrottle"))
		वापस;
	DBGINFO(("%s unthrottle\n", info->device_name));
	अगर (I_IXOFF(tty)) अणु
		अगर (info->x_अक्षर)
			info->x_अक्षर = 0;
		अन्यथा
			send_xअक्षर(tty, START_CHAR(tty));
	पूर्ण
	अगर (C_CRTSCTS(tty)) अणु
		spin_lock_irqsave(&info->lock,flags);
		info->संकेतs |= SerialSignal_RTS;
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण
पूर्ण

/*
 * set or clear transmit अवरोध condition
 * अवरोध_state	-1=set अवरोध condition, 0=clear
 */
अटल पूर्णांक set_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित लघु value;
	अचिन्हित दीर्घ flags;

	अगर (sanity_check(info, tty->name, "set_break"))
		वापस -EINVAL;
	DBGINFO(("%s set_break(%d)\n", info->device_name, अवरोध_state));

	spin_lock_irqsave(&info->lock,flags);
	value = rd_reg16(info, TCR);
 	अगर (अवरोध_state == -1)
		value |= BIT6;
	अन्यथा
		value &= ~BIT6;
	wr_reg16(info, TCR, value);
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

#अगर SYNCLINK_GENERIC_HDLC

/**
 * hdlcdev_attach - called by generic HDLC layer when protocol selected (PPP, frame relay, etc.)
 * @dev:      poपूर्णांकer to network device काष्ठाure
 * @encoding: serial encoding setting
 * @parity:   FCS setting
 *
 * Set encoding and frame check sequence (FCS) options.
 *
 * Return: 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			  अचिन्हित लघु parity)
अणु
	काष्ठा slgt_info *info = dev_to_port(dev);
	अचिन्हित अक्षर  new_encoding;
	अचिन्हित लघु new_crctype;

	/* वापस error अगर TTY पूर्णांकerface खोलो */
	अगर (info->port.count)
		वापस -EBUSY;

	DBGINFO(("%s hdlcdev_attach\n", info->device_name));

	चयन (encoding)
	अणु
	हाल ENCODING_NRZ:        new_encoding = HDLC_ENCODING_NRZ; अवरोध;
	हाल ENCODING_NRZI:       new_encoding = HDLC_ENCODING_NRZI_SPACE; अवरोध;
	हाल ENCODING_FM_MARK:    new_encoding = HDLC_ENCODING_BIPHASE_MARK; अवरोध;
	हाल ENCODING_FM_SPACE:   new_encoding = HDLC_ENCODING_BIPHASE_SPACE; अवरोध;
	हाल ENCODING_MANCHESTER: new_encoding = HDLC_ENCODING_BIPHASE_LEVEL; अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण

	चयन (parity)
	अणु
	हाल PARITY_NONE:            new_crctype = HDLC_CRC_NONE; अवरोध;
	हाल PARITY_CRC16_PR1_CCITT: new_crctype = HDLC_CRC_16_CCITT; अवरोध;
	हाल PARITY_CRC32_PR1_CCITT: new_crctype = HDLC_CRC_32_CCITT; अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण

	info->params.encoding = new_encoding;
	info->params.crc_type = new_crctype;

	/* अगर network पूर्णांकerface up, reprogram hardware */
	अगर (info->netcount)
		program_hw(info);

	वापस 0;
पूर्ण

/**
 * hdlcdev_xmit - called by generic HDLC layer to send a frame
 * @skb: socket buffer containing HDLC frame
 * @dev: poपूर्णांकer to network device काष्ठाure
 */
अटल netdev_tx_t hdlcdev_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा slgt_info *info = dev_to_port(dev);
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s hdlc_xmit\n", dev->name));

	अगर (!skb->len)
		वापस NETDEV_TX_OK;

	/* stop sending until this frame completes */
	netअगर_stop_queue(dev);

	/* update network statistics */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/* save start समय क्रम transmit समयout detection */
	netअगर_trans_update(dev);

	spin_lock_irqsave(&info->lock, flags);
	tx_load(info, skb->data, skb->len);
	spin_unlock_irqrestore(&info->lock, flags);

	/* करोne with socket buffer, so मुक्त it */
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * hdlcdev_खोलो - called by network layer when पूर्णांकerface enabled
 * @dev: poपूर्णांकer to network device काष्ठाure
 *
 * Claim resources and initialize hardware.
 *
 * Return: 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा slgt_info *info = dev_to_port(dev);
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (!try_module_get(THIS_MODULE))
		वापस -EBUSY;

	DBGINFO(("%s hdlcdev_open\n", dev->name));

	/* generic HDLC layer खोलो processing */
	rc = hdlc_खोलो(dev);
	अगर (rc)
		वापस rc;

	/* arbitrate between network and tty खोलोs */
	spin_lock_irqsave(&info->netlock, flags);
	अगर (info->port.count != 0 || info->netcount != 0) अणु
		DBGINFO(("%s hdlc_open busy\n", dev->name));
		spin_unlock_irqrestore(&info->netlock, flags);
		वापस -EBUSY;
	पूर्ण
	info->netcount=1;
	spin_unlock_irqrestore(&info->netlock, flags);

	/* claim resources and init adapter */
	अगर ((rc = startup(info)) != 0) अणु
		spin_lock_irqsave(&info->netlock, flags);
		info->netcount=0;
		spin_unlock_irqrestore(&info->netlock, flags);
		वापस rc;
	पूर्ण

	/* निश्चित RTS and DTR, apply hardware settings */
	info->संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	program_hw(info);

	/* enable network layer transmit */
	netअगर_trans_update(dev);
	netअगर_start_queue(dev);

	/* inक्रमm generic HDLC layer of current DCD status */
	spin_lock_irqsave(&info->lock, flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);
	अगर (info->संकेतs & SerialSignal_DCD)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

/**
 * hdlcdev_बंद - called by network layer when पूर्णांकerface is disabled
 * @dev:  poपूर्णांकer to network device काष्ठाure
 *
 * Shutकरोwn hardware and release resources.
 *
 * Return: 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा slgt_info *info = dev_to_port(dev);
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s hdlcdev_close\n", dev->name));

	netअगर_stop_queue(dev);

	/* shutकरोwn adapter and release resources */
	shutकरोwn(info);

	hdlc_बंद(dev);

	spin_lock_irqsave(&info->netlock, flags);
	info->netcount=0;
	spin_unlock_irqrestore(&info->netlock, flags);

	module_put(THIS_MODULE);
	वापस 0;
पूर्ण

/**
 * hdlcdev_ioctl - called by network layer to process IOCTL call to network device
 * @dev: poपूर्णांकer to network device काष्ठाure
 * @अगरr: poपूर्णांकer to network पूर्णांकerface request काष्ठाure
 * @cmd: IOCTL command code
 *
 * Return: 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	काष्ठा slgt_info *info = dev_to_port(dev);
	अचिन्हित पूर्णांक flags;

	DBGINFO(("%s hdlcdev_ioctl\n", dev->name));

	/* वापस error अगर TTY पूर्णांकerface खोलो */
	अगर (info->port.count)
		वापस -EBUSY;

	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	स_रखो(&new_line, 0, माप(new_line));

	चयन(अगरr->अगरr_settings.type) अणु
	हाल IF_GET_IFACE: /* वापस current sync_serial_settings */

		अगरr->अगरr_settings.type = IF_IFACE_SYNC_SERIAL;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण

		flags = info->params.flags & (HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_RXC_DPLL |
					      HDLC_FLAG_RXC_BRG    | HDLC_FLAG_RXC_TXCPIN |
					      HDLC_FLAG_TXC_TXCPIN | HDLC_FLAG_TXC_DPLL |
					      HDLC_FLAG_TXC_BRG    | HDLC_FLAG_TXC_RXCPIN);

		चयन (flags)अणु
		हाल (HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_TXCPIN): new_line.घड़ी_प्रकारype = CLOCK_EXT; अवरोध;
		हाल (HDLC_FLAG_RXC_BRG    | HDLC_FLAG_TXC_BRG):    new_line.घड़ी_प्रकारype = CLOCK_INT; अवरोध;
		हाल (HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_BRG):    new_line.घड़ी_प्रकारype = CLOCK_TXINT; अवरोध;
		हाल (HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_RXCPIN): new_line.घड़ी_प्रकारype = CLOCK_TXFROMRX; अवरोध;
		शेष: new_line.घड़ी_प्रकारype = CLOCK_DEFAULT;
		पूर्ण

		new_line.घड़ी_rate = info->params.घड़ी_speed;
		new_line.loopback   = info->params.loopback ? 1:0;

		अगर (copy_to_user(line, &new_line, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_IFACE_SYNC_SERIAL: /* set sync_serial_settings */

		अगर(!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&new_line, line, size))
			वापस -EFAULT;

		चयन (new_line.घड़ी_प्रकारype)
		अणु
		हाल CLOCK_EXT:      flags = HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_TXCPIN; अवरोध;
		हाल CLOCK_TXFROMRX: flags = HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_RXCPIN; अवरोध;
		हाल CLOCK_INT:      flags = HDLC_FLAG_RXC_BRG    | HDLC_FLAG_TXC_BRG;    अवरोध;
		हाल CLOCK_TXINT:    flags = HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_TXC_BRG;    अवरोध;
		हाल CLOCK_DEFAULT:  flags = info->params.flags &
					     (HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_RXC_DPLL |
					      HDLC_FLAG_RXC_BRG    | HDLC_FLAG_RXC_TXCPIN |
					      HDLC_FLAG_TXC_TXCPIN | HDLC_FLAG_TXC_DPLL |
					      HDLC_FLAG_TXC_BRG    | HDLC_FLAG_TXC_RXCPIN); अवरोध;
		शेष: वापस -EINVAL;
		पूर्ण

		अगर (new_line.loopback != 0 && new_line.loopback != 1)
			वापस -EINVAL;

		info->params.flags &= ~(HDLC_FLAG_RXC_RXCPIN | HDLC_FLAG_RXC_DPLL |
					HDLC_FLAG_RXC_BRG    | HDLC_FLAG_RXC_TXCPIN |
					HDLC_FLAG_TXC_TXCPIN | HDLC_FLAG_TXC_DPLL |
					HDLC_FLAG_TXC_BRG    | HDLC_FLAG_TXC_RXCPIN);
		info->params.flags |= flags;

		info->params.loopback = new_line.loopback;

		अगर (flags & (HDLC_FLAG_RXC_BRG | HDLC_FLAG_TXC_BRG))
			info->params.घड़ी_speed = new_line.घड़ी_rate;
		अन्यथा
			info->params.घड़ी_speed = 0;

		/* अगर network पूर्णांकerface up, reprogram hardware */
		अगर (info->netcount)
			program_hw(info);
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण

/**
 * hdlcdev_tx_समयout - called by network layer when transmit समयout is detected
 * @dev: poपूर्णांकer to network device काष्ठाure
 * @txqueue: unused
 */
अटल व्योम hdlcdev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा slgt_info *info = dev_to_port(dev);
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s hdlcdev_tx_timeout\n", dev->name));

	dev->stats.tx_errors++;
	dev->stats.tx_पातed_errors++;

	spin_lock_irqsave(&info->lock,flags);
	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);

	netअगर_wake_queue(dev);
पूर्ण

/**
 * hdlcdev_tx_करोne - called by device driver when transmit completes
 * @info: poपूर्णांकer to device instance inक्रमmation
 *
 * Reenable network layer transmit अगर stopped.
 */
अटल व्योम hdlcdev_tx_करोne(काष्ठा slgt_info *info)
अणु
	अगर (netअगर_queue_stopped(info->netdev))
		netअगर_wake_queue(info->netdev);
पूर्ण

/**
 * hdlcdev_rx - called by device driver when frame received
 * @info: poपूर्णांकer to device instance inक्रमmation
 * @buf:  poपूर्णांकer to buffer contianing frame data
 * @size: count of data bytes in buf
 *
 * Pass frame to network layer.
 */
अटल व्योम hdlcdev_rx(काष्ठा slgt_info *info, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb = dev_alloc_skb(size);
	काष्ठा net_device *dev = info->netdev;

	DBGINFO(("%s hdlcdev_rx\n", dev->name));

	अगर (skb == शून्य) अणु
		DBGERR(("%s: can't alloc skb, drop packet\n", dev->name));
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	skb_put_data(skb, buf, size);

	skb->protocol = hdlc_type_trans(skb, dev);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += size;

	netअगर_rx(skb);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hdlcdev_ops = अणु
	.nकरो_खोलो       = hdlcdev_खोलो,
	.nकरो_stop       = hdlcdev_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = hdlcdev_ioctl,
	.nकरो_tx_समयout = hdlcdev_tx_समयout,
पूर्ण;

/**
 * hdlcdev_init - called by device driver when adding device instance
 * @info: poपूर्णांकer to device instance inक्रमmation
 *
 * Do generic HDLC initialization.
 *
 * Return: 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_init(काष्ठा slgt_info *info)
अणु
	पूर्णांक rc;
	काष्ठा net_device *dev;
	hdlc_device *hdlc;

	/* allocate and initialize network and HDLC layer objects */

	dev = alloc_hdlcdev(info);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s hdlc device alloc failure\n", info->device_name);
		वापस -ENOMEM;
	पूर्ण

	/* क्रम network layer reporting purposes only */
	dev->mem_start = info->phys_reg_addr;
	dev->mem_end   = info->phys_reg_addr + SLGT_REG_SIZE - 1;
	dev->irq       = info->irq_level;

	/* network layer callbacks and settings */
	dev->netdev_ops	    = &hdlcdev_ops;
	dev->watchकरोg_समयo = 10 * HZ;
	dev->tx_queue_len   = 50;

	/* generic HDLC layer callbacks and settings */
	hdlc         = dev_to_hdlc(dev);
	hdlc->attach = hdlcdev_attach;
	hdlc->xmit   = hdlcdev_xmit;

	/* रेजिस्टर objects with HDLC layer */
	rc = रेजिस्टर_hdlc_device(dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "%s:unable to register hdlc device\n",__खाता__);
		मुक्त_netdev(dev);
		वापस rc;
	पूर्ण

	info->netdev = dev;
	वापस 0;
पूर्ण

/**
 * hdlcdev_निकास - called by device driver when removing device instance
 * @info: poपूर्णांकer to device instance inक्रमmation
 *
 * Do generic HDLC cleanup.
 */
अटल व्योम hdlcdev_निकास(काष्ठा slgt_info *info)
अणु
	unरेजिस्टर_hdlc_device(info->netdev);
	मुक्त_netdev(info->netdev);
	info->netdev = शून्य;
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_HDLC */

/*
 * get async data from rx DMA buffers
 */
अटल व्योम rx_async(काष्ठा slgt_info *info)
अणु
 	काष्ठा mgsl_icount *icount = &info->icount;
	अचिन्हित पूर्णांक start, end;
	अचिन्हित अक्षर *p;
	अचिन्हित अक्षर status;
	काष्ठा slgt_desc *bufs = info->rbufs;
	पूर्णांक i, count;
	पूर्णांक अक्षरs = 0;
	पूर्णांक stat;
	अचिन्हित अक्षर ch;

	start = end = info->rbuf_current;

	जबतक(desc_complete(bufs[end])) अणु
		count = desc_count(bufs[end]) - info->rbuf_index;
		p     = bufs[end].buf + info->rbuf_index;

		DBGISR(("%s rx_async count=%d\n", info->device_name, count));
		DBGDATA(info, p, count, "rx");

		क्रम(i=0 ; i < count; i+=2, p+=2) अणु
			ch = *p;
			icount->rx++;

			stat = 0;

			status = *(p + 1) & (BIT1 + BIT0);
			अगर (status) अणु
				अगर (status & BIT1)
					icount->parity++;
				अन्यथा अगर (status & BIT0)
					icount->frame++;
				/* discard अक्षर अगर tty control flags say so */
				अगर (status & info->ignore_status_mask)
					जारी;
				अगर (status & BIT1)
					stat = TTY_PARITY;
				अन्यथा अगर (status & BIT0)
					stat = TTY_FRAME;
			पूर्ण
			tty_insert_flip_अक्षर(&info->port, ch, stat);
			अक्षरs++;
		पूर्ण

		अगर (i < count) अणु
			/* receive buffer not completed */
			info->rbuf_index += i;
			mod_समयr(&info->rx_समयr, jअगरfies + 1);
			अवरोध;
		पूर्ण

		info->rbuf_index = 0;
		मुक्त_rbufs(info, end, end);

		अगर (++end == info->rbuf_count)
			end = 0;

		/* अगर entire list searched then no frame available */
		अगर (end == start)
			अवरोध;
	पूर्ण

	अगर (अक्षरs)
		tty_flip_buffer_push(&info->port);
पूर्ण

/*
 * वापस next bottom half action to perक्रमm
 */
अटल पूर्णांक bh_action(काष्ठा slgt_info *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&info->lock,flags);

	अगर (info->pending_bh & BH_RECEIVE) अणु
		info->pending_bh &= ~BH_RECEIVE;
		rc = BH_RECEIVE;
	पूर्ण अन्यथा अगर (info->pending_bh & BH_TRANSMIT) अणु
		info->pending_bh &= ~BH_TRANSMIT;
		rc = BH_TRANSMIT;
	पूर्ण अन्यथा अगर (info->pending_bh & BH_STATUS) अणु
		info->pending_bh &= ~BH_STATUS;
		rc = BH_STATUS;
	पूर्ण अन्यथा अणु
		/* Mark BH routine as complete */
		info->bh_running = false;
		info->bh_requested = false;
		rc = 0;
	पूर्ण

	spin_unlock_irqrestore(&info->lock,flags);

	वापस rc;
पूर्ण

/*
 * perक्रमm bottom half processing
 */
अटल व्योम bh_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा slgt_info *info = container_of(work, काष्ठा slgt_info, task);
	पूर्णांक action;

	info->bh_running = true;

	जबतक((action = bh_action(info))) अणु
		चयन (action) अणु
		हाल BH_RECEIVE:
			DBGBH(("%s bh receive\n", info->device_name));
			चयन(info->params.mode) अणु
			हाल MGSL_MODE_ASYNC:
				rx_async(info);
				अवरोध;
			हाल MGSL_MODE_HDLC:
				जबतक(rx_get_frame(info));
				अवरोध;
			हाल MGSL_MODE_RAW:
			हाल MGSL_MODE_MONOSYNC:
			हाल MGSL_MODE_BISYNC:
			हाल MGSL_MODE_XSYNC:
				जबतक(rx_get_buf(info));
				अवरोध;
			पूर्ण
			/* restart receiver अगर rx DMA buffers exhausted */
			अगर (info->rx_restart)
				rx_start(info);
			अवरोध;
		हाल BH_TRANSMIT:
			bh_transmit(info);
			अवरोध;
		हाल BH_STATUS:
			DBGBH(("%s bh status\n", info->device_name));
			info->ri_chkcount = 0;
			info->dsr_chkcount = 0;
			info->dcd_chkcount = 0;
			info->cts_chkcount = 0;
			अवरोध;
		शेष:
			DBGBH(("%s unknown action\n", info->device_name));
			अवरोध;
		पूर्ण
	पूर्ण
	DBGBH(("%s bh_handler exit\n", info->device_name));
पूर्ण

अटल व्योम bh_transmit(काष्ठा slgt_info *info)
अणु
	काष्ठा tty_काष्ठा *tty = info->port.tty;

	DBGBH(("%s bh_transmit\n", info->device_name));
	अगर (tty)
		tty_wakeup(tty);
पूर्ण

अटल व्योम dsr_change(काष्ठा slgt_info *info, अचिन्हित लघु status)
अणु
	अगर (status & BIT3) अणु
		info->संकेतs |= SerialSignal_DSR;
		info->input_संकेत_events.dsr_up++;
	पूर्ण अन्यथा अणु
		info->संकेतs &= ~SerialSignal_DSR;
		info->input_संकेत_events.dsr_करोwn++;
	पूर्ण
	DBGISR(("dsr_change %s signals=%04X\n", info->device_name, info->संकेतs));
	अगर ((info->dsr_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) अणु
		slgt_irq_off(info, IRQ_DSR);
		वापस;
	पूर्ण
	info->icount.dsr++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;
पूर्ण

अटल व्योम cts_change(काष्ठा slgt_info *info, अचिन्हित लघु status)
अणु
	अगर (status & BIT2) अणु
		info->संकेतs |= SerialSignal_CTS;
		info->input_संकेत_events.cts_up++;
	पूर्ण अन्यथा अणु
		info->संकेतs &= ~SerialSignal_CTS;
		info->input_संकेत_events.cts_करोwn++;
	पूर्ण
	DBGISR(("cts_change %s signals=%04X\n", info->device_name, info->संकेतs));
	अगर ((info->cts_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) अणु
		slgt_irq_off(info, IRQ_CTS);
		वापस;
	पूर्ण
	info->icount.cts++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;

	अगर (tty_port_cts_enabled(&info->port)) अणु
		अगर (info->port.tty) अणु
			अगर (info->port.tty->hw_stopped) अणु
				अगर (info->संकेतs & SerialSignal_CTS) अणु
		 			info->port.tty->hw_stopped = 0;
					info->pending_bh |= BH_TRANSMIT;
					वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!(info->संकेतs & SerialSignal_CTS))
		 			info->port.tty->hw_stopped = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dcd_change(काष्ठा slgt_info *info, अचिन्हित लघु status)
अणु
	अगर (status & BIT1) अणु
		info->संकेतs |= SerialSignal_DCD;
		info->input_संकेत_events.dcd_up++;
	पूर्ण अन्यथा अणु
		info->संकेतs &= ~SerialSignal_DCD;
		info->input_संकेत_events.dcd_करोwn++;
	पूर्ण
	DBGISR(("dcd_change %s signals=%04X\n", info->device_name, info->संकेतs));
	अगर ((info->dcd_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) अणु
		slgt_irq_off(info, IRQ_DCD);
		वापस;
	पूर्ण
	info->icount.dcd++;
#अगर SYNCLINK_GENERIC_HDLC
	अगर (info->netcount) अणु
		अगर (info->संकेतs & SerialSignal_DCD)
			netअगर_carrier_on(info->netdev);
		अन्यथा
			netअगर_carrier_off(info->netdev);
	पूर्ण
#पूर्ण_अगर
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;

	अगर (tty_port_check_carrier(&info->port)) अणु
		अगर (info->संकेतs & SerialSignal_DCD)
			wake_up_पूर्णांकerruptible(&info->port.खोलो_रुको);
		अन्यथा अणु
			अगर (info->port.tty)
				tty_hangup(info->port.tty);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ri_change(काष्ठा slgt_info *info, अचिन्हित लघु status)
अणु
	अगर (status & BIT0) अणु
		info->संकेतs |= SerialSignal_RI;
		info->input_संकेत_events.ri_up++;
	पूर्ण अन्यथा अणु
		info->संकेतs &= ~SerialSignal_RI;
		info->input_संकेत_events.ri_करोwn++;
	पूर्ण
	DBGISR(("ri_change %s signals=%04X\n", info->device_name, info->संकेतs));
	अगर ((info->ri_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) अणु
		slgt_irq_off(info, IRQ_RI);
		वापस;
	पूर्ण
	info->icount.rng++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;
पूर्ण

अटल व्योम isr_rxdata(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक count = info->rbuf_fill_count;
	अचिन्हित पूर्णांक i = info->rbuf_fill_index;
	अचिन्हित लघु reg;

	जबतक (rd_reg16(info, SSR) & IRQ_RXDATA) अणु
		reg = rd_reg16(info, RDR);
		DBGISR(("isr_rxdata %s RDR=%04X\n", info->device_name, reg));
		अगर (desc_complete(info->rbufs[i])) अणु
			/* all buffers full */
			rx_stop(info);
			info->rx_restart = true;
			जारी;
		पूर्ण
		info->rbufs[i].buf[count++] = (अचिन्हित अक्षर)reg;
		/* async mode saves status byte to buffer क्रम each data byte */
		अगर (info->params.mode == MGSL_MODE_ASYNC)
			info->rbufs[i].buf[count++] = (अचिन्हित अक्षर)(reg >> 8);
		अगर (count == info->rbuf_fill_level || (reg & BIT10)) अणु
			/* buffer full or end of frame */
			set_desc_count(info->rbufs[i], count);
			set_desc_status(info->rbufs[i], BIT15 | (reg >> 8));
			info->rbuf_fill_count = count = 0;
			अगर (++i == info->rbuf_count)
				i = 0;
			info->pending_bh |= BH_RECEIVE;
		पूर्ण
	पूर्ण

	info->rbuf_fill_index = i;
	info->rbuf_fill_count = count;
पूर्ण

अटल व्योम isr_serial(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु status = rd_reg16(info, SSR);

	DBGISR(("%s isr_serial status=%04X\n", info->device_name, status));

	wr_reg16(info, SSR, status); /* clear pending */

	info->irq_occurred = true;

	अगर (info->params.mode == MGSL_MODE_ASYNC) अणु
		अगर (status & IRQ_TXIDLE) अणु
			अगर (info->tx_active)
				isr_txeom(info, status);
		पूर्ण
		अगर (info->rx_pio && (status & IRQ_RXDATA))
			isr_rxdata(info);
		अगर ((status & IRQ_RXBREAK) && (status & RXBREAK)) अणु
			info->icount.brk++;
			/* process अवरोध detection अगर tty control allows */
			अगर (info->port.tty) अणु
				अगर (!(status & info->ignore_status_mask)) अणु
					अगर (info->पढ़ो_status_mask & MASK_BREAK) अणु
						tty_insert_flip_अक्षर(&info->port, 0, TTY_BREAK);
						अगर (info->port.flags & ASYNC_SAK)
							करो_SAK(info->port.tty);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (status & (IRQ_TXIDLE + IRQ_TXUNDER))
			isr_txeom(info, status);
		अगर (info->rx_pio && (status & IRQ_RXDATA))
			isr_rxdata(info);
		अगर (status & IRQ_RXIDLE) अणु
			अगर (status & RXIDLE)
				info->icount.rxidle++;
			अन्यथा
				info->icount.निकासhunt++;
			wake_up_पूर्णांकerruptible(&info->event_रुको_q);
		पूर्ण

		अगर (status & IRQ_RXOVER)
			rx_start(info);
	पूर्ण

	अगर (status & IRQ_DSR)
		dsr_change(info, status);
	अगर (status & IRQ_CTS)
		cts_change(info, status);
	अगर (status & IRQ_DCD)
		dcd_change(info, status);
	अगर (status & IRQ_RI)
		ri_change(info, status);
पूर्ण

अटल व्योम isr_rdma(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक status = rd_reg32(info, RDCSR);

	DBGISR(("%s isr_rdma status=%08x\n", info->device_name, status));

	/* RDCSR (rx DMA control/status)
	 *
	 * 31..07  reserved
	 * 06      save status byte to DMA buffer
	 * 05      error
	 * 04      eol (end of list)
	 * 03      eob (end of buffer)
	 * 02      IRQ enable
	 * 01      reset
	 * 00      enable
	 */
	wr_reg32(info, RDCSR, status);	/* clear pending */

	अगर (status & (BIT5 + BIT4)) अणु
		DBGISR(("%s isr_rdma rx_restart=1\n", info->device_name));
		info->rx_restart = true;
	पूर्ण
	info->pending_bh |= BH_RECEIVE;
पूर्ण

अटल व्योम isr_tdma(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक status = rd_reg32(info, TDCSR);

	DBGISR(("%s isr_tdma status=%08x\n", info->device_name, status));

	/* TDCSR (tx DMA control/status)
	 *
	 * 31..06  reserved
	 * 05      error
	 * 04      eol (end of list)
	 * 03      eob (end of buffer)
	 * 02      IRQ enable
	 * 01      reset
	 * 00      enable
	 */
	wr_reg32(info, TDCSR, status);	/* clear pending */

	अगर (status & (BIT5 + BIT4 + BIT3)) अणु
		// another transmit buffer has completed
		// run bottom half to get more send data from user
		info->pending_bh |= BH_TRANSMIT;
	पूर्ण
पूर्ण

/*
 * वापस true अगर there are unsent tx DMA buffers, otherwise false
 *
 * अगर there are unsent buffers then info->tbuf_start
 * is set to index of first unsent buffer
 */
अटल bool unsent_tbufs(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i = info->tbuf_current;
	bool rc = false;

	/*
	 * search backwards from last loaded buffer (precedes tbuf_current)
	 * क्रम first unsent buffer (desc_count > 0)
	 */

	करो अणु
		अगर (i)
			i--;
		अन्यथा
			i = info->tbuf_count - 1;
		अगर (!desc_count(info->tbufs[i]))
			अवरोध;
		info->tbuf_start = i;
		rc = true;
	पूर्ण जबतक (i != info->tbuf_current);

	वापस rc;
पूर्ण

अटल व्योम isr_txeom(काष्ठा slgt_info *info, अचिन्हित लघु status)
अणु
	DBGISR(("%s txeom status=%04x\n", info->device_name, status));

	slgt_irq_off(info, IRQ_TXDATA + IRQ_TXIDLE + IRQ_TXUNDER);
	tdma_reset(info);
	अगर (status & IRQ_TXUNDER) अणु
		अचिन्हित लघु val = rd_reg16(info, TCR);
		wr_reg16(info, TCR, (अचिन्हित लघु)(val | BIT2)); /* set reset bit */
		wr_reg16(info, TCR, val); /* clear reset bit */
	पूर्ण

	अगर (info->tx_active) अणु
		अगर (info->params.mode != MGSL_MODE_ASYNC) अणु
			अगर (status & IRQ_TXUNDER)
				info->icount.txunder++;
			अन्यथा अगर (status & IRQ_TXIDLE)
				info->icount.txok++;
		पूर्ण

		अगर (unsent_tbufs(info)) अणु
			tx_start(info);
			update_tx_समयr(info);
			वापस;
		पूर्ण
		info->tx_active = false;

		del_समयr(&info->tx_समयr);

		अगर (info->params.mode != MGSL_MODE_ASYNC && info->drop_rts_on_tx_करोne) अणु
			info->संकेतs &= ~SerialSignal_RTS;
			info->drop_rts_on_tx_करोne = false;
			set_संकेतs(info);
		पूर्ण

#अगर SYNCLINK_GENERIC_HDLC
		अगर (info->netcount)
			hdlcdev_tx_करोne(info);
		अन्यथा
#पूर्ण_अगर
		अणु
			अगर (info->port.tty && (info->port.tty->stopped || info->port.tty->hw_stopped)) अणु
				tx_stop(info);
				वापस;
			पूर्ण
			info->pending_bh |= BH_TRANSMIT;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम isr_gpio(काष्ठा slgt_info *info, अचिन्हित पूर्णांक changed, अचिन्हित पूर्णांक state)
अणु
	काष्ठा cond_रुको *w, *prev;

	/* wake processes रुकोing क्रम specअगरic transitions */
	क्रम (w = info->gpio_रुको_q, prev = शून्य ; w != शून्य ; w = w->next) अणु
		अगर (w->data & changed) अणु
			w->data = state;
			wake_up_पूर्णांकerruptible(&w->q);
			अगर (prev != शून्य)
				prev->next = w->next;
			अन्यथा
				info->gpio_रुको_q = w->next;
		पूर्ण अन्यथा
			prev = w;
	पूर्ण
पूर्ण

/* पूर्णांकerrupt service routine
 *
 * 	irq	पूर्णांकerrupt number
 * 	dev_id	device ID supplied during पूर्णांकerrupt registration
 */
अटल irqवापस_t slgt_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा slgt_info *info = dev_id;
	अचिन्हित पूर्णांक gsr;
	अचिन्हित पूर्णांक i;

	DBGISR(("slgt_interrupt irq=%d entry\n", info->irq_level));

	जबतक((gsr = rd_reg32(info, GSR) & 0xffffff00)) अणु
		DBGISR(("%s gsr=%08x\n", info->device_name, gsr));
		info->irq_occurred = true;
		क्रम(i=0; i < info->port_count ; i++) अणु
			अगर (info->port_array[i] == शून्य)
				जारी;
			spin_lock(&info->port_array[i]->lock);
			अगर (gsr & (BIT8 << i))
				isr_serial(info->port_array[i]);
			अगर (gsr & (BIT16 << (i*2)))
				isr_rdma(info->port_array[i]);
			अगर (gsr & (BIT17 << (i*2)))
				isr_tdma(info->port_array[i]);
			spin_unlock(&info->port_array[i]->lock);
		पूर्ण
	पूर्ण

	अगर (info->gpio_present) अणु
		अचिन्हित पूर्णांक state;
		अचिन्हित पूर्णांक changed;
		spin_lock(&info->lock);
		जबतक ((changed = rd_reg32(info, IOSR)) != 0) अणु
			DBGISR(("%s iosr=%08x\n", info->device_name, changed));
			/* पढ़ो latched state of GPIO संकेतs */
			state = rd_reg32(info, IOVR);
			/* clear pending GPIO पूर्णांकerrupt bits */
			wr_reg32(info, IOSR, changed);
			क्रम (i=0 ; i < info->port_count ; i++) अणु
				अगर (info->port_array[i] != शून्य)
					isr_gpio(info->port_array[i], changed, state);
			पूर्ण
		पूर्ण
		spin_unlock(&info->lock);
	पूर्ण

	क्रम(i=0; i < info->port_count ; i++) अणु
		काष्ठा slgt_info *port = info->port_array[i];
		अगर (port == शून्य)
			जारी;
		spin_lock(&port->lock);
		अगर ((port->port.count || port->netcount) &&
		    port->pending_bh && !port->bh_running &&
		    !port->bh_requested) अणु
			DBGISR(("%s bh queued\n", port->device_name));
			schedule_work(&port->task);
			port->bh_requested = true;
		पूर्ण
		spin_unlock(&port->lock);
	पूर्ण

	DBGISR(("slgt_interrupt irq=%d exit\n", info->irq_level));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक startup(काष्ठा slgt_info *info)
अणु
	DBGINFO(("%s startup\n", info->device_name));

	अगर (tty_port_initialized(&info->port))
		वापस 0;

	अगर (!info->tx_buf) अणु
		info->tx_buf = kदो_स्मृति(info->max_frame_size, GFP_KERNEL);
		अगर (!info->tx_buf) अणु
			DBGERR(("%s can't allocate tx buffer\n", info->device_name));
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	info->pending_bh = 0;

	स_रखो(&info->icount, 0, माप(info->icount));

	/* program hardware क्रम current parameters */
	change_params(info);

	अगर (info->port.tty)
		clear_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 1);

	वापस 0;
पूर्ण

/*
 *  called by बंद() and hangup() to shutकरोwn hardware
 */
अटल व्योम shutकरोwn(काष्ठा slgt_info *info)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!tty_port_initialized(&info->port))
		वापस;

	DBGINFO(("%s shutdown\n", info->device_name));

	/* clear status रुको queue because status changes */
	/* can't happen after shutting करोwn the hardware */
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);

	del_समयr_sync(&info->tx_समयr);
	del_समयr_sync(&info->rx_समयr);

	kमुक्त(info->tx_buf);
	info->tx_buf = शून्य;

	spin_lock_irqsave(&info->lock,flags);

	tx_stop(info);
	rx_stop(info);

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);

 	अगर (!info->port.tty || info->port.tty->termios.c_cflag & HUPCL) अणु
		info->संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_संकेतs(info);
	पूर्ण

	flush_cond_रुको(&info->gpio_रुको_q);

	spin_unlock_irqrestore(&info->lock,flags);

	अगर (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 0);
पूर्ण

अटल व्योम program_hw(काष्ठा slgt_info *info)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock,flags);

	rx_stop(info);
	tx_stop(info);

	अगर (info->params.mode != MGSL_MODE_ASYNC ||
	    info->netcount)
		sync_mode(info);
	अन्यथा
		async_mode(info);

	set_संकेतs(info);

	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;

	slgt_irq_on(info, IRQ_DCD | IRQ_CTS | IRQ_DSR | IRQ_RI);
	get_संकेतs(info);

	अगर (info->netcount ||
	    (info->port.tty && info->port.tty->termios.c_cflag & CREAD))
		rx_start(info);

	spin_unlock_irqrestore(&info->lock,flags);
पूर्ण

/*
 * reconfigure adapter based on new parameters
 */
अटल व्योम change_params(काष्ठा slgt_info *info)
अणु
	अचिन्हित cflag;
	पूर्णांक bits_per_अक्षर;

	अगर (!info->port.tty)
		वापस;
	DBGINFO(("%s change_params\n", info->device_name));

	cflag = info->port.tty->termios.c_cflag;

	/* अगर B0 rate (hangup) specअगरied then negate RTS and DTR */
	/* otherwise निश्चित RTS and DTR */
 	अगर (cflag & CBAUD)
		info->संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	अन्यथा
		info->संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);

	/* byte size and parity */

	चयन (cflag & CSIZE) अणु
	हाल CS5: info->params.data_bits = 5; अवरोध;
	हाल CS6: info->params.data_bits = 6; अवरोध;
	हाल CS7: info->params.data_bits = 7; अवरोध;
	हाल CS8: info->params.data_bits = 8; अवरोध;
	शेष:  info->params.data_bits = 7; अवरोध;
	पूर्ण

	info->params.stop_bits = (cflag & CSTOPB) ? 2 : 1;

	अगर (cflag & PARENB)
		info->params.parity = (cflag & PARODD) ? ASYNC_PARITY_ODD : ASYNC_PARITY_EVEN;
	अन्यथा
		info->params.parity = ASYNC_PARITY_NONE;

	/* calculate number of jअगरfies to transmit a full
	 * FIFO (32 bytes) at specअगरied data rate
	 */
	bits_per_अक्षर = info->params.data_bits +
			info->params.stop_bits + 1;

	info->params.data_rate = tty_get_baud_rate(info->port.tty);

	अगर (info->params.data_rate) अणु
		info->समयout = (32*HZ*bits_per_अक्षर) /
				info->params.data_rate;
	पूर्ण
	info->समयout += HZ/50;		/* Add .02 seconds of slop */

	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);

	/* process tty input control flags */

	info->पढ़ो_status_mask = IRQ_RXOVER;
	अगर (I_INPCK(info->port.tty))
		info->पढ़ो_status_mask |= MASK_PARITY | MASK_FRAMING;
	अगर (I_BRKINT(info->port.tty) || I_PARMRK(info->port.tty))
		info->पढ़ो_status_mask |= MASK_BREAK;
	अगर (I_IGNPAR(info->port.tty))
		info->ignore_status_mask |= MASK_PARITY | MASK_FRAMING;
	अगर (I_IGNBRK(info->port.tty)) अणु
		info->ignore_status_mask |= MASK_BREAK;
		/* If ignoring parity and अवरोध indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		अगर (I_IGNPAR(info->port.tty))
			info->ignore_status_mask |= MASK_OVERRUN;
	पूर्ण

	program_hw(info);
पूर्ण

अटल पूर्णांक get_stats(काष्ठा slgt_info *info, काष्ठा mgsl_icount __user *user_icount)
अणु
	DBGINFO(("%s get_stats\n",  info->device_name));
	अगर (!user_icount) अणु
		स_रखो(&info->icount, 0, माप(info->icount));
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(user_icount, &info->icount, माप(काष्ठा mgsl_icount)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_params(काष्ठा slgt_info *info, MGSL_PARAMS __user *user_params)
अणु
	DBGINFO(("%s get_params\n", info->device_name));
	अगर (copy_to_user(user_params, &info->params, माप(MGSL_PARAMS)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक set_params(काष्ठा slgt_info *info, MGSL_PARAMS __user *new_params)
अणु
 	अचिन्हित दीर्घ flags;
	MGSL_PARAMS पंचांगp_params;

	DBGINFO(("%s set_params\n", info->device_name));
	अगर (copy_from_user(&पंचांगp_params, new_params, माप(MGSL_PARAMS)))
		वापस -EFAULT;

	spin_lock_irqsave(&info->lock, flags);
	अगर (पंचांगp_params.mode == MGSL_MODE_BASE_CLOCK)
		info->base_घड़ी = पंचांगp_params.घड़ी_speed;
	अन्यथा
		स_नकल(&info->params, &पंचांगp_params, माप(MGSL_PARAMS));
	spin_unlock_irqrestore(&info->lock, flags);

	program_hw(info);

	वापस 0;
पूर्ण

अटल पूर्णांक get_txidle(काष्ठा slgt_info *info, पूर्णांक __user *idle_mode)
अणु
	DBGINFO(("%s get_txidle=%d\n", info->device_name, info->idle_mode));
	अगर (put_user(info->idle_mode, idle_mode))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक set_txidle(काष्ठा slgt_info *info, पूर्णांक idle_mode)
अणु
 	अचिन्हित दीर्घ flags;
	DBGINFO(("%s set_txidle(%d)\n", info->device_name, idle_mode));
	spin_lock_irqsave(&info->lock,flags);
	info->idle_mode = idle_mode;
	अगर (info->params.mode != MGSL_MODE_ASYNC)
		tx_set_idle(info);
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

अटल पूर्णांक tx_enable(काष्ठा slgt_info *info, पूर्णांक enable)
अणु
 	अचिन्हित दीर्घ flags;
	DBGINFO(("%s tx_enable(%d)\n", info->device_name, enable));
	spin_lock_irqsave(&info->lock,flags);
	अगर (enable) अणु
		अगर (!info->tx_enabled)
			tx_start(info);
	पूर्ण अन्यथा अणु
		अगर (info->tx_enabled)
			tx_stop(info);
	पूर्ण
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

/*
 * पात transmit HDLC frame
 */
अटल पूर्णांक tx_पात(काष्ठा slgt_info *info)
अणु
 	अचिन्हित दीर्घ flags;
	DBGINFO(("%s tx_abort\n", info->device_name));
	spin_lock_irqsave(&info->lock,flags);
	tdma_reset(info);
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

अटल पूर्णांक rx_enable(काष्ठा slgt_info *info, पूर्णांक enable)
अणु
 	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक rbuf_fill_level;
	DBGINFO(("%s rx_enable(%08x)\n", info->device_name, enable));
	spin_lock_irqsave(&info->lock,flags);
	/*
	 * enable[31..16] = receive DMA buffer fill level
	 * 0 = noop (leave fill level unchanged)
	 * fill level must be multiple of 4 and <= buffer size
	 */
	rbuf_fill_level = ((अचिन्हित पूर्णांक)enable) >> 16;
	अगर (rbuf_fill_level) अणु
		अगर ((rbuf_fill_level > DMAबफ_मानE) || (rbuf_fill_level % 4)) अणु
			spin_unlock_irqrestore(&info->lock, flags);
			वापस -EINVAL;
		पूर्ण
		info->rbuf_fill_level = rbuf_fill_level;
		अगर (rbuf_fill_level < 128)
			info->rx_pio = 1; /* PIO mode */
		अन्यथा
			info->rx_pio = 0; /* DMA mode */
		rx_stop(info); /* restart receiver to use new fill level */
	पूर्ण

	/*
	 * enable[1..0] = receiver enable command
	 * 0 = disable
	 * 1 = enable
	 * 2 = enable or क्रमce hunt mode अगर alपढ़ोy enabled
	 */
	enable &= 3;
	अगर (enable) अणु
		अगर (!info->rx_enabled)
			rx_start(info);
		अन्यथा अगर (enable == 2) अणु
			/* क्रमce hunt mode (ग_लिखो 1 to RCR[3]) */
			wr_reg16(info, RCR, rd_reg16(info, RCR) | BIT3);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (info->rx_enabled)
			rx_stop(info);
	पूर्ण
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

/*
 *  रुको क्रम specअगरied event to occur
 */
अटल पूर्णांक रुको_mgsl_event(काष्ठा slgt_info *info, पूर्णांक __user *mask_ptr)
अणु
 	अचिन्हित दीर्घ flags;
	पूर्णांक s;
	पूर्णांक rc=0;
	काष्ठा mgsl_icount cprev, cnow;
	पूर्णांक events;
	पूर्णांक mask;
	काष्ठा	_input_संकेत_events oldsigs, newsigs;
	DECLARE_WAITQUEUE(रुको, current);

	अगर (get_user(mask, mask_ptr))
		वापस -EFAULT;

	DBGINFO(("%s wait_mgsl_event(%d)\n", info->device_name, mask));

	spin_lock_irqsave(&info->lock,flags);

	/* वापस immediately अगर state matches requested events */
	get_संकेतs(info);
	s = info->संकेतs;

	events = mask &
		( ((s & SerialSignal_DSR) ? MgslEvent_DsrActive:MgslEvent_DsrInactive) +
 		  ((s & SerialSignal_DCD) ? MgslEvent_DcdActive:MgslEvent_DcdInactive) +
		  ((s & SerialSignal_CTS) ? MgslEvent_CtsActive:MgslEvent_CtsInactive) +
		  ((s & SerialSignal_RI)  ? MgslEvent_RiActive :MgslEvent_RiInactive) );
	अगर (events) अणु
		spin_unlock_irqrestore(&info->lock,flags);
		जाओ निकास;
	पूर्ण

	/* save current irq counts */
	cprev = info->icount;
	oldsigs = info->input_संकेत_events;

	/* enable hunt and idle irqs अगर needed */
	अगर (mask & (MgslEvent_ExitHuntMode+MgslEvent_IdleReceived)) अणु
		अचिन्हित लघु val = rd_reg16(info, SCR);
		अगर (!(val & IRQ_RXIDLE))
			wr_reg16(info, SCR, (अचिन्हित लघु)(val | IRQ_RXIDLE));
	पूर्ण

	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&info->event_रुको_q, &रुको);

	spin_unlock_irqrestore(&info->lock,flags);

	क्रम(;;) अणु
		schedule();
		अगर (संकेत_pending(current)) अणु
			rc = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/* get current irq counts */
		spin_lock_irqsave(&info->lock,flags);
		cnow = info->icount;
		newsigs = info->input_संकेत_events;
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&info->lock,flags);

		/* अगर no change, रुको पातed क्रम some reason */
		अगर (newsigs.dsr_up   == oldsigs.dsr_up   &&
		    newsigs.dsr_करोwn == oldsigs.dsr_करोwn &&
		    newsigs.dcd_up   == oldsigs.dcd_up   &&
		    newsigs.dcd_करोwn == oldsigs.dcd_करोwn &&
		    newsigs.cts_up   == oldsigs.cts_up   &&
		    newsigs.cts_करोwn == oldsigs.cts_करोwn &&
		    newsigs.ri_up    == oldsigs.ri_up    &&
		    newsigs.ri_करोwn  == oldsigs.ri_करोwn  &&
		    cnow.निकासhunt    == cprev.निकासhunt   &&
		    cnow.rxidle      == cprev.rxidle) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण

		events = mask &
			( (newsigs.dsr_up   != oldsigs.dsr_up   ? MgslEvent_DsrActive:0)   +
			  (newsigs.dsr_करोwn != oldsigs.dsr_करोwn ? MgslEvent_DsrInactive:0) +
			  (newsigs.dcd_up   != oldsigs.dcd_up   ? MgslEvent_DcdActive:0)   +
			  (newsigs.dcd_करोwn != oldsigs.dcd_करोwn ? MgslEvent_DcdInactive:0) +
			  (newsigs.cts_up   != oldsigs.cts_up   ? MgslEvent_CtsActive:0)   +
			  (newsigs.cts_करोwn != oldsigs.cts_करोwn ? MgslEvent_CtsInactive:0) +
			  (newsigs.ri_up    != oldsigs.ri_up    ? MgslEvent_RiActive:0)    +
			  (newsigs.ri_करोwn  != oldsigs.ri_करोwn  ? MgslEvent_RiInactive:0)  +
			  (cnow.निकासhunt    != cprev.निकासhunt   ? MgslEvent_ExitHuntMode:0) +
			  (cnow.rxidle      != cprev.rxidle     ? MgslEvent_IdleReceived:0) );
		अगर (events)
			अवरोध;

		cprev = cnow;
		oldsigs = newsigs;
	पूर्ण

	हटाओ_रुको_queue(&info->event_रुको_q, &रुको);
	set_current_state(TASK_RUNNING);


	अगर (mask & (MgslEvent_ExitHuntMode + MgslEvent_IdleReceived)) अणु
		spin_lock_irqsave(&info->lock,flags);
		अगर (!रुकोqueue_active(&info->event_रुको_q)) अणु
			/* disable enable निकास hunt mode/idle rcvd IRQs */
			wr_reg16(info, SCR,
				(अचिन्हित लघु)(rd_reg16(info, SCR) & ~IRQ_RXIDLE));
		पूर्ण
		spin_unlock_irqrestore(&info->lock,flags);
	पूर्ण
निकास:
	अगर (rc == 0)
		rc = put_user(events, mask_ptr);
	वापस rc;
पूर्ण

अटल पूर्णांक get_पूर्णांकerface(काष्ठा slgt_info *info, पूर्णांक __user *अगर_mode)
अणु
	DBGINFO(("%s get_interface=%x\n", info->device_name, info->अगर_mode));
	अगर (put_user(info->अगर_mode, अगर_mode))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक set_पूर्णांकerface(काष्ठा slgt_info *info, पूर्णांक अगर_mode)
अणु
 	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;

	DBGINFO(("%s set_interface=%x)\n", info->device_name, अगर_mode));
	spin_lock_irqsave(&info->lock,flags);
	info->अगर_mode = अगर_mode;

	msc_set_vcr(info);

	/* TCR (tx control) 07  1=RTS driver control */
	val = rd_reg16(info, TCR);
	अगर (info->अगर_mode & MGSL_INTERFACE_RTS_EN)
		val |= BIT7;
	अन्यथा
		val &= ~BIT7;
	wr_reg16(info, TCR, val);

	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

अटल पूर्णांक get_xsync(काष्ठा slgt_info *info, पूर्णांक __user *xsync)
अणु
	DBGINFO(("%s get_xsync=%x\n", info->device_name, info->xsync));
	अगर (put_user(info->xsync, xsync))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * set extended sync pattern (1 to 4 bytes) क्रम extended sync mode
 *
 * sync pattern is contained in least signअगरicant bytes of value
 * most signअगरicant byte of sync pattern is oldest (1st sent/detected)
 */
अटल पूर्णांक set_xsync(काष्ठा slgt_info *info, पूर्णांक xsync)
अणु
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s set_xsync=%x)\n", info->device_name, xsync));
	spin_lock_irqsave(&info->lock, flags);
	info->xsync = xsync;
	wr_reg32(info, XSR, xsync);
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक get_xctrl(काष्ठा slgt_info *info, पूर्णांक __user *xctrl)
अणु
	DBGINFO(("%s get_xctrl=%x\n", info->device_name, info->xctrl));
	अगर (put_user(info->xctrl, xctrl))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * set extended control options
 *
 * xctrl[31:19] reserved, must be zero
 * xctrl[18:17] extended sync pattern length in bytes
 *              00 = 1 byte  in xsr[7:0]
 *              01 = 2 bytes in xsr[15:0]
 *              10 = 3 bytes in xsr[23:0]
 *              11 = 4 bytes in xsr[31:0]
 * xctrl[16]    1 = enable terminal count, 0=disabled
 * xctrl[15:0]  receive terminal count क्रम fixed length packets
 *              value is count minus one (0 = 1 byte packet)
 *              when terminal count is reached, receiver
 *              स्वतःmatically वापसs to hunt mode and receive
 *              FIFO contents are flushed to DMA buffers with
 *              end of frame (खातापूर्ण) status
 */
अटल पूर्णांक set_xctrl(काष्ठा slgt_info *info, पूर्णांक xctrl)
अणु
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s set_xctrl=%x)\n", info->device_name, xctrl));
	spin_lock_irqsave(&info->lock, flags);
	info->xctrl = xctrl;
	wr_reg32(info, XCR, xctrl);
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

/*
 * set general purpose IO pin state and direction
 *
 * user_gpio fields:
 * state   each bit indicates a pin state
 * smask   set bit indicates pin state to set
 * dir     each bit indicates a pin direction (0=input, 1=output)
 * dmask   set bit indicates pin direction to set
 */
अटल पूर्णांक set_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *user_gpio)
अणु
 	अचिन्हित दीर्घ flags;
	काष्ठा gpio_desc gpio;
	__u32 data;

	अगर (!info->gpio_present)
		वापस -EINVAL;
	अगर (copy_from_user(&gpio, user_gpio, माप(gpio)))
		वापस -EFAULT;
	DBGINFO(("%s set_gpio state=%08x smask=%08x dir=%08x dmask=%08x\n",
		 info->device_name, gpio.state, gpio.smask,
		 gpio.dir, gpio.dmask));

	spin_lock_irqsave(&info->port_array[0]->lock, flags);
	अगर (gpio.dmask) अणु
		data = rd_reg32(info, IODR);
		data |= gpio.dmask & gpio.dir;
		data &= ~(gpio.dmask & ~gpio.dir);
		wr_reg32(info, IODR, data);
	पूर्ण
	अगर (gpio.smask) अणु
		data = rd_reg32(info, IOVR);
		data |= gpio.smask & gpio.state;
		data &= ~(gpio.smask & ~gpio.state);
		wr_reg32(info, IOVR, data);
	पूर्ण
	spin_unlock_irqrestore(&info->port_array[0]->lock, flags);

	वापस 0;
पूर्ण

/*
 * get general purpose IO pin state and direction
 */
अटल पूर्णांक get_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *user_gpio)
अणु
	काष्ठा gpio_desc gpio;
	अगर (!info->gpio_present)
		वापस -EINVAL;
	gpio.state = rd_reg32(info, IOVR);
	gpio.smask = 0xffffffff;
	gpio.dir   = rd_reg32(info, IODR);
	gpio.dmask = 0xffffffff;
	अगर (copy_to_user(user_gpio, &gpio, माप(gpio)))
		वापस -EFAULT;
	DBGINFO(("%s get_gpio state=%08x dir=%08x\n",
		 info->device_name, gpio.state, gpio.dir));
	वापस 0;
पूर्ण

/*
 * conditional रुको facility
 */
अटल व्योम init_cond_रुको(काष्ठा cond_रुको *w, अचिन्हित पूर्णांक data)
अणु
	init_रुकोqueue_head(&w->q);
	init_रुकोqueue_entry(&w->रुको, current);
	w->data = data;
पूर्ण

अटल व्योम add_cond_रुको(काष्ठा cond_रुको **head, काष्ठा cond_रुको *w)
अणु
	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&w->q, &w->रुको);
	w->next = *head;
	*head = w;
पूर्ण

अटल व्योम हटाओ_cond_रुको(काष्ठा cond_रुको **head, काष्ठा cond_रुको *cw)
अणु
	काष्ठा cond_रुको *w, *prev;
	हटाओ_रुको_queue(&cw->q, &cw->रुको);
	set_current_state(TASK_RUNNING);
	क्रम (w = *head, prev = शून्य ; w != शून्य ; prev = w, w = w->next) अणु
		अगर (w == cw) अणु
			अगर (prev != शून्य)
				prev->next = w->next;
			अन्यथा
				*head = w->next;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम flush_cond_रुको(काष्ठा cond_रुको **head)
अणु
	जबतक (*head != शून्य) अणु
		wake_up_पूर्णांकerruptible(&(*head)->q);
		*head = (*head)->next;
	पूर्ण
पूर्ण

/*
 * रुको क्रम general purpose I/O pin(s) to enter specअगरied state
 *
 * user_gpio fields:
 * state - bit indicates target pin state
 * smask - set bit indicates watched pin
 *
 * The रुको ends when at least one watched pin enters the specअगरied
 * state. When 0 (no error) is वापसed, user_gpio->state is set to the
 * state of all GPIO pins when the रुको ends.
 *
 * Note: Each pin may be a dedicated input, dedicated output, or
 * configurable input/output. The number and configuration of pins
 * varies with the specअगरic adapter model. Only input pins (dedicated
 * or configured) can be monitored with this function.
 */
अटल पूर्णांक रुको_gpio(काष्ठा slgt_info *info, काष्ठा gpio_desc __user *user_gpio)
अणु
 	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;
	काष्ठा gpio_desc gpio;
	काष्ठा cond_रुको रुको;
	u32 state;

	अगर (!info->gpio_present)
		वापस -EINVAL;
	अगर (copy_from_user(&gpio, user_gpio, माप(gpio)))
		वापस -EFAULT;
	DBGINFO(("%s wait_gpio() state=%08x smask=%08x\n",
		 info->device_name, gpio.state, gpio.smask));
	/* ignore output pins identअगरied by set IODR bit */
	अगर ((gpio.smask &= ~rd_reg32(info, IODR)) == 0)
		वापस -EINVAL;
	init_cond_रुको(&रुको, gpio.smask);

	spin_lock_irqsave(&info->port_array[0]->lock, flags);
	/* enable पूर्णांकerrupts क्रम watched pins */
	wr_reg32(info, IOER, rd_reg32(info, IOER) | gpio.smask);
	/* get current pin states */
	state = rd_reg32(info, IOVR);

	अगर (gpio.smask & ~(state ^ gpio.state)) अणु
		/* alपढ़ोy in target state */
		gpio.state = state;
	पूर्ण अन्यथा अणु
		/* रुको क्रम target state */
		add_cond_रुको(&info->gpio_रुको_q, &रुको);
		spin_unlock_irqrestore(&info->port_array[0]->lock, flags);
		schedule();
		अगर (संकेत_pending(current))
			rc = -ERESTARTSYS;
		अन्यथा
			gpio.state = रुको.data;
		spin_lock_irqsave(&info->port_array[0]->lock, flags);
		हटाओ_cond_रुको(&info->gpio_रुको_q, &रुको);
	पूर्ण

	/* disable all GPIO पूर्णांकerrupts अगर no रुकोing processes */
	अगर (info->gpio_रुको_q == शून्य)
		wr_reg32(info, IOER, 0);
	spin_unlock_irqrestore(&info->port_array[0]->lock, flags);

	अगर ((rc == 0) && copy_to_user(user_gpio, &gpio, माप(gpio)))
		rc = -EFAULT;
	वापस rc;
पूर्ण

अटल पूर्णांक modem_input_रुको(काष्ठा slgt_info *info,पूर्णांक arg)
अणु
 	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	काष्ठा mgsl_icount cprev, cnow;
	DECLARE_WAITQUEUE(रुको, current);

	/* save current irq counts */
	spin_lock_irqsave(&info->lock,flags);
	cprev = info->icount;
	add_रुको_queue(&info->status_event_रुको_q, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	spin_unlock_irqrestore(&info->lock,flags);

	क्रम(;;) अणु
		schedule();
		अगर (संकेत_pending(current)) अणु
			rc = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/* get new irq counts */
		spin_lock_irqsave(&info->lock,flags);
		cnow = info->icount;
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&info->lock,flags);

		/* अगर no change, रुको पातed क्रम some reason */
		अगर (cnow.rng == cprev.rng && cnow.dsr == cprev.dsr &&
		    cnow.dcd == cprev.dcd && cnow.cts == cprev.cts) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण

		/* check क्रम change in caller specअगरied modem input */
		अगर ((arg & TIOCM_RNG && cnow.rng != cprev.rng) ||
		    (arg & TIOCM_DSR && cnow.dsr != cprev.dsr) ||
		    (arg & TIOCM_CD  && cnow.dcd != cprev.dcd) ||
		    (arg & TIOCM_CTS && cnow.cts != cprev.cts)) अणु
			rc = 0;
			अवरोध;
		पूर्ण

		cprev = cnow;
	पूर्ण
	हटाओ_रुको_queue(&info->status_event_रुको_q, &रुको);
	set_current_state(TASK_RUNNING);
	वापस rc;
पूर्ण

/*
 *  वापस state of serial control and status संकेतs
 */
अटल पूर्णांक tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
	अचिन्हित पूर्णांक result;
 	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock,flags);
 	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock,flags);

	result = ((info->संकेतs & SerialSignal_RTS) ? TIOCM_RTS:0) +
		((info->संकेतs & SerialSignal_DTR) ? TIOCM_DTR:0) +
		((info->संकेतs & SerialSignal_DCD) ? TIOCM_CAR:0) +
		((info->संकेतs & SerialSignal_RI)  ? TIOCM_RNG:0) +
		((info->संकेतs & SerialSignal_DSR) ? TIOCM_DSR:0) +
		((info->संकेतs & SerialSignal_CTS) ? TIOCM_CTS:0);

	DBGINFO(("%s tiocmget value=%08X\n", info->device_name, result));
	वापस result;
पूर्ण

/*
 * set modem control संकेतs (DTR/RTS)
 *
 * 	cmd	संकेत command: TIOCMBIS = set bit TIOCMBIC = clear bit
 *		TIOCMSET = set/clear संकेत values
 * 	value	bit mask क्रम command
 */
अटल पूर्णांक tiocmset(काष्ठा tty_काष्ठा *tty,
		    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा slgt_info *info = tty->driver_data;
 	अचिन्हित दीर्घ flags;

	DBGINFO(("%s tiocmset(%x,%x)\n", info->device_name, set, clear));

	अगर (set & TIOCM_RTS)
		info->संकेतs |= SerialSignal_RTS;
	अगर (set & TIOCM_DTR)
		info->संकेतs |= SerialSignal_DTR;
	अगर (clear & TIOCM_RTS)
		info->संकेतs &= ~SerialSignal_RTS;
	अगर (clear & TIOCM_DTR)
		info->संकेतs &= ~SerialSignal_DTR;

	spin_lock_irqsave(&info->lock,flags);
	set_संकेतs(info);
	spin_unlock_irqrestore(&info->lock,flags);
	वापस 0;
पूर्ण

अटल पूर्णांक carrier_उठाओd(काष्ठा tty_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा slgt_info *info = container_of(port, काष्ठा slgt_info, port);

	spin_lock_irqsave(&info->lock,flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock,flags);
	वापस (info->संकेतs & SerialSignal_DCD) ? 1 : 0;
पूर्ण

अटल व्योम dtr_rts(काष्ठा tty_port *port, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा slgt_info *info = container_of(port, काष्ठा slgt_info, port);

	spin_lock_irqsave(&info->lock,flags);
	अगर (on)
		info->संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	अन्यथा
		info->संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
	set_संकेतs(info);
	spin_unlock_irqrestore(&info->lock,flags);
पूर्ण


/*
 *  block current process until the device is पढ़ोy to खोलो
 */
अटल पूर्णांक block_til_पढ़ोy(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp,
			   काष्ठा slgt_info *info)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक		retval;
	bool		करो_clocal = false;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		cd;
	काष्ठा tty_port *port = &info->port;

	DBGINFO(("%s block_til_ready\n", tty->driver->name));

	अगर (filp->f_flags & O_NONBLOCK || tty_io_error(tty)) अणु
		/* nonblock mode is set or port is not enabled */
		tty_port_set_active(port, 1);
		वापस 0;
	पूर्ण

	अगर (C_CLOCAL(tty))
		करो_clocal = true;

	/* Wait क्रम carrier detect and the line to become
	 * मुक्त (i.e., not in use by the callout).  While we are in
	 * this loop, port->count is dropped by one, so that
	 * बंद() knows when to मुक्त things.  We restore it upon
	 * निकास, either normal or abnormal.
	 */

	retval = 0;
	add_रुको_queue(&port->खोलो_रुको, &रुको);

	spin_lock_irqsave(&info->lock, flags);
	port->count--;
	spin_unlock_irqrestore(&info->lock, flags);
	port->blocked_खोलो++;

	जबतक (1) अणु
		अगर (C_BAUD(tty) && tty_port_initialized(port))
			tty_port_उठाओ_dtr_rts(port);

		set_current_state(TASK_INTERRUPTIBLE);

		अगर (tty_hung_up_p(filp) || !tty_port_initialized(port)) अणु
			retval = (port->flags & ASYNC_HUP_NOTIFY) ?
					-EAGAIN : -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cd = tty_port_carrier_उठाओd(port);
		अगर (करो_clocal || cd)
			अवरोध;

		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		DBGINFO(("%s block_til_ready wait\n", tty->driver->name));
		tty_unlock(tty);
		schedule();
		tty_lock(tty);
	पूर्ण

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&port->खोलो_रुको, &रुको);

	अगर (!tty_hung_up_p(filp))
		port->count++;
	port->blocked_खोलो--;

	अगर (!retval)
		tty_port_set_active(port, 1);

	DBGINFO(("%s block_til_ready ready, rc=%d\n", tty->driver->name, retval));
	वापस retval;
पूर्ण

/*
 * allocate buffers used क्रम calling line discipline receive_buf
 * directly in synchronous mode
 * note: add 5 bytes to max frame size to allow appending
 * 32-bit CRC and status byte when configured to करो so
 */
अटल पूर्णांक alloc_पंचांगp_rbuf(काष्ठा slgt_info *info)
अणु
	info->पंचांगp_rbuf = kदो_स्मृति(info->max_frame_size + 5, GFP_KERNEL);
	अगर (info->पंचांगp_rbuf == शून्य)
		वापस -ENOMEM;
	/* unused flag buffer to satisfy receive_buf calling पूर्णांकerface */
	info->flag_buf = kzalloc(info->max_frame_size + 5, GFP_KERNEL);
	अगर (!info->flag_buf) अणु
		kमुक्त(info->पंचांगp_rbuf);
		info->पंचांगp_rbuf = शून्य;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_पंचांगp_rbuf(काष्ठा slgt_info *info)
अणु
	kमुक्त(info->पंचांगp_rbuf);
	info->पंचांगp_rbuf = शून्य;
	kमुक्त(info->flag_buf);
	info->flag_buf = शून्य;
पूर्ण

/*
 * allocate DMA descriptor lists.
 */
अटल पूर्णांक alloc_desc(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक pbufs;

	/* allocate memory to hold descriptor lists */
	info->bufs = dma_alloc_coherent(&info->pdev->dev, DESC_LIST_SIZE,
					&info->bufs_dma_addr, GFP_KERNEL);
	अगर (info->bufs == शून्य)
		वापस -ENOMEM;

	info->rbufs = (काष्ठा slgt_desc*)info->bufs;
	info->tbufs = ((काष्ठा slgt_desc*)info->bufs) + info->rbuf_count;

	pbufs = (अचिन्हित पूर्णांक)info->bufs_dma_addr;

	/*
	 * Build circular lists of descriptors
	 */

	क्रम (i=0; i < info->rbuf_count; i++) अणु
		/* physical address of this descriptor */
		info->rbufs[i].pdesc = pbufs + (i * माप(काष्ठा slgt_desc));

		/* physical address of next descriptor */
		अगर (i == info->rbuf_count - 1)
			info->rbufs[i].next = cpu_to_le32(pbufs);
		अन्यथा
			info->rbufs[i].next = cpu_to_le32(pbufs + ((i+1) * माप(काष्ठा slgt_desc)));
		set_desc_count(info->rbufs[i], DMAबफ_मानE);
	पूर्ण

	क्रम (i=0; i < info->tbuf_count; i++) अणु
		/* physical address of this descriptor */
		info->tbufs[i].pdesc = pbufs + ((info->rbuf_count + i) * माप(काष्ठा slgt_desc));

		/* physical address of next descriptor */
		अगर (i == info->tbuf_count - 1)
			info->tbufs[i].next = cpu_to_le32(pbufs + info->rbuf_count * माप(काष्ठा slgt_desc));
		अन्यथा
			info->tbufs[i].next = cpu_to_le32(pbufs + ((info->rbuf_count + i + 1) * माप(काष्ठा slgt_desc)));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_desc(काष्ठा slgt_info *info)
अणु
	अगर (info->bufs != शून्य) अणु
		dma_मुक्त_coherent(&info->pdev->dev, DESC_LIST_SIZE,
				  info->bufs, info->bufs_dma_addr);
		info->bufs  = शून्य;
		info->rbufs = शून्य;
		info->tbufs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_bufs(काष्ठा slgt_info *info, काष्ठा slgt_desc *bufs, पूर्णांक count)
अणु
	पूर्णांक i;
	क्रम (i=0; i < count; i++) अणु
		bufs[i].buf = dma_alloc_coherent(&info->pdev->dev, DMAबफ_मानE,
						 &bufs[i].buf_dma_addr, GFP_KERNEL);
		अगर (!bufs[i].buf)
			वापस -ENOMEM;
		bufs[i].pbuf  = cpu_to_le32((अचिन्हित पूर्णांक)bufs[i].buf_dma_addr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_bufs(काष्ठा slgt_info *info, काष्ठा slgt_desc *bufs, पूर्णांक count)
अणु
	पूर्णांक i;
	क्रम (i=0; i < count; i++) अणु
		अगर (bufs[i].buf == शून्य)
			जारी;
		dma_मुक्त_coherent(&info->pdev->dev, DMAबफ_मानE, bufs[i].buf,
				  bufs[i].buf_dma_addr);
		bufs[i].buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_dma_bufs(काष्ठा slgt_info *info)
अणु
	info->rbuf_count = 32;
	info->tbuf_count = 32;

	अगर (alloc_desc(info) < 0 ||
	    alloc_bufs(info, info->rbufs, info->rbuf_count) < 0 ||
	    alloc_bufs(info, info->tbufs, info->tbuf_count) < 0 ||
	    alloc_पंचांगp_rbuf(info) < 0) अणु
		DBGERR(("%s DMA buffer alloc fail\n", info->device_name));
		वापस -ENOMEM;
	पूर्ण
	reset_rbufs(info);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_dma_bufs(काष्ठा slgt_info *info)
अणु
	अगर (info->bufs) अणु
		मुक्त_bufs(info, info->rbufs, info->rbuf_count);
		मुक्त_bufs(info, info->tbufs, info->tbuf_count);
		मुक्त_desc(info);
	पूर्ण
	मुक्त_पंचांगp_rbuf(info);
पूर्ण

अटल पूर्णांक claim_resources(काष्ठा slgt_info *info)
अणु
	अगर (request_mem_region(info->phys_reg_addr, SLGT_REG_SIZE, "synclink_gt") == शून्य) अणु
		DBGERR(("%s reg addr conflict, addr=%08X\n",
			info->device_name, info->phys_reg_addr));
		info->init_error = DiagStatus_AddressConflict;
		जाओ errout;
	पूर्ण
	अन्यथा
		info->reg_addr_requested = true;

	info->reg_addr = ioremap(info->phys_reg_addr, SLGT_REG_SIZE);
	अगर (!info->reg_addr) अणु
		DBGERR(("%s can't map device registers, addr=%08X\n",
			info->device_name, info->phys_reg_addr));
		info->init_error = DiagStatus_CantAssignPciResources;
		जाओ errout;
	पूर्ण
	वापस 0;

errout:
	release_resources(info);
	वापस -ENODEV;
पूर्ण

अटल व्योम release_resources(काष्ठा slgt_info *info)
अणु
	अगर (info->irq_requested) अणु
		मुक्त_irq(info->irq_level, info);
		info->irq_requested = false;
	पूर्ण

	अगर (info->reg_addr_requested) अणु
		release_mem_region(info->phys_reg_addr, SLGT_REG_SIZE);
		info->reg_addr_requested = false;
	पूर्ण

	अगर (info->reg_addr) अणु
		iounmap(info->reg_addr);
		info->reg_addr = शून्य;
	पूर्ण
पूर्ण

/* Add the specअगरied device instance data काष्ठाure to the
 * global linked list of devices and increment the device count.
 */
अटल व्योम add_device(काष्ठा slgt_info *info)
अणु
	अक्षर *devstr;

	info->next_device = शून्य;
	info->line = slgt_device_count;
	प्र_लिखो(info->device_name, "%s%d", tty_dev_prefix, info->line);

	अगर (info->line < MAX_DEVICES) अणु
		अगर (maxframe[info->line])
			info->max_frame_size = maxframe[info->line];
	पूर्ण

	slgt_device_count++;

	अगर (!slgt_device_list)
		slgt_device_list = info;
	अन्यथा अणु
		काष्ठा slgt_info *current_dev = slgt_device_list;
		जबतक(current_dev->next_device)
			current_dev = current_dev->next_device;
		current_dev->next_device = info;
	पूर्ण

	अगर (info->max_frame_size < 4096)
		info->max_frame_size = 4096;
	अन्यथा अगर (info->max_frame_size > 65535)
		info->max_frame_size = 65535;

	चयन(info->pdev->device) अणु
	हाल SYNCLINK_GT_DEVICE_ID:
		devstr = "GT";
		अवरोध;
	हाल SYNCLINK_GT2_DEVICE_ID:
		devstr = "GT2";
		अवरोध;
	हाल SYNCLINK_GT4_DEVICE_ID:
		devstr = "GT4";
		अवरोध;
	हाल SYNCLINK_AC_DEVICE_ID:
		devstr = "AC";
		info->params.mode = MGSL_MODE_ASYNC;
		अवरोध;
	शेष:
		devstr = "(unknown model)";
	पूर्ण
	prपूर्णांकk("SyncLink %s %s IO=%08x IRQ=%d MaxFrameSize=%u\n",
		devstr, info->device_name, info->phys_reg_addr,
		info->irq_level, info->max_frame_size);

#अगर SYNCLINK_GENERIC_HDLC
	hdlcdev_init(info);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा tty_port_operations slgt_port_ops = अणु
	.carrier_उठाओd = carrier_उठाओd,
	.dtr_rts = dtr_rts,
पूर्ण;

/*
 *  allocate device instance काष्ठाure, वापस शून्य on failure
 */
अटल काष्ठा slgt_info *alloc_dev(पूर्णांक adapter_num, पूर्णांक port_num, काष्ठा pci_dev *pdev)
अणु
	काष्ठा slgt_info *info;

	info = kzalloc(माप(काष्ठा slgt_info), GFP_KERNEL);

	अगर (!info) अणु
		DBGERR(("%s device alloc failed adapter=%d port=%d\n",
			driver_name, adapter_num, port_num));
	पूर्ण अन्यथा अणु
		tty_port_init(&info->port);
		info->port.ops = &slgt_port_ops;
		info->magic = MGSL_MAGIC;
		INIT_WORK(&info->task, bh_handler);
		info->max_frame_size = 4096;
		info->base_घड़ी = 14745600;
		info->rbuf_fill_level = DMAबफ_मानE;
		init_रुकोqueue_head(&info->status_event_रुको_q);
		init_रुकोqueue_head(&info->event_रुको_q);
		spin_lock_init(&info->netlock);
		स_नकल(&info->params,&शेष_params,माप(MGSL_PARAMS));
		info->idle_mode = HDLC_TXIDLE_FLAGS;
		info->adapter_num = adapter_num;
		info->port_num = port_num;

		समयr_setup(&info->tx_समयr, tx_समयout, 0);
		समयr_setup(&info->rx_समयr, rx_समयout, 0);

		/* Copy configuration info to device instance data */
		info->pdev = pdev;
		info->irq_level = pdev->irq;
		info->phys_reg_addr = pci_resource_start(pdev,0);

		info->bus_type = MGSL_BUS_TYPE_PCI;
		info->irq_flags = IRQF_SHARED;

		info->init_error = -1; /* assume error, set to 0 on successful init */
	पूर्ण

	वापस info;
पूर्ण

अटल व्योम device_init(पूर्णांक adapter_num, काष्ठा pci_dev *pdev)
अणु
	काष्ठा slgt_info *port_array[SLGT_MAX_PORTS];
	पूर्णांक i;
	पूर्णांक port_count = 1;

	अगर (pdev->device == SYNCLINK_GT2_DEVICE_ID)
		port_count = 2;
	अन्यथा अगर (pdev->device == SYNCLINK_GT4_DEVICE_ID)
		port_count = 4;

	/* allocate device instances क्रम all ports */
	क्रम (i=0; i < port_count; ++i) अणु
		port_array[i] = alloc_dev(adapter_num, i, pdev);
		अगर (port_array[i] == शून्य) अणु
			क्रम (--i; i >= 0; --i) अणु
				tty_port_destroy(&port_array[i]->port);
				kमुक्त(port_array[i]);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	/* give copy of port_array to all ports and add to device list  */
	क्रम (i=0; i < port_count; ++i) अणु
		स_नकल(port_array[i]->port_array, port_array, माप(port_array));
		add_device(port_array[i]);
		port_array[i]->port_count = port_count;
		spin_lock_init(&port_array[i]->lock);
	पूर्ण

	/* Allocate and claim adapter resources */
	अगर (!claim_resources(port_array[0])) अणु

		alloc_dma_bufs(port_array[0]);

		/* copy resource inक्रमmation from first port to others */
		क्रम (i = 1; i < port_count; ++i) अणु
			port_array[i]->irq_level = port_array[0]->irq_level;
			port_array[i]->reg_addr  = port_array[0]->reg_addr;
			alloc_dma_bufs(port_array[i]);
		पूर्ण

		अगर (request_irq(port_array[0]->irq_level,
					slgt_पूर्णांकerrupt,
					port_array[0]->irq_flags,
					port_array[0]->device_name,
					port_array[0]) < 0) अणु
			DBGERR(("%s request_irq failed IRQ=%d\n",
				port_array[0]->device_name,
				port_array[0]->irq_level));
		पूर्ण अन्यथा अणु
			port_array[0]->irq_requested = true;
			adapter_test(port_array[0]);
			क्रम (i=1 ; i < port_count ; i++) अणु
				port_array[i]->init_error = port_array[0]->init_error;
				port_array[i]->gpio_present = port_array[0]->gpio_present;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < port_count; ++i) अणु
		काष्ठा slgt_info *info = port_array[i];
		tty_port_रेजिस्टर_device(&info->port, serial_driver, info->line,
				&info->pdev->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक init_one(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	अगर (pci_enable_device(dev)) अणु
		prपूर्णांकk("error enabling pci device %p\n", dev);
		वापस -EIO;
	पूर्ण
	pci_set_master(dev);
	device_init(slgt_device_count, dev);
	वापस 0;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *dev)
अणु
पूर्ण

अटल स्थिर काष्ठा tty_operations ops = अणु
	.खोलो = खोलो,
	.बंद = बंद,
	.ग_लिखो = ग_लिखो,
	.put_अक्षर = put_अक्षर,
	.flush_अक्षरs = flush_अक्षरs,
	.ग_लिखो_room = ग_लिखो_room,
	.अक्षरs_in_buffer = अक्षरs_in_buffer,
	.flush_buffer = flush_buffer,
	.ioctl = ioctl,
	.compat_ioctl = slgt_compat_ioctl,
	.throttle = throttle,
	.unthrottle = unthrottle,
	.send_xअक्षर = send_xअक्षर,
	.अवरोध_ctl = set_अवरोध,
	.रुको_until_sent = रुको_until_sent,
	.set_termios = set_termios,
	.stop = tx_hold,
	.start = tx_release,
	.hangup = hangup,
	.tiocmget = tiocmget,
	.tiocmset = tiocmset,
	.get_icount = get_icount,
	.proc_show = synclink_gt_proc_show,
पूर्ण;

अटल व्योम slgt_cleanup(व्योम)
अणु
	काष्ठा slgt_info *info;
	काष्ठा slgt_info *पंचांगp;

	prपूर्णांकk(KERN_INFO "unload %s\n", driver_name);

	अगर (serial_driver) अणु
		क्रम (info=slgt_device_list ; info != शून्य ; info=info->next_device)
			tty_unरेजिस्टर_device(serial_driver, info->line);
		tty_unरेजिस्टर_driver(serial_driver);
		put_tty_driver(serial_driver);
	पूर्ण

	/* reset devices */
	info = slgt_device_list;
	जबतक(info) अणु
		reset_port(info);
		info = info->next_device;
	पूर्ण

	/* release devices */
	info = slgt_device_list;
	जबतक(info) अणु
#अगर SYNCLINK_GENERIC_HDLC
		hdlcdev_निकास(info);
#पूर्ण_अगर
		मुक्त_dma_bufs(info);
		मुक्त_पंचांगp_rbuf(info);
		अगर (info->port_num == 0)
			release_resources(info);
		पंचांगp = info;
		info = info->next_device;
		tty_port_destroy(&पंचांगp->port);
		kमुक्त(पंचांगp);
	पूर्ण

	अगर (pci_रेजिस्टरed)
		pci_unरेजिस्टर_driver(&pci_driver);
पूर्ण

/*
 *  Driver initialization entry poपूर्णांक.
 */
अटल पूर्णांक __init slgt_init(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "%s\n", driver_name);

	serial_driver = alloc_tty_driver(MAX_DEVICES);
	अगर (!serial_driver) अणु
		prपूर्णांकk("%s can't allocate tty driver\n", driver_name);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the tty_driver काष्ठाure */

	serial_driver->driver_name = slgt_driver_name;
	serial_driver->name = tty_dev_prefix;
	serial_driver->major = ttymajor;
	serial_driver->minor_start = 64;
	serial_driver->type = TTY_DRIVER_TYPE_SERIAL;
	serial_driver->subtype = SERIAL_TYPE_NORMAL;
	serial_driver->init_termios = tty_std_termios;
	serial_driver->init_termios.c_cflag =
		B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	serial_driver->init_termios.c_ispeed = 9600;
	serial_driver->init_termios.c_ospeed = 9600;
	serial_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(serial_driver, &ops);
	अगर ((rc = tty_रेजिस्टर_driver(serial_driver)) < 0) अणु
		DBGERR(("%s can't register serial driver\n", driver_name));
		put_tty_driver(serial_driver);
		serial_driver = शून्य;
		जाओ error;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s, tty major#%d\n",
	       driver_name, serial_driver->major);

	slgt_device_count = 0;
	अगर ((rc = pci_रेजिस्टर_driver(&pci_driver)) < 0) अणु
		prपूर्णांकk("%s pci_register_driver error=%d\n", driver_name, rc);
		जाओ error;
	पूर्ण
	pci_रेजिस्टरed = true;

	अगर (!slgt_device_list)
		prपूर्णांकk("%s no devices found\n",driver_name);

	वापस 0;

error:
	slgt_cleanup();
	वापस rc;
पूर्ण

अटल व्योम __निकास slgt_निकास(व्योम)
अणु
	slgt_cleanup();
पूर्ण

module_init(slgt_init);
module_निकास(slgt_निकास);

/*
 * रेजिस्टर access routines
 */

#घोषणा CALC_REGADDR() \
	अचिन्हित दीर्घ reg_addr = ((अचिन्हित दीर्घ)info->reg_addr) + addr; \
	अगर (addr >= 0x80) \
		reg_addr += (info->port_num) * 32; \
	अन्यथा अगर (addr >= 0x40)	\
		reg_addr += (info->port_num) * 16;

अटल __u8 rd_reg8(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr)
अणु
	CALC_REGADDR();
	वापस पढ़ोb((व्योम __iomem *)reg_addr);
पूर्ण

अटल व्योम wr_reg8(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u8 value)
अणु
	CALC_REGADDR();
	ग_लिखोb(value, (व्योम __iomem *)reg_addr);
पूर्ण

अटल __u16 rd_reg16(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr)
अणु
	CALC_REGADDR();
	वापस पढ़ोw((व्योम __iomem *)reg_addr);
पूर्ण

अटल व्योम wr_reg16(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u16 value)
अणु
	CALC_REGADDR();
	ग_लिखोw(value, (व्योम __iomem *)reg_addr);
पूर्ण

अटल __u32 rd_reg32(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr)
अणु
	CALC_REGADDR();
	वापस पढ़ोl((व्योम __iomem *)reg_addr);
पूर्ण

अटल व्योम wr_reg32(काष्ठा slgt_info *info, अचिन्हित पूर्णांक addr, __u32 value)
अणु
	CALC_REGADDR();
	ग_लिखोl(value, (व्योम __iomem *)reg_addr);
पूर्ण

अटल व्योम rdma_reset(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i;

	/* set reset bit */
	wr_reg32(info, RDCSR, BIT1);

	/* रुको क्रम enable bit cleared */
	क्रम(i=0 ; i < 1000 ; i++)
		अगर (!(rd_reg32(info, RDCSR) & BIT0))
			अवरोध;
पूर्ण

अटल व्योम tdma_reset(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i;

	/* set reset bit */
	wr_reg32(info, TDCSR, BIT1);

	/* रुको क्रम enable bit cleared */
	क्रम(i=0 ; i < 1000 ; i++)
		अगर (!(rd_reg32(info, TDCSR) & BIT0))
			अवरोध;
पूर्ण

/*
 * enable पूर्णांकernal loopback
 * TxCLK and RxCLK are generated from BRG
 * and TxD is looped back to RxD पूर्णांकernally.
 */
अटल व्योम enable_loopback(काष्ठा slgt_info *info)
अणु
	/* SCR (serial control) BIT2=loopback enable */
	wr_reg16(info, SCR, (अचिन्हित लघु)(rd_reg16(info, SCR) | BIT2));

	अगर (info->params.mode != MGSL_MODE_ASYNC) अणु
		/* CCR (घड़ी control)
		 * 07..05  tx घड़ी source (010 = BRG)
		 * 04..02  rx घड़ी source (010 = BRG)
		 * 01      auxclk enable   (0 = disable)
		 * 00      BRG enable      (1 = enable)
		 *
		 * 0100 1001
		 */
		wr_reg8(info, CCR, 0x49);

		/* set speed अगर available, otherwise use शेष */
		अगर (info->params.घड़ी_speed)
			set_rate(info, info->params.घड़ी_speed);
		अन्यथा
			set_rate(info, 3686400);
	पूर्ण
पूर्ण

/*
 *  set baud rate generator to specअगरied rate
 */
अटल व्योम set_rate(काष्ठा slgt_info *info, u32 rate)
अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक osc = info->base_घड़ी;

	/* भाग = osc/rate - 1
	 *
	 * Round भाग up अगर osc/rate is not पूर्णांकeger to
	 * क्रमce to next slowest rate.
	 */

	अगर (rate) अणु
		भाग = osc/rate;
		अगर (!(osc % rate) && भाग)
			भाग--;
		wr_reg16(info, BDR, (अचिन्हित लघु)भाग);
	पूर्ण
पूर्ण

अटल व्योम rx_stop(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु val;

	/* disable and reset receiver */
	val = rd_reg16(info, RCR) & ~BIT1;          /* clear enable bit */
	wr_reg16(info, RCR, (अचिन्हित लघु)(val | BIT2)); /* set reset bit */
	wr_reg16(info, RCR, val);                  /* clear reset bit */

	slgt_irq_off(info, IRQ_RXOVER + IRQ_RXDATA + IRQ_RXIDLE);

	/* clear pending rx पूर्णांकerrupts */
	wr_reg16(info, SSR, IRQ_RXIDLE + IRQ_RXOVER);

	rdma_reset(info);

	info->rx_enabled = false;
	info->rx_restart = false;
पूर्ण

अटल व्योम rx_start(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु val;

	slgt_irq_off(info, IRQ_RXOVER + IRQ_RXDATA);

	/* clear pending rx overrun IRQ */
	wr_reg16(info, SSR, IRQ_RXOVER);

	/* reset and disable receiver */
	val = rd_reg16(info, RCR) & ~BIT1; /* clear enable bit */
	wr_reg16(info, RCR, (अचिन्हित लघु)(val | BIT2)); /* set reset bit */
	wr_reg16(info, RCR, val);                  /* clear reset bit */

	rdma_reset(info);
	reset_rbufs(info);

	अगर (info->rx_pio) अणु
		/* rx request when rx FIFO not empty */
		wr_reg16(info, SCR, (अचिन्हित लघु)(rd_reg16(info, SCR) & ~BIT14));
		slgt_irq_on(info, IRQ_RXDATA);
		अगर (info->params.mode == MGSL_MODE_ASYNC) अणु
			/* enable saving of rx status */
			wr_reg32(info, RDCSR, BIT6);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* rx request when rx FIFO half full */
		wr_reg16(info, SCR, (अचिन्हित लघु)(rd_reg16(info, SCR) | BIT14));
		/* set 1st descriptor address */
		wr_reg32(info, RDDAR, info->rbufs[0].pdesc);

		अगर (info->params.mode != MGSL_MODE_ASYNC) अणु
			/* enable rx DMA and DMA पूर्णांकerrupt */
			wr_reg32(info, RDCSR, (BIT2 + BIT0));
		पूर्ण अन्यथा अणु
			/* enable saving of rx status, rx DMA and DMA पूर्णांकerrupt */
			wr_reg32(info, RDCSR, (BIT6 + BIT2 + BIT0));
		पूर्ण
	पूर्ण

	slgt_irq_on(info, IRQ_RXOVER);

	/* enable receiver */
	wr_reg16(info, RCR, (अचिन्हित लघु)(rd_reg16(info, RCR) | BIT1));

	info->rx_restart = false;
	info->rx_enabled = true;
पूर्ण

अटल व्योम tx_start(काष्ठा slgt_info *info)
अणु
	अगर (!info->tx_enabled) अणु
		wr_reg16(info, TCR,
			 (अचिन्हित लघु)((rd_reg16(info, TCR) | BIT1) & ~BIT2));
		info->tx_enabled = true;
	पूर्ण

	अगर (desc_count(info->tbufs[info->tbuf_start])) अणु
		info->drop_rts_on_tx_करोne = false;

		अगर (info->params.mode != MGSL_MODE_ASYNC) अणु
			अगर (info->params.flags & HDLC_FLAG_AUTO_RTS) अणु
				get_संकेतs(info);
				अगर (!(info->संकेतs & SerialSignal_RTS)) अणु
					info->संकेतs |= SerialSignal_RTS;
					set_संकेतs(info);
					info->drop_rts_on_tx_करोne = true;
				पूर्ण
			पूर्ण

			slgt_irq_off(info, IRQ_TXDATA);
			slgt_irq_on(info, IRQ_TXUNDER + IRQ_TXIDLE);
			/* clear tx idle and underrun status bits */
			wr_reg16(info, SSR, (अचिन्हित लघु)(IRQ_TXIDLE + IRQ_TXUNDER));
		पूर्ण अन्यथा अणु
			slgt_irq_off(info, IRQ_TXDATA);
			slgt_irq_on(info, IRQ_TXIDLE);
			/* clear tx idle status bit */
			wr_reg16(info, SSR, IRQ_TXIDLE);
		पूर्ण
		/* set 1st descriptor address and start DMA */
		wr_reg32(info, TDDAR, info->tbufs[info->tbuf_start].pdesc);
		wr_reg32(info, TDCSR, BIT2 + BIT0);
		info->tx_active = true;
	पूर्ण
पूर्ण

अटल व्योम tx_stop(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु val;

	del_समयr(&info->tx_समयr);

	tdma_reset(info);

	/* reset and disable transmitter */
	val = rd_reg16(info, TCR) & ~BIT1;          /* clear enable bit */
	wr_reg16(info, TCR, (अचिन्हित लघु)(val | BIT2)); /* set reset bit */

	slgt_irq_off(info, IRQ_TXDATA + IRQ_TXIDLE + IRQ_TXUNDER);

	/* clear tx idle and underrun status bit */
	wr_reg16(info, SSR, (अचिन्हित लघु)(IRQ_TXIDLE + IRQ_TXUNDER));

	reset_tbufs(info);

	info->tx_enabled = false;
	info->tx_active = false;
पूर्ण

अटल व्योम reset_port(काष्ठा slgt_info *info)
अणु
	अगर (!info->reg_addr)
		वापस;

	tx_stop(info);
	rx_stop(info);

	info->संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
	set_संकेतs(info);

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
पूर्ण

अटल व्योम reset_adapter(काष्ठा slgt_info *info)
अणु
	पूर्णांक i;
	क्रम (i=0; i < info->port_count; ++i) अणु
		अगर (info->port_array[i])
			reset_port(info->port_array[i]);
	पूर्ण
पूर्ण

अटल व्योम async_mode(काष्ठा slgt_info *info)
अणु
  	अचिन्हित लघु val;

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
	tx_stop(info);
	rx_stop(info);

	/* TCR (tx control)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NRZ
	 * 09      parity enable
	 * 08      1=odd parity, 0=even parity
	 * 07      1=RTS driver control
	 * 06      1=अवरोध enable
	 * 05..04  अक्षरacter length
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      0=1 stop bit, 1=2 stop bits
	 * 02      reset
	 * 01      enable
	 * 00      स्वतः-CTS enable
	 */
	val = 0x4000;

	अगर (info->अगर_mode & MGSL_INTERFACE_RTS_EN)
		val |= BIT7;

	अगर (info->params.parity != ASYNC_PARITY_NONE) अणु
		val |= BIT9;
		अगर (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT8;
	पूर्ण

	चयन (info->params.data_bits)
	अणु
	हाल 6: val |= BIT4; अवरोध;
	हाल 7: val |= BIT5; अवरोध;
	हाल 8: val |= BIT5 + BIT4; अवरोध;
	पूर्ण

	अगर (info->params.stop_bits != 1)
		val |= BIT3;

	अगर (info->params.flags & HDLC_FLAG_AUTO_CTS)
		val |= BIT0;

	wr_reg16(info, TCR, val);

	/* RCR (rx control)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NRZ
	 * 09      parity enable
	 * 08      1=odd parity, 0=even parity
	 * 07..06  reserved, must be 0
	 * 05..04  अक्षरacter length
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      reserved, must be zero
	 * 02      reset
	 * 01      enable
	 * 00      स्वतः-DCD enable
	 */
	val = 0x4000;

	अगर (info->params.parity != ASYNC_PARITY_NONE) अणु
		val |= BIT9;
		अगर (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT8;
	पूर्ण

	चयन (info->params.data_bits)
	अणु
	हाल 6: val |= BIT4; अवरोध;
	हाल 7: val |= BIT5; अवरोध;
	हाल 8: val |= BIT5 + BIT4; अवरोध;
	पूर्ण

	अगर (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT0;

	wr_reg16(info, RCR, val);

	/* CCR (घड़ी control)
	 *
	 * 07..05  011 = tx घड़ी source is BRG/16
	 * 04..02  010 = rx घड़ी source is BRG
	 * 01      0 = auxclk disabled
	 * 00      1 = BRG enabled
	 *
	 * 0110 1001
	 */
	wr_reg8(info, CCR, 0x69);

	msc_set_vcr(info);

	/* SCR (serial control)
	 *
	 * 15  1=tx req on FIFO half empty
	 * 14  1=rx req on FIFO half full
	 * 13  tx data  IRQ enable
	 * 12  tx idle  IRQ enable
	 * 11  rx अवरोध on IRQ enable
	 * 10  rx data  IRQ enable
	 * 09  rx अवरोध off IRQ enable
	 * 08  overrun  IRQ enable
	 * 07  DSR      IRQ enable
	 * 06  CTS      IRQ enable
	 * 05  DCD      IRQ enable
	 * 04  RI       IRQ enable
	 * 03  0=16x sampling, 1=8x sampling
	 * 02  1=txd->rxd पूर्णांकernal loopback enable
	 * 01  reserved, must be zero
	 * 00  1=master IRQ enable
	 */
	val = BIT15 + BIT14 + BIT0;
	/* JCR[8] : 1 = x8 async mode feature available */
	अगर ((rd_reg32(info, JCR) & BIT8) && info->params.data_rate &&
	    ((info->base_घड़ी < (info->params.data_rate * 16)) ||
	     (info->base_घड़ी % (info->params.data_rate * 16)))) अणु
		/* use 8x sampling */
		val |= BIT3;
		set_rate(info, info->params.data_rate * 8);
	पूर्ण अन्यथा अणु
		/* use 16x sampling */
		set_rate(info, info->params.data_rate * 16);
	पूर्ण
	wr_reg16(info, SCR, val);

	slgt_irq_on(info, IRQ_RXBREAK | IRQ_RXOVER);

	अगर (info->params.loopback)
		enable_loopback(info);
पूर्ण

अटल व्योम sync_mode(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु val;

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
	tx_stop(info);
	rx_stop(info);

	/* TCR (tx control)
	 *
	 * 15..13  mode
	 *         000=HDLC/SDLC
	 *         001=raw bit synchronous
	 *         010=asynchronous/isochronous
	 *         011=monosync byte synchronous
	 *         100=bisync byte synchronous
	 *         101=xsync byte synchronous
	 * 12..10  encoding
	 * 09      CRC enable
	 * 08      CRC32
	 * 07      1=RTS driver control
	 * 06      preamble enable
	 * 05..04  preamble length
	 * 03      share खोलो/बंद flag
	 * 02      reset
	 * 01      enable
	 * 00      स्वतः-CTS enable
	 */
	val = BIT2;

	चयन(info->params.mode) अणु
	हाल MGSL_MODE_XSYNC:
		val |= BIT15 + BIT13;
		अवरोध;
	हाल MGSL_MODE_MONOSYNC: val |= BIT14 + BIT13; अवरोध;
	हाल MGSL_MODE_BISYNC:   val |= BIT15; अवरोध;
	हाल MGSL_MODE_RAW:      val |= BIT13; अवरोध;
	पूर्ण
	अगर (info->अगर_mode & MGSL_INTERFACE_RTS_EN)
		val |= BIT7;

	चयन(info->params.encoding)
	अणु
	हाल HDLC_ENCODING_NRZB:          val |= BIT10; अवरोध;
	हाल HDLC_ENCODING_NRZI_MARK:     val |= BIT11; अवरोध;
	हाल HDLC_ENCODING_NRZI:          val |= BIT11 + BIT10; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_MARK:  val |= BIT12; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_SPACE: val |= BIT12 + BIT10; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_LEVEL: val |= BIT12 + BIT11; अवरोध;
	हाल HDLC_ENCODING_DIFF_BIPHASE_LEVEL: val |= BIT12 + BIT11 + BIT10; अवरोध;
	पूर्ण

	चयन (info->params.crc_type & HDLC_CRC_MASK)
	अणु
	हाल HDLC_CRC_16_CCITT: val |= BIT9; अवरोध;
	हाल HDLC_CRC_32_CCITT: val |= BIT9 + BIT8; अवरोध;
	पूर्ण

	अगर (info->params.preamble != HDLC_PREAMBLE_PATTERN_NONE)
		val |= BIT6;

	चयन (info->params.preamble_length)
	अणु
	हाल HDLC_PREAMBLE_LENGTH_16BITS: val |= BIT5; अवरोध;
	हाल HDLC_PREAMBLE_LENGTH_32BITS: val |= BIT4; अवरोध;
	हाल HDLC_PREAMBLE_LENGTH_64BITS: val |= BIT5 + BIT4; अवरोध;
	पूर्ण

	अगर (info->params.flags & HDLC_FLAG_AUTO_CTS)
		val |= BIT0;

	wr_reg16(info, TCR, val);

	/* TPR (transmit preamble) */

	चयन (info->params.preamble)
	अणु
	हाल HDLC_PREAMBLE_PATTERN_FLAGS: val = 0x7e; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_ONES:  val = 0xff; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_ZEROS: val = 0x00; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_10:    val = 0x55; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_01:    val = 0xaa; अवरोध;
	शेष:                          val = 0x7e; अवरोध;
	पूर्ण
	wr_reg8(info, TPR, (अचिन्हित अक्षर)val);

	/* RCR (rx control)
	 *
	 * 15..13  mode
	 *         000=HDLC/SDLC
	 *         001=raw bit synchronous
	 *         010=asynchronous/isochronous
	 *         011=monosync byte synchronous
	 *         100=bisync byte synchronous
	 *         101=xsync byte synchronous
	 * 12..10  encoding
	 * 09      CRC enable
	 * 08      CRC32
	 * 07..03  reserved, must be 0
	 * 02      reset
	 * 01      enable
	 * 00      स्वतः-DCD enable
	 */
	val = 0;

	चयन(info->params.mode) अणु
	हाल MGSL_MODE_XSYNC:
		val |= BIT15 + BIT13;
		अवरोध;
	हाल MGSL_MODE_MONOSYNC: val |= BIT14 + BIT13; अवरोध;
	हाल MGSL_MODE_BISYNC:   val |= BIT15; अवरोध;
	हाल MGSL_MODE_RAW:      val |= BIT13; अवरोध;
	पूर्ण

	चयन(info->params.encoding)
	अणु
	हाल HDLC_ENCODING_NRZB:          val |= BIT10; अवरोध;
	हाल HDLC_ENCODING_NRZI_MARK:     val |= BIT11; अवरोध;
	हाल HDLC_ENCODING_NRZI:          val |= BIT11 + BIT10; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_MARK:  val |= BIT12; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_SPACE: val |= BIT12 + BIT10; अवरोध;
	हाल HDLC_ENCODING_BIPHASE_LEVEL: val |= BIT12 + BIT11; अवरोध;
	हाल HDLC_ENCODING_DIFF_BIPHASE_LEVEL: val |= BIT12 + BIT11 + BIT10; अवरोध;
	पूर्ण

	चयन (info->params.crc_type & HDLC_CRC_MASK)
	अणु
	हाल HDLC_CRC_16_CCITT: val |= BIT9; अवरोध;
	हाल HDLC_CRC_32_CCITT: val |= BIT9 + BIT8; अवरोध;
	पूर्ण

	अगर (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT0;

	wr_reg16(info, RCR, val);

	/* CCR (घड़ी control)
	 *
	 * 07..05  tx घड़ी source
	 * 04..02  rx घड़ी source
	 * 01      auxclk enable
	 * 00      BRG enable
	 */
	val = 0;

	अगर (info->params.flags & HDLC_FLAG_TXC_BRG)
	अणु
		// when RxC source is DPLL, BRG generates 16X DPLL
		// reference घड़ी, so take TxC from BRG/16 to get
		// transmit घड़ी at actual data rate
		अगर (info->params.flags & HDLC_FLAG_RXC_DPLL)
			val |= BIT6 + BIT5;	/* 011, txclk = BRG/16 */
		अन्यथा
			val |= BIT6;	/* 010, txclk = BRG */
	पूर्ण
	अन्यथा अगर (info->params.flags & HDLC_FLAG_TXC_DPLL)
		val |= BIT7;	/* 100, txclk = DPLL Input */
	अन्यथा अगर (info->params.flags & HDLC_FLAG_TXC_RXCPIN)
		val |= BIT5;	/* 001, txclk = RXC Input */

	अगर (info->params.flags & HDLC_FLAG_RXC_BRG)
		val |= BIT3;	/* 010, rxclk = BRG */
	अन्यथा अगर (info->params.flags & HDLC_FLAG_RXC_DPLL)
		val |= BIT4;	/* 100, rxclk = DPLL */
	अन्यथा अगर (info->params.flags & HDLC_FLAG_RXC_TXCPIN)
		val |= BIT2;	/* 001, rxclk = TXC Input */

	अगर (info->params.घड़ी_speed)
		val |= BIT1 + BIT0;

	wr_reg8(info, CCR, (अचिन्हित अक्षर)val);

	अगर (info->params.flags & (HDLC_FLAG_TXC_DPLL + HDLC_FLAG_RXC_DPLL))
	अणु
		// program DPLL mode
		चयन(info->params.encoding)
		अणु
		हाल HDLC_ENCODING_BIPHASE_MARK:
		हाल HDLC_ENCODING_BIPHASE_SPACE:
			val = BIT7; अवरोध;
		हाल HDLC_ENCODING_BIPHASE_LEVEL:
		हाल HDLC_ENCODING_DIFF_BIPHASE_LEVEL:
			val = BIT7 + BIT6; अवरोध;
		शेष: val = BIT6;	// NRZ encodings
		पूर्ण
		wr_reg16(info, RCR, (अचिन्हित लघु)(rd_reg16(info, RCR) | val));

		// DPLL requires a 16X reference घड़ी from BRG
		set_rate(info, info->params.घड़ी_speed * 16);
	पूर्ण
	अन्यथा
		set_rate(info, info->params.घड़ी_speed);

	tx_set_idle(info);

	msc_set_vcr(info);

	/* SCR (serial control)
	 *
	 * 15  1=tx req on FIFO half empty
	 * 14  1=rx req on FIFO half full
	 * 13  tx data  IRQ enable
	 * 12  tx idle  IRQ enable
	 * 11  underrun IRQ enable
	 * 10  rx data  IRQ enable
	 * 09  rx idle  IRQ enable
	 * 08  overrun  IRQ enable
	 * 07  DSR      IRQ enable
	 * 06  CTS      IRQ enable
	 * 05  DCD      IRQ enable
	 * 04  RI       IRQ enable
	 * 03  reserved, must be zero
	 * 02  1=txd->rxd पूर्णांकernal loopback enable
	 * 01  reserved, must be zero
	 * 00  1=master IRQ enable
	 */
	wr_reg16(info, SCR, BIT15 + BIT14 + BIT0);

	अगर (info->params.loopback)
		enable_loopback(info);
पूर्ण

/*
 *  set transmit idle mode
 */
अटल व्योम tx_set_idle(काष्ठा slgt_info *info)
अणु
	अचिन्हित अक्षर val;
	अचिन्हित लघु tcr;

	/* अगर preamble enabled (tcr[6] == 1) then tx idle size = 8 bits
	 * अन्यथा tcr[5:4] = tx idle size: 00 = 8 bits, 01 = 16 bits
	 */
	tcr = rd_reg16(info, TCR);
	अगर (info->idle_mode & HDLC_TXIDLE_CUSTOM_16) अणु
		/* disable preamble, set idle size to 16 bits */
		tcr = (tcr & ~(BIT6 + BIT5)) | BIT4;
		/* MSB of 16 bit idle specअगरied in tx preamble रेजिस्टर (TPR) */
		wr_reg8(info, TPR, (अचिन्हित अक्षर)((info->idle_mode >> 8) & 0xff));
	पूर्ण अन्यथा अगर (!(tcr & BIT6)) अणु
		/* preamble is disabled, set idle size to 8 bits */
		tcr &= ~(BIT5 + BIT4);
	पूर्ण
	wr_reg16(info, TCR, tcr);

	अगर (info->idle_mode & (HDLC_TXIDLE_CUSTOM_8 | HDLC_TXIDLE_CUSTOM_16)) अणु
		/* LSB of custom tx idle specअगरied in tx idle रेजिस्टर */
		val = (अचिन्हित अक्षर)(info->idle_mode & 0xff);
	पूर्ण अन्यथा अणु
		/* standard 8 bit idle patterns */
		चयन(info->idle_mode)
		अणु
		हाल HDLC_TXIDLE_FLAGS:          val = 0x7e; अवरोध;
		हाल HDLC_TXIDLE_ALT_ZEROS_ONES:
		हाल HDLC_TXIDLE_ALT_MARK_SPACE: val = 0xaa; अवरोध;
		हाल HDLC_TXIDLE_ZEROS:
		हाल HDLC_TXIDLE_SPACE:          val = 0x00; अवरोध;
		शेष:                         val = 0xff;
		पूर्ण
	पूर्ण

	wr_reg8(info, TIR, val);
पूर्ण

/*
 * get state of V24 status (input) संकेतs
 */
अटल व्योम get_संकेतs(काष्ठा slgt_info *info)
अणु
	अचिन्हित लघु status = rd_reg16(info, SSR);

	/* clear all serial संकेतs except RTS and DTR */
	info->संकेतs &= SerialSignal_RTS | SerialSignal_DTR;

	अगर (status & BIT3)
		info->संकेतs |= SerialSignal_DSR;
	अगर (status & BIT2)
		info->संकेतs |= SerialSignal_CTS;
	अगर (status & BIT1)
		info->संकेतs |= SerialSignal_DCD;
	अगर (status & BIT0)
		info->संकेतs |= SerialSignal_RI;
पूर्ण

/*
 * set V.24 Control Register based on current configuration
 */
अटल व्योम msc_set_vcr(काष्ठा slgt_info *info)
अणु
	अचिन्हित अक्षर val = 0;

	/* VCR (V.24 control)
	 *
	 * 07..04  serial IF select
	 * 03      DTR
	 * 02      RTS
	 * 01      LL
	 * 00      RL
	 */

	चयन(info->अगर_mode & MGSL_INTERFACE_MASK)
	अणु
	हाल MGSL_INTERFACE_RS232:
		val |= BIT5; /* 0010 */
		अवरोध;
	हाल MGSL_INTERFACE_V35:
		val |= BIT7 + BIT6 + BIT5; /* 1110 */
		अवरोध;
	हाल MGSL_INTERFACE_RS422:
		val |= BIT6; /* 0100 */
		अवरोध;
	पूर्ण

	अगर (info->अगर_mode & MGSL_INTERFACE_MSB_FIRST)
		val |= BIT4;
	अगर (info->संकेतs & SerialSignal_DTR)
		val |= BIT3;
	अगर (info->संकेतs & SerialSignal_RTS)
		val |= BIT2;
	अगर (info->अगर_mode & MGSL_INTERFACE_LL)
		val |= BIT1;
	अगर (info->अगर_mode & MGSL_INTERFACE_RL)
		val |= BIT0;
	wr_reg8(info, VCR, val);
पूर्ण

/*
 * set state of V24 control (output) संकेतs
 */
अटल व्योम set_संकेतs(काष्ठा slgt_info *info)
अणु
	अचिन्हित अक्षर val = rd_reg8(info, VCR);
	अगर (info->संकेतs & SerialSignal_DTR)
		val |= BIT3;
	अन्यथा
		val &= ~BIT3;
	अगर (info->संकेतs & SerialSignal_RTS)
		val |= BIT2;
	अन्यथा
		val &= ~BIT2;
	wr_reg8(info, VCR, val);
पूर्ण

/*
 * मुक्त range of receive DMA buffers (i to last)
 */
अटल व्योम मुक्त_rbufs(काष्ठा slgt_info *info, अचिन्हित पूर्णांक i, अचिन्हित पूर्णांक last)
अणु
	पूर्णांक करोne = 0;

	जबतक(!करोne) अणु
		/* reset current buffer क्रम reuse */
		info->rbufs[i].status = 0;
		set_desc_count(info->rbufs[i], info->rbuf_fill_level);
		अगर (i == last)
			करोne = 1;
		अगर (++i == info->rbuf_count)
			i = 0;
	पूर्ण
	info->rbuf_current = i;
पूर्ण

/*
 * mark all receive DMA buffers as मुक्त
 */
अटल व्योम reset_rbufs(काष्ठा slgt_info *info)
अणु
	मुक्त_rbufs(info, 0, info->rbuf_count - 1);
	info->rbuf_fill_index = 0;
	info->rbuf_fill_count = 0;
पूर्ण

/*
 * pass receive HDLC frame to upper layer
 *
 * वापस true अगर frame available, otherwise false
 */
अटल bool rx_get_frame(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक start, end;
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक framesize = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *tty = info->port.tty;
	अचिन्हित अक्षर addr_field = 0xff;
	अचिन्हित पूर्णांक crc_size = 0;

	चयन (info->params.crc_type & HDLC_CRC_MASK) अणु
	हाल HDLC_CRC_16_CCITT: crc_size = 2; अवरोध;
	हाल HDLC_CRC_32_CCITT: crc_size = 4; अवरोध;
	पूर्ण

check_again:

	framesize = 0;
	addr_field = 0xff;
	start = end = info->rbuf_current;

	क्रम (;;) अणु
		अगर (!desc_complete(info->rbufs[end]))
			जाओ cleanup;

		अगर (framesize == 0 && info->params.addr_filter != 0xff)
			addr_field = info->rbufs[end].buf[0];

		framesize += desc_count(info->rbufs[end]);

		अगर (desc_eof(info->rbufs[end]))
			अवरोध;

		अगर (++end == info->rbuf_count)
			end = 0;

		अगर (end == info->rbuf_current) अणु
			अगर (info->rx_enabled)अणु
				spin_lock_irqsave(&info->lock,flags);
				rx_start(info);
				spin_unlock_irqrestore(&info->lock,flags);
			पूर्ण
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* status
	 *
	 * 15      buffer complete
	 * 14..06  reserved
	 * 05..04  residue
	 * 02      eof (end of frame)
	 * 01      CRC error
	 * 00      पात
	 */
	status = desc_status(info->rbufs[end]);

	/* ignore CRC bit अगर not using CRC (bit is undefined) */
	अगर ((info->params.crc_type & HDLC_CRC_MASK) == HDLC_CRC_NONE)
		status &= ~BIT1;

	अगर (framesize == 0 ||
		 (addr_field != 0xff && addr_field != info->params.addr_filter)) अणु
		मुक्त_rbufs(info, start, end);
		जाओ check_again;
	पूर्ण

	अगर (framesize < (2 + crc_size) || status & BIT0) अणु
		info->icount.rxलघु++;
		framesize = 0;
	पूर्ण अन्यथा अगर (status & BIT1) अणु
		info->icount.rxcrc++;
		अगर (!(info->params.crc_type & HDLC_CRC_RETURN_EX))
			framesize = 0;
	पूर्ण

#अगर SYNCLINK_GENERIC_HDLC
	अगर (framesize == 0) अणु
		info->netdev->stats.rx_errors++;
		info->netdev->stats.rx_frame_errors++;
	पूर्ण
#पूर्ण_अगर

	DBGBH(("%s rx frame status=%04X size=%d\n",
		info->device_name, status, framesize));
	DBGDATA(info, info->rbufs[start].buf, min_t(पूर्णांक, framesize, info->rbuf_fill_level), "rx");

	अगर (framesize) अणु
		अगर (!(info->params.crc_type & HDLC_CRC_RETURN_EX)) अणु
			framesize -= crc_size;
			crc_size = 0;
		पूर्ण

		अगर (framesize > info->max_frame_size + crc_size)
			info->icount.rxदीर्घ++;
		अन्यथा अणु
			/* copy dma buffer(s) to contiguous temp buffer */
			पूर्णांक copy_count = framesize;
			पूर्णांक i = start;
			अचिन्हित अक्षर *p = info->पंचांगp_rbuf;
			info->पंचांगp_rbuf_count = framesize;

			info->icount.rxok++;

			जबतक(copy_count) अणु
				पूर्णांक partial_count = min_t(पूर्णांक, copy_count, info->rbuf_fill_level);
				स_नकल(p, info->rbufs[i].buf, partial_count);
				p += partial_count;
				copy_count -= partial_count;
				अगर (++i == info->rbuf_count)
					i = 0;
			पूर्ण

			अगर (info->params.crc_type & HDLC_CRC_RETURN_EX) अणु
				*p = (status & BIT1) ? RX_CRC_ERROR : RX_OK;
				framesize++;
			पूर्ण

#अगर SYNCLINK_GENERIC_HDLC
			अगर (info->netcount)
				hdlcdev_rx(info,info->पंचांगp_rbuf, framesize);
			अन्यथा
#पूर्ण_अगर
				ldisc_receive_buf(tty, info->पंचांगp_rbuf, info->flag_buf, framesize);
		पूर्ण
	पूर्ण
	मुक्त_rbufs(info, start, end);
	वापस true;

cleanup:
	वापस false;
पूर्ण

/*
 * pass receive buffer (RAW synchronous mode) to tty layer
 * वापस true अगर buffer available, otherwise false
 */
अटल bool rx_get_buf(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i = info->rbuf_current;
	अचिन्हित पूर्णांक count;

	अगर (!desc_complete(info->rbufs[i]))
		वापस false;
	count = desc_count(info->rbufs[i]);
	चयन(info->params.mode) अणु
	हाल MGSL_MODE_MONOSYNC:
	हाल MGSL_MODE_BISYNC:
	हाल MGSL_MODE_XSYNC:
		/* ignore residue in byte synchronous modes */
		अगर (desc_residue(info->rbufs[i]))
			count--;
		अवरोध;
	पूर्ण
	DBGDATA(info, info->rbufs[i].buf, count, "rx");
	DBGINFO(("rx_get_buf size=%d\n", count));
	अगर (count)
		ldisc_receive_buf(info->port.tty, info->rbufs[i].buf,
				  info->flag_buf, count);
	मुक्त_rbufs(info, i, i);
	वापस true;
पूर्ण

अटल व्योम reset_tbufs(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक i;
	info->tbuf_current = 0;
	क्रम (i=0 ; i < info->tbuf_count ; i++) अणु
		info->tbufs[i].status = 0;
		info->tbufs[i].count  = 0;
	पूर्ण
पूर्ण

/*
 * वापस number of मुक्त transmit DMA buffers
 */
अटल अचिन्हित पूर्णांक मुक्त_tbuf_count(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i = info->tbuf_current;

	करो
	अणु
		अगर (desc_count(info->tbufs[i]))
			अवरोध; /* buffer in use */
		++count;
		अगर (++i == info->tbuf_count)
			i=0;
	पूर्ण जबतक (i != info->tbuf_current);

	/* अगर tx DMA active, last zero count buffer is in use */
	अगर (count && (rd_reg32(info, TDCSR) & BIT0))
		--count;

	वापस count;
पूर्ण

/*
 * वापस number of bytes in unsent transmit DMA buffers
 * and the serial controller tx FIFO
 */
अटल अचिन्हित पूर्णांक tbuf_bytes(काष्ठा slgt_info *info)
अणु
	अचिन्हित पूर्णांक total_count = 0;
	अचिन्हित पूर्णांक i = info->tbuf_current;
	अचिन्हित पूर्णांक reg_value;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक active_buf_count = 0;

	/*
	 * Add descriptor counts क्रम all tx DMA buffers.
	 * If count is zero (cleared by DMA controller after पढ़ो),
	 * the buffer is complete or is actively being पढ़ो from.
	 *
	 * Record buf_count of last buffer with zero count starting
	 * from current ring position. buf_count is mirror
	 * copy of count and is not cleared by serial controller.
	 * If DMA controller is active, that buffer is actively
	 * being पढ़ो so add to total.
	 */
	करो अणु
		count = desc_count(info->tbufs[i]);
		अगर (count)
			total_count += count;
		अन्यथा अगर (!total_count)
			active_buf_count = info->tbufs[i].buf_count;
		अगर (++i == info->tbuf_count)
			i = 0;
	पूर्ण जबतक (i != info->tbuf_current);

	/* पढ़ो tx DMA status रेजिस्टर */
	reg_value = rd_reg32(info, TDCSR);

	/* अगर tx DMA active, last zero count buffer is in use */
	अगर (reg_value & BIT0)
		total_count += active_buf_count;

	/* add tx FIFO count = reg_value[15..8] */
	total_count += (reg_value >> 8) & 0xff;

	/* अगर transmitter active add one byte क्रम shअगरt रेजिस्टर */
	अगर (info->tx_active)
		total_count++;

	वापस total_count;
पूर्ण

/*
 * load data पूर्णांकo transmit DMA buffer ring and start transmitter अगर needed
 * वापस true अगर data accepted, otherwise false (buffers full)
 */
अटल bool tx_load(काष्ठा slgt_info *info, स्थिर अक्षर *buf, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित लघु count;
	अचिन्हित पूर्णांक i;
	काष्ठा slgt_desc *d;

	/* check required buffer space */
	अगर (DIV_ROUND_UP(size, DMAबफ_मानE) > मुक्त_tbuf_count(info))
		वापस false;

	DBGDATA(info, buf, size, "tx");

	/*
	 * copy data to one or more DMA buffers in circular ring
	 * tbuf_start   = first buffer क्रम this data
	 * tbuf_current = next मुक्त buffer
	 *
	 * Copy all data beक्रमe making data visible to DMA controller by
	 * setting descriptor count of the first buffer.
	 * This prevents an active DMA controller from पढ़ोing the first DMA
	 * buffers of a frame and stopping beक्रमe the final buffers are filled.
	 */

	info->tbuf_start = i = info->tbuf_current;

	जबतक (size) अणु
		d = &info->tbufs[i];

		count = (अचिन्हित लघु)((size > DMAबफ_मानE) ? DMAबफ_मानE : size);
		स_नकल(d->buf, buf, count);

		size -= count;
		buf  += count;

		/*
		 * set खातापूर्ण bit क्रम last buffer of HDLC frame or
		 * क्रम every buffer in raw mode
		 */
		अगर ((!size && info->params.mode == MGSL_MODE_HDLC) ||
		    info->params.mode == MGSL_MODE_RAW)
			set_desc_eof(*d, 1);
		अन्यथा
			set_desc_eof(*d, 0);

		/* set descriptor count क्रम all but first buffer */
		अगर (i != info->tbuf_start)
			set_desc_count(*d, count);
		d->buf_count = count;

		अगर (++i == info->tbuf_count)
			i = 0;
	पूर्ण

	info->tbuf_current = i;

	/* set first buffer count to make new data visible to DMA controller */
	d = &info->tbufs[info->tbuf_start];
	set_desc_count(*d, d->buf_count);

	/* start transmitter अगर needed and update transmit समयout */
	अगर (!info->tx_active)
		tx_start(info);
	update_tx_समयr(info);

	वापस true;
पूर्ण

अटल पूर्णांक रेजिस्टर_test(काष्ठा slgt_info *info)
अणु
	अटल अचिन्हित लघु patterns[] =
		अणु0x0000, 0xffff, 0xaaaa, 0x5555, 0x6969, 0x9696पूर्ण;
	अटल अचिन्हित पूर्णांक count = ARRAY_SIZE(patterns);
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	क्रम (i=0 ; i < count ; i++) अणु
		wr_reg16(info, TIR, patterns[i]);
		wr_reg16(info, BDR, patterns[(i+1)%count]);
		अगर ((rd_reg16(info, TIR) != patterns[i]) ||
		    (rd_reg16(info, BDR) != patterns[(i+1)%count])) अणु
			rc = -ENODEV;
			अवरोध;
		पूर्ण
	पूर्ण
	info->gpio_present = (rd_reg32(info, JCR) & BIT5) ? 1 : 0;
	info->init_error = rc ? 0 : DiagStatus_AddressFailure;
	वापस rc;
पूर्ण

अटल पूर्णांक irq_test(काष्ठा slgt_info *info)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *oldtty = info->port.tty;
	u32 speed = info->params.data_rate;

	info->params.data_rate = 921600;
	info->port.tty = शून्य;

	spin_lock_irqsave(&info->lock, flags);
	async_mode(info);
	slgt_irq_on(info, IRQ_TXIDLE);

	/* enable transmitter */
	wr_reg16(info, TCR,
		(अचिन्हित लघु)(rd_reg16(info, TCR) | BIT1));

	/* ग_लिखो one byte and रुको क्रम tx idle */
	wr_reg16(info, TDR, 0);

	/* assume failure */
	info->init_error = DiagStatus_IrqFailure;
	info->irq_occurred = false;

	spin_unlock_irqrestore(&info->lock, flags);

	समयout=100;
	जबतक(समयout-- && !info->irq_occurred)
		msleep_पूर्णांकerruptible(10);

	spin_lock_irqsave(&info->lock,flags);
	reset_port(info);
	spin_unlock_irqrestore(&info->lock,flags);

	info->params.data_rate = speed;
	info->port.tty = oldtty;

	info->init_error = info->irq_occurred ? 0 : DiagStatus_IrqFailure;
	वापस info->irq_occurred ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक loopback_test_rx(काष्ठा slgt_info *info)
अणु
	अचिन्हित अक्षर *src, *dest;
	पूर्णांक count;

	अगर (desc_complete(info->rbufs[0])) अणु
		count = desc_count(info->rbufs[0]);
		src   = info->rbufs[0].buf;
		dest  = info->पंचांगp_rbuf;

		क्रम( ; count ; count-=2, src+=2) अणु
			/* src=data byte (src+1)=status byte */
			अगर (!(*(src+1) & (BIT9 + BIT8))) अणु
				*dest = *src;
				dest++;
				info->पंचांगp_rbuf_count++;
			पूर्ण
		पूर्ण
		DBGDATA(info, info->पंचांगp_rbuf, info->पंचांगp_rbuf_count, "rx");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_test(काष्ठा slgt_info *info)
अणु
#घोषणा TESTFRAMESIZE 20

	अचिन्हित दीर्घ समयout;
	u16 count;
	अचिन्हित अक्षर buf[TESTFRAMESIZE];
	पूर्णांक rc = -ENODEV;
	अचिन्हित दीर्घ flags;

	काष्ठा tty_काष्ठा *oldtty = info->port.tty;
	MGSL_PARAMS params;

	स_नकल(&params, &info->params, माप(params));

	info->params.mode = MGSL_MODE_ASYNC;
	info->params.data_rate = 921600;
	info->params.loopback = 1;
	info->port.tty = शून्य;

	/* build and send transmit frame */
	क्रम (count = 0; count < TESTFRAMESIZE; ++count)
		buf[count] = (अचिन्हित अक्षर)count;

	info->पंचांगp_rbuf_count = 0;
	स_रखो(info->पंचांगp_rbuf, 0, TESTFRAMESIZE);

	/* program hardware क्रम HDLC and enabled receiver */
	spin_lock_irqsave(&info->lock,flags);
	async_mode(info);
	rx_start(info);
	tx_load(info, buf, count);
	spin_unlock_irqrestore(&info->lock, flags);

	/* रुको क्रम receive complete */
	क्रम (समयout = 100; समयout; --समयout) अणु
		msleep_पूर्णांकerruptible(10);
		अगर (loopback_test_rx(info)) अणु
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* verअगरy received frame length and contents */
	अगर (!rc && (info->पंचांगp_rbuf_count != count ||
		  स_भेद(buf, info->पंचांगp_rbuf, count))) अणु
		rc = -ENODEV;
	पूर्ण

	spin_lock_irqsave(&info->lock,flags);
	reset_adapter(info);
	spin_unlock_irqrestore(&info->lock,flags);

	स_नकल(&info->params, &params, माप(info->params));
	info->port.tty = oldtty;

	info->init_error = rc ? DiagStatus_DmaFailure : 0;
	वापस rc;
पूर्ण

अटल पूर्णांक adapter_test(काष्ठा slgt_info *info)
अणु
	DBGINFO(("testing %s\n", info->device_name));
	अगर (रेजिस्टर_test(info) < 0) अणु
		prपूर्णांकk("register test failure %s addr=%08X\n",
			info->device_name, info->phys_reg_addr);
	पूर्ण अन्यथा अगर (irq_test(info) < 0) अणु
		prपूर्णांकk("IRQ test failure %s IRQ=%d\n",
			info->device_name, info->irq_level);
	पूर्ण अन्यथा अगर (loopback_test(info) < 0) अणु
		prपूर्णांकk("loopback test failure %s\n", info->device_name);
	पूर्ण
	वापस info->init_error;
पूर्ण

/*
 * transmit समयout handler
 */
अटल व्योम tx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा slgt_info *info = from_समयr(info, t, tx_समयr);
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s tx_timeout\n", info->device_name));
	अगर(info->tx_active && info->params.mode == MGSL_MODE_HDLC) अणु
		info->icount.txसमयout++;
	पूर्ण
	spin_lock_irqsave(&info->lock,flags);
	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);

#अगर SYNCLINK_GENERIC_HDLC
	अगर (info->netcount)
		hdlcdev_tx_करोne(info);
	अन्यथा
#पूर्ण_अगर
		bh_transmit(info);
पूर्ण

/*
 * receive buffer polling समयr
 */
अटल व्योम rx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा slgt_info *info = from_समयr(info, t, rx_समयr);
	अचिन्हित दीर्घ flags;

	DBGINFO(("%s rx_timeout\n", info->device_name));
	spin_lock_irqsave(&info->lock, flags);
	info->pending_bh |= BH_RECEIVE;
	spin_unlock_irqrestore(&info->lock, flags);
	bh_handler(&info->task);
पूर्ण

