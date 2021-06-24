<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Micron P320 SSD
 *   Copyright (C) 2011 Micron Technology, Inc.
 *
 * Portions of this code were derived from works subjected to the
 * following copyright:
 *    Copyright (C) 2009 Integrated Device Technology, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ata.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/smp.h>
#समावेश <linux/compat.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/genhd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/bपन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <../drivers/ata/ahci.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/numa.h>
#समावेश "mtip32xx.h"

#घोषणा HW_CMD_SLOT_SZ		(MTIP_MAX_COMMAND_SLOTS * 32)

/* DMA region containing RX Fis, Identअगरy, RLE10, and SMART buffers */
#घोषणा AHCI_RX_FIS_SZ          0x100
#घोषणा AHCI_RX_FIS_OFFSET      0x0
#घोषणा AHCI_IDFY_SZ            ATA_SECT_SIZE
#घोषणा AHCI_IDFY_OFFSET        0x400
#घोषणा AHCI_SECTBUF_SZ         ATA_SECT_SIZE
#घोषणा AHCI_SECTBUF_OFFSET     0x800
#घोषणा AHCI_SMARTBUF_SZ        ATA_SECT_SIZE
#घोषणा AHCI_SMARTBUF_OFFSET    0xC00
/* 0x100 + 0x200 + 0x200 + 0x200 is smaller than 4k but we pad it out */
#घोषणा BLOCK_DMA_ALLOC_SZ      4096

/* DMA region containing command table (should be 8192 bytes) */
#घोषणा AHCI_CMD_SLOT_SZ        माप(काष्ठा mtip_cmd_hdr)
#घोषणा AHCI_CMD_TBL_SZ         (MTIP_MAX_COMMAND_SLOTS * AHCI_CMD_SLOT_SZ)
#घोषणा AHCI_CMD_TBL_OFFSET     0x0

/* DMA region per command (contains header and SGL) */
#घोषणा AHCI_CMD_TBL_HDR_SZ     0x80
#घोषणा AHCI_CMD_TBL_HDR_OFFSET 0x0
#घोषणा AHCI_CMD_TBL_SGL_SZ     (MTIP_MAX_SG * माप(काष्ठा mtip_cmd_sg))
#घोषणा AHCI_CMD_TBL_SGL_OFFSET AHCI_CMD_TBL_HDR_SZ
#घोषणा CMD_DMA_ALLOC_SZ        (AHCI_CMD_TBL_SGL_SZ + AHCI_CMD_TBL_HDR_SZ)


#घोषणा HOST_CAP_NZDMA		(1 << 19)
#घोषणा HOST_HSORG		0xFC
#घोषणा HSORG_DISABLE_SLOTGRP_INTR (1<<24)
#घोषणा HSORG_DISABLE_SLOTGRP_PXIS (1<<16)
#घोषणा HSORG_HWREV		0xFF00
#घोषणा HSORG_STYLE		0x8
#घोषणा HSORG_SLOTGROUPS	0x7

#घोषणा PORT_COMMAND_ISSUE	0x38
#घोषणा PORT_SDBV		0x7C

#घोषणा PORT_OFFSET		0x100
#घोषणा PORT_MEM_SIZE		0x80

#घोषणा PORT_IRQ_ERR \
	(PORT_IRQ_HBUS_ERR | PORT_IRQ_IF_ERR | PORT_IRQ_CONNECT | \
	 PORT_IRQ_PHYRDY | PORT_IRQ_UNK_FIS | PORT_IRQ_BAD_PMP | \
	 PORT_IRQ_TF_ERR | PORT_IRQ_HBUS_DATA_ERR | PORT_IRQ_IF_NONFATAL | \
	 PORT_IRQ_OVERFLOW)
#घोषणा PORT_IRQ_LEGACY \
	(PORT_IRQ_PIOS_FIS | PORT_IRQ_D2H_REG_FIS)
#घोषणा PORT_IRQ_HANDLED \
	(PORT_IRQ_SDB_FIS | PORT_IRQ_LEGACY | \
	 PORT_IRQ_TF_ERR | PORT_IRQ_IF_ERR | \
	 PORT_IRQ_CONNECT | PORT_IRQ_PHYRDY)
#घोषणा DEF_PORT_IRQ \
	(PORT_IRQ_ERR | PORT_IRQ_LEGACY | PORT_IRQ_SDB_FIS)

/* product numbers */
#घोषणा MTIP_PRODUCT_UNKNOWN	0x00
#घोषणा MTIP_PRODUCT_ASICFPGA	0x11

/* Device instance number, incremented each समय a device is probed. */
अटल पूर्णांक instance;

अटल LIST_HEAD(online_list);
अटल LIST_HEAD(removing_list);
अटल DEFINE_SPINLOCK(dev_lock);

/*
 * Global variable used to hold the major block device number
 * allocated in mtip_init().
 */
अटल पूर्णांक mtip_major;
अटल काष्ठा dentry *dfs_parent;
अटल काष्ठा dentry *dfs_device_status;

अटल u32 cpu_use[NR_CPUS];

अटल DEFINE_IDA(rssd_index_ida);

अटल पूर्णांक mtip_block_initialize(काष्ठा driver_data *dd);

#अगर_घोषित CONFIG_COMPAT
काष्ठा mtip_compat_ide_task_request_s अणु
	__u8		io_ports[8];
	__u8		hob_ports[8];
	ide_reg_valid_t	out_flags;
	ide_reg_valid_t	in_flags;
	पूर्णांक		data_phase;
	पूर्णांक		req_cmd;
	compat_uदीर्घ_t	out_size;
	compat_uदीर्घ_t	in_size;
पूर्ण;
#पूर्ण_अगर

/*
 * This function check_क्रम_surprise_removal is called
 * जबतक card is हटाओd from the प्रणाली and it will
 * पढ़ो the venकरोr id from the configuration space
 *
 * @pdev Poपूर्णांकer to the pci_dev काष्ठाure.
 *
 * वापस value
 *	 true अगर device हटाओd, अन्यथा false
 */
अटल bool mtip_check_surprise_removal(काष्ठा pci_dev *pdev)
अणु
	u16 venकरोr_id = 0;
	काष्ठा driver_data *dd = pci_get_drvdata(pdev);

	अगर (dd->sr)
		वापस true;

       /* Read the venकरोrID from the configuration space */
	pci_पढ़ो_config_word(pdev, 0x00, &venकरोr_id);
	अगर (venकरोr_id == 0xFFFF) अणु
		dd->sr = true;
		अगर (dd->queue)
			blk_queue_flag_set(QUEUE_FLAG_DEAD, dd->queue);
		अन्यथा
			dev_warn(&dd->pdev->dev,
				"%s: dd->queue is NULL\n", __func__);
		वापस true; /* device हटाओd */
	पूर्ण

	वापस false; /* device present */
पूर्ण

अटल काष्ठा mtip_cmd *mtip_cmd_from_tag(काष्ठा driver_data *dd,
					  अचिन्हित पूर्णांक tag)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = dd->queue->queue_hw_ctx[0];

	वापस blk_mq_rq_to_pdu(blk_mq_tag_to_rq(hctx->tags, tag));
पूर्ण

/*
 * Reset the HBA (without sleeping)
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0	The reset was successful.
 *	-1	The HBA Reset bit did not clear.
 */
अटल पूर्णांक mtip_hba_reset(काष्ठा driver_data *dd)
अणु
	अचिन्हित दीर्घ समयout;

	/* Set the reset bit */
	ग_लिखोl(HOST_RESET, dd->mmio + HOST_CTL);

	/* Flush */
	पढ़ोl(dd->mmio + HOST_CTL);

	/*
	 * Spin क्रम up to 10 seconds रुकोing क्रम reset acknowledgement. Spec
	 * is 1 sec but in LUN failure conditions, up to 10 secs are required
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(10000);
	करो अणु
		mdelay(10);
		अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))
			वापस -1;

	पूर्ण जबतक ((पढ़ोl(dd->mmio + HOST_CTL) & HOST_RESET)
		 && समय_beक्रमe(jअगरfies, समयout));

	अगर (पढ़ोl(dd->mmio + HOST_CTL) & HOST_RESET)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Issue a command to the hardware.
 *
 * Set the appropriate bit in the s_active and Command Issue hardware
 * रेजिस्टरs, causing hardware command processing to begin.
 *
 * @port Poपूर्णांकer to the port काष्ठाure.
 * @tag  The tag of the command to be issued.
 *
 * वापस value
 *      None
 */
अटल अंतरभूत व्योम mtip_issue_ncq_command(काष्ठा mtip_port *port, पूर्णांक tag)
अणु
	पूर्णांक group = tag >> 5;

	/* guard SACT and CI रेजिस्टरs */
	spin_lock(&port->cmd_issue_lock[group]);
	ग_लिखोl((1 << MTIP_TAG_BIT(tag)),
			port->s_active[MTIP_TAG_INDEX(tag)]);
	ग_लिखोl((1 << MTIP_TAG_BIT(tag)),
			port->cmd_issue[MTIP_TAG_INDEX(tag)]);
	spin_unlock(&port->cmd_issue_lock[group]);
पूर्ण

/*
 * Enable/disable the reception of FIS
 *
 * @port   Poपूर्णांकer to the port data काष्ठाure
 * @enable 1 to enable, 0 to disable
 *
 * वापस value
 *	Previous state: 1 enabled, 0 disabled
 */
अटल पूर्णांक mtip_enable_fis(काष्ठा mtip_port *port, पूर्णांक enable)
अणु
	u32 पंचांगp;

	/* enable FIS reception */
	पंचांगp = पढ़ोl(port->mmio + PORT_CMD);
	अगर (enable)
		ग_लिखोl(पंचांगp | PORT_CMD_FIS_RX, port->mmio + PORT_CMD);
	अन्यथा
		ग_लिखोl(पंचांगp & ~PORT_CMD_FIS_RX, port->mmio + PORT_CMD);

	/* Flush */
	पढ़ोl(port->mmio + PORT_CMD);

	वापस (((पंचांगp & PORT_CMD_FIS_RX) == PORT_CMD_FIS_RX));
पूर्ण

/*
 * Enable/disable the DMA engine
 *
 * @port   Poपूर्णांकer to the port data काष्ठाure
 * @enable 1 to enable, 0 to disable
 *
 * वापस value
 *	Previous state: 1 enabled, 0 disabled.
 */
अटल पूर्णांक mtip_enable_engine(काष्ठा mtip_port *port, पूर्णांक enable)
अणु
	u32 पंचांगp;

	/* enable FIS reception */
	पंचांगp = पढ़ोl(port->mmio + PORT_CMD);
	अगर (enable)
		ग_लिखोl(पंचांगp | PORT_CMD_START, port->mmio + PORT_CMD);
	अन्यथा
		ग_लिखोl(पंचांगp & ~PORT_CMD_START, port->mmio + PORT_CMD);

	पढ़ोl(port->mmio + PORT_CMD);
	वापस (((पंचांगp & PORT_CMD_START) == PORT_CMD_START));
पूर्ण

/*
 * Enables the port DMA engine and FIS reception.
 *
 * वापस value
 *	None
 */
अटल अंतरभूत व्योम mtip_start_port(काष्ठा mtip_port *port)
अणु
	/* Enable FIS reception */
	mtip_enable_fis(port, 1);

	/* Enable the DMA engine */
	mtip_enable_engine(port, 1);
पूर्ण

/*
 * Deinitialize a port by disabling port पूर्णांकerrupts, the DMA engine,
 * and FIS reception.
 *
 * @port Poपूर्णांकer to the port काष्ठाure
 *
 * वापस value
 *	None
 */
अटल अंतरभूत व्योम mtip_deinit_port(काष्ठा mtip_port *port)
अणु
	/* Disable पूर्णांकerrupts on this port */
	ग_लिखोl(0, port->mmio + PORT_IRQ_MASK);

	/* Disable the DMA engine */
	mtip_enable_engine(port, 0);

	/* Disable FIS reception */
	mtip_enable_fis(port, 0);
पूर्ण

/*
 * Initialize a port.
 *
 * This function deinitializes the port by calling mtip_deinit_port() and
 * then initializes it by setting the command header and RX FIS addresses,
 * clearing the SError रेजिस्टर and any pending port पूर्णांकerrupts beक्रमe
 * re-enabling the शेष set of port पूर्णांकerrupts.
 *
 * @port Poपूर्णांकer to the port काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_init_port(काष्ठा mtip_port *port)
अणु
	पूर्णांक i;
	mtip_deinit_port(port);

	/* Program the command list base and FIS base addresses */
	अगर (पढ़ोl(port->dd->mmio + HOST_CAP) & HOST_CAP_64) अणु
		ग_लिखोl((port->command_list_dma >> 16) >> 16,
			 port->mmio + PORT_LST_ADDR_HI);
		ग_लिखोl((port->rxfis_dma >> 16) >> 16,
			 port->mmio + PORT_FIS_ADDR_HI);
		set_bit(MTIP_PF_HOST_CAP_64, &port->flags);
	पूर्ण

	ग_लिखोl(port->command_list_dma & 0xFFFFFFFF,
			port->mmio + PORT_LST_ADDR);
	ग_लिखोl(port->rxfis_dma & 0xFFFFFFFF, port->mmio + PORT_FIS_ADDR);

	/* Clear SError */
	ग_लिखोl(पढ़ोl(port->mmio + PORT_SCR_ERR), port->mmio + PORT_SCR_ERR);

	/* reset the completed रेजिस्टरs.*/
	क्रम (i = 0; i < port->dd->slot_groups; i++)
		ग_लिखोl(0xFFFFFFFF, port->completed[i]);

	/* Clear any pending पूर्णांकerrupts क्रम this port */
	ग_लिखोl(पढ़ोl(port->mmio + PORT_IRQ_STAT), port->mmio + PORT_IRQ_STAT);

	/* Clear any pending पूर्णांकerrupts on the HBA. */
	ग_लिखोl(पढ़ोl(port->dd->mmio + HOST_IRQ_STAT),
					port->dd->mmio + HOST_IRQ_STAT);

	/* Enable port पूर्णांकerrupts */
	ग_लिखोl(DEF_PORT_IRQ, port->mmio + PORT_IRQ_MASK);
पूर्ण

/*
 * Restart a port
 *
 * @port Poपूर्णांकer to the port data काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_restart_port(काष्ठा mtip_port *port)
अणु
	अचिन्हित दीर्घ समयout;

	/* Disable the DMA engine */
	mtip_enable_engine(port, 0);

	/* Chip quirk: रुको up to 500ms क्रम PxCMD.CR == 0 */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक ((पढ़ोl(port->mmio + PORT_CMD) & PORT_CMD_LIST_ON)
		 && समय_beक्रमe(jअगरfies, समयout))
		;

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		वापस;

	/*
	 * Chip quirk: escalate to hba reset अगर
	 * PxCMD.CR not clear after 500 ms
	 */
	अगर (पढ़ोl(port->mmio + PORT_CMD) & PORT_CMD_LIST_ON) अणु
		dev_warn(&port->dd->pdev->dev,
			"PxCMD.CR not clear, escalating reset\n");

		अगर (mtip_hba_reset(port->dd))
			dev_err(&port->dd->pdev->dev,
				"HBA reset escalation failed.\n");

		/* 30 ms delay beक्रमe com reset to quiesce chip */
		mdelay(30);
	पूर्ण

	dev_warn(&port->dd->pdev->dev, "Issuing COM reset\n");

	/* Set PxSCTL.DET */
	ग_लिखोl(पढ़ोl(port->mmio + PORT_SCR_CTL) |
			 1, port->mmio + PORT_SCR_CTL);
	पढ़ोl(port->mmio + PORT_SCR_CTL);

	/* Wait 1 ms to quiesce chip function */
	समयout = jअगरfies + msecs_to_jअगरfies(1);
	जबतक (समय_beक्रमe(jअगरfies, समयout))
		;

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		वापस;

	/* Clear PxSCTL.DET */
	ग_लिखोl(पढ़ोl(port->mmio + PORT_SCR_CTL) & ~1,
			 port->mmio + PORT_SCR_CTL);
	पढ़ोl(port->mmio + PORT_SCR_CTL);

	/* Wait 500 ms क्रम bit 0 of PORT_SCR_STS to be set */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (((पढ़ोl(port->mmio + PORT_SCR_STAT) & 0x01) == 0)
			 && समय_beक्रमe(jअगरfies, समयout))
		;

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		वापस;

	अगर ((पढ़ोl(port->mmio + PORT_SCR_STAT) & 0x01) == 0)
		dev_warn(&port->dd->pdev->dev,
			"COM reset failed\n");

	mtip_init_port(port);
	mtip_start_port(port);

पूर्ण

अटल पूर्णांक mtip_device_reset(काष्ठा driver_data *dd)
अणु
	पूर्णांक rv = 0;

	अगर (mtip_check_surprise_removal(dd->pdev))
		वापस 0;

	अगर (mtip_hba_reset(dd) < 0)
		rv = -EFAULT;

	mdelay(1);
	mtip_init_port(dd->port);
	mtip_start_port(dd->port);

	/* Enable पूर्णांकerrupts on the HBA. */
	ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
					dd->mmio + HOST_CTL);
	वापस rv;
पूर्ण

/*
 * Helper function क्रम tag logging
 */
अटल व्योम prपूर्णांक_tags(काष्ठा driver_data *dd,
			अक्षर *msg,
			अचिन्हित दीर्घ *tagbits,
			पूर्णांक cnt)
अणु
	अचिन्हित अक्षर tagmap[128];
	पूर्णांक group, tagmap_len = 0;

	स_रखो(tagmap, 0, माप(tagmap));
	क्रम (group = SLOTBITS_IN_LONGS; group > 0; group--)
		tagmap_len += प्र_लिखो(tagmap + tagmap_len, "%016lX ",
						tagbits[group-1]);
	dev_warn(&dd->pdev->dev,
			"%d command(s) %s: tagmap [%s]", cnt, msg, tagmap);
पूर्ण

अटल पूर्णांक mtip_पढ़ो_log_page(काष्ठा mtip_port *port, u8 page, u16 *buffer,
				dma_addr_t buffer_dma, अचिन्हित पूर्णांक sectors);
अटल पूर्णांक mtip_get_smart_attr(काष्ठा mtip_port *port, अचिन्हित पूर्णांक id,
						काष्ठा smart_attr *attrib);

अटल व्योम mtip_complete_command(काष्ठा mtip_cmd *cmd, blk_status_t status)
अणु
	काष्ठा request *req = blk_mq_rq_from_pdu(cmd);

	cmd->status = status;
	अगर (likely(!blk_should_fake_समयout(req->q)))
		blk_mq_complete_request(req);
पूर्ण

