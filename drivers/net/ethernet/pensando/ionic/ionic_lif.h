<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_LIF_H_
#घोषणा _IONIC_LIF_H_

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <uapi/linux/net_tstamp.h>
#समावेश <linux/dim.h>
#समावेश <linux/pci.h>
#समावेश "ionic_rx_filter.h"

#घोषणा IONIC_ADMINQ_LENGTH	16	/* must be a घातer of two */
#घोषणा IONIC_NOTIFYQ_LENGTH	64	/* must be a घातer of two */

#घोषणा IONIC_MAX_NUM_NAPI_CNTR		(NAPI_POLL_WEIGHT + 1)
#घोषणा IONIC_MAX_NUM_SG_CNTR		(IONIC_TX_MAX_SG_ELEMS + 1)

#घोषणा ADD_ADDR	true
#घोषणा DEL_ADDR	false
#घोषणा CAN_SLEEP	true
#घोषणा CAN_NOT_SLEEP	false

#घोषणा IONIC_RX_COPYBREAK_DEFAULT	256
#घोषणा IONIC_TX_BUDGET_DEFAULT		256

काष्ठा ionic_tx_stats अणु
	u64 pkts;
	u64 bytes;
	u64 csum_none;
	u64 csum;
	u64 tso;
	u64 tso_bytes;
	u64 frags;
	u64 vlan_inserted;
	u64 clean;
	u64 linearize;
	u64 crc32_csum;
	u64 sg_cntr[IONIC_MAX_NUM_SG_CNTR];
	u64 dma_map_err;
	u64 hwstamp_valid;
	u64 hwstamp_invalid;
पूर्ण;

काष्ठा ionic_rx_stats अणु
	u64 pkts;
	u64 bytes;
	u64 csum_none;
	u64 csum_complete;
	u64 buffers_posted;
	u64 dropped;
	u64 vlan_stripped;
	u64 csum_error;
	u64 dma_map_err;
	u64 alloc_err;
	u64 hwstamp_valid;
	u64 hwstamp_invalid;
पूर्ण;

#घोषणा IONIC_QCQ_F_INITED		BIT(0)
#घोषणा IONIC_QCQ_F_SG			BIT(1)
#घोषणा IONIC_QCQ_F_INTR		BIT(2)
#घोषणा IONIC_QCQ_F_TX_STATS		BIT(3)
#घोषणा IONIC_QCQ_F_RX_STATS		BIT(4)
#घोषणा IONIC_QCQ_F_NOTIFYQ		BIT(5)

काष्ठा ionic_napi_stats अणु
	u64 poll_count;
	u64 work_करोne_cntr[IONIC_MAX_NUM_NAPI_CNTR];
पूर्ण;

काष्ठा ionic_qcq अणु
	व्योम *q_base;
	dma_addr_t q_base_pa;
	u32 q_size;
	व्योम *cq_base;
	dma_addr_t cq_base_pa;
	u32 cq_size;
	व्योम *sg_base;
	dma_addr_t sg_base_pa;
	u32 sg_size;
	काष्ठा dim dim;
	काष्ठा ionic_queue q;
	काष्ठा ionic_cq cq;
	काष्ठा ionic_पूर्णांकr_info पूर्णांकr;
	काष्ठा napi_काष्ठा napi;
	काष्ठा ionic_napi_stats napi_stats;
	अचिन्हित पूर्णांक flags;
	काष्ठा dentry *dentry;
पूर्ण;

#घोषणा q_to_qcq(q)		container_of(q, काष्ठा ionic_qcq, q)
#घोषणा q_to_tx_stats(q)	(&(q)->lअगर->txqstats[(q)->index])
#घोषणा q_to_rx_stats(q)	(&(q)->lअगर->rxqstats[(q)->index])
#घोषणा napi_to_qcq(napi)	container_of(napi, काष्ठा ionic_qcq, napi)
#घोषणा napi_to_cq(napi)	(&napi_to_qcq(napi)->cq)

क्रमागत ionic_deferred_work_type अणु
	IONIC_DW_TYPE_RX_MODE,
	IONIC_DW_TYPE_RX_ADDR_ADD,
	IONIC_DW_TYPE_RX_ADDR_DEL,
	IONIC_DW_TYPE_LINK_STATUS,
	IONIC_DW_TYPE_LIF_RESET,
