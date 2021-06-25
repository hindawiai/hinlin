<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Copyright IBM Corp. 2001, 2007
 *	Authors:	Fritz Elfert (felfert@millenux.com)
 *			Peter Tiedemann (ptiedem@de.ibm.com)
 */

#अगर_अघोषित _CTCM_MAIN_H_
#घोषणा _CTCM_MAIN_H_

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

#समावेश "fsm.h"
#समावेश "ctcm_dbug.h"
#समावेश "ctcm_mpc.h"

#घोषणा CTC_DRIVER_NAME	"ctcm"
#घोषणा CTC_DEVICE_NAME	"ctc"
#घोषणा MPC_DEVICE_NAME	"mpc"
#घोषणा CTC_DEVICE_GENE CTC_DEVICE_NAME "%d"
#घोषणा MPC_DEVICE_GENE	MPC_DEVICE_NAME "%d"

#घोषणा CHANNEL_FLAGS_READ	0
#घोषणा CHANNEL_FLAGS_WRITE	1
#घोषणा CHANNEL_FLAGS_INUSE	2
#घोषणा CHANNEL_FLAGS_बफ_मानE_CHANGED	4
#घोषणा CHANNEL_FLAGS_FAILED	8
#घोषणा CHANNEL_FLAGS_WAITIRQ	16
#घोषणा CHANNEL_FLAGS_RWMASK	1
#घोषणा CHANNEL_सूचीECTION(f) (f & CHANNEL_FLAGS_RWMASK)

#घोषणा LOG_FLAG_ILLEGALPKT	1
#घोषणा LOG_FLAG_ILLEGALSIZE	2
#घोषणा LOG_FLAG_OVERRUN	4
#घोषणा LOG_FLAG_NOMEM		8

#घोषणा ctcm_pr_debug(fmt, arg...) prपूर्णांकk(KERN_DEBUG fmt, ##arg)

