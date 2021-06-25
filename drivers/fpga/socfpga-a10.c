<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Manager Driver क्रम Altera Arria10 SoCFPGA
 *
 * Copyright (C) 2015-2016 Altera Corporation
 */
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>

#घोषणा A10_FPGAMGR_DCLKCNT_OFST				0x08
#घोषणा A10_FPGAMGR_DCLKSTAT_OFST				0x0c
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_OFST				0x70
#घोषणा A10_FPGAMGR_IMGCFG_CTL_01_OFST				0x74
#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_OFST				0x78
#घोषणा A10_FPGAMGR_IMGCFG_STAT_OFST				0x80

#घोषणा A10_FPGAMGR_DCLKSTAT_DCLKDONE				BIT(0)

#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_NCONFIG		BIT(0)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_NSTATUS		BIT(1)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_CONDONE		BIT(2)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_NCONFIG			BIT(8)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_NSTATUS_OE		BIT(16)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_00_S2F_CONDONE_OE		BIT(24)

#घोषणा A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG		BIT(0)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST		BIT(16)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE			BIT(24)

#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL			BIT(0)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_MASK		(BIT(16) | BIT(17))
#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_SHIFT			16
#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_CFGWIDTH			BIT(24)
#घोषणा A10_FPGAMGR_IMGCFG_CTL_02_CFGWIDTH_SHIFT		24

#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_CRC_ERROR			BIT(0)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_EARLY_USERMODE		BIT(1)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE			BIT(2)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN			BIT(4)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_CONDONE_PIN			BIT(6)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_PR_READY			BIT(9)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_PR_DONE			BIT(10)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_PR_ERROR			BIT(11)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_NCONFIG_PIN			BIT(12)
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_MSEL_MASK	(BIT(16) | BIT(17) | BIT(18))
#घोषणा A10_FPGAMGR_IMGCFG_STAT_F2S_MSEL_SHIFT		        16

/* FPGA CD Ratio Value */
#घोषणा CDRATIO_x1						0x0
#घोषणा CDRATIO_x2						0x1
#घोषणा CDRATIO_x4						0x2
#घोषणा CDRATIO_x8						0x3

/* Configuration width 16/32 bit */
#घोषणा CFGWDTH_32						1
#घोषणा CFGWDTH_16						0

/*
 * काष्ठा a10_fpga_priv - निजी data क्रम fpga manager
 * @regmap: regmap क्रम रेजिस्टर access
 * @fpga_data_addr: iomap क्रम single address data रेजिस्टर to FPGA
 * @clk: घड़ी
 */
काष्ठा a10_fpga_priv अणु
	काष्ठा regmap *regmap;
	व्योम __iomem *fpga_data_addr;
	काष्ठा clk *clk;
पूर्ण;

अटल bool socfpga_a10_fpga_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल A10_FPGAMGR_DCLKCNT_OFST:
	हाल A10_FPGAMGR_DCLKSTAT_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_00_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_01_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_02_OFST:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool socfpga_a10_fpga_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल A10_FPGAMGR_DCLKCNT_OFST:
	हाल A10_FPGAMGR_DCLKSTAT_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_00_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_01_OFST:
	हाल A10_FPGAMGR_IMGCFG_CTL_02_OFST:
	हाल A10_FPGAMGR_IMGCFG_STAT_OFST:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config socfpga_a10_fpga_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.ग_लिखोable_reg = socfpga_a10_fpga_ग_लिखोable_reg,
	.पढ़ोable_reg = socfpga_a10_fpga_पढ़ोable_reg,
	.max_रेजिस्टर = A10_FPGAMGR_IMGCFG_STAT_OFST,
	.cache_type = REGCACHE_NONE,
पूर्ण;

/*
 * from the रेजिस्टर map description of cdratio in imgcfg_ctrl_02:
 *  Normal Configuration    : 32bit Passive Parallel
 *  Partial Reconfiguration : 16bit Passive Parallel
 */
अटल व्योम socfpga_a10_fpga_set_cfg_width(काष्ठा a10_fpga_priv *priv,
					   पूर्णांक width)
अणु
	width <<= A10_FPGAMGR_IMGCFG_CTL_02_CFGWIDTH_SHIFT;

	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_CFGWIDTH, width);
पूर्ण

