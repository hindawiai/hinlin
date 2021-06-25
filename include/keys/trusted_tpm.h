<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TRUSTED_TPM_H
#घोषणा __TRUSTED_TPM_H

#समावेश <keys/trusted-type.h>
#समावेश <linux/tpm_command.h>

/* implementation specअगरic TPM स्थिरants */
#घोषणा MAX_BUF_SIZE			1024
#घोषणा TPM_GETRANDOM_SIZE		14
#घोषणा TPM_SIZE_OFFSET			2
#घोषणा TPM_RETURN_OFFSET		6
#घोषणा TPM_DATA_OFFSET			10

#घोषणा LOAD32(buffer, offset)	(ntohl(*(uपूर्णांक32_t *)&buffer[offset]))
#घोषणा LOAD32N(buffer, offset)	(*(uपूर्णांक32_t *)&buffer[offset])
#घोषणा LOAD16(buffer, offset)	(ntohs(*(uपूर्णांक16_t *)&buffer[offset]))

बाह्य काष्ठा trusted_key_ops trusted_key_tpm_ops;

काष्ठा osapsess अणु
	uपूर्णांक32_t handle;
	अचिन्हित अक्षर secret[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर enonce[TPM_NONCE_SIZE];
पूर्ण;

/* discrete values, but have to store in uपूर्णांक16_t क्रम TPM use */
क्रमागत अणु
	SEAL_keytype = 1,
	SRK_keytype = 4
पूर्ण;

पूर्णांक TSS_authhmac(अचिन्हित अक्षर *digest, स्थिर अचिन्हित अक्षर *key,
			अचिन्हित पूर्णांक keylen, अचिन्हित अक्षर *h1,
			अचिन्हित अक्षर *h2, अचिन्हित पूर्णांक h3, ...);
पूर्णांक TSS_checkhmac1(अचिन्हित अक्षर *buffer,
			  स्थिर uपूर्णांक32_t command,
			  स्थिर अचिन्हित अक्षर *ononce,
			  स्थिर अचिन्हित अक्षर *key,
			  अचिन्हित पूर्णांक keylen, ...);

पूर्णांक trusted_tpm_send(अचिन्हित अक्षर *cmd, माप_प्रकार buflen);
पूर्णांक oiap(काष्ठा tpm_buf *tb, uपूर्णांक32_t *handle, अचिन्हित अक्षर *nonce);

पूर्णांक tpm2_seal_trusted(काष्ठा tpm_chip *chip,
		      काष्ठा trusted_key_payload *payload,
		      काष्ठा trusted_key_options *options);
पूर्णांक tpm2_unseal_trusted(काष्ठा tpm_chip *chip,
			काष्ठा trusted_key_payload *payload,
			काष्ठा trusted_key_options *options);

#घोषणा TPM_DEBUG 0

#अगर TPM_DEBUG
अटल अंतरभूत व्योम dump_options(काष्ठा trusted_key_options *o)
अणु
	pr_info("sealing key type %d\n", o->keytype);
	pr_info("sealing key handle %0X\n", o->keyhandle);
	pr_info("pcrlock %d\n", o->pcrlock);
	pr_info("pcrinfo %d\n", o->pcrinfo_len);
	prपूर्णांक_hex_dump(KERN_INFO, "pcrinfo ", DUMP_PREFIX_NONE,
		       16, 1, o->pcrinfo, o->pcrinfo_len, 0);
पूर्ण

अटल अंतरभूत व्योम dump_sess(काष्ठा osapsess *s)
अणु
	prपूर्णांक_hex_dump(KERN_INFO, "trusted-key: handle ", DUMP_PREFIX_NONE,
		       16, 1, &s->handle, 4, 0);
	pr_info("secret:\n");
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE,
		       16, 1, &s->secret, SHA1_DIGEST_SIZE, 0);
	pr_info("trusted-key: enonce:\n");
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE,
		       16, 1, &s->enonce, SHA1_DIGEST_SIZE, 0);
पूर्ण

अटल अंतरभूत व्योम dump_tpm_buf(अचिन्हित अक्षर *buf)
अणु
	पूर्णांक len;

	pr_info("\ntpm buffer\n");
	len = LOAD32(buf, TPM_SIZE_OFFSET);
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1, buf, len, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_options(काष्ठा trusted_key_options *o)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_sess(काष्ठा osapsess *s)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_tpm_buf(अचिन्हित अक्षर *buf)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
