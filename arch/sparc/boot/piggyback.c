<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   Simple utility to make a single-image install kernel with initial ramdisk
   क्रम Sparc tftpbooting without need to set up nfs.

   Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
   Pete Zaitcev <zaitcev@yahoo.com> endian fixes क्रम cross-compiles, 2000.
   Copyright (C) 2011 Sam Ravnborg <sam@ravnborg.org>

 */

#समावेश <dirent.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

/*
 * Note: run this on an a.out kernel (use elftoaout क्रम it),
 * as PROM looks क्रम a.out image only.
 */

#घोषणा AOUT_TEXT_OFFSET   32

अटल पूर्णांक is64bit = 0;

/* align to घातer-of-two size */
अटल पूर्णांक align(पूर्णांक n)
अणु
	अगर (is64bit)
		वापस (n + 0x1fff) & ~0x1fff;
	अन्यथा
		वापस (n + 0xfff) & ~0xfff;
पूर्ण

/* पढ़ो two bytes as big endian */
अटल अचिन्हित लघु ld2(अक्षर *p)
अणु
	वापस (p[0] << 8) | p[1];
पूर्ण

/* save 4 bytes as big endian */
अटल व्योम st4(अक्षर *p, अचिन्हित पूर्णांक x)
अणु
	p[0] = x >> 24;
	p[1] = x >> 16;
	p[2] = x >> 8;
	p[3] = x;
पूर्ण

अटल व्योम die(स्थिर अक्षर *str)
अणु
	लिखो_त्रुटि(str);
	निकास(1);
पूर्ण

अटल व्योम usage(व्योम)
अणु
	/* fs_img.gz is an image of initial ramdisk. */
	ख_लिखो(मानक_त्रुटि, "Usage: piggyback bits vmlinux.aout System.map fs_img.gz\n");
	ख_लिखो(मानक_त्रुटि, "\tKernel image will be modified in place.\n");
	निकास(1);
पूर्ण

अटल पूर्णांक start_line(स्थिर अक्षर *line)
अणु
	अगर (म_भेद(line + 10, " _start\n") == 0)
		वापस 1;
	अन्यथा अगर (म_भेद(line + 18, " _start\n") == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक end_line(स्थिर अक्षर *line)
अणु
	अगर (म_भेद(line + 10, " _end\n") == 0)
		वापस 1;
	अन्यथा अगर (म_भेद (line + 18, " _end\n") == 0)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Find address क्रम start and end in System.map.
 * The file looks like this:
 * f0004000 ... _start
 * f0379f79 ... _end
 * 1234567890123456
 * ^coloumn 1
 * There is support क्रम 64 bit addresses too.
 *
 * Return 0 अगर either start or end is not found
 */
अटल पूर्णांक get_start_end(स्थिर अक्षर *filename, अचिन्हित पूर्णांक *start,
                                               अचिन्हित पूर्णांक *end)
अणु
	खाता *map;
	अक्षर buffer[1024];

	*start = 0;
	*end = 0;
	map = ख_खोलो(filename, "r");
	अगर (!map)
		die(filename);
	जबतक (ख_माला_लो(buffer, 1024, map)) अणु
		अगर (start_line(buffer))
			*start = म_से_अदीर्घ(buffer, शून्य, 16);
		अन्यथा अगर (end_line(buffer))
			*end = म_से_अदीर्घ(buffer, शून्य, 16);
	पूर्ण
	ख_बंद (map);

	अगर (*start == 0 || *end == 0)
		वापस 0;

	वापस 1;
पूर्ण

#घोषणा LOOKBACK (128 * 4)
#घोषणा बफ_मानE 1024
/*
 * Find the HdrS entry from head_32/head_64.
 * We check अगर it is at the beginning of the file (sparc64 हाल)
 * and अगर not we search क्रम it.
 * When we search करो so in steps of 4 as HdrS is on a 4-byte aligned
 * address (it is on same alignment as sparc inकाष्ठाions)
 * Return the offset to the HdrS entry (as off_t)
 */
अटल off_t get_hdrs_offset(पूर्णांक kernelfd, स्थिर अक्षर *filename)
अणु
	अक्षर buffer[बफ_मानE];
	off_t offset;
	पूर्णांक i;

	अगर (lseek(kernelfd, 0, शुरू_से) < 0)
		die("lseek");
	अगर (पढ़ो(kernelfd, buffer, बफ_मानE) != बफ_मानE)
		die(filename);

	अगर (buffer[40] == 'H' && buffer[41] == 'd' &&
	    buffer[42] == 'r' && buffer[43] == 'S') अणु
		वापस 40;
	पूर्ण अन्यथा अणु
		/*  Find the gokernel label */
		/* Decode offset from branch inकाष्ठाion */
		offset = ld2(buffer + AOUT_TEXT_OFFSET + 2) << 2;
		/* Go back 512 bytes so we करो not miss HdrS */
		offset -= LOOKBACK;
		/* skip a.out header */
		offset += AOUT_TEXT_OFFSET;
		अगर (offset < 0) अणु
			त्रुटि_सं = -EINVAL;
			die("Calculated a negative offset, probably elftoaout generated an invalid image. Did you use a recent elftoaout ?");
		पूर्ण
		अगर (lseek(kernelfd, offset, शुरू_से) < 0)
			die("lseek");
		अगर (पढ़ो(kernelfd, buffer, बफ_मानE) != बफ_मानE)
			die(filename);

		क्रम (i = 0; i < LOOKBACK; i += 4) अणु
			अगर (buffer[i + 0] == 'H' && buffer[i + 1] == 'd' &&
			    buffer[i + 2] == 'r' && buffer[i + 3] == 'S') अणु
				वापस offset + i;
			पूर्ण
		पूर्ण
	पूर्ण
	ख_लिखो (मानक_त्रुटि, "Couldn't find headers signature in %s\n", filename);
	निकास(1);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc,अक्षर **argv)
