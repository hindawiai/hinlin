<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * typec_wcove.c - WhiskeyCove PMIC USB Type-C PHY driver
 *
 * Copyright (C) 2017 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>

/* Register offsets */
#घोषणा WCOVE_CHGRIRQ0		0x4e09

#घोषणा USBC_CONTROL1		0x7001
#घोषणा USBC_CONTROL2		0x7002
#घोषणा USBC_CONTROL3		0x7003
#घोषणा USBC_CC1_CTRL		0x7004
#घोषणा USBC_CC2_CTRL		0x7005
#घोषणा USBC_STATUS1		0x7007
#घोषणा USBC_STATUS2		0x7008
#घोषणा USBC_STATUS3		0x7009
#घोषणा USBC_CC1		0x700a
#घोषणा USBC_CC2		0x700b
#घोषणा USBC_CC1_STATUS		0x700c
#घोषणा USBC_CC2_STATUS		0x700d
#घोषणा USBC_IRQ1		0x7015
#घोषणा USBC_IRQ2		0x7016
#घोषणा USBC_IRQMASK1		0x7017
#घोषणा USBC_IRQMASK2		0x7018
#घोषणा USBC_PDCFG2		0x701a
#घोषणा USBC_PDCFG3		0x701b
#घोषणा USBC_PDSTATUS		0x701c
#घोषणा USBC_RXSTATUS		0x701d
#घोषणा USBC_RXINFO		0x701e
#घोषणा USBC_TXCMD		0x701f
#घोषणा USBC_TXINFO		0x7020
#घोषणा USBC_RX_DATA		0x7028
#घोषणा USBC_TX_DATA		0x7047

/* Register bits */

#घोषणा USBC_CONTROL1_MODE_MASK		0x3
#घोषणा   USBC_CONTROL1_MODE_SNK	0
#घोषणा   USBC_CONTROL1_MODE_SNKACC	1
#घोषणा   USBC_CONTROL1_MODE_SRC	2
#घोषणा   USBC_CONTROL1_MODE_SRCACC	3
#घोषणा   USBC_CONTROL1_MODE_DRP	4
#घोषणा   USBC_CONTROL1_MODE_DRPACC	5
#घोषणा   USBC_CONTROL1_MODE_TEST	7
#घोषणा USBC_CONTROL1_CURSRC_MASK	0xc
#घोषणा   USBC_CONTROL1_CURSRC_UA_0	(0 << 3)
#घोषणा   USBC_CONTROL1_CURSRC_UA_80	(1 << 3)
#घोषणा   USBC_CONTROL1_CURSRC_UA_180	(2 << 3)
#घोषणा   USBC_CONTROL1_CURSRC_UA_330	(3 << 3)
#घोषणा USBC_CONTROL1_DRPTOGGLE_RANDOM	0xe0

#घोषणा USBC_CONTROL2_UNATT_SNK		BIT(0)
#घोषणा USBC_CONTROL2_UNATT_SRC		BIT(1)
#घोषणा USBC_CONTROL2_DIS_ST		BIT(2)

#घोषणा USBC_CONTROL3_DET_DIS		BIT(0)
#घोषणा USBC_CONTROL3_PD_DIS		BIT(1)
#घोषणा USBC_CONTROL3_RESETPHY		BIT(2)

#घोषणा USBC_CC_CTRL_PU_EN		BIT(0)
#घोषणा USBC_CC_CTRL_VCONN_EN		BIT(1)
#घोषणा USBC_CC_CTRL_TX_EN		BIT(2)
#घोषणा USBC_CC_CTRL_PD_EN		BIT(3)
#घोषणा USBC_CC_CTRL_CDET_EN		BIT(4)
#घोषणा USBC_CC_CTRL_RDET_EN		BIT(5)
#घोषणा USBC_CC_CTRL_ADC_EN		BIT(6)
#घोषणा USBC_CC_CTRL_VBUSOK		BIT(7)

