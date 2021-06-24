<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * common LSM auditing functions
 *
 * Based on code written क्रम SELinux by :
 *			Stephen Smalley, <sds@tycho.nsa.gov>
 * 			James Morris <jmorris@redhat.com>
 * Author : Etienne Basset, <etienne.basset@ensta.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <net/sock.h>
#समावेश <linux/un.h>
#समावेश <net/af_unix.h>
#समावेश <linux/audit.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/dccp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/lsm_audit.h>
#समावेश <linux/security.h>

/**
 * ipv4_skb_to_auditdata : fill auditdata from skb
 * @skb : the skb
 * @ad : the audit data to fill
 * @proto : the layer 4 protocol
 *
 * वापस  0 on success
 */
पूर्णांक ipv4_skb_to_auditdata(काष्ठा sk_buff *skb,
		काष्ठा common_audit_data *ad, u8 *proto)
अणु
	पूर्णांक ret = 0;
	काष्ठा iphdr *ih;

	ih = ip_hdr(skb);
	अगर (ih == शून्य)
		वापस -EINVAL;

	ad->u.net->v4info.saddr = ih->saddr;
	ad->u.net->v4info.daddr = ih->daddr;

	अगर (proto)
		*proto = ih->protocol;
	/* non initial fragment */
	अगर (ntohs(ih->frag_off) & IP_OFFSET)
		वापस 0;

	चयन (ih->protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr *th = tcp_hdr(skb);
		अगर (th == शून्य)
			अवरोध;

		ad->u.net->sport = th->source;
		ad->u.net->dport = th->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_UDP: अणु
		काष्ठा udphdr *uh = udp_hdr(skb);
		अगर (uh == शून्य)
			अवरोध;

		ad->u.net->sport = uh->source;
		ad->u.net->dport = uh->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_DCCP: अणु
		काष्ठा dccp_hdr *dh = dccp_hdr(skb);
		अगर (dh == शून्य)
			अवरोध;

		ad->u.net->sport = dh->dccph_sport;
		ad->u.net->dport = dh->dccph_dport;
		अवरोध;
	पूर्ण
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctphdr *sh = sctp_hdr(skb);
		अगर (sh == शून्य)
			अवरोध;
		ad->u.net->sport = sh->source;
		ad->u.net->dport = sh->dest;
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * ipv6_skb_to_auditdata : fill auditdata from skb
 * @skb : the skb
 * @ad : the audit data to fill
 * @proto : the layer 4 protocol
 *
 * वापस  0 on success
 */
पूर्णांक ipv6_skb_to_auditdata(काष्ठा sk_buff *skb,
		काष्ठा common_audit_data *ad, u8 *proto)
अणु
	पूर्णांक offset, ret = 0;
	काष्ठा ipv6hdr *ip6;
	u8 nexthdr;
	__be16 frag_off;

	ip6 = ipv6_hdr(skb);
	अगर (ip6 == शून्य)
		वापस -EINVAL;
	ad->u.net->v6info.saddr = ip6->saddr;
	ad->u.net->v6info.daddr = ip6->daddr;
	ret = 0;
	/* IPv6 can have several extension header beक्रमe the Transport header
	 * skip them */
	offset = skb_network_offset(skb);
	offset += माप(*ip6);
	nexthdr = ip6->nexthdr;
	offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);
	अगर (offset < 0)
		वापस 0;
	अगर (proto)
		*proto = nexthdr;
	चयन (nexthdr) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _tcph, *th;

		th = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
		अगर (th == शून्य)
			अवरोध;

		ad->u.net->sport = th->source;
		ad->u.net->dport = th->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_UDP: अणु
		काष्ठा udphdr _udph, *uh;

		uh = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
		अगर (uh == शून्य)
			अवरोध;

		ad->u.net->sport = uh->source;
		ad->u.net->dport = uh->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_DCCP: अणु
		काष्ठा dccp_hdr _dccph, *dh;

		dh = skb_header_poपूर्णांकer(skb, offset, माप(_dccph), &_dccph);
		अगर (dh == शून्य)
			अवरोध;

		ad->u.net->sport = dh->dccph_sport;
		ad->u.net->dport = dh->dccph_dport;
		अवरोध;
	पूर्ण
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctphdr _sctph, *sh;

		sh = skb_header_poपूर्णांकer(skb, offset, माप(_sctph), &_sctph);
		अगर (sh == शून्य)
			अवरोध;
		ad->u.net->sport = sh->source;
		ad->u.net->dport = sh->dest;
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत व्योम prपूर्णांक_ipv6_addr(काष्ठा audit_buffer *ab,
				   स्थिर काष्ठा in6_addr *addr, __be16 port,
				   अक्षर *name1, अक्षर *name2)
अणु
	अगर (!ipv6_addr_any(addr))
		audit_log_क्रमmat(ab, " %s=%pI6c", name1, addr);
	अगर (port)
		audit_log_क्रमmat(ab, " %s=%d", name2, ntohs(port));
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_ipv4_addr(काष्ठा audit_buffer *ab, __be32 addr,
				   __be16 port, अक्षर *name1, अक्षर *name2)
