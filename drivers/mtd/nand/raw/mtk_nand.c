<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * MTK न_अंकD Flash controller driver.
 * Copyright (C) 2016 MediaTek Inc.
 * Authors:	Xiaolei Li		<xiaolei.li@mediatek.com>
 *		Jorge Ramirez-Ortiz	<jorge.ramirez-ortiz@linaro.org>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश "mtk_ecc.h"

/* न_अंकD controller रेजिस्टर definition */
#घोषणा NFI_CNFG		(0x00)
#घोषणा		CNFG_AHB		BIT(0)
#घोषणा		CNFG_READ_EN		BIT(1)
#घोषणा		CNFG_DMA_BURST_EN	BIT(2)
#घोषणा		CNFG_BYTE_RW		BIT(6)
#घोषणा		CNFG_HW_ECC_EN		BIT(8)
#घोषणा		CNFG_AUTO_FMT_EN	BIT(9)
#घोषणा		CNFG_OP_CUST		(6 << 12)
#घोषणा NFI_PAGEFMT		(0x04)
#घोषणा		PAGEFMT_FDM_ECC_SHIFT	(12)
#घोषणा		PAGEFMT_FDM_SHIFT	(8)
#घोषणा		PAGEFMT_SEC_SEL_512	BIT(2)
#घोषणा		PAGEFMT_512_2K		(0)
#घोषणा		PAGEFMT_2K_4K		(1)
#घोषणा		PAGEFMT_4K_8K		(2)
#घोषणा		PAGEFMT_8K_16K		(3)
/* NFI control */
#घोषणा NFI_CON			(0x08)
#घोषणा		CON_FIFO_FLUSH		BIT(0)
#घोषणा		CON_NFI_RST		BIT(1)
#घोषणा		CON_BRD			BIT(8)  /* burst  पढ़ो */
#घोषणा		CON_BWR			BIT(9)	/* burst  ग_लिखो */
#घोषणा		CON_SEC_SHIFT		(12)
/* Timming control रेजिस्टर */
#घोषणा NFI_ACCCON		(0x0C)
#घोषणा NFI_INTR_EN		(0x10)
#घोषणा		INTR_AHB_DONE_EN	BIT(6)
#घोषणा NFI_INTR_STA		(0x14)
#घोषणा NFI_CMD			(0x20)
#घोषणा NFI_ADDRNOB		(0x30)
#घोषणा NFI_COLADDR		(0x34)
#घोषणा NFI_ROWADDR		(0x38)
#घोषणा NFI_STRDATA		(0x40)
#घोषणा		STAR_EN			(1)
#घोषणा		STAR_DE			(0)
#घोषणा NFI_CNRNB		(0x44)
#घोषणा NFI_DATAW		(0x50)
#घोषणा NFI_DATAR		(0x54)
#घोषणा NFI_PIO_सूचीDY		(0x58)
#घोषणा		PIO_DI_RDY		(0x01)
#घोषणा NFI_STA			(0x60)
#घोषणा		STA_CMD			BIT(0)
#घोषणा		STA_ADDR		BIT(1)
#घोषणा		STA_BUSY		BIT(8)
#घोषणा		STA_EMP_PAGE		BIT(12)
#घोषणा		NFI_FSM_CUSTDATA	(0xe << 16)
#घोषणा		NFI_FSM_MASK		(0xf << 16)
#घोषणा NFI_ADDRCNTR		(0x70)
#घोषणा		CNTR_MASK		GENMASK(16, 12)
#घोषणा		ADDRCNTR_SEC_SHIFT	(12)
#घोषणा		ADDRCNTR_SEC(val) \
		(((val) & CNTR_MASK) >> ADDRCNTR_SEC_SHIFT)
#घोषणा NFI_STRADDR		(0x80)
#घोषणा NFI_BYTELEN		(0x84)
#घोषणा NFI_CSEL		(0x90)
#घोषणा NFI_FDML(x)		(0xA0 + (x) * माप(u32) * 2)
#घोषणा NFI_FDMM(x)		(0xA4 + (x) * माप(u32) * 2)
#घोषणा NFI_FDM_MAX_SIZE	(8)
#घोषणा NFI_FDM_MIN_SIZE	(1)
#घोषणा NFI_DEBUG_CON1		(0x220)
#घोषणा		STROBE_MASK		GENMASK(4, 3)
#घोषणा		STROBE_SHIFT		(3)
#घोषणा		MAX_STROBE_DLY		(3)
#घोषणा NFI_MASTER_STA		(0x224)
#घोषणा		MASTER_STA_MASK		(0x0FFF)
#घोषणा NFI_EMPTY_THRESH	(0x23C)

#घोषणा MTK_NAME		"mtk-nand"
#घोषणा KB(x)			((x) * 1024UL)
#घोषणा MB(x)			(KB(x) * 1024UL)

#घोषणा MTK_TIMEOUT		(500000)
#घोषणा MTK_RESET_TIMEOUT	(1000000)
#घोषणा MTK_न_अंकD_MAX_NSELS	(2)
#घोषणा MTK_NFC_MIN_SPARE	(16)
#घोषणा ACCTIMING(tpoecs, tprecs, tc2r, tw2r, twh, twst, trlt) \
	((tpoecs) << 28 | (tprecs) << 22 | (tc2r) << 16 | \
	(tw2r) << 12 | (twh) << 8 | (twst) << 4 | (trlt))

काष्ठा mtk_nfc_caps अणु
	स्थिर u8 *spare_size;
	u8 num_spare_size;
	u8 pageक्रमmat_spare_shअगरt;
	u8 nfi_clk_भाग;
	u8 max_sector;
	u32 max_sector_size;
पूर्ण;

काष्ठा mtk_nfc_bad_mark_ctl अणु
	व्योम (*bm_swap)(काष्ठा mtd_info *, u8 *buf, पूर्णांक raw);
	u32 sec;
	u32 pos;
पूर्ण;

/*
 * FDM: region used to store मुक्त OOB data
 */
काष्ठा mtk_nfc_fdm अणु
	u32 reg_size;
	u32 ecc_size;
पूर्ण;

काष्ठा mtk_nfc_nand_chip अणु
	काष्ठा list_head node;
	काष्ठा nand_chip nand;

	काष्ठा mtk_nfc_bad_mark_ctl bad_mark;
	काष्ठा mtk_nfc_fdm fdm;
	u32 spare_per_sector;

	पूर्णांक nsels;
	u8 sels[];
	/* nothing after this field */
पूर्ण;

काष्ठा mtk_nfc_clk अणु
	काष्ठा clk *nfi_clk;
	काष्ठा clk *pad_clk;
पूर्ण;

काष्ठा mtk_nfc अणु
	काष्ठा nand_controller controller;
	काष्ठा mtk_ecc_config ecc_cfg;
	काष्ठा mtk_nfc_clk clk;
	काष्ठा mtk_ecc *ecc;

	काष्ठा device *dev;
	स्थिर काष्ठा mtk_nfc_caps *caps;
	व्योम __iomem *regs;

	काष्ठा completion करोne;
	काष्ठा list_head chips;

	u8 *buffer;

	अचिन्हित दीर्घ asचिन्हित_cs;
पूर्ण;

