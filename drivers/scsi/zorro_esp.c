<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ESP front-end क्रम Amiga ZORRO SCSI प्रणालीs.
 *
 * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)
 *
 * Copyright (C) 2011,2018 Michael Schmitz (schmitz@debian.org) क्रम
 *               migration to ESP SCSI core
 *
 * Copyright (C) 2013 Tuomas Vainikka (tuomas.vainikka@aalto.fi) क्रम
 *               Blizzard 1230 DMA and probe function fixes
 */
/*
 * ZORRO bus code from:
 */
/*
 * Detection routine क्रम the NCR53c710 based Amiga SCSI Controllers क्रम Linux.
 *		Amiga MacroSystemUS WarpEngine SCSI controller.
 *		Amiga Technologies/DKB A4091 SCSI controller.
 *
 * Written 1997 by Alan Hourihane <alanh@fairlite.demon.co.uk>
 * plus modअगरications of the 53c7xx.c driver to support the Amiga.
 *
 * Rewritten to use 53c700.c by Kars de Jong <jongk@linux-m68k.org>
 */

#घोषणा pr_fmt(fmt)        KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/delay.h>
#समावेश <linux/zorro.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "esp_scsi.h"

MODULE_AUTHOR("Michael Schmitz <schmitz@debian.org>");
MODULE_DESCRIPTION("Amiga Zorro NCR5C9x (ESP) driver");
MODULE_LICENSE("GPL");

/* per-board रेजिस्टर layout definitions */

/* Blizzard 1230 DMA पूर्णांकerface */

काष्ठा blz1230_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर dma_addr;		/* DMA address      [0x0000] */
	अचिन्हित अक्षर dmapad2[0x7fff];
	अचिन्हित अक्षर dma_latch;	/* DMA latch        [0x8000] */
पूर्ण;

/* Blizzard 1230II DMA पूर्णांकerface */

काष्ठा blz1230II_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर dma_addr;		/* DMA address      [0x0000] */
	अचिन्हित अक्षर dmapad2[0xf];
	अचिन्हित अक्षर dma_latch;	/* DMA latch        [0x0010] */
पूर्ण;

/* Blizzard 2060 DMA पूर्णांकerface */

काष्ठा blz2060_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर dma_led_ctrl;	/* DMA led control   [0x000] */
	अचिन्हित अक्षर dmapad1[0x0f];
	अचिन्हित अक्षर dma_addr0;	/* DMA address (MSB) [0x010] */
	अचिन्हित अक्षर dmapad2[0x03];
	अचिन्हित अक्षर dma_addr1;	/* DMA address       [0x014] */
	अचिन्हित अक्षर dmapad3[0x03];
	अचिन्हित अक्षर dma_addr2;	/* DMA address       [0x018] */
	अचिन्हित अक्षर dmapad4[0x03];
	अचिन्हित अक्षर dma_addr3;	/* DMA address (LSB) [0x01c] */
पूर्ण;

/* DMA control bits */
#घोषणा DMA_WRITE 0x80000000

/* Cyberstorm DMA पूर्णांकerface */

काष्ठा cyber_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर dma_addr0;	/* DMA address (MSB) [0x000] */
	अचिन्हित अक्षर dmapad1[1];
	अचिन्हित अक्षर dma_addr1;	/* DMA address       [0x002] */
	अचिन्हित अक्षर dmapad2[1];
	अचिन्हित अक्षर dma_addr2;	/* DMA address       [0x004] */
	अचिन्हित अक्षर dmapad3[1];
	अचिन्हित अक्षर dma_addr3;	/* DMA address (LSB) [0x006] */
	अचिन्हित अक्षर dmapad4[0x3fb];
	अचिन्हित अक्षर cond_reg;		/* DMA cond    (ro)  [0x402] */
#घोषणा ctrl_reg  cond_reg		/* DMA control (wo)  [0x402] */
पूर्ण;

/* DMA control bits */
#घोषणा CYBER_DMA_WRITE  0x40	/* DMA direction. 1 = ग_लिखो */
#घोषणा CYBER_DMA_Z3     0x20	/* 16 (Z2) or 32 (CHIP/Z3) bit DMA transfer */

/* DMA status bits */
#घोषणा CYBER_DMA_HNDL_INTR 0x80	/* DMA IRQ pending? */

