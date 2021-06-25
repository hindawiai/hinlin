<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2002, 2004
 * Copyright (c) 2002 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Sysctl related पूर्णांकerfaces क्रम SCTP.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Mingqin Liu           <liuming@us.ibm.com>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Ardelle Fan           <ardelle.fan@पूर्णांकel.com>
 *    Ryan Layer            <rmlayer@us.ibm.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <net/sctp/काष्ठाs.h>
#समावेश <net/sctp/sctp.h>
#समावेश <linux/sysctl.h>

अटल पूर्णांक समयr_max = 86400000; /* ms in one day */
अटल पूर्णांक sack_समयr_min = 1;
अटल पूर्णांक sack_समयr_max = 500;
अटल पूर्णांक addr_scope_max = SCTP_SCOPE_POLICY_MAX;
अटल पूर्णांक rwnd_scale_max = 16;
अटल पूर्णांक rto_alpha_min = 0;
अटल पूर्णांक rto_beta_min = 0;
अटल पूर्णांक rto_alpha_max = 1000;
अटल पूर्णांक rto_beta_max = 1000;
अटल पूर्णांक pf_expose_max = SCTP_PF_EXPOSE_MAX;
अटल पूर्णांक ps_retrans_max = SCTP_PS_RETRANS_MAX;
अटल पूर्णांक udp_port_max = 65535;

अटल अचिन्हित दीर्घ max_स्वतःबंद_min = 0;
अटल अचिन्हित दीर्घ max_स्वतःबंद_max =
	(MAX_SCHEDULE_TIMEOUT / HZ > अच_पूर्णांक_उच्च)
	? अच_पूर्णांक_उच्च : MAX_SCHEDULE_TIMEOUT / HZ;

