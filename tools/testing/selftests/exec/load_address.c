<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <link.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

काष्ठा Statistics अणु
	अचिन्हित दीर्घ दीर्घ load_address;
	अचिन्हित दीर्घ दीर्घ alignment;
पूर्ण;

पूर्णांक ExtractStatistics(काष्ठा dl_phdr_info *info, माप_प्रकार size, व्योम *data)
अणु
	काष्ठा Statistics *stats = (काष्ठा Statistics *) data;
	पूर्णांक i;

	अगर (info->dlpi_name != शून्य && info->dlpi_name[0] != '\0') अणु
		// Ignore headers from other than the executable.
		वापस 2;
	पूर्ण

	stats->load_address = (अचिन्हित दीर्घ दीर्घ) info->dlpi_addr;
	stats->alignment = 0;

	क्रम (i = 0; i < info->dlpi_phnum; i++) अणु
		अगर (info->dlpi_phdr[i].p_type != PT_LOAD)
			जारी;

		अगर (info->dlpi_phdr[i].p_align > stats->alignment)
			stats->alignment = info->dlpi_phdr[i].p_align;
	पूर्ण

	वापस 1;  // Terminate dl_iterate_phdr.
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा Statistics extracted;
	अचिन्हित दीर्घ दीर्घ misalign;
	पूर्णांक ret;

	ret = dl_iterate_phdr(ExtractStatistics, &extracted);
	अगर (ret != 1) अणु
		ख_लिखो(मानक_त्रुटि, "FAILED\n");
		वापस 1;
	पूर्ण

	अगर (extracted.alignment == 0) अणु
		ख_लिखो(मानक_त्रुटि, "No alignment found\n");
		वापस 1;
	पूर्ण अन्यथा अगर (extracted.alignment & (extracted.alignment - 1)) अणु
		ख_लिखो(मानक_त्रुटि, "Alignment is not a power of 2\n");
		वापस 1;
	पूर्ण

	misalign = extracted.load_address & (extracted.alignment - 1);
	अगर (misalign) अणु
		म_लिखो("alignment = %llu, load_address = %llu\n",
			extracted.alignment, extracted.load_address);
		ख_लिखो(मानक_त्रुटि, "FAILED\n");
		वापस 1;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "PASS\n");
	वापस 0;
पूर्ण