पूर्ण;

काष्ठा ionic_deferred_work अणु
	काष्ठा list_head list;
	क्रमागत ionic_deferred_work_type type;
	जोड़ अणु
		अचिन्हित पूर्णांक rx_mode;
		u8 addr[ETH_ALEN];
		u8 fw_status;
	पूर्ण;
पूर्ण;

काष्ठा ionic_deferred अणु
	spinlock_t lock;		/* lock क्रम deferred work list */
	काष्ठा list_head list;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा ionic_lअगर_sw_stats अणु
	u64 tx_packets;
	u64 tx_bytes;
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_tso;
	u64 tx_tso_bytes;
	u64 tx_csum_none;
	u64 tx_csum;
	u64 rx_csum_none;
	u64 rx_csum_complete;
	u64 rx_csum_error;
	u64 tx_hwstamp_valid;
	u64 tx_hwstamp_invalid;
	u64 rx_hwstamp_valid;
	u64 rx_hwstamp_invalid;
	u64 hw_tx_dropped;
	u64 hw_rx_dropped;
	u64 hw_rx_over_errors;
	u64 hw_rx_missed_errors;
	u64 hw_tx_पातed_errors;
पूर्ण;

क्रमागत ionic_lअगर_state_flags अणु
	IONIC_LIF_F_INITED,
	IONIC_LIF_F_SW_DEBUG_STATS,
	IONIC_LIF_F_UP,
	IONIC_LIF_F_LINK_CHECK_REQUESTED,
	IONIC_LIF_F_FW_RESET,
	IONIC_LIF_F_SPLIT_INTR,
	IONIC_LIF_F_BROKEN,
	IONIC_LIF_F_TX_DIM_INTR,
	IONIC_LIF_F_RX_DIM_INTR,

	/* leave this as last */
	IONIC_LIF_F_STATE_SIZE
पूर्ण;

काष्ठा ionic_qtype_info अणु
	u8  version;
	u8  supported;
	u64 features;
	u16 desc_sz;
	u16 comp_sz;
	u16 sg_desc_sz;
	u16 max_sg_elems;
	u16 sg_desc_stride;
पूर्ण;

काष्ठा ionic_phc;

#घोषणा IONIC_LIF_NAME_MAX_SZ		32
काष्ठा ionic_lअगर अणु
	काष्ठा net_device *netdev;
	DECLARE_BITMAP(state, IONIC_LIF_F_STATE_SIZE);
	काष्ठा ionic *ionic;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक hw_index;
	काष्ठा mutex queue_lock;	/* lock क्रम queue काष्ठाures */
	spinlock_t adminq_lock;		/* lock क्रम AdminQ operations */
	काष्ठा ionic_qcq *adminqcq;
	काष्ठा ionic_qcq *notअगरyqcq;
	काष्ठा ionic_qcq **txqcqs;
	काष्ठा ionic_qcq *hwstamp_txq;
	काष्ठा ionic_tx_stats *txqstats;
	काष्ठा ionic_qcq **rxqcqs;
	काष्ठा ionic_qcq *hwstamp_rxq;
	काष्ठा ionic_rx_stats *rxqstats;
	काष्ठा ionic_deferred deferred;
	काष्ठा work_काष्ठा tx_समयout_work;
	u64 last_eid;
	अचिन्हित पूर्णांक kern_pid;
	u64 __iomem *kern_dbpage;
	अचिन्हित पूर्णांक neqs;
	अचिन्हित पूर्णांक nxqs;
	अचिन्हित पूर्णांक ntxq_descs;
	अचिन्हित पूर्णांक nrxq_descs;
	u32 rx_copyअवरोध;
	u64 rxq_features;
	अचिन्हित पूर्णांक rx_mode;
	u64 hw_features;
	bool रेजिस्टरed;
	bool mc_overflow;
	bool uc_overflow;
	u16 lअगर_type;
	अचिन्हित पूर्णांक nmcast;
	अचिन्हित पूर्णांक nucast;
	अक्षर name[IONIC_LIF_NAME_MAX_SZ];

	जोड़ ionic_lअगर_identity *identity;
	काष्ठा ionic_lअगर_info *info;
	dma_addr_t info_pa;
	u32 info_sz;
	काष्ठा ionic_qtype_info qtype_info[IONIC_QTYPE_MAX];

	u16 rss_types;
	u8 rss_hash_key[IONIC_RSS_HASH_KEY_SIZE];
	u8 *rss_ind_tbl;
	dma_addr_t rss_ind_tbl_pa;
	u32 rss_ind_tbl_sz;

	काष्ठा ionic_rx_filters rx_filters;
	u32 rx_coalesce_usecs;		/* what the user asked क्रम */
	u32 rx_coalesce_hw;		/* what the hw is using */
	u32 tx_coalesce_usecs;		/* what the user asked क्रम */
	u32 tx_coalesce_hw;		/* what the hw is using */
	अचिन्हित दीर्घ *dbid_inuse;
	अचिन्हित पूर्णांक dbid_count;

	काष्ठा ionic_phc *phc;

	काष्ठा dentry *dentry;
