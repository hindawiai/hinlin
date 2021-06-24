<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S3C64XX/S5PC1XX Oneन_अंकD driver
 *
 *  Copyright तऊ 2008-2010 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *  Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Implementation:
 *	S3C64XX: emulate the pseuकरो BufferRAM
 *	S5PC110: use DMA
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश "samsung.h"

क्रमागत soc_type अणु
	TYPE_S3C6400,
	TYPE_S3C6410,
	TYPE_S5PC110,
पूर्ण;

#घोषणा ONEन_अंकD_ERASE_STATUS		0x00
#घोषणा ONEन_अंकD_MULTI_ERASE_SET		0x01
#घोषणा ONEन_अंकD_ERASE_START		0x03
#घोषणा ONEन_अंकD_UNLOCK_START		0x08
#घोषणा ONEन_अंकD_UNLOCK_END		0x09
#घोषणा ONEन_अंकD_LOCK_START		0x0A
#घोषणा ONEन_अंकD_LOCK_END		0x0B
#घोषणा ONEन_अंकD_LOCK_TIGHT_START	0x0C
#घोषणा ONEन_अंकD_LOCK_TIGHT_END		0x0D
#घोषणा ONEन_अंकD_UNLOCK_ALL		0x0E
#घोषणा ONEन_अंकD_OTP_ACCESS		0x12
#घोषणा ONEन_अंकD_SPARE_ACCESS_ONLY	0x13
#घोषणा ONEन_अंकD_MAIN_ACCESS_ONLY	0x14
#घोषणा ONEन_अंकD_ERASE_VERIFY		0x15
#घोषणा ONEन_अंकD_MAIN_SPARE_ACCESS	0x16
#घोषणा ONEन_अंकD_PIPELINE_READ		0x4000

#घोषणा MAP_00				(0x0)
#घोषणा MAP_01				(0x1)
#घोषणा MAP_10				(0x2)
#घोषणा MAP_11				(0x3)

#घोषणा S3C64XX_CMD_MAP_SHIFT		24

#घोषणा S3C6400_FBA_SHIFT		10
#घोषणा S3C6400_FPA_SHIFT		4
#घोषणा S3C6400_FSA_SHIFT		2

#घोषणा S3C6410_FBA_SHIFT		12
#घोषणा S3C6410_FPA_SHIFT		6
#घोषणा S3C6410_FSA_SHIFT		4

/* S5PC110 specअगरic definitions */
#घोषणा S5PC110_DMA_SRC_ADDR		0x400
#घोषणा S5PC110_DMA_SRC_CFG		0x404
#घोषणा S5PC110_DMA_DST_ADDR		0x408
#घोषणा S5PC110_DMA_DST_CFG		0x40C
#घोषणा S5PC110_DMA_TRANS_SIZE		0x414
#घोषणा S5PC110_DMA_TRANS_CMD		0x418
#घोषणा S5PC110_DMA_TRANS_STATUS	0x41C
#घोषणा S5PC110_DMA_TRANS_सूची		0x420
#घोषणा S5PC110_INTC_DMA_CLR		0x1004
#घोषणा S5PC110_INTC_ONEन_अंकD_CLR	0x1008
#घोषणा S5PC110_INTC_DMA_MASK		0x1024
#घोषणा S5PC110_INTC_ONEन_अंकD_MASK	0x1028
#घोषणा S5PC110_INTC_DMA_PEND		0x1044
#घोषणा S5PC110_INTC_ONEन_अंकD_PEND	0x1048
#घोषणा S5PC110_INTC_DMA_STATUS		0x1064
#घोषणा S5PC110_INTC_ONEन_अंकD_STATUS	0x1068

#घोषणा S5PC110_INTC_DMA_TD		(1 << 24)
#घोषणा S5PC110_INTC_DMA_TE		(1 << 16)

#घोषणा S5PC110_DMA_CFG_SINGLE		(0x0 << 16)
#घोषणा S5PC110_DMA_CFG_4BURST		(0x2 << 16)
#घोषणा S5PC110_DMA_CFG_8BURST		(0x3 << 16)
#घोषणा S5PC110_DMA_CFG_16BURST		(0x4 << 16)

#घोषणा S5PC110_DMA_CFG_INC		(0x0 << 8)
#घोषणा S5PC110_DMA_CFG_CNT		(0x1 << 8)

#घोषणा S5PC110_DMA_CFG_8BIT		(0x0 << 0)
#घोषणा S5PC110_DMA_CFG_16BIT		(0x1 << 0)
#घोषणा S5PC110_DMA_CFG_32BIT		(0x2 << 0)

#घोषणा S5PC110_DMA_SRC_CFG_READ	(S5PC110_DMA_CFG_16BURST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_16BIT)
#घोषणा S5PC110_DMA_DST_CFG_READ	(S5PC110_DMA_CFG_16BURST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_32BIT)
#घोषणा S5PC110_DMA_SRC_CFG_WRITE	(S5PC110_DMA_CFG_16BURST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_32BIT)
#घोषणा S5PC110_DMA_DST_CFG_WRITE	(S5PC110_DMA_CFG_16BURST | \
					S5PC110_DMA_CFG_INC | \
					S5PC110_DMA_CFG_16BIT)