/* The CyberStorm II DMA पूर्णांकerface */
काष्ठा cyberII_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर cond_reg;		/* DMA cond    (ro)  [0x000] */
#घोषणा ctrl_reg  cond_reg		/* DMA control (wo)  [0x000] */
	अचिन्हित अक्षर dmapad4[0x3f];
	अचिन्हित अक्षर dma_addr0;	/* DMA address (MSB) [0x040] */
	अचिन्हित अक्षर dmapad1[3];
	अचिन्हित अक्षर dma_addr1;	/* DMA address       [0x044] */
	अचिन्हित अक्षर dmapad2[3];
	अचिन्हित अक्षर dma_addr2;	/* DMA address       [0x048] */
	अचिन्हित अक्षर dmapad3[3];
	अचिन्हित अक्षर dma_addr3;	/* DMA address (LSB) [0x04c] */
पूर्ण;

/* Fastlane DMA पूर्णांकerface */

काष्ठा fastlane_dma_रेजिस्टरs अणु
	अचिन्हित अक्षर cond_reg;		/* DMA status  (ro) [0x0000] */
#घोषणा ctrl_reg  cond_reg		/* DMA control (wo) [0x0000] */
	अक्षर dmapad1[0x3f];
	अचिन्हित अक्षर clear_strobe;	/* DMA clear   (wo) [0x0040] */
पूर्ण;

/*
 * The controller रेजिस्टरs can be found in the Z2 config area at these
 * offsets:
 */
#घोषणा FASTLANE_ESP_ADDR	0x1000001

/* DMA status bits */
#घोषणा FASTLANE_DMA_MINT	0x80
#घोषणा FASTLANE_DMA_IACT	0x40
#घोषणा FASTLANE_DMA_CREQ	0x20

/* DMA control bits */
#घोषणा FASTLANE_DMA_FCODE	0xa0
#घोषणा FASTLANE_DMA_MASK	0xf3
#घोषणा FASTLANE_DMA_WRITE	0x08	/* 1 = ग_लिखो */
#घोषणा FASTLANE_DMA_ENABLE	0x04	/* Enable DMA */
#घोषणा FASTLANE_DMA_EDI	0x02	/* Enable DMA IRQ ? */
#घोषणा FASTLANE_DMA_ESI	0x01	/* Enable SCSI IRQ */

/*
 * निजी data used क्रम driver
 */
काष्ठा zorro_esp_priv अणु
	काष्ठा esp *esp;		/* our ESP instance - क्रम Scsi_host* */
	व्योम __iomem *board_base;	/* भव address (Zorro III board) */
	पूर्णांक zorro3;			/* board is Zorro III */
	अचिन्हित अक्षर ctrl_data;	/* shaकरोw copy of ctrl_reg */
पूर्ण;

/*
 * On all implementations except क्रम the Oktagon, padding between ESP
 * रेजिस्टरs is three bytes.
 * On Oktagon, it is one byte - use a dअगरferent accessor there.
 *
 * Oktagon needs PDMA - currently unsupported!
 */