/*
 * Handle an error.
 *
 * @dd Poपूर्णांकer to the DRIVER_DATA काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_handle_tfe(काष्ठा driver_data *dd)
अणु
	पूर्णांक group, tag, bit, reissue, rv;
	काष्ठा mtip_port *port;
	काष्ठा mtip_cmd  *cmd;
	u32 completed;
	काष्ठा host_to_dev_fis *fis;
	अचिन्हित दीर्घ tagaccum[SLOTBITS_IN_LONGS];
	अचिन्हित पूर्णांक cmd_cnt = 0;
	अचिन्हित अक्षर *buf;
	अक्षर *fail_reason = शून्य;
	पूर्णांक fail_all_ncq_ग_लिखो = 0, fail_all_ncq_cmds = 0;

	dev_warn(&dd->pdev->dev, "Taskfile error\n");

	port = dd->port;

	अगर (test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags)) अणु
		cmd = mtip_cmd_from_tag(dd, MTIP_TAG_INTERNAL);
		dbg_prपूर्णांकk(MTIP_DRV_NAME " TFE for the internal command\n");
		mtip_complete_command(cmd, BLK_STS_IOERR);
		वापस;
	पूर्ण

	/* clear the tag accumulator */
	स_रखो(tagaccum, 0, SLOTBITS_IN_LONGS * माप(दीर्घ));

	/* Loop through all the groups */
	क्रम (group = 0; group < dd->slot_groups; group++) अणु
		completed = पढ़ोl(port->completed[group]);

		dev_warn(&dd->pdev->dev, "g=%u, comp=%x\n", group, completed);

		/* clear completed status रेजिस्टर in the hardware.*/
		ग_लिखोl(completed, port->completed[group]);

		/* Process successfully completed commands */
		क्रम (bit = 0; bit < 32 && completed; bit++) अणु
			अगर (!(completed & (1<<bit)))
				जारी;
			tag = (group << 5) + bit;

			/* Skip the पूर्णांकernal command slot */
			अगर (tag == MTIP_TAG_INTERNAL)
				जारी;

			cmd = mtip_cmd_from_tag(dd, tag);
			mtip_complete_command(cmd, 0);
			set_bit(tag, tagaccum);
			cmd_cnt++;
		पूर्ण
	पूर्ण

	prपूर्णांक_tags(dd, "completed (TFE)", tagaccum, cmd_cnt);

	/* Restart the port */
	mdelay(20);
	mtip_restart_port(port);

	/* Trying to determine the cause of the error */
	rv = mtip_पढ़ो_log_page(dd->port, ATA_LOG_SATA_NCQ,
				dd->port->log_buf,
				dd->port->log_buf_dma, 1);
	अगर (rv) अणु
		dev_warn(&dd->pdev->dev,
			"Error in READ LOG EXT (10h) command\n");
		/* non-critical error, करोn't fail the load */
	पूर्ण अन्यथा अणु
		buf = (अचिन्हित अक्षर *)dd->port->log_buf;
		अगर (buf[259] & 0x1) अणु
			dev_info(&dd->pdev->dev,
				"Write protect bit is set.\n");
			set_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag);
			fail_all_ncq_ग_लिखो = 1;
			fail_reason = "write protect";
		पूर्ण
		अगर (buf[288] == 0xF7) अणु
			dev_info(&dd->pdev->dev,
				"Exceeded Tmax, drive in thermal shutdown.\n");
			set_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag);
			fail_all_ncq_cmds = 1;
			fail_reason = "thermal shutdown";
		पूर्ण
		अगर (buf[288] == 0xBF) अणु
			set_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag);
			dev_info(&dd->pdev->dev,
				"Drive indicates rebuild has failed. Secure erase required.\n");
			fail_all_ncq_cmds = 1;
			fail_reason = "rebuild failed";
		पूर्ण
	पूर्ण

	/* clear the tag accumulator */
	स_रखो(tagaccum, 0, SLOTBITS_IN_LONGS * माप(दीर्घ));

	/* Loop through all the groups */
	क्रम (group = 0; group < dd->slot_groups; group++) अणु
		क्रम (bit = 0; bit < 32; bit++) अणु
			reissue = 1;
			tag = (group << 5) + bit;
			cmd = mtip_cmd_from_tag(dd, tag);

			fis = (काष्ठा host_to_dev_fis *)cmd->command;

			/* Should re-issue? */
			अगर (tag == MTIP_TAG_INTERNAL ||
			    fis->command == ATA_CMD_SET_FEATURES)
				reissue = 0;
			अन्यथा अणु
				अगर (fail_all_ncq_cmds ||
					(fail_all_ncq_ग_लिखो &&
					fis->command == ATA_CMD_FPDMA_WRITE)) अणु
					dev_warn(&dd->pdev->dev,
					"  Fail: %s w/tag %d [%s].\n",
					fis->command == ATA_CMD_FPDMA_WRITE ?
						"write" : "read",
					tag,
					fail_reason != शून्य ?
						fail_reason : "unknown");
					mtip_complete_command(cmd, BLK_STS_MEDIUM);
					जारी;
				पूर्ण
			पूर्ण

			/*
			 * First check अगर this command has
			 *  exceeded its retries.
			 */
			अगर (reissue && (cmd->retries-- > 0)) अणु

				set_bit(tag, tagaccum);

				/* Re-issue the command. */
				mtip_issue_ncq_command(port, tag);

				जारी;
			पूर्ण

			/* Retire a command that will not be reissued */
			dev_warn(&port->dd->pdev->dev,
				"retiring tag %d\n", tag);

			mtip_complete_command(cmd, BLK_STS_IOERR);
		पूर्ण
	पूर्ण
	prपूर्णांक_tags(dd, "reissued (TFE)", tagaccum, cmd_cnt);
पूर्ण

/*
 * Handle a set device bits पूर्णांकerrupt
 */
अटल अंतरभूत व्योम mtip_workq_sdbfx(काष्ठा mtip_port *port, पूर्णांक group,
							u32 completed)
अणु
	काष्ठा driver_data *dd = port->dd;
	पूर्णांक tag, bit;
	काष्ठा mtip_cmd *command;

	अगर (!completed) अणु
		WARN_ON_ONCE(!completed);
		वापस;
	पूर्ण
	/* clear completed status रेजिस्टर in the hardware.*/
	ग_लिखोl(completed, port->completed[group]);

	/* Process completed commands. */
	क्रम (bit = 0; (bit < 32) && completed; bit++) अणु
		अगर (completed & 0x01) अणु
			tag = (group << 5) | bit;

			/* skip पूर्णांकernal command slot. */
			अगर (unlikely(tag == MTIP_TAG_INTERNAL))
				जारी;

			command = mtip_cmd_from_tag(dd, tag);
			mtip_complete_command(command, 0);
		पूर्ण
		completed >>= 1;
	पूर्ण

	/* If last, re-enable पूर्णांकerrupts */
	अगर (atomic_dec_वापस(&dd->irq_workers_active) == 0)
		ग_लिखोl(0xffffffff, dd->mmio + HOST_IRQ_STAT);
पूर्ण

/*
 * Process legacy pio and d2h पूर्णांकerrupts
 */
अटल अंतरभूत व्योम mtip_process_legacy(काष्ठा driver_data *dd, u32 port_stat)
अणु
	काष्ठा mtip_port *port = dd->port;
	काष्ठा mtip_cmd *cmd = mtip_cmd_from_tag(dd, MTIP_TAG_INTERNAL);

	अगर (test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags) && cmd) अणु
		पूर्णांक group = MTIP_TAG_INDEX(MTIP_TAG_INTERNAL);
		पूर्णांक status = पढ़ोl(port->cmd_issue[group]);

		अगर (!(status & (1 << MTIP_TAG_BIT(MTIP_TAG_INTERNAL))))
			mtip_complete_command(cmd, 0);
	पूर्ण
पूर्ण

/*
 * Demux and handle errors
 */
अटल अंतरभूत व्योम mtip_process_errors(काष्ठा driver_data *dd, u32 port_stat)
अणु
	अगर (unlikely(port_stat & PORT_IRQ_CONNECT)) अणु
		dev_warn(&dd->pdev->dev,
			"Clearing PxSERR.DIAG.x\n");
		ग_लिखोl((1 << 26), dd->port->mmio + PORT_SCR_ERR);
	पूर्ण

	अगर (unlikely(port_stat & PORT_IRQ_PHYRDY)) अणु
		dev_warn(&dd->pdev->dev,
			"Clearing PxSERR.DIAG.n\n");
		ग_लिखोl((1 << 16), dd->port->mmio + PORT_SCR_ERR);
	पूर्ण

	अगर (unlikely(port_stat & ~PORT_IRQ_HANDLED)) अणु
		dev_warn(&dd->pdev->dev,
			"Port stat errors %x unhandled\n",
			(port_stat & ~PORT_IRQ_HANDLED));
		अगर (mtip_check_surprise_removal(dd->pdev))
			वापस;
	पूर्ण
	अगर (likely(port_stat & (PORT_IRQ_TF_ERR | PORT_IRQ_IF_ERR))) अणु
		set_bit(MTIP_PF_EH_ACTIVE_BIT, &dd->port->flags);
		wake_up_पूर्णांकerruptible(&dd->port->svc_रुको);
	पूर्ण
पूर्ण

अटल अंतरभूत irqवापस_t mtip_handle_irq(काष्ठा driver_data *data)
अणु
	काष्ठा driver_data *dd = (काष्ठा driver_data *) data;
	काष्ठा mtip_port *port = dd->port;
	u32 hba_stat, port_stat;
	पूर्णांक rv = IRQ_NONE;
	पूर्णांक करो_irq_enable = 1, i, workers;
	काष्ठा mtip_work *twork;

	hba_stat = पढ़ोl(dd->mmio + HOST_IRQ_STAT);
	अगर (hba_stat) अणु
		rv = IRQ_HANDLED;

		/* Acknowledge the पूर्णांकerrupt status on the port.*/
		port_stat = पढ़ोl(port->mmio + PORT_IRQ_STAT);
		अगर (unlikely(port_stat == 0xFFFFFFFF)) अणु
			mtip_check_surprise_removal(dd->pdev);
			वापस IRQ_HANDLED;
		पूर्ण
		ग_लिखोl(port_stat, port->mmio + PORT_IRQ_STAT);

		/* Demux port status */
		अगर (likely(port_stat & PORT_IRQ_SDB_FIS)) अणु
			करो_irq_enable = 0;
			WARN_ON_ONCE(atomic_पढ़ो(&dd->irq_workers_active) != 0);

			/* Start at 1: group zero is always local? */
			क्रम (i = 0, workers = 0; i < MTIP_MAX_SLOT_GROUPS;
									i++) अणु
				twork = &dd->work[i];
				twork->completed = पढ़ोl(port->completed[i]);
				अगर (twork->completed)
					workers++;
			पूर्ण

			atomic_set(&dd->irq_workers_active, workers);
			अगर (workers) अणु
				क्रम (i = 1; i < MTIP_MAX_SLOT_GROUPS; i++) अणु
					twork = &dd->work[i];
					अगर (twork->completed)
						queue_work_on(
							twork->cpu_binding,
							dd->isr_workq,
							&twork->work);
				पूर्ण

				अगर (likely(dd->work[0].completed))
					mtip_workq_sdbfx(port, 0,
							dd->work[0].completed);

			पूर्ण अन्यथा अणु
				/*
				 * Chip quirk: SDB पूर्णांकerrupt but nothing
				 * to complete
				 */
				करो_irq_enable = 1;
			पूर्ण
		पूर्ण

		अगर (unlikely(port_stat & PORT_IRQ_ERR)) अणु
			अगर (unlikely(mtip_check_surprise_removal(dd->pdev))) अणु
				/* करोn't proceed further */
				वापस IRQ_HANDLED;
			पूर्ण
			अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
							&dd->dd_flag))
				वापस rv;

			mtip_process_errors(dd, port_stat & PORT_IRQ_ERR);
		पूर्ण

		अगर (unlikely(port_stat & PORT_IRQ_LEGACY))
			mtip_process_legacy(dd, port_stat & PORT_IRQ_LEGACY);
	पूर्ण

	/* acknowledge पूर्णांकerrupt */
	अगर (unlikely(करो_irq_enable))
		ग_लिखोl(hba_stat, dd->mmio + HOST_IRQ_STAT);

	वापस rv;
पूर्ण

/*
 * HBA पूर्णांकerrupt subroutine.
 *
 * @irq		IRQ number.
 * @instance	Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	IRQ_HANDLED	A HBA पूर्णांकerrupt was pending and handled.
 *	IRQ_NONE	This पूर्णांकerrupt was not क्रम the HBA.
 */
अटल irqवापस_t mtip_irq_handler(पूर्णांक irq, व्योम *instance)
अणु
	काष्ठा driver_data *dd = instance;

	वापस mtip_handle_irq(dd);
पूर्ण

अटल व्योम mtip_issue_non_ncq_command(काष्ठा mtip_port *port, पूर्णांक tag)
अणु
	ग_लिखोl(1 << MTIP_TAG_BIT(tag), port->cmd_issue[MTIP_TAG_INDEX(tag)]);
पूर्ण

अटल bool mtip_छोड़ो_ncq(काष्ठा mtip_port *port,
				काष्ठा host_to_dev_fis *fis)
अणु
	अचिन्हित दीर्घ task_file_data;

	task_file_data = पढ़ोl(port->mmio+PORT_TFDATA);
	अगर ((task_file_data & 1))
		वापस false;

	अगर (fis->command == ATA_CMD_SEC_ERASE_PREP) अणु
		port->ic_छोड़ो_समयr = jअगरfies;
		वापस true;
	पूर्ण अन्यथा अगर ((fis->command == ATA_CMD_DOWNLOAD_MICRO) &&
					(fis->features == 0x03)) अणु
		set_bit(MTIP_PF_DM_ACTIVE_BIT, &port->flags);
		port->ic_छोड़ो_समयr = jअगरfies;
		वापस true;
	पूर्ण अन्यथा अगर ((fis->command == ATA_CMD_SEC_ERASE_UNIT) ||
		((fis->command == 0xFC) &&
			(fis->features == 0x27 || fis->features == 0x72 ||
			 fis->features == 0x62 || fis->features == 0x26))) अणु
		clear_bit(MTIP_DDF_SEC_LOCK_BIT, &port->dd->dd_flag);
		clear_bit(MTIP_DDF_REBUILD_FAILED_BIT, &port->dd->dd_flag);
		/* Com reset after secure erase or lowlevel क्रमmat */
		mtip_restart_port(port);
		clear_bit(MTIP_PF_SE_ACTIVE_BIT, &port->flags);
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल bool mtip_commands_active(काष्ठा mtip_port *port)
अणु
	अचिन्हित पूर्णांक active;
	अचिन्हित पूर्णांक n;

	/*
	 * Ignore s_active bit 0 of array element 0.
	 * This bit will always be set
	 */
	active = पढ़ोl(port->s_active[0]) & 0xFFFFFFFE;
	क्रम (n = 1; n < port->dd->slot_groups; n++)
		active |= पढ़ोl(port->s_active[n]);

	वापस active != 0;
पूर्ण

/*
 * Wait क्रम port to quiesce
 *
 * @port    Poपूर्णांकer to port data काष्ठाure
 * @समयout Max duration to रुको (ms)
 *
 * वापस value
 *	0	Success
 *	-EBUSY  Commands still active
 */
अटल पूर्णांक mtip_quiesce_io(काष्ठा mtip_port *port, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ to;
	bool active = true;

	blk_mq_quiesce_queue(port->dd->queue);

	to = jअगरfies + msecs_to_jअगरfies(समयout);
	करो अणु
		अगर (test_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags) &&
			test_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags)) अणु
			msleep(20);
			जारी; /* svc thd is actively issuing commands */
		पूर्ण

		msleep(100);

		अगर (mtip_check_surprise_removal(port->dd->pdev))
			जाओ err_fault;

		active = mtip_commands_active(port);
		अगर (!active)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, to));

	blk_mq_unquiesce_queue(port->dd->queue);
	वापस active ? -EBUSY : 0;
err_fault:
	blk_mq_unquiesce_queue(port->dd->queue);
	वापस -EFAULT;
पूर्ण

काष्ठा mtip_पूर्णांक_cmd अणु
	पूर्णांक fis_len;
	dma_addr_t buffer;
	पूर्णांक buf_len;
	u32 opts;
पूर्ण;

/*
 * Execute an पूर्णांकernal command and रुको क्रम the completion.
 *
 * @port    Poपूर्णांकer to the port data काष्ठाure.
 * @fis     Poपूर्णांकer to the FIS that describes the command.
 * @fis_len  Length in WORDS of the FIS.
 * @buffer  DMA accessible क्रम command data.
 * @buf_len  Length, in bytes, of the data buffer.
 * @opts    Command header options, excluding the FIS length
 *             and the number of PRD entries.
 * @समयout Time in ms to रुको क्रम the command to complete.
 *
 * वापस value
 *	0	 Command completed successfully.
 *	-EFAULT  The buffer address is not correctly aligned.
 *	-EBUSY   Internal command or other IO in progress.
 *	-EAGAIN  Time out रुकोing क्रम command to complete.
 */
अटल पूर्णांक mtip_exec_पूर्णांकernal_command(काष्ठा mtip_port *port,
					काष्ठा host_to_dev_fis *fis,
					पूर्णांक fis_len,
					dma_addr_t buffer,
					पूर्णांक buf_len,
					u32 opts,
					अचिन्हित दीर्घ समयout)
अणु
	काष्ठा mtip_cmd *पूर्णांक_cmd;
	काष्ठा driver_data *dd = port->dd;
	काष्ठा request *rq;
	काष्ठा mtip_पूर्णांक_cmd icmd = अणु
		.fis_len = fis_len,
		.buffer = buffer,
		.buf_len = buf_len,
		.opts = opts
	पूर्ण;
	पूर्णांक rv = 0;

	/* Make sure the buffer is 8 byte aligned. This is asic specअगरic. */
	अगर (buffer & 0x00000007) अणु
		dev_err(&dd->pdev->dev, "SG buffer is not 8 byte aligned\n");
		वापस -EFAULT;
	पूर्ण

	अगर (mtip_check_surprise_removal(dd->pdev))
		वापस -EFAULT;

	rq = blk_mq_alloc_request(dd->queue, REQ_OP_DRV_IN, BLK_MQ_REQ_RESERVED);
	अगर (IS_ERR(rq)) अणु
		dbg_prपूर्णांकk(MTIP_DRV_NAME "Unable to allocate tag for PIO cmd\n");
		वापस -EFAULT;
	पूर्ण

	set_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags);

	अगर (fis->command == ATA_CMD_SEC_ERASE_PREP)
		set_bit(MTIP_PF_SE_ACTIVE_BIT, &port->flags);

	clear_bit(MTIP_PF_DM_ACTIVE_BIT, &port->flags);

	अगर (fis->command != ATA_CMD_STANDBYNOW1) अणु
		/* रुको क्रम io to complete अगर non atomic */
		अगर (mtip_quiesce_io(port, MTIP_QUIESCE_IO_TIMEOUT_MS) < 0) अणु
			dev_warn(&dd->pdev->dev, "Failed to quiesce IO\n");
			blk_mq_मुक्त_request(rq);
			clear_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags);
			wake_up_पूर्णांकerruptible(&port->svc_रुको);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Copy the command to the command table */
	पूर्णांक_cmd = blk_mq_rq_to_pdu(rq);
	पूर्णांक_cmd->icmd = &icmd;
	स_नकल(पूर्णांक_cmd->command, fis, fis_len*4);

	rq->समयout = समयout;

	/* insert request and run queue */
	blk_execute_rq(शून्य, rq, true);

	अगर (पूर्णांक_cmd->status) अणु
		dev_err(&dd->pdev->dev, "Internal command [%02X] failed %d\n",
				fis->command, पूर्णांक_cmd->status);
		rv = -EIO;

		अगर (mtip_check_surprise_removal(dd->pdev) ||
			test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
					&dd->dd_flag)) अणु
			dev_err(&dd->pdev->dev,
				"Internal command [%02X] wait returned due to SR\n",
				fis->command);
			rv = -ENXIO;
			जाओ exec_ic_निकास;
		पूर्ण
		mtip_device_reset(dd); /* recover from समयout issue */
		rv = -EAGAIN;
		जाओ exec_ic_निकास;
	पूर्ण

	अगर (पढ़ोl(port->cmd_issue[MTIP_TAG_INDEX(MTIP_TAG_INTERNAL)])
			& (1 << MTIP_TAG_BIT(MTIP_TAG_INTERNAL))) अणु
		rv = -ENXIO;
		अगर (!test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag)) अणु
			mtip_device_reset(dd);
			rv = -EAGAIN;
		पूर्ण
	पूर्ण
