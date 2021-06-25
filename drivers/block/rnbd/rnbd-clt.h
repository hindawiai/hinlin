<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अगर_अघोषित RNBD_CLT_H
#घोषणा RNBD_CLT_H

#समावेश <linux/रुको.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/refcount.h>

#समावेश <rtrs.h>
#समावेश "rnbd-proto.h"
#समावेश "rnbd-log.h"

/* Max. number of segments per IO request, Mellanox Connect X ~ Connect X5,
 * choose minimial 30 क्रम all, minus 1 क्रम पूर्णांकernal protocol, so 29.
 */
#घोषणा BMAX_SEGMENTS 29
/*  समय in seconds between reconnect tries, शेष to 30 s */
#घोषणा RECONNECT_DELAY 30
/*
 * Number of बार to reconnect on error beक्रमe giving up, 0 क्रम * disabled,
 * -1 क्रम क्रमever
 */
#घोषणा MAX_RECONNECTS -1

क्रमागत rnbd_clt_dev_state अणु
	DEV_STATE_INIT,
	DEV_STATE_MAPPED,
	DEV_STATE_MAPPED_DISCONNECTED,
	DEV_STATE_UNMAPPED,
पूर्ण;

काष्ठा rnbd_iu_comp अणु
	रुको_queue_head_t रुको;
	पूर्णांक त्रुटि_सं;
पूर्ण;

#अगर_घोषित CONFIG_ARCH_NO_SG_CHAIN
#घोषणा RNBD_INLINE_SG_CNT 0
#अन्यथा
#घोषणा RNBD_INLINE_SG_CNT 2
#पूर्ण_अगर
#घोषणा RNBD_RDMA_SGL_SIZE (माप(काष्ठा scatterlist) * RNBD_INLINE_SG_CNT)

काष्ठा rnbd_iu अणु
	जोड़ अणु
		काष्ठा request *rq; /* क्रम block io */
		व्योम *buf; /* क्रम user messages */
	पूर्ण;
	काष्ठा rtrs_permit	*permit;
	जोड़ अणु
		/* use to send msg associated with a dev */
		काष्ठा rnbd_clt_dev *dev;
		/* use to send msg associated with a sess */
		काष्ठा rnbd_clt_session *sess;
	पूर्ण;
	काष्ठा sg_table		sgt;
	काष्ठा work_काष्ठा	work;
	पूर्णांक			त्रुटि_सं;
	काष्ठा rnbd_iu_comp	comp;
	atomic_t		refcount;
	काष्ठा scatterlist	first_sgl[]; /* must be the last one */
पूर्ण;

काष्ठा rnbd_cpu_qlist अणु
	काष्ठा list_head	requeue_list;
	spinlock_t		requeue_lock;
	अचिन्हित पूर्णांक		cpu;
पूर्ण;

काष्ठा rnbd_clt_session अणु
	काष्ठा list_head        list;
	काष्ठा rtrs_clt        *rtrs;
	रुको_queue_head_t       rtrs_रुकोq;
	bool                    rtrs_पढ़ोy;
	काष्ठा rnbd_cpu_qlist	__percpu
				*cpu_queues;
	DECLARE_BITMAP(cpu_queues_bm, NR_CPUS);
	पूर्णांक	__percpu	*cpu_rr; /* per-cpu var क्रम CPU round-robin */
	atomic_t		busy;
	माप_प्रकार			queue_depth;
	u32			max_io_size;
	काष्ठा blk_mq_tag_set	tag_set;
	u32			nr_poll_queues;
	काष्ठा mutex		lock; /* protects state and devs_list */
	काष्ठा list_head        devs_list; /* list of काष्ठा rnbd_clt_dev */
	refcount_t		refcount;
	अक्षर			sessname[NAME_MAX];
	u8			ver; /* protocol version */
पूर्ण;

/**
 * Submission queues.
 */
काष्ठा rnbd_queue अणु
	काष्ठा list_head	requeue_list;
	अचिन्हित दीर्घ		in_list;
	काष्ठा rnbd_clt_dev	*dev;
	काष्ठा blk_mq_hw_ctx	*hctx;
पूर्ण;

काष्ठा rnbd_clt_dev अणु
	काष्ठा rnbd_clt_session	*sess;
	काष्ठा request_queue	*queue;
	काष्ठा rnbd_queue	*hw_queues;
	u32			device_id;
	/* local Idr index - used to track minor number allocations. */
	u32			clt_device_id;
	काष्ठा mutex		lock;
	क्रमागत rnbd_clt_dev_state	dev_state;
	अक्षर			*pathname;
	क्रमागत rnbd_access_mode	access_mode;
	u32			nr_poll_queues;
	bool			पढ़ो_only;
	bool			rotational;
	bool			wc;
	bool			fua;
	u32			max_hw_sectors;
	u32			max_ग_लिखो_same_sectors;
	u32			max_discard_sectors;
	u32			discard_granularity;
	u32			discard_alignment;
	u16			secure_discard;
	u16			physical_block_size;
	u16			logical_block_size;
	u16			max_segments;
	माप_प्रकार			nsectors;
	u64			size;		/* device size in bytes */
	काष्ठा list_head        list;
	काष्ठा gendisk		*gd;
	काष्ठा kobject		kobj;
	अक्षर			*blk_symlink_name;
	refcount_t		refcount;
	काष्ठा work_काष्ठा	unmap_on_rmmod_work;
पूर्ण;

/* rnbd-clt.c */

काष्ठा rnbd_clt_dev *rnbd_clt_map_device(स्थिर अक्षर *sessname,
					   काष्ठा rtrs_addr *paths,
					   माप_प्रकार path_cnt, u16 port_nr,
					   स्थिर अक्षर *pathname,
					   क्रमागत rnbd_access_mode access_mode,
					   u32 nr_poll_queues);
पूर्णांक rnbd_clt_unmap_device(काष्ठा rnbd_clt_dev *dev, bool क्रमce,
			   स्थिर काष्ठा attribute *sysfs_self);

पूर्णांक rnbd_clt_remap_device(काष्ठा rnbd_clt_dev *dev);
पूर्णांक rnbd_clt_resize_disk(काष्ठा rnbd_clt_dev *dev, माप_प्रकार newsize);

/* rnbd-clt-sysfs.c */

पूर्णांक rnbd_clt_create_sysfs_files(व्योम);

व्योम rnbd_clt_destroy_sysfs_files(व्योम);

व्योम rnbd_clt_हटाओ_dev_symlink(काष्ठा rnbd_clt_dev *dev);

#पूर्ण_अगर /* RNBD_CLT_H */
