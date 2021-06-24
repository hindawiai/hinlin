<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2015-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2018 NXP
 */

#अगर_अघोषित _CAAMALG_QI2_H_
#घोषणा _CAAMALG_QI2_H_

#समावेश <soc/fsl/dpaa2-पन.स>
#समावेश <soc/fsl/dpaa2-fd.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/netdevice.h>
#समावेश "dpseci.h"
#समावेश "desc_constr.h"
#समावेश <crypto/skcipher.h>

#घोषणा DPAA2_CAAM_STORE_SIZE	16
/* NAPI weight *must* be a multiple of the store size. */
#घोषणा DPAA2_CAAM_NAPI_WEIGHT	512

/* The congestion entrance threshold was chosen so that on LS2088
 * we support the maximum throughput क्रम the available memory
 */
#घोषणा DPAA2_SEC_CONG_ENTRY_THRESH	(128 * 1024 * 1024)
#घोषणा DPAA2_SEC_CONG_EXIT_THRESH	(DPAA2_SEC_CONG_ENTRY_THRESH * 9 / 10)

/**
 * dpaa2_caam_priv - driver निजी data
 * @dpseci_id: DPSECI object unique ID
 * @major_ver: DPSECI major version
 * @minor_ver: DPSECI minor version
 * @dpseci_attr: DPSECI attributes
 * @sec_attr: SEC engine attributes
 * @rx_queue_attr: array of Rx queue attributes
 * @tx_queue_attr: array of Tx queue attributes
 * @cscn_mem: poपूर्णांकer to memory region containing the congestion SCN
 *	it's size is larger than to accommodate alignment
 * @cscn_mem_aligned: poपूर्णांकer to congestion SCN; it is computed as
 *	PTR_ALIGN(cscn_mem, DPAA2_CSCN_ALIGN)
 * @cscn_dma: dma address used by the QMAN to ग_लिखो CSCN messages
 * @dev: device associated with the DPSECI object
 * @mc_io: poपूर्णांकer to MC portal's I/O object
 * @करोमुख्य: IOMMU करोमुख्य
 * @ppriv: per CPU poपूर्णांकers to privata data
 */
काष्ठा dpaa2_caam_priv अणु
	पूर्णांक dpsec_id;

	u16 major_ver;
	u16 minor_ver;

	काष्ठा dpseci_attr dpseci_attr;
	काष्ठा dpseci_sec_attr sec_attr;
	काष्ठा dpseci_rx_queue_attr rx_queue_attr[DPSECI_MAX_QUEUE_NUM];
	काष्ठा dpseci_tx_queue_attr tx_queue_attr[DPSECI_MAX_QUEUE_NUM];
	पूर्णांक num_pairs;

	/* congestion */
	व्योम *cscn_mem;
	व्योम *cscn_mem_aligned;
	dma_addr_t cscn_dma;

	काष्ठा device *dev;
	काष्ठा fsl_mc_io *mc_io;
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	काष्ठा dpaa2_caam_priv_per_cpu __percpu *ppriv;
	काष्ठा dentry *dfs_root;
पूर्ण;

/**
 * dpaa2_caam_priv_per_cpu - per CPU निजी data
 * @napi: napi काष्ठाure
 * @net_dev: netdev used by napi
 * @req_fqid: (भव) request (Tx / enqueue) FQID
 * @rsp_fqid: (भव) response (Rx / dequeue) FQID
 * @prio: पूर्णांकernal queue number - index क्रम dpaa2_caam_priv.*_queue_attr
 * @nctx: notअगरication context of response FQ
 * @store: where dequeued frames are stored
 * @priv: backpoपूर्णांकer to dpaa2_caam_priv
 * @dpio: portal used क्रम data path operations
 */
काष्ठा dpaa2_caam_priv_per_cpu अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device net_dev;
	पूर्णांक req_fqid;
	पूर्णांक rsp_fqid;
	पूर्णांक prio;
	काष्ठा dpaa2_io_notअगरication_ctx nctx;
	काष्ठा dpaa2_io_store *store;
	काष्ठा dpaa2_caam_priv *priv;
	काष्ठा dpaa2_io *dpio;
