<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *      IP Virtual Server
 *      data काष्ठाure and functionality definitions
 */

#अगर_अघोषित _IP_VS_H
#घोषणा _IP_VS_H

#समावेश <linux/types.h>	/* For __beXX types in userland */

#घोषणा IP_VS_VERSION_CODE	0x010201
#घोषणा NVERSION(version)			\
	(version >> 16) & 0xFF,			\
	(version >> 8) & 0xFF,			\
	version & 0xFF

/*
 *      Virtual Service Flags
 */
#घोषणा IP_VS_SVC_F_PERSISTENT	0x0001		/* persistent port */
#घोषणा IP_VS_SVC_F_HASHED	0x0002		/* hashed entry */
#घोषणा IP_VS_SVC_F_ONEPACKET	0x0004		/* one-packet scheduling */
#घोषणा IP_VS_SVC_F_SCHED1	0x0008		/* scheduler flag 1 */
#घोषणा IP_VS_SVC_F_SCHED2	0x0010		/* scheduler flag 2 */
#घोषणा IP_VS_SVC_F_SCHED3	0x0020		/* scheduler flag 3 */

#घोषणा IP_VS_SVC_F_SCHED_SH_FALLBACK	IP_VS_SVC_F_SCHED1 /* SH fallback */
#घोषणा IP_VS_SVC_F_SCHED_SH_PORT	IP_VS_SVC_F_SCHED2 /* SH use port */

/*
 *      Destination Server Flags
 */
#घोषणा IP_VS_DEST_F_AVAILABLE	0x0001		/* server is available */
#घोषणा IP_VS_DEST_F_OVERLOAD	0x0002		/* server is overloaded */

/*
 *      IPVS sync daemon states
 */
#घोषणा IP_VS_STATE_NONE	0x0000		/* daemon is stopped */
#घोषणा IP_VS_STATE_MASTER	0x0001		/* started as master */
#घोषणा IP_VS_STATE_BACKUP	0x0002		/* started as backup */

/*
 *      IPVS socket options
 */
#घोषणा IP_VS_BASE_CTL		(64+1024+64)		/* base */

#घोषणा IP_VS_SO_SET_NONE	IP_VS_BASE_CTL		/* just peek */
#घोषणा IP_VS_SO_SET_INSERT	(IP_VS_BASE_CTL+1)
#घोषणा IP_VS_SO_SET_ADD	(IP_VS_BASE_CTL+2)
#घोषणा IP_VS_SO_SET_EDIT	(IP_VS_BASE_CTL+3)
#घोषणा IP_VS_SO_SET_DEL	(IP_VS_BASE_CTL+4)
#घोषणा IP_VS_SO_SET_FLUSH	(IP_VS_BASE_CTL+5)
#घोषणा IP_VS_SO_SET_LIST	(IP_VS_BASE_CTL+6)
#घोषणा IP_VS_SO_SET_ADDDEST	(IP_VS_BASE_CTL+7)
#घोषणा IP_VS_SO_SET_DELDEST	(IP_VS_BASE_CTL+8)
#घोषणा IP_VS_SO_SET_EDITDEST	(IP_VS_BASE_CTL+9)
#घोषणा IP_VS_SO_SET_TIMEOUT	(IP_VS_BASE_CTL+10)
#घोषणा IP_VS_SO_SET_STARTDAEMON (IP_VS_BASE_CTL+11)
#घोषणा IP_VS_SO_SET_STOPDAEMON (IP_VS_BASE_CTL+12)
#घोषणा IP_VS_SO_SET_RESTORE    (IP_VS_BASE_CTL+13)
#घोषणा IP_VS_SO_SET_SAVE       (IP_VS_BASE_CTL+14)
#घोषणा IP_VS_SO_SET_ZERO	(IP_VS_BASE_CTL+15)
#घोषणा IP_VS_SO_SET_MAX	IP_VS_SO_SET_ZERO

#घोषणा IP_VS_SO_GET_VERSION	IP_VS_BASE_CTL
#घोषणा IP_VS_SO_GET_INFO	(IP_VS_BASE_CTL+1)
#घोषणा IP_VS_SO_GET_SERVICES	(IP_VS_BASE_CTL+2)
#घोषणा IP_VS_SO_GET_SERVICE	(IP_VS_BASE_CTL+3)
#घोषणा IP_VS_SO_GET_DESTS	(IP_VS_BASE_CTL+4)
#घोषणा IP_VS_SO_GET_DEST	(IP_VS_BASE_CTL+5)	/* not used now */
#घोषणा IP_VS_SO_GET_TIMEOUT	(IP_VS_BASE_CTL+6)
#घोषणा IP_VS_SO_GET_DAEMON	(IP_VS_BASE_CTL+7)
#घोषणा IP_VS_SO_GET_MAX	IP_VS_SO_GET_DAEMON


