<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/* Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश "sja1105_static_config.h"
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>

/* Convenience wrappers over the generic packing functions. These take पूर्णांकo
 * account the SJA1105 memory layout quirks and provide some level of
 * programmer protection against incorrect API use. The errors are not expected
 * to occur durring runसमय, thereक्रमe prपूर्णांकing and swallowing them here is
 * appropriate instead of clutterring up higher-level code.
 */
व्योम sja1105_pack(व्योम *buf, स्थिर u64 *val, पूर्णांक start, पूर्णांक end, माप_प्रकार len)
अणु
	पूर्णांक rc = packing(buf, (u64 *)val, start, end, len,
			 PACK, QUIRK_LSW32_IS_FIRST);

	अगर (likely(!rc))
		वापस;

	अगर (rc == -EINVAL) अणु
		pr_err("Start bit (%d) expected to be larger than end (%d)\n",
		       start, end);
	पूर्ण अन्यथा अगर (rc == -दुस्फल) अणु
		अगर ((start - end + 1) > 64)
			pr_err("Field %d-%d too large for 64 bits!\n",
			       start, end);
		अन्यथा
			pr_err("Cannot store %llx inside bits %d-%d (would truncate)\n",
			       *val, start, end);
	पूर्ण
	dump_stack();
पूर्ण

व्योम sja1105_unpack(स्थिर व्योम *buf, u64 *val, पूर्णांक start, पूर्णांक end, माप_प्रकार len)
अणु
	पूर्णांक rc = packing((व्योम *)buf, val, start, end, len,
			 UNPACK, QUIRK_LSW32_IS_FIRST);

	अगर (likely(!rc))
		वापस;

	अगर (rc == -EINVAL)
		pr_err("Start bit (%d) expected to be larger than end (%d)\n",
		       start, end);
	अन्यथा अगर (rc == -दुस्फल)
		pr_err("Field %d-%d too large for 64 bits!\n",
		       start, end);
	dump_stack();
पूर्ण

व्योम sja1105_packing(व्योम *buf, u64 *val, पूर्णांक start, पूर्णांक end,
		     माप_प्रकार len, क्रमागत packing_op op)
अणु
	पूर्णांक rc = packing(buf, val, start, end, len, op, QUIRK_LSW32_IS_FIRST);

	अगर (likely(!rc))
		वापस;

	अगर (rc == -EINVAL) अणु
		pr_err("Start bit (%d) expected to be larger than end (%d)\n",
		       start, end);
	पूर्ण अन्यथा अगर (rc == -दुस्फल) अणु
		अगर ((start - end + 1) > 64)
			pr_err("Field %d-%d too large for 64 bits!\n",
			       start, end);
		अन्यथा
			pr_err("Cannot store %llx inside bits %d-%d (would truncate)\n",
			       *val, start, end);
	पूर्ण
	dump_stack();
पूर्ण

/* Little-endian Ethernet CRC32 of data packed as big-endian u32 words */
u32 sja1105_crc32(स्थिर व्योम *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;
	u64 word;
	u32 crc;

	/* seed */
	crc = ~0;
	क्रम (i = 0; i < len; i += 4) अणु
		sja1105_unpack(buf + i, &word, 31, 0, 4);
		crc = crc32_le(crc, (u8 *)&word, 4);
	पूर्ण
	वापस ~crc;
पूर्ण

अटल माप_प्रकार sja1105et_avb_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						 क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_AVB_PARAMS_ENTRY;
	काष्ठा sja1105_avb_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->desपंचांगeta, 95, 48, size, op);
	sja1105_packing(buf, &entry->srcmeta,  47,  0, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105pqrs_avb_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY;
	काष्ठा sja1105_avb_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->cas_master, 126, 126, size, op);
	sja1105_packing(buf, &entry->desपंचांगeta,   125,  78, size, op);
	sja1105_packing(buf, &entry->srcmeta,     77,  30, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105et_general_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						     क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_GENERAL_PARAMS_ENTRY;
	काष्ठा sja1105_general_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->vllupक्रमmat, 319, 319, size, op);
	sja1105_packing(buf, &entry->mirr_ptacu,  318, 318, size, op);
	sja1105_packing(buf, &entry->चयनid,    317, 315, size, op);
	sja1105_packing(buf, &entry->hostprio,    314, 312, size, op);
	sja1105_packing(buf, &entry->mac_fltres1, 311, 264, size, op);
	sja1105_packing(buf, &entry->mac_fltres0, 263, 216, size, op);
	sja1105_packing(buf, &entry->mac_flt1,    215, 168, size, op);
	sja1105_packing(buf, &entry->mac_flt0,    167, 120, size, op);
	sja1105_packing(buf, &entry->incl_srcpt1, 119, 119, size, op);
	sja1105_packing(buf, &entry->incl_srcpt0, 118, 118, size, op);
	sja1105_packing(buf, &entry->send_meta1,  117, 117, size, op);
	sja1105_packing(buf, &entry->send_meta0,  116, 116, size, op);
	sja1105_packing(buf, &entry->casc_port,   115, 113, size, op);
	sja1105_packing(buf, &entry->host_port,   112, 110, size, op);
	sja1105_packing(buf, &entry->mirr_port,   109, 107, size, op);
	sja1105_packing(buf, &entry->vlmarker,    106,  75, size, op);
	sja1105_packing(buf, &entry->vlmask,       74,  43, size, op);
	sja1105_packing(buf, &entry->tpid,         42,  27, size, op);
	sja1105_packing(buf, &entry->ignore2stf,   26,  26, size, op);
	sja1105_packing(buf, &entry->tpid2,        25,  10, size, op);
	वापस size;
