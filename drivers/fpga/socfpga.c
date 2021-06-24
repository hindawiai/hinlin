<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Manager Driver क्रम Altera SOCFPGA
 *
 *  Copyright (C) 2013-2015 Altera Corporation
 */
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm.h>

/* Register offsets */
#घोषणा SOCFPGA_FPGMGR_STAT_OFST				0x0
#घोषणा SOCFPGA_FPGMGR_CTL_OFST					0x4
#घोषणा SOCFPGA_FPGMGR_DCLKCNT_OFST				0x8
#घोषणा SOCFPGA_FPGMGR_DCLKSTAT_OFST				0xc
#घोषणा SOCFPGA_FPGMGR_GPIO_INTEN_OFST				0x830
#घोषणा SOCFPGA_FPGMGR_GPIO_INTMSK_OFST				0x834
#घोषणा SOCFPGA_FPGMGR_GPIO_INTTYPE_LEVEL_OFST			0x838
#घोषणा SOCFPGA_FPGMGR_GPIO_INT_POL_OFST			0x83c
#घोषणा SOCFPGA_FPGMGR_GPIO_INTSTAT_OFST			0x840
#घोषणा SOCFPGA_FPGMGR_GPIO_RAW_INTSTAT_OFST			0x844
#घोषणा SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST			0x84c
#घोषणा SOCFPGA_FPGMGR_GPIO_EXT_PORTA_OFST			0x850

/* Register bit defines */
/* SOCFPGA_FPGMGR_STAT रेजिस्टर mode field values */
#घोषणा SOCFPGA_FPGMGR_STAT_POWER_UP				0x0 /*ramping*/
#घोषणा SOCFPGA_FPGMGR_STAT_RESET				0x1
#घोषणा SOCFPGA_FPGMGR_STAT_CFG					0x2
#घोषणा SOCFPGA_FPGMGR_STAT_INIT				0x3
#घोषणा SOCFPGA_FPGMGR_STAT_USER_MODE				0x4
#घोषणा SOCFPGA_FPGMGR_STAT_UNKNOWN				0x5
#घोषणा SOCFPGA_FPGMGR_STAT_STATE_MASK				0x7
/* This is a flag value that करोesn't really happen in this रेजिस्टर field */
#घोषणा SOCFPGA_FPGMGR_STAT_POWER_OFF				0x0

#घोषणा MSEL_PP16_FAST_NOAES_NODC				0x0
#घोषणा MSEL_PP16_FAST_AES_NODC					0x1
#घोषणा MSEL_PP16_FAST_AESOPT_DC				0x2
#घोषणा MSEL_PP16_SLOW_NOAES_NODC				0x4
#घोषणा MSEL_PP16_SLOW_AES_NODC					0x5
#घोषणा MSEL_PP16_SLOW_AESOPT_DC				0x6
#घोषणा MSEL_PP32_FAST_NOAES_NODC				0x8
#घोषणा MSEL_PP32_FAST_AES_NODC					0x9
#घोषणा MSEL_PP32_FAST_AESOPT_DC				0xa
#घोषणा MSEL_PP32_SLOW_NOAES_NODC				0xc
#घोषणा MSEL_PP32_SLOW_AES_NODC					0xd
#घोषणा MSEL_PP32_SLOW_AESOPT_DC				0xe
#घोषणा SOCFPGA_FPGMGR_STAT_MSEL_MASK				0x000000f8
#घोषणा SOCFPGA_FPGMGR_STAT_MSEL_SHIFT				3

/* SOCFPGA_FPGMGR_CTL रेजिस्टर */
#घोषणा SOCFPGA_FPGMGR_CTL_EN					0x00000001
#घोषणा SOCFPGA_FPGMGR_CTL_NCE					0x00000002
#घोषणा SOCFPGA_FPGMGR_CTL_NCFGPULL				0x00000004

#घोषणा CDRATIO_X1						0x00000000
#घोषणा CDRATIO_X2						0x00000040
#घोषणा CDRATIO_X4						0x00000080
#घोषणा CDRATIO_X8						0x000000c0
#घोषणा SOCFPGA_FPGMGR_CTL_CDRATIO_MASK				0x000000c0

#घोषणा SOCFPGA_FPGMGR_CTL_AXICFGEN				0x00000100

