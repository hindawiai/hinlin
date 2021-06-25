<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synopsys G210 Test Chip driver
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#समावेश "ufshcd.h"
#समावेश "unipro.h"

#समावेश "ufshcd-dwc.h"
#समावेश "ufshci-dwc.h"
#समावेश "tc-dwc-g210.h"

/**
 * tc_dwc_g210_setup_40bit_rmmi()
 * This function configures Synopsys TC specअगरic atributes (40-bit RMMI)
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success or non-zero value on failure
 */
अटल पूर्णांक tc_dwc_g210_setup_40bit_rmmi(काष्ठा ufs_hba *hba)
अणु
	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_attrs[] = अणु
		अणु UIC_ARG_MIB(TX_GLOBALHIBERNATE), 0x00, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(REFCLKMODE), 0x01, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CसूचीECTCTRL6), 0x80, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBDIVFACTOR), 0x08, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBDCOCTRL5), 0x64, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBPRGTUNING), 0x09, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(RTOBSERVESELECT), 0x00, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(TX_REFCLKFREQ, SELIND_LN0_TX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(TX_CFGCLKFREQVAL, SELIND_LN0_TX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGEXTRATTR, SELIND_LN0_TX), 0x14,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(DITHERCTRL2, SELIND_LN0_TX), 0xd6,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RX_REFCLKFREQ, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RX_CFGCLKFREQVAL, SELIND_LN0_RX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGWIDEINLN, SELIND_LN0_RX), 4,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXCDR8, SELIND_LN0_RX), 0x80,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(सूचीECTCTRL10), 0x04, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(सूचीECTCTRL19), 0x02, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXCDR8, SELIND_LN0_RX), 0x80,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG4, SELIND_LN0_RX), 0x03,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR8, SELIND_LN0_RX), 0x16,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXसूचीECTCTRL2, SELIND_LN0_RX), 0x42,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG3, SELIND_LN0_RX), 0xa4,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXCALCTRL, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG2, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR4, SELIND_LN0_RX), 0x28,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXSQCTRL, SELIND_LN0_RX), 0x1E,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR6, SELIND_LN0_RX), 0x2f,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR6, SELIND_LN0_RX), 0x2f,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBPRGPLL2), 0x00, DME_LOCAL पूर्ण,
	पूर्ण;

	वापस ufshcd_dwc_dme_set_attrs(hba, setup_attrs,
						ARRAY_SIZE(setup_attrs));
पूर्ण

/**
 * tc_dwc_g210_setup_20bit_rmmi_lane0()
 * This function configures Synopsys TC 20-bit RMMI Lane 0
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success or non-zero value on failure
 */
अटल पूर्णांक tc_dwc_g210_setup_20bit_rmmi_lane0(काष्ठा ufs_hba *hba)
अणु
	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_attrs[] = अणु
		अणु UIC_ARG_MIB_SEL(TX_REFCLKFREQ, SELIND_LN0_TX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(TX_CFGCLKFREQVAL, SELIND_LN0_TX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RX_CFGCLKFREQVAL, SELIND_LN0_RX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGEXTRATTR, SELIND_LN0_TX), 0x12,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(DITHERCTRL2, SELIND_LN0_TX), 0xd6,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RX_REFCLKFREQ, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGWIDEINLN, SELIND_LN0_RX), 2,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXCDR8, SELIND_LN0_RX), 0x80,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(सूचीECTCTRL10), 0x04, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(सूचीECTCTRL19), 0x02, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG4, SELIND_LN0_RX), 0x03,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR8, SELIND_LN0_RX), 0x16,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXसूचीECTCTRL2, SELIND_LN0_RX), 0x42,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG3, SELIND_LN0_RX), 0xa4,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXCALCTRL, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG2, SELIND_LN0_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR4, SELIND_LN0_RX), 0x28,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXSQCTRL, SELIND_LN0_RX), 0x1E,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR6, SELIND_LN0_RX), 0x2f,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBPRGPLL2), 0x00, DME_LOCAL पूर्ण,
	पूर्ण;

	वापस ufshcd_dwc_dme_set_attrs(hba, setup_attrs,
						ARRAY_SIZE(setup_attrs));
पूर्ण

/**
 * tc_dwc_g210_setup_20bit_rmmi_lane1()
 * This function configures Synopsys TC 20-bit RMMI Lane 1
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success or non-zero value on failure
 */
