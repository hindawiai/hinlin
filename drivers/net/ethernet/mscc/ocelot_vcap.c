<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot Switch driver
 * Copyright (c) 2019 Microsemi Corporation
 */

#समावेश <linux/iopoll.h>
#समावेश <linux/proc_fs.h>

#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश "ocelot_police.h"
#समावेश "ocelot_vcap.h"

#घोषणा ENTRY_WIDTH 32

क्रमागत vcap_sel अणु
	VCAP_SEL_ENTRY = 0x1,
	VCAP_SEL_ACTION = 0x2,
	VCAP_SEL_COUNTER = 0x4,
	VCAP_SEL_ALL = 0x7,
पूर्ण;

क्रमागत vcap_cmd अणु
	VCAP_CMD_WRITE = 0, /* Copy from Cache to TCAM */
	VCAP_CMD_READ = 1, /* Copy from TCAM to Cache */
	VCAP_CMD_MOVE_UP = 2, /* Move <count> up */
	VCAP_CMD_MOVE_DOWN = 3, /* Move <count> करोwn */
	VCAP_CMD_INITIALIZE = 4, /* Write all (from cache) */
पूर्ण;

#घोषणा VCAP_ENTRY_WIDTH 12 /* Max entry width (32bit words) */
#घोषणा VCAP_COUNTER_WIDTH 4 /* Max counter width (32bit words) */

काष्ठा vcap_data अणु
	u32 entry[VCAP_ENTRY_WIDTH]; /* ENTRY_DAT */
	u32 mask[VCAP_ENTRY_WIDTH]; /* MASK_DAT */
	u32 action[VCAP_ENTRY_WIDTH]; /* ACTION_DAT */
	u32 counter[VCAP_COUNTER_WIDTH]; /* CNT_DAT */
	u32 tg; /* TG_DAT */
	u32 type; /* Action type */
	u32 tg_sw; /* Current type-group */
	u32 cnt; /* Current counter */
	u32 key_offset; /* Current entry offset */
	u32 action_offset; /* Current action offset */
	u32 counter_offset; /* Current counter offset */
	u32 tg_value; /* Current type-group value */
	u32 tg_mask; /* Current type-group mask */
पूर्ण;

अटल u32 vcap_पढ़ो_update_ctrl(काष्ठा ocelot *ocelot,
				 स्थिर काष्ठा vcap_props *vcap)
अणु
	वापस ocelot_target_पढ़ो(ocelot, vcap->target, VCAP_CORE_UPDATE_CTRL);
पूर्ण

अटल व्योम vcap_cmd(काष्ठा ocelot *ocelot, स्थिर काष्ठा vcap_props *vcap,
		     u16 ix, पूर्णांक cmd, पूर्णांक sel)
अणु
	u32 value = (VCAP_CORE_UPDATE_CTRL_UPDATE_CMD(cmd) |
		     VCAP_CORE_UPDATE_CTRL_UPDATE_ADDR(ix) |
		     VCAP_CORE_UPDATE_CTRL_UPDATE_SHOT);

	अगर ((sel & VCAP_SEL_ENTRY) && ix >= vcap->entry_count)
		वापस;

	अगर (!(sel & VCAP_SEL_ENTRY))
		value |= VCAP_CORE_UPDATE_CTRL_UPDATE_ENTRY_DIS;

	अगर (!(sel & VCAP_SEL_ACTION))
		value |= VCAP_CORE_UPDATE_CTRL_UPDATE_ACTION_DIS;

	अगर (!(sel & VCAP_SEL_COUNTER))
		value |= VCAP_CORE_UPDATE_CTRL_UPDATE_CNT_DIS;

	ocelot_target_ग_लिखो(ocelot, vcap->target, value, VCAP_CORE_UPDATE_CTRL);

	पढ़ो_poll_समयout(vcap_पढ़ो_update_ctrl, value,
			  (value & VCAP_CORE_UPDATE_CTRL_UPDATE_SHOT) == 0,
			  10, 100000, false, ocelot, vcap);
पूर्ण

/* Convert from 0-based row to VCAP entry row and run command */
अटल व्योम vcap_row_cmd(काष्ठा ocelot *ocelot, स्थिर काष्ठा vcap_props *vcap,
			 u32 row, पूर्णांक cmd, पूर्णांक sel)
अणु
	vcap_cmd(ocelot, vcap, vcap->entry_count - row - 1, cmd, sel);
पूर्ण

अटल व्योम vcap_entry2cache(काष्ठा ocelot *ocelot,
			     स्थिर काष्ठा vcap_props *vcap,
			     काष्ठा vcap_data *data)
अणु
	u32 entry_words, i;

	entry_words = DIV_ROUND_UP(vcap->entry_width, ENTRY_WIDTH);

	क्रम (i = 0; i < entry_words; i++) अणु
		ocelot_target_ग_लिखो_rix(ocelot, vcap->target, data->entry[i],
					VCAP_CACHE_ENTRY_DAT, i);
		ocelot_target_ग_लिखो_rix(ocelot, vcap->target, ~data->mask[i],
					VCAP_CACHE_MASK_DAT, i);
	पूर्ण
	ocelot_target_ग_लिखो(ocelot, vcap->target, data->tg, VCAP_CACHE_TG_DAT);
पूर्ण

अटल व्योम vcap_cache2entry(काष्ठा ocelot *ocelot,
			     स्थिर काष्ठा vcap_props *vcap,
			     काष्ठा vcap_data *data)
अणु
	u32 entry_words, i;

	entry_words = DIV_ROUND_UP(vcap->entry_width, ENTRY_WIDTH);

	क्रम (i = 0; i < entry_words; i++) अणु
		data->entry[i] = ocelot_target_पढ़ो_rix(ocelot, vcap->target,
							VCAP_CACHE_ENTRY_DAT, i);
		// Invert mask
		data->mask[i] = ~ocelot_target_पढ़ो_rix(ocelot, vcap->target,
							VCAP_CACHE_MASK_DAT, i);
	पूर्ण
	data->tg = ocelot_target_पढ़ो(ocelot, vcap->target, VCAP_CACHE_TG_DAT);
पूर्ण

अटल व्योम vcap_action2cache(काष्ठा ocelot *ocelot,
			      स्थिर काष्ठा vcap_props *vcap,
			      काष्ठा vcap_data *data)
अणु
	u32 action_words, mask;
	पूर्णांक i, width;

	/* Encode action type */
	width = vcap->action_type_width;
	अगर (width) अणु
		mask = GENMASK(width, 0);
		data->action[0] = ((data->action[0] & ~mask) | data->type);
	पूर्ण

	action_words = DIV_ROUND_UP(vcap->action_width, ENTRY_WIDTH);

	क्रम (i = 0; i < action_words; i++)
		ocelot_target_ग_लिखो_rix(ocelot, vcap->target, data->action[i],
					VCAP_CACHE_ACTION_DAT, i);

	क्रम (i = 0; i < vcap->counter_words; i++)
		ocelot_target_ग_लिखो_rix(ocelot, vcap->target, data->counter[i],
					VCAP_CACHE_CNT_DAT, i);