पूर्ण

/* TPID and TPID2 are पूर्णांकentionally reversed so that semantic
 * compatibility with E/T is kept.
 */
माप_प्रकार sja1105pqrs_general_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY;
	काष्ठा sja1105_general_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->vllupक्रमmat, 351, 351, size, op);
	sja1105_packing(buf, &entry->mirr_ptacu,  350, 350, size, op);
	sja1105_packing(buf, &entry->चयनid,    349, 347, size, op);
	sja1105_packing(buf, &entry->hostprio,    346, 344, size, op);
	sja1105_packing(buf, &entry->mac_fltres1, 343, 296, size, op);
	sja1105_packing(buf, &entry->mac_fltres0, 295, 248, size, op);
	sja1105_packing(buf, &entry->mac_flt1,    247, 200, size, op);
	sja1105_packing(buf, &entry->mac_flt0,    199, 152, size, op);
	sja1105_packing(buf, &entry->incl_srcpt1, 151, 151, size, op);
	sja1105_packing(buf, &entry->incl_srcpt0, 150, 150, size, op);
	sja1105_packing(buf, &entry->send_meta1,  149, 149, size, op);
	sja1105_packing(buf, &entry->send_meta0,  148, 148, size, op);
	sja1105_packing(buf, &entry->casc_port,   147, 145, size, op);
	sja1105_packing(buf, &entry->host_port,   144, 142, size, op);
	sja1105_packing(buf, &entry->mirr_port,   141, 139, size, op);
	sja1105_packing(buf, &entry->vlmarker,    138, 107, size, op);
	sja1105_packing(buf, &entry->vlmask,      106,  75, size, op);
	sja1105_packing(buf, &entry->tpid2,        74,  59, size, op);
	sja1105_packing(buf, &entry->ignore2stf,   58,  58, size, op);
	sja1105_packing(buf, &entry->tpid,         57,  42, size, op);
	sja1105_packing(buf, &entry->queue_ts,     41,  41, size, op);
	sja1105_packing(buf, &entry->egrmirrvid,   40,  29, size, op);
	sja1105_packing(buf, &entry->egrmirrpcp,   28,  26, size, op);
	sja1105_packing(buf, &entry->egrmirrdei,   25,  25, size, op);
	sja1105_packing(buf, &entry->replay_port,  24,  22, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार
sja1105_l2_क्रमwarding_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY;
	काष्ठा sja1105_l2_क्रमwarding_params_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	sja1105_packing(buf, &entry->max_dynp, 95, 93, size, op);
	क्रम (i = 0, offset = 13; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entry->part_spc[i],
				offset + 9, offset + 0, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105_l2_क्रमwarding_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_L2_FORWARDING_ENTRY;
	काष्ठा sja1105_l2_क्रमwarding_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	sja1105_packing(buf, &entry->bc_करोमुख्य,  63, 59, size, op);
	sja1105_packing(buf, &entry->reach_port, 58, 54, size, op);
	sja1105_packing(buf, &entry->fl_करोमुख्य,  53, 49, size, op);
	क्रम (i = 0, offset = 25; i < 8; i++, offset += 3)
		sja1105_packing(buf, &entry->vlan_pmap[i],
				offset + 2, offset + 0, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार
sja1105et_l2_lookup_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY;
	काष्ठा sja1105_l2_lookup_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->maxage,         31, 17, size, op);
	sja1105_packing(buf, &entry->dyn_tbsz,       16, 14, size, op);
	sja1105_packing(buf, &entry->poly,           13,  6, size, op);
	sja1105_packing(buf, &entry->shared_learn,    5,  5, size, op);
	sja1105_packing(buf, &entry->no_enf_hostprt,  4,  4, size, op);
	sja1105_packing(buf, &entry->no_mgmt_learn,   3,  3, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105pqrs_l2_lookup_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						  क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY;
	काष्ठा sja1105_l2_lookup_params_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 58; i < 5; i++, offset += 11)
		sja1105_packing(buf, &entry->maxaddrp[i],
				offset + 10, offset + 0, size, op);
	sja1105_packing(buf, &entry->maxage,         57,  43, size, op);
	sja1105_packing(buf, &entry->start_dynspc,   42,  33, size, op);
	sja1105_packing(buf, &entry->drpnolearn,     32,  28, size, op);
	sja1105_packing(buf, &entry->shared_learn,   27,  27, size, op);
	sja1105_packing(buf, &entry->no_enf_hostprt, 26,  26, size, op);
	sja1105_packing(buf, &entry->no_mgmt_learn,  25,  25, size, op);
	sja1105_packing(buf, &entry->use_अटल,     24,  24, size, op);
	sja1105_packing(buf, &entry->owr_dyn,        23,  23, size, op);
	sja1105_packing(buf, &entry->learn_once,     22,  22, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105et_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_L2_LOOKUP_ENTRY;
	काष्ठा sja1105_l2_lookup_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->vlanid,    95, 84, size, op);
	sja1105_packing(buf, &entry->macaddr,   83, 36, size, op);
	sja1105_packing(buf, &entry->destports, 35, 31, size, op);
	sja1105_packing(buf, &entry->enfport,   30, 30, size, op);
	sja1105_packing(buf, &entry->index,     29, 20, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105pqrs_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	काष्ठा sja1105_l2_lookup_entry *entry = entry_ptr;

	अगर (entry->lockeds) अणु
		sja1105_packing(buf, &entry->tsreg,    159, 159, size, op);
		sja1105_packing(buf, &entry->mirrvlan, 158, 147, size, op);
		sja1105_packing(buf, &entry->takets,   146, 146, size, op);
		sja1105_packing(buf, &entry->mirr,     145, 145, size, op);
		sja1105_packing(buf, &entry->retag,    144, 144, size, op);
	पूर्ण अन्यथा अणु
		sja1105_packing(buf, &entry->touched,  159, 159, size, op);
		sja1105_packing(buf, &entry->age,      158, 144, size, op);
	पूर्ण
	sja1105_packing(buf, &entry->mask_iotag,   143, 143, size, op);
	sja1105_packing(buf, &entry->mask_vlanid,  142, 131, size, op);
	sja1105_packing(buf, &entry->mask_macaddr, 130,  83, size, op);
	sja1105_packing(buf, &entry->iotag,         82,  82, size, op);
	sja1105_packing(buf, &entry->vlanid,        81,  70, size, op);
	sja1105_packing(buf, &entry->macaddr,       69,  22, size, op);
	sja1105_packing(buf, &entry->destports,     21,  17, size, op);
	sja1105_packing(buf, &entry->enfport,       16,  16, size, op);
	sja1105_packing(buf, &entry->index,         15,   6, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_l2_policing_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_L2_POLICING_ENTRY;
	काष्ठा sja1105_l2_policing_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->sharindx,  63, 58, size, op);
	sja1105_packing(buf, &entry->smax,      57, 42, size, op);
	sja1105_packing(buf, &entry->rate,      41, 26, size, op);
	sja1105_packing(buf, &entry->maxlen,    25, 15, size, op);
	sja1105_packing(buf, &entry->partition, 14, 12, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105et_mac_config_entry_packing(व्योम *buf, व्योम *entry_ptr,
						 क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_MAC_CONFIG_ENTRY;
	काष्ठा sja1105_mac_config_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 72; i < 8; i++, offset += 19) अणु
		sja1105_packing(buf, &entry->enabled[i],
				offset +  0, offset +  0, size, op);
		sja1105_packing(buf, &entry->base[i],
				offset +  9, offset +  1, size, op);
		sja1105_packing(buf, &entry->top[i],
				offset + 18, offset + 10, size, op);
	पूर्ण
	sja1105_packing(buf, &entry->अगरg,       71, 67, size, op);
	sja1105_packing(buf, &entry->speed,     66, 65, size, op);
	sja1105_packing(buf, &entry->tp_delin,  64, 49, size, op);
	sja1105_packing(buf, &entry->tp_delout, 48, 33, size, op);
	sja1105_packing(buf, &entry->maxage,    32, 25, size, op);
	sja1105_packing(buf, &entry->vlanprio,  24, 22, size, op);
	sja1105_packing(buf, &entry->vlanid,    21, 10, size, op);
	sja1105_packing(buf, &entry->ing_mirr,   9,  9, size, op);
	sja1105_packing(buf, &entry->egr_mirr,   8,  8, size, op);
	sja1105_packing(buf, &entry->drpnona664, 7,  7, size, op);
	sja1105_packing(buf, &entry->drpdtag,    6,  6, size, op);
	sja1105_packing(buf, &entry->drpuntag,   5,  5, size, op);
	sja1105_packing(buf, &entry->retag,      4,  4, size, op);
	sja1105_packing(buf, &entry->dyn_learn,  3,  3, size, op);
	sja1105_packing(buf, &entry->egress,     2,  2, size, op);
	sja1105_packing(buf, &entry->ingress,    1,  1, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105pqrs_mac_config_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY;
	काष्ठा sja1105_mac_config_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 104; i < 8; i++, offset += 19) अणु
		sja1105_packing(buf, &entry->enabled[i],
				offset +  0, offset +  0, size, op);
		sja1105_packing(buf, &entry->base[i],
				offset +  9, offset +  1, size, op);
		sja1105_packing(buf, &entry->top[i],
				offset + 18, offset + 10, size, op);
	पूर्ण
	sja1105_packing(buf, &entry->अगरg,       103, 99, size, op);
	sja1105_packing(buf, &entry->speed,      98, 97, size, op);
	sja1105_packing(buf, &entry->tp_delin,   96, 81, size, op);
	sja1105_packing(buf, &entry->tp_delout,  80, 65, size, op);
	sja1105_packing(buf, &entry->maxage,     64, 57, size, op);
	sja1105_packing(buf, &entry->vlanprio,   56, 54, size, op);
	sja1105_packing(buf, &entry->vlanid,     53, 42, size, op);
	sja1105_packing(buf, &entry->ing_mirr,   41, 41, size, op);
	sja1105_packing(buf, &entry->egr_mirr,   40, 40, size, op);
	sja1105_packing(buf, &entry->drpnona664, 39, 39, size, op);
	sja1105_packing(buf, &entry->drpdtag,    38, 38, size, op);
	sja1105_packing(buf, &entry->drpuntag,   35, 35, size, op);
	sja1105_packing(buf, &entry->retag,      34, 34, size, op);
	sja1105_packing(buf, &entry->dyn_learn,  33, 33, size, op);
	sja1105_packing(buf, &entry->egress,     32, 32, size, op);
	sja1105_packing(buf, &entry->ingress,    31, 31, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार
sja1105_schedule_entry_poपूर्णांकs_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						   क्रमागत packing_op op)
अणु
	काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_PARAMS_ENTRY;

	sja1105_packing(buf, &entry->clksrc,    31, 30, size, op);
	sja1105_packing(buf, &entry->actsubsch, 29, 27, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार
sja1105_schedule_entry_poपूर्णांकs_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op)
अणु
	काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_ENTRY;

	sja1105_packing(buf, &entry->subschindx, 31, 29, size, op);
	sja1105_packing(buf, &entry->delta,      28, 11, size, op);
	sja1105_packing(buf, &entry->address,    10, 1,  size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_schedule_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						    क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY;
	काष्ठा sja1105_schedule_params_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 16; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entry->subscheind[i],
				offset + 9, offset + 0, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_schedule_entry_packing(व्योम *buf, व्योम *entry_ptr,
					     क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_SCHEDULE_ENTRY;
	काष्ठा sja1105_schedule_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->winstindex,  63, 54, size, op);
	sja1105_packing(buf, &entry->winend,      53, 53, size, op);
	sja1105_packing(buf, &entry->winst,       52, 52, size, op);
	sja1105_packing(buf, &entry->destports,   51, 47, size, op);
	sja1105_packing(buf, &entry->setvalid,    46, 46, size, op);
	sja1105_packing(buf, &entry->txen,        45, 45, size, op);
	sja1105_packing(buf, &entry->resmedia_en, 44, 44, size, op);
	sja1105_packing(buf, &entry->resmedia,    43, 36, size, op);
	sja1105_packing(buf, &entry->vlindex,     35, 26, size, op);
	sja1105_packing(buf, &entry->delta,       25, 8,  size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार
sja1105_vl_क्रमwarding_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					   क्रमागत packing_op op)
अणु
	काष्ठा sja1105_vl_क्रमwarding_params_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_VL_FORWARDING_PARAMS_ENTRY;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 16; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entry->partspc[i],
				offset + 9, offset + 0, size, op);
	sja1105_packing(buf, &entry->debugen, 15, 15, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_vl_क्रमwarding_entry_packing(व्योम *buf, व्योम *entry_ptr,
						  क्रमागत packing_op op)
अणु
	काष्ठा sja1105_vl_क्रमwarding_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_VL_FORWARDING_ENTRY;

	sja1105_packing(buf, &entry->type,      31, 31, size, op);
	sja1105_packing(buf, &entry->priority,  30, 28, size, op);
	sja1105_packing(buf, &entry->partition, 27, 25, size, op);
	sja1105_packing(buf, &entry->destports, 24, 20, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105_vl_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
				       क्रमागत packing_op op)
अणु
	काष्ठा sja1105_vl_lookup_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_VL_LOOKUP_ENTRY;

	अगर (entry->क्रमmat == SJA1105_VL_FORMAT_PSFP) अणु
		/* Interpreting vllupक्रमmat as 0 */
		sja1105_packing(buf, &entry->destports,
				95, 91, size, op);
		sja1105_packing(buf, &entry->iscritical,
				90, 90, size, op);
		sja1105_packing(buf, &entry->macaddr,
				89, 42, size, op);
		sja1105_packing(buf, &entry->vlanid,
				41, 30, size, op);
		sja1105_packing(buf, &entry->port,
				29, 27, size, op);
		sja1105_packing(buf, &entry->vlanprior,
				26, 24, size, op);
	पूर्ण अन्यथा अणु
		/* Interpreting vllupक्रमmat as 1 */
		sja1105_packing(buf, &entry->egrmirr,
				95, 91, size, op);
		sja1105_packing(buf, &entry->ingrmirr,
				90, 90, size, op);
		sja1105_packing(buf, &entry->vlid,
				57, 42, size, op);
		sja1105_packing(buf, &entry->port,
				29, 27, size, op);
	पूर्ण
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_vl_policing_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op)
अणु
	काष्ठा sja1105_vl_policing_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_VL_POLICING_ENTRY;

	sja1105_packing(buf, &entry->type,      63, 63, size, op);
	sja1105_packing(buf, &entry->maxlen,    62, 52, size, op);
	sja1105_packing(buf, &entry->sharindx,  51, 42, size, op);
	अगर (entry->type == 0) अणु
		sja1105_packing(buf, &entry->bag,    41, 28, size, op);
		sja1105_packing(buf, &entry->jitter, 27, 18, size, op);
	पूर्ण
	वापस size;
पूर्ण

माप_प्रकार sja1105_vlan_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY;
	काष्ठा sja1105_vlan_lookup_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->ving_mirr,  63, 59, size, op);
	sja1105_packing(buf, &entry->vegr_mirr,  58, 54, size, op);
	sja1105_packing(buf, &entry->vmemb_port, 53, 49, size, op);
	sja1105_packing(buf, &entry->vlan_bc,    48, 44, size, op);
	sja1105_packing(buf, &entry->tag_port,   43, 39, size, op);
	sja1105_packing(buf, &entry->vlanid,     38, 27, size, op);
	वापस size;
पूर्ण

अटल माप_प्रकार sja1105_xmii_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_XMII_PARAMS_ENTRY;
	काष्ठा sja1105_xmii_params_entry *entry = entry_ptr;
	पूर्णांक offset, i;

	क्रम (i = 0, offset = 17; i < 5; i++, offset += 3) अणु
		sja1105_packing(buf, &entry->xmii_mode[i],
				offset + 1, offset + 0, size, op);
		sja1105_packing(buf, &entry->phy_mac[i],
				offset + 2, offset + 2, size, op);
	पूर्ण
	वापस size;
पूर्ण

माप_प्रकार sja1105_retagging_entry_packing(व्योम *buf, व्योम *entry_ptr,
				       क्रमागत packing_op op)
अणु
	काष्ठा sja1105_retagging_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105_SIZE_RETAGGING_ENTRY;

	sja1105_packing(buf, &entry->egr_port,       63, 59, size, op);
	sja1105_packing(buf, &entry->ing_port,       58, 54, size, op);
	sja1105_packing(buf, &entry->vlan_ing,       53, 42, size, op);
	sja1105_packing(buf, &entry->vlan_egr,       41, 30, size, op);
	sja1105_packing(buf, &entry->करो_not_learn,   29, 29, size, op);
	sja1105_packing(buf, &entry->use_dest_ports, 28, 28, size, op);
	sja1105_packing(buf, &entry->destports,      27, 23, size, op);
	वापस size;
पूर्ण

माप_प्रकार sja1105_table_header_packing(व्योम *buf, व्योम *entry_ptr,
				    क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105_SIZE_TABLE_HEADER;
	काष्ठा sja1105_table_header *entry = entry_ptr;

	sja1105_packing(buf, &entry->block_id, 31, 24, size, op);
	sja1105_packing(buf, &entry->len,      55, 32, size, op);
	sja1105_packing(buf, &entry->crc,      95, 64, size, op);
	वापस size;
पूर्ण

/* WARNING: the *hdr poपूर्णांकer is really non-स्थिर, because it is
 * modअगरying the CRC of the header क्रम a 2-stage packing operation
 */
व्योम
sja1105_table_header_pack_with_crc(व्योम *buf, काष्ठा sja1105_table_header *hdr)
अणु
	/* First pack the table as-is, then calculate the CRC, and
	 * finally put the proper CRC पूर्णांकo the packed buffer
	 */
	स_रखो(buf, 0, SJA1105_SIZE_TABLE_HEADER);
	sja1105_table_header_packing(buf, hdr, PACK);
	hdr->crc = sja1105_crc32(buf, SJA1105_SIZE_TABLE_HEADER - 4);
	sja1105_pack(buf + SJA1105_SIZE_TABLE_HEADER - 4, &hdr->crc, 31, 0, 4);
पूर्ण

अटल व्योम sja1105_table_ग_लिखो_crc(u8 *table_start, u8 *crc_ptr)
अणु
	u64 computed_crc;
	पूर्णांक len_bytes;

	len_bytes = (uपूर्णांकptr_t)(crc_ptr - table_start);
	computed_crc = sja1105_crc32(table_start, len_bytes);
	sja1105_pack(crc_ptr, &computed_crc, 31, 0, 4);
पूर्ण

/* The block IDs that the चयनes support are unक्रमtunately sparse, so keep a
 * mapping table to "block indices" and translate back and क्रमth so that we
 * करोn't waste useless memory in काष्ठा sja1105_अटल_config.
 * Also, since the block id comes from essentially untrusted input (unpacking
 * the अटल config from userspace) it has to be sanitized (range-checked)
 * beक्रमe blindly indexing kernel memory with the blk_idx.
 */
अटल u64 blk_id_map[BLK_IDX_MAX] = अणु
	[BLK_IDX_SCHEDULE] = BLKID_SCHEDULE,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS] = BLKID_SCHEDULE_ENTRY_POINTS,
	[BLK_IDX_VL_LOOKUP] = BLKID_VL_LOOKUP,
	[BLK_IDX_VL_POLICING] = BLKID_VL_POLICING,
	[BLK_IDX_VL_FORWARDING] = BLKID_VL_FORWARDING,
	[BLK_IDX_L2_LOOKUP] = BLKID_L2_LOOKUP,
	[BLK_IDX_L2_POLICING] = BLKID_L2_POLICING,
	[BLK_IDX_VLAN_LOOKUP] = BLKID_VLAN_LOOKUP,
	[BLK_IDX_L2_FORWARDING] = BLKID_L2_FORWARDING,
	[BLK_IDX_MAC_CONFIG] = BLKID_MAC_CONFIG,
	[BLK_IDX_SCHEDULE_PARAMS] = BLKID_SCHEDULE_PARAMS,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS] = BLKID_SCHEDULE_ENTRY_POINTS_PARAMS,
	[BLK_IDX_VL_FORWARDING_PARAMS] = BLKID_VL_FORWARDING_PARAMS,
	[BLK_IDX_L2_LOOKUP_PARAMS] = BLKID_L2_LOOKUP_PARAMS,
	[BLK_IDX_L2_FORWARDING_PARAMS] = BLKID_L2_FORWARDING_PARAMS,
	[BLK_IDX_AVB_PARAMS] = BLKID_AVB_PARAMS,
	[BLK_IDX_GENERAL_PARAMS] = BLKID_GENERAL_PARAMS,
	[BLK_IDX_RETAGGING] = BLKID_RETAGGING,
	[BLK_IDX_XMII_PARAMS] = BLKID_XMII_PARAMS,
पूर्ण;

स्थिर अक्षर *sja1105_अटल_config_error_msg[] = अणु
	[SJA1105_CONFIG_OK] = "",
	[SJA1105_TTETHERNET_NOT_SUPPORTED] =
		"schedule-table present, but TTEthernet is "
		"only supported on T and Q/S",
	[SJA1105_INCORRECT_TTETHERNET_CONFIGURATION] =
		"schedule-table present, but one of "
		"schedule-entry-points-table, schedule-parameters-table or "
		"schedule-entry-points-parameters table is empty",
	[SJA1105_INCORRECT_VIRTUAL_LINK_CONFIGURATION] =
		"vl-lookup-table present, but one of vl-policing-table, "
		"vl-forwarding-table or vl-forwarding-parameters-table is empty",
	[SJA1105_MISSING_L2_POLICING_TABLE] =
		"l2-policing-table needs to have at least one entry",
	[SJA1105_MISSING_L2_FORWARDING_TABLE] =
		"l2-forwarding-table is either missing or incomplete",
	[SJA1105_MISSING_L2_FORWARDING_PARAMS_TABLE] =
		"l2-forwarding-parameters-table is missing",
	[SJA1105_MISSING_GENERAL_PARAMS_TABLE] =
		"general-parameters-table is missing",
	[SJA1105_MISSING_VLAN_TABLE] =
		"vlan-lookup-table needs to have at least the default untagged VLAN",
	[SJA1105_MISSING_XMII_TABLE] =
		"xmii-table is missing",
	[SJA1105_MISSING_MAC_TABLE] =
		"mac-configuration-table needs to contain an entry for each port",
	[SJA1105_OVERCOMMITTED_FRAME_MEMORY] =
		"Not allowed to overcommit frame memory. L2 memory partitions "
		"and VL memory partitions share the same space. The sum of all "
		"16 memory partitions is not allowed to be larger than 929 "
		"128-byte blocks (or 910 with retagging). Please adjust "
		"l2-forwarding-parameters-table.part_spc and/or "
		"vl-forwarding-parameters-table.partspc.",
पूर्ण;

अटल sja1105_config_valid_t
अटल_config_check_memory_size(स्थिर काष्ठा sja1105_table *tables)
अणु
	स्थिर काष्ठा sja1105_l2_क्रमwarding_params_entry *l2_fwd_params;
	स्थिर काष्ठा sja1105_vl_क्रमwarding_params_entry *vl_fwd_params;
	पूर्णांक i, max_mem, mem = 0;

	l2_fwd_params = tables[BLK_IDX_L2_FORWARDING_PARAMS].entries;

	क्रम (i = 0; i < 8; i++)
		mem += l2_fwd_params->part_spc[i];

	अगर (tables[BLK_IDX_VL_FORWARDING_PARAMS].entry_count) अणु
		vl_fwd_params = tables[BLK_IDX_VL_FORWARDING_PARAMS].entries;
		क्रम (i = 0; i < 8; i++)
			mem += vl_fwd_params->partspc[i];
	पूर्ण

	अगर (tables[BLK_IDX_RETAGGING].entry_count)
		max_mem = SJA1105_MAX_FRAME_MEMORY_RETAGGING;
	अन्यथा
		max_mem = SJA1105_MAX_FRAME_MEMORY;

	अगर (mem > max_mem)
		वापस SJA1105_OVERCOMMITTED_FRAME_MEMORY;

	वापस SJA1105_CONFIG_OK;
पूर्ण

sja1105_config_valid_t
sja1105_अटल_config_check_valid(स्थिर काष्ठा sja1105_अटल_config *config)
अणु
	स्थिर काष्ठा sja1105_table *tables = config->tables;
#घोषणा IS_FULL(blk_idx) \
	(tables[blk_idx].entry_count == tables[blk_idx].ops->max_entry_count)

	अगर (tables[BLK_IDX_SCHEDULE].entry_count) अणु
		अगर (config->device_id != SJA1105T_DEVICE_ID &&
		    config->device_id != SJA1105QS_DEVICE_ID)
			वापस SJA1105_TTETHERNET_NOT_SUPPORTED;

		अगर (tables[BLK_IDX_SCHEDULE_ENTRY_POINTS].entry_count == 0)
			वापस SJA1105_INCORRECT_TTETHERNET_CONFIGURATION;

		अगर (!IS_FULL(BLK_IDX_SCHEDULE_PARAMS))
			वापस SJA1105_INCORRECT_TTETHERNET_CONFIGURATION;

		अगर (!IS_FULL(BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS))
			वापस SJA1105_INCORRECT_TTETHERNET_CONFIGURATION;
	पूर्ण
	अगर (tables[BLK_IDX_VL_LOOKUP].entry_count) अणु
		काष्ठा sja1105_vl_lookup_entry *vl_lookup;
		bool has_critical_links = false;
		पूर्णांक i;

		vl_lookup = tables[BLK_IDX_VL_LOOKUP].entries;

		क्रम (i = 0; i < tables[BLK_IDX_VL_LOOKUP].entry_count; i++) अणु
			अगर (vl_lookup[i].iscritical) अणु
				has_critical_links = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (tables[BLK_IDX_VL_POLICING].entry_count == 0 &&
		    has_critical_links)
			वापस SJA1105_INCORRECT_VIRTUAL_LINK_CONFIGURATION;

		अगर (tables[BLK_IDX_VL_FORWARDING].entry_count == 0 &&
		    has_critical_links)
			वापस SJA1105_INCORRECT_VIRTUAL_LINK_CONFIGURATION;

		अगर (tables[BLK_IDX_VL_FORWARDING_PARAMS].entry_count == 0 &&
		    has_critical_links)
			वापस SJA1105_INCORRECT_VIRTUAL_LINK_CONFIGURATION;
	पूर्ण

	अगर (tables[BLK_IDX_L2_POLICING].entry_count == 0)
		वापस SJA1105_MISSING_L2_POLICING_TABLE;

	अगर (tables[BLK_IDX_VLAN_LOOKUP].entry_count == 0)
		वापस SJA1105_MISSING_VLAN_TABLE;

	अगर (!IS_FULL(BLK_IDX_L2_FORWARDING))
		वापस SJA1105_MISSING_L2_FORWARDING_TABLE;

	अगर (!IS_FULL(BLK_IDX_MAC_CONFIG))
		वापस SJA1105_MISSING_MAC_TABLE;

	अगर (!IS_FULL(BLK_IDX_L2_FORWARDING_PARAMS))
		वापस SJA1105_MISSING_L2_FORWARDING_PARAMS_TABLE;

	अगर (!IS_FULL(BLK_IDX_GENERAL_PARAMS))
		वापस SJA1105_MISSING_GENERAL_PARAMS_TABLE;

	अगर (!IS_FULL(BLK_IDX_XMII_PARAMS))
		वापस SJA1105_MISSING_XMII_TABLE;

	वापस अटल_config_check_memory_size(tables);
#अघोषित IS_FULL
पूर्ण

व्योम
sja1105_अटल_config_pack(व्योम *buf, काष्ठा sja1105_अटल_config *config)
अणु
	काष्ठा sja1105_table_header header = अणु0पूर्ण;
	क्रमागत sja1105_blk_idx i;
	अक्षर *p = buf;
	पूर्णांक j;

	sja1105_pack(p, &config->device_id, 31, 0, 4);
	p += SJA1105_SIZE_DEVICE_ID;

	क्रम (i = 0; i < BLK_IDX_MAX; i++) अणु
		स्थिर काष्ठा sja1105_table *table;
		अक्षर *table_start;

		table = &config->tables[i];
		अगर (!table->entry_count)
			जारी;

		header.block_id = blk_id_map[i];
		header.len = table->entry_count *
			     table->ops->packed_entry_size / 4;
		sja1105_table_header_pack_with_crc(p, &header);
		p += SJA1105_SIZE_TABLE_HEADER;
		table_start = p;
		क्रम (j = 0; j < table->entry_count; j++) अणु
			u8 *entry_ptr = table->entries;

			entry_ptr += j * table->ops->unpacked_entry_size;
			स_रखो(p, 0, table->ops->packed_entry_size);
			table->ops->packing(p, entry_ptr, PACK);
			p += table->ops->packed_entry_size;
		पूर्ण
		sja1105_table_ग_लिखो_crc(table_start, p);
		p += 4;
	पूर्ण
	/* Final header:
	 * Block ID करोes not matter
	 * Length of 0 marks that header is final
	 * CRC will be replaced on-the-fly on "config upload"
	 */
	header.block_id = 0;
	header.len = 0;
	header.crc = 0xDEADBEEF;
	स_रखो(p, 0, SJA1105_SIZE_TABLE_HEADER);
	sja1105_table_header_packing(p, &header, PACK);
पूर्ण

माप_प्रकार
sja1105_अटल_config_get_length(स्थिर काष्ठा sja1105_अटल_config *config)
अणु
	अचिन्हित पूर्णांक sum;
	अचिन्हित पूर्णांक header_count;
	क्रमागत sja1105_blk_idx i;

	/* Ending header */
	header_count = 1;
	sum = SJA1105_SIZE_DEVICE_ID;

	/* Tables (headers and entries) */
	क्रम (i = 0; i < BLK_IDX_MAX; i++) अणु
		स्थिर काष्ठा sja1105_table *table;

		table = &config->tables[i];
		अगर (table->entry_count)
			header_count++;

		sum += table->ops->packed_entry_size * table->entry_count;
	पूर्ण
	/* Headers have an additional CRC at the end */
	sum += header_count * (SJA1105_SIZE_TABLE_HEADER + 4);
	/* Last header करोes not have an extra CRC because there is no data */
	sum -= 4;

	वापस sum;
पूर्ण

/* Compatibility matrices */

/* SJA1105E: First generation, no TTEthernet */
स्थिर काष्ठा sja1105_table_ops sja1105e_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105et_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105ET_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105et_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105ET_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105et_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105et_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105et_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

/* SJA1105T: First generation, TTEthernet */
स्थिर काष्ठा sja1105_table_ops sja1105t_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_SCHEDULE] = अणु
		.packing = sja1105_schedule_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_LOOKUP] = अणु
		.packing = sja1105_vl_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VL_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_VL_POLICING] = अणु
		.packing = sja1105_vl_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_policing_entry),
		.packed_entry_size = SJA1105_SIZE_VL_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING] = अणु
		.packing = sja1105_vl_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105et_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105ET_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105et_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105ET_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_PARAMS] = अणु
		.packing = sja1105_schedule_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING_PARAMS] = अणु
		.packing = sja1105_vl_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105et_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105et_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105et_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105ET_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