#घोषणा CFGWDTH_16						0x00000000
#घोषणा CFGWDTH_32						0x00000200
#घोषणा SOCFPGA_FPGMGR_CTL_CFGWDTH_MASK				0x00000200

/* SOCFPGA_FPGMGR_DCLKSTAT रेजिस्टर */
#घोषणा SOCFPGA_FPGMGR_DCLKSTAT_DCNTDONE_E_DONE			0x1

/* SOCFPGA_FPGMGR_GPIO_* रेजिस्टरs share the same bit positions */
#घोषणा SOCFPGA_FPGMGR_MON_NSTATUS				0x0001
#घोषणा SOCFPGA_FPGMGR_MON_CONF_DONE				0x0002
#घोषणा SOCFPGA_FPGMGR_MON_INIT_DONE				0x0004
#घोषणा SOCFPGA_FPGMGR_MON_CRC_ERROR				0x0008
#घोषणा SOCFPGA_FPGMGR_MON_CVP_CONF_DONE			0x0010
#घोषणा SOCFPGA_FPGMGR_MON_PR_READY				0x0020
#घोषणा SOCFPGA_FPGMGR_MON_PR_ERROR				0x0040
#घोषणा SOCFPGA_FPGMGR_MON_PR_DONE				0x0080
#घोषणा SOCFPGA_FPGMGR_MON_NCONFIG_PIN				0x0100
#घोषणा SOCFPGA_FPGMGR_MON_NSTATUS_PIN				0x0200
#घोषणा SOCFPGA_FPGMGR_MON_CONF_DONE_PIN			0x0400
#घोषणा SOCFPGA_FPGMGR_MON_FPGA_POWER_ON			0x0800
#घोषणा SOCFPGA_FPGMGR_MON_STATUS_MASK				0x0fff

#घोषणा SOCFPGA_FPGMGR_NUM_SUPPLIES 3
#घोषणा SOCFPGA_RESUME_TIMEOUT 3

/* In घातer-up order. Reverse क्रम घातer-करोwn. */
अटल स्थिर अक्षर *supply_names[SOCFPGA_FPGMGR_NUM_SUPPLIES] __maybe_unused = अणु
	"FPGA-1.5V",
	"FPGA-1.1V",
	"FPGA-2.5V",
पूर्ण;

काष्ठा socfpga_fpga_priv अणु
	व्योम __iomem *fpga_base_addr;
	व्योम __iomem *fpga_data_addr;
	काष्ठा completion status_complete;
	पूर्णांक irq;
पूर्ण;

काष्ठा cfgmgr_mode अणु
	/* Values to set in the CTRL रेजिस्टर */
	u32 ctrl;

	/* flag that this table entry is a valid mode */
	bool valid;
पूर्ण;

/* For SOCFPGA_FPGMGR_STAT_MSEL field */
अटल काष्ठा cfgmgr_mode cfgmgr_modes[] = अणु
	[MSEL_PP16_FAST_NOAES_NODC] = अणु CFGWDTH_16 | CDRATIO_X1, 1 पूर्ण,
	[MSEL_PP16_FAST_AES_NODC] =   अणु CFGWDTH_16 | CDRATIO_X2, 1 पूर्ण,
	[MSEL_PP16_FAST_AESOPT_DC] =  अणु CFGWDTH_16 | CDRATIO_X4, 1 पूर्ण,
	[MSEL_PP16_SLOW_NOAES_NODC] = अणु CFGWDTH_16 | CDRATIO_X1, 1 पूर्ण,
	[MSEL_PP16_SLOW_AES_NODC] =   अणु CFGWDTH_16 | CDRATIO_X2, 1 पूर्ण,
	[MSEL_PP16_SLOW_AESOPT_DC] =  अणु CFGWDTH_16 | CDRATIO_X4, 1 पूर्ण,
	[MSEL_PP32_FAST_NOAES_NODC] = अणु CFGWDTH_32 | CDRATIO_X1, 1 पूर्ण,
	[MSEL_PP32_FAST_AES_NODC] =   अणु CFGWDTH_32 | CDRATIO_X4, 1 पूर्ण,
	[MSEL_PP32_FAST_AESOPT_DC] =  अणु CFGWDTH_32 | CDRATIO_X8, 1 पूर्ण,
	[MSEL_PP32_SLOW_NOAES_NODC] = अणु CFGWDTH_32 | CDRATIO_X1, 1 पूर्ण,
	[MSEL_PP32_SLOW_AES_NODC] =   अणु CFGWDTH_32 | CDRATIO_X4, 1 पूर्ण,
	[MSEL_PP32_SLOW_AESOPT_DC] =  अणु CFGWDTH_32 | CDRATIO_X8, 1 पूर्ण,
