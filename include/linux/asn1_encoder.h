<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _LINUX_ASN1_ENCODER_H
#घोषणा _LINUX_ASN1_ENCODER_H

#समावेश <linux/types.h>
#समावेश <linux/asn1.h>
#समावेश <linux/asn1_ber_bytecode.h>
#समावेश <linux/bug.h>

#घोषणा asn1_oid_len(oid) (माप(oid)/माप(u32))
अचिन्हित अक्षर *
asn1_encode_पूर्णांकeger(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		    s64 पूर्णांकeger);
अचिन्हित अक्षर *
asn1_encode_oid(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		u32 oid[], पूर्णांक oid_len);
अचिन्हित अक्षर *
asn1_encode_tag(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		u32 tag, स्थिर अचिन्हित अक्षर *string, पूर्णांक len);
अचिन्हित अक्षर *
asn1_encode_octet_string(अचिन्हित अक्षर *data,
			 स्थिर अचिन्हित अक्षर *end_data,
			 स्थिर अचिन्हित अक्षर *string, u32 len);
अचिन्हित अक्षर *
asn1_encode_sequence(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		     स्थिर अचिन्हित अक्षर *seq, पूर्णांक len);
अचिन्हित अक्षर *
asn1_encode_boolean(अचिन्हित अक्षर *data, स्थिर अचिन्हित अक्षर *end_data,
		    bool val);

#पूर्ण_अगर
