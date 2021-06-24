<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

#समावेश "fjes_hw.h"
#समावेश "fjes.h"
#समावेश "fjes_trace.h"

अटल व्योम fjes_hw_update_zone_task(काष्ठा work_काष्ठा *);
अटल व्योम fjes_hw_epstop_task(काष्ठा work_काष्ठा *);

/* supported MTU list */
स्थिर u32 fjes_support_mtu[] = अणु
	FJES_MTU_DEFINE(8 * 1024),
	FJES_MTU_DEFINE(16 * 1024),
	FJES_MTU_DEFINE(32 * 1024),
	FJES_MTU_DEFINE(64 * 1024),
	0
पूर्ण;

u32 fjes_hw_rd32(काष्ठा fjes_hw *hw, u32 reg)
अणु
	u8 *base = hw->base;
	u32 value = 0;

	value = पढ़ोl(&base[reg]);

	वापस value;
पूर्ण

अटल u8 *fjes_hw_iomap(काष्ठा fjes_hw *hw)
अणु
	u8 *base;

	अगर (!request_mem_region(hw->hw_res.start, hw->hw_res.size,
				fjes_driver_name)) अणु
		pr_err("request_mem_region failed\n");
		वापस शून्य;
	पूर्ण

	base = (u8 *)ioremap(hw->hw_res.start, hw->hw_res.size);

	वापस base;
पूर्ण

अटल व्योम fjes_hw_iounmap(काष्ठा fjes_hw *hw)
अणु
	iounmap(hw->base);
	release_mem_region(hw->hw_res.start, hw->hw_res.size);
पूर्ण

पूर्णांक fjes_hw_reset(काष्ठा fjes_hw *hw)
अणु
	जोड़ REG_DCTL dctl;
	पूर्णांक समयout;

	dctl.reg = 0;
	dctl.bits.reset = 1;
	wr32(XSCT_DCTL, dctl.reg);

	समयout = FJES_DEVICE_RESET_TIMEOUT * 1000;
	dctl.reg = rd32(XSCT_DCTL);
	जबतक ((dctl.bits.reset == 1) && (समयout > 0)) अणु
		msleep(1000);
		dctl.reg = rd32(XSCT_DCTL);
		समयout -= 1000;
	पूर्ण

	वापस समयout > 0 ? 0 : -EIO;
पूर्ण

अटल पूर्णांक fjes_hw_get_max_epid(काष्ठा fjes_hw *hw)
अणु
	जोड़ REG_MAX_EP info;

	info.reg = rd32(XSCT_MAX_EP);

	वापस info.bits.maxep;
पूर्ण

अटल पूर्णांक fjes_hw_get_my_epid(काष्ठा fjes_hw *hw)
अणु
	जोड़ REG_OWNER_EPID info;

	info.reg = rd32(XSCT_OWNER_EPID);

	वापस info.bits.epid;
पूर्ण

अटल पूर्णांक fjes_hw_alloc_shared_status_region(काष्ठा fjes_hw *hw)
अणु
	माप_प्रकार size;

	size = माप(काष्ठा fjes_device_shared_info) +
	    (माप(u8) * hw->max_epid);
	hw->hw_info.share = kzalloc(size, GFP_KERNEL);
	अगर (!hw->hw_info.share)
		वापस -ENOMEM;

	hw->hw_info.share->epnum = hw->max_epid;

	वापस 0;
पूर्ण

अटल व्योम fjes_hw_मुक्त_shared_status_region(काष्ठा fjes_hw *hw)
अणु
	kमुक्त(hw->hw_info.share);
	hw->hw_info.share = शून्य;
पूर्ण

अटल पूर्णांक fjes_hw_alloc_epbuf(काष्ठा epbuf_handler *epbh)
अणु
	व्योम *mem;

	mem = vzalloc(EP_BUFFER_SIZE);
	अगर (!mem)
		वापस -ENOMEM;

	epbh->buffer = mem;
	epbh->size = EP_BUFFER_SIZE;

	epbh->info = (जोड़ ep_buffer_info *)mem;
	epbh->ring = (u8 *)(mem + माप(जोड़ ep_buffer_info));

	वापस 0;
पूर्ण

अटल व्योम fjes_hw_मुक्त_epbuf(काष्ठा epbuf_handler *epbh)
अणु
	vमुक्त(epbh->buffer);
	epbh->buffer = शून्य;
	epbh->size = 0;

	epbh->info = शून्य;
	epbh->ring = शून्य;
पूर्ण

व्योम fjes_hw_setup_epbuf(काष्ठा epbuf_handler *epbh, u8 *mac_addr, u32 mtu)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	u16 vlan_id[EP_BUFFER_SUPPORT_VLAN_MAX];
	पूर्णांक i;

	क्रम (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++)
		vlan_id[i] = info->v1i.vlan_id[i];

	स_रखो(info, 0, माप(जोड़ ep_buffer_info));

	info->v1i.version = 0;  /* version 0 */

	क्रम (i = 0; i < ETH_ALEN; i++)
		info->v1i.mac_addr[i] = mac_addr[i];

	info->v1i.head = 0;
	info->v1i.tail = 1;

	info->v1i.info_size = माप(जोड़ ep_buffer_info);
	info->v1i.buffer_size = epbh->size - info->v1i.info_size;

	info->v1i.frame_max = FJES_MTU_TO_FRAME_SIZE(mtu);
	info->v1i.count_max =
	    EP_RING_NUM(info->v1i.buffer_size, info->v1i.frame_max);

	क्रम (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++)
		info->v1i.vlan_id[i] = vlan_id[i];

	info->v1i.rx_status |= FJES_RX_MTU_CHANGING_DONE;
