<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* net/aपंचांग/common.h - ATM sockets (common part क्रम PVC and SVC) */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित NET_ATM_COMMON_H
#घोषणा NET_ATM_COMMON_H

#समावेश <linux/net.h>
#समावेश <linux/poll.h> /* क्रम poll_table */


पूर्णांक vcc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol, पूर्णांक family, पूर्णांक kern);
पूर्णांक vcc_release(काष्ठा socket *sock);
पूर्णांक vcc_connect(काष्ठा socket *sock, पूर्णांक itf, लघु vpi, पूर्णांक vci);
पूर्णांक vcc_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		पूर्णांक flags);
पूर्णांक vcc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार total_len);
__poll_t vcc_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको);
पूर्णांक vcc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक vcc_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक vcc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		   sockptr_t optval, अचिन्हित पूर्णांक optlen);
पूर्णांक vcc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		   अक्षर __user *optval, पूर्णांक __user *optlen);
व्योम vcc_process_recv_queue(काष्ठा aपंचांग_vcc *vcc);

पूर्णांक aपंचांगpvc_init(व्योम);
व्योम aपंचांगpvc_निकास(व्योम);
पूर्णांक aपंचांगsvc_init(व्योम);
व्योम aपंचांगsvc_निकास(व्योम);
पूर्णांक aपंचांग_sysfs_init(व्योम);
व्योम aपंचांग_sysfs_निकास(व्योम);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक aपंचांग_proc_init(व्योम);
व्योम aपंचांग_proc_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक aपंचांग_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aपंचांग_proc_निकास(व्योम)
अणु
	/* nothing */
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/* SVC */
पूर्णांक svc_change_qos(काष्ठा aपंचांग_vcc *vcc,काष्ठा aपंचांग_qos *qos);

व्योम aपंचांग_dev_release_vccs(काष्ठा aपंचांग_dev *dev);

#पूर्ण_अगर
