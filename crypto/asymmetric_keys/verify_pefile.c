<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Parse a चिन्हित PE binary
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "PEFILE: "fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/pe.h>
#समावेश <linux/asn1.h>
#समावेश <linux/verअगरication.h>
#समावेश <crypto/hash.h>
#समावेश "verify_pefile.h"

/*
 * Parse a PE binary.
 */
अटल पूर्णांक pefile_parse_binary(स्थिर व्योम *pebuf, अचिन्हित पूर्णांक pelen,
			       काष्ठा pefile_context *ctx)
अणु
	स्थिर काष्ठा mz_hdr *mz = pebuf;
	स्थिर काष्ठा pe_hdr *pe;
	स्थिर काष्ठा pe32_opt_hdr *pe32;
	स्थिर काष्ठा pe32plus_opt_hdr *pe64;
	स्थिर काष्ठा data_directory *ddir;
	स्थिर काष्ठा data_dirent *dde;
	स्थिर काष्ठा section_header *secs, *sec;
	माप_प्रकार cursor, datalen = pelen;

	kenter("");

#घोषणा chkaddr(base, x, s)						\
	करो अणु								\
		अगर ((x) < base || (s) >= datalen || (x) > datalen - (s)) \
			वापस -ELIBBAD;				\
	पूर्ण जबतक (0)

	chkaddr(0, 0, माप(*mz));
	अगर (mz->magic != MZ_MAGIC)
		वापस -ELIBBAD;
	cursor = माप(*mz);

	chkaddr(cursor, mz->peaddr, माप(*pe));
	pe = pebuf + mz->peaddr;
	अगर (pe->magic != PE_MAGIC)
		वापस -ELIBBAD;
	cursor = mz->peaddr + माप(*pe);

	chkaddr(0, cursor, माप(pe32->magic));
	pe32 = pebuf + cursor;
	pe64 = pebuf + cursor;

	चयन (pe32->magic) अणु
	हाल PE_OPT_MAGIC_PE32:
		chkaddr(0, cursor, माप(*pe32));
		ctx->image_checksum_offset =
			(अचिन्हित दीर्घ)&pe32->csum - (अचिन्हित दीर्घ)pebuf;
		ctx->header_size = pe32->header_size;
		cursor += माप(*pe32);
		ctx->n_data_dirents = pe32->data_dirs;
		अवरोध;

	हाल PE_OPT_MAGIC_PE32PLUS:
		chkaddr(0, cursor, माप(*pe64));
		ctx->image_checksum_offset =
			(अचिन्हित दीर्घ)&pe64->csum - (अचिन्हित दीर्घ)pebuf;
		ctx->header_size = pe64->header_size;
		cursor += माप(*pe64);
		ctx->n_data_dirents = pe64->data_dirs;
		अवरोध;

	शेष:
		pr_debug("Unknown PEOPT magic = %04hx\n", pe32->magic);
		वापस -ELIBBAD;
	पूर्ण

	pr_debug("checksum @ %x\n", ctx->image_checksum_offset);
	pr_debug("header size = %x\n", ctx->header_size);

	अगर (cursor >= ctx->header_size || ctx->header_size >= datalen)
		वापस -ELIBBAD;

	अगर (ctx->n_data_dirents > (ctx->header_size - cursor) / माप(*dde))
		वापस -ELIBBAD;

	ddir = pebuf + cursor;
	cursor += माप(*dde) * ctx->n_data_dirents;

	ctx->cert_dirent_offset =
		(अचिन्हित दीर्घ)&ddir->certs - (अचिन्हित दीर्घ)pebuf;
	ctx->certs_size = ddir->certs.size;

	अगर (!ddir->certs.भव_address || !ddir->certs.size) अणु
		pr_debug("Unsigned PE binary\n");
		वापस -ENODATA;
	पूर्ण

	chkaddr(ctx->header_size, ddir->certs.भव_address,
		ddir->certs.size);
	ctx->sig_offset = ddir->certs.भव_address;
	ctx->sig_len = ddir->certs.size;
	pr_debug("cert = %x @%x [%*ph]\n",
		 ctx->sig_len, ctx->sig_offset,
		 ctx->sig_len, pebuf + ctx->sig_offset);

	ctx->n_sections = pe->sections;
	अगर (ctx->n_sections > (ctx->header_size - cursor) / माप(*sec))
		वापस -ELIBBAD;
	ctx->secs = secs = pebuf + cursor;

	वापस 0;
