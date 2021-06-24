<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * devtree.c - convenience functions क्रम device tree manipulation
 * Copyright 2007 David Gibson, IBM Corporation.
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 *
 * Authors: David Gibson <david@gibson.dropbear.id.au>
 *	    Scott Wood <scottwood@मुक्तscale.com>
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "ops.h"

व्योम dt_fixup_memory(u64 start, u64 size)
अणु
	व्योम *root, *memory;
	पूर्णांक naddr, nsize, i;
	u32 memreg[4];

	root = finddevice("/");
	अगर (getprop(root, "#address-cells", &naddr, माप(naddr)) < 0)
		naddr = 2;
	अगर (naddr < 1 || naddr > 2)
		fatal("Can't cope with #address-cells == %d in /\n\r", naddr);

	अगर (getprop(root, "#size-cells", &nsize, माप(nsize)) < 0)
		nsize = 1;
	अगर (nsize < 1 || nsize > 2)
		fatal("Can't cope with #size-cells == %d in /\n\r", nsize);

	i = 0;
	अगर (naddr == 2)
		memreg[i++] = start >> 32;
	memreg[i++] = start & 0xffffffff;
	अगर (nsize == 2)
		memreg[i++] = size >> 32;
	memreg[i++] = size & 0xffffffff;

	memory = finddevice("/memory");
	अगर (! memory) अणु
		memory = create_node(शून्य, "memory");
		setprop_str(memory, "device_type", "memory");
	पूर्ण

	म_लिखो("Memory <- <0x%x", memreg[0]);
	क्रम (i = 1; i < (naddr + nsize); i++)
		म_लिखो(" 0x%x", memreg[i]);
	म_लिखो("> (%ldMB)\n\r", (अचिन्हित दीर्घ)(size >> 20));

	setprop(memory, "reg", memreg, (naddr + nsize)*माप(u32));
पूर्ण

#घोषणा MHZ(x)	((x + 500000) / 1000000)

व्योम dt_fixup_cpu_घड़ीs(u32 cpu, u32 tb, u32 bus)
अणु
	व्योम *devp = शून्य;

	म_लिखो("CPU clock-frequency <- 0x%x (%dMHz)\n\r", cpu, MHZ(cpu));
	म_लिखो("CPU timebase-frequency <- 0x%x (%dMHz)\n\r", tb, MHZ(tb));
	अगर (bus > 0)
		म_लिखो("CPU bus-frequency <- 0x%x (%dMHz)\n\r", bus, MHZ(bus));

	जबतक ((devp = find_node_by_devtype(devp, "cpu"))) अणु
		setprop_val(devp, "clock-frequency", cpu);
		setprop_val(devp, "timebase-frequency", tb);
		अगर (bus > 0)
			setprop_val(devp, "bus-frequency", bus);
	पूर्ण

	समयbase_period_ns = 1000000000 / tb;
पूर्ण

व्योम dt_fixup_घड़ी(स्थिर अक्षर *path, u32 freq)
अणु
	व्योम *devp = finddevice(path);

	अगर (devp) अणु
		म_लिखो("%s: clock-frequency <- %x (%dMHz)\n\r", path, freq, MHZ(freq));
		setprop_val(devp, "clock-frequency", freq);
	पूर्ण
पूर्ण

व्योम dt_fixup_mac_address_by_alias(स्थिर अक्षर *alias, स्थिर u8 *addr)
अणु
	व्योम *devp = find_node_by_alias(alias);

	अगर (devp) अणु
		म_लिखो("%s: local-mac-address <-"
		       " %02x:%02x:%02x:%02x:%02x:%02x\n\r", alias,
		       addr[0], addr[1], addr[2],
		       addr[3], addr[4], addr[5]);

		setprop(devp, "local-mac-address", addr, 6);
	पूर्ण
पूर्ण

व्योम dt_fixup_mac_address(u32 index, स्थिर u8 *addr)
अणु
	व्योम *devp = find_node_by_prop_value(शून्य, "linux,network-index",
	                                     (व्योम*)&index, माप(index));

	अगर (devp) अणु
		म_लिखो("ENET%d: local-mac-address <-"
		       " %02x:%02x:%02x:%02x:%02x:%02x\n\r", index,
		       addr[0], addr[1], addr[2],
		       addr[3], addr[4], addr[5]);

		setprop(devp, "local-mac-address", addr, 6);
	पूर्ण
