<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <fcntl.h>
#समावेश <माला.स>

#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#समावेश <linux/types.h>
#समावेश <linux/spi/spidev.h>


अटल पूर्णांक verbose;

अटल व्योम करो_पढ़ो(पूर्णांक fd, पूर्णांक len)
अणु
	अचिन्हित अक्षर	buf[32], *bp;
	पूर्णांक		status;

	/* पढ़ो at least 2 bytes, no more than 32 */
	अगर (len < 2)
		len = 2;
	अन्यथा अगर (len > माप(buf))
		len = माप(buf);
	स_रखो(buf, 0, माप buf);

	status = पढ़ो(fd, buf, len);
	अगर (status < 0) अणु
		लिखो_त्रुटि("read");
		वापस;
	पूर्ण
	अगर (status != len) अणु
		ख_लिखो(मानक_त्रुटि, "short read\n");
		वापस;
	पूर्ण

	म_लिखो("read(%2d, %2d): %02x %02x,", len, status,
		buf[0], buf[1]);
	status -= 2;
	bp = buf + 2;
	जबतक (status-- > 0)
		म_लिखो(" %02x", *bp++);
	म_लिखो("\n");
पूर्ण

अटल व्योम करो_msg(पूर्णांक fd, पूर्णांक len)
अणु
	काष्ठा spi_ioc_transfer	xfer[2];
	अचिन्हित अक्षर		buf[32], *bp;
	पूर्णांक			status;

	स_रखो(xfer, 0, माप xfer);
	स_रखो(buf, 0, माप buf);

	अगर (len > माप buf)
		len = माप buf;

	buf[0] = 0xaa;
	xfer[0].tx_buf = (अचिन्हित दीर्घ)buf;
	xfer[0].len = 1;

	xfer[1].rx_buf = (अचिन्हित दीर्घ) buf;
	xfer[1].len = len;

	status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
	अगर (status < 0) अणु
		लिखो_त्रुटि("SPI_IOC_MESSAGE");
		वापस;
	पूर्ण

	म_लिखो("response(%2d, %2d): ", len, status);
	क्रम (bp = buf; len; len--)
		म_लिखो(" %02x", *bp++);
	म_लिखो("\n");
पूर्ण

अटल व्योम dumpstat(स्थिर अक्षर *name, पूर्णांक fd)
अणु
	__u8	lsb, bits;
	__u32	mode, speed;

	अगर (ioctl(fd, SPI_IOC_RD_MODE32, &mode) < 0) अणु
		लिखो_त्रुटि("SPI rd_mode");
		वापस;
	पूर्ण
	अगर (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) अणु
		लिखो_त्रुटि("SPI rd_lsb_fist");
		वापस;
	पूर्ण
	अगर (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) अणु
		लिखो_त्रुटि("SPI bits_per_word");
		वापस;
	पूर्ण
	अगर (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) अणु
		लिखो_त्रुटि("SPI max_speed_hz");
		वापस;
	पूर्ण

	म_लिखो("%s: spi mode 0x%x, %d bits %sper word, %d Hz max\n",
		name, mode, bits, lsb ? "(lsb first) " : "", speed);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक		c;
	पूर्णांक		पढ़ोcount = 0;
	पूर्णांक		msglen = 0;
	पूर्णांक		fd;
	स्थिर अक्षर	*name;

	जबतक ((c = getopt(argc, argv, "hm:r:v")) != खातापूर्ण) अणु
		चयन (c) अणु
		हाल 'm':
			msglen = म_से_प(optarg);
			अगर (msglen < 0)
				जाओ usage;
			जारी;
		हाल 'r':
			पढ़ोcount = म_से_प(optarg);
			अगर (पढ़ोcount < 0)
				जाओ usage;
			जारी;
		हाल 'v':
			verbose++;
			जारी;
		हाल 'h':
		हाल '?':
usage:
			ख_लिखो(मानक_त्रुटि,
				"usage: %s [-h] [-m N] [-r N] /dev/spidevB.D\n",
				argv[0]);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर ((optind + 1) != argc)
		जाओ usage;
	name = argv[optind];

	fd = खोलो(name, O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("open");
		वापस 1;
	पूर्ण

	dumpstat(name, fd);

	अगर (msglen)
		करो_msg(fd, msglen);

	अगर (पढ़ोcount)
		करो_पढ़ो(fd, पढ़ोcount);

	बंद(fd);
	वापस 0;
पूर्ण
