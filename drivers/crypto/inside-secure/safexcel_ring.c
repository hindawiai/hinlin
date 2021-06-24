<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Marvell
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>

#समावेश "safexcel.h"

पूर्णांक safexcel_init_ring_descriptors(काष्ठा safexcel_crypto_priv *priv,
				   काष्ठा safexcel_desc_ring *cdr,
				   काष्ठा safexcel_desc_ring *rdr)
अणु
	पूर्णांक i;
	काष्ठा safexcel_command_desc *cdesc;
	dma_addr_t atok;

	/* Actual command descriptor ring */
	cdr->offset = priv->config.cd_offset;
	cdr->base = dmam_alloc_coherent(priv->dev,
					cdr->offset * EIP197_DEFAULT_RING_SIZE,
					&cdr->base_dma, GFP_KERNEL);
	अगर (!cdr->base)
		वापस -ENOMEM;
	cdr->ग_लिखो = cdr->base;
	cdr->base_end = cdr->base + cdr->offset * (EIP197_DEFAULT_RING_SIZE - 1);
	cdr->पढ़ो = cdr->base;

	/* Command descriptor shaकरोw ring क्रम storing additional token data */
	cdr->shoffset = priv->config.cdsh_offset;
	cdr->shbase = dmam_alloc_coherent(priv->dev,
					  cdr->shoffset *
					  EIP197_DEFAULT_RING_SIZE,
					  &cdr->shbase_dma, GFP_KERNEL);
	अगर (!cdr->shbase)
		वापस -ENOMEM;
	cdr->shग_लिखो = cdr->shbase;
	cdr->shbase_end = cdr->shbase + cdr->shoffset *
					(EIP197_DEFAULT_RING_SIZE - 1);

	/*
	 * Populate command descriptors with physical poपूर्णांकers to shaकरोw descs.
	 * Note that we only need to करो this once अगर we करोn't overग_लिखो them.
	 */
	cdesc = cdr->base;
	atok = cdr->shbase_dma;
	क्रम (i = 0; i < EIP197_DEFAULT_RING_SIZE; i++) अणु
		cdesc->atok_lo = lower_32_bits(atok);
		cdesc->atok_hi = upper_32_bits(atok);
		cdesc = (व्योम *)cdesc + cdr->offset;
		atok += cdr->shoffset;
	पूर्ण

	rdr->offset = priv->config.rd_offset;
	/* Use shoffset क्रम result token offset here */
	rdr->shoffset = priv->config.res_offset;
	rdr->base = dmam_alloc_coherent(priv->dev,
					rdr->offset * EIP197_DEFAULT_RING_SIZE,
					&rdr->base_dma, GFP_KERNEL);
	अगर (!rdr->base)
		वापस -ENOMEM;
	rdr->ग_लिखो = rdr->base;
	rdr->base_end = rdr->base + rdr->offset  * (EIP197_DEFAULT_RING_SIZE - 1);
	rdr->पढ़ो = rdr->base;

	वापस 0;
पूर्ण

अंतरभूत पूर्णांक safexcel_select_ring(काष्ठा safexcel_crypto_priv *priv)
अणु
	वापस (atomic_inc_वापस(&priv->ring_used) % priv->config.rings);
पूर्ण

अटल व्योम *safexcel_ring_next_cwptr(काष्ठा safexcel_crypto_priv *priv,
				     काष्ठा safexcel_desc_ring *ring,
				     bool first,
				     काष्ठा safexcel_token **atoken)
अणु
	व्योम *ptr = ring->ग_लिखो;

	अगर (first)
		*atoken = ring->shग_लिखो;

	अगर ((ring->ग_लिखो == ring->पढ़ो - ring->offset) ||
	    (ring->पढ़ो == ring->base && ring->ग_लिखो == ring->base_end))
		वापस ERR_PTR(-ENOMEM);

	अगर (ring->ग_लिखो == ring->base_end) अणु
		ring->ग_लिखो = ring->base;
		ring->shग_लिखो = ring->shbase;
	पूर्ण अन्यथा अणु
		ring->ग_लिखो += ring->offset;
		ring->shग_लिखो += ring->shoffset;
	पूर्ण

	वापस ptr;
पूर्ण

अटल व्योम *safexcel_ring_next_rwptr(काष्ठा safexcel_crypto_priv *priv,
				     काष्ठा safexcel_desc_ring *ring,
				     काष्ठा result_data_desc **rtoken)
अणु
	व्योम *ptr = ring->ग_लिखो;

	/* Result token at relative offset shoffset */
	*rtoken = ring->ग_लिखो + ring->shoffset;

	अगर ((ring->ग_लिखो == ring->पढ़ो - ring->offset) ||
	    (ring->पढ़ो == ring->base && ring->ग_लिखो == ring->base_end))
		वापस ERR_PTR(-ENOMEM);

	अगर (ring->ग_लिखो == ring->base_end)
		ring->ग_लिखो = ring->base;
	अन्यथा
		ring->ग_लिखो += ring->offset;

	वापस ptr;
पूर्ण

व्योम *safexcel_ring_next_rptr(काष्ठा safexcel_crypto_priv *priv,
			      काष्ठा safexcel_desc_ring *ring)
