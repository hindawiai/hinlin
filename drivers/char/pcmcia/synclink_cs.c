<शैली गुरु>
/*
 * linux/drivers/अक्षर/pcmcia/synclink_cs.c
 *
 * $Id: synclink_cs.c,v 4.34 2005/09/08 13:20:54 paulkf Exp $
 *
 * Device driver क्रम Microgate SyncLink PC Card
 * multiprotocol serial adapter.
 *
 * written by Paul Fulghum क्रम Microgate Corporation
 * paulkf@microgate.com
 *
 * Microgate and SyncLink are trademarks of Microgate Corporation
 *
 * This code is released under the GNU General Public License (GPL)
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

#घोषणा VERSION(ver,rel,seq) (((ver)<<16) | ((rel)<<8) | (seq))
#अगर defined(__i386__)
#  define BREAKPOINT() यंत्र("   int $3");
#अन्यथा
#  define BREAKPOINT() अणु पूर्ण
#पूर्ण_अगर

#घोषणा MAX_DEVICE_COUNT 4

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
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
#समावेश <linux/synclink.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/termios.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hdlc.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#अगर defined(CONFIG_HDLC) || (defined(CONFIG_HDLC_MODULE) && defined(CONFIG_SYNCLINK_CS_MODULE))
#घोषणा SYNCLINK_GENERIC_HDLC 1
#अन्यथा
#घोषणा SYNCLINK_GENERIC_HDLC 0
#पूर्ण_अगर

#घोषणा GET_USER(error,value,addr) error = get_user(value,addr)
#घोषणा COPY_FROM_USER(error,dest,src,size) error = copy_from_user(dest,src,size) ? -EFAULT : 0
#घोषणा PUT_USER(error,value,addr) error = put_user(value,addr)
#घोषणा COPY_TO_USER(error,dest,src,size) error = copy_to_user(dest,src,size) ? -EFAULT : 0

#समावेश <linux/uaccess.h>

अटल MGSL_PARAMS शेष_params = अणु
	MGSL_MODE_HDLC,			/* अचिन्हित दीर्घ mode */
	0,				/* अचिन्हित अक्षर loopback; */
	HDLC_FLAG_UNDERRUN_ABORT15,	/* अचिन्हित लघु flags; */
	HDLC_ENCODING_NRZI_SPACE,	/* अचिन्हित अक्षर encoding; */
	0,				/* अचिन्हित दीर्घ घड़ी_speed; */
	0xff,				/* अचिन्हित अक्षर addr_filter; */
	HDLC_CRC_16_CCITT,		/* अचिन्हित लघु crc_type; */
	HDLC_PREAMBLE_LENGTH_8BITS,	/* अचिन्हित अक्षर preamble_length; */
	HDLC_PREAMBLE_PATTERN_NONE,	/* अचिन्हित अक्षर preamble; */
	9600,				/* अचिन्हित दीर्घ data_rate; */
	8,				/* अचिन्हित अक्षर data_bits; */
	1,				/* अचिन्हित अक्षर stop_bits; */
	ASYNC_PARITY_NONE		/* अचिन्हित अक्षर parity; */
पूर्ण;

प्रकार काष्ठा अणु
	पूर्णांक count;
	अचिन्हित अक्षर status;
	अक्षर data[1];
पूर्ण RXBUF;

/* The queue of BH actions to be perक्रमmed */

#घोषणा BH_RECEIVE  1
#घोषणा BH_TRANSMIT 2
#घोषणा BH_STATUS   4

#घोषणा IO_PIN_SHUTDOWN_LIMIT 100

#घोषणा RELEVANT_IFLAG(अगरlag) (अगरlag & (IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK))

काष्ठा _input_संकेत_events अणु
	पूर्णांक	ri_up;
	पूर्णांक	ri_करोwn;
	पूर्णांक	dsr_up;
	पूर्णांक	dsr_करोwn;
	पूर्णांक	dcd_up;
	पूर्णांक	dcd_करोwn;
	पूर्णांक	cts_up;
	पूर्णांक	cts_करोwn;
पूर्ण;


/*
 * Device instance data काष्ठाure
 */

प्रकार काष्ठा _mgslpc_info अणु
	काष्ठा tty_port		port;
	व्योम *अगर_ptr;	/* General purpose poपूर्णांकer (used by SPPP) */
	पूर्णांक			magic;
	पूर्णांक			line;

	काष्ठा mgsl_icount	icount;

	पूर्णांक			समयout;
	पूर्णांक			x_अक्षर;		/* xon/xoff अक्षरacter */
	अचिन्हित अक्षर		पढ़ो_status_mask;
	अचिन्हित अक्षर		ignore_status_mask;

	अचिन्हित अक्षर *tx_buf;
	पूर्णांक            tx_put;
	पूर्णांक            tx_get;
	पूर्णांक            tx_count;

	/* circular list of fixed length rx buffers */

	अचिन्हित अक्षर  *rx_buf;        /* memory allocated क्रम all rx buffers */
	पूर्णांक            rx_buf_total_size; /* size of memory allocated क्रम rx buffers */
	पूर्णांक            rx_put;         /* index of next empty rx buffer */
	पूर्णांक            rx_get;         /* index of next full rx buffer */
	पूर्णांक            rx_buf_size;    /* size in bytes of single rx buffer */
	पूर्णांक            rx_buf_count;   /* total number of rx buffers */
	पूर्णांक            rx_frame_count; /* number of full rx buffers */

	रुको_queue_head_t	status_event_रुको_q;
	रुको_queue_head_t	event_रुको_q;
	काष्ठा समयr_list	tx_समयr;	/* HDLC transmit समयout समयr */
	काष्ठा _mgslpc_info	*next_device;	/* device list link */

	अचिन्हित लघु imra_value;
	अचिन्हित लघु imrb_value;
	अचिन्हित अक्षर  pim_value;

	spinlock_t lock;
	काष्ठा work_काष्ठा task;		/* task काष्ठाure क्रम scheduling bh */

	u32 max_frame_size;

	u32 pending_bh;

	bool bh_running;
	bool bh_requested;

	पूर्णांक dcd_chkcount; /* check counts to prevent */
	पूर्णांक cts_chkcount; /* too many IRQs अगर a संकेत */
	पूर्णांक dsr_chkcount; /* is भग्नing */
	पूर्णांक ri_chkcount;

	bool rx_enabled;
	bool rx_overflow;

	bool tx_enabled;
	bool tx_active;
	bool tx_पातing;
	u32 idle_mode;

	पूर्णांक अगर_mode; /* serial पूर्णांकerface selection (RS-232, v.35 etc) */

	अक्षर device_name[25];		/* device instance name */

	अचिन्हित पूर्णांक io_base;	/* base I/O address of adapter */
	अचिन्हित पूर्णांक irq_level;

	MGSL_PARAMS params;		/* communications parameters */

	अचिन्हित अक्षर serial_संकेतs;	/* current serial संकेत states */

	bool irq_occurred;		/* क्रम diagnostics use */
	अक्षर testing_irq;
	अचिन्हित पूर्णांक init_error;	/* startup error (DIAGS)	*/

	अक्षर *flag_buf;
	bool drop_rts_on_tx_करोne;

	काष्ठा	_input_संकेत_events	input_संकेत_events;

	/* PCMCIA support */
	काष्ठा pcmcia_device	*p_dev;
	पूर्णांक		      stop;

	/* SPPP/Cisco HDLC device parts */
	पूर्णांक netcount;
	spinlock_t netlock;

#अगर SYNCLINK_GENERIC_HDLC
	काष्ठा net_device *netdev;
#पूर्ण_अगर

पूर्ण MGSLPC_INFO;

#घोषणा MGSLPC_MAGIC 0x5402

/*
 * The size of the serial xmit buffer is 1 page, or 4096 bytes
 */
#घोषणा TXबफ_मानE 4096


#घोषणा CHA     0x00   /* channel A offset */
#घोषणा CHB     0x40   /* channel B offset */

/*
 *  FIXME: PPC has PVR defined in यंत्र/reg.h.  For now we just undef it.
 */
#अघोषित PVR

#घोषणा RXFIFO  0
#घोषणा TXFIFO  0
#घोषणा STAR    0x20
#घोषणा CMDR    0x20
#घोषणा RSTA    0x21
#घोषणा PRE     0x21
#घोषणा MODE    0x22
#घोषणा TIMR    0x23
#घोषणा XAD1    0x24
#घोषणा XAD2    0x25
#घोषणा RAH1    0x26
#घोषणा RAH2    0x27
#घोषणा DAFO    0x27
#घोषणा RAL1    0x28
#घोषणा RFC     0x28
#घोषणा RHCR    0x29
#घोषणा RAL2    0x29
#घोषणा RBCL    0x2a
#घोषणा XBCL    0x2a
#घोषणा RBCH    0x2b
#घोषणा XBCH    0x2b
#घोषणा CCR0    0x2c
#घोषणा CCR1    0x2d
#घोषणा CCR2    0x2e
#घोषणा CCR3    0x2f
#घोषणा VSTR    0x34
#घोषणा BGR     0x34
#घोषणा RLCR    0x35
#घोषणा AML     0x36
#घोषणा AMH     0x37
#घोषणा GIS     0x38
#घोषणा IVA     0x38
#घोषणा IPC     0x39
#घोषणा ISR     0x3a
#घोषणा IMR     0x3a
#घोषणा PVR     0x3c
#घोषणा PIS     0x3d
#घोषणा PIM     0x3d
#घोषणा PCR     0x3e
#घोषणा CCR4    0x3f

// IMR/ISR

#घोषणा IRQ_BREAK_ON    BIT15   // rx अवरोध detected
#घोषणा IRQ_DATAOVERRUN BIT14	// receive data overflow
#घोषणा IRQ_ALLSENT     BIT13	// all sent
#घोषणा IRQ_UNDERRUN    BIT12	// transmit data underrun
#घोषणा IRQ_TIMER       BIT11	// समयr पूर्णांकerrupt
#घोषणा IRQ_CTS         BIT10	// CTS status change
#घोषणा IRQ_TXREPEAT    BIT9	// tx message repeat
#घोषणा IRQ_TXFIFO      BIT8	// transmit pool पढ़ोy
#घोषणा IRQ_RXEOM       BIT7	// receive message end
#घोषणा IRQ_EXITHUNT    BIT6	// receive frame start
#घोषणा IRQ_RXTIME      BIT6    // rx अक्षर समयout
#घोषणा IRQ_DCD         BIT2	// carrier detect status change
#घोषणा IRQ_OVERRUN     BIT1	// receive frame overflow
#घोषणा IRQ_RXFIFO      BIT0	// receive pool full

// STAR

#घोषणा XFW   BIT6		// transmit FIFO ग_लिखो enable
#घोषणा CEC   BIT2		// command executing
#घोषणा CTS   BIT1		// CTS state

#घोषणा PVR_DTR      BIT0
#घोषणा PVR_DSR      BIT1
#घोषणा PVR_RI       BIT2
#घोषणा PVR_AUTOCTS  BIT3
#घोषणा PVR_RS232    0x20   /* 0010b */
#घोषणा PVR_V35      0xe0   /* 1110b */
#घोषणा PVR_RS422    0x40   /* 0100b */

/* Register access functions */

#घोषणा ग_लिखो_reg(info, reg, val) outb((val),(info)->io_base + (reg))
#घोषणा पढ़ो_reg(info, reg) inb((info)->io_base + (reg))

#घोषणा पढ़ो_reg16(info, reg) inw((info)->io_base + (reg))
#घोषणा ग_लिखो_reg16(info, reg, val) outw((val), (info)->io_base + (reg))

#घोषणा set_reg_bits(info, reg, mask) \
	ग_लिखो_reg(info, (reg), \
		 (अचिन्हित अक्षर) (पढ़ो_reg(info, (reg)) | (mask)))
#घोषणा clear_reg_bits(info, reg, mask) \
	ग_लिखो_reg(info, (reg), \
		 (अचिन्हित अक्षर) (पढ़ो_reg(info, (reg)) & ~(mask)))
/*
 * पूर्णांकerrupt enable/disable routines
 */
अटल व्योम irq_disable(MGSLPC_INFO *info, अचिन्हित अक्षर channel, अचिन्हित लघु mask)
अणु
	अगर (channel == CHA) अणु
		info->imra_value |= mask;
		ग_लिखो_reg16(info, CHA + IMR, info->imra_value);
	पूर्ण अन्यथा अणु
		info->imrb_value |= mask;
		ग_लिखो_reg16(info, CHB + IMR, info->imrb_value);
	पूर्ण
पूर्ण
अटल व्योम irq_enable(MGSLPC_INFO *info, अचिन्हित अक्षर channel, अचिन्हित लघु mask)
अणु
	अगर (channel == CHA) अणु
		info->imra_value &= ~mask;
		ग_लिखो_reg16(info, CHA + IMR, info->imra_value);
	पूर्ण अन्यथा अणु
		info->imrb_value &= ~mask;
		ग_लिखो_reg16(info, CHB + IMR, info->imrb_value);
	पूर्ण
पूर्ण

#घोषणा port_irq_disable(info, mask) \
	अणु info->pim_value |= (mask); ग_लिखो_reg(info, PIM, info->pim_value); पूर्ण

#घोषणा port_irq_enable(info, mask) \
	अणु info->pim_value &= ~(mask); ग_लिखो_reg(info, PIM, info->pim_value); पूर्ण

अटल व्योम rx_start(MGSLPC_INFO *info);
अटल व्योम rx_stop(MGSLPC_INFO *info);

अटल व्योम tx_start(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty);
अटल व्योम tx_stop(MGSLPC_INFO *info);
अटल व्योम tx_set_idle(MGSLPC_INFO *info);

अटल व्योम get_संकेतs(MGSLPC_INFO *info);
अटल व्योम set_संकेतs(MGSLPC_INFO *info);

अटल व्योम reset_device(MGSLPC_INFO *info);

अटल व्योम hdlc_mode(MGSLPC_INFO *info);
अटल व्योम async_mode(MGSLPC_INFO *info);

अटल व्योम tx_समयout(काष्ठा समयr_list *t);

अटल पूर्णांक carrier_उठाओd(काष्ठा tty_port *port);
अटल व्योम dtr_rts(काष्ठा tty_port *port, पूर्णांक onoff);

#अगर SYNCLINK_GENERIC_HDLC
#घोषणा dev_to_port(D) (dev_to_hdlc(D)->priv)
अटल व्योम hdlcdev_tx_करोne(MGSLPC_INFO *info);
अटल व्योम hdlcdev_rx(MGSLPC_INFO *info, अक्षर *buf, पूर्णांक size);
अटल पूर्णांक  hdlcdev_init(MGSLPC_INFO *info);
अटल व्योम hdlcdev_निकास(MGSLPC_INFO *info);
#पूर्ण_अगर

अटल व्योम trace_block(MGSLPC_INFO *info,स्थिर अक्षर* data, पूर्णांक count, पूर्णांक xmit);

अटल bool रेजिस्टर_test(MGSLPC_INFO *info);
अटल bool irq_test(MGSLPC_INFO *info);
अटल पूर्णांक adapter_test(MGSLPC_INFO *info);

अटल पूर्णांक claim_resources(MGSLPC_INFO *info);
अटल व्योम release_resources(MGSLPC_INFO *info);
अटल पूर्णांक mgslpc_add_device(MGSLPC_INFO *info);
अटल व्योम mgslpc_हटाओ_device(MGSLPC_INFO *info);

अटल bool rx_get_frame(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty);
अटल व्योम rx_reset_buffers(MGSLPC_INFO *info);
अटल पूर्णांक  rx_alloc_buffers(MGSLPC_INFO *info);
अटल व्योम rx_मुक्त_buffers(MGSLPC_INFO *info);

अटल irqवापस_t mgslpc_isr(पूर्णांक irq, व्योम *dev_id);

/*
 * Bottom half पूर्णांकerrupt handlers
 */
अटल व्योम bh_handler(काष्ठा work_काष्ठा *work);
अटल व्योम bh_transmit(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty);
अटल व्योम bh_status(MGSLPC_INFO *info);

/*
 * ioctl handlers
 */