पूर्ण

व्योम
fjes_hw_init_command_रेजिस्टरs(काष्ठा fjes_hw *hw,
			       काष्ठा fjes_device_command_param *param)
अणु
	/* Request Buffer length */
	wr32(XSCT_REQBL, (__le32)(param->req_len));
	/* Response Buffer Length */
	wr32(XSCT_RESPBL, (__le32)(param->res_len));

	/* Request Buffer Address */
	wr32(XSCT_REQBAL,
	     (__le32)(param->req_start & GENMASK_ULL(31, 0)));
	wr32(XSCT_REQBAH,
	     (__le32)((param->req_start & GENMASK_ULL(63, 32)) >> 32));

	/* Response Buffer Address */
	wr32(XSCT_RESPBAL,
	     (__le32)(param->res_start & GENMASK_ULL(31, 0)));
	wr32(XSCT_RESPBAH,
	     (__le32)((param->res_start & GENMASK_ULL(63, 32)) >> 32));

	/* Share status address */
	wr32(XSCT_SHSTSAL,
	     (__le32)(param->share_start & GENMASK_ULL(31, 0)));
	wr32(XSCT_SHSTSAH,
	     (__le32)((param->share_start & GENMASK_ULL(63, 32)) >> 32));
पूर्ण

अटल पूर्णांक fjes_hw_setup(काष्ठा fjes_hw *hw)
अणु
	u8 mac[ETH_ALEN] = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	काष्ठा fjes_device_command_param param;
	काष्ठा ep_share_mem_info *buf_pair;
	अचिन्हित दीर्घ flags;
	माप_प्रकार mem_size;
	पूर्णांक result;
	पूर्णांक epidx;
	व्योम *buf;

	hw->hw_info.max_epid = &hw->max_epid;
	hw->hw_info.my_epid = &hw->my_epid;

	buf = kसुस्मृति(hw->max_epid, माप(काष्ठा ep_share_mem_info),
		      GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	hw->ep_shm_info = (काष्ठा ep_share_mem_info *)buf;

	mem_size = FJES_DEV_REQ_BUF_SIZE(hw->max_epid);
	hw->hw_info.req_buf = kzalloc(mem_size, GFP_KERNEL);
	अगर (!(hw->hw_info.req_buf))
		वापस -ENOMEM;

	hw->hw_info.req_buf_size = mem_size;

	mem_size = FJES_DEV_RES_BUF_SIZE(hw->max_epid);
	hw->hw_info.res_buf = kzalloc(mem_size, GFP_KERNEL);
	अगर (!(hw->hw_info.res_buf))
		वापस -ENOMEM;

	hw->hw_info.res_buf_size = mem_size;

	result = fjes_hw_alloc_shared_status_region(hw);
	अगर (result)
		वापस result;

	hw->hw_info.buffer_share_bit = 0;
	hw->hw_info.buffer_unshare_reserve_bit = 0;

	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx != hw->my_epid) अणु
			buf_pair = &hw->ep_shm_info[epidx];

			result = fjes_hw_alloc_epbuf(&buf_pair->tx);
			अगर (result)
				वापस result;

			result = fjes_hw_alloc_epbuf(&buf_pair->rx);
			अगर (result)
				वापस result;

			spin_lock_irqsave(&hw->rx_status_lock, flags);
			fjes_hw_setup_epbuf(&buf_pair->tx, mac,
					    fjes_support_mtu[0]);
			fjes_hw_setup_epbuf(&buf_pair->rx, mac,
					    fjes_support_mtu[0]);
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);
		पूर्ण
	पूर्ण

	स_रखो(&param, 0, माप(param));

	param.req_len = hw->hw_info.req_buf_size;
	param.req_start = __pa(hw->hw_info.req_buf);
	param.res_len = hw->hw_info.res_buf_size;
	param.res_start = __pa(hw->hw_info.res_buf);

	param.share_start = __pa(hw->hw_info.share->ep_status);

	fjes_hw_init_command_रेजिस्टरs(hw, &param);

	वापस 0;
पूर्ण

अटल व्योम fjes_hw_cleanup(काष्ठा fjes_hw *hw)
अणु
	पूर्णांक epidx;

	अगर (!hw->ep_shm_info)
		वापस;

	fjes_hw_मुक्त_shared_status_region(hw);

	kमुक्त(hw->hw_info.req_buf);
	hw->hw_info.req_buf = शून्य;

	kमुक्त(hw->hw_info.res_buf);
	hw->hw_info.res_buf = शून्य;

	क्रम (epidx = 0; epidx < hw->max_epid ; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;
		fjes_hw_मुक्त_epbuf(&hw->ep_shm_info[epidx].tx);
		fjes_hw_मुक्त_epbuf(&hw->ep_shm_info[epidx].rx);
	पूर्ण

	kमुक्त(hw->ep_shm_info);
	hw->ep_shm_info = शून्य;
पूर्ण

पूर्णांक fjes_hw_init(काष्ठा fjes_hw *hw)
अणु
	पूर्णांक ret;

	hw->base = fjes_hw_iomap(hw);
	अगर (!hw->base)
		वापस -EIO;

	ret = fjes_hw_reset(hw);
	अगर (ret)
		वापस ret;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, true);

	INIT_WORK(&hw->update_zone_task, fjes_hw_update_zone_task);
	INIT_WORK(&hw->epstop_task, fjes_hw_epstop_task);

	mutex_init(&hw->hw_info.lock);
	spin_lock_init(&hw->rx_status_lock);

	hw->max_epid = fjes_hw_get_max_epid(hw);
	hw->my_epid = fjes_hw_get_my_epid(hw);

	अगर ((hw->max_epid == 0) || (hw->my_epid >= hw->max_epid))
		वापस -ENXIO;

	ret = fjes_hw_setup(hw);

	hw->hw_info.trace = vzalloc(FJES_DEBUG_BUFFER_SIZE);
	hw->hw_info.trace_size = FJES_DEBUG_BUFFER_SIZE;

	वापस ret;
