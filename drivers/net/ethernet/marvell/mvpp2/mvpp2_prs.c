<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Header Parser helpers क्रम Marvell PPv2 Network Controller
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <uapi/linux/ppp_defs.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश "mvpp2.h"
#समावेश "mvpp2_prs.h"

/* Update parser tcam and sram hw entries */
अटल पूर्णांक mvpp2_prs_hw_ग_लिखो(काष्ठा mvpp2 *priv, काष्ठा mvpp2_prs_entry *pe)
अणु
	पूर्णांक i;

	अगर (pe->index > MVPP2_PRS_TCAM_SRAM_SIZE - 1)
		वापस -EINVAL;

	/* Clear entry invalidation bit */
	pe->tcam[MVPP2_PRS_TCAM_INV_WORD] &= ~MVPP2_PRS_TCAM_INV_MASK;

	/* Write sram index - indirect access */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_SRAM_IDX_REG, pe->index);
	क्रम (i = 0; i < MVPP2_PRS_SRAM_WORDS; i++)
		mvpp2_ग_लिखो(priv, MVPP2_PRS_SRAM_DATA_REG(i), pe->sram[i]);

	/* Write tcam index - indirect access */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_IDX_REG, pe->index);
	क्रम (i = 0; i < MVPP2_PRS_TCAM_WORDS; i++)
		mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_DATA_REG(i), pe->tcam[i]);

	वापस 0;
पूर्ण

/* Initialize tcam entry from hw */
पूर्णांक mvpp2_prs_init_from_hw(काष्ठा mvpp2 *priv, काष्ठा mvpp2_prs_entry *pe,
			   पूर्णांक tid)
अणु
	पूर्णांक i;

	अगर (tid > MVPP2_PRS_TCAM_SRAM_SIZE - 1)
		वापस -EINVAL;

	स_रखो(pe, 0, माप(*pe));
	pe->index = tid;

	/* Write tcam index - indirect access */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_IDX_REG, pe->index);

	pe->tcam[MVPP2_PRS_TCAM_INV_WORD] = mvpp2_पढ़ो(priv,
			      MVPP2_PRS_TCAM_DATA_REG(MVPP2_PRS_TCAM_INV_WORD));
	अगर (pe->tcam[MVPP2_PRS_TCAM_INV_WORD] & MVPP2_PRS_TCAM_INV_MASK)
		वापस MVPP2_PRS_TCAM_ENTRY_INVALID;

	क्रम (i = 0; i < MVPP2_PRS_TCAM_WORDS; i++)
		pe->tcam[i] = mvpp2_पढ़ो(priv, MVPP2_PRS_TCAM_DATA_REG(i));

	/* Write sram index - indirect access */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_SRAM_IDX_REG, pe->index);
	क्रम (i = 0; i < MVPP2_PRS_SRAM_WORDS; i++)
		pe->sram[i] = mvpp2_पढ़ो(priv, MVPP2_PRS_SRAM_DATA_REG(i));

	वापस 0;
पूर्ण

/* Invalidate tcam hw entry */
अटल व्योम mvpp2_prs_hw_inv(काष्ठा mvpp2 *priv, पूर्णांक index)
अणु
	/* Write index - indirect access */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_IDX_REG, index);
	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_DATA_REG(MVPP2_PRS_TCAM_INV_WORD),
		    MVPP2_PRS_TCAM_INV_MASK);
पूर्ण

/* Enable shaकरोw table entry and set its lookup ID */
अटल व्योम mvpp2_prs_shaकरोw_set(काष्ठा mvpp2 *priv, पूर्णांक index, पूर्णांक lu)
अणु
	priv->prs_shaकरोw[index].valid = true;
	priv->prs_shaकरोw[index].lu = lu;
पूर्ण

/* Update ri fields in shaकरोw table entry */
अटल व्योम mvpp2_prs_shaकरोw_ri_set(काष्ठा mvpp2 *priv, पूर्णांक index,
				    अचिन्हित पूर्णांक ri, अचिन्हित पूर्णांक ri_mask)
अणु
	priv->prs_shaकरोw[index].ri_mask = ri_mask;
	priv->prs_shaकरोw[index].ri = ri;
पूर्ण

/* Update lookup field in tcam sw entry */
अटल व्योम mvpp2_prs_tcam_lu_set(काष्ठा mvpp2_prs_entry *pe, अचिन्हित पूर्णांक lu)
अणु
	pe->tcam[MVPP2_PRS_TCAM_LU_WORD] &= ~MVPP2_PRS_TCAM_LU(MVPP2_PRS_LU_MASK);
	pe->tcam[MVPP2_PRS_TCAM_LU_WORD] &= ~MVPP2_PRS_TCAM_LU_EN(MVPP2_PRS_LU_MASK);
	pe->tcam[MVPP2_PRS_TCAM_LU_WORD] |= MVPP2_PRS_TCAM_LU(lu & MVPP2_PRS_LU_MASK);
	pe->tcam[MVPP2_PRS_TCAM_LU_WORD] |= MVPP2_PRS_TCAM_LU_EN(MVPP2_PRS_LU_MASK);
पूर्ण

/* Update mask क्रम single port in tcam sw entry */
अटल व्योम mvpp2_prs_tcam_port_set(काष्ठा mvpp2_prs_entry *pe,
				    अचिन्हित पूर्णांक port, bool add)
अणु
	अगर (add)
		pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] &= ~MVPP2_PRS_TCAM_PORT_EN(BIT(port));
	अन्यथा
		pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] |= MVPP2_PRS_TCAM_PORT_EN(BIT(port));
पूर्ण

/* Update port map in tcam sw entry */
अटल व्योम mvpp2_prs_tcam_port_map_set(काष्ठा mvpp2_prs_entry *pe,
					अचिन्हित पूर्णांक ports)
अणु
	pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] &= ~MVPP2_PRS_TCAM_PORT(MVPP2_PRS_PORT_MASK);
	pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] &= ~MVPP2_PRS_TCAM_PORT_EN(MVPP2_PRS_PORT_MASK);
	pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] |= MVPP2_PRS_TCAM_PORT_EN(~ports & MVPP2_PRS_PORT_MASK);
पूर्ण

/* Obtain port map from tcam sw entry */
अचिन्हित पूर्णांक mvpp2_prs_tcam_port_map_get(काष्ठा mvpp2_prs_entry *pe)
अणु
	वापस (~pe->tcam[MVPP2_PRS_TCAM_PORT_WORD] >> 24) & MVPP2_PRS_PORT_MASK;
पूर्ण

/* Set byte of data and its enable bits in tcam sw entry */
अटल व्योम mvpp2_prs_tcam_data_byte_set(काष्ठा mvpp2_prs_entry *pe,
					 अचिन्हित पूर्णांक offs, अचिन्हित अक्षर byte,
					 अचिन्हित अक्षर enable)
अणु
	पूर्णांक pos = MVPP2_PRS_BYTE_IN_WORD(offs) * BITS_PER_BYTE;

	pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] &= ~(0xff << pos);
	pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] &= ~(MVPP2_PRS_TCAM_EN(0xff) << pos);
	pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] |= byte << pos;
	pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] |= MVPP2_PRS_TCAM_EN(enable << pos);
पूर्ण

/* Get byte of data and its enable bits from tcam sw entry */
व्योम mvpp2_prs_tcam_data_byte_get(काष्ठा mvpp2_prs_entry *pe,
				  अचिन्हित पूर्णांक offs, अचिन्हित अक्षर *byte,
				  अचिन्हित अक्षर *enable)
अणु
	पूर्णांक pos = MVPP2_PRS_BYTE_IN_WORD(offs) * BITS_PER_BYTE;

	*byte = (pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] >> pos) & 0xff;
	*enable = (pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] >> (pos + 16)) & 0xff;
पूर्ण

/* Compare tcam data bytes with a pattern */
अटल bool mvpp2_prs_tcam_data_cmp(काष्ठा mvpp2_prs_entry *pe, पूर्णांक offs,
				    u16 data)
अणु
	u16 tcam_data;

	tcam_data = pe->tcam[MVPP2_PRS_BYTE_TO_WORD(offs)] & 0xffff;
	वापस tcam_data == data;
पूर्ण

/* Update ai bits in tcam sw entry */
अटल व्योम mvpp2_prs_tcam_ai_update(काष्ठा mvpp2_prs_entry *pe,
				     अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक enable)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MVPP2_PRS_AI_BITS; i++) अणु
		अगर (!(enable & BIT(i)))
			जारी;

		अगर (bits & BIT(i))
			pe->tcam[MVPP2_PRS_TCAM_AI_WORD] |= BIT(i);
		अन्यथा
			pe->tcam[MVPP2_PRS_TCAM_AI_WORD] &= ~BIT(i);
	पूर्ण

	pe->tcam[MVPP2_PRS_TCAM_AI_WORD] |= MVPP2_PRS_TCAM_AI_EN(enable);
पूर्ण

/* Get ai bits from tcam sw entry */
अटल पूर्णांक mvpp2_prs_tcam_ai_get(काष्ठा mvpp2_prs_entry *pe)
अणु
	वापस pe->tcam[MVPP2_PRS_TCAM_AI_WORD] & MVPP2_PRS_AI_MASK;
पूर्ण

/* Set ethertype in tcam sw entry */
अटल व्योम mvpp2_prs_match_etype(काष्ठा mvpp2_prs_entry *pe, पूर्णांक offset,
				  अचिन्हित लघु ethertype)
अणु
	mvpp2_prs_tcam_data_byte_set(pe, offset + 0, ethertype >> 8, 0xff);
	mvpp2_prs_tcam_data_byte_set(pe, offset + 1, ethertype & 0xff, 0xff);
