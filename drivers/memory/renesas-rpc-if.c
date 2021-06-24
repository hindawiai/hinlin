<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RPC-IF core driver
 *
 * Copyright (C) 2018-2019 Renesas Solutions Corp.
 * Copyright (C) 2019 Macronix International Co., Ltd.
 * Copyright (C) 2019-2020 Cogent Embedded, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <memory/renesas-rpc-अगर.h>

#घोषणा RPCIF_CMNCR		0x0000	/* R/W */
#घोषणा RPCIF_CMNCR_MD		BIT(31)
#घोषणा RPCIF_CMNCR_SFDE	BIT(24) /* unकरोcumented but must be set */
#घोषणा RPCIF_CMNCR_MOIIO3(val)	(((val) & 0x3) << 22)
#घोषणा RPCIF_CMNCR_MOIIO2(val)	(((val) & 0x3) << 20)
#घोषणा RPCIF_CMNCR_MOIIO1(val)	(((val) & 0x3) << 18)
#घोषणा RPCIF_CMNCR_MOIIO0(val)	(((val) & 0x3) << 16)
#घोषणा RPCIF_CMNCR_MOIIO_HIZ	(RPCIF_CMNCR_MOIIO0(3) | \
				 RPCIF_CMNCR_MOIIO1(3) | \
				 RPCIF_CMNCR_MOIIO2(3) | RPCIF_CMNCR_MOIIO3(3))
#घोषणा RPCIF_CMNCR_IO3FV(val)	(((val) & 0x3) << 14) /* unकरोcumented */
#घोषणा RPCIF_CMNCR_IO2FV(val)	(((val) & 0x3) << 12) /* unकरोcumented */
#घोषणा RPCIF_CMNCR_IO0FV(val)	(((val) & 0x3) << 8)
#घोषणा RPCIF_CMNCR_IOFV_HIZ	(RPCIF_CMNCR_IO0FV(3) | RPCIF_CMNCR_IO2FV(3) | \
				 RPCIF_CMNCR_IO3FV(3))
#घोषणा RPCIF_CMNCR_BSZ(val)	(((val) & 0x3) << 0)

#घोषणा RPCIF_SSLDR		0x0004	/* R/W */
#घोषणा RPCIF_SSLDR_SPNDL(d)	(((d) & 0x7) << 16)
#घोषणा RPCIF_SSLDR_SLNDL(d)	(((d) & 0x7) << 8)
#घोषणा RPCIF_SSLDR_SCKDL(d)	(((d) & 0x7) << 0)

#घोषणा RPCIF_DRCR		0x000C	/* R/W */
#घोषणा RPCIF_DRCR_SSLN		BIT(24)
#घोषणा RPCIF_DRCR_RBURST(v)	((((v) - 1) & 0x1F) << 16)
#घोषणा RPCIF_DRCR_RCF		BIT(9)
#घोषणा RPCIF_DRCR_RBE		BIT(8)
#घोषणा RPCIF_DRCR_SSLE		BIT(0)

#घोषणा RPCIF_DRCMR		0x0010	/* R/W */
#घोषणा RPCIF_DRCMR_CMD(c)	(((c) & 0xFF) << 16)
#घोषणा RPCIF_DRCMR_OCMD(c)	(((c) & 0xFF) << 0)

#घोषणा RPCIF_DREAR		0x0014	/* R/W */
#घोषणा RPCIF_DREAR_EAV(c)	(((c) & 0xF) << 16)
#घोषणा RPCIF_DREAR_EAC(c)	(((c) & 0x7) << 0)

#घोषणा RPCIF_DROPR		0x0018	/* R/W */

