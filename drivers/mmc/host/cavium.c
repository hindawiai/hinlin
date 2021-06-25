<शैली गुरु>
/*
 * Shared part of driver क्रम MMC/SDHC controller on Cavium OCTEON and
 * ThunderX SOCs.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012-2017 Cavium Inc.
 * Authors:
 *   David Daney <david.daney@cavium.com>
 *   Peter Swain <pswain@cavium.com>
 *   Steven J. Hill <steven.hill@cavium.com>
 *   Jan Glauber <jglauber@cavium.com>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/समय.स>

#समावेश "cavium.h"

स्थिर अक्षर *cvm_mmc_irq_names[] = अणु
	"MMC Buffer",
	"MMC Command",
	"MMC DMA",
	"MMC Command Error",
	"MMC DMA Error",
	"MMC Switch",
	"MMC Switch Error",
	"MMC DMA int Fifo",
	"MMC DMA int",
पूर्ण;

/*
 * The Cavium MMC host hardware assumes that all commands have fixed
 * command and response types.  These are correct अगर MMC devices are
 * being used.  However, non-MMC devices like SD use command and
 * response types that are unexpected by the host hardware.
 *
 * The command and response types can be overridden by supplying an
 * XOR value that is applied to the type.  We calculate the XOR value
 * from the values in this table and the flags passed from the MMC
 * core.
 */
अटल काष्ठा cvm_mmc_cr_type cvm_mmc_cr_types[] = अणु
	अणु0, 0पूर्ण,		/* CMD0 */
	अणु0, 3पूर्ण,		/* CMD1 */
	अणु0, 2पूर्ण,		/* CMD2 */
	अणु0, 1पूर्ण,		/* CMD3 */
	अणु0, 0पूर्ण,		/* CMD4 */
	अणु0, 1पूर्ण,		/* CMD5 */
	अणु0, 1पूर्ण,		/* CMD6 */
	अणु0, 1पूर्ण,		/* CMD7 */
	अणु1, 1पूर्ण,		/* CMD8 */
	अणु0, 2पूर्ण,		/* CMD9 */
	अणु0, 2पूर्ण,		/* CMD10 */
	अणु1, 1पूर्ण,		/* CMD11 */
	अणु0, 1पूर्ण,		/* CMD12 */
	अणु0, 1पूर्ण,		/* CMD13 */
	अणु1, 1पूर्ण,		/* CMD14 */
	अणु0, 0पूर्ण,		/* CMD15 */
	अणु0, 1पूर्ण,		/* CMD16 */
	अणु1, 1पूर्ण,		/* CMD17 */
	अणु1, 1पूर्ण,		/* CMD18 */
	अणु3, 1पूर्ण,		/* CMD19 */
	अणु2, 1पूर्ण,		/* CMD20 */
	अणु0, 0पूर्ण,		/* CMD21 */
	अणु0, 0पूर्ण,		/* CMD22 */
	अणु0, 1पूर्ण,		/* CMD23 */
	अणु2, 1पूर्ण,		/* CMD24 */
	अणु2, 1पूर्ण,		/* CMD25 */
	अणु2, 1पूर्ण,		/* CMD26 */
	अणु2, 1पूर्ण,		/* CMD27 */
	अणु0, 1पूर्ण,		/* CMD28 */
	अणु0, 1पूर्ण,		/* CMD29 */
	अणु1, 1पूर्ण,		/* CMD30 */
	अणु1, 1पूर्ण,		/* CMD31 */
	अणु0, 0पूर्ण,		/* CMD32 */
	अणु0, 0पूर्ण,		/* CMD33 */
	अणु0, 0पूर्ण,		/* CMD34 */
	अणु0, 1पूर्ण,		/* CMD35 */
	अणु0, 1पूर्ण,		/* CMD36 */
	अणु0, 0पूर्ण,		/* CMD37 */
	अणु0, 1पूर्ण,		/* CMD38 */
	अणु0, 4पूर्ण,		/* CMD39 */
	अणु0, 5पूर्ण,		/* CMD40 */
	अणु0, 0पूर्ण,		/* CMD41 */
	अणु2, 1पूर्ण,		/* CMD42 */
	अणु0, 0पूर्ण,		/* CMD43 */
	अणु0, 0पूर्ण,		/* CMD44 */
	अणु0, 0पूर्ण,		/* CMD45 */
	अणु0, 0पूर्ण,		/* CMD46 */
	अणु0, 0पूर्ण,		/* CMD47 */
	अणु0, 0पूर्ण,		/* CMD48 */
	अणु0, 0पूर्ण,		/* CMD49 */
	अणु0, 0पूर्ण,		/* CMD50 */
	अणु0, 0पूर्ण,		/* CMD51 */
	अणु0, 0पूर्ण,		/* CMD52 */
	अणु0, 0पूर्ण,		/* CMD53 */
	अणु0, 0पूर्ण,		/* CMD54 */
	अणु0, 1पूर्ण,		/* CMD55 */
	अणु0xff, 0xffपूर्ण,	/* CMD56 */
	अणु0, 0पूर्ण,		/* CMD57 */
	अणु0, 0पूर्ण,		/* CMD58 */
	अणु0, 0पूर्ण,		/* CMD59 */
	अणु0, 0पूर्ण,		/* CMD60 */
	अणु0, 0पूर्ण,		/* CMD61 */
	अणु0, 0पूर्ण,		/* CMD62 */
	अणु0, 0पूर्ण		/* CMD63 */
पूर्ण;

