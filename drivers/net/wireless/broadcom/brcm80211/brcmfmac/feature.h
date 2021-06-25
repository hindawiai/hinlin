<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित _BRCMF_FEATURE_H
#घोषणा _BRCMF_FEATURE_H

/*
 * Features:
 *
 * MBSS: multiple BSSID support (eg. guest network in AP mode).
 * MCHAN: multi-channel क्रम concurrent P2P.
 * PNO: preferred network offload.
 * WOWL: Wake-On-WLAN.
 * P2P: peer-to-peer
 * RSDB: Real Simultaneous Dual Band
 * TDLS: Tunneled Direct Link Setup
 * SCAN_RANDOM_MAC: Ranकरोm MAC during (net detect) scheduled scan.
 * WOWL_ND: WOWL net detect (PNO)
 * WOWL_GTK: (WOWL) GTK rekeying offload
 * WOWL_ARP_ND: ARP and Neighbor Discovery offload support during WOWL.
 * MFP: 802.11w Management Frame Protection.
 * GSCAN: enhanced scan offload feature.
 * FWSUP: Firmware supplicant.
 * MONITOR: firmware can pass monitor packets to host.
 * MONITOR_FLAG: firmware flags monitor packets.
 * MONITOR_FMT_RADIOTAP: firmware provides monitor packets with radiotap header
 * MONITOR_FMT_HW_RX_HDR: firmware provides monitor packets with hw/ucode header
 * DOT11H: firmware supports 802.11h
 * SAE: simultaneous authentication of equals
 * FWAUTH: Firmware authenticator
 */
#घोषणा BRCMF_FEAT_LIST \
	BRCMF_FEAT_DEF(MBSS) \
	BRCMF_FEAT_DEF(MCHAN) \
	BRCMF_FEAT_DEF(PNO) \
	BRCMF_FEAT_DEF(WOWL) \
	BRCMF_FEAT_DEF(P2P) \
	BRCMF_FEAT_DEF(RSDB) \
	BRCMF_FEAT_DEF(TDLS) \
	BRCMF_FEAT_DEF(SCAN_RANDOM_MAC) \
	BRCMF_FEAT_DEF(WOWL_ND) \
	BRCMF_FEAT_DEF(WOWL_GTK) \
	BRCMF_FEAT_DEF(WOWL_ARP_ND) \
	BRCMF_FEAT_DEF(MFP) \
	BRCMF_FEAT_DEF(GSCAN) \
	BRCMF_FEAT_DEF(FWSUP) \
	BRCMF_FEAT_DEF(MONITOR) \
	BRCMF_FEAT_DEF(MONITOR_FLAG) \
	BRCMF_FEAT_DEF(MONITOR_FMT_RADIOTAP) \
	BRCMF_FEAT_DEF(MONITOR_FMT_HW_RX_HDR) \
	BRCMF_FEAT_DEF(DOT11H) \
	BRCMF_FEAT_DEF(SAE) \
	BRCMF_FEAT_DEF(FWAUTH)

/*
 * Quirks:
 *
 * AUTO_AUTH: workaround needed क्रम स्वतःmatic authentication type.
 * NEED_MPC: driver needs to disable MPC during scanning operation.
 */
#घोषणा BRCMF_QUIRK_LIST \
	BRCMF_QUIRK_DEF(AUTO_AUTH) \
	BRCMF_QUIRK_DEF(NEED_MPC)

#घोषणा BRCMF_FEAT_DEF(_f) \
	BRCMF_FEAT_ ## _f,
/*
 * expand feature list to क्रमागतeration.
 */
क्रमागत brcmf_feat_id अणु
	BRCMF_FEAT_LIST
	BRCMF_FEAT_LAST
पूर्ण;
#अघोषित BRCMF_FEAT_DEF

#घोषणा BRCMF_QUIRK_DEF(_q) \
	BRCMF_FEAT_QUIRK_ ## _q,
/*
 * expand quirk list to क्रमागतeration.
 */
क्रमागत brcmf_feat_quirk अणु
	BRCMF_QUIRK_LIST
	BRCMF_FEAT_QUIRK_LAST
पूर्ण;
#अघोषित BRCMF_QUIRK_DEF

/**
 * brcmf_feat_attach() - determine features and quirks.
 *
 * @drvr: driver instance.
 */
व्योम brcmf_feat_attach(काष्ठा brcmf_pub *drvr);

/**
 * brcmf_feat_debugfs_create() - create debugfs entries.
 *
 * @drvr: driver instance.
 */
व्योम brcmf_feat_debugfs_create(काष्ठा brcmf_pub *drvr);

/**
 * brcmf_feat_is_enabled() - query feature.
 *
 * @अगरp: पूर्णांकerface instance.
 * @id: feature id to check.
 *
 * Return: true is feature is enabled; otherwise false.
 */
bool brcmf_feat_is_enabled(काष्ठा brcmf_अगर *अगरp, क्रमागत brcmf_feat_id id);

/**
 * brcmf_feat_is_quirk_enabled() - query chip quirk.
 *
 * @अगरp: पूर्णांकerface instance.
 * @quirk: quirk id to check.
 *
 * Return: true is quirk is enabled; otherwise false.
 */
bool brcmf_feat_is_quirk_enabled(काष्ठा brcmf_अगर *अगरp,
				 क्रमागत brcmf_feat_quirk quirk);

#पूर्ण_अगर /* _BRCMF_FEATURE_H */
