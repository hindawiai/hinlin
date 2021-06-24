<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ATM Lan Emulation Daemon driver पूर्णांकerface
 *
 * Marko Kiiskila <mkiiskila@yahoo.com>
 */

#अगर_अघोषित _ATMLEC_H_
#घोषणा _ATMLEC_H_

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/types.h>

/* ATM lec daemon control socket */
#घोषणा ATMLEC_CTRL	_IO('a', ATMIOC_LANE)
#घोषणा ATMLEC_DATA	_IO('a', ATMIOC_LANE+1)
#घोषणा ATMLEC_MCAST	_IO('a', ATMIOC_LANE+2)

/* Maximum number of LEC पूर्णांकerfaces (tweakable) */
#घोषणा MAX_LEC_ITF 48

प्रकार क्रमागत अणु
	l_set_mac_addr,
	l_del_mac_addr,
	l_svc_setup,
	l_addr_delete,
	l_topology_change,
	l_flush_complete,
	l_arp_update,
	l_narp_req,		/* LANE2 mandates the use of this */
	l_config,
	l_flush_tran_id,
	l_set_lecid,
	l_arp_xmt,
	l_rdesc_arp_xmt,
	l_associate_req,
	l_should_bridge		/* should we bridge this MAC? */
पूर्ण aपंचांगlec_msg_type;

#घोषणा ATMLEC_MSG_TYPE_MAX l_should_bridge

काष्ठा aपंचांगlec_config_msg अणु
	अचिन्हित पूर्णांक maximum_unknown_frame_count;
	अचिन्हित पूर्णांक max_unknown_frame_समय;
	अचिन्हित लघु max_retry_count;
	अचिन्हित पूर्णांक aging_समय;
	अचिन्हित पूर्णांक क्रमward_delay_समय;
	अचिन्हित पूर्णांक arp_response_समय;
	अचिन्हित पूर्णांक flush_समयout;
	अचिन्हित पूर्णांक path_चयनing_delay;
	अचिन्हित पूर्णांक lane_version;	/* LANE2: 1 क्रम LANEv1, 2 क्रम LANEv2 */
	पूर्णांक mtu;
	पूर्णांक is_proxy;
पूर्ण;

काष्ठा aपंचांगlec_msg अणु
	aपंचांगlec_msg_type type;
	पूर्णांक मापtlvs;		/* LANE2: अगर != 0, tlvs follow */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित अक्षर mac_addr[ETH_ALEN];
			अचिन्हित अक्षर aपंचांग_addr[ATM_ESA_LEN];
			अचिन्हित पूर्णांक flag;	/*
						 * Topology_change flag,
						 * remoteflag, permanent flag,
						 * lecid, transaction id
						 */
			अचिन्हित पूर्णांक targetless_le_arp;	/* LANE2 */
			अचिन्हित पूर्णांक no_source_le_narp;	/* LANE2 */
		पूर्ण normal;
		काष्ठा aपंचांगlec_config_msg config;
		काष्ठा अणु
			__u16 lec_id;				/* requestor lec_id  */
			__u32 tran_id;				/* transaction id    */
			अचिन्हित अक्षर mac_addr[ETH_ALEN];	/* dst mac addr      */
			अचिन्हित अक्षर aपंचांग_addr[ATM_ESA_LEN];	/* reqestor ATM addr */
		पूर्ण proxy;	/*
				 * For mapping LE_ARP requests to responses. Filled by
				 * zeppelin, वापसed by kernel. Used only when proxying
				 */
	पूर्ण content;
पूर्ण __ATM_API_ALIGN;

काष्ठा aपंचांगlec_ioc अणु
	पूर्णांक dev_num;
	अचिन्हित अक्षर aपंचांग_addr[ATM_ESA_LEN];
	अचिन्हित अक्षर receive;	/* 1= receive vcc, 0 = send vcc */
पूर्ण;
#पूर्ण_अगर /* _ATMLEC_H_ */