exec_ic_निकास:
	/* Clear the allocated and active bits क्रम the पूर्णांकernal command. */
	blk_mq_मुक्त_request(rq);
	clear_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags);
	अगर (rv >= 0 && mtip_छोड़ो_ncq(port, fis)) अणु
		/* NCQ छोड़ोd */
		वापस rv;
	पूर्ण
	wake_up_पूर्णांकerruptible(&port->svc_रुको);

	वापस rv;
पूर्ण

/*
 * Byte-swap ATA ID strings.
 *
 * ATA identअगरy data contains strings in byte-swapped 16-bit words.
 * They must be swapped (on all architectures) to be usable as C strings.
 * This function swaps bytes in-place.
 *
 * @buf The buffer location of the string
 * @len The number of bytes to swap
 *
 * वापस value
 *	None
 */
अटल अंतरभूत व्योम ata_swap_string(u16 *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < (len/2); i++)
		be16_to_cpus(&buf[i]);
पूर्ण

अटल व्योम mtip_set_समयout(काष्ठा driver_data *dd,
					काष्ठा host_to_dev_fis *fis,
					अचिन्हित पूर्णांक *समयout, u8 erasemode)
अणु
	चयन (fis->command) अणु
	हाल ATA_CMD_DOWNLOAD_MICRO:
		*समयout = 120000; /* 2 minutes */
		अवरोध;
	हाल ATA_CMD_SEC_ERASE_UNIT:
	हाल 0xFC:
		अगर (erasemode)
			*समयout = ((*(dd->port->identअगरy + 90) * 2) * 60000);
		अन्यथा
			*समयout = ((*(dd->port->identअगरy + 89) * 2) * 60000);
		अवरोध;
	हाल ATA_CMD_STANDBYNOW1:
		*समयout = 120000;  /* 2 minutes */
		अवरोध;
	हाल 0xF7:
	हाल 0xFA:
		*समयout = 60000;  /* 60 seconds */
		अवरोध;
	हाल ATA_CMD_SMART:
		*समयout = 15000;  /* 15 seconds */
		अवरोध;
	शेष:
		*समयout = MTIP_IOCTL_CMD_TIMEOUT_MS;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Request the device identity inक्रमmation.
 *
 * If a user space buffer is not specअगरied, i.e. is शून्य, the
 * identअगरy inक्रमmation is still पढ़ो from the drive and placed
 * पूर्णांकo the identअगरy data buffer (@e port->identअगरy) in the
 * port data काष्ठाure.
 * When the identअगरy buffer contains valid identअगरy inक्रमmation @e
 * port->identअगरy_valid is non-zero.
 *
 * @port	 Poपूर्णांकer to the port काष्ठाure.
 * @user_buffer  A user space buffer where the identअगरy data should be
 *                    copied.
 *
 * वापस value
 *	0	Command completed successfully.
 *	-EFAULT An error occurred जबतक coping data to the user buffer.
 *	-1	Command failed.
 */
अटल पूर्णांक mtip_get_identअगरy(काष्ठा mtip_port *port, व्योम __user *user_buffer)
अणु
	पूर्णांक rv = 0;
	काष्ठा host_to_dev_fis fis;

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &port->dd->dd_flag))
		वापस -EFAULT;

	/* Build the FIS. */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= ATA_CMD_ID_ATA;

	/* Set the identअगरy inक्रमmation as invalid. */
	port->identअगरy_valid = 0;

	/* Clear the identअगरy inक्रमmation. */
	स_रखो(port->identअगरy, 0, माप(u16) * ATA_ID_WORDS);

	/* Execute the command. */
	अगर (mtip_exec_पूर्णांकernal_command(port,
				&fis,
				5,
				port->identअगरy_dma,
				माप(u16) * ATA_ID_WORDS,
				0,
				MTIP_INT_CMD_TIMEOUT_MS)
				< 0) अणु
		rv = -1;
		जाओ out;
	पूर्ण

	/*
	 * Perक्रमm any necessary byte-swapping.  Yes, the kernel करोes in fact
	 * perक्रमm field-sensitive swapping on the string fields.
	 * See the kernel use of ata_id_string() क्रम proof of this.
	 */
#अगर_घोषित __LITTLE_ENDIAN
	ata_swap_string(port->identअगरy + 27, 40);  /* model string*/
	ata_swap_string(port->identअगरy + 23, 8);   /* firmware string*/
	ata_swap_string(port->identअगरy + 10, 20);  /* serial# string*/
#अन्यथा
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < ATA_ID_WORDS; i++)
			port->identअगरy[i] = le16_to_cpu(port->identअगरy[i]);
	पूर्ण
#पूर्ण_अगर

	/* Check security locked state */
	अगर (port->identअगरy[128] & 0x4)
		set_bit(MTIP_DDF_SEC_LOCK_BIT, &port->dd->dd_flag);
	अन्यथा
		clear_bit(MTIP_DDF_SEC_LOCK_BIT, &port->dd->dd_flag);

	/* Set the identअगरy buffer as valid. */
	port->identअगरy_valid = 1;

	अगर (user_buffer) अणु
		अगर (copy_to_user(
			user_buffer,
			port->identअगरy,
			ATA_ID_WORDS * माप(u16))) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस rv;
पूर्ण

/*
 * Issue a standby immediate command to the device.
 *
 * @port Poपूर्णांकer to the port काष्ठाure.
 *
 * वापस value
 *	0	Command was executed successfully.
 *	-1	An error occurred जबतक executing the command.
 */
अटल पूर्णांक mtip_standby_immediate(काष्ठा mtip_port *port)
अणु
	पूर्णांक rv;
	काष्ठा host_to_dev_fis	fis;
	अचिन्हित दीर्घ __maybe_unused start;
	अचिन्हित पूर्णांक समयout;

	/* Build the FIS. */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= ATA_CMD_STANDBYNOW1;

	mtip_set_समयout(port->dd, &fis, &समयout, 0);

	start = jअगरfies;
	rv = mtip_exec_पूर्णांकernal_command(port,
					&fis,
					5,
					0,
					0,
					0,
					समयout);
	dbg_prपूर्णांकk(MTIP_DRV_NAME "Time taken to complete standby cmd: %d ms\n",
			jअगरfies_to_msecs(jअगरfies - start));
	अगर (rv)
		dev_warn(&port->dd->pdev->dev,
			"STANDBY IMMEDIATE command failed.\n");

	वापस rv;
पूर्ण

/*
 * Issue a READ LOG EXT command to the device.
 *
 * @port	poपूर्णांकer to the port काष्ठाure.
 * @page	page number to fetch
 * @buffer	poपूर्णांकer to buffer
 * @buffer_dma	dma address corresponding to @buffer
 * @sectors	page length to fetch, in sectors
 *
 * वापस value
 *	@rv	वापस value from mtip_exec_पूर्णांकernal_command()
 */
अटल पूर्णांक mtip_पढ़ो_log_page(काष्ठा mtip_port *port, u8 page, u16 *buffer,
				dma_addr_t buffer_dma, अचिन्हित पूर्णांक sectors)
अणु
	काष्ठा host_to_dev_fis fis;

	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= ATA_CMD_READ_LOG_EXT;
	fis.sect_count	= sectors & 0xFF;
	fis.sect_cnt_ex	= (sectors >> 8) & 0xFF;
	fis.lba_low	= page;
	fis.lba_mid	= 0;
	fis.device	= ATA_DEVICE_OBS;

	स_रखो(buffer, 0, sectors * ATA_SECT_SIZE);

	वापस mtip_exec_पूर्णांकernal_command(port,
					&fis,
					5,
					buffer_dma,
					sectors * ATA_SECT_SIZE,
					0,
					MTIP_INT_CMD_TIMEOUT_MS);
पूर्ण

/*
 * Issue a SMART READ DATA command to the device.
 *
 * @port	poपूर्णांकer to the port काष्ठाure.
 * @buffer	poपूर्णांकer to buffer
 * @buffer_dma	dma address corresponding to @buffer
 *
 * वापस value
 *	@rv	वापस value from mtip_exec_पूर्णांकernal_command()
 */
अटल पूर्णांक mtip_get_smart_data(काष्ठा mtip_port *port, u8 *buffer,
					dma_addr_t buffer_dma)
अणु
	काष्ठा host_to_dev_fis fis;

	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= ATA_CMD_SMART;
	fis.features	= 0xD0;
	fis.sect_count	= 1;
	fis.lba_mid	= 0x4F;
	fis.lba_hi	= 0xC2;
	fis.device	= ATA_DEVICE_OBS;

	वापस mtip_exec_पूर्णांकernal_command(port,
					&fis,
					5,
					buffer_dma,
					ATA_SECT_SIZE,
					0,
					15000);
पूर्ण

/*
 * Get the value of a smart attribute
 *
 * @port	poपूर्णांकer to the port काष्ठाure
 * @id		attribute number
 * @attrib	poपूर्णांकer to वापस attrib inक्रमmation corresponding to @id
 *
 * वापस value
 *	-EINVAL	शून्य buffer passed or unsupported attribute @id.
 *	-EPERM	Identअगरy data not valid, SMART not supported or not enabled
 */
अटल पूर्णांक mtip_get_smart_attr(काष्ठा mtip_port *port, अचिन्हित पूर्णांक id,
						काष्ठा smart_attr *attrib)
अणु
	पूर्णांक rv, i;
	काष्ठा smart_attr *pattr;

	अगर (!attrib)
		वापस -EINVAL;

	अगर (!port->identअगरy_valid) अणु
		dev_warn(&port->dd->pdev->dev, "IDENTIFY DATA not valid\n");
		वापस -EPERM;
	पूर्ण
	अगर (!(port->identअगरy[82] & 0x1)) अणु
		dev_warn(&port->dd->pdev->dev, "SMART not supported\n");
		वापस -EPERM;
	पूर्ण
	अगर (!(port->identअगरy[85] & 0x1)) अणु
		dev_warn(&port->dd->pdev->dev, "SMART not enabled\n");
		वापस -EPERM;
	पूर्ण

	स_रखो(port->smart_buf, 0, ATA_SECT_SIZE);
	rv = mtip_get_smart_data(port, port->smart_buf, port->smart_buf_dma);
	अगर (rv) अणु
		dev_warn(&port->dd->pdev->dev, "Failed to ge SMART data\n");
		वापस rv;
	पूर्ण

	pattr = (काष्ठा smart_attr *)(port->smart_buf + 2);
	क्रम (i = 0; i < 29; i++, pattr++)
		अगर (pattr->attr_id == id) अणु
			स_नकल(attrib, pattr, माप(काष्ठा smart_attr));
			अवरोध;
		पूर्ण

	अगर (i == 29) अणु
		dev_warn(&port->dd->pdev->dev,
			"Query for invalid SMART attribute ID\n");
		rv = -EINVAL;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * Get the drive capacity.
 *
 * @dd      Poपूर्णांकer to the device data काष्ठाure.
 * @sectors Poपूर्णांकer to the variable that will receive the sector count.
 *
 * वापस value
 *	1 Capacity was वापसed successfully.
 *	0 The identअगरy inक्रमmation is invalid.
 */
अटल bool mtip_hw_get_capacity(काष्ठा driver_data *dd, sector_t *sectors)
अणु
	काष्ठा mtip_port *port = dd->port;
	u64 total, raw0, raw1, raw2, raw3;
	raw0 = port->identअगरy[100];
	raw1 = port->identअगरy[101];
	raw2 = port->identअगरy[102];
	raw3 = port->identअगरy[103];
	total = raw0 | raw1<<16 | raw2<<32 | raw3<<48;
	*sectors = total;
	वापस (bool) !!port->identअगरy_valid;
पूर्ण

/*
 * Display the identअगरy command data.
 *
 * @port Poपूर्णांकer to the port data काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_dump_identअगरy(काष्ठा mtip_port *port)
अणु
	sector_t sectors;
	अचिन्हित लघु revid;
	अक्षर cbuf[42];

	अगर (!port->identअगरy_valid)
		वापस;

	strlcpy(cbuf, (अक्षर *)(port->identअगरy+10), 21);
	dev_info(&port->dd->pdev->dev,
		"Serial No.: %s\n", cbuf);

	strlcpy(cbuf, (अक्षर *)(port->identअगरy+23), 9);
	dev_info(&port->dd->pdev->dev,
		"Firmware Ver.: %s\n", cbuf);

	strlcpy(cbuf, (अक्षर *)(port->identअगरy+27), 41);
	dev_info(&port->dd->pdev->dev, "Model: %s\n", cbuf);

	dev_info(&port->dd->pdev->dev, "Security: %04x %s\n",
		port->identअगरy[128],
		port->identअगरy[128] & 0x4 ? "(LOCKED)" : "");

	अगर (mtip_hw_get_capacity(port->dd, &sectors))
		dev_info(&port->dd->pdev->dev,
			"Capacity: %llu sectors (%llu MB)\n",
			 (u64)sectors,
			 ((u64)sectors) * ATA_SECT_SIZE >> 20);

	pci_पढ़ो_config_word(port->dd->pdev, PCI_REVISION_ID, &revid);
	चयन (revid & 0xFF) अणु
	हाल 0x1:
		strlcpy(cbuf, "A0", 3);
		अवरोध;
	हाल 0x3:
		strlcpy(cbuf, "A2", 3);
		अवरोध;
	शेष:
		strlcpy(cbuf, "?", 2);
		अवरोध;
	पूर्ण
	dev_info(&port->dd->pdev->dev,
		"Card Type: %s\n", cbuf);
पूर्ण

/*
 * Map the commands scatter list पूर्णांकo the command table.
 *
 * @command Poपूर्णांकer to the command.
 * @nents Number of scatter list entries.
 *
 * वापस value
 *	None
 */
अटल अंतरभूत व्योम fill_command_sg(काष्ठा driver_data *dd,
				काष्ठा mtip_cmd *command,
				पूर्णांक nents)
अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक dma_len;
	काष्ठा mtip_cmd_sg *command_sg;
	काष्ठा scatterlist *sg;

	command_sg = command->command + AHCI_CMD_TBL_HDR_SZ;

	क्रम_each_sg(command->sg, sg, nents, n) अणु
		dma_len = sg_dma_len(sg);
		अगर (dma_len > 0x400000)
			dev_err(&dd->pdev->dev,
				"DMA segment length truncated\n");
		command_sg->info = cpu_to_le32((dma_len-1) & 0x3FFFFF);
		command_sg->dba	=  cpu_to_le32(sg_dma_address(sg));
		command_sg->dba_upper =
			cpu_to_le32((sg_dma_address(sg) >> 16) >> 16);
		command_sg++;
	पूर्ण
पूर्ण

/*
 * @brief Execute a drive command.
 *
 * वापस value 0 The command completed successfully.
 * वापस value -1 An error occurred जबतक executing the command.
 */
अटल पूर्णांक exec_drive_task(काष्ठा mtip_port *port, u8 *command)
अणु
	काष्ठा host_to_dev_fis	fis;
	काष्ठा host_to_dev_fis *reply = (port->rxfis + RX_FIS_D2H_REG);
	अचिन्हित पूर्णांक to;

	/* Build the FIS. */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= command[0];
	fis.features	= command[1];
	fis.sect_count	= command[2];
	fis.sector	= command[3];
	fis.cyl_low	= command[4];
	fis.cyl_hi	= command[5];
	fis.device	= command[6] & ~0x10; /* Clear the dev bit*/

	mtip_set_समयout(port->dd, &fis, &to, 0);

	dbg_prपूर्णांकk(MTIP_DRV_NAME " %s: User Command: cmd %x, feat %x, nsect %x, sect %x, lcyl %x, hcyl %x, sel %x\n",
		__func__,
		command[0],
		command[1],
		command[2],
		command[3],
		command[4],
		command[5],
		command[6]);

	/* Execute the command. */
	अगर (mtip_exec_पूर्णांकernal_command(port,
				 &fis,
				 5,
				 0,
				 0,
				 0,
				 to) < 0) अणु
		वापस -1;
	पूर्ण

	command[0] = reply->command; /* Status*/
	command[1] = reply->features; /* Error*/
	command[4] = reply->cyl_low;
	command[5] = reply->cyl_hi;

	dbg_prपूर्णांकk(MTIP_DRV_NAME " %s: Completion Status: stat %x, err %x , cyl_lo %x cyl_hi %x\n",
		__func__,
		command[0],
		command[1],
		command[4],
		command[5]);

	वापस 0;
पूर्ण

/*
 * @brief Execute a drive command.
 *
 * @param port Poपूर्णांकer to the port data काष्ठाure.
 * @param command Poपूर्णांकer to the user specअगरied command parameters.
 * @param user_buffer Poपूर्णांकer to the user space buffer where पढ़ो sector
 *                   data should be copied.
 *
 * वापस value 0 The command completed successfully.
 * वापस value -EFAULT An error occurred जबतक copying the completion
 *                 data to the user space buffer.
 * वापस value -1 An error occurred जबतक executing the command.
 */
अटल पूर्णांक exec_drive_command(काष्ठा mtip_port *port, u8 *command,
				व्योम __user *user_buffer)
