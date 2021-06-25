<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Author: Roberto Sassu <roberto.sassu@polito.it>
 *
 * File: ima_ढाँचा.c
 *      Helpers to manage ढाँचा descriptors.
 */

#समावेश <linux/rculist.h>
#समावेश "ima.h"
#समावेश "ima_template_lib.h"

क्रमागत header_fields अणु HDR_PCR, HDR_DIGEST, HDR_TEMPLATE_NAME,
		     HDR_TEMPLATE_DATA, HDR__LAST पूर्ण;

अटल काष्ठा ima_ढाँचा_desc builtin_ढाँचाs[] = अणु
	अणु.name = IMA_TEMPLATE_IMA_NAME, .fmt = IMA_TEMPLATE_IMA_FMTपूर्ण,
	अणु.name = "ima-ng", .fmt = "d-ng|n-ng"पूर्ण,
	अणु.name = "ima-sig", .fmt = "d-ng|n-ng|sig"पूर्ण,
	अणु.name = "ima-buf", .fmt = "d-ng|n-ng|buf"पूर्ण,
	अणु.name = "ima-modsig", .fmt = "d-ng|n-ng|sig|d-modsig|modsig"पूर्ण,
	अणु.name = "", .fmt = ""पूर्ण,	/* placeholder क्रम a custom क्रमmat */
पूर्ण;

अटल LIST_HEAD(defined_ढाँचाs);
अटल DEFINE_SPINLOCK(ढाँचा_list);

अटल स्थिर काष्ठा ima_ढाँचा_field supported_fields[] = अणु
	अणु.field_id = "d", .field_init = ima_eventdigest_init,
	 .field_show = ima_show_ढाँचा_digestपूर्ण,
	अणु.field_id = "n", .field_init = ima_eventname_init,
	 .field_show = ima_show_ढाँचा_stringपूर्ण,
	अणु.field_id = "d-ng", .field_init = ima_eventdigest_ng_init,
	 .field_show = ima_show_ढाँचा_digest_ngपूर्ण,
	अणु.field_id = "n-ng", .field_init = ima_eventname_ng_init,
	 .field_show = ima_show_ढाँचा_stringपूर्ण,
	अणु.field_id = "sig", .field_init = ima_eventsig_init,
	 .field_show = ima_show_ढाँचा_sigपूर्ण,
	अणु.field_id = "buf", .field_init = ima_eventbuf_init,
	 .field_show = ima_show_ढाँचा_bufपूर्ण,
	अणु.field_id = "d-modsig", .field_init = ima_eventdigest_modsig_init,
	 .field_show = ima_show_ढाँचा_digest_ngपूर्ण,
	अणु.field_id = "modsig", .field_init = ima_evenपंचांगodsig_init,
	 .field_show = ima_show_ढाँचा_sigपूर्ण,
पूर्ण;

/*
 * Used when restoring measurements carried over from a kexec. 'd' and 'n' don't
 * need to be accounted क्रम since they shouldn't be defined in the same ढाँचा
 * description as 'd-ng' and 'n-ng' respectively.
 */
#घोषणा MAX_TEMPLATE_NAME_LEN माप("d-ng|n-ng|sig|buf|d-modisg|modsig")

अटल काष्ठा ima_ढाँचा_desc *ima_ढाँचा;
अटल काष्ठा ima_ढाँचा_desc *ima_buf_ढाँचा;

/**
 * ima_ढाँचा_has_modsig - Check whether ढाँचा has modsig-related fields.
 * @ima_ढाँचा: IMA ढाँचा to check.
 *
 * Tells whether the given ढाँचा has fields referencing a file's appended
 * signature.
 */
