<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2019 NXP
 *
 */
#अगर_अघोषित __FSL_DPAA2_IO_H
#घोषणा __FSL_DPAA2_IO_H

#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irqवापस.h>

#समावेश "dpaa2-fd.h"
#समावेश "dpaa2-global.h"

काष्ठा dpaa2_io;
काष्ठा dpaa2_io_store;
काष्ठा device;

/**
 * DOC: DPIO Service
 *
 * The DPIO service provides APIs क्रम users to पूर्णांकeract with the datapath
 * by enqueueing and dequeing frame descriptors.
 *
 * The following set of APIs can be used to enqueue and dequeue frames
 * as well as producing notअगरication callbacks when data is available
 * क्रम dequeue.
 */

#घोषणा DPAA2_IO_ANY_CPU	-1

/**
 * काष्ठा dpaa2_io_desc - The DPIO descriptor
 * @receives_notअगरications: Use notअगरicaton mode. Non-zero अगर the DPIO
 *                  has a channel.
 * @has_8prio:      Set to non-zero क्रम channel with 8 priority WQs.  Ignored
 *                  unless receives_notअगरication is TRUE.
 * @cpu:            The cpu index that at least पूर्णांकerrupt handlers will
 *                  execute on.
 * @stash_affinity: The stash affinity क्रम this portal favour 'cpu'
 * @regs_cena:      The cache enabled regs.
 * @regs_cinh:      The cache inhibited regs
 * @dpio_id:        The dpio index
 * @qman_version:   The qman version
 *
 * Describes the attributes and features of the DPIO object.
 */
काष्ठा dpaa2_io_desc अणु
	पूर्णांक receives_notअगरications;
	पूर्णांक has_8prio;
	पूर्णांक cpu;
	व्योम *regs_cena;
	व्योम __iomem *regs_cinh;
	पूर्णांक dpio_id;
	u32 qman_version;
पूर्ण;

काष्ठा dpaa2_io *dpaa2_io_create(स्थिर काष्ठा dpaa2_io_desc *desc,
				 काष्ठा device *dev);

व्योम dpaa2_io_करोwn(काष्ठा dpaa2_io *d);

irqवापस_t dpaa2_io_irq(काष्ठा dpaa2_io *obj);

काष्ठा dpaa2_io *dpaa2_io_service_select(पूर्णांक cpu);

/**
 * काष्ठा dpaa2_io_notअगरication_ctx - The DPIO notअगरication context काष्ठाure
 * @cb:           The callback to be invoked when the notअगरication arrives
 * @is_cdan:      Zero क्रम FQDAN, non-zero क्रम CDAN
 * @id:           FQID or channel ID, needed क्रम rearm
 * @desired_cpu:  The cpu on which the notअगरications will show up. Use
 *                DPAA2_IO_ANY_CPU अगर करोn't care
 * @dpio_id:      The dpio index
 * @qman64:       The 64-bit context value shows up in the FQDAN/CDAN.
 * @node:         The list node
 * @dpio_निजी: The dpio object पूर्णांकernal to dpio_service
 *
 * Used when a FQDAN/CDAN registration is made by drivers.
 */
काष्ठा dpaa2_io_notअगरication_ctx अणु
	व्योम (*cb)(काष्ठा dpaa2_io_notअगरication_ctx *ctx);
	पूर्णांक is_cdan;
	u32 id;
	पूर्णांक desired_cpu;
	पूर्णांक dpio_id;
	u64 qman64;
	काष्ठा list_head node;
	व्योम *dpio_निजी;
पूर्ण;

पूर्णांक dpaa2_io_get_cpu(काष्ठा dpaa2_io *d);

पूर्णांक dpaa2_io_service_रेजिस्टर(काष्ठा dpaa2_io *service,
			      काष्ठा dpaa2_io_notअगरication_ctx *ctx,
			      काष्ठा device *dev);
व्योम dpaa2_io_service_deरेजिस्टर(काष्ठा dpaa2_io *service,
				 काष्ठा dpaa2_io_notअगरication_ctx *ctx,
				 काष्ठा device *dev);
पूर्णांक dpaa2_io_service_rearm(काष्ठा dpaa2_io *service,
			   काष्ठा dpaa2_io_notअगरication_ctx *ctx);

पूर्णांक dpaa2_io_service_pull_fq(काष्ठा dpaa2_io *d, u32 fqid,
			     काष्ठा dpaa2_io_store *s);
पूर्णांक dpaa2_io_service_pull_channel(काष्ठा dpaa2_io *d, u32 channelid,
				  काष्ठा dpaa2_io_store *s);

पूर्णांक dpaa2_io_service_enqueue_fq(काष्ठा dpaa2_io *d, u32 fqid,
				स्थिर काष्ठा dpaa2_fd *fd);
पूर्णांक dpaa2_io_service_enqueue_multiple_fq(काष्ठा dpaa2_io *d, u32 fqid,
				स्थिर काष्ठा dpaa2_fd *fd, पूर्णांक number_of_frame);
पूर्णांक dpaa2_io_service_enqueue_multiple_desc_fq(काष्ठा dpaa2_io *d, u32 *fqid,
				स्थिर काष्ठा dpaa2_fd *fd, पूर्णांक number_of_frame);
पूर्णांक dpaa2_io_service_enqueue_qd(काष्ठा dpaa2_io *d, u32 qdid, u8 prio,
				u16 qdbin, स्थिर काष्ठा dpaa2_fd *fd);
पूर्णांक dpaa2_io_service_release(काष्ठा dpaa2_io *d, u16 bpid,
			     स्थिर u64 *buffers, अचिन्हित पूर्णांक num_buffers);
पूर्णांक dpaa2_io_service_acquire(काष्ठा dpaa2_io *d, u16 bpid,
			     u64 *buffers, अचिन्हित पूर्णांक num_buffers);

काष्ठा dpaa2_io_store *dpaa2_io_store_create(अचिन्हित पूर्णांक max_frames,
					     काष्ठा device *dev);
व्योम dpaa2_io_store_destroy(काष्ठा dpaa2_io_store *s);
काष्ठा dpaa2_dq *dpaa2_io_store_next(काष्ठा dpaa2_io_store *s, पूर्णांक *is_last);

पूर्णांक dpaa2_io_query_fq_count(काष्ठा dpaa2_io *d, u32 fqid,
			    u32 *fcnt, u32 *bcnt);
पूर्णांक dpaa2_io_query_bp_count(काष्ठा dpaa2_io *d, u16 bpid,
			    u32 *num);
#पूर्ण_अगर /* __FSL_DPAA2_IO_H */