पूर्ण

व्योम fjes_hw_निकास(काष्ठा fjes_hw *hw)
अणु
	पूर्णांक ret;

	अगर (hw->base) अणु

		अगर (hw->debug_mode) अणु
			/* disable debug mode */
			mutex_lock(&hw->hw_info.lock);
			fjes_hw_stop_debug(hw);
			mutex_unlock(&hw->hw_info.lock);
		पूर्ण
		vमुक्त(hw->hw_info.trace);
		hw->hw_info.trace = शून्य;
		hw->hw_info.trace_size = 0;
		hw->debug_mode = 0;

		ret = fjes_hw_reset(hw);
		अगर (ret)
			pr_err("%s: reset error", __func__);

		fjes_hw_iounmap(hw);
		hw->base = शून्य;
	पूर्ण

	fjes_hw_cleanup(hw);

	cancel_work_sync(&hw->update_zone_task);
	cancel_work_sync(&hw->epstop_task);
पूर्ण

अटल क्रमागत fjes_dev_command_response_e
fjes_hw_issue_request_command(काष्ठा fjes_hw *hw,
			      क्रमागत fjes_dev_command_request_type type)
अणु
	क्रमागत fjes_dev_command_response_e ret = FJES_CMD_STATUS_UNKNOWN;
	जोड़ REG_CR cr;
	जोड़ REG_CS cs;
	पूर्णांक समयout = FJES_COMMAND_REQ_TIMEOUT * 1000;

	cr.reg = 0;
	cr.bits.req_start = 1;
	cr.bits.req_code = type;
	wr32(XSCT_CR, cr.reg);
	cr.reg = rd32(XSCT_CR);

	अगर (cr.bits.error == 0) अणु
		समयout = FJES_COMMAND_REQ_TIMEOUT * 1000;
		cs.reg = rd32(XSCT_CS);

		जबतक ((cs.bits.complete != 1) && समयout > 0) अणु
			msleep(1000);
			cs.reg = rd32(XSCT_CS);
			समयout -= 1000;
		पूर्ण

		अगर (cs.bits.complete == 1)
			ret = FJES_CMD_STATUS_NORMAL;
		अन्यथा अगर (समयout <= 0)
			ret = FJES_CMD_STATUS_TIMEOUT;

	पूर्ण अन्यथा अणु
		चयन (cr.bits.err_info) अणु
		हाल FJES_CMD_REQ_ERR_INFO_PARAM:
			ret = FJES_CMD_STATUS_ERROR_PARAM;
			अवरोध;
		हाल FJES_CMD_REQ_ERR_INFO_STATUS:
			ret = FJES_CMD_STATUS_ERROR_STATUS;
			अवरोध;
		शेष:
			ret = FJES_CMD_STATUS_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	trace_fjes_hw_issue_request_command(&cr, &cs, समयout, ret);

	वापस ret;
पूर्ण

पूर्णांक fjes_hw_request_info(काष्ठा fjes_hw *hw)
अणु
	जोड़ fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	जोड़ fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	क्रमागत fjes_dev_command_response_e ret;
	पूर्णांक result;

	स_रखो(req_buf, 0, hw->hw_info.req_buf_size);
	स_रखो(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->info.length = FJES_DEV_COMMAND_INFO_REQ_LEN;

	res_buf->info.length = 0;
	res_buf->info.code = 0;

	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_INFO);
	trace_fjes_hw_request_info(hw, res_buf);

	result = 0;

	अगर (FJES_DEV_COMMAND_INFO_RES_LEN((*hw->hw_info.max_epid)) !=
		res_buf->info.length) अणु
		trace_fjes_hw_request_info_err("Invalid res_buf");
		result = -ENOMSG;
	पूर्ण अन्यथा अगर (ret == FJES_CMD_STATUS_NORMAL) अणु
		चयन (res_buf->info.code) अणु
		हाल FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_TIMEOUT:
			trace_fjes_hw_request_info_err("Timeout");
			result = -EBUSY;
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_PARAM:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_STATUS:
			result = -EPERM;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक fjes_hw_रेजिस्टर_buff_addr(काष्ठा fjes_hw *hw, पूर्णांक dest_epid,
			       काष्ठा ep_share_mem_info *buf_pair)