#घोषणा USBC_STATUS1_DET_ONGOING	BIT(6)
#घोषणा USBC_STATUS1_RSLT(r)		((r) & 0xf)
#घोषणा USBC_RSLT_NOTHING		0
#घोषणा USBC_RSLT_SRC_DEFAULT		1
#घोषणा USBC_RSLT_SRC_1_5A		2
#घोषणा USBC_RSLT_SRC_3_0A		3
#घोषणा USBC_RSLT_SNK			4
#घोषणा USBC_RSLT_DEBUG_ACC		5
#घोषणा USBC_RSLT_AUDIO_ACC		6
#घोषणा USBC_RSLT_UNDEF			15
#घोषणा USBC_STATUS1_ORIENT(r)		(((r) >> 4) & 0x3)
#घोषणा USBC_ORIENT_NORMAL		1
#घोषणा USBC_ORIENT_REVERSE		2

#घोषणा USBC_STATUS2_VBUS_REQ		BIT(5)

#घोषणा UCSC_CC_STATUS_SNK_RP		BIT(0)
#घोषणा UCSC_CC_STATUS_PWRDEFSNK	BIT(1)
#घोषणा UCSC_CC_STATUS_PWR_1P5A_SNK	BIT(2)
#घोषणा UCSC_CC_STATUS_PWR_3A_SNK	BIT(3)
#घोषणा UCSC_CC_STATUS_SRC_RP		BIT(4)
#घोषणा UCSC_CC_STATUS_RX(r)		(((r) >> 5) & 0x3)
#घोषणा   USBC_CC_STATUS_RD		1
#घोषणा   USBC_CC_STATUS_RA		2

#घोषणा USBC_IRQ1_ADCDONE1		BIT(2)
#घोषणा USBC_IRQ1_OVERTEMP		BIT(1)
#घोषणा USBC_IRQ1_SHORT			BIT(0)

#घोषणा USBC_IRQ2_CC_CHANGE		BIT(7)
#घोषणा USBC_IRQ2_RX_PD			BIT(6)
#घोषणा USBC_IRQ2_RX_HR			BIT(5)
#घोषणा USBC_IRQ2_RX_CR			BIT(4)
#घोषणा USBC_IRQ2_TX_SUCCESS		BIT(3)
#घोषणा USBC_IRQ2_TX_FAIL		BIT(2)

#घोषणा USBC_IRQMASK1_ALL	(USBC_IRQ1_ADCDONE1 | USBC_IRQ1_OVERTEMP | \
				 USBC_IRQ1_SHORT)

#घोषणा USBC_IRQMASK2_ALL	(USBC_IRQ2_CC_CHANGE | USBC_IRQ2_RX_PD | \
				 USBC_IRQ2_RX_HR | USBC_IRQ2_RX_CR | \
				 USBC_IRQ2_TX_SUCCESS | USBC_IRQ2_TX_FAIL)

#घोषणा USBC_PDCFG2_SOP			BIT(0)
#घोषणा USBC_PDCFG2_SOP_P		BIT(1)
#घोषणा USBC_PDCFG2_SOP_PP		BIT(2)
#घोषणा USBC_PDCFG2_SOP_P_DEBUG		BIT(3)
#घोषणा USBC_PDCFG2_SOP_PP_DEBUG	BIT(4)

#घोषणा USBC_PDCFG3_DATAROLE_SHIFT	1
#घोषणा USBC_PDCFG3_SOP_SHIFT		2

#घोषणा USBC_RXSTATUS_RXCLEAR		BIT(0)
#घोषणा USBC_RXSTATUS_RXDATA		BIT(7)

#घोषणा USBC_RXINFO_RXBYTES(i)		(((i) >> 3) & 0x1f)

#घोषणा USBC_TXCMD_BUF_RDY		BIT(0)
#घोषणा USBC_TXCMD_START		BIT(1)
#घोषणा USBC_TXCMD_NOP			(0 << 5)
#घोषणा USBC_TXCMD_MSG			(1 << 5)
#घोषणा USBC_TXCMD_CR			(2 << 5)
#घोषणा USBC_TXCMD_HR			(3 << 5)
#घोषणा USBC_TXCMD_BIST			(4 << 5)

