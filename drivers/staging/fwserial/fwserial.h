<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FIREWIRE_FWSERIAL_H
#घोषणा _FIREWIRE_FWSERIAL_H

#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/list.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mutex.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश "dma_fifo.h"

#अगर_घोषित FWTTY_PROFILING
#घोषणा DISTRIBUTION_MAX_SIZE     8192
#घोषणा DISTRIBUTION_MAX_INDEX    (ilog2(DISTRIBUTION_MAX_SIZE) + 1)
अटल अंतरभूत व्योम fwtty_profile_data(अचिन्हित पूर्णांक stat[], अचिन्हित पूर्णांक val)
अणु
	पूर्णांक n = (val) ? min(ilog2(val) + 1, DISTRIBUTION_MAX_INDEX) : 0;
	++stat[n];
पूर्ण
#अन्यथा
#घोषणा DISTRIBUTION_MAX_INDEX    0
#घोषणा fwtty_profile_data(st, n)
#पूर्ण_अगर

/* Parameters क्रम both VIRT_CABLE_PLUG & VIRT_CABLE_PLUG_RSP mgmt codes */
काष्ठा virt_plug_params अणु
	__be32  status_hi;
	__be32  status_lo;
	__be32	fअगरo_hi;
	__be32	fअगरo_lo;
	__be32	fअगरo_len;
पूर्ण;

काष्ठा peer_work_params अणु
	जोड़ अणु
		काष्ठा virt_plug_params plug_req;
	पूर्ण;
पूर्ण;

/**
 * fwtty_peer: काष्ठाure representing local & remote unit devices
 * @unit: unit child device of fw_device node
 * @serial: back poपूर्णांकer to associated fw_serial aggregate
 * @guid: unique 64-bit guid क्रम this unit device
 * @generation: most recent bus generation
 * @node_id: most recent node_id
 * @speed: link speed of peer (0 = S100, 2 = S400, ... 5 = S3200)
 * @mgmt_addr: bus addr region to ग_लिखो mgmt packets to
 * @status_addr: bus addr रेजिस्टर to ग_लिखो line status to
 * @fअगरo_addr: bus addr region to ग_लिखो serial output to
 * @fअगरo_len:  max length क्रम single ग_लिखो to fअगरo_addr
 * @list: link क्रम insertion पूर्णांकo fw_serial's peer_list
 * @rcu: क्रम deferring peer reclamation
 * @lock: spinlock to synchonize changes to state & port fields
 * @work: only one work item can be queued at any one समय
 *        Note: pending work is canceled prior to removal, so this
 *        peer is valid क्रम at least the lअगरeसमय of the work function
 * @work_params: parameter block क्रम work functions
 * @समयr: समयr क्रम resetting peer state अगर remote request बार out
 * @state: current state
 * @connect: work item क्रम स्वतः-connecting
 * @connect_retries: # of connections alपढ़ोy attempted
 * @port: associated tty_port (usable अगर state == FWSC_ATTACHED)
 */
काष्ठा fwtty_peer अणु
	काष्ठा fw_unit		*unit;
	काष्ठा fw_serial	*serial;
	u64			guid;
	पूर्णांक			generation;
	पूर्णांक			node_id;
	अचिन्हित पूर्णांक		speed;
	पूर्णांक			max_payload;
	u64			mgmt_addr;

	/* these are usable only अगर state == FWSC_ATTACHED */
	u64			status_addr;
	u64			fअगरo_addr;
	पूर्णांक			fअगरo_len;

	काष्ठा list_head	list;
	काष्ठा rcu_head		rcu;

	spinlock_t		lock;
	work_func_t		workfn;
	काष्ठा work_काष्ठा	work;
	काष्ठा peer_work_params work_params;
	काष्ठा समयr_list	समयr;
	पूर्णांक			state;
	काष्ठा delayed_work	connect;
	पूर्णांक			connect_retries;

	काष्ठा fwtty_port	*port;
पूर्ण;

#घोषणा to_peer(ptr, field)	(container_of(ptr, काष्ठा fwtty_peer, field))