पूर्ण

/* Set vid in tcam sw entry */
अटल व्योम mvpp2_prs_match_vid(काष्ठा mvpp2_prs_entry *pe, पूर्णांक offset,
				अचिन्हित लघु vid)
अणु
	mvpp2_prs_tcam_data_byte_set(pe, offset + 0, (vid & 0xf00) >> 8, 0xf);
	mvpp2_prs_tcam_data_byte_set(pe, offset + 1, vid & 0xff, 0xff);
पूर्ण

/* Set bits in sram sw entry */
अटल व्योम mvpp2_prs_sram_bits_set(काष्ठा mvpp2_prs_entry *pe, पूर्णांक bit_num,
				    u32 val)
अणु
	pe->sram[MVPP2_BIT_TO_WORD(bit_num)] |= (val << (MVPP2_BIT_IN_WORD(bit_num)));
पूर्ण

/* Clear bits in sram sw entry */
अटल व्योम mvpp2_prs_sram_bits_clear(काष्ठा mvpp2_prs_entry *pe, पूर्णांक bit_num,
				      u32 val)
अणु
	pe->sram[MVPP2_BIT_TO_WORD(bit_num)] &= ~(val << (MVPP2_BIT_IN_WORD(bit_num)));
पूर्ण

/* Update ri bits in sram sw entry */
अटल व्योम mvpp2_prs_sram_ri_update(काष्ठा mvpp2_prs_entry *pe,
				     अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MVPP2_PRS_SRAM_RI_CTRL_BITS; i++) अणु
		अगर (!(mask & BIT(i)))
			जारी;

		अगर (bits & BIT(i))
			mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_RI_OFFS + i,
						1);
		अन्यथा
			mvpp2_prs_sram_bits_clear(pe,
						  MVPP2_PRS_SRAM_RI_OFFS + i,
						  1);

		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_RI_CTRL_OFFS + i, 1);
	पूर्ण
पूर्ण

/* Obtain ri bits from sram sw entry */
अटल पूर्णांक mvpp2_prs_sram_ri_get(काष्ठा mvpp2_prs_entry *pe)
अणु
	वापस pe->sram[MVPP2_PRS_SRAM_RI_WORD];
पूर्ण

/* Update ai bits in sram sw entry */
अटल व्योम mvpp2_prs_sram_ai_update(काष्ठा mvpp2_prs_entry *pe,
				     अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MVPP2_PRS_SRAM_AI_CTRL_BITS; i++) अणु
		अगर (!(mask & BIT(i)))
			जारी;

		अगर (bits & BIT(i))
			mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_AI_OFFS + i,
						1);
		अन्यथा
			mvpp2_prs_sram_bits_clear(pe,
						  MVPP2_PRS_SRAM_AI_OFFS + i,
						  1);

		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_AI_CTRL_OFFS + i, 1);
	पूर्ण
पूर्ण

/* Read ai bits from sram sw entry */
अटल पूर्णांक mvpp2_prs_sram_ai_get(काष्ठा mvpp2_prs_entry *pe)
अणु
	u8 bits;
	/* ai is stored on bits 90->97; so it spपढ़ोs across two u32 */
	पूर्णांक ai_off = MVPP2_BIT_TO_WORD(MVPP2_PRS_SRAM_AI_OFFS);
	पूर्णांक ai_shअगरt = MVPP2_BIT_IN_WORD(MVPP2_PRS_SRAM_AI_OFFS);

	bits = (pe->sram[ai_off] >> ai_shअगरt) |
	       (pe->sram[ai_off + 1] << (32 - ai_shअगरt));

	वापस bits;
पूर्ण

/* In sram sw entry set lookup ID field of the tcam key to be used in the next
 * lookup पूर्णांकeration
 */
अटल व्योम mvpp2_prs_sram_next_lu_set(काष्ठा mvpp2_prs_entry *pe,
				       अचिन्हित पूर्णांक lu)
अणु
	पूर्णांक sram_next_off = MVPP2_PRS_SRAM_NEXT_LU_OFFS;

	mvpp2_prs_sram_bits_clear(pe, sram_next_off,
				  MVPP2_PRS_SRAM_NEXT_LU_MASK);
	mvpp2_prs_sram_bits_set(pe, sram_next_off, lu);
पूर्ण

/* In the sram sw entry set sign and value of the next lookup offset
 * and the offset value generated to the classअगरier
 */
अटल व्योम mvpp2_prs_sram_shअगरt_set(काष्ठा mvpp2_prs_entry *pe, पूर्णांक shअगरt,
				     अचिन्हित पूर्णांक op)
अणु
	/* Set sign */
	अगर (shअगरt < 0) अणु
		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_SHIFT_SIGN_BIT, 1);
		shअगरt = 0 - shअगरt;
	पूर्ण अन्यथा अणु
		mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_SHIFT_SIGN_BIT, 1);
	पूर्ण

	/* Set value */
	pe->sram[MVPP2_BIT_TO_WORD(MVPP2_PRS_SRAM_SHIFT_OFFS)] |=
		shअगरt & MVPP2_PRS_SRAM_SHIFT_MASK;

	/* Reset and set operation */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS,
				  MVPP2_PRS_SRAM_OP_SEL_SHIFT_MASK);
	mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS, op);

	/* Set base offset as current */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_BASE_OFFS, 1);
पूर्ण

/* In the sram sw entry set sign and value of the user defined offset
 * generated to the classअगरier
 */
अटल व्योम mvpp2_prs_sram_offset_set(काष्ठा mvpp2_prs_entry *pe,
				      अचिन्हित पूर्णांक type, पूर्णांक offset,
				      अचिन्हित पूर्णांक op)
अणु
	/* Set sign */
	अगर (offset < 0) अणु
		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_UDF_SIGN_BIT, 1);
		offset = 0 - offset;
	पूर्ण अन्यथा अणु
		mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_UDF_SIGN_BIT, 1);
	पूर्ण

	/* Set value */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_UDF_OFFS,
				  MVPP2_PRS_SRAM_UDF_MASK);
	mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_UDF_OFFS,
				offset & MVPP2_PRS_SRAM_UDF_MASK);

	/* Set offset type */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_UDF_TYPE_OFFS,
				  MVPP2_PRS_SRAM_UDF_TYPE_MASK);
	mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_UDF_TYPE_OFFS, type);

	/* Set offset operation */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_UDF_OFFS,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_MASK);
	mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_OP_SEL_UDF_OFFS,
				op & MVPP2_PRS_SRAM_OP_SEL_UDF_MASK);

	/* Set base offset as current */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_BASE_OFFS, 1);
पूर्ण

/* Find parser flow entry */
अटल पूर्णांक mvpp2_prs_flow_find(काष्ठा mvpp2 *priv, पूर्णांक flow)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	/* Go through the all entires with MVPP2_PRS_LU_FLOWS */
	क्रम (tid = MVPP2_PRS_TCAM_SRAM_SIZE - 1; tid >= 0; tid--) अणु
		u8 bits;

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_FLOWS)
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);
		bits = mvpp2_prs_sram_ai_get(&pe);

		/* Sram store classअगरication lookup ID in AI bits [5:0] */
		अगर ((bits & MVPP2_PRS_FLOW_ID_MASK) == flow)
			वापस tid;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Return first मुक्त tcam index, seeking from start to end */
अटल पूर्णांक mvpp2_prs_tcam_first_मुक्त(काष्ठा mvpp2 *priv, अचिन्हित अक्षर start,
				     अचिन्हित अक्षर end)
अणु
	पूर्णांक tid;

	अगर (start > end)
		swap(start, end);

	अगर (end >= MVPP2_PRS_TCAM_SRAM_SIZE)
		end = MVPP2_PRS_TCAM_SRAM_SIZE - 1;

	क्रम (tid = start; tid <= end; tid++) अणु
		अगर (!priv->prs_shaकरोw[tid].valid)
			वापस tid;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Drop flow control छोड़ो frames */
अटल व्योम mvpp2_prs_drop_fc(काष्ठा mvpp2 *priv)
अणु
	अचिन्हित अक्षर da[ETH_ALEN] = अणु 0x01, 0x80, 0xC2, 0x00, 0x00, 0x01 पूर्ण;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित पूर्णांक len;

	स_रखो(&pe, 0, माप(pe));

	/* For all ports - drop flow control frames */
	pe.index = MVPP2_PE_FC_DROP;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);

	/* Set match on DA */
	len = ETH_ALEN;
	जबतक (len--)
		mvpp2_prs_tcam_data_byte_set(&pe, len, da[len], 0xff);

	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_DROP_MASK);

	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

	/* Mask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Enable/disable dropping all mac da's */
अटल व्योम mvpp2_prs_mac_drop_all_set(काष्ठा mvpp2 *priv, पूर्णांक port, bool add)
अणु
	काष्ठा mvpp2_prs_entry pe;

	अगर (priv->prs_shaकरोw[MVPP2_PE_DROP_ALL].valid) अणु
		/* Entry exist - update port only */
		mvpp2_prs_init_from_hw(priv, &pe, MVPP2_PE_DROP_ALL);
	पूर्ण अन्यथा अणु
		/* Entry करोesn't exist - create new */
		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);
		pe.index = MVPP2_PE_DROP_ALL;

		/* Non-promiscuous mode क्रम all ports - DROP unknown packets */
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
					 MVPP2_PRS_RI_DROP_MASK);

		mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

		/* Update shaकरोw table */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);
	पूर्ण

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Set port to unicast or multicast promiscuous mode */
व्योम mvpp2_prs_mac_promisc_set(काष्ठा mvpp2 *priv, पूर्णांक port,
			       क्रमागत mvpp2_prs_l2_cast l2_cast, bool add)
