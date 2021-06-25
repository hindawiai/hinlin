<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  tअगरm_sd.c - TI FlashMedia driver
 *
 *  Copyright (C) 2006 Alex Dubov <oakad@yahoo.com>
 *
 * Special thanks to Brad Campbell क्रम extensive testing of this driver.
 */


#समावेश <linux/tअगरm.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRIVER_NAME "tifm_sd"
#घोषणा DRIVER_VERSION "0.8"

अटल bool no_dma = 0;
अटल bool fixed_समयout = 0;
module_param(no_dma, bool, 0644);
module_param(fixed_समयout, bool, 0644);

/* Constants here are mostly from OMAP5912 datasheet */
#घोषणा TIFM_MMCSD_RESET      0x0002
#घोषणा TIFM_MMCSD_CLKMASK    0x03ff
#घोषणा TIFM_MMCSD_POWER      0x0800
#घोषणा TIFM_MMCSD_4BBUS      0x8000
#घोषणा TIFM_MMCSD_RXDE       0x8000   /* rx dma enable */
#घोषणा TIFM_MMCSD_TXDE       0x0080   /* tx dma enable */
#घोषणा TIFM_MMCSD_BUFINT     0x0c00   /* set bits: AE, AF */
#घोषणा TIFM_MMCSD_DPE        0x0020   /* data समयout counted in kilocycles */
#घोषणा TIFM_MMCSD_INAB       0x0080   /* पात / initialize command */
#घोषणा TIFM_MMCSD_READ       0x8000

#घोषणा TIFM_MMCSD_ERRMASK    0x01e0   /* set bits: CCRC, CTO, DCRC, DTO */
#घोषणा TIFM_MMCSD_EOC        0x0001   /* end of command phase  */
#घोषणा TIFM_MMCSD_CD         0x0002   /* card detect           */
#घोषणा TIFM_MMCSD_CB         0x0004   /* card enter busy state */
#घोषणा TIFM_MMCSD_BRS        0x0008   /* block received/sent   */
#घोषणा TIFM_MMCSD_खातापूर्णB       0x0010   /* card निकास busy state  */
#घोषणा TIFM_MMCSD_DTO        0x0020   /* data समय-out         */
#घोषणा TIFM_MMCSD_DCRC       0x0040   /* data crc error        */
#घोषणा TIFM_MMCSD_CTO        0x0080   /* command समय-out      */
#घोषणा TIFM_MMCSD_CCRC       0x0100   /* command crc error     */
#घोषणा TIFM_MMCSD_AF         0x0400   /* fअगरo almost full      */
#घोषणा TIFM_MMCSD_AE         0x0800   /* fअगरo almost empty     */
#घोषणा TIFM_MMCSD_OCRB       0x1000   /* OCR busy              */
#घोषणा TIFM_MMCSD_CIRQ       0x2000   /* card irq (cmd40/sdio) */
#घोषणा TIFM_MMCSD_CERR       0x4000   /* card status error     */

#घोषणा TIFM_MMCSD_ODTO       0x0040   /* खोलो drain / extended समयout */
#घोषणा TIFM_MMCSD_CARD_RO    0x0200   /* card is पढ़ो-only     */

#घोषणा TIFM_MMCSD_FIFO_SIZE  0x0020

#घोषणा TIFM_MMCSD_RSP_R0     0x0000
#घोषणा TIFM_MMCSD_RSP_R1     0x0100
#घोषणा TIFM_MMCSD_RSP_R2     0x0200
#घोषणा TIFM_MMCSD_RSP_R3     0x0300
#घोषणा TIFM_MMCSD_RSP_R4     0x0400
#घोषणा TIFM_MMCSD_RSP_R5     0x0500
#घोषणा TIFM_MMCSD_RSP_R6     0x0600

#घोषणा TIFM_MMCSD_RSP_BUSY   0x0800

#घोषणा TIFM_MMCSD_CMD_BC     0x0000
#घोषणा TIFM_MMCSD_CMD_BCR    0x1000
#घोषणा TIFM_MMCSD_CMD_AC     0x2000
#घोषणा TIFM_MMCSD_CMD_ADTC   0x3000

#घोषणा TIFM_MMCSD_MAX_BLOCK_SIZE  0x0800UL

#घोषणा TIFM_MMCSD_REQ_TIMEOUT_MS  1000

क्रमागत अणु
	CMD_READY    = 0x0001,
	FIFO_READY   = 0x0002,
	BRS_READY    = 0x0004,
	SCMD_ACTIVE  = 0x0008,
	SCMD_READY   = 0x0010,
	CARD_BUSY    = 0x0020,
	DATA_CARRY   = 0x0040
पूर्ण;

काष्ठा tअगरm_sd अणु
	काष्ठा tअगरm_dev       *dev;

	अचिन्हित लघु        eject:1,
			      खोलो_drain:1,
			      no_dma:1;
	अचिन्हित लघु        cmd_flags;

	अचिन्हित पूर्णांक          clk_freq;
	अचिन्हित पूर्णांक          clk_भाग;
	अचिन्हित दीर्घ         समयout_jअगरfies;

	काष्ठा tasklet_काष्ठा finish_tasklet;
	काष्ठा समयr_list     समयr;
	काष्ठा mmc_request    *req;

	पूर्णांक                   sg_len;
	पूर्णांक                   sg_pos;
	अचिन्हित पूर्णांक          block_pos;
	काष्ठा scatterlist    bounce_buf;
	अचिन्हित अक्षर         bounce_buf_data[TIFM_MMCSD_MAX_BLOCK_SIZE];
