<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ATM ioctl handling */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
/* 2003 John Levon  <levon@movementarian.org> */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/net.h>		/* काष्ठा socket, काष्ठा proto_ops */
#समावेश <linux/aपंचांग.h>		/* ATM stuff */
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगclip.h>	/* CLIP_*ENCAP */
#समावेश <linux/aपंचांगarp.h>	/* manअगरest स्थिरants */
#समावेश <linux/capability.h>
#समावेश <linux/sonet.h>	/* क्रम ioctls */
#समावेश <linux/aपंचांगsvc.h>
#समावेश <linux/aपंचांगmpc.h>
#समावेश <net/aपंचांगclip.h>
#समावेश <linux/aपंचांगlec.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <net/compat.h>

#समावेश "resources.h"
#समावेश "signaling.h"		/* क्रम WAITING and sigd_attach */
#समावेश "common.h"


अटल DEFINE_MUTEX(ioctl_mutex);
अटल LIST_HEAD(ioctl_list);


व्योम रेजिस्टर_aपंचांग_ioctl(काष्ठा aपंचांग_ioctl *ioctl)
अणु
	mutex_lock(&ioctl_mutex);
	list_add_tail(&ioctl->list, &ioctl_list);
	mutex_unlock(&ioctl_mutex);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_aपंचांग_ioctl);

व्योम deरेजिस्टर_aपंचांग_ioctl(काष्ठा aपंचांग_ioctl *ioctl)
अणु
	mutex_lock(&ioctl_mutex);
	list_del(&ioctl->list);
	mutex_unlock(&ioctl_mutex);
पूर्ण
EXPORT_SYMBOL(deरेजिस्टर_aपंचांग_ioctl);

अटल पूर्णांक करो_vcc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg, पूर्णांक compat)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक error;
	काष्ठा list_head *pos;
	व्योम __user *argp = (व्योम __user *)arg;
	व्योम __user *buf;
	पूर्णांक __user *len;

	vcc = ATM_SD(sock);
	चयन (cmd) अणु
	हाल SIOCOUTQ:
		अगर (sock->state != SS_CONNECTED ||
		    !test_bit(ATM_VF_READY, &vcc->flags)) अणु
			error =  -EINVAL;
			जाओ करोne;
		पूर्ण
		error = put_user(sk->sk_sndbuf - sk_wmem_alloc_get(sk),
				 (पूर्णांक __user *)argp) ? -EFAULT : 0;
		जाओ करोne;
	हाल SIOCINQ:
	अणु
		काष्ठा sk_buff *skb;

		अगर (sock->state != SS_CONNECTED) अणु
			error = -EINVAL;
			जाओ करोne;
		पूर्ण
		skb = skb_peek(&sk->sk_receive_queue);
		error = put_user(skb ? skb->len : 0,
				 (पूर्णांक __user *)argp) ? -EFAULT : 0;
		जाओ करोne;
	पूर्ण
	हाल ATM_SETSC:
		net_warn_ratelimited("ATM_SETSC is obsolete; used by %s:%d\n",
				     current->comm, task_pid_nr(current));
		error = 0;
		जाओ करोne;
	हाल ATMSIGD_CTRL:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
		/*
		 * The user/kernel protocol क्रम exchanging संकेतling
		 * info uses kernel poपूर्णांकers as opaque references,
		 * so the holder of the file descriptor can scribble
		 * on the kernel... so we should make sure that we
		 * have the same privileges that /proc/kcore needs
		 */
		अगर (!capable(CAP_SYS_RAWIO)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
#अगर_घोषित CONFIG_COMPAT
		/* WTF? I करोn't even want to _think_ about making this
		   work क्रम 32-bit userspace. TBH I करोn't really want
		   to think about it at all. dwmw2. */
		अगर (compat) अणु
			net_warn_ratelimited("32-bit task cannot be atmsigd\n");
			error = -EINVAL;
			जाओ करोne;
		पूर्ण
#पूर्ण_अगर
		error = sigd_attach(vcc);
		अगर (!error)
			sock->state = SS_CONNECTED;
		जाओ करोne;
	हाल ATM_SETBACKEND:
	हाल ATM_NEWBACKENDIF:
	अणु
		aपंचांग_backend_t backend;
		error = get_user(backend, (aपंचांग_backend_t __user *)argp);
		अगर (error)
			जाओ करोne;
		चयन (backend) अणु
		हाल ATM_BACKEND_PPP:
			request_module("pppoatm");
			अवरोध;
		हाल ATM_BACKEND_BR2684:
			request_module("br2684");
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ATMMPC_CTRL:
	हाल ATMMPC_DATA:
		request_module("mpoa");
		अवरोध;
	हाल ATMARPD_CTRL:
		request_module("clip");
		अवरोध;
	हाल ATMLEC_CTRL:
		request_module("lec");
		अवरोध;
	पूर्ण

	error = -ENOIOCTLCMD;

	mutex_lock(&ioctl_mutex);
	list_क्रम_each(pos, &ioctl_list) अणु
		काष्ठा aपंचांग_ioctl *ic = list_entry(pos, काष्ठा aपंचांग_ioctl, list);
		अगर (try_module_get(ic->owner)) अणु
			error = ic->ioctl(sock, cmd, arg);
			module_put(ic->owner);
			अगर (error != -ENOIOCTLCMD)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioctl_mutex);

	अगर (error != -ENOIOCTLCMD)
		जाओ करोne;

	अगर (cmd == ATM_GETNAMES) अणु
		अगर (IS_ENABLED(CONFIG_COMPAT) && compat) अणु
