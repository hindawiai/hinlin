<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nosy-dump - Interface to snoop mode driver क्रम TI PCILynx 1394 controllers
 * Copyright (C) 2002-2006 Kristian Hथचgsberg
 */

#समावेश <byteswap.h>
#समावेश <endian.h>
#समावेश <fcntl.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <poll.h>
#समावेश <popt.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/समय.स>
#समावेश <termios.h>
#समावेश <unistd.h>

#समावेश "list.h"
#समावेश "nosy-dump.h"
#समावेश "nosy-user.h"

क्रमागत अणु
	PACKET_FIELD_DETAIL		= 0x01,
	PACKET_FIELD_DATA_LENGTH	= 0x02,
	/* Marks the fields we prपूर्णांक in transaction view. */
	PACKET_FIELD_TRANSACTION	= 0x04,
पूर्ण;

अटल व्योम prपूर्णांक_packet(uपूर्णांक32_t *data, माप_प्रकार length);
अटल व्योम decode_link_packet(काष्ठा link_packet *packet, माप_प्रकार length,
			       पूर्णांक include_flags, पूर्णांक exclude_flags);
अटल पूर्णांक run = 1;
sig_t sys_sigपूर्णांक_handler;

अटल अक्षर *option_nosy_device = "/dev/nosy";
अटल अक्षर *option_view = "packet";
अटल अक्षर *option_output;
अटल अक्षर *option_input;
अटल पूर्णांक option_hex;
अटल पूर्णांक option_iso;
अटल पूर्णांक option_cycle_start;
अटल पूर्णांक option_version;
अटल पूर्णांक option_verbose;

क्रमागत अणु
	VIEW_TRANSACTION,
	VIEW_PACKET,
	VIEW_STATS,
पूर्ण;

अटल स्थिर काष्ठा poptOption options[] = अणु
	अणु
		.दीर्घName	= "device",
		.लघुName	= 'd',
		.argInfo	= POPT_ARG_STRING,
		.arg		= &option_nosy_device,
		.descrip	= "Path to nosy device.",
		.argDescrip	= "DEVICE"
	पूर्ण,
	अणु
		.दीर्घName	= "view",
		.argInfo	= POPT_ARG_STRING,
		.arg		= &option_view,
		.descrip	= "Specify view of bus traffic: packet, transaction or stats.",
		.argDescrip	= "VIEW"
	पूर्ण,
	अणु
		.दीर्घName	= "hex",
		.लघुName	= 'x',
		.argInfo	= POPT_ARG_NONE,
		.arg		= &option_hex,
		.descrip	= "Print each packet in hex.",
	पूर्ण,
	अणु
		.दीर्घName	= "iso",
		.argInfo	= POPT_ARG_NONE,
		.arg		= &option_iso,
		.descrip	= "Print iso packets.",
	पूर्ण,
	अणु
		.दीर्घName	= "cycle-start",
		.argInfo	= POPT_ARG_NONE,
		.arg		= &option_cycle_start,
		.descrip	= "Print cycle start packets.",
	पूर्ण,
	अणु
		.दीर्घName	= "verbose",
		.लघुName	= 'v',
		.argInfo	= POPT_ARG_NONE,
		.arg		= &option_verbose,
		.descrip	= "Verbose packet view.",
	पूर्ण,
	अणु
		.दीर्घName	= "output",
		.लघुName	= 'o',
		.argInfo	= POPT_ARG_STRING,
		.arg		= &option_output,
		.descrip	= "Log to output file.",
		.argDescrip	= "FILENAME"
	पूर्ण,
	अणु
		.दीर्घName	= "input",
		.लघुName	= 'i',
		.argInfo	= POPT_ARG_STRING,
		.arg		= &option_input,
		.descrip	= "Decode log from file.",
		.argDescrip	= "FILENAME"
	पूर्ण,
	अणु
		.दीर्घName	= "version",
		.argInfo	= POPT_ARG_NONE,
		.arg		= &option_version,
		.descrip	= "Specify print version info.",
	पूर्ण,
	POPT_AUTOHELP
	POPT_TABLEEND
पूर्ण;

/* Allow all ^C except the first to पूर्णांकerrupt the program in the usual way. */
अटल व्योम
sigपूर्णांक_handler(पूर्णांक संकेत_num)
अणु
	अगर (run == 1) अणु
		run = 0;
		संकेत(संक_विघ्न, संक_पूर्व);
	पूर्ण
पूर्ण