अटल व्योम zorro_esp_ग_लिखो8(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोb(val, esp->regs + (reg * 4UL));
पूर्ण

अटल u8 zorro_esp_पढ़ो8(काष्ठा esp *esp, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोb(esp->regs + (reg * 4UL));
पूर्ण

अटल पूर्णांक zorro_esp_irq_pending(काष्ठा esp *esp)
अणु
	/* check ESP status रेजिस्टर; DMA has no status reg. */
	अगर (zorro_esp_पढ़ो8(esp, ESP_STATUS) & ESP_STAT_INTR)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cyber_esp_irq_pending(काष्ठा esp *esp)
अणु
	काष्ठा cyber_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	अचिन्हित अक्षर dma_status = पढ़ोb(&dregs->cond_reg);

	/* It's important to check the DMA IRQ bit in the correct way! */
	वापस ((zorro_esp_पढ़ो8(esp, ESP_STATUS) & ESP_STAT_INTR) &&
		(dma_status & CYBER_DMA_HNDL_INTR));
पूर्ण

अटल पूर्णांक fastlane_esp_irq_pending(काष्ठा esp *esp)
अणु
	काष्ठा fastlane_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	अचिन्हित अक्षर dma_status;

	dma_status = पढ़ोb(&dregs->cond_reg);

	अगर (dma_status & FASTLANE_DMA_IACT)
		वापस 0;	/* not our IRQ */

	/* Return non-zero अगर ESP requested IRQ */
	वापस (
	   (dma_status & FASTLANE_DMA_CREQ) &&
	   (!(dma_status & FASTLANE_DMA_MINT)) &&
	   (zorro_esp_पढ़ो8(esp, ESP_STATUS) & ESP_STAT_INTR));
पूर्ण

अटल u32 zorro_esp_dma_length_limit(काष्ठा esp *esp, u32 dma_addr,
					u32 dma_len)
अणु
	वापस dma_len > (1U << 16) ? (1U << 16) : dma_len;
पूर्ण

अटल u32 fastlane_esp_dma_length_limit(काष्ठा esp *esp, u32 dma_addr,
					u32 dma_len)
अणु
	/* The old driver used 0xfffc as limit, so करो that here too */
	वापस dma_len > 0xfffc ? 0xfffc : dma_len;
पूर्ण

अटल व्योम zorro_esp_reset_dma(काष्ठा esp *esp)
अणु
	/* nothing to करो here */
पूर्ण

अटल व्योम zorro_esp_dma_drain(काष्ठा esp *esp)
अणु
	/* nothing to करो here */
पूर्ण

अटल व्योम zorro_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	/* nothing to करो here */
पूर्ण

अटल व्योम fastlane_esp_dma_invalidate(काष्ठा esp *esp)
अणु
	काष्ठा zorro_esp_priv *zep = dev_get_drvdata(esp->dev);
	काष्ठा fastlane_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	अचिन्हित अक्षर *ctrl_data = &zep->ctrl_data;

	*ctrl_data = (*ctrl_data & FASTLANE_DMA_MASK);
	ग_लिखोb(0, &dregs->clear_strobe);
	z_ग_लिखोl(0, zep->board_base);
पूर्ण

/* Blizzard 1230/60 SCSI-IV DMA */

अटल व्योम zorro_esp_send_blz1230_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा blz1230_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;

	/*
	 * Use PIO अगर transferring message bytes to esp->command_block_dma.
	 * PIO requires a भव address, so substitute esp->command_block
	 * क्रम addr.
	 */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	/* Clear the results of a possible prior esp->ops->send_dma_cmd() */
	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	अगर (ग_लिखो)
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
	अन्यथा
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);

	addr >>= 1;
	अगर (ग_लिखो)
		addr &= ~(DMA_WRITE);
	अन्यथा
		addr |= DMA_WRITE;

	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_latch);
	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_addr);
	ग_लिखोb((addr >> 16) & 0xff, &dregs->dma_addr);
	ग_लिखोb((addr >>  8) & 0xff, &dregs->dma_addr);
	ग_लिखोb(addr & 0xff, &dregs->dma_addr);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
पूर्ण

/* Blizzard 1230-II DMA */

अटल व्योम zorro_esp_send_blz1230II_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा blz1230II_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;

	/* Use PIO अगर transferring message bytes to esp->command_block_dma */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	अगर (ग_लिखो)
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
	अन्यथा
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);

	addr >>= 1;
	अगर (ग_लिखो)
		addr &= ~(DMA_WRITE);
	अन्यथा
		addr |= DMA_WRITE;

	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_latch);
	ग_लिखोb((addr >> 16) & 0xff, &dregs->dma_addr);
	ग_लिखोb((addr >>  8) & 0xff, &dregs->dma_addr);
	ग_लिखोb(addr & 0xff, &dregs->dma_addr);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
पूर्ण

/* Blizzard 2060 DMA */

अटल व्योम zorro_esp_send_blz2060_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा blz2060_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;

	/* Use PIO अगर transferring message bytes to esp->command_block_dma */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	अगर (ग_लिखो)
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
	अन्यथा
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);

	addr >>= 1;
	अगर (ग_लिखो)
		addr &= ~(DMA_WRITE);
	अन्यथा
		addr |= DMA_WRITE;

	ग_लिखोb(addr & 0xff, &dregs->dma_addr3);
	ग_लिखोb((addr >>  8) & 0xff, &dregs->dma_addr2);
	ग_लिखोb((addr >> 16) & 0xff, &dregs->dma_addr1);
	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_addr0);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
पूर्ण

/* Cyberstorm I DMA */

