<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <elf.h>

पूर्णांक
मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित अक्षर ei[EI_NIDENT];
	जोड़ अणु लघु s; अक्षर c[2]; पूर्ण endian_test;

	अगर (ख_पढ़ो(ei, 1, EI_NIDENT, मानक_निवेश) != EI_NIDENT) अणु
		ख_लिखो(मानक_त्रुटि, "Error: input truncated\n");
		वापस 1;
	पूर्ण
	अगर (स_भेद(ei, ELFMAG, SELFMAG) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "Error: not ELF\n");
		वापस 1;
	पूर्ण
	चयन (ei[EI_CLASS]) अणु
	हाल ELFCLASS32:
		म_लिखो("#define KERNEL_ELFCLASS ELFCLASS32\n");
		अवरोध;
	हाल ELFCLASS64:
		म_लिखो("#define KERNEL_ELFCLASS ELFCLASS64\n");
		अवरोध;
	शेष:
		निकास(1);
	पूर्ण
	चयन (ei[EI_DATA]) अणु
	हाल ELFDATA2LSB:
		म_लिखो("#define KERNEL_ELFDATA ELFDATA2LSB\n");
		अवरोध;
	हाल ELFDATA2MSB:
		म_लिखो("#define KERNEL_ELFDATA ELFDATA2MSB\n");
		अवरोध;
	शेष:
		निकास(1);
	पूर्ण

	अगर (माप(अचिन्हित दीर्घ) == 4) अणु
		म_लिखो("#define HOST_ELFCLASS ELFCLASS32\n");
	पूर्ण अन्यथा अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		म_लिखो("#define HOST_ELFCLASS ELFCLASS64\n");
	पूर्ण

	endian_test.s = 0x0102;
	अगर (स_भेद(endian_test.c, "\x01\x02", 2) == 0)
		म_लिखो("#define HOST_ELFDATA ELFDATA2MSB\n");
	अन्यथा अगर (स_भेद(endian_test.c, "\x02\x01", 2) == 0)
		म_लिखो("#define HOST_ELFDATA ELFDATA2LSB\n");
	अन्यथा
		निकास(1);

	वापस 0;
पूर्ण
