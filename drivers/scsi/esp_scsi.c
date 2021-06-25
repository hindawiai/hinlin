<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* esp_scsi.c: ESP SCSI driver.
 *
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/irqवापस.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "esp_scsi.h"

#घोषणा DRV_MODULE_NAME		"esp"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_VERSION		"2.000"
#घोषणा DRV_MODULE_RELDATE	"April 19, 2007"

/* SCSI bus reset settle समय in seconds.  */
अटल पूर्णांक esp_bus_reset_settle = 3;

अटल u32 esp_debug;
#घोषणा ESP_DEBUG_INTR		0x00000001
#घोषणा ESP_DEBUG_SCSICMD	0x00000002
#घोषणा ESP_DEBUG_RESET		0x00000004
#घोषणा ESP_DEBUG_MSGIN		0x00000008
#घोषणा ESP_DEBUG_MSGOUT	0x00000010
#घोषणा ESP_DEBUG_CMDDONE	0x00000020
#घोषणा ESP_DEBUG_DISCONNECT	0x00000040
#घोषणा ESP_DEBUG_DATASTART	0x00000080
#घोषणा ESP_DEBUG_DATADONE	0x00000100
#घोषणा ESP_DEBUG_RECONNECT	0x00000200
#घोषणा ESP_DEBUG_AUTOSENSE	0x00000400
#घोषणा ESP_DEBUG_EVENT		0x00000800
#घोषणा ESP_DEBUG_COMMAND	0x00001000

#घोषणा esp_log_पूर्णांकr(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_INTR) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_reset(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_RESET) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_msgin(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_MSGIN) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_msgout(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_MSGOUT) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_cmdकरोne(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_CMDDONE) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_disconnect(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_DISCONNECT) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_datastart(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_DATASTART) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_dataकरोne(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_DATADONE) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_reconnect(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_RECONNECT) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_स्वतःsense(f, a...) \
करो अणु	अगर (esp_debug & ESP_DEBUG_AUTOSENSE) \
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_event(f, a...) \
करो अणु   अगर (esp_debug & ESP_DEBUG_EVENT)	\
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_log_command(f, a...) \
करो अणु   अगर (esp_debug & ESP_DEBUG_COMMAND)	\
		shost_prपूर्णांकk(KERN_DEBUG, esp->host, f, ## a);	\
पूर्ण जबतक (0)

#घोषणा esp_पढ़ो8(REG)		esp->ops->esp_पढ़ो8(esp, REG)
#घोषणा esp_ग_लिखो8(VAL,REG)	esp->ops->esp_ग_लिखो8(esp, VAL, REG)

अटल व्योम esp_log_fill_regs(काष्ठा esp *esp,
			      काष्ठा esp_event_ent *p)
अणु
	p->sreg = esp->sreg;
	p->seqreg = esp->seqreg;
	p->sreg2 = esp->sreg2;
	p->ireg = esp->ireg;
	p->select_state = esp->select_state;
	p->event = esp->event;
पूर्ण

व्योम scsi_esp_cmd(काष्ठा esp *esp, u8 val)
अणु
	काष्ठा esp_event_ent *p;
	पूर्णांक idx = esp->esp_event_cur;

	p = &esp->esp_event_log[idx];
	p->type = ESP_EVENT_TYPE_CMD;
	p->val = val;
	esp_log_fill_regs(esp, p);

	esp->esp_event_cur = (idx + 1) & (ESP_EVENT_LOG_SZ - 1);

	esp_log_command("cmd[%02x]\n", val);
	esp_ग_लिखो8(val, ESP_CMD);
पूर्ण
EXPORT_SYMBOL(scsi_esp_cmd);

अटल व्योम esp_send_dma_cmd(काष्ठा esp *esp, पूर्णांक len, पूर्णांक max_len, पूर्णांक cmd)
अणु
	अगर (esp->flags & ESP_FLAG_USE_FIFO) अणु
		पूर्णांक i;

		scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		क्रम (i = 0; i < len; i++)
			esp_ग_लिखो8(esp->command_block[i], ESP_FDATA);
		scsi_esp_cmd(esp, cmd);
	पूर्ण अन्यथा अणु
		अगर (esp->rev == FASHME)
			scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		cmd |= ESP_CMD_DMA;
		esp->ops->send_dma_cmd(esp, esp->command_block_dma,
				       len, max_len, 0, cmd);
	पूर्ण
पूर्ण

अटल व्योम esp_event(काष्ठा esp *esp, u8 val)
अणु
	काष्ठा esp_event_ent *p;
	पूर्णांक idx = esp->esp_event_cur;

	p = &esp->esp_event_log[idx];
	p->type = ESP_EVENT_TYPE_EVENT;
	p->val = val;
	esp_log_fill_regs(esp, p);

	esp->esp_event_cur = (idx + 1) & (ESP_EVENT_LOG_SZ - 1);

	esp->event = val;
पूर्ण

अटल व्योम esp_dump_cmd_log(काष्ठा esp *esp)
अणु
	पूर्णांक idx = esp->esp_event_cur;
	पूर्णांक stop = idx;

	shost_prपूर्णांकk(KERN_INFO, esp->host, "Dumping command log\n");
	करो अणु
		काष्ठा esp_event_ent *p = &esp->esp_event_log[idx];

		shost_prपूर्णांकk(KERN_INFO, esp->host,
			     "ent[%d] %s val[%02x] sreg[%02x] seqreg[%02x] "
			     "sreg2[%02x] ireg[%02x] ss[%02x] event[%02x]\n",
			     idx,
			     p->type == ESP_EVENT_TYPE_CMD ? "CMD" : "EVENT",
			     p->val, p->sreg, p->seqreg,
			     p->sreg2, p->ireg, p->select_state, p->event);

		idx = (idx + 1) & (ESP_EVENT_LOG_SZ - 1);
	पूर्ण जबतक (idx != stop);
पूर्ण

अटल व्योम esp_flush_fअगरo(काष्ठा esp *esp)
अणु
	scsi_esp_cmd(esp, ESP_CMD_FLUSH);
	अगर (esp->rev == ESP236) अणु
		पूर्णांक lim = 1000;

		जबतक (esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES) अणु
			अगर (--lim == 0) अणु
				shost_prपूर्णांकk(KERN_ALERT, esp->host,
					     "ESP_FF_BYTES will not clear!\n");
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hme_पढ़ो_fअगरo(काष्ठा esp *esp)
अणु
	पूर्णांक fcnt = esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES;
	पूर्णांक idx = 0;

	जबतक (fcnt--) अणु
		esp->fअगरo[idx++] = esp_पढ़ो8(ESP_FDATA);
		esp->fअगरo[idx++] = esp_पढ़ो8(ESP_FDATA);
	पूर्ण
	अगर (esp->sreg2 & ESP_STAT2_F1BYTE) अणु
		esp_ग_लिखो8(0, ESP_FDATA);
		esp->fअगरo[idx++] = esp_पढ़ो8(ESP_FDATA);
		scsi_esp_cmd(esp, ESP_CMD_FLUSH);
	पूर्ण
	esp->fअगरo_cnt = idx;
पूर्ण

अटल व्योम esp_set_all_config3(काष्ठा esp *esp, u8 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ESP_MAX_TARGET; i++)
		esp->target[i].esp_config3 = val;
पूर्ण

/* Reset the ESP chip, _not_ the SCSI bus. */
अटल व्योम esp_reset_esp(काष्ठा esp *esp)
अणु
	/* Now reset the ESP chip */
	scsi_esp_cmd(esp, ESP_CMD_RC);
	scsi_esp_cmd(esp, ESP_CMD_शून्य | ESP_CMD_DMA);
	अगर (esp->rev == FAST)
		esp_ग_लिखो8(ESP_CONFIG2_FENAB, ESP_CFG2);
	scsi_esp_cmd(esp, ESP_CMD_शून्य | ESP_CMD_DMA);

	/* This is the only poपूर्णांक at which it is reliable to पढ़ो
	 * the ID-code क्रम a fast ESP chip variants.
	 */
	esp->max_period = ((35 * esp->ccycle) / 1000);
	अगर (esp->rev == FAST) अणु
		u8 family_code = ESP_FAMILY(esp_पढ़ो8(ESP_UID));

		अगर (family_code == ESP_UID_F236) अणु
			esp->rev = FAS236;
		पूर्ण अन्यथा अगर (family_code == ESP_UID_HME) अणु
			esp->rev = FASHME; /* Version is usually '5'. */
		पूर्ण अन्यथा अगर (family_code == ESP_UID_FSC) अणु
			esp->rev = FSC;
			/* Enable Active Negation */
			esp_ग_लिखो8(ESP_CONFIG4_RADE, ESP_CFG4);
		पूर्ण अन्यथा अणु
			esp->rev = FAS100A;
		पूर्ण
		esp->min_period = ((4 * esp->ccycle) / 1000);
	पूर्ण अन्यथा अणु
		esp->min_period = ((5 * esp->ccycle) / 1000);
	पूर्ण
	अगर (esp->rev == FAS236) अणु
		/*
		 * The AM53c974 chip वापसs the same ID as FAS236;
		 * try to configure glitch eater.
		 */
		u8 config4 = ESP_CONFIG4_GE1;
		esp_ग_लिखो8(config4, ESP_CFG4);
		config4 = esp_पढ़ो8(ESP_CFG4);
		अगर (config4 & ESP_CONFIG4_GE1) अणु
			esp->rev = PCSCSI;
			esp_ग_लिखो8(esp->config4, ESP_CFG4);
		पूर्ण
	पूर्ण
	esp->max_period = (esp->max_period + 3)>>2;
	esp->min_period = (esp->min_period + 3)>>2;

	esp_ग_लिखो8(esp->config1, ESP_CFG1);
	चयन (esp->rev) अणु
	हाल ESP100:
		/* nothing to करो */
		अवरोध;

	हाल ESP100A:
		esp_ग_लिखो8(esp->config2, ESP_CFG2);
		अवरोध;

	हाल ESP236:
		/* Slow 236 */
		esp_ग_लिखो8(esp->config2, ESP_CFG2);
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);
		अवरोध;

	हाल FASHME:
		esp->config2 |= (ESP_CONFIG2_HME32 | ESP_CONFIG2_HMEFENAB);
		fallthrough;

	हाल FAS236:
	हाल PCSCSI:
	हाल FSC:
		esp_ग_लिखो8(esp->config2, ESP_CFG2);
		अगर (esp->rev == FASHME) अणु
			u8 cfg3 = esp->target[0].esp_config3;

			cfg3 |= ESP_CONFIG3_FCLOCK | ESP_CONFIG3_OBPUSH;
			अगर (esp->scsi_id >= 8)
				cfg3 |= ESP_CONFIG3_IDBIT3;
			esp_set_all_config3(esp, cfg3);
		पूर्ण अन्यथा अणु
			u32 cfg3 = esp->target[0].esp_config3;

			cfg3 |= ESP_CONFIG3_FCLK;
			esp_set_all_config3(esp, cfg3);
		पूर्ण
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);
		अगर (esp->rev == FASHME) अणु
			esp->radelay = 80;
		पूर्ण अन्यथा अणु
			अगर (esp->flags & ESP_FLAG_DIFFERENTIAL)
				esp->radelay = 0;
			अन्यथा
				esp->radelay = 96;
		पूर्ण
		अवरोध;

	हाल FAS100A:
		/* Fast 100a */
		esp_ग_लिखो8(esp->config2, ESP_CFG2);
		esp_set_all_config3(esp,
				    (esp->target[0].esp_config3 |
				     ESP_CONFIG3_FCLOCK));
		esp->prev_cfg3 = esp->target[0].esp_config3;
		esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);
		esp->radelay = 32;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Reload the configuration रेजिस्टरs */
	esp_ग_लिखो8(esp->cfact, ESP_CFACT);

	esp->prev_stp = 0;
	esp_ग_लिखो8(esp->prev_stp, ESP_STP);

	esp->prev_soff = 0;
	esp_ग_लिखो8(esp->prev_soff, ESP_SOFF);

	esp_ग_लिखो8(esp->neg_defp, ESP_TIMEO);

	/* Eat any bitrot in the chip */
	esp_पढ़ो8(ESP_INTRPT);
	udelay(100);
पूर्ण

