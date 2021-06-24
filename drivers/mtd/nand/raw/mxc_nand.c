<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Sascha Hauer, kernel@pengutronix.de
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#घोषणा DRIVER_NAME "mxc_nand"

/* Addresses क्रम NFC रेजिस्टरs */
#घोषणा NFC_V1_V2_BUF_SIZE		(host->regs + 0x00)
#घोषणा NFC_V1_V2_BUF_ADDR		(host->regs + 0x04)
#घोषणा NFC_V1_V2_FLASH_ADDR		(host->regs + 0x06)
#घोषणा NFC_V1_V2_FLASH_CMD		(host->regs + 0x08)
#घोषणा NFC_V1_V2_CONFIG		(host->regs + 0x0a)
#घोषणा NFC_V1_V2_ECC_STATUS_RESULT	(host->regs + 0x0c)
#घोषणा NFC_V1_V2_RSLTMAIN_AREA		(host->regs + 0x0e)
#घोषणा NFC_V21_RSLTSPARE_AREA		(host->regs + 0x10)
#घोषणा NFC_V1_V2_WRPROT		(host->regs + 0x12)
#घोषणा NFC_V1_UNLOCKSTART_BLKADDR	(host->regs + 0x14)
#घोषणा NFC_V1_UNLOCKEND_BLKADDR	(host->regs + 0x16)
#घोषणा NFC_V21_UNLOCKSTART_BLKADDR0	(host->regs + 0x20)
#घोषणा NFC_V21_UNLOCKSTART_BLKADDR1	(host->regs + 0x24)
#घोषणा NFC_V21_UNLOCKSTART_BLKADDR2	(host->regs + 0x28)
#घोषणा NFC_V21_UNLOCKSTART_BLKADDR3	(host->regs + 0x2c)
#घोषणा NFC_V21_UNLOCKEND_BLKADDR0	(host->regs + 0x22)
#घोषणा NFC_V21_UNLOCKEND_BLKADDR1	(host->regs + 0x26)
#घोषणा NFC_V21_UNLOCKEND_BLKADDR2	(host->regs + 0x2a)
#घोषणा NFC_V21_UNLOCKEND_BLKADDR3	(host->regs + 0x2e)
#घोषणा NFC_V1_V2_NF_WRPRST		(host->regs + 0x18)
#घोषणा NFC_V1_V2_CONFIG1		(host->regs + 0x1a)
#घोषणा NFC_V1_V2_CONFIG2		(host->regs + 0x1c)

#घोषणा NFC_V2_CONFIG1_ECC_MODE_4	(1 << 0)
#घोषणा NFC_V1_V2_CONFIG1_SP_EN		(1 << 2)
#घोषणा NFC_V1_V2_CONFIG1_ECC_EN	(1 << 3)
#घोषणा NFC_V1_V2_CONFIG1_INT_MSK	(1 << 4)
#घोषणा NFC_V1_V2_CONFIG1_BIG		(1 << 5)
#घोषणा NFC_V1_V2_CONFIG1_RST		(1 << 6)
#घोषणा NFC_V1_V2_CONFIG1_CE		(1 << 7)
#घोषणा NFC_V2_CONFIG1_ONE_CYCLE	(1 << 8)
#घोषणा NFC_V2_CONFIG1_PPB(x)		(((x) & 0x3) << 9)
#घोषणा NFC_V2_CONFIG1_FP_INT		(1 << 11)

#घोषणा NFC_V1_V2_CONFIG2_INT		(1 << 15)

/*
 * Operation modes क्रम the NFC. Valid क्रम v1, v2 and v3
 * type controllers.
 */
#घोषणा NFC_CMD				(1 << 0)
#घोषणा NFC_ADDR			(1 << 1)
#घोषणा NFC_INPUT			(1 << 2)
#घोषणा NFC_OUTPUT			(1 << 3)
#घोषणा NFC_ID				(1 << 4)
#घोषणा NFC_STATUS			(1 << 5)

#घोषणा NFC_V3_FLASH_CMD		(host->regs_axi + 0x00)
#घोषणा NFC_V3_FLASH_ADDR0		(host->regs_axi + 0x04)

#घोषणा NFC_V3_CONFIG1			(host->regs_axi + 0x34)
#घोषणा NFC_V3_CONFIG1_SP_EN		(1 << 0)
#घोषणा NFC_V3_CONFIG1_RBA(x)		(((x) & 0x7 ) << 4)

#घोषणा NFC_V3_ECC_STATUS_RESULT	(host->regs_axi + 0x38)

#घोषणा NFC_V3_LAUNCH			(host->regs_axi + 0x40)

#घोषणा NFC_V3_WRPROT			(host->regs_ip + 0x0)
#घोषणा NFC_V3_WRPROT_LOCK_TIGHT	(1 << 0)
#घोषणा NFC_V3_WRPROT_LOCK		(1 << 1)
#घोषणा NFC_V3_WRPROT_UNLOCK		(1 << 2)
#घोषणा NFC_V3_WRPROT_BLS_UNLOCK	(2 << 6)

#घोषणा NFC_V3_WRPROT_UNLOCK_BLK_ADD0   (host->regs_ip + 0x04)

#घोषणा NFC_V3_CONFIG2			(host->regs_ip + 0x24)
#घोषणा NFC_V3_CONFIG2_PS_512			(0 << 0)
#घोषणा NFC_V3_CONFIG2_PS_2048			(1 << 0)
#घोषणा NFC_V3_CONFIG2_PS_4096			(2 << 0)
#घोषणा NFC_V3_CONFIG2_ONE_CYCLE		(1 << 2)
#घोषणा NFC_V3_CONFIG2_ECC_EN			(1 << 3)
#घोषणा NFC_V3_CONFIG2_2CMD_PHASES		(1 << 4)
#घोषणा NFC_V3_CONFIG2_NUM_ADDR_PHASE0		(1 << 5)
#घोषणा NFC_V3_CONFIG2_ECC_MODE_8		(1 << 6)
#घोषणा NFC_V3_CONFIG2_PPB(x, shअगरt)		(((x) & 0x3) << shअगरt)
#घोषणा NFC_V3_CONFIG2_NUM_ADDR_PHASE1(x)	(((x) & 0x3) << 12)
#घोषणा NFC_V3_CONFIG2_INT_MSK			(1 << 15)
#घोषणा NFC_V3_CONFIG2_ST_CMD(x)		(((x) & 0xff) << 24)
#घोषणा NFC_V3_CONFIG2_SPAS(x)			(((x) & 0xff) << 16)

#घोषणा NFC_V3_CONFIG3				(host->regs_ip + 0x28)
#घोषणा NFC_V3_CONFIG3_ADD_OP(x)		(((x) & 0x3) << 0)
#घोषणा NFC_V3_CONFIG3_FW8			(1 << 3)
#घोषणा NFC_V3_CONFIG3_SBB(x)			(((x) & 0x7) << 8)
#घोषणा NFC_V3_CONFIG3_NUM_OF_DEVICES(x)	(((x) & 0x7) << 12)
#घोषणा NFC_V3_CONFIG3_RBB_MODE			(1 << 15)
#घोषणा NFC_V3_CONFIG3_NO_SDMA			(1 << 20)

#घोषणा NFC_V3_IPC			(host->regs_ip + 0x2C)
#घोषणा NFC_V3_IPC_CREQ			(1 << 0)
#घोषणा NFC_V3_IPC_INT			(1 << 31)

#घोषणा NFC_V3_DELAY_LINE		(host->regs_ip + 0x34)

काष्ठा mxc_nand_host;