/*
 *      IPVS Connection Flags
 *      Only flags 0..15 are sent to backup server
 */
#घोषणा IP_VS_CONN_F_FWD_MASK	0x0007		/* mask क्रम the fwd methods */
#घोषणा IP_VS_CONN_F_MASQ	0x0000		/* masquerading/NAT */
#घोषणा IP_VS_CONN_F_LOCALNODE	0x0001		/* local node */
#घोषणा IP_VS_CONN_F_TUNNEL	0x0002		/* tunneling */
#घोषणा IP_VS_CONN_F_DROUTE	0x0003		/* direct routing */
#घोषणा IP_VS_CONN_F_BYPASS	0x0004		/* cache bypass */
#घोषणा IP_VS_CONN_F_SYNC	0x0020		/* entry created by sync */
#घोषणा IP_VS_CONN_F_HASHED	0x0040		/* hashed entry */
#घोषणा IP_VS_CONN_F_NOOUTPUT	0x0080		/* no output packets */
#घोषणा IP_VS_CONN_F_INACTIVE	0x0100		/* not established */
#घोषणा IP_VS_CONN_F_OUT_SEQ	0x0200		/* must करो output seq adjust */
#घोषणा IP_VS_CONN_F_IN_SEQ	0x0400		/* must करो input seq adjust */
#घोषणा IP_VS_CONN_F_SEQ_MASK	0x0600		/* in/out sequence mask */
#घोषणा IP_VS_CONN_F_NO_CPORT	0x0800		/* no client port set yet */
#घोषणा IP_VS_CONN_F_TEMPLATE	0x1000		/* ढाँचा, not connection */
#घोषणा IP_VS_CONN_F_ONE_PACKET	0x2000		/* क्रमward only one packet */

/* Initial bits allowed in backup server */
#घोषणा IP_VS_CONN_F_BACKUP_MASK (IP_VS_CONN_F_FWD_MASK | \
				  IP_VS_CONN_F_NOOUTPUT | \
				  IP_VS_CONN_F_INACTIVE | \
				  IP_VS_CONN_F_SEQ_MASK | \
				  IP_VS_CONN_F_NO_CPORT | \
				  IP_VS_CONN_F_TEMPLATE \
				 )

/* Bits allowed to update in backup server */
#घोषणा IP_VS_CONN_F_BACKUP_UPD_MASK (IP_VS_CONN_F_INACTIVE | \
				      IP_VS_CONN_F_SEQ_MASK)

/* Flags that are not sent to backup server start from bit 16 */
#घोषणा IP_VS_CONN_F_NFCT	(1 << 16)	/* use netfilter conntrack */

/* Connection flags from destination that can be changed by user space */
#घोषणा IP_VS_CONN_F_DEST_MASK (IP_VS_CONN_F_FWD_MASK | \
				IP_VS_CONN_F_ONE_PACKET | \
				IP_VS_CONN_F_NFCT | \
				0)

#घोषणा IP_VS_SCHEDNAME_MAXLEN	16
#घोषणा IP_VS_PENAME_MAXLEN	16
#घोषणा IP_VS_IFNAME_MAXLEN	16

#घोषणा IP_VS_PEDATA_MAXLEN     255

/* Tunnel types */
क्रमागत अणु
	IP_VS_CONN_F_TUNNEL_TYPE_IPIP = 0,	/* IPIP */
	IP_VS_CONN_F_TUNNEL_TYPE_GUE,		/* GUE */
	IP_VS_CONN_F_TUNNEL_TYPE_GRE,		/* GRE */
	IP_VS_CONN_F_TUNNEL_TYPE_MAX,
पूर्ण;

/* Tunnel encapsulation flags */
#घोषणा IP_VS_TUNNEL_ENCAP_FLAG_NOCSUM		(0)
#घोषणा IP_VS_TUNNEL_ENCAP_FLAG_CSUM		(1 << 0)
#घोषणा IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM		(1 << 1)

/*
 *	The काष्ठा ip_vs_service_user and काष्ठा ip_vs_dest_user are
 *	used to set IPVS rules through setsockopt.
 */