#घोषणा RPCIF_DRENR		0x001C	/* R/W */
#घोषणा RPCIF_DRENR_CDB(o)	(u32)((((o) & 0x3) << 30))
#घोषणा RPCIF_DRENR_OCDB(o)	(((o) & 0x3) << 28)
#घोषणा RPCIF_DRENR_ADB(o)	(((o) & 0x3) << 24)
#घोषणा RPCIF_DRENR_OPDB(o)	(((o) & 0x3) << 20)
#घोषणा RPCIF_DRENR_DRDB(o)	(((o) & 0x3) << 16)
#घोषणा RPCIF_DRENR_DME		BIT(15)
#घोषणा RPCIF_DRENR_CDE		BIT(14)
#घोषणा RPCIF_DRENR_OCDE	BIT(12)
#घोषणा RPCIF_DRENR_ADE(v)	(((v) & 0xF) << 8)
#घोषणा RPCIF_DRENR_OPDE(v)	(((v) & 0xF) << 4)

#घोषणा RPCIF_SMCR		0x0020	/* R/W */
#घोषणा RPCIF_SMCR_SSLKP	BIT(8)
#घोषणा RPCIF_SMCR_SPIRE	BIT(2)
#घोषणा RPCIF_SMCR_SPIWE	BIT(1)
#घोषणा RPCIF_SMCR_SPIE		BIT(0)

#घोषणा RPCIF_SMCMR		0x0024	/* R/W */
#घोषणा RPCIF_SMCMR_CMD(c)	(((c) & 0xFF) << 16)
#घोषणा RPCIF_SMCMR_OCMD(c)	(((c) & 0xFF) << 0)

#घोषणा RPCIF_SMADR		0x0028	/* R/W */

#घोषणा RPCIF_SMOPR		0x002C	/* R/W */
#घोषणा RPCIF_SMOPR_OPD3(o)	(((o) & 0xFF) << 24)
#घोषणा RPCIF_SMOPR_OPD2(o)	(((o) & 0xFF) << 16)
#घोषणा RPCIF_SMOPR_OPD1(o)	(((o) & 0xFF) << 8)
#घोषणा RPCIF_SMOPR_OPD0(o)	(((o) & 0xFF) << 0)

#घोषणा RPCIF_SMENR		0x0030	/* R/W */
#घोषणा RPCIF_SMENR_CDB(o)	(((o) & 0x3) << 30)
#घोषणा RPCIF_SMENR_OCDB(o)	(((o) & 0x3) << 28)
#घोषणा RPCIF_SMENR_ADB(o)	(((o) & 0x3) << 24)
#घोषणा RPCIF_SMENR_OPDB(o)	(((o) & 0x3) << 20)
#घोषणा RPCIF_SMENR_SPIDB(o)	(((o) & 0x3) << 16)
#घोषणा RPCIF_SMENR_DME		BIT(15)
#घोषणा RPCIF_SMENR_CDE		BIT(14)
#घोषणा RPCIF_SMENR_OCDE	BIT(12)
#घोषणा RPCIF_SMENR_ADE(v)	(((v) & 0xF) << 8)
#घोषणा RPCIF_SMENR_OPDE(v)	(((v) & 0xF) << 4)
#घोषणा RPCIF_SMENR_SPIDE(v)	(((v) & 0xF) << 0)

#घोषणा RPCIF_SMRDR0		0x0038	/* R */
#घोषणा RPCIF_SMRDR1		0x003C	/* R */
#घोषणा RPCIF_SMWDR0		0x0040	/* W */
#घोषणा RPCIF_SMWDR1		0x0044	/* W */

#घोषणा RPCIF_CMNSR		0x0048	/* R */
#घोषणा RPCIF_CMNSR_SSLF	BIT(1)
#घोषणा RPCIF_CMNSR_TEND	BIT(0)

#घोषणा RPCIF_DRDMCR		0x0058	/* R/W */
#घोषणा RPCIF_DMDMCR_DMCYC(v)	((((v) - 1) & 0x1F) << 0)

#घोषणा RPCIF_DRDRENR		0x005C	/* R/W */
#घोषणा RPCIF_DRDRENR_HYPE(v)	(((v) & 0x7) << 12)
#घोषणा RPCIF_DRDRENR_ADDRE	BIT(8)
#घोषणा RPCIF_DRDRENR_OPDRE	BIT(4)
#घोषणा RPCIF_DRDRENR_DRDRE	BIT(0)