अणु
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित अक्षर cast_match;
	अचिन्हित पूर्णांक ri;
	पूर्णांक tid;

	अगर (l2_cast == MVPP2_PRS_L2_UNI_CAST) अणु
		cast_match = MVPP2_PRS_UCAST_VAL;
		tid = MVPP2_PE_MAC_UC_PROMISCUOUS;
		ri = MVPP2_PRS_RI_L2_UCAST;
	पूर्ण अन्यथा अणु
		cast_match = MVPP2_PRS_MCAST_VAL;
		tid = MVPP2_PE_MAC_MC_PROMISCUOUS;
		ri = MVPP2_PRS_RI_L2_MCAST;
	पूर्ण

	/* promiscuous mode - Accept unknown unicast or multicast packets */
	अगर (priv->prs_shaकरोw[tid].valid) अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण अन्यथा अणु
		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);
		pe.index = tid;

		/* Continue - set next lookup */
		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_DSA);

		/* Set result info bits */
		mvpp2_prs_sram_ri_update(&pe, ri, MVPP2_PRS_RI_L2_CAST_MASK);

		/* Match UC or MC addresses */
		mvpp2_prs_tcam_data_byte_set(&pe, 0, cast_match,
					     MVPP2_PRS_CAST_MASK);

		/* Shअगरt to ethertype */
		mvpp2_prs_sram_shअगरt_set(&pe, 2 * ETH_ALEN,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);

		/* Update shaकरोw table */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);
	पूर्ण

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Set entry क्रम dsa packets */
अटल व्योम mvpp2_prs_dsa_tag_set(काष्ठा mvpp2 *priv, पूर्णांक port, bool add,
				  bool tagged, bool extend)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid, shअगरt;

	अगर (extend) अणु
		tid = tagged ? MVPP2_PE_EDSA_TAGGED : MVPP2_PE_EDSA_UNTAGGED;
		shअगरt = 8;
	पूर्ण अन्यथा अणु
		tid = tagged ? MVPP2_PE_DSA_TAGGED : MVPP2_PE_DSA_UNTAGGED;
		shअगरt = 4;
	पूर्ण

	अगर (priv->prs_shaकरोw[tid].valid) अणु
		/* Entry exist - update port only */
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण अन्यथा अणु
		/* Entry करोesn't exist - create new */
		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_DSA);
		pe.index = tid;

		/* Update shaकरोw table */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_DSA);

		अगर (tagged) अणु
			/* Set tagged bit in DSA tag */
			mvpp2_prs_tcam_data_byte_set(&pe, 0,
					     MVPP2_PRS_TCAM_DSA_TAGGED_BIT,
					     MVPP2_PRS_TCAM_DSA_TAGGED_BIT);

			/* Set ai bits क्रम next iteration */
			अगर (extend)
				mvpp2_prs_sram_ai_update(&pe, 1,
							MVPP2_PRS_SRAM_AI_MASK);
			अन्यथा
				mvpp2_prs_sram_ai_update(&pe, 0,
							MVPP2_PRS_SRAM_AI_MASK);

			/* Set result info bits to 'single vlan' */
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_SINGLE,
						 MVPP2_PRS_RI_VLAN_MASK);
			/* If packet is tagged जारी check vid filtering */
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VID);
		पूर्ण अन्यथा अणु
			/* Shअगरt 4 bytes क्रम DSA tag or 8 bytes क्रम EDSA tag*/
			mvpp2_prs_sram_shअगरt_set(&pe, shअगरt,
					MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

			/* Set result info bits to 'no vlans' */
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_NONE,
						 MVPP2_PRS_RI_VLAN_MASK);
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);
		पूर्ण

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);
	पूर्ण

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Set entry क्रम dsa ethertype */
अटल व्योम mvpp2_prs_dsa_tag_ethertype_set(काष्ठा mvpp2 *priv, पूर्णांक port,
					    bool add, bool tagged, bool extend)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid, shअगरt, port_mask;

	अगर (extend) अणु
		tid = tagged ? MVPP2_PE_ETYPE_EDSA_TAGGED :
		      MVPP2_PE_ETYPE_EDSA_UNTAGGED;
		port_mask = 0;
		shअगरt = 8;
	पूर्ण अन्यथा अणु
		tid = tagged ? MVPP2_PE_ETYPE_DSA_TAGGED :
		      MVPP2_PE_ETYPE_DSA_UNTAGGED;
		port_mask = MVPP2_PRS_PORT_MASK;
		shअगरt = 4;
	पूर्ण

	अगर (priv->prs_shaकरोw[tid].valid) अणु
		/* Entry exist - update port only */
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण अन्यथा अणु
		/* Entry करोesn't exist - create new */
		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_DSA);
		pe.index = tid;

		/* Set ethertype */
		mvpp2_prs_match_etype(&pe, 0, ETH_P_EDSA);
		mvpp2_prs_match_etype(&pe, 2, 0);

		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DSA_MASK,
					 MVPP2_PRS_RI_DSA_MASK);
		/* Shअगरt ethertype + 2 byte reserved + tag*/
		mvpp2_prs_sram_shअगरt_set(&pe, 2 + MVPP2_ETH_TYPE_LEN + shअगरt,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

		/* Update shaकरोw table */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_DSA);

		अगर (tagged) अणु
			/* Set tagged bit in DSA tag */
			mvpp2_prs_tcam_data_byte_set(&pe,
						     MVPP2_ETH_TYPE_LEN + 2 + 3,
						 MVPP2_PRS_TCAM_DSA_TAGGED_BIT,
						 MVPP2_PRS_TCAM_DSA_TAGGED_BIT);
			/* Clear all ai bits क्रम next iteration */
			mvpp2_prs_sram_ai_update(&pe, 0,
						 MVPP2_PRS_SRAM_AI_MASK);
			/* If packet is tagged जारी check vlans */
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		पूर्ण अन्यथा अणु
			/* Set result info bits to 'no vlans' */
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_NONE,
						 MVPP2_PRS_RI_VLAN_MASK);
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);
		पूर्ण
		/* Mask/unmask all ports, depending on dsa type */
		mvpp2_prs_tcam_port_map_set(&pe, port_mask);
	पूर्ण

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Search क्रम existing single/triple vlan entry */
अटल पूर्णांक mvpp2_prs_vlan_find(काष्ठा mvpp2 *priv, अचिन्हित लघु tpid, पूर्णांक ai)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	/* Go through the all entries with MVPP2_PRS_LU_VLAN */
	क्रम (tid = MVPP2_PE_FIRST_FREE_TID;
	     tid <= MVPP2_PE_LAST_FREE_TID; tid++) अणु
		अचिन्हित पूर्णांक ri_bits, ai_bits;
		bool match;

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_VLAN)
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);
		match = mvpp2_prs_tcam_data_cmp(&pe, 0, tpid);
		अगर (!match)
			जारी;

		/* Get vlan type */
		ri_bits = mvpp2_prs_sram_ri_get(&pe);
		ri_bits &= MVPP2_PRS_RI_VLAN_MASK;

		/* Get current ai value from tcam */
		ai_bits = mvpp2_prs_tcam_ai_get(&pe);
		/* Clear द्विगुन vlan bit */
		ai_bits &= ~MVPP2_PRS_DBL_VLAN_AI_BIT;

		अगर (ai != ai_bits)
			जारी;

		अगर (ri_bits == MVPP2_PRS_RI_VLAN_SINGLE ||
		    ri_bits == MVPP2_PRS_RI_VLAN_TRIPLE)
			वापस tid;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Add/update single/triple vlan entry */
अटल पूर्णांक mvpp2_prs_vlan_add(काष्ठा mvpp2 *priv, अचिन्हित लघु tpid, पूर्णांक ai,
			      अचिन्हित पूर्णांक port_map)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid_aux, tid;
	पूर्णांक ret = 0;

	स_रखो(&pe, 0, माप(pe));

	tid = mvpp2_prs_vlan_find(priv, tpid, ai);

	अगर (tid < 0) अणु
		/* Create new tcam entry */
		tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_LAST_FREE_TID,
						MVPP2_PE_FIRST_FREE_TID);
		अगर (tid < 0)
			वापस tid;

		/* Get last द्विगुन vlan tid */
		क्रम (tid_aux = MVPP2_PE_LAST_FREE_TID;
		     tid_aux >= MVPP2_PE_FIRST_FREE_TID; tid_aux--) अणु
			अचिन्हित पूर्णांक ri_bits;

			अगर (!priv->prs_shaकरोw[tid_aux].valid ||
			    priv->prs_shaकरोw[tid_aux].lu != MVPP2_PRS_LU_VLAN)
				जारी;

			mvpp2_prs_init_from_hw(priv, &pe, tid_aux);
			ri_bits = mvpp2_prs_sram_ri_get(&pe);
			अगर ((ri_bits & MVPP2_PRS_RI_VLAN_MASK) ==
			    MVPP2_PRS_RI_VLAN_DOUBLE)
				अवरोध;
		पूर्ण

		अगर (tid <= tid_aux)
			वापस -EINVAL;

		स_रखो(&pe, 0, माप(pe));
		pe.index = tid;
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VLAN);

		mvpp2_prs_match_etype(&pe, 0, tpid);

		/* VLAN tag detected, proceed with VID filtering */
		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VID);

		/* Clear all ai bits क्रम next iteration */
		mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

		अगर (ai == MVPP2_PRS_SINGLE_VLAN_AI) अणु
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_SINGLE,
						 MVPP2_PRS_RI_VLAN_MASK);
		पूर्ण अन्यथा अणु
			ai |= MVPP2_PRS_DBL_VLAN_AI_BIT;
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_TRIPLE,
						 MVPP2_PRS_RI_VLAN_MASK);
		पूर्ण
		mvpp2_prs_tcam_ai_update(&pe, ai, MVPP2_PRS_SRAM_AI_MASK);

		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VLAN);
	पूर्ण अन्यथा अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण
	/* Update ports' mask */
	mvpp2_prs_tcam_port_map_set(&pe, port_map);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस ret;
