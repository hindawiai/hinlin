<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _DCB_CONFIG_H_
#घोषणा _DCB_CONFIG_H_

#समावेश <linux/dcbnl.h>
#समावेश "ixgbe_type.h"

/* DCB data काष्ठाures */

#घोषणा IXGBE_MAX_PACKET_BUFFERS 8
#घोषणा MAX_USER_PRIORITY        8
#घोषणा MAX_BW_GROUP             8
#घोषणा BW_PERCENT               100

#घोषणा DCB_TX_CONFIG            0
#घोषणा DCB_RX_CONFIG            1

/* DCB error Codes */
#घोषणा DCB_SUCCESS              0
#घोषणा DCB_ERR_CONFIG           -1
#घोषणा DCB_ERR_PARAM            -2

/* Transmit and receive Errors */
/* Error in bandwidth group allocation */
#घोषणा DCB_ERR_BW_GROUP        -3
/* Error in traffic class bandwidth allocation */
#घोषणा DCB_ERR_TC_BW           -4
/* Traffic class has both link strict and group strict enabled */
#घोषणा DCB_ERR_LS_GS           -5
/* Link strict traffic class has non zero bandwidth */
#घोषणा DCB_ERR_LS_BW_NONZERO   -6
/* Link strict bandwidth group has non zero bandwidth */
#घोषणा DCB_ERR_LS_BWG_NONZERO  -7
/*  Traffic class has zero bandwidth */
#घोषणा DCB_ERR_TC_BW_ZERO      -8

#घोषणा DCB_NOT_IMPLEMENTED      0x7FFFFFFF

काष्ठा dcb_pfc_tc_debug अणु
	u8  tc;
	u8  छोड़ो_status;
	u64 छोड़ो_quanta;
पूर्ण;

क्रमागत strict_prio_type अणु
	prio_none = 0,
	prio_group,
	prio_link
पूर्ण;

/* DCB capability definitions */
#घोषणा IXGBE_DCB_PG_SUPPORT        0x00000001
#घोषणा IXGBE_DCB_PFC_SUPPORT       0x00000002
#घोषणा IXGBE_DCB_BCN_SUPPORT       0x00000004
#घोषणा IXGBE_DCB_UP2TC_SUPPORT     0x00000008
#घोषणा IXGBE_DCB_GSP_SUPPORT       0x00000010

#घोषणा IXGBE_DCB_8_TC_SUPPORT      0x80

काष्ठा dcb_support अणु
	/* DCB capabilities */
	u32 capabilities;

	/* Each bit represents a number of TCs configurable in the hw.
	 * If 8 traffic classes can be configured, the value is 0x80.
	 */
	u8  traffic_classes;
	u8  pfc_traffic_classes;
पूर्ण;

/* Traffic class bandwidth allocation per direction */
काष्ठा tc_bw_alloc अणु
	u8 bwg_id;		  /* Bandwidth Group (BWG) ID */
	u8 bwg_percent;		  /* % of BWG's bandwidth */
	u8 link_percent;	  /* % of link bandwidth */
	u8 up_to_tc_biपंचांगap;	  /* User Priority to Traffic Class mapping */
	u16 data_credits_refill;  /* Credit refill amount in 64B granularity */
	u16 data_credits_max;	  /* Max credits क्रम a configured packet buffer
				   * in 64B granularity.*/
	क्रमागत strict_prio_type prio_type; /* Link or Group Strict Priority */
पूर्ण;

क्रमागत dcb_pfc_type अणु
	pfc_disabled = 0,
	pfc_enabled_full,
	pfc_enabled_tx,
	pfc_enabled_rx
पूर्ण;

/* Traffic class configuration */
काष्ठा tc_configuration अणु
	काष्ठा tc_bw_alloc path[2]; /* One each क्रम Tx/Rx */
	क्रमागत dcb_pfc_type  dcb_pfc; /* Class based flow control setting */

	u16 desc_credits_max; /* For Tx Descriptor arbitration */
	u8 tc; /* Traffic class (TC) */
पूर्ण;

काष्ठा dcb_num_tcs अणु
	u8 pg_tcs;
	u8 pfc_tcs;
पूर्ण;

काष्ठा ixgbe_dcb_config अणु
	काष्ठा dcb_support support;
	काष्ठा dcb_num_tcs num_tcs;
	काष्ठा tc_configuration tc_config[MAX_TRAFFIC_CLASS];
	u8     bw_percentage[2][MAX_BW_GROUP]; /* One each क्रम Tx/Rx */
	bool   pfc_mode_enable;

	u32  dcb_cfg_version; /* Not used...OS-specअगरic? */
	u32  link_speed; /* For bandwidth allocation validation purpose */
पूर्ण;

/* DCB driver APIs */
व्योम ixgbe_dcb_unpack_pfc(काष्ठा ixgbe_dcb_config *cfg, u8 *pfc_en);
व्योम ixgbe_dcb_unpack_refill(काष्ठा ixgbe_dcb_config *, पूर्णांक, u16 *);
व्योम ixgbe_dcb_unpack_max(काष्ठा ixgbe_dcb_config *, u16 *);
व्योम ixgbe_dcb_unpack_bwgid(काष्ठा ixgbe_dcb_config *, पूर्णांक, u8 *);
व्योम ixgbe_dcb_unpack_prio(काष्ठा ixgbe_dcb_config *, पूर्णांक, u8 *);
व्योम ixgbe_dcb_unpack_map(काष्ठा ixgbe_dcb_config *, पूर्णांक, u8 *);
u8 ixgbe_dcb_get_tc_from_up(काष्ठा ixgbe_dcb_config *, पूर्णांक, u8);

/* DCB credits calculation */
s32 ixgbe_dcb_calculate_tc_credits(काष्ठा ixgbe_hw *,
				   काष्ठा ixgbe_dcb_config *, पूर्णांक, u8);

/* DCB hw initialization */
s32 ixgbe_dcb_hw_ets(काष्ठा ixgbe_hw *hw, काष्ठा ieee_ets *ets, पूर्णांक max);
s32 ixgbe_dcb_hw_ets_config(काष्ठा ixgbe_hw *hw, u16 *refill, u16 *max,
			    u8 *bwg_id, u8 *prio_type, u8 *tc_prio);
s32 ixgbe_dcb_hw_pfc_config(काष्ठा ixgbe_hw *hw, u8 pfc_en, u8 *tc_prio);
s32 ixgbe_dcb_hw_config(काष्ठा ixgbe_hw *, काष्ठा ixgbe_dcb_config *);

व्योम ixgbe_dcb_पढ़ो_rtrup2tc(काष्ठा ixgbe_hw *hw, u8 *map);

/* DCB definitions क्रम credit calculation */
#घोषणा DCB_CREDIT_QUANTUM	64   /* DCB Quantum */
#घोषणा MAX_CREDIT_REFILL       511  /* 0x1FF * 64B = 32704B */
#घोषणा DCB_MAX_TSO_SIZE        (32*1024) /* MAX TSO packet size supported in DCB mode */
#घोषणा MINIMUM_CREDIT_FOR_TSO  (DCB_MAX_TSO_SIZE/64 + 1) /* 513 क्रम 32KB TSO packet */
#घोषणा MAX_CREDIT              4095 /* Maximum credit supported: 256KB * 1204 / 64B */

#पूर्ण_अगर /* _DCB_CONFIG_H */