अणु
	काष्ठा host_to_dev_fis	fis;
	काष्ठा host_to_dev_fis *reply;
	u8 *buf = शून्य;
	dma_addr_t dma_addr = 0;
	पूर्णांक rv = 0, xfer_sz = command[3];
	अचिन्हित पूर्णांक to;

	अगर (xfer_sz) अणु
		अगर (!user_buffer)
			वापस -EFAULT;

		buf = dma_alloc_coherent(&port->dd->pdev->dev,
				ATA_SECT_SIZE * xfer_sz,
				&dma_addr,
				GFP_KERNEL);
		अगर (!buf) अणु
			dev_err(&port->dd->pdev->dev,
				"Memory allocation failed (%d bytes)\n",
				ATA_SECT_SIZE * xfer_sz);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Build the FIS. */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= command[0];
	fis.features	= command[2];
	fis.sect_count	= command[3];
	अगर (fis.command == ATA_CMD_SMART) अणु
		fis.sector	= command[1];
		fis.cyl_low	= 0x4F;
		fis.cyl_hi	= 0xC2;
	पूर्ण

	mtip_set_समयout(port->dd, &fis, &to, 0);

	अगर (xfer_sz)
		reply = (port->rxfis + RX_FIS_PIO_SETUP);
	अन्यथा
		reply = (port->rxfis + RX_FIS_D2H_REG);

	dbg_prपूर्णांकk(MTIP_DRV_NAME
		" %s: User Command: cmd %x, sect %x, "
		"feat %x, sectcnt %x\n",
		__func__,
		command[0],
		command[1],
		command[2],
		command[3]);

	/* Execute the command. */
	अगर (mtip_exec_पूर्णांकernal_command(port,
				&fis,
				 5,
				 (xfer_sz ? dma_addr : 0),
				 (xfer_sz ? ATA_SECT_SIZE * xfer_sz : 0),
				 0,
				 to)
				 < 0) अणु
		rv = -EFAULT;
		जाओ निकास_drive_command;
	पूर्ण

	/* Collect the completion status. */
	command[0] = reply->command; /* Status*/
	command[1] = reply->features; /* Error*/
	command[2] = reply->sect_count;

	dbg_prपूर्णांकk(MTIP_DRV_NAME
		" %s: Completion Status: stat %x, "
		"err %x, nsect %x\n",
		__func__,
		command[0],
		command[1],
		command[2]);

	अगर (xfer_sz) अणु
		अगर (copy_to_user(user_buffer,
				 buf,
				 ATA_SECT_SIZE * command[3])) अणु
			rv = -EFAULT;
			जाओ निकास_drive_command;
		पूर्ण
	पूर्ण
निकास_drive_command:
	अगर (buf)
		dma_मुक्त_coherent(&port->dd->pdev->dev,
				ATA_SECT_SIZE * xfer_sz, buf, dma_addr);
	वापस rv;
पूर्ण

/*
 *  Indicates whether a command has a single sector payload.
 *
 *  @command passed to the device to perक्रमm the certain event.
 *  @features passed to the device to perक्रमm the certain event.
 *
 *  वापस value
 *	1	command is one that always has a single sector payload,
 *		regardless of the value in the Sector Count field.
 *      0       otherwise
 *
 */
अटल अचिन्हित पूर्णांक implicit_sector(अचिन्हित अक्षर command,
				    अचिन्हित अक्षर features)
अणु
	अचिन्हित पूर्णांक rv = 0;

	/* list of commands that have an implicit sector count of 1 */
	चयन (command) अणु
	हाल ATA_CMD_SEC_SET_PASS:
	हाल ATA_CMD_SEC_UNLOCK:
	हाल ATA_CMD_SEC_ERASE_PREP:
	हाल ATA_CMD_SEC_ERASE_UNIT:
	हाल ATA_CMD_SEC_FREEZE_LOCK:
	हाल ATA_CMD_SEC_DISABLE_PASS:
	हाल ATA_CMD_PMP_READ:
	हाल ATA_CMD_PMP_WRITE:
		rv = 1;
		अवरोध;
	हाल ATA_CMD_SET_MAX:
		अगर (features == ATA_SET_MAX_UNLOCK)
			rv = 1;
		अवरोध;
	हाल ATA_CMD_SMART:
		अगर ((features == ATA_SMART_READ_VALUES) ||
				(features == ATA_SMART_READ_THRESHOLDS))
			rv = 1;
		अवरोध;
	हाल ATA_CMD_CONF_OVERLAY:
		अगर ((features == ATA_DCO_IDENTIFY) ||
				(features == ATA_DCO_SET))
			rv = 1;
		अवरोध;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Executes a taskfile
 * See ide_taskfile_ioctl() क्रम derivation
 */
अटल पूर्णांक exec_drive_taskfile(काष्ठा driver_data *dd,
			       व्योम __user *buf,
			       ide_task_request_t *req_task,
			       पूर्णांक outtotal)
अणु
	काष्ठा host_to_dev_fis	fis;
	काष्ठा host_to_dev_fis *reply;
	u8 *outbuf = शून्य;
	u8 *inbuf = शून्य;
	dma_addr_t outbuf_dma = 0;
	dma_addr_t inbuf_dma = 0;
	dma_addr_t dma_buffer = 0;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक taskin = 0;
	अचिन्हित पूर्णांक taskout = 0;
	u8 nsect = 0;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक क्रमce_single_sector;
	अचिन्हित पूर्णांक transfer_size;
	अचिन्हित दीर्घ task_file_data;
	पूर्णांक पूर्णांकotal = outtotal + req_task->out_size;
	पूर्णांक erasemode = 0;

	taskout = req_task->out_size;
	taskin = req_task->in_size;
	/* 130560 = 512 * 0xFF*/
	अगर (taskin > 130560 || taskout > 130560)
		वापस -EINVAL;

	अगर (taskout) अणु
		outbuf = memdup_user(buf + outtotal, taskout);
		अगर (IS_ERR(outbuf))
			वापस PTR_ERR(outbuf);

		outbuf_dma = dma_map_single(&dd->pdev->dev, outbuf,
					    taskout, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&dd->pdev->dev, outbuf_dma)) अणु
			err = -ENOMEM;
			जाओ पात;
		पूर्ण
		dma_buffer = outbuf_dma;
	पूर्ण

	अगर (taskin) अणु
		inbuf = memdup_user(buf + पूर्णांकotal, taskin);
		अगर (IS_ERR(inbuf)) अणु
			err = PTR_ERR(inbuf);
			inbuf = शून्य;
			जाओ पात;
		पूर्ण
		inbuf_dma = dma_map_single(&dd->pdev->dev, inbuf,
					   taskin, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&dd->pdev->dev, inbuf_dma)) अणु
			err = -ENOMEM;
			जाओ पात;
		पूर्ण
		dma_buffer = inbuf_dma;
	पूर्ण

	/* only supports PIO and non-data commands from this ioctl. */
	चयन (req_task->data_phase) अणु
	हाल TASKखाता_OUT:
		nsect = taskout / ATA_SECT_SIZE;
		reply = (dd->port->rxfis + RX_FIS_PIO_SETUP);
		अवरोध;
	हाल TASKखाता_IN:
		reply = (dd->port->rxfis + RX_FIS_PIO_SETUP);
		अवरोध;
	हाल TASKखाता_NO_DATA:
		reply = (dd->port->rxfis + RX_FIS_D2H_REG);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ पात;
	पूर्ण

	/* Build the FIS. */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));

	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= req_task->io_ports[7];
	fis.features	= req_task->io_ports[1];
	fis.sect_count	= req_task->io_ports[2];
	fis.lba_low	= req_task->io_ports[3];
	fis.lba_mid	= req_task->io_ports[4];
	fis.lba_hi	= req_task->io_ports[5];
	 /* Clear the dev bit*/
	fis.device	= req_task->io_ports[6] & ~0x10;

	अगर ((req_task->in_flags.all == 0) && (req_task->out_flags.all & 1)) अणु
		req_task->in_flags.all	=
			IDE_TASKखाता_STD_IN_FLAGS |
			(IDE_HOB_STD_IN_FLAGS << 8);
		fis.lba_low_ex		= req_task->hob_ports[3];
		fis.lba_mid_ex		= req_task->hob_ports[4];
		fis.lba_hi_ex		= req_task->hob_ports[5];
		fis.features_ex		= req_task->hob_ports[1];
		fis.sect_cnt_ex		= req_task->hob_ports[2];

	पूर्ण अन्यथा अणु
		req_task->in_flags.all = IDE_TASKखाता_STD_IN_FLAGS;
	पूर्ण

	क्रमce_single_sector = implicit_sector(fis.command, fis.features);

	अगर ((taskin || taskout) && (!fis.sect_count)) अणु
		अगर (nsect)
			fis.sect_count = nsect;
		अन्यथा अणु
			अगर (!क्रमce_single_sector) अणु
				dev_warn(&dd->pdev->dev,
					"data movement but "
					"sect_count is 0\n");
				err = -EINVAL;
				जाओ पात;
			पूर्ण
		पूर्ण
	पूर्ण

	dbg_prपूर्णांकk(MTIP_DRV_NAME
		" %s: cmd %x, feat %x, nsect %x,"
		" sect/lbal %x, lcyl/lbam %x, hcyl/lbah %x,"
		" head/dev %x\n",
		__func__,
		fis.command,
		fis.features,
		fis.sect_count,
		fis.lba_low,
		fis.lba_mid,
		fis.lba_hi,
		fis.device);

	/* check क्रम erase mode support during secure erase.*/
	अगर ((fis.command == ATA_CMD_SEC_ERASE_UNIT) && outbuf &&
					(outbuf[0] & MTIP_SEC_ERASE_MODE)) अणु
		erasemode = 1;
	पूर्ण

	mtip_set_समयout(dd, &fis, &समयout, erasemode);

	/* Determine the correct transfer size.*/
	अगर (क्रमce_single_sector)
		transfer_size = ATA_SECT_SIZE;
	अन्यथा
		transfer_size = ATA_SECT_SIZE * fis.sect_count;

	/* Execute the command.*/
	अगर (mtip_exec_पूर्णांकernal_command(dd->port,
				 &fis,
				 5,
				 dma_buffer,
				 transfer_size,
				 0,
				 समयout) < 0) अणु
		err = -EIO;
		जाओ पात;
	पूर्ण

	task_file_data = पढ़ोl(dd->port->mmio+PORT_TFDATA);

	अगर ((req_task->data_phase == TASKखाता_IN) && !(task_file_data & 1)) अणु
		reply = dd->port->rxfis + RX_FIS_PIO_SETUP;
		req_task->io_ports[7] = reply->control;
	पूर्ण अन्यथा अणु
		reply = dd->port->rxfis + RX_FIS_D2H_REG;
		req_task->io_ports[7] = reply->command;
	पूर्ण

	/* reclaim the DMA buffers.*/
	अगर (inbuf_dma)
		dma_unmap_single(&dd->pdev->dev, inbuf_dma, taskin,
				 DMA_FROM_DEVICE);
	अगर (outbuf_dma)
		dma_unmap_single(&dd->pdev->dev, outbuf_dma, taskout,
				 DMA_TO_DEVICE);
	inbuf_dma  = 0;
	outbuf_dma = 0;

	/* वापस the ATA रेजिस्टरs to the caller.*/
	req_task->io_ports[1] = reply->features;
	req_task->io_ports[2] = reply->sect_count;
	req_task->io_ports[3] = reply->lba_low;
	req_task->io_ports[4] = reply->lba_mid;
	req_task->io_ports[5] = reply->lba_hi;
	req_task->io_ports[6] = reply->device;

	अगर (req_task->out_flags.all & 1)  अणु

		req_task->hob_ports[3] = reply->lba_low_ex;
		req_task->hob_ports[4] = reply->lba_mid_ex;
		req_task->hob_ports[5] = reply->lba_hi_ex;
		req_task->hob_ports[1] = reply->features_ex;
		req_task->hob_ports[2] = reply->sect_cnt_ex;
	पूर्ण
	dbg_prपूर्णांकk(MTIP_DRV_NAME
		" %s: Completion: stat %x,"
		"err %x, sect_cnt %x, lbalo %x,"
		"lbamid %x, lbahi %x, dev %x\n",
		__func__,
		req_task->io_ports[7],
		req_task->io_ports[1],
		req_task->io_ports[2],
		req_task->io_ports[3],
		req_task->io_ports[4],
		req_task->io_ports[5],
		req_task->io_ports[6]);

	अगर (taskout) अणु
		अगर (copy_to_user(buf + outtotal, outbuf, taskout)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण
	अगर (taskin) अणु
		अगर (copy_to_user(buf + पूर्णांकotal, inbuf, taskin)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण
पात:
	अगर (inbuf_dma)
		dma_unmap_single(&dd->pdev->dev, inbuf_dma, taskin,
				 DMA_FROM_DEVICE);
	अगर (outbuf_dma)
		dma_unmap_single(&dd->pdev->dev, outbuf_dma, taskout,
				 DMA_TO_DEVICE);
	kमुक्त(outbuf);
	kमुक्त(inbuf);

	वापस err;
पूर्ण

/*
 * Handle IOCTL calls from the Block Layer.
 *
 * This function is called by the Block Layer when it receives an IOCTL
 * command that it करोes not understand. If the IOCTL command is not supported
 * this function वापसs -ENOTTY.
 *
 * @dd  Poपूर्णांकer to the driver data काष्ठाure.
 * @cmd IOCTL command passed from the Block Layer.
 * @arg IOCTL argument passed from the Block Layer.
 *
 * वापस value
 *	0	The IOCTL completed successfully.
 *	-ENOTTY The specअगरied command is not supported.
 *	-EFAULT An error occurred copying data to a user space buffer.
 *	-EIO	An error occurred जबतक executing the command.
 */
अटल पूर्णांक mtip_hw_ioctl(काष्ठा driver_data *dd, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल HDIO_GET_IDENTITY:
	अणु
		अगर (copy_to_user((व्योम __user *)arg, dd->port->identअगरy,
						माप(u16) * ATA_ID_WORDS))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल HDIO_DRIVE_CMD:
	अणु
		u8 drive_command[4];

		/* Copy the user command info to our buffer. */
		अगर (copy_from_user(drive_command,
					 (व्योम __user *) arg,
					 माप(drive_command)))
			वापस -EFAULT;

		/* Execute the drive command. */
		अगर (exec_drive_command(dd->port,
					 drive_command,
					 (व्योम __user *) (arg+4)))
			वापस -EIO;

		/* Copy the status back to the users buffer. */
		अगर (copy_to_user((व्योम __user *) arg,
					 drive_command,
					 माप(drive_command)))
			वापस -EFAULT;

		अवरोध;
	पूर्ण
	हाल HDIO_DRIVE_TASK:
	अणु
		u8 drive_command[7];

		/* Copy the user command info to our buffer. */
		अगर (copy_from_user(drive_command,
					 (व्योम __user *) arg,
					 माप(drive_command)))
			वापस -EFAULT;

		/* Execute the drive command. */
		अगर (exec_drive_task(dd->port, drive_command))
			वापस -EIO;

		/* Copy the status back to the users buffer. */
		अगर (copy_to_user((व्योम __user *) arg,
					 drive_command,
					 माप(drive_command)))
			वापस -EFAULT;

		अवरोध;
	पूर्ण
	हाल HDIO_DRIVE_TASKखाता: अणु
		ide_task_request_t req_task;
		पूर्णांक ret, outtotal;

		अगर (copy_from_user(&req_task, (व्योम __user *) arg,
					माप(req_task)))
			वापस -EFAULT;

		outtotal = माप(req_task);

		ret = exec_drive_taskfile(dd, (व्योम __user *) arg,
						&req_task, outtotal);

		अगर (copy_to_user((व्योम __user *) arg, &req_task,
							माप(req_task)))
			वापस -EFAULT;

		वापस ret;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Submit an IO to the hw
 *
 * This function is called by the block layer to issue an io
 * to the device. Upon completion, the callback function will
 * be called with the data parameter passed as the callback data.
 *
 * @dd       Poपूर्णांकer to the driver data काष्ठाure.
 * @start    First sector to पढ़ो.
 * @nsect    Number of sectors to पढ़ो.
 * @tag      The tag of this पढ़ो command.
 * @callback Poपूर्णांकer to the function that should be called
 *	     when the पढ़ो completes.
 * @data     Callback data passed to the callback function
 *	     when the पढ़ो completes.
 * @dir      Direction (पढ़ो or ग_लिखो)
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_hw_submit_io(काष्ठा driver_data *dd, काष्ठा request *rq,
			      काष्ठा mtip_cmd *command,
			      काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा mtip_cmd_hdr *hdr =
		dd->port->command_list + माप(काष्ठा mtip_cmd_hdr) * rq->tag;
	काष्ठा host_to_dev_fis	*fis;
	काष्ठा mtip_port *port = dd->port;
	पूर्णांक dma_dir = rq_data_dir(rq) == READ ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	u64 start = blk_rq_pos(rq);
	अचिन्हित पूर्णांक nsect = blk_rq_sectors(rq);
	अचिन्हित पूर्णांक nents;

	/* Map the scatter list क्रम DMA access */
	nents = blk_rq_map_sg(hctx->queue, rq, command->sg);
	nents = dma_map_sg(&dd->pdev->dev, command->sg, nents, dma_dir);

	prefetch(&port->flags);

	command->scatter_ents = nents;

	/*
	 * The number of retries क्रम this command beक्रमe it is
	 * reported as a failure to the upper layers.
	 */
	command->retries = MTIP_MAX_RETRIES;

	/* Fill out fis */
	fis = command->command;
	fis->type        = 0x27;
	fis->opts        = 1 << 7;
	अगर (dma_dir == DMA_FROM_DEVICE)
		fis->command = ATA_CMD_FPDMA_READ;
	अन्यथा
		fis->command = ATA_CMD_FPDMA_WRITE;
	fis->lba_low     = start & 0xFF;
	fis->lba_mid     = (start >> 8) & 0xFF;
	fis->lba_hi      = (start >> 16) & 0xFF;
	fis->lba_low_ex  = (start >> 24) & 0xFF;
	fis->lba_mid_ex  = (start >> 32) & 0xFF;
	fis->lba_hi_ex   = (start >> 40) & 0xFF;
	fis->device	 = 1 << 6;
	fis->features    = nsect & 0xFF;
	fis->features_ex = (nsect >> 8) & 0xFF;
	fis->sect_count  = ((rq->tag << 3) | (rq->tag >> 5));
	fis->sect_cnt_ex = 0;
	fis->control     = 0;
	fis->res2        = 0;
	fis->res3        = 0;
	fill_command_sg(dd, command, nents);

	अगर (unlikely(command->unaligned))
		fis->device |= 1 << 7;

	/* Populate the command header */
	hdr->ctba = cpu_to_le32(command->command_dma & 0xFFFFFFFF);
	अगर (test_bit(MTIP_PF_HOST_CAP_64, &dd->port->flags))
		hdr->ctbau = cpu_to_le32((command->command_dma >> 16) >> 16);
	hdr->opts = cpu_to_le32((nents << 16) | 5 | AHCI_CMD_PREFETCH);
	hdr->byte_count = 0;

	command->direction = dma_dir;

	/*
	 * To prevent this command from being issued
	 * अगर an पूर्णांकernal command is in progress or error handling is active.
	 */
	अगर (unlikely(port->flags & MTIP_PF_PAUSE_IO)) अणु
		set_bit(rq->tag, port->cmds_to_issue);
		set_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags);
		वापस;
	पूर्ण

	/* Issue the command to the hardware */
	mtip_issue_ncq_command(port, rq->tag);
पूर्ण

/*
 * Sysfs status dump.
 *
 * @dev  Poपूर्णांकer to the device काष्ठाure, passed by the kernrel.
 * @attr Poपूर्णांकer to the device_attribute काष्ठाure passed by the kernel.
 * @buf  Poपूर्णांकer to the अक्षर buffer that will receive the stats info.
 *
 * वापस value
 *	The size, in bytes, of the data copied पूर्णांकo buf.
 */
अटल sमाप_प्रकार mtip_hw_show_status(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा driver_data *dd = dev_to_disk(dev)->निजी_data;
	पूर्णांक size = 0;

	अगर (test_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag))
		size += प्र_लिखो(buf, "%s", "thermal_shutdown\n");
	अन्यथा अगर (test_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag))
		size += प्र_लिखो(buf, "%s", "write_protect\n");
	अन्यथा
		size += प्र_लिखो(buf, "%s", "online\n");

	वापस size;
पूर्ण

अटल DEVICE_ATTR(status, 0444, mtip_hw_show_status, शून्य);

/* debugsfs entries */

अटल sमाप_प्रकार show_device_status(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	पूर्णांक size = 0;
	काष्ठा driver_data *dd, *पंचांगp;
	अचिन्हित दीर्घ flags;
	अक्षर id_buf[42];
	u16 status = 0;

	spin_lock_irqsave(&dev_lock, flags);
	size += प्र_लिखो(&buf[size], "Devices Present:\n");
	list_क्रम_each_entry_safe(dd, पंचांगp, &online_list, online_list) अणु
		अगर (dd->pdev) अणु
			अगर (dd->port &&
			    dd->port->identअगरy &&
			    dd->port->identअगरy_valid) अणु
				strlcpy(id_buf,
					(अक्षर *) (dd->port->identअगरy + 10), 21);
				status = *(dd->port->identअगरy + 141);
			पूर्ण अन्यथा अणु
				स_रखो(id_buf, 0, 42);
				status = 0;
			पूर्ण

			अगर (dd->port &&
			    test_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags)) अणु
				size += प्र_लिखो(&buf[size],
					" device %s %s (ftl rebuild %d %%)\n",
					dev_name(&dd->pdev->dev),
					id_buf,
					status);
			पूर्ण अन्यथा अणु
				size += प्र_लिखो(&buf[size],
					" device %s %s\n",
					dev_name(&dd->pdev->dev),
					id_buf);
			पूर्ण
		पूर्ण
	पूर्ण

	size += प्र_लिखो(&buf[size], "Devices Being Removed:\n");
	list_क्रम_each_entry_safe(dd, पंचांगp, &removing_list, हटाओ_list) अणु
		अगर (dd->pdev) अणु
			अगर (dd->port &&
			    dd->port->identअगरy &&
			    dd->port->identअगरy_valid) अणु
				strlcpy(id_buf,
					(अक्षर *) (dd->port->identअगरy+10), 21);
				status = *(dd->port->identअगरy + 141);
			पूर्ण अन्यथा अणु
				स_रखो(id_buf, 0, 42);
				status = 0;
			पूर्ण

			अगर (dd->port &&
			    test_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags)) अणु
				size += प्र_लिखो(&buf[size],
					" device %s %s (ftl rebuild %d %%)\n",
					dev_name(&dd->pdev->dev),
					id_buf,
					status);
			पूर्ण अन्यथा अणु
				size += प्र_लिखो(&buf[size],
					" device %s %s\n",
					dev_name(&dd->pdev->dev),
					id_buf);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev_lock, flags);

	वापस size;
