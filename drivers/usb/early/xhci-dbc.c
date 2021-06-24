<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xhci-dbc.c - xHCI debug capability early driver
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/console.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/memblock.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <linux/bcd.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/usb/xhci-dbgp.h>

#समावेश "../host/xhci.h"
#समावेश "xhci-dbc.h"

अटल काष्ठा xdbc_state xdbc;
अटल bool early_console_keep;

#अगर_घोषित XDBC_TRACE
#घोषणा	xdbc_trace	trace_prपूर्णांकk
#अन्यथा
अटल अंतरभूत व्योम xdbc_trace(स्थिर अक्षर *fmt, ...) अणु पूर्ण
#पूर्ण_अगर /* XDBC_TRACE */

अटल व्योम __iomem * __init xdbc_map_pci_mmio(u32 bus, u32 dev, u32 func)
अणु
	u64 val64, sz64, mask64;
	व्योम __iomem *base;
	u32 val, sz;
	u8 byte;

	val = पढ़ो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0);
	ग_लिखो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0, ~0);
	sz = पढ़ो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0);
	ग_लिखो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0, val);

	अगर (val == 0xffffffff || sz == 0xffffffff) अणु
		pr_notice("invalid mmio bar\n");
		वापस शून्य;
	पूर्ण

	val64	= val & PCI_BASE_ADDRESS_MEM_MASK;
	sz64	= sz & PCI_BASE_ADDRESS_MEM_MASK;
	mask64	= PCI_BASE_ADDRESS_MEM_MASK;

	अगर ((val & PCI_BASE_ADDRESS_MEM_TYPE_MASK) == PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
		val = पढ़ो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0 + 4);
		ग_लिखो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0 + 4, ~0);
		sz = पढ़ो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0 + 4);
		ग_लिखो_pci_config(bus, dev, func, PCI_BASE_ADDRESS_0 + 4, val);

		val64	|= (u64)val << 32;
		sz64	|= (u64)sz << 32;
		mask64	|= ~0ULL << 32;
	पूर्ण

	sz64 &= mask64;

	अगर (!sz64) अणु
		pr_notice("invalid mmio address\n");
		वापस शून्य;
	पूर्ण

	sz64 = 1ULL << __ffs64(sz64);

	/* Check अगर the mem space is enabled: */
	byte = पढ़ो_pci_config_byte(bus, dev, func, PCI_COMMAND);
	अगर (!(byte & PCI_COMMAND_MEMORY)) अणु
		byte |= PCI_COMMAND_MEMORY;
		ग_लिखो_pci_config_byte(bus, dev, func, PCI_COMMAND, byte);
	पूर्ण

	xdbc.xhci_start = val64;
	xdbc.xhci_length = sz64;
	base = early_ioremap(val64, sz64);

	वापस base;
पूर्ण

अटल व्योम * __init xdbc_get_page(dma_addr_t *dma_addr)
अणु
	व्योम *virt;

	virt = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!virt)
		वापस शून्य;

	अगर (dma_addr)
		*dma_addr = (dma_addr_t)__pa(virt);

	वापस virt;
पूर्ण

अटल u32 __init xdbc_find_dbgp(पूर्णांक xdbc_num, u32 *b, u32 *d, u32 *f)
अणु
	u32 bus, dev, func, class;

	क्रम (bus = 0; bus < XDBC_PCI_MAX_BUSES; bus++) अणु
		क्रम (dev = 0; dev < XDBC_PCI_MAX_DEVICES; dev++) अणु
			क्रम (func = 0; func < XDBC_PCI_MAX_FUNCTION; func++) अणु

				class = पढ़ो_pci_config(bus, dev, func, PCI_CLASS_REVISION);
				अगर ((class >> 8) != PCI_CLASS_SERIAL_USB_XHCI)
					जारी;

				अगर (xdbc_num-- != 0)
					जारी;

				*b = bus;
				*d = dev;
				*f = func;

				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक handshake(व्योम __iomem *ptr, u32 mask, u32 करोne, पूर्णांक रुको, पूर्णांक delay)
अणु
	u32 result;

	वापस पढ़ोl_poll_समयout_atomic(ptr, result,
					 ((result & mask) == करोne),
					 delay, रुको);
पूर्ण

अटल व्योम __init xdbc_bios_hanकरोff(व्योम)
अणु
	पूर्णांक offset, समयout;
	u32 val;

	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_LEGACY);
	val = पढ़ोl(xdbc.xhci_base + offset);

	अगर (val & XHCI_HC_BIOS_OWNED) अणु
		ग_लिखोl(val | XHCI_HC_OS_OWNED, xdbc.xhci_base + offset);
		समयout = handshake(xdbc.xhci_base + offset, XHCI_HC_BIOS_OWNED, 0, 5000, 10);

		अगर (समयout) अणु
			pr_notice("failed to hand over xHCI control from BIOS\n");
			ग_लिखोl(val & ~XHCI_HC_BIOS_OWNED, xdbc.xhci_base + offset);
		पूर्ण
	पूर्ण

	/* Disable BIOS SMIs and clear all SMI events: */
	val = पढ़ोl(xdbc.xhci_base + offset + XHCI_LEGACY_CONTROL_OFFSET);
	val &= XHCI_LEGACY_DISABLE_SMI;
	val |= XHCI_LEGACY_SMI_EVENTS;
	ग_लिखोl(val, xdbc.xhci_base + offset + XHCI_LEGACY_CONTROL_OFFSET);
पूर्ण

अटल पूर्णांक __init
xdbc_alloc_ring(काष्ठा xdbc_segment *seg, काष्ठा xdbc_ring *ring)
अणु
	seg->trbs = xdbc_get_page(&seg->dma);
	अगर (!seg->trbs)
		वापस -ENOMEM;

	ring->segment = seg;

	वापस 0;
पूर्ण

अटल व्योम __init xdbc_मुक्त_ring(काष्ठा xdbc_ring *ring)
अणु
	काष्ठा xdbc_segment *seg = ring->segment;

	अगर (!seg)
		वापस;

	memblock_मुक्त(seg->dma, PAGE_SIZE);
	ring->segment = शून्य;
पूर्ण

अटल व्योम xdbc_reset_ring(काष्ठा xdbc_ring *ring)
अणु
	काष्ठा xdbc_segment *seg = ring->segment;
	काष्ठा xdbc_trb *link_trb;

	स_रखो(seg->trbs, 0, PAGE_SIZE);

	ring->enqueue = seg->trbs;
	ring->dequeue = seg->trbs;
	ring->cycle_state = 1;

	अगर (ring != &xdbc.evt_ring) अणु
		link_trb = &seg->trbs[XDBC_TRBS_PER_SEGMENT - 1];
		link_trb->field[0] = cpu_to_le32(lower_32_bits(seg->dma));
		link_trb->field[1] = cpu_to_le32(upper_32_bits(seg->dma));
		link_trb->field[3] = cpu_to_le32(TRB_TYPE(TRB_LINK)) | cpu_to_le32(LINK_TOGGLE);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम xdbc_put_utf16(u16 *s, स्थिर अक्षर *c, माप_प्रकार size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		s[i] = cpu_to_le16(c[i]);
पूर्ण

अटल व्योम xdbc_mem_init(व्योम)
अणु
	काष्ठा xdbc_ep_context *ep_in, *ep_out;
	काष्ठा usb_string_descriptor *s_desc;
	काष्ठा xdbc_erst_entry *entry;
	काष्ठा xdbc_strings *strings;
	काष्ठा xdbc_context *ctx;
	अचिन्हित पूर्णांक max_burst;
	u32 string_length;
	पूर्णांक index = 0;
	u32 dev_info;

	xdbc_reset_ring(&xdbc.evt_ring);
	xdbc_reset_ring(&xdbc.in_ring);
	xdbc_reset_ring(&xdbc.out_ring);
	स_रखो(xdbc.table_base, 0, PAGE_SIZE);
	स_रखो(xdbc.out_buf, 0, PAGE_SIZE);

	/* Initialize event ring segment table: */
	xdbc.erst_size	= 16;
	xdbc.erst_base	= xdbc.table_base + index * XDBC_TABLE_ENTRY_SIZE;
	xdbc.erst_dma	= xdbc.table_dma + index * XDBC_TABLE_ENTRY_SIZE;

	index += XDBC_ERST_ENTRY_NUM;
	entry = (काष्ठा xdbc_erst_entry *)xdbc.erst_base;

	entry->seg_addr		= cpu_to_le64(xdbc.evt_seg.dma);
	entry->seg_size		= cpu_to_le32(XDBC_TRBS_PER_SEGMENT);
	entry->__reserved_0	= 0;

	/* Initialize ERST रेजिस्टरs: */
	ग_लिखोl(1, &xdbc.xdbc_reg->ersts);
	xdbc_ग_लिखो64(xdbc.erst_dma, &xdbc.xdbc_reg->erstba);
	xdbc_ग_लिखो64(xdbc.evt_seg.dma, &xdbc.xdbc_reg->erdp);

	/* Debug capability contexts: */
	xdbc.dbcc_size	= 64 * 3;
	xdbc.dbcc_base	= xdbc.table_base + index * XDBC_TABLE_ENTRY_SIZE;
	xdbc.dbcc_dma	= xdbc.table_dma + index * XDBC_TABLE_ENTRY_SIZE;

	index += XDBC_DBCC_ENTRY_NUM;

	/* Popluate the strings: */
	xdbc.string_size = माप(काष्ठा xdbc_strings);
	xdbc.string_base = xdbc.table_base + index * XDBC_TABLE_ENTRY_SIZE;
	xdbc.string_dma	 = xdbc.table_dma + index * XDBC_TABLE_ENTRY_SIZE;
	strings		 = (काष्ठा xdbc_strings *)xdbc.string_base;

	index += XDBC_STRING_ENTRY_NUM;

	/* Serial string: */
	s_desc			= (काष्ठा usb_string_descriptor *)strings->serial;
	s_desc->bLength		= (म_माप(XDBC_STRING_SERIAL) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;

	xdbc_put_utf16(s_desc->wData, XDBC_STRING_SERIAL, म_माप(XDBC_STRING_SERIAL));
	string_length = s_desc->bLength;
	string_length <<= 8;

	/* Product string: */
	s_desc			= (काष्ठा usb_string_descriptor *)strings->product;
	s_desc->bLength		= (म_माप(XDBC_STRING_PRODUCT) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;

	xdbc_put_utf16(s_desc->wData, XDBC_STRING_PRODUCT, म_माप(XDBC_STRING_PRODUCT));
	string_length += s_desc->bLength;
	string_length <<= 8;

	/* Manufacture string: */
	s_desc			= (काष्ठा usb_string_descriptor *)strings->manufacturer;
	s_desc->bLength		= (म_माप(XDBC_STRING_MANUFACTURER) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;

	xdbc_put_utf16(s_desc->wData, XDBC_STRING_MANUFACTURER, म_माप(XDBC_STRING_MANUFACTURER));
	string_length += s_desc->bLength;
	string_length <<= 8;

	/* String0: */
	strings->string0[0]	= 4;
	strings->string0[1]	= USB_DT_STRING;
	strings->string0[2]	= 0x09;
	strings->string0[3]	= 0x04;

	string_length += 4;

	/* Populate info Context: */
	ctx = (काष्ठा xdbc_context *)xdbc.dbcc_base;

	ctx->info.string0	= cpu_to_le64(xdbc.string_dma);
	ctx->info.manufacturer	= cpu_to_le64(xdbc.string_dma + XDBC_MAX_STRING_LENGTH);
	ctx->info.product	= cpu_to_le64(xdbc.string_dma + XDBC_MAX_STRING_LENGTH * 2);
	ctx->info.serial	= cpu_to_le64(xdbc.string_dma + XDBC_MAX_STRING_LENGTH * 3);
	ctx->info.length	= cpu_to_le32(string_length);

	/* Populate bulk out endpoपूर्णांक context: */
	max_burst = DEBUG_MAX_BURST(पढ़ोl(&xdbc.xdbc_reg->control));
	ep_out = (काष्ठा xdbc_ep_context *)&ctx->out;

	ep_out->ep_info1	= 0;
	ep_out->ep_info2	= cpu_to_le32(EP_TYPE(BULK_OUT_EP) | MAX_PACKET(1024) | MAX_BURST(max_burst));
	ep_out->deq		= cpu_to_le64(xdbc.out_seg.dma | xdbc.out_ring.cycle_state);

	/* Populate bulk in endpoपूर्णांक context: */
	ep_in = (काष्ठा xdbc_ep_context *)&ctx->in;

	ep_in->ep_info1		= 0;
	ep_in->ep_info2		= cpu_to_le32(EP_TYPE(BULK_IN_EP) | MAX_PACKET(1024) | MAX_BURST(max_burst));
	ep_in->deq		= cpu_to_le64(xdbc.in_seg.dma | xdbc.in_ring.cycle_state);

	/* Set DbC context and info रेजिस्टरs: */
	xdbc_ग_लिखो64(xdbc.dbcc_dma, &xdbc.xdbc_reg->dccp);

	dev_info = cpu_to_le32((XDBC_VENDOR_ID << 16) | XDBC_PROTOCOL);
	ग_लिखोl(dev_info, &xdbc.xdbc_reg->devinfo1);

	dev_info = cpu_to_le32((XDBC_DEVICE_REV << 16) | XDBC_PRODUCT_ID);
	ग_लिखोl(dev_info, &xdbc.xdbc_reg->devinfo2);

	xdbc.in_buf = xdbc.out_buf + XDBC_MAX_PACKET;
	xdbc.in_dma = xdbc.out_dma + XDBC_MAX_PACKET;
पूर्ण

अटल व्योम xdbc_करो_reset_debug_port(u32 id, u32 count)
अणु
	व्योम __iomem *ops_reg;
	व्योम __iomem *portsc;
	u32 val, cap_length;
	पूर्णांक i;

	cap_length = पढ़ोl(xdbc.xhci_base) & 0xff;
	ops_reg = xdbc.xhci_base + cap_length;

	id--;
	क्रम (i = id; i < (id + count); i++) अणु
		portsc = ops_reg + 0x400 + i * 0x10;
		val = पढ़ोl(portsc);
		अगर (!(val & PORT_CONNECT))
			ग_लिखोl(val | PORT_RESET, portsc);
	पूर्ण
पूर्ण

अटल व्योम xdbc_reset_debug_port(व्योम)
अणु
	u32 val, port_offset, port_count;
	पूर्णांक offset = 0;

	करो अणु
		offset = xhci_find_next_ext_cap(xdbc.xhci_base, offset, XHCI_EXT_CAPS_PROTOCOL);
		अगर (!offset)
			अवरोध;

		val = पढ़ोl(xdbc.xhci_base + offset);
		अगर (XHCI_EXT_PORT_MAJOR(val) != 0x3)
			जारी;

		val = पढ़ोl(xdbc.xhci_base + offset + 8);
		port_offset = XHCI_EXT_PORT_OFF(val);
		port_count = XHCI_EXT_PORT_COUNT(val);

		xdbc_करो_reset_debug_port(port_offset, port_count);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम
xdbc_queue_trb(काष्ठा xdbc_ring *ring, u32 field1, u32 field2, u32 field3, u32 field4)
अणु
	काष्ठा xdbc_trb *trb, *link_trb;

	trb = ring->enqueue;
	trb->field[0] = cpu_to_le32(field1);
	trb->field[1] = cpu_to_le32(field2);
	trb->field[2] = cpu_to_le32(field3);
	trb->field[3] = cpu_to_le32(field4);

	++(ring->enqueue);
	अगर (ring->enqueue >= &ring->segment->trbs[TRBS_PER_SEGMENT - 1]) अणु
		link_trb = ring->enqueue;
		अगर (ring->cycle_state)
			link_trb->field[3] |= cpu_to_le32(TRB_CYCLE);
		अन्यथा
			link_trb->field[3] &= cpu_to_le32(~TRB_CYCLE);

		ring->enqueue = ring->segment->trbs;
		ring->cycle_state ^= 1;
	पूर्ण
पूर्ण

अटल व्योम xdbc_ring_करोorbell(पूर्णांक target)
अणु
	ग_लिखोl(DOOR_BELL_TARGET(target), &xdbc.xdbc_reg->करोorbell);
पूर्ण

अटल पूर्णांक xdbc_start(व्योम)
अणु
	u32 ctrl, status;
	पूर्णांक ret;

	ctrl = पढ़ोl(&xdbc.xdbc_reg->control);
	ग_लिखोl(ctrl | CTRL_DBC_ENABLE | CTRL_PORT_ENABLE, &xdbc.xdbc_reg->control);
	ret = handshake(&xdbc.xdbc_reg->control, CTRL_DBC_ENABLE, CTRL_DBC_ENABLE, 100000, 100);
	अगर (ret) अणु
		xdbc_trace("failed to initialize hardware\n");
		वापस ret;
	पूर्ण

	/* Reset port to aव्योम bus hang: */
	अगर (xdbc.venकरोr == PCI_VENDOR_ID_INTEL)
		xdbc_reset_debug_port();

	/* Wait क्रम port connection: */
	ret = handshake(&xdbc.xdbc_reg->portsc, PORTSC_CONN_STATUS, PORTSC_CONN_STATUS, 5000000, 100);
	अगर (ret) अणु
		xdbc_trace("waiting for connection timed out\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम debug device to be configured: */
	ret = handshake(&xdbc.xdbc_reg->control, CTRL_DBC_RUN, CTRL_DBC_RUN, 5000000, 100);
	अगर (ret) अणु
		xdbc_trace("waiting for device configuration timed out\n");
		वापस ret;
	पूर्ण

	/* Check port number: */
	status = पढ़ोl(&xdbc.xdbc_reg->status);
	अगर (!DCST_DEBUG_PORT(status)) अणु
		xdbc_trace("invalid root hub port number\n");
		वापस -ENODEV;
	पूर्ण

	xdbc.port_number = DCST_DEBUG_PORT(status);

	xdbc_trace("DbC is running now, control 0x%08x port ID %d\n",
		   पढ़ोl(&xdbc.xdbc_reg->control), xdbc.port_number);

	वापस 0;
पूर्ण

अटल पूर्णांक xdbc_bulk_transfer(व्योम *data, पूर्णांक size, bool पढ़ो)
अणु
	काष्ठा xdbc_ring *ring;
	काष्ठा xdbc_trb *trb;
	u32 length, control;
	u32 cycle;
	u64 addr;

	अगर (size > XDBC_MAX_PACKET) अणु
		xdbc_trace("bad parameter, size %d\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर (!(xdbc.flags & XDBC_FLAGS_INITIALIZED) ||
	    !(xdbc.flags & XDBC_FLAGS_CONFIGURED) ||
	    (!पढ़ो && (xdbc.flags & XDBC_FLAGS_OUT_STALL)) ||
	    (पढ़ो && (xdbc.flags & XDBC_FLAGS_IN_STALL))) अणु

		xdbc_trace("connection not ready, flags %08x\n", xdbc.flags);
		वापस -EIO;
	पूर्ण

	ring = (पढ़ो ? &xdbc.in_ring : &xdbc.out_ring);
	trb = ring->enqueue;
	cycle = ring->cycle_state;
	length = TRB_LEN(size);
	control = TRB_TYPE(TRB_NORMAL) | TRB_IOC;

	अगर (cycle)
		control &= cpu_to_le32(~TRB_CYCLE);
	अन्यथा
		control |= cpu_to_le32(TRB_CYCLE);

	अगर (पढ़ो) अणु
		स_रखो(xdbc.in_buf, 0, XDBC_MAX_PACKET);
		addr = xdbc.in_dma;
		xdbc.flags |= XDBC_FLAGS_IN_PROCESS;
	पूर्ण अन्यथा अणु
		स_रखो(xdbc.out_buf, 0, XDBC_MAX_PACKET);
		स_नकल(xdbc.out_buf, data, size);
		addr = xdbc.out_dma;
		xdbc.flags |= XDBC_FLAGS_OUT_PROCESS;
	पूर्ण

	xdbc_queue_trb(ring, lower_32_bits(addr), upper_32_bits(addr), length, control);

	/*
	 * Add a barrier between ग_लिखोs of trb fields and flipping
	 * the cycle bit:
	 */
	wmb();
	अगर (cycle)
		trb->field[3] |= cpu_to_le32(cycle);
	अन्यथा
		trb->field[3] &= cpu_to_le32(~TRB_CYCLE);

	xdbc_ring_करोorbell(पढ़ो ? IN_EP_DOORBELL : OUT_EP_DOORBELL);

	वापस size;
पूर्ण

अटल पूर्णांक xdbc_handle_बाह्यal_reset(व्योम)
अणु
	पूर्णांक ret = 0;

	xdbc.flags = 0;
	ग_लिखोl(0, &xdbc.xdbc_reg->control);
	ret = handshake(&xdbc.xdbc_reg->control, CTRL_DBC_ENABLE, 0, 100000, 10);
	अगर (ret)
		जाओ reset_out;

	xdbc_mem_init();

	ret = xdbc_start();
	अगर (ret < 0)
		जाओ reset_out;

	xdbc_trace("dbc recovered\n");

	xdbc.flags |= XDBC_FLAGS_INITIALIZED | XDBC_FLAGS_CONFIGURED;

	xdbc_bulk_transfer(शून्य, XDBC_MAX_PACKET, true);

	वापस 0;

reset_out:
	xdbc_trace("failed to recover from external reset\n");
	वापस ret;
पूर्ण

अटल पूर्णांक __init xdbc_early_setup(व्योम)
अणु
	पूर्णांक ret;

	ग_लिखोl(0, &xdbc.xdbc_reg->control);
	ret = handshake(&xdbc.xdbc_reg->control, CTRL_DBC_ENABLE, 0, 100000, 100);
	अगर (ret)
		वापस ret;

	/* Allocate the table page: */
	xdbc.table_base = xdbc_get_page(&xdbc.table_dma);
	अगर (!xdbc.table_base)
		वापस -ENOMEM;

	/* Get and store the transfer buffer: */
	xdbc.out_buf = xdbc_get_page(&xdbc.out_dma);
	अगर (!xdbc.out_buf)
		वापस -ENOMEM;

	/* Allocate the event ring: */
	ret = xdbc_alloc_ring(&xdbc.evt_seg, &xdbc.evt_ring);
	अगर (ret < 0)
		वापस ret;

	/* Allocate IN/OUT endpoपूर्णांक transfer rings: */
	ret = xdbc_alloc_ring(&xdbc.in_seg, &xdbc.in_ring);
	अगर (ret < 0)
		वापस ret;

	ret = xdbc_alloc_ring(&xdbc.out_seg, &xdbc.out_ring);
	अगर (ret < 0)
		वापस ret;

	xdbc_mem_init();

	ret = xdbc_start();
	अगर (ret < 0) अणु
		ग_लिखोl(0, &xdbc.xdbc_reg->control);
		वापस ret;
	पूर्ण

	xdbc.flags |= XDBC_FLAGS_INITIALIZED | XDBC_FLAGS_CONFIGURED;

	xdbc_bulk_transfer(शून्य, XDBC_MAX_PACKET, true);

	वापस 0;
पूर्ण

पूर्णांक __init early_xdbc_parse_parameter(अक्षर *s)
अणु
	अचिन्हित दीर्घ dbgp_num = 0;
	u32 bus, dev, func, offset;
	पूर्णांक ret;

	अगर (!early_pci_allowed())
		वापस -EPERM;

	अगर (म_माला(s, "keep"))
		early_console_keep = true;

	अगर (xdbc.xdbc_reg)
		वापस 0;

	अगर (*s && kम_से_अदीर्घ(s, 0, &dbgp_num))
		dbgp_num = 0;

	pr_notice("dbgp_num: %lu\n", dbgp_num);

	/* Locate the host controller: */
	ret = xdbc_find_dbgp(dbgp_num, &bus, &dev, &func);
	अगर (ret) अणु
		pr_notice("failed to locate xhci host\n");
		वापस -ENODEV;
	पूर्ण

	xdbc.venकरोr	= पढ़ो_pci_config_16(bus, dev, func, PCI_VENDOR_ID);
	xdbc.device	= पढ़ो_pci_config_16(bus, dev, func, PCI_DEVICE_ID);
	xdbc.bus	= bus;
	xdbc.dev	= dev;
	xdbc.func	= func;

	/* Map the IO memory: */
	xdbc.xhci_base = xdbc_map_pci_mmio(bus, dev, func);
	अगर (!xdbc.xhci_base)
		वापस -EINVAL;

	/* Locate DbC रेजिस्टरs: */
	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_DEBUG);
	अगर (!offset) अणु
		pr_notice("xhci host doesn't support debug capability\n");
		early_iounmap(xdbc.xhci_base, xdbc.xhci_length);
		xdbc.xhci_base = शून्य;
		xdbc.xhci_length = 0;

		वापस -ENODEV;
	पूर्ण
	xdbc.xdbc_reg = (काष्ठा xdbc_regs __iomem *)(xdbc.xhci_base + offset);

	वापस 0;
पूर्ण

पूर्णांक __init early_xdbc_setup_hardware(व्योम)
अणु
	पूर्णांक ret;

	अगर (!xdbc.xdbc_reg)
		वापस -ENODEV;

	xdbc_bios_hanकरोff();

	raw_spin_lock_init(&xdbc.lock);

	ret = xdbc_early_setup();
	अगर (ret) अणु
		pr_notice("failed to setup the connection to host\n");

		xdbc_मुक्त_ring(&xdbc.evt_ring);
		xdbc_मुक्त_ring(&xdbc.out_ring);
		xdbc_मुक्त_ring(&xdbc.in_ring);

		अगर (xdbc.table_dma)
			memblock_मुक्त(xdbc.table_dma, PAGE_SIZE);

		अगर (xdbc.out_dma)
			memblock_मुक्त(xdbc.out_dma, PAGE_SIZE);

		xdbc.table_base = शून्य;
		xdbc.out_buf = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xdbc_handle_port_status(काष्ठा xdbc_trb *evt_trb)
अणु
	u32 port_reg;

	port_reg = पढ़ोl(&xdbc.xdbc_reg->portsc);
	अगर (port_reg & PORTSC_CONN_CHANGE) अणु
		xdbc_trace("connect status change event\n");

		/* Check whether cable unplugged: */
		अगर (!(port_reg & PORTSC_CONN_STATUS)) अणु
			xdbc.flags = 0;
			xdbc_trace("cable unplugged\n");
		पूर्ण
	पूर्ण

	अगर (port_reg & PORTSC_RESET_CHANGE)
		xdbc_trace("port reset change event\n");

	अगर (port_reg & PORTSC_LINK_CHANGE)
		xdbc_trace("port link status change event\n");

	अगर (port_reg & PORTSC_CONFIG_CHANGE)
		xdbc_trace("config error change\n");

	/* Write back the value to clear RW1C bits: */
	ग_लिखोl(port_reg, &xdbc.xdbc_reg->portsc);
पूर्ण

अटल व्योम xdbc_handle_tx_event(काष्ठा xdbc_trb *evt_trb)
अणु
	u32 comp_code;
	पूर्णांक ep_id;

	comp_code	= GET_COMP_CODE(le32_to_cpu(evt_trb->field[2]));
	ep_id		= TRB_TO_EP_ID(le32_to_cpu(evt_trb->field[3]));

	चयन (comp_code) अणु
	हाल COMP_SUCCESS:
	हाल COMP_SHORT_PACKET:
		अवरोध;
	हाल COMP_TRB_ERROR:
	हाल COMP_BABBLE_DETECTED_ERROR:
	हाल COMP_USB_TRANSACTION_ERROR:
	हाल COMP_STALL_ERROR:
	शेष:
		अगर (ep_id == XDBC_EPID_OUT || ep_id == XDBC_EPID_OUT_INTEL)
			xdbc.flags |= XDBC_FLAGS_OUT_STALL;
		अगर (ep_id == XDBC_EPID_IN || ep_id == XDBC_EPID_IN_INTEL)
			xdbc.flags |= XDBC_FLAGS_IN_STALL;

		xdbc_trace("endpoint %d stalled\n", ep_id);
		अवरोध;
	पूर्ण

	अगर (ep_id == XDBC_EPID_IN || ep_id == XDBC_EPID_IN_INTEL) अणु
		xdbc.flags &= ~XDBC_FLAGS_IN_PROCESS;
		xdbc_bulk_transfer(शून्य, XDBC_MAX_PACKET, true);
	पूर्ण अन्यथा अगर (ep_id == XDBC_EPID_OUT || ep_id == XDBC_EPID_OUT_INTEL) अणु
		xdbc.flags &= ~XDBC_FLAGS_OUT_PROCESS;
	पूर्ण अन्यथा अणु
		xdbc_trace("invalid endpoint id %d\n", ep_id);
	पूर्ण
पूर्ण

अटल व्योम xdbc_handle_events(व्योम)
अणु
	काष्ठा xdbc_trb *evt_trb;
	bool update_erdp = false;
	u32 reg;
	u8 cmd;

	cmd = पढ़ो_pci_config_byte(xdbc.bus, xdbc.dev, xdbc.func, PCI_COMMAND);
	अगर (!(cmd & PCI_COMMAND_MASTER)) अणु
		cmd |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
		ग_लिखो_pci_config_byte(xdbc.bus, xdbc.dev, xdbc.func, PCI_COMMAND, cmd);
	पूर्ण

	अगर (!(xdbc.flags & XDBC_FLAGS_INITIALIZED))
		वापस;

	/* Handle बाह्यal reset events: */
	reg = पढ़ोl(&xdbc.xdbc_reg->control);
	अगर (!(reg & CTRL_DBC_ENABLE)) अणु
		अगर (xdbc_handle_बाह्यal_reset()) अणु
			xdbc_trace("failed to recover connection\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Handle configure-निकास event: */
	reg = पढ़ोl(&xdbc.xdbc_reg->control);
	अगर (reg & CTRL_DBC_RUN_CHANGE) अणु
		ग_लिखोl(reg, &xdbc.xdbc_reg->control);
		अगर (reg & CTRL_DBC_RUN)
			xdbc.flags |= XDBC_FLAGS_CONFIGURED;
		अन्यथा
			xdbc.flags &= ~XDBC_FLAGS_CONFIGURED;
	पूर्ण

	/* Handle endpoपूर्णांक stall event: */
	reg = पढ़ोl(&xdbc.xdbc_reg->control);
	अगर (reg & CTRL_HALT_IN_TR) अणु
		xdbc.flags |= XDBC_FLAGS_IN_STALL;
	पूर्ण अन्यथा अणु
		xdbc.flags &= ~XDBC_FLAGS_IN_STALL;
		अगर (!(xdbc.flags & XDBC_FLAGS_IN_PROCESS))
			xdbc_bulk_transfer(शून्य, XDBC_MAX_PACKET, true);
	पूर्ण

	अगर (reg & CTRL_HALT_OUT_TR)
		xdbc.flags |= XDBC_FLAGS_OUT_STALL;
	अन्यथा
		xdbc.flags &= ~XDBC_FLAGS_OUT_STALL;

	/* Handle the events in the event ring: */
	evt_trb = xdbc.evt_ring.dequeue;
	जबतक ((le32_to_cpu(evt_trb->field[3]) & TRB_CYCLE) == xdbc.evt_ring.cycle_state) अणु
		/*
		 * Add a barrier between पढ़ोing the cycle flag and any
		 * पढ़ोs of the event's flags/data below:
		 */
		rmb();

		चयन ((le32_to_cpu(evt_trb->field[3]) & TRB_TYPE_BITMASK)) अणु
		हाल TRB_TYPE(TRB_PORT_STATUS):
			xdbc_handle_port_status(evt_trb);
			अवरोध;
		हाल TRB_TYPE(TRB_TRANSFER):
			xdbc_handle_tx_event(evt_trb);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		++(xdbc.evt_ring.dequeue);
		अगर (xdbc.evt_ring.dequeue == &xdbc.evt_seg.trbs[TRBS_PER_SEGMENT]) अणु
			xdbc.evt_ring.dequeue = xdbc.evt_seg.trbs;
			xdbc.evt_ring.cycle_state ^= 1;
		पूर्ण

		evt_trb = xdbc.evt_ring.dequeue;
		update_erdp = true;
	पूर्ण

	/* Update event ring dequeue poपूर्णांकer: */
	अगर (update_erdp)
		xdbc_ग_लिखो64(__pa(xdbc.evt_ring.dequeue), &xdbc.xdbc_reg->erdp);
पूर्ण

अटल पूर्णांक xdbc_bulk_ग_लिखो(स्थिर अक्षर *bytes, पूर्णांक size)
अणु
	पूर्णांक ret, समयout = 0;
	अचिन्हित दीर्घ flags;

retry:
	अगर (in_nmi()) अणु
		अगर (!raw_spin_trylock_irqsave(&xdbc.lock, flags))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		raw_spin_lock_irqsave(&xdbc.lock, flags);
	पूर्ण

	xdbc_handle_events();

	/* Check completion of the previous request: */
	अगर ((xdbc.flags & XDBC_FLAGS_OUT_PROCESS) && (समयout < 2000000)) अणु
		raw_spin_unlock_irqrestore(&xdbc.lock, flags);
		udelay(100);
		समयout += 100;
		जाओ retry;
	पूर्ण

	अगर (xdbc.flags & XDBC_FLAGS_OUT_PROCESS) अणु
		raw_spin_unlock_irqrestore(&xdbc.lock, flags);
		xdbc_trace("previous transfer not completed yet\n");

		वापस -ETIMEDOUT;
	पूर्ण

	ret = xdbc_bulk_transfer((व्योम *)bytes, size, false);
	raw_spin_unlock_irqrestore(&xdbc.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम early_xdbc_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *str, u32 n)
अणु
	अटल अक्षर buf[XDBC_MAX_PACKET];
	पूर्णांक chunk, ret;
	पूर्णांक use_cr = 0;

	अगर (!xdbc.xdbc_reg)
		वापस;
	स_रखो(buf, 0, XDBC_MAX_PACKET);
	जबतक (n > 0) अणु
		क्रम (chunk = 0; chunk < XDBC_MAX_PACKET && n > 0; str++, chunk++, n--) अणु

			अगर (!use_cr && *str == '\n') अणु
				use_cr = 1;
				buf[chunk] = '\r';
				str--;
				n++;
				जारी;
			पूर्ण

			अगर (use_cr)
				use_cr = 0;
			buf[chunk] = *str;
		पूर्ण

		अगर (chunk > 0) अणु
			ret = xdbc_bulk_ग_लिखो(buf, chunk);
			अगर (ret < 0)
				xdbc_trace("missed message {%s}\n", buf);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा console early_xdbc_console = अणु
	.name		= "earlyxdbc",
	.ग_लिखो		= early_xdbc_ग_लिखो,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

व्योम __init early_xdbc_रेजिस्टर_console(व्योम)
अणु
	अगर (early_console)
		वापस;

	early_console = &early_xdbc_console;
	अगर (early_console_keep)
		early_console->flags &= ~CON_BOOT;
	अन्यथा
		early_console->flags |= CON_BOOT;
	रेजिस्टर_console(early_console);
पूर्ण

अटल व्योम xdbc_unरेजिस्टर_console(व्योम)
अणु
	अगर (early_xdbc_console.flags & CON_ENABLED)
		unरेजिस्टर_console(&early_xdbc_console);
पूर्ण

अटल पूर्णांक xdbc_scrub_function(व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;

	जबतक (true) अणु
		raw_spin_lock_irqsave(&xdbc.lock, flags);
		xdbc_handle_events();

		अगर (!(xdbc.flags & XDBC_FLAGS_INITIALIZED)) अणु
			raw_spin_unlock_irqrestore(&xdbc.lock, flags);
			अवरोध;
		पूर्ण

		raw_spin_unlock_irqrestore(&xdbc.lock, flags);
		schedule_समयout_पूर्णांकerruptible(1);
	पूर्ण

	xdbc_unरेजिस्टर_console();
	ग_लिखोl(0, &xdbc.xdbc_reg->control);
	xdbc_trace("dbc scrub function exits\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __init xdbc_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base;
	पूर्णांक ret = 0;
	u32 offset;

	अगर (!(xdbc.flags & XDBC_FLAGS_INITIALIZED))
		वापस 0;

	/*
	 * It's समय to shut करोwn the DbC, so that the debug
	 * port can be reused by the host controller:
	 */
	अगर (early_xdbc_console.index == -1 ||
	    (early_xdbc_console.flags & CON_BOOT)) अणु
		xdbc_trace("hardware not used anymore\n");
		जाओ मुक्त_and_quit;
	पूर्ण

	base = ioremap(xdbc.xhci_start, xdbc.xhci_length);
	अगर (!base) अणु
		xdbc_trace("failed to remap the io address\n");
		ret = -ENOMEM;
		जाओ मुक्त_and_quit;
	पूर्ण

	raw_spin_lock_irqsave(&xdbc.lock, flags);
	early_iounmap(xdbc.xhci_base, xdbc.xhci_length);
	xdbc.xhci_base = base;
	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_DEBUG);
	xdbc.xdbc_reg = (काष्ठा xdbc_regs __iomem *)(xdbc.xhci_base + offset);
	raw_spin_unlock_irqrestore(&xdbc.lock, flags);

	kthपढ़ो_run(xdbc_scrub_function, शून्य, "%s", "xdbc");

	वापस 0;

मुक्त_and_quit:
	xdbc_मुक्त_ring(&xdbc.evt_ring);
	xdbc_मुक्त_ring(&xdbc.out_ring);
	xdbc_मुक्त_ring(&xdbc.in_ring);
	memblock_मुक्त(xdbc.table_dma, PAGE_SIZE);
	memblock_मुक्त(xdbc.out_dma, PAGE_SIZE);
	ग_लिखोl(0, &xdbc.xdbc_reg->control);
	early_iounmap(xdbc.xhci_base, xdbc.xhci_length);

	वापस ret;
पूर्ण
subsys_initcall(xdbc_init);
