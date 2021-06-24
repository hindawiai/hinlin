<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <fcntl.h>
#समावेश <समय.स>
#समावेश <sys/ioctl.h>
#समावेश <linux/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/types.h>
#समावेश <linux/spi/spidev.h>

#घोषणा ARRAY_SIZE(a) (माप(a) / माप((a)[0]))

अटल व्योम pपात(स्थिर अक्षर *s)
अणु
	अगर (त्रुटि_सं != 0)
		लिखो_त्रुटि(s);
	अन्यथा
		म_लिखो("%s\n", s);

	पात();
पूर्ण

अटल स्थिर अक्षर *device = "/dev/spidev1.1";
अटल uपूर्णांक32_t mode;
अटल uपूर्णांक8_t bits = 8;
अटल अक्षर *input_file;
अटल अक्षर *output_file;
अटल uपूर्णांक32_t speed = 500000;
अटल uपूर्णांक16_t delay;
अटल पूर्णांक verbose;
अटल पूर्णांक transfer_size;
अटल पूर्णांक iterations;
अटल पूर्णांक पूर्णांकerval = 5; /* पूर्णांकerval in seconds क्रम showing transfer rate */

अटल uपूर्णांक8_t शेष_tx[] = अणु
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0x0D,
पूर्ण;

अटल uपूर्णांक8_t शेष_rx[ARRAY_SIZE(शेष_tx)] = अणु0, पूर्ण;
अटल अक्षर *input_tx;

अटल व्योम hex_dump(स्थिर व्योम *src, माप_प्रकार length, माप_प्रकार line_size,
		     अक्षर *prefix)
अणु
	पूर्णांक i = 0;
	स्थिर अचिन्हित अक्षर *address = src;
	स्थिर अचिन्हित अक्षर *line = address;
	अचिन्हित अक्षर c;

	म_लिखो("%s | ", prefix);
	जबतक (length-- > 0) अणु
		म_लिखो("%02X ", *address++);
		अगर (!(++i % line_size) || (length == 0 && i % line_size)) अणु
			अगर (length == 0) अणु
				जबतक (i++ % line_size)
					म_लिखो("__ ");
			पूर्ण
			म_लिखो(" |");
			जबतक (line < address) अणु
				c = *line++;
				म_लिखो("%c", (c < 32 || c > 126) ? '.' : c);
			पूर्ण
			म_लिखो("|\n");
			अगर (length > 0)
				म_लिखो("%s | ", prefix);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *  Unescape - process hexadecimal escape अक्षरacter
 *      converts shell input "\x23" -> 0x23
 */
