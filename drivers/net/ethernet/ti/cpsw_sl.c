<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments Ethernet Switch media-access-controller (MAC) submodule/
 * Ethernet MAC Sliver (CPGMAC_SL)
 *
 * Copyright (C) 2019 Texas Instruments
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

#समावेश "cpsw_sl.h"

#घोषणा CPSW_SL_REG_NOTUSED U16_MAX

अटल स्थिर u16 cpsw_sl_reg_map_cpsw[] = अणु
	[CPSW_SL_IDVER] = 0x00,
	[CPSW_SL_MACCONTROL] = 0x04,
	[CPSW_SL_MACSTATUS] = 0x08,
	[CPSW_SL_SOFT_RESET] = 0x0c,
	[CPSW_SL_RX_MAXLEN] = 0x10,
	[CPSW_SL_BOFFTEST] = 0x14,
	[CPSW_SL_RX_PAUSE] = 0x18,
	[CPSW_SL_TX_PAUSE] = 0x1c,
	[CPSW_SL_EMCONTROL] = 0x20,
	[CPSW_SL_RX_PRI_MAP] = 0x24,
	[CPSW_SL_TX_GAP] = 0x28,
पूर्ण;

अटल स्थिर u16 cpsw_sl_reg_map_66ak2hk[] = अणु
	[CPSW_SL_IDVER] = 0x00,
	[CPSW_SL_MACCONTROL] = 0x04,
	[CPSW_SL_MACSTATUS] = 0x08,
	[CPSW_SL_SOFT_RESET] = 0x0c,
	[CPSW_SL_RX_MAXLEN] = 0x10,
	[CPSW_SL_BOFFTEST] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_RX_PAUSE] = 0x18,
	[CPSW_SL_TX_PAUSE] = 0x1c,
	[CPSW_SL_EMCONTROL] = 0x20,
	[CPSW_SL_RX_PRI_MAP] = 0x24,
	[CPSW_SL_TX_GAP] = CPSW_SL_REG_NOTUSED,
पूर्ण;

अटल स्थिर u16 cpsw_sl_reg_map_66ak2x_xgbe[] = अणु
	[CPSW_SL_IDVER] = 0x00,
	[CPSW_SL_MACCONTROL] = 0x04,
	[CPSW_SL_MACSTATUS] = 0x08,
	[CPSW_SL_SOFT_RESET] = 0x0c,
	[CPSW_SL_RX_MAXLEN] = 0x10,
	[CPSW_SL_BOFFTEST] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_RX_PAUSE] = 0x18,
	[CPSW_SL_TX_PAUSE] = 0x1c,
	[CPSW_SL_EMCONTROL] = 0x20,
	[CPSW_SL_RX_PRI_MAP] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_TX_GAP] = 0x28,
पूर्ण;

अटल स्थिर u16 cpsw_sl_reg_map_66ak2elg_am65[] = अणु
	[CPSW_SL_IDVER] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_MACCONTROL] = 0x00,
	[CPSW_SL_MACSTATUS] = 0x04,
	[CPSW_SL_SOFT_RESET] = 0x08,
	[CPSW_SL_RX_MAXLEN] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_BOFFTEST] = 0x0c,
	[CPSW_SL_RX_PAUSE] = 0x10,
	[CPSW_SL_TX_PAUSE] = 0x40,
	[CPSW_SL_EMCONTROL] = 0x70,
	[CPSW_SL_RX_PRI_MAP] = CPSW_SL_REG_NOTUSED,
	[CPSW_SL_TX_GAP] = 0x74,
पूर्ण;

#घोषणा CPSW_SL_SOFT_RESET_BIT		BIT(0)

#घोषणा CPSW_SL_STATUS_PN_IDLE		BIT(31)
#घोषणा CPSW_SL_AM65_STATUS_PN_E_IDLE	BIT(30)
#घोषणा CPSW_SL_AM65_STATUS_PN_P_IDLE	BIT(29)
#घोषणा CPSW_SL_AM65_STATUS_PN_TX_IDLE	BIT(28)

#घोषणा CPSW_SL_STATUS_IDLE_MASK_BASE (CPSW_SL_STATUS_PN_IDLE)

#घोषणा CPSW_SL_STATUS_IDLE_MASK_K3 \
	(CPSW_SL_STATUS_IDLE_MASK_BASE | CPSW_SL_AM65_STATUS_PN_E_IDLE | \
	 CPSW_SL_AM65_STATUS_PN_P_IDLE | CPSW_SL_AM65_STATUS_PN_TX_IDLE)

#घोषणा CPSW_SL_CTL_FUNC_BASE \
	(CPSW_SL_CTL_FULLDUPLEX |\
	CPSW_SL_CTL_LOOPBACK |\
	CPSW_SL_CTL_RX_FLOW_EN |\
	CPSW_SL_CTL_TX_FLOW_EN |\
	CPSW_SL_CTL_GMII_EN |\
	CPSW_SL_CTL_TX_PACE |\
	CPSW_SL_CTL_GIG |\
	CPSW_SL_CTL_CMD_IDLE |\
	CPSW_SL_CTL_IFCTL_A |\
	CPSW_SL_CTL_IFCTL_B |\
	CPSW_SL_CTL_GIG_FORCE |\
	CPSW_SL_CTL_EXT_EN |\
	CPSW_SL_CTL_RX_CEF_EN |\
	CPSW_SL_CTL_RX_CSF_EN |\
	CPSW_SL_CTL_RX_CMF_EN)