पूर्ण

अटल sमाप_प्रकार mtip_hw_पढ़ो_device_status(काष्ठा file *f, अक्षर __user *ubuf,
						माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा driver_data *dd =  (काष्ठा driver_data *)f->निजी_data;
	पूर्णांक size = *offset;
	अक्षर *buf;
	पूर्णांक rv = 0;

	अगर (!len || *offset)
		वापस 0;

	buf = kzalloc(MTIP_DFS_MAX_BUF_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		dev_err(&dd->pdev->dev,
			"Memory allocation: status buffer\n");
		वापस -ENOMEM;
	पूर्ण

	size += show_device_status(शून्य, buf);

	*offset = size <= len ? size : len;
	size = copy_to_user(ubuf, buf, *offset);
	अगर (size)
		rv = -EFAULT;

	kमुक्त(buf);
	वापस rv ? rv : *offset;
पूर्ण

अटल sमाप_प्रकार mtip_hw_पढ़ो_रेजिस्टरs(काष्ठा file *f, अक्षर __user *ubuf,
				  माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा driver_data *dd =  (काष्ठा driver_data *)f->निजी_data;
	अक्षर *buf;
	u32 group_allocated;
	पूर्णांक size = *offset;
	पूर्णांक n, rv = 0;

	अगर (!len || size)
		वापस 0;

	buf = kzalloc(MTIP_DFS_MAX_BUF_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		dev_err(&dd->pdev->dev,
			"Memory allocation: register buffer\n");
		वापस -ENOMEM;
	पूर्ण

	size += प्र_लिखो(&buf[size], "H/ S ACTive      : [ 0x");

	क्रम (n = dd->slot_groups-1; n >= 0; n--)
		size += प्र_लिखो(&buf[size], "%08X ",
					 पढ़ोl(dd->port->s_active[n]));

	size += प्र_लिखो(&buf[size], "]\n");
	size += प्र_लिखो(&buf[size], "H/ Command Issue : [ 0x");

	क्रम (n = dd->slot_groups-1; n >= 0; n--)
		size += प्र_लिखो(&buf[size], "%08X ",
					पढ़ोl(dd->port->cmd_issue[n]));

	size += प्र_लिखो(&buf[size], "]\n");
	size += प्र_लिखो(&buf[size], "H/ Completed     : [ 0x");

	क्रम (n = dd->slot_groups-1; n >= 0; n--)
		size += प्र_लिखो(&buf[size], "%08X ",
				पढ़ोl(dd->port->completed[n]));

	size += प्र_लिखो(&buf[size], "]\n");
	size += प्र_लिखो(&buf[size], "H/ PORT IRQ STAT : [ 0x%08X ]\n",
				पढ़ोl(dd->port->mmio + PORT_IRQ_STAT));
	size += प्र_लिखो(&buf[size], "H/ HOST IRQ STAT : [ 0x%08X ]\n",
				पढ़ोl(dd->mmio + HOST_IRQ_STAT));
	size += प्र_लिखो(&buf[size], "\n");

	size += प्र_लिखो(&buf[size], "L/ Commands in Q : [ 0x");

	क्रम (n = dd->slot_groups-1; n >= 0; n--) अणु
		अगर (माप(दीर्घ) > माप(u32))
			group_allocated =
				dd->port->cmds_to_issue[n/2] >> (32*(n&1));
		अन्यथा
			group_allocated = dd->port->cmds_to_issue[n];
		size += प्र_लिखो(&buf[size], "%08X ", group_allocated);
	पूर्ण
	size += प्र_लिखो(&buf[size], "]\n");

	*offset = size <= len ? size : len;
	size = copy_to_user(ubuf, buf, *offset);
	अगर (size)
		rv = -EFAULT;

	kमुक्त(buf);
	वापस rv ? rv : *offset;
पूर्ण

अटल sमाप_प्रकार mtip_hw_पढ़ो_flags(काष्ठा file *f, अक्षर __user *ubuf,
				  माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा driver_data *dd =  (काष्ठा driver_data *)f->निजी_data;
	अक्षर *buf;
	पूर्णांक size = *offset;
	पूर्णांक rv = 0;

	अगर (!len || size)
		वापस 0;

	buf = kzalloc(MTIP_DFS_MAX_BUF_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		dev_err(&dd->pdev->dev,
			"Memory allocation: flag buffer\n");
		वापस -ENOMEM;
	पूर्ण

	size += प्र_लिखो(&buf[size], "Flag-port : [ %08lX ]\n",
							dd->port->flags);
	size += प्र_लिखो(&buf[size], "Flag-dd   : [ %08lX ]\n",
							dd->dd_flag);

	*offset = size <= len ? size : len;
	size = copy_to_user(ubuf, buf, *offset);
	अगर (size)
		rv = -EFAULT;

	kमुक्त(buf);
	वापस rv ? rv : *offset;
पूर्ण

अटल स्थिर काष्ठा file_operations mtip_device_status_fops = अणु
	.owner  = THIS_MODULE,
	.खोलो   = simple_खोलो,
	.पढ़ो   = mtip_hw_पढ़ो_device_status,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations mtip_regs_fops = अणु
	.owner  = THIS_MODULE,
	.खोलो   = simple_खोलो,
	.पढ़ो   = mtip_hw_पढ़ो_रेजिस्टरs,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations mtip_flags_fops = अणु
	.owner  = THIS_MODULE,
	.खोलो   = simple_खोलो,
	.पढ़ो   = mtip_hw_पढ़ो_flags,
	.llseek = no_llseek,
पूर्ण;

/*
 * Create the sysfs related attributes.
 *
 * @dd   Poपूर्णांकer to the driver data काष्ठाure.
 * @kobj Poपूर्णांकer to the kobj क्रम the block device.
 *
 * वापस value
 *	0	Operation completed successfully.
 *	-EINVAL Invalid parameter.
 */
अटल पूर्णांक mtip_hw_sysfs_init(काष्ठा driver_data *dd, काष्ठा kobject *kobj)
अणु
	अगर (!kobj || !dd)
		वापस -EINVAL;

	अगर (sysfs_create_file(kobj, &dev_attr_status.attr))
		dev_warn(&dd->pdev->dev,
			"Error creating 'status' sysfs entry\n");
	वापस 0;
पूर्ण

/*
 * Remove the sysfs related attributes.
 *
 * @dd   Poपूर्णांकer to the driver data काष्ठाure.
 * @kobj Poपूर्णांकer to the kobj क्रम the block device.
 *
 * वापस value
 *	0	Operation completed successfully.
 *	-EINVAL Invalid parameter.
 */
अटल पूर्णांक mtip_hw_sysfs_निकास(काष्ठा driver_data *dd, काष्ठा kobject *kobj)
अणु
	अगर (!kobj || !dd)
		वापस -EINVAL;

	sysfs_हटाओ_file(kobj, &dev_attr_status.attr);

	वापस 0;
पूर्ण

अटल पूर्णांक mtip_hw_debugfs_init(काष्ठा driver_data *dd)
अणु
	अगर (!dfs_parent)
		वापस -1;

	dd->dfs_node = debugfs_create_dir(dd->disk->disk_name, dfs_parent);
	अगर (IS_ERR_OR_शून्य(dd->dfs_node)) अणु
		dev_warn(&dd->pdev->dev,
			"Error creating node %s under debugfs\n",
						dd->disk->disk_name);
		dd->dfs_node = शून्य;
		वापस -1;
	पूर्ण

	debugfs_create_file("flags", 0444, dd->dfs_node, dd, &mtip_flags_fops);
	debugfs_create_file("registers", 0444, dd->dfs_node, dd,
			    &mtip_regs_fops);

	वापस 0;
पूर्ण

अटल व्योम mtip_hw_debugfs_निकास(काष्ठा driver_data *dd)
अणु
	debugfs_हटाओ_recursive(dd->dfs_node);
पूर्ण

/*
 * Perक्रमm any init/resume समय hardware setup
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल अंतरभूत व्योम hba_setup(काष्ठा driver_data *dd)
अणु
	u32 hwdata;
	hwdata = पढ़ोl(dd->mmio + HOST_HSORG);

	/* पूर्णांकerrupt bug workaround: use only 1 IS bit.*/
	ग_लिखोl(hwdata |
		HSORG_DISABLE_SLOTGRP_INTR |
		HSORG_DISABLE_SLOTGRP_PXIS,
		dd->mmio + HOST_HSORG);
पूर्ण

अटल पूर्णांक mtip_device_unaligned_स्थिरrained(काष्ठा driver_data *dd)
अणु
	वापस (dd->pdev->device == P420M_DEVICE_ID ? 1 : 0);
पूर्ण

/*
 * Detect the details of the product, and store anything needed
 * पूर्णांकo the driver data काष्ठाure.  This includes product type and
 * version and number of slot groups.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_detect_product(काष्ठा driver_data *dd)
अणु
	u32 hwdata;
	अचिन्हित पूर्णांक rev, slotgroups;

	/*
	 * HBA base + 0xFC [15:0] - venकरोr-specअगरic hardware पूर्णांकerface
	 * info रेजिस्टर:
	 * [15:8] hardware/software पूर्णांकerface rev#
	 * [   3] asic-style पूर्णांकerface
	 * [ 2:0] number of slot groups, minus 1 (only valid क्रम asic-style).
	 */
	hwdata = पढ़ोl(dd->mmio + HOST_HSORG);

	dd->product_type = MTIP_PRODUCT_UNKNOWN;
	dd->slot_groups = 1;

	अगर (hwdata & 0x8) अणु
		dd->product_type = MTIP_PRODUCT_ASICFPGA;
		rev = (hwdata & HSORG_HWREV) >> 8;
		slotgroups = (hwdata & HSORG_SLOTGROUPS) + 1;
		dev_info(&dd->pdev->dev,
			"ASIC-FPGA design, HS rev 0x%x, "
			"%i slot groups [%i slots]\n",
			 rev,
			 slotgroups,
			 slotgroups * 32);

		अगर (slotgroups > MTIP_MAX_SLOT_GROUPS) अणु
			dev_warn(&dd->pdev->dev,
				"Warning: driver only supports "
				"%i slot groups.\n", MTIP_MAX_SLOT_GROUPS);
			slotgroups = MTIP_MAX_SLOT_GROUPS;
		पूर्ण
		dd->slot_groups = slotgroups;
		वापस;
	पूर्ण

	dev_warn(&dd->pdev->dev, "Unrecognized product id\n");
पूर्ण

/*
 * Blocking रुको क्रम FTL rebuild to complete
 *
 * @dd Poपूर्णांकer to the DRIVER_DATA काष्ठाure.
 *
 * वापस value
 *	0	FTL rebuild completed successfully
 *	-EFAULT FTL rebuild error/समयout/पूर्णांकerruption
 */
अटल पूर्णांक mtip_ftl_rebuild_poll(काष्ठा driver_data *dd)
अणु
	अचिन्हित दीर्घ समयout, cnt = 0, start;

	dev_warn(&dd->pdev->dev,
		"FTL rebuild in progress. Polling for completion.\n");

	start = jअगरfies;
	समयout = jअगरfies + msecs_to_jअगरfies(MTIP_FTL_REBUILD_TIMEOUT_MS);

	करो अणु
		अगर (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
				&dd->dd_flag)))
			वापस -EFAULT;
		अगर (mtip_check_surprise_removal(dd->pdev))
			वापस -EFAULT;

		अगर (mtip_get_identअगरy(dd->port, शून्य) < 0)
			वापस -EFAULT;

		अगर (*(dd->port->identअगरy + MTIP_FTL_REBUILD_OFFSET) ==
			MTIP_FTL_REBUILD_MAGIC) अणु
			ssleep(1);
			/* Prपूर्णांक message every 3 minutes */
			अगर (cnt++ >= 180) अणु
				dev_warn(&dd->pdev->dev,
				"FTL rebuild in progress (%d secs).\n",
				jअगरfies_to_msecs(jअगरfies - start) / 1000);
				cnt = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&dd->pdev->dev,
				"FTL rebuild complete (%d secs).\n",
			jअगरfies_to_msecs(jअगरfies - start) / 1000);
			mtip_block_initialize(dd);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	/* Check क्रम समयout */
	dev_err(&dd->pdev->dev,
		"Timed out waiting for FTL rebuild to complete (%d secs).\n",
		jअगरfies_to_msecs(jअगरfies - start) / 1000);
	वापस -EFAULT;
पूर्ण

अटल व्योम mtip_softirq_करोne_fn(काष्ठा request *rq)
अणु
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);
	काष्ठा driver_data *dd = rq->q->queuedata;

	/* Unmap the DMA scatter list entries */
	dma_unmap_sg(&dd->pdev->dev, cmd->sg, cmd->scatter_ents,
							cmd->direction);

	अगर (unlikely(cmd->unaligned))
		atomic_inc(&dd->port->cmd_slot_unal);

	blk_mq_end_request(rq, cmd->status);
पूर्ण

अटल bool mtip_पात_cmd(काष्ठा request *req, व्योम *data, bool reserved)
अणु
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(req);
	काष्ठा driver_data *dd = data;

	dbg_prपूर्णांकk(MTIP_DRV_NAME " Aborting request, tag = %d\n", req->tag);

	clear_bit(req->tag, dd->port->cmds_to_issue);
	cmd->status = BLK_STS_IOERR;
	mtip_softirq_करोne_fn(req);
	वापस true;
पूर्ण

अटल bool mtip_queue_cmd(काष्ठा request *req, व्योम *data, bool reserved)
अणु
	काष्ठा driver_data *dd = data;

	set_bit(req->tag, dd->port->cmds_to_issue);
	blk_पात_request(req);
	वापस true;
पूर्ण

/*
 * service thपढ़ो to issue queued commands
 *
 * @data Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0
 */

अटल पूर्णांक mtip_service_thपढ़ो(व्योम *data)
अणु
	काष्ठा driver_data *dd = (काष्ठा driver_data *)data;
	अचिन्हित दीर्घ slot, slot_start, slot_wrap, to;
	अचिन्हित पूर्णांक num_cmd_slots = dd->slot_groups * 32;
	काष्ठा mtip_port *port = dd->port;

	जबतक (1) अणु
		अगर (kthपढ़ो_should_stop() ||
			test_bit(MTIP_PF_SVC_THD_STOP_BIT, &port->flags))
			जाओ st_out;
		clear_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags);

		/*
		 * the condition is to check neither an पूर्णांकernal command is
		 * is in progress nor error handling is active
		 */
		रुको_event_पूर्णांकerruptible(port->svc_रुको, (port->flags) &&
			(port->flags & MTIP_PF_SVC_THD_WORK));

		अगर (kthपढ़ो_should_stop() ||
			test_bit(MTIP_PF_SVC_THD_STOP_BIT, &port->flags))
			जाओ st_out;

		अगर (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
				&dd->dd_flag)))
			जाओ st_out;

		set_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags);

restart_eh:
		/* Demux bits: start with error handling */
		अगर (test_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags)) अणु
			mtip_handle_tfe(dd);
			clear_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags);
		पूर्ण

		अगर (test_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags))
			जाओ restart_eh;

		अगर (test_bit(MTIP_PF_TO_ACTIVE_BIT, &port->flags)) अणु
			to = jअगरfies + msecs_to_jअगरfies(5000);

			करो अणु
				mdelay(100);
			पूर्ण जबतक (atomic_पढ़ो(&dd->irq_workers_active) != 0 &&
				समय_beक्रमe(jअगरfies, to));

			अगर (atomic_पढ़ो(&dd->irq_workers_active) != 0)
				dev_warn(&dd->pdev->dev,
					"Completion workers still active!");

			blk_mq_quiesce_queue(dd->queue);

			blk_mq_tagset_busy_iter(&dd->tags, mtip_queue_cmd, dd);

			set_bit(MTIP_PF_ISSUE_CMDS_BIT, &dd->port->flags);

			अगर (mtip_device_reset(dd))
				blk_mq_tagset_busy_iter(&dd->tags,
							mtip_पात_cmd, dd);

			clear_bit(MTIP_PF_TO_ACTIVE_BIT, &dd->port->flags);

			blk_mq_unquiesce_queue(dd->queue);
		पूर्ण

		अगर (test_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags)) अणु
			slot = 1;
			/* used to restrict the loop to one iteration */
			slot_start = num_cmd_slots;
			slot_wrap = 0;
			जबतक (1) अणु
				slot = find_next_bit(port->cmds_to_issue,
						num_cmd_slots, slot);
				अगर (slot_wrap == 1) अणु
					अगर ((slot_start >= slot) ||
						(slot >= num_cmd_slots))
						अवरोध;
				पूर्ण
				अगर (unlikely(slot_start == num_cmd_slots))
					slot_start = slot;

				अगर (unlikely(slot == num_cmd_slots)) अणु
					slot = 1;
					slot_wrap = 1;
					जारी;
				पूर्ण

				/* Issue the command to the hardware */
				mtip_issue_ncq_command(port, slot);

				clear_bit(slot, port->cmds_to_issue);
			पूर्ण

			clear_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags);
		पूर्ण

		अगर (test_bit(MTIP_PF_REBUILD_BIT, &port->flags)) अणु
			अगर (mtip_ftl_rebuild_poll(dd) == 0)
				clear_bit(MTIP_PF_REBUILD_BIT, &port->flags);
		पूर्ण
	पूर्ण

