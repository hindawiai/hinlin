<शैली गुरु>
#अगर_अघोषित _NF_OSF_H
#घोषणा _NF_OSF_H

#समावेश <linux/types.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>

#घोषणा MAXGENRELEN	32

#घोषणा NF_OSF_GENRE	(1 << 0)
#घोषणा NF_OSF_TTL	(1 << 1)
#घोषणा NF_OSF_LOG	(1 << 2)
#घोषणा NF_OSF_INVERT	(1 << 3)

#घोषणा NF_OSF_LOGLEVEL_ALL		0	/* log all matched fingerprपूर्णांकs */
#घोषणा NF_OSF_LOGLEVEL_FIRST		1	/* log only the first matced fingerprपूर्णांक */
#घोषणा NF_OSF_LOGLEVEL_ALL_KNOWN	2	/* करो not log unknown packets */

#घोषणा NF_OSF_TTL_TRUE			0	/* True ip and fingerprपूर्णांक TTL comparison */

/* Check अगर ip TTL is less than fingerprपूर्णांक one */
#घोषणा NF_OSF_TTL_LESS			1

/* Do not compare ip and fingerprपूर्णांक TTL at all */
#घोषणा NF_OSF_TTL_NOCHECK		2

#घोषणा NF_OSF_FLAGMASK		(NF_OSF_GENRE | NF_OSF_TTL | \
				 NF_OSF_LOG | NF_OSF_INVERT)
/* Wildcard MSS (kind of).
 * It is used to implement a state machine क्रम the dअगरferent wildcard values
 * of the MSS and winकरोw sizes.
 */
काष्ठा nf_osf_wc अणु
	__u32	wc;
	__u32	val;
पूर्ण;

/* This काष्ठा represents IANA options
 * http://www.iana.org/assignments/tcp-parameters
 */
काष्ठा nf_osf_opt अणु
	__u16			kind, length;
	काष्ठा nf_osf_wc	wc;
पूर्ण;

काष्ठा nf_osf_info अणु
	अक्षर	genre[MAXGENRELEN];
	__u32	len;
	__u32	flags;
	__u32	loglevel;
	__u32	ttl;
पूर्ण;

काष्ठा nf_osf_user_finger अणु
	काष्ठा nf_osf_wc	wss;

	__u8	ttl, df;
	__u16	ss, mss;
	__u16	opt_num;

	अक्षर	genre[MAXGENRELEN];
	अक्षर	version[MAXGENRELEN];
	अक्षर	subtype[MAXGENRELEN];

	/* MAX_IPOPTLEN is maximum अगर all options are NOPs or EOLs */
	काष्ठा nf_osf_opt	opt[MAX_IPOPTLEN];
पूर्ण;

काष्ठा nf_osf_nlmsg अणु
	काष्ठा nf_osf_user_finger	f;
	काष्ठा iphdr			ip;
	काष्ठा tcphdr			tcp;
पूर्ण;

/* Defines क्रम IANA option kinds */
क्रमागत iana_options अणु
	OSFOPT_EOL = 0,		/* End of options */
	OSFOPT_NOP,		/* NOP */
	OSFOPT_MSS,		/* Maximum segment size */
	OSFOPT_WSO,		/* Winकरोw scale option */
	OSFOPT_SACKP,		/* SACK permitted */
	OSFOPT_SACK,		/* SACK */
	OSFOPT_ECHO,
	OSFOPT_ECHOREPLY,
	OSFOPT_TS,		/* Timestamp option */
	OSFOPT_POCP,		/* Partial Order Connection Permitted */
	OSFOPT_POSP,		/* Partial Order Service Profile */

	/* Others are not used in the current OSF */
	OSFOPT_EMPTY = 255,
पूर्ण;

/* Initial winकरोw size option state machine: multiple of mss, mtu or
 * plain numeric value. Can also be made as plain numeric value which
 * is not a multiple of specअगरied value.
 */
क्रमागत nf_osf_winकरोw_size_options अणु
	OSF_WSS_PLAIN	= 0,
	OSF_WSS_MSS,
	OSF_WSS_MTU,
	OSF_WSS_MODULO,
	OSF_WSS_MAX,
पूर्ण;

क्रमागत nf_osf_attr_type अणु
	OSF_ATTR_UNSPEC,
	OSF_ATTR_FINGER,
	OSF_ATTR_MAX,
पूर्ण;

/*
 * Add/हटाओ fingerprपूर्णांक from the kernel.
 */
क्रमागत nf_osf_msg_types अणु
	OSF_MSG_ADD,
	OSF_MSG_REMOVE,
	OSF_MSG_MAX,
पूर्ण;

#पूर्ण_अगर /* _NF_OSF_H */
