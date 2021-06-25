<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2019
 *  Author(s): Harald Freudenberger <freude@linux.ibm.com>
 *	       Ingo Franzki <अगरranzki@linux.ibm.com>
 *
 *  Collection of CCA misc functions used by zcrypt and pkey
 */

#घोषणा KMSG_COMPONENT "zcrypt"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/zcrypt.h>
#समावेश <यंत्र/pkey.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_debug.h"
#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_ccamisc.h"

#घोषणा DEBUG_DBG(...)	ZCRYPT_DBF(DBF_DEBUG, ##__VA_ARGS__)
#घोषणा DEBUG_INFO(...) ZCRYPT_DBF(DBF_INFO, ##__VA_ARGS__)
#घोषणा DEBUG_WARN(...) ZCRYPT_DBF(DBF_WARN, ##__VA_ARGS__)
#घोषणा DEBUG_ERR(...)	ZCRYPT_DBF(DBF_ERR, ##__VA_ARGS__)

/* Size of parameter block used क्रम all cca requests/replies */
#घोषणा PARMBSIZE 512

/* Size of vardata block used क्रम some of the cca requests/replies */
#घोषणा VARDATASIZE 4096

काष्ठा cca_info_list_entry अणु
	काष्ठा list_head list;
	u16 cardnr;
	u16 करोमुख्य;
	काष्ठा cca_info info;
पूर्ण;

/* a list with cca_info_list_entry entries */
अटल LIST_HEAD(cca_info_list);
अटल DEFINE_SPINLOCK(cca_info_list_lock);

/*
 * Simple check अगर the token is a valid CCA secure AES data key
 * token. If keybitsize is given, the bitsize of the key is
 * also checked. Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_secaeskeytoken(debug_info_t *dbg, पूर्णांक dbflvl,
			     स्थिर u8 *token, पूर्णांक keybitsize)
अणु
	काष्ठा secaeskeytoken *t = (काष्ठा secaeskeytoken *) token;

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (t->type != TOKTYPE_CCA_INTERNAL) अणु
		अगर (dbg)
			DBF("%s token check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) t->type, TOKTYPE_CCA_INTERNAL);
		वापस -EINVAL;
	पूर्ण
	अगर (t->version != TOKVER_CCA_AES) अणु
		अगर (dbg)
			DBF("%s token check failed, version 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) t->version, TOKVER_CCA_AES);
		वापस -EINVAL;
	पूर्ण
	अगर (keybitsize > 0 && t->bitsize != keybitsize) अणु
		अगर (dbg)
			DBF("%s token check failed, bitsize %d != %d\n",
			    __func__, (पूर्णांक) t->bitsize, keybitsize);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cca_check_secaeskeytoken);

/*
 * Simple check अगर the token is a valid CCA secure AES cipher key
 * token. If keybitsize is given, the bitsize of the key is
 * also checked. If checkcpacfexport is enabled, the key is also
 * checked क्रम the export flag to allow CPACF export.
 * Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_secaescipherkey(debug_info_t *dbg, पूर्णांक dbflvl,
			      स्थिर u8 *token, पूर्णांक keybitsize,
			      पूर्णांक checkcpacfexport)
अणु
	काष्ठा cipherkeytoken *t = (काष्ठा cipherkeytoken *) token;
	bool keybitsizeok = true;

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (t->type != TOKTYPE_CCA_INTERNAL) अणु
		अगर (dbg)
			DBF("%s token check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) t->type, TOKTYPE_CCA_INTERNAL);
		वापस -EINVAL;
	पूर्ण
	अगर (t->version != TOKVER_CCA_VLSC) अणु
		अगर (dbg)
			DBF("%s token check failed, version 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) t->version, TOKVER_CCA_VLSC);
		वापस -EINVAL;
	पूर्ण
	अगर (t->algtype != 0x02) अणु
		अगर (dbg)
			DBF("%s token check failed, algtype 0x%02x != 0x02\n",
			    __func__, (पूर्णांक) t->algtype);
		वापस -EINVAL;
	पूर्ण
	अगर (t->keytype != 0x0001) अणु
		अगर (dbg)
			DBF("%s token check failed, keytype 0x%04x != 0x0001\n",
			    __func__, (पूर्णांक) t->keytype);
		वापस -EINVAL;
	पूर्ण
	अगर (t->plfver != 0x00 && t->plfver != 0x01) अणु
		अगर (dbg)
			DBF("%s token check failed, unknown plfver 0x%02x\n",
			    __func__, (पूर्णांक) t->plfver);
		वापस -EINVAL;
	पूर्ण
	अगर (t->wpllen != 512 && t->wpllen != 576 && t->wpllen != 640) अणु
		अगर (dbg)
			DBF("%s token check failed, unknown wpllen %d\n",
			    __func__, (पूर्णांक) t->wpllen);
		वापस -EINVAL;
	पूर्ण
	अगर (keybitsize > 0) अणु
		चयन (keybitsize) अणु
		हाल 128:
			अगर (t->wpllen != (t->plfver ? 640 : 512))
				keybitsizeok = false;
			अवरोध;
		हाल 192:
			अगर (t->wpllen != (t->plfver ? 640 : 576))
				keybitsizeok = false;
			अवरोध;
		हाल 256:
			अगर (t->wpllen != 640)
				keybitsizeok = false;
			अवरोध;
		शेष:
			keybitsizeok = false;
			अवरोध;
		पूर्ण
		अगर (!keybitsizeok) अणु
			अगर (dbg)
				DBF("%s token check failed, bitsize %d\n",
				    __func__, keybitsize);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (checkcpacfexport && !(t->kmf1 & KMF1_XPRT_CPAC)) अणु
		अगर (dbg)
			DBF("%s token check failed, XPRT_CPAC bit is 0\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cca_check_secaescipherkey);

/*
 * Simple check अगर the token is a valid CCA secure ECC निजी
 * key token. Returns 0 on success or त्रुटि_सं value on failure.
 */
पूर्णांक cca_check_sececckeytoken(debug_info_t *dbg, पूर्णांक dbflvl,
			     स्थिर u8 *token, माप_प्रकार keysize,
			     पूर्णांक checkcpacfexport)
अणु
	काष्ठा eccprivkeytoken *t = (काष्ठा eccprivkeytoken *) token;

#घोषणा DBF(...) debug_प्र_लिखो_event(dbg, dbflvl, ##__VA_ARGS__)

	अगर (t->type != TOKTYPE_CCA_INTERNAL_PKA) अणु
		अगर (dbg)
			DBF("%s token check failed, type 0x%02x != 0x%02x\n",
			    __func__, (पूर्णांक) t->type, TOKTYPE_CCA_INTERNAL_PKA);
		वापस -EINVAL;
	पूर्ण
	अगर (t->len > keysize) अणु
		अगर (dbg)
			DBF("%s token check failed, len %d > keysize %zu\n",
			    __func__, (पूर्णांक) t->len, keysize);
		वापस -EINVAL;
	पूर्ण
	अगर (t->secid != 0x20) अणु
		अगर (dbg)
			DBF("%s token check failed, secid 0x%02x != 0x20\n",
			    __func__, (पूर्णांक) t->secid);
		वापस -EINVAL;
	पूर्ण
	अगर (checkcpacfexport && !(t->kutc & 0x01)) अणु
		अगर (dbg)
			DBF("%s token check failed, XPRTCPAC bit is 0\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

#अघोषित DBF

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cca_check_sececckeytoken);

/*
 * Allocate consecutive memory क्रम request CPRB, request param
 * block, reply CPRB and reply param block and fill in values
 * क्रम the common fields. Returns 0 on success or त्रुटि_सं value
 * on failure.
 */