अणु
	जोड़ fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	जोड़ fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	क्रमागत fjes_dev_command_response_e ret;
	पूर्णांक page_count;
	पूर्णांक समयout;
	पूर्णांक i, idx;
	व्योम *addr;
	पूर्णांक result;

	अगर (test_bit(dest_epid, &hw->hw_info.buffer_share_bit))
		वापस 0;

	स_रखो(req_buf, 0, hw->hw_info.req_buf_size);
	स_रखो(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->share_buffer.length = FJES_DEV_COMMAND_SHARE_BUFFER_REQ_LEN(
						buf_pair->tx.size,
						buf_pair->rx.size);
	req_buf->share_buffer.epid = dest_epid;

	idx = 0;
	req_buf->share_buffer.buffer[idx++] = buf_pair->tx.size;
	page_count = buf_pair->tx.size / EP_BUFFER_INFO_SIZE;
	क्रम (i = 0; i < page_count; i++) अणु
		addr = ((u8 *)(buf_pair->tx.buffer)) +
				(i * EP_BUFFER_INFO_SIZE);
		req_buf->share_buffer.buffer[idx++] =
				(__le64)(page_to_phys(vदो_स्मृति_to_page(addr)) +
						offset_in_page(addr));
	पूर्ण

	req_buf->share_buffer.buffer[idx++] = buf_pair->rx.size;
	page_count = buf_pair->rx.size / EP_BUFFER_INFO_SIZE;
	क्रम (i = 0; i < page_count; i++) अणु
		addr = ((u8 *)(buf_pair->rx.buffer)) +
				(i * EP_BUFFER_INFO_SIZE);
		req_buf->share_buffer.buffer[idx++] =
				(__le64)(page_to_phys(vदो_स्मृति_to_page(addr)) +
						offset_in_page(addr));
	पूर्ण

	res_buf->share_buffer.length = 0;
	res_buf->share_buffer.code = 0;

	trace_fjes_hw_रेजिस्टर_buff_addr_req(req_buf, buf_pair);

	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_SHARE_BUFFER);

	समयout = FJES_COMMAND_REQ_BUFF_TIMEOUT * 1000;
	जबतक ((ret == FJES_CMD_STATUS_NORMAL) &&
	       (res_buf->share_buffer.length ==
		FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN) &&
	       (res_buf->share_buffer.code == FJES_CMD_REQ_RES_CODE_BUSY) &&
	       (समयout > 0)) अणु
			msleep(200 + hw->my_epid * 20);
			समयout -= (200 + hw->my_epid * 20);

			res_buf->share_buffer.length = 0;
			res_buf->share_buffer.code = 0;

			ret = fjes_hw_issue_request_command(
					hw, FJES_CMD_REQ_SHARE_BUFFER);
	पूर्ण

	result = 0;

	trace_fjes_hw_रेजिस्टर_buff_addr(res_buf, समयout);

	अगर (res_buf->share_buffer.length !=
			FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN) अणु
		trace_fjes_hw_रेजिस्टर_buff_addr_err("Invalid res_buf");
		result = -ENOMSG;
	पूर्ण अन्यथा अगर (ret == FJES_CMD_STATUS_NORMAL) अणु
		चयन (res_buf->share_buffer.code) अणु
		हाल FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			set_bit(dest_epid, &hw->hw_info.buffer_share_bit);
			अवरोध;
		हाल FJES_CMD_REQ_RES_CODE_BUSY:
			trace_fjes_hw_रेजिस्टर_buff_addr_err("Busy Timeout");
			result = -EBUSY;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_TIMEOUT:
			trace_fjes_hw_रेजिस्टर_buff_addr_err("Timeout");
			result = -EBUSY;
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_PARAM:
		हाल FJES_CMD_STATUS_ERROR_STATUS:
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक fjes_hw_unरेजिस्टर_buff_addr(काष्ठा fjes_hw *hw, पूर्णांक dest_epid)
अणु
	जोड़ fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	जोड़ fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	काष्ठा fjes_device_shared_info *share = hw->hw_info.share;
	क्रमागत fjes_dev_command_response_e ret;
	पूर्णांक समयout;
	पूर्णांक result;

	अगर (!hw->base)
		वापस -EPERM;

	अगर (!req_buf || !res_buf || !share)
		वापस -EPERM;

	अगर (!test_bit(dest_epid, &hw->hw_info.buffer_share_bit))
		वापस 0;

	स_रखो(req_buf, 0, hw->hw_info.req_buf_size);
	स_रखो(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->unshare_buffer.length =
			FJES_DEV_COMMAND_UNSHARE_BUFFER_REQ_LEN;
	req_buf->unshare_buffer.epid = dest_epid;

	res_buf->unshare_buffer.length = 0;
	res_buf->unshare_buffer.code = 0;

	trace_fjes_hw_unरेजिस्टर_buff_addr_req(req_buf);
	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_UNSHARE_BUFFER);

	समयout = FJES_COMMAND_REQ_BUFF_TIMEOUT * 1000;
	जबतक ((ret == FJES_CMD_STATUS_NORMAL) &&
	       (res_buf->unshare_buffer.length ==
		FJES_DEV_COMMAND_UNSHARE_BUFFER_RES_LEN) &&
	       (res_buf->unshare_buffer.code ==
		FJES_CMD_REQ_RES_CODE_BUSY) &&
	       (समयout > 0)) अणु
		msleep(200 + hw->my_epid * 20);
		समयout -= (200 + hw->my_epid * 20);

		res_buf->unshare_buffer.length = 0;
		res_buf->unshare_buffer.code = 0;

		ret =
		fjes_hw_issue_request_command(hw, FJES_CMD_REQ_UNSHARE_BUFFER);
	पूर्ण

	result = 0;

	trace_fjes_hw_unरेजिस्टर_buff_addr(res_buf, समयout);

	अगर (res_buf->unshare_buffer.length !=
			FJES_DEV_COMMAND_UNSHARE_BUFFER_RES_LEN) अणु
		trace_fjes_hw_unरेजिस्टर_buff_addr_err("Invalid res_buf");
		result = -ENOMSG;
	पूर्ण अन्यथा अगर (ret == FJES_CMD_STATUS_NORMAL) अणु
		चयन (res_buf->unshare_buffer.code) अणु
		हाल FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			clear_bit(dest_epid, &hw->hw_info.buffer_share_bit);
			अवरोध;
		हाल FJES_CMD_REQ_RES_CODE_BUSY:
			trace_fjes_hw_unरेजिस्टर_buff_addr_err("Busy Timeout");
			result = -EBUSY;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_TIMEOUT:
			trace_fjes_hw_unरेजिस्टर_buff_addr_err("Timeout");
			result = -EBUSY;
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_PARAM:
		हाल FJES_CMD_STATUS_ERROR_STATUS:
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक fjes_hw_उठाओ_पूर्णांकerrupt(काष्ठा fjes_hw *hw, पूर्णांक dest_epid,
			    क्रमागत REG_ICTL_MASK  mask)
