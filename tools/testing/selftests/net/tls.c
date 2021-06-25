<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश <linux/tls.h>
#समावेश <linux/tcp.h>
#समावेश <linux/socket.h>

#समावेश <sys/types.h>
#समावेश <sys/sendfile.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>

#समावेश "../kselftest_harness.h"

#घोषणा TLS_PAYLOAD_MAX_LEN 16384
#घोषणा SOL_TLS 282

FIXTURE(tls_basic)
अणु
	पूर्णांक fd, cfd;
	bool notls;
पूर्ण;

FIXTURE_SETUP(tls_basic)
अणु
	काष्ठा sockaddr_in addr;
	socklen_t len;
	पूर्णांक sfd, ret;

	self->notls = false;
	len = माप(addr);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	self->fd = socket(AF_INET, SOCK_STREAM, 0);
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	ret = bind(sfd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);
	ret = listen(sfd, 10);
	ASSERT_EQ(ret, 0);

	ret = माला_लोockname(sfd, &addr, &len);
	ASSERT_EQ(ret, 0);

	ret = connect(self->fd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);

	self->cfd = accept(sfd, &addr, &len);
	ASSERT_GE(self->cfd, 0);

	बंद(sfd);

	ret = setsockopt(self->fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	अगर (ret != 0) अणु
		ASSERT_EQ(त्रुटि_सं, ENOENT);
		self->notls = true;
		म_लिखो("Failure setting TCP_ULP, testing without tls\n");
		वापस;
	पूर्ण

	ret = setsockopt(self->cfd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	ASSERT_EQ(ret, 0);
पूर्ण

FIXTURE_TEARDOWN(tls_basic)
अणु
	बंद(self->fd);
	बंद(self->cfd);
पूर्ण

/* Send some data through with ULP but no keys */
TEST_F(tls_basic, base_base)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10];

	ASSERT_EQ(म_माप(test_str) + 1, send_len);

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण;

FIXTURE(tls)
अणु
	पूर्णांक fd, cfd;
	bool notls;
पूर्ण;

FIXTURE_VARIANT(tls)
अणु
	uपूर्णांक16_t tls_version;
	uपूर्णांक16_t cipher_type;
पूर्ण;

FIXTURE_VARIANT_ADD(tls, 12_gcm)
अणु
	.tls_version = TLS_1_2_VERSION,
	.cipher_type = TLS_CIPHER_AES_GCM_128,
पूर्ण;

FIXTURE_VARIANT_ADD(tls, 13_gcm)
अणु
	.tls_version = TLS_1_3_VERSION,
	.cipher_type = TLS_CIPHER_AES_GCM_128,
पूर्ण;

FIXTURE_VARIANT_ADD(tls, 12_chacha)
अणु
	.tls_version = TLS_1_2_VERSION,
	.cipher_type = TLS_CIPHER_CHACHA20_POLY1305,
पूर्ण;

FIXTURE_VARIANT_ADD(tls, 13_chacha)
अणु
	.tls_version = TLS_1_3_VERSION,
	.cipher_type = TLS_CIPHER_CHACHA20_POLY1305,
पूर्ण;

FIXTURE_SETUP(tls)
अणु
	जोड़ अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 aes128;
		काष्ठा tls12_crypto_info_chacha20_poly1305 chacha20;
	पूर्ण tls12;
	काष्ठा sockaddr_in addr;
	socklen_t len;
	पूर्णांक sfd, ret;
	माप_प्रकार tls12_sz;

	self->notls = false;
	len = माप(addr);

	स_रखो(&tls12, 0, माप(tls12));
	चयन (variant->cipher_type) अणु
	हाल TLS_CIPHER_CHACHA20_POLY1305:
		tls12_sz = माप(काष्ठा tls12_crypto_info_chacha20_poly1305);
		tls12.chacha20.info.version = variant->tls_version;
		tls12.chacha20.info.cipher_type = variant->cipher_type;
		अवरोध;
	हाल TLS_CIPHER_AES_GCM_128:
		tls12_sz = माप(काष्ठा tls12_crypto_info_aes_gcm_128);
		tls12.aes128.info.version = variant->tls_version;
		tls12.aes128.info.cipher_type = variant->cipher_type;
		अवरोध;
	शेष:
		tls12_sz = 0;
	पूर्ण

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	self->fd = socket(AF_INET, SOCK_STREAM, 0);
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	ret = bind(sfd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);
	ret = listen(sfd, 10);
	ASSERT_EQ(ret, 0);

	ret = माला_लोockname(sfd, &addr, &len);
	ASSERT_EQ(ret, 0);

	ret = connect(self->fd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);

	ret = setsockopt(self->fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	अगर (ret != 0) अणु
		self->notls = true;
		म_लिखो("Failure setting TCP_ULP, testing without tls\n");
	पूर्ण

	अगर (!self->notls) अणु
		ret = setsockopt(self->fd, SOL_TLS, TLS_TX, &tls12,
				 tls12_sz);
		ASSERT_EQ(ret, 0);
	पूर्ण

	self->cfd = accept(sfd, &addr, &len);
	ASSERT_GE(self->cfd, 0);

	अगर (!self->notls) अणु
		ret = setsockopt(self->cfd, IPPROTO_TCP, TCP_ULP, "tls",
				 माप("tls"));
		ASSERT_EQ(ret, 0);

		ret = setsockopt(self->cfd, SOL_TLS, TLS_RX, &tls12,
				 tls12_sz);
		ASSERT_EQ(ret, 0);
	पूर्ण

	बंद(sfd);
पूर्ण

FIXTURE_TEARDOWN(tls)
अणु
	बंद(self->fd);
	बंद(self->cfd);
पूर्ण

TEST_F(tls, sendfile)
अणु
	पूर्णांक filefd = खोलो("/proc/self/exe", O_RDONLY);
	काष्ठा stat st;

	EXPECT_GE(filefd, 0);
	ख_स्थिति(filefd, &st);
	EXPECT_GE(sendfile(self->fd, filefd, 0, st.st_size), 0);
पूर्ण

TEST_F(tls, send_then_sendfile)
अणु
	पूर्णांक filefd = खोलो("/proc/self/exe", O_RDONLY);
	अक्षर स्थिर *test_str = "test_send";
	पूर्णांक to_send = म_माप(test_str) + 1;
	अक्षर recv_buf[10];
	काष्ठा stat st;
	अक्षर *buf;

	EXPECT_GE(filefd, 0);
	ख_स्थिति(filefd, &st);
	buf = (अक्षर *)दो_स्मृति(st.st_size);

	EXPECT_EQ(send(self->fd, test_str, to_send, 0), to_send);
	EXPECT_EQ(recv(self->cfd, recv_buf, to_send, MSG_WAITALL), to_send);
	EXPECT_EQ(स_भेद(test_str, recv_buf, to_send), 0);

	EXPECT_GE(sendfile(self->fd, filefd, 0, st.st_size), 0);
	EXPECT_EQ(recv(self->cfd, buf, st.st_size, MSG_WAITALL), st.st_size);
पूर्ण

अटल व्योम chunked_sendfile(काष्ठा __test_metadata *_metadata,
			     काष्ठा _test_data_tls *self,
			     uपूर्णांक16_t chunk_size,
			     uपूर्णांक16_t extra_payload_size)
अणु
	अक्षर buf[TLS_PAYLOAD_MAX_LEN];
	uपूर्णांक16_t test_payload_size;
	पूर्णांक size = 0;
	पूर्णांक ret;
	अक्षर filename[] = "/tmp/mytemp.XXXXXX";
	पूर्णांक fd = mkstemp(filename);
	off_t offset = 0;

	unlink(filename);
	ASSERT_GE(fd, 0);
	EXPECT_GE(chunk_size, 1);
	test_payload_size = chunk_size + extra_payload_size;
	ASSERT_GE(TLS_PAYLOAD_MAX_LEN, test_payload_size);
	स_रखो(buf, 1, test_payload_size);
	size = ग_लिखो(fd, buf, test_payload_size);
	EXPECT_EQ(size, test_payload_size);
	fsync(fd);

	जबतक (size > 0) अणु
		ret = sendfile(self->fd, fd, &offset, chunk_size);
		EXPECT_GE(ret, 0);
		size -= ret;
	पूर्ण

	EXPECT_EQ(recv(self->cfd, buf, test_payload_size, MSG_WAITALL),
		  test_payload_size);

	बंद(fd);
पूर्ण

TEST_F(tls, multi_chunk_sendfile)
अणु
	chunked_sendfile(_metadata, self, 4096, 4096);
	chunked_sendfile(_metadata, self, 4096, 0);
	chunked_sendfile(_metadata, self, 4096, 1);
	chunked_sendfile(_metadata, self, 4096, 2048);
	chunked_sendfile(_metadata, self, 8192, 2048);
	chunked_sendfile(_metadata, self, 4096, 8192);
	chunked_sendfile(_metadata, self, 8192, 4096);
	chunked_sendfile(_metadata, self, 12288, 1024);
	chunked_sendfile(_metadata, self, 12288, 2000);
	chunked_sendfile(_metadata, self, 15360, 100);
	chunked_sendfile(_metadata, self, 15360, 300);
	chunked_sendfile(_metadata, self, 1, 4096);
	chunked_sendfile(_metadata, self, 2048, 4096);
	chunked_sendfile(_metadata, self, 2048, 8192);
	chunked_sendfile(_metadata, self, 4096, 8192);
	chunked_sendfile(_metadata, self, 1024, 12288);
	chunked_sendfile(_metadata, self, 2000, 12288);
	chunked_sendfile(_metadata, self, 100, 15360);
	chunked_sendfile(_metadata, self, 300, 15360);
पूर्ण

TEST_F(tls, recv_max)
अणु
	अचिन्हित पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर recv_mem[TLS_PAYLOAD_MAX_LEN];
	अक्षर buf[TLS_PAYLOAD_MAX_LEN];

	EXPECT_GE(send(self->fd, buf, send_len, 0), 0);
	EXPECT_NE(recv(self->cfd, recv_mem, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, recv_mem, send_len), 0);
पूर्ण

TEST_F(tls, recv_small)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10];

	send_len = म_माप(test_str) + 1;
	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण

TEST_F(tls, msg_more)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10 * 2];

	EXPECT_EQ(send(self->fd, test_str, send_len, MSG_MORE), send_len);
	EXPECT_EQ(recv(self->cfd, buf, send_len, MSG_DONTWAIT), -1);
	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_EQ(recv(self->cfd, buf, send_len * 2, MSG_WAITALL),
		  send_len * 2);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण

TEST_F(tls, msg_more_unsent)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10];

	EXPECT_EQ(send(self->fd, test_str, send_len, MSG_MORE), send_len);
	EXPECT_EQ(recv(self->cfd, buf, send_len, MSG_DONTWAIT), -1);
पूर्ण

TEST_F(tls, sendmsg_single)
अणु
	काष्ठा msghdr msg;

	अक्षर स्थिर *test_str = "test_sendmsg";
	माप_प्रकार send_len = 13;
	काष्ठा iovec vec;
	अक्षर buf[13];

	vec.iov_base = (अक्षर *)test_str;
	vec.iov_len = send_len;
	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;
	EXPECT_EQ(sendmsg(self->fd, &msg, 0), send_len);
	EXPECT_EQ(recv(self->cfd, buf, send_len, MSG_WAITALL), send_len);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण

#घोषणा MAX_FRAGS	64
#घोषणा SEND_LEN	13
TEST_F(tls, sendmsg_fragmented)
अणु
	अक्षर स्थिर *test_str = "test_sendmsg";
	अक्षर buf[SEND_LEN * MAX_FRAGS];
	काष्ठा iovec vec[MAX_FRAGS];
	काष्ठा msghdr msg;
	पूर्णांक i, frags;

	क्रम (frags = 1; frags <= MAX_FRAGS; frags++) अणु
		क्रम (i = 0; i < frags; i++) अणु
			vec[i].iov_base = (अक्षर *)test_str;
			vec[i].iov_len = SEND_LEN;
		पूर्ण

		स_रखो(&msg, 0, माप(काष्ठा msghdr));
		msg.msg_iov = vec;
		msg.msg_iovlen = frags;

		EXPECT_EQ(sendmsg(self->fd, &msg, 0), SEND_LEN * frags);
		EXPECT_EQ(recv(self->cfd, buf, SEND_LEN * frags, MSG_WAITALL),
			  SEND_LEN * frags);

		क्रम (i = 0; i < frags; i++)
			EXPECT_EQ(स_भेद(buf + SEND_LEN * i,
					 test_str, SEND_LEN), 0);
	पूर्ण