/* SJA1105P: Second generation, no TTEthernet, no SGMII */
स्थिर काष्ठा sja1105_table_ops sja1105p_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105pqrs_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105pqrs_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105pqrs_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105pqrs_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105pqrs_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

/* SJA1105Q: Second generation, TTEthernet, no SGMII */
स्थिर काष्ठा sja1105_table_ops sja1105q_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_SCHEDULE] = अणु
		.packing = sja1105_schedule_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_LOOKUP] = अणु
		.packing = sja1105_vl_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VL_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_VL_POLICING] = अणु
		.packing = sja1105_vl_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_policing_entry),
		.packed_entry_size = SJA1105_SIZE_VL_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING] = अणु
		.packing = sja1105_vl_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105pqrs_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105pqrs_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_PARAMS] = अणु
		.packing = sja1105_schedule_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING_PARAMS] = अणु
		.packing = sja1105_vl_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105pqrs_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105pqrs_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105pqrs_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

/* SJA1105R: Second generation, no TTEthernet, SGMII */
स्थिर काष्ठा sja1105_table_ops sja1105r_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105pqrs_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105pqrs_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105pqrs_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105pqrs_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105pqrs_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

/* SJA1105S: Second generation, TTEthernet, SGMII */
स्थिर काष्ठा sja1105_table_ops sja1105s_table_ops[BLK_IDX_MAX] = अणु
	[BLK_IDX_SCHEDULE] = अणु
		.packing = sja1105_schedule_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_LOOKUP] = अणु
		.packing = sja1105_vl_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VL_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_VL_POLICING] = अणु
		.packing = sja1105_vl_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_policing_entry),
		.packed_entry_size = SJA1105_SIZE_VL_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING] = अणु
		.packing = sja1105_vl_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP] = अणु
		.packing = sja1105pqrs_l2_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_POLICING] = अणु
		.packing = sja1105_l2_policing_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_policing_entry),
		.packed_entry_size = SJA1105_SIZE_L2_POLICING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_POLICING_COUNT,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.packing = sja1105_vlan_lookup_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vlan_lookup_entry),
		.packed_entry_size = SJA1105_SIZE_VLAN_LOOKUP_ENTRY,
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.packing = sja1105_l2_क्रमwarding_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.packing = sja1105pqrs_mac_config_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_mac_config_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_PARAMS] = अणु
		.packing = sja1105_schedule_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS] = अणु
		.packing = sja1105_schedule_entry_poपूर्णांकs_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry),
		.packed_entry_size = SJA1105_SIZE_SCHEDULE_ENTRY_POINTS_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_VL_FORWARDING_PARAMS] = अणु
		.packing = sja1105_vl_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_vl_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_VL_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_VL_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.packing = sja1105pqrs_l2_lookup_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_lookup_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING_PARAMS] = अणु
		.packing = sja1105_l2_क्रमwarding_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_l2_क्रमwarding_params_entry),
		.packed_entry_size = SJA1105_SIZE_L2_FORWARDING_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.packing = sja1105pqrs_avb_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_avb_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.packing = sja1105pqrs_general_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_general_params_entry),
		.packed_entry_size = SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.packing = sja1105_retagging_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_retagging_entry),
		.packed_entry_size = SJA1105_SIZE_RETAGGING_ENTRY,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
	पूर्ण,
	[BLK_IDX_XMII_PARAMS] = अणु
		.packing = sja1105_xmii_params_entry_packing,
		.unpacked_entry_size = माप(काष्ठा sja1105_xmii_params_entry),
		.packed_entry_size = SJA1105_SIZE_XMII_PARAMS_ENTRY,
		.max_entry_count = SJA1105_MAX_XMII_PARAMS_COUNT,
	पूर्ण,