#घोषणा USBC_TXINFO_RETRIES(d)		(d << 3)

काष्ठा wcove_typec अणु
	काष्ठा mutex lock; /* device lock */
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	guid_t guid;

	bool vbus;

	काष्ठा tcpc_dev tcpc;
	काष्ठा tcpm_port *tcpm;
पूर्ण;

#घोषणा tcpc_to_wcove(_tcpc_) container_of(_tcpc_, काष्ठा wcove_typec, tcpc)

क्रमागत wcove_typec_func अणु
	WCOVE_FUNC_DRIVE_VBUS = 1,
	WCOVE_FUNC_ORIENTATION,
	WCOVE_FUNC_ROLE,
	WCOVE_FUNC_DRIVE_VCONN,
पूर्ण;

क्रमागत wcove_typec_orientation अणु
	WCOVE_ORIENTATION_NORMAL,
	WCOVE_ORIENTATION_REVERSE,
पूर्ण;

क्रमागत wcove_typec_role अणु
	WCOVE_ROLE_HOST,
	WCOVE_ROLE_DEVICE,
पूर्ण;

#घोषणा WCOVE_DSM_UUID		"482383f0-2876-4e49-8685-db66211af037"

अटल पूर्णांक wcove_typec_func(काष्ठा wcove_typec *wcove,
			    क्रमागत wcove_typec_func func, पूर्णांक param)
अणु
	जोड़ acpi_object *obj;
	जोड़ acpi_object पंचांगp;
	जोड़ acpi_object argv4 = ACPI_INIT_DSM_ARGV4(1, &पंचांगp);

	पंचांगp.type = ACPI_TYPE_INTEGER;
	पंचांगp.पूर्णांकeger.value = param;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(wcove->dev), &wcove->guid, 1, func,
				&argv4);
	अगर (!obj) अणु
		dev_err(wcove->dev, "%s: failed to evaluate _DSM\n", __func__);
		वापस -EIO;
	पूर्ण

	ACPI_FREE(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक wcove_init(काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(wcove->regmap, USBC_CONTROL1, 0);
	अगर (ret)
		वापस ret;

	/* Unmask everything */
	ret = regmap_ग_लिखो(wcove->regmap, USBC_IRQMASK1, 0);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(wcove->regmap, USBC_IRQMASK2, 0);
पूर्ण

अटल पूर्णांक wcove_get_vbus(काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक cc1ctrl;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wcove->regmap, USBC_CC1_CTRL, &cc1ctrl);
	अगर (ret)
		वापस ret;

	wcove->vbus = !!(cc1ctrl & USBC_CC_CTRL_VBUSOK);

	वापस wcove->vbus;
पूर्ण

अटल पूर्णांक wcove_set_vbus(काष्ठा tcpc_dev *tcpc, bool on, bool sink)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);

	वापस wcove_typec_func(wcove, WCOVE_FUNC_DRIVE_VBUS, on);
पूर्ण

अटल पूर्णांक wcove_set_vconn(काष्ठा tcpc_dev *tcpc, bool on)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);

	वापस wcove_typec_func(wcove, WCOVE_FUNC_DRIVE_VCONN, on);
पूर्ण

अटल क्रमागत typec_cc_status wcove_to_typec_cc(अचिन्हित पूर्णांक cc)
अणु
	अगर (cc & UCSC_CC_STATUS_SNK_RP) अणु
		अगर (cc & UCSC_CC_STATUS_PWRDEFSNK)
			वापस TYPEC_CC_RP_DEF;
		अन्यथा अगर (cc & UCSC_CC_STATUS_PWR_1P5A_SNK)
			वापस TYPEC_CC_RP_1_5;
		अन्यथा अगर (cc & UCSC_CC_STATUS_PWR_3A_SNK)
			वापस TYPEC_CC_RP_3_0;
	पूर्ण अन्यथा अणु
		चयन (UCSC_CC_STATUS_RX(cc)) अणु
		हाल USBC_CC_STATUS_RD:
			वापस TYPEC_CC_RD;
		हाल USBC_CC_STATUS_RA:
			वापस TYPEC_CC_RA;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस TYPEC_CC_OPEN;
