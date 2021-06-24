<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_hw.h
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#अगर_अघोषित __EHEA_HW_H__
#घोषणा __EHEA_HW_H__

#घोषणा QPX_SQA_VALUE   EHEA_BMASK_IBM(48, 63)
#घोषणा QPX_RQ1A_VALUE  EHEA_BMASK_IBM(48, 63)
#घोषणा QPX_RQ2A_VALUE  EHEA_BMASK_IBM(48, 63)
#घोषणा QPX_RQ3A_VALUE  EHEA_BMASK_IBM(48, 63)

#घोषणा QPTEMM_OFFSET(x) दुरत्व(काष्ठा ehea_qptemm, x)

काष्ठा ehea_qptemm अणु
	u64 qpx_hcr;
	u64 qpx_c;
	u64 qpx_herr;
	u64 qpx_aer;
	u64 qpx_sqa;
	u64 qpx_sqc;
	u64 qpx_rq1a;
	u64 qpx_rq1c;
	u64 qpx_st;
	u64 qpx_aerr;
	u64 qpx_tenure;
	u64 qpx_reserved1[(0x098 - 0x058) / 8];
	u64 qpx_portp;
	u64 qpx_reserved2[(0x100 - 0x0A0) / 8];
	u64 qpx_t;
	u64 qpx_sqhp;
	u64 qpx_sqptp;
	u64 qpx_reserved3[(0x140 - 0x118) / 8];
	u64 qpx_sqwsize;
	u64 qpx_reserved4[(0x170 - 0x148) / 8];
	u64 qpx_sqsize;
	u64 qpx_reserved5[(0x1B0 - 0x178) / 8];
	u64 qpx_sigt;
	u64 qpx_wqecnt;
	u64 qpx_rq1hp;
	u64 qpx_rq1ptp;
	u64 qpx_rq1size;
	u64 qpx_reserved6[(0x220 - 0x1D8) / 8];
	u64 qpx_rq1wsize;
	u64 qpx_reserved7[(0x240 - 0x228) / 8];
	u64 qpx_pd;
	u64 qpx_scqn;
	u64 qpx_rcqn;
	u64 qpx_aeqn;
	u64 reserved49;
	u64 qpx_ram;
	u64 qpx_reserved8[(0x300 - 0x270) / 8];
	u64 qpx_rq2a;
	u64 qpx_rq2c;
	u64 qpx_rq2hp;
	u64 qpx_rq2ptp;
	u64 qpx_rq2size;
	u64 qpx_rq2wsize;
	u64 qpx_rq2th;
	u64 qpx_rq3a;
	u64 qpx_rq3c;
	u64 qpx_rq3hp;
	u64 qpx_rq3ptp;
	u64 qpx_rq3size;
	u64 qpx_rq3wsize;
	u64 qpx_rq3th;
	u64 qpx_lpn;
	u64 qpx_reserved9[(0x400 - 0x378) / 8];
	u64 reserved_ext[(0x500 - 0x400) / 8];
	u64 reserved2[(0x1000 - 0x500) / 8];
पूर्ण;

#घोषणा MRx_HCR_LPARID_VALID EHEA_BMASK_IBM(0, 0)

#घोषणा MRMWMM_OFFSET(x) दुरत्व(काष्ठा ehea_mrmwmm, x)

काष्ठा ehea_mrmwmm अणु
	u64 mrx_hcr;
	u64 mrx_c;
	u64 mrx_herr;
	u64 mrx_aer;
	u64 mrx_pp;
	u64 reserved1;
	u64 reserved2;
	u64 reserved3;
	u64 reserved4[(0x200 - 0x40) / 8];
	u64 mrx_ctl[64];
पूर्ण;

#घोषणा QPEDMM_OFFSET(x) दुरत्व(काष्ठा ehea_qpedmm, x)

काष्ठा ehea_qpedmm अणु

	u64 reserved0[(0x400) / 8];
	u64 qpedx_phh;
	u64 qpedx_ppsgp;
	u64 qpedx_ppsgu;
	u64 qpedx_ppdgp;
	u64 qpedx_ppdgu;
	u64 qpedx_aph;
	u64 qpedx_apsgp;
	u64 qpedx_apsgu;
	u64 qpedx_apdgp;
	u64 qpedx_apdgu;
	u64 qpedx_apav;
	u64 qpedx_apsav;
	u64 qpedx_hcr;
	u64 reserved1[4];
	u64 qpedx_rrl0;
	u64 qpedx_rrrkey0;
	u64 qpedx_rrva0;
	u64 reserved2;
	u64 qpedx_rrl1;
	u64 qpedx_rrrkey1;
	u64 qpedx_rrva1;
	u64 reserved3;
	u64 qpedx_rrl2;
	u64 qpedx_rrrkey2;
	u64 qpedx_rrva2;
	u64 reserved4;
	u64 qpedx_rrl3;
	u64 qpedx_rrrkey3;
	u64 qpedx_rrva3;
पूर्ण;

#घोषणा CQX_FECADDER EHEA_BMASK_IBM(32, 63)
#घोषणा CQX_FEC_CQE_CNT EHEA_BMASK_IBM(32, 63)
#घोषणा CQX_N1_GENERATE_COMP_EVENT EHEA_BMASK_IBM(0, 0)
#घोषणा CQX_EP_EVENT_PENDING EHEA_BMASK_IBM(0, 0)

