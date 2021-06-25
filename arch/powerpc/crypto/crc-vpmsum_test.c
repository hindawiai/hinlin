<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CRC vpmsum tester
 * Copyright 2017 Daniel Axtens, IBM Corporation.
 */

#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/crc32.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/चयन_to.h>

अटल अचिन्हित दीर्घ iterations = 10000;

#घोषणा MAX_CRC_LENGTH 65535


अटल पूर्णांक __init crc_test_init(व्योम)
अणु
	u16 crc16 = 0, verअगरy16 = 0;
	__le32 verअगरy32le = 0;
	अचिन्हित अक्षर *data;
	u32 verअगरy32 = 0;
	अचिन्हित दीर्घ i;
	__le32 crc32;
	पूर्णांक ret;

	काष्ठा crypto_shash *crct10dअगर_tfm;
	काष्ठा crypto_shash *crc32c_tfm;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	data = kदो_स्मृति(MAX_CRC_LENGTH, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	crct10dअगर_tfm = crypto_alloc_shash("crct10dif", 0, 0);

	अगर (IS_ERR(crct10dअगर_tfm)) अणु
		pr_err("Error allocating crc-t10dif\n");
		जाओ मुक्त_buf;
	पूर्ण

	crc32c_tfm = crypto_alloc_shash("crc32c", 0, 0);

	अगर (IS_ERR(crc32c_tfm)) अणु
		pr_err("Error allocating crc32c\n");
		जाओ मुक्त_16;
	पूर्ण

	करो अणु
		SHASH_DESC_ON_STACK(crct10dअगर_shash, crct10dअगर_tfm);
		SHASH_DESC_ON_STACK(crc32c_shash, crc32c_tfm);

		crct10dअगर_shash->tfm = crct10dअगर_tfm;
		ret = crypto_shash_init(crct10dअगर_shash);

		अगर (ret) अणु
			pr_err("Error initing crc-t10dif\n");
			जाओ मुक्त_32;
		पूर्ण


		crc32c_shash->tfm = crc32c_tfm;
		ret = crypto_shash_init(crc32c_shash);

		अगर (ret) अणु
			pr_err("Error initing crc32c\n");
			जाओ मुक्त_32;
		पूर्ण

		pr_info("crc-vpmsum_test begins, %lu iterations\n", iterations);
		क्रम (i=0; i<iterations; i++) अणु
			माप_प्रकार offset = pअक्रमom_u32_max(16);
			माप_प्रकार len = pअक्रमom_u32_max(MAX_CRC_LENGTH);

			अगर (len <= offset)
				जारी;
			pअक्रमom_bytes(data, len);
			len -= offset;

			crypto_shash_update(crct10dअगर_shash, data+offset, len);
			crypto_shash_final(crct10dअगर_shash, (u8 *)(&crc16));
			verअगरy16 = crc_t10dअगर_generic(verअगरy16, data+offset, len);


			अगर (crc16 != verअगरy16) अणु
				pr_err("FAILURE in CRC16: got 0x%04x expected 0x%04x (len %lu)\n",
				       crc16, verअगरy16, len);
				अवरोध;
			पूर्ण

			crypto_shash_update(crc32c_shash, data+offset, len);
			crypto_shash_final(crc32c_shash, (u8 *)(&crc32));
			verअगरy32 = le32_to_cpu(verअगरy32le);
		        verअगरy32le = ~cpu_to_le32(__crc32c_le(~verअगरy32, data+offset, len));
			अगर (crc32 != verअगरy32le) अणु
				pr_err("FAILURE in CRC32: got 0x%08x expected 0x%08x (len %lu)\n",
				       crc32, verअगरy32, len);
				अवरोध;
			पूर्ण
		cond_resched();
		पूर्ण
		pr_info("crc-vpmsum_test done, completed %lu iterations\n", i);
	पूर्ण जबतक (0);

मुक्त_32:
	crypto_मुक्त_shash(crc32c_tfm);

मुक्त_16:
	crypto_मुक्त_shash(crct10dअगर_tfm);

मुक्त_buf:
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल व्योम __निकास crc_test_निकास(व्योम) अणुपूर्ण

module_init(crc_test_init);
module_निकास(crc_test_निकास);
module_param(iterations, दीर्घ, 0400);

MODULE_AUTHOR("Daniel Axtens <dja@axtens.net>");
MODULE_DESCRIPTION("Vector polynomial multiply-sum CRC tester");
MODULE_LICENSE("GPL");