अटल पूर्णांक alloc_and_prep_cprbmem(माप_प्रकार paramblen,
				  u8 **pcprbmem,
				  काष्ठा CPRBX **preqCPRB,
				  काष्ठा CPRBX **prepCPRB)
अणु
	u8 *cprbmem;
	माप_प्रकार cprbplusparamblen = माप(काष्ठा CPRBX) + paramblen;
	काष्ठा CPRBX *preqcblk, *prepcblk;

	/*
	 * allocate consecutive memory क्रम request CPRB, request param
	 * block, reply CPRB and reply param block
	 */
	cprbmem = kसुस्मृति(2, cprbplusparamblen, GFP_KERNEL);
	अगर (!cprbmem)
		वापस -ENOMEM;

	preqcblk = (काष्ठा CPRBX *) cprbmem;
	prepcblk = (काष्ठा CPRBX *) (cprbmem + cprbplusparamblen);

	/* fill request cprb काष्ठा */
	preqcblk->cprb_len = माप(काष्ठा CPRBX);
	preqcblk->cprb_ver_id = 0x02;
	स_नकल(preqcblk->func_id, "T2", 2);
	preqcblk->rpl_msgbl = cprbplusparamblen;
	अगर (paramblen) अणु
		preqcblk->req_parmb =
			((u8 __user *) preqcblk) + माप(काष्ठा CPRBX);
		preqcblk->rpl_parmb =
			((u8 __user *) prepcblk) + माप(काष्ठा CPRBX);
	पूर्ण

	*pcprbmem = cprbmem;
	*preqCPRB = preqcblk;
	*prepCPRB = prepcblk;

	वापस 0;
पूर्ण

/*
 * Free the cprb memory allocated with the function above.
 * If the scrub value is not zero, the memory is filled
 * with zeros beक्रमe मुक्तing (useful अगर there was some
 * clear key material in there).
 */
अटल व्योम मुक्त_cprbmem(व्योम *mem, माप_प्रकार paramblen, पूर्णांक scrub)
अणु
	अगर (scrub)
		memzero_explicit(mem, 2 * (माप(काष्ठा CPRBX) + paramblen));
	kमुक्त(mem);
पूर्ण

/*
 * Helper function to prepare the xcrb काष्ठा
 */
अटल अंतरभूत व्योम prep_xcrb(काष्ठा ica_xcRB *pxcrb,
			     u16 cardnr,
			     काष्ठा CPRBX *preqcblk,
			     काष्ठा CPRBX *prepcblk)
अणु
	स_रखो(pxcrb, 0, माप(*pxcrb));
	pxcrb->agent_ID = 0x4341; /* 'CA' */
	pxcrb->user_defined = (cardnr == 0xFFFF ? AUTOSELECT : cardnr);
	pxcrb->request_control_blk_length =
		preqcblk->cprb_len + preqcblk->req_parml;
	pxcrb->request_control_blk_addr = (व्योम __user *) preqcblk;
	pxcrb->reply_control_blk_length = preqcblk->rpl_msgbl;
	pxcrb->reply_control_blk_addr = (व्योम __user *) prepcblk;
पूर्ण

/*
 * Generate (अक्रमom) CCA AES DATA secure key.
 */
पूर्णांक cca_genseckey(u16 cardnr, u16 करोमुख्य,
		  u32 keybitsize, u8 seckey[SECKEYBLOBSIZE])
अणु
	पूर्णांक i, rc, keysize;
	पूर्णांक seckeysize;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा kgreqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा lv1 अणु
			u16 len;
			अक्षर  key_क्रमm[8];
			अक्षर  key_length[8];
			अक्षर  key_type1[8];
			अक्षर  key_type2[8];
		पूर्ण lv1;
		काष्ठा lv2 अणु
			u16 len;
			काष्ठा keyid अणु
				u16 len;
				u16 attr;
				u8  data[SECKEYBLOBSIZE];
			पूर्ण keyid[6];
		पूर्ण lv2;
	पूर्ण __packed * preqparm;
	काष्ठा kgrepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा lv3 अणु
			u16 len;
			u16 keyblocklen;
			काष्ठा अणु
				u16 toklen;
				u16 tokattr;
				u8  tok[0];
				/* ... some more data ... */
			पूर्ण keyblock;
		पूर्ण lv3;
	पूर्ण __packed * prepparm;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with KG request */
	preqparm = (काष्ठा kgreqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "KG", 2);
	preqparm->rule_array_len = माप(preqparm->rule_array_len);
	preqparm->lv1.len = माप(काष्ठा lv1);
	स_नकल(preqparm->lv1.key_क्रमm,	 "OP      ", 8);
	चयन (keybitsize) अणु
	हाल PKEY_SIZE_AES_128:
	हाल PKEY_KEYTYPE_AES_128: /* older ioctls used this */
		keysize = 16;
		स_नकल(preqparm->lv1.key_length, "KEYLN16 ", 8);
		अवरोध;
	हाल PKEY_SIZE_AES_192:
	हाल PKEY_KEYTYPE_AES_192: /* older ioctls used this */
		keysize = 24;
		स_नकल(preqparm->lv1.key_length, "KEYLN24 ", 8);
		अवरोध;
	हाल PKEY_SIZE_AES_256:
	हाल PKEY_KEYTYPE_AES_256: /* older ioctls used this */
		keysize = 32;
		स_नकल(preqparm->lv1.key_length, "KEYLN32 ", 8);
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported keybitsize %d\n",
			  __func__, keybitsize);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	स_नकल(preqparm->lv1.key_type1,  "AESDATA ", 8);
	preqparm->lv2.len = माप(काष्ठा lv2);
	क्रम (i = 0; i < 6; i++) अणु
		preqparm->lv2.keyid[i].len = माप(काष्ठा keyid);
		preqparm->lv2.keyid[i].attr = (i == 2 ? 0x30 : 0x10);
	पूर्ण
	preqcblk->req_parml = माप(काष्ठा kgreqparm);

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR("%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, errno %d\n",
			  __func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR("%s secure key generate failure, card response %d/%d\n",
			  __func__,
			  (पूर्णांक) prepcblk->ccp_rtcode,
			  (पूर्णांक) prepcblk->ccp_rscode);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* process response cprb param block */
	ptr =  ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा kgrepparm *) ptr;

	/* check length of the वापसed secure key token */
	seckeysize = prepparm->lv3.keyblock.toklen
		- माप(prepparm->lv3.keyblock.toklen)
		- माप(prepparm->lv3.keyblock.tokattr);
	अगर (seckeysize != SECKEYBLOBSIZE) अणु
		DEBUG_ERR("%s secure token size mismatch %d != %d bytes\n",
			  __func__, seckeysize, SECKEYBLOBSIZE);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* check secure key token */
	rc = cca_check_secaeskeytoken(zcrypt_dbf_info, DBF_ERR,
				      prepparm->lv3.keyblock.tok, 8*keysize);
	अगर (rc) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the generated secure key token */
	स_नकल(seckey, prepparm->lv3.keyblock.tok, SECKEYBLOBSIZE);

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_genseckey);

/*
 * Generate an CCA AES DATA secure key with given key value.
 */
पूर्णांक cca_clr2seckey(u16 cardnr, u16 करोमुख्य, u32 keybitsize,
		   स्थिर u8 *clrkey, u8 seckey[SECKEYBLOBSIZE])
