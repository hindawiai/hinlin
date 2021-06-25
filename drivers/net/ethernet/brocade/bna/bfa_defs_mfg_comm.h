<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#अगर_अघोषित __BFA_DEFS_MFG_COMM_H__
#घोषणा __BFA_DEFS_MFG_COMM_H__

#समावेश "bfa_defs.h"

/* Manufacturing block version */
#घोषणा BFA_MFG_VERSION				3
#घोषणा BFA_MFG_VERSION_UNINIT			0xFF

/* Manufacturing block encrypted version */
#घोषणा BFA_MFG_ENC_VER				2

/* Manufacturing block version 1 length */
#घोषणा BFA_MFG_VER1_LEN			128

/* Manufacturing block header length */
#घोषणा BFA_MFG_HDR_LEN				4

#घोषणा BFA_MFG_SERIALNUM_SIZE			11
#घोषणा STRSZ(_n)				(((_n) + 4) & ~3)

/* Manufacturing card type */
क्रमागत अणु
	BFA_MFG_TYPE_CB_MAX  = 825,      /*!< Crossbow card type max	*/
	BFA_MFG_TYPE_FC8P2   = 825,      /*!< 8G 2port FC card		*/
	BFA_MFG_TYPE_FC8P1   = 815,      /*!< 8G 1port FC card		*/
	BFA_MFG_TYPE_FC4P2   = 425,      /*!< 4G 2port FC card		*/
	BFA_MFG_TYPE_FC4P1   = 415,      /*!< 4G 1port FC card		*/
	BFA_MFG_TYPE_CNA10P2 = 1020,     /*!< 10G 2port CNA card	*/
	BFA_MFG_TYPE_CNA10P1 = 1010,     /*!< 10G 1port CNA card	*/
	BFA_MFG_TYPE_JAYHAWK = 804,	 /*!< Jayhawk mezz card		*/
	BFA_MFG_TYPE_WANCHESE = 1007,	 /*!< Wanchese mezz card	*/
	BFA_MFG_TYPE_ASTRA    = 807,	 /*!< Astra mezz card		*/
	BFA_MFG_TYPE_LIGHTNING_P0 = 902, /*!< Lightning mezz card - old	*/
	BFA_MFG_TYPE_LIGHTNING = 1741,	 /*!< Lightning mezz card	*/
	BFA_MFG_TYPE_PROWLER_F = 1560,	 /*!< Prowler FC only cards	*/
	BFA_MFG_TYPE_PROWLER_N = 1410,	 /*!< Prowler NIC only cards	*/
	BFA_MFG_TYPE_PROWLER_C = 1710,	 /*!< Prowler CNA only cards	*/
	BFA_MFG_TYPE_PROWLER_D = 1860,	 /*!< Prowler Dual cards	*/
	BFA_MFG_TYPE_CHINOOK   = 1867,	 /*!< Chinook cards		*/
	BFA_MFG_TYPE_INVALID = 0,	 /*!< Invalid card type		*/
पूर्ण;

/* Check अगर Mezz card */
#घोषणा bfa_mfg_is_mezz(type) (( \
	(type) == BFA_MFG_TYPE_JAYHAWK || \
	(type) == BFA_MFG_TYPE_WANCHESE || \
	(type) == BFA_MFG_TYPE_ASTRA || \
	(type) == BFA_MFG_TYPE_LIGHTNING_P0 || \
	(type) == BFA_MFG_TYPE_LIGHTNING || \
	(type) == BFA_MFG_TYPE_CHINOOK))

क्रमागत अणु
	CB_GPIO_TTV	= (1),		/*!< TTV debug capable cards	*/
	CB_GPIO_FC8P2   = (2),		/*!< 8G 2port FC card		*/
	CB_GPIO_FC8P1   = (3),		/*!< 8G 1port FC card		*/
	CB_GPIO_FC4P2   = (4),		/*!< 4G 2port FC card		*/
	CB_GPIO_FC4P1   = (5),		/*!< 4G 1port FC card		*/
	CB_GPIO_DFLY    = (6),		/*!< 8G 2port FC mezzanine card	*/
	CB_GPIO_PROTO   = BIT(7)	/*!< 8G 2port FC prototypes	*/
