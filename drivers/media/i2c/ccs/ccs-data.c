<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * CCS अटल data binary parser library
 *
 * Copyright 2019--2020 Intel Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "ccs-data-defs.h"

काष्ठा bin_container अणु
	व्योम *base;
	व्योम *now;
	व्योम *end;
	माप_प्रकार size;
पूर्ण;

अटल व्योम *bin_alloc(काष्ठा bin_container *bin, माप_प्रकार len)
अणु
	व्योम *ptr;

	len = ALIGN(len, 8);

	अगर (bin->end - bin->now < len)
		वापस शून्य;

	ptr = bin->now;
	bin->now += len;

	वापस ptr;
पूर्ण

अटल व्योम bin_reserve(काष्ठा bin_container *bin, माप_प्रकार len)
अणु
	bin->size += ALIGN(len, 8);
पूर्ण

अटल पूर्णांक bin_backing_alloc(काष्ठा bin_container *bin)
अणु
	bin->base = bin->now = kvzalloc(bin->size, GFP_KERNEL);
	अगर (!bin->base)
		वापस -ENOMEM;

	bin->end = bin->base + bin->size;

	वापस 0;
पूर्ण

#घोषणा is_contained(var, endp)				\
	(माप(*var) <= (endp) - (व्योम *)(var))
#घोषणा has_headroom(ptr, headroom, endp)	\
	((headroom) <= (endp) - (व्योम *)(ptr))
#घोषणा is_contained_with_headroom(var, headroom, endp)		\
	(माप(*var) + (headroom) <= (endp) - (व्योम *)(var))

अटल पूर्णांक
ccs_data_parse_length_specअगरier(स्थिर काष्ठा __ccs_data_length_specअगरier *__len,
				माप_प्रकार *__hlen, माप_प्रकार *__plen,
				स्थिर व्योम *endp)
अणु
	माप_प्रकार hlen, plen;

	अगर (!is_contained(__len, endp))
		वापस -ENODATA;

	चयन (__len->length >> CCS_DATA_LENGTH_SPECIFIER_SIZE_SHIFT) अणु
	हाल CCS_DATA_LENGTH_SPECIFIER_1:
		hlen = माप(*__len);
		plen = __len->length &
			((1 << CCS_DATA_LENGTH_SPECIFIER_SIZE_SHIFT) - 1);
		अवरोध;
	हाल CCS_DATA_LENGTH_SPECIFIER_2: अणु
		काष्ठा __ccs_data_length_specअगरier2 *__len2 = (व्योम *)__len;

		अगर (!is_contained(__len2, endp))
			वापस -ENODATA;

		hlen = माप(*__len2);
		plen = ((माप_प्रकार)
			(__len2->length[0] &
			 ((1 << CCS_DATA_LENGTH_SPECIFIER_SIZE_SHIFT) - 1))
			<< 8) + __len2->length[1];
		अवरोध;
	पूर्ण
	हाल CCS_DATA_LENGTH_SPECIFIER_3: अणु
		काष्ठा __ccs_data_length_specअगरier3 *__len3 = (व्योम *)__len;

		अगर (!is_contained(__len3, endp))
			वापस -ENODATA;

		hlen = माप(*__len3);
		plen = ((माप_प्रकार)
			(__len3->length[0] &
			 ((1 << CCS_DATA_LENGTH_SPECIFIER_SIZE_SHIFT) - 1))
			<< 16) + (__len3->length[0] << 8) + __len3->length[1];
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!has_headroom(__len, hlen + plen, endp))
		वापस -ENODATA;

	*__hlen = hlen;
	*__plen = plen;

	वापस 0;
पूर्ण

अटल u8
ccs_data_parse_क्रमmat_version(स्थिर काष्ठा __ccs_data_block *block)
अणु
	वापस block->id >> CCS_DATA_BLOCK_HEADER_ID_VERSION_SHIFT;
पूर्ण

अटल u8 ccs_data_parse_block_id(स्थिर काष्ठा __ccs_data_block *block,
				       bool is_first)
अणु
	अगर (!is_first)
		वापस block->id;

	वापस block->id & ((1 << CCS_DATA_BLOCK_HEADER_ID_VERSION_SHIFT) - 1);
पूर्ण