काष्ठा ip_vs_service_user अणु
	/* भव service addresses */
	__u16		protocol;
	__be32			addr;		/* भव ip address */
	__be16			port;
	__u32		fwmark;		/* firwall mark of service */

	/* भव service options */
	अक्षर			sched_name[IP_VS_SCHEDNAME_MAXLEN];
	अचिन्हित पूर्णांक		flags;		/* भव service flags */
	अचिन्हित पूर्णांक		समयout;	/* persistent समयout in sec */
	__be32			neपंचांगask;	/* persistent neपंचांगask */
पूर्ण;


काष्ठा ip_vs_dest_user अणु
	/* destination server address */
	__be32			addr;
	__be16			port;

	/* real server options */
	अचिन्हित पूर्णांक		conn_flags;	/* connection flags */
	पूर्णांक			weight;		/* destination weight */

	/* thresholds क्रम active connections */
	__u32		u_threshold;	/* upper threshold */
	__u32		l_threshold;	/* lower threshold */
पूर्ण;


/*
 *	IPVS statistics object (क्रम user space)
 */
काष्ठा ip_vs_stats_user अणु
	__u32                   conns;          /* connections scheduled */
	__u32                   inpkts;         /* incoming packets */
	__u32                   outpkts;        /* outgoing packets */
	__u64                   inbytes;        /* incoming bytes */
	__u64                   outbytes;       /* outgoing bytes */

	__u32			cps;		/* current connection rate */
	__u32			inpps;		/* current in packet rate */
	__u32			outpps;		/* current out packet rate */
	__u32			inbps;		/* current in byte rate */
	__u32			outbps;		/* current out byte rate */
पूर्ण;


/* The argument to IP_VS_SO_GET_INFO */
काष्ठा ip_vs_getinfo अणु
	/* version number */
	अचिन्हित पूर्णांक		version;

	/* size of connection hash table */
	अचिन्हित पूर्णांक		size;

	/* number of भव services */
	अचिन्हित पूर्णांक		num_services;
पूर्ण;


/* The argument to IP_VS_SO_GET_SERVICE */
काष्ठा ip_vs_service_entry अणु
	/* which service: user fills in these */
	__u16		protocol;
	__be32			addr;		/* भव address */
	__be16			port;
	__u32		fwmark;		/* firwall mark of service */

	/* service options */
	अक्षर			sched_name[IP_VS_SCHEDNAME_MAXLEN];
	अचिन्हित पूर्णांक		flags;          /* भव service flags */
	अचिन्हित पूर्णांक		समयout;	/* persistent समयout */
	__be32			neपंचांगask;	/* persistent neपंचांगask */

	/* number of real servers */
	अचिन्हित पूर्णांक		num_dests;

	/* statistics */
	काष्ठा ip_vs_stats_user stats;
पूर्ण;


काष्ठा ip_vs_dest_entry अणु
	__be32			addr;		/* destination address */
	__be16			port;
	अचिन्हित पूर्णांक		conn_flags;	/* connection flags */
	पूर्णांक			weight;		/* destination weight */

	__u32		u_threshold;	/* upper threshold */
	__u32		l_threshold;	/* lower threshold */

	__u32		activeconns;	/* active connections */
	__u32		inactconns;	/* inactive connections */
	__u32		persistconns;	/* persistent connections */

	/* statistics */
	काष्ठा ip_vs_stats_user stats;
पूर्ण;


/* The argument to IP_VS_SO_GET_DESTS */
काष्ठा ip_vs_get_dests अणु
	/* which service: user fills in these */
	__u16		protocol;
	__be32			addr;		/* भव address */
	__be16			port;
	__u32		fwmark;		/* firwall mark of service */

	/* number of real servers */
	अचिन्हित पूर्णांक		num_dests;

	/* the real servers */
	काष्ठा ip_vs_dest_entry	entrytable[0];
पूर्ण;


/* The argument to IP_VS_SO_GET_SERVICES */
काष्ठा ip_vs_get_services अणु
	/* number of भव services */
	अचिन्हित पूर्णांक		num_services;

	/* service table */
	काष्ठा ip_vs_service_entry entrytable[0];
पूर्ण;


/* The argument to IP_VS_SO_GET_TIMEOUT */
काष्ठा ip_vs_समयout_user अणु
	पूर्णांक			tcp_समयout;
	पूर्णांक			tcp_fin_समयout;
	पूर्णांक			udp_समयout;
पूर्ण;


