<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FPGA Manager Driver क्रम Altera Arria/Cyclone/Stratix CvP
 *
 * Copyright (C) 2017 DENX Software Engineering
 *
 * Anम_से_दij Gustschin <agust@denx.de>
 *
 * Manage Altera FPGA firmware using PCIe CvP.
 * Firmware must be in binary "rbf" क्रमmat.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sizes.h>

#घोषणा CVP_BAR		0	/* BAR used क्रम data transfer in memory mode */
#घोषणा CVP_DUMMY_WR	244	/* dummy ग_लिखोs to clear CvP state machine */
#घोषणा TIMEOUT_US	2000	/* CVP STATUS समयout क्रम USERMODE polling */

/* Venकरोr Specअगरic Extended Capability Registers */
#घोषणा VSE_PCIE_EXT_CAP_ID		0x0
#घोषणा VSE_PCIE_EXT_CAP_ID_VAL		0x000b	/* 16bit */

#घोषणा VSE_CVP_STATUS			0x1c	/* 32bit */
#घोषणा VSE_CVP_STATUS_CFG_RDY		BIT(18)	/* CVP_CONFIG_READY */
#घोषणा VSE_CVP_STATUS_CFG_ERR		BIT(19)	/* CVP_CONFIG_ERROR */
#घोषणा VSE_CVP_STATUS_CVP_EN		BIT(20)	/* ctrl block is enabling CVP */
#घोषणा VSE_CVP_STATUS_USERMODE		BIT(21)	/* USERMODE */
#घोषणा VSE_CVP_STATUS_CFG_DONE		BIT(23)	/* CVP_CONFIG_DONE */
#घोषणा VSE_CVP_STATUS_PLD_CLK_IN_USE	BIT(24)	/* PLD_CLK_IN_USE */

#घोषणा VSE_CVP_MODE_CTRL		0x20	/* 32bit */
#घोषणा VSE_CVP_MODE_CTRL_CVP_MODE	BIT(0)	/* CVP (1) or normal mode (0) */
#घोषणा VSE_CVP_MODE_CTRL_HIP_CLK_SEL	BIT(1) /* PMA (1) or fabric घड़ी (0) */
#घोषणा VSE_CVP_MODE_CTRL_NUMCLKS_OFF	8	/* NUMCLKS bits offset */
#घोषणा VSE_CVP_MODE_CTRL_NUMCLKS_MASK	GENMASK(15, 8)

#घोषणा VSE_CVP_DATA			0x28	/* 32bit */
#घोषणा VSE_CVP_PROG_CTRL		0x2c	/* 32bit */
#घोषणा VSE_CVP_PROG_CTRL_CONFIG	BIT(0)
#घोषणा VSE_CVP_PROG_CTRL_START_XFER	BIT(1)
#घोषणा VSE_CVP_PROG_CTRL_MASK		GENMASK(1, 0)

#घोषणा VSE_UNCOR_ERR_STATUS		0x34	/* 32bit */
#घोषणा VSE_UNCOR_ERR_CVP_CFG_ERR	BIT(5)	/* CVP_CONFIG_ERROR_LATCHED */

#घोषणा V1_VSEC_OFFSET			0x200	/* Venकरोr Specअगरic Offset V1 */
/* V2 Defines */
#घोषणा VSE_CVP_TX_CREDITS		0x49	/* 8bit */

#घोषणा V2_CREDIT_TIMEOUT_US		20000
#घोषणा V2_CHECK_CREDIT_US		10
#घोषणा V2_POLL_TIMEOUT_US		1000000
#घोषणा V2_USER_TIMEOUT_US		500000

#घोषणा V1_POLL_TIMEOUT_US		10

#घोषणा DRV_NAME		"altera-cvp"
#घोषणा ALTERA_CVP_MGR_NAME	"Altera CvP FPGA Manager"

/* Write block sizes */
#घोषणा ALTERA_CVP_V1_SIZE	4
#घोषणा ALTERA_CVP_V2_SIZE	4096

