<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2007
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Christian Borntraeger (cborntra@de.ibm.com),
 */

#घोषणा KMSG_COMPONENT "cpcmd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/पन.स>

अटल DEFINE_SPINLOCK(cpcmd_lock);
अटल अक्षर cpcmd_buf[241];

अटल पूर्णांक diag8_noresponse(पूर्णांक cmdlen)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2") = (addr_t) cpcmd_buf;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र ("3") = cmdlen;

	यंत्र अस्थिर(
		"	diag	%1,%0,0x8\n"
		: "+d" (reg3) : "d" (reg2) : "cc");
	वापस reg3;
पूर्ण

अटल पूर्णांक diag8_response(पूर्णांक cmdlen, अक्षर *response, पूर्णांक *rlen)
अणु
	अचिन्हित दीर्घ _cmdlen = cmdlen | 0x40000000L;
	अचिन्हित दीर्घ _rlen = *rlen;
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2") = (addr_t) cpcmd_buf;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र ("3") = (addr_t) response;
	रेजिस्टर अचिन्हित दीर्घ reg4 यंत्र ("4") = _cmdlen;
	रेजिस्टर अचिन्हित दीर्घ reg5 यंत्र ("5") = _rlen;

	यंत्र अस्थिर(
		"	diag	%2,%0,0x8\n"
		"	brc	8,1f\n"
		"	agr	%1,%4\n"
		"1:\n"
		: "+d" (reg4), "+d" (reg5)
		: "d" (reg2), "d" (reg3), "d" (*rlen) : "cc");
	*rlen = reg5;
	वापस reg4;
पूर्ण

/*
 * __cpcmd has some restrictions over cpcmd
 *  - __cpcmd is unlocked and thereक्रमe not SMP-safe
 */
पूर्णांक  __cpcmd(स्थिर अक्षर *cmd, अक्षर *response, पूर्णांक rlen, पूर्णांक *response_code)
अणु
	पूर्णांक cmdlen;
	पूर्णांक rc;
	पूर्णांक response_len;

	cmdlen = म_माप(cmd);
	BUG_ON(cmdlen > 240);
	स_नकल(cpcmd_buf, cmd, cmdlen);
	ASCEBC(cpcmd_buf, cmdlen);

	diag_stat_inc(DIAG_STAT_X008);
	अगर (response) अणु
		स_रखो(response, 0, rlen);
		response_len = rlen;
		rc = diag8_response(cmdlen, response, &rlen);
		EBCASC(response, response_len);
        पूर्ण अन्यथा अणु
		rc = diag8_noresponse(cmdlen);
        पूर्ण
	अगर (response_code)
		*response_code = rc;
	वापस rlen;
पूर्ण
EXPORT_SYMBOL(__cpcmd);

पूर्णांक cpcmd(स्थिर अक्षर *cmd, अक्षर *response, पूर्णांक rlen, पूर्णांक *response_code)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *lowbuf;
	पूर्णांक len;

	अगर (is_vदो_स्मृति_or_module_addr(response)) अणु
		lowbuf = kदो_स्मृति(rlen, GFP_KERNEL);
		अगर (!lowbuf) अणु
			pr_warn("The cpcmd kernel function failed to allocate a response buffer\n");
			वापस -ENOMEM;
		पूर्ण
		spin_lock_irqsave(&cpcmd_lock, flags);
		len = __cpcmd(cmd, lowbuf, rlen, response_code);
		spin_unlock_irqrestore(&cpcmd_lock, flags);
		स_नकल(response, lowbuf, rlen);
		kमुक्त(lowbuf);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&cpcmd_lock, flags);
		len = __cpcmd(cmd, response, rlen, response_code);
		spin_unlock_irqrestore(&cpcmd_lock, flags);
	पूर्ण
	वापस len;
पूर्ण
EXPORT_SYMBOL(cpcmd);
