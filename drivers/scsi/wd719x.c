<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Western Digital WD7193, WD7197 and WD7296 SCSI cards
 * Copyright 2013 Ondrej Zary
 *
 * Original driver by
 * Aaron Dewell <dewell@woods.net>
 * Gaerti <Juergen.Gaertner@mbox.si.uni-hannover.de>
 *
 * HW करोcumentation available in book:
 *
 * SPIDER Command Protocol
 * by Chandru M. Sippy
 * SCSI Storage Products (MCP)
 * Western Digital Corporation
 * 09-15-95
 *
 * http://web.archive.org/web/20070717175254/http://sun1.rrzn.uni-hannover.de/gaertner.juergen/wd719x/Linux/Docu/Spider/
 */

/*
 * Driver workflow:
 * 1. SCSI command is transक्रमmed to SCB (Spider Control Block) by the
 *    queuecommand function.
 * 2. The address of the SCB is stored in a list to be able to access it, अगर
 *    something goes wrong.
 * 3. The address of the SCB is written to the Controller, which loads the SCB
 *    via BM-DMA and processes it.
 * 4. After it has finished, it generates an पूर्णांकerrupt, and sets रेजिस्टरs.
 *
 * flaws:
 *  - पात/reset functions
 *
 * ToDo:
 *  - tagged queueing
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश "wd719x.h"

/* low-level रेजिस्टर access */
अटल अंतरभूत u8 wd719x_पढ़ोb(काष्ठा wd719x *wd, u8 reg)
अणु
	वापस ioपढ़ो8(wd->base + reg);
पूर्ण

अटल अंतरभूत u32 wd719x_पढ़ोl(काष्ठा wd719x *wd, u8 reg)
अणु
	वापस ioपढ़ो32(wd->base + reg);
पूर्ण

अटल अंतरभूत व्योम wd719x_ग_लिखोb(काष्ठा wd719x *wd, u8 reg, u8 val)
अणु
	ioग_लिखो8(val, wd->base + reg);
पूर्ण

अटल अंतरभूत व्योम wd719x_ग_लिखोw(काष्ठा wd719x *wd, u8 reg, u16 val)
अणु
	ioग_लिखो16(val, wd->base + reg);
पूर्ण

अटल अंतरभूत व्योम wd719x_ग_लिखोl(काष्ठा wd719x *wd, u8 reg, u32 val)
अणु
	ioग_लिखो32(val, wd->base + reg);
पूर्ण

/* रुको until the command रेजिस्टर is पढ़ोy */
अटल अंतरभूत पूर्णांक wd719x_रुको_पढ़ोy(काष्ठा wd719x *wd)
अणु
	पूर्णांक i = 0;

	करो अणु
		अगर (wd719x_पढ़ोb(wd, WD719X_AMR_COMMAND) == WD719X_CMD_READY)
			वापस 0;
		udelay(1);
	पूर्ण जबतक (i++ < WD719X_WAIT_FOR_CMD_READY);

	dev_err(&wd->pdev->dev, "command register is not ready: 0x%02x\n",
		wd719x_पढ़ोb(wd, WD719X_AMR_COMMAND));

	वापस -ETIMEDOUT;
पूर्ण

