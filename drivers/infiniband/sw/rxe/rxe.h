<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_H
#घोषणा RXE_H

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/crc32.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_addr.h>
#समावेश <crypto/hash.h>

#समावेश "rxe_net.h"
#समावेश "rxe_opcode.h"
#समावेश "rxe_hdr.h"
#समावेश "rxe_param.h"
#समावेश "rxe_verbs.h"
#समावेश "rxe_loc.h"

/*
 * Version 1 and Version 2 are identical on 64 bit machines, but on 32 bit
 * machines Version 2 has a dअगरferent काष्ठा layout.
 */
#घोषणा RXE_UVERBS_ABI_VERSION		2

#घोषणा RXE_ROCE_V2_SPORT		(0xc000)

बाह्य bool rxe_initialized;

अटल अंतरभूत u32 rxe_crc32(काष्ठा rxe_dev *rxe,
			    u32 crc, व्योम *next, माप_प्रकार len)
अणु
	u32 retval;
	पूर्णांक err;

	SHASH_DESC_ON_STACK(shash, rxe->tfm);

	shash->tfm = rxe->tfm;
	*(u32 *)shash_desc_ctx(shash) = crc;
	err = crypto_shash_update(shash, next, len);
	अगर (unlikely(err)) अणु
		pr_warn_ratelimited("failed crc calculation, err: %d\n", err);
		वापस crc32_le(crc, next, len);
	पूर्ण

	retval = *(u32 *)shash_desc_ctx(shash);
	barrier_data(shash_desc_ctx(shash));
	वापस retval;
पूर्ण

व्योम rxe_set_mtu(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक dev_mtu);

पूर्णांक rxe_add(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक mtu, स्थिर अक्षर *ibdev_name);

व्योम rxe_rcv(काष्ठा sk_buff *skb);

/* The caller must करो a matching ib_device_put(&dev->ib_dev) */
अटल अंतरभूत काष्ठा rxe_dev *rxe_get_dev_from_net(काष्ठा net_device *ndev)
अणु
	काष्ठा ib_device *ibdev =
		ib_device_get_by_netdev(ndev, RDMA_DRIVER_RXE);

	अगर (!ibdev)
		वापस शून्य;
	वापस container_of(ibdev, काष्ठा rxe_dev, ib_dev);
पूर्ण

व्योम rxe_port_up(काष्ठा rxe_dev *rxe);
व्योम rxe_port_करोwn(काष्ठा rxe_dev *rxe);
व्योम rxe_set_port_state(काष्ठा rxe_dev *rxe);

#पूर्ण_अगर /* RXE_H */
