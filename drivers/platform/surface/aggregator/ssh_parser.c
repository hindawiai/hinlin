<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SSH message parser.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/serial_hub.h>
#समावेश "ssh_parser.h"

/**
 * sshp_validate_crc() - Validate a CRC in raw message data.
 * @src: The span of data over which the CRC should be computed.
 * @crc: The poपूर्णांकer to the expected u16 CRC value.
 *
 * Computes the CRC of the provided data span (@src), compares it to the CRC
 * stored at the given address (@crc), and वापसs the result of this
 * comparison, i.e. %true अगर equal. This function is पूर्णांकended to run on raw
 * input/message data.
 *
 * Return: Returns %true अगर the computed CRC matches the stored CRC, %false
 * otherwise.
 */
अटल bool sshp_validate_crc(स्थिर काष्ठा ssam_span *src, स्थिर u8 *crc)
अणु
	u16 actual = ssh_crc(src->ptr, src->len);
	u16 expected = get_unaligned_le16(crc);

	वापस actual == expected;
पूर्ण

/**
 * sshp_starts_with_syn() - Check अगर the given data starts with SSH SYN bytes.
 * @src: The data span to check the start of.
 */
अटल bool sshp_starts_with_syn(स्थिर काष्ठा ssam_span *src)
अणु
	वापस src->len >= 2 && get_unaligned_le16(src->ptr) == SSH_MSG_SYN;
पूर्ण

/**
 * sshp_find_syn() - Find SSH SYN bytes in the given data span.
 * @src: The data span to search in.
 * @rem: The span (output) indicating the reमुख्यing data, starting with SSH
 *       SYN bytes, अगर found.
 *
 * Search क्रम SSH SYN bytes in the given source span. If found, set the @rem
 * span to the reमुख्यing data, starting with the first SYN bytes and capped by
 * the source span length, and वापस %true. This function करोes not copy any
 * data, but rather only sets poपूर्णांकers to the respective start addresses and
 * length values.
 *
 * If no SSH SYN bytes could be found, set the @rem span to the zero-length
 * span at the end of the source span and वापस %false.
 *
 * If partial SSH SYN bytes could be found at the end of the source span, set
 * the @rem span to cover these partial SYN bytes, capped by the end of the
 * source span, and वापस %false. This function should then be re-run once
 * more data is available.
 *
 * Return: Returns %true अगर a complete SSH SYN sequence could be found,
 * %false otherwise.
 */
bool sshp_find_syn(स्थिर काष्ठा ssam_span *src, काष्ठा ssam_span *rem)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < src->len - 1; i++) अणु
		अगर (likely(get_unaligned_le16(src->ptr + i) == SSH_MSG_SYN)) अणु
			rem->ptr = src->ptr + i;
			rem->len = src->len - i;
			वापस true;
		पूर्ण
	पूर्ण

	अगर (unlikely(src->ptr[src->len - 1] == (SSH_MSG_SYN & 0xff))) अणु
		rem->ptr = src->ptr + src->len - 1;
		rem->len = 1;
		वापस false;
	पूर्ण

	rem->ptr = src->ptr + src->len;
	rem->len = 0;
	वापस false;
पूर्ण

/**
 * sshp_parse_frame() - Parse SSH frame.
 * @dev: The device used क्रम logging.
 * @source: The source to parse from.
 * @frame: The parsed frame (output).
 * @payload: The parsed payload (output).
 * @maxlen: The maximum supported message length.
 *
 * Parses and validates a SSH frame, including its payload, from the given
 * source. Sets the provided @frame poपूर्णांकer to the start of the frame and
 * ग_लिखोs the limits of the frame payload to the provided @payload span
 * poपूर्णांकer.
 *
 * This function करोes not copy any data, but rather only validates the message
 * data and sets poपूर्णांकers (and length values) to indicate the respective parts.
 *
 * If no complete SSH frame could be found, the frame poपूर्णांकer will be set to
 * the %शून्य poपूर्णांकer and the payload span will be set to the null span (start
 * poपूर्णांकer %शून्य, size zero).
 *
 * Return: Returns zero on success or अगर the frame is incomplete, %-ENOMSG अगर
 * the start of the message is invalid, %-EBADMSG अगर any (frame-header or
 * payload) CRC is invalid, or %-EMSGSIZE अगर the SSH message is bigger than
 * the maximum message length specअगरied in the @maxlen parameter.
 */
पूर्णांक sshp_parse_frame(स्थिर काष्ठा device *dev, स्थिर काष्ठा ssam_span *source,
		     काष्ठा ssh_frame **frame, काष्ठा ssam_span *payload,
		     माप_प्रकार maxlen)