#घोषणा S5PC110_DMA_TRANS_CMD_TDC	(0x1 << 18)
#घोषणा S5PC110_DMA_TRANS_CMD_TEC	(0x1 << 16)
#घोषणा S5PC110_DMA_TRANS_CMD_TR	(0x1 << 0)

#घोषणा S5PC110_DMA_TRANS_STATUS_TD	(0x1 << 18)
#घोषणा S5PC110_DMA_TRANS_STATUS_TB	(0x1 << 17)
#घोषणा S5PC110_DMA_TRANS_STATUS_TE	(0x1 << 16)

#घोषणा S5PC110_DMA_सूची_READ		0x0
#घोषणा S5PC110_DMA_सूची_WRITE		0x1

काष्ठा s3c_onenand अणु
	काष्ठा mtd_info	*mtd;
	काष्ठा platक्रमm_device	*pdev;
	क्रमागत soc_type	type;
	व्योम __iomem	*base;
	व्योम __iomem	*ahb_addr;
	पूर्णांक		bootram_command;
	व्योम		*page_buf;
	व्योम		*oob_buf;
	अचिन्हित पूर्णांक	(*mem_addr)(पूर्णांक fba, पूर्णांक fpa, पूर्णांक fsa);
	अचिन्हित पूर्णांक	(*cmd_map)(अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक val);
	व्योम __iomem	*dma_addr;
	अचिन्हित दीर्घ	phys_base;
	काष्ठा completion	complete;
पूर्ण;

#घोषणा CMD_MAP_00(dev, addr)		(dev->cmd_map(MAP_00, ((addr) << 1)))
#घोषणा CMD_MAP_01(dev, mem_addr)	(dev->cmd_map(MAP_01, (mem_addr)))
#घोषणा CMD_MAP_10(dev, mem_addr)	(dev->cmd_map(MAP_10, (mem_addr)))
#घोषणा CMD_MAP_11(dev, addr)		(dev->cmd_map(MAP_11, ((addr) << 2)))

अटल काष्ठा s3c_onenand *onenand;

अटल अंतरभूत पूर्णांक s3c_पढ़ो_reg(पूर्णांक offset)
अणु
	वापस पढ़ोl(onenand->base + offset);
पूर्ण

अटल अंतरभूत व्योम s3c_ग_लिखो_reg(पूर्णांक value, पूर्णांक offset)
अणु
	ग_लिखोl(value, onenand->base + offset);
पूर्ण

अटल अंतरभूत पूर्णांक s3c_पढ़ो_cmd(अचिन्हित पूर्णांक cmd)
अणु
	वापस पढ़ोl(onenand->ahb_addr + cmd);
पूर्ण

अटल अंतरभूत व्योम s3c_ग_लिखो_cmd(पूर्णांक value, अचिन्हित पूर्णांक cmd)
अणु
	ग_लिखोl(value, onenand->ahb_addr + cmd);
पूर्ण

#अगर_घोषित SAMSUNG_DEBUG
अटल व्योम s3c_dump_reg(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x400; i += 0x40) अणु
		prपूर्णांकk(KERN_INFO "0x%08X: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			(अचिन्हित पूर्णांक) onenand->base + i,
			s3c_पढ़ो_reg(i), s3c_पढ़ो_reg(i + 0x10),
			s3c_पढ़ो_reg(i + 0x20), s3c_पढ़ो_reg(i + 0x30));
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक s3c64xx_cmd_map(अचिन्हित type, अचिन्हित val)
अणु
	वापस (type << S3C64XX_CMD_MAP_SHIFT) | val;
पूर्ण

अटल अचिन्हित पूर्णांक s3c6400_mem_addr(पूर्णांक fba, पूर्णांक fpa, पूर्णांक fsa)
अणु
	वापस (fba << S3C6400_FBA_SHIFT) | (fpa << S3C6400_FPA_SHIFT) |
		(fsa << S3C6400_FSA_SHIFT);
पूर्ण

अटल अचिन्हित पूर्णांक s3c6410_mem_addr(पूर्णांक fba, पूर्णांक fpa, पूर्णांक fsa)
अणु
	वापस (fba << S3C6410_FBA_SHIFT) | (fpa << S3C6410_FPA_SHIFT) |
		(fsa << S3C6410_FSA_SHIFT);
पूर्ण

अटल व्योम s3c_onenand_reset(व्योम)
अणु
	अचिन्हित दीर्घ समयout = 0x10000;
	पूर्णांक stat;

	s3c_ग_लिखो_reg(ONEन_अंकD_MEM_RESET_COLD, MEM_RESET_OFFSET);
	जबतक (1 && समयout--) अणु
		stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
		अगर (stat & RST_CMP)
			अवरोध;
	पूर्ण
	stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
	s3c_ग_लिखो_reg(stat, INT_ERR_ACK_OFFSET);

	/* Clear पूर्णांकerrupt */
	s3c_ग_लिखो_reg(0x0, INT_ERR_ACK_OFFSET);
	/* Clear the ECC status */
	s3c_ग_लिखो_reg(0x0, ECC_ERR_STAT_OFFSET);