/*
 * supported spare size of each IP.
 * order should be the same with the spare size bitfiled defination of
 * रेजिस्टर NFI_PAGEFMT.
 */
अटल स्थिर u8 spare_size_mt2701[] = अणु
	16, 26, 27, 28, 32, 36, 40, 44,	48, 49, 50, 51, 52, 62, 63, 64
पूर्ण;

अटल स्थिर u8 spare_size_mt2712[] = अणु
	16, 26, 27, 28, 32, 36, 40, 44, 48, 49, 50, 51, 52, 62, 61, 63, 64, 67,
	74
पूर्ण;

अटल स्थिर u8 spare_size_mt7622[] = अणु
	16, 26, 27, 28
पूर्ण;

अटल अंतरभूत काष्ठा mtk_nfc_nand_chip *to_mtk_nand(काष्ठा nand_chip *nand)
अणु
	वापस container_of(nand, काष्ठा mtk_nfc_nand_chip, nand);
पूर्ण

अटल अंतरभूत u8 *data_ptr(काष्ठा nand_chip *chip, स्थिर u8 *p, पूर्णांक i)
अणु
	वापस (u8 *)p + i * chip->ecc.size;
पूर्ण

अटल अंतरभूत u8 *oob_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u8 *poi;

	/* map the sector's FDM data to मुक्त oob:
	 * the beginning of the oob area stores the FDM data of bad mark sectors
	 */

	अगर (i < mtk_nand->bad_mark.sec)
		poi = chip->oob_poi + (i + 1) * mtk_nand->fdm.reg_size;
	अन्यथा अगर (i == mtk_nand->bad_mark.sec)
		poi = chip->oob_poi;
	अन्यथा
		poi = chip->oob_poi + i * mtk_nand->fdm.reg_size;

	वापस poi;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_data_len(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);

	वापस chip->ecc.size + mtk_nand->spare_per_sector;
पूर्ण

अटल अंतरभूत u8 *mtk_data_ptr(काष्ठा nand_chip *chip,  पूर्णांक i)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);

	वापस nfc->buffer + i * mtk_data_len(chip);
पूर्ण

अटल अंतरभूत u8 *mtk_oob_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);

	वापस nfc->buffer + i * mtk_data_len(chip) + chip->ecc.size;
पूर्ण

अटल अंतरभूत व्योम nfi_ग_लिखोl(काष्ठा mtk_nfc *nfc, u32 val, u32 reg)
अणु
	ग_लिखोl(val, nfc->regs + reg);
पूर्ण

अटल अंतरभूत व्योम nfi_ग_लिखोw(काष्ठा mtk_nfc *nfc, u16 val, u32 reg)
अणु
	ग_लिखोw(val, nfc->regs + reg);
पूर्ण

अटल अंतरभूत व्योम nfi_ग_लिखोb(काष्ठा mtk_nfc *nfc, u8 val, u32 reg)
अणु
	ग_लिखोb(val, nfc->regs + reg);
पूर्ण

अटल अंतरभूत u32 nfi_पढ़ोl(काष्ठा mtk_nfc *nfc, u32 reg)
अणु
	वापस पढ़ोl_relaxed(nfc->regs + reg);
पूर्ण

अटल अंतरभूत u16 nfi_पढ़ोw(काष्ठा mtk_nfc *nfc, u32 reg)
अणु
	वापस पढ़ोw_relaxed(nfc->regs + reg);
पूर्ण

अटल अंतरभूत u8 nfi_पढ़ोb(काष्ठा mtk_nfc *nfc, u32 reg)
अणु
	वापस पढ़ोb_relaxed(nfc->regs + reg);
पूर्ण

अटल व्योम mtk_nfc_hw_reset(काष्ठा mtk_nfc *nfc)
अणु
	काष्ठा device *dev = nfc->dev;
	u32 val;
	पूर्णांक ret;

	/* reset all रेजिस्टरs and क्रमce the NFI master to terminate */
	nfi_ग_लिखोl(nfc, CON_FIFO_FLUSH | CON_NFI_RST, NFI_CON);

	/* रुको क्रम the master to finish the last transaction */
	ret = पढ़ोl_poll_समयout(nfc->regs + NFI_MASTER_STA, val,
				 !(val & MASTER_STA_MASK), 50,
				 MTK_RESET_TIMEOUT);
	अगर (ret)
		dev_warn(dev, "master active in reset [0x%x] = 0x%x\n",
			 NFI_MASTER_STA, val);

	/* ensure any status रेजिस्टर affected by the NFI master is reset */
	nfi_ग_लिखोl(nfc, CON_FIFO_FLUSH | CON_NFI_RST, NFI_CON);
	nfi_ग_लिखोw(nfc, STAR_DE, NFI_STRDATA);
पूर्ण