अटल पूर्णांक tc_dwc_g210_setup_20bit_rmmi_lane1(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक connected_rx_lanes = 0;
	पूर्णांक connected_tx_lanes = 0;
	पूर्णांक ret = 0;

	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_tx_attrs[] = अणु
		अणु UIC_ARG_MIB_SEL(TX_REFCLKFREQ, SELIND_LN1_TX), 0x0d,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(TX_CFGCLKFREQVAL, SELIND_LN1_TX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGEXTRATTR, SELIND_LN1_TX), 0x12,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(DITHERCTRL2, SELIND_LN0_TX), 0xd6,
								DME_LOCAL पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_rx_attrs[] = अणु
		अणु UIC_ARG_MIB_SEL(RX_REFCLKFREQ, SELIND_LN1_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RX_CFGCLKFREQVAL, SELIND_LN1_RX), 0x19,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGWIDEINLN, SELIND_LN1_RX), 2,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXCDR8, SELIND_LN1_RX), 0x80,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG4, SELIND_LN1_RX), 0x03,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR8, SELIND_LN1_RX), 0x16,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXसूचीECTCTRL2, SELIND_LN1_RX), 0x42,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG3, SELIND_LN1_RX), 0xa4,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXCALCTRL, SELIND_LN1_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(ENARXसूचीECTCFG2, SELIND_LN1_RX), 0x01,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR4, SELIND_LN1_RX), 0x28,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(RXSQCTRL, SELIND_LN1_RX), 0x1E,
								DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB_SEL(CFGRXOVR6, SELIND_LN1_RX), 0x2f,
								DME_LOCAL पूर्ण,
	पूर्ण;

	/* Get the available lane count */
	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILRXDATALANES),
			&connected_rx_lanes);
	ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILTXDATALANES),
			&connected_tx_lanes);

	अगर (connected_tx_lanes == 2) अणु

		ret = ufshcd_dwc_dme_set_attrs(hba, setup_tx_attrs,
						ARRAY_SIZE(setup_tx_attrs));

		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (connected_rx_lanes == 2) अणु
		ret = ufshcd_dwc_dme_set_attrs(hba, setup_rx_attrs,
						ARRAY_SIZE(setup_rx_attrs));
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 * tc_dwc_g210_setup_20bit_rmmi()
 * This function configures Synopsys TC specअगरic atributes (20-bit RMMI)
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success or non-zero value on failure
 */
अटल पूर्णांक tc_dwc_g210_setup_20bit_rmmi(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_attrs[] = अणु
		अणु UIC_ARG_MIB(TX_GLOBALHIBERNATE), 0x00, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(REFCLKMODE), 0x01, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CसूचीECTCTRL6), 0xc0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBDIVFACTOR), 0x44, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBDCOCTRL5), 0x64, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(CBPRGTUNING), 0x09, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(RTOBSERVESELECT), 0x00, DME_LOCAL पूर्ण,
	पूर्ण;

	ret = ufshcd_dwc_dme_set_attrs(hba, setup_attrs,
						ARRAY_SIZE(setup_attrs));
	अगर (ret)
		जाओ out;

	/* Lane 0 configuration*/
	ret = tc_dwc_g210_setup_20bit_rmmi_lane0(hba);
	अगर (ret)
		जाओ out;

	/* Lane 1 configuration*/
	ret = tc_dwc_g210_setup_20bit_rmmi_lane1(hba);
	अगर (ret)
		जाओ out;

out:
	वापस ret;
पूर्ण

/**
 * tc_dwc_g210_config_40_bit()
 * This function configures Local (host) Synopsys 40-bit TC specअगरic attributes
 *
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success non-zero value on failure
 */
पूर्णांक tc_dwc_g210_config_40_bit(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	dev_info(hba->dev, "Configuring Test Chip 40-bit RMMI\n");
	ret = tc_dwc_g210_setup_40bit_rmmi(hba);
	अगर (ret) अणु
		dev_err(hba->dev, "Configuration failed\n");
		जाओ out;
	पूर्ण

	/* To ग_लिखो Shaकरोw रेजिस्टर bank to effective configuration block */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_MPHYCFGUPDT), 0x01);
	अगर (ret)
		जाओ out;

	/* To configure Debug OMC */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_DEBUGOMC), 0x01);

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tc_dwc_g210_config_40_bit);

/**
 * tc_dwc_g210_config_20_bit()
 * This function configures Local (host) Synopsys 20-bit TC specअगरic attributes
 *
 * @hba: Poपूर्णांकer to drivers काष्ठाure
 *
 * Returns 0 on success non-zero value on failure
 */
पूर्णांक tc_dwc_g210_config_20_bit(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;

	dev_info(hba->dev, "Configuring Test Chip 20-bit RMMI\n");
	ret = tc_dwc_g210_setup_20bit_rmmi(hba);
	अगर (ret) अणु
		dev_err(hba->dev, "Configuration failed\n");
		जाओ out;
	पूर्ण

	/* To ग_लिखो Shaकरोw रेजिस्टर bank to effective configuration block */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_MPHYCFGUPDT), 0x01);
	अगर (ret)
		जाओ out;

	/* To configure Debug OMC */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_DEBUGOMC), 0x01);

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tc_dwc_g210_config_20_bit);

MODULE_AUTHOR("Joao Pinto <Joao.Pinto@synopsys.com>");
MODULE_DESCRIPTION("Synopsys G210 Test Chip driver");
MODULE_LICENSE("Dual BSD/GPL");