पूर्ण

अटल अचिन्हित लघु s3c_onenand_पढ़ोw(व्योम __iomem *addr)
अणु
	काष्ठा onenand_chip *this = onenand->mtd->priv;
	काष्ठा device *dev = &onenand->pdev->dev;
	पूर्णांक reg = addr - this->base;
	पूर्णांक word_addr = reg >> 1;
	पूर्णांक value;

	/* It's used क्रम probing समय */
	चयन (reg) अणु
	हाल ONEन_अंकD_REG_MANUFACTURER_ID:
		वापस s3c_पढ़ो_reg(MANUFACT_ID_OFFSET);
	हाल ONEन_अंकD_REG_DEVICE_ID:
		वापस s3c_पढ़ो_reg(DEVICE_ID_OFFSET);
	हाल ONEन_अंकD_REG_VERSION_ID:
		वापस s3c_पढ़ो_reg(FLASH_VER_ID_OFFSET);
	हाल ONEन_अंकD_REG_DATA_BUFFER_SIZE:
		वापस s3c_पढ़ो_reg(DATA_BUF_SIZE_OFFSET);
	हाल ONEन_अंकD_REG_TECHNOLOGY:
		वापस s3c_पढ़ो_reg(TECH_OFFSET);
	हाल ONEन_अंकD_REG_SYS_CFG1:
		वापस s3c_पढ़ो_reg(MEM_CFG_OFFSET);

	/* Used at unlock all status */
	हाल ONEन_अंकD_REG_CTRL_STATUS:
		वापस 0;

	हाल ONEन_अंकD_REG_WP_STATUS:
		वापस ONEन_अंकD_WP_US;

	शेष:
		अवरोध;
	पूर्ण

	/* BootRAM access control */
	अगर ((अचिन्हित दीर्घ)addr < ONEन_अंकD_DATARAM && onenand->bootram_command) अणु
		अगर (word_addr == 0)
			वापस s3c_पढ़ो_reg(MANUFACT_ID_OFFSET);
		अगर (word_addr == 1)
			वापस s3c_पढ़ो_reg(DEVICE_ID_OFFSET);
		अगर (word_addr == 2)
			वापस s3c_पढ़ो_reg(FLASH_VER_ID_OFFSET);
	पूर्ण

	value = s3c_पढ़ो_cmd(CMD_MAP_11(onenand, word_addr)) & 0xffff;
	dev_info(dev, "%s: Illegal access at reg 0x%x, value 0x%x\n", __func__,
		 word_addr, value);
	वापस value;
पूर्ण

अटल व्योम s3c_onenand_ग_लिखोw(अचिन्हित लघु value, व्योम __iomem *addr)
अणु
	काष्ठा onenand_chip *this = onenand->mtd->priv;
	काष्ठा device *dev = &onenand->pdev->dev;
	अचिन्हित पूर्णांक reg = addr - this->base;
	अचिन्हित पूर्णांक word_addr = reg >> 1;

	/* It's used क्रम probing समय */
	चयन (reg) अणु
	हाल ONEन_अंकD_REG_SYS_CFG1:
		s3c_ग_लिखो_reg(value, MEM_CFG_OFFSET);
		वापस;

	हाल ONEन_अंकD_REG_START_ADDRESS1:
	हाल ONEन_अंकD_REG_START_ADDRESS2:
		वापस;

	/* Lock/lock-tight/unlock/unlock_all */
	हाल ONEन_अंकD_REG_START_BLOCK_ADDRESS:
		वापस;

	शेष:
		अवरोध;
	पूर्ण

	/* BootRAM access control */
	अगर ((अचिन्हित दीर्घ)addr < ONEन_अंकD_DATARAM) अणु
		अगर (value == ONEन_अंकD_CMD_READID) अणु
			onenand->bootram_command = 1;
			वापस;
		पूर्ण
		अगर (value == ONEन_अंकD_CMD_RESET) अणु
			s3c_ग_लिखो_reg(ONEन_अंकD_MEM_RESET_COLD, MEM_RESET_OFFSET);
			onenand->bootram_command = 0;
			वापस;
		पूर्ण
	पूर्ण

	dev_info(dev, "%s: Illegal access at reg 0x%x, value 0x%x\n", __func__,
		 word_addr, value);

	s3c_ग_लिखो_cmd(value, CMD_MAP_11(onenand, word_addr));
पूर्ण

