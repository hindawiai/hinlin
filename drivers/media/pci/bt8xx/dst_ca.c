<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	CA-driver क्रम TwinHan DST Frontend/Card

	Copyright (C) 2004, 2005 Manu Abraham (manu@kromtek.com)

*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/dvb/ca.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_frontend.h>
#समावेश "dst_ca.h"
#समावेश "dst_common.h"

#घोषणा DST_CA_ERROR		0
#घोषणा DST_CA_NOTICE		1
#घोषणा DST_CA_INFO		2
#घोषणा DST_CA_DEBUG		3

#घोषणा dprपूर्णांकk(x, y, z, क्रमmat, arg...) करो अणु						\
	अगर (z) अणु									\
		अगर	((x > DST_CA_ERROR) && (x > y))					\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर	((x > DST_CA_NOTICE) && (x > y))				\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((x > DST_CA_INFO) && (x > y))					\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((x > DST_CA_DEBUG) && (x > y))					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (x > y)								\
			prपूर्णांकk(क्रमmat, ## arg);						\
	पूर्ण										\
पूर्ण जबतक(0)


अटल DEFINE_MUTEX(dst_ca_mutex);
अटल अचिन्हित पूर्णांक verbose = 5;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "verbose startup messages, default is 1 (yes)");

अटल व्योम put_command_and_length(u8 *data, पूर्णांक command, पूर्णांक length)
अणु
	data[0] = (command >> 16) & 0xff;
	data[1] = (command >> 8) & 0xff;
	data[2] = command & 0xff;
	data[3] = length;
पूर्ण

अटल व्योम put_checksum(u8 *check_string, पूर्णांक length)
अणु
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Computing string checksum.");
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, "  -> string length : 0x%02x", length);
	check_string[length] = dst_check_sum (check_string, length);
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, "  -> checksum      : 0x%02x", check_string[length]);
पूर्ण

अटल पूर्णांक dst_ci_command(काष्ठा dst_state* state, u8 * data, u8 *ca_string, u8 len, पूर्णांक पढ़ो)
अणु
	u8 reply;

	mutex_lock(&state->dst_mutex);
	dst_comm_init(state);
	msleep(65);

	अगर (ग_लिखो_dst(state, data, len)) अणु
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Write not successful, trying to recover");
		dst_error_recovery(state);
		जाओ error;
	पूर्ण
	अगर ((dst_pio_disable(state)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " DST PIO disable failed.");
		जाओ error;
	पूर्ण
	अगर (पढ़ो_dst(state, &reply, GET_ACK) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
		dst_error_recovery(state);
		जाओ error;
	पूर्ण
	अगर (पढ़ो) अणु
		अगर (! dst_रुको_dst_पढ़ोy(state, LONG_DELAY)) अणु
			dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " 8820 not ready");
			जाओ error;
		पूर्ण
		अगर (पढ़ो_dst(state, ca_string, 128) < 0) अणु	/*	Try to make this dynamic	*/
			dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
			dst_error_recovery(state);
			जाओ error;
		पूर्ण
	पूर्ण
	mutex_unlock(&state->dst_mutex);
	वापस 0;

error:
	mutex_unlock(&state->dst_mutex);
	वापस -EIO;
पूर्ण


अटल पूर्णांक dst_put_ci(काष्ठा dst_state *state, u8 *data, पूर्णांक len, u8 *ca_string, पूर्णांक पढ़ो)
अणु
	u8 dst_ca_comm_err = 0;

	जबतक (dst_ca_comm_err < RETRIES) अणु
		dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " Put Command");
		अगर (dst_ci_command(state, data, ca_string, len, पढ़ो)) अणु	// If error
			dst_error_recovery(state);
			dst_ca_comm_err++; // work required here.
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर(dst_ca_comm_err == RETRIES)
		वापस -EIO;

	वापस 0;
पूर्ण



