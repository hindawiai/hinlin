<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD am53c974 driver.
 * Copyright (c) 2014 Hannes Reinecke, SUSE Linux GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <scsi/scsi_host.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME "am53c974"
#घोषणा DRV_MODULE_VERSION "1.00"

अटल bool am53c974_debug;
अटल bool am53c974_fenab = true;

#घोषणा esp_dma_log(f, a...)						\
	करो अणु								\
		अगर (am53c974_debug)					\
			shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ##a);	\
	पूर्ण जबतक (0)

#घोषणा ESP_DMA_CMD 0x10
#घोषणा ESP_DMA_STC 0x11
#घोषणा ESP_DMA_SPA 0x12
#घोषणा ESP_DMA_WBC 0x13
#घोषणा ESP_DMA_WAC 0x14
#घोषणा ESP_DMA_STATUS 0x15
#घोषणा ESP_DMA_SMDLA 0x16
#घोषणा ESP_DMA_WMAC 0x17

#घोषणा ESP_DMA_CMD_IDLE 0x00
#घोषणा ESP_DMA_CMD_BLAST 0x01
#घोषणा ESP_DMA_CMD_ABORT 0x02
#घोषणा ESP_DMA_CMD_START 0x03
#घोषणा ESP_DMA_CMD_MASK  0x03
#घोषणा ESP_DMA_CMD_DIAG 0x04
#घोषणा ESP_DMA_CMD_MDL 0x10
#घोषणा ESP_DMA_CMD_INTE_P 0x20
#घोषणा ESP_DMA_CMD_INTE_D 0x40
#घोषणा ESP_DMA_CMD_सूची 0x80

#घोषणा ESP_DMA_STAT_PWDN 0x01
#घोषणा ESP_DMA_STAT_ERROR 0x02
#घोषणा ESP_DMA_STAT_ABORT 0x04
#घोषणा ESP_DMA_STAT_DONE 0x08
#घोषणा ESP_DMA_STAT_SCSIINT 0x10
#घोषणा ESP_DMA_STAT_BCMPLT 0x20

/* EEPROM is accessed with 16-bit values */
#घोषणा DC390_EEPROM_READ 0x80
#घोषणा DC390_EEPROM_LEN 0x40

/*
 * DC390 EEPROM
 *
 * 8 * 4 bytes of per-device options
 * followed by HBA specअगरic options
 */

/* Per-device options */
#घोषणा DC390_EE_MODE1 0x00
#घोषणा DC390_EE_SPEED 0x01

/* HBA-specअगरic options */
#घोषणा DC390_EE_ADAPT_SCSI_ID 0x40
#घोषणा DC390_EE_MODE2 0x41
#घोषणा DC390_EE_DELAY 0x42
#घोषणा DC390_EE_TAG_CMD_NUM 0x43

#घोषणा DC390_EE_MODE1_PARITY_CHK   0x01
#घोषणा DC390_EE_MODE1_SYNC_NEGO    0x02
#घोषणा DC390_EE_MODE1_EN_DISC      0x04
#घोषणा DC390_EE_MODE1_SEND_START   0x08
#घोषणा DC390_EE_MODE1_TCQ          0x10

#घोषणा DC390_EE_MODE2_MORE_2DRV    0x01
#घोषणा DC390_EE_MODE2_GREATER_1G   0x02
#घोषणा DC390_EE_MODE2_RST_SCSI_BUS 0x04
#घोषणा DC390_EE_MODE2_ACTIVE_NEGATION 0x08
#घोषणा DC390_EE_MODE2_NO_SEEK      0x10
#घोषणा DC390_EE_MODE2_LUN_CHECK    0x20

काष्ठा pci_esp_priv अणु
	काष्ठा esp *esp;
	u8 dma_status;
पूर्ण;

अटल व्योम pci_esp_dma_drain(काष्ठा esp *esp);

अटल अंतरभूत काष्ठा pci_esp_priv *pci_esp_get_priv(काष्ठा esp *esp)
अणु
	वापस dev_get_drvdata(esp->dev);
पूर्ण

अटल व्योम pci_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	ioग_लिखो8(val, esp->regs + (reg * 4UL));
पूर्ण

अटल u8 pci_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस ioपढ़ो8(esp->regs + (reg * 4UL));
पूर्ण

अटल व्योम pci_esp_ग_लिखो32(काष्ठा esp *esp, u32 val, अचिन्हित दीर्घ reg)
अणु
	वापस ioग_लिखो32(val, esp->regs + (reg * 4UL));
पूर्ण

