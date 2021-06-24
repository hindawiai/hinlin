<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bdc_ep.c - BRCM BDC USB3.0 device controller endpoपूर्णांक related functions
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 *
 * Based on drivers under drivers/usb/
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/composite.h>

#समावेश "bdc.h"
#समावेश "bdc_ep.h"
#समावेश "bdc_cmd.h"
#समावेश "bdc_dbg.h"

अटल स्थिर अक्षर * स्थिर ep0_state_string[] =  अणु
	"WAIT_FOR_SETUP",
	"WAIT_FOR_DATA_START",
	"WAIT_FOR_DATA_XMIT",
	"WAIT_FOR_STATUS_START",
	"WAIT_FOR_STATUS_XMIT",
	"STATUS_PENDING"
पूर्ण;

/* Free the bdl during ep disable */
अटल व्योम ep_bd_list_मुक्त(काष्ठा bdc_ep *ep, u32 num_tअसल)
अणु
	काष्ठा bd_list *bd_list = &ep->bd_list;
	काष्ठा bdc *bdc = ep->bdc;
	काष्ठा bd_table *bd_table;
	पूर्णांक index;

	dev_dbg(bdc->dev, "%s ep:%s num_tabs:%d\n",
				 __func__, ep->name, num_tअसल);

	अगर (!bd_list->bd_table_array) अणु
		dev_dbg(bdc->dev, "%s already freed\n", ep->name);
		वापस;
	पूर्ण
	क्रम (index = 0; index < num_tअसल; index++) अणु
		/*
		 * check अगर the bd_table काष्ठा is allocated ?
		 * अगर yes, then check अगर bd memory has been allocated, then
		 * मुक्त the dma_pool and also the bd_table काष्ठा memory
		 */
		bd_table = bd_list->bd_table_array[index];
		dev_dbg(bdc->dev, "bd_table:%p index:%d\n", bd_table, index);
		अगर (!bd_table) अणु
			dev_dbg(bdc->dev, "bd_table not allocated\n");
			जारी;
		पूर्ण
		अगर (!bd_table->start_bd) अणु
			dev_dbg(bdc->dev, "bd dma pool not allocated\n");
			जारी;
		पूर्ण

		dev_dbg(bdc->dev,
				"Free dma pool start_bd:%p dma:%llx\n",
				bd_table->start_bd,
				(अचिन्हित दीर्घ दीर्घ)bd_table->dma);

		dma_pool_मुक्त(bdc->bd_table_pool,
				bd_table->start_bd,
				bd_table->dma);
		/* Free the bd_table काष्ठाure */
		kमुक्त(bd_table);
	पूर्ण
	/* Free the bd table array */
	kमुक्त(ep->bd_list.bd_table_array);
पूर्ण

/*
 * chain the tables, by insteting a chain bd at the end of prev_table, poपूर्णांकing
 * to next_table
 */
अटल अंतरभूत व्योम chain_table(काष्ठा bd_table *prev_table,
					काष्ठा bd_table *next_table,
					u32 bd_p_tab)
अणु
	/* Chain the prev table to next table */
	prev_table->start_bd[bd_p_tab-1].offset[0] =
				cpu_to_le32(lower_32_bits(next_table->dma));

	prev_table->start_bd[bd_p_tab-1].offset[1] =
				cpu_to_le32(upper_32_bits(next_table->dma));

	prev_table->start_bd[bd_p_tab-1].offset[2] =
				0x0;

	prev_table->start_bd[bd_p_tab-1].offset[3] =
				cpu_to_le32(MARK_CHAIN_BD);
पूर्ण

/* Allocate the bdl क्रम ep, during config ep */
अटल पूर्णांक ep_bd_list_alloc(काष्ठा bdc_ep *ep)
अणु
	काष्ठा bd_table *prev_table = शून्य;
	पूर्णांक index, num_tअसल, bd_p_tab;
	काष्ठा bdc *bdc = ep->bdc;
	काष्ठा bd_table *bd_table;
	dma_addr_t dma;

	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->desc))
		num_tअसल = NUM_TABLES_ISOCH;
	अन्यथा
		num_tअसल = NUM_TABLES;

	bd_p_tab = NUM_BDS_PER_TABLE;
	/* अगर there is only 1 table in bd list then loop chain to self */
	dev_dbg(bdc->dev,
		"%s ep:%p num_tabs:%d\n",
		__func__, ep, num_tअसल);

	/* Allocate memory क्रम table array */
	ep->bd_list.bd_table_array = kसुस्मृति(num_tअसल,
					     माप(काष्ठा bd_table *),
					     GFP_ATOMIC);
	अगर (!ep->bd_list.bd_table_array)
		वापस -ENOMEM;

	/* Allocate memory क्रम each table */
	क्रम (index = 0; index < num_tअसल; index++) अणु
		/* Allocate memory क्रम bd_table काष्ठाure */
		bd_table = kzalloc(माप(*bd_table), GFP_ATOMIC);
		अगर (!bd_table)
			जाओ fail;

		bd_table->start_bd = dma_pool_zalloc(bdc->bd_table_pool,
							GFP_ATOMIC,
							&dma);
		अगर (!bd_table->start_bd) अणु
			kमुक्त(bd_table);
			जाओ fail;
		पूर्ण

		bd_table->dma = dma;

		dev_dbg(bdc->dev,
			"index:%d start_bd:%p dma=%08llx prev_table:%p\n",
			index, bd_table->start_bd,
			(अचिन्हित दीर्घ दीर्घ)bd_table->dma, prev_table);

		ep->bd_list.bd_table_array[index] = bd_table;
		अगर (prev_table)
			chain_table(prev_table, bd_table, bd_p_tab);

		prev_table = bd_table;
	पूर्ण
	chain_table(prev_table, ep->bd_list.bd_table_array[0], bd_p_tab);
	/* Memory allocation is successful, now init the पूर्णांकernal fields */
	ep->bd_list.num_tअसल = num_tअसल;
	ep->bd_list.max_bdi  = (num_tअसल * bd_p_tab) - 1;
	ep->bd_list.num_tअसल = num_tअसल;
	ep->bd_list.num_bds_table = bd_p_tab;
	ep->bd_list.eqp_bdi = 0;
	ep->bd_list.hwd_bdi = 0;

	वापस 0;
fail:
	/* Free the bd_table_array, bd_table काष्ठा, bd's */
	ep_bd_list_मुक्त(ep, num_tअसल);

	वापस -ENOMEM;
पूर्ण

/* वापसs how many bd's are need क्रम this transfer */
अटल अंतरभूत पूर्णांक bd_needed_req(काष्ठा bdc_req *req)
अणु
	पूर्णांक bd_needed = 0;
	पूर्णांक reमुख्यing;

	/* 1 bd needed क्रम 0 byte transfer */
	अगर (req->usb_req.length == 0)
		वापस 1;

	/* reमुख्यing bytes after tranfering all max BD size BD's */
	reमुख्यing = req->usb_req.length % BD_MAX_BUFF_SIZE;
	अगर (reमुख्यing)
		bd_needed++;

	/* How many maximum BUFF size BD's ? */
	reमुख्यing = req->usb_req.length / BD_MAX_BUFF_SIZE;
	bd_needed += reमुख्यing;

	वापस bd_needed;
पूर्ण

/* वापसs the bd index(bdi) corresponding to bd dma address */
अटल पूर्णांक bd_add_to_bdi(काष्ठा bdc_ep *ep, dma_addr_t bd_dma_addr)
अणु
	काष्ठा bd_list *bd_list = &ep->bd_list;
	dma_addr_t dma_first_bd, dma_last_bd;
	काष्ठा bdc *bdc = ep->bdc;
	काष्ठा bd_table *bd_table;
	bool found = false;
	पूर्णांक tbi, bdi;

	dma_first_bd = dma_last_bd = 0;
	dev_dbg(bdc->dev, "%s  %llx\n",
			__func__, (अचिन्हित दीर्घ दीर्घ)bd_dma_addr);
	/*
	 * Find in which table this bd_dma_addr beदीर्घs?, go through the table
	 * array and compare addresses of first and last address of bd of each
	 * table
	 */
	क्रम (tbi = 0; tbi < bd_list->num_tअसल; tbi++) अणु
		bd_table = bd_list->bd_table_array[tbi];
		dma_first_bd = bd_table->dma;
		dma_last_bd = bd_table->dma +
					(माप(काष्ठा bdc_bd) *
					(bd_list->num_bds_table - 1));
		dev_dbg(bdc->dev, "dma_first_bd:%llx dma_last_bd:%llx\n",
					(अचिन्हित दीर्घ दीर्घ)dma_first_bd,
					(अचिन्हित दीर्घ दीर्घ)dma_last_bd);
		अगर (bd_dma_addr >= dma_first_bd && bd_dma_addr <= dma_last_bd) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (unlikely(!found)) अणु
		dev_err(bdc->dev, "%s FATAL err, bd not found\n", __func__);
		वापस -EINVAL;
	पूर्ण
	/* Now we know the table, find the bdi */
	bdi = (bd_dma_addr - dma_first_bd) / माप(काष्ठा bdc_bd);

	/* वापस the global bdi, to compare with ep eqp_bdi */
	वापस (bdi + (tbi * bd_list->num_bds_table));
पूर्ण

