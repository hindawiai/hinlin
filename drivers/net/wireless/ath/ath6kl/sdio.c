<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sd.h>
#समावेश "hif.h"
#समावेश "hif-ops.h"
#समावेश "target.h"
#समावेश "debug.h"
#समावेश "cfg80211.h"
#समावेश "trace.h"

काष्ठा ath6kl_sdio अणु
	काष्ठा sdio_func *func;

	/* protects access to bus_req_मुक्तq */
	spinlock_t lock;

	/* मुक्त list */
	काष्ठा list_head bus_req_मुक्तq;

	/* available bus requests */
	काष्ठा bus_request bus_req[BUS_REQUEST_MAX_NUM];

	काष्ठा ath6kl *ar;

	u8 *dma_buffer;

	/* protects access to dma_buffer */
	काष्ठा mutex dma_buffer_mutex;

	/* scatter request list head */
	काष्ठा list_head scat_req;

	atomic_t irq_handling;
	रुको_queue_head_t irq_wq;

	/* protects access to scat_req */
	spinlock_t scat_lock;

	bool scatter_enabled;

	bool is_disabled;
	स्थिर काष्ठा sdio_device_id *id;
	काष्ठा work_काष्ठा wr_async_work;
	काष्ठा list_head wr_asyncq;

	/* protects access to wr_asyncq */
	spinlock_t wr_async_lock;
पूर्ण;

#घोषणा CMD53_ARG_READ          0
#घोषणा CMD53_ARG_WRITE         1
#घोषणा CMD53_ARG_BLOCK_BASIS   1
#घोषणा CMD53_ARG_FIXED_ADDRESS 0
#घोषणा CMD53_ARG_INCR_ADDRESS  1

अटल पूर्णांक ath6kl_sdio_config(काष्ठा ath6kl *ar);

अटल अंतरभूत काष्ठा ath6kl_sdio *ath6kl_sdio_priv(काष्ठा ath6kl *ar)
अणु
	वापस ar->hअगर_priv;
पूर्ण

/*
 * Macro to check अगर DMA buffer is WORD-aligned and DMA-able.
 * Most host controllers assume the buffer is DMA'able and will
 * bug-check otherwise (i.e. buffers on the stack). virt_addr_valid
 * check fails on stack memory.
 */
अटल अंतरभूत bool buf_needs_bounce(u8 *buf)
अणु
	वापस ((अचिन्हित दीर्घ) buf & 0x3) || !virt_addr_valid(buf);
पूर्ण