पूर्ण;

अटल u32 socfpga_fpga_पढ़ोl(काष्ठा socfpga_fpga_priv *priv, u32 reg_offset)
अणु
	वापस पढ़ोl(priv->fpga_base_addr + reg_offset);
पूर्ण

अटल व्योम socfpga_fpga_ग_लिखोl(काष्ठा socfpga_fpga_priv *priv, u32 reg_offset,
				u32 value)
अणु
	ग_लिखोl(value, priv->fpga_base_addr + reg_offset);
पूर्ण

अटल u32 socfpga_fpga_raw_पढ़ोl(काष्ठा socfpga_fpga_priv *priv,
				  u32 reg_offset)
अणु
	वापस __raw_पढ़ोl(priv->fpga_base_addr + reg_offset);
पूर्ण

अटल व्योम socfpga_fpga_raw_ग_लिखोl(काष्ठा socfpga_fpga_priv *priv,
				    u32 reg_offset, u32 value)
अणु
	__raw_ग_लिखोl(value, priv->fpga_base_addr + reg_offset);
पूर्ण

अटल व्योम socfpga_fpga_data_ग_लिखोl(काष्ठा socfpga_fpga_priv *priv, u32 value)
अणु
	ग_लिखोl(value, priv->fpga_data_addr);
पूर्ण

अटल अंतरभूत व्योम socfpga_fpga_set_bitsl(काष्ठा socfpga_fpga_priv *priv,
					  u32 offset, u32 bits)
अणु
	u32 val;

	val = socfpga_fpga_पढ़ोl(priv, offset);
	val |= bits;
	socfpga_fpga_ग_लिखोl(priv, offset, val);
पूर्ण

अटल अंतरभूत व्योम socfpga_fpga_clr_bitsl(काष्ठा socfpga_fpga_priv *priv,
					  u32 offset, u32 bits)
अणु
	u32 val;

	val = socfpga_fpga_पढ़ोl(priv, offset);
	val &= ~bits;
	socfpga_fpga_ग_लिखोl(priv, offset, val);
पूर्ण

अटल u32 socfpga_fpga_mon_status_get(काष्ठा socfpga_fpga_priv *priv)
अणु
	वापस socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_GPIO_EXT_PORTA_OFST) &
		SOCFPGA_FPGMGR_MON_STATUS_MASK;
पूर्ण

अटल u32 socfpga_fpga_state_get(काष्ठा socfpga_fpga_priv *priv)
अणु
	u32 status = socfpga_fpga_mon_status_get(priv);

	अगर ((status & SOCFPGA_FPGMGR_MON_FPGA_POWER_ON) == 0)
		वापस SOCFPGA_FPGMGR_STAT_POWER_OFF;

	वापस socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_STAT_OFST) &
		SOCFPGA_FPGMGR_STAT_STATE_MASK;
पूर्ण

अटल व्योम socfpga_fpga_clear_करोne_status(काष्ठा socfpga_fpga_priv *priv)
अणु
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_DCLKSTAT_OFST,
			    SOCFPGA_FPGMGR_DCLKSTAT_DCNTDONE_E_DONE);
पूर्ण

/*
 * Set the DCLKCNT, रुको क्रम DCLKSTAT to report the count completed, and clear
 * the complete status.
 */
अटल पूर्णांक socfpga_fpga_dclk_set_and_रुको_clear(काष्ठा socfpga_fpga_priv *priv,
						u32 count)
