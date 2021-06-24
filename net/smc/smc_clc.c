<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  CLC (connection layer control) handshake over initial TCP socket to
 *  prepare क्रम RDMA traffic
 *
 *  Copyright IBM Corp. 2016, 2018
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/in.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/utsname.h>
#समावेश <linux/प्रकार.स>

#समावेश <net/addrconf.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>

#समावेश "smc.h"
#समावेश "smc_core.h"
#समावेश "smc_clc.h"
#समावेश "smc_ib.h"
#समावेश "smc_ism.h"

#घोषणा SMCR_CLC_ACCEPT_CONFIRM_LEN 68
#घोषणा SMCD_CLC_ACCEPT_CONFIRM_LEN 48
#घोषणा SMCD_CLC_ACCEPT_CONFIRM_LEN_V2 78
#घोषणा SMC_CLC_RECV_BUF_LEN	100

/* eye catcher "SMCR" EBCDIC क्रम CLC messages */
अटल स्थिर अक्षर SMC_EYECATCHER[4] = अणु'\xe2', '\xd4', '\xc3', '\xd9'पूर्ण;
/* eye catcher "SMCD" EBCDIC क्रम CLC messages */
अटल स्थिर अक्षर SMCD_EYECATCHER[4] = अणु'\xe2', '\xd4', '\xc3', '\xc4'पूर्ण;

अटल u8 smc_hostname[SMC_MAX_HOSTNAME_LEN];

/* check arriving CLC proposal */
अटल bool smc_clc_msg_prop_valid(काष्ठा smc_clc_msg_proposal *pclc)
अणु
	काष्ठा smc_clc_msg_proposal_prefix *pclc_prfx;
	काष्ठा smc_clc_smcd_v2_extension *smcd_v2_ext;
	काष्ठा smc_clc_msg_hdr *hdr = &pclc->hdr;
	काष्ठा smc_clc_v2_extension *v2_ext;

	v2_ext = smc_get_clc_v2_ext(pclc);
	pclc_prfx = smc_clc_proposal_get_prefix(pclc);
	अगर (hdr->version == SMC_V1) अणु
		अगर (hdr->typev1 == SMC_TYPE_N)
			वापस false;
		अगर (ntohs(hdr->length) !=
			माप(*pclc) + ntohs(pclc->iparea_offset) +
			माप(*pclc_prfx) +
			pclc_prfx->ipv6_prefixes_cnt *
				माप(काष्ठा smc_clc_ipv6_prefix) +
			माप(काष्ठा smc_clc_msg_trail))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (ntohs(hdr->length) !=
			माप(*pclc) +
			माप(काष्ठा smc_clc_msg_smcd) +
			(hdr->typev1 != SMC_TYPE_N ?
				माप(*pclc_prfx) +
				pclc_prfx->ipv6_prefixes_cnt *
				माप(काष्ठा smc_clc_ipv6_prefix) : 0) +
			(hdr->typev2 != SMC_TYPE_N ?
				माप(*v2_ext) +
				v2_ext->hdr.eid_cnt * SMC_MAX_EID_LEN : 0) +
			(smcd_indicated(hdr->typev2) ?
				माप(*smcd_v2_ext) + v2_ext->hdr.ism_gid_cnt *
					माप(काष्ठा smc_clc_smcd_gid_chid) :
				0) +
			माप(काष्ठा smc_clc_msg_trail))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* check arriving CLC accept or confirm */
अटल bool
smc_clc_msg_acc_conf_valid(काष्ठा smc_clc_msg_accept_confirm_v2 *clc_v2)
अणु
	काष्ठा smc_clc_msg_hdr *hdr = &clc_v2->hdr;

	अगर (hdr->typev1 != SMC_TYPE_R && hdr->typev1 != SMC_TYPE_D)
		वापस false;
	अगर (hdr->version == SMC_V1) अणु
		अगर ((hdr->typev1 == SMC_TYPE_R &&
		     ntohs(hdr->length) != SMCR_CLC_ACCEPT_CONFIRM_LEN) ||
		    (hdr->typev1 == SMC_TYPE_D &&
		     ntohs(hdr->length) != SMCD_CLC_ACCEPT_CONFIRM_LEN))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (hdr->typev1 == SMC_TYPE_D &&
		    ntohs(hdr->length) != SMCD_CLC_ACCEPT_CONFIRM_LEN_V2 &&
		    (ntohs(hdr->length) != SMCD_CLC_ACCEPT_CONFIRM_LEN_V2 +
				माप(काष्ठा smc_clc_first_contact_ext)))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम smc_clc_fill_fce(काष्ठा smc_clc_first_contact_ext *fce, पूर्णांक *len)