#अगर_घोषित CONFIG_COMPAT
			काष्ठा compat_aपंचांग_iobuf __user *ciobuf = argp;
			compat_uptr_t cbuf;
			len = &ciobuf->length;
			अगर (get_user(cbuf, &ciobuf->buffer))
				वापस -EFAULT;
			buf = compat_ptr(cbuf);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			काष्ठा aपंचांग_iobuf __user *iobuf = argp;
			len = &iobuf->length;
			अगर (get_user(buf, &iobuf->buffer))
				वापस -EFAULT;
		पूर्ण
		error = aपंचांग_getnames(buf, len);
	पूर्ण अन्यथा अणु
		पूर्णांक number;

		अगर (IS_ENABLED(CONFIG_COMPAT) && compat) अणु
#अगर_घोषित CONFIG_COMPAT
			काष्ठा compat_aपंचांगअगर_sioc __user *csioc = argp;
			compat_uptr_t carg;

			len = &csioc->length;
			अगर (get_user(carg, &csioc->arg))
				वापस -EFAULT;
			buf = compat_ptr(carg);
			अगर (get_user(number, &csioc->number))
				वापस -EFAULT;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			काष्ठा aपंचांगअगर_sioc __user *sioc = argp;

			len = &sioc->length;
			अगर (get_user(buf, &sioc->arg))
				वापस -EFAULT;
			अगर (get_user(number, &sioc->number))
				वापस -EFAULT;
		पूर्ण
		error = aपंचांग_dev_ioctl(cmd, buf, len, number, compat);
	पूर्ण

करोne:
	वापस error;
पूर्ण

पूर्णांक vcc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस करो_vcc_ioctl(sock, cmd, arg, 0);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * FIXME:
 * The compat_ioctl handling is duplicated, using both these conversion
 * routines and the compat argument to the actual handlers. Both
 * versions are somewhat incomplete and should be merged, e.g. by
 * moving the ioctl number translation पूर्णांकo the actual handlers and
 * समाप्तing the conversion code.
 *
 * -arnd, November 2009
 */
#घोषणा ATM_GETLINKRATE32 _IOW('a', ATMIOC_ITF+1, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETNAMES32    _IOW('a', ATMIOC_ITF+3, काष्ठा compat_aपंचांग_iobuf)
#घोषणा ATM_GETTYPE32     _IOW('a', ATMIOC_ITF+4, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETESI32	  _IOW('a', ATMIOC_ITF+5, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETADDR32	  _IOW('a', ATMIOC_ITF+6, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_RSTADDR32	  _IOW('a', ATMIOC_ITF+7, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_ADDADDR32	  _IOW('a', ATMIOC_ITF+8, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_DELADDR32	  _IOW('a', ATMIOC_ITF+9, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETCIRANGE32  _IOW('a', ATMIOC_ITF+10, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_SETCIRANGE32  _IOW('a', ATMIOC_ITF+11, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_SETESI32      _IOW('a', ATMIOC_ITF+12, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_SETESIF32     _IOW('a', ATMIOC_ITF+13, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETSTAT32     _IOW('a', ATMIOC_SARCOM+0, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETSTATZ32    _IOW('a', ATMIOC_SARCOM+1, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_GETLOOP32	  _IOW('a', ATMIOC_SARCOM+2, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_SETLOOP32	  _IOW('a', ATMIOC_SARCOM+3, काष्ठा compat_aपंचांगअगर_sioc)
#घोषणा ATM_QUERYLOOP32	  _IOW('a', ATMIOC_SARCOM+4, काष्ठा compat_aपंचांगअगर_sioc)