अटल पूर्णांक ccs_data_parse_version(काष्ठा bin_container *bin,
				  काष्ठा ccs_data_container *ccsdata,
				  स्थिर व्योम *payload, स्थिर व्योम *endp)
अणु
	स्थिर काष्ठा __ccs_data_block_version *v = payload;
	काष्ठा ccs_data_block_version *vv;

	अगर (v + 1 != endp)
		वापस -ENODATA;

	अगर (!bin->base) अणु
		bin_reserve(bin, माप(*ccsdata->version));
		वापस 0;
	पूर्ण

	ccsdata->version = bin_alloc(bin, माप(*ccsdata->version));
	अगर (!ccsdata->version)
		वापस -ENOMEM;

	vv = ccsdata->version;
	vv->version_major = ((u16)v->अटल_data_version_major[0] << 8) +
		v->अटल_data_version_major[1];
	vv->version_minor = ((u16)v->अटल_data_version_minor[0] << 8) +
		v->अटल_data_version_minor[1];
	vv->date_year =  ((u16)v->year[0] << 8) + v->year[1];
	vv->date_month = v->month;
	vv->date_day = v->day;

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_ccs_data_version(काष्ठा device *dev,
				   काष्ठा ccs_data_block_version *v)
अणु
	dev_dbg(dev,
		"static data version %4.4x.%4.4x, date %4.4u-%2.2u-%2.2u\n",
		v->version_major, v->version_minor,
		v->date_year, v->date_month, v->date_day);
पूर्ण

अटल पूर्णांक ccs_data_block_parse_header(स्थिर काष्ठा __ccs_data_block *block,
				       bool is_first, अचिन्हित पूर्णांक *__block_id,
				       स्थिर व्योम **payload,
				       स्थिर काष्ठा __ccs_data_block **next_block,
				       स्थिर व्योम *endp, काष्ठा device *dev,
				       bool verbose)
अणु
	माप_प्रकार plen, hlen;
	u8 block_id;
	पूर्णांक rval;

	अगर (!is_contained(block, endp))
		वापस -ENODATA;

	rval = ccs_data_parse_length_specअगरier(&block->length, &hlen, &plen,
					       endp);
	अगर (rval < 0)
		वापस rval;

	block_id = ccs_data_parse_block_id(block, is_first);

	अगर (verbose)
		dev_dbg(dev,
			"Block ID 0x%2.2x, header length %zu, payload length %zu\n",
			block_id, hlen, plen);

	अगर (!has_headroom(&block->length, hlen + plen, endp))
		वापस -ENODATA;

	अगर (__block_id)
		*__block_id = block_id;

	अगर (payload)
		*payload = (व्योम *)&block->length + hlen;

	अगर (next_block)
		*next_block = (व्योम *)&block->length + hlen + plen;

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_regs(काष्ठा bin_container *bin,
			       काष्ठा ccs_reg **__regs,
			       माप_प्रकार *__num_regs, स्थिर व्योम *payload,
			       स्थिर व्योम *endp, काष्ठा device *dev)