bool ima_ढाँचा_has_modsig(स्थिर काष्ठा ima_ढाँचा_desc *ima_ढाँचा)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ima_ढाँचा->num_fields; i++)
		अगर (!म_भेद(ima_ढाँचा->fields[i]->field_id, "modsig") ||
		    !म_भेद(ima_ढाँचा->fields[i]->field_id, "d-modsig"))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __init ima_ढाँचा_setup(अक्षर *str)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc;
	पूर्णांक ढाँचा_len = म_माप(str);

	अगर (ima_ढाँचा)
		वापस 1;

	ima_init_ढाँचा_list();

	/*
	 * Verअगरy that a ढाँचा with the supplied name exists.
	 * If not, use CONFIG_IMA_DEFAULT_TEMPLATE.
	 */
	ढाँचा_desc = lookup_ढाँचा_desc(str);
	अगर (!ढाँचा_desc) अणु
		pr_err("template %s not found, using %s\n",
		       str, CONFIG_IMA_DEFAULT_TEMPLATE);
		वापस 1;
	पूर्ण

	/*
	 * Verअगरy whether the current hash algorithm is supported
	 * by the 'ima' ढाँचा.
	 */
	अगर (ढाँचा_len == 3 && म_भेद(str, IMA_TEMPLATE_IMA_NAME) == 0 &&
	    ima_hash_algo != HASH_ALGO_SHA1 && ima_hash_algo != HASH_ALGO_MD5) अणु
		pr_err("template does not support hash alg\n");
		वापस 1;
	पूर्ण

	ima_ढाँचा = ढाँचा_desc;
	वापस 1;
पूर्ण
__setup("ima_template=", ima_ढाँचा_setup);

अटल पूर्णांक __init ima_ढाँचा_fmt_setup(अक्षर *str)
अणु
	पूर्णांक num_ढाँचाs = ARRAY_SIZE(builtin_ढाँचाs);

	अगर (ima_ढाँचा)
		वापस 1;

	अगर (ढाँचा_desc_init_fields(str, शून्य, शून्य) < 0) अणु
		pr_err("format string '%s' not valid, using template %s\n",
		       str, CONFIG_IMA_DEFAULT_TEMPLATE);
		वापस 1;
	पूर्ण

	builtin_ढाँचाs[num_ढाँचाs - 1].fmt = str;
	ima_ढाँचा = builtin_ढाँचाs + num_ढाँचाs - 1;

	वापस 1;
पूर्ण
__setup("ima_template_fmt=", ima_ढाँचा_fmt_setup);

