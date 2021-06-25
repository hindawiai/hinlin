<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2019 NXP
 */
#अगर_अघोषित __FSL_DPMAC_H
#घोषणा __FSL_DPMAC_H

/* Data Path MAC API
 * Contains initialization APIs and runसमय control APIs क्रम DPMAC
 */

काष्ठा fsl_mc_io;

पूर्णांक dpmac_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dpmac_id,
	       u16 *token);

पूर्णांक dpmac_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

/**
 * क्रमागत dpmac_link_type -  DPMAC link type
 * @DPMAC_LINK_TYPE_NONE: No link
 * @DPMAC_LINK_TYPE_FIXED: Link is fixed type
 * @DPMAC_LINK_TYPE_PHY: Link by PHY ID
 * @DPMAC_LINK_TYPE_BACKPLANE: Backplane link type
 */
क्रमागत dpmac_link_type अणु
	DPMAC_LINK_TYPE_NONE,
	DPMAC_LINK_TYPE_FIXED,
	DPMAC_LINK_TYPE_PHY,
	DPMAC_LINK_TYPE_BACKPLANE
पूर्ण;

/**
 * क्रमागत dpmac_eth_अगर - DPMAC Ethrnet पूर्णांकerface
 * @DPMAC_ETH_IF_MII: MII पूर्णांकerface
 * @DPMAC_ETH_IF_RMII: RMII पूर्णांकerface
 * @DPMAC_ETH_IF_SMII: SMII पूर्णांकerface
 * @DPMAC_ETH_IF_GMII: GMII पूर्णांकerface
 * @DPMAC_ETH_IF_RGMII: RGMII पूर्णांकerface
 * @DPMAC_ETH_IF_SGMII: SGMII पूर्णांकerface
 * @DPMAC_ETH_IF_QSGMII: QSGMII पूर्णांकerface
 * @DPMAC_ETH_IF_XAUI: XAUI पूर्णांकerface
 * @DPMAC_ETH_IF_XFI: XFI पूर्णांकerface
 * @DPMAC_ETH_IF_CAUI: CAUI पूर्णांकerface
 * @DPMAC_ETH_IF_1000BASEX: 1000BASEX पूर्णांकerface
 * @DPMAC_ETH_IF_USXGMII: USXGMII पूर्णांकerface
 */
क्रमागत dpmac_eth_अगर अणु
	DPMAC_ETH_IF_MII,
	DPMAC_ETH_IF_RMII,
	DPMAC_ETH_IF_SMII,
	DPMAC_ETH_IF_GMII,
	DPMAC_ETH_IF_RGMII,
	DPMAC_ETH_IF_SGMII,
	DPMAC_ETH_IF_QSGMII,
	DPMAC_ETH_IF_XAUI,
	DPMAC_ETH_IF_XFI,
	DPMAC_ETH_IF_CAUI,
	DPMAC_ETH_IF_1000BASEX,
	DPMAC_ETH_IF_USXGMII,
पूर्ण;

/**
 * काष्ठा dpmac_attr - Structure representing DPMAC attributes
 * @id:		DPMAC object ID
 * @max_rate:	Maximum supported rate - in Mbps
 * @eth_अगर:	Ethernet पूर्णांकerface
 * @link_type:	link type
 */
काष्ठा dpmac_attr अणु
	u16 id;
	u32 max_rate;
	क्रमागत dpmac_eth_अगर eth_अगर;
	क्रमागत dpmac_link_type link_type;
पूर्ण;

पूर्णांक dpmac_get_attributes(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpmac_attr *attr);

/* DPMAC link configuration/state options */

#घोषणा DPMAC_LINK_OPT_AUTONEG			BIT_ULL(0)
#घोषणा DPMAC_LINK_OPT_HALF_DUPLEX		BIT_ULL(1)
#घोषणा DPMAC_LINK_OPT_PAUSE			BIT_ULL(2)
#घोषणा DPMAC_LINK_OPT_ASYM_PAUSE		BIT_ULL(3)

/* Advertised link speeds */
#घोषणा DPMAC_ADVERTISED_10BASET_FULL		BIT_ULL(0)
#घोषणा DPMAC_ADVERTISED_100BASET_FULL		BIT_ULL(1)
#घोषणा DPMAC_ADVERTISED_1000BASET_FULL		BIT_ULL(2)
#घोषणा DPMAC_ADVERTISED_10000BASET_FULL	BIT_ULL(4)
#घोषणा DPMAC_ADVERTISED_2500BASEX_FULL		BIT_ULL(5)

/* Advertise स्वतः-negotiation enable */
#घोषणा DPMAC_ADVERTISED_AUTONEG		BIT_ULL(3)

/**
 * काष्ठा dpmac_link_state - DPMAC link configuration request
 * @rate: Rate in Mbps
 * @options: Enable/Disable DPMAC link cfg features (biपंचांगap)
 * @up: Link state
 * @state_valid: Ignore/Update the state of the link
 * @supported: Speeds capability of the phy (biपंचांगap)
 * @advertising: Speeds that are advertised क्रम स्वतःneg (biपंचांगap)
 */
काष्ठा dpmac_link_state अणु
	u32 rate;
	u64 options;
	पूर्णांक up;
	पूर्णांक state_valid;
	u64 supported;
	u64 advertising;
पूर्ण;