अणु
	काष्ठा ccs_reg *regs_base = शून्य, *regs = शून्य;
	माप_प्रकार num_regs = 0;
	u16 addr = 0;

	अगर (bin->base && __regs) अणु
		regs = regs_base = bin_alloc(bin, माप(*regs) * *__num_regs);
		अगर (!regs)
			वापस -ENOMEM;
	पूर्ण

	जबतक (payload < endp && num_regs < पूर्णांक_उच्च) अणु
		स्थिर काष्ठा __ccs_data_block_regs *r = payload;
		माप_प्रकार len;
		स्थिर व्योम *data;

		अगर (!is_contained(r, endp))
			वापस -ENODATA;

		चयन (r->reg_len >> CCS_DATA_BLOCK_REGS_SEL_SHIFT) अणु
		हाल CCS_DATA_BLOCK_REGS_SEL_REGS:
			addr += r->reg_len & CCS_DATA_BLOCK_REGS_ADDR_MASK;
			len = ((r->reg_len & CCS_DATA_BLOCK_REGS_LEN_MASK)
			       >> CCS_DATA_BLOCK_REGS_LEN_SHIFT) + 1;

			अगर (!is_contained_with_headroom(r, len, endp))
				वापस -ENODATA;

			data = r + 1;
			अवरोध;
		हाल CCS_DATA_BLOCK_REGS_SEL_REGS2: अणु
			स्थिर काष्ठा __ccs_data_block_regs2 *r2 = payload;

			अगर (!is_contained(r2, endp))
				वापस -ENODATA;

			addr += ((u16)(r2->reg_len &
				       CCS_DATA_BLOCK_REGS_2_ADDR_MASK) << 8)
				+ r2->addr;
			len = ((r2->reg_len & CCS_DATA_BLOCK_REGS_2_LEN_MASK)
			       >> CCS_DATA_BLOCK_REGS_2_LEN_SHIFT) + 1;

			अगर (!is_contained_with_headroom(r2, len, endp))
				वापस -ENODATA;

			data = r2 + 1;
			अवरोध;
		पूर्ण
		हाल CCS_DATA_BLOCK_REGS_SEL_REGS3: अणु
			स्थिर काष्ठा __ccs_data_block_regs3 *r3 = payload;

			अगर (!is_contained(r3, endp))
				वापस -ENODATA;

			addr = ((u16)r3->addr[0] << 8) + r3->addr[1];
			len = (r3->reg_len & CCS_DATA_BLOCK_REGS_3_LEN_MASK) + 1;

			अगर (!is_contained_with_headroom(r3, len, endp))
				वापस -ENODATA;

			data = r3 + 1;
			अवरोध;
		पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण

		num_regs++;

		अगर (!bin->base) अणु
			bin_reserve(bin, len);
		पूर्ण अन्यथा अगर (__regs) अणु
			अगर (!regs)
				वापस -EIO;

			regs->addr = addr;
			regs->len = len;
			regs->value = bin_alloc(bin, len);
			अगर (!regs->value)
				वापस -ENOMEM;

			स_नकल(regs->value, data, len);
			regs++;
		पूर्ण

		addr += len;
		payload = data + len;
	पूर्ण

	अगर (!bin->base)
		bin_reserve(bin, माप(*regs) * num_regs);

	अगर (__num_regs)
		*__num_regs = num_regs;

	अगर (bin->base && __regs) अणु
		अगर (!regs_base)
			वापस -EIO;

		*__regs = regs_base;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_reg_rules(काष्ठा bin_container *bin,
				    काष्ठा ccs_reg **__regs,
				    माप_प्रकार *__num_regs,
				    स्थिर व्योम *payload,
				    स्थिर व्योम *endp, काष्ठा device *dev)
अणु
	पूर्णांक rval;

	अगर (!bin->base)
		वापस ccs_data_parse_regs(bin, शून्य, शून्य, payload, endp, dev);

	rval = ccs_data_parse_regs(bin, शून्य, __num_regs, payload, endp, dev);
	अगर (rval)
		वापस rval;

	वापस ccs_data_parse_regs(bin, __regs, __num_regs, payload, endp,
				   dev);
पूर्ण

अटल व्योम assign_ffd_entry(काष्ठा ccs_frame_क्रमmat_desc *desc,
			     स्थिर काष्ठा __ccs_data_block_ffd_entry *ent)
अणु
	desc->pixelcode = ent->pixelcode;
	desc->value = ((u16)ent->value[0] << 8) + ent->value[1];
पूर्ण

अटल पूर्णांक ccs_data_parse_ffd(काष्ठा bin_container *bin,
			      काष्ठा ccs_frame_क्रमmat_descs **ffd,
			      स्थिर व्योम *payload,
			      स्थिर व्योम *endp, काष्ठा device *dev)