अटल पूर्णांक pci_esp_irq_pending(काष्ठा esp *esp)
अणु
	काष्ठा pci_esp_priv *pep = pci_esp_get_priv(esp);

	pep->dma_status = pci_esp_पढ़ो8(esp, ESP_DMA_STATUS);
	esp_dma_log("dma intr dreg[%02x]\n", pep->dma_status);

	अगर (pep->dma_status & (ESP_DMA_STAT_ERROR |
			       ESP_DMA_STAT_ABORT |
			       ESP_DMA_STAT_DONE |
			       ESP_DMA_STAT_SCSIINT))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम pci_esp_reset_dma(काष्ठा esp *esp)
अणु
	/* Nothing to करो ? */
पूर्ण

अटल व्योम pci_esp_dma_drain(काष्ठा esp *esp)
अणु
	u8 resid;
	पूर्णांक lim = 1000;


	अगर ((esp->sreg & ESP_STAT_PMASK) == ESP_DOP ||
	    (esp->sreg & ESP_STAT_PMASK) == ESP_DIP)
		/* Data-In or Data-Out, nothing to be करोne */
		वापस;

	जबतक (--lim > 0) अणु
		resid = pci_esp_पढ़ो8(esp, ESP_FFLAGS) & ESP_FF_FBYTES;
		अगर (resid <= 1)
			अवरोध;
		cpu_relax();
	पूर्ण

	/*
	 * When there is a residual BCMPLT will never be set
	 * (obviously). But we still have to issue the BLAST
	 * command, otherwise the data will not being transferred.
	 * But we'll never know when the BLAST operation is
	 * finished. So check क्रम some समय and give up eventually.
	 */
	lim = 1000;
	pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_सूची | ESP_DMA_CMD_BLAST, ESP_DMA_CMD);
	जबतक (pci_esp_पढ़ो8(esp, ESP_DMA_STATUS) & ESP_DMA_STAT_BCMPLT) अणु
		अगर (--lim == 0)
			अवरोध;
		cpu_relax();
	पूर्ण
	pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_सूची | ESP_DMA_CMD_IDLE, ESP_DMA_CMD);
	esp_dma_log("DMA blast done (%d tries, %d bytes left)\n", lim, resid);
	/* BLAST residual handling is currently untested */
	अगर (WARN_ON_ONCE(resid == 1)) अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;

		ent->flags |= ESP_CMD_FLAG_RESIDUAL;
	पूर्ण
पूर्ण

अटल व्योम pci_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	काष्ठा pci_esp_priv *pep = pci_esp_get_priv(esp);

	esp_dma_log("invalidate DMA\n");

	pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_IDLE, ESP_DMA_CMD);
	pep->dma_status = 0;
पूर्ण

अटल पूर्णांक pci_esp_dma_error(काष्ठा esp *esp)
अणु
	काष्ठा pci_esp_priv *pep = pci_esp_get_priv(esp);

	अगर (pep->dma_status & ESP_DMA_STAT_ERROR) अणु
		u8 dma_cmd = pci_esp_पढ़ो8(esp, ESP_DMA_CMD);

		अगर ((dma_cmd & ESP_DMA_CMD_MASK) == ESP_DMA_CMD_START)
			pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_ABORT, ESP_DMA_CMD);

		वापस 1;
	पूर्ण
	अगर (pep->dma_status & ESP_DMA_STAT_ABORT) अणु
		pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_IDLE, ESP_DMA_CMD);
		pep->dma_status = pci_esp_पढ़ो8(esp, ESP_DMA_CMD);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pci_esp_send_dma_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
				 u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा pci_esp_priv *pep = pci_esp_get_priv(esp);
	u32 val = 0;

	BUG_ON(!(cmd & ESP_CMD_DMA));

	pep->dma_status = 0;

	/* Set DMA engine to IDLE */
	अगर (ग_लिखो)
		/* DMA ग_लिखो direction logic is inverted */
		val |= ESP_DMA_CMD_सूची;
	pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_IDLE | val, ESP_DMA_CMD);

	pci_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	pci_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	अगर (esp->config2 & ESP_CONFIG2_FENAB)
		pci_esp_ग_लिखो8(esp, (esp_count >> 16) & 0xff, ESP_TCHI);

	pci_esp_ग_लिखो32(esp, esp_count, ESP_DMA_STC);
	pci_esp_ग_लिखो32(esp, addr, ESP_DMA_SPA);

	esp_dma_log("start dma addr[%x] count[%d:%d]\n",
		    addr, esp_count, dma_count);

	scsi_esp_cmd(esp, cmd);
	/* Send DMA Start command */
	pci_esp_ग_लिखो8(esp, ESP_DMA_CMD_START | val, ESP_DMA_CMD);
पूर्ण