पूर्ण

अटल व्योम vcap_cache2action(काष्ठा ocelot *ocelot,
			      स्थिर काष्ठा vcap_props *vcap,
			      काष्ठा vcap_data *data)
अणु
	u32 action_words;
	पूर्णांक i, width;

	action_words = DIV_ROUND_UP(vcap->action_width, ENTRY_WIDTH);

	क्रम (i = 0; i < action_words; i++)
		data->action[i] = ocelot_target_पढ़ो_rix(ocelot, vcap->target,
							 VCAP_CACHE_ACTION_DAT,
							 i);

	क्रम (i = 0; i < vcap->counter_words; i++)
		data->counter[i] = ocelot_target_पढ़ो_rix(ocelot, vcap->target,
							  VCAP_CACHE_CNT_DAT,
							  i);

	/* Extract action type */
	width = vcap->action_type_width;
	data->type = (width ? (data->action[0] & GENMASK(width, 0)) : 0);
पूर्ण

/* Calculate offsets क्रम entry */
अटल व्योम vcap_data_offset_get(स्थिर काष्ठा vcap_props *vcap,
				 काष्ठा vcap_data *data, पूर्णांक ix)
अणु
	पूर्णांक num_subwords_per_entry, num_subwords_per_action;
	पूर्णांक i, col, offset, num_entries_per_row, base;
	u32 width = vcap->tg_width;

	चयन (data->tg_sw) अणु
	हाल VCAP_TG_FULL:
		num_entries_per_row = 1;
		अवरोध;
	हाल VCAP_TG_HALF:
		num_entries_per_row = 2;
		अवरोध;
	हाल VCAP_TG_QUARTER:
		num_entries_per_row = 4;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	col = (ix % num_entries_per_row);
	num_subwords_per_entry = (vcap->sw_count / num_entries_per_row);
	base = (vcap->sw_count - col * num_subwords_per_entry -
		num_subwords_per_entry);
	data->tg_value = 0;
	data->tg_mask = 0;
	क्रम (i = 0; i < num_subwords_per_entry; i++) अणु
		offset = ((base + i) * width);
		data->tg_value |= (data->tg_sw << offset);
		data->tg_mask |= GENMASK(offset + width - 1, offset);
	पूर्ण

	/* Calculate key/action/counter offsets */
	col = (num_entries_per_row - col - 1);
	data->key_offset = (base * vcap->entry_width) / vcap->sw_count;
	data->counter_offset = (num_subwords_per_entry * col *
				vcap->counter_width);
	i = data->type;
	width = vcap->action_table[i].width;
	num_subwords_per_action = vcap->action_table[i].count;
	data->action_offset = ((num_subwords_per_action * col * width) /
				num_entries_per_row);
	data->action_offset += vcap->action_type_width;
पूर्ण

अटल व्योम vcap_data_set(u32 *data, u32 offset, u32 len, u32 value)
अणु
	u32 i, v, m;

	क्रम (i = 0; i < len; i++, offset++) अणु
		v = data[offset / ENTRY_WIDTH];
		m = (1 << (offset % ENTRY_WIDTH));
		अगर (value & (1 << i))
			v |= m;
		अन्यथा
			v &= ~m;
		data[offset / ENTRY_WIDTH] = v;
	पूर्ण
पूर्ण

अटल u32 vcap_data_get(u32 *data, u32 offset, u32 len)
अणु
	u32 i, v, m, value = 0;

	क्रम (i = 0; i < len; i++, offset++) अणु
		v = data[offset / ENTRY_WIDTH];
		m = (1 << (offset % ENTRY_WIDTH));
		अगर (v & m)
			value |= (1 << i);
	पूर्ण
	वापस value;
पूर्ण

अटल व्योम vcap_key_field_set(काष्ठा vcap_data *data, u32 offset, u32 width,
			       u32 value, u32 mask)
अणु
	vcap_data_set(data->entry, offset + data->key_offset, width, value);
	vcap_data_set(data->mask, offset + data->key_offset, width, mask);
पूर्ण

अटल व्योम vcap_key_set(स्थिर काष्ठा vcap_props *vcap, काष्ठा vcap_data *data,
			 पूर्णांक field, u32 value, u32 mask)
अणु
	u32 offset = vcap->keys[field].offset;
	u32 length = vcap->keys[field].length;

	vcap_key_field_set(data, offset, length, value, mask);
पूर्ण

अटल व्योम vcap_key_bytes_set(स्थिर काष्ठा vcap_props *vcap,
			       काष्ठा vcap_data *data, पूर्णांक field,
			       u8 *val, u8 *msk)
अणु
	u32 offset = vcap->keys[field].offset;
	u32 count  = vcap->keys[field].length;
	u32 i, j, n = 0, value = 0, mask = 0;

	WARN_ON(count % 8);

	/* Data wider than 32 bits are split up in chunks of maximum 32 bits.
	 * The 32 LSB of the data are written to the 32 MSB of the TCAM.
	 */
	offset += count;
	count /= 8;

	क्रम (i = 0; i < count; i++) अणु
		j = (count - i - 1);
		value += (val[j] << n);
		mask += (msk[j] << n);
		n += 8;
		अगर (n == ENTRY_WIDTH || (i + 1) == count) अणु
			offset -= n;
			vcap_key_field_set(data, offset, n, value, mask);
			n = 0;
			value = 0;
			mask = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vcap_key_l4_port_set(स्थिर काष्ठा vcap_props *vcap,
				 काष्ठा vcap_data *data, पूर्णांक field,
				 काष्ठा ocelot_vcap_udp_tcp *port)
अणु
	u32 offset = vcap->keys[field].offset;
	u32 length = vcap->keys[field].length;

	WARN_ON(length != 16);

	vcap_key_field_set(data, offset, length, port->value, port->mask);
पूर्ण

अटल व्योम vcap_key_bit_set(स्थिर काष्ठा vcap_props *vcap,
			     काष्ठा vcap_data *data, पूर्णांक field,
			     क्रमागत ocelot_vcap_bit val)
अणु
	u32 value = (val == OCELOT_VCAP_BIT_1 ? 1 : 0);
	u32 msk = (val == OCELOT_VCAP_BIT_ANY ? 0 : 1);
	u32 offset = vcap->keys[field].offset;
	u32 length = vcap->keys[field].length;

	WARN_ON(length != 1);

	vcap_key_field_set(data, offset, length, value, msk);
पूर्ण

अटल व्योम vcap_action_set(स्थिर काष्ठा vcap_props *vcap,
			    काष्ठा vcap_data *data, पूर्णांक field, u32 value)
