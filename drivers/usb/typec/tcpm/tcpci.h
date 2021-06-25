<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2015-2017 Google, Inc
 *
 * USB Type-C Port Controller Interface.
 */

#अगर_अघोषित __LINUX_USB_TCPCI_H
#घोषणा __LINUX_USB_TCPCI_H

#समावेश <linux/usb/typec.h>

#घोषणा TCPC_VENDOR_ID			0x0
#घोषणा TCPC_PRODUCT_ID			0x2
#घोषणा TCPC_BCD_DEV			0x4
#घोषणा TCPC_TC_REV			0x6
#घोषणा TCPC_PD_REV			0x8
#घोषणा TCPC_PD_INT_REV			0xa

#घोषणा TCPC_ALERT			0x10
#घोषणा TCPC_ALERT_EXTND		BIT(14)
#घोषणा TCPC_ALERT_EXTENDED_STATUS	BIT(13)
#घोषणा TCPC_ALERT_VBUS_DISCNCT		BIT(11)
#घोषणा TCPC_ALERT_RX_BUF_OVF		BIT(10)
#घोषणा TCPC_ALERT_FAULT		BIT(9)
#घोषणा TCPC_ALERT_V_ALARM_LO		BIT(8)
#घोषणा TCPC_ALERT_V_ALARM_HI		BIT(7)
#घोषणा TCPC_ALERT_TX_SUCCESS		BIT(6)
#घोषणा TCPC_ALERT_TX_DISCARDED		BIT(5)
#घोषणा TCPC_ALERT_TX_FAILED		BIT(4)
#घोषणा TCPC_ALERT_RX_HARD_RST		BIT(3)
#घोषणा TCPC_ALERT_RX_STATUS		BIT(2)
#घोषणा TCPC_ALERT_POWER_STATUS		BIT(1)
#घोषणा TCPC_ALERT_CC_STATUS		BIT(0)

#घोषणा TCPC_ALERT_MASK			0x12
#घोषणा TCPC_POWER_STATUS_MASK		0x14
#घोषणा TCPC_FAULT_STATUS_MASK		0x15

#घोषणा TCPC_EXTENDED_STATUS_MASK		0x16
#घोषणा TCPC_EXTENDED_STATUS_MASK_VSAFE0V	BIT(0)

#घोषणा TCPC_ALERT_EXTENDED_MASK	0x17
#घोषणा TCPC_SINK_FAST_ROLE_SWAP	BIT(0)

#घोषणा TCPC_CONFIG_STD_OUTPUT		0x18

#घोषणा TCPC_TCPC_CTRL			0x19
#घोषणा TCPC_TCPC_CTRL_ORIENTATION	BIT(0)
#घोषणा PLUG_ORNT_CC1			0
#घोषणा PLUG_ORNT_CC2			1
#घोषणा TCPC_TCPC_CTRL_BIST_TM		BIT(1)
#घोषणा TCPC_TCPC_CTRL_EN_LK4CONN_ALRT	BIT(6)

#घोषणा TCPC_EXTENDED_STATUS		0x20
#घोषणा TCPC_EXTENDED_STATUS_VSAFE0V	BIT(0)

#घोषणा TCPC_ROLE_CTRL			0x1a
#घोषणा TCPC_ROLE_CTRL_DRP		BIT(6)
#घोषणा TCPC_ROLE_CTRL_RP_VAL_SHIFT	4
#घोषणा TCPC_ROLE_CTRL_RP_VAL_MASK	0x3
#घोषणा TCPC_ROLE_CTRL_RP_VAL_DEF	0x0
#घोषणा TCPC_ROLE_CTRL_RP_VAL_1_5	0x1
#घोषणा TCPC_ROLE_CTRL_RP_VAL_3_0	0x2
#घोषणा TCPC_ROLE_CTRL_CC2_SHIFT	2
#घोषणा TCPC_ROLE_CTRL_CC2_MASK		0x3
#घोषणा TCPC_ROLE_CTRL_CC1_SHIFT	0
#घोषणा TCPC_ROLE_CTRL_CC1_MASK		0x3
#घोषणा TCPC_ROLE_CTRL_CC_RA		0x0
#घोषणा TCPC_ROLE_CTRL_CC_RP		0x1
#घोषणा TCPC_ROLE_CTRL_CC_RD		0x2
#घोषणा TCPC_ROLE_CTRL_CC_OPEN		0x3