अटल u32 pci_esp_dma_length_limit(काष्ठा esp *esp, u32 dma_addr, u32 dma_len)
अणु
	पूर्णांक dma_limit = 16;
	u32 base, end;

	/*
	 * If CONFIG2_FENAB is set we can
	 * handle up to 24 bit addresses
	 */
	अगर (esp->config2 & ESP_CONFIG2_FENAB)
		dma_limit = 24;

	अगर (dma_len > (1U << dma_limit))
		dma_len = (1U << dma_limit);

	/*
	 * Prevent crossing a 24-bit address boundary.
	 */
	base = dma_addr & ((1U << 24) - 1U);
	end = base + dma_len;
	अगर (end > (1U << 24))
		end = (1U <<24);
	dma_len = end - base;

	वापस dma_len;
पूर्ण

अटल स्थिर काष्ठा esp_driver_ops pci_esp_ops = अणु
	.esp_ग_लिखो8	=	pci_esp_ग_लिखो8,
	.esp_पढ़ो8	=	pci_esp_पढ़ो8,
	.irq_pending	=	pci_esp_irq_pending,
	.reset_dma	=	pci_esp_reset_dma,
	.dma_drain	=	pci_esp_dma_drain,
	.dma_invalidate	=	pci_esp_dma_invalidate,
	.send_dma_cmd	=	pci_esp_send_dma_cmd,
	.dma_error	=	pci_esp_dma_error,
	.dma_length_limit =	pci_esp_dma_length_limit,
पूर्ण;

/*
 * Read DC-390 eeprom
 */
अटल व्योम dc390_eeprom_prepare_पढ़ो(काष्ठा pci_dev *pdev, u8 cmd)
अणु
	u8 carry_flag = 1, j = 0x80, bval;
	पूर्णांक i;

	क्रम (i = 0; i < 9; i++) अणु
		अगर (carry_flag) अणु
			pci_ग_लिखो_config_byte(pdev, 0x80, 0x40);
			bval = 0xc0;
		पूर्ण अन्यथा
			bval = 0x80;

		udelay(160);
		pci_ग_लिखो_config_byte(pdev, 0x80, bval);
		udelay(160);
		pci_ग_लिखो_config_byte(pdev, 0x80, 0);
		udelay(160);

		carry_flag = (cmd & j) ? 1 : 0;
		j >>= 1;
	पूर्ण
पूर्ण