पूर्ण
#अघोषित MAX_FRAGS
#अघोषित SEND_LEN

TEST_F(tls, sendmsg_large)
अणु
	व्योम *mem = दो_स्मृति(16384);
	माप_प्रकार send_len = 16384;
	माप_प्रकार sends = 128;
	काष्ठा msghdr msg;
	माप_प्रकार recvs = 0;
	माप_प्रकार sent = 0;

	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	जबतक (sent++ < sends) अणु
		काष्ठा iovec vec = अणु (व्योम *)mem, send_len पूर्ण;

		msg.msg_iov = &vec;
		msg.msg_iovlen = 1;
		EXPECT_EQ(sendmsg(self->cfd, &msg, 0), send_len);
	पूर्ण

	जबतक (recvs++ < sends)
		EXPECT_NE(recv(self->fd, mem, send_len, 0), -1);

	मुक्त(mem);
पूर्ण

TEST_F(tls, sendmsg_multiple)
अणु
	अक्षर स्थिर *test_str = "test_sendmsg_multiple";
	काष्ठा iovec vec[5];
	अक्षर *test_strs[5];
	काष्ठा msghdr msg;
	पूर्णांक total_len = 0;
	पूर्णांक len_cmp = 0;
	पूर्णांक iov_len = 5;
	अक्षर *buf;
	पूर्णांक i;

	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	क्रम (i = 0; i < iov_len; i++) अणु
		test_strs[i] = (अक्षर *)दो_स्मृति(म_माप(test_str) + 1);
		snम_लिखो(test_strs[i], म_माप(test_str) + 1, "%s", test_str);
		vec[i].iov_base = (व्योम *)test_strs[i];
		vec[i].iov_len = म_माप(test_strs[i]) + 1;
		total_len += vec[i].iov_len;
	पूर्ण
	msg.msg_iov = vec;
	msg.msg_iovlen = iov_len;

	EXPECT_EQ(sendmsg(self->cfd, &msg, 0), total_len);
	buf = दो_स्मृति(total_len);
	EXPECT_NE(recv(self->fd, buf, total_len, 0), -1);
	क्रम (i = 0; i < iov_len; i++) अणु
		EXPECT_EQ(स_भेद(test_strs[i], buf + len_cmp,
				 म_माप(test_strs[i])),
			  0);
		len_cmp += म_माप(buf + len_cmp) + 1;
	पूर्ण
	क्रम (i = 0; i < iov_len; i++)
		मुक्त(test_strs[i]);
	मुक्त(buf);
पूर्ण

TEST_F(tls, sendmsg_multiple_stress)
अणु
	अक्षर स्थिर *test_str = "abcdefghijklmno";
	काष्ठा iovec vec[1024];
	अक्षर *test_strs[1024];
	पूर्णांक iov_len = 1024;
	पूर्णांक total_len = 0;
	अक्षर buf[1 << 14];
	काष्ठा msghdr msg;
	पूर्णांक len_cmp = 0;
	पूर्णांक i;

	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	क्रम (i = 0; i < iov_len; i++) अणु
		test_strs[i] = (अक्षर *)दो_स्मृति(म_माप(test_str) + 1);
		snम_लिखो(test_strs[i], म_माप(test_str) + 1, "%s", test_str);
		vec[i].iov_base = (व्योम *)test_strs[i];
		vec[i].iov_len = म_माप(test_strs[i]) + 1;
		total_len += vec[i].iov_len;
	पूर्ण
	msg.msg_iov = vec;
	msg.msg_iovlen = iov_len;

	EXPECT_EQ(sendmsg(self->fd, &msg, 0), total_len);
	EXPECT_NE(recv(self->cfd, buf, total_len, 0), -1);

	क्रम (i = 0; i < iov_len; i++)
		len_cmp += म_माप(buf + len_cmp) + 1;

	क्रम (i = 0; i < iov_len; i++)
		मुक्त(test_strs[i]);
पूर्ण

TEST_F(tls, splice_from_pipe)
अणु
	पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर mem_send[TLS_PAYLOAD_MAX_LEN];
	अक्षर mem_recv[TLS_PAYLOAD_MAX_LEN];
	पूर्णांक p[2];

	ASSERT_GE(pipe(p), 0);
	EXPECT_GE(ग_लिखो(p[1], mem_send, send_len), 0);
	EXPECT_GE(splice(p[0], शून्य, self->fd, शून्य, send_len, 0), 0);
	EXPECT_EQ(recv(self->cfd, mem_recv, send_len, MSG_WAITALL), send_len);
	EXPECT_EQ(स_भेद(mem_send, mem_recv, send_len), 0);
पूर्ण

TEST_F(tls, splice_from_pipe2)
अणु
	पूर्णांक send_len = 16000;
	अक्षर mem_send[16000];
	अक्षर mem_recv[16000];
	पूर्णांक p2[2];
	पूर्णांक p[2];

	ASSERT_GE(pipe(p), 0);
	ASSERT_GE(pipe(p2), 0);
	EXPECT_GE(ग_लिखो(p[1], mem_send, 8000), 0);
	EXPECT_GE(splice(p[0], शून्य, self->fd, शून्य, 8000, 0), 0);
	EXPECT_GE(ग_लिखो(p2[1], mem_send + 8000, 8000), 0);
	EXPECT_GE(splice(p2[0], शून्य, self->fd, शून्य, 8000, 0), 0);
	EXPECT_EQ(recv(self->cfd, mem_recv, send_len, MSG_WAITALL), send_len);
	EXPECT_EQ(स_भेद(mem_send, mem_recv, send_len), 0);
