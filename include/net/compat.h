<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित NET_COMPAT_H
#घोषणा NET_COMPAT_H


काष्ठा sock;

#समावेश <linux/compat.h>

काष्ठा compat_msghdr अणु
	compat_uptr_t	msg_name;	/* व्योम * */
	compat_पूर्णांक_t	msg_namelen;
	compat_uptr_t	msg_iov;	/* काष्ठा compat_iovec * */
	compat_माप_प्रकार	msg_iovlen;
	compat_uptr_t	msg_control;	/* व्योम * */
	compat_माप_प्रकार	msg_controllen;
	compat_uपूर्णांक_t	msg_flags;
पूर्ण;

काष्ठा compat_mmsghdr अणु
	काष्ठा compat_msghdr msg_hdr;
	compat_uपूर्णांक_t        msg_len;
पूर्ण;

काष्ठा compat_cmsghdr अणु
	compat_माप_प्रकार	cmsg_len;
	compat_पूर्णांक_t	cmsg_level;
	compat_पूर्णांक_t	cmsg_type;
पूर्ण;

काष्ठा compat_rtentry अणु
	u32		rt_pad1;
	काष्ठा sockaddr rt_dst;         /* target address               */
	काष्ठा sockaddr rt_gateway;     /* gateway addr (RTF_GATEWAY)   */
	काष्ठा sockaddr rt_genmask;     /* target network mask (IP)     */
	अचिन्हित लघु	rt_flags;
	लघु		rt_pad2;
	u32		rt_pad3;
	अचिन्हित अक्षर	rt_tos;
	अचिन्हित अक्षर	rt_class;
	लघु		rt_pad4;
	लघु		rt_metric;      /* +1 क्रम binary compatibility! */
	compat_uptr_t	rt_dev;         /* क्रमcing the device at add    */
	u32		rt_mtu;         /* per route MTU/Winकरोw         */
	u32		rt_winकरोw;      /* Winकरोw clamping              */
	अचिन्हित लघु  rt_irtt;        /* Initial RTT                  */
पूर्ण;

पूर्णांक __get_compat_msghdr(काष्ठा msghdr *kmsg, काष्ठा compat_msghdr __user *umsg,
			काष्ठा sockaddr __user **save_addr, compat_uptr_t *ptr,
			compat_माप_प्रकार *len);
पूर्णांक get_compat_msghdr(काष्ठा msghdr *, काष्ठा compat_msghdr __user *,
		      काष्ठा sockaddr __user **, काष्ठा iovec **);
पूर्णांक put_cmsg_compat(काष्ठा msghdr*, पूर्णांक, पूर्णांक, पूर्णांक, व्योम *);

पूर्णांक cmsghdr_from_user_compat_to_kern(काष्ठा msghdr *, काष्ठा sock *,
				     अचिन्हित अक्षर *, पूर्णांक);

काष्ठा compat_group_req अणु
	__u32				 gr_पूर्णांकerface;
	काष्ठा __kernel_sockaddr_storage gr_group
		__aligned(4);
पूर्ण __packed;

काष्ठा compat_group_source_req अणु
	__u32				 gsr_पूर्णांकerface;
	काष्ठा __kernel_sockaddr_storage gsr_group
		__aligned(4);
	काष्ठा __kernel_sockaddr_storage gsr_source
		__aligned(4);
पूर्ण __packed;

काष्ठा compat_group_filter अणु
	__u32				 gf_पूर्णांकerface;
	काष्ठा __kernel_sockaddr_storage gf_group
		__aligned(4);
	__u32				 gf_भ_शेषe;
	__u32				 gf_numsrc;
	काष्ठा __kernel_sockaddr_storage gf_slist[1]
		__aligned(4);
पूर्ण __packed;

#पूर्ण_अगर /* NET_COMPAT_H */