अटल काष्ठा cvm_mmc_cr_mods cvm_mmc_get_cr_mods(काष्ठा mmc_command *cmd)
अणु
	काष्ठा cvm_mmc_cr_type *cr;
	u8 hardware_ctype, hardware_rtype;
	u8 desired_ctype = 0, desired_rtype = 0;
	काष्ठा cvm_mmc_cr_mods r;

	cr = cvm_mmc_cr_types + (cmd->opcode & 0x3f);
	hardware_ctype = cr->ctype;
	hardware_rtype = cr->rtype;
	अगर (cmd->opcode == MMC_GEN_CMD)
		hardware_ctype = (cmd->arg & 1) ? 1 : 2;

	चयन (mmc_cmd_type(cmd)) अणु
	हाल MMC_CMD_ADTC:
		desired_ctype = (cmd->data->flags & MMC_DATA_WRITE) ? 2 : 1;
		अवरोध;
	हाल MMC_CMD_AC:
	हाल MMC_CMD_BC:
	हाल MMC_CMD_BCR:
		desired_ctype = 0;
		अवरोध;
	पूर्ण

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		desired_rtype = 0;
		अवरोध;
	हाल MMC_RSP_R1:/* MMC_RSP_R5, MMC_RSP_R6, MMC_RSP_R7 */
	हाल MMC_RSP_R1B:
		desired_rtype = 1;
		अवरोध;
	हाल MMC_RSP_R2:
		desired_rtype = 2;
		अवरोध;
	हाल MMC_RSP_R3: /* MMC_RSP_R4 */
		desired_rtype = 3;
		अवरोध;
	पूर्ण
	r.ctype_xor = desired_ctype ^ hardware_ctype;
	r.rtype_xor = desired_rtype ^ hardware_rtype;
	वापस r;
पूर्ण

अटल व्योम check_चयन_errors(काष्ठा cvm_mmc_host *host)
अणु
	u64 emm_चयन;

	emm_चयन = पढ़ोq(host->base + MIO_EMM_SWITCH(host));
	अगर (emm_चयन & MIO_EMM_SWITCH_ERR0)
		dev_err(host->dev, "Switch power class error\n");
	अगर (emm_चयन & MIO_EMM_SWITCH_ERR1)
		dev_err(host->dev, "Switch hs timing error\n");
	अगर (emm_चयन & MIO_EMM_SWITCH_ERR2)
		dev_err(host->dev, "Switch bus width error\n");
पूर्ण

अटल व्योम clear_bus_id(u64 *reg)
अणु
	u64 bus_id_mask = GENMASK_ULL(61, 60);

	*reg &= ~bus_id_mask;
पूर्ण

अटल व्योम set_bus_id(u64 *reg, पूर्णांक bus_id)
अणु
	clear_bus_id(reg);
	*reg |= FIELD_PREP(GENMASK(61, 60), bus_id);
पूर्ण

अटल पूर्णांक get_bus_id(u64 reg)
अणु
	वापस FIELD_GET(GENMASK_ULL(61, 60), reg);
पूर्ण

/*
 * We never set the चयन_exe bit since that would पूर्णांकerfere
 * with the commands send by the MMC core.
 */
अटल व्योम करो_चयन(काष्ठा cvm_mmc_host *host, u64 emm_चयन)
अणु
	पूर्णांक retries = 100;
	u64 rsp_sts;
	पूर्णांक bus_id;

	/*
	 * Modes setting only taken from slot 0. Work around that hardware
	 * issue by first चयनing to slot 0.
	 */
	bus_id = get_bus_id(emm_चयन);
	clear_bus_id(&emm_चयन);
	ग_लिखोq(emm_चयन, host->base + MIO_EMM_SWITCH(host));

	set_bus_id(&emm_चयन, bus_id);
	ग_लिखोq(emm_चयन, host->base + MIO_EMM_SWITCH(host));

	/* रुको क्रम the चयन to finish */
	करो अणु
		rsp_sts = पढ़ोq(host->base + MIO_EMM_RSP_STS(host));
		अगर (!(rsp_sts & MIO_EMM_RSP_STS_SWITCH_VAL))
			अवरोध;
		udelay(10);
	पूर्ण जबतक (--retries);

	check_चयन_errors(host);
पूर्ण

अटल bool चयन_val_changed(काष्ठा cvm_mmc_slot *slot, u64 new_val)
अणु
	/* Match BUS_ID, HS_TIMING, BUS_WIDTH, POWER_CLASS, CLK_HI, CLK_LO */
	u64 match = 0x3001070fffffffffull;

	वापस (slot->cached_चयन & match) != (new_val & match);
पूर्ण

अटल व्योम set_wकरोg(काष्ठा cvm_mmc_slot *slot, अचिन्हित पूर्णांक ns)
अणु
	u64 समयout;

	अगर (!slot->घड़ी)
		वापस;

	अगर (ns)
		समयout = (slot->घड़ी * ns) / NSEC_PER_SEC;
	अन्यथा
		समयout = (slot->घड़ी * 850ull) / 1000ull;
	ग_लिखोq(समयout, slot->host->base + MIO_EMM_WDOG(slot->host));
पूर्ण

अटल व्योम cvm_mmc_reset_bus(काष्ठा cvm_mmc_slot *slot)
अणु
	काष्ठा cvm_mmc_host *host = slot->host;
	u64 emm_चयन, wकरोg;

	emm_चयन = पढ़ोq(slot->host->base + MIO_EMM_SWITCH(host));
	emm_चयन &= ~(MIO_EMM_SWITCH_EXE | MIO_EMM_SWITCH_ERR0 |
			MIO_EMM_SWITCH_ERR1 | MIO_EMM_SWITCH_ERR2);
	set_bus_id(&emm_चयन, slot->bus_id);

	wकरोg = पढ़ोq(slot->host->base + MIO_EMM_WDOG(host));
	करो_चयन(slot->host, emm_चयन);

	slot->cached_चयन = emm_चयन;

	msleep(20);

	ग_लिखोq(wकरोg, slot->host->base + MIO_EMM_WDOG(host));
