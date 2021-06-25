<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple test program that demonstrates a file copy through io_uring. This
 * uses the API exposed by liburing.
 *
 * Copyright (C) 2018-2019 Jens Axboe
 */
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/ioctl.h>

#समावेश "liburing.h"

#घोषणा QD	64
#घोषणा BS	(32*1024)

अटल पूर्णांक infd, outfd;

काष्ठा io_data अणु
	पूर्णांक पढ़ो;
	off_t first_offset, offset;
	माप_प्रकार first_len;
	काष्ठा iovec iov;
पूर्ण;

अटल पूर्णांक setup_context(अचिन्हित entries, काष्ठा io_uring *ring)
अणु
	पूर्णांक ret;

	ret = io_uring_queue_init(entries, ring, 0);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "queue_init: %s\n", म_त्रुटि(-ret));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_file_size(पूर्णांक fd, off_t *size)
अणु
	काष्ठा stat st;

	अगर (ख_स्थिति(fd, &st) < 0)
		वापस -1;
	अगर (S_ISREG(st.st_mode)) अणु
		*size = st.st_size;
		वापस 0;
	पूर्ण अन्यथा अगर (S_ISBLK(st.st_mode)) अणु
		अचिन्हित दीर्घ दीर्घ bytes;

		अगर (ioctl(fd, BLKGETSIZE64, &bytes) != 0)
			वापस -1;

		*size = bytes;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम queue_prepped(काष्ठा io_uring *ring, काष्ठा io_data *data)
अणु
	काष्ठा io_uring_sqe *sqe;

	sqe = io_uring_get_sqe(ring);
	निश्चित(sqe);

	अगर (data->पढ़ो)
		io_uring_prep_पढ़ोv(sqe, infd, &data->iov, 1, data->offset);
	अन्यथा
		io_uring_prep_ग_लिखोv(sqe, outfd, &data->iov, 1, data->offset);

	io_uring_sqe_set_data(sqe, data);
पूर्ण

अटल पूर्णांक queue_पढ़ो(काष्ठा io_uring *ring, off_t size, off_t offset)
अणु
	काष्ठा io_uring_sqe *sqe;
	काष्ठा io_data *data;

	data = दो_स्मृति(size + माप(*data));
	अगर (!data)
		वापस 1;

	sqe = io_uring_get_sqe(ring);
	अगर (!sqe) अणु
		मुक्त(data);
		वापस 1;
	पूर्ण

	data->पढ़ो = 1;
	data->offset = data->first_offset = offset;

	data->iov.iov_base = data + 1;
	data->iov.iov_len = size;
	data->first_len = size;

	io_uring_prep_पढ़ोv(sqe, infd, &data->iov, 1, offset);
	io_uring_sqe_set_data(sqe, data);
	वापस 0;
पूर्ण

अटल व्योम queue_ग_लिखो(काष्ठा io_uring *ring, काष्ठा io_data *data)
अणु
	data->पढ़ो = 0;
	data->offset = data->first_offset;

	data->iov.iov_base = data + 1;
	data->iov.iov_len = data->first_len;

	queue_prepped(ring, data);
	io_uring_submit(ring);
पूर्ण

अटल पूर्णांक copy_file(काष्ठा io_uring *ring, off_t insize)
अणु
	अचिन्हित दीर्घ पढ़ोs, ग_लिखोs;
	काष्ठा io_uring_cqe *cqe;
	off_t ग_लिखो_left, offset;
	पूर्णांक ret;

	ग_लिखो_left = insize;
	ग_लिखोs = पढ़ोs = offset = 0;

	जबतक (insize || ग_लिखो_left) अणु
		अचिन्हित दीर्घ had_पढ़ोs;
		पूर्णांक got_comp;

		/*
		 * Queue up as many पढ़ोs as we can
		 */
		had_पढ़ोs = पढ़ोs;
		जबतक (insize) अणु
			off_t this_size = insize;

			अगर (पढ़ोs + ग_लिखोs >= QD)
				अवरोध;
			अगर (this_size > BS)
				this_size = BS;
			अन्यथा अगर (!this_size)
				अवरोध;

			अगर (queue_पढ़ो(ring, this_size, offset))
				अवरोध;

			insize -= this_size;
			offset += this_size;
			पढ़ोs++;
		पूर्ण

		अगर (had_पढ़ोs != पढ़ोs) अणु
			ret = io_uring_submit(ring);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि, "io_uring_submit: %s\n", म_त्रुटि(-ret));
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Queue is full at this poपूर्णांक. Find at least one completion.
		 */
		got_comp = 0;
		जबतक (ग_लिखो_left) अणु
			काष्ठा io_data *data;

			अगर (!got_comp) अणु
				ret = io_uring_रुको_cqe(ring, &cqe);
				got_comp = 1;
			पूर्ण अन्यथा
				ret = io_uring_peek_cqe(ring, &cqe);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि, "io_uring_peek_cqe: %s\n",
							म_त्रुटि(-ret));
				वापस 1;
			पूर्ण
			अगर (!cqe)
				अवरोध;

			data = io_uring_cqe_get_data(cqe);
			अगर (cqe->res < 0) अणु
				अगर (cqe->res == -EAGAIN) अणु
					queue_prepped(ring, data);
					io_uring_cqe_seen(ring, cqe);
					जारी;
				पूर्ण
				ख_लिखो(मानक_त्रुटि, "cqe failed: %s\n",
						म_त्रुटि(-cqe->res));
				वापस 1;
			पूर्ण अन्यथा अगर ((माप_प्रकार) cqe->res != data->iov.iov_len) अणु
				/* Short पढ़ो/ग_लिखो, adjust and requeue */
				data->iov.iov_base += cqe->res;
				data->iov.iov_len -= cqe->res;
				data->offset += cqe->res;
				queue_prepped(ring, data);
				io_uring_cqe_seen(ring, cqe);
				जारी;
			पूर्ण

			/*
			 * All करोne. अगर ग_लिखो, nothing अन्यथा to करो. अगर पढ़ो,
			 * queue up corresponding ग_लिखो.
			 */
			अगर (data->पढ़ो) अणु
				queue_ग_लिखो(ring, data);
				ग_लिखो_left -= data->first_len;
				पढ़ोs--;
				ग_लिखोs++;
			पूर्ण अन्यथा अणु
				मुक्त(data);
				ग_लिखोs--;
			पूर्ण
			io_uring_cqe_seen(ring, cqe);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा io_uring ring;
	off_t insize;
	पूर्णांक ret;

	अगर (argc < 3) अणु
		म_लिखो("%s: infile outfile\n", argv[0]);
		वापस 1;
	पूर्ण

	infd = खोलो(argv[1], O_RDONLY);
	अगर (infd < 0) अणु
		लिखो_त्रुटि("open infile");
		वापस 1;
	पूर्ण
	outfd = खोलो(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	अगर (outfd < 0) अणु
		लिखो_त्रुटि("open outfile");
		वापस 1;
	पूर्ण

	अगर (setup_context(QD, &ring))
		वापस 1;
	अगर (get_file_size(infd, &insize))
		वापस 1;

	ret = copy_file(&ring, insize);

	बंद(infd);
	बंद(outfd);
	io_uring_queue_निकास(&ring);
	वापस ret;
पूर्ण