पूर्ण

TEST_F(tls, send_and_splice)
अणु
	पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर mem_send[TLS_PAYLOAD_MAX_LEN];
	अक्षर mem_recv[TLS_PAYLOAD_MAX_LEN];
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len2 = 10;
	अक्षर buf[10];
	पूर्णांक p[2];

	ASSERT_GE(pipe(p), 0);
	EXPECT_EQ(send(self->fd, test_str, send_len2, 0), send_len2);
	EXPECT_EQ(recv(self->cfd, buf, send_len2, MSG_WAITALL), send_len2);
	EXPECT_EQ(स_भेद(test_str, buf, send_len2), 0);

	EXPECT_GE(ग_लिखो(p[1], mem_send, send_len), send_len);
	EXPECT_GE(splice(p[0], शून्य, self->fd, शून्य, send_len, 0), send_len);

	EXPECT_EQ(recv(self->cfd, mem_recv, send_len, MSG_WAITALL), send_len);
	EXPECT_EQ(स_भेद(mem_send, mem_recv, send_len), 0);
पूर्ण

TEST_F(tls, splice_to_pipe)
अणु
	पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर mem_send[TLS_PAYLOAD_MAX_LEN];
	अक्षर mem_recv[TLS_PAYLOAD_MAX_LEN];
	पूर्णांक p[2];

	ASSERT_GE(pipe(p), 0);
	EXPECT_GE(send(self->fd, mem_send, send_len, 0), 0);
	EXPECT_GE(splice(self->cfd, शून्य, p[1], शून्य, send_len, 0), 0);
	EXPECT_GE(पढ़ो(p[0], mem_recv, send_len), 0);
	EXPECT_EQ(स_भेद(mem_send, mem_recv, send_len), 0);
पूर्ण

TEST_F(tls, recvmsg_single)
अणु
	अक्षर स्थिर *test_str = "test_recvmsg_single";
	पूर्णांक send_len = म_माप(test_str) + 1;
	अक्षर buf[20];
	काष्ठा msghdr hdr;
	काष्ठा iovec vec;

	स_रखो(&hdr, 0, माप(hdr));
	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	vec.iov_base = (अक्षर *)buf;
	vec.iov_len = send_len;
	hdr.msg_iovlen = 1;
	hdr.msg_iov = &vec;
	EXPECT_NE(recvmsg(self->cfd, &hdr, 0), -1);
	EXPECT_EQ(स_भेद(test_str, buf, send_len), 0);
पूर्ण

TEST_F(tls, recvmsg_single_max)
अणु
	पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर send_mem[TLS_PAYLOAD_MAX_LEN];
	अक्षर recv_mem[TLS_PAYLOAD_MAX_LEN];
	काष्ठा iovec vec;
	काष्ठा msghdr hdr;

	EXPECT_EQ(send(self->fd, send_mem, send_len, 0), send_len);
	vec.iov_base = (अक्षर *)recv_mem;
	vec.iov_len = TLS_PAYLOAD_MAX_LEN;

	hdr.msg_iovlen = 1;
	hdr.msg_iov = &vec;
	EXPECT_NE(recvmsg(self->cfd, &hdr, 0), -1);
	EXPECT_EQ(स_भेद(send_mem, recv_mem, send_len), 0);
पूर्ण

TEST_F(tls, recvmsg_multiple)
अणु
	अचिन्हित पूर्णांक msg_iovlen = 1024;
	अचिन्हित पूर्णांक len_compared = 0;
	काष्ठा iovec vec[1024];
	अक्षर *iov_base[1024];
	अचिन्हित पूर्णांक iov_len = 16;
	पूर्णांक send_len = 1 << 14;
	अक्षर buf[1 << 14];
	काष्ठा msghdr hdr;
	पूर्णांक i;

	EXPECT_EQ(send(self->fd, buf, send_len, 0), send_len);
	क्रम (i = 0; i < msg_iovlen; i++) अणु
		iov_base[i] = (अक्षर *)दो_स्मृति(iov_len);
		vec[i].iov_base = iov_base[i];
		vec[i].iov_len = iov_len;
	पूर्ण

	hdr.msg_iovlen = msg_iovlen;
	hdr.msg_iov = vec;
	EXPECT_NE(recvmsg(self->cfd, &hdr, 0), -1);
	क्रम (i = 0; i < msg_iovlen; i++)
		len_compared += iov_len;

	क्रम (i = 0; i < msg_iovlen; i++)
		मुक्त(iov_base[i]);
पूर्ण

TEST_F(tls, single_send_multiple_recv)
अणु
	अचिन्हित पूर्णांक total_len = TLS_PAYLOAD_MAX_LEN * 2;
	अचिन्हित पूर्णांक send_len = TLS_PAYLOAD_MAX_LEN;
	अक्षर send_mem[TLS_PAYLOAD_MAX_LEN * 2];
	अक्षर recv_mem[TLS_PAYLOAD_MAX_LEN * 2];

	EXPECT_GE(send(self->fd, send_mem, total_len, 0), 0);
	स_रखो(recv_mem, 0, total_len);

	EXPECT_NE(recv(self->cfd, recv_mem, send_len, 0), -1);
	EXPECT_NE(recv(self->cfd, recv_mem + send_len, send_len, 0), -1);
	EXPECT_EQ(स_भेद(send_mem, recv_mem, total_len), 0);
पूर्ण

TEST_F(tls, multiple_send_single_recv)
अणु
	अचिन्हित पूर्णांक total_len = 2 * 10;
	अचिन्हित पूर्णांक send_len = 10;
	अक्षर recv_mem[2 * 10];
	अक्षर send_mem[10];

	EXPECT_GE(send(self->fd, send_mem, send_len, 0), 0);
	EXPECT_GE(send(self->fd, send_mem, send_len, 0), 0);
	स_रखो(recv_mem, 0, total_len);
	EXPECT_EQ(recv(self->cfd, recv_mem, total_len, MSG_WAITALL), total_len);

	EXPECT_EQ(स_भेद(send_mem, recv_mem, send_len), 0);
	EXPECT_EQ(स_भेद(send_mem, recv_mem + send_len, send_len), 0);
