<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */
/* ****************** SDIO CARD Interface Functions **************************/

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <net/cfg80211.h>

#समावेश <defs.h>
#समावेश <brcm_hw_ids.h>
#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <chipcommon.h>
#समावेश <soc.h>
#समावेश "chip.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "sdio.h"
#समावेश "core.h"
#समावेश "common.h"

#घोषणा SDIOH_API_ACCESS_RETRY_LIMIT	2

#घोषणा DMA_ALIGN_MASK	0x03

#घोषणा SDIO_FUNC1_BLOCKSIZE		64
#घोषणा SDIO_FUNC2_BLOCKSIZE		512
#घोषणा SDIO_4373_FUNC2_BLOCKSIZE	256
#घोषणा SDIO_435X_FUNC2_BLOCKSIZE	256
#घोषणा SDIO_4329_FUNC2_BLOCKSIZE	128
/* Maximum milliseconds to रुको क्रम F2 to come up */
#घोषणा SDIO_WAIT_F2RDY	3000

#घोषणा BRCMF_DEFAULT_RXGLOM_SIZE	32  /* max rx frames in glom chain */

काष्ठा brcmf_sdiod_मुक्तzer अणु
	atomic_t मुक्तzing;
	atomic_t thपढ़ो_count;
	u32 frozen_count;
	रुको_queue_head_t thपढ़ो_मुक्तze;
	काष्ठा completion resumed;
पूर्ण;

अटल irqवापस_t brcmf_sdiod_oob_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev_id);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;

	brcmf_dbg(INTR, "OOB intr triggered\n");

	/* out-of-band पूर्णांकerrupt is level-triggered which won't
	 * be cleared until dpc
	 */
	अगर (sdiodev->irq_en) अणु
		disable_irq_nosync(irq);
		sdiodev->irq_en = false;
	पूर्ण

	brcmf_sdio_isr(sdiodev->bus, true);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम brcmf_sdiod_ib_irqhandler(काष्ठा sdio_func *func)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(&func->dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;

	brcmf_dbg(INTR, "IB intr triggered\n");

	brcmf_sdio_isr(sdiodev->bus, false);
पूर्ण

/* dummy handler क्रम SDIO function 2 पूर्णांकerrupt */
अटल व्योम brcmf_sdiod_dummy_irqhandler(काष्ठा sdio_func *func)
अणु
पूर्ण

पूर्णांक brcmf_sdiod_पूर्णांकr_रेजिस्टर(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	काष्ठा brcmfmac_sdio_pd *pdata;
	पूर्णांक ret = 0;
	u8 data;
	u32 addr, gpiocontrol;

	pdata = &sdiodev->settings->bus.sdio;
	अगर (pdata->oob_irq_supported) अणु
		brcmf_dbg(SDIO, "Enter, register OOB IRQ %d\n",
			  pdata->oob_irq_nr);
		spin_lock_init(&sdiodev->irq_en_lock);
		sdiodev->irq_en = true;

		ret = request_irq(pdata->oob_irq_nr, brcmf_sdiod_oob_irqhandler,
				  pdata->oob_irq_flags, "brcmf_oob_intr",
				  &sdiodev->func1->dev);
		अगर (ret != 0) अणु
			brcmf_err("request_irq failed %d\n", ret);
			वापस ret;
		पूर्ण
		sdiodev->oob_irq_requested = true;

		ret = enable_irq_wake(pdata->oob_irq_nr);
		अगर (ret != 0) अणु
			brcmf_err("enable_irq_wake failed %d\n", ret);
			वापस ret;
		पूर्ण
		disable_irq_wake(pdata->oob_irq_nr);

		sdio_claim_host(sdiodev->func1);

		अगर (sdiodev->bus_अगर->chip == BRCM_CC_43362_CHIP_ID) अणु
			/* assign GPIO to SDIO core */
			addr = CORE_CC_REG(SI_ENUM_BASE, gpiocontrol);
			gpiocontrol = brcmf_sdiod_पढ़ोl(sdiodev, addr, &ret);
			gpiocontrol |= 0x2;
			brcmf_sdiod_ग_लिखोl(sdiodev, addr, gpiocontrol, &ret);

			brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_GPIO_SELECT,
					   0xf, &ret);
			brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_GPIO_OUT, 0, &ret);
			brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_GPIO_EN, 0x2, &ret);
		पूर्ण

		/* must configure SDIO_CCCR_IENx to enable irq */
		data = brcmf_sdiod_func0_rb(sdiodev, SDIO_CCCR_IENx, &ret);
		data |= SDIO_CCCR_IEN_FUNC1 | SDIO_CCCR_IEN_FUNC2 |
			SDIO_CCCR_IEN_FUNC0;
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_IENx, data, &ret);

		/* redirect, configure and enable io क्रम पूर्णांकerrupt संकेत */
		data = SDIO_CCCR_BRCM_SEPINT_MASK | SDIO_CCCR_BRCM_SEPINT_OE;
		अगर (pdata->oob_irq_flags & IRQF_TRIGGER_HIGH)
			data |= SDIO_CCCR_BRCM_SEPINT_ACT_HI;
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_BRCM_SEPINT,
				     data, &ret);
		sdio_release_host(sdiodev->func1);
	पूर्ण अन्यथा अणु
		brcmf_dbg(SDIO, "Entering\n");
		sdio_claim_host(sdiodev->func1);
		sdio_claim_irq(sdiodev->func1, brcmf_sdiod_ib_irqhandler);
		sdio_claim_irq(sdiodev->func2, brcmf_sdiod_dummy_irqhandler);
		sdio_release_host(sdiodev->func1);
		sdiodev->sd_irq_requested = true;
	पूर्ण

	वापस 0;