अणु
	पूर्णांक समयout = 2;
	u32 करोne;

	/* Clear any existing DONE status. */
	अगर (socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_DCLKSTAT_OFST))
		socfpga_fpga_clear_करोne_status(priv);

	/* Issue the DCLK count. */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_DCLKCNT_OFST, count);

	/* Poll DCLKSTAT to see अगर it completed in the समयout period. */
	करो अणु
		करोne = socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_DCLKSTAT_OFST);
		अगर (करोne == SOCFPGA_FPGMGR_DCLKSTAT_DCNTDONE_E_DONE) अणु
			socfpga_fpga_clear_करोne_status(priv);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक socfpga_fpga_रुको_क्रम_state(काष्ठा socfpga_fpga_priv *priv,
				       u32 state)
अणु
	पूर्णांक समयout = 2;

	/*
	 * HW करोesn't support an पूर्णांकerrupt क्रम changes in state, so poll to see
	 * अगर it matches the requested state within the समयout period.
	 */
	करो अणु
		अगर ((socfpga_fpga_state_get(priv) & state) != 0)
			वापस 0;
		msleep(20);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम socfpga_fpga_enable_irqs(काष्ठा socfpga_fpga_priv *priv, u32 irqs)
अणु
	/* set irqs to level sensitive */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_INTTYPE_LEVEL_OFST, 0);

	/* set पूर्णांकerrupt polarity */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_INT_POL_OFST, irqs);

	/* clear irqs */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST, irqs);

	/* unmask पूर्णांकerrupts */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_INTMSK_OFST, 0);

	/* enable पूर्णांकerrupts */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_INTEN_OFST, irqs);
पूर्ण

अटल व्योम socfpga_fpga_disable_irqs(काष्ठा socfpga_fpga_priv *priv)
अणु
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_INTEN_OFST, 0);
पूर्ण

अटल irqवापस_t socfpga_fpga_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा socfpga_fpga_priv *priv = dev_id;
	u32 irqs, st;
	bool conf_करोne, nstatus;

	/* clear irqs */
	irqs = socfpga_fpga_raw_पढ़ोl(priv, SOCFPGA_FPGMGR_GPIO_INTSTAT_OFST);

	socfpga_fpga_raw_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST, irqs);

	st = socfpga_fpga_raw_पढ़ोl(priv, SOCFPGA_FPGMGR_GPIO_EXT_PORTA_OFST);
	conf_करोne = (st & SOCFPGA_FPGMGR_MON_CONF_DONE) != 0;
	nstatus = (st & SOCFPGA_FPGMGR_MON_NSTATUS) != 0;

	/* success */
	अगर (conf_करोne && nstatus) अणु
		/* disable irqs */
		socfpga_fpga_raw_ग_लिखोl(priv,
					SOCFPGA_FPGMGR_GPIO_INTEN_OFST, 0);
		complete(&priv->status_complete);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक socfpga_fpga_रुको_क्रम_config_करोne(काष्ठा socfpga_fpga_priv *priv)
अणु
	पूर्णांक समयout, ret = 0;

	socfpga_fpga_disable_irqs(priv);
	init_completion(&priv->status_complete);
	socfpga_fpga_enable_irqs(priv, SOCFPGA_FPGMGR_MON_CONF_DONE);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
						&priv->status_complete,
						msecs_to_jअगरfies(10));
	अगर (समयout == 0)
		ret = -ETIMEDOUT;

	socfpga_fpga_disable_irqs(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक socfpga_fpga_cfg_mode_get(काष्ठा socfpga_fpga_priv *priv)
अणु
	u32 msel;

	msel = socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_STAT_OFST);
	msel &= SOCFPGA_FPGMGR_STAT_MSEL_MASK;
	msel >>= SOCFPGA_FPGMGR_STAT_MSEL_SHIFT;

	/* Check that this MSEL setting is supported */
	अगर ((msel >= ARRAY_SIZE(cfgmgr_modes)) || !cfgmgr_modes[msel].valid)
		वापस -EINVAL;

	वापस msel;
पूर्ण