पूर्ण;

#घोषणा bfa_mfg_adapter_prop_init_gpio(gpio, card_type, prop)	\
करो अणु								\
	अगर ((gpio) & CB_GPIO_PROTO) अणु				\
		(prop) |= BFI_ADAPTER_PROTO;			\
		(gpio) &= ~CB_GPIO_PROTO;			\
	पूर्ण							\
	चयन (gpio) अणु						\
	हाल CB_GPIO_TTV:					\
		(prop) |= BFI_ADAPTER_TTV;			\
	हाल CB_GPIO_DFLY:					\
	हाल CB_GPIO_FC8P2:					\
		(prop) |= BFI_ADAPTER_SETP(NPORTS, 2);		\
		(prop) |= BFI_ADAPTER_SETP(SPEED, 8);		\
		(card_type) = BFA_MFG_TYPE_FC8P2;		\
		अवरोध;						\
	हाल CB_GPIO_FC8P1:					\
		(prop) |= BFI_ADAPTER_SETP(NPORTS, 1);		\
		(prop) |= BFI_ADAPTER_SETP(SPEED, 8);		\
		(card_type) = BFA_MFG_TYPE_FC8P1;		\
		अवरोध;						\
	हाल CB_GPIO_FC4P2:					\
		(prop) |= BFI_ADAPTER_SETP(NPORTS, 2);		\
		(prop) |= BFI_ADAPTER_SETP(SPEED, 4);		\
		(card_type) = BFA_MFG_TYPE_FC4P2;		\
		अवरोध;						\
	हाल CB_GPIO_FC4P1:					\
		(prop) |= BFI_ADAPTER_SETP(NPORTS, 1);		\
		(prop) |= BFI_ADAPTER_SETP(SPEED, 4);		\
		(card_type) = BFA_MFG_TYPE_FC4P1;		\
		अवरोध;						\
	शेष:						\
		(prop) |= BFI_ADAPTER_UNSUPP;			\
		(card_type) = BFA_MFG_TYPE_INVALID;		\
	पूर्ण							\
पूर्ण जबतक (0)

/* VPD data length */
#घोषणा BFA_MFG_VPD_LEN			512
#घोषणा BFA_MFG_VPD_LEN_INVALID		0

#घोषणा BFA_MFG_VPD_PCI_HDR_OFF		137
#घोषणा BFA_MFG_VPD_PCI_VER_MASK	0x07	/*!< version mask 3 bits */
#घोषणा BFA_MFG_VPD_PCI_VDR_MASK	0xf8	/*!< venकरोr mask 5 bits */

/* VPD venकरोr tag */
क्रमागत अणु
	BFA_MFG_VPD_UNKNOWN	= 0,     /*!< venकरोr unknown		*/
	BFA_MFG_VPD_IBM		= 1,     /*!< venकरोr IBM		*/
	BFA_MFG_VPD_HP		= 2,     /*!< venकरोr HP			*/
	BFA_MFG_VPD_DELL	= 3,     /*!< venकरोr DELL		*/
	BFA_MFG_VPD_PCI_IBM	= 0x08,  /*!< PCI VPD IBM		*/
	BFA_MFG_VPD_PCI_HP	= 0x10,  /*!< PCI VPD HP		*/
	BFA_MFG_VPD_PCI_DELL	= 0x20,  /*!< PCI VPD DELL		*/
	BFA_MFG_VPD_PCI_BRCD	= 0xf8,  /*!< PCI VPD Brocade		*/
पूर्ण;

/* BFA adapter flash vpd data definition.
 *
 * All numerical fields are in big-endian क्रमmat.
 */
काष्ठा bfa_mfg_vpd अणु
	u8		version;	/*!< vpd data version */
	u8		vpd_sig[3];	/*!< अक्षरacters 'V', 'P', 'D' */
	u8		chksum;		/*!< u8 checksum */
	u8		venकरोr;		/*!< venकरोr */
	u8	len;		/*!< vpd data length excluding header */
	u8	rsv;
	u8		data[BFA_MFG_VPD_LEN];	/*!< vpd data */
पूर्ण __packed;

#पूर्ण_अगर /* __BFA_DEFS_MFG_H__ */
