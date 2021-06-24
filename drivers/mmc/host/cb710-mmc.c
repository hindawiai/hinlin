<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cb710/mmc.c
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश "cb710-mmc.h"

#घोषणा CB710_MMC_REQ_TIMEOUT_MS	2000

अटल स्थिर u8 cb710_घड़ी_भागider_log2[8] = अणु
/*	1, 2, 4, 8, 16, 32, 128, 512 */
	0, 1, 2, 3,  4,  5,   7,   9
पूर्ण;
#घोषणा CB710_MAX_DIVIDER_IDX	\
	(ARRAY_SIZE(cb710_घड़ी_भागider_log2) - 1)

अटल स्थिर u8 cb710_src_freq_mhz[16] = अणु
	33, 10, 20, 25, 30, 35, 40, 45,
	50, 55, 60, 65, 70, 75, 80, 85
पूर्ण;

अटल व्योम cb710_mmc_select_घड़ी_भागider(काष्ठा mmc_host *mmc, पूर्णांक hz)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);
	काष्ठा pci_dev *pdev = cb710_slot_to_chip(slot)->pdev;
	u32 src_freq_idx;
	u32 भागider_idx;
	पूर्णांक src_hz;

	/* on CB710 in HP nx9500:
	 *   src_freq_idx == 0
	 *   indexes 1-7 work as written in the table
	 *   indexes 0,8-15 give no घड़ी output
	 */
	pci_पढ़ो_config_dword(pdev, 0x48, &src_freq_idx);
	src_freq_idx = (src_freq_idx >> 16) & 0xF;
	src_hz = cb710_src_freq_mhz[src_freq_idx] * 1000000;

	क्रम (भागider_idx = 0; भागider_idx < CB710_MAX_DIVIDER_IDX; ++भागider_idx) अणु
		अगर (hz >= src_hz >> cb710_घड़ी_भागider_log2[भागider_idx])
			अवरोध;
	पूर्ण

	अगर (src_freq_idx)
		भागider_idx |= 0x8;
	अन्यथा अगर (भागider_idx == 0)
		भागider_idx = 1;

	cb710_pci_update_config_reg(pdev, 0x40, ~0xF0000000, भागider_idx << 28);

	dev_dbg(cb710_slot_dev(slot),
		"clock set to %d Hz, wanted %d Hz; src_freq_idx = %d, divider_idx = %d|%d\n",
		src_hz >> cb710_घड़ी_भागider_log2[भागider_idx & 7],
		hz, src_freq_idx, भागider_idx & 7, भागider_idx & 8);
पूर्ण

अटल व्योम __cb710_mmc_enable_irq(काष्ठा cb710_slot *slot,
	अचिन्हित लघु enable, अचिन्हित लघु mask)
अणु
	/* clear global IE
	 * - it माला_लो set later अगर any पूर्णांकerrupt sources are enabled */
	mask |= CB710_MMC_IE_IRQ_ENABLE;

	/* look like पूर्णांकerrupt is fired whenever
	 * WORD[0x0C] & WORD[0x10] != 0;
	 * -> bit 15 port 0x0C seems to be global पूर्णांकerrupt enable
	 */

	enable = (cb710_पढ़ो_port_16(slot, CB710_MMC_IRQ_ENABLE_PORT)
		& ~mask) | enable;

	अगर (enable)
		enable |= CB710_MMC_IE_IRQ_ENABLE;

	cb710_ग_लिखो_port_16(slot, CB710_MMC_IRQ_ENABLE_PORT, enable);
पूर्ण

अटल व्योम cb710_mmc_enable_irq(काष्ठा cb710_slot *slot,
	अचिन्हित लघु enable, अचिन्हित लघु mask)
अणु
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(cb710_slot_to_mmc(slot));
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पढ़ोer->irq_lock, flags);
	/* this is the only thing irq_lock protects */
	__cb710_mmc_enable_irq(slot, enable, mask);
	spin_unlock_irqrestore(&पढ़ोer->irq_lock, flags);
पूर्ण

अटल व्योम cb710_mmc_reset_events(काष्ठा cb710_slot *slot)
अणु
	cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS0_PORT, 0xFF);
	cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS1_PORT, 0xFF);
	cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS2_PORT, 0xFF);
पूर्ण