#घोषणा RPCIF_SMDMCR		0x0060	/* R/W */
#घोषणा RPCIF_SMDMCR_DMCYC(v)	((((v) - 1) & 0x1F) << 0)

#घोषणा RPCIF_SMDRENR		0x0064	/* R/W */
#घोषणा RPCIF_SMDRENR_HYPE(v)	(((v) & 0x7) << 12)
#घोषणा RPCIF_SMDRENR_ADDRE	BIT(8)
#घोषणा RPCIF_SMDRENR_OPDRE	BIT(4)
#घोषणा RPCIF_SMDRENR_SPIDRE	BIT(0)

#घोषणा RPCIF_PHYCNT		0x007C	/* R/W */
#घोषणा RPCIF_PHYCNT_CAL	BIT(31)
#घोषणा RPCIF_PHYCNT_OCTA(v)	(((v) & 0x3) << 22)
#घोषणा RPCIF_PHYCNT_EXDS	BIT(21)
#घोषणा RPCIF_PHYCNT_OCT	BIT(20)
#घोषणा RPCIF_PHYCNT_DDRCAL	BIT(19)
#घोषणा RPCIF_PHYCNT_HS		BIT(18)
#घोषणा RPCIF_PHYCNT_STRTIM(v)	(((v) & 0x7) << 15)
#घोषणा RPCIF_PHYCNT_WBUF2	BIT(4)
#घोषणा RPCIF_PHYCNT_WBUF	BIT(2)
#घोषणा RPCIF_PHYCNT_PHYMEM(v)	(((v) & 0x3) << 0)

#घोषणा RPCIF_PHYOFFSET1	0x0080	/* R/W */
#घोषणा RPCIF_PHYOFFSET1_DDRTMG(v) (((v) & 0x3) << 28)

#घोषणा RPCIF_PHYOFFSET2	0x0084	/* R/W */
#घोषणा RPCIF_PHYOFFSET2_OCTTMG(v) (((v) & 0x7) << 8)

#घोषणा RPCIF_PHYINT		0x0088	/* R/W */
#घोषणा RPCIF_PHYINT_WPVAL	BIT(1)

#घोषणा RPCIF_सूचीMAP_SIZE	0x4000000

अटल स्थिर काष्ठा regmap_range rpcअगर_अस्थिर_ranges[] = अणु
	regmap_reg_range(RPCIF_SMRDR0, RPCIF_SMRDR1),
	regmap_reg_range(RPCIF_SMWDR0, RPCIF_SMWDR1),
	regmap_reg_range(RPCIF_CMNSR, RPCIF_CMNSR),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table rpcअगर_अस्थिर_table = अणु
	.yes_ranges	= rpcअगर_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(rpcअगर_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config rpcअगर_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.fast_io	= true,
	.max_रेजिस्टर	= RPCIF_PHYINT,
	.अस्थिर_table	= &rpcअगर_अस्थिर_table,
पूर्ण;

पूर्णांक rpcअगर_sw_init(काष्ठा rpcअगर *rpc, काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;
	व्योम __iomem *base;

	rpc->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	rpc->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					    &rpcअगर_regmap_config);
	अगर (IS_ERR(rpc->regmap)) अणु
		dev_err(&pdev->dev,
			"failed to init regmap for rpcif, error %ld\n",
			PTR_ERR(rpc->regmap));
		वापस	PTR_ERR(rpc->regmap);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dirmap");
	rpc->dirmap = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rpc->dirmap))
		rpc->dirmap = शून्य;
	rpc->size = resource_size(res);

	rpc->rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);

	वापस PTR_ERR_OR_ZERO(rpc->rstc);
पूर्ण
EXPORT_SYMBOL(rpcअगर_sw_init);