पूर्ण

व्योम brcmf_sdiod_पूर्णांकr_unरेजिस्टर(काष्ठा brcmf_sdio_dev *sdiodev)
अणु

	brcmf_dbg(SDIO, "Entering oob=%d sd=%d\n",
		  sdiodev->oob_irq_requested,
		  sdiodev->sd_irq_requested);

	अगर (sdiodev->oob_irq_requested) अणु
		काष्ठा brcmfmac_sdio_pd *pdata;

		pdata = &sdiodev->settings->bus.sdio;
		sdio_claim_host(sdiodev->func1);
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_BRCM_SEPINT, 0, शून्य);
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_IENx, 0, शून्य);
		sdio_release_host(sdiodev->func1);

		sdiodev->oob_irq_requested = false;
		मुक्त_irq(pdata->oob_irq_nr, &sdiodev->func1->dev);
		sdiodev->irq_en = false;
		sdiodev->oob_irq_requested = false;
	पूर्ण

	अगर (sdiodev->sd_irq_requested) अणु
		sdio_claim_host(sdiodev->func1);
		sdio_release_irq(sdiodev->func2);
		sdio_release_irq(sdiodev->func1);
		sdio_release_host(sdiodev->func1);
		sdiodev->sd_irq_requested = false;
	पूर्ण
पूर्ण

व्योम brcmf_sdiod_change_state(काष्ठा brcmf_sdio_dev *sdiodev,
			      क्रमागत brcmf_sdiod_state state)
अणु
	अगर (sdiodev->state == BRCMF_SDIOD_NOMEDIUM ||
	    state == sdiodev->state)
		वापस;

	brcmf_dbg(TRACE, "%d -> %d\n", sdiodev->state, state);
	चयन (sdiodev->state) अणु
	हाल BRCMF_SDIOD_DATA:
		/* any other state means bus पूर्णांकerface is करोwn */
		brcmf_bus_change_state(sdiodev->bus_अगर, BRCMF_BUS_DOWN);
		अवरोध;
	हाल BRCMF_SDIOD_DOWN:
		/* transition from DOWN to DATA means bus पूर्णांकerface is up */
		अगर (state == BRCMF_SDIOD_DATA)
			brcmf_bus_change_state(sdiodev->bus_अगर, BRCMF_BUS_UP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	sdiodev->state = state;
पूर्ण

अटल पूर्णांक brcmf_sdiod_set_backplane_winकरोw(काष्ठा brcmf_sdio_dev *sdiodev,
					    u32 addr)
अणु
	u32 v, bar0 = addr & SBSDIO_SBWINDOW_MASK;
	पूर्णांक err = 0, i;

	अगर (bar0 == sdiodev->sbwad)
		वापस 0;

	v = bar0 >> 8;

	क्रम (i = 0 ; i < 3 && !err ; i++, v >>= 8)
		brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_SBADDRLOW + i,
				   v & 0xff, &err);

	अगर (!err)
		sdiodev->sbwad = bar0;

	वापस err;
पूर्ण

u32 brcmf_sdiod_पढ़ोl(काष्ठा brcmf_sdio_dev *sdiodev, u32 addr, पूर्णांक *ret)
अणु
	u32 data = 0;
	पूर्णांक retval;

	retval = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (retval)
		जाओ out;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	data = sdio_पढ़ोl(sdiodev->func1, addr, &retval);

out:
	अगर (ret)
		*ret = retval;

	वापस data;
पूर्ण

व्योम brcmf_sdiod_ग_लिखोl(काष्ठा brcmf_sdio_dev *sdiodev, u32 addr,
			u32 data, पूर्णांक *ret)
अणु
	पूर्णांक retval;

	retval = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (retval)
		जाओ out;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	sdio_ग_लिखोl(sdiodev->func1, data, addr, &retval);

out:
	अगर (ret)
		*ret = retval;
पूर्ण