अटल व्योम ath6kl_sdio_set_mbox_info(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_mbox_info *mbox_info = &ar->mbox_info;

	/* EP1 has an extended range */
	mbox_info->htc_addr = HIF_MBOX_BASE_ADDR;
	mbox_info->htc_ext_addr = HIF_MBOX0_EXT_BASE_ADDR;
	mbox_info->htc_ext_sz = HIF_MBOX0_EXT_WIDTH;
	mbox_info->block_size = HIF_MBOX_BLOCK_SIZE;
	mbox_info->gmbox_addr = HIF_GMBOX_BASE_ADDR;
	mbox_info->gmbox_sz = HIF_GMBOX_WIDTH;
पूर्ण

अटल अंतरभूत व्योम ath6kl_sdio_set_cmd53_arg(u32 *arg, u8 rw, u8 func,
					     u8 mode, u8 opcode, u32 addr,
					     u16 blksz)
अणु
	*arg = (((rw & 1) << 31) |
		((func & 0x7) << 28) |
		((mode & 1) << 27) |
		((opcode & 1) << 26) |
		((addr & 0x1FFFF) << 9) |
		(blksz & 0x1FF));
पूर्ण

अटल अंतरभूत व्योम ath6kl_sdio_set_cmd52_arg(u32 *arg, u8 ग_लिखो, u8 raw,
					     अचिन्हित पूर्णांक address,
					     अचिन्हित अक्षर val)
अणु
	स्थिर u8 func = 0;

	*arg = ((ग_लिखो & 1) << 31) |
	       ((func & 0x7) << 28) |
	       ((raw & 1) << 27) |
	       (1 << 26) |
	       ((address & 0x1FFFF) << 9) |
	       (1 << 8) |
	       (val & 0xFF);
पूर्ण

अटल पूर्णांक ath6kl_sdio_func0_cmd52_wr_byte(काष्ठा mmc_card *card,
					   अचिन्हित पूर्णांक address,
					   अचिन्हित अक्षर byte)
अणु
	काष्ठा mmc_command io_cmd;

	स_रखो(&io_cmd, 0, माप(io_cmd));
	ath6kl_sdio_set_cmd52_arg(&io_cmd.arg, 1, 0, address, byte);
	io_cmd.opcode = SD_IO_RW_सूचीECT;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(card->host, &io_cmd, 0);
पूर्ण

अटल पूर्णांक ath6kl_sdio_io(काष्ठा sdio_func *func, u32 request, u32 addr,
			  u8 *buf, u32 len)
अणु
	पूर्णांक ret = 0;

	sdio_claim_host(func);

	अगर (request & HIF_WRITE) अणु
		/* FIXME: looks like ugly workaround क्रम something */
		अगर (addr >= HIF_MBOX_BASE_ADDR &&
		    addr <= HIF_MBOX_END_ADDR)
			addr += (HIF_MBOX_WIDTH - len);

		/* FIXME: this also looks like ugly workaround */
		अगर (addr == HIF_MBOX0_EXT_BASE_ADDR)
			addr += HIF_MBOX0_EXT_WIDTH - len;

		अगर (request & HIF_FIXED_ADDRESS)
			ret = sdio_ग_लिखोsb(func, addr, buf, len);
		अन्यथा
			ret = sdio_स_नकल_toio(func, addr, buf, len);
	पूर्ण अन्यथा अणु
		अगर (request & HIF_FIXED_ADDRESS)
			ret = sdio_पढ़ोsb(func, buf, addr, len);
		अन्यथा
			ret = sdio_स_नकल_fromio(func, buf, addr, len);
	पूर्ण

	sdio_release_host(func);

	ath6kl_dbg(ATH6KL_DBG_SDIO, "%s addr 0x%x%s buf 0x%p len %d\n",
		   request & HIF_WRITE ? "wr" : "rd", addr,
		   request & HIF_FIXED_ADDRESS ? " (fixed)" : "", buf, len);
	ath6kl_dbg_dump(ATH6KL_DBG_SDIO_DUMP, शून्य, "sdio ", buf, len);

	trace_ath6kl_sdio(addr, request, buf, len);

	वापस ret;
पूर्ण

अटल काष्ठा bus_request *ath6kl_sdio_alloc_busreq(काष्ठा ath6kl_sdio *ar_sdio)
अणु
	काष्ठा bus_request *bus_req;

	spin_lock_bh(&ar_sdio->lock);

	अगर (list_empty(&ar_sdio->bus_req_मुक्तq)) अणु
		spin_unlock_bh(&ar_sdio->lock);
		वापस शून्य;
	पूर्ण

	bus_req = list_first_entry(&ar_sdio->bus_req_मुक्तq,
				   काष्ठा bus_request, list);
	list_del(&bus_req->list);

	spin_unlock_bh(&ar_sdio->lock);
	ath6kl_dbg(ATH6KL_DBG_SCATTER, "%s: bus request 0x%p\n",
		   __func__, bus_req);

	वापस bus_req;
पूर्ण

अटल व्योम ath6kl_sdio_मुक्त_bus_req(काष्ठा ath6kl_sdio *ar_sdio,
				     काष्ठा bus_request *bus_req)
अणु
	ath6kl_dbg(ATH6KL_DBG_SCATTER, "%s: bus request 0x%p\n",
		   __func__, bus_req);

	spin_lock_bh(&ar_sdio->lock);
	list_add_tail(&bus_req->list, &ar_sdio->bus_req_मुक्तq);
	spin_unlock_bh(&ar_sdio->lock);
पूर्ण

अटल व्योम ath6kl_sdio_setup_scat_data(काष्ठा hअगर_scatter_req *scat_req,
					काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	data->blksz = HIF_MBOX_BLOCK_SIZE;
	data->blocks = scat_req->len / HIF_MBOX_BLOCK_SIZE;

	ath6kl_dbg(ATH6KL_DBG_SCATTER,
		   "hif-scatter: (%s) addr: 0x%X, (block len: %d, block count: %d) , (tot:%d,sg:%d)\n",
		   (scat_req->req & HIF_WRITE) ? "WR" : "RD", scat_req->addr,
		   data->blksz, data->blocks, scat_req->len,
		   scat_req->scat_entries);

	data->flags = (scat_req->req & HIF_WRITE) ? MMC_DATA_WRITE :
						    MMC_DATA_READ;

	/* fill SG entries */
	sg = scat_req->sgentries;
	sg_init_table(sg, scat_req->scat_entries);

	/* assemble SG list */
	क्रम (i = 0; i < scat_req->scat_entries; i++, sg++) अणु
		ath6kl_dbg(ATH6KL_DBG_SCATTER, "%d: addr:0x%p, len:%d\n",
			   i, scat_req->scat_list[i].buf,
			   scat_req->scat_list[i].len);

		sg_set_buf(sg, scat_req->scat_list[i].buf,
			   scat_req->scat_list[i].len);
	पूर्ण

	/* set scatter-gather table क्रम request */
	data->sg = scat_req->sgentries;
	data->sg_len = scat_req->scat_entries;
पूर्ण

अटल पूर्णांक ath6kl_sdio_scat_rw(काष्ठा ath6kl_sdio *ar_sdio,
			       काष्ठा bus_request *req)
अणु
	काष्ठा mmc_request mmc_req;
	काष्ठा mmc_command cmd;
	काष्ठा mmc_data data;
	काष्ठा hअगर_scatter_req *scat_req;
	u8 opcode, rw;
	पूर्णांक status, len;

	scat_req = req->scat_req;

	अगर (scat_req->virt_scat) अणु
		len = scat_req->len;
		अगर (scat_req->req & HIF_BLOCK_BASIS)
			len = round_करोwn(len, HIF_MBOX_BLOCK_SIZE);

		status = ath6kl_sdio_io(ar_sdio->func, scat_req->req,
					scat_req->addr, scat_req->virt_dma_buf,
					len);
		जाओ scat_complete;
	पूर्ण

	स_रखो(&mmc_req, 0, माप(काष्ठा mmc_request));
	स_रखो(&cmd, 0, माप(काष्ठा mmc_command));
	स_रखो(&data, 0, माप(काष्ठा mmc_data));

	ath6kl_sdio_setup_scat_data(scat_req, &data);

	opcode = (scat_req->req & HIF_FIXED_ADDRESS) ?
		  CMD53_ARG_FIXED_ADDRESS : CMD53_ARG_INCR_ADDRESS;

	rw = (scat_req->req & HIF_WRITE) ? CMD53_ARG_WRITE : CMD53_ARG_READ;

	/* Fixup the address so that the last byte will fall on MBOX EOM */
	अगर (scat_req->req & HIF_WRITE) अणु
		अगर (scat_req->addr == HIF_MBOX_BASE_ADDR)
			scat_req->addr += HIF_MBOX_WIDTH - scat_req->len;
		अन्यथा
			/* Uses extended address range */
			scat_req->addr += HIF_MBOX0_EXT_WIDTH - scat_req->len;
	पूर्ण

	/* set command argument */
	ath6kl_sdio_set_cmd53_arg(&cmd.arg, rw, ar_sdio->func->num,
				  CMD53_ARG_BLOCK_BASIS, opcode, scat_req->addr,
				  data.blocks);

	cmd.opcode = SD_IO_RW_EXTENDED;
	cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

	mmc_req.cmd = &cmd;
	mmc_req.data = &data;

	sdio_claim_host(ar_sdio->func);

	mmc_set_data_समयout(&data, ar_sdio->func->card);

	trace_ath6kl_sdio_scat(scat_req->addr,
			       scat_req->req,
			       scat_req->len,
			       scat_req->scat_entries,
			       scat_req->scat_list);

	/* synchronous call to process request */
	mmc_रुको_क्रम_req(ar_sdio->func->card->host, &mmc_req);

	sdio_release_host(ar_sdio->func);

	status = cmd.error ? cmd.error : data.error;

scat_complete:
	scat_req->status = status;

	अगर (scat_req->status)
		ath6kl_err("Scatter write request failed:%d\n",
			   scat_req->status);

	अगर (scat_req->req & HIF_ASYNCHRONOUS)
		scat_req->complete(ar_sdio->ar->htc_target, scat_req);

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_sdio_alloc_prep_scat_req(काष्ठा ath6kl_sdio *ar_sdio,
					   पूर्णांक n_scat_entry, पूर्णांक n_scat_req,
					   bool virt_scat)
अणु
	काष्ठा hअगर_scatter_req *s_req;
	काष्ठा bus_request *bus_req;
	पूर्णांक i, scat_req_sz, scat_list_sz, size;
	u8 *virt_buf;

	scat_list_sz = n_scat_entry * माप(काष्ठा hअगर_scatter_item);
	scat_req_sz = माप(*s_req) + scat_list_sz;

	अगर (!virt_scat)
		size = माप(काष्ठा scatterlist) * n_scat_entry;
	अन्यथा
		size =  2 * L1_CACHE_BYTES +
			ATH6KL_MAX_TRANSFER_SIZE_PER_SCATTER;

	क्रम (i = 0; i < n_scat_req; i++) अणु
		/* allocate the scatter request */
		s_req = kzalloc(scat_req_sz, GFP_KERNEL);
		अगर (!s_req)
			वापस -ENOMEM;

		अगर (virt_scat) अणु
			virt_buf = kzalloc(size, GFP_KERNEL);
			अगर (!virt_buf) अणु
				kमुक्त(s_req);
				वापस -ENOMEM;
			पूर्ण

			s_req->virt_dma_buf =
				(u8 *)L1_CACHE_ALIGN((अचिन्हित दीर्घ)virt_buf);
		पूर्ण अन्यथा अणु
			/* allocate sglist */
			s_req->sgentries = kzalloc(size, GFP_KERNEL);

			अगर (!s_req->sgentries) अणु
				kमुक्त(s_req);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		/* allocate a bus request क्रम this scatter request */
		bus_req = ath6kl_sdio_alloc_busreq(ar_sdio);
		अगर (!bus_req) अणु
			kमुक्त(s_req->sgentries);
			kमुक्त(s_req->virt_dma_buf);
			kमुक्त(s_req);
			वापस -ENOMEM;
		पूर्ण

		/* assign the scatter request to this bus request */
		bus_req->scat_req = s_req;
		s_req->busrequest = bus_req;

		s_req->virt_scat = virt_scat;

		/* add it to the scatter pool */
		hअगर_scatter_req_add(ar_sdio->ar, s_req);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_sdio_पढ़ो_ग_लिखो_sync(काष्ठा ath6kl *ar, u32 addr, u8 *buf,
				       u32 len, u32 request)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	u8  *tbuf = शून्य;
	पूर्णांक ret;
	bool bounced = false;

	अगर (request & HIF_BLOCK_BASIS)
		len = round_करोwn(len, HIF_MBOX_BLOCK_SIZE);

	अगर (buf_needs_bounce(buf)) अणु
		अगर (!ar_sdio->dma_buffer)
			वापस -ENOMEM;
		mutex_lock(&ar_sdio->dma_buffer_mutex);
		tbuf = ar_sdio->dma_buffer;

		अगर (request & HIF_WRITE)
			स_नकल(tbuf, buf, len);

		bounced = true;
	पूर्ण अन्यथा अणु
		tbuf = buf;
	पूर्ण

	ret = ath6kl_sdio_io(ar_sdio->func, request, addr, tbuf, len);
	अगर ((request & HIF_READ) && bounced)
		स_नकल(buf, tbuf, len);

	अगर (bounced)
		mutex_unlock(&ar_sdio->dma_buffer_mutex);

	वापस ret;
पूर्ण

अटल व्योम __ath6kl_sdio_ग_लिखो_async(काष्ठा ath6kl_sdio *ar_sdio,
				      काष्ठा bus_request *req)
अणु
	अगर (req->scat_req) अणु
		ath6kl_sdio_scat_rw(ar_sdio, req);
	पूर्ण अन्यथा अणु
		व्योम *context;
		पूर्णांक status;

		status = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar_sdio->ar, req->address,
						     req->buffer, req->length,
						     req->request);
		context = req->packet;
		ath6kl_sdio_मुक्त_bus_req(ar_sdio, req);
		ath6kl_hअगर_rw_comp_handler(context, status);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_sdio_ग_लिखो_async_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath6kl_sdio *ar_sdio;
	काष्ठा bus_request *req, *पंचांगp_req;

	ar_sdio = container_of(work, काष्ठा ath6kl_sdio, wr_async_work);

	spin_lock_bh(&ar_sdio->wr_async_lock);
	list_क्रम_each_entry_safe(req, पंचांगp_req, &ar_sdio->wr_asyncq, list) अणु
		list_del(&req->list);
		spin_unlock_bh(&ar_sdio->wr_async_lock);
		__ath6kl_sdio_ग_लिखो_async(ar_sdio, req);
		spin_lock_bh(&ar_sdio->wr_async_lock);
	पूर्ण
	spin_unlock_bh(&ar_sdio->wr_async_lock);
पूर्ण

अटल व्योम ath6kl_sdio_irq_handler(काष्ठा sdio_func *func)
अणु
	पूर्णांक status;
	काष्ठा ath6kl_sdio *ar_sdio;

	ath6kl_dbg(ATH6KL_DBG_SDIO, "irq\n");

	ar_sdio = sdio_get_drvdata(func);
	atomic_set(&ar_sdio->irq_handling, 1);
	/*
	 * Release the host during पूर्णांकerrups so we can pick it back up when
	 * we process commands.
	 */
	sdio_release_host(ar_sdio->func);

	status = ath6kl_hअगर_पूर्णांकr_bh_handler(ar_sdio->ar);
	sdio_claim_host(ar_sdio->func);

	atomic_set(&ar_sdio->irq_handling, 0);
	wake_up(&ar_sdio->irq_wq);

	WARN_ON(status && status != -ECANCELED);
पूर्ण

अटल पूर्णांक ath6kl_sdio_घातer_on(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret = 0;

	अगर (!ar_sdio->is_disabled)
		वापस 0;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "sdio power on\n");

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret) अणु
		ath6kl_err("Unable to enable sdio func: %d)\n", ret);
		sdio_release_host(func);
		वापस ret;
	पूर्ण

	sdio_release_host(func);

	/*
	 * Wait क्रम hardware to initialise. It should take a lot less than
	 * 10 ms but let's be conservative here.
	 */
	msleep(10);

	ret = ath6kl_sdio_config(ar);
	अगर (ret) अणु
		ath6kl_err("Failed to config sdio: %d\n", ret);
		जाओ out;
	पूर्ण

	ar_sdio->is_disabled = false;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_sdio_घातer_off(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	पूर्णांक ret;

	अगर (ar_sdio->is_disabled)
		वापस 0;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "sdio power off\n");

	/* Disable the card */
	sdio_claim_host(ar_sdio->func);
	ret = sdio_disable_func(ar_sdio->func);
	sdio_release_host(ar_sdio->func);

	अगर (ret)
		वापस ret;

	ar_sdio->is_disabled = true;

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_sdio_ग_लिखो_async(काष्ठा ath6kl *ar, u32 address, u8 *buffer,
				   u32 length, u32 request,
				   काष्ठा htc_packet *packet)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा bus_request *bus_req;

	bus_req = ath6kl_sdio_alloc_busreq(ar_sdio);

	अगर (WARN_ON_ONCE(!bus_req))
		वापस -ENOMEM;

	bus_req->address = address;
	bus_req->buffer = buffer;
	bus_req->length = length;
	bus_req->request = request;
	bus_req->packet = packet;

	spin_lock_bh(&ar_sdio->wr_async_lock);
	list_add_tail(&bus_req->list, &ar_sdio->wr_asyncq);
	spin_unlock_bh(&ar_sdio->wr_async_lock);
	queue_work(ar->ath6kl_wq, &ar_sdio->wr_async_work);

	वापस 0;
