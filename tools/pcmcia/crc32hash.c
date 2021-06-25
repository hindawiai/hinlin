<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* crc32hash.c - derived from linux/lib/crc32.c, GNU GPL v2 */
/* Usage example:
$ ./crc32hash "Dual Speed"
*/

#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <प्रकार.स>
#समावेश <मानककोष.स>

अटल अचिन्हित पूर्णांक crc32(अचिन्हित अक्षर स्थिर *p, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक crc = 0;
	जबतक (len--) अणु
		crc ^= *p++;
		क्रम (i = 0; i < 8; i++)
			crc = (crc >> 1) ^ ((crc & 1) ? 0xedb88320 : 0);
	पूर्ण
	वापस crc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv) अणु
	अचिन्हित पूर्णांक result;
	अगर (argc != 2) अणु
		म_लिखो("no string passed as argument\n");
		वापस -1;
	पूर्ण
	result = crc32((अचिन्हित अक्षर स्थिर *)argv[1], म_माप(argv[1]));
	म_लिखो("0x%x\n", result);
	वापस 0;
पूर्ण
