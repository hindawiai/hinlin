<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PURGATORY_H
#घोषणा _LINUX_PURGATORY_H

#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>
#समावेश <uapi/linux/kexec.h>

काष्ठा kexec_sha_region अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ len;
पूर्ण;

/*
 * These क्रमward declarations serve two purposes:
 *
 * 1) Make sparse happy when checking arch/purgatory
 * 2) Document that these are required to be global so the symbol
 *    lookup in kexec works
 */
बाह्य काष्ठा kexec_sha_region purgatory_sha_regions[KEXEC_SEGMENT_MAX];
बाह्य u8 purgatory_sha256_digest[SHA256_DIGEST_SIZE];

#पूर्ण_अगर