अणु
	काष्ठा ssam_span sf;
	काष्ठा ssam_span sp;

	/* Initialize output. */
	*frame = शून्य;
	payload->ptr = शून्य;
	payload->len = 0;

	अगर (!sshp_starts_with_syn(source)) अणु
		dev_warn(dev, "rx: parser: invalid start of frame\n");
		वापस -ENOMSG;
	पूर्ण

	/* Check क्रम minimum packet length. */
	अगर (unlikely(source->len < SSH_MESSAGE_LENGTH(0))) अणु
		dev_dbg(dev, "rx: parser: not enough data for frame\n");
		वापस 0;
	पूर्ण

	/* Pin करोwn frame. */
	sf.ptr = source->ptr + माप(u16);
	sf.len = माप(काष्ठा ssh_frame);

	/* Validate frame CRC. */
	अगर (unlikely(!sshp_validate_crc(&sf, sf.ptr + sf.len))) अणु
		dev_warn(dev, "rx: parser: invalid frame CRC\n");
		वापस -EBADMSG;
	पूर्ण

	/* Ensure packet करोes not exceed maximum length. */
	sp.len = get_unaligned_le16(&((काष्ठा ssh_frame *)sf.ptr)->len);
	अगर (unlikely(SSH_MESSAGE_LENGTH(sp.len) > maxlen)) अणु
		dev_warn(dev, "rx: parser: frame too large: %llu bytes\n",
			 SSH_MESSAGE_LENGTH(sp.len));
		वापस -EMSGSIZE;
	पूर्ण

	/* Pin करोwn payload. */
	sp.ptr = sf.ptr + sf.len + माप(u16);

	/* Check क्रम frame + payload length. */
	अगर (source->len < SSH_MESSAGE_LENGTH(sp.len)) अणु
		dev_dbg(dev, "rx: parser: not enough data for payload\n");
		वापस 0;
	पूर्ण

	/* Validate payload CRC. */
	अगर (unlikely(!sshp_validate_crc(&sp, sp.ptr + sp.len))) अणु
		dev_warn(dev, "rx: parser: invalid payload CRC\n");
		वापस -EBADMSG;
	पूर्ण

	*frame = (काष्ठा ssh_frame *)sf.ptr;
	*payload = sp;

	dev_dbg(dev, "rx: parser: valid frame found (type: %#04x, len: %u)\n",
		(*frame)->type, (*frame)->len);

	वापस 0;
पूर्ण

/**
 * sshp_parse_command() - Parse SSH command frame payload.
 * @dev: The device used क्रम logging.
 * @source: The source to parse from.
 * @command: The parsed command (output).
 * @command_data: The parsed command data/payload (output).
 *
 * Parses and validates a SSH command frame payload. Sets the @command poपूर्णांकer
 * to the command header and the @command_data span to the command data (i.e.
 * payload of the command). This will result in a zero-length span अगर the
 * command करोes not have any associated data/payload. This function करोes not
 * check the frame-payload-type field, which should be checked by the caller
 * beक्रमe calling this function.
 *
 * The @source parameter should be the complete frame payload, e.g. वापसed
 * by the sshp_parse_frame() command.
 *
 * This function करोes not copy any data, but rather only validates the frame
 * payload data and sets poपूर्णांकers (and length values) to indicate the
 * respective parts.
 *
 * Return: Returns zero on success or %-ENOMSG अगर @source करोes not represent a
 * valid command-type frame payload, i.e. is too लघु.
 */
पूर्णांक sshp_parse_command(स्थिर काष्ठा device *dev, स्थिर काष्ठा ssam_span *source,
		       काष्ठा ssh_command **command,
		       काष्ठा ssam_span *command_data)
अणु
	/* Check क्रम minimum length. */
	अगर (unlikely(source->len < माप(काष्ठा ssh_command))) अणु
		*command = शून्य;
		command_data->ptr = शून्य;
		command_data->len = 0;

		dev_err(dev, "rx: parser: command payload is too short\n");
		वापस -ENOMSG;
	पूर्ण

	*command = (काष्ठा ssh_command *)source->ptr;
	command_data->ptr = source->ptr + माप(काष्ठा ssh_command);
	command_data->len = source->len - माप(काष्ठा ssh_command);

	dev_dbg(dev, "rx: parser: valid command found (tc: %#04x, cid: %#04x)\n",
		(*command)->tc, (*command)->cid);

	वापस 0;
पूर्ण
