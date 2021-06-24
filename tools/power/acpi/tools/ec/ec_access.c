<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ec_access.c
 *
 * Copyright (C) 2010 SUSE Linux Products GmbH
 * Author:
 *      Thomas Renninger <trenn@suse.de>
 */

#समावेश <fcntl.h>
#समावेश <err.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <libgen.h>
#समावेश <unistd.h>
#समावेश <getopt.h>
#समावेश <मानक_निवेशt.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>


#घोषणा EC_SPACE_SIZE 256
#घोषणा SYSFS_PATH "/sys/kernel/debug/ec/ec0/io"

/* TBD/Enhancements:
   - Provide param क्रम accessing dअगरferent ECs (not supported by kernel yet)
*/

अटल पूर्णांक पढ़ो_mode = -1;
अटल पूर्णांक sleep_समय;
अटल पूर्णांक ग_लिखो_byte_offset = -1;
अटल पूर्णांक पढ़ो_byte_offset = -1;
अटल uपूर्णांक8_t ग_लिखो_value = -1;

व्योम usage(अक्षर progname[], पूर्णांक निकास_status)
अणु
	म_लिखो("Usage:\n");
	म_लिखो("1) %s -r [-s sleep]\n", basename(progname));
	म_लिखो("2) %s -b byte_offset\n", basename(progname));
	म_लिखो("3) %s -w byte_offset -v value\n\n", basename(progname));

	माला_दो("\t-r [-s sleep]      : Dump EC registers");
	माला_दो("\t                     If sleep is given, sleep x seconds,");
	माला_दो("\t                     re-read EC registers and show changes");
	माला_दो("\t-b offset          : Read value at byte_offset (in hex)");
	माला_दो("\t-w offset -v value : Write value at byte_offset");
	माला_दो("\t-h                 : Print this help\n\n");
	माला_दो("Offsets and values are in hexadecimal number system.");
	माला_दो("The offset and value must be between 0 and 0xff.");
	निकास(निकास_status);
पूर्ण

व्योम parse_opts(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "rs:b:w:v:h")) != -1) अणु

		चयन (c) अणु
		हाल 'r':
			अगर (पढ़ो_mode != -1)
				usage(argv[0], निकास_त्रुटि);
			पढ़ो_mode = 1;
			अवरोध;
		हाल 's':
			अगर (पढ़ो_mode != -1 && पढ़ो_mode != 1)
				usage(argv[0], निकास_त्रुटि);

			sleep_समय = म_से_प(optarg);
			अगर (sleep_समय <= 0) अणु
				sleep_समय = 0;
				usage(argv[0], निकास_त्रुटि);
				म_लिखो("Bad sleep time: %s\n", optarg);
			पूर्ण
			अवरोध;
		हाल 'b':
			अगर (पढ़ो_mode != -1)
				usage(argv[0], निकास_त्रुटि);
			पढ़ो_mode = 1;
			पढ़ो_byte_offset = म_से_अदीर्घ(optarg, शून्य, 16);
			अवरोध;
		हाल 'w':
			अगर (पढ़ो_mode != -1)
				usage(argv[0], निकास_त्रुटि);
			पढ़ो_mode = 0;
			ग_लिखो_byte_offset = म_से_अदीर्घ(optarg, शून्य, 16);
			अवरोध;
		हाल 'v':
			ग_लिखो_value = म_से_अदीर्घ(optarg, शून्य, 16);
			अवरोध;
		हाल 'h':
			usage(argv[0], निकास_सफल);
		शेष:
			ख_लिखो(मानक_त्रुटि, "Unknown option!\n");
			usage(argv[0], निकास_त्रुटि);
		पूर्ण
	पूर्ण
	अगर (पढ़ो_mode == 0) अणु
		अगर (ग_लिखो_byte_offset < 0 ||
		    ग_लिखो_byte_offset >= EC_SPACE_SIZE) अणु
			ख_लिखो(मानक_त्रुटि, "Wrong byte offset 0x%.2x, valid: "
				"[0-0x%.2x]\n",
				ग_लिखो_byte_offset, EC_SPACE_SIZE - 1);
			usage(argv[0], निकास_त्रुटि);
		पूर्ण
		अगर (ग_लिखो_value < 0 ||
		    ग_लिखो_value >= 255) अणु
			ख_लिखो(मानक_त्रुटि, "Wrong byte offset 0x%.2x, valid:"
				"[0-0xff]\n", ग_लिखो_byte_offset);
			usage(argv[0], निकास_त्रुटि);
		पूर्ण
	पूर्ण
	अगर (पढ़ो_mode == 1 && पढ़ो_byte_offset != -1) अणु
		अगर (पढ़ो_byte_offset < -1 ||
		    पढ़ो_byte_offset >= EC_SPACE_SIZE) अणु
			ख_लिखो(मानक_त्रुटि, "Wrong byte offset 0x%.2x, valid: "
				"[0-0x%.2x]\n",
				पढ़ो_byte_offset, EC_SPACE_SIZE - 1);
			usage(argv[0], निकास_त्रुटि);
		पूर्ण
	पूर्ण
	/* Add additional parameter checks here */