अटल पूर्णांक tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल पूर्णांक get_stats(MGSLPC_INFO *info, काष्ठा mgsl_icount __user *user_icount);
अटल पूर्णांक get_params(MGSLPC_INFO *info, MGSL_PARAMS __user *user_params);
अटल पूर्णांक set_params(MGSLPC_INFO *info, MGSL_PARAMS __user *new_params, काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक get_txidle(MGSLPC_INFO *info, पूर्णांक __user *idle_mode);
अटल पूर्णांक set_txidle(MGSLPC_INFO *info, पूर्णांक idle_mode);
अटल पूर्णांक set_txenable(MGSLPC_INFO *info, पूर्णांक enable, काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक tx_पात(MGSLPC_INFO *info);
अटल पूर्णांक set_rxenable(MGSLPC_INFO *info, पूर्णांक enable);
अटल पूर्णांक रुको_events(MGSLPC_INFO *info, पूर्णांक __user *mask);

अटल MGSLPC_INFO *mgslpc_device_list = शून्य;
अटल पूर्णांक mgslpc_device_count = 0;

/*
 * Set this param to non-zero to load eax with the
 * .text section address and अवरोधpoपूर्णांक on module load.
 * This is useful क्रम use with gdb and add-symbol-file command.
 */
अटल bool अवरोध_on_load;

/*
 * Driver major number, शेषs to zero to get स्वतः
 * asचिन्हित major number. May be क्रमced as module parameter.
 */
अटल पूर्णांक ttymajor=0;

अटल पूर्णांक debug_level = 0;
अटल पूर्णांक maxframe[MAX_DEVICE_COUNT] = अणु0,पूर्ण;

module_param(अवरोध_on_load, bool, 0);
module_param(ttymajor, पूर्णांक, 0);
module_param(debug_level, पूर्णांक, 0);
module_param_array(maxframe, पूर्णांक, शून्य, 0);

MODULE_LICENSE("GPL");

अटल अक्षर *driver_name = "SyncLink PC Card driver";
अटल अक्षर *driver_version = "$Revision: 4.34 $";

अटल काष्ठा tty_driver *serial_driver;

/* number of अक्षरacters left in xmit buffer beक्रमe we ask क्रम more */
#घोषणा WAKEUP_CHARS 256

अटल व्योम mgslpc_change_params(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty);
अटल व्योम mgslpc_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout);

/* PCMCIA prototypes */

अटल पूर्णांक mgslpc_config(काष्ठा pcmcia_device *link);
अटल व्योम mgslpc_release(u_दीर्घ arg);
अटल व्योम mgslpc_detach(काष्ठा pcmcia_device *p_dev);

/*
 * 1st function defined in .text section. Calling this function in
 * init_module() followed by a अवरोधpoपूर्णांक allows a remote debugger
 * (gdb) to get the .text address क्रम the add-symbol-file command.
 * This allows remote debugging of dynamically loadable modules.
 */
अटल व्योम* mgslpc_get_text_ptr(व्योम)
अणु
	वापस mgslpc_get_text_ptr;
पूर्ण

/**
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

अटल स्थिर काष्ठा tty_port_operations mgslpc_port_ops = अणु
	.carrier_उठाओd = carrier_उठाओd,
	.dtr_rts = dtr_rts
पूर्ण;

अटल पूर्णांक mgslpc_probe(काष्ठा pcmcia_device *link)
अणु
	MGSLPC_INFO *info;
	पूर्णांक ret;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("mgslpc_attach\n");

	info = kzalloc(माप(MGSLPC_INFO), GFP_KERNEL);
	अगर (!info) अणु
		prपूर्णांकk("Error can't allocate device instance data\n");
		वापस -ENOMEM;
	पूर्ण

	info->magic = MGSLPC_MAGIC;
	tty_port_init(&info->port);
	info->port.ops = &mgslpc_port_ops;
	INIT_WORK(&info->task, bh_handler);
	info->max_frame_size = 4096;
	init_रुकोqueue_head(&info->status_event_रुको_q);
	init_रुकोqueue_head(&info->event_रुको_q);
	spin_lock_init(&info->lock);
	spin_lock_init(&info->netlock);
	स_नकल(&info->params,&शेष_params,माप(MGSL_PARAMS));
	info->idle_mode = HDLC_TXIDLE_FLAGS;
	info->imra_value = 0xffff;
	info->imrb_value = 0xffff;
	info->pim_value = 0xff;

	info->p_dev = link;
	link->priv = info;

	/* Initialize the काष्ठा pcmcia_device काष्ठाure */

	ret = mgslpc_config(link);
	अगर (ret != 0)
		जाओ failed;

	ret = mgslpc_add_device(info);
	अगर (ret != 0)
		जाओ failed_release;

	वापस 0;

failed_release:
	mgslpc_release((u_दीर्घ)link);
failed:
	tty_port_destroy(&info->port);
	kमुक्त(info);
	वापस ret;
पूर्ण

/* Card has been inserted.
 */

अटल पूर्णांक mgslpc_ioprobe(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक mgslpc_config(काष्ठा pcmcia_device *link)
अणु
	MGSLPC_INFO *info = link->priv;
	पूर्णांक ret;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("mgslpc_config(0x%p)\n", link);

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, mgslpc_ioprobe, शून्य);
	अगर (ret != 0)
		जाओ failed;

	link->config_index = 8;
	link->config_regs = PRESENT_OPTION;

	ret = pcmcia_request_irq(link, mgslpc_isr);
	अगर (ret)
		जाओ failed;
	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	info->io_base = link->resource[0]->start;
	info->irq_level = link->irq;
	वापस 0;

failed:
	mgslpc_release((u_दीर्घ)link);
	वापस -ENODEV;
पूर्ण

/* Card has been हटाओd.
 * Unरेजिस्टर device and release PCMCIA configuration.
 * If device is खोलो, postpone until it is बंदd.
 */
अटल व्योम mgslpc_release(u_दीर्घ arg)
अणु
	काष्ठा pcmcia_device *link = (काष्ठा pcmcia_device *)arg;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("mgslpc_release(0x%p)\n", link);

	pcmcia_disable_device(link);
पूर्ण

अटल व्योम mgslpc_detach(काष्ठा pcmcia_device *link)
अणु
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("mgslpc_detach(0x%p)\n", link);

	((MGSLPC_INFO *)link->priv)->stop = 1;
	mgslpc_release((u_दीर्घ)link);

	mgslpc_हटाओ_device((MGSLPC_INFO *)link->priv);
पूर्ण

अटल पूर्णांक mgslpc_suspend(काष्ठा pcmcia_device *link)
अणु
	MGSLPC_INFO *info = link->priv;

	info->stop = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mgslpc_resume(काष्ठा pcmcia_device *link)
अणु
	MGSLPC_INFO *info = link->priv;

	info->stop = 0;

	वापस 0;
पूर्ण


अटल अंतरभूत bool mgslpc_paranoia_check(MGSLPC_INFO *info,
					अक्षर *name, स्थिर अक्षर *routine)
अणु
#अगर_घोषित MGSLPC_PARANOIA_CHECK
	अटल स्थिर अक्षर *badmagic =
		"Warning: bad magic number for mgsl struct (%s) in %s\n";
	अटल स्थिर अक्षर *badinfo =
		"Warning: null mgslpc_info for (%s) in %s\n";

	अगर (!info) अणु
		prपूर्णांकk(badinfo, name, routine);
		वापस true;
	पूर्ण
	अगर (info->magic != MGSLPC_MAGIC) अणु
		prपूर्णांकk(badmagic, name, routine);
		वापस true;
	पूर्ण
#अन्यथा
	अगर (!info)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण


#घोषणा CMD_RXFIFO      BIT7	// release current rx FIFO
#घोषणा CMD_RXRESET     BIT6	// receiver reset
#घोषणा CMD_RXFIFO_READ BIT5
#घोषणा CMD_START_TIMER BIT4
#घोषणा CMD_TXFIFO      BIT3	// release current tx FIFO
#घोषणा CMD_TXEOM       BIT1	// transmit end message
#घोषणा CMD_TXRESET     BIT0	// transmit reset

अटल bool रुको_command_complete(MGSLPC_INFO *info, अचिन्हित अक्षर channel)
अणु
	पूर्णांक i = 0;
	/* रुको क्रम command completion */
	जबतक (पढ़ो_reg(info, (अचिन्हित अक्षर)(channel+STAR)) & BIT2) अणु
		udelay(1);
		अगर (i++ == 1000)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम issue_command(MGSLPC_INFO *info, अचिन्हित अक्षर channel, अचिन्हित अक्षर cmd)
अणु
	रुको_command_complete(info, channel);
	ग_लिखो_reg(info, (अचिन्हित अक्षर) (channel + CMDR), cmd);
पूर्ण

अटल व्योम tx_छोड़ो(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (mgslpc_paranoia_check(info, tty->name, "tx_pause"))
		वापस;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("tx_pause(%s)\n", info->device_name);

	spin_lock_irqsave(&info->lock, flags);
	अगर (info->tx_enabled)
		tx_stop(info);
	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

अटल व्योम tx_release(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (mgslpc_paranoia_check(info, tty->name, "tx_release"))
		वापस;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("tx_release(%s)\n", info->device_name);

	spin_lock_irqsave(&info->lock, flags);
	अगर (!info->tx_enabled)
		tx_start(info, tty);
	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

/* Return next bottom half action to perक्रमm.
 * or 0 अगर nothing to करो.
 */
अटल पूर्णांक bh_action(MGSLPC_INFO *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&info->lock, flags);

	अगर (info->pending_bh & BH_RECEIVE) अणु
		info->pending_bh &= ~BH_RECEIVE;
		rc = BH_RECEIVE;
	पूर्ण अन्यथा अगर (info->pending_bh & BH_TRANSMIT) अणु
		info->pending_bh &= ~BH_TRANSMIT;
		rc = BH_TRANSMIT;
	पूर्ण अन्यथा अगर (info->pending_bh & BH_STATUS) अणु
		info->pending_bh &= ~BH_STATUS;
		rc = BH_STATUS;
	पूर्ण

	अगर (!rc) अणु
		/* Mark BH routine as complete */
		info->bh_running = false;
		info->bh_requested = false;
	पूर्ण

	spin_unlock_irqrestore(&info->lock, flags);

	वापस rc;
पूर्ण

अटल व्योम bh_handler(काष्ठा work_काष्ठा *work)
अणु
	MGSLPC_INFO *info = container_of(work, MGSLPC_INFO, task);
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक action;

	अगर (debug_level >= DEBUG_LEVEL_BH)
		prपूर्णांकk("%s(%d):bh_handler(%s) entry\n",
			__खाता__,__LINE__,info->device_name);

	info->bh_running = true;
	tty = tty_port_tty_get(&info->port);

	जबतक((action = bh_action(info)) != 0) अणु

		/* Process work item */
		अगर (debug_level >= DEBUG_LEVEL_BH)
			prपूर्णांकk("%s(%d):bh_handler() work item action=%d\n",
				__खाता__,__LINE__,action);

		चयन (action) अणु

		हाल BH_RECEIVE:
			जबतक(rx_get_frame(info, tty));
			अवरोध;
		हाल BH_TRANSMIT:
			bh_transmit(info, tty);
			अवरोध;
		हाल BH_STATUS:
			bh_status(info);
			अवरोध;
		शेष:
			/* unknown work item ID */
			prपूर्णांकk("Unknown work item ID=%08X!\n", action);
			अवरोध;
		पूर्ण
	पूर्ण

	tty_kref_put(tty);
	अगर (debug_level >= DEBUG_LEVEL_BH)
		prपूर्णांकk("%s(%d):bh_handler(%s) exit\n",
			__खाता__,__LINE__,info->device_name);
पूर्ण

अटल व्योम bh_transmit(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अगर (debug_level >= DEBUG_LEVEL_BH)
		prपूर्णांकk("bh_transmit() entry on %s\n", info->device_name);

	अगर (tty)
		tty_wakeup(tty);
पूर्ण

अटल व्योम bh_status(MGSLPC_INFO *info)
अणु
	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;
	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
पूर्ण

/* eom: non-zero = end of frame */
अटल व्योम rx_पढ़ोy_hdlc(MGSLPC_INFO *info, पूर्णांक eom)
अणु
	अचिन्हित अक्षर data[2];
	अचिन्हित अक्षर fअगरo_count, पढ़ो_count, i;
	RXBUF *buf = (RXBUF*)(info->rx_buf + (info->rx_put * info->rx_buf_size));

	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):rx_ready_hdlc(eom=%d)\n", __खाता__, __LINE__, eom);

	अगर (!info->rx_enabled)
		वापस;

	अगर (info->rx_frame_count >= info->rx_buf_count) अणु
		/* no more मुक्त buffers */
		issue_command(info, CHA, CMD_RXRESET);
		info->pending_bh |= BH_RECEIVE;
		info->rx_overflow = true;
		info->icount.buf_overrun++;
		वापस;
	पूर्ण

	अगर (eom) अणु
		/* end of frame, get FIFO count from RBCL रेजिस्टर */
		fअगरo_count = (अचिन्हित अक्षर)(पढ़ो_reg(info, CHA+RBCL) & 0x1f);
		अगर (fअगरo_count == 0)
			fअगरo_count = 32;
	पूर्ण अन्यथा
		fअगरo_count = 32;

	करो अणु
		अगर (fअगरo_count == 1) अणु
			पढ़ो_count = 1;
			data[0] = पढ़ो_reg(info, CHA + RXFIFO);
		पूर्ण अन्यथा अणु
			पढ़ो_count = 2;
			*((अचिन्हित लघु *) data) = पढ़ो_reg16(info, CHA + RXFIFO);
		पूर्ण
		fअगरo_count -= पढ़ो_count;
		अगर (!fअगरo_count && eom)
			buf->status = data[--पढ़ो_count];

		क्रम (i = 0; i < पढ़ो_count; i++) अणु
			अगर (buf->count >= info->max_frame_size) अणु
				/* frame too large, reset receiver and reset current buffer */
				issue_command(info, CHA, CMD_RXRESET);
				buf->count = 0;
				वापस;
			पूर्ण
			*(buf->data + buf->count) = data[i];
			buf->count++;
		पूर्ण
	पूर्ण जबतक (fअगरo_count);

	अगर (eom) अणु
		info->pending_bh |= BH_RECEIVE;
		info->rx_frame_count++;
		info->rx_put++;
		अगर (info->rx_put >= info->rx_buf_count)
			info->rx_put = 0;
	पूर्ण
	issue_command(info, CHA, CMD_RXFIFO);
पूर्ण

अटल व्योम rx_पढ़ोy_async(MGSLPC_INFO *info, पूर्णांक tcd)
अणु
	काष्ठा tty_port *port = &info->port;
	अचिन्हित अक्षर data, status, flag;
	पूर्णांक fअगरo_count;
	पूर्णांक work = 0;
	काष्ठा mgsl_icount *icount = &info->icount;

	अगर (tcd) अणु
		/* early termination, get FIFO count from RBCL रेजिस्टर */
		fअगरo_count = (अचिन्हित अक्षर)(पढ़ो_reg(info, CHA+RBCL) & 0x1f);

		/* Zero fअगरo count could mean 0 or 32 bytes available.
		 * If BIT5 of STAR is set then at least 1 byte is available.
		 */
		अगर (!fअगरo_count && (पढ़ो_reg(info,CHA+STAR) & BIT5))
			fअगरo_count = 32;
	पूर्ण अन्यथा
		fअगरo_count = 32;

	tty_buffer_request_room(port, fअगरo_count);
	/* Flush received async data to receive data buffer. */
	जबतक (fअगरo_count) अणु
		data   = पढ़ो_reg(info, CHA + RXFIFO);
		status = पढ़ो_reg(info, CHA + RXFIFO);
		fअगरo_count -= 2;

		icount->rx++;
		flag = TTY_NORMAL;

		// अगर no frameing/crc error then save data
		// BIT7:parity error
		// BIT6:framing error

		अगर (status & (BIT7 + BIT6)) अणु
			अगर (status & BIT7)
				icount->parity++;
			अन्यथा
				icount->frame++;

			/* discard अक्षर अगर tty control flags say so */
			अगर (status & info->ignore_status_mask)
				जारी;

			status &= info->पढ़ो_status_mask;

			अगर (status & BIT7)
				flag = TTY_PARITY;
			अन्यथा अगर (status & BIT6)
				flag = TTY_FRAME;
		पूर्ण
		work += tty_insert_flip_अक्षर(port, data, flag);
	पूर्ण
	issue_command(info, CHA, CMD_RXFIFO);

	अगर (debug_level >= DEBUG_LEVEL_ISR) अणु
		prपूर्णांकk("%s(%d):rx_ready_async",
			__खाता__,__LINE__);
		prपूर्णांकk("%s(%d):rx=%d brk=%d parity=%d frame=%d overrun=%d\n",
			__खाता__,__LINE__,icount->rx,icount->brk,
			icount->parity,icount->frame,icount->overrun);
	पूर्ण

	अगर (work)
		tty_flip_buffer_push(port);
पूर्ण


अटल व्योम tx_करोne(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!info->tx_active)
		वापस;

	info->tx_active = false;
	info->tx_पातing = false;

	अगर (info->params.mode == MGSL_MODE_ASYNC)
		वापस;

	info->tx_count = info->tx_put = info->tx_get = 0;
	del_समयr(&info->tx_समयr);

	अगर (info->drop_rts_on_tx_करोne) अणु
		get_संकेतs(info);
		अगर (info->serial_संकेतs & SerialSignal_RTS) अणु
			info->serial_संकेतs &= ~SerialSignal_RTS;
			set_संकेतs(info);
		पूर्ण
		info->drop_rts_on_tx_करोne = false;
	पूर्ण

#अगर SYNCLINK_GENERIC_HDLC
	अगर (info->netcount)
		hdlcdev_tx_करोne(info);
	अन्यथा
#पूर्ण_अगर
	अणु
		अगर (tty && (tty->stopped || tty->hw_stopped)) अणु
			tx_stop(info);
			वापस;
		पूर्ण
		info->pending_bh |= BH_TRANSMIT;
	पूर्ण
पूर्ण

अटल व्योम tx_पढ़ोy(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित अक्षर fअगरo_count = 32;
	पूर्णांक c;

	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):tx_ready(%s)\n", __खाता__, __LINE__, info->device_name);

	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		अगर (!info->tx_active)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (tty && (tty->stopped || tty->hw_stopped)) अणु
			tx_stop(info);
			वापस;
		पूर्ण
		अगर (!info->tx_count)
			info->tx_active = false;
	पूर्ण

	अगर (!info->tx_count)
		वापस;

	जबतक (info->tx_count && fअगरo_count) अणु
		c = min(2, min_t(पूर्णांक, fअगरo_count, min(info->tx_count, TXबफ_मानE - info->tx_get)));

		अगर (c == 1) अणु
			ग_लिखो_reg(info, CHA + TXFIFO, *(info->tx_buf + info->tx_get));
		पूर्ण अन्यथा अणु
			ग_लिखो_reg16(info, CHA + TXFIFO,
					  *((अचिन्हित लघु*)(info->tx_buf + info->tx_get)));
		पूर्ण
		info->tx_count -= c;
		info->tx_get = (info->tx_get + c) & (TXबफ_मानE - 1);
		fअगरo_count -= c;
	पूर्ण

	अगर (info->params.mode == MGSL_MODE_ASYNC) अणु
		अगर (info->tx_count < WAKEUP_CHARS)
			info->pending_bh |= BH_TRANSMIT;
		issue_command(info, CHA, CMD_TXFIFO);
	पूर्ण अन्यथा अणु
		अगर (info->tx_count)
			issue_command(info, CHA, CMD_TXFIFO);
		अन्यथा
			issue_command(info, CHA, CMD_TXFIFO + CMD_TXEOM);
	पूर्ण
पूर्ण

अटल व्योम cts_change(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	get_संकेतs(info);
	अगर ((info->cts_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
		irq_disable(info, CHB, IRQ_CTS);
	info->icount.cts++;
	अगर (info->serial_संकेतs & SerialSignal_CTS)
		info->input_संकेत_events.cts_up++;
	अन्यथा
		info->input_संकेत_events.cts_करोwn++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);

	अगर (tty && tty_port_cts_enabled(&info->port)) अणु
		अगर (tty->hw_stopped) अणु
			अगर (info->serial_संकेतs & SerialSignal_CTS) अणु
				अगर (debug_level >= DEBUG_LEVEL_ISR)
					prपूर्णांकk("CTS tx start...");
				tty->hw_stopped = 0;
				tx_start(info, tty);
				info->pending_bh |= BH_TRANSMIT;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(info->serial_संकेतs & SerialSignal_CTS)) अणु
				अगर (debug_level >= DEBUG_LEVEL_ISR)
					prपूर्णांकk("CTS tx stop...");
				tty->hw_stopped = 1;
				tx_stop(info);
			पूर्ण
		पूर्ण
	पूर्ण
	info->pending_bh |= BH_STATUS;
पूर्ण

अटल व्योम dcd_change(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	get_संकेतs(info);
	अगर ((info->dcd_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
		irq_disable(info, CHB, IRQ_DCD);
	info->icount.dcd++;
	अगर (info->serial_संकेतs & SerialSignal_DCD) अणु
		info->input_संकेत_events.dcd_up++;
	पूर्ण
	अन्यथा
		info->input_संकेत_events.dcd_करोwn++;
#अगर SYNCLINK_GENERIC_HDLC
	अगर (info->netcount) अणु
		अगर (info->serial_संकेतs & SerialSignal_DCD)
			netअगर_carrier_on(info->netdev);
		अन्यथा
			netअगर_carrier_off(info->netdev);
	पूर्ण
#पूर्ण_अगर
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);

	अगर (tty_port_check_carrier(&info->port)) अणु
		अगर (debug_level >= DEBUG_LEVEL_ISR)
			prपूर्णांकk("%s CD now %s...", info->device_name,
			       (info->serial_संकेतs & SerialSignal_DCD) ? "on" : "off");
		अगर (info->serial_संकेतs & SerialSignal_DCD)
			wake_up_पूर्णांकerruptible(&info->port.खोलो_रुको);
		अन्यथा अणु
			अगर (debug_level >= DEBUG_LEVEL_ISR)
				prपूर्णांकk("doing serial hangup...");
			अगर (tty)
				tty_hangup(tty);
		पूर्ण
	पूर्ण
	info->pending_bh |= BH_STATUS;
पूर्ण

अटल व्योम dsr_change(MGSLPC_INFO *info)
अणु
	get_संकेतs(info);
	अगर ((info->dsr_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
		port_irq_disable(info, PVR_DSR);
	info->icount.dsr++;
	अगर (info->serial_संकेतs & SerialSignal_DSR)
		info->input_संकेत_events.dsr_up++;
	अन्यथा
		info->input_संकेत_events.dsr_करोwn++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;
पूर्ण

अटल व्योम ri_change(MGSLPC_INFO *info)
अणु
	get_संकेतs(info);
	अगर ((info->ri_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
		port_irq_disable(info, PVR_RI);
	info->icount.rng++;
	अगर (info->serial_संकेतs & SerialSignal_RI)
		info->input_संकेत_events.ri_up++;
	अन्यथा
		info->input_संकेत_events.ri_करोwn++;
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);
	info->pending_bh |= BH_STATUS;
पूर्ण

/* Interrupt service routine entry poपूर्णांक.
 *
 * Arguments:
 *
 * irq     पूर्णांकerrupt number that caused पूर्णांकerrupt
 * dev_id  device ID supplied during पूर्णांकerrupt registration
 */
अटल irqवापस_t mgslpc_isr(पूर्णांक dummy, व्योम *dev_id)
अणु
	MGSLPC_INFO *info = dev_id;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित लघु isr;
	अचिन्हित अक्षर gis, pis;
	पूर्णांक count=0;

	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("mgslpc_isr(%d) entry.\n", info->irq_level);

	अगर (!(info->p_dev->_locked))
		वापस IRQ_HANDLED;

	tty = tty_port_tty_get(&info->port);

	spin_lock(&info->lock);

	जबतक ((gis = पढ़ो_reg(info, CHA + GIS))) अणु
		अगर (debug_level >= DEBUG_LEVEL_ISR)
			prपूर्णांकk("mgslpc_isr %s gis=%04X\n", info->device_name,gis);

		अगर ((gis & 0x70) || count > 1000) अणु
			prपूर्णांकk("synclink_cs:hardware failed or ejected\n");
			अवरोध;
		पूर्ण
		count++;

		अगर (gis & (BIT1 | BIT0)) अणु
			isr = पढ़ो_reg16(info, CHB + ISR);
			अगर (isr & IRQ_DCD)
				dcd_change(info, tty);
			अगर (isr & IRQ_CTS)
				cts_change(info, tty);
		पूर्ण
		अगर (gis & (BIT3 | BIT2))
		अणु
			isr = पढ़ो_reg16(info, CHA + ISR);
			अगर (isr & IRQ_TIMER) अणु
				info->irq_occurred = true;
				irq_disable(info, CHA, IRQ_TIMER);
			पूर्ण

			/* receive IRQs */
			अगर (isr & IRQ_EXITHUNT) अणु
				info->icount.निकासhunt++;
				wake_up_पूर्णांकerruptible(&info->event_रुको_q);
			पूर्ण
			अगर (isr & IRQ_BREAK_ON) अणु
				info->icount.brk++;
				अगर (info->port.flags & ASYNC_SAK)
					करो_SAK(tty);
			पूर्ण
			अगर (isr & IRQ_RXTIME) अणु
				issue_command(info, CHA, CMD_RXFIFO_READ);
			पूर्ण
			अगर (isr & (IRQ_RXEOM | IRQ_RXFIFO)) अणु
				अगर (info->params.mode == MGSL_MODE_HDLC)
					rx_पढ़ोy_hdlc(info, isr & IRQ_RXEOM);
				अन्यथा
					rx_पढ़ोy_async(info, isr & IRQ_RXEOM);
			पूर्ण

			/* transmit IRQs */
			अगर (isr & IRQ_UNDERRUN) अणु
				अगर (info->tx_पातing)
					info->icount.txपात++;
				अन्यथा
					info->icount.txunder++;
				tx_करोne(info, tty);
			पूर्ण
			अन्यथा अगर (isr & IRQ_ALLSENT) अणु
				info->icount.txok++;
				tx_करोne(info, tty);
			पूर्ण
			अन्यथा अगर (isr & IRQ_TXFIFO)
				tx_पढ़ोy(info, tty);
		पूर्ण
		अगर (gis & BIT7) अणु
			pis = पढ़ो_reg(info, CHA + PIS);
			अगर (pis & BIT1)
				dsr_change(info);
			अगर (pis & BIT2)
				ri_change(info);
		पूर्ण
	पूर्ण

	/* Request bottom half processing अगर there's something
	 * क्रम it to करो and the bh is not alपढ़ोy running
	 */

	अगर (info->pending_bh && !info->bh_running && !info->bh_requested) अणु
		अगर (debug_level >= DEBUG_LEVEL_ISR)
			prपूर्णांकk("%s(%d):%s queueing bh task.\n",
				__खाता__,__LINE__,info->device_name);
		schedule_work(&info->task);
		info->bh_requested = true;
	पूर्ण

	spin_unlock(&info->lock);
	tty_kref_put(tty);

	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):mgslpc_isr(%d)exit.\n",
		       __खाता__, __LINE__, info->irq_level);

	वापस IRQ_HANDLED;
पूर्ण

/* Initialize and start device.
 */
अटल पूर्णांक startup(MGSLPC_INFO * info, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक retval = 0;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):startup(%s)\n", __खाता__, __LINE__, info->device_name);

	अगर (tty_port_initialized(&info->port))
		वापस 0;

	अगर (!info->tx_buf) अणु
		/* allocate a page of memory क्रम a transmit buffer */
		info->tx_buf = (अचिन्हित अक्षर *)get_zeroed_page(GFP_KERNEL);
		अगर (!info->tx_buf) अणु
			prपूर्णांकk(KERN_ERR"%s(%d):%s can't allocate transmit buffer\n",
				__खाता__, __LINE__, info->device_name);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	info->pending_bh = 0;

	स_रखो(&info->icount, 0, माप(info->icount));

	समयr_setup(&info->tx_समयr, tx_समयout, 0);

	/* Allocate and claim adapter resources */
	retval = claim_resources(info);

	/* perक्रमm existence check and diagnostics */
	अगर (!retval)
		retval = adapter_test(info);

	अगर (retval) अणु
		अगर (capable(CAP_SYS_ADMIN) && tty)
			set_bit(TTY_IO_ERROR, &tty->flags);
		release_resources(info);
		वापस retval;
	पूर्ण

	/* program hardware क्रम current parameters */
	mgslpc_change_params(info, tty);

	अगर (tty)
		clear_bit(TTY_IO_ERROR, &tty->flags);

	tty_port_set_initialized(&info->port, 1);

	वापस 0;
पूर्ण

/* Called by mgslpc_बंद() and mgslpc_hangup() to shutकरोwn hardware
 */
अटल व्योम shutकरोwn(MGSLPC_INFO * info, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!tty_port_initialized(&info->port))
		वापस;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_shutdown(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	/* clear status रुको queue because status changes */
	/* can't happen after shutting करोwn the hardware */
	wake_up_पूर्णांकerruptible(&info->status_event_रुको_q);
	wake_up_पूर्णांकerruptible(&info->event_रुको_q);

	del_समयr_sync(&info->tx_समयr);

	अगर (info->tx_buf) अणु
		मुक्त_page((अचिन्हित दीर्घ) info->tx_buf);
		info->tx_buf = शून्य;
	पूर्ण

	spin_lock_irqsave(&info->lock, flags);

	rx_stop(info);
	tx_stop(info);

	/* TODO:disable पूर्णांकerrupts instead of reset to preserve संकेत states */
	reset_device(info);

	अगर (!tty || C_HUPCL(tty)) अणु
		info->serial_संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
		set_संकेतs(info);
	पूर्ण

	spin_unlock_irqrestore(&info->lock, flags);

	release_resources(info);

	अगर (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);

	tty_port_set_initialized(&info->port, 0);
पूर्ण

अटल व्योम mgslpc_program_hw(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);

	rx_stop(info);
	tx_stop(info);
	info->tx_count = info->tx_put = info->tx_get = 0;

	अगर (info->params.mode == MGSL_MODE_HDLC || info->netcount)
		hdlc_mode(info);
	अन्यथा
		async_mode(info);

	set_संकेतs(info);

	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;

	irq_enable(info, CHB, IRQ_DCD | IRQ_CTS);
	port_irq_enable(info, (अचिन्हित अक्षर) PVR_DSR | PVR_RI);
	get_संकेतs(info);

	अगर (info->netcount || (tty && C_CREAD(tty)))
		rx_start(info);

	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

/* Reconfigure adapter based on new parameters
 */
अटल व्योम mgslpc_change_params(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित cflag;
	पूर्णांक bits_per_अक्षर;

	अगर (!tty)
		वापस;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_change_params(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	cflag = tty->termios.c_cflag;

	/* अगर B0 rate (hangup) specअगरied then negate RTS and DTR */
	/* otherwise निश्चित RTS and DTR */
	अगर (cflag & CBAUD)
		info->serial_संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	अन्यथा
		info->serial_संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);

	/* byte size and parity */

	चयन (cflag & CSIZE) अणु
	हाल CS5: info->params.data_bits = 5; अवरोध;
	हाल CS6: info->params.data_bits = 6; अवरोध;
	हाल CS7: info->params.data_bits = 7; अवरोध;
	हाल CS8: info->params.data_bits = 8; अवरोध;
	शेष:  info->params.data_bits = 7; अवरोध;
	पूर्ण

	अगर (cflag & CSTOPB)
		info->params.stop_bits = 2;
	अन्यथा
		info->params.stop_bits = 1;

	info->params.parity = ASYNC_PARITY_NONE;
	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD)
			info->params.parity = ASYNC_PARITY_ODD;
		अन्यथा
			info->params.parity = ASYNC_PARITY_EVEN;
#अगर_घोषित CMSPAR
		अगर (cflag & CMSPAR)
			info->params.parity = ASYNC_PARITY_SPACE;
#पूर्ण_अगर
	पूर्ण

	/* calculate number of jअगरfies to transmit a full
	 * FIFO (32 bytes) at specअगरied data rate
	 */
	bits_per_अक्षर = info->params.data_bits +
			info->params.stop_bits + 1;

	/* अगर port data rate is set to 460800 or less then
	 * allow tty settings to override, otherwise keep the
	 * current data rate.
	 */
	अगर (info->params.data_rate <= 460800) अणु
		info->params.data_rate = tty_get_baud_rate(tty);
	पूर्ण

	अगर (info->params.data_rate) अणु
		info->समयout = (32*HZ*bits_per_अक्षर) /
				info->params.data_rate;
	पूर्ण
	info->समयout += HZ/50;		/* Add .02 seconds of slop */

	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);

	/* process tty input control flags */

	info->पढ़ो_status_mask = 0;
	अगर (I_INPCK(tty))
		info->पढ़ो_status_mask |= BIT7 | BIT6;
	अगर (I_IGNPAR(tty))
		info->ignore_status_mask |= BIT7 | BIT6;

	mgslpc_program_hw(info, tty);
पूर्ण

/* Add a अक्षरacter to the transmit buffer
 */
अटल पूर्णांक mgslpc_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO) अणु
		prपूर्णांकk("%s(%d):mgslpc_put_char(%d) on %s\n",
			__खाता__, __LINE__, ch, info->device_name);
	पूर्ण

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_put_char"))
		वापस 0;

	अगर (!info->tx_buf)
		वापस 0;

	spin_lock_irqsave(&info->lock, flags);

	अगर (info->params.mode == MGSL_MODE_ASYNC || !info->tx_active) अणु
		अगर (info->tx_count < TXबफ_मानE - 1) अणु
			info->tx_buf[info->tx_put++] = ch;
			info->tx_put &= TXबफ_मानE-1;
			info->tx_count++;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&info->lock, flags);
	वापस 1;
पूर्ण

/* Enable transmitter so reमुख्यing अक्षरacters in the
 * transmit buffer are sent.
 */
अटल व्योम mgslpc_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_flush_chars() entry on %s tx_count=%d\n",
			__खाता__, __LINE__, info->device_name, info->tx_count);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_flush_chars"))
		वापस;

	अगर (info->tx_count <= 0 || tty->stopped ||
	    tty->hw_stopped || !info->tx_buf)
		वापस;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_flush_chars() entry on %s starting transmitter\n",
			__खाता__, __LINE__, info->device_name);

	spin_lock_irqsave(&info->lock, flags);
	अगर (!info->tx_active)
		tx_start(info, tty);
	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

/* Send a block of data
 *
 * Arguments:
 *
 * tty        poपूर्णांकer to tty inक्रमmation काष्ठाure
 * buf	      poपूर्णांकer to buffer containing send data
 * count      size of send data in bytes
 *
 * Returns: number of अक्षरacters written
 */
अटल पूर्णांक mgslpc_ग_लिखो(काष्ठा tty_काष्ठा * tty,
			स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक c, ret = 0;
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_write(%s) count=%d\n",
			__खाता__, __LINE__, info->device_name, count);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_write") ||
		!info->tx_buf)
		जाओ cleanup;

	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		अगर (count > TXबफ_मानE) अणु
			ret = -EIO;
			जाओ cleanup;
		पूर्ण
		अगर (info->tx_active)
			जाओ cleanup;
		अन्यथा अगर (info->tx_count)
			जाओ start;
	पूर्ण

	क्रम (;;) अणु
		c = min(count,
			min(TXबफ_मानE - info->tx_count - 1,
			    TXबफ_मानE - info->tx_put));
		अगर (c <= 0)
			अवरोध;

		स_नकल(info->tx_buf + info->tx_put, buf, c);

		spin_lock_irqsave(&info->lock, flags);
		info->tx_put = (info->tx_put + c) & (TXबफ_मानE-1);
		info->tx_count += c;
		spin_unlock_irqrestore(&info->lock, flags);

		buf += c;
		count -= c;
		ret += c;
	पूर्ण
start:
	अगर (info->tx_count && !tty->stopped && !tty->hw_stopped) अणु
		spin_lock_irqsave(&info->lock, flags);
		अगर (!info->tx_active)
			tx_start(info, tty);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण
cleanup:
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_write(%s) returning=%d\n",
			__खाता__, __LINE__, info->device_name, ret);
	वापस ret;
पूर्ण

/* Return the count of मुक्त bytes in transmit buffer
 */
अटल पूर्णांक mgslpc_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	पूर्णांक ret;

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_write_room"))
		वापस 0;

	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		/* HDLC (frame oriented) mode */
		अगर (info->tx_active)
			वापस 0;
		अन्यथा
			वापस HDLC_MAX_FRAME_SIZE;
	पूर्ण अन्यथा अणु
		ret = TXबफ_मानE - info->tx_count - 1;
		अगर (ret < 0)
			ret = 0;
	पूर्ण

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_write_room(%s)=%d\n",
			 __खाता__, __LINE__, info->device_name, ret);
	वापस ret;