अणु
	स_रखो(fce, 0, माप(*fce));
	fce->os_type = SMC_CLC_OS_LINUX;
	fce->release = SMC_RELEASE;
	स_नकल(fce->hostname, smc_hostname, माप(smc_hostname));
	(*len) += माप(*fce);
पूर्ण

/* check अगर received message has a correct header length and contains valid
 * heading and trailing eyecatchers
 */
अटल bool smc_clc_msg_hdr_valid(काष्ठा smc_clc_msg_hdr *clcm, bool check_trl)
अणु
	काष्ठा smc_clc_msg_accept_confirm_v2 *clc_v2;
	काष्ठा smc_clc_msg_proposal *pclc;
	काष्ठा smc_clc_msg_decline *dclc;
	काष्ठा smc_clc_msg_trail *trl;

	अगर (स_भेद(clcm->eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER)) &&
	    स_भेद(clcm->eyecatcher, SMCD_EYECATCHER, माप(SMCD_EYECATCHER)))
		वापस false;
	चयन (clcm->type) अणु
	हाल SMC_CLC_PROPOSAL:
		pclc = (काष्ठा smc_clc_msg_proposal *)clcm;
		अगर (!smc_clc_msg_prop_valid(pclc))
			वापस false;
		trl = (काष्ठा smc_clc_msg_trail *)
			((u8 *)pclc + ntohs(pclc->hdr.length) - माप(*trl));
		अवरोध;
	हाल SMC_CLC_ACCEPT:
	हाल SMC_CLC_CONFIRM:
		clc_v2 = (काष्ठा smc_clc_msg_accept_confirm_v2 *)clcm;
		अगर (!smc_clc_msg_acc_conf_valid(clc_v2))
			वापस false;
		trl = (काष्ठा smc_clc_msg_trail *)
			((u8 *)clc_v2 + ntohs(clc_v2->hdr.length) -
							माप(*trl));
		अवरोध;
	हाल SMC_CLC_DECLINE:
		dclc = (काष्ठा smc_clc_msg_decline *)clcm;
		अगर (ntohs(dclc->hdr.length) != माप(*dclc))
			वापस false;
		trl = &dclc->trl;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	अगर (check_trl &&
	    स_भेद(trl->eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER)) &&
	    स_भेद(trl->eyecatcher, SMCD_EYECATCHER, माप(SMCD_EYECATCHER)))
		वापस false;
	वापस true;
पूर्ण

/* find ipv4 addr on device and get the prefix len, fill CLC proposal msg */
अटल पूर्णांक smc_clc_prfx_set4_rcu(काष्ठा dst_entry *dst, __be32 ipv4,
				 काष्ठा smc_clc_msg_proposal_prefix *prop)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dst->dev);
	स्थिर काष्ठा in_अगरaddr *अगरa;

	अगर (!in_dev)
		वापस -ENODEV;

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (!inet_अगरa_match(ipv4, अगरa))
			जारी;
		prop->prefix_len = inet_mask_len(अगरa->अगरa_mask);
		prop->outgoing_subnet = अगरa->अगरa_address & अगरa->अगरa_mask;
		/* prop->ipv6_prefixes_cnt = 0; alपढ़ोy करोne by स_रखो beक्रमe */
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/* fill CLC proposal msg with ipv6 prefixes from device */
अटल पूर्णांक smc_clc_prfx_set6_rcu(काष्ठा dst_entry *dst,
				 काष्ठा smc_clc_msg_proposal_prefix *prop,
				 काष्ठा smc_clc_ipv6_prefix *ipv6_prfx)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा inet6_dev *in6_dev = __in6_dev_get(dst->dev);
	काष्ठा inet6_अगरaddr *अगरa;
	पूर्णांक cnt = 0;

	अगर (!in6_dev)
		वापस -ENODEV;
	/* use a maximum of 8 IPv6 prefixes from device */
	list_क्रम_each_entry(अगरa, &in6_dev->addr_list, अगर_list) अणु
		अगर (ipv6_addr_type(&अगरa->addr) & IPV6_ADDR_LINKLOCAL)
			जारी;
		ipv6_addr_prefix(&ipv6_prfx[cnt].prefix,
				 &अगरa->addr, अगरa->prefix_len);
		ipv6_prfx[cnt].prefix_len = अगरa->prefix_len;
		cnt++;
		अगर (cnt == SMC_CLC_MAX_V6_PREFIX)
			अवरोध;
	पूर्ण
	prop->ipv6_prefixes_cnt = cnt;
	अगर (cnt)
		वापस 0;
#पूर्ण_अगर
	वापस -ENOENT;
पूर्ण