अटल व्योम cb710_mmc_enable_4bit_data(काष्ठा cb710_slot *slot, पूर्णांक enable)
अणु
	अगर (enable)
		cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT,
			CB710_MMC_C1_4BIT_DATA_BUS, 0);
	अन्यथा
		cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT,
			0, CB710_MMC_C1_4BIT_DATA_BUS);
पूर्ण

अटल पूर्णांक cb710_check_event(काष्ठा cb710_slot *slot, u8 what)
अणु
	u16 status;

	status = cb710_पढ़ो_port_16(slot, CB710_MMC_STATUS_PORT);

	अगर (status & CB710_MMC_S0_FIFO_UNDERFLOW) अणु
		/* it is just a guess, so log it */
		dev_dbg(cb710_slot_dev(slot),
			"CHECK : ignoring bit 6 in status %04X\n", status);
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS0_PORT,
			CB710_MMC_S0_FIFO_UNDERFLOW);
		status &= ~CB710_MMC_S0_FIFO_UNDERFLOW;
	पूर्ण

	अगर (status & CB710_MMC_STATUS_ERROR_EVENTS) अणु
		dev_dbg(cb710_slot_dev(slot),
			"CHECK : returning EIO on status %04X\n", status);
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS0_PORT, status & 0xFF);
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS1_PORT,
			CB710_MMC_S1_RESET);
		वापस -EIO;
	पूर्ण

	/* 'what' is a bit in MMC_STATUS1 */
	अगर ((status >> 8) & what) अणु
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS1_PORT, what);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cb710_रुको_क्रम_event(काष्ठा cb710_slot *slot, u8 what)
अणु
	पूर्णांक err = 0;
	अचिन्हित limit = 2000000;	/* FIXME: real समयout */

#अगर_घोषित CONFIG_CB710_DEBUG
	u32 e, x;
	e = cb710_पढ़ो_port_32(slot, CB710_MMC_STATUS_PORT);
#पूर्ण_अगर

	जबतक (!(err = cb710_check_event(slot, what))) अणु
		अगर (!--limit) अणु
			cb710_dump_regs(cb710_slot_to_chip(slot),
				CB710_DUMP_REGS_MMC);
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण

#अगर_घोषित CONFIG_CB710_DEBUG
	x = cb710_पढ़ो_port_32(slot, CB710_MMC_STATUS_PORT);

	limit = 2000000 - limit;
	अगर (limit > 100)
		dev_dbg(cb710_slot_dev(slot),
			"WAIT10: waited %d loops, what %d, entry val %08X, exit val %08X\n",
			limit, what, e, x);
#पूर्ण_अगर
	वापस err < 0 ? err : 0;
पूर्ण


अटल पूर्णांक cb710_रुको_जबतक_busy(काष्ठा cb710_slot *slot, uपूर्णांक8_t mask)
अणु
	अचिन्हित limit = 500000;	/* FIXME: real समयout */
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_CB710_DEBUG
	u32 e, x;
	e = cb710_पढ़ो_port_32(slot, CB710_MMC_STATUS_PORT);
#पूर्ण_अगर

	जबतक (cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS2_PORT) & mask) अणु
		अगर (!--limit) अणु
			cb710_dump_regs(cb710_slot_to_chip(slot),
				CB710_DUMP_REGS_MMC);
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण

#अगर_घोषित CONFIG_CB710_DEBUG
	x = cb710_पढ़ो_port_32(slot, CB710_MMC_STATUS_PORT);

	limit = 500000 - limit;
	अगर (limit > 100)
		dev_dbg(cb710_slot_dev(slot),
			"WAIT12: waited %d loops, mask %02X, entry val %08X, exit val %08X\n",
			limit, mask, e, x);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम cb710_mmc_set_transfer_size(काष्ठा cb710_slot *slot,
	माप_प्रकार count, माप_प्रकार blocksize)
अणु
	cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	cb710_ग_लिखो_port_32(slot, CB710_MMC_TRANSFER_SIZE_PORT,
		((count - 1) << 16)|(blocksize - 1));

	dev_vdbg(cb710_slot_dev(slot), "set up for %zu block%s of %zu bytes\n",
		count, count == 1 ? "" : "s", blocksize);
पूर्ण