पूर्ण

/* Return the count of bytes in transmit buffer
 */
अटल पूर्णांक mgslpc_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	पूर्णांक rc;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_chars_in_buffer(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_chars_in_buffer"))
		वापस 0;

	अगर (info->params.mode == MGSL_MODE_HDLC)
		rc = info->tx_active ? info->max_frame_size : 0;
	अन्यथा
		rc = info->tx_count;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_chars_in_buffer(%s)=%d\n",
			 __खाता__, __LINE__, info->device_name, rc);

	वापस rc;
पूर्ण

/* Discard all data in the send buffer
 */
अटल व्योम mgslpc_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_flush_buffer(%s) entry\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_flush_buffer"))
		वापस;

	spin_lock_irqsave(&info->lock, flags);
	info->tx_count = info->tx_put = info->tx_get = 0;
	del_समयr(&info->tx_समयr);
	spin_unlock_irqrestore(&info->lock, flags);

	wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);
	tty_wakeup(tty);
पूर्ण

/* Send a high-priority XON/XOFF अक्षरacter
 */
अटल व्योम mgslpc_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_send_xchar(%s,%d)\n",
			 __खाता__, __LINE__, info->device_name, ch);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_send_xchar"))
		वापस;

	info->x_अक्षर = ch;
	अगर (ch) अणु
		spin_lock_irqsave(&info->lock, flags);
		अगर (!info->tx_enabled)
			tx_start(info, tty);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण
पूर्ण

/* Signal remote device to throttle send data (our receive data)
 */
अटल व्योम mgslpc_throttle(काष्ठा tty_काष्ठा * tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_throttle(%s) entry\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_throttle"))
		वापस;

	अगर (I_IXOFF(tty))
		mgslpc_send_xअक्षर(tty, STOP_CHAR(tty));

	अगर (C_CRTSCTS(tty)) अणु
		spin_lock_irqsave(&info->lock, flags);
		info->serial_संकेतs &= ~SerialSignal_RTS;
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण
पूर्ण

/* Signal remote device to stop throttling send data (our receive data)
 */
अटल व्योम mgslpc_unthrottle(काष्ठा tty_काष्ठा * tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_unthrottle(%s) entry\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_unthrottle"))
		वापस;

	अगर (I_IXOFF(tty)) अणु
		अगर (info->x_अक्षर)
			info->x_अक्षर = 0;
		अन्यथा
			mgslpc_send_xअक्षर(tty, START_CHAR(tty));
	पूर्ण

	अगर (C_CRTSCTS(tty)) अणु
		spin_lock_irqsave(&info->lock, flags);
		info->serial_संकेतs |= SerialSignal_RTS;
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण
पूर्ण

/* get the current serial statistics
 */
अटल पूर्णांक get_stats(MGSLPC_INFO * info, काष्ठा mgsl_icount __user *user_icount)
अणु
	पूर्णांक err;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("get_params(%s)\n", info->device_name);
	अगर (!user_icount) अणु
		स_रखो(&info->icount, 0, माप(info->icount));
	पूर्ण अन्यथा अणु
		COPY_TO_USER(err, user_icount, &info->icount, माप(काष्ठा mgsl_icount));
		अगर (err)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/* get the current serial parameters
 */
अटल पूर्णांक get_params(MGSLPC_INFO * info, MGSL_PARAMS __user *user_params)
अणु
	पूर्णांक err;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("get_params(%s)\n", info->device_name);
	COPY_TO_USER(err,user_params, &info->params, माप(MGSL_PARAMS));
	अगर (err)
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* set the serial parameters
 *
 * Arguments:
 *
 *	info		poपूर्णांकer to device instance data
 *	new_params	user buffer containing new serial params
 *
 * Returns:	0 अगर success, otherwise error code
 */
अटल पूर्णांक set_params(MGSLPC_INFO * info, MGSL_PARAMS __user *new_params, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	MGSL_PARAMS पंचांगp_params;
	पूर्णांक err;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):set_params %s\n", __खाता__,__LINE__,
			info->device_name);
	COPY_FROM_USER(err,&पंचांगp_params, new_params, माप(MGSL_PARAMS));
	अगर (err) अणु
		अगर (debug_level >= DEBUG_LEVEL_INFO)
			prपूर्णांकk("%s(%d):set_params(%s) user buffer copy failed\n",
				__खाता__, __LINE__, info->device_name);
		वापस -EFAULT;
	पूर्ण

	spin_lock_irqsave(&info->lock, flags);
	स_नकल(&info->params,&पंचांगp_params,माप(MGSL_PARAMS));
	spin_unlock_irqrestore(&info->lock, flags);

	mgslpc_change_params(info, tty);

	वापस 0;
पूर्ण

अटल पूर्णांक get_txidle(MGSLPC_INFO * info, पूर्णांक __user *idle_mode)
अणु
	पूर्णांक err;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("get_txidle(%s)=%d\n", info->device_name, info->idle_mode);
	COPY_TO_USER(err,idle_mode, &info->idle_mode, माप(पूर्णांक));
	अगर (err)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक set_txidle(MGSLPC_INFO * info, पूर्णांक idle_mode)
अणु
	अचिन्हित दीर्घ flags;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("set_txidle(%s,%d)\n", info->device_name, idle_mode);
	spin_lock_irqsave(&info->lock, flags);
	info->idle_mode = idle_mode;
	tx_set_idle(info);
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक get_पूर्णांकerface(MGSLPC_INFO * info, पूर्णांक __user *अगर_mode)
अणु
	पूर्णांक err;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("get_interface(%s)=%d\n", info->device_name, info->अगर_mode);
	COPY_TO_USER(err,अगर_mode, &info->अगर_mode, माप(पूर्णांक));
	अगर (err)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक set_पूर्णांकerface(MGSLPC_INFO * info, पूर्णांक अगर_mode)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val;
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("set_interface(%s,%d)\n", info->device_name, अगर_mode);
	spin_lock_irqsave(&info->lock, flags);
	info->अगर_mode = अगर_mode;

	val = पढ़ो_reg(info, PVR) & 0x0f;
	चयन (info->अगर_mode)
	अणु
	हाल MGSL_INTERFACE_RS232: val |= PVR_RS232; अवरोध;
	हाल MGSL_INTERFACE_V35:   val |= PVR_V35;   अवरोध;
	हाल MGSL_INTERFACE_RS422: val |= PVR_RS422; अवरोध;
	पूर्ण
	ग_लिखो_reg(info, PVR, val);

	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक set_txenable(MGSLPC_INFO * info, पूर्णांक enable, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("set_txenable(%s,%d)\n", info->device_name, enable);

	spin_lock_irqsave(&info->lock, flags);
	अगर (enable) अणु
		अगर (!info->tx_enabled)
			tx_start(info, tty);
	पूर्ण अन्यथा अणु
		अगर (info->tx_enabled)
			tx_stop(info);
	पूर्ण
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक tx_पात(MGSLPC_INFO * info)
अणु
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("tx_abort(%s)\n", info->device_name);

	spin_lock_irqsave(&info->lock, flags);
	अगर (info->tx_active && info->tx_count &&
	    info->params.mode == MGSL_MODE_HDLC) अणु
		/* clear data count so FIFO is not filled on next IRQ.
		 * This results in underrun and पात transmission.
		 */
		info->tx_count = info->tx_put = info->tx_get = 0;
		info->tx_पातing = true;
	पूर्ण
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक set_rxenable(MGSLPC_INFO * info, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("set_rxenable(%s,%d)\n", info->device_name, enable);

	spin_lock_irqsave(&info->lock, flags);
	अगर (enable) अणु
		अगर (!info->rx_enabled)
			rx_start(info);
	पूर्ण अन्यथा अणु
		अगर (info->rx_enabled)
			rx_stop(info);
	पूर्ण
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

/* रुको क्रम specअगरied event to occur
 *
 * Arguments:		info	poपूर्णांकer to device instance data
 *			mask	poपूर्णांकer to biपंचांगask of events to रुको क्रम
 * Return Value:	0	अगर successful and bit mask updated with
 *				of events triggerred,
 *			otherwise error code
 */
अटल पूर्णांक रुको_events(MGSLPC_INFO * info, पूर्णांक __user *mask_ptr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक s;
	पूर्णांक rc=0;
	काष्ठा mgsl_icount cprev, cnow;
	पूर्णांक events;
	पूर्णांक mask;
	काष्ठा	_input_संकेत_events oldsigs, newsigs;
	DECLARE_WAITQUEUE(रुको, current);

	COPY_FROM_USER(rc,&mask, mask_ptr, माप(पूर्णांक));
	अगर (rc)
		वापस  -EFAULT;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("wait_events(%s,%d)\n", info->device_name, mask);

	spin_lock_irqsave(&info->lock, flags);

	/* वापस immediately अगर state matches requested events */
	get_संकेतs(info);
	s = info->serial_संकेतs;
	events = mask &
		( ((s & SerialSignal_DSR) ? MgslEvent_DsrActive:MgslEvent_DsrInactive) +
		  ((s & SerialSignal_DCD) ? MgslEvent_DcdActive:MgslEvent_DcdInactive) +
		  ((s & SerialSignal_CTS) ? MgslEvent_CtsActive:MgslEvent_CtsInactive) +
		  ((s & SerialSignal_RI)  ? MgslEvent_RiActive :MgslEvent_RiInactive) );
	अगर (events) अणु
		spin_unlock_irqrestore(&info->lock, flags);
		जाओ निकास;
	पूर्ण

	/* save current irq counts */
	cprev = info->icount;
	oldsigs = info->input_संकेत_events;

	अगर ((info->params.mode == MGSL_MODE_HDLC) &&
	    (mask & MgslEvent_ExitHuntMode))
		irq_enable(info, CHA, IRQ_EXITHUNT);

	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&info->event_रुको_q, &रुको);

	spin_unlock_irqrestore(&info->lock, flags);


	क्रम(;;) अणु
		schedule();
		अगर (संकेत_pending(current)) अणु
			rc = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/* get current irq counts */
		spin_lock_irqsave(&info->lock, flags);
		cnow = info->icount;
		newsigs = info->input_संकेत_events;
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&info->lock, flags);

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

	अगर (mask & MgslEvent_ExitHuntMode) अणु
		spin_lock_irqsave(&info->lock, flags);
		अगर (!रुकोqueue_active(&info->event_रुको_q))
			irq_disable(info, CHA, IRQ_EXITHUNT);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण
निकास:
	अगर (rc == 0)
		PUT_USER(rc, events, mask_ptr);
	वापस rc;
पूर्ण

अटल पूर्णांक modem_input_रुको(MGSLPC_INFO *info,पूर्णांक arg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	काष्ठा mgsl_icount cprev, cnow;
	DECLARE_WAITQUEUE(रुको, current);

	/* save current irq counts */
	spin_lock_irqsave(&info->lock, flags);
	cprev = info->icount;
	add_रुको_queue(&info->status_event_रुको_q, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	spin_unlock_irqrestore(&info->lock, flags);

	क्रम(;;) अणु
		schedule();
		अगर (संकेत_pending(current)) अणु
			rc = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/* get new irq counts */
		spin_lock_irqsave(&info->lock, flags);
		cnow = info->icount;
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&info->lock, flags);

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

/* वापस the state of the serial control and status संकेतs
 */
अटल पूर्णांक tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);

	result = ((info->serial_संकेतs & SerialSignal_RTS) ? TIOCM_RTS:0) +
		((info->serial_संकेतs & SerialSignal_DTR) ? TIOCM_DTR:0) +
		((info->serial_संकेतs & SerialSignal_DCD) ? TIOCM_CAR:0) +
		((info->serial_संकेतs & SerialSignal_RI)  ? TIOCM_RNG:0) +
		((info->serial_संकेतs & SerialSignal_DSR) ? TIOCM_DSR:0) +
		((info->serial_संकेतs & SerialSignal_CTS) ? TIOCM_CTS:0);

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):%s tiocmget() value=%08X\n",
			 __खाता__, __LINE__, info->device_name, result);
	वापस result;