पूर्ण;

/* क्रम some reason, host won't respond correctly to पढ़ोw/ग_लिखोw */
अटल व्योम tअगरm_sd_पढ़ो_fअगरo(काष्ठा tअगरm_sd *host, काष्ठा page *pg,
			      अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pos = 0, val;

	buf = kmap_atomic(pg) + off;
	अगर (host->cmd_flags & DATA_CARRY) अणु
		buf[pos++] = host->bounce_buf_data[0];
		host->cmd_flags &= ~DATA_CARRY;
	पूर्ण

	जबतक (pos < cnt) अणु
		val = पढ़ोl(sock->addr + SOCK_MMCSD_DATA);
		buf[pos++] = val & 0xff;
		अगर (pos == cnt) अणु
			host->bounce_buf_data[0] = (val >> 8) & 0xff;
			host->cmd_flags |= DATA_CARRY;
			अवरोध;
		पूर्ण
		buf[pos++] = (val >> 8) & 0xff;
	पूर्ण
	kunmap_atomic(buf - off);
पूर्ण

अटल व्योम tअगरm_sd_ग_लिखो_fअगरo(काष्ठा tअगरm_sd *host, काष्ठा page *pg,
			       अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pos = 0, val;

	buf = kmap_atomic(pg) + off;
	अगर (host->cmd_flags & DATA_CARRY) अणु
		val = host->bounce_buf_data[0] | ((buf[pos++] << 8) & 0xff00);
		ग_लिखोl(val, sock->addr + SOCK_MMCSD_DATA);
		host->cmd_flags &= ~DATA_CARRY;
	पूर्ण

	जबतक (pos < cnt) अणु
		val = buf[pos++];
		अगर (pos == cnt) अणु
			host->bounce_buf_data[0] = val & 0xff;
			host->cmd_flags |= DATA_CARRY;
			अवरोध;
		पूर्ण
		val |= (buf[pos++] << 8) & 0xff00;
		ग_लिखोl(val, sock->addr + SOCK_MMCSD_DATA);
	पूर्ण
	kunmap_atomic(buf - off);
पूर्ण

अटल व्योम tअगरm_sd_transfer_data(काष्ठा tअगरm_sd *host)
अणु
	काष्ठा mmc_data *r_data = host->req->cmd->data;
	काष्ठा scatterlist *sg = r_data->sg;
	अचिन्हित पूर्णांक off, cnt, t_size = TIFM_MMCSD_FIFO_SIZE * 2;
	अचिन्हित पूर्णांक p_off, p_cnt;
	काष्ठा page *pg;

	अगर (host->sg_pos == host->sg_len)
		वापस;
	जबतक (t_size) अणु
		cnt = sg[host->sg_pos].length - host->block_pos;
		अगर (!cnt) अणु
			host->block_pos = 0;
			host->sg_pos++;
			अगर (host->sg_pos == host->sg_len) अणु
				अगर ((r_data->flags & MMC_DATA_WRITE)
				    && (host->cmd_flags & DATA_CARRY))
					ग_लिखोl(host->bounce_buf_data[0],
					       host->dev->addr
					       + SOCK_MMCSD_DATA);

				वापस;
			पूर्ण
			cnt = sg[host->sg_pos].length;
		पूर्ण
		off = sg[host->sg_pos].offset + host->block_pos;

		pg = nth_page(sg_page(&sg[host->sg_pos]), off >> PAGE_SHIFT);
		p_off = offset_in_page(off);
		p_cnt = PAGE_SIZE - p_off;
		p_cnt = min(p_cnt, cnt);
		p_cnt = min(p_cnt, t_size);

		अगर (r_data->flags & MMC_DATA_READ)
			tअगरm_sd_पढ़ो_fअगरo(host, pg, p_off, p_cnt);
		अन्यथा अगर (r_data->flags & MMC_DATA_WRITE)
			tअगरm_sd_ग_लिखो_fअगरo(host, pg, p_off, p_cnt);

		t_size -= p_cnt;
		host->block_pos += p_cnt;
	पूर्ण
पूर्ण

अटल व्योम tअगरm_sd_copy_page(काष्ठा page *dst, अचिन्हित पूर्णांक dst_off,
			      काष्ठा page *src, अचिन्हित पूर्णांक src_off,
			      अचिन्हित पूर्णांक count)
अणु
	अचिन्हित अक्षर *src_buf = kmap_atomic(src) + src_off;
	अचिन्हित अक्षर *dst_buf = kmap_atomic(dst) + dst_off;

	स_नकल(dst_buf, src_buf, count);

	kunmap_atomic(dst_buf - dst_off);
	kunmap_atomic(src_buf - src_off);
पूर्ण

अटल व्योम tअगरm_sd_bounce_block(काष्ठा tअगरm_sd *host, काष्ठा mmc_data *r_data)
अणु
	काष्ठा scatterlist *sg = r_data->sg;
	अचिन्हित पूर्णांक t_size = r_data->blksz;
	अचिन्हित पूर्णांक off, cnt;
	अचिन्हित पूर्णांक p_off, p_cnt;
	काष्ठा page *pg;

	dev_dbg(&host->dev->dev, "bouncing block\n");
	जबतक (t_size) अणु
		cnt = sg[host->sg_pos].length - host->block_pos;
		अगर (!cnt) अणु
			host->block_pos = 0;
			host->sg_pos++;
			अगर (host->sg_pos == host->sg_len)
				वापस;
			cnt = sg[host->sg_pos].length;
		पूर्ण
		off = sg[host->sg_pos].offset + host->block_pos;

		pg = nth_page(sg_page(&sg[host->sg_pos]), off >> PAGE_SHIFT);
		p_off = offset_in_page(off);
		p_cnt = PAGE_SIZE - p_off;
		p_cnt = min(p_cnt, cnt);
		p_cnt = min(p_cnt, t_size);

		अगर (r_data->flags & MMC_DATA_WRITE)
			tअगरm_sd_copy_page(sg_page(&host->bounce_buf),
					  r_data->blksz - t_size,
					  pg, p_off, p_cnt);
		अन्यथा अगर (r_data->flags & MMC_DATA_READ)
			tअगरm_sd_copy_page(pg, p_off, sg_page(&host->bounce_buf),
					  r_data->blksz - t_size, p_cnt);

		t_size -= p_cnt;
		host->block_pos += p_cnt;
	पूर्ण
पूर्ण

अटल पूर्णांक tअगरm_sd_set_dma_data(काष्ठा tअगरm_sd *host, काष्ठा mmc_data *r_data)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक t_size = TIFM_DMA_TSIZE * r_data->blksz;
	अचिन्हित पूर्णांक dma_len, dma_blk_cnt, dma_off;
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (host->sg_pos == host->sg_len)
		वापस 1;

	अगर (host->cmd_flags & DATA_CARRY) अणु
		host->cmd_flags &= ~DATA_CARRY;
		local_irq_save(flags);
		tअगरm_sd_bounce_block(host, r_data);
		local_irq_restore(flags);
		अगर (host->sg_pos == host->sg_len)
			वापस 1;
	पूर्ण

	dma_len = sg_dma_len(&r_data->sg[host->sg_pos]) - host->block_pos;
	अगर (!dma_len) अणु
		host->block_pos = 0;
		host->sg_pos++;
		अगर (host->sg_pos == host->sg_len)
			वापस 1;
		dma_len = sg_dma_len(&r_data->sg[host->sg_pos]);
	पूर्ण

	अगर (dma_len < t_size) अणु
		dma_blk_cnt = dma_len / r_data->blksz;
		dma_off = host->block_pos;
		host->block_pos += dma_blk_cnt * r_data->blksz;
	पूर्ण अन्यथा अणु
		dma_blk_cnt = TIFM_DMA_TSIZE;
		dma_off = host->block_pos;
		host->block_pos += t_size;
	पूर्ण

	अगर (dma_blk_cnt)
		sg = &r_data->sg[host->sg_pos];
	अन्यथा अगर (dma_len) अणु
		अगर (r_data->flags & MMC_DATA_WRITE) अणु
			local_irq_save(flags);
			tअगरm_sd_bounce_block(host, r_data);
			local_irq_restore(flags);
		पूर्ण अन्यथा
			host->cmd_flags |= DATA_CARRY;

		sg = &host->bounce_buf;
		dma_off = 0;
		dma_blk_cnt = 1;
	पूर्ण अन्यथा
		वापस 1;

	dev_dbg(&sock->dev, "setting dma for %d blocks\n", dma_blk_cnt);
	ग_लिखोl(sg_dma_address(sg) + dma_off, sock->addr + SOCK_DMA_ADDRESS);
	अगर (r_data->flags & MMC_DATA_WRITE)
		ग_लिखोl((dma_blk_cnt << 8) | TIFM_DMA_TX | TIFM_DMA_EN,
		       sock->addr + SOCK_DMA_CONTROL);
	अन्यथा
		ग_लिखोl((dma_blk_cnt << 8) | TIFM_DMA_EN,
		       sock->addr + SOCK_DMA_CONTROL);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tअगरm_sd_op_flags(काष्ठा mmc_command *cmd)
अणु
	अचिन्हित पूर्णांक rc = 0;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		rc |= TIFM_MMCSD_RSP_R0;
		अवरोध;
	हाल MMC_RSP_R1B:
		rc |= TIFM_MMCSD_RSP_BUSY;
		fallthrough;
	हाल MMC_RSP_R1:
		rc |= TIFM_MMCSD_RSP_R1;
		अवरोध;
	हाल MMC_RSP_R2:
		rc |= TIFM_MMCSD_RSP_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		rc |= TIFM_MMCSD_RSP_R3;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (mmc_cmd_type(cmd)) अणु
	हाल MMC_CMD_BC:
		rc |= TIFM_MMCSD_CMD_BC;
		अवरोध;
	हाल MMC_CMD_BCR:
		rc |= TIFM_MMCSD_CMD_BCR;
		अवरोध;
	हाल MMC_CMD_AC:
		rc |= TIFM_MMCSD_CMD_AC;
		अवरोध;
	हाल MMC_CMD_ADTC:
		rc |= TIFM_MMCSD_CMD_ADTC;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम tअगरm_sd_exec(काष्ठा tअगरm_sd *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक cmd_mask = tअगरm_sd_op_flags(cmd);

	अगर (host->खोलो_drain)
		cmd_mask |= TIFM_MMCSD_ODTO;

	अगर (cmd->data && (cmd->data->flags & MMC_DATA_READ))
		cmd_mask |= TIFM_MMCSD_READ;

	dev_dbg(&sock->dev, "executing opcode 0x%x, arg: 0x%x, mask: 0x%x\n",
		cmd->opcode, cmd->arg, cmd_mask);

	ग_लिखोl((cmd->arg >> 16) & 0xffff, sock->addr + SOCK_MMCSD_ARG_HIGH);
	ग_लिखोl(cmd->arg & 0xffff, sock->addr + SOCK_MMCSD_ARG_LOW);
	ग_लिखोl(cmd->opcode | cmd_mask, sock->addr + SOCK_MMCSD_COMMAND);
पूर्ण

अटल व्योम tअगरm_sd_fetch_resp(काष्ठा mmc_command *cmd, काष्ठा tअगरm_dev *sock)
अणु
	cmd->resp[0] = (पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x1c) << 16)
		       | पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x18);
	cmd->resp[1] = (पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x14) << 16)
		       | पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x10);
	cmd->resp[2] = (पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x0c) << 16)
		       | पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x08);
	cmd->resp[3] = (पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x04) << 16)
		       | पढ़ोl(sock->addr + SOCK_MMCSD_RESPONSE + 0x00);
