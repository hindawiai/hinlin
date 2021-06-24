<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2019
 *  Author(s): Harald Freudenberger <freude@linux.ibm.com>
 *
 *  Collection of EP11 misc functions used by zcrypt and pkey
 */

#घोषणा KMSG_COMPONENT "zcrypt"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/zcrypt.h>
#समावेश <यंत्र/pkey.h>
#समावेश <crypto/aes.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_debug.h"
#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_ep11misc.h"
#समावेश "zcrypt_ccamisc.h"

#घोषणा DEBUG_DBG(...)	ZCRYPT_DBF(DBF_DEBUG, ##__VA_ARGS__)
#घोषणा DEBUG_INFO(...) ZCRYPT_DBF(DBF_INFO, ##__VA_ARGS__)
#घोषणा DEBUG_WARN(...) ZCRYPT_DBF(DBF_WARN, ##__VA_ARGS__)
#घोषणा DEBUG_ERR(...)	ZCRYPT_DBF(DBF_ERR, ##__VA_ARGS__)

/* शेष iv used here */
अटल स्थिर u8 def_iv[16] = अणु 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			       0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff पूर्ण;

/* ep11 card info cache */
काष्ठा card_list_entry अणु
	काष्ठा list_head list;
	u16 cardnr;
	काष्ठा ep11_card_info info;
पूर्ण;
अटल LIST_HEAD(card_list);
अटल DEFINE_SPINLOCK(card_list_lock);

अटल पूर्णांक card_cache_fetch(u16 cardnr, काष्ठा ep11_card_info *ci)
अणु
	पूर्णांक rc = -ENOENT;
	काष्ठा card_list_entry *ptr;

	spin_lock_bh(&card_list_lock);
	list_क्रम_each_entry(ptr, &card_list, list) अणु
		अगर (ptr->cardnr == cardnr) अणु
			स_नकल(ci, &ptr->info, माप(*ci));
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&card_list_lock);

	वापस rc;
पूर्ण

अटल व्योम card_cache_update(u16 cardnr, स्थिर काष्ठा ep11_card_info *ci)
अणु
	पूर्णांक found = 0;
	काष्ठा card_list_entry *ptr;

	spin_lock_bh(&card_list_lock);
	list_क्रम_each_entry(ptr, &card_list, list) अणु
		अगर (ptr->cardnr == cardnr) अणु
			स_नकल(&ptr->info, ci, माप(*ci));
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		ptr = kदो_स्मृति(माप(*ptr), GFP_ATOMIC);
		अगर (!ptr) अणु
			spin_unlock_bh(&card_list_lock);
			वापस;
		पूर्ण
		ptr->cardnr = cardnr;
		स_नकल(&ptr->info, ci, माप(*ci));
		list_add(&ptr->list, &card_list);
	पूर्ण
	spin_unlock_bh(&card_list_lock);
पूर्ण

अटल व्योम card_cache_scrub(u16 cardnr)
अणु
	काष्ठा card_list_entry *ptr;

	spin_lock_bh(&card_list_lock);
	list_क्रम_each_entry(ptr, &card_list, list) अणु
		अगर (ptr->cardnr == cardnr) अणु
			list_del(&ptr->list);
			kमुक्त(ptr);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&card_list_lock);
पूर्ण

अटल व्योम __निकास card_cache_मुक्त(व्योम)
अणु
	काष्ठा card_list_entry *ptr, *pnext;

	spin_lock_bh(&card_list_lock);
	list_क्रम_each_entry_safe(ptr, pnext, &card_list, list) अणु
		list_del(&ptr->list);
		kमुक्त(ptr);
	पूर्ण
	spin_unlock_bh(&card_list_lock);
पूर्ण

/*
 * Simple check अगर the key blob is a valid EP11 AES key blob with header.
 */
पूर्णांक ep11_check_aes_key_with_hdr(debug_info_t *dbg, पूर्णांक dbflvl,
				स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp)