/* retrieve and set prefixes in CLC proposal msg */
अटल पूर्णांक smc_clc_prfx_set(काष्ठा socket *clcsock,
			    काष्ठा smc_clc_msg_proposal_prefix *prop,
			    काष्ठा smc_clc_ipv6_prefix *ipv6_prfx)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(clcsock->sk);
	काष्ठा sockaddr_storage addrs;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा sockaddr_in *addr;
	पूर्णांक rc = -ENOENT;

	अगर (!dst) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण
	अगर (!dst->dev) अणु
		rc = -ENODEV;
		जाओ out_rel;
	पूर्ण
	/* get address to which the पूर्णांकernal TCP socket is bound */
	kernel_माला_लोockname(clcsock, (काष्ठा sockaddr *)&addrs);
	/* analyze IP specअगरic data of net_device beदीर्घing to TCP socket */
	addr6 = (काष्ठा sockaddr_in6 *)&addrs;
	rcu_पढ़ो_lock();
	अगर (addrs.ss_family == PF_INET) अणु
		/* IPv4 */
		addr = (काष्ठा sockaddr_in *)&addrs;
		rc = smc_clc_prfx_set4_rcu(dst, addr->sin_addr.s_addr, prop);
	पूर्ण अन्यथा अगर (ipv6_addr_v4mapped(&addr6->sin6_addr)) अणु
		/* mapped IPv4 address - peer is IPv4 only */
		rc = smc_clc_prfx_set4_rcu(dst, addr6->sin6_addr.s6_addr32[3],
					   prop);
	पूर्ण अन्यथा अणु
		/* IPv6 */
		rc = smc_clc_prfx_set6_rcu(dst, prop, ipv6_prfx);
	पूर्ण
	rcu_पढ़ो_unlock();
out_rel:
	dst_release(dst);
out:
	वापस rc;
पूर्ण

/* match ipv4 addrs of dev against addr in CLC proposal */
अटल पूर्णांक smc_clc_prfx_match4_rcu(काष्ठा net_device *dev,
				   काष्ठा smc_clc_msg_proposal_prefix *prop)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	स्थिर काष्ठा in_अगरaddr *अगरa;

	अगर (!in_dev)
		वापस -ENODEV;
	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (prop->prefix_len == inet_mask_len(अगरa->अगरa_mask) &&
		    inet_अगरa_match(prop->outgoing_subnet, अगरa))
			वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* match ipv6 addrs of dev against addrs in CLC proposal */
अटल पूर्णांक smc_clc_prfx_match6_rcu(काष्ठा net_device *dev,
				   काष्ठा smc_clc_msg_proposal_prefix *prop)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा inet6_dev *in6_dev = __in6_dev_get(dev);
	काष्ठा smc_clc_ipv6_prefix *ipv6_prfx;
	काष्ठा inet6_अगरaddr *अगरa;
	पूर्णांक i, max;

	अगर (!in6_dev)
		वापस -ENODEV;
	/* ipv6 prefix list starts behind smc_clc_msg_proposal_prefix */
	ipv6_prfx = (काष्ठा smc_clc_ipv6_prefix *)((u8 *)prop + माप(*prop));
	max = min_t(u8, prop->ipv6_prefixes_cnt, SMC_CLC_MAX_V6_PREFIX);
	list_क्रम_each_entry(अगरa, &in6_dev->addr_list, अगर_list) अणु
		अगर (ipv6_addr_type(&अगरa->addr) & IPV6_ADDR_LINKLOCAL)
			जारी;
		क्रम (i = 0; i < max; i++) अणु
			अगर (अगरa->prefix_len == ipv6_prfx[i].prefix_len &&
			    ipv6_prefix_equal(&अगरa->addr, &ipv6_prfx[i].prefix,
					      अगरa->prefix_len))
				वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस -ENOENT;
पूर्ण

/* check अगर proposed prefixes match one of our device prefixes */
पूर्णांक smc_clc_prfx_match(काष्ठा socket *clcsock,
		       काष्ठा smc_clc_msg_proposal_prefix *prop)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(clcsock->sk);
	पूर्णांक rc;

	अगर (!dst) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण
	अगर (!dst->dev) अणु
		rc = -ENODEV;
		जाओ out_rel;
	पूर्ण
	rcu_पढ़ो_lock();
	अगर (!prop->ipv6_prefixes_cnt)
		rc = smc_clc_prfx_match4_rcu(dst->dev, prop);
	अन्यथा
		rc = smc_clc_prfx_match6_rcu(dst->dev, prop);
	rcu_पढ़ो_unlock();
out_rel:
	dst_release(dst);
out:
	वापस rc;