अटल व्योम socfpga_a10_fpga_generate_dclks(काष्ठा a10_fpga_priv *priv,
					    u32 count)
अणु
	u32 val;

	/* Clear any existing DONE status. */
	regmap_ग_लिखो(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST,
		     A10_FPGAMGR_DCLKSTAT_DCLKDONE);

	/* Issue the DCLK regmap. */
	regmap_ग_लिखो(priv->regmap, A10_FPGAMGR_DCLKCNT_OFST, count);

	/* रुको till the dclkcnt करोne */
	regmap_पढ़ो_poll_समयout(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST, val,
				 val, 1, 100);

	/* Clear DONE status. */
	regmap_ग_लिखो(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST,
		     A10_FPGAMGR_DCLKSTAT_DCLKDONE);
पूर्ण

#घोषणा RBF_ENCRYPTION_MODE_OFFSET		69
#घोषणा RBF_DECOMPRESS_OFFSET			229

अटल पूर्णांक socfpga_a10_fpga_encrypted(u32 *buf32, माप_प्रकार buf32_size)
अणु
	अगर (buf32_size < RBF_ENCRYPTION_MODE_OFFSET + 1)
		वापस -EINVAL;

	/* Is the bitstream encrypted? */
	वापस ((buf32[RBF_ENCRYPTION_MODE_OFFSET] >> 2) & 3) != 0;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_compressed(u32 *buf32, माप_प्रकार buf32_size)
अणु
	अगर (buf32_size < RBF_DECOMPRESS_OFFSET + 1)
		वापस -EINVAL;

	/* Is the bitstream compressed? */
	वापस !((buf32[RBF_DECOMPRESS_OFFSET] >> 1) & 1);
पूर्ण

अटल अचिन्हित पूर्णांक socfpga_a10_fpga_get_cd_ratio(अचिन्हित पूर्णांक cfg_width,
						  bool encrypt, bool compress)
अणु
	अचिन्हित पूर्णांक cd_ratio;

	/*
	 * cd ratio is dependent on cfg width and whether the bitstream
	 * is encrypted and/or compressed.
	 *
	 * | width | encr. | compr. | cd ratio |
	 * |  16   |   0   |   0    |     1    |
	 * |  16   |   0   |   1    |     4    |
	 * |  16   |   1   |   0    |     2    |
	 * |  16   |   1   |   1    |     4    |
	 * |  32   |   0   |   0    |     1    |
	 * |  32   |   0   |   1    |     8    |
	 * |  32   |   1   |   0    |     4    |
	 * |  32   |   1   |   1    |     8    |
	 */
	अगर (!compress && !encrypt)
		वापस CDRATIO_x1;

	अगर (compress)
		cd_ratio = CDRATIO_x4;
	अन्यथा
		cd_ratio = CDRATIO_x2;

	/* If 32 bit, द्विगुन the cd ratio by incrementing the field  */
	अगर (cfg_width == CFGWDTH_32)
		cd_ratio += 1;

	वापस cd_ratio;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_set_cdratio(काष्ठा fpga_manager *mgr,
					अचिन्हित पूर्णांक cfg_width,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा a10_fpga_priv *priv = mgr->priv;
	अचिन्हित पूर्णांक cd_ratio;
	पूर्णांक encrypt, compress;

	encrypt = socfpga_a10_fpga_encrypted((u32 *)buf, count / 4);
	अगर (encrypt < 0)
		वापस -EINVAL;

	compress = socfpga_a10_fpga_compressed((u32 *)buf, count / 4);
	अगर (compress < 0)
		वापस -EINVAL;

	cd_ratio = socfpga_a10_fpga_get_cd_ratio(cfg_width, encrypt, compress);

	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_MASK,
			   cd_ratio << A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_SHIFT);

	वापस 0;
पूर्ण

अटल u32 socfpga_a10_fpga_पढ़ो_stat(काष्ठा a10_fpga_priv *priv)
अणु
	u32 val;

	regmap_पढ़ो(priv->regmap, A10_FPGAMGR_IMGCFG_STAT_OFST, &val);

	वापस val;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_रुको_क्रम_pr_पढ़ोy(काष्ठा a10_fpga_priv *priv)