अटल पूर्णांक socfpga_fpga_cfg_mode_set(काष्ठा socfpga_fpga_priv *priv)
अणु
	u32 ctrl_reg;
	पूर्णांक mode;

	/* get value from MSEL pins */
	mode = socfpga_fpga_cfg_mode_get(priv);
	अगर (mode < 0)
		वापस mode;

	/* Adjust CTRL क्रम the CDRATIO */
	ctrl_reg = socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_CTL_OFST);
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_CDRATIO_MASK;
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_CFGWDTH_MASK;
	ctrl_reg |= cfgmgr_modes[mode].ctrl;

	/* Set NCE to 0. */
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_NCE;
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_fpga_reset(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा socfpga_fpga_priv *priv = mgr->priv;
	u32 ctrl_reg, status;
	पूर्णांक ret;

	/*
	 * Step 1:
	 *  - Set CTRL.CFGWDTH, CTRL.CDRATIO to match cfg mode
	 *  - Set CTRL.NCE to 0
	 */
	ret = socfpga_fpga_cfg_mode_set(priv);
	अगर (ret)
		वापस ret;

	/* Step 2: Set CTRL.EN to 1 */
	socfpga_fpga_set_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_EN);

	/* Step 3: Set CTRL.NCONFIGPULL to 1 to put FPGA in reset */
	ctrl_reg = socfpga_fpga_पढ़ोl(priv, SOCFPGA_FPGMGR_CTL_OFST);
	ctrl_reg |= SOCFPGA_FPGMGR_CTL_NCFGPULL;
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	/* Step 4: Wait क्रम STATUS.MODE to report FPGA is in reset phase */
	status = socfpga_fpga_रुको_क्रम_state(priv, SOCFPGA_FPGMGR_STAT_RESET);

	/* Step 5: Set CONTROL.NCONFIGPULL to 0 to release FPGA from reset */
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_NCFGPULL;
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	/* Timeout रुकोing क्रम reset */
	अगर (status)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/*
 * Prepare the FPGA to receive the configuration data.
 */
अटल पूर्णांक socfpga_fpga_ops_configure_init(काष्ठा fpga_manager *mgr,
					   काष्ठा fpga_image_info *info,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा socfpga_fpga_priv *priv = mgr->priv;
	पूर्णांक ret;

	अगर (info->flags & FPGA_MGR_PARTIAL_RECONFIG) अणु
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		वापस -EINVAL;
	पूर्ण
	/* Steps 1 - 5: Reset the FPGA */
	ret = socfpga_fpga_reset(mgr);
	अगर (ret)
		वापस ret;

	/* Step 6: Wait क्रम FPGA to enter configuration phase */
	अगर (socfpga_fpga_रुको_क्रम_state(priv, SOCFPGA_FPGMGR_STAT_CFG))
		वापस -ETIMEDOUT;

	/* Step 7: Clear nSTATUS पूर्णांकerrupt */
	socfpga_fpga_ग_लिखोl(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST,
			    SOCFPGA_FPGMGR_MON_NSTATUS);

	/* Step 8: Set CTRL.AXICFGEN to 1 to enable transfer of config data */
	socfpga_fpga_set_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_AXICFGEN);

	वापस 0;
पूर्ण

/*
 * Step 9: ग_लिखो data to the FPGA data रेजिस्टर
 */
अटल पूर्णांक socfpga_fpga_ops_configure_ग_लिखो(काष्ठा fpga_manager *mgr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा socfpga_fpga_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	माप_प्रकार i = 0;

	अगर (count <= 0)
		वापस -EINVAL;

	/* Write out the complete 32-bit chunks. */
	जबतक (count >= माप(u32)) अणु
		socfpga_fpga_data_ग_लिखोl(priv, buffer_32[i++]);
		count -= माप(u32);
	पूर्ण

	/* Write out reमुख्यing non 32-bit chunks. */
	चयन (count) अणु
	हाल 3:
		socfpga_fpga_data_ग_लिखोl(priv, buffer_32[i++] & 0x00ffffff);
		अवरोध;
	हाल 2:
		socfpga_fpga_data_ग_लिखोl(priv, buffer_32[i++] & 0x0000ffff);
		अवरोध;
	हाल 1:
		socfpga_fpga_data_ग_लिखोl(priv, buffer_32[i++] & 0x000000ff);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		/* This will never happen. */
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_fpga_ops_configure_complete(काष्ठा fpga_manager *mgr,
					       काष्ठा fpga_image_info *info)
अणु
	काष्ठा socfpga_fpga_priv *priv = mgr->priv;
	u32 status;

	/*
	 * Step 10:
	 *  - Observe CONF_DONE and nSTATUS (active low)
	 *  - अगर CONF_DONE = 1 and nSTATUS = 1, configuration was successful
	 *  - अगर CONF_DONE = 0 and nSTATUS = 0, configuration failed
	 */
	status = socfpga_fpga_रुको_क्रम_config_करोne(priv);
	अगर (status)
		वापस status;

	/* Step 11: Clear CTRL.AXICFGEN to disable transfer of config data */
	socfpga_fpga_clr_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_AXICFGEN);

	/*
	 * Step 12:
	 *  - Write 4 to DCLKCNT
	 *  - Wait क्रम STATUS.DCNTDONE = 1
	 *  - Clear W1C bit in STATUS.DCNTDONE
	 */
	अगर (socfpga_fpga_dclk_set_and_रुको_clear(priv, 4))
		वापस -ETIMEDOUT;

	/* Step 13: Wait क्रम STATUS.MODE to report USER MODE */
	अगर (socfpga_fpga_रुको_क्रम_state(priv, SOCFPGA_FPGMGR_STAT_USER_MODE))
		वापस -ETIMEDOUT;

	/* Step 14: Set CTRL.EN to 0 */
	socfpga_fpga_clr_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_EN);

	वापस 0;