पूर्ण

/* Wait क्रम data on the tcp-socket, analyze received data
 * Returns:
 * 0 अगर success and it was not a decline that we received.
 * SMC_CLC_DECL_REPLY अगर decline received क्रम fallback w/o another decl send.
 * clcsock error, -EINTR, -ECONNRESET, -EPROTO otherwise.
 */
पूर्णांक smc_clc_रुको_msg(काष्ठा smc_sock *smc, व्योम *buf, पूर्णांक buflen,
		     u8 expected_type, अचिन्हित दीर्घ समयout)
अणु
	दीर्घ rcvसमयo = smc->clcsock->sk->sk_rcvसमयo;
	काष्ठा sock *clc_sk = smc->clcsock->sk;
	काष्ठा smc_clc_msg_hdr *clcm = buf;
	काष्ठा msghdr msg = अणुशून्य, 0पूर्ण;
	पूर्णांक reason_code = 0;
	काष्ठा kvec vec = अणुbuf, buflenपूर्ण;
	पूर्णांक len, datlen, recvlen;
	bool check_trl = true;
	पूर्णांक krflags;

	/* peek the first few bytes to determine length of data to receive
	 * so we करोn't consume any subsequent CLC message or payload data
	 * in the TCP byte stream
	 */
	/*
	 * Caller must make sure that buflen is no less than
	 * माप(काष्ठा smc_clc_msg_hdr)
	 */
	krflags = MSG_PEEK | MSG_WAITALL;
	clc_sk->sk_rcvसमयo = समयout;
	iov_iter_kvec(&msg.msg_iter, READ, &vec, 1,
			माप(काष्ठा smc_clc_msg_hdr));
	len = sock_recvmsg(smc->clcsock, &msg, krflags);
	अगर (संकेत_pending(current)) अणु
		reason_code = -EINTR;
		clc_sk->sk_err = EINTR;
		smc->sk.sk_err = EINTR;
		जाओ out;
	पूर्ण
	अगर (clc_sk->sk_err) अणु
		reason_code = -clc_sk->sk_err;
		अगर (clc_sk->sk_err == EAGAIN &&
		    expected_type == SMC_CLC_DECLINE)
			clc_sk->sk_err = 0; /* reset क्रम fallback usage */
		अन्यथा
			smc->sk.sk_err = clc_sk->sk_err;
		जाओ out;
	पूर्ण
	अगर (!len) अणु /* peer has perक्रमmed orderly shutकरोwn */
		smc->sk.sk_err = ECONNRESET;
		reason_code = -ECONNRESET;
		जाओ out;
	पूर्ण
	अगर (len < 0) अणु
		अगर (len != -EAGAIN || expected_type != SMC_CLC_DECLINE)
			smc->sk.sk_err = -len;
		reason_code = len;
		जाओ out;
	पूर्ण
	datlen = ntohs(clcm->length);
	अगर ((len < माप(काष्ठा smc_clc_msg_hdr)) ||
	    (clcm->version < SMC_V1) ||
	    ((clcm->type != SMC_CLC_DECLINE) &&
	     (clcm->type != expected_type))) अणु
		smc->sk.sk_err = EPROTO;
		reason_code = -EPROTO;
		जाओ out;
	पूर्ण

	/* receive the complete CLC message */
	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	अगर (datlen > buflen) अणु
		check_trl = false;
		recvlen = buflen;
	पूर्ण अन्यथा अणु
		recvlen = datlen;
	पूर्ण
	iov_iter_kvec(&msg.msg_iter, READ, &vec, 1, recvlen);
	krflags = MSG_WAITALL;
	len = sock_recvmsg(smc->clcsock, &msg, krflags);
	अगर (len < recvlen || !smc_clc_msg_hdr_valid(clcm, check_trl)) अणु
		smc->sk.sk_err = EPROTO;
		reason_code = -EPROTO;
		जाओ out;
	पूर्ण
	datlen -= len;
	जबतक (datlen) अणु
		u8 पंचांगp[SMC_CLC_RECV_BUF_LEN];

		vec.iov_base = &पंचांगp;
		vec.iov_len = SMC_CLC_RECV_BUF_LEN;
		/* receive reमुख्यing proposal message */
		recvlen = datlen > SMC_CLC_RECV_BUF_LEN ?
						SMC_CLC_RECV_BUF_LEN : datlen;
		iov_iter_kvec(&msg.msg_iter, READ, &vec, 1, recvlen);
		len = sock_recvmsg(smc->clcsock, &msg, krflags);
		datlen -= len;
	पूर्ण
	अगर (clcm->type == SMC_CLC_DECLINE) अणु
		काष्ठा smc_clc_msg_decline *dclc;

		dclc = (काष्ठा smc_clc_msg_decline *)clcm;
		reason_code = SMC_CLC_DECL_PEERDECL;
		smc->peer_diagnosis = ntohl(dclc->peer_diagnosis);
		अगर (((काष्ठा smc_clc_msg_decline *)buf)->hdr.typev2 &
						SMC_FIRST_CONTACT_MASK) अणु
			smc->conn.lgr->sync_err = 1;
			smc_lgr_terminate_sched(smc->conn.lgr);
		पूर्ण
	पूर्ण

