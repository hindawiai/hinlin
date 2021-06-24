<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पन.स>
#समावेश <linux/export.h>

/**
 *	check_signature		-	find BIOS signatures
 *	@io_addr: mmio address to check
 *	@signature:  signature block
 *	@length: length of signature
 *
 *	Perक्रमm a signature comparison with the mmio address io_addr. This
 *	address should have been obtained by ioremap.
 *	Returns 1 on a match.
 */

पूर्णांक check_signature(स्थिर अस्थिर व्योम __iomem *io_addr,
			स्थिर अचिन्हित अक्षर *signature, पूर्णांक length)
अणु
	जबतक (length--) अणु
		अगर (पढ़ोb(io_addr) != *signature)
			वापस 0;
		io_addr++;
		signature++;
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL(check_signature);