काष्ठा cpsw_sl अणु
	काष्ठा device *dev;
	व्योम __iomem *sl_base;
	स्थिर u16 *regs;
	u32 control_features;
	u32 idle_mask;
पूर्ण;

काष्ठा cpsw_sl_dev_id अणु
	स्थिर अक्षर *device_id;
	स्थिर u16 *regs;
	स्थिर u32 control_features;
	स्थिर u32 regs_offset;
	स्थिर u32 idle_mask;
पूर्ण;

अटल स्थिर काष्ठा cpsw_sl_dev_id cpsw_sl_id_match[] = अणु
	अणु
		.device_id = "cpsw",
		.regs = cpsw_sl_reg_map_cpsw,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_MTEST |
				    CPSW_SL_CTL_TX_SHORT_GAP_EN |
				    CPSW_SL_CTL_TX_SG_LIM_EN,
		.idle_mask = CPSW_SL_STATUS_IDLE_MASK_BASE,
	पूर्ण,
	अणु
		.device_id = "66ak2hk",
		.regs = cpsw_sl_reg_map_66ak2hk,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_TX_SHORT_GAP_EN,
		.idle_mask = CPSW_SL_STATUS_IDLE_MASK_BASE,
	पूर्ण,
	अणु
		.device_id = "66ak2x_xgbe",
		.regs = cpsw_sl_reg_map_66ak2x_xgbe,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_XGIG |
				    CPSW_SL_CTL_TX_SHORT_GAP_EN |
				    CPSW_SL_CTL_CRC_TYPE |
				    CPSW_SL_CTL_XGMII_EN,
		.idle_mask = CPSW_SL_STATUS_IDLE_MASK_BASE,
	पूर्ण,
	अणु
		.device_id = "66ak2el",
		.regs = cpsw_sl_reg_map_66ak2elg_am65,
		.regs_offset = 0x330,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_MTEST |
				    CPSW_SL_CTL_TX_SHORT_GAP_EN |
				    CPSW_SL_CTL_CRC_TYPE |
				    CPSW_SL_CTL_EXT_EN_RX_FLO |
				    CPSW_SL_CTL_EXT_EN_TX_FLO |
				    CPSW_SL_CTL_TX_SG_LIM_EN,
		.idle_mask = CPSW_SL_STATUS_IDLE_MASK_BASE,
	पूर्ण,
	अणु
		.device_id = "66ak2g",
		.regs = cpsw_sl_reg_map_66ak2elg_am65,
		.regs_offset = 0x330,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_MTEST |
				    CPSW_SL_CTL_CRC_TYPE |
				    CPSW_SL_CTL_EXT_EN_RX_FLO |
				    CPSW_SL_CTL_EXT_EN_TX_FLO,
	पूर्ण,
	अणु
		.device_id = "am65",
		.regs = cpsw_sl_reg_map_66ak2elg_am65,
		.regs_offset = 0x330,
		.control_features = CPSW_SL_CTL_FUNC_BASE |
				    CPSW_SL_CTL_MTEST |
				    CPSW_SL_CTL_XGIG |
				    CPSW_SL_CTL_TX_SHORT_GAP_EN |
				    CPSW_SL_CTL_CRC_TYPE |
				    CPSW_SL_CTL_XGMII_EN |
				    CPSW_SL_CTL_EXT_EN_RX_FLO |
				    CPSW_SL_CTL_EXT_EN_TX_FLO |
				    CPSW_SL_CTL_TX_SG_LIM_EN |
				    CPSW_SL_CTL_EXT_EN_XGIG,
		.idle_mask = CPSW_SL_STATUS_IDLE_MASK_K3,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

u32 cpsw_sl_reg_पढ़ो(काष्ठा cpsw_sl *sl, क्रमागत cpsw_sl_regs reg)
अणु
	पूर्णांक val;

	अगर (sl->regs[reg] == CPSW_SL_REG_NOTUSED) अणु
		dev_err(sl->dev, "cpsw_sl: not sup r reg: %04X\n",
			sl->regs[reg]);
		वापस 0;
	पूर्ण

	val = पढ़ोl(sl->sl_base + sl->regs[reg]);
	dev_dbg(sl->dev, "cpsw_sl: reg: %04X r 0x%08X\n", sl->regs[reg], val);
	वापस val;
पूर्ण

