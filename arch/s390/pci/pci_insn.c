<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * s390 specअगरic pci inकाष्ठाions
 *
 * Copyright IBM Corp. 2013
 */

#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/pci_insn.h>
#समावेश <यंत्र/pci_debug.h>
#समावेश <यंत्र/pci_पन.स>
#समावेश <यंत्र/processor.h>

#घोषणा ZPCI_INSN_BUSY_DELAY	1	/* 1 microsecond */

अटल अंतरभूत व्योम zpci_err_insn(u8 cc, u8 status, u64 req, u64 offset)
अणु
	काष्ठा अणु
		u64 req;
		u64 offset;
		u8 cc;
		u8 status;
	पूर्ण __packed data = अणुreq, offset, cc, statusपूर्ण;

	zpci_err_hex(&data, माप(data));
पूर्ण

/* Modअगरy PCI Function Controls */
अटल अंतरभूत u8 __mpcअगरc(u64 req, काष्ठा zpci_fib *fib, u8 *status)
अणु
	u8 cc;

	यंत्र अस्थिर (
		"	.insn	rxy,0xe300000000d0,%[req],%[fib]\n"
		"	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		: [cc] "=d" (cc), [req] "+d" (req), [fib] "+Q" (*fib)
		: : "cc");
	*status = req >> 24 & 0xff;
	वापस cc;
पूर्ण

u8 zpci_mod_fc(u64 req, काष्ठा zpci_fib *fib, u8 *status)
अणु
	u8 cc;

	करो अणु
		cc = __mpcअगरc(req, fib, status);
		अगर (cc == 2)
			msleep(ZPCI_INSN_BUSY_DELAY);
	पूर्ण जबतक (cc == 2);

	अगर (cc)
		zpci_err_insn(cc, *status, req, 0);

	वापस cc;
पूर्ण

/* Refresh PCI Translations */
अटल अंतरभूत u8 __rpcit(u64 fn, u64 addr, u64 range, u8 *status)
अणु
	रेजिस्टर u64 __addr यंत्र("2") = addr;
	रेजिस्टर u64 __range यंत्र("3") = range;
	u8 cc;

	यंत्र अस्थिर (
		"	.insn	rre,0xb9d30000,%[fn],%[addr]\n"
		"	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		: [cc] "=d" (cc), [fn] "+d" (fn)
		: [addr] "d" (__addr), "d" (__range)
		: "cc");
	*status = fn >> 24 & 0xff;
	वापस cc;
पूर्ण

पूर्णांक zpci_refresh_trans(u64 fn, u64 addr, u64 range)
अणु
	u8 cc, status;

	करो अणु
		cc = __rpcit(fn, addr, range, &status);
		अगर (cc == 2)
			udelay(ZPCI_INSN_BUSY_DELAY);
	पूर्ण जबतक (cc == 2);

	अगर (cc)
		zpci_err_insn(cc, status, addr, range);

	अगर (cc == 1 && (status == 4 || status == 16))
		वापस -ENOMEM;

	वापस (cc) ? -EIO : 0;
पूर्ण

/* Set Interruption Controls */
पूर्णांक __zpci_set_irq_ctrl(u16 ctl, u8 isc, जोड़ zpci_sic_iib *iib)
अणु
	अगर (!test_facility(72))
		वापस -EIO;

	यंत्र अस्थिर(
		".insn	rsy,0xeb00000000d1,%[ctl],%[isc],%[iib]\n"
		: : [ctl] "d" (ctl), [isc] "d" (isc << 27), [iib] "Q" (*iib));

	वापस 0;
पूर्ण

/* PCI Load */
अटल अंतरभूत पूर्णांक ____pcilg(u64 *data, u64 req, u64 offset, u8 *status)
अणु
	रेजिस्टर u64 __req यंत्र("2") = req;
	रेजिस्टर u64 __offset यंत्र("3") = offset;
	पूर्णांक cc = -ENXIO;
	u64 __data;

	यंत्र अस्थिर (
		"	.insn	rre,0xb9d20000,%[data],%[req]\n"
		"0:	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [data] "=d" (__data), [req] "+d" (__req)
		:  "d" (__offset)
		: "cc");
	*status = __req >> 24 & 0xff;
	*data = __data;
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक __pcilg(u64 *data, u64 req, u64 offset, u8 *status)
अणु
	u64 __data;
	पूर्णांक cc;

	cc = ____pcilg(&__data, req, offset, status);
	अगर (!cc)
		*data = __data;

	वापस cc;
पूर्ण

पूर्णांक __zpci_load(u64 *data, u64 req, u64 offset)
अणु
	u8 status;
	पूर्णांक cc;

	करो अणु
		cc = __pcilg(data, req, offset, &status);
		अगर (cc == 2)
			udelay(ZPCI_INSN_BUSY_DELAY);
	पूर्ण जबतक (cc == 2);

	अगर (cc)
		zpci_err_insn(cc, status, req, offset);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(__zpci_load);

अटल अंतरभूत पूर्णांक zpci_load_fh(u64 *data, स्थिर अस्थिर व्योम __iomem *addr,
			       अचिन्हित दीर्घ len)
अणु
	काष्ठा zpci_iomap_entry *entry = &zpci_iomap_start[ZPCI_IDX(addr)];
	u64 req = ZPCI_CREATE_REQ(entry->fh, entry->bar, len);

	वापस __zpci_load(data, req, ZPCI_OFFSET(addr));
पूर्ण

अटल अंतरभूत पूर्णांक __pcilg_mio(u64 *data, u64 ioaddr, u64 len, u8 *status)
अणु
	रेजिस्टर u64 addr यंत्र("2") = ioaddr;
	रेजिस्टर u64 r3 यंत्र("3") = len;
	पूर्णांक cc = -ENXIO;
	u64 __data;

	यंत्र अस्थिर (
		"       .insn   rre,0xb9d60000,%[data],%[ioaddr]\n"
		"0:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [data] "=d" (__data), "+d" (r3)
		: [ioaddr] "d" (addr)
		: "cc");
	*status = r3 >> 24 & 0xff;
	*data = __data;
	वापस cc;
पूर्ण

पूर्णांक zpci_load(u64 *data, स्थिर अस्थिर व्योम __iomem *addr, अचिन्हित दीर्घ len)
अणु
	u8 status;
	पूर्णांक cc;

	अगर (!अटल_branch_unlikely(&have_mio))
		वापस zpci_load_fh(data, addr, len);

	cc = __pcilg_mio(data, (__क्रमce u64) addr, len, &status);
	अगर (cc)
		zpci_err_insn(cc, status, 0, (__क्रमce u64) addr);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(zpci_load);

/* PCI Store */
अटल अंतरभूत पूर्णांक __pcistg(u64 data, u64 req, u64 offset, u8 *status)
अणु
	रेजिस्टर u64 __req यंत्र("2") = req;
	रेजिस्टर u64 __offset यंत्र("3") = offset;
	पूर्णांक cc = -ENXIO;

	यंत्र अस्थिर (
		"	.insn	rre,0xb9d00000,%[data],%[req]\n"
		"0:	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [req] "+d" (__req)
		: "d" (__offset), [data] "d" (data)
		: "cc");
	*status = __req >> 24 & 0xff;
	वापस cc;
पूर्ण

पूर्णांक __zpci_store(u64 data, u64 req, u64 offset)
अणु
	u8 status;
	पूर्णांक cc;

	करो अणु
		cc = __pcistg(data, req, offset, &status);
		अगर (cc == 2)
			udelay(ZPCI_INSN_BUSY_DELAY);
	पूर्ण जबतक (cc == 2);

	अगर (cc)
		zpci_err_insn(cc, status, req, offset);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(__zpci_store);

अटल अंतरभूत पूर्णांक zpci_store_fh(स्थिर अस्थिर व्योम __iomem *addr, u64 data,
				अचिन्हित दीर्घ len)
अणु
	काष्ठा zpci_iomap_entry *entry = &zpci_iomap_start[ZPCI_IDX(addr)];
	u64 req = ZPCI_CREATE_REQ(entry->fh, entry->bar, len);

	वापस __zpci_store(data, req, ZPCI_OFFSET(addr));
पूर्ण