पूर्ण

/* Get first मुक्त द्विगुन vlan ai number */
अटल पूर्णांक mvpp2_prs_द्विगुन_vlan_ai_मुक्त_get(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < MVPP2_PRS_DBL_VLANS_MAX; i++) अणु
		अगर (!priv->prs_द्विगुन_vlans[i])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Search क्रम existing द्विगुन vlan entry */
अटल पूर्णांक mvpp2_prs_द्विगुन_vlan_find(काष्ठा mvpp2 *priv, अचिन्हित लघु tpid1,
				      अचिन्हित लघु tpid2)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	/* Go through the all entries with MVPP2_PRS_LU_VLAN */
	क्रम (tid = MVPP2_PE_FIRST_FREE_TID;
	     tid <= MVPP2_PE_LAST_FREE_TID; tid++) अणु
		अचिन्हित पूर्णांक ri_mask;
		bool match;

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_VLAN)
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);

		match = mvpp2_prs_tcam_data_cmp(&pe, 0, tpid1) &&
			mvpp2_prs_tcam_data_cmp(&pe, 4, tpid2);

		अगर (!match)
			जारी;

		ri_mask = mvpp2_prs_sram_ri_get(&pe) & MVPP2_PRS_RI_VLAN_MASK;
		अगर (ri_mask == MVPP2_PRS_RI_VLAN_DOUBLE)
			वापस tid;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Add or update द्विगुन vlan entry */
अटल पूर्णांक mvpp2_prs_द्विगुन_vlan_add(काष्ठा mvpp2 *priv, अचिन्हित लघु tpid1,
				     अचिन्हित लघु tpid2,
				     अचिन्हित पूर्णांक port_map)
अणु
	पूर्णांक tid_aux, tid, ai, ret = 0;
	काष्ठा mvpp2_prs_entry pe;

	स_रखो(&pe, 0, माप(pe));

	tid = mvpp2_prs_द्विगुन_vlan_find(priv, tpid1, tpid2);

	अगर (tid < 0) अणु
		/* Create new tcam entry */
		tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
				MVPP2_PE_LAST_FREE_TID);
		अगर (tid < 0)
			वापस tid;

		/* Set ai value क्रम new द्विगुन vlan entry */
		ai = mvpp2_prs_द्विगुन_vlan_ai_मुक्त_get(priv);
		अगर (ai < 0)
			वापस ai;

		/* Get first single/triple vlan tid */
		क्रम (tid_aux = MVPP2_PE_FIRST_FREE_TID;
		     tid_aux <= MVPP2_PE_LAST_FREE_TID; tid_aux++) अणु
			अचिन्हित पूर्णांक ri_bits;

			अगर (!priv->prs_shaकरोw[tid_aux].valid ||
			    priv->prs_shaकरोw[tid_aux].lu != MVPP2_PRS_LU_VLAN)
				जारी;

			mvpp2_prs_init_from_hw(priv, &pe, tid_aux);
			ri_bits = mvpp2_prs_sram_ri_get(&pe);
			ri_bits &= MVPP2_PRS_RI_VLAN_MASK;
			अगर (ri_bits == MVPP2_PRS_RI_VLAN_SINGLE ||
			    ri_bits == MVPP2_PRS_RI_VLAN_TRIPLE)
				अवरोध;
		पूर्ण

		अगर (tid >= tid_aux)
			वापस -दुस्फल;

		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		pe.index = tid;

		priv->prs_द्विगुन_vlans[ai] = true;

		mvpp2_prs_match_etype(&pe, 0, tpid1);
		mvpp2_prs_match_etype(&pe, 4, tpid2);

		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		/* Shअगरt 4 bytes - skip outer vlan tag */
		mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_VLAN_TAG_LEN,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_DOUBLE,
					 MVPP2_PRS_RI_VLAN_MASK);
		mvpp2_prs_sram_ai_update(&pe, ai | MVPP2_PRS_DBL_VLAN_AI_BIT,
					 MVPP2_PRS_SRAM_AI_MASK);

		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VLAN);
	पूर्ण अन्यथा अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण

	/* Update ports' mask */
	mvpp2_prs_tcam_port_map_set(&pe, port_map);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस ret;
पूर्ण

/* IPv4 header parsing क्रम fragmentation and L4 offset */
अटल पूर्णांक mvpp2_prs_ip4_proto(काष्ठा mvpp2 *priv, अचिन्हित लघु proto,
			       अचिन्हित पूर्णांक ri, अचिन्हित पूर्णांक ri_mask)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	अगर ((proto != IPPROTO_TCP) && (proto != IPPROTO_UDP) &&
	    (proto != IPPROTO_IGMP))
		वापस -EINVAL;

	/* Not fragmented packet */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP4);
	pe.index = tid;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);

	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3, -4,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_IPV4_DIP_AI_BIT);
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask | MVPP2_PRS_RI_IP_FRAG_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 2, 0x00,
				     MVPP2_PRS_TCAM_PROTO_MASK_L);
	mvpp2_prs_tcam_data_byte_set(&pe, 3, 0x00,
				     MVPP2_PRS_TCAM_PROTO_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 5, proto, MVPP2_PRS_TCAM_PROTO_MASK);
	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV4_DIP_AI_BIT,
				 MVPP2_PRS_IPV4_DIP_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Fragmented packet */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	pe.index = tid;
	/* Clear ri beक्रमe updating */
	pe.sram[MVPP2_PRS_SRAM_RI_WORD] = 0x0;
	pe.sram[MVPP2_PRS_SRAM_RI_CTRL_WORD] = 0x0;
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask);

	mvpp2_prs_sram_ri_update(&pe, ri | MVPP2_PRS_RI_IP_FRAG_TRUE,
				 ri_mask | MVPP2_PRS_RI_IP_FRAG_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 2, 0x00, 0x0);
	mvpp2_prs_tcam_data_byte_set(&pe, 3, 0x00, 0x0);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* IPv4 L3 multicast or broadcast */
अटल पूर्णांक mvpp2_prs_ip4_cast(काष्ठा mvpp2 *priv, अचिन्हित लघु l3_cast)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक mask, tid;

	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP4);
	pe.index = tid;

	चयन (l3_cast) अणु
	हाल MVPP2_PRS_L3_MULTI_CAST:
		mvpp2_prs_tcam_data_byte_set(&pe, 0, MVPP2_PRS_IPV4_MC,
					     MVPP2_PRS_IPV4_MC_MASK);
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_MCAST,
					 MVPP2_PRS_RI_L3_ADDR_MASK);
		अवरोध;
	हाल  MVPP2_PRS_L3_BROAD_CAST:
		mask = MVPP2_PRS_IPV4_BC_MASK;
		mvpp2_prs_tcam_data_byte_set(&pe, 0, mask, mask);
		mvpp2_prs_tcam_data_byte_set(&pe, 1, mask, mask);
		mvpp2_prs_tcam_data_byte_set(&pe, 2, mask, mask);
		mvpp2_prs_tcam_data_byte_set(&pe, 3, mask, mask);
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_BCAST,
					 MVPP2_PRS_RI_L3_ADDR_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Go again to ipv4 */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP4);

	mvpp2_prs_sram_ai_update(&pe, MVPP2_PRS_IPV4_DIP_AI_BIT,
				 MVPP2_PRS_IPV4_DIP_AI_BIT);

	/* Shअगरt back to IPv4 proto */
	mvpp2_prs_sram_shअगरt_set(&pe, -12, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_IPV4_DIP_AI_BIT);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Set entries क्रम protocols over IPv6  */
अटल पूर्णांक mvpp2_prs_ip6_proto(काष्ठा mvpp2 *priv, अचिन्हित लघु proto,
			       अचिन्हित पूर्णांक ri, अचिन्हित पूर्णांक ri_mask)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	अगर ((proto != IPPROTO_TCP) && (proto != IPPROTO_UDP) &&
	    (proto != IPPROTO_ICMPV6) && (proto != IPPROTO_IPIP))
		वापस -EINVAL;

	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = tid;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask);
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L4,
				  माप(काष्ठा ipv6hdr) - 6,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	mvpp2_prs_tcam_data_byte_set(&pe, 0, proto, MVPP2_PRS_TCAM_PROTO_MASK);
	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Write HW */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP6);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* IPv6 L3 multicast entry */
अटल पूर्णांक mvpp2_prs_ip6_cast(काष्ठा mvpp2 *priv, अचिन्हित लघु l3_cast)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	अगर (l3_cast != MVPP2_PRS_L3_MULTI_CAST)
		वापस -EINVAL;

	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = tid;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP6);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_MCAST,
				 MVPP2_PRS_RI_L3_ADDR_MASK);
	mvpp2_prs_sram_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Shअगरt back to IPv6 NH */
	mvpp2_prs_sram_shअगरt_set(&pe, -18, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	mvpp2_prs_tcam_data_byte_set(&pe, 0, MVPP2_PRS_IPV6_MC,
				     MVPP2_PRS_IPV6_MC_MASK);
	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP6);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Parser per-port initialization */