/* state values क्रम fwtty_peer.state field */
क्रमागत fwtty_peer_state अणु
	FWPS_GONE,
	FWPS_NOT_ATTACHED,
	FWPS_ATTACHED,
	FWPS_PLUG_PENDING,
	FWPS_PLUG_RESPONDING,
	FWPS_UNPLUG_PENDING,
	FWPS_UNPLUG_RESPONDING,

	FWPS_NO_MGMT_ADDR = -1,
पूर्ण;

#घोषणा CONNECT_RETRY_DELAY	HZ
#घोषणा MAX_CONNECT_RETRIES	10

/* must be holding peer lock क्रम these state funclets */
अटल अंतरभूत व्योम peer_set_state(काष्ठा fwtty_peer *peer, पूर्णांक new)
अणु
	peer->state = new;
पूर्ण

अटल अंतरभूत काष्ठा fwtty_port *peer_revert_state(काष्ठा fwtty_peer *peer)
अणु
	काष्ठा fwtty_port *port = peer->port;

	peer->port = शून्य;
	peer_set_state(peer, FWPS_NOT_ATTACHED);
	वापस port;
पूर्ण

काष्ठा fwserial_mgmt_pkt अणु
	काष्ठा अणु
		__be16		len;
		__be16		code;
	पूर्ण hdr;
	जोड़ अणु
		काष्ठा virt_plug_params plug_req;
		काष्ठा virt_plug_params plug_rsp;
	पूर्ण;
पूर्ण __packed;

/* fwserial_mgmt_packet codes */
#घोषणा FWSC_RSP_OK			0x0000
#घोषणा FWSC_RSP_NACK			0x8000
#घोषणा FWSC_CODE_MASK			0x0fff

#घोषणा FWSC_VIRT_CABLE_PLUG		1
#घोषणा FWSC_VIRT_CABLE_UNPLUG		2
#घोषणा FWSC_VIRT_CABLE_PLUG_RSP	3
#घोषणा FWSC_VIRT_CABLE_UNPLUG_RSP	4

/* 1 min. plug समयout -- suitable क्रम userland authorization */
#घोषणा VIRT_CABLE_PLUG_TIMEOUT		(60 * HZ)

काष्ठा stats अणु
	अचिन्हित पूर्णांक	xअक्षरs;
	अचिन्हित पूर्णांक	dropped;
	अचिन्हित पूर्णांक	tx_stall;
	अचिन्हित पूर्णांक	fअगरo_errs;
	अचिन्हित पूर्णांक	sent;
	अचिन्हित पूर्णांक	lost;
	अचिन्हित पूर्णांक	throttled;
	अचिन्हित पूर्णांक	पढ़ोs[DISTRIBUTION_MAX_INDEX + 1];
	अचिन्हित पूर्णांक	ग_लिखोs[DISTRIBUTION_MAX_INDEX + 1];
	अचिन्हित पूर्णांक	txns[DISTRIBUTION_MAX_INDEX + 1];
	अचिन्हित पूर्णांक	unthrottle[DISTRIBUTION_MAX_INDEX + 1];
पूर्ण;

काष्ठा fwconsole_ops अणु
	व्योम (*notअगरy)(पूर्णांक code, व्योम *data);
	व्योम (*stats)(काष्ठा stats *stats, व्योम *data);
	व्योम (*proc_show)(काष्ठा seq_file *m, व्योम *data);
पूर्ण;

/* codes क्रम console ops notअगरy */
#घोषणा FWCON_NOTIFY_ATTACH		1
#घोषणा FWCON_NOTIFY_DETACH		2