काष्ठा mxc_nand_devtype_data अणु
	व्योम (*preset)(काष्ठा mtd_info *);
	पूर्णांक (*पढ़ो_page)(काष्ठा nand_chip *chip, व्योम *buf, व्योम *oob, bool ecc,
			 पूर्णांक page);
	व्योम (*send_cmd)(काष्ठा mxc_nand_host *, uपूर्णांक16_t, पूर्णांक);
	व्योम (*send_addr)(काष्ठा mxc_nand_host *, uपूर्णांक16_t, पूर्णांक);
	व्योम (*send_page)(काष्ठा mtd_info *, अचिन्हित पूर्णांक);
	व्योम (*send_पढ़ो_id)(काष्ठा mxc_nand_host *);
	uपूर्णांक16_t (*get_dev_status)(काष्ठा mxc_nand_host *);
	पूर्णांक (*check_पूर्णांक)(काष्ठा mxc_nand_host *);
	व्योम (*irq_control)(काष्ठा mxc_nand_host *, पूर्णांक);
	u32 (*get_ecc_status)(काष्ठा mxc_nand_host *);
	स्थिर काष्ठा mtd_ooblayout_ops *ooblayout;
	व्योम (*select_chip)(काष्ठा nand_chip *chip, पूर्णांक cs);
	पूर्णांक (*setup_पूर्णांकerface)(काष्ठा nand_chip *chip, पूर्णांक csline,
			       स्थिर काष्ठा nand_पूर्णांकerface_config *conf);
	व्योम (*enable_hwecc)(काष्ठा nand_chip *chip, bool enable);

	/*
	 * On i.MX21 the CONFIG2:INT bit cannot be पढ़ो अगर पूर्णांकerrupts are masked
	 * (CONFIG1:INT_MSK is set). To handle this the driver uses
	 * enable_irq/disable_irq_nosync instead of CONFIG1:INT_MSK
	 */
	पूर्णांक irqpending_quirk;
	पूर्णांक needs_ip;

	माप_प्रकार regs_offset;
	माप_प्रकार spare0_offset;
	माप_प्रकार axi_offset;

	पूर्णांक spare_len;
	पूर्णांक eccbytes;
	पूर्णांक eccsize;
	पूर्णांक ppb_shअगरt;
पूर्ण;

काष्ठा mxc_nand_host अणु
	काष्ठा nand_chip	nand;
	काष्ठा device		*dev;

	व्योम __iomem		*spare0;
	व्योम __iomem		*मुख्य_area0;

	व्योम __iomem		*base;
	व्योम __iomem		*regs;
	व्योम __iomem		*regs_axi;
	व्योम __iomem		*regs_ip;
	पूर्णांक			status_request;
	काष्ठा clk		*clk;
	पूर्णांक			clk_act;
	पूर्णांक			irq;
	पूर्णांक			eccsize;
	पूर्णांक			used_oobsize;
	पूर्णांक			active_cs;

	काष्ठा completion	op_completion;

	uपूर्णांक8_t			*data_buf;
	अचिन्हित पूर्णांक		buf_start;

	स्थिर काष्ठा mxc_nand_devtype_data *devtype_data;
पूर्ण;

अटल स्थिर अक्षर * स्थिर part_probes[] = अणु
	"cmdlinepart", "RedBoot", "ofpart", शून्य पूर्ण;

अटल व्योम स_नकल32_fromio(व्योम *trg, स्थिर व्योम __iomem  *src, माप_प्रकार size)
अणु
	पूर्णांक i;
	u32 *t = trg;
	स्थिर __iomem u32 *s = src;

	क्रम (i = 0; i < (size >> 2); i++)
		*t++ = __raw_पढ़ोl(s++);
पूर्ण

अटल व्योम स_नकल16_fromio(व्योम *trg, स्थिर व्योम __iomem  *src, माप_प्रकार size)
अणु
	पूर्णांक i;
	u16 *t = trg;
	स्थिर __iomem u16 *s = src;

	/* We assume that src (IO) is always 32bit aligned */
	अगर (PTR_ALIGN(trg, 4) == trg && IS_ALIGNED(size, 4)) अणु
		स_नकल32_fromio(trg, src, size);
		वापस;
	पूर्ण

	क्रम (i = 0; i < (size >> 1); i++)
		*t++ = __raw_पढ़ोw(s++);
पूर्ण

अटल अंतरभूत व्योम स_नकल32_toio(व्योम __iomem *trg, स्थिर व्योम *src, पूर्णांक size)
अणु
	/* __ioग_लिखो32_copy use 32bit size values so भागide by 4 */
	__ioग_लिखो32_copy(trg, src, size / 4);
पूर्ण

अटल व्योम स_नकल16_toio(व्योम __iomem *trg, स्थिर व्योम *src, पूर्णांक size)
अणु
	पूर्णांक i;
	__iomem u16 *t = trg;
	स्थिर u16 *s = src;

	/* We assume that trg (IO) is always 32bit aligned */
	अगर (PTR_ALIGN(src, 4) == src && IS_ALIGNED(size, 4)) अणु
		स_नकल32_toio(trg, src, size);
		वापस;
	पूर्ण

	क्रम (i = 0; i < (size >> 1); i++)
		__raw_ग_लिखोw(*s++, t++);
पूर्ण

/*
 * The controller splits a page पूर्णांकo data chunks of 512 bytes + partial oob.
 * There are ग_लिखोsize / 512 such chunks, the size of the partial oob parts is
 * oobsize / #chunks rounded करोwn to a multiple of 2. The last oob chunk then
 * contains additionally the byte lost by rounding (अगर any).
 * This function handles the needed shuffling between host->data_buf (which
 * holds a page in natural order, i.e. ग_लिखोsize bytes data + oobsize bytes
 * spare) and the NFC buffer.
 */
अटल व्योम copy_spare(काष्ठा mtd_info *mtd, bool bfrom, व्योम *buf)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(this);
	u16 i, oob_chunk_size;
	u16 num_chunks = mtd->ग_लिखोsize / 512;

	u8 *d = buf;
	u8 __iomem *s = host->spare0;
	u16 sparebuf_size = host->devtype_data->spare_len;

	/* size of oob chunk क्रम all but possibly the last one */
	oob_chunk_size = (host->used_oobsize / num_chunks) & ~1;

	अगर (bfrom) अणु
		क्रम (i = 0; i < num_chunks - 1; i++)
			स_नकल16_fromio(d + i * oob_chunk_size,
					s + i * sparebuf_size,
					oob_chunk_size);

		/* the last chunk */
		स_नकल16_fromio(d + i * oob_chunk_size,
				s + i * sparebuf_size,
				host->used_oobsize - i * oob_chunk_size);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < num_chunks - 1; i++)
			स_नकल16_toio(&s[i * sparebuf_size],
				      &d[i * oob_chunk_size],
				      oob_chunk_size);

		/* the last chunk */
		स_नकल16_toio(&s[i * sparebuf_size],
			      &d[i * oob_chunk_size],
			      host->used_oobsize - i * oob_chunk_size);
	पूर्ण
पूर्ण

/*
 * MXC न_अंकDFC can only perक्रमm full page+spare or spare-only पढ़ो/ग_लिखो.  When
 * the upper layers perक्रमm a पढ़ो/ग_लिखो buf operation, the saved column address
 * is used to index पूर्णांकo the full page. So usually this function is called with
 * column == 0 (unless no column cycle is needed indicated by column == -1)
 */
अटल व्योम mxc_करो_addr_cycle(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);

	/* Write out column address, अगर necessary */
	अगर (column != -1) अणु
		host->devtype_data->send_addr(host, column & 0xff,
					      page_addr == -1);
		अगर (mtd->ग_लिखोsize > 512)
			/* another col addr cycle क्रम 2k page */
			host->devtype_data->send_addr(host,
						      (column >> 8) & 0xff,
						      false);
	पूर्ण

	/* Write out page address, अगर necessary */
	अगर (page_addr != -1) अणु
		/* paddr_0 - p_addr_7 */
		host->devtype_data->send_addr(host, (page_addr & 0xff), false);

		अगर (mtd->ग_लिखोsize > 512) अणु
			अगर (mtd->size >= 0x10000000) अणु
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff,
						false);
				host->devtype_data->send_addr(host,
						(page_addr >> 16) & 0xff,
						true);
			पूर्ण अन्यथा
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff, true);
		पूर्ण अन्यथा अणु
			अगर (nand_chip->options & न_अंकD_ROW_ADDR_3) अणु
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff,
						false);
				host->devtype_data->send_addr(host,
						(page_addr >> 16) & 0xff,
						true);
			पूर्ण अन्यथा
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_पूर्णांक_v3(काष्ठा mxc_nand_host *host)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = पढ़ोl(NFC_V3_IPC);
	अगर (!(पंचांगp & NFC_V3_IPC_INT))
		वापस 0;

	पंचांगp &= ~NFC_V3_IPC_INT;
	ग_लिखोl(पंचांगp, NFC_V3_IPC);

	वापस 1;
पूर्ण

अटल पूर्णांक check_पूर्णांक_v1_v2(काष्ठा mxc_nand_host *host)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = पढ़ोw(NFC_V1_V2_CONFIG2);
	अगर (!(पंचांगp & NFC_V1_V2_CONFIG2_INT))
		वापस 0;

	अगर (!host->devtype_data->irqpending_quirk)
		ग_लिखोw(पंचांगp & ~NFC_V1_V2_CONFIG2_INT, NFC_V1_V2_CONFIG2);

	वापस 1;