/* poll पूर्णांकerrupt status रेजिस्टर until command finishes */
अटल अंतरभूत पूर्णांक wd719x_रुको_करोne(काष्ठा wd719x *wd, पूर्णांक समयout)
अणु
	u8 status;

	जबतक (समयout > 0) अणु
		status = wd719x_पढ़ोb(wd, WD719X_AMR_INT_STATUS);
		अगर (status)
			अवरोध;
		समयout--;
		udelay(1);
	पूर्ण

	अगर (समयout <= 0) अणु
		dev_err(&wd->pdev->dev, "direct command timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (status != WD719X_INT_NOERRORS) अणु
		u8 sue = wd719x_पढ़ोb(wd, WD719X_AMR_SCB_ERROR);
		/* we get this after wd719x_dev_reset, it's not an error */
		अगर (sue == WD719X_SUE_TERM)
			वापस 0;
		/* we get this after wd719x_bus_reset, it's not an error */
		अगर (sue == WD719X_SUE_RESET)
			वापस 0;
		dev_err(&wd->pdev->dev, "direct command failed, status 0x%02x, SUE 0x%02x\n",
			status, sue);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wd719x_direct_cmd(काष्ठा wd719x *wd, u8 opcode, u8 dev, u8 lun,
			     u8 tag, dma_addr_t data, पूर्णांक समयout)
अणु
	पूर्णांक ret = 0;

	/* clear पूर्णांकerrupt status रेजिस्टर (allow command रेजिस्टर to clear) */
	wd719x_ग_लिखोb(wd, WD719X_AMR_INT_STATUS, WD719X_INT_NONE);

	/* Wait क्रम the Command रेजिस्टर to become मुक्त */
	अगर (wd719x_रुको_पढ़ोy(wd))
		वापस -ETIMEDOUT;

	/* disable पूर्णांकerrupts except क्रम RESET/ABORT (it अवरोधs them) */
	अगर (opcode != WD719X_CMD_BUSRESET && opcode != WD719X_CMD_ABORT &&
	    opcode != WD719X_CMD_ABORT_TAG && opcode != WD719X_CMD_RESET)
		dev |= WD719X_DISABLE_INT;
	wd719x_ग_लिखोb(wd, WD719X_AMR_CMD_PARAM, dev);
	wd719x_ग_लिखोb(wd, WD719X_AMR_CMD_PARAM_2, lun);
	wd719x_ग_लिखोb(wd, WD719X_AMR_CMD_PARAM_3, tag);
	अगर (data)
		wd719x_ग_लिखोl(wd, WD719X_AMR_SCB_IN, data);

	/* clear पूर्णांकerrupt status रेजिस्टर again */
	wd719x_ग_लिखोb(wd, WD719X_AMR_INT_STATUS, WD719X_INT_NONE);

	/* Now, ग_लिखो the command */
	wd719x_ग_लिखोb(wd, WD719X_AMR_COMMAND, opcode);

	अगर (समयout)	/* रुको क्रम the command to complete */
		ret = wd719x_रुको_करोne(wd, समयout);

	/* clear पूर्णांकerrupt status रेजिस्टर (clean up) */
	अगर (opcode != WD719X_CMD_READ_FIRMVER)
		wd719x_ग_लिखोb(wd, WD719X_AMR_INT_STATUS, WD719X_INT_NONE);

	वापस ret;
पूर्ण

अटल व्योम wd719x_destroy(काष्ठा wd719x *wd)
अणु
	/* stop the RISC */
	अगर (wd719x_direct_cmd(wd, WD719X_CMD_SLEEP, 0, 0, 0, 0,
			      WD719X_WAIT_FOR_RISC))
		dev_warn(&wd->pdev->dev, "RISC sleep command failed\n");
	/* disable RISC */
	wd719x_ग_लिखोb(wd, WD719X_PCI_MODE_SELECT, 0);

	WARN_ON_ONCE(!list_empty(&wd->active_scbs));

	/* मुक्त पूर्णांकernal buffers */
	dma_मुक्त_coherent(&wd->pdev->dev, wd->fw_size, wd->fw_virt,
			  wd->fw_phys);
	wd->fw_virt = शून्य;
	dma_मुक्त_coherent(&wd->pdev->dev, WD719X_HASH_TABLE_SIZE, wd->hash_virt,
			  wd->hash_phys);
	wd->hash_virt = शून्य;
	dma_मुक्त_coherent(&wd->pdev->dev, माप(काष्ठा wd719x_host_param),
			  wd->params, wd->params_phys);
	wd->params = शून्य;
	मुक्त_irq(wd->pdev->irq, wd);
पूर्ण

/* finish a SCSI command, unmap buffers */
अटल व्योम wd719x_finish_cmd(काष्ठा wd719x_scb *scb, पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *cmd = scb->cmd;
	काष्ठा wd719x *wd = shost_priv(cmd->device->host);

	list_del(&scb->list);

	dma_unmap_single(&wd->pdev->dev, scb->phys,
			माप(काष्ठा wd719x_scb), DMA_BIसूचीECTIONAL);
	scsi_dma_unmap(cmd);
	dma_unmap_single(&wd->pdev->dev, cmd->SCp.dma_handle,
			 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);

	cmd->result = result << 16;
	cmd->scsi_करोne(cmd);
पूर्ण

/* Build a SCB and send it to the card */
अटल पूर्णांक wd719x_queuecommand(काष्ठा Scsi_Host *sh, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक i, count_sg;
	अचिन्हित दीर्घ flags;
	काष्ठा wd719x_scb *scb = scsi_cmd_priv(cmd);
	काष्ठा wd719x *wd = shost_priv(sh);

	scb->cmd = cmd;

	scb->CDB_tag = 0;	/* Tagged queueing not supported yet */
	scb->devid = cmd->device->id;
	scb->lun = cmd->device->lun;

	/* copy the command */
	स_नकल(scb->CDB, cmd->cmnd, cmd->cmd_len);

	/* map SCB */
	scb->phys = dma_map_single(&wd->pdev->dev, scb, माप(*scb),
				   DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(&wd->pdev->dev, scb->phys))
		जाओ out_error;

	/* map sense buffer */
	scb->sense_buf_length = SCSI_SENSE_BUFFERSIZE;
	cmd->SCp.dma_handle = dma_map_single(&wd->pdev->dev, cmd->sense_buffer,
			SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&wd->pdev->dev, cmd->SCp.dma_handle))
		जाओ out_unmap_scb;
	scb->sense_buf = cpu_to_le32(cmd->SCp.dma_handle);

	/* request स्वतःsense */
	scb->SCB_options |= WD719X_SCB_FLAGS_AUTO_REQUEST_SENSE;

	/* check direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		scb->SCB_options |= WD719X_SCB_FLAGS_CHECK_सूचीECTION
				 |  WD719X_SCB_FLAGS_PCI_TO_SCSI;
	अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
		scb->SCB_options |= WD719X_SCB_FLAGS_CHECK_सूचीECTION;

	/* Scather/gather */
	count_sg = scsi_dma_map(cmd);
	अगर (count_sg < 0)
		जाओ out_unmap_sense;
	BUG_ON(count_sg > WD719X_SG);

	अगर (count_sg) अणु
		काष्ठा scatterlist *sg;

		scb->data_length = cpu_to_le32(count_sg *
					       माप(काष्ठा wd719x_sglist));
		scb->data_p = cpu_to_le32(scb->phys +
					  दुरत्व(काष्ठा wd719x_scb, sg_list));

		scsi_क्रम_each_sg(cmd, sg, count_sg, i) अणु
			scb->sg_list[i].ptr = cpu_to_le32(sg_dma_address(sg));
			scb->sg_list[i].length = cpu_to_le32(sg_dma_len(sg));
		पूर्ण
		scb->SCB_options |= WD719X_SCB_FLAGS_DO_SCATTER_GATHER;
	पूर्ण अन्यथा अणु /* zero length */
		scb->data_length = 0;
		scb->data_p = 0;
	पूर्ण

	spin_lock_irqsave(wd->sh->host_lock, flags);

	/* check अगर the Command रेजिस्टर is मुक्त */
	अगर (wd719x_पढ़ोb(wd, WD719X_AMR_COMMAND) != WD719X_CMD_READY) अणु
		spin_unlock_irqrestore(wd->sh->host_lock, flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	list_add(&scb->list, &wd->active_scbs);

	/* ग_लिखो poपूर्णांकer to the AMR */
	wd719x_ग_लिखोl(wd, WD719X_AMR_SCB_IN, scb->phys);
	/* send SCB opcode */
	wd719x_ग_लिखोb(wd, WD719X_AMR_COMMAND, WD719X_CMD_PROCESS_SCB);

	spin_unlock_irqrestore(wd->sh->host_lock, flags);
	वापस 0;

out_unmap_sense:
	dma_unmap_single(&wd->pdev->dev, cmd->SCp.dma_handle,
			 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
out_unmap_scb:
	dma_unmap_single(&wd->pdev->dev, scb->phys, माप(*scb),
			 DMA_BIसूचीECTIONAL);
out_error:
	cmd->result = DID_ERROR << 16;
	cmd->scsi_करोne(cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक wd719x_chip_init(काष्ठा wd719x *wd)
अणु
	पूर्णांक i, ret;
	u32 risc_init[3];
	स्थिर काष्ठा firmware *fw_wcs, *fw_risc;
	स्थिर अक्षर fwname_wcs[] = "wd719x-wcs.bin";
	स्थिर अक्षर fwname_risc[] = "wd719x-risc.bin";

	स_रखो(wd->hash_virt, 0, WD719X_HASH_TABLE_SIZE);

	/* WCS (sequencer) firmware */
	ret = request_firmware(&fw_wcs, fwname_wcs, &wd->pdev->dev);
	अगर (ret) अणु
		dev_err(&wd->pdev->dev, "Unable to load firmware %s: %d\n",
			fwname_wcs, ret);
		वापस ret;
	पूर्ण
	/* RISC firmware */
	ret = request_firmware(&fw_risc, fwname_risc, &wd->pdev->dev);
	अगर (ret) अणु
		dev_err(&wd->pdev->dev, "Unable to load firmware %s: %d\n",
			fwname_risc, ret);
		release_firmware(fw_wcs);
		वापस ret;
	पूर्ण
	wd->fw_size = ALIGN(fw_wcs->size, 4) + fw_risc->size;

	अगर (!wd->fw_virt)
		wd->fw_virt = dma_alloc_coherent(&wd->pdev->dev, wd->fw_size,
						 &wd->fw_phys, GFP_KERNEL);
	अगर (!wd->fw_virt) अणु
		ret = -ENOMEM;
		जाओ wd719x_init_end;
	पूर्ण

	/* make a fresh copy of WCS and RISC code */
	स_नकल(wd->fw_virt, fw_wcs->data, fw_wcs->size);
	स_नकल(wd->fw_virt + ALIGN(fw_wcs->size, 4), fw_risc->data,
		fw_risc->size);

	/* Reset the Spider Chip and adapter itself */
	wd719x_ग_लिखोb(wd, WD719X_PCI_PORT_RESET, WD719X_PCI_RESET);
	udelay(WD719X_WAIT_FOR_RISC);
	/* Clear PIO mode bits set by BIOS */
	wd719x_ग_लिखोb(wd, WD719X_AMR_CMD_PARAM, 0);
	/* ensure RISC is not running */
	wd719x_ग_लिखोb(wd, WD719X_PCI_MODE_SELECT, 0);
	/* ensure command port is पढ़ोy */
	wd719x_ग_लिखोb(wd, WD719X_AMR_COMMAND, 0);
	अगर (wd719x_रुको_पढ़ोy(wd)) अणु
		ret = -ETIMEDOUT;
		जाओ wd719x_init_end;
	पूर्ण

	/* Transfer the first 2K words of RISC code to kick start the uP */
	risc_init[0] = wd->fw_phys;				/* WCS FW */
	risc_init[1] = wd->fw_phys + ALIGN(fw_wcs->size, 4);	/* RISC FW */
	risc_init[2] = wd->hash_phys;				/* hash table */

	/* clear DMA status */
	wd719x_ग_लिखोb(wd, WD719X_PCI_CHANNEL2_3STATUS, 0);

	/* address to पढ़ो firmware from */
	wd719x_ग_लिखोl(wd, WD719X_PCI_EXTERNAL_ADDR, risc_init[1]);
	/* base address to ग_लिखो firmware to (on card) */
	wd719x_ग_लिखोw(wd, WD719X_PCI_INTERNAL_ADDR, WD719X_PRAM_BASE_ADDR);
	/* size: first 2K words */
	wd719x_ग_लिखोw(wd, WD719X_PCI_DMA_TRANSFER_SIZE, 2048 * 2);
	/* start DMA */
	wd719x_ग_लिखोb(wd, WD719X_PCI_CHANNEL2_3CMD, WD719X_START_CHANNEL2_3DMA);

	/* रुको क्रम DMA to complete */
	i = WD719X_WAIT_FOR_RISC;
	जबतक (i-- > 0) अणु
		u8 status = wd719x_पढ़ोb(wd, WD719X_PCI_CHANNEL2_3STATUS);
		अगर (status == WD719X_START_CHANNEL2_3DONE)
			अवरोध;
		अगर (status == WD719X_START_CHANNEL2_3ABORT) अणु
			dev_warn(&wd->pdev->dev, "RISC bootstrap failed: DMA aborted\n");
			ret = -EIO;
			जाओ wd719x_init_end;
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (i < 1) अणु
		dev_warn(&wd->pdev->dev, "RISC bootstrap failed: DMA timeout\n");
		ret = -ETIMEDOUT;
		जाओ wd719x_init_end;
	पूर्ण

	/* firmware is loaded, now initialize and wake up the RISC */
	/* ग_लिखो RISC initialization दीर्घ words to Spider */
	wd719x_ग_लिखोl(wd, WD719X_AMR_SCB_IN, risc_init[0]);
	wd719x_ग_लिखोl(wd, WD719X_AMR_SCB_IN + 4, risc_init[1]);
	wd719x_ग_लिखोl(wd, WD719X_AMR_SCB_IN + 8, risc_init[2]);

	/* disable पूर्णांकerrupts during initialization of RISC */
	wd719x_ग_लिखोb(wd, WD719X_AMR_CMD_PARAM, WD719X_DISABLE_INT);

	/* issue INITIALIZE RISC comand */
	wd719x_ग_लिखोb(wd, WD719X_AMR_COMMAND, WD719X_CMD_INIT_RISC);
	/* enable advanced mode (wake up RISC) */
	wd719x_ग_लिखोb(wd, WD719X_PCI_MODE_SELECT, WD719X_ENABLE_ADVANCE_MODE);
	udelay(WD719X_WAIT_FOR_RISC);

	ret = wd719x_रुको_करोne(wd, WD719X_WAIT_FOR_RISC);
	/* clear पूर्णांकerrupt status रेजिस्टर */
	wd719x_ग_लिखोb(wd, WD719X_AMR_INT_STATUS, WD719X_INT_NONE);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "Unable to initialize RISC\n");
		जाओ wd719x_init_end;
	पूर्ण
	/* RISC is up and running */

	/* Read FW version from RISC */
	ret = wd719x_direct_cmd(wd, WD719X_CMD_READ_FIRMVER, 0, 0, 0, 0,
				WD719X_WAIT_FOR_RISC);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "Unable to read firmware version\n");
		जाओ wd719x_init_end;
	पूर्ण
	dev_info(&wd->pdev->dev, "RISC initialized with firmware version %.2x.%.2x\n",
			wd719x_पढ़ोb(wd, WD719X_AMR_SCB_OUT + 1),
			wd719x_पढ़ोb(wd, WD719X_AMR_SCB_OUT));

	/* RESET SCSI bus */
	ret = wd719x_direct_cmd(wd, WD719X_CMD_BUSRESET, 0, 0, 0, 0,
				WD719X_WAIT_FOR_SCSI_RESET);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "SCSI bus reset failed\n");
		जाओ wd719x_init_end;
	पूर्ण

	/* use HostParameter काष्ठाure to set Spider's Host Parameter Block */
	ret = wd719x_direct_cmd(wd, WD719X_CMD_SET_PARAM, 0,
				माप(काष्ठा wd719x_host_param), 0,
				wd->params_phys, WD719X_WAIT_FOR_RISC);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "Failed to set HOST PARAMETERS\n");
		जाओ wd719x_init_end;
	पूर्ण

	/* initiate SCAM (करोes nothing अगर disabled in BIOS) */
	/* bug?: we should pass a mask of अटल IDs which we करोn't have */
	ret = wd719x_direct_cmd(wd, WD719X_CMD_INIT_SCAM, 0, 0, 0, 0,
				WD719X_WAIT_FOR_SCSI_RESET);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "SCAM initialization failed\n");
		जाओ wd719x_init_end;
	पूर्ण

	/* clear AMR_BIOS_SHARE_INT रेजिस्टर */
	wd719x_ग_लिखोb(wd, WD719X_AMR_BIOS_SHARE_INT, 0);

