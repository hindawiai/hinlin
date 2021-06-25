<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// HiSilicon SPI NOR V3XX Flash Controller Driver क्रम hi16xx chipsets
//
// Copyright (c) 2019 HiSilicon Technologies Co., Ltd.
// Author: John Garry <john.garry@huawei.com>

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

#घोषणा HISI_SFC_V3XX_VERSION (0x1f8)

#घोषणा HISI_SFC_V3XX_GLB_CFG (0x100)
#घोषणा HISI_SFC_V3XX_GLB_CFG_CS0_ADDR_MODE BIT(2)
#घोषणा HISI_SFC_V3XX_RAW_INT_STAT (0x120)
#घोषणा HISI_SFC_V3XX_INT_STAT (0x124)
#घोषणा HISI_SFC_V3XX_INT_MASK (0x128)
#घोषणा HISI_SFC_V3XX_INT_CLR (0x12c)
#घोषणा HISI_SFC_V3XX_CMD_CFG (0x300)
#घोषणा HISI_SFC_V3XX_CMD_CFG_DATA_CNT_OFF 9
#घोषणा HISI_SFC_V3XX_CMD_CFG_RW_MSK BIT(8)
#घोषणा HISI_SFC_V3XX_CMD_CFG_DATA_EN_MSK BIT(7)
#घोषणा HISI_SFC_V3XX_CMD_CFG_DUMMY_CNT_OFF 4
#घोषणा HISI_SFC_V3XX_CMD_CFG_ADDR_EN_MSK BIT(3)
#घोषणा HISI_SFC_V3XX_CMD_CFG_CS_SEL_OFF 1
#घोषणा HISI_SFC_V3XX_CMD_CFG_START_MSK BIT(0)
#घोषणा HISI_SFC_V3XX_CMD_INS (0x308)
#घोषणा HISI_SFC_V3XX_CMD_ADDR (0x30c)
#घोषणा HISI_SFC_V3XX_CMD_DATABUF0 (0x400)

/* Common definition of पूर्णांकerrupt bit masks */
#घोषणा HISI_SFC_V3XX_INT_MASK_ALL (0x1ff)	/* all the masks */
#घोषणा HISI_SFC_V3XX_INT_MASK_CPLT BIT(0)	/* command execution complete */
#घोषणा HISI_SFC_V3XX_INT_MASK_PP_ERR BIT(2)	/* page progrom error */
#घोषणा HISI_SFC_V3XX_INT_MASK_IACCES BIT(5)	/* error visiting inaccessible/
						 * रक्षित address
						 */

/* IO Mode definition in HISI_SFC_V3XX_CMD_CFG */
#घोषणा HISI_SFC_V3XX_STD (0 << 17)
#घोषणा HISI_SFC_V3XX_DIDO (1 << 17)
#घोषणा HISI_SFC_V3XX_DIO (2 << 17)
#घोषणा HISI_SFC_V3XX_FULL_DIO (3 << 17)
#घोषणा HISI_SFC_V3XX_QIQO (5 << 17)
#घोषणा HISI_SFC_V3XX_QIO (6 << 17)
#घोषणा HISI_SFC_V3XX_FULL_QIO (7 << 17)

/*
 * The IO modes lookup table. hisi_sfc_v3xx_io_modes[(z - 1) / 2][y / 2][x / 2]
 * stands क्रम x-y-z mode, as described in SFDP terminology. -EIO indicates
 * an invalid mode.
 */
अटल स्थिर पूर्णांक hisi_sfc_v3xx_io_modes[2][3][3] = अणु
	अणु
		अणु HISI_SFC_V3XX_DIDO, HISI_SFC_V3XX_DIDO, HISI_SFC_V3XX_DIDO पूर्ण,
		अणु HISI_SFC_V3XX_DIO, HISI_SFC_V3XX_FULL_DIO, -EIO पूर्ण,
		अणु -EIO, -EIO, -EIO पूर्ण,
	पूर्ण,
	अणु
		अणु HISI_SFC_V3XX_QIQO, HISI_SFC_V3XX_QIQO, HISI_SFC_V3XX_QIQO पूर्ण,
		अणु -EIO, -EIO, -EIO पूर्ण,
		अणु HISI_SFC_V3XX_QIO, -EIO, HISI_SFC_V3XX_FULL_QIO पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा hisi_sfc_v3xx_host अणु
	काष्ठा device *dev;
	व्योम __iomem *regbase;
	पूर्णांक max_cmd_dword;
	काष्ठा completion *completion;
	u8 address_mode;
	पूर्णांक irq;
