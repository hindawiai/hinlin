<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 NXP */

#अगर_अघोषित __DPAA2_QDMA_H
#घोषणा __DPAA2_QDMA_H

#घोषणा DPAA2_QDMA_STORE_SIZE 16
#घोषणा NUM_CH 8

काष्ठा dpaa2_qdma_sd_d अणु
	u32 rsv:32;
	जोड़ अणु
		काष्ठा अणु
			u32 ssd:12; /* souce stride distance */
			u32 sss:12; /* souce stride size */
			u32 rsv1:8;
		पूर्ण sdf;
		काष्ठा अणु
			u32 dsd:12; /* Destination stride distance */
			u32 dss:12; /* Destination stride size */
			u32 rsv2:8;
		पूर्ण ddf;
	पूर्ण df;
	u32 rbpcmd;	/* Route-by-port command */
	u32 cmd;
पूर्ण __attribute__((__packed__));

/* Source descriptor command पढ़ो transaction type क्रम RBP=0: */
/* coherent copy of cacheable memory */
#घोषणा QDMA_SD_CMD_RDTTYPE_COHERENT (0xb << 28)
/* Destination descriptor command ग_लिखो transaction type क्रम RBP=0: */
/* coherent copy of cacheable memory */
#घोषणा QDMA_DD_CMD_WRTTYPE_COHERENT (0x6 << 28)
#घोषणा LX2160_QDMA_DD_CMD_WRTTYPE_COHERENT (0xb << 28)

#घोषणा QMAN_FD_FMT_ENABLE	BIT(0) /* frame list table enable */
#घोषणा QMAN_FD_BMT_ENABLE	BIT(15) /* bypass memory translation */
#घोषणा QMAN_FD_BMT_DISABLE	(0) /* bypass memory translation */
#घोषणा QMAN_FD_SL_DISABLE	(0) /* लघु lengthe disabled */
#घोषणा QMAN_FD_SL_ENABLE	BIT(14) /* लघु lengthe enabled */

#घोषणा QDMA_FINAL_BIT_DISABLE	(0) /* final bit disable */
#घोषणा QDMA_FINAL_BIT_ENABLE	BIT(31) /* final bit enable */

#घोषणा QDMA_FD_SHORT_FORMAT	BIT(11) /* लघु क्रमmat */
#घोषणा QDMA_FD_LONG_FORMAT	(0) /* दीर्घ क्रमmat */
#घोषणा QDMA_SER_DISABLE	(8) /* no notअगरication */
#घोषणा QDMA_SER_CTX		BIT(8) /* notअगरication by FQD_CTX[fqid] */
#घोषणा QDMA_SER_DEST		(2 << 8) /* notअगरication by destination desc */
#घोषणा QDMA_SER_BOTH		(3 << 8) /* soruce and dest notअगरication */
#घोषणा QDMA_FD_SPF_ENALBE	BIT(30) /* source prefetch enable */

#घोषणा QMAN_FD_VA_ENABLE	BIT(14) /* Address used is भव address */
#घोषणा QMAN_FD_VA_DISABLE	(0)/* Address used is a real address */
/* Flow Context: 49bit physical address */
#घोषणा QMAN_FD_CBMT_ENABLE	BIT(15)
#घोषणा QMAN_FD_CBMT_DISABLE	(0) /* Flow Context: 64bit भव address */
#घोषणा QMAN_FD_SC_DISABLE	(0) /* stashing control */

#घोषणा QDMA_FL_FMT_SBF		(0x0) /* Single buffer frame */
#घोषणा QDMA_FL_FMT_SGE		(0x2) /* Scatter gather frame */
#घोषणा QDMA_FL_BMT_ENABLE	BIT(15) /* enable bypass memory translation */
#घोषणा QDMA_FL_BMT_DISABLE	(0x0) /* enable bypass memory translation */
#घोषणा QDMA_FL_SL_LONG		(0x0)/* दीर्घ length */
#घोषणा QDMA_FL_SL_SHORT	(0x1) /* लघु length */
#घोषणा QDMA_FL_F		(0x1)/* last frame list bit */