/* वापसs the table index(tbi) of the given bdi */
अटल पूर्णांक bdi_to_tbi(काष्ठा bdc_ep *ep, पूर्णांक bdi)
अणु
	पूर्णांक tbi;

	tbi = bdi / ep->bd_list.num_bds_table;
	dev_vdbg(ep->bdc->dev,
		"bdi:%d num_bds_table:%d tbi:%d\n",
		bdi, ep->bd_list.num_bds_table, tbi);

	वापस tbi;
पूर्ण

/* Find the bdi last bd in the transfer */
अटल अंतरभूत पूर्णांक find_end_bdi(काष्ठा bdc_ep *ep, पूर्णांक next_hwd_bdi)
अणु
	पूर्णांक end_bdi;

	end_bdi = next_hwd_bdi - 1;
	अगर (end_bdi < 0)
		end_bdi = ep->bd_list.max_bdi - 1;
	अन्यथा अगर ((end_bdi % (ep->bd_list.num_bds_table-1)) == 0)
		end_bdi--;

	वापस end_bdi;
पूर्ण

/*
 * How many transfer bd's are available on this ep bdl, chain bds are not
 * counted in available bds
 */
अटल पूर्णांक bd_available_ep(काष्ठा bdc_ep *ep)
अणु
	काष्ठा bd_list *bd_list = &ep->bd_list;
	पूर्णांक available1, available2;
	काष्ठा bdc *bdc = ep->bdc;
	पूर्णांक chain_bd1, chain_bd2;
	पूर्णांक available_bd = 0;

	available1 = available2 = chain_bd1 = chain_bd2 = 0;
	/* अगर empty then we have all bd's available - number of chain bd's */
	अगर (bd_list->eqp_bdi == bd_list->hwd_bdi)
		वापस bd_list->max_bdi - bd_list->num_tअसल;

	/*
	 * Depending upon where eqp and dqp poपूर्णांकers are, caculate number
	 * of avaialble bd's
	 */
	अगर (bd_list->hwd_bdi < bd_list->eqp_bdi) अणु
		/* available bd's are from eqp..max_bds + 0..dqp - chain_bds */
		available1 = bd_list->max_bdi - bd_list->eqp_bdi;
		available2 = bd_list->hwd_bdi;
		chain_bd1 = available1 / bd_list->num_bds_table;
		chain_bd2 = available2 / bd_list->num_bds_table;
		dev_vdbg(bdc->dev, "chain_bd1:%d chain_bd2:%d\n",
						chain_bd1, chain_bd2);
		available_bd = available1 + available2 - chain_bd1 - chain_bd2;
	पूर्ण अन्यथा अणु
		/* available bd's are from eqp..dqp - number of chain bd's */
		available1 = bd_list->hwd_bdi -  bd_list->eqp_bdi;
		/* अगर gap between eqp and dqp is less than NUM_BDS_PER_TABLE */
		अगर ((bd_list->hwd_bdi - bd_list->eqp_bdi)
					<= bd_list->num_bds_table) अणु
			/* If there any chain bd in between */
			अगर (!(bdi_to_tbi(ep, bd_list->hwd_bdi)
					== bdi_to_tbi(ep, bd_list->eqp_bdi))) अणु
				available_bd = available1 - 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			chain_bd1 = available1 / bd_list->num_bds_table;
			available_bd = available1 - chain_bd1;
		पूर्ण
	पूर्ण
	/*
	 * we need to keep one extra bd to check अगर ring is full or empty so
	 * reduce by 1
	 */
	available_bd--;
	dev_vdbg(bdc->dev, "available_bd:%d\n", available_bd);

	वापस available_bd;
पूर्ण

/* Notअगरy the hardware after queueing the bd to bdl */
व्योम bdc_notअगरy_xfr(काष्ठा bdc *bdc, u32 epnum)
अणु
	काष्ठा bdc_ep *ep = bdc->bdc_ep_array[epnum];

	dev_vdbg(bdc->dev, "%s epnum:%d\n", __func__, epnum);
	/*
	 * We करोn't have anyway to check अगर ep state is running,
	 * except the software flags.
	 */
	अगर (unlikely(ep->flags & BDC_EP_STOP))
		ep->flags &= ~BDC_EP_STOP;

	bdc_ग_लिखोl(bdc->regs, BDC_XSFNTF, epnum);
पूर्ण

/* वापसs the bd corresponding to bdi */
अटल काष्ठा bdc_bd *bdi_to_bd(काष्ठा bdc_ep *ep, पूर्णांक bdi)
अणु
	पूर्णांक tbi = bdi_to_tbi(ep, bdi);
	पूर्णांक local_bdi = 0;

	local_bdi = bdi - (tbi * ep->bd_list.num_bds_table);
	dev_vdbg(ep->bdc->dev,
		"%s bdi:%d local_bdi:%d\n",
		 __func__, bdi, local_bdi);

	वापस (ep->bd_list.bd_table_array[tbi]->start_bd + local_bdi);
पूर्ण

/* Advance the enqueue poपूर्णांकer */
अटल व्योम ep_bdlist_eqp_adv(काष्ठा bdc_ep *ep)
अणु
	ep->bd_list.eqp_bdi++;
	/* अगर it's chain bd, then move to next */
	अगर (((ep->bd_list.eqp_bdi + 1) % ep->bd_list.num_bds_table) == 0)
		ep->bd_list.eqp_bdi++;

	/* अगर the eqp is poपूर्णांकing to last + 1 then move back to 0 */
	अगर (ep->bd_list.eqp_bdi == (ep->bd_list.max_bdi + 1))
		ep->bd_list.eqp_bdi = 0;
पूर्ण