अटल व्योम zorro_esp_send_cyber_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा zorro_esp_priv *zep = dev_get_drvdata(esp->dev);
	काष्ठा cyber_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;
	अचिन्हित अक्षर *ctrl_data = &zep->ctrl_data;

	/* Use PIO अगर transferring message bytes to esp->command_block_dma */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	अगर (ग_लिखो) अणु
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
		addr &= ~(1);
	पूर्ण अन्यथा अणु
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);
		addr |= 1;
	पूर्ण

	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_addr0);
	ग_लिखोb((addr >> 16) & 0xff, &dregs->dma_addr1);
	ग_लिखोb((addr >>  8) & 0xff, &dregs->dma_addr2);
	ग_लिखोb(addr & 0xff, &dregs->dma_addr3);

	अगर (ग_लिखो)
		*ctrl_data &= ~(CYBER_DMA_WRITE);
	अन्यथा
		*ctrl_data |= CYBER_DMA_WRITE;

	*ctrl_data &= ~(CYBER_DMA_Z3);	/* Z2, करो 16 bit DMA */

	ग_लिखोb(*ctrl_data, &dregs->ctrl_reg);

	scsi_esp_cmd(esp, cmd);
पूर्ण

/* Cyberstorm II DMA */

अटल व्योम zorro_esp_send_cyberII_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा cyberII_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;

	/* Use PIO अगर transferring message bytes to esp->command_block_dma */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	अगर (ग_लिखो) अणु
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
		addr &= ~(1);
	पूर्ण अन्यथा अणु
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);
		addr |= 1;
	पूर्ण

	ग_लिखोb((addr >> 24) & 0xff, &dregs->dma_addr0);
	ग_लिखोb((addr >> 16) & 0xff, &dregs->dma_addr1);
	ग_लिखोb((addr >>  8) & 0xff, &dregs->dma_addr2);
	ग_लिखोb(addr & 0xff, &dregs->dma_addr3);

	scsi_esp_cmd(esp, cmd);
पूर्ण

/* Fastlane DMA */

अटल व्योम zorro_esp_send_fastlane_dma_cmd(काष्ठा esp *esp, u32 addr,
			u32 esp_count, u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	काष्ठा zorro_esp_priv *zep = dev_get_drvdata(esp->dev);
	काष्ठा fastlane_dma_रेजिस्टरs __iomem *dregs = esp->dma_regs;
	u8 phase = esp->sreg & ESP_STAT_PMASK;
	अचिन्हित अक्षर *ctrl_data = &zep->ctrl_data;

	/* Use PIO अगर transferring message bytes to esp->command_block_dma */
	अगर (phase == ESP_MIP && addr == esp->command_block_dma) अणु
		esp_send_pio_cmd(esp, (u32)esp->command_block, esp_count,
				 dma_count, ग_लिखो, cmd);
		वापस;
	पूर्ण

	esp->send_cmd_error = 0;
	esp->send_cmd_residual = 0;

	zorro_esp_ग_लिखो8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	zorro_esp_ग_लिखो8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	अगर (ग_लिखो) अणु
		/* DMA receive */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_FROM_DEVICE);
		addr &= ~(1);
	पूर्ण अन्यथा अणु
		/* DMA send */
		dma_sync_single_क्रम_device(esp->dev, addr, esp_count,
				DMA_TO_DEVICE);
		addr |= 1;
	पूर्ण

	ग_लिखोb(0, &dregs->clear_strobe);
	z_ग_लिखोl(addr, ((addr & 0x00ffffff) + zep->board_base));

	अगर (ग_लिखो) अणु
		*ctrl_data = (*ctrl_data & FASTLANE_DMA_MASK) |
				FASTLANE_DMA_ENABLE;
	पूर्ण अन्यथा अणु
		*ctrl_data = ((*ctrl_data & FASTLANE_DMA_MASK) |
				FASTLANE_DMA_ENABLE |
				FASTLANE_DMA_WRITE);
	पूर्ण

	ग_लिखोb(*ctrl_data, &dregs->ctrl_reg);

	scsi_esp_cmd(esp, cmd);
पूर्ण

अटल पूर्णांक zorro_esp_dma_error(काष्ठा esp *esp)
अणु
	वापस esp->send_cmd_error;
पूर्ण

/* per-board ESP driver ops */

अटल स्थिर काष्ठा esp_driver_ops blz1230_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= zorro_esp_irq_pending,
	.dma_length_limit	= zorro_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= zorro_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_blz1230_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