अणु
	u32 ig = mask | dest_epid;

	wr32(XSCT_IG, cpu_to_le32(ig));

	वापस 0;
पूर्ण

u32 fjes_hw_capture_पूर्णांकerrupt_status(काष्ठा fjes_hw *hw)
अणु
	u32 cur_is;

	cur_is = rd32(XSCT_IS);

	वापस cur_is;
पूर्ण

व्योम fjes_hw_set_irqmask(काष्ठा fjes_hw *hw,
			 क्रमागत REG_ICTL_MASK पूर्णांकr_mask, bool mask)
अणु
	अगर (mask)
		wr32(XSCT_IMS, पूर्णांकr_mask);
	अन्यथा
		wr32(XSCT_IMC, पूर्णांकr_mask);
पूर्ण

bool fjes_hw_epid_is_same_zone(काष्ठा fjes_hw *hw, पूर्णांक epid)
अणु
	अगर (epid >= hw->max_epid)
		वापस false;

	अगर ((hw->ep_shm_info[epid].es_status !=
			FJES_ZONING_STATUS_ENABLE) ||
		(hw->ep_shm_info[hw->my_epid].zone ==
			FJES_ZONING_ZONE_TYPE_NONE))
		वापस false;
	अन्यथा
		वापस (hw->ep_shm_info[epid].zone ==
				hw->ep_shm_info[hw->my_epid].zone);
पूर्ण

पूर्णांक fjes_hw_epid_is_shared(काष्ठा fjes_device_shared_info *share,
			   पूर्णांक dest_epid)
अणु
	पूर्णांक value = false;

	अगर (dest_epid < share->epnum)
		value = share->ep_status[dest_epid];

	वापस value;
पूर्ण

अटल bool fjes_hw_epid_is_stop_requested(काष्ठा fjes_hw *hw, पूर्णांक src_epid)
अणु
	वापस test_bit(src_epid, &hw->txrx_stop_req_bit);
पूर्ण

अटल bool fjes_hw_epid_is_stop_process_करोne(काष्ठा fjes_hw *hw, पूर्णांक src_epid)
अणु
	वापस (hw->ep_shm_info[src_epid].tx.info->v1i.rx_status &
			FJES_RX_STOP_REQ_DONE);
पूर्ण

क्रमागत ep_partner_status
fjes_hw_get_partner_ep_status(काष्ठा fjes_hw *hw, पूर्णांक epid)
अणु
	क्रमागत ep_partner_status status;

	अगर (fjes_hw_epid_is_shared(hw->hw_info.share, epid)) अणु
		अगर (fjes_hw_epid_is_stop_requested(hw, epid)) अणु
			status = EP_PARTNER_WAITING;
		पूर्ण अन्यथा अणु
			अगर (fjes_hw_epid_is_stop_process_करोne(hw, epid))
				status = EP_PARTNER_COMPLETE;
			अन्यथा
				status = EP_PARTNER_SHARED;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = EP_PARTNER_UNSHARE;
	पूर्ण

	वापस status;
पूर्ण

व्योम fjes_hw_उठाओ_epstop(काष्ठा fjes_hw *hw)
अणु
	क्रमागत ep_partner_status status;
	अचिन्हित दीर्घ flags;
	पूर्णांक epidx;

	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		status = fjes_hw_get_partner_ep_status(hw, epidx);
		चयन (status) अणु
		हाल EP_PARTNER_SHARED:
			fjes_hw_उठाओ_पूर्णांकerrupt(hw, epidx,
						REG_ICTL_MASK_TXRX_STOP_REQ);
			hw->ep_shm_info[epidx].ep_stats.send_पूर्णांकr_unshare += 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		set_bit(epidx, &hw->hw_info.buffer_unshare_reserve_bit);
		set_bit(epidx, &hw->txrx_stop_req_bit);

		spin_lock_irqsave(&hw->rx_status_lock, flags);
		hw->ep_shm_info[epidx].tx.info->v1i.rx_status |=
				FJES_RX_STOP_REQ_REQUEST;
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);
	पूर्ण
पूर्ण

