<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 *
 */

#अगर_अघोषित __MTK_CMDQ_H__
#घोषणा __MTK_CMDQ_H__

#समावेश <linux/mailbox_client.h>
#समावेश <linux/mailbox/mtk-cmdq-mailbox.h>
#समावेश <linux/समयr.h>

#घोषणा CMDQ_ADDR_HIGH(addr)	((u32)(((addr) >> 16) & GENMASK(31, 0)))
#घोषणा CMDQ_ADDR_LOW(addr)	((u16)(addr) | BIT(1))

काष्ठा cmdq_pkt;

काष्ठा cmdq_client_reg अणु
	u8 subsys;
	u16 offset;
	u16 size;
पूर्ण;

काष्ठा cmdq_client अणु
	काष्ठा mbox_client client;
	काष्ठा mbox_chan *chan;
पूर्ण;

/**
 * cmdq_dev_get_client_reg() - parse cmdq client reg from the device
 *			       node of CMDQ client
 * @dev:	device of CMDQ mailbox client
 * @client_reg: CMDQ client reg poपूर्णांकer
 * @idx:	the index of desired reg
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 *
 * Help CMDQ client parsing the cmdq client reg
 * from the device node of CMDQ client.
 */
पूर्णांक cmdq_dev_get_client_reg(काष्ठा device *dev,
			    काष्ठा cmdq_client_reg *client_reg, पूर्णांक idx);

/**
 * cmdq_mbox_create() - create CMDQ mailbox client and channel
 * @dev:	device of CMDQ mailbox client
 * @index:	index of CMDQ mailbox channel
 *
 * Return: CMDQ mailbox client poपूर्णांकer
 */
काष्ठा cmdq_client *cmdq_mbox_create(काष्ठा device *dev, पूर्णांक index);

/**
 * cmdq_mbox_destroy() - destroy CMDQ mailbox client and channel
 * @client:	the CMDQ mailbox client
 */
व्योम cmdq_mbox_destroy(काष्ठा cmdq_client *client);

/**
 * cmdq_pkt_create() - create a CMDQ packet
 * @client:	the CMDQ mailbox client
 * @size:	required CMDQ buffer size
 *
 * Return: CMDQ packet poपूर्णांकer
 */
काष्ठा cmdq_pkt *cmdq_pkt_create(काष्ठा cmdq_client *client, माप_प्रकार size);

/**
 * cmdq_pkt_destroy() - destroy the CMDQ packet
 * @pkt:	the CMDQ packet
 */
व्योम cmdq_pkt_destroy(काष्ठा cmdq_pkt *pkt);

/**
 * cmdq_pkt_ग_लिखो() - append ग_लिखो command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub प्रणाली code
 * @offset:	रेजिस्टर offset from CMDQ sub प्रणाली
 * @value:	the specअगरied target रेजिस्टर value
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_ग_लिखो(काष्ठा cmdq_pkt *pkt, u8 subsys, u16 offset, u32 value);

/**
 * cmdq_pkt_ग_लिखो_mask() - append ग_लिखो command with mask to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub प्रणाली code
 * @offset:	रेजिस्टर offset from CMDQ sub प्रणाली
 * @value:	the specअगरied target रेजिस्टर value
 * @mask:	the specअगरied target रेजिस्टर mask
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_ग_लिखो_mask(काष्ठा cmdq_pkt *pkt, u8 subsys,
			u16 offset, u32 value, u32 mask);

/*
 * cmdq_pkt_पढ़ो_s() - append पढ़ो_s command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addr_reg_idx:	पूर्णांकernal रेजिस्टर ID which contains high address of pa
 * @addr_low:	low address of pa
 * @reg_idx:	the CMDQ पूर्णांकernal रेजिस्टर ID to cache पढ़ो data
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_पढ़ो_s(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx, u16 addr_low,
		    u16 reg_idx);

/**
 * cmdq_pkt_ग_लिखो_s() - append ग_लिखो_s command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addr_reg_idx:	पूर्णांकernal रेजिस्टर ID which contains high address of pa
 * @addr_low:	low address of pa
 * @src_reg_idx:	the CMDQ पूर्णांकernal रेजिस्टर ID which cache source value
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 *
 * Support ग_लिखो value to physical address without subsys. Use CMDQ_ADDR_HIGH()
 * to get high address and call cmdq_pkt_assign() to assign value पूर्णांकo पूर्णांकernal
 * reg. Also use CMDQ_ADDR_LOW() to get low address क्रम addr_low parameter when
 * call to this function.
 */
पूर्णांक cmdq_pkt_ग_लिखो_s(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx,
		     u16 addr_low, u16 src_reg_idx);

/**
 * cmdq_pkt_ग_लिखो_s_mask() - append ग_लिखो_s with mask command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addr_reg_idx:	पूर्णांकernal रेजिस्टर ID which contains high address of pa
 * @addr_low:	low address of pa
 * @src_reg_idx:	the CMDQ पूर्णांकernal रेजिस्टर ID which cache source value
 * @mask:	the specअगरied target address mask, use U32_MAX अगर no need
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 *
 * Support ग_लिखो value to physical address without subsys. Use CMDQ_ADDR_HIGH()
 * to get high address and call cmdq_pkt_assign() to assign value पूर्णांकo पूर्णांकernal
 * reg. Also use CMDQ_ADDR_LOW() to get low address क्रम addr_low parameter when
 * call to this function.
 */