पूर्ण

/* set modem control संकेतs (DTR/RTS)
 */
अटल पूर्णांक tiocmset(काष्ठा tty_काष्ठा *tty,
		    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):%s tiocmset(%x,%x)\n",
			__खाता__, __LINE__, info->device_name, set, clear);

	अगर (set & TIOCM_RTS)
		info->serial_संकेतs |= SerialSignal_RTS;
	अगर (set & TIOCM_DTR)
		info->serial_संकेतs |= SerialSignal_DTR;
	अगर (clear & TIOCM_RTS)
		info->serial_संकेतs &= ~SerialSignal_RTS;
	अगर (clear & TIOCM_DTR)
		info->serial_संकेतs &= ~SerialSignal_DTR;

	spin_lock_irqsave(&info->lock, flags);
	set_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);

	वापस 0;
पूर्ण

/* Set or clear transmit अवरोध condition
 *
 * Arguments:		tty		poपूर्णांकer to tty instance data
 *			अवरोध_state	-1=set अवरोध condition, 0=clear
 */
अटल पूर्णांक mgslpc_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_break(%s,%d)\n",
			 __खाता__, __LINE__, info->device_name, अवरोध_state);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_break"))
		वापस -EINVAL;

	spin_lock_irqsave(&info->lock, flags);
	अगर (अवरोध_state == -1)
		set_reg_bits(info, CHA+DAFO, BIT6);
	अन्यथा
		clear_reg_bits(info, CHA+DAFO, BIT6);
	spin_unlock_irqrestore(&info->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक mgslpc_get_icount(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	काष्ठा mgsl_icount cnow;	/* kernel counter temps */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	cnow = info->icount;
	spin_unlock_irqrestore(&info->lock, flags);

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

/* Service an IOCTL request
 *
 * Arguments:
 *
 *	tty	poपूर्णांकer to tty instance data
 *	cmd	IOCTL command code
 *	arg	command argument/context
 *
 * Return Value:	0 अगर success, otherwise error code
 */
अटल पूर्णांक mgslpc_ioctl(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_ioctl %s cmd=%08X\n", __खाता__, __LINE__,
			info->device_name, cmd);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_ioctl"))
		वापस -ENODEV;

	अगर (cmd != TIOCMIWAIT) अणु
		अगर (tty_io_error(tty))
		    वापस -EIO;
	पूर्ण

	चयन (cmd) अणु
	हाल MGSL_IOCGPARAMS:
		वापस get_params(info, argp);
	हाल MGSL_IOCSPARAMS:
		वापस set_params(info, argp, tty);
	हाल MGSL_IOCGTXIDLE:
		वापस get_txidle(info, argp);
	हाल MGSL_IOCSTXIDLE:
		वापस set_txidle(info, (पूर्णांक)arg);
	हाल MGSL_IOCGIF:
		वापस get_पूर्णांकerface(info, argp);
	हाल MGSL_IOCSIF:
		वापस set_पूर्णांकerface(info,(पूर्णांक)arg);
	हाल MGSL_IOCTXENABLE:
		वापस set_txenable(info,(पूर्णांक)arg, tty);
	हाल MGSL_IOCRXENABLE:
		वापस set_rxenable(info,(पूर्णांक)arg);
	हाल MGSL_IOCTXABORT:
		वापस tx_पात(info);
	हाल MGSL_IOCGSTATS:
		वापस get_stats(info, argp);
	हाल MGSL_IOCWAITEVENT:
		वापस रुको_events(info, argp);
	हाल TIOCMIWAIT:
		वापस modem_input_रुको(info,(पूर्णांक)arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

/* Set new termios settings
 *
 * Arguments:
 *
 *	tty		poपूर्णांकer to tty काष्ठाure
 *	termios		poपूर्णांकer to buffer to hold वापसed old termios
 */
अटल व्योम mgslpc_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old_termios)
अणु
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_set_termios %s\n", __खाता__, __LINE__,
			tty->driver->name);

	/* just वापस अगर nothing has changed */
	अगर ((tty->termios.c_cflag == old_termios->c_cflag)
	    && (RELEVANT_IFLAG(tty->termios.c_अगरlag)
		== RELEVANT_IFLAG(old_termios->c_अगरlag)))
	  वापस;

	mgslpc_change_params(info, tty);

	/* Handle transition to B0 status */
	अगर ((old_termios->c_cflag & CBAUD) && !C_BAUD(tty)) अणु
		info->serial_संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
		spin_lock_irqsave(&info->lock, flags);
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण

	/* Handle transition away from B0 status */
	अगर (!(old_termios->c_cflag & CBAUD) && C_BAUD(tty)) अणु
		info->serial_संकेतs |= SerialSignal_DTR;
		अगर (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->serial_संकेतs |= SerialSignal_RTS;
		spin_lock_irqsave(&info->lock, flags);
		set_संकेतs(info);
		spin_unlock_irqrestore(&info->lock, flags);
	पूर्ण

	/* Handle turning off CRTSCTS */
	अगर (old_termios->c_cflag & CRTSCTS && !C_CRTSCTS(tty)) अणु
		tty->hw_stopped = 0;
		tx_release(tty);
	पूर्ण
पूर्ण

अटल व्योम mgslpc_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	काष्ठा tty_port *port = &info->port;

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_close"))
		वापस;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_close(%s) entry, count=%d\n",
			 __खाता__, __LINE__, info->device_name, port->count);

	अगर (tty_port_बंद_start(port, tty, filp) == 0)
		जाओ cleanup;

	अगर (tty_port_initialized(port))
		mgslpc_रुको_until_sent(tty, info->समयout);

	mgslpc_flush_buffer(tty);

	tty_ldisc_flush(tty);
	shutकरोwn(info, tty);
	
	tty_port_बंद_end(port, tty);
	tty_port_tty_set(port, शून्य);
cleanup:
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_close(%s) exit, count=%d\n", __खाता__, __LINE__,
			tty->driver->name, port->count);
पूर्ण

/* Wait until the transmitter is empty.
 */
अटल व्योम mgslpc_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	अचिन्हित दीर्घ orig_jअगरfies, अक्षर_समय;

	अगर (!info)
		वापस;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_wait_until_sent(%s) entry\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_wait_until_sent"))
		वापस;

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

	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		जबतक (info->tx_active) अणु
			msleep_पूर्णांकerruptible(jअगरfies_to_msecs(अक्षर_समय));
			अगर (संकेत_pending(current))
				अवरोध;
			अगर (समयout && समय_after(jअगरfies, orig_jअगरfies + समयout))
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक ((info->tx_count || info->tx_active) &&
			info->tx_enabled) अणु
			msleep_पूर्णांकerruptible(jअगरfies_to_msecs(अक्षर_समय));
			अगर (संकेत_pending(current))
				अवरोध;
			अगर (समयout && समय_after(jअगरfies, orig_jअगरfies + समयout))
				अवरोध;
		पूर्ण
	पूर्ण

निकास:
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_wait_until_sent(%s) exit\n",
			 __खाता__, __LINE__, info->device_name);
पूर्ण

/* Called by tty_hangup() when a hangup is संकेतed.
 * This is the same as closing all खोलो files क्रम the port.
 */
अटल व्योम mgslpc_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_hangup(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_hangup"))
		वापस;

	mgslpc_flush_buffer(tty);
	shutकरोwn(info, tty);
	tty_port_hangup(&info->port);
पूर्ण

अटल पूर्णांक carrier_उठाओd(काष्ठा tty_port *port)
अणु
	MGSLPC_INFO *info = container_of(port, MGSLPC_INFO, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);

	अगर (info->serial_संकेतs & SerialSignal_DCD)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम dtr_rts(काष्ठा tty_port *port, पूर्णांक onoff)
अणु
	MGSLPC_INFO *info = container_of(port, MGSLPC_INFO, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	अगर (onoff)
		info->serial_संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	अन्यथा
		info->serial_संकेतs &= ~(SerialSignal_RTS | SerialSignal_DTR);
	set_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);
पूर्ण


अटल पूर्णांक mgslpc_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	MGSLPC_INFO	*info;
	काष्ठा tty_port *port;
	पूर्णांक		retval, line;
	अचिन्हित दीर्घ	flags;

	/* verअगरy range of specअगरied line number */
	line = tty->index;
	अगर (line >= mgslpc_device_count) अणु
		prपूर्णांकk("%s(%d):mgslpc_open with invalid line #%d.\n",
			__खाता__, __LINE__, line);
		वापस -ENODEV;
	पूर्ण

	/* find the info काष्ठाure क्रम the specअगरied line */
	info = mgslpc_device_list;
	जबतक(info && info->line != line)
		info = info->next_device;
	अगर (mgslpc_paranoia_check(info, tty->name, "mgslpc_open"))
		वापस -ENODEV;

	port = &info->port;
	tty->driver_data = info;
	tty_port_tty_set(port, tty);

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_open(%s), old ref count = %d\n",
			 __खाता__, __LINE__, tty->driver->name, port->count);

	spin_lock_irqsave(&info->netlock, flags);
	अगर (info->netcount) अणु
		retval = -EBUSY;
		spin_unlock_irqrestore(&info->netlock, flags);
		जाओ cleanup;
	पूर्ण
	spin_lock(&port->lock);
	port->count++;
	spin_unlock(&port->lock);
	spin_unlock_irqrestore(&info->netlock, flags);

	अगर (port->count == 1) अणु
		/* 1st खोलो on this device, init hardware */
		retval = startup(info, tty);
		अगर (retval < 0)
			जाओ cleanup;
	पूर्ण

	retval = tty_port_block_til_पढ़ोy(&info->port, tty, filp);
	अगर (retval) अणु
		अगर (debug_level >= DEBUG_LEVEL_INFO)
			prपूर्णांकk("%s(%d):block_til_ready(%s) returned %d\n",
				 __खाता__, __LINE__, info->device_name, retval);
		जाओ cleanup;
	पूर्ण

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):mgslpc_open(%s) success\n",
			 __खाता__, __LINE__, info->device_name);
	retval = 0;

cleanup:
	वापस retval;
पूर्ण

/*
 * /proc fs routines....
 */

अटल अंतरभूत व्योम line_info(काष्ठा seq_file *m, MGSLPC_INFO *info)
अणु
	अक्षर	stat_buf[30];
	अचिन्हित दीर्घ flags;

	seq_म_लिखो(m, "%s:io:%04X irq:%d",
		      info->device_name, info->io_base, info->irq_level);

	/* output current serial संकेत states */
	spin_lock_irqsave(&info->lock, flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);

	stat_buf[0] = 0;
	stat_buf[1] = 0;
	अगर (info->serial_संकेतs & SerialSignal_RTS)
		म_जोड़ो(stat_buf, "|RTS");
	अगर (info->serial_संकेतs & SerialSignal_CTS)
		म_जोड़ो(stat_buf, "|CTS");
	अगर (info->serial_संकेतs & SerialSignal_DTR)
		म_जोड़ो(stat_buf, "|DTR");
	अगर (info->serial_संकेतs & SerialSignal_DSR)
		म_जोड़ो(stat_buf, "|DSR");
	अगर (info->serial_संकेतs & SerialSignal_DCD)
		म_जोड़ो(stat_buf, "|CD");
	अगर (info->serial_संकेतs & SerialSignal_RI)
		म_जोड़ो(stat_buf, "|RI");

	अगर (info->params.mode == MGSL_MODE_HDLC) अणु
		seq_म_लिखो(m, " HDLC txok:%d rxok:%d",
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
		seq_म_लिखो(m, " ASYNC tx:%d rx:%d",
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

	seq_म_लिखो(m, "txactive=%d bh_req=%d bh_run=%d pending_bh=%x\n",
		       info->tx_active,info->bh_requested,info->bh_running,
		       info->pending_bh);
पूर्ण

/* Called to prपूर्णांक inक्रमmation about devices
 */
अटल पूर्णांक mgslpc_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	MGSLPC_INFO *info;

	seq_म_लिखो(m, "synclink driver:%s\n", driver_version);

	info = mgslpc_device_list;
	जबतक (info) अणु
		line_info(m, info);
		info = info->next_device;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rx_alloc_buffers(MGSLPC_INFO *info)
अणु
	/* each buffer has header and data */
	info->rx_buf_size = माप(RXBUF) + info->max_frame_size;

	/* calculate total allocation size क्रम 8 buffers */
	info->rx_buf_total_size = info->rx_buf_size * 8;

	/* limit total allocated memory */
	अगर (info->rx_buf_total_size > 0x10000)
		info->rx_buf_total_size = 0x10000;

	/* calculate number of buffers */
	info->rx_buf_count = info->rx_buf_total_size / info->rx_buf_size;

	info->rx_buf = kदो_स्मृति(info->rx_buf_total_size, GFP_KERNEL);
	अगर (info->rx_buf == शून्य)
		वापस -ENOMEM;

	/* unused flag buffer to satisfy receive_buf calling पूर्णांकerface */
	info->flag_buf = kzalloc(info->max_frame_size, GFP_KERNEL);
	अगर (!info->flag_buf) अणु
		kमुक्त(info->rx_buf);
		info->rx_buf = शून्य;
		वापस -ENOMEM;
	पूर्ण
	
	rx_reset_buffers(info);
	वापस 0;
पूर्ण

अटल व्योम rx_मुक्त_buffers(MGSLPC_INFO *info)
अणु
	kमुक्त(info->rx_buf);
	info->rx_buf = शून्य;
	kमुक्त(info->flag_buf);
	info->flag_buf = शून्य;
पूर्ण

अटल पूर्णांक claim_resources(MGSLPC_INFO *info)
अणु
	अगर (rx_alloc_buffers(info) < 0) अणु
		prपूर्णांकk("Can't allocate rx buffer %s\n", info->device_name);
		release_resources(info);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम release_resources(MGSLPC_INFO *info)
अणु
	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("release_resources(%s)\n", info->device_name);
	rx_मुक्त_buffers(info);
पूर्ण

/* Add the specअगरied device instance data काष्ठाure to the
 * global linked list of devices and increment the device count.
 *
 * Arguments:		info	poपूर्णांकer to device instance data
 */
अटल पूर्णांक mgslpc_add_device(MGSLPC_INFO *info)
अणु
	MGSLPC_INFO *current_dev = शून्य;
	काष्ठा device *tty_dev;
	पूर्णांक ret;

	info->next_device = शून्य;
	info->line = mgslpc_device_count;
	प्र_लिखो(info->device_name,"ttySLP%d",info->line);

	अगर (info->line < MAX_DEVICE_COUNT) अणु
		अगर (maxframe[info->line])
			info->max_frame_size = maxframe[info->line];
	पूर्ण

	mgslpc_device_count++;

	अगर (!mgslpc_device_list)
		mgslpc_device_list = info;
	अन्यथा अणु
		current_dev = mgslpc_device_list;
		जबतक (current_dev->next_device)
			current_dev = current_dev->next_device;
		current_dev->next_device = info;
	पूर्ण

	अगर (info->max_frame_size < 4096)
		info->max_frame_size = 4096;
	अन्यथा अगर (info->max_frame_size > 65535)
		info->max_frame_size = 65535;

	prपूर्णांकk("SyncLink PC Card %s:IO=%04X IRQ=%d\n",
		info->device_name, info->io_base, info->irq_level);

#अगर SYNCLINK_GENERIC_HDLC
	ret = hdlcdev_init(info);
	अगर (ret != 0)
		जाओ failed;
#पूर्ण_अगर

	tty_dev = tty_port_रेजिस्टर_device(&info->port, serial_driver, info->line,
			&info->p_dev->dev);
	अगर (IS_ERR(tty_dev)) अणु
		ret = PTR_ERR(tty_dev);
#अगर SYNCLINK_GENERIC_HDLC
		hdlcdev_निकास(info);
#पूर्ण_अगर
		जाओ failed;
	पूर्ण

	वापस 0;

failed:
	अगर (current_dev)
		current_dev->next_device = शून्य;
	अन्यथा
		mgslpc_device_list = शून्य;
	mgslpc_device_count--;
	वापस ret;
पूर्ण

अटल व्योम mgslpc_हटाओ_device(MGSLPC_INFO *हटाओ_info)
अणु
	MGSLPC_INFO *info = mgslpc_device_list;
	MGSLPC_INFO *last = शून्य;

	जबतक(info) अणु
		अगर (info == हटाओ_info) अणु
			अगर (last)
				last->next_device = info->next_device;
			अन्यथा
				mgslpc_device_list = info->next_device;
			tty_unरेजिस्टर_device(serial_driver, info->line);
#अगर SYNCLINK_GENERIC_HDLC
			hdlcdev_निकास(info);
#पूर्ण_अगर
			release_resources(info);
			tty_port_destroy(&info->port);
			kमुक्त(info);
			mgslpc_device_count--;
			वापस;
		पूर्ण
		last = info;
		info = info->next_device;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id mgslpc_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x02c5, 0x0050),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, mgslpc_ids);