out:
	clc_sk->sk_rcvसमयo = rcvसमयo;
	वापस reason_code;
पूर्ण

/* send CLC DECLINE message across पूर्णांकernal TCP socket */
पूर्णांक smc_clc_send_decline(काष्ठा smc_sock *smc, u32 peer_diag_info, u8 version)
अणु
	काष्ठा smc_clc_msg_decline dclc;
	काष्ठा msghdr msg;
	काष्ठा kvec vec;
	पूर्णांक len;

	स_रखो(&dclc, 0, माप(dclc));
	स_नकल(dclc.hdr.eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER));
	dclc.hdr.type = SMC_CLC_DECLINE;
	dclc.hdr.length = htons(माप(काष्ठा smc_clc_msg_decline));
	dclc.hdr.version = version;
	dclc.os_type = version == SMC_V1 ? 0 : SMC_CLC_OS_LINUX;
	dclc.hdr.typev2 = (peer_diag_info == SMC_CLC_DECL_SYNCERR) ?
						SMC_FIRST_CONTACT_MASK : 0;
	अगर ((!smc->conn.lgr || !smc->conn.lgr->is_smcd) &&
	    smc_ib_is_valid_local_प्रणालीid())
		स_नकल(dclc.id_क्रम_peer, local_प्रणालीid,
		       माप(local_प्रणालीid));
	dclc.peer_diagnosis = htonl(peer_diag_info);
	स_नकल(dclc.trl.eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER));

	स_रखो(&msg, 0, माप(msg));
	vec.iov_base = &dclc;
	vec.iov_len = माप(काष्ठा smc_clc_msg_decline);
	len = kernel_sendmsg(smc->clcsock, &msg, &vec, 1,
			     माप(काष्ठा smc_clc_msg_decline));
	अगर (len < 0 || len < माप(काष्ठा smc_clc_msg_decline))
		len = -EPROTO;
	वापस len > 0 ? 0 : len;
पूर्ण