व्योम rpcअगर_hw_init(काष्ठा rpcअगर *rpc, bool hyperflash)
अणु
	u32 dummy;

	pm_runसमय_get_sync(rpc->dev);

	/*
	 * NOTE: The 0x260 are unकरोcumented bits, but they must be set.
	 *	 RPCIF_PHYCNT_STRTIM is strobe timing adjusपंचांगent bits,
	 *	 0x0 : the delay is biggest,
	 *	 0x1 : the delay is 2nd biggest,
	 *	 On H3 ES1.x, the value should be 0, जबतक on others,
	 *	 the value should be 7.
	 */
	regmap_ग_लिखो(rpc->regmap, RPCIF_PHYCNT, RPCIF_PHYCNT_STRTIM(7) |
		     RPCIF_PHYCNT_PHYMEM(hyperflash ? 3 : 0) | 0x260);

	/*
	 * NOTE: The 0x1511144 are unकरोcumented bits, but they must be set
	 *       क्रम RPCIF_PHYOFFSET1.
	 *	 The 0x31 are unकरोcumented bits, but they must be set
	 *	 क्रम RPCIF_PHYOFFSET2.
	 */
	regmap_ग_लिखो(rpc->regmap, RPCIF_PHYOFFSET1, 0x1511144 |
		     RPCIF_PHYOFFSET1_DDRTMG(3));
	regmap_ग_लिखो(rpc->regmap, RPCIF_PHYOFFSET2, 0x31 |
		     RPCIF_PHYOFFSET2_OCTTMG(4));

	अगर (hyperflash)
		regmap_update_bits(rpc->regmap, RPCIF_PHYINT,
				   RPCIF_PHYINT_WPVAL, 0);

	regmap_ग_लिखो(rpc->regmap, RPCIF_CMNCR, RPCIF_CMNCR_SFDE |
		     RPCIF_CMNCR_MOIIO_HIZ | RPCIF_CMNCR_IOFV_HIZ |
		     RPCIF_CMNCR_BSZ(hyperflash ? 1 : 0));
	/* Set RCF after BSZ update */
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRCR, RPCIF_DRCR_RCF);
	/* Dummy पढ़ो according to spec */
	regmap_पढ़ो(rpc->regmap, RPCIF_DRCR, &dummy);
	regmap_ग_लिखो(rpc->regmap, RPCIF_SSLDR, RPCIF_SSLDR_SPNDL(7) |
		     RPCIF_SSLDR_SLNDL(7) | RPCIF_SSLDR_SCKDL(7));

	pm_runसमय_put(rpc->dev);

	rpc->bus_size = hyperflash ? 2 : 1;
पूर्ण
EXPORT_SYMBOL(rpcअगर_hw_init);

अटल पूर्णांक रुको_msg_xfer_end(काष्ठा rpcअगर *rpc)
अणु
	u32 sts;

	वापस regmap_पढ़ो_poll_समयout(rpc->regmap, RPCIF_CMNSR, sts,
					sts & RPCIF_CMNSR_TEND, 0,
					USEC_PER_SEC);
पूर्ण

अटल u8 rpcअगर_bits_set(काष्ठा rpcअगर *rpc, u32 nbytes)
अणु
	अगर (rpc->bus_size == 2)
		nbytes /= 2;
	nbytes = clamp(nbytes, 1U, 4U);
	वापस GENMASK(3, 4 - nbytes);
पूर्ण

अटल u8 rpcअगर_bit_size(u8 buswidth)
अणु
	वापस buswidth > 4 ? 2 : ilog2(buswidth);
पूर्ण

व्योम rpcअगर_prepare(काष्ठा rpcअगर *rpc, स्थिर काष्ठा rpcअगर_op *op, u64 *offs,
		   माप_प्रकार *len)