अटल पूर्णांक ca_get_app_info(काष्ठा dst_state *state)
अणु
	पूर्णांक length, str_length;
	अटल u8 command[8] = अणु0x07, 0x40, 0x01, 0x00, 0x01, 0x00, 0x00, 0xffपूर्ण;

	put_checksum(&command[0], command[0]);
	अगर ((dst_put_ci(state, command, माप(command), state->messages, GET_REPLY)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->dst_put_ci FAILED !");
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->dst_put_ci SUCCESS !");
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " ================================ CI Module Application Info ======================================");
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Application Type=[%d], Application Vendor=[%d], Vendor Code=[%d]\n%s: Application info=[%s]",
		state->messages[7], (state->messages[8] << 8) | state->messages[9],
		(state->messages[10] << 8) | state->messages[11], __func__, (अक्षर *)(&state->messages[12]));
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " ==================================================================================================");

	// Transक्रमm dst message to correct application_info message
	length = state->messages[5];
	str_length = length - 6;
	अगर (str_length < 0) अणु
		str_length = 0;
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, "Invalid string length returned in ca_get_app_info(). Recovering.");
	पूर्ण

	// First, the command and length fields
	put_command_and_length(&state->messages[0], CA_APP_INFO, length);

	// Copy application_type, application_manufacturer and manufacturer_code
	स_हटाओ(&state->messages[4], &state->messages[7], 5);

	// Set string length and copy string
	state->messages[9] = str_length;
	स_हटाओ(&state->messages[10], &state->messages[12], str_length);

	वापस 0;
पूर्ण

अटल पूर्णांक ca_get_ca_info(काष्ठा dst_state *state)
अणु
	पूर्णांक srcPtr, dstPtr, i, num_ids;
	अटल u8 slot_command[8] = अणु0x07, 0x40, 0x00, 0x00, 0x02, 0x00, 0x00, 0xffपूर्ण;
	स्थिर पूर्णांक in_प्रणाली_id_pos = 8, out_प्रणाली_id_pos = 4, in_num_ids_pos = 7;

	put_checksum(&slot_command[0], slot_command[0]);
	अगर ((dst_put_ci(state, slot_command, माप (slot_command), state->messages, GET_REPLY)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->dst_put_ci FAILED !");
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->dst_put_ci SUCCESS !");

	// Prपूर्णांक raw data
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, " DST data = [");
	क्रम (i = 0; i < state->messages[0] + 1; i++) अणु
		dprपूर्णांकk(verbose, DST_CA_INFO, 0, " 0x%02x", state->messages[i]);
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "]\n");

	// Set the command and length of the output
	num_ids = state->messages[in_num_ids_pos];
	अगर (num_ids >= 100) अणु
		num_ids = 100;
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, "Invalid number of ids (>100). Recovering.");
	पूर्ण
	put_command_and_length(&state->messages[0], CA_INFO, num_ids * 2);

	dprपूर्णांकk(verbose, DST_CA_INFO, 0, " CA_INFO = [");
	srcPtr = in_प्रणाली_id_pos;
	dstPtr = out_प्रणाली_id_pos;
	क्रम(i = 0; i < num_ids; i++) अणु
		dprपूर्णांकk(verbose, DST_CA_INFO, 0, " 0x%02x%02x", state->messages[srcPtr + 0], state->messages[srcPtr + 1]);
		// Append to output
		state->messages[dstPtr + 0] = state->messages[srcPtr + 0];
		state->messages[dstPtr + 1] = state->messages[srcPtr + 1];
		srcPtr += 2;
		dstPtr += 2;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "]\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ca_get_slot_caps(काष्ठा dst_state *state, काष्ठा ca_caps *p_ca_caps, व्योम __user *arg)