wd719x_init_end:
	release_firmware(fw_wcs);
	release_firmware(fw_risc);

	वापस ret;
पूर्ण

अटल पूर्णांक wd719x_पात(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक action, result;
	अचिन्हित दीर्घ flags;
	काष्ठा wd719x_scb *scb = scsi_cmd_priv(cmd);
	काष्ठा wd719x *wd = shost_priv(cmd->device->host);

	dev_info(&wd->pdev->dev, "abort command, tag: %x\n", cmd->tag);

	action = /*cmd->tag ? WD719X_CMD_ABORT_TAG : */WD719X_CMD_ABORT;

	spin_lock_irqsave(wd->sh->host_lock, flags);
	result = wd719x_direct_cmd(wd, action, cmd->device->id,
				   cmd->device->lun, cmd->tag, scb->phys, 0);
	wd719x_finish_cmd(scb, DID_ABORT);
	spin_unlock_irqrestore(wd->sh->host_lock, flags);
	अगर (result)
		वापस FAILED;

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक wd719x_reset(काष्ठा scsi_cmnd *cmd, u8 opcode, u8 device)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags;
	काष्ठा wd719x *wd = shost_priv(cmd->device->host);
	काष्ठा wd719x_scb *scb, *पंचांगp;

	dev_info(&wd->pdev->dev, "%s reset requested\n",
		 (opcode == WD719X_CMD_BUSRESET) ? "bus" : "device");

	spin_lock_irqsave(wd->sh->host_lock, flags);
	result = wd719x_direct_cmd(wd, opcode, device, 0, 0, 0,
				   WD719X_WAIT_FOR_SCSI_RESET);
	/* flush all SCBs (or all क्रम a device अगर dev_reset) */
	list_क्रम_each_entry_safe(scb, पंचांगp, &wd->active_scbs, list) अणु
		अगर (opcode == WD719X_CMD_BUSRESET ||
		    scb->cmd->device->id == device)
			wd719x_finish_cmd(scb, DID_RESET);
	पूर्ण
	spin_unlock_irqrestore(wd->sh->host_lock, flags);
	अगर (result)
		वापस FAILED;

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक wd719x_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	वापस wd719x_reset(cmd, WD719X_CMD_RESET, cmd->device->id);
पूर्ण

अटल पूर्णांक wd719x_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	वापस wd719x_reset(cmd, WD719X_CMD_BUSRESET, 0);
पूर्ण

अटल पूर्णांक wd719x_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा wd719x *wd = shost_priv(cmd->device->host);
	काष्ठा wd719x_scb *scb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	dev_info(&wd->pdev->dev, "host reset requested\n");
	spin_lock_irqsave(wd->sh->host_lock, flags);
	/* stop the RISC */
	अगर (wd719x_direct_cmd(wd, WD719X_CMD_SLEEP, 0, 0, 0, 0,
			      WD719X_WAIT_FOR_RISC))
		dev_warn(&wd->pdev->dev, "RISC sleep command failed\n");
	/* disable RISC */
	wd719x_ग_लिखोb(wd, WD719X_PCI_MODE_SELECT, 0);

	/* flush all SCBs */
	list_क्रम_each_entry_safe(scb, पंचांगp, &wd->active_scbs, list)
		wd719x_finish_cmd(scb, DID_RESET);
	spin_unlock_irqrestore(wd->sh->host_lock, flags);

	/* Try to reinit the RISC */
	वापस wd719x_chip_init(wd) == 0 ? SUCCESS : FAILED;
पूर्ण

अटल पूर्णांक wd719x_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
			    sector_t capacity, पूर्णांक geom[])