पूर्ण

अटल व्योम ath6kl_sdio_irq_enable(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	पूर्णांक ret;

	sdio_claim_host(ar_sdio->func);

	/* Register the isr */
	ret =  sdio_claim_irq(ar_sdio->func, ath6kl_sdio_irq_handler);
	अगर (ret)
		ath6kl_err("Failed to claim sdio irq: %d\n", ret);

	sdio_release_host(ar_sdio->func);
पूर्ण

अटल bool ath6kl_sdio_is_on_irq(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);

	वापस !atomic_पढ़ो(&ar_sdio->irq_handling);
पूर्ण

अटल व्योम ath6kl_sdio_irq_disable(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	पूर्णांक ret;

	sdio_claim_host(ar_sdio->func);

	अगर (atomic_पढ़ो(&ar_sdio->irq_handling)) अणु
		sdio_release_host(ar_sdio->func);

		ret = रुको_event_पूर्णांकerruptible(ar_sdio->irq_wq,
					       ath6kl_sdio_is_on_irq(ar));
		अगर (ret)
			वापस;

		sdio_claim_host(ar_sdio->func);
	पूर्ण

	ret = sdio_release_irq(ar_sdio->func);
	अगर (ret)
		ath6kl_err("Failed to release sdio irq: %d\n", ret);

	sdio_release_host(ar_sdio->func);
पूर्ण

अटल काष्ठा hअगर_scatter_req *ath6kl_sdio_scatter_req_get(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा hअगर_scatter_req *node = शून्य;

	spin_lock_bh(&ar_sdio->scat_lock);

	अगर (!list_empty(&ar_sdio->scat_req)) अणु
		node = list_first_entry(&ar_sdio->scat_req,
					काष्ठा hअगर_scatter_req, list);
		list_del(&node->list);

		node->scat_q_depth = get_queue_depth(&ar_sdio->scat_req);
	पूर्ण

	spin_unlock_bh(&ar_sdio->scat_lock);

	वापस node;
पूर्ण

अटल व्योम ath6kl_sdio_scatter_req_add(काष्ठा ath6kl *ar,
					काष्ठा hअगर_scatter_req *s_req)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);

	spin_lock_bh(&ar_sdio->scat_lock);

	list_add_tail(&s_req->list, &ar_sdio->scat_req);

	spin_unlock_bh(&ar_sdio->scat_lock);
पूर्ण

/* scatter gather पढ़ो ग_लिखो request */
अटल पूर्णांक ath6kl_sdio_async_rw_scatter(काष्ठा ath6kl *ar,
					काष्ठा hअगर_scatter_req *scat_req)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	u32 request = scat_req->req;
	पूर्णांक status = 0;

	अगर (!scat_req->len)
		वापस -EINVAL;

	ath6kl_dbg(ATH6KL_DBG_SCATTER,
		   "hif-scatter: total len: %d scatter entries: %d\n",
		   scat_req->len, scat_req->scat_entries);

	अगर (request & HIF_SYNCHRONOUS) अणु
		status = ath6kl_sdio_scat_rw(ar_sdio, scat_req->busrequest);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&ar_sdio->wr_async_lock);
		list_add_tail(&scat_req->busrequest->list, &ar_sdio->wr_asyncq);
		spin_unlock_bh(&ar_sdio->wr_async_lock);
		queue_work(ar->ath6kl_wq, &ar_sdio->wr_async_work);
	पूर्ण

	वापस status;
पूर्ण

/* clean up scatter support */
अटल व्योम ath6kl_sdio_cleanup_scatter(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा hअगर_scatter_req *s_req, *पंचांगp_req;

	/* empty the मुक्त list */
	spin_lock_bh(&ar_sdio->scat_lock);
	list_क्रम_each_entry_safe(s_req, पंचांगp_req, &ar_sdio->scat_req, list) अणु
		list_del(&s_req->list);
		spin_unlock_bh(&ar_sdio->scat_lock);

		/*
		 * FIXME: should we also call completion handler with
		 * ath6kl_hअगर_rw_comp_handler() with status -ECANCELED so
		 * that the packet is properly मुक्तd?
		 */
		अगर (s_req->busrequest) अणु
			s_req->busrequest->scat_req = शून्य;
			ath6kl_sdio_मुक्त_bus_req(ar_sdio, s_req->busrequest);
		पूर्ण
		kमुक्त(s_req->virt_dma_buf);
		kमुक्त(s_req->sgentries);
		kमुक्त(s_req);

		spin_lock_bh(&ar_sdio->scat_lock);
	पूर्ण
	spin_unlock_bh(&ar_sdio->scat_lock);

	ar_sdio->scatter_enabled = false;
पूर्ण

/* setup of HIF scatter resources */
अटल पूर्णांक ath6kl_sdio_enable_scatter(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा htc_target *target = ar->htc_target;
	पूर्णांक ret = 0;
	bool virt_scat = false;

	अगर (ar_sdio->scatter_enabled)
		वापस 0;

	ar_sdio->scatter_enabled = true;

	/* check अगर host supports scatter and it meets our requirements */
	अगर (ar_sdio->func->card->host->max_segs < MAX_SCATTER_ENTRIES_PER_REQ) अणु
		ath6kl_err("host only supports scatter of :%d entries, need: %d\n",
			   ar_sdio->func->card->host->max_segs,
			   MAX_SCATTER_ENTRIES_PER_REQ);
		virt_scat = true;
	पूर्ण

	अगर (!virt_scat) अणु
		ret = ath6kl_sdio_alloc_prep_scat_req(ar_sdio,
				MAX_SCATTER_ENTRIES_PER_REQ,
				MAX_SCATTER_REQUESTS, virt_scat);

		अगर (!ret) अणु
			ath6kl_dbg(ATH6KL_DBG_BOOT,
				   "hif-scatter enabled requests %d entries %d\n",
				   MAX_SCATTER_REQUESTS,
				   MAX_SCATTER_ENTRIES_PER_REQ);

			target->max_scat_entries = MAX_SCATTER_ENTRIES_PER_REQ;
			target->max_xfer_szper_scatreq =
						MAX_SCATTER_REQ_TRANSFER_SIZE;
		पूर्ण अन्यथा अणु
			ath6kl_sdio_cleanup_scatter(ar);
			ath6kl_warn("hif scatter resource setup failed, trying virtual scatter method\n");
		पूर्ण
	पूर्ण

	अगर (virt_scat || ret) अणु
		ret = ath6kl_sdio_alloc_prep_scat_req(ar_sdio,
				ATH6KL_SCATTER_ENTRIES_PER_REQ,
				ATH6KL_SCATTER_REQS, virt_scat);

		अगर (ret) अणु
			ath6kl_err("failed to alloc virtual scatter resources !\n");
			ath6kl_sdio_cleanup_scatter(ar);
			वापस ret;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_BOOT,
			   "virtual scatter enabled requests %d entries %d\n",
			   ATH6KL_SCATTER_REQS, ATH6KL_SCATTER_ENTRIES_PER_REQ);

		target->max_scat_entries = ATH6KL_SCATTER_ENTRIES_PER_REQ;
		target->max_xfer_szper_scatreq =
					ATH6KL_MAX_TRANSFER_SIZE_PER_SCATTER;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_sdio_config(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	अगर (ar_sdio->id->device >= SDIO_DEVICE_ID_ATHEROS_AR6003_00) अणु
		/* enable 4-bit ASYNC पूर्णांकerrupt on AR6003 or later */
		ret = ath6kl_sdio_func0_cmd52_wr_byte(func->card,
						CCCR_SDIO_IRQ_MODE_REG,
						SDIO_IRQ_MODE_ASYNC_4BIT_IRQ);
		अगर (ret) अणु
			ath6kl_err("Failed to enable 4-bit async irq mode %d\n",
				   ret);
			जाओ out;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_BOOT, "4-bit async irq mode enabled\n");
	पूर्ण

	/* give us some समय to enable, in ms */
	func->enable_समयout = 100;

	ret = sdio_set_block_size(func, HIF_MBOX_BLOCK_SIZE);
	अगर (ret) अणु
		ath6kl_err("Set sdio block size %d failed: %d)\n",
			   HIF_MBOX_BLOCK_SIZE, ret);
		जाओ out;
	पूर्ण

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_set_sdio_pm_caps(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	mmc_pm_flag_t flags;
	पूर्णांक ret;

	flags = sdio_get_host_pm_caps(func);

	ath6kl_dbg(ATH6KL_DBG_SUSPEND, "sdio suspend pm_caps 0x%x\n", flags);

	अगर (!(flags & MMC_PM_WAKE_SDIO_IRQ) ||
	    !(flags & MMC_PM_KEEP_POWER))
		वापस -EINVAL;

	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	अगर (ret) अणु
		ath6kl_err("set sdio keep pwr flag failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* sdio irq wakes up host */
	ret = sdio_set_host_pm_flags(func, MMC_PM_WAKE_SDIO_IRQ);
	अगर (ret)
		ath6kl_err("set sdio wake irq flag failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_sdio_suspend(काष्ठा ath6kl *ar, काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	mmc_pm_flag_t flags;
	bool try_deepsleep = false;
	पूर्णांक ret;

	अगर (ar->suspend_mode == WLAN_POWER_STATE_WOW ||
	    (!ar->suspend_mode && wow)) अणु
		ret = ath6kl_set_sdio_pm_caps(ar);
		अगर (ret)
			जाओ cut_pwr;

		ret = ath6kl_cfg80211_suspend(ar, ATH6KL_CFG_SUSPEND_WOW, wow);
		अगर (ret && ret != -ENOTCONN)
			ath6kl_err("wow suspend failed: %d\n", ret);

		अगर (ret &&
		    (!ar->wow_suspend_mode ||
		     ar->wow_suspend_mode == WLAN_POWER_STATE_DEEP_SLEEP))
			try_deepsleep = true;
		अन्यथा अगर (ret &&
			 ar->wow_suspend_mode == WLAN_POWER_STATE_CUT_PWR)
			जाओ cut_pwr;
		अगर (!ret)
			वापस 0;
	पूर्ण

	अगर (ar->suspend_mode == WLAN_POWER_STATE_DEEP_SLEEP ||
	    !ar->suspend_mode || try_deepsleep) अणु
		flags = sdio_get_host_pm_caps(func);
		अगर (!(flags & MMC_PM_KEEP_POWER))
			जाओ cut_pwr;

		ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
		अगर (ret)
			जाओ cut_pwr;

		/*
		 * Workaround to support Deep Sleep with MSM, set the host pm
		 * flag as MMC_PM_WAKE_SDIO_IRQ to allow SDCC deiver to disable
		 * the sdc2_घड़ी and पूर्णांकernally allows MSM to enter
		 * TCXO shutकरोwn properly.
		 */
		अगर ((flags & MMC_PM_WAKE_SDIO_IRQ)) अणु
			ret = sdio_set_host_pm_flags(func,
						MMC_PM_WAKE_SDIO_IRQ);
			अगर (ret)
				जाओ cut_pwr;
		पूर्ण

		ret = ath6kl_cfg80211_suspend(ar, ATH6KL_CFG_SUSPEND_DEEPSLEEP,
					      शून्य);
		अगर (ret)
			जाओ cut_pwr;

		वापस 0;
	पूर्ण

cut_pwr:
	अगर (func->card && func->card->host)
		func->card->host->pm_flags &= ~MMC_PM_KEEP_POWER;

	वापस ath6kl_cfg80211_suspend(ar, ATH6KL_CFG_SUSPEND_CUTPOWER, शून्य);
पूर्ण

अटल पूर्णांक ath6kl_sdio_resume(काष्ठा ath6kl *ar)
अणु
	चयन (ar->state) अणु
	हाल ATH6KL_STATE_OFF:
	हाल ATH6KL_STATE_CUTPOWER:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND,
			   "sdio resume configuring sdio\n");

		/* need to set sdio settings after घातer is cut from sdio */
		ath6kl_sdio_config(ar);
		अवरोध;

	हाल ATH6KL_STATE_ON:
		अवरोध;

	हाल ATH6KL_STATE_DEEPSLEEP:
		अवरोध;

	हाल ATH6KL_STATE_WOW:
		अवरोध;

	हाल ATH6KL_STATE_SUSPENDING:
		अवरोध;

	हाल ATH6KL_STATE_RESUMING:
		अवरोध;

	हाल ATH6KL_STATE_RECOVERY:
		अवरोध;
	पूर्ण

	ath6kl_cfg80211_resume(ar);

	वापस 0;
पूर्ण

/* set the winकरोw address रेजिस्टर (using 4-byte रेजिस्टर access ). */
अटल पूर्णांक ath6kl_set_addrwin_reg(काष्ठा ath6kl *ar, u32 reg_addr, u32 addr)
अणु
	पूर्णांक status;
	u8 addr_val[4];
	s32 i;

	/*
	 * Write bytes 1,2,3 of the रेजिस्टर to set the upper address bytes,
	 * the LSB is written last to initiate the access cycle
	 */

	क्रम (i = 1; i <= 3; i++) अणु
		/*
		 * Fill the buffer with the address byte value we want to
		 * hit 4 बार.
		 */
		स_रखो(addr_val, ((u8 *)&addr)[i], 4);

		/*
		 * Hit each byte of the रेजिस्टर address with a 4-byte
		 * ग_लिखो operation to the same address, this is a harmless
		 * operation.
		 */
		status = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, reg_addr + i, addr_val,
					     4, HIF_WR_SYNC_BYTE_FIX);
		अगर (status)
			अवरोध;
	पूर्ण

	अगर (status) अणु
		ath6kl_err("%s: failed to write initial bytes of 0x%x to window reg: 0x%X\n",
			   __func__, addr, reg_addr);
		वापस status;
	पूर्ण

	/*
	 * Write the address रेजिस्टर again, this समय ग_लिखो the whole
	 * 4-byte value. The effect here is that the LSB ग_लिखो causes the
	 * cycle to start, the extra 3 byte ग_लिखो to bytes 1,2,3 has no
	 * effect since we are writing the same values again
	 */
	status = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, reg_addr, (u8 *)(&addr),
				     4, HIF_WR_SYNC_BYTE_INC);

	अगर (status) अणु
		ath6kl_err("%s: failed to write 0x%x to window reg: 0x%X\n",
			   __func__, addr, reg_addr);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_sdio_diag_पढ़ो32(काष्ठा ath6kl *ar, u32 address, u32 *data)
अणु
	पूर्णांक status;

	/* set winकरोw रेजिस्टर to start पढ़ो cycle */
	status = ath6kl_set_addrwin_reg(ar, WINDOW_READ_ADDR_ADDRESS,
					address);

	अगर (status)
		वापस status;

	/* पढ़ो the data */
	status = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, WINDOW_DATA_ADDRESS,
				(u8 *)data, माप(u32), HIF_RD_SYNC_BYTE_INC);
	अगर (status) अणु
		ath6kl_err("%s: failed to read from window data addr\n",
			   __func__);
		वापस status;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_sdio_diag_ग_लिखो32(काष्ठा ath6kl *ar, u32 address,
				    __le32 data)
अणु
	पूर्णांक status;
	u32 val = (__क्रमce u32) data;

	/* set ग_लिखो data */
	status = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, WINDOW_DATA_ADDRESS,
				(u8 *) &val, माप(u32), HIF_WR_SYNC_BYTE_INC);
	अगर (status) अणु
		ath6kl_err("%s: failed to write 0x%x to window data addr\n",
			   __func__, data);
		वापस status;
	पूर्ण

	/* set winकरोw रेजिस्टर, which starts the ग_लिखो cycle */
	वापस ath6kl_set_addrwin_reg(ar, WINDOW_WRITE_ADDR_ADDRESS,
				      address);