पूर्ण

अटल व्योम irq_control_v1_v2(काष्ठा mxc_nand_host *host, पूर्णांक activate)
अणु
	uपूर्णांक16_t पंचांगp;

	पंचांगp = पढ़ोw(NFC_V1_V2_CONFIG1);

	अगर (activate)
		पंचांगp &= ~NFC_V1_V2_CONFIG1_INT_MSK;
	अन्यथा
		पंचांगp |= NFC_V1_V2_CONFIG1_INT_MSK;

	ग_लिखोw(पंचांगp, NFC_V1_V2_CONFIG1);
पूर्ण

अटल व्योम irq_control_v3(काष्ठा mxc_nand_host *host, पूर्णांक activate)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = पढ़ोl(NFC_V3_CONFIG2);

	अगर (activate)
		पंचांगp &= ~NFC_V3_CONFIG2_INT_MSK;
	अन्यथा
		पंचांगp |= NFC_V3_CONFIG2_INT_MSK;

	ग_लिखोl(पंचांगp, NFC_V3_CONFIG2);
पूर्ण

अटल व्योम irq_control(काष्ठा mxc_nand_host *host, पूर्णांक activate)
अणु
	अगर (host->devtype_data->irqpending_quirk) अणु
		अगर (activate)
			enable_irq(host->irq);
		अन्यथा
			disable_irq_nosync(host->irq);
	पूर्ण अन्यथा अणु
		host->devtype_data->irq_control(host, activate);
	पूर्ण
पूर्ण

अटल u32 get_ecc_status_v1(काष्ठा mxc_nand_host *host)
अणु
	वापस पढ़ोw(NFC_V1_V2_ECC_STATUS_RESULT);
पूर्ण

अटल u32 get_ecc_status_v2(काष्ठा mxc_nand_host *host)
अणु
	वापस पढ़ोl(NFC_V1_V2_ECC_STATUS_RESULT);
पूर्ण

अटल u32 get_ecc_status_v3(काष्ठा mxc_nand_host *host)
अणु
	वापस पढ़ोl(NFC_V3_ECC_STATUS_RESULT);
पूर्ण

अटल irqवापस_t mxc_nfc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxc_nand_host *host = dev_id;

	अगर (!host->devtype_data->check_पूर्णांक(host))
		वापस IRQ_NONE;

	irq_control(host, 0);

	complete(&host->op_completion);

	वापस IRQ_HANDLED;
पूर्ण

/* This function polls the न_अंकDFC to रुको क्रम the basic operation to
 * complete by checking the INT bit of config2 रेजिस्टर.
 */
अटल पूर्णांक रुको_op_करोne(काष्ठा mxc_nand_host *host, पूर्णांक useirq)
अणु
	पूर्णांक ret = 0;

	/*
	 * If operation is alपढ़ोy complete, करोn't bother to setup an irq or a
	 * loop.
	 */
	अगर (host->devtype_data->check_पूर्णांक(host))
		वापस 0;

	अगर (useirq) अणु
		अचिन्हित दीर्घ समयout;

		reinit_completion(&host->op_completion);

		irq_control(host, 1);

		समयout = रुको_क्रम_completion_समयout(&host->op_completion, HZ);
		अगर (!समयout && !host->devtype_data->check_पूर्णांक(host)) अणु
			dev_dbg(host->dev, "timeout waiting for irq\n");
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक max_retries = 8000;
		पूर्णांक करोne;

		करो अणु
			udelay(1);

			करोne = host->devtype_data->check_पूर्णांक(host);
			अगर (करोne)
				अवरोध;

		पूर्ण जबतक (--max_retries);

		अगर (!करोne) अणु
			dev_dbg(host->dev, "timeout polling for completion\n");
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण

	WARN_ONCE(ret < 0, "timeout! useirq=%d\n", useirq);

	वापस ret;
पूर्ण

अटल व्योम send_cmd_v3(काष्ठा mxc_nand_host *host, uपूर्णांक16_t cmd, पूर्णांक useirq)
अणु
	/* fill command */
	ग_लिखोl(cmd, NFC_V3_FLASH_CMD);

	/* send out command */
	ग_लिखोl(NFC_CMD, NFC_V3_LAUNCH);

	/* Wait क्रम operation to complete */
	रुको_op_करोne(host, useirq);
पूर्ण

/* This function issues the specअगरied command to the न_अंकD device and
 * रुकोs क्रम completion. */
अटल व्योम send_cmd_v1_v2(काष्ठा mxc_nand_host *host, uपूर्णांक16_t cmd, पूर्णांक useirq)
अणु
	dev_dbg(host->dev, "send_cmd(host, 0x%x, %d)\n", cmd, useirq);

	ग_लिखोw(cmd, NFC_V1_V2_FLASH_CMD);
	ग_लिखोw(NFC_CMD, NFC_V1_V2_CONFIG2);

	अगर (host->devtype_data->irqpending_quirk && (cmd == न_अंकD_CMD_RESET)) अणु
		पूर्णांक max_retries = 100;
		/* Reset completion is indicated by NFC_CONFIG2 */
		/* being set to 0 */
		जबतक (max_retries-- > 0) अणु
			अगर (पढ़ोw(NFC_V1_V2_CONFIG2) == 0) अणु
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण
		अगर (max_retries < 0)
			dev_dbg(host->dev, "%s: RESET failed\n", __func__);
	पूर्ण अन्यथा अणु
		/* Wait क्रम operation to complete */
		रुको_op_करोne(host, useirq);
	पूर्ण
पूर्ण

अटल व्योम send_addr_v3(काष्ठा mxc_nand_host *host, uपूर्णांक16_t addr, पूर्णांक islast)
अणु
	/* fill address */
	ग_लिखोl(addr, NFC_V3_FLASH_ADDR0);

	/* send out address */
	ग_लिखोl(NFC_ADDR, NFC_V3_LAUNCH);

	रुको_op_करोne(host, 0);
पूर्ण

/* This function sends an address (or partial address) to the
 * न_अंकD device. The address is used to select the source/destination क्रम
 * a न_अंकD command. */
अटल व्योम send_addr_v1_v2(काष्ठा mxc_nand_host *host, uपूर्णांक16_t addr, पूर्णांक islast)
अणु
	dev_dbg(host->dev, "send_addr(host, 0x%x %d)\n", addr, islast);

	ग_लिखोw(addr, NFC_V1_V2_FLASH_ADDR);
	ग_लिखोw(NFC_ADDR, NFC_V1_V2_CONFIG2);

	/* Wait क्रम operation to complete */
	रुको_op_करोne(host, islast);
पूर्ण

अटल व्योम send_page_v3(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ops)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uपूर्णांक32_t पंचांगp;

	पंचांगp = पढ़ोl(NFC_V3_CONFIG1);
	पंचांगp &= ~(7 << 4);
	ग_लिखोl(पंचांगp, NFC_V3_CONFIG1);

	/* transfer data from NFC ram to nand */
	ग_लिखोl(ops, NFC_V3_LAUNCH);

	रुको_op_करोne(host, false);
पूर्ण

अटल व्योम send_page_v2(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ops)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);

	/* न_अंकDFC buffer 0 is used क्रम page पढ़ो/ग_लिखो */
	ग_लिखोw(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);

	ग_लिखोw(ops, NFC_V1_V2_CONFIG2);

	/* Wait क्रम operation to complete */
	रुको_op_करोne(host, true);
पूर्ण

अटल व्योम send_page_v1(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ops)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	पूर्णांक bufs, i;

	अगर (mtd->ग_लिखोsize > 512)
		bufs = 4;
	अन्यथा
		bufs = 1;

	क्रम (i = 0; i < bufs; i++) अणु

		/* न_अंकDFC buffer 0 is used क्रम page पढ़ो/ग_लिखो */
		ग_लिखोw((host->active_cs << 4) | i, NFC_V1_V2_BUF_ADDR);

		ग_लिखोw(ops, NFC_V1_V2_CONFIG2);

		/* Wait क्रम operation to complete */
		रुको_op_करोne(host, true);
	पूर्ण
पूर्ण