काष्ठा ima_ढाँचा_desc *lookup_ढाँचा_desc(स्थिर अक्षर *name)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc;
	पूर्णांक found = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ढाँचा_desc, &defined_ढाँचाs, list) अणु
		अगर ((म_भेद(ढाँचा_desc->name, name) == 0) ||
		    (म_भेद(ढाँचा_desc->fmt, name) == 0)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस found ? ढाँचा_desc : शून्य;
पूर्ण

अटल स्थिर काष्ठा ima_ढाँचा_field *
lookup_ढाँचा_field(स्थिर अक्षर *field_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(supported_fields); i++)
		अगर (म_भेदन(supported_fields[i].field_id, field_id,
			    IMA_TEMPLATE_FIELD_ID_MAX_LEN) == 0)
			वापस &supported_fields[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक ढाँचा_fmt_size(स्थिर अक्षर *ढाँचा_fmt)
अणु
	अक्षर c;
	पूर्णांक ढाँचा_fmt_len = म_माप(ढाँचा_fmt);
	पूर्णांक i = 0, j = 0;

	जबतक (i < ढाँचा_fmt_len) अणु
		c = ढाँचा_fmt[i];
		अगर (c == '|')
			j++;
		i++;
	पूर्ण

	वापस j + 1;
पूर्ण

पूर्णांक ढाँचा_desc_init_fields(स्थिर अक्षर *ढाँचा_fmt,
			      स्थिर काष्ठा ima_ढाँचा_field ***fields,
			      पूर्णांक *num_fields)
अणु
	स्थिर अक्षर *ढाँचा_fmt_ptr;
	स्थिर काष्ठा ima_ढाँचा_field *found_fields[IMA_TEMPLATE_NUM_FIELDS_MAX];
	पूर्णांक ढाँचा_num_fields;
	पूर्णांक i, len;

	अगर (num_fields && *num_fields > 0) /* alपढ़ोy initialized? */
		वापस 0;

	ढाँचा_num_fields = ढाँचा_fmt_size(ढाँचा_fmt);

	अगर (ढाँचा_num_fields > IMA_TEMPLATE_NUM_FIELDS_MAX) अणु
		pr_err("format string '%s' contains too many fields\n",
		       ढाँचा_fmt);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0, ढाँचा_fmt_ptr = ढाँचा_fmt; i < ढाँचा_num_fields;
	     i++, ढाँचा_fmt_ptr += len + 1) अणु
		अक्षर पंचांगp_field_id[IMA_TEMPLATE_FIELD_ID_MAX_LEN + 1];

		len = म_अक्षरnul(ढाँचा_fmt_ptr, '|') - ढाँचा_fmt_ptr;
		अगर (len == 0 || len > IMA_TEMPLATE_FIELD_ID_MAX_LEN) अणु
			pr_err("Invalid field with length %d\n", len);
			वापस -EINVAL;
		पूर्ण

		स_नकल(पंचांगp_field_id, ढाँचा_fmt_ptr, len);
		पंचांगp_field_id[len] = '\0';
		found_fields[i] = lookup_ढाँचा_field(पंचांगp_field_id);
		अगर (!found_fields[i]) अणु
			pr_err("field '%s' not found\n", पंचांगp_field_id);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (fields && num_fields) अणु
		*fields = kदो_स्मृति_array(i, माप(*fields), GFP_KERNEL);
		अगर (*fields == शून्य)
			वापस -ENOMEM;

		स_नकल(*fields, found_fields, i * माप(*fields));
		*num_fields = i;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ima_init_ढाँचा_list(व्योम)
अणु
	पूर्णांक i;

	अगर (!list_empty(&defined_ढाँचाs))
		वापस;

	spin_lock(&ढाँचा_list);
	क्रम (i = 0; i < ARRAY_SIZE(builtin_ढाँचाs); i++) अणु
		list_add_tail_rcu(&builtin_ढाँचाs[i].list,
				  &defined_ढाँचाs);
	पूर्ण
	spin_unlock(&ढाँचा_list);
पूर्ण

काष्ठा ima_ढाँचा_desc *ima_ढाँचा_desc_current(व्योम)
अणु
	अगर (!ima_ढाँचा) अणु
		ima_init_ढाँचा_list();
		ima_ढाँचा =
		    lookup_ढाँचा_desc(CONFIG_IMA_DEFAULT_TEMPLATE);
	पूर्ण
	वापस ima_ढाँचा;
पूर्ण

काष्ठा ima_ढाँचा_desc *ima_ढाँचा_desc_buf(व्योम)
अणु
	अगर (!ima_buf_ढाँचा) अणु
		ima_init_ढाँचा_list();
		ima_buf_ढाँचा = lookup_ढाँचा_desc("ima-buf");
	पूर्ण
	वापस ima_buf_ढाँचा;
पूर्ण

पूर्णांक __init ima_init_ढाँचा(व्योम)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा = ima_ढाँचा_desc_current();
	पूर्णांक result;

	result = ढाँचा_desc_init_fields(ढाँचा->fmt,
					   &(ढाँचा->fields),
					   &(ढाँचा->num_fields));
	अगर (result < 0) अणु
		pr_err("template %s init failed, result: %d\n",
		       (म_माप(ढाँचा->name) ?
		       ढाँचा->name : ढाँचा->fmt), result);
		वापस result;
	पूर्ण

	ढाँचा = ima_ढाँचा_desc_buf();
	अगर (!ढाँचा) अणु
		pr_err("Failed to get ima-buf template\n");
		वापस -EINVAL;
	पूर्ण

	result = ढाँचा_desc_init_fields(ढाँचा->fmt,
					   &(ढाँचा->fields),
					   &(ढाँचा->num_fields));
	अगर (result < 0)
		pr_err("template %s init failed, result: %d\n",
		       (म_माप(ढाँचा->name) ?
		       ढाँचा->name : ढाँचा->fmt), result);

	वापस result;
पूर्ण

अटल काष्ठा ima_ढाँचा_desc *restore_ढाँचा_fmt(अक्षर *ढाँचा_name)
अणु
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc = शून्य;
	पूर्णांक ret;

	ret = ढाँचा_desc_init_fields(ढाँचा_name, शून्य, शून्य);
	अगर (ret < 0) अणु
		pr_err("attempting to initialize the template \"%s\" failed\n",
			ढाँचा_name);
		जाओ out;
	पूर्ण

	ढाँचा_desc = kzalloc(माप(*ढाँचा_desc), GFP_KERNEL);
	अगर (!ढाँचा_desc)
		जाओ out;

	ढाँचा_desc->name = "";
	ढाँचा_desc->fmt = kstrdup(ढाँचा_name, GFP_KERNEL);
	अगर (!ढाँचा_desc->fmt)
		जाओ out;

	spin_lock(&ढाँचा_list);
	list_add_tail_rcu(&ढाँचा_desc->list, &defined_ढाँचाs);
	spin_unlock(&ढाँचा_list);
out:
	वापस ढाँचा_desc;
पूर्ण

अटल पूर्णांक ima_restore_ढाँचा_data(काष्ठा ima_ढाँचा_desc *ढाँचा_desc,
				     व्योम *ढाँचा_data,
				     पूर्णांक ढाँचा_data_size,
				     काष्ठा ima_ढाँचा_entry **entry)
अणु
	काष्ठा tpm_digest *digests;
	पूर्णांक ret = 0;
	पूर्णांक i;

	*entry = kzalloc(काष्ठा_size(*entry, ढाँचा_data,
				     ढाँचा_desc->num_fields), GFP_NOFS);
	अगर (!*entry)
		वापस -ENOMEM;

	digests = kसुस्मृति(NR_BANKS(ima_tpm_chip) + ima_extra_slots,
			  माप(*digests), GFP_NOFS);
	अगर (!digests) अणु
		kमुक्त(*entry);
		वापस -ENOMEM;
	पूर्ण

	(*entry)->digests = digests;

	ret = ima_parse_buf(ढाँचा_data, ढाँचा_data + ढाँचा_data_size,
			    शून्य, ढाँचा_desc->num_fields,
			    (*entry)->ढाँचा_data, शून्य, शून्य,
			    ENFORCE_FIELDS | ENFORCE_BUFEND, "template data");
	अगर (ret < 0) अणु
		kमुक्त((*entry)->digests);
		kमुक्त(*entry);
		वापस ret;
	पूर्ण

	(*entry)->ढाँचा_desc = ढाँचा_desc;
	क्रम (i = 0; i < ढाँचा_desc->num_fields; i++) अणु
		काष्ठा ima_field_data *field_data = &(*entry)->ढाँचा_data[i];
		u8 *data = field_data->data;

		(*entry)->ढाँचा_data[i].data =
			kzalloc(field_data->len + 1, GFP_KERNEL);
		अगर (!(*entry)->ढाँचा_data[i].data) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		स_नकल((*entry)->ढाँचा_data[i].data, data, field_data->len);
		(*entry)->ढाँचा_data_len += माप(field_data->len);
		(*entry)->ढाँचा_data_len += field_data->len;
	पूर्ण

	अगर (ret < 0) अणु
		ima_मुक्त_ढाँचा_entry(*entry);
		*entry = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/* Restore the serialized binary measurement list without extending PCRs. */
पूर्णांक ima_restore_measurement_list(loff_t size, व्योम *buf)
अणु
	अक्षर ढाँचा_name[MAX_TEMPLATE_NAME_LEN];
	अचिन्हित अक्षर zero[TPM_DIGEST_SIZE] = अणु 0 पूर्ण;

	काष्ठा ima_kexec_hdr *khdr = buf;
	काष्ठा ima_field_data hdr[HDR__LAST] = अणु
		[HDR_PCR] = अणु.len = माप(u32)पूर्ण,
		[HDR_DIGEST] = अणु.len = TPM_DIGEST_SIZEपूर्ण,
	पूर्ण;

	व्योम *bufp = buf + माप(*khdr);
	व्योम *bufendp;
	काष्ठा ima_ढाँचा_entry *entry;
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc;
	DECLARE_BITMAP(hdr_mask, HDR__LAST);
	अचिन्हित दीर्घ count = 0;
	पूर्णांक ret = 0;

	अगर (!buf || size < माप(*khdr))
		वापस 0;

	अगर (ima_canonical_fmt) अणु
		khdr->version = le16_to_cpu(khdr->version);
		khdr->count = le64_to_cpu(khdr->count);
		khdr->buffer_size = le64_to_cpu(khdr->buffer_size);
	पूर्ण

	अगर (khdr->version != 1) अणु
		pr_err("attempting to restore a incompatible measurement list");
		वापस -EINVAL;
	पूर्ण

	अगर (khdr->count > अच_दीर्घ_उच्च - 1) अणु
		pr_err("attempting to restore too many measurements");
		वापस -EINVAL;
	पूर्ण

	biपंचांगap_zero(hdr_mask, HDR__LAST);
	biपंचांगap_set(hdr_mask, HDR_PCR, 1);
	biपंचांगap_set(hdr_mask, HDR_DIGEST, 1);

	/*
	 * ima kexec buffer prefix: version, buffer size, count
	 * v1 क्रमmat: pcr, digest, ढाँचा-name-len, ढाँचा-name,
	 *	      ढाँचा-data-size, ढाँचा-data
	 */
	bufendp = buf + khdr->buffer_size;
	जबतक ((bufp < bufendp) && (count++ < khdr->count)) अणु
		पूर्णांक enक्रमce_mask = ENFORCE_FIELDS;

		enक्रमce_mask |= (count == khdr->count) ? ENFORCE_BUFEND : 0;
		ret = ima_parse_buf(bufp, bufendp, &bufp, HDR__LAST, hdr, शून्य,
				    hdr_mask, enक्रमce_mask, "entry header");
		अगर (ret < 0)
			अवरोध;

		अगर (hdr[HDR_TEMPLATE_NAME].len >= MAX_TEMPLATE_NAME_LEN) अणु
			pr_err("attempting to restore a template name that is too long\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* ढाँचा name is not null terminated */
		स_नकल(ढाँचा_name, hdr[HDR_TEMPLATE_NAME].data,
		       hdr[HDR_TEMPLATE_NAME].len);
		ढाँचा_name[hdr[HDR_TEMPLATE_NAME].len] = 0;

		अगर (म_भेद(ढाँचा_name, "ima") == 0) अणु
			pr_err("attempting to restore an unsupported template \"%s\" failed\n",
			       ढाँचा_name);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ढाँचा_desc = lookup_ढाँचा_desc(ढाँचा_name);
		अगर (!ढाँचा_desc) अणु
			ढाँचा_desc = restore_ढाँचा_fmt(ढाँचा_name);
			अगर (!ढाँचा_desc)
				अवरोध;
		पूर्ण

		/*
		 * Only the running प्रणाली's ढाँचा क्रमmat is initialized
		 * on boot.  As needed, initialize the other ढाँचा क्रमmats.
		 */
		ret = ढाँचा_desc_init_fields(ढाँचा_desc->fmt,
						&(ढाँचा_desc->fields),
						&(ढाँचा_desc->num_fields));
		अगर (ret < 0) अणु
			pr_err("attempting to restore the template fmt \"%s\" failed\n",
			       ढाँचा_desc->fmt);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = ima_restore_ढाँचा_data(ढाँचा_desc,
						hdr[HDR_TEMPLATE_DATA].data,
						hdr[HDR_TEMPLATE_DATA].len,
						&entry);
		अगर (ret < 0)
			अवरोध;

		अगर (स_भेद(hdr[HDR_DIGEST].data, zero, माप(zero))) अणु
			ret = ima_calc_field_array_hash(
						&entry->ढाँचा_data[0],
						entry);
			अगर (ret < 0) अणु
				pr_err("cannot calculate template digest\n");
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण

		entry->pcr = !ima_canonical_fmt ? *(u32 *)(hdr[HDR_PCR].data) :
			     le32_to_cpu(*(u32 *)(hdr[HDR_PCR].data));
		ret = ima_restore_measurement_entry(entry);
		अगर (ret < 0)
			अवरोध;

	पूर्ण
	वापस ret;
पूर्ण