/* Setup the first bd क्रम ep0 transfer */
अटल पूर्णांक setup_first_bd_ep0(काष्ठा bdc *bdc, काष्ठा bdc_req *req, u32 *dword3)
अणु
	u16 wValue;
	u32 req_len;

	req->ep->dir = 0;
	req_len = req->usb_req.length;
	चयन (bdc->ep0_state) अणु
	हाल WAIT_FOR_DATA_START:
		*dword3 |= BD_TYPE_DS;
		अगर (bdc->setup_pkt.bRequestType & USB_सूची_IN)
			*dword3 |= BD_सूची_IN;

		/* check अगर zlp will be needed */
		wValue = le16_to_cpu(bdc->setup_pkt.wValue);
		अगर ((wValue > req_len) &&
				(req_len % bdc->gadget.ep0->maxpacket == 0)) अणु
			dev_dbg(bdc->dev, "ZLP needed wVal:%d len:%d MaxP:%d\n",
					wValue, req_len,
					bdc->gadget.ep0->maxpacket);
			bdc->zlp_needed = true;
		पूर्ण
		अवरोध;

	हाल WAIT_FOR_STATUS_START:
		*dword3 |= BD_TYPE_SS;
		अगर (!le16_to_cpu(bdc->setup_pkt.wLength) ||
				!(bdc->setup_pkt.bRequestType & USB_सूची_IN))
			*dword3 |= BD_सूची_IN;
		अवरोध;
	शेष:
		dev_err(bdc->dev,
			"Unknown ep0 state for queueing bd ep0_state:%s\n",
			ep0_state_string[bdc->ep0_state]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Setup the bd dma descriptor क्रम a given request */
अटल पूर्णांक setup_bd_list_xfr(काष्ठा bdc *bdc, काष्ठा bdc_req *req, पूर्णांक num_bds)
अणु
	dma_addr_t buf_add = req->usb_req.dma;
	u32 maxp, tfs, dword2, dword3;
	काष्ठा bd_transfer *bd_xfr;
	काष्ठा bd_list *bd_list;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc_bd *bd;
	पूर्णांक ret, bdnum;
	u32 req_len;

	ep = req->ep;
	bd_list = &ep->bd_list;
	bd_xfr = &req->bd_xfr;
	bd_xfr->req = req;
	bd_xfr->start_bdi = bd_list->eqp_bdi;
	bd = bdi_to_bd(ep, bd_list->eqp_bdi);
	req_len = req->usb_req.length;
	maxp = usb_endpoपूर्णांक_maxp(ep->desc);
	tfs = roundup(req->usb_req.length, maxp);
	tfs = tfs/maxp;
	dev_vdbg(bdc->dev, "%s ep:%s num_bds:%d tfs:%d r_len:%d bd:%p\n",
				__func__, ep->name, num_bds, tfs, req_len, bd);

	क्रम (bdnum = 0; bdnum < num_bds; bdnum++) अणु
		dword2 = dword3 = 0;
		/* First bd */
		अगर (!bdnum) अणु
			dword3 |= BD_SOT|BD_SBF|(tfs<<BD_TFS_SHIFT);
			dword2 |= BD_LTF;
			/* क्रमmat of first bd क्रम ep0 is dअगरferent than other */
			अगर (ep->ep_num == 1) अणु
				ret = setup_first_bd_ep0(bdc, req, &dword3);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		अगर (!req->ep->dir)
			dword3 |= BD_ISP;

		अगर (req_len > BD_MAX_BUFF_SIZE) अणु
			dword2 |= BD_MAX_BUFF_SIZE;
			req_len -= BD_MAX_BUFF_SIZE;
		पूर्ण अन्यथा अणु
			/* this should be the last bd */
			dword2 |= req_len;
			dword3 |= BD_IOC;
			dword3 |= BD_EOT;
		पूर्ण
		/* Currently only 1 INT target is supported */
		dword2 |= BD_INTR_TARGET(0);
		bd = bdi_to_bd(ep, ep->bd_list.eqp_bdi);
		अगर (unlikely(!bd)) अणु
			dev_err(bdc->dev, "Err bd pointing to wrong addr\n");
			वापस -EINVAL;
		पूर्ण
		/* ग_लिखो bd */
		bd->offset[0] = cpu_to_le32(lower_32_bits(buf_add));
		bd->offset[1] = cpu_to_le32(upper_32_bits(buf_add));
		bd->offset[2] = cpu_to_le32(dword2);
		bd->offset[3] = cpu_to_le32(dword3);
		/* advance eqp poपूर्णांकer */
		ep_bdlist_eqp_adv(ep);
		/* advance the buff poपूर्णांकer */
		buf_add += BD_MAX_BUFF_SIZE;
		dev_vdbg(bdc->dev, "buf_add:%08llx req_len:%d bd:%p eqp:%d\n",
				(अचिन्हित दीर्घ दीर्घ)buf_add, req_len, bd,
							ep->bd_list.eqp_bdi);
		bd = bdi_to_bd(ep, ep->bd_list.eqp_bdi);
		bd->offset[3] = cpu_to_le32(BD_SBF);
	पूर्ण
	/* clear the STOP BD fetch bit from the first bd of this xfr */
	bd = bdi_to_bd(ep, bd_xfr->start_bdi);
	bd->offset[3] &= cpu_to_le32(~BD_SBF);
	/* the new eqp will be next hw dqp */
	bd_xfr->num_bds  = num_bds;
	bd_xfr->next_hwd_bdi = ep->bd_list.eqp_bdi;
	/* everything is written correctly beक्रमe notअगरying the HW */
	wmb();

	वापस 0;
पूर्ण

/* Queue the xfr */
अटल पूर्णांक bdc_queue_xfr(काष्ठा bdc *bdc, काष्ठा bdc_req *req)
अणु
	पूर्णांक num_bds, bd_available;
	काष्ठा bdc_ep *ep;
	पूर्णांक ret;

	ep = req->ep;
	dev_dbg(bdc->dev, "%s req:%p\n", __func__, req);
	dev_dbg(bdc->dev, "eqp_bdi:%d hwd_bdi:%d\n",
			ep->bd_list.eqp_bdi, ep->bd_list.hwd_bdi);

	num_bds =  bd_needed_req(req);
	bd_available = bd_available_ep(ep);

	/* how many bd's are avaialble on ep */
	अगर (num_bds > bd_available)
		वापस -ENOMEM;

	ret = setup_bd_list_xfr(bdc, req, num_bds);
	अगर (ret)
		वापस ret;
	list_add_tail(&req->queue, &ep->queue);
	bdc_dbg_bd_list(bdc, ep);
	bdc_notअगरy_xfr(bdc, ep->ep_num);

	वापस 0;
पूर्ण

/* callback to gadget layer when xfr completes */
अटल व्योम bdc_req_complete(काष्ठा bdc_ep *ep, काष्ठा bdc_req *req,
						पूर्णांक status)
अणु
	काष्ठा bdc *bdc = ep->bdc;

	अगर (req == शून्य)
		वापस;

	dev_dbg(bdc->dev, "%s ep:%s status:%d\n", __func__, ep->name, status);
	list_del(&req->queue);
	req->usb_req.status = status;
	usb_gadget_unmap_request(&bdc->gadget, &req->usb_req, ep->dir);
	अगर (req->usb_req.complete) अणु
		spin_unlock(&bdc->lock);
		usb_gadget_giveback_request(&ep->usb_ep, &req->usb_req);
		spin_lock(&bdc->lock);
	पूर्ण
पूर्ण

/* Disable the endpoपूर्णांक */
पूर्णांक bdc_ep_disable(काष्ठा bdc_ep *ep)
अणु
	काष्ठा bdc_req *req;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	ret = 0;
	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s() ep->ep_num=%d\n", __func__, ep->ep_num);
	/* Stop the endpoपूर्णांक */
	ret = bdc_stop_ep(bdc, ep->ep_num);

	/*
	 * Intentionally करोn't check the ret value of stop, it can fail in
	 * disconnect scenarios, जारी with dconfig
	 */
	/* de-queue any pending requests */
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा bdc_req,
				queue);
		bdc_req_complete(ep, req, -ESHUTDOWN);
	पूर्ण
	/* deconfigure the endpoपूर्णांक */
	ret = bdc_dconfig_ep(bdc, ep);
	अगर (ret)
		dev_warn(bdc->dev,
			"dconfig fail but continue with memory free");

	ep->flags = 0;
	/* ep0 memory is not मुक्तd, but reused on next connect sr */
	अगर (ep->ep_num == 1)
		वापस 0;

	/* Free the bdl memory */
	ep_bd_list_मुक्त(ep, ep->bd_list.num_tअसल);
	ep->desc = शून्य;
	ep->comp_desc = शून्य;
	ep->usb_ep.desc = शून्य;
	ep->ep_type = 0;

	वापस ret;
पूर्ण

/* Enable the ep */
पूर्णांक bdc_ep_enable(काष्ठा bdc_ep *ep)
अणु
	काष्ठा bdc *bdc;
	पूर्णांक ret = 0;

	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s NUM_TABLES:%d %d\n",
					__func__, NUM_TABLES, NUM_TABLES_ISOCH);

	ret = ep_bd_list_alloc(ep);
	अगर (ret) अणु
		dev_err(bdc->dev, "ep bd list allocation failed:%d\n", ret);
		वापस -ENOMEM;
	पूर्ण
	bdc_dbg_bd_list(bdc, ep);
	/* only क्रम ep0: config ep is called क्रम ep0 from connect event */
	अगर (ep->ep_num == 1)
		वापस ret;

	/* Issue a configure endpoपूर्णांक command */
	ret = bdc_config_ep(bdc, ep);
	अगर (ret)
		वापस ret;

	ep->usb_ep.maxpacket = usb_endpoपूर्णांक_maxp(ep->desc);
	ep->usb_ep.desc = ep->desc;
	ep->usb_ep.comp_desc = ep->comp_desc;
	ep->ep_type = usb_endpoपूर्णांक_type(ep->desc);
	ep->flags |= BDC_EP_ENABLED;

	वापस 0;
पूर्ण

/* EP0 related code */

/* Queue a status stage BD */
अटल पूर्णांक ep0_queue_status_stage(काष्ठा bdc *bdc)
अणु
	काष्ठा bdc_req *status_req;
	काष्ठा bdc_ep *ep;

	status_req = &bdc->status_req;
	ep = bdc->bdc_ep_array[1];
	status_req->ep = ep;
	status_req->usb_req.length = 0;
	status_req->usb_req.status = -EINPROGRESS;
	status_req->usb_req.actual = 0;
	status_req->usb_req.complete = शून्य;
	bdc_queue_xfr(bdc, status_req);

	वापस 0;
पूर्ण

/* Queue xfr on ep0 */
अटल पूर्णांक ep0_queue(काष्ठा bdc_ep *ep, काष्ठा bdc_req *req)
अणु
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s()\n", __func__);
	req->usb_req.actual = 0;
	req->usb_req.status = -EINPROGRESS;
	req->epnum = ep->ep_num;

	अगर (bdc->delayed_status) अणु
		bdc->delayed_status = false;
		/* अगर status stage was delayed? */
		अगर (bdc->ep0_state == WAIT_FOR_STATUS_START) अणु
			/* Queue a status stage BD */
			ep0_queue_status_stage(bdc);
			bdc->ep0_state = WAIT_FOR_STATUS_XMIT;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * अगर delayed status is false and 0 length transfer is requested
		 * i.e. क्रम status stage of some setup request, then just
		 * वापस from here the status stage is queued independently
		 */
		अगर (req->usb_req.length == 0)
			वापस 0;

	पूर्ण
	ret = usb_gadget_map_request(&bdc->gadget, &req->usb_req, ep->dir);
	अगर (ret) अणु
		dev_err(bdc->dev, "dma mapping failed %s\n", ep->name);
		वापस ret;
	पूर्ण

	वापस bdc_queue_xfr(bdc, req);
पूर्ण

/* Queue data stage */
अटल पूर्णांक ep0_queue_data_stage(काष्ठा bdc *bdc)
अणु
	काष्ठा bdc_ep *ep;

	dev_dbg(bdc->dev, "%s\n", __func__);
	ep = bdc->bdc_ep_array[1];
	bdc->ep0_req.ep = ep;
	bdc->ep0_req.usb_req.complete = शून्य;

	वापस ep0_queue(ep, &bdc->ep0_req);
पूर्ण

/* Queue req on ep */
अटल पूर्णांक ep_queue(काष्ठा bdc_ep *ep, काष्ठा bdc_req *req)
अणु
	काष्ठा bdc *bdc;
	पूर्णांक ret = 0;

	अगर (!req || !ep->usb_ep.desc)
		वापस -EINVAL;

	bdc = ep->bdc;

	req->usb_req.actual = 0;
	req->usb_req.status = -EINPROGRESS;
	req->epnum = ep->ep_num;

	ret = usb_gadget_map_request(&bdc->gadget, &req->usb_req, ep->dir);
	अगर (ret) अणु
		dev_err(bdc->dev, "dma mapping failed\n");
		वापस ret;
	पूर्ण

	वापस bdc_queue_xfr(bdc, req);
पूर्ण