पूर्णांक cmdq_pkt_ग_लिखो_s_mask(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx,
			  u16 addr_low, u16 src_reg_idx, u32 mask);

/**
 * cmdq_pkt_ग_लिखो_s_value() - append ग_लिखो_s command to the CMDQ packet which
 *			      ग_लिखो value to a physical address
 * @pkt:	the CMDQ packet
 * @high_addr_reg_idx:	पूर्णांकernal रेजिस्टर ID which contains high address of pa
 * @addr_low:	low address of pa
 * @value:	the specअगरied target value
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_ग_लिखो_s_value(काष्ठा cmdq_pkt *pkt, u8 high_addr_reg_idx,
			   u16 addr_low, u32 value);

/**
 * cmdq_pkt_ग_लिखो_s_mask_value() - append ग_लिखो_s command with mask to the CMDQ
 *				   packet which ग_लिखो value to a physical
 *				   address
 * @pkt:	the CMDQ packet
 * @high_addr_reg_idx:	पूर्णांकernal रेजिस्टर ID which contains high address of pa
 * @addr_low:	low address of pa
 * @value:	the specअगरied target value
 * @mask:	the specअगरied target mask
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_ग_लिखो_s_mask_value(काष्ठा cmdq_pkt *pkt, u8 high_addr_reg_idx,
				u16 addr_low, u32 value, u32 mask);

/**
 * cmdq_pkt_wfe() - append रुको क्रम event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desired event type to रुको
 * @clear:	clear event or not after event arrive
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_wfe(काष्ठा cmdq_pkt *pkt, u16 event, bool clear);

/**
 * cmdq_pkt_clear_event() - append clear event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desired event to be cleared
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_clear_event(काष्ठा cmdq_pkt *pkt, u16 event);

/**
 * cmdq_pkt_set_event() - append set event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desired event to be set
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_set_event(काष्ठा cmdq_pkt *pkt, u16 event);

/**
 * cmdq_pkt_poll() - Append polling command to the CMDQ packet, ask GCE to
 *		     execute an inकाष्ठाion that रुको क्रम a specअगरied
 *		     hardware रेजिस्टर to check क्रम the value w/o mask.
 *		     All GCE hardware thपढ़ोs will be blocked by this
 *		     inकाष्ठाion.
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub प्रणाली code
 * @offset:	रेजिस्टर offset from CMDQ sub प्रणाली
 * @value:	the specअगरied target रेजिस्टर value
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_poll(काष्ठा cmdq_pkt *pkt, u8 subsys,
		  u16 offset, u32 value);

/**
 * cmdq_pkt_poll_mask() - Append polling command to the CMDQ packet, ask GCE to
 *		          execute an inकाष्ठाion that रुको क्रम a specअगरied
 *		          hardware रेजिस्टर to check क्रम the value w/ mask.
 *		          All GCE hardware thपढ़ोs will be blocked by this
 *		          inकाष्ठाion.
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub प्रणाली code
 * @offset:	रेजिस्टर offset from CMDQ sub प्रणाली
 * @value:	the specअगरied target रेजिस्टर value
 * @mask:	the specअगरied target रेजिस्टर mask
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_poll_mask(काष्ठा cmdq_pkt *pkt, u8 subsys,
		       u16 offset, u32 value, u32 mask);

/**
 * cmdq_pkt_assign() - Append logic assign command to the CMDQ packet, ask GCE
 *		       to execute an inकाष्ठाion that set a स्थिरant value पूर्णांकo
 *		       पूर्णांकernal रेजिस्टर and use as value, mask or address in
 *		       पढ़ो/ग_लिखो inकाष्ठाion.
 * @pkt:	the CMDQ packet
 * @reg_idx:	the CMDQ पूर्णांकernal रेजिस्टर ID
 * @value:	the specअगरied value
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_assign(काष्ठा cmdq_pkt *pkt, u16 reg_idx, u32 value);

/**
 * cmdq_pkt_jump() - Append jump command to the CMDQ packet, ask GCE
 *		     to execute an inकाष्ठाion that change current thपढ़ो PC to
 *		     a physical address which should contains more inकाष्ठाion.
 * @pkt:        the CMDQ packet
 * @addr:       physical address of target inकाष्ठाion buffer
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_jump(काष्ठा cmdq_pkt *pkt, dma_addr_t addr);

/**
 * cmdq_pkt_finalize() - Append EOC and jump command to pkt.
 * @pkt:	the CMDQ packet
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 */
पूर्णांक cmdq_pkt_finalize(काष्ठा cmdq_pkt *pkt);

/**
 * cmdq_pkt_flush_async() - trigger CMDQ to asynchronously execute the CMDQ
 *                          packet and call back at the end of करोne packet
 * @pkt:	the CMDQ packet
 * @cb:		called at the end of करोne packet
 * @data:	this data will pass back to cb
 *
 * Return: 0 क्रम success; अन्यथा the error code is वापसed
 *
 * Trigger CMDQ to asynchronously execute the CMDQ packet and call back
 * at the end of करोne packet. Note that this is an ASYNC function. When the
 * function वापसed, it may or may not be finished.
 */
पूर्णांक cmdq_pkt_flush_async(काष्ठा cmdq_pkt *pkt, cmdq_async_flush_cb cb,
			 व्योम *data);

#पूर्ण_अगर	/* __MTK_CMDQ_H__ */