व्योम cpsw_sl_reg_ग_लिखो(काष्ठा cpsw_sl *sl, क्रमागत cpsw_sl_regs reg, u32 val)
अणु
	अगर (sl->regs[reg] == CPSW_SL_REG_NOTUSED) अणु
		dev_err(sl->dev, "cpsw_sl: not sup w reg: %04X\n",
			sl->regs[reg]);
		वापस;
	पूर्ण

	dev_dbg(sl->dev, "cpsw_sl: reg: %04X w 0x%08X\n", sl->regs[reg], val);
	ग_लिखोl(val, sl->sl_base + sl->regs[reg]);
पूर्ण

अटल स्थिर काष्ठा cpsw_sl_dev_id *cpsw_sl_match_id(
		स्थिर काष्ठा cpsw_sl_dev_id *id,
		स्थिर अक्षर *device_id)
अणु
	अगर (!id || !device_id)
		वापस शून्य;

	जबतक (id->device_id) अणु
		अगर (म_भेद(device_id, id->device_id) == 0)
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा cpsw_sl *cpsw_sl_get(स्थिर अक्षर *device_id, काष्ठा device *dev,
			    व्योम __iomem *sl_base)
अणु
	स्थिर काष्ठा cpsw_sl_dev_id *sl_dev_id;
	काष्ठा cpsw_sl *sl;

	sl = devm_kzalloc(dev, माप(काष्ठा cpsw_sl), GFP_KERNEL);
	अगर (!sl)
		वापस ERR_PTR(-ENOMEM);
	sl->dev = dev;
	sl->sl_base = sl_base;

	sl_dev_id = cpsw_sl_match_id(cpsw_sl_id_match, device_id);
	अगर (!sl_dev_id) अणु
		dev_err(sl->dev, "cpsw_sl: dev_id %s not found.\n", device_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	sl->regs = sl_dev_id->regs;
	sl->control_features = sl_dev_id->control_features;
	sl->idle_mask = sl_dev_id->idle_mask;
	sl->sl_base += sl_dev_id->regs_offset;

	वापस sl;
पूर्ण

व्योम cpsw_sl_reset(काष्ठा cpsw_sl *sl, अचिन्हित दीर्घ पंचांगo)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(पंचांगo);

	/* Set the soft reset bit */
	cpsw_sl_reg_ग_लिखो(sl, CPSW_SL_SOFT_RESET, CPSW_SL_SOFT_RESET_BIT);

	/* Wait क्रम the bit to clear */
	करो अणु
		usleep_range(100, 200);
	पूर्ण जबतक ((cpsw_sl_reg_पढ़ो(sl, CPSW_SL_SOFT_RESET) &
		  CPSW_SL_SOFT_RESET_BIT) &&
		  समय_after(समयout, jअगरfies));

	अगर (cpsw_sl_reg_पढ़ो(sl, CPSW_SL_SOFT_RESET) & CPSW_SL_SOFT_RESET_BIT)
		dev_err(sl->dev, "cpsw_sl failed to soft-reset.\n");
पूर्ण

u32 cpsw_sl_ctl_set(काष्ठा cpsw_sl *sl, u32 ctl_funcs)
अणु
	u32 val;

	अगर (ctl_funcs & ~sl->control_features) अणु
		dev_err(sl->dev, "cpsw_sl: unsupported func 0x%08X\n",
			ctl_funcs & (~sl->control_features));
		वापस -EINVAL;
	पूर्ण

	val = cpsw_sl_reg_पढ़ो(sl, CPSW_SL_MACCONTROL);
	val |= ctl_funcs;
	cpsw_sl_reg_ग_लिखो(sl, CPSW_SL_MACCONTROL, val);

	वापस 0;
पूर्ण

u32 cpsw_sl_ctl_clr(काष्ठा cpsw_sl *sl, u32 ctl_funcs)
अणु
	u32 val;

	अगर (ctl_funcs & ~sl->control_features) अणु
		dev_err(sl->dev, "cpsw_sl: unsupported func 0x%08X\n",
			ctl_funcs & (~sl->control_features));
		वापस -EINVAL;
	पूर्ण

	val = cpsw_sl_reg_पढ़ो(sl, CPSW_SL_MACCONTROL);
	val &= ~ctl_funcs;
	cpsw_sl_reg_ग_लिखो(sl, CPSW_SL_MACCONTROL, val);

	वापस 0;
पूर्ण

व्योम cpsw_sl_ctl_reset(काष्ठा cpsw_sl *sl)
अणु
	cpsw_sl_reg_ग_लिखो(sl, CPSW_SL_MACCONTROL, 0);
पूर्ण

पूर्णांक cpsw_sl_रुको_क्रम_idle(काष्ठा cpsw_sl *sl, अचिन्हित दीर्घ पंचांगo)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(पंचांगo);

	करो अणु
		usleep_range(100, 200);
	पूर्ण जबतक (!(cpsw_sl_reg_पढ़ो(sl, CPSW_SL_MACSTATUS) &
		  sl->idle_mask) && समय_after(समयout, jअगरfies));

	अगर (!(cpsw_sl_reg_पढ़ो(sl, CPSW_SL_MACSTATUS) & sl->idle_mask)) अणु
		dev_err(sl->dev, "cpsw_sl failed to soft-reset.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