/* Dequeue a request from ep */
अटल पूर्णांक ep_dequeue(काष्ठा bdc_ep *ep, काष्ठा bdc_req *req)
अणु
	पूर्णांक start_bdi, end_bdi, tbi, eqp_bdi, curr_hw_dqpi;
	bool start_pending, end_pending;
	bool first_हटाओ = false;
	काष्ठा bdc_req *first_req;
	काष्ठा bdc_bd *bd_start;
	काष्ठा bd_table *table;
	dma_addr_t next_bd_dma;
	u64   deq_ptr_64 = 0;
	काष्ठा bdc  *bdc;
	u32    पंचांगp_32;
	पूर्णांक ret;

	bdc = ep->bdc;
	start_pending = end_pending = false;
	eqp_bdi = ep->bd_list.eqp_bdi - 1;

	अगर (eqp_bdi < 0)
		eqp_bdi = ep->bd_list.max_bdi;

	start_bdi = req->bd_xfr.start_bdi;
	end_bdi = find_end_bdi(ep, req->bd_xfr.next_hwd_bdi);

	dev_dbg(bdc->dev, "%s ep:%s start:%d end:%d\n",
					__func__, ep->name, start_bdi, end_bdi);
	dev_dbg(bdc->dev, "%s ep=%p ep->desc=%p\n", __func__,
						ep, (व्योम *)ep->usb_ep.desc);
	/* अगर still connected, stop the ep to see where the HW is ? */
	अगर (!(bdc_पढ़ोl(bdc->regs, BDC_USPC) & BDC_PST_MASK)) अणु
		ret = bdc_stop_ep(bdc, ep->ep_num);
		/* अगर there is an issue, then no need to go further */
		अगर (ret)
			वापस 0;
	पूर्ण अन्यथा
		वापस 0;

	/*
	 * After endpoपूर्णांक is stopped, there can be 3 हालs, the request
	 * is processed, pending or in the middle of processing
	 */

	/* The current hw dequeue poपूर्णांकer */
	पंचांगp_32 = bdc_पढ़ोl(bdc->regs, BDC_EPSTS0);
	deq_ptr_64 = पंचांगp_32;
	पंचांगp_32 = bdc_पढ़ोl(bdc->regs, BDC_EPSTS1);
	deq_ptr_64 |= ((u64)पंचांगp_32 << 32);

	/* we have the dma addr of next bd that will be fetched by hardware */
	curr_hw_dqpi = bd_add_to_bdi(ep, deq_ptr_64);
	अगर (curr_hw_dqpi < 0)
		वापस curr_hw_dqpi;

	/*
	 * curr_hw_dqpi poपूर्णांकs to actual dqp of HW and HW owns bd's from
	 * curr_hw_dqbdi..eqp_bdi.
	 */

	/* Check अगर start_bdi and end_bdi are in range of HW owned BD's */
	अगर (curr_hw_dqpi > eqp_bdi) अणु
		/* there is a wrap from last to 0 */
		अगर (start_bdi >= curr_hw_dqpi || start_bdi <= eqp_bdi) अणु
			start_pending = true;
			end_pending = true;
		पूर्ण अन्यथा अगर (end_bdi >= curr_hw_dqpi || end_bdi <= eqp_bdi) अणु
			end_pending = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (start_bdi >= curr_hw_dqpi) अणु
			start_pending = true;
			end_pending = true;
		पूर्ण अन्यथा अगर (end_bdi >= curr_hw_dqpi) अणु
			end_pending = true;
		पूर्ण
	पूर्ण
	dev_dbg(bdc->dev,
		"start_pending:%d end_pending:%d speed:%d\n",
		start_pending, end_pending, bdc->gadget.speed);

	/* If both start till end are processes, we cannot deq req */
	अगर (!start_pending && !end_pending)
		वापस -EINVAL;

	/*
	 * अगर ep_dequeue is called after disconnect then just वापस
	 * success from here
	 */
	अगर (bdc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस 0;
	tbi = bdi_to_tbi(ep, req->bd_xfr.next_hwd_bdi);
	table = ep->bd_list.bd_table_array[tbi];
	next_bd_dma =  table->dma +
			माप(काष्ठा bdc_bd)*(req->bd_xfr.next_hwd_bdi -
					tbi * ep->bd_list.num_bds_table);

	first_req = list_first_entry(&ep->queue, काष्ठा bdc_req,
			queue);

	अगर (req == first_req)
		first_हटाओ = true;

	/*
	 * Due to HW limitation we need to bypadd chain bd's and issue ep_bla,
	 * inहाल अगर start is pending this is the first request in the list
	 * then issue ep_bla instead of marking as chain bd
	 */
	अगर (start_pending && !first_हटाओ) अणु
		/*
		 * Mark the start bd as Chain bd, and poपूर्णांक the chain
		 * bd to next_bd_dma
		 */
		bd_start = bdi_to_bd(ep, start_bdi);
		bd_start->offset[0] = cpu_to_le32(lower_32_bits(next_bd_dma));
		bd_start->offset[1] = cpu_to_le32(upper_32_bits(next_bd_dma));
		bd_start->offset[2] = 0x0;
		bd_start->offset[3] = cpu_to_le32(MARK_CHAIN_BD);
		bdc_dbg_bd_list(bdc, ep);
	पूर्ण अन्यथा अगर (end_pending) अणु
		/*
		 * The transfer is stopped in the middle, move the
		 * HW deq poपूर्णांकer to next_bd_dma
		 */
		ret = bdc_ep_bla(bdc, ep, next_bd_dma);
		अगर (ret) अणु
			dev_err(bdc->dev, "error in ep_bla:%d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Halt/Clear the ep based on value */
अटल पूर्णांक ep_set_halt(काष्ठा bdc_ep *ep, u32 value)
अणु
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s ep:%s value=%d\n", __func__, ep->name, value);

	अगर (value) अणु
		dev_dbg(bdc->dev, "Halt\n");
		अगर (ep->ep_num == 1)
			bdc->ep0_state = WAIT_FOR_SETUP;

		ret = bdc_ep_set_stall(bdc, ep->ep_num);
		अगर (ret)
			dev_err(bdc->dev, "failed to set STALL on %s\n",
				ep->name);
		अन्यथा
			ep->flags |= BDC_EP_STALL;
	पूर्ण अन्यथा अणु
		/* Clear */
		dev_dbg(bdc->dev, "Before Clear\n");
		ret = bdc_ep_clear_stall(bdc, ep->ep_num);
		अगर (ret)
			dev_err(bdc->dev, "failed to clear STALL on %s\n",
				ep->name);
		अन्यथा
			ep->flags &= ~BDC_EP_STALL;
		dev_dbg(bdc->dev, "After  Clear\n");
	पूर्ण

	वापस ret;
पूर्ण

/* Free all the ep */
व्योम bdc_मुक्त_ep(काष्ठा bdc *bdc)
अणु
	काष्ठा bdc_ep *ep;
	u8	epnum;

	dev_dbg(bdc->dev, "%s\n", __func__);
	क्रम (epnum = 1; epnum < bdc->num_eps; epnum++) अणु
		ep = bdc->bdc_ep_array[epnum];
		अगर (!ep)
			जारी;

		अगर (ep->flags & BDC_EP_ENABLED)
			ep_bd_list_मुक्त(ep, ep->bd_list.num_tअसल);

		/* ep0 is not in this gadget list */
		अगर (epnum != 1)
			list_del(&ep->usb_ep.ep_list);

		kमुक्त(ep);
	पूर्ण
पूर्ण

/* USB2 spec, section 7.1.20 */
अटल पूर्णांक bdc_set_test_mode(काष्ठा bdc *bdc)
अणु
	u32 usb2_pm;

	usb2_pm = bdc_पढ़ोl(bdc->regs, BDC_USPPM2);
	usb2_pm &= ~BDC_PTC_MASK;
	dev_dbg(bdc->dev, "%s\n", __func__);
	चयन (bdc->test_mode) अणु
	हाल USB_TEST_J:
	हाल USB_TEST_K:
	हाल USB_TEST_SE0_NAK:
	हाल USB_TEST_PACKET:
	हाल USB_TEST_FORCE_ENABLE:
		usb2_pm |= bdc->test_mode << 28;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	dev_dbg(bdc->dev, "usb2_pm=%08x", usb2_pm);
	bdc_ग_लिखोl(bdc->regs, BDC_USPPM2, usb2_pm);

	वापस 0;
पूर्ण

/*
 * Helper function to handle Transfer status report with status as either
 * success or लघु
 */
अटल व्योम handle_xsr_succ_status(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep,
							काष्ठा bdc_sr *sreport)
अणु
	पूर्णांक लघु_bdi, start_bdi, end_bdi, max_len_bds, chain_bds;
	काष्ठा bd_list *bd_list = &ep->bd_list;
	पूर्णांक actual_length, length_लघु;
	काष्ठा bd_transfer *bd_xfr;
	काष्ठा bdc_bd *लघु_bd;
	काष्ठा bdc_req *req;
	u64   deq_ptr_64 = 0;
	पूर्णांक status = 0;
	पूर्णांक sr_status;
	u32    पंचांगp_32;

	dev_dbg(bdc->dev, "%s  ep:%p\n", __func__, ep);
	bdc_dbg_srr(bdc, 0);
	/* करो not process thie sr अगर ignore flag is set */
	अगर (ep->ignore_next_sr) अणु
		ep->ignore_next_sr = false;
		वापस;
	पूर्ण

	अगर (unlikely(list_empty(&ep->queue))) अणु
		dev_warn(bdc->dev, "xfr srr with no BD's queued\n");
		वापस;
	पूर्ण
	req = list_entry(ep->queue.next, काष्ठा bdc_req,
			queue);

	bd_xfr = &req->bd_xfr;
	sr_status = XSF_STS(le32_to_cpu(sreport->offset[3]));

	/*
	 * sr_status is लघु and this transfer has more than 1 bd then it needs
	 * special handling,  this is only applicable क्रम bulk and ctrl
	 */
	अगर (sr_status == XSF_SHORT &&  bd_xfr->num_bds > 1) अणु
		/*
		 * This is multi bd xfr, lets see which bd
		 * caused लघु transfer and how many bytes have been
		 * transferred so far.
		 */
		पंचांगp_32 = le32_to_cpu(sreport->offset[0]);
		deq_ptr_64 = पंचांगp_32;
		पंचांगp_32 = le32_to_cpu(sreport->offset[1]);
		deq_ptr_64 |= ((u64)पंचांगp_32 << 32);
		लघु_bdi = bd_add_to_bdi(ep, deq_ptr_64);
		अगर (unlikely(लघु_bdi < 0))
			dev_warn(bdc->dev, "bd doesn't exist?\n");

		start_bdi =  bd_xfr->start_bdi;
		/*
		 * We know the start_bdi and लघु_bdi, how many xfr
		 * bds in between
		 */
		अगर (start_bdi <= लघु_bdi) अणु
			max_len_bds = लघु_bdi - start_bdi;
			अगर (max_len_bds <= bd_list->num_bds_table) अणु
				अगर (!(bdi_to_tbi(ep, start_bdi) ==
						bdi_to_tbi(ep, लघु_bdi)))
					max_len_bds--;
			पूर्ण अन्यथा अणु
				chain_bds = max_len_bds/bd_list->num_bds_table;
				max_len_bds -= chain_bds;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* there is a wrap in the ring within a xfr */
			chain_bds = (bd_list->max_bdi - start_bdi)/
							bd_list->num_bds_table;
			chain_bds += लघु_bdi/bd_list->num_bds_table;
			max_len_bds = bd_list->max_bdi - start_bdi;
			max_len_bds += लघु_bdi;
			max_len_bds -= chain_bds;
		पूर्ण
		/* max_len_bds is the number of full length bds */
		end_bdi = find_end_bdi(ep, bd_xfr->next_hwd_bdi);
		अगर (!(end_bdi == लघु_bdi))
			ep->ignore_next_sr = true;

		actual_length = max_len_bds * BD_MAX_BUFF_SIZE;
		लघु_bd = bdi_to_bd(ep, लघु_bdi);
		/* length queued */
		length_लघु = le32_to_cpu(लघु_bd->offset[2]) & 0x1FFFFF;
		/* actual length trensfered */
		length_लघु -= SR_BD_LEN(le32_to_cpu(sreport->offset[2]));
		actual_length += length_लघु;
		req->usb_req.actual = actual_length;
	पूर्ण अन्यथा अणु
		req->usb_req.actual = req->usb_req.length -
			SR_BD_LEN(le32_to_cpu(sreport->offset[2]));
		dev_dbg(bdc->dev,
			"len=%d actual=%d bd_xfr->next_hwd_bdi:%d\n",
			req->usb_req.length, req->usb_req.actual,
			bd_xfr->next_hwd_bdi);
	पूर्ण

	/* Update the dequeue poपूर्णांकer */
	ep->bd_list.hwd_bdi = bd_xfr->next_hwd_bdi;
	अगर (req->usb_req.actual < req->usb_req.length) अणु
		dev_dbg(bdc->dev, "short xfr on %d\n", ep->ep_num);
		अगर (req->usb_req.लघु_not_ok)
			status = -EREMOTEIO;
	पूर्ण
	bdc_req_complete(ep, bd_xfr->req, status);
पूर्ण

/* EP0 setup related packet handlers */

/*
 * Setup packet received, just store the packet and process on next DS or SS
 * started SR
 */
व्योम bdc_xsf_ep0_setup_recv(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	काष्ठा usb_ctrlrequest *setup_pkt;
	u32 len;

	dev_dbg(bdc->dev,
		"%s ep0_state:%s\n",
		__func__, ep0_state_string[bdc->ep0_state]);
	/* Store received setup packet */
	setup_pkt = &bdc->setup_pkt;
	स_नकल(setup_pkt, &sreport->offset[0], माप(*setup_pkt));
	len = le16_to_cpu(setup_pkt->wLength);
	अगर (!len)
		bdc->ep0_state = WAIT_FOR_STATUS_START;
	अन्यथा
		bdc->ep0_state = WAIT_FOR_DATA_START;


	dev_dbg(bdc->dev,
		"%s exit ep0_state:%s\n",
		__func__, ep0_state_string[bdc->ep0_state]);
पूर्ण

/* Stall ep0 */
अटल व्योम ep0_stall(काष्ठा bdc *bdc)
अणु
	काष्ठा bdc_ep	*ep = bdc->bdc_ep_array[1];
	काष्ठा bdc_req *req;

	dev_dbg(bdc->dev, "%s\n", __func__);
	bdc->delayed_status = false;
	ep_set_halt(ep, 1);

	/* de-queue any pendig requests */
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा bdc_req,
				queue);
		bdc_req_complete(ep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण

/* SET_ADD handlers */
अटल पूर्णांक ep0_set_address(काष्ठा bdc *bdc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = bdc->gadget.state;
	पूर्णांक ret = 0;
	u32 addr;

	addr = le16_to_cpu(ctrl->wValue);
	dev_dbg(bdc->dev,
		"%s addr:%d dev state:%d\n",
		__func__, addr, state);

	अगर (addr > 127)
		वापस -EINVAL;

	चयन (state) अणु
	हाल USB_STATE_DEFAULT:
	हाल USB_STATE_ADDRESS:
		/* Issue Address device command */
		ret = bdc_address_device(bdc, addr);
		अगर (ret)
			वापस ret;

		अगर (addr)
			usb_gadget_set_state(&bdc->gadget, USB_STATE_ADDRESS);
		अन्यथा
			usb_gadget_set_state(&bdc->gadget, USB_STATE_DEFAULT);

		bdc->dev_addr = addr;
		अवरोध;
	शेष:
		dev_warn(bdc->dev,
			"SET Address in wrong device state %d\n",
			state);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/* Handler क्रम SET/CLEAR FEATURE requests क्रम device */
अटल पूर्णांक ep0_handle_feature_dev(काष्ठा bdc *bdc, u16 wValue,
							u16 wIndex, bool set)
अणु
	क्रमागत usb_device_state state = bdc->gadget.state;
	u32	usppms = 0;

	dev_dbg(bdc->dev, "%s set:%d dev state:%d\n",
					__func__, set, state);
	चयन (wValue) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		dev_dbg(bdc->dev, "USB_DEVICE_REMOTE_WAKEUP\n");
		अगर (set)
			bdc->devstatus |= REMOTE_WAKE_ENABLE;
		अन्यथा
			bdc->devstatus &= ~REMOTE_WAKE_ENABLE;
		अवरोध;

	हाल USB_DEVICE_TEST_MODE:
		dev_dbg(bdc->dev, "USB_DEVICE_TEST_MODE\n");
		अगर ((wIndex & 0xFF) ||
				(bdc->gadget.speed != USB_SPEED_HIGH) || !set)
			वापस -EINVAL;

		bdc->test_mode = wIndex >> 8;
		अवरोध;

	हाल USB_DEVICE_U1_ENABLE:
		dev_dbg(bdc->dev, "USB_DEVICE_U1_ENABLE\n");

		अगर (bdc->gadget.speed != USB_SPEED_SUPER ||
						state != USB_STATE_CONFIGURED)
			वापस -EINVAL;

		usppms =  bdc_पढ़ोl(bdc->regs, BDC_USPPMS);
		अगर (set) अणु
			/* clear previous u1t */
			usppms &= ~BDC_U1T(BDC_U1T_MASK);
			usppms |= BDC_U1T(U1_TIMEOUT);
			usppms |= BDC_U1E | BDC_PORT_W1S;
			bdc->devstatus |= (1 << USB_DEV_STAT_U1_ENABLED);
		पूर्ण अन्यथा अणु
			usppms &= ~BDC_U1E;
			usppms |= BDC_PORT_W1S;
			bdc->devstatus &= ~(1 << USB_DEV_STAT_U1_ENABLED);
		पूर्ण
		bdc_ग_लिखोl(bdc->regs, BDC_USPPMS, usppms);
		अवरोध;

	हाल USB_DEVICE_U2_ENABLE:
		dev_dbg(bdc->dev, "USB_DEVICE_U2_ENABLE\n");

		अगर (bdc->gadget.speed != USB_SPEED_SUPER ||
						state != USB_STATE_CONFIGURED)
			वापस -EINVAL;

		usppms = bdc_पढ़ोl(bdc->regs, BDC_USPPMS);
		अगर (set) अणु
			usppms |= BDC_U2E;
			usppms |= BDC_U2A;
			bdc->devstatus |= (1 << USB_DEV_STAT_U2_ENABLED);
		पूर्ण अन्यथा अणु
			usppms &= ~BDC_U2E;
			usppms &= ~BDC_U2A;
			bdc->devstatus &= ~(1 << USB_DEV_STAT_U2_ENABLED);
		पूर्ण
		bdc_ग_लिखोl(bdc->regs, BDC_USPPMS, usppms);
		अवरोध;

	हाल USB_DEVICE_LTM_ENABLE:
		dev_dbg(bdc->dev, "USB_DEVICE_LTM_ENABLE?\n");
		अगर (bdc->gadget.speed != USB_SPEED_SUPER ||
						state != USB_STATE_CONFIGURED)
			वापस -EINVAL;
		अवरोध;
	शेष:
		dev_err(bdc->dev, "Unknown wValue:%d\n", wValue);
		वापस -EOPNOTSUPP;
	पूर्ण /* USB_RECIP_DEVICE end */

	वापस 0;
पूर्ण

/* SET/CLEAR FEATURE handler */
अटल पूर्णांक ep0_handle_feature(काष्ठा bdc *bdc,
			      काष्ठा usb_ctrlrequest *setup_pkt, bool set)
अणु
	क्रमागत usb_device_state state = bdc->gadget.state;
	काष्ठा bdc_ep *ep;
	u16 wValue;
	u16 wIndex;
	पूर्णांक epnum;

	wValue = le16_to_cpu(setup_pkt->wValue);
	wIndex = le16_to_cpu(setup_pkt->wIndex);

	dev_dbg(bdc->dev,
		"%s wValue=%d wIndex=%d	devstate=%08x speed=%d set=%d",
		__func__, wValue, wIndex, state,
		bdc->gadget.speed, set);

	चयन (setup_pkt->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		वापस ep0_handle_feature_dev(bdc, wValue, wIndex, set);
	हाल USB_RECIP_INTERFACE:
		dev_dbg(bdc->dev, "USB_RECIP_INTERFACE\n");
		/* USB3 spec, sec 9.4.9 */
		अगर (wValue != USB_INTRF_FUNC_SUSPEND)
			वापस -EINVAL;
		/* USB3 spec, Table 9-8 */
		अगर (set) अणु
			अगर (wIndex & USB_INTRF_FUNC_SUSPEND_RW) अणु
				dev_dbg(bdc->dev, "SET REMOTE_WAKEUP\n");
				bdc->devstatus |= REMOTE_WAKE_ENABLE;
			पूर्ण अन्यथा अणु
				dev_dbg(bdc->dev, "CLEAR REMOTE_WAKEUP\n");
				bdc->devstatus &= ~REMOTE_WAKE_ENABLE;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		dev_dbg(bdc->dev, "USB_RECIP_ENDPOINT\n");
		अगर (wValue != USB_ENDPOINT_HALT)
			वापस -EINVAL;

		epnum = wIndex & USB_ENDPOINT_NUMBER_MASK;
		अगर (epnum) अणु
			अगर ((wIndex & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN)
				epnum = epnum * 2 + 1;
			अन्यथा
				epnum *= 2;
		पूर्ण अन्यथा अणु
			epnum = 1; /*EP0*/
		पूर्ण
		/*
		 * If CLEAR_FEATURE on ep0 then करोn't करो anything as the stall
		 * condition on ep0 has alपढ़ोy been cleared when SETUP packet
		 * was received.
		 */
		अगर (epnum == 1 && !set) अणु
			dev_dbg(bdc->dev, "ep0 stall already cleared\n");
			वापस 0;
		पूर्ण
		dev_dbg(bdc->dev, "epnum=%d\n", epnum);
		ep = bdc->bdc_ep_array[epnum];
		अगर (!ep)
			वापस -EINVAL;

		वापस ep_set_halt(ep, set);
	शेष:
		dev_err(bdc->dev, "Unknown recipient\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* GET_STATUS request handler */
अटल पूर्णांक ep0_handle_status(काष्ठा bdc *bdc,
			     काष्ठा usb_ctrlrequest *setup_pkt)
अणु
	क्रमागत usb_device_state state = bdc->gadget.state;
	काष्ठा bdc_ep *ep;
	u16 usb_status = 0;
	u32 epnum;
	u16 wIndex;

	/* USB2.0 spec sec 9.4.5 */
	अगर (state == USB_STATE_DEFAULT)
		वापस -EINVAL;
	wIndex = le16_to_cpu(setup_pkt->wIndex);
	dev_dbg(bdc->dev, "%s\n", __func__);
	usb_status = bdc->devstatus;
	चयन (setup_pkt->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		dev_dbg(bdc->dev,
			"USB_RECIP_DEVICE devstatus:%08x\n",
			bdc->devstatus);
		/* USB3 spec, sec 9.4.5 */
		अगर (bdc->gadget.speed == USB_SPEED_SUPER)
			usb_status &= ~REMOTE_WAKE_ENABLE;
		अवरोध;

	हाल USB_RECIP_INTERFACE:
		dev_dbg(bdc->dev, "USB_RECIP_INTERFACE\n");
		अगर (bdc->gadget.speed == USB_SPEED_SUPER) अणु
			/*
			 * This should come from func क्रम Func remote wkup
			 * usb_status |=1;
			 */
			अगर (bdc->devstatus & REMOTE_WAKE_ENABLE)
				usb_status |= REMOTE_WAKE_ENABLE;
		पूर्ण अन्यथा अणु
			usb_status = 0;
		पूर्ण

		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		dev_dbg(bdc->dev, "USB_RECIP_ENDPOINT\n");
		epnum = wIndex & USB_ENDPOINT_NUMBER_MASK;
		अगर (epnum) अणु
			अगर ((wIndex & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN)
				epnum = epnum*2 + 1;
			अन्यथा
				epnum *= 2;
		पूर्ण अन्यथा अणु
			epnum = 1; /* EP0 */
		पूर्ण

		ep = bdc->bdc_ep_array[epnum];
		अगर (!ep) अणु
			dev_err(bdc->dev, "ISSUE, GET_STATUS for invalid EP ?");
			वापस -EINVAL;
		पूर्ण
		अगर (ep->flags & BDC_EP_STALL)
			usb_status |= 1 << USB_ENDPOINT_HALT;

		अवरोध;
	शेष:
		dev_err(bdc->dev, "Unknown recipient for get_status\n");
		वापस -EINVAL;
	पूर्ण
	/* prepare a data stage क्रम GET_STATUS */
	dev_dbg(bdc->dev, "usb_status=%08x\n", usb_status);
	*(__le16 *)bdc->ep0_response_buff = cpu_to_le16(usb_status);
	bdc->ep0_req.usb_req.length = 2;
	bdc->ep0_req.usb_req.buf = &bdc->ep0_response_buff;
	ep0_queue_data_stage(bdc);

	वापस 0;
पूर्ण

अटल व्योम ep0_set_sel_cmpl(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	/* ep0_set_sel_cmpl */
पूर्ण

/* Queue data stage to handle 6 byte SET_SEL request */
अटल पूर्णांक ep0_set_sel(काष्ठा bdc *bdc,
			     काष्ठा usb_ctrlrequest *setup_pkt)
अणु
	काष्ठा bdc_ep	*ep;
	u16	wLength;

	dev_dbg(bdc->dev, "%s\n", __func__);
	wLength = le16_to_cpu(setup_pkt->wLength);
	अगर (unlikely(wLength != 6)) अणु
		dev_err(bdc->dev, "%s Wrong wLength:%d\n", __func__, wLength);
		वापस -EINVAL;
	पूर्ण
	ep = bdc->bdc_ep_array[1];
	bdc->ep0_req.ep = ep;
	bdc->ep0_req.usb_req.length = 6;
	bdc->ep0_req.usb_req.buf = bdc->ep0_response_buff;
	bdc->ep0_req.usb_req.complete = ep0_set_sel_cmpl;
	ep0_queue_data_stage(bdc);

	वापस 0;
पूर्ण

/*
 * Queue a 0 byte bd only अगर wLength is more than the length and length is
 * a multiple of MaxPacket then queue 0 byte BD
 */
अटल पूर्णांक ep0_queue_zlp(काष्ठा bdc *bdc)
अणु
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s\n", __func__);
	bdc->ep0_req.ep = bdc->bdc_ep_array[1];
	bdc->ep0_req.usb_req.length = 0;
	bdc->ep0_req.usb_req.complete = शून्य;
	bdc->ep0_state = WAIT_FOR_DATA_START;
	ret = bdc_queue_xfr(bdc, &bdc->ep0_req);
	अगर (ret) अणु
		dev_err(bdc->dev, "err queueing zlp :%d\n", ret);
		वापस ret;
	पूर्ण
	bdc->ep0_state = WAIT_FOR_DATA_XMIT;

	वापस 0;
पूर्ण

/* Control request handler */
अटल पूर्णांक handle_control_request(काष्ठा bdc *bdc)
अणु
	क्रमागत usb_device_state state = bdc->gadget.state;
	काष्ठा usb_ctrlrequest *setup_pkt;
	पूर्णांक delegate_setup = 0;
	पूर्णांक ret = 0;
	पूर्णांक config = 0;

	setup_pkt = &bdc->setup_pkt;
	dev_dbg(bdc->dev, "%s\n", __func__);
	अगर ((setup_pkt->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (setup_pkt->bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			dev_dbg(bdc->dev, "USB_REQ_SET_ADDRESS\n");
			ret = ep0_set_address(bdc, setup_pkt);
			bdc->devstatus &= DEVSTATUS_CLEAR;
			अवरोध;

		हाल USB_REQ_SET_CONFIGURATION:
			dev_dbg(bdc->dev, "USB_REQ_SET_CONFIGURATION\n");
			अगर (state == USB_STATE_ADDRESS) अणु
				usb_gadget_set_state(&bdc->gadget,
							USB_STATE_CONFIGURED);
			पूर्ण अन्यथा अगर (state == USB_STATE_CONFIGURED) अणु
				/*
				 * USB2 spec sec 9.4.7, अगर wValue is 0 then dev
				 * is moved to addressed state
				 */
				config = le16_to_cpu(setup_pkt->wValue);
				अगर (!config)
					usb_gadget_set_state(
							&bdc->gadget,
							USB_STATE_ADDRESS);
			पूर्ण
			delegate_setup = 1;
			अवरोध;

		हाल USB_REQ_SET_FEATURE:
			dev_dbg(bdc->dev, "USB_REQ_SET_FEATURE\n");
			ret = ep0_handle_feature(bdc, setup_pkt, 1);
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
			dev_dbg(bdc->dev, "USB_REQ_CLEAR_FEATURE\n");
			ret = ep0_handle_feature(bdc, setup_pkt, 0);
			अवरोध;

		हाल USB_REQ_GET_STATUS:
			dev_dbg(bdc->dev, "USB_REQ_GET_STATUS\n");
			ret = ep0_handle_status(bdc, setup_pkt);
			अवरोध;

		हाल USB_REQ_SET_SEL:
			dev_dbg(bdc->dev, "USB_REQ_SET_SEL\n");
			ret = ep0_set_sel(bdc, setup_pkt);
			अवरोध;

		हाल USB_REQ_SET_ISOCH_DELAY:
			dev_warn(bdc->dev,
			"USB_REQ_SET_ISOCH_DELAY not handled\n");
			ret = 0;
			अवरोध;
		शेष:
			delegate_setup = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		delegate_setup = 1;
	पूर्ण

	अगर (delegate_setup) अणु
		spin_unlock(&bdc->lock);
		ret = bdc->gadget_driver->setup(&bdc->gadget, setup_pkt);
		spin_lock(&bdc->lock);
	पूर्ण

	वापस ret;
पूर्ण

/* EP0: Data stage started */
व्योम bdc_xsf_ep0_data_start(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	काष्ठा bdc_ep *ep;
	पूर्णांक ret = 0;

	dev_dbg(bdc->dev, "%s\n", __func__);
	ep = bdc->bdc_ep_array[1];
	/* If ep0 was stalled, the clear it first */
	अगर (ep->flags & BDC_EP_STALL) अणु
		ret = ep_set_halt(ep, 0);
		अगर (ret)
			जाओ err;
	पूर्ण
	अगर (bdc->ep0_state != WAIT_FOR_DATA_START)
		dev_warn(bdc->dev,
			"Data stage not expected ep0_state:%s\n",
			ep0_state_string[bdc->ep0_state]);

	ret = handle_control_request(bdc);
	अगर (ret == USB_GADGET_DELAYED_STATUS) अणु
		/*
		 * The ep0 state will reमुख्य WAIT_FOR_DATA_START till
		 * we received ep_queue on ep0
		 */
		bdc->delayed_status = true;
		वापस;
	पूर्ण
	अगर (!ret) अणु
		bdc->ep0_state = WAIT_FOR_DATA_XMIT;
		dev_dbg(bdc->dev,
			"ep0_state:%s", ep0_state_string[bdc->ep0_state]);
		वापस;
	पूर्ण
err:
	ep0_stall(bdc);
पूर्ण

/* EP0: status stage started */
व्योम bdc_xsf_ep0_status_start(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	काष्ठा usb_ctrlrequest *setup_pkt;
	काष्ठा bdc_ep *ep;
	पूर्णांक ret = 0;

	dev_dbg(bdc->dev,
		"%s ep0_state:%s",
		__func__, ep0_state_string[bdc->ep0_state]);
	ep = bdc->bdc_ep_array[1];

	/* check अगर ZLP was queued? */
	अगर (bdc->zlp_needed)
		bdc->zlp_needed = false;

	अगर (ep->flags & BDC_EP_STALL) अणु
		ret = ep_set_halt(ep, 0);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर ((bdc->ep0_state != WAIT_FOR_STATUS_START) &&
				(bdc->ep0_state != WAIT_FOR_DATA_XMIT))
		dev_err(bdc->dev,
			"Status stage recv but ep0_state:%s\n",
			ep0_state_string[bdc->ep0_state]);

	/* check अगर data stage is in progress ? */
	अगर (bdc->ep0_state == WAIT_FOR_DATA_XMIT) अणु
		bdc->ep0_state = STATUS_PENDING;
		/* Status stage will be queued upon Data stage transmit event */
		dev_dbg(bdc->dev,
			"status started but data  not transmitted yet\n");
		वापस;
	पूर्ण
	setup_pkt = &bdc->setup_pkt;

	/*
	 * 2 stage setup then only process the setup, क्रम 3 stage setup the date
	 * stage is alपढ़ोy handled
	 */
	अगर (!le16_to_cpu(setup_pkt->wLength)) अणु
		ret = handle_control_request(bdc);
		अगर (ret == USB_GADGET_DELAYED_STATUS) अणु
			bdc->delayed_status = true;
			/* ep0_state will reमुख्य WAIT_FOR_STATUS_START */
			वापस;
		पूर्ण
	पूर्ण
	अगर (!ret) अणु
		/* Queue a status stage BD */
		ep0_queue_status_stage(bdc);
		bdc->ep0_state = WAIT_FOR_STATUS_XMIT;
		dev_dbg(bdc->dev,
			"ep0_state:%s", ep0_state_string[bdc->ep0_state]);
		वापस;
	पूर्ण
err:
	ep0_stall(bdc);
पूर्ण

/* Helper function to update ep0 upon SR with xsf_succ or xsf_लघु */
अटल व्योम ep0_xsf_complete(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	dev_dbg(bdc->dev, "%s\n", __func__);
	चयन (bdc->ep0_state) अणु
	हाल WAIT_FOR_DATA_XMIT:
		bdc->ep0_state = WAIT_FOR_STATUS_START;
		अवरोध;
	हाल WAIT_FOR_STATUS_XMIT:
		bdc->ep0_state = WAIT_FOR_SETUP;
		अगर (bdc->test_mode) अणु
			पूर्णांक ret;

			dev_dbg(bdc->dev, "test_mode:%d\n", bdc->test_mode);
			ret = bdc_set_test_mode(bdc);
			अगर (ret < 0) अणु
				dev_err(bdc->dev, "Err in setting Test mode\n");
				वापस;
			पूर्ण
			bdc->test_mode = 0;
		पूर्ण
		अवरोध;
	हाल STATUS_PENDING:
		bdc_xsf_ep0_status_start(bdc, sreport);
		अवरोध;

	शेष:
		dev_err(bdc->dev,
			"Unknown ep0_state:%s\n",
			ep0_state_string[bdc->ep0_state]);

	पूर्ण
पूर्ण

/* xfr completion status report handler */
व्योम bdc_sr_xsf(काष्ठा bdc *bdc, काष्ठा bdc_sr *sreport)
अणु
	काष्ठा bdc_ep *ep;
	u32 sr_status;
	u8 ep_num;

	ep_num = (le32_to_cpu(sreport->offset[3])>>4) & 0x1f;
	ep = bdc->bdc_ep_array[ep_num];
	अगर (!ep || !(ep->flags & BDC_EP_ENABLED)) अणु
		dev_err(bdc->dev, "xsf for ep not enabled\n");
		वापस;
	पूर्ण
	/*
	 * check अगर this transfer is after link went from U3->U0 due
	 * to remote wakeup
	 */
	अगर (bdc->devstatus & FUNC_WAKE_ISSUED) अणु
		bdc->devstatus &= ~(FUNC_WAKE_ISSUED);
		dev_dbg(bdc->dev, "%s clearing FUNC_WAKE_ISSUED flag\n",
								__func__);
	पूर्ण
	sr_status = XSF_STS(le32_to_cpu(sreport->offset[3]));
	dev_dbg_ratelimited(bdc->dev, "%s sr_status=%d ep:%s\n",
					__func__, sr_status, ep->name);

	चयन (sr_status) अणु
	हाल XSF_SUCC:
	हाल XSF_SHORT:
		handle_xsr_succ_status(bdc, ep, sreport);
		अगर (ep_num == 1)
			ep0_xsf_complete(bdc, sreport);
		अवरोध;

	हाल XSF_SETUP_RECV:
	हाल XSF_DATA_START:
	हाल XSF_STATUS_START:
		अगर (ep_num != 1) अणु
			dev_err(bdc->dev,
				"ep0 related packets on non ep0 endpoint");
			वापस;
		पूर्ण
		bdc->sr_xsf_ep0[sr_status - XSF_SETUP_RECV](bdc, sreport);
		अवरोध;

	हाल XSF_BABB:
		अगर (ep_num == 1) अणु
			dev_dbg(bdc->dev, "Babble on ep0 zlp_need:%d\n",
							bdc->zlp_needed);
			/*
			 * If the last completed transfer had wLength >Data Len,
			 * and Len is multiple of MaxPacket,then queue ZLP
			 */
			अगर (bdc->zlp_needed) अणु
				/* queue 0 length bd */
				ep0_queue_zlp(bdc);
				वापस;
			पूर्ण
		पूर्ण
		dev_warn(bdc->dev, "Babble on ep not handled\n");
		अवरोध;
	शेष:
		dev_warn(bdc->dev, "sr status not handled:%x\n", sr_status);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bdc_gadget_ep_queue(काष्ठा usb_ep *_ep,
				काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा bdc_req *req;
	अचिन्हित दीर्घ flags;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	अगर (!_ep || !_ep->desc)
		वापस -ESHUTDOWN;

	अगर (!_req || !_req->complete || !_req->buf)
		वापस -EINVAL;

	ep = to_bdc_ep(_ep);
	req = to_bdc_req(_req);
	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s ep:%p req:%p\n", __func__, ep, req);
	dev_dbg(bdc->dev, "queuing request %p to %s length %d zero:%d\n",
				_req, ep->name, _req->length, _req->zero);

	अगर (!ep->usb_ep.desc) अणु
		dev_warn(bdc->dev,
			"trying to queue req %p to disabled %s\n",
			_req, ep->name);
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (_req->length > MAX_XFR_LEN) अणु
		dev_warn(bdc->dev,
			"req length > supported MAX:%d requested:%d\n",
			MAX_XFR_LEN, _req->length);
		वापस -EOPNOTSUPP;
	पूर्ण
	spin_lock_irqsave(&bdc->lock, flags);
	अगर (ep == bdc->bdc_ep_array[1])
		ret = ep0_queue(ep, req);
	अन्यथा
		ret = ep_queue(ep, req);

	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक bdc_gadget_ep_dequeue(काष्ठा usb_ep *_ep,
				  काष्ठा usb_request *_req)
अणु
	काष्ठा bdc_req *req;
	अचिन्हित दीर्घ flags;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	ep = to_bdc_ep(_ep);
	req = to_bdc_req(_req);
	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s ep:%s req:%p\n", __func__, ep->name, req);
	bdc_dbg_bd_list(bdc, ep);
	spin_lock_irqsave(&bdc->lock, flags);
	/* make sure it's still queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->usb_req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->usb_req != _req) अणु
		spin_unlock_irqrestore(&bdc->lock, flags);
		dev_err(bdc->dev, "usb_req !=req n");
		वापस -EINVAL;
	पूर्ण
	ret = ep_dequeue(ep, req);
	अगर (ret) अणु
		ret = -EOPNOTSUPP;
		जाओ err;
	पूर्ण
	bdc_req_complete(ep, req, -ECONNRESET);

err:
	bdc_dbg_bd_list(bdc, ep);
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक bdc_gadget_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	ep = to_bdc_ep(_ep);
	bdc = ep->bdc;
	dev_dbg(bdc->dev, "%s ep:%s value=%d\n", __func__, ep->name, value);
	spin_lock_irqsave(&bdc->lock, flags);
	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->usb_ep.desc))
		ret = -EINVAL;
	अन्यथा अगर (!list_empty(&ep->queue))
		ret = -EAGAIN;
	अन्यथा
		ret = ep_set_halt(ep, value);

	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा usb_request *bdc_gadget_alloc_request(काष्ठा usb_ep *_ep,
						     gfp_t gfp_flags)
अणु
	काष्ठा bdc_req *req;
	काष्ठा bdc_ep *ep;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	ep = to_bdc_ep(_ep);
	req->ep = ep;
	req->epnum = ep->ep_num;
	req->usb_req.dma = DMA_ADDR_INVALID;
	dev_dbg(ep->bdc->dev, "%s ep:%s req:%p\n", __func__, ep->name, req);

	वापस &req->usb_req;
पूर्ण

अटल व्योम bdc_gadget_मुक्त_request(काष्ठा usb_ep *_ep,
				     काष्ठा usb_request *_req)
अणु
	काष्ठा bdc_req *req;

	req = to_bdc_req(_req);
	kमुक्त(req);
पूर्ण

/* endpoपूर्णांक operations */

/* configure endpoपूर्णांक and also allocate resources */
अटल पूर्णांक bdc_gadget_ep_enable(काष्ठा usb_ep *_ep,
				 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	अगर (!_ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		pr_debug("%s invalid parameters\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->wMaxPacketSize) अणु
		pr_debug("%s missing wMaxPacketSize\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = to_bdc_ep(_ep);
	bdc = ep->bdc;

	/* Sanity check, upper layer will not send enable क्रम ep0 */
	अगर (ep == bdc->bdc_ep_array[1])
		वापस -EINVAL;

	अगर (!bdc->gadget_driver
	    || bdc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		वापस -ESHUTDOWN;
	पूर्ण

	dev_dbg(bdc->dev, "%s Enabling %s\n", __func__, ep->name);
	spin_lock_irqsave(&bdc->lock, flags);
	ep->desc = desc;
	ep->comp_desc = _ep->comp_desc;
	ret = bdc_ep_enable(ep);
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक bdc_gadget_ep_disable(काष्ठा usb_ep *_ep)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bdc_ep *ep;
	काष्ठा bdc *bdc;
	पूर्णांक ret;

	अगर (!_ep) अणु
		pr_debug("bdc: invalid parameters\n");
		वापस -EINVAL;
	पूर्ण
	ep = to_bdc_ep(_ep);
	bdc = ep->bdc;

	/* Upper layer will not call this क्रम ep0, but करो a sanity check */
	अगर (ep == bdc->bdc_ep_array[1]) अणु
		dev_warn(bdc->dev, "%s called for ep0\n", __func__);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(bdc->dev,
		"%s() ep:%s ep->flags:%08x\n",
		__func__, ep->name, ep->flags);

	अगर (!(ep->flags & BDC_EP_ENABLED)) अणु
		अगर (bdc->gadget.speed != USB_SPEED_UNKNOWN)
			dev_warn(bdc->dev, "%s is already disabled\n",
				 ep->name);
		वापस 0;
	पूर्ण
	spin_lock_irqsave(&bdc->lock, flags);
	ret = bdc_ep_disable(ep);
	spin_unlock_irqrestore(&bdc->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops bdc_gadget_ep_ops = अणु
	.enable = bdc_gadget_ep_enable,
	.disable = bdc_gadget_ep_disable,
	.alloc_request = bdc_gadget_alloc_request,
	.मुक्त_request = bdc_gadget_मुक्त_request,
	.queue = bdc_gadget_ep_queue,
	.dequeue = bdc_gadget_ep_dequeue,
	.set_halt = bdc_gadget_ep_set_halt
पूर्ण;

/* dir = 1 is IN */
अटल पूर्णांक init_ep(काष्ठा bdc *bdc, u32 epnum, u32 dir)
अणु
	काष्ठा bdc_ep *ep;

	dev_dbg(bdc->dev, "%s epnum=%d dir=%d\n", __func__, epnum, dir);
	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep->bdc = bdc;
	ep->dir = dir;

	अगर (dir)
		ep->usb_ep.caps.dir_in = true;
	अन्यथा
		ep->usb_ep.caps.dir_out = true;

	/* ep->ep_num is the index inside bdc_ep */
	अगर (epnum == 1) अणु
		ep->ep_num = 1;
		bdc->bdc_ep_array[ep->ep_num] = ep;
		snम_लिखो(ep->name, माप(ep->name), "ep%d", epnum - 1);
		usb_ep_set_maxpacket_limit(&ep->usb_ep, EP0_MAX_PKT_SIZE);
		ep->usb_ep.caps.type_control = true;
		ep->comp_desc = शून्य;
		bdc->gadget.ep0 = &ep->usb_ep;
	पूर्ण अन्यथा अणु
		अगर (dir)
			ep->ep_num = epnum * 2 - 1;
		अन्यथा
			ep->ep_num = epnum * 2 - 2;

		bdc->bdc_ep_array[ep->ep_num] = ep;
		snम_लिखो(ep->name, माप(ep->name), "ep%d%s", epnum - 1,
			 dir & 1 ? "in" : "out");

		usb_ep_set_maxpacket_limit(&ep->usb_ep, 1024);
		ep->usb_ep.caps.type_iso = true;
		ep->usb_ep.caps.type_bulk = true;
		ep->usb_ep.caps.type_पूर्णांक = true;
		ep->usb_ep.max_streams = 0;
		list_add_tail(&ep->usb_ep.ep_list, &bdc->gadget.ep_list);
	पूर्ण
	ep->usb_ep.ops = &bdc_gadget_ep_ops;
	ep->usb_ep.name = ep->name;
	ep->flags = 0;
	ep->ignore_next_sr = false;
	dev_dbg(bdc->dev, "ep=%p ep->usb_ep.name=%s epnum=%d ep->epnum=%d\n",
				ep, ep->usb_ep.name, epnum, ep->ep_num);

	INIT_LIST_HEAD(&ep->queue);

	वापस 0;
पूर्ण

/* Init all ep */
पूर्णांक bdc_init_ep(काष्ठा bdc *bdc)
अणु
	u8 epnum;
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	INIT_LIST_HEAD(&bdc->gadget.ep_list);
	/* init ep0 */
	ret = init_ep(bdc, 1, 0);
	अगर (ret) अणु
		dev_err(bdc->dev, "init ep ep0 fail %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (epnum = 2; epnum <= bdc->num_eps / 2; epnum++) अणु
		/* OUT */
		ret = init_ep(bdc, epnum, 0);
		अगर (ret) अणु
			dev_err(bdc->dev,
				"init ep failed for:%d error: %d\n",
				epnum, ret);
			वापस ret;
		पूर्ण

		/* IN */
		ret = init_ep(bdc, epnum, 1);
		अगर (ret) अणु
			dev_err(bdc->dev,
				"init ep failed for:%d error: %d\n",
				epnum, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