अणु
	rpc->smcr = 0;
	rpc->smadr = 0;
	rpc->enable = 0;
	rpc->command = 0;
	rpc->option = 0;
	rpc->dummy = 0;
	rpc->ddr = 0;
	rpc->xferlen = 0;

	अगर (op->cmd.buswidth) अणु
		rpc->enable  = RPCIF_SMENR_CDE |
			RPCIF_SMENR_CDB(rpcअगर_bit_size(op->cmd.buswidth));
		rpc->command = RPCIF_SMCMR_CMD(op->cmd.opcode);
		अगर (op->cmd.ddr)
			rpc->ddr = RPCIF_SMDRENR_HYPE(0x5);
	पूर्ण
	अगर (op->ocmd.buswidth) अणु
		rpc->enable  |= RPCIF_SMENR_OCDE |
			RPCIF_SMENR_OCDB(rpcअगर_bit_size(op->ocmd.buswidth));
		rpc->command |= RPCIF_SMCMR_OCMD(op->ocmd.opcode);
	पूर्ण

	अगर (op->addr.buswidth) अणु
		rpc->enable |=
			RPCIF_SMENR_ADB(rpcअगर_bit_size(op->addr.buswidth));
		अगर (op->addr.nbytes == 4)
			rpc->enable |= RPCIF_SMENR_ADE(0xF);
		अन्यथा
			rpc->enable |= RPCIF_SMENR_ADE(GENMASK(
						2, 3 - op->addr.nbytes));
		अगर (op->addr.ddr)
			rpc->ddr |= RPCIF_SMDRENR_ADDRE;

		अगर (offs && len)
			rpc->smadr = *offs;
		अन्यथा
			rpc->smadr = op->addr.val;
	पूर्ण

	अगर (op->dummy.buswidth) अणु
		rpc->enable |= RPCIF_SMENR_DME;
		rpc->dummy = RPCIF_SMDMCR_DMCYC(op->dummy.ncycles /
						op->dummy.buswidth);
	पूर्ण

	अगर (op->option.buswidth) अणु
		rpc->enable |= RPCIF_SMENR_OPDE(
			rpcअगर_bits_set(rpc, op->option.nbytes)) |
			RPCIF_SMENR_OPDB(rpcअगर_bit_size(op->option.buswidth));
		अगर (op->option.ddr)
			rpc->ddr |= RPCIF_SMDRENR_OPDRE;
		rpc->option = op->option.val;
	पूर्ण

	rpc->dir = op->data.dir;
	अगर (op->data.buswidth) अणु
		u32 nbytes;

		rpc->buffer = op->data.buf.in;
		चयन (op->data.dir) अणु
		हाल RPCIF_DATA_IN:
			rpc->smcr = RPCIF_SMCR_SPIRE;
			अवरोध;
		हाल RPCIF_DATA_OUT:
			rpc->smcr = RPCIF_SMCR_SPIWE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (op->data.ddr)
			rpc->ddr |= RPCIF_SMDRENR_SPIDRE;

		अगर (offs && len)
			nbytes = *len;
		अन्यथा
			nbytes = op->data.nbytes;
		rpc->xferlen = nbytes;

		rpc->enable |= RPCIF_SMENR_SPIDE(rpcअगर_bits_set(rpc, nbytes)) |
			RPCIF_SMENR_SPIDB(rpcअगर_bit_size(op->data.buswidth));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rpcअगर_prepare);