अटल काष्ठा pcmcia_driver mgslpc_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "synclink_cs",
	.probe		= mgslpc_probe,
	.हटाओ		= mgslpc_detach,
	.id_table	= mgslpc_ids,
	.suspend	= mgslpc_suspend,
	.resume		= mgslpc_resume,
पूर्ण;

अटल स्थिर काष्ठा tty_operations mgslpc_ops = अणु
	.खोलो = mgslpc_खोलो,
	.बंद = mgslpc_बंद,
	.ग_लिखो = mgslpc_ग_लिखो,
	.put_अक्षर = mgslpc_put_अक्षर,
	.flush_अक्षरs = mgslpc_flush_अक्षरs,
	.ग_लिखो_room = mgslpc_ग_लिखो_room,
	.अक्षरs_in_buffer = mgslpc_अक्षरs_in_buffer,
	.flush_buffer = mgslpc_flush_buffer,
	.ioctl = mgslpc_ioctl,
	.throttle = mgslpc_throttle,
	.unthrottle = mgslpc_unthrottle,
	.send_xअक्षर = mgslpc_send_xअक्षर,
	.अवरोध_ctl = mgslpc_अवरोध,
	.रुको_until_sent = mgslpc_रुको_until_sent,
	.set_termios = mgslpc_set_termios,
	.stop = tx_छोड़ो,
	.start = tx_release,
	.hangup = mgslpc_hangup,
	.tiocmget = tiocmget,
	.tiocmset = tiocmset,
	.get_icount = mgslpc_get_icount,
	.proc_show = mgslpc_proc_show,
पूर्ण;

अटल पूर्णांक __init synclink_cs_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (अवरोध_on_load) अणु
		mgslpc_get_text_ptr();
		BREAKPOINT();
	पूर्ण

	serial_driver = tty_alloc_driver(MAX_DEVICE_COUNT,
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_DEV);
	अगर (IS_ERR(serial_driver)) अणु
		rc = PTR_ERR(serial_driver);
		जाओ err;
	पूर्ण

	/* Initialize the tty_driver काष्ठाure */
	serial_driver->driver_name = "synclink_cs";
	serial_driver->name = "ttySLP";
	serial_driver->major = ttymajor;
	serial_driver->minor_start = 64;
	serial_driver->type = TTY_DRIVER_TYPE_SERIAL;
	serial_driver->subtype = SERIAL_TYPE_NORMAL;
	serial_driver->init_termios = tty_std_termios;
	serial_driver->init_termios.c_cflag =
	B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	tty_set_operations(serial_driver, &mgslpc_ops);

	rc = tty_रेजिस्टर_driver(serial_driver);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "%s(%d):Couldn't register serial driver\n",
				__खाता__, __LINE__);
		जाओ err_put_tty;
	पूर्ण

	rc = pcmcia_रेजिस्टर_driver(&mgslpc_driver);
	अगर (rc < 0)
		जाओ err_unreg_tty;

	prपूर्णांकk(KERN_INFO "%s %s, tty major#%d\n", driver_name, driver_version,
			serial_driver->major);

	वापस 0;
err_unreg_tty:
	tty_unरेजिस्टर_driver(serial_driver);
err_put_tty:
	put_tty_driver(serial_driver);
err:
	वापस rc;
पूर्ण

अटल व्योम __निकास synclink_cs_निकास(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&mgslpc_driver);
	tty_unरेजिस्टर_driver(serial_driver);
	put_tty_driver(serial_driver);
पूर्ण

module_init(synclink_cs_init);
module_निकास(synclink_cs_निकास);

