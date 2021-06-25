<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ioport.h>
#समावेश <यंत्र/पन.स>

#समावेश "pc873xx.h"

अटल अचिन्हित pc873xx_probelist[] = अणु0x398, 0x26e, 0पूर्ण;

अटल अक्षर *pc873xx_names[] = अणु
	"PC87303", "PC87306", "PC87312", "PC87332", "PC87334"
पूर्ण;

अटल अचिन्हित पूर्णांक base, model;


अचिन्हित पूर्णांक __init pc873xx_get_base(व्योम)
अणु
	वापस base;
पूर्ण

अक्षर *__init pc873xx_get_model(व्योम)
अणु
	वापस pc873xx_names[model];
पूर्ण

अटल अचिन्हित अक्षर __init pc873xx_पढ़ो(अचिन्हित पूर्णांक base, पूर्णांक reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल व्योम __init pc873xx_ग_लिखो(अचिन्हित पूर्णांक base, पूर्णांक reg, अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	outb(reg, base);
	outb(data, base + 1);
	outb(data, base + 1);		/* Must be written twice */
	local_irq_restore(flags);
पूर्ण

पूर्णांक __init pc873xx_probe(व्योम)
अणु
	पूर्णांक val, index = 0;

	जबतक ((base = pc873xx_probelist[index++])) अणु

		अगर (request_region(base, 2, "Super IO PC873xx") == शून्य)
			जारी;

		val = pc873xx_पढ़ो(base, REG_SID);
		अगर ((val & 0xf0) == 0x10) अणु
			model = PC87332;
			अवरोध;
		पूर्ण अन्यथा अगर ((val & 0xf8) == 0x70) अणु
			model = PC87306;
			अवरोध;
		पूर्ण अन्यथा अगर ((val & 0xf8) == 0x50) अणु
			model = PC87334;
			अवरोध;
		पूर्ण अन्यथा अगर ((val & 0xf8) == 0x40) अणु
			model = PC87303;
			अवरोध;
		पूर्ण

		release_region(base, 2);
	पूर्ण

	वापस (base == 0) ? -1 : 1;
पूर्ण

व्योम __init pc873xx_enable_epp19(व्योम)
अणु
	अचिन्हित अक्षर data;

	prपूर्णांकk(KERN_INFO "PC873xx enabling EPP v1.9\n");
	data = pc873xx_पढ़ो(base, REG_PCR);
	pc873xx_ग_लिखो(base, REG_PCR, (data & 0xFC) | 0x02);
पूर्ण

व्योम __init pc873xx_enable_ide(व्योम)
अणु
	अचिन्हित अक्षर data;

	prपूर्णांकk(KERN_INFO "PC873xx enabling IDE interrupt\n");
	data = pc873xx_पढ़ो(base, REG_FER);
	pc873xx_ग_लिखो(base, REG_FER, data | 0x40);
पूर्ण