पूर्ण;

अटल व्योम hisi_sfc_v3xx_disable_पूर्णांक(काष्ठा hisi_sfc_v3xx_host *host)
अणु
	ग_लिखोl(0, host->regbase + HISI_SFC_V3XX_INT_MASK);
पूर्ण

अटल व्योम hisi_sfc_v3xx_enable_पूर्णांक(काष्ठा hisi_sfc_v3xx_host *host)
अणु
	ग_लिखोl(HISI_SFC_V3XX_INT_MASK_ALL, host->regbase + HISI_SFC_V3XX_INT_MASK);
पूर्ण

अटल व्योम hisi_sfc_v3xx_clear_पूर्णांक(काष्ठा hisi_sfc_v3xx_host *host)
अणु
	ग_लिखोl(HISI_SFC_V3XX_INT_MASK_ALL, host->regbase + HISI_SFC_V3XX_INT_CLR);
पूर्ण

/*
 * The पूर्णांकerrupt status रेजिस्टर indicates whether an error occurs
 * after per operation. Check it, and clear the पूर्णांकerrupts क्रम
 * next समय judgement.
 */
अटल पूर्णांक hisi_sfc_v3xx_handle_completion(काष्ठा hisi_sfc_v3xx_host *host)
अणु
	u32 reg;

	reg = पढ़ोl(host->regbase + HISI_SFC_V3XX_RAW_INT_STAT);
	hisi_sfc_v3xx_clear_पूर्णांक(host);

	अगर (reg & HISI_SFC_V3XX_INT_MASK_IACCES) अणु
		dev_err(host->dev, "fail to access protected address\n");
		वापस -EIO;
	पूर्ण

	अगर (reg & HISI_SFC_V3XX_INT_MASK_PP_ERR) अणु
		dev_err(host->dev, "page program operation failed\n");
		वापस -EIO;
	पूर्ण

	/*
	 * The other bits of the पूर्णांकerrupt रेजिस्टरs is not currently
	 * used and probably not be triggered in this driver. When it
	 * happens, we regard it as an unsupported error here.
	 */
	अगर (!(reg & HISI_SFC_V3XX_INT_MASK_CPLT)) अणु
		dev_err(host->dev, "unsupported error occurred, status=0x%x\n", reg);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HISI_SFC_V3XX_WAIT_TIMEOUT_US		1000000
#घोषणा HISI_SFC_V3XX_WAIT_POLL_INTERVAL_US	10

अटल पूर्णांक hisi_sfc_v3xx_रुको_cmd_idle(काष्ठा hisi_sfc_v3xx_host *host)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(host->regbase + HISI_SFC_V3XX_CMD_CFG, reg,
				  !(reg & HISI_SFC_V3XX_CMD_CFG_START_MSK),
				  HISI_SFC_V3XX_WAIT_POLL_INTERVAL_US,
				  HISI_SFC_V3XX_WAIT_TIMEOUT_US);
पूर्ण

अटल पूर्णांक hisi_sfc_v3xx_adjust_op_size(काष्ठा spi_mem *mem,
					काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_device *spi = mem->spi;
	काष्ठा hisi_sfc_v3xx_host *host;
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t)op->data.buf.in;
	पूर्णांक max_byte_count;

	host = spi_controller_get_devdata(spi->master);

	max_byte_count = host->max_cmd_dword * 4;

	अगर (!IS_ALIGNED(addr, 4) && op->data.nbytes >= 4)
		op->data.nbytes = 4 - (addr % 4);
	अन्यथा अगर (op->data.nbytes > max_byte_count)
		op->data.nbytes = max_byte_count;

	वापस 0;
पूर्ण

/*
 * The controller only supports Standard SPI mode, Duall mode and
 * Quad mode. Double sanitize the ops here to aव्योम OOB access.
 */