/* send CLC PROPOSAL message across पूर्णांकernal TCP socket */
पूर्णांक smc_clc_send_proposal(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_clc_smcd_v2_extension *smcd_v2_ext;
	काष्ठा smc_clc_msg_proposal_prefix *pclc_prfx;
	काष्ठा smc_clc_msg_proposal *pclc_base;
	काष्ठा smc_clc_smcd_gid_chid *gidchids;
	काष्ठा smc_clc_msg_proposal_area *pclc;
	काष्ठा smc_clc_ipv6_prefix *ipv6_prfx;
	काष्ठा smc_clc_v2_extension *v2_ext;
	काष्ठा smc_clc_msg_smcd *pclc_smcd;
	काष्ठा smc_clc_msg_trail *trl;
	पूर्णांक len, i, plen, rc;
	पूर्णांक reason_code = 0;
	काष्ठा kvec vec[8];
	काष्ठा msghdr msg;

	pclc = kzalloc(माप(*pclc), GFP_KERNEL);
	अगर (!pclc)
		वापस -ENOMEM;

	pclc_base = &pclc->pclc_base;
	pclc_smcd = &pclc->pclc_smcd;
	pclc_prfx = &pclc->pclc_prfx;
	ipv6_prfx = pclc->pclc_prfx_ipv6;
	v2_ext = &pclc->pclc_v2_ext;
	smcd_v2_ext = &pclc->pclc_smcd_v2_ext;
	gidchids = pclc->pclc_gidchids;
	trl = &pclc->pclc_trl;

	pclc_base->hdr.version = SMC_V2;
	pclc_base->hdr.typev1 = ini->smc_type_v1;
	pclc_base->hdr.typev2 = ini->smc_type_v2;
	plen = माप(*pclc_base) + माप(*pclc_smcd) + माप(*trl);

	/* retrieve ip prefixes क्रम CLC proposal msg */
	अगर (ini->smc_type_v1 != SMC_TYPE_N) अणु
		rc = smc_clc_prfx_set(smc->clcsock, pclc_prfx, ipv6_prfx);
		अगर (rc) अणु
			अगर (ini->smc_type_v2 == SMC_TYPE_N) अणु
				kमुक्त(pclc);
				वापस SMC_CLC_DECL_CNFERR;
			पूर्ण
			pclc_base->hdr.typev1 = SMC_TYPE_N;
		पूर्ण अन्यथा अणु
			pclc_base->iparea_offset = htons(माप(*pclc_smcd));
			plen += माप(*pclc_prfx) +
					pclc_prfx->ipv6_prefixes_cnt *
					माप(ipv6_prfx[0]);
		पूर्ण
	पूर्ण

	/* build SMC Proposal CLC message */
	स_नकल(pclc_base->hdr.eyecatcher, SMC_EYECATCHER,
	       माप(SMC_EYECATCHER));
	pclc_base->hdr.type = SMC_CLC_PROPOSAL;
	अगर (smcr_indicated(ini->smc_type_v1)) अणु
		/* add SMC-R specअगरics */
		स_नकल(pclc_base->lcl.id_क्रम_peer, local_प्रणालीid,
		       माप(local_प्रणालीid));
		स_नकल(pclc_base->lcl.gid, ini->ib_gid, SMC_GID_SIZE);
		स_नकल(pclc_base->lcl.mac, &ini->ib_dev->mac[ini->ib_port - 1],
		       ETH_ALEN);
	पूर्ण
	अगर (smcd_indicated(ini->smc_type_v1)) अणु
		/* add SMC-D specअगरics */
		अगर (ini->ism_dev[0]) अणु
			pclc_smcd->ism.gid = htonll(ini->ism_dev[0]->local_gid);
			pclc_smcd->ism.chid =
				htons(smc_ism_get_chid(ini->ism_dev[0]));
		पूर्ण
	पूर्ण
	अगर (ini->smc_type_v2 == SMC_TYPE_N) अणु
		pclc_smcd->v2_ext_offset = 0;
	पूर्ण अन्यथा अणु
		u16 v2_ext_offset;
		u8 *eid = शून्य;

		v2_ext_offset = माप(*pclc_smcd) -
			दुरत्वend(काष्ठा smc_clc_msg_smcd, v2_ext_offset);
		अगर (ini->smc_type_v1 != SMC_TYPE_N)
			v2_ext_offset += माप(*pclc_prfx) +
						pclc_prfx->ipv6_prefixes_cnt *
						माप(ipv6_prfx[0]);
		pclc_smcd->v2_ext_offset = htons(v2_ext_offset);
		v2_ext->hdr.eid_cnt = 0;
		v2_ext->hdr.ism_gid_cnt = ini->ism_offered_cnt;
		v2_ext->hdr.flag.release = SMC_RELEASE;
		v2_ext->hdr.flag.seid = 1;
		v2_ext->hdr.smcd_v2_ext_offset = htons(माप(*v2_ext) -
				दुरत्वend(काष्ठा smc_clnt_opts_area_hdr,
					    smcd_v2_ext_offset) +
				v2_ext->hdr.eid_cnt * SMC_MAX_EID_LEN);
		अगर (ini->ism_dev[0])
			smc_ism_get_प्रणाली_eid(ini->ism_dev[0], &eid);
		अन्यथा
			smc_ism_get_प्रणाली_eid(ini->ism_dev[1], &eid);
		अगर (eid)
			स_नकल(smcd_v2_ext->प्रणाली_eid, eid, SMC_MAX_EID_LEN);
		plen += माप(*v2_ext) + माप(*smcd_v2_ext);
		अगर (ini->ism_offered_cnt) अणु
			क्रम (i = 1; i <= ini->ism_offered_cnt; i++) अणु
				gidchids[i - 1].gid =
					htonll(ini->ism_dev[i]->local_gid);
				gidchids[i - 1].chid =
					htons(smc_ism_get_chid(ini->ism_dev[i]));
			पूर्ण
			plen += ini->ism_offered_cnt *
				माप(काष्ठा smc_clc_smcd_gid_chid);
		पूर्ण
	पूर्ण
	pclc_base->hdr.length = htons(plen);
	स_नकल(trl->eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER));

	/* send SMC Proposal CLC message */
	स_रखो(&msg, 0, माप(msg));
	i = 0;
	vec[i].iov_base = pclc_base;
	vec[i++].iov_len = माप(*pclc_base);
	vec[i].iov_base = pclc_smcd;
	vec[i++].iov_len = माप(*pclc_smcd);
	अगर (ini->smc_type_v1 != SMC_TYPE_N) अणु
		vec[i].iov_base = pclc_prfx;
		vec[i++].iov_len = माप(*pclc_prfx);
		अगर (pclc_prfx->ipv6_prefixes_cnt > 0) अणु
			vec[i].iov_base = ipv6_prfx;
			vec[i++].iov_len = pclc_prfx->ipv6_prefixes_cnt *
					   माप(ipv6_prfx[0]);
		पूर्ण
	पूर्ण
	अगर (ini->smc_type_v2 != SMC_TYPE_N) अणु
		vec[i].iov_base = v2_ext;
		vec[i++].iov_len = माप(*v2_ext);
		vec[i].iov_base = smcd_v2_ext;
		vec[i++].iov_len = माप(*smcd_v2_ext);
		अगर (ini->ism_offered_cnt) अणु
			vec[i].iov_base = gidchids;
			vec[i++].iov_len = ini->ism_offered_cnt *
					माप(काष्ठा smc_clc_smcd_gid_chid);
		पूर्ण
	पूर्ण
	vec[i].iov_base = trl;
	vec[i++].iov_len = माप(*trl);
	/* due to the few bytes needed क्रम clc-handshake this cannot block */
	len = kernel_sendmsg(smc->clcsock, &msg, vec, i, plen);
	अगर (len < 0) अणु
		smc->sk.sk_err = smc->clcsock->sk->sk_err;
		reason_code = -smc->sk.sk_err;
	पूर्ण अन्यथा अगर (len < ntohs(pclc_base->hdr.length)) अणु
		reason_code = -ENETUNREACH;
		smc->sk.sk_err = -reason_code;
	पूर्ण

	kमुक्त(pclc);
	वापस reason_code;
