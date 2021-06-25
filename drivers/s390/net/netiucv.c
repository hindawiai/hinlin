<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IUCV network driver
 *
 * Copyright IBM Corp. 2001, 2009
 *
 * Author(s):
 *	Original netiucv driver:
 *		Fritz Elfert (elfert@de.ibm.com, felfert@millenux.com)
 *	Sysfs पूर्णांकegration and all bugs therein:
 *		Cornelia Huck (cornelia.huck@de.ibm.com)
 *	PM functions:
 *		Ursula Braun (ursula.braun@de.ibm.com)
 *
 * Documentation used:
 *  the source of the original IUCV driver by:
 *    Stefan Hegewald <hegewald@de.ibm.com>
 *    Harपंचांगut Penner <hpenner@de.ibm.com>
 *    Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 *    Martin Schwidefsky (schwidefsky@de.ibm.com)
 *    Alan Alपंचांगark (Alan_Alपंचांगark@us.ibm.com)  Sept. 2000
 */

#घोषणा KMSG_COMPONENT "netiucv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>

#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <net/dst.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ebcdic.h>

#समावेश <net/iucv/iucv.h>
#समावेश "fsm.h"

MODULE_AUTHOR
    ("(C) 2001 IBM Corporation by Fritz Elfert (felfert@millenux.com)");
MODULE_DESCRIPTION ("Linux for S/390 IUCV network driver");

/**
 * Debug Facility stuff
 */
#घोषणा IUCV_DBF_SETUP_NAME "iucv_setup"
#घोषणा IUCV_DBF_SETUP_LEN 64
#घोषणा IUCV_DBF_SETUP_PAGES 2
#घोषणा IUCV_DBF_SETUP_NR_AREAS 1
#घोषणा IUCV_DBF_SETUP_LEVEL 3

#घोषणा IUCV_DBF_DATA_NAME "iucv_data"
#घोषणा IUCV_DBF_DATA_LEN 128
#घोषणा IUCV_DBF_DATA_PAGES 2
#घोषणा IUCV_DBF_DATA_NR_AREAS 1
#घोषणा IUCV_DBF_DATA_LEVEL 2

#घोषणा IUCV_DBF_TRACE_NAME "iucv_trace"
#घोषणा IUCV_DBF_TRACE_LEN 16
#घोषणा IUCV_DBF_TRACE_PAGES 4
#घोषणा IUCV_DBF_TRACE_NR_AREAS 1
#घोषणा IUCV_DBF_TRACE_LEVEL 3