अणु
	u32 reg, i;

	क्रम (i = 0; i < 10 ; i++) अणु
		reg = socfpga_a10_fpga_पढ़ो_stat(priv);

		अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_ERROR)
			वापस -EINVAL;

		अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_READY)
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_रुको_क्रम_pr_करोne(काष्ठा a10_fpga_priv *priv)
अणु
	u32 reg, i;

	क्रम (i = 0; i < 10 ; i++) अणु
		reg = socfpga_a10_fpga_पढ़ो_stat(priv);

		अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_ERROR)
			वापस -EINVAL;

		अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_DONE)
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/* Start the FPGA programming by initialize the FPGA Manager */
अटल पूर्णांक socfpga_a10_fpga_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				       काष्ठा fpga_image_info *info,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा a10_fpga_priv *priv = mgr->priv;
	अचिन्हित पूर्णांक cfg_width;
	u32 msel, stat, mask;
	पूर्णांक ret;

	अगर (info->flags & FPGA_MGR_PARTIAL_RECONFIG)
		cfg_width = CFGWDTH_16;
	अन्यथा
		वापस -EINVAL;

	/* Check क्रम passive parallel (msel == 000 or 001) */
	msel = socfpga_a10_fpga_पढ़ो_stat(priv);
	msel &= A10_FPGAMGR_IMGCFG_STAT_F2S_MSEL_MASK;
	msel >>= A10_FPGAMGR_IMGCFG_STAT_F2S_MSEL_SHIFT;
	अगर ((msel != 0) && (msel != 1)) अणु
		dev_dbg(&mgr->dev, "Fail: invalid msel=%d\n", msel);
		वापस -EINVAL;
	पूर्ण

	/* Make sure no बाह्यal devices are पूर्णांकerfering */
	stat = socfpga_a10_fpga_पढ़ो_stat(priv);
	mask = A10_FPGAMGR_IMGCFG_STAT_F2S_NCONFIG_PIN |
	       A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN;
	अगर ((stat & mask) != mask)
		वापस -EINVAL;

	/* Set cfg width */
	socfpga_a10_fpga_set_cfg_width(priv, cfg_width);

	/* Determine cd ratio from bitstream header and set cd ratio */
	ret = socfpga_a10_fpga_set_cdratio(mgr, cfg_width, buf, count);
	अगर (ret)
		वापस ret;

	/*
	 * Clear s2f_nce to enable chip select.  Leave pr_request
	 * unनिश्चितed and override disabled.
	 */
	regmap_ग_लिखो(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
		     A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG);

	/* Set cfg_ctrl to enable s2f dclk and data */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL,
			   A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL);

	/*
	 * Disable overrides not needed क्रम pr.
	 * s2f_config==1 leaves reset deasseted.
	 */
	regmap_ग_लिखो(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_00_OFST,
		     A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_NCONFIG |
		     A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_NSTATUS |
		     A10_FPGAMGR_IMGCFG_CTL_00_S2F_NENABLE_CONDONE |
		     A10_FPGAMGR_IMGCFG_CTL_00_S2F_NCONFIG);

	/* Enable override क्रम data, dclk, nce, and pr_request to CSS */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG, 0);

	/* Send some घड़ीs to clear out any errors */
	socfpga_a10_fpga_generate_dclks(priv, 256);

	/* Assert pr_request */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST);

	/* Provide 2048 DCLKs beक्रमe starting the config data streaming. */
	socfpga_a10_fpga_generate_dclks(priv, 0x7ff);

	/* Wait क्रम pr_पढ़ोy */
	वापस socfpga_a10_fpga_रुको_क्रम_pr_पढ़ोy(priv);
पूर्ण

/*
 * ग_लिखो data to the FPGA data रेजिस्टर
 */
अटल पूर्णांक socfpga_a10_fpga_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	काष्ठा a10_fpga_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	माप_प्रकार i = 0;

	अगर (count <= 0)
		वापस -EINVAL;

	/* Write out the complete 32-bit chunks */
	जबतक (count >= माप(u32)) अणु
		ग_लिखोl(buffer_32[i++], priv->fpga_data_addr);
		count -= माप(u32);
	पूर्ण

	/* Write out reमुख्यing non 32-bit chunks */
	चयन (count) अणु
	हाल 3:
		ग_लिखोl(buffer_32[i++] & 0x00ffffff, priv->fpga_data_addr);
		अवरोध;
	हाल 2:
		ग_लिखोl(buffer_32[i++] & 0x0000ffff, priv->fpga_data_addr);
		अवरोध;
	हाल 1:
		ग_लिखोl(buffer_32[i++] & 0x000000ff, priv->fpga_data_addr);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		/* This will never happen */
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
					   काष्ठा fpga_image_info *info)