अटल अंतरभूत पूर्णांक __pcistg_mio(u64 data, u64 ioaddr, u64 len, u8 *status)
अणु
	रेजिस्टर u64 addr यंत्र("2") = ioaddr;
	रेजिस्टर u64 r3 यंत्र("3") = len;
	पूर्णांक cc = -ENXIO;

	यंत्र अस्थिर (
		"       .insn   rre,0xb9d40000,%[data],%[ioaddr]\n"
		"0:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), "+d" (r3)
		: [data] "d" (data), [ioaddr] "d" (addr)
		: "cc");
	*status = r3 >> 24 & 0xff;
	वापस cc;
पूर्ण

पूर्णांक zpci_store(स्थिर अस्थिर व्योम __iomem *addr, u64 data, अचिन्हित दीर्घ len)
अणु
	u8 status;
	पूर्णांक cc;

	अगर (!अटल_branch_unlikely(&have_mio))
		वापस zpci_store_fh(addr, data, len);

	cc = __pcistg_mio(data, (__क्रमce u64) addr, len, &status);
	अगर (cc)
		zpci_err_insn(cc, status, 0, (__क्रमce u64) addr);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(zpci_store);

/* PCI Store Block */
अटल अंतरभूत पूर्णांक __pcistb(स्थिर u64 *data, u64 req, u64 offset, u8 *status)
अणु
	पूर्णांक cc = -ENXIO;

	यंत्र अस्थिर (
		"	.insn	rsy,0xeb00000000d0,%[req],%[offset],%[data]\n"
		"0:	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [req] "+d" (req)
		: [offset] "d" (offset), [data] "Q" (*data)
		: "cc");
	*status = req >> 24 & 0xff;
	वापस cc;
पूर्ण

पूर्णांक __zpci_store_block(स्थिर u64 *data, u64 req, u64 offset)
अणु
	u8 status;
	पूर्णांक cc;

	करो अणु
		cc = __pcistb(data, req, offset, &status);
		अगर (cc == 2)
			udelay(ZPCI_INSN_BUSY_DELAY);
	पूर्ण जबतक (cc == 2);

	अगर (cc)
		zpci_err_insn(cc, status, req, offset);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(__zpci_store_block);

अटल अंतरभूत पूर्णांक zpci_ग_लिखो_block_fh(अस्थिर व्योम __iomem *dst,
				      स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	काष्ठा zpci_iomap_entry *entry = &zpci_iomap_start[ZPCI_IDX(dst)];
	u64 req = ZPCI_CREATE_REQ(entry->fh, entry->bar, len);
	u64 offset = ZPCI_OFFSET(dst);

	वापस __zpci_store_block(src, req, offset);
पूर्ण

अटल अंतरभूत पूर्णांक __pcistb_mio(स्थिर u64 *data, u64 ioaddr, u64 len, u8 *status)
अणु
	पूर्णांक cc = -ENXIO;

	यंत्र अस्थिर (
		"       .insn   rsy,0xeb00000000d4,%[len],%[ioaddr],%[data]\n"
		"0:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: [cc] "+d" (cc), [len] "+d" (len)
		: [ioaddr] "d" (ioaddr), [data] "Q" (*data)
		: "cc");
	*status = len >> 24 & 0xff;
	वापस cc;
पूर्ण

पूर्णांक zpci_ग_लिखो_block(अस्थिर व्योम __iomem *dst,
		     स्थिर व्योम *src, अचिन्हित दीर्घ len)
अणु
	u8 status;
	पूर्णांक cc;

	अगर (!अटल_branch_unlikely(&have_mio))
		वापस zpci_ग_लिखो_block_fh(dst, src, len);

	cc = __pcistb_mio(src, (__क्रमce u64) dst, len, &status);
	अगर (cc)
		zpci_err_insn(cc, status, 0, (__क्रमce u64) dst);

	वापस (cc > 0) ? -EIO : cc;
पूर्ण
EXPORT_SYMBOL_GPL(zpci_ग_लिखो_block);

अटल अंतरभूत व्योम __pciwb_mio(व्योम)
अणु
	अचिन्हित दीर्घ unused = 0;

	यंत्र अस्थिर (".insn    rre,0xb9d50000,%[op],%[op]\n"
		      : [op] "+d" (unused));
पूर्ण

व्योम zpci_barrier(व्योम)
अणु
	अगर (अटल_branch_likely(&have_mio))
		__pciwb_mio();
पूर्ण
EXPORT_SYMBOL_GPL(zpci_barrier);