अणु
	पूर्णांक rc, keysize, seckeysize;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा cmreqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		अक्षर  rule_array[8];
		काष्ठा lv1 अणु
			u16 len;
			u8  clrkey[0];
		पूर्ण lv1;
		काष्ठा lv2 अणु
			u16 len;
			काष्ठा keyid अणु
				u16 len;
				u16 attr;
				u8  data[SECKEYBLOBSIZE];
			पूर्ण keyid;
		पूर्ण lv2;
	पूर्ण __packed * preqparm;
	काष्ठा lv2 *plv2;
	काष्ठा cmrepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा lv3 अणु
			u16 len;
			u16 keyblocklen;
			काष्ठा अणु
				u16 toklen;
				u16 tokattr;
				u8  tok[0];
				/* ... some more data ... */
			पूर्ण keyblock;
		पूर्ण lv3;
	पूर्ण __packed * prepparm;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with CM request */
	preqparm = (काष्ठा cmreqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "CM", 2);
	स_नकल(preqparm->rule_array, "AES     ", 8);
	preqparm->rule_array_len =
		माप(preqparm->rule_array_len) + माप(preqparm->rule_array);
	चयन (keybitsize) अणु
	हाल PKEY_SIZE_AES_128:
	हाल PKEY_KEYTYPE_AES_128: /* older ioctls used this */
		keysize = 16;
		अवरोध;
	हाल PKEY_SIZE_AES_192:
	हाल PKEY_KEYTYPE_AES_192: /* older ioctls used this */
		keysize = 24;
		अवरोध;
	हाल PKEY_SIZE_AES_256:
	हाल PKEY_KEYTYPE_AES_256: /* older ioctls used this */
		keysize = 32;
		अवरोध;
	शेष:
		DEBUG_ERR("%s unknown/unsupported keybitsize %d\n",
			  __func__, keybitsize);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	preqparm->lv1.len = माप(काष्ठा lv1) + keysize;
	स_नकल(preqparm->lv1.clrkey, clrkey, keysize);
	plv2 = (काष्ठा lv2 *) (((u8 *) &preqparm->lv2) + keysize);
	plv2->len = माप(काष्ठा lv2);
	plv2->keyid.len = माप(काष्ठा keyid);
	plv2->keyid.attr = 0x30;
	preqcblk->req_parml = माप(काष्ठा cmreqparm) + keysize;

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR("%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			  __func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR("%s clear key import failure, card response %d/%d\n",
			  __func__,
			  (पूर्णांक) prepcblk->ccp_rtcode,
			  (पूर्णांक) prepcblk->ccp_rscode);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा cmrepparm *) ptr;

	/* check length of the वापसed secure key token */
	seckeysize = prepparm->lv3.keyblock.toklen
		- माप(prepparm->lv3.keyblock.toklen)
		- माप(prepparm->lv3.keyblock.tokattr);
	अगर (seckeysize != SECKEYBLOBSIZE) अणु
		DEBUG_ERR("%s secure token size mismatch %d != %d bytes\n",
			  __func__, seckeysize, SECKEYBLOBSIZE);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* check secure key token */
	rc = cca_check_secaeskeytoken(zcrypt_dbf_info, DBF_ERR,
				      prepparm->lv3.keyblock.tok, 8*keysize);
	अगर (rc) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the generated secure key token */
	अगर (seckey)
		स_नकल(seckey, prepparm->lv3.keyblock.tok, SECKEYBLOBSIZE);

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 1);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_clr2seckey);

/*
 * Derive proteced key from an CCA AES DATA secure key.
 */
पूर्णांक cca_sec2protkey(u16 cardnr, u16 करोमुख्य,
		    स्थिर u8 seckey[SECKEYBLOBSIZE],
		    u8 *protkey, u32 *protkeylen, u32 *protkeytype)
अणु
	पूर्णांक rc;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा uskreqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा lv1 अणु
			u16 len;
			u16 attr_len;
			u16 attr_flags;
		पूर्ण lv1;
		काष्ठा lv2 अणु
			u16 len;
			u16 attr_len;
			u16 attr_flags;
			u8  token[0];	      /* cca secure key token */
		पूर्ण lv2;
	पूर्ण __packed * preqparm;
	काष्ठा uskrepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा lv3 अणु
			u16 len;
			u16 attr_len;
			u16 attr_flags;
			काष्ठा cpacfkeyblock अणु
				u8  version;  /* version of this काष्ठा */
				u8  flags[2];
				u8  algo;
				u8  क्रमm;
				u8  pad1[3];
				u16 len;
				u8  key[64];  /* the key (len bytes) */
				u16 keyattrlen;
				u8  keyattr[32];
				u8  pad2[1];
				u8  vptype;
				u8  vp[32];  /* verअगरication pattern */
			पूर्ण ckb;
		पूर्ण lv3;
	पूर्ण __packed * prepparm;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with USK request */
	preqparm = (काष्ठा uskreqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "US", 2);
	preqparm->rule_array_len = माप(preqparm->rule_array_len);
	preqparm->lv1.len = माप(काष्ठा lv1);
	preqparm->lv1.attr_len = माप(काष्ठा lv1) - माप(preqparm->lv1.len);
	preqparm->lv1.attr_flags = 0x0001;
	preqparm->lv2.len = माप(काष्ठा lv2) + SECKEYBLOBSIZE;
	preqparm->lv2.attr_len = माप(काष्ठा lv2)
		- माप(preqparm->lv2.len) + SECKEYBLOBSIZE;
	preqparm->lv2.attr_flags = 0x0000;
	स_नकल(preqparm->lv2.token, seckey, SECKEYBLOBSIZE);
	preqcblk->req_parml = माप(काष्ठा uskreqparm) + SECKEYBLOBSIZE;

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR("%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			  __func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR("%s unwrap secure key failure, card response %d/%d\n",
			  __func__,
			  (पूर्णांक) prepcblk->ccp_rtcode,
			  (पूर्णांक) prepcblk->ccp_rscode);
		अगर (prepcblk->ccp_rtcode == 8 && prepcblk->ccp_rscode == 2290)
			rc = -EAGAIN;
		अन्यथा
			rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (prepcblk->ccp_rscode != 0) अणु
		DEBUG_WARN("%s unwrap secure key warning, card response %d/%d\n",
			   __func__,
			   (पूर्णांक) prepcblk->ccp_rtcode,
			   (पूर्णांक) prepcblk->ccp_rscode);
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा uskrepparm *) ptr;

	/* check the वापसed keyblock */
	अगर (prepparm->lv3.ckb.version != 0x01 &&
	    prepparm->lv3.ckb.version != 0x02) अणु
		DEBUG_ERR("%s reply param keyblock version mismatch 0x%02x\n",
			  __func__, (पूर्णांक) prepparm->lv3.ckb.version);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the tanslated रक्षित key */
	चयन (prepparm->lv3.ckb.len) अणु
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
		DEBUG_ERR("%s unknown/unsupported keylen %d\n",
			  __func__, prepparm->lv3.ckb.len);
		rc = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(protkey, prepparm->lv3.ckb.key, prepparm->lv3.ckb.len);
	अगर (protkeylen)
		*protkeylen = prepparm->lv3.ckb.len;

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_sec2protkey);

/*
 * AES cipher key skeleton created with CSNBKTB2 with these flags:
 * INTERNAL, NO-KEY, AES, CIPHER, ANY-MODE, NOEX-SYM, NOEXAASY,
 * NOEXUASY, XPRTCPAC, NOEX-RAW, NOEX-DES, NOEX-AES, NOEX-RSA
 * used by cca_gencipherkey() and cca_clr2cipherkey().
 */
अटल स्थिर u8 aes_cipher_key_skeleton[] = अणु
	0x01, 0x00, 0x00, 0x38, 0x05, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x00, 0x01, 0x02, 0xc0, 0x00, 0xff,
	0x00, 0x03, 0x08, 0xc8, 0x00, 0x00, 0x00, 0x00 पूर्ण;
#घोषणा SIZखातापूर्ण_SKELETON (माप(aes_cipher_key_skeleton))

/*
 * Generate (अक्रमom) CCA AES CIPHER secure key.
 */
पूर्णांक cca_gencipherkey(u16 cardnr, u16 करोमुख्य, u32 keybitsize, u32 keygenflags,
		     u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	पूर्णांक rc;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा gkreqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		अक्षर rule_array[2*8];
		काष्ठा अणु
			u16 len;
			u8  key_type_1[8];
			u8  key_type_2[8];
			u16 clear_key_bit_len;
			u16 key_name_1_len;
			u16 key_name_2_len;
			u16 user_data_1_len;
			u16 user_data_2_len;
			u8  key_name_1[0];
			u8  key_name_2[0];
			u8  user_data_1[0];
			u8  user_data_2[0];
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  kek_id_1[0];
			पूर्ण tlv1;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  kek_id_2[0];
			पूर्ण tlv2;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  gen_key_id_1[SIZखातापूर्ण_SKELETON];
			पूर्ण tlv3;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  gen_key_id_1_label[0];
			पूर्ण tlv4;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  gen_key_id_2[0];
			पूर्ण tlv5;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  gen_key_id_2_label[0];
			पूर्ण tlv6;
		पूर्ण kb;
	पूर्ण __packed * preqparm;
	काष्ठा gkrepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा अणु
			u16 len;
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
			काष्ठा अणु
				u16 len;
				u16 flag;
				u8  gen_key[0]; /* 120-136 bytes */
			पूर्ण tlv1;
		पूर्ण kb;
	पूर्ण __packed * prepparm;
	काष्ठा cipherkeytoken *t;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;
	preqcblk->req_parml = माप(काष्ठा gkreqparm);

	/* prepare request param block with GK request */
	preqparm = (काष्ठा gkreqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "GK", 2);
	preqparm->rule_array_len =  माप(uपूर्णांक16_t) + 2 * 8;
	स_नकल(preqparm->rule_array, "AES     OP      ", 2*8);

	/* prepare vud block */
	preqparm->vud.len = माप(preqparm->vud);
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
	preqparm->vud.clear_key_bit_len = keybitsize;
	स_नकल(preqparm->vud.key_type_1, "TOKEN   ", 8);
	स_रखो(preqparm->vud.key_type_2, ' ', माप(preqparm->vud.key_type_2));

	/* prepare kb block */
	preqparm->kb.len = माप(preqparm->kb);
	preqparm->kb.tlv1.len = माप(preqparm->kb.tlv1);
	preqparm->kb.tlv1.flag = 0x0030;
	preqparm->kb.tlv2.len = माप(preqparm->kb.tlv2);
	preqparm->kb.tlv2.flag = 0x0030;
	preqparm->kb.tlv3.len = माप(preqparm->kb.tlv3);
	preqparm->kb.tlv3.flag = 0x0030;
	स_नकल(preqparm->kb.tlv3.gen_key_id_1,
	       aes_cipher_key_skeleton, SIZखातापूर्ण_SKELETON);
	preqparm->kb.tlv4.len = माप(preqparm->kb.tlv4);
	preqparm->kb.tlv4.flag = 0x0030;
	preqparm->kb.tlv5.len = माप(preqparm->kb.tlv5);
	preqparm->kb.tlv5.flag = 0x0030;
	preqparm->kb.tlv6.len = माप(preqparm->kb.tlv6);
	preqparm->kb.tlv6.flag = 0x0030;

	/* patch the skeleton key token export flags inside the kb block */
	अगर (keygenflags) अणु
		t = (काष्ठा cipherkeytoken *) preqparm->kb.tlv3.gen_key_id_1;
		t->kmf1 |= (u16) (keygenflags & 0x0000FF00);
		t->kmf1 &= (u16) ~(keygenflags & 0x000000FF);
	पूर्ण

	/* prepare xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR(
			"%s cipher key generate failure, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा gkrepparm *) ptr;

	/* करो some plausibility checks on the key block */
	अगर (prepparm->kb.len < 120 + 5 * माप(uपूर्णांक16_t) ||
	    prepparm->kb.len > 136 + 5 * माप(uपूर्णांक16_t)) अणु
		DEBUG_ERR("%s reply with invalid or unknown key block\n",
			  __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* and some checks on the generated key */
	rc = cca_check_secaescipherkey(zcrypt_dbf_info, DBF_ERR,
				       prepparm->kb.tlv1.gen_key,
				       keybitsize, 1);
	अगर (rc) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the generated vlsc key token */
	t = (काष्ठा cipherkeytoken *) prepparm->kb.tlv1.gen_key;
	अगर (keybuf) अणु
		अगर (*keybufsize >= t->len)
			स_नकल(keybuf, t, t->len);
		अन्यथा
			rc = -EINVAL;
	पूर्ण
	*keybufsize = t->len;

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_gencipherkey);

/*
 * Helper function, करोes a the CSNBKPI2 CPRB.
 */
अटल पूर्णांक _ip_cprb_helper(u16 cardnr, u16 करोमुख्य,
			   स्थिर अक्षर *rule_array_1,
			   स्थिर अक्षर *rule_array_2,
			   स्थिर अक्षर *rule_array_3,
			   स्थिर u8 *clr_key_value,
			   पूर्णांक clr_key_bit_size,
			   u8 *key_token,
			   पूर्णांक *key_token_size)
अणु
	पूर्णांक rc, n;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा rule_array_block अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		अक्षर rule_array[0];
	पूर्ण __packed * preq_ra_block;
	काष्ठा vud_block अणु
		u16 len;
		काष्ठा अणु
			u16 len;
			u16 flag;	     /* 0x0064 */
			u16 clr_key_bit_len;
		पूर्ण tlv1;
		काष्ठा अणु
			u16 len;
			u16 flag;	/* 0x0063 */
			u8  clr_key[0]; /* clear key value bytes */
		पूर्ण tlv2;
	पूर्ण __packed * preq_vud_block;
	काष्ठा key_block अणु
		u16 len;
		काष्ठा अणु
			u16 len;
			u16 flag;	  /* 0x0030 */
			u8  key_token[0]; /* key skeleton */
		पूर्ण tlv1;
	पूर्ण __packed * preq_key_block;
	काष्ठा iprepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा अणु
			u16 len;
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
			काष्ठा अणु
				u16 len;
				u16 flag;	  /* 0x0030 */
				u8  key_token[0]; /* key token */
			पूर्ण tlv1;
		पूर्ण kb;
	पूर्ण __packed * prepparm;
	काष्ठा cipherkeytoken *t;
	पूर्णांक complete = म_भेदन(rule_array_2, "COMPLETE", 8) ? 0 : 1;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;
	preqcblk->req_parml = 0;

	/* prepare request param block with IP request */
	preq_ra_block = (काष्ठा rule_array_block __क्रमce *) preqcblk->req_parmb;
	स_नकल(preq_ra_block->subfunc_code, "IP", 2);
	preq_ra_block->rule_array_len =  माप(uपूर्णांक16_t) + 2 * 8;
	स_नकल(preq_ra_block->rule_array, rule_array_1, 8);
	स_नकल(preq_ra_block->rule_array + 8, rule_array_2, 8);
	preqcblk->req_parml = माप(काष्ठा rule_array_block) + 2 * 8;
	अगर (rule_array_3) अणु
		preq_ra_block->rule_array_len += 8;
		स_नकल(preq_ra_block->rule_array + 16, rule_array_3, 8);
		preqcblk->req_parml += 8;
	पूर्ण

	/* prepare vud block */
	preq_vud_block = (काष्ठा vud_block __क्रमce *)
		(preqcblk->req_parmb + preqcblk->req_parml);
	n = complete ? 0 : (clr_key_bit_size + 7) / 8;
	preq_vud_block->len = माप(काष्ठा vud_block) + n;
	preq_vud_block->tlv1.len = माप(preq_vud_block->tlv1);
	preq_vud_block->tlv1.flag = 0x0064;
	preq_vud_block->tlv1.clr_key_bit_len = complete ? 0 : clr_key_bit_size;
	preq_vud_block->tlv2.len = माप(preq_vud_block->tlv2) + n;
	preq_vud_block->tlv2.flag = 0x0063;
	अगर (!complete)
		स_नकल(preq_vud_block->tlv2.clr_key, clr_key_value, n);
	preqcblk->req_parml += preq_vud_block->len;

	/* prepare key block */
	preq_key_block = (काष्ठा key_block __क्रमce *)
		(preqcblk->req_parmb + preqcblk->req_parml);
	n = *key_token_size;
	preq_key_block->len = माप(काष्ठा key_block) + n;
	preq_key_block->tlv1.len = माप(preq_key_block->tlv1) + n;
	preq_key_block->tlv1.flag = 0x0030;
	स_नकल(preq_key_block->tlv1.key_token, key_token, *key_token_size);
	preqcblk->req_parml += preq_key_block->len;

	/* prepare xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR(
			"%s CSNBKPI2 failure, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा iprepparm *) ptr;

	/* करो some plausibility checks on the key block */
	अगर (prepparm->kb.len < 120 + 3 * माप(uपूर्णांक16_t) ||
	    prepparm->kb.len > 136 + 3 * माप(uपूर्णांक16_t)) अणु
		DEBUG_ERR("%s reply with invalid or unknown key block\n",
			  __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* करो not check the key here, it may be incomplete */

	/* copy the vlsc key token back */
	t = (काष्ठा cipherkeytoken *) prepparm->kb.tlv1.key_token;
	स_नकल(key_token, t, t->len);
	*key_token_size = t->len;

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण

/*
 * Build CCA AES CIPHER secure key with a given clear key value.
 */
पूर्णांक cca_clr2cipherkey(u16 card, u16 करोm, u32 keybitsize, u32 keygenflags,
		      स्थिर u8 *clrkey, u8 *keybuf, माप_प्रकार *keybufsize)
अणु
	पूर्णांक rc;
	u8 *token;
	पूर्णांक tokensize;
	u8 exorbuf[32];
	काष्ठा cipherkeytoken *t;

	/* fill exorbuf with अक्रमom data */
	get_अक्रमom_bytes(exorbuf, माप(exorbuf));

	/* allocate space क्रम the key token to build */
	token = kदो_स्मृति(MAXCCAVLSCTOKENSIZE, GFP_KERNEL);
	अगर (!token)
		वापस -ENOMEM;

	/* prepare the token with the key skeleton */
	tokensize = SIZखातापूर्ण_SKELETON;
	स_नकल(token, aes_cipher_key_skeleton, tokensize);

	/* patch the skeleton key token export flags */
	अगर (keygenflags) अणु
		t = (काष्ठा cipherkeytoken *) token;
		t->kmf1 |= (u16) (keygenflags & 0x0000FF00);
		t->kmf1 &= (u16) ~(keygenflags & 0x000000FF);
	पूर्ण

	/*
	 * Do the key import with the clear key value in 4 steps:
	 * 1/4 FIRST import with only अक्रमom data
	 * 2/4 EXOR the clear key
	 * 3/4 EXOR the very same अक्रमom data again
	 * 4/4 COMPLETE the secure cipher key import
	 */
	rc = _ip_cprb_helper(card, करोm, "AES     ", "FIRST   ", "MIN3PART",
			     exorbuf, keybitsize, token, &tokensize);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s clear key import 1/4 with CSNBKPI2 failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	rc = _ip_cprb_helper(card, करोm, "AES     ", "ADD-PART", शून्य,
			     clrkey, keybitsize, token, &tokensize);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s clear key import 2/4 with CSNBKPI2 failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	rc = _ip_cprb_helper(card, करोm, "AES     ", "ADD-PART", शून्य,
			     exorbuf, keybitsize, token, &tokensize);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s clear key import 3/4 with CSNBKPI2 failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	rc = _ip_cprb_helper(card, करोm, "AES     ", "COMPLETE", शून्य,
			     शून्य, keybitsize, token, &tokensize);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s clear key import 4/4 with CSNBKPI2 failed, rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	/* copy the generated key token */
	अगर (keybuf) अणु
		अगर (tokensize > *keybufsize)
			rc = -EINVAL;
		अन्यथा
			स_नकल(keybuf, token, tokensize);
	पूर्ण
	*keybufsize = tokensize;

out:
	kमुक्त(token);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_clr2cipherkey);

/*
 * Derive proteced key from CCA AES cipher secure key.
 */
पूर्णांक cca_cipher2protkey(u16 cardnr, u16 करोमुख्य, स्थिर u8 *ckey,
		       u8 *protkey, u32 *protkeylen, u32 *protkeytype)
अणु
	पूर्णांक rc;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा aureqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		u8  rule_array[8];
		काष्ठा अणु
			u16 len;
			u16 tk_blob_len;
			u16 tk_blob_tag;
			u8  tk_blob[66];
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
			u16 cca_key_token_len;
			u16 cca_key_token_flags;
			u8  cca_key_token[0]; // 64 or more
		पूर्ण kb;
	पूर्ण __packed * preqparm;
	काष्ठा aurepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा अणु
			u16 len;
			u16 sublen;
			u16 tag;
			काष्ठा cpacfkeyblock अणु
				u8  version;  /* version of this काष्ठा */
				u8  flags[2];
				u8  algo;
				u8  क्रमm;
				u8  pad1[3];
				u16 keylen;
				u8  key[64];  /* the key (keylen bytes) */
				u16 keyattrlen;
				u8  keyattr[32];
				u8  pad2[1];
				u8  vptype;
				u8  vp[32];  /* verअगरication pattern */
			पूर्ण ckb;
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
		पूर्ण kb;
	पूर्ण __packed * prepparm;
	पूर्णांक keytoklen = ((काष्ठा cipherkeytoken *)ckey)->len;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with AU request */
	preqparm = (काष्ठा aureqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "AU", 2);
	preqparm->rule_array_len =
		माप(preqparm->rule_array_len)
		+ माप(preqparm->rule_array);
	स_नकल(preqparm->rule_array, "EXPT-SK ", 8);
	/* vud, tk blob */
	preqparm->vud.len = माप(preqparm->vud);
	preqparm->vud.tk_blob_len = माप(preqparm->vud.tk_blob)
		+ 2 * माप(uपूर्णांक16_t);
	preqparm->vud.tk_blob_tag = 0x00C2;
	/* kb, cca token */
	preqparm->kb.len = keytoklen + 3 * माप(uपूर्णांक16_t);
	preqparm->kb.cca_key_token_len = keytoklen + 2 * माप(uपूर्णांक16_t);
	स_नकल(preqparm->kb.cca_key_token, ckey, keytoklen);
	/* now fill length of param block पूर्णांकo cprb */
	preqcblk->req_parml = माप(काष्ठा aureqparm) + keytoklen;

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR(
			"%s unwrap secure key failure, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
		अगर (prepcblk->ccp_rtcode == 8 && prepcblk->ccp_rscode == 2290)
			rc = -EAGAIN;
		अन्यथा
			rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (prepcblk->ccp_rscode != 0) अणु
		DEBUG_WARN(
			"%s unwrap secure key warning, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा aurepparm *) ptr;

	/* check the वापसed keyblock */
	अगर (prepparm->vud.ckb.version != 0x01 &&
	    prepparm->vud.ckb.version != 0x02) अणु
		DEBUG_ERR("%s reply param keyblock version mismatch 0x%02x\n",
			  __func__, (पूर्णांक) prepparm->vud.ckb.version);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (prepparm->vud.ckb.algo != 0x02) अणु
		DEBUG_ERR(
			"%s reply param keyblock algo mismatch 0x%02x != 0x02\n",
			__func__, (पूर्णांक) prepparm->vud.ckb.algo);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the translated रक्षित key */
	चयन (prepparm->vud.ckb.keylen) अणु
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
		DEBUG_ERR("%s unknown/unsupported keylen %d\n",
			  __func__, prepparm->vud.ckb.keylen);
		rc = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(protkey, prepparm->vud.ckb.key, prepparm->vud.ckb.keylen);
	अगर (protkeylen)
		*protkeylen = prepparm->vud.ckb.keylen;

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_cipher2protkey);

/*
 * Derive रक्षित key from CCA ECC secure निजी key.
 */
पूर्णांक cca_ecc2protkey(u16 cardnr, u16 करोमुख्य, स्थिर u8 *key,
		    u8 *protkey, u32 *protkeylen, u32 *protkeytype)
अणु
	पूर्णांक rc;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा aureqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		u8  rule_array[8];
		काष्ठा अणु
			u16 len;
			u16 tk_blob_len;
			u16 tk_blob_tag;
			u8  tk_blob[66];
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
			u16 cca_key_token_len;
			u16 cca_key_token_flags;
			u8  cca_key_token[0];
		पूर्ण kb;
	पूर्ण __packed * preqparm;
	काष्ठा aurepparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		काष्ठा अणु
			u16 len;
			u16 sublen;
			u16 tag;
			काष्ठा cpacfkeyblock अणु
				u8  version;  /* version of this काष्ठा */
				u8  flags[2];
				u8  algo;
				u8  क्रमm;
				u8  pad1[3];
				u16 keylen;
				u8  key[0];  /* the key (keylen bytes) */
				u16 keyattrlen;
				u8  keyattr[32];
				u8  pad2[1];
				u8  vptype;
				u8  vp[32];  /* verअगरication pattern */
			पूर्ण ckb;
		पूर्ण vud;
		काष्ठा अणु
			u16 len;
		पूर्ण kb;
	पूर्ण __packed * prepparm;
	पूर्णांक keylen = ((काष्ठा eccprivkeytoken *)key)->len;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(PARMBSIZE, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with AU request */
	preqparm = (काष्ठा aureqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "AU", 2);
	preqparm->rule_array_len =
		माप(preqparm->rule_array_len)
		+ माप(preqparm->rule_array);
	स_नकल(preqparm->rule_array, "EXPT-SK ", 8);
	/* vud, tk blob */
	preqparm->vud.len = माप(preqparm->vud);
	preqparm->vud.tk_blob_len = माप(preqparm->vud.tk_blob)
		+ 2 * माप(uपूर्णांक16_t);
	preqparm->vud.tk_blob_tag = 0x00C2;
	/* kb, cca token */
	preqparm->kb.len = keylen + 3 * माप(uपूर्णांक16_t);
	preqparm->kb.cca_key_token_len = keylen + 2 * माप(uपूर्णांक16_t);
	स_नकल(preqparm->kb.cca_key_token, key, keylen);
	/* now fill length of param block पूर्णांकo cprb */
	preqcblk->req_parml = माप(काष्ठा aureqparm) + keylen;

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR(
			"%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			__func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR(
			"%s unwrap secure key failure, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
		अगर (prepcblk->ccp_rtcode == 8 && prepcblk->ccp_rscode == 2290)
			rc = -EAGAIN;
		अन्यथा
			rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (prepcblk->ccp_rscode != 0) अणु
		DEBUG_WARN(
			"%s unwrap secure key warning, card response %d/%d\n",
			__func__,
			(पूर्णांक) prepcblk->ccp_rtcode,
			(पूर्णांक) prepcblk->ccp_rscode);
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा aurepparm *) ptr;

	/* check the वापसed keyblock */
	अगर (prepparm->vud.ckb.version != 0x02) अणु
		DEBUG_ERR("%s reply param keyblock version mismatch 0x%02x != 0x02\n",
			  __func__, (पूर्णांक) prepparm->vud.ckb.version);
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (prepparm->vud.ckb.algo != 0x81) अणु
		DEBUG_ERR(
			"%s reply param keyblock algo mismatch 0x%02x != 0x81\n",
			__func__, (पूर्णांक) prepparm->vud.ckb.algo);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy the translated रक्षित key */
	अगर (prepparm->vud.ckb.keylen > *protkeylen) अणु
		DEBUG_ERR("%s prot keylen mismatch %d > buffersize %u\n",
			  __func__, prepparm->vud.ckb.keylen, *protkeylen);
		rc = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(protkey, prepparm->vud.ckb.key, prepparm->vud.ckb.keylen);
	*protkeylen = prepparm->vud.ckb.keylen;
	अगर (protkeytype)
		*protkeytype = PKEY_KEYTYPE_ECC;

out:
	मुक्त_cprbmem(mem, PARMBSIZE, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_ecc2protkey);

/*
 * query cryptographic facility from CCA adapter
 */
पूर्णांक cca_query_crypto_facility(u16 cardnr, u16 करोमुख्य,
			      स्थिर अक्षर *keyword,
			      u8 *rarray, माप_प्रकार *rarraylen,
			      u8 *varray, माप_प्रकार *varraylen)
अणु
	पूर्णांक rc;
	u16 len;
	u8 *mem, *ptr;
	काष्ठा CPRBX *preqcblk, *prepcblk;
	काष्ठा ica_xcRB xcrb;
	काष्ठा fqreqparm अणु
		u8  subfunc_code[2];
		u16 rule_array_len;
		अक्षर  rule_array[8];
		काष्ठा lv1 अणु
			u16 len;
			u8  data[VARDATASIZE];
		पूर्ण lv1;
		u16 dummylen;
	पूर्ण __packed * preqparm;
	माप_प्रकार parmbsize = माप(काष्ठा fqreqparm);
	काष्ठा fqrepparm अणु
		u8  subfunc_code[2];
		u8  lvdata[0];
	पूर्ण __packed * prepparm;

	/* get alपढ़ोy prepared memory क्रम 2 cprbs with param block each */
	rc = alloc_and_prep_cprbmem(parmbsize, &mem, &preqcblk, &prepcblk);
	अगर (rc)
		वापस rc;

	/* fill request cprb काष्ठा */
	preqcblk->करोमुख्य = करोमुख्य;

	/* fill request cprb param block with FQ request */
	preqparm = (काष्ठा fqreqparm __क्रमce *) preqcblk->req_parmb;
	स_नकल(preqparm->subfunc_code, "FQ", 2);
	स_नकल(preqparm->rule_array, keyword, माप(preqparm->rule_array));
	preqparm->rule_array_len =
		माप(preqparm->rule_array_len) + माप(preqparm->rule_array);
	preqparm->lv1.len = माप(preqparm->lv1);
	preqparm->dummylen = माप(preqparm->dummylen);
	preqcblk->req_parml = parmbsize;

	/* fill xcrb काष्ठा */
	prep_xcrb(&xcrb, cardnr, preqcblk, prepcblk);

	/* क्रमward xcrb with request CPRB and reply CPRB to zcrypt dd */
	rc = zcrypt_send_cprb(&xcrb);
	अगर (rc) अणु
		DEBUG_ERR("%s zcrypt_send_cprb (cardnr=%d domain=%d) failed, rc=%d\n",
			  __func__, (पूर्णांक) cardnr, (पूर्णांक) करोमुख्य, rc);
		जाओ out;
	पूर्ण

	/* check response वापसcode and reasoncode */
	अगर (prepcblk->ccp_rtcode != 0) अणु
		DEBUG_ERR("%s unwrap secure key failure, card response %d/%d\n",
			  __func__,
			  (पूर्णांक) prepcblk->ccp_rtcode,
			  (पूर्णांक) prepcblk->ccp_rscode);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* process response cprb param block */
	ptr = ((u8 *) prepcblk) + माप(काष्ठा CPRBX);
	prepcblk->rpl_parmb = (u8 __user *) ptr;
	prepparm = (काष्ठा fqrepparm *) ptr;
	ptr = prepparm->lvdata;

	/* check and possibly copy reply rule array */
	len = *((u16 *) ptr);
	अगर (len > माप(u16)) अणु
		ptr += माप(u16);
		len -= माप(u16);
		अगर (rarray && rarraylen && *rarraylen > 0) अणु
			*rarraylen = (len > *rarraylen ? *rarraylen : len);
			स_नकल(rarray, ptr, *rarraylen);
		पूर्ण
		ptr += len;
	पूर्ण
	/* check and possible copy reply var array */
	len = *((u16 *) ptr);
	अगर (len > माप(u16)) अणु
		ptr += माप(u16);
		len -= माप(u16);
		अगर (varray && varraylen && *varraylen > 0) अणु
			*varraylen = (len > *varraylen ? *varraylen : len);
			स_नकल(varray, ptr, *varraylen);
		पूर्ण
		ptr += len;
	पूर्ण

out:
	मुक्त_cprbmem(mem, parmbsize, 0);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_query_crypto_facility);

अटल पूर्णांक cca_info_cache_fetch(u16 cardnr, u16 करोमुख्य, काष्ठा cca_info *ci)
अणु
	पूर्णांक rc = -ENOENT;
	काष्ठा cca_info_list_entry *ptr;

	spin_lock_bh(&cca_info_list_lock);
	list_क्रम_each_entry(ptr, &cca_info_list, list) अणु
		अगर (ptr->cardnr == cardnr && ptr->करोमुख्य == करोमुख्य) अणु
			स_नकल(ci, &ptr->info, माप(*ci));
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cca_info_list_lock);

	वापस rc;
पूर्ण

अटल व्योम cca_info_cache_update(u16 cardnr, u16 करोमुख्य,
				  स्थिर काष्ठा cca_info *ci)
अणु
	पूर्णांक found = 0;
	काष्ठा cca_info_list_entry *ptr;

	spin_lock_bh(&cca_info_list_lock);
	list_क्रम_each_entry(ptr, &cca_info_list, list) अणु
		अगर (ptr->cardnr == cardnr &&
		    ptr->करोमुख्य == करोमुख्य) अणु
			स_नकल(&ptr->info, ci, माप(*ci));
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		ptr = kदो_स्मृति(माप(*ptr), GFP_ATOMIC);
		अगर (!ptr) अणु
			spin_unlock_bh(&cca_info_list_lock);
			वापस;
		पूर्ण
		ptr->cardnr = cardnr;
		ptr->करोमुख्य = करोमुख्य;
		स_नकल(&ptr->info, ci, माप(*ci));
		list_add(&ptr->list, &cca_info_list);
	पूर्ण
	spin_unlock_bh(&cca_info_list_lock);
पूर्ण

अटल व्योम cca_info_cache_scrub(u16 cardnr, u16 करोमुख्य)
अणु
	काष्ठा cca_info_list_entry *ptr;

	spin_lock_bh(&cca_info_list_lock);
	list_क्रम_each_entry(ptr, &cca_info_list, list) अणु
		अगर (ptr->cardnr == cardnr &&
		    ptr->करोमुख्य == करोमुख्य) अणु
			list_del(&ptr->list);
			kमुक्त(ptr);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cca_info_list_lock);
