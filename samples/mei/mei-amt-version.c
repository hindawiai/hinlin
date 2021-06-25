<शैली गुरु>
/******************************************************************************
 * Intel Management Engine Interface (Intel MEI) Linux driver
 * Intel MEI Interface Header
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2012 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * Contact Inक्रमmation:
 *	Intel Corporation.
 *	linux-mei@linux.पूर्णांकel.com
 *	http://www.पूर्णांकel.com
 *
 * BSD LICENSE
 *
 * Copyright(c) 2003 - 2012 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <bits/wordsize.h>
#समावेश <linux/mei.h>

/*****************************************************************************
 * Intel Management Engine Interface
 *****************************************************************************/

#घोषणा mei_msg(_me, fmt, ARGS...) करो अणु         \
	अगर (_me->verbose)                       \
		ख_लिखो(मानक_त्रुटि, fmt, ##ARGS);	\
पूर्ण जबतक (0)

#घोषणा mei_err(_me, fmt, ARGS...) करो अणु         \
	ख_लिखो(मानक_त्रुटि, "Error: " fmt, ##ARGS); \
पूर्ण जबतक (0)

काष्ठा mei अणु
	uuid_le guid;
	bool initialized;
	bool verbose;
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित अक्षर prot_ver;
	पूर्णांक fd;
पूर्ण;

अटल व्योम mei_deinit(काष्ठा mei *cl)
अणु
	अगर (cl->fd != -1)
		बंद(cl->fd);
	cl->fd = -1;
	cl->buf_size = 0;
	cl->prot_ver = 0;
	cl->initialized = false;
पूर्ण

अटल bool mei_init(काष्ठा mei *me, स्थिर uuid_le *guid,
		अचिन्हित अक्षर req_protocol_version, bool verbose)
अणु
	पूर्णांक result;
	काष्ठा mei_client *cl;
	काष्ठा mei_connect_client_data data;

	me->verbose = verbose;

	me->fd = खोलो("/dev/mei0", O_RDWR);
	अगर (me->fd == -1) अणु
		mei_err(me, "Cannot establish a handle to the Intel MEI driver\n");
		जाओ err;
	पूर्ण
	स_नकल(&me->guid, guid, माप(*guid));
	स_रखो(&data, 0, माप(data));
	me->initialized = true;

	स_नकल(&data.in_client_uuid, &me->guid, माप(me->guid));
	result = ioctl(me->fd, IOCTL_MEI_CONNECT_CLIENT, &data);
	अगर (result) अणु
		mei_err(me, "IOCTL_MEI_CONNECT_CLIENT receive message. err=%d\n", result);
		जाओ err;
	पूर्ण
	cl = &data.out_client_properties;
	mei_msg(me, "max_message_length %d\n", cl->max_msg_length);
	mei_msg(me, "protocol_version %d\n", cl->protocol_version);

	अगर ((req_protocol_version > 0) &&
	     (cl->protocol_version != req_protocol_version)) अणु
		mei_err(me, "Intel MEI protocol version not supported\n");
		जाओ err;
	पूर्ण

	me->buf_size = cl->max_msg_length;
	me->prot_ver = cl->protocol_version;

	वापस true;
err:
	mei_deinit(me);
	वापस false;
पूर्ण

अटल sमाप_प्रकार mei_recv_msg(काष्ठा mei *me, अचिन्हित अक्षर *buffer,
			sमाप_प्रकार len, अचिन्हित दीर्घ समयout)
अणु
	sमाप_प्रकार rc;

	mei_msg(me, "call read length = %zd\n", len);

	rc = पढ़ो(me->fd, buffer, len);
	अगर (rc < 0) अणु
		mei_err(me, "read failed with status %zd %s\n",
				rc, म_त्रुटि(त्रुटि_सं));
		mei_deinit(me);
	पूर्ण अन्यथा अणु
		mei_msg(me, "read succeeded with result %zd\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mei_send_msg(काष्ठा mei *me, स्थिर अचिन्हित अक्षर *buffer,
			sमाप_प्रकार len, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा समयval tv;
	sमाप_प्रकार written;
	sमाप_प्रकार rc;
	fd_set set;

	tv.tv_sec = समयout / 1000;
	tv.tv_usec = (समयout % 1000) * 1000000;

	mei_msg(me, "call write length = %zd\n", len);

	written = ग_लिखो(me->fd, buffer, len);
	अगर (written < 0) अणु
		rc = -त्रुटि_सं;
		mei_err(me, "write failed with status %zd %s\n",
			written, म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	FD_ZERO(&set);
	FD_SET(me->fd, &set);
	rc = select(me->fd + 1 , &set, शून्य, शून्य, &tv);
	अगर (rc > 0 && FD_ISSET(me->fd, &set)) अणु
		mei_msg(me, "write success\n");
	पूर्ण अन्यथा अगर (rc == 0) अणु
		mei_err(me, "write failed on timeout with status\n");
		जाओ out;
	पूर्ण अन्यथा अणु /* rc < 0 */
		mei_err(me, "write failed on select with status %zd\n", rc);
		जाओ out;
	पूर्ण

	rc = written;
out:
	अगर (rc < 0)
		mei_deinit(me);

	वापस rc;
पूर्ण

/***************************************************************************
 * Intel Advanced Management Technology ME Client
 ***************************************************************************/

#घोषणा AMT_MAJOR_VERSION 1
#घोषणा AMT_MINOR_VERSION 1

#घोषणा AMT_STATUS_SUCCESS                0x0
#घोषणा AMT_STATUS_INTERNAL_ERROR         0x1
#घोषणा AMT_STATUS_NOT_READY              0x2
#घोषणा AMT_STATUS_INVALID_AMT_MODE       0x3
#घोषणा AMT_STATUS_INVALID_MESSAGE_LENGTH 0x4

#घोषणा AMT_STATUS_HOST_IF_EMPTY_RESPONSE  0x4000
#घोषणा AMT_STATUS_SDK_RESOURCES      0x1004


#घोषणा AMT_BIOS_VERSION_LEN   65
#घोषणा AMT_VERSIONS_NUMBER    50
#घोषणा AMT_UNICODE_STRING_LEN 20

काष्ठा amt_unicode_string अणु
	uपूर्णांक16_t length;
	अक्षर string[AMT_UNICODE_STRING_LEN];
पूर्ण __attribute__((packed));

काष्ठा amt_version_type अणु
	काष्ठा amt_unicode_string description;
	काष्ठा amt_unicode_string version;
पूर्ण __attribute__((packed));

काष्ठा amt_version अणु
	uपूर्णांक8_t major;
	uपूर्णांक8_t minor;
पूर्ण __attribute__((packed));

काष्ठा amt_code_versions अणु
	uपूर्णांक8_t bios[AMT_BIOS_VERSION_LEN];
	uपूर्णांक32_t count;
	काष्ठा amt_version_type versions[AMT_VERSIONS_NUMBER];
पूर्ण __attribute__((packed));

/***************************************************************************
 * Intel Advanced Management Technology Host Interface
 ***************************************************************************/

काष्ठा amt_host_अगर_msg_header अणु
	काष्ठा amt_version version;
	uपूर्णांक16_t _reserved;
	uपूर्णांक32_t command;
	uपूर्णांक32_t length;
पूर्ण __attribute__((packed));

काष्ठा amt_host_अगर_resp_header अणु
	काष्ठा amt_host_अगर_msg_header header;
	uपूर्णांक32_t status;
	अचिन्हित अक्षर data[];
पूर्ण __attribute__((packed));

स्थिर uuid_le MEI_IAMTHIF = UUID_LE(0x12f80028, 0xb4b7, 0x4b2d,  \
				0xac, 0xa8, 0x46, 0xe0, 0xff, 0x65, 0x81, 0x4c);

#घोषणा AMT_HOST_IF_CODE_VERSIONS_REQUEST  0x0400001A
#घोषणा AMT_HOST_IF_CODE_VERSIONS_RESPONSE 0x0480001A

स्थिर काष्ठा amt_host_अगर_msg_header CODE_VERSION_REQ = अणु
	.version = अणुAMT_MAJOR_VERSION, AMT_MINOR_VERSIONपूर्ण,
	._reserved = 0,
	.command = AMT_HOST_IF_CODE_VERSIONS_REQUEST,
	.length = 0
पूर्ण;


काष्ठा amt_host_अगर अणु
	काष्ठा mei mei_cl;
	अचिन्हित दीर्घ send_समयout;
	bool initialized;
पूर्ण;


अटल bool amt_host_अगर_init(काष्ठा amt_host_अगर *acmd,
		      अचिन्हित दीर्घ send_समयout, bool verbose)
अणु
	acmd->send_समयout = (send_समयout) ? send_समयout : 20000;
	acmd->initialized = mei_init(&acmd->mei_cl, &MEI_IAMTHIF, 0, verbose);
	वापस acmd->initialized;
पूर्ण

अटल व्योम amt_host_अगर_deinit(काष्ठा amt_host_अगर *acmd)
अणु
	mei_deinit(&acmd->mei_cl);
	acmd->initialized = false;
पूर्ण

अटल uपूर्णांक32_t amt_verअगरy_code_versions(स्थिर काष्ठा amt_host_अगर_resp_header *resp)
अणु
	uपूर्णांक32_t status = AMT_STATUS_SUCCESS;
	काष्ठा amt_code_versions *code_ver;
	माप_प्रकार code_ver_len;
	uपूर्णांक32_t ver_type_cnt;
	uपूर्णांक32_t len;
	uपूर्णांक32_t i;

	code_ver = (काष्ठा amt_code_versions *)resp->data;
	/* length - माप(status) */
	code_ver_len = resp->header.length - माप(uपूर्णांक32_t);
	ver_type_cnt = code_ver_len -
			माप(code_ver->bios) -
			माप(code_ver->count);
	अगर (code_ver->count != ver_type_cnt / माप(काष्ठा amt_version_type)) अणु
		status = AMT_STATUS_INTERNAL_ERROR;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < code_ver->count; i++) अणु
		len = code_ver->versions[i].description.length;

		अगर (len > AMT_UNICODE_STRING_LEN) अणु
			status = AMT_STATUS_INTERNAL_ERROR;
			जाओ out;
		पूर्ण

		len = code_ver->versions[i].version.length;
		अगर (code_ver->versions[i].version.string[len] != '\0' ||
		    len != म_माप(code_ver->versions[i].version.string)) अणु
			status = AMT_STATUS_INTERNAL_ERROR;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस status;
पूर्ण

अटल uपूर्णांक32_t amt_verअगरy_response_header(uपूर्णांक32_t command,
				स्थिर काष्ठा amt_host_अगर_msg_header *resp_hdr,
				uपूर्णांक32_t response_size)
अणु
	अगर (response_size < माप(काष्ठा amt_host_अगर_resp_header)) अणु
		वापस AMT_STATUS_INTERNAL_ERROR;
	पूर्ण अन्यथा अगर (response_size != (resp_hdr->length +
				माप(काष्ठा amt_host_अगर_msg_header))) अणु
		वापस AMT_STATUS_INTERNAL_ERROR;
	पूर्ण अन्यथा अगर (resp_hdr->command != command) अणु
		वापस AMT_STATUS_INTERNAL_ERROR;
	पूर्ण अन्यथा अगर (resp_hdr->_reserved != 0) अणु
		वापस AMT_STATUS_INTERNAL_ERROR;
	पूर्ण अन्यथा अगर (resp_hdr->version.major != AMT_MAJOR_VERSION ||
		   resp_hdr->version.minor < AMT_MINOR_VERSION) अणु
		वापस AMT_STATUS_INTERNAL_ERROR;
	पूर्ण
	वापस AMT_STATUS_SUCCESS;
पूर्ण

अटल uपूर्णांक32_t amt_host_अगर_call(काष्ठा amt_host_अगर *acmd,
			स्थिर अचिन्हित अक्षर *command, sमाप_प्रकार command_sz,
			uपूर्णांक8_t **पढ़ो_buf, uपूर्णांक32_t rcmd,
			अचिन्हित पूर्णांक expected_sz)
अणु
	uपूर्णांक32_t in_buf_sz;
	sमाप_प्रकार out_buf_sz;
	sमाप_प्रकार written;
	uपूर्णांक32_t status;
	काष्ठा amt_host_अगर_resp_header *msg_hdr;

	in_buf_sz = acmd->mei_cl.buf_size;
	*पढ़ो_buf = (uपूर्णांक8_t *)दो_स्मृति(माप(uपूर्णांक8_t) * in_buf_sz);
	अगर (*पढ़ो_buf == शून्य)
		वापस AMT_STATUS_SDK_RESOURCES;
	स_रखो(*पढ़ो_buf, 0, in_buf_sz);
	msg_hdr = (काष्ठा amt_host_अगर_resp_header *)*पढ़ो_buf;

	written = mei_send_msg(&acmd->mei_cl,
				command, command_sz, acmd->send_समयout);
	अगर (written != command_sz)
		वापस AMT_STATUS_INTERNAL_ERROR;

	out_buf_sz = mei_recv_msg(&acmd->mei_cl, *पढ़ो_buf, in_buf_sz, 2000);
	अगर (out_buf_sz <= 0)
		वापस AMT_STATUS_HOST_IF_EMPTY_RESPONSE;

	status = msg_hdr->status;
	अगर (status != AMT_STATUS_SUCCESS)
		वापस status;

	status = amt_verअगरy_response_header(rcmd,
				&msg_hdr->header, out_buf_sz);
	अगर (status != AMT_STATUS_SUCCESS)
		वापस status;

	अगर (expected_sz && expected_sz != out_buf_sz)
		वापस AMT_STATUS_INTERNAL_ERROR;

	वापस AMT_STATUS_SUCCESS;
पूर्ण


अटल uपूर्णांक32_t amt_get_code_versions(काष्ठा amt_host_अगर *cmd,
			       काष्ठा amt_code_versions *versions)
अणु
	काष्ठा amt_host_अगर_resp_header *response = शून्य;
	uपूर्णांक32_t status;

	status = amt_host_अगर_call(cmd,
			(स्थिर अचिन्हित अक्षर *)&CODE_VERSION_REQ,
			माप(CODE_VERSION_REQ),
			(uपूर्णांक8_t **)&response,
			AMT_HOST_IF_CODE_VERSIONS_RESPONSE, 0);

	अगर (status != AMT_STATUS_SUCCESS)
		जाओ out;

	status = amt_verअगरy_code_versions(response);
	अगर (status != AMT_STATUS_SUCCESS)
		जाओ out;

	स_नकल(versions, response->data, माप(काष्ठा amt_code_versions));
out:
	अगर (response != शून्य)
		मुक्त(response);

	वापस status;
पूर्ण

/************************** end of amt_host_अगर_command ***********************/
पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा amt_code_versions ver;
	काष्ठा amt_host_अगर acmd;
	अचिन्हित पूर्णांक i;
	uपूर्णांक32_t status;
	पूर्णांक ret;
	bool verbose;

	verbose = (argc > 1 && म_भेद(argv[1], "-v") == 0);

	अगर (!amt_host_अगर_init(&acmd, 5000, verbose)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	status = amt_get_code_versions(&acmd, &ver);

	amt_host_अगर_deinit(&acmd);

	चयन (status) अणु
	हाल AMT_STATUS_HOST_IF_EMPTY_RESPONSE:
		म_लिखो("Intel AMT: DISABLED\n");
		ret = 0;
		अवरोध;
	हाल AMT_STATUS_SUCCESS:
		म_लिखो("Intel AMT: ENABLED\n");
		क्रम (i = 0; i < ver.count; i++) अणु
			म_लिखो("%s:\t%s\n", ver.versions[i].description.string,
				ver.versions[i].version.string);
		पूर्ण
		ret = 0;
		अवरोध;
	शेष:
		म_लिखो("An error has occurred\n");
		ret = 1;
		अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण
