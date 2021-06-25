<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB_TYPEC_TBT_H
#घोषणा __USB_TYPEC_TBT_H

#समावेश <linux/usb/typec_alपंचांगode.h>

#घोषणा USB_TYPEC_VENDOR_INTEL		0x8087
/* Alias क्रम convenience */
#घोषणा USB_TYPEC_TBT_SID		USB_TYPEC_VENDOR_INTEL

/* Connector state क्रम Thunderbolt3 */
#घोषणा TYPEC_TBT_MODE			TYPEC_STATE_MODAL

/**
 * काष्ठा typec_thunderbolt_data - Thundebolt3 Alt Mode specअगरic data
 * @device_mode: Device Discover Mode VDO
 * @cable_mode: Cable Discover Mode VDO
 * @enter_vकरो: Enter Mode VDO
 */
काष्ठा typec_thunderbolt_data अणु
	u32 device_mode;
	u32 cable_mode;
	u32 enter_vकरो;
पूर्ण;

/* TBT3 Device Discover Mode VDO bits */
#घोषणा TBT_MODE			BIT(0)
#घोषणा TBT_ADAPTER(_vकरो_)		(((_vकरो_) & BIT(16)) >> 16)
#घोषणा   TBT_ADAPTER_LEGACY		0
#घोषणा   TBT_ADAPTER_TBT3		1
#घोषणा TBT_INTEL_SPECIFIC_B0		BIT(26)
#घोषणा TBT_VENDOR_SPECIFIC_B0		BIT(30)
#घोषणा TBT_VENDOR_SPECIFIC_B1		BIT(31)

#घोषणा TBT_SET_ADAPTER(a)		(((a) & 1) << 16)

/* TBT3 Cable Discover Mode VDO bits */
#घोषणा TBT_CABLE_SPEED(_vकरो_)		(((_vकरो_) & GENMASK(18, 16)) >> 16)
#घोषणा   TBT_CABLE_USB3_GEN1		1
#घोषणा   TBT_CABLE_USB3_PASSIVE	2
#घोषणा   TBT_CABLE_10_AND_20GBPS	3
#घोषणा TBT_CABLE_ROUNDED_SUPPORT(_vकरो_) \
					(((_vकरो_) & GENMASK(20, 19)) >> 19)
#घोषणा   TBT_GEN3_NON_ROUNDED                 0
#घोषणा   TBT_GEN3_GEN4_ROUNDED_NON_ROUNDED    1
#घोषणा TBT_CABLE_OPTICAL		BIT(21)
#घोषणा TBT_CABLE_RETIMER		BIT(22)
#घोषणा TBT_CABLE_LINK_TRAINING		BIT(23)

#घोषणा TBT_SET_CABLE_SPEED(_s_)	(((_s_) & GENMASK(2, 0)) << 16)
#घोषणा TBT_SET_CABLE_ROUNDED(_g_)	(((_g_) & GENMASK(1, 0)) << 19)

/* TBT3 Device Enter Mode VDO bits */
#घोषणा TBT_ENTER_MODE_CABLE_SPEED(s)	TBT_SET_CABLE_SPEED(s)
#घोषणा TBT_ENTER_MODE_ACTIVE_CABLE	BIT(24)

#पूर्ण_अगर /* __USB_TYPEC_TBT_H */
