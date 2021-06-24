<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Tests क्रम presence or असलence of hardware रेजिस्टरs.
 * This code was originally in atari/config.c, but I noticed
 * that it was also in drivers/nubus/nubus.c and I wanted to
 * use it in hp300/config.c, so it seemed sensible to pull it
 * out पूर्णांकo its own file.
 *
 * The test is क्रम use when trying to पढ़ो a hardware रेजिस्टर
 * that isn't present would cause a bus error. We set up a
 * temporary handler so that this करोesn't समाप्त the kernel.
 *
 * There is a test-by-पढ़ोing and a test-by-writing; I present
 * them here complete with the comments from the original atari
 * config.c...
 *                -- PMM <pmaydell@chiark.greenend.org.uk>, 05/1998
 */

/* This function tests क्रम the presence of an address, specially a
 * hardware रेजिस्टर address. It is called very early in the kernel
 * initialization process, when the VBR रेजिस्टर isn't set up yet. On
 * an Atari, it still poपूर्णांकs to address 0, which is unmapped. So a bus
 * error would cause another bus error जबतक fetching the exception
 * vector, and the CPU would करो nothing at all. So we needed to set up
 * a temporary VBR and a vector table क्रम the duration of the test.
 */

#समावेश <linux/module.h>

पूर्णांक hwreg_present(अस्थिर व्योम *regp)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	दीर्घ save_sp, save_vbr;
	दीर्घ पंचांगp_vectors[3];

	local_irq_save(flags);
	__यंत्र__ __अस्थिर__ (
		"movec %/vbr,%2\n\t"
		"movel #Lberr1,%4@(8)\n\t"
		"movec %4,%/vbr\n\t"
		"movel %/sp,%1\n\t"
		"moveq #0,%0\n\t"
		"tstb %3@\n\t"
		"nop\n\t"
		"moveq #1,%0\n"
	"Lberr1:\n\t"
		"movel %1,%/sp\n\t"
		"movec %2,%/vbr"
		: "=&d" (ret), "=&r" (save_sp), "=&r" (save_vbr)
		: "a" (regp), "a" (पंचांगp_vectors)
	);
	local_irq_restore(flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(hwreg_present);

/* Basically the same, but ग_लिखोs a value पूर्णांकo a word रेजिस्टर, रक्षित
 * by a bus error handler. Returns 1 अगर successful, 0 otherwise.
 */

पूर्णांक hwreg_ग_लिखो(अस्थिर व्योम *regp, अचिन्हित लघु val)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	दीर्घ save_sp, save_vbr;
	दीर्घ पंचांगp_vectors[3];

	local_irq_save(flags);
	__यंत्र__ __अस्थिर__ (
		"movec %/vbr,%2\n\t"
		"movel #Lberr2,%4@(8)\n\t"
		"movec %4,%/vbr\n\t"
		"movel %/sp,%1\n\t"
		"moveq #0,%0\n\t"
		"movew %5,%3@\n\t"
		"nop\n\t"
		/*
		 * If this nop isn't present, 'ret' may alपढ़ोy be loaded
		 * with 1 at the समय the bus error happens!
		 */
		"moveq #1,%0\n"
	"Lberr2:\n\t"
		"movel %1,%/sp\n\t"
		"movec %2,%/vbr"
		: "=&d" (ret), "=&r" (save_sp), "=&r" (save_vbr)
		: "a" (regp), "a" (पंचांगp_vectors), "g" (val)
	);
	local_irq_restore(flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(hwreg_ग_लिखो);