अणु
	पूर्णांक offset = vcap->actions[field].offset;
	पूर्णांक length = vcap->actions[field].length;

	vcap_data_set(data->action, offset + data->action_offset, length,
		      value);
पूर्ण

अटल व्योम is2_action_set(काष्ठा ocelot *ocelot, काष्ठा vcap_data *data,
			   काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_IS2];
	काष्ठा ocelot_vcap_action *a = &filter->action;

	vcap_action_set(vcap, data, VCAP_IS2_ACT_MASK_MODE, a->mask_mode);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_PORT_MASK, a->port_mask);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_POLICE_ENA, a->police_ena);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_POLICE_IDX, a->pol_ix);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_CPU_QU_NUM, a->cpu_qu_num);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_CPU_COPY_ENA, a->cpu_copy_ena);
पूर्ण

अटल व्योम is2_entry_set(काष्ठा ocelot *ocelot, पूर्णांक ix,
			  काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_IS2];
	काष्ठा ocelot_vcap_key_vlan *tag = &filter->vlan;
	u32 val, msk, type, type_mask = 0xf, i, count;
	काष्ठा ocelot_vcap_u64 payload;
	काष्ठा vcap_data data;
	पूर्णांक row = (ix / 2);

	स_रखो(&payload, 0, माप(payload));
	स_रखो(&data, 0, माप(data));

	/* Read row */
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_READ, VCAP_SEL_ALL);
	vcap_cache2entry(ocelot, vcap, &data);
	vcap_cache2action(ocelot, vcap, &data);

	data.tg_sw = VCAP_TG_HALF;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	अगर (filter->prio != 0)
		data.tg |= data.tg_value;

	data.type = IS2_ACTION_TYPE_NORMAL;

	vcap_key_set(vcap, &data, VCAP_IS2_HK_PAG, filter->pag, 0xff);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_FIRST,
			 (filter->lookup == 0) ? OCELOT_VCAP_BIT_1 :
			 OCELOT_VCAP_BIT_0);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_IGR_PORT_MASK, 0,
		     ~filter->ingress_port_mask);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_FIRST, OCELOT_VCAP_BIT_ANY);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_HOST_MATCH,
			 OCELOT_VCAP_BIT_ANY);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L2_MC, filter->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L2_BC, filter->dmac_bc);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_VLAN_TAGGED, tag->tagged);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_VID,
		     tag->vid.value, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_PCP,
		     tag->pcp.value[0], tag->pcp.mask[0]);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_DEI, tag->dei);

	चयन (filter->key_type) अणु
	हाल OCELOT_VCAP_KEY_ETYPE: अणु
		काष्ठा ocelot_vcap_key_etype *etype = &filter->key.etype;

		type = IS2_TYPE_ETYPE;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_DMAC,
				   etype->dmac.value, etype->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_SMAC,
				   etype->smac.value, etype->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_ETYPE,
				   etype->etype.value, etype->etype.mask);
		/* Clear unused bits */
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD0,
			     0, 0);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD1,
			     0, 0);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD2,
			     0, 0);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD0,
				   etype->data.value, etype->data.mask);
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_LLC: अणु
		काष्ठा ocelot_vcap_key_llc *llc = &filter->key.llc;

		type = IS2_TYPE_LLC;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_DMAC,
				   llc->dmac.value, llc->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_SMAC,
				   llc->smac.value, llc->smac.mask);
		क्रम (i = 0; i < 4; i++) अणु
			payload.value[i] = llc->llc.value[i];
			payload.mask[i] = llc->llc.mask[i];
		पूर्ण
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_LLC_L2_LLC,
				   payload.value, payload.mask);
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_SNAP: अणु
		काष्ठा ocelot_vcap_key_snap *snap = &filter->key.snap;

		type = IS2_TYPE_SNAP;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_DMAC,
				   snap->dmac.value, snap->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L2_SMAC,
				   snap->smac.value, snap->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_SNAP_L2_SNAP,
				   filter->key.snap.snap.value,
				   filter->key.snap.snap.mask);
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_ARP: अणु
		काष्ठा ocelot_vcap_key_arp *arp = &filter->key.arp;

		type = IS2_TYPE_ARP;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_ARP_SMAC,
				   arp->smac.value, arp->smac.mask);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_ADDR_SPACE_OK,
				 arp->ethernet);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_PROTO_SPACE_OK,
				 arp->ip);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_LEN_OK,
				 arp->length);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_TARGET_MATCH,
				 arp->dmac_match);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_SENDER_MATCH,
				 arp->smac_match);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_ARP_OPCODE_UNKNOWN,
				 arp->unknown);

		/* OPCODE is inverse, bit 0 is reply flag, bit 1 is RARP flag */
		val = ((arp->req == OCELOT_VCAP_BIT_0 ? 1 : 0) |
		       (arp->arp == OCELOT_VCAP_BIT_0 ? 2 : 0));
		msk = ((arp->req == OCELOT_VCAP_BIT_ANY ? 0 : 1) |
		       (arp->arp == OCELOT_VCAP_BIT_ANY ? 0 : 2));
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ARP_OPCODE,
			     val, msk);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_ARP_L3_IP4_DIP,
				   arp->dip.value.addr, arp->dip.mask.addr);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_ARP_L3_IP4_SIP,
				   arp->sip.value.addr, arp->sip.mask.addr);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ARP_DIP_EQ_SIP,
			     0, 0);
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_IPV4:
	हाल OCELOT_VCAP_KEY_IPV6: अणु
		क्रमागत ocelot_vcap_bit sip_eq_dip, sport_eq_dport, seq_zero, tcp;
		क्रमागत ocelot_vcap_bit ttl, fragment, options, tcp_ack, tcp_urg;
		क्रमागत ocelot_vcap_bit tcp_fin, tcp_syn, tcp_rst, tcp_psh;
		काष्ठा ocelot_vcap_key_ipv4 *ipv4 = शून्य;
		काष्ठा ocelot_vcap_key_ipv6 *ipv6 = शून्य;
		काष्ठा ocelot_vcap_udp_tcp *sport, *dport;
		काष्ठा ocelot_vcap_ipv4 sip, dip;
		काष्ठा ocelot_vcap_u8 proto, ds;
		काष्ठा ocelot_vcap_u48 *ip_data;

		अगर (filter->key_type == OCELOT_VCAP_KEY_IPV4) अणु
			ipv4 = &filter->key.ipv4;
			ttl = ipv4->ttl;
			fragment = ipv4->fragment;
			options = ipv4->options;
			proto = ipv4->proto;
			ds = ipv4->ds;
			ip_data = &ipv4->data;
			sip = ipv4->sip;
			dip = ipv4->dip;
			sport = &ipv4->sport;
			dport = &ipv4->dport;
			tcp_fin = ipv4->tcp_fin;
			tcp_syn = ipv4->tcp_syn;
			tcp_rst = ipv4->tcp_rst;
			tcp_psh = ipv4->tcp_psh;
			tcp_ack = ipv4->tcp_ack;
			tcp_urg = ipv4->tcp_urg;
			sip_eq_dip = ipv4->sip_eq_dip;
			sport_eq_dport = ipv4->sport_eq_dport;
			seq_zero = ipv4->seq_zero;
		पूर्ण अन्यथा अणु
			ipv6 = &filter->key.ipv6;
			ttl = ipv6->ttl;
			fragment = OCELOT_VCAP_BIT_ANY;
			options = OCELOT_VCAP_BIT_ANY;
			proto = ipv6->proto;
			ds = ipv6->ds;
			ip_data = &ipv6->data;
			क्रम (i = 0; i < 8; i++) अणु
				val = ipv6->sip.value[i + 8];
				msk = ipv6->sip.mask[i + 8];
				अगर (i < 4) अणु
					dip.value.addr[i] = val;
					dip.mask.addr[i] = msk;
				पूर्ण अन्यथा अणु
					sip.value.addr[i - 4] = val;
					sip.mask.addr[i - 4] = msk;
				पूर्ण
			पूर्ण
			sport = &ipv6->sport;
			dport = &ipv6->dport;
			tcp_fin = ipv6->tcp_fin;
			tcp_syn = ipv6->tcp_syn;
			tcp_rst = ipv6->tcp_rst;
			tcp_psh = ipv6->tcp_psh;
			tcp_ack = ipv6->tcp_ack;
			tcp_urg = ipv6->tcp_urg;
			sip_eq_dip = ipv6->sip_eq_dip;
			sport_eq_dport = ipv6->sport_eq_dport;
			seq_zero = ipv6->seq_zero;
		पूर्ण

		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_IP4,
				 ipv4 ? OCELOT_VCAP_BIT_1 : OCELOT_VCAP_BIT_0);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L3_FRAGMENT,
				 fragment);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_L3_FRAG_OFS_GT0, 0, 0);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L3_OPTIONS,
				 options);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_IP4_L3_TTL_GT0,
				 ttl);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L3_TOS,
				   ds.value, ds.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L3_IP4_DIP,
				   dip.value.addr, dip.mask.addr);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_L3_IP4_SIP,
				   sip.value.addr, sip.mask.addr);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_DIP_EQ_SIP,
				 sip_eq_dip);
		val = proto.value[0];
		msk = proto.mask[0];
		type = IS2_TYPE_IP_UDP_TCP;
		अगर (msk == 0xff && (val == 6 || val == 17)) अणु
			/* UDP/TCP protocol match */
			tcp = (val == 6 ?
			       OCELOT_VCAP_BIT_1 : OCELOT_VCAP_BIT_0);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_TCP, tcp);
			vcap_key_l4_port_set(vcap, &data,
					     VCAP_IS2_HK_L4_DPORT, dport);
			vcap_key_l4_port_set(vcap, &data,
					     VCAP_IS2_HK_L4_SPORT, sport);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_L4_RNG, 0, 0);
			vcap_key_bit_set(vcap, &data,
					 VCAP_IS2_HK_L4_SPORT_EQ_DPORT,
					 sport_eq_dport);
			vcap_key_bit_set(vcap, &data,
					 VCAP_IS2_HK_L4_SEQUENCE_EQ0,
					 seq_zero);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_FIN,
					 tcp_fin);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_SYN,
					 tcp_syn);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_RST,
					 tcp_rst);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_PSH,
					 tcp_psh);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_ACK,
					 tcp_ack);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_L4_URG,
					 tcp_urg);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_L4_1588_DOM,
				     0, 0);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_L4_1588_VER,
				     0, 0);
		पूर्ण अन्यथा अणु
			अगर (msk == 0) अणु
				/* Any IP protocol match */
				type_mask = IS2_TYPE_MASK_IP_ANY;
			पूर्ण अन्यथा अणु
				/* Non-UDP/TCP protocol match */
				type = IS2_TYPE_IP_OTHER;
				क्रम (i = 0; i < 6; i++) अणु
					payload.value[i] = ip_data->value[i];
					payload.mask[i] = ip_data->mask[i];
				पूर्ण
			पूर्ण
			vcap_key_bytes_set(vcap, &data,
					   VCAP_IS2_HK_IP4_L3_PROTO,
					   proto.value, proto.mask);
			vcap_key_bytes_set(vcap, &data,
					   VCAP_IS2_HK_L3_PAYLOAD,
					   payload.value, payload.mask);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_ANY:
	शेष:
		type = 0;
		type_mask = 0;
		count = vcap->entry_width / 2;
		/* Iterate over the non-common part of the key and
		 * clear entry data
		 */
		क्रम (i = vcap->keys[VCAP_IS2_HK_L2_DMAC].offset;
		     i < count; i += ENTRY_WIDTH) अणु
			vcap_key_field_set(&data, i, min(32u, count - i), 0, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	vcap_key_set(vcap, &data, VCAP_IS2_TYPE, type, type_mask);
	is2_action_set(ocelot, &data, filter);
	vcap_data_set(data.counter, data.counter_offset,
		      vcap->counter_width, filter->stats.pkts);

	/* Write row */
	vcap_entry2cache(ocelot, vcap, &data);
	vcap_action2cache(ocelot, vcap, &data);
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_WRITE, VCAP_SEL_ALL);
पूर्ण