अटल पूर्णांक brcmf_sdiod_skbuff_पढ़ो(काष्ठा brcmf_sdio_dev *sdiodev,
				   काष्ठा sdio_func *func, u32 addr,
				   काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक req_sz;
	पूर्णांक err;

	/* Single skb use the standard mmc पूर्णांकerface */
	req_sz = skb->len + 3;
	req_sz &= (uपूर्णांक)~3;

	चयन (func->num) अणु
	हाल 1:
		err = sdio_स_नकल_fromio(func, ((u8 *)(skb->data)), addr,
					 req_sz);
		अवरोध;
	हाल 2:
		err = sdio_पढ़ोsb(func, ((u8 *)(skb->data)), addr, req_sz);
		अवरोध;
	शेष:
		/* bail out as things are really fishy here */
		WARN(1, "invalid sdio function number: %d\n", func->num);
		err = -ENOMEDIUM;
	पूर्ण

	अगर (err == -ENOMEDIUM)
		brcmf_sdiod_change_state(sdiodev, BRCMF_SDIOD_NOMEDIUM);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_sdiod_skbuff_ग_लिखो(काष्ठा brcmf_sdio_dev *sdiodev,
				    काष्ठा sdio_func *func, u32 addr,
				    काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक req_sz;
	पूर्णांक err;

	/* Single skb use the standard mmc पूर्णांकerface */
	req_sz = skb->len + 3;
	req_sz &= (uपूर्णांक)~3;

	err = sdio_स_नकल_toio(func, addr, ((u8 *)(skb->data)), req_sz);

	अगर (err == -ENOMEDIUM)
		brcmf_sdiod_change_state(sdiodev, BRCMF_SDIOD_NOMEDIUM);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_submit_one(काष्ठा mmc_data *md, काष्ठा mmc_request *mr,
			  काष्ठा mmc_command *mc, पूर्णांक sg_cnt, पूर्णांक req_sz,
			  पूर्णांक func_blk_sz, u32 *addr,
			  काष्ठा brcmf_sdio_dev *sdiodev,
			  काष्ठा sdio_func *func, पूर्णांक ग_लिखो)
अणु
	पूर्णांक ret;

	md->sg_len = sg_cnt;
	md->blocks = req_sz / func_blk_sz;
	mc->arg |= (*addr & 0x1FFFF) << 9;	/* address */
	mc->arg |= md->blocks & 0x1FF;	/* block count */
	/* incrementing addr क्रम function 1 */
	अगर (func->num == 1)
		*addr += req_sz;

	mmc_set_data_समयout(md, func->card);
	mmc_रुको_क्रम_req(func->card->host, mr);

	ret = mc->error ? mc->error : md->error;
	अगर (ret == -ENOMEDIUM) अणु
		brcmf_sdiod_change_state(sdiodev, BRCMF_SDIOD_NOMEDIUM);
	पूर्ण अन्यथा अगर (ret != 0) अणु
		brcmf_err("CMD53 sg block %s failed %d\n",
			  ग_लिखो ? "write" : "read", ret);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * brcmf_sdiod_sglist_rw - SDIO पूर्णांकerface function क्रम block data access
 * @sdiodev: brcmfmac sdio device
 * @func: SDIO function
 * @ग_लिखो: direction flag
 * @addr: करोngle memory address as source/destination
 * @pktlist: skb buffer head poपूर्णांकer
 *
 * This function takes the respbonsibility as the पूर्णांकerface function to MMC
 * stack क्रम block data access. It assumes that the skb passed करोwn by the
 * caller has alपढ़ोy been padded and aligned.
 */
अटल पूर्णांक brcmf_sdiod_sglist_rw(काष्ठा brcmf_sdio_dev *sdiodev,
				 काष्ठा sdio_func *func,
				 bool ग_लिखो, u32 addr,
				 काष्ठा sk_buff_head *pktlist)
अणु
	अचिन्हित पूर्णांक req_sz, func_blk_sz, sg_cnt, sg_data_sz, pkt_offset;
	अचिन्हित पूर्णांक max_req_sz, src_offset, dst_offset;
	अचिन्हित अक्षर *pkt_data, *orig_data, *dst_data;
	काष्ठा sk_buff_head local_list, *target_list;
	काष्ठा sk_buff *pkt_next = शून्य, *src;
	अचिन्हित लघु max_seg_cnt;
	काष्ठा mmc_request mmc_req;
	काष्ठा mmc_command mmc_cmd;
	काष्ठा mmc_data mmc_dat;
	काष्ठा scatterlist *sgl;
	पूर्णांक ret = 0;

	अगर (!pktlist->qlen)
		वापस -EINVAL;

	target_list = pktlist;
	/* क्रम host with broken sg support, prepare a page aligned list */
	__skb_queue_head_init(&local_list);
	अगर (!ग_लिखो && sdiodev->settings->bus.sdio.broken_sg_support) अणु
		req_sz = 0;
		skb_queue_walk(pktlist, pkt_next)
			req_sz += pkt_next->len;
		req_sz = ALIGN(req_sz, func->cur_blksize);
		जबतक (req_sz > PAGE_SIZE) अणु
			pkt_next = brcmu_pkt_buf_get_skb(PAGE_SIZE);
			अगर (pkt_next == शून्य) अणु
				ret = -ENOMEM;
				जाओ निकास;
			पूर्ण
			__skb_queue_tail(&local_list, pkt_next);
			req_sz -= PAGE_SIZE;
		पूर्ण
		pkt_next = brcmu_pkt_buf_get_skb(req_sz);
		अगर (pkt_next == शून्य) अणु
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण
		__skb_queue_tail(&local_list, pkt_next);
		target_list = &local_list;
	पूर्ण

	func_blk_sz = func->cur_blksize;
	max_req_sz = sdiodev->max_request_size;
	max_seg_cnt = min_t(अचिन्हित लघु, sdiodev->max_segment_count,
			    target_list->qlen);

	स_रखो(&mmc_req, 0, माप(काष्ठा mmc_request));
	स_रखो(&mmc_cmd, 0, माप(काष्ठा mmc_command));
	स_रखो(&mmc_dat, 0, माप(काष्ठा mmc_data));

	mmc_dat.sg = sdiodev->sgtable.sgl;
	mmc_dat.blksz = func_blk_sz;
	mmc_dat.flags = ग_लिखो ? MMC_DATA_WRITE : MMC_DATA_READ;
	mmc_cmd.opcode = SD_IO_RW_EXTENDED;
	mmc_cmd.arg = ग_लिखो ? 1<<31 : 0;	/* ग_लिखो flag  */
	mmc_cmd.arg |= (func->num & 0x7) << 28;	/* SDIO func num */
	mmc_cmd.arg |= 1 << 27;			/* block mode */
	/* क्रम function 1 the addr will be incremented */
	mmc_cmd.arg |= (func->num == 1) ? 1 << 26 : 0;
	mmc_cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;
	mmc_req.cmd = &mmc_cmd;
	mmc_req.data = &mmc_dat;

	req_sz = 0;
	sg_cnt = 0;
	sgl = sdiodev->sgtable.sgl;
	skb_queue_walk(target_list, pkt_next) अणु
		pkt_offset = 0;
		जबतक (pkt_offset < pkt_next->len) अणु
			pkt_data = pkt_next->data + pkt_offset;
			sg_data_sz = pkt_next->len - pkt_offset;
			अगर (sg_data_sz > sdiodev->max_segment_size)
				sg_data_sz = sdiodev->max_segment_size;
			अगर (sg_data_sz > max_req_sz - req_sz)
				sg_data_sz = max_req_sz - req_sz;

			sg_set_buf(sgl, pkt_data, sg_data_sz);
			sg_cnt++;

			sgl = sg_next(sgl);
			req_sz += sg_data_sz;
			pkt_offset += sg_data_sz;
			अगर (req_sz >= max_req_sz || sg_cnt >= max_seg_cnt) अणु
				ret = mmc_submit_one(&mmc_dat, &mmc_req, &mmc_cmd,
						     sg_cnt, req_sz, func_blk_sz,
						     &addr, sdiodev, func, ग_लिखो);
				अगर (ret)
					जाओ निकास_queue_walk;
				req_sz = 0;
				sg_cnt = 0;
				sgl = sdiodev->sgtable.sgl;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (sg_cnt)
		ret = mmc_submit_one(&mmc_dat, &mmc_req, &mmc_cmd,
				     sg_cnt, req_sz, func_blk_sz,
				     &addr, sdiodev, func, ग_लिखो);
निकास_queue_walk:
	अगर (!ग_लिखो && sdiodev->settings->bus.sdio.broken_sg_support) अणु
		src = __skb_peek(&local_list);
		src_offset = 0;
		skb_queue_walk(pktlist, pkt_next) अणु
			dst_offset = 0;

			/* This is safe because we must have enough SKB data
			 * in the local list to cover everything in pktlist.
			 */
			जबतक (1) अणु
				req_sz = pkt_next->len - dst_offset;
				अगर (req_sz > src->len - src_offset)
					req_sz = src->len - src_offset;

				orig_data = src->data + src_offset;
				dst_data = pkt_next->data + dst_offset;
				स_नकल(dst_data, orig_data, req_sz);

				src_offset += req_sz;
				अगर (src_offset == src->len) अणु
					src_offset = 0;
					src = skb_peek_next(src, &local_list);
				पूर्ण
				dst_offset += req_sz;
				अगर (dst_offset == pkt_next->len)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	sg_init_table(sdiodev->sgtable.sgl, sdiodev->sgtable.orig_nents);
	जबतक ((pkt_next = __skb_dequeue(&local_list)) != शून्य)
		brcmu_pkt_buf_मुक्त_skb(pkt_next);

	वापस ret;
पूर्ण

पूर्णांक brcmf_sdiod_recv_buf(काष्ठा brcmf_sdio_dev *sdiodev, u8 *buf, uपूर्णांक nbytes)
अणु
	काष्ठा sk_buff *mypkt;
	पूर्णांक err;

	mypkt = brcmu_pkt_buf_get_skb(nbytes);
	अगर (!mypkt) अणु
		brcmf_err("brcmu_pkt_buf_get_skb failed: len %d\n",
			  nbytes);
		वापस -EIO;
	पूर्ण

	err = brcmf_sdiod_recv_pkt(sdiodev, mypkt);
	अगर (!err)
		स_नकल(buf, mypkt->data, nbytes);

	brcmu_pkt_buf_मुक्त_skb(mypkt);
	वापस err;
पूर्ण

पूर्णांक brcmf_sdiod_recv_pkt(काष्ठा brcmf_sdio_dev *sdiodev, काष्ठा sk_buff *pkt)
अणु
	u32 addr = sdiodev->cc_core->base;
	पूर्णांक err = 0;

	brcmf_dbg(SDIO, "addr = 0x%x, size = %d\n", addr, pkt->len);

	err = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (err)
		जाओ करोne;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	err = brcmf_sdiod_skbuff_पढ़ो(sdiodev, sdiodev->func2, addr, pkt);

करोne:
	वापस err;
पूर्ण

पूर्णांक brcmf_sdiod_recv_chain(काष्ठा brcmf_sdio_dev *sdiodev,
			   काष्ठा sk_buff_head *pktq, uपूर्णांक totlen)
अणु
	काष्ठा sk_buff *glom_skb = शून्य;
	काष्ठा sk_buff *skb;
	u32 addr = sdiodev->cc_core->base;
	पूर्णांक err = 0;

	brcmf_dbg(SDIO, "addr = 0x%x, size = %d\n",
		  addr, pktq->qlen);

	err = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (err)
		जाओ करोne;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	अगर (pktq->qlen == 1)
		err = brcmf_sdiod_skbuff_पढ़ो(sdiodev, sdiodev->func2, addr,
					      __skb_peek(pktq));
	अन्यथा अगर (!sdiodev->sg_support) अणु
		glom_skb = brcmu_pkt_buf_get_skb(totlen);
		अगर (!glom_skb)
			वापस -ENOMEM;
		err = brcmf_sdiod_skbuff_पढ़ो(sdiodev, sdiodev->func2, addr,
					      glom_skb);
		अगर (err)
			जाओ करोne;

		skb_queue_walk(pktq, skb) अणु
			स_नकल(skb->data, glom_skb->data, skb->len);
			skb_pull(glom_skb, skb->len);
		पूर्ण
	पूर्ण अन्यथा
		err = brcmf_sdiod_sglist_rw(sdiodev, sdiodev->func2, false,
					    addr, pktq);

करोne:
	brcmu_pkt_buf_मुक्त_skb(glom_skb);
	वापस err;
पूर्ण

पूर्णांक brcmf_sdiod_send_buf(काष्ठा brcmf_sdio_dev *sdiodev, u8 *buf, uपूर्णांक nbytes)
अणु
	काष्ठा sk_buff *mypkt;
	u32 addr = sdiodev->cc_core->base;
	पूर्णांक err;

	mypkt = brcmu_pkt_buf_get_skb(nbytes);

	अगर (!mypkt) अणु
		brcmf_err("brcmu_pkt_buf_get_skb failed: len %d\n",
			  nbytes);
		वापस -EIO;
	पूर्ण

	स_नकल(mypkt->data, buf, nbytes);

	err = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (err)
		जाओ out;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	err = brcmf_sdiod_skbuff_ग_लिखो(sdiodev, sdiodev->func2, addr, mypkt);
out:
	brcmu_pkt_buf_मुक्त_skb(mypkt);

	वापस err;
पूर्ण

पूर्णांक brcmf_sdiod_send_pkt(काष्ठा brcmf_sdio_dev *sdiodev,
			 काष्ठा sk_buff_head *pktq)
अणु
	काष्ठा sk_buff *skb;
	u32 addr = sdiodev->cc_core->base;
	पूर्णांक err;

	brcmf_dbg(SDIO, "addr = 0x%x, size = %d\n", addr, pktq->qlen);

	err = brcmf_sdiod_set_backplane_winकरोw(sdiodev, addr);
	अगर (err)
		वापस err;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	अगर (pktq->qlen == 1 || !sdiodev->sg_support) अणु
		skb_queue_walk(pktq, skb) अणु
			err = brcmf_sdiod_skbuff_ग_लिखो(sdiodev, sdiodev->func2,
						       addr, skb);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = brcmf_sdiod_sglist_rw(sdiodev, sdiodev->func2, true,
					    addr, pktq);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक
brcmf_sdiod_ramrw(काष्ठा brcmf_sdio_dev *sdiodev, bool ग_लिखो, u32 address,
		  u8 *data, uपूर्णांक size)
अणु
	पूर्णांक err = 0;
	काष्ठा sk_buff *pkt;
	u32 sdaddr;
	uपूर्णांक dsize;

	dsize = min_t(uपूर्णांक, SBSDIO_SB_OFT_ADDR_LIMIT, size);
	pkt = dev_alloc_skb(dsize);
	अगर (!pkt) अणु
		brcmf_err("dev_alloc_skb failed: len %d\n", dsize);
		वापस -EIO;
	पूर्ण
	pkt->priority = 0;

	/* Determine initial transfer parameters */
	sdaddr = address & SBSDIO_SB_OFT_ADDR_MASK;
	अगर ((sdaddr + size) & SBSDIO_SBWINDOW_MASK)
		dsize = (SBSDIO_SB_OFT_ADDR_LIMIT - sdaddr);
	अन्यथा
		dsize = size;

	sdio_claim_host(sdiodev->func1);

	/* Do the transfer(s) */
	जबतक (size) अणु
		/* Set the backplane winकरोw to include the start address */
		err = brcmf_sdiod_set_backplane_winकरोw(sdiodev, address);
		अगर (err)
			अवरोध;

		brcmf_dbg(SDIO, "%s %d bytes at offset 0x%08x in window 0x%08x\n",
			  ग_लिखो ? "write" : "read", dsize,
			  sdaddr, address & SBSDIO_SBWINDOW_MASK);

		sdaddr &= SBSDIO_SB_OFT_ADDR_MASK;
		sdaddr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

		skb_put(pkt, dsize);

		अगर (ग_लिखो) अणु
			स_नकल(pkt->data, data, dsize);
			err = brcmf_sdiod_skbuff_ग_लिखो(sdiodev, sdiodev->func1,
						       sdaddr, pkt);
		पूर्ण अन्यथा अणु
			err = brcmf_sdiod_skbuff_पढ़ो(sdiodev, sdiodev->func1,
						      sdaddr, pkt);
		पूर्ण

		अगर (err) अणु
			brcmf_err("membytes transfer failed\n");
			अवरोध;
		पूर्ण
		अगर (!ग_लिखो)
			स_नकल(data, pkt->data, dsize);
		skb_trim(pkt, 0);

		/* Adjust क्रम next transfer (अगर any) */
		size -= dsize;
		अगर (size) अणु
			data += dsize;
			address += dsize;
			sdaddr = 0;
			dsize = min_t(uपूर्णांक, SBSDIO_SB_OFT_ADDR_LIMIT, size);
		पूर्ण
	पूर्ण

	dev_kमुक्त_skb(pkt);

	sdio_release_host(sdiodev->func1);

	वापस err;
पूर्ण

पूर्णांक brcmf_sdiod_पात(काष्ठा brcmf_sdio_dev *sdiodev, काष्ठा sdio_func *func)
अणु
	brcmf_dbg(SDIO, "Enter\n");

	/* Issue पात cmd52 command through F0 */
	brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_ABORT, func->num, शून्य);

	brcmf_dbg(SDIO, "Exit\n");
	वापस 0;
पूर्ण

व्योम brcmf_sdiod_sgtable_alloc(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	काष्ठा sdio_func *func;
	काष्ठा mmc_host *host;
	uपूर्णांक max_blocks;
	uपूर्णांक nents;
	पूर्णांक err;

	func = sdiodev->func2;
	host = func->card->host;
	sdiodev->sg_support = host->max_segs > 1;
	max_blocks = min_t(uपूर्णांक, host->max_blk_count, 511u);
	sdiodev->max_request_size = min_t(uपूर्णांक, host->max_req_size,
					  max_blocks * func->cur_blksize);
	sdiodev->max_segment_count = min_t(uपूर्णांक, host->max_segs,
					   SG_MAX_SINGLE_ALLOC);
	sdiodev->max_segment_size = host->max_seg_size;

	अगर (!sdiodev->sg_support)
		वापस;

	nents = max_t(uपूर्णांक, BRCMF_DEFAULT_RXGLOM_SIZE,
		      sdiodev->settings->bus.sdio.txglomsz);
	nents += (nents >> 4) + 1;

	WARN_ON(nents > sdiodev->max_segment_count);

	brcmf_dbg(TRACE, "nents=%d\n", nents);
	err = sg_alloc_table(&sdiodev->sgtable, nents, GFP_KERNEL);
	अगर (err < 0) अणु
		brcmf_err("allocation failed: disable scatter-gather");
		sdiodev->sg_support = false;
	पूर्ण

	sdiodev->txglomsz = sdiodev->settings->bus.sdio.txglomsz;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmf_sdiod_मुक्तzer_attach(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	sdiodev->मुक्तzer = kzalloc(माप(*sdiodev->मुक्तzer), GFP_KERNEL);
	अगर (!sdiodev->मुक्तzer)
		वापस -ENOMEM;
	atomic_set(&sdiodev->मुक्तzer->thपढ़ो_count, 0);
	atomic_set(&sdiodev->मुक्तzer->मुक्तzing, 0);
	init_रुकोqueue_head(&sdiodev->मुक्तzer->thपढ़ो_मुक्तze);
	init_completion(&sdiodev->मुक्तzer->resumed);
	वापस 0;
पूर्ण

अटल व्योम brcmf_sdiod_मुक्तzer_detach(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	अगर (sdiodev->मुक्तzer) अणु
		WARN_ON(atomic_पढ़ो(&sdiodev->मुक्तzer->मुक्तzing));
		kमुक्त(sdiodev->मुक्तzer);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_sdiod_मुक्तzer_on(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	atomic_t *expect = &sdiodev->मुक्तzer->thपढ़ो_count;
	पूर्णांक res = 0;

	sdiodev->मुक्तzer->frozen_count = 0;
	reinit_completion(&sdiodev->मुक्तzer->resumed);
	atomic_set(&sdiodev->मुक्तzer->मुक्तzing, 1);
	brcmf_sdio_trigger_dpc(sdiodev->bus);
	रुको_event(sdiodev->मुक्तzer->thपढ़ो_मुक्तze,
		   atomic_पढ़ो(expect) == sdiodev->मुक्तzer->frozen_count);
	sdio_claim_host(sdiodev->func1);
	res = brcmf_sdio_sleep(sdiodev->bus, true);
	sdio_release_host(sdiodev->func1);
	वापस res;
पूर्ण

अटल व्योम brcmf_sdiod_मुक्तzer_off(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	sdio_claim_host(sdiodev->func1);
	brcmf_sdio_sleep(sdiodev->bus, false);
	sdio_release_host(sdiodev->func1);
	atomic_set(&sdiodev->मुक्तzer->मुक्तzing, 0);
	complete_all(&sdiodev->मुक्तzer->resumed);
पूर्ण

bool brcmf_sdiod_मुक्तzing(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	वापस atomic_पढ़ो(&sdiodev->मुक्तzer->मुक्तzing);
पूर्ण

व्योम brcmf_sdiod_try_मुक्तze(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	अगर (!brcmf_sdiod_मुक्तzing(sdiodev))
		वापस;
	sdiodev->मुक्तzer->frozen_count++;
	wake_up(&sdiodev->मुक्तzer->thपढ़ो_मुक्तze);
	रुको_क्रम_completion(&sdiodev->मुक्तzer->resumed);
पूर्ण

व्योम brcmf_sdiod_मुक्तzer_count(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	atomic_inc(&sdiodev->मुक्तzer->thपढ़ो_count);
पूर्ण

व्योम brcmf_sdiod_मुक्तzer_uncount(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	atomic_dec(&sdiodev->मुक्तzer->thपढ़ो_count);
पूर्ण
#अन्यथा
अटल पूर्णांक brcmf_sdiod_मुक्तzer_attach(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	वापस 0;
पूर्ण

अटल व्योम brcmf_sdiod_मुक्तzer_detach(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

पूर्णांक brcmf_sdiod_हटाओ(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	sdiodev->state = BRCMF_SDIOD_DOWN;
	अगर (sdiodev->bus) अणु
		brcmf_sdio_हटाओ(sdiodev->bus);
		sdiodev->bus = शून्य;
	पूर्ण

	brcmf_sdiod_मुक्तzer_detach(sdiodev);

	/* Disable Function 2 */
	sdio_claim_host(sdiodev->func2);
	sdio_disable_func(sdiodev->func2);
	sdio_release_host(sdiodev->func2);

	/* Disable Function 1 */
	sdio_claim_host(sdiodev->func1);
	sdio_disable_func(sdiodev->func1);
	sdio_release_host(sdiodev->func1);

	sg_मुक्त_table(&sdiodev->sgtable);
	sdiodev->sbwad = 0;

	pm_runसमय_allow(sdiodev->func1->card->host->parent);
	वापस 0;
पूर्ण

अटल व्योम brcmf_sdiod_host_fixup(काष्ठा mmc_host *host)
अणु
	/* runसमय-pm घातers off the device */
	pm_runसमय_क्रमbid(host->parent);
	/* aव्योम removal detection upon resume */
	host->caps |= MMC_CAP_NONREMOVABLE;
पूर्ण

पूर्णांक brcmf_sdiod_probe(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक f2_blksz = SDIO_FUNC2_BLOCKSIZE;

	sdio_claim_host(sdiodev->func1);

	ret = sdio_set_block_size(sdiodev->func1, SDIO_FUNC1_BLOCKSIZE);
	अगर (ret) अणु
		brcmf_err("Failed to set F1 blocksize\n");
		sdio_release_host(sdiodev->func1);
		जाओ out;
	पूर्ण
	चयन (sdiodev->func2->device) अणु
	हाल SDIO_DEVICE_ID_BROADCOM_CYPRESS_4373:
		f2_blksz = SDIO_4373_FUNC2_BLOCKSIZE;
		अवरोध;
	हाल SDIO_DEVICE_ID_BROADCOM_4359:
	हाल SDIO_DEVICE_ID_BROADCOM_4354:
	हाल SDIO_DEVICE_ID_BROADCOM_4356:
		f2_blksz = SDIO_435X_FUNC2_BLOCKSIZE;
		अवरोध;
	हाल SDIO_DEVICE_ID_BROADCOM_4329:
		f2_blksz = SDIO_4329_FUNC2_BLOCKSIZE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = sdio_set_block_size(sdiodev->func2, f2_blksz);
	अगर (ret) अणु
		brcmf_err("Failed to set F2 blocksize\n");
		sdio_release_host(sdiodev->func1);
		जाओ out;
	पूर्ण अन्यथा अणु
		brcmf_dbg(SDIO, "set F2 blocksize to %d\n", f2_blksz);
	पूर्ण

	/* increase F2 समयout */
	sdiodev->func2->enable_समयout = SDIO_WAIT_F2RDY;

	/* Enable Function 1 */
	ret = sdio_enable_func(sdiodev->func1);
	sdio_release_host(sdiodev->func1);
	अगर (ret) अणु
		brcmf_err("Failed to enable F1: err=%d\n", ret);
		जाओ out;
	पूर्ण

	ret = brcmf_sdiod_मुक्तzer_attach(sdiodev);
	अगर (ret)
		जाओ out;

	/* try to attach to the target device */
	sdiodev->bus = brcmf_sdio_probe(sdiodev);
	अगर (!sdiodev->bus) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	brcmf_sdiod_host_fixup(sdiodev->func2->card->host);
out:
	अगर (ret)
		brcmf_sdiod_हटाओ(sdiodev);

	वापस ret;
पूर्ण

#घोषणा BRCMF_SDIO_DEVICE(dev_id)	\
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_BROADCOM, dev_id)पूर्ण

/* devices we support, null terminated */
अटल स्थिर काष्ठा sdio_device_id brcmf_sdmmc_ids[] = अणु
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43143),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43241),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4329),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4330),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4334),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43340),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43341),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43362),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43364),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4335_4339),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4339),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43430),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4345),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_43455),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4354),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4356),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_4359),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_CYPRESS_4373),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_CYPRESS_43012),
	BRCMF_SDIO_DEVICE(SDIO_DEVICE_ID_BROADCOM_CYPRESS_89359),
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(sdio, brcmf_sdmmc_ids);