/* The argument to IP_VS_SO_GET_DAEMON */
काष्ठा ip_vs_daemon_user अणु
	/* sync daemon state (master/backup) */
	पूर्णांक			state;

	/* multicast पूर्णांकerface name */
	अक्षर			mcast_अगरn[IP_VS_IFNAME_MAXLEN];

	/* SyncID we beदीर्घ to */
	पूर्णांक			syncid;
पूर्ण;

/*
 *
 * IPVS Generic Netlink पूर्णांकerface definitions
 *
 */

/* Generic Netlink family info */

#घोषणा IPVS_GENL_NAME		"IPVS"
#घोषणा IPVS_GENL_VERSION	0x1

काष्ठा ip_vs_flags अणु
	__u32 flags;
	__u32 mask;
पूर्ण;

/* Generic Netlink command attributes */
क्रमागत अणु
	IPVS_CMD_UNSPEC = 0,

	IPVS_CMD_NEW_SERVICE,		/* add service */
	IPVS_CMD_SET_SERVICE,		/* modअगरy service */
	IPVS_CMD_DEL_SERVICE,		/* delete service */
	IPVS_CMD_GET_SERVICE,		/* get service info */

	IPVS_CMD_NEW_DEST,		/* add destination */
	IPVS_CMD_SET_DEST,		/* modअगरy destination */
	IPVS_CMD_DEL_DEST,		/* delete destination */
	IPVS_CMD_GET_DEST,		/* get destination info */

	IPVS_CMD_NEW_DAEMON,		/* start sync daemon */
	IPVS_CMD_DEL_DAEMON,		/* stop sync daemon */
	IPVS_CMD_GET_DAEMON,		/* get sync daemon status */

	IPVS_CMD_SET_CONFIG,		/* set config settings */
	IPVS_CMD_GET_CONFIG,		/* get config settings */

	IPVS_CMD_SET_INFO,		/* only used in GET_INFO reply */
	IPVS_CMD_GET_INFO,		/* get general IPVS info */

	IPVS_CMD_ZERO,			/* zero all counters and stats */
	IPVS_CMD_FLUSH,			/* flush services and dests */

	__IPVS_CMD_MAX,
पूर्ण;

#घोषणा IPVS_CMD_MAX (__IPVS_CMD_MAX - 1)

/* Attributes used in the first level of commands */
क्रमागत अणु
	IPVS_CMD_ATTR_UNSPEC = 0,
	IPVS_CMD_ATTR_SERVICE,		/* nested service attribute */
	IPVS_CMD_ATTR_DEST,		/* nested destination attribute */
	IPVS_CMD_ATTR_DAEMON,		/* nested sync daemon attribute */
	IPVS_CMD_ATTR_TIMEOUT_TCP,	/* TCP connection समयout */
	IPVS_CMD_ATTR_TIMEOUT_TCP_FIN,	/* TCP FIN रुको समयout */
	IPVS_CMD_ATTR_TIMEOUT_UDP,	/* UDP समयout */
	__IPVS_CMD_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_CMD_ATTR_MAX (__IPVS_CMD_ATTR_MAX - 1)

/*
 * Attributes used to describe a service
 *
 * Used inside nested attribute IPVS_CMD_ATTR_SERVICE
 */
क्रमागत अणु
	IPVS_SVC_ATTR_UNSPEC = 0,
	IPVS_SVC_ATTR_AF,		/* address family */
	IPVS_SVC_ATTR_PROTOCOL,		/* भव service protocol */
	IPVS_SVC_ATTR_ADDR,		/* भव service address */
	IPVS_SVC_ATTR_PORT,		/* भव service port */
	IPVS_SVC_ATTR_FWMARK,		/* firewall mark of service */

	IPVS_SVC_ATTR_SCHED_NAME,	/* name of scheduler */
	IPVS_SVC_ATTR_FLAGS,		/* भव service flags */
	IPVS_SVC_ATTR_TIMEOUT,		/* persistent समयout */
	IPVS_SVC_ATTR_NETMASK,		/* persistent neपंचांगask */

	IPVS_SVC_ATTR_STATS,		/* nested attribute क्रम service stats */

	IPVS_SVC_ATTR_PE_NAME,		/* name of ct retriever */

	IPVS_SVC_ATTR_STATS64,		/* nested attribute क्रम service stats */

	__IPVS_SVC_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_SVC_ATTR_MAX (__IPVS_SVC_ATTR_MAX - 1)

/*
 * Attributes used to describe a destination (real server)
 *
 * Used inside nested attribute IPVS_CMD_ATTR_DEST
 */