अटल पूर्णांक unescape(अक्षर *_dst, अक्षर *_src, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक match;
	अक्षर *src = _src;
	अक्षर *dst = _dst;
	अचिन्हित पूर्णांक ch;

	जबतक (*src) अणु
		अगर (*src == '\\' && *(src+1) == 'x') अणु
			match = माला_पूछो(src + 2, "%2x", &ch);
			अगर (!match)
				pपात("malformed input string");

			src += 4;
			*dst++ = (अचिन्हित अक्षर)ch;
		पूर्ण अन्यथा अणु
			*dst++ = *src++;
		पूर्ण
		ret++;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम transfer(पूर्णांक fd, uपूर्णांक8_t स्थिर *tx, uपूर्णांक8_t स्थिर *rx, माप_प्रकार len)
अणु
	पूर्णांक ret;
	पूर्णांक out_fd;
	काष्ठा spi_ioc_transfer tr = अणु
		.tx_buf = (अचिन्हित दीर्घ)tx,
		.rx_buf = (अचिन्हित दीर्घ)rx,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	पूर्ण;

	अगर (mode & SPI_TX_OCTAL)
		tr.tx_nbits = 8;
	अन्यथा अगर (mode & SPI_TX_QUAD)
		tr.tx_nbits = 4;
	अन्यथा अगर (mode & SPI_TX_DUAL)
		tr.tx_nbits = 2;
	अगर (mode & SPI_RX_OCTAL)
		tr.rx_nbits = 8;
	अन्यथा अगर (mode & SPI_RX_QUAD)
		tr.rx_nbits = 4;
	अन्यथा अगर (mode & SPI_RX_DUAL)
		tr.rx_nbits = 2;
	अगर (!(mode & SPI_LOOP)) अणु
		अगर (mode & (SPI_TX_OCTAL | SPI_TX_QUAD | SPI_TX_DUAL))
			tr.rx_buf = 0;
		अन्यथा अगर (mode & (SPI_RX_OCTAL | SPI_RX_QUAD | SPI_RX_DUAL))
			tr.tx_buf = 0;
	पूर्ण

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	अगर (ret < 1)
		pपात("can't send spi message");

	अगर (verbose)
		hex_dump(tx, len, 32, "TX");

	अगर (output_file) अणु
		out_fd = खोलो(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		अगर (out_fd < 0)
			pपात("could not open output file");

		ret = ग_लिखो(out_fd, rx, len);
		अगर (ret != len)
			pपात("not all bytes written to output file");

		बंद(out_fd);
	पूर्ण

	अगर (verbose)
		hex_dump(rx, len, 32, "RX");
पूर्ण

अटल व्योम prपूर्णांक_usage(स्थिर अक्षर *prog)
अणु
	म_लिखो("Usage: %s [-DsbdlHOLC3vpNR24SI]\n", prog);
	माला_दो("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word\n"
	     "  -i --input    input data from a file (e.g. \"test.bin\")\n"
	     "  -o --output   output data to a file (e.g. \"results.bin\")\n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n"
	     "  -v --verbose  Verbose (show tx buffer)\n"
	     "  -p            Send data (e.g. \"1234\\xde\\xad\")\n"
	     "  -N --no-cs    no chip select\n"
	     "  -R --ready    slave pulls low to pause\n"
	     "  -2 --dual     dual transfer\n"
	     "  -4 --quad     quad transfer\n"
	     "  -8 --octal    octal transfer\n"
	     "  -S --size     transfer size\n"
	     "  -I --iter     iterations\n");
	निकास(1);
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर *argv[])
अणु
	जबतक (1) अणु
		अटल स्थिर काष्ठा option lopts[] = अणु
			अणु "device",  1, 0, 'D' पूर्ण,
			अणु "speed",   1, 0, 's' पूर्ण,
			अणु "delay",   1, 0, 'd' पूर्ण,
			अणु "bpw",     1, 0, 'b' पूर्ण,
			अणु "input",   1, 0, 'i' पूर्ण,
			अणु "output",  1, 0, 'o' पूर्ण,
			अणु "loop",    0, 0, 'l' पूर्ण,
			अणु "cpha",    0, 0, 'H' पूर्ण,
			अणु "cpol",    0, 0, 'O' पूर्ण,
			अणु "lsb",     0, 0, 'L' पूर्ण,
			अणु "cs-high", 0, 0, 'C' पूर्ण,
			अणु "3wire",   0, 0, '3' पूर्ण,
			अणु "no-cs",   0, 0, 'N' पूर्ण,
			अणु "ready",   0, 0, 'R' पूर्ण,
			अणु "dual",    0, 0, '2' पूर्ण,
			अणु "verbose", 0, 0, 'v' पूर्ण,
			अणु "quad",    0, 0, '4' पूर्ण,
			अणु "octal",   0, 0, '8' पूर्ण,
			अणु "size",    1, 0, 'S' पूर्ण,
			अणु "iter",    1, 0, 'I' पूर्ण,
			अणु शून्य, 0, 0, 0 पूर्ण,
		पूर्ण;
		पूर्णांक c;

		c = getopt_दीर्घ(argc, argv, "D:s:d:b:i:o:lHOLC3NR248p:vS:I:",
				lopts, शून्य);

		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'D':
			device = optarg;
			अवरोध;
		हाल 's':
			speed = म_से_प(optarg);
			अवरोध;
		हाल 'd':
			delay = म_से_प(optarg);
			अवरोध;
		हाल 'b':
			bits = म_से_प(optarg);
			अवरोध;
		हाल 'i':
			input_file = optarg;
			अवरोध;
		हाल 'o':
			output_file = optarg;
			अवरोध;
		हाल 'l':
			mode |= SPI_LOOP;
			अवरोध;
		हाल 'H':
			mode |= SPI_CPHA;
			अवरोध;
		हाल 'O':
			mode |= SPI_CPOL;
			अवरोध;
		हाल 'L':
			mode |= SPI_LSB_FIRST;
			अवरोध;
		हाल 'C':
			mode |= SPI_CS_HIGH;
			अवरोध;
		हाल '3':
			mode |= SPI_3WIRE;
			अवरोध;
		हाल 'N':
			mode |= SPI_NO_CS;
			अवरोध;
		हाल 'v':
			verbose = 1;
			अवरोध;
		हाल 'R':
			mode |= SPI_READY;
			अवरोध;
		हाल 'p':
			input_tx = optarg;
			अवरोध;
		हाल '2':
			mode |= SPI_TX_DUAL;
			अवरोध;
		हाल '4':
			mode |= SPI_TX_QUAD;
			अवरोध;
		हाल '8':
			mode |= SPI_TX_OCTAL;
			अवरोध;
		हाल 'S':
			transfer_size = म_से_प(optarg);
			अवरोध;
		हाल 'I':
			iterations = म_से_प(optarg);
			अवरोध;
		शेष:
			prपूर्णांक_usage(argv[0]);
		पूर्ण
	पूर्ण
	अगर (mode & SPI_LOOP) अणु
		अगर (mode & SPI_TX_DUAL)
			mode |= SPI_RX_DUAL;
		अगर (mode & SPI_TX_QUAD)
			mode |= SPI_RX_QUAD;
		अगर (mode & SPI_TX_OCTAL)
			mode |= SPI_RX_OCTAL;
	पूर्ण
पूर्ण

अटल व्योम transfer_escaped_string(पूर्णांक fd, अक्षर *str)
अणु
	माप_प्रकार size = म_माप(str);
	uपूर्णांक8_t *tx;
	uपूर्णांक8_t *rx;

	tx = दो_स्मृति(size);
	अगर (!tx)
		pपात("can't allocate tx buffer");

	rx = दो_स्मृति(size);
	अगर (!rx)
		pपात("can't allocate rx buffer");

	size = unescape((अक्षर *)tx, str, size);
	transfer(fd, tx, rx, size);
	मुक्त(rx);
	मुक्त(tx);
पूर्ण

अटल व्योम transfer_file(पूर्णांक fd, अक्षर *filename)
अणु
	sमाप_प्रकार bytes;
	काष्ठा stat sb;
	पूर्णांक tx_fd;
	uपूर्णांक8_t *tx;
	uपूर्णांक8_t *rx;

	अगर (stat(filename, &sb) == -1)
		pपात("can't stat input file");

	tx_fd = खोलो(filename, O_RDONLY);
	अगर (tx_fd < 0)
		pपात("can't open input file");

	tx = दो_स्मृति(sb.st_size);
	अगर (!tx)
		pपात("can't allocate tx buffer");

	rx = दो_स्मृति(sb.st_size);
	अगर (!rx)
		pपात("can't allocate rx buffer");

	bytes = पढ़ो(tx_fd, tx, sb.st_size);
	अगर (bytes != sb.st_size)
		pपात("failed to read input file");

	transfer(fd, tx, rx, sb.st_size);
	मुक्त(rx);
	मुक्त(tx);
	बंद(tx_fd);
पूर्ण

अटल uपूर्णांक64_t _पढ़ो_count;
अटल uपूर्णांक64_t _ग_लिखो_count;

अटल व्योम show_transfer_rate(व्योम)
अणु
	अटल uपूर्णांक64_t prev_पढ़ो_count, prev_ग_लिखो_count;
	द्विगुन rx_rate, tx_rate;

	rx_rate = ((_पढ़ो_count - prev_पढ़ो_count) * 8) / (पूर्णांकerval*1000.0);
	tx_rate = ((_ग_लिखो_count - prev_ग_लिखो_count) * 8) / (पूर्णांकerval*1000.0);

	म_लिखो("rate: tx %.1fkbps, rx %.1fkbps\n", rx_rate, tx_rate);

	prev_पढ़ो_count = _पढ़ो_count;
	prev_ग_लिखो_count = _ग_लिखो_count;
पूर्ण

अटल व्योम transfer_buf(पूर्णांक fd, पूर्णांक len)
अणु
	uपूर्णांक8_t *tx;
	uपूर्णांक8_t *rx;
	पूर्णांक i;

	tx = दो_स्मृति(len);
	अगर (!tx)
		pपात("can't allocate tx buffer");
	क्रम (i = 0; i < len; i++)
		tx[i] = अक्रमom();

	rx = दो_स्मृति(len);
	अगर (!rx)
		pपात("can't allocate rx buffer");

	transfer(fd, tx, rx, len);

	_ग_लिखो_count += len;
	_पढ़ो_count += len;

	अगर (mode & SPI_LOOP) अणु
		अगर (स_भेद(tx, rx, len)) अणु
			ख_लिखो(मानक_त्रुटि, "transfer error !\n");
			hex_dump(tx, len, 32, "TX");
			hex_dump(rx, len, 32, "RX");
			निकास(1);
		पूर्ण
	पूर्ण

	मुक्त(rx);
	मुक्त(tx);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret = 0;
	पूर्णांक fd;

	parse_opts(argc, argv);

	अगर (input_tx && input_file)
		pपात("only one of -p and --input may be selected");

	fd = खोलो(device, O_RDWR);
	अगर (fd < 0)
		pपात("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode);
	अगर (ret == -1)
		pपात("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode);
	अगर (ret == -1)
		pपात("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	अगर (ret == -1)
		pपात("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	अगर (ret == -1)
		pपात("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	अगर (ret == -1)
		pपात("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	अगर (ret == -1)
		pपात("can't get max speed hz");

	म_लिखो("spi mode: 0x%x\n", mode);
	म_लिखो("bits per word: %u\n", bits);
	म_लिखो("max speed: %u Hz (%u kHz)\n", speed, speed/1000);

	अगर (input_tx)
		transfer_escaped_string(fd, input_tx);
	अन्यथा अगर (input_file)
		transfer_file(fd, input_file);
	अन्यथा अगर (transfer_size) अणु
		काष्ठा बारpec last_stat;

		घड़ी_समय_लो(CLOCK_MONOTONIC, &last_stat);

		जबतक (iterations-- > 0) अणु
			काष्ठा बारpec current;

			transfer_buf(fd, transfer_size);

			घड़ी_समय_लो(CLOCK_MONOTONIC, &current);
			अगर (current.tv_sec - last_stat.tv_sec > पूर्णांकerval) अणु
				show_transfer_rate();
				last_stat = current;
			पूर्ण
		पूर्ण
		म_लिखो("total: tx %.1fKB, rx %.1fKB\n",
		       _ग_लिखो_count/1024.0, _पढ़ो_count/1024.0);
	पूर्ण अन्यथा
		transfer(fd, शेष_tx, शेष_rx, माप(शेष_tx));

	बंद(fd);

	वापस ret;
पूर्ण