/* Optional CvP config error status check क्रम debugging */
अटल bool altera_cvp_chkcfg;

काष्ठा cvp_priv;

काष्ठा altera_cvp_conf अणु
	काष्ठा fpga_manager	*mgr;
	काष्ठा pci_dev		*pci_dev;
	व्योम __iomem		*map;
	व्योम			(*ग_लिखो_data)(काष्ठा altera_cvp_conf *conf,
					      u32 data);
	अक्षर			mgr_name[64];
	u8			numclks;
	u32			sent_packets;
	u32			vsec_offset;
	स्थिर काष्ठा cvp_priv	*priv;
पूर्ण;

काष्ठा cvp_priv अणु
	व्योम	(*चयन_clk)(काष्ठा altera_cvp_conf *conf);
	पूर्णांक	(*clear_state)(काष्ठा altera_cvp_conf *conf);
	पूर्णांक	(*रुको_credit)(काष्ठा fpga_manager *mgr, u32 blocks);
	माप_प्रकार	block_size;
	पूर्णांक	poll_समय_us;
	पूर्णांक	user_समय_us;
पूर्ण;

अटल पूर्णांक altera_पढ़ो_config_byte(काष्ठा altera_cvp_conf *conf,
				   पूर्णांक where, u8 *val)
अणु
	वापस pci_पढ़ो_config_byte(conf->pci_dev, conf->vsec_offset + where,
				    val);
पूर्ण

अटल पूर्णांक altera_पढ़ो_config_dword(काष्ठा altera_cvp_conf *conf,
				    पूर्णांक where, u32 *val)
अणु
	वापस pci_पढ़ो_config_dword(conf->pci_dev, conf->vsec_offset + where,
				     val);
पूर्ण

अटल पूर्णांक altera_ग_लिखो_config_dword(काष्ठा altera_cvp_conf *conf,
				     पूर्णांक where, u32 val)
अणु
	वापस pci_ग_लिखो_config_dword(conf->pci_dev, conf->vsec_offset + where,
				      val);
पूर्ण

अटल क्रमागत fpga_mgr_states altera_cvp_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	u32 status;

	altera_पढ़ो_config_dword(conf, VSE_CVP_STATUS, &status);

	अगर (status & VSE_CVP_STATUS_CFG_DONE)
		वापस FPGA_MGR_STATE_OPERATING;

	अगर (status & VSE_CVP_STATUS_CVP_EN)
		वापस FPGA_MGR_STATE_POWER_UP;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल व्योम altera_cvp_ग_लिखो_data_iomem(काष्ठा altera_cvp_conf *conf, u32 val)
अणु
	ग_लिखोl(val, conf->map);
पूर्ण

अटल व्योम altera_cvp_ग_लिखो_data_config(काष्ठा altera_cvp_conf *conf, u32 val)
अणु
	pci_ग_लिखो_config_dword(conf->pci_dev, conf->vsec_offset + VSE_CVP_DATA,
			       val);
पूर्ण

/* चयनes between CvP घड़ी and पूर्णांकernal घड़ी */
अटल व्योम altera_cvp_dummy_ग_लिखो(काष्ठा altera_cvp_conf *conf)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	/* set 1 CVP घड़ी cycle क्रम every CVP Data Register Write */
	altera_पढ़ो_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_NUMCLKS_MASK;
	val |= 1 << VSE_CVP_MODE_CTRL_NUMCLKS_OFF;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	क्रम (i = 0; i < CVP_DUMMY_WR; i++)
		conf->ग_लिखो_data(conf, 0); /* dummy data, could be any value */
पूर्ण

अटल पूर्णांक altera_cvp_रुको_status(काष्ठा altera_cvp_conf *conf, u32 status_mask,
				  u32 status_val, पूर्णांक समयout_us)
