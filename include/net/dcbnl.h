<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008, Intel Corporation.
 *
 * Author: Lucy Liu <lucy.liu@पूर्णांकel.com>
 */

#अगर_अघोषित __NET_DCBNL_H__
#घोषणा __NET_DCBNL_H__

#समावेश <linux/dcbnl.h>

काष्ठा dcb_app_type अणु
	पूर्णांक	अगरindex;
	काष्ठा dcb_app	  app;
	काष्ठा list_head  list;
	u8	dcbx;
पूर्ण;

पूर्णांक dcb_setapp(काष्ठा net_device *, काष्ठा dcb_app *);
u8 dcb_getapp(काष्ठा net_device *, काष्ठा dcb_app *);
पूर्णांक dcb_ieee_setapp(काष्ठा net_device *, काष्ठा dcb_app *);
पूर्णांक dcb_ieee_delapp(काष्ठा net_device *, काष्ठा dcb_app *);
u8 dcb_ieee_getapp_mask(काष्ठा net_device *, काष्ठा dcb_app *);

काष्ठा dcb_ieee_app_prio_map अणु
	u64 map[IEEE_8021QAZ_MAX_TCS];
पूर्ण;
व्योम dcb_ieee_getapp_prio_dscp_mask_map(स्थिर काष्ठा net_device *dev,
					काष्ठा dcb_ieee_app_prio_map *p_map);

काष्ठा dcb_ieee_app_dscp_map अणु
	u8 map[64];
पूर्ण;
व्योम dcb_ieee_getapp_dscp_prio_mask_map(स्थिर काष्ठा net_device *dev,
					काष्ठा dcb_ieee_app_dscp_map *p_map);
u8 dcb_ieee_getapp_शेष_prio_mask(स्थिर काष्ठा net_device *dev);

पूर्णांक dcbnl_ieee_notअगरy(काष्ठा net_device *dev, पूर्णांक event, पूर्णांक cmd,
		      u32 seq, u32 pid);
पूर्णांक dcbnl_cee_notअगरy(काष्ठा net_device *dev, पूर्णांक event, पूर्णांक cmd,
		     u32 seq, u32 pid);

/*
 * Ops काष्ठा क्रम the netlink callbacks.  Used by DCB-enabled drivers through
 * the netdevice काष्ठा.
 */