#घोषणा CTCM_PR_DEBUG(fmt, arg...) \
	करो अणु \
		अगर (करो_debug) \
			prपूर्णांकk(KERN_DEBUG fmt, ##arg); \
	पूर्ण जबतक (0)

#घोषणा	CTCM_PR_DBGDATA(fmt, arg...) \
	करो अणु \
		अगर (करो_debug_data) \
			prपूर्णांकk(KERN_DEBUG fmt, ##arg); \
	पूर्ण जबतक (0)

#घोषणा	CTCM_D3_DUMP(buf, len) \
	करो अणु \
		अगर (करो_debug_data) \
			ctcmpc_dumpit(buf, len); \
	पूर्ण जबतक (0)

#घोषणा	CTCM_CCW_DUMP(buf, len) \
	करो अणु \
		अगर (करो_debug_ccw) \
			ctcmpc_dumpit(buf, len); \
	पूर्ण जबतक (0)

/**
 * Enum क्रम classअगरying detected devices
 */
क्रमागत ctcm_channel_types अणु
	/* Device is not a channel  */
	ctcm_channel_type_none,

	/* Device is a CTC/A */
	ctcm_channel_type_parallel,

	/* Device is a FICON channel */
	ctcm_channel_type_ficon,

	/* Device is a ESCON channel */
	ctcm_channel_type_escon
पूर्ण;

/*
 * CCW commands, used in this driver.
 */
#घोषणा CCW_CMD_WRITE		0x01
#घोषणा CCW_CMD_READ		0x02
#घोषणा CCW_CMD_NOOP		0x03
#घोषणा CCW_CMD_TIC             0x08
#घोषणा CCW_CMD_SENSE_CMD	0x14
#घोषणा CCW_CMD_WRITE_CTL	0x17
#घोषणा CCW_CMD_SET_EXTENDED	0xc3
#घोषणा CCW_CMD_PREPARE		0xe3

#घोषणा CTCM_PROTO_S390		0
#घोषणा CTCM_PROTO_LINUX	1
#घोषणा CTCM_PROTO_LINUX_TTY	2
#घोषणा CTCM_PROTO_OS390	3
#घोषणा CTCM_PROTO_MPC		4
#घोषणा CTCM_PROTO_MAX		4

#घोषणा CTCM_बफ_मानE_LIMIT	65535
#घोषणा CTCM_बफ_मानE_DEFAULT	32768
#घोषणा MPC_बफ_मानE_DEFAULT	CTCM_बफ_मानE_LIMIT

#घोषणा CTCM_TIME_1_SEC		1000
#घोषणा CTCM_TIME_5_SEC		5000
#घोषणा CTCM_TIME_10_SEC	10000

#घोषणा CTCM_INITIAL_BLOCKLEN	2

#घोषणा CTCM_READ		0
#घोषणा CTCM_WRITE		1

#घोषणा CTCM_ID_SIZE		20+3

काष्ठा ctcm_profile अणु
	अचिन्हित दीर्घ maxmulti;
	अचिन्हित दीर्घ maxcqueue;
	अचिन्हित दीर्घ करोios_single;
	अचिन्हित दीर्घ करोios_multi;
	अचिन्हित दीर्घ txlen;
	अचिन्हित दीर्घ tx_समय;
	अचिन्हित दीर्घ send_stamp;
पूर्ण;

/*
 * Definition of one channel
 */
काष्ठा channel अणु
	काष्ठा channel *next;
	अक्षर id[CTCM_ID_SIZE];
	काष्ठा ccw_device *cdev;
	/*
	 * Type of this channel.
	 * CTC/A or Escon क्रम valid channels.
	 */
	क्रमागत ctcm_channel_types type;
	/*
	 * Misc. flags. See CHANNEL_FLAGS_... below
	 */
	__u32 flags;
	__u16 protocol;		/* protocol of this channel (4 = MPC) */
	/*
	 * I/O and irq related stuff
	 */
	काष्ठा ccw1 *ccw;
	काष्ठा irb *irb;
	/*
	 * RX/TX buffer size
	 */
	पूर्णांक max_bufsize;
	काष्ठा sk_buff *trans_skb;	/* transmit/receive buffer */
	काष्ठा sk_buff_head io_queue;	/* universal I/O queue */
	काष्ठा tasklet_काष्ठा ch_tasklet;	/* MPC ONLY */
	/*
	 * TX queue क्रम collecting skb's during busy.
	 */
	काष्ठा sk_buff_head collect_queue;
	/*
	 * Amount of data in collect_queue.
	 */
	पूर्णांक collect_len;
	/*
	 * spinlock क्रम collect_queue and collect_len
	 */
	spinlock_t collect_lock;
	/*
	 * Timer क्रम detecting unresposive
	 * I/O operations.
	 */
	fsm_समयr समयr;
	/* MPC ONLY section begin */
	__u32	th_seq_num;	/* SNA TH seq number */
	__u8	th_seg;
	__u32	pdu_seq;
	काष्ठा sk_buff		*xid_skb;
	अक्षर			*xid_skb_data;
	काष्ठा th_header	*xid_th;
	काष्ठा xid2		*xid;
	अक्षर			*xid_id;
	काष्ठा th_header	*rcvd_xid_th;
	काष्ठा xid2		*rcvd_xid;
	अक्षर			*rcvd_xid_id;
	__u8			in_mpcgroup;
	fsm_समयr		sweep_समयr;
	काष्ठा sk_buff_head	sweep_queue;
	काष्ठा th_header	*discontact_th;
	काष्ठा tasklet_काष्ठा	ch_disc_tasklet;
	/* MPC ONLY section end */

	पूर्णांक retry;		/* retry counter क्रम misc. operations */
	fsm_instance *fsm;	/* finite state machine of this channel */
	काष्ठा net_device *netdev;	/* corresponding net_device */
	काष्ठा ctcm_profile prof;
	__u8 *trans_skb_data;
	__u16 logflags;
	__u8  sense_rc; /* last unit check sense code report control */
पूर्ण;

काष्ठा ctcm_priv अणु
	काष्ठा net_device_stats	stats;
	अचिन्हित दीर्घ	tbusy;

	/* The MPC group काष्ठा of this पूर्णांकerface */
	काष्ठा	mpc_group	*mpcg;	/* MPC only */
	काष्ठा	xid2		*xid;	/* MPC only */

	/* The finite state machine of this पूर्णांकerface */
	fsm_instance *fsm;

	/* The protocol of this device */
	__u16 protocol;

	/* Timer क्रम restarting after I/O Errors */
	fsm_समयr	restart_समयr;

	पूर्णांक buffer_size;	/* ctc only */

	काष्ठा channel *channel[2];
पूर्ण;

पूर्णांक ctcm_खोलो(काष्ठा net_device *dev);
पूर्णांक ctcm_बंद(काष्ठा net_device *dev);

बाह्य स्थिर काष्ठा attribute_group *ctcm_attr_groups[];

/*
 * Compatibility macros क्रम busy handling
 * of network devices.
 */
अटल अंतरभूत व्योम ctcm_clear_busy_करो(काष्ठा net_device *dev)
अणु
	clear_bit(0, &(((काष्ठा ctcm_priv *)dev->ml_priv)->tbusy));
	netअगर_wake_queue(dev);
पूर्ण

अटल अंतरभूत व्योम ctcm_clear_busy(काष्ठा net_device *dev)
अणु
	काष्ठा mpc_group *grp;
	grp = ((काष्ठा ctcm_priv *)dev->ml_priv)->mpcg;

	अगर (!(grp && grp->in_sweep))
		ctcm_clear_busy_करो(dev);
पूर्ण


अटल अंतरभूत पूर्णांक ctcm_test_and_set_busy(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस test_and_set_bit(0,
			&(((काष्ठा ctcm_priv *)dev->ml_priv)->tbusy));
पूर्ण

बाह्य पूर्णांक loglevel;
बाह्य काष्ठा channel *channels;

व्योम ctcm_unpack_skb(काष्ठा channel *ch, काष्ठा sk_buff *pskb);

/*
 * Functions related to setup and device detection.
 */

अटल अंतरभूत पूर्णांक ctcm_less_than(अक्षर *id1, अक्षर *id2)
अणु
	अचिन्हित दीर्घ dev1, dev2;

	id1 = id1 + 5;
	id2 = id2 + 5;

	dev1 = simple_म_से_अदीर्घ(id1, &id1, 16);
	dev2 = simple_म_से_अदीर्घ(id2, &id2, 16);

	वापस (dev1 < dev2);
पूर्ण

पूर्णांक ctcm_ch_alloc_buffer(काष्ठा channel *ch);

अटल अंतरभूत पूर्णांक ctcm_checkalloc_buffer(काष्ठा channel *ch)
अणु
	अगर (ch->trans_skb == शून्य)
		वापस ctcm_ch_alloc_buffer(ch);
	अगर (ch->flags & CHANNEL_FLAGS_बफ_मानE_CHANGED) अणु
		dev_kमुक्त_skb(ch->trans_skb);
		वापस ctcm_ch_alloc_buffer(ch);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा mpc_group *ctcmpc_init_mpc_group(काष्ठा ctcm_priv *priv);

/* test अगर protocol attribute (of काष्ठा ctcm_priv or काष्ठा channel)
 * has MPC protocol setting. Type is not checked
 */
#घोषणा IS_MPC(p) ((p)->protocol == CTCM_PROTO_MPC)

/* test अगर काष्ठा ctcm_priv of काष्ठा net_device has MPC protocol setting */
#घोषणा IS_MPCDEV(dev) IS_MPC((काष्ठा ctcm_priv *)dev->ml_priv)

/*
 * Definition of our link level header.
 */
काष्ठा ll_header अणु
	__u16 length;
	__u16 type;
	__u16 unused;
पूर्ण;
#घोषणा LL_HEADER_LENGTH (माप(काष्ठा ll_header))

#पूर्ण_अगर
