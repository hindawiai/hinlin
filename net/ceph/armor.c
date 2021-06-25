<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/त्रुटिसं.स>

पूर्णांक ceph_armor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end);
पूर्णांक ceph_unarmor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end);

/*
 * base64 encode/decode.
 */

अटल स्थिर अक्षर *pem_key =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

अटल पूर्णांक encode_bits(पूर्णांक c)
अणु
	वापस pem_key[c];
पूर्ण

अटल पूर्णांक decode_bits(अक्षर c)
अणु
	अगर (c >= 'A' && c <= 'Z')
		वापस c - 'A';
	अगर (c >= 'a' && c <= 'z')
		वापस c - 'a' + 26;
	अगर (c >= '0' && c <= '9')
		वापस c - '0' + 52;
	अगर (c == '+')
		वापस 62;
	अगर (c == '/')
		वापस 63;
	अगर (c == '=')
		वापस 0; /* just non-negative, please */
	वापस -EINVAL;
पूर्ण

पूर्णांक ceph_armor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end)
अणु
	पूर्णांक olen = 0;
	पूर्णांक line = 0;

	जबतक (src < end) अणु
		अचिन्हित अक्षर a, b, c;

		a = *src++;
		*dst++ = encode_bits(a >> 2);
		अगर (src < end) अणु
			b = *src++;
			*dst++ = encode_bits(((a & 3) << 4) | (b >> 4));
			अगर (src < end) अणु
				c = *src++;
				*dst++ = encode_bits(((b & 15) << 2) |
						     (c >> 6));
				*dst++ = encode_bits(c & 63);
			पूर्ण अन्यथा अणु
				*dst++ = encode_bits((b & 15) << 2);
				*dst++ = '=';
			पूर्ण
		पूर्ण अन्यथा अणु
			*dst++ = encode_bits(((a & 3) << 4));
			*dst++ = '=';
			*dst++ = '=';
		पूर्ण
		olen += 4;
		line += 4;
		अगर (line == 64) अणु
			line = 0;
			*(dst++) = '\n';
			olen++;
		पूर्ण
	पूर्ण
	वापस olen;
पूर्ण

पूर्णांक ceph_unarmor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end)
अणु
	पूर्णांक olen = 0;

	जबतक (src < end) अणु
		पूर्णांक a, b, c, d;

		अगर (src[0] == '\n') अणु
			src++;
			जारी;
		पूर्ण
		अगर (src + 4 > end)
			वापस -EINVAL;
		a = decode_bits(src[0]);
		b = decode_bits(src[1]);
		c = decode_bits(src[2]);
		d = decode_bits(src[3]);
		अगर (a < 0 || b < 0 || c < 0 || d < 0)
			वापस -EINVAL;

		*dst++ = (a << 2) | (b >> 4);
		अगर (src[2] == '=')
			वापस olen + 1;
		*dst++ = ((b & 15) << 4) | (c >> 2);
		अगर (src[3] == '=')
			वापस olen + 2;
		*dst++ = ((c & 3) << 6) | d;
		olen += 3;
		src += 4;
	पूर्ण
	वापस olen;
पूर्ण
