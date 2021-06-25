<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UFS Host driver क्रम Synopsys Designware Core
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#समावेश "ufshcd.h"
#समावेश "unipro.h"

#समावेश "ufshcd-dwc.h"
#समावेश "ufshci-dwc.h"

पूर्णांक ufshcd_dwc_dme_set_attrs(काष्ठा ufs_hba *hba,
				स्थिर काष्ठा ufshcd_dme_attr_val *v, पूर्णांक n)
अणु
	पूर्णांक ret = 0;
	पूर्णांक attr_node = 0;

	क्रम (attr_node = 0; attr_node < n; attr_node++) अणु
		ret = ufshcd_dme_set_attr(hba, v[attr_node].attr_sel,
			ATTR_SET_NOR, v[attr_node].mib_val, v[attr_node].peer);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ufshcd_dwc_dme_set_attrs);

/**
 * ufshcd_dwc_program_clk_भाग()
 * This function programs the clk भागider value. This value is needed to
 * provide 1 microsecond tick to unipro layer.
 * @hba: Private Structure poपूर्णांकer
 * @भागider_val: घड़ी भागider value to be programmed
 *
 */
अटल व्योम ufshcd_dwc_program_clk_भाग(काष्ठा ufs_hba *hba, u32 भागider_val)
अणु
	ufshcd_ग_लिखोl(hba, भागider_val, DWC_UFS_REG_HCLKDIV);
पूर्ण

/**
 * ufshcd_dwc_link_is_up()
 * Check अगर link is up
 * @hba: निजी काष्ठाure poपूर्णांकer
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक ufshcd_dwc_link_is_up(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक dme_result = 0;

	ufshcd_dme_get(hba, UIC_ARG_MIB(VS_POWERSTATE), &dme_result);

	अगर (dme_result == UFSHCD_LINK_IS_UP) अणु
		ufshcd_set_link_active(hba);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * ufshcd_dwc_connection_setup()
 * This function configures both the local side (host) and the peer side
 * (device) unipro attributes to establish the connection to application/
 * cport.
 * This function is not required अगर the hardware is properly configured to
 * have this connection setup on reset. But invoking this function करोes no
 * harm and should be fine even working with any ufs device.
 *
 * @hba: poपूर्णांकer to drivers निजी data
 *
 * Returns 0 on success non-zero value on failure
 */
अटल पूर्णांक ufshcd_dwc_connection_setup(काष्ठा ufs_hba *hba)
अणु
	अटल स्थिर काष्ठा ufshcd_dme_attr_val setup_attrs[] = अणु
		अणु UIC_ARG_MIB(T_CONNECTIONSTATE), 0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(N_DEVICEID), 0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(N_DEVICEID_VALID), 0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_PEERDEVICEID), 1, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_PEERCPORTID), 0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_TRAFFICCLASS), 0, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_CPORTFLAGS), 0x6, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_CPORTMODE), 1, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_CONNECTIONSTATE), 1, DME_LOCAL पूर्ण,
		अणु UIC_ARG_MIB(T_CONNECTIONSTATE), 0, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(N_DEVICEID), 1, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(N_DEVICEID_VALID), 1, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_PEERDEVICEID), 1, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_PEERCPORTID), 0, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_TRAFFICCLASS), 0, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_CPORTFLAGS), 0x6, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_CPORTMODE), 1, DME_PEER पूर्ण,
		अणु UIC_ARG_MIB(T_CONNECTIONSTATE), 1, DME_PEER पूर्ण
	पूर्ण;

	वापस ufshcd_dwc_dme_set_attrs(hba, setup_attrs, ARRAY_SIZE(setup_attrs));
पूर्ण

/**
 * ufshcd_dwc_link_startup_notअगरy()
 * UFS Host DWC specअगरic link startup sequence
 * @hba: निजी काष्ठाure poपूर्णांकer
 * @status: Callback notअगरy status
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_dwc_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	पूर्णांक err = 0;

	अगर (status == PRE_CHANGE) अणु
		ufshcd_dwc_program_clk_भाग(hba, DWC_UFS_REG_HCLKDIV_DIV_125);

		err = ufshcd_vops_phy_initialization(hba);
		अगर (err) अणु
			dev_err(hba->dev, "Phy setup failed (%d)\n", err);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु /* POST_CHANGE */
		err = ufshcd_dwc_link_is_up(hba);
		अगर (err) अणु
			dev_err(hba->dev, "Link is not up\n");
			जाओ out;
		पूर्ण

		err = ufshcd_dwc_connection_setup(hba);
		अगर (err)
			dev_err(hba->dev, "Connection setup failed (%d)\n",
									err);
	पूर्ण

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(ufshcd_dwc_link_startup_notअगरy);

MODULE_AUTHOR("Joao Pinto <Joao.Pinto@synopsys.com>");
MODULE_DESCRIPTION("UFS Host driver for Synopsys Designware Core");
MODULE_LICENSE("Dual BSD/GPL");