अटल पूर्णांक proc_sctp_करो_hmac_alg(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक proc_sctp_करो_rto_min(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक proc_sctp_करो_rto_max(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
				माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक proc_sctp_करो_udp_port(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
				 माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक proc_sctp_करो_alpha_beta(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक proc_sctp_करो_auth(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

अटल काष्ठा ctl_table sctp_table[] = अणु
	अणु
		.procname	= "sctp_mem",
		.data		= &sysctl_sctp_mem,
		.maxlen		= माप(sysctl_sctp_mem),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax
	पूर्ण,
	अणु
		.procname	= "sctp_rmem",
		.data		= &sysctl_sctp_rmem,
		.maxlen		= माप(sysctl_sctp_rmem),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sctp_wmem",
		.data		= &sysctl_sctp_wmem,
		.maxlen		= माप(sysctl_sctp_wmem),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,

	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा ctl_table sctp_net_table[] = अणु
	अणु
		.procname	= "rto_initial",
		.data		= &init_net.sctp.rto_initial,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ONE,
		.extra2         = &समयr_max
	पूर्ण,
	अणु
		.procname	= "rto_min",
		.data		= &init_net.sctp.rto_min,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_rto_min,
		.extra1         = SYSCTL_ONE,
		.extra2         = &init_net.sctp.rto_max
	पूर्ण,
	अणु
		.procname	= "rto_max",
		.data		= &init_net.sctp.rto_max,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_rto_max,
		.extra1         = &init_net.sctp.rto_min,
		.extra2         = &समयr_max
	पूर्ण,
	अणु
		.procname	= "rto_alpha_exp_divisor",
		.data		= &init_net.sctp.rto_alpha,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_alpha_beta,
		.extra1		= &rto_alpha_min,
		.extra2		= &rto_alpha_max,
	पूर्ण,
	अणु
		.procname	= "rto_beta_exp_divisor",
		.data		= &init_net.sctp.rto_beta,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_alpha_beta,
		.extra1		= &rto_beta_min,
		.extra2		= &rto_beta_max,
	पूर्ण,
	अणु
		.procname	= "max_burst",
		.data		= &init_net.sctp.max_burst,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "cookie_preserve_enable",
		.data		= &init_net.sctp.cookie_preserve_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cookie_hmac_alg",
		.data		= &init_net.sctp.sctp_hmac_alg,
		.maxlen		= 8,
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_hmac_alg,
	पूर्ण,
	अणु
		.procname	= "valid_cookie_life",
		.data		= &init_net.sctp.valid_cookie_lअगरe,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ONE,
		.extra2         = &समयr_max
	पूर्ण,
	अणु
		.procname	= "sack_timeout",
		.data		= &init_net.sctp.sack_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = &sack_समयr_min,
		.extra2         = &sack_समयr_max,
	पूर्ण,
	अणु
		.procname	= "hb_interval",
		.data		= &init_net.sctp.hb_पूर्णांकerval,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ONE,
		.extra2         = &समयr_max
	पूर्ण,
	अणु
		.procname	= "association_max_retrans",
		.data		= &init_net.sctp.max_retrans_association,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "path_max_retrans",
		.data		= &init_net.sctp.max_retrans_path,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "max_init_retransmits",
		.data		= &init_net.sctp.max_retrans_init,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname	= "pf_retrans",
		.data		= &init_net.sctp.pf_retrans,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &init_net.sctp.ps_retrans,
	पूर्ण,
	अणु
		.procname	= "ps_retrans",
		.data		= &init_net.sctp.ps_retrans,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &init_net.sctp.pf_retrans,
		.extra2		= &ps_retrans_max,
	पूर्ण,
	अणु
		.procname	= "sndbuf_policy",
		.data		= &init_net.sctp.sndbuf_policy,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "rcvbuf_policy",
		.data		= &init_net.sctp.rcvbuf_policy,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "default_auto_asconf",
		.data		= &init_net.sctp.शेष_स्वतः_asconf,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "addip_enable",
		.data		= &init_net.sctp.addip_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "addip_noauth_enable",
		.data		= &init_net.sctp.addip_noauth,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "prsctp_enable",
		.data		= &init_net.sctp.prsctp_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "reconf_enable",
		.data		= &init_net.sctp.reconf_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "auth_enable",
		.data		= &init_net.sctp.auth_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_auth,
	पूर्ण,
	अणु
		.procname	= "intl_enable",
		.data		= &init_net.sctp.पूर्णांकl_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "ecn_enable",
		.data		= &init_net.sctp.ecn_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "udp_port",
		.data		= &init_net.sctp.udp_port,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_sctp_करो_udp_port,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &udp_port_max,
	पूर्ण,
	अणु
		.procname	= "encap_port",
		.data		= &init_net.sctp.encap_port,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &udp_port_max,
	पूर्ण,
	अणु
		.procname	= "addr_scope_policy",
		.data		= &init_net.sctp.scope_policy,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &addr_scope_max,
	पूर्ण,
	अणु
		.procname	= "rwnd_update_shift",
		.data		= &init_net.sctp.rwnd_upd_shअगरt,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= &proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= &rwnd_scale_max,
	पूर्ण,
	अणु
		.procname	= "max_autoclose",
		.data		= &init_net.sctp.max_स्वतःबंद,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= &proc_करोuदीर्घvec_minmax,
		.extra1		= &max_स्वतःबंद_min,
		.extra2		= &max_स्वतःबंद_max,
	पूर्ण,
	अणु
		.procname	= "pf_enable",
		.data		= &init_net.sctp.pf_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "pf_expose",
		.data		= &init_net.sctp.pf_expose,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &pf_expose_max,
	पूर्ण,

	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक proc_sctp_करो_hmac_alg(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा ctl_table tbl;
	bool changed = false;
	अक्षर *none = "none";
	अक्षर पंचांगp[8] = अणु0पूर्ण;
	पूर्णांक ret;

	स_रखो(&tbl, 0, माप(काष्ठा ctl_table));

	अगर (ग_लिखो) अणु
		tbl.data = पंचांगp;
		tbl.maxlen = माप(पंचांगp);
	पूर्ण अन्यथा अणु
		tbl.data = net->sctp.sctp_hmac_alg ? : none;
		tbl.maxlen = म_माप(tbl.data);
	पूर्ण

	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0) अणु
#अगर_घोषित CONFIG_CRYPTO_MD5
		अगर (!म_भेदन(पंचांगp, "md5", 3)) अणु
			net->sctp.sctp_hmac_alg = "md5";
			changed = true;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_SHA1
		अगर (!म_भेदन(पंचांगp, "sha1", 4)) अणु
			net->sctp.sctp_hmac_alg = "sha1";
			changed = true;
		पूर्ण
#पूर्ण_अगर
		अगर (!म_भेदन(पंचांगp, "none", 4)) अणु
			net->sctp.sctp_hmac_alg = शून्य;
			changed = true;
		पूर्ण
		अगर (!changed)
			ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_sctp_करो_rto_min(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	अचिन्हित पूर्णांक min = *(अचिन्हित पूर्णांक *) ctl->extra1;
	अचिन्हित पूर्णांक max = *(अचिन्हित पूर्णांक *) ctl->extra2;
	काष्ठा ctl_table tbl;
	पूर्णांक ret, new_value;

	स_रखो(&tbl, 0, माप(काष्ठा ctl_table));
	tbl.maxlen = माप(अचिन्हित पूर्णांक);

	अगर (ग_लिखो)
		tbl.data = &new_value;
	अन्यथा
		tbl.data = &net->sctp.rto_min;

	ret = proc_करोपूर्णांकvec(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0) अणु
		अगर (new_value > max || new_value < min)
			वापस -EINVAL;

		net->sctp.rto_min = new_value;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_sctp_करो_rto_max(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	अचिन्हित पूर्णांक min = *(अचिन्हित पूर्णांक *) ctl->extra1;
	अचिन्हित पूर्णांक max = *(अचिन्हित पूर्णांक *) ctl->extra2;
	काष्ठा ctl_table tbl;
	पूर्णांक ret, new_value;

	स_रखो(&tbl, 0, माप(काष्ठा ctl_table));
	tbl.maxlen = माप(अचिन्हित पूर्णांक);

	अगर (ग_लिखो)
		tbl.data = &new_value;
	अन्यथा
		tbl.data = &net->sctp.rto_max;

	ret = proc_करोपूर्णांकvec(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0) अणु
		अगर (new_value > max || new_value < min)
			वापस -EINVAL;

		net->sctp.rto_max = new_value;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_sctp_करो_alpha_beta(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (ग_लिखो)
		pr_warn_once("Changing rto_alpha or rto_beta may lead to "
			     "suboptimal rtt/srtt estimations!\n");

	वापस proc_करोपूर्णांकvec_minmax(ctl, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक proc_sctp_करो_auth(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा ctl_table tbl;
	पूर्णांक new_value, ret;

	स_रखो(&tbl, 0, माप(काष्ठा ctl_table));
	tbl.maxlen = माप(अचिन्हित पूर्णांक);

	अगर (ग_लिखो)
		tbl.data = &new_value;
	अन्यथा
		tbl.data = &net->sctp.auth_enable;

	ret = proc_करोपूर्णांकvec(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0) अणु
		काष्ठा sock *sk = net->sctp.ctl_sock;

		net->sctp.auth_enable = new_value;
		/* Update the value in the control socket */
		lock_sock(sk);
		sctp_sk(sk)->ep->auth_enable = new_value;
		release_sock(sk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_sctp_करो_udp_port(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	अचिन्हित पूर्णांक min = *(अचिन्हित पूर्णांक *)ctl->extra1;
	अचिन्हित पूर्णांक max = *(अचिन्हित पूर्णांक *)ctl->extra2;
	काष्ठा ctl_table tbl;
	पूर्णांक ret, new_value;

	स_रखो(&tbl, 0, माप(काष्ठा ctl_table));
	tbl.maxlen = माप(अचिन्हित पूर्णांक);

	अगर (ग_लिखो)
		tbl.data = &new_value;
	अन्यथा
		tbl.data = &net->sctp.udp_port;

	ret = proc_करोपूर्णांकvec(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0) अणु
		काष्ठा sock *sk = net->sctp.ctl_sock;

		अगर (new_value > max || new_value < min)
			वापस -EINVAL;

		net->sctp.udp_port = new_value;
		sctp_udp_sock_stop(net);
		अगर (new_value) अणु
			ret = sctp_udp_sock_start(net);
			अगर (ret)
				net->sctp.udp_port = 0;
		पूर्ण

		/* Update the value in the control socket */
		lock_sock(sk);
		sctp_sk(sk)->udp_port = htons(net->sctp.udp_port);
		release_sock(sk);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक sctp_sysctl_net_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	पूर्णांक i;

	table = kmemdup(sctp_net_table, माप(sctp_net_table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	क्रम (i = 0; table[i].data; i++)
		table[i].data += (अक्षर *)(&net->sctp) - (अक्षर *)&init_net.sctp;

	net->sctp.sysctl_header = रेजिस्टर_net_sysctl(net, "net/sctp", table);
	अगर (net->sctp.sysctl_header == शून्य) अणु
		kमुक्त(table);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम sctp_sysctl_net_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->sctp.sysctl_header->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->sctp.sysctl_header);
	kमुक्त(table);
पूर्ण

अटल काष्ठा ctl_table_header *sctp_sysctl_header;

/* Sysctl registration.  */
व्योम sctp_sysctl_रेजिस्टर(व्योम)
अणु
	sctp_sysctl_header = रेजिस्टर_net_sysctl(&init_net, "net/sctp", sctp_table);
पूर्ण

/* Sysctl deregistration.  */
व्योम sctp_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(sctp_sysctl_header);
पूर्ण