अटल काष्ठा subaction *
subaction_create(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	काष्ठा subaction *sa;

	/* we put the ack in the subaction काष्ठा क्रम easy access. */
	sa = दो_स्मृति(माप *sa - माप sa->packet + length);
	अगर (!sa)
		निकास(निकास_त्रुटि);
	sa->ack = data[length / 4 - 1];
	sa->length = length;
	स_नकल(&sa->packet, data, length);

	वापस sa;
पूर्ण

अटल व्योम
subaction_destroy(काष्ठा subaction *sa)
अणु
	मुक्त(sa);
पूर्ण

अटल काष्ठा list pending_transaction_list = अणु
	&pending_transaction_list, &pending_transaction_list
पूर्ण;

अटल काष्ठा link_transaction *
link_transaction_lookup(पूर्णांक request_node, पूर्णांक response_node, पूर्णांक tlabel)
अणु
	काष्ठा link_transaction *t;

	list_क्रम_each_entry(t, &pending_transaction_list, link) अणु
		अगर (t->request_node == request_node &&
		    t->response_node == response_node &&
		    t->tlabel == tlabel)
			वापस t;
	पूर्ण

	t = दो_स्मृति(माप *t);
	अगर (!t)
		निकास(निकास_त्रुटि);
	t->request_node = request_node;
	t->response_node = response_node;
	t->tlabel = tlabel;
	list_init(&t->request_list);
	list_init(&t->response_list);

	list_append(&pending_transaction_list, &t->link);

	वापस t;
पूर्ण

अटल व्योम
link_transaction_destroy(काष्ठा link_transaction *t)
अणु
	काष्ठा subaction *sa;

	जबतक (!list_empty(&t->request_list)) अणु
		sa = list_head(&t->request_list, काष्ठा subaction, link);
		list_हटाओ(&sa->link);
		subaction_destroy(sa);
	पूर्ण
	जबतक (!list_empty(&t->response_list)) अणु
		sa = list_head(&t->response_list, काष्ठा subaction, link);
		list_हटाओ(&sa->link);
		subaction_destroy(sa);
	पूर्ण
	मुक्त(t);
पूर्ण

काष्ठा protocol_decoder अणु
	स्थिर अक्षर *name;
	पूर्णांक (*decode)(काष्ठा link_transaction *t);
पूर्ण;

अटल स्थिर काष्ठा protocol_decoder protocol_decoders[] = अणु
	अणु "FCP", decode_fcp पूर्ण
पूर्ण;

अटल व्योम
handle_transaction(काष्ठा link_transaction *t)
अणु
	काष्ठा subaction *sa;
	पूर्णांक i;

	अगर (!t->request) अणु
		म_लिखो("BUG in handle_transaction\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < array_length(protocol_decoders); i++)
		अगर (protocol_decoders[i].decode(t))
			अवरोध;

	/* HACK: decode only fcp right now. */
	वापस;

	decode_link_packet(&t->request->packet, t->request->length,
			   PACKET_FIELD_TRANSACTION, 0);
	अगर (t->response)
		decode_link_packet(&t->response->packet, t->request->length,
				   PACKET_FIELD_TRANSACTION, 0);
	अन्यथा
		म_लिखो("[no response]");

	अगर (option_verbose) अणु
		list_क्रम_each_entry(sa, &t->request_list, link)
			prपूर्णांक_packet((uपूर्णांक32_t *) &sa->packet, sa->length);
		list_क्रम_each_entry(sa, &t->response_list, link)
			prपूर्णांक_packet((uपूर्णांक32_t *) &sa->packet, sa->length);
	पूर्ण
	म_लिखो("\r\n");

	link_transaction_destroy(t);
पूर्ण

अटल व्योम
clear_pending_transaction_list(व्योम)
अणु
	काष्ठा link_transaction *t;

	जबतक (!list_empty(&pending_transaction_list)) अणु
		t = list_head(&pending_transaction_list,
			      काष्ठा link_transaction, link);
		list_हटाओ(&t->link);
		link_transaction_destroy(t);
		/* prपूर्णांक unfinished transactions */
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर tcode_names[] = अणु
	[0x0] = "write_quadlet_request",	[0x6] = "read_quadlet_response",
	[0x1] = "write_block_request",		[0x7] = "read_block_response",
	[0x2] = "write_response",		[0x8] = "cycle_start",
	[0x3] = "reserved",			[0x9] = "lock_request",
	[0x4] = "read_quadlet_request",		[0xa] = "iso_data",
	[0x5] = "read_block_request",		[0xb] = "lock_response",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ack_names[] = अणु
	[0x0] = "no ack",			[0x8] = "reserved (0x08)",
	[0x1] = "ack_complete",			[0x9] = "reserved (0x09)",
	[0x2] = "ack_pending",			[0xa] = "reserved (0x0a)",
	[0x3] = "reserved (0x03)",		[0xb] = "reserved (0x0b)",
	[0x4] = "ack_busy_x",			[0xc] = "reserved (0x0c)",
	[0x5] = "ack_busy_a",			[0xd] = "ack_data_error",
	[0x6] = "ack_busy_b",			[0xe] = "ack_type_error",
	[0x7] = "reserved (0x07)",		[0xf] = "reserved (0x0f)",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rcode_names[] = अणु
	[0x0] = "complete",			[0x4] = "conflict_error",
	[0x1] = "reserved (0x01)",		[0x5] = "data_error",
	[0x2] = "reserved (0x02)",		[0x6] = "type_error",
	[0x3] = "reserved (0x03)",		[0x7] = "address_error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर retry_names[] = अणु
	[0x0] = "retry_1",
	[0x1] = "retry_x",
	[0x2] = "retry_a",
	[0x3] = "retry_b",
पूर्ण;

क्रमागत अणु
	PACKET_RESERVED,
	PACKET_REQUEST,
	PACKET_RESPONSE,
	PACKET_OTHER,
पूर्ण;

काष्ठा packet_info अणु
	स्थिर अक्षर *name;
	पूर्णांक type;
	पूर्णांक response_tcode;
	स्थिर काष्ठा packet_field *fields;
	पूर्णांक field_count;
पूर्ण;

काष्ठा packet_field अणु
	स्थिर अक्षर *name; /* Short name क्रम field. */
	पूर्णांक offset;	/* Location of field, specअगरied in bits; */
			/* negative means from end of packet.    */
	पूर्णांक width;	/* Width of field, 0 means use data_length. */
	पूर्णांक flags;	/* Show options. */
	स्थिर अक्षर * स्थिर *value_names;
पूर्ण;

#घोषणा COMMON_REQUEST_FIELDS						\
	अणु "dest", 0, 16, PACKET_FIELD_TRANSACTION पूर्ण,			\
	अणु "tl", 16, 6 पूर्ण,						\
	अणु "rt", 22, 2, PACKET_FIELD_DETAIL, retry_names पूर्ण,		\
	अणु "tcode", 24, 4, PACKET_FIELD_TRANSACTION, tcode_names पूर्ण,	\
	अणु "pri", 28, 4, PACKET_FIELD_DETAIL पूर्ण,				\
	अणु "src", 32, 16, PACKET_FIELD_TRANSACTION पूर्ण,			\
	अणु "offs", 48, 48, PACKET_FIELD_TRANSACTION पूर्ण

#घोषणा COMMON_RESPONSE_FIELDS						\
	अणु "dest", 0, 16 पूर्ण,						\
	अणु "tl", 16, 6 पूर्ण,						\
	अणु "rt", 22, 2, PACKET_FIELD_DETAIL, retry_names पूर्ण,		\
	अणु "tcode", 24, 4, 0, tcode_names पूर्ण,				\
	अणु "pri", 28, 4, PACKET_FIELD_DETAIL पूर्ण,				\
	अणु "src", 32, 16 पूर्ण,						\
	अणु "rcode", 48, 4, PACKET_FIELD_TRANSACTION, rcode_names पूर्ण

अटल स्थिर काष्ठा packet_field पढ़ो_quadlet_request_fields[] = अणु
	COMMON_REQUEST_FIELDS,
	अणु "crc", 96, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", 156, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field पढ़ो_quadlet_response_fields[] = अणु
	COMMON_RESPONSE_FIELDS,
	अणु "data", 96, 32, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "crc", 128, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", 188, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field पढ़ो_block_request_fields[] = अणु
	COMMON_REQUEST_FIELDS,
	अणु "data_length", 96, 16, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "extended_tcode", 112, 16 पूर्ण,
	अणु "crc", 128, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", 188, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field block_response_fields[] = अणु
	COMMON_RESPONSE_FIELDS,
	अणु "data_length", 96, 16, PACKET_FIELD_DATA_LENGTH पूर्ण,
	अणु "extended_tcode", 112, 16 पूर्ण,
	अणु "crc", 128, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "data", 160, 0, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "crc", -64, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", -4, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field ग_लिखो_quadlet_request_fields[] = अणु
	COMMON_REQUEST_FIELDS,
	अणु "data", 96, 32, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "ack", -4, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field block_request_fields[] = अणु
	COMMON_REQUEST_FIELDS,
	अणु "data_length", 96, 16, PACKET_FIELD_DATA_LENGTH | PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "extended_tcode", 112, 16, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "crc", 128, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "data", 160, 0, PACKET_FIELD_TRANSACTION पूर्ण,
	अणु "crc", -64, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", -4, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field ग_लिखो_response_fields[] = अणु
	COMMON_RESPONSE_FIELDS,
	अणु "reserved", 64, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", -4, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_field iso_data_fields[] = अणु
	अणु "data_length", 0, 16, PACKET_FIELD_DATA_LENGTH पूर्ण,
	अणु "tag", 16, 2 पूर्ण,
	अणु "channel", 18, 6 पूर्ण,
	अणु "tcode", 24, 4, 0, tcode_names पूर्ण,
	अणु "sy", 28, 4 पूर्ण,
	अणु "crc", 32, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "data", 64, 0 पूर्ण,
	अणु "crc", -64, 32, PACKET_FIELD_DETAIL पूर्ण,
	अणु "ack", -4, 4, 0, ack_names पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा packet_info packet_info[] = अणु
	अणु
		.name		= "write_quadlet_request",
		.type		= PACKET_REQUEST,
		.response_tcode	= TCODE_WRITE_RESPONSE,
		.fields		= ग_लिखो_quadlet_request_fields,
		.field_count	= array_length(ग_लिखो_quadlet_request_fields)
	पूर्ण,
	अणु
		.name		= "write_block_request",
		.type		= PACKET_REQUEST,
		.response_tcode	= TCODE_WRITE_RESPONSE,
		.fields		= block_request_fields,
		.field_count	= array_length(block_request_fields)
	पूर्ण,
	अणु
		.name		= "write_response",
		.type		= PACKET_RESPONSE,
		.fields		= ग_लिखो_response_fields,
		.field_count	= array_length(ग_लिखो_response_fields)
	पूर्ण,
	अणु
		.name		= "reserved",
		.type		= PACKET_RESERVED,
	पूर्ण,
	अणु
		.name		= "read_quadlet_request",
		.type		= PACKET_REQUEST,
		.response_tcode	= TCODE_READ_QUADLET_RESPONSE,
		.fields		= पढ़ो_quadlet_request_fields,
		.field_count	= array_length(पढ़ो_quadlet_request_fields)
	पूर्ण,
	अणु
		.name		= "read_block_request",
		.type		= PACKET_REQUEST,
		.response_tcode	= TCODE_READ_BLOCK_RESPONSE,
		.fields		= पढ़ो_block_request_fields,
		.field_count	= array_length(पढ़ो_block_request_fields)
	पूर्ण,
	अणु
		.name		= "read_quadlet_response",
		.type		= PACKET_RESPONSE,
		.fields		= पढ़ो_quadlet_response_fields,
		.field_count	= array_length(पढ़ो_quadlet_response_fields)
	पूर्ण,
	अणु
		.name		= "read_block_response",
		.type		= PACKET_RESPONSE,
		.fields		= block_response_fields,
		.field_count	= array_length(block_response_fields)
	पूर्ण,
	अणु
		.name		= "cycle_start",
		.type		= PACKET_OTHER,
		.fields		= ग_लिखो_quadlet_request_fields,
		.field_count	= array_length(ग_लिखो_quadlet_request_fields)
	पूर्ण,
	अणु
		.name		= "lock_request",
		.type		= PACKET_REQUEST,
		.fields		= block_request_fields,
		.field_count	= array_length(block_request_fields)
	पूर्ण,
	अणु
		.name		= "iso_data",
		.type		= PACKET_OTHER,
		.fields		= iso_data_fields,
		.field_count	= array_length(iso_data_fields)
	पूर्ण,
	अणु
		.name		= "lock_response",
		.type		= PACKET_RESPONSE,
		.fields		= block_response_fields,
		.field_count	= array_length(block_response_fields)
	पूर्ण,
पूर्ण;

अटल पूर्णांक
handle_request_packet(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	काष्ठा link_packet *p = (काष्ठा link_packet *) data;
	काष्ठा subaction *sa, *prev;
	काष्ठा link_transaction *t;

	t = link_transaction_lookup(p->common.source, p->common.destination,
			p->common.tlabel);
	sa = subaction_create(data, length);
	t->request = sa;

	अगर (!list_empty(&t->request_list)) अणु
		prev = list_tail(&t->request_list,
				 काष्ठा subaction, link);

		अगर (!ACK_BUSY(prev->ack)) अणु
			/*
			 * error, we should only see ack_busy_* beक्रमe the
			 * ack_pending/ack_complete -- this is an ack_pending
			 * instead (ack_complete would have finished the
			 * transaction).
			 */
		पूर्ण

		अगर (prev->packet.common.tcode != sa->packet.common.tcode ||
		    prev->packet.common.tlabel != sa->packet.common.tlabel) अणु
			/* स_भेद() ? */
			/* error, these should match क्रम retries. */
		पूर्ण
	पूर्ण

	list_append(&t->request_list, &sa->link);

	चयन (sa->ack) अणु
	हाल ACK_COMPLETE:
		अगर (p->common.tcode != TCODE_WRITE_QUADLET_REQUEST &&
		    p->common.tcode != TCODE_WRITE_BLOCK_REQUEST)
			/* error, unअगरied transactions only allowed क्रम ग_लिखो */;
		list_हटाओ(&t->link);
		handle_transaction(t);
		अवरोध;

	हाल ACK_NO_ACK:
	हाल ACK_DATA_ERROR:
	हाल ACK_TYPE_ERROR:
		list_हटाओ(&t->link);
		handle_transaction(t);
		अवरोध;

	हाल ACK_PENDING:
		/* request subaction phase over, रुको क्रम response. */
		अवरोध;

	हाल ACK_BUSY_X:
	हाल ACK_BUSY_A:
	हाल ACK_BUSY_B:
		/* ok, रुको क्रम retry. */
		/* check that retry protocol is respected. */
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक
handle_response_packet(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	काष्ठा link_packet *p = (काष्ठा link_packet *) data;
	काष्ठा subaction *sa, *prev;
	काष्ठा link_transaction *t;

	t = link_transaction_lookup(p->common.destination, p->common.source,
			p->common.tlabel);
	अगर (list_empty(&t->request_list)) अणु
		/* unsolicited response */
	पूर्ण

	sa = subaction_create(data, length);
	t->response = sa;

	अगर (!list_empty(&t->response_list)) अणु
		prev = list_tail(&t->response_list, काष्ठा subaction, link);

		अगर (!ACK_BUSY(prev->ack)) अणु
			/*
			 * error, we should only see ack_busy_* beक्रमe the
			 * ack_pending/ack_complete
			 */
		पूर्ण

		अगर (prev->packet.common.tcode != sa->packet.common.tcode ||
		    prev->packet.common.tlabel != sa->packet.common.tlabel) अणु
			/* use स_भेद() instead? */
			/* error, these should match क्रम retries. */
		पूर्ण
	पूर्ण अन्यथा अणु
		prev = list_tail(&t->request_list, काष्ठा subaction, link);
		अगर (prev->ack != ACK_PENDING) अणु
			/*
			 * error, should not get response unless last request got
			 * ack_pending.
			 */
		पूर्ण

		अगर (packet_info[prev->packet.common.tcode].response_tcode !=
		    sa->packet.common.tcode) अणु
			/* error, tcode mismatch */
		पूर्ण
	पूर्ण

	list_append(&t->response_list, &sa->link);

	चयन (sa->ack) अणु
	हाल ACK_COMPLETE:
	हाल ACK_NO_ACK:
	हाल ACK_DATA_ERROR:
	हाल ACK_TYPE_ERROR:
		list_हटाओ(&t->link);
		handle_transaction(t);
		/* transaction complete, हटाओ t from pending list. */
		अवरोध;

	हाल ACK_PENDING:
		/* error क्रम responses. */
		अवरोध;

	हाल ACK_BUSY_X:
	हाल ACK_BUSY_A:
	हाल ACK_BUSY_B:
		/* no problem, रुको क्रम next retry */
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक
handle_packet(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	अगर (length == 0) अणु
		म_लिखो("bus reset\r\n");
		clear_pending_transaction_list();
	पूर्ण अन्यथा अगर (length > माप(काष्ठा phy_packet)) अणु
		काष्ठा link_packet *p = (काष्ठा link_packet *) data;

		चयन (packet_info[p->common.tcode].type) अणु
		हाल PACKET_REQUEST:
			वापस handle_request_packet(data, length);

		हाल PACKET_RESPONSE:
			वापस handle_response_packet(data, length);

		हाल PACKET_OTHER:
		हाल PACKET_RESERVED:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक
get_bits(काष्ठा link_packet *packet, पूर्णांक offset, पूर्णांक width)
अणु
	uपूर्णांक32_t *data = (uपूर्णांक32_t *) packet;
	uपूर्णांक32_t index, shअगरt, mask;

	index = offset / 32 + 1;
	shअगरt = 32 - (offset & 31) - width;
	mask = width == 32 ? ~0 : (1 << width) - 1;

	वापस (data[index] >> shअगरt) & mask;
पूर्ण

#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा byte_index(i) ((i) ^ 3)
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा byte_index(i) (i)
#अन्यथा
#त्रुटि unsupported byte order.
#पूर्ण_अगर

अटल व्योम
dump_data(अचिन्हित अक्षर *data, पूर्णांक length)
अणु
	पूर्णांक i, prपूर्णांक_length;

	अगर (length > 128)
		prपूर्णांक_length = 128;
	अन्यथा
		prपूर्णांक_length = length;

	क्रम (i = 0; i < prपूर्णांक_length; i++)
		म_लिखो("%s%02hhx",
		       (i % 4 == 0 && i != 0) ? " " : "",
		       data[byte_index(i)]);

	अगर (prपूर्णांक_length < length)
		म_लिखो(" (%d more bytes)", length - prपूर्णांक_length);
पूर्ण

अटल व्योम
decode_link_packet(काष्ठा link_packet *packet, माप_प्रकार length,
		   पूर्णांक include_flags, पूर्णांक exclude_flags)
अणु
	स्थिर काष्ठा packet_info *pi;
	पूर्णांक data_length = 0;
	पूर्णांक i;

	pi = &packet_info[packet->common.tcode];

	क्रम (i = 0; i < pi->field_count; i++) अणु
		स्थिर काष्ठा packet_field *f = &pi->fields[i];
		पूर्णांक offset;

		अगर (f->flags & exclude_flags)
			जारी;
		अगर (include_flags && !(f->flags & include_flags))
			जारी;

		अगर (f->offset < 0)
			offset = length * 8 + f->offset - 32;
		अन्यथा
			offset = f->offset;

		अगर (f->value_names != शून्य) अणु
			uपूर्णांक32_t bits;

			bits = get_bits(packet, offset, f->width);
			म_लिखो("%s", f->value_names[bits]);
		पूर्ण अन्यथा अगर (f->width == 0) अणु
			म_लिखो("%s=[", f->name);
			dump_data((अचिन्हित अक्षर *) packet + (offset / 8 + 4), data_length);
			म_लिखो("]");
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ दीर्घ bits;
			पूर्णांक high_width, low_width;

			अगर ((offset & ~31) != ((offset + f->width - 1) & ~31)) अणु
				/* Bit field spans quadlet boundary. */
				high_width = ((offset + 31) & ~31) - offset;
				low_width = f->width - high_width;

				bits = get_bits(packet, offset, high_width);
				bits = (bits << low_width) |
					get_bits(packet, offset + high_width, low_width);
			पूर्ण अन्यथा अणु
				bits = get_bits(packet, offset, f->width);
			पूर्ण

			म_लिखो("%s=0x%0*llx", f->name, (f->width + 3) / 4, bits);

			अगर (f->flags & PACKET_FIELD_DATA_LENGTH)
				data_length = bits;
		पूर्ण

		अगर (i < pi->field_count - 1)
			म_लिखो(", ");
	पूर्ण
पूर्ण

अटल व्योम
prपूर्णांक_packet(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	पूर्णांक i;

	म_लिखो("%6u  ", data[0]);

	अगर (length == 4) अणु
		म_लिखो("bus reset");
	पूर्ण अन्यथा अगर (length < माप(काष्ठा phy_packet)) अणु
		म_लिखो("short packet: ");
		क्रम (i = 1; i < length / 4; i++)
			म_लिखो("%s%08x", i == 0 ? "[" : " ", data[i]);
		म_लिखो("]");

	पूर्ण अन्यथा अगर (length == माप(काष्ठा phy_packet) && data[1] == ~data[2]) अणु
		काष्ठा phy_packet *pp = (काष्ठा phy_packet *) data;

		/* phy packet are 3 quadlets: the 1 quadlet payload,
		 * the bitwise inverse of the payload and the snoop
		 * mode ack */

		चयन (pp->common.identअगरier) अणु
		हाल PHY_PACKET_CONFIGURATION:
			अगर (!pp->phy_config.set_root && !pp->phy_config.set_gap_count) अणु
				म_लिखो("ext phy config: phy_id=%02x", pp->phy_config.root_id);
			पूर्ण अन्यथा अणु
				म_लिखो("phy config:");
				अगर (pp->phy_config.set_root)
					म_लिखो(" set_root_id=%02x", pp->phy_config.root_id);
				अगर (pp->phy_config.set_gap_count)
					म_लिखो(" set_gap_count=%d", pp->phy_config.gap_count);
			पूर्ण
			अवरोध;

		हाल PHY_PACKET_LINK_ON:
			म_लिखो("link-on packet, phy_id=%02x", pp->link_on.phy_id);
			अवरोध;

		हाल PHY_PACKET_SELF_ID:
			अगर (pp->self_id.extended) अणु
				म_लिखो("extended self id: phy_id=%02x, seq=%d",
				       pp->ext_self_id.phy_id, pp->ext_self_id.sequence);
			पूर्ण अन्यथा अणु
				अटल स्थिर अक्षर * स्थिर speed_names[] = अणु
					"S100", "S200", "S400", "BETA"
				पूर्ण;
				म_लिखो("self id: phy_id=%02x, link %s, gap_count=%d, speed=%s%s%s",
				       pp->self_id.phy_id,
				       (pp->self_id.link_active ? "active" : "not active"),
				       pp->self_id.gap_count,
				       speed_names[pp->self_id.phy_speed],
				       (pp->self_id.contender ? ", irm contender" : ""),
				       (pp->self_id.initiated_reset ? ", initiator" : ""));
			पूर्ण
			अवरोध;
		शेष:
			म_लिखो("unknown phy packet: ");
			क्रम (i = 1; i < length / 4; i++)
				म_लिखो("%s%08x", i == 0 ? "[" : " ", data[i]);
			म_लिखो("]");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा link_packet *packet = (काष्ठा link_packet *) data;

		decode_link_packet(packet, length, 0,
				   option_verbose ? 0 : PACKET_FIELD_DETAIL);
	पूर्ण

	अगर (option_hex) अणु
		म_लिखो("  [");
		dump_data((अचिन्हित अक्षर *) data + 4, length - 4);
		म_लिखो("]");
	पूर्ण

	म_लिखो("\r\n");
पूर्ण

#घोषणा HIDE_CURSOR	"\033[?25l"
#घोषणा SHOW_CURSOR	"\033[?25h"
#घोषणा CLEAR		"\033[H\033[2J"

अटल व्योम
prपूर्णांक_stats(uपूर्णांक32_t *data, माप_प्रकार length)
अणु
	अटल पूर्णांक bus_reset_count, लघु_packet_count, phy_packet_count;
	अटल पूर्णांक tcode_count[16];
	अटल काष्ठा समयval last_update;
	काष्ठा समयval now;
	पूर्णांक i;

	अगर (length == 0)
		bus_reset_count++;
	अन्यथा अगर (length < माप(काष्ठा phy_packet))
		लघु_packet_count++;
	अन्यथा अगर (length == माप(काष्ठा phy_packet) && data[1] == ~data[2])
		phy_packet_count++;
	अन्यथा अणु
		काष्ठा link_packet *packet = (काष्ठा link_packet *) data;
		tcode_count[packet->common.tcode]++;
	पूर्ण

	समय_लोofday(&now, शून्य);
	अगर (now.tv_sec <= last_update.tv_sec &&
	    now.tv_usec < last_update.tv_usec + 500000)
		वापस;

	last_update = now;
	म_लिखो(CLEAR HIDE_CURSOR
	       "  bus resets              : %8d\n"
	       "  short packets           : %8d\n"
	       "  phy packets             : %8d\n",
	       bus_reset_count, लघु_packet_count, phy_packet_count);

	क्रम (i = 0; i < array_length(packet_info); i++)
		अगर (packet_info[i].type != PACKET_RESERVED)
			म_लिखो("  %-24s: %8d\n", packet_info[i].name, tcode_count[i]);
	म_लिखो(SHOW_CURSOR "\n");
पूर्ण

अटल काष्ठा termios saved_attributes;

अटल व्योम
reset_input_mode(व्योम)
अणु
	tcsetattr(STDIN_खाताNO, TCSANOW, &saved_attributes);
पूर्ण

अटल व्योम
set_input_mode(व्योम)
अणु
	काष्ठा termios tattr;

	/* Make sure मानक_निवेश is a terminal. */
	अगर (!isatty(STDIN_खाताNO)) अणु
		ख_लिखो(मानक_त्रुटि, "Not a terminal.\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr(STDIN_खाताNO, &saved_attributes);
	निकास_पर(reset_input_mode);

	/* Set the funny terminal modes. */
	tcgetattr(STDIN_खाताNO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_खाताNO, TCSAFLUSH, &tattr);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	uपूर्णांक32_t buf[128 * 1024];
	uपूर्णांक32_t filter;
	पूर्णांक length, retval, view;
	पूर्णांक fd = -1;
	खाता *output = शून्य, *input = शून्य;
	poptContext con;
	अक्षर c;
	काष्ठा pollfd pollfds[2];

	sys_sigपूर्णांक_handler = संकेत(संक_विघ्न, sigपूर्णांक_handler);

	con = poptGetContext(शून्य, argc, argv, options, 0);
	retval = poptGetNextOpt(con);
	अगर (retval < -1) अणु
		poptPrपूर्णांकUsage(con, मानक_निकास, 0);
		वापस -1;
	पूर्ण

	अगर (option_version) अणु
		म_लिखो("dump tool for nosy sniffer, version %s\n", VERSION);
		वापस 0;
	पूर्ण

	अगर (__BYTE_ORDER != __LITTLE_ENDIAN)
		ख_लिखो(मानक_त्रुटि, "warning: nosy has only been tested on little "
			"endian machines\n");

	अगर (option_input != शून्य) अणु
		input = ख_खोलो(option_input, "r");
		अगर (input == शून्य) अणु
			ख_लिखो(मानक_त्रुटि, "Could not open %s, %m\n", option_input);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		fd = खोलो(option_nosy_device, O_RDWR);
		अगर (fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Could not open %s, %m\n", option_nosy_device);
			वापस -1;
		पूर्ण
		set_input_mode();
	पूर्ण

	अगर (म_भेद(option_view, "transaction") == 0)
		view = VIEW_TRANSACTION;
	अन्यथा अगर (म_भेद(option_view, "stats") == 0)
		view = VIEW_STATS;
	अन्यथा
		view = VIEW_PACKET;

	अगर (option_output) अणु
		output = ख_खोलो(option_output, "w");
		अगर (output == शून्य) अणु
			ख_लिखो(मानक_त्रुटि, "Could not open %s, %m\n", option_output);
			वापस -1;
		पूर्ण
	पूर्ण

	रखो_भबफ(मानक_निकास, शून्य, _IOLBF, बफ_मान);

	filter = ~0;
	अगर (!option_iso)
		filter &= ~(1 << TCODE_STREAM_DATA);
	अगर (!option_cycle_start)
		filter &= ~(1 << TCODE_CYCLE_START);
	अगर (view == VIEW_STATS)
		filter = ~(1 << TCODE_CYCLE_START);

	ioctl(fd, NOSY_IOC_FILTER, filter);

	ioctl(fd, NOSY_IOC_START);

	pollfds[0].fd = fd;
	pollfds[0].events = POLLIN;
	pollfds[1].fd = STDIN_खाताNO;
	pollfds[1].events = POLLIN;

	जबतक (run) अणु
		अगर (input != शून्य) अणु
			अगर (ख_पढ़ो(&length, माप length, 1, input) != 1)
				वापस 0;
			ख_पढ़ो(buf, 1, length, input);
		पूर्ण अन्यथा अणु
			poll(pollfds, 2, -1);
			अगर (pollfds[1].revents) अणु
				पढ़ो(STDIN_खाताNO, &c, माप c);
				चयन (c) अणु
				हाल 'q':
					अगर (output != शून्य)
						ख_बंद(output);
					वापस 0;
				पूर्ण
			पूर्ण

			अगर (pollfds[0].revents)
				length = पढ़ो(fd, buf, माप buf);
			अन्यथा
				जारी;
		पूर्ण

		अगर (output != शून्य) अणु
			ख_डालो(&length, माप length, 1, output);
			ख_डालो(buf, 1, length, output);
		पूर्ण

		चयन (view) अणु
		हाल VIEW_TRANSACTION:
			handle_packet(buf, length);
			अवरोध;
		हाल VIEW_PACKET:
			prपूर्णांक_packet(buf, length);
			अवरोध;
		हाल VIEW_STATS:
			prपूर्णांक_stats(buf, length);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (output != शून्य)
		ख_बंद(output);

	बंद(fd);

	poptFreeContext(con);

	वापस 0;
पूर्ण