अटल व्योम mvpp2_prs_hw_port_init(काष्ठा mvpp2 *priv, पूर्णांक port, पूर्णांक lu_first,
				   पूर्णांक lu_max, पूर्णांक offset)
अणु
	u32 val;

	/* Set lookup ID */
	val = mvpp2_पढ़ो(priv, MVPP2_PRS_INIT_LOOKUP_REG);
	val &= ~MVPP2_PRS_PORT_LU_MASK(port);
	val |=  MVPP2_PRS_PORT_LU_VAL(port, lu_first);
	mvpp2_ग_लिखो(priv, MVPP2_PRS_INIT_LOOKUP_REG, val);

	/* Set maximum number of loops क्रम packet received from port */
	val = mvpp2_पढ़ो(priv, MVPP2_PRS_MAX_LOOP_REG(port));
	val &= ~MVPP2_PRS_MAX_LOOP_MASK(port);
	val |= MVPP2_PRS_MAX_LOOP_VAL(port, lu_max);
	mvpp2_ग_लिखो(priv, MVPP2_PRS_MAX_LOOP_REG(port), val);

	/* Set initial offset क्रम packet header extraction क्रम the first
	 * searching loop
	 */
	val = mvpp2_पढ़ो(priv, MVPP2_PRS_INIT_OFFS_REG(port));
	val &= ~MVPP2_PRS_INIT_OFF_MASK(port);
	val |= MVPP2_PRS_INIT_OFF_VAL(port, offset);
	mvpp2_ग_लिखो(priv, MVPP2_PRS_INIT_OFFS_REG(port), val);
पूर्ण

/* Default flow entries initialization क्रम all ports */
अटल व्योम mvpp2_prs_def_flow_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक port;

	क्रम (port = 0; port < MVPP2_MAX_PORTS; port++) अणु
		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
		pe.index = MVPP2_PE_FIRST_DEFAULT_FLOW - port;

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);

		/* Set flow ID*/
		mvpp2_prs_sram_ai_update(&pe, port, MVPP2_PRS_FLOW_ID_MASK);
		mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_DONE_BIT, 1);

		/* Update shaकरोw table and hw entry */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_FLOWS);
		mvpp2_prs_hw_ग_लिखो(priv, &pe);
	पूर्ण
पूर्ण

/* Set शेष entry क्रम Marvell Header field */
अटल व्योम mvpp2_prs_mh_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;

	स_रखो(&pe, 0, माप(pe));

	pe.index = MVPP2_PE_MH_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MH);
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_MH_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_MAC);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MH);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Set MH entry that skip parser */
	pe.index = MVPP2_PE_MH_SKIP_PRS;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MH);
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_MH_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

	/* Mask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, 0);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MH);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Set शेष entires (place holder) क्रम promiscuous, non-promiscuous and
 * multicast MAC addresses
 */
अटल व्योम mvpp2_prs_mac_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;

	स_रखो(&pe, 0, माप(pe));

	/* Non-promiscuous mode क्रम all ports - DROP unknown packets */
	pe.index = MVPP2_PE_MAC_NON_PROMISCUOUS;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);

	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_DROP_MASK);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Create dummy entries क्रम drop all and promiscuous modes */
	mvpp2_prs_drop_fc(priv);
	mvpp2_prs_mac_drop_all_set(priv, 0, false);
	mvpp2_prs_mac_promisc_set(priv, 0, MVPP2_PRS_L2_UNI_CAST, false);
	mvpp2_prs_mac_promisc_set(priv, 0, MVPP2_PRS_L2_MULTI_CAST, false);
पूर्ण

/* Set शेष entries क्रम various types of dsa packets */
अटल व्योम mvpp2_prs_dsa_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;

	/* None tagged EDSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_UNTAGGED,
			      MVPP2_PRS_EDSA);

	/* Tagged EDSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);

	/* None tagged DSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_UNTAGGED,
			      MVPP2_PRS_DSA);

	/* Tagged DSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);

	/* None tagged EDSA ethertype entry - place holder*/
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, false,
					MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);

	/* Tagged EDSA ethertype entry - place holder*/
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, false,
					MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);

	/* None tagged DSA ethertype entry */
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, true,
					MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);

	/* Tagged DSA ethertype entry */
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, true,
					MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);

	/* Set शेष entry, in हाल DSA or EDSA tag not found */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_DSA);
	pe.index = MVPP2_PE_DSA_DEFAULT;
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);

	/* Shअगरt 0 bytes */
	mvpp2_prs_sram_shअगरt_set(&pe, 0, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);

	/* Clear all sram ai bits क्रम next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Initialize parser entries क्रम VID filtering */
अटल व्योम mvpp2_prs_vid_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;

	स_रखो(&pe, 0, माप(pe));

	/* Set शेष vid entry */
	pe.index = MVPP2_PE_VID_FLTR_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_EDSA_VID_AI_BIT);

	/* Skip VLAN header - Set offset to 4 bytes */
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_VLAN_TAG_LEN,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Clear all ai bits क्रम next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Set शेष vid entry क्रम extended DSA*/
	स_रखो(&pe, 0, माप(pe));

	/* Set शेष vid entry */
	pe.index = MVPP2_PE_VID_EDSA_FLTR_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_EDSA_VID_AI_BIT,
				 MVPP2_PRS_EDSA_VID_AI_BIT);

	/* Skip VLAN header - Set offset to 8 bytes */
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_VLAN_TAG_EDSA_LEN,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Clear all ai bits क्रम next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Match basic ethertypes */
अटल पूर्णांक mvpp2_prs_etype_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid, ihl;

	/* Ethertype: PPPoE */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, ETH_P_PPP_SES);

	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_PPPOE_HDR_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_PPPOE);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_PPPOE_MASK,
				 MVPP2_PRS_RI_PPPOE_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
	priv->prs_shaकरोw[pe.index].finish = false;
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_PPPOE_MASK,
				MVPP2_PRS_RI_PPPOE_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Ethertype: ARP */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, ETH_P_ARP);

	/* Generate flow in the next iteration*/
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_ARP,
				 MVPP2_PRS_RI_L3_PROTO_MASK);
	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
	priv->prs_shaकरोw[pe.index].finish = true;
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_L3_ARP,
				MVPP2_PRS_RI_L3_PROTO_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Ethertype: LBTD */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, MVPP2_IP_LBDT_TYPE);

	/* Generate flow in the next iteration*/
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_CPU_CODE_RX_SPEC |
				 MVPP2_PRS_RI_UDF3_RX_SPECIAL,
				 MVPP2_PRS_RI_CPU_CODE_MASK |
				 MVPP2_PRS_RI_UDF3_MASK);
	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
	priv->prs_shaकरोw[pe.index].finish = true;
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_CPU_CODE_RX_SPEC |
				MVPP2_PRS_RI_UDF3_RX_SPECIAL,
				MVPP2_PRS_RI_CPU_CODE_MASK |
				MVPP2_PRS_RI_UDF3_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Ethertype: IPv4 with header length >= 5 */
	क्रम (ihl = MVPP2_PRS_IPV4_IHL_MIN; ihl <= MVPP2_PRS_IPV4_IHL_MAX; ihl++) अणु
		tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
						MVPP2_PE_LAST_FREE_TID);
		अगर (tid < 0)
			वापस tid;

		स_रखो(&pe, 0, माप(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
		pe.index = tid;

		mvpp2_prs_match_etype(&pe, 0, ETH_P_IP);
		mvpp2_prs_tcam_data_byte_set(&pe, MVPP2_ETH_TYPE_LEN,
					     MVPP2_PRS_IPV4_HEAD | ihl,
					     MVPP2_PRS_IPV4_HEAD_MASK |
					     MVPP2_PRS_IPV4_IHL_MASK);

		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP4);
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_IP4,
					 MVPP2_PRS_RI_L3_PROTO_MASK);
		/* जाओ ipv4 dst-address (skip eth_type + IP-header-size - 4) */
		mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_ETH_TYPE_LEN +
					 माप(काष्ठा iphdr) - 4,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
		/* Set L4 offset */
		mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L4,
					  MVPP2_ETH_TYPE_LEN + (ihl * 4),
					  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

		/* Update shaकरोw table and hw entry */
		mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
		priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
		priv->prs_shaकरोw[pe.index].finish = false;
		mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_L3_IP4,
					MVPP2_PRS_RI_L3_PROTO_MASK);
		mvpp2_prs_hw_ग_लिखो(priv, &pe);
	पूर्ण

	/* Ethertype: IPv6 without options */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, ETH_P_IPV6);

	/* Skip DIP of IPV6 header */
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_ETH_TYPE_LEN + 8 +
				 MVPP2_MAX_L3_ADDR_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP6);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_IP6,
				 MVPP2_PRS_RI_L3_PROTO_MASK);
	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
	priv->prs_shaकरोw[pe.index].finish = false;
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_L3_IP6,
				MVPP2_PRS_RI_L3_PROTO_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Default entry क्रम MVPP2_PRS_LU_L2 - Unknown ethtype */
	स_रखो(&pe, 0, माप(काष्ठा mvpp2_prs_entry));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_L2);
	pe.index = MVPP2_PE_ETH_TYPE_UN;

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Generate flow in the next iteration*/
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_UN,
				 MVPP2_PRS_RI_L3_PROTO_MASK);
	/* Set L3 offset even it's unknown L3 */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_L2);
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_L2_DEF;
	priv->prs_shaकरोw[pe.index].finish = true;
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, MVPP2_PRS_RI_L3_UN,
				MVPP2_PRS_RI_L3_PROTO_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Configure vlan entries and detect up to 2 successive VLAN tags.
 * Possible options:
 * 0x8100, 0x88A8
 * 0x8100, 0x8100
 * 0x8100
 * 0x88A8
 */