पूर्ण

/* build and send CLC CONFIRM / ACCEPT message */
अटल पूर्णांक smc_clc_send_confirm_accept(काष्ठा smc_sock *smc,
				       काष्ठा smc_clc_msg_accept_confirm_v2 *clc_v2,
				       पूर्णांक first_contact, u8 version)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा smc_clc_msg_accept_confirm *clc;
	काष्ठा smc_clc_first_contact_ext fce;
	काष्ठा smc_clc_msg_trail trl;
	काष्ठा kvec vec[3];
	काष्ठा msghdr msg;
	पूर्णांक i, len;

	/* send SMC Confirm CLC msg */
	clc = (काष्ठा smc_clc_msg_accept_confirm *)clc_v2;
	clc->hdr.version = version;	/* SMC version */
	अगर (first_contact)
		clc->hdr.typev2 |= SMC_FIRST_CONTACT_MASK;
	अगर (conn->lgr->is_smcd) अणु
		/* SMC-D specअगरic settings */
		स_नकल(clc->hdr.eyecatcher, SMCD_EYECATCHER,
		       माप(SMCD_EYECATCHER));
		clc->hdr.typev1 = SMC_TYPE_D;
		clc->d0.gid = conn->lgr->smcd->local_gid;
		clc->d0.token = conn->rmb_desc->token;
		clc->d0.dmbe_size = conn->rmbe_size_लघु;
		clc->d0.dmbe_idx = 0;
		स_नकल(&clc->d0.linkid, conn->lgr->id, SMC_LGR_ID_SIZE);
		अगर (version == SMC_V1) अणु
			clc->hdr.length = htons(SMCD_CLC_ACCEPT_CONFIRM_LEN);
		पूर्ण अन्यथा अणु
			u8 *eid = शून्य;

			clc_v2->chid = htons(smc_ism_get_chid(conn->lgr->smcd));
			smc_ism_get_प्रणाली_eid(conn->lgr->smcd, &eid);
			अगर (eid)
				स_नकल(clc_v2->eid, eid, SMC_MAX_EID_LEN);
			len = SMCD_CLC_ACCEPT_CONFIRM_LEN_V2;
			अगर (first_contact)
				smc_clc_fill_fce(&fce, &len);
			clc_v2->hdr.length = htons(len);
		पूर्ण
		स_नकल(trl.eyecatcher, SMCD_EYECATCHER,
		       माप(SMCD_EYECATCHER));
	पूर्ण अन्यथा अणु
		काष्ठा smc_link *link = conn->lnk;

		/* SMC-R specअगरic settings */
		link = conn->lnk;
		स_नकल(clc->hdr.eyecatcher, SMC_EYECATCHER,
		       माप(SMC_EYECATCHER));
		clc->hdr.typev1 = SMC_TYPE_R;
		clc->hdr.length = htons(SMCR_CLC_ACCEPT_CONFIRM_LEN);
		स_नकल(clc->r0.lcl.id_क्रम_peer, local_प्रणालीid,
		       माप(local_प्रणालीid));
		स_नकल(&clc->r0.lcl.gid, link->gid, SMC_GID_SIZE);
		स_नकल(&clc->r0.lcl.mac, &link->smcibdev->mac[link->ibport - 1],
		       ETH_ALEN);
		hton24(clc->r0.qpn, link->roce_qp->qp_num);
		clc->r0.rmb_rkey =
			htonl(conn->rmb_desc->mr_rx[link->link_idx]->rkey);
		clc->r0.rmbe_idx = 1; /* क्रम now: 1 RMB = 1 RMBE */
		clc->r0.rmbe_alert_token = htonl(conn->alert_token_local);
		चयन (clc->hdr.type) अणु
		हाल SMC_CLC_ACCEPT:
			clc->r0.qp_mtu = link->path_mtu;
			अवरोध;
		हाल SMC_CLC_CONFIRM:
			clc->r0.qp_mtu = min(link->path_mtu, link->peer_mtu);
			अवरोध;
		पूर्ण
		clc->r0.rmbe_size = conn->rmbe_size_लघु;
		clc->r0.rmb_dma_addr = cpu_to_be64((u64)sg_dma_address
				(conn->rmb_desc->sgt[link->link_idx].sgl));
		hton24(clc->r0.psn, link->psn_initial);
		स_नकल(trl.eyecatcher, SMC_EYECATCHER, माप(SMC_EYECATCHER));
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	i = 0;
	vec[i].iov_base = clc_v2;
	अगर (version > SMC_V1)
		vec[i++].iov_len = SMCD_CLC_ACCEPT_CONFIRM_LEN_V2 - माप(trl);
	अन्यथा
		vec[i++].iov_len = (clc->hdr.typev1 == SMC_TYPE_D ?
						SMCD_CLC_ACCEPT_CONFIRM_LEN :
						SMCR_CLC_ACCEPT_CONFIRM_LEN) -
				   माप(trl);
	अगर (version > SMC_V1 && first_contact) अणु
		vec[i].iov_base = &fce;
		vec[i++].iov_len = माप(fce);
	पूर्ण
	vec[i].iov_base = &trl;
	vec[i++].iov_len = माप(trl);
	वापस kernel_sendmsg(smc->clcsock, &msg, vec, 1,
			      ntohs(clc->hdr.length));
