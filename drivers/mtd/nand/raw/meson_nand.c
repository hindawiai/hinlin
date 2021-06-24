<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Amlogic Meson Nand Flash Controller Driver
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Liang Yang <liang.yang@amlogic.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sched/task_stack.h>

#घोषणा NFC_REG_CMD		0x00
#घोषणा NFC_CMD_IDLE		(0xc << 14)
#घोषणा NFC_CMD_CLE		(0x5 << 14)
#घोषणा NFC_CMD_ALE		(0x6 << 14)
#घोषणा NFC_CMD_ADL		((0 << 16) | (3 << 20))
#घोषणा NFC_CMD_ADH		((1 << 16) | (3 << 20))
#घोषणा NFC_CMD_AIL		((2 << 16) | (3 << 20))
#घोषणा NFC_CMD_AIH		((3 << 16) | (3 << 20))
#घोषणा NFC_CMD_SEED		((8 << 16) | (3 << 20))
#घोषणा NFC_CMD_M2N		((0 << 17) | (2 << 20))
#घोषणा NFC_CMD_N2M		((1 << 17) | (2 << 20))
#घोषणा NFC_CMD_RB		BIT(20)
#घोषणा NFC_CMD_SCRAMBLER_ENABLE	BIT(19)
#घोषणा NFC_CMD_SCRAMBLER_DISABLE	0
#घोषणा NFC_CMD_SHORTMODE_DISABLE	0
#घोषणा NFC_CMD_RB_INT		BIT(14)

#घोषणा NFC_CMD_GET_SIZE(x)	(((x) >> 22) & GENMASK(4, 0))

#घोषणा NFC_REG_CFG		0x04
#घोषणा NFC_REG_DADR		0x08
#घोषणा NFC_REG_IADR		0x0c
#घोषणा NFC_REG_BUF		0x10
#घोषणा NFC_REG_INFO		0x14
#घोषणा NFC_REG_DC		0x18
#घोषणा NFC_REG_ADR		0x1c
#घोषणा NFC_REG_DL		0x20
#घोषणा NFC_REG_DH		0x24
#घोषणा NFC_REG_CADR		0x28
#घोषणा NFC_REG_SADR		0x2c
#घोषणा NFC_REG_PINS		0x30
#घोषणा NFC_REG_VER		0x38

#घोषणा NFC_RB_IRQ_EN		BIT(21)

#घोषणा CMDRWGEN(cmd_dir, ran, bch, लघु_mode, page_size, pages)	\
	(								\
		(cmd_dir)			|			\
		((ran) << 19)			|			\
		((bch) << 14)			|			\
		((लघु_mode) << 13)		|			\
		(((page_size) & 0x7f) << 6)	|			\
		((pages) & 0x3f)					\
	)

#घोषणा GENCMDDADDRL(adl, addr)		((adl) | ((addr) & 0xffff))
#घोषणा GENCMDDADDRH(adh, addr)		((adh) | (((addr) >> 16) & 0xffff))
#घोषणा GENCMDIADDRL(ail, addr)		((ail) | ((addr) & 0xffff))
#घोषणा GENCMDIADDRH(aih, addr)		((aih) | (((addr) >> 16) & 0xffff))

#घोषणा DMA_सूची(dir)		((dir) ? NFC_CMD_N2M : NFC_CMD_M2N)

#घोषणा ECC_CHECK_RETURN_FF	(-1)

#घोषणा न_अंकD_CE0		(0xe << 10)
#घोषणा न_अंकD_CE1		(0xd << 10)

#घोषणा DMA_BUSY_TIMEOUT	0x100000
#घोषणा CMD_FIFO_EMPTY_TIMEOUT	1000

#घोषणा MAX_CE_NUM		2

/* eMMC घड़ी रेजिस्टर, misc control */
#घोषणा CLK_SELECT_न_अंकD		BIT(31)

#घोषणा NFC_CLK_CYCLE		6

/* nand flash controller delay 3 ns */
#घोषणा NFC_DEFAULT_DELAY	3000

#घोषणा ROW_ADDER(page, index)	(((page) >> (8 * (index))) & 0xff)
#घोषणा MAX_CYCLE_ADDRS		5
#घोषणा सूचीREAD			1
#घोषणा सूचीWRITE		0

#घोषणा ECC_PARITY_BCH8_512B	14
#घोषणा ECC_COMPLETE            BIT(31)
#घोषणा ECC_ERR_CNT(x)		(((x) >> 24) & GENMASK(5, 0))
#घोषणा ECC_ZERO_CNT(x)		(((x) >> 16) & GENMASK(5, 0))
#घोषणा ECC_UNCORRECTABLE	0x3f

#घोषणा PER_INFO_BYTE		8

काष्ठा meson_nfc_nand_chip अणु
	काष्ठा list_head node;
	काष्ठा nand_chip nand;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ level1_भागider;
	u32 bus_timing;
	u32 twb;
	u32 tadl;
	u32 tbers_max;

	u32 bch_mode;
	u8 *data_buf;
	__le64 *info_buf;
	u32 nsels;
	u8 sels[];
पूर्ण;

काष्ठा meson_nand_ecc अणु
	u32 bch;
	u32 strength;
पूर्ण;

काष्ठा meson_nfc_data अणु
	स्थिर काष्ठा nand_ecc_caps *ecc_caps;
पूर्ण;

काष्ठा meson_nfc_param अणु
	u32 chip_select;
	u32 rb_select;
पूर्ण;

काष्ठा nand_rw_cmd अणु
	u32 cmd0;
	u32 addrs[MAX_CYCLE_ADDRS];
	u32 cmd1;
पूर्ण;

काष्ठा nand_timing अणु
	u32 twb;
	u32 tadl;
	u32 tbers_max;
पूर्ण;

काष्ठा meson_nfc अणु
	काष्ठा nand_controller controller;
	काष्ठा clk *core_clk;
	काष्ठा clk *device_clk;
	काष्ठा clk *phase_tx;
	काष्ठा clk *phase_rx;

	अचिन्हित दीर्घ clk_rate;
	u32 bus_timing;

	काष्ठा device *dev;
	व्योम __iomem *reg_base;
	काष्ठा regmap *reg_clk;
	काष्ठा completion completion;
	काष्ठा list_head chips;
	स्थिर काष्ठा meson_nfc_data *data;
	काष्ठा meson_nfc_param param;
	काष्ठा nand_timing timing;
	जोड़ अणु
		पूर्णांक cmd[32];
		काष्ठा nand_rw_cmd rw;
	पूर्ण cmdfअगरo;

	dma_addr_t daddr;
	dma_addr_t iaddr;

	अचिन्हित दीर्घ asचिन्हित_cs;
