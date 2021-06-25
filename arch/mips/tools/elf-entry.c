<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <byteswap.h>
#समावेश <elf.h>
#समावेश <endian.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#अगर_घोषित be32toh
/* If libc provides [bl]eअणु32,64पूर्णtoh() then we'll use them */
#या_अगर BYTE_ORDER == LITTLE_ENDIAN
# define be32toh(x)	bswap_32(x)
# define le32toh(x)	(x)
# define be64toh(x)	bswap_64(x)
# define le64toh(x)	(x)
#या_अगर BYTE_ORDER == BIG_ENDIAN
# define be32toh(x)	(x)
# define le32toh(x)	bswap_32(x)
# define be64toh(x)	(x)
# define le64toh(x)	bswap_64(x)
#पूर्ण_अगर

__attribute__((noवापस))
अटल व्योम die(स्थिर अक्षर *msg)
अणु
	ख_माला_दो(msg, मानक_त्रुटि);
	निकास(निकास_त्रुटि);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	uपूर्णांक64_t entry;
	माप_प्रकार nपढ़ो;
	खाता *file;
	जोड़ अणु
		Elf32_Ehdr ehdr32;
		Elf64_Ehdr ehdr64;
	पूर्ण hdr;

	अगर (argc != 2)
		die("Usage: elf-entry <elf-file>\n");

	file = ख_खोलो(argv[1], "r");
	अगर (!file) अणु
		लिखो_त्रुटि("Unable to open input file");
		वापस निकास_त्रुटि;
	पूर्ण

	nपढ़ो = ख_पढ़ो(&hdr, 1, माप(hdr), file);
	अगर (nपढ़ो != माप(hdr)) अणु
		लिखो_त्रुटि("Unable to read input file");
		ख_बंद(file);
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (स_भेद(hdr.ehdr32.e_ident, ELFMAG, SELFMAG)) अणु
		ख_बंद(file);
		die("Input is not an ELF\n");
	पूर्ण

	चयन (hdr.ehdr32.e_ident[EI_CLASS]) अणु
	हाल ELFCLASS32:
		चयन (hdr.ehdr32.e_ident[EI_DATA]) अणु
		हाल ELFDATA2LSB:
			entry = le32toh(hdr.ehdr32.e_entry);
			अवरोध;
		हाल ELFDATA2MSB:
			entry = be32toh(hdr.ehdr32.e_entry);
			अवरोध;
		शेष:
			ख_बंद(file);
			die("Invalid ELF encoding\n");
		पूर्ण

		/* Sign extend to क्रमm a canonical address */
		entry = (पूर्णांक64_t)(पूर्णांक32_t)entry;
		अवरोध;

	हाल ELFCLASS64:
		चयन (hdr.ehdr32.e_ident[EI_DATA]) अणु
		हाल ELFDATA2LSB:
			entry = le64toh(hdr.ehdr64.e_entry);
			अवरोध;
		हाल ELFDATA2MSB:
			entry = be64toh(hdr.ehdr64.e_entry);
			अवरोध;
		शेष:
			ख_बंद(file);
			die("Invalid ELF encoding\n");
		पूर्ण
		अवरोध;

	शेष:
		ख_बंद(file);
		die("Invalid ELF class\n");
	पूर्ण

	म_लिखो("0x%016" PRIx64 "\n", entry);
	ख_बंद(file);
	वापस निकास_सफल;
पूर्ण