अटल व्योम send_पढ़ो_id_v3(काष्ठा mxc_nand_host *host)
अणु
	/* Read ID पूर्णांकo मुख्य buffer */
	ग_लिखोl(NFC_ID, NFC_V3_LAUNCH);

	रुको_op_करोne(host, true);

	स_नकल32_fromio(host->data_buf, host->मुख्य_area0, 16);
पूर्ण

/* Request the न_अंकDFC to perक्रमm a पढ़ो of the न_अंकD device ID. */
अटल व्योम send_पढ़ो_id_v1_v2(काष्ठा mxc_nand_host *host)
अणु
	/* न_अंकDFC buffer 0 is used क्रम device ID output */
	ग_लिखोw(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);

	ग_लिखोw(NFC_ID, NFC_V1_V2_CONFIG2);

	/* Wait क्रम operation to complete */
	रुको_op_करोne(host, true);

	स_नकल32_fromio(host->data_buf, host->मुख्य_area0, 16);
पूर्ण

अटल uपूर्णांक16_t get_dev_status_v3(काष्ठा mxc_nand_host *host)
अणु
	ग_लिखोw(NFC_STATUS, NFC_V3_LAUNCH);
	रुको_op_करोne(host, true);

	वापस पढ़ोl(NFC_V3_CONFIG1) >> 16;
पूर्ण

/* This function requests the न_अंकDFC to perक्रमm a पढ़ो of the
 * न_अंकD device status and वापसs the current status. */
अटल uपूर्णांक16_t get_dev_status_v1_v2(काष्ठा mxc_nand_host *host)
अणु
	व्योम __iomem *मुख्य_buf = host->मुख्य_area0;
	uपूर्णांक32_t store;
	uपूर्णांक16_t ret;

	ग_लिखोw(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);

	/*
	 * The device status is stored in मुख्य_area0. To
	 * prevent corruption of the buffer save the value
	 * and restore it afterwards.
	 */
	store = पढ़ोl(मुख्य_buf);

	ग_लिखोw(NFC_STATUS, NFC_V1_V2_CONFIG2);
	रुको_op_करोne(host, true);

	ret = पढ़ोw(मुख्य_buf);

	ग_लिखोl(store, मुख्य_buf);

	वापस ret;
पूर्ण

अटल व्योम mxc_nand_enable_hwecc_v1_v2(काष्ठा nand_chip *chip, bool enable)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	uपूर्णांक16_t config1;

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस;

	config1 = पढ़ोw(NFC_V1_V2_CONFIG1);

	अगर (enable)
		config1 |= NFC_V1_V2_CONFIG1_ECC_EN;
	अन्यथा
		config1 &= ~NFC_V1_V2_CONFIG1_ECC_EN;

	ग_लिखोw(config1, NFC_V1_V2_CONFIG1);
पूर्ण

अटल व्योम mxc_nand_enable_hwecc_v3(काष्ठा nand_chip *chip, bool enable)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	uपूर्णांक32_t config2;

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस;

	config2 = पढ़ोl(NFC_V3_CONFIG2);

	अगर (enable)
		config2 |= NFC_V3_CONFIG2_ECC_EN;
	अन्यथा
		config2 &= ~NFC_V3_CONFIG2_ECC_EN;

	ग_लिखोl(config2, NFC_V3_CONFIG2);
पूर्ण

/* This functions is used by upper layer to checks अगर device is पढ़ोy */
अटल पूर्णांक mxc_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	/*
	 * NFC handles R/B पूर्णांकernally. Thereक्रमe, this function
	 * always वापसs status as पढ़ोy.
	 */
	वापस 1;
पूर्ण

अटल पूर्णांक mxc_nand_पढ़ो_page_v1(काष्ठा nand_chip *chip, व्योम *buf, व्योम *oob,
				 bool ecc, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक bitflips_corrected = 0;
	पूर्णांक no_subpages;
	पूर्णांक i;

	host->devtype_data->enable_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, न_अंकD_CMD_READ0, false);
	mxc_करो_addr_cycle(mtd, 0, page);

	अगर (mtd->ग_लिखोsize > 512)
		host->devtype_data->send_cmd(host, न_अंकD_CMD_READSTART, true);

	no_subpages = mtd->ग_लिखोsize >> 9;

	क्रम (i = 0; i < no_subpages; i++) अणु
		uपूर्णांक16_t ecc_stats;

		/* न_अंकDFC buffer 0 is used क्रम page पढ़ो/ग_लिखो */
		ग_लिखोw((host->active_cs << 4) | i, NFC_V1_V2_BUF_ADDR);

		ग_लिखोw(NFC_OUTPUT, NFC_V1_V2_CONFIG2);

		/* Wait क्रम operation to complete */
		रुको_op_करोne(host, true);

		ecc_stats = get_ecc_status_v1(host);

		ecc_stats >>= 2;

		अगर (buf && ecc) अणु
			चयन (ecc_stats & 0x3) अणु
			हाल 0:
			शेष:
				अवरोध;
			हाल 1:
				mtd->ecc_stats.corrected++;
				bitflips_corrected = 1;
				अवरोध;
			हाल 2:
				mtd->ecc_stats.failed++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (buf)
		स_नकल32_fromio(buf, host->मुख्य_area0, mtd->ग_लिखोsize);
	अगर (oob)
		copy_spare(mtd, true, oob);

	वापस bitflips_corrected;
पूर्ण

अटल पूर्णांक mxc_nand_पढ़ो_page_v2_v3(काष्ठा nand_chip *chip, व्योम *buf,
				    व्योम *oob, bool ecc, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक max_bitflips = 0;
	u32 ecc_stat, err;
	पूर्णांक no_subpages;
	u8 ecc_bit_mask, err_limit;

	host->devtype_data->enable_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, न_अंकD_CMD_READ0, false);
	mxc_करो_addr_cycle(mtd, 0, page);

	अगर (mtd->ग_लिखोsize > 512)
		host->devtype_data->send_cmd(host,
				न_अंकD_CMD_READSTART, true);

	host->devtype_data->send_page(mtd, NFC_OUTPUT);

	अगर (buf)
		स_नकल32_fromio(buf, host->मुख्य_area0, mtd->ग_लिखोsize);
	अगर (oob)
		copy_spare(mtd, true, oob);

	ecc_bit_mask = (host->eccsize == 4) ? 0x7 : 0xf;
	err_limit = (host->eccsize == 4) ? 0x4 : 0x8;

	no_subpages = mtd->ग_लिखोsize >> 9;

	ecc_stat = host->devtype_data->get_ecc_status(host);

	करो अणु
		err = ecc_stat & ecc_bit_mask;
		अगर (err > err_limit) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += err;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, err);
		पूर्ण

		ecc_stat >>= 4;
	पूर्ण जबतक (--no_subpages);

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक mxc_nand_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	व्योम *oob_buf;

	अगर (oob_required)
		oob_buf = chip->oob_poi;
	अन्यथा
		oob_buf = शून्य;

	वापस host->devtype_data->पढ़ो_page(chip, buf, oob_buf, 1, page);
पूर्ण

अटल पूर्णांक mxc_nand_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	व्योम *oob_buf;

	अगर (oob_required)
		oob_buf = chip->oob_poi;
	अन्यथा
		oob_buf = शून्य;

	वापस host->devtype_data->पढ़ो_page(chip, buf, oob_buf, 0, page);
पूर्ण

अटल पूर्णांक mxc_nand_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);

	वापस host->devtype_data->पढ़ो_page(chip, शून्य, chip->oob_poi, 0,
					     page);
पूर्ण

अटल पूर्णांक mxc_nand_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       bool ecc, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);

	host->devtype_data->enable_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, न_अंकD_CMD_SEQIN, false);
	mxc_करो_addr_cycle(mtd, 0, page);

	स_नकल32_toio(host->मुख्य_area0, buf, mtd->ग_लिखोsize);
	copy_spare(mtd, false, chip->oob_poi);

	host->devtype_data->send_page(mtd, NFC_INPUT);
	host->devtype_data->send_cmd(host, न_अंकD_CMD_PAGEPROG, true);
	mxc_करो_addr_cycle(mtd, 0, page);

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_nand_ग_लिखो_page_ecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस mxc_nand_ग_लिखो_page(chip, buf, true, page);
पूर्ण

अटल पूर्णांक mxc_nand_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस mxc_nand_ग_लिखो_page(chip, buf, false, page);
पूर्ण

अटल पूर्णांक mxc_nand_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);

	स_रखो(host->data_buf, 0xff, mtd->ग_लिखोsize);

	वापस mxc_nand_ग_लिखो_page(chip, host->data_buf, false, page);
