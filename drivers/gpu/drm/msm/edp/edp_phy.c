<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश "edp.h"
#समावेश "edp.xml.h"

#घोषणा EDP_MAX_LANE	4

काष्ठा edp_phy अणु
	व्योम __iomem *base;
पूर्ण;

bool msm_edp_phy_पढ़ोy(काष्ठा edp_phy *phy)
अणु
	u32 status;
	पूर्णांक cnt = 100;

	जबतक (--cnt) अणु
		status = edp_पढ़ो(phy->base +
				REG_EDP_PHY_GLB_PHY_STATUS);
		अगर (status & 0x01)
			अवरोध;
		usleep_range(500, 1000);
	पूर्ण

	अगर (cnt == 0) अणु
		pr_err("%s: PHY NOT ready\n", __func__);
		वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण
पूर्ण

व्योम msm_edp_phy_ctrl(काष्ठा edp_phy *phy, पूर्णांक enable)
अणु
	DBG("enable=%d", enable);
	अगर (enable) अणु
		/* Reset */
		edp_ग_लिखो(phy->base + REG_EDP_PHY_CTRL,
			EDP_PHY_CTRL_SW_RESET | EDP_PHY_CTRL_SW_RESET_PLL);
		/* Make sure fully reset */
		wmb();
		usleep_range(500, 1000);
		edp_ग_लिखो(phy->base + REG_EDP_PHY_CTRL, 0x000);
		edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_PD_CTL, 0x3f);
		edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_CFG, 0x1);
	पूर्ण अन्यथा अणु
		edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_PD_CTL, 0xc0);
	पूर्ण
पूर्ण

/* voltage mode and pre emphasis cfg */
व्योम msm_edp_phy_vm_pe_init(काष्ठा edp_phy *phy)
अणु
	edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_VM_CFG0, 0x3);
	edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_VM_CFG1, 0x64);
	edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_MISC9, 0x6c);
पूर्ण

व्योम msm_edp_phy_vm_pe_cfg(काष्ठा edp_phy *phy, u32 v0, u32 v1)
अणु
	edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_VM_CFG0, v0);
	edp_ग_लिखो(phy->base + REG_EDP_PHY_GLB_VM_CFG1, v1);
पूर्ण

व्योम msm_edp_phy_lane_घातer_ctrl(काष्ठा edp_phy *phy, bool up, u32 max_lane)
अणु
	u32 i;
	u32 data;

	अगर (up)
		data = 0;	/* घातer up */
	अन्यथा
		data = 0x7;	/* घातer करोwn */

	क्रम (i = 0; i < max_lane; i++)
		edp_ग_लिखो(phy->base + REG_EDP_PHY_LN_PD_CTL(i) , data);

	/* घातer करोwn unused lane */
	data = 0x7;	/* घातer करोwn */
	क्रम (i = max_lane; i < EDP_MAX_LANE; i++)
		edp_ग_लिखो(phy->base + REG_EDP_PHY_LN_PD_CTL(i) , data);
पूर्ण

व्योम *msm_edp_phy_init(काष्ठा device *dev, व्योम __iomem *regbase)
अणु
	काष्ठा edp_phy *phy = शून्य;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस शून्य;

	phy->base = regbase;
	वापस phy;
पूर्ण