अटल व्योम cb710_mmc_fअगरo_hack(काष्ठा cb710_slot *slot)
अणु
	/* without this, received data is prepended with 8-bytes of zeroes */
	u32 r1, r2;
	पूर्णांक ok = 0;

	r1 = cb710_पढ़ो_port_32(slot, CB710_MMC_DATA_PORT);
	r2 = cb710_पढ़ो_port_32(slot, CB710_MMC_DATA_PORT);
	अगर (cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS0_PORT)
	    & CB710_MMC_S0_FIFO_UNDERFLOW) अणु
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS0_PORT,
			CB710_MMC_S0_FIFO_UNDERFLOW);
		ok = 1;
	पूर्ण

	dev_dbg(cb710_slot_dev(slot),
		"FIFO-read-hack: expected STATUS0 bit was %s\n",
		ok ? "set." : "NOT SET!");
	dev_dbg(cb710_slot_dev(slot),
		"FIFO-read-hack: dwords ignored: %08X %08X - %s\n",
		r1, r2, (r1|r2) ? "BAD (NOT ZERO)!" : "ok");
पूर्ण

अटल पूर्णांक cb710_mmc_receive_pio(काष्ठा cb710_slot *slot,
	काष्ठा sg_mapping_iter *miter, माप_प्रकार dw_count)
अणु
	अगर (!(cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS2_PORT) & CB710_MMC_S2_FIFO_READY)) अणु
		पूर्णांक err = cb710_रुको_क्रम_event(slot,
			CB710_MMC_S1_PIO_TRANSFER_DONE);
		अगर (err)
			वापस err;
	पूर्ण

	cb710_sg_dwiter_ग_लिखो_from_io(miter,
		slot->iobase + CB710_MMC_DATA_PORT, dw_count);

	वापस 0;
पूर्ण

अटल bool cb710_is_transfer_size_supported(काष्ठा mmc_data *data)
अणु
	वापस !(data->blksz & 15 && (data->blocks != 1 || data->blksz != 8));
पूर्ण

अटल पूर्णांक cb710_mmc_receive(काष्ठा cb710_slot *slot, काष्ठा mmc_data *data)
अणु
	काष्ठा sg_mapping_iter miter;
	माप_प्रकार len, blocks = data->blocks;
	पूर्णांक err = 0;

	/* TODO: I करोn't know how/अगर the hardware handles non-16B-boundary blocks
	 * except single 8B block */
	अगर (unlikely(data->blksz & 15 && (data->blocks != 1 || data->blksz != 8)))
		वापस -EINVAL;

	sg_miter_start(&miter, data->sg, data->sg_len, SG_MITER_TO_SG);

	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG2_PORT,
		15, CB710_MMC_C2_READ_PIO_SIZE_MASK);

	cb710_mmc_fअगरo_hack(slot);

	जबतक (blocks-- > 0) अणु
		len = data->blksz;

		जबतक (len >= 16) अणु
			err = cb710_mmc_receive_pio(slot, &miter, 4);
			अगर (err)
				जाओ out;
			len -= 16;
		पूर्ण

		अगर (!len)
			जारी;

		cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG2_PORT,
			len - 1, CB710_MMC_C2_READ_PIO_SIZE_MASK);

		len = (len >= 8) ? 4 : 2;
		err = cb710_mmc_receive_pio(slot, &miter, len);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	sg_miter_stop(&miter);
	वापस err;
पूर्ण

अटल पूर्णांक cb710_mmc_send(काष्ठा cb710_slot *slot, काष्ठा mmc_data *data)
अणु
	काष्ठा sg_mapping_iter miter;
	माप_प्रकार len, blocks = data->blocks;
	पूर्णांक err = 0;

	/* TODO: I करोn't know how/अगर the hardware handles multiple
	 * non-16B-boundary blocks */
	अगर (unlikely(data->blocks > 1 && data->blksz & 15))
		वापस -EINVAL;

	sg_miter_start(&miter, data->sg, data->sg_len, SG_MITER_FROM_SG);

	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG2_PORT,
		0, CB710_MMC_C2_READ_PIO_SIZE_MASK);

	जबतक (blocks-- > 0) अणु
		len = (data->blksz + 15) >> 4;
		करो अणु
			अगर (!(cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS2_PORT)
			    & CB710_MMC_S2_FIFO_EMPTY)) अणु
				err = cb710_रुको_क्रम_event(slot,
					CB710_MMC_S1_PIO_TRANSFER_DONE);
				अगर (err)
					जाओ out;
			पूर्ण
			cb710_sg_dwiter_पढ़ो_to_io(&miter,
				slot->iobase + CB710_MMC_DATA_PORT, 4);
		पूर्ण जबतक (--len);
	पूर्ण