अटल पूर्णांक s3c_onenand_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा device *dev = &onenand->pdev->dev;
	अचिन्हित पूर्णांक flags = INT_ACT;
	अचिन्हित पूर्णांक stat, ecc;
	अचिन्हित दीर्घ समयout;

	चयन (state) अणु
	हाल FL_READING:
		flags |= BLK_RW_CMP | LOAD_CMP;
		अवरोध;
	हाल FL_WRITING:
		flags |= BLK_RW_CMP | PGM_CMP;
		अवरोध;
	हाल FL_ERASING:
		flags |= BLK_RW_CMP | ERS_CMP;
		अवरोध;
	हाल FL_LOCKING:
		flags |= BLK_RW_CMP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* The 20 msec is enough */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
		अगर (stat & flags)
			अवरोध;

		अगर (state != FL_READING)
			cond_resched();
	पूर्ण
	/* To get correct पूर्णांकerrupt status in समयout हाल */
	stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
	s3c_ग_लिखो_reg(stat, INT_ERR_ACK_OFFSET);

	/*
	 * In the Spec. it checks the controller status first
	 * However अगर you get the correct inक्रमmation in हाल of
	 * घातer off recovery (POR) test, it should पढ़ो ECC status first
	 */
	अगर (stat & LOAD_CMP) अणु
		ecc = s3c_पढ़ो_reg(ECC_ERR_STAT_OFFSET);
		अगर (ecc & ONEन_अंकD_ECC_4BIT_UNCORRECTABLE) अणु
			dev_info(dev, "%s: ECC error = 0x%04x\n", __func__,
				 ecc);
			mtd->ecc_stats.failed++;
			वापस -EBADMSG;
		पूर्ण
	पूर्ण

	अगर (stat & (LOCKED_BLK | ERS_FAIL | PGM_FAIL | LD_FAIL_ECC_ERR)) अणु
		dev_info(dev, "%s: controller error = 0x%04x\n", __func__,
			 stat);
		अगर (stat & LOCKED_BLK)
			dev_info(dev, "%s: it's locked error = 0x%04x\n",
				 __func__, stat);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_onenand_command(काष्ठा mtd_info *mtd, पूर्णांक cmd, loff_t addr,
			       माप_प्रकार len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित पूर्णांक *m, *s;
	पूर्णांक fba, fpa, fsa = 0;
	अचिन्हित पूर्णांक mem_addr, cmd_map_01, cmd_map_10;
	पूर्णांक i, mcount, scount;
	पूर्णांक index;

	fba = (पूर्णांक) (addr >> this->erase_shअगरt);
	fpa = (पूर्णांक) (addr >> this->page_shअगरt);
	fpa &= this->page_mask;

	mem_addr = onenand->mem_addr(fba, fpa, fsa);
	cmd_map_01 = CMD_MAP_01(onenand, mem_addr);
	cmd_map_10 = CMD_MAP_10(onenand, mem_addr);

	चयन (cmd) अणु
	हाल ONEन_अंकD_CMD_READ:
	हाल ONEन_अंकD_CMD_READOOB:
	हाल ONEन_अंकD_CMD_BUFFERRAM:
		ONEन_अंकD_SET_NEXT_BUFFERRAM(this);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	index = ONEन_अंकD_CURRENT_BUFFERRAM(this);

	/*
	 * Emulate Two BufferRAMs and access with 4 bytes poपूर्णांकer
	 */
	m = onenand->page_buf;
	s = onenand->oob_buf;

	अगर (index) अणु
		m += (this->ग_लिखोsize >> 2);
		s += (mtd->oobsize >> 2);
	पूर्ण

	mcount = mtd->ग_लिखोsize >> 2;
	scount = mtd->oobsize >> 2;

	चयन (cmd) अणु
	हाल ONEन_अंकD_CMD_READ:
		/* Main */
		क्रम (i = 0; i < mcount; i++)
			*m++ = s3c_पढ़ो_cmd(cmd_map_01);
		वापस 0;

	हाल ONEन_अंकD_CMD_READOOB:
		s3c_ग_लिखो_reg(TSRF, TRANS_SPARE_OFFSET);
		/* Main */
		क्रम (i = 0; i < mcount; i++)
			*m++ = s3c_पढ़ो_cmd(cmd_map_01);

		/* Spare */
		क्रम (i = 0; i < scount; i++)
			*s++ = s3c_पढ़ो_cmd(cmd_map_01);

		s3c_ग_लिखो_reg(0, TRANS_SPARE_OFFSET);
		वापस 0;

	हाल ONEन_अंकD_CMD_PROG:
		/* Main */
		क्रम (i = 0; i < mcount; i++)
			s3c_ग_लिखो_cmd(*m++, cmd_map_01);
		वापस 0;

	हाल ONEन_अंकD_CMD_PROGOOB:
		s3c_ग_लिखो_reg(TSRF, TRANS_SPARE_OFFSET);

		/* Main - dummy ग_लिखो */
		क्रम (i = 0; i < mcount; i++)
			s3c_ग_लिखो_cmd(0xffffffff, cmd_map_01);

		/* Spare */
		क्रम (i = 0; i < scount; i++)
			s3c_ग_लिखो_cmd(*s++, cmd_map_01);

		s3c_ग_लिखो_reg(0, TRANS_SPARE_OFFSET);
		वापस 0;

	हाल ONEन_अंकD_CMD_UNLOCK_ALL:
		s3c_ग_लिखो_cmd(ONEन_अंकD_UNLOCK_ALL, cmd_map_10);
		वापस 0;

	हाल ONEन_अंकD_CMD_ERASE:
		s3c_ग_लिखो_cmd(ONEन_अंकD_ERASE_START, cmd_map_10);
		वापस 0;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर *s3c_get_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक index = ONEन_अंकD_CURRENT_BUFFERRAM(this);
	अचिन्हित अक्षर *p;

	अगर (area == ONEन_अंकD_DATARAM) अणु
		p = onenand->page_buf;
		अगर (index == 1)
			p += this->ग_लिखोsize;
	पूर्ण अन्यथा अणु
		p = onenand->oob_buf;
		अगर (index == 1)
			p += mtd->oobsize;
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक onenand_पढ़ो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
				  अचिन्हित अक्षर *buffer, पूर्णांक offset,
				  माप_प्रकार count)