अणु
	अगर (capacity >= 0x200000) अणु
		geom[0] = 255;	/* heads */
		geom[1] = 63;	/* sectors */
	पूर्ण अन्यथा अणु
		geom[0] = 64;	/* heads */
		geom[1] = 32;	/* sectors */
	पूर्ण
	geom[2] = sector_भाग(capacity, geom[0] * geom[1]);	/* cylinders */

	वापस 0;
पूर्ण

/* process a SCB-completion पूर्णांकerrupt */
अटल अंतरभूत व्योम wd719x_पूर्णांकerrupt_SCB(काष्ठा wd719x *wd,
					जोड़ wd719x_regs regs,
					काष्ठा wd719x_scb *scb)
अणु
	पूर्णांक result;

	/* now have to find result from card */
	चयन (regs.bytes.SUE) अणु
	हाल WD719X_SUE_NOERRORS:
		result = DID_OK;
		अवरोध;
	हाल WD719X_SUE_REJECTED:
		dev_err(&wd->pdev->dev, "command rejected\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_SCBQFULL:
		dev_err(&wd->pdev->dev, "SCB queue is full\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_TERM:
		dev_dbg(&wd->pdev->dev, "SCB terminated by direct command\n");
		result = DID_ABORT;	/* or DID_RESET? */
		अवरोध;
	हाल WD719X_SUE_CHAN1ABORT:
	हाल WD719X_SUE_CHAN23ABORT:
		result = DID_ABORT;
		dev_err(&wd->pdev->dev, "DMA abort\n");
		अवरोध;
	हाल WD719X_SUE_CHAN1PAR:
	हाल WD719X_SUE_CHAN23PAR:
		result = DID_PARITY;
		dev_err(&wd->pdev->dev, "DMA parity error\n");
		अवरोध;
	हाल WD719X_SUE_TIMEOUT:
		result = DID_TIME_OUT;
		dev_dbg(&wd->pdev->dev, "selection timeout\n");
		अवरोध;
	हाल WD719X_SUE_RESET:
		dev_dbg(&wd->pdev->dev, "bus reset occurred\n");
		result = DID_RESET;
		अवरोध;
	हाल WD719X_SUE_BUSERROR:
		dev_dbg(&wd->pdev->dev, "SCSI bus error\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_WRONGWAY:
		dev_err(&wd->pdev->dev, "wrong data transfer direction\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_BADPHASE:
		dev_err(&wd->pdev->dev, "invalid SCSI phase\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_TOOLONG:
		dev_err(&wd->pdev->dev, "record too long\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_BUSFREE:
		dev_err(&wd->pdev->dev, "unexpected bus free\n");
		result = DID_NO_CONNECT; /* or DID_ERROR ???*/
		अवरोध;
	हाल WD719X_SUE_ARSDONE:
		dev_dbg(&wd->pdev->dev, "auto request sense\n");
		अगर (regs.bytes.SCSI == 0)
			result = DID_OK;
		अन्यथा
			result = DID_PARITY;
		अवरोध;
	हाल WD719X_SUE_IGNORED:
		dev_err(&wd->pdev->dev, "target id %d ignored command\n",
			scb->cmd->device->id);
		result = DID_NO_CONNECT;
		अवरोध;
	हाल WD719X_SUE_WRONGTAGS:
		dev_err(&wd->pdev->dev, "reversed tags\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_BADTAGS:
		dev_err(&wd->pdev->dev, "tag type not supported by target\n");
		result = DID_ERROR;
		अवरोध;
	हाल WD719X_SUE_NOSCAMID:
		dev_err(&wd->pdev->dev, "no SCAM soft ID available\n");
		result = DID_ERROR;
		अवरोध;
	शेष:
		dev_warn(&wd->pdev->dev, "unknown SUE error code: 0x%x\n",
			 regs.bytes.SUE);
		result = DID_ERROR;
		अवरोध;
	पूर्ण

	wd719x_finish_cmd(scb, result);
पूर्ण

अटल irqवापस_t wd719x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wd719x *wd = dev_id;
	जोड़ wd719x_regs regs;
	अचिन्हित दीर्घ flags;
	u32 SCB_out;

	spin_lock_irqsave(wd->sh->host_lock, flags);
	/* पढ़ो SCB poपूर्णांकer back from card */
	SCB_out = wd719x_पढ़ोl(wd, WD719X_AMR_SCB_OUT);
	/* पढ़ो all status info at once */
	regs.all = cpu_to_le32(wd719x_पढ़ोl(wd, WD719X_AMR_OP_CODE));

	चयन (regs.bytes.INT) अणु
	हाल WD719X_INT_NONE:
		spin_unlock_irqrestore(wd->sh->host_lock, flags);
		वापस IRQ_NONE;
	हाल WD719X_INT_LINKNOSTATUS:
		dev_err(&wd->pdev->dev, "linked command completed with no status\n");
		अवरोध;
	हाल WD719X_INT_BADINT:
		dev_err(&wd->pdev->dev, "unsolicited interrupt\n");
		अवरोध;
	हाल WD719X_INT_NOERRORS:
	हाल WD719X_INT_LINKNOERRORS:
	हाल WD719X_INT_ERRORSLOGGED:
	हाल WD719X_INT_SPIDERFAILED:
		/* was the cmd completed a direct or SCB command? */
		अगर (regs.bytes.OPC == WD719X_CMD_PROCESS_SCB) अणु
			काष्ठा wd719x_scb *scb;
			list_क्रम_each_entry(scb, &wd->active_scbs, list)
				अगर (SCB_out == scb->phys)
					अवरोध;
			अगर (SCB_out == scb->phys)
				wd719x_पूर्णांकerrupt_SCB(wd, regs, scb);
			अन्यथा
				dev_err(&wd->pdev->dev, "card returned invalid SCB pointer\n");
		पूर्ण अन्यथा
			dev_dbg(&wd->pdev->dev, "direct command 0x%x completed\n",
				 regs.bytes.OPC);
		अवरोध;
	हाल WD719X_INT_PIOREADY:
		dev_err(&wd->pdev->dev, "card indicates PIO data ready but we never use PIO\n");
		/* पूर्णांकerrupt will not be cleared until all data is पढ़ो */
		अवरोध;
	शेष:
		dev_err(&wd->pdev->dev, "unknown interrupt reason: %d\n",
			regs.bytes.INT);

	पूर्ण
	/* clear पूर्णांकerrupt so another can happen */
	wd719x_ग_लिखोb(wd, WD719X_AMR_INT_STATUS, WD719X_INT_NONE);
	spin_unlock_irqrestore(wd->sh->host_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wd719x_eeprom_reg_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा wd719x *wd = eeprom->data;
	u8 reg = wd719x_पढ़ोb(wd, WD719X_PCI_GPIO_DATA);

	eeprom->reg_data_out = reg & WD719X_EE_DO;
पूर्ण

अटल व्योम wd719x_eeprom_reg_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा wd719x *wd = eeprom->data;
	u8 reg = 0;

	अगर (eeprom->reg_data_in)
		reg |= WD719X_EE_DI;
	अगर (eeprom->reg_data_घड़ी)
		reg |= WD719X_EE_CLK;
	अगर (eeprom->reg_chip_select)
		reg |= WD719X_EE_CS;

	wd719x_ग_लिखोb(wd, WD719X_PCI_GPIO_DATA, reg);
पूर्ण

/* पढ़ो config from EEPROM so it can be करोwnloaded by the RISC on (re-)init */
अटल व्योम wd719x_पढ़ो_eeprom(काष्ठा wd719x *wd)
अणु
	काष्ठा eeprom_93cx6 eeprom;
	u8 gpio;
	काष्ठा wd719x_eeprom_header header;

	eeprom.data = wd;
	eeprom.रेजिस्टर_पढ़ो = wd719x_eeprom_reg_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = wd719x_eeprom_reg_ग_लिखो;
	eeprom.width = PCI_EEPROM_WIDTH_93C46;

	/* set all outमाला_दो to low */
	wd719x_ग_लिखोb(wd, WD719X_PCI_GPIO_DATA, 0);
	/* configure GPIO pins */
	gpio = wd719x_पढ़ोb(wd, WD719X_PCI_GPIO_CONTROL);
	/* GPIO outमाला_दो */
	gpio &= (~(WD719X_EE_CLK | WD719X_EE_DI | WD719X_EE_CS));
	/* GPIO input */
	gpio |= WD719X_EE_DO;
	wd719x_ग_लिखोb(wd, WD719X_PCI_GPIO_CONTROL, gpio);

	/* पढ़ो EEPROM header */
	eeprom_93cx6_multiपढ़ोb(&eeprom, 0, (u8 *)&header, माप(header));

	अगर (header.sig1 == 'W' && header.sig2 == 'D')
		eeprom_93cx6_multiपढ़ोb(&eeprom, header.cfg_offset,
					(u8 *)wd->params,
					माप(काष्ठा wd719x_host_param));
	अन्यथा अणु /* शेष EEPROM values */
		dev_warn(&wd->pdev->dev, "EEPROM signature is invalid (0x%02x 0x%02x), using default values\n",
			 header.sig1, header.sig2);
		wd->params->ch_1_th	= 0x10;	/* 16 DWs = 64 B */
		wd->params->scsi_conf	= 0x4c;	/* 48ma, spue, parity check */
		wd->params->own_scsi_id	= 0x07;	/* ID 7, SCAM disabled */
		wd->params->sel_समयout = 0x4d;	/* 250 ms */
		wd->params->sleep_समयr	= 0x01;
		wd->params->cdb_size	= cpu_to_le16(0x5555);	/* all 6 B */
		wd->params->scsi_pad	= 0x1b;
		अगर (wd->type == WD719X_TYPE_7193) /* narrow card - disable */
			wd->params->wide = cpu_to_le32(0x00000000);
		अन्यथा	/* initiate & respond to WIDE messages */
			wd->params->wide = cpu_to_le32(0xffffffff);
		wd->params->sync	= cpu_to_le32(0xffffffff);
		wd->params->soft_mask	= 0x00;	/* all disabled */
		wd->params->unsol_mask	= 0x00;	/* all disabled */
	पूर्ण
	/* disable TAGGED messages */
	wd->params->tag_en = cpu_to_le16(0x0000);
पूर्ण

/* Read card type from GPIO bits 1 and 3 */
अटल क्रमागत wd719x_card_type wd719x_detect_type(काष्ठा wd719x *wd)
अणु
	u8 card = wd719x_पढ़ोb(wd, WD719X_PCI_GPIO_CONTROL);

	card |= WD719X_GPIO_ID_BITS;
	wd719x_ग_लिखोb(wd, WD719X_PCI_GPIO_CONTROL, card);
	card = wd719x_पढ़ोb(wd, WD719X_PCI_GPIO_DATA) & WD719X_GPIO_ID_BITS;
	चयन (card) अणु
	हाल 0x08:
		वापस WD719X_TYPE_7193;
	हाल 0x02:
		वापस WD719X_TYPE_7197;
	हाल 0x00:
		वापस WD719X_TYPE_7296;
	शेष:
		dev_warn(&wd->pdev->dev, "unknown card type 0x%x\n", card);
		वापस WD719X_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक wd719x_board_found(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा wd719x *wd = shost_priv(sh);
	अटल स्थिर अक्षर * स्थिर card_types[] = अणु
		"Unknown card", "WD7193", "WD7197", "WD7296"
	पूर्ण;
	पूर्णांक ret;

	INIT_LIST_HEAD(&wd->active_scbs);

	sh->base = pci_resource_start(wd->pdev, 0);

	wd->type = wd719x_detect_type(wd);

	wd->sh = sh;
	sh->irq = wd->pdev->irq;
	wd->fw_virt = शून्य;

	/* memory area क्रम host (EEPROM) parameters */
	wd->params = dma_alloc_coherent(&wd->pdev->dev,
					माप(काष्ठा wd719x_host_param),
					&wd->params_phys, GFP_KERNEL);
	अगर (!wd->params) अणु
		dev_warn(&wd->pdev->dev, "unable to allocate parameter buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/* memory area क्रम the RISC क्रम hash table of outstanding requests */
	wd->hash_virt = dma_alloc_coherent(&wd->pdev->dev,
					   WD719X_HASH_TABLE_SIZE,
					   &wd->hash_phys, GFP_KERNEL);
	अगर (!wd->hash_virt) अणु
		dev_warn(&wd->pdev->dev, "unable to allocate hash buffer\n");
		ret = -ENOMEM;
		जाओ fail_मुक्त_params;
	पूर्ण

	ret = request_irq(wd->pdev->irq, wd719x_पूर्णांकerrupt, IRQF_SHARED,
			  "wd719x", wd);
	अगर (ret) अणु
		dev_warn(&wd->pdev->dev, "unable to assign IRQ %d\n",
			 wd->pdev->irq);
		जाओ fail_मुक्त_hash;
	पूर्ण

	/* पढ़ो parameters from EEPROM */
	wd719x_पढ़ो_eeprom(wd);

	ret = wd719x_chip_init(wd);
	अगर (ret)
		जाओ fail_मुक्त_irq;

	sh->this_id = wd->params->own_scsi_id & WD719X_EE_SCSI_ID_MASK;

	dev_info(&wd->pdev->dev, "%s at I/O 0x%lx, IRQ %u, SCSI ID %d\n",
		 card_types[wd->type], sh->base, sh->irq, sh->this_id);

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(wd->pdev->irq, wd);
fail_मुक्त_hash:
	dma_मुक्त_coherent(&wd->pdev->dev, WD719X_HASH_TABLE_SIZE, wd->hash_virt,
			    wd->hash_phys);
fail_मुक्त_params:
	dma_मुक्त_coherent(&wd->pdev->dev, माप(काष्ठा wd719x_host_param),
			    wd->params, wd->params_phys);

	वापस ret;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा wd719x_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "Western Digital 719x",
	.cmd_size			= माप(काष्ठा wd719x_scb),
	.queuecommand			= wd719x_queuecommand,
	.eh_पात_handler		= wd719x_पात,
	.eh_device_reset_handler	= wd719x_dev_reset,
	.eh_bus_reset_handler		= wd719x_bus_reset,
	.eh_host_reset_handler		= wd719x_host_reset,
	.bios_param			= wd719x_biosparam,
	.proc_name			= "wd719x",
	.can_queue			= 255,
	.this_id			= 7,
	.sg_tablesize			= WD719X_SG,
पूर्ण;

अटल पूर्णांक wd719x_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *d)
अणु
	पूर्णांक err;
	काष्ठा Scsi_Host *sh;
	काष्ठा wd719x *wd;

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ fail;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		dev_warn(&pdev->dev, "Unable to set 32-bit DMA mask\n");
		जाओ disable_device;
	पूर्ण

	err = pci_request_regions(pdev, "wd719x");
	अगर (err)
		जाओ disable_device;
	pci_set_master(pdev);

	err = -ENODEV;
	अगर (pci_resource_len(pdev, 0) == 0)
		जाओ release_region;

	err = -ENOMEM;
	sh = scsi_host_alloc(&wd719x_ढाँचा, माप(काष्ठा wd719x));
	अगर (!sh)
		जाओ release_region;

	wd = shost_priv(sh);
	wd->base = pci_iomap(pdev, 0, 0);
	अगर (!wd->base)
		जाओ मुक्त_host;
	wd->pdev = pdev;

	err = wd719x_board_found(sh);
	अगर (err)
		जाओ unmap;

	err = scsi_add_host(sh, &wd->pdev->dev);
	अगर (err)
		जाओ destroy;

	scsi_scan_host(sh);

	pci_set_drvdata(pdev, sh);
	वापस 0;

destroy:
	wd719x_destroy(wd);
unmap:
	pci_iounmap(pdev, wd->base);
मुक्त_host:
	scsi_host_put(sh);
release_region:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
fail:
	वापस err;
पूर्ण


अटल व्योम wd719x_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *sh = pci_get_drvdata(pdev);
	काष्ठा wd719x *wd = shost_priv(sh);

	scsi_हटाओ_host(sh);
	wd719x_destroy(wd);
	pci_iounmap(pdev, wd->base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	scsi_host_put(sh);
पूर्ण

अटल स्थिर काष्ठा pci_device_id wd719x_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_WD, 0x3296) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, wd719x_pci_table);

अटल काष्ठा pci_driver wd719x_pci_driver = अणु
	.name =		"wd719x",
	.id_table =	wd719x_pci_table,
	.probe =	wd719x_pci_probe,
	.हटाओ =	wd719x_pci_हटाओ,
पूर्ण;

module_pci_driver(wd719x_pci_driver);

MODULE_DESCRIPTION("Western Digital WD7193/7197/7296 SCSI driver");
MODULE_AUTHOR("Ondrej Zary, Aaron Dewell, Juergen Gaertner");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("wd719x-wcs.bin");
MODULE_FIRMWARE("wd719x-risc.bin");