अटल स्थिर काष्ठा esp_driver_ops blz1230II_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= zorro_esp_irq_pending,
	.dma_length_limit	= zorro_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= zorro_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_blz1230II_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

अटल स्थिर काष्ठा esp_driver_ops blz2060_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= zorro_esp_irq_pending,
	.dma_length_limit	= zorro_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= zorro_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_blz2060_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

अटल स्थिर काष्ठा esp_driver_ops cyber_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= cyber_esp_irq_pending,
	.dma_length_limit	= zorro_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= zorro_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_cyber_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

अटल स्थिर काष्ठा esp_driver_ops cyberII_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= zorro_esp_irq_pending,
	.dma_length_limit	= zorro_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= zorro_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_cyberII_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

अटल स्थिर काष्ठा esp_driver_ops fastlane_esp_ops = अणु
	.esp_ग_लिखो8		= zorro_esp_ग_लिखो8,
	.esp_पढ़ो8		= zorro_esp_पढ़ो8,
	.irq_pending		= fastlane_esp_irq_pending,
	.dma_length_limit	= fastlane_esp_dma_length_limit,
	.reset_dma		= zorro_esp_reset_dma,
	.dma_drain		= zorro_esp_dma_drain,
	.dma_invalidate		= fastlane_esp_dma_invalidate,
	.send_dma_cmd		= zorro_esp_send_fastlane_dma_cmd,
	.dma_error		= zorro_esp_dma_error,
पूर्ण;

/* Zorro driver config data */

काष्ठा zorro_driver_data अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ dma_offset;
	पूर्णांक असलolute;	/* offset is असलolute address */
	पूर्णांक scsi_option;
	स्थिर काष्ठा esp_driver_ops *esp_ops;
पूर्ण;

/* board types */

क्रमागत अणु
	ZORRO_BLZ1230,
	ZORRO_BLZ1230II,
	ZORRO_BLZ2060,
	ZORRO_CYBER,
	ZORRO_CYBERII,
	ZORRO_FASTLANE,
पूर्ण;

/* per-board config data */

अटल स्थिर काष्ठा zorro_driver_data zorro_esp_boards[] = अणु
	[ZORRO_BLZ1230] = अणु
				.name		= "Blizzard 1230",
				.offset		= 0x8000,
				.dma_offset	= 0x10000,
				.scsi_option	= 1,
				.esp_ops	= &blz1230_esp_ops,
	पूर्ण,
	[ZORRO_BLZ1230II] = अणु
				.name		= "Blizzard 1230II",
				.offset		= 0x10000,
				.dma_offset	= 0x10021,
				.scsi_option	= 1,
				.esp_ops	= &blz1230II_esp_ops,
	पूर्ण,
	[ZORRO_BLZ2060] = अणु
				.name		= "Blizzard 2060",
				.offset		= 0x1ff00,
				.dma_offset	= 0x1ffe0,
				.esp_ops	= &blz2060_esp_ops,
	पूर्ण,
	[ZORRO_CYBER] = अणु
				.name		= "CyberStormI",
				.offset		= 0xf400,
				.dma_offset	= 0xf800,
				.esp_ops	= &cyber_esp_ops,
	पूर्ण,
	[ZORRO_CYBERII] = अणु
				.name		= "CyberStormII",
				.offset		= 0x1ff03,
				.dma_offset	= 0x1ff43,
				.scsi_option	= 1,
				.esp_ops	= &cyberII_esp_ops,
	पूर्ण,
	[ZORRO_FASTLANE] = अणु
				.name		= "Fastlane",
				.offset		= 0x1000001,
				.dma_offset	= 0x1000041,
				.esp_ops	= &fastlane_esp_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा zorro_device_id zorro_esp_zorro_tbl[] = अणु
	अणु	/* Blizzard 1230 IV */
		.id = ZORRO_ID(PHASE5, 0x11, 0),
		.driver_data = ZORRO_BLZ1230,
	पूर्ण,
	अणु	/* Blizzard 1230 II (Zorro II) or Fastlane (Zorro III) */
		.id = ZORRO_ID(PHASE5, 0x0B, 0),
		.driver_data = ZORRO_BLZ1230II,
	पूर्ण,
	अणु	/* Blizzard 2060 */
		.id = ZORRO_ID(PHASE5, 0x18, 0),
		.driver_data = ZORRO_BLZ2060,
	पूर्ण,
	अणु	/* Cyberstorm */
		.id = ZORRO_ID(PHASE5, 0x0C, 0),
		.driver_data = ZORRO_CYBER,
	पूर्ण,
	अणु	/* Cyberstorm II */
		.id = ZORRO_ID(PHASE5, 0x19, 0),
		.driver_data = ZORRO_CYBERII,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, zorro_esp_zorro_tbl);