out:
	sg_miter_stop(&miter);
	वापस err;
पूर्ण

अटल u16 cb710_encode_cmd_flags(काष्ठा cb710_mmc_पढ़ोer *पढ़ोer,
	काष्ठा mmc_command *cmd)
अणु
	अचिन्हित पूर्णांक flags = cmd->flags;
	u16 cb_flags = 0;

	/* Winकरोws driver वापसed 0 क्रम commands क्रम which no response
	 * is expected. It happened that there were only two such commands
	 * used: MMC_GO_IDLE_STATE and MMC_GO_INACTIVE_STATE so it might
	 * as well be a bug in that driver.
	 *
	 * Original driver set bit 14 क्रम MMC/SD application
	 * commands. There's no difference 'on the wire' and
	 * it apparently works without it anyway.
	 */

	चयन (flags & MMC_CMD_MASK) अणु
	हाल MMC_CMD_AC:	cb_flags = CB710_MMC_CMD_AC;	अवरोध;
	हाल MMC_CMD_ADTC:	cb_flags = CB710_MMC_CMD_ADTC;	अवरोध;
	हाल MMC_CMD_BC:	cb_flags = CB710_MMC_CMD_BC;	अवरोध;
	हाल MMC_CMD_BCR:	cb_flags = CB710_MMC_CMD_BCR;	अवरोध;
	पूर्ण

	अगर (flags & MMC_RSP_BUSY)
		cb_flags |= CB710_MMC_RSP_BUSY;

	cb_flags |= cmd->opcode << CB710_MMC_CMD_CODE_SHIFT;

	अगर (cmd->data && (cmd->data->flags & MMC_DATA_READ))
		cb_flags |= CB710_MMC_DATA_READ;

	अगर (flags & MMC_RSP_PRESENT) अणु
		/* Winकरोws driver set 01 at bits 4,3 except क्रम
		 * MMC_SET_BLOCKLEN where it set 10. Maybe the
		 * hardware can करो something special about this
		 * command? The original driver looks buggy/incomplete
		 * anyway so we ignore this क्रम now.
		 *
		 * I assume that 00 here means no response is expected.
		 */
		cb_flags |= CB710_MMC_RSP_PRESENT;

		अगर (flags & MMC_RSP_136)
			cb_flags |= CB710_MMC_RSP_136;
		अगर (!(flags & MMC_RSP_CRC))
			cb_flags |= CB710_MMC_RSP_NO_CRC;
	पूर्ण

	वापस cb_flags;
पूर्ण

अटल व्योम cb710_receive_response(काष्ठा cb710_slot *slot,
	काष्ठा mmc_command *cmd)
अणु
	अचिन्हित rsp_opcode, wanted_opcode;

	/* Looks like final byte with CRC is always stripped (same as SDHCI) */
	अगर (cmd->flags & MMC_RSP_136) अणु
		u32 resp[4];

		resp[0] = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE3_PORT);
		resp[1] = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE2_PORT);
		resp[2] = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE1_PORT);
		resp[3] = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE0_PORT);
		rsp_opcode = resp[0] >> 24;

		cmd->resp[0] = (resp[0] << 8)|(resp[1] >> 24);
		cmd->resp[1] = (resp[1] << 8)|(resp[2] >> 24);
		cmd->resp[2] = (resp[2] << 8)|(resp[3] >> 24);
		cmd->resp[3] = (resp[3] << 8);
	पूर्ण अन्यथा अणु
		rsp_opcode = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE1_PORT) & 0x3F;
		cmd->resp[0] = cb710_पढ़ो_port_32(slot, CB710_MMC_RESPONSE0_PORT);
	पूर्ण

	wanted_opcode = (cmd->flags & MMC_RSP_OPCODE) ? cmd->opcode : 0x3F;
	अगर (rsp_opcode != wanted_opcode)
		cmd->error = -EILSEQ;
पूर्ण

अटल पूर्णांक cb710_mmc_transfer_data(काष्ठा cb710_slot *slot,
	काष्ठा mmc_data *data)