अटल पूर्णांक mvpp2_prs_vlan_init(काष्ठा platक्रमm_device *pdev, काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक err;

	priv->prs_द्विगुन_vlans = devm_kसुस्मृति(&pdev->dev, माप(bool),
					      MVPP2_PRS_DBL_VLANS_MAX,
					      GFP_KERNEL);
	अगर (!priv->prs_द्विगुन_vlans)
		वापस -ENOMEM;

	/* Double VLAN: 0x8100, 0x88A8 */
	err = mvpp2_prs_द्विगुन_vlan_add(priv, ETH_P_8021Q, ETH_P_8021AD,
					MVPP2_PRS_PORT_MASK);
	अगर (err)
		वापस err;

	/* Double VLAN: 0x8100, 0x8100 */
	err = mvpp2_prs_द्विगुन_vlan_add(priv, ETH_P_8021Q, ETH_P_8021Q,
					MVPP2_PRS_PORT_MASK);
	अगर (err)
		वापस err;

	/* Single VLAN: 0x88a8 */
	err = mvpp2_prs_vlan_add(priv, ETH_P_8021AD, MVPP2_PRS_SINGLE_VLAN_AI,
				 MVPP2_PRS_PORT_MASK);
	अगर (err)
		वापस err;

	/* Single VLAN: 0x8100 */
	err = mvpp2_prs_vlan_add(priv, ETH_P_8021Q, MVPP2_PRS_SINGLE_VLAN_AI,
				 MVPP2_PRS_PORT_MASK);
	अगर (err)
		वापस err;

	/* Set शेष द्विगुन vlan entry */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VLAN);
	pe.index = MVPP2_PE_VLAN_DBL;

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VID);

	/* Clear ai क्रम next iterations */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_DOUBLE,
				 MVPP2_PRS_RI_VLAN_MASK);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_DBL_VLAN_AI_BIT,
				 MVPP2_PRS_DBL_VLAN_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VLAN);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Set शेष vlan none entry */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VLAN);
	pe.index = MVPP2_PE_VLAN_NONE;

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_NONE,
				 MVPP2_PRS_RI_VLAN_MASK);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VLAN);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Set entries क्रम PPPoE ethertype */
अटल पूर्णांक mvpp2_prs_pppoe_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	/* IPv4 over PPPoE with options */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_PPPOE);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, PPP_IP);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP4);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_IP4_OPT,
				 MVPP2_PRS_RI_L3_PROTO_MASK);
	/* जाओ ipv4 dest-address (skip eth_type + IP-header-size - 4) */
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_ETH_TYPE_LEN +
				 माप(काष्ठा iphdr) - 4,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_PPPOE);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* IPv4 over PPPoE without options */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	pe.index = tid;

	mvpp2_prs_tcam_data_byte_set(&pe, MVPP2_ETH_TYPE_LEN,
				     MVPP2_PRS_IPV4_HEAD |
				     MVPP2_PRS_IPV4_IHL_MIN,
				     MVPP2_PRS_IPV4_HEAD_MASK |
				     MVPP2_PRS_IPV4_IHL_MASK);

	/* Clear ri beक्रमe updating */
	pe.sram[MVPP2_PRS_SRAM_RI_WORD] = 0x0;
	pe.sram[MVPP2_PRS_SRAM_RI_CTRL_WORD] = 0x0;
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_IP4,
				 MVPP2_PRS_RI_L3_PROTO_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_PPPOE);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* IPv6 over PPPoE */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_PPPOE);
	pe.index = tid;

	mvpp2_prs_match_etype(&pe, 0, PPP_IPV6);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP6);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_IP6,
				 MVPP2_PRS_RI_L3_PROTO_MASK);
	/* Jump to DIP of IPV6 header */
	mvpp2_prs_sram_shअगरt_set(&pe, MVPP2_ETH_TYPE_LEN + 8 +
				 MVPP2_MAX_L3_ADDR_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_PPPOE);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Non-IP over PPPoE */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_PPPOE);
	pe.index = tid;

	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_UN,
				 MVPP2_PRS_RI_L3_PROTO_MASK);

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	/* Set L3 offset even अगर it's unknown L3 */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3,
				  MVPP2_ETH_TYPE_LEN,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_PPPOE);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Initialize entries क्रम IPv4 */
अटल पूर्णांक mvpp2_prs_ip4_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक err;

	/* Set entries क्रम TCP, UDP and IGMP over IPv4 */
	err = mvpp2_prs_ip4_proto(priv, IPPROTO_TCP, MVPP2_PRS_RI_L4_TCP,
				  MVPP2_PRS_RI_L4_PROTO_MASK);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip4_proto(priv, IPPROTO_UDP, MVPP2_PRS_RI_L4_UDP,
				  MVPP2_PRS_RI_L4_PROTO_MASK);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip4_proto(priv, IPPROTO_IGMP,
				  MVPP2_PRS_RI_CPU_CODE_RX_SPEC |
				  MVPP2_PRS_RI_UDF3_RX_SPECIAL,
				  MVPP2_PRS_RI_CPU_CODE_MASK |
				  MVPP2_PRS_RI_UDF3_MASK);
	अगर (err)
		वापस err;

	/* IPv4 Broadcast */
	err = mvpp2_prs_ip4_cast(priv, MVPP2_PRS_L3_BROAD_CAST);
	अगर (err)
		वापस err;

	/* IPv4 Multicast */
	err = mvpp2_prs_ip4_cast(priv, MVPP2_PRS_L3_MULTI_CAST);
	अगर (err)
		वापस err;

	/* Default IPv4 entry क्रम unknown protocols */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP4);
	pe.index = MVPP2_PE_IP4_PROTO_UN;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);

	/* Set L3 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L3, -4,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_IPV4_DIP_AI_BIT);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L4_OTHER,
				 MVPP2_PRS_RI_L4_PROTO_MASK);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV4_DIP_AI_BIT,
				 MVPP2_PRS_IPV4_DIP_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Default IPv4 entry क्रम unicast address */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP4);
	pe.index = MVPP2_PE_IP4_ADDR_UN;

	/* Go again to ipv4 */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP4);

	mvpp2_prs_sram_ai_update(&pe, MVPP2_PRS_IPV4_DIP_AI_BIT,
				 MVPP2_PRS_IPV4_DIP_AI_BIT);

	/* Shअगरt back to IPv4 proto */
	mvpp2_prs_sram_shअगरt_set(&pe, -12, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_UCAST,
				 MVPP2_PRS_RI_L3_ADDR_MASK);
	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_IPV4_DIP_AI_BIT);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Initialize entries क्रम IPv6 */
अटल पूर्णांक mvpp2_prs_ip6_init(काष्ठा mvpp2 *priv)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid, err;

	/* Set entries क्रम TCP, UDP and ICMP over IPv6 */
	err = mvpp2_prs_ip6_proto(priv, IPPROTO_TCP,
				  MVPP2_PRS_RI_L4_TCP,
				  MVPP2_PRS_RI_L4_PROTO_MASK);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip6_proto(priv, IPPROTO_UDP,
				  MVPP2_PRS_RI_L4_UDP,
				  MVPP2_PRS_RI_L4_PROTO_MASK);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip6_proto(priv, IPPROTO_ICMPV6,
				  MVPP2_PRS_RI_CPU_CODE_RX_SPEC |
				  MVPP2_PRS_RI_UDF3_RX_SPECIAL,
				  MVPP2_PRS_RI_CPU_CODE_MASK |
				  MVPP2_PRS_RI_UDF3_MASK);
	अगर (err)
		वापस err;

	/* IPv4 is the last header. This is similar हाल as 6-TCP or 17-UDP */
	/* Result Info: UDF7=1, DS lite */
	err = mvpp2_prs_ip6_proto(priv, IPPROTO_IPIP,
				  MVPP2_PRS_RI_UDF7_IP6_LITE,
				  MVPP2_PRS_RI_UDF7_MASK);
	अगर (err)
		वापस err;

	/* IPv6 multicast */
	err = mvpp2_prs_ip6_cast(priv, MVPP2_PRS_L3_MULTI_CAST);
	अगर (err)
		वापस err;

	/* Entry क्रम checking hop limit */
	tid = mvpp2_prs_tcam_first_मुक्त(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = tid;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_UN |
				 MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_L3_PROTO_MASK |
				 MVPP2_PRS_RI_DROP_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 1, 0x00, MVPP2_PRS_IPV6_HOP_MASK);
	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Default IPv6 entry क्रम unknown protocols */
	स_रखो(&pe, 0, माप(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = MVPP2_PE_IP6_PROTO_UN;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L4_OTHER,
				 MVPP2_PRS_RI_L4_PROTO_MASK);
	/* Set L4 offset relatively to our current place */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L4,
				  माप(काष्ठा ipv6hdr) - 4,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Default IPv6 entry क्रम unknown ext protocols */
	स_रखो(&pe, 0, माप(काष्ठा mvpp2_prs_entry));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = MVPP2_PE_IP6_EXT_PROTO_UN;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L4_OTHER,
				 MVPP2_PRS_RI_L4_PROTO_MASK);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV6_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	/* Default IPv6 entry क्रम unicast address */
	स_रखो(&pe, 0, माप(काष्ठा mvpp2_prs_entry));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = MVPP2_PE_IP6_ADDR_UN;

	/* Finished: go to IPv6 again */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP6);
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_L3_UCAST,
				 MVPP2_PRS_RI_L3_ADDR_MASK);
	mvpp2_prs_sram_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Shअगरt back to IPV6 NH */
	mvpp2_prs_sram_shअगरt_set(&pe, -18, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shaकरोw table and hw entry */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_IP6);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Find tcam entry with matched pair <vid,port> */