पूर्ण

TEST_F(tls, single_send_multiple_recv_non_align)
अणु
	स्थिर अचिन्हित पूर्णांक total_len = 15;
	स्थिर अचिन्हित पूर्णांक recv_len = 10;
	अक्षर recv_mem[recv_len * 2];
	अक्षर send_mem[total_len];

	EXPECT_GE(send(self->fd, send_mem, total_len, 0), 0);
	स_रखो(recv_mem, 0, total_len);

	EXPECT_EQ(recv(self->cfd, recv_mem, recv_len, 0), recv_len);
	EXPECT_EQ(recv(self->cfd, recv_mem + recv_len, recv_len, 0), 5);
	EXPECT_EQ(स_भेद(send_mem, recv_mem, total_len), 0);
पूर्ण

TEST_F(tls, recv_partial)
अणु
	अक्षर स्थिर *test_str = "test_read_partial";
	अक्षर स्थिर *test_str_first = "test_read";
	अक्षर स्थिर *test_str_second = "_partial";
	पूर्णांक send_len = म_माप(test_str) + 1;
	अक्षर recv_mem[18];

	स_रखो(recv_mem, 0, माप(recv_mem));
	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, recv_mem, म_माप(test_str_first),
		       MSG_WAITALL), -1);
	EXPECT_EQ(स_भेद(test_str_first, recv_mem, म_माप(test_str_first)), 0);
	स_रखो(recv_mem, 0, माप(recv_mem));
	EXPECT_NE(recv(self->cfd, recv_mem, म_माप(test_str_second),
		       MSG_WAITALL), -1);
	EXPECT_EQ(स_भेद(test_str_second, recv_mem, म_माप(test_str_second)),
		  0);
पूर्ण

TEST_F(tls, recv_nonblock)
अणु
	अक्षर buf[4096];
	bool err;

	EXPECT_EQ(recv(self->cfd, buf, माप(buf), MSG_DONTWAIT), -1);
	err = (त्रुटि_सं == EAGAIN || त्रुटि_सं == EWOULDBLOCK);
	EXPECT_EQ(err, true);
पूर्ण

TEST_F(tls, recv_peek)
अणु
	अक्षर स्थिर *test_str = "test_read_peek";
	पूर्णांक send_len = म_माप(test_str) + 1;
	अक्षर buf[15];

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, buf, send_len, MSG_PEEK), -1);
	EXPECT_EQ(स_भेद(test_str, buf, send_len), 0);
	स_रखो(buf, 0, माप(buf));
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(test_str, buf, send_len), 0);
पूर्ण

TEST_F(tls, recv_peek_multiple)
अणु
	अक्षर स्थिर *test_str = "test_read_peek";
	पूर्णांक send_len = म_माप(test_str) + 1;
	अचिन्हित पूर्णांक num_peeks = 100;
	अक्षर buf[15];
	पूर्णांक i;

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	क्रम (i = 0; i < num_peeks; i++) अणु
		EXPECT_NE(recv(self->cfd, buf, send_len, MSG_PEEK), -1);
		EXPECT_EQ(स_भेद(test_str, buf, send_len), 0);
		स_रखो(buf, 0, माप(buf));
	पूर्ण
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(test_str, buf, send_len), 0);
पूर्ण

TEST_F(tls, recv_peek_multiple_records)
अणु
	अक्षर स्थिर *test_str = "test_read_peek_mult_recs";
	अक्षर स्थिर *test_str_first = "test_read_peek";
	अक्षर स्थिर *test_str_second = "_mult_recs";
	पूर्णांक len;
	अक्षर buf[64];

	len = म_माप(test_str_first);
	EXPECT_EQ(send(self->fd, test_str_first, len, 0), len);

	len = म_माप(test_str_second) + 1;
	EXPECT_EQ(send(self->fd, test_str_second, len, 0), len);

	len = म_माप(test_str_first);
	स_रखो(buf, 0, len);
	EXPECT_EQ(recv(self->cfd, buf, len, MSG_PEEK | MSG_WAITALL), len);

	/* MSG_PEEK can only peek पूर्णांकo the current record. */
	len = म_माप(test_str_first);
	EXPECT_EQ(स_भेद(test_str_first, buf, len), 0);

	len = म_माप(test_str) + 1;
	स_रखो(buf, 0, len);
	EXPECT_EQ(recv(self->cfd, buf, len, MSG_WAITALL), len);

	/* Non-MSG_PEEK will advance strparser (and thereक्रमe record)
	 * however.
	 */
	len = म_माप(test_str) + 1;
	EXPECT_EQ(स_भेद(test_str, buf, len), 0);

	/* MSG_MORE will hold current record खोलो, so later MSG_PEEK
	 * will see everything.
	 */
	len = म_माप(test_str_first);
	EXPECT_EQ(send(self->fd, test_str_first, len, MSG_MORE), len);

	len = म_माप(test_str_second) + 1;
	EXPECT_EQ(send(self->fd, test_str_second, len, 0), len);

	len = म_माप(test_str) + 1;
	स_रखो(buf, 0, len);
	EXPECT_EQ(recv(self->cfd, buf, len, MSG_PEEK | MSG_WAITALL), len);

	len = म_माप(test_str) + 1;
	EXPECT_EQ(स_भेद(test_str, buf, len), 0);
पूर्ण

TEST_F(tls, recv_peek_large_buf_mult_recs)
अणु
	अक्षर स्थिर *test_str = "test_read_peek_mult_recs";
	अक्षर स्थिर *test_str_first = "test_read_peek";
	अक्षर स्थिर *test_str_second = "_mult_recs";
	पूर्णांक len;
	अक्षर buf[64];

	len = म_माप(test_str_first);
	EXPECT_EQ(send(self->fd, test_str_first, len, 0), len);

	len = म_माप(test_str_second) + 1;
	EXPECT_EQ(send(self->fd, test_str_second, len, 0), len);

	len = म_माप(test_str) + 1;
	स_रखो(buf, 0, len);
	EXPECT_NE((len = recv(self->cfd, buf, len,
			      MSG_PEEK | MSG_WAITALL)), -1);
	len = म_माप(test_str) + 1;
	EXPECT_EQ(स_भेद(test_str, buf, len), 0);
