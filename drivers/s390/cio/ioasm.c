<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Channel subप्रणाली I/O inकाष्ठाions.
 */

#समावेश <linux/export.h>

#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/crw.h>

#समावेश "ioasm.h"
#समावेश "orb.h"
#समावेश "cio.h"
#समावेश "cio_inject.h"

अटल अंतरभूत पूर्णांक __stsch(काष्ठा subchannel_id schid, काष्ठा schib *addr)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र ("1") = schid;
	पूर्णांक ccode = -EIO;

	यंत्र अस्थिर(
		"	stsch	0(%3)\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (ccode), "=m" (*addr)
		: "d" (reg1), "a" (addr)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक stsch(काष्ठा subchannel_id schid, काष्ठा schib *addr)
अणु
	पूर्णांक ccode;

	ccode = __stsch(schid, addr);
	trace_s390_cio_stsch(schid, addr, ccode);

	वापस ccode;
पूर्ण
EXPORT_SYMBOL(stsch);

अटल अंतरभूत पूर्णांक __msch(काष्ठा subchannel_id schid, काष्ठा schib *addr)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र ("1") = schid;
	पूर्णांक ccode = -EIO;

	यंत्र अस्थिर(
		"	msch	0(%2)\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (ccode)
		: "d" (reg1), "a" (addr), "m" (*addr)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक msch(काष्ठा subchannel_id schid, काष्ठा schib *addr)
अणु
	पूर्णांक ccode;

	ccode = __msch(schid, addr);
	trace_s390_cio_msch(schid, addr, ccode);

	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक __tsch(काष्ठा subchannel_id schid, काष्ठा irb *addr)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र ("1") = schid;
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	tsch	0(%3)\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode), "=m" (*addr)
		: "d" (reg1), "a" (addr)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक tsch(काष्ठा subchannel_id schid, काष्ठा irb *addr)
अणु
	पूर्णांक ccode;

	ccode = __tsch(schid, addr);
	trace_s390_cio_tsch(schid, addr, ccode);

	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक __ssch(काष्ठा subchannel_id schid, जोड़ orb *addr)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र("1") = schid;
	पूर्णांक ccode = -EIO;

	यंत्र अस्थिर(
		"	ssch	0(%2)\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (ccode)
		: "d" (reg1), "a" (addr), "m" (*addr)
		: "cc", "memory");
	वापस ccode;
पूर्ण

पूर्णांक ssch(काष्ठा subchannel_id schid, जोड़ orb *addr)
अणु
	पूर्णांक ccode;

	ccode = __ssch(schid, addr);
	trace_s390_cio_ssch(schid, addr, ccode);

	वापस ccode;
पूर्ण
EXPORT_SYMBOL(ssch);

अटल अंतरभूत पूर्णांक __csch(काष्ठा subchannel_id schid)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र("1") = schid;
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	csch\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode)
		: "d" (reg1)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक csch(काष्ठा subchannel_id schid)
अणु
	पूर्णांक ccode;

	ccode = __csch(schid);
	trace_s390_cio_csch(schid, ccode);

	वापस ccode;
पूर्ण
EXPORT_SYMBOL(csch);

पूर्णांक tpi(काष्ठा tpi_info *addr)
अणु
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	tpi	0(%2)\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode), "=m" (*addr)
		: "a" (addr)
		: "cc");
	trace_s390_cio_tpi(addr, ccode);

	वापस ccode;
पूर्ण

पूर्णांक chsc(व्योम *chsc_area)
अणु
	प्रकार काष्ठा अणु अक्षर _[4096]; पूर्ण addr_type;
	पूर्णांक cc = -EIO;

	यंत्र अस्थिर(
		"	.insn	rre,0xb25f0000,%2,0\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (cc), "=m" (*(addr_type *) chsc_area)
		: "d" (chsc_area), "m" (*(addr_type *) chsc_area)
		: "cc");
	trace_s390_cio_chsc(chsc_area, cc);

	वापस cc;
पूर्ण
EXPORT_SYMBOL(chsc);

अटल अंतरभूत पूर्णांक __rsch(काष्ठा subchannel_id schid)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र("1") = schid;
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	rsch\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode)
		: "d" (reg1)
		: "cc", "memory");

	वापस ccode;
पूर्ण

पूर्णांक rsch(काष्ठा subchannel_id schid)
अणु
	पूर्णांक ccode;

	ccode = __rsch(schid);
	trace_s390_cio_rsch(schid, ccode);

	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक __hsch(काष्ठा subchannel_id schid)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र("1") = schid;
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	hsch\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode)
		: "d" (reg1)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक hsch(काष्ठा subchannel_id schid)
अणु
	पूर्णांक ccode;

	ccode = __hsch(schid);
	trace_s390_cio_hsch(schid, ccode);

	वापस ccode;
पूर्ण
EXPORT_SYMBOL(hsch);

अटल अंतरभूत पूर्णांक __xsch(काष्ठा subchannel_id schid)
अणु
	रेजिस्टर काष्ठा subchannel_id reg1 यंत्र("1") = schid;
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	xsch\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode)
		: "d" (reg1)
		: "cc");
	वापस ccode;
पूर्ण

पूर्णांक xsch(काष्ठा subchannel_id schid)
अणु
	पूर्णांक ccode;

	ccode = __xsch(schid);
	trace_s390_cio_xsch(schid, ccode);

	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक __stcrw(काष्ठा crw *crw)
अणु
	पूर्णांक ccode;

	यंत्र अस्थिर(
		"	stcrw	0(%2)\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (ccode), "=m" (*crw)
		: "a" (crw)
		: "cc");
	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक _stcrw(काष्ठा crw *crw)
अणु
#अगर_घोषित CONFIG_CIO_INJECT
	अगर (अटल_branch_unlikely(&cio_inject_enabled)) अणु
		अगर (stcrw_get_injected(crw) == 0)
			वापस 0;
	पूर्ण
#पूर्ण_अगर

	वापस __stcrw(crw);
पूर्ण

पूर्णांक stcrw(काष्ठा crw *crw)
अणु
	पूर्णांक ccode;

	ccode = _stcrw(crw);
	trace_s390_cio_stcrw(crw, ccode);

	वापस ccode;
पूर्ण