st_out:
	वापस 0;
पूर्ण

/*
 * DMA region tearकरोwn
 *
 * @dd Poपूर्णांकer to driver_data काष्ठाure
 *
 * वापस value
 *      None
 */
अटल व्योम mtip_dma_मुक्त(काष्ठा driver_data *dd)
अणु
	काष्ठा mtip_port *port = dd->port;

	अगर (port->block1)
		dma_मुक्त_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					port->block1, port->block1_dma);

	अगर (port->command_list) अणु
		dma_मुक्त_coherent(&dd->pdev->dev, AHCI_CMD_TBL_SZ,
				port->command_list, port->command_list_dma);
	पूर्ण
पूर्ण

/*
 * DMA region setup
 *
 * @dd Poपूर्णांकer to driver_data काष्ठाure
 *
 * वापस value
 *      -ENOMEM Not enough मुक्त DMA region space to initialize driver
 */
अटल पूर्णांक mtip_dma_alloc(काष्ठा driver_data *dd)
अणु
	काष्ठा mtip_port *port = dd->port;

	/* Allocate dma memory क्रम RX Fis, Identअगरy, and Sector Bufffer */
	port->block1 =
		dma_alloc_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					&port->block1_dma, GFP_KERNEL);
	अगर (!port->block1)
		वापस -ENOMEM;

	/* Allocate dma memory क्रम command list */
	port->command_list =
		dma_alloc_coherent(&dd->pdev->dev, AHCI_CMD_TBL_SZ,
					&port->command_list_dma, GFP_KERNEL);
	अगर (!port->command_list) अणु
		dma_मुक्त_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					port->block1, port->block1_dma);
		port->block1 = शून्य;
		port->block1_dma = 0;
		वापस -ENOMEM;
	पूर्ण

	/* Setup all poपूर्णांकers पूर्णांकo first DMA region */
	port->rxfis         = port->block1 + AHCI_RX_FIS_OFFSET;
	port->rxfis_dma     = port->block1_dma + AHCI_RX_FIS_OFFSET;
	port->identअगरy      = port->block1 + AHCI_IDFY_OFFSET;
	port->identअगरy_dma  = port->block1_dma + AHCI_IDFY_OFFSET;
	port->log_buf       = port->block1 + AHCI_SECTBUF_OFFSET;
	port->log_buf_dma   = port->block1_dma + AHCI_SECTBUF_OFFSET;
	port->smart_buf     = port->block1 + AHCI_SMARTBUF_OFFSET;
	port->smart_buf_dma = port->block1_dma + AHCI_SMARTBUF_OFFSET;

	वापस 0;
पूर्ण

अटल पूर्णांक mtip_hw_get_identअगरy(काष्ठा driver_data *dd)
अणु
	काष्ठा smart_attr attr242;
	अचिन्हित अक्षर *buf;
	पूर्णांक rv;

	अगर (mtip_get_identअगरy(dd->port, शून्य) < 0)
		वापस -EFAULT;

	अगर (*(dd->port->identअगरy + MTIP_FTL_REBUILD_OFFSET) ==
		MTIP_FTL_REBUILD_MAGIC) अणु
		set_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags);
		वापस MTIP_FTL_REBUILD_MAGIC;
	पूर्ण
	mtip_dump_identअगरy(dd->port);

	/* check ग_लिखो protect, over temp and rebuild statuses */
	rv = mtip_पढ़ो_log_page(dd->port, ATA_LOG_SATA_NCQ,
				dd->port->log_buf,
				dd->port->log_buf_dma, 1);
	अगर (rv) अणु
		dev_warn(&dd->pdev->dev,
			"Error in READ LOG EXT (10h) command\n");
		/* non-critical error, करोn't fail the load */
	पूर्ण अन्यथा अणु
		buf = (अचिन्हित अक्षर *)dd->port->log_buf;
		अगर (buf[259] & 0x1) अणु
			dev_info(&dd->pdev->dev,
				"Write protect bit is set.\n");
			set_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag);
		पूर्ण
		अगर (buf[288] == 0xF7) अणु
			dev_info(&dd->pdev->dev,
				"Exceeded Tmax, drive in thermal shutdown.\n");
			set_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag);
		पूर्ण
		अगर (buf[288] == 0xBF) अणु
			dev_info(&dd->pdev->dev,
				"Drive indicates rebuild has failed.\n");
			set_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag);
		पूर्ण
	पूर्ण

	/* get ग_लिखो protect progess */
	स_रखो(&attr242, 0, माप(काष्ठा smart_attr));
	अगर (mtip_get_smart_attr(dd->port, 242, &attr242))
		dev_warn(&dd->pdev->dev,
				"Unable to check write protect progress\n");
	अन्यथा
		dev_info(&dd->pdev->dev,
				"Write protect progress: %u%% (%u blocks)\n",
				attr242.cur, le32_to_cpu(attr242.data));

	वापस rv;
पूर्ण

/*
 * Called once क्रम each card.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0 on success, अन्यथा an error code.
 */
अटल पूर्णांक mtip_hw_init(काष्ठा driver_data *dd)
अणु
	पूर्णांक i;
	पूर्णांक rv;
	अचिन्हित दीर्घ समयout, समयtaken;

	dd->mmio = pcim_iomap_table(dd->pdev)[MTIP_ABAR];

	mtip_detect_product(dd);
	अगर (dd->product_type == MTIP_PRODUCT_UNKNOWN) अणु
		rv = -EIO;
		जाओ out1;
	पूर्ण

	hba_setup(dd);

	dd->port = kzalloc_node(माप(काष्ठा mtip_port), GFP_KERNEL,
				dd->numa_node);
	अगर (!dd->port) अणु
		dev_err(&dd->pdev->dev,
			"Memory allocation: port structure\n");
		वापस -ENOMEM;
	पूर्ण

	/* Continue workqueue setup */
	क्रम (i = 0; i < MTIP_MAX_SLOT_GROUPS; i++)
		dd->work[i].port = dd->port;

	/* Enable unaligned IO स्थिरraपूर्णांकs क्रम some devices */
	अगर (mtip_device_unaligned_स्थिरrained(dd))
		dd->unal_qdepth = MTIP_MAX_UNALIGNED_SLOTS;
	अन्यथा
		dd->unal_qdepth = 0;

	atomic_set(&dd->port->cmd_slot_unal, dd->unal_qdepth);

	/* Spinlock to prevent concurrent issue */
	क्रम (i = 0; i < MTIP_MAX_SLOT_GROUPS; i++)
		spin_lock_init(&dd->port->cmd_issue_lock[i]);

	/* Set the port mmio base address. */
	dd->port->mmio	= dd->mmio + PORT_OFFSET;
	dd->port->dd	= dd;

	/* DMA allocations */
	rv = mtip_dma_alloc(dd);
	अगर (rv < 0)
		जाओ out1;

	/* Setup the poपूर्णांकers to the extended s_active and CI रेजिस्टरs. */
	क्रम (i = 0; i < dd->slot_groups; i++) अणु
		dd->port->s_active[i] =
			dd->port->mmio + i*0x80 + PORT_SCR_ACT;
		dd->port->cmd_issue[i] =
			dd->port->mmio + i*0x80 + PORT_COMMAND_ISSUE;
		dd->port->completed[i] =
			dd->port->mmio + i*0x80 + PORT_SDBV;
	पूर्ण

	समयtaken = jअगरfies;
	समयout = jअगरfies + msecs_to_jअगरfies(30000);
	जबतक (((पढ़ोl(dd->port->mmio + PORT_SCR_STAT) & 0x0F) != 0x03) &&
		 समय_beक्रमe(jअगरfies, समयout)) अणु
		mdelay(100);
	पूर्ण
	अगर (unlikely(mtip_check_surprise_removal(dd->pdev))) अणु
		समयtaken = jअगरfies - समयtaken;
		dev_warn(&dd->pdev->dev,
			"Surprise removal detected at %u ms\n",
			jअगरfies_to_msecs(समयtaken));
		rv = -ENODEV;
		जाओ out2 ;
	पूर्ण
	अगर (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))) अणु
		समयtaken = jअगरfies - समयtaken;
		dev_warn(&dd->pdev->dev,
			"Removal detected at %u ms\n",
			jअगरfies_to_msecs(समयtaken));
		rv = -EFAULT;
		जाओ out2;
	पूर्ण

	/* Conditionally reset the HBA. */
	अगर (!(पढ़ोl(dd->mmio + HOST_CAP) & HOST_CAP_NZDMA)) अणु
		अगर (mtip_hba_reset(dd) < 0) अणु
			dev_err(&dd->pdev->dev,
				"Card did not reset within timeout\n");
			rv = -EIO;
			जाओ out2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Clear any pending पूर्णांकerrupts on the HBA */
		ग_लिखोl(पढ़ोl(dd->mmio + HOST_IRQ_STAT),
			dd->mmio + HOST_IRQ_STAT);
	पूर्ण

	mtip_init_port(dd->port);
	mtip_start_port(dd->port);

	/* Setup the ISR and enable पूर्णांकerrupts. */
	rv = request_irq(dd->pdev->irq, mtip_irq_handler, IRQF_SHARED,
			 dev_driver_string(&dd->pdev->dev), dd);
	अगर (rv) अणु
		dev_err(&dd->pdev->dev,
			"Unable to allocate IRQ %d\n", dd->pdev->irq);
		जाओ out2;
	पूर्ण
	irq_set_affinity_hपूर्णांक(dd->pdev->irq, get_cpu_mask(dd->isr_binding));

	/* Enable पूर्णांकerrupts on the HBA. */
	ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
					dd->mmio + HOST_CTL);

	init_रुकोqueue_head(&dd->port->svc_रुको);

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag)) अणु
		rv = -EFAULT;
		जाओ out3;
	पूर्ण

	वापस rv;

out3:
	/* Disable पूर्णांकerrupts on the HBA. */
	ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
			dd->mmio + HOST_CTL);

	/* Release the IRQ. */
	irq_set_affinity_hपूर्णांक(dd->pdev->irq, शून्य);
	मुक्त_irq(dd->pdev->irq, dd);

out2:
	mtip_deinit_port(dd->port);
	mtip_dma_मुक्त(dd);

out1:
	/* Free the memory allocated क्रम the क्रम काष्ठाure. */
	kमुक्त(dd->port);

	वापस rv;
पूर्ण

अटल पूर्णांक mtip_standby_drive(काष्ठा driver_data *dd)
अणु
	पूर्णांक rv = 0;

	अगर (dd->sr || !dd->port)
		वापस -ENODEV;
	/*
	 * Send standby immediate (E0h) to the drive so that it
	 * saves its state.
	 */
	अगर (!test_bit(MTIP_PF_REBUILD_BIT, &dd->port->flags) &&
	    !test_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag) &&
	    !test_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag)) अणु
		rv = mtip_standby_immediate(dd->port);
		अगर (rv)
			dev_warn(&dd->pdev->dev,
				"STANDBY IMMEDIATE failed\n");
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Called to deinitialize an पूर्णांकerface.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0
 */
अटल पूर्णांक mtip_hw_निकास(काष्ठा driver_data *dd)
अणु
	अगर (!dd->sr) अणु
		/* de-initialize the port. */
		mtip_deinit_port(dd->port);

		/* Disable पूर्णांकerrupts on the HBA. */
		ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
				dd->mmio + HOST_CTL);
	पूर्ण

	/* Release the IRQ. */
	irq_set_affinity_hपूर्णांक(dd->pdev->irq, शून्य);
	मुक्त_irq(dd->pdev->irq, dd);
	msleep(1000);

	/* Free dma regions */
	mtip_dma_मुक्त(dd);

	/* Free the memory allocated क्रम the क्रम काष्ठाure. */
	kमुक्त(dd->port);
	dd->port = शून्य;

	वापस 0;
पूर्ण

/*
 * Issue a Standby Immediate command to the device.
 *
 * This function is called by the Block Layer just beक्रमe the
 * प्रणाली घातers off during a shutकरोwn.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0
 */
अटल पूर्णांक mtip_hw_shutकरोwn(काष्ठा driver_data *dd)
अणु
	/*
	 * Send standby immediate (E0h) to the drive so that it
	 * saves its state.
	 */
	mtip_standby_drive(dd);

	वापस 0;
पूर्ण

/*
 * Suspend function
 *
 * This function is called by the Block Layer just beक्रमe the
 * प्रणाली hibernates.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0	Suspend was successful
 *	-EFAULT Suspend was not successful
 */
अटल पूर्णांक mtip_hw_suspend(काष्ठा driver_data *dd)
अणु
	/*
	 * Send standby immediate (E0h) to the drive
	 * so that it saves its state.
	 */
	अगर (mtip_standby_drive(dd) != 0) अणु
		dev_err(&dd->pdev->dev,
			"Failed standby-immediate command\n");
		वापस -EFAULT;
	पूर्ण

	/* Disable पूर्णांकerrupts on the HBA.*/
	ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
			dd->mmio + HOST_CTL);
	mtip_deinit_port(dd->port);

	वापस 0;
पूर्ण

/*
 * Resume function
 *
 * This function is called by the Block Layer as the
 * प्रणाली resumes.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0	Resume was successful
 *      -EFAULT Resume was not successful
 */
अटल पूर्णांक mtip_hw_resume(काष्ठा driver_data *dd)
अणु
	/* Perक्रमm any needed hardware setup steps */
	hba_setup(dd);

	/* Reset the HBA */
	अगर (mtip_hba_reset(dd) != 0) अणु
		dev_err(&dd->pdev->dev,
			"Unable to reset the HBA\n");
		वापस -EFAULT;
	पूर्ण

	/*
	 * Enable the port, DMA engine, and FIS reception specअगरic
	 * h/w in controller.
	 */
	mtip_init_port(dd->port);
	mtip_start_port(dd->port);

	/* Enable पूर्णांकerrupts on the HBA.*/
	ग_लिखोl(पढ़ोl(dd->mmio + HOST_CTL) | HOST_IRQ_EN,
			dd->mmio + HOST_CTL);

	वापस 0;
पूर्ण

/*
 * Helper function क्रम reusing disk name
 * upon hot insertion.
 */
अटल पूर्णांक rssd_disk_name_क्रमmat(अक्षर *prefix,
				 पूर्णांक index,
				 अक्षर *buf,
				 पूर्णांक buflen)
अणु
	स्थिर पूर्णांक base = 'z' - 'a' + 1;
	अक्षर *begin = buf + म_माप(prefix);
	अक्षर *end = buf + buflen;
	अक्षर *p;
	पूर्णांक unit;

	p = end - 1;
	*p = '\0';
	unit = base;
	करो अणु
		अगर (p == begin)
			वापस -EINVAL;
		*--p = 'a' + (index % unit);
		index = (index / unit) - 1;
	पूर्ण जबतक (index >= 0);

	स_हटाओ(begin, p, end - p);
	स_नकल(buf, prefix, म_माप(prefix));

	वापस 0;
पूर्ण

/*
 * Block layer IOCTL handler.
 *
 * @dev Poपूर्णांकer to the block_device काष्ठाure.
 * @mode ignored
 * @cmd IOCTL command passed from the user application.
 * @arg Argument passed from the user application.
 *
 * वापस value
 *	0        IOCTL completed successfully.
 *	-ENOTTY  IOCTL not supported or invalid driver data
 *                 काष्ठाure poपूर्णांकer.
 */
अटल पूर्णांक mtip_block_ioctl(काष्ठा block_device *dev,
			    भ_शेषe_t mode,
			    अचिन्हित cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा driver_data *dd = dev->bd_disk->निजी_data;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!dd)
		वापस -ENOTTY;

	अगर (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag)))
		वापस -ENOTTY;

	चयन (cmd) अणु
	हाल BLKFLSBUF:
		वापस -ENOTTY;
	शेष:
		वापस mtip_hw_ioctl(dd, cmd, arg);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Block layer compat IOCTL handler.
 *
 * @dev Poपूर्णांकer to the block_device काष्ठाure.
 * @mode ignored
 * @cmd IOCTL command passed from the user application.
 * @arg Argument passed from the user application.
 *
 * वापस value
 *	0        IOCTL completed successfully.
 *	-ENOTTY  IOCTL not supported or invalid driver data
 *                 काष्ठाure poपूर्णांकer.
 */
अटल पूर्णांक mtip_block_compat_ioctl(काष्ठा block_device *dev,
			    भ_शेषe_t mode,
			    अचिन्हित cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा driver_data *dd = dev->bd_disk->निजी_data;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!dd)
		वापस -ENOTTY;

	अगर (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag)))
		वापस -ENOTTY;

	चयन (cmd) अणु
	हाल BLKFLSBUF:
		वापस -ENOTTY;
	हाल HDIO_DRIVE_TASKखाता: अणु
		काष्ठा mtip_compat_ide_task_request_s __user *compat_req_task;
		ide_task_request_t req_task;
		पूर्णांक compat_tasksize, outtotal, ret;

		compat_tasksize =
			माप(काष्ठा mtip_compat_ide_task_request_s);

		compat_req_task =
			(काष्ठा mtip_compat_ide_task_request_s __user *) arg;

		अगर (copy_from_user(&req_task, (व्योम __user *) arg,
			compat_tasksize - (2 * माप(compat_दीर्घ_t))))
			वापस -EFAULT;

		अगर (get_user(req_task.out_size, &compat_req_task->out_size))
			वापस -EFAULT;

		अगर (get_user(req_task.in_size, &compat_req_task->in_size))
			वापस -EFAULT;

		outtotal = माप(काष्ठा mtip_compat_ide_task_request_s);

		ret = exec_drive_taskfile(dd, (व्योम __user *) arg,
						&req_task, outtotal);

		अगर (copy_to_user((व्योम __user *) arg, &req_task,
				compat_tasksize -
				(2 * माप(compat_दीर्घ_t))))
			वापस -EFAULT;

		अगर (put_user(req_task.out_size, &compat_req_task->out_size))
			वापस -EFAULT;

		अगर (put_user(req_task.in_size, &compat_req_task->in_size))
			वापस -EFAULT;

		वापस ret;
	पूर्ण
	शेष:
		वापस mtip_hw_ioctl(dd, cmd, arg);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Obtain the geometry of the device.
 *
 * You may think that this function is obsolete, but some applications,
 * fdisk क्रम example still used CHS values. This function describes the
 * device as having 224 heads and 56 sectors per cylinder. These values are
 * chosen so that each cylinder is aligned on a 4KB boundary. Since a
 * partition is described in terms of a start and end cylinder this means
 * that each partition is also 4KB aligned. Non-aligned partitions adversely
 * affects perक्रमmance.
 *
 * @dev Poपूर्णांकer to the block_device strucutre.
 * @geo Poपूर्णांकer to a hd_geometry काष्ठाure.
 *
 * वापस value
 *	0       Operation completed successfully.
 *	-ENOTTY An error occurred जबतक पढ़ोing the drive capacity.
 */
