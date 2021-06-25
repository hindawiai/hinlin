<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __nosy_user_h
#घोषणा __nosy_user_h

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा NOSY_IOC_GET_STATS _IOR('&', 0, काष्ठा nosy_stats)
#घोषणा NOSY_IOC_START     _IO('&', 1)
#घोषणा NOSY_IOC_STOP      _IO('&', 2)
#घोषणा NOSY_IOC_FILTER    _IOW('&', 2, __u32)

काष्ठा nosy_stats अणु
	__u32 total_packet_count;
	__u32 lost_packet_count;
पूर्ण;

/*
 * Format of packets वापसed from the kernel driver:
 *
 *	quadlet with बारtamp		(microseconds, CPU endian)
 *	quadlet-padded packet data...	(little endian)
 *	quadlet with ack		(little endian)
 */

#पूर्ण_अगर /* __nosy_user_h */
