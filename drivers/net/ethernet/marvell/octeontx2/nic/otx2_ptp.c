<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 PTP support क्रम ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश "otx2_common.h"
#समावेश "otx2_ptp.h"

अटल पूर्णांक otx2_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp_info, दीर्घ scaled_ppm)
अणु
	काष्ठा otx2_ptp *ptp = container_of(ptp_info, काष्ठा otx2_ptp,
					    ptp_info);
	काष्ठा ptp_req *req;

	अगर (!ptp->nic)
		वापस -ENODEV;

	req = otx2_mbox_alloc_msg_ptp_op(&ptp->nic->mbox);
	अगर (!req)
		वापस -ENOMEM;

	req->op = PTP_OP_ADJFINE;
	req->scaled_ppm = scaled_ppm;

	वापस otx2_sync_mbox_msg(&ptp->nic->mbox);
पूर्ण

अटल u64 ptp_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा otx2_ptp *ptp = container_of(cc, काष्ठा otx2_ptp, cycle_counter);
	काष्ठा ptp_req *req;
	काष्ठा ptp_rsp *rsp;
	पूर्णांक err;

	अगर (!ptp->nic)
		वापस 0;

	req = otx2_mbox_alloc_msg_ptp_op(&ptp->nic->mbox);
	अगर (!req)
		वापस 0;

	req->op = PTP_OP_GET_CLOCK;

	err = otx2_sync_mbox_msg(&ptp->nic->mbox);
	अगर (err)
		वापस 0;

	rsp = (काष्ठा ptp_rsp *)otx2_mbox_get_rsp(&ptp->nic->mbox.mbox, 0,
						  &req->hdr);
	अगर (IS_ERR(rsp))
		वापस 0;

	वापस rsp->clk;
पूर्ण

अटल पूर्णांक otx2_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp_info, s64 delta)
अणु
	काष्ठा otx2_ptp *ptp = container_of(ptp_info, काष्ठा otx2_ptp,
					    ptp_info);
	काष्ठा otx2_nic *pfvf = ptp->nic;

	mutex_lock(&pfvf->mbox.lock);
	समयcounter_adjसमय(&ptp->समय_counter, delta);
	mutex_unlock(&pfvf->mbox.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp_info,
			    काष्ठा बारpec64 *ts)
अणु
	काष्ठा otx2_ptp *ptp = container_of(ptp_info, काष्ठा otx2_ptp,
					    ptp_info);
	काष्ठा otx2_nic *pfvf = ptp->nic;
	u64 nsec;

	mutex_lock(&pfvf->mbox.lock);
	nsec = समयcounter_पढ़ो(&ptp->समय_counter);
	mutex_unlock(&pfvf->mbox.lock);

	*ts = ns_to_बारpec64(nsec);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp_info,
			    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा otx2_ptp *ptp = container_of(ptp_info, काष्ठा otx2_ptp,
					    ptp_info);
	काष्ठा otx2_nic *pfvf = ptp->nic;
	u64 nsec;

	nsec = बारpec64_to_ns(ts);

	mutex_lock(&pfvf->mbox.lock);
	समयcounter_init(&ptp->समय_counter, &ptp->cycle_counter, nsec);
	mutex_unlock(&pfvf->mbox.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_ptp_enable(काष्ठा ptp_घड़ी_info *ptp_info,
			   काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक otx2_ptp_init(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_ptp *ptp_ptr;
	काष्ठा cyclecounter *cc;
	काष्ठा ptp_req *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	/* check अगर PTP block is available */
	req = otx2_mbox_alloc_msg_ptp_op(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->op = PTP_OP_GET_CLOCK;

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण
	mutex_unlock(&pfvf->mbox.lock);

	ptp_ptr = kzalloc(माप(*ptp_ptr), GFP_KERNEL);
	अगर (!ptp_ptr) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	ptp_ptr->nic = pfvf;

	cc = &ptp_ptr->cycle_counter;
	cc->पढ़ो = ptp_cc_पढ़ो;
	cc->mask = CYCLECOUNTER_MASK(64);
	cc->mult = 1;
	cc->shअगरt = 0;

	समयcounter_init(&ptp_ptr->समय_counter, &ptp_ptr->cycle_counter,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	ptp_ptr->ptp_info = (काष्ठा ptp_घड़ी_info) अणु
		.owner          = THIS_MODULE,
		.name           = "OcteonTX2 PTP",
		.max_adj        = 1000000000ull,
		.n_ext_ts       = 0,
		.n_pins         = 0,
		.pps            = 0,
		.adjfine        = otx2_ptp_adjfine,
		.adjसमय        = otx2_ptp_adjसमय,
		.समय_लो64      = otx2_ptp_समय_लो,
		.समय_रखो64      = otx2_ptp_समय_रखो,
		.enable         = otx2_ptp_enable,
	पूर्ण;

	ptp_ptr->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&ptp_ptr->ptp_info, pfvf->dev);
	अगर (IS_ERR_OR_शून्य(ptp_ptr->ptp_घड़ी)) अणु
		err = ptp_ptr->ptp_घड़ी ?
		      PTR_ERR(ptp_ptr->ptp_घड़ी) : -ENODEV;
		kमुक्त(ptp_ptr);
		जाओ error;
	पूर्ण

	pfvf->ptp = ptp_ptr;

error:
	वापस err;
पूर्ण

व्योम otx2_ptp_destroy(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_ptp *ptp = pfvf->ptp;

	अगर (!ptp)
		वापस;

	ptp_घड़ी_unरेजिस्टर(ptp->ptp_घड़ी);
	kमुक्त(ptp);
	pfvf->ptp = शून्य;
पूर्ण

पूर्णांक otx2_ptp_घड़ी_index(काष्ठा otx2_nic *pfvf)
अणु
	अगर (!pfvf->ptp)
		वापस -ENODEV;

	वापस ptp_घड़ी_index(pfvf->ptp->ptp_घड़ी);
पूर्ण

पूर्णांक otx2_ptp_tstamp2समय(काष्ठा otx2_nic *pfvf, u64 tstamp, u64 *tsns)
अणु
	अगर (!pfvf->ptp)
		वापस -ENODEV;

	*tsns = समयcounter_cyc2समय(&pfvf->ptp->समय_counter, tstamp);

	वापस 0;
पूर्ण