पूर्ण

अटल u_अक्षर mxc_nand_पढ़ो_byte(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uपूर्णांक8_t ret;

	/* Check क्रम status request */
	अगर (host->status_request)
		वापस host->devtype_data->get_dev_status(host) & 0xFF;

	अगर (nand_chip->options & न_अंकD_BUSWIDTH_16) अणु
		/* only take the lower byte of each word */
		ret = *(uपूर्णांक16_t *)(host->data_buf + host->buf_start);

		host->buf_start += 2;
	पूर्ण अन्यथा अणु
		ret = *(uपूर्णांक8_t *)(host->data_buf + host->buf_start);
		host->buf_start++;
	पूर्ण

	dev_dbg(host->dev, "%s: ret=0x%hhx (start=%u)\n", __func__, ret, host->buf_start);
	वापस ret;
पूर्ण

/* Write data of length len to buffer buf. The data to be
 * written on न_अंकD Flash is first copied to RAMbuffer. After the Data Input
 * Operation by the NFC, the data is written to न_अंकD Flash */
अटल व्योम mxc_nand_ग_लिखो_buf(काष्ठा nand_chip *nand_chip, स्थिर u_अक्षर *buf,
			       पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand_chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	u16 col = host->buf_start;
	पूर्णांक n = mtd->oobsize + mtd->ग_लिखोsize - col;

	n = min(n, len);

	स_नकल(host->data_buf + col, buf, n);

	host->buf_start += n;
पूर्ण

/* Read the data buffer from the न_अंकD Flash. To पढ़ो the data from न_अंकD
 * Flash first the data output cycle is initiated by the NFC, which copies
 * the data to RAMbuffer. This data of length len is then copied to buffer buf.
 */
अटल व्योम mxc_nand_पढ़ो_buf(काष्ठा nand_chip *nand_chip, u_अक्षर *buf,
			      पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand_chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	u16 col = host->buf_start;
	पूर्णांक n = mtd->oobsize + mtd->ग_लिखोsize - col;

	n = min(n, len);

	स_नकल(buf, host->data_buf + col, n);

	host->buf_start += n;
पूर्ण

/* This function is used by upper layer क्रम select and
 * deselect of the न_अंकD chip */
अटल व्योम mxc_nand_select_chip_v1_v3(काष्ठा nand_chip *nand_chip, पूर्णांक chip)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);

	अगर (chip == -1) अणु
		/* Disable the NFC घड़ी */
		अगर (host->clk_act) अणु
			clk_disable_unprepare(host->clk);
			host->clk_act = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!host->clk_act) अणु
		/* Enable the NFC घड़ी */
		clk_prepare_enable(host->clk);
		host->clk_act = 1;
	पूर्ण
पूर्ण

अटल व्योम mxc_nand_select_chip_v2(काष्ठा nand_chip *nand_chip, पूर्णांक chip)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);

	अगर (chip == -1) अणु
		/* Disable the NFC घड़ी */
		अगर (host->clk_act) अणु
			clk_disable_unprepare(host->clk);
			host->clk_act = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!host->clk_act) अणु
		/* Enable the NFC घड़ी */
		clk_prepare_enable(host->clk);
		host->clk_act = 1;
	पूर्ण

	host->active_cs = chip;
	ग_लिखोw(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);
पूर्ण

#घोषणा MXC_V1_ECCBYTES		5

अटल पूर्णांक mxc_v1_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);

	अगर (section >= nand_chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 6;
	oobregion->length = MXC_V1_ECCBYTES;

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_v1_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);

	अगर (section > nand_chip->ecc.steps)
		वापस -दुस्फल;

	अगर (!section) अणु
		अगर (mtd->ग_लिखोsize <= 512) अणु
			oobregion->offset = 0;
			oobregion->length = 5;
		पूर्ण अन्यथा अणु
			oobregion->offset = 2;
			oobregion->length = 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		oobregion->offset = ((section - 1) * 16) + MXC_V1_ECCBYTES + 6;
		अगर (section < nand_chip->ecc.steps)
			oobregion->length = (section * 16) + 6 -
					    oobregion->offset;
		अन्यथा
			oobregion->length = mtd->oobsize - oobregion->offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops mxc_v1_ooblayout_ops = अणु
	.ecc = mxc_v1_ooblayout_ecc,
	.मुक्त = mxc_v1_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक mxc_v2_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	पूर्णांक stepsize = nand_chip->ecc.bytes == 9 ? 16 : 26;

	अगर (section >= nand_chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * stepsize) + 7;
	oobregion->length = nand_chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_v2_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	पूर्णांक stepsize = nand_chip->ecc.bytes == 9 ? 16 : 26;

	अगर (section >= nand_chip->ecc.steps)
		वापस -दुस्फल;

	अगर (!section) अणु
		अगर (mtd->ग_लिखोsize <= 512) अणु
			oobregion->offset = 0;
			oobregion->length = 5;
		पूर्ण अन्यथा अणु
			oobregion->offset = 2;
			oobregion->length = 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		oobregion->offset = section * stepsize;
		oobregion->length = 7;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops mxc_v2_ooblayout_ops = अणु
	.ecc = mxc_v2_ooblayout_ecc,
	.मुक्त = mxc_v2_ooblayout_मुक्त,
पूर्ण;

/*
 * v2 and v3 type controllers can करो 4bit or 8bit ecc depending
 * on how much oob the nand chip has. For 8bit ecc we need at least
 * 26 bytes of oob data per 512 byte block.
 */