पूर्ण;

क्रमागत अणु
	NFC_ECC_BCH8_1K		= 2,
	NFC_ECC_BCH24_1K,
	NFC_ECC_BCH30_1K,
	NFC_ECC_BCH40_1K,
	NFC_ECC_BCH50_1K,
	NFC_ECC_BCH60_1K,
पूर्ण;

#घोषणा MESON_ECC_DATA(b, s)	अणु .bch = (b),	.strength = (s)पूर्ण

अटल काष्ठा meson_nand_ecc meson_ecc[] = अणु
	MESON_ECC_DATA(NFC_ECC_BCH8_1K, 8),
	MESON_ECC_DATA(NFC_ECC_BCH24_1K, 24),
	MESON_ECC_DATA(NFC_ECC_BCH30_1K, 30),
	MESON_ECC_DATA(NFC_ECC_BCH40_1K, 40),
	MESON_ECC_DATA(NFC_ECC_BCH50_1K, 50),
	MESON_ECC_DATA(NFC_ECC_BCH60_1K, 60),
पूर्ण;

अटल पूर्णांक meson_nand_calc_ecc_bytes(पूर्णांक step_size, पूर्णांक strength)
अणु
	पूर्णांक ecc_bytes;

	अगर (step_size == 512 && strength == 8)
		वापस ECC_PARITY_BCH8_512B;

	ecc_bytes = DIV_ROUND_UP(strength * fls(step_size * 8), 8);
	ecc_bytes = ALIGN(ecc_bytes, 2);

	वापस ecc_bytes;
पूर्ण

न_अंकD_ECC_CAPS_SINGLE(meson_gxl_ecc_caps,
		     meson_nand_calc_ecc_bytes, 1024, 8, 24, 30, 40, 50, 60);
न_अंकD_ECC_CAPS_SINGLE(meson_axg_ecc_caps,
		     meson_nand_calc_ecc_bytes, 1024, 8);

अटल काष्ठा meson_nfc_nand_chip *to_meson_nand(काष्ठा nand_chip *nand)
अणु
	वापस container_of(nand, काष्ठा meson_nfc_nand_chip, nand);
पूर्ण

अटल व्योम meson_nfc_select_chip(काष्ठा nand_chip *nand, पूर्णांक chip)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	पूर्णांक ret, value;

	अगर (chip < 0 || WARN_ON_ONCE(chip >= meson_chip->nsels))
		वापस;

	nfc->param.chip_select = meson_chip->sels[chip] ? न_अंकD_CE1 : न_अंकD_CE0;
	nfc->param.rb_select = nfc->param.chip_select;
	nfc->timing.twb = meson_chip->twb;
	nfc->timing.tadl = meson_chip->tadl;
	nfc->timing.tbers_max = meson_chip->tbers_max;

	अगर (nfc->clk_rate != meson_chip->clk_rate) अणु
		ret = clk_set_rate(nfc->device_clk, meson_chip->clk_rate);
		अगर (ret) अणु
			dev_err(nfc->dev, "failed to set clock rate\n");
			वापस;
		पूर्ण
		nfc->clk_rate = meson_chip->clk_rate;
	पूर्ण
	अगर (nfc->bus_timing != meson_chip->bus_timing) अणु
		value = (NFC_CLK_CYCLE - 1) | (meson_chip->bus_timing << 5);
		ग_लिखोl(value, nfc->reg_base + NFC_REG_CFG);
		ग_लिखोl((1 << 31), nfc->reg_base + NFC_REG_CMD);
		nfc->bus_timing =  meson_chip->bus_timing;
	पूर्ण
पूर्ण

अटल व्योम meson_nfc_cmd_idle(काष्ठा meson_nfc *nfc, u32 समय)
अणु
	ग_लिखोl(nfc->param.chip_select | NFC_CMD_IDLE | (समय & 0x3ff),
	       nfc->reg_base + NFC_REG_CMD);
पूर्ण

अटल व्योम meson_nfc_cmd_seed(काष्ठा meson_nfc *nfc, u32 seed)
अणु
	ग_लिखोl(NFC_CMD_SEED | (0xc2 + (seed & 0x7fff)),
	       nfc->reg_base + NFC_REG_CMD);
पूर्ण

अटल व्योम meson_nfc_cmd_access(काष्ठा nand_chip *nand, पूर्णांक raw, bool dir,
				 पूर्णांक scrambler)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(mtd_to_nand(mtd));
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u32 bch = meson_chip->bch_mode, cmd;
	पूर्णांक len = mtd->ग_लिखोsize, pagesize, pages;

	pagesize = nand->ecc.size;

	अगर (raw) अणु
		len = mtd->ग_लिखोsize + mtd->oobsize;
		cmd = (len & GENMASK(5, 0)) | scrambler | DMA_सूची(dir);
		ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
		वापस;
	पूर्ण

	pages = len / nand->ecc.size;

	cmd = CMDRWGEN(DMA_सूची(dir), scrambler, bch,
		       NFC_CMD_SHORTMODE_DISABLE, pagesize, pages);

	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
पूर्ण

अटल व्योम meson_nfc_drain_cmd(काष्ठा meson_nfc *nfc)
अणु
	/*
	 * Insert two commands to make sure all valid commands are finished.
	 *
	 * The Nand flash controller is deचिन्हित as two stages pipleline -
	 *  a) fetch and b) excute.
	 * There might be हालs when the driver see command queue is empty,
	 * but the Nand flash controller still has two commands buffered,
	 * one is fetched पूर्णांकo NFC request queue (पढ़ोy to run), and another
	 * is actively executing. So pushing 2 "IDLE" commands guarantees that
	 * the pipeline is emptied.
	 */
	meson_nfc_cmd_idle(nfc, 0);
	meson_nfc_cmd_idle(nfc, 0);
पूर्ण

अटल पूर्णांक meson_nfc_रुको_cmd_finish(काष्ठा meson_nfc *nfc,
				     अचिन्हित पूर्णांक समयout_ms)
