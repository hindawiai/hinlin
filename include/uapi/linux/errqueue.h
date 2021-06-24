<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_ERRQUEUE_H
#घोषणा _UAPI_LINUX_ERRQUEUE_H

#समावेश <linux/types.h>
#समावेश <linux/समय_प्रकारypes.h>

/* RFC 4884: वापस offset to extension काष्ठा + validation */
काष्ठा sock_ee_data_rfc4884 अणु
	__u16	len;
	__u8	flags;
	__u8	reserved;
पूर्ण;

काष्ठा sock_extended_err अणु
	__u32	ee_त्रुटि_सं;	
	__u8	ee_origin;
	__u8	ee_type;
	__u8	ee_code;
	__u8	ee_pad;
	__u32   ee_info;
	जोड़	अणु
		__u32   ee_data;
		काष्ठा sock_ee_data_rfc4884 ee_rfc4884;
	पूर्ण;
पूर्ण;

#घोषणा SO_EE_ORIGIN_NONE	0
#घोषणा SO_EE_ORIGIN_LOCAL	1
#घोषणा SO_EE_ORIGIN_ICMP	2
#घोषणा SO_EE_ORIGIN_ICMP6	3
#घोषणा SO_EE_ORIGIN_TXSTATUS	4
#घोषणा SO_EE_ORIGIN_ZEROCOPY	5
#घोषणा SO_EE_ORIGIN_TXTIME	6
#घोषणा SO_EE_ORIGIN_TIMESTAMPING SO_EE_ORIGIN_TXSTATUS

#घोषणा SO_EE_OFFENDER(ee)	((काष्ठा sockaddr*)((ee)+1))

#घोषणा SO_EE_CODE_ZEROCOPY_COPIED	1

#घोषणा SO_EE_CODE_TXTIME_INVALID_PARAM	1
#घोषणा SO_EE_CODE_TXTIME_MISSED	2

#घोषणा SO_EE_RFC4884_FLAG_INVALID	1

/**
 *	काष्ठा scm_बारtamping - बारtamps exposed through cmsg
 *
 *	The बारtamping पूर्णांकerfaces SO_TIMESTAMPING, MSG_TSTAMP_*
 *	communicate network बारtamps by passing this काष्ठा in a cmsg with
 *	recvmsg(). See Documentation/networking/बारtamping.rst क्रम details.
 *	User space sees a बारpec definition that matches either
 *	__kernel_बारpec or __kernel_old_बारpec, in the kernel we
 *	require two काष्ठाure definitions to provide both.
 */
काष्ठा scm_बारtamping अणु
#अगर_घोषित __KERNEL__
	काष्ठा __kernel_old_बारpec ts[3];
#अन्यथा
	काष्ठा बारpec ts[3];
#पूर्ण_अगर
पूर्ण;

काष्ठा scm_बारtamping64 अणु
	काष्ठा __kernel_बारpec ts[3];
पूर्ण;

/* The type of scm_बारtamping, passed in sock_extended_err ee_info.
 * This defines the type of ts[0]. For SCM_TSTAMP_SND only, अगर ts[0]
 * is zero, then this is a hardware बारtamp and recorded in ts[2].
 */
क्रमागत अणु
	SCM_TSTAMP_SND,		/* driver passed skb to NIC, or HW */
	SCM_TSTAMP_SCHED,	/* data entered the packet scheduler */
	SCM_TSTAMP_ACK,		/* data acknowledged by peer */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_ERRQUEUE_H */
