<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2014 Intel Corporation

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

#अगर IS_ENABLED(CONFIG_BT_SELFTEST) && IS_MODULE(CONFIG_BT)

/* When CONFIG_BT_SELFTEST=y and the CONFIG_BT=m, then the self testing
 * is run at module loading समय.
 */
पूर्णांक bt_selftest(व्योम);

#अन्यथा

/* When CONFIG_BT_SELFTEST=y and CONFIG_BT=y, then the self testing
 * is run via late_initcall() to make sure that subsys_initcall() of
 * the Bluetooth subप्रणाली and device_initcall() of the Crypto subप्रणाली
 * करो not clash.
 *
 * When CONFIG_BT_SELFTEST=n, then this turns पूर्णांकo an empty call that
 * has no impact.
 */
अटल अंतरभूत पूर्णांक bt_selftest(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