अटल bool hisi_sfc_v3xx_supports_op(काष्ठा spi_mem *mem,
				      स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_device *spi = mem->spi;
	काष्ठा hisi_sfc_v3xx_host *host;

	host = spi_controller_get_devdata(spi->master);

	अगर (op->data.buswidth > 4 || op->dummy.buswidth > 4 ||
	    op->addr.buswidth > 4 || op->cmd.buswidth > 4)
		वापस false;

	अगर (op->addr.nbytes != host->address_mode && op->addr.nbytes)
		वापस false;

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

/*
 * स_नकल_अणुto,fromपूर्णio करोesn't gurantee 32b accesses - which we require क्रम the
 * DATABUF रेजिस्टरs -so use __ioअणुपढ़ो,ग_लिखोपूर्ण32_copy when possible. For
 * trailing bytes, copy them byte-by-byte from the DATABUF रेजिस्टर, as we
 * can't clobber outside the source/dest buffer.
 *
 * For efficient data पढ़ो/ग_लिखो, we try to put any start 32b unaligned data
 * पूर्णांकo a separate transaction in hisi_sfc_v3xx_adjust_op_size().
 */
अटल व्योम hisi_sfc_v3xx_पढ़ो_databuf(काष्ठा hisi_sfc_v3xx_host *host,
				       u8 *to, अचिन्हित पूर्णांक len)
अणु
	व्योम __iomem *from;
	पूर्णांक i;

	from = host->regbase + HISI_SFC_V3XX_CMD_DATABUF0;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)to, 4)) अणु
		पूर्णांक words = len / 4;

		__ioपढ़ो32_copy(to, from, words);

		len -= words * 4;
		अगर (len) अणु
			u32 val;

			to += words * 4;
			from += words * 4;

			val = __raw_पढ़ोl(from);

			क्रम (i = 0; i < len; i++, val >>= 8, to++)
				*to = (u8)val;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < DIV_ROUND_UP(len, 4); i++, from += 4) अणु
			u32 val = __raw_पढ़ोl(from);
			पूर्णांक j;

			क्रम (j = 0; j < 4 && (j + (i * 4) < len);
			     to++, val >>= 8, j++)
				*to = (u8)val;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hisi_sfc_v3xx_ग_लिखो_databuf(काष्ठा hisi_sfc_v3xx_host *host,
					स्थिर u8 *from, अचिन्हित पूर्णांक len)
अणु
	व्योम __iomem *to;
	पूर्णांक i;

	to = host->regbase + HISI_SFC_V3XX_CMD_DATABUF0;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)from, 4)) अणु
		पूर्णांक words = len / 4;

		__ioग_लिखो32_copy(to, from, words);

		len -= words * 4;
		अगर (len) अणु
			u32 val = 0;

			to += words * 4;
			from += words * 4;

			क्रम (i = 0; i < len; i++, from++)
				val |= *from << i * 8;
			__raw_ग_लिखोl(val, to);
		पूर्ण

	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < DIV_ROUND_UP(len, 4); i++, to += 4) अणु
			u32 val = 0;
			पूर्णांक j;

			क्रम (j = 0; j < 4 && (j + (i * 4) < len);
			     from++, j++)
				val |= *from << j * 8;
			__raw_ग_लिखोl(val, to);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_sfc_v3xx_start_bus(काष्ठा hisi_sfc_v3xx_host *host,
				   स्थिर काष्ठा spi_mem_op *op,
				   u8 chip_select)