पूर्ण

अटल पूर्णांक wcove_get_cc(काष्ठा tcpc_dev *tcpc, क्रमागत typec_cc_status *cc1,
			क्रमागत typec_cc_status *cc2)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक cc1_status;
	अचिन्हित पूर्णांक cc2_status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wcove->regmap, USBC_CC1_STATUS, &cc1_status);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(wcove->regmap, USBC_CC2_STATUS, &cc2_status);
	अगर (ret)
		वापस ret;

	*cc1 = wcove_to_typec_cc(cc1_status);
	*cc2 = wcove_to_typec_cc(cc2_status);

	वापस 0;
पूर्ण

अटल पूर्णांक wcove_set_cc(काष्ठा tcpc_dev *tcpc, क्रमागत typec_cc_status cc)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक ctrl;

	चयन (cc) अणु
	हाल TYPEC_CC_RD:
		ctrl = USBC_CONTROL1_MODE_SNK;
		अवरोध;
	हाल TYPEC_CC_RP_DEF:
		ctrl = USBC_CONTROL1_CURSRC_UA_80 | USBC_CONTROL1_MODE_SRC;
		अवरोध;
	हाल TYPEC_CC_RP_1_5:
		ctrl = USBC_CONTROL1_CURSRC_UA_180 | USBC_CONTROL1_MODE_SRC;
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		ctrl = USBC_CONTROL1_CURSRC_UA_330 | USBC_CONTROL1_MODE_SRC;
		अवरोध;
	हाल TYPEC_CC_OPEN:
		ctrl = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_ग_लिखो(wcove->regmap, USBC_CONTROL1, ctrl);
पूर्ण

अटल पूर्णांक wcove_set_polarity(काष्ठा tcpc_dev *tcpc, क्रमागत typec_cc_polarity pol)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);

	वापस wcove_typec_func(wcove, WCOVE_FUNC_ORIENTATION, pol);
पूर्ण

अटल पूर्णांक wcove_set_current_limit(काष्ठा tcpc_dev *tcpc, u32 max_ma, u32 mv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक wcove_set_roles(काष्ठा tcpc_dev *tcpc, bool attached,
			   क्रमागत typec_role role, क्रमागत typec_data_role data)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = wcove_typec_func(wcove, WCOVE_FUNC_ROLE, data == TYPEC_HOST ?
			       WCOVE_ROLE_HOST : WCOVE_ROLE_DEVICE);
	अगर (ret)
		वापस ret;

	val = role;
	val |= data << USBC_PDCFG3_DATAROLE_SHIFT;
	val |= PD_REV20 << USBC_PDCFG3_SOP_SHIFT;

	वापस regmap_ग_लिखो(wcove->regmap, USBC_PDCFG3, val);
पूर्ण

अटल पूर्णांक wcove_set_pd_rx(काष्ठा tcpc_dev *tcpc, bool on)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);

	वापस regmap_ग_लिखो(wcove->regmap, USBC_PDCFG2,
			    on ? USBC_PDCFG2_SOP : 0);
पूर्ण