पूर्णांक dpmac_set_link_state(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpmac_link_state *link_state);

/**
 * क्रमागत dpmac_counter_id - DPMAC counter types
 *
 * @DPMAC_CNT_ING_FRAME_64: counts 64-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_127: counts 65- to 127-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_255: counts 128- to 255-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_511: counts 256- to 511-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_1023: counts 512- to 1023-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_1518: counts 1024- to 1518-bytes frames, good or bad.
 * @DPMAC_CNT_ING_FRAME_1519_MAX: counts 1519-bytes frames and larger
 *				  (up to max frame length specअगरied),
 *				  good or bad.
 * @DPMAC_CNT_ING_FRAG: counts frames which are लघुer than 64 bytes received
 *			with a wrong CRC
 * @DPMAC_CNT_ING_JABBER: counts frames दीर्घer than the maximum frame length
 *			  specअगरied, with a bad frame check sequence.
 * @DPMAC_CNT_ING_FRAME_DISCARD: counts dropped frames due to पूर्णांकernal errors.
 *				 Occurs when a receive FIFO overflows.
 *				 Includes also frames truncated as a result of
 *				 the receive FIFO overflow.
 * @DPMAC_CNT_ING_ALIGN_ERR: counts frames with an alignment error
 *			     (optional used क्रम wrong SFD).
 * @DPMAC_CNT_EGR_UNDERSIZED: counts frames transmitted that was less than 64
 *			      bytes दीर्घ with a good CRC.
 * @DPMAC_CNT_ING_OVERSIZED: counts frames दीर्घer than the maximum frame length
 *			     specअगरied, with a good frame check sequence.
 * @DPMAC_CNT_ING_VALID_PAUSE_FRAME: counts valid छोड़ो frames (regular and PFC)
 * @DPMAC_CNT_EGR_VALID_PAUSE_FRAME: counts valid छोड़ो frames transmitted
 *				     (regular and PFC).
 * @DPMAC_CNT_ING_BYTE: counts bytes received except preamble क्रम all valid
 *			frames and valid छोड़ो frames.
 * @DPMAC_CNT_ING_MCAST_FRAME: counts received multicast frames.
 * @DPMAC_CNT_ING_BCAST_FRAME: counts received broadcast frames.
 * @DPMAC_CNT_ING_ALL_FRAME: counts each good or bad frames received.
 * @DPMAC_CNT_ING_UCAST_FRAME: counts received unicast frames.
 * @DPMAC_CNT_ING_ERR_FRAME: counts frames received with an error
 *			     (except क्रम undersized/fragment frame).
 * @DPMAC_CNT_EGR_BYTE: counts bytes transmitted except preamble क्रम all valid
 *			frames and valid छोड़ो frames transmitted.
 * @DPMAC_CNT_EGR_MCAST_FRAME: counts transmitted multicast frames.
 * @DPMAC_CNT_EGR_BCAST_FRAME: counts transmitted broadcast frames.
 * @DPMAC_CNT_EGR_UCAST_FRAME: counts transmitted unicast frames.
 * @DPMAC_CNT_EGR_ERR_FRAME: counts frames transmitted with an error.
 * @DPMAC_CNT_ING_GOOD_FRAME: counts frames received without error, including
 *			      छोड़ो frames.
 * @DPMAC_CNT_EGR_GOOD_FRAME: counts frames transmitted without error, including
 *			      छोड़ो frames.
 */
क्रमागत dpmac_counter_id अणु
	DPMAC_CNT_ING_FRAME_64,
	DPMAC_CNT_ING_FRAME_127,
	DPMAC_CNT_ING_FRAME_255,
	DPMAC_CNT_ING_FRAME_511,
	DPMAC_CNT_ING_FRAME_1023,
	DPMAC_CNT_ING_FRAME_1518,
	DPMAC_CNT_ING_FRAME_1519_MAX,
	DPMAC_CNT_ING_FRAG,
	DPMAC_CNT_ING_JABBER,
	DPMAC_CNT_ING_FRAME_DISCARD,
	DPMAC_CNT_ING_ALIGN_ERR,
	DPMAC_CNT_EGR_UNDERSIZED,
	DPMAC_CNT_ING_OVERSIZED,
	DPMAC_CNT_ING_VALID_PAUSE_FRAME,
	DPMAC_CNT_EGR_VALID_PAUSE_FRAME,
	DPMAC_CNT_ING_BYTE,
	DPMAC_CNT_ING_MCAST_FRAME,
	DPMAC_CNT_ING_BCAST_FRAME,
	DPMAC_CNT_ING_ALL_FRAME,
	DPMAC_CNT_ING_UCAST_FRAME,
	DPMAC_CNT_ING_ERR_FRAME,
	DPMAC_CNT_EGR_BYTE,
	DPMAC_CNT_EGR_MCAST_FRAME,
	DPMAC_CNT_EGR_BCAST_FRAME,
	DPMAC_CNT_EGR_UCAST_FRAME,
	DPMAC_CNT_EGR_ERR_FRAME,
	DPMAC_CNT_ING_GOOD_FRAME,
	DPMAC_CNT_EGR_GOOD_FRAME
पूर्ण;

पूर्णांक dpmac_get_counter(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		      क्रमागत dpmac_counter_id id, u64 *value);

#पूर्ण_अगर /* __FSL_DPMAC_H */