अटल पूर्णांक mtk_nfc_send_command(काष्ठा mtk_nfc *nfc, u8 command)
अणु
	काष्ठा device *dev = nfc->dev;
	u32 val;
	पूर्णांक ret;

	nfi_ग_लिखोl(nfc, command, NFI_CMD);

	ret = पढ़ोl_poll_समयout_atomic(nfc->regs + NFI_STA, val,
					!(val & STA_CMD), 10,  MTK_TIMEOUT);
	अगर (ret) अणु
		dev_warn(dev, "nfi core timed out entering command mode\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_send_address(काष्ठा mtk_nfc *nfc, पूर्णांक addr)
अणु
	काष्ठा device *dev = nfc->dev;
	u32 val;
	पूर्णांक ret;

	nfi_ग_लिखोl(nfc, addr, NFI_COLADDR);
	nfi_ग_लिखोl(nfc, 0, NFI_ROWADDR);
	nfi_ग_लिखोw(nfc, 1, NFI_ADDRNOB);

	ret = पढ़ोl_poll_समयout_atomic(nfc->regs + NFI_STA, val,
					!(val & STA_ADDR), 10, MTK_TIMEOUT);
	अगर (ret) अणु
		dev_warn(dev, "nfi core timed out entering address mode\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_hw_runसमय_config(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	u32 fmt, spare, i;

	अगर (!mtd->ग_लिखोsize)
		वापस 0;

	spare = mtk_nand->spare_per_sector;

	चयन (mtd->ग_लिखोsize) अणु
	हाल 512:
		fmt = PAGEFMT_512_2K | PAGEFMT_SEC_SEL_512;
		अवरोध;
	हाल KB(2):
		अगर (chip->ecc.size == 512)
			fmt = PAGEFMT_2K_4K | PAGEFMT_SEC_SEL_512;
		अन्यथा
			fmt = PAGEFMT_512_2K;
		अवरोध;
	हाल KB(4):
		अगर (chip->ecc.size == 512)
			fmt = PAGEFMT_4K_8K | PAGEFMT_SEC_SEL_512;
		अन्यथा
			fmt = PAGEFMT_2K_4K;
		अवरोध;
	हाल KB(8):
		अगर (chip->ecc.size == 512)
			fmt = PAGEFMT_8K_16K | PAGEFMT_SEC_SEL_512;
		अन्यथा
			fmt = PAGEFMT_4K_8K;
		अवरोध;
	हाल KB(16):
		fmt = PAGEFMT_8K_16K;
		अवरोध;
	शेष:
		dev_err(nfc->dev, "invalid page len: %d\n", mtd->ग_लिखोsize);
		वापस -EINVAL;
	पूर्ण

	/*
	 * the hardware will द्विगुन the value क्रम this eccsize, so we need to
	 * halve it
	 */
	अगर (chip->ecc.size == 1024)
		spare >>= 1;

	क्रम (i = 0; i < nfc->caps->num_spare_size; i++) अणु
		अगर (nfc->caps->spare_size[i] == spare)
			अवरोध;
	पूर्ण

	अगर (i == nfc->caps->num_spare_size) अणु
		dev_err(nfc->dev, "invalid spare size %d\n", spare);
		वापस -EINVAL;
	पूर्ण

	fmt |= i << nfc->caps->pageक्रमmat_spare_shअगरt;

	fmt |= mtk_nand->fdm.reg_size << PAGEFMT_FDM_SHIFT;
	fmt |= mtk_nand->fdm.ecc_size << PAGEFMT_FDM_ECC_SHIFT;
	nfi_ग_लिखोl(nfc, fmt, NFI_PAGEFMT);

	nfc->ecc_cfg.strength = chip->ecc.strength;
	nfc->ecc_cfg.len = chip->ecc.size + mtk_nand->fdm.ecc_size;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mtk_nfc_रुको_ioपढ़ोy(काष्ठा mtk_nfc *nfc)
अणु
	पूर्णांक rc;
	u8 val;

	rc = पढ़ोb_poll_समयout_atomic(nfc->regs + NFI_PIO_सूचीDY, val,
				       val & PIO_DI_RDY, 10, MTK_TIMEOUT);
	अगर (rc < 0)
		dev_err(nfc->dev, "data not ready\n");
पूर्ण

अटल अंतरभूत u8 mtk_nfc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	u32 reg;

	/* after each byte पढ़ो, the NFI_STA reg is reset by the hardware */
	reg = nfi_पढ़ोl(nfc, NFI_STA) & NFI_FSM_MASK;
	अगर (reg != NFI_FSM_CUSTDATA) अणु
		reg = nfi_पढ़ोw(nfc, NFI_CNFG);
		reg |= CNFG_BYTE_RW | CNFG_READ_EN;
		nfi_ग_लिखोw(nfc, reg, NFI_CNFG);

		/*
		 * set to max sector to allow the HW to जारी पढ़ोing over
		 * unaligned accesses
		 */
		reg = (nfc->caps->max_sector << CON_SEC_SHIFT) | CON_BRD;
		nfi_ग_लिखोl(nfc, reg, NFI_CON);

		/* trigger to fetch data */
		nfi_ग_लिखोw(nfc, STAR_EN, NFI_STRDATA);
	पूर्ण

	mtk_nfc_रुको_ioपढ़ोy(nfc);

	वापस nfi_पढ़ोb(nfc, NFI_DATAR);
पूर्ण

अटल व्योम mtk_nfc_पढ़ो_buf(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		buf[i] = mtk_nfc_पढ़ो_byte(chip);
पूर्ण

अटल व्योम mtk_nfc_ग_लिखो_byte(काष्ठा nand_chip *chip, u8 byte)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	u32 reg;

	reg = nfi_पढ़ोl(nfc, NFI_STA) & NFI_FSM_MASK;

	अगर (reg != NFI_FSM_CUSTDATA) अणु
		reg = nfi_पढ़ोw(nfc, NFI_CNFG) | CNFG_BYTE_RW;
		nfi_ग_लिखोw(nfc, reg, NFI_CNFG);

		reg = nfc->caps->max_sector << CON_SEC_SHIFT | CON_BWR;
		nfi_ग_लिखोl(nfc, reg, NFI_CON);

		nfi_ग_लिखोw(nfc, STAR_EN, NFI_STRDATA);
	पूर्ण

	mtk_nfc_रुको_ioपढ़ोy(nfc);
	nfi_ग_लिखोb(nfc, byte, NFI_DATAW);
पूर्ण

अटल व्योम mtk_nfc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		mtk_nfc_ग_लिखो_byte(chip, buf[i]);
पूर्ण

अटल पूर्णांक mtk_nfc_exec_instr(काष्ठा nand_chip *chip,
			      स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक i;
	u32 status;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		mtk_nfc_send_command(nfc, instr->ctx.cmd.opcode);
		वापस 0;
	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
			mtk_nfc_send_address(nfc, instr->ctx.addr.addrs[i]);
		वापस 0;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		mtk_nfc_पढ़ो_buf(chip, instr->ctx.data.buf.in,
				 instr->ctx.data.len);
		वापस 0;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		mtk_nfc_ग_लिखो_buf(chip, instr->ctx.data.buf.out,
				  instr->ctx.data.len);
		वापस 0;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		वापस पढ़ोl_poll_समयout(nfc->regs + NFI_STA, status,
					  !(status & STA_BUSY), 20,
					  instr->ctx.रुकोrdy.समयout_ms * 1000);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम mtk_nfc_select_target(काष्ठा nand_chip *nand, अचिन्हित पूर्णांक cs)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(nand);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(nand);

	mtk_nfc_hw_runसमय_config(nand_to_mtd(nand));

	nfi_ग_लिखोl(nfc, mtk_nand->sels[cs], NFI_CSEL);
पूर्ण

अटल पूर्णांक mtk_nfc_exec_op(काष्ठा nand_chip *chip,
			   स्थिर काष्ठा nand_operation *op,
			   bool check_only)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (check_only)
		वापस 0;

	mtk_nfc_hw_reset(nfc);
	nfi_ग_लिखोw(nfc, CNFG_OP_CUST, NFI_CNFG);
	mtk_nfc_select_target(chip, op->cs);

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = mtk_nfc_exec_instr(chip, &op->instrs[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक csline,
				   स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 rate, tpoecs, tprecs, tc2r, tw2r, twh, twst = 0, trlt = 0;
	u32 temp, tsel = 0;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -ENOTSUPP;

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	rate = clk_get_rate(nfc->clk.nfi_clk);
	/* There is a frequency भागider in some IPs */
	rate /= nfc->caps->nfi_clk_भाग;

	/* turn घड़ी rate पूर्णांकo KHZ */
	rate /= 1000;

	tpoecs = max(timings->tALH_min, timings->tCLH_min) / 1000;
	tpoecs = DIV_ROUND_UP(tpoecs * rate, 1000000);
	tpoecs &= 0xf;

	tprecs = max(timings->tCLS_min, timings->tALS_min) / 1000;
	tprecs = DIV_ROUND_UP(tprecs * rate, 1000000);
	tprecs &= 0x3f;

	/* sdr पूर्णांकerface has no tCR which means CE# low to RE# low */
	tc2r = 0;

	tw2r = timings->tWHR_min / 1000;
	tw2r = DIV_ROUND_UP(tw2r * rate, 1000000);
	tw2r = DIV_ROUND_UP(tw2r - 1, 2);
	tw2r &= 0xf;

	twh = max(timings->tREH_min, timings->tWH_min) / 1000;
	twh = DIV_ROUND_UP(twh * rate, 1000000) - 1;
	twh &= 0xf;

	/* Calculate real WE#/RE# hold समय in nanosecond */
	temp = (twh + 1) * 1000000 / rate;
	/* nanosecond to picosecond */
	temp *= 1000;

	/*
	 * WE# low level समय should be expaned to meet WE# pulse समय
	 * and WE# cycle समय at the same समय.
	 */
	अगर (temp < timings->tWC_min)
		twst = timings->tWC_min - temp;
	twst = max(timings->tWP_min, twst) / 1000;
	twst = DIV_ROUND_UP(twst * rate, 1000000) - 1;
	twst &= 0xf;

	/*
	 * RE# low level समय should be expaned to meet RE# pulse समय
	 * and RE# cycle समय at the same समय.
	 */
	अगर (temp < timings->tRC_min)
		trlt = timings->tRC_min - temp;
	trlt = max(trlt, timings->tRP_min) / 1000;
	trlt = DIV_ROUND_UP(trlt * rate, 1000000) - 1;
	trlt &= 0xf;

	/* Calculate RE# pulse समय in nanosecond. */
	temp = (trlt + 1) * 1000000 / rate;
	/* nanosecond to picosecond */
	temp *= 1000;
	/*
	 * If RE# access समय is bigger than RE# pulse समय,
	 * delay sampling data timing.
	 */
	अगर (temp < timings->tREA_max) अणु
		tsel = timings->tREA_max / 1000;
		tsel = DIV_ROUND_UP(tsel * rate, 1000000);
		tsel -= (trlt + 1);
		अगर (tsel > MAX_STROBE_DLY) अणु
			trlt += tsel - MAX_STROBE_DLY;
			tsel = MAX_STROBE_DLY;
		पूर्ण
	पूर्ण
	temp = nfi_पढ़ोl(nfc, NFI_DEBUG_CON1);
	temp &= ~STROBE_MASK;
	temp |= tsel << STROBE_SHIFT;
	nfi_ग_लिखोl(nfc, temp, NFI_DEBUG_CON1);

	/*
	 * ACCON: access timing control रेजिस्टर
	 * -------------------------------------
	 * 31:28: tpoecs, minimum required समय क्रम CS post pulling करोwn after
	 *        accessing the device
	 * 27:22: tprecs, minimum required समय क्रम CS pre pulling करोwn beक्रमe
	 *        accessing the device
	 * 21:16: tc2r, minimum required समय from NCEB low to NREB low
	 * 15:12: tw2r, minimum required समय from NWEB high to NREB low.
	 * 11:08: twh, ग_लिखो enable hold समय
	 * 07:04: twst, ग_लिखो रुको states
	 * 03:00: trlt, पढ़ो रुको states
	 */
	trlt = ACCTIMING(tpoecs, tprecs, tc2r, tw2r, twh, twst, trlt);
	nfi_ग_लिखोl(nfc, trlt, NFI_ACCCON);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_sector_encode(काष्ठा nand_chip *chip, u8 *data)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	पूर्णांक size = chip->ecc.size + mtk_nand->fdm.reg_size;

	nfc->ecc_cfg.mode = ECC_DMA_MODE;
	nfc->ecc_cfg.op = ECC_ENCODE;

	वापस mtk_ecc_encode(nfc->ecc, &nfc->ecc_cfg, data, size);
पूर्ण

अटल व्योम mtk_nfc_no_bad_mark_swap(काष्ठा mtd_info *a, u8 *b, पूर्णांक c)
अणु
	/* nop */
पूर्ण

अटल व्योम mtk_nfc_bad_mark_swap(काष्ठा mtd_info *mtd, u8 *buf, पूर्णांक raw)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *nand = to_mtk_nand(chip);
	u32 bad_pos = nand->bad_mark.pos;

	अगर (raw)
		bad_pos += nand->bad_mark.sec * mtk_data_len(chip);
	अन्यथा
		bad_pos += nand->bad_mark.sec * chip->ecc.size;

	swap(chip->oob_poi[0], buf[bad_pos]);
पूर्ण

अटल पूर्णांक mtk_nfc_क्रमmat_subpage(काष्ठा mtd_info *mtd, u32 offset,
				  u32 len, स्थिर u8 *buf)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 start, end;
	पूर्णांक i, ret;

	start = offset / chip->ecc.size;
	end = DIV_ROUND_UP(offset + len, chip->ecc.size);

	स_रखो(nfc->buffer, 0xff, mtd->ग_लिखोsize + mtd->oobsize);
	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		स_नकल(mtk_data_ptr(chip, i), data_ptr(chip, buf, i),
		       chip->ecc.size);

		अगर (start > i || i >= end)
			जारी;

		अगर (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		स_नकल(mtk_oob_ptr(chip, i), oob_ptr(chip, i), fdm->reg_size);

		/* program the CRC back to the OOB */
		ret = mtk_nfc_sector_encode(chip, mtk_data_ptr(chip, i));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_nfc_क्रमmat_page(काष्ठा mtd_info *mtd, स्थिर u8 *buf)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 i;

	स_रखो(nfc->buffer, 0xff, mtd->ग_लिखोsize + mtd->oobsize);
	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		अगर (buf)
			स_नकल(mtk_data_ptr(chip, i), data_ptr(chip, buf, i),
			       chip->ecc.size);

		अगर (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		स_नकल(mtk_oob_ptr(chip, i), oob_ptr(chip, i), fdm->reg_size);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mtk_nfc_पढ़ो_fdm(काष्ठा nand_chip *chip, u32 start,
				    u32 sectors)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vall, valm;
	u8 *oobptr;
	पूर्णांक i, j;

	क्रम (i = 0; i < sectors; i++) अणु
		oobptr = oob_ptr(chip, start + i);
		vall = nfi_पढ़ोl(nfc, NFI_FDML(i));
		valm = nfi_पढ़ोl(nfc, NFI_FDMM(i));

		क्रम (j = 0; j < fdm->reg_size; j++)
			oobptr[j] = (j >= 4 ? valm : vall) >> ((j % 4) * 8);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mtk_nfc_ग_लिखो_fdm(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vall, valm;
	u8 *oobptr;
	पूर्णांक i, j;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		oobptr = oob_ptr(chip, i);
		vall = 0;
		valm = 0;
		क्रम (j = 0; j < 8; j++) अणु
			अगर (j < 4)
				vall |= (j < fdm->reg_size ? oobptr[j] : 0xff)
						<< (j * 8);
			अन्यथा
				valm |= (j < fdm->reg_size ? oobptr[j] : 0xff)
						<< ((j - 4) * 8);
		पूर्ण
		nfi_ग_लिखोl(nfc, vall, NFI_FDML(i));
		nfi_ग_लिखोl(nfc, valm, NFI_FDMM(i));
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_nfc_करो_ग_लिखो_page(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
				 स्थिर u8 *buf, पूर्णांक page, पूर्णांक len)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा device *dev = nfc->dev;
	dma_addr_t addr;
	u32 reg;
	पूर्णांक ret;

	addr = dma_map_single(dev, (व्योम *)buf, len, DMA_TO_DEVICE);
	ret = dma_mapping_error(nfc->dev, addr);
	अगर (ret) अणु
		dev_err(nfc->dev, "dma mapping error\n");
		वापस -EINVAL;
	पूर्ण

	reg = nfi_पढ़ोw(nfc, NFI_CNFG) | CNFG_AHB | CNFG_DMA_BURST_EN;
	nfi_ग_लिखोw(nfc, reg, NFI_CNFG);

	nfi_ग_लिखोl(nfc, chip->ecc.steps << CON_SEC_SHIFT, NFI_CON);
	nfi_ग_लिखोl(nfc, lower_32_bits(addr), NFI_STRADDR);
	nfi_ग_लिखोw(nfc, INTR_AHB_DONE_EN, NFI_INTR_EN);

	init_completion(&nfc->करोne);

	reg = nfi_पढ़ोl(nfc, NFI_CON) | CON_BWR;
	nfi_ग_लिखोl(nfc, reg, NFI_CON);
	nfi_ग_लिखोw(nfc, STAR_EN, NFI_STRDATA);

	ret = रुको_क्रम_completion_समयout(&nfc->करोne, msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(dev, "program ahb done timeout\n");
		nfi_ग_लिखोw(nfc, 0, NFI_INTR_EN);
		ret = -ETIMEDOUT;
		जाओ समयout;
	पूर्ण

	ret = पढ़ोl_poll_समयout_atomic(nfc->regs + NFI_ADDRCNTR, reg,
					ADDRCNTR_SEC(reg) >= chip->ecc.steps,
					10, MTK_TIMEOUT);
	अगर (ret)
		dev_err(dev, "hwecc write timeout\n");

समयout:

	dma_unmap_single(nfc->dev, addr, len, DMA_TO_DEVICE);
	nfi_ग_लिखोl(nfc, 0, NFI_CON);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nfc_ग_लिखो_page(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
			      स्थिर u8 *buf, पूर्णांक page, पूर्णांक raw)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	माप_प्रकार len;
	स्थिर u8 *bufpoi;
	u32 reg;
	पूर्णांक ret;

	mtk_nfc_select_target(chip, chip->cur_cs);
	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	अगर (!raw) अणु
		/* OOB => FDM: from रेजिस्टर,  ECC: from HW */
		reg = nfi_पढ़ोw(nfc, NFI_CNFG) | CNFG_AUTO_FMT_EN;
		nfi_ग_लिखोw(nfc, reg | CNFG_HW_ECC_EN, NFI_CNFG);

		nfc->ecc_cfg.op = ECC_ENCODE;
		nfc->ecc_cfg.mode = ECC_NFI_MODE;
		ret = mtk_ecc_enable(nfc->ecc, &nfc->ecc_cfg);
		अगर (ret) अणु
			/* clear NFI config */
			reg = nfi_पढ़ोw(nfc, NFI_CNFG);
			reg &= ~(CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN);
			nfi_ग_लिखोw(nfc, reg, NFI_CNFG);

			वापस ret;
		पूर्ण

		स_नकल(nfc->buffer, buf, mtd->ग_लिखोsize);
		mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, raw);
		bufpoi = nfc->buffer;

		/* ग_लिखो OOB पूर्णांकo the FDM रेजिस्टरs (OOB area in MTK न_अंकD) */
		mtk_nfc_ग_लिखो_fdm(chip);
	पूर्ण अन्यथा अणु
		bufpoi = buf;
	पूर्ण

	len = mtd->ग_लिखोsize + (raw ? mtd->oobsize : 0);
	ret = mtk_nfc_करो_ग_लिखो_page(mtd, chip, bufpoi, page, len);

	अगर (!raw)
		mtk_ecc_disable(nfc->ecc);

	अगर (ret)
		वापस ret;

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक mtk_nfc_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				    पूर्णांक oob_on, पूर्णांक page)
अणु
	वापस mtk_nfc_ग_लिखो_page(nand_to_mtd(chip), chip, buf, page, 0);
पूर्ण

अटल पूर्णांक mtk_nfc_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				  पूर्णांक oob_on, पूर्णांक pg)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);

	mtk_nfc_क्रमmat_page(mtd, buf);
	वापस mtk_nfc_ग_लिखो_page(mtd, chip, nfc->buffer, pg, 1);
पूर्ण

अटल पूर्णांक mtk_nfc_ग_लिखो_subpage_hwecc(काष्ठा nand_chip *chip, u32 offset,
				       u32 data_len, स्थिर u8 *buf,
				       पूर्णांक oob_on, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	पूर्णांक ret;

	ret = mtk_nfc_क्रमmat_subpage(mtd, offset, data_len, buf);
	अगर (ret < 0)
		वापस ret;

	/* use the data in the निजी buffer (now with FDM and CRC) */
	वापस mtk_nfc_ग_लिखो_page(mtd, chip, nfc->buffer, page, 1);
पूर्ण

अटल पूर्णांक mtk_nfc_ग_लिखो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस mtk_nfc_ग_लिखो_page_raw(chip, शून्य, 1, page);
पूर्ण

अटल पूर्णांक mtk_nfc_update_ecc_stats(काष्ठा mtd_info *mtd, u8 *buf, u32 start,
				    u32 sectors)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_ecc_stats stats;
	u32 reg_size = mtk_nand->fdm.reg_size;
	पूर्णांक rc, i;

	rc = nfi_पढ़ोl(nfc, NFI_STA) & STA_EMP_PAGE;
	अगर (rc) अणु
		स_रखो(buf, 0xff, sectors * chip->ecc.size);
		क्रम (i = 0; i < sectors; i++)
			स_रखो(oob_ptr(chip, start + i), 0xff, reg_size);
		वापस 0;
	पूर्ण

	mtk_ecc_get_stats(nfc->ecc, &stats, sectors);
	mtd->ecc_stats.corrected += stats.corrected;
	mtd->ecc_stats.failed += stats.failed;

	वापस stats.bitflips;
पूर्ण

अटल पूर्णांक mtk_nfc_पढ़ो_subpage(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
				u32 data_offs, u32 पढ़ोlen,
				u8 *bufpoi, पूर्णांक page, पूर्णांक raw)
अणु
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u32 spare = mtk_nand->spare_per_sector;
	u32 column, sectors, start, end, reg;
	dma_addr_t addr;
	पूर्णांक bitflips = 0;
	माप_प्रकार len;
	u8 *buf;
	पूर्णांक rc;

	mtk_nfc_select_target(chip, chip->cur_cs);
	start = data_offs / chip->ecc.size;
	end = DIV_ROUND_UP(data_offs + पढ़ोlen, chip->ecc.size);

	sectors = end - start;
	column = start * (chip->ecc.size + spare);

	len = sectors * chip->ecc.size + (raw ? sectors * spare : 0);
	buf = bufpoi + start * chip->ecc.size;

	nand_पढ़ो_page_op(chip, page, column, शून्य, 0);

	addr = dma_map_single(nfc->dev, buf, len, DMA_FROM_DEVICE);
	rc = dma_mapping_error(nfc->dev, addr);
	अगर (rc) अणु
		dev_err(nfc->dev, "dma mapping error\n");

		वापस -EINVAL;
	पूर्ण

	reg = nfi_पढ़ोw(nfc, NFI_CNFG);
	reg |= CNFG_READ_EN | CNFG_DMA_BURST_EN | CNFG_AHB;
	अगर (!raw) अणु
		reg |= CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN;
		nfi_ग_लिखोw(nfc, reg, NFI_CNFG);

		nfc->ecc_cfg.mode = ECC_NFI_MODE;
		nfc->ecc_cfg.sectors = sectors;
		nfc->ecc_cfg.op = ECC_DECODE;
		rc = mtk_ecc_enable(nfc->ecc, &nfc->ecc_cfg);
		अगर (rc) अणु
			dev_err(nfc->dev, "ecc enable\n");
			/* clear NFI_CNFG */
			reg &= ~(CNFG_DMA_BURST_EN | CNFG_AHB | CNFG_READ_EN |
				CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN);
			nfi_ग_लिखोw(nfc, reg, NFI_CNFG);
			dma_unmap_single(nfc->dev, addr, len, DMA_FROM_DEVICE);

			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		nfi_ग_लिखोw(nfc, reg, NFI_CNFG);
	पूर्ण

	nfi_ग_लिखोl(nfc, sectors << CON_SEC_SHIFT, NFI_CON);
	nfi_ग_लिखोw(nfc, INTR_AHB_DONE_EN, NFI_INTR_EN);
	nfi_ग_लिखोl(nfc, lower_32_bits(addr), NFI_STRADDR);

	init_completion(&nfc->करोne);
	reg = nfi_पढ़ोl(nfc, NFI_CON) | CON_BRD;
	nfi_ग_लिखोl(nfc, reg, NFI_CON);
	nfi_ग_लिखोw(nfc, STAR_EN, NFI_STRDATA);

	rc = रुको_क्रम_completion_समयout(&nfc->करोne, msecs_to_jअगरfies(500));
	अगर (!rc)
		dev_warn(nfc->dev, "read ahb/dma done timeout\n");

	rc = पढ़ोl_poll_समयout_atomic(nfc->regs + NFI_BYTELEN, reg,
				       ADDRCNTR_SEC(reg) >= sectors, 10,
				       MTK_TIMEOUT);
	अगर (rc < 0) अणु
		dev_err(nfc->dev, "subpage done timeout\n");
		bitflips = -EIO;
	पूर्ण अन्यथा अगर (!raw) अणु
		rc = mtk_ecc_रुको_करोne(nfc->ecc, ECC_DECODE);
		bitflips = rc < 0 ? -ETIMEDOUT :
			mtk_nfc_update_ecc_stats(mtd, buf, start, sectors);
		mtk_nfc_पढ़ो_fdm(chip, start, sectors);
	पूर्ण

	dma_unmap_single(nfc->dev, addr, len, DMA_FROM_DEVICE);

	अगर (raw)
		जाओ करोne;

	mtk_ecc_disable(nfc->ecc);

	अगर (clamp(mtk_nand->bad_mark.sec, start, end) == mtk_nand->bad_mark.sec)
		mtk_nand->bad_mark.bm_swap(mtd, bufpoi, raw);
करोne:
	nfi_ग_लिखोl(nfc, 0, NFI_CON);

	वापस bitflips;
पूर्ण

अटल पूर्णांक mtk_nfc_पढ़ो_subpage_hwecc(काष्ठा nand_chip *chip, u32 off,
				      u32 len, u8 *p, पूर्णांक pg)
अणु
	वापस mtk_nfc_पढ़ो_subpage(nand_to_mtd(chip), chip, off, len, p, pg,
				    0);
पूर्ण

अटल पूर्णांक mtk_nfc_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, u8 *p, पूर्णांक oob_on,
				   पूर्णांक pg)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस mtk_nfc_पढ़ो_subpage(mtd, chip, 0, mtd->ग_लिखोsize, p, pg, 0);
पूर्ण

अटल पूर्णांक mtk_nfc_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक oob_on,
				 पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	पूर्णांक i, ret;

	स_रखो(nfc->buffer, 0xff, mtd->ग_लिखोsize + mtd->oobsize);
	ret = mtk_nfc_पढ़ो_subpage(mtd, chip, 0, mtd->ग_लिखोsize, nfc->buffer,
				   page, 1);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		स_नकल(oob_ptr(chip, i), mtk_oob_ptr(chip, i), fdm->reg_size);

		अगर (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		अगर (buf)
			स_नकल(data_ptr(chip, buf, i), mtk_data_ptr(chip, i),
			       chip->ecc.size);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nfc_पढ़ो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस mtk_nfc_पढ़ो_page_raw(chip, शून्य, 1, page);
पूर्ण

अटल अंतरभूत व्योम mtk_nfc_hw_init(काष्ठा mtk_nfc *nfc)
अणु
	/*
	 * CNRNB: nand पढ़ोy/busy रेजिस्टर
	 * -------------------------------
	 * 7:4: समयout रेजिस्टर क्रम polling the न_अंकD busy/पढ़ोy संकेत
	 * 0  : poll the status of the busy/पढ़ोy संकेत after [7:4]*16 cycles.
	 */
	nfi_ग_लिखोw(nfc, 0xf1, NFI_CNRNB);
	nfi_ग_लिखोl(nfc, PAGEFMT_8K_16K, NFI_PAGEFMT);

	mtk_nfc_hw_reset(nfc);

	nfi_पढ़ोl(nfc, NFI_INTR_STA);
	nfi_ग_लिखोl(nfc, 0, NFI_INTR_EN);
पूर्ण

अटल irqवापस_t mtk_nfc_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा mtk_nfc *nfc = id;
	u16 sta, ien;

	sta = nfi_पढ़ोw(nfc, NFI_INTR_STA);
	ien = nfi_पढ़ोw(nfc, NFI_INTR_EN);

	अगर (!(sta & ien))
		वापस IRQ_NONE;

	nfi_ग_लिखोw(nfc, ~sta & ien, NFI_INTR_EN);
	complete(&nfc->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_nfc_enable_clk(काष्ठा device *dev, काष्ठा mtk_nfc_clk *clk)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(clk->nfi_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable nfi clk\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(clk->pad_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable pad clk\n");
		clk_disable_unprepare(clk->nfi_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_nfc_disable_clk(काष्ठा mtk_nfc_clk *clk)
अणु
	clk_disable_unprepare(clk->nfi_clk);
	clk_disable_unprepare(clk->pad_clk);
पूर्ण

अटल पूर्णांक mtk_nfc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oob_region)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	काष्ठा mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 eccsteps;

	eccsteps = mtd->ग_लिखोsize / chip->ecc.size;

	अगर (section >= eccsteps)
		वापस -दुस्फल;

	oob_region->length = fdm->reg_size - fdm->ecc_size;
	oob_region->offset = section * fdm->reg_size + fdm->ecc_size;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oob_region)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u32 eccsteps;

	अगर (section)
		वापस -दुस्फल;

	eccsteps = mtd->ग_लिखोsize / chip->ecc.size;
	oob_region->offset = mtk_nand->fdm.reg_size * eccsteps;
	oob_region->length = mtd->oobsize - oob_region->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops mtk_nfc_ooblayout_ops = अणु
	.मुक्त = mtk_nfc_ooblayout_मुक्त,
	.ecc = mtk_nfc_ooblayout_ecc,
पूर्ण;

अटल व्योम mtk_nfc_set_fdm(काष्ठा mtk_nfc_fdm *fdm, काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	काष्ठा mtk_nfc_nand_chip *chip = to_mtk_nand(nand);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(nand);
	u32 ecc_bytes;

	ecc_bytes = DIV_ROUND_UP(nand->ecc.strength *
				 mtk_ecc_get_parity_bits(nfc->ecc), 8);

	fdm->reg_size = chip->spare_per_sector - ecc_bytes;
	अगर (fdm->reg_size > NFI_FDM_MAX_SIZE)
		fdm->reg_size = NFI_FDM_MAX_SIZE;

	/* bad block mark storage */
	fdm->ecc_size = 1;
पूर्ण

अटल व्योम mtk_nfc_set_bad_mark_ctl(काष्ठा mtk_nfc_bad_mark_ctl *bm_ctl,
				     काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);

	अगर (mtd->ग_लिखोsize == 512) अणु
		bm_ctl->bm_swap = mtk_nfc_no_bad_mark_swap;
	पूर्ण अन्यथा अणु
		bm_ctl->bm_swap = mtk_nfc_bad_mark_swap;
		bm_ctl->sec = mtd->ग_लिखोsize / mtk_data_len(nand);
		bm_ctl->pos = mtd->ग_लिखोsize % mtk_data_len(nand);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_nfc_set_spare_per_sector(u32 *sps, काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(nand);
	स्थिर u8 *spare = nfc->caps->spare_size;
	u32 eccsteps, i, बंदst_spare = 0;

	eccsteps = mtd->ग_लिखोsize / nand->ecc.size;
	*sps = mtd->oobsize / eccsteps;

	अगर (nand->ecc.size == 1024)
		*sps >>= 1;

	अगर (*sps < MTK_NFC_MIN_SPARE)
		वापस -EINVAL;

	क्रम (i = 0; i < nfc->caps->num_spare_size; i++) अणु
		अगर (*sps >= spare[i] && spare[i] >= spare[बंदst_spare]) अणु
			बंदst_spare = i;
			अगर (*sps == spare[i])
				अवरोध;
		पूर्ण
	पूर्ण

	*sps = spare[बंदst_spare];

	अगर (nand->ecc.size == 1024)
		*sps <<= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_ecc_init(काष्ठा device *dev, काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&nand->base);
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(nand);
	u32 spare;
	पूर्णांक मुक्त, ret;

	/* support only ecc hw mode */
	अगर (nand->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		dev_err(dev, "ecc.engine_type not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* अगर optional dt settings not present */
	अगर (!nand->ecc.size || !nand->ecc.strength) अणु
		/* use datasheet requirements */
		nand->ecc.strength = requirements->strength;
		nand->ecc.size = requirements->step_size;

		/*
		 * align eccstrength and eccsize
		 * this controller only supports 512 and 1024 sizes
		 */
		अगर (nand->ecc.size < 1024) अणु
			अगर (mtd->ग_लिखोsize > 512 &&
			    nfc->caps->max_sector_size > 512) अणु
				nand->ecc.size = 1024;
				nand->ecc.strength <<= 1;
			पूर्ण अन्यथा अणु
				nand->ecc.size = 512;
			पूर्ण
		पूर्ण अन्यथा अणु
			nand->ecc.size = 1024;
		पूर्ण

		ret = mtk_nfc_set_spare_per_sector(&spare, mtd);
		अगर (ret)
			वापस ret;

		/* calculate oob bytes except ecc parity data */
		मुक्त = (nand->ecc.strength * mtk_ecc_get_parity_bits(nfc->ecc)
			+ 7) >> 3;
		मुक्त = spare - मुक्त;

		/*
		 * enhance ecc strength अगर oob left is bigger than max FDM size
		 * or reduce ecc strength अगर oob size is not enough क्रम ecc
		 * parity data.
		 */
		अगर (मुक्त > NFI_FDM_MAX_SIZE) अणु
			spare -= NFI_FDM_MAX_SIZE;
			nand->ecc.strength = (spare << 3) /
					     mtk_ecc_get_parity_bits(nfc->ecc);
		पूर्ण अन्यथा अगर (मुक्त < 0) अणु
			spare -= NFI_FDM_MIN_SIZE;
			nand->ecc.strength = (spare << 3) /
					     mtk_ecc_get_parity_bits(nfc->ecc);
		पूर्ण
	पूर्ण

	mtk_ecc_adjust_strength(nfc->ecc, &nand->ecc.strength);

	dev_info(dev, "eccsize %d eccstrength %d\n",
		 nand->ecc.size, nand->ecc.strength);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा device *dev = mtd->dev.parent;
	काष्ठा mtk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	पूर्णांक len;
	पूर्णांक ret;

	अगर (chip->options & न_अंकD_BUSWIDTH_16) अणु
		dev_err(dev, "16bits buswidth not supported");
		वापस -EINVAL;
	पूर्ण

	/* store bbt magic in page, cause OOB is not रक्षित */
	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	ret = mtk_nfc_ecc_init(dev, mtd);
	अगर (ret)
		वापस ret;

	ret = mtk_nfc_set_spare_per_sector(&mtk_nand->spare_per_sector, mtd);
	अगर (ret)
		वापस ret;

	mtk_nfc_set_fdm(&mtk_nand->fdm, mtd);
	mtk_nfc_set_bad_mark_ctl(&mtk_nand->bad_mark, mtd);

	len = mtd->ग_लिखोsize + mtd->oobsize;
	nfc->buffer = devm_kzalloc(dev, len, GFP_KERNEL);
	अगर (!nfc->buffer)
		वापस  -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops mtk_nfc_controller_ops = अणु
	.attach_chip = mtk_nfc_attach_chip,
	.setup_पूर्णांकerface = mtk_nfc_setup_पूर्णांकerface,
	.exec_op = mtk_nfc_exec_op,
पूर्ण;

अटल पूर्णांक mtk_nfc_nand_chip_init(काष्ठा device *dev, काष्ठा mtk_nfc *nfc,
				  काष्ठा device_node *np)
अणु
	काष्ठा mtk_nfc_nand_chip *chip;
	काष्ठा nand_chip *nand;
	काष्ठा mtd_info *mtd;
	पूर्णांक nsels;
	u32 पंचांगp;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!of_get_property(np, "reg", &nsels))
		वापस -ENODEV;

	nsels /= माप(u32);
	अगर (!nsels || nsels > MTK_न_अंकD_MAX_NSELS) अणु
		dev_err(dev, "invalid reg property size %d\n", nsels);
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(dev, माप(*chip) + nsels * माप(u8),
			    GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->nsels = nsels;
	क्रम (i = 0; i < nsels; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &पंचांगp);
		अगर (ret) अणु
			dev_err(dev, "reg property failure : %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (पंचांगp >= MTK_न_अंकD_MAX_NSELS) अणु
			dev_err(dev, "invalid CS: %u\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण

		अगर (test_and_set_bit(पंचांगp, &nfc->asचिन्हित_cs)) अणु
			dev_err(dev, "CS %u already assigned\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण

		chip->sels[i] = पंचांगp;
	पूर्ण

	nand = &chip->nand;
	nand->controller = &nfc->controller;

	nand_set_flash_node(nand, np);
	nand_set_controller_data(nand, nfc);

	nand->options |= न_अंकD_USES_DMA | न_अंकD_SUBPAGE_READ;

	/* set शेष mode in हाल dt entry is missing */
	nand->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	nand->ecc.ग_लिखो_subpage = mtk_nfc_ग_लिखो_subpage_hwecc;
	nand->ecc.ग_लिखो_page_raw = mtk_nfc_ग_लिखो_page_raw;
	nand->ecc.ग_लिखो_page = mtk_nfc_ग_लिखो_page_hwecc;
	nand->ecc.ग_लिखो_oob_raw = mtk_nfc_ग_लिखो_oob_std;
	nand->ecc.ग_लिखो_oob = mtk_nfc_ग_लिखो_oob_std;

	nand->ecc.पढ़ो_subpage = mtk_nfc_पढ़ो_subpage_hwecc;
	nand->ecc.पढ़ो_page_raw = mtk_nfc_पढ़ो_page_raw;
	nand->ecc.पढ़ो_page = mtk_nfc_पढ़ो_page_hwecc;
	nand->ecc.पढ़ो_oob_raw = mtk_nfc_पढ़ो_oob_std;
	nand->ecc.पढ़ो_oob = mtk_nfc_पढ़ो_oob_std;

	mtd = nand_to_mtd(nand);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;
	mtd->name = MTK_NAME;
	mtd_set_ooblayout(mtd, &mtk_nfc_ooblayout_ops);

	mtk_nfc_hw_init(nfc);

	ret = nand_scan(nand, nsels);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "mtd parse partition error\n");
		nand_cleanup(nand);
		वापस ret;
	पूर्ण

	list_add_tail(&chip->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_nand_chips_init(काष्ठा device *dev, काष्ठा mtk_nfc *nfc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *nand_np;
	पूर्णांक ret;

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = mtk_nfc_nand_chip_init(dev, nfc, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_nfc_caps mtk_nfc_caps_mt2701 = अणु
	.spare_size = spare_size_mt2701,
	.num_spare_size = 16,
	.pageक्रमmat_spare_shअगरt = 4,
	.nfi_clk_भाग = 1,
	.max_sector = 16,
	.max_sector_size = 1024,
पूर्ण;

अटल स्थिर काष्ठा mtk_nfc_caps mtk_nfc_caps_mt2712 = अणु
	.spare_size = spare_size_mt2712,
	.num_spare_size = 19,
	.pageक्रमmat_spare_shअगरt = 16,
	.nfi_clk_भाग = 2,
	.max_sector = 16,
	.max_sector_size = 1024,
पूर्ण;

अटल स्थिर काष्ठा mtk_nfc_caps mtk_nfc_caps_mt7622 = अणु
	.spare_size = spare_size_mt7622,
	.num_spare_size = 4,
	.pageक्रमmat_spare_shअगरt = 4,
	.nfi_clk_भाग = 1,
	.max_sector = 8,
	.max_sector_size = 512,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_nfc_id_table[] = अणु
	अणु
		.compatible = "mediatek,mt2701-nfc",
		.data = &mtk_nfc_caps_mt2701,
	पूर्ण, अणु
		.compatible = "mediatek,mt2712-nfc",
		.data = &mtk_nfc_caps_mt2712,
	पूर्ण, अणु
		.compatible = "mediatek,mt7622-nfc",
		.data = &mtk_nfc_caps_mt7622,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_nfc_id_table);

अटल पूर्णांक mtk_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा mtk_nfc *nfc;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	nfc = devm_kzalloc(dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);
	nfc->controller.ops = &mtk_nfc_controller_ops;

	/* probe defer अगर not पढ़ोy */
	nfc->ecc = of_mtk_ecc_get(np);
	अगर (IS_ERR(nfc->ecc))
		वापस PTR_ERR(nfc->ecc);
	अन्यथा अगर (!nfc->ecc)
		वापस -ENODEV;

	nfc->caps = of_device_get_match_data(dev);
	nfc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nfc->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(nfc->regs)) अणु
		ret = PTR_ERR(nfc->regs);
		जाओ release_ecc;
	पूर्ण

	nfc->clk.nfi_clk = devm_clk_get(dev, "nfi_clk");
	अगर (IS_ERR(nfc->clk.nfi_clk)) अणु
		dev_err(dev, "no clk\n");
		ret = PTR_ERR(nfc->clk.nfi_clk);
		जाओ release_ecc;
	पूर्ण

	nfc->clk.pad_clk = devm_clk_get(dev, "pad_clk");
	अगर (IS_ERR(nfc->clk.pad_clk)) अणु
		dev_err(dev, "no pad clk\n");
		ret = PTR_ERR(nfc->clk.pad_clk);
		जाओ release_ecc;
	पूर्ण

	ret = mtk_nfc_enable_clk(dev, &nfc->clk);
	अगर (ret)
		जाओ release_ecc;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	ret = devm_request_irq(dev, irq, mtk_nfc_irq, 0x0, "mtk-nand", nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to request nfi irq\n");
		जाओ clk_disable;
	पूर्ण

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "failed to set dma mask\n");
		जाओ clk_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, nfc);

	ret = mtk_nfc_nand_chips_init(dev, nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to init nand chips\n");
		जाओ clk_disable;
	पूर्ण

	वापस 0;

clk_disable:
	mtk_nfc_disable_clk(&nfc->clk);

release_ecc:
	mtk_ecc_release(nfc->ecc);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_nfc *nfc = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_nfc_nand_chip *mtk_chip;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	जबतक (!list_empty(&nfc->chips)) अणु
		mtk_chip = list_first_entry(&nfc->chips,
					    काष्ठा mtk_nfc_nand_chip, node);
		chip = &mtk_chip->nand;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&mtk_chip->node);
	पूर्ण

	mtk_ecc_release(nfc->ecc);
	mtk_nfc_disable_clk(&nfc->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_nfc *nfc = dev_get_drvdata(dev);

	mtk_nfc_disable_clk(&nfc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_nfc_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_nfc *nfc = dev_get_drvdata(dev);
	काष्ठा mtk_nfc_nand_chip *chip;
	काष्ठा nand_chip *nand;
	पूर्णांक ret;
	u32 i;

	udelay(200);

	ret = mtk_nfc_enable_clk(dev, &nfc->clk);
	अगर (ret)
		वापस ret;

	/* reset न_अंकD chip अगर VCC was घातered off */
	list_क्रम_each_entry(chip, &nfc->chips, node) अणु
		nand = &chip->nand;
		क्रम (i = 0; i < chip->nsels; i++)
			nand_reset(nand, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mtk_nfc_pm_ops, mtk_nfc_suspend, mtk_nfc_resume);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mtk_nfc_driver = अणु
	.probe  = mtk_nfc_probe,
	.हटाओ = mtk_nfc_हटाओ,
	.driver = अणु
		.name  = MTK_NAME,
		.of_match_table = mtk_nfc_id_table,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &mtk_nfc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_nfc_driver);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Xiaolei Li <xiaolei.li@mediatek.com>");
MODULE_DESCRIPTION("MTK Nand Flash Controller Driver");