पूर्ण

/*
 * Check and strip the PE wrapper from around the signature and check that the
 * remnant looks something like PKCS#7.
 */
अटल पूर्णांक pefile_strip_sig_wrapper(स्थिर व्योम *pebuf,
				    काष्ठा pefile_context *ctx)
अणु
	काष्ठा win_certअगरicate wrapper;
	स्थिर u8 *pkcs7;
	अचिन्हित len;

	अगर (ctx->sig_len < माप(wrapper)) अणु
		pr_debug("Signature wrapper too short\n");
		वापस -ELIBBAD;
	पूर्ण

	स_नकल(&wrapper, pebuf + ctx->sig_offset, माप(wrapper));
	pr_debug("sig wrapper = { %x, %x, %x }\n",
		 wrapper.length, wrapper.revision, wrapper.cert_type);

	/* Both pesign and sbsign round up the length of certअगरicate table
	 * (in optional header data directories) to 8 byte alignment.
	 */
	अगर (round_up(wrapper.length, 8) != ctx->sig_len) अणु
		pr_debug("Signature wrapper len wrong\n");
		वापस -ELIBBAD;
	पूर्ण
	अगर (wrapper.revision != WIN_CERT_REVISION_2_0) अणु
		pr_debug("Signature is not revision 2.0\n");
		वापस -ENOTSUPP;
	पूर्ण
	अगर (wrapper.cert_type != WIN_CERT_TYPE_PKCS_SIGNED_DATA) अणु
		pr_debug("Signature certificate type is not PKCS\n");
		वापस -ENOTSUPP;
	पूर्ण

	/* It looks like the pkcs signature length in wrapper->length and the
	 * size obtained from the data dir entries, which lists the total size
	 * of certअगरicate table, are both aligned to an octaword boundary, so
	 * we may have to deal with some padding.
	 */
	ctx->sig_len = wrapper.length;
	ctx->sig_offset += माप(wrapper);
	ctx->sig_len -= माप(wrapper);
	अगर (ctx->sig_len < 4) अणु
		pr_debug("Signature data missing\n");
		वापस -EKEYREJECTED;
	पूर्ण

	/* What's left should be a PKCS#7 cert */
	pkcs7 = pebuf + ctx->sig_offset;
	अगर (pkcs7[0] != (ASN1_CONS_BIT | ASN1_SEQ))
		जाओ not_pkcs7;

	चयन (pkcs7[1]) अणु
	हाल 0 ... 0x7f:
		len = pkcs7[1] + 2;
		जाओ check_len;
	हाल ASN1_INDEFINITE_LENGTH:
		वापस 0;
	हाल 0x81:
		len = pkcs7[2] + 3;
		जाओ check_len;
	हाल 0x82:
		len = ((pkcs7[2] << 8) | pkcs7[3]) + 4;
		जाओ check_len;
	हाल 0x83 ... 0xff:
		वापस -EMSGSIZE;
	शेष:
		जाओ not_pkcs7;
	पूर्ण

check_len:
	अगर (len <= ctx->sig_len) अणु
		/* There may be padding */
		ctx->sig_len = len;
		वापस 0;
	पूर्ण
not_pkcs7:
	pr_debug("Signature data not PKCS#7\n");
	वापस -ELIBBAD;
पूर्ण

/*
 * Compare two sections क्रम canonicalisation.
 */