अणु
	स्थिर काष्ठा __ccs_data_block_ffd *__ffd = payload;
	स्थिर काष्ठा __ccs_data_block_ffd_entry *__entry;
	अचिन्हित पूर्णांक i;

	अगर (!is_contained(__ffd, endp))
		वापस -ENODATA;

	अगर ((व्योम *)__ffd + माप(*__ffd) +
	    ((u32)__ffd->num_column_descs +
	     (u32)__ffd->num_row_descs) *
	    माप(काष्ठा __ccs_data_block_ffd_entry) != endp)
		वापस -ENODATA;

	अगर (!bin->base) अणु
		bin_reserve(bin, माप(**ffd));
		bin_reserve(bin, __ffd->num_column_descs *
			    माप(काष्ठा ccs_frame_क्रमmat_desc));
		bin_reserve(bin, __ffd->num_row_descs *
			    माप(काष्ठा ccs_frame_क्रमmat_desc));

		वापस 0;
	पूर्ण

	*ffd = bin_alloc(bin, माप(**ffd));
	अगर (!*ffd)
		वापस -ENOMEM;

	(*ffd)->num_column_descs = __ffd->num_column_descs;
	(*ffd)->num_row_descs = __ffd->num_row_descs;
	__entry = (व्योम *)(__ffd + 1);

	(*ffd)->column_descs = bin_alloc(bin, __ffd->num_column_descs *
					 माप(*(*ffd)->column_descs));
	अगर (!(*ffd)->column_descs)
		वापस -ENOMEM;

	क्रम (i = 0; i < __ffd->num_column_descs; i++, __entry++)
		assign_ffd_entry(&(*ffd)->column_descs[i], __entry);

	(*ffd)->row_descs = bin_alloc(bin, __ffd->num_row_descs *
				      माप(*(*ffd)->row_descs));
	अगर (!(*ffd)->row_descs)
		वापस -ENOMEM;

	क्रम (i = 0; i < __ffd->num_row_descs; i++, __entry++)
		assign_ffd_entry(&(*ffd)->row_descs[i], __entry);

	अगर (__entry != endp)
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_pdaf_पढ़ोout(काष्ठा bin_container *bin,
				       काष्ठा ccs_pdaf_पढ़ोout **pdaf_पढ़ोout,
				       स्थिर व्योम *payload,
				       स्थिर व्योम *endp, काष्ठा device *dev)
अणु
	स्थिर काष्ठा __ccs_data_block_pdaf_पढ़ोout *__pdaf = payload;

	अगर (!is_contained(__pdaf, endp))
		वापस -ENODATA;

	अगर (!bin->base) अणु
		bin_reserve(bin, माप(**pdaf_पढ़ोout));
	पूर्ण अन्यथा अणु
		*pdaf_पढ़ोout = bin_alloc(bin, माप(**pdaf_पढ़ोout));
		अगर (!*pdaf_पढ़ोout)
			वापस -ENOMEM;

		(*pdaf_पढ़ोout)->pdaf_पढ़ोout_info_order =
			__pdaf->pdaf_पढ़ोout_info_order;
	पूर्ण

	वापस ccs_data_parse_ffd(bin, !bin->base ? शून्य : &(*pdaf_पढ़ोout)->ffd,
				  __pdaf + 1, endp, dev);
पूर्ण

अटल पूर्णांक ccs_data_parse_rules(काष्ठा bin_container *bin,
				काष्ठा ccs_rule **__rules,
				माप_प्रकार *__num_rules, स्थिर व्योम *payload,
				स्थिर व्योम *endp, काष्ठा device *dev)
