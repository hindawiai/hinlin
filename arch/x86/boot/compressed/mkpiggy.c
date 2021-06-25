<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ----------------------------------------------------------------------- *
 *
 *  Copyright (C) 2009 Intel Corporation. All rights reserved.
 *
 *  H. Peter Anvin <hpa@linux.पूर्णांकel.com>
 *
 * -----------------------------------------------------------------------
 *
 * Outमाला_दो a small assembly wrapper with the appropriate symbols defined.
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <tools/le_byteshअगरt.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	uपूर्णांक32_t olen;
	दीर्घ ilen;
	खाता *f = शून्य;
	पूर्णांक retval = 1;

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s compressed_file\n", argv[0]);
		जाओ bail;
	पूर्ण

	/* Get the inक्रमmation क्रम the compressed kernel image first */

	f = ख_खोलो(argv[1], "r");
	अगर (!f) अणु
		लिखो_त्रुटि(argv[1]);
		जाओ bail;
	पूर्ण


	अगर (ख_जाओ(f, -4L, अंत_से)) अणु
		लिखो_त्रुटि(argv[1]);
	पूर्ण

	अगर (ख_पढ़ो(&olen, माप(olen), 1, f) != 1) अणु
		लिखो_त्रुटि(argv[1]);
		जाओ bail;
	पूर्ण

	ilen = ख_बताओ(f);
	olen = get_unaligned_le32(&olen);

	म_लिखो(".section \".rodata..compressed\",\"a\",@progbits\n");
	म_लिखो(".globl z_input_len\n");
	म_लिखो("z_input_len = %lu\n", ilen);
	म_लिखो(".globl z_output_len\n");
	म_लिखो("z_output_len = %lu\n", (अचिन्हित दीर्घ)olen);

	म_लिखो(".globl input_data, input_data_end\n");
	म_लिखो("input_data:\n");
	म_लिखो(".incbin \"%s\"\n", argv[1]);
	म_लिखो("input_data_end:\n");

	म_लिखो(".section \".rodata\",\"a\",@progbits\n");
	म_लिखो(".globl input_len\n");
	म_लिखो("input_len:\n\t.long %lu\n", ilen);
	म_लिखो(".globl output_len\n");
	म_लिखो("output_len:\n\t.long %lu\n", (अचिन्हित दीर्घ)olen);

	retval = 0;
bail:
	अगर (f)
		ख_बंद(f);
	वापस retval;
पूर्ण