अणु
	अचिन्हित पूर्णांक retries;
	u32 val;

	retries = समयout_us / 10;
	अगर (समयout_us % 10)
		retries++;

	करो अणु
		altera_पढ़ो_config_dword(conf, VSE_CVP_STATUS, &val);
		अगर ((val & status_mask) == status_val)
			वापस 0;

		/* use small usleep value to re-check and अवरोध early */
		usleep_range(10, 11);
	पूर्ण जबतक (--retries);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक altera_cvp_chk_error(काष्ठा fpga_manager *mgr, माप_प्रकार bytes)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	u32 val;
	पूर्णांक ret;

	/* STEP 10 (optional) - check CVP_CONFIG_ERROR flag */
	ret = altera_पढ़ो_config_dword(conf, VSE_CVP_STATUS, &val);
	अगर (ret || (val & VSE_CVP_STATUS_CFG_ERR)) अणु
		dev_err(&mgr->dev, "CVP_CONFIG_ERROR after %zu bytes!\n",
			bytes);
		वापस -EPROTO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * CvP Version2 Functions
 * Recent Intel FPGAs use a credit mechanism to throttle incoming
 * bitstreams and a dअगरferent method of clearing the state.
 */

अटल पूर्णांक altera_cvp_v2_clear_state(काष्ठा altera_cvp_conf *conf)
अणु
	u32 val;
	पूर्णांक ret;

	/* Clear the START_XFER and CVP_CONFIG bits */
	ret = altera_पढ़ो_config_dword(conf, VSE_CVP_PROG_CTRL, &val);
	अगर (ret) अणु
		dev_err(&conf->pci_dev->dev,
			"Error reading CVP Program Control Register\n");
		वापस ret;
	पूर्ण

	val &= ~VSE_CVP_PROG_CTRL_MASK;
	ret = altera_ग_लिखो_config_dword(conf, VSE_CVP_PROG_CTRL, val);
	अगर (ret) अणु
		dev_err(&conf->pci_dev->dev,
			"Error writing CVP Program Control Register\n");
		वापस ret;
	पूर्ण

	वापस altera_cvp_रुको_status(conf, VSE_CVP_STATUS_CFG_RDY, 0,
				      conf->priv->poll_समय_us);
पूर्ण

अटल पूर्णांक altera_cvp_v2_रुको_क्रम_credit(काष्ठा fpga_manager *mgr,
					 u32 blocks)
अणु
	u32 समयout = V2_CREDIT_TIMEOUT_US / V2_CHECK_CREDIT_US;
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	पूर्णांक ret;
	u8 val;

	करो अणु
		ret = altera_पढ़ो_config_byte(conf, VSE_CVP_TX_CREDITS, &val);
		अगर (ret) अणु
			dev_err(&conf->pci_dev->dev,
				"Error reading CVP Credit Register\n");
			वापस ret;
		पूर्ण

		/* Return अगर there is space in FIFO */
		अगर (val - (u8)conf->sent_packets)
			वापस 0;

		ret = altera_cvp_chk_error(mgr, blocks * ALTERA_CVP_V2_SIZE);
		अगर (ret) अणु
			dev_err(&conf->pci_dev->dev,
				"CE Bit error credit reg[0x%x]:sent[0x%x]\n",
				val, conf->sent_packets);
			वापस -EAGAIN;
		पूर्ण

		/* Limit the check credit byte traffic */
		usleep_range(V2_CHECK_CREDIT_US, V2_CHECK_CREDIT_US + 1);
	पूर्ण जबतक (समयout--);

	dev_err(&conf->pci_dev->dev, "Timeout waiting for credit\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक altera_cvp_send_block(काष्ठा altera_cvp_conf *conf,
				 स्थिर u32 *data, माप_प्रकार len)