अणु
	पूर्णांक len = op->data.nbytes, buswidth_mode;
	u32 config = 0;

	अगर (op->addr.nbytes)
		config |= HISI_SFC_V3XX_CMD_CFG_ADDR_EN_MSK;

	अगर (op->data.buswidth == 0 || op->data.buswidth == 1) अणु
		buswidth_mode = HISI_SFC_V3XX_STD;
	पूर्ण अन्यथा अणु
		पूर्णांक data_idx, addr_idx, cmd_idx;

		data_idx = (op->data.buswidth - 1) / 2;
		addr_idx = op->addr.buswidth / 2;
		cmd_idx = op->cmd.buswidth / 2;
		buswidth_mode = hisi_sfc_v3xx_io_modes[data_idx][addr_idx][cmd_idx];
	पूर्ण
	अगर (buswidth_mode < 0)
		वापस buswidth_mode;
	config |= buswidth_mode;

	अगर (op->data.dir != SPI_MEM_NO_DATA) अणु
		config |= (len - 1) << HISI_SFC_V3XX_CMD_CFG_DATA_CNT_OFF;
		config |= HISI_SFC_V3XX_CMD_CFG_DATA_EN_MSK;
	पूर्ण

	अगर (op->data.dir == SPI_MEM_DATA_IN)
		config |= HISI_SFC_V3XX_CMD_CFG_RW_MSK;

	config |= op->dummy.nbytes << HISI_SFC_V3XX_CMD_CFG_DUMMY_CNT_OFF |
		  chip_select << HISI_SFC_V3XX_CMD_CFG_CS_SEL_OFF |
		  HISI_SFC_V3XX_CMD_CFG_START_MSK;

	ग_लिखोl(op->addr.val, host->regbase + HISI_SFC_V3XX_CMD_ADDR);
	ग_लिखोl(op->cmd.opcode, host->regbase + HISI_SFC_V3XX_CMD_INS);

	ग_लिखोl(config, host->regbase + HISI_SFC_V3XX_CMD_CFG);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sfc_v3xx_generic_exec_op(काष्ठा hisi_sfc_v3xx_host *host,
					 स्थिर काष्ठा spi_mem_op *op,
					 u8 chip_select)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret;

	अगर (host->irq) अणु
		host->completion = &करोne;
		hisi_sfc_v3xx_enable_पूर्णांक(host);
	पूर्ण

	अगर (op->data.dir == SPI_MEM_DATA_OUT)
		hisi_sfc_v3xx_ग_लिखो_databuf(host, op->data.buf.out, op->data.nbytes);

	ret = hisi_sfc_v3xx_start_bus(host, op, chip_select);
	अगर (ret)
		वापस ret;

	अगर (host->irq) अणु
		ret = रुको_क्रम_completion_समयout(host->completion,
						  usecs_to_jअगरfies(HISI_SFC_V3XX_WAIT_TIMEOUT_US));
		अगर (!ret)
			ret = -ETIMEDOUT;
		अन्यथा
			ret = 0;

		hisi_sfc_v3xx_disable_पूर्णांक(host);
		synchronize_irq(host->irq);
		host->completion = शून्य;
	पूर्ण अन्यथा अणु
		ret = hisi_sfc_v3xx_रुको_cmd_idle(host);
	पूर्ण
	अगर (hisi_sfc_v3xx_handle_completion(host) || ret)
		वापस -EIO;

	अगर (op->data.dir == SPI_MEM_DATA_IN)
		hisi_sfc_v3xx_पढ़ो_databuf(host, op->data.buf.in, op->data.nbytes);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sfc_v3xx_exec_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा hisi_sfc_v3xx_host *host;
	काष्ठा spi_device *spi = mem->spi;
	u8 chip_select = spi->chip_select;

	host = spi_controller_get_devdata(spi->master);

	वापस hisi_sfc_v3xx_generic_exec_op(host, op, chip_select);
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops hisi_sfc_v3xx_mem_ops = अणु
	.adjust_op_size = hisi_sfc_v3xx_adjust_op_size,
	.supports_op = hisi_sfc_v3xx_supports_op,
	.exec_op = hisi_sfc_v3xx_exec_op,
पूर्ण;