#घोषणा TCPC_FAULT_CTRL			0x1b

#घोषणा TCPC_POWER_CTRL			0x1c
#घोषणा TCPC_POWER_CTRL_VCONN_ENABLE	BIT(0)
#घोषणा TCPC_POWER_CTRL_BLEED_DISCHARGE	BIT(3)
#घोषणा TCPC_POWER_CTRL_AUTO_DISCHARGE	BIT(4)
#घोषणा TCPC_DIS_VOLT_ALRM		BIT(5)
#घोषणा TCPC_POWER_CTRL_VBUS_VOLT_MON	BIT(6)
#घोषणा TCPC_FAST_ROLE_SWAP_EN		BIT(7)

#घोषणा TCPC_CC_STATUS			0x1d
#घोषणा TCPC_CC_STATUS_TOGGLING		BIT(5)
#घोषणा TCPC_CC_STATUS_TERM		BIT(4)
#घोषणा TCPC_CC_STATUS_TERM_RP		0
#घोषणा TCPC_CC_STATUS_TERM_RD		1
#घोषणा TCPC_CC_STATE_SRC_OPEN		0
#घोषणा TCPC_CC_STATUS_CC2_SHIFT	2
#घोषणा TCPC_CC_STATUS_CC2_MASK		0x3
#घोषणा TCPC_CC_STATUS_CC1_SHIFT	0
#घोषणा TCPC_CC_STATUS_CC1_MASK		0x3

#घोषणा TCPC_POWER_STATUS		0x1e
#घोषणा TCPC_POWER_STATUS_DBG_ACC_CON	BIT(7)
#घोषणा TCPC_POWER_STATUS_UNINIT	BIT(6)
#घोषणा TCPC_POWER_STATUS_SOURCING_VBUS	BIT(4)
#घोषणा TCPC_POWER_STATUS_VBUS_DET	BIT(3)
#घोषणा TCPC_POWER_STATUS_VBUS_PRES	BIT(2)
#घोषणा TCPC_POWER_STATUS_SINKING_VBUS	BIT(0)

#घोषणा TCPC_FAULT_STATUS		0x1f

#घोषणा TCPC_ALERT_EXTENDED		0x21

#घोषणा TCPC_COMMAND			0x23
#घोषणा TCPC_CMD_WAKE_I2C		0x11
#घोषणा TCPC_CMD_DISABLE_VBUS_DETECT	0x22
#घोषणा TCPC_CMD_ENABLE_VBUS_DETECT	0x33
#घोषणा TCPC_CMD_DISABLE_SINK_VBUS	0x44
#घोषणा TCPC_CMD_SINK_VBUS		0x55
#घोषणा TCPC_CMD_DISABLE_SRC_VBUS	0x66
#घोषणा TCPC_CMD_SRC_VBUS_DEFAULT	0x77
#घोषणा TCPC_CMD_SRC_VBUS_HIGH		0x88
#घोषणा TCPC_CMD_LOOK4CONNECTION	0x99
#घोषणा TCPC_CMD_RXONEMORE		0xAA
#घोषणा TCPC_CMD_I2C_IDLE		0xFF

#घोषणा TCPC_DEV_CAP_1			0x24
#घोषणा TCPC_DEV_CAP_2			0x26
#घोषणा TCPC_STD_INPUT_CAP		0x28
#घोषणा TCPC_STD_OUTPUT_CAP		0x29

#घोषणा TCPC_MSG_HDR_INFO		0x2e
#घोषणा TCPC_MSG_HDR_INFO_DATA_ROLE	BIT(3)
#घोषणा TCPC_MSG_HDR_INFO_PWR_ROLE	BIT(0)
#घोषणा TCPC_MSG_HDR_INFO_REV_SHIFT	1
#घोषणा TCPC_MSG_HDR_INFO_REV_MASK	0x3

#घोषणा TCPC_RX_DETECT			0x2f
#घोषणा TCPC_RX_DETECT_HARD_RESET	BIT(5)
#घोषणा TCPC_RX_DETECT_SOP		BIT(0)
#घोषणा TCPC_RX_DETECT_SOP1		BIT(1)
#घोषणा TCPC_RX_DETECT_SOP2		BIT(2)
#घोषणा TCPC_RX_DETECT_DBG1		BIT(3)
#घोषणा TCPC_RX_DETECT_DBG2		BIT(4)