अटल व्योम is1_action_set(काष्ठा ocelot *ocelot, काष्ठा vcap_data *data,
			   स्थिर काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_IS1];
	स्थिर काष्ठा ocelot_vcap_action *a = &filter->action;

	vcap_action_set(vcap, data, VCAP_IS1_ACT_VID_REPLACE_ENA,
			a->vid_replace_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VID_ADD_VAL, a->vid);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VLAN_POP_CNT_ENA,
			a->vlan_pop_cnt_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VLAN_POP_CNT,
			a->vlan_pop_cnt);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PCP_DEI_ENA, a->pcp_dei_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PCP_VAL, a->pcp);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_DEI_VAL, a->dei);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_QOS_ENA, a->qos_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_QOS_VAL, a->qos_val);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PAG_OVERRIDE_MASK,
			a->pag_override_mask);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PAG_VAL, a->pag_val);
पूर्ण

अटल व्योम is1_entry_set(काष्ठा ocelot *ocelot, पूर्णांक ix,
			  काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_IS1];
	काष्ठा ocelot_vcap_key_vlan *tag = &filter->vlan;
	काष्ठा ocelot_vcap_u64 payload;
	काष्ठा vcap_data data;
	पूर्णांक row = ix / 2;
	u32 type;

	स_रखो(&payload, 0, माप(payload));
	स_रखो(&data, 0, माप(data));

	/* Read row */
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_READ, VCAP_SEL_ALL);
	vcap_cache2entry(ocelot, vcap, &data);
	vcap_cache2action(ocelot, vcap, &data);

	data.tg_sw = VCAP_TG_HALF;
	data.type = IS1_ACTION_TYPE_NORMAL;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	अगर (filter->prio != 0)
		data.tg |= data.tg_value;

	vcap_key_set(vcap, &data, VCAP_IS1_HK_LOOKUP, filter->lookup, 0x3);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_IGR_PORT_MASK, 0,
		     ~filter->ingress_port_mask);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_L2_MC, filter->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_L2_BC, filter->dmac_bc);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_VLAN_TAGGED, tag->tagged);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_VID,
		     tag->vid.value, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_PCP,
		     tag->pcp.value[0], tag->pcp.mask[0]);
	type = IS1_TYPE_S1_NORMAL;

	चयन (filter->key_type) अणु
	हाल OCELOT_VCAP_KEY_ETYPE: अणु
		काष्ठा ocelot_vcap_key_etype *etype = &filter->key.etype;

		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_L2_SMAC,
				   etype->smac.value, etype->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_ETYPE,
				   etype->etype.value, etype->etype.mask);
		अवरोध;
	पूर्ण
	हाल OCELOT_VCAP_KEY_IPV4: अणु
		काष्ठा ocelot_vcap_key_ipv4 *ipv4 = &filter->key.ipv4;
		काष्ठा ocelot_vcap_udp_tcp *sport = &ipv4->sport;
		काष्ठा ocelot_vcap_udp_tcp *dport = &ipv4->dport;
		क्रमागत ocelot_vcap_bit tcp_udp = OCELOT_VCAP_BIT_0;
		काष्ठा ocelot_vcap_u8 proto = ipv4->proto;
		काष्ठा ocelot_vcap_ipv4 sip = ipv4->sip;
		u32 val, msk;

		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_IP_SNAP,
				 OCELOT_VCAP_BIT_1);
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_IP4,
				 OCELOT_VCAP_BIT_1);
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_ETYPE_LEN,
				 OCELOT_VCAP_BIT_1);
		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_L3_IP4_SIP,
				   sip.value.addr, sip.mask.addr);

		val = proto.value[0];
		msk = proto.mask[0];

		अगर ((val == NEXTHDR_TCP || val == NEXTHDR_UDP) && msk == 0xff)
			tcp_udp = OCELOT_VCAP_BIT_1;
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TCP_UDP, tcp_udp);

		अगर (tcp_udp) अणु
			क्रमागत ocelot_vcap_bit tcp = OCELOT_VCAP_BIT_0;

			अगर (val == NEXTHDR_TCP)
				tcp = OCELOT_VCAP_BIT_1;

			vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TCP, tcp);
			vcap_key_l4_port_set(vcap, &data, VCAP_IS1_HK_L4_SPORT,
					     sport);
			/* Overloaded field */
			vcap_key_l4_port_set(vcap, &data, VCAP_IS1_HK_ETYPE,
					     dport);
		पूर्ण अन्यथा अणु
			/* IPv4 "other" frame */
			काष्ठा ocelot_vcap_u16 etype = अणु0पूर्ण;

			/* Overloaded field */
			etype.value[0] = proto.value[0];
			etype.mask[0] = proto.mask[0];

			vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_ETYPE,
					   etype.value, etype.mask);
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TYPE,
			 type ? OCELOT_VCAP_BIT_1 : OCELOT_VCAP_BIT_0);

	is1_action_set(ocelot, &data, filter);
	vcap_data_set(data.counter, data.counter_offset,
		      vcap->counter_width, filter->stats.pkts);

	/* Write row */
	vcap_entry2cache(ocelot, vcap, &data);
	vcap_action2cache(ocelot, vcap, &data);
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_WRITE, VCAP_SEL_ALL);
पूर्ण

