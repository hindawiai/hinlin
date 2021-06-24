<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_FCOE_H
#घोषणा _IXGBE_FCOE_H

#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_fcoe.h>

/* shअगरt bits within STAT fo FCSTAT */
#घोषणा IXGBE_RXDADV_FCSTAT_SHIFT	4

/* ddp user buffer */
#घोषणा IXGBE_BUFFCNT_MAX	256	/* 8 bits bufcnt */
#घोषणा IXGBE_FCPTR_ALIGN	16
#घोषणा IXGBE_FCPTR_MAX	(IXGBE_BUFFCNT_MAX * माप(dma_addr_t))
#घोषणा IXGBE_FCBUFF_4KB	0x0
#घोषणा IXGBE_FCBUFF_8KB	0x1
#घोषणा IXGBE_FCBUFF_16KB	0x2
#घोषणा IXGBE_FCBUFF_64KB	0x3
#घोषणा IXGBE_FCBUFF_MAX	65536	/* 64KB max */
#घोषणा IXGBE_FCBUFF_MIN	4096	/* 4KB min */
#घोषणा IXGBE_FCOE_DDP_MAX	512	/* 9 bits xid */
#घोषणा IXGBE_FCOE_DDP_MAX_X550	2048	/* 11 bits xid */

/* Default traffic class to use क्रम FCoE */
#घोषणा IXGBE_FCOE_DEFTC	3

/* fcerr */
#घोषणा IXGBE_FCERR_BADCRC       0x00100000

/* FCoE DDP क्रम target mode */
#घोषणा __IXGBE_FCOE_TARGET	1

काष्ठा ixgbe_fcoe_ddp अणु
	पूर्णांक len;
	u32 err;
	अचिन्हित पूर्णांक sgc;
	काष्ठा scatterlist *sgl;
	dma_addr_t udp;
	u64 *udl;
	काष्ठा dma_pool *pool;
पूर्ण;

/* per cpu variables */
काष्ठा ixgbe_fcoe_ddp_pool अणु
	काष्ठा dma_pool *pool;
	u64 noddp;
	u64 noddp_ext_buff;
पूर्ण;

काष्ठा ixgbe_fcoe अणु
	काष्ठा ixgbe_fcoe_ddp_pool __percpu *ddp_pool;
	atomic_t refcnt;
	spinlock_t lock;
	काष्ठा ixgbe_fcoe_ddp ddp[IXGBE_FCOE_DDP_MAX_X550];
	व्योम *extra_ddp_buffer;
	dma_addr_t extra_ddp_buffer_dma;
	अचिन्हित दीर्घ mode;
	u8 up;
पूर्ण;

#पूर्ण_अगर /* _IXGBE_FCOE_H */