पूर्ण

अटल पूर्णांक ath6kl_sdio_bmi_credits(काष्ठा ath6kl *ar)
अणु
	u32 addr;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	ar->bmi.cmd_credits = 0;

	/* Read the counter रेजिस्टर to get the command credits */
	addr = COUNT_DEC_ADDRESS + (HTC_MAILBOX_NUM_MAX + ENDPOINT1) * 4;

	समयout = jअगरfies + msecs_to_jअगरfies(BMI_COMMUNICATION_TIMEOUT);
	जबतक (समय_beक्रमe(jअगरfies, समयout) && !ar->bmi.cmd_credits) अणु
		/*
		 * Hit the credit counter with a 4-byte access, the first byte
		 * पढ़ो will hit the counter and cause a decrement, जबतक the
		 * reमुख्यing 3 bytes has no effect. The rationale behind this
		 * is to make all HIF accesses 4-byte aligned.
		 */
		ret = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, addr,
					 (u8 *)&ar->bmi.cmd_credits, 4,
					 HIF_RD_SYNC_BYTE_INC);
		अगर (ret) अणु
			ath6kl_err("Unable to decrement the command credit count register: %d\n",
				   ret);
			वापस ret;
		पूर्ण

		/* The counter is only 8 bits.
		 * Ignore anything in the upper 3 bytes
		 */
		ar->bmi.cmd_credits &= 0xFF;
	पूर्ण

	अगर (!ar->bmi.cmd_credits) अणु
		ath6kl_err("bmi communication timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_bmi_get_rx_lkahd(काष्ठा ath6kl *ar)
अणु
	अचिन्हित दीर्घ समयout;
	u32 rx_word = 0;
	पूर्णांक ret = 0;

	समयout = jअगरfies + msecs_to_jअगरfies(BMI_COMMUNICATION_TIMEOUT);
	जबतक ((समय_beक्रमe(jअगरfies, समयout)) && !rx_word) अणु
		ret = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar,
					RX_LOOKAHEAD_VALID_ADDRESS,
					(u8 *)&rx_word, माप(rx_word),
					HIF_RD_SYNC_BYTE_INC);
		अगर (ret) अणु
			ath6kl_err("unable to read RX_LOOKAHEAD_VALID\n");
			वापस ret;
		पूर्ण

		 /* all we really want is one bit */
		rx_word &= (1 << ENDPOINT1);
	पूर्ण

	अगर (!rx_word) अणु
		ath6kl_err("bmi_recv_buf FIFO empty\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_sdio_bmi_ग_लिखो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	पूर्णांक ret;
	u32 addr;

	ret = ath6kl_sdio_bmi_credits(ar);
	अगर (ret)
		वापस ret;

	addr = ar->mbox_info.htc_addr;

	ret = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, addr, buf, len,
					  HIF_WR_SYNC_BYTE_INC);
	अगर (ret) अणु
		ath6kl_err("unable to send the bmi data to the device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_sdio_bmi_पढ़ो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	पूर्णांक ret;
	u32 addr;

	/*
	 * During normal bootup, small पढ़ोs may be required.
	 * Rather than issue an HIF Read and then रुको as the Target
	 * adds successive bytes to the FIFO, we रुको here until
	 * we know that response data is available.
	 *
	 * This allows us to cleanly समयout on an unexpected
	 * Target failure rather than risk problems at the HIF level.
	 * In particular, this aव्योमs SDIO समयouts and possibly garbage
	 * data on some host controllers.  And on an पूर्णांकerconnect
	 * such as Compact Flash (as well as some SDIO masters) which
	 * करोes not provide any indication on data समयout, it aव्योमs
	 * a potential hang or garbage response.
	 *
	 * Synchronization is more dअगरficult क्रम पढ़ोs larger than the
	 * size of the MBOX FIFO (128B), because the Target is unable
	 * to push the 129th byte of data until AFTER the Host posts an
	 * HIF Read and हटाओs some FIFO data.  So क्रम large पढ़ोs the
	 * Host proceeds to post an HIF Read BEFORE all the data is
	 * actually available to पढ़ो.  Fortunately, large BMI पढ़ोs करो
	 * not occur in practice -- they're supported क्रम debug/development.
	 *
	 * So Host/Target BMI synchronization is भागided पूर्णांकo these हालs:
	 *  CASE 1: length < 4
	 *        Should not happen
	 *
	 *  CASE 2: 4 <= length <= 128
	 *        Wait क्रम first 4 bytes to be in FIFO
	 *        If CONSERVATIVE_BMI_READ is enabled, also रुको क्रम
	 *        a BMI command credit, which indicates that the ENTIRE
	 *        response is available in the the FIFO
	 *
	 *  CASE 3: length > 128
	 *        Wait क्रम the first 4 bytes to be in FIFO
	 *
	 * For most uses, a small समयout should be sufficient and we will
	 * usually see a response quickly; but there may be some unusual
	 * (debug) हालs of BMI_EXECUTE where we want an larger समयout.
	 * For now, we use an unbounded busy loop जबतक रुकोing क्रम
	 * BMI_EXECUTE.
	 *
	 * If BMI_EXECUTE ever needs to support दीर्घer-latency execution,
	 * especially in production, this code needs to be enhanced to sleep
	 * and yield.  Also note that BMI_COMMUNICATION_TIMEOUT is currently
	 * a function of Host processor speed.
	 */
	अगर (len >= 4) अणु /* NB: Currently, always true */
		ret = ath6kl_bmi_get_rx_lkahd(ar);
		अगर (ret)
			वापस ret;
	पूर्ण

	addr = ar->mbox_info.htc_addr;
	ret = ath6kl_sdio_पढ़ो_ग_लिखो_sync(ar, addr, buf, len,
				  HIF_RD_SYNC_BYTE_INC);
	अगर (ret) अणु
		ath6kl_err("Unable to read the bmi data from the device: %d\n",
			   ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath6kl_sdio_stop(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	काष्ठा bus_request *req, *पंचांगp_req;
	व्योम *context;

	/* FIXME: make sure that wq is not queued again */

	cancel_work_sync(&ar_sdio->wr_async_work);

	spin_lock_bh(&ar_sdio->wr_async_lock);

	list_क्रम_each_entry_safe(req, पंचांगp_req, &ar_sdio->wr_asyncq, list) अणु
		list_del(&req->list);

		अगर (req->scat_req) अणु
			/* this is a scatter gather request */
			req->scat_req->status = -ECANCELED;
			req->scat_req->complete(ar_sdio->ar->htc_target,
						req->scat_req);
		पूर्ण अन्यथा अणु
			context = req->packet;
			ath6kl_sdio_मुक्त_bus_req(ar_sdio, req);
			ath6kl_hअगर_rw_comp_handler(context, -ECANCELED);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ar_sdio->wr_async_lock);

	WARN_ON(get_queue_depth(&ar_sdio->scat_req) != 4);
पूर्ण

अटल स्थिर काष्ठा ath6kl_hअगर_ops ath6kl_sdio_ops = अणु
	.पढ़ो_ग_लिखो_sync = ath6kl_sdio_पढ़ो_ग_लिखो_sync,
	.ग_लिखो_async = ath6kl_sdio_ग_लिखो_async,
	.irq_enable = ath6kl_sdio_irq_enable,
	.irq_disable = ath6kl_sdio_irq_disable,
	.scatter_req_get = ath6kl_sdio_scatter_req_get,
	.scatter_req_add = ath6kl_sdio_scatter_req_add,
	.enable_scatter = ath6kl_sdio_enable_scatter,
	.scat_req_rw = ath6kl_sdio_async_rw_scatter,
	.cleanup_scatter = ath6kl_sdio_cleanup_scatter,
	.suspend = ath6kl_sdio_suspend,
	.resume = ath6kl_sdio_resume,
	.diag_पढ़ो32 = ath6kl_sdio_diag_पढ़ो32,
	.diag_ग_लिखो32 = ath6kl_sdio_diag_ग_लिखो32,
	.bmi_पढ़ो = ath6kl_sdio_bmi_पढ़ो,
	.bmi_ग_लिखो = ath6kl_sdio_bmi_ग_लिखो,
	.घातer_on = ath6kl_sdio_घातer_on,
	.घातer_off = ath6kl_sdio_घातer_off,
	.stop = ath6kl_sdio_stop,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP

/*
 * Empty handlers so that mmc subप्रणाली करोesn't हटाओ us entirely during
 * suspend. We instead follow cfg80211 suspend/resume handlers.
 */
अटल पूर्णांक ath6kl_sdio_pm_suspend(काष्ठा device *device)
अणु
	ath6kl_dbg(ATH6KL_DBG_SUSPEND, "sdio pm suspend\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_sdio_pm_resume(काष्ठा device *device)
अणु
	ath6kl_dbg(ATH6KL_DBG_SUSPEND, "sdio pm resume\n");

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath6kl_sdio_pm_ops, ath6kl_sdio_pm_suspend,
			 ath6kl_sdio_pm_resume);

#घोषणा ATH6KL_SDIO_PM_OPS (&ath6kl_sdio_pm_ops)

#अन्यथा

#घोषणा ATH6KL_SDIO_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक ath6kl_sdio_probe(काष्ठा sdio_func *func,
			     स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा ath6kl_sdio *ar_sdio;
	काष्ठा ath6kl *ar;
	पूर्णांक count;

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "sdio new func %d vendor 0x%x device 0x%x block 0x%x/0x%x\n",
		   func->num, func->venकरोr, func->device,
		   func->max_blksize, func->cur_blksize);

	ar_sdio = kzalloc(माप(काष्ठा ath6kl_sdio), GFP_KERNEL);
	अगर (!ar_sdio)
		वापस -ENOMEM;

	ar_sdio->dma_buffer = kzalloc(HIF_DMA_BUFFER_SIZE, GFP_KERNEL);
	अगर (!ar_sdio->dma_buffer) अणु
		ret = -ENOMEM;
		जाओ err_hअगर;
	पूर्ण

	ar_sdio->func = func;
	sdio_set_drvdata(func, ar_sdio);

	ar_sdio->id = id;
	ar_sdio->is_disabled = true;

	spin_lock_init(&ar_sdio->lock);
	spin_lock_init(&ar_sdio->scat_lock);
	spin_lock_init(&ar_sdio->wr_async_lock);
	mutex_init(&ar_sdio->dma_buffer_mutex);

	INIT_LIST_HEAD(&ar_sdio->scat_req);
	INIT_LIST_HEAD(&ar_sdio->bus_req_मुक्तq);
	INIT_LIST_HEAD(&ar_sdio->wr_asyncq);

	INIT_WORK(&ar_sdio->wr_async_work, ath6kl_sdio_ग_लिखो_async_work);

	init_रुकोqueue_head(&ar_sdio->irq_wq);

	क्रम (count = 0; count < BUS_REQUEST_MAX_NUM; count++)
		ath6kl_sdio_मुक्त_bus_req(ar_sdio, &ar_sdio->bus_req[count]);

	ar = ath6kl_core_create(&ar_sdio->func->dev);
	अगर (!ar) अणु
		ath6kl_err("Failed to alloc ath6kl core\n");
		ret = -ENOMEM;
		जाओ err_dma;
	पूर्ण

	ar_sdio->ar = ar;
	ar->hअगर_type = ATH6KL_HIF_TYPE_SDIO;
	ar->hअगर_priv = ar_sdio;
	ar->hअगर_ops = &ath6kl_sdio_ops;
	ar->bmi.max_data_size = 256;

	ath6kl_sdio_set_mbox_info(ar);

	ret = ath6kl_sdio_config(ar);
	अगर (ret) अणु
		ath6kl_err("Failed to config sdio: %d\n", ret);
		जाओ err_core_alloc;
	पूर्ण

	ret = ath6kl_core_init(ar, ATH6KL_HTC_TYPE_MBOX);
	अगर (ret) अणु
		ath6kl_err("Failed to init ath6kl core\n");
		जाओ err_core_alloc;
	पूर्ण

	वापस ret;

err_core_alloc:
	ath6kl_core_destroy(ar_sdio->ar);
err_dma:
	kमुक्त(ar_sdio->dma_buffer);
err_hअगर:
	kमुक्त(ar_sdio);

	वापस ret;
पूर्ण

अटल व्योम ath6kl_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा ath6kl_sdio *ar_sdio;

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "sdio removed func %d vendor 0x%x device 0x%x\n",
		   func->num, func->venकरोr, func->device);

	ar_sdio = sdio_get_drvdata(func);

	ath6kl_stop_txrx(ar_sdio->ar);
	cancel_work_sync(&ar_sdio->wr_async_work);

	ath6kl_core_cleanup(ar_sdio->ar);
	ath6kl_core_destroy(ar_sdio->ar);

	kमुक्त(ar_sdio->dma_buffer);
	kमुक्त(ar_sdio);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id ath6kl_sdio_devices[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6003_00)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6003_01)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6004_00)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6004_01)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6004_02)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6004_18)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6004_19)पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, ath6kl_sdio_devices);