अणु
	काष्ठा ccs_rule *rules_base = शून्य, *rules = शून्य, *next_rule = शून्य;
	माप_प्रकार num_rules = 0;
	स्थिर व्योम *__next_rule = payload;
	पूर्णांक rval;

	अगर (bin->base) अणु
		rules_base = next_rule =
			bin_alloc(bin, माप(*rules) * *__num_rules);
		अगर (!rules_base)
			वापस -ENOMEM;
	पूर्ण

	जबतक (__next_rule < endp) अणु
		माप_प्रकार rule_hlen, rule_plen, rule_plen2;
		स्थिर u8 *__rule_type;
		स्थिर व्योम *rule_payload;

		/* Size of a single rule */
		rval = ccs_data_parse_length_specअगरier(__next_rule, &rule_hlen,
						       &rule_plen, endp);

		अगर (rval < 0)
			वापस rval;

		__rule_type = __next_rule + rule_hlen;

		अगर (!is_contained(__rule_type, endp))
			वापस -ENODATA;

		rule_payload = __rule_type + 1;
		rule_plen2 = rule_plen - माप(*__rule_type);

		चयन (*__rule_type) अणु
		हाल CCS_DATA_BLOCK_RULE_ID_IF: अणु
			स्थिर काष्ठा __ccs_data_block_rule_अगर *__अगर_rules =
				rule_payload;
			स्थिर माप_प्रकार __num_अगर_rules =
				rule_plen2 / माप(*__अगर_rules);
			काष्ठा ccs_अगर_rule *अगर_rule;

			अगर (!has_headroom(__अगर_rules,
					  माप(*__अगर_rules) * __num_अगर_rules,
					  rule_payload + rule_plen2))
				वापस -ENODATA;

			/* Also check there is no extra data */
			अगर (__अगर_rules + __num_अगर_rules !=
			    rule_payload + rule_plen2)
				वापस -EINVAL;

			अगर (!bin->base) अणु
				bin_reserve(bin,
					    माप(*अगर_rule) *
					    __num_अगर_rules);
				num_rules++;
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक i;

				अगर (!next_rule)
					वापस -EIO;

				rules = next_rule;
				next_rule++;

				अगर_rule = bin_alloc(bin,
						    माप(*अगर_rule) *
						    __num_अगर_rules);
				अगर (!अगर_rule)
					वापस -ENOMEM;

				क्रम (i = 0; i < __num_अगर_rules; i++) अणु
					अगर_rule[i].addr =
						((u16)__अगर_rules[i].addr[0]
						 << 8) +
						__अगर_rules[i].addr[1];
					अगर_rule[i].value = __अगर_rules[i].value;
					अगर_rule[i].mask = __अगर_rules[i].mask;
				पूर्ण

				rules->अगर_rules = अगर_rule;
				rules->num_अगर_rules = __num_अगर_rules;
			पूर्ण
			अवरोध;
		पूर्ण
		हाल CCS_DATA_BLOCK_RULE_ID_READ_ONLY_REGS:
			rval = ccs_data_parse_reg_rules(bin, &rules->पढ़ो_only_regs,
							&rules->num_पढ़ो_only_regs,
							rule_payload,
							rule_payload + rule_plen2,
							dev);
			अगर (rval)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_RULE_ID_FFD:
			rval = ccs_data_parse_ffd(bin, &rules->frame_क्रमmat,
						  rule_payload,
						  rule_payload + rule_plen2,
						  dev);
			अगर (rval)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_RULE_ID_MSR:
			rval = ccs_data_parse_reg_rules(bin,
							&rules->manufacturer_regs,
							&rules->num_manufacturer_regs,
							rule_payload,
							rule_payload + rule_plen2,
							dev);
			अगर (rval)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_RULE_ID_PDAF_READOUT:
			rval = ccs_data_parse_pdaf_पढ़ोout(bin,
							   &rules->pdaf_पढ़ोout,
							   rule_payload,
							   rule_payload + rule_plen2,
							   dev);
			अगर (rval)
				वापस rval;
			अवरोध;
		शेष:
			dev_dbg(dev,
				"Don't know how to handle rule type %u!\n",
				*__rule_type);
			वापस -EINVAL;
		पूर्ण
		__next_rule = __next_rule + rule_hlen + rule_plen;
	पूर्ण

	अगर (!bin->base) अणु
		bin_reserve(bin, माप(*rules) * num_rules);
		*__num_rules = num_rules;
	पूर्ण अन्यथा अणु
		अगर (!rules_base)
			वापस -EIO;

		*__rules = rules_base;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_pdaf(काष्ठा bin_container *bin, काष्ठा ccs_pdaf_pix_loc **pdaf,
			       स्थिर व्योम *payload, स्थिर व्योम *endp,
			       काष्ठा device *dev)