अटल पूर्णांक mvpp2_prs_vid_range_find(काष्ठा mvpp2_port *port, u16 vid, u16 mask)
अणु
	अचिन्हित अक्षर byte[2], enable[2];
	काष्ठा mvpp2_prs_entry pe;
	u16 rvid, rmask;
	पूर्णांक tid;

	/* Go through the all entries with MVPP2_PRS_LU_VID */
	क्रम (tid = MVPP2_PRS_VID_PORT_FIRST(port->id);
	     tid <= MVPP2_PRS_VID_PORT_LAST(port->id); tid++) अणु
		अगर (!port->priv->prs_shaकरोw[tid].valid ||
		    port->priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_VID)
			जारी;

		mvpp2_prs_init_from_hw(port->priv, &pe, tid);

		mvpp2_prs_tcam_data_byte_get(&pe, 2, &byte[0], &enable[0]);
		mvpp2_prs_tcam_data_byte_get(&pe, 3, &byte[1], &enable[1]);

		rvid = ((byte[0] & 0xf) << 8) + byte[1];
		rmask = ((enable[0] & 0xf) << 8) + enable[1];

		अगर (rvid != vid || rmask != mask)
			जारी;

		वापस tid;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Write parser entry क्रम VID filtering */
पूर्णांक mvpp2_prs_vid_entry_add(काष्ठा mvpp2_port *port, u16 vid)
अणु
	अचिन्हित पूर्णांक vid_start = MVPP2_PE_VID_FILT_RANGE_START +
				 port->id * MVPP2_PRS_VLAN_FILT_MAX;
	अचिन्हित पूर्णांक mask = 0xfff, reg_val, shअगरt;
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	स_रखो(&pe, 0, माप(pe));

	/* Scan TCAM and see अगर entry with this <vid,port> alपढ़ोy exist */
	tid = mvpp2_prs_vid_range_find(port, vid, mask);

	reg_val = mvpp2_पढ़ो(priv, MVPP2_MH_REG(port->id));
	अगर (reg_val & MVPP2_DSA_EXTENDED)
		shअगरt = MVPP2_VLAN_TAG_EDSA_LEN;
	अन्यथा
		shअगरt = MVPP2_VLAN_TAG_LEN;

	/* No such entry */
	अगर (tid < 0) अणु

		/* Go through all entries from first to last in vlan range */
		tid = mvpp2_prs_tcam_first_मुक्त(priv, vid_start,
						vid_start +
						MVPP2_PRS_VLAN_FILT_MAX_ENTRY);

		/* There isn't room क्रम a new VID filter */
		अगर (tid < 0)
			वापस tid;

		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);
		pe.index = tid;

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);
	पूर्ण अन्यथा अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण

	/* Enable the current port */
	mvpp2_prs_tcam_port_set(&pe, port->id, true);

	/* Continue - set next lookup */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Skip VLAN header - Set offset to 4 or 8 bytes */
	mvpp2_prs_sram_shअगरt_set(&pe, shअगरt, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Set match on VID */
	mvpp2_prs_match_vid(&pe, MVPP2_PRS_VID_TCAM_BYTE, vid);

	/* Clear all ai bits क्रम next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	/* Update shaकरोw table */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Write parser entry क्रम VID filtering */
व्योम mvpp2_prs_vid_entry_हटाओ(काष्ठा mvpp2_port *port, u16 vid)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	पूर्णांक tid;

	/* Scan TCAM and see अगर entry with this <vid,port> alपढ़ोy exist */
	tid = mvpp2_prs_vid_range_find(port, vid, 0xfff);

	/* No such entry */
	अगर (tid < 0)
		वापस;

	mvpp2_prs_hw_inv(priv, tid);
	priv->prs_shaकरोw[tid].valid = false;
पूर्ण

/* Remove all existing VID filters on this port */
व्योम mvpp2_prs_vid_हटाओ_all(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	पूर्णांक tid;

	क्रम (tid = MVPP2_PRS_VID_PORT_FIRST(port->id);
	     tid <= MVPP2_PRS_VID_PORT_LAST(port->id); tid++) अणु
		अगर (priv->prs_shaकरोw[tid].valid) अणु
			mvpp2_prs_hw_inv(priv, tid);
			priv->prs_shaकरोw[tid].valid = false;
		पूर्ण
	पूर्ण
पूर्ण

/* Remove VID filering entry क्रम this port */
व्योम mvpp2_prs_vid_disable_filtering(काष्ठा mvpp2_port *port)
अणु
	अचिन्हित पूर्णांक tid = MVPP2_PRS_VID_PORT_DFLT(port->id);
	काष्ठा mvpp2 *priv = port->priv;

	/* Invalidate the guard entry */
	mvpp2_prs_hw_inv(priv, tid);

	priv->prs_shaकरोw[tid].valid = false;
पूर्ण

/* Add guard entry that drops packets when no VID is matched on this port */
व्योम mvpp2_prs_vid_enable_filtering(काष्ठा mvpp2_port *port)
अणु
	अचिन्हित पूर्णांक tid = MVPP2_PRS_VID_PORT_DFLT(port->id);
	काष्ठा mvpp2 *priv = port->priv;
	अचिन्हित पूर्णांक reg_val, shअगरt;
	काष्ठा mvpp2_prs_entry pe;

	अगर (priv->prs_shaकरोw[tid].valid)
		वापस;

	स_रखो(&pe, 0, माप(pe));

	pe.index = tid;

	reg_val = mvpp2_पढ़ो(priv, MVPP2_MH_REG(port->id));
	अगर (reg_val & MVPP2_DSA_EXTENDED)
		shअगरt = MVPP2_VLAN_TAG_EDSA_LEN;
	अन्यथा
		shअगरt = MVPP2_VLAN_TAG_LEN;

	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	/* Mask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, 0);

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port->id, true);

	/* Continue - set next lookup */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Skip VLAN header - Set offset to 4 or 8 bytes */
	mvpp2_prs_sram_shअगरt_set(&pe, shअगरt, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Drop VLAN packets that करोn't beदीर्घ to any VIDs on this port */
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_DROP_MASK);

	/* Clear all ai bits क्रम next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	/* Update shaकरोw table */
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);
पूर्ण

/* Parser शेष initialization */
पूर्णांक mvpp2_prs_शेष_init(काष्ठा platक्रमm_device *pdev, काष्ठा mvpp2 *priv)
अणु
	पूर्णांक err, index, i;

	/* Enable tcam table */
	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_CTRL_REG, MVPP2_PRS_TCAM_EN_MASK);

	/* Clear all tcam and sram entries */
	क्रम (index = 0; index < MVPP2_PRS_TCAM_SRAM_SIZE; index++) अणु
		mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_IDX_REG, index);
		क्रम (i = 0; i < MVPP2_PRS_TCAM_WORDS; i++)
			mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_DATA_REG(i), 0);

		mvpp2_ग_लिखो(priv, MVPP2_PRS_SRAM_IDX_REG, index);
		क्रम (i = 0; i < MVPP2_PRS_SRAM_WORDS; i++)
			mvpp2_ग_लिखो(priv, MVPP2_PRS_SRAM_DATA_REG(i), 0);
	पूर्ण

	/* Invalidate all tcam entries */
	क्रम (index = 0; index < MVPP2_PRS_TCAM_SRAM_SIZE; index++)
		mvpp2_prs_hw_inv(priv, index);

	priv->prs_shaकरोw = devm_kसुस्मृति(&pdev->dev, MVPP2_PRS_TCAM_SRAM_SIZE,
					माप(*priv->prs_shaकरोw),
					GFP_KERNEL);
	अगर (!priv->prs_shaकरोw)
		वापस -ENOMEM;

	/* Always start from lookup = 0 */
	क्रम (index = 0; index < MVPP2_MAX_PORTS; index++)
		mvpp2_prs_hw_port_init(priv, index, MVPP2_PRS_LU_MH,
				       MVPP2_PRS_PORT_LU_MAX, 0);

	mvpp2_prs_def_flow_init(priv);

	mvpp2_prs_mh_init(priv);

	mvpp2_prs_mac_init(priv);

	mvpp2_prs_dsa_init(priv);

	mvpp2_prs_vid_init(priv);

	err = mvpp2_prs_etype_init(priv);
	अगर (err)
		वापस err;

	err = mvpp2_prs_vlan_init(pdev, priv);
	अगर (err)
		वापस err;

	err = mvpp2_prs_pppoe_init(priv);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip6_init(priv);
	अगर (err)
		वापस err;

	err = mvpp2_prs_ip4_init(priv);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Compare MAC DA with tcam entry data */
अटल bool mvpp2_prs_mac_range_equals(काष्ठा mvpp2_prs_entry *pe,
				       स्थिर u8 *da, अचिन्हित अक्षर *mask)
अणु
	अचिन्हित अक्षर tcam_byte, tcam_mask;
	पूर्णांक index;

	क्रम (index = 0; index < ETH_ALEN; index++) अणु
		mvpp2_prs_tcam_data_byte_get(pe, index, &tcam_byte, &tcam_mask);
		अगर (tcam_mask != mask[index])
			वापस false;

		अगर ((tcam_mask & tcam_byte) != (da[index] & mask[index]))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Find tcam entry with matched pair <MAC DA, port> */