पूर्ण;

पूर्णांक sja1105_अटल_config_init(काष्ठा sja1105_अटल_config *config,
			       स्थिर काष्ठा sja1105_table_ops *अटल_ops,
			       u64 device_id)
अणु
	क्रमागत sja1105_blk_idx i;

	*config = (काष्ठा sja1105_अटल_config) अणु0पूर्ण;

	/* Transfer अटल_ops array from priv पूर्णांकo per-table ops
	 * क्रम handier access
	 */
	क्रम (i = 0; i < BLK_IDX_MAX; i++)
		config->tables[i].ops = &अटल_ops[i];

	config->device_id = device_id;
	वापस 0;
पूर्ण

व्योम sja1105_अटल_config_मुक्त(काष्ठा sja1105_अटल_config *config)
अणु
	क्रमागत sja1105_blk_idx i;

	क्रम (i = 0; i < BLK_IDX_MAX; i++) अणु
		अगर (config->tables[i].entry_count) अणु
			kमुक्त(config->tables[i].entries);
			config->tables[i].entry_count = 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक sja1105_table_delete_entry(काष्ठा sja1105_table *table, पूर्णांक i)
अणु
	माप_प्रकार entry_size = table->ops->unpacked_entry_size;
	u8 *entries = table->entries;

	अगर (i > table->entry_count)
		वापस -दुस्फल;

	स_हटाओ(entries + i * entry_size, entries + (i + 1) * entry_size,
		(table->entry_count - i) * entry_size);

	table->entry_count--;

	वापस 0;
पूर्ण

/* No poपूर्णांकers to table->entries should be kept when this is called. */
पूर्णांक sja1105_table_resize(काष्ठा sja1105_table *table, माप_प्रकार new_count)
अणु
	माप_प्रकार entry_size = table->ops->unpacked_entry_size;
	व्योम *new_entries, *old_entries = table->entries;

	अगर (new_count > table->ops->max_entry_count)
		वापस -दुस्फल;

	new_entries = kसुस्मृति(new_count, entry_size, GFP_KERNEL);
	अगर (!new_entries)
		वापस -ENOMEM;

	स_नकल(new_entries, old_entries, min(new_count, table->entry_count) *
		entry_size);

	table->entries = new_entries;
	table->entry_count = new_count;
	kमुक्त(old_entries);
	वापस 0;
पूर्ण