अटल पूर्णांक wcove_pd_transmit(काष्ठा tcpc_dev *tcpc,
			     क्रमागत tcpm_transmit_type type,
			     स्थिर काष्ठा pd_message *msg,
			     अचिन्हित पूर्णांक negotiated_rev)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक info = 0;
	अचिन्हित पूर्णांक cmd;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wcove->regmap, USBC_TXCMD, &cmd);
	अगर (ret)
		वापस ret;

	अगर (!(cmd & USBC_TXCMD_BUF_RDY)) अणु
		dev_warn(wcove->dev, "%s: Last transmission still ongoing!",
			 __func__);
		वापस -EBUSY;
	पूर्ण

	अगर (msg) अणु
		स्थिर u8 *data = (व्योम *)msg;
		पूर्णांक i;

		क्रम (i = 0; i < pd_header_cnt_le(msg->header) * 4 + 2; i++) अणु
			ret = regmap_ग_लिखो(wcove->regmap, USBC_TX_DATA + i,
					   data[i]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	चयन (type) अणु
	हाल TCPC_TX_SOP:
	हाल TCPC_TX_SOP_PRIME:
	हाल TCPC_TX_SOP_PRIME_PRIME:
	हाल TCPC_TX_SOP_DEBUG_PRIME:
	हाल TCPC_TX_SOP_DEBUG_PRIME_PRIME:
		info = type + 1;
		cmd = USBC_TXCMD_MSG;
		अवरोध;
	हाल TCPC_TX_HARD_RESET:
		cmd = USBC_TXCMD_HR;
		अवरोध;
	हाल TCPC_TX_CABLE_RESET:
		cmd = USBC_TXCMD_CR;
		अवरोध;
	हाल TCPC_TX_BIST_MODE_2:
		cmd = USBC_TXCMD_BIST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* NOTE Setting maximum number of retries (7) */
	ret = regmap_ग_लिखो(wcove->regmap, USBC_TXINFO,
			   info | USBC_TXINFO_RETRIES(7));
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(wcove->regmap, USBC_TXCMD, cmd | USBC_TXCMD_START);
पूर्ण

अटल पूर्णांक wcove_start_toggling(काष्ठा tcpc_dev *tcpc,
				क्रमागत typec_port_type port_type,
				क्रमागत typec_cc_status cc)
अणु
	काष्ठा wcove_typec *wcove = tcpc_to_wcove(tcpc);
	अचिन्हित पूर्णांक usbc_ctrl;

	अगर (port_type != TYPEC_PORT_DRP)
		वापस -EOPNOTSUPP;

	usbc_ctrl = USBC_CONTROL1_MODE_DRP | USBC_CONTROL1_DRPTOGGLE_RANDOM;

	चयन (cc) अणु
	हाल TYPEC_CC_RP_1_5:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_180;
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_330;
		अवरोध;
	शेष:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_80;
		अवरोध;
	पूर्ण

	वापस regmap_ग_लिखो(wcove->regmap, USBC_CONTROL1, usbc_ctrl);
पूर्ण

अटल पूर्णांक wcove_पढ़ो_rx_buffer(काष्ठा wcove_typec *wcove, व्योम *msg)
अणु
	अचिन्हित पूर्णांक info;
	पूर्णांक ret;
	पूर्णांक i;

	ret = regmap_पढ़ो(wcove->regmap, USBC_RXINFO, &info);
	अगर (ret)
		वापस ret;

	/* FIXME: Check that USBC_RXINFO_RXBYTES(info) matches the header */

	क्रम (i = 0; i < USBC_RXINFO_RXBYTES(info); i++) अणु
		ret = regmap_पढ़ो(wcove->regmap, USBC_RX_DATA + i, msg + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो(wcove->regmap, USBC_RXSTATUS,
			    USBC_RXSTATUS_RXCLEAR);
पूर्ण

अटल irqवापस_t wcove_typec_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wcove_typec *wcove = data;
	अचिन्हित पूर्णांक usbc_irq1 = 0;
	अचिन्हित पूर्णांक usbc_irq2 = 0;
	अचिन्हित पूर्णांक cc1ctrl;
	पूर्णांक ret;

	mutex_lock(&wcove->lock);

	/* Read.. */
	ret = regmap_पढ़ो(wcove->regmap, USBC_IRQ1, &usbc_irq1);
	अगर (ret)
		जाओ err;

	ret = regmap_पढ़ो(wcove->regmap, USBC_IRQ2, &usbc_irq2);
	अगर (ret)
		जाओ err;

	ret = regmap_पढ़ो(wcove->regmap, USBC_CC1_CTRL, &cc1ctrl);
	अगर (ret)
		जाओ err;

	अगर (!wcove->tcpm)
		जाओ err;

	/* ..check.. */
	अगर (usbc_irq1 & USBC_IRQ1_OVERTEMP) अणु
		dev_err(wcove->dev, "VCONN Switch Over Temperature!\n");
		wcove_typec_func(wcove, WCOVE_FUNC_DRIVE_VCONN, false);
		/* REVISIT: Report an error? */
	पूर्ण

	अगर (usbc_irq1 & USBC_IRQ1_SHORT) अणु
		dev_err(wcove->dev, "VCONN Switch Short Circuit!\n");
		wcove_typec_func(wcove, WCOVE_FUNC_DRIVE_VCONN, false);
		/* REVISIT: Report an error? */
	पूर्ण

	अगर (wcove->vbus != !!(cc1ctrl & USBC_CC_CTRL_VBUSOK))
		tcpm_vbus_change(wcove->tcpm);

	/* REVISIT: See अगर tcpm code can be made to consider Type-C HW FSMs */
	अगर (usbc_irq2 & USBC_IRQ2_CC_CHANGE)
		tcpm_cc_change(wcove->tcpm);

	अगर (usbc_irq2 & USBC_IRQ2_RX_PD) अणु
		अचिन्हित पूर्णांक status;

		/*
		 * FIXME: Need to check अगर TX is ongoing and report
		 * TX_सूचीEGARDED अगर needed?
		 */

		ret = regmap_पढ़ो(wcove->regmap, USBC_RXSTATUS, &status);
		अगर (ret)
			जाओ err;

		/* Flush all buffers */
		जबतक (status & USBC_RXSTATUS_RXDATA) अणु
			काष्ठा pd_message msg;

			ret = wcove_पढ़ो_rx_buffer(wcove, &msg);
			अगर (ret) अणु
				dev_err(wcove->dev, "%s: RX read failed\n",
					__func__);
				जाओ err;
			पूर्ण

			tcpm_pd_receive(wcove->tcpm, &msg);

			ret = regmap_पढ़ो(wcove->regmap, USBC_RXSTATUS,
					  &status);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (usbc_irq2 & USBC_IRQ2_RX_HR)
		tcpm_pd_hard_reset(wcove->tcpm);

	/* REVISIT: अगर (usbc_irq2 & USBC_IRQ2_RX_CR) */

	अगर (usbc_irq2 & USBC_IRQ2_TX_SUCCESS)
		tcpm_pd_transmit_complete(wcove->tcpm, TCPC_TX_SUCCESS);

	अगर (usbc_irq2 & USBC_IRQ2_TX_FAIL)
		tcpm_pd_transmit_complete(wcove->tcpm, TCPC_TX_FAILED);

err:
	/* ..and clear. */
	अगर (usbc_irq1) अणु
		ret = regmap_ग_लिखो(wcove->regmap, USBC_IRQ1, usbc_irq1);
		अगर (ret)
			dev_WARN(wcove->dev, "%s failed to clear IRQ1\n",
				 __func__);
	पूर्ण

	अगर (usbc_irq2) अणु
		ret = regmap_ग_लिखो(wcove->regmap, USBC_IRQ2, usbc_irq2);
		अगर (ret)
			dev_WARN(wcove->dev, "%s failed to clear IRQ2\n",
				 __func__);
	पूर्ण

	/* REVISIT: Clear WhiskeyCove CHGR Type-C पूर्णांकerrupt */
	regmap_ग_लिखो(wcove->regmap, WCOVE_CHGRIRQ0, BIT(5));

	mutex_unlock(&wcove->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * The following घातer levels should be safe to use with Joule board.
 */
अटल स्थिर u32 src_pकरो[] = अणु
	PDO_FIXED(5000, 1500, PDO_FIXED_DUAL_ROLE | PDO_FIXED_DATA_SWAP |
		  PDO_FIXED_USB_COMM),
पूर्ण;

अटल स्थिर u32 snk_pकरो[] = अणु
	PDO_FIXED(5000, 500, PDO_FIXED_DUAL_ROLE | PDO_FIXED_DATA_SWAP |
		  PDO_FIXED_USB_COMM),
	PDO_VAR(5000, 12000, 3000),
पूर्ण;

अटल स्थिर काष्ठा property_entry wcove_props[] = अणु
	PROPERTY_ENTRY_STRING("data-role", "dual"),
	PROPERTY_ENTRY_STRING("power-role", "dual"),
	PROPERTY_ENTRY_STRING("try-power-role", "sink"),
	PROPERTY_ENTRY_U32_ARRAY("source-pdos", src_pकरो),
	PROPERTY_ENTRY_U32_ARRAY("sink-pdos", snk_pकरो),
	PROPERTY_ENTRY_U32("op-sink-microwatt", 15000000),
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक wcove_typec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wcove_typec *wcove;
	पूर्णांक irq;
	पूर्णांक ret;

	wcove = devm_kzalloc(&pdev->dev, माप(*wcove), GFP_KERNEL);
	अगर (!wcove)
		वापस -ENOMEM;

	mutex_init(&wcove->lock);
	wcove->dev = &pdev->dev;
	wcove->regmap = pmic->regmap;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	irq = regmap_irq_get_virq(pmic->irq_chip_data_chgr, irq);
	अगर (irq < 0)
		वापस irq;

	ret = guid_parse(WCOVE_DSM_UUID, &wcove->guid);
	अगर (ret)
		वापस ret;

	अगर (!acpi_check_dsm(ACPI_HANDLE(&pdev->dev), &wcove->guid, 0, 0x1f)) अणु
		dev_err(&pdev->dev, "Missing _DSM functions\n");
		वापस -ENODEV;
	पूर्ण

	wcove->tcpc.init = wcove_init;
	wcove->tcpc.get_vbus = wcove_get_vbus;
	wcove->tcpc.set_vbus = wcove_set_vbus;
	wcove->tcpc.set_cc = wcove_set_cc;
	wcove->tcpc.get_cc = wcove_get_cc;
	wcove->tcpc.set_polarity = wcove_set_polarity;
	wcove->tcpc.set_vconn = wcove_set_vconn;
	wcove->tcpc.set_current_limit = wcove_set_current_limit;
	wcove->tcpc.start_toggling = wcove_start_toggling;

	wcove->tcpc.set_pd_rx = wcove_set_pd_rx;
	wcove->tcpc.set_roles = wcove_set_roles;
	wcove->tcpc.pd_transmit = wcove_pd_transmit;

	wcove->tcpc.fwnode = fwnode_create_software_node(wcove_props, शून्य);
	अगर (IS_ERR(wcove->tcpc.fwnode))
		वापस PTR_ERR(wcove->tcpc.fwnode);

	wcove->tcpm = tcpm_रेजिस्टर_port(wcove->dev, &wcove->tcpc);
	अगर (IS_ERR(wcove->tcpm)) अणु
		fwnode_हटाओ_software_node(wcove->tcpc.fwnode);
		वापस PTR_ERR(wcove->tcpm);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wcove_typec_irq, IRQF_ONESHOT,
					"wcove_typec", wcove);
	अगर (ret) अणु
		tcpm_unरेजिस्टर_port(wcove->tcpm);
		fwnode_हटाओ_software_node(wcove->tcpc.fwnode);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wcove);
	वापस 0;
पूर्ण

अटल पूर्णांक wcove_typec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wcove_typec *wcove = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक val;

	/* Mask everything */
	regmap_पढ़ो(wcove->regmap, USBC_IRQMASK1, &val);
	regmap_ग_लिखो(wcove->regmap, USBC_IRQMASK1, val | USBC_IRQMASK1_ALL);
	regmap_पढ़ो(wcove->regmap, USBC_IRQMASK2, &val);
	regmap_ग_लिखो(wcove->regmap, USBC_IRQMASK2, val | USBC_IRQMASK2_ALL);

	tcpm_unरेजिस्टर_port(wcove->tcpm);
	fwnode_हटाओ_software_node(wcove->tcpc.fwnode);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wcove_typec_driver = अणु
	.driver = अणु
		.name		= "bxt_wcove_usbc",
	पूर्ण,
	.probe			= wcove_typec_probe,
	.हटाओ			= wcove_typec_हटाओ,
पूर्ण;

module_platक्रमm_driver(wcove_typec_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("WhiskeyCove PMIC USB Type-C PHY driver");
MODULE_ALIAS("platform:bxt_wcove_usbc");