पूर्णांक fjes_hw_रुको_epstop(काष्ठा fjes_hw *hw)
अणु
	क्रमागत ep_partner_status status;
	जोड़ ep_buffer_info *info;
	पूर्णांक रुको_समय = 0;
	पूर्णांक epidx;

	जबतक (hw->hw_info.buffer_unshare_reserve_bit &&
	       (रुको_समय < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)) अणु
		क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
			अगर (epidx == hw->my_epid)
				जारी;
			status = fjes_hw_epid_is_shared(hw->hw_info.share,
							epidx);
			info = hw->ep_shm_info[epidx].rx.info;
			अगर ((!status ||
			     (info->v1i.rx_status &
			      FJES_RX_STOP_REQ_DONE)) &&
			    test_bit(epidx,
				     &hw->hw_info.buffer_unshare_reserve_bit)) अणु
				clear_bit(epidx,
					  &hw->hw_info.buffer_unshare_reserve_bit);
			पूर्ण
		पूर्ण

		msleep(100);
		रुको_समय += 100;
	पूर्ण

	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;
		अगर (test_bit(epidx, &hw->hw_info.buffer_unshare_reserve_bit))
			clear_bit(epidx,
				  &hw->hw_info.buffer_unshare_reserve_bit);
	पूर्ण

	वापस (रुको_समय < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)
			? 0 : -EBUSY;
पूर्ण

bool fjes_hw_check_epbuf_version(काष्ठा epbuf_handler *epbh, u32 version)
अणु
	जोड़ ep_buffer_info *info = epbh->info;

	वापस (info->common.version == version);
पूर्ण

bool fjes_hw_check_mtu(काष्ठा epbuf_handler *epbh, u32 mtu)
अणु
	जोड़ ep_buffer_info *info = epbh->info;

	वापस ((info->v1i.frame_max == FJES_MTU_TO_FRAME_SIZE(mtu)) &&
		info->v1i.rx_status & FJES_RX_MTU_CHANGING_DONE);
पूर्ण

bool fjes_hw_check_vlan_id(काष्ठा epbuf_handler *epbh, u16 vlan_id)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	bool ret = false;
	पूर्णांक i;

	अगर (vlan_id == 0) अणु
		ret = true;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++) अणु
			अगर (vlan_id == info->v1i.vlan_id[i]) अणु
				ret = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool fjes_hw_set_vlan_id(काष्ठा epbuf_handler *epbh, u16 vlan_id)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	पूर्णांक i;

	क्रम (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++) अणु
		अगर (info->v1i.vlan_id[i] == 0) अणु
			info->v1i.vlan_id[i] = vlan_id;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