/**
 * fwtty_port: काष्ठाure used to track/represent underlying tty_port
 * @port: underlying tty_port
 * @device: tty device
 * @index: index पूर्णांकo port_table क्रम this particular port
 *    note: minor = index + minor_start asचिन्हित by tty_alloc_driver()
 * @serial: back poपूर्णांकer to the containing fw_serial
 * @rx_handler: bus address handler क्रम unique addr region used by remotes
 *              to communicate with this port. Every port uses
 *		fwtty_port_handler() क्रम per port transactions.
 * @fwcon_ops: ops क्रम attached fw_console (अगर any)
 * @con_data: निजी data क्रम fw_console
 * @रुको_tx: रुकोqueue क्रम sleeping until ग_लिखोr/drain completes tx
 * @emit_अवरोधs: delayed work responsible क्रम generating अवरोधs when the
 *               अवरोध line status is active
 * @cps : अक्षरacters per second computed from the termios settings
 * @अवरोध_last: बारtamp in jअगरfies from last emit_अवरोधs
 * @hangup: work responsible क्रम HUPing when carrier is dropped/lost
 * @mstatus: loose भवization of LSR/MSR
 *         bits 15..0  correspond to TIOCM_* bits
 *         bits 19..16 reserved क्रम mctrl
 *         bit 20      OOB_TX_THROTTLE
 *	   bits 23..21 reserved
 *         bits 31..24 correspond to UART_LSR_* bits
 * @lock: spinlock क्रम protecting concurrent access to fields below it
 * @mctrl: loose भवization of MCR
 *         bits 15..0  correspond to TIOCM_* bits
 *         bit 16      OOB_RX_THROTTLE
 *         bits 19..17 reserved
 *	   bits 31..20 reserved क्रम mstatus
 * @drain: delayed work scheduled to ensure that ग_लिखोs are flushed.
 *         The work can race with the ग_लिखोr but concurrent sending is
 *         prevented with the IN_TX flag. Scheduled under lock to
 *         limit scheduling when fअगरo has just been drained.
 * @tx_fअगरo: fअगरo used to store & block-up ग_लिखोs क्रम dma to remote
 * @max_payload: max bytes transmissible per dma (based on peer's max_payload)
 * @status_mask: UART_LSR_* biपंचांगask signअगरicant to rx (based on termios)
 * @ignore_mask: UART_LSR_* biपंचांगask of states to ignore (also based on termios)
 * @अवरोध_ctl: अगर set, port is 'sending break' to remote
 * @ग_लिखो_only: self-explanatory
 * @overrun: previous rx was lost (partially or completely)
 * @loopback: अगर set, port is in loopback mode
 * @flags: atomic bit flags
 *         bit 0: IN_TX - gate to allow only one cpu to send from the dma fअगरo
 *                        at a समय.
 *         bit 1: STOP_TX - क्रमce tx to निकास जबतक sending
 * @peer: rcu-poपूर्णांकer to associated fwtty_peer (अगर attached)
 *        शून्य अगर no peer attached
 * @icount: predefined statistics reported by the TIOCGICOUNT ioctl
 * @stats: additional statistics reported in /proc/tty/driver/firewire_serial
 */
काष्ठा fwtty_port अणु
	काष्ठा tty_port		   port;
	काष्ठा device		   *device;
	अचिन्हित पूर्णांक		   index;
	काष्ठा fw_serial	   *serial;
	काष्ठा fw_address_handler  rx_handler;

	काष्ठा fwconsole_ops	   *fwcon_ops;
	व्योम			   *con_data;

	रुको_queue_head_t	   रुको_tx;
	काष्ठा delayed_work	   emit_अवरोधs;
	अचिन्हित पूर्णांक		   cps;
	अचिन्हित दीर्घ		   अवरोध_last;

	काष्ठा work_काष्ठा	   hangup;

	अचिन्हित पूर्णांक		   mstatus;

	spinlock_t		   lock;
	अचिन्हित पूर्णांक		   mctrl;
	काष्ठा delayed_work	   drain;
	काष्ठा dma_fअगरo		   tx_fअगरo;
	पूर्णांक			   max_payload;
	अचिन्हित पूर्णांक		   status_mask;
	अचिन्हित पूर्णांक		   ignore_mask;
	अचिन्हित पूर्णांक		   अवरोध_ctl:1,
				   ग_लिखो_only:1,
				   overrun:1,
				   loopback:1;
	अचिन्हित दीर्घ		   flags;

	काष्ठा fwtty_peer __rcu	   *peer;

	काष्ठा async_icount	   icount;
	काष्ठा stats		   stats;
पूर्ण;

#घोषणा to_port(ptr, field)	(container_of(ptr, काष्ठा fwtty_port, field))

