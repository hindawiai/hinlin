<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   Unix SMB/Netbios implementation.
   Version 1.9.
   SMB parameters and setup
   Copyright (C) Andrew Tridgell 1992-2000
   Copyright (C) Luke Kenneth Casson Leighton 1996-2000
   Modअगरied by Jeremy Allison 1995.
   Copyright (C) Andrew Bartlett <abartlet@samba.org> 2002-2003
   Modअगरied by Steve French (sfrench@us.ibm.com) 2002-2003

*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fips.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <crypto/des.h>
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifsproto.h"

#अगर_अघोषित false
#घोषणा false 0
#पूर्ण_अगर
#अगर_अघोषित true
#घोषणा true 1
#पूर्ण_अगर

/* following came from the other byteorder.h to aव्योम include conflicts */
#घोषणा CVAL(buf,pos) (((अचिन्हित अक्षर *)(buf))[pos])
#घोषणा SSVALX(buf,pos,val) (CVAL(buf,pos)=(val)&0xFF,CVAL(buf,pos+1)=(val)>>8)
#घोषणा SSVAL(buf,pos,val) SSVALX((buf),(pos),((__u16)(val)))

अटल व्योम
str_to_key(अचिन्हित अक्षर *str, अचिन्हित अक्षर *key)
अणु
	पूर्णांक i;

	key[0] = str[0] >> 1;
	key[1] = ((str[0] & 0x01) << 6) | (str[1] >> 2);
	key[2] = ((str[1] & 0x03) << 5) | (str[2] >> 3);
	key[3] = ((str[2] & 0x07) << 4) | (str[3] >> 4);
	key[4] = ((str[3] & 0x0F) << 3) | (str[4] >> 5);
	key[5] = ((str[4] & 0x1F) << 2) | (str[5] >> 6);
	key[6] = ((str[5] & 0x3F) << 1) | (str[6] >> 7);
	key[7] = str[6] & 0x7F;
	क्रम (i = 0; i < 8; i++)
		key[i] = (key[i] << 1);
पूर्ण

अटल पूर्णांक
smbhash(अचिन्हित अक्षर *out, स्थिर अचिन्हित अक्षर *in, अचिन्हित अक्षर *key)
अणु
	अचिन्हित अक्षर key2[8];
	काष्ठा des_ctx ctx;

	str_to_key(key, key2);

	अगर (fips_enabled) अणु
		cअगरs_dbg(VFS, "FIPS compliance enabled: DES not permitted\n");
		वापस -ENOENT;
	पूर्ण

	des_expand_key(&ctx, key2, DES_KEY_SIZE);
	des_encrypt(&ctx, out, in);
	memzero_explicit(&ctx, माप(ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक
E_P16(अचिन्हित अक्षर *p14, अचिन्हित अक्षर *p16)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर sp8[8] =
	    अणु 0x4b, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25 पूर्ण;

	rc = smbhash(p16, sp8, p14);
	अगर (rc)
		वापस rc;
	rc = smbhash(p16 + 8, sp8, p14 + 7);
	वापस rc;
पूर्ण

अटल पूर्णांक
E_P24(अचिन्हित अक्षर *p21, स्थिर अचिन्हित अक्षर *c8, अचिन्हित अक्षर *p24)
अणु
	पूर्णांक rc;

	rc = smbhash(p24, c8, p21);
	अगर (rc)
		वापस rc;
	rc = smbhash(p24 + 8, c8, p21 + 7);
	अगर (rc)
		वापस rc;
	rc = smbhash(p24 + 16, c8, p21 + 14);
	वापस rc;
पूर्ण

/* produce a md4 message digest from data of length n bytes */
पूर्णांक
mdfour(अचिन्हित अक्षर *md4_hash, अचिन्हित अक्षर *link_str, पूर्णांक link_len)
अणु
	पूर्णांक rc;
	काष्ठा crypto_shash *md4 = शून्य;
	काष्ठा sdesc *sdescmd4 = शून्य;

	rc = cअगरs_alloc_hash("md4", &md4, &sdescmd4);
	अगर (rc)
		जाओ mdfour_err;

	rc = crypto_shash_init(&sdescmd4->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init md4 shash\n", __func__);
		जाओ mdfour_err;
	पूर्ण
	rc = crypto_shash_update(&sdescmd4->shash, link_str, link_len);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with link_str\n", __func__);
		जाओ mdfour_err;
	पूर्ण
	rc = crypto_shash_final(&sdescmd4->shash, md4_hash);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate md4 hash\n", __func__);

mdfour_err:
	cअगरs_मुक्त_hash(&md4, &sdescmd4);
	वापस rc;
पूर्ण

/*
   This implements the X/Open SMB password encryption
   It takes a password, a 8 byte "crypt key" and माला_दो 24 bytes of
   encrypted password पूर्णांकo p24 */
/* Note that password must be upperहालd and null terminated */
पूर्णांक
SMBencrypt(अचिन्हित अक्षर *passwd, स्थिर अचिन्हित अक्षर *c8, अचिन्हित अक्षर *p24)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर p14[14], p16[16], p21[21];

	स_रखो(p14, '\0', 14);
	स_रखो(p16, '\0', 16);
	स_रखो(p21, '\0', 21);

	स_नकल(p14, passwd, 14);
	rc = E_P16(p14, p16);
	अगर (rc)
		वापस rc;

	स_नकल(p21, p16, 16);
	rc = E_P24(p21, c8, p24);

	वापस rc;
पूर्ण

/*
 * Creates the MD4 Hash of the users password in NT UNICODE.
 */

पूर्णांक
E_md4hash(स्थिर अचिन्हित अक्षर *passwd, अचिन्हित अक्षर *p16,
	स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक rc;
	पूर्णांक len;
	__le16 wpwd[129];

	/* Password cannot be दीर्घer than 128 अक्षरacters */
	अगर (passwd) /* Password must be converted to NT unicode */
		len = cअगरs_strtoUTF16(wpwd, passwd, 128, codepage);
	अन्यथा अणु
		len = 0;
		*wpwd = 0; /* Ensure string is null terminated */
	पूर्ण

	rc = mdfour(p16, (अचिन्हित अक्षर *) wpwd, len * माप(__le16));
	memzero_explicit(wpwd, माप(wpwd));

	वापस rc;
पूर्ण

/* Does the NT MD4 hash then des encryption. */
पूर्णांक
SMBNTencrypt(अचिन्हित अक्षर *passwd, अचिन्हित अक्षर *c8, अचिन्हित अक्षर *p24,
		स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर p16[16], p21[21];

	स_रखो(p16, '\0', 16);
	स_रखो(p21, '\0', 21);

	rc = E_md4hash(passwd, p16, codepage);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s Can't generate NT hash, error: %d\n",
			 __func__, rc);
		वापस rc;
	पूर्ण
	स_नकल(p21, p16, 16);
	rc = E_P24(p21, c8, p24);
	वापस rc;
पूर्ण
