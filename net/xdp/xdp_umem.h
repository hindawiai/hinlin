<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* XDP user-space packet buffer
 * Copyright(c) 2018 Intel Corporation.
 */

#अगर_अघोषित XDP_UMEM_H_
#घोषणा XDP_UMEM_H_

#समावेश <net/xdp_sock_drv.h>

व्योम xdp_get_umem(काष्ठा xdp_umem *umem);
व्योम xdp_put_umem(काष्ठा xdp_umem *umem, bool defer_cleanup);
काष्ठा xdp_umem *xdp_umem_create(काष्ठा xdp_umem_reg *mr);

#पूर्ण_अगर /* XDP_UMEM_H_ */