अटल पूर्णांक get_eccsize(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक oobbytes_per_512 = 0;

	oobbytes_per_512 = mtd->oobsize * 512 / mtd->ग_लिखोsize;

	अगर (oobbytes_per_512 < 26)
		वापस 4;
	अन्यथा
		वापस 8;
पूर्ण

अटल व्योम preset_v1(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uपूर्णांक16_t config1 = 0;

	अगर (nand_chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST &&
	    mtd->ग_लिखोsize)
		config1 |= NFC_V1_V2_CONFIG1_ECC_EN;

	अगर (!host->devtype_data->irqpending_quirk)
		config1 |= NFC_V1_V2_CONFIG1_INT_MSK;

	host->eccsize = 1;

	ग_लिखोw(config1, NFC_V1_V2_CONFIG1);
	/* preset operation */

	/* Unlock the पूर्णांकernal RAM Buffer */
	ग_लिखोw(0x2, NFC_V1_V2_CONFIG);

	/* Blocks to be unlocked */
	ग_लिखोw(0x0, NFC_V1_UNLOCKSTART_BLKADDR);
	ग_लिखोw(0xffff, NFC_V1_UNLOCKEND_BLKADDR);

	/* Unlock Block Command क्रम given address range */
	ग_लिखोw(0x4, NFC_V1_V2_WRPROT);
पूर्ण

अटल पूर्णांक mxc_nand_v2_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक csline,
				       स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक tRC_min_ns, tRC_ps, ret;
	अचिन्हित दीर्घ rate, rate_round;
	स्थिर काष्ठा nand_sdr_timings *timings;
	u16 config1;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -ENOTSUPP;

	config1 = पढ़ोw(NFC_V1_V2_CONFIG1);

	tRC_min_ns = timings->tRC_min / 1000;
	rate = 1000000000 / tRC_min_ns;

	/*
	 * For tRC < 30ns we have to use EDO mode. In this हाल the controller
	 * करोes one access per घड़ी cycle. Otherwise the controller करोes one
	 * access in two घड़ी cycles, thus we have to द्विगुन the rate to the
	 * controller.
	 */
	अगर (tRC_min_ns < 30) अणु
		rate_round = clk_round_rate(host->clk, rate);
		config1 |= NFC_V2_CONFIG1_ONE_CYCLE;
		tRC_ps = 1000000000 / (rate_round / 1000);
	पूर्ण अन्यथा अणु
		rate *= 2;
		rate_round = clk_round_rate(host->clk, rate);
		config1 &= ~NFC_V2_CONFIG1_ONE_CYCLE;
		tRC_ps = 1000000000 / (rate_round / 1000 / 2);
	पूर्ण

	/*
	 * The timing values compared against are from the i.MX25 Automotive
	 * datasheet, Table 50. NFC Timing Parameters
	 */
	अगर (timings->tCLS_min > tRC_ps - 1000 ||
	    timings->tCLH_min > tRC_ps - 2000 ||
	    timings->tCS_min > tRC_ps - 1000 ||
	    timings->tCH_min > tRC_ps - 2000 ||
	    timings->tWP_min > tRC_ps - 1500 ||
	    timings->tALS_min > tRC_ps ||
	    timings->tALH_min > tRC_ps - 3000 ||
	    timings->tDS_min > tRC_ps ||
	    timings->tDH_min > tRC_ps - 5000 ||
	    timings->tWC_min > 2 * tRC_ps ||
	    timings->tWH_min > tRC_ps - 2500 ||
	    timings->tRR_min > 6 * tRC_ps ||
	    timings->tRP_min > 3 * tRC_ps / 2 ||
	    timings->tRC_min > 2 * tRC_ps ||
	    timings->tREH_min > (tRC_ps / 2) - 2500) अणु
		dev_dbg(host->dev, "Timing out of bounds\n");
		वापस -EINVAL;
	पूर्ण

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	ret = clk_set_rate(host->clk, rate);
	अगर (ret)
		वापस ret;

	ग_लिखोw(config1, NFC_V1_V2_CONFIG1);

	dev_dbg(host->dev, "Setting rate to %ldHz, %s mode\n", rate_round,
		config1 & NFC_V2_CONFIG1_ONE_CYCLE ? "One cycle (EDO)" :
		"normal");

	वापस 0;
पूर्ण

अटल व्योम preset_v2(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uपूर्णांक16_t config1 = 0;

	config1 |= NFC_V2_CONFIG1_FP_INT;

	अगर (!host->devtype_data->irqpending_quirk)
		config1 |= NFC_V1_V2_CONFIG1_INT_MSK;

	अगर (mtd->ग_लिखोsize) अणु
		uपूर्णांक16_t pages_per_block = mtd->erasesize / mtd->ग_लिखोsize;

		अगर (nand_chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
			config1 |= NFC_V1_V2_CONFIG1_ECC_EN;

		host->eccsize = get_eccsize(mtd);
		अगर (host->eccsize == 4)
			config1 |= NFC_V2_CONFIG1_ECC_MODE_4;

		config1 |= NFC_V2_CONFIG1_PPB(ffs(pages_per_block) - 6);
	पूर्ण अन्यथा अणु
		host->eccsize = 1;
	पूर्ण

	ग_लिखोw(config1, NFC_V1_V2_CONFIG1);
	/* preset operation */

	/* spare area size in 16-bit half-words */
	ग_लिखोw(mtd->oobsize / 2, NFC_V21_RSLTSPARE_AREA);

	/* Unlock the पूर्णांकernal RAM Buffer */
	ग_लिखोw(0x2, NFC_V1_V2_CONFIG);

	/* Blocks to be unlocked */
	ग_लिखोw(0x0, NFC_V21_UNLOCKSTART_BLKADDR0);
	ग_लिखोw(0x0, NFC_V21_UNLOCKSTART_BLKADDR1);
	ग_लिखोw(0x0, NFC_V21_UNLOCKSTART_BLKADDR2);
	ग_लिखोw(0x0, NFC_V21_UNLOCKSTART_BLKADDR3);
	ग_लिखोw(0xffff, NFC_V21_UNLOCKEND_BLKADDR0);
	ग_लिखोw(0xffff, NFC_V21_UNLOCKEND_BLKADDR1);
	ग_लिखोw(0xffff, NFC_V21_UNLOCKEND_BLKADDR2);
	ग_लिखोw(0xffff, NFC_V21_UNLOCKEND_BLKADDR3);

	/* Unlock Block Command क्रम given address range */
	ग_लिखोw(0x4, NFC_V1_V2_WRPROT);
पूर्ण

अटल व्योम preset_v3(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	uपूर्णांक32_t config2, config3;
	पूर्णांक i, addr_phases;

	ग_लिखोl(NFC_V3_CONFIG1_RBA(0), NFC_V3_CONFIG1);
	ग_लिखोl(NFC_V3_IPC_CREQ, NFC_V3_IPC);

	/* Unlock the पूर्णांकernal RAM Buffer */
	ग_लिखोl(NFC_V3_WRPROT_BLS_UNLOCK | NFC_V3_WRPROT_UNLOCK,
			NFC_V3_WRPROT);

	/* Blocks to be unlocked */
	क्रम (i = 0; i < न_अंकD_MAX_CHIPS; i++)
		ग_लिखोl(0xffff << 16, NFC_V3_WRPROT_UNLOCK_BLK_ADD0 + (i << 2));

	ग_लिखोl(0, NFC_V3_IPC);

	config2 = NFC_V3_CONFIG2_ONE_CYCLE |
		NFC_V3_CONFIG2_2CMD_PHASES |
		NFC_V3_CONFIG2_SPAS(mtd->oobsize >> 1) |
		NFC_V3_CONFIG2_ST_CMD(0x70) |
		NFC_V3_CONFIG2_INT_MSK |
		NFC_V3_CONFIG2_NUM_ADDR_PHASE0;

	addr_phases = fls(chip->pagemask) >> 3;

	अगर (mtd->ग_लिखोsize == 2048) अणु
		config2 |= NFC_V3_CONFIG2_PS_2048;
		config2 |= NFC_V3_CONFIG2_NUM_ADDR_PHASE1(addr_phases);
	पूर्ण अन्यथा अगर (mtd->ग_लिखोsize == 4096) अणु
		config2 |= NFC_V3_CONFIG2_PS_4096;
		config2 |= NFC_V3_CONFIG2_NUM_ADDR_PHASE1(addr_phases);
	पूर्ण अन्यथा अणु
		config2 |= NFC_V3_CONFIG2_PS_512;
		config2 |= NFC_V3_CONFIG2_NUM_ADDR_PHASE1(addr_phases - 1);
	पूर्ण

	अगर (mtd->ग_लिखोsize) अणु
		अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
			config2 |= NFC_V3_CONFIG2_ECC_EN;

		config2 |= NFC_V3_CONFIG2_PPB(
				ffs(mtd->erasesize / mtd->ग_लिखोsize) - 6,
				host->devtype_data->ppb_shअगरt);
		host->eccsize = get_eccsize(mtd);
		अगर (host->eccsize == 8)
			config2 |= NFC_V3_CONFIG2_ECC_MODE_8;
	पूर्ण

	ग_लिखोl(config2, NFC_V3_CONFIG2);

	config3 = NFC_V3_CONFIG3_NUM_OF_DEVICES(0) |
			NFC_V3_CONFIG3_NO_SDMA |
			NFC_V3_CONFIG3_RBB_MODE |
			NFC_V3_CONFIG3_SBB(6) | /* Reset शेष */
			NFC_V3_CONFIG3_ADD_OP(0);

	अगर (!(chip->options & न_अंकD_BUSWIDTH_16))
		config3 |= NFC_V3_CONFIG3_FW8;

	ग_लिखोl(config3, NFC_V3_CONFIG3);

	ग_लिखोl(0, NFC_V3_DELAY_LINE);
पूर्ण

/* Used by the upper layer to ग_लिखो command to न_अंकD Flash क्रम
 * dअगरferent operations to be carried out on न_अंकD Flash */
अटल व्योम mxc_nand_command(काष्ठा nand_chip *nand_chip, अचिन्हित command,
			     पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand_chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(nand_chip);

	dev_dbg(host->dev, "mxc_nand_command (cmd = 0x%x, col = 0x%x, page = 0x%x)\n",
	      command, column, page_addr);

	/* Reset command state inक्रमmation */
	host->status_request = false;

	/* Command pre-processing step */
	चयन (command) अणु
	हाल न_अंकD_CMD_RESET:
		host->devtype_data->preset(mtd);
		host->devtype_data->send_cmd(host, command, false);
		अवरोध;

	हाल न_अंकD_CMD_STATUS:
		host->buf_start = 0;
		host->status_request = true;

		host->devtype_data->send_cmd(host, command, true);
		WARN_ONCE(column != -1 || page_addr != -1,
			  "Unexpected column/row value (cmd=%u, col=%d, row=%d)\n",
			  command, column, page_addr);
		mxc_करो_addr_cycle(mtd, column, page_addr);
		अवरोध;

	हाल न_अंकD_CMD_READID:
		host->devtype_data->send_cmd(host, command, true);
		mxc_करो_addr_cycle(mtd, column, page_addr);
		host->devtype_data->send_पढ़ो_id(host);
		host->buf_start = 0;
		अवरोध;

	हाल न_अंकD_CMD_ERASE1:
	हाल न_अंकD_CMD_ERASE2:
		host->devtype_data->send_cmd(host, command, false);
		WARN_ONCE(column != -1,
			  "Unexpected column value (cmd=%u, col=%d)\n",
			  command, column);
		mxc_करो_addr_cycle(mtd, column, page_addr);

		अवरोध;
	हाल न_अंकD_CMD_PARAM:
		host->devtype_data->send_cmd(host, command, false);
		mxc_करो_addr_cycle(mtd, column, page_addr);
		host->devtype_data->send_page(mtd, NFC_OUTPUT);
		स_नकल32_fromio(host->data_buf, host->मुख्य_area0, 512);
		host->buf_start = 0;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Unimplemented command (cmd=%u)\n",
			  command);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mxc_nand_set_features(काष्ठा nand_chip *chip, पूर्णांक addr,
				 u8 *subfeature_param)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक i;

	host->buf_start = 0;

	क्रम (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		chip->legacy.ग_लिखो_byte(chip, subfeature_param[i]);

	स_नकल32_toio(host->मुख्य_area0, host->data_buf, mtd->ग_लिखोsize);
	host->devtype_data->send_cmd(host, न_अंकD_CMD_SET_FEATURES, false);
	mxc_करो_addr_cycle(mtd, addr, -1);
	host->devtype_data->send_page(mtd, NFC_INPUT);

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_nand_get_features(काष्ठा nand_chip *chip, पूर्णांक addr,
				 u8 *subfeature_param)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक i;

	host->devtype_data->send_cmd(host, न_अंकD_CMD_GET_FEATURES, false);
	mxc_करो_addr_cycle(mtd, addr, -1);
	host->devtype_data->send_page(mtd, NFC_OUTPUT);
	स_नकल32_fromio(host->data_buf, host->मुख्य_area0, 512);
	host->buf_start = 0;

	क्रम (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		*subfeature_param++ = chip->legacy.पढ़ो_byte(chip);

	वापस 0;
पूर्ण

/*
 * The generic flash bbt descriptors overlap with our ecc
 * hardware, so define some i.MX specअगरic ones.
 */
अटल uपूर्णांक8_t bbt_pattern[] = अणु 'B', 'b', 't', '0' पूर्ण;
अटल uपूर्णांक8_t mirror_pattern[] = अणु '1', 't', 'b', 'B' पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
	    | न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs = 0,
	.len = 4,
	.veroffs = 4,
	.maxblocks = 4,
	.pattern = bbt_pattern,
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
	    | न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs = 0,
	.len = 4,
	.veroffs = 4,
	.maxblocks = 4,
	.pattern = mirror_pattern,
पूर्ण;

/* v1 + irqpending_quirk: i.MX21 */
अटल स्थिर काष्ठा mxc_nand_devtype_data imx21_nand_devtype_data = अणु
	.preset = preset_v1,
	.पढ़ो_page = mxc_nand_पढ़ो_page_v1,
	.send_cmd = send_cmd_v1_v2,
	.send_addr = send_addr_v1_v2,
	.send_page = send_page_v1,
	.send_पढ़ो_id = send_पढ़ो_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_पूर्णांक = check_पूर्णांक_v1_v2,
	.irq_control = irq_control_v1_v2,
	.get_ecc_status = get_ecc_status_v1,
	.ooblayout = &mxc_v1_ooblayout_ops,
	.select_chip = mxc_nand_select_chip_v1_v3,
	.enable_hwecc = mxc_nand_enable_hwecc_v1_v2,
	.irqpending_quirk = 1,
	.needs_ip = 0,
	.regs_offset = 0xe00,
	.spare0_offset = 0x800,
	.spare_len = 16,
	.eccbytes = 3,
	.eccsize = 1,
पूर्ण;

/* v1 + !irqpending_quirk: i.MX27, i.MX31 */
अटल स्थिर काष्ठा mxc_nand_devtype_data imx27_nand_devtype_data = अणु
	.preset = preset_v1,
	.पढ़ो_page = mxc_nand_पढ़ो_page_v1,
	.send_cmd = send_cmd_v1_v2,
	.send_addr = send_addr_v1_v2,
	.send_page = send_page_v1,
	.send_पढ़ो_id = send_पढ़ो_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_पूर्णांक = check_पूर्णांक_v1_v2,
	.irq_control = irq_control_v1_v2,
	.get_ecc_status = get_ecc_status_v1,
	.ooblayout = &mxc_v1_ooblayout_ops,
	.select_chip = mxc_nand_select_chip_v1_v3,
	.enable_hwecc = mxc_nand_enable_hwecc_v1_v2,
	.irqpending_quirk = 0,
	.needs_ip = 0,
	.regs_offset = 0xe00,
	.spare0_offset = 0x800,
	.axi_offset = 0,
	.spare_len = 16,
	.eccbytes = 3,
	.eccsize = 1,
पूर्ण;

/* v21: i.MX25, i.MX35 */
अटल स्थिर काष्ठा mxc_nand_devtype_data imx25_nand_devtype_data = अणु
	.preset = preset_v2,
	.पढ़ो_page = mxc_nand_पढ़ो_page_v2_v3,
	.send_cmd = send_cmd_v1_v2,
	.send_addr = send_addr_v1_v2,
	.send_page = send_page_v2,
	.send_पढ़ो_id = send_पढ़ो_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_पूर्णांक = check_पूर्णांक_v1_v2,
	.irq_control = irq_control_v1_v2,
	.get_ecc_status = get_ecc_status_v2,
	.ooblayout = &mxc_v2_ooblayout_ops,
	.select_chip = mxc_nand_select_chip_v2,
	.setup_पूर्णांकerface = mxc_nand_v2_setup_पूर्णांकerface,
	.enable_hwecc = mxc_nand_enable_hwecc_v1_v2,
	.irqpending_quirk = 0,
	.needs_ip = 0,
	.regs_offset = 0x1e00,
	.spare0_offset = 0x1000,
	.axi_offset = 0,
	.spare_len = 64,
	.eccbytes = 9,
	.eccsize = 0,
पूर्ण;

/* v3.2a: i.MX51 */
अटल स्थिर काष्ठा mxc_nand_devtype_data imx51_nand_devtype_data = अणु
	.preset = preset_v3,
	.पढ़ो_page = mxc_nand_पढ़ो_page_v2_v3,
	.send_cmd = send_cmd_v3,
	.send_addr = send_addr_v3,
	.send_page = send_page_v3,
	.send_पढ़ो_id = send_पढ़ो_id_v3,
	.get_dev_status = get_dev_status_v3,
	.check_पूर्णांक = check_पूर्णांक_v3,
	.irq_control = irq_control_v3,
	.get_ecc_status = get_ecc_status_v3,
	.ooblayout = &mxc_v2_ooblayout_ops,
	.select_chip = mxc_nand_select_chip_v1_v3,
	.enable_hwecc = mxc_nand_enable_hwecc_v3,
	.irqpending_quirk = 0,
	.needs_ip = 1,
	.regs_offset = 0,
	.spare0_offset = 0x1000,
	.axi_offset = 0x1e00,
	.spare_len = 64,
	.eccbytes = 0,
	.eccsize = 0,
	.ppb_shअगरt = 7,
पूर्ण;

/* v3.2b: i.MX53 */
अटल स्थिर काष्ठा mxc_nand_devtype_data imx53_nand_devtype_data = अणु
	.preset = preset_v3,
	.पढ़ो_page = mxc_nand_पढ़ो_page_v2_v3,
	.send_cmd = send_cmd_v3,
	.send_addr = send_addr_v3,
	.send_page = send_page_v3,
	.send_पढ़ो_id = send_पढ़ो_id_v3,
	.get_dev_status = get_dev_status_v3,
	.check_पूर्णांक = check_पूर्णांक_v3,
	.irq_control = irq_control_v3,
	.get_ecc_status = get_ecc_status_v3,
	.ooblayout = &mxc_v2_ooblayout_ops,
	.select_chip = mxc_nand_select_chip_v1_v3,
	.enable_hwecc = mxc_nand_enable_hwecc_v3,
	.irqpending_quirk = 0,
	.needs_ip = 1,
	.regs_offset = 0,
	.spare0_offset = 0x1000,
	.axi_offset = 0x1e00,
	.spare_len = 64,
	.eccbytes = 0,
	.eccsize = 0,
	.ppb_shअगरt = 8,
पूर्ण;

अटल अंतरभूत पूर्णांक is_imx21_nfc(काष्ठा mxc_nand_host *host)
अणु
	वापस host->devtype_data == &imx21_nand_devtype_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx27_nfc(काष्ठा mxc_nand_host *host)
अणु
	वापस host->devtype_data == &imx27_nand_devtype_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx25_nfc(काष्ठा mxc_nand_host *host)
अणु
	वापस host->devtype_data == &imx25_nand_devtype_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx51_nfc(काष्ठा mxc_nand_host *host)
अणु
	वापस host->devtype_data == &imx51_nand_devtype_data;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx53_nfc(काष्ठा mxc_nand_host *host)
अणु
	वापस host->devtype_data == &imx53_nand_devtype_data;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxcnd_dt_ids[] = अणु
	अणु .compatible = "fsl,imx21-nand", .data = &imx21_nand_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx27-nand", .data = &imx27_nand_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx25-nand", .data = &imx25_nand_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx51-nand", .data = &imx51_nand_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx53-nand", .data = &imx53_nand_devtype_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxcnd_dt_ids);

अटल पूर्णांक mxcnd_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);
	काष्ठा device *dev = mtd->dev.parent;

	chip->ecc.bytes = host->devtype_data->eccbytes;
	host->eccsize = host->devtype_data->eccsize;
	chip->ecc.size = 512;
	mtd_set_ooblayout(mtd, host->devtype_data->ooblayout);

	चयन (chip->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		chip->ecc.पढ़ो_page = mxc_nand_पढ़ो_page;
		chip->ecc.पढ़ो_page_raw = mxc_nand_पढ़ो_page_raw;
		chip->ecc.पढ़ो_oob = mxc_nand_पढ़ो_oob;
		chip->ecc.ग_लिखो_page = mxc_nand_ग_लिखो_page_ecc;
		chip->ecc.ग_लिखो_page_raw = mxc_nand_ग_लिखो_page_raw;
		chip->ecc.ग_लिखो_oob = mxc_nand_ग_लिखो_oob;
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH) अणु
		chip->bbt_td = &bbt_मुख्य_descr;
		chip->bbt_md = &bbt_mirror_descr;
	पूर्ण

	/* Allocate the right size buffer now */
	devm_kमुक्त(dev, (व्योम *)host->data_buf);
	host->data_buf = devm_kzalloc(dev, mtd->ग_लिखोsize + mtd->oobsize,
				      GFP_KERNEL);
	अगर (!host->data_buf)
		वापस -ENOMEM;

	/* Call preset again, with correct ग_लिखोsize chip समय */
	host->devtype_data->preset(mtd);

	अगर (!chip->ecc.bytes) अणु
		अगर (host->eccsize == 8)
			chip->ecc.bytes = 18;
		अन्यथा अगर (host->eccsize == 4)
			chip->ecc.bytes = 9;
	पूर्ण

	/*
	 * Experimentation shows that i.MX NFC can only handle up to 218 oob
	 * bytes. Limit used_oobsize to 218 so as to not confuse copy_spare()
	 * पूर्णांकo copying invalid data to/from the spare IO buffer, as this
	 * might cause ECC data corruption when करोing sub-page ग_लिखो to a
	 * partially written page.
	 */
	host->used_oobsize = min(mtd->oobsize, 218U);

	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		अगर (is_imx21_nfc(host) || is_imx27_nfc(host))
			chip->ecc.strength = 1;
		अन्यथा
			chip->ecc.strength = (host->eccsize == 4) ? 4 : 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxcnd_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
				 स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा mxc_nand_host *host = nand_get_controller_data(chip);

	वापस host->devtype_data->setup_पूर्णांकerface(chip, chipnr, conf);
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops mxcnd_controller_ops = अणु
	.attach_chip = mxcnd_attach_chip,
	.setup_पूर्णांकerface = mxcnd_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक mxcnd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nand_chip *this;
	काष्ठा mtd_info *mtd;
	काष्ठा mxc_nand_host *host;
	काष्ठा resource *res;
	पूर्णांक err = 0;

	/* Allocate memory क्रम MTD device काष्ठाure and निजी data */
	host = devm_kzalloc(&pdev->dev, माप(काष्ठा mxc_nand_host),
			GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	/* allocate a temporary buffer क्रम the nand_scan_ident() */
	host->data_buf = devm_kzalloc(&pdev->dev, PAGE_SIZE, GFP_KERNEL);
	अगर (!host->data_buf)
		वापस -ENOMEM;

	host->dev = &pdev->dev;
	/* काष्ठाures must be linked */
	this = &host->nand;
	mtd = nand_to_mtd(this);
	mtd->dev.parent = &pdev->dev;
	mtd->name = DRIVER_NAME;

	/* 50 us command delay समय */
	this->legacy.chip_delay = 5;

	nand_set_controller_data(this, host);
	nand_set_flash_node(this, pdev->dev.of_node);
	this->legacy.dev_पढ़ोy = mxc_nand_dev_पढ़ोy;
	this->legacy.cmdfunc = mxc_nand_command;
	this->legacy.पढ़ो_byte = mxc_nand_पढ़ो_byte;
	this->legacy.ग_लिखो_buf = mxc_nand_ग_लिखो_buf;
	this->legacy.पढ़ो_buf = mxc_nand_पढ़ो_buf;
	this->legacy.set_features = mxc_nand_set_features;
	this->legacy.get_features = mxc_nand_get_features;

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk))
		वापस PTR_ERR(host->clk);

	host->devtype_data = device_get_match_data(&pdev->dev);

	अगर (!host->devtype_data->setup_पूर्णांकerface)
		this->options |= न_अंकD_KEEP_TIMINGS;

	अगर (host->devtype_data->needs_ip) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		host->regs_ip = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(host->regs_ip))
			वापस PTR_ERR(host->regs_ip);

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	पूर्ण

	host->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->base))
		वापस PTR_ERR(host->base);

	host->मुख्य_area0 = host->base;

	अगर (host->devtype_data->regs_offset)
		host->regs = host->base + host->devtype_data->regs_offset;
	host->spare0 = host->base + host->devtype_data->spare0_offset;
	अगर (host->devtype_data->axi_offset)
		host->regs_axi = host->base + host->devtype_data->axi_offset;

	this->legacy.select_chip = host->devtype_data->select_chip;

	init_completion(&host->op_completion);

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0)
		वापस host->irq;

	/*
	 * Use host->devtype_data->irq_control() here instead of irq_control()
	 * because we must not disable_irq_nosync without having requested the
	 * irq.
	 */
	host->devtype_data->irq_control(host, 0);

	err = devm_request_irq(&pdev->dev, host->irq, mxc_nfc_irq,
			0, DRIVER_NAME, host);
	अगर (err)
		वापस err;

	err = clk_prepare_enable(host->clk);
	अगर (err)
		वापस err;
	host->clk_act = 1;

	/*
	 * Now that we "own" the पूर्णांकerrupt make sure the पूर्णांकerrupt mask bit is
	 * cleared on i.MX21. Otherwise we can't पढ़ो the पूर्णांकerrupt status bit
	 * on this machine.
	 */
	अगर (host->devtype_data->irqpending_quirk) अणु
		disable_irq_nosync(host->irq);
		host->devtype_data->irq_control(host, 1);
	पूर्ण

	/* Scan the न_अंकD device */
	this->legacy.dummy_controller.ops = &mxcnd_controller_ops;
	err = nand_scan(this, is_imx25_nfc(host) ? 4 : 1);
	अगर (err)
		जाओ escan;

	/* Register the partitions */
	err = mtd_device_parse_रेजिस्टर(mtd, part_probes, शून्य, शून्य, 0);
	अगर (err)
		जाओ cleanup_nand;

	platक्रमm_set_drvdata(pdev, host);

	वापस 0;

cleanup_nand:
	nand_cleanup(this);
escan:
	अगर (host->clk_act)
		clk_disable_unprepare(host->clk);

	वापस err;
पूर्ण

अटल पूर्णांक mxcnd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_nand_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &host->nand;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	अगर (host->clk_act)
		clk_disable_unprepare(host->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxcnd_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = mxcnd_dt_ids,
	पूर्ण,
	.probe = mxcnd_probe,
	.हटाओ = mxcnd_हटाओ,
पूर्ण;
module_platक्रमm_driver(mxcnd_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MXC NAND MTD driver");
MODULE_LICENSE("GPL");