व्योम fjes_hw_del_vlan_id(काष्ठा epbuf_handler *epbh, u16 vlan_id)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	पूर्णांक i;

	अगर (0 != vlan_id) अणु
		क्रम (i = 0; i < EP_BUFFER_SUPPORT_VLAN_MAX; i++) अणु
			अगर (vlan_id == info->v1i.vlan_id[i])
				info->v1i.vlan_id[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

bool fjes_hw_epbuf_rx_is_empty(काष्ठा epbuf_handler *epbh)
अणु
	जोड़ ep_buffer_info *info = epbh->info;

	अगर (!(info->v1i.rx_status & FJES_RX_MTU_CHANGING_DONE))
		वापस true;

	अगर (info->v1i.count_max == 0)
		वापस true;

	वापस EP_RING_EMPTY(info->v1i.head, info->v1i.tail,
			     info->v1i.count_max);
पूर्ण

व्योम *fjes_hw_epbuf_rx_curpkt_get_addr(काष्ठा epbuf_handler *epbh,
				       माप_प्रकार *psize)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	काष्ठा esmem_frame *ring_frame;
	व्योम *frame;

	ring_frame = (काष्ठा esmem_frame *)&(epbh->ring[EP_RING_INDEX
					     (info->v1i.head,
					      info->v1i.count_max) *
					     info->v1i.frame_max]);

	*psize = (माप_प्रकार)ring_frame->frame_size;

	frame = ring_frame->frame_data;

	वापस frame;
पूर्ण

व्योम fjes_hw_epbuf_rx_curpkt_drop(काष्ठा epbuf_handler *epbh)
अणु
	जोड़ ep_buffer_info *info = epbh->info;

	अगर (fjes_hw_epbuf_rx_is_empty(epbh))
		वापस;

	EP_RING_INDEX_INC(epbh->info->v1i.head, info->v1i.count_max);
पूर्ण

पूर्णांक fjes_hw_epbuf_tx_pkt_send(काष्ठा epbuf_handler *epbh,
			      व्योम *frame, माप_प्रकार size)
अणु
	जोड़ ep_buffer_info *info = epbh->info;
	काष्ठा esmem_frame *ring_frame;

	अगर (EP_RING_FULL(info->v1i.head, info->v1i.tail, info->v1i.count_max))
		वापस -ENOBUFS;

	ring_frame = (काष्ठा esmem_frame *)&(epbh->ring[EP_RING_INDEX
					     (info->v1i.tail - 1,
					      info->v1i.count_max) *
					     info->v1i.frame_max]);

	ring_frame->frame_size = size;
	स_नकल((व्योम *)(ring_frame->frame_data), (व्योम *)frame, size);

	EP_RING_INDEX_INC(epbh->info->v1i.tail, info->v1i.count_max);

	वापस 0;
पूर्ण

अटल व्योम fjes_hw_update_zone_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_hw *hw = container_of(work,
			काष्ठा fjes_hw, update_zone_task);

	काष्ठा my_s अणुu8 es_status; u8 zone; पूर्ण *info;
	जोड़ fjes_device_command_res *res_buf;
	क्रमागत ep_partner_status pstatus;

	काष्ठा fjes_adapter *adapter;
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ flags;

	uदीर्घ unshare_bit = 0;
	uदीर्घ share_bit = 0;
	uदीर्घ irq_bit = 0;

	पूर्णांक epidx;
	पूर्णांक ret;

	adapter = (काष्ठा fjes_adapter *)hw->back;
	netdev = adapter->netdev;
	res_buf = hw->hw_info.res_buf;
	info = (काष्ठा my_s *)&res_buf->info.info;

	mutex_lock(&hw->hw_info.lock);

	ret = fjes_hw_request_info(hw);
	चयन (ret) अणु
	हाल -ENOMSG:
	हाल -EBUSY:
	शेष:
		अगर (!work_pending(&adapter->क्रमce_बंद_task)) अणु
			adapter->क्रमce_reset = true;
			schedule_work(&adapter->क्रमce_बंद_task);
		पूर्ण
		अवरोध;

	हाल 0:

		क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
			अगर (epidx == hw->my_epid) अणु
				hw->ep_shm_info[epidx].es_status =
					info[epidx].es_status;
				hw->ep_shm_info[epidx].zone =
					info[epidx].zone;
				जारी;
			पूर्ण

			pstatus = fjes_hw_get_partner_ep_status(hw, epidx);
			चयन (pstatus) अणु
			हाल EP_PARTNER_UNSHARE:
			शेष:
				अगर ((info[epidx].zone !=
					FJES_ZONING_ZONE_TYPE_NONE) &&
				    (info[epidx].es_status ==
					FJES_ZONING_STATUS_ENABLE) &&
				    (info[epidx].zone ==
					info[hw->my_epid].zone))
					set_bit(epidx, &share_bit);
				अन्यथा
					set_bit(epidx, &unshare_bit);
				अवरोध;

			हाल EP_PARTNER_COMPLETE:
			हाल EP_PARTNER_WAITING:
				अगर ((info[epidx].zone ==
					FJES_ZONING_ZONE_TYPE_NONE) ||
				    (info[epidx].es_status !=
					FJES_ZONING_STATUS_ENABLE) ||
				    (info[epidx].zone !=
					info[hw->my_epid].zone)) अणु
					set_bit(epidx,
						&adapter->unshare_watch_biपंचांगask);
					set_bit(epidx,
						&hw->hw_info.buffer_unshare_reserve_bit);
				पूर्ण
				अवरोध;

			हाल EP_PARTNER_SHARED:
				अगर ((info[epidx].zone ==
					FJES_ZONING_ZONE_TYPE_NONE) ||
				    (info[epidx].es_status !=
					FJES_ZONING_STATUS_ENABLE) ||
				    (info[epidx].zone !=
					info[hw->my_epid].zone))
					set_bit(epidx, &irq_bit);
				अवरोध;
			पूर्ण

			hw->ep_shm_info[epidx].es_status =
				info[epidx].es_status;
			hw->ep_shm_info[epidx].zone = info[epidx].zone;
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&hw->hw_info.lock);

	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;

		अगर (test_bit(epidx, &share_bit)) अणु
			spin_lock_irqsave(&hw->rx_status_lock, flags);
			fjes_hw_setup_epbuf(&hw->ep_shm_info[epidx].tx,
					    netdev->dev_addr, netdev->mtu);
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);

			mutex_lock(&hw->hw_info.lock);

			ret = fjes_hw_रेजिस्टर_buff_addr(
				hw, epidx, &hw->ep_shm_info[epidx]);

			चयन (ret) अणु
			हाल 0:
				अवरोध;
			हाल -ENOMSG:
			हाल -EBUSY:
			शेष:
				अगर (!work_pending(&adapter->क्रमce_बंद_task)) अणु
					adapter->क्रमce_reset = true;
					schedule_work(
					  &adapter->क्रमce_बंद_task);
				पूर्ण
				अवरोध;
			पूर्ण
			mutex_unlock(&hw->hw_info.lock);

			hw->ep_shm_info[epidx].ep_stats
					      .com_regist_buf_exec += 1;
		पूर्ण

		अगर (test_bit(epidx, &unshare_bit)) अणु
			mutex_lock(&hw->hw_info.lock);

			ret = fjes_hw_unरेजिस्टर_buff_addr(hw, epidx);

			चयन (ret) अणु
			हाल 0:
				अवरोध;
			हाल -ENOMSG:
			हाल -EBUSY:
			शेष:
				अगर (!work_pending(&adapter->क्रमce_बंद_task)) अणु
					adapter->क्रमce_reset = true;
					schedule_work(
					  &adapter->क्रमce_बंद_task);
				पूर्ण
				अवरोध;
			पूर्ण

			mutex_unlock(&hw->hw_info.lock);

			hw->ep_shm_info[epidx].ep_stats
					      .com_unregist_buf_exec += 1;

			अगर (ret == 0) अणु
				spin_lock_irqsave(&hw->rx_status_lock, flags);
				fjes_hw_setup_epbuf(
					&hw->ep_shm_info[epidx].tx,
					netdev->dev_addr, netdev->mtu);
				spin_unlock_irqrestore(&hw->rx_status_lock,
						       flags);
			पूर्ण
		पूर्ण

		अगर (test_bit(epidx, &irq_bit)) अणु
			fjes_hw_उठाओ_पूर्णांकerrupt(hw, epidx,
						REG_ICTL_MASK_TXRX_STOP_REQ);

			hw->ep_shm_info[epidx].ep_stats.send_पूर्णांकr_unshare += 1;

			set_bit(epidx, &hw->txrx_stop_req_bit);
			spin_lock_irqsave(&hw->rx_status_lock, flags);
			hw->ep_shm_info[epidx].tx.
				info->v1i.rx_status |=
					FJES_RX_STOP_REQ_REQUEST;
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);
			set_bit(epidx, &hw->hw_info.buffer_unshare_reserve_bit);
		पूर्ण
	पूर्ण

	अगर (irq_bit || adapter->unshare_watch_biपंचांगask) अणु
		अगर (!work_pending(&adapter->unshare_watch_task))
			queue_work(adapter->control_wq,
				   &adapter->unshare_watch_task);
	पूर्ण
