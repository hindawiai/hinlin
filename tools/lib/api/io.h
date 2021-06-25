<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lightweight buffered पढ़ोing library.
 *
 * Copyright 2019 Google LLC.
 */
#अगर_अघोषित __API_IO__
#घोषणा __API_IO__

#समावेश <मानककोष.स>
#समावेश <unistd.h>

काष्ठा io अणु
	/* File descriptor being पढ़ो/ */
	पूर्णांक fd;
	/* Size of the पढ़ो buffer. */
	अचिन्हित पूर्णांक buf_len;
	/* Poपूर्णांकer to storage क्रम buffering पढ़ो. */
	अक्षर *buf;
	/* End of the storage. */
	अक्षर *end;
	/* Currently accessed data poपूर्णांकer. */
	अक्षर *data;
	/* Set true on when the end of file on पढ़ो error. */
	bool eof;
पूर्ण;

अटल अंतरभूत व्योम io__init(काष्ठा io *io, पूर्णांक fd,
			    अक्षर *buf, अचिन्हित पूर्णांक buf_len)
अणु
	io->fd = fd;
	io->buf_len = buf_len;
	io->buf = buf;
	io->end = buf;
	io->data = buf;
	io->eof = false;
पूर्ण

/* Reads one अक्षरacter from the "io" file with similar semantics to ख_अक्षर_लो. */
अटल अंतरभूत पूर्णांक io__get_अक्षर(काष्ठा io *io)
अणु
	अक्षर *ptr = io->data;

	अगर (io->eof)
		वापस -1;

	अगर (ptr == io->end) अणु
		sमाप_प्रकार n = पढ़ो(io->fd, io->buf, io->buf_len);

		अगर (n <= 0) अणु
			io->eof = true;
			वापस -1;
		पूर्ण
		ptr = &io->buf[0];
		io->end = &io->buf[n];
	पूर्ण
	io->data = ptr + 1;
	वापस *ptr;
पूर्ण

/* Read a hexadecimal value with no 0x prefix पूर्णांकo the out argument hex. If the
 * first अक्षरacter isn't hexadecimal वापसs -2, io->eof वापसs -1, otherwise
 * वापसs the अक्षरacter after the hexadecimal value which may be -1 क्रम eof.
 * If the पढ़ो value is larger than a u64 the high-order bits will be dropped.
 */
अटल अंतरभूत पूर्णांक io__get_hex(काष्ठा io *io, __u64 *hex)
अणु
	bool first_पढ़ो = true;

	*hex = 0;
	जबतक (true) अणु
		पूर्णांक ch = io__get_अक्षर(io);

		अगर (ch < 0)
			वापस ch;
		अगर (ch >= '0' && ch <= '9')
			*hex = (*hex << 4) | (ch - '0');
		अन्यथा अगर (ch >= 'a' && ch <= 'f')
			*hex = (*hex << 4) | (ch - 'a' + 10);
		अन्यथा अगर (ch >= 'A' && ch <= 'F')
			*hex = (*hex << 4) | (ch - 'A' + 10);
		अन्यथा अगर (first_पढ़ो)
			वापस -2;
		अन्यथा
			वापस ch;
		first_पढ़ो = false;
	पूर्ण
पूर्ण

/* Read a positive decimal value with out argument dec. If the first अक्षरacter
 * isn't a decimal वापसs -2, io->eof वापसs -1, otherwise वापसs the
 * अक्षरacter after the decimal value which may be -1 क्रम eof. If the पढ़ो value
 * is larger than a u64 the high-order bits will be dropped.
 */
अटल अंतरभूत पूर्णांक io__get_dec(काष्ठा io *io, __u64 *dec)
अणु
	bool first_पढ़ो = true;

	*dec = 0;
	जबतक (true) अणु
		पूर्णांक ch = io__get_अक्षर(io);

		अगर (ch < 0)
			वापस ch;
		अगर (ch >= '0' && ch <= '9')
			*dec = (*dec * 10) + ch - '0';
		अन्यथा अगर (first_पढ़ो)
			वापस -2;
		अन्यथा
			वापस ch;
		first_पढ़ो = false;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __API_IO__ */