अणु
	काष्ठा ep11kblob_header *hdr = (काष्ठा ep11kblob_header *) key;
	काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) (key + माप(*hdr));

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (keylen < माप(*hdr) + माप(*kb)) अणु
		DBF("%s key check failed, keylen %zu < %zu\n",
		    __func__, keylen, माप(*hdr) + माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->type != TOKTYPE_NON_CCA) अणु
		अगर (dbg)
			DBF("%s key check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) hdr->type, TOKTYPE_NON_CCA);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->hver != 0x00) अणु
		अगर (dbg)
			DBF("%s key check failed, header version 0x%02x != 0x00\n",
			    __func__, (पूर्णांक) hdr->hver);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->version != TOKVER_EP11_AES_WITH_HEADER) अणु
		अगर (dbg)
			DBF("%s key check failed, version 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) hdr->version, TOKVER_EP11_AES_WITH_HEADER);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->len > keylen) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d keylen %zu mismatch\n",
			    __func__, (पूर्णांक) hdr->len, keylen);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->len < माप(*hdr) + माप(*kb)) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d < %zu\n",
			    __func__, (पूर्णांक) hdr->len, माप(*hdr) + माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (kb->version != EP11_STRUCT_MAGIC) अणु
		अगर (dbg)
			DBF("%s key check failed, blob magic 0x%04x != 0x%04x\n",
			    __func__, (पूर्णांक) kb->version, EP11_STRUCT_MAGIC);
		वापस -EINVAL;
	पूर्ण
	अगर (checkcpacfexp && !(kb->attr & EP11_BLOB_PKEY_EXTRACTABLE)) अणु
		अगर (dbg)
			DBF("%s key check failed, PKEY_EXTRACTABLE is off\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ep11_check_aes_key_with_hdr);

/*
 * Simple check अगर the key blob is a valid EP11 ECC key blob with header.
 */
पूर्णांक ep11_check_ecc_key_with_hdr(debug_info_t *dbg, पूर्णांक dbflvl,
				स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp)
अणु
	काष्ठा ep11kblob_header *hdr = (काष्ठा ep11kblob_header *) key;
	काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) (key + माप(*hdr));

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (keylen < माप(*hdr) + माप(*kb)) अणु
		DBF("%s key check failed, keylen %zu < %zu\n",
		    __func__, keylen, माप(*hdr) + माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->type != TOKTYPE_NON_CCA) अणु
		अगर (dbg)
			DBF("%s key check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) hdr->type, TOKTYPE_NON_CCA);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->hver != 0x00) अणु
		अगर (dbg)
			DBF("%s key check failed, header version 0x%02x != 0x00\n",
			    __func__, (पूर्णांक) hdr->hver);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->version != TOKVER_EP11_ECC_WITH_HEADER) अणु
		अगर (dbg)
			DBF("%s key check failed, version 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) hdr->version, TOKVER_EP11_ECC_WITH_HEADER);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->len > keylen) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d keylen %zu mismatch\n",
			    __func__, (पूर्णांक) hdr->len, keylen);
		वापस -EINVAL;
	पूर्ण
	अगर (hdr->len < माप(*hdr) + माप(*kb)) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d < %zu\n",
			    __func__, (पूर्णांक) hdr->len, माप(*hdr) + माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (kb->version != EP11_STRUCT_MAGIC) अणु
		अगर (dbg)
			DBF("%s key check failed, blob magic 0x%04x != 0x%04x\n",
			    __func__, (पूर्णांक) kb->version, EP11_STRUCT_MAGIC);
		वापस -EINVAL;
	पूर्ण
	अगर (checkcpacfexp && !(kb->attr & EP11_BLOB_PKEY_EXTRACTABLE)) अणु
		अगर (dbg)
			DBF("%s key check failed, PKEY_EXTRACTABLE is off\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ep11_check_ecc_key_with_hdr);

/*
 * Simple check अगर the key blob is a valid EP11 AES key blob with
 * the header in the session field (old style EP11 AES key).
 */
पूर्णांक ep11_check_aes_key(debug_info_t *dbg, पूर्णांक dbflvl,
		       स्थिर u8 *key, माप_प्रकार keylen, पूर्णांक checkcpacfexp)
अणु
	काष्ठा ep11keyblob *kb = (काष्ठा ep11keyblob *) key;

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (keylen < माप(*kb)) अणु
		DBF("%s key check failed, keylen %zu < %zu\n",
		    __func__, keylen, माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (kb->head.type != TOKTYPE_NON_CCA) अणु
		अगर (dbg)
			DBF("%s key check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) kb->head.type, TOKTYPE_NON_CCA);
		वापस -EINVAL;
	पूर्ण
	अगर (kb->head.version != TOKVER_EP11_AES) अणु
		अगर (dbg)
			DBF("%s key check failed, version 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) kb->head.version, TOKVER_EP11_AES);
		वापस -EINVAL;
	पूर्ण
	अगर (kb->head.len > keylen) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d keylen %zu mismatch\n",
			    __func__, (पूर्णांक) kb->head.len, keylen);
		वापस -EINVAL;
	पूर्ण
	अगर (kb->head.len < माप(*kb)) अणु
		अगर (dbg)
			DBF("%s key check failed, header len %d < %zu\n",
			    __func__, (पूर्णांक) kb->head.len, माप(*kb));
		वापस -EINVAL;
	पूर्ण

	अगर (kb->version != EP11_STRUCT_MAGIC) अणु
		अगर (dbg)
			DBF("%s key check failed, blob magic 0x%04x != 0x%04x\n",
			    __func__, (पूर्णांक) kb->version, EP11_STRUCT_MAGIC);
		वापस -EINVAL;
	पूर्ण
	अगर (checkcpacfexp && !(kb->attr & EP11_BLOB_PKEY_EXTRACTABLE)) अणु
		अगर (dbg)
			DBF("%s key check failed, PKEY_EXTRACTABLE is off\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ep11_check_aes_key);

/*
 * Allocate and prepare ep11 cprb plus additional payload.
 */
अटल अंतरभूत काष्ठा ep11_cprb *alloc_cprb(माप_प्रकार payload_len)
अणु
	माप_प्रकार len = माप(काष्ठा ep11_cprb) + payload_len;
	काष्ठा ep11_cprb *cprb;

	cprb = kzalloc(len, GFP_KERNEL);
	अगर (!cprb)
		वापस शून्य;

	cprb->cprb_len = माप(काष्ठा ep11_cprb);
	cprb->cprb_ver_id = 0x04;
	स_नकल(cprb->func_id, "T4", 2);
	cprb->ret_code = 0xFFFFFFFF;
	cprb->payload_len = payload_len;

	वापस cprb;
पूर्ण

/*
 * Some helper functions related to ASN1 encoding.
 * Limited to length info <= 2 byte.
 */

#घोषणा ASN1TAGLEN(x) (2 + (x) + ((x) > 127 ? 1 : 0) + ((x) > 255 ? 1 : 0))

अटल पूर्णांक asn1tag_ग_लिखो(u8 *ptr, u8 tag, स्थिर u8 *pvalue, u16 valuelen)
अणु
	ptr[0] = tag;
	अगर (valuelen > 255) अणु
		ptr[1] = 0x82;
		*((u16 *)(ptr + 2)) = valuelen;
		स_नकल(ptr + 4, pvalue, valuelen);
		वापस 4 + valuelen;
	पूर्ण
	अगर (valuelen > 127) अणु
		ptr[1] = 0x81;
		ptr[2] = (u8) valuelen;
		स_नकल(ptr + 3, pvalue, valuelen);
		वापस 3 + valuelen;
	पूर्ण
	ptr[1] = (u8) valuelen;
	स_नकल(ptr + 2, pvalue, valuelen);
	वापस 2 + valuelen;
पूर्ण

/* EP11 payload > 127 bytes starts with this काष्ठा */
काष्ठा pl_head अणु
	u8  tag;
	u8  lenfmt;
	u16 len;
	u8  func_tag;
	u8  func_len;
	u32 func;
	u8  करोm_tag;
	u8  करोm_len;
	u32 करोm;
पूर्ण __packed;

/* prep ep11 payload head helper function */
अटल अंतरभूत व्योम prep_head(काष्ठा pl_head *h,
			     माप_प्रकार pl_size, पूर्णांक api, पूर्णांक func)
अणु
	h->tag = 0x30;
	h->lenfmt = 0x82;
	h->len = pl_size - 4;
	h->func_tag = 0x04;
	h->func_len = माप(u32);
	h->func = (api << 16) + func;
	h->करोm_tag = 0x04;
	h->करोm_len = माप(u32);
पूर्ण

/* prep urb helper function */
अटल अंतरभूत व्योम prep_urb(काष्ठा ep11_urb *u,
			    काष्ठा ep11_target_dev *t, पूर्णांक nt,
			    काष्ठा ep11_cprb *req, माप_प्रकार req_len,
			    काष्ठा ep11_cprb *rep, माप_प्रकार rep_len)
अणु
	u->tarमाला_लो = (u8 __user *) t;
	u->tarमाला_लो_num = nt;
	u->req = (u8 __user *) req;
	u->req_len = req_len;
	u->resp = (u8 __user *) rep;
	u->resp_len = rep_len;
पूर्ण

/* Check ep11 reply payload, वापस 0 or suggested त्रुटि_सं value. */
अटल पूर्णांक check_reply_pl(स्थिर u8 *pl, स्थिर अक्षर *func)
अणु
	पूर्णांक len;
	u32 ret;

	/* start tag */
	अगर (*pl++ != 0x30) अणु
		DEBUG_ERR("%s reply start tag mismatch\n", func);
		वापस -EIO;
	पूर्ण

	/* payload length क्रमmat */
	अगर (*pl < 127) अणु
		len = *pl;
		pl++;
	पूर्ण अन्यथा अगर (*pl == 0x81) अणु
		pl++;
		len = *pl;
		pl++;
	पूर्ण अन्यथा अगर (*pl == 0x82) अणु
		pl++;
		len = *((u16 *)pl);
		pl += 2;
	पूर्ण अन्यथा अणु
		DEBUG_ERR("%s reply start tag lenfmt mismatch 0x%02hhx\n",
			  func, *pl);
		वापस -EIO;
	पूर्ण

	/* len should cover at least 3 fields with 32 bit value each */
	अगर (len < 3 * 6) अणु
		DEBUG_ERR("%s reply length %d too small\n", func, len);
		वापस -EIO;
	पूर्ण

	/* function tag, length and value */
	अगर (pl[0] != 0x04 || pl[1] != 0x04) अणु
		DEBUG_ERR("%s function tag or length mismatch\n", func);
		वापस -EIO;
	पूर्ण
	pl += 6;

	/* करोm tag, length and value */
	अगर (pl[0] != 0x04 || pl[1] != 0x04) अणु
		DEBUG_ERR("%s dom tag or length mismatch\n", func);
		वापस -EIO;
	पूर्ण
	pl += 6;

	/* वापस value tag, length and value */
	अगर (pl[0] != 0x04 || pl[1] != 0x04) अणु
		DEBUG_ERR("%s return value tag or length mismatch\n", func);
		वापस -EIO;
	पूर्ण
	pl += 2;
	ret = *((u32 *)pl);
	अगर (ret != 0) अणु
		DEBUG_ERR("%s return value 0x%04x != 0\n", func, ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Helper function which करोes an ep11 query with given query type.
 */
अटल पूर्णांक ep11_query_info(u16 cardnr, u16 करोमुख्य, u32 query_type,
			   माप_प्रकार buflen, u8 *buf)
अणु
	काष्ठा ep11_info_req_pl अणु
		काष्ठा pl_head head;
		u8  query_type_tag;
		u8  query_type_len;
		u32 query_type;
		u8  query_subtype_tag;
		u8  query_subtype_len;
		u32 query_subtype;
	पूर्ण __packed * req_pl;
	काष्ठा ep11_info_rep_pl अणु
		काष्ठा pl_head head;
		u8  rc_tag;
		u8  rc_len;
		u32 rc;
		u8  data_tag;
		u8  data_lenfmt;
		u16 data_len;
	पूर्ण __packed * rep_pl;
	काष्ठा ep11_cprb *req = शून्य, *rep = शून्य;
	काष्ठा ep11_target_dev target;
	काष्ठा ep11_urb *urb = शून्य;
	पूर्णांक api = 1, rc = -ENOMEM;

	/* request cprb and payload */
	req = alloc_cprb(माप(काष्ठा ep11_info_req_pl));
	अगर (!req)
		जाओ out;
	req_pl = (काष्ठा ep11_info_req_pl *) (((u8 *) req) + माप(*req));
	prep_head(&req_pl->head, माप(*req_pl), api, 38); /* get xcp info */
	req_pl->query_type_tag = 0x04;
	req_pl->query_type_len = माप(u32);
	req_pl->query_type = query_type;
	req_pl->query_subtype_tag = 0x04;
	req_pl->query_subtype_len = माप(u32);

	/* reply cprb and payload */
	rep = alloc_cprb(माप(काष्ठा ep11_info_rep_pl) + buflen);
	अगर (!rep)
		जाओ out;
	rep_pl = (काष्ठा ep11_info_rep_pl *) (((u8 *) rep) + माप(*rep));

	/* urb and target */
	urb = kदो_स्मृति(माप(काष्ठा ep11_urb), GFP_KERNEL);
	अगर (!urb)
		जाओ out;
	target.ap_id = cardnr;
	target.करोm_id = करोमुख्य;
	prep_urb(urb, &target, 1,
		 req, माप(*req) + माप(*req_pl),
		 rep, माप(*rep) + माप(*rep_pl) + buflen);

	rc = zcrypt_send_ep11_cprb(urb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_ep11_cprb(card=%d dom=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	rc = check_reply_pl((u8 *)rep_pl, __func__);
	अगर (rc)
		जाओ out;
	अगर (rep_pl->data_tag != 0x04 || rep_pl->data_lenfmt != 0x82) अणु
		DEBUG_ERR("%s unknown reply data format\n", __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (rep_pl->data_len > buflen) अणु
		DEBUG_ERR("%s mismatch between reply data len and buffer len\n",
			  __func__);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	स_नकल(buf, ((u8 *) rep_pl) + माप(*rep_pl), rep_pl->data_len);

out:
	kमुक्त(req);
	kमुक्त(rep);
	kमुक्त(urb);
	वापस rc;
पूर्ण

/*
 * Provide inक्रमmation about an EP11 card.
 */
पूर्णांक ep11_get_card_info(u16 card, काष्ठा ep11_card_info *info, पूर्णांक verअगरy)
अणु
	पूर्णांक rc;
	काष्ठा ep11_module_query_info अणु
		u32 API_ord_nr;
		u32 firmware_id;
		u8  FW_major_vers;
		u8  FW_minor_vers;
		u8  CSP_major_vers;
		u8  CSP_minor_vers;
		u8  fwid[32];
		u8  xcp_config_hash[32];
		u8  CSP_config_hash[32];
		u8  serial[16];
		u8  module_date_समय[16];
		u64 op_mode;
		u32 PKCS11_flags;
		u32 ext_flags;
		u32 करोमुख्यs;
		u32 sym_state_bytes;
		u32 digest_state_bytes;
		u32 pin_blob_bytes;
		u32 SPKI_bytes;
		u32 priv_key_blob_bytes;
		u32 sym_blob_bytes;
		u32 max_payload_bytes;
		u32 CP_profile_bytes;
		u32 max_CP_index;
	पूर्ण __packed * pmqi = शून्य;

	rc = card_cache_fetch(card, info);
	अगर (rc || verअगरy) अणु
		pmqi = kदो_स्मृति(माप(*pmqi), GFP_KERNEL);
		अगर (!pmqi)
			वापस -ENOMEM;
		rc = ep11_query_info(card, AUTOSEL_DOM,
				     0x01 /* module info query */,
				     माप(*pmqi), (u8 *) pmqi);
		अगर (rc) अणु
			अगर (rc == -ENODEV)
				card_cache_scrub(card);
			जाओ out;
		पूर्ण
		स_रखो(info, 0, माप(*info));
		info->API_ord_nr = pmqi->API_ord_nr;
		info->FW_version =
			(pmqi->FW_major_vers << 8) + pmqi->FW_minor_vers;
		स_नकल(info->serial, pmqi->serial, माप(info->serial));
		info->op_mode = pmqi->op_mode;
		card_cache_update(card, info);
	पूर्ण

out:
	kमुक्त(pmqi);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_get_card_info);

/*
 * Provide inक्रमmation about a करोमुख्य within an EP11 card.
 */
पूर्णांक ep11_get_करोमुख्य_info(u16 card, u16 करोमुख्य, काष्ठा ep11_करोमुख्य_info *info)
अणु
	पूर्णांक rc;
	काष्ठा ep11_करोमुख्य_query_info अणु
		u32 करोm_index;
		u8  cur_WK_VP[32];
		u8  new_WK_VP[32];
		u32 करोm_flags;
		u64 op_mode;
	पूर्ण __packed * p_करोm_info;

	p_करोm_info = kदो_स्मृति(माप(*p_करोm_info), GFP_KERNEL);
	अगर (!p_करोm_info)
		वापस -ENOMEM;

	rc = ep11_query_info(card, करोमुख्य, 0x03 /* करोमुख्य info query */,
			     माप(*p_करोm_info), (u8 *) p_करोm_info);
	अगर (rc)
		जाओ out;

	स_रखो(info, 0, माप(*info));
	info->cur_wk_state = '0';
	info->new_wk_state = '0';
	अगर (p_करोm_info->करोm_flags & 0x10 /* left imprपूर्णांक mode */) अणु
		अगर (p_करोm_info->करोm_flags & 0x02 /* cur wk valid */) अणु
			info->cur_wk_state = '1';
			स_नकल(info->cur_wkvp, p_करोm_info->cur_WK_VP, 32);
		पूर्ण
		अगर (p_करोm_info->करोm_flags & 0x04 /* new wk present */
		    || p_करोm_info->करोm_flags & 0x08 /* new wk committed */) अणु
			info->new_wk_state =
				p_करोm_info->करोm_flags & 0x08 ? '2' : '1';
			स_नकल(info->new_wkvp, p_करोm_info->new_WK_VP, 32);
		पूर्ण
	पूर्ण
	info->op_mode = p_करोm_info->op_mode;

out:
	kमुक्त(p_करोm_info);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_get_करोमुख्य_info);

/*
 * Default EP11 AES key generate attributes, used when no keygenflags given:
 * XCP_BLOB_ENCRYPT | XCP_BLOB_DECRYPT | XCP_BLOB_PROTKEY_EXTRACTABLE
 */
#घोषणा KEY_ATTR_DEFAULTS 0x00200c00

पूर्णांक ep11_genaeskey(u16 card, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		   u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	काष्ठा keygen_req_pl अणु
		काष्ठा pl_head head;
		u8  var_tag;
		u8  var_len;
		u32 var;
		u8  keybytes_tag;
		u8  keybytes_len;
		u32 keybytes;
		u8  mech_tag;
		u8  mech_len;
		u32 mech;
		u8  attr_tag;
		u8  attr_len;
		u32 attr_header;
		u32 attr_bool_mask;
		u32 attr_bool_bits;
		u32 attr_val_len_type;
		u32 attr_val_len_value;
		u8  pin_tag;
		u8  pin_len;
	पूर्ण __packed * req_pl;
	काष्ठा keygen_rep_pl अणु
		काष्ठा pl_head head;
		u8  rc_tag;
		u8  rc_len;
		u32 rc;
		u8  data_tag;
		u8  data_lenfmt;
		u16 data_len;
		u8  data[512];
	पूर्ण __packed * rep_pl;
	काष्ठा ep11_cprb *req = शून्य, *rep = शून्य;
	काष्ठा ep11_target_dev target;
	काष्ठा ep11_urb *urb = शून्य;
	काष्ठा ep11keyblob *kb;
	पूर्णांक api, rc = -ENOMEM;

	चयन (keybitsize) अणु
	हाल 128:
	हाल 192:
	हाल 256:
		अवरोध;
	शेष:
		DEBUG_ERR(
			"%s unknown/unsupported keybitsize %d\n",
			__func__, keybitsize);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* request cprb and payload */
	req = alloc_cprb(माप(काष्ठा keygen_req_pl));
	अगर (!req)
		जाओ out;
	req_pl = (काष्ठा keygen_req_pl *) (((u8 *) req) + माप(*req));
	api = (!keygenflags || keygenflags & 0x00200000) ? 4 : 1;
	prep_head(&req_pl->head, माप(*req_pl), api, 21); /* GenerateKey */
	req_pl->var_tag = 0x04;
	req_pl->var_len = माप(u32);
	req_pl->keybytes_tag = 0x04;
	req_pl->keybytes_len = माप(u32);
	req_pl->keybytes = keybitsize / 8;
	req_pl->mech_tag = 0x04;
	req_pl->mech_len = माप(u32);
	req_pl->mech = 0x00001080; /* CKM_AES_KEY_GEN */
	req_pl->attr_tag = 0x04;
	req_pl->attr_len = 5 * माप(u32);
	req_pl->attr_header = 0x10010000;
	req_pl->attr_bool_mask = keygenflags ? keygenflags : KEY_ATTR_DEFAULTS;
	req_pl->attr_bool_bits = keygenflags ? keygenflags : KEY_ATTR_DEFAULTS;
	req_pl->attr_val_len_type = 0x00000161; /* CKA_VALUE_LEN */
	req_pl->attr_val_len_value = keybitsize / 8;
	req_pl->pin_tag = 0x04;

	/* reply cprb and payload */
	rep = alloc_cprb(माप(काष्ठा keygen_rep_pl));
	अगर (!rep)
		जाओ out;
	rep_pl = (काष्ठा keygen_rep_pl *) (((u8 *) rep) + माप(*rep));

	/* urb and target */
	urb = kदो_स्मृति(माप(काष्ठा ep11_urb), GFP_KERNEL);
	अगर (!urb)
		जाओ out;
	target.ap_id = card;
	target.करोm_id = करोमुख्य;
	prep_urb(urb, &target, 1,
		 req, माप(*req) + माप(*req_pl),
		 rep, माप(*rep) + माप(*rep_pl));

	rc = zcrypt_send_ep11_cprb(urb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_ep11_cprb(card=%d dom=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) card, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	rc = check_reply_pl((u8 *)rep_pl, __func__);
	अगर (rc)
		जाओ out;
	अगर (rep_pl->data_tag != 0x04 || rep_pl->data_lenfmt != 0x82) अणु
		DEBUG_ERR("%s unknown reply data format\n", __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (rep_pl->data_len > *keybufsize) अणु
		DEBUG_ERR("%s mismatch reply data len / key buffer len\n",
			  __func__);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	/* copy key blob and set header values */
	स_नकल(keybuf, rep_pl->data, rep_pl->data_len);
	*keybufsize = rep_pl->data_len;
	kb = (काष्ठा ep11keyblob *) keybuf;
	kb->head.type = TOKTYPE_NON_CCA;
	kb->head.len = rep_pl->data_len;
	kb->head.version = TOKVER_EP11_AES;
	kb->head.keybitlen = keybitsize;

out:
	kमुक्त(req);
	kमुक्त(rep);
	kमुक्त(urb);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_genaeskey);

अटल पूर्णांक ep11_cryptsingle(u16 card, u16 करोमुख्य,
			    u16 mode, u32 mech, स्थिर u8 *iv,
			    स्थिर u8 *key, माप_प्रकार keysize,
			    स्थिर u8 *inbuf, माप_प्रकार inbufsize,
			    u8 *outbuf, माप_प्रकार *outbufsize)
अणु
	काष्ठा crypt_req_pl अणु
		काष्ठा pl_head head;
		u8  var_tag;
		u8  var_len;
		u32 var;
		u8  mech_tag;
		u8  mech_len;
		u32 mech;
		/*
		 * maybe followed by iv data
		 * followed by key tag + key blob
		 * followed by plaपूर्णांकext tag + plaपूर्णांकext
		 */
	पूर्ण __packed * req_pl;
	काष्ठा crypt_rep_pl अणु
		काष्ठा pl_head head;
		u8  rc_tag;
		u8  rc_len;
		u32 rc;
		u8  data_tag;
		u8  data_lenfmt;
		/* data follows */
	पूर्ण __packed * rep_pl;
	काष्ठा ep11_cprb *req = शून्य, *rep = शून्य;
	काष्ठा ep11_target_dev target;
	काष्ठा ep11_urb *urb = शून्य;
	माप_प्रकार req_pl_size, rep_pl_size;
	पूर्णांक n, api = 1, rc = -ENOMEM;
	u8 *p;

	/* the simple asn1 coding used has length limits */
	अगर (keysize > 0xFFFF || inbufsize > 0xFFFF)
		वापस -EINVAL;

	/* request cprb and payload */
	req_pl_size = माप(काष्ठा crypt_req_pl) + (iv ? 16 : 0)
		+ ASN1TAGLEN(keysize) + ASN1TAGLEN(inbufsize);
	req = alloc_cprb(req_pl_size);
	अगर (!req)
		जाओ out;
	req_pl = (काष्ठा crypt_req_pl *) (((u8 *) req) + माप(*req));
	prep_head(&req_pl->head, req_pl_size, api, (mode ? 20 : 19));
	req_pl->var_tag = 0x04;
	req_pl->var_len = माप(u32);
	/* mech is mech + mech params (iv here) */
	req_pl->mech_tag = 0x04;
	req_pl->mech_len = माप(u32) + (iv ? 16 : 0);
	req_pl->mech = (mech ? mech : 0x00001085); /* CKM_AES_CBC_PAD */
	p = ((u8 *) req_pl) + माप(*req_pl);
	अगर (iv) अणु
		स_नकल(p, iv, 16);
		p += 16;
	पूर्ण
	/* key and input data */
	p += asn1tag_ग_लिखो(p, 0x04, key, keysize);
	p += asn1tag_ग_लिखो(p, 0x04, inbuf, inbufsize);

	/* reply cprb and payload, assume out data size <= in data size + 32 */
	rep_pl_size = माप(काष्ठा crypt_rep_pl) + ASN1TAGLEN(inbufsize + 32);
	rep = alloc_cprb(rep_pl_size);
	अगर (!rep)
		जाओ out;
	rep_pl = (काष्ठा crypt_rep_pl *) (((u8 *) rep) + माप(*rep));

	/* urb and target */
	urb = kदो_स्मृति(माप(काष्ठा ep11_urb), GFP_KERNEL);
	अगर (!urb)
		जाओ out;
	target.ap_id = card;
	target.करोm_id = करोमुख्य;
	prep_urb(urb, &target, 1,
		 req, माप(*req) + req_pl_size,
		 rep, माप(*rep) + rep_pl_size);

	rc = zcrypt_send_ep11_cprb(urb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_ep11_cprb(card=%d dom=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) card, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	rc = check_reply_pl((u8 *)rep_pl, __func__);
	अगर (rc)
		जाओ out;
	अगर (rep_pl->data_tag != 0x04) अणु
		DEBUG_ERR("%s unknown reply data format\n", __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण
	p = ((u8 *) rep_pl) + माप(*rep_pl);
	अगर (rep_pl->data_lenfmt <= 127)
		n = rep_pl->data_lenfmt;
	अन्यथा अगर (rep_pl->data_lenfmt == 0x81)
		n = *p++;
	अन्यथा अगर (rep_pl->data_lenfmt == 0x82) अणु
		n = *((u16 *) p);
		p += 2;
	पूर्ण अन्यथा अणु
		DEBUG_ERR("%s unknown reply data length format 0x%02hhx\n",
			  __func__, rep_pl->data_lenfmt);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (n > *outbufsize) अणु
		DEBUG_ERR("%s mismatch reply data len %d / output buffer %zu\n",
			  __func__, n, *outbufsize);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	स_नकल(outbuf, p, n);
	*outbufsize = n;

out:
	kमुक्त(req);
	kमुक्त(rep);
	kमुक्त(urb);
	वापस rc;
पूर्ण

अटल पूर्णांक ep11_unwrapkey(u16 card, u16 करोमुख्य,
			  स्थिर u8 *kek, माप_प्रकार keksize,
			  स्थिर u8 *enckey, माप_प्रकार enckeysize,
			  u32 mech, स्थिर u8 *iv,
			  u32 keybitsize, u32 keygenflags,
			  u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	काष्ठा uw_req_pl अणु
		काष्ठा pl_head head;
		u8  attr_tag;
		u8  attr_len;
		u32 attr_header;
		u32 attr_bool_mask;
		u32 attr_bool_bits;
		u32 attr_key_type;
		u32 attr_key_type_value;
		u32 attr_val_len;
		u32 attr_val_len_value;
		u8  mech_tag;
		u8  mech_len;
		u32 mech;
		/*
		 * maybe followed by iv data
		 * followed by kek tag + kek blob
		 * followed by empty mac tag
		 * followed by empty pin tag
		 * followed by encryted key tag + bytes
		 */
	पूर्ण __packed * req_pl;
	काष्ठा uw_rep_pl अणु
		काष्ठा pl_head head;
		u8  rc_tag;
		u8  rc_len;
		u32 rc;
		u8  data_tag;
		u8  data_lenfmt;
		u16 data_len;
		u8  data[512];
	पूर्ण __packed * rep_pl;
	काष्ठा ep11_cprb *req = शून्य, *rep = शून्य;
	काष्ठा ep11_target_dev target;
	काष्ठा ep11_urb *urb = शून्य;
	काष्ठा ep11keyblob *kb;
	माप_प्रकार req_pl_size;
	पूर्णांक api, rc = -ENOMEM;
	u8 *p;

	/* request cprb and payload */
	req_pl_size = माप(काष्ठा uw_req_pl) + (iv ? 16 : 0)
		+ ASN1TAGLEN(keksize) + 4 + ASN1TAGLEN(enckeysize);
	req = alloc_cprb(req_pl_size);
	अगर (!req)
		जाओ out;
	req_pl = (काष्ठा uw_req_pl *) (((u8 *) req) + माप(*req));
	api = (!keygenflags || keygenflags & 0x00200000) ? 4 : 1;
	prep_head(&req_pl->head, req_pl_size, api, 34); /* UnwrapKey */
	req_pl->attr_tag = 0x04;
	req_pl->attr_len = 7 * माप(u32);
	req_pl->attr_header = 0x10020000;
	req_pl->attr_bool_mask = keygenflags ? keygenflags : KEY_ATTR_DEFAULTS;
	req_pl->attr_bool_bits = keygenflags ? keygenflags : KEY_ATTR_DEFAULTS;
	req_pl->attr_key_type = 0x00000100; /* CKA_KEY_TYPE */
	req_pl->attr_key_type_value = 0x0000001f; /* CKK_AES */
	req_pl->attr_val_len = 0x00000161; /* CKA_VALUE_LEN */
	req_pl->attr_val_len_value = keybitsize / 8;
	/* mech is mech + mech params (iv here) */
	req_pl->mech_tag = 0x04;
	req_pl->mech_len = माप(u32) + (iv ? 16 : 0);
	req_pl->mech = (mech ? mech : 0x00001085); /* CKM_AES_CBC_PAD */
	p = ((u8 *) req_pl) + माप(*req_pl);
	अगर (iv) अणु
		स_नकल(p, iv, 16);
		p += 16;
	पूर्ण
	/* kek */
	p += asn1tag_ग_लिखो(p, 0x04, kek, keksize);
	/* empty mac key tag */
	*p++ = 0x04;
	*p++ = 0;
	/* empty pin tag */
	*p++ = 0x04;
	*p++ = 0;
	/* encrypted key value tag and bytes */
	p += asn1tag_ग_लिखो(p, 0x04, enckey, enckeysize);

	/* reply cprb and payload */
	rep = alloc_cprb(माप(काष्ठा uw_rep_pl));
	अगर (!rep)
		जाओ out;
	rep_pl = (काष्ठा uw_rep_pl *) (((u8 *) rep) + माप(*rep));

	/* urb and target */
	urb = kदो_स्मृति(माप(काष्ठा ep11_urb), GFP_KERNEL);
	अगर (!urb)
		जाओ out;
	target.ap_id = card;
	target.करोm_id = करोमुख्य;
	prep_urb(urb, &target, 1,
		 req, माप(*req) + req_pl_size,
		 rep, माप(*rep) + माप(*rep_pl));

	rc = zcrypt_send_ep11_cprb(urb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_ep11_cprb(card=%d dom=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) card, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	rc = check_reply_pl((u8 *)rep_pl, __func__);
	अगर (rc)
		जाओ out;
	अगर (rep_pl->data_tag != 0x04 || rep_pl->data_lenfmt != 0x82) अणु
		DEBUG_ERR("%s unknown reply data format\n", __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (rep_pl->data_len > *keybufsize) अणु
		DEBUG_ERR("%s mismatch reply data len / key buffer len\n",
			  __func__);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	/* copy key blob and set header values */
	स_नकल(keybuf, rep_pl->data, rep_pl->data_len);
	*keybufsize = rep_pl->data_len;
	kb = (काष्ठा ep11keyblob *) keybuf;
	kb->head.type = TOKTYPE_NON_CCA;
	kb->head.len = rep_pl->data_len;
	kb->head.version = TOKVER_EP11_AES;
	kb->head.keybitlen = keybitsize;

out:
	kमुक्त(req);
	kमुक्त(rep);
	kमुक्त(urb);
	वापस rc;
पूर्ण

अटल पूर्णांक ep11_wrapkey(u16 card, u16 करोमुख्य,
			स्थिर u8 *key, माप_प्रकार keysize,
			u32 mech, स्थिर u8 *iv,
			u8 *databuf, माप_प्रकार *datasize)
अणु
	काष्ठा wk_req_pl अणु
		काष्ठा pl_head head;
		u8  var_tag;
		u8  var_len;
		u32 var;
		u8  mech_tag;
		u8  mech_len;
		u32 mech;
		/*
		 * followed by iv data
		 * followed by key tag + key blob
		 * followed by dummy kek param
		 * followed by dummy mac param
		 */
	पूर्ण __packed * req_pl;
	काष्ठा wk_rep_pl अणु
		काष्ठा pl_head head;
		u8  rc_tag;
		u8  rc_len;
		u32 rc;
		u8  data_tag;
		u8  data_lenfmt;
		u16 data_len;
		u8  data[1024];
	पूर्ण __packed * rep_pl;
	काष्ठा ep11_cprb *req = शून्य, *rep = शून्य;
	काष्ठा ep11_target_dev target;
	काष्ठा ep11_urb *urb = शून्य;
	काष्ठा ep11keyblob *kb;
	माप_प्रकार req_pl_size;
	पूर्णांक api, rc = -ENOMEM;
	bool has_header = false;
	u8 *p;

	/* maybe the session field holds a header with key info */
	kb = (काष्ठा ep11keyblob *) key;
	अगर (kb->head.type == TOKTYPE_NON_CCA &&
	    kb->head.version == TOKVER_EP11_AES) अणु
		has_header = true;
		keysize = kb->head.len < keysize ? kb->head.len : keysize;
	पूर्ण

	/* request cprb and payload */
	req_pl_size = माप(काष्ठा wk_req_pl) + (iv ? 16 : 0)
		+ ASN1TAGLEN(keysize) + 4;
	req = alloc_cprb(req_pl_size);
	अगर (!req)
		जाओ out;
	अगर (!mech || mech == 0x80060001)
		req->flags |= 0x20; /* CPACF_WRAP needs special bit */
	req_pl = (काष्ठा wk_req_pl *) (((u8 *) req) + माप(*req));
	api = (!mech || mech == 0x80060001) ? 4 : 1; /* CKM_IBM_CPACF_WRAP */
	prep_head(&req_pl->head, req_pl_size, api, 33); /* WrapKey */
	req_pl->var_tag = 0x04;
	req_pl->var_len = माप(u32);
	/* mech is mech + mech params (iv here) */
	req_pl->mech_tag = 0x04;
	req_pl->mech_len = माप(u32) + (iv ? 16 : 0);
	req_pl->mech = (mech ? mech : 0x80060001); /* CKM_IBM_CPACF_WRAP */
	p = ((u8 *) req_pl) + माप(*req_pl);
	अगर (iv) अणु
		स_नकल(p, iv, 16);
		p += 16;
	पूर्ण
	/* key blob */
	p += asn1tag_ग_लिखो(p, 0x04, key, keysize);
	/* maybe the key argument needs the head data cleaned out */
	अगर (has_header) अणु
		kb = (काष्ठा ep11keyblob *)(p - keysize);
		स_रखो(&kb->head, 0, माप(kb->head));
	पूर्ण
	/* empty kek tag */
	*p++ = 0x04;
	*p++ = 0;
	/* empty mac tag */
	*p++ = 0x04;
	*p++ = 0;

	/* reply cprb and payload */
	rep = alloc_cprb(माप(काष्ठा wk_rep_pl));
	अगर (!rep)
		जाओ out;
	rep_pl = (काष्ठा wk_rep_pl *) (((u8 *) rep) + माप(*rep));

	/* urb and target */
	urb = kदो_स्मृति(माप(काष्ठा ep11_urb), GFP_KERNEL);
	अगर (!urb)
		जाओ out;
	target.ap_id = card;
	target.करोm_id = करोमुख्य;
	prep_urb(urb, &target, 1,
		 req, माप(*req) + req_pl_size,
		 rep, माप(*rep) + माप(*rep_pl));

	rc = zcrypt_send_ep11_cprb(urb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_ep11_cprb(card=%d dom=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) card, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	rc = check_reply_pl((u8 *)rep_pl, __func__);
	अगर (rc)
		जाओ out;
	अगर (rep_pl->data_tag != 0x04 || rep_pl->data_lenfmt != 0x82) अणु
		DEBUG_ERR("%s unknown reply data format\n", __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (rep_pl->data_len > *datasize) अणु
		DEBUG_ERR("%s mismatch reply data len / data buffer len\n",
			  __func__);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	/* copy the data from the cprb to the data buffer */
	स_नकल(databuf, rep_pl->data, rep_pl->data_len);
	*datasize = rep_pl->data_len;

out:
	kमुक्त(req);
	kमुक्त(rep);
	kमुक्त(urb);
	वापस rc;
पूर्ण

पूर्णांक ep11_clr2keyblob(u16 card, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		     स्थिर u8 *clrkey, u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	पूर्णांक rc;
	काष्ठा ep11keyblob *kb;
	u8 encbuf[64], *kek = शून्य;
	माप_प्रकार clrkeylen, keklen, encbuflen = माप(encbuf);

	अगर (keybitsize == 128 || keybitsize == 192 || keybitsize == 256)
		clrkeylen = keybitsize / 8;
	अन्यथा अणु
		DEBUG_ERR(
			"%s unknown/unsupported keybitsize %d\n",
			__func__, keybitsize);
		वापस -EINVAL;
	पूर्ण

	/* allocate memory क्रम the temp kek */
	keklen = MAXEP11AESKEYBLOBSIZE;
	kek = kदो_स्मृति(keklen, GFP_ATOMIC);
	अगर (!kek) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Step 1: generate AES 256 bit अक्रमom kek key */
	rc = ep11_genaeskey(card, करोमुख्य, 256,
			    0x00006c00, /* EN/DECRYPT, WRAP/UNWRAP */
			    kek, &keklen);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s generate kek key failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	kb = (काष्ठा ep11keyblob *) kek;
	स_रखो(&kb->head, 0, माप(kb->head));

	/* Step 2: encrypt clear key value with the kek key */
	rc = ep11_cryptsingle(card, करोमुख्य, 0, 0, def_iv, kek, keklen,
			      clrkey, clrkeylen, encbuf, &encbuflen);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s encrypting key value with kek key failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	/* Step 3: import the encrypted key value as a new key */
	rc = ep11_unwrapkey(card, करोमुख्य, kek, keklen,
			    encbuf, encbuflen, 0, def_iv,
			    keybitsize, 0, keybuf, keybufsize);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s importing key value as new key failed,, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

out:
	kमुक्त(kek);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_clr2keyblob);

पूर्णांक ep11_kblob2protkey(u16 card, u16 करोm, स्थिर u8 *keyblob, माप_प्रकार keybloblen,
		       u8 *protkey, u32 *protkeylen, u32 *protkeytype)
अणु
	पूर्णांक rc = -EIO;
	u8 *wkbuf = शून्य;
	माप_प्रकार wkbuflen, keylen;
	काष्ठा wk_info अणु
		u16 version;
		u8  res1[16];
		u32 pkeytype;
		u32 pkeybitsize;
		u64 pkeysize;
		u8  res2[8];
		u8  pkey[0];
	पूर्ण __packed * wki;
	स्थिर u8 *key;
	काष्ठा ep11kblob_header *hdr;

	/* key with or without header ? */
	hdr = (काष्ठा ep11kblob_header *) keyblob;
	अगर (hdr->type == TOKTYPE_NON_CCA
	    && (hdr->version == TOKVER_EP11_AES_WITH_HEADER
		|| hdr->version == TOKVER_EP11_ECC_WITH_HEADER)
	    && is_ep11_keyblob(keyblob + माप(काष्ठा ep11kblob_header))) अणु
		/* EP11 AES or ECC key with header */
		key = keyblob + माप(काष्ठा ep11kblob_header);
		keylen = hdr->len - माप(काष्ठा ep11kblob_header);
	पूर्ण अन्यथा अगर (hdr->type == TOKTYPE_NON_CCA
		   && hdr->version == TOKVER_EP11_AES
		   && is_ep11_keyblob(keyblob)) अणु
		/* EP11 AES key (old style) */
		key = keyblob;
		keylen = hdr->len;
	पूर्ण अन्यथा अगर (is_ep11_keyblob(keyblob)) अणु
		/* raw EP11 key blob */
		key = keyblob;
		keylen = keybloblen;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/* alloc temp working buffer */
	wkbuflen = (keylen + AES_BLOCK_SIZE) & (~(AES_BLOCK_SIZE - 1));
	wkbuf = kदो_स्मृति(wkbuflen, GFP_ATOMIC);
	अगर (!wkbuf)
		वापस -ENOMEM;

	/* ep11 secure key -> रक्षित key + info */
	rc = ep11_wrapkey(card, करोm, key, keylen,
			  0, def_iv, wkbuf, &wkbuflen);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s rewrapping ep11 key to pkey failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	wki = (काष्ठा wk_info *) wkbuf;

	/* check काष्ठा version and pkey type */
	अगर (wki->version != 1 || wki->pkeytype < 1 || wki->pkeytype > 5) अणु
		DEBUG_ERR("%s wk info version %d or pkeytype %d mismatch.\n",
			  __func__, (पूर्णांक) wki->version, (पूर्णांक) wki->pkeytype);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* check रक्षित key type field */
	चयन (wki->pkeytype) अणु
	हाल 1: /* AES */
		चयन (wki->pkeysize) अणु
		हाल 16+32:
			/* AES 128 रक्षित key */
			अगर (protkeytype)
				*protkeytype = PKEY_KEYTYPE_AES_128;
			अवरोध;
		हाल 24+32:
			/* AES 192 रक्षित key */
			अगर (protkeytype)
				*protkeytype = PKEY_KEYTYPE_AES_192;
			अवरोध;
		हाल 32+32:
			/* AES 256 रक्षित key */
			अगर (protkeytype)
				*protkeytype = PKEY_KEYTYPE_AES_256;
			अवरोध;
		शेष:
			DEBUG_ERR("%s unknown/unsupported AES pkeysize %d\n",
				  __func__, (पूर्णांक) wki->pkeysize);
			rc = -EIO;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल 3: /* EC-P */
	हाल 4: /* EC-ED */
	हाल 5: /* EC-BP */
		अगर (protkeytype)
			*protkeytype = PKEY_KEYTYPE_ECC;
		अवरोध;
	हाल 2: /* TDES */
	शेष:
		DEBUG_ERR("%s unknown/unsupported key type %d\n",
			  __func__, (पूर्णांक) wki->pkeytype);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the tanslated रक्षित key */
	अगर (wki->pkeysize > *protkeylen) अणु
		DEBUG_ERR("%s wk info pkeysize %llu > protkeysize %u\n",
			  __func__, wki->pkeysize, *protkeylen);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	स_नकल(protkey, wki->pkey, wki->pkeysize);
	*protkeylen = wki->pkeysize;

out:
	kमुक्त(wkbuf);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_kblob2protkey);

पूर्णांक ep11_findcard2(u32 **apqns, u32 *nr_apqns, u16 cardnr, u16 करोमुख्य,
		   पूर्णांक minhwtype, पूर्णांक minapi, स्थिर u8 *wkvp)
अणु
	काष्ठा zcrypt_device_status_ext *device_status;
	u32 *_apqns = शून्य, _nr_apqns = 0;
	पूर्णांक i, card, करोm, rc = -ENOMEM;
	काष्ठा ep11_करोमुख्य_info edi;
	काष्ठा ep11_card_info eci;

	/* fetch status of all crypto cards */
	device_status = kvदो_स्मृति_array(MAX_ZDEV_ENTRIES_EXT,
				       माप(काष्ठा zcrypt_device_status_ext),
				       GFP_KERNEL);
	अगर (!device_status)
		वापस -ENOMEM;
	zcrypt_device_status_mask_ext(device_status);

	/* allocate 1k space क्रम up to 256 apqns */
	_apqns = kदो_स्मृति_array(256, माप(u32), GFP_KERNEL);
	अगर (!_apqns) अणु
		kvमुक्त(device_status);
		वापस -ENOMEM;
	पूर्ण

	/* walk through all the crypto apqnss */
	क्रम (i = 0; i < MAX_ZDEV_ENTRIES_EXT; i++) अणु
		card = AP_QID_CARD(device_status[i].qid);
		करोm = AP_QID_QUEUE(device_status[i].qid);
		/* check online state */
		अगर (!device_status[i].online)
			जारी;
		/* check क्रम ep11 functions */
		अगर (!(device_status[i].functions & 0x01))
			जारी;
		/* check cardnr */
		अगर (cardnr != 0xFFFF && card != cardnr)
			जारी;
		/* check करोमुख्य */
		अगर (करोमुख्य != 0xFFFF && करोm != करोमुख्य)
			जारी;
		/* check min hardware type */
		अगर (minhwtype && device_status[i].hwtype < minhwtype)
			जारी;
		/* check min api version अगर given */
		अगर (minapi > 0) अणु
			अगर (ep11_get_card_info(card, &eci, 0))
				जारी;
			अगर (minapi > eci.API_ord_nr)
				जारी;
		पूर्ण
		/* check wkvp अगर given */
		अगर (wkvp) अणु
			अगर (ep11_get_करोमुख्य_info(card, करोm, &edi))
				जारी;
			अगर (edi.cur_wk_state != '1')
				जारी;
			अगर (स_भेद(wkvp, edi.cur_wkvp, 16))
				जारी;
		पूर्ण
		/* apqn passed all filtering criterons, add to the array */
		अगर (_nr_apqns < 256)
			_apqns[_nr_apqns++] = (((u16)card) << 16) | ((u16) करोm);
	पूर्ण

	/* nothing found ? */
	अगर (!_nr_apqns) अणु
		kमुक्त(_apqns);
		rc = -ENODEV;
	पूर्ण अन्यथा अणु
		/* no re-allocation, simple वापस the _apqns array */
		*apqns = _apqns;
		*nr_apqns = _nr_apqns;
		rc = 0;
	पूर्ण

	kvमुक्त(device_status);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ep11_findcard2);

व्योम __निकास zcrypt_ep11misc_निकास(व्योम)
अणु
	card_cache_मुक्त();
पूर्ण
