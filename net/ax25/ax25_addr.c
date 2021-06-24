<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * The शेष broadcast address of an पूर्णांकerface is QST-0; the शेष address
 * is LINUX-1.  The null address is defined as a callsign of all spaces with
 * an SSID of zero.
 */

स्थिर ax25_address ax25_bcast =
	अणुअणु'Q' << 1, 'S' << 1, 'T' << 1, ' ' << 1, ' ' << 1, ' ' << 1, 0 << 1पूर्णपूर्ण;
स्थिर ax25_address ax25_defaddr =
	अणुअणु'L' << 1, 'I' << 1, 'N' << 1, 'U' << 1, 'X' << 1, ' ' << 1, 1 << 1पूर्णपूर्ण;
स्थिर ax25_address null_ax25_address =
	अणुअणु' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, 0 << 1पूर्णपूर्ण;

EXPORT_SYMBOL_GPL(ax25_bcast);
EXPORT_SYMBOL_GPL(ax25_defaddr);
EXPORT_SYMBOL(null_ax25_address);

/*
 *	ax25 -> ascii conversion
 */
अक्षर *ax2asc(अक्षर *buf, स्थिर ax25_address *a)
अणु
	अक्षर c, *s;
	पूर्णांक n;

	क्रम (n = 0, s = buf; n < 6; n++) अणु
		c = (a->ax25_call[n] >> 1) & 0x7F;

		अगर (c != ' ') *s++ = c;
	पूर्ण

	*s++ = '-';

	अगर ((n = ((a->ax25_call[6] >> 1) & 0x0F)) > 9) अणु
		*s++ = '1';
		n -= 10;
	पूर्ण

	*s++ = n + '0';
	*s++ = '\0';

	अगर (*buf == '\0' || *buf == '-')
	   वापस "*";

	वापस buf;

पूर्ण

EXPORT_SYMBOL(ax2asc);

/*
 *	ascii -> ax25 conversion
 */
व्योम asc2ax(ax25_address *addr, स्थिर अक्षर *callsign)
अणु
	स्थिर अक्षर *s;
	पूर्णांक n;

	क्रम (s = callsign, n = 0; n < 6; n++) अणु
		अगर (*s != '\0' && *s != '-')
			addr->ax25_call[n] = *s++;
		अन्यथा
			addr->ax25_call[n] = ' ';
		addr->ax25_call[n] <<= 1;
		addr->ax25_call[n] &= 0xFE;
	पूर्ण

	अगर (*s++ == '\0') अणु
		addr->ax25_call[6] = 0x00;
		वापस;
	पूर्ण

	addr->ax25_call[6] = *s++ - '0';

	अगर (*s != '\0') अणु
		addr->ax25_call[6] *= 10;
		addr->ax25_call[6] += *s++ - '0';
	पूर्ण

	addr->ax25_call[6] <<= 1;
	addr->ax25_call[6] &= 0x1E;
पूर्ण

EXPORT_SYMBOL(asc2ax);

/*
 *	Compare two ax.25 addresses
 */
पूर्णांक ax25cmp(स्थिर ax25_address *a, स्थिर ax25_address *b)
अणु
	पूर्णांक ct = 0;

	जबतक (ct < 6) अणु
		अगर ((a->ax25_call[ct] & 0xFE) != (b->ax25_call[ct] & 0xFE))	/* Clean off repeater bits */
			वापस 1;
		ct++;
	पूर्ण

	अगर ((a->ax25_call[ct] & 0x1E) == (b->ax25_call[ct] & 0x1E))	/* SSID without control bit */
		वापस 0;

	वापस 2;			/* Partial match */
पूर्ण

EXPORT_SYMBOL(ax25cmp);

/*
 *	Compare two AX.25 digipeater paths.
 */
पूर्णांक ax25digicmp(स्थिर ax25_digi *digi1, स्थिर ax25_digi *digi2)
अणु
	पूर्णांक i;

	अगर (digi1->ndigi != digi2->ndigi)
		वापस 1;

	अगर (digi1->lastrepeat != digi2->lastrepeat)
		वापस 1;

	क्रम (i = 0; i < digi1->ndigi; i++)
		अगर (ax25cmp(&digi1->calls[i], &digi2->calls[i]) != 0)
			वापस 1;

	वापस 0;
पूर्ण

/*
 *	Given an AX.25 address pull of to, from, digi list, command/response and the start of data
 *
 */
स्थिर अचिन्हित अक्षर *ax25_addr_parse(स्थिर अचिन्हित अक्षर *buf, पूर्णांक len,
	ax25_address *src, ax25_address *dest, ax25_digi *digi, पूर्णांक *flags,
	पूर्णांक *dama)