पूर्णांक rpcअगर_manual_xfer(काष्ठा rpcअगर *rpc)
अणु
	u32 smenr, smcr, pos = 0, max = 4;
	पूर्णांक ret = 0;

	अगर (rpc->bus_size == 2)
		max = 8;

	pm_runसमय_get_sync(rpc->dev);

	regmap_update_bits(rpc->regmap, RPCIF_PHYCNT,
			   RPCIF_PHYCNT_CAL, RPCIF_PHYCNT_CAL);
	regmap_update_bits(rpc->regmap, RPCIF_CMNCR,
			   RPCIF_CMNCR_MD, RPCIF_CMNCR_MD);
	regmap_ग_लिखो(rpc->regmap, RPCIF_SMCMR, rpc->command);
	regmap_ग_लिखो(rpc->regmap, RPCIF_SMOPR, rpc->option);
	regmap_ग_लिखो(rpc->regmap, RPCIF_SMDMCR, rpc->dummy);
	regmap_ग_लिखो(rpc->regmap, RPCIF_SMDRENR, rpc->ddr);
	smenr = rpc->enable;

	चयन (rpc->dir) अणु
	हाल RPCIF_DATA_OUT:
		जबतक (pos < rpc->xferlen) अणु
			u32 nbytes = rpc->xferlen - pos;
			u32 data[2];

			smcr = rpc->smcr | RPCIF_SMCR_SPIE;
			अगर (nbytes > max) अणु
				nbytes = max;
				smcr |= RPCIF_SMCR_SSLKP;
			पूर्ण

			स_नकल(data, rpc->buffer + pos, nbytes);
			अगर (nbytes > 4) अणु
				regmap_ग_लिखो(rpc->regmap, RPCIF_SMWDR1,
					     data[0]);
				regmap_ग_लिखो(rpc->regmap, RPCIF_SMWDR0,
					     data[1]);
			पूर्ण अन्यथा अगर (nbytes > 2) अणु
				regmap_ग_लिखो(rpc->regmap, RPCIF_SMWDR0,
					     data[0]);
			पूर्ण अन्यथा	अणु
				regmap_ग_लिखो(rpc->regmap, RPCIF_SMWDR0,
					     data[0] << 16);
			पूर्ण

			regmap_ग_लिखो(rpc->regmap, RPCIF_SMADR,
				     rpc->smadr + pos);
			regmap_ग_लिखो(rpc->regmap, RPCIF_SMENR, smenr);
			regmap_ग_लिखो(rpc->regmap, RPCIF_SMCR, smcr);
			ret = रुको_msg_xfer_end(rpc);
			अगर (ret)
				जाओ err_out;

			pos += nbytes;
			smenr = rpc->enable &
				~RPCIF_SMENR_CDE & ~RPCIF_SMENR_ADE(0xF);
		पूर्ण
		अवरोध;
	हाल RPCIF_DATA_IN:
		/*
		 * RPC-IF spoils the data क्रम the commands without an address
		 * phase (like RDID) in the manual mode, so we'll have to work
		 * around this issue by using the बाह्यal address space पढ़ो
		 * mode instead.
		 */
		अगर (!(smenr & RPCIF_SMENR_ADE(0xF)) && rpc->dirmap) अणु
			u32 dummy;

			regmap_update_bits(rpc->regmap, RPCIF_CMNCR,
					   RPCIF_CMNCR_MD, 0);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRCR,
				     RPCIF_DRCR_RBURST(32) | RPCIF_DRCR_RBE);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRCMR, rpc->command);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DREAR,
				     RPCIF_DREAR_EAC(1));
			regmap_ग_लिखो(rpc->regmap, RPCIF_DROPR, rpc->option);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRENR,
				     smenr & ~RPCIF_SMENR_SPIDE(0xF));
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRDMCR,  rpc->dummy);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRDRENR, rpc->ddr);
			स_नकल_fromio(rpc->buffer, rpc->dirmap, rpc->xferlen);
			regmap_ग_लिखो(rpc->regmap, RPCIF_DRCR, RPCIF_DRCR_RCF);
			/* Dummy पढ़ो according to spec */
			regmap_पढ़ो(rpc->regmap, RPCIF_DRCR, &dummy);
			अवरोध;
		पूर्ण
		जबतक (pos < rpc->xferlen) अणु
			u32 nbytes = rpc->xferlen - pos;
			u32 data[2];

			अगर (nbytes > max)
				nbytes = max;

			regmap_ग_लिखो(rpc->regmap, RPCIF_SMADR,
				     rpc->smadr + pos);
			regmap_ग_लिखो(rpc->regmap, RPCIF_SMENR, smenr);
			regmap_ग_लिखो(rpc->regmap, RPCIF_SMCR,
				     rpc->smcr | RPCIF_SMCR_SPIE);
			ret = रुको_msg_xfer_end(rpc);
			अगर (ret)
				जाओ err_out;

			अगर (nbytes > 4) अणु
				regmap_पढ़ो(rpc->regmap, RPCIF_SMRDR1,
					    &data[0]);
				regmap_पढ़ो(rpc->regmap, RPCIF_SMRDR0,
					    &data[1]);
			पूर्ण अन्यथा अगर (nbytes > 2) अणु
				regmap_पढ़ो(rpc->regmap, RPCIF_SMRDR0,
					    &data[0]);
			पूर्ण अन्यथा	अणु
				regmap_पढ़ो(rpc->regmap, RPCIF_SMRDR0,
					    &data[0]);
				data[0] >>= 16;
			पूर्ण
			स_नकल(rpc->buffer + pos, data, nbytes);

			pos += nbytes;
		पूर्ण
		अवरोध;
	शेष:
		regmap_ग_लिखो(rpc->regmap, RPCIF_SMENR, rpc->enable);
		regmap_ग_लिखो(rpc->regmap, RPCIF_SMCR,
			     rpc->smcr | RPCIF_SMCR_SPIE);
		ret = रुको_msg_xfer_end(rpc);
		अगर (ret)
			जाओ err_out;
	पूर्ण

