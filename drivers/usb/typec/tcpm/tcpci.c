<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2015-2017 Google, Inc
 *
 * USB Type-C Port Controller Interface.
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/usb/typec.h>

#समावेश "tcpci.h"

#घोषणा	PD_RETRY_COUNT_DEFAULT			3
#घोषणा	PD_RETRY_COUNT_3_0_OR_HIGHER		2
#घोषणा	AUTO_DISCHARGE_DEFAULT_THRESHOLD_MV	3500
#घोषणा	AUTO_DISCHARGE_PD_HEADROOM_MV		850
#घोषणा	AUTO_DISCHARGE_PPS_HEADROOM_MV		1250

#घोषणा tcpc_presenting_rd(reg, cc) \
	(!(TCPC_ROLE_CTRL_DRP & (reg)) && \
	 (((reg) & (TCPC_ROLE_CTRL_## cc ##_MASK << TCPC_ROLE_CTRL_## cc ##_SHIFT)) == \
	  (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_## cc ##_SHIFT)))

काष्ठा tcpci अणु
	काष्ठा device *dev;

	काष्ठा tcpm_port *port;

	काष्ठा regmap *regmap;

	bool controls_vbus;

	काष्ठा tcpc_dev tcpc;
	काष्ठा tcpci_data *data;
पूर्ण;

काष्ठा tcpci_chip अणु
	काष्ठा tcpci *tcpci;
	काष्ठा tcpci_data data;
पूर्ण;

काष्ठा tcpm_port *tcpci_get_tcpm_port(काष्ठा tcpci *tcpci)
अणु
	वापस tcpci->port;
पूर्ण
EXPORT_SYMBOL_GPL(tcpci_get_tcpm_port);

अटल अंतरभूत काष्ठा tcpci *tcpc_to_tcpci(काष्ठा tcpc_dev *tcpc)
अणु
	वापस container_of(tcpc, काष्ठा tcpci, tcpc);
पूर्ण

अटल पूर्णांक tcpci_पढ़ो16(काष्ठा tcpci *tcpci, अचिन्हित पूर्णांक reg, u16 *val)
अणु
	वापस regmap_raw_पढ़ो(tcpci->regmap, reg, val, माप(u16));
पूर्ण

अटल पूर्णांक tcpci_ग_लिखो16(काष्ठा tcpci *tcpci, अचिन्हित पूर्णांक reg, u16 val)
अणु
	वापस regmap_raw_ग_लिखो(tcpci->regmap, reg, &val, माप(u16));
पूर्ण

अटल पूर्णांक tcpci_set_cc(काष्ठा tcpc_dev *tcpc, क्रमागत typec_cc_status cc)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	चयन (cc) अणु
	हाल TYPEC_CC_RA:
		reg = (TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC2_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RD:
		reg = (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_DEF:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_DEF <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_1_5:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_OPEN:
	शेष:
		reg = (TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT);
		अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_ROLE_CTRL, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_start_toggling(काष्ठा tcpc_dev *tcpc,
				क्रमागत typec_port_type port_type,
				क्रमागत typec_cc_status cc)
अणु
	पूर्णांक ret;
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg = TCPC_ROLE_CTRL_DRP;

	अगर (port_type != TYPEC_PORT_DRP)
		वापस -EOPNOTSUPP;

	/* Handle venकरोr drp toggling */
	अगर (tcpci->data->start_drp_toggling) अणु
		ret = tcpci->data->start_drp_toggling(tcpci, tcpci->data, cc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	चयन (cc) अणु
	शेष:
	हाल TYPEC_CC_RP_DEF:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_DEF <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_1_5:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		अवरोध;
	पूर्ण

	अगर (cc == TYPEC_CC_RD)
		reg |= (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
	अन्यथा
		reg |= (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT);
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_ROLE_CTRL, reg);
	अगर (ret < 0)
		वापस ret;
	वापस regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
			    TCPC_CMD_LOOK4CONNECTION);
पूर्ण

अटल क्रमागत typec_cc_status tcpci_to_typec_cc(अचिन्हित पूर्णांक cc, bool sink)
अणु
	चयन (cc) अणु
	हाल 0x1:
		वापस sink ? TYPEC_CC_RP_DEF : TYPEC_CC_RA;
	हाल 0x2:
		वापस sink ? TYPEC_CC_RP_1_5 : TYPEC_CC_RD;
	हाल 0x3:
		अगर (sink)
			वापस TYPEC_CC_RP_3_0;
		fallthrough;
	हाल 0x0:
	शेष:
		वापस TYPEC_CC_OPEN;
	पूर्ण
पूर्ण

अटल पूर्णांक tcpci_get_cc(काष्ठा tcpc_dev *tcpc,
			क्रमागत typec_cc_status *cc1, क्रमागत typec_cc_status *cc2)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg, role_control;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tcpci->regmap, TCPC_ROLE_CTRL, &role_control);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(tcpci->regmap, TCPC_CC_STATUS, &reg);
	अगर (ret < 0)
		वापस ret;

	*cc1 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC1_SHIFT) &
				 TCPC_CC_STATUS_CC1_MASK,
				 reg & TCPC_CC_STATUS_TERM ||
				 tcpc_presenting_rd(role_control, CC1));
	*cc2 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC2_SHIFT) &
				 TCPC_CC_STATUS_CC2_MASK,
				 reg & TCPC_CC_STATUS_TERM ||
				 tcpc_presenting_rd(role_control, CC2));

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_set_polarity(काष्ठा tcpc_dev *tcpc,
			      क्रमागत typec_cc_polarity polarity)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	क्रमागत typec_cc_status cc1, cc2;

	/* Obtain Rp setting from role control */
	ret = regmap_पढ़ो(tcpci->regmap, TCPC_ROLE_CTRL, &reg);
	अगर (ret < 0)
		वापस ret;

	ret = tcpci_get_cc(tcpc, &cc1, &cc2);
	अगर (ret < 0)
		वापस ret;

	/*
	 * When port has drp toggling enabled, ROLE_CONTROL would only have the initial
	 * terminations क्रम the toggling and करोes not indicate the final cc
	 * terminations when ConnectionResult is 0 i.e. drp toggling stops and
	 * the connection is resolbed. Infer port role from TCPC_CC_STATUS based on the
	 * terminations seen. The port role is then used to set the cc terminations.
	 */
	अगर (reg & TCPC_ROLE_CTRL_DRP) अणु
		/* Disable DRP क्रम the OPEN setting to take effect */
		reg = reg & ~TCPC_ROLE_CTRL_DRP;

		अगर (polarity == TYPEC_POLARITY_CC2) अणु
			reg &= ~(TCPC_ROLE_CTRL_CC2_MASK << TCPC_ROLE_CTRL_CC2_SHIFT);
			/* Local port is source */
			अगर (cc2 == TYPEC_CC_RD)
				/* Role control would have the Rp setting when DRP was enabled */
				reg |= TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT;
			अन्यथा
				reg |= TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT;
		पूर्ण अन्यथा अणु
			reg &= ~(TCPC_ROLE_CTRL_CC1_MASK << TCPC_ROLE_CTRL_CC1_SHIFT);
			/* Local port is source */
			अगर (cc1 == TYPEC_CC_RD)
				/* Role control would have the Rp setting when DRP was enabled */
				reg |= TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT;
			अन्यथा
				reg |= TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT;
		पूर्ण
	पूर्ण

	अगर (polarity == TYPEC_POLARITY_CC2)
		reg |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT;
	अन्यथा
		reg |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT;
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_ROLE_CTRL, reg);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(tcpci->regmap, TCPC_TCPC_CTRL,
			   (polarity == TYPEC_POLARITY_CC2) ?
			   TCPC_TCPC_CTRL_ORIENTATION : 0);
पूर्ण

अटल व्योम tcpci_set_partner_usb_comm_capable(काष्ठा tcpc_dev *tcpc, bool capable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);

	अगर (tcpci->data->set_partner_usb_comm_capable)
		tcpci->data->set_partner_usb_comm_capable(tcpci, tcpci->data, capable);
पूर्ण

अटल पूर्णांक tcpci_set_vconn(काष्ठा tcpc_dev *tcpc, bool enable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	पूर्णांक ret;

	/* Handle venकरोr set vconn */
	अगर (tcpci->data->set_vconn) अणु
		ret = tcpci->data->set_vconn(tcpci, tcpci->data, enable);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस regmap_update_bits(tcpci->regmap, TCPC_POWER_CTRL,
				TCPC_POWER_CTRL_VCONN_ENABLE,
				enable ? TCPC_POWER_CTRL_VCONN_ENABLE : 0);
पूर्ण

अटल पूर्णांक tcpci_enable_स्वतः_vbus_disअक्षरge(काष्ठा tcpc_dev *dev, bool enable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(tcpci->regmap, TCPC_POWER_CTRL, TCPC_POWER_CTRL_AUTO_DISCHARGE,
				 enable ? TCPC_POWER_CTRL_AUTO_DISCHARGE : 0);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpci_set_स्वतः_vbus_disअक्षरge_threshold(काष्ठा tcpc_dev *dev, क्रमागत typec_pwr_opmode mode,
						   bool pps_active, u32 requested_vbus_voltage_mv)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(dev);
	अचिन्हित पूर्णांक pwr_ctrl, threshold = 0;
	पूर्णांक ret;

	/*
	 * Indicates that vbus is going to go away due PR_SWAP, hard reset etc.
	 * Do not disअक्षरge vbus here.
	 */
	अगर (requested_vbus_voltage_mv == 0)
		जाओ ग_लिखो_thresh;

	ret = regmap_पढ़ो(tcpci->regmap, TCPC_POWER_CTRL, &pwr_ctrl);
	अगर (ret < 0)
		वापस ret;

	अगर (pwr_ctrl & TCPC_FAST_ROLE_SWAP_EN) अणु
		/* To prevent disconnect when the source is fast role swap is capable. */
		threshold = AUTO_DISCHARGE_DEFAULT_THRESHOLD_MV;
	पूर्ण अन्यथा अगर (mode == TYPEC_PWR_MODE_PD) अणु
		अगर (pps_active)
			threshold = (95 * requested_vbus_voltage_mv / 100) -
				AUTO_DISCHARGE_PD_HEADROOM_MV;
		अन्यथा
			threshold = (95 * requested_vbus_voltage_mv / 100) -
				AUTO_DISCHARGE_PPS_HEADROOM_MV;
	पूर्ण अन्यथा अणु
		/* 3.5V क्रम non-pd sink */
		threshold = AUTO_DISCHARGE_DEFAULT_THRESHOLD_MV;
	पूर्ण

	threshold = threshold / TCPC_VBUS_SINK_DISCONNECT_THRESH_LSB_MV;

	अगर (threshold > TCPC_VBUS_SINK_DISCONNECT_THRESH_MAX)
		वापस -EINVAL;

ग_लिखो_thresh:
	वापस tcpci_ग_लिखो16(tcpci, TCPC_VBUS_SINK_DISCONNECT_THRESH, threshold);
पूर्ण

अटल पूर्णांक tcpci_enable_frs(काष्ठा tcpc_dev *dev, bool enable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(dev);
	पूर्णांक ret;

	/* To prevent disconnect during FRS, set disconnect threshold to 3.5V */
	ret = tcpci_ग_लिखो16(tcpci, TCPC_VBUS_SINK_DISCONNECT_THRESH, enable ? 0 : 0x8c);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(tcpci->regmap, TCPC_POWER_CTRL, TCPC_FAST_ROLE_SWAP_EN, enable ?
				 TCPC_FAST_ROLE_SWAP_EN : 0);

	वापस ret;
पूर्ण

अटल व्योम tcpci_frs_sourcing_vbus(काष्ठा tcpc_dev *dev)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(dev);

	अगर (tcpci->data->frs_sourcing_vbus)
		tcpci->data->frs_sourcing_vbus(tcpci, tcpci->data);
पूर्ण

अटल पूर्णांक tcpci_set_bist_data(काष्ठा tcpc_dev *tcpc, bool enable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);

	वापस regmap_update_bits(tcpci->regmap, TCPC_TCPC_CTRL, TCPC_TCPC_CTRL_BIST_TM,
				 enable ? TCPC_TCPC_CTRL_BIST_TM : 0);
पूर्ण

अटल पूर्णांक tcpci_set_roles(काष्ठा tcpc_dev *tcpc, bool attached,
			   क्रमागत typec_role role, क्रमागत typec_data_role data)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	reg = PD_REV20 << TCPC_MSG_HDR_INFO_REV_SHIFT;
	अगर (role == TYPEC_SOURCE)
		reg |= TCPC_MSG_HDR_INFO_PWR_ROLE;
	अगर (data == TYPEC_HOST)
		reg |= TCPC_MSG_HDR_INFO_DATA_ROLE;
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_MSG_HDR_INFO, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_set_pd_rx(काष्ठा tcpc_dev *tcpc, bool enable)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक ret;

	अगर (enable)
		reg = TCPC_RX_DETECT_SOP | TCPC_RX_DETECT_HARD_RESET;
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_RX_DETECT, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_get_vbus(काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tcpci->regmap, TCPC_POWER_STATUS, &reg);
	अगर (ret < 0)
		वापस ret;

	वापस !!(reg & TCPC_POWER_STATUS_VBUS_PRES);
पूर्ण

अटल bool tcpci_is_vbus_vsafe0v(काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tcpci->regmap, TCPC_EXTENDED_STATUS, &reg);
	अगर (ret < 0)
		वापस false;

	वापस !!(reg & TCPC_EXTENDED_STATUS_VSAFE0V);
पूर्ण

अटल पूर्णांक tcpci_set_vbus(काष्ठा tcpc_dev *tcpc, bool source, bool sink)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	पूर्णांक ret;

	अगर (tcpci->data->set_vbus) अणु
		ret = tcpci->data->set_vbus(tcpci, tcpci->data, source, sink);
		/* Bypass when ret > 0 */
		अगर (ret != 0)
			वापस ret < 0 ? ret : 0;
	पूर्ण

	/* Disable both source and sink first beक्रमe enabling anything */

	अगर (!source) अणु
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_DISABLE_SRC_VBUS);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!sink) अणु
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_DISABLE_SINK_VBUS);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (source) अणु
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_SRC_VBUS_DEFAULT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (sink) अणु
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_SINK_VBUS);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_pd_transmit(काष्ठा tcpc_dev *tcpc, क्रमागत tcpm_transmit_type type,
			     स्थिर काष्ठा pd_message *msg, अचिन्हित पूर्णांक negotiated_rev)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	u16 header = msg ? le16_to_cpu(msg->header) : 0;
	अचिन्हित पूर्णांक reg, cnt;
	पूर्णांक ret;

	cnt = msg ? pd_header_cnt(header) * 4 : 0;
	/**
	 * TCPCI spec क्रमbids direct access of TCPC_TX_DATA.
	 * But, since some of the chipsets offer this capability,
	 * it's fair to support both.
	 */
	अगर (tcpci->data->TX_BUF_BYTE_x_hidden) अणु
		u8 buf[TCPC_TRANSMIT_BUFFER_MAX_LEN] = अणु0,पूर्ण;
		u8 pos = 0;

		/* Payload + header + TCPC_TX_BYTE_CNT */
		buf[pos++] = cnt + 2;

		अगर (msg)
			स_नकल(&buf[pos], &msg->header, माप(msg->header));

		pos += माप(header);

		अगर (cnt > 0)
			स_नकल(&buf[pos], msg->payload, cnt);

		pos += cnt;
		ret = regmap_raw_ग_लिखो(tcpci->regmap, TCPC_TX_BYTE_CNT, buf, pos);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_TX_BYTE_CNT, cnt + 2);
		अगर (ret < 0)
			वापस ret;

		ret = tcpci_ग_लिखो16(tcpci, TCPC_TX_HDR, header);
		अगर (ret < 0)
			वापस ret;

		अगर (cnt > 0) अणु
			ret = regmap_raw_ग_लिखो(tcpci->regmap, TCPC_TX_DATA, &msg->payload, cnt);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* nRetryCount is 3 in PD2.0 spec where 2 in PD3.0 spec */
	reg = ((negotiated_rev > PD_REV20 ? PD_RETRY_COUNT_3_0_OR_HIGHER : PD_RETRY_COUNT_DEFAULT)
	       << TCPC_TRANSMIT_RETRY_SHIFT) | (type << TCPC_TRANSMIT_TYPE_SHIFT);
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_TRANSMIT, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_init(काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा tcpci *tcpci = tcpc_to_tcpci(tcpc);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(2000); /* XXX */
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		ret = regmap_पढ़ो(tcpci->regmap, TCPC_POWER_STATUS, &reg);
		अगर (ret < 0)
			वापस ret;
		अगर (!(reg & TCPC_POWER_STATUS_UNINIT))
			अवरोध;
		usleep_range(10000, 20000);
	पूर्ण
	अगर (समय_after(jअगरfies, समयout))
		वापस -ETIMEDOUT;

	/* Handle venकरोr init */
	अगर (tcpci->data->init) अणु
		ret = tcpci->data->init(tcpci, tcpci->data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Clear all events */
	ret = tcpci_ग_लिखो16(tcpci, TCPC_ALERT, 0xffff);
	अगर (ret < 0)
		वापस ret;

	अगर (tcpci->controls_vbus)
		reg = TCPC_POWER_STATUS_VBUS_PRES;
	अन्यथा
		reg = 0;
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_POWER_STATUS_MASK, reg);
	अगर (ret < 0)
		वापस ret;

	/* Enable Vbus detection */
	ret = regmap_ग_लिखो(tcpci->regmap, TCPC_COMMAND,
			   TCPC_CMD_ENABLE_VBUS_DETECT);
	अगर (ret < 0)
		वापस ret;

	reg = TCPC_ALERT_TX_SUCCESS | TCPC_ALERT_TX_FAILED |
		TCPC_ALERT_TX_DISCARDED | TCPC_ALERT_RX_STATUS |
		TCPC_ALERT_RX_HARD_RST | TCPC_ALERT_CC_STATUS;
	अगर (tcpci->controls_vbus)
		reg |= TCPC_ALERT_POWER_STATUS;
	/* Enable VSAFE0V status पूर्णांकerrupt when detecting VSAFE0V is supported */
	अगर (tcpci->data->vbus_vsafe0v) अणु
		reg |= TCPC_ALERT_EXTENDED_STATUS;
		ret = regmap_ग_लिखो(tcpci->regmap, TCPC_EXTENDED_STATUS_MASK,
				   TCPC_EXTENDED_STATUS_VSAFE0V);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस tcpci_ग_लिखो16(tcpci, TCPC_ALERT_MASK, reg);
पूर्ण

irqवापस_t tcpci_irq(काष्ठा tcpci *tcpci)
अणु
	u16 status;
	पूर्णांक ret;
	अचिन्हित पूर्णांक raw;

	tcpci_पढ़ो16(tcpci, TCPC_ALERT, &status);

	/*
	 * Clear alert status क्रम everything except RX_STATUS, which shouldn't
	 * be cleared until we have successfully retrieved message.
	 */
	अगर (status & ~TCPC_ALERT_RX_STATUS)
		tcpci_ग_लिखो16(tcpci, TCPC_ALERT,
			      status & ~TCPC_ALERT_RX_STATUS);

	अगर (status & TCPC_ALERT_CC_STATUS)
		tcpm_cc_change(tcpci->port);

	अगर (status & TCPC_ALERT_POWER_STATUS) अणु
		regmap_पढ़ो(tcpci->regmap, TCPC_POWER_STATUS_MASK, &raw);
		/*
		 * If घातer status mask has been reset, then the TCPC
		 * has reset.
		 */
		अगर (raw == 0xff)
			tcpm_tcpc_reset(tcpci->port);
		अन्यथा
			tcpm_vbus_change(tcpci->port);
	पूर्ण

	अगर (status & TCPC_ALERT_RX_STATUS) अणु
		काष्ठा pd_message msg;
		अचिन्हित पूर्णांक cnt, payload_cnt;
		u16 header;

		regmap_पढ़ो(tcpci->regmap, TCPC_RX_BYTE_CNT, &cnt);
		/*
		 * 'cnt' corresponds to READABLE_BYTE_COUNT in section 4.4.14
		 * of the TCPCI spec [Rev 2.0 Ver 1.0 October 2017] and is
		 * defined in table 4-36 as one greater than the number of
		 * bytes received. And that number includes the header. So:
		 */
		अगर (cnt > 3)
			payload_cnt = cnt - (1 + माप(msg.header));
		अन्यथा
			payload_cnt = 0;

		tcpci_पढ़ो16(tcpci, TCPC_RX_HDR, &header);
		msg.header = cpu_to_le16(header);

		अगर (WARN_ON(payload_cnt > माप(msg.payload)))
			payload_cnt = माप(msg.payload);

		अगर (payload_cnt > 0)
			regmap_raw_पढ़ो(tcpci->regmap, TCPC_RX_DATA,
					&msg.payload, payload_cnt);

		/* Read complete, clear RX status alert bit */
		tcpci_ग_लिखो16(tcpci, TCPC_ALERT, TCPC_ALERT_RX_STATUS);

		tcpm_pd_receive(tcpci->port, &msg);
	पूर्ण

	अगर (status & TCPC_ALERT_EXTENDED_STATUS) अणु
		ret = regmap_पढ़ो(tcpci->regmap, TCPC_EXTENDED_STATUS, &raw);
		अगर (!ret && (raw & TCPC_EXTENDED_STATUS_VSAFE0V))
			tcpm_vbus_change(tcpci->port);
	पूर्ण

	अगर (status & TCPC_ALERT_RX_HARD_RST)
		tcpm_pd_hard_reset(tcpci->port);

	अगर (status & TCPC_ALERT_TX_SUCCESS)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_SUCCESS);
	अन्यथा अगर (status & TCPC_ALERT_TX_DISCARDED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_DISCARDED);
	अन्यथा अगर (status & TCPC_ALERT_TX_FAILED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_FAILED);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(tcpci_irq);

