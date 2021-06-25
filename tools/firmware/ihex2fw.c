<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Parser/loader क्रम IHEX क्रमmatted data.
 *
 * Copyright तऊ 2008 David Woodhouse <dwmw2@infradead.org>
 * Copyright तऊ 2005 Jan Harkes <jaharkes@cs.cmu.edu>
 */

#समावेश <मानक_निवेशt.h>
#समावेश <arpa/inet.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#घोषणा _GNU_SOURCE
#समावेश <getopt.h>


#घोषणा __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#घोषणा __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#घोषणा ALIGN(x, a)			__ALIGN_KERNEL((x), (a))

काष्ठा ihex_binrec अणु
	काष्ठा ihex_binrec *next; /* not part of the real data काष्ठाure */
        uपूर्णांक32_t addr;
        uपूर्णांक16_t len;
        uपूर्णांक8_t data[];
पूर्ण;

/**
 * nybble/hex are little helpers to parse hexadecimal numbers to a byte value
 **/
अटल uपूर्णांक8_t nybble(स्थिर uपूर्णांक8_t n)
अणु
	अगर      (n >= '0' && n <= '9') return n - '0';
	अन्यथा अगर (n >= 'A' && n <= 'F') return n - ('A' - 10);
	अन्यथा अगर (n >= 'a' && n <= 'f') return n - ('a' - 10);
	वापस 0;
पूर्ण

अटल uपूर्णांक8_t hex(स्थिर uपूर्णांक8_t *data, uपूर्णांक8_t *crc)
अणु
	uपूर्णांक8_t val = (nybble(data[0]) << 4) | nybble(data[1]);
	*crc += val;
	वापस val;
पूर्ण

अटल पूर्णांक process_ihex(uपूर्णांक8_t *data, sमाप_प्रकार size);
अटल व्योम file_record(काष्ठा ihex_binrec *record);
अटल पूर्णांक output_records(पूर्णांक outfd);

अटल पूर्णांक sort_records = 0;
अटल पूर्णांक wide_records = 0;
अटल पूर्णांक include_jump = 0;