निकास:
	pm_runसमय_put(rpc->dev);
	वापस ret;

err_out:
	अगर (reset_control_reset(rpc->rstc))
		dev_err(rpc->dev, "Failed to reset HW\n");
	rpcअगर_hw_init(rpc, rpc->bus_size == 2);
	जाओ निकास;
पूर्ण
EXPORT_SYMBOL(rpcअगर_manual_xfer);

sमाप_प्रकार rpcअगर_dirmap_पढ़ो(काष्ठा rpcअगर *rpc, u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	loff_t from = offs & (RPCIF_सूचीMAP_SIZE - 1);
	माप_प्रकार size = RPCIF_सूचीMAP_SIZE - from;

	अगर (len > size)
		len = size;

	pm_runसमय_get_sync(rpc->dev);

	regmap_update_bits(rpc->regmap, RPCIF_CMNCR, RPCIF_CMNCR_MD, 0);
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRCR, 0);
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRCMR, rpc->command);
	regmap_ग_लिखो(rpc->regmap, RPCIF_DREAR,
		     RPCIF_DREAR_EAV(offs >> 25) | RPCIF_DREAR_EAC(1));
	regmap_ग_लिखो(rpc->regmap, RPCIF_DROPR, rpc->option);
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRENR,
		     rpc->enable & ~RPCIF_SMENR_SPIDE(0xF));
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRDMCR, rpc->dummy);
	regmap_ग_लिखो(rpc->regmap, RPCIF_DRDRENR, rpc->ddr);

	स_नकल_fromio(buf, rpc->dirmap + from, len);

	pm_runसमय_put(rpc->dev);

	वापस len;
पूर्ण
EXPORT_SYMBOL(rpcअगर_dirmap_पढ़ो);

अटल पूर्णांक rpcअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *vdev;
	काष्ठा device_node *flash;
	स्थिर अक्षर *name;

	flash = of_get_next_child(pdev->dev.of_node, शून्य);
	अगर (!flash) अणु
		dev_warn(&pdev->dev, "no flash node found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_device_is_compatible(flash, "jedec,spi-nor")) अणु
		name = "rpc-if-spi";
	पूर्ण अन्यथा अगर (of_device_is_compatible(flash, "cfi-flash")) अणु
		name = "rpc-if-hyperflash";
	पूर्ण अन्यथा	अणु
		of_node_put(flash);
		dev_warn(&pdev->dev, "unknown flash type\n");
		वापस -ENODEV;
	पूर्ण
	of_node_put(flash);

	vdev = platक्रमm_device_alloc(name, pdev->id);
	अगर (!vdev)
		वापस -ENOMEM;
	vdev->dev.parent = &pdev->dev;
	platक्रमm_set_drvdata(pdev, vdev);
	वापस platक्रमm_device_add(vdev);
पूर्ण

अटल पूर्णांक rpcअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *vdev = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(vdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rpcअगर_of_match[] = अणु
	अणु .compatible = "renesas,rcar-gen3-rpc-if", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rpcअगर_of_match);

अटल काष्ठा platक्रमm_driver rpcअगर_driver = अणु
	.probe	= rpcअगर_probe,
	.हटाओ	= rpcअगर_हटाओ,
	.driver = अणु
		.name =	"rpc-if",
		.of_match_table = rpcअगर_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rpcअगर_driver);

MODULE_DESCRIPTION("Renesas RPC-IF core driver");
MODULE_LICENSE("GPL v2");
