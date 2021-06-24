<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित _HNS_DSAF_PPE_H
#घोषणा _HNS_DSAF_PPE_H

#समावेश <linux/platक्रमm_device.h>

#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_rcb.h"

#घोषणा HNS_PPE_SERVICE_NW_ENGINE_NUM DSAF_COMM_CHN
#घोषणा HNS_PPE_DEBUG_NW_ENGINE_NUM 1
#घोषणा HNS_PPE_COM_NUM DSAF_COMM_DEV_NUM

#घोषणा PPE_COMMON_REG_OFFSET 0x70000
#घोषणा PPE_REG_OFFSET 0x10000

#घोषणा ETH_PPE_DUMP_NUM 576
#घोषणा ETH_PPE_STATIC_NUM 12

#घोषणा HNS_PPEV2_RSS_IND_TBL_SIZE 256
#घोषणा HNS_PPEV2_RSS_KEY_SIZE 40 /* in bytes or 320 bits */
#घोषणा HNS_PPEV2_RSS_KEY_NUM (HNS_PPEV2_RSS_KEY_SIZE / माप(u32))

#घोषणा HNS_PPEV2_MAX_FRAME_LEN 0X980

क्रमागत ppe_qid_mode अणु
	PPE_QID_MODE0 = 0, /* fixed queue id mode */
	PPE_QID_MODE1,	   /* चयन:128VM non चयन:6Port/4VM/4TC */
	PPE_QID_MODE2,	   /* चयन:32VM/4TC non चयन:6Port/16VM */
	PPE_QID_MODE3,	   /* चयन:4TC/8RSS non चयन:2Port/64VM */
	PPE_QID_MODE4,	   /* चयन:8VM/16RSS non चयन:2Port/16VM/4TC */
	PPE_QID_MODE5,	   /* चयन:16VM/8TC non चयन:6Port/16RSS */
	PPE_QID_MODE6,	   /* चयन:32VM/4RSS non चयन:6Port/2VM/8TC */
	PPE_QID_MODE7,	   /* चयन:32RSS non चयन:2Port/8VM/8TC */
	PPE_QID_MODE8,	   /* चयन:6VM/4TC/4RSS non चयन:2Port/16VM/4RSS */
	PPE_QID_MODE9,	   /* non चयन:2Port/32VM/2RSS */
	PPE_QID_MODE10,	   /* non चयन:2Port/32RSS */
	PPE_QID_MODE11,	   /* non चयन:2Port/4TC/16RSS */
पूर्ण;

क्रमागत ppe_port_mode अणु
	PPE_MODE_GE = 0,
	PPE_MODE_XGE,
पूर्ण;

क्रमागत ppe_common_mode अणु
	PPE_COMMON_MODE_DEBUG = 0,
	PPE_COMMON_MODE_SERVICE,
	PPE_COMMON_MODE_MAX
पूर्ण;

काष्ठा hns_ppe_hw_stats अणु
	u64 rx_pkts_from_sw;
	u64 rx_pkts;
	u64 rx_drop_no_bd;
	u64 rx_alloc_buf_fail;
	u64 rx_alloc_buf_रुको;
	u64 rx_drop_no_buf;
	u64 rx_err_fअगरo_full;
	u64 tx_bd_क्रमm_rcb;
	u64 tx_pkts_from_rcb;
	u64 tx_pkts;
	u64 tx_err_fअगरo_empty;
	u64 tx_err_checksum;
पूर्ण;

काष्ठा hns_ppe_cb अणु
	काष्ठा device *dev;
	काष्ठा hns_ppe_cb *next;	/* poपूर्णांकer to next ppe device */
	काष्ठा ppe_common_cb *ppe_common_cb; /* beदीर्घ to */
	काष्ठा hns_ppe_hw_stats hw_stats;

	u8 index;	/* index in a ppe common device */
	u8 __iomem *io_base;
	पूर्णांक virq;
	u32 rss_indir_table[HNS_PPEV2_RSS_IND_TBL_SIZE]; /*shaकरोw indir tab */
	u32 rss_key[HNS_PPEV2_RSS_KEY_NUM]; /* rss hash key */
पूर्ण;

काष्ठा ppe_common_cb अणु
	काष्ठा device *dev;
	काष्ठा dsaf_device *dsaf_dev;
	u8 __iomem *io_base;

	क्रमागत ppe_common_mode ppe_mode;

	u8 comm_index;   /*ppe_common index*/

	u32 ppe_num;
	काष्ठा hns_ppe_cb ppe_cb[];

पूर्ण;

पूर्णांक hns_ppe_रुको_tx_fअगरo_clean(काष्ठा hns_ppe_cb *ppe_cb);
पूर्णांक hns_ppe_init(काष्ठा dsaf_device *dsaf_dev);

व्योम hns_ppe_uninit(काष्ठा dsaf_device *dsaf_dev);

व्योम hns_ppe_reset_common(काष्ठा dsaf_device *dsaf_dev, u8 ppe_common_index);

व्योम hns_ppe_update_stats(काष्ठा hns_ppe_cb *ppe_cb);

पूर्णांक hns_ppe_get_sset_count(पूर्णांक stringset);
पूर्णांक hns_ppe_get_regs_count(व्योम);
व्योम hns_ppe_get_regs(काष्ठा hns_ppe_cb *ppe_cb, व्योम *data);

व्योम hns_ppe_get_strings(काष्ठा hns_ppe_cb *ppe_cb, पूर्णांक stringset, u8 *data);
व्योम hns_ppe_get_stats(काष्ठा hns_ppe_cb *ppe_cb, u64 *data);
व्योम hns_ppe_set_tso_enable(काष्ठा hns_ppe_cb *ppe_cb, u32 value);
व्योम hns_ppe_set_rss_key(काष्ठा hns_ppe_cb *ppe_cb,
			 स्थिर u32 rss_key[HNS_PPEV2_RSS_KEY_NUM]);
व्योम hns_ppe_set_indir_table(काष्ठा hns_ppe_cb *ppe_cb,
			     स्थिर u32 rss_tab[HNS_PPEV2_RSS_IND_TBL_SIZE]);
#पूर्ण_अगर /* _HNS_DSAF_PPE_H */