पूर्ण

/* Switch to another slot अगर needed */
अटल व्योम cvm_mmc_चयन_to(काष्ठा cvm_mmc_slot *slot)
अणु
	काष्ठा cvm_mmc_host *host = slot->host;
	काष्ठा cvm_mmc_slot *old_slot;
	u64 emm_sample, emm_चयन;

	अगर (slot->bus_id == host->last_slot)
		वापस;

	अगर (host->last_slot >= 0 && host->slot[host->last_slot]) अणु
		old_slot = host->slot[host->last_slot];
		old_slot->cached_चयन = पढ़ोq(host->base + MIO_EMM_SWITCH(host));
		old_slot->cached_rca = पढ़ोq(host->base + MIO_EMM_RCA(host));
	पूर्ण

	ग_लिखोq(slot->cached_rca, host->base + MIO_EMM_RCA(host));
	emm_चयन = slot->cached_चयन;
	set_bus_id(&emm_चयन, slot->bus_id);
	करो_चयन(host, emm_चयन);

	emm_sample = FIELD_PREP(MIO_EMM_SAMPLE_CMD_CNT, slot->cmd_cnt) |
		     FIELD_PREP(MIO_EMM_SAMPLE_DAT_CNT, slot->dat_cnt);
	ग_लिखोq(emm_sample, host->base + MIO_EMM_SAMPLE(host));

	host->last_slot = slot->bus_id;
पूर्ण

अटल व्योम करो_पढ़ो(काष्ठा cvm_mmc_host *host, काष्ठा mmc_request *req,
		    u64 dbuf)
अणु
	काष्ठा sg_mapping_iter *smi = &host->smi;
	पूर्णांक data_len = req->data->blocks * req->data->blksz;
	पूर्णांक bytes_xfered, shअगरt = -1;
	u64 dat = 0;

	/* Auto inc from offset zero */
	ग_लिखोq((0x10000 | (dbuf << 6)), host->base + MIO_EMM_BUF_IDX(host));

	क्रम (bytes_xfered = 0; bytes_xfered < data_len;) अणु
		अगर (smi->consumed >= smi->length) अणु
			अगर (!sg_miter_next(smi))
				अवरोध;
			smi->consumed = 0;
		पूर्ण

		अगर (shअगरt < 0) अणु
			dat = पढ़ोq(host->base + MIO_EMM_BUF_DAT(host));
			shअगरt = 56;
		पूर्ण

		जबतक (smi->consumed < smi->length && shअगरt >= 0) अणु
			((u8 *)smi->addr)[smi->consumed] = (dat >> shअगरt) & 0xff;
			bytes_xfered++;
			smi->consumed++;
			shअगरt -= 8;
		पूर्ण
	पूर्ण

	sg_miter_stop(smi);
	req->data->bytes_xfered = bytes_xfered;
	req->data->error = 0;
पूर्ण

अटल व्योम करो_ग_लिखो(काष्ठा mmc_request *req)
अणु
	req->data->bytes_xfered = req->data->blocks * req->data->blksz;
	req->data->error = 0;
पूर्ण

अटल व्योम set_cmd_response(काष्ठा cvm_mmc_host *host, काष्ठा mmc_request *req,
			     u64 rsp_sts)
अणु
	u64 rsp_hi, rsp_lo;

	अगर (!(rsp_sts & MIO_EMM_RSP_STS_RSP_VAL))
		वापस;

	rsp_lo = पढ़ोq(host->base + MIO_EMM_RSP_LO(host));

	चयन (FIELD_GET(MIO_EMM_RSP_STS_RSP_TYPE, rsp_sts)) अणु
	हाल 1:
	हाल 3:
		req->cmd->resp[0] = (rsp_lo >> 8) & 0xffffffff;
		req->cmd->resp[1] = 0;
		req->cmd->resp[2] = 0;
		req->cmd->resp[3] = 0;
		अवरोध;
	हाल 2:
		req->cmd->resp[3] = rsp_lo & 0xffffffff;
		req->cmd->resp[2] = (rsp_lo >> 32) & 0xffffffff;
		rsp_hi = पढ़ोq(host->base + MIO_EMM_RSP_HI(host));
		req->cmd->resp[1] = rsp_hi & 0xffffffff;
		req->cmd->resp[0] = (rsp_hi >> 32) & 0xffffffff;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dma_dir(काष्ठा mmc_data *data)
अणु
	वापस (data->flags & MMC_DATA_WRITE) ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
पूर्ण