अणु
	स्थिर काष्ठा __ccs_data_block_pdaf_pix_loc *__pdaf = payload;
	स्थिर काष्ठा __ccs_data_block_pdaf_pix_loc_block_desc_group *__bdesc_group;
	स्थिर काष्ठा __ccs_data_block_pdaf_pix_loc_pixel_desc *__pixel_desc;
	अचिन्हित पूर्णांक i;
	u16 num_block_desc_groups;
	u8 max_block_type_id = 0;
	स्थिर u8 *__num_pixel_descs;

	अगर (!is_contained(__pdaf, endp))
		वापस -ENODATA;

	अगर (bin->base) अणु
		*pdaf = bin_alloc(bin, माप(**pdaf));
		अगर (!*pdaf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		bin_reserve(bin, माप(**pdaf));
	पूर्ण

	num_block_desc_groups =
		((u16)__pdaf->num_block_desc_groups[0] << 8) +
		__pdaf->num_block_desc_groups[1];

	अगर (bin->base) अणु
		(*pdaf)->मुख्य_offset_x =
			((u16)__pdaf->मुख्य_offset_x[0] << 8) +
			__pdaf->मुख्य_offset_x[1];
		(*pdaf)->मुख्य_offset_y =
			((u16)__pdaf->मुख्य_offset_y[0] << 8) +
			__pdaf->मुख्य_offset_y[1];
		(*pdaf)->global_pdaf_type = __pdaf->global_pdaf_type;
		(*pdaf)->block_width = __pdaf->block_width;
		(*pdaf)->block_height = __pdaf->block_height;
		(*pdaf)->num_block_desc_groups = num_block_desc_groups;
	पूर्ण

	__bdesc_group = (स्थिर व्योम *)(__pdaf + 1);

	अगर (bin->base) अणु
		(*pdaf)->block_desc_groups =
			bin_alloc(bin,
				  माप(काष्ठा ccs_pdaf_pix_loc_block_desc_group) *
				  num_block_desc_groups);
		अगर (!(*pdaf)->block_desc_groups)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		bin_reserve(bin, माप(काष्ठा ccs_pdaf_pix_loc_block_desc_group) *
			    num_block_desc_groups);
	पूर्ण

	क्रम (i = 0; i < num_block_desc_groups; i++) अणु
		स्थिर काष्ठा __ccs_data_block_pdaf_pix_loc_block_desc *__bdesc;
		u16 num_block_descs;
		अचिन्हित पूर्णांक j;

		अगर (!is_contained(__bdesc_group, endp))
			वापस -ENODATA;

		num_block_descs =
			((u16)__bdesc_group->num_block_descs[0] << 8) +
			__bdesc_group->num_block_descs[1];

		अगर (bin->base) अणु
			(*pdaf)->block_desc_groups[i].repeat_y =
				__bdesc_group->repeat_y;
			(*pdaf)->block_desc_groups[i].num_block_descs =
				num_block_descs;
		पूर्ण

		__bdesc = (स्थिर व्योम *)(__bdesc_group + 1);

		अगर (bin->base) अणु
			(*pdaf)->block_desc_groups[i].block_descs =
				bin_alloc(bin,
					  माप(काष्ठा ccs_pdaf_pix_loc_block_desc) *
					  num_block_descs);
			अगर (!(*pdaf)->block_desc_groups[i].block_descs)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			bin_reserve(bin, माप(काष्ठा ccs_pdaf_pix_loc_block_desc) *
				    num_block_descs);
		पूर्ण

		क्रम (j = 0; j < num_block_descs; j++, __bdesc++) अणु
			काष्ठा ccs_pdaf_pix_loc_block_desc *bdesc;

			अगर (!is_contained(__bdesc, endp))
				वापस -ENODATA;

			अगर (max_block_type_id <= __bdesc->block_type_id)
				max_block_type_id = __bdesc->block_type_id + 1;

			अगर (!bin->base)
				जारी;

			bdesc = &(*pdaf)->block_desc_groups[i].block_descs[j];

			bdesc->repeat_x = ((u16)__bdesc->repeat_x[0] << 8)
				+ __bdesc->repeat_x[1];

			अगर (__bdesc->block_type_id >= num_block_descs)
				वापस -EINVAL;

			bdesc->block_type_id = __bdesc->block_type_id;
		पूर्ण

		__bdesc_group = (स्थिर व्योम *)__bdesc;
	पूर्ण

	__num_pixel_descs = (स्थिर व्योम *)__bdesc_group;

	अगर (bin->base) अणु
		(*pdaf)->pixel_desc_groups =
			bin_alloc(bin,
				  माप(काष्ठा ccs_pdaf_pix_loc_pixel_desc_group) *
				  max_block_type_id);
		अगर (!(*pdaf)->pixel_desc_groups)
			वापस -ENOMEM;
		(*pdaf)->num_pixel_desc_grups = max_block_type_id;
	पूर्ण अन्यथा अणु
		bin_reserve(bin, माप(काष्ठा ccs_pdaf_pix_loc_pixel_desc_group) *
			    max_block_type_id);
	पूर्ण

	क्रम (i = 0; i < max_block_type_id; i++) अणु
		काष्ठा ccs_pdaf_pix_loc_pixel_desc_group *pdgroup = शून्य;
		अचिन्हित पूर्णांक j;

		अगर (!is_contained(__num_pixel_descs, endp))
			वापस -ENODATA;

		अगर (bin->base) अणु
			pdgroup = &(*pdaf)->pixel_desc_groups[i];
			pdgroup->descs =
				bin_alloc(bin,
					  माप(काष्ठा ccs_pdaf_pix_loc_pixel_desc) *
					  *__num_pixel_descs);
			अगर (!pdgroup->descs)
				वापस -ENOMEM;
			pdgroup->num_descs = *__num_pixel_descs;
		पूर्ण अन्यथा अणु
			bin_reserve(bin, माप(काष्ठा ccs_pdaf_pix_loc_pixel_desc) *
				    *__num_pixel_descs);
		पूर्ण

		__pixel_desc = (स्थिर व्योम *)(__num_pixel_descs + 1);

		क्रम (j = 0; j < *__num_pixel_descs; j++, __pixel_desc++) अणु
			काष्ठा ccs_pdaf_pix_loc_pixel_desc *pdesc;

			अगर (!is_contained(__pixel_desc, endp))
				वापस -ENODATA;

			अगर (!bin->base)
				जारी;

			अगर (!pdgroup)
				वापस -EIO;

			pdesc = &pdgroup->descs[j];
			pdesc->pixel_type = __pixel_desc->pixel_type;
			pdesc->small_offset_x = __pixel_desc->small_offset_x;
			pdesc->small_offset_y = __pixel_desc->small_offset_y;
		पूर्ण

		__num_pixel_descs = (स्थिर व्योम *)(__pixel_desc + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_license(काष्ठा bin_container *bin,
				  अक्षर **__license,
				  माप_प्रकार *__license_length,
				  स्थिर व्योम *payload, स्थिर व्योम *endp)
अणु
	माप_प्रकार size = endp - payload;
	अक्षर *license;

	अगर (!bin->base) अणु
		bin_reserve(bin, size);
		वापस 0;
	पूर्ण

	license = bin_alloc(bin, size);
	अगर (!license)
		वापस -ENOMEM;

	स_नकल(license, payload, size);

	*__license = license;
	*__license_length = size;

	वापस 0;
पूर्ण

अटल पूर्णांक ccs_data_parse_end(bool *end, स्थिर व्योम *payload, स्थिर व्योम *endp,
			      काष्ठा device *dev)
अणु
	स्थिर काष्ठा __ccs_data_block_end *__end = payload;

	अगर (__end + 1 != endp) अणु
		dev_dbg(dev, "Invalid end block length %u\n",
			(अचिन्हित पूर्णांक)(endp - payload));
		वापस -ENODATA;
	पूर्ण

	*end = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __ccs_data_parse(काष्ठा bin_container *bin,
			    काष्ठा ccs_data_container *ccsdata,
			    स्थिर व्योम *data, माप_प्रकार len, काष्ठा device *dev,
			    bool verbose)
अणु
	स्थिर काष्ठा __ccs_data_block *block = data;
	स्थिर काष्ठा __ccs_data_block *endp = data + len;
	अचिन्हित पूर्णांक version;
	bool is_first = true;
	पूर्णांक rval;

	version = ccs_data_parse_क्रमmat_version(block);
	अगर (version != CCS_STATIC_DATA_VERSION) अणु
		dev_dbg(dev, "Don't know how to handle version %u\n", version);
		वापस -EINVAL;
	पूर्ण

	अगर (verbose)
		dev_dbg(dev, "Parsing CCS static data version %u\n", version);

	अगर (!bin->base)
		*ccsdata = (काष्ठा ccs_data_container)अणु 0 पूर्ण;

	जबतक (block < endp) अणु
		स्थिर काष्ठा __ccs_data_block *next_block;
		अचिन्हित पूर्णांक block_id;
		स्थिर व्योम *payload;

		rval = ccs_data_block_parse_header(block, is_first, &block_id,
						   &payload, &next_block, endp,
						   dev,
						   bin->base ? false : verbose);

		अगर (rval < 0)
			वापस rval;

		चयन (block_id) अणु
		हाल CCS_DATA_BLOCK_ID_DUMMY:
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_DATA_VERSION:
			rval = ccs_data_parse_version(bin, ccsdata, payload,
						      next_block);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_SENSOR_READ_ONLY_REGS:
			rval = ccs_data_parse_regs(
				bin, &ccsdata->sensor_पढ़ो_only_regs,
				&ccsdata->num_sensor_पढ़ो_only_regs, payload,
				next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_SENSOR_MANUFACTURER_REGS:
			rval = ccs_data_parse_regs(
				bin, &ccsdata->sensor_manufacturer_regs,
				&ccsdata->num_sensor_manufacturer_regs, payload,
				next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_MODULE_READ_ONLY_REGS:
			rval = ccs_data_parse_regs(
				bin, &ccsdata->module_पढ़ो_only_regs,
				&ccsdata->num_module_पढ़ो_only_regs, payload,
				next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_MODULE_MANUFACTURER_REGS:
			rval = ccs_data_parse_regs(
				bin, &ccsdata->module_manufacturer_regs,
				&ccsdata->num_module_manufacturer_regs, payload,
				next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_SENSOR_PDAF_PIXEL_LOCATION:
			rval = ccs_data_parse_pdaf(bin, &ccsdata->sensor_pdaf,
						   payload, next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_MODULE_PDAF_PIXEL_LOCATION:
			rval = ccs_data_parse_pdaf(bin, &ccsdata->module_pdaf,
						   payload, next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_SENSOR_RULE_BASED_BLOCK:
			rval = ccs_data_parse_rules(
				bin, &ccsdata->sensor_rules,
				&ccsdata->num_sensor_rules, payload, next_block,
				dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_MODULE_RULE_BASED_BLOCK:
			rval = ccs_data_parse_rules(
				bin, &ccsdata->module_rules,
				&ccsdata->num_module_rules, payload, next_block,
				dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_LICENSE:
			rval = ccs_data_parse_license(bin, &ccsdata->license,
						      &ccsdata->license_length,
						      payload, next_block);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		हाल CCS_DATA_BLOCK_ID_END:
			rval = ccs_data_parse_end(&ccsdata->end, payload,
						  next_block, dev);
			अगर (rval < 0)
				वापस rval;
			अवरोध;
		शेष:
			dev_dbg(dev, "WARNING: not handling block ID 0x%2.2x\n",
				block_id);
		पूर्ण

		block = next_block;
		is_first = false;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ccs_data_parse - Parse a CCS अटल data file पूर्णांकo a usable in-memory
 *		    data काष्ठाure
 * @ccsdata:	CCS अटल data in-memory data काष्ठाure
 * @data:	CCS अटल data binary
 * @len:	Length of @data
 * @dev:	Device the data is related to (used क्रम prपूर्णांकing debug messages)
 * @verbose:	Whether to be verbose or not
 */
पूर्णांक ccs_data_parse(काष्ठा ccs_data_container *ccsdata, स्थिर व्योम *data,
		   माप_प्रकार len, काष्ठा device *dev, bool verbose)
अणु
	काष्ठा bin_container bin = अणु 0 पूर्ण;
	पूर्णांक rval;

	rval = __ccs_data_parse(&bin, ccsdata, data, len, dev, verbose);
	अगर (rval)
		वापस rval;

	rval = bin_backing_alloc(&bin);
	अगर (rval)
		वापस rval;

	rval = __ccs_data_parse(&bin, ccsdata, data, len, dev, false);
	अगर (rval)
		जाओ out_मुक्त;

	अगर (verbose && ccsdata->version)
		prपूर्णांक_ccs_data_version(dev, ccsdata->version);

	अगर (bin.now != bin.end) अणु
		rval = -EPROTO;
		dev_dbg(dev, "parsing mismatch; base %p; now %p; end %p\n",
			bin.base, bin.now, bin.end);
		जाओ out_मुक्त;
	पूर्ण

	ccsdata->backing = bin.base;

	वापस 0;

out_मुक्त:
	kvमुक्त(bin.base);

	वापस rval;
पूर्ण