अणु
	पूर्णांक i;
	u8 slot_cap[256];
	अटल u8 slot_command[8] = अणु0x07, 0x40, 0x02, 0x00, 0x02, 0x00, 0x00, 0xffपूर्ण;

	put_checksum(&slot_command[0], slot_command[0]);
	अगर ((dst_put_ci(state, slot_command, माप (slot_command), slot_cap, GET_REPLY)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->dst_put_ci FAILED !");
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " -->dst_put_ci SUCCESS !");

	/*	Will implement the rest soon		*/

	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Slot cap = [%d]", slot_cap[7]);
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "===================================\n");
	क्रम (i = 0; i < slot_cap[0] + 1; i++)
		dprपूर्णांकk(verbose, DST_CA_INFO, 0, " %d", slot_cap[i]);
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "\n");

	p_ca_caps->slot_num = 1;
	p_ca_caps->slot_type = 1;
	p_ca_caps->descr_num = slot_cap[7];
	p_ca_caps->descr_type = 1;

	अगर (copy_to_user(arg, p_ca_caps, माप (काष्ठा ca_caps)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*	Need some more work	*/
अटल पूर्णांक ca_get_slot_descr(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण


अटल पूर्णांक ca_get_slot_info(काष्ठा dst_state *state, काष्ठा ca_slot_info *p_ca_slot_info, व्योम __user *arg)
अणु
	पूर्णांक i;
	अटल u8 slot_command[8] = अणु0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xffपूर्ण;

	u8 *slot_info = state->messages;

	put_checksum(&slot_command[0], 7);
	अगर ((dst_put_ci(state, slot_command, माप (slot_command), slot_info, GET_REPLY)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->dst_put_ci FAILED !");
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->dst_put_ci SUCCESS !");

	/*	Will implement the rest soon		*/

	dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Slot info = [%d]", slot_info[3]);
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "===================================\n");
	क्रम (i = 0; i < 8; i++)
		dprपूर्णांकk(verbose, DST_CA_INFO, 0, " %d", slot_info[i]);
	dprपूर्णांकk(verbose, DST_CA_INFO, 0, "\n");

	अगर (slot_info[4] & 0x80) अणु
		p_ca_slot_info->flags = CA_CI_MODULE_PRESENT;
		p_ca_slot_info->num = 1;
		p_ca_slot_info->type = CA_CI;
	पूर्ण अन्यथा अगर (slot_info[4] & 0x40) अणु
		p_ca_slot_info->flags = CA_CI_MODULE_READY;
		p_ca_slot_info->num = 1;
		p_ca_slot_info->type = CA_CI;
	पूर्ण अन्यथा
		p_ca_slot_info->flags = 0;

	अगर (copy_to_user(arg, p_ca_slot_info, माप (काष्ठा ca_slot_info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण


अटल पूर्णांक ca_get_message(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, व्योम __user *arg)
अणु
	u8 i = 0;
	u32 command = 0;

	अगर (copy_from_user(p_ca_message, arg, माप (काष्ठा ca_msg)))
		वापस -EFAULT;

	dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " Message = [%*ph]",
		3, p_ca_message->msg);

	क्रम (i = 0; i < 3; i++) अणु
		command = command | p_ca_message->msg[i];
		अगर (i < 2)
			command = command << 8;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " Command=[0x%x]", command);

	चयन (command) अणु
	हाल CA_APP_INFO:
		स_नकल(p_ca_message->msg, state->messages, 128);
		अगर (copy_to_user(arg, p_ca_message, माप (काष्ठा ca_msg)) )
			वापस -EFAULT;
		अवरोध;
	हाल CA_INFO:
		स_नकल(p_ca_message->msg, state->messages, 128);
		अगर (copy_to_user(arg, p_ca_message, माप (काष्ठा ca_msg)) )
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक handle_dst_tag(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, काष्ठा ca_msg *hw_buffer, u32 length)
अणु
	अगर (state->dst_hw_cap & DST_TYPE_HAS_SESSION) अणु
		hw_buffer->msg[2] = p_ca_message->msg[1];	/*	MSB	*/
		hw_buffer->msg[3] = p_ca_message->msg[2];	/*	LSB	*/
	पूर्ण अन्यथा अणु
		अगर (length > 247) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " Message too long ! *** Bailing Out *** !");
			वापस -EIO;
		पूर्ण
		hw_buffer->msg[0] = (length & 0xff) + 7;
		hw_buffer->msg[1] = 0x40;
		hw_buffer->msg[2] = 0x03;
		hw_buffer->msg[3] = 0x00;
		hw_buffer->msg[4] = 0x03;
		hw_buffer->msg[5] = length & 0xff;
		hw_buffer->msg[6] = 0x00;

		/*
		 *	Need to compute length क्रम EN50221 section 8.3.2, क्रम the समय being
		 *	assuming 8.3.2 is not applicable
		 */
		स_नकल(&hw_buffer->msg[7], &p_ca_message->msg[4], length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_to_8820(काष्ठा dst_state *state, काष्ठा ca_msg *hw_buffer, u8 length, u8 reply)
अणु
	अगर ((dst_put_ci(state, hw_buffer->msg, length, hw_buffer->msg, reply)) < 0) अणु
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " DST-CI Command failed.");
		dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " Resetting DST.");
		rdc_reset_state(state);
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " DST-CI Command success.");

	वापस 0;
पूर्ण

अटल u32 asn_1_decode(u8 *asn_1_array)
अणु
	u8 length_field = 0, word_count = 0, count = 0;
	u32 length = 0;

	length_field = asn_1_array[0];
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Length field=[%02x]", length_field);
	अगर (length_field < 0x80) अणु
		length = length_field & 0x7f;
		dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Length=[%02x]\n", length);
	पूर्ण अन्यथा अणु
		word_count = length_field & 0x7f;
		क्रम (count = 0; count < word_count; count++) अणु
			length = length  << 8;
			length += asn_1_array[count + 1];
			dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Length=[%04x]", length);
		पूर्ण
	पूर्ण
	वापस length;
पूर्ण

अटल पूर्णांक debug_string(u8 *msg, u32 length, u32 offset)
अणु
	u32 i;

	dprपूर्णांकk(verbose, DST_CA_DEBUG, 0, " String=[ ");
	क्रम (i = offset; i < length; i++)
		dprपूर्णांकk(verbose, DST_CA_DEBUG, 0, "%02x ", msg[i]);
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 0, "]\n");

	वापस 0;
पूर्ण


अटल पूर्णांक ca_set_pmt(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, काष्ठा ca_msg *hw_buffer, u8 reply, u8 query)
अणु
	u32 length = 0;
	u8 tag_length = 8;

	length = asn_1_decode(&p_ca_message->msg[3]);
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " CA Message length=[%d]", length);
	debug_string(&p_ca_message->msg[4], length, 0); /*	length is excluding tag & length	*/

	स_रखो(hw_buffer->msg, '\0', length);
	handle_dst_tag(state, p_ca_message, hw_buffer, length);
	put_checksum(hw_buffer->msg, hw_buffer->msg[0]);

	debug_string(hw_buffer->msg, (length + tag_length), 0); /*	tags too	*/
	ग_लिखो_to_8820(state, hw_buffer, (length + tag_length), reply);

	वापस 0;
