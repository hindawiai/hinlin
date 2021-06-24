<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  c 2001 PPC 64 Team, IBM Corp
 *
 * /dev/nvram driver क्रम PPC
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश "chrp.h"

अटल अचिन्हित पूर्णांक nvram_size;
अटल अचिन्हित अक्षर nvram_buf[4];
अटल DEFINE_SPINLOCK(nvram_lock);

अटल अचिन्हित अक्षर chrp_nvram_पढ़ो_val(पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक करोne;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर ret;

	अगर (addr >= nvram_size) अणु
		prपूर्णांकk(KERN_DEBUG "%s: read addr %d > nvram_size %u\n",
		       current->comm, addr, nvram_size);
		वापस 0xff;
	पूर्ण
	spin_lock_irqsave(&nvram_lock, flags);
	अगर ((rtas_call(rtas_token("nvram-fetch"), 3, 2, &करोne, addr,
		       __pa(nvram_buf), 1) != 0) || 1 != करोne)
		ret = 0xff;
	अन्यथा
		ret = nvram_buf[0];
	spin_unlock_irqrestore(&nvram_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम chrp_nvram_ग_लिखो_val(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	अचिन्हित पूर्णांक करोne;
	अचिन्हित दीर्घ flags;

	अगर (addr >= nvram_size) अणु
		prपूर्णांकk(KERN_DEBUG "%s: write addr %d > nvram_size %u\n",
		       current->comm, addr, nvram_size);
		वापस;
	पूर्ण
	spin_lock_irqsave(&nvram_lock, flags);
	nvram_buf[0] = val;
	अगर ((rtas_call(rtas_token("nvram-store"), 3, 2, &करोne, addr,
		       __pa(nvram_buf), 1) != 0) || 1 != करोne)
		prपूर्णांकk(KERN_DEBUG "rtas IO error storing 0x%02x at %d", val, addr);
	spin_unlock_irqrestore(&nvram_lock, flags);
पूर्ण

अटल sमाप_प्रकार chrp_nvram_size(व्योम)
अणु
	वापस nvram_size;
पूर्ण

व्योम __init chrp_nvram_init(व्योम)
अणु
	काष्ठा device_node *nvram;
	स्थिर __be32 *nbytes_p;
	अचिन्हित पूर्णांक proplen;

	nvram = of_find_node_by_type(शून्य, "nvram");
	अगर (nvram == शून्य)
		वापस;

	nbytes_p = of_get_property(nvram, "#bytes", &proplen);
	अगर (nbytes_p == शून्य || proplen != माप(अचिन्हित पूर्णांक)) अणु
		of_node_put(nvram);
		वापस;
	पूर्ण

	nvram_size = be32_to_cpup(nbytes_p);

	prपूर्णांकk(KERN_INFO "CHRP nvram contains %u bytes\n", nvram_size);
	of_node_put(nvram);

	ppc_md.nvram_पढ़ो_val  = chrp_nvram_पढ़ो_val;
	ppc_md.nvram_ग_लिखो_val = chrp_nvram_ग_लिखो_val;
	ppc_md.nvram_size      = chrp_nvram_size;

	वापस;
पूर्ण

MODULE_LICENSE("GPL v2");