अणु
	u32 cmd_size = 0;
	पूर्णांक ret;

	/* रुको cmd fअगरo is empty */
	ret = पढ़ोl_relaxed_poll_समयout(nfc->reg_base + NFC_REG_CMD, cmd_size,
					 !NFC_CMD_GET_SIZE(cmd_size),
					 10, समयout_ms * 1000);
	अगर (ret)
		dev_err(nfc->dev, "wait for empty CMD FIFO time out\n");

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_रुको_dma_finish(काष्ठा meson_nfc *nfc)
अणु
	meson_nfc_drain_cmd(nfc);

	वापस meson_nfc_रुको_cmd_finish(nfc, DMA_BUSY_TIMEOUT);
पूर्ण

अटल u8 *meson_nfc_oob_ptr(काष्ठा nand_chip *nand, पूर्णांक i)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	पूर्णांक len;

	len = nand->ecc.size * (i + 1) + (nand->ecc.bytes + 2) * i;

	वापस meson_chip->data_buf + len;
पूर्ण

अटल u8 *meson_nfc_data_ptr(काष्ठा nand_chip *nand, पूर्णांक i)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	पूर्णांक len, temp;

	temp = nand->ecc.size + nand->ecc.bytes;
	len = (temp + 2) * i;

	वापस meson_chip->data_buf + len;
पूर्ण

अटल व्योम meson_nfc_get_data_oob(काष्ठा nand_chip *nand,
				   u8 *buf, u8 *oobbuf)
अणु
	पूर्णांक i, oob_len = 0;
	u8 *dsrc, *osrc;

	oob_len = nand->ecc.bytes + 2;
	क्रम (i = 0; i < nand->ecc.steps; i++) अणु
		अगर (buf) अणु
			dsrc = meson_nfc_data_ptr(nand, i);
			स_नकल(buf, dsrc, nand->ecc.size);
			buf += nand->ecc.size;
		पूर्ण
		osrc = meson_nfc_oob_ptr(nand, i);
		स_नकल(oobbuf, osrc, oob_len);
		oobbuf += oob_len;
	पूर्ण
पूर्ण

अटल व्योम meson_nfc_set_data_oob(काष्ठा nand_chip *nand,
				   स्थिर u8 *buf, u8 *oobbuf)
अणु
	पूर्णांक i, oob_len = 0;
	u8 *dsrc, *osrc;

	oob_len = nand->ecc.bytes + 2;
	क्रम (i = 0; i < nand->ecc.steps; i++) अणु
		अगर (buf) अणु
			dsrc = meson_nfc_data_ptr(nand, i);
			स_नकल(dsrc, buf, nand->ecc.size);
			buf += nand->ecc.size;
		पूर्ण
		osrc = meson_nfc_oob_ptr(nand, i);
		स_नकल(osrc, oobbuf, oob_len);
		oobbuf += oob_len;
	पूर्ण
पूर्ण

अटल पूर्णांक meson_nfc_queue_rb(काष्ठा meson_nfc *nfc, पूर्णांक समयout_ms)
अणु
	u32 cmd, cfg;
	पूर्णांक ret = 0;

	meson_nfc_cmd_idle(nfc, nfc->timing.twb);
	meson_nfc_drain_cmd(nfc);
	meson_nfc_रुको_cmd_finish(nfc, CMD_FIFO_EMPTY_TIMEOUT);

	cfg = पढ़ोl(nfc->reg_base + NFC_REG_CFG);
	cfg |= NFC_RB_IRQ_EN;
	ग_लिखोl(cfg, nfc->reg_base + NFC_REG_CFG);

	reinit_completion(&nfc->completion);

	/* use the max erase समय as the maximum घड़ी क्रम रुकोing R/B */
	cmd = NFC_CMD_RB | NFC_CMD_RB_INT
		| nfc->param.chip_select | nfc->timing.tbers_max;
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

	ret = रुको_क्रम_completion_समयout(&nfc->completion,
					  msecs_to_jअगरfies(समयout_ms));
	अगर (ret == 0)
		ret = -1;

	वापस ret;
पूर्ण

अटल व्योम meson_nfc_set_user_byte(काष्ठा nand_chip *nand, u8 *oob_buf)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__le64 *info;
	पूर्णांक i, count;

	क्रम (i = 0, count = 0; i < nand->ecc.steps; i++, count += 2) अणु
		info = &meson_chip->info_buf[i];
		*info |= oob_buf[count];
		*info |= oob_buf[count + 1] << 8;
	पूर्ण
पूर्ण

अटल व्योम meson_nfc_get_user_byte(काष्ठा nand_chip *nand, u8 *oob_buf)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__le64 *info;
	पूर्णांक i, count;

	क्रम (i = 0, count = 0; i < nand->ecc.steps; i++, count += 2) अणु
		info = &meson_chip->info_buf[i];
		oob_buf[count] = *info;
		oob_buf[count + 1] = *info >> 8;
	पूर्ण
पूर्ण

अटल पूर्णांक meson_nfc_ecc_correct(काष्ठा nand_chip *nand, u32 *bitflips,
				 u64 *correct_biपंचांगap)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__le64 *info;
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < nand->ecc.steps; i++) अणु
		info = &meson_chip->info_buf[i];
		अगर (ECC_ERR_CNT(*info) != ECC_UNCORRECTABLE) अणु
			mtd->ecc_stats.corrected += ECC_ERR_CNT(*info);
			*bitflips = max_t(u32, *bitflips, ECC_ERR_CNT(*info));
			*correct_biपंचांगap |= 1 >> i;
			जारी;
		पूर्ण
		अगर ((nand->options & न_अंकD_NEED_SCRAMBLING) &&
		    ECC_ZERO_CNT(*info) < nand->ecc.strength) अणु
			mtd->ecc_stats.corrected += ECC_ZERO_CNT(*info);
			*bitflips = max_t(u32, *bitflips,
					  ECC_ZERO_CNT(*info));
			ret = ECC_CHECK_RETURN_FF;
		पूर्ण अन्यथा अणु
			ret = -EBADMSG;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_dma_buffer_setup(काष्ठा nand_chip *nand, व्योम *databuf,
				      पूर्णांक datalen, व्योम *infobuf, पूर्णांक infolen,
				      क्रमागत dma_data_direction dir)