अटल व्योम mgslpc_set_rate(MGSLPC_INFO *info, अचिन्हित अक्षर channel, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक M, N;
	अचिन्हित अक्षर val;

	/* note:standard BRG mode is broken in V3.2 chip
	 * so enhanced mode is always used
	 */

	अगर (rate) अणु
		N = 3686400 / rate;
		अगर (!N)
			N = 1;
		N >>= 1;
		क्रम (M = 1; N > 64 && M < 16; M++)
			N >>= 1;
		N--;

		/* BGR[5..0] = N
		 * BGR[9..6] = M
		 * BGR[7..0] contained in BGR रेजिस्टर
		 * BGR[9..8] contained in CCR2[7..6]
		 * भागisor = (N+1)*2^M
		 *
		 * Note: M *must* not be zero (causes asymetric duty cycle)
		 */
		ग_लिखो_reg(info, (अचिन्हित अक्षर) (channel + BGR),
				  (अचिन्हित अक्षर) ((M << 6) + N));
		val = पढ़ो_reg(info, (अचिन्हित अक्षर) (channel + CCR2)) & 0x3f;
		val |= ((M << 4) & 0xc0);
		ग_लिखो_reg(info, (अचिन्हित अक्षर) (channel + CCR2), val);
	पूर्ण
पूर्ण

/* Enabled the AUX घड़ी output at the specअगरied frequency.
 */
अटल व्योम enable_auxclk(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर val;

	/* MODE
	 *
	 * 07..06  MDS[1..0] 10 = transparent HDLC mode
	 * 05      ADM Address Mode, 0 = no addr recognition
	 * 04      TMD Timer Mode, 0 = बाह्यal
	 * 03      RAC Receiver Active, 0 = inactive
	 * 02      RTS 0=RTS active during xmit, 1=RTS always active
	 * 01      TRS Timer Resolution, 1=512
	 * 00      TLP Test Loop, 0 = no loop
	 *
	 * 1000 0010
	 */
	val = 0x82;

	/* channel B RTS is used to enable AUXCLK driver on SP505 */
	अगर (info->params.mode == MGSL_MODE_HDLC && info->params.घड़ी_speed)
		val |= BIT2;
	ग_लिखो_reg(info, CHB + MODE, val);

	/* CCR0
	 *
	 * 07      PU Power Up, 1=active, 0=घातer करोwn
	 * 06      MCE Master Clock Enable, 1=enabled
	 * 05      Reserved, 0
	 * 04..02  SC[2..0] Encoding
	 * 01..00  SM[1..0] Serial Mode, 00=HDLC
	 *
	 * 11000000
	 */
	ग_लिखो_reg(info, CHB + CCR0, 0xc0);

	/* CCR1
	 *
	 * 07      SFLG Shared Flag, 0 = disable shared flags
	 * 06      GALP Go Active On Loop, 0 = not used
	 * 05      GLP Go On Loop, 0 = not used
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      ITF Interframe Time Fill, 0=mark, 1=flag
	 * 02..00  CM[2..0] Clock Mode
	 *
	 * 0001 0111
	 */
	ग_लिखो_reg(info, CHB + CCR1, 0x17);

	/* CCR2 (Channel B)
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate भागisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 1=TxCLK is output
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      C32, CRC select, 0=CRC-16, 1=CRC-32
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0011 1000
	 */
	अगर (info->params.mode == MGSL_MODE_HDLC && info->params.घड़ी_speed)
		ग_लिखो_reg(info, CHB + CCR2, 0x38);
	अन्यथा
		ग_लिखो_reg(info, CHB + CCR2, 0x30);

	/* CCR4
	 *
	 * 07      MCK4 Master Clock Divide by 4, 1=enabled
	 * 06      EBRG Enhanced Baud Rate Generator Mode, 1=enabled
	 * 05      TST1 Test Pin, 0=normal operation
	 * 04      ICD Ivert Carrier Detect, 1=enabled (active low)
	 * 03..02  Reserved, must be 0
	 * 01..00  RFT[1..0] RxFIFO Threshold 00=32 bytes
	 *
	 * 0101 0000
	 */
	ग_लिखो_reg(info, CHB + CCR4, 0x50);

	/* अगर auxclk not enabled, set पूर्णांकernal BRG so
	 * CTS transitions can be detected (requires TxC)
	 */
	अगर (info->params.mode == MGSL_MODE_HDLC && info->params.घड़ी_speed)
		mgslpc_set_rate(info, CHB, info->params.घड़ी_speed);
	अन्यथा
		mgslpc_set_rate(info, CHB, 921600);
पूर्ण

अटल व्योम loopback_enable(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर val;

	/* CCR1:02..00  CM[2..0] Clock Mode = 111 (घड़ी mode 7) */
	val = पढ़ो_reg(info, CHA + CCR1) | (BIT2 | BIT1 | BIT0);
	ग_लिखो_reg(info, CHA + CCR1, val);

	/* CCR2:04 SSEL Clock source select, 1=submode b */
	val = पढ़ो_reg(info, CHA + CCR2) | (BIT4 | BIT5);
	ग_लिखो_reg(info, CHA + CCR2, val);

	/* set LinkSpeed अगर available, otherwise शेष to 2Mbps */
	अगर (info->params.घड़ी_speed)
		mgslpc_set_rate(info, CHA, info->params.घड़ी_speed);
	अन्यथा
		mgslpc_set_rate(info, CHA, 1843200);

	/* MODE:00 TLP Test Loop, 1=loopback enabled */
	val = पढ़ो_reg(info, CHA + MODE) | BIT0;
	ग_लिखो_reg(info, CHA + MODE, val);
पूर्ण

अटल व्योम hdlc_mode(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर val;
	अचिन्हित अक्षर clkmode, clksubmode;

	/* disable all पूर्णांकerrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* assume घड़ी mode 0a, rcv=RxC xmt=TxC */
	clkmode = clksubmode = 0;
	अगर (info->params.flags & HDLC_FLAG_RXC_DPLL
	    && info->params.flags & HDLC_FLAG_TXC_DPLL) अणु
		/* घड़ी mode 7a, rcv = DPLL, xmt = DPLL */
		clkmode = 7;
	पूर्ण अन्यथा अगर (info->params.flags & HDLC_FLAG_RXC_BRG
		 && info->params.flags & HDLC_FLAG_TXC_BRG) अणु
		/* घड़ी mode 7b, rcv = BRG, xmt = BRG */
		clkmode = 7;
		clksubmode = 1;
	पूर्ण अन्यथा अगर (info->params.flags & HDLC_FLAG_RXC_DPLL) अणु
		अगर (info->params.flags & HDLC_FLAG_TXC_BRG) अणु
			/* घड़ी mode 6b, rcv = DPLL, xmt = BRG/16 */
			clkmode = 6;
			clksubmode = 1;
		पूर्ण अन्यथा अणु
			/* घड़ी mode 6a, rcv = DPLL, xmt = TxC */
			clkmode = 6;
		पूर्ण
	पूर्ण अन्यथा अगर (info->params.flags & HDLC_FLAG_TXC_BRG) अणु
		/* घड़ी mode 0b, rcv = RxC, xmt = BRG */
		clksubmode = 1;
	पूर्ण

	/* MODE
	 *
	 * 07..06  MDS[1..0] 10 = transparent HDLC mode
	 * 05      ADM Address Mode, 0 = no addr recognition
	 * 04      TMD Timer Mode, 0 = बाह्यal
	 * 03      RAC Receiver Active, 0 = inactive
	 * 02      RTS 0=RTS active during xmit, 1=RTS always active
	 * 01      TRS Timer Resolution, 1=512
	 * 00      TLP Test Loop, 0 = no loop
	 *
	 * 1000 0010
	 */
	val = 0x82;
	अगर (info->params.loopback)
		val |= BIT0;

	/* preserve RTS state */
	अगर (info->serial_संकेतs & SerialSignal_RTS)
		val |= BIT2;
	ग_लिखो_reg(info, CHA + MODE, val);

	/* CCR0
	 *
	 * 07      PU Power Up, 1=active, 0=घातer करोwn
	 * 06      MCE Master Clock Enable, 1=enabled
	 * 05      Reserved, 0
	 * 04..02  SC[2..0] Encoding
	 * 01..00  SM[1..0] Serial Mode, 00=HDLC
	 *
	 * 11000000
	 */
	val = 0xc0;
	चयन (info->params.encoding)
	अणु
	हाल HDLC_ENCODING_NRZI:
		val |= BIT3;
		अवरोध;
	हाल HDLC_ENCODING_BIPHASE_SPACE:
		val |= BIT4;
		अवरोध;		// FM0
	हाल HDLC_ENCODING_BIPHASE_MARK:
		val |= BIT4 | BIT2;
		अवरोध;		// FM1
	हाल HDLC_ENCODING_BIPHASE_LEVEL:
		val |= BIT4 | BIT3;
		अवरोध;		// Manchester
	पूर्ण
	ग_लिखो_reg(info, CHA + CCR0, val);

	/* CCR1
	 *
	 * 07      SFLG Shared Flag, 0 = disable shared flags
	 * 06      GALP Go Active On Loop, 0 = not used
	 * 05      GLP Go On Loop, 0 = not used
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      ITF Interframe Time Fill, 0=mark, 1=flag
	 * 02..00  CM[2..0] Clock Mode
	 *
	 * 0001 0000
	 */
	val = 0x10 + clkmode;
	ग_लिखो_reg(info, CHA + CCR1, val);

	/* CCR2
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate भागisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 0=TxCLK is input
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      C32, CRC select, 0=CRC-16, 1=CRC-32
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0000 0000
	 */
	val = 0x00;
	अगर (clkmode == 2 || clkmode == 3 || clkmode == 6
	    || clkmode == 7 || (clkmode == 0 && clksubmode == 1))
		val |= BIT5;
	अगर (clksubmode)
		val |= BIT4;
	अगर (info->params.crc_type == HDLC_CRC_32_CCITT)
		val |= BIT1;
	अगर (info->params.encoding == HDLC_ENCODING_NRZB)
		val |= BIT0;
	ग_लिखो_reg(info, CHA + CCR2, val);

	/* CCR3
	 *
	 * 07..06  PRE[1..0] Preamble count 00=1, 01=2, 10=4, 11=8
	 * 05      EPT Enable preamble transmission, 1=enabled
	 * 04      RADD Receive address pushed to FIFO, 0=disabled
	 * 03      CRL CRC Reset Level, 0=FFFF
	 * 02      RCRC Rx CRC 0=On 1=Off
	 * 01      TCRC Tx CRC 0=On 1=Off
	 * 00      PSD DPLL Phase Shअगरt Disable
	 *
	 * 0000 0000
	 */
	val = 0x00;
	अगर (info->params.crc_type == HDLC_CRC_NONE)
		val |= BIT2 | BIT1;
	अगर (info->params.preamble != HDLC_PREAMBLE_PATTERN_NONE)
		val |= BIT5;
	चयन (info->params.preamble_length)
	अणु
	हाल HDLC_PREAMBLE_LENGTH_16BITS:
		val |= BIT6;
		अवरोध;
	हाल HDLC_PREAMBLE_LENGTH_32BITS:
		val |= BIT6;
		अवरोध;
	हाल HDLC_PREAMBLE_LENGTH_64BITS:
		val |= BIT7 | BIT6;
		अवरोध;
	पूर्ण
	ग_लिखो_reg(info, CHA + CCR3, val);

	/* PRE - Preamble pattern */
	val = 0;
	चयन (info->params.preamble)
	अणु
	हाल HDLC_PREAMBLE_PATTERN_FLAGS: val = 0x7e; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_10:    val = 0xaa; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_01:    val = 0x55; अवरोध;
	हाल HDLC_PREAMBLE_PATTERN_ONES:  val = 0xff; अवरोध;
	पूर्ण
	ग_लिखो_reg(info, CHA + PRE, val);

	/* CCR4
	 *
	 * 07      MCK4 Master Clock Divide by 4, 1=enabled
	 * 06      EBRG Enhanced Baud Rate Generator Mode, 1=enabled
	 * 05      TST1 Test Pin, 0=normal operation
	 * 04      ICD Ivert Carrier Detect, 1=enabled (active low)
	 * 03..02  Reserved, must be 0
	 * 01..00  RFT[1..0] RxFIFO Threshold 00=32 bytes
	 *
	 * 0101 0000
	 */
	val = 0x50;
	ग_लिखो_reg(info, CHA + CCR4, val);
	अगर (info->params.flags & HDLC_FLAG_RXC_DPLL)
		mgslpc_set_rate(info, CHA, info->params.घड़ी_speed * 16);
	अन्यथा
		mgslpc_set_rate(info, CHA, info->params.घड़ी_speed);

	/* RLCR Receive length check रेजिस्टर
	 *
	 * 7     1=enable receive length check
	 * 6..0  Max frame length = (RL + 1) * 32
	 */
	ग_लिखो_reg(info, CHA + RLCR, 0);

	/* XBCH Transmit Byte Count High
	 *
	 * 07      DMA mode, 0 = पूर्णांकerrupt driven
	 * 06      NRM, 0=ABM (ignored)
	 * 05      CAS Carrier Auto Start
	 * 04      XC Transmit Continuously (ignored)
	 * 03..00  XBC[10..8] Transmit byte count bits 10..8
	 *
	 * 0000 0000
	 */
	val = 0x00;
	अगर (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT5;
	ग_लिखो_reg(info, CHA + XBCH, val);
	enable_auxclk(info);
	अगर (info->params.loopback || info->testing_irq)
		loopback_enable(info);
	अगर (info->params.flags & HDLC_FLAG_AUTO_CTS)
	अणु
		irq_enable(info, CHB, IRQ_CTS);
		/* PVR[3] 1=AUTO CTS active */
		set_reg_bits(info, CHA + PVR, BIT3);
	पूर्ण अन्यथा
		clear_reg_bits(info, CHA + PVR, BIT3);

	irq_enable(info, CHA,
			 IRQ_RXEOM | IRQ_RXFIFO | IRQ_ALLSENT |
			 IRQ_UNDERRUN | IRQ_TXFIFO);
	issue_command(info, CHA, CMD_TXRESET + CMD_RXRESET);
	रुको_command_complete(info, CHA);
	पढ़ो_reg16(info, CHA + ISR);	/* clear pending IRQs */

	/* Master घड़ी mode enabled above to allow reset commands
	 * to complete even अगर no data घड़ीs are present.
	 *
	 * Disable master घड़ी mode क्रम normal communications because
	 * V3.2 of the ESCC2 has a bug that prevents the transmit all sent
	 * IRQ when in master घड़ी mode.
	 *
	 * Leave master घड़ी mode enabled क्रम IRQ test because the
	 * समयr IRQ used by the test can only happen in master घड़ी mode.
	 */
	अगर (!info->testing_irq)
		clear_reg_bits(info, CHA + CCR0, BIT6);

	tx_set_idle(info);

	tx_stop(info);
	rx_stop(info);
पूर्ण

अटल व्योम rx_stop(MGSLPC_INFO *info)
अणु
	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):rx_stop(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	/* MODE:03 RAC Receiver Active, 0=inactive */
	clear_reg_bits(info, CHA + MODE, BIT3);

	info->rx_enabled = false;
	info->rx_overflow = false;
पूर्ण

अटल व्योम rx_start(MGSLPC_INFO *info)
अणु
	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):rx_start(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	rx_reset_buffers(info);
	info->rx_enabled = false;
	info->rx_overflow = false;

	/* MODE:03 RAC Receiver Active, 1=active */
	set_reg_bits(info, CHA + MODE, BIT3);

	info->rx_enabled = true;
पूर्ण

अटल व्योम tx_start(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):tx_start(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	अगर (info->tx_count) अणु
		/* If स्वतः RTS enabled and RTS is inactive, then निश्चित */
		/* RTS and set a flag indicating that the driver should */
		/* negate RTS when the transmission completes. */
		info->drop_rts_on_tx_करोne = false;

		अगर (info->params.flags & HDLC_FLAG_AUTO_RTS) अणु
			get_संकेतs(info);
			अगर (!(info->serial_संकेतs & SerialSignal_RTS)) अणु
				info->serial_संकेतs |= SerialSignal_RTS;
				set_संकेतs(info);
				info->drop_rts_on_tx_करोne = true;
			पूर्ण
		पूर्ण

		अगर (info->params.mode == MGSL_MODE_ASYNC) अणु
			अगर (!info->tx_active) अणु
				info->tx_active = true;
				tx_पढ़ोy(info, tty);
			पूर्ण
		पूर्ण अन्यथा अणु
			info->tx_active = true;
			tx_पढ़ोy(info, tty);
			mod_समयr(&info->tx_समयr, jअगरfies +
					msecs_to_jअगरfies(5000));
		पूर्ण
	पूर्ण

	अगर (!info->tx_enabled)
		info->tx_enabled = true;
पूर्ण

अटल व्योम tx_stop(MGSLPC_INFO *info)
अणु
	अगर (debug_level >= DEBUG_LEVEL_ISR)
		prपूर्णांकk("%s(%d):tx_stop(%s)\n",
			 __खाता__, __LINE__, info->device_name);

	del_समयr(&info->tx_समयr);

	info->tx_enabled = false;
	info->tx_active = false;
पूर्ण

/* Reset the adapter to a known state and prepare it क्रम further use.
 */
अटल व्योम reset_device(MGSLPC_INFO *info)
अणु
	/* घातer up both channels (set BIT7) */
	ग_लिखो_reg(info, CHA + CCR0, 0x80);
	ग_लिखो_reg(info, CHB + CCR0, 0x80);
	ग_लिखो_reg(info, CHA + MODE, 0);
	ग_लिखो_reg(info, CHB + MODE, 0);

	/* disable all पूर्णांकerrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* PCR Port Configuration Register
	 *
	 * 07..04  DEC[3..0] Serial I/F select outमाला_दो
	 * 03      output, 1=AUTO CTS control enabled
	 * 02      RI Ring Indicator input 0=active
	 * 01      DSR input 0=active
	 * 00      DTR output 0=active
	 *
	 * 0000 0110
	 */
	ग_लिखो_reg(info, PCR, 0x06);

	/* PVR Port Value Register
	 *
	 * 07..04  DEC[3..0] Serial I/F select (0000=disabled)
	 * 03      AUTO CTS output 1=enabled
	 * 02      RI Ring Indicator input
	 * 01      DSR input
	 * 00      DTR output (1=inactive)
	 *
	 * 0000 0001
	 */
//	ग_लिखो_reg(info, PVR, PVR_DTR);

	/* IPC Interrupt Port Configuration
	 *
	 * 07      VIS 1=Masked पूर्णांकerrupts visible
	 * 06..05  Reserved, 0
	 * 04..03  SLA Slave address, 00 ignored
	 * 02      CASM Cascading Mode, 1=daisy chain
	 * 01..00  IC[1..0] Interrupt Config, 01=push-pull output, active low
	 *
	 * 0000 0101
	 */
	ग_लिखो_reg(info, IPC, 0x05);
पूर्ण

अटल व्योम async_mode(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर val;

	/* disable all पूर्णांकerrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* MODE
	 *
	 * 07      Reserved, 0
	 * 06      FRTS RTS State, 0=active
	 * 05      FCTS Flow Control on CTS
	 * 04      FLON Flow Control Enable
	 * 03      RAC Receiver Active, 0 = inactive
	 * 02      RTS 0=Auto RTS, 1=manual RTS
	 * 01      TRS Timer Resolution, 1=512
	 * 00      TLP Test Loop, 0 = no loop
	 *
	 * 0000 0110
	 */
	val = 0x06;
	अगर (info->params.loopback)
		val |= BIT0;

	/* preserve RTS state */
	अगर (!(info->serial_संकेतs & SerialSignal_RTS))
		val |= BIT6;
	ग_लिखो_reg(info, CHA + MODE, val);

	/* CCR0
	 *
	 * 07      PU Power Up, 1=active, 0=घातer करोwn
	 * 06      MCE Master Clock Enable, 1=enabled
	 * 05      Reserved, 0
	 * 04..02  SC[2..0] Encoding, 000=NRZ
	 * 01..00  SM[1..0] Serial Mode, 11=Async
	 *
	 * 1000 0011
	 */
	ग_लिखो_reg(info, CHA + CCR0, 0x83);

	/* CCR1
	 *
	 * 07..05  Reserved, 0
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      BCR Bit Clock Rate, 1=16x
	 * 02..00  CM[2..0] Clock Mode, 111=BRG
	 *
	 * 0001 1111
	 */
	ग_लिखो_reg(info, CHA + CCR1, 0x1f);

	/* CCR2 (channel A)
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate भागisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 0=TxCLK is input
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      Reserved, 0
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0001 0000
	 */
	ग_लिखो_reg(info, CHA + CCR2, 0x10);

	/* CCR3
	 *
	 * 07..01  Reserved, 0
	 * 00      PSD DPLL Phase Shअगरt Disable
	 *
	 * 0000 0000
	 */
	ग_लिखो_reg(info, CHA + CCR3, 0);

	/* CCR4
	 *
	 * 07      MCK4 Master Clock Divide by 4, 1=enabled
	 * 06      EBRG Enhanced Baud Rate Generator Mode, 1=enabled
	 * 05      TST1 Test Pin, 0=normal operation
	 * 04      ICD Ivert Carrier Detect, 1=enabled (active low)
	 * 03..00  Reserved, must be 0
	 *
	 * 0101 0000
	 */
	ग_लिखो_reg(info, CHA + CCR4, 0x50);
	mgslpc_set_rate(info, CHA, info->params.data_rate * 16);

	/* DAFO Data Format
	 *
	 * 07      Reserved, 0
	 * 06      XBRK transmit अवरोध, 0=normal operation
	 * 05      Stop bits (0=1, 1=2)
	 * 04..03  PAR[1..0] Parity (01=odd, 10=even)
	 * 02      PAREN Parity Enable
	 * 01..00  CHL[1..0] Character Length (00=8, 01=7)
	 *
	 */
	val = 0x00;
	अगर (info->params.data_bits != 8)
		val |= BIT0;	/* 7 bits */
	अगर (info->params.stop_bits != 1)
		val |= BIT5;
	अगर (info->params.parity != ASYNC_PARITY_NONE)
	अणु
		val |= BIT2;	/* Parity enable */
		अगर (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT3;
		अन्यथा
			val |= BIT4;
	पूर्ण
	ग_लिखो_reg(info, CHA + DAFO, val);

	/* RFC Rx FIFO Control
	 *
	 * 07      Reserved, 0
	 * 06      DPS, 1=parity bit not stored in data byte
	 * 05      DXS, 0=all data stored in FIFO (including XON/XOFF)
	 * 04      RFDF Rx FIFO Data Format, 1=status byte stored in FIFO
	 * 03..02  RFTH[1..0], rx threshold, 11=16 status + 16 data byte
	 * 01      Reserved, 0
	 * 00      TCDE Terminate Char Detect Enable, 0=disabled
	 *
	 * 0101 1100
	 */
	ग_लिखो_reg(info, CHA + RFC, 0x5c);

	/* RLCR Receive length check रेजिस्टर
	 *
	 * Max frame length = (RL + 1) * 32
	 */
	ग_लिखो_reg(info, CHA + RLCR, 0);

	/* XBCH Transmit Byte Count High
	 *
	 * 07      DMA mode, 0 = पूर्णांकerrupt driven
	 * 06      NRM, 0=ABM (ignored)
	 * 05      CAS Carrier Auto Start
	 * 04      XC Transmit Continuously (ignored)
	 * 03..00  XBC[10..8] Transmit byte count bits 10..8
	 *
	 * 0000 0000
	 */
	val = 0x00;
	अगर (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT5;
	ग_लिखो_reg(info, CHA + XBCH, val);
	अगर (info->params.flags & HDLC_FLAG_AUTO_CTS)
		irq_enable(info, CHA, IRQ_CTS);

	/* MODE:03 RAC Receiver Active, 1=active */
	set_reg_bits(info, CHA + MODE, BIT3);
	enable_auxclk(info);
	अगर (info->params.flags & HDLC_FLAG_AUTO_CTS) अणु
		irq_enable(info, CHB, IRQ_CTS);
		/* PVR[3] 1=AUTO CTS active */
		set_reg_bits(info, CHA + PVR, BIT3);
	पूर्ण अन्यथा
		clear_reg_bits(info, CHA + PVR, BIT3);
	irq_enable(info, CHA,
			  IRQ_RXEOM | IRQ_RXFIFO | IRQ_BREAK_ON | IRQ_RXTIME |
			  IRQ_ALLSENT | IRQ_TXFIFO);
	issue_command(info, CHA, CMD_TXRESET + CMD_RXRESET);
	रुको_command_complete(info, CHA);
	पढ़ो_reg16(info, CHA + ISR);	/* clear pending IRQs */
पूर्ण

/* Set the HDLC idle mode क्रम the transmitter.
 */
अटल व्योम tx_set_idle(MGSLPC_INFO *info)
अणु
	/* Note: ESCC2 only supports flags and one idle modes */
	अगर (info->idle_mode == HDLC_TXIDLE_FLAGS)
		set_reg_bits(info, CHA + CCR1, BIT3);
	अन्यथा
		clear_reg_bits(info, CHA + CCR1, BIT3);
पूर्ण

/* get state of the V24 status (input) संकेतs.
 */
अटल व्योम get_संकेतs(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर status = 0;

	/* preserve RTS and DTR */
	info->serial_संकेतs &= SerialSignal_RTS | SerialSignal_DTR;

	अगर (पढ़ो_reg(info, CHB + VSTR) & BIT7)
		info->serial_संकेतs |= SerialSignal_DCD;
	अगर (पढ़ो_reg(info, CHB + STAR) & BIT1)
		info->serial_संकेतs |= SerialSignal_CTS;

	status = पढ़ो_reg(info, CHA + PVR);
	अगर (!(status & PVR_RI))
		info->serial_संकेतs |= SerialSignal_RI;
	अगर (!(status & PVR_DSR))
		info->serial_संकेतs |= SerialSignal_DSR;
पूर्ण

/* Set the state of RTS and DTR based on contents of
 * serial_संकेतs member of device extension.
 */
अटल व्योम set_संकेतs(MGSLPC_INFO *info)
अणु
	अचिन्हित अक्षर val;

	val = पढ़ो_reg(info, CHA + MODE);
	अगर (info->params.mode == MGSL_MODE_ASYNC) अणु
		अगर (info->serial_संकेतs & SerialSignal_RTS)
			val &= ~BIT6;
		अन्यथा
			val |= BIT6;
	पूर्ण अन्यथा अणु
		अगर (info->serial_संकेतs & SerialSignal_RTS)
			val |= BIT2;
		अन्यथा
			val &= ~BIT2;
	पूर्ण
	ग_लिखो_reg(info, CHA + MODE, val);

	अगर (info->serial_संकेतs & SerialSignal_DTR)
		clear_reg_bits(info, CHA + PVR, PVR_DTR);
	अन्यथा
		set_reg_bits(info, CHA + PVR, PVR_DTR);
पूर्ण

अटल व्योम rx_reset_buffers(MGSLPC_INFO *info)
अणु
	RXBUF *buf;
	पूर्णांक i;

	info->rx_put = 0;
	info->rx_get = 0;
	info->rx_frame_count = 0;
	क्रम (i=0 ; i < info->rx_buf_count ; i++) अणु
		buf = (RXBUF*)(info->rx_buf + (i * info->rx_buf_size));
		buf->status = buf->count = 0;
	पूर्ण
पूर्ण

/* Attempt to वापस a received HDLC frame
 * Only frames received without errors are वापसed.
 *
 * Returns true अगर frame वापसed, otherwise false
 */
अटल bool rx_get_frame(MGSLPC_INFO *info, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित लघु status;
	RXBUF *buf;
	अचिन्हित पूर्णांक framesize = 0;
	अचिन्हित दीर्घ flags;
	bool वापस_frame = false;

	अगर (info->rx_frame_count == 0)
		वापस false;

	buf = (RXBUF*)(info->rx_buf + (info->rx_get * info->rx_buf_size));

	status = buf->status;

	/* 07  VFR  1=valid frame
	 * 06  RDO  1=data overrun
	 * 05  CRC  1=OK, 0=error
	 * 04  RAB  1=frame पातed
	 */
	अगर ((status & 0xf0) != 0xA0) अणु
		अगर (!(status & BIT7) || (status & BIT4))
			info->icount.rxपात++;
		अन्यथा अगर (status & BIT6)
			info->icount.rxover++;
		अन्यथा अगर (!(status & BIT5)) अणु
			info->icount.rxcrc++;
			अगर (info->params.crc_type & HDLC_CRC_RETURN_EX)
				वापस_frame = true;
		पूर्ण
		framesize = 0;
#अगर SYNCLINK_GENERIC_HDLC
		अणु
			info->netdev->stats.rx_errors++;
			info->netdev->stats.rx_frame_errors++;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा
		वापस_frame = true;

	अगर (वापस_frame)
		framesize = buf->count;

	अगर (debug_level >= DEBUG_LEVEL_BH)
		prपूर्णांकk("%s(%d):rx_get_frame(%s) status=%04X size=%d\n",
			__खाता__, __LINE__, info->device_name, status, framesize);

	अगर (debug_level >= DEBUG_LEVEL_DATA)
		trace_block(info, buf->data, framesize, 0);

	अगर (framesize) अणु
		अगर ((info->params.crc_type & HDLC_CRC_RETURN_EX &&
		      framesize+1 > info->max_frame_size) ||
		    framesize > info->max_frame_size)
			info->icount.rxदीर्घ++;
		अन्यथा अणु
			अगर (status & BIT5)
				info->icount.rxok++;

			अगर (info->params.crc_type & HDLC_CRC_RETURN_EX) अणु
				*(buf->data + framesize) = status & BIT5 ? RX_OK:RX_CRC_ERROR;
				++framesize;
			पूर्ण

#अगर SYNCLINK_GENERIC_HDLC
			अगर (info->netcount)
				hdlcdev_rx(info, buf->data, framesize);
			अन्यथा
#पूर्ण_अगर
				ldisc_receive_buf(tty, buf->data, info->flag_buf, framesize);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&info->lock, flags);
	buf->status = buf->count = 0;
	info->rx_frame_count--;
	info->rx_get++;
	अगर (info->rx_get >= info->rx_buf_count)
		info->rx_get = 0;
	spin_unlock_irqrestore(&info->lock, flags);

	वापस true;
पूर्ण

अटल bool रेजिस्टर_test(MGSLPC_INFO *info)
अणु
	अटल अचिन्हित अक्षर patterns[] =
	    अणु 0x00, 0xff, 0xaa, 0x55, 0x69, 0x96, 0x0f पूर्ण;
	अटल अचिन्हित पूर्णांक count = ARRAY_SIZE(patterns);
	अचिन्हित पूर्णांक i;
	bool rc = true;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	reset_device(info);

	क्रम (i = 0; i < count; i++) अणु
		ग_लिखो_reg(info, XAD1, patterns[i]);
		ग_लिखो_reg(info, XAD2, patterns[(i + 1) % count]);
		अगर ((पढ़ो_reg(info, XAD1) != patterns[i]) ||
		    (पढ़ो_reg(info, XAD2) != patterns[(i + 1) % count])) अणु
			rc = false;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&info->lock, flags);
	वापस rc;
पूर्ण

अटल bool irq_test(MGSLPC_INFO *info)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->lock, flags);
	reset_device(info);

	info->testing_irq = true;
	hdlc_mode(info);

	info->irq_occurred = false;

	/* init hdlc mode */

	irq_enable(info, CHA, IRQ_TIMER);
	ग_लिखो_reg(info, CHA + TIMR, 0);	/* 512 cycles */
	issue_command(info, CHA, CMD_START_TIMER);

	spin_unlock_irqrestore(&info->lock, flags);

	end_समय=100;
	जबतक(end_समय-- && !info->irq_occurred) अणु
		msleep_पूर्णांकerruptible(10);
	पूर्ण

	info->testing_irq = false;

	spin_lock_irqsave(&info->lock, flags);
	reset_device(info);
	spin_unlock_irqrestore(&info->lock, flags);

	वापस info->irq_occurred;
पूर्ण

अटल पूर्णांक adapter_test(MGSLPC_INFO *info)
अणु
	अगर (!रेजिस्टर_test(info)) अणु
		info->init_error = DiagStatus_AddressFailure;
		prपूर्णांकk("%s(%d):Register test failure for device %s Addr=%04X\n",
			__खाता__, __LINE__, info->device_name, (अचिन्हित लघु)(info->io_base));
		वापस -ENODEV;
	पूर्ण

	अगर (!irq_test(info)) अणु
		info->init_error = DiagStatus_IrqFailure;
		prपूर्णांकk("%s(%d):Interrupt test failure for device %s IRQ=%d\n",
			__खाता__, __LINE__, info->device_name, (अचिन्हित लघु)(info->irq_level));
		वापस -ENODEV;
	पूर्ण

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):device %s passed diagnostics\n",
			__खाता__, __LINE__, info->device_name);
	वापस 0;
पूर्ण

अटल व्योम trace_block(MGSLPC_INFO *info,स्थिर अक्षर* data, पूर्णांक count, पूर्णांक xmit)
अणु
	पूर्णांक i;
	पूर्णांक linecount;
	अगर (xmit)
		prपूर्णांकk("%s tx data:\n", info->device_name);
	अन्यथा
		prपूर्णांकk("%s rx data:\n", info->device_name);

	जबतक(count) अणु
		अगर (count > 16)
			linecount = 16;
		अन्यथा
			linecount = count;

		क्रम(i=0;i<linecount;i++)
			prपूर्णांकk("%02X ", (अचिन्हित अक्षर)data[i]);
		क्रम(;i<17;i++)
			prपूर्णांकk("   ");
		क्रम(i=0;i<linecount;i++) अणु
			अगर (data[i]>=040 && data[i]<=0176)
				prपूर्णांकk("%c", data[i]);
			अन्यथा
				prपूर्णांकk(".");
		पूर्ण
		prपूर्णांकk("\n");

		data  += linecount;
		count -= linecount;
	पूर्ण
पूर्ण

/* HDLC frame समय out
 * update stats and करो tx completion processing
 */
अटल व्योम tx_समयout(काष्ठा समयr_list *t)
अणु
	MGSLPC_INFO *info = from_समयr(info, t, tx_समयr);
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s(%d):tx_timeout(%s)\n",
			__खाता__, __LINE__, info->device_name);
	अगर (info->tx_active &&
	    info->params.mode == MGSL_MODE_HDLC) अणु
		info->icount.txसमयout++;
	पूर्ण
	spin_lock_irqsave(&info->lock, flags);
	info->tx_active = false;
	info->tx_count = info->tx_put = info->tx_get = 0;

	spin_unlock_irqrestore(&info->lock, flags);

#अगर SYNCLINK_GENERIC_HDLC
	अगर (info->netcount)
		hdlcdev_tx_करोne(info);
	अन्यथा
#पूर्ण_अगर
	अणु
		काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&info->port);
		bh_transmit(info, tty);
		tty_kref_put(tty);
	पूर्ण
पूर्ण

#अगर SYNCLINK_GENERIC_HDLC

/**
 * called by generic HDLC layer when protocol selected (PPP, frame relay, etc.)
 * set encoding and frame check sequence (FCS) options
 *
 * dev       poपूर्णांकer to network device काष्ठाure
 * encoding  serial encoding setting
 * parity    FCS setting
 *
 * वापसs 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			  अचिन्हित लघु parity)
अणु
	MGSLPC_INFO *info = dev_to_port(dev);
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित अक्षर  new_encoding;
	अचिन्हित लघु new_crctype;

	/* वापस error अगर TTY पूर्णांकerface खोलो */
	अगर (info->port.count)
		वापस -EBUSY;

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
	अगर (info->netcount) अणु
		tty = tty_port_tty_get(&info->port);
		mgslpc_program_hw(info, tty);
		tty_kref_put(tty);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * called by generic HDLC layer to send frame
 *
 * skb  socket buffer containing HDLC frame
 * dev  poपूर्णांकer to network device काष्ठाure
 */
अटल netdev_tx_t hdlcdev_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	MGSLPC_INFO *info = dev_to_port(dev);
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk(KERN_INFO "%s:hdlc_xmit(%s)\n", __खाता__, dev->name);

	/* stop sending until this frame completes */
	netअगर_stop_queue(dev);

	/* copy data to device buffers */
	skb_copy_from_linear_data(skb, info->tx_buf, skb->len);
	info->tx_get = 0;
	info->tx_put = info->tx_count = skb->len;

	/* update network statistics */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/* करोne with socket buffer, so मुक्त it */
	dev_kमुक्त_skb(skb);

	/* save start समय क्रम transmit समयout detection */
	netअगर_trans_update(dev);

	/* start hardware transmitter अगर necessary */
	spin_lock_irqsave(&info->lock, flags);
	अगर (!info->tx_active) अणु
		काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&info->port);
		tx_start(info, tty);
		tty_kref_put(tty);
	पूर्ण
	spin_unlock_irqrestore(&info->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * called by network layer when पूर्णांकerface enabled
 * claim resources and initialize hardware
 *
 * dev  poपूर्णांकer to network device काष्ठाure
 *
 * वापसs 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_खोलो(काष्ठा net_device *dev)
अणु
	MGSLPC_INFO *info = dev_to_port(dev);
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s:hdlcdev_open(%s)\n", __खाता__, dev->name);

	/* generic HDLC layer खोलो processing */
	rc = hdlc_खोलो(dev);
	अगर (rc != 0)
		वापस rc;

	/* arbitrate between network and tty खोलोs */
	spin_lock_irqsave(&info->netlock, flags);
	अगर (info->port.count != 0 || info->netcount != 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: hdlc_open returning busy\n", dev->name);
		spin_unlock_irqrestore(&info->netlock, flags);
		वापस -EBUSY;
	पूर्ण
	info->netcount=1;
	spin_unlock_irqrestore(&info->netlock, flags);

	tty = tty_port_tty_get(&info->port);
	/* claim resources and init adapter */
	rc = startup(info, tty);
	अगर (rc != 0) अणु
		tty_kref_put(tty);
		spin_lock_irqsave(&info->netlock, flags);
		info->netcount=0;
		spin_unlock_irqrestore(&info->netlock, flags);
		वापस rc;
	पूर्ण
	/* निश्चित RTS and DTR, apply hardware settings */
	info->serial_संकेतs |= SerialSignal_RTS | SerialSignal_DTR;
	mgslpc_program_hw(info, tty);
	tty_kref_put(tty);

	/* enable network layer transmit */
	netअगर_trans_update(dev);
	netअगर_start_queue(dev);

	/* inक्रमm generic HDLC layer of current DCD status */
	spin_lock_irqsave(&info->lock, flags);
	get_संकेतs(info);
	spin_unlock_irqrestore(&info->lock, flags);
	अगर (info->serial_संकेतs & SerialSignal_DCD)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

/**
 * called by network layer when पूर्णांकerface is disabled
 * shutकरोwn hardware and release resources
 *
 * dev  poपूर्णांकer to network device काष्ठाure
 *
 * वापसs 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_बंद(काष्ठा net_device *dev)
अणु
	MGSLPC_INFO *info = dev_to_port(dev);
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&info->port);
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s:hdlcdev_close(%s)\n", __खाता__, dev->name);

	netअगर_stop_queue(dev);

	/* shutकरोwn adapter and release resources */
	shutकरोwn(info, tty);
	tty_kref_put(tty);
	hdlc_बंद(dev);

	spin_lock_irqsave(&info->netlock, flags);
	info->netcount=0;
	spin_unlock_irqrestore(&info->netlock, flags);

	वापस 0;
पूर्ण

/**
 * called by network layer to process IOCTL call to network device
 *
 * dev  poपूर्णांकer to network device काष्ठाure
 * अगरr  poपूर्णांकer to network पूर्णांकerface request काष्ठाure
 * cmd  IOCTL command code
 *
 * वापसs 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	MGSLPC_INFO *info = dev_to_port(dev);
	अचिन्हित पूर्णांक flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("%s:hdlcdev_ioctl(%s)\n", __खाता__, dev->name);

	/* वापस error अगर TTY पूर्णांकerface खोलो */
	अगर (info->port.count)
		वापस -EBUSY;

	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	स_रखो(&new_line, 0, size);

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
		अगर (info->netcount) अणु
			काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&info->port);
			mgslpc_program_hw(info, tty);
			tty_kref_put(tty);
		पूर्ण
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण

/**
 * called by network layer when transmit समयout is detected
 *
 * dev  poपूर्णांकer to network device काष्ठाure
 */
अटल व्योम hdlcdev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	MGSLPC_INFO *info = dev_to_port(dev);
	अचिन्हित दीर्घ flags;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("hdlcdev_tx_timeout(%s)\n", dev->name);

	dev->stats.tx_errors++;
	dev->stats.tx_पातed_errors++;

	spin_lock_irqsave(&info->lock, flags);
	tx_stop(info);
	spin_unlock_irqrestore(&info->lock, flags);

	netअगर_wake_queue(dev);
पूर्ण

/**
 * called by device driver when transmit completes
 * reenable network layer transmit अगर stopped
 *
 * info  poपूर्णांकer to device instance inक्रमmation
 */
अटल व्योम hdlcdev_tx_करोne(MGSLPC_INFO *info)
अणु
	अगर (netअगर_queue_stopped(info->netdev))
		netअगर_wake_queue(info->netdev);
पूर्ण

/**
 * called by device driver when frame received
 * pass frame to network layer
 *
 * info  poपूर्णांकer to device instance inक्रमmation
 * buf   poपूर्णांकer to buffer contianing frame data
 * size  count of data bytes in buf
 */
अटल व्योम hdlcdev_rx(MGSLPC_INFO *info, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb = dev_alloc_skb(size);
	काष्ठा net_device *dev = info->netdev;

	अगर (debug_level >= DEBUG_LEVEL_INFO)
		prपूर्णांकk("hdlcdev_rx(%s)\n", dev->name);

	अगर (skb == शून्य) अणु
		prपूर्णांकk(KERN_NOTICE "%s: can't alloc skb, dropping packet\n", dev->name);
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
 * called by device driver when adding device instance
 * करो generic HDLC initialization
 *
 * info  poपूर्णांकer to device instance inक्रमmation
 *
 * वापसs 0 अगर success, otherwise error code
 */
अटल पूर्णांक hdlcdev_init(MGSLPC_INFO *info)
अणु
	पूर्णांक rc;
	काष्ठा net_device *dev;
	hdlc_device *hdlc;

	/* allocate and initialize network and HDLC layer objects */

	dev = alloc_hdlcdev(info);
	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s:hdlc device allocation failure\n", __खाता__);
		वापस -ENOMEM;
	पूर्ण

	/* क्रम network layer reporting purposes only */
	dev->base_addr = info->io_base;
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
		prपूर्णांकk(KERN_WARNING "%s:unable to register hdlc device\n", __खाता__);
		मुक्त_netdev(dev);
		वापस rc;
	पूर्ण

	info->netdev = dev;
	वापस 0;
पूर्ण

/**
 * called by device driver when removing device instance
 * करो generic HDLC cleanup
 *
 * info  poपूर्णांकer to device instance inक्रमmation
 */
अटल व्योम hdlcdev_निकास(MGSLPC_INFO *info)
अणु
	unरेजिस्टर_hdlc_device(info->netdev);
	मुक्त_netdev(info->netdev);
	info->netdev = शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_HDLC */