पूर्ण

व्योम dump_ec(पूर्णांक fd)
अणु
	अक्षर buf[EC_SPACE_SIZE];
	अक्षर buf2[EC_SPACE_SIZE];
	पूर्णांक byte_off, bytes_पढ़ो;

	bytes_पढ़ो = पढ़ो(fd, buf, EC_SPACE_SIZE);

	अगर (bytes_पढ़ो == -1)
		err(निकास_त्रुटि, "Could not read from %s\n", SYSFS_PATH);

	अगर (bytes_पढ़ो != EC_SPACE_SIZE)
		ख_लिखो(मानक_त्रुटि, "Could only read %d bytes\n", bytes_पढ़ो);

	म_लिखो("     00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F");
	क्रम (byte_off = 0; byte_off < bytes_पढ़ो; byte_off++) अणु
		अगर ((byte_off % 16) == 0)
			म_लिखो("\n%.2X: ", byte_off);
		म_लिखो(" %.2x ", (uपूर्णांक8_t)buf[byte_off]);
	पूर्ण
	म_लिखो("\n");

	अगर (!sleep_समय)
		वापस;

	म_लिखो("\n");
	lseek(fd, 0, शुरू_से);
	sleep(sleep_समय);

	bytes_पढ़ो = पढ़ो(fd, buf2, EC_SPACE_SIZE);

	अगर (bytes_पढ़ो == -1)
		err(निकास_त्रुटि, "Could not read from %s\n", SYSFS_PATH);

	अगर (bytes_पढ़ो != EC_SPACE_SIZE)
		ख_लिखो(मानक_त्रुटि, "Could only read %d bytes\n", bytes_पढ़ो);

	म_लिखो("     00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F");
	क्रम (byte_off = 0; byte_off < bytes_पढ़ो; byte_off++) अणु
		अगर ((byte_off % 16) == 0)
			म_लिखो("\n%.2X: ", byte_off);

		अगर (buf[byte_off] == buf2[byte_off])
			म_लिखो(" %.2x ", (uपूर्णांक8_t)buf2[byte_off]);
		अन्यथा
			म_लिखो("*%.2x ", (uपूर्णांक8_t)buf2[byte_off]);
	पूर्ण
	म_लिखो("\n");
पूर्ण

व्योम पढ़ो_ec_val(पूर्णांक fd, पूर्णांक byte_offset)
अणु
	uपूर्णांक8_t buf;
	पूर्णांक error;

	error = lseek(fd, byte_offset, शुरू_से);
	अगर (error != byte_offset)
		err(निकास_त्रुटि, "Cannot set offset to 0x%.2x", byte_offset);

	error = पढ़ो(fd, &buf, 1);
	अगर (error != 1)
		err(निकास_त्रुटि, "Could not read byte 0x%.2x from %s\n",
		    byte_offset, SYSFS_PATH);
	म_लिखो("0x%.2x\n", buf);
	वापस;
पूर्ण

व्योम ग_लिखो_ec_val(पूर्णांक fd, पूर्णांक byte_offset, uपूर्णांक8_t value)
अणु
	पूर्णांक error;

	error = lseek(fd, byte_offset, शुरू_से);
	अगर (error != byte_offset)
		err(निकास_त्रुटि, "Cannot set offset to 0x%.2x", byte_offset);

	error = ग_लिखो(fd, &value, 1);
	अगर (error != 1)
		err(निकास_त्रुटि, "Cannot write value 0x%.2x to offset 0x%.2x",
		    value, byte_offset);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक file_mode = O_RDONLY;
	पूर्णांक fd;

	parse_opts(argc, argv);

	अगर (पढ़ो_mode == 0)
		file_mode = O_WRONLY;
	अन्यथा अगर (पढ़ो_mode == 1)
		file_mode = O_RDONLY;
	अन्यथा
		usage(argv[0], निकास_त्रुटि);

	fd = खोलो(SYSFS_PATH, file_mode);
	अगर (fd == -1)
		err(निकास_त्रुटि, "%s", SYSFS_PATH);

	अगर (पढ़ो_mode)
		अगर (पढ़ो_byte_offset == -1)
			dump_ec(fd);
		अन्यथा अगर (पढ़ो_byte_offset < 0 ||
			 पढ़ो_byte_offset >= EC_SPACE_SIZE)
			usage(argv[0], निकास_त्रुटि);
		अन्यथा
			पढ़ो_ec_val(fd, पढ़ो_byte_offset);
	अन्यथा
		ग_लिखो_ec_val(fd, ग_लिखो_byte_offset, ग_लिखो_value);
	बंद(fd);

	निकास(निकास_सफल);
पूर्ण
