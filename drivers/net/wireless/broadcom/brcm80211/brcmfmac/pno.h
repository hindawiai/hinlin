<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2016 Broadcom
 */
#अगर_अघोषित _BRCMF_PNO_H
#घोषणा _BRCMF_PNO_H

#घोषणा BRCMF_PNO_SCAN_COMPLETE			1
#घोषणा BRCMF_PNO_MAX_PFN_COUNT			16
#घोषणा BRCMF_PNO_SCHED_SCAN_MIN_PERIOD	10
#घोषणा BRCMF_PNO_SCHED_SCAN_MAX_PERIOD	508

/* क्रमward declaration */
काष्ठा brcmf_pno_info;

/**
 * brcmf_pno_start_sched_scan - initiate scheduled scan on device.
 *
 * @अगरp: पूर्णांकerface object used.
 * @req: configuration parameters क्रम scheduled scan.
 */
पूर्णांक brcmf_pno_start_sched_scan(काष्ठा brcmf_अगर *अगरp,
			       काष्ठा cfg80211_sched_scan_request *req);

/**
 * brcmf_pno_stop_sched_scan - terminate scheduled scan on device.
 *
 * @अगरp: पूर्णांकerface object used.
 * @reqid: unique identअगरier of scan to be stopped.
 */
पूर्णांक brcmf_pno_stop_sched_scan(काष्ठा brcmf_अगर *अगरp, u64 reqid);

/**
 * brcmf_pno_wiphy_params - fill scheduled scan parameters in wiphy instance.
 *
 * @wiphy: wiphy instance to be used.
 * @gscan: indicates whether the device has support क्रम g-scan feature.
 */
व्योम brcmf_pno_wiphy_params(काष्ठा wiphy *wiphy, bool gscan);

/**
 * brcmf_pno_attach - allocate and attach module inक्रमmation.
 *
 * @cfg: cfg80211 context used.
 */
पूर्णांक brcmf_pno_attach(काष्ठा brcmf_cfg80211_info *cfg);

/**
 * brcmf_pno_detach - detach and मुक्त module inक्रमmation.
 *
 * @cfg: cfg80211 context used.
 */
व्योम brcmf_pno_detach(काष्ठा brcmf_cfg80211_info *cfg);

/**
 * brcmf_pno_find_reqid_by_bucket - find request id क्रम given bucket index.
 *
 * @pi: pno instance used.
 * @bucket: index of firmware bucket.
 */
u64 brcmf_pno_find_reqid_by_bucket(काष्ठा brcmf_pno_info *pi, u32 bucket);

/**
 * brcmf_pno_get_bucket_map - determine bucket map क्रम given netinfo.
 *
 * @pi: pno instance used.
 * @netinfo: netinfo to compare with bucket configuration.
 */
u32 brcmf_pno_get_bucket_map(काष्ठा brcmf_pno_info *pi,
			     काष्ठा brcmf_pno_net_info_le *netinfo);

#पूर्ण_अगर /* _BRCMF_PNO_H */