पूर्ण

/* send CLC CONFIRM message across पूर्णांकernal TCP socket */
पूर्णांक smc_clc_send_confirm(काष्ठा smc_sock *smc, bool clnt_first_contact,
			 u8 version)
अणु
	काष्ठा smc_clc_msg_accept_confirm_v2 cclc_v2;
	पूर्णांक reason_code = 0;
	पूर्णांक len;

	/* send SMC Confirm CLC msg */
	स_रखो(&cclc_v2, 0, माप(cclc_v2));
	cclc_v2.hdr.type = SMC_CLC_CONFIRM;
	len = smc_clc_send_confirm_accept(smc, &cclc_v2, clnt_first_contact,
					  version);
	अगर (len < ntohs(cclc_v2.hdr.length)) अणु
		अगर (len >= 0) अणु
			reason_code = -ENETUNREACH;
			smc->sk.sk_err = -reason_code;
		पूर्ण अन्यथा अणु
			smc->sk.sk_err = smc->clcsock->sk->sk_err;
			reason_code = -smc->sk.sk_err;
		पूर्ण
	पूर्ण
	वापस reason_code;
पूर्ण

/* send CLC ACCEPT message across पूर्णांकernal TCP socket */
पूर्णांक smc_clc_send_accept(काष्ठा smc_sock *new_smc, bool srv_first_contact,
			u8 version)
अणु
	काष्ठा smc_clc_msg_accept_confirm_v2 aclc_v2;
	पूर्णांक len;

	स_रखो(&aclc_v2, 0, माप(aclc_v2));
	aclc_v2.hdr.type = SMC_CLC_ACCEPT;
	len = smc_clc_send_confirm_accept(new_smc, &aclc_v2, srv_first_contact,
					  version);
	अगर (len < ntohs(aclc_v2.hdr.length))
		len = len >= 0 ? -EPROTO : -new_smc->clcsock->sk->sk_err;

	वापस len > 0 ? 0 : len;
पूर्ण

व्योम smc_clc_get_hostname(u8 **host)
अणु
	*host = &smc_hostname[0];
पूर्ण

व्योम __init smc_clc_init(व्योम)
अणु
	काष्ठा new_utsname *u;

	स_रखो(smc_hostname, _S, माप(smc_hostname)); /* ASCII blanks */
	u = utsname();
	स_नकल(smc_hostname, u->nodename,
	       min_t(माप_प्रकार, म_माप(u->nodename), माप(smc_hostname)));
पूर्ण