अटल काष्ठा sdio_driver ath6kl_sdio_driver = अणु
	.name = "ath6kl_sdio",
	.id_table = ath6kl_sdio_devices,
	.probe = ath6kl_sdio_probe,
	.हटाओ = ath6kl_sdio_हटाओ,
	.drv.pm = ATH6KL_SDIO_PM_OPS,
पूर्ण;

अटल पूर्णांक __init ath6kl_sdio_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sdio_रेजिस्टर_driver(&ath6kl_sdio_driver);
	अगर (ret)
		ath6kl_err("sdio driver registration failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम __निकास ath6kl_sdio_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&ath6kl_sdio_driver);
पूर्ण

module_init(ath6kl_sdio_init);
module_निकास(ath6kl_sdio_निकास);

MODULE_AUTHOR("Atheros Communications, Inc.");
MODULE_DESCRIPTION("Driver support for Atheros AR600x SDIO devices");
MODULE_LICENSE("Dual BSD/GPL");

MODULE_FIRMWARE(AR6003_HW_2_0_FW_सूची "/" AR6003_HW_2_0_OTP_खाता);
MODULE_FIRMWARE(AR6003_HW_2_0_FW_सूची "/" AR6003_HW_2_0_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6003_HW_2_0_FW_सूची "/" AR6003_HW_2_0_PATCH_खाता);
MODULE_FIRMWARE(AR6003_HW_2_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6003_HW_2_0_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6003_HW_2_1_1_FW_सूची "/" AR6003_HW_2_1_1_OTP_खाता);
MODULE_FIRMWARE(AR6003_HW_2_1_1_FW_सूची "/" AR6003_HW_2_1_1_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6003_HW_2_1_1_FW_सूची "/" AR6003_HW_2_1_1_PATCH_खाता);
MODULE_FIRMWARE(AR6003_HW_2_1_1_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6003_HW_2_1_1_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_0_FW_सूची "/" AR6004_HW_1_0_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_0_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_FW_सूची "/" AR6004_HW_1_1_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_1_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_FW_सूची "/" AR6004_HW_1_2_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_2_DEFAULT_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_FW_सूची "/" AR6004_HW_1_3_FIRMWARE_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_BOARD_DATA_खाता);
MODULE_FIRMWARE(AR6004_HW_1_3_DEFAULT_BOARD_DATA_खाता);