पूर्ण

व्योम __dt_fixup_mac_addresses(u32 startindex, ...)
अणु
	बहु_सूची ap;
	u32 index = startindex;
	स्थिर u8 *addr;

	बहु_शुरू(ap, startindex);

	जबतक ((addr = बहु_तर्क(ap, स्थिर u8 *)))
		dt_fixup_mac_address(index++, addr);

	बहु_पूर्ण(ap);
पूर्ण

#घोषणा MAX_ADDR_CELLS 4

व्योम dt_get_reg_क्रमmat(व्योम *node, u32 *naddr, u32 *nsize)
अणु
	अगर (getprop(node, "#address-cells", naddr, 4) != 4)
		*naddr = 2;
	अगर (getprop(node, "#size-cells", nsize, 4) != 4)
		*nsize = 1;
पूर्ण

अटल व्योम copy_val(u32 *dest, u32 *src, पूर्णांक naddr)
अणु
	पूर्णांक pad = MAX_ADDR_CELLS - naddr;

	स_रखो(dest, 0, pad * 4);
	स_नकल(dest + pad, src, naddr * 4);
पूर्ण

अटल पूर्णांक sub_reg(u32 *reg, u32 *sub)
अणु
	पूर्णांक i, borrow = 0;

	क्रम (i = MAX_ADDR_CELLS - 1; i >= 0; i--) अणु
		पूर्णांक prev_borrow = borrow;
		borrow = reg[i] < sub[i] + prev_borrow;
		reg[i] -= sub[i] + prev_borrow;
	पूर्ण

	वापस !borrow;
पूर्ण

अटल पूर्णांक add_reg(u32 *reg, u32 *add, पूर्णांक naddr)
अणु
	पूर्णांक i, carry = 0;

	क्रम (i = MAX_ADDR_CELLS - 1; i >= MAX_ADDR_CELLS - naddr; i--) अणु
		u64 पंचांगp = (u64)reg[i] + add[i] + carry;
		carry = पंचांगp >> 32;
		reg[i] = (u32)पंचांगp;
	पूर्ण

	वापस !carry;
पूर्ण

/* It is assumed that अगर the first byte of reg fits in a
 * range, then the whole reg block fits.
 */
अटल पूर्णांक compare_reg(u32 *reg, u32 *range, u32 *rangesize)
अणु
	पूर्णांक i;
	u32 end;

	क्रम (i = 0; i < MAX_ADDR_CELLS; i++) अणु
		अगर (reg[i] < range[i])
			वापस 0;
		अगर (reg[i] > range[i])
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < MAX_ADDR_CELLS; i++) अणु
		end = range[i] + rangesize[i];

		अगर (reg[i] < end)
			अवरोध;
		अगर (reg[i] > end)
			वापस 0;
	पूर्ण

	वापस reg[i] != end;
पूर्ण

/* reg must be MAX_ADDR_CELLS */
अटल पूर्णांक find_range(u32 *reg, u32 *ranges, पूर्णांक nregaddr,
                      पूर्णांक naddr, पूर्णांक nsize, पूर्णांक buflen)
अणु
	पूर्णांक nrange = nregaddr + naddr + nsize;
	पूर्णांक i;

	क्रम (i = 0; i + nrange <= buflen; i += nrange) अणु
		u32 range_addr[MAX_ADDR_CELLS];
		u32 range_size[MAX_ADDR_CELLS];

		copy_val(range_addr, ranges + i, nregaddr);
		copy_val(range_size, ranges + i + nregaddr + naddr, nsize);

		अगर (compare_reg(reg, range_addr, range_size))
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* Currently only generic buses without special encodings are supported.
 * In particular, PCI is not supported.  Also, only the beginning of the
 * reg block is tracked; size is ignored except in ranges.
 */
अटल u32 prop_buf[MAX_PROP_LEN / 4];

अटल पूर्णांक dt_xlate(व्योम *node, पूर्णांक res, पूर्णांक reglen, अचिन्हित दीर्घ *addr,
		अचिन्हित दीर्घ *size)
अणु
	u32 last_addr[MAX_ADDR_CELLS];
	u32 this_addr[MAX_ADDR_CELLS];
	व्योम *parent;
	u64 ret_addr, ret_size;
	u32 naddr, nsize, prev_naddr, prev_nsize;
	पूर्णांक buflen, offset;

	parent = get_parent(node);
	अगर (!parent)
		वापस 0;

	dt_get_reg_क्रमmat(parent, &naddr, &nsize);

	अगर (nsize > 2)
		वापस 0;

	offset = (naddr + nsize) * res;

	अगर (reglen < offset + naddr + nsize ||
	    MAX_PROP_LEN < (offset + naddr + nsize) * 4)
		वापस 0;

	copy_val(last_addr, prop_buf + offset, naddr);

	ret_size = prop_buf[offset + naddr];
	अगर (nsize == 2) अणु
		ret_size <<= 32;
		ret_size |= prop_buf[offset + naddr + 1];
	पूर्ण

	क्रम (;;) अणु
		prev_naddr = naddr;
		prev_nsize = nsize;
		node = parent;

		parent = get_parent(node);
		अगर (!parent)
			अवरोध;

		dt_get_reg_क्रमmat(parent, &naddr, &nsize);

		buflen = getprop(node, "ranges", prop_buf,
				माप(prop_buf));
		अगर (buflen == 0)
			जारी;
		अगर (buflen < 0 || buflen > माप(prop_buf))
			वापस 0;

		offset = find_range(last_addr, prop_buf, prev_naddr,
		                    naddr, prev_nsize, buflen / 4);

		अगर (offset < 0)
			वापस 0;

		copy_val(this_addr, prop_buf + offset, prev_naddr);

		अगर (!sub_reg(last_addr, this_addr))
			वापस 0;

		copy_val(this_addr, prop_buf + offset + prev_naddr, naddr);

		अगर (!add_reg(last_addr, this_addr, naddr))
			वापस 0;
	पूर्ण

	अगर (naddr > 2)
		वापस 0;

	ret_addr = ((u64)last_addr[2] << 32) | last_addr[3];

	अगर (माप(व्योम *) == 4 &&
	    (ret_addr >= 0x100000000ULL || ret_size > 0x100000000ULL ||
	     ret_addr + ret_size > 0x100000000ULL))
		वापस 0;

	*addr = ret_addr;
	अगर (size)
		*size = ret_size;

	वापस 1;
पूर्ण

पूर्णांक dt_xlate_reg(व्योम *node, पूर्णांक res, अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ *size)
अणु
	पूर्णांक reglen;

	reglen = getprop(node, "reg", prop_buf, माप(prop_buf)) / 4;
	वापस dt_xlate(node, res, reglen, addr, size);
पूर्ण

पूर्णांक dt_xlate_addr(व्योम *node, u32 *buf, पूर्णांक buflen, अचिन्हित दीर्घ *xlated_addr)
अणु

	अगर (buflen > माप(prop_buf))
		वापस 0;

	स_नकल(prop_buf, buf, buflen);
	वापस dt_xlate(node, 0, buflen / 4, xlated_addr, शून्य);
पूर्ण

पूर्णांक dt_is_compatible(व्योम *node, स्थिर अक्षर *compat)
अणु
	अक्षर *buf = (अक्षर *)prop_buf;
	पूर्णांक len, pos;

	len = getprop(node, "compatible", buf, MAX_PROP_LEN);
	अगर (len < 0)
		वापस 0;

	क्रम (pos = 0; pos < len; pos++) अणु
		अगर (!म_भेद(buf + pos, compat))
			वापस 1;

		pos += strnlen(&buf[pos], len - pos);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dt_get_भव_reg(व्योम *node, व्योम **addr, पूर्णांक nres)
अणु
	अचिन्हित दीर्घ xaddr;
	पूर्णांक n;

	n = getprop(node, "virtual-reg", addr, nres * 4);
	अगर (n > 0)
		वापस n / 4;

	क्रम (n = 0; n < nres; n++) अणु
		अगर (!dt_xlate_reg(node, n, &xaddr, शून्य))
			अवरोध;

		addr[n] = (व्योम *)xaddr;
	पूर्ण

	वापस n;
पूर्ण