काष्ठा dcbnl_rtnl_ops अणु
	/* IEEE 802.1Qaz std */
	पूर्णांक (*ieee_getets) (काष्ठा net_device *, काष्ठा ieee_ets *);
	पूर्णांक (*ieee_setets) (काष्ठा net_device *, काष्ठा ieee_ets *);
	पूर्णांक (*ieee_geपंचांगaxrate) (काष्ठा net_device *, काष्ठा ieee_maxrate *);
	पूर्णांक (*ieee_seपंचांगaxrate) (काष्ठा net_device *, काष्ठा ieee_maxrate *);
	पूर्णांक (*ieee_getqcn) (काष्ठा net_device *, काष्ठा ieee_qcn *);
	पूर्णांक (*ieee_setqcn) (काष्ठा net_device *, काष्ठा ieee_qcn *);
	पूर्णांक (*ieee_getqcnstats) (काष्ठा net_device *, काष्ठा ieee_qcn_stats *);
	पूर्णांक (*ieee_getpfc) (काष्ठा net_device *, काष्ठा ieee_pfc *);
	पूर्णांक (*ieee_setpfc) (काष्ठा net_device *, काष्ठा ieee_pfc *);
	पूर्णांक (*ieee_getapp) (काष्ठा net_device *, काष्ठा dcb_app *);
	पूर्णांक (*ieee_setapp) (काष्ठा net_device *, काष्ठा dcb_app *);
	पूर्णांक (*ieee_delapp) (काष्ठा net_device *, काष्ठा dcb_app *);
	पूर्णांक (*ieee_peer_getets) (काष्ठा net_device *, काष्ठा ieee_ets *);
	पूर्णांक (*ieee_peer_getpfc) (काष्ठा net_device *, काष्ठा ieee_pfc *);

	/* CEE std */
	u8   (*माला_लोtate)(काष्ठा net_device *);
	u8   (*setstate)(काष्ठा net_device *, u8);
	व्योम (*getpermhwaddr)(काष्ठा net_device *, u8 *);
	व्योम (*setpgtccfgtx)(काष्ठा net_device *, पूर्णांक, u8, u8, u8, u8);
	व्योम (*setpgbwgcfgtx)(काष्ठा net_device *, पूर्णांक, u8);
	व्योम (*setpgtccfgrx)(काष्ठा net_device *, पूर्णांक, u8, u8, u8, u8);
	व्योम (*setpgbwgcfgrx)(काष्ठा net_device *, पूर्णांक, u8);
	व्योम (*getpgtccfgtx)(काष्ठा net_device *, पूर्णांक, u8 *, u8 *, u8 *, u8 *);
	व्योम (*getpgbwgcfgtx)(काष्ठा net_device *, पूर्णांक, u8 *);
	व्योम (*getpgtccfgrx)(काष्ठा net_device *, पूर्णांक, u8 *, u8 *, u8 *, u8 *);
	व्योम (*getpgbwgcfgrx)(काष्ठा net_device *, पूर्णांक, u8 *);
	व्योम (*setpfccfg)(काष्ठा net_device *, पूर्णांक, u8);
	व्योम (*getpfccfg)(काष्ठा net_device *, पूर्णांक, u8 *);
	u8   (*setall)(काष्ठा net_device *);
	u8   (*अ_लोap)(काष्ठा net_device *, पूर्णांक, u8 *);
	पूर्णांक  (*getnumtcs)(काष्ठा net_device *, पूर्णांक, u8 *);
	पूर्णांक  (*setnumtcs)(काष्ठा net_device *, पूर्णांक, u8);
	u8   (*getpfcstate)(काष्ठा net_device *);
	व्योम (*setpfcstate)(काष्ठा net_device *, u8);
	व्योम (*getbcncfg)(काष्ठा net_device *, पूर्णांक, u32 *);
	व्योम (*setbcncfg)(काष्ठा net_device *, पूर्णांक, u32);
	व्योम (*getbcnrp)(काष्ठा net_device *, पूर्णांक, u8 *);
	व्योम (*setbcnrp)(काष्ठा net_device *, पूर्णांक, u8);
	पूर्णांक  (*setapp)(काष्ठा net_device *, u8, u16, u8);
	पूर्णांक  (*getapp)(काष्ठा net_device *, u8, u16);
	u8   (*getfeatcfg)(काष्ठा net_device *, पूर्णांक, u8 *);
	u8   (*setfeatcfg)(काष्ठा net_device *, पूर्णांक, u8);

	/* DCBX configuration */
	u8   (*getdcbx)(काष्ठा net_device *);
	u8   (*setdcbx)(काष्ठा net_device *, u8);

	/* peer apps */
	पूर्णांक (*peer_getappinfo)(काष्ठा net_device *, काष्ठा dcb_peer_app_info *,
			       u16 *);
	पूर्णांक (*peer_getapptable)(काष्ठा net_device *, काष्ठा dcb_app *);

	/* CEE peer */
	पूर्णांक (*cee_peer_getpg) (काष्ठा net_device *, काष्ठा cee_pg *);
	पूर्णांक (*cee_peer_getpfc) (काष्ठा net_device *, काष्ठा cee_pfc *);

	/* buffer settings */
	पूर्णांक (*dcbnl_getbuffer)(काष्ठा net_device *, काष्ठा dcbnl_buffer *);
	पूर्णांक (*dcbnl_रखो_बफfer)(काष्ठा net_device *, काष्ठा dcbnl_buffer *);
पूर्ण;

#पूर्ण_अगर /* __NET_DCBNL_H__ */
