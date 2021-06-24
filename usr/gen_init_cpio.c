<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <प्रकार.स>
#समावेश <सीमा.स>

/*
 * Original work by Jeff Garzik
 *
 * External file lists, symlink, pipe and fअगरo support by Thayne Harbaugh
 * Hard link support by Luciano Rocha
 */

#घोषणा xstr(s) #s
#घोषणा str(s) xstr(s)

अटल अचिन्हित पूर्णांक offset;
अटल अचिन्हित पूर्णांक ino = 721;
अटल समय_प्रकार शेष_mसमय;

काष्ठा file_handler अणु
	स्थिर अक्षर *type;
	पूर्णांक (*handler)(स्थिर अक्षर *line);
पूर्ण;

अटल व्योम push_string(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक name_len = म_माप(name) + 1;

	ख_माला_दो(name, मानक_निकास);
	अक्षर_दो(0);
	offset += name_len;
पूर्ण

अटल व्योम push_pad (व्योम)
अणु
	जबतक (offset & 3) अणु
		अक्षर_दो(0);
		offset++;
	पूर्ण
पूर्ण

अटल व्योम push_rest(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक name_len = म_माप(name) + 1;
	अचिन्हित पूर्णांक पंचांगp_ofs;

	ख_माला_दो(name, मानक_निकास);
	अक्षर_दो(0);
	offset += name_len;

	पंचांगp_ofs = name_len + 110;
	जबतक (पंचांगp_ofs & 3) अणु
		अक्षर_दो(0);
		offset++;
		पंचांगp_ofs++;
	पूर्ण
पूर्ण

अटल व्योम push_hdr(स्थिर अक्षर *s)
अणु
	ख_माला_दो(s, मानक_निकास);
	offset += 110;
पूर्ण

अटल व्योम cpio_trailer(व्योम)
अणु
	अक्षर s[256];
	स्थिर अक्षर name[] = "TRAILER!!!";

	प्र_लिखो(s, "%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		0,			/* ino */
		0,			/* mode */
		(दीर्घ) 0,		/* uid */
		(दीर्घ) 0,		/* gid */
		1,			/* nlink */
		(दीर्घ) 0,		/* mसमय */
		0,			/* filesize */
		0,			/* major */
		0,			/* minor */
		0,			/* rmajor */
		0,			/* rminor */
		(अचिन्हित)म_माप(name)+1, /* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_rest(name);

	जबतक (offset % 512) अणु
		अक्षर_दो(0);
		offset++;
	पूर्ण
पूर्ण

अटल पूर्णांक cpio_mkslink(स्थिर अक्षर *name, स्थिर अक्षर *target,
			 अचिन्हित पूर्णांक mode, uid_t uid, gid_t gid)
अणु
	अक्षर s[256];

	अगर (name[0] == '/')
		name++;
	प्र_लिखो(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		ino++,			/* ino */
		S_IFLNK | mode,		/* mode */
		(दीर्घ) uid,		/* uid */
		(दीर्घ) gid,		/* gid */
		1,			/* nlink */
		(दीर्घ) शेष_mसमय,	/* mसमय */
		(अचिन्हित)म_माप(target)+1, /* filesize */
		3,			/* major */
		1,			/* minor */
		0,			/* rmajor */
		0,			/* rminor */
		(अचिन्हित)म_माप(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_string(name);
	push_pad();
	push_string(target);
	push_pad();
	वापस 0;
पूर्ण

अटल पूर्णांक cpio_mkslink_line(स्थिर अक्षर *line)
अणु
	अक्षर name[PATH_MAX + 1];
	अक्षर target[PATH_MAX + 1];
	अचिन्हित पूर्णांक mode;
	पूर्णांक uid;
	पूर्णांक gid;
	पूर्णांक rc = -1;

	अगर (5 != माला_पूछो(line, "%" str(PATH_MAX) "s %" str(PATH_MAX) "s %o %d %d", name, target, &mode, &uid, &gid)) अणु
		ख_लिखो(मानक_त्रुटि, "Unrecognized dir format '%s'", line);
		जाओ fail;
	पूर्ण
	rc = cpio_mkslink(name, target, mode, uid, gid);
 fail:
	वापस rc;
पूर्ण

अटल पूर्णांक cpio_mkgeneric(स्थिर अक्षर *name, अचिन्हित पूर्णांक mode,
		       uid_t uid, gid_t gid)
अणु
	अक्षर s[256];

	अगर (name[0] == '/')
		name++;
	प्र_लिखो(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		ino++,			/* ino */
		mode,			/* mode */
		(दीर्घ) uid,		/* uid */
		(दीर्घ) gid,		/* gid */
		2,			/* nlink */
		(दीर्घ) शेष_mसमय,	/* mसमय */
		0,			/* filesize */
		3,			/* major */
		1,			/* minor */
		0,			/* rmajor */
		0,			/* rminor */
		(अचिन्हित)म_माप(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_rest(name);
	वापस 0;
पूर्ण

क्रमागत generic_types अणु
	GT_सूची,
	GT_PIPE,
	GT_SOCK
पूर्ण;

काष्ठा generic_type अणु
	स्थिर अक्षर *type;
	mode_t mode;
पूर्ण;

अटल काष्ठा generic_type generic_type_table[] = अणु
	[GT_सूची] = अणु
		.type = "dir",
		.mode = S_IFसूची
	पूर्ण,
	[GT_PIPE] = अणु
		.type = "pipe",
		.mode = S_IFIFO
	पूर्ण,
	[GT_SOCK] = अणु
		.type = "sock",
		.mode = S_IFSOCK
	पूर्ण
पूर्ण;

अटल पूर्णांक cpio_mkgeneric_line(स्थिर अक्षर *line, क्रमागत generic_types gt)
अणु
	अक्षर name[PATH_MAX + 1];
	अचिन्हित पूर्णांक mode;
	पूर्णांक uid;
	पूर्णांक gid;
	पूर्णांक rc = -1;

	अगर (4 != माला_पूछो(line, "%" str(PATH_MAX) "s %o %d %d", name, &mode, &uid, &gid)) अणु
		ख_लिखो(मानक_त्रुटि, "Unrecognized %s format '%s'",
			line, generic_type_table[gt].type);
		जाओ fail;
	पूर्ण
	mode |= generic_type_table[gt].mode;
	rc = cpio_mkgeneric(name, mode, uid, gid);
 fail:
	वापस rc;
पूर्ण

अटल पूर्णांक cpio_सूची_गढ़ो_line(स्थिर अक्षर *line)
अणु
	वापस cpio_mkgeneric_line(line, GT_सूची);
पूर्ण

अटल पूर्णांक cpio_mkpipe_line(स्थिर अक्षर *line)
अणु
	वापस cpio_mkgeneric_line(line, GT_PIPE);
पूर्ण

अटल पूर्णांक cpio_mksock_line(स्थिर अक्षर *line)
अणु
	वापस cpio_mkgeneric_line(line, GT_SOCK);
पूर्ण

अटल पूर्णांक cpio_mknod(स्थिर अक्षर *name, अचिन्हित पूर्णांक mode,
		       uid_t uid, gid_t gid, अक्षर dev_type,
		       अचिन्हित पूर्णांक maj, अचिन्हित पूर्णांक min)
अणु
	अक्षर s[256];

	अगर (dev_type == 'b')
		mode |= S_IFBLK;
	अन्यथा
		mode |= S_IFCHR;

	अगर (name[0] == '/')
		name++;
	प्र_लिखो(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		ino++,			/* ino */
		mode,			/* mode */
		(दीर्घ) uid,		/* uid */
		(दीर्घ) gid,		/* gid */
		1,			/* nlink */
		(दीर्घ) शेष_mसमय,	/* mसमय */
		0,			/* filesize */
		3,			/* major */
		1,			/* minor */
		maj,			/* rmajor */
		min,			/* rminor */
		(अचिन्हित)म_माप(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_rest(name);
	वापस 0;
पूर्ण

अटल पूर्णांक cpio_mknod_line(स्थिर अक्षर *line)
अणु
	अक्षर name[PATH_MAX + 1];
	अचिन्हित पूर्णांक mode;
	पूर्णांक uid;
	पूर्णांक gid;
	अक्षर dev_type;
	अचिन्हित पूर्णांक maj;
	अचिन्हित पूर्णांक min;
	पूर्णांक rc = -1;

	अगर (7 != माला_पूछो(line, "%" str(PATH_MAX) "s %o %d %d %c %u %u",
			 name, &mode, &uid, &gid, &dev_type, &maj, &min)) अणु
		ख_लिखो(मानक_त्रुटि, "Unrecognized nod format '%s'", line);
		जाओ fail;
	पूर्ण
	rc = cpio_mknod(name, mode, uid, gid, dev_type, maj, min);
 fail:
	वापस rc;
पूर्ण

अटल पूर्णांक cpio_mkfile(स्थिर अक्षर *name, स्थिर अक्षर *location,
			अचिन्हित पूर्णांक mode, uid_t uid, gid_t gid,
			अचिन्हित पूर्णांक nlinks)
अणु
	अक्षर s[256];
	अक्षर *filebuf = शून्य;
	काष्ठा stat buf;
	दीर्घ size;
	पूर्णांक file = -1;
	पूर्णांक retval;
	पूर्णांक rc = -1;
	पूर्णांक namesize;
	अचिन्हित पूर्णांक i;

	mode |= S_IFREG;

	file = खोलो (location, O_RDONLY);
	अगर (file < 0) अणु
		ख_लिखो (मानक_त्रुटि, "File %s could not be opened for reading\n", location);
		जाओ error;
	पूर्ण

	retval = ख_स्थिति(file, &buf);
	अगर (retval) अणु
		ख_लिखो(मानक_त्रुटि, "File %s could not be stat()'ed\n", location);
		जाओ error;
	पूर्ण

	filebuf = दो_स्मृति(buf.st_size);
	अगर (!filebuf) अणु
		ख_लिखो (मानक_त्रुटि, "out of memory\n");
		जाओ error;
	पूर्ण

	retval = पढ़ो (file, filebuf, buf.st_size);
	अगर (retval < 0) अणु
		ख_लिखो (मानक_त्रुटि, "Can not read %s file\n", location);
		जाओ error;
	पूर्ण

	size = 0;
	क्रम (i = 1; i <= nlinks; i++) अणु
		/* data goes on last link */
		अगर (i == nlinks) size = buf.st_size;

		अगर (name[0] == '/')
			name++;
		namesize = म_माप(name) + 1;
		प्र_लिखो(s,"%s%08X%08X%08lX%08lX%08X%08lX"
		       "%08lX%08X%08X%08X%08X%08X%08X",
			"070701",		/* magic */
			ino,			/* ino */
			mode,			/* mode */
			(दीर्घ) uid,		/* uid */
			(दीर्घ) gid,		/* gid */
			nlinks,			/* nlink */
			(दीर्घ) buf.st_mसमय,	/* mसमय */
			size,			/* filesize */
			3,			/* major */
			1,			/* minor */
			0,			/* rmajor */
			0,			/* rminor */
			namesize,		/* namesize */
			0);			/* chksum */
		push_hdr(s);
		push_string(name);
		push_pad();

		अगर (size) अणु
			अगर (ख_डालो(filebuf, size, 1, मानक_निकास) != 1) अणु
				ख_लिखो(मानक_त्रुटि, "writing filebuf failed\n");
				जाओ error;
			पूर्ण
			offset += size;
			push_pad();
		पूर्ण

		name += namesize;
	पूर्ण
	ino++;
	rc = 0;
	
error:
	अगर (filebuf) मुक्त(filebuf);
	अगर (file >= 0) बंद(file);
	वापस rc;
पूर्ण

अटल अक्षर *cpio_replace_env(अक्षर *new_location)
अणु
	अक्षर expanded[PATH_MAX + 1];
	अक्षर *start, *end, *var;

	जबतक ((start = म_माला(new_location, "${")) &&
	       (end = म_अक्षर(start + 2, '}'))) अणु
		*start = *end = 0;
		var = दो_पर्या(start + 2);
		snम_लिखो(expanded, माप expanded, "%s%s%s",
			 new_location, var ? var : "", end + 1);
		म_नकल(new_location, expanded);
	पूर्ण

	वापस new_location;
पूर्ण

अटल पूर्णांक cpio_mkfile_line(स्थिर अक्षर *line)
अणु
	अक्षर name[PATH_MAX + 1];
	अक्षर *dname = शून्य; /* दो_स्मृति'ed buffer क्रम hard links */
	अक्षर location[PATH_MAX + 1];
	अचिन्हित पूर्णांक mode;
	पूर्णांक uid;
	पूर्णांक gid;
	पूर्णांक nlinks = 1;
	पूर्णांक end = 0, dname_len = 0;
	पूर्णांक rc = -1;

	अगर (5 > माला_पूछो(line, "%" str(PATH_MAX) "s %" str(PATH_MAX)
				"s %o %d %d %n",
				name, location, &mode, &uid, &gid, &end)) अणु
		ख_लिखो(मानक_त्रुटि, "Unrecognized file format '%s'", line);
		जाओ fail;
	पूर्ण
	अगर (end && है_चित्र(line[end])) अणु
		पूर्णांक len;
		पूर्णांक nend;

		dname = दो_स्मृति(म_माप(line));
		अगर (!dname) अणु
			ख_लिखो (मानक_त्रुटि, "out of memory (%d)\n", dname_len);
			जाओ fail;
		पूर्ण

		dname_len = म_माप(name) + 1;
		स_नकल(dname, name, dname_len);

		करो अणु
			nend = 0;
			अगर (माला_पूछो(line + end, "%" str(PATH_MAX) "s %n",
					name, &nend) < 1)
				अवरोध;
			len = म_माप(name) + 1;
			स_नकल(dname + dname_len, name, len);
			dname_len += len;
			nlinks++;
			end += nend;
		पूर्ण जबतक (है_चित्र(line[end]));
	पूर्ण अन्यथा अणु
		dname = name;
	पूर्ण
	rc = cpio_mkfile(dname, cpio_replace_env(location),
	                 mode, uid, gid, nlinks);
 fail:
	अगर (dname_len) मुक्त(dname);
	वापस rc;
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage:\n"
		"\t%s [-t <timestamp>] <cpio_list>\n"
		"\n"
		"<cpio_list> is a file containing newline separated entries that\n"
		"describe the files to be included in the initramfs archive:\n"
		"\n"
		"# a comment\n"
		"file <name> <location> <mode> <uid> <gid> [<hard links>]\n"
		"dir <name> <mode> <uid> <gid>\n"
		"nod <name> <mode> <uid> <gid> <dev_type> <maj> <min>\n"
		"slink <name> <target> <mode> <uid> <gid>\n"
		"pipe <name> <mode> <uid> <gid>\n"
		"sock <name> <mode> <uid> <gid>\n"
		"\n"
		"<name>       name of the file/dir/nod/etc in the archive\n"
		"<location>   location of the file in the current filesystem\n"
		"             expands shell variables quoted with ${}\n"
		"<target>     link target\n"
		"<mode>       mode/permissions of the file\n"
		"<uid>        user id (0=root)\n"
		"<gid>        group id (0=root)\n"
		"<dev_type>   device type (b=block, c=character)\n"
		"<maj>        major number of nod\n"
		"<min>        minor number of nod\n"
		"<hard links> space separated list of other links to file\n"
		"\n"
		"example:\n"
		"# A simple initramfs\n"
		"dir /dev 0755 0 0\n"
		"nod /dev/console 0600 0 0 c 5 1\n"
		"dir /root 0700 0 0\n"
		"dir /sbin 0755 0 0\n"
		"file /sbin/kinit /usr/src/klibc/kinit/kinit 0755 0 0\n"
		"\n"
		"<timestamp> is time in seconds since Epoch that will be used\n"
		"as mtime for symlinks, special files and directories. The default\n"
		"is to use the current time for these entries.\n",
		prog);
पूर्ण

काष्ठा file_handler file_handler_table[] = अणु
	अणु
		.type    = "file",
		.handler = cpio_mkfile_line,
	पूर्ण, अणु
		.type    = "nod",
		.handler = cpio_mknod_line,
	पूर्ण, अणु
		.type    = "dir",
		.handler = cpio_सूची_गढ़ो_line,
	पूर्ण, अणु
		.type    = "slink",
		.handler = cpio_mkslink_line,
	पूर्ण, अणु
		.type    = "pipe",
		.handler = cpio_mkpipe_line,
	पूर्ण, अणु
		.type    = "sock",
		.handler = cpio_mksock_line,
	पूर्ण, अणु
		.type    = शून्य,
		.handler = शून्य,
	पूर्ण
पूर्ण;

#घोषणा LINE_SIZE (2 * PATH_MAX + 50)

पूर्णांक मुख्य (पूर्णांक argc, अक्षर *argv[])
अणु
	खाता *cpio_list;
	अक्षर line[LINE_SIZE];
	अक्षर *args, *type;
	पूर्णांक ec = 0;
	पूर्णांक line_nr = 0;
	स्थिर अक्षर *filename;

	शेष_mसमय = समय(शून्य);
	जबतक (1) अणु
		पूर्णांक opt = getopt(argc, argv, "t:h");
		अक्षर *invalid;

		अगर (opt == -1)
			अवरोध;
		चयन (opt) अणु
		हाल 't':
			शेष_mसमय = म_से_दीर्घ(optarg, &invalid, 10);
			अगर (!*optarg || *invalid) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid timestamp: %s\n",
						optarg);
				usage(argv[0]);
				निकास(1);
			पूर्ण
			अवरोध;
		हाल 'h':
		हाल '?':
			usage(argv[0]);
			निकास(opt == 'h' ? 0 : 1);
		पूर्ण
	पूर्ण

	अगर (argc - optind != 1) अणु
		usage(argv[0]);
		निकास(1);
	पूर्ण
	filename = argv[optind];
	अगर (!म_भेद(filename, "-"))
		cpio_list = मानक_निवेश;
	अन्यथा अगर (!(cpio_list = ख_खोलो(filename, "r"))) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: unable to open '%s': %s\n\n",
			filename, म_त्रुटि(त्रुटि_सं));
		usage(argv[0]);
		निकास(1);
	पूर्ण

	जबतक (ख_माला_लो(line, LINE_SIZE, cpio_list)) अणु
		पूर्णांक type_idx;
		माप_प्रकार slen = म_माप(line);

		line_nr++;

		अगर ('#' == *line) अणु
			/* comment - skip to next line */
			जारी;
		पूर्ण

		अगर (! (type = म_मोहर(line, " \t"))) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: incorrect format, could not locate file type line %d: '%s'\n",
				line_nr, line);
			ec = -1;
			अवरोध;
		पूर्ण

		अगर ('\n' == *type) अणु
			/* a blank line */
			जारी;
		पूर्ण

		अगर (slen == म_माप(type)) अणु
			/* must be an empty line */
			जारी;
		पूर्ण

		अगर (! (args = म_मोहर(शून्य, "\n"))) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: incorrect format, newline required line %d: '%s'\n",
				line_nr, line);
			ec = -1;
		पूर्ण

		क्रम (type_idx = 0; file_handler_table[type_idx].type; type_idx++) अणु
			पूर्णांक rc;
			अगर (! म_भेद(line, file_handler_table[type_idx].type)) अणु
				अगर ((rc = file_handler_table[type_idx].handler(args))) अणु
					ec = rc;
					ख_लिखो(मानक_त्रुटि, " line %d\n", line_nr);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (शून्य == file_handler_table[type_idx].type) अणु
			ख_लिखो(मानक_त्रुटि, "unknown file type line %d: '%s'\n",
				line_nr, line);
		पूर्ण
	पूर्ण
	अगर (ec == 0)
		cpio_trailer();

	निकास(ec);
पूर्ण