अटल पूर्णांक zorro_esp_probe(काष्ठा zorro_dev *z,
				       स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा scsi_host_ढाँचा *tpnt = &scsi_esp_ढाँचा;
	काष्ठा Scsi_Host *host;
	काष्ठा esp *esp;
	स्थिर काष्ठा zorro_driver_data *zdd;
	काष्ठा zorro_esp_priv *zep;
	अचिन्हित दीर्घ board, ioaddr, dmaaddr;
	पूर्णांक err;

	board = zorro_resource_start(z);
	zdd = &zorro_esp_boards[ent->driver_data];

	pr_info("%s found at address 0x%lx.\n", zdd->name, board);

	zep = kzalloc(माप(*zep), GFP_KERNEL);
	अगर (!zep) अणु
		pr_err("Can't allocate device private data!\n");
		वापस -ENOMEM;
	पूर्ण

	/* let's figure out whether we have a Zorro II or Zorro III board */
	अगर ((z->rom.er_Type & ERT_TYPEMASK) == ERT_ZORROIII) अणु
		अगर (board > 0xffffff)
			zep->zorro3 = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Even though most of these boards identअगरy as Zorro II,
		 * they are in fact CPU expansion slot boards and have full
		 * access to all of memory. Fix up DMA biपंचांगask here.
		 */
		z->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	पूर्ण

	/*
	 * If Zorro III and ID matches Fastlane, our device table entry
	 * contains data क्रम the Blizzard 1230 II board which करोes share the
	 * same ID. Fix up device table entry here.
	 * TODO: Some Cyberstom060 boards also share this ID but would need
	 * to use the Cyberstorm I driver data ... we catch this by checking
	 * क्रम presence of ESP chip later, but करोn't try to fix up yet.
	 */
	अगर (zep->zorro3 && ent->driver_data == ZORRO_BLZ1230II) अणु
		pr_info("%s at address 0x%lx is Fastlane Z3, fixing data!\n",
			zdd->name, board);
		zdd = &zorro_esp_boards[ZORRO_FASTLANE];
	पूर्ण

	अगर (zdd->असलolute) अणु
		ioaddr  = zdd->offset;
		dmaaddr = zdd->dma_offset;
	पूर्ण अन्यथा अणु
		ioaddr  = board + zdd->offset;
		dmaaddr = board + zdd->dma_offset;
	पूर्ण

	अगर (!zorro_request_device(z, zdd->name)) अणु
		pr_err("cannot reserve region 0x%lx, abort\n",
		       board);
		err = -EBUSY;
		जाओ fail_मुक्त_zep;
	पूर्ण

	host = scsi_host_alloc(tpnt, माप(काष्ठा esp));

	अगर (!host) अणु
		pr_err("No host detected; board configuration problem?\n");
		err = -ENOMEM;
		जाओ fail_release_device;
	पूर्ण

	host->base		= ioaddr;
	host->this_id		= 7;

	esp			= shost_priv(host);
	esp->host		= host;
	esp->dev		= &z->dev;

	esp->scsi_id		= host->this_id;
	esp->scsi_id_mask	= (1 << esp->scsi_id);

	esp->cfreq = 40000000;

	zep->esp = esp;

	dev_set_drvdata(esp->dev, zep);

	/* additional setup required क्रम Fastlane */
	अगर (zep->zorro3 && ent->driver_data == ZORRO_BLZ1230II) अणु
		/* map full address space up to ESP base क्रम DMA */
		zep->board_base = ioremap(board, FASTLANE_ESP_ADDR - 1);
		अगर (!zep->board_base) अणु
			pr_err("Cannot allocate board address space\n");
			err = -ENOMEM;
			जाओ fail_मुक्त_host;
		पूर्ण
		/* initialize DMA control shaकरोw रेजिस्टर */
		zep->ctrl_data = (FASTLANE_DMA_FCODE |
				  FASTLANE_DMA_EDI | FASTLANE_DMA_ESI);
	पूर्ण

	esp->ops = zdd->esp_ops;

	अगर (ioaddr > 0xffffff)
		esp->regs = ioremap(ioaddr, 0x20);
	अन्यथा
		/* ZorroII address space remapped nocache by early startup */
		esp->regs = ZTWO_VADDR(ioaddr);

	अगर (!esp->regs) अणु
		err = -ENOMEM;
		जाओ fail_unmap_fastlane;
	पूर्ण

	esp->fअगरo_reg = esp->regs + ESP_FDATA * 4;

	/* Check whether a Blizzard 12x0 or CyberstormII really has SCSI */
	अगर (zdd->scsi_option) अणु
		zorro_esp_ग_लिखो8(esp, (ESP_CONFIG1_PENABLE | 7), ESP_CFG1);
		अगर (zorro_esp_पढ़ो8(esp, ESP_CFG1) != (ESP_CONFIG1_PENABLE|7)) अणु
			err = -ENODEV;
			जाओ fail_unmap_regs;
		पूर्ण
	पूर्ण

	अगर (zep->zorro3) अणु
		/*
		 * Only Fastlane Z3 क्रम now - add चयन क्रम correct काष्ठा
		 * dma_रेजिस्टरs size अगर adding any more
		 */
		esp->dma_regs = ioremap(dmaaddr,
					माप(काष्ठा fastlane_dma_रेजिस्टरs));
	पूर्ण अन्यथा
		/* ZorroII address space remapped nocache by early startup */
		esp->dma_regs = ZTWO_VADDR(dmaaddr);

	अगर (!esp->dma_regs) अणु
		err = -ENOMEM;
		जाओ fail_unmap_regs;
	पूर्ण

	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);

	अगर (!esp->command_block) अणु
		err = -ENOMEM;
		जाओ fail_unmap_dma_regs;
	पूर्ण

	host->irq = IRQ_AMIGA_PORTS;
	err = request_irq(host->irq, scsi_esp_पूर्णांकr, IRQF_SHARED,
			  "Amiga Zorro ESP", esp);
	अगर (err < 0) अणु
		err = -ENODEV;
		जाओ fail_मुक्त_command_block;
	पूर्ण

	/* रेजिस्टर the chip */
	err = scsi_esp_रेजिस्टर(esp);

	अगर (err) अणु
		err = -ENOMEM;
		जाओ fail_मुक्त_irq;
	पूर्ण

	वापस 0;

