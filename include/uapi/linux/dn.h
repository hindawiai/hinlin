<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_DN_H
#घोषणा _LINUX_DN_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

/*

	DECnet Data Structures and Constants

*/

/* 
 * DNPROTO_NSP can't be the same as SOL_SOCKET, 
 * so increment each by one (compared to ULTRIX)
 */
#घोषणा DNPROTO_NSP     2                       /* NSP protocol number       */
#घोषणा DNPROTO_ROU     3                       /* Routing protocol number   */
#घोषणा DNPROTO_NML     4                       /* Net mgt protocol number   */
#घोषणा DNPROTO_EVL     5                       /* Evl protocol number (usr) */
#घोषणा DNPROTO_EVR     6                       /* Evl protocol number (evl) */
#घोषणा DNPROTO_NSPT    7                       /* NSP trace protocol number */


#घोषणा DN_ADDL		2
#घोषणा DN_MAXADDL	2 /* ULTRIX headers have 20 here, but pathworks has 2 */
#घोषणा DN_MAXOPTL	16
#घोषणा DN_MAXOBJL	16
#घोषणा DN_MAXACCL	40
#घोषणा DN_MAXALIASL	128
#घोषणा DN_MAXNODEL	256
#घोषणा DNबफ_मानE	65023

/* 
 * SET/GET Socket options  - must match the DSO_ numbers below
 */
#घोषणा SO_CONDATA      1
#घोषणा SO_CONACCESS    2
#घोषणा SO_PROXYUSR     3
#घोषणा SO_LINKINFO     7

#घोषणा DSO_CONDATA     1        /* Set/Get connect data                */
#घोषणा DSO_DISDATA     10       /* Set/Get disconnect data             */
#घोषणा DSO_CONACCESS   2        /* Set/Get connect access data         */
#घोषणा DSO_ACCEPTMODE  4        /* Set/Get accept mode                 */
#घोषणा DSO_CONACCEPT   5        /* Accept deferred connection          */
#घोषणा DSO_CONREJECT   6        /* Reject deferred connection          */
#घोषणा DSO_LINKINFO    7        /* Set/Get link inक्रमmation            */
#घोषणा DSO_STREAM      8        /* Set socket type to stream           */
#घोषणा DSO_SEQPACKET   9        /* Set socket type to sequenced packet */
#घोषणा DSO_MAXWINDOW   11       /* Maximum winकरोw size allowed         */
#घोषणा DSO_NODELAY	12       /* Turn off nagle                      */
#घोषणा DSO_CORK        13       /* Wait क्रम more data!                 */
#घोषणा DSO_SERVICES	14       /* NSP Services field                  */
#घोषणा DSO_INFO	15       /* NSP Info field                      */
#घोषणा DSO_MAX         15       /* Maximum option number               */


/* LINK States */
#घोषणा LL_INACTIVE	0
#घोषणा LL_CONNECTING	1
#घोषणा LL_RUNNING	2
#घोषणा LL_DISCONNECTING 3

#घोषणा ACC_IMMED 0
#घोषणा ACC_DEFER 1

#घोषणा SDF_WILD        1                  /* Wild card object          */
#घोषणा SDF_PROXY       2                  /* Addr eligible क्रम proxy   */
#घोषणा SDF_UICPROXY    4                  /* Use uic-based proxy       */

/* Structures */


काष्ठा dn_naddr अणु
	__le16		a_len;
	__u8 a_addr[DN_MAXADDL]; /* Two bytes little endian */
पूर्ण;

काष्ठा sockaddr_dn अणु
	__u16		sdn_family;
	__u8		sdn_flags;
	__u8		sdn_objnum;
	__le16		sdn_objnamel;
	__u8		sdn_objname[DN_MAXOBJL];
	काष्ठा   dn_naddr	sdn_add;
पूर्ण;
#घोषणा sdn_nodeaddrl   sdn_add.a_len   /* Node address length  */
#घोषणा sdn_nodeaddr    sdn_add.a_addr  /* Node address         */



/*
 * DECnet set/get DSO_CONDATA, DSO_DISDATA (optional data) काष्ठाure
 */
काष्ठा optdata_dn अणु
        __le16  opt_status;     /* Extended status वापस */
#घोषणा opt_sts opt_status
        __le16  opt_optl;       /* Length of user data    */
        __u8   opt_data[16];   /* User data              */
पूर्ण;

काष्ठा accessdata_dn अणु
	__u8		acc_accl;
	__u8		acc_acc[DN_MAXACCL];
	__u8 		acc_passl;
	__u8		acc_pass[DN_MAXACCL];
	__u8 		acc_userl;
	__u8		acc_user[DN_MAXACCL];
पूर्ण;

/*
 * DECnet logical link inक्रमmation काष्ठाure
 */
काष्ठा linkinfo_dn अणु
        __u16  idn_segsize;    /* Segment size क्रम link */
        __u8   idn_linkstate;  /* Logical link state    */
पूर्ण;

/*
 * Ethernet address क्रमmat (क्रम DECnet)
 */
जोड़ etheraddress अणु
        __u8 dne_addr[ETH_ALEN];      /* Full ethernet address */
  काष्ठा अणु
                __u8 dne_hiord[4];    /* DECnet HIORD prefix   */
                __u8 dne_nodeaddr[2]; /* DECnet node address   */
  पूर्ण dne_remote;
पूर्ण;


/*
 * DECnet physical socket address क्रमmat
 */
काष्ठा dn_addr अणु
        __le16 dna_family;      /* AF_DECnet               */
        जोड़ etheraddress dna_netaddr; /* DECnet ethernet address */
पूर्ण;

#घोषणा DECNET_IOCTL_BASE 0x89 /* PROTOPRIVATE range */

#घोषणा SIOCSNETADDR  _IOW(DECNET_IOCTL_BASE, 0xe0, काष्ठा dn_naddr)
#घोषणा SIOCGNETADDR  _IOR(DECNET_IOCTL_BASE, 0xe1, काष्ठा dn_naddr)
#घोषणा OSIOCSNETADDR _IOW(DECNET_IOCTL_BASE, 0xe0, पूर्णांक)
#घोषणा OSIOCGNETADDR _IOR(DECNET_IOCTL_BASE, 0xe1, पूर्णांक)

#पूर्ण_अगर /* _LINUX_DN_H */