अटल पूर्णांक mtip_block_getgeo(काष्ठा block_device *dev,
				काष्ठा hd_geometry *geo)
अणु
	काष्ठा driver_data *dd = dev->bd_disk->निजी_data;
	sector_t capacity;

	अगर (!dd)
		वापस -ENOTTY;

	अगर (!(mtip_hw_get_capacity(dd, &capacity))) अणु
		dev_warn(&dd->pdev->dev,
			"Could not get drive capacity.\n");
		वापस -ENOTTY;
	पूर्ण

	geo->heads = 224;
	geo->sectors = 56;
	sector_भाग(capacity, (geo->heads * geo->sectors));
	geo->cylinders = capacity;
	वापस 0;
पूर्ण

अटल पूर्णांक mtip_block_खोलो(काष्ठा block_device *dev, भ_शेषe_t mode)
अणु
	काष्ठा driver_data *dd;

	अगर (dev && dev->bd_disk) अणु
		dd = (काष्ठा driver_data *) dev->bd_disk->निजी_data;

		अगर (dd) अणु
			अगर (test_bit(MTIP_DDF_REMOVAL_BIT,
							&dd->dd_flag)) अणु
				वापस -ENODEV;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम mtip_block_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
पूर्ण

/*
 * Block device operation function.
 *
 * This काष्ठाure contains poपूर्णांकers to the functions required by the block
 * layer.
 */
अटल स्थिर काष्ठा block_device_operations mtip_block_ops = अणु
	.खोलो		= mtip_block_खोलो,
	.release	= mtip_block_release,
	.ioctl		= mtip_block_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= mtip_block_compat_ioctl,
#पूर्ण_अगर
	.getgeo		= mtip_block_getgeo,
	.owner		= THIS_MODULE
पूर्ण;

अटल अंतरभूत bool is_se_active(काष्ठा driver_data *dd)
अणु
	अगर (unlikely(test_bit(MTIP_PF_SE_ACTIVE_BIT, &dd->port->flags))) अणु
		अगर (dd->port->ic_छोड़ो_समयr) अणु
			अचिन्हित दीर्घ to = dd->port->ic_छोड़ो_समयr +
							msecs_to_jअगरfies(1000);
			अगर (समय_after(jअगरfies, to)) अणु
				clear_bit(MTIP_PF_SE_ACTIVE_BIT,
							&dd->port->flags);
				clear_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag);
				dd->port->ic_छोड़ो_समयr = 0;
				wake_up_पूर्णांकerruptible(&dd->port->svc_रुको);
				वापस false;
			पूर्ण
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool is_stopped(काष्ठा driver_data *dd, काष्ठा request *rq)
अणु
	अगर (likely(!(dd->dd_flag & MTIP_DDF_STOP_IO)))
		वापस false;

	अगर (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))
		वापस true;
	अगर (test_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag))
		वापस true;
	अगर (test_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag) &&
	    rq_data_dir(rq))
		वापस true;
	अगर (test_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag))
		वापस true;
	अगर (test_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag))
		वापस true;

	वापस false;
पूर्ण

अटल bool mtip_check_unal_depth(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा request *rq)
अणु
	काष्ठा driver_data *dd = hctx->queue->queuedata;
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	अगर (rq_data_dir(rq) == READ || !dd->unal_qdepth)
		वापस false;

	/*
	 * If unaligned depth must be limited on this controller, mark it
	 * as unaligned अगर the IO isn't on a 4k boundary (start of length).
	 */
	अगर (blk_rq_sectors(rq) <= 64) अणु
		अगर ((blk_rq_pos(rq) & 7) || (blk_rq_sectors(rq) & 7))
			cmd->unaligned = 1;
	पूर्ण

	अगर (cmd->unaligned && atomic_dec_अगर_positive(&dd->port->cmd_slot_unal) >= 0)
		वापस true;

	वापस false;
पूर्ण

अटल blk_status_t mtip_issue_reserved_cmd(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा request *rq)
अणु
	काष्ठा driver_data *dd = hctx->queue->queuedata;
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);
	काष्ठा mtip_पूर्णांक_cmd *icmd = cmd->icmd;
	काष्ठा mtip_cmd_hdr *hdr =
		dd->port->command_list + माप(काष्ठा mtip_cmd_hdr) * rq->tag;
	काष्ठा mtip_cmd_sg *command_sg;

	अगर (mtip_commands_active(dd->port))
		वापस BLK_STS_DEV_RESOURCE;

	hdr->ctba = cpu_to_le32(cmd->command_dma & 0xFFFFFFFF);
	अगर (test_bit(MTIP_PF_HOST_CAP_64, &dd->port->flags))
		hdr->ctbau = cpu_to_le32((cmd->command_dma >> 16) >> 16);
	/* Populate the SG list */
	hdr->opts = cpu_to_le32(icmd->opts | icmd->fis_len);
	अगर (icmd->buf_len) अणु
		command_sg = cmd->command + AHCI_CMD_TBL_HDR_SZ;

		command_sg->info = cpu_to_le32((icmd->buf_len-1) & 0x3FFFFF);
		command_sg->dba	= cpu_to_le32(icmd->buffer & 0xFFFFFFFF);
		command_sg->dba_upper =
			cpu_to_le32((icmd->buffer >> 16) >> 16);

		hdr->opts |= cpu_to_le32((1 << 16));
	पूर्ण

	/* Populate the command header */
	hdr->byte_count = 0;

	blk_mq_start_request(rq);
	mtip_issue_non_ncq_command(dd->port, rq->tag);
	वापस 0;
पूर्ण

अटल blk_status_t mtip_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा driver_data *dd = hctx->queue->queuedata;
	काष्ठा request *rq = bd->rq;
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	अगर (blk_rq_is_passthrough(rq))
		वापस mtip_issue_reserved_cmd(hctx, rq);

	अगर (unlikely(mtip_check_unal_depth(hctx, rq)))
		वापस BLK_STS_DEV_RESOURCE;

	अगर (is_se_active(dd) || is_stopped(dd, rq))
		वापस BLK_STS_IOERR;

	blk_mq_start_request(rq);

	mtip_hw_submit_io(dd, rq, cmd, hctx);
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम mtip_मुक्त_cmd(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
			  अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा driver_data *dd = set->driver_data;
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	अगर (!cmd->command)
		वापस;

	dma_मुक्त_coherent(&dd->pdev->dev, CMD_DMA_ALLOC_SZ, cmd->command,
			  cmd->command_dma);
पूर्ण

अटल पूर्णांक mtip_init_cmd(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
			 अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा driver_data *dd = set->driver_data;
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	cmd->command = dma_alloc_coherent(&dd->pdev->dev, CMD_DMA_ALLOC_SZ,
			&cmd->command_dma, GFP_KERNEL);
	अगर (!cmd->command)
		वापस -ENOMEM;

	sg_init_table(cmd->sg, MTIP_MAX_SG);
	वापस 0;
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस mtip_cmd_समयout(काष्ठा request *req,
								bool reserved)
अणु
	काष्ठा driver_data *dd = req->q->queuedata;

	अगर (reserved) अणु
		काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(req);

		cmd->status = BLK_STS_TIMEOUT;
		blk_mq_complete_request(req);
		वापस BLK_EH_DONE;
	पूर्ण

	अगर (test_bit(req->tag, dd->port->cmds_to_issue))
		जाओ निकास_handler;

	अगर (test_and_set_bit(MTIP_PF_TO_ACTIVE_BIT, &dd->port->flags))
		जाओ निकास_handler;

	wake_up_पूर्णांकerruptible(&dd->port->svc_रुको);
निकास_handler:
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops mtip_mq_ops = अणु
	.queue_rq	= mtip_queue_rq,
	.init_request	= mtip_init_cmd,
	.निकास_request	= mtip_मुक्त_cmd,
	.complete	= mtip_softirq_करोne_fn,
	.समयout        = mtip_cmd_समयout,
पूर्ण;

/*
 * Block layer initialization function.
 *
 * This function is called once by the PCI layer क्रम each P320
 * device that is connected to the प्रणाली.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0 on success अन्यथा an error code.
 */
अटल पूर्णांक mtip_block_initialize(काष्ठा driver_data *dd)
अणु
	पूर्णांक rv = 0, रुको_क्रम_rebuild = 0;
	sector_t capacity;
	अचिन्हित पूर्णांक index = 0;
	काष्ठा kobject *kobj;

	अगर (dd->disk)
		जाओ skip_create_disk; /* hw init करोne, beक्रमe rebuild */

	अगर (mtip_hw_init(dd)) अणु
		rv = -EINVAL;
		जाओ protocol_init_error;
	पूर्ण

	dd->disk = alloc_disk_node(MTIP_MAX_MINORS, dd->numa_node);
	अगर (dd->disk  == शून्य) अणु
		dev_err(&dd->pdev->dev,
			"Unable to allocate gendisk structure\n");
		rv = -EINVAL;
		जाओ alloc_disk_error;
	पूर्ण

	rv = ida_alloc(&rssd_index_ida, GFP_KERNEL);
	अगर (rv < 0)
		जाओ ida_get_error;
	index = rv;

	rv = rssd_disk_name_क्रमmat("rssd",
				index,
				dd->disk->disk_name,
				DISK_NAME_LEN);
	अगर (rv)
		जाओ disk_index_error;

	dd->disk->major		= dd->major;
	dd->disk->first_minor	= index * MTIP_MAX_MINORS;
	dd->disk->minors 	= MTIP_MAX_MINORS;
	dd->disk->fops		= &mtip_block_ops;
	dd->disk->निजी_data	= dd;
	dd->index		= index;

	mtip_hw_debugfs_init(dd);

	स_रखो(&dd->tags, 0, माप(dd->tags));
	dd->tags.ops = &mtip_mq_ops;
	dd->tags.nr_hw_queues = 1;
	dd->tags.queue_depth = MTIP_MAX_COMMAND_SLOTS;
	dd->tags.reserved_tags = 1;
	dd->tags.cmd_size = माप(काष्ठा mtip_cmd);
	dd->tags.numa_node = dd->numa_node;
	dd->tags.flags = BLK_MQ_F_SHOULD_MERGE;
	dd->tags.driver_data = dd;
	dd->tags.समयout = MTIP_NCQ_CMD_TIMEOUT_MS;

	rv = blk_mq_alloc_tag_set(&dd->tags);
	अगर (rv) अणु
		dev_err(&dd->pdev->dev,
			"Unable to allocate request queue\n");
		जाओ block_queue_alloc_tag_error;
	पूर्ण

	/* Allocate the request queue. */
	dd->queue = blk_mq_init_queue(&dd->tags);
	अगर (IS_ERR(dd->queue)) अणु
		dev_err(&dd->pdev->dev,
			"Unable to allocate request queue\n");
		rv = -ENOMEM;
		जाओ block_queue_alloc_init_error;
	पूर्ण

	dd->disk->queue		= dd->queue;
	dd->queue->queuedata	= dd;

skip_create_disk:
	/* Initialize the protocol layer. */
	रुको_क्रम_rebuild = mtip_hw_get_identअगरy(dd);
	अगर (रुको_क्रम_rebuild < 0) अणु
		dev_err(&dd->pdev->dev,
			"Protocol layer initialization failed\n");
		rv = -EINVAL;
		जाओ init_hw_cmds_error;
	पूर्ण

	/*
	 * अगर rebuild pending, start the service thपढ़ो, and delay the block
	 * queue creation and device_add_disk()
	 */
	अगर (रुको_क्रम_rebuild == MTIP_FTL_REBUILD_MAGIC)
		जाओ start_service_thपढ़ो;

	/* Set device limits. */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, dd->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, dd->queue);
	blk_queue_max_segments(dd->queue, MTIP_MAX_SG);
	blk_queue_physical_block_size(dd->queue, 4096);
	blk_queue_max_hw_sectors(dd->queue, 0xffff);
	blk_queue_max_segment_size(dd->queue, 0x400000);
	dma_set_max_seg_size(&dd->pdev->dev, 0x400000);
	blk_queue_io_min(dd->queue, 4096);

	/* Set the capacity of the device in 512 byte sectors. */
	अगर (!(mtip_hw_get_capacity(dd, &capacity))) अणु
		dev_warn(&dd->pdev->dev,
			"Could not read drive capacity\n");
		rv = -EIO;
		जाओ पढ़ो_capacity_error;
	पूर्ण
	set_capacity(dd->disk, capacity);

	/* Enable the block device and add it to /dev */
	device_add_disk(&dd->pdev->dev, dd->disk, शून्य);

	/*
	 * Now that the disk is active, initialize any sysfs attributes
	 * managed by the protocol layer.
	 */
	kobj = kobject_get(&disk_to_dev(dd->disk)->kobj);
	अगर (kobj) अणु
		mtip_hw_sysfs_init(dd, kobj);
		kobject_put(kobj);
	पूर्ण

	अगर (dd->mtip_svc_handler) अणु
		set_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag);
		वापस rv; /* service thपढ़ो created क्रम handling rebuild */
	पूर्ण

start_service_thपढ़ो:
	dd->mtip_svc_handler = kthपढ़ो_create_on_node(mtip_service_thपढ़ो,
						dd, dd->numa_node,
						"mtip_svc_thd_%02d", index);

	अगर (IS_ERR(dd->mtip_svc_handler)) अणु
		dev_err(&dd->pdev->dev, "service thread failed to start\n");
		dd->mtip_svc_handler = शून्य;
		rv = -EFAULT;
		जाओ kthपढ़ो_run_error;
	पूर्ण
	wake_up_process(dd->mtip_svc_handler);
	अगर (रुको_क्रम_rebuild == MTIP_FTL_REBUILD_MAGIC)
		rv = रुको_क्रम_rebuild;

	वापस rv;

kthपढ़ो_run_error:
	/* Delete our gendisk. This also हटाओs the device from /dev */
	del_gendisk(dd->disk);

पढ़ो_capacity_error:
init_hw_cmds_error:
	blk_cleanup_queue(dd->queue);
block_queue_alloc_init_error:
	blk_mq_मुक्त_tag_set(&dd->tags);
block_queue_alloc_tag_error:
	mtip_hw_debugfs_निकास(dd);
disk_index_error:
	ida_मुक्त(&rssd_index_ida, index);

ida_get_error:
	put_disk(dd->disk);

alloc_disk_error:
	mtip_hw_निकास(dd); /* De-initialize the protocol layer. */

protocol_init_error:
	वापस rv;
पूर्ण

अटल bool mtip_no_dev_cleanup(काष्ठा request *rq, व्योम *data, bool reserv)
अणु
	काष्ठा mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	cmd->status = BLK_STS_IOERR;
	blk_mq_complete_request(rq);
	वापस true;
पूर्ण

/*
 * Block layer deinitialization function.
 *
 * Called by the PCI layer as each P320 device is हटाओd.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0
 */
अटल पूर्णांक mtip_block_हटाओ(काष्ठा driver_data *dd)
अणु
	काष्ठा kobject *kobj;

	mtip_hw_debugfs_निकास(dd);

	अगर (dd->mtip_svc_handler) अणु
		set_bit(MTIP_PF_SVC_THD_STOP_BIT, &dd->port->flags);
		wake_up_पूर्णांकerruptible(&dd->port->svc_रुको);
		kthपढ़ो_stop(dd->mtip_svc_handler);
	पूर्ण

	/* Clean up the sysfs attributes, अगर created */
	अगर (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag)) अणु
		kobj = kobject_get(&disk_to_dev(dd->disk)->kobj);
		अगर (kobj) अणु
			mtip_hw_sysfs_निकास(dd, kobj);
			kobject_put(kobj);
		पूर्ण
	पूर्ण

	अगर (!dd->sr) अणु
		/*
		 * Explicitly रुको here क्रम IOs to quiesce,
		 * as mtip_standby_drive usually won't रुको क्रम IOs.
		 */
		अगर (!mtip_quiesce_io(dd->port, MTIP_QUIESCE_IO_TIMEOUT_MS))
			mtip_standby_drive(dd);
	पूर्ण
	अन्यथा
		dev_info(&dd->pdev->dev, "device %s surprise removal\n",
						dd->disk->disk_name);

	blk_मुक्तze_queue_start(dd->queue);
	blk_mq_quiesce_queue(dd->queue);
	blk_mq_tagset_busy_iter(&dd->tags, mtip_no_dev_cleanup, dd);
	blk_mq_unquiesce_queue(dd->queue);

	अगर (dd->disk) अणु
		अगर (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag))
			del_gendisk(dd->disk);
		अगर (dd->disk->queue) अणु
			blk_cleanup_queue(dd->queue);
			blk_mq_मुक्त_tag_set(&dd->tags);
			dd->queue = शून्य;
		पूर्ण
		put_disk(dd->disk);
	पूर्ण
	dd->disk  = शून्य;

	ida_मुक्त(&rssd_index_ida, dd->index);

	/* De-initialize the protocol layer. */
	mtip_hw_निकास(dd);

	वापस 0;
पूर्ण

/*
 * Function called by the PCI layer when just beक्रमe the
 * machine shuts करोwn.
 *
 * If a protocol layer shutकरोwn function is present it will be called
 * by this function.
 *
 * @dd Poपूर्णांकer to the driver data काष्ठाure.
 *
 * वापस value
 *	0
 */
अटल पूर्णांक mtip_block_shutकरोwn(काष्ठा driver_data *dd)
अणु
	mtip_hw_shutकरोwn(dd);

	/* Delete our gendisk काष्ठाure, and cleanup the blk queue. */
	अगर (dd->disk) अणु
		dev_info(&dd->pdev->dev,
			"Shutting down %s ...\n", dd->disk->disk_name);

		अगर (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag))
			del_gendisk(dd->disk);
		अगर (dd->disk->queue) अणु
			blk_cleanup_queue(dd->queue);
			blk_mq_मुक्त_tag_set(&dd->tags);
		पूर्ण
		put_disk(dd->disk);
		dd->disk  = शून्य;
		dd->queue = शून्य;
	पूर्ण

	ida_मुक्त(&rssd_index_ida, dd->index);
	वापस 0;
पूर्ण

अटल पूर्णांक mtip_block_suspend(काष्ठा driver_data *dd)
अणु
	dev_info(&dd->pdev->dev,
		"Suspending %s ...\n", dd->disk->disk_name);
	mtip_hw_suspend(dd);
	वापस 0;