अणु
	अचिन्हित अक्षर *p;

	p = s3c_get_bufferram(mtd, area);
	स_नकल(buffer, p + offset, count);
	वापस 0;
पूर्ण

अटल पूर्णांक onenand_ग_लिखो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
				   स्थिर अचिन्हित अक्षर *buffer, पूर्णांक offset,
				   माप_प्रकार count)
अणु
	अचिन्हित अक्षर *p;

	p = s3c_get_bufferram(mtd, area);
	स_नकल(p + offset, buffer, count);
	वापस 0;
पूर्ण

अटल पूर्णांक (*s5pc110_dma_ops)(dma_addr_t dst, dma_addr_t src, माप_प्रकार count, पूर्णांक direction);

अटल पूर्णांक s5pc110_dma_poll(dma_addr_t dst, dma_addr_t src, माप_प्रकार count, पूर्णांक direction)
अणु
	व्योम __iomem *base = onenand->dma_addr;
	पूर्णांक status;
	अचिन्हित दीर्घ समयout;

	ग_लिखोl(src, base + S5PC110_DMA_SRC_ADDR);
	ग_लिखोl(dst, base + S5PC110_DMA_DST_ADDR);

	अगर (direction == S5PC110_DMA_सूची_READ) अणु
		ग_लिखोl(S5PC110_DMA_SRC_CFG_READ, base + S5PC110_DMA_SRC_CFG);
		ग_लिखोl(S5PC110_DMA_DST_CFG_READ, base + S5PC110_DMA_DST_CFG);
	पूर्ण अन्यथा अणु
		ग_लिखोl(S5PC110_DMA_SRC_CFG_WRITE, base + S5PC110_DMA_SRC_CFG);
		ग_लिखोl(S5PC110_DMA_DST_CFG_WRITE, base + S5PC110_DMA_DST_CFG);
	पूर्ण

	ग_लिखोl(count, base + S5PC110_DMA_TRANS_SIZE);
	ग_लिखोl(direction, base + S5PC110_DMA_TRANS_सूची);

	ग_लिखोl(S5PC110_DMA_TRANS_CMD_TR, base + S5PC110_DMA_TRANS_CMD);

	/*
	 * There's no exact समयout values at Spec.
	 * In real हाल it takes under 1 msec.
	 * So 20 msecs are enough.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(20);

	करो अणु
		status = पढ़ोl(base + S5PC110_DMA_TRANS_STATUS);
		अगर (status & S5PC110_DMA_TRANS_STATUS_TE) अणु
			ग_लिखोl(S5PC110_DMA_TRANS_CMD_TEC,
					base + S5PC110_DMA_TRANS_CMD);
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक (!(status & S5PC110_DMA_TRANS_STATUS_TD) &&
		समय_beक्रमe(jअगरfies, समयout));

	ग_लिखोl(S5PC110_DMA_TRANS_CMD_TDC, base + S5PC110_DMA_TRANS_CMD);

	वापस 0;
पूर्ण

अटल irqवापस_t s5pc110_onenand_irq(पूर्णांक irq, व्योम *data)
अणु
	व्योम __iomem *base = onenand->dma_addr;
	पूर्णांक status, cmd = 0;

	status = पढ़ोl(base + S5PC110_INTC_DMA_STATUS);

	अगर (likely(status & S5PC110_INTC_DMA_TD))
		cmd = S5PC110_DMA_TRANS_CMD_TDC;

	अगर (unlikely(status & S5PC110_INTC_DMA_TE))
		cmd = S5PC110_DMA_TRANS_CMD_TEC;

	ग_लिखोl(cmd, base + S5PC110_DMA_TRANS_CMD);
	ग_लिखोl(status, base + S5PC110_INTC_DMA_CLR);

	अगर (!onenand->complete.करोne)
		complete(&onenand->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s5pc110_dma_irq(dma_addr_t dst, dma_addr_t src, माप_प्रकार count, पूर्णांक direction)
अणु
	व्योम __iomem *base = onenand->dma_addr;
	पूर्णांक status;

	status = पढ़ोl(base + S5PC110_INTC_DMA_MASK);
	अगर (status) अणु
		status &= ~(S5PC110_INTC_DMA_TD | S5PC110_INTC_DMA_TE);
		ग_लिखोl(status, base + S5PC110_INTC_DMA_MASK);
	पूर्ण

	ग_लिखोl(src, base + S5PC110_DMA_SRC_ADDR);
	ग_लिखोl(dst, base + S5PC110_DMA_DST_ADDR);

	अगर (direction == S5PC110_DMA_सूची_READ) अणु
		ग_लिखोl(S5PC110_DMA_SRC_CFG_READ, base + S5PC110_DMA_SRC_CFG);
		ग_लिखोl(S5PC110_DMA_DST_CFG_READ, base + S5PC110_DMA_DST_CFG);
	पूर्ण अन्यथा अणु
		ग_लिखोl(S5PC110_DMA_SRC_CFG_WRITE, base + S5PC110_DMA_SRC_CFG);
		ग_लिखोl(S5PC110_DMA_DST_CFG_WRITE, base + S5PC110_DMA_DST_CFG);
	पूर्ण

	ग_लिखोl(count, base + S5PC110_DMA_TRANS_SIZE);
	ग_लिखोl(direction, base + S5PC110_DMA_TRANS_सूची);

	ग_लिखोl(S5PC110_DMA_TRANS_CMD_TR, base + S5PC110_DMA_TRANS_CMD);

	रुको_क्रम_completion_समयout(&onenand->complete, msecs_to_jअगरfies(20));

	वापस 0;
पूर्ण

अटल पूर्णांक s5pc110_पढ़ो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
		अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	व्योम __iomem *p;
	व्योम *buf = (व्योम *) buffer;
	dma_addr_t dma_src, dma_dst;
	पूर्णांक err, ofs, page_dma = 0;
	काष्ठा device *dev = &onenand->pdev->dev;

	p = this->base + area;
	अगर (ONEन_अंकD_CURRENT_BUFFERRAM(this)) अणु
		अगर (area == ONEन_अंकD_DATARAM)
			p += this->ग_लिखोsize;
		अन्यथा
			p += mtd->oobsize;
	पूर्ण

	अगर (offset & 3 || (माप_प्रकार) buf & 3 ||
		!onenand->dma_addr || count != mtd->ग_लिखोsize)
		जाओ normal;

	/* Handle vदो_स्मृति address */
	अगर (buf >= high_memory) अणु
		काष्ठा page *page;

		अगर (((माप_प्रकार) buf & PAGE_MASK) !=
		    ((माप_प्रकार) (buf + count - 1) & PAGE_MASK))
			जाओ normal;
		page = vदो_स्मृति_to_page(buf);
		अगर (!page)
			जाओ normal;

		/* Page offset */
		ofs = ((माप_प्रकार) buf & ~PAGE_MASK);
		page_dma = 1;

		/* DMA routine */
		dma_src = onenand->phys_base + (p - this->base);
		dma_dst = dma_map_page(dev, page, ofs, count, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		/* DMA routine */
		dma_src = onenand->phys_base + (p - this->base);
		dma_dst = dma_map_single(dev, buf, count, DMA_FROM_DEVICE);
	पूर्ण
	अगर (dma_mapping_error(dev, dma_dst)) अणु
		dev_err(dev, "Couldn't map a %zu byte buffer for DMA\n", count);
		जाओ normal;
	पूर्ण
	err = s5pc110_dma_ops(dma_dst, dma_src,
			count, S5PC110_DMA_सूची_READ);

	अगर (page_dma)
		dma_unmap_page(dev, dma_dst, count, DMA_FROM_DEVICE);
	अन्यथा
		dma_unmap_single(dev, dma_dst, count, DMA_FROM_DEVICE);

	अगर (!err)
		वापस 0;

normal:
	अगर (count != mtd->ग_लिखोsize) अणु
		/* Copy the bufferram to memory to prevent unaligned access */
		स_नकल_fromio(this->page_buf, p, mtd->ग_लिखोsize);
		स_नकल(buffer, this->page_buf + offset, count);
	पूर्ण अन्यथा अणु
		स_नकल_fromio(buffer, p, count);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5pc110_chip_probe(काष्ठा mtd_info *mtd)
अणु
	/* Now just वापस 0 */
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_onenand_bbt_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक flags = INT_ACT | LOAD_CMP;
	अचिन्हित पूर्णांक stat;
	अचिन्हित दीर्घ समयout;

	/* The 20 msec is enough */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
		अगर (stat & flags)
			अवरोध;
	पूर्ण
	/* To get correct पूर्णांकerrupt status in समयout हाल */
	stat = s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET);
	s3c_ग_लिखो_reg(stat, INT_ERR_ACK_OFFSET);

	अगर (stat & LD_FAIL_ECC_ERR) अणु
		s3c_onenand_reset();
		वापस ONEन_अंकD_BBT_READ_ERROR;
	पूर्ण

	अगर (stat & LOAD_CMP) अणु
		पूर्णांक ecc = s3c_पढ़ो_reg(ECC_ERR_STAT_OFFSET);
		अगर (ecc & ONEन_अंकD_ECC_4BIT_UNCORRECTABLE) अणु
			s3c_onenand_reset();
			वापस ONEन_अंकD_BBT_READ_ERROR;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s3c_onenand_check_lock_status(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा device *dev = &onenand->pdev->dev;
	अचिन्हित पूर्णांक block, end;

	end = this->chipsize >> this->erase_shअगरt;

	क्रम (block = 0; block < end; block++) अणु
		अचिन्हित पूर्णांक mem_addr = onenand->mem_addr(block, 0, 0);
		s3c_पढ़ो_cmd(CMD_MAP_01(onenand, mem_addr));

		अगर (s3c_पढ़ो_reg(INT_ERR_STAT_OFFSET) & LOCKED_BLK) अणु
			dev_err(dev, "block %d is write-protected!\n", block);
			s3c_ग_लिखो_reg(LOCKED_BLK, INT_ERR_ACK_OFFSET);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s3c_onenand_करो_lock_cmd(काष्ठा mtd_info *mtd, loff_t ofs,
				    माप_प्रकार len, पूर्णांक cmd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक start, end, start_mem_addr, end_mem_addr;

	start = ofs >> this->erase_shअगरt;
	start_mem_addr = onenand->mem_addr(start, 0, 0);
	end = start + (len >> this->erase_shअगरt) - 1;
	end_mem_addr = onenand->mem_addr(end, 0, 0);

	अगर (cmd == ONEन_अंकD_CMD_LOCK) अणु
		s3c_ग_लिखो_cmd(ONEन_अंकD_LOCK_START, CMD_MAP_10(onenand,
							     start_mem_addr));
		s3c_ग_लिखो_cmd(ONEन_अंकD_LOCK_END, CMD_MAP_10(onenand,
							   end_mem_addr));
	पूर्ण अन्यथा अणु
		s3c_ग_लिखो_cmd(ONEन_अंकD_UNLOCK_START, CMD_MAP_10(onenand,
							       start_mem_addr));
		s3c_ग_लिखो_cmd(ONEन_अंकD_UNLOCK_END, CMD_MAP_10(onenand,
							     end_mem_addr));
	पूर्ण

	this->रुको(mtd, FL_LOCKING);
पूर्ण

अटल व्योम s3c_unlock_all(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	loff_t ofs = 0;
	माप_प्रकार len = this->chipsize;

	अगर (this->options & ONEन_अंकD_HAS_UNLOCK_ALL) अणु
		/* Write unlock command */
		this->command(mtd, ONEन_अंकD_CMD_UNLOCK_ALL, 0, 0);

		/* No need to check वापस value */
		this->रुको(mtd, FL_LOCKING);

		/* Workaround क्रम all block unlock in DDP */
		अगर (!ONEन_अंकD_IS_DDP(this)) अणु
			s3c_onenand_check_lock_status(mtd);
			वापस;
		पूर्ण

		/* All blocks on another chip */
		ofs = this->chipsize >> 1;
		len = this->chipsize >> 1;
	पूर्ण

	s3c_onenand_करो_lock_cmd(mtd, ofs, len, ONEन_अंकD_CMD_UNLOCK);

	s3c_onenand_check_lock_status(mtd);
पूर्ण

अटल व्योम s3c_onenand_setup(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	onenand->mtd = mtd;

	अगर (onenand->type == TYPE_S3C6400) अणु
		onenand->mem_addr = s3c6400_mem_addr;
		onenand->cmd_map = s3c64xx_cmd_map;
	पूर्ण अन्यथा अगर (onenand->type == TYPE_S3C6410) अणु
		onenand->mem_addr = s3c6410_mem_addr;
		onenand->cmd_map = s3c64xx_cmd_map;
	पूर्ण अन्यथा अगर (onenand->type == TYPE_S5PC110) अणु
		/* Use generic onenand functions */
		this->पढ़ो_bufferram = s5pc110_पढ़ो_bufferram;
		this->chip_probe = s5pc110_chip_probe;
		वापस;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	this->पढ़ो_word = s3c_onenand_पढ़ोw;
	this->ग_लिखो_word = s3c_onenand_ग_लिखोw;

	this->रुको = s3c_onenand_रुको;
	this->bbt_रुको = s3c_onenand_bbt_रुको;
	this->unlock_all = s3c_unlock_all;
	this->command = s3c_onenand_command;

	this->पढ़ो_bufferram = onenand_पढ़ो_bufferram;
	this->ग_लिखो_bufferram = onenand_ग_लिखो_bufferram;
पूर्ण

अटल पूर्णांक s3c_onenand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा onenand_platक्रमm_data *pdata;
	काष्ठा onenand_chip *this;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *r;
	पूर्णांक size, err;

	pdata = dev_get_platdata(&pdev->dev);
	/* No need to check pdata. the platक्रमm data is optional */

	size = माप(काष्ठा mtd_info) + माप(काष्ठा onenand_chip);
	mtd = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!mtd)
		वापस -ENOMEM;

	onenand = devm_kzalloc(&pdev->dev, माप(काष्ठा s3c_onenand),
			       GFP_KERNEL);
	अगर (!onenand)
		वापस -ENOMEM;

	this = (काष्ठा onenand_chip *) &mtd[1];
	mtd->priv = this;
	mtd->dev.parent = &pdev->dev;
	onenand->pdev = pdev;
	onenand->type = platक्रमm_get_device_id(pdev)->driver_data;

	s3c_onenand_setup(mtd);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	onenand->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(onenand->base))
		वापस PTR_ERR(onenand->base);

	onenand->phys_base = r->start;

	/* Set onenand_chip also */
	this->base = onenand->base;

	/* Use runसमय badblock check */
	this->options |= ONEन_अंकD_SKIP_UNLOCK_CHECK;

	अगर (onenand->type != TYPE_S5PC110) अणु
		r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		onenand->ahb_addr = devm_ioremap_resource(&pdev->dev, r);
		अगर (IS_ERR(onenand->ahb_addr))
			वापस PTR_ERR(onenand->ahb_addr);

		/* Allocate 4KiB BufferRAM */
		onenand->page_buf = devm_kzalloc(&pdev->dev, SZ_4K,
						 GFP_KERNEL);
		अगर (!onenand->page_buf)
			वापस -ENOMEM;

		/* Allocate 128 SpareRAM */
		onenand->oob_buf = devm_kzalloc(&pdev->dev, 128, GFP_KERNEL);
		अगर (!onenand->oob_buf)
			वापस -ENOMEM;

		/* S3C करोesn't handle subpage ग_लिखो */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->ग_लिखोsize;

	पूर्ण अन्यथा अणु /* S5PC110 */
		r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		onenand->dma_addr = devm_ioremap_resource(&pdev->dev, r);
		अगर (IS_ERR(onenand->dma_addr))
			वापस PTR_ERR(onenand->dma_addr);

		s5pc110_dma_ops = s5pc110_dma_poll;
		/* Interrupt support */
		r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
		अगर (r) अणु
			init_completion(&onenand->complete);
			s5pc110_dma_ops = s5pc110_dma_irq;
			err = devm_request_irq(&pdev->dev, r->start,
					       s5pc110_onenand_irq,
					       IRQF_SHARED, "onenand",
					       &onenand);
			अगर (err) अणु
				dev_err(&pdev->dev, "failed to get irq\n");
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	err = onenand_scan(mtd, 1);
	अगर (err)
		वापस err;

	अगर (onenand->type != TYPE_S5PC110) अणु
		/* S3C करोesn't handle subpage ग_लिखो */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->ग_लिखोsize;
	पूर्ण

	अगर (s3c_पढ़ो_reg(MEM_CFG_OFFSET) & ONEन_अंकD_SYS_CFG1_SYNC_READ)
		dev_info(&onenand->pdev->dev, "OneNAND Sync. Burst Read enabled\n");

	err = mtd_device_रेजिस्टर(mtd, pdata ? pdata->parts : शून्य,
				  pdata ? pdata->nr_parts : 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to parse partitions and register the MTD device\n");
		onenand_release(mtd);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mtd);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_onenand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtd_info *mtd = platक्रमm_get_drvdata(pdev);

	onenand_release(mtd);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_pm_ops_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा onenand_chip *this = mtd->priv;

	this->रुको(mtd, FL_PM_SUSPENDED);
	वापस 0;
पूर्ण

अटल  पूर्णांक s3c_pm_ops_resume(काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	काष्ठा onenand_chip *this = mtd->priv;

	this->unlock_all(mtd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s3c_pm_ops = अणु
	.suspend	= s3c_pm_ops_suspend,
	.resume		= s3c_pm_ops_resume,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c_onenand_driver_ids[] = अणु
	अणु
		.name		= "s3c6400-onenand",
		.driver_data	= TYPE_S3C6400,
	पूर्ण, अणु
		.name		= "s3c6410-onenand",
		.driver_data	= TYPE_S3C6410,
	पूर्ण, अणु
		.name		= "s5pc110-onenand",
		.driver_data	= TYPE_S5PC110,
	पूर्ण, अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c_onenand_driver_ids);

अटल काष्ठा platक्रमm_driver s3c_onenand_driver = अणु
	.driver         = अणु
		.name	= "samsung-onenand",
		.pm	= &s3c_pm_ops,
	पूर्ण,
	.id_table	= s3c_onenand_driver_ids,
	.probe          = s3c_onenand_probe,
	.हटाओ         = s3c_onenand_हटाओ,
पूर्ण;

module_platक्रमm_driver(s3c_onenand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyungmin Park <kyungmin.park@samsung.com>");
MODULE_DESCRIPTION("Samsung OneNAND controller support");
