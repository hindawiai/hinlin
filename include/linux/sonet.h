<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sonet.h - SONET/SHD physical layer control */
#अगर_अघोषित LINUX_SONET_H
#घोषणा LINUX_SONET_H


#समावेश <linux/atomic.h>
#समावेश <uapi/linux/sonet.h>

काष्ठा k_sonet_stats अणु
#घोषणा __HANDLE_ITEM(i) atomic_t i
	__SONET_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण;

बाह्य व्योम sonet_copy_stats(काष्ठा k_sonet_stats *from,काष्ठा sonet_stats *to);
बाह्य व्योम sonet_subtract_stats(काष्ठा k_sonet_stats *from,
    काष्ठा sonet_stats *to);

#पूर्ण_अगर