अणु
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	u32 cmd;
	पूर्णांक ret = 0;

	nfc->daddr = dma_map_single(nfc->dev, databuf, datalen, dir);
	ret = dma_mapping_error(nfc->dev, nfc->daddr);
	अगर (ret) अणु
		dev_err(nfc->dev, "DMA mapping error\n");
		वापस ret;
	पूर्ण
	cmd = GENCMDDADDRL(NFC_CMD_ADL, nfc->daddr);
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

	cmd = GENCMDDADDRH(NFC_CMD_ADH, nfc->daddr);
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

	अगर (infobuf) अणु
		nfc->iaddr = dma_map_single(nfc->dev, infobuf, infolen, dir);
		ret = dma_mapping_error(nfc->dev, nfc->iaddr);
		अगर (ret) अणु
			dev_err(nfc->dev, "DMA mapping error\n");
			dma_unmap_single(nfc->dev,
					 nfc->daddr, datalen, dir);
			वापस ret;
		पूर्ण
		cmd = GENCMDIADDRL(NFC_CMD_AIL, nfc->iaddr);
		ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

		cmd = GENCMDIADDRH(NFC_CMD_AIH, nfc->iaddr);
		ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम meson_nfc_dma_buffer_release(काष्ठा nand_chip *nand,
					 पूर्णांक datalen, पूर्णांक infolen,
					 क्रमागत dma_data_direction dir)