अणु
	काष्ठा a10_fpga_priv *priv = mgr->priv;
	u32 reg;
	पूर्णांक ret;

	/* Wait क्रम pr_करोne */
	ret = socfpga_a10_fpga_रुको_क्रम_pr_करोne(priv);

	/* Clear pr_request */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST, 0);

	/* Send some घड़ीs to clear out any errors */
	socfpga_a10_fpga_generate_dclks(priv, 256);

	/* Disable s2f dclk and data */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL, 0);

	/* Deनिश्चित chip select */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE);

	/* Disable data, dclk, nce, and pr_request override to CSS */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG);

	/* Return any errors regarding pr_करोne or pr_error */
	अगर (ret)
		वापस ret;

	/* Final check */
	reg = socfpga_a10_fpga_पढ़ो_stat(priv);

	अगर (((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE) == 0) ||
	    ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_CONDONE_PIN) == 0) ||
	    ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN) == 0)) अणु
		dev_dbg(&mgr->dev,
			"Timeout in final check. Status=%08xf\n", reg);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत fpga_mgr_states socfpga_a10_fpga_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा a10_fpga_priv *priv = mgr->priv;
	u32 reg = socfpga_a10_fpga_पढ़ो_stat(priv);

	अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE)
		वापस FPGA_MGR_STATE_OPERATING;

	अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_PR_READY)
		वापस FPGA_MGR_STATE_WRITE;

	अगर (reg & A10_FPGAMGR_IMGCFG_STAT_F2S_CRC_ERROR)
		वापस FPGA_MGR_STATE_WRITE_COMPLETE_ERR;

	अगर ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN) == 0)
		वापस FPGA_MGR_STATE_RESET;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops socfpga_a10_fpga_mgr_ops = अणु
	.initial_header_size = (RBF_DECOMPRESS_OFFSET + 1) * 4,
	.state = socfpga_a10_fpga_state,
	.ग_लिखो_init = socfpga_a10_fpga_ग_लिखो_init,
	.ग_लिखो = socfpga_a10_fpga_ग_लिखो,
	.ग_लिखो_complete = socfpga_a10_fpga_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक socfpga_a10_fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा a10_fpga_priv *priv;
	व्योम __iomem *reg_base;
	काष्ठा fpga_manager *mgr;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* First mmio base is क्रम रेजिस्टर access */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	/* Second mmio base is क्रम writing FPGA image data */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->fpga_data_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->fpga_data_addr))
		वापस PTR_ERR(priv->fpga_data_addr);

	/* regmap क्रम रेजिस्टर access */
	priv->regmap = devm_regmap_init_mmio(dev, reg_base,
					     &socfpga_a10_fpga_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस -ENODEV;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "no clock specified\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable clock\n");
		वापस -EBUSY;
	पूर्ण

	mgr = devm_fpga_mgr_create(dev, "SoCFPGA Arria10 FPGA Manager",
				   &socfpga_a10_fpga_mgr_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mgr);

	ret = fpga_mgr_रेजिस्टर(mgr);
	अगर (ret) अणु
		clk_disable_unprepare(priv->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_a10_fpga_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_manager *mgr = platक्रमm_get_drvdata(pdev);
	काष्ठा a10_fpga_priv *priv = mgr->priv;

	fpga_mgr_unरेजिस्टर(mgr);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id socfpga_a10_fpga_of_match[] = अणु
	अणु .compatible = "altr,socfpga-a10-fpga-mgr", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, socfpga_a10_fpga_of_match);

अटल काष्ठा platक्रमm_driver socfpga_a10_fpga_driver = अणु
	.probe = socfpga_a10_fpga_probe,
	.हटाओ = socfpga_a10_fpga_हटाओ,
	.driver = अणु
		.name	= "socfpga_a10_fpga_manager",
		.of_match_table = socfpga_a10_fpga_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(socfpga_a10_fpga_driver);

MODULE_AUTHOR("Alan Tull <atull@opensource.altera.com>");
MODULE_DESCRIPTION("SoCFPGA Arria10 FPGA Manager");
MODULE_LICENSE("GPL v2");