अटल irqवापस_t hisi_sfc_v3xx_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_sfc_v3xx_host *host = data;

	hisi_sfc_v3xx_disable_पूर्णांक(host);

	complete(host->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_sfc_v3xx_buswidth_override_bits;

/*
 * ACPI FW करोes not allow us to currently set the device buswidth, so quirk it
 * depending on the board.
 */
अटल पूर्णांक __init hisi_sfc_v3xx_dmi_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	hisi_sfc_v3xx_buswidth_override_bits = SPI_RX_QUAD | SPI_TX_QUAD;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id hisi_sfc_v3xx_dmi_quirk_table[]  = अणु
	अणु
	.callback = hisi_sfc_v3xx_dmi_quirk,
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Huawei"),
		DMI_MATCH(DMI_PRODUCT_NAME, "D06"),
	पूर्ण,
	पूर्ण,
	अणु
	.callback = hisi_sfc_v3xx_dmi_quirk,
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Huawei"),
		DMI_MATCH(DMI_PRODUCT_NAME, "TaiShan 2280 V2"),
	पूर्ण,
	पूर्ण,
	अणु
	.callback = hisi_sfc_v3xx_dmi_quirk,
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Huawei"),
		DMI_MATCH(DMI_PRODUCT_NAME, "TaiShan 200 (Model 2280)"),
	पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक hisi_sfc_v3xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hisi_sfc_v3xx_host *host;
	काष्ठा spi_controller *ctlr;
	u32 version, glb_config;
	पूर्णांक ret;

	ctlr = spi_alloc_master(&pdev->dev, माप(*host));
	अगर (!ctlr)
		वापस -ENOMEM;

	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD |
			  SPI_TX_DUAL | SPI_TX_QUAD;

	ctlr->buswidth_override_bits = hisi_sfc_v3xx_buswidth_override_bits;

	host = spi_controller_get_devdata(ctlr);
	host->dev = dev;

	platक्रमm_set_drvdata(pdev, host);

	host->regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->regbase)) अणु
		ret = PTR_ERR(host->regbase);
		जाओ err_put_master;
	पूर्ण

	host->irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (host->irq == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ err_put_master;
	पूर्ण

	hisi_sfc_v3xx_disable_पूर्णांक(host);

	अगर (host->irq > 0) अणु
		ret = devm_request_irq(dev, host->irq, hisi_sfc_v3xx_isr, 0,
				       "hisi-sfc-v3xx", host);

		अगर (ret) अणु
			dev_err(dev, "failed to request irq%d, ret = %d\n", host->irq, ret);
			host->irq = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		host->irq = 0;
	पूर्ण

	ctlr->bus_num = -1;
	ctlr->num_chipselect = 1;
	ctlr->mem_ops = &hisi_sfc_v3xx_mem_ops;

	/*
	 * The address mode of the controller is either 3 or 4,
	 * which is indicated by the address mode bit in
	 * the global config रेजिस्टर. The रेजिस्टर is पढ़ो only
	 * क्रम the OS driver.
	 */
	glb_config = पढ़ोl(host->regbase + HISI_SFC_V3XX_GLB_CFG);
	अगर (glb_config & HISI_SFC_V3XX_GLB_CFG_CS0_ADDR_MODE)
		host->address_mode = 4;
	अन्यथा
		host->address_mode = 3;

	version = पढ़ोl(host->regbase + HISI_SFC_V3XX_VERSION);

	अगर (version >= 0x351)
		host->max_cmd_dword = 64;
	अन्यथा
		host->max_cmd_dword = 16;

	ret = devm_spi_रेजिस्टर_controller(dev, ctlr);
	अगर (ret)
		जाओ err_put_master;

	dev_info(&pdev->dev, "hw version 0x%x, %s mode.\n",
		 version, host->irq ? "irq" : "polling");

	वापस 0;

err_put_master:
	spi_master_put(ctlr);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_sfc_v3xx_acpi_ids[] = अणु
	अणु"HISI0341", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_sfc_v3xx_acpi_ids);

अटल काष्ठा platक्रमm_driver hisi_sfc_v3xx_spi_driver = अणु
	.driver = अणु
		.name	= "hisi-sfc-v3xx",
		.acpi_match_table = hisi_sfc_v3xx_acpi_ids,
	पूर्ण,
	.probe	= hisi_sfc_v3xx_probe,
पूर्ण;

अटल पूर्णांक __init hisi_sfc_v3xx_spi_init(व्योम)
अणु
	dmi_check_प्रणाली(hisi_sfc_v3xx_dmi_quirk_table);

	वापस platक्रमm_driver_रेजिस्टर(&hisi_sfc_v3xx_spi_driver);
पूर्ण

अटल व्योम __निकास hisi_sfc_v3xx_spi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_sfc_v3xx_spi_driver);
पूर्ण

module_init(hisi_sfc_v3xx_spi_init);
module_निकास(hisi_sfc_v3xx_spi_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Garry <john.garry@huawei.com>");
MODULE_DESCRIPTION("HiSilicon SPI NOR V3XX Flash Controller Driver for hi16xx chipsets");