अणु
	पूर्णांक error, to;

	अगर (data->flags & MMC_DATA_READ)
		error = cb710_mmc_receive(slot, data);
	अन्यथा
		error = cb710_mmc_send(slot, data);

	to = cb710_रुको_क्रम_event(slot, CB710_MMC_S1_DATA_TRANSFER_DONE);
	अगर (!error)
		error = to;

	अगर (!error)
		data->bytes_xfered = data->blksz * data->blocks;
	वापस error;
पूर्ण

अटल पूर्णांक cb710_mmc_command(काष्ठा mmc_host *mmc, काष्ठा mmc_command *cmd)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(mmc);
	काष्ठा mmc_data *data = cmd->data;

	u16 cb_cmd = cb710_encode_cmd_flags(पढ़ोer, cmd);
	dev_dbg(cb710_slot_dev(slot), "cmd request: 0x%04X\n", cb_cmd);

	अगर (data) अणु
		अगर (!cb710_is_transfer_size_supported(data)) अणु
			data->error = -EINVAL;
			वापस -1;
		पूर्ण
		cb710_mmc_set_transfer_size(slot, data->blocks, data->blksz);
	पूर्ण

	cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20|CB710_MMC_S2_BUSY_10);
	cb710_ग_लिखो_port_16(slot, CB710_MMC_CMD_TYPE_PORT, cb_cmd);
	cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	cb710_ग_लिखो_port_32(slot, CB710_MMC_CMD_PARAM_PORT, cmd->arg);
	cb710_mmc_reset_events(slot);
	cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG0_PORT, 0x01, 0);

	cmd->error = cb710_रुको_क्रम_event(slot, CB710_MMC_S1_COMMAND_SENT);
	अगर (cmd->error)
		वापस -1;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		cb710_receive_response(slot, cmd);
		अगर (cmd->error)
			वापस -1;
	पूर्ण

	अगर (data)
		data->error = cb710_mmc_transfer_data(slot, data);
	वापस 0;
पूर्ण

अटल व्योम cb710_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(mmc);

	WARN_ON(पढ़ोer->mrq != शून्य);

	पढ़ोer->mrq = mrq;
	cb710_mmc_enable_irq(slot, CB710_MMC_IE_TEST_MASK, 0);

	अगर (!cb710_mmc_command(mmc, mrq->cmd) && mrq->stop)
		cb710_mmc_command(mmc, mrq->stop);

	tasklet_schedule(&पढ़ोer->finish_req_tasklet);
पूर्ण

अटल पूर्णांक cb710_mmc_घातerup(काष्ठा cb710_slot *slot)
अणु
#अगर_घोषित CONFIG_CB710_DEBUG
	काष्ठा cb710_chip *chip = cb710_slot_to_chip(slot);
#पूर्ण_अगर
	पूर्णांक err;

	/* a lot of magic क्रम now */
	dev_dbg(cb710_slot_dev(slot), "bus powerup\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	अगर (unlikely(err))
		वापस err;
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x80, 0);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG3_PORT, 0x80, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(1);
	dev_dbg(cb710_slot_dev(slot), "after delay 1\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	अगर (unlikely(err))
		वापस err;
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x09, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(1);
	dev_dbg(cb710_slot_dev(slot), "after delay 2\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	अगर (unlikely(err))
		वापस err;
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT, 0, 0x08);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(2);
	dev_dbg(cb710_slot_dev(slot), "after delay 3\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG0_PORT, 0x06, 0);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x70, 0);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG2_PORT, 0x80, 0);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG3_PORT, 0x03, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_रुको_जबतक_busy(slot, CB710_MMC_S2_BUSY_20);
	अगर (unlikely(err))
		वापस err;
	/* This port behaves weird: quick byte पढ़ोs of 0x08,0x09 वापस
	 * 0xFF,0x00 after writing 0xFFFF to 0x08; it works correctly when
	 * पढ़ो/written from userspace...  What am I missing here?
	 * (it करोesn't depend on ग_लिखो-to-पढ़ो delay) */
	cb710_ग_लिखो_port_16(slot, CB710_MMC_CONFIGB_PORT, 0xFFFF);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG0_PORT, 0x06, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	dev_dbg(cb710_slot_dev(slot), "bus powerup finished\n");

	वापस cb710_check_event(slot, 0);
पूर्ण

अटल व्योम cb710_mmc_घातerकरोwn(काष्ठा cb710_slot *slot)
अणु
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG1_PORT, 0, 0x81);
	cb710_modअगरy_port_8(slot, CB710_MMC_CONFIG3_PORT, 0, 0x80);
पूर्ण

अटल व्योम cb710_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(mmc);
	पूर्णांक err;

	cb710_mmc_select_घड़ी_भागider(mmc, ios->घड़ी);

	अगर (ios->घातer_mode != पढ़ोer->last_घातer_mode) अणु
		चयन (ios->घातer_mode) अणु
		हाल MMC_POWER_ON:
			err = cb710_mmc_घातerup(slot);
			अगर (err) अणु
				dev_warn(cb710_slot_dev(slot),
					"powerup failed (%d)- retrying\n", err);
				cb710_mmc_घातerकरोwn(slot);
				udelay(1);
				err = cb710_mmc_घातerup(slot);
				अगर (err)
					dev_warn(cb710_slot_dev(slot),
						"powerup retry failed (%d) - expect errors\n",
					err);
			पूर्ण
			पढ़ोer->last_घातer_mode = MMC_POWER_ON;
			अवरोध;
		हाल MMC_POWER_OFF:
			cb710_mmc_घातerकरोwn(slot);
			पढ़ोer->last_घातer_mode = MMC_POWER_OFF;
			अवरोध;
		हाल MMC_POWER_UP:
		शेष:
			/* ignore */
			अवरोध;
		पूर्ण
	पूर्ण

	cb710_mmc_enable_4bit_data(slot, ios->bus_width != MMC_BUS_WIDTH_1);

	cb710_mmc_enable_irq(slot, CB710_MMC_IE_TEST_MASK, 0);
पूर्ण

अटल पूर्णांक cb710_mmc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);

	वापस cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS3_PORT)
		& CB710_MMC_S3_WRITE_PROTECTED;