पूर्ण

अटल व्योम fjes_hw_epstop_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fjes_hw *hw = container_of(work, काष्ठा fjes_hw, epstop_task);
	काष्ठा fjes_adapter *adapter = (काष्ठा fjes_adapter *)hw->back;
	अचिन्हित दीर्घ flags;

	uदीर्घ reमुख्य_bit;
	पूर्णांक epid_bit;

	जबतक ((reमुख्य_bit = hw->epstop_req_bit)) अणु
		क्रम (epid_bit = 0; reमुख्य_bit; reमुख्य_bit >>= 1, epid_bit++) अणु
			अगर (reमुख्य_bit & 1) अणु
				spin_lock_irqsave(&hw->rx_status_lock, flags);
				hw->ep_shm_info[epid_bit].
					tx.info->v1i.rx_status |=
						FJES_RX_STOP_REQ_DONE;
				spin_unlock_irqrestore(&hw->rx_status_lock,
						       flags);

				clear_bit(epid_bit, &hw->epstop_req_bit);
				set_bit(epid_bit,
					&adapter->unshare_watch_biपंचांगask);

				अगर (!work_pending(&adapter->unshare_watch_task))
					queue_work(
						adapter->control_wq,
						&adapter->unshare_watch_task);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक fjes_hw_start_debug(काष्ठा fjes_hw *hw)
अणु
	जोड़ fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	जोड़ fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	क्रमागत fjes_dev_command_response_e ret;
	पूर्णांक page_count;
	पूर्णांक result = 0;
	व्योम *addr;
	पूर्णांक i;

	अगर (!hw->hw_info.trace)
		वापस -EPERM;
	स_रखो(hw->hw_info.trace, 0, FJES_DEBUG_BUFFER_SIZE);

	स_रखो(req_buf, 0, hw->hw_info.req_buf_size);
	स_रखो(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->start_trace.length =
		FJES_DEV_COMMAND_START_DBG_REQ_LEN(hw->hw_info.trace_size);
	req_buf->start_trace.mode = hw->debug_mode;
	req_buf->start_trace.buffer_len = hw->hw_info.trace_size;
	page_count = hw->hw_info.trace_size / FJES_DEBUG_PAGE_SIZE;
	क्रम (i = 0; i < page_count; i++) अणु
		addr = ((u8 *)hw->hw_info.trace) + i * FJES_DEBUG_PAGE_SIZE;
		req_buf->start_trace.buffer[i] =
			(__le64)(page_to_phys(vदो_स्मृति_to_page(addr)) +
			offset_in_page(addr));
	पूर्ण

	res_buf->start_trace.length = 0;
	res_buf->start_trace.code = 0;

	trace_fjes_hw_start_debug_req(req_buf);
	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_START_DEBUG);
	trace_fjes_hw_start_debug(res_buf);

	अगर (res_buf->start_trace.length !=
		FJES_DEV_COMMAND_START_DBG_RES_LEN) अणु
		result = -ENOMSG;
		trace_fjes_hw_start_debug_err("Invalid res_buf");
	पूर्ण अन्यथा अगर (ret == FJES_CMD_STATUS_NORMAL) अणु
		चयन (res_buf->start_trace.code) अणु
		हाल FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_TIMEOUT:
			trace_fjes_hw_start_debug_err("Busy Timeout");
			result = -EBUSY;
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_PARAM:
		हाल FJES_CMD_STATUS_ERROR_STATUS:
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक fjes_hw_stop_debug(काष्ठा fjes_hw *hw)
अणु
	जोड़ fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	जोड़ fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	क्रमागत fjes_dev_command_response_e ret;
	पूर्णांक result = 0;

	अगर (!hw->hw_info.trace)
		वापस -EPERM;

	स_रखो(req_buf, 0, hw->hw_info.req_buf_size);
	स_रखो(res_buf, 0, hw->hw_info.res_buf_size);
	req_buf->stop_trace.length = FJES_DEV_COMMAND_STOP_DBG_REQ_LEN;

	res_buf->stop_trace.length = 0;
	res_buf->stop_trace.code = 0;

	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_STOP_DEBUG);
	trace_fjes_hw_stop_debug(res_buf);

	अगर (res_buf->stop_trace.length != FJES_DEV_COMMAND_STOP_DBG_RES_LEN) अणु
		trace_fjes_hw_stop_debug_err("Invalid res_buf");
		result = -ENOMSG;
	पूर्ण अन्यथा अगर (ret == FJES_CMD_STATUS_NORMAL) अणु
		चयन (res_buf->stop_trace.code) अणु
		हाल FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			hw->debug_mode = 0;
			अवरोध;
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			अवरोध;
		हाल FJES_CMD_STATUS_TIMEOUT:
			result = -EBUSY;
			trace_fjes_hw_stop_debug_err("Busy Timeout");
			अवरोध;
		हाल FJES_CMD_STATUS_ERROR_PARAM:
		हाल FJES_CMD_STATUS_ERROR_STATUS:
		शेष:
			result = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण
