<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Crypto user configuration API.
 *
 * Copyright (C) 2017-2018 Corentin Labbe <clabbe@baylibre.com>
 *
 */

#समावेश <linux/crypto.h>
#समावेश <linux/cryptouser.h>
#समावेश <linux/sched.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/पूर्णांकernal/cryptouser.h>

#समावेश "internal.h"

#घोषणा null_terminated(x)	(strnlen(x, माप(x)) < माप(x))

काष्ठा crypto_dump_info अणु
	काष्ठा sk_buff *in_skb;
	काष्ठा sk_buff *out_skb;
	u32 nlmsg_seq;
	u16 nlmsg_flags;
पूर्ण;

अटल पूर्णांक crypto_report_aead(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_aead raead;

	स_रखो(&raead, 0, माप(raead));

	strscpy(raead.type, "aead", माप(raead.type));

	raead.stat_encrypt_cnt = atomic64_पढ़ो(&alg->stats.aead.encrypt_cnt);
	raead.stat_encrypt_tlen = atomic64_पढ़ो(&alg->stats.aead.encrypt_tlen);
	raead.stat_decrypt_cnt = atomic64_पढ़ो(&alg->stats.aead.decrypt_cnt);
	raead.stat_decrypt_tlen = atomic64_पढ़ो(&alg->stats.aead.decrypt_tlen);
	raead.stat_err_cnt = atomic64_पढ़ो(&alg->stats.aead.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_AEAD, माप(raead), &raead);
पूर्ण

अटल पूर्णांक crypto_report_cipher(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_cipher rcipher;

	स_रखो(&rcipher, 0, माप(rcipher));

	strscpy(rcipher.type, "cipher", माप(rcipher.type));

	rcipher.stat_encrypt_cnt = atomic64_पढ़ो(&alg->stats.cipher.encrypt_cnt);
	rcipher.stat_encrypt_tlen = atomic64_पढ़ो(&alg->stats.cipher.encrypt_tlen);
	rcipher.stat_decrypt_cnt =  atomic64_पढ़ो(&alg->stats.cipher.decrypt_cnt);
	rcipher.stat_decrypt_tlen = atomic64_पढ़ो(&alg->stats.cipher.decrypt_tlen);
	rcipher.stat_err_cnt =  atomic64_पढ़ो(&alg->stats.cipher.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_CIPHER, माप(rcipher), &rcipher);
पूर्ण

अटल पूर्णांक crypto_report_comp(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_compress rcomp;

	स_रखो(&rcomp, 0, माप(rcomp));

	strscpy(rcomp.type, "compression", माप(rcomp.type));
	rcomp.stat_compress_cnt = atomic64_पढ़ो(&alg->stats.compress.compress_cnt);
	rcomp.stat_compress_tlen = atomic64_पढ़ो(&alg->stats.compress.compress_tlen);
	rcomp.stat_decompress_cnt = atomic64_पढ़ो(&alg->stats.compress.decompress_cnt);
	rcomp.stat_decompress_tlen = atomic64_पढ़ो(&alg->stats.compress.decompress_tlen);
	rcomp.stat_err_cnt = atomic64_पढ़ो(&alg->stats.compress.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_COMPRESS, माप(rcomp), &rcomp);
पूर्ण

अटल पूर्णांक crypto_report_acomp(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_compress racomp;

	स_रखो(&racomp, 0, माप(racomp));

	strscpy(racomp.type, "acomp", माप(racomp.type));
	racomp.stat_compress_cnt = atomic64_पढ़ो(&alg->stats.compress.compress_cnt);
	racomp.stat_compress_tlen = atomic64_पढ़ो(&alg->stats.compress.compress_tlen);
	racomp.stat_decompress_cnt =  atomic64_पढ़ो(&alg->stats.compress.decompress_cnt);
	racomp.stat_decompress_tlen = atomic64_पढ़ो(&alg->stats.compress.decompress_tlen);
	racomp.stat_err_cnt = atomic64_पढ़ो(&alg->stats.compress.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_ACOMP, माप(racomp), &racomp);
पूर्ण

अटल पूर्णांक crypto_report_akcipher(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_akcipher rakcipher;

	स_रखो(&rakcipher, 0, माप(rakcipher));

	strscpy(rakcipher.type, "akcipher", माप(rakcipher.type));
	rakcipher.stat_encrypt_cnt = atomic64_पढ़ो(&alg->stats.akcipher.encrypt_cnt);
	rakcipher.stat_encrypt_tlen = atomic64_पढ़ो(&alg->stats.akcipher.encrypt_tlen);
	rakcipher.stat_decrypt_cnt = atomic64_पढ़ो(&alg->stats.akcipher.decrypt_cnt);
	rakcipher.stat_decrypt_tlen = atomic64_पढ़ो(&alg->stats.akcipher.decrypt_tlen);
	rakcipher.stat_sign_cnt = atomic64_पढ़ो(&alg->stats.akcipher.sign_cnt);
	rakcipher.stat_verअगरy_cnt = atomic64_पढ़ो(&alg->stats.akcipher.verअगरy_cnt);
	rakcipher.stat_err_cnt = atomic64_पढ़ो(&alg->stats.akcipher.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_AKCIPHER,
		       माप(rakcipher), &rakcipher);
पूर्ण

अटल पूर्णांक crypto_report_kpp(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_kpp rkpp;

	स_रखो(&rkpp, 0, माप(rkpp));

	strscpy(rkpp.type, "kpp", माप(rkpp.type));

	rkpp.stat_setsecret_cnt = atomic64_पढ़ो(&alg->stats.kpp.setsecret_cnt);
	rkpp.stat_generate_खुला_key_cnt = atomic64_पढ़ो(&alg->stats.kpp.generate_खुला_key_cnt);
	rkpp.stat_compute_shared_secret_cnt = atomic64_पढ़ो(&alg->stats.kpp.compute_shared_secret_cnt);
	rkpp.stat_err_cnt = atomic64_पढ़ो(&alg->stats.kpp.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_KPP, माप(rkpp), &rkpp);
पूर्ण

अटल पूर्णांक crypto_report_ahash(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_hash rhash;

	स_रखो(&rhash, 0, माप(rhash));

	strscpy(rhash.type, "ahash", माप(rhash.type));

	rhash.stat_hash_cnt = atomic64_पढ़ो(&alg->stats.hash.hash_cnt);
	rhash.stat_hash_tlen = atomic64_पढ़ो(&alg->stats.hash.hash_tlen);
	rhash.stat_err_cnt = atomic64_पढ़ो(&alg->stats.hash.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_HASH, माप(rhash), &rhash);
पूर्ण

अटल पूर्णांक crypto_report_shash(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_hash rhash;

	स_रखो(&rhash, 0, माप(rhash));

	strscpy(rhash.type, "shash", माप(rhash.type));

	rhash.stat_hash_cnt =  atomic64_पढ़ो(&alg->stats.hash.hash_cnt);
	rhash.stat_hash_tlen = atomic64_पढ़ो(&alg->stats.hash.hash_tlen);
	rhash.stat_err_cnt = atomic64_पढ़ो(&alg->stats.hash.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_HASH, माप(rhash), &rhash);
पूर्ण

अटल पूर्णांक crypto_report_rng(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_stat_rng rrng;

	स_रखो(&rrng, 0, माप(rrng));

	strscpy(rrng.type, "rng", माप(rrng.type));

	rrng.stat_generate_cnt = atomic64_पढ़ो(&alg->stats.rng.generate_cnt);
	rrng.stat_generate_tlen = atomic64_पढ़ो(&alg->stats.rng.generate_tlen);
	rrng.stat_seed_cnt = atomic64_पढ़ो(&alg->stats.rng.seed_cnt);
	rrng.stat_err_cnt = atomic64_पढ़ो(&alg->stats.rng.err_cnt);

	वापस nla_put(skb, CRYPTOCFGA_STAT_RNG, माप(rrng), &rrng);
पूर्ण

अटल पूर्णांक crypto_reportstat_one(काष्ठा crypto_alg *alg,
				 काष्ठा crypto_user_alg *ualg,
				 काष्ठा sk_buff *skb)
अणु
	स_रखो(ualg, 0, माप(*ualg));

	strscpy(ualg->cru_name, alg->cra_name, माप(ualg->cru_name));
	strscpy(ualg->cru_driver_name, alg->cra_driver_name,
		माप(ualg->cru_driver_name));
	strscpy(ualg->cru_module_name, module_name(alg->cra_module),
		माप(ualg->cru_module_name));

	ualg->cru_type = 0;
	ualg->cru_mask = 0;
	ualg->cru_flags = alg->cra_flags;
	ualg->cru_refcnt = refcount_पढ़ो(&alg->cra_refcnt);

	अगर (nla_put_u32(skb, CRYPTOCFGA_PRIORITY_VAL, alg->cra_priority))
		जाओ nla_put_failure;
	अगर (alg->cra_flags & CRYPTO_ALG_LARVAL) अणु
		काष्ठा crypto_stat_larval rl;

		स_रखो(&rl, 0, माप(rl));
		strscpy(rl.type, "larval", माप(rl.type));
		अगर (nla_put(skb, CRYPTOCFGA_STAT_LARVAL, माप(rl), &rl))
			जाओ nla_put_failure;
		जाओ out;
	पूर्ण

	चयन (alg->cra_flags & (CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_LARVAL)) अणु
	हाल CRYPTO_ALG_TYPE_AEAD:
		अगर (crypto_report_aead(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		अगर (crypto_report_cipher(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_CIPHER:
		अगर (crypto_report_cipher(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_COMPRESS:
		अगर (crypto_report_comp(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_ACOMPRESS:
		अगर (crypto_report_acomp(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_SCOMPRESS:
		अगर (crypto_report_acomp(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AKCIPHER:
		अगर (crypto_report_akcipher(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_KPP:
		अगर (crypto_report_kpp(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AHASH:
		अगर (crypto_report_ahash(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_HASH:
		अगर (crypto_report_shash(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	हाल CRYPTO_ALG_TYPE_RNG:
		अगर (crypto_report_rng(skb, alg))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		pr_err("ERROR: Unhandled alg %d in %s\n",
		       alg->cra_flags & (CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_LARVAL),
		       __func__);
	पूर्ण

out:
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक crypto_reportstat_alg(काष्ठा crypto_alg *alg,
				 काष्ठा crypto_dump_info *info)
अणु
	काष्ठा sk_buff *in_skb = info->in_skb;
	काष्ठा sk_buff *skb = info->out_skb;
	काष्ठा nlmsghdr *nlh;
	काष्ठा crypto_user_alg *ualg;
	पूर्णांक err = 0;

	nlh = nlmsg_put(skb, NETLINK_CB(in_skb).portid, info->nlmsg_seq,
			CRYPTO_MSG_GETSTAT, माप(*ualg), info->nlmsg_flags);
	अगर (!nlh) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	ualg = nlmsg_data(nlh);

	err = crypto_reportstat_one(alg, ualg, skb);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		जाओ out;
	पूर्ण

	nlmsg_end(skb, nlh);

out:
	वापस err;
पूर्ण

पूर्णांक crypto_reportstat(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *in_nlh,
		      काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा crypto_user_alg *p = nlmsg_data(in_nlh);
	काष्ठा crypto_alg *alg;
	काष्ठा sk_buff *skb;
	काष्ठा crypto_dump_info info;
	पूर्णांक err;

	अगर (!null_terminated(p->cru_name) || !null_terminated(p->cru_driver_name))
		वापस -EINVAL;

	alg = crypto_alg_match(p, 0);
	अगर (!alg)
		वापस -ENOENT;

	err = -ENOMEM;
	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		जाओ drop_alg;

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nlmsg_seq = in_nlh->nlmsg_seq;
	info.nlmsg_flags = 0;

	err = crypto_reportstat_alg(alg, &info);

drop_alg:
	crypto_mod_put(alg);

	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	वापस nlmsg_unicast(net->crypto_nlsk, skb, NETLINK_CB(in_skb).portid);
पूर्ण

MODULE_LICENSE("GPL");