पूर्ण

अटल व्योम __निकास mkvp_cache_मुक्त(व्योम)
अणु
	काष्ठा cca_info_list_entry *ptr, *pnext;

	spin_lock_bh(&cca_info_list_lock);
	list_क्रम_each_entry_safe(ptr, pnext, &cca_info_list, list) अणु
		list_del(&ptr->list);
		kमुक्त(ptr);
	पूर्ण
	spin_unlock_bh(&cca_info_list_lock);
पूर्ण

/*
 * Fetch cca_info values via query_crypto_facility from adapter.
 */
अटल पूर्णांक fetch_cca_info(u16 cardnr, u16 करोमुख्य, काष्ठा cca_info *ci)
अणु
	पूर्णांक rc, found = 0;
	माप_प्रकार rlen, vlen;
	u8 *rarray, *varray, *pg;
	काष्ठा zcrypt_device_status_ext devstat;

	स_रखो(ci, 0, माप(*ci));

	/* get first info from zcrypt device driver about this apqn */
	rc = zcrypt_device_status_ext(cardnr, करोमुख्य, &devstat);
	अगर (rc)
		वापस rc;
	ci->hwtype = devस्थिति.सwtype;

	/* prep page क्रम rule array and var array use */
	pg = (u8 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pg)
		वापस -ENOMEM;
	rarray = pg;
	varray = pg + PAGE_SIZE/2;
	rlen = vlen = PAGE_SIZE/2;

	/* QF क्रम this card/करोमुख्य */
	rc = cca_query_crypto_facility(cardnr, करोमुख्य, "STATICSA",
				       rarray, &rlen, varray, &vlen);
	अगर (rc == 0 && rlen >= 10*8 && vlen >= 204) अणु
		स_नकल(ci->serial, rarray, 8);
		ci->new_aes_mk_state = (अक्षर) rarray[7*8];
		ci->cur_aes_mk_state = (अक्षर) rarray[8*8];
		ci->old_aes_mk_state = (अक्षर) rarray[9*8];
		अगर (ci->old_aes_mk_state == '2')
			स_नकल(&ci->old_aes_mkvp, varray + 172, 8);
		अगर (ci->cur_aes_mk_state == '2')
			स_नकल(&ci->cur_aes_mkvp, varray + 184, 8);
		अगर (ci->new_aes_mk_state == '3')
			स_नकल(&ci->new_aes_mkvp, varray + 196, 8);
		found++;
	पूर्ण
	अगर (!found)
		जाओ out;
	rlen = vlen = PAGE_SIZE/2;
	rc = cca_query_crypto_facility(cardnr, करोमुख्य, "STATICSB",
				       rarray, &rlen, varray, &vlen);
	अगर (rc == 0 && rlen >= 10*8 && vlen >= 240) अणु
		ci->new_apka_mk_state = (अक्षर) rarray[7*8];
		ci->cur_apka_mk_state = (अक्षर) rarray[8*8];
		ci->old_apka_mk_state = (अक्षर) rarray[9*8];
		अगर (ci->old_apka_mk_state == '2')
			स_नकल(&ci->old_apka_mkvp, varray + 208, 8);
		अगर (ci->cur_apka_mk_state == '2')
			स_नकल(&ci->cur_apka_mkvp, varray + 220, 8);
		अगर (ci->new_apka_mk_state == '3')
			स_नकल(&ci->new_apka_mkvp, varray + 232, 8);
		found++;
	पूर्ण