पूर्ण


/*	Board supports CA PMT reply ?		*/
अटल पूर्णांक dst_check_ca_pmt(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, काष्ठा ca_msg *hw_buffer)
अणु
	पूर्णांक ca_pmt_reply_test = 0;

	/*	Do test board			*/
	/*	Not there yet but soon		*/

	/*	CA PMT Reply capable		*/
	अगर (ca_pmt_reply_test) अणु
		अगर ((ca_set_pmt(state, p_ca_message, hw_buffer, 1, GET_REPLY)) < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " ca_set_pmt.. failed !");
			वापस -EIO;
		पूर्ण

	/*	Process CA PMT Reply		*/
	/*	will implement soon		*/
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " Not there yet");
	पूर्ण
	/*	CA PMT Reply not capable	*/
	अगर (!ca_pmt_reply_test) अणु
		अगर ((ca_set_pmt(state, p_ca_message, hw_buffer, 0, NO_REPLY)) < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " ca_set_pmt.. failed !");
			वापस -EIO;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_NOTICE, 1, " ca_set_pmt.. success !");
	/*	put a dummy message		*/

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ca_send_message(काष्ठा dst_state *state, काष्ठा ca_msg *p_ca_message, व्योम __user *arg)
अणु
	पूर्णांक i;
	u32 command;
	काष्ठा ca_msg *hw_buffer;
	पूर्णांक result = 0;

	hw_buffer = kदो_स्मृति(माप(*hw_buffer), GFP_KERNEL);
	अगर (!hw_buffer)
		वापस -ENOMEM;
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " ");

	अगर (copy_from_user(p_ca_message, arg, माप (काष्ठा ca_msg))) अणु
		result = -EFAULT;
		जाओ मुक्त_mem_and_निकास;
	पूर्ण

	/*	EN50221 tag	*/
	command = 0;

	क्रम (i = 0; i < 3; i++) अणु
		command = command | p_ca_message->msg[i];
		अगर (i < 2)
			command = command << 8;
	पूर्ण
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Command=[0x%x]\n", command);

	चयन (command) अणु
	हाल CA_PMT:
		dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, "Command = SEND_CA_PMT");
		अगर ((ca_set_pmt(state, p_ca_message, hw_buffer, 0, 0)) < 0) अणु	// code simplअगरication started
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_PMT Failed !");
			result = -1;
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_PMT Success !");
		अवरोध;
	हाल CA_PMT_REPLY:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, "Command = CA_PMT_REPLY");
		/*      Have to handle the 2 basic types of cards here  */
		अगर ((dst_check_ca_pmt(state, p_ca_message, hw_buffer)) < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_PMT_REPLY Failed !");
			result = -1;
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_PMT_REPLY Success !");
		अवरोध;
	हाल CA_APP_INFO_ENQUIRY:		// only क्रम debugging
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting Cam Application information");

		अगर ((ca_get_app_info(state)) < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_APP_INFO_ENQUIRY Failed !");
			result = -1;
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_APP_INFO_ENQUIRY Success !");
		अवरोध;
	हाल CA_INFO_ENQUIRY:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting CA Information");

		अगर ((ca_get_ca_info(state)) < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_INFO_ENQUIRY Failed !");
			result = -1;
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_INFO_ENQUIRY Success !");
		अवरोध;
	पूर्ण

मुक्त_mem_and_निकास:
	kमुक्त (hw_buffer);

	वापस result;
पूर्ण

अटल दीर्घ dst_ca_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ ioctl_arg)
अणु
	काष्ठा dvb_device *dvbdev;
	काष्ठा dst_state *state;
	काष्ठा ca_slot_info *p_ca_slot_info;
	काष्ठा ca_caps *p_ca_caps;
	काष्ठा ca_msg *p_ca_message;
	व्योम __user *arg = (व्योम __user *)ioctl_arg;
	पूर्णांक result = 0;

	mutex_lock(&dst_ca_mutex);
	dvbdev = file->निजी_data;
	state = (काष्ठा dst_state *)dvbdev->priv;
	p_ca_message = kदो_स्मृति(माप (काष्ठा ca_msg), GFP_KERNEL);
	p_ca_slot_info = kदो_स्मृति(माप (काष्ठा ca_slot_info), GFP_KERNEL);
	p_ca_caps = kदो_स्मृति(माप (काष्ठा ca_caps), GFP_KERNEL);
	अगर (!p_ca_message || !p_ca_slot_info || !p_ca_caps) अणु
		result = -ENOMEM;
		जाओ मुक्त_mem_and_निकास;
	पूर्ण

	/*	We have now only the standard ioctl's, the driver is upposed to handle पूर्णांकernals.	*/
	चयन (cmd) अणु
	हाल CA_SEND_MSG:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Sending message");
		result = ca_send_message(state, p_ca_message, arg);

		अगर (result < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_SEND_MSG Failed !");
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		अवरोध;
	हाल CA_GET_MSG:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting message");
		result = ca_get_message(state, p_ca_message, arg);
		अगर (result < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_GET_MSG Failed !");
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_GET_MSG Success !");
		अवरोध;
	हाल CA_RESET:
		dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " Resetting DST");
		dst_error_bailout(state);
		msleep(4000);
		अवरोध;
	हाल CA_GET_SLOT_INFO:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting Slot info");
		result = ca_get_slot_info(state, p_ca_slot_info, arg);
		अगर (result < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_GET_SLOT_INFO Failed !");
			result = -1;
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_GET_SLOT_INFO Success !");
		अवरोध;
	हाल CA_GET_CAP:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting Slot capabilities");
		result = ca_get_slot_caps(state, p_ca_caps, arg);
		अगर (result < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_GET_CAP Failed !");
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_GET_CAP Success !");
		अवरोध;
	हाल CA_GET_DESCR_INFO:
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " Getting descrambler description");
		result = ca_get_slot_descr(state, p_ca_message, arg);
		अगर (result < 0) अणु
			dprपूर्णांकk(verbose, DST_CA_ERROR, 1, " -->CA_GET_DESCR_INFO Failed !");
			जाओ मुक्त_mem_and_निकास;
		पूर्ण
		dprपूर्णांकk(verbose, DST_CA_INFO, 1, " -->CA_GET_DESCR_INFO Success !");
		अवरोध;
	शेष:
		result = -EOPNOTSUPP;
	पूर्ण
 मुक्त_mem_and_निकास:
	kमुक्त (p_ca_message);
	kमुक्त (p_ca_slot_info);
	kमुक्त (p_ca_caps);

	mutex_unlock(&dst_ca_mutex);
	वापस result;
पूर्ण

अटल पूर्णांक dst_ca_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Device opened [%p] ", file);

	वापस 0;
पूर्ण

अटल पूर्णांक dst_ca_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Device closed.");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dst_ca_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार length, loff_t *offset)
अणु
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Device read.");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dst_ca_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार length, loff_t *offset)
अणु
	dprपूर्णांकk(verbose, DST_CA_DEBUG, 1, " Device write.");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations dst_ca_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = dst_ca_ioctl,
	.खोलो = dst_ca_खोलो,
	.release = dst_ca_release,
	.पढ़ो = dst_ca_पढ़ो,
	.ग_लिखो = dst_ca_ग_लिखो,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_ca = अणु
	.priv = शून्य,
	.users = 1,
	.पढ़ोers = 1,
	.ग_लिखोrs = 1,
	.fops = &dst_ca_fops
पूर्ण;

काष्ठा dvb_device *dst_ca_attach(काष्ठा dst_state *dst, काष्ठा dvb_adapter *dvb_adapter)
अणु
	काष्ठा dvb_device *dvbdev;

	dprपूर्णांकk(verbose, DST_CA_ERROR, 1, "registering DST-CA device");
	अगर (dvb_रेजिस्टर_device(dvb_adapter, &dvbdev, &dvbdev_ca, dst,
				DVB_DEVICE_CA, 0) == 0) अणु
		dst->dst_ca = dvbdev;
		वापस dst->dst_ca;
	पूर्ण

	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(dst_ca_attach);

MODULE_DESCRIPTION("DST DVB-S/T/C Combo CA driver");
MODULE_AUTHOR("Manu Abraham");
MODULE_LICENSE("GPL");