पूर्ण;

काष्ठा ionic_phc अणु
	spinlock_t lock; /* lock क्रम cc and tc */
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;

	काष्ठा mutex config_lock; /* lock क्रम ts_config */
	काष्ठा hwtstamp_config ts_config;
	u64 ts_config_rx_filt;
	u32 ts_config_tx_mode;

	u32 init_cc_mult;
	दीर्घ aux_work_delay;

	काष्ठा ptp_घड़ी_info ptp_info;
	काष्ठा ptp_घड़ी *ptp;
	काष्ठा ionic_lअगर *lअगर;
पूर्ण;

काष्ठा ionic_queue_params अणु
	अचिन्हित पूर्णांक nxqs;
	अचिन्हित पूर्णांक ntxq_descs;
	अचिन्हित पूर्णांक nrxq_descs;
	अचिन्हित पूर्णांक पूर्णांकr_split;
	u64 rxq_features;
पूर्ण;

अटल अंतरभूत व्योम ionic_init_queue_params(काष्ठा ionic_lअगर *lअगर,
					   काष्ठा ionic_queue_params *qparam)
अणु
	qparam->nxqs = lअगर->nxqs;
	qparam->ntxq_descs = lअगर->ntxq_descs;
	qparam->nrxq_descs = lअगर->nrxq_descs;
	qparam->पूर्णांकr_split = test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state);
	qparam->rxq_features = lअगर->rxq_features;
पूर्ण

अटल अंतरभूत u32 ionic_coal_usec_to_hw(काष्ठा ionic *ionic, u32 usecs)
अणु
	u32 mult = le32_to_cpu(ionic->ident.dev.पूर्णांकr_coal_mult);
	u32 भाग = le32_to_cpu(ionic->ident.dev.पूर्णांकr_coal_भाग);

	/* Div-by-zero should never be an issue, but check anyway */
	अगर (!भाग || !mult)
		वापस 0;

	/* Round up in हाल usecs is बंद to the next hw unit */
	usecs += (भाग / mult) >> 1;

	/* Convert from usecs to device units */
	वापस (usecs * mult) / भाग;
पूर्ण

व्योम ionic_link_status_check_request(काष्ठा ionic_lअगर *lअगर, bool can_sleep);
व्योम ionic_get_stats64(काष्ठा net_device *netdev,
		       काष्ठा rtnl_link_stats64 *ns);
व्योम ionic_lअगर_deferred_enqueue(काष्ठा ionic_deferred *def,
				काष्ठा ionic_deferred_work *work);