अटल पूर्णांक
mvpp2_prs_mac_da_range_find(काष्ठा mvpp2 *priv, पूर्णांक pmap, स्थिर u8 *da,
			    अचिन्हित अक्षर *mask, पूर्णांक udf_type)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	/* Go through the all entires with MVPP2_PRS_LU_MAC */
	क्रम (tid = MVPP2_PE_MAC_RANGE_START;
	     tid <= MVPP2_PE_MAC_RANGE_END; tid++) अणु
		अचिन्हित पूर्णांक entry_pmap;

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    (priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_MAC) ||
		    (priv->prs_shaकरोw[tid].udf != udf_type))
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);
		entry_pmap = mvpp2_prs_tcam_port_map_get(&pe);

		अगर (mvpp2_prs_mac_range_equals(&pe, da, mask) &&
		    entry_pmap == pmap)
			वापस tid;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Update parser's mac da entry */
पूर्णांक mvpp2_prs_mac_da_accept(काष्ठा mvpp2_port *port, स्थिर u8 *da, bool add)
अणु
	अचिन्हित अक्षर mask[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
	काष्ठा mvpp2 *priv = port->priv;
	अचिन्हित पूर्णांक pmap, len, ri;
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	स_रखो(&pe, 0, माप(pe));

	/* Scan TCAM and see अगर entry with this <MAC DA, port> alपढ़ोy exist */
	tid = mvpp2_prs_mac_da_range_find(priv, BIT(port->id), da, mask,
					  MVPP2_PRS_UDF_MAC_DEF);

	/* No such entry */
	अगर (tid < 0) अणु
		अगर (!add)
			वापस 0;

		/* Create new TCAM entry */
		/* Go through the all entries from first to last */
		tid = mvpp2_prs_tcam_first_मुक्त(priv,
						MVPP2_PE_MAC_RANGE_START,
						MVPP2_PE_MAC_RANGE_END);
		अगर (tid < 0)
			वापस tid;

		pe.index = tid;

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);
	पूर्ण अन्यथा अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	पूर्ण

	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port->id, add);

	/* Invalidate the entry अगर no ports are left enabled */
	pmap = mvpp2_prs_tcam_port_map_get(&pe);
	अगर (pmap == 0) अणु
		अगर (add)
			वापस -EINVAL;

		mvpp2_prs_hw_inv(priv, pe.index);
		priv->prs_shaकरोw[pe.index].valid = false;
		वापस 0;
	पूर्ण

	/* Continue - set next lookup */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_DSA);

	/* Set match on DA */
	len = ETH_ALEN;
	जबतक (len--)
		mvpp2_prs_tcam_data_byte_set(&pe, len, da[len], 0xff);

	/* Set result info bits */
	अगर (is_broadcast_ether_addr(da)) अणु
		ri = MVPP2_PRS_RI_L2_BCAST;
	पूर्ण अन्यथा अगर (is_multicast_ether_addr(da)) अणु
		ri = MVPP2_PRS_RI_L2_MCAST;
	पूर्ण अन्यथा अणु
		ri = MVPP2_PRS_RI_L2_UCAST;

		अगर (ether_addr_equal(da, port->dev->dev_addr))
			ri |= MVPP2_PRS_RI_MAC_ME_MASK;
	पूर्ण

	mvpp2_prs_sram_ri_update(&pe, ri, MVPP2_PRS_RI_L2_CAST_MASK |
				 MVPP2_PRS_RI_MAC_ME_MASK);
	mvpp2_prs_shaकरोw_ri_set(priv, pe.index, ri, MVPP2_PRS_RI_L2_CAST_MASK |
				MVPP2_PRS_RI_MAC_ME_MASK);

	/* Shअगरt to ethertype */
	mvpp2_prs_sram_shअगरt_set(&pe, 2 * ETH_ALEN,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Update shaकरोw table and hw entry */
	priv->prs_shaकरोw[pe.index].udf = MVPP2_PRS_UDF_MAC_DEF;
	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_MAC);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

पूर्णांक mvpp2_prs_update_mac_da(काष्ठा net_device *dev, स्थिर u8 *da)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक err;

	/* Remove old parser entry */
	err = mvpp2_prs_mac_da_accept(port, dev->dev_addr, false);
	अगर (err)
		वापस err;

	/* Add new parser entry */
	err = mvpp2_prs_mac_da_accept(port, da, true);
	अगर (err)
		वापस err;

	/* Set addr in the device */
	ether_addr_copy(dev->dev_addr, da);

	वापस 0;
पूर्ण

व्योम mvpp2_prs_mac_del_all(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित दीर्घ pmap;
	पूर्णांक index, tid;

	क्रम (tid = MVPP2_PE_MAC_RANGE_START;
	     tid <= MVPP2_PE_MAC_RANGE_END; tid++) अणु
		अचिन्हित अक्षर da[ETH_ALEN], da_mask[ETH_ALEN];

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    (priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_MAC) ||
		    (priv->prs_shaकरोw[tid].udf != MVPP2_PRS_UDF_MAC_DEF))
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);

		/* We only want entries active on this port */
		अगर (!test_bit(port->id, &pmap))
			जारी;

		/* Read mac addr from entry */
		क्रम (index = 0; index < ETH_ALEN; index++)
			mvpp2_prs_tcam_data_byte_get(&pe, index, &da[index],
						     &da_mask[index]);

		/* Special हालs : Don't remove broadcast and port's own
		 * address
		 */
		अगर (is_broadcast_ether_addr(da) ||
		    ether_addr_equal(da, port->dev->dev_addr))
			जारी;

		/* Remove entry from TCAM */
		mvpp2_prs_mac_da_accept(port, da, false);
	पूर्ण
पूर्ण

पूर्णांक mvpp2_prs_tag_mode_set(काष्ठा mvpp2 *priv, पूर्णांक port, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल MVPP2_TAG_TYPE_EDSA:
		/* Add port to EDSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		/* Remove port from DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		अवरोध;

	हाल MVPP2_TAG_TYPE_DSA:
		/* Add port to DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		/* Remove port from EDSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		अवरोध;

	हाल MVPP2_TAG_TYPE_MH:
	हाल MVPP2_TAG_TYPE_NONE:
		/* Remove port क्रमm EDSA and DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		अवरोध;

	शेष:
		अगर ((type < 0) || (type > MVPP2_TAG_TYPE_EDSA))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mvpp2_prs_add_flow(काष्ठा mvpp2 *priv, पूर्णांक flow, u32 ri, u32 ri_mask)
अणु
	काष्ठा mvpp2_prs_entry pe;
	u8 *ri_byte, *ri_byte_mask;
	पूर्णांक tid, i;

	स_रखो(&pe, 0, माप(pe));

	tid = mvpp2_prs_tcam_first_मुक्त(priv,
					MVPP2_PE_LAST_FREE_TID,
					MVPP2_PE_FIRST_FREE_TID);
	अगर (tid < 0)
		वापस tid;

	pe.index = tid;

	ri_byte = (u8 *)&ri;
	ri_byte_mask = (u8 *)&ri_mask;

	mvpp2_prs_sram_ai_update(&pe, flow, MVPP2_PRS_FLOW_ID_MASK);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_DONE_BIT, 1);

	क्रम (i = 0; i < 4; i++) अणु
		mvpp2_prs_tcam_data_byte_set(&pe, i, ri_byte[i],
					     ri_byte_mask[i]);
	पूर्ण

	mvpp2_prs_shaकरोw_set(priv, pe.index, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);
	mvpp2_prs_hw_ग_लिखो(priv, &pe);

	वापस 0;
पूर्ण

/* Set prs flow क्रम the port */
पूर्णांक mvpp2_prs_def_flow(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_prs_entry pe;
	पूर्णांक tid;

	स_रखो(&pe, 0, माप(pe));

	tid = mvpp2_prs_flow_find(port->priv, port->id);

	/* Such entry not exist */
	अगर (tid < 0) अणु
		/* Go through the all entires from last to first */
		tid = mvpp2_prs_tcam_first_मुक्त(port->priv,
						MVPP2_PE_LAST_FREE_TID,
					       MVPP2_PE_FIRST_FREE_TID);
		अगर (tid < 0)
			वापस tid;

		pe.index = tid;

		/* Set flow ID*/
		mvpp2_prs_sram_ai_update(&pe, port->id, MVPP2_PRS_FLOW_ID_MASK);
		mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_DONE_BIT, 1);

		/* Update shaकरोw table */
		mvpp2_prs_shaकरोw_set(port->priv, pe.index, MVPP2_PRS_LU_FLOWS);
	पूर्ण अन्यथा अणु
		mvpp2_prs_init_from_hw(port->priv, &pe, tid);
	पूर्ण

	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_port_map_set(&pe, (1 << port->id));
	mvpp2_prs_hw_ग_लिखो(port->priv, &pe);

	वापस 0;
पूर्ण

पूर्णांक mvpp2_prs_hits(काष्ठा mvpp2 *priv, पूर्णांक index)
अणु
	u32 val;

	अगर (index > MVPP2_PRS_TCAM_SRAM_SIZE)
		वापस -EINVAL;

	mvpp2_ग_लिखो(priv, MVPP2_PRS_TCAM_HIT_IDX_REG, index);

	val = mvpp2_पढ़ो(priv, MVPP2_PRS_TCAM_HIT_CNT_REG);

	val &= MVPP2_PRS_TCAM_HIT_CNT_MASK;

	वापस val;
पूर्ण
