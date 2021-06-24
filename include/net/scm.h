<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NET_SCM_H
#घोषणा __LINUX_NET_SCM_H

#समावेश <linux/सीमा.स>
#समावेश <linux/net.h>
#समावेश <linux/cred.h>
#समावेश <linux/security.h>
#समावेश <linux/pid.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/sched/संकेत.स>

/* Well, we should have at least one descriptor खोलो
 * to accept passed FDs 8)
 */
#घोषणा SCM_MAX_FD	253

काष्ठा scm_creds अणु
	u32	pid;
	kuid_t	uid;
	kgid_t	gid;
पूर्ण;

काष्ठा scm_fp_list अणु
	लघु			count;
	लघु			max;
	काष्ठा user_काष्ठा	*user;
	काष्ठा file		*fp[SCM_MAX_FD];
पूर्ण;

काष्ठा scm_cookie अणु
	काष्ठा pid		*pid;		/* Skb credentials */
	काष्ठा scm_fp_list	*fp;		/* Passed files		*/
	काष्ठा scm_creds	creds;		/* Skb credentials	*/
#अगर_घोषित CONFIG_SECURITY_NETWORK
	u32			secid;		/* Passed security ID 	*/
#पूर्ण_अगर
पूर्ण;

व्योम scm_detach_fds(काष्ठा msghdr *msg, काष्ठा scm_cookie *scm);
व्योम scm_detach_fds_compat(काष्ठा msghdr *msg, काष्ठा scm_cookie *scm);
पूर्णांक __scm_send(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा scm_cookie *scm);
व्योम __scm_destroy(काष्ठा scm_cookie *scm);
काष्ठा scm_fp_list *scm_fp_dup(काष्ठा scm_fp_list *fpl);

#अगर_घोषित CONFIG_SECURITY_NETWORK
अटल __अंतरभूत__ व्योम unix_get_peersec_dgram(काष्ठा socket *sock, काष्ठा scm_cookie *scm)
अणु
	security_socket_getpeersec_dgram(sock, शून्य, &scm->secid);
पूर्ण
#अन्यथा
अटल __अंतरभूत__ व्योम unix_get_peersec_dgram(काष्ठा socket *sock, काष्ठा scm_cookie *scm)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

अटल __अंतरभूत__ व्योम scm_set_cred(काष्ठा scm_cookie *scm,
				    काष्ठा pid *pid, kuid_t uid, kgid_t gid)
अणु
	scm->pid  = get_pid(pid);
	scm->creds.pid = pid_vnr(pid);
	scm->creds.uid = uid;
	scm->creds.gid = gid;
पूर्ण

अटल __अंतरभूत__ व्योम scm_destroy_cred(काष्ठा scm_cookie *scm)
अणु
	put_pid(scm->pid);
	scm->pid  = शून्य;
पूर्ण

अटल __अंतरभूत__ व्योम scm_destroy(काष्ठा scm_cookie *scm)
अणु
	scm_destroy_cred(scm);
	अगर (scm->fp)
		__scm_destroy(scm);
पूर्ण

अटल __अंतरभूत__ पूर्णांक scm_send(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       काष्ठा scm_cookie *scm, bool क्रमcecreds)
अणु
	स_रखो(scm, 0, माप(*scm));
	scm->creds.uid = INVALID_UID;
	scm->creds.gid = INVALID_GID;
	अगर (क्रमcecreds)
		scm_set_cred(scm, task_tgid(current), current_uid(), current_gid());
	unix_get_peersec_dgram(sock, scm);
	अगर (msg->msg_controllen <= 0)
		वापस 0;
	वापस __scm_send(sock, msg, scm);
पूर्ण

#अगर_घोषित CONFIG_SECURITY_NETWORK
अटल अंतरभूत व्योम scm_passec(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा scm_cookie *scm)
अणु
	अक्षर *secdata;
	u32 seclen;
	पूर्णांक err;

	अगर (test_bit(SOCK_PASSSEC, &sock->flags)) अणु
		err = security_secid_to_secctx(scm->secid, &secdata, &seclen);

		अगर (!err) अणु
			put_cmsg(msg, SOL_SOCKET, SCM_SECURITY, seclen, secdata);
			security_release_secctx(secdata, seclen);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम scm_passec(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा scm_cookie *scm)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

अटल __अंतरभूत__ व्योम scm_recv(काष्ठा socket *sock, काष्ठा msghdr *msg,
				काष्ठा scm_cookie *scm, पूर्णांक flags)
अणु
	अगर (!msg->msg_control) अणु
		अगर (test_bit(SOCK_PASSCRED, &sock->flags) || scm->fp)
			msg->msg_flags |= MSG_CTRUNC;
		scm_destroy(scm);
		वापस;
	पूर्ण

	अगर (test_bit(SOCK_PASSCRED, &sock->flags)) अणु
		काष्ठा user_namespace *current_ns = current_user_ns();
		काष्ठा ucred ucreds = अणु
			.pid = scm->creds.pid,
			.uid = from_kuid_munged(current_ns, scm->creds.uid),
			.gid = from_kgid_munged(current_ns, scm->creds.gid),
		पूर्ण;
		put_cmsg(msg, SOL_SOCKET, SCM_CREDENTIALS, माप(ucreds), &ucreds);
	पूर्ण

	scm_destroy_cred(scm);

	scm_passec(sock, msg, scm);

	अगर (!scm->fp)
		वापस;
	
	scm_detach_fds(msg, scm);
पूर्ण


#पूर्ण_अगर /* __LINUX_NET_SCM_H */