अणु
	व्योम *ptr = ring->पढ़ो;

	अगर (ring->ग_लिखो == ring->पढ़ो)
		वापस ERR_PTR(-ENOENT);

	अगर (ring->पढ़ो == ring->base_end)
		ring->पढ़ो = ring->base;
	अन्यथा
		ring->पढ़ो += ring->offset;

	वापस ptr;
पूर्ण

अंतरभूत व्योम *safexcel_ring_curr_rptr(काष्ठा safexcel_crypto_priv *priv,
				     पूर्णांक ring)
अणु
	काष्ठा safexcel_desc_ring *rdr = &priv->ring[ring].rdr;

	वापस rdr->पढ़ो;
पूर्ण

अंतरभूत पूर्णांक safexcel_ring_first_rdr_index(काष्ठा safexcel_crypto_priv *priv,
					 पूर्णांक ring)
अणु
	काष्ठा safexcel_desc_ring *rdr = &priv->ring[ring].rdr;

	वापस (rdr->पढ़ो - rdr->base) / rdr->offset;
पूर्ण

अंतरभूत पूर्णांक safexcel_ring_rdr_rdesc_index(काष्ठा safexcel_crypto_priv *priv,
					 पूर्णांक ring,
					 काष्ठा safexcel_result_desc *rdesc)
अणु
	काष्ठा safexcel_desc_ring *rdr = &priv->ring[ring].rdr;

	वापस ((व्योम *)rdesc - rdr->base) / rdr->offset;
पूर्ण

व्योम safexcel_ring_rollback_wptr(काष्ठा safexcel_crypto_priv *priv,
				 काष्ठा safexcel_desc_ring *ring)
अणु
	अगर (ring->ग_लिखो == ring->पढ़ो)
		वापस;

	अगर (ring->ग_लिखो == ring->base) अणु
		ring->ग_लिखो = ring->base_end;
		ring->shग_लिखो = ring->shbase_end;
	पूर्ण अन्यथा अणु
		ring->ग_लिखो -= ring->offset;
		ring->shग_लिखो -= ring->shoffset;
	पूर्ण
पूर्ण

काष्ठा safexcel_command_desc *safexcel_add_cdesc(काष्ठा safexcel_crypto_priv *priv,
						 पूर्णांक ring_id,
						 bool first, bool last,
						 dma_addr_t data, u32 data_len,
						 u32 full_data_len,
						 dma_addr_t context,
						 काष्ठा safexcel_token **atoken)
अणु
	काष्ठा safexcel_command_desc *cdesc;

	cdesc = safexcel_ring_next_cwptr(priv, &priv->ring[ring_id].cdr,
					 first, atoken);
	अगर (IS_ERR(cdesc))
		वापस cdesc;

	cdesc->particle_size = data_len;
	cdesc->rsvd0 = 0;
	cdesc->last_seg = last;
	cdesc->first_seg = first;
	cdesc->additional_cdata_size = 0;
	cdesc->rsvd1 = 0;
	cdesc->data_lo = lower_32_bits(data);
	cdesc->data_hi = upper_32_bits(data);

	अगर (first) अणु
		/*
		 * Note that the length here MUST be >0 or अन्यथा the EIP(1)97
		 * may hang. Newer EIP197 firmware actually incorporates this
		 * fix alपढ़ोy, but that करोesn't help the EIP97 and we may
		 * also be running older firmware.
		 */
		cdesc->control_data.packet_length = full_data_len ?: 1;
		cdesc->control_data.options = EIP197_OPTION_MAGIC_VALUE |
					      EIP197_OPTION_64BIT_CTX |
					      EIP197_OPTION_CTX_CTRL_IN_CMD |
					      EIP197_OPTION_RC_AUTO;
		cdesc->control_data.type = EIP197_TYPE_BCLA;
		cdesc->control_data.context_lo = lower_32_bits(context) |
						 EIP197_CONTEXT_SMALL;
		cdesc->control_data.context_hi = upper_32_bits(context);
	पूर्ण

	वापस cdesc;
पूर्ण

काष्ठा safexcel_result_desc *safexcel_add_rdesc(काष्ठा safexcel_crypto_priv *priv,
						पूर्णांक ring_id,
						bool first, bool last,
						dma_addr_t data, u32 len)
अणु
	काष्ठा safexcel_result_desc *rdesc;
	काष्ठा result_data_desc *rtoken;

	rdesc = safexcel_ring_next_rwptr(priv, &priv->ring[ring_id].rdr,
					 &rtoken);
	अगर (IS_ERR(rdesc))
		वापस rdesc;

	rdesc->particle_size = len;
	rdesc->rsvd0 = 0;
	rdesc->descriptor_overflow = 1; /* assume error */
	rdesc->buffer_overflow = 1;     /* assume error */
	rdesc->last_seg = last;
	rdesc->first_seg = first;
	rdesc->result_size = EIP197_RD64_RESULT_SIZE;
	rdesc->rsvd1 = 0;
	rdesc->data_lo = lower_32_bits(data);
	rdesc->data_hi = upper_32_bits(data);

	/* Clear length in result token */
	rtoken->packet_length = 0;
	/* Assume errors - HW will clear अगर not the हाल */
	rtoken->error_code = 0x7fff;

	वापस rdesc;
पूर्ण