पूर्ण

अटल पूर्णांक cb710_mmc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cb710_slot *slot = cb710_mmc_to_slot(mmc);

	वापस cb710_पढ़ो_port_8(slot, CB710_MMC_STATUS3_PORT)
		& CB710_MMC_S3_CARD_DETECTED;
पूर्ण

अटल पूर्णांक cb710_mmc_irq_handler(काष्ठा cb710_slot *slot)
अणु
	काष्ठा mmc_host *mmc = cb710_slot_to_mmc(slot);
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(mmc);
	u32 status, config1, config2, irqen;

	status = cb710_पढ़ो_port_32(slot, CB710_MMC_STATUS_PORT);
	irqen = cb710_पढ़ो_port_32(slot, CB710_MMC_IRQ_ENABLE_PORT);
	config2 = cb710_पढ़ो_port_32(slot, CB710_MMC_CONFIGB_PORT);
	config1 = cb710_पढ़ो_port_32(slot, CB710_MMC_CONFIG_PORT);

	dev_dbg(cb710_slot_dev(slot), "interrupt; status: %08X, "
		"ie: %08X, c2: %08X, c1: %08X\n",
		status, irqen, config2, config1);

	अगर (status & (CB710_MMC_S1_CARD_CHANGED << 8)) अणु
		/* ack the event */
		cb710_ग_लिखो_port_8(slot, CB710_MMC_STATUS1_PORT,
			CB710_MMC_S1_CARD_CHANGED);
		अगर ((irqen & CB710_MMC_IE_CISTATUS_MASK)
		    == CB710_MMC_IE_CISTATUS_MASK)
			mmc_detect_change(mmc, HZ/5);
	पूर्ण अन्यथा अणु
		dev_dbg(cb710_slot_dev(slot), "unknown interrupt (test)\n");
		spin_lock(&पढ़ोer->irq_lock);
		__cb710_mmc_enable_irq(slot, 0, CB710_MMC_IE_TEST_MASK);
		spin_unlock(&पढ़ोer->irq_lock);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम cb710_mmc_finish_request_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = from_tasklet(पढ़ोer, t,
						       finish_req_tasklet);
	काष्ठा mmc_request *mrq = पढ़ोer->mrq;

	पढ़ोer->mrq = शून्य;
	mmc_request_करोne(mmc_from_priv(पढ़ोer), mrq);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops cb710_mmc_host = अणु
	.request = cb710_mmc_request,
	.set_ios = cb710_mmc_set_ios,
	.get_ro = cb710_mmc_get_ro,
	.get_cd = cb710_mmc_get_cd,
पूर्ण;

#अगर_घोषित CONFIG_PM

