<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/* Bluetooth kernel library. */

#घोषणा pr_fmt(fmt) "Bluetooth: " fmt

#समावेश <linux/export.h>

#समावेश <net/bluetooth/bluetooth.h>

व्योम baswap(bdaddr_t *dst, स्थिर bdaddr_t *src)
अणु
	स्थिर अचिन्हित अक्षर *s = (स्थिर अचिन्हित अक्षर *)src;
	अचिन्हित अक्षर *d = (अचिन्हित अक्षर *)dst;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		d[i] = s[5 - i];
पूर्ण
EXPORT_SYMBOL(baswap);

/* Bluetooth error codes to Unix त्रुटि_सं mapping */
पूर्णांक bt_to_त्रुटि_सं(__u16 code)
अणु
	चयन (code) अणु
	हाल 0:
		वापस 0;

	हाल 0x01:
		वापस EBADRQC;

	हाल 0x02:
		वापस ENOTCONN;

	हाल 0x03:
		वापस EIO;

	हाल 0x04:
	हाल 0x3c:
		वापस EHOSTDOWN;

	हाल 0x05:
		वापस EACCES;

	हाल 0x06:
		वापस EBADE;

	हाल 0x07:
		वापस ENOMEM;

	हाल 0x08:
		वापस ETIMEDOUT;

	हाल 0x09:
		वापस EMLINK;

	हाल 0x0a:
		वापस EMLINK;

	हाल 0x0b:
		वापस EALREADY;

	हाल 0x0c:
		वापस EBUSY;

	हाल 0x0d:
	हाल 0x0e:
	हाल 0x0f:
		वापस ECONNREFUSED;

	हाल 0x10:
		वापस ETIMEDOUT;

	हाल 0x11:
	हाल 0x27:
	हाल 0x29:
	हाल 0x20:
		वापस EOPNOTSUPP;

	हाल 0x12:
		वापस EINVAL;

	हाल 0x13:
	हाल 0x14:
	हाल 0x15:
		वापस ECONNRESET;

	हाल 0x16:
		वापस ECONNABORTED;

	हाल 0x17:
		वापस ELOOP;

	हाल 0x18:
		वापस EACCES;

	हाल 0x1a:
		वापस EPROTONOSUPPORT;

	हाल 0x1b:
		वापस ECONNREFUSED;

	हाल 0x19:
	हाल 0x1e:
	हाल 0x23:
	हाल 0x24:
	हाल 0x25:
		वापस EPROTO;

	शेष:
		वापस ENOSYS;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(bt_to_त्रुटि_सं);

व्योम bt_info(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	pr_info("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_info);

व्योम bt_warn(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	pr_warn("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_warn);

व्योम bt_err(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	pr_err("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_err);

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
अटल bool debug_enable;

व्योम bt_dbg_set(bool enable)
अणु
	debug_enable = enable;
पूर्ण

bool bt_dbg_get(व्योम)
अणु
	वापस debug_enable;
पूर्ण

व्योम bt_dbg(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (likely(!debug_enable))
		वापस;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	prपूर्णांकk(KERN_DEBUG pr_fmt("%pV"), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_dbg);
#पूर्ण_अगर

व्योम bt_warn_ratelimited(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	pr_warn_ratelimited("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_warn_ratelimited);

व्योम bt_err_ratelimited(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	pr_err_ratelimited("%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(bt_err_ratelimited);
