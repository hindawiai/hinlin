<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_SCTP_H__
#घोषणा __NETNS_SCTP_H__

काष्ठा sock;
काष्ठा proc_dir_entry;
काष्ठा sctp_mib;
काष्ठा ctl_table_header;

काष्ठा netns_sctp अणु
	DEFINE_SNMP_STAT(काष्ठा sctp_mib, sctp_statistics);

#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *proc_net_sctp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header *sysctl_header;
#पूर्ण_अगर
	/* This is the global socket data काष्ठाure used क्रम responding to
	 * the Out-of-the-blue (OOTB) packets.  A control sock will be created
	 * क्रम this socket at the initialization समय.
	 */
	काष्ठा sock *ctl_sock;

	/* UDP tunneling listening sock. */
	काष्ठा sock *udp4_sock;
	काष्ठा sock *udp6_sock;
	/* UDP tunneling listening port. */
	पूर्णांक udp_port;
	/* UDP tunneling remote encap port. */
	पूर्णांक encap_port;

	/* This is the global local address list.
	 * We actively मुख्यtain this complete list of addresses on
	 * the प्रणाली by catching address add/delete events.
	 *
	 * It is a list of sctp_sockaddr_entry.
	 */
	काष्ठा list_head local_addr_list;
	काष्ठा list_head addr_रुकोq;
	काष्ठा समयr_list addr_wq_समयr;
	काष्ठा list_head स्वतः_asconf_splist;
	/* Lock that protects both addr_रुकोq and स्वतः_asconf_splist */
	spinlock_t addr_wq_lock;

	/* Lock that protects the local_addr_list ग_लिखोrs */
	spinlock_t local_addr_lock;

	/* RFC2960 Section 14. Suggested SCTP Protocol Parameter Values
	 *
	 * The following protocol parameters are RECOMMENDED:
	 *
	 * RTO.Initial		    - 3	 seconds
	 * RTO.Min		    - 1	 second
	 * RTO.Max		   -  60 seconds
	 * RTO.Alpha		    - 1/8  (3 when converted to right shअगरts.)
	 * RTO.Beta		    - 1/4  (2 when converted to right shअगरts.)
	 */
	अचिन्हित पूर्णांक rto_initial;
	अचिन्हित पूर्णांक rto_min;
	अचिन्हित पूर्णांक rto_max;

	/* Note: rto_alpha and rto_beta are really defined as inverse
	 * घातers of two to facilitate पूर्णांकeger operations.
	 */
	पूर्णांक rto_alpha;
	पूर्णांक rto_beta;

	/* Max.Burst		    - 4 */
	पूर्णांक max_burst;

	/* Whether Cookie Preservative is enabled(1) or not(0) */
	पूर्णांक cookie_preserve_enable;

	/* The namespace शेष hmac alg */
	अक्षर *sctp_hmac_alg;

	/* Valid.Cookie.Lअगरe	    - 60  seconds  */
	अचिन्हित पूर्णांक valid_cookie_lअगरe;

	/* Delayed SACK समयout  200ms शेष*/
	अचिन्हित पूर्णांक sack_समयout;

	/* HB.पूर्णांकerval		    - 30 seconds  */
	अचिन्हित पूर्णांक hb_पूर्णांकerval;

	/* Association.Max.Retrans  - 10 attempts
	 * Path.Max.Retrans	    - 5	 attempts (per destination address)
	 * Max.Init.Retransmits	    - 8	 attempts
	 */
	पूर्णांक max_retrans_association;
	पूर्णांक max_retrans_path;
	पूर्णांक max_retrans_init;
	/* Potentially-Failed.Max.Retrans sysctl value
	 * taken from:
	 * http://tools.ietf.org/hपंचांगl/draft-nishida-tsvwg-sctp-failover-05
	 */
	पूर्णांक pf_retrans;

	/* Primary.Switchover.Max.Retrans sysctl value
	 * taken from:
	 * https://tools.ietf.org/hपंचांगl/rfc7829
	 */
	पूर्णांक ps_retrans;

	/*
	 * Disable Potentially-Failed feature, the feature is enabled by शेष
	 * pf_enable	-  0  : disable pf
	 *		- >0  : enable pf
	 */
	पूर्णांक pf_enable;

	/*
	 * Disable Potentially-Failed state exposure, ignored by शेष
	 * pf_expose	-  0  : compatible with old applications (by शेष)
	 *		-  1  : disable pf state exposure
	 *		-  2  : enable  pf state exposure
	 */
	पूर्णांक pf_expose;

	/*
	 * Policy क्रम preक्रमming sctp/socket accounting
	 * 0   - करो socket level accounting, all assocs share sk_sndbuf
	 * 1   - करो sctp accounting, each asoc may use sk_sndbuf bytes
	 */
	पूर्णांक sndbuf_policy;

	/*
	 * Policy क्रम preक्रमming sctp/socket accounting
	 * 0   - करो socket level accounting, all assocs share sk_rcvbuf
	 * 1   - करो sctp accounting, each asoc may use sk_rcvbuf bytes
	 */
	पूर्णांक rcvbuf_policy;

	पूर्णांक शेष_स्वतः_asconf;

	/* Flag to indicate अगर addip is enabled. */
	पूर्णांक addip_enable;
	पूर्णांक addip_noauth;

	/* Flag to indicate अगर PR-SCTP is enabled. */
	पूर्णांक prsctp_enable;

	/* Flag to indicate अगर PR-CONFIG is enabled. */
	पूर्णांक reconf_enable;

	/* Flag to indicate अगर SCTP-AUTH is enabled */
	पूर्णांक auth_enable;

	/* Flag to indicate अगर stream पूर्णांकerleave is enabled */
	पूर्णांक पूर्णांकl_enable;

	/* Flag to indicate अगर ecn is enabled */
	पूर्णांक ecn_enable;

	/*
	 * Policy to control SCTP IPv4 address scoping
	 * 0   - Disable IPv4 address scoping
	 * 1   - Enable IPv4 address scoping
	 * 2   - Selectively allow only IPv4 निजी addresses
	 * 3   - Selectively allow only IPv4 link local address
	 */
	पूर्णांक scope_policy;

	/* Threshold क्रम rwnd update SACKS.  Receive buffer shअगरted this many
	 * bits is an indicator of when to send and winकरोw update SACK.
	 */
	पूर्णांक rwnd_upd_shअगरt;

	/* Threshold क्रम स्वतःबंद समयout, in seconds. */
	अचिन्हित दीर्घ max_स्वतःबंद;
पूर्ण;

#पूर्ण_अगर /* __NETNS_SCTP_H__ */