पूर्ण

TEST_F(tls, recv_lowat)
अणु
	अक्षर send_mem[10] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण;
	अक्षर recv_mem[20];
	पूर्णांक lowat = 8;

	EXPECT_EQ(send(self->fd, send_mem, 10, 0), 10);
	EXPECT_EQ(send(self->fd, send_mem, 5, 0), 5);

	स_रखो(recv_mem, 0, 20);
	EXPECT_EQ(setsockopt(self->cfd, SOL_SOCKET, SO_RCVLOWAT,
			     &lowat, माप(lowat)), 0);
	EXPECT_EQ(recv(self->cfd, recv_mem, 1, MSG_WAITALL), 1);
	EXPECT_EQ(recv(self->cfd, recv_mem + 1, 6, MSG_WAITALL), 6);
	EXPECT_EQ(recv(self->cfd, recv_mem + 7, 10, 0), 8);

	EXPECT_EQ(स_भेद(send_mem, recv_mem, 10), 0);
	EXPECT_EQ(स_भेद(send_mem, recv_mem + 10, 5), 0);
पूर्ण

TEST_F(tls, bidir)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10];
	पूर्णांक ret;

	अगर (!self->notls) अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 tls12;

		स_रखो(&tls12, 0, माप(tls12));
		tls12.info.version = variant->tls_version;
		tls12.info.cipher_type = TLS_CIPHER_AES_GCM_128;

		ret = setsockopt(self->fd, SOL_TLS, TLS_RX, &tls12,
				 माप(tls12));
		ASSERT_EQ(ret, 0);

		ret = setsockopt(self->cfd, SOL_TLS, TLS_TX, &tls12,
				 माप(tls12));
		ASSERT_EQ(ret, 0);
	पूर्ण

	ASSERT_EQ(म_माप(test_str) + 1, send_len);

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);

	स_रखो(buf, 0, माप(buf));

	EXPECT_EQ(send(self->cfd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->fd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण;

TEST_F(tls, pollin)
अणु
	अक्षर स्थिर *test_str = "test_poll";
	काष्ठा pollfd fd = अणु 0, 0, 0 पूर्ण;
	अक्षर buf[10];
	पूर्णांक send_len = 10;

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	fd.fd = self->cfd;
	fd.events = POLLIN;

	EXPECT_EQ(poll(&fd, 1, 20), 1);
	EXPECT_EQ(fd.revents & POLLIN, 1);
	EXPECT_EQ(recv(self->cfd, buf, send_len, MSG_WAITALL), send_len);
	/* Test timing out */
	EXPECT_EQ(poll(&fd, 1, 20), 0);
पूर्ण

TEST_F(tls, poll_रुको)
अणु
	अक्षर स्थिर *test_str = "test_poll_wait";
	पूर्णांक send_len = म_माप(test_str) + 1;
	काष्ठा pollfd fd = अणु 0, 0, 0 पूर्ण;
	अक्षर recv_mem[15];

	fd.fd = self->cfd;
	fd.events = POLLIN;
	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	/* Set समयout to inf. secs */
	EXPECT_EQ(poll(&fd, 1, -1), 1);
	EXPECT_EQ(fd.revents & POLLIN, 1);
	EXPECT_EQ(recv(self->cfd, recv_mem, send_len, MSG_WAITALL), send_len);
पूर्ण

TEST_F(tls, poll_रुको_split)
अणु
	काष्ठा pollfd fd = अणु 0, 0, 0 पूर्ण;
	अक्षर send_mem[20] = अणुपूर्ण;
	अक्षर recv_mem[15];

	fd.fd = self->cfd;
	fd.events = POLLIN;
	/* Send 20 bytes */
	EXPECT_EQ(send(self->fd, send_mem, माप(send_mem), 0),
		  माप(send_mem));
	/* Poll with inf. समयout */
	EXPECT_EQ(poll(&fd, 1, -1), 1);
	EXPECT_EQ(fd.revents & POLLIN, 1);
	EXPECT_EQ(recv(self->cfd, recv_mem, माप(recv_mem), MSG_WAITALL),
		  माप(recv_mem));

	/* Now the reमुख्यing 5 bytes of record data are in TLS ULP */
	fd.fd = self->cfd;
	fd.events = POLLIN;
	EXPECT_EQ(poll(&fd, 1, -1), 1);
	EXPECT_EQ(fd.revents & POLLIN, 1);
	EXPECT_EQ(recv(self->cfd, recv_mem, माप(recv_mem), 0),
		  माप(send_mem) - माप(recv_mem));
पूर्ण

TEST_F(tls, blocking)
अणु
	माप_प्रकार data = 100000;
	पूर्णांक res = विभाजन();

	EXPECT_NE(res, -1);

	अगर (res) अणु
		/* parent */
		माप_प्रकार left = data;
		अक्षर buf[16384];
		पूर्णांक status;
		पूर्णांक pid2;

		जबतक (left) अणु
			पूर्णांक res = send(self->fd, buf,
				       left > 16384 ? 16384 : left, 0);

			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण

		pid2 = रुको(&status);
		EXPECT_EQ(status, 0);
		EXPECT_EQ(res, pid2);
	पूर्ण अन्यथा अणु
		/* child */
		माप_प्रकार left = data;
		अक्षर buf[16384];

		जबतक (left) अणु
			पूर्णांक res = recv(self->cfd, buf,
				       left > 16384 ? 16384 : left, 0);

			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण
	पूर्ण
पूर्ण

TEST_F(tls, nonblocking)
अणु
	माप_प्रकार data = 100000;
	पूर्णांक sendbuf = 100;
	पूर्णांक flags;
	पूर्णांक res;

	flags = fcntl(self->fd, F_GETFL, 0);
	fcntl(self->fd, F_SETFL, flags | O_NONBLOCK);
	fcntl(self->cfd, F_SETFL, flags | O_NONBLOCK);

	/* Ensure nonblocking behavior by imposing a small send
	 * buffer.
	 */
	EXPECT_EQ(setsockopt(self->fd, SOL_SOCKET, SO_SNDBUF,
			     &sendbuf, माप(sendbuf)), 0);

	res = विभाजन();
	EXPECT_NE(res, -1);

	अगर (res) अणु
		/* parent */
		bool eagain = false;
		माप_प्रकार left = data;
		अक्षर buf[16384];
		पूर्णांक status;
		पूर्णांक pid2;

		जबतक (left) अणु
			पूर्णांक res = send(self->fd, buf,
				       left > 16384 ? 16384 : left, 0);

			अगर (res == -1 && त्रुटि_सं == EAGAIN) अणु
				eagain = true;
				usleep(10000);
				जारी;
			पूर्ण
			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण

		EXPECT_TRUE(eagain);
		pid2 = रुको(&status);

		EXPECT_EQ(status, 0);
		EXPECT_EQ(res, pid2);
	पूर्ण अन्यथा अणु
		/* child */
		bool eagain = false;
		माप_प्रकार left = data;
		अक्षर buf[16384];

		जबतक (left) अणु
			पूर्णांक res = recv(self->cfd, buf,
				       left > 16384 ? 16384 : left, 0);

			अगर (res == -1 && त्रुटि_सं == EAGAIN) अणु
				eagain = true;
				usleep(10000);
				जारी;
			पूर्ण
			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण
		EXPECT_TRUE(eagain);
	पूर्ण
पूर्ण

अटल व्योम
test_mutliproc(काष्ठा __test_metadata *_metadata, काष्ठा _test_data_tls *self,
	       bool sendpg, अचिन्हित पूर्णांक n_पढ़ोers, अचिन्हित पूर्णांक n_ग_लिखोrs)
अणु
	स्थिर अचिन्हित पूर्णांक n_children = n_पढ़ोers + n_ग_लिखोrs;
	स्थिर माप_प्रकार data = 6 * 1000 * 1000;
	स्थिर माप_प्रकार file_sz = data / 100;
	माप_प्रकार पढ़ो_bias, ग_लिखो_bias;
	पूर्णांक i, fd, child_id;
	अक्षर buf[file_sz];
	pid_t pid;

	/* Only allow multiples क्रम simplicity */
	ASSERT_EQ(!(n_पढ़ोers % n_ग_लिखोrs) || !(n_ग_लिखोrs % n_पढ़ोers), true);
	पढ़ो_bias = n_ग_लिखोrs / n_पढ़ोers ?: 1;
	ग_लिखो_bias = n_पढ़ोers / n_ग_लिखोrs ?: 1;

	/* prep a file to send */
	fd = खोलो("/tmp/", O_TMPखाता | O_RDWR, 0600);
	ASSERT_GE(fd, 0);

	स_रखो(buf, 0xac, file_sz);
	ASSERT_EQ(ग_लिखो(fd, buf, file_sz), file_sz);

	/* spawn children */
	क्रम (child_id = 0; child_id < n_children; child_id++) अणु
		pid = विभाजन();
		ASSERT_NE(pid, -1);
		अगर (!pid)
			अवरोध;
	पूर्ण

	/* parent रुकोs क्रम all children */
	अगर (pid) अणु
		क्रम (i = 0; i < n_children; i++) अणु
			पूर्णांक status;

			रुको(&status);
			EXPECT_EQ(status, 0);
		पूर्ण

		वापस;
	पूर्ण

	/* Split thपढ़ोs क्रम पढ़ोing and writing */
	अगर (child_id < n_पढ़ोers) अणु
		माप_प्रकार left = data * पढ़ो_bias;
		अक्षर rb[8001];

		जबतक (left) अणु
			पूर्णांक res;

			res = recv(self->cfd, rb,
				   left > माप(rb) ? माप(rb) : left, 0);

			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण
	पूर्ण अन्यथा अणु
		माप_प्रकार left = data * ग_लिखो_bias;

		जबतक (left) अणु
			पूर्णांक res;

			ASSERT_EQ(lseek(fd, 0, शुरू_से), 0);
			अगर (sendpg)
				res = sendfile(self->fd, fd, शून्य,
					       left > file_sz ? file_sz : left);
			अन्यथा
				res = send(self->fd, buf,
					   left > file_sz ? file_sz : left, 0);

			EXPECT_GE(res, 0);
			left -= res;
		पूर्ण
	पूर्ण
पूर्ण

TEST_F(tls, mutliproc_even)
अणु
	test_mutliproc(_metadata, self, false, 6, 6);
पूर्ण

TEST_F(tls, mutliproc_पढ़ोers)
अणु
	test_mutliproc(_metadata, self, false, 4, 12);
पूर्ण

TEST_F(tls, mutliproc_ग_लिखोrs)
अणु
	test_mutliproc(_metadata, self, false, 10, 2);
पूर्ण

TEST_F(tls, mutliproc_sendpage_even)
अणु
	test_mutliproc(_metadata, self, true, 6, 6);
पूर्ण

TEST_F(tls, mutliproc_sendpage_पढ़ोers)
अणु
	test_mutliproc(_metadata, self, true, 4, 12);
पूर्ण

TEST_F(tls, mutliproc_sendpage_ग_लिखोrs)
अणु
	test_mutliproc(_metadata, self, true, 10, 2);
पूर्ण

TEST_F(tls, control_msg)
अणु
	अगर (self->notls)
		वापस;

	अक्षर cbuf[CMSG_SPACE(माप(अक्षर))];
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक cmsg_len = माप(अक्षर);
	अक्षर record_type = 100;
	काष्ठा cmsghdr *cmsg;
	काष्ठा msghdr msg;
	पूर्णांक send_len = 10;
	काष्ठा iovec vec;
	अक्षर buf[10];

	vec.iov_base = (अक्षर *)test_str;
	vec.iov_len = 10;
	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;
	msg.msg_control = cbuf;
	msg.msg_controllen = माप(cbuf);
	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_TLS;
	/* test sending non-record types. */
	cmsg->cmsg_type = TLS_SET_RECORD_TYPE;
	cmsg->cmsg_len = CMSG_LEN(cmsg_len);
	*CMSG_DATA(cmsg) = record_type;
	msg.msg_controllen = cmsg->cmsg_len;

	EXPECT_EQ(sendmsg(self->fd, &msg, 0), send_len);
	/* Should fail because we didn't provide a control message */
	EXPECT_EQ(recv(self->cfd, buf, send_len, 0), -1);

	vec.iov_base = buf;
	EXPECT_EQ(recvmsg(self->cfd, &msg, MSG_WAITALL | MSG_PEEK), send_len);

	cmsg = CMSG_FIRSTHDR(&msg);
	EXPECT_NE(cmsg, शून्य);
	EXPECT_EQ(cmsg->cmsg_level, SOL_TLS);
	EXPECT_EQ(cmsg->cmsg_type, TLS_GET_RECORD_TYPE);
	record_type = *((अचिन्हित अक्षर *)CMSG_DATA(cmsg));
	EXPECT_EQ(record_type, 100);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);

	/* Recv the message again without MSG_PEEK */
	record_type = 0;
	स_रखो(buf, 0, माप(buf));

	EXPECT_EQ(recvmsg(self->cfd, &msg, MSG_WAITALL), send_len);
	cmsg = CMSG_FIRSTHDR(&msg);
	EXPECT_NE(cmsg, शून्य);
	EXPECT_EQ(cmsg->cmsg_level, SOL_TLS);
	EXPECT_EQ(cmsg->cmsg_type, TLS_GET_RECORD_TYPE);
	record_type = *((अचिन्हित अक्षर *)CMSG_DATA(cmsg));
	EXPECT_EQ(record_type, 100);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);