अणु
	पूर्णांक d = 0;

	अगर (len < 14) वापस शून्य;

	अगर (flags != शून्य) अणु
		*flags = 0;

		अगर (buf[6] & AX25_CBIT)
			*flags = AX25_COMMAND;
		अगर (buf[13] & AX25_CBIT)
			*flags = AX25_RESPONSE;
	पूर्ण

	अगर (dama != शून्य)
		*dama = ~buf[13] & AX25_DAMA_FLAG;

	/* Copy to, from */
	अगर (dest != शून्य)
		स_नकल(dest, buf + 0, AX25_ADDR_LEN);
	अगर (src != शून्य)
		स_नकल(src,  buf + 7, AX25_ADDR_LEN);

	buf += 2 * AX25_ADDR_LEN;
	len -= 2 * AX25_ADDR_LEN;

	digi->lastrepeat = -1;
	digi->ndigi      = 0;

	जबतक (!(buf[-1] & AX25_EBIT)) अणु
		अगर (d >= AX25_MAX_DIGIS)
			वापस शून्य;
		अगर (len < AX25_ADDR_LEN)
			वापस शून्य;

		स_नकल(&digi->calls[d], buf, AX25_ADDR_LEN);
		digi->ndigi = d + 1;

		अगर (buf[6] & AX25_HBIT) अणु
			digi->repeated[d] = 1;
			digi->lastrepeat  = d;
		पूर्ण अन्यथा अणु
			digi->repeated[d] = 0;
		पूर्ण

		buf += AX25_ADDR_LEN;
		len -= AX25_ADDR_LEN;
		d++;
	पूर्ण

	वापस buf;
पूर्ण

/*
 *	Assemble an AX.25 header from the bits
 */
पूर्णांक ax25_addr_build(अचिन्हित अक्षर *buf, स्थिर ax25_address *src,
	स्थिर ax25_address *dest, स्थिर ax25_digi *d, पूर्णांक flag, पूर्णांक modulus)
अणु
	पूर्णांक len = 0;
	पूर्णांक ct  = 0;

	स_नकल(buf, dest, AX25_ADDR_LEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] |= AX25_SSSID_SPARE;

	अगर (flag == AX25_COMMAND) buf[6] |= AX25_CBIT;

	buf += AX25_ADDR_LEN;
	len += AX25_ADDR_LEN;

	स_नकल(buf, src, AX25_ADDR_LEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] &= ~AX25_SSSID_SPARE;

	अगर (modulus == AX25_MODULUS)
		buf[6] |= AX25_SSSID_SPARE;
	अन्यथा
		buf[6] |= AX25_ESSID_SPARE;

	अगर (flag == AX25_RESPONSE) buf[6] |= AX25_CBIT;

	/*
	 *	Fast path the normal digiless path
	 */
	अगर (d == शून्य || d->ndigi == 0) अणु
		buf[6] |= AX25_EBIT;
		वापस 2 * AX25_ADDR_LEN;
	पूर्ण

	buf += AX25_ADDR_LEN;
	len += AX25_ADDR_LEN;

	जबतक (ct < d->ndigi) अणु
		स_नकल(buf, &d->calls[ct], AX25_ADDR_LEN);

		अगर (d->repeated[ct])
			buf[6] |= AX25_HBIT;
		अन्यथा
			buf[6] &= ~AX25_HBIT;

		buf[6] &= ~AX25_EBIT;
		buf[6] |= AX25_SSSID_SPARE;

		buf += AX25_ADDR_LEN;
		len += AX25_ADDR_LEN;
		ct++;
	पूर्ण

	buf[-1] |= AX25_EBIT;

	वापस len;
पूर्ण

पूर्णांक ax25_addr_size(स्थिर ax25_digi *dp)
अणु
	अगर (dp == शून्य)
		वापस 2 * AX25_ADDR_LEN;

	वापस AX25_ADDR_LEN * (2 + dp->ndigi);
पूर्ण

/*
 *	Reverse Digipeat List. May not pass both parameters as same काष्ठा
 */
व्योम ax25_digi_invert(स्थिर ax25_digi *in, ax25_digi *out)
अणु
	पूर्णांक ct;

	out->ndigi      = in->ndigi;
	out->lastrepeat = in->ndigi - in->lastrepeat - 2;

	/* Invert the digipeaters */
	क्रम (ct = 0; ct < in->ndigi; ct++) अणु
		out->calls[ct] = in->calls[in->ndigi - ct - 1];

		अगर (ct <= out->lastrepeat) अणु
			out->calls[ct].ax25_call[6] |= AX25_HBIT;
			out->repeated[ct]            = 1;
		पूर्ण अन्यथा अणु
			out->calls[ct].ax25_call[6] &= ~AX25_HBIT;
			out->repeated[ct]            = 0;
		पूर्ण
	पूर्ण
पूर्ण