पूर्ण

अटल व्योम tअगरm_sd_check_status(काष्ठा tअगरm_sd *host)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	काष्ठा mmc_command *cmd = host->req->cmd;

	अगर (cmd->error)
		जाओ finish_request;

	अगर (!(host->cmd_flags & CMD_READY))
		वापस;

	अगर (cmd->data) अणु
		अगर (cmd->data->error) अणु
			अगर ((host->cmd_flags & SCMD_ACTIVE)
			    && !(host->cmd_flags & SCMD_READY))
				वापस;

			जाओ finish_request;
		पूर्ण

		अगर (!(host->cmd_flags & BRS_READY))
			वापस;

		अगर (!(host->no_dma || (host->cmd_flags & FIFO_READY)))
			वापस;

		अगर (cmd->data->flags & MMC_DATA_WRITE) अणु
			अगर (host->req->stop) अणु
				अगर (!(host->cmd_flags & SCMD_ACTIVE)) अणु
					host->cmd_flags |= SCMD_ACTIVE;
					ग_लिखोl(TIFM_MMCSD_खातापूर्णB
					       | पढ़ोl(sock->addr
						       + SOCK_MMCSD_INT_ENABLE),
					       sock->addr
					       + SOCK_MMCSD_INT_ENABLE);
					tअगरm_sd_exec(host, host->req->stop);
					वापस;
				पूर्ण अन्यथा अणु
					अगर (!(host->cmd_flags & SCMD_READY)
					    || (host->cmd_flags & CARD_BUSY))
						वापस;
					ग_लिखोl((~TIFM_MMCSD_खातापूर्णB)
					       & पढ़ोl(sock->addr
						       + SOCK_MMCSD_INT_ENABLE),
					       sock->addr
					       + SOCK_MMCSD_INT_ENABLE);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (host->cmd_flags & CARD_BUSY)
					वापस;
				ग_लिखोl((~TIFM_MMCSD_खातापूर्णB)
				       & पढ़ोl(sock->addr
					       + SOCK_MMCSD_INT_ENABLE),
				       sock->addr + SOCK_MMCSD_INT_ENABLE);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (host->req->stop) अणु
				अगर (!(host->cmd_flags & SCMD_ACTIVE)) अणु
					host->cmd_flags |= SCMD_ACTIVE;
					tअगरm_sd_exec(host, host->req->stop);
					वापस;
				पूर्ण अन्यथा अणु
					अगर (!(host->cmd_flags & SCMD_READY))
						वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