पूर्ण

TEST_F(tls, shutकरोwn)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;
	अक्षर buf[10];

	ASSERT_EQ(म_माप(test_str) + 1, send_len);

	EXPECT_EQ(send(self->fd, test_str, send_len, 0), send_len);
	EXPECT_NE(recv(self->cfd, buf, send_len, 0), -1);
	EXPECT_EQ(स_भेद(buf, test_str, send_len), 0);

	shutकरोwn(self->fd, SHUT_RDWR);
	shutकरोwn(self->cfd, SHUT_RDWR);
पूर्ण

TEST_F(tls, shutकरोwn_unsent)
अणु
	अक्षर स्थिर *test_str = "test_read";
	पूर्णांक send_len = 10;

	EXPECT_EQ(send(self->fd, test_str, send_len, MSG_MORE), send_len);

	shutकरोwn(self->fd, SHUT_RDWR);
	shutकरोwn(self->cfd, SHUT_RDWR);
पूर्ण

TEST_F(tls, shutकरोwn_reuse)
अणु
	काष्ठा sockaddr_in addr;
	पूर्णांक ret;

	shutकरोwn(self->fd, SHUT_RDWR);
	shutकरोwn(self->cfd, SHUT_RDWR);
	बंद(self->cfd);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	ret = bind(self->fd, &addr, माप(addr));
	EXPECT_EQ(ret, 0);
	ret = listen(self->fd, 10);
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	ret = connect(self->fd, &addr, माप(addr));
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, EISCONN);
पूर्ण