अटल व्योम brcmf_sdiod_acpi_set_घातer_manageable(काष्ठा device *dev,
						  पूर्णांक val)
अणु
#अगर IS_ENABLED(CONFIG_ACPI)
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	अगर (adev)
		adev->flags.घातer_manageable = 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक brcmf_ops_sdio_probe(काष्ठा sdio_func *func,
				स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा brcmf_sdio_dev *sdiodev;
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा device *dev;

	brcmf_dbg(SDIO, "Enter\n");
	brcmf_dbg(SDIO, "Class=%x\n", func->class);
	brcmf_dbg(SDIO, "sdio vendor ID: 0x%04x\n", func->venकरोr);
	brcmf_dbg(SDIO, "sdio device ID: 0x%04x\n", func->device);
	brcmf_dbg(SDIO, "Function#: %d\n", func->num);

	dev = &func->dev;

	/* Set MMC_QUIRK_LENIENT_FN0 क्रम this card */
	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	/* prohibit ACPI घातer management क्रम this device */
	brcmf_sdiod_acpi_set_घातer_manageable(dev, 0);

	/* Consume func num 1 but करोnt करो anything with it. */
	अगर (func->num == 1)
		वापस 0;

	/* Ignore anything but func 2 */
	अगर (func->num != 2)
		वापस -ENODEV;

	bus_अगर = kzalloc(माप(काष्ठा brcmf_bus), GFP_KERNEL);
	अगर (!bus_अगर)
		वापस -ENOMEM;
	sdiodev = kzalloc(माप(काष्ठा brcmf_sdio_dev), GFP_KERNEL);
	अगर (!sdiodev) अणु
		kमुक्त(bus_अगर);
		वापस -ENOMEM;
	पूर्ण

	/* store refs to functions used. mmc_card करोes
	 * not hold the F0 function poपूर्णांकer.
	 */
	sdiodev->func1 = func->card->sdio_func[0];
	sdiodev->func2 = func;

	sdiodev->bus_अगर = bus_अगर;
	bus_अगर->bus_priv.sdio = sdiodev;
	bus_अगर->proto_type = BRCMF_PROTO_BCDC;
	dev_set_drvdata(&func->dev, bus_अगर);
	dev_set_drvdata(&sdiodev->func1->dev, bus_अगर);
	sdiodev->dev = &sdiodev->func1->dev;

	brcmf_sdiod_change_state(sdiodev, BRCMF_SDIOD_DOWN);

	brcmf_dbg(SDIO, "F2 found, calling brcmf_sdiod_probe...\n");
	err = brcmf_sdiod_probe(sdiodev);
	अगर (err) अणु
		brcmf_err("F2 error, probe failed %d...\n", err);
		जाओ fail;
	पूर्ण

	brcmf_dbg(SDIO, "F2 init completed...\n");
	वापस 0;

fail:
	dev_set_drvdata(&func->dev, शून्य);
	dev_set_drvdata(&sdiodev->func1->dev, शून्य);
	kमुक्त(sdiodev);
	kमुक्त(bus_अगर);
	वापस err;
पूर्ण

अटल व्योम brcmf_ops_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा brcmf_sdio_dev *sdiodev;

	brcmf_dbg(SDIO, "Enter\n");
	brcmf_dbg(SDIO, "sdio vendor ID: 0x%04x\n", func->venकरोr);
	brcmf_dbg(SDIO, "sdio device ID: 0x%04x\n", func->device);
	brcmf_dbg(SDIO, "Function: %d\n", func->num);

	bus_अगर = dev_get_drvdata(&func->dev);
	अगर (bus_अगर) अणु
		sdiodev = bus_अगर->bus_priv.sdio;

		/* start by unरेजिस्टरing irqs */
		brcmf_sdiod_पूर्णांकr_unरेजिस्टर(sdiodev);

		अगर (func->num != 1)
			वापस;

		/* only proceed with rest of cleanup अगर func 1 */
		brcmf_sdiod_हटाओ(sdiodev);

		dev_set_drvdata(&sdiodev->func1->dev, शून्य);
		dev_set_drvdata(&sdiodev->func2->dev, शून्य);

		kमुक्त(bus_अगर);
		kमुक्त(sdiodev);
	पूर्ण

	brcmf_dbg(SDIO, "Exit\n");
पूर्ण

व्योम brcmf_sdio_wowl_config(काष्ठा device *dev, bool enabled)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;

	brcmf_dbg(SDIO, "Configuring WOWL, enabled=%d\n", enabled);
	sdiodev->wowl_enabled = enabled;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmf_ops_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func;
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा brcmf_sdio_dev *sdiodev;
	mmc_pm_flag_t pm_caps, sdio_flags;
	पूर्णांक ret = 0;

	func = container_of(dev, काष्ठा sdio_func, dev);
	brcmf_dbg(SDIO, "Enter: F%d\n", func->num);
	अगर (func->num != 1)
		वापस 0;


	bus_अगर = dev_get_drvdata(dev);
	sdiodev = bus_अगर->bus_priv.sdio;

	pm_caps = sdio_get_host_pm_caps(func);

	अगर (pm_caps & MMC_PM_KEEP_POWER) अणु
		/* preserve card घातer during suspend */
		brcmf_sdiod_मुक्तzer_on(sdiodev);
		brcmf_sdio_wd_समयr(sdiodev->bus, 0);

		sdio_flags = MMC_PM_KEEP_POWER;
		अगर (sdiodev->wowl_enabled) अणु
			अगर (sdiodev->settings->bus.sdio.oob_irq_supported)
				enable_irq_wake(sdiodev->settings->bus.sdio.oob_irq_nr);
			अन्यथा
				sdio_flags |= MMC_PM_WAKE_SDIO_IRQ;
		पूर्ण

		अगर (sdio_set_host_pm_flags(sdiodev->func1, sdio_flags))
			brcmf_err("Failed to set pm_flags %x\n", sdio_flags);

	पूर्ण अन्यथा अणु
		/* घातer will be cut so हटाओ device, probe again in resume */
		brcmf_sdiod_पूर्णांकr_unरेजिस्टर(sdiodev);
		ret = brcmf_sdiod_हटाओ(sdiodev);
		अगर (ret)
			brcmf_err("Failed to remove device on suspend\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_ops_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा sdio_func *func = container_of(dev, काष्ठा sdio_func, dev);
	mmc_pm_flag_t pm_caps = sdio_get_host_pm_caps(func);
	पूर्णांक ret = 0;

	brcmf_dbg(SDIO, "Enter: F%d\n", func->num);
	अगर (func->num != 2)
		वापस 0;

	अगर (!(pm_caps & MMC_PM_KEEP_POWER)) अणु
		/* bus was घातered off and device हटाओd, probe again */
		ret = brcmf_sdiod_probe(sdiodev);
		अगर (ret)
			brcmf_err("Failed to probe device on resume\n");
	पूर्ण अन्यथा अणु
		अगर (sdiodev->wowl_enabled &&
		    sdiodev->settings->bus.sdio.oob_irq_supported)
			disable_irq_wake(sdiodev->settings->bus.sdio.oob_irq_nr);

		brcmf_sdiod_मुक्तzer_off(sdiodev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops brcmf_sdio_pm_ops = अणु
	.suspend	= brcmf_ops_sdio_suspend,
	.resume		= brcmf_ops_sdio_resume,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_PM_SLEEP */

अटल काष्ठा sdio_driver brcmf_sdmmc_driver = अणु
	.probe = brcmf_ops_sdio_probe,
	.हटाओ = brcmf_ops_sdio_हटाओ,
	.name = KBUILD_MODNAME,
	.id_table = brcmf_sdmmc_ids,
	.drv = अणु
		.owner = THIS_MODULE,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &brcmf_sdio_pm_ops,
#पूर्ण_अगर	/* CONFIG_PM_SLEEP */
		.coredump = brcmf_dev_coredump,
	पूर्ण,
पूर्ण;

पूर्णांक brcmf_sdio_रेजिस्टर(व्योम)
अणु
	वापस sdio_रेजिस्टर_driver(&brcmf_sdmmc_driver);
पूर्ण

व्योम brcmf_sdio_निकास(व्योम)
अणु
	brcmf_dbg(SDIO, "Enter\n");

	sdio_unरेजिस्टर_driver(&brcmf_sdmmc_driver);
पूर्ण