क्रमागत अणु
	IPVS_DEST_ATTR_UNSPEC = 0,
	IPVS_DEST_ATTR_ADDR,		/* real server address */
	IPVS_DEST_ATTR_PORT,		/* real server port */

	IPVS_DEST_ATTR_FWD_METHOD,	/* क्रमwarding method */
	IPVS_DEST_ATTR_WEIGHT,		/* destination weight */

	IPVS_DEST_ATTR_U_THRESH,	/* upper threshold */
	IPVS_DEST_ATTR_L_THRESH,	/* lower threshold */

	IPVS_DEST_ATTR_ACTIVE_CONNS,	/* active connections */
	IPVS_DEST_ATTR_INACT_CONNS,	/* inactive connections */
	IPVS_DEST_ATTR_PERSIST_CONNS,	/* persistent connections */

	IPVS_DEST_ATTR_STATS,		/* nested attribute क्रम dest stats */

	IPVS_DEST_ATTR_ADDR_FAMILY,	/* Address family of address */

	IPVS_DEST_ATTR_STATS64,		/* nested attribute क्रम dest stats */

	IPVS_DEST_ATTR_TUN_TYPE,	/* tunnel type */

	IPVS_DEST_ATTR_TUN_PORT,	/* tunnel port */

	IPVS_DEST_ATTR_TUN_FLAGS,	/* tunnel flags */

	__IPVS_DEST_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_DEST_ATTR_MAX (__IPVS_DEST_ATTR_MAX - 1)

/*
 * Attributes describing a sync daemon
 *
 * Used inside nested attribute IPVS_CMD_ATTR_DAEMON
 */
क्रमागत अणु
	IPVS_DAEMON_ATTR_UNSPEC = 0,
	IPVS_DAEMON_ATTR_STATE,		/* sync daemon state (master/backup) */
	IPVS_DAEMON_ATTR_MCAST_IFN,	/* multicast पूर्णांकerface name */
	IPVS_DAEMON_ATTR_SYNC_ID,	/* SyncID we beदीर्घ to */
	IPVS_DAEMON_ATTR_SYNC_MAXLEN,	/* UDP Payload Size */
	IPVS_DAEMON_ATTR_MCAST_GROUP,	/* IPv4 Multicast Address */
	IPVS_DAEMON_ATTR_MCAST_GROUP6,	/* IPv6 Multicast Address */
	IPVS_DAEMON_ATTR_MCAST_PORT,	/* Multicast Port (base) */
	IPVS_DAEMON_ATTR_MCAST_TTL,	/* Multicast TTL */
	__IPVS_DAEMON_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_DAEMON_ATTR_MAX (__IPVS_DAEMON_ATTR_MAX - 1)

/*
 * Attributes used to describe service or destination entry statistics
 *
 * Used inside nested attributes IPVS_SVC_ATTR_STATS, IPVS_DEST_ATTR_STATS,
 * IPVS_SVC_ATTR_STATS64 and IPVS_DEST_ATTR_STATS64.
 */
क्रमागत अणु
	IPVS_STATS_ATTR_UNSPEC = 0,
	IPVS_STATS_ATTR_CONNS,		/* connections scheduled */
	IPVS_STATS_ATTR_INPKTS,		/* incoming packets */
	IPVS_STATS_ATTR_OUTPKTS,	/* outgoing packets */
	IPVS_STATS_ATTR_INBYTES,	/* incoming bytes */
	IPVS_STATS_ATTR_OUTBYTES,	/* outgoing bytes */

	IPVS_STATS_ATTR_CPS,		/* current connection rate */
	IPVS_STATS_ATTR_INPPS,		/* current in packet rate */
	IPVS_STATS_ATTR_OUTPPS,		/* current out packet rate */
	IPVS_STATS_ATTR_INBPS,		/* current in byte rate */
	IPVS_STATS_ATTR_OUTBPS,		/* current out byte rate */
	IPVS_STATS_ATTR_PAD,
	__IPVS_STATS_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_STATS_ATTR_MAX (__IPVS_STATS_ATTR_MAX - 1)

/* Attributes used in response to IPVS_CMD_GET_INFO command */
क्रमागत अणु
	IPVS_INFO_ATTR_UNSPEC = 0,
	IPVS_INFO_ATTR_VERSION,		/* IPVS version number */
	IPVS_INFO_ATTR_CONN_TAB_SIZE,	/* size of connection hash table */
	__IPVS_INFO_ATTR_MAX,
पूर्ण;

#घोषणा IPVS_INFO_ATTR_MAX (__IPVS_INFO_ATTR_MAX - 1)

#पूर्ण_अगर	/* _IP_VS_H */