अणु
	u32 mask, words = len / माप(u32);
	पूर्णांक i, reमुख्यder;

	क्रम (i = 0; i < words; i++)
		conf->ग_लिखो_data(conf, *data++);

	/* ग_लिखो up to 3 trailing bytes, अगर any */
	reमुख्यder = len % माप(u32);
	अगर (reमुख्यder) अणु
		mask = BIT(reमुख्यder * 8) - 1;
		अगर (mask)
			conf->ग_लिखो_data(conf, *data & mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक altera_cvp_tearकरोwn(काष्ठा fpga_manager *mgr,
			       काष्ठा fpga_image_info *info)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	पूर्णांक ret;
	u32 val;

	/* STEP 12 - reset START_XFER bit */
	altera_पढ़ो_config_dword(conf, VSE_CVP_PROG_CTRL, &val);
	val &= ~VSE_CVP_PROG_CTRL_START_XFER;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/* STEP 13 - reset CVP_CONFIG bit */
	val &= ~VSE_CVP_PROG_CTRL_CONFIG;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/*
	 * STEP 14
	 * - set CVP_NUMCLKS to 1 and then issue CVP_DUMMY_WR dummy
	 *   ग_लिखोs to the HIP
	 */
	अगर (conf->priv->चयन_clk)
		conf->priv->चयन_clk(conf);

	/* STEP 15 - poll CVP_CONFIG_READY bit क्रम 0 with 10us समयout */
	ret = altera_cvp_रुको_status(conf, VSE_CVP_STATUS_CFG_RDY, 0,
				     conf->priv->poll_समय_us);
	अगर (ret)
		dev_err(&mgr->dev, "CFG_RDY == 0 timeout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक altera_cvp_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				 काष्ठा fpga_image_info *info,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	u32 अगरlags, val;
	पूर्णांक ret;

	अगरlags = info ? info->flags : 0;

	अगर (अगरlags & FPGA_MGR_PARTIAL_RECONFIG) अणु
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		वापस -EINVAL;
	पूर्ण

	/* Determine allowed घड़ी to data ratio */
	अगर (अगरlags & FPGA_MGR_COMPRESSED_BITSTREAM)
		conf->numclks = 8; /* ratio क्रम all compressed images */
	अन्यथा अगर (अगरlags & FPGA_MGR_ENCRYPTED_BITSTREAM)
		conf->numclks = 4; /* क्रम uncompressed and encrypted images */
	अन्यथा
		conf->numclks = 1; /* क्रम uncompressed and unencrypted images */

	/* STEP 1 - पढ़ो CVP status and check CVP_EN flag */
	altera_पढ़ो_config_dword(conf, VSE_CVP_STATUS, &val);
	अगर (!(val & VSE_CVP_STATUS_CVP_EN)) अणु
		dev_err(&mgr->dev, "CVP mode off: 0x%04x\n", val);
		वापस -ENODEV;
	पूर्ण

	अगर (val & VSE_CVP_STATUS_CFG_RDY) अणु
		dev_warn(&mgr->dev, "CvP already started, teardown first\n");
		ret = altera_cvp_tearकरोwn(mgr, info);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * STEP 2
	 * - set HIP_CLK_SEL and CVP_MODE (must be set in the order mentioned)
	 */
	/* चयन from fabric to PMA घड़ी */
	altera_पढ़ो_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val |= VSE_CVP_MODE_CTRL_HIP_CLK_SEL;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	/* set CVP mode */
	altera_पढ़ो_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val |= VSE_CVP_MODE_CTRL_CVP_MODE;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	/*
	 * STEP 3
	 * - set CVP_NUMCLKS to 1 and issue CVP_DUMMY_WR dummy ग_लिखोs to the HIP
	 */
	अगर (conf->priv->चयन_clk)
		conf->priv->चयन_clk(conf);

	अगर (conf->priv->clear_state) अणु
		ret = conf->priv->clear_state(conf);
		अगर (ret) अणु
			dev_err(&mgr->dev, "Problem clearing out state\n");
			वापस ret;
		पूर्ण
	पूर्ण

	conf->sent_packets = 0;

	/* STEP 4 - set CVP_CONFIG bit */
	altera_पढ़ो_config_dword(conf, VSE_CVP_PROG_CTRL, &val);
	/* request control block to begin transfer using CVP */
	val |= VSE_CVP_PROG_CTRL_CONFIG;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/* STEP 5 - poll CVP_CONFIG READY क्रम 1 with समयout */
	ret = altera_cvp_रुको_status(conf, VSE_CVP_STATUS_CFG_RDY,
				     VSE_CVP_STATUS_CFG_RDY,
				     conf->priv->poll_समय_us);
	अगर (ret) अणु
		dev_warn(&mgr->dev, "CFG_RDY == 1 timeout\n");
		वापस ret;
	पूर्ण

	/*
	 * STEP 6
	 * - set CVP_NUMCLKS to 1 and issue CVP_DUMMY_WR dummy ग_लिखोs to the HIP
	 */
	अगर (conf->priv->चयन_clk)
		conf->priv->चयन_clk(conf);

	अगर (altera_cvp_chkcfg) अणु
		ret = altera_cvp_chk_error(mgr, 0);
		अगर (ret) अणु
			dev_warn(&mgr->dev, "CFG_RDY == 1 timeout\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* STEP 7 - set START_XFER */
	altera_पढ़ो_config_dword(conf, VSE_CVP_PROG_CTRL, &val);
	val |= VSE_CVP_PROG_CTRL_START_XFER;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/* STEP 8 - start transfer (set CVP_NUMCLKS क्रम bitstream) */
	अगर (conf->priv->चयन_clk) अणु
		altera_पढ़ो_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
		val &= ~VSE_CVP_MODE_CTRL_NUMCLKS_MASK;
		val |= conf->numclks << VSE_CVP_MODE_CTRL_NUMCLKS_OFF;
		altera_ग_लिखो_config_dword(conf, VSE_CVP_MODE_CTRL, val);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक altera_cvp_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	माप_प्रकार करोne, reमुख्यing, len;
	स्थिर u32 *data;
	पूर्णांक status = 0;

	/* STEP 9 - ग_लिखो 32-bit data from RBF file to CVP data रेजिस्टर */
	data = (u32 *)buf;
	reमुख्यing = count;
	करोne = 0;

	जबतक (reमुख्यing) अणु
		/* Use credit throttling अगर available */
		अगर (conf->priv->रुको_credit) अणु
			status = conf->priv->रुको_credit(mgr, करोne);
			अगर (status) अणु
				dev_err(&conf->pci_dev->dev,
					"Wait Credit ERR: 0x%x\n", status);
				वापस status;
			पूर्ण
		पूर्ण

		len = min(conf->priv->block_size, reमुख्यing);
		altera_cvp_send_block(conf, data, len);
		data += len / माप(u32);
		करोne += len;
		reमुख्यing -= len;
		conf->sent_packets++;

		/*
		 * STEP 10 (optional) and STEP 11
		 * - check error flag
		 * - loop until data transfer completed
		 * Config images can be huge (more than 40 MiB), so
		 * only check after a new 4k data block has been written.
		 * This reduces the number of checks and speeds up the
		 * configuration process.
		 */
		अगर (altera_cvp_chkcfg && !(करोne % SZ_4K)) अणु
			status = altera_cvp_chk_error(mgr, करोne);
			अगर (status < 0)
				वापस status;
		पूर्ण
	पूर्ण

	अगर (altera_cvp_chkcfg)
		status = altera_cvp_chk_error(mgr, count);

	वापस status;
पूर्ण

अटल पूर्णांक altera_cvp_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				     काष्ठा fpga_image_info *info)
अणु
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	u32 mask, val;
	पूर्णांक ret;

	ret = altera_cvp_tearकरोwn(mgr, info);
	अगर (ret)
		वापस ret;

	/* STEP 16 - check CVP_CONFIG_ERROR_LATCHED bit */
	altera_पढ़ो_config_dword(conf, VSE_UNCOR_ERR_STATUS, &val);
	अगर (val & VSE_UNCOR_ERR_CVP_CFG_ERR) अणु
		dev_err(&mgr->dev, "detected CVP_CONFIG_ERROR_LATCHED!\n");
		वापस -EPROTO;
	पूर्ण

	/* STEP 17 - reset CVP_MODE and HIP_CLK_SEL bit */
	altera_पढ़ो_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_HIP_CLK_SEL;
	val &= ~VSE_CVP_MODE_CTRL_CVP_MODE;
	altera_ग_लिखो_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	/* STEP 18 - poll PLD_CLK_IN_USE and USER_MODE bits */
	mask = VSE_CVP_STATUS_PLD_CLK_IN_USE | VSE_CVP_STATUS_USERMODE;
	ret = altera_cvp_रुको_status(conf, mask, mask,
				     conf->priv->user_समय_us);
	अगर (ret)
		dev_err(&mgr->dev, "PLD_CLK_IN_USE|USERMODE timeout\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops altera_cvp_ops = अणु
	.state		= altera_cvp_state,
	.ग_लिखो_init	= altera_cvp_ग_लिखो_init,
	.ग_लिखो		= altera_cvp_ग_लिखो,
	.ग_लिखो_complete	= altera_cvp_ग_लिखो_complete,
पूर्ण;

अटल स्थिर काष्ठा cvp_priv cvp_priv_v1 = अणु
	.चयन_clk	= altera_cvp_dummy_ग_लिखो,
	.block_size	= ALTERA_CVP_V1_SIZE,
	.poll_समय_us	= V1_POLL_TIMEOUT_US,
	.user_समय_us	= TIMEOUT_US,
पूर्ण;

अटल स्थिर काष्ठा cvp_priv cvp_priv_v2 = अणु
	.clear_state	= altera_cvp_v2_clear_state,
	.रुको_credit	= altera_cvp_v2_रुको_क्रम_credit,
	.block_size	= ALTERA_CVP_V2_SIZE,
	.poll_समय_us	= V2_POLL_TIMEOUT_US,
	.user_समय_us	= V2_USER_TIMEOUT_US,
पूर्ण;

अटल sमाप_प्रकार chkcfg_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, 3, "%d\n", altera_cvp_chkcfg);
पूर्ण

अटल sमाप_प्रकार chkcfg_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = kstrtobool(buf, &altera_cvp_chkcfg);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DRIVER_ATTR_RW(chkcfg);

अटल पूर्णांक altera_cvp_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *dev_id);
अटल व्योम altera_cvp_हटाओ(काष्ठा pci_dev *pdev);

अटल काष्ठा pci_device_id altera_cvp_id_tbl[] = अणु
	अणु PCI_VDEVICE(ALTERA, PCI_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, altera_cvp_id_tbl);

अटल काष्ठा pci_driver altera_cvp_driver = अणु
	.name   = DRV_NAME,
	.id_table = altera_cvp_id_tbl,
	.probe  = altera_cvp_probe,
	.हटाओ = altera_cvp_हटाओ,
पूर्ण;

अटल पूर्णांक altera_cvp_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा altera_cvp_conf *conf;
	काष्ठा fpga_manager *mgr;
	पूर्णांक ret, offset;
	u16 cmd, val;
	u32 regval;

	/* Discover the Venकरोr Specअगरic Offset क्रम this device */
	offset = pci_find_next_ext_capability(pdev, 0, PCI_EXT_CAP_ID_VNDR);
	अगर (!offset) अणु
		dev_err(&pdev->dev, "No Vendor Specific Offset.\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * First check अगर this is the expected FPGA device. PCI config
	 * space access works without enabling the PCI device, memory
	 * space access is enabled further करोwn.
	 */
	pci_पढ़ो_config_word(pdev, offset + VSE_PCIE_EXT_CAP_ID, &val);
	अगर (val != VSE_PCIE_EXT_CAP_ID_VAL) अणु
		dev_err(&pdev->dev, "Wrong EXT_CAP_ID value 0x%x\n", val);
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, offset + VSE_CVP_STATUS, &regval);
	अगर (!(regval & VSE_CVP_STATUS_CVP_EN)) अणु
		dev_err(&pdev->dev,
			"CVP is disabled for this device: CVP_STATUS Reg 0x%x\n",
			regval);
		वापस -ENODEV;
	पूर्ण

	conf = devm_kzalloc(&pdev->dev, माप(*conf), GFP_KERNEL);
	अगर (!conf)
		वापस -ENOMEM;

	conf->vsec_offset = offset;

	/*
	 * Enable memory BAR access. We cannot use pci_enable_device() here
	 * because it will make the driver unusable with FPGA devices that
	 * have additional big IOMEM resources (e.g. 4GiB BARs) on 32-bit
	 * platक्रमm. Such BARs will not have an asचिन्हित address range and
	 * pci_enable_device() will fail, complaining about not claimed BAR,
	 * even अगर the concerned BAR is not needed क्रम FPGA configuration
	 * at all. Thus, enable the device via PCI config space command.
	 */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर (!(cmd & PCI_COMMAND_MEMORY)) अणु
		cmd |= PCI_COMMAND_MEMORY;
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
	पूर्ण

	ret = pci_request_region(pdev, CVP_BAR, "CVP");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Requesting CVP BAR region failed\n");
		जाओ err_disable;
	पूर्ण

	conf->pci_dev = pdev;
	conf->ग_लिखो_data = altera_cvp_ग_लिखो_data_iomem;

	अगर (conf->vsec_offset == V1_VSEC_OFFSET)
		conf->priv = &cvp_priv_v1;
	अन्यथा
		conf->priv = &cvp_priv_v2;

	conf->map = pci_iomap(pdev, CVP_BAR, 0);
	अगर (!conf->map) अणु
		dev_warn(&pdev->dev, "Mapping CVP BAR failed\n");
		conf->ग_लिखो_data = altera_cvp_ग_लिखो_data_config;
	पूर्ण

	snम_लिखो(conf->mgr_name, माप(conf->mgr_name), "%s @%s",
		 ALTERA_CVP_MGR_NAME, pci_name(pdev));

	mgr = devm_fpga_mgr_create(&pdev->dev, conf->mgr_name,
				   &altera_cvp_ops, conf);
	अगर (!mgr) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	pci_set_drvdata(pdev, mgr);

	ret = fpga_mgr_रेजिस्टर(mgr);
	अगर (ret)
		जाओ err_unmap;

	वापस 0;

err_unmap:
	अगर (conf->map)
		pci_iounmap(pdev, conf->map);
	pci_release_region(pdev, CVP_BAR);
err_disable:
	cmd &= ~PCI_COMMAND_MEMORY;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
	वापस ret;
पूर्ण

अटल व्योम altera_cvp_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fpga_manager *mgr = pci_get_drvdata(pdev);
	काष्ठा altera_cvp_conf *conf = mgr->priv;
	u16 cmd;

	fpga_mgr_unरेजिस्टर(mgr);
	अगर (conf->map)
		pci_iounmap(pdev, conf->map);
	pci_release_region(pdev, CVP_BAR);
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	cmd &= ~PCI_COMMAND_MEMORY;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
पूर्ण

अटल पूर्णांक __init altera_cvp_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&altera_cvp_driver);
	अगर (ret)
		वापस ret;

	ret = driver_create_file(&altera_cvp_driver.driver,
				 &driver_attr_chkcfg);
	अगर (ret)
		pr_warn("Can't create sysfs chkcfg file\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास altera_cvp_निकास(व्योम)
अणु
	driver_हटाओ_file(&altera_cvp_driver.driver, &driver_attr_chkcfg);
	pci_unरेजिस्टर_driver(&altera_cvp_driver);
पूर्ण

module_init(altera_cvp_init);
module_निकास(altera_cvp_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_DESCRIPTION("Module to load Altera FPGA over CvP");