/*Description of Frame list table काष्ठाure*/
काष्ठा dpaa2_qdma_chan अणु
	काष्ठा dpaa2_qdma_engine	*qdma;
	काष्ठा virt_dma_chan		vchan;
	काष्ठा virt_dma_desc		vdesc;
	क्रमागत dma_status			status;
	u32				fqid;

	/* spinlock used by dpaa2 qdma driver */
	spinlock_t			queue_lock;
	काष्ठा dma_pool			*fd_pool;
	काष्ठा dma_pool			*fl_pool;
	काष्ठा dma_pool			*sdd_pool;

	काष्ठा list_head		comp_used;
	काष्ठा list_head		comp_मुक्त;

पूर्ण;

काष्ठा dpaa2_qdma_comp अणु
	dma_addr_t		fd_bus_addr;
	dma_addr_t		fl_bus_addr;
	dma_addr_t		desc_bus_addr;
	काष्ठा dpaa2_fd		*fd_virt_addr;
	काष्ठा dpaa2_fl_entry	*fl_virt_addr;
	काष्ठा dpaa2_qdma_sd_d	*desc_virt_addr;
	काष्ठा dpaa2_qdma_chan	*qchan;
	काष्ठा virt_dma_desc	vdesc;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा dpaa2_qdma_engine अणु
	काष्ठा dma_device	dma_dev;
	u32			n_chans;
	काष्ठा dpaa2_qdma_chan	chans[NUM_CH];
	पूर्णांक			qdma_wrtype_fixup;
	पूर्णांक			desc_allocated;

	काष्ठा dpaa2_qdma_priv *priv;
पूर्ण;

/*
 * dpaa2_qdma_priv - driver निजी data
 */
काष्ठा dpaa2_qdma_priv अणु
	पूर्णांक dpqdma_id;

	काष्ठा iommu_करोमुख्य	*iommu_करोमुख्य;
	काष्ठा dpdmai_attr	dpdmai_attr;
	काष्ठा device		*dev;
	काष्ठा fsl_mc_io	*mc_io;
	काष्ठा fsl_mc_device	*dpdmai_dev;
	u8			num_pairs;

	काष्ठा dpaa2_qdma_engine	*dpaa2_qdma;
	काष्ठा dpaa2_qdma_priv_per_prio	*ppriv;

	काष्ठा dpdmai_rx_queue_attr rx_queue_attr[DPDMAI_PRIO_NUM];
	u32 tx_fqid[DPDMAI_PRIO_NUM];
पूर्ण;

काष्ठा dpaa2_qdma_priv_per_prio अणु
	पूर्णांक req_fqid;
	पूर्णांक rsp_fqid;
	पूर्णांक prio;

	काष्ठा dpaa2_io_store *store;
	काष्ठा dpaa2_io_notअगरication_ctx nctx;

	काष्ठा dpaa2_qdma_priv *priv;
पूर्ण;

अटल काष्ठा soc_device_attribute soc_fixup_tuning[] = अणु
	अणु .family = "QorIQ LX2160A"पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* FD pool size: one FD + 3 Frame list + 2 source/destination descriptor */
#घोषणा FD_POOL_SIZE (माप(काष्ठा dpaa2_fd) + \
		माप(काष्ठा dpaa2_fl_entry) * 3 + \
		माप(काष्ठा dpaa2_qdma_sd_d) * 2)

अटल व्योम dpaa2_dpdmai_मुक्त_channels(काष्ठा dpaa2_qdma_engine *dpaa2_qdma);
अटल व्योम dpaa2_dpdmai_मुक्त_comp(काष्ठा dpaa2_qdma_chan *qchan,
				   काष्ठा list_head *head);
#पूर्ण_अगर /* __DPAA2_QDMA_H */