#घोषणा TCPC_RX_BYTE_CNT		0x30
#घोषणा TCPC_RX_BUF_FRAME_TYPE		0x31
#घोषणा TCPC_RX_BUF_FRAME_TYPE_SOP	0
#घोषणा TCPC_RX_HDR			0x32
#घोषणा TCPC_RX_DATA			0x34 /* through 0x4f */

#घोषणा TCPC_TRANSMIT			0x50
#घोषणा TCPC_TRANSMIT_RETRY_SHIFT	4
#घोषणा TCPC_TRANSMIT_RETRY_MASK	0x3
#घोषणा TCPC_TRANSMIT_TYPE_SHIFT	0
#घोषणा TCPC_TRANSMIT_TYPE_MASK		0x7

#घोषणा TCPC_TX_BYTE_CNT		0x51
#घोषणा TCPC_TX_HDR			0x52
#घोषणा TCPC_TX_DATA			0x54 /* through 0x6f */

#घोषणा TCPC_VBUS_VOLTAGE			0x70
#घोषणा TCPC_VBUS_VOLTAGE_MASK			0x3ff
#घोषणा TCPC_VBUS_VOLTAGE_LSB_MV		25
#घोषणा TCPC_VBUS_SINK_DISCONNECT_THRESH	0x72
#घोषणा TCPC_VBUS_SINK_DISCONNECT_THRESH_LSB_MV	25
#घोषणा TCPC_VBUS_SINK_DISCONNECT_THRESH_MAX	0x3ff
#घोषणा TCPC_VBUS_STOP_DISCHARGE_THRESH		0x74
#घोषणा TCPC_VBUS_VOLTAGE_ALARM_HI_CFG		0x76
#घोषणा TCPC_VBUS_VOLTAGE_ALARM_LO_CFG		0x78

/* I2C_WRITE_BYTE_COUNT + 1 when TX_BUF_BYTE_x is only accessible I2C_WRITE_BYTE_COUNT */
#घोषणा TCPC_TRANSMIT_BUFFER_MAX_LEN		31

काष्ठा tcpci;

/*
 * @TX_BUF_BYTE_x_hidden:
 *		optional; Set when TX_BUF_BYTE_x can only be accessed through I2C_WRITE_BYTE_COUNT.
 * @frs_sourcing_vbus:
 *		Optional; Callback to perक्रमm chip specअगरic operations when FRS
 *		is sourcing vbus.
 * @स्वतः_disअक्षरge_disconnect:
 *		Optional; Enables TCPC to स्वतःnously disअक्षरge vbus on disconnect.
 * @vbus_vsafe0v:
 *		optional; Set when TCPC can detect whether vbus is at VSAFE0V.
 * @set_partner_usb_comm_capable:
 *		Optional; The USB Communications Capable bit indicates अगर port
 *		partner is capable of communication over the USB data lines
 *		(e.g. D+/- or SS Tx/Rx). Called to notअगरy the status of the bit.
 */
काष्ठा tcpci_data अणु
	काष्ठा regmap *regmap;
	अचिन्हित अक्षर TX_BUF_BYTE_x_hidden:1;
	अचिन्हित अक्षर स्वतः_disअक्षरge_disconnect:1;
	अचिन्हित अक्षर vbus_vsafe0v:1;

	पूर्णांक (*init)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data);
	पूर्णांक (*set_vconn)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data,
			 bool enable);
	पूर्णांक (*start_drp_toggling)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data,
				  क्रमागत typec_cc_status cc);
	पूर्णांक (*set_vbus)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data, bool source, bool sink);
	व्योम (*frs_sourcing_vbus)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data);
	व्योम (*set_partner_usb_comm_capable)(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data,
					     bool capable);
पूर्ण;

काष्ठा tcpci *tcpci_रेजिस्टर_port(काष्ठा device *dev, काष्ठा tcpci_data *data);
व्योम tcpci_unरेजिस्टर_port(काष्ठा tcpci *tcpci);
irqवापस_t tcpci_irq(काष्ठा tcpci *tcpci);

काष्ठा tcpm_port;
काष्ठा tcpm_port *tcpci_get_tcpm_port(काष्ठा tcpci *tcpci);
#पूर्ण_अगर /* __LINUX_USB_TCPCI_H */
