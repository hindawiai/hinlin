<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Public definitions क्रम the CAAM/QI (Queue Interface) backend.
 *
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 */

#अगर_अघोषित __QI_H__
#घोषणा __QI_H__

#समावेश <soc/fsl/qman.h>
#समावेश "compat.h"
#समावेश "desc.h"
#समावेश "desc_constr.h"

/* Length of a single buffer in the QI driver memory cache */
#घोषणा CAAM_QI_MEMCACHE_SIZE	768

बाह्य bool caam_congested __पढ़ो_mostly;

/*
 * This is the request काष्ठाure the driver application should fill जबतक
 * submitting a job to driver.
 */
काष्ठा caam_drv_req;

/*
 * caam_qi_cbk - application's callback function invoked by the driver when the
 *               request has been successfully processed.
 * @drv_req: original request that was submitted
 * @status: completion status of request (0 - success, non-zero - error code)
 */
प्रकार व्योम (*caam_qi_cbk)(काष्ठा caam_drv_req *drv_req, u32 status);

क्रमागत optype अणु
	ENCRYPT,
	DECRYPT,
	NUM_OP
पूर्ण;

/**
 * caam_drv_ctx - CAAM/QI backend driver context
 *
 * The jobs are processed by the driver against a driver context.
 * With every cryptographic context, a driver context is attached.
 * The driver context contains data क्रम निजी use by driver.
 * For the applications, this is an opaque काष्ठाure.
 *
 * @prehdr: preheader placed beक्रमe shrd desc
 * @sh_desc: shared descriptor
 * @context_a: shared descriptor dma address
 * @req_fq: to-CAAM request frame queue
 * @rsp_fq: from-CAAM response frame queue
 * @refcnt: reference counter incremented क्रम each frame enqueued in to-CAAM FQ
 * @cpu: cpu on which to receive CAAM response
 * @op_type: operation type
 * @qidev: device poपूर्णांकer क्रम CAAM/QI backend
 */
काष्ठा caam_drv_ctx अणु
	u32 prehdr[2];
	u32 sh_desc[MAX_SDLEN];
	dma_addr_t context_a;
	काष्ठा qman_fq *req_fq;
	काष्ठा qman_fq *rsp_fq;
	refcount_t refcnt;
	पूर्णांक cpu;
	क्रमागत optype op_type;
	काष्ठा device *qidev;
पूर्ण ____cacheline_aligned;

/**
 * caam_drv_req - The request काष्ठाure the driver application should fill जबतक
 *                submitting a job to driver.
 * @fd_sgt: QMan S/G poपूर्णांकing to output (fd_sgt[0]) and input (fd_sgt[1])
 *          buffers.
 * @cbk: callback function to invoke when job is completed
 * @app_ctx: arbitrary context attached with request by the application
 *
 * The fields mentioned below should not be used by application.
 * These are क्रम निजी use by driver.
 *
 * @hdr__: linked list header to मुख्यtain list of outstanding requests to CAAM
 * @hwaddr: DMA address क्रम the S/G table.
 */
काष्ठा caam_drv_req अणु
	काष्ठा qm_sg_entry fd_sgt[2];
	काष्ठा caam_drv_ctx *drv_ctx;
	caam_qi_cbk cbk;
	व्योम *app_ctx;
पूर्ण ____cacheline_aligned;

/**
 * caam_drv_ctx_init - Initialise a CAAM/QI driver context
 *
 * A CAAM/QI driver context must be attached with each cryptographic context.
 * This function allocates memory क्रम CAAM/QI context and वापसs a handle to
 * the application. This handle must be submitted aदीर्घ with each enqueue
 * request to the driver by the application.
 *
 * @cpu: CPU where the application prefers to the driver to receive CAAM
 *       responses. The request completion callback would be issued from this
 *       CPU.
 * @sh_desc: shared descriptor poपूर्णांकer to be attached with CAAM/QI driver
 *           context.
 *
 * Returns a driver context on success or negative error code on failure.
 */
काष्ठा caam_drv_ctx *caam_drv_ctx_init(काष्ठा device *qidev, पूर्णांक *cpu,
				       u32 *sh_desc);

/**
 * caam_qi_enqueue - Submit a request to QI backend driver.
 *
 * The request काष्ठाure must be properly filled as described above.
 *
 * @qidev: device poपूर्णांकer क्रम QI backend
 * @req: CAAM QI request काष्ठाure
 *
 * Returns 0 on success or negative error code on failure.
 */
पूर्णांक caam_qi_enqueue(काष्ठा device *qidev, काष्ठा caam_drv_req *req);

/**
 * caam_drv_ctx_busy - Check अगर there are too many jobs pending with CAAM
 *		       or too many CAAM responses are pending to be processed.
 * @drv_ctx: driver context क्रम which job is to be submitted
 *
 * Returns caam congestion status 'true/false'
 */
bool caam_drv_ctx_busy(काष्ठा caam_drv_ctx *drv_ctx);

/**
 * caam_drv_ctx_update - Update QI driver context
 *
 * Invoked when shared descriptor is required to be change in driver context.
 *
 * @drv_ctx: driver context to be updated
 * @sh_desc: new shared descriptor poपूर्णांकer to be updated in QI driver context
 *
 * Returns 0 on success or negative error code on failure.
 */
पूर्णांक caam_drv_ctx_update(काष्ठा caam_drv_ctx *drv_ctx, u32 *sh_desc);

/**
 * caam_drv_ctx_rel - Release a QI driver context
 * @drv_ctx: context to be released
 */
व्योम caam_drv_ctx_rel(काष्ठा caam_drv_ctx *drv_ctx);

पूर्णांक caam_qi_init(काष्ठा platक्रमm_device *pdev);

/**
 * qi_cache_alloc - Allocate buffers from CAAM-QI cache
 *
 * Invoked when a user of the CAAM-QI (i.e. caamalg-qi) needs data which has
 * to be allocated on the hotpath. Instead of using दो_स्मृति, one can use the
 * services of the CAAM QI memory cache (backed by kmem_cache). The buffers
 * will have a size of 256B, which is sufficient क्रम hosting 16 SG entries.
 *
 * @flags: flags that would be used क्रम the equivalent दो_स्मृति(..) call
 *
 * Returns a poपूर्णांकer to a retrieved buffer on success or शून्य on failure.
 */
व्योम *qi_cache_alloc(gfp_t flags);

/**
 * qi_cache_मुक्त - Frees buffers allocated from CAAM-QI cache
 *
 * Invoked when a user of the CAAM-QI (i.e. caamalg-qi) no दीर्घer needs
 * the buffer previously allocated by a qi_cache_alloc call.
 * No checking is being करोne, the call is a passthrough call to
 * kmem_cache_मुक्त(...)
 *
 * @obj: object previously allocated using qi_cache_alloc()
 */
व्योम qi_cache_मुक्त(व्योम *obj);

#पूर्ण_अगर /* __QI_H__ */