अटल u16 dc390_eeprom_get_data(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	u16 wval = 0;
	u8 bval;

	क्रम (i = 0; i < 16; i++) अणु
		wval <<= 1;

		pci_ग_लिखो_config_byte(pdev, 0x80, 0x80);
		udelay(160);
		pci_ग_लिखो_config_byte(pdev, 0x80, 0x40);
		udelay(160);
		pci_पढ़ो_config_byte(pdev, 0x00, &bval);

		अगर (bval == 0x22)
			wval |= 1;
	पूर्ण

	वापस wval;
पूर्ण

अटल व्योम dc390_पढ़ो_eeprom(काष्ठा pci_dev *pdev, u16 *ptr)
अणु
	u8 cmd = DC390_EEPROM_READ, i;

	क्रम (i = 0; i < DC390_EEPROM_LEN; i++) अणु
		pci_ग_लिखो_config_byte(pdev, 0xc0, 0);
		udelay(160);

		dc390_eeprom_prepare_पढ़ो(pdev, cmd++);
		*ptr++ = dc390_eeprom_get_data(pdev);

		pci_ग_लिखो_config_byte(pdev, 0x80, 0);
		pci_ग_लिखो_config_byte(pdev, 0x80, 0);
		udelay(160);
	पूर्ण
पूर्ण

अटल व्योम dc390_check_eeprom(काष्ठा esp *esp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(esp->dev);
	u8 EEbuf[128];
	u16 *ptr = (u16 *)EEbuf, wval = 0;
	पूर्णांक i;

	dc390_पढ़ो_eeprom(pdev, ptr);

	क्रम (i = 0; i < DC390_EEPROM_LEN; i++, ptr++)
		wval += *ptr;

	/* no Tekram EEprom found */
	अगर (wval != 0x1234) अणु
		dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
			   "No valid Tekram EEprom found\n");
		वापस;
	पूर्ण
	esp->scsi_id = EEbuf[DC390_EE_ADAPT_SCSI_ID];
	esp->num_tags = 2 << EEbuf[DC390_EE_TAG_CMD_NUM];
	अगर (EEbuf[DC390_EE_MODE2] & DC390_EE_MODE2_ACTIVE_NEGATION)
		esp->config4 |= ESP_CONFIG4_RADE | ESP_CONFIG4_RAE;
पूर्ण

अटल पूर्णांक pci_esp_probe_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा scsi_host_ढाँचा *hostt = &scsi_esp_ढाँचा;
	पूर्णांक err = -ENODEV;
	काष्ठा Scsi_Host *shost;
	काष्ठा esp *esp;
	काष्ठा pci_esp_priv *pep;

	अगर (pci_enable_device(pdev)) अणु
		dev_prपूर्णांकk(KERN_INFO, &pdev->dev, "cannot enable device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
			   "failed to set 32bit DMA mask\n");
		जाओ fail_disable_device;
	पूर्ण

	shost = scsi_host_alloc(hostt, माप(काष्ठा esp));
	अगर (!shost) अणु
		dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
			   "failed to allocate scsi host\n");
		err = -ENOMEM;
		जाओ fail_disable_device;
	पूर्ण

	pep = kzalloc(माप(काष्ठा pci_esp_priv), GFP_KERNEL);
	अगर (!pep) अणु
		dev_prपूर्णांकk(KERN_INFO, &pdev->dev,
			   "failed to allocate esp_priv\n");
		err = -ENOMEM;
		जाओ fail_host_alloc;
	पूर्ण

	esp = shost_priv(shost);
	esp->host = shost;
	esp->dev = &pdev->dev;
	esp->ops = &pci_esp_ops;
	/*
	 * The am53c974 HBA has a design flaw of generating
	 * spurious DMA completion पूर्णांकerrupts when using
	 * DMA क्रम command submission.
	 */
	esp->flags |= ESP_FLAG_USE_FIFO;
	/*
	 * Enable CONFIG2_FENAB to allow क्रम large DMA transfers
	 */
	अगर (am53c974_fenab)
		esp->config2 |= ESP_CONFIG2_FENAB;

	pep->esp = esp;

	अगर (pci_request_regions(pdev, DRV_MODULE_NAME)) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
			   "pci memory selection failed\n");
		जाओ fail_priv_alloc;
	पूर्ण

	esp->regs = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!esp->regs) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev, "pci I/O map failed\n");
		err = -EINVAL;
		जाओ fail_release_regions;
	पूर्ण
	esp->dma_regs = esp->regs;

	pci_set_master(pdev);

	esp->command_block = dma_alloc_coherent(&pdev->dev, 16,
			&esp->command_block_dma, GFP_KERNEL);
	अगर (!esp->command_block) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
			   "failed to allocate command block\n");
		err = -ENOMEM;
		जाओ fail_unmap_regs;
	पूर्ण

	pci_set_drvdata(pdev, pep);

	err = request_irq(pdev->irq, scsi_esp_पूर्णांकr, IRQF_SHARED,
			  DRV_MODULE_NAME, esp);
	अगर (err < 0) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev, "failed to register IRQ\n");
		जाओ fail_unmap_command_block;
	पूर्ण

	esp->scsi_id = 7;
	dc390_check_eeprom(esp);

	shost->this_id = esp->scsi_id;
	shost->max_id = 8;
	shost->irq = pdev->irq;
	shost->io_port = pci_resource_start(pdev, 0);
	shost->n_io_port = pci_resource_len(pdev, 0);
	shost->unique_id = shost->io_port;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	/* Assume 40MHz घड़ी */
	esp->cfreq = 40000000;

	err = scsi_esp_रेजिस्टर(esp);
	अगर (err)
		जाओ fail_मुक्त_irq;

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(pdev->irq, esp);
fail_unmap_command_block:
	pci_set_drvdata(pdev, शून्य);
	dma_मुक्त_coherent(&pdev->dev, 16, esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs:
	pci_iounmap(pdev, esp->regs);
fail_release_regions:
	pci_release_regions(pdev);
fail_priv_alloc:
	kमुक्त(pep);
fail_host_alloc:
	scsi_host_put(shost);
fail_disable_device:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम pci_esp_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_esp_priv *pep = pci_get_drvdata(pdev);
	काष्ठा esp *esp = pep->esp;

	scsi_esp_unरेजिस्टर(esp);
	मुक्त_irq(pdev->irq, esp);
	pci_set_drvdata(pdev, शून्य);
	dma_मुक्त_coherent(&pdev->dev, 16, esp->command_block,
			  esp->command_block_dma);
	pci_iounmap(pdev, esp->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(pep);

	scsi_host_put(esp->host);
पूर्ण

अटल काष्ठा pci_device_id am53c974_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_SCSI,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, am53c974_pci_tbl);

अटल काष्ठा pci_driver am53c974_driver = अणु
	.name           = DRV_MODULE_NAME,
	.id_table       = am53c974_pci_tbl,
	.probe          = pci_esp_probe_one,
	.हटाओ         = pci_esp_हटाओ_one,
पूर्ण;

module_pci_driver(am53c974_driver);

MODULE_DESCRIPTION("AM53C974 SCSI driver");
MODULE_AUTHOR("Hannes Reinecke <hare@suse.de>");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);
MODULE_ALIAS("tmscsim");

module_param(am53c974_debug, bool, 0644);
MODULE_PARM_DESC(am53c974_debug, "Enable debugging");

module_param(am53c974_fenab, bool, 0444);
MODULE_PARM_DESC(am53c974_fenab, "Enable 24-bit DMA transfer sizes");