out:
	मुक्त_page((अचिन्हित दीर्घ) pg);
	वापस found == 2 ? 0 : -ENOENT;
पूर्ण

/*
 * Fetch cca inक्रमmation about a CCA queue.
 */
पूर्णांक cca_get_info(u16 card, u16 करोm, काष्ठा cca_info *ci, पूर्णांक verअगरy)
अणु
	पूर्णांक rc;

	rc = cca_info_cache_fetch(card, करोm, ci);
	अगर (rc || verअगरy) अणु
		rc = fetch_cca_info(card, करोm, ci);
		अगर (rc == 0)
			cca_info_cache_update(card, करोm, ci);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(cca_get_info);

/*
 * Search क्रम a matching crypto card based on the
 * Master Key Verअगरication Pattern given.
 */
अटल पूर्णांक findcard(u64 mkvp, u16 *pcardnr, u16 *pकरोमुख्य,
		    पूर्णांक verअगरy, पूर्णांक minhwtype)
अणु
	काष्ठा zcrypt_device_status_ext *device_status;
	u16 card, करोm;
	काष्ठा cca_info ci;
	पूर्णांक i, rc, oi = -1;

	/* mkvp must not be zero, minhwtype needs to be >= 0 */
	अगर (mkvp == 0 || minhwtype < 0)
		वापस -EINVAL;

	/* fetch status of all crypto cards */
	device_status = kvदो_स्मृति_array(MAX_ZDEV_ENTRIES_EXT,
				       माप(काष्ठा zcrypt_device_status_ext),
				       GFP_KERNEL);
	अगर (!device_status)
		वापस -ENOMEM;
	zcrypt_device_status_mask_ext(device_status);

	/* walk through all crypto cards */
	क्रम (i = 0; i < MAX_ZDEV_ENTRIES_EXT; i++) अणु
		card = AP_QID_CARD(device_status[i].qid);
		करोm = AP_QID_QUEUE(device_status[i].qid);
		अगर (device_status[i].online &&
		    device_status[i].functions & 0x04) अणु
			/* enabled CCA card, check current mkvp from cache */
			अगर (cca_info_cache_fetch(card, करोm, &ci) == 0 &&
			    ci.hwtype >= minhwtype &&
			    ci.cur_aes_mk_state == '2' &&
			    ci.cur_aes_mkvp == mkvp) अणु
				अगर (!verअगरy)
					अवरोध;
				/* verअगरy: refresh card info */
				अगर (fetch_cca_info(card, करोm, &ci) == 0) अणु
					cca_info_cache_update(card, करोm, &ci);
					अगर (ci.hwtype >= minhwtype &&
					    ci.cur_aes_mk_state == '2' &&
					    ci.cur_aes_mkvp == mkvp)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Card is offline and/or not a CCA card. */
			/* del mkvp entry from cache अगर it exists */
			cca_info_cache_scrub(card, करोm);
		पूर्ण
	पूर्ण
	अगर (i >= MAX_ZDEV_ENTRIES_EXT) अणु
		/* nothing found, so this समय without cache */
		क्रम (i = 0; i < MAX_ZDEV_ENTRIES_EXT; i++) अणु
			अगर (!(device_status[i].online &&
			      device_status[i].functions & 0x04))
				जारी;
			card = AP_QID_CARD(device_status[i].qid);
			करोm = AP_QID_QUEUE(device_status[i].qid);
			/* fresh fetch mkvp from adapter */
			अगर (fetch_cca_info(card, करोm, &ci) == 0) अणु
				cca_info_cache_update(card, करोm, &ci);
				अगर (ci.hwtype >= minhwtype &&
				    ci.cur_aes_mk_state == '2' &&
				    ci.cur_aes_mkvp == mkvp)
					अवरोध;
				अगर (ci.hwtype >= minhwtype &&
				    ci.old_aes_mk_state == '2' &&
				    ci.old_aes_mkvp == mkvp &&
				    oi < 0)
					oi = i;
			पूर्ण
		पूर्ण
		अगर (i >= MAX_ZDEV_ENTRIES_EXT && oi >= 0) अणु
			/* old mkvp matched, use this card then */
			card = AP_QID_CARD(device_status[oi].qid);
			करोm = AP_QID_QUEUE(device_status[oi].qid);
		पूर्ण
	पूर्ण
	अगर (i < MAX_ZDEV_ENTRIES_EXT || oi >= 0) अणु
		अगर (pcardnr)
			*pcardnr = card;
		अगर (pकरोमुख्य)
			*pकरोमुख्य = करोm;
		rc = (i < MAX_ZDEV_ENTRIES_EXT ? 0 : 1);
	पूर्ण अन्यथा
		rc = -ENODEV;

	kvमुक्त(device_status);
	वापस rc;