#घोषणा IUCV_DBF_TEXT(name,level,text) \
	करो अणु \
		debug_text_event(iucv_dbf_##name,level,text); \
	पूर्ण जबतक (0)

#घोषणा IUCV_DBF_HEX(name,level,addr,len) \
	करो अणु \
		debug_event(iucv_dbf_##name,level,(व्योम*)(addr),len); \
	पूर्ण जबतक (0)

DECLARE_PER_CPU(अक्षर[256], iucv_dbf_txt_buf);

#घोषणा IUCV_DBF_TEXT_(name, level, text...) \
	करो अणु \
		अगर (debug_level_enabled(iucv_dbf_##name, level)) अणु \
			अक्षर* __buf = get_cpu_var(iucv_dbf_txt_buf); \
			प्र_लिखो(__buf, text); \
			debug_text_event(iucv_dbf_##name, level, __buf); \
			put_cpu_var(iucv_dbf_txt_buf); \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा IUCV_DBF_SPRINTF(name,level,text...) \
	करो अणु \
		debug_प्र_लिखो_event(iucv_dbf_trace, level, ##text ); \
		debug_प्र_लिखो_event(iucv_dbf_trace, level, text ); \
	पूर्ण जबतक (0)

/**
 * some more debug stuff
 */
#घोषणा PRINTK_HEADER " iucv: "       /* क्रम debugging */

अटल काष्ठा device_driver netiucv_driver = अणु
	.owner = THIS_MODULE,
	.name = "netiucv",
	.bus  = &iucv_bus,
पूर्ण;

अटल पूर्णांक netiucv_callback_connreq(काष्ठा iucv_path *, u8 *, u8 *);
अटल व्योम netiucv_callback_connack(काष्ठा iucv_path *, u8 *);
अटल व्योम netiucv_callback_connrej(काष्ठा iucv_path *, u8 *);
अटल व्योम netiucv_callback_connsusp(काष्ठा iucv_path *, u8 *);
अटल व्योम netiucv_callback_connres(काष्ठा iucv_path *, u8 *);
अटल व्योम netiucv_callback_rx(काष्ठा iucv_path *, काष्ठा iucv_message *);
अटल व्योम netiucv_callback_txकरोne(काष्ठा iucv_path *, काष्ठा iucv_message *);

अटल काष्ठा iucv_handler netiucv_handler = अणु
	.path_pending	  = netiucv_callback_connreq,
	.path_complete	  = netiucv_callback_connack,
	.path_severed	  = netiucv_callback_connrej,
	.path_quiesced	  = netiucv_callback_connsusp,
	.path_resumed	  = netiucv_callback_connres,
	.message_pending  = netiucv_callback_rx,
	.message_complete = netiucv_callback_txकरोne
पूर्ण;

/**
 * Per connection profiling data
 */
काष्ठा connection_profile अणु
	अचिन्हित दीर्घ maxmulti;
	अचिन्हित दीर्घ maxcqueue;
	अचिन्हित दीर्घ करोios_single;
	अचिन्हित दीर्घ करोios_multi;
	अचिन्हित दीर्घ txlen;
	अचिन्हित दीर्घ tx_समय;
	अचिन्हित दीर्घ send_stamp;
	अचिन्हित दीर्घ tx_pending;
	अचिन्हित दीर्घ tx_max_pending;
पूर्ण;

/**
 * Representation of one iucv connection
 */
काष्ठा iucv_connection अणु
	काष्ठा list_head	  list;
	काष्ठा iucv_path	  *path;
	काष्ठा sk_buff            *rx_buff;
	काष्ठा sk_buff            *tx_buff;
	काष्ठा sk_buff_head       collect_queue;
	काष्ठा sk_buff_head	  commit_queue;
	spinlock_t                collect_lock;
	पूर्णांक                       collect_len;
	पूर्णांक                       max_buffsize;
	fsm_समयr                 समयr;
	fsm_instance              *fsm;
	काष्ठा net_device         *netdev;
	काष्ठा connection_profile prof;
	अक्षर                      userid[9];
	अक्षर			  userdata[17];
पूर्ण;

/**
 * Linked list of all connection काष्ठाs.
 */
अटल LIST_HEAD(iucv_connection_list);
अटल DEFINE_RWLOCK(iucv_connection_rwlock);

/**
 * Representation of event-data क्रम the
 * connection state machine.
 */
काष्ठा iucv_event अणु
	काष्ठा iucv_connection *conn;
	व्योम                   *data;
पूर्ण;

/**
 * Private part of the network device काष्ठाure
 */
काष्ठा netiucv_priv अणु
	काष्ठा net_device_stats stats;
	अचिन्हित दीर्घ           tbusy;
	fsm_instance            *fsm;
        काष्ठा iucv_connection  *conn;
	काष्ठा device           *dev;
पूर्ण;

/**
 * Link level header क्रम a packet.
 */
काष्ठा ll_header अणु
	u16 next;
पूर्ण;

#घोषणा NETIUCV_HDRLEN		 (माप(काष्ठा ll_header))
#घोषणा NETIUCV_बफ_मानE_MAX	 65537
#घोषणा NETIUCV_बफ_मानE_DEFAULT  NETIUCV_बफ_मानE_MAX
#घोषणा NETIUCV_MTU_MAX          (NETIUCV_बफ_मानE_MAX - NETIUCV_HDRLEN)
#घोषणा NETIUCV_MTU_DEFAULT      9216
#घोषणा NETIUCV_QUEUELEN_DEFAULT 50
#घोषणा NETIUCV_TIMEOUT_5SEC     5000

/**
 * Compatibility macros क्रम busy handling
 * of network devices.
 */
अटल व्योम netiucv_clear_busy(काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(dev);
	clear_bit(0, &priv->tbusy);
	netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक netiucv_test_and_set_busy(काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(dev);
	netअगर_stop_queue(dev);
	वापस test_and_set_bit(0, &priv->tbusy);
पूर्ण

अटल u8 iucvMagic_ascii[16] = अणु
	0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
पूर्ण;

अटल u8 iucvMagic_ebcdic[16] = अणु
	0xF0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
	0xF0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
पूर्ण;

/**
 * Convert an iucv userId to its prपूर्णांकable
 * क्रमm (strip whitespace at end).
 *
 * @param An iucv userId
 *
 * @वापसs The prपूर्णांकable string (अटल data!!)
 */
अटल अक्षर *netiucv_prपूर्णांकname(अक्षर *name, पूर्णांक len)
अणु
	अटल अक्षर पंचांगp[17];
	अक्षर *p = पंचांगp;
	स_नकल(पंचांगp, name, len);
	पंचांगp[len] = '\0';
	जबतक (*p && ((p - पंचांगp) < len) && (!है_खाली(*p)))
		p++;
	*p = '\0';
	वापस पंचांगp;
पूर्ण

अटल अक्षर *netiucv_prपूर्णांकuser(काष्ठा iucv_connection *conn)
अणु
	अटल अक्षर पंचांगp_uid[9];
	अटल अक्षर पंचांगp_udat[17];
	अटल अक्षर buf[100];

	अगर (स_भेद(conn->userdata, iucvMagic_ebcdic, 16)) अणु
		पंचांगp_uid[8] = '\0';
		पंचांगp_udat[16] = '\0';
		स_नकल(पंचांगp_uid, netiucv_prपूर्णांकname(conn->userid, 8), 8);
		स_नकल(पंचांगp_udat, conn->userdata, 16);
		EBCASC(पंचांगp_udat, 16);
		स_नकल(पंचांगp_udat, netiucv_prपूर्णांकname(पंचांगp_udat, 16), 16);
		प्र_लिखो(buf, "%s.%s", पंचांगp_uid, पंचांगp_udat);
		वापस buf;
	पूर्ण अन्यथा
		वापस netiucv_prपूर्णांकname(conn->userid, 8);
पूर्ण

/**
 * States of the पूर्णांकerface statemachine.
 */
क्रमागत dev_states अणु
	DEV_STATE_STOPPED,
	DEV_STATE_STARTWAIT,
	DEV_STATE_STOPWAIT,
	DEV_STATE_RUNNING,
	/**
	 * MUST be always the last element!!
	 */
	NR_DEV_STATES
पूर्ण;

अटल स्थिर अक्षर *dev_state_names[] = अणु
	"Stopped",
	"StartWait",
	"StopWait",
	"Running",
पूर्ण;

/**
 * Events of the पूर्णांकerface statemachine.
 */
क्रमागत dev_events अणु
	DEV_EVENT_START,
	DEV_EVENT_STOP,
	DEV_EVENT_CONUP,
	DEV_EVENT_CONDOWN,
	/**
	 * MUST be always the last element!!
	 */
	NR_DEV_EVENTS
पूर्ण;

अटल स्थिर अक्षर *dev_event_names[] = अणु
	"Start",
	"Stop",
	"Connection up",
	"Connection down",
पूर्ण;

/**
 * Events of the connection statemachine
 */
क्रमागत conn_events अणु
	/**
	 * Events, representing callbacks from
	 * lowlevel iucv layer)
	 */
	CONN_EVENT_CONN_REQ,
	CONN_EVENT_CONN_ACK,
	CONN_EVENT_CONN_REJ,
	CONN_EVENT_CONN_SUS,
	CONN_EVENT_CONN_RES,
	CONN_EVENT_RX,
	CONN_EVENT_TXDONE,

	/**
	 * Events, representing errors वापस codes from
	 * calls to lowlevel iucv layer
	 */

	/**
	 * Event, representing समयr expiry.
	 */
	CONN_EVENT_TIMER,

	/**
	 * Events, representing commands from upper levels.
	 */
	CONN_EVENT_START,
	CONN_EVENT_STOP,

	/**
	 * MUST be always the last element!!
	 */
	NR_CONN_EVENTS,
पूर्ण;

अटल स्थिर अक्षर *conn_event_names[] = अणु
	"Remote connection request",
	"Remote connection acknowledge",
	"Remote connection reject",
	"Connection suspended",
	"Connection resumed",
	"Data received",
	"Data sent",

	"Timer",

	"Start",
	"Stop",
पूर्ण;

/**
 * States of the connection statemachine.
 */
क्रमागत conn_states अणु
	/**
	 * Connection not asचिन्हित to any device,
	 * initial state, invalid
	 */
	CONN_STATE_INVALID,

	/**
	 * Userid asचिन्हित but not operating
	 */
	CONN_STATE_STOPPED,

	/**
	 * Connection रेजिस्टरed,
	 * no connection request sent yet,
	 * no connection request received
	 */
	CONN_STATE_STARTWAIT,

	/**
	 * Connection रेजिस्टरed and connection request sent,
	 * no acknowledge and no connection request received yet.
	 */
	CONN_STATE_SETUPWAIT,

	/**
	 * Connection up and running idle
	 */
	CONN_STATE_IDLE,

	/**
	 * Data sent, aरुकोing CONN_EVENT_TXDONE
	 */
	CONN_STATE_TX,

	/**
	 * Error during registration.
	 */
	CONN_STATE_REGERR,

	/**
	 * Error during registration.
	 */
	CONN_STATE_CONNERR,

	/**
	 * MUST be always the last element!!
	 */
	NR_CONN_STATES,
पूर्ण;

अटल स्थिर अक्षर *conn_state_names[] = अणु
	"Invalid",
	"Stopped",
	"StartWait",
	"SetupWait",
	"Idle",
	"TX",
	"Terminating",
	"Registration error",
	"Connect error",
पूर्ण;


/**
 * Debug Facility Stuff
 */
अटल debug_info_t *iucv_dbf_setup = शून्य;
अटल debug_info_t *iucv_dbf_data = शून्य;
अटल debug_info_t *iucv_dbf_trace = शून्य;

DEFINE_PER_CPU(अक्षर[256], iucv_dbf_txt_buf);

अटल व्योम iucv_unरेजिस्टर_dbf_views(व्योम)
अणु
	debug_unरेजिस्टर(iucv_dbf_setup);
	debug_unरेजिस्टर(iucv_dbf_data);
	debug_unरेजिस्टर(iucv_dbf_trace);
पूर्ण
अटल पूर्णांक iucv_रेजिस्टर_dbf_views(व्योम)
अणु
	iucv_dbf_setup = debug_रेजिस्टर(IUCV_DBF_SETUP_NAME,
					IUCV_DBF_SETUP_PAGES,
					IUCV_DBF_SETUP_NR_AREAS,
					IUCV_DBF_SETUP_LEN);
	iucv_dbf_data = debug_रेजिस्टर(IUCV_DBF_DATA_NAME,
				       IUCV_DBF_DATA_PAGES,
				       IUCV_DBF_DATA_NR_AREAS,
				       IUCV_DBF_DATA_LEN);
	iucv_dbf_trace = debug_रेजिस्टर(IUCV_DBF_TRACE_NAME,
					IUCV_DBF_TRACE_PAGES,
					IUCV_DBF_TRACE_NR_AREAS,
					IUCV_DBF_TRACE_LEN);

	अगर ((iucv_dbf_setup == शून्य) || (iucv_dbf_data == शून्य) ||
	    (iucv_dbf_trace == शून्य)) अणु
		iucv_unरेजिस्टर_dbf_views();
		वापस -ENOMEM;
	पूर्ण
	debug_रेजिस्टर_view(iucv_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_setup, IUCV_DBF_SETUP_LEVEL);

	debug_रेजिस्टर_view(iucv_dbf_data, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_data, IUCV_DBF_DATA_LEVEL);

	debug_रेजिस्टर_view(iucv_dbf_trace, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_trace, IUCV_DBF_TRACE_LEVEL);

	वापस 0;
पूर्ण

/*
 * Callback-wrappers, called from lowlevel iucv layer.
 */

अटल व्योम netiucv_callback_rx(काष्ठा iucv_path *path,
				काष्ठा iucv_message *msg)
अणु
	काष्ठा iucv_connection *conn = path->निजी;
	काष्ठा iucv_event ev;

	ev.conn = conn;
	ev.data = msg;
	fsm_event(conn->fsm, CONN_EVENT_RX, &ev);
पूर्ण

अटल व्योम netiucv_callback_txकरोne(काष्ठा iucv_path *path,
				    काष्ठा iucv_message *msg)
अणु
	काष्ठा iucv_connection *conn = path->निजी;
	काष्ठा iucv_event ev;

	ev.conn = conn;
	ev.data = msg;
	fsm_event(conn->fsm, CONN_EVENT_TXDONE, &ev);
पूर्ण

अटल व्योम netiucv_callback_connack(काष्ठा iucv_path *path, u8 ipuser[16])
अणु
	काष्ठा iucv_connection *conn = path->निजी;

	fsm_event(conn->fsm, CONN_EVENT_CONN_ACK, conn);
पूर्ण

अटल पूर्णांक netiucv_callback_connreq(काष्ठा iucv_path *path, u8 *ipvmid,
				    u8 *ipuser)
अणु
	काष्ठा iucv_connection *conn = path->निजी;
	काष्ठा iucv_event ev;
	अटल अक्षर पंचांगp_user[9];
	अटल अक्षर पंचांगp_udat[17];
	पूर्णांक rc;

	rc = -EINVAL;
	स_नकल(पंचांगp_user, netiucv_prपूर्णांकname(ipvmid, 8), 8);
	स_नकल(पंचांगp_udat, ipuser, 16);
	EBCASC(पंचांगp_udat, 16);
	पढ़ो_lock_bh(&iucv_connection_rwlock);
	list_क्रम_each_entry(conn, &iucv_connection_list, list) अणु
		अगर (म_भेदन(ipvmid, conn->userid, 8) ||
		    म_भेदन(ipuser, conn->userdata, 16))
			जारी;
		/* Found a matching connection क्रम this path. */
		conn->path = path;
		ev.conn = conn;
		ev.data = path;
		fsm_event(conn->fsm, CONN_EVENT_CONN_REQ, &ev);
		rc = 0;
	पूर्ण
	IUCV_DBF_TEXT_(setup, 2, "Connection requested for %s.%s\n",
		       पंचांगp_user, netiucv_prपूर्णांकname(पंचांगp_udat, 16));
	पढ़ो_unlock_bh(&iucv_connection_rwlock);
	वापस rc;
पूर्ण

अटल व्योम netiucv_callback_connrej(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा iucv_connection *conn = path->निजी;

	fsm_event(conn->fsm, CONN_EVENT_CONN_REJ, conn);
पूर्ण

अटल व्योम netiucv_callback_connsusp(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा iucv_connection *conn = path->निजी;

	fsm_event(conn->fsm, CONN_EVENT_CONN_SUS, conn);
पूर्ण

अटल व्योम netiucv_callback_connres(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा iucv_connection *conn = path->निजी;

	fsm_event(conn->fsm, CONN_EVENT_CONN_RES, conn);
पूर्ण

/**
 * NOP action क्रम statemachines
 */
अटल व्योम netiucv_action_nop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
पूर्ण

/*
 * Actions of the connection statemachine
 */

/**
 * netiucv_unpack_skb
 * @conn: The connection where this skb has been received.
 * @pskb: The received skb.
 *
 * Unpack a just received skb and hand it over to upper layers.
 * Helper function क्रम conn_action_rx.
 */
अटल व्योम netiucv_unpack_skb(काष्ठा iucv_connection *conn,
			       काष्ठा sk_buff *pskb)
अणु
	काष्ठा net_device     *dev = conn->netdev;
	काष्ठा netiucv_priv   *privptr = netdev_priv(dev);
	u16 offset = 0;

	skb_put(pskb, NETIUCV_HDRLEN);
	pskb->dev = dev;
	pskb->ip_summed = CHECKSUM_NONE;
	pskb->protocol = cpu_to_be16(ETH_P_IP);

	जबतक (1) अणु
		काष्ठा sk_buff *skb;
		काष्ठा ll_header *header = (काष्ठा ll_header *) pskb->data;

		अगर (!header->next)
			अवरोध;

		skb_pull(pskb, NETIUCV_HDRLEN);
		header->next -= offset;
		offset += header->next;
		header->next -= NETIUCV_HDRLEN;
		अगर (skb_tailroom(pskb) < header->next) अणु
			IUCV_DBF_TEXT_(data, 2, "Illegal next field: %d > %d\n",
				header->next, skb_tailroom(pskb));
			वापस;
		पूर्ण
		skb_put(pskb, header->next);
		skb_reset_mac_header(pskb);
		skb = dev_alloc_skb(pskb->len);
		अगर (!skb) अणु
			IUCV_DBF_TEXT(data, 2,
				"Out of memory in netiucv_unpack_skb\n");
			privptr->stats.rx_dropped++;
			वापस;
		पूर्ण
		skb_copy_from_linear_data(pskb, skb_put(skb, pskb->len),
					  pskb->len);
		skb_reset_mac_header(skb);
		skb->dev = pskb->dev;
		skb->protocol = pskb->protocol;
		pskb->ip_summed = CHECKSUM_UNNECESSARY;
		privptr->stats.rx_packets++;
		privptr->stats.rx_bytes += skb->len;
		/*
		 * Since receiving is always initiated from a tasklet (in iucv.c),
		 * we must use netअगर_rx_ni() instead of netअगर_rx()
		 */
		netअगर_rx_ni(skb);
		skb_pull(pskb, header->next);
		skb_put(pskb, NETIUCV_HDRLEN);
	पूर्ण
पूर्ण

अटल व्योम conn_action_rx(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_event *ev = arg;
	काष्ठा iucv_connection *conn = ev->conn;
	काष्ठा iucv_message *msg = ev->data;
	काष्ठा netiucv_priv *privptr = netdev_priv(conn->netdev);
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 4, __func__);

	अगर (!conn->netdev) अणु
		iucv_message_reject(conn->path, msg);
		IUCV_DBF_TEXT(data, 2,
			      "Received data for unlinked connection\n");
		वापस;
	पूर्ण
	अगर (msg->length > conn->max_buffsize) अणु
		iucv_message_reject(conn->path, msg);
		privptr->stats.rx_dropped++;
		IUCV_DBF_TEXT_(data, 2, "msglen %d > max_buffsize %d\n",
			       msg->length, conn->max_buffsize);
		वापस;
	पूर्ण
	conn->rx_buff->data = conn->rx_buff->head;
	skb_reset_tail_poपूर्णांकer(conn->rx_buff);
	conn->rx_buff->len = 0;
	rc = iucv_message_receive(conn->path, msg, 0, conn->rx_buff->data,
				  msg->length, शून्य);
	अगर (rc || msg->length < 5) अणु
		privptr->stats.rx_errors++;
		IUCV_DBF_TEXT_(data, 2, "rc %d from iucv_receive\n", rc);
		वापस;
	पूर्ण
	netiucv_unpack_skb(conn, conn->rx_buff);
पूर्ण

अटल व्योम conn_action_txकरोne(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_event *ev = arg;
	काष्ठा iucv_connection *conn = ev->conn;
	काष्ठा iucv_message *msg = ev->data;
	काष्ठा iucv_message txmsg;
	काष्ठा netiucv_priv *privptr = शून्य;
	u32 single_flag = msg->tag;
	u32 txbytes = 0;
	u32 txpackets = 0;
	u32 stat_maxcq = 0;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ saveflags;
	काष्ठा ll_header header;
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 4, __func__);

	अगर (!conn || !conn->netdev) अणु
		IUCV_DBF_TEXT(data, 2,
			      "Send confirmation for unlinked connection\n");
		वापस;
	पूर्ण
	privptr = netdev_priv(conn->netdev);
	conn->prof.tx_pending--;
	अगर (single_flag) अणु
		अगर ((skb = skb_dequeue(&conn->commit_queue))) अणु
			refcount_dec(&skb->users);
			अगर (privptr) अणु
				privptr->stats.tx_packets++;
				privptr->stats.tx_bytes +=
					(skb->len - NETIUCV_HDRLEN
						  - NETIUCV_HDRLEN);
			पूर्ण
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण
	conn->tx_buff->data = conn->tx_buff->head;
	skb_reset_tail_poपूर्णांकer(conn->tx_buff);
	conn->tx_buff->len = 0;
	spin_lock_irqsave(&conn->collect_lock, saveflags);
	जबतक ((skb = skb_dequeue(&conn->collect_queue))) अणु
		header.next = conn->tx_buff->len + skb->len + NETIUCV_HDRLEN;
		skb_put_data(conn->tx_buff, &header, NETIUCV_HDRLEN);
		skb_copy_from_linear_data(skb,
					  skb_put(conn->tx_buff, skb->len),
					  skb->len);
		txbytes += skb->len;
		txpackets++;
		stat_maxcq++;
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
	अगर (conn->collect_len > conn->prof.maxmulti)
		conn->prof.maxmulti = conn->collect_len;
	conn->collect_len = 0;
	spin_unlock_irqrestore(&conn->collect_lock, saveflags);
	अगर (conn->tx_buff->len == 0) अणु
		fsm_newstate(fi, CONN_STATE_IDLE);
		वापस;
	पूर्ण

	header.next = 0;
	skb_put_data(conn->tx_buff, &header, NETIUCV_HDRLEN);
	conn->prof.send_stamp = jअगरfies;
	txmsg.class = 0;
	txmsg.tag = 0;
	rc = iucv_message_send(conn->path, &txmsg, 0, 0,
			       conn->tx_buff->data, conn->tx_buff->len);
	conn->prof.करोios_multi++;
	conn->prof.txlen += conn->tx_buff->len;
	conn->prof.tx_pending++;
	अगर (conn->prof.tx_pending > conn->prof.tx_max_pending)
		conn->prof.tx_max_pending = conn->prof.tx_pending;
	अगर (rc) अणु
		conn->prof.tx_pending--;
		fsm_newstate(fi, CONN_STATE_IDLE);
		अगर (privptr)
			privptr->stats.tx_errors += txpackets;
		IUCV_DBF_TEXT_(data, 2, "rc %d from iucv_send\n", rc);
	पूर्ण अन्यथा अणु
		अगर (privptr) अणु
			privptr->stats.tx_packets += txpackets;
			privptr->stats.tx_bytes += txbytes;
		पूर्ण
		अगर (stat_maxcq > conn->prof.maxcqueue)
			conn->prof.maxcqueue = stat_maxcq;
	पूर्ण
पूर्ण

अटल व्योम conn_action_connaccept(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_event *ev = arg;
	काष्ठा iucv_connection *conn = ev->conn;
	काष्ठा iucv_path *path = ev->data;
	काष्ठा net_device *netdev = conn->netdev;
	काष्ठा netiucv_priv *privptr = netdev_priv(netdev);
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 3, __func__);

	conn->path = path;
	path->msglim = NETIUCV_QUEUELEN_DEFAULT;
	path->flags = 0;
	rc = iucv_path_accept(path, &netiucv_handler, conn->userdata , conn);
	अगर (rc) अणु
		IUCV_DBF_TEXT_(setup, 2, "rc %d from iucv_accept", rc);
		वापस;
	पूर्ण
	fsm_newstate(fi, CONN_STATE_IDLE);
	netdev->tx_queue_len = conn->path->msglim;
	fsm_event(privptr->fsm, DEV_EVENT_CONUP, netdev);
पूर्ण

अटल व्योम conn_action_connreject(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_event *ev = arg;
	काष्ठा iucv_path *path = ev->data;

	IUCV_DBF_TEXT(trace, 3, __func__);
	iucv_path_sever(path, शून्य);
पूर्ण

अटल व्योम conn_action_connack(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_connection *conn = arg;
	काष्ठा net_device *netdev = conn->netdev;
	काष्ठा netiucv_priv *privptr = netdev_priv(netdev);

	IUCV_DBF_TEXT(trace, 3, __func__);
	fsm_delसमयr(&conn->समयr);
	fsm_newstate(fi, CONN_STATE_IDLE);
	netdev->tx_queue_len = conn->path->msglim;
	fsm_event(privptr->fsm, DEV_EVENT_CONUP, netdev);
पूर्ण

अटल व्योम conn_action_conntimsev(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_connection *conn = arg;

	IUCV_DBF_TEXT(trace, 3, __func__);
	fsm_delसमयr(&conn->समयr);
	iucv_path_sever(conn->path, conn->userdata);
	fsm_newstate(fi, CONN_STATE_STARTWAIT);
पूर्ण

अटल व्योम conn_action_connsever(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_connection *conn = arg;
	काष्ठा net_device *netdev = conn->netdev;
	काष्ठा netiucv_priv *privptr = netdev_priv(netdev);

	IUCV_DBF_TEXT(trace, 3, __func__);

	fsm_delसमयr(&conn->समयr);
	iucv_path_sever(conn->path, conn->userdata);
	dev_info(privptr->dev, "The peer z/VM guest %s has closed the "
			       "connection\n", netiucv_prपूर्णांकuser(conn));
	IUCV_DBF_TEXT(data, 2,
		      "conn_action_connsever: Remote dropped connection\n");
	fsm_newstate(fi, CONN_STATE_STARTWAIT);
	fsm_event(privptr->fsm, DEV_EVENT_CONDOWN, netdev);
पूर्ण

अटल व्योम conn_action_start(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_connection *conn = arg;
	काष्ठा net_device *netdev = conn->netdev;
	काष्ठा netiucv_priv *privptr = netdev_priv(netdev);
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 3, __func__);

	fsm_newstate(fi, CONN_STATE_STARTWAIT);

	/*
	 * We must set the state beक्रमe calling iucv_connect because the
	 * callback handler could be called at any poपूर्णांक after the connection
	 * request is sent
	 */

	fsm_newstate(fi, CONN_STATE_SETUPWAIT);
	conn->path = iucv_path_alloc(NETIUCV_QUEUELEN_DEFAULT, 0, GFP_KERNEL);
	IUCV_DBF_TEXT_(setup, 2, "%s: connecting to %s ...\n",
		netdev->name, netiucv_prपूर्णांकuser(conn));

	rc = iucv_path_connect(conn->path, &netiucv_handler, conn->userid,
			       शून्य, conn->userdata, conn);
	चयन (rc) अणु
	हाल 0:
		netdev->tx_queue_len = conn->path->msglim;
		fsm_addसमयr(&conn->समयr, NETIUCV_TIMEOUT_5SEC,
			     CONN_EVENT_TIMER, conn);
		वापस;
	हाल 11:
		dev_warn(privptr->dev,
			"The IUCV device failed to connect to z/VM guest %s\n",
			netiucv_prपूर्णांकname(conn->userid, 8));
		fsm_newstate(fi, CONN_STATE_STARTWAIT);
		अवरोध;
	हाल 12:
		dev_warn(privptr->dev,
			"The IUCV device failed to connect to the peer on z/VM"
			" guest %s\n", netiucv_prपूर्णांकname(conn->userid, 8));
		fsm_newstate(fi, CONN_STATE_STARTWAIT);
		अवरोध;
	हाल 13:
		dev_err(privptr->dev,
			"Connecting the IUCV device would exceed the maximum"
			" number of IUCV connections\n");
		fsm_newstate(fi, CONN_STATE_CONNERR);
		अवरोध;
	हाल 14:
		dev_err(privptr->dev,
			"z/VM guest %s has too many IUCV connections"
			" to connect with the IUCV device\n",
			netiucv_prपूर्णांकname(conn->userid, 8));
		fsm_newstate(fi, CONN_STATE_CONNERR);
		अवरोध;
	हाल 15:
		dev_err(privptr->dev,
			"The IUCV device cannot connect to a z/VM guest with no"
			" IUCV authorization\n");
		fsm_newstate(fi, CONN_STATE_CONNERR);
		अवरोध;
	शेष:
		dev_err(privptr->dev,
			"Connecting the IUCV device failed with error %d\n",
			rc);
		fsm_newstate(fi, CONN_STATE_CONNERR);
		अवरोध;
	पूर्ण
	IUCV_DBF_TEXT_(setup, 5, "iucv_connect rc is %d\n", rc);
	kमुक्त(conn->path);
	conn->path = शून्य;
पूर्ण

अटल व्योम netiucv_purge_skb_queue(काष्ठा sk_buff_head *q)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(q))) अणु
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम conn_action_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_event *ev = arg;
	काष्ठा iucv_connection *conn = ev->conn;
	काष्ठा net_device *netdev = conn->netdev;
	काष्ठा netiucv_priv *privptr = netdev_priv(netdev);

	IUCV_DBF_TEXT(trace, 3, __func__);

	fsm_delसमयr(&conn->समयr);
	fsm_newstate(fi, CONN_STATE_STOPPED);
	netiucv_purge_skb_queue(&conn->collect_queue);
	अगर (conn->path) अणु
		IUCV_DBF_TEXT(trace, 5, "calling iucv_path_sever\n");
		iucv_path_sever(conn->path, conn->userdata);
		kमुक्त(conn->path);
		conn->path = शून्य;
	पूर्ण
	netiucv_purge_skb_queue(&conn->commit_queue);
	fsm_event(privptr->fsm, DEV_EVENT_CONDOWN, netdev);
पूर्ण

अटल व्योम conn_action_inval(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा iucv_connection *conn = arg;
	काष्ठा net_device *netdev = conn->netdev;

	IUCV_DBF_TEXT_(data, 2, "%s('%s'): conn_action_inval called\n",
		netdev->name, conn->userid);
पूर्ण

अटल स्थिर fsm_node conn_fsm[] = अणु
	अणु CONN_STATE_INVALID,   CONN_EVENT_START,    conn_action_inval      पूर्ण,
	अणु CONN_STATE_STOPPED,   CONN_EVENT_START,    conn_action_start      पूर्ण,

	अणु CONN_STATE_STOPPED,   CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_STARTWAIT, CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_SETUPWAIT, CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_IDLE,      CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_TX,        CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_REGERR,    CONN_EVENT_STOP,     conn_action_stop       पूर्ण,
	अणु CONN_STATE_CONNERR,   CONN_EVENT_STOP,     conn_action_stop       पूर्ण,

	अणु CONN_STATE_STOPPED,   CONN_EVENT_CONN_REQ, conn_action_connreject पूर्ण,
        अणु CONN_STATE_STARTWAIT, CONN_EVENT_CONN_REQ, conn_action_connaccept पूर्ण,
	अणु CONN_STATE_SETUPWAIT, CONN_EVENT_CONN_REQ, conn_action_connaccept पूर्ण,
	अणु CONN_STATE_IDLE,      CONN_EVENT_CONN_REQ, conn_action_connreject पूर्ण,
	अणु CONN_STATE_TX,        CONN_EVENT_CONN_REQ, conn_action_connreject पूर्ण,

	अणु CONN_STATE_SETUPWAIT, CONN_EVENT_CONN_ACK, conn_action_connack    पूर्ण,
	अणु CONN_STATE_SETUPWAIT, CONN_EVENT_TIMER,    conn_action_conntimsev पूर्ण,

	अणु CONN_STATE_SETUPWAIT, CONN_EVENT_CONN_REJ, conn_action_connsever  पूर्ण,
	अणु CONN_STATE_IDLE,      CONN_EVENT_CONN_REJ, conn_action_connsever  पूर्ण,
	अणु CONN_STATE_TX,        CONN_EVENT_CONN_REJ, conn_action_connsever  पूर्ण,

	अणु CONN_STATE_IDLE,      CONN_EVENT_RX,       conn_action_rx         पूर्ण,
	अणु CONN_STATE_TX,        CONN_EVENT_RX,       conn_action_rx         पूर्ण,

	अणु CONN_STATE_TX,        CONN_EVENT_TXDONE,   conn_action_txकरोne     पूर्ण,
	अणु CONN_STATE_IDLE,      CONN_EVENT_TXDONE,   conn_action_txकरोne     पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक CONN_FSM_LEN = माप(conn_fsm) / माप(fsm_node);


/*
 * Actions क्रम पूर्णांकerface - statemachine.
 */

/**
 * dev_action_start
 * @fi: An instance of an पूर्णांकerface statemachine.
 * @event: The event, just happened.
 * @arg: Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 *
 * Startup connection by sending CONN_EVENT_START to it.
 */
अटल व्योम dev_action_start(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device   *dev = arg;
	काष्ठा netiucv_priv *privptr = netdev_priv(dev);

	IUCV_DBF_TEXT(trace, 3, __func__);

	fsm_newstate(fi, DEV_STATE_STARTWAIT);
	fsm_event(privptr->conn->fsm, CONN_EVENT_START, privptr->conn);
पूर्ण

/**
 * Shutकरोwn connection by sending CONN_EVENT_STOP to it.
 *
 * @param fi    An instance of an पूर्णांकerface statemachine.
 * @param event The event, just happened.
 * @param arg   Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम
dev_action_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device   *dev = arg;
	काष्ठा netiucv_priv *privptr = netdev_priv(dev);
	काष्ठा iucv_event   ev;

	IUCV_DBF_TEXT(trace, 3, __func__);

	ev.conn = privptr->conn;

	fsm_newstate(fi, DEV_STATE_STOPWAIT);
	fsm_event(privptr->conn->fsm, CONN_EVENT_STOP, &ev);
पूर्ण

/**
 * Called from connection statemachine
 * when a connection is up and running.
 *
 * @param fi    An instance of an पूर्णांकerface statemachine.
 * @param event The event, just happened.
 * @param arg   Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम
dev_action_connup(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device   *dev = arg;
	काष्ठा netiucv_priv *privptr = netdev_priv(dev);

	IUCV_DBF_TEXT(trace, 3, __func__);

	चयन (fsm_माला_लोtate(fi)) अणु
		हाल DEV_STATE_STARTWAIT:
			fsm_newstate(fi, DEV_STATE_RUNNING);
			dev_info(privptr->dev,
				"The IUCV device has been connected"
				" successfully to %s\n",
				netiucv_prपूर्णांकuser(privptr->conn));
			IUCV_DBF_TEXT(setup, 3,
				"connection is up and running\n");
			अवरोध;
		हाल DEV_STATE_STOPWAIT:
			IUCV_DBF_TEXT(data, 2,
				"dev_action_connup: in DEV_STATE_STOPWAIT\n");
			अवरोध;
	पूर्ण
पूर्ण

/**
 * Called from connection statemachine
 * when a connection has been shutकरोwn.
 *
 * @param fi    An instance of an पूर्णांकerface statemachine.
 * @param event The event, just happened.
 * @param arg   Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम
dev_action_connकरोwn(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	IUCV_DBF_TEXT(trace, 3, __func__);

	चयन (fsm_माला_लोtate(fi)) अणु
		हाल DEV_STATE_RUNNING:
			fsm_newstate(fi, DEV_STATE_STARTWAIT);
			अवरोध;
		हाल DEV_STATE_STOPWAIT:
			fsm_newstate(fi, DEV_STATE_STOPPED);
			IUCV_DBF_TEXT(setup, 3, "connection is down\n");
			अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर fsm_node dev_fsm[] = अणु
	अणु DEV_STATE_STOPPED,    DEV_EVENT_START,   dev_action_start    पूर्ण,

	अणु DEV_STATE_STOPWAIT,   DEV_EVENT_START,   dev_action_start    पूर्ण,
	अणु DEV_STATE_STOPWAIT,   DEV_EVENT_CONDOWN, dev_action_connकरोwn पूर्ण,

	अणु DEV_STATE_STARTWAIT,  DEV_EVENT_STOP,    dev_action_stop     पूर्ण,
	अणु DEV_STATE_STARTWAIT,  DEV_EVENT_CONUP,   dev_action_connup   पूर्ण,

	अणु DEV_STATE_RUNNING,    DEV_EVENT_STOP,    dev_action_stop     पूर्ण,
	अणु DEV_STATE_RUNNING,    DEV_EVENT_CONDOWN, dev_action_connकरोwn पूर्ण,
	अणु DEV_STATE_RUNNING,    DEV_EVENT_CONUP,   netiucv_action_nop  पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक DEV_FSM_LEN = माप(dev_fsm) / माप(fsm_node);

/**
 * Transmit a packet.
 * This is a helper function क्रम netiucv_tx().
 *
 * @param conn Connection to be used क्रम sending.
 * @param skb Poपूर्णांकer to काष्ठा sk_buff of packet to send.
 *            The linklevel header has alपढ़ोy been set up
 *            by netiucv_tx().
 *
 * @वापस 0 on success, -ERRNO on failure. (Never fails.)
 */
अटल पूर्णांक netiucv_transmit_skb(काष्ठा iucv_connection *conn,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_message msg;
	अचिन्हित दीर्घ saveflags;
	काष्ठा ll_header header;
	पूर्णांक rc;

	अगर (fsm_माला_लोtate(conn->fsm) != CONN_STATE_IDLE) अणु
		पूर्णांक l = skb->len + NETIUCV_HDRLEN;

		spin_lock_irqsave(&conn->collect_lock, saveflags);
		अगर (conn->collect_len + l >
		    (conn->max_buffsize - NETIUCV_HDRLEN)) अणु
			rc = -EBUSY;
			IUCV_DBF_TEXT(data, 2,
				      "EBUSY from netiucv_transmit_skb\n");
		पूर्ण अन्यथा अणु
			refcount_inc(&skb->users);
			skb_queue_tail(&conn->collect_queue, skb);
			conn->collect_len += l;
			rc = 0;
		पूर्ण
		spin_unlock_irqrestore(&conn->collect_lock, saveflags);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *nskb = skb;
		/**
		 * Copy the skb to a new allocated skb in lowmem only अगर the
		 * data is located above 2G in memory or tailroom is < 2.
		 */
		अचिन्हित दीर्घ hi = ((अचिन्हित दीर्घ)(skb_tail_poपूर्णांकer(skb) +
				    NETIUCV_HDRLEN)) >> 31;
		पूर्णांक copied = 0;
		अगर (hi || (skb_tailroom(skb) < 2)) अणु
			nskb = alloc_skb(skb->len + NETIUCV_HDRLEN +
					 NETIUCV_HDRLEN, GFP_ATOMIC | GFP_DMA);
			अगर (!nskb) अणु
				IUCV_DBF_TEXT(data, 2, "alloc_skb failed\n");
				rc = -ENOMEM;
				वापस rc;
			पूर्ण अन्यथा अणु
				skb_reserve(nskb, NETIUCV_HDRLEN);
				skb_put_data(nskb, skb->data, skb->len);
			पूर्ण
			copied = 1;
		पूर्ण
		/**
		 * skb now is below 2G and has enough room. Add headers.
		 */
		header.next = nskb->len + NETIUCV_HDRLEN;
		स_नकल(skb_push(nskb, NETIUCV_HDRLEN), &header, NETIUCV_HDRLEN);
		header.next = 0;
		skb_put_data(nskb, &header, NETIUCV_HDRLEN);

		fsm_newstate(conn->fsm, CONN_STATE_TX);
		conn->prof.send_stamp = jअगरfies;

		msg.tag = 1;
		msg.class = 0;
		rc = iucv_message_send(conn->path, &msg, 0, 0,
				       nskb->data, nskb->len);
		conn->prof.करोios_single++;
		conn->prof.txlen += skb->len;
		conn->prof.tx_pending++;
		अगर (conn->prof.tx_pending > conn->prof.tx_max_pending)
			conn->prof.tx_max_pending = conn->prof.tx_pending;
		अगर (rc) अणु
			काष्ठा netiucv_priv *privptr;
			fsm_newstate(conn->fsm, CONN_STATE_IDLE);
			conn->prof.tx_pending--;
			privptr = netdev_priv(conn->netdev);
			अगर (privptr)
				privptr->stats.tx_errors++;
			अगर (copied)
				dev_kमुक्त_skb(nskb);
			अन्यथा अणु
				/**
				 * Remove our headers. They get added
				 * again on retransmit.
				 */
				skb_pull(skb, NETIUCV_HDRLEN);
				skb_trim(skb, skb->len - NETIUCV_HDRLEN);
			पूर्ण
			IUCV_DBF_TEXT_(data, 2, "rc %d from iucv_send\n", rc);
		पूर्ण अन्यथा अणु
			अगर (copied)
				dev_kमुक्त_skb(skb);
			refcount_inc(&nskb->users);
			skb_queue_tail(&conn->commit_queue, nskb);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Interface API क्रम upper network layers
 */

/**
 * Open an पूर्णांकerface.
 * Called from generic network layer when अगरconfig up is run.
 *
 * @param dev Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * @वापस 0 on success, -ERRNO on failure. (Never fails.)
 */
अटल पूर्णांक netiucv_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(dev);

	fsm_event(priv->fsm, DEV_EVENT_START, dev);
	वापस 0;
पूर्ण

/**
 * Close an पूर्णांकerface.
 * Called from generic network layer when अगरconfig करोwn is run.
 *
 * @param dev Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * @वापस 0 on success, -ERRNO on failure. (Never fails.)
 */
अटल पूर्णांक netiucv_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(dev);

	fsm_event(priv->fsm, DEV_EVENT_STOP, dev);
	वापस 0;
पूर्ण

/**
 * Start transmission of a packet.
 * Called from generic network device layer.
 *
 * @param skb Poपूर्णांकer to buffer containing the packet.
 * @param dev Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * @वापस 0 अगर packet consumed, !0 अगर packet rejected.
 *         Note: If we वापस !0, then the packet is मुक्त'd by
 *               the generic network layer.
 */
अटल पूर्णांक netiucv_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *privptr = netdev_priv(dev);
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 4, __func__);
	/**
	 * Some sanity checks ...
	 */
	अगर (skb == शून्य) अणु
		IUCV_DBF_TEXT(data, 2, "netiucv_tx: skb is NULL\n");
		privptr->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb_headroom(skb) < NETIUCV_HDRLEN) अणु
		IUCV_DBF_TEXT(data, 2,
			"netiucv_tx: skb_headroom < NETIUCV_HDRLEN\n");
		dev_kमुक्त_skb(skb);
		privptr->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/**
	 * If connection is not running, try to restart it
	 * and throw away packet.
	 */
	अगर (fsm_माला_लोtate(privptr->fsm) != DEV_STATE_RUNNING) अणु
		dev_kमुक्त_skb(skb);
		privptr->stats.tx_dropped++;
		privptr->stats.tx_errors++;
		privptr->stats.tx_carrier_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (netiucv_test_and_set_busy(dev)) अणु
		IUCV_DBF_TEXT(data, 2, "EBUSY from netiucv_tx\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण
	netअगर_trans_update(dev);
	rc = netiucv_transmit_skb(privptr->conn, skb);
	netiucv_clear_busy(dev);
	वापस rc ? NETDEV_TX_BUSY : NETDEV_TX_OK;
पूर्ण

/**
 * netiucv_stats
 * @dev: Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * Returns पूर्णांकerface statistics of a device.
 *
 * Returns poपूर्णांकer to stats काष्ठा of this पूर्णांकerface.
 */
अटल काष्ठा net_device_stats *netiucv_stats (काष्ठा net_device * dev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस &priv->stats;
पूर्ण

/*
 * attributes in sysfs
 */

अटल sमाप_प्रकार user_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%s\n", netiucv_prपूर्णांकuser(priv->conn));
पूर्ण

अटल पूर्णांक netiucv_check_user(स्थिर अक्षर *buf, माप_प्रकार count, अक्षर *username,
			      अक्षर *userdata)
अणु
	स्थिर अक्षर *p;
	पूर्णांक i;

	p = म_अक्षर(buf, '.');
	अगर ((p && ((count > 26) ||
		   ((p - buf) > 8) ||
		   (buf + count - p > 18))) ||
	    (!p && (count > 9))) अणु
		IUCV_DBF_TEXT(setup, 2, "conn_write: too long\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0, p = buf; i < 8 && *p && *p != '.'; i++, p++) अणु
		अगर (है_अक्षर_अंक(*p) || *p == '$') अणु
			username[i] = बड़े(*p);
			जारी;
		पूर्ण
		अगर (*p == '\n')
			/* trailing lf, grr */
			अवरोध;
		IUCV_DBF_TEXT_(setup, 2,
			       "conn_write: invalid character %02x\n", *p);
		वापस -EINVAL;
	पूर्ण
	जबतक (i < 8)
		username[i++] = ' ';
	username[8] = '\0';

	अगर (*p == '.') अणु
		p++;
		क्रम (i = 0; i < 16 && *p; i++, p++) अणु
			अगर (*p == '\n')
				अवरोध;
			userdata[i] = बड़े(*p);
		पूर्ण
		जबतक (i > 0 && i < 16)
			userdata[i++] = ' ';
	पूर्ण अन्यथा
		स_नकल(userdata, iucvMagic_ascii, 16);
	userdata[16] = '\0';
	ASCEBC(userdata, 16);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार user_ग_लिखो(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = priv->conn->netdev;
	अक्षर	username[9];
	अक्षर	userdata[17];
	पूर्णांक	rc;
	काष्ठा iucv_connection *cp;

	IUCV_DBF_TEXT(trace, 3, __func__);
	rc = netiucv_check_user(buf, count, username, userdata);
	अगर (rc)
		वापस rc;

	अगर (स_भेद(username, priv->conn->userid, 9) &&
	    (ndev->flags & (IFF_UP | IFF_RUNNING))) अणु
		/* username changed जबतक the पूर्णांकerface is active. */
		IUCV_DBF_TEXT(setup, 2, "user_write: device active\n");
		वापस -EPERM;
	पूर्ण
	पढ़ो_lock_bh(&iucv_connection_rwlock);
	list_क्रम_each_entry(cp, &iucv_connection_list, list) अणु
		अगर (!म_भेदन(username, cp->userid, 9) &&
		   !म_भेदन(userdata, cp->userdata, 17) && cp->netdev != ndev) अणु
			पढ़ो_unlock_bh(&iucv_connection_rwlock);
			IUCV_DBF_TEXT_(setup, 2, "user_write: Connection to %s "
				"already exists\n", netiucv_prपूर्णांकuser(cp));
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&iucv_connection_rwlock);
	स_नकल(priv->conn->userid, username, 9);
	स_नकल(priv->conn->userdata, userdata, 17);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(user, 0644, user_show, user_ग_लिखो);

अटल sमाप_प्रकार buffer_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%d\n", priv->conn->max_buffsize);
पूर्ण

अटल sमाप_प्रकार buffer_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = priv->conn->netdev;
	अचिन्हित पूर्णांक bs1;
	पूर्णांक rc;

	IUCV_DBF_TEXT(trace, 3, __func__);
	अगर (count >= 39)
		वापस -EINVAL;

	rc = kstrtouपूर्णांक(buf, 0, &bs1);

	अगर (rc == -EINVAL) अणु
		IUCV_DBF_TEXT_(setup, 2, "buffer_write: invalid char %s\n",
			buf);
		वापस -EINVAL;
	पूर्ण
	अगर ((rc == -दुस्फल) || (bs1 > NETIUCV_बफ_मानE_MAX)) अणु
		IUCV_DBF_TEXT_(setup, 2,
			"buffer_write: buffer size %d too large\n",
			bs1);
		वापस -EINVAL;
	पूर्ण
	अगर ((ndev->flags & IFF_RUNNING) &&
	    (bs1 < (ndev->mtu + NETIUCV_HDRLEN + 2))) अणु
		IUCV_DBF_TEXT_(setup, 2,
			"buffer_write: buffer size %d too small\n",
			bs1);
		वापस -EINVAL;
	पूर्ण
	अगर (bs1 < (576 + NETIUCV_HDRLEN + NETIUCV_HDRLEN)) अणु
		IUCV_DBF_TEXT_(setup, 2,
			"buffer_write: buffer size %d too small\n",
			bs1);
		वापस -EINVAL;
	पूर्ण

	priv->conn->max_buffsize = bs1;
	अगर (!(ndev->flags & IFF_RUNNING))
		ndev->mtu = bs1 - NETIUCV_HDRLEN - NETIUCV_HDRLEN;

	वापस count;

पूर्ण

अटल DEVICE_ATTR(buffer, 0644, buffer_show, buffer_ग_लिखो);

अटल sमाप_प्रकार dev_fsm_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%s\n", fsm_माला_लोtate_str(priv->fsm));
पूर्ण

अटल DEVICE_ATTR(device_fsm_state, 0444, dev_fsm_show, शून्य);

अटल sमाप_प्रकार conn_fsm_show (काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%s\n", fsm_माला_लोtate_str(priv->conn->fsm));
पूर्ण

अटल DEVICE_ATTR(connection_fsm_state, 0444, conn_fsm_show, शून्य);

अटल sमाप_प्रकार maxmulti_show (काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.maxmulti);
पूर्ण

अटल sमाप_प्रकार maxmulti_ग_लिखो (काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.maxmulti = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(max_tx_buffer_used, 0644, maxmulti_show, maxmulti_ग_लिखो);

अटल sमाप_प्रकार maxcq_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.maxcqueue);
पूर्ण

अटल sमाप_प्रकार maxcq_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.maxcqueue = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(max_chained_skbs, 0644, maxcq_show, maxcq_ग_लिखो);

अटल sमाप_प्रकार sकरोio_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.करोios_single);
पूर्ण

अटल sमाप_प्रकार sकरोio_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.करोios_single = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(tx_single_ग_लिखो_ops, 0644, sकरोio_show, sकरोio_ग_लिखो);

अटल sमाप_प्रकार mकरोio_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.करोios_multi);
पूर्ण

अटल sमाप_प्रकार mकरोio_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	priv->conn->prof.करोios_multi = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(tx_multi_ग_लिखो_ops, 0644, mकरोio_show, mकरोio_ग_लिखो);

अटल sमाप_प्रकार txlen_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.txlen);
पूर्ण

अटल sमाप_प्रकार txlen_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.txlen = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(netto_bytes, 0644, txlen_show, txlen_ग_लिखो);

अटल sमाप_प्रकार txसमय_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.tx_समय);
पूर्ण

अटल sमाप_प्रकार txसमय_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.tx_समय = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(max_tx_io_समय, 0644, txसमय_show, txसमय_ग_लिखो);

अटल sमाप_प्रकार txpend_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.tx_pending);
पूर्ण

अटल sमाप_प्रकार txpend_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.tx_pending = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(tx_pending, 0644, txpend_show, txpend_ग_लिखो);

अटल sमाप_प्रकार txmpnd_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 5, __func__);
	वापस प्र_लिखो(buf, "%ld\n", priv->conn->prof.tx_max_pending);
पूर्ण

अटल sमाप_प्रकार txmpnd_ग_लिखो (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा netiucv_priv *priv = dev_get_drvdata(dev);

	IUCV_DBF_TEXT(trace, 4, __func__);
	priv->conn->prof.tx_max_pending = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(tx_max_pending, 0644, txmpnd_show, txmpnd_ग_लिखो);

अटल काष्ठा attribute *netiucv_attrs[] = अणु
	&dev_attr_buffer.attr,
	&dev_attr_user.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group netiucv_attr_group = अणु
	.attrs = netiucv_attrs,
पूर्ण;

अटल काष्ठा attribute *netiucv_stat_attrs[] = अणु
	&dev_attr_device_fsm_state.attr,
	&dev_attr_connection_fsm_state.attr,
	&dev_attr_max_tx_buffer_used.attr,
	&dev_attr_max_chained_skbs.attr,
	&dev_attr_tx_single_ग_लिखो_ops.attr,
	&dev_attr_tx_multi_ग_लिखो_ops.attr,
	&dev_attr_netto_bytes.attr,
	&dev_attr_max_tx_io_समय.attr,
	&dev_attr_tx_pending.attr,
	&dev_attr_tx_max_pending.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group netiucv_stat_attr_group = अणु
	.name  = "stats",
	.attrs = netiucv_stat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *netiucv_attr_groups[] = अणु
	&netiucv_stat_attr_group,
	&netiucv_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक netiucv_रेजिस्टर_device(काष्ठा net_device *ndev)
अणु
	काष्ठा netiucv_priv *priv = netdev_priv(ndev);
	काष्ठा device *dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	पूर्णांक ret;

	IUCV_DBF_TEXT(trace, 3, __func__);

	अगर (dev) अणु
		dev_set_name(dev, "net%s", ndev->name);
		dev->bus = &iucv_bus;
		dev->parent = iucv_root;
		dev->groups = netiucv_attr_groups;
		/*
		 * The release function could be called after the
		 * module has been unloaded. It's _only_ task is to
		 * मुक्त the काष्ठा. Thereक्रमe, we specअगरy kमुक्त()
		 * directly here. (Probably a little bit obfuscating
		 * but legiसमय ...).
		 */
		dev->release = (व्योम (*)(काष्ठा device *))kमुक्त;
		dev->driver = &netiucv_driver;
	पूर्ण अन्यथा
		वापस -ENOMEM;

	ret = device_रेजिस्टर(dev);
	अगर (ret) अणु
		put_device(dev);
		वापस ret;
	पूर्ण
	priv->dev = dev;
	dev_set_drvdata(dev, priv);
	वापस 0;
पूर्ण

अटल व्योम netiucv_unरेजिस्टर_device(काष्ठा device *dev)
अणु
	IUCV_DBF_TEXT(trace, 3, __func__);
	device_unरेजिस्टर(dev);
पूर्ण

/**
 * Allocate and initialize a new connection काष्ठाure.
 * Add it to the list of netiucv connections;
 */
अटल काष्ठा iucv_connection *netiucv_new_connection(काष्ठा net_device *dev,
						      अक्षर *username,
						      अक्षर *userdata)
अणु
	काष्ठा iucv_connection *conn;

	conn = kzalloc(माप(*conn), GFP_KERNEL);
	अगर (!conn)
		जाओ out;
	skb_queue_head_init(&conn->collect_queue);
	skb_queue_head_init(&conn->commit_queue);
	spin_lock_init(&conn->collect_lock);
	conn->max_buffsize = NETIUCV_बफ_मानE_DEFAULT;
	conn->netdev = dev;

	conn->rx_buff = alloc_skb(conn->max_buffsize, GFP_KERNEL | GFP_DMA);
	अगर (!conn->rx_buff)
		जाओ out_conn;
	conn->tx_buff = alloc_skb(conn->max_buffsize, GFP_KERNEL | GFP_DMA);
	अगर (!conn->tx_buff)
		जाओ out_rx;
	conn->fsm = init_fsm("netiucvconn", conn_state_names,
			     conn_event_names, NR_CONN_STATES,
			     NR_CONN_EVENTS, conn_fsm, CONN_FSM_LEN,
			     GFP_KERNEL);
	अगर (!conn->fsm)
		जाओ out_tx;

	fsm_समय_रखोr(conn->fsm, &conn->समयr);
	fsm_newstate(conn->fsm, CONN_STATE_INVALID);

	अगर (userdata)
		स_नकल(conn->userdata, userdata, 17);
	अगर (username) अणु
		स_नकल(conn->userid, username, 9);
		fsm_newstate(conn->fsm, CONN_STATE_STOPPED);
	पूर्ण

	ग_लिखो_lock_bh(&iucv_connection_rwlock);
	list_add_tail(&conn->list, &iucv_connection_list);
	ग_लिखो_unlock_bh(&iucv_connection_rwlock);
	वापस conn;

out_tx:
	kमुक्त_skb(conn->tx_buff);
out_rx:
	kमुक्त_skb(conn->rx_buff);
out_conn:
	kमुक्त(conn);
out:
	वापस शून्य;
पूर्ण

/**
 * Release a connection काष्ठाure and हटाओ it from the
 * list of netiucv connections.
 */
अटल व्योम netiucv_हटाओ_connection(काष्ठा iucv_connection *conn)
अणु

	IUCV_DBF_TEXT(trace, 3, __func__);
	ग_लिखो_lock_bh(&iucv_connection_rwlock);
	list_del_init(&conn->list);
	ग_लिखो_unlock_bh(&iucv_connection_rwlock);
	fsm_delसमयr(&conn->समयr);
	netiucv_purge_skb_queue(&conn->collect_queue);
	अगर (conn->path) अणु
		iucv_path_sever(conn->path, conn->userdata);
		kमुक्त(conn->path);
		conn->path = शून्य;
	पूर्ण
	netiucv_purge_skb_queue(&conn->commit_queue);
	kमुक्त_fsm(conn->fsm);
	kमुक्त_skb(conn->rx_buff);
	kमुक्त_skb(conn->tx_buff);
पूर्ण

/**
 * Release everything of a net device.
 */
अटल व्योम netiucv_मुक्त_netdevice(काष्ठा net_device *dev)
अणु
	काष्ठा netiucv_priv *privptr = netdev_priv(dev);

	IUCV_DBF_TEXT(trace, 3, __func__);

	अगर (!dev)
		वापस;

	अगर (privptr) अणु
		अगर (privptr->conn)
			netiucv_हटाओ_connection(privptr->conn);
		अगर (privptr->fsm)
			kमुक्त_fsm(privptr->fsm);
		privptr->conn = शून्य; privptr->fsm = शून्य;
		/* privptr माला_लो मुक्तd by मुक्त_netdev() */
	पूर्ण
पूर्ण

/**
 * Initialize a net device. (Called from kernel in alloc_netdev())
 */
अटल स्थिर काष्ठा net_device_ops netiucv_netdev_ops = अणु
	.nकरो_खोलो		= netiucv_खोलो,
	.nकरो_stop		= netiucv_बंद,
	.nकरो_get_stats		= netiucv_stats,
	.nकरो_start_xmit		= netiucv_tx,
पूर्ण;

अटल व्योम netiucv_setup_netdevice(काष्ठा net_device *dev)
अणु
	dev->mtu	         = NETIUCV_MTU_DEFAULT;
	dev->min_mtu		 = 576;
	dev->max_mtu		 = NETIUCV_MTU_MAX;
	dev->needs_मुक्त_netdev   = true;
	dev->priv_deकाष्ठाor     = netiucv_मुक्त_netdevice;
	dev->hard_header_len     = NETIUCV_HDRLEN;
	dev->addr_len            = 0;
	dev->type                = ARPHRD_SLIP;
	dev->tx_queue_len        = NETIUCV_QUEUELEN_DEFAULT;
	dev->flags	         = IFF_POINTOPOINT | IFF_NOARP;
	dev->netdev_ops		 = &netiucv_netdev_ops;
पूर्ण

/**
 * Allocate and initialize everything of a net device.
 */
अटल काष्ठा net_device *netiucv_init_netdevice(अक्षर *username, अक्षर *userdata)
अणु
	काष्ठा netiucv_priv *privptr;
	काष्ठा net_device *dev;

	dev = alloc_netdev(माप(काष्ठा netiucv_priv), "iucv%d",
			   NET_NAME_UNKNOWN, netiucv_setup_netdevice);
	अगर (!dev)
		वापस शून्य;
	rtnl_lock();
	अगर (dev_alloc_name(dev, dev->name) < 0)
		जाओ out_netdev;

	privptr = netdev_priv(dev);
	privptr->fsm = init_fsm("netiucvdev", dev_state_names,
				dev_event_names, NR_DEV_STATES, NR_DEV_EVENTS,
				dev_fsm, DEV_FSM_LEN, GFP_KERNEL);
	अगर (!privptr->fsm)
		जाओ out_netdev;

	privptr->conn = netiucv_new_connection(dev, username, userdata);
	अगर (!privptr->conn) अणु
		IUCV_DBF_TEXT(setup, 2, "NULL from netiucv_new_connection\n");
		जाओ out_fsm;
	पूर्ण
	fsm_newstate(privptr->fsm, DEV_STATE_STOPPED);
	वापस dev;

out_fsm:
	kमुक्त_fsm(privptr->fsm);
out_netdev:
	rtnl_unlock();
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार connection_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	अक्षर username[9];
	अक्षर userdata[17];
	पूर्णांक rc;
	काष्ठा net_device *dev;
	काष्ठा netiucv_priv *priv;
	काष्ठा iucv_connection *cp;

	IUCV_DBF_TEXT(trace, 3, __func__);
	rc = netiucv_check_user(buf, count, username, userdata);
	अगर (rc)
		वापस rc;

	पढ़ो_lock_bh(&iucv_connection_rwlock);
	list_क्रम_each_entry(cp, &iucv_connection_list, list) अणु
		अगर (!म_भेदन(username, cp->userid, 9) &&
		    !म_भेदन(userdata, cp->userdata, 17)) अणु
			पढ़ो_unlock_bh(&iucv_connection_rwlock);
			IUCV_DBF_TEXT_(setup, 2, "conn_write: Connection to %s "
				"already exists\n", netiucv_prपूर्णांकuser(cp));
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&iucv_connection_rwlock);

	dev = netiucv_init_netdevice(username, userdata);
	अगर (!dev) अणु
		IUCV_DBF_TEXT(setup, 2, "NULL from netiucv_init_netdevice\n");
		वापस -ENODEV;
	पूर्ण

	rc = netiucv_रेजिस्टर_device(dev);
	अगर (rc) अणु
		rtnl_unlock();
		IUCV_DBF_TEXT_(setup, 2,
			"ret %d from netiucv_register_device\n", rc);
		जाओ out_मुक्त_ndev;
	पूर्ण

	/* sysfs magic */
	priv = netdev_priv(dev);
	SET_NETDEV_DEV(dev, priv->dev);

	rc = रेजिस्टर_netdevice(dev);
	rtnl_unlock();
	अगर (rc)
		जाओ out_unreg;

	dev_info(priv->dev, "The IUCV interface to %s has been established "
			    "successfully\n",
		netiucv_prपूर्णांकuser(priv->conn));

	वापस count;

out_unreg:
	netiucv_unरेजिस्टर_device(priv->dev);
out_मुक्त_ndev:
	netiucv_मुक्त_netdevice(dev);
	वापस rc;
पूर्ण
अटल DRIVER_ATTR_WO(connection);

अटल sमाप_प्रकार हटाओ_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा iucv_connection *cp;
        काष्ठा net_device *ndev;
        काष्ठा netiucv_priv *priv;
        काष्ठा device *dev;
        अक्षर name[IFNAMSIZ];
	स्थिर अक्षर *p;
        पूर्णांक i;

	IUCV_DBF_TEXT(trace, 3, __func__);

        अगर (count >= IFNAMSIZ)
                count = IFNAMSIZ - 1;

	क्रम (i = 0, p = buf; i < count && *p; i++, p++) अणु
		अगर (*p == '\n' || *p == ' ')
                        /* trailing lf, grr */
                        अवरोध;
		name[i] = *p;
        पूर्ण
        name[i] = '\0';

	पढ़ो_lock_bh(&iucv_connection_rwlock);
	list_क्रम_each_entry(cp, &iucv_connection_list, list) अणु
		ndev = cp->netdev;
		priv = netdev_priv(ndev);
                dev = priv->dev;
		अगर (म_भेदन(name, ndev->name, count))
			जारी;
		पढ़ो_unlock_bh(&iucv_connection_rwlock);
                अगर (ndev->flags & (IFF_UP | IFF_RUNNING)) अणु
			dev_warn(dev, "The IUCV device is connected"
				" to %s and cannot be removed\n",
				priv->conn->userid);
			IUCV_DBF_TEXT(data, 2, "remove_write: still active\n");
			वापस -EPERM;
                पूर्ण
                unरेजिस्टर_netdev(ndev);
                netiucv_unरेजिस्टर_device(dev);
                वापस count;
        पूर्ण
	पढ़ो_unlock_bh(&iucv_connection_rwlock);
	IUCV_DBF_TEXT(data, 2, "remove_write: unknown device\n");
        वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_WO(हटाओ);

अटल काष्ठा attribute * netiucv_drv_attrs[] = अणु
	&driver_attr_connection.attr,
	&driver_attr_हटाओ.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group netiucv_drv_attr_group = अणु
	.attrs = netiucv_drv_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *netiucv_drv_attr_groups[] = अणु
	&netiucv_drv_attr_group,
	शून्य,
पूर्ण;

अटल व्योम netiucv_banner(व्योम)
अणु
	pr_info("driver initialized\n");
पूर्ण

अटल व्योम __निकास netiucv_निकास(व्योम)
अणु
	काष्ठा iucv_connection *cp;
	काष्ठा net_device *ndev;
	काष्ठा netiucv_priv *priv;
	काष्ठा device *dev;

	IUCV_DBF_TEXT(trace, 3, __func__);
	जबतक (!list_empty(&iucv_connection_list)) अणु
		cp = list_entry(iucv_connection_list.next,
				काष्ठा iucv_connection, list);
		ndev = cp->netdev;
		priv = netdev_priv(ndev);
		dev = priv->dev;

		unरेजिस्टर_netdev(ndev);
		netiucv_unरेजिस्टर_device(dev);
	पूर्ण

	driver_unरेजिस्टर(&netiucv_driver);
	iucv_unरेजिस्टर(&netiucv_handler, 1);
	iucv_unरेजिस्टर_dbf_views();

	pr_info("driver unloaded\n");
	वापस;
पूर्ण

अटल पूर्णांक __init netiucv_init(व्योम)
अणु
	पूर्णांक rc;

	rc = iucv_रेजिस्टर_dbf_views();
	अगर (rc)
		जाओ out;
	rc = iucv_रेजिस्टर(&netiucv_handler, 1);
	अगर (rc)
		जाओ out_dbf;
	IUCV_DBF_TEXT(trace, 3, __func__);
	netiucv_driver.groups = netiucv_drv_attr_groups;
	rc = driver_रेजिस्टर(&netiucv_driver);
	अगर (rc) अणु
		IUCV_DBF_TEXT_(setup, 2, "ret %d from driver_register\n", rc);
		जाओ out_iucv;
	पूर्ण

	netiucv_banner();
	वापस rc;

out_iucv:
	iucv_unरेजिस्टर(&netiucv_handler, 1);
out_dbf:
	iucv_unरेजिस्टर_dbf_views();
out:
	वापस rc;
पूर्ण

module_init(netiucv_init);
module_निकास(netiucv_निकास);
MODULE_LICENSE("GPL");