अटल पूर्णांक usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "ihex2fw: Convert ihex files into binary "
		"representation for use by Linux kernel\n");
	ख_लिखो(मानक_त्रुटि, "usage: ihex2fw [<options>] <src.HEX> <dst.fw>\n");
	ख_लिखो(मानक_त्रुटि, "       -w: wide records (16-bit length)\n");
	ख_लिखो(मानक_त्रुटि, "       -s: sort records by address\n");
	ख_लिखो(मानक_त्रुटि, "       -j: include records for CS:IP/EIP address\n");
	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक infd, outfd;
	काष्ठा stat st;
	uपूर्णांक8_t *data;
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "wsj")) != -1) अणु
		चयन (opt) अणु
		हाल 'w':
			wide_records = 1;
			अवरोध;
		हाल 's':
			sort_records = 1;
			अवरोध;
		हाल 'j':
			include_jump = 1;
			अवरोध;
		शेष:
			वापस usage();
		पूर्ण
	पूर्ण

	अगर (optind + 2 != argc)
		वापस usage();

	अगर (!म_भेद(argv[optind], "-"))
		infd = 0;
	अन्यथा
		infd = खोलो(argv[optind], O_RDONLY);
	अगर (infd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open source file: %s",
			म_त्रुटि(त्रुटि_सं));
		वापस usage();
	पूर्ण
	अगर (ख_स्थिति(infd, &st)) अणु
		लिखो_त्रुटि("stat");
		वापस 1;
	पूर्ण
	data = mmap(शून्य, st.st_size, PROT_READ, MAP_SHARED, infd, 0);
	अगर (data == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		वापस 1;
	पूर्ण

	अगर (!म_भेद(argv[optind+1], "-"))
		outfd = 1;
	अन्यथा
		outfd = खोलो(argv[optind+1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
	अगर (outfd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open destination file: %s",
			म_त्रुटि(त्रुटि_सं));
		वापस usage();
	पूर्ण
	अगर (process_ihex(data, st.st_size))
		वापस 1;

	वापस output_records(outfd);
पूर्ण

अटल पूर्णांक process_ihex(uपूर्णांक8_t *data, sमाप_प्रकार size)
अणु
	काष्ठा ihex_binrec *record;
	माप_प्रकार record_size;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t data32;
	uपूर्णांक8_t type, crc = 0, crcbyte = 0;
	पूर्णांक i, j;
	पूर्णांक line = 1;
	पूर्णांक len;

	i = 0;
next_record:
	/* search क्रम the start of record अक्षरacter */
	जबतक (i < size) अणु
		अगर (data[i] == '\n') line++;
		अगर (data[i++] == ':') अवरोध;
	पूर्ण

	/* Minimum record length would be about 10 अक्षरacters */
	अगर (i + 10 > size) अणु
		ख_लिखो(मानक_त्रुटि, "Can't find valid record at line %d\n", line);
		वापस -EINVAL;
	पूर्ण

	len = hex(data + i, &crc); i += 2;
	अगर (wide_records) अणु
		len <<= 8;
		len += hex(data + i, &crc); i += 2;
	पूर्ण
	record_size = ALIGN(माप(*record) + len, 4);
	record = दो_स्मृति(record_size);
	अगर (!record) अणु
		ख_लिखो(मानक_त्रुटि, "out of memory for records\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(record, 0, record_size);
	record->len = len;

	/* now check अगर we have enough data to पढ़ो everything */
	अगर (i + 8 + (record->len * 2) > size) अणु
		ख_लिखो(मानक_त्रुटि, "Not enough data to read complete record at line %d\n",
			line);
		वापस -EINVAL;
	पूर्ण

	record->addr  = hex(data + i, &crc) << 8; i += 2;
	record->addr |= hex(data + i, &crc); i += 2;
	type = hex(data + i, &crc); i += 2;

	क्रम (j = 0; j < record->len; j++, i += 2)
		record->data[j] = hex(data + i, &crc);

	/* check CRC */
	crcbyte = hex(data + i, &crc); i += 2;
	अगर (crc != 0) अणु
		ख_लिखो(मानक_त्रुटि, "CRC failure at line %d: got 0x%X, expected 0x%X\n",
			line, crcbyte, (अचिन्हित अक्षर)(crcbyte-crc));
		वापस -EINVAL;
	पूर्ण

	/* Done पढ़ोing the record */
	चयन (type) अणु
	हाल 0:
		/* old style खातापूर्ण record? */
		अगर (!record->len)
			अवरोध;

		record->addr += offset;
		file_record(record);
		जाओ next_record;

	हाल 1: /* End-Of-File Record */
		अगर (record->addr || record->len) अणु
			ख_लिखो(मानक_त्रुटि, "Bad EOF record (type 01) format at line %d",
				line);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल 2: /* Extended Segment Address Record (HEX86) */
	हाल 4: /* Extended Linear Address Record (HEX386) */
		अगर (record->addr || record->len != 2) अणु
			ख_लिखो(मानक_त्रुटि, "Bad HEX86/HEX386 record (type %02X) at line %d\n",
				type, line);
			वापस -EINVAL;
		पूर्ण

		/* We shouldn't really be using the offset क्रम HEX86 because
		 * the wraparound हाल is specअगरied quite dअगरferently. */
		offset = record->data[0] << 8 | record->data[1];
		offset <<= (type == 2 ? 4 : 16);
		जाओ next_record;

	हाल 3: /* Start Segment Address Record */
	हाल 5: /* Start Linear Address Record */
		अगर (record->addr || record->len != 4) अणु
			ख_लिखो(मानक_त्रुटि, "Bad Start Address record (type %02X) at line %d\n",
				type, line);
			वापस -EINVAL;
		पूर्ण

		स_नकल(&data32, &record->data[0], माप(data32));
		data32 = htonl(data32);
		स_नकल(&record->data[0], &data32, माप(data32));

		/* These records contain the CS/IP or EIP where execution
		 * starts. If requested output this as a record. */
		अगर (include_jump)
			file_record(record);
		जाओ next_record;

	शेष:
		ख_लिखो(मानक_त्रुटि, "Unknown record (type %02X)\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ihex_binrec *records;

अटल व्योम file_record(काष्ठा ihex_binrec *record)
अणु
	काष्ठा ihex_binrec **p = &records;

	जबतक ((*p) && (!sort_records || (*p)->addr < record->addr))
		p = &((*p)->next);

	record->next = *p;
	*p = record;
पूर्ण

अटल uपूर्णांक16_t ihex_binrec_size(काष्ठा ihex_binrec *p)
अणु
	वापस p->len + माप(p->addr) + माप(p->len);
पूर्ण

अटल पूर्णांक output_records(पूर्णांक outfd)
अणु
	अचिन्हित अक्षर zeroes[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	काष्ठा ihex_binrec *p = records;

	जबतक (p) अणु
		uपूर्णांक16_t ग_लिखोlen = ALIGN(ihex_binrec_size(p), 4);

		p->addr = htonl(p->addr);
		p->len = htons(p->len);
		अगर (ग_लिखो(outfd, &p->addr, ग_लिखोlen) != ग_लिखोlen)
			वापस 1;
		p = p->next;
	पूर्ण
	/* खातापूर्ण record is zero length, since we करोn't bother to represent
	   the type field in the binary version */
	अगर (ग_लिखो(outfd, zeroes, 6) != 6)
		वापस 1;
	वापस 0;
पूर्ण
