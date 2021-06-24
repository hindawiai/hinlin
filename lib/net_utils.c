<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>

bool mac_pton(स्थिर अक्षर *s, u8 *mac)
अणु
	पूर्णांक i;

	/* XX:XX:XX:XX:XX:XX */
	अगर (म_माप(s) < 3 * ETH_ALEN - 1)
		वापस false;

	/* Don't dirty result unless string is valid MAC. */
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		अगर (!है_षष्ठादशक(s[i * 3]) || !है_षष्ठादशक(s[i * 3 + 1]))
			वापस false;
		अगर (i != ETH_ALEN - 1 && s[i * 3 + 2] != ':')
			वापस false;
	पूर्ण
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac[i] = (hex_to_bin(s[i * 3]) << 4) | hex_to_bin(s[i * 3 + 1]);
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(mac_pton);