अटल irqवापस_t _tcpci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tcpci_chip *chip = dev_id;

	वापस tcpci_irq(chip->tcpci);
पूर्ण

अटल स्थिर काष्ठा regmap_config tcpci_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0x7F, /* 0x80 .. 0xFF are venकरोr defined */
पूर्ण;

अटल पूर्णांक tcpci_parse_config(काष्ठा tcpci *tcpci)
अणु
	tcpci->controls_vbus = true; /* XXX */

	tcpci->tcpc.fwnode = device_get_named_child_node(tcpci->dev,
							 "connector");
	अगर (!tcpci->tcpc.fwnode) अणु
		dev_err(tcpci->dev, "Can't find connector node.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा tcpci *tcpci_रेजिस्टर_port(काष्ठा device *dev, काष्ठा tcpci_data *data)
अणु
	काष्ठा tcpci *tcpci;
	पूर्णांक err;

	tcpci = devm_kzalloc(dev, माप(*tcpci), GFP_KERNEL);
	अगर (!tcpci)
		वापस ERR_PTR(-ENOMEM);

	tcpci->dev = dev;
	tcpci->data = data;
	tcpci->regmap = data->regmap;

	tcpci->tcpc.init = tcpci_init;
	tcpci->tcpc.get_vbus = tcpci_get_vbus;
	tcpci->tcpc.set_vbus = tcpci_set_vbus;
	tcpci->tcpc.set_cc = tcpci_set_cc;
	tcpci->tcpc.get_cc = tcpci_get_cc;
	tcpci->tcpc.set_polarity = tcpci_set_polarity;
	tcpci->tcpc.set_vconn = tcpci_set_vconn;
	tcpci->tcpc.start_toggling = tcpci_start_toggling;

	tcpci->tcpc.set_pd_rx = tcpci_set_pd_rx;
	tcpci->tcpc.set_roles = tcpci_set_roles;
	tcpci->tcpc.pd_transmit = tcpci_pd_transmit;
	tcpci->tcpc.set_bist_data = tcpci_set_bist_data;
	tcpci->tcpc.enable_frs = tcpci_enable_frs;
	tcpci->tcpc.frs_sourcing_vbus = tcpci_frs_sourcing_vbus;
	tcpci->tcpc.set_partner_usb_comm_capable = tcpci_set_partner_usb_comm_capable;

	अगर (tcpci->data->स्वतः_disअक्षरge_disconnect) अणु
		tcpci->tcpc.enable_स्वतः_vbus_disअक्षरge = tcpci_enable_स्वतः_vbus_disअक्षरge;
		tcpci->tcpc.set_स्वतः_vbus_disअक्षरge_threshold =
			tcpci_set_स्वतः_vbus_disअक्षरge_threshold;
		regmap_update_bits(tcpci->regmap, TCPC_POWER_CTRL, TCPC_POWER_CTRL_BLEED_DISCHARGE,
				   TCPC_POWER_CTRL_BLEED_DISCHARGE);
	पूर्ण

	अगर (tcpci->data->vbus_vsafe0v)
		tcpci->tcpc.is_vbus_vsafe0v = tcpci_is_vbus_vsafe0v;

	err = tcpci_parse_config(tcpci);
	अगर (err < 0)
		वापस ERR_PTR(err);

	tcpci->port = tcpm_रेजिस्टर_port(tcpci->dev, &tcpci->tcpc);
	अगर (IS_ERR(tcpci->port))
		वापस ERR_CAST(tcpci->port);

	वापस tcpci;
पूर्ण
EXPORT_SYMBOL_GPL(tcpci_रेजिस्टर_port);

व्योम tcpci_unरेजिस्टर_port(काष्ठा tcpci *tcpci)
अणु
	tcpm_unरेजिस्टर_port(tcpci->port);
पूर्ण
EXPORT_SYMBOL_GPL(tcpci_unरेजिस्टर_port);

अटल पूर्णांक tcpci_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा tcpci_chip *chip;
	पूर्णांक err;
	u16 val = 0;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->data.regmap = devm_regmap_init_i2c(client, &tcpci_regmap_config);
	अगर (IS_ERR(chip->data.regmap))
		वापस PTR_ERR(chip->data.regmap);

	i2c_set_clientdata(client, chip);

	/* Disable chip पूर्णांकerrupts beक्रमe requesting irq */
	err = regmap_raw_ग_लिखो(chip->data.regmap, TCPC_ALERT_MASK, &val,
			       माप(u16));
	अगर (err < 0)
		वापस err;

	chip->tcpci = tcpci_रेजिस्टर_port(&client->dev, &chip->data);
	अगर (IS_ERR(chip->tcpci))
		वापस PTR_ERR(chip->tcpci);

	err = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					_tcpci_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					dev_name(&client->dev), chip);
	अगर (err < 0) अणु
		tcpci_unरेजिस्टर_port(chip->tcpci);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tcpci_chip *chip = i2c_get_clientdata(client);
	पूर्णांक err;

	/* Disable chip पूर्णांकerrupts beक्रमe unरेजिस्टरing port */
	err = tcpci_ग_लिखो16(chip->tcpci, TCPC_ALERT_MASK, 0);
	अगर (err < 0)
		वापस err;

	tcpci_unरेजिस्टर_port(chip->tcpci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tcpci_id[] = अणु
	अणु "tcpci", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tcpci_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tcpci_of_match[] = अणु
	अणु .compatible = "nxp,ptn5110", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tcpci_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tcpci_i2c_driver = अणु
	.driver = अणु
		.name = "tcpci",
		.of_match_table = of_match_ptr(tcpci_of_match),
	पूर्ण,
	.probe = tcpci_probe,
	.हटाओ = tcpci_हटाओ,
	.id_table = tcpci_id,
पूर्ण;
module_i2c_driver(tcpci_i2c_driver);

MODULE_DESCRIPTION("USB Type-C Port Controller Interface driver");
MODULE_LICENSE("GPL");