पूर्णांक ionic_lअगर_alloc(काष्ठा ionic *ionic);
पूर्णांक ionic_lअगर_init(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_मुक्त(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_deinit(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_lअगर_रेजिस्टर(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_unरेजिस्टर(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_lअगर_identअगरy(काष्ठा ionic *ionic, u8 lअगर_type,
		       जोड़ ionic_lअगर_identity *lअगर_ident);
पूर्णांक ionic_lअगर_size(काष्ठा ionic *ionic);

#अगर IS_ENABLED(CONFIG_PTP_1588_CLOCK)
पूर्णांक ionic_lअगर_hwstamp_replay(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_lअगर_hwstamp_set(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr);
पूर्णांक ionic_lअगर_hwstamp_get(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr);
kसमय_प्रकार ionic_lअगर_phc_kसमय(काष्ठा ionic_lअगर *lअगर, u64 counter);
व्योम ionic_lअगर_रेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_unरेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_alloc_phc(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_lअगर_मुक्त_phc(काष्ठा ionic_lअगर *lअगर);
#अन्यथा
अटल अंतरभूत पूर्णांक ionic_lअगर_hwstamp_replay(काष्ठा ionic_lअगर *lअगर)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ionic_lअगर_hwstamp_set(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ionic_lअगर_hwstamp_get(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत kसमय_प्रकार ionic_lअगर_phc_kसमय(काष्ठा ionic_lअगर *lअगर, u64 counter)
अणु
	वापस ns_to_kसमय(0);
पूर्ण

अटल अंतरभूत व्योम ionic_lअगर_रेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर) अणुपूर्ण
अटल अंतरभूत व्योम ionic_lअगर_unरेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर) अणुपूर्ण
अटल अंतरभूत व्योम ionic_lअगर_alloc_phc(काष्ठा ionic_lअगर *lअगर) अणुपूर्ण
अटल अंतरभूत व्योम ionic_lअगर_मुक्त_phc(काष्ठा ionic_lअगर *lअगर) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक ionic_lअगर_create_hwstamp_txq(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_lअगर_create_hwstamp_rxq(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_lअगर_config_hwstamp_rxq_all(काष्ठा ionic_lअगर *lअगर, bool rx_all);
पूर्णांक ionic_lअगर_set_hwstamp_txmode(काष्ठा ionic_lअगर *lअगर, u16 txstamp_mode);
पूर्णांक ionic_lअगर_set_hwstamp_rxfilt(काष्ठा ionic_lअगर *lअगर, u64 pkt_class);

पूर्णांक ionic_lअगर_rss_config(काष्ठा ionic_lअगर *lअगर, u16 types,
			 स्थिर u8 *key, स्थिर u32 *indir);
पूर्णांक ionic_reconfigure_queues(काष्ठा ionic_lअगर *lअगर,
			     काष्ठा ionic_queue_params *qparam);

अटल अंतरभूत व्योम debug_stats_txq_post(काष्ठा ionic_queue *q, bool dbell)
अणु
	काष्ठा ionic_txq_desc *desc = &q->txq[q->head_idx];
	u8 num_sg_elems;

	q->dbell_count += dbell;

	num_sg_elems = ((le64_to_cpu(desc->cmd) >> IONIC_TXQ_DESC_NSGE_SHIFT)
						& IONIC_TXQ_DESC_NSGE_MASK);
	अगर (num_sg_elems > (IONIC_MAX_NUM_SG_CNTR - 1))
		num_sg_elems = IONIC_MAX_NUM_SG_CNTR - 1;

	q->lअगर->txqstats[q->index].sg_cntr[num_sg_elems]++;
पूर्ण

अटल अंतरभूत व्योम debug_stats_napi_poll(काष्ठा ionic_qcq *qcq,
					 अचिन्हित पूर्णांक work_करोne)
अणु
	qcq->napi_stats.poll_count++;

	अगर (work_करोne > (IONIC_MAX_NUM_NAPI_CNTR - 1))
		work_करोne = IONIC_MAX_NUM_NAPI_CNTR - 1;

	qcq->napi_stats.work_करोne_cntr[work_करोne]++;
पूर्ण

#घोषणा DEBUG_STATS_CQE_CNT(cq)		((cq)->compl_count++)
#घोषणा DEBUG_STATS_RX_BUFF_CNT(q)	((q)->lअगर->rxqstats[q->index].buffers_posted++)
#घोषणा DEBUG_STATS_TXQ_POST(q, dbell)  debug_stats_txq_post(q, dbell)
#घोषणा DEBUG_STATS_NAPI_POLL(qcq, work_करोne) \
	debug_stats_napi_poll(qcq, work_करोne)

#पूर्ण_अगर /* _IONIC_LIF_H_ */