पूर्ण

/*
 * Search क्रम a matching crypto card based on the Master Key
 * Verअगरication Pattern provided inside a secure key token.
 */
पूर्णांक cca_findcard(स्थिर u8 *key, u16 *pcardnr, u16 *pकरोमुख्य, पूर्णांक verअगरy)
अणु
	u64 mkvp;
	पूर्णांक minhwtype = 0;
	स्थिर काष्ठा keytoken_header *hdr = (काष्ठा keytoken_header *) key;

	अगर (hdr->type != TOKTYPE_CCA_INTERNAL)
		वापस -EINVAL;

	चयन (hdr->version) अणु
	हाल TOKVER_CCA_AES:
		mkvp = ((काष्ठा secaeskeytoken *)key)->mkvp;
		अवरोध;
	हाल TOKVER_CCA_VLSC:
		mkvp = ((काष्ठा cipherkeytoken *)key)->mkvp0;
		minhwtype = AP_DEVICE_TYPE_CEX6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस findcard(mkvp, pcardnr, pकरोमुख्य, verअगरy, minhwtype);
पूर्ण
EXPORT_SYMBOL(cca_findcard);

पूर्णांक cca_findcard2(u32 **apqns, u32 *nr_apqns, u16 cardnr, u16 करोमुख्य,
		  पूर्णांक minhwtype, पूर्णांक mktype, u64 cur_mkvp, u64 old_mkvp,
		  पूर्णांक verअगरy)