अटल व्योम es0_action_set(काष्ठा ocelot *ocelot, काष्ठा vcap_data *data,
			   स्थिर काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_ES0];
	स्थिर काष्ठा ocelot_vcap_action *a = &filter->action;

	vcap_action_set(vcap, data, VCAP_ES0_ACT_PUSH_OUTER_TAG,
			a->push_outer_tag);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PUSH_INNER_TAG,
			a->push_inner_tag);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_TPID_SEL,
			a->tag_a_tpid_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_VID_SEL,
			a->tag_a_vid_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_PCP_SEL,
			a->tag_a_pcp_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_VID_A_VAL, a->vid_a_val);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PCP_A_VAL, a->pcp_a_val);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_TPID_SEL,
			a->tag_b_tpid_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_VID_SEL,
			a->tag_b_vid_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_PCP_SEL,
			a->tag_b_pcp_sel);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_VID_B_VAL, a->vid_b_val);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PCP_B_VAL, a->pcp_b_val);
पूर्ण

अटल व्योम es0_entry_set(काष्ठा ocelot *ocelot, पूर्णांक ix,
			  काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_ES0];
	काष्ठा ocelot_vcap_key_vlan *tag = &filter->vlan;
	काष्ठा ocelot_vcap_u64 payload;
	काष्ठा vcap_data data;
	पूर्णांक row = ix;

	स_रखो(&payload, 0, माप(payload));
	स_रखो(&data, 0, माप(data));

	/* Read row */
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_READ, VCAP_SEL_ALL);
	vcap_cache2entry(ocelot, vcap, &data);
	vcap_cache2action(ocelot, vcap, &data);

	data.tg_sw = VCAP_TG_FULL;
	data.type = ES0_ACTION_TYPE_NORMAL;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	अगर (filter->prio != 0)
		data.tg |= data.tg_value;

	vcap_key_set(vcap, &data, VCAP_ES0_IGR_PORT, filter->ingress_port.value,
		     filter->ingress_port.mask);
	vcap_key_set(vcap, &data, VCAP_ES0_EGR_PORT, filter->egress_port.value,
		     filter->egress_port.mask);
	vcap_key_bit_set(vcap, &data, VCAP_ES0_L2_MC, filter->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_ES0_L2_BC, filter->dmac_bc);
	vcap_key_set(vcap, &data, VCAP_ES0_VID,
		     tag->vid.value, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_ES0_PCP,
		     tag->pcp.value[0], tag->pcp.mask[0]);

	es0_action_set(ocelot, &data, filter);
	vcap_data_set(data.counter, data.counter_offset,
		      vcap->counter_width, filter->stats.pkts);

	/* Write row */
	vcap_entry2cache(ocelot, vcap, &data);
	vcap_action2cache(ocelot, vcap, &data);
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_WRITE, VCAP_SEL_ALL);
पूर्ण

अटल व्योम vcap_entry_get(काष्ठा ocelot *ocelot, पूर्णांक ix,
			   काष्ठा ocelot_vcap_filter *filter)
अणु
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[filter->block_id];
	काष्ठा vcap_data data;
	पूर्णांक row, count;
	u32 cnt;

	अगर (filter->block_id == VCAP_ES0)
		data.tg_sw = VCAP_TG_FULL;
	अन्यथा
		data.tg_sw = VCAP_TG_HALF;

	count = (1 << (data.tg_sw - 1));
	row = (ix / count);
	vcap_row_cmd(ocelot, vcap, row, VCAP_CMD_READ, VCAP_SEL_COUNTER);
	vcap_cache2action(ocelot, vcap, &data);
	vcap_data_offset_get(vcap, &data, ix);
	cnt = vcap_data_get(data.counter, data.counter_offset,
			    vcap->counter_width);

	filter->stats.pkts = cnt;
पूर्ण

अटल व्योम vcap_entry_set(काष्ठा ocelot *ocelot, पूर्णांक ix,
			   काष्ठा ocelot_vcap_filter *filter)
अणु
	अगर (filter->block_id == VCAP_IS1)
		वापस is1_entry_set(ocelot, ix, filter);
	अगर (filter->block_id == VCAP_IS2)
		वापस is2_entry_set(ocelot, ix, filter);
	अगर (filter->block_id == VCAP_ES0)
		वापस es0_entry_set(ocelot, ix, filter);
पूर्ण

अटल पूर्णांक ocelot_vcap_policer_add(काष्ठा ocelot *ocelot, u32 pol_ix,
				   काष्ठा ocelot_policer *pol)
अणु
	काष्ठा qos_policer_conf pp = अणु 0 पूर्ण;

	अगर (!pol)
		वापस -EINVAL;

	pp.mode = MSCC_QOS_RATE_MODE_DATA;
	pp.pir = pol->rate;
	pp.pbs = pol->burst;

	वापस qos_policer_conf_set(ocelot, 0, pol_ix, &pp);
पूर्ण

अटल व्योम ocelot_vcap_policer_del(काष्ठा ocelot *ocelot,
				    काष्ठा ocelot_vcap_block *block,
				    u32 pol_ix)
अणु
	काष्ठा ocelot_vcap_filter *filter;
	काष्ठा qos_policer_conf pp = अणु0पूर्ण;
	पूर्णांक index = -1;

	अगर (pol_ix < block->pol_lpr)
		वापस;

	list_क्रम_each_entry(filter, &block->rules, list) अणु
		index++;
		अगर (filter->block_id == VCAP_IS2 &&
		    filter->action.police_ena &&
		    filter->action.pol_ix < pol_ix) अणु
			filter->action.pol_ix += 1;
			ocelot_vcap_policer_add(ocelot, filter->action.pol_ix,
						&filter->action.pol);
			is2_entry_set(ocelot, index, filter);
		पूर्ण
	पूर्ण

	pp.mode = MSCC_QOS_RATE_MODE_DISABLED;
	qos_policer_conf_set(ocelot, 0, pol_ix, &pp);

	block->pol_lpr++;
पूर्ण

अटल व्योम ocelot_vcap_filter_add_to_block(काष्ठा ocelot *ocelot,
					    काष्ठा ocelot_vcap_block *block,
					    काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_filter *पंचांगp;
	काष्ठा list_head *pos, *n;

	अगर (filter->block_id == VCAP_IS2 && filter->action.police_ena) अणु
		block->pol_lpr--;
		filter->action.pol_ix = block->pol_lpr;
		ocelot_vcap_policer_add(ocelot, filter->action.pol_ix,
					&filter->action.pol);
	पूर्ण

	block->count++;

	अगर (list_empty(&block->rules)) अणु
		list_add(&filter->list, &block->rules);
		वापस;
	पूर्ण

	list_क्रम_each_safe(pos, n, &block->rules) अणु
		पंचांगp = list_entry(pos, काष्ठा ocelot_vcap_filter, list);
		अगर (filter->prio < पंचांगp->prio)
			अवरोध;
	पूर्ण
	list_add(&filter->list, pos->prev);
पूर्ण

अटल bool ocelot_vcap_filter_equal(स्थिर काष्ठा ocelot_vcap_filter *a,
				     स्थिर काष्ठा ocelot_vcap_filter *b)
अणु
	वापस !स_भेद(&a->id, &b->id, माप(काष्ठा ocelot_vcap_id));
पूर्ण

अटल पूर्णांक ocelot_vcap_block_get_filter_index(काष्ठा ocelot_vcap_block *block,
					      काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_filter *पंचांगp;
	पूर्णांक index = 0;

	list_क्रम_each_entry(पंचांगp, &block->rules, list) अणु
		अगर (ocelot_vcap_filter_equal(filter, पंचांगp))
			वापस index;
		index++;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल काष्ठा ocelot_vcap_filter*
ocelot_vcap_block_find_filter_by_index(काष्ठा ocelot_vcap_block *block,
				       पूर्णांक index)
अणु
	काष्ठा ocelot_vcap_filter *पंचांगp;
	पूर्णांक i = 0;

	list_क्रम_each_entry(पंचांगp, &block->rules, list) अणु
		अगर (i == index)
			वापस पंचांगp;
		++i;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ocelot_vcap_filter *
ocelot_vcap_block_find_filter_by_id(काष्ठा ocelot_vcap_block *block, पूर्णांक cookie,
				    bool tc_offload)
अणु
	काष्ठा ocelot_vcap_filter *filter;

	list_क्रम_each_entry(filter, &block->rules, list)
		अगर (filter->id.tc_offload == tc_offload &&
		    filter->id.cookie == cookie)
			वापस filter;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ocelot_vcap_block_find_filter_by_id);

/* If @on=false, then SNAP, ARP, IP and OAM frames will not match on keys based
 * on destination and source MAC addresses, but only on higher-level protocol
 * inक्रमmation. The only frame types to match on keys containing MAC addresses
 * in this हाल are non-SNAP, non-ARP, non-IP and non-OAM frames.
 *
 * If @on=true, then the above frame types (SNAP, ARP, IP and OAM) will match
 * on MAC_ETYPE keys such as destination and source MAC on this ingress port.
 * However the setting has the side effect of making these frames not matching
 * on any _other_ keys than MAC_ETYPE ones.
 */
अटल व्योम ocelot_match_all_as_mac_etype(काष्ठा ocelot *ocelot, पूर्णांक port,
					  पूर्णांक lookup, bool on)
अणु
	u32 val = 0;

	अगर (on)
		val = ANA_PORT_VCAP_S2_CFG_S2_SNAP_DIS(BIT(lookup)) |
		      ANA_PORT_VCAP_S2_CFG_S2_ARP_DIS(BIT(lookup)) |
		      ANA_PORT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(BIT(lookup)) |
		      ANA_PORT_VCAP_S2_CFG_S2_IP_OTHER_DIS(BIT(lookup)) |
		      ANA_PORT_VCAP_S2_CFG_S2_OAM_DIS(BIT(lookup));

	ocelot_rmw_gix(ocelot, val,
		       ANA_PORT_VCAP_S2_CFG_S2_SNAP_DIS(BIT(lookup)) |
		       ANA_PORT_VCAP_S2_CFG_S2_ARP_DIS(BIT(lookup)) |
		       ANA_PORT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(BIT(lookup)) |
		       ANA_PORT_VCAP_S2_CFG_S2_IP_OTHER_DIS(BIT(lookup)) |
		       ANA_PORT_VCAP_S2_CFG_S2_OAM_DIS(BIT(lookup)),
		       ANA_PORT_VCAP_S2_CFG, port);
पूर्ण

अटल bool
ocelot_vcap_is_problematic_mac_etype(काष्ठा ocelot_vcap_filter *filter)
अणु
	u16 proto, mask;

	अगर (filter->key_type != OCELOT_VCAP_KEY_ETYPE)
		वापस false;

	proto = ntohs(*(__be16 *)filter->key.etype.etype.value);
	mask = ntohs(*(__be16 *)filter->key.etype.etype.mask);

	/* ETH_P_ALL match, so all protocols below are included */
	अगर (mask == 0)
		वापस true;
	अगर (proto == ETH_P_ARP)
		वापस true;
	अगर (proto == ETH_P_IP)
		वापस true;
	अगर (proto == ETH_P_IPV6)
		वापस true;

	वापस false;
पूर्ण

अटल bool
ocelot_vcap_is_problematic_non_mac_etype(काष्ठा ocelot_vcap_filter *filter)
अणु
	अगर (filter->key_type == OCELOT_VCAP_KEY_SNAP)
		वापस true;
	अगर (filter->key_type == OCELOT_VCAP_KEY_ARP)
		वापस true;
	अगर (filter->key_type == OCELOT_VCAP_KEY_IPV4)
		वापस true;
	अगर (filter->key_type == OCELOT_VCAP_KEY_IPV6)
		वापस true;
	वापस false;
पूर्ण

अटल bool
ocelot_exclusive_mac_etype_filter_rules(काष्ठा ocelot *ocelot,
					काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_block *block = &ocelot->block[filter->block_id];
	काष्ठा ocelot_vcap_filter *पंचांगp;
	अचिन्हित दीर्घ port;
	पूर्णांक i;

	/* We only have the S2_IP_TCPUDP_DIS set of knobs क्रम VCAP IS2 */
	अगर (filter->block_id != VCAP_IS2)
		वापस true;

	अगर (ocelot_vcap_is_problematic_mac_etype(filter)) अणु
		/* Search क्रम any non-MAC_ETYPE rules on the port */
		क्रम (i = 0; i < block->count; i++) अणु
			पंचांगp = ocelot_vcap_block_find_filter_by_index(block, i);
			अगर (पंचांगp->ingress_port_mask & filter->ingress_port_mask &&
			    पंचांगp->lookup == filter->lookup &&
			    ocelot_vcap_is_problematic_non_mac_etype(पंचांगp))
				वापस false;
		पूर्ण

		क्रम_each_set_bit(port, &filter->ingress_port_mask,
				 ocelot->num_phys_ports)
			ocelot_match_all_as_mac_etype(ocelot, port,
						      filter->lookup, true);
	पूर्ण अन्यथा अगर (ocelot_vcap_is_problematic_non_mac_etype(filter)) अणु
		/* Search क्रम any MAC_ETYPE rules on the port */
		क्रम (i = 0; i < block->count; i++) अणु
			पंचांगp = ocelot_vcap_block_find_filter_by_index(block, i);
			अगर (पंचांगp->ingress_port_mask & filter->ingress_port_mask &&
			    पंचांगp->lookup == filter->lookup &&
			    ocelot_vcap_is_problematic_mac_etype(पंचांगp))
				वापस false;
		पूर्ण

		क्रम_each_set_bit(port, &filter->ingress_port_mask,
				 ocelot->num_phys_ports)
			ocelot_match_all_as_mac_etype(ocelot, port,
						      filter->lookup, false);
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक ocelot_vcap_filter_add(काष्ठा ocelot *ocelot,
			   काष्ठा ocelot_vcap_filter *filter,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot_vcap_block *block = &ocelot->block[filter->block_id];
	पूर्णांक i, index;

	अगर (!ocelot_exclusive_mac_etype_filter_rules(ocelot, filter)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Cannot mix MAC_ETYPE with non-MAC_ETYPE rules, use the other IS2 lookup");
		वापस -EBUSY;
	पूर्ण

	/* Add filter to the linked list */
	ocelot_vcap_filter_add_to_block(ocelot, block, filter);

	/* Get the index of the inserted filter */
	index = ocelot_vcap_block_get_filter_index(block, filter);
	अगर (index < 0)
		वापस index;

	/* Move करोwn the rules to make place क्रम the new filter */
	क्रम (i = block->count - 1; i > index; i--) अणु
		काष्ठा ocelot_vcap_filter *पंचांगp;

		पंचांगp = ocelot_vcap_block_find_filter_by_index(block, i);
		vcap_entry_set(ocelot, i, पंचांगp);
	पूर्ण

	/* Now insert the new filter */
	vcap_entry_set(ocelot, index, filter);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_vcap_filter_add);

अटल व्योम ocelot_vcap_block_हटाओ_filter(काष्ठा ocelot *ocelot,
					    काष्ठा ocelot_vcap_block *block,
					    काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_filter *पंचांगp;
	काष्ठा list_head *pos, *q;

	list_क्रम_each_safe(pos, q, &block->rules) अणु
		पंचांगp = list_entry(pos, काष्ठा ocelot_vcap_filter, list);
		अगर (ocelot_vcap_filter_equal(filter, पंचांगp)) अणु
			अगर (पंचांगp->block_id == VCAP_IS2 &&
			    पंचांगp->action.police_ena)
				ocelot_vcap_policer_del(ocelot, block,
							पंचांगp->action.pol_ix);

			list_del(pos);
			kमुक्त(पंचांगp);
		पूर्ण
	पूर्ण

	block->count--;
पूर्ण

पूर्णांक ocelot_vcap_filter_del(काष्ठा ocelot *ocelot,
			   काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_block *block = &ocelot->block[filter->block_id];
	काष्ठा ocelot_vcap_filter del_filter;
	पूर्णांक i, index;

	स_रखो(&del_filter, 0, माप(del_filter));

	/* Gets index of the filter */
	index = ocelot_vcap_block_get_filter_index(block, filter);
	अगर (index < 0)
		वापस index;

	/* Delete filter */
	ocelot_vcap_block_हटाओ_filter(ocelot, block, filter);

	/* Move up all the blocks over the deleted filter */
	क्रम (i = index; i < block->count; i++) अणु
		काष्ठा ocelot_vcap_filter *पंचांगp;

		पंचांगp = ocelot_vcap_block_find_filter_by_index(block, i);
		vcap_entry_set(ocelot, i, पंचांगp);
	पूर्ण

	/* Now delete the last filter, because it is duplicated */
	vcap_entry_set(ocelot, block->count, &del_filter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_vcap_filter_del);

पूर्णांक ocelot_vcap_filter_stats_update(काष्ठा ocelot *ocelot,
				    काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_vcap_block *block = &ocelot->block[filter->block_id];
	काष्ठा ocelot_vcap_filter पंचांगp;
	पूर्णांक index;

	index = ocelot_vcap_block_get_filter_index(block, filter);
	अगर (index < 0)
		वापस index;

	vcap_entry_get(ocelot, index, filter);

	/* After we get the result we need to clear the counters */
	पंचांगp = *filter;
	पंचांगp.stats.pkts = 0;
	vcap_entry_set(ocelot, index, &पंचांगp);

	वापस 0;
पूर्ण

अटल व्योम ocelot_vcap_init_one(काष्ठा ocelot *ocelot,
				 स्थिर काष्ठा vcap_props *vcap)
अणु
	काष्ठा vcap_data data;

	स_रखो(&data, 0, माप(data));

	vcap_entry2cache(ocelot, vcap, &data);
	ocelot_target_ग_लिखो(ocelot, vcap->target, vcap->entry_count,
			    VCAP_CORE_MV_CFG);
	vcap_cmd(ocelot, vcap, 0, VCAP_CMD_INITIALIZE, VCAP_SEL_ENTRY);

	vcap_action2cache(ocelot, vcap, &data);
	ocelot_target_ग_लिखो(ocelot, vcap->target, vcap->action_count,
			    VCAP_CORE_MV_CFG);
	vcap_cmd(ocelot, vcap, 0, VCAP_CMD_INITIALIZE,
		 VCAP_SEL_ACTION | VCAP_SEL_COUNTER);
पूर्ण

अटल व्योम ocelot_vcap_detect_स्थिरants(काष्ठा ocelot *ocelot,
					 काष्ठा vcap_props *vcap)
अणु
	पूर्णांक counter_memory_width;
	पूर्णांक num_शेष_actions;
	पूर्णांक version;

	version = ocelot_target_पढ़ो(ocelot, vcap->target,
				     VCAP_CONST_VCAP_VER);
	/* Only version 0 VCAP supported क्रम now */
	अगर (WARN_ON(version != 0))
		वापस;

	/* Width in bits of type-group field */
	vcap->tg_width = ocelot_target_पढ़ो(ocelot, vcap->target,
					    VCAP_CONST_ENTRY_TG_WIDTH);
	/* Number of subwords per TCAM row */
	vcap->sw_count = ocelot_target_पढ़ो(ocelot, vcap->target,
					    VCAP_CONST_ENTRY_SWCNT);
	/* Number of rows in TCAM. There can be this many full keys, or द्विगुन
	 * this number half keys, or 4 बार this number quarter keys.
	 */
	vcap->entry_count = ocelot_target_पढ़ो(ocelot, vcap->target,
					       VCAP_CONST_ENTRY_CNT);
	/* Assuming there are 4 subwords per TCAM row, their layout in the
	 * actual TCAM (not in the cache) would be:
	 *
	 * |  SW 3  | TG 3 |  SW 2  | TG 2 |  SW 1  | TG 1 |  SW 0  | TG 0 |
	 *
	 * (where SW=subword and TG=Type-Group).
	 *
	 * What VCAP_CONST_ENTRY_CNT is giving us is the width of one full TCAM
	 * row. But when software accesses the TCAM through the cache
	 * रेजिस्टरs, the Type-Group values are written through another set of
	 * रेजिस्टरs VCAP_TG_DAT, and thereक्रमe, it appears as though the 4
	 * subwords are contiguous in the cache memory.
	 * Important mention: regardless of the number of key entries per row
	 * (and thereक्रमe of key size: 1 full key or 2 half keys or 4 quarter
	 * keys), software always has to configure 4 Type-Group values. For
	 * example, in the हाल of 1 full key, the driver needs to set all 4
	 * Type-Group to be full key.
	 *
	 * For this reason, we need to fix up the value that the hardware is
	 * giving us. We करोn't actually care about the width of the entry in
	 * the TCAM. What we care about is the width of the entry in the cache
	 * रेजिस्टरs, which is how we get to पूर्णांकeract with it. And since the
	 * VCAP_ENTRY_DAT cache रेजिस्टरs access only the subwords and not the
	 * Type-Groups, this means we need to subtract the width of the
	 * Type-Groups when packing and unpacking key entry data in a TCAM row.
	 */
	vcap->entry_width = ocelot_target_पढ़ो(ocelot, vcap->target,
					       VCAP_CONST_ENTRY_WIDTH);
	vcap->entry_width -= vcap->tg_width * vcap->sw_count;
	num_शेष_actions = ocelot_target_पढ़ो(ocelot, vcap->target,
						 VCAP_CONST_ACTION_DEF_CNT);
	vcap->action_count = vcap->entry_count + num_शेष_actions;
	vcap->action_width = ocelot_target_पढ़ो(ocelot, vcap->target,
						VCAP_CONST_ACTION_WIDTH);
	/* The width of the counter memory, this is the complete width of all
	 * counter-fields associated with one full-word entry. There is one
	 * counter per entry sub-word (see CAP_CORE::ENTRY_SWCNT क्रम number of
	 * subwords.)
	 */
	vcap->counter_words = vcap->sw_count;
	counter_memory_width = ocelot_target_पढ़ो(ocelot, vcap->target,
						  VCAP_CONST_CNT_WIDTH);
	vcap->counter_width = counter_memory_width / vcap->counter_words;
पूर्ण

पूर्णांक ocelot_vcap_init(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक i;

	/* Create a policer that will drop the frames क्रम the cpu.
	 * This policer will be used as action in the acl rules to drop
	 * frames.
	 */
	ocelot_ग_लिखो_gix(ocelot, 0x299, ANA_POL_MODE_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_ग_लिखो_gix(ocelot, 0x1, ANA_POL_PIR_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_ग_लिखो_gix(ocelot, 0x3fffff, ANA_POL_PIR_STATE,
			 OCELOT_POLICER_DISCARD);
	ocelot_ग_लिखो_gix(ocelot, 0x0, ANA_POL_CIR_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_ग_लिखो_gix(ocelot, 0x3fffff, ANA_POL_CIR_STATE,
			 OCELOT_POLICER_DISCARD);

	क्रम (i = 0; i < OCELOT_NUM_VCAP_BLOCKS; i++) अणु
		काष्ठा ocelot_vcap_block *block = &ocelot->block[i];
		काष्ठा vcap_props *vcap = &ocelot->vcap[i];

		INIT_LIST_HEAD(&block->rules);
		block->pol_lpr = OCELOT_POLICER_DISCARD - 1;

		ocelot_vcap_detect_स्थिरants(ocelot, vcap);
		ocelot_vcap_init_one(ocelot, vcap);
	पूर्ण

	INIT_LIST_HEAD(&ocelot->dummy_rules);

	वापस 0;
पूर्ण