अटल पूर्णांक finish_dma_single(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	data->bytes_xfered = data->blocks * data->blksz;
	data->error = 0;
	dma_unmap_sg(host->dev, data->sg, data->sg_len, get_dma_dir(data));
	वापस 1;
पूर्ण

अटल पूर्णांक finish_dma_sg(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	u64 fअगरo_cfg;
	पूर्णांक count;

	/* Check अगर there are any pending requests left */
	fअगरo_cfg = पढ़ोq(host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	count = FIELD_GET(MIO_EMM_DMA_FIFO_CFG_COUNT, fअगरo_cfg);
	अगर (count)
		dev_err(host->dev, "%u requests still pending\n", count);

	data->bytes_xfered = data->blocks * data->blksz;
	data->error = 0;

	/* Clear and disable FIFO */
	ग_लिखोq(BIT_ULL(16), host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	dma_unmap_sg(host->dev, data->sg, data->sg_len, get_dma_dir(data));
	वापस 1;
पूर्ण

अटल पूर्णांक finish_dma(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	अगर (host->use_sg && data->sg_len > 1)
		वापस finish_dma_sg(host, data);
	अन्यथा
		वापस finish_dma_single(host, data);
पूर्ण

अटल पूर्णांक check_status(u64 rsp_sts)
अणु
	अगर (rsp_sts & MIO_EMM_RSP_STS_RSP_BAD_STS ||
	    rsp_sts & MIO_EMM_RSP_STS_RSP_CRC_ERR ||
	    rsp_sts & MIO_EMM_RSP_STS_BLK_CRC_ERR)
		वापस -EILSEQ;
	अगर (rsp_sts & MIO_EMM_RSP_STS_RSP_TIMEOUT ||
	    rsp_sts & MIO_EMM_RSP_STS_BLK_TIMEOUT)
		वापस -ETIMEDOUT;
	अगर (rsp_sts & MIO_EMM_RSP_STS_DBUF_ERR)
		वापस -EIO;
	वापस 0;
पूर्ण

/* Try to clean up failed DMA. */
अटल व्योम cleanup_dma(काष्ठा cvm_mmc_host *host, u64 rsp_sts)
अणु
	u64 emm_dma;

	emm_dma = पढ़ोq(host->base + MIO_EMM_DMA(host));
	emm_dma |= FIELD_PREP(MIO_EMM_DMA_VAL, 1) |
		   FIELD_PREP(MIO_EMM_DMA_DAT_शून्य, 1);
	set_bus_id(&emm_dma, get_bus_id(rsp_sts));
	ग_लिखोq(emm_dma, host->base + MIO_EMM_DMA(host));
पूर्ण

irqवापस_t cvm_mmc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cvm_mmc_host *host = dev_id;
	काष्ठा mmc_request *req;
	u64 emm_पूर्णांक, rsp_sts;
	bool host_करोne;

	अगर (host->need_irq_handler_lock)
		spin_lock(&host->irq_handler_lock);
	अन्यथा
		__acquire(&host->irq_handler_lock);

	/* Clear पूर्णांकerrupt bits (ग_लिखो 1 clears ). */
	emm_पूर्णांक = पढ़ोq(host->base + MIO_EMM_INT(host));
	ग_लिखोq(emm_पूर्णांक, host->base + MIO_EMM_INT(host));

	अगर (emm_पूर्णांक & MIO_EMM_INT_SWITCH_ERR)
		check_चयन_errors(host);

	req = host->current_req;
	अगर (!req)
		जाओ out;

	rsp_sts = पढ़ोq(host->base + MIO_EMM_RSP_STS(host));
	/*
	 * dma_val set means DMA is still in progress. Don't touch
	 * the request and रुको क्रम the पूर्णांकerrupt indicating that
	 * the DMA is finished.
	 */
	अगर ((rsp_sts & MIO_EMM_RSP_STS_DMA_VAL) && host->dma_active)
		जाओ out;

	अगर (!host->dma_active && req->data &&
	    (emm_पूर्णांक & MIO_EMM_INT_BUF_DONE)) अणु
		अचिन्हित पूर्णांक type = (rsp_sts >> 7) & 3;

		अगर (type == 1)
			करो_पढ़ो(host, req, rsp_sts & MIO_EMM_RSP_STS_DBUF);
		अन्यथा अगर (type == 2)
			करो_ग_लिखो(req);
	पूर्ण

	host_करोne = emm_पूर्णांक & MIO_EMM_INT_CMD_DONE ||
		    emm_पूर्णांक & MIO_EMM_INT_DMA_DONE ||
		    emm_पूर्णांक & MIO_EMM_INT_CMD_ERR  ||
		    emm_पूर्णांक & MIO_EMM_INT_DMA_ERR;

	अगर (!(host_करोne && req->करोne))
		जाओ no_req_करोne;

	req->cmd->error = check_status(rsp_sts);

	अगर (host->dma_active && req->data)
		अगर (!finish_dma(host, req->data))
			जाओ no_req_करोne;

	set_cmd_response(host, req, rsp_sts);
	अगर ((emm_पूर्णांक & MIO_EMM_INT_DMA_ERR) &&
	    (rsp_sts & MIO_EMM_RSP_STS_DMA_PEND))
		cleanup_dma(host, rsp_sts);

	host->current_req = शून्य;
	req->करोne(req);

no_req_करोne:
	अगर (host->dmar_fixup_करोne)
		host->dmar_fixup_करोne(host);
	अगर (host_करोne)
		host->release_bus(host);
out:
	अगर (host->need_irq_handler_lock)
		spin_unlock(&host->irq_handler_lock);
	अन्यथा
		__release(&host->irq_handler_lock);
	वापस IRQ_RETVAL(emm_पूर्णांक != 0);
पूर्ण

/*
 * Program DMA_CFG and अगर needed DMA_ADR.
 * Returns 0 on error, DMA address otherwise.
 */
अटल u64 prepare_dma_single(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	u64 dma_cfg, addr;
	पूर्णांक count, rw;

	count = dma_map_sg(host->dev, data->sg, data->sg_len,
			   get_dma_dir(data));
	अगर (!count)
		वापस 0;

	rw = (data->flags & MMC_DATA_WRITE) ? 1 : 0;
	dma_cfg = FIELD_PREP(MIO_EMM_DMA_CFG_EN, 1) |
		  FIELD_PREP(MIO_EMM_DMA_CFG_RW, rw);
#अगर_घोषित __LITTLE_ENDIAN
	dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_ENDIAN, 1);
#पूर्ण_अगर
	dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_SIZE,
			      (sg_dma_len(&data->sg[0]) / 8) - 1);

	addr = sg_dma_address(&data->sg[0]);
	अगर (!host->big_dma_addr)
		dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_ADR, addr);
	ग_लिखोq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	pr_debug("[%s] sg_dma_len: %u  total sg_elem: %d\n",
		 (rw) ? "W" : "R", sg_dma_len(&data->sg[0]), count);

	अगर (host->big_dma_addr)
		ग_लिखोq(addr, host->dma_base + MIO_EMM_DMA_ADR(host));
	वापस addr;
पूर्ण

/*
 * Queue complete sg list पूर्णांकo the FIFO.
 * Returns 0 on error, 1 otherwise.
 */
अटल u64 prepare_dma_sg(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg;
	u64 fअगरo_cmd, addr;
	पूर्णांक count, i, rw;

	count = dma_map_sg(host->dev, data->sg, data->sg_len,
			   get_dma_dir(data));
	अगर (!count)
		वापस 0;
	अगर (count > 16)
		जाओ error;

	/* Enable FIFO by removing CLR bit */
	ग_लिखोq(0, host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));

	क्रम_each_sg(data->sg, sg, count, i) अणु
		/* Program DMA address */
		addr = sg_dma_address(sg);
		अगर (addr & 7)
			जाओ error;
		ग_लिखोq(addr, host->dma_base + MIO_EMM_DMA_FIFO_ADR(host));

		/*
		 * If we have scatter-gather support we also have an extra
		 * रेजिस्टर क्रम the DMA addr, so no need to check
		 * host->big_dma_addr here.
		 */
		rw = (data->flags & MMC_DATA_WRITE) ? 1 : 0;
		fअगरo_cmd = FIELD_PREP(MIO_EMM_DMA_FIFO_CMD_RW, rw);

		/* enable पूर्णांकerrupts on the last element */
		fअगरo_cmd |= FIELD_PREP(MIO_EMM_DMA_FIFO_CMD_INTDIS,
				       (i + 1 == count) ? 0 : 1);

#अगर_घोषित __LITTLE_ENDIAN
		fअगरo_cmd |= FIELD_PREP(MIO_EMM_DMA_FIFO_CMD_ENDIAN, 1);
#पूर्ण_अगर
		fअगरo_cmd |= FIELD_PREP(MIO_EMM_DMA_FIFO_CMD_SIZE,
				       sg_dma_len(sg) / 8 - 1);
		/*
		 * The ग_लिखो copies the address and the command to the FIFO
		 * and increments the FIFO's COUNT field.
		 */
		ग_लिखोq(fअगरo_cmd, host->dma_base + MIO_EMM_DMA_FIFO_CMD(host));
		pr_debug("[%s] sg_dma_len: %u  sg_elem: %d/%d\n",
			 (rw) ? "W" : "R", sg_dma_len(sg), i, count);
	पूर्ण

	/*
	 * In dअगरference to prepare_dma_single we करोn't वापस the
	 * address here, as it would not make sense क्रम scatter-gather.
	 * The dma fixup is only required on models that करोn't support
	 * scatter-gather, so that is not a problem.
	 */
	वापस 1;

error:
	WARN_ON_ONCE(1);
	dma_unmap_sg(host->dev, data->sg, data->sg_len, get_dma_dir(data));
	/* Disable FIFO */
	ग_लिखोq(BIT_ULL(16), host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	वापस 0;
पूर्ण

अटल u64 prepare_dma(काष्ठा cvm_mmc_host *host, काष्ठा mmc_data *data)
अणु
	अगर (host->use_sg && data->sg_len > 1)
		वापस prepare_dma_sg(host, data);
	अन्यथा
		वापस prepare_dma_single(host, data);
पूर्ण

अटल u64 prepare_ext_dma(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा cvm_mmc_slot *slot = mmc_priv(mmc);
	u64 emm_dma;

	emm_dma = FIELD_PREP(MIO_EMM_DMA_VAL, 1) |
		  FIELD_PREP(MIO_EMM_DMA_SECTOR,
			     mmc_card_is_blockaddr(mmc->card) ? 1 : 0) |
		  FIELD_PREP(MIO_EMM_DMA_RW,
			     (mrq->data->flags & MMC_DATA_WRITE) ? 1 : 0) |
		  FIELD_PREP(MIO_EMM_DMA_BLOCK_CNT, mrq->data->blocks) |
		  FIELD_PREP(MIO_EMM_DMA_CARD_ADDR, mrq->cmd->arg);
	set_bus_id(&emm_dma, slot->bus_id);

	अगर (mmc_card_mmc(mmc->card) || (mmc_card_sd(mmc->card) &&
	    (mmc->card->scr.cmds & SD_SCR_CMD23_SUPPORT)))
		emm_dma |= FIELD_PREP(MIO_EMM_DMA_MULTI, 1);

	pr_debug("[%s] blocks: %u  multi: %d\n",
		(emm_dma & MIO_EMM_DMA_RW) ? "W" : "R",
		 mrq->data->blocks, (emm_dma & MIO_EMM_DMA_MULTI) ? 1 : 0);
	वापस emm_dma;
पूर्ण

अटल व्योम cvm_mmc_dma_request(काष्ठा mmc_host *mmc,
				काष्ठा mmc_request *mrq)
अणु
	काष्ठा cvm_mmc_slot *slot = mmc_priv(mmc);
	काष्ठा cvm_mmc_host *host = slot->host;
	काष्ठा mmc_data *data;
	u64 emm_dma, addr;

	अगर (!mrq->data || !mrq->data->sg || !mrq->data->sg_len ||
	    !mrq->stop || mrq->stop->opcode != MMC_STOP_TRANSMISSION) अणु
		dev_err(&mmc->card->dev, "Error: %s no data\n", __func__);
		जाओ error;
	पूर्ण

	cvm_mmc_चयन_to(slot);

	data = mrq->data;
	pr_debug("DMA request  blocks: %d  block_size: %d  total_size: %d\n",
		 data->blocks, data->blksz, data->blocks * data->blksz);
	अगर (data->समयout_ns)
		set_wकरोg(slot, data->समयout_ns);

	WARN_ON(host->current_req);
	host->current_req = mrq;

	emm_dma = prepare_ext_dma(mmc, mrq);
	addr = prepare_dma(host, data);
	अगर (!addr) अणु
		dev_err(host->dev, "prepare_dma failed\n");
		जाओ error;
	पूर्ण

	host->dma_active = true;
	host->पूर्णांक_enable(host, MIO_EMM_INT_CMD_ERR | MIO_EMM_INT_DMA_DONE |
			 MIO_EMM_INT_DMA_ERR);

	अगर (host->dmar_fixup)
		host->dmar_fixup(host, mrq->cmd, data, addr);

	/*
	 * If we have a valid SD card in the slot, we set the response
	 * bit mask to check क्रम CRC errors and समयouts only.
	 * Otherwise, use the शेष घातer reset value.
	 */
	अगर (mmc_card_sd(mmc->card))
		ग_लिखोq(0x00b00000ull, host->base + MIO_EMM_STS_MASK(host));
	अन्यथा
		ग_लिखोq(0xe4390080ull, host->base + MIO_EMM_STS_MASK(host));
	ग_लिखोq(emm_dma, host->base + MIO_EMM_DMA(host));
	वापस;

error:
	mrq->cmd->error = -EINVAL;
	अगर (mrq->करोne)
		mrq->करोne(mrq);
	host->release_bus(host);
पूर्ण

अटल व्योम करो_पढ़ो_request(काष्ठा cvm_mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	sg_miter_start(&host->smi, mrq->data->sg, mrq->data->sg_len,
		       SG_MITER_ATOMIC | SG_MITER_TO_SG);
पूर्ण

अटल व्योम करो_ग_लिखो_request(काष्ठा cvm_mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	अचिन्हित पूर्णांक data_len = mrq->data->blocks * mrq->data->blksz;
	काष्ठा sg_mapping_iter *smi = &host->smi;
	अचिन्हित पूर्णांक bytes_xfered;
	पूर्णांक shअगरt = 56;
	u64 dat = 0;

	/* Copy data to the xmit buffer beक्रमe issuing the command. */
	sg_miter_start(smi, mrq->data->sg, mrq->data->sg_len, SG_MITER_FROM_SG);

	/* Auto inc from offset zero, dbuf zero */
	ग_लिखोq(0x10000ull, host->base + MIO_EMM_BUF_IDX(host));

	क्रम (bytes_xfered = 0; bytes_xfered < data_len;) अणु
		अगर (smi->consumed >= smi->length) अणु
			अगर (!sg_miter_next(smi))
				अवरोध;
			smi->consumed = 0;
		पूर्ण

		जबतक (smi->consumed < smi->length && shअगरt >= 0) अणु
			dat |= (u64)((u8 *)smi->addr)[smi->consumed] << shअगरt;
			bytes_xfered++;
			smi->consumed++;
			shअगरt -= 8;
		पूर्ण

		अगर (shअगरt < 0) अणु
			ग_लिखोq(dat, host->base + MIO_EMM_BUF_DAT(host));
			shअगरt = 56;
			dat = 0;
		पूर्ण
	पूर्ण
	sg_miter_stop(smi);
पूर्ण

अटल व्योम cvm_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा cvm_mmc_slot *slot = mmc_priv(mmc);
	काष्ठा cvm_mmc_host *host = slot->host;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा cvm_mmc_cr_mods mods;
	u64 emm_cmd, rsp_sts;
	पूर्णांक retries = 100;

	/*
	 * Note about locking:
	 * All MMC devices share the same bus and controller. Allow only a
	 * single user of the bootbus/MMC bus at a समय. The lock is acquired
	 * on all entry poपूर्णांकs from the MMC layer.
	 *
	 * For requests the lock is only released after the completion
	 * पूर्णांकerrupt!
	 */
	host->acquire_bus(host);

	अगर (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
	    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK)
		वापस cvm_mmc_dma_request(mmc, mrq);

	cvm_mmc_चयन_to(slot);

	mods = cvm_mmc_get_cr_mods(cmd);

	WARN_ON(host->current_req);
	host->current_req = mrq;

	अगर (cmd->data) अणु
		अगर (cmd->data->flags & MMC_DATA_READ)
			करो_पढ़ो_request(host, mrq);
		अन्यथा
			करो_ग_लिखो_request(host, mrq);

		अगर (cmd->data->समयout_ns)
			set_wकरोg(slot, cmd->data->समयout_ns);
	पूर्ण अन्यथा
		set_wकरोg(slot, 0);

	host->dma_active = false;
	host->पूर्णांक_enable(host, MIO_EMM_INT_CMD_DONE | MIO_EMM_INT_CMD_ERR);

	emm_cmd = FIELD_PREP(MIO_EMM_CMD_VAL, 1) |
		  FIELD_PREP(MIO_EMM_CMD_CTYPE_XOR, mods.ctype_xor) |
		  FIELD_PREP(MIO_EMM_CMD_RTYPE_XOR, mods.rtype_xor) |
		  FIELD_PREP(MIO_EMM_CMD_IDX, cmd->opcode) |
		  FIELD_PREP(MIO_EMM_CMD_ARG, cmd->arg);
	set_bus_id(&emm_cmd, slot->bus_id);
	अगर (cmd->data && mmc_cmd_type(cmd) == MMC_CMD_ADTC)
		emm_cmd |= FIELD_PREP(MIO_EMM_CMD_OFFSET,
				64 - ((cmd->data->blocks * cmd->data->blksz) / 8));

	ग_लिखोq(0, host->base + MIO_EMM_STS_MASK(host));

retry:
	rsp_sts = पढ़ोq(host->base + MIO_EMM_RSP_STS(host));
	अगर (rsp_sts & MIO_EMM_RSP_STS_DMA_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_CMD_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_SWITCH_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_DMA_PEND) अणु
		udelay(10);
		अगर (--retries)
			जाओ retry;
	पूर्ण
	अगर (!retries)
		dev_err(host->dev, "Bad status: %llx before command write\n", rsp_sts);
	ग_लिखोq(emm_cmd, host->base + MIO_EMM_CMD(host));
पूर्ण

अटल व्योम cvm_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा cvm_mmc_slot *slot = mmc_priv(mmc);
	काष्ठा cvm_mmc_host *host = slot->host;
	पूर्णांक clk_period = 0, घातer_class = 10, bus_width = 0;
	u64 घड़ी, emm_चयन;

	host->acquire_bus(host);
	cvm_mmc_चयन_to(slot);

	/* Set the घातer state */
	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_ON:
		अवरोध;

	हाल MMC_POWER_OFF:
		cvm_mmc_reset_bus(slot);
		अगर (host->global_pwr_gpiod)
			host->set_shared_घातer(host, 0);
		अन्यथा अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		अवरोध;

	हाल MMC_POWER_UP:
		अगर (host->global_pwr_gpiod)
			host->set_shared_घातer(host, 1);
		अन्यथा अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		अवरोध;
	पूर्ण

	/* Convert bus width to HW definition */
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_8:
		bus_width = 2;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		bus_width = 1;
		अवरोध;
	हाल MMC_BUS_WIDTH_1:
		bus_width = 0;
		अवरोध;
	पूर्ण

	/* DDR is available क्रम 4/8 bit bus width */
	अगर (ios->bus_width && ios->timing == MMC_TIMING_MMC_DDR52)
		bus_width |= 4;

	/* Change the घड़ी frequency. */
	घड़ी = ios->घड़ी;
	अगर (घड़ी > 52000000)
		घड़ी = 52000000;
	slot->घड़ी = घड़ी;

	अगर (घड़ी)
		clk_period = (host->sys_freq + घड़ी - 1) / (2 * घड़ी);

	emm_चयन = FIELD_PREP(MIO_EMM_SWITCH_HS_TIMING,
				(ios->timing == MMC_TIMING_MMC_HS)) |
		     FIELD_PREP(MIO_EMM_SWITCH_BUS_WIDTH, bus_width) |
		     FIELD_PREP(MIO_EMM_SWITCH_POWER_CLASS, घातer_class) |
		     FIELD_PREP(MIO_EMM_SWITCH_CLK_HI, clk_period) |
		     FIELD_PREP(MIO_EMM_SWITCH_CLK_LO, clk_period);
	set_bus_id(&emm_चयन, slot->bus_id);

	अगर (!चयन_val_changed(slot, emm_चयन))
		जाओ out;

	set_wकरोg(slot, 0);
	करो_चयन(host, emm_चयन);
	slot->cached_चयन = emm_चयन;
out:
	host->release_bus(host);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops cvm_mmc_ops = अणु
	.request        = cvm_mmc_request,
	.set_ios        = cvm_mmc_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmc_gpio_get_cd,
पूर्ण;

अटल व्योम cvm_mmc_set_घड़ी(काष्ठा cvm_mmc_slot *slot, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा mmc_host *mmc = slot->mmc;

	घड़ी = min(घड़ी, mmc->f_max);
	घड़ी = max(घड़ी, mmc->f_min);
	slot->घड़ी = घड़ी;
पूर्ण

अटल पूर्णांक cvm_mmc_init_lowlevel(काष्ठा cvm_mmc_slot *slot)
अणु
	काष्ठा cvm_mmc_host *host = slot->host;
	u64 emm_चयन;

	/* Enable this bus slot. */
	host->emm_cfg |= (1ull << slot->bus_id);
	ग_लिखोq(host->emm_cfg, slot->host->base + MIO_EMM_CFG(host));
	udelay(10);

	/* Program initial घड़ी speed and घातer. */
	cvm_mmc_set_घड़ी(slot, slot->mmc->f_min);
	emm_चयन = FIELD_PREP(MIO_EMM_SWITCH_POWER_CLASS, 10);
	emm_चयन |= FIELD_PREP(MIO_EMM_SWITCH_CLK_HI,
				 (host->sys_freq / slot->घड़ी) / 2);
	emm_चयन |= FIELD_PREP(MIO_EMM_SWITCH_CLK_LO,
				 (host->sys_freq / slot->घड़ी) / 2);

	/* Make the changes take effect on this bus slot. */
	set_bus_id(&emm_चयन, slot->bus_id);
	करो_चयन(host, emm_चयन);

	slot->cached_चयन = emm_चयन;

	/*
	 * Set watchकरोg समयout value and शेष reset value
	 * क्रम the mask रेजिस्टर. Finally, set the CARD_RCA
	 * bit so that we can get the card address relative
	 * to the CMD रेजिस्टर क्रम CMD7 transactions.
	 */
	set_wकरोg(slot, 0);
	ग_लिखोq(0xe4390080ull, host->base + MIO_EMM_STS_MASK(host));
	ग_लिखोq(1, host->base + MIO_EMM_RCA(host));
	वापस 0;
पूर्ण

अटल पूर्णांक cvm_mmc_of_parse(काष्ठा device *dev, काष्ठा cvm_mmc_slot *slot)
अणु
	u32 id, cmd_skew = 0, dat_skew = 0, bus_width = 0;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा mmc_host *mmc = slot->mmc;
	u64 घड़ी_period;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "reg", &id);
	अगर (ret) अणु
		dev_err(dev, "Missing or invalid reg property on %pOF\n", node);
		वापस ret;
	पूर्ण

	अगर (id >= CAVIUM_MAX_MMC || slot->host->slot[id]) अणु
		dev_err(dev, "Invalid reg property on %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		वापस ret;
	/*
	 * Legacy Octeon firmware has no regulator entry, fall-back to
	 * a hard-coded voltage to get a sane OCR.
	 */
	अगर (IS_ERR(mmc->supply.vmmc))
		mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	/* Common MMC bindings */
	ret = mmc_of_parse(mmc);
	अगर (ret)
		वापस ret;

	/* Set bus width */
	अगर (!(mmc->caps & (MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA))) अणु
		of_property_पढ़ो_u32(node, "cavium,bus-max-width", &bus_width);
		अगर (bus_width == 8)
			mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_4_BIT_DATA;
		अन्यथा अगर (bus_width == 4)
			mmc->caps |= MMC_CAP_4_BIT_DATA;
	पूर्ण

	/* Set maximum and minimum frequency */
	अगर (!mmc->f_max)
		of_property_पढ़ो_u32(node, "spi-max-frequency", &mmc->f_max);
	अगर (!mmc->f_max || mmc->f_max > 52000000)
		mmc->f_max = 52000000;
	mmc->f_min = 400000;

	/* Sampling रेजिस्टर settings, period in picoseconds */
	घड़ी_period = 1000000000000ull / slot->host->sys_freq;
	of_property_पढ़ो_u32(node, "cavium,cmd-clk-skew", &cmd_skew);
	of_property_पढ़ो_u32(node, "cavium,dat-clk-skew", &dat_skew);
	slot->cmd_cnt = (cmd_skew + घड़ी_period / 2) / घड़ी_period;
	slot->dat_cnt = (dat_skew + घड़ी_period / 2) / घड़ी_period;

	वापस id;
पूर्ण

पूर्णांक cvm_mmc_of_slot_probe(काष्ठा device *dev, काष्ठा cvm_mmc_host *host)
अणु
	काष्ठा cvm_mmc_slot *slot;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret, id;

	mmc = mmc_alloc_host(माप(काष्ठा cvm_mmc_slot), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	slot = mmc_priv(mmc);
	slot->mmc = mmc;
	slot->host = host;

	ret = cvm_mmc_of_parse(dev, slot);
	अगर (ret < 0)
		जाओ error;
	id = ret;

	/* Set up host parameters */
	mmc->ops = &cvm_mmc_ops;

	/*
	 * We only have a 3.3v supply, we cannot support any
	 * of the UHS modes. We करो support the high speed DDR
	 * modes up to 52MHz.
	 *
	 * Disable bounce buffers क्रम max_segs = 1
	 */
	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
		     MMC_CAP_CMD23 | MMC_CAP_POWER_OFF_CARD | MMC_CAP_3_3V_DDR;

	अगर (host->use_sg)
		mmc->max_segs = 16;
	अन्यथा
		mmc->max_segs = 1;

	/* DMA size field can address up to 8 MB */
	mmc->max_seg_size = min_t(अचिन्हित पूर्णांक, 8 * 1024 * 1024,
				  dma_get_max_seg_size(host->dev));
	mmc->max_req_size = mmc->max_seg_size;
	/* External DMA is in 512 byte blocks */
	mmc->max_blk_size = 512;
	/* DMA block count field is 15 bits */
	mmc->max_blk_count = 32767;

	slot->घड़ी = mmc->f_min;
	slot->bus_id = id;
	slot->cached_rca = 1;

	host->acquire_bus(host);
	host->slot[id] = slot;
	cvm_mmc_चयन_to(slot);
	cvm_mmc_init_lowlevel(slot);
	host->release_bus(host);

	ret = mmc_add_host(mmc);
	अगर (ret) अणु
		dev_err(dev, "mmc_add_host() returned %d\n", ret);
		slot->host->slot[id] = शून्य;
		जाओ error;
	पूर्ण
	वापस 0;

error:
	mmc_मुक्त_host(slot->mmc);
	वापस ret;
पूर्ण

पूर्णांक cvm_mmc_of_slot_हटाओ(काष्ठा cvm_mmc_slot *slot)
अणु
	mmc_हटाओ_host(slot->mmc);
	slot->host->slot[slot->bus_id] = शून्य;
	mmc_मुक्त_host(slot->mmc);
	वापस 0;
पूर्ण