पूर्ण

/* Translate state रेजिस्टर values to FPGA framework state */
अटल स्थिर क्रमागत fpga_mgr_states socfpga_state_to_framework_state[] = अणु
	[SOCFPGA_FPGMGR_STAT_POWER_OFF] = FPGA_MGR_STATE_POWER_OFF,
	[SOCFPGA_FPGMGR_STAT_RESET] = FPGA_MGR_STATE_RESET,
	[SOCFPGA_FPGMGR_STAT_CFG] = FPGA_MGR_STATE_WRITE_INIT,
	[SOCFPGA_FPGMGR_STAT_INIT] = FPGA_MGR_STATE_WRITE_INIT,
	[SOCFPGA_FPGMGR_STAT_USER_MODE] = FPGA_MGR_STATE_OPERATING,
	[SOCFPGA_FPGMGR_STAT_UNKNOWN] = FPGA_MGR_STATE_UNKNOWN,
पूर्ण;

अटल क्रमागत fpga_mgr_states socfpga_fpga_ops_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा socfpga_fpga_priv *priv = mgr->priv;
	क्रमागत fpga_mgr_states ret;
	u32 state;

	state = socfpga_fpga_state_get(priv);

	अगर (state < ARRAY_SIZE(socfpga_state_to_framework_state))
		ret = socfpga_state_to_framework_state[state];
	अन्यथा
		ret = FPGA_MGR_STATE_UNKNOWN;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops socfpga_fpga_ops = अणु
	.state = socfpga_fpga_ops_state,
	.ग_लिखो_init = socfpga_fpga_ops_configure_init,
	.ग_लिखो = socfpga_fpga_ops_configure_ग_लिखो,
	.ग_लिखो_complete = socfpga_fpga_ops_configure_complete,
पूर्ण;

अटल पूर्णांक socfpga_fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा socfpga_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->fpga_base_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->fpga_base_addr))
		वापस PTR_ERR(priv->fpga_base_addr);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->fpga_data_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->fpga_data_addr))
		वापस PTR_ERR(priv->fpga_data_addr);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	ret = devm_request_irq(dev, priv->irq, socfpga_fpga_isr, 0,
			       dev_name(dev), priv);
	अगर (ret)
		वापस ret;

	mgr = devm_fpga_mgr_create(dev, "Altera SOCFPGA FPGA Manager",
				   &socfpga_fpga_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id socfpga_fpga_of_match[] = अणु
	अणु .compatible = "altr,socfpga-fpga-mgr", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, socfpga_fpga_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver socfpga_fpga_driver = अणु
	.probe = socfpga_fpga_probe,
	.driver = अणु
		.name	= "socfpga_fpga_manager",
		.of_match_table = of_match_ptr(socfpga_fpga_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(socfpga_fpga_driver);

MODULE_AUTHOR("Alan Tull <atull@opensource.altera.com>");
MODULE_DESCRIPTION("Altera SOCFPGA FPGA Manager");
MODULE_LICENSE("GPL v2");