अणु
	अटल अक्षर aout_magic[] = अणु 0x01, 0x03, 0x01, 0x07 पूर्ण;
	अक्षर buffer[1024];
	अचिन्हित पूर्णांक i, start, end;
	off_t offset;
	काष्ठा stat s;
	पूर्णांक image, tail;

	अगर (argc != 5)
		usage();
	अगर (म_भेद(argv[1], "64") == 0)
		is64bit = 1;
	अगर (stat (argv[4], &s) < 0)
		die(argv[4]);

	अगर (!get_start_end(argv[3], &start, &end)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not determine start and end from %s\n",
		        argv[3]);
		निकास(1);
	पूर्ण
	अगर ((image = खोलो(argv[2], O_RDWR)) < 0)
		die(argv[2]);
	अगर (पढ़ो(image, buffer, 512) != 512)
		die(argv[2]);
	अगर (स_भेद(buffer, aout_magic, 4) != 0) अणु
		ख_लिखो (मानक_त्रुटि, "Not a.out. Don't blame me.\n");
		निकास(1);
	पूर्ण
	/*
	 * We need to fill in values क्रम
	 * sparc_ramdisk_image + sparc_ramdisk_size
	 * To locate these symbols search क्रम the "HdrS" text which appear
	 * in the image a little beक्रमe the gokernel symbol.
	 * See definition of these in init_32.S
	 */

	offset = get_hdrs_offset(image, argv[2]);
	/* skip HdrS + LINUX_VERSION_CODE + HdrS version */
	offset += 10;

	अगर (lseek(image, offset, 0) < 0)
		die("lseek");

	/*
	 * root_flags = 0
	 * root_dev = 1 (RAMDISK_MAJOR)
	 * ram_flags = 0
	 * sparc_ramdisk_image = "PAGE aligned address after _end")
	 * sparc_ramdisk_size = size of image
	 */
	st4(buffer, 0);
	st4(buffer + 4, 0x01000000);
	st4(buffer + 8, align(end + 32));
	st4(buffer + 12, s.st_size);

	अगर (ग_लिखो(image, buffer + 2, 14) != 14)
		die(argv[2]);

	/* For sparc64 update a_text and clear a_data + a_bss */
	अगर (is64bit)
	अणु
		अगर (lseek(image, 4, 0) < 0)
			die("lseek");
		/* a_text */
		st4(buffer, align(end + 32 + 8191) - (start & ~0x3fffffUL) +
		            s.st_size);
		/* a_data */
		st4(buffer + 4, 0);
		/* a_bss */
		st4(buffer + 8, 0);
		अगर (ग_लिखो(image, buffer, 12) != 12)
			die(argv[2]);
	पूर्ण

	/* seek page aligned boundary in the image file and add boot image */
	अगर (lseek(image, AOUT_TEXT_OFFSET - start + align(end + 32), 0) < 0)
		die("lseek");
	अगर ((tail = खोलो(argv[4], O_RDONLY)) < 0)
		die(argv[4]);
	जबतक ((i = पढ़ो(tail, buffer, 1024)) > 0)
		अगर (ग_लिखो(image, buffer, i) != i)
			die(argv[2]);
	अगर (बंद(image) < 0)
		die("close");
	अगर (बंद(tail) < 0)
		die("close");
	वापस 0;
पूर्ण
