<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AppliedMicro X-Gene SoC SATA Host Controller Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *         Tuan Phan <tphan@apm.com>
 *         Suman Tripathi <stripathi@apm.com>
 *
 * NOTE: PM support is not currently available.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/phy/phy.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "xgene-ahci"

/* Max # of disk per a controller */
#घोषणा MAX_AHCI_CHN_PERCTR		2

/* MUX CSR */
#घोषणा SATA_ENET_CONFIG_REG		0x00000000
#घोषणा  CFG_SATA_ENET_SELECT_MASK	0x00000001

/* SATA core host controller CSR */
#घोषणा SLVRDERRATTRIBUTES		0x00000000
#घोषणा SLVWRERRATTRIBUTES		0x00000004
#घोषणा MSTRDERRATTRIBUTES		0x00000008
#घोषणा MSTWRERRATTRIBUTES		0x0000000c
#घोषणा BUSCTLREG			0x00000014
#घोषणा IOFMSTRWAUX			0x00000018
#घोषणा INTSTATUSMASK			0x0000002c
#घोषणा ERRINTSTATUS			0x00000030
#घोषणा ERRINTSTATUSMASK		0x00000034

/* SATA host AHCI CSR */
#घोषणा PORTCFG				0x000000a4
#घोषणा  PORTADDR_SET(dst, src) \
		(((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))
#घोषणा PORTPHY1CFG		0x000000a8
#घोषणा PORTPHY1CFG_FRCPHYRDY_SET(dst, src) \
		(((dst) & ~0x00100000) | (((u32)(src) << 0x14) & 0x00100000))
#घोषणा PORTPHY2CFG			0x000000ac
#घोषणा PORTPHY3CFG			0x000000b0
#घोषणा PORTPHY4CFG			0x000000b4
#घोषणा PORTPHY5CFG			0x000000b8
#घोषणा SCTL0				0x0000012C
#घोषणा PORTPHY5CFG_RTCHG_SET(dst, src) \
		(((dst) & ~0xfff00000) | (((u32)(src) << 0x14) & 0xfff00000))
#घोषणा PORTAXICFG_EN_CONTEXT_SET(dst, src) \
		(((dst) & ~0x01000000) | (((u32)(src) << 0x18) & 0x01000000))
#घोषणा PORTAXICFG			0x000000bc
#घोषणा PORTAXICFG_OUTTRANS_SET(dst, src) \
		(((dst) & ~0x00f00000) | (((u32)(src) << 0x14) & 0x00f00000))
#घोषणा PORTRANSCFG			0x000000c8
#घोषणा PORTRANSCFG_RXWM_SET(dst, src)		\
		(((dst) & ~0x0000007f) | (((u32)(src)) & 0x0000007f))

/* SATA host controller AXI CSR */
#घोषणा INT_SLV_TMOMASK			0x00000010

/* SATA diagnostic CSR */
#घोषणा CFG_MEM_RAM_SHUTDOWN		0x00000070
#घोषणा BLOCK_MEM_RDY			0x00000074

/* Max retry क्रम link करोwn */
#घोषणा MAX_LINK_DOWN_RETRY 3

क्रमागत xgene_ahci_version अणु
	XGENE_AHCI_V1 = 1,
	XGENE_AHCI_V2,
पूर्ण;

काष्ठा xgene_ahci_context अणु
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा device *dev;
	u8 last_cmd[MAX_AHCI_CHN_PERCTR]; /* tracking the last command issued*/
	u32 class[MAX_AHCI_CHN_PERCTR]; /* tracking the class of device */
	व्योम __iomem *csr_core;		/* Core CSR address of IP */
	व्योम __iomem *csr_diag;		/* Diag CSR address of IP */
	व्योम __iomem *csr_axi;		/* AXI CSR address of IP */
	व्योम __iomem *csr_mux;		/* MUX CSR address of IP */
पूर्ण;

अटल पूर्णांक xgene_ahci_init_memram(काष्ठा xgene_ahci_context *ctx)
अणु
	dev_dbg(ctx->dev, "Release memory from shutdown\n");
	ग_लिखोl(0x0, ctx->csr_diag + CFG_MEM_RAM_SHUTDOWN);
	पढ़ोl(ctx->csr_diag + CFG_MEM_RAM_SHUTDOWN); /* Force a barrier */
	msleep(1);	/* reset may take up to 1ms */
	अगर (पढ़ोl(ctx->csr_diag + BLOCK_MEM_RDY) != 0xFFFFFFFF) अणु
		dev_err(ctx->dev, "failed to release memory from shutdown\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * xgene_ahci_poll_reg_val- Poll a रेजिस्टर on a specअगरic value.
 * @ap : ATA port of पूर्णांकerest.
 * @reg : Register of पूर्णांकerest.
 * @val : Value to be attained.
 * @पूर्णांकerval : रुकोing पूर्णांकerval क्रम polling.
 * @समयout : समयout क्रम achieving the value.
 */
अटल पूर्णांक xgene_ahci_poll_reg_val(काष्ठा ata_port *ap,
				   व्योम __iomem *reg, अचिन्हित
				   पूर्णांक val, अचिन्हित दीर्घ पूर्णांकerval,
				   अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ deadline;
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = ioपढ़ो32(reg);
	deadline = ata_deadline(jअगरfies, समयout);

	जबतक (पंचांगp != val && समय_beक्रमe(jअगरfies, deadline)) अणु
		ata_msleep(ap, पूर्णांकerval);
		पंचांगp = ioपढ़ो32(reg);
	पूर्ण

	वापस पंचांगp;
पूर्ण

/**
 * xgene_ahci_restart_engine - Restart the dma engine.
 * @ap : ATA port of पूर्णांकerest
 *
 * Waits क्रम completion of multiple commands and restarts
 * the DMA engine inside the controller.
 */
अटल पूर्णांक xgene_ahci_restart_engine(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 fbs;

	/*
	 * In हाल of PMP multiple IDENTIFY DEVICE commands can be
	 * issued inside PxCI. So need to poll PxCI क्रम the
	 * completion of outstanding IDENTIFY DEVICE commands beक्रमe
	 * we restart the DMA engine.
	 */
	अगर (xgene_ahci_poll_reg_val(ap, port_mmio +
				    PORT_CMD_ISSUE, 0x0, 1, 100))
		  वापस -EBUSY;

	hpriv->stop_engine(ap);
	ahci_start_fis_rx(ap);

	/*
	 * Enable the PxFBS.FBS_EN bit as it
	 * माला_लो cleared due to stopping the engine.
	 */
	अगर (pp->fbs_supported) अणु
		fbs = पढ़ोl(port_mmio + PORT_FBS);
		ग_लिखोl(fbs | PORT_FBS_EN, port_mmio + PORT_FBS);
		fbs = पढ़ोl(port_mmio + PORT_FBS);
	पूर्ण

	hpriv->start_engine(ap);

	वापस 0;
पूर्ण

/**
 * xgene_ahci_qc_issue - Issue commands to the device
 * @qc: Command to issue
 *
 * Due to Hardware errata क्रम IDENTIFY DEVICE command, the controller cannot
 * clear the BSY bit after receiving the PIO setup FIS. This results in the dma
 * state machine goes पूर्णांकo the CMFatalErrorUpdate state and locks up. By
 * restarting the dma engine, it हटाओs the controller out of lock up state.
 *
 * Due to H/W errata, the controller is unable to save the PMP
 * field fetched from command header beक्रमe sending the H2D FIS.
 * When the device वापसs the PMP port field in the D2H FIS, there is
 * a mismatch and results in command completion failure. The
 * workaround is to ग_लिखो the pmp value to PxFBS.DEV field beक्रमe issuing
 * any command to PMP.
 */
अटल अचिन्हित पूर्णांक xgene_ahci_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा xgene_ahci_context *ctx = hpriv->plat_data;
	पूर्णांक rc = 0;
	u32 port_fbs;
	व्योम *port_mmio = ahci_port_base(ap);

	/*
	 * Write the pmp value to PxFBS.DEV
	 * क्रम हाल of Port Mulitplier.
	 */
	अगर (ctx->class[ap->port_no] == ATA_DEV_PMP) अणु
		port_fbs = पढ़ोl(port_mmio + PORT_FBS);
		port_fbs &= ~PORT_FBS_DEV_MASK;
		port_fbs |= qc->dev->link->pmp << PORT_FBS_DEV_OFFSET;
		ग_लिखोl(port_fbs, port_mmio + PORT_FBS);
	पूर्ण

	अगर (unlikely((ctx->last_cmd[ap->port_no] == ATA_CMD_ID_ATA) ||
	    (ctx->last_cmd[ap->port_no] == ATA_CMD_PACKET) ||
	    (ctx->last_cmd[ap->port_no] == ATA_CMD_SMART)))
		xgene_ahci_restart_engine(ap);

	rc = ahci_qc_issue(qc);

	/* Save the last command issued */
	ctx->last_cmd[ap->port_no] = qc->tf.command;

	वापस rc;
पूर्ण

अटल bool xgene_ahci_is_memram_inited(काष्ठा xgene_ahci_context *ctx)
अणु
	व्योम __iomem *diagcsr = ctx->csr_diag;

	वापस (पढ़ोl(diagcsr + CFG_MEM_RAM_SHUTDOWN) == 0 &&
	        पढ़ोl(diagcsr + BLOCK_MEM_RDY) == 0xFFFFFFFF);
पूर्ण

/**
 * xgene_ahci_पढ़ो_id - Read ID data from the specअगरied device
 * @dev: device
 * @tf: proposed taskfile
 * @id: data buffer
 *
 * This custom पढ़ो ID function is required due to the fact that the HW
 * करोes not support DEVSLP.
 */
अटल अचिन्हित पूर्णांक xgene_ahci_पढ़ो_id(काष्ठा ata_device *dev,
				       काष्ठा ata_taskfile *tf, u16 *id)
अणु
	u32 err_mask;

	err_mask = ata_करो_dev_पढ़ो_id(dev, tf, id);
	अगर (err_mask)
		वापस err_mask;

	/*
	 * Mask reserved area. Word78 spec of Link Power Management
	 * bit15-8: reserved
	 * bit7: NCQ स्वतःsence
	 * bit6: Software settings preservation supported
	 * bit5: reserved
	 * bit4: In-order sata delivery supported
	 * bit3: DIPM requests supported
	 * bit2: DMA Setup FIS Auto-Activate optimization supported
	 * bit1: DMA Setup FIX non-Zero buffer offsets supported
	 * bit0: Reserved
	 *
	 * Clear reserved bit 8 (DEVSLP bit) as we करोn't support DEVSLP
	 */
	id[ATA_ID_FEATURE_SUPP] &= cpu_to_le16(~(1 << 8));

	वापस 0;
पूर्ण

अटल व्योम xgene_ahci_set_phy_cfg(काष्ठा xgene_ahci_context *ctx, पूर्णांक channel)
अणु
	व्योम __iomem *mmio = ctx->hpriv->mmio;
	u32 val;

	dev_dbg(ctx->dev, "port configure mmio 0x%p channel %d\n",
		mmio, channel);
	val = पढ़ोl(mmio + PORTCFG);
	val = PORTADDR_SET(val, channel == 0 ? 2 : 3);
	ग_लिखोl(val, mmio + PORTCFG);
	पढ़ोl(mmio + PORTCFG);  /* Force a barrier */
	/* Disable fix rate */
	ग_लिखोl(0x0001fffe, mmio + PORTPHY1CFG);
	पढ़ोl(mmio + PORTPHY1CFG); /* Force a barrier */
	ग_लिखोl(0x28183219, mmio + PORTPHY2CFG);
	पढ़ोl(mmio + PORTPHY2CFG); /* Force a barrier */
	ग_लिखोl(0x13081008, mmio + PORTPHY3CFG);
	पढ़ोl(mmio + PORTPHY3CFG); /* Force a barrier */
	ग_लिखोl(0x00480815, mmio + PORTPHY4CFG);
	पढ़ोl(mmio + PORTPHY4CFG); /* Force a barrier */
	/* Set winकरोw negotiation */
	val = पढ़ोl(mmio + PORTPHY5CFG);
	val = PORTPHY5CFG_RTCHG_SET(val, 0x300);
	ग_लिखोl(val, mmio + PORTPHY5CFG);
	पढ़ोl(mmio + PORTPHY5CFG); /* Force a barrier */
	val = पढ़ोl(mmio + PORTAXICFG);
	val = PORTAXICFG_EN_CONTEXT_SET(val, 0x1); /* Enable context mgmt */
	val = PORTAXICFG_OUTTRANS_SET(val, 0xe); /* Set outstanding */
	ग_लिखोl(val, mmio + PORTAXICFG);
	पढ़ोl(mmio + PORTAXICFG); /* Force a barrier */
	/* Set the watermark threshold of the receive FIFO */
	val = पढ़ोl(mmio + PORTRANSCFG);
	val = PORTRANSCFG_RXWM_SET(val, 0x30);
	ग_लिखोl(val, mmio + PORTRANSCFG);
पूर्ण

/**
 * xgene_ahci_करो_hardreset - Issue the actual COMRESET
 * @link: link to reset
 * @deadline: deadline jअगरfies क्रम the operation
 * @online: Return value to indicate अगर device online
 *
 * Due to the limitation of the hardware PHY, a dअगरference set of setting is
 * required क्रम each supported disk speed - Gen3 (6.0Gbps), Gen2 (3.0Gbps),
 * and Gen1 (1.5Gbps). Otherwise during दीर्घ IO stress test, the PHY will
 * report disparity error and etc. In addition, during COMRESET, there can
 * be error reported in the रेजिस्टर PORT_SCR_ERR. For SERR_DISPARITY and
 * SERR_10B_8B_ERR, the PHY receiver line must be reseted. Also during दीर्घ
 * reboot cycle regression, someबार the PHY reports link करोwn even अगर the
 * device is present because of speed negotiation failure. so need to retry
 * the COMRESET to get the link up. The following algorithm is followed to
 * proper configure the hardware PHY during COMRESET:
 *
 * Alg Part 1:
 * 1. Start the PHY at Gen3 speed (शेष setting)
 * 2. Issue the COMRESET
 * 3. If no link, go to Alg Part 3
 * 4. If link up, determine अगर the negotiated speed matches the PHY
 *    configured speed
 * 5. If they matched, go to Alg Part 2
 * 6. If they करो not matched and first समय, configure the PHY क्रम the linked
 *    up disk speed and repeat step 2
 * 7. Go to Alg Part 2
 *
 * Alg Part 2:
 * 1. On link up, अगर there are any SERR_DISPARITY and SERR_10B_8B_ERR error
 *    reported in the रेजिस्टर PORT_SCR_ERR, then reset the PHY receiver line
 * 2. Go to Alg Part 4
 *
 * Alg Part 3:
 * 1. Check the PORT_SCR_STAT to see whether device presence detected but PHY
 *    communication establishment failed and maximum link करोwn attempts are
 *    less than Max attempts 3 then जाओ Alg Part 1.
 * 2. Go to Alg Part 4.
 *
 * Alg Part 4:
 * 1. Clear any pending from रेजिस्टर PORT_SCR_ERR.
 *
 * NOTE: For the initial version, we will NOT support Gen1/Gen2. In addition
 *       and until the underlying PHY supports an method to reset the receiver
 *       line, on detection of SERR_DISPARITY or SERR_10B_8B_ERR errors,
 *       an warning message will be prपूर्णांकed.
 */
अटल पूर्णांक xgene_ahci_करो_hardreset(काष्ठा ata_link *link,
				   अचिन्हित दीर्घ deadline, bool *online)
अणु
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा xgene_ahci_context *ctx = hpriv->plat_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ata_taskfile tf;
	पूर्णांक link_करोwn_retry = 0;
	पूर्णांक rc;
	u32 val, sstatus;

	करो अणु
		/* clear D2H reception area to properly रुको क्रम D2H FIS */
		ata_tf_init(link->device, &tf);
		tf.command = ATA_BUSY;
		ata_tf_to_fis(&tf, 0, 0, d2h_fis);
		rc = sata_link_hardreset(link, timing, deadline, online,
				 ahci_check_पढ़ोy);
		अगर (*online) अणु
			val = पढ़ोl(port_mmio + PORT_SCR_ERR);
			अगर (val & (SERR_DISPARITY | SERR_10B_8B_ERR))
				dev_warn(ctx->dev, "link has error\n");
			अवरोध;
		पूर्ण

		sata_scr_पढ़ो(link, SCR_STATUS, &sstatus);
	पूर्ण जबतक (link_करोwn_retry++ < MAX_LINK_DOWN_RETRY &&
		 (sstatus & 0xff) == 0x1);

	/* clear all errors अगर any pending */
	val = पढ़ोl(port_mmio + PORT_SCR_ERR);
	ग_लिखोl(val, port_mmio + PORT_SCR_ERR);

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_ahci_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
        काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	bool online;
	पूर्णांक rc;
	u32 portcmd_saved;
	u32 portclb_saved;
	u32 portclbhi_saved;
	u32 portrxfis_saved;
	u32 portrxfishi_saved;

	/* As hardreset resets these CSR, save it to restore later */
	portcmd_saved = पढ़ोl(port_mmio + PORT_CMD);
	portclb_saved = पढ़ोl(port_mmio + PORT_LST_ADDR);
	portclbhi_saved = पढ़ोl(port_mmio + PORT_LST_ADDR_HI);
	portrxfis_saved = पढ़ोl(port_mmio + PORT_FIS_ADDR);
	portrxfishi_saved = पढ़ोl(port_mmio + PORT_FIS_ADDR_HI);

	hpriv->stop_engine(ap);

	rc = xgene_ahci_करो_hardreset(link, deadline, &online);

	/* As controller hardreset clears them, restore them */
	ग_लिखोl(portcmd_saved, port_mmio + PORT_CMD);
	ग_लिखोl(portclb_saved, port_mmio + PORT_LST_ADDR);
	ग_लिखोl(portclbhi_saved, port_mmio + PORT_LST_ADDR_HI);
	ग_लिखोl(portrxfis_saved, port_mmio + PORT_FIS_ADDR);
	ग_लिखोl(portrxfishi_saved, port_mmio + PORT_FIS_ADDR_HI);

	hpriv->start_engine(ap);

	अगर (online)
		*class = ahci_dev_classअगरy(ap);

	वापस rc;
पूर्ण

अटल व्योम xgene_ahci_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	ahci_platक्रमm_disable_resources(hpriv);
पूर्ण

/**
 * xgene_ahci_pmp_softreset - Issue the softreset to the drives connected
 *                            to Port Multiplier.
 * @link: link to reset
 * @class: Return value to indicate class of device
 * @deadline: deadline jअगरfies क्रम the operation
 *
 * Due to H/W errata, the controller is unable to save the PMP
 * field fetched from command header beक्रमe sending the H2D FIS.
 * When the device वापसs the PMP port field in the D2H FIS, there is
 * a mismatch and results in command completion failure. The workaround
 * is to ग_लिखो the pmp value to PxFBS.DEV field beक्रमe issuing any command
 * to PMP.
 */
अटल पूर्णांक xgene_ahci_pmp_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक pmp = sata_srst_pmp(link);
	काष्ठा ata_port *ap = link->ap;
	u32 rc;
	व्योम *port_mmio = ahci_port_base(ap);
	u32 port_fbs;

	/*
	 * Set PxFBS.DEV field with pmp
	 * value.
	 */
	port_fbs = पढ़ोl(port_mmio + PORT_FBS);
	port_fbs &= ~PORT_FBS_DEV_MASK;
	port_fbs |= pmp << PORT_FBS_DEV_OFFSET;
	ग_लिखोl(port_fbs, port_mmio + PORT_FBS);

	rc = ahci_करो_softreset(link, class, pmp, deadline, ahci_check_पढ़ोy);

	वापस rc;
पूर्ण

/**
 * xgene_ahci_softreset - Issue the softreset to the drive.
 * @link: link to reset
 * @class: Return value to indicate class of device
 * @deadline: deadline jअगरfies क्रम the operation
 *
 * Due to H/W errata, the controller is unable to save the PMP
 * field fetched from command header beक्रमe sending the H2D FIS.
 * When the device वापसs the PMP port field in the D2H FIS, there is
 * a mismatch and results in command completion failure. The workaround
 * is to ग_लिखो the pmp value to PxFBS.DEV field beक्रमe issuing any command
 * to PMP. Here is the algorithm to detect PMP :
 *
 * 1. Save the PxFBS value
 * 2. Program PxFBS.DEV with pmp value send by framework. Framework sends
 *    0xF क्रम both PMP/NON-PMP initially
 * 3. Issue softreset
 * 4. If signature class is PMP जाओ 6
 * 5. restore the original PxFBS and जाओ 3
 * 6. वापस
 */
अटल पूर्णांक xgene_ahci_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक pmp = sata_srst_pmp(link);
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा xgene_ahci_context *ctx = hpriv->plat_data;
	व्योम *port_mmio = ahci_port_base(ap);
	u32 port_fbs;
	u32 port_fbs_save;
	u32 retry = 1;
	u32 rc;

	port_fbs_save = पढ़ोl(port_mmio + PORT_FBS);

	/*
	 * Set PxFBS.DEV field with pmp
	 * value.
	 */
	port_fbs = पढ़ोl(port_mmio + PORT_FBS);
	port_fbs &= ~PORT_FBS_DEV_MASK;
	port_fbs |= pmp << PORT_FBS_DEV_OFFSET;
	ग_लिखोl(port_fbs, port_mmio + PORT_FBS);

softreset_retry:
	rc = ahci_करो_softreset(link, class, pmp,
			       deadline, ahci_check_पढ़ोy);

	ctx->class[ap->port_no] = *class;
	अगर (*class != ATA_DEV_PMP) अणु
		/*
		 * Retry क्रम normal drives without
		 * setting PxFBS.DEV field with pmp value.
		 */
		अगर (retry--) अणु
			ग_लिखोl(port_fbs_save, port_mmio + PORT_FBS);
			जाओ softreset_retry;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * xgene_ahci_handle_broken_edge_irq - Handle the broken irq.
 * @host: Host that recieved the irq
 * @irq_masked: HOST_IRQ_STAT value
 *
 * For hardware with broken edge trigger latch
 * the HOST_IRQ_STAT रेजिस्टर misses the edge पूर्णांकerrupt
 * when clearing of HOST_IRQ_STAT रेजिस्टर and hardware
 * reporting the PORT_IRQ_STAT रेजिस्टर at the
 * same घड़ी cycle.
 * As such, the algorithm below outlines the workaround.
 *
 * 1. Read HOST_IRQ_STAT रेजिस्टर and save the state.
 * 2. Clear the HOST_IRQ_STAT रेजिस्टर.
 * 3. Read back the HOST_IRQ_STAT रेजिस्टर.
 * 4. If HOST_IRQ_STAT रेजिस्टर equals to zero, then
 *    traverse the rest of port's PORT_IRQ_STAT रेजिस्टर
 *    to check अगर an पूर्णांकerrupt is triggered at that poपूर्णांक अन्यथा
 *    go to step 6.
 * 5. If PORT_IRQ_STAT रेजिस्टर of rest ports is not equal to zero
 *    then update the state of HOST_IRQ_STAT saved in step 1.
 * 6. Handle port पूर्णांकerrupts.
 * 7. Exit
 */
अटल पूर्णांक xgene_ahci_handle_broken_edge_irq(काष्ठा ata_host *host,
					     u32 irq_masked)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *port_mmio;
	पूर्णांक i;

	अगर (!पढ़ोl(hpriv->mmio + HOST_IRQ_STAT)) अणु
		क्रम (i = 0; i < host->n_ports; i++) अणु
			अगर (irq_masked & (1 << i))
				जारी;

			port_mmio = ahci_port_base(host->ports[i]);
			अगर (पढ़ोl(port_mmio + PORT_IRQ_STAT))
				irq_masked |= (1 << i);
		पूर्ण
	पूर्ण

	वापस ahci_handle_port_पूर्णांकr(host, irq_masked);
पूर्ण

अटल irqवापस_t xgene_ahci_irq_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा ahci_host_priv *hpriv;
	अचिन्हित पूर्णांक rc = 0;
	व्योम __iomem *mmio;
	u32 irq_stat, irq_masked;

	VPRINTK("ENTER\n");

	hpriv = host->निजी_data;
	mmio = hpriv->mmio;

	/* sigh.  0xffffffff is a valid वापस from h/w */
	irq_stat = पढ़ोl(mmio + HOST_IRQ_STAT);
	अगर (!irq_stat)
		वापस IRQ_NONE;

	irq_masked = irq_stat & hpriv->port_map;

	spin_lock(&host->lock);

	/*
	 * HOST_IRQ_STAT behaves as edge triggered latch meaning that
	 * it should be cleared beक्रमe all the port events are cleared.
	 */
	ग_लिखोl(irq_stat, mmio + HOST_IRQ_STAT);

	rc = xgene_ahci_handle_broken_edge_irq(host, irq_masked);

	spin_unlock(&host->lock);

	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(rc);
पूर्ण

अटल काष्ठा ata_port_operations xgene_ahci_v1_ops = अणु
	.inherits = &ahci_ops,
	.host_stop = xgene_ahci_host_stop,
	.hardreset = xgene_ahci_hardreset,
	.पढ़ो_id = xgene_ahci_पढ़ो_id,
	.qc_issue = xgene_ahci_qc_issue,
	.softreset = xgene_ahci_softreset,
	.pmp_softreset = xgene_ahci_pmp_softreset
पूर्ण;

अटल स्थिर काष्ठा ata_port_info xgene_ahci_v1_port_info = अणु
	.flags = AHCI_FLAG_COMMON | ATA_FLAG_PMP,
	.pio_mask = ATA_PIO4,
	.udma_mask = ATA_UDMA6,
	.port_ops = &xgene_ahci_v1_ops,
पूर्ण;

अटल काष्ठा ata_port_operations xgene_ahci_v2_ops = अणु
	.inherits = &ahci_ops,
	.host_stop = xgene_ahci_host_stop,
	.hardreset = xgene_ahci_hardreset,
	.पढ़ो_id = xgene_ahci_पढ़ो_id,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info xgene_ahci_v2_port_info = अणु
	.flags = AHCI_FLAG_COMMON | ATA_FLAG_PMP,
	.pio_mask = ATA_PIO4,
	.udma_mask = ATA_UDMA6,
	.port_ops = &xgene_ahci_v2_ops,
पूर्ण;

अटल पूर्णांक xgene_ahci_hw_init(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा xgene_ahci_context *ctx = hpriv->plat_data;
	पूर्णांक i;
	पूर्णांक rc;
	u32 val;

	/* Remove IP RAM out of shutकरोwn */
	rc = xgene_ahci_init_memram(ctx);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < MAX_AHCI_CHN_PERCTR; i++)
		xgene_ahci_set_phy_cfg(ctx, i);

	/* AXI disable Mask */
	ग_लिखोl(0xffffffff, hpriv->mmio + HOST_IRQ_STAT);
	पढ़ोl(hpriv->mmio + HOST_IRQ_STAT); /* Force a barrier */
	ग_लिखोl(0, ctx->csr_core + INTSTATUSMASK);
	val = पढ़ोl(ctx->csr_core + INTSTATUSMASK); /* Force a barrier */
	dev_dbg(ctx->dev, "top level interrupt mask 0x%X value 0x%08X\n",
		INTSTATUSMASK, val);

	ग_लिखोl(0x0, ctx->csr_core + ERRINTSTATUSMASK);
	पढ़ोl(ctx->csr_core + ERRINTSTATUSMASK); /* Force a barrier */
	ग_लिखोl(0x0, ctx->csr_axi + INT_SLV_TMOMASK);
	पढ़ोl(ctx->csr_axi + INT_SLV_TMOMASK);

	/* Enable AXI Interrupt */
	ग_लिखोl(0xffffffff, ctx->csr_core + SLVRDERRATTRIBUTES);
	ग_लिखोl(0xffffffff, ctx->csr_core + SLVWRERRATTRIBUTES);
	ग_लिखोl(0xffffffff, ctx->csr_core + MSTRDERRATTRIBUTES);
	ग_लिखोl(0xffffffff, ctx->csr_core + MSTWRERRATTRIBUTES);

	/* Enable coherency */
	val = पढ़ोl(ctx->csr_core + BUSCTLREG);
	val &= ~0x00000002;     /* Enable ग_लिखो coherency */
	val &= ~0x00000001;     /* Enable पढ़ो coherency */
	ग_लिखोl(val, ctx->csr_core + BUSCTLREG);

	val = पढ़ोl(ctx->csr_core + IOFMSTRWAUX);
	val |= (1 << 3);        /* Enable पढ़ो coherency */
	val |= (1 << 9);        /* Enable ग_लिखो coherency */
	ग_लिखोl(val, ctx->csr_core + IOFMSTRWAUX);
	val = पढ़ोl(ctx->csr_core + IOFMSTRWAUX);
	dev_dbg(ctx->dev, "coherency 0x%X value 0x%08X\n",
		IOFMSTRWAUX, val);

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_ahci_mux_select(काष्ठा xgene_ahci_context *ctx)
अणु
	u32 val;

	/* Check क्रम optional MUX resource */
	अगर (!ctx->csr_mux)
		वापस 0;

	val = पढ़ोl(ctx->csr_mux + SATA_ENET_CONFIG_REG);
	val &= ~CFG_SATA_ENET_SELECT_MASK;
	ग_लिखोl(val, ctx->csr_mux + SATA_ENET_CONFIG_REG);
	val = पढ़ोl(ctx->csr_mux + SATA_ENET_CONFIG_REG);
	वापस val & CFG_SATA_ENET_SELECT_MASK ? -1 : 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_ahci_acpi_match[] = अणु
	अणु "APMC0D0D", XGENE_AHCI_V1पूर्ण,
	अणु "APMC0D32", XGENE_AHCI_V2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_ahci_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id xgene_ahci_of_match[] = अणु
	अणु.compatible = "apm,xgene-ahci", .data = (व्योम *) XGENE_AHCI_V1पूर्ण,
	अणु.compatible = "apm,xgene-ahci-v2", .data = (व्योम *) XGENE_AHCI_V2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_ahci_of_match);

अटल पूर्णांक xgene_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा xgene_ahci_context *ctx;
	काष्ठा resource *res;
	स्थिर काष्ठा of_device_id *of_devid;
	क्रमागत xgene_ahci_version version = XGENE_AHCI_V1;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &xgene_ahci_v1_port_info,
					      &xgene_ahci_v2_port_info पूर्ण;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	hpriv->plat_data = ctx;
	ctx->hpriv = hpriv;
	ctx->dev = dev;

	/* Retrieve the IP core resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	ctx->csr_core = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->csr_core))
		वापस PTR_ERR(ctx->csr_core);

	/* Retrieve the IP diagnostic resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	ctx->csr_diag = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->csr_diag))
		वापस PTR_ERR(ctx->csr_diag);

	/* Retrieve the IP AXI resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
	ctx->csr_axi = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->csr_axi))
		वापस PTR_ERR(ctx->csr_axi);

	/* Retrieve the optional IP mux resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 4);
	अगर (res) अणु
		व्योम __iomem *csr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(csr))
			वापस PTR_ERR(csr);

		ctx->csr_mux = csr;
	पूर्ण

	of_devid = of_match_device(xgene_ahci_of_match, dev);
	अगर (of_devid) अणु
		अगर (of_devid->data)
			version = (क्रमागत xgene_ahci_version) of_devid->data;
	पूर्ण
#अगर_घोषित CONFIG_ACPI
	अन्यथा अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;
		काष्ठा acpi_device_info *info;
		acpi_status status;

		acpi_id = acpi_match_device(xgene_ahci_acpi_match, &pdev->dev);
		अगर (!acpi_id) अणु
			dev_warn(&pdev->dev, "No node entry in ACPI table. Assume version1\n");
			version = XGENE_AHCI_V1;
		पूर्ण अन्यथा अगर (acpi_id->driver_data) अणु
			version = (क्रमागत xgene_ahci_version) acpi_id->driver_data;
			status = acpi_get_object_info(ACPI_HANDLE(&pdev->dev), &info);
			अगर (ACPI_FAILURE(status)) अणु
				dev_warn(&pdev->dev, "%s: Error reading device info. Assume version1\n",
					__func__);
				version = XGENE_AHCI_V1;
			पूर्ण अन्यथा अणु
				अगर (info->valid & ACPI_VALID_CID)
					version = XGENE_AHCI_V2;
				kमुक्त(info);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	dev_dbg(dev, "VAddr 0x%p Mmio VAddr 0x%p\n", ctx->csr_core,
		hpriv->mmio);

	/* Select ATA */
	अगर ((rc = xgene_ahci_mux_select(ctx))) अणु
		dev_err(dev, "SATA mux selection failed error %d\n", rc);
		वापस -ENODEV;
	पूर्ण

	अगर (xgene_ahci_is_memram_inited(ctx)) अणु
		dev_info(dev, "skip clock and PHY initialization\n");
		जाओ skip_clk_phy;
	पूर्ण

	/* Due to errata, HW requires full toggle transition */
	rc = ahci_platक्रमm_enable_clks(hpriv);
	अगर (rc)
		जाओ disable_resources;
	ahci_platक्रमm_disable_clks(hpriv);

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		जाओ disable_resources;

	/* Configure the host controller */
	xgene_ahci_hw_init(hpriv);
skip_clk_phy:

	चयन (version) अणु
	हाल XGENE_AHCI_V1:
		hpriv->flags = AHCI_HFLAG_NO_NCQ;
		अवरोध;
	हाल XGENE_AHCI_V2:
		hpriv->flags |= AHCI_HFLAG_YES_FBS;
		hpriv->irq_handler = xgene_ahci_irq_पूर्णांकr;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rc = ahci_platक्रमm_init_host(pdev, hpriv, ppi[version - 1],
				     &ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	dev_dbg(dev, "X-Gene SATA host controller initialized\n");
	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver xgene_ahci_driver = अणु
	.probe = xgene_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = xgene_ahci_of_match,
		.acpi_match_table = ACPI_PTR(xgene_ahci_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xgene_ahci_driver);

MODULE_DESCRIPTION("APM X-Gene AHCI SATA driver");
MODULE_AUTHOR("Loc Ho <lho@apm.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.4");