पूर्ण

अटल पूर्णांक mtip_block_resume(काष्ठा driver_data *dd)
अणु
	dev_info(&dd->pdev->dev, "Resuming %s ...\n",
		dd->disk->disk_name);
	mtip_hw_resume(dd);
	वापस 0;
पूर्ण

अटल व्योम drop_cpu(पूर्णांक cpu)
अणु
	cpu_use[cpu]--;
पूर्ण

अटल पूर्णांक get_least_used_cpu_on_node(पूर्णांक node)
अणु
	पूर्णांक cpu, least_used_cpu, least_cnt;
	स्थिर काष्ठा cpumask *node_mask;

	node_mask = cpumask_of_node(node);
	least_used_cpu = cpumask_first(node_mask);
	least_cnt = cpu_use[least_used_cpu];
	cpu = least_used_cpu;

	क्रम_each_cpu(cpu, node_mask) अणु
		अगर (cpu_use[cpu] < least_cnt) अणु
			least_used_cpu = cpu;
			least_cnt = cpu_use[cpu];
		पूर्ण
	पूर्ण
	cpu_use[least_used_cpu]++;
	वापस least_used_cpu;
पूर्ण

/* Helper क्रम selecting a node in round robin mode */
अटल अंतरभूत पूर्णांक mtip_get_next_rr_node(व्योम)
अणु
	अटल पूर्णांक next_node = NUMA_NO_NODE;

	अगर (next_node == NUMA_NO_NODE) अणु
		next_node = first_online_node;
		वापस next_node;
	पूर्ण

	next_node = next_online_node(next_node);
	अगर (next_node == MAX_NUMNODES)
		next_node = first_online_node;
	वापस next_node;
पूर्ण

अटल DEFINE_HANDLER(0);
अटल DEFINE_HANDLER(1);
अटल DEFINE_HANDLER(2);
अटल DEFINE_HANDLER(3);
अटल DEFINE_HANDLER(4);
अटल DEFINE_HANDLER(5);
अटल DEFINE_HANDLER(6);
अटल DEFINE_HANDLER(7);

अटल व्योम mtip_disable_link_opts(काष्ठा driver_data *dd, काष्ठा pci_dev *pdev)
अणु
	अचिन्हित लघु pcie_dev_ctrl;

	अगर (pci_is_pcie(pdev)) अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVCTL, &pcie_dev_ctrl);
		अगर (pcie_dev_ctrl & PCI_EXP_DEVCTL_NOSNOOP_EN ||
		    pcie_dev_ctrl & PCI_EXP_DEVCTL_RELAX_EN) अणु
			dev_info(&dd->pdev->dev,
				"Disabling ERO/No-Snoop on bridge device %04x:%04x\n",
					pdev->venकरोr, pdev->device);
			pcie_dev_ctrl &= ~(PCI_EXP_DEVCTL_NOSNOOP_EN |
						PCI_EXP_DEVCTL_RELAX_EN);
			pcie_capability_ग_लिखो_word(pdev, PCI_EXP_DEVCTL,
				pcie_dev_ctrl);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mtip_fix_ero_nosnoop(काष्ठा driver_data *dd, काष्ठा pci_dev *pdev)
अणु
	/*
	 * This workaround is specअगरic to AMD/ATI chipset with a PCI upstream
	 * device with device id 0x5aXX
	 */
	अगर (pdev->bus && pdev->bus->self) अणु
		अगर (pdev->bus->self->venकरोr == PCI_VENDOR_ID_ATI &&
		    ((pdev->bus->self->device & 0xff00) == 0x5a00)) अणु
			mtip_disable_link_opts(dd, pdev->bus->self);
		पूर्ण अन्यथा अणु
			/* Check further up the topology */
			काष्ठा pci_dev *parent_dev = pdev->bus->self;
			अगर (parent_dev->bus &&
				parent_dev->bus->parent &&
				parent_dev->bus->parent->self &&
				parent_dev->bus->parent->self->venकरोr ==
					 PCI_VENDOR_ID_ATI &&
				(parent_dev->bus->parent->self->device &
					0xff00) == 0x5a00) अणु
				mtip_disable_link_opts(dd,
					parent_dev->bus->parent->self);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called क्रम each supported PCI device detected.
 *
 * This function allocates the निजी data काष्ठाure, enables the
 * PCI device and then calls the block layer initialization function.
 *
 * वापस value
 *	0 on success अन्यथा an error code.
 */
अटल पूर्णांक mtip_pci_probe(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rv = 0;
	काष्ठा driver_data *dd = शून्य;
	अक्षर cpu_list[256];
	स्थिर काष्ठा cpumask *node_mask;
	पूर्णांक cpu, i = 0, j = 0;
	पूर्णांक my_node = NUMA_NO_NODE;
	अचिन्हित दीर्घ flags;

	/* Allocate memory क्रम this devices निजी data. */
	my_node = pcibus_to_node(pdev->bus);
	अगर (my_node != NUMA_NO_NODE) अणु
		अगर (!node_online(my_node))
			my_node = mtip_get_next_rr_node();
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "Kernel not reporting proximity, choosing a node\n");
		my_node = mtip_get_next_rr_node();
	पूर्ण
	dev_info(&pdev->dev, "NUMA node %d (closest: %d,%d, probe on %d:%d)\n",
		my_node, pcibus_to_node(pdev->bus), dev_to_node(&pdev->dev),
		cpu_to_node(raw_smp_processor_id()), raw_smp_processor_id());

	dd = kzalloc_node(माप(काष्ठा driver_data), GFP_KERNEL, my_node);
	अगर (dd == शून्य) अणु
		dev_err(&pdev->dev,
			"Unable to allocate memory for driver data\n");
		वापस -ENOMEM;
	पूर्ण

	/* Attach the निजी data to this PCI device.  */
	pci_set_drvdata(pdev, dd);

	rv = pcim_enable_device(pdev);
	अगर (rv < 0) अणु
		dev_err(&pdev->dev, "Unable to enable device\n");
		जाओ iomap_err;
	पूर्ण

	/* Map BAR5 to memory. */
	rv = pcim_iomap_regions(pdev, 1 << MTIP_ABAR, MTIP_DRV_NAME);
	अगर (rv < 0) अणु
		dev_err(&pdev->dev, "Unable to map regions\n");
		जाओ iomap_err;
	पूर्ण

	rv = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rv) अणु
		dev_warn(&pdev->dev, "64-bit DMA enable failed\n");
		जाओ seपंचांगask_err;
	पूर्ण

	/* Copy the info we may need later पूर्णांकo the निजी data काष्ठाure. */
	dd->major	= mtip_major;
	dd->instance	= instance;
	dd->pdev	= pdev;
	dd->numa_node	= my_node;

	INIT_LIST_HEAD(&dd->online_list);
	INIT_LIST_HEAD(&dd->हटाओ_list);

	स_रखो(dd->workq_name, 0, 32);
	snम_लिखो(dd->workq_name, 31, "mtipq%d", dd->instance);

	dd->isr_workq = create_workqueue(dd->workq_name);
	अगर (!dd->isr_workq) अणु
		dev_warn(&pdev->dev, "Can't create wq %d\n", dd->instance);
		rv = -ENOMEM;
		जाओ seपंचांगask_err;
	पूर्ण

	स_रखो(cpu_list, 0, माप(cpu_list));

	node_mask = cpumask_of_node(dd->numa_node);
	अगर (!cpumask_empty(node_mask)) अणु
		क्रम_each_cpu(cpu, node_mask)
		अणु
			snम_लिखो(&cpu_list[j], 256 - j, "%d ", cpu);
			j = म_माप(cpu_list);
		पूर्ण

		dev_info(&pdev->dev, "Node %d on package %d has %d cpu(s): %s\n",
			dd->numa_node,
			topology_physical_package_id(cpumask_first(node_mask)),
			nr_cpus_node(dd->numa_node),
			cpu_list);
	पूर्ण अन्यथा
		dev_dbg(&pdev->dev, "mtip32xx: node_mask empty\n");

	dd->isr_binding = get_least_used_cpu_on_node(dd->numa_node);
	dev_info(&pdev->dev, "Initial IRQ binding node:cpu %d:%d\n",
		cpu_to_node(dd->isr_binding), dd->isr_binding);

	/* first worker context always runs in ISR */
	dd->work[0].cpu_binding = dd->isr_binding;
	dd->work[1].cpu_binding = get_least_used_cpu_on_node(dd->numa_node);
	dd->work[2].cpu_binding = get_least_used_cpu_on_node(dd->numa_node);
	dd->work[3].cpu_binding = dd->work[0].cpu_binding;
	dd->work[4].cpu_binding = dd->work[1].cpu_binding;
	dd->work[5].cpu_binding = dd->work[2].cpu_binding;
	dd->work[6].cpu_binding = dd->work[2].cpu_binding;
	dd->work[7].cpu_binding = dd->work[1].cpu_binding;

	/* Log the bindings */
	क्रम_each_present_cpu(cpu) अणु
		स_रखो(cpu_list, 0, माप(cpu_list));
		क्रम (i = 0, j = 0; i < MTIP_MAX_SLOT_GROUPS; i++) अणु
			अगर (dd->work[i].cpu_binding == cpu) अणु
				snम_लिखो(&cpu_list[j], 256 - j, "%d ", i);
				j = म_माप(cpu_list);
			पूर्ण
		पूर्ण
		अगर (j)
			dev_info(&pdev->dev, "CPU %d: WQs %s\n", cpu, cpu_list);
	पूर्ण

	INIT_WORK(&dd->work[0].work, mtip_workq_sdbf0);
	INIT_WORK(&dd->work[1].work, mtip_workq_sdbf1);
	INIT_WORK(&dd->work[2].work, mtip_workq_sdbf2);
	INIT_WORK(&dd->work[3].work, mtip_workq_sdbf3);
	INIT_WORK(&dd->work[4].work, mtip_workq_sdbf4);
	INIT_WORK(&dd->work[5].work, mtip_workq_sdbf5);
	INIT_WORK(&dd->work[6].work, mtip_workq_sdbf6);
	INIT_WORK(&dd->work[7].work, mtip_workq_sdbf7);

	pci_set_master(pdev);
	rv = pci_enable_msi(pdev);
	अगर (rv) अणु
		dev_warn(&pdev->dev,
			"Unable to enable MSI interrupt.\n");
		जाओ msi_initialize_err;
	पूर्ण

	mtip_fix_ero_nosnoop(dd, pdev);

	/* Initialize the block layer. */
	rv = mtip_block_initialize(dd);
	अगर (rv < 0) अणु
		dev_err(&pdev->dev,
			"Unable to initialize block layer\n");
		जाओ block_initialize_err;
	पूर्ण

	/*
	 * Increment the instance count so that each device has a unique
	 * instance number.
	 */
	instance++;
	अगर (rv != MTIP_FTL_REBUILD_MAGIC)
		set_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag);
	अन्यथा
		rv = 0; /* device in rebuild state, वापस 0 from probe */

	/* Add to online list even अगर in ftl rebuild */
	spin_lock_irqsave(&dev_lock, flags);
	list_add(&dd->online_list, &online_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	जाओ करोne;

block_initialize_err:
	pci_disable_msi(pdev);

msi_initialize_err:
	अगर (dd->isr_workq) अणु
		flush_workqueue(dd->isr_workq);
		destroy_workqueue(dd->isr_workq);
		drop_cpu(dd->work[0].cpu_binding);
		drop_cpu(dd->work[1].cpu_binding);
		drop_cpu(dd->work[2].cpu_binding);
	पूर्ण
seपंचांगask_err:
	pcim_iounmap_regions(pdev, 1 << MTIP_ABAR);

iomap_err:
	kमुक्त(dd);
	pci_set_drvdata(pdev, शून्य);
	वापस rv;
करोne:
	वापस rv;
पूर्ण

/*
 * Called क्रम each probed device when the device is हटाओd or the
 * driver is unloaded.
 *
 * वापस value
 *	None
 */
अटल व्योम mtip_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा driver_data *dd = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags, to;

	set_bit(MTIP_DDF_REMOVAL_BIT, &dd->dd_flag);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->online_list);
	list_add(&dd->हटाओ_list, &removing_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	mtip_check_surprise_removal(pdev);
	synchronize_irq(dd->pdev->irq);

	/* Spin until workers are करोne */
	to = jअगरfies + msecs_to_jअगरfies(4000);
	करो अणु
		msleep(20);
	पूर्ण जबतक (atomic_पढ़ो(&dd->irq_workers_active) != 0 &&
		समय_beक्रमe(jअगरfies, to));

	अगर (atomic_पढ़ो(&dd->irq_workers_active) != 0) अणु
		dev_warn(&dd->pdev->dev,
			"Completion workers still active!\n");
	पूर्ण

	blk_set_queue_dying(dd->queue);
	set_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag);

	/* Clean up the block layer. */
	mtip_block_हटाओ(dd);

	अगर (dd->isr_workq) अणु
		flush_workqueue(dd->isr_workq);
		destroy_workqueue(dd->isr_workq);
		drop_cpu(dd->work[0].cpu_binding);
		drop_cpu(dd->work[1].cpu_binding);
		drop_cpu(dd->work[2].cpu_binding);
	पूर्ण

	pci_disable_msi(pdev);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->हटाओ_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	kमुक्त(dd);

	pcim_iounmap_regions(pdev, 1 << MTIP_ABAR);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/*
 * Called क्रम each probed device when the device is suspended.
 *
 * वापस value
 *	0  Success
 *	<0 Error
 */
अटल पूर्णांक mtip_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	पूर्णांक rv = 0;
	काष्ठा driver_data *dd = pci_get_drvdata(pdev);

	अगर (!dd) अणु
		dev_err(&pdev->dev,
			"Driver private datastructure is NULL\n");
		वापस -EFAULT;
	पूर्ण

	set_bit(MTIP_DDF_RESUME_BIT, &dd->dd_flag);

	/* Disable ports & पूर्णांकerrupts then send standby immediate */
	rv = mtip_block_suspend(dd);
	अगर (rv < 0) अणु
		dev_err(&pdev->dev,
			"Failed to suspend controller\n");
		वापस rv;
	पूर्ण

	/*
	 * Save the pci config space to pdev काष्ठाure &
	 * disable the device
	 */
	pci_save_state(pdev);
	pci_disable_device(pdev);

	/* Move to Low घातer state*/
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस rv;
पूर्ण

/*
 * Called क्रम each probed device when the device is resumed.
 *
 * वापस value
 *      0  Success
 *      <0 Error
 */
अटल पूर्णांक mtip_pci_resume(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rv = 0;
	काष्ठा driver_data *dd;

	dd = pci_get_drvdata(pdev);
	अगर (!dd) अणु
		dev_err(&pdev->dev,
			"Driver private datastructure is NULL\n");
		वापस -EFAULT;
	पूर्ण

	/* Move the device to active State */
	pci_set_घातer_state(pdev, PCI_D0);

	/* Restore PCI configuration space */
	pci_restore_state(pdev);

	/* Enable the PCI device*/
	rv = pcim_enable_device(pdev);
	अगर (rv < 0) अणु
		dev_err(&pdev->dev,
			"Failed to enable card during resume\n");
		जाओ err;
	पूर्ण
	pci_set_master(pdev);

	/*
	 * Calls hbaReset, initPort, & startPort function
	 * then enables पूर्णांकerrupts
	 */
	rv = mtip_block_resume(dd);
	अगर (rv < 0)
		dev_err(&pdev->dev, "Unable to resume\n");

err:
	clear_bit(MTIP_DDF_RESUME_BIT, &dd->dd_flag);

	वापस rv;
पूर्ण

/*
 * Shutकरोwn routine
 *
 * वापस value
 *      None
 */
अटल व्योम mtip_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा driver_data *dd = pci_get_drvdata(pdev);
	अगर (dd)
		mtip_block_shutकरोwn(dd);
पूर्ण

/* Table of device ids supported by this driver. */
अटल स्थिर काष्ठा pci_device_id mtip_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P320H_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P320M_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P320S_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P325M_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P420H_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P420M_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICRON, P425M_DEVICE_ID) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* Structure that describes the PCI driver functions. */
अटल काष्ठा pci_driver mtip_pci_driver = अणु
	.name			= MTIP_DRV_NAME,
	.id_table		= mtip_pci_tbl,
	.probe			= mtip_pci_probe,
	.हटाओ			= mtip_pci_हटाओ,
	.suspend		= mtip_pci_suspend,
	.resume			= mtip_pci_resume,
	.shutकरोwn		= mtip_pci_shutकरोwn,
पूर्ण;

MODULE_DEVICE_TABLE(pci, mtip_pci_tbl);

/*
 * Module initialization function.
 *
 * Called once when the module is loaded. This function allocates a major
 * block device number to the Cyclone devices and रेजिस्टरs the PCI layer
 * of the driver.
 *
 * Return value
 *      0 on success अन्यथा error code.
 */
अटल पूर्णांक __init mtip_init(व्योम)
अणु
	पूर्णांक error;

	pr_info(MTIP_DRV_NAME " Version " MTIP_DRV_VERSION "\n");

	/* Allocate a major block device number to use with this driver. */
	error = रेजिस्टर_blkdev(0, MTIP_DRV_NAME);
	अगर (error <= 0) अणु
		pr_err("Unable to register block device (%d)\n",
		error);
		वापस -EBUSY;
	पूर्ण
	mtip_major = error;

	dfs_parent = debugfs_create_dir("rssd", शून्य);
	अगर (IS_ERR_OR_शून्य(dfs_parent)) अणु
		pr_warn("Error creating debugfs parent\n");
		dfs_parent = शून्य;
	पूर्ण
	अगर (dfs_parent) अणु
		dfs_device_status = debugfs_create_file("device_status",
					0444, dfs_parent, शून्य,
					&mtip_device_status_fops);
		अगर (IS_ERR_OR_शून्य(dfs_device_status)) अणु
			pr_err("Error creating device_status node\n");
			dfs_device_status = शून्य;
		पूर्ण
	पूर्ण

	/* Register our PCI operations. */
	error = pci_रेजिस्टर_driver(&mtip_pci_driver);
	अगर (error) अणु
		debugfs_हटाओ(dfs_parent);
		unरेजिस्टर_blkdev(mtip_major, MTIP_DRV_NAME);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Module de-initialization function.
 *
 * Called once when the module is unloaded. This function deallocates
 * the major block device number allocated by mtip_init() and
 * unरेजिस्टरs the PCI layer of the driver.
 *
 * Return value
 *      none
 */
अटल व्योम __निकास mtip_निकास(व्योम)
अणु
	/* Release the allocated major block device number. */
	unरेजिस्टर_blkdev(mtip_major, MTIP_DRV_NAME);

	/* Unरेजिस्टर the PCI driver. */
	pci_unरेजिस्टर_driver(&mtip_pci_driver);

	debugfs_हटाओ_recursive(dfs_parent);
पूर्ण

MODULE_AUTHOR("Micron Technology, Inc");
MODULE_DESCRIPTION("Micron RealSSD PCIe Block Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(MTIP_DRV_VERSION);

module_init(mtip_init);
module_निकास(mtip_निकास);