अटल पूर्णांक pefile_compare_shdrs(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा section_header *shdra = a;
	स्थिर काष्ठा section_header *shdrb = b;
	पूर्णांक rc;

	अगर (shdra->data_addr > shdrb->data_addr)
		वापस 1;
	अगर (shdrb->data_addr > shdra->data_addr)
		वापस -1;

	अगर (shdra->भव_address > shdrb->भव_address)
		वापस 1;
	अगर (shdrb->भव_address > shdra->भव_address)
		वापस -1;

	rc = म_भेद(shdra->name, shdrb->name);
	अगर (rc != 0)
		वापस rc;

	अगर (shdra->भव_size > shdrb->भव_size)
		वापस 1;
	अगर (shdrb->भव_size > shdra->भव_size)
		वापस -1;

	अगर (shdra->raw_data_size > shdrb->raw_data_size)
		वापस 1;
	अगर (shdrb->raw_data_size > shdra->raw_data_size)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Load the contents of the PE binary पूर्णांकo the digest, leaving out the image
 * checksum and the certअगरicate data block.
 */
अटल पूर्णांक pefile_digest_pe_contents(स्थिर व्योम *pebuf, अचिन्हित पूर्णांक pelen,
				     काष्ठा pefile_context *ctx,
				     काष्ठा shash_desc *desc)
अणु
	अचिन्हित *canon, पंचांगp, loop, i, hashed_bytes;
	पूर्णांक ret;

	/* Digest the header and data directory, but leave out the image
	 * checksum and the data dirent क्रम the signature.
	 */
	ret = crypto_shash_update(desc, pebuf, ctx->image_checksum_offset);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = ctx->image_checksum_offset + माप(uपूर्णांक32_t);
	ret = crypto_shash_update(desc, pebuf + पंचांगp,
				  ctx->cert_dirent_offset - पंचांगp);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = ctx->cert_dirent_offset + माप(काष्ठा data_dirent);
	ret = crypto_shash_update(desc, pebuf + पंचांगp, ctx->header_size - पंचांगp);
	अगर (ret < 0)
		वापस ret;

	canon = kसुस्मृति(ctx->n_sections, माप(अचिन्हित), GFP_KERNEL);
	अगर (!canon)
		वापस -ENOMEM;

	/* We have to canonicalise the section table, so we perक्रमm an
	 * insertion sort.
	 */
	canon[0] = 0;
	क्रम (loop = 1; loop < ctx->n_sections; loop++) अणु
		क्रम (i = 0; i < loop; i++) अणु
			अगर (pefile_compare_shdrs(&ctx->secs[canon[i]],
						 &ctx->secs[loop]) > 0) अणु
				स_हटाओ(&canon[i + 1], &canon[i],
					(loop - i) * माप(canon[0]));
				अवरोध;
			पूर्ण
		पूर्ण
		canon[i] = loop;
	पूर्ण

	hashed_bytes = ctx->header_size;
	क्रम (loop = 0; loop < ctx->n_sections; loop++) अणु
		i = canon[loop];
		अगर (ctx->secs[i].raw_data_size == 0)
			जारी;
		ret = crypto_shash_update(desc,
					  pebuf + ctx->secs[i].data_addr,
					  ctx->secs[i].raw_data_size);
		अगर (ret < 0) अणु
			kमुक्त(canon);
			वापस ret;
		पूर्ण
		hashed_bytes += ctx->secs[i].raw_data_size;
	पूर्ण
	kमुक्त(canon);

	अगर (pelen > hashed_bytes) अणु
		पंचांगp = hashed_bytes + ctx->certs_size;
		ret = crypto_shash_update(desc,
					  pebuf + hashed_bytes,
					  pelen - पंचांगp);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Digest the contents of the PE binary, leaving out the image checksum and the
 * certअगरicate data block.
 */
अटल पूर्णांक pefile_digest_pe(स्थिर व्योम *pebuf, अचिन्हित पूर्णांक pelen,
			    काष्ठा pefile_context *ctx)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;
	माप_प्रकार digest_size, desc_size;
	व्योम *digest;
	पूर्णांक ret;

	kenter(",%s", ctx->digest_algo);

	/* Allocate the hashing algorithm we're going to need and find out how
	 * big the hash operational data will be.
	 */
	tfm = crypto_alloc_shash(ctx->digest_algo, 0, 0);
	अगर (IS_ERR(tfm))
		वापस (PTR_ERR(tfm) == -ENOENT) ? -ENOPKG : PTR_ERR(tfm);

	desc_size = crypto_shash_descsize(tfm) + माप(*desc);
	digest_size = crypto_shash_digestsize(tfm);

	अगर (digest_size != ctx->digest_len) अणु
		pr_debug("Digest size mismatch (%zx != %x)\n",
			 digest_size, ctx->digest_len);
		ret = -EBADMSG;
		जाओ error_no_desc;
	पूर्ण
	pr_debug("Digest: desc=%zu size=%zu\n", desc_size, digest_size);

	ret = -ENOMEM;
	desc = kzalloc(desc_size + digest_size, GFP_KERNEL);
	अगर (!desc)
		जाओ error_no_desc;

	desc->tfm   = tfm;
	ret = crypto_shash_init(desc);
	अगर (ret < 0)
		जाओ error;

	ret = pefile_digest_pe_contents(pebuf, pelen, ctx, desc);
	अगर (ret < 0)
		जाओ error;

	digest = (व्योम *)desc + desc_size;
	ret = crypto_shash_final(desc, digest);
	अगर (ret < 0)
		जाओ error;

	pr_debug("Digest calc = [%*ph]\n", ctx->digest_len, digest);

	/* Check that the PE file digest matches that in the MSCODE part of the
	 * PKCS#7 certअगरicate.
	 */
	अगर (स_भेद(digest, ctx->digest, ctx->digest_len) != 0) अणु
		pr_debug("Digest mismatch\n");
		ret = -EKEYREJECTED;
	पूर्ण अन्यथा अणु
		pr_debug("The digests match!\n");
	पूर्ण

error:
	kमुक्त_sensitive(desc);
error_no_desc:
	crypto_मुक्त_shash(tfm);
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/**
 * verअगरy_pefile_signature - Verअगरy the signature on a PE binary image
 * @pebuf: Buffer containing the PE binary image
 * @pelen: Length of the binary image
 * @trust_keys: Signing certअगरicate(s) to use as starting poपूर्णांकs
 * @usage: The use to which the key is being put.
 *
 * Validate that the certअगरicate chain inside the PKCS#7 message inside the PE
 * binary image पूर्णांकersects keys we alपढ़ोy know and trust.
 *
 * Returns, in order of descending priority:
 *
 *  (*) -ELIBBAD अगर the image cannot be parsed, or:
 *
 *  (*) -EKEYREJECTED अगर a signature failed to match क्रम which we have a valid
 *	key, or:
 *
 *  (*) 0 अगर at least one signature chain पूर्णांकersects with the keys in the trust
 *	keyring, or:
 *
 *  (*) -ENODATA अगर there is no signature present.
 *
 *  (*) -ENOPKG अगर a suitable crypto module couldn't be found क्रम a check on a
 *	chain.
 *
 *  (*) -ENOKEY अगर we couldn't find a match क्रम any of the signature chains in
 *	the message.
 *
 * May also वापस -ENOMEM.
 */
पूर्णांक verअगरy_pefile_signature(स्थिर व्योम *pebuf, अचिन्हित pelen,
			    काष्ठा key *trusted_keys,
			    क्रमागत key_being_used_क्रम usage)
अणु
	काष्ठा pefile_context ctx;
	पूर्णांक ret;

	kenter("");

	स_रखो(&ctx, 0, माप(ctx));
	ret = pefile_parse_binary(pebuf, pelen, &ctx);
	अगर (ret < 0)
		वापस ret;

	ret = pefile_strip_sig_wrapper(pebuf, &ctx);
	अगर (ret < 0)
		वापस ret;

	ret = verअगरy_pkcs7_signature(शून्य, 0,
				     pebuf + ctx.sig_offset, ctx.sig_len,
				     trusted_keys, usage,
				     mscode_parse, &ctx);
	अगर (ret < 0)
		जाओ error;

	pr_debug("Digest: %u [%*ph]\n",
		 ctx.digest_len, ctx.digest_len, ctx.digest);

	/* Generate the digest and check against the PKCS7 certअगरicate
	 * contents.
	 */
	ret = pefile_digest_pe(pebuf, pelen, &ctx);

error:
	kमुक्त_sensitive(ctx.digest);
	वापस ret;
पूर्ण
