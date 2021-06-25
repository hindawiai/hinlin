<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2016,2019 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"

/* Allocate the requested number of contiguous LSB slots
 * from the LSB biपंचांगap. Look in the निजी range क्रम this
 * queue first; failing that, check the खुला area.
 * If no space is available, रुको around.
 * Return: first slot number
 */
अटल u32 ccp_lsb_alloc(काष्ठा ccp_cmd_queue *cmd_q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा ccp_device *ccp;
	पूर्णांक start;

	/* First look at the map क्रम the queue */
	अगर (cmd_q->lsb >= 0) अणु
		start = (u32)biपंचांगap_find_next_zero_area(cmd_q->lsbmap,
							LSB_SIZE,
							0, count, 0);
		अगर (start < LSB_SIZE) अणु
			biपंचांगap_set(cmd_q->lsbmap, start, count);
			वापस start + cmd_q->lsb * LSB_SIZE;
		पूर्ण
	पूर्ण

	/* No joy; try to get an entry from the shared blocks */
	ccp = cmd_q->ccp;
	क्रम (;;) अणु
		mutex_lock(&ccp->sb_mutex);

		start = (u32)biपंचांगap_find_next_zero_area(ccp->lsbmap,
							MAX_LSB_CNT * LSB_SIZE,
							0,
							count, 0);
		अगर (start <= MAX_LSB_CNT * LSB_SIZE) अणु
			biपंचांगap_set(ccp->lsbmap, start, count);

			mutex_unlock(&ccp->sb_mutex);
			वापस start;
		पूर्ण

		ccp->sb_avail = 0;

		mutex_unlock(&ccp->sb_mutex);

		/* Wait क्रम KSB entries to become available */
		अगर (रुको_event_पूर्णांकerruptible(ccp->sb_queue, ccp->sb_avail))
			वापस 0;
	पूर्ण
पूर्ण

/* Free a number of LSB slots from the biपंचांगap, starting at
 * the indicated starting slot number.
 */
अटल व्योम ccp_lsb_मुक्त(काष्ठा ccp_cmd_queue *cmd_q, अचिन्हित पूर्णांक start,
			 अचिन्हित पूर्णांक count)
अणु
	अगर (!start)
		वापस;

	अगर (cmd_q->lsb == start) अणु
		/* An entry from the निजी LSB */
		biपंचांगap_clear(cmd_q->lsbmap, start, count);
	पूर्ण अन्यथा अणु
		/* From the shared LSBs */
		काष्ठा ccp_device *ccp = cmd_q->ccp;

		mutex_lock(&ccp->sb_mutex);
		biपंचांगap_clear(ccp->lsbmap, start, count);
		ccp->sb_avail = 1;
		mutex_unlock(&ccp->sb_mutex);
		wake_up_पूर्णांकerruptible_all(&ccp->sb_queue);
	पूर्ण
पूर्ण

/* CCP version 5: Union to define the function field (cmd_reg1/dword0) */
जोड़ ccp_function अणु
	काष्ठा अणु
		u16 size:7;
		u16 encrypt:1;
		u16 mode:5;
		u16 type:2;
	पूर्ण aes;
	काष्ठा अणु
		u16 size:7;
		u16 encrypt:1;
		u16 rsvd:5;
		u16 type:2;
	पूर्ण aes_xts;
	काष्ठा अणु
		u16 size:7;
		u16 encrypt:1;
		u16 mode:5;
		u16 type:2;
	पूर्ण des3;
	काष्ठा अणु
		u16 rsvd1:10;
		u16 type:4;
		u16 rsvd2:1;
	पूर्ण sha;
	काष्ठा अणु
		u16 mode:3;
		u16 size:12;
	पूर्ण rsa;
	काष्ठा अणु
		u16 byteswap:2;
		u16 bitwise:3;
		u16 reflect:2;
		u16 rsvd:8;
	पूर्ण pt;
	काष्ठा  अणु
		u16 rsvd:13;
	पूर्ण zlib;
	काष्ठा अणु
		u16 size:10;
		u16 type:2;
		u16 mode:3;
	पूर्ण ecc;
	u16 raw;
पूर्ण;

#घोषणा	CCP_AES_SIZE(p)		((p)->aes.size)
#घोषणा	CCP_AES_ENCRYPT(p)	((p)->aes.encrypt)
#घोषणा	CCP_AES_MODE(p)		((p)->aes.mode)
#घोषणा	CCP_AES_TYPE(p)		((p)->aes.type)
#घोषणा	CCP_XTS_SIZE(p)		((p)->aes_xts.size)
#घोषणा	CCP_XTS_TYPE(p)		((p)->aes_xts.type)
#घोषणा	CCP_XTS_ENCRYPT(p)	((p)->aes_xts.encrypt)
#घोषणा	CCP_DES3_SIZE(p)	((p)->des3.size)
#घोषणा	CCP_DES3_ENCRYPT(p)	((p)->des3.encrypt)
#घोषणा	CCP_DES3_MODE(p)	((p)->des3.mode)
#घोषणा	CCP_DES3_TYPE(p)	((p)->des3.type)
#घोषणा	CCP_SHA_TYPE(p)		((p)->sha.type)
#घोषणा	CCP_RSA_SIZE(p)		((p)->rsa.size)
#घोषणा	CCP_PT_BYTESWAP(p)	((p)->pt.byteswap)
#घोषणा	CCP_PT_BITWISE(p)	((p)->pt.bitwise)
#घोषणा	CCP_ECC_MODE(p)		((p)->ecc.mode)
#घोषणा	CCP_ECC_AFFINE(p)	((p)->ecc.one)

/* Word 0 */
#घोषणा CCP5_CMD_DW0(p)		((p)->dw0)
#घोषणा CCP5_CMD_SOC(p)		(CCP5_CMD_DW0(p).soc)
#घोषणा CCP5_CMD_IOC(p)		(CCP5_CMD_DW0(p).ioc)
#घोषणा CCP5_CMD_INIT(p)	(CCP5_CMD_DW0(p).init)
#घोषणा CCP5_CMD_EOM(p)		(CCP5_CMD_DW0(p).eom)
#घोषणा CCP5_CMD_FUNCTION(p)	(CCP5_CMD_DW0(p).function)
#घोषणा CCP5_CMD_ENGINE(p)	(CCP5_CMD_DW0(p).engine)
#घोषणा CCP5_CMD_PROT(p)	(CCP5_CMD_DW0(p).prot)

/* Word 1 */
#घोषणा CCP5_CMD_DW1(p)		((p)->length)
#घोषणा CCP5_CMD_LEN(p)		(CCP5_CMD_DW1(p))

/* Word 2 */
#घोषणा CCP5_CMD_DW2(p)		((p)->src_lo)
#घोषणा CCP5_CMD_SRC_LO(p)	(CCP5_CMD_DW2(p))

/* Word 3 */
#घोषणा CCP5_CMD_DW3(p)		((p)->dw3)
#घोषणा CCP5_CMD_SRC_MEM(p)	((p)->dw3.src_mem)
#घोषणा CCP5_CMD_SRC_HI(p)	((p)->dw3.src_hi)
#घोषणा CCP5_CMD_LSB_ID(p)	((p)->dw3.lsb_cxt_id)
#घोषणा CCP5_CMD_FIX_SRC(p)	((p)->dw3.fixed)

/* Words 4/5 */
#घोषणा CCP5_CMD_DW4(p)		((p)->dw4)
#घोषणा CCP5_CMD_DST_LO(p)	(CCP5_CMD_DW4(p).dst_lo)
#घोषणा CCP5_CMD_DW5(p)		((p)->dw5.fields.dst_hi)
#घोषणा CCP5_CMD_DST_HI(p)	(CCP5_CMD_DW5(p))
#घोषणा CCP5_CMD_DST_MEM(p)	((p)->dw5.fields.dst_mem)
#घोषणा CCP5_CMD_FIX_DST(p)	((p)->dw5.fields.fixed)
#घोषणा CCP5_CMD_SHA_LO(p)	((p)->dw4.sha_len_lo)
#घोषणा CCP5_CMD_SHA_HI(p)	((p)->dw5.sha_len_hi)

/* Word 6/7 */
#घोषणा CCP5_CMD_DW6(p)		((p)->key_lo)
#घोषणा CCP5_CMD_KEY_LO(p)	(CCP5_CMD_DW6(p))
#घोषणा CCP5_CMD_DW7(p)		((p)->dw7)
#घोषणा CCP5_CMD_KEY_HI(p)	((p)->dw7.key_hi)
#घोषणा CCP5_CMD_KEY_MEM(p)	((p)->dw7.key_mem)

अटल अंतरभूत u32 low_address(अचिन्हित दीर्घ addr)
अणु
	वापस (u64)addr & 0x0ffffffff;
पूर्ण

अटल अंतरभूत u32 high_address(अचिन्हित दीर्घ addr)
अणु
	वापस ((u64)addr >> 32) & 0x00000ffff;
पूर्ण

अटल अचिन्हित पूर्णांक ccp5_get_मुक्त_slots(काष्ठा ccp_cmd_queue *cmd_q)
अणु
	अचिन्हित पूर्णांक head_idx, n;
	u32 head_lo, queue_start;

	queue_start = low_address(cmd_q->qdma_tail);
	head_lo = ioपढ़ो32(cmd_q->reg_head_lo);
	head_idx = (head_lo - queue_start) / माप(काष्ठा ccp5_desc);

	n = head_idx + COMMANDS_PER_QUEUE - cmd_q->qidx - 1;

	वापस n % COMMANDS_PER_QUEUE; /* Always one unused spot */
पूर्ण

अटल पूर्णांक ccp5_करो_cmd(काष्ठा ccp5_desc *desc,
		       काष्ठा ccp_cmd_queue *cmd_q)
अणु
	__le32 *mP;
	u32 *dP;
	u32 tail;
	पूर्णांक	i;
	पूर्णांक ret = 0;

	cmd_q->total_ops++;

	अगर (CCP5_CMD_SOC(desc)) अणु
		CCP5_CMD_IOC(desc) = 1;
		CCP5_CMD_SOC(desc) = 0;
	पूर्ण
	mutex_lock(&cmd_q->q_mutex);

	mP = (__le32 *)&cmd_q->qbase[cmd_q->qidx];
	dP = (u32 *)desc;
	क्रम (i = 0; i < 8; i++)
		mP[i] = cpu_to_le32(dP[i]); /* handle endianness */

	cmd_q->qidx = (cmd_q->qidx + 1) % COMMANDS_PER_QUEUE;

	/* The data used by this command must be flushed to memory */
	wmb();

	/* Write the new tail address back to the queue रेजिस्टर */
	tail = low_address(cmd_q->qdma_tail + cmd_q->qidx * Q_DESC_SIZE);
	ioग_लिखो32(tail, cmd_q->reg_tail_lo);

	/* Turn the queue back on using our cached control रेजिस्टर */
	ioग_लिखो32(cmd_q->qcontrol | CMD5_Q_RUN, cmd_q->reg_control);
	mutex_unlock(&cmd_q->q_mutex);

	अगर (CCP5_CMD_IOC(desc)) अणु
		/* Wait क्रम the job to complete */
		ret = रुको_event_पूर्णांकerruptible(cmd_q->पूर्णांक_queue,
					       cmd_q->पूर्णांक_rcvd);
		अगर (ret || cmd_q->cmd_error) अणु
			/* Log the error and flush the queue by
			 * moving the head poपूर्णांकer
			 */
			अगर (cmd_q->cmd_error)
				ccp_log_error(cmd_q->ccp,
					      cmd_q->cmd_error);
			ioग_लिखो32(tail, cmd_q->reg_head_lo);
			अगर (!ret)
				ret = -EIO;
		पूर्ण
		cmd_q->पूर्णांक_rcvd = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_aes(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;
	u32 key_addr = op->sb_key * LSB_ITEM_SIZE;

	op->cmd_q->total_aes_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_AES;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_AES_ENCRYPT(&function) = op->u.aes.action;
	CCP_AES_MODE(&function) = op->u.aes.mode;
	CCP_AES_TYPE(&function) = op->u.aes.type;
	CCP_AES_SIZE(&function) = op->u.aes.size;

	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->src.u.dma.length;

	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_LO(&desc) = lower_32_bits(key_addr);
	CCP5_CMD_KEY_HI(&desc) = 0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_LSB_ID(&desc) = op->sb_ctx;

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_xts_aes(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;
	u32 key_addr = op->sb_key * LSB_ITEM_SIZE;

	op->cmd_q->total_xts_aes_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_XTS_AES_128;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_XTS_TYPE(&function) = op->u.xts.type;
	CCP_XTS_ENCRYPT(&function) = op->u.xts.action;
	CCP_XTS_SIZE(&function) = op->u.xts.unit_size;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->src.u.dma.length;

	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_LO(&desc) = lower_32_bits(key_addr);
	CCP5_CMD_KEY_HI(&desc) =  0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_LSB_ID(&desc) = op->sb_ctx;

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_sha(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;

	op->cmd_q->total_sha_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_SHA;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 1;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_SHA_TYPE(&function) = op->u.sha.type;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->src.u.dma.length;

	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_LSB_ID(&desc) = op->sb_ctx;

	अगर (op->eom) अणु
		CCP5_CMD_SHA_LO(&desc) = lower_32_bits(op->u.sha.msg_bits);
		CCP5_CMD_SHA_HI(&desc) = upper_32_bits(op->u.sha.msg_bits);
	पूर्ण अन्यथा अणु
		CCP5_CMD_SHA_LO(&desc) = 0;
		CCP5_CMD_SHA_HI(&desc) = 0;
	पूर्ण

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_des3(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;
	u32 key_addr = op->sb_key * LSB_ITEM_SIZE;

	op->cmd_q->total_3des_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, माप(काष्ठा ccp5_desc));

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_DES3;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = op->init;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_DES3_ENCRYPT(&function) = op->u.des3.action;
	CCP_DES3_MODE(&function) = op->u.des3.mode;
	CCP_DES3_TYPE(&function) = op->u.des3.type;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->src.u.dma.length;

	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_KEY_LO(&desc) = lower_32_bits(key_addr);
	CCP5_CMD_KEY_HI(&desc) = 0;
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SB;
	CCP5_CMD_LSB_ID(&desc) = op->sb_ctx;

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_rsa(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;

	op->cmd_q->total_rsa_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_RSA;

	CCP5_CMD_SOC(&desc) = op->soc;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = 1;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_RSA_SIZE(&function) = (op->u.rsa.mod_size + 7) >> 3;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->u.rsa.input_len;

	/* Source is from बाह्यal memory */
	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	/* Destination is in बाह्यal memory */
	CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	/* Key (Exponent) is in बाह्यal memory */
	CCP5_CMD_KEY_LO(&desc) = ccp_addr_lo(&op->exp.u.dma);
	CCP5_CMD_KEY_HI(&desc) = ccp_addr_hi(&op->exp.u.dma);
	CCP5_CMD_KEY_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_passthru(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;
	काष्ठा ccp_dma_info *saddr = &op->src.u.dma;
	काष्ठा ccp_dma_info *daddr = &op->dst.u.dma;


	op->cmd_q->total_pt_ops++;

	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_PASSTHRU;

	CCP5_CMD_SOC(&desc) = 0;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = op->eom;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	CCP_PT_BYTESWAP(&function) = op->u.passthru.byte_swap;
	CCP_PT_BITWISE(&function) = op->u.passthru.bit_mod;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	/* Length of source data is always 256 bytes */
	अगर (op->src.type == CCP_MEMTYPE_SYSTEM)
		CCP5_CMD_LEN(&desc) = saddr->length;
	अन्यथा
		CCP5_CMD_LEN(&desc) = daddr->length;

	अगर (op->src.type == CCP_MEMTYPE_SYSTEM) अणु
		CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
		CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
		CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

		अगर (op->u.passthru.bit_mod != CCP_PASSTHRU_BITWISE_NOOP)
			CCP5_CMD_LSB_ID(&desc) = op->sb_key;
	पूर्ण अन्यथा अणु
		u32 key_addr = op->src.u.sb * CCP_SB_BYTES;

		CCP5_CMD_SRC_LO(&desc) = lower_32_bits(key_addr);
		CCP5_CMD_SRC_HI(&desc) = 0;
		CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SB;
	पूर्ण

	अगर (op->dst.type == CCP_MEMTYPE_SYSTEM) अणु
		CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
		CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
		CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;
	पूर्ण अन्यथा अणु
		u32 key_addr = op->dst.u.sb * CCP_SB_BYTES;

		CCP5_CMD_DST_LO(&desc) = lower_32_bits(key_addr);
		CCP5_CMD_DST_HI(&desc) = 0;
		CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SB;
	पूर्ण

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp5_perक्रमm_ecc(काष्ठा ccp_op *op)
अणु
	काष्ठा ccp5_desc desc;
	जोड़ ccp_function function;

	op->cmd_q->total_ecc_ops++;

	/* Zero out all the fields of the command desc */
	स_रखो(&desc, 0, Q_DESC_SIZE);

	CCP5_CMD_ENGINE(&desc) = CCP_ENGINE_ECC;

	CCP5_CMD_SOC(&desc) = 0;
	CCP5_CMD_IOC(&desc) = 1;
	CCP5_CMD_INIT(&desc) = 0;
	CCP5_CMD_EOM(&desc) = 1;
	CCP5_CMD_PROT(&desc) = 0;

	function.raw = 0;
	function.ecc.mode = op->u.ecc.function;
	CCP5_CMD_FUNCTION(&desc) = function.raw;

	CCP5_CMD_LEN(&desc) = op->src.u.dma.length;

	CCP5_CMD_SRC_LO(&desc) = ccp_addr_lo(&op->src.u.dma);
	CCP5_CMD_SRC_HI(&desc) = ccp_addr_hi(&op->src.u.dma);
	CCP5_CMD_SRC_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	CCP5_CMD_DST_LO(&desc) = ccp_addr_lo(&op->dst.u.dma);
	CCP5_CMD_DST_HI(&desc) = ccp_addr_hi(&op->dst.u.dma);
	CCP5_CMD_DST_MEM(&desc) = CCP_MEMTYPE_SYSTEM;

	वापस ccp5_करो_cmd(&desc, op->cmd_q);
पूर्ण

अटल पूर्णांक ccp_find_lsb_regions(काष्ठा ccp_cmd_queue *cmd_q, u64 status)
अणु
	पूर्णांक q_mask = 1 << cmd_q->id;
	पूर्णांक queues = 0;
	पूर्णांक j;

	/* Build a bit mask to know which LSBs this queue has access to.
	 * Don't bother with segment 0 as it has special privileges.
	 */
	क्रम (j = 1; j < MAX_LSB_CNT; j++) अणु
		अगर (status & q_mask)
			biपंचांगap_set(cmd_q->lsbmask, j, 1);
		status >>= LSB_REGION_WIDTH;
	पूर्ण
	queues = biपंचांगap_weight(cmd_q->lsbmask, MAX_LSB_CNT);
	dev_dbg(cmd_q->ccp->dev, "Queue %d can access %d LSB regions\n",
		 cmd_q->id, queues);

	वापस queues ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ccp_find_and_assign_lsb_to_q(काष्ठा ccp_device *ccp,
					पूर्णांक lsb_cnt, पूर्णांक n_lsbs,
					अचिन्हित दीर्घ *lsb_pub)
अणु
	DECLARE_BITMAP(qlsb, MAX_LSB_CNT);
	पूर्णांक bitno;
	पूर्णांक qlsb_wgt;
	पूर्णांक i;

	/* For each queue:
	 * If the count of potential LSBs available to a queue matches the
	 * ordinal given to us in lsb_cnt:
	 * Copy the mask of possible LSBs क्रम this queue पूर्णांकo "qlsb";
	 * For each bit in qlsb, see अगर the corresponding bit in the
	 * aggregation mask is set; अगर so, we have a match.
	 *     If we have a match, clear the bit in the aggregation to
	 *     mark it as no दीर्घer available.
	 *     If there is no match, clear the bit in qlsb and keep looking.
	 */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		काष्ठा ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		qlsb_wgt = biपंचांगap_weight(cmd_q->lsbmask, MAX_LSB_CNT);

		अगर (qlsb_wgt == lsb_cnt) अणु
			biपंचांगap_copy(qlsb, cmd_q->lsbmask, MAX_LSB_CNT);

			bitno = find_first_bit(qlsb, MAX_LSB_CNT);
			जबतक (bitno < MAX_LSB_CNT) अणु
				अगर (test_bit(bitno, lsb_pub)) अणु
					/* We found an available LSB
					 * that this queue can access
					 */
					cmd_q->lsb = bitno;
					biपंचांगap_clear(lsb_pub, bitno, 1);
					dev_dbg(ccp->dev,
						 "Queue %d gets LSB %d\n",
						 i, bitno);
					अवरोध;
				पूर्ण
				biपंचांगap_clear(qlsb, bitno, 1);
				bitno = find_first_bit(qlsb, MAX_LSB_CNT);
			पूर्ण
			अगर (bitno >= MAX_LSB_CNT)
				वापस -EINVAL;
			n_lsbs--;
		पूर्ण
	पूर्ण
	वापस n_lsbs;
पूर्ण

/* For each queue, from the most- to least-स्थिरrained:
 * find an LSB that can be asचिन्हित to the queue. If there are N queues that
 * can only use M LSBs, where N > M, fail; otherwise, every queue will get a
 * dedicated LSB. Reमुख्यing LSB regions become a shared resource.
 * If we have fewer LSBs than queues, all LSB regions become shared resources.
 */
अटल पूर्णांक ccp_assign_lsbs(काष्ठा ccp_device *ccp)
अणु
	DECLARE_BITMAP(lsb_pub, MAX_LSB_CNT);
	DECLARE_BITMAP(qlsb, MAX_LSB_CNT);
	पूर्णांक n_lsbs = 0;
	पूर्णांक bitno;
	पूर्णांक i, lsb_cnt;
	पूर्णांक rc = 0;

	biपंचांगap_zero(lsb_pub, MAX_LSB_CNT);

	/* Create an aggregate biपंचांगap to get a total count of available LSBs */
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		biपंचांगap_or(lsb_pub,
			  lsb_pub, ccp->cmd_q[i].lsbmask,
			  MAX_LSB_CNT);

	n_lsbs = biपंचांगap_weight(lsb_pub, MAX_LSB_CNT);

	अगर (n_lsbs >= ccp->cmd_q_count) अणु
		/* We have enough LSBS to give every queue a निजी LSB.
		 * Brute क्रमce search to start with the queues that are more
		 * स्थिरrained in LSB choice. When an LSB is निजीly
		 * asचिन्हित, it is हटाओd from the खुला mask.
		 * This is an ugly N squared algorithm with some optimization.
		 */
		क्रम (lsb_cnt = 1;
		     n_lsbs && (lsb_cnt <= MAX_LSB_CNT);
		     lsb_cnt++) अणु
			rc = ccp_find_and_assign_lsb_to_q(ccp, lsb_cnt, n_lsbs,
							  lsb_pub);
			अगर (rc < 0)
				वापस -EINVAL;
			n_lsbs = rc;
		पूर्ण
	पूर्ण

	rc = 0;
	/* What's left of the LSBs, according to the खुला mask, now become
	 * shared. Any zero bits in the lsb_pub mask represent an LSB region
	 * that can't be used as a shared resource, so mark the LSB slots क्रम
	 * them as "in use".
	 */
	biपंचांगap_copy(qlsb, lsb_pub, MAX_LSB_CNT);

	bitno = find_first_zero_bit(qlsb, MAX_LSB_CNT);
	जबतक (bitno < MAX_LSB_CNT) अणु
		biपंचांगap_set(ccp->lsbmap, bitno * LSB_SIZE, LSB_SIZE);
		biपंचांगap_set(qlsb, bitno, 1);
		bitno = find_first_zero_bit(qlsb, MAX_LSB_CNT);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ccp5_disable_queue_पूर्णांकerrupts(काष्ठा ccp_device *ccp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		ioग_लिखो32(0x0, ccp->cmd_q[i].reg_पूर्णांक_enable);
पूर्ण

अटल व्योम ccp5_enable_queue_पूर्णांकerrupts(काष्ठा ccp_device *ccp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		ioग_लिखो32(SUPPORTED_INTERRUPTS, ccp->cmd_q[i].reg_पूर्णांक_enable);
पूर्ण

अटल व्योम ccp5_irq_bh(अचिन्हित दीर्घ data)
अणु
	काष्ठा ccp_device *ccp = (काष्ठा ccp_device *)data;
	u32 status;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		काष्ठा ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		status = ioपढ़ो32(cmd_q->reg_पूर्णांकerrupt_status);

		अगर (status) अणु
			cmd_q->पूर्णांक_status = status;
			cmd_q->q_status = ioपढ़ो32(cmd_q->reg_status);
			cmd_q->q_पूर्णांक_status = ioपढ़ो32(cmd_q->reg_पूर्णांक_status);

			/* On error, only save the first error value */
			अगर ((status & INT_ERROR) && !cmd_q->cmd_error)
				cmd_q->cmd_error = CMD_Q_ERROR(cmd_q->q_status);

			cmd_q->पूर्णांक_rcvd = 1;

			/* Acknowledge the पूर्णांकerrupt and wake the kthपढ़ो */
			ioग_लिखो32(status, cmd_q->reg_पूर्णांकerrupt_status);
			wake_up_पूर्णांकerruptible(&cmd_q->पूर्णांक_queue);
		पूर्ण
	पूर्ण
	ccp5_enable_queue_पूर्णांकerrupts(ccp);
पूर्ण

अटल irqवापस_t ccp5_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ccp_device *ccp = (काष्ठा ccp_device *)data;

	ccp5_disable_queue_पूर्णांकerrupts(ccp);
	ccp->total_पूर्णांकerrupts++;
	अगर (ccp->use_tasklet)
		tasklet_schedule(&ccp->irq_tasklet);
	अन्यथा
		ccp5_irq_bh((अचिन्हित दीर्घ)ccp);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ccp5_init(काष्ठा ccp_device *ccp)
अणु
	काष्ठा device *dev = ccp->dev;
	काष्ठा ccp_cmd_queue *cmd_q;
	काष्ठा dma_pool *dma_pool;
	अक्षर dma_pool_name[MAX_DMAPOOL_NAME_LEN];
	अचिन्हित पूर्णांक qmr, i;
	u64 status;
	u32 status_lo, status_hi;
	पूर्णांक ret;

	/* Find available queues */
	qmr = ioपढ़ो32(ccp->io_regs + Q_MASK_REG);
	/*
	 * Check क्रम a access to the रेजिस्टरs.  If this पढ़ो वापसs
	 * 0xffffffff, it's likely that the प्रणाली is running a broken
	 * BIOS which disallows access to the device. Stop here and fail
	 * the initialization (but not the load, as the PSP could get
	 * properly initialized).
	 */
	अगर (qmr == 0xffffffff) अणु
		dev_notice(dev, "ccp: unable to access the device: you might be running a broken BIOS.\n");
		वापस 1;
	पूर्ण

	क्रम (i = 0; (i < MAX_HW_QUEUES) && (ccp->cmd_q_count < ccp->max_q_count); i++) अणु
		अगर (!(qmr & (1 << i)))
			जारी;

		/* Allocate a dma pool क्रम this queue */
		snम_लिखो(dma_pool_name, माप(dma_pool_name), "%s_q%d",
			 ccp->name, i);
		dma_pool = dma_pool_create(dma_pool_name, dev,
					   CCP_DMAPOOL_MAX_SIZE,
					   CCP_DMAPOOL_ALIGN, 0);
		अगर (!dma_pool) अणु
			dev_err(dev, "unable to allocate dma pool\n");
			ret = -ENOMEM;
			जाओ e_pool;
		पूर्ण

		cmd_q = &ccp->cmd_q[ccp->cmd_q_count];
		ccp->cmd_q_count++;

		cmd_q->ccp = ccp;
		cmd_q->id = i;
		cmd_q->dma_pool = dma_pool;
		mutex_init(&cmd_q->q_mutex);

		/* Page alignment satisfies our needs क्रम N <= 128 */
		BUILD_BUG_ON(COMMANDS_PER_QUEUE > 128);
		cmd_q->qsize = Q_SIZE(Q_DESC_SIZE);
		cmd_q->qbase = dmam_alloc_coherent(dev, cmd_q->qsize,
						   &cmd_q->qbase_dma,
						   GFP_KERNEL);
		अगर (!cmd_q->qbase) अणु
			dev_err(dev, "unable to allocate command queue\n");
			ret = -ENOMEM;
			जाओ e_pool;
		पूर्ण

		cmd_q->qidx = 0;
		/* Preset some रेजिस्टर values and masks that are queue
		 * number dependent
		 */
		cmd_q->reg_control = ccp->io_regs +
				     CMD5_Q_STATUS_INCR * (i + 1);
		cmd_q->reg_tail_lo = cmd_q->reg_control + CMD5_Q_TAIL_LO_BASE;
		cmd_q->reg_head_lo = cmd_q->reg_control + CMD5_Q_HEAD_LO_BASE;
		cmd_q->reg_पूर्णांक_enable = cmd_q->reg_control +
					CMD5_Q_INT_ENABLE_BASE;
		cmd_q->reg_पूर्णांकerrupt_status = cmd_q->reg_control +
					      CMD5_Q_INTERRUPT_STATUS_BASE;
		cmd_q->reg_status = cmd_q->reg_control + CMD5_Q_STATUS_BASE;
		cmd_q->reg_पूर्णांक_status = cmd_q->reg_control +
					CMD5_Q_INT_STATUS_BASE;
		cmd_q->reg_dma_status = cmd_q->reg_control +
					CMD5_Q_DMA_STATUS_BASE;
		cmd_q->reg_dma_पढ़ो_status = cmd_q->reg_control +
					     CMD5_Q_DMA_READ_STATUS_BASE;
		cmd_q->reg_dma_ग_लिखो_status = cmd_q->reg_control +
					      CMD5_Q_DMA_WRITE_STATUS_BASE;

		init_रुकोqueue_head(&cmd_q->पूर्णांक_queue);

		dev_dbg(dev, "queue #%u available\n", i);
	पूर्ण

	अगर (ccp->cmd_q_count == 0) अणु
		dev_notice(dev, "no command queues available\n");
		ret = 1;
		जाओ e_pool;
	पूर्ण

	/* Turn off the queues and disable पूर्णांकerrupts until पढ़ोy */
	ccp5_disable_queue_पूर्णांकerrupts(ccp);
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		cmd_q->qcontrol = 0; /* Start with nothing */
		ioग_लिखो32(cmd_q->qcontrol, cmd_q->reg_control);

		ioपढ़ो32(cmd_q->reg_पूर्णांक_status);
		ioपढ़ो32(cmd_q->reg_status);

		/* Clear the पूर्णांकerrupt status */
		ioग_लिखो32(SUPPORTED_INTERRUPTS, cmd_q->reg_पूर्णांकerrupt_status);
	पूर्ण

	dev_dbg(dev, "Requesting an IRQ...\n");
	/* Request an irq */
	ret = sp_request_ccp_irq(ccp->sp, ccp5_irq_handler, ccp->name, ccp);
	अगर (ret) अणु
		dev_err(dev, "unable to allocate an IRQ\n");
		जाओ e_pool;
	पूर्ण
	/* Initialize the ISR tasklet */
	अगर (ccp->use_tasklet)
		tasklet_init(&ccp->irq_tasklet, ccp5_irq_bh,
			     (अचिन्हित दीर्घ)ccp);

	dev_dbg(dev, "Loading LSB map...\n");
	/* Copy the निजी LSB mask to the खुला रेजिस्टरs */
	status_lo = ioपढ़ो32(ccp->io_regs + LSB_PRIVATE_MASK_LO_OFFSET);
	status_hi = ioपढ़ो32(ccp->io_regs + LSB_PRIVATE_MASK_HI_OFFSET);
	ioग_लिखो32(status_lo, ccp->io_regs + LSB_PUBLIC_MASK_LO_OFFSET);
	ioग_लिखो32(status_hi, ccp->io_regs + LSB_PUBLIC_MASK_HI_OFFSET);
	status = ((u64)status_hi<<30) | (u64)status_lo;

	dev_dbg(dev, "Configuring virtual queues...\n");
	/* Configure size of each भव queue accessible to host */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		u32 dma_addr_lo;
		u32 dma_addr_hi;

		cmd_q = &ccp->cmd_q[i];

		cmd_q->qcontrol &= ~(CMD5_Q_SIZE << CMD5_Q_SHIFT);
		cmd_q->qcontrol |= QUEUE_SIZE_VAL << CMD5_Q_SHIFT;

		cmd_q->qdma_tail = cmd_q->qbase_dma;
		dma_addr_lo = low_address(cmd_q->qdma_tail);
		ioग_लिखो32((u32)dma_addr_lo, cmd_q->reg_tail_lo);
		ioग_लिखो32((u32)dma_addr_lo, cmd_q->reg_head_lo);

		dma_addr_hi = high_address(cmd_q->qdma_tail);
		cmd_q->qcontrol |= (dma_addr_hi << 16);
		ioग_लिखो32(cmd_q->qcontrol, cmd_q->reg_control);

		/* Find the LSB regions accessible to the queue */
		ccp_find_lsb_regions(cmd_q, status);
		cmd_q->lsb = -1; /* Unasचिन्हित value */
	पूर्ण

	dev_dbg(dev, "Assigning LSBs...\n");
	ret = ccp_assign_lsbs(ccp);
	अगर (ret) अणु
		dev_err(dev, "Unable to assign LSBs (%d)\n", ret);
		जाओ e_irq;
	पूर्ण

	/* Optimization: pre-allocate LSB slots क्रम each queue */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		ccp->cmd_q[i].sb_key = ccp_lsb_alloc(&ccp->cmd_q[i], 2);
		ccp->cmd_q[i].sb_ctx = ccp_lsb_alloc(&ccp->cmd_q[i], 2);
	पूर्ण

	dev_dbg(dev, "Starting threads...\n");
	/* Create a kthपढ़ो क्रम each queue */
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		काष्ठा task_काष्ठा *kthपढ़ो;

		cmd_q = &ccp->cmd_q[i];

		kthपढ़ो = kthपढ़ो_create(ccp_cmd_queue_thपढ़ो, cmd_q,
					 "%s-q%u", ccp->name, cmd_q->id);
		अगर (IS_ERR(kthपढ़ो)) अणु
			dev_err(dev, "error creating queue thread (%ld)\n",
				PTR_ERR(kthपढ़ो));
			ret = PTR_ERR(kthपढ़ो);
			जाओ e_kthपढ़ो;
		पूर्ण

		cmd_q->kthपढ़ो = kthपढ़ो;
		wake_up_process(kthपढ़ो);
	पूर्ण

	dev_dbg(dev, "Enabling interrupts...\n");
	ccp5_enable_queue_पूर्णांकerrupts(ccp);

	dev_dbg(dev, "Registering device...\n");
	/* Put this on the unit list to make it available */
	ccp_add_device(ccp);

	ret = ccp_रेजिस्टर_rng(ccp);
	अगर (ret)
		जाओ e_kthपढ़ो;

	/* Register the DMA engine support */
	ret = ccp_dmaengine_रेजिस्टर(ccp);
	अगर (ret)
		जाओ e_hwrng;

#अगर_घोषित CONFIG_CRYPTO_DEV_CCP_DEBUGFS
	/* Set up debugfs entries */
	ccp5_debugfs_setup(ccp);
#पूर्ण_अगर

	वापस 0;

e_hwrng:
	ccp_unरेजिस्टर_rng(ccp);

e_kthपढ़ो:
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		अगर (ccp->cmd_q[i].kthपढ़ो)
			kthपढ़ो_stop(ccp->cmd_q[i].kthपढ़ो);

e_irq:
	sp_मुक्त_ccp_irq(ccp->sp, ccp);

e_pool:
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		dma_pool_destroy(ccp->cmd_q[i].dma_pool);

	वापस ret;
पूर्ण

अटल व्योम ccp5_destroy(काष्ठा ccp_device *ccp)
अणु
	काष्ठा ccp_cmd_queue *cmd_q;
	काष्ठा ccp_cmd *cmd;
	अचिन्हित पूर्णांक i;

	/* Unरेजिस्टर the DMA engine */
	ccp_dmaengine_unरेजिस्टर(ccp);

	/* Unरेजिस्टर the RNG */
	ccp_unरेजिस्टर_rng(ccp);

	/* Remove this device from the list of available units first */
	ccp_del_device(ccp);

#अगर_घोषित CONFIG_CRYPTO_DEV_CCP_DEBUGFS
	/* We're in the process of tearing करोwn the entire driver;
	 * when all the devices are gone clean up debugfs
	 */
	अगर (ccp_present())
		ccp5_debugfs_destroy();
#पूर्ण_अगर

	/* Disable and clear पूर्णांकerrupts */
	ccp5_disable_queue_पूर्णांकerrupts(ccp);
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		/* Turn off the run bit */
		ioग_लिखो32(cmd_q->qcontrol & ~CMD5_Q_RUN, cmd_q->reg_control);

		/* Clear the पूर्णांकerrupt status */
		ioग_लिखो32(SUPPORTED_INTERRUPTS, cmd_q->reg_पूर्णांकerrupt_status);
		ioपढ़ो32(cmd_q->reg_पूर्णांक_status);
		ioपढ़ो32(cmd_q->reg_status);
	पूर्ण

	/* Stop the queue kthपढ़ोs */
	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		अगर (ccp->cmd_q[i].kthपढ़ो)
			kthपढ़ो_stop(ccp->cmd_q[i].kthपढ़ो);

	sp_मुक्त_ccp_irq(ccp->sp, ccp);

	/* Flush the cmd and backlog queue */
	जबतक (!list_empty(&ccp->cmd)) अणु
		/* Invoke the callback directly with an error code */
		cmd = list_first_entry(&ccp->cmd, काष्ठा ccp_cmd, entry);
		list_del(&cmd->entry);
		cmd->callback(cmd->data, -ENODEV);
	पूर्ण
	जबतक (!list_empty(&ccp->backlog)) अणु
		/* Invoke the callback directly with an error code */
		cmd = list_first_entry(&ccp->backlog, काष्ठा ccp_cmd, entry);
		list_del(&cmd->entry);
		cmd->callback(cmd->data, -ENODEV);
	पूर्ण
पूर्ण

अटल व्योम ccp5_config(काष्ठा ccp_device *ccp)
अणु
	/* Public side */
	ioग_लिखो32(0x0, ccp->io_regs + CMD5_REQID_CONFIG_OFFSET);
पूर्ण

अटल व्योम ccp5other_config(काष्ठा ccp_device *ccp)
अणु
	पूर्णांक i;
	u32 rnd;

	/* We own all of the queues on the NTB CCP */

	ioग_लिखो32(0x00012D57, ccp->io_regs + CMD5_TRNG_CTL_OFFSET);
	ioग_लिखो32(0x00000003, ccp->io_regs + CMD5_CONFIG_0_OFFSET);
	क्रम (i = 0; i < 12; i++) अणु
		rnd = ioपढ़ो32(ccp->io_regs + TRNG_OUT_REG);
		ioग_लिखो32(rnd, ccp->io_regs + CMD5_AES_MASK_OFFSET);
	पूर्ण

	ioग_लिखो32(0x0000001F, ccp->io_regs + CMD5_QUEUE_MASK_OFFSET);
	ioग_लिखो32(0x00005B6D, ccp->io_regs + CMD5_QUEUE_PRIO_OFFSET);
	ioग_लिखो32(0x00000000, ccp->io_regs + CMD5_CMD_TIMEOUT_OFFSET);

	ioग_लिखो32(0x3FFFFFFF, ccp->io_regs + LSB_PRIVATE_MASK_LO_OFFSET);
	ioग_लिखो32(0x000003FF, ccp->io_regs + LSB_PRIVATE_MASK_HI_OFFSET);

	ioग_लिखो32(0x00108823, ccp->io_regs + CMD5_CLK_GATE_CTL_OFFSET);

	ccp5_config(ccp);
पूर्ण

/* Version 5 adds some function, but is essentially the same as v5 */
अटल स्थिर काष्ठा ccp_actions ccp5_actions = अणु
	.aes = ccp5_perक्रमm_aes,
	.xts_aes = ccp5_perक्रमm_xts_aes,
	.sha = ccp5_perक्रमm_sha,
	.des3 = ccp5_perक्रमm_des3,
	.rsa = ccp5_perक्रमm_rsa,
	.passthru = ccp5_perक्रमm_passthru,
	.ecc = ccp5_perक्रमm_ecc,
	.sballoc = ccp_lsb_alloc,
	.sbमुक्त = ccp_lsb_मुक्त,
	.init = ccp5_init,
	.destroy = ccp5_destroy,
	.get_मुक्त_slots = ccp5_get_मुक्त_slots,
पूर्ण;

स्थिर काष्ठा ccp_vdata ccpv5a = अणु
	.version = CCP_VERSION(5, 0),
	.setup = ccp5_config,
	.perक्रमm = &ccp5_actions,
	.offset = 0x0,
	.rsamax = CCP5_RSA_MAX_WIDTH,
पूर्ण;

स्थिर काष्ठा ccp_vdata ccpv5b = अणु
	.version = CCP_VERSION(5, 0),
	.dma_chan_attr = DMA_PRIVATE,
	.setup = ccp5other_config,
	.perक्रमm = &ccp5_actions,
	.offset = 0x0,
	.rsamax = CCP5_RSA_MAX_WIDTH,
पूर्ण;
