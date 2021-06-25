<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Makes a tree bootable image क्रम IBM Evaluation boards.
 * Basically, just take a zImage, skip the ELF header, and stuff
 * a 32 byte header on the front.
 *
 * We use htonl, which is a network macro, to make sure we're करोing
 * The Right Thing on an LE machine.  It's non-obvious, but it should
 * work on anything BSD'ish.
 */

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <netinet/in.h>
#अगर_घोषित __sun__
#समावेश <पूर्णांकtypes.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

/* This माला_लो tacked on the front of the image.  There are also a few
 * bytes allocated after the _start label used by the boot rom (see
 * head.S क्रम details).
 */
प्रकार काष्ठा boot_block अणु
	uपूर्णांक32_t bb_magic;		/* 0x0052504F */
	uपूर्णांक32_t bb_dest;		/* Target address of the image */
	uपूर्णांक32_t bb_num_512blocks;	/* Size, rounded-up, in 512 byte blks */
	uपूर्णांक32_t bb_debug_flag;	/* Run debugger or image after load */
	uपूर्णांक32_t bb_entry_poपूर्णांक;	/* The image address to start */
	uपूर्णांक32_t bb_checksum;	/* 32 bit checksum including header */
	uपूर्णांक32_t reserved[2];
पूर्ण boot_block_t;

#घोषणा IMGBLK	512
अचिन्हित पूर्णांक	पंचांगpbuf[IMGBLK / माप(अचिन्हित पूर्णांक)];

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक	in_fd, out_fd;
	पूर्णांक	nblks, i;
	अचिन्हित पूर्णांक	cksum, *cp;
	काष्ठा	stat	st;
	boot_block_t	bt;

	अगर (argc < 5) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s <zImage-file> <boot-image> <load address> <entry point>\n",argv[0]);
		निकास(1);
	पूर्ण

	अगर (stat(argv[1], &st) < 0) अणु
		लिखो_त्रुटि("stat");
		निकास(2);
	पूर्ण

	nblks = (st.st_size + IMGBLK) / IMGBLK;

	bt.bb_magic = htonl(0x0052504F);

	/* If we have the optional entry poपूर्णांक parameter, use it */
	bt.bb_dest = htonl(म_से_अदीर्घ(argv[3], शून्य, 0));
	bt.bb_entry_poपूर्णांक = htonl(म_से_अदीर्घ(argv[4], शून्य, 0));

	/* We know these from the linker command.
	 * ...and then move it up पूर्णांकo memory a little more so the
	 * relocation can happen.
	 */
	bt.bb_num_512blocks = htonl(nblks);
	bt.bb_debug_flag = 0;

	bt.bb_checksum = 0;

	/* To be neat and tidy :-).
	*/
	bt.reserved[0] = 0;
	bt.reserved[1] = 0;

	अगर ((in_fd = खोलो(argv[1], O_RDONLY)) < 0) अणु
		लिखो_त्रुटि("zImage open");
		निकास(3);
	पूर्ण

	अगर ((out_fd = खोलो(argv[2], (O_RDWR | O_CREAT | O_TRUNC), 0666)) < 0) अणु
		लिखो_त्रुटि("bootfile open");
		निकास(3);
	पूर्ण

	cksum = 0;
	cp = (व्योम *)&bt;
	क्रम (i = 0; i < माप(bt) / माप(अचिन्हित पूर्णांक); i++)
		cksum += *cp++;

	/* Assume zImage is an ELF file, and skip the 64K header.
	*/
	अगर (पढ़ो(in_fd, पंचांगpbuf, माप(पंचांगpbuf)) != माप(पंचांगpbuf)) अणु
		ख_लिखो(मानक_त्रुटि, "%s is too small to be an ELF image\n",
				argv[1]);
		निकास(4);
	पूर्ण

	अगर (पंचांगpbuf[0] != htonl(0x7f454c46)) अणु
		ख_लिखो(मानक_त्रुटि, "%s is not an ELF image\n", argv[1]);
		निकास(4);
	पूर्ण

	अगर (lseek(in_fd, (64 * 1024), शुरू_से) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s failed to seek in ELF image\n", argv[1]);
		निकास(4);
	पूर्ण

	nblks -= (64 * 1024) / IMGBLK;

	/* And away we go......
	*/
	अगर (ग_लिखो(out_fd, &bt, माप(bt)) != माप(bt)) अणु
		लिखो_त्रुटि("boot-image write");
		निकास(5);
	पूर्ण

	जबतक (nblks-- > 0) अणु
		अगर (पढ़ो(in_fd, पंचांगpbuf, माप(पंचांगpbuf)) < 0) अणु
			लिखो_त्रुटि("zImage read");
			निकास(5);
		पूर्ण
		cp = पंचांगpbuf;
		क्रम (i = 0; i < माप(पंचांगpbuf) / माप(अचिन्हित पूर्णांक); i++)
			cksum += *cp++;
		अगर (ग_लिखो(out_fd, पंचांगpbuf, माप(पंचांगpbuf)) != माप(पंचांगpbuf)) अणु
			लिखो_त्रुटि("boot-image write");
			निकास(5);
		पूर्ण
	पूर्ण

	/* reग_लिखो the header with the computed checksum.
	*/
	bt.bb_checksum = htonl(cksum);
	अगर (lseek(out_fd, 0, शुरू_से) < 0) अणु
		लिखो_त्रुटि("rewrite seek");
		निकास(1);
	पूर्ण
	अगर (ग_लिखो(out_fd, &bt, माप(bt)) != माप(bt)) अणु
		लिखो_त्रुटि("boot-image rewrite");
		निकास(1);
	पूर्ण

	निकास(0);
पूर्ण