पूर्ण;

/* Length of a single buffer in the QI driver memory cache */
#घोषणा CAAM_QI_MEMCACHE_SIZE	512

/*
 * aead_edesc - s/w-extended aead descriptor
 * @src_nents: number of segments in input scatterlist
 * @dst_nents: number of segments in output scatterlist
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @qm_sg_bytes: length of dma mapped h/w link table
 * @qm_sg_dma: bus physical mapped address of h/w link table
 * @assoclen: associated data length, in CAAM endianness
 * @assoclen_dma: bus physical mapped address of req->assoclen
 * @sgt: the h/w link table, followed by IV
 */
काष्ठा aead_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक qm_sg_bytes;
	dma_addr_t qm_sg_dma;
	अचिन्हित पूर्णांक assoclen;
	dma_addr_t assoclen_dma;
	काष्ठा dpaa2_sg_entry sgt[];
पूर्ण;

/*
 * skcipher_edesc - s/w-extended skcipher descriptor
 * @src_nents: number of segments in input scatterlist
 * @dst_nents: number of segments in output scatterlist
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @qm_sg_bytes: length of dma mapped qm_sg space
 * @qm_sg_dma: I/O भव address of h/w link table
 * @sgt: the h/w link table, followed by IV
 */
काष्ठा skcipher_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक qm_sg_bytes;
	dma_addr_t qm_sg_dma;
	काष्ठा dpaa2_sg_entry sgt[];
पूर्ण;

/*
 * ahash_edesc - s/w-extended ahash descriptor
 * @qm_sg_dma: I/O भव address of h/w link table
 * @src_nents: number of segments in input scatterlist
 * @qm_sg_bytes: length of dma mapped qm_sg space
 * @sgt: poपूर्णांकer to h/w link table
 */
काष्ठा ahash_edesc अणु
	dma_addr_t qm_sg_dma;
	पूर्णांक src_nents;
	पूर्णांक qm_sg_bytes;
	काष्ठा dpaa2_sg_entry sgt[];
पूर्ण;

/**
 * caam_flc - Flow Context (FLC)
 * @flc: Flow Context options
 * @sh_desc: Shared Descriptor
 */
काष्ठा caam_flc अणु
	u32 flc[16];
	u32 sh_desc[MAX_SDLEN];
पूर्ण ____cacheline_aligned;

क्रमागत optype अणु
	ENCRYPT = 0,
	DECRYPT,
	NUM_OP
पूर्ण;

/**
 * caam_request - the request काष्ठाure the driver application should fill जबतक
 *                submitting a job to driver.
 * @fd_flt: Frame list table defining input and output
 *          fd_flt[0] - FLE poपूर्णांकing to output buffer
 *          fd_flt[1] - FLE poपूर्णांकing to input buffer
 * @fd_flt_dma: DMA address क्रम the frame list table
 * @flc: Flow Context
 * @flc_dma: I/O भव address of Flow Context
 * @cbk: Callback function to invoke when job is completed
 * @ctx: arbit context attached with request by the application
 * @edesc: extended descriptor; poपूर्णांकs to one of अणुskcipher,aeadपूर्ण_edesc
 */
काष्ठा caam_request अणु
	काष्ठा dpaa2_fl_entry fd_flt[2];
	dma_addr_t fd_flt_dma;
	काष्ठा caam_flc *flc;
	dma_addr_t flc_dma;
	व्योम (*cbk)(व्योम *ctx, u32 err);
	व्योम *ctx;
	व्योम *edesc;
	काष्ठा skcipher_request fallback_req;
पूर्ण;

/**
 * dpaa2_caam_enqueue() - enqueue a crypto request
 * @dev: device associated with the DPSECI object
 * @req: poपूर्णांकer to caam_request
 */
पूर्णांक dpaa2_caam_enqueue(काष्ठा device *dev, काष्ठा caam_request *req);

#पूर्ण_अगर	/* _CAAMALG_QI2_H_ */