अणु
	अगर (addr)
		audit_log_क्रमmat(ab, " %s=%pI4", name1, &addr);
	अगर (port)
		audit_log_क्रमmat(ab, " %s=%d", name2, ntohs(port));
पूर्ण

/**
 * dump_common_audit_data - helper to dump common audit data
 * @a : common audit data
 *
 */
अटल व्योम dump_common_audit_data(काष्ठा audit_buffer *ab,
				   काष्ठा common_audit_data *a)
अणु
	अक्षर comm[माप(current->comm)];

	/*
	 * To keep stack sizes in check क्रमce programers to notice अगर they
	 * start making this जोड़ too large!  See काष्ठा lsm_network_audit
	 * as an example of how to deal with large data.
	 */
	BUILD_BUG_ON(माप(a->u) > माप(व्योम *)*2);

	audit_log_क्रमmat(ab, " pid=%d comm=", task_tgid_nr(current));
	audit_log_untrustedstring(ab, स_नकल(comm, current->comm, माप(comm)));

	चयन (a->type) अणु
	हाल LSM_AUDIT_DATA_NONE:
		वापस;
	हाल LSM_AUDIT_DATA_IPC:
		audit_log_क्रमmat(ab, " key=%d ", a->u.ipc_id);
		अवरोध;
	हाल LSM_AUDIT_DATA_CAP:
		audit_log_क्रमmat(ab, " capability=%d ", a->u.cap);
		अवरोध;
	हाल LSM_AUDIT_DATA_PATH: अणु
		काष्ठा inode *inode;

		audit_log_d_path(ab, " path=", &a->u.path);

		inode = d_backing_inode(a->u.path.dentry);
		अगर (inode) अणु
			audit_log_क्रमmat(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_खाता: अणु
		काष्ठा inode *inode;

		audit_log_d_path(ab, " path=", &a->u.file->f_path);

		inode = file_inode(a->u.file);
		अगर (inode) अणु
			audit_log_क्रमmat(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_IOCTL_OP: अणु
		काष्ठा inode *inode;

		audit_log_d_path(ab, " path=", &a->u.op->path);

		inode = a->u.op->path.dentry->d_inode;
		अगर (inode) अणु
			audit_log_क्रमmat(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
		पूर्ण

		audit_log_क्रमmat(ab, " ioctlcmd=0x%hx", a->u.op->cmd);
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_DENTRY: अणु
		काष्ठा inode *inode;

		audit_log_क्रमmat(ab, " name=");
		spin_lock(&a->u.dentry->d_lock);
		audit_log_untrustedstring(ab, a->u.dentry->d_name.name);
		spin_unlock(&a->u.dentry->d_lock);

		inode = d_backing_inode(a->u.dentry);
		अगर (inode) अणु
			audit_log_क्रमmat(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_INODE: अणु
		काष्ठा dentry *dentry;
		काष्ठा inode *inode;

		rcu_पढ़ो_lock();
		inode = a->u.inode;
		dentry = d_find_alias_rcu(inode);
		अगर (dentry) अणु
			audit_log_क्रमmat(ab, " name=");
			spin_lock(&dentry->d_lock);
			audit_log_untrustedstring(ab, dentry->d_name.name);
			spin_unlock(&dentry->d_lock);
		पूर्ण
		audit_log_क्रमmat(ab, " dev=");
		audit_log_untrustedstring(ab, inode->i_sb->s_id);
		audit_log_क्रमmat(ab, " ino=%lu", inode->i_ino);
		rcu_पढ़ो_unlock();
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_TASK: अणु
		काष्ठा task_काष्ठा *tsk = a->u.tsk;
		अगर (tsk) अणु
			pid_t pid = task_tgid_nr(tsk);
			अगर (pid) अणु
				अक्षर comm[माप(tsk->comm)];
				audit_log_क्रमmat(ab, " opid=%d ocomm=", pid);
				audit_log_untrustedstring(ab,
				    स_नकल(comm, tsk->comm, माप(comm)));
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_NET:
		अगर (a->u.net->sk) अणु
			स्थिर काष्ठा sock *sk = a->u.net->sk;
			काष्ठा unix_sock *u;
			काष्ठा unix_address *addr;
			पूर्णांक len = 0;
			अक्षर *p = शून्य;

			चयन (sk->sk_family) अणु
			हाल AF_INET: अणु
				काष्ठा inet_sock *inet = inet_sk(sk);

				prपूर्णांक_ipv4_addr(ab, inet->inet_rcv_saddr,
						inet->inet_sport,
						"laddr", "lport");
				prपूर्णांक_ipv4_addr(ab, inet->inet_daddr,
						inet->inet_dport,
						"faddr", "fport");
				अवरोध;
			पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
			हाल AF_INET6: अणु
				काष्ठा inet_sock *inet = inet_sk(sk);

				prपूर्णांक_ipv6_addr(ab, &sk->sk_v6_rcv_saddr,
						inet->inet_sport,
						"laddr", "lport");
				prपूर्णांक_ipv6_addr(ab, &sk->sk_v6_daddr,
						inet->inet_dport,
						"faddr", "fport");
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			हाल AF_UNIX:
				u = unix_sk(sk);
				addr = smp_load_acquire(&u->addr);
				अगर (!addr)
					अवरोध;
				अगर (u->path.dentry) अणु
					audit_log_d_path(ab, " path=", &u->path);
					अवरोध;
				पूर्ण
				len = addr->len-माप(लघु);
				p = &addr->name->sun_path[0];
				audit_log_क्रमmat(ab, " path=");
				अगर (*p)
					audit_log_untrustedstring(ab, p);
				अन्यथा
					audit_log_n_hex(ab, p, len);
				अवरोध;
			पूर्ण
		पूर्ण

		चयन (a->u.net->family) अणु
		हाल AF_INET:
			prपूर्णांक_ipv4_addr(ab, a->u.net->v4info.saddr,
					a->u.net->sport,
					"saddr", "src");
			prपूर्णांक_ipv4_addr(ab, a->u.net->v4info.daddr,
					a->u.net->dport,
					"daddr", "dest");
			अवरोध;
		हाल AF_INET6:
			prपूर्णांक_ipv6_addr(ab, &a->u.net->v6info.saddr,
					a->u.net->sport,
					"saddr", "src");
			prपूर्णांक_ipv6_addr(ab, &a->u.net->v6info.daddr,
					a->u.net->dport,
					"daddr", "dest");
			अवरोध;
		पूर्ण
		अगर (a->u.net->netअगर > 0) अणु
			काष्ठा net_device *dev;

			/* NOTE: we always use init's namespace */
			dev = dev_get_by_index(&init_net, a->u.net->netअगर);
			अगर (dev) अणु
				audit_log_क्रमmat(ab, " netif=%s", dev->name);
				dev_put(dev);
			पूर्ण
		पूर्ण
		अवरोध;
#अगर_घोषित CONFIG_KEYS
	हाल LSM_AUDIT_DATA_KEY:
		audit_log_क्रमmat(ab, " key_serial=%u", a->u.key_काष्ठा.key);
		अगर (a->u.key_काष्ठा.key_desc) अणु
			audit_log_क्रमmat(ab, " key_desc=");
			audit_log_untrustedstring(ab, a->u.key_काष्ठा.key_desc);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल LSM_AUDIT_DATA_KMOD:
		audit_log_क्रमmat(ab, " kmod=");
		audit_log_untrustedstring(ab, a->u.kmod_name);
		अवरोध;
	हाल LSM_AUDIT_DATA_IBPKEY: अणु
		काष्ठा in6_addr sbn_pfx;

		स_रखो(&sbn_pfx.s6_addr, 0,
		       माप(sbn_pfx.s6_addr));
		स_नकल(&sbn_pfx.s6_addr, &a->u.ibpkey->subnet_prefix,
		       माप(a->u.ibpkey->subnet_prefix));
		audit_log_क्रमmat(ab, " pkey=0x%x subnet_prefix=%pI6c",
				 a->u.ibpkey->pkey, &sbn_pfx);
		अवरोध;
	पूर्ण
	हाल LSM_AUDIT_DATA_IBENDPORT:
		audit_log_क्रमmat(ab, " device=%s port_num=%u",
				 a->u.ibendport->dev_name,
				 a->u.ibendport->port);
		अवरोध;
	हाल LSM_AUDIT_DATA_LOCKDOWN:
		audit_log_क्रमmat(ab, " lockdown_reason=\"%s\"",
				 lockकरोwn_reasons[a->u.reason]);
		अवरोध;
	पूर्ण /* चयन (a->type) */
पूर्ण

/**
 * common_lsm_audit - generic LSM auditing function
 * @a:  auxiliary audit data
 * @pre_audit: lsm-specअगरic pre-audit callback
 * @post_audit: lsm-specअगरic post-audit callback
 *
 * setup the audit buffer क्रम common security inक्रमmation
 * uses callback to prपूर्णांक LSM specअगरic inक्रमmation
 */
व्योम common_lsm_audit(काष्ठा common_audit_data *a,
	व्योम (*pre_audit)(काष्ठा audit_buffer *, व्योम *),
	व्योम (*post_audit)(काष्ठा audit_buffer *, व्योम *))
अणु
	काष्ठा audit_buffer *ab;

	अगर (a == शून्य)
		वापस;
	/* we use GFP_ATOMIC so we won't sleep */
	ab = audit_log_start(audit_context(), GFP_ATOMIC | __GFP_NOWARN,
			     AUDIT_AVC);

	अगर (ab == शून्य)
		वापस;

	अगर (pre_audit)
		pre_audit(ab, a);

	dump_common_audit_data(ab, a);

	अगर (post_audit)
		post_audit(ab, a);

	audit_log_end(ab);
पूर्ण
