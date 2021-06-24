<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PlanetCore configuration data support functions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "stdio.h"
#समावेश "stdlib.h"
#समावेश "ops.h"
#समावेश "planetcore.h"
#समावेश "io.h"

/* PlanetCore passes inक्रमmation to the OS in the क्रमm of
 * a table of key=value strings, separated by newlines.
 *
 * The list is terminated by an empty string (i.e. two
 * consecutive newlines).
 *
 * To make it easier to parse, we first convert all the
 * newlines पूर्णांकo null bytes.
 */

व्योम planetcore_prepare_table(अक्षर *table)
अणु
	करो अणु
		अगर (*table == '\n')
			*table = 0;

		table++;
	पूर्ण जबतक (*(table - 1) || *table != '\n');

	*table = 0;
पूर्ण

स्थिर अक्षर *planetcore_get_key(स्थिर अक्षर *table, स्थिर अक्षर *key)
अणु
	पूर्णांक keylen = म_माप(key);

	करो अणु
		अगर (!म_भेदन(table, key, keylen) && table[keylen] == '=')
			वापस table + keylen + 1;

		table += म_माप(table) + 1;
	पूर्ण जबतक (म_माप(table) != 0);

	वापस शून्य;
पूर्ण

पूर्णांक planetcore_get_decimal(स्थिर अक्षर *table, स्थिर अक्षर *key, u64 *val)
अणु
	स्थिर अक्षर *str = planetcore_get_key(table, key);
	अगर (!str)
		वापस 0;

	*val = म_से_अदीर्घl(str, शून्य, 10);
	वापस 1;
पूर्ण

पूर्णांक planetcore_get_hex(स्थिर अक्षर *table, स्थिर अक्षर *key, u64 *val)
अणु
	स्थिर अक्षर *str = planetcore_get_key(table, key);
	अगर (!str)
		वापस 0;

	*val = म_से_अदीर्घl(str, शून्य, 16);
	वापस 1;
पूर्ण

अटल u64 mac_table[4] = अणु
	0x000000000000,
	0x000000800000,
	0x000000400000,
	0x000000c00000,
पूर्ण;

व्योम planetcore_set_mac_addrs(स्थिर अक्षर *table)
अणु
	u8 addr[4][6];
	u64 पूर्णांक_addr;
	u32 i;
	पूर्णांक j;

	अगर (!planetcore_get_hex(table, PLANETCORE_KEY_MAC_ADDR, &पूर्णांक_addr))
		वापस;

	क्रम (i = 0; i < 4; i++) अणु
		u64 this_dev_addr = (पूर्णांक_addr & ~0x000000c00000) |
		                    mac_table[i];

		क्रम (j = 5; j >= 0; j--) अणु
			addr[i][j] = this_dev_addr & 0xff;
			this_dev_addr >>= 8;
		पूर्ण

		dt_fixup_mac_address(i, addr[i]);
	पूर्ण
पूर्ण

अटल अक्षर prop_buf[MAX_PROP_LEN];

व्योम planetcore_set_मानक_निकास_path(स्थिर अक्षर *table)
अणु
	अक्षर *path;
	स्थिर अक्षर *label;
	व्योम *node, *chosen;

	label = planetcore_get_key(table, PLANETCORE_KEY_SERIAL_PORT);
	अगर (!label)
		वापस;

	node = find_node_by_prop_value_str(शून्य, "linux,planetcore-label",
	                                   label);
	अगर (!node)
		वापस;

	path = get_path(node, prop_buf, MAX_PROP_LEN);
	अगर (!path)
		वापस;

	chosen = finddevice("/chosen");
	अगर (!chosen)
		chosen = create_node(शून्य, "chosen");
	अगर (!chosen)
		वापस;

	setprop_str(chosen, "linux,stdout-path", path);
पूर्ण