अटल काष्ठा अणु
	अचिन्हित पूर्णांक cmd32;
	अचिन्हित पूर्णांक cmd;
पूर्ण aपंचांग_ioctl_map[] = अणु
	अणु ATM_GETLINKRATE32, ATM_GETLINKRATE पूर्ण,
	अणु ATM_GETNAMES32,    ATM_GETNAMES पूर्ण,
	अणु ATM_GETTYPE32,     ATM_GETTYPE पूर्ण,
	अणु ATM_GETESI32,	     ATM_GETESI पूर्ण,
	अणु ATM_GETADDR32,     ATM_GETADDR पूर्ण,
	अणु ATM_RSTADDR32,     ATM_RSTADDR पूर्ण,
	अणु ATM_ADDADDR32,     ATM_ADDADDR पूर्ण,
	अणु ATM_DELADDR32,     ATM_DELADDR पूर्ण,
	अणु ATM_GETCIRANGE32,  ATM_GETCIRANGE पूर्ण,
	अणु ATM_SETCIRANGE32,  ATM_SETCIRANGE पूर्ण,
	अणु ATM_SETESI32,	     ATM_SETESI पूर्ण,
	अणु ATM_SETESIF32,     ATM_SETESIF पूर्ण,
	अणु ATM_GETSTAT32,     ATM_GETSTAT पूर्ण,
	अणु ATM_GETSTATZ32,    ATM_GETSTATZ पूर्ण,
	अणु ATM_GETLOOP32,     ATM_GETLOOP पूर्ण,
	अणु ATM_SETLOOP32,     ATM_SETLOOP पूर्ण,
	अणु ATM_QUERYLOOP32,   ATM_QUERYLOOP पूर्ण,
पूर्ण;

#घोषणा NR_ATM_IOCTL ARRAY_SIZE(aपंचांग_ioctl_map)

अटल पूर्णांक करो_aपंचांग_iobuf(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_aपंचांग_iobuf __user *iobuf32 = compat_ptr(arg);
	u32 data;

	अगर (get_user(data, &iobuf32->buffer))
		वापस -EFAULT;

	वापस aपंचांग_getnames(&iobuf32->length, compat_ptr(data));
पूर्ण

अटल पूर्णांक करो_aपंचांगअगर_sioc(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_aपंचांगअगर_sioc __user *sioc32 = compat_ptr(arg);
	पूर्णांक number;
	u32 data;

	अगर (get_user(data, &sioc32->arg) || get_user(number, &sioc32->number))
		वापस -EFAULT;
	वापस aपंचांग_dev_ioctl(cmd, compat_ptr(data), &sioc32->length, number, 0);
पूर्ण

अटल पूर्णांक करो_aपंचांग_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd32,
			अचिन्हित दीर्घ arg)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक cmd = 0;

	चयन (cmd32) अणु
	हाल SONET_GETSTAT:
	हाल SONET_GETSTATZ:
	हाल SONET_GETDIAG:
	हाल SONET_SETDIAG:
	हाल SONET_CLRDIAG:
	हाल SONET_SETFRAMING:
	हाल SONET_GETFRAMING:
	हाल SONET_GETFRSENSE:
		वापस करो_aपंचांगअगर_sioc(sock, cmd32, arg);
	पूर्ण

	क्रम (i = 0; i < NR_ATM_IOCTL; i++) अणु
		अगर (cmd32 == aपंचांग_ioctl_map[i].cmd32) अणु
			cmd = aपंचांग_ioctl_map[i].cmd;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == NR_ATM_IOCTL)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल ATM_GETNAMES:
		वापस करो_aपंचांग_iobuf(sock, cmd, arg);

	हाल ATM_GETLINKRATE:
	हाल ATM_GETTYPE:
	हाल ATM_GETESI:
	हाल ATM_GETADDR:
	हाल ATM_RSTADDR:
	हाल ATM_ADDADDR:
	हाल ATM_DELADDR:
	हाल ATM_GETCIRANGE:
	हाल ATM_SETCIRANGE:
	हाल ATM_SETESI:
	हाल ATM_SETESIF:
	हाल ATM_GETSTAT:
	हाल ATM_GETSTATZ:
	हाल ATM_GETLOOP:
	हाल ATM_SETLOOP:
	हाल ATM_QUERYLOOP:
		वापस करो_aपंचांगअगर_sioc(sock, cmd, arg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक vcc_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
		     अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	ret = करो_vcc_ioctl(sock, cmd, arg, 1);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	वापस करो_aपंचांग_ioctl(sock, cmd, arg);
पूर्ण
#पूर्ण_अगर