fail_मुक्त_irq:
	मुक्त_irq(host->irq, esp);

fail_मुक्त_command_block:
	dma_मुक्त_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

fail_unmap_dma_regs:
	अगर (zep->zorro3)
		iounmap(esp->dma_regs);

fail_unmap_regs:
	अगर (ioaddr > 0xffffff)
		iounmap(esp->regs);

fail_unmap_fastlane:
	अगर (zep->zorro3)
		iounmap(zep->board_base);

fail_मुक्त_host:
	scsi_host_put(host);

fail_release_device:
	zorro_release_device(z);

fail_मुक्त_zep:
	kमुक्त(zep);

	वापस err;
पूर्ण

अटल व्योम zorro_esp_हटाओ(काष्ठा zorro_dev *z)
अणु
	काष्ठा zorro_esp_priv *zep = dev_get_drvdata(&z->dev);
	काष्ठा esp *esp	= zep->esp;
	काष्ठा Scsi_Host *host = esp->host;

	scsi_esp_unरेजिस्टर(esp);

	मुक्त_irq(host->irq, esp);
	dma_मुक्त_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

	अगर (zep->zorro3) अणु
		iounmap(zep->board_base);
		iounmap(esp->dma_regs);
	पूर्ण

	अगर (host->base > 0xffffff)
		iounmap(esp->regs);

	scsi_host_put(host);

	zorro_release_device(z);

	kमुक्त(zep);
पूर्ण

अटल काष्ठा zorro_driver zorro_esp_driver = अणु
	.name	  = KBUILD_MODNAME,
	.id_table = zorro_esp_zorro_tbl,
	.probe	  = zorro_esp_probe,
	.हटाओ	  = zorro_esp_हटाओ,
पूर्ण;

अटल पूर्णांक __init zorro_esp_scsi_init(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&zorro_esp_driver);
पूर्ण

अटल व्योम __निकास zorro_esp_scsi_निकास(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&zorro_esp_driver);
पूर्ण

module_init(zorro_esp_scsi_init);
module_निकास(zorro_esp_scsi_निकास);