/* bit #s क्रम flags field */
#घोषणा IN_TX                      0
#घोषणा STOP_TX                    1

/* biपंचांगasks क्रम special mctrl/mstatus bits */
#घोषणा OOB_RX_THROTTLE   0x00010000
#घोषणा MCTRL_RSRVD       0x000e0000
#घोषणा OOB_TX_THROTTLE   0x00100000
#घोषणा MSTATUS_RSRVD     0x00e00000

#घोषणा MCTRL_MASK        (TIOCM_DTR | TIOCM_RTS | TIOCM_OUT1 | TIOCM_OUT2 | \
			   TIOCM_LOOP | OOB_RX_THROTTLE | MCTRL_RSRVD)

/* XXX even every 1/50th secs. may be unnecessarily accurate */
/* delay in jअगरfies between brk emits */
#घोषणा FREQ_BREAKS        (HZ / 50)

/* Ports are allocated in blocks of num_ports क्रम each fw_card */
#घोषणा MAX_CARD_PORTS           CONFIG_FWTTY_MAX_CARD_PORTS
#घोषणा MAX_TOTAL_PORTS          CONFIG_FWTTY_MAX_TOTAL_PORTS

/* tuning parameters */
#घोषणा FWTTY_PORT_TXFIFO_LEN	4096
#घोषणा FWTTY_PORT_MAX_PEND_DMA    8    /* costs a cache line per pend */
#घोषणा DRAIN_THRESHOLD         1024
#घोषणा MAX_ASYNC_PAYLOAD       4096    /* ohci-defined limit          */
#घोषणा WRITER_MINIMUM           128
/* TODO: how to set watermark to AR context size? see fwtty_rx() */
#घोषणा HIGH_WATERMARK         32768	/* AR context is 32K	       */

/*
 * Size of bus addr region above 4GB used per port as the recv addr
 * - must be at least as big as the MAX_ASYNC_PAYLOAD
 */
#घोषणा FWTTY_PORT_RXFIFO_LEN	MAX_ASYNC_PAYLOAD

/**
 * fw_serial: aggregate used to associate tty ports with specअगरic fw_card
 * @card: fw_card associated with this fw_serial device (1:1 association)
 * @kref: reference-counted multi-port management allows delayed destroy
 * @self: local unit device as 'peer'. Not valid until local unit device
 *         is क्रमागतerated.
 * @list: link क्रम insertion पूर्णांकo fwserial_list
 * @peer_list: list of local & remote unit devices attached to this card
 * @ports: fixed array of tty_ports provided by this serial device
 */
काष्ठा fw_serial अणु
	काष्ठा fw_card	  *card;
	काष्ठा kref	  kref;

	काष्ठा dentry	  *debugfs;
	काष्ठा fwtty_peer *self;

	काष्ठा list_head  list;
	काष्ठा list_head  peer_list;

	काष्ठा fwtty_port *ports[MAX_CARD_PORTS];
पूर्ण;

#घोषणा to_serial(ptr, field)	(container_of(ptr, काष्ठा fw_serial, field))

#घोषणा TTY_DEV_NAME		    "fwtty"	/* ttyFW was taken           */
अटल स्थिर अक्षर tty_dev_name[] =  TTY_DEV_NAME;
अटल स्थिर अक्षर loop_dev_name[] = "fwloop";

बाह्य काष्ठा tty_driver *fwtty_driver;

/*
 * Returns the max send async payload size in bytes based on the unit device
 * link speed. Self-limiting asynchronous bandwidth (via reducing the payload)
 * is not necessary and करोes not work, because
 *   1) asynchronous traffic will असलorb all available bandwidth (less that
 *	being used क्रम isochronous traffic)
 *   2) isochronous arbitration always wins.
 */
अटल अंतरभूत पूर्णांक link_speed_to_max_payload(अचिन्हित पूर्णांक speed)
अणु
	/* Max async payload is 4096 - see IEEE 1394-2008 tables 6-4, 16-18 */
	वापस min(512 << speed, 4096);
पूर्ण

#पूर्ण_अगर /* _FIREWIRE_FWSERIAL_H */