अणु
	काष्ठा zcrypt_device_status_ext *device_status;
	u32 *_apqns = शून्य, _nr_apqns = 0;
	पूर्णांक i, card, करोm, curmatch, oldmatch, rc = 0;
	काष्ठा cca_info ci;

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
		/* check क्रम cca functions */
		अगर (!(device_status[i].functions & 0x04))
			जारी;
		/* check cardnr */
		अगर (cardnr != 0xFFFF && card != cardnr)
			जारी;
		/* check करोमुख्य */
		अगर (करोमुख्य != 0xFFFF && करोm != करोमुख्य)
			जारी;
		/* get cca info on this apqn */
		अगर (cca_get_info(card, करोm, &ci, verअगरy))
			जारी;
		/* current master key needs to be valid */
		अगर (mktype == AES_MK_SET && ci.cur_aes_mk_state != '2')
			जारी;
		अगर (mktype == APKA_MK_SET && ci.cur_apka_mk_state != '2')
			जारी;
		/* check min hardware type */
		अगर (minhwtype > 0 && minhwtype > ci.hwtype)
			जारी;
		अगर (cur_mkvp || old_mkvp) अणु
			/* check mkvps */
			curmatch = oldmatch = 0;
			अगर (mktype == AES_MK_SET) अणु
				अगर (cur_mkvp && cur_mkvp == ci.cur_aes_mkvp)
					curmatch = 1;
				अगर (old_mkvp && ci.old_aes_mk_state == '2' &&
				    old_mkvp == ci.old_aes_mkvp)
					oldmatch = 1;
			पूर्ण अन्यथा अणु
				अगर (cur_mkvp && cur_mkvp == ci.cur_apka_mkvp)
					curmatch = 1;
				अगर (old_mkvp && ci.old_apka_mk_state == '2' &&
				    old_mkvp == ci.old_apka_mkvp)
					oldmatch = 1;
			पूर्ण
			अगर (curmatch + oldmatch < 1)
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
EXPORT_SYMBOL(cca_findcard2);

व्योम __निकास zcrypt_ccamisc_निकास(व्योम)
अणु
	mkvp_cache_मुक्त();
पूर्ण