अटल व्योम esp_map_dma(काष्ठा esp *esp, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);
	काष्ठा scatterlist *sg = scsi_sglist(cmd);
	पूर्णांक total = 0, i;
	काष्ठा scatterlist *s;

	अगर (cmd->sc_data_direction == DMA_NONE)
		वापस;

	अगर (esp->flags & ESP_FLAG_NO_DMA_MAP) अणु
		/*
		 * For pseuकरो DMA and PIO we need the भव address instead of
		 * a dma address, so perक्रमm an identity mapping.
		 */
		spriv->num_sg = scsi_sg_count(cmd);

		scsi_क्रम_each_sg(cmd, s, spriv->num_sg, i) अणु
			s->dma_address = (uपूर्णांकptr_t)sg_virt(s);
			total += sg_dma_len(s);
		पूर्ण
	पूर्ण अन्यथा अणु
		spriv->num_sg = scsi_dma_map(cmd);
		scsi_क्रम_each_sg(cmd, s, spriv->num_sg, i)
			total += sg_dma_len(s);
	पूर्ण
	spriv->cur_residue = sg_dma_len(sg);
	spriv->prv_sg = शून्य;
	spriv->cur_sg = sg;
	spriv->tot_residue = total;
पूर्ण

अटल dma_addr_t esp_cur_dma_addr(काष्ठा esp_cmd_entry *ent,
				   काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp_cmd_priv *p = ESP_CMD_PRIV(cmd);

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		वापस ent->sense_dma +
			(ent->sense_ptr - cmd->sense_buffer);
	पूर्ण

	वापस sg_dma_address(p->cur_sg) +
		(sg_dma_len(p->cur_sg) -
		 p->cur_residue);
पूर्ण

अटल अचिन्हित पूर्णांक esp_cur_dma_len(काष्ठा esp_cmd_entry *ent,
				    काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp_cmd_priv *p = ESP_CMD_PRIV(cmd);

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		वापस SCSI_SENSE_BUFFERSIZE -
			(ent->sense_ptr - cmd->sense_buffer);
	पूर्ण
	वापस p->cur_residue;
पूर्ण

अटल व्योम esp_advance_dma(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent,
			    काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक len)
अणु
	काष्ठा esp_cmd_priv *p = ESP_CMD_PRIV(cmd);

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		ent->sense_ptr += len;
		वापस;
	पूर्ण

	p->cur_residue -= len;
	p->tot_residue -= len;
	अगर (p->cur_residue < 0 || p->tot_residue < 0) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Data transfer overflow.\n");
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "cur_residue[%d] tot_residue[%d] len[%u]\n",
			     p->cur_residue, p->tot_residue, len);
		p->cur_residue = 0;
		p->tot_residue = 0;
	पूर्ण
	अगर (!p->cur_residue && p->tot_residue) अणु
		p->prv_sg = p->cur_sg;
		p->cur_sg = sg_next(p->cur_sg);
		p->cur_residue = sg_dma_len(p->cur_sg);
	पूर्ण
पूर्ण

अटल व्योम esp_unmap_dma(काष्ठा esp *esp, काष्ठा scsi_cmnd *cmd)
अणु
	अगर (!(esp->flags & ESP_FLAG_NO_DMA_MAP))
		scsi_dma_unmap(cmd);
पूर्ण

अटल व्योम esp_save_poपूर्णांकers(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	काष्ठा scsi_cmnd *cmd = ent->cmd;
	काष्ठा esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		ent->saved_sense_ptr = ent->sense_ptr;
		वापस;
	पूर्ण
	ent->saved_cur_residue = spriv->cur_residue;
	ent->saved_prv_sg = spriv->prv_sg;
	ent->saved_cur_sg = spriv->cur_sg;
	ent->saved_tot_residue = spriv->tot_residue;
पूर्ण

अटल व्योम esp_restore_poपूर्णांकers(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	काष्ठा scsi_cmnd *cmd = ent->cmd;
	काष्ठा esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		ent->sense_ptr = ent->saved_sense_ptr;
		वापस;
	पूर्ण
	spriv->cur_residue = ent->saved_cur_residue;
	spriv->prv_sg = ent->saved_prv_sg;
	spriv->cur_sg = ent->saved_cur_sg;
	spriv->tot_residue = ent->saved_tot_residue;
पूर्ण

अटल व्योम esp_ग_लिखो_tgt_config3(काष्ठा esp *esp, पूर्णांक tgt)
अणु
	अगर (esp->rev > ESP100A) अणु
		u8 val = esp->target[tgt].esp_config3;

		अगर (val != esp->prev_cfg3) अणु
			esp->prev_cfg3 = val;
			esp_ग_लिखो8(val, ESP_CFG3);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esp_ग_लिखो_tgt_sync(काष्ठा esp *esp, पूर्णांक tgt)
अणु
	u8 off = esp->target[tgt].esp_offset;
	u8 per = esp->target[tgt].esp_period;

	अगर (off != esp->prev_soff) अणु
		esp->prev_soff = off;
		esp_ग_लिखो8(off, ESP_SOFF);
	पूर्ण
	अगर (per != esp->prev_stp) अणु
		esp->prev_stp = per;
		esp_ग_लिखो8(per, ESP_STP);
	पूर्ण
पूर्ण

अटल u32 esp_dma_length_limit(काष्ठा esp *esp, u32 dma_addr, u32 dma_len)
अणु
	अगर (esp->rev == FASHME) अणु
		/* Arbitrary segment boundaries, 24-bit counts.  */
		अगर (dma_len > (1U << 24))
			dma_len = (1U << 24);
	पूर्ण अन्यथा अणु
		u32 base, end;

		/* ESP chip limits other variants by 16-bits of transfer
		 * count.  Actually on FAS100A and FAS236 we could get
		 * 24-bits of transfer count by enabling ESP_CONFIG2_FENAB
		 * in the ESP_CFG2 रेजिस्टर but that causes other unwanted
		 * changes so we करोn't use it currently.
		 */
		अगर (dma_len > (1U << 16))
			dma_len = (1U << 16);

		/* All of the DMA variants hooked up to these chips
		 * cannot handle crossing a 24-bit address boundary.
		 */
		base = dma_addr & ((1U << 24) - 1U);
		end = base + dma_len;
		अगर (end > (1U << 24))
			end = (1U <<24);
		dma_len = end - base;
	पूर्ण
	वापस dma_len;
पूर्ण

अटल पूर्णांक esp_need_to_nego_wide(काष्ठा esp_target_data *tp)
अणु
	काष्ठा scsi_target *target = tp->starget;

	वापस spi_width(target) != tp->nego_goal_width;
पूर्ण

अटल पूर्णांक esp_need_to_nego_sync(काष्ठा esp_target_data *tp)
अणु
	काष्ठा scsi_target *target = tp->starget;

	/* When offset is zero, period is "don't care".  */
	अगर (!spi_offset(target) && !tp->nego_goal_offset)
		वापस 0;

	अगर (spi_offset(target) == tp->nego_goal_offset &&
	    spi_period(target) == tp->nego_goal_period)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक esp_alloc_lun_tag(काष्ठा esp_cmd_entry *ent,
			     काष्ठा esp_lun_data *lp)
अणु
	अगर (!ent->orig_tag[0]) अणु
		/* Non-tagged, slot alपढ़ोy taken?  */
		अगर (lp->non_tagged_cmd)
			वापस -EBUSY;

		अगर (lp->hold) अणु
			/* We are being held by active tagged
			 * commands.
			 */
			अगर (lp->num_tagged)
				वापस -EBUSY;

			/* Tagged commands completed, we can unplug
			 * the queue and run this untagged command.
			 */
			lp->hold = 0;
		पूर्ण अन्यथा अगर (lp->num_tagged) अणु
			/* Plug the queue until num_tagged decreases
			 * to zero in esp_मुक्त_lun_tag.
			 */
			lp->hold = 1;
			वापस -EBUSY;
		पूर्ण

		lp->non_tagged_cmd = ent;
		वापस 0;
	पूर्ण

	/* Tagged command. Check that it isn't blocked by a non-tagged one. */
	अगर (lp->non_tagged_cmd || lp->hold)
		वापस -EBUSY;

	BUG_ON(lp->tagged_cmds[ent->orig_tag[1]]);

	lp->tagged_cmds[ent->orig_tag[1]] = ent;
	lp->num_tagged++;

	वापस 0;
पूर्ण

अटल व्योम esp_मुक्त_lun_tag(काष्ठा esp_cmd_entry *ent,
			     काष्ठा esp_lun_data *lp)
अणु
	अगर (ent->orig_tag[0]) अणु
		BUG_ON(lp->tagged_cmds[ent->orig_tag[1]] != ent);
		lp->tagged_cmds[ent->orig_tag[1]] = शून्य;
		lp->num_tagged--;
	पूर्ण अन्यथा अणु
		BUG_ON(lp->non_tagged_cmd != ent);
		lp->non_tagged_cmd = शून्य;
	पूर्ण
पूर्ण

अटल व्योम esp_map_sense(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	ent->sense_ptr = ent->cmd->sense_buffer;
	अगर (esp->flags & ESP_FLAG_NO_DMA_MAP) अणु
		ent->sense_dma = (uपूर्णांकptr_t)ent->sense_ptr;
		वापस;
	पूर्ण

	ent->sense_dma = dma_map_single(esp->dev, ent->sense_ptr,
					SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम esp_unmap_sense(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	अगर (!(esp->flags & ESP_FLAG_NO_DMA_MAP))
		dma_unmap_single(esp->dev, ent->sense_dma,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	ent->sense_ptr = शून्य;
पूर्ण

/* When a contingent allegiance condition is created, we क्रमce feed a
 * REQUEST_SENSE command to the device to fetch the sense data.  I
 * tried many other schemes, relying on the scsi error handling layer
 * to send out the REQUEST_SENSE स्वतःmatically, but this was dअगरficult
 * to get right especially in the presence of applications like smartd
 * which use SG_IO to send out their own REQUEST_SENSE commands.
 */
अटल व्योम esp_स्वतःsense(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	काष्ठा scsi_cmnd *cmd = ent->cmd;
	काष्ठा scsi_device *dev = cmd->device;
	पूर्णांक tgt, lun;
	u8 *p, val;

	tgt = dev->id;
	lun = dev->lun;


	अगर (!ent->sense_ptr) अणु
		esp_log_स्वतःsense("Doing auto-sense for tgt[%d] lun[%d]\n",
				  tgt, lun);
		esp_map_sense(esp, ent);
	पूर्ण
	ent->saved_sense_ptr = ent->sense_ptr;

	esp->active_cmd = ent;

	p = esp->command_block;
	esp->msg_out_len = 0;

	*p++ = IDENTIFY(0, lun);
	*p++ = REQUEST_SENSE;
	*p++ = ((dev->scsi_level <= SCSI_2) ?
		(lun << 5) : 0);
	*p++ = 0;
	*p++ = 0;
	*p++ = SCSI_SENSE_BUFFERSIZE;
	*p++ = 0;

	esp->select_state = ESP_SELECT_BASIC;

	val = tgt;
	अगर (esp->rev == FASHME)
		val |= ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT;
	esp_ग_लिखो8(val, ESP_BUSID);

	esp_ग_लिखो_tgt_sync(esp, tgt);
	esp_ग_लिखो_tgt_config3(esp, tgt);

	val = (p - esp->command_block);

	esp_send_dma_cmd(esp, val, 16, ESP_CMD_SELA);
पूर्ण

अटल काष्ठा esp_cmd_entry *find_and_prep_issuable_command(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent;

	list_क्रम_each_entry(ent, &esp->queued_cmds, list) अणु
		काष्ठा scsi_cmnd *cmd = ent->cmd;
		काष्ठा scsi_device *dev = cmd->device;
		काष्ठा esp_lun_data *lp = dev->hostdata;

		अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
			ent->tag[0] = 0;
			ent->tag[1] = 0;
			वापस ent;
		पूर्ण

		अगर (!spi_populate_tag_msg(&ent->tag[0], cmd)) अणु
			ent->tag[0] = 0;
			ent->tag[1] = 0;
		पूर्ण
		ent->orig_tag[0] = ent->tag[0];
		ent->orig_tag[1] = ent->tag[1];

		अगर (esp_alloc_lun_tag(ent, lp) < 0)
			जारी;

		वापस ent;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम esp_maybe_execute_command(काष्ठा esp *esp)
अणु
	काष्ठा esp_target_data *tp;
	काष्ठा scsi_device *dev;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा esp_cmd_entry *ent;
	bool select_and_stop = false;
	पूर्णांक tgt, lun, i;
	u32 val, start_cmd;
	u8 *p;

	अगर (esp->active_cmd ||
	    (esp->flags & ESP_FLAG_RESETTING))
		वापस;

	ent = find_and_prep_issuable_command(esp);
	अगर (!ent)
		वापस;

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		esp_स्वतःsense(esp, ent);
		वापस;
	पूर्ण

	cmd = ent->cmd;
	dev = cmd->device;
	tgt = dev->id;
	lun = dev->lun;
	tp = &esp->target[tgt];

	list_move(&ent->list, &esp->active_cmds);

	esp->active_cmd = ent;

	esp_map_dma(esp, cmd);
	esp_save_poपूर्णांकers(esp, ent);

	अगर (!(cmd->cmd_len == 6 || cmd->cmd_len == 10 || cmd->cmd_len == 12))
		select_and_stop = true;

	p = esp->command_block;

	esp->msg_out_len = 0;
	अगर (tp->flags & ESP_TGT_CHECK_NEGO) अणु
		/* Need to negotiate.  If the target is broken
		 * go क्रम synchronous transfers and non-wide.
		 */
		अगर (tp->flags & ESP_TGT_BROKEN) अणु
			tp->flags &= ~ESP_TGT_DISCONNECT;
			tp->nego_goal_period = 0;
			tp->nego_goal_offset = 0;
			tp->nego_goal_width = 0;
			tp->nego_goal_tags = 0;
		पूर्ण

		/* If the settings are not changing, skip this.  */
		अगर (spi_width(tp->starget) == tp->nego_goal_width &&
		    spi_period(tp->starget) == tp->nego_goal_period &&
		    spi_offset(tp->starget) == tp->nego_goal_offset) अणु
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
			जाओ build_identअगरy;
		पूर्ण

		अगर (esp->rev == FASHME && esp_need_to_nego_wide(tp)) अणु
			esp->msg_out_len =
				spi_populate_width_msg(&esp->msg_out[0],
						       (tp->nego_goal_width ?
							1 : 0));
			tp->flags |= ESP_TGT_NEGO_WIDE;
		पूर्ण अन्यथा अगर (esp_need_to_nego_sync(tp)) अणु
			esp->msg_out_len =
				spi_populate_sync_msg(&esp->msg_out[0],
						      tp->nego_goal_period,
						      tp->nego_goal_offset);
			tp->flags |= ESP_TGT_NEGO_SYNC;
		पूर्ण अन्यथा अणु
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
		पूर्ण

		/* If there are multiple message bytes, use Select and Stop */
		अगर (esp->msg_out_len)
			select_and_stop = true;
	पूर्ण

build_identअगरy:
	*p++ = IDENTIFY(tp->flags & ESP_TGT_DISCONNECT, lun);

	अगर (ent->tag[0] && esp->rev == ESP100) अणु
		/* ESP100 lacks select w/atn3 command, use select
		 * and stop instead.
		 */
		select_and_stop = true;
	पूर्ण

	अगर (select_and_stop) अणु
		esp->cmd_bytes_left = cmd->cmd_len;
		esp->cmd_bytes_ptr = &cmd->cmnd[0];

		अगर (ent->tag[0]) अणु
			क्रम (i = esp->msg_out_len - 1;
			     i >= 0; i--)
				esp->msg_out[i + 2] = esp->msg_out[i];
			esp->msg_out[0] = ent->tag[0];
			esp->msg_out[1] = ent->tag[1];
			esp->msg_out_len += 2;
		पूर्ण

		start_cmd = ESP_CMD_SELAS;
		esp->select_state = ESP_SELECT_MSGOUT;
	पूर्ण अन्यथा अणु
		start_cmd = ESP_CMD_SELA;
		अगर (ent->tag[0]) अणु
			*p++ = ent->tag[0];
			*p++ = ent->tag[1];

			start_cmd = ESP_CMD_SA3;
		पूर्ण

		क्रम (i = 0; i < cmd->cmd_len; i++)
			*p++ = cmd->cmnd[i];

		esp->select_state = ESP_SELECT_BASIC;
	पूर्ण
	val = tgt;
	अगर (esp->rev == FASHME)
		val |= ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT;
	esp_ग_लिखो8(val, ESP_BUSID);

	esp_ग_लिखो_tgt_sync(esp, tgt);
	esp_ग_लिखो_tgt_config3(esp, tgt);

	val = (p - esp->command_block);

	अगर (esp_debug & ESP_DEBUG_SCSICMD) अणु
		prपूर्णांकk("ESP: tgt[%d] lun[%d] scsi_cmd [ ", tgt, lun);
		क्रम (i = 0; i < cmd->cmd_len; i++)
			prपूर्णांकk("%02x ", cmd->cmnd[i]);
		prपूर्णांकk("]\n");
	पूर्ण

	esp_send_dma_cmd(esp, val, 16, start_cmd);
पूर्ण

अटल काष्ठा esp_cmd_entry *esp_get_ent(काष्ठा esp *esp)
अणु
	काष्ठा list_head *head = &esp->esp_cmd_pool;
	काष्ठा esp_cmd_entry *ret;

	अगर (list_empty(head)) अणु
		ret = kzalloc(माप(काष्ठा esp_cmd_entry), GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		ret = list_entry(head->next, काष्ठा esp_cmd_entry, list);
		list_del(&ret->list);
		स_रखो(ret, 0, माप(*ret));
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम esp_put_ent(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	list_add(&ent->list, &esp->esp_cmd_pool);
पूर्ण

अटल व्योम esp_cmd_is_करोne(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent,
			    काष्ठा scsi_cmnd *cmd, अचिन्हित अक्षर host_byte)
अणु
	काष्ठा scsi_device *dev = cmd->device;
	पूर्णांक tgt = dev->id;
	पूर्णांक lun = dev->lun;

	esp->active_cmd = शून्य;
	esp_unmap_dma(esp, cmd);
	esp_मुक्त_lun_tag(ent, dev->hostdata);
	cmd->result = 0;
	set_host_byte(cmd, host_byte);
	अगर (host_byte == DID_OK)
		set_status_byte(cmd, ent->status);

	अगर (ent->eh_करोne) अणु
		complete(ent->eh_करोne);
		ent->eh_करोne = शून्य;
	पूर्ण

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE) अणु
		esp_unmap_sense(esp, ent);

		/* Restore the message/status bytes to what we actually
		 * saw originally.  Also, report that we are providing
		 * the sense data.
		 */
		cmd->result = ((DRIVER_SENSE << 24) |
			       (DID_OK << 16) |
			       (SAM_STAT_CHECK_CONDITION << 0));

		ent->flags &= ~ESP_CMD_FLAG_AUTOSENSE;
		अगर (esp_debug & ESP_DEBUG_AUTOSENSE) अणु
			पूर्णांक i;

			prपूर्णांकk("esp%d: tgt[%d] lun[%d] AUTO SENSE[ ",
			       esp->host->unique_id, tgt, lun);
			क्रम (i = 0; i < 18; i++)
				prपूर्णांकk("%02x ", cmd->sense_buffer[i]);
			prपूर्णांकk("]\n");
		पूर्ण
	पूर्ण

	cmd->scsi_करोne(cmd);

	list_del(&ent->list);
	esp_put_ent(esp, ent);

	esp_maybe_execute_command(esp);
पूर्ण

अटल व्योम esp_event_queue_full(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	काष्ठा scsi_device *dev = ent->cmd->device;
	काष्ठा esp_lun_data *lp = dev->hostdata;

	scsi_track_queue_full(dev, lp->num_tagged - 1);
पूर्ण

अटल पूर्णांक esp_queuecommand_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा scsi_device *dev = cmd->device;
	काष्ठा esp *esp = shost_priv(dev->host);
	काष्ठा esp_cmd_priv *spriv;
	काष्ठा esp_cmd_entry *ent;

	ent = esp_get_ent(esp);
	अगर (!ent)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	ent->cmd = cmd;

	cmd->scsi_करोne = करोne;

	spriv = ESP_CMD_PRIV(cmd);
	spriv->num_sg = 0;

	list_add_tail(&ent->list, &esp->queued_cmds);

	esp_maybe_execute_command(esp);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(esp_queuecommand)

अटल पूर्णांक esp_check_gross_error(काष्ठा esp *esp)
अणु
	अगर (esp->sreg & ESP_STAT_SPAM) अणु
		/* Gross Error, could be one of:
		 * - top of fअगरo overwritten
		 * - top of command रेजिस्टर overwritten
		 * - DMA programmed with wrong direction
		 * - improper phase change
		 */
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Gross error sreg[%02x]\n", esp->sreg);
		/* XXX Reset the chip. XXX */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक esp_check_spur_पूर्णांकr(काष्ठा esp *esp)
अणु
	चयन (esp->rev) अणु
	हाल ESP100:
	हाल ESP100A:
		/* The पूर्णांकerrupt pending bit of the status रेजिस्टर cannot
		 * be trusted on these revisions.
		 */
		esp->sreg &= ~ESP_STAT_INTR;
		अवरोध;

	शेष:
		अगर (!(esp->sreg & ESP_STAT_INTR)) अणु
			अगर (esp->ireg & ESP_INTR_SR)
				वापस 1;

			/* If the DMA is indicating पूर्णांकerrupt pending and the
			 * ESP is not, the only possibility is a DMA error.
			 */
			अगर (!esp->ops->dma_error(esp)) अणु
				shost_prपूर्णांकk(KERN_ERR, esp->host,
					     "Spurious irq, sreg=%02x.\n",
					     esp->sreg);
				वापस -1;
			पूर्ण

			shost_prपूर्णांकk(KERN_ERR, esp->host, "DMA error\n");

			/* XXX Reset the chip. XXX */
			वापस -1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम esp_schedule_reset(काष्ठा esp *esp)
अणु
	esp_log_reset("esp_schedule_reset() from %ps\n",
		      __builtin_वापस_address(0));
	esp->flags |= ESP_FLAG_RESETTING;
	esp_event(esp, ESP_EVENT_RESET);
पूर्ण

/* In order to aव्योम having to add a special half-reconnected state
 * पूर्णांकo the driver we just sit here and poll through the rest of
 * the reselection process to get the tag message bytes.
 */
अटल काष्ठा esp_cmd_entry *esp_reconnect_with_tag(काष्ठा esp *esp,
						    काष्ठा esp_lun_data *lp)
अणु
	काष्ठा esp_cmd_entry *ent;
	पूर्णांक i;

	अगर (!lp->num_tagged) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect w/num_tagged==0\n");
		वापस शून्य;
	पूर्ण

	esp_log_reconnect("reconnect tag, ");

	क्रम (i = 0; i < ESP_QUICKIRQ_LIMIT; i++) अणु
		अगर (esp->ops->irq_pending(esp))
			अवरोध;
	पूर्ण
	अगर (i == ESP_QUICKIRQ_LIMIT) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect IRQ1 timeout\n");
		वापस शून्य;
	पूर्ण

	esp->sreg = esp_पढ़ो8(ESP_STATUS);
	esp->ireg = esp_पढ़ो8(ESP_INTRPT);

	esp_log_reconnect("IRQ(%d:%x:%x), ",
			  i, esp->ireg, esp->sreg);

	अगर (esp->ireg & ESP_INTR_DC) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect, got disconnect.\n");
		वापस शून्य;
	पूर्ण

	अगर ((esp->sreg & ESP_STAT_PMASK) != ESP_MIP) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect, not MIP sreg[%02x].\n", esp->sreg);
		वापस शून्य;
	पूर्ण

	/* DMA in the tag bytes... */
	esp->command_block[0] = 0xff;
	esp->command_block[1] = 0xff;
	esp->ops->send_dma_cmd(esp, esp->command_block_dma,
			       2, 2, 1, ESP_CMD_DMA | ESP_CMD_TI);

	/* ACK the message.  */
	scsi_esp_cmd(esp, ESP_CMD_MOK);

	क्रम (i = 0; i < ESP_RESELECT_TAG_LIMIT; i++) अणु
		अगर (esp->ops->irq_pending(esp)) अणु
			esp->sreg = esp_पढ़ो8(ESP_STATUS);
			esp->ireg = esp_पढ़ो8(ESP_INTRPT);
			अगर (esp->ireg & ESP_INTR_FDONE)
				अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (i == ESP_RESELECT_TAG_LIMIT) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host, "Reconnect IRQ2 timeout\n");
		वापस शून्य;
	पूर्ण
	esp->ops->dma_drain(esp);
	esp->ops->dma_invalidate(esp);

	esp_log_reconnect("IRQ2(%d:%x:%x) tag[%x:%x]\n",
			  i, esp->ireg, esp->sreg,
			  esp->command_block[0],
			  esp->command_block[1]);

	अगर (esp->command_block[0] < SIMPLE_QUEUE_TAG ||
	    esp->command_block[0] > ORDERED_QUEUE_TAG) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect, bad tag type %02x.\n",
			     esp->command_block[0]);
		वापस शून्य;
	पूर्ण

	ent = lp->tagged_cmds[esp->command_block[1]];
	अगर (!ent) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect, no entry for tag %02x.\n",
			     esp->command_block[1]);
		वापस शून्य;
	पूर्ण

	वापस ent;
पूर्ण

अटल पूर्णांक esp_reconnect(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent;
	काष्ठा esp_target_data *tp;
	काष्ठा esp_lun_data *lp;
	काष्ठा scsi_device *dev;
	पूर्णांक target, lun;

	BUG_ON(esp->active_cmd);
	अगर (esp->rev == FASHME) अणु
		/* FASHME माला_दो the target and lun numbers directly
		 * पूर्णांकo the fअगरo.
		 */
		target = esp->fअगरo[0];
		lun = esp->fअगरo[1] & 0x7;
	पूर्ण अन्यथा अणु
		u8 bits = esp_पढ़ो8(ESP_FDATA);

		/* Older chips put the lun directly पूर्णांकo the fअगरo, but
		 * the target is given as a sample of the arbitration
		 * lines on the bus at reselection समय.  So we should
		 * see the ID of the ESP and the one reconnecting target
		 * set in the biपंचांगap.
		 */
		अगर (!(bits & esp->scsi_id_mask))
			जाओ करो_reset;
		bits &= ~esp->scsi_id_mask;
		अगर (!bits || (bits & (bits - 1)))
			जाओ करो_reset;

		target = ffs(bits) - 1;
		lun = (esp_पढ़ो8(ESP_FDATA) & 0x7);

		scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		अगर (esp->rev == ESP100) अणु
			u8 ireg = esp_पढ़ो8(ESP_INTRPT);
			/* This chip has a bug during reselection that can
			 * cause a spurious illegal-command पूर्णांकerrupt, which
			 * we simply ACK here.  Another possibility is a bus
			 * reset so we must check क्रम that.
			 */
			अगर (ireg & ESP_INTR_SR)
				जाओ करो_reset;
		पूर्ण
		scsi_esp_cmd(esp, ESP_CMD_शून्य);
	पूर्ण

	esp_ग_लिखो_tgt_sync(esp, target);
	esp_ग_लिखो_tgt_config3(esp, target);

	scsi_esp_cmd(esp, ESP_CMD_MOK);

	अगर (esp->rev == FASHME)
		esp_ग_लिखो8(target | ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT,
			   ESP_BUSID);

	tp = &esp->target[target];
	dev = __scsi_device_lookup_by_target(tp->starget, lun);
	अगर (!dev) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Reconnect, no lp tgt[%u] lun[%u]\n",
			     target, lun);
		जाओ करो_reset;
	पूर्ण
	lp = dev->hostdata;

	ent = lp->non_tagged_cmd;
	अगर (!ent) अणु
		ent = esp_reconnect_with_tag(esp, lp);
		अगर (!ent)
			जाओ करो_reset;
	पूर्ण

	esp->active_cmd = ent;

	esp_event(esp, ESP_EVENT_CHECK_PHASE);
	esp_restore_poपूर्णांकers(esp, ent);
	esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
	वापस 1;

करो_reset:
	esp_schedule_reset(esp);
	वापस 0;
पूर्ण

अटल पूर्णांक esp_finish_select(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent;
	काष्ठा scsi_cmnd *cmd;

	/* No दीर्घer selecting.  */
	esp->select_state = ESP_SELECT_NONE;

	esp->seqreg = esp_पढ़ो8(ESP_SSTEP) & ESP_STEP_VBITS;
	ent = esp->active_cmd;
	cmd = ent->cmd;

	अगर (esp->ops->dma_error(esp)) अणु
		/* If we see a DMA error during or as a result of selection,
		 * all bets are off.
		 */
		esp_schedule_reset(esp);
		esp_cmd_is_करोne(esp, ent, cmd, DID_ERROR);
		वापस 0;
	पूर्ण

	esp->ops->dma_invalidate(esp);

	अगर (esp->ireg == (ESP_INTR_RSEL | ESP_INTR_FDONE)) अणु
		काष्ठा esp_target_data *tp = &esp->target[cmd->device->id];

		/* Carefully back out of the selection attempt.  Release
		 * resources (such as DMA mapping & TAG) and reset state (such
		 * as message out and command delivery variables).
		 */
		अगर (!(ent->flags & ESP_CMD_FLAG_AUTOSENSE)) अणु
			esp_unmap_dma(esp, cmd);
			esp_मुक्त_lun_tag(ent, cmd->device->hostdata);
			tp->flags &= ~(ESP_TGT_NEGO_SYNC | ESP_TGT_NEGO_WIDE);
			esp->cmd_bytes_ptr = शून्य;
			esp->cmd_bytes_left = 0;
		पूर्ण अन्यथा अणु
			esp_unmap_sense(esp, ent);
		पूर्ण

		/* Now that the state is unwound properly, put back onto
		 * the issue queue.  This command is no दीर्घer active.
		 */
		list_move(&ent->list, &esp->queued_cmds);
		esp->active_cmd = शून्य;

		/* Return value ignored by caller, it directly invokes
		 * esp_reconnect().
		 */
		वापस 0;
	पूर्ण

	अगर (esp->ireg == ESP_INTR_DC) अणु
		काष्ठा scsi_device *dev = cmd->device;

		/* Disconnect.  Make sure we re-negotiate sync and
		 * wide parameters अगर this target starts responding
		 * again in the future.
		 */
		esp->target[dev->id].flags |= ESP_TGT_CHECK_NEGO;

		scsi_esp_cmd(esp, ESP_CMD_ESEL);
		esp_cmd_is_करोne(esp, ent, cmd, DID_BAD_TARGET);
		वापस 1;
	पूर्ण

	अगर (esp->ireg == (ESP_INTR_FDONE | ESP_INTR_BSERV)) अणु
		/* Selection successful.  On pre-FAST chips we have
		 * to करो a NOP and possibly clean out the FIFO.
		 */
		अगर (esp->rev <= ESP236) अणु
			पूर्णांक fcnt = esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES;

			scsi_esp_cmd(esp, ESP_CMD_शून्य);

			अगर (!fcnt &&
			    (!esp->prev_soff ||
			     ((esp->sreg & ESP_STAT_PMASK) != ESP_DIP)))
				esp_flush_fअगरo(esp);
		पूर्ण

		/* If we are करोing a Select And Stop command, negotiation, etc.
		 * we'll करो the right thing as we transition to the next phase.
		 */
		esp_event(esp, ESP_EVENT_CHECK_PHASE);
		वापस 0;
	पूर्ण

	shost_prपूर्णांकk(KERN_INFO, esp->host,
		     "Unexpected selection completion ireg[%x]\n", esp->ireg);
	esp_schedule_reset(esp);
	वापस 0;
पूर्ण

अटल पूर्णांक esp_data_bytes_sent(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent,
			       काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक fअगरo_cnt, ecount, bytes_sent, flush_fअगरo;

	fअगरo_cnt = esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES;
	अगर (esp->prev_cfg3 & ESP_CONFIG3_EWIDE)
		fअगरo_cnt <<= 1;

	ecount = 0;
	अगर (!(esp->sreg & ESP_STAT_TCNT)) अणु
		ecount = ((अचिन्हित पूर्णांक)esp_पढ़ो8(ESP_TCLOW) |
			  (((अचिन्हित पूर्णांक)esp_पढ़ो8(ESP_TCMED)) << 8));
		अगर (esp->rev == FASHME)
			ecount |= ((अचिन्हित पूर्णांक)esp_पढ़ो8(FAS_RLO)) << 16;
		अगर (esp->rev == PCSCSI && (esp->config2 & ESP_CONFIG2_FENAB))
			ecount |= ((अचिन्हित पूर्णांक)esp_पढ़ो8(ESP_TCHI)) << 16;
	पूर्ण

	bytes_sent = esp->data_dma_len;
	bytes_sent -= ecount;
	bytes_sent -= esp->send_cmd_residual;

	/*
	 * The am53c974 has a DMA 'peculiarity'. The करोc states:
	 * In some odd byte conditions, one residual byte will
	 * be left in the SCSI FIFO, and the FIFO Flags will
	 * never count to '0 '. When this happens, the residual
	 * byte should be retrieved via PIO following completion
	 * of the BLAST operation.
	 */
	अगर (fअगरo_cnt == 1 && ent->flags & ESP_CMD_FLAG_RESIDUAL) अणु
		माप_प्रकार count = 1;
		माप_प्रकार offset = bytes_sent;
		u8 bval = esp_पढ़ो8(ESP_FDATA);

		अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE)
			ent->sense_ptr[bytes_sent] = bval;
		अन्यथा अणु
			काष्ठा esp_cmd_priv *p = ESP_CMD_PRIV(cmd);
			u8 *ptr;

			ptr = scsi_kmap_atomic_sg(p->cur_sg, p->num_sg,
						  &offset, &count);
			अगर (likely(ptr)) अणु
				*(ptr + offset) = bval;
				scsi_kunmap_atomic_sg(ptr);
			पूर्ण
		पूर्ण
		bytes_sent += fअगरo_cnt;
		ent->flags &= ~ESP_CMD_FLAG_RESIDUAL;
	पूर्ण
	अगर (!(ent->flags & ESP_CMD_FLAG_WRITE))
		bytes_sent -= fअगरo_cnt;

	flush_fअगरo = 0;
	अगर (!esp->prev_soff) अणु
		/* Synchronous data transfer, always flush fअगरo. */
		flush_fअगरo = 1;
	पूर्ण अन्यथा अणु
		अगर (esp->rev == ESP100) अणु
			u32 fflags, phase;

			/* ESP100 has a chip bug where in the synchronous data
			 * phase it can mistake a final दीर्घ REQ pulse from the
			 * target as an extra data byte.  Fun.
			 *
			 * To detect this हाल we resample the status रेजिस्टर
			 * and fअगरo flags.  If we're still in a data phase and
			 * we see spurious chunks in the fअगरo, we वापस error
			 * to the caller which should reset and set things up
			 * such that we only try future transfers to this
			 * target in synchronous mode.
			 */
			esp->sreg = esp_पढ़ो8(ESP_STATUS);
			phase = esp->sreg & ESP_STAT_PMASK;
			fflags = esp_पढ़ो8(ESP_FFLAGS);

			अगर ((phase == ESP_DOP &&
			     (fflags & ESP_FF_ONOTZERO)) ||
			    (phase == ESP_DIP &&
			     (fflags & ESP_FF_FBYTES)))
				वापस -1;
		पूर्ण
		अगर (!(ent->flags & ESP_CMD_FLAG_WRITE))
			flush_fअगरo = 1;
	पूर्ण

	अगर (flush_fअगरo)
		esp_flush_fअगरo(esp);

	वापस bytes_sent;
पूर्ण

अटल व्योम esp_setsync(काष्ठा esp *esp, काष्ठा esp_target_data *tp,
			u8 scsi_period, u8 scsi_offset,
			u8 esp_stp, u8 esp_soff)
अणु
	spi_period(tp->starget) = scsi_period;
	spi_offset(tp->starget) = scsi_offset;
	spi_width(tp->starget) = (tp->flags & ESP_TGT_WIDE) ? 1 : 0;

	अगर (esp_soff) अणु
		esp_stp &= 0x1f;
		esp_soff |= esp->radelay;
		अगर (esp->rev >= FAS236) अणु
			u8 bit = ESP_CONFIG3_FSCSI;
			अगर (esp->rev >= FAS100A)
				bit = ESP_CONFIG3_FAST;

			अगर (scsi_period < 50) अणु
				अगर (esp->rev == FASHME)
					esp_soff &= ~esp->radelay;
				tp->esp_config3 |= bit;
			पूर्ण अन्यथा अणु
				tp->esp_config3 &= ~bit;
			पूर्ण
			esp->prev_cfg3 = tp->esp_config3;
			esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);
		पूर्ण
	पूर्ण

	tp->esp_period = esp->prev_stp = esp_stp;
	tp->esp_offset = esp->prev_soff = esp_soff;

	esp_ग_लिखो8(esp_soff, ESP_SOFF);
	esp_ग_लिखो8(esp_stp, ESP_STP);

	tp->flags &= ~(ESP_TGT_NEGO_SYNC | ESP_TGT_CHECK_NEGO);

	spi_display_xfer_agreement(tp->starget);
पूर्ण

अटल व्योम esp_msgin_reject(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent = esp->active_cmd;
	काष्ठा scsi_cmnd *cmd = ent->cmd;
	काष्ठा esp_target_data *tp;
	पूर्णांक tgt;

	tgt = cmd->device->id;
	tp = &esp->target[tgt];

	अगर (tp->flags & ESP_TGT_NEGO_WIDE) अणु
		tp->flags &= ~(ESP_TGT_NEGO_WIDE | ESP_TGT_WIDE);

		अगर (!esp_need_to_nego_sync(tp)) अणु
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
			scsi_esp_cmd(esp, ESP_CMD_RATN);
		पूर्ण अन्यथा अणु
			esp->msg_out_len =
				spi_populate_sync_msg(&esp->msg_out[0],
						      tp->nego_goal_period,
						      tp->nego_goal_offset);
			tp->flags |= ESP_TGT_NEGO_SYNC;
			scsi_esp_cmd(esp, ESP_CMD_SATN);
		पूर्ण
		वापस;
	पूर्ण

	अगर (tp->flags & ESP_TGT_NEGO_SYNC) अणु
		tp->flags &= ~(ESP_TGT_NEGO_SYNC | ESP_TGT_CHECK_NEGO);
		tp->esp_period = 0;
		tp->esp_offset = 0;
		esp_setsync(esp, tp, 0, 0, 0, 0);
		scsi_esp_cmd(esp, ESP_CMD_RATN);
		वापस;
	पूर्ण

	shost_prपूर्णांकk(KERN_INFO, esp->host, "Unexpected MESSAGE REJECT\n");
	esp_schedule_reset(esp);
पूर्ण

अटल व्योम esp_msgin_sdtr(काष्ठा esp *esp, काष्ठा esp_target_data *tp)
अणु
	u8 period = esp->msg_in[3];
	u8 offset = esp->msg_in[4];
	u8 stp;

	अगर (!(tp->flags & ESP_TGT_NEGO_SYNC))
		जाओ करो_reject;

	अगर (offset > 15)
		जाओ करो_reject;

	अगर (offset) अणु
		पूर्णांक one_घड़ी;

		अगर (period > esp->max_period) अणु
			period = offset = 0;
			जाओ करो_sdtr;
		पूर्ण
		अगर (period < esp->min_period)
			जाओ करो_reject;

		one_घड़ी = esp->ccycle / 1000;
		stp = DIV_ROUND_UP(period << 2, one_घड़ी);
		अगर (stp && esp->rev >= FAS236) अणु
			अगर (stp >= 50)
				stp--;
		पूर्ण
	पूर्ण अन्यथा अणु
		stp = 0;
	पूर्ण

	esp_setsync(esp, tp, period, offset, stp, offset);
	वापस;

करो_reject:
	esp->msg_out[0] = MESSAGE_REJECT;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
	वापस;

करो_sdtr:
	tp->nego_goal_period = period;
	tp->nego_goal_offset = offset;
	esp->msg_out_len =
		spi_populate_sync_msg(&esp->msg_out[0],
				      tp->nego_goal_period,
				      tp->nego_goal_offset);
	scsi_esp_cmd(esp, ESP_CMD_SATN);
पूर्ण

अटल व्योम esp_msgin_wdtr(काष्ठा esp *esp, काष्ठा esp_target_data *tp)
अणु
	पूर्णांक size = 8 << esp->msg_in[3];
	u8 cfg3;

	अगर (esp->rev != FASHME)
		जाओ करो_reject;

	अगर (size != 8 && size != 16)
		जाओ करो_reject;

	अगर (!(tp->flags & ESP_TGT_NEGO_WIDE))
		जाओ करो_reject;

	cfg3 = tp->esp_config3;
	अगर (size == 16) अणु
		tp->flags |= ESP_TGT_WIDE;
		cfg3 |= ESP_CONFIG3_EWIDE;
	पूर्ण अन्यथा अणु
		tp->flags &= ~ESP_TGT_WIDE;
		cfg3 &= ~ESP_CONFIG3_EWIDE;
	पूर्ण
	tp->esp_config3 = cfg3;
	esp->prev_cfg3 = cfg3;
	esp_ग_लिखो8(cfg3, ESP_CFG3);

	tp->flags &= ~ESP_TGT_NEGO_WIDE;

	spi_period(tp->starget) = 0;
	spi_offset(tp->starget) = 0;
	अगर (!esp_need_to_nego_sync(tp)) अणु
		tp->flags &= ~ESP_TGT_CHECK_NEGO;
		scsi_esp_cmd(esp, ESP_CMD_RATN);
	पूर्ण अन्यथा अणु
		esp->msg_out_len =
			spi_populate_sync_msg(&esp->msg_out[0],
					      tp->nego_goal_period,
					      tp->nego_goal_offset);
		tp->flags |= ESP_TGT_NEGO_SYNC;
		scsi_esp_cmd(esp, ESP_CMD_SATN);
	पूर्ण
	वापस;

करो_reject:
	esp->msg_out[0] = MESSAGE_REJECT;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
पूर्ण

अटल व्योम esp_msgin_extended(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent = esp->active_cmd;
	काष्ठा scsi_cmnd *cmd = ent->cmd;
	काष्ठा esp_target_data *tp;
	पूर्णांक tgt = cmd->device->id;

	tp = &esp->target[tgt];
	अगर (esp->msg_in[2] == EXTENDED_SDTR) अणु
		esp_msgin_sdtr(esp, tp);
		वापस;
	पूर्ण
	अगर (esp->msg_in[2] == EXTENDED_WDTR) अणु
		esp_msgin_wdtr(esp, tp);
		वापस;
	पूर्ण

	shost_prपूर्णांकk(KERN_INFO, esp->host,
		     "Unexpected extended msg type %x\n", esp->msg_in[2]);

	esp->msg_out[0] = MESSAGE_REJECT;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
पूर्ण

/* Analyze msgin bytes received from target so far.  Return non-zero
 * अगर there are more bytes needed to complete the message.
 */
अटल पूर्णांक esp_msgin_process(काष्ठा esp *esp)
अणु
	u8 msg0 = esp->msg_in[0];
	पूर्णांक len = esp->msg_in_len;

	अगर (msg0 & 0x80) अणु
		/* Identअगरy */
		shost_prपूर्णांकk(KERN_INFO, esp->host,
			     "Unexpected msgin identify\n");
		वापस 0;
	पूर्ण

	चयन (msg0) अणु
	हाल EXTENDED_MESSAGE:
		अगर (len == 1)
			वापस 1;
		अगर (len < esp->msg_in[1] + 2)
			वापस 1;
		esp_msgin_extended(esp);
		वापस 0;

	हाल IGNORE_WIDE_RESIDUE: अणु
		काष्ठा esp_cmd_entry *ent;
		काष्ठा esp_cmd_priv *spriv;
		अगर (len == 1)
			वापस 1;

		अगर (esp->msg_in[1] != 1)
			जाओ करो_reject;

		ent = esp->active_cmd;
		spriv = ESP_CMD_PRIV(ent->cmd);

		अगर (spriv->cur_residue == sg_dma_len(spriv->cur_sg)) अणु
			spriv->cur_sg = spriv->prv_sg;
			spriv->cur_residue = 1;
		पूर्ण अन्यथा
			spriv->cur_residue++;
		spriv->tot_residue++;
		वापस 0;
	पूर्ण
	हाल NOP:
		वापस 0;
	हाल RESTORE_POINTERS:
		esp_restore_poपूर्णांकers(esp, esp->active_cmd);
		वापस 0;
	हाल SAVE_POINTERS:
		esp_save_poपूर्णांकers(esp, esp->active_cmd);
		वापस 0;

	हाल COMMAND_COMPLETE:
	हाल DISCONNECT: अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;

		ent->message = msg0;
		esp_event(esp, ESP_EVENT_FREE_BUS);
		esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
		वापस 0;
	पूर्ण
	हाल MESSAGE_REJECT:
		esp_msgin_reject(esp);
		वापस 0;

	शेष:
	करो_reject:
		esp->msg_out[0] = MESSAGE_REJECT;
		esp->msg_out_len = 1;
		scsi_esp_cmd(esp, ESP_CMD_SATN);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक esp_process_event(काष्ठा esp *esp)
अणु
	पूर्णांक ग_लिखो, i;

again:
	ग_लिखो = 0;
	esp_log_event("process event %d phase %x\n",
		      esp->event, esp->sreg & ESP_STAT_PMASK);
	चयन (esp->event) अणु
	हाल ESP_EVENT_CHECK_PHASE:
		चयन (esp->sreg & ESP_STAT_PMASK) अणु
		हाल ESP_DOP:
			esp_event(esp, ESP_EVENT_DATA_OUT);
			अवरोध;
		हाल ESP_DIP:
			esp_event(esp, ESP_EVENT_DATA_IN);
			अवरोध;
		हाल ESP_STATP:
			esp_flush_fअगरo(esp);
			scsi_esp_cmd(esp, ESP_CMD_ICCSEQ);
			esp_event(esp, ESP_EVENT_STATUS);
			esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
			वापस 1;

		हाल ESP_MOP:
			esp_event(esp, ESP_EVENT_MSGOUT);
			अवरोध;

		हाल ESP_MIP:
			esp_event(esp, ESP_EVENT_MSGIN);
			अवरोध;

		हाल ESP_CMDP:
			esp_event(esp, ESP_EVENT_CMD_START);
			अवरोध;

		शेष:
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "Unexpected phase, sreg=%02x\n",
				     esp->sreg);
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण
		जाओ again;

	हाल ESP_EVENT_DATA_IN:
		ग_लिखो = 1;
		fallthrough;

	हाल ESP_EVENT_DATA_OUT: अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;
		काष्ठा scsi_cmnd *cmd = ent->cmd;
		dma_addr_t dma_addr = esp_cur_dma_addr(ent, cmd);
		अचिन्हित पूर्णांक dma_len = esp_cur_dma_len(ent, cmd);

		अगर (esp->rev == ESP100)
			scsi_esp_cmd(esp, ESP_CMD_शून्य);

		अगर (ग_लिखो)
			ent->flags |= ESP_CMD_FLAG_WRITE;
		अन्यथा
			ent->flags &= ~ESP_CMD_FLAG_WRITE;

		अगर (esp->ops->dma_length_limit)
			dma_len = esp->ops->dma_length_limit(esp, dma_addr,
							     dma_len);
		अन्यथा
			dma_len = esp_dma_length_limit(esp, dma_addr, dma_len);

		esp->data_dma_len = dma_len;

		अगर (!dma_len) अणु
			shost_prपूर्णांकk(KERN_ERR, esp->host,
				     "DMA length is zero!\n");
			shost_prपूर्णांकk(KERN_ERR, esp->host,
				     "cur adr[%08llx] len[%08x]\n",
				     (अचिन्हित दीर्घ दीर्घ)esp_cur_dma_addr(ent, cmd),
				     esp_cur_dma_len(ent, cmd));
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण

		esp_log_datastart("start data addr[%08llx] len[%u] write(%d)\n",
				  (अचिन्हित दीर्घ दीर्घ)dma_addr, dma_len, ग_लिखो);

		esp->ops->send_dma_cmd(esp, dma_addr, dma_len, dma_len,
				       ग_लिखो, ESP_CMD_DMA | ESP_CMD_TI);
		esp_event(esp, ESP_EVENT_DATA_DONE);
		अवरोध;
	पूर्ण
	हाल ESP_EVENT_DATA_DONE: अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;
		काष्ठा scsi_cmnd *cmd = ent->cmd;
		पूर्णांक bytes_sent;

		अगर (esp->ops->dma_error(esp)) अणु
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "data done, DMA error, resetting\n");
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण

		अगर (ent->flags & ESP_CMD_FLAG_WRITE) अणु
			/* XXX parity errors, etc. XXX */

			esp->ops->dma_drain(esp);
		पूर्ण
		esp->ops->dma_invalidate(esp);

		अगर (esp->ireg != ESP_INTR_BSERV) अणु
			/* We should always see exactly a bus-service
			 * पूर्णांकerrupt at the end of a successful transfer.
			 */
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "data done, not BSERV, resetting\n");
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण

		bytes_sent = esp_data_bytes_sent(esp, ent, cmd);

		esp_log_dataकरोne("data done flgs[%x] sent[%d]\n",
				 ent->flags, bytes_sent);

		अगर (bytes_sent < 0) अणु
			/* XXX क्रमce sync mode क्रम this target XXX */
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण

		esp_advance_dma(esp, ent, cmd, bytes_sent);
		esp_event(esp, ESP_EVENT_CHECK_PHASE);
		जाओ again;
	पूर्ण

	हाल ESP_EVENT_STATUS: अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;

		अगर (esp->ireg & ESP_INTR_FDONE) अणु
			ent->status = esp_पढ़ो8(ESP_FDATA);
			ent->message = esp_पढ़ो8(ESP_FDATA);
			scsi_esp_cmd(esp, ESP_CMD_MOK);
		पूर्ण अन्यथा अगर (esp->ireg == ESP_INTR_BSERV) अणु
			ent->status = esp_पढ़ो8(ESP_FDATA);
			ent->message = 0xff;
			esp_event(esp, ESP_EVENT_MSGIN);
			वापस 0;
		पूर्ण

		अगर (ent->message != COMMAND_COMPLETE) अणु
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "Unexpected message %x in status\n",
				     ent->message);
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण

		esp_event(esp, ESP_EVENT_FREE_BUS);
		esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
		अवरोध;
	पूर्ण
	हाल ESP_EVENT_FREE_BUS: अणु
		काष्ठा esp_cmd_entry *ent = esp->active_cmd;
		काष्ठा scsi_cmnd *cmd = ent->cmd;

		अगर (ent->message == COMMAND_COMPLETE ||
		    ent->message == DISCONNECT)
			scsi_esp_cmd(esp, ESP_CMD_ESEL);

		अगर (ent->message == COMMAND_COMPLETE) अणु
			esp_log_cmdकरोne("Command done status[%x] message[%x]\n",
					ent->status, ent->message);
			अगर (ent->status == SAM_STAT_TASK_SET_FULL)
				esp_event_queue_full(esp, ent);

			अगर (ent->status == SAM_STAT_CHECK_CONDITION &&
			    !(ent->flags & ESP_CMD_FLAG_AUTOSENSE)) अणु
				ent->flags |= ESP_CMD_FLAG_AUTOSENSE;
				esp_स्वतःsense(esp, ent);
			पूर्ण अन्यथा अणु
				esp_cmd_is_करोne(esp, ent, cmd, DID_OK);
			पूर्ण
		पूर्ण अन्यथा अगर (ent->message == DISCONNECT) अणु
			esp_log_disconnect("Disconnecting tgt[%d] tag[%x:%x]\n",
					   cmd->device->id,
					   ent->tag[0], ent->tag[1]);

			esp->active_cmd = शून्य;
			esp_maybe_execute_command(esp);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "Unexpected message %x in freebus\n",
				     ent->message);
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण
		अगर (esp->active_cmd)
			esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
		अवरोध;
	पूर्ण
	हाल ESP_EVENT_MSGOUT: अणु
		scsi_esp_cmd(esp, ESP_CMD_FLUSH);

		अगर (esp_debug & ESP_DEBUG_MSGOUT) अणु
			पूर्णांक i;
			prपूर्णांकk("ESP: Sending message [ ");
			क्रम (i = 0; i < esp->msg_out_len; i++)
				prपूर्णांकk("%02x ", esp->msg_out[i]);
			prपूर्णांकk("]\n");
		पूर्ण

		अगर (esp->rev == FASHME) अणु
			पूर्णांक i;

			/* Always use the fअगरo.  */
			क्रम (i = 0; i < esp->msg_out_len; i++) अणु
				esp_ग_लिखो8(esp->msg_out[i], ESP_FDATA);
				esp_ग_लिखो8(0, ESP_FDATA);
			पूर्ण
			scsi_esp_cmd(esp, ESP_CMD_TI);
		पूर्ण अन्यथा अणु
			अगर (esp->msg_out_len == 1) अणु
				esp_ग_लिखो8(esp->msg_out[0], ESP_FDATA);
				scsi_esp_cmd(esp, ESP_CMD_TI);
			पूर्ण अन्यथा अगर (esp->flags & ESP_FLAG_USE_FIFO) अणु
				क्रम (i = 0; i < esp->msg_out_len; i++)
					esp_ग_लिखो8(esp->msg_out[i], ESP_FDATA);
				scsi_esp_cmd(esp, ESP_CMD_TI);
			पूर्ण अन्यथा अणु
				/* Use DMA. */
				स_नकल(esp->command_block,
				       esp->msg_out,
				       esp->msg_out_len);

				esp->ops->send_dma_cmd(esp,
						       esp->command_block_dma,
						       esp->msg_out_len,
						       esp->msg_out_len,
						       0,
						       ESP_CMD_DMA|ESP_CMD_TI);
			पूर्ण
		पूर्ण
		esp_event(esp, ESP_EVENT_MSGOUT_DONE);
		अवरोध;
	पूर्ण
	हाल ESP_EVENT_MSGOUT_DONE:
		अगर (esp->rev == FASHME) अणु
			scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		पूर्ण अन्यथा अणु
			अगर (esp->msg_out_len > 1)
				esp->ops->dma_invalidate(esp);

			/* XXX अगर the chip went पूर्णांकo disconnected mode,
			 * we can't run the phase state machine anyway.
			 */
			अगर (!(esp->ireg & ESP_INTR_DC))
				scsi_esp_cmd(esp, ESP_CMD_शून्य);
		पूर्ण

		esp->msg_out_len = 0;

		esp_event(esp, ESP_EVENT_CHECK_PHASE);
		जाओ again;
	हाल ESP_EVENT_MSGIN:
		अगर (esp->ireg & ESP_INTR_BSERV) अणु
			अगर (esp->rev == FASHME) अणु
				अगर (!(esp_पढ़ो8(ESP_STATUS2) &
				      ESP_STAT2_FEMPTY))
					scsi_esp_cmd(esp, ESP_CMD_FLUSH);
			पूर्ण अन्यथा अणु
				scsi_esp_cmd(esp, ESP_CMD_FLUSH);
				अगर (esp->rev == ESP100)
					scsi_esp_cmd(esp, ESP_CMD_शून्य);
			पूर्ण
			scsi_esp_cmd(esp, ESP_CMD_TI);
			esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
			वापस 1;
		पूर्ण
		अगर (esp->ireg & ESP_INTR_FDONE) अणु
			u8 val;

			अगर (esp->rev == FASHME)
				val = esp->fअगरo[0];
			अन्यथा
				val = esp_पढ़ो8(ESP_FDATA);
			esp->msg_in[esp->msg_in_len++] = val;

			esp_log_msgin("Got msgin byte %x\n", val);

			अगर (!esp_msgin_process(esp))
				esp->msg_in_len = 0;

			अगर (esp->rev == FASHME)
				scsi_esp_cmd(esp, ESP_CMD_FLUSH);

			scsi_esp_cmd(esp, ESP_CMD_MOK);

			/* Check whether a bus reset is to be करोne next */
			अगर (esp->event == ESP_EVENT_RESET)
				वापस 0;

			अगर (esp->event != ESP_EVENT_FREE_BUS)
				esp_event(esp, ESP_EVENT_CHECK_PHASE);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_INFO, esp->host,
				     "MSGIN neither BSERV not FDON, resetting");
			esp_schedule_reset(esp);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल ESP_EVENT_CMD_START:
		स_नकल(esp->command_block, esp->cmd_bytes_ptr,
		       esp->cmd_bytes_left);
		esp_send_dma_cmd(esp, esp->cmd_bytes_left, 16, ESP_CMD_TI);
		esp_event(esp, ESP_EVENT_CMD_DONE);
		esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
		अवरोध;
	हाल ESP_EVENT_CMD_DONE:
		esp->ops->dma_invalidate(esp);
		अगर (esp->ireg & ESP_INTR_BSERV) अणु
			esp_event(esp, ESP_EVENT_CHECK_PHASE);
			जाओ again;
		पूर्ण
		esp_schedule_reset(esp);
		वापस 0;

	हाल ESP_EVENT_RESET:
		scsi_esp_cmd(esp, ESP_CMD_RS);
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_INFO, esp->host,
			     "Unexpected event %x, resetting\n", esp->event);
		esp_schedule_reset(esp);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम esp_reset_cleanup_one(काष्ठा esp *esp, काष्ठा esp_cmd_entry *ent)
अणु
	काष्ठा scsi_cmnd *cmd = ent->cmd;

	esp_unmap_dma(esp, cmd);
	esp_मुक्त_lun_tag(ent, cmd->device->hostdata);
	cmd->result = DID_RESET << 16;

	अगर (ent->flags & ESP_CMD_FLAG_AUTOSENSE)
		esp_unmap_sense(esp, ent);

	cmd->scsi_करोne(cmd);
	list_del(&ent->list);
	esp_put_ent(esp, ent);
पूर्ण

अटल व्योम esp_clear_hold(काष्ठा scsi_device *dev, व्योम *data)
अणु
	काष्ठा esp_lun_data *lp = dev->hostdata;

	BUG_ON(lp->num_tagged);
	lp->hold = 0;
पूर्ण

अटल व्योम esp_reset_cleanup(काष्ठा esp *esp)
अणु
	काष्ठा esp_cmd_entry *ent, *पंचांगp;
	पूर्णांक i;

	list_क्रम_each_entry_safe(ent, पंचांगp, &esp->queued_cmds, list) अणु
		काष्ठा scsi_cmnd *cmd = ent->cmd;

		list_del(&ent->list);
		cmd->result = DID_RESET << 16;
		cmd->scsi_करोne(cmd);
		esp_put_ent(esp, ent);
	पूर्ण

	list_क्रम_each_entry_safe(ent, पंचांगp, &esp->active_cmds, list) अणु
		अगर (ent == esp->active_cmd)
			esp->active_cmd = शून्य;
		esp_reset_cleanup_one(esp, ent);
	पूर्ण

	BUG_ON(esp->active_cmd != शून्य);

	/* Force renegotiation of sync/wide transfers.  */
	क्रम (i = 0; i < ESP_MAX_TARGET; i++) अणु
		काष्ठा esp_target_data *tp = &esp->target[i];

		tp->esp_period = 0;
		tp->esp_offset = 0;
		tp->esp_config3 &= ~(ESP_CONFIG3_EWIDE |
				     ESP_CONFIG3_FSCSI |
				     ESP_CONFIG3_FAST);
		tp->flags &= ~ESP_TGT_WIDE;
		tp->flags |= ESP_TGT_CHECK_NEGO;

		अगर (tp->starget)
			__starget_क्रम_each_device(tp->starget, शून्य,
						  esp_clear_hold);
	पूर्ण
	esp->flags &= ~ESP_FLAG_RESETTING;
पूर्ण

/* Runs under host->lock */
अटल व्योम __esp_पूर्णांकerrupt(काष्ठा esp *esp)
अणु
	पूर्णांक finish_reset, पूर्णांकr_करोne;
	u8 phase;

       /*
	* Once INTRPT is पढ़ो STATUS and SSTEP are cleared.
	*/
	esp->sreg = esp_पढ़ो8(ESP_STATUS);
	esp->seqreg = esp_पढ़ो8(ESP_SSTEP);
	esp->ireg = esp_पढ़ो8(ESP_INTRPT);

	अगर (esp->flags & ESP_FLAG_RESETTING) अणु
		finish_reset = 1;
	पूर्ण अन्यथा अणु
		अगर (esp_check_gross_error(esp))
			वापस;

		finish_reset = esp_check_spur_पूर्णांकr(esp);
		अगर (finish_reset < 0)
			वापस;
	पूर्ण

	अगर (esp->ireg & ESP_INTR_SR)
		finish_reset = 1;

	अगर (finish_reset) अणु
		esp_reset_cleanup(esp);
		अगर (esp->eh_reset) अणु
			complete(esp->eh_reset);
			esp->eh_reset = शून्य;
		पूर्ण
		वापस;
	पूर्ण

	phase = (esp->sreg & ESP_STAT_PMASK);
	अगर (esp->rev == FASHME) अणु
		अगर (((phase != ESP_DIP && phase != ESP_DOP) &&
		     esp->select_state == ESP_SELECT_NONE &&
		     esp->event != ESP_EVENT_STATUS &&
		     esp->event != ESP_EVENT_DATA_DONE) ||
		    (esp->ireg & ESP_INTR_RSEL)) अणु
			esp->sreg2 = esp_पढ़ो8(ESP_STATUS2);
			अगर (!(esp->sreg2 & ESP_STAT2_FEMPTY) ||
			    (esp->sreg2 & ESP_STAT2_F1BYTE))
				hme_पढ़ो_fअगरo(esp);
		पूर्ण
	पूर्ण

	esp_log_पूर्णांकr("intr sreg[%02x] seqreg[%02x] "
		     "sreg2[%02x] ireg[%02x]\n",
		     esp->sreg, esp->seqreg, esp->sreg2, esp->ireg);

	पूर्णांकr_करोne = 0;

	अगर (esp->ireg & (ESP_INTR_S | ESP_INTR_SATN | ESP_INTR_IC)) अणु
		shost_prपूर्णांकk(KERN_INFO, esp->host,
			     "unexpected IREG %02x\n", esp->ireg);
		अगर (esp->ireg & ESP_INTR_IC)
			esp_dump_cmd_log(esp);

		esp_schedule_reset(esp);
	पूर्ण अन्यथा अणु
		अगर (esp->ireg & ESP_INTR_RSEL) अणु
			अगर (esp->active_cmd)
				(व्योम) esp_finish_select(esp);
			पूर्णांकr_करोne = esp_reconnect(esp);
		पूर्ण अन्यथा अणु
			/* Some combination of FDONE, BSERV, DC. */
			अगर (esp->select_state != ESP_SELECT_NONE)
				पूर्णांकr_करोne = esp_finish_select(esp);
		पूर्ण
	पूर्ण
	जबतक (!पूर्णांकr_करोne)
		पूर्णांकr_करोne = esp_process_event(esp);
पूर्ण

irqवापस_t scsi_esp_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा esp *esp = dev_id;
	अचिन्हित दीर्घ flags;
	irqवापस_t ret;

	spin_lock_irqsave(esp->host->host_lock, flags);
	ret = IRQ_NONE;
	अगर (esp->ops->irq_pending(esp)) अणु
		ret = IRQ_HANDLED;
		क्रम (;;) अणु
			पूर्णांक i;

			__esp_पूर्णांकerrupt(esp);
			अगर (!(esp->flags & ESP_FLAG_QUICKIRQ_CHECK))
				अवरोध;
			esp->flags &= ~ESP_FLAG_QUICKIRQ_CHECK;

			क्रम (i = 0; i < ESP_QUICKIRQ_LIMIT; i++) अणु
				अगर (esp->ops->irq_pending(esp))
					अवरोध;
			पूर्ण
			अगर (i == ESP_QUICKIRQ_LIMIT)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(esp->host->host_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(scsi_esp_पूर्णांकr);

अटल व्योम esp_get_revision(काष्ठा esp *esp)
अणु
	u8 val;

	esp->config1 = (ESP_CONFIG1_PENABLE | (esp->scsi_id & 7));
	अगर (esp->config2 == 0) अणु
		esp->config2 = (ESP_CONFIG2_SCSI2ENAB | ESP_CONFIG2_REGPARITY);
		esp_ग_लिखो8(esp->config2, ESP_CFG2);

		val = esp_पढ़ो8(ESP_CFG2);
		val &= ~ESP_CONFIG2_MAGIC;

		esp->config2 = 0;
		अगर (val != (ESP_CONFIG2_SCSI2ENAB | ESP_CONFIG2_REGPARITY)) अणु
			/*
			 * If what we ग_लिखो to cfg2 करोes not come back,
			 * cfg2 is not implemented.
			 * Thereक्रमe this must be a plain esp100.
			 */
			esp->rev = ESP100;
			वापस;
		पूर्ण
	पूर्ण

	esp_set_all_config3(esp, 5);
	esp->prev_cfg3 = 5;
	esp_ग_लिखो8(esp->config2, ESP_CFG2);
	esp_ग_लिखो8(0, ESP_CFG3);
	esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);

	val = esp_पढ़ो8(ESP_CFG3);
	अगर (val != 5) अणु
		/* The cfg2 रेजिस्टर is implemented, however
		 * cfg3 is not, must be esp100a.
		 */
		esp->rev = ESP100A;
	पूर्ण अन्यथा अणु
		esp_set_all_config3(esp, 0);
		esp->prev_cfg3 = 0;
		esp_ग_लिखो8(esp->prev_cfg3, ESP_CFG3);

		/* All of cfgअणु1,2,3पूर्ण implemented, must be one of
		 * the fas variants, figure out which one.
		 */
		अगर (esp->cfact == 0 || esp->cfact > ESP_CCF_F5) अणु
			esp->rev = FAST;
			esp->sync_defp = SYNC_DEFP_FAST;
		पूर्ण अन्यथा अणु
			esp->rev = ESP236;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esp_init_swstate(काष्ठा esp *esp)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&esp->queued_cmds);
	INIT_LIST_HEAD(&esp->active_cmds);
	INIT_LIST_HEAD(&esp->esp_cmd_pool);

	/* Start with a clear state, करोमुख्य validation (via ->slave_configure,
	 * spi_dv_device()) will attempt to enable SYNC, WIDE, and tagged
	 * commands.
	 */
	क्रम (i = 0 ; i < ESP_MAX_TARGET; i++) अणु
		esp->target[i].flags = 0;
		esp->target[i].nego_goal_period = 0;
		esp->target[i].nego_goal_offset = 0;
		esp->target[i].nego_goal_width = 0;
		esp->target[i].nego_goal_tags = 0;
	पूर्ण
पूर्ण

/* This places the ESP पूर्णांकo a known state at boot समय. */
अटल व्योम esp_bootup_reset(काष्ठा esp *esp)
अणु
	u8 val;

	/* Reset the DMA */
	esp->ops->reset_dma(esp);

	/* Reset the ESP */
	esp_reset_esp(esp);

	/* Reset the SCSI bus, but tell ESP not to generate an irq */
	val = esp_पढ़ो8(ESP_CFG1);
	val |= ESP_CONFIG1_SRRDISAB;
	esp_ग_लिखो8(val, ESP_CFG1);

	scsi_esp_cmd(esp, ESP_CMD_RS);
	udelay(400);

	esp_ग_लिखो8(esp->config1, ESP_CFG1);

	/* Eat any bitrot in the chip and we are करोne... */
	esp_पढ़ो8(ESP_INTRPT);
पूर्ण

अटल व्योम esp_set_घड़ी_params(काष्ठा esp *esp)
अणु
	पूर्णांक fhz;
	u8 ccf;

	/* This is getting messy but it has to be करोne correctly or अन्यथा
	 * you get weird behavior all over the place.  We are trying to
	 * basically figure out three pieces of inक्रमmation.
	 *
	 * a) Clock Conversion Factor
	 *
	 *    This is a representation of the input crystal घड़ी frequency
	 *    going पूर्णांकo the ESP on this machine.  Any operation whose timing
	 *    is दीर्घer than 400ns depends on this value being correct.  For
	 *    example, you'll get blips क्रम arbitration/selection during high
	 *    load or with multiple tarमाला_लो अगर this is not set correctly.
	 *
	 * b) Selection Time-Out
	 *
	 *    The ESP isn't very bright and will arbitrate क्रम the bus and try
	 *    to select a target क्रमever अगर you let it.  This value tells the
	 *    ESP when it has taken too दीर्घ to negotiate and that it should
	 *    पूर्णांकerrupt the CPU so we can see what happened.  The value is
	 *    computed as follows (from NCR/Symbios chip करोcs).
	 *
	 *          (Time Out Period) *  (Input Clock)
	 *    STO = ----------------------------------
	 *          (8192) * (Clock Conversion Factor)
	 *
	 *    We use a समय out period of 250ms (ESP_BUS_TIMEOUT).
	 *
	 * c) Imperical स्थिरants क्रम synchronous offset and transfer period
         *    रेजिस्टर values
	 *
	 *    This entails the smallest and largest sync period we could ever
	 *    handle on this ESP.
	 */
	fhz = esp->cfreq;

	ccf = ((fhz / 1000000) + 4) / 5;
	अगर (ccf == 1)
		ccf = 2;

	/* If we can't find anything reasonable, just assume 20MHZ.
	 * This is the घड़ी frequency of the older sun4c's where I've
	 * been unable to find the घड़ी-frequency PROM property.  All
	 * other machines provide useful values it seems.
	 */
	अगर (fhz <= 5000000 || ccf < 1 || ccf > 8) अणु
		fhz = 20000000;
		ccf = 4;
	पूर्ण

	esp->cfact = (ccf == 8 ? 0 : ccf);
	esp->cfreq = fhz;
	esp->ccycle = ESP_HZ_TO_CYCLE(fhz);
	esp->ctick = ESP_TICK(ccf, esp->ccycle);
	esp->neg_defp = ESP_NEG_DEFP(fhz, ccf);
	esp->sync_defp = SYNC_DEFP_SLOW;
पूर्ण

अटल स्थिर अक्षर *esp_chip_names[] = अणु
	"ESP100",
	"ESP100A",
	"ESP236",
	"FAS236",
	"AM53C974",
	"53CF9x-2",
	"FAS100A",
	"FAST",
	"FASHME",
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *esp_transport_ढाँचा;

पूर्णांक scsi_esp_रेजिस्टर(काष्ठा esp *esp)
अणु
	अटल पूर्णांक instance;
	पूर्णांक err;

	अगर (!esp->num_tags)
		esp->num_tags = ESP_DEFAULT_TAGS;
	esp->host->transportt = esp_transport_ढाँचा;
	esp->host->max_lun = ESP_MAX_LUN;
	esp->host->cmd_per_lun = 2;
	esp->host->unique_id = instance;

	esp_set_घड़ी_params(esp);

	esp_get_revision(esp);

	esp_init_swstate(esp);

	esp_bootup_reset(esp);

	dev_prपूर्णांकk(KERN_INFO, esp->dev, "esp%u: regs[%1p:%1p] irq[%u]\n",
		   esp->host->unique_id, esp->regs, esp->dma_regs,
		   esp->host->irq);
	dev_prपूर्णांकk(KERN_INFO, esp->dev,
		   "esp%u: is a %s, %u MHz (ccf=%u), SCSI ID %u\n",
		   esp->host->unique_id, esp_chip_names[esp->rev],
		   esp->cfreq / 1000000, esp->cfact, esp->scsi_id);

	/* Let the SCSI bus reset settle. */
	ssleep(esp_bus_reset_settle);

	err = scsi_add_host(esp->host, esp->dev);
	अगर (err)
		वापस err;

	instance++;

	scsi_scan_host(esp->host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_esp_रेजिस्टर);

व्योम scsi_esp_unरेजिस्टर(काष्ठा esp *esp)
अणु
	scsi_हटाओ_host(esp->host);
पूर्ण
EXPORT_SYMBOL(scsi_esp_unरेजिस्टर);

अटल पूर्णांक esp_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा esp *esp = shost_priv(dev_to_shost(&starget->dev));
	काष्ठा esp_target_data *tp = &esp->target[starget->id];

	tp->starget = starget;

	वापस 0;
पूर्ण

अटल व्योम esp_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा esp *esp = shost_priv(dev_to_shost(&starget->dev));
	काष्ठा esp_target_data *tp = &esp->target[starget->id];

	tp->starget = शून्य;
पूर्ण

अटल पूर्णांक esp_slave_alloc(काष्ठा scsi_device *dev)
अणु
	काष्ठा esp *esp = shost_priv(dev->host);
	काष्ठा esp_target_data *tp = &esp->target[dev->id];
	काष्ठा esp_lun_data *lp;

	lp = kzalloc(माप(*lp), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;
	dev->hostdata = lp;

	spi_min_period(tp->starget) = esp->min_period;
	spi_max_offset(tp->starget) = 15;

	अगर (esp->flags & ESP_FLAG_WIDE_CAPABLE)
		spi_max_width(tp->starget) = 1;
	अन्यथा
		spi_max_width(tp->starget) = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक esp_slave_configure(काष्ठा scsi_device *dev)
अणु
	काष्ठा esp *esp = shost_priv(dev->host);
	काष्ठा esp_target_data *tp = &esp->target[dev->id];

	अगर (dev->tagged_supported)
		scsi_change_queue_depth(dev, esp->num_tags);

	tp->flags |= ESP_TGT_DISCONNECT;

	अगर (!spi_initial_dv(dev->sdev_target))
		spi_dv_device(dev);

	वापस 0;
पूर्ण

अटल व्योम esp_slave_destroy(काष्ठा scsi_device *dev)
अणु
	काष्ठा esp_lun_data *lp = dev->hostdata;

	kमुक्त(lp);
	dev->hostdata = शून्य;
पूर्ण

अटल पूर्णांक esp_eh_पात_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp *esp = shost_priv(cmd->device->host);
	काष्ठा esp_cmd_entry *ent, *पंचांगp;
	काष्ठा completion eh_करोne;
	अचिन्हित दीर्घ flags;

	/* XXX This helps a lot with debugging but might be a bit
	 * XXX much क्रम the final driver.
	 */
	spin_lock_irqsave(esp->host->host_lock, flags);
	shost_prपूर्णांकk(KERN_ERR, esp->host, "Aborting command [%p:%02x]\n",
		     cmd, cmd->cmnd[0]);
	ent = esp->active_cmd;
	अगर (ent)
		shost_prपूर्णांकk(KERN_ERR, esp->host,
			     "Current command [%p:%02x]\n",
			     ent->cmd, ent->cmd->cmnd[0]);
	list_क्रम_each_entry(ent, &esp->queued_cmds, list) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host, "Queued command [%p:%02x]\n",
			     ent->cmd, ent->cmd->cmnd[0]);
	पूर्ण
	list_क्रम_each_entry(ent, &esp->active_cmds, list) अणु
		shost_prपूर्णांकk(KERN_ERR, esp->host, " Active command [%p:%02x]\n",
			     ent->cmd, ent->cmd->cmnd[0]);
	पूर्ण
	esp_dump_cmd_log(esp);
	spin_unlock_irqrestore(esp->host->host_lock, flags);

	spin_lock_irqsave(esp->host->host_lock, flags);

	ent = शून्य;
	list_क्रम_each_entry(पंचांगp, &esp->queued_cmds, list) अणु
		अगर (पंचांगp->cmd == cmd) अणु
			ent = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ent) अणु
		/* Easiest हाल, we didn't even issue the command
		 * yet so it is trivial to पात.
		 */
		list_del(&ent->list);

		cmd->result = DID_ABORT << 16;
		cmd->scsi_करोne(cmd);

		esp_put_ent(esp, ent);

		जाओ out_success;
	पूर्ण

	init_completion(&eh_करोne);

	ent = esp->active_cmd;
	अगर (ent && ent->cmd == cmd) अणु
		/* Command is the currently active command on
		 * the bus.  If we alपढ़ोy have an output message
		 * pending, no dice.
		 */
		अगर (esp->msg_out_len)
			जाओ out_failure;

		/* Send out an पात, encouraging the target to
		 * go to MSGOUT phase by निश्चितing ATN.
		 */
		esp->msg_out[0] = ABORT_TASK_SET;
		esp->msg_out_len = 1;
		ent->eh_करोne = &eh_करोne;

		scsi_esp_cmd(esp, ESP_CMD_SATN);
	पूर्ण अन्यथा अणु
		/* The command is disconnected.  This is not easy to
		 * पात.  For now we fail and let the scsi error
		 * handling layer go try a scsi bus reset or host
		 * reset.
		 *
		 * What we could करो is put together a scsi command
		 * solely क्रम the purpose of sending an पात message
		 * to the target.  Coming up with all the code to
		 * cook up scsi commands, special हाल them everywhere,
		 * etc. is क्रम questionable gain and it would be better
		 * अगर the generic scsi error handling layer could करो at
		 * least some of that क्रम us.
		 *
		 * Anyways this is an area क्रम potential future improvement
		 * in this driver.
		 */
		जाओ out_failure;
	पूर्ण

	spin_unlock_irqrestore(esp->host->host_lock, flags);

	अगर (!रुको_क्रम_completion_समयout(&eh_करोne, 5 * HZ)) अणु
		spin_lock_irqsave(esp->host->host_lock, flags);
		ent->eh_करोne = शून्य;
		spin_unlock_irqrestore(esp->host->host_lock, flags);

		वापस FAILED;
	पूर्ण

	वापस SUCCESS;

out_success:
	spin_unlock_irqrestore(esp->host->host_lock, flags);
	वापस SUCCESS;

out_failure:
	/* XXX This might be a good location to set ESP_TGT_BROKEN
	 * XXX since we know which target/lun in particular is
	 * XXX causing trouble.
	 */
	spin_unlock_irqrestore(esp->host->host_lock, flags);
	वापस FAILED;
पूर्ण

अटल पूर्णांक esp_eh_bus_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp *esp = shost_priv(cmd->device->host);
	काष्ठा completion eh_reset;
	अचिन्हित दीर्घ flags;

	init_completion(&eh_reset);

	spin_lock_irqsave(esp->host->host_lock, flags);

	esp->eh_reset = &eh_reset;

	/* XXX This is too simple... We should add lots of
	 * XXX checks here so that अगर we find that the chip is
	 * XXX very wedged we वापस failure immediately so
	 * XXX that we can perक्रमm a full chip reset.
	 */
	esp->flags |= ESP_FLAG_RESETTING;
	scsi_esp_cmd(esp, ESP_CMD_RS);

	spin_unlock_irqrestore(esp->host->host_lock, flags);

	ssleep(esp_bus_reset_settle);

	अगर (!रुको_क्रम_completion_समयout(&eh_reset, 5 * HZ)) अणु
		spin_lock_irqsave(esp->host->host_lock, flags);
		esp->eh_reset = शून्य;
		spin_unlock_irqrestore(esp->host->host_lock, flags);

		वापस FAILED;
	पूर्ण

	वापस SUCCESS;
पूर्ण

/* All bets are off, reset the entire device.  */
अटल पूर्णांक esp_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा esp *esp = shost_priv(cmd->device->host);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(esp->host->host_lock, flags);
	esp_bootup_reset(esp);
	esp_reset_cleanup(esp);
	spin_unlock_irqrestore(esp->host->host_lock, flags);

	ssleep(esp_bus_reset_settle);

	वापस SUCCESS;
पूर्ण

अटल स्थिर अक्षर *esp_info(काष्ठा Scsi_Host *host)
अणु
	वापस "esp";
पूर्ण

काष्ठा scsi_host_ढाँचा scsi_esp_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "esp",
	.info			= esp_info,
	.queuecommand		= esp_queuecommand,
	.target_alloc		= esp_target_alloc,
	.target_destroy		= esp_target_destroy,
	.slave_alloc		= esp_slave_alloc,
	.slave_configure	= esp_slave_configure,
	.slave_destroy		= esp_slave_destroy,
	.eh_पात_handler	= esp_eh_पात_handler,
	.eh_bus_reset_handler	= esp_eh_bus_reset_handler,
	.eh_host_reset_handler	= esp_eh_host_reset_handler,
	.can_queue		= 7,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.max_sectors		= 0xffff,
	.skip_settle_delay	= 1,
पूर्ण;
EXPORT_SYMBOL(scsi_esp_ढाँचा);

अटल व्योम esp_get_संकेतling(काष्ठा Scsi_Host *host)
अणु
	काष्ठा esp *esp = shost_priv(host);
	क्रमागत spi_संकेत_type type;

	अगर (esp->flags & ESP_FLAG_DIFFERENTIAL)
		type = SPI_SIGNAL_HVD;
	अन्यथा
		type = SPI_SIGNAL_SE;

	spi_संकेतling(host) = type;
पूर्ण

अटल व्योम esp_set_offset(काष्ठा scsi_target *target, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(target->dev.parent);
	काष्ठा esp *esp = shost_priv(host);
	काष्ठा esp_target_data *tp = &esp->target[target->id];

	अगर (esp->flags & ESP_FLAG_DISABLE_SYNC)
		tp->nego_goal_offset = 0;
	अन्यथा
		tp->nego_goal_offset = offset;
	tp->flags |= ESP_TGT_CHECK_NEGO;
पूर्ण

अटल व्योम esp_set_period(काष्ठा scsi_target *target, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(target->dev.parent);
	काष्ठा esp *esp = shost_priv(host);
	काष्ठा esp_target_data *tp = &esp->target[target->id];

	tp->nego_goal_period = period;
	tp->flags |= ESP_TGT_CHECK_NEGO;
पूर्ण

अटल व्योम esp_set_width(काष्ठा scsi_target *target, पूर्णांक width)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(target->dev.parent);
	काष्ठा esp *esp = shost_priv(host);
	काष्ठा esp_target_data *tp = &esp->target[target->id];

	tp->nego_goal_width = (width ? 1 : 0);
	tp->flags |= ESP_TGT_CHECK_NEGO;
पूर्ण

अटल काष्ठा spi_function_ढाँचा esp_transport_ops = अणु
	.set_offset		= esp_set_offset,
	.show_offset		= 1,
	.set_period		= esp_set_period,
	.show_period		= 1,
	.set_width		= esp_set_width,
	.show_width		= 1,
	.get_संकेतling		= esp_get_संकेतling,
पूर्ण;

अटल पूर्णांक __init esp_init(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा scsi_poपूर्णांकer) <
		     माप(काष्ठा esp_cmd_priv));

	esp_transport_ढाँचा = spi_attach_transport(&esp_transport_ops);
	अगर (!esp_transport_ढाँचा)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम __निकास esp_निकास(व्योम)
अणु
	spi_release_transport(esp_transport_ढाँचा);
पूर्ण

MODULE_DESCRIPTION("ESP SCSI driver core");
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

module_param(esp_bus_reset_settle, पूर्णांक, 0);
MODULE_PARM_DESC(esp_bus_reset_settle,
		 "ESP scsi bus reset delay in seconds");

module_param(esp_debug, पूर्णांक, 0);
MODULE_PARM_DESC(esp_debug,
"ESP bitmapped debugging message enable value:\n"
"	0x00000001	Log interrupt events\n"
"	0x00000002	Log scsi commands\n"
"	0x00000004	Log resets\n"
"	0x00000008	Log message in events\n"
"	0x00000010	Log message out events\n"
"	0x00000020	Log command completion\n"
"	0x00000040	Log disconnects\n"
"	0x00000080	Log data start\n"
"	0x00000100	Log data done\n"
"	0x00000200	Log reconnects\n"
"	0x00000400	Log auto-sense data\n"
);

module_init(esp_init);
module_निकास(esp_निकास);

#अगर_घोषित CONFIG_SCSI_ESP_PIO
अटल अंतरभूत अचिन्हित पूर्णांक esp_रुको_क्रम_fअगरo(काष्ठा esp *esp)
अणु
	पूर्णांक i = 500000;

	करो अणु
		अचिन्हित पूर्णांक fbytes = esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES;

		अगर (fbytes)
			वापस fbytes;

		udelay(1);
	पूर्ण जबतक (--i);

	shost_prपूर्णांकk(KERN_ERR, esp->host, "FIFO is empty. sreg [%02x]\n",
		     esp_पढ़ो8(ESP_STATUS));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक esp_रुको_क्रम_पूर्णांकr(काष्ठा esp *esp)
अणु
	पूर्णांक i = 500000;

	करो अणु
		esp->sreg = esp_पढ़ो8(ESP_STATUS);
		अगर (esp->sreg & ESP_STAT_INTR)
			वापस 0;

		udelay(1);
	पूर्ण जबतक (--i);

	shost_prपूर्णांकk(KERN_ERR, esp->host, "IRQ timeout. sreg [%02x]\n",
		     esp->sreg);
	वापस 1;
पूर्ण

#घोषणा ESP_FIFO_SIZE 16

व्योम esp_send_pio_cmd(काष्ठा esp *esp, u32 addr, u32 esp_count,
		      u32 dma_count, पूर्णांक ग_लिखो, u8 cmd)
अणु
	u8 phase = esp->sreg & ESP_STAT_PMASK;

	cmd &= ~ESP_CMD_DMA;
	esp->send_cmd_error = 0;

	अगर (ग_लिखो) अणु
		u8 *dst = (u8 *)addr;
		u8 mask = ~(phase == ESP_MIP ? ESP_INTR_FDONE : ESP_INTR_BSERV);

		scsi_esp_cmd(esp, cmd);

		जबतक (1) अणु
			अगर (!esp_रुको_क्रम_fअगरo(esp))
				अवरोध;

			*dst++ = पढ़ोb(esp->fअगरo_reg);
			--esp_count;

			अगर (!esp_count)
				अवरोध;

			अगर (esp_रुको_क्रम_पूर्णांकr(esp)) अणु
				esp->send_cmd_error = 1;
				अवरोध;
			पूर्ण

			अगर ((esp->sreg & ESP_STAT_PMASK) != phase)
				अवरोध;

			esp->ireg = esp_पढ़ो8(ESP_INTRPT);
			अगर (esp->ireg & mask) अणु
				esp->send_cmd_error = 1;
				अवरोध;
			पूर्ण

			अगर (phase == ESP_MIP)
				esp_ग_लिखो8(ESP_CMD_MOK, ESP_CMD);

			esp_ग_लिखो8(ESP_CMD_TI, ESP_CMD);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक n = ESP_FIFO_SIZE;
		u8 *src = (u8 *)addr;

		scsi_esp_cmd(esp, ESP_CMD_FLUSH);

		अगर (n > esp_count)
			n = esp_count;
		ग_लिखोsb(esp->fअगरo_reg, src, n);
		src += n;
		esp_count -= n;

		scsi_esp_cmd(esp, cmd);

		जबतक (esp_count) अणु
			अगर (esp_रुको_क्रम_पूर्णांकr(esp)) अणु
				esp->send_cmd_error = 1;
				अवरोध;
			पूर्ण

			अगर ((esp->sreg & ESP_STAT_PMASK) != phase)
				अवरोध;

			esp->ireg = esp_पढ़ो8(ESP_INTRPT);
			अगर (esp->ireg & ~ESP_INTR_BSERV) अणु
				esp->send_cmd_error = 1;
				अवरोध;
			पूर्ण

			n = ESP_FIFO_SIZE -
			    (esp_पढ़ो8(ESP_FFLAGS) & ESP_FF_FBYTES);

			अगर (n > esp_count)
				n = esp_count;
			ग_लिखोsb(esp->fअगरo_reg, src, n);
			src += n;
			esp_count -= n;

			esp_ग_लिखो8(ESP_CMD_TI, ESP_CMD);
		पूर्ण
	पूर्ण

	esp->send_cmd_residual = esp_count;
पूर्ण
EXPORT_SYMBOL(esp_send_pio_cmd);
#पूर्ण_अगर