अटल पूर्णांक cb710_mmc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा cb710_slot *slot = cb710_pdev_to_slot(pdev);

	cb710_mmc_enable_irq(slot, 0, ~0);
	वापस 0;
पूर्ण

अटल पूर्णांक cb710_mmc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cb710_slot *slot = cb710_pdev_to_slot(pdev);

	cb710_mmc_enable_irq(slot, 0, ~0);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक cb710_mmc_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cb710_slot *slot = cb710_pdev_to_slot(pdev);
	काष्ठा cb710_chip *chip = cb710_slot_to_chip(slot);
	काष्ठा mmc_host *mmc;
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer;
	पूर्णांक err;
	u32 val;

	mmc = mmc_alloc_host(माप(*पढ़ोer), cb710_slot_dev(slot));
	अगर (!mmc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mmc);

	/* harmless (maybe) magic */
	pci_पढ़ो_config_dword(chip->pdev, 0x48, &val);
	val = cb710_src_freq_mhz[(val >> 16) & 0xF];
	dev_dbg(cb710_slot_dev(slot), "source frequency: %dMHz\n", val);
	val *= 1000000;

	mmc->ops = &cb710_mmc_host;
	mmc->f_max = val;
	mmc->f_min = val >> cb710_घड़ी_भागider_log2[CB710_MAX_DIVIDER_IDX];
	mmc->ocr_avail = MMC_VDD_32_33|MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;
	/*
	 * In cb710_रुको_क्रम_event() we use a fixed समयout of ~2s, hence let's
	 * inक्रमm the core about it. A future improvement should instead make
	 * use of the cmd->busy_समयout.
	 */
	mmc->max_busy_समयout = CB710_MMC_REQ_TIMEOUT_MS;

	पढ़ोer = mmc_priv(mmc);

	tasklet_setup(&पढ़ोer->finish_req_tasklet,
		      cb710_mmc_finish_request_tasklet);
	spin_lock_init(&पढ़ोer->irq_lock);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);

	cb710_mmc_enable_irq(slot, 0, ~0);
	cb710_set_irq_handler(slot, cb710_mmc_irq_handler);

	err = mmc_add_host(mmc);
	अगर (unlikely(err))
		जाओ err_मुक्त_mmc;

	dev_dbg(cb710_slot_dev(slot), "mmc_hostname is %s\n",
		mmc_hostname(mmc));

	cb710_mmc_enable_irq(slot, CB710_MMC_IE_CARD_INSERTION_STATUS, 0);

	वापस 0;

err_मुक्त_mmc:
	dev_dbg(cb710_slot_dev(slot), "mmc_add_host() failed: %d\n", err);

	cb710_set_irq_handler(slot, शून्य);
	mmc_मुक्त_host(mmc);
	वापस err;
पूर्ण

अटल पूर्णांक cb710_mmc_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cb710_slot *slot = cb710_pdev_to_slot(pdev);
	काष्ठा mmc_host *mmc = cb710_slot_to_mmc(slot);
	काष्ठा cb710_mmc_पढ़ोer *पढ़ोer = mmc_priv(mmc);

	cb710_mmc_enable_irq(slot, 0, CB710_MMC_IE_CARD_INSERTION_STATUS);

	mmc_हटाओ_host(mmc);

	/* IRQs should be disabled now, but let's stay on the safe side */
	cb710_mmc_enable_irq(slot, 0, ~0);
	cb710_set_irq_handler(slot, शून्य);

	/* clear config ports - just in हाल */
	cb710_ग_लिखो_port_32(slot, CB710_MMC_CONFIG_PORT, 0);
	cb710_ग_लिखो_port_16(slot, CB710_MMC_CONFIGB_PORT, 0);

	tasklet_समाप्त(&पढ़ोer->finish_req_tasklet);

	mmc_मुक्त_host(mmc);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cb710_mmc_driver = अणु
	.driver.name = "cb710-mmc",
	.probe = cb710_mmc_init,
	.हटाओ = cb710_mmc_निकास,
#अगर_घोषित CONFIG_PM
	.suspend = cb710_mmc_suspend,
	.resume = cb710_mmc_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(cb710_mmc_driver);

MODULE_AUTHOR("Michaध Mirosधaw <mirq-linux@rere.qmqm.pl>");
MODULE_DESCRIPTION("ENE CB710 memory card reader driver - MMC/SD part");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cb710-mmc");