TEST(non_established) अणु
	काष्ठा tls12_crypto_info_aes_gcm_256 tls12;
	काष्ठा sockaddr_in addr;
	पूर्णांक sfd, ret, fd;
	socklen_t len;

	len = माप(addr);

	स_रखो(&tls12, 0, माप(tls12));
	tls12.info.version = TLS_1_2_VERSION;
	tls12.info.cipher_type = TLS_CIPHER_AES_GCM_256;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	ret = bind(sfd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);
	ret = listen(sfd, 10);
	ASSERT_EQ(ret, 0);

	ret = setsockopt(fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	EXPECT_EQ(ret, -1);
	/* TLS ULP not supported */
	अगर (त्रुटि_सं == ENOENT)
		वापस;
	EXPECT_EQ(त्रुटि_सं, ENOTCONN);

	ret = setsockopt(sfd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, ENOTCONN);

	ret = माला_लोockname(sfd, &addr, &len);
	ASSERT_EQ(ret, 0);

	ret = connect(fd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);

	ret = setsockopt(fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	ASSERT_EQ(ret, 0);

	ret = setsockopt(fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, EEXIST);

	बंद(fd);
	बंद(sfd);
पूर्ण

TEST(keysizes) अणु
	काष्ठा tls12_crypto_info_aes_gcm_256 tls12;
	काष्ठा sockaddr_in addr;
	पूर्णांक sfd, ret, fd, cfd;
	socklen_t len;
	bool notls;

	notls = false;
	len = माप(addr);

	स_रखो(&tls12, 0, माप(tls12));
	tls12.info.version = TLS_1_2_VERSION;
	tls12.info.cipher_type = TLS_CIPHER_AES_GCM_256;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	ret = bind(sfd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);
	ret = listen(sfd, 10);
	ASSERT_EQ(ret, 0);

	ret = माला_लोockname(sfd, &addr, &len);
	ASSERT_EQ(ret, 0);

	ret = connect(fd, &addr, माप(addr));
	ASSERT_EQ(ret, 0);

	ret = setsockopt(fd, IPPROTO_TCP, TCP_ULP, "tls", माप("tls"));
	अगर (ret != 0) अणु
		notls = true;
		म_लिखो("Failure setting TCP_ULP, testing without tls\n");
	पूर्ण

	अगर (!notls) अणु
		ret = setsockopt(fd, SOL_TLS, TLS_TX, &tls12,
				 माप(tls12));
		EXPECT_EQ(ret, 0);
	पूर्ण

	cfd = accept(sfd, &addr, &len);
	ASSERT_GE(cfd, 0);

	अगर (!notls) अणु
		ret = setsockopt(cfd, IPPROTO_TCP, TCP_ULP, "tls",
				 माप("tls"));
		EXPECT_EQ(ret, 0);

		ret = setsockopt(cfd, SOL_TLS, TLS_RX, &tls12,
				 माप(tls12));
		EXPECT_EQ(ret, 0);
	पूर्ण

	बंद(sfd);
	बंद(fd);
	बंद(cfd);
पूर्ण

TEST_HARNESS_MAIN