finish_request:
	tasklet_schedule(&host->finish_tasklet);
पूर्ण

/* Called from पूर्णांकerrupt handler */
अटल व्योम tअगरm_sd_data_event(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_sd *host;
	अचिन्हित पूर्णांक fअगरo_status = 0;
	काष्ठा mmc_data *r_data = शून्य;

	spin_lock(&sock->lock);
	host = mmc_priv((काष्ठा mmc_host*)tअगरm_get_drvdata(sock));
	fअगरo_status = पढ़ोl(sock->addr + SOCK_DMA_FIFO_STATUS);
	dev_dbg(&sock->dev, "data event: fifo_status %x, flags %x\n",
		fअगरo_status, host->cmd_flags);

	अगर (host->req) अणु
		r_data = host->req->cmd->data;

		अगर (r_data && (fअगरo_status & TIFM_FIFO_READY)) अणु
			अगर (tअगरm_sd_set_dma_data(host, r_data)) अणु
				host->cmd_flags |= FIFO_READY;
				tअगरm_sd_check_status(host);
			पूर्ण
		पूर्ण
	पूर्ण

	ग_लिखोl(fअगरo_status, sock->addr + SOCK_DMA_FIFO_STATUS);
	spin_unlock(&sock->lock);
पूर्ण

/* Called from पूर्णांकerrupt handler */
अटल व्योम tअगरm_sd_card_event(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_sd *host;
	अचिन्हित पूर्णांक host_status = 0;
	पूर्णांक cmd_error = 0;
	काष्ठा mmc_command *cmd = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock(&sock->lock);
	host = mmc_priv((काष्ठा mmc_host*)tअगरm_get_drvdata(sock));
	host_status = पढ़ोl(sock->addr + SOCK_MMCSD_STATUS);
	dev_dbg(&sock->dev, "host event: host_status %x, flags %x\n",
		host_status, host->cmd_flags);

	अगर (host->req) अणु
		cmd = host->req->cmd;

		अगर (host_status & TIFM_MMCSD_ERRMASK) अणु
			ग_लिखोl(host_status & TIFM_MMCSD_ERRMASK,
			       sock->addr + SOCK_MMCSD_STATUS);
			अगर (host_status & TIFM_MMCSD_CTO)
				cmd_error = -ETIMEDOUT;
			अन्यथा अगर (host_status & TIFM_MMCSD_CCRC)
				cmd_error = -EILSEQ;

			अगर (cmd->data) अणु
				अगर (host_status & TIFM_MMCSD_DTO)
					cmd->data->error = -ETIMEDOUT;
				अन्यथा अगर (host_status & TIFM_MMCSD_DCRC)
					cmd->data->error = -EILSEQ;
			पूर्ण

			ग_लिखोl(TIFM_FIFO_INT_SETALL,
			       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
			ग_लिखोl(TIFM_DMA_RESET, sock->addr + SOCK_DMA_CONTROL);

			अगर (host->req->stop) अणु
				अगर (host->cmd_flags & SCMD_ACTIVE) अणु
					host->req->stop->error = cmd_error;
					host->cmd_flags |= SCMD_READY;
				पूर्ण अन्यथा अणु
					cmd->error = cmd_error;
					host->cmd_flags |= SCMD_ACTIVE;
					tअगरm_sd_exec(host, host->req->stop);
					जाओ करोne;
				पूर्ण
			पूर्ण अन्यथा
				cmd->error = cmd_error;
		पूर्ण अन्यथा अणु
			अगर (host_status & (TIFM_MMCSD_EOC | TIFM_MMCSD_CERR)) अणु
				अगर (!(host->cmd_flags & CMD_READY)) अणु
					host->cmd_flags |= CMD_READY;
					tअगरm_sd_fetch_resp(cmd, sock);
				पूर्ण अन्यथा अगर (host->cmd_flags & SCMD_ACTIVE) अणु
					host->cmd_flags |= SCMD_READY;
					tअगरm_sd_fetch_resp(host->req->stop,
							   sock);
				पूर्ण
			पूर्ण
			अगर (host_status & TIFM_MMCSD_BRS)
				host->cmd_flags |= BRS_READY;
		पूर्ण

		अगर (host->no_dma && cmd->data) अणु
			अगर (host_status & TIFM_MMCSD_AE)
				ग_लिखोl(host_status & TIFM_MMCSD_AE,
				       sock->addr + SOCK_MMCSD_STATUS);

			अगर (host_status & (TIFM_MMCSD_AE | TIFM_MMCSD_AF
					   | TIFM_MMCSD_BRS)) अणु
				local_irq_save(flags);
				tअगरm_sd_transfer_data(host);
				local_irq_restore(flags);
				host_status &= ~TIFM_MMCSD_AE;
			पूर्ण
		पूर्ण

		अगर (host_status & TIFM_MMCSD_खातापूर्णB)
			host->cmd_flags &= ~CARD_BUSY;
		अन्यथा अगर (host_status & TIFM_MMCSD_CB)
			host->cmd_flags |= CARD_BUSY;

		tअगरm_sd_check_status(host);
	पूर्ण
करोne:
	ग_लिखोl(host_status, sock->addr + SOCK_MMCSD_STATUS);
	spin_unlock(&sock->lock);
पूर्ण

अटल व्योम tअगरm_sd_set_data_समयout(काष्ठा tअगरm_sd *host,
				     काष्ठा mmc_data *data)
अणु
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक data_समयout = data->समयout_clks;

	अगर (fixed_समयout)
		वापस;

	data_समयout += data->समयout_ns /
			((1000000000UL / host->clk_freq) * host->clk_भाग);

	अगर (data_समयout < 0xffff) अणु
		ग_लिखोl(data_समयout, sock->addr + SOCK_MMCSD_DATA_TO);
		ग_लिखोl((~TIFM_MMCSD_DPE)
		       & पढ़ोl(sock->addr + SOCK_MMCSD_SDIO_MODE_CONFIG),
		       sock->addr + SOCK_MMCSD_SDIO_MODE_CONFIG);
	पूर्ण अन्यथा अणु
		data_समयout = (data_समयout >> 10) + 1;
		अगर (data_समयout > 0xffff)
			data_समयout = 0;	/* set to unlimited */
		ग_लिखोl(data_समयout, sock->addr + SOCK_MMCSD_DATA_TO);
		ग_लिखोl(TIFM_MMCSD_DPE
		       | पढ़ोl(sock->addr + SOCK_MMCSD_SDIO_MODE_CONFIG),
		       sock->addr + SOCK_MMCSD_SDIO_MODE_CONFIG);
	पूर्ण
पूर्ण

अटल व्योम tअगरm_sd_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा tअगरm_sd *host = mmc_priv(mmc);
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित दीर्घ flags;
	काष्ठा mmc_data *r_data = mrq->cmd->data;

	spin_lock_irqsave(&sock->lock, flags);
	अगर (host->eject) अणु
		mrq->cmd->error = -ENOMEDIUM;
		जाओ err_out;
	पूर्ण

	अगर (host->req) अणु
		pr_err("%s : unfinished request detected\n",
		       dev_name(&sock->dev));
		mrq->cmd->error = -ETIMEDOUT;
		जाओ err_out;
	पूर्ण

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->sg_pos = 0;

	अगर (mrq->data && !is_घातer_of_2(mrq->data->blksz))
		host->no_dma = 1;
	अन्यथा
		host->no_dma = no_dma ? 1 : 0;

	अगर (r_data) अणु
		tअगरm_sd_set_data_समयout(host, r_data);

		अगर ((r_data->flags & MMC_DATA_WRITE) && !mrq->stop)
			 ग_लिखोl(TIFM_MMCSD_खातापूर्णB
				| पढ़ोl(sock->addr + SOCK_MMCSD_INT_ENABLE),
				sock->addr + SOCK_MMCSD_INT_ENABLE);

		अगर (host->no_dma) अणु
			ग_लिखोl(TIFM_MMCSD_BUFINT
			       | पढ़ोl(sock->addr + SOCK_MMCSD_INT_ENABLE),
			       sock->addr + SOCK_MMCSD_INT_ENABLE);
			ग_लिखोl(((TIFM_MMCSD_FIFO_SIZE - 1) << 8)
			       | (TIFM_MMCSD_FIFO_SIZE - 1),
			       sock->addr + SOCK_MMCSD_BUFFER_CONFIG);

			host->sg_len = r_data->sg_len;
		पूर्ण अन्यथा अणु
			sg_init_one(&host->bounce_buf, host->bounce_buf_data,
				    r_data->blksz);

			अगर(1 != tअगरm_map_sg(sock, &host->bounce_buf, 1,
					    r_data->flags & MMC_DATA_WRITE
					    ? PCI_DMA_TODEVICE
					    : PCI_DMA_FROMDEVICE)) अणु
				pr_err("%s : scatterlist map failed\n",
				       dev_name(&sock->dev));
				mrq->cmd->error = -ENOMEM;
				जाओ err_out;
			पूर्ण
			host->sg_len = tअगरm_map_sg(sock, r_data->sg,
						   r_data->sg_len,
						   r_data->flags
						   & MMC_DATA_WRITE
						   ? PCI_DMA_TODEVICE
						   : PCI_DMA_FROMDEVICE);
			अगर (host->sg_len < 1) अणु
				pr_err("%s : scatterlist map failed\n",
				       dev_name(&sock->dev));
				tअगरm_unmap_sg(sock, &host->bounce_buf, 1,
					      r_data->flags & MMC_DATA_WRITE
					      ? PCI_DMA_TODEVICE
					      : PCI_DMA_FROMDEVICE);
				mrq->cmd->error = -ENOMEM;
				जाओ err_out;
			पूर्ण

			ग_लिखोl(TIFM_FIFO_INT_SETALL,
			       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
			ग_लिखोl(ilog2(r_data->blksz) - 2,
			       sock->addr + SOCK_FIFO_PAGE_SIZE);
			ग_लिखोl(TIFM_FIFO_ENABLE,
			       sock->addr + SOCK_FIFO_CONTROL);
			ग_लिखोl(TIFM_FIFO_INTMASK,
			       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);

			अगर (r_data->flags & MMC_DATA_WRITE)
				ग_लिखोl(TIFM_MMCSD_TXDE,
				       sock->addr + SOCK_MMCSD_BUFFER_CONFIG);
			अन्यथा
				ग_लिखोl(TIFM_MMCSD_RXDE,
				       sock->addr + SOCK_MMCSD_BUFFER_CONFIG);

			tअगरm_sd_set_dma_data(host, r_data);
		पूर्ण

		ग_लिखोl(r_data->blocks - 1,
		       sock->addr + SOCK_MMCSD_NUM_BLOCKS);
		ग_लिखोl(r_data->blksz - 1,
		       sock->addr + SOCK_MMCSD_BLOCK_LEN);
	पूर्ण

	host->req = mrq;
	mod_समयr(&host->समयr, jअगरfies + host->समयout_jअगरfies);
	ग_लिखोl(TIFM_CTRL_LED | पढ़ोl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);
	tअगरm_sd_exec(host, mrq->cmd);
	spin_unlock_irqrestore(&sock->lock, flags);
	वापस;

err_out:
	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल व्योम tअगरm_sd_end_cmd(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा tअगरm_sd *host = from_tasklet(host, t, finish_tasklet);
	काष्ठा tअगरm_dev *sock = host->dev;
	काष्ठा mmc_host *mmc = tअगरm_get_drvdata(sock);
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_data *r_data = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sock->lock, flags);

	del_समयr(&host->समयr);
	mrq = host->req;
	host->req = शून्य;

	अगर (!mrq) अणु
		pr_err(" %s : no request to complete?\n",
		       dev_name(&sock->dev));
		spin_unlock_irqrestore(&sock->lock, flags);
		वापस;
	पूर्ण

	r_data = mrq->cmd->data;
	अगर (r_data) अणु
		अगर (host->no_dma) अणु
			ग_लिखोl((~TIFM_MMCSD_BUFINT)
			       & पढ़ोl(sock->addr + SOCK_MMCSD_INT_ENABLE),
			       sock->addr + SOCK_MMCSD_INT_ENABLE);
		पूर्ण अन्यथा अणु
			tअगरm_unmap_sg(sock, &host->bounce_buf, 1,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
			tअगरm_unmap_sg(sock, r_data->sg, r_data->sg_len,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
		पूर्ण

		r_data->bytes_xfered = r_data->blocks
			- पढ़ोl(sock->addr + SOCK_MMCSD_NUM_BLOCKS) - 1;
		r_data->bytes_xfered *= r_data->blksz;
		r_data->bytes_xfered += r_data->blksz
			- पढ़ोl(sock->addr + SOCK_MMCSD_BLOCK_LEN) + 1;
	पूर्ण

	ग_लिखोl((~TIFM_CTRL_LED) & पढ़ोl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);

	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_request_करोne(mmc, mrq);
पूर्ण

अटल व्योम tअगरm_sd_पात(काष्ठा समयr_list *t)
अणु
	काष्ठा tअगरm_sd *host = from_समयr(host, t, समयr);

	pr_err("%s : card failed to respond for a long period of time "
	       "(%x, %x)\n",
	       dev_name(&host->dev->dev), host->req->cmd->opcode, host->cmd_flags);

	tअगरm_eject(host->dev);
पूर्ण

अटल व्योम tअगरm_sd_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा tअगरm_sd *host = mmc_priv(mmc);
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित पूर्णांक clk_भाग1, clk_भाग2;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sock->lock, flags);

	dev_dbg(&sock->dev, "ios: clock = %u, vdd = %x, bus_mode = %x, "
		"chip_select = %x, power_mode = %x, bus_width = %x\n",
		ios->घड़ी, ios->vdd, ios->bus_mode, ios->chip_select,
		ios->घातer_mode, ios->bus_width);

	अगर (ios->bus_width == MMC_BUS_WIDTH_4) अणु
		ग_लिखोl(TIFM_MMCSD_4BBUS | पढ़ोl(sock->addr + SOCK_MMCSD_CONFIG),
		       sock->addr + SOCK_MMCSD_CONFIG);
	पूर्ण अन्यथा अणु
		ग_लिखोl((~TIFM_MMCSD_4BBUS)
		       & पढ़ोl(sock->addr + SOCK_MMCSD_CONFIG),
		       sock->addr + SOCK_MMCSD_CONFIG);
	पूर्ण

	अगर (ios->घड़ी) अणु
		clk_भाग1 = 20000000 / ios->घड़ी;
		अगर (!clk_भाग1)
			clk_भाग1 = 1;

		clk_भाग2 = 24000000 / ios->घड़ी;
		अगर (!clk_भाग2)
			clk_भाग2 = 1;

		अगर ((20000000 / clk_भाग1) > ios->घड़ी)
			clk_भाग1++;
		अगर ((24000000 / clk_भाग2) > ios->घड़ी)
			clk_भाग2++;
		अगर ((20000000 / clk_भाग1) > (24000000 / clk_भाग2)) अणु
			host->clk_freq = 20000000;
			host->clk_भाग = clk_भाग1;
			ग_लिखोl((~TIFM_CTRL_FAST_CLK)
			       & पढ़ोl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		पूर्ण अन्यथा अणु
			host->clk_freq = 24000000;
			host->clk_भाग = clk_भाग2;
			ग_लिखोl(TIFM_CTRL_FAST_CLK
			       | पढ़ोl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		पूर्ण
	पूर्ण अन्यथा अणु
		host->clk_भाग = 0;
	पूर्ण
	host->clk_भाग &= TIFM_MMCSD_CLKMASK;
	ग_लिखोl(host->clk_भाग
	       | ((~TIFM_MMCSD_CLKMASK)
		  & पढ़ोl(sock->addr + SOCK_MMCSD_CONFIG)),
	       sock->addr + SOCK_MMCSD_CONFIG);

	host->खोलो_drain = (ios->bus_mode == MMC_BUSMODE_OPENDRAIN);

	/* chip_select : maybe later */
	//vdd
	//घातer is set beक्रमe probe / after हटाओ

	spin_unlock_irqrestore(&sock->lock, flags);
पूर्ण

अटल पूर्णांक tअगरm_sd_ro(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक rc = 0;
	काष्ठा tअगरm_sd *host = mmc_priv(mmc);
	काष्ठा tअगरm_dev *sock = host->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sock->lock, flags);
	अगर (TIFM_MMCSD_CARD_RO & पढ़ोl(sock->addr + SOCK_PRESENT_STATE))
		rc = 1;
	spin_unlock_irqrestore(&sock->lock, flags);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops tअगरm_sd_ops = अणु
	.request = tअगरm_sd_request,
	.set_ios = tअगरm_sd_ios,
	.get_ro  = tअगरm_sd_ro
पूर्ण;

अटल पूर्णांक tअगरm_sd_initialize_host(काष्ठा tअगरm_sd *host)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक host_status = 0;
	काष्ठा tअगरm_dev *sock = host->dev;

	ग_लिखोl(0, sock->addr + SOCK_MMCSD_INT_ENABLE);
	host->clk_भाग = 61;
	host->clk_freq = 20000000;
	ग_लिखोl(TIFM_MMCSD_RESET, sock->addr + SOCK_MMCSD_SYSTEM_CONTROL);
	ग_लिखोl(host->clk_भाग | TIFM_MMCSD_POWER,
	       sock->addr + SOCK_MMCSD_CONFIG);

	/* रुको up to 0.51 sec क्रम reset */
	क्रम (rc = 32; rc <= 256; rc <<= 1) अणु
		अगर (1 & पढ़ोl(sock->addr + SOCK_MMCSD_SYSTEM_STATUS)) अणु
			rc = 0;
			अवरोध;
		पूर्ण
		msleep(rc);
	पूर्ण

	अगर (rc) अणु
		pr_err("%s : controller failed to reset\n",
		       dev_name(&sock->dev));
		वापस -ENODEV;
	पूर्ण

	ग_लिखोl(0, sock->addr + SOCK_MMCSD_NUM_BLOCKS);
	ग_लिखोl(host->clk_भाग | TIFM_MMCSD_POWER,
	       sock->addr + SOCK_MMCSD_CONFIG);
	ग_लिखोl(TIFM_MMCSD_RXDE, sock->addr + SOCK_MMCSD_BUFFER_CONFIG);

	// command समयout fixed to 64 घड़ीs क्रम now
	ग_लिखोl(64, sock->addr + SOCK_MMCSD_COMMAND_TO);
	ग_लिखोl(TIFM_MMCSD_INAB, sock->addr + SOCK_MMCSD_COMMAND);

	क्रम (rc = 16; rc <= 64; rc <<= 1) अणु
		host_status = पढ़ोl(sock->addr + SOCK_MMCSD_STATUS);
		ग_लिखोl(host_status, sock->addr + SOCK_MMCSD_STATUS);
		अगर (!(host_status & TIFM_MMCSD_ERRMASK)
		    && (host_status & TIFM_MMCSD_EOC)) अणु
			rc = 0;
			अवरोध;
		पूर्ण
		msleep(rc);
	पूर्ण

	अगर (rc) अणु
		pr_err("%s : card not ready - probe failed on initialization\n",
		       dev_name(&sock->dev));
		वापस -ENODEV;
	पूर्ण

	ग_लिखोl(TIFM_MMCSD_CERR | TIFM_MMCSD_BRS | TIFM_MMCSD_EOC
	       | TIFM_MMCSD_ERRMASK,
	       sock->addr + SOCK_MMCSD_INT_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_sd_probe(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा tअगरm_sd *host;
	पूर्णांक rc = -EIO;

	अगर (!(TIFM_SOCK_STATE_OCCUPIED
	      & पढ़ोl(sock->addr + SOCK_PRESENT_STATE))) अणु
		pr_warn("%s : card gone, unexpectedly\n",
			dev_name(&sock->dev));
		वापस rc;
	पूर्ण

	mmc = mmc_alloc_host(माप(काष्ठा tअगरm_sd), &sock->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	tअगरm_set_drvdata(sock, mmc);
	host->dev = sock;
	host->समयout_jअगरfies = msecs_to_jअगरfies(TIFM_MMCSD_REQ_TIMEOUT_MS);
	/*
	 * We use a fixed request समयout of 1s, hence inक्रमm the core about it.
	 * A future improvement should instead respect the cmd->busy_समयout.
	 */
	mmc->max_busy_समयout = TIFM_MMCSD_REQ_TIMEOUT_MS;

	tasklet_setup(&host->finish_tasklet, tअगरm_sd_end_cmd);
	समयr_setup(&host->समयr, tअगरm_sd_पात, 0);

	mmc->ops = &tअगरm_sd_ops;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;
	mmc->f_min = 20000000 / 60;
	mmc->f_max = 24000000;

	mmc->max_blk_count = 2048;
	mmc->max_segs = mmc->max_blk_count;
	mmc->max_blk_size = min(TIFM_MMCSD_MAX_BLOCK_SIZE, PAGE_SIZE);
	mmc->max_seg_size = mmc->max_blk_count * mmc->max_blk_size;
	mmc->max_req_size = mmc->max_seg_size;

	sock->card_event = tअगरm_sd_card_event;
	sock->data_event = tअगरm_sd_data_event;
	rc = tअगरm_sd_initialize_host(host);

	अगर (!rc)
		rc = mmc_add_host(mmc);
	अगर (!rc)
		वापस 0;

	mmc_मुक्त_host(mmc);
	वापस rc;
पूर्ण

अटल व्योम tअगरm_sd_हटाओ(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा mmc_host *mmc = tअगरm_get_drvdata(sock);
	काष्ठा tअगरm_sd *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sock->lock, flags);
	host->eject = 1;
	ग_लिखोl(0, sock->addr + SOCK_MMCSD_INT_ENABLE);
	spin_unlock_irqrestore(&sock->lock, flags);

	tasklet_समाप्त(&host->finish_tasklet);

	spin_lock_irqsave(&sock->lock, flags);
	अगर (host->req) अणु
		ग_लिखोl(TIFM_FIFO_INT_SETALL,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
		ग_लिखोl(0, sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
		host->req->cmd->error = -ENOMEDIUM;
		अगर (host->req->stop)
			host->req->stop->error = -ENOMEDIUM;
		tasklet_schedule(&host->finish_tasklet);
	पूर्ण
	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_हटाओ_host(mmc);
	dev_dbg(&sock->dev, "after remove\n");

	mmc_मुक्त_host(mmc);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक tअगरm_sd_suspend(काष्ठा tअगरm_dev *sock, pm_message_t state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_sd_resume(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा mmc_host *mmc = tअगरm_get_drvdata(sock);
	काष्ठा tअगरm_sd *host = mmc_priv(mmc);
	पूर्णांक rc;

	rc = tअगरm_sd_initialize_host(host);
	dev_dbg(&sock->dev, "resume initialize %d\n", rc);

	अगर (rc)
		host->eject = 1;

	वापस rc;
पूर्ण

#अन्यथा

#घोषणा tअगरm_sd_suspend शून्य
#घोषणा tअगरm_sd_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा tअगरm_device_id tअगरm_sd_id_tbl[] = अणु
	अणु TIFM_TYPE_SD पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा tअगरm_driver tअगरm_sd_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
		.owner = THIS_MODULE
	पूर्ण,
	.id_table = tअगरm_sd_id_tbl,
	.probe    = tअगरm_sd_probe,
	.हटाओ   = tअगरm_sd_हटाओ,
	.suspend  = tअगरm_sd_suspend,
	.resume   = tअगरm_sd_resume
पूर्ण;

अटल पूर्णांक __init tअगरm_sd_init(व्योम)
अणु
	वापस tअगरm_रेजिस्टर_driver(&tअगरm_sd_driver);
पूर्ण

अटल व्योम __निकास tअगरm_sd_निकास(व्योम)
अणु
	tअगरm_unरेजिस्टर_driver(&tअगरm_sd_driver);
पूर्ण

MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("TI FlashMedia SD driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(tअगरm, tअगरm_sd_id_tbl);
MODULE_VERSION(DRIVER_VERSION);

module_init(tअगरm_sd_init);
module_निकास(tअगरm_sd_निकास);