अणु
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);

	dma_unmap_single(nfc->dev, nfc->daddr, datalen, dir);
	अगर (infolen)
		dma_unmap_single(nfc->dev, nfc->iaddr, infolen, dir);
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_buf(काष्ठा nand_chip *nand, u8 *buf, पूर्णांक len)
अणु
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	पूर्णांक ret = 0;
	u32 cmd;
	u8 *info;

	info = kzalloc(PER_INFO_BYTE, GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	ret = meson_nfc_dma_buffer_setup(nand, buf, len, info,
					 PER_INFO_BYTE, DMA_FROM_DEVICE);
	अगर (ret)
		जाओ out;

	cmd = NFC_CMD_N2M | (len & GENMASK(5, 0));
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

	meson_nfc_drain_cmd(nfc);
	meson_nfc_रुको_cmd_finish(nfc, 1000);
	meson_nfc_dma_buffer_release(nand, len, PER_INFO_BYTE, DMA_FROM_DEVICE);

out:
	kमुक्त(info);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_ग_लिखो_buf(काष्ठा nand_chip *nand, u8 *buf, पूर्णांक len)
अणु
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	पूर्णांक ret = 0;
	u32 cmd;

	ret = meson_nfc_dma_buffer_setup(nand, buf, len, शून्य,
					 0, DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	cmd = NFC_CMD_M2N | (len & GENMASK(5, 0));
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);

	meson_nfc_drain_cmd(nfc);
	meson_nfc_रुको_cmd_finish(nfc, 1000);
	meson_nfc_dma_buffer_release(nand, len, 0, DMA_TO_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_rw_cmd_prepare_and_execute(काष्ठा nand_chip *nand,
						पूर्णांक page, bool in)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(nand));
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	u32 *addrs = nfc->cmdfअगरo.rw.addrs;
	u32 cs = nfc->param.chip_select;
	u32 cmd0, cmd_num, row_start;
	पूर्णांक ret = 0, i;

	cmd_num = माप(काष्ठा nand_rw_cmd) / माप(पूर्णांक);

	cmd0 = in ? न_अंकD_CMD_READ0 : न_अंकD_CMD_SEQIN;
	nfc->cmdfअगरo.rw.cmd0 = cs | NFC_CMD_CLE | cmd0;

	addrs[0] = cs | NFC_CMD_ALE | 0;
	अगर (mtd->ग_लिखोsize <= 512) अणु
		cmd_num--;
		row_start = 1;
	पूर्ण अन्यथा अणु
		addrs[1] = cs | NFC_CMD_ALE | 0;
		row_start = 2;
	पूर्ण

	addrs[row_start] = cs | NFC_CMD_ALE | ROW_ADDER(page, 0);
	addrs[row_start + 1] = cs | NFC_CMD_ALE | ROW_ADDER(page, 1);

	अगर (nand->options & न_अंकD_ROW_ADDR_3)
		addrs[row_start + 2] =
			cs | NFC_CMD_ALE | ROW_ADDER(page, 2);
	अन्यथा
		cmd_num--;

	/* subtract cmd1 */
	cmd_num--;

	क्रम (i = 0; i < cmd_num; i++)
		ग_लिखोl_relaxed(nfc->cmdfअगरo.cmd[i],
			       nfc->reg_base + NFC_REG_CMD);

	अगर (in) अणु
		nfc->cmdfअगरo.rw.cmd1 = cs | NFC_CMD_CLE | न_अंकD_CMD_READSTART;
		ग_लिखोl(nfc->cmdfअगरo.rw.cmd1, nfc->reg_base + NFC_REG_CMD);
		meson_nfc_queue_rb(nfc, PSEC_TO_MSEC(sdr->tR_max));
	पूर्ण अन्यथा अणु
		meson_nfc_cmd_idle(nfc, nfc->timing.tadl);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_ग_लिखो_page_sub(काष्ठा nand_chip *nand,
				    पूर्णांक page, पूर्णांक raw)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(nand));
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	पूर्णांक data_len, info_len;
	u32 cmd;
	पूर्णांक ret;

	meson_nfc_select_chip(nand, nand->cur_cs);

	data_len =  mtd->ग_लिखोsize + mtd->oobsize;
	info_len = nand->ecc.steps * PER_INFO_BYTE;

	ret = meson_nfc_rw_cmd_prepare_and_execute(nand, page, सूचीWRITE);
	अगर (ret)
		वापस ret;

	ret = meson_nfc_dma_buffer_setup(nand, meson_chip->data_buf,
					 data_len, meson_chip->info_buf,
					 info_len, DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	अगर (nand->options & न_अंकD_NEED_SCRAMBLING) अणु
		meson_nfc_cmd_seed(nfc, page);
		meson_nfc_cmd_access(nand, raw, सूचीWRITE,
				     NFC_CMD_SCRAMBLER_ENABLE);
	पूर्ण अन्यथा अणु
		meson_nfc_cmd_access(nand, raw, सूचीWRITE,
				     NFC_CMD_SCRAMBLER_DISABLE);
	पूर्ण

	cmd = nfc->param.chip_select | NFC_CMD_CLE | न_अंकD_CMD_PAGEPROG;
	ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
	meson_nfc_queue_rb(nfc, PSEC_TO_MSEC(sdr->tPROG_max));

	meson_nfc_dma_buffer_release(nand, data_len, info_len, DMA_TO_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_ग_लिखो_page_raw(काष्ठा nand_chip *nand, स्थिर u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	u8 *oob_buf = nand->oob_poi;

	meson_nfc_set_data_oob(nand, buf, oob_buf);

	वापस meson_nfc_ग_लिखो_page_sub(nand, page, 1);
पूर्ण

अटल पूर्णांक meson_nfc_ग_लिखो_page_hwecc(काष्ठा nand_chip *nand,
				      स्थिर u8 *buf, पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u8 *oob_buf = nand->oob_poi;

	स_नकल(meson_chip->data_buf, buf, mtd->ग_लिखोsize);
	स_रखो(meson_chip->info_buf, 0, nand->ecc.steps * PER_INFO_BYTE);
	meson_nfc_set_user_byte(nand, oob_buf);

	वापस meson_nfc_ग_लिखो_page_sub(nand, page, 0);
पूर्ण

अटल व्योम meson_nfc_check_ecc_pages_valid(काष्ठा meson_nfc *nfc,
					    काष्ठा nand_chip *nand, पूर्णांक raw)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__le64 *info;
	u32 neccpages;
	पूर्णांक ret;

	neccpages = raw ? 1 : nand->ecc.steps;
	info = &meson_chip->info_buf[neccpages - 1];
	करो अणु
		usleep_range(10, 15);
		/* info is updated by nfc dma engine*/
		smp_rmb();
		ret = *info & ECC_COMPLETE;
	पूर्ण जबतक (!ret);
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_page_sub(काष्ठा nand_chip *nand,
				   पूर्णांक page, पूर्णांक raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	पूर्णांक data_len, info_len;
	पूर्णांक ret;

	meson_nfc_select_chip(nand, nand->cur_cs);

	data_len =  mtd->ग_लिखोsize + mtd->oobsize;
	info_len = nand->ecc.steps * PER_INFO_BYTE;

	ret = meson_nfc_rw_cmd_prepare_and_execute(nand, page, सूचीREAD);
	अगर (ret)
		वापस ret;

	ret = meson_nfc_dma_buffer_setup(nand, meson_chip->data_buf,
					 data_len, meson_chip->info_buf,
					 info_len, DMA_FROM_DEVICE);
	अगर (ret)
		वापस ret;

	अगर (nand->options & न_अंकD_NEED_SCRAMBLING) अणु
		meson_nfc_cmd_seed(nfc, page);
		meson_nfc_cmd_access(nand, raw, सूचीREAD,
				     NFC_CMD_SCRAMBLER_ENABLE);
	पूर्ण अन्यथा अणु
		meson_nfc_cmd_access(nand, raw, सूचीREAD,
				     NFC_CMD_SCRAMBLER_DISABLE);
	पूर्ण

	ret = meson_nfc_रुको_dma_finish(nfc);
	meson_nfc_check_ecc_pages_valid(nfc, nand, raw);

	meson_nfc_dma_buffer_release(nand, data_len, info_len, DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_page_raw(काष्ठा nand_chip *nand, u8 *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	u8 *oob_buf = nand->oob_poi;
	पूर्णांक ret;

	ret = meson_nfc_पढ़ो_page_sub(nand, page, 1);
	अगर (ret)
		वापस ret;

	meson_nfc_get_data_oob(nand, buf, oob_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_page_hwecc(काष्ठा nand_chip *nand, u8 *buf,
				     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	u64 correct_biपंचांगap = 0;
	u32 bitflips = 0;
	u8 *oob_buf = nand->oob_poi;
	पूर्णांक ret, i;

	ret = meson_nfc_पढ़ो_page_sub(nand, page, 0);
	अगर (ret)
		वापस ret;

	meson_nfc_get_user_byte(nand, oob_buf);
	ret = meson_nfc_ecc_correct(nand, &bitflips, &correct_biपंचांगap);
	अगर (ret == ECC_CHECK_RETURN_FF) अणु
		अगर (buf)
			स_रखो(buf, 0xff, mtd->ग_लिखोsize);
		स_रखो(oob_buf, 0xff, mtd->oobsize);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		अगर ((nand->options & न_अंकD_NEED_SCRAMBLING) || !buf) अणु
			mtd->ecc_stats.failed++;
			वापस bitflips;
		पूर्ण
		ret  = meson_nfc_पढ़ो_page_raw(nand, buf, 0, page);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < nand->ecc.steps ; i++) अणु
			u8 *data = buf + i * ecc->size;
			u8 *oob = nand->oob_poi + i * (ecc->bytes + 2);

			अगर (correct_biपंचांगap & (1 << i))
				जारी;
			ret = nand_check_erased_ecc_chunk(data,	ecc->size,
							  oob, ecc->bytes + 2,
							  शून्य, 0,
							  ecc->strength);
			अगर (ret < 0) अणु
				mtd->ecc_stats.failed++;
			पूर्ण अन्यथा अणु
				mtd->ecc_stats.corrected += ret;
				bitflips =  max_t(u32, bitflips, ret);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (buf && buf != meson_chip->data_buf) अणु
		स_नकल(buf, meson_chip->data_buf, mtd->ग_लिखोsize);
	पूर्ण

	वापस bitflips;
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_oob_raw(काष्ठा nand_chip *nand, पूर्णांक page)
अणु
	वापस meson_nfc_पढ़ो_page_raw(nand, शून्य, 1, page);
पूर्ण

अटल पूर्णांक meson_nfc_पढ़ो_oob(काष्ठा nand_chip *nand, पूर्णांक page)
अणु
	वापस meson_nfc_पढ़ो_page_hwecc(nand, शून्य, 1, page);
पूर्ण

अटल bool meson_nfc_is_buffer_dma_safe(स्थिर व्योम *buffer)
अणु
	अगर (virt_addr_valid(buffer) && (!object_is_on_stack(buffer)))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम *
meson_nand_op_get_dma_safe_input_buf(स्थिर काष्ठा nand_op_instr *instr)
अणु
	अगर (WARN_ON(instr->type != न_अंकD_OP_DATA_IN_INSTR))
		वापस शून्य;

	अगर (meson_nfc_is_buffer_dma_safe(instr->ctx.data.buf.in))
		वापस instr->ctx.data.buf.in;

	वापस kzalloc(instr->ctx.data.len, GFP_KERNEL);
पूर्ण

अटल व्योम
meson_nand_op_put_dma_safe_input_buf(स्थिर काष्ठा nand_op_instr *instr,
				     व्योम *buf)
अणु
	अगर (WARN_ON(instr->type != न_अंकD_OP_DATA_IN_INSTR) ||
	    WARN_ON(!buf))
		वापस;

	अगर (buf == instr->ctx.data.buf.in)
		वापस;

	स_नकल(instr->ctx.data.buf.in, buf, instr->ctx.data.len);
	kमुक्त(buf);
पूर्ण

अटल व्योम *
meson_nand_op_get_dma_safe_output_buf(स्थिर काष्ठा nand_op_instr *instr)
अणु
	अगर (WARN_ON(instr->type != न_अंकD_OP_DATA_OUT_INSTR))
		वापस शून्य;

	अगर (meson_nfc_is_buffer_dma_safe(instr->ctx.data.buf.out))
		वापस (व्योम *)instr->ctx.data.buf.out;

	वापस kmemdup(instr->ctx.data.buf.out,
		       instr->ctx.data.len, GFP_KERNEL);
पूर्ण

अटल व्योम
meson_nand_op_put_dma_safe_output_buf(स्थिर काष्ठा nand_op_instr *instr,
				      स्थिर व्योम *buf)
अणु
	अगर (WARN_ON(instr->type != न_अंकD_OP_DATA_OUT_INSTR) ||
	    WARN_ON(!buf))
		वापस;

	अगर (buf != instr->ctx.data.buf.out)
		kमुक्त(buf);
पूर्ण

अटल पूर्णांक meson_nfc_exec_op(काष्ठा nand_chip *nand,
			     स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	व्योम *buf;
	u32 op_id, delay_idle, cmd;
	पूर्णांक i;

	अगर (check_only)
		वापस 0;

	meson_nfc_select_chip(nand, op->cs);
	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];
		delay_idle = DIV_ROUND_UP(PSEC_TO_NSEC(instr->delay_ns),
					  meson_chip->level1_भागider *
					  NFC_CLK_CYCLE);
		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			cmd = nfc->param.chip_select | NFC_CMD_CLE;
			cmd |= instr->ctx.cmd.opcode & 0xff;
			ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
			meson_nfc_cmd_idle(nfc, delay_idle);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
				cmd = nfc->param.chip_select | NFC_CMD_ALE;
				cmd |= instr->ctx.addr.addrs[i] & 0xff;
				ग_लिखोl(cmd, nfc->reg_base + NFC_REG_CMD);
			पूर्ण
			meson_nfc_cmd_idle(nfc, delay_idle);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			buf = meson_nand_op_get_dma_safe_input_buf(instr);
			अगर (!buf)
				वापस -ENOMEM;
			meson_nfc_पढ़ो_buf(nand, buf, instr->ctx.data.len);
			meson_nand_op_put_dma_safe_input_buf(instr, buf);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			buf = meson_nand_op_get_dma_safe_output_buf(instr);
			अगर (!buf)
				वापस -ENOMEM;
			meson_nfc_ग_लिखो_buf(nand, buf, instr->ctx.data.len);
			meson_nand_op_put_dma_safe_output_buf(instr, buf);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			meson_nfc_queue_rb(nfc, instr->ctx.रुकोrdy.समयout_ms);
			अगर (instr->delay_ns)
				meson_nfc_cmd_idle(nfc, delay_idle);
			अवरोध;
		पूर्ण
	पूर्ण
	meson_nfc_रुको_cmd_finish(nfc, 1000);
	वापस 0;
पूर्ण

अटल पूर्णांक meson_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);

	अगर (section >= nand->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset =  2 + (section * (2 + nand->ecc.bytes));
	oobregion->length = nand->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);

	अगर (section >= nand->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = section * (2 + nand->ecc.bytes);
	oobregion->length = 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops meson_ooblayout_ops = अणु
	.ecc = meson_ooblayout_ecc,
	.मुक्त = meson_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक meson_nfc_clk_init(काष्ठा meson_nfc *nfc)
अणु
	पूर्णांक ret;

	/* request core घड़ी */
	nfc->core_clk = devm_clk_get(nfc->dev, "core");
	अगर (IS_ERR(nfc->core_clk)) अणु
		dev_err(nfc->dev, "failed to get core clock\n");
		वापस PTR_ERR(nfc->core_clk);
	पूर्ण

	nfc->device_clk = devm_clk_get(nfc->dev, "device");
	अगर (IS_ERR(nfc->device_clk)) अणु
		dev_err(nfc->dev, "failed to get device clock\n");
		वापस PTR_ERR(nfc->device_clk);
	पूर्ण

	nfc->phase_tx = devm_clk_get(nfc->dev, "tx");
	अगर (IS_ERR(nfc->phase_tx)) अणु
		dev_err(nfc->dev, "failed to get TX clk\n");
		वापस PTR_ERR(nfc->phase_tx);
	पूर्ण

	nfc->phase_rx = devm_clk_get(nfc->dev, "rx");
	अगर (IS_ERR(nfc->phase_rx)) अणु
		dev_err(nfc->dev, "failed to get RX clk\n");
		वापस PTR_ERR(nfc->phase_rx);
	पूर्ण

	/* init SD_EMMC_CLOCK to sane शेषs w/min घड़ी rate */
	regmap_update_bits(nfc->reg_clk,
			   0, CLK_SELECT_न_अंकD, CLK_SELECT_न_अंकD);

	ret = clk_prepare_enable(nfc->core_clk);
	अगर (ret) अणु
		dev_err(nfc->dev, "failed to enable core clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(nfc->device_clk);
	अगर (ret) अणु
		dev_err(nfc->dev, "failed to enable device clock\n");
		जाओ err_device_clk;
	पूर्ण

	ret = clk_prepare_enable(nfc->phase_tx);
	अगर (ret) अणु
		dev_err(nfc->dev, "failed to enable TX clock\n");
		जाओ err_phase_tx;
	पूर्ण

	ret = clk_prepare_enable(nfc->phase_rx);
	अगर (ret) अणु
		dev_err(nfc->dev, "failed to enable RX clock\n");
		जाओ err_phase_rx;
	पूर्ण

	ret = clk_set_rate(nfc->device_clk, 24000000);
	अगर (ret)
		जाओ err_disable_rx;

	वापस 0;

err_disable_rx:
	clk_disable_unprepare(nfc->phase_rx);
err_phase_rx:
	clk_disable_unprepare(nfc->phase_tx);
err_phase_tx:
	clk_disable_unprepare(nfc->device_clk);
err_device_clk:
	clk_disable_unprepare(nfc->core_clk);
	वापस ret;
पूर्ण

अटल व्योम meson_nfc_disable_clk(काष्ठा meson_nfc *nfc)
अणु
	clk_disable_unprepare(nfc->phase_rx);
	clk_disable_unprepare(nfc->phase_tx);
	clk_disable_unprepare(nfc->device_clk);
	clk_disable_unprepare(nfc->core_clk);
पूर्ण

अटल व्योम meson_nfc_मुक्त_buffer(काष्ठा nand_chip *nand)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);

	kमुक्त(meson_chip->info_buf);
	kमुक्त(meson_chip->data_buf);
पूर्ण

अटल पूर्णांक meson_chip_buffer_init(काष्ठा nand_chip *nand)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u32 page_bytes, info_bytes, nsectors;

	nsectors = mtd->ग_लिखोsize / nand->ecc.size;

	page_bytes =  mtd->ग_लिखोsize + mtd->oobsize;
	info_bytes = nsectors * PER_INFO_BYTE;

	meson_chip->data_buf = kदो_स्मृति(page_bytes, GFP_KERNEL);
	अगर (!meson_chip->data_buf)
		वापस -ENOMEM;

	meson_chip->info_buf = kदो_स्मृति(info_bytes, GFP_KERNEL);
	अगर (!meson_chip->info_buf) अणु
		kमुक्त(meson_chip->data_buf);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक meson_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *nand, पूर्णांक csline,
			      स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 भाग, bt_min, bt_max, tbers_घड़ीs;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -ENOTSUPP;

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	भाग = DIV_ROUND_UP((timings->tRC_min / 1000), NFC_CLK_CYCLE);
	bt_min = (timings->tREA_max + NFC_DEFAULT_DELAY) / भाग;
	bt_max = (NFC_DEFAULT_DELAY + timings->tRHOH_min +
		  timings->tRC_min / 2) / भाग;

	meson_chip->twb = DIV_ROUND_UP(PSEC_TO_NSEC(timings->tWB_max),
				       भाग * NFC_CLK_CYCLE);
	meson_chip->tadl = DIV_ROUND_UP(PSEC_TO_NSEC(timings->tADL_min),
					भाग * NFC_CLK_CYCLE);
	tbers_घड़ीs = DIV_ROUND_UP_ULL(PSEC_TO_NSEC(timings->tBERS_max),
					भाग * NFC_CLK_CYCLE);
	meson_chip->tbers_max = ilog2(tbers_घड़ीs);
	अगर (!is_घातer_of_2(tbers_घड़ीs))
		meson_chip->tbers_max++;

	bt_min = DIV_ROUND_UP(bt_min, 1000);
	bt_max = DIV_ROUND_UP(bt_max, 1000);

	अगर (bt_max < bt_min)
		वापस -EINVAL;

	meson_chip->level1_भागider = भाग;
	meson_chip->clk_rate = 1000000000 / meson_chip->level1_भागider;
	meson_chip->bus_timing = (bt_min + bt_max) / 2 + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_nand_bch_mode(काष्ठा nand_chip *nand)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	पूर्णांक i;

	अगर (nand->ecc.strength > 60 || nand->ecc.strength < 8)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(meson_ecc); i++) अणु
		अगर (meson_ecc[i].strength == nand->ecc.strength) अणु
			meson_chip->bch_mode = meson_ecc[i].bch;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम meson_nand_detach_chip(काष्ठा nand_chip *nand)
अणु
	meson_nfc_मुक्त_buffer(nand);
पूर्ण

अटल पूर्णांक meson_nand_attach_chip(काष्ठा nand_chip *nand)
अणु
	काष्ठा meson_nfc *nfc = nand_get_controller_data(nand);
	काष्ठा meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	पूर्णांक nsectors = mtd->ग_लिखोsize / 1024;
	पूर्णांक ret;

	अगर (!mtd->name) अणु
		mtd->name = devm_kaप्र_लिखो(nfc->dev, GFP_KERNEL,
					   "%s:nand%d",
					   dev_name(nfc->dev),
					   meson_chip->sels[0]);
		अगर (!mtd->name)
			वापस -ENOMEM;
	पूर्ण

	अगर (nand->bbt_options & न_अंकD_BBT_USE_FLASH)
		nand->bbt_options |= न_अंकD_BBT_NO_OOB;

	nand->options |= न_अंकD_NO_SUBPAGE_WRITE;

	ret = nand_ecc_choose_conf(nand, nfc->data->ecc_caps,
				   mtd->oobsize - 2 * nsectors);
	अगर (ret) अणु
		dev_err(nfc->dev, "failed to ECC init\n");
		वापस -EINVAL;
	पूर्ण

	mtd_set_ooblayout(mtd, &meson_ooblayout_ops);

	ret = meson_nand_bch_mode(nand);
	अगर (ret)
		वापस -EINVAL;

	nand->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	nand->ecc.ग_लिखो_page_raw = meson_nfc_ग_लिखो_page_raw;
	nand->ecc.ग_लिखो_page = meson_nfc_ग_लिखो_page_hwecc;
	nand->ecc.ग_लिखो_oob_raw = nand_ग_लिखो_oob_std;
	nand->ecc.ग_लिखो_oob = nand_ग_लिखो_oob_std;

	nand->ecc.पढ़ो_page_raw = meson_nfc_पढ़ो_page_raw;
	nand->ecc.पढ़ो_page = meson_nfc_पढ़ो_page_hwecc;
	nand->ecc.पढ़ो_oob_raw = meson_nfc_पढ़ो_oob_raw;
	nand->ecc.पढ़ो_oob = meson_nfc_पढ़ो_oob;

	अगर (nand->options & न_अंकD_BUSWIDTH_16) अणु
		dev_err(nfc->dev, "16bits bus width not supported");
		वापस -EINVAL;
	पूर्ण
	ret = meson_chip_buffer_init(nand);
	अगर (ret)
		वापस -ENOMEM;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops meson_nand_controller_ops = अणु
	.attach_chip = meson_nand_attach_chip,
	.detach_chip = meson_nand_detach_chip,
	.setup_पूर्णांकerface = meson_nfc_setup_पूर्णांकerface,
	.exec_op = meson_nfc_exec_op,
पूर्ण;

अटल पूर्णांक
meson_nfc_nand_chip_init(काष्ठा device *dev,
			 काष्ठा meson_nfc *nfc, काष्ठा device_node *np)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip;
	काष्ठा nand_chip *nand;
	काष्ठा mtd_info *mtd;
	पूर्णांक ret, i;
	u32 पंचांगp, nsels;

	nsels = of_property_count_elems_of_size(np, "reg", माप(u32));
	अगर (!nsels || nsels > MAX_CE_NUM) अणु
		dev_err(dev, "invalid register property size\n");
		वापस -EINVAL;
	पूर्ण

	meson_chip = devm_kzalloc(dev, काष्ठा_size(meson_chip, sels, nsels),
				  GFP_KERNEL);
	अगर (!meson_chip)
		वापस -ENOMEM;

	meson_chip->nsels = nsels;

	क्रम (i = 0; i < nsels; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &पंचांगp);
		अगर (ret) अणु
			dev_err(dev, "could not retrieve register property: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (test_and_set_bit(पंचांगp, &nfc->asचिन्हित_cs)) अणु
			dev_err(dev, "CS %d already assigned\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	nand = &meson_chip->nand;
	nand->controller = &nfc->controller;
	nand->controller->ops = &meson_nand_controller_ops;
	nand_set_flash_node(nand, np);
	nand_set_controller_data(nand, nfc);

	nand->options |= न_अंकD_USES_DMA;
	mtd = nand_to_mtd(nand);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;

	ret = nand_scan(nand, nsels);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to register MTD device: %d\n", ret);
		nand_cleanup(nand);
		वापस ret;
	पूर्ण

	list_add_tail(&meson_chip->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_nfc_nand_chip_cleanup(काष्ठा meson_nfc *nfc)
अणु
	काष्ठा meson_nfc_nand_chip *meson_chip;
	काष्ठा mtd_info *mtd;
	पूर्णांक ret;

	जबतक (!list_empty(&nfc->chips)) अणु
		meson_chip = list_first_entry(&nfc->chips,
					      काष्ठा meson_nfc_nand_chip, node);
		mtd = nand_to_mtd(&meson_chip->nand);
		ret = mtd_device_unरेजिस्टर(mtd);
		अगर (ret)
			वापस ret;

		meson_nfc_मुक्त_buffer(&meson_chip->nand);
		nand_cleanup(&meson_chip->nand);
		list_del(&meson_chip->node);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_nfc_nand_chips_init(काष्ठा device *dev,
				     काष्ठा meson_nfc *nfc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *nand_np;
	पूर्णांक ret;

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = meson_nfc_nand_chip_init(dev, nfc, nand_np);
		अगर (ret) अणु
			meson_nfc_nand_chip_cleanup(nfc);
			of_node_put(nand_np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t meson_nfc_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा meson_nfc *nfc = id;
	u32 cfg;

	cfg = पढ़ोl(nfc->reg_base + NFC_REG_CFG);
	अगर (!(cfg & NFC_RB_IRQ_EN))
		वापस IRQ_NONE;

	cfg &= ~(NFC_RB_IRQ_EN);
	ग_लिखोl(cfg, nfc->reg_base + NFC_REG_CFG);

	complete(&nfc->completion);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा meson_nfc_data meson_gxl_data = अणु
	.ecc_caps = &meson_gxl_ecc_caps,
पूर्ण;

अटल स्थिर काष्ठा meson_nfc_data meson_axg_data = अणु
	.ecc_caps = &meson_axg_ecc_caps,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_nfc_id_table[] = अणु
	अणु
		.compatible = "amlogic,meson-gxl-nfc",
		.data = &meson_gxl_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-axg-nfc",
		.data = &meson_axg_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_nfc_id_table);

अटल पूर्णांक meson_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_nfc *nfc;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	nfc = devm_kzalloc(dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->data = of_device_get_match_data(&pdev->dev);
	अगर (!nfc->data)
		वापस -ENODEV;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);
	init_completion(&nfc->completion);

	nfc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nfc->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(nfc->reg_base))
		वापस PTR_ERR(nfc->reg_base);

	nfc->reg_clk =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"amlogic,mmc-syscon");
	अगर (IS_ERR(nfc->reg_clk)) अणु
		dev_err(dev, "Failed to lookup clock base\n");
		वापस PTR_ERR(nfc->reg_clk);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	ret = meson_nfc_clk_init(nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize NAND clock\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(0, nfc->reg_base + NFC_REG_CFG);
	ret = devm_request_irq(dev, irq, meson_nfc_irq, 0, dev_name(dev), nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to request NFC IRQ\n");
		ret = -EINVAL;
		जाओ err_clk;
	पूर्ण

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "failed to set DMA mask\n");
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, nfc);

	ret = meson_nfc_nand_chips_init(dev, nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to init NAND chips\n");
		जाओ err_clk;
	पूर्ण

	वापस 0;
err_clk:
	meson_nfc_disable_clk(nfc);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_nfc *nfc = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = meson_nfc_nand_chip_cleanup(nfc);
	अगर (ret)
		वापस ret;

	meson_nfc_disable_clk(nfc);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver meson_nfc_driver = अणु
	.probe  = meson_nfc_probe,
	.हटाओ = meson_nfc_हटाओ,
	.driver = अणु
		.name  = "meson-nand",
		.of_match_table = meson_nfc_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_nfc_driver);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Liang Yang <liang.yang@amlogic.com>");
MODULE_DESCRIPTION("Amlogic's Meson NAND Flash Controller driver");