#घोषणा CQTEMM_OFFSET(x) दुरत्व(काष्ठा ehea_cqtemm, x)

काष्ठा ehea_cqtemm अणु
	u64 cqx_hcr;
	u64 cqx_c;
	u64 cqx_herr;
	u64 cqx_aer;
	u64 cqx_ptp;
	u64 cqx_tp;
	u64 cqx_fec;
	u64 cqx_feca;
	u64 cqx_ep;
	u64 cqx_eq;
	u64 reserved1;
	u64 cqx_n0;
	u64 cqx_n1;
	u64 reserved2[(0x1000 - 0x60) / 8];
पूर्ण;

#घोषणा EQTEMM_OFFSET(x) दुरत्व(काष्ठा ehea_eqtemm, x)

काष्ठा ehea_eqtemm अणु
	u64 eqx_hcr;
	u64 eqx_c;
	u64 eqx_herr;
	u64 eqx_aer;
	u64 eqx_ptp;
	u64 eqx_tp;
	u64 eqx_ssba;
	u64 eqx_psba;
	u64 eqx_cec;
	u64 eqx_meql;
	u64 eqx_xisbi;
	u64 eqx_xisc;
	u64 eqx_it;
पूर्ण;

/*
 * These access functions will be changed when the dissuccsion about
 * the new access methods क्रम POWER has settled.
 */

अटल अंतरभूत u64 epa_load(काष्ठा h_epa epa, u32 offset)
अणु
	वापस __raw_पढ़ोq((व्योम __iomem *)(epa.addr + offset));
पूर्ण

अटल अंतरभूत व्योम epa_store(काष्ठा h_epa epa, u32 offset, u64 value)
अणु
	__raw_ग_लिखोq(value, (व्योम __iomem *)(epa.addr + offset));
	epa_load(epa, offset);	/* synchronize explicitly to eHEA */
पूर्ण

अटल अंतरभूत व्योम epa_store_acc(काष्ठा h_epa epa, u32 offset, u64 value)
अणु
	__raw_ग_लिखोq(value, (व्योम __iomem *)(epa.addr + offset));
पूर्ण

#घोषणा epa_store_cq(epa, offset, value)\
	epa_store(epa, CQTEMM_OFFSET(offset), value)
#घोषणा epa_load_cq(epa, offset)\
	epa_load(epa, CQTEMM_OFFSET(offset))

अटल अंतरभूत व्योम ehea_update_sqa(काष्ठा ehea_qp *qp, u16 nr_wqes)
अणु
	काष्ठा h_epa epa = qp->epas.kernel;
	epa_store_acc(epa, QPTEMM_OFFSET(qpx_sqa),
		      EHEA_BMASK_SET(QPX_SQA_VALUE, nr_wqes));
पूर्ण

अटल अंतरभूत व्योम ehea_update_rq3a(काष्ठा ehea_qp *qp, u16 nr_wqes)
अणु
	काष्ठा h_epa epa = qp->epas.kernel;
	epa_store_acc(epa, QPTEMM_OFFSET(qpx_rq3a),
		      EHEA_BMASK_SET(QPX_RQ1A_VALUE, nr_wqes));
पूर्ण

अटल अंतरभूत व्योम ehea_update_rq2a(काष्ठा ehea_qp *qp, u16 nr_wqes)
अणु
	काष्ठा h_epa epa = qp->epas.kernel;
	epa_store_acc(epa, QPTEMM_OFFSET(qpx_rq2a),
		      EHEA_BMASK_SET(QPX_RQ2A_VALUE, nr_wqes));
पूर्ण

अटल अंतरभूत व्योम ehea_update_rq1a(काष्ठा ehea_qp *qp, u16 nr_wqes)
अणु
	काष्ठा h_epa epa = qp->epas.kernel;
	epa_store_acc(epa, QPTEMM_OFFSET(qpx_rq1a),
		      EHEA_BMASK_SET(QPX_RQ3A_VALUE, nr_wqes));
पूर्ण

अटल अंतरभूत व्योम ehea_update_feca(काष्ठा ehea_cq *cq, u32 nr_cqes)
अणु
	काष्ठा h_epa epa = cq->epas.kernel;
	epa_store_acc(epa, CQTEMM_OFFSET(cqx_feca),
		      EHEA_BMASK_SET(CQX_FECADDER, nr_cqes));
पूर्ण

अटल अंतरभूत व्योम ehea_reset_cq_n1(काष्ठा ehea_cq *cq)
अणु
	काष्ठा h_epa epa = cq->epas.kernel;
	epa_store_cq(epa, cqx_n1,
		     EHEA_BMASK_SET(CQX_N1_GENERATE_COMP_EVENT, 1));
पूर्ण

अटल अंतरभूत व्योम ehea_reset_cq_ep(काष्ठा ehea_cq *my_cq)
अणु
	काष्ठा h_epa epa = my_cq->epas.kernel;
	epa_store_acc(epa, CQTEMM_OFFSET(cqx_ep),
		      EHEA_BMASK_SET(CQX_EP_EVENT_PENDING, 0));
पूर्ण

#पूर्ण_अगर	/* __EHEA_HW_H__ */
