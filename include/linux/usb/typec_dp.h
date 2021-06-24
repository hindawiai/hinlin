<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB_TYPEC_DP_H
#घोषणा __USB_TYPEC_DP_H

#समावेश <linux/usb/typec_alपंचांगode.h>

#घोषणा USB_TYPEC_DP_SID	0xff01
/* USB IF has not asचिन्हित a Standard ID (SID) क्रम VirtualLink,
 * so the manufacturers of VirtualLink adapters use their Venकरोr
 * IDs as the SVID.
 */
#घोषणा USB_TYPEC_NVIDIA_VLINK_SID	0x955	/* NVIDIA VirtualLink */
#घोषणा USB_TYPEC_DP_MODE	1

/*
 * Connector states matching the pin assignments in DisplayPort Alt Mode
 * Specअगरication.
 *
 * These values are meant primarily to be used by the mux drivers, but they are
 * also used as the "value" part in the alternate mode notअगरication chain, so
 * receivers of those notअगरications will always see them.
 *
 * Note. DisplayPort USB Type-C Alt Mode Specअगरication version 1.0b deprecated
 * pin assignments A, B and F, but they are still defined here क्रम legacy
 * purposes.
 */
क्रमागत अणु
	TYPEC_DP_STATE_A = TYPEC_STATE_MODAL,	/* Not supported after v1.0b */
	TYPEC_DP_STATE_B,			/* Not supported after v1.0b */
	TYPEC_DP_STATE_C,
	TYPEC_DP_STATE_D,
	TYPEC_DP_STATE_E,
	TYPEC_DP_STATE_F,			/* Not supported after v1.0b */
पूर्ण;

/*
 * काष्ठा typec_displayport_data - DisplayPort Alt Mode specअगरic data
 * @status: Status Update command VDO content
 * @conf: Configure command VDO content
 *
 * This काष्ठाure is delivered as the data part with the notअगरications. It
 * contains the VDOs from the two DisplayPort Type-C alternate mode specअगरic
 * commands: Status Update and Configure.
 *
 * @status will show क्रम example the status of the HPD संकेत.
 */
काष्ठा typec_displayport_data अणु
	u32 status;
	u32 conf;
पूर्ण;

क्रमागत अणु
	DP_PIN_ASSIGN_A, /* Not supported after v1.0b */
	DP_PIN_ASSIGN_B, /* Not supported after v1.0b */
	DP_PIN_ASSIGN_C,
	DP_PIN_ASSIGN_D,
	DP_PIN_ASSIGN_E,
	DP_PIN_ASSIGN_F, /* Not supported after v1.0b */
पूर्ण;

/* DisplayPort alt mode specअगरic commands */
#घोषणा DP_CMD_STATUS_UPDATE		VDO_CMD_VENDOR(0)
#घोषणा DP_CMD_CONFIGURE		VDO_CMD_VENDOR(1)

/* DisplayPort Capabilities VDO bits (वापसed with Discover Modes) */
#घोषणा DP_CAP_CAPABILITY(_cap_)	((_cap_) & 3)
#घोषणा   DP_CAP_UFP_D			1
#घोषणा   DP_CAP_DFP_D			2
#घोषणा   DP_CAP_DFP_D_AND_UFP_D	3
#घोषणा DP_CAP_DP_SIGNALING		BIT(2) /* Always set */
#घोषणा DP_CAP_GEN2			BIT(3) /* Reserved after v1.0b */
#घोषणा DP_CAP_RECEPTACLE		BIT(6)
#घोषणा DP_CAP_USB			BIT(7)
#घोषणा DP_CAP_DFP_D_PIN_ASSIGN(_cap_)	(((_cap_) & GENMASK(15, 8)) >> 8)
#घोषणा DP_CAP_UFP_D_PIN_ASSIGN(_cap_)	(((_cap_) & GENMASK(23, 16)) >> 16)

/* DisplayPort Status Update VDO bits */
#घोषणा DP_STATUS_CONNECTION(_status_)	((_status_) & 3)
#घोषणा   DP_STATUS_CON_DISABLED	0
#घोषणा   DP_STATUS_CON_DFP_D		1
#घोषणा   DP_STATUS_CON_UFP_D		2
#घोषणा   DP_STATUS_CON_BOTH		3
#घोषणा DP_STATUS_POWER_LOW		BIT(2)
#घोषणा DP_STATUS_ENABLED		BIT(3)
#घोषणा DP_STATUS_PREFER_MULTI_FUNC	BIT(4)
#घोषणा DP_STATUS_SWITCH_TO_USB		BIT(5)
#घोषणा DP_STATUS_EXIT_DP_MODE		BIT(6)
#घोषणा DP_STATUS_HPD_STATE		BIT(7) /* 0 = HPD_Low, 1 = HPD_High */
#घोषणा DP_STATUS_IRQ_HPD		BIT(8)

/* DisplayPort Configurations VDO bits */
#घोषणा DP_CONF_CURRENTLY(_conf_)	((_conf_) & 3)
#घोषणा DP_CONF_UFP_U_AS_DFP_D		BIT(0)
#घोषणा DP_CONF_UFP_U_AS_UFP_D		BIT(1)
#घोषणा DP_CONF_SIGNALING_DP		BIT(2)
#घोषणा DP_CONF_SIGNALING_GEN_2		BIT(3) /* Reserved after v1.0b */
#घोषणा DP_CONF_PIN_ASSIGNEMENT_SHIFT	8
#घोषणा DP_CONF_PIN_ASSIGNEMENT_MASK	GENMASK(15, 8)

/* Helper क्रम setting/getting the pin assignement value to the configuration */
#घोषणा DP_CONF_SET_PIN_ASSIGN(_a_)	((_a_) << 8)
#घोषणा DP_CONF_GET_PIN_ASSIGN(_conf_)	(((_conf_) & GENMASK(15, 8)) >> 8)

#पूर्ण_अगर /* __USB_TYPEC_DP_H */
